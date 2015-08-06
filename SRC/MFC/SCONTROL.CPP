/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

// SControl.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SControl.h"
#include	"savegame.h"
#include	"dinput.h"
#include	"winmove.h"

#ifdef _DEBUG
#ifndef THIS_FILE_DEFINED
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
struct	devdesc
{
	CString name;
	CString	prodname;
	int		numbuttons,
			numhats,
			numaxes;
	bool	enablepoll,
			useff,
			ismouse,
			supportsff;
	GUID	devid;
};

devdesc			connecteddevices[20];

struct	axisdesc
{
	CString	name;
	bool	ishat,
			firstofpair,
			xtype,
			ytype;
	int		devnum;
	int		axisnum;
	int		pairaxisnum;
	AxisUses
			assignedtask;
};
axisdesc	connectedaxes[100];
int useddevices,usedaxes,firstaxes;
int joystickalias,mousealias;

int currdevaxiscount,currdevhatcount;

static	BOOL CALLBACK DIEnumDeviceObjectsProc(LPCDIDEVICEOBJECTINSTANCE ddoi,LPVOID pvRef)
{
	connectedaxes[usedaxes].name=ddoi->tszName;
	connectedaxes[usedaxes].devnum=useddevices;
	connectedaxes[usedaxes].pairaxisnum=-1;
	connectedaxes[usedaxes].ytype=false;
	if (ddoi->guidType==GUID_POV)
	{
		connectedaxes[usedaxes].ishat=true;
		connectedaxes[usedaxes].pairaxisnum=usedaxes;
		connectedaxes[usedaxes].axisnum=currdevhatcount++;
		connectedaxes[usedaxes].assignedtask=AU_UNASSIGNED;
		connectedaxes[usedaxes].xtype=true;
		connectedaxes[usedaxes].firstofpair=true;
	}
	else
	{
		connectedaxes[usedaxes].ishat=false;
		connectedaxes[usedaxes].axisnum=currdevaxiscount++;
		connectedaxes[usedaxes].assignedtask=AU_UNASSIGNED;
		if (ddoi->guidType==GUID_XAxis)
		{
			connectedaxes[usedaxes].xtype=true;
			connectedaxes[usedaxes].firstofpair=true;
		}
		else if (ddoi->guidType==GUID_RyAxis || ddoi->guidType==GUID_RzAxis)// || ddoi->guidType==GUID_ZAxis) //DAW 15/02/00
		{
			connectedaxes[usedaxes].xtype=true;
			connectedaxes[usedaxes].firstofpair=false;
		}
		else
		{
			connectedaxes[usedaxes].xtype=false;
			connectedaxes[usedaxes].firstofpair=false;
			if (ddoi->guidType==GUID_YAxis)
				connectedaxes[usedaxes].ytype=true;
		}
	}
	usedaxes++;
	return DIENUM_CONTINUE;
}
static	void	FixPairs(int	usedaxesbefore,int	usedaxes)
{
	for (int xaxis=usedaxesbefore;xaxis<usedaxes;xaxis++)
		if (connectedaxes[xaxis].firstofpair && connectedaxes[xaxis].pairaxisnum ==-1)
		{
			int yaxis=xaxis+1;
			if (yaxis>=usedaxes || !connectedaxes[yaxis].ytype || connectedaxes[yaxis].pairaxisnum !=-1)
				for (yaxis=usedaxesbefore;yaxis<usedaxes;yaxis++)
					breakif(connectedaxes[yaxis].ytype && connectedaxes[yaxis].pairaxisnum ==-1);
			if (yaxis<usedaxes)
			{
				connectedaxes[xaxis].pairaxisnum=yaxis;
				connectedaxes[yaxis].pairaxisnum=xaxis;
			}
			else
			{
				connectedaxes[xaxis].firstofpair=false;
			}
		}
}

static void	ShiftDuplicate(int	usedaxesbefore,int	usedaxes)
{
}

static BOOL CALLBACK DIEnumDevicesProc(const DIDEVICEINSTANCE *ddi,LPVOID pvRef)
{
	if ((ddi->dwDevType&255)!=DIDEVTYPE_KEYBOARD)
	{
		LPDIRECTINPUT	DIdev=(LPDIRECTINPUT)pvRef;
		connecteddevices[useddevices].name=ddi->tszInstanceName;
		const char* prodname=ddi->tszProductName;
		while (strlen(prodname)>25)
			if (strchr(prodname,' '))
				prodname=strchr(prodname,' ')+1;
			else
				break;
		connecteddevices[useddevices].enablepoll=false;
		connecteddevices[useddevices].useff=false;
		connecteddevices[useddevices].prodname=prodname;
		connecteddevices[useddevices].devid=ddi->guidInstance;
		connecteddevices[useddevices].ismouse=((ddi->dwDevType&255)==DIDEVTYPE_MOUSE);
		LPDIRECTINPUTDEVICE dev;
		DIDEVCAPS			caps={sizeof(DIDEVCAPS)};
		DIdev->CreateDevice(connecteddevices[useddevices].devid,&dev,NULL);
		dev->GetCapabilities(&caps);
		connecteddevices[useddevices].supportsff=(caps.dwFlags&DIDC_FORCEFEEDBACK)!=0;
		connecteddevices[useddevices].numbuttons=caps.dwButtons;
		connecteddevices[useddevices].numhats=caps.dwPOVs;
		connecteddevices[useddevices].numaxes=caps.dwAxes;
		currdevaxiscount=0;
		currdevhatcount=0;
		int	usedaxesbefore=usedaxes;
		dev->EnumObjects(DIEnumDeviceObjectsProc,NULL,DIDFT_AXIS+DIDFT_POV);
		FixPairs(usedaxesbefore,usedaxes);
		dev->Release();
		useddevices++;
	}
	return DIENUM_CONTINUE;
}

void	SController::BuildEnumerationTables()
{
	useddevices=2;
	const middleaxes=20;
	usedaxes=middleaxes;
	firstaxes=middleaxes;
	LPDIRECTINPUT	DIdev;
	DirectInputCreate(AfxGetInstanceHandle( ),DIRECTINPUT_VERSION,&DIdev,NULL);
	DIdev->EnumDevices(DIDEVTYPE_MOUSE,DIEnumDevicesProc,DIdev,DIEDFL_ATTACHEDONLY);
	DIdev->EnumDevices(DIDEVTYPE_JOYSTICK,DIEnumDevicesProc,DIdev,DIEDFL_ATTACHEDONLY);
	int i;
	joystickalias=0;
	mousealias=0;
	for (i=2;i<useddevices;i++)
		breakif (!connecteddevices[i].ismouse);
	if (i<useddevices)	//copy first joystick as default
	{
		joystickalias=i;
		connecteddevices[0]=connecteddevices[i];
		connecteddevices[0].name=RESSTRING(FIRSTJOYSTICK);
		for (int j=usedaxes;--j>10;)
			if (connectedaxes[j].devnum==i)
			{
				connectedaxes[--firstaxes]=connectedaxes[j];
				if (connectedaxes[firstaxes].pairaxisnum!=-1)
					connectedaxes[firstaxes].pairaxisnum=connectedaxes[firstaxes].pairaxisnum-j+firstaxes;
				connectedaxes[firstaxes].devnum=0;
			}
	}
	else
	{
		connecteddevices[0].devid.Data1=0;
		connecteddevices[0].name=RESSTRING(FIRSTJOYSTICK);
		connecteddevices[0].prodname=RESSTRING(NOTCONNECTED);
		connecteddevices[0].numaxes=0;
		connecteddevices[0].numbuttons=0;
		connecteddevices[0].numhats=0;
	}
	DIdev->Release();

	for (i=2;i<useddevices;i++)
		breakif (connecteddevices[i].ismouse);
	if (i<useddevices)	//copy first joystick as default
	{
		mousealias=i;
		connecteddevices[1]=connecteddevices[i];
		connecteddevices[1].name=RESSTRING(FIRSTMOUSE);
		for (int j=usedaxes;--j>=10;)
			if (connectedaxes[j].devnum==i)
			{
				connectedaxes[--firstaxes]=connectedaxes[j];
				if (connectedaxes[firstaxes].pairaxisnum!=-1)
					connectedaxes[firstaxes].pairaxisnum=connectedaxes[firstaxes].pairaxisnum-j+firstaxes;
				connectedaxes[firstaxes].devnum=1;
			}
	}
	else
	{
		connecteddevices[1].devid.Data1=0;
		connecteddevices[1].name=RESSTRING(FIRSTMOUSE);
		connecteddevices[1].prodname=RESSTRING(NOTCONNECTED);
		connecteddevices[1].numaxes=0;
		connecteddevices[1].numbuttons=0;
		connecteddevices[1].numhats=0;
	}
	
	if (useddevices<=4)	//2 reserved general + 2 specific
	{
		useddevices=2;
		usedaxes=middleaxes;
	}
}
/////////////////////////////////////////////////////////////////////////////
// SController dialog
#define OPTIONS	\
	SETFIELD(BIT(flightdifficulty,FD_FF_GUN),			IDC_CBO_FF_GUNRATTLE,RESCOMBO(OFF,2),			NOLEVEL)	\
	SETFIELD(BIT(flightdifficulty,FD_FF_BUFFET),		IDC_CBO_FF_BUFFET,RESCOMBO(OFF,2),				NOLEVEL)	\
	SETFIELD(BIT(flightdifficulty,FD_FF_AERODYNAMIC),	IDC_CBO_FF_AERODYNAMIC,RESCOMBO(OFF,2),			NOLEVEL)	\
	SETFIELD(BIT(flightdifficulty,FD_FF_AIRFRAME),		IDC_CBO_FF_AIRFRAME,RESCOMBO(OFF,2),			NOLEVEL)	\


SController::SController(CWnd* pParent /*=NULL*/)
	: RowanDialog(SController::IDD, pParent)
{
	//{{AFX_DATA_INIT(SController)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SController::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SController)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RSTATICCTRL9,m_IDC_RSTATICCTRL9);
	DDX_Control(pDX,IDC_RSTATICCTRL12,m_IDC_RSTATICCTRL12);
	DDX_Control(pDX,IDC_RSTATICCTRL14,m_IDC_RSTATICCTRL14);
	DDX_Control(pDX,IDC_RSTATICCTRL16,m_IDC_RSTATICCTRL16);
	DDX_Control(pDX,IDC_DEVLIST,m_IDC_DEVLIST);
	DDX_Control(pDX,IDC_STICKDEV,m_IDC_STICKDEV);
	DDX_Control(pDX,IDC_THROTDEV,m_IDC_THROTDEV);
	DDX_Control(pDX,IDC_RUDDEV,m_IDC_RUDDEV);
	DDX_Control(pDX,IDC_PANDEV,m_IDC_PANDEV);
	DDX_Control(pDX,IDC_RSTATICCTRL17,m_IDC_RSTATICCTRL17);
	DDX_Control(pDX,IDC_RSTATICCTRL18,m_IDC_RSTATICCTRL18);
	DDX_Control(pDX,IDC_RSTATICCTRL19,m_IDC_RSTATICCTRL19);
	DDX_Control(pDX,IDC_PITCHDEV,m_IDC_PITCHDEV);
	DDX_Control(pDX,IDC_ZOOMDEV,m_IDC_ZOOMDEV);
	DDX_Control(pDX,IDC_MOUSEDEV,m_IDC_MOUSEDEV);
	DDX_Control(pDX,IDC_DEVDESC,m_IDC_DEVDESC);
	DDX_Control(pDX,IDC_CALIB,m_IDC_CALIB);
	DDX_Control(pDX,IDC_SUPPFF,m_IDC_SUPPFF);
	DDX_Control(pDX,IDC_SELFF,m_IDC_SELFF);
	DDX_Control(pDX,IDC_SUPPFF2,m_IDC_SUPPFF2);
	DDX_Control(pDX,IDC_SELPOLL,m_IDC_SELPOLL);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_RSTATICCTRL8,m_IDC_RSTATICCTRL8);
	DDX_Control(pDX,IDC_RSTATICCTRL46,m_IDC_RSTATICCTRL46);
	DDX_Control(pDX,IDC_CBO_FF_GUNRATTLE,m_IDC_CBO_FF_GUNRATTLE);
	DDX_Control(pDX,IDC_CBO_FF_STALL,m_IDC_CBO_FF_STALL);
	DDX_Control(pDX,IDC_CBO_FF_HIGHSPEED,m_IDC_CBO_FF_HIGHSPEED);
	DDX_Control(pDX,IDC_CBO_FF_AIRFRAME,m_IDC_CBO_FF_AIRFRAME);
	DDX_Control(pDX,IDC_CBO_CONTROLCOLDEADZONE,m_IDC_CBO_CONTROLCOLDEADZONE);
	DDX_Control(pDX,IDC_CBO_RUDDERDEADZONE,m_IDC_CBO_RUDDERDEADZONE);
	//}}AFX_DATA_MAP
#define	SG2C_DISPLAY setlevel
#include "sg2combo.h"
	OPTIONS	
	m_IDC_DEVLIST.SetCircularStyle(TRUE);
	m_IDC_STICKDEV.SetCircularStyle(TRUE);
	m_IDC_THROTDEV.SetCircularStyle(TRUE);
	m_IDC_RUDDEV.SetCircularStyle(TRUE);
	m_IDC_PANDEV.SetCircularStyle(TRUE);
	m_IDC_PITCHDEV.SetCircularStyle(TRUE);
	m_IDC_ZOOMDEV.SetCircularStyle(TRUE);
	m_IDC_MOUSEDEV.SetCircularStyle(TRUE);
	m_IDC_CBO_FF_GUNRATTLE.SetCircularStyle(TRUE);
	m_IDC_CBO_FF_STALL.SetCircularStyle(TRUE);
	m_IDC_CBO_FF_HIGHSPEED.SetCircularStyle(TRUE);
	m_IDC_CBO_FF_AIRFRAME.SetCircularStyle(TRUE);
	m_IDC_CBO_CONTROLCOLDEADZONE.SetCircularStyle(TRUE);
	m_IDC_CBO_RUDDERDEADZONE.SetCircularStyle(TRUE);

	AfxGetMainWnd()->ModifyStyleEx(WS_EX_TOPMOST,0);
	AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);

	AfxGetMainWnd()->ModifyStyleEx(WS_EX_TOPMOST,0);
	AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);

	CREdtBt*	calib=GETDLGITEM(IDC_CALIB);
	calib->SetCaption(RESSTRING(CALIBRATE));
	BuildEnumerationTables();
	GetAxisConfig();
	RemakeDisplay();
}

void SController::PreDestroyPanel()
{
#define	SG2C_WRITEBACK setlevel
#include "sg2combo.h"
	OPTIONS	
	SetAxisConfig();

	AfxGetMainWnd()->ModifyStyleEx(0,WS_EX_TOPMOST);
	AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
}
#define SG2C_CLEANUP
#include "sg2combo.h"

BEGIN_MESSAGE_MAP(SController, CDialog)
	//{{AFX_MSG_MAP(SController)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(SController, CDialog)
    //{{AFX_EVENTSINK_MAP(SController)
	ON_EVENT(SController, IDC_CALIB, 1 /* Clicked */, OnClickedCalib, VTS_NONE)
	ON_EVENT(SController, IDC_DEVLIST, 1 /* TextChanged */, OnTextChangedDevlist, VTS_BSTR)
	ON_EVENT(SController, IDC_MOUSEDEV, 1 /* TextChanged */, OnTextChangedMousedev, VTS_BSTR)
	ON_EVENT(SController, IDC_PANDEV, 1 /* TextChanged */, OnTextChangedPandev, VTS_BSTR)
	ON_EVENT(SController, IDC_PITCHDEV, 1 /* TextChanged */, OnTextChangedPitchdev, VTS_BSTR)
	ON_EVENT(SController, IDC_RUDDEV, 1 /* TextChanged */, OnTextChangedRuddev, VTS_BSTR)
	ON_EVENT(SController, IDC_SELFF, 1 /* Clicked */, OnClickedSelff, VTS_NONE)
	ON_EVENT(SController, IDC_SELPOLL, 1 /* Clicked */, OnClickedSelpoll, VTS_NONE)
	ON_EVENT(SController, IDC_STICKDEV, 1 /* TextChanged */, OnTextChangedStickdev, VTS_BSTR)
	ON_EVENT(SController, IDC_THROTDEV, 1 /* TextChanged */, OnTextChangedThrotdev, VTS_BSTR)
	ON_EVENT(SController, IDC_ZOOMDEV, 1 /* TextChanged */, OnTextChangedZoomdev, VTS_BSTR)
	ON_EVENT(SController, IDC_CBO_CONTROLCOLDEADZONE, 1 /* TextChanged */, OnTextChangedCboControlcoldeadzone, VTS_BSTR)
	ON_EVENT(SController, IDC_CBO_RUDDERDEADZONE, 1 /* TextChanged */, OnTextChangedCboRudderdeadzone, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////

void	SController::GetAxisConfig(bool setff)	//convert runtime device list to ui axis list
{
	bool donesome=false;
	for (int rtdev=0;_Analogue.runtimedevices[rtdev].devid.Data1;rtdev++)
	{
		int setdev=0;
		if (_Analogue.runtimedevices[rtdev].devid.Data1==1)
			setdev=0;
		else
		if (_Analogue.runtimedevices[rtdev].devid.Data1==2)
			setdev=1;
		else
		for (setdev=2;setdev<useddevices;setdev++)
			breakif(connecteddevices[setdev].devid==_Analogue.runtimedevices[rtdev].devid);

		if (setdev<useddevices)
		{
			donesome=true;
			connecteddevices[setdev].enablepoll=true;
			connecteddevices[setdev].useff=_Analogue.runtimedevices[rtdev].useff;
			int ra=0;
			int rh=0;
			for (int va=firstaxes;va<usedaxes;va++)
				if (connectedaxes[va].devnum==setdev)
				{
					if (connectedaxes[va].ishat)
						connectedaxes[va].assignedtask=(AxisUses)_Analogue.runtimedevices[rtdev].hatmaps[rh++];
					else
						connectedaxes[va].assignedtask=(AxisUses)_Analogue.runtimedevices[rtdev].axismaps[ra++];
				}
		}
	}
	if (!donesome)
	{								//ASSUME default stick is 
		if (connecteddevices[0].supportsff && setff)
			connecteddevices[0].useff=true;
		int ra=0;
		int rh=0;	connecteddevices[0].enablepoll=true;
		int rm=0;	connecteddevices[1].enablepoll=true;
		bool donestick=false,donethr=false,doneped=false;
		for (int va=firstaxes;va<usedaxes;va++)
			if (connectedaxes[va].devnum==0)
				if (connectedaxes[va].ishat)
					;////	{if (!rh++)	connectedaxes[va].assignedtask=AU_VIEWH;}
				else
				{
					if (connectedaxes[va].assignedtask==AU_UNASSIGNED)
						if (connectedaxes[va].firstofpair && !donestick)
						{
							connectedaxes[va].assignedtask=AU_AILERON;
							connectedaxes[connectedaxes[va].pairaxisnum].assignedtask=AU_ELEVATOR;
							donestick=true;
						}
						else
						if (connectedaxes[va].xtype && !doneped)
						{
							connectedaxes[va].assignedtask=AU_RUDDER;
							doneped=true;
						}
						else
						if (!donethr)
						{
							connectedaxes[va].assignedtask=AU_THROTTLE;
							donethr=true;
						}
				}
			else
				if (connectedaxes[va].devnum==1)
					if (!connectedaxes[va].ishat)
						if (connectedaxes[va].firstofpair)
						{
							connectedaxes[va].assignedtask=AU_UI_X;
							connectedaxes[connectedaxes[va].pairaxisnum].assignedtask=AU_UI_Y;
						}
	}
}
void	SController::SetAxisConfig()	//set runtime device config from ui axis list
{
	int rtdev=0;
	for (int setdev=0;setdev<useddevices;setdev++)
	{
		if (connecteddevices[setdev].enablepoll && connecteddevices[setdev].devid.Data1)
		{
			if (setdev==0)
				_Analogue.runtimedevices[rtdev].devid.Data1=1;
			else
			if (setdev==1)
				_Analogue.runtimedevices[rtdev].devid.Data1=2;
			else
				_Analogue.runtimedevices[rtdev].devid=connecteddevices[setdev].devid;
			_Analogue.runtimedevices[rtdev].useff=connecteddevices[setdev].useff;
			_Analogue.runtimedevices[rtdev].ismouse=connecteddevices[setdev].ismouse;
			int ra=0;
			int rh=0;
			for (int va=firstaxes;va<usedaxes;va++)
				if (connectedaxes[va].devnum==setdev)
					if (connectedaxes[va].ishat)
						_Analogue.runtimedevices[rtdev].hatmaps[rh++]=connectedaxes[va].assignedtask;
					else
						_Analogue.runtimedevices[rtdev].axismaps[ra++]=connectedaxes[va].assignedtask;
			while (rh<RunTimeDevDesc::MAXMAPS)
				_Analogue.runtimedevices[rtdev].hatmaps[rh++]=AU_UNASSIGNED;
			while (ra<RunTimeDevDesc::MAXMAPS)
				_Analogue.runtimedevices[rtdev].axismaps[ra++]=AU_UNASSIGNED;
			rtdev++;
		}
	}
	_Analogue.runtimedevices[rtdev].devid.Data1=0;
}


void	SController::RemakeDisplay()
{
	CRCombo* combo=GETDLGITEM(IDC_DEVLIST);
	int	index=combo->GetIndex();
	if (index==-1) index=0;
	combo->Clear();
	for (int i=0;i<useddevices;i++)
		combo->AddString(CSprintf("%s: %s",connecteddevices[i].name,connecteddevices[i].prodname));	
	combo->SetIndex(index);
	CRStatic* desc=GETDLGITEM(IDC_DEVDESC);
	desc->SetString(CSprintf("%i %s, %i %s, %i %s",
						connecteddevices[index].numaxes,RESSTRING(JOYAXES),
						connecteddevices[index].numhats,RESSTRING(COOLIEHATS),
						connecteddevices[index].numbuttons,RESSTRING(BUTTONS)	));
	CRButton* button=GETDLGITEM(IDC_SELPOLL);
	button->SetPressed(connecteddevices[index].enablepoll);
	button=GETDLGITEM(IDC_SELFF);
	desc=GETDLGITEM(IDC_SUPPFF);
	desc->SetString(RESSTRING(USEFFOUT));
	if (connecteddevices[index].supportsff)
	{
		desc->SetForeColor(RGB(255,255,0));

		button->SetDisabled(FALSE);
		button->SetPressed(connecteddevices[index].useff);
	}
	else
	{
		desc->SetForeColor(RGB(80,80,80));
		button->SetPressed(FALSE);
		button->SetDisabled(TRUE);
	}
	RemakeAxes();
}
void	SController::RemakeAxes()
{
	SetAxesCombo(m_IDC_STICKDEV,AU_AILERON,true,true,true);
	SetAxesCombo(m_IDC_THROTDEV,AU_THROTTLE,false,true,false);
	SetAxesCombo(m_IDC_RUDDEV,AU_RUDDER,false,true,false);	  //was true,true,false //DAW 15/02/00
	if (SetAxesCombo(m_IDC_PANDEV,AU_VIEWH,true,false,false))
	{
		CRCombo* h=GETDLGITEM(IDC_PANDEV);
		CRCombo* p=GETDLGITEM(IDC_PITCHDEV);
		p->Clear();
		p->SetCaption(h->GetCaption());
			
	}
	else
		SetAxesCombo(m_IDC_PITCHDEV,AU_VIEWP,false,true,false);
	SetAxesCombo(m_IDC_ZOOMDEV,AU_VIEWZ,false,true,false);
	SetAxesCombo(m_IDC_MOUSEDEV,AU_UI_X,true,false,true);
}

int	SController::ChangedAxesCombo(CRCombo& m_ID,AxisUses task,bool xonly,bool analogonly,bool paironly)
{
	int newindex;
	{
		CRCombo* combo=GETDLGITEM(ID);
		newindex=combo->GetIndex();
		combo->Clear();
	}
	int currindex=1;
	int selindex=-1;
	for (int i=firstaxes;i<usedaxes;i++)
	{
		if (connectedaxes[i].assignedtask==task)
			connectedaxes[i].assignedtask=AU_UNASSIGNED;
		if (!connecteddevices[connectedaxes[i].devnum].enablepoll)
			continue;
		if (xonly && !connectedaxes[i].xtype)
			continue;
		if (analogonly && connectedaxes[i].ishat)
			continue;
		if (paironly && !connectedaxes[i].firstofpair)
			continue;
		if (connectedaxes[i].assignedtask!=AU_UNASSIGNED)
				continue;
		if (newindex==currindex)
		{
			connectedaxes[i].assignedtask=task;
			selindex=i;
		}
		currindex++;
	}
	return selindex;

}

void	SController::ChangedAxesSecondValue(int newind,AxisUses task)
{
	if (newind!=-1)
		ChangedAxesValue(connectedaxes[newind].pairaxisnum,task);
	else
		ChangedAxesValue(newind,task);

}
void	SController::ChangedAxesValue(int newind,AxisUses task)
{
	for (int i=firstaxes;i<usedaxes;i++)
	{
		if (connectedaxes[i].assignedtask==task)
			connectedaxes[i].assignedtask=AU_UNASSIGNED;
	}
	if (newind>=0)
		connectedaxes[newind].assignedtask=task;
}

bool	SController::SetAxesCombo(CRCombo& m_ID,AxisUses task,bool xonly,bool analogonly,bool paironly)
{
	CRCombo* combo=GETDLGITEM(ID);
	combo->Clear();
	combo->AddString(RESSTRING(KEYBOARD));
	int currindex=1;
	int selindex=0;
	bool	rv=false;
	for (int i=firstaxes;i<usedaxes;i++)
	{
		if (!connecteddevices[connectedaxes[i].devnum].enablepoll)
			continue;
		if (xonly && !connectedaxes[i].xtype)
			continue;
		if (analogonly && connectedaxes[i].ishat)
			continue;
		if (paironly && !connectedaxes[i].firstofpair)
			continue;
		if (connectedaxes[i].assignedtask!=AU_UNASSIGNED)
			if (connectedaxes[i].assignedtask!=task)
				continue;
			else
			{
				rv=connectedaxes[i].ishat;
				selindex=currindex;
			}
		if (paironly && !connectedaxes[i].ishat)
			combo->AddString(CSprintf("%s: %s & %s",
									connecteddevices[connectedaxes[i].devnum].name,
									connectedaxes[i].name,connectedaxes[i+1].name));
		else
			combo->AddString(CSprintf("%s: %s",
									connecteddevices[connectedaxes[i].devnum].name,
									connectedaxes[i].name			));
		currindex++;
	}
	combo->SetIndex(selindex);
	return rv;
}
/////////////////////////////////////////////////////////////////////////////
// SController message handlers
void SController::OnClickedCalib() 
{
	// TODO: Add your control notification handler code here
	CRCombo* combo=GETDLGITEM(IDC_DEVLIST);
	int	index=combo->GetIndex();
	LPDIRECTINPUTDEVICE dev;
	LPDIRECTINPUT	DIdev;
	DirectInputCreate(AfxGetInstanceHandle( ),DIRECTINPUT_VERSION,&DIdev,NULL);
	if (connecteddevices[index].devid.Data1)
	{
		if (SUCCEEDED(DIdev->CreateDevice(connecteddevices[index].devid,&dev,NULL)))
		{
			dev->RunControlPanel(Master_3d.winst,0);
//OLD_CODE			dev->RunControlPanel(m_hWnd,0);
			dev->Release();
		}
		else
			DIdev->RunControlPanel(Master_3d.winst,0);
//OLD_CODE			DIdev->RunControlPanel(m_hWnd,0);
	}
	else
		DIdev->RunControlPanel(Master_3d.winst,0);
//OLD_CODE		DIdev->RunControlPanel(m_hWnd,0);
	DIdev->Release();
	SetAxisConfig();
	BuildEnumerationTables();
	GetAxisConfig();
	RemakeDisplay();
}

//void SController::OnClickedCalib2() 
//{
//	// TODO: Add your control notification handler code here
//	_Analogue.DIdev->RunControlPanel(m_hWnd,0);
//	SetAxisConfig();
//	BuildEnumerationTables();
//	GetAxisConfig();
//	RemakeDisplay();
//
//}

void SController::OnTextChangedDevlist(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	SetAxisConfig();
	BuildEnumerationTables();
	GetAxisConfig();
	RemakeDisplay();

	
}

void SController::OnClickedSelff() 
{
	// TODO: Add your control notification handler code here
	CRCombo* combo=GETDLGITEM(IDC_DEVLIST);
	int	index=combo->GetIndex();
	CRButton* button=GETDLGITEM(IDC_SELFF);
	if (connecteddevices[index].supportsff && connecteddevices[index].enablepoll)
	{
		connecteddevices[index].useff=(connecteddevices[index].useff==false);
//		connecteddevices[index].enablepoll=true;
//		button->SetPressed(true);
	}	
	else
		button->SetPressed(false);

	int i;



}

void SController::OnClickedSelpoll() 
{
	// TODO: Add your control notification handler code here
	CRCombo* combo=GETDLGITEM(IDC_DEVLIST);
	int	index=combo->GetIndex();
	CRButton* button=GETDLGITEM(IDC_SELPOLL);
	bool	nowset=button->GetPressed()!=0;
	int i;
	for (i=firstaxes;i<usedaxes;i++)
		breakif(connectedaxes[i].devnum==index && connectedaxes[i].assignedtask!=AU_UNASSIGNED);
	int altind=-1;
	if (nowset && i==usedaxes)
		if (index==0)
			altind=joystickalias;
		elseif (index==1)
			altind=mousealias;
		elseif (index==joystickalias)
			altind=0;
		elseif (index==mousealias)
			altind=1;
	if (altind!=-1)
	{	//disable the other version of this stick...
		connecteddevices[altind].enablepoll=false;
		connecteddevices[index].useff=connecteddevices[altind].useff;

		connecteddevices[altind].useff=false;

		GETDLGITEM(IDC_SELFF)->SetPressed(connecteddevices[index].useff);

		for (int i=firstaxes;i<usedaxes;i++)
			if (connectedaxes[i].devnum==altind && connectedaxes[i].assignedtask!=AU_UNASSIGNED)
			{
				int j;
				for (j=firstaxes;j<usedaxes;j++)
					breakif (	connectedaxes[j].devnum==index 
						&&	connectedaxes[j].axisnum==connectedaxes[i].axisnum
						&&	connectedaxes[j].ishat==connectedaxes[i].ishat	);
				
				connectedaxes[j].assignedtask=connectedaxes[i].assignedtask;
				connectedaxes[i].assignedtask=AU_UNASSIGNED;
			}

	}
	if (i<usedaxes)
		button->SetPressed(true);
	else
	{
		connecteddevices[index].enablepoll=nowset;			
		RemakeAxes();
	}
}


void SController::OnTextChangedMousedev(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	int newaxis=ChangedAxesCombo(m_IDC_MOUSEDEV,AU_UI_X,true,false,true);
	if (newaxis>=0 && !connectedaxes[newaxis].ishat)
	{
		ChangedAxesSecondValue(newaxis,AU_UI_Y);
	}
	else
		ChangedAxesValue(-1,AU_UI_Y);

	RemakeAxes();
	SetEnabled(newaxis);
}

void	SController::SetEnabled(int newaxis)
{
	CRCombo* combo=GETDLGITEM(IDC_DEVLIST);
	int	index=combo->GetIndex();
	if (newaxis>=0 && index==connectedaxes[newaxis].devnum && !connecteddevices[index].enablepoll)
	{
		CRButton* button=GETDLGITEM(IDC_SELPOLL);
		button->SetPressed(true);
		connecteddevices[index].enablepoll=true;
	}
}
void SController::OnTextChangedPandev(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	int newaxis=ChangedAxesCombo(m_IDC_PANDEV,AU_VIEWH,true,false,false);
	if (connectedaxes[newaxis].firstofpair)
		if (connectedaxes[newaxis].ishat)
			ChangedAxesValue(-1,AU_VIEWP);
		else
		{
			ChangedAxesSecondValue(newaxis,AU_VIEWP);
		}
	RemakeAxes();
	SetEnabled(newaxis);
}

void SController::OnTextChangedPitchdev(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	int newaxis=ChangedAxesCombo(m_IDC_PITCHDEV,AU_VIEWP,false,false,false);	
	SetEnabled(newaxis);
	RemakeAxes();
}

void SController::OnTextChangedRuddev(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	int newaxis=ChangedAxesCombo(m_IDC_RUDDEV,AU_RUDDER,false,true,false);	  //was true,true,false //DAW 15/02/00
	SetEnabled(newaxis);
	RemakeAxes();
}


void SController::OnTextChangedStickdev(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	int newaxis=ChangedAxesCombo(m_IDC_STICKDEV,AU_AILERON,true,true,true);	
	ChangedAxesSecondValue(newaxis,AU_ELEVATOR);
	SetEnabled(newaxis);
	RemakeAxes();
}

void SController::OnTextChangedThrotdev(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	int newaxis=ChangedAxesCombo(m_IDC_THROTDEV,AU_THROTTLE,false,true,false);	
	SetEnabled(newaxis);
	RemakeAxes();
}

void SController::OnTextChangedZoomdev(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	int newaxis=ChangedAxesCombo(m_IDC_ZOOMDEV,AU_VIEWZ,false,true,false);	
	SetEnabled(newaxis);
	RemakeAxes();
}

void SController::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==ControlsPref_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}

	CDialog::OnTimer(nIDEvent);
}

void SController::OnDestroy() 
{
	KillTimer(ControlsPref_Timer);

	CDialog::OnDestroy();

}

void SController::OnTextChangedCboControlcoldeadzone(LPCTSTR text) 
{
  	CRCombo* combo;
	combo=GETDLGITEM(IDC_CBO_CONTROLCOLDEADZONE);
	int index = combo->GetIndex();	

	switch (index)
	{
		case 0:	
		{
			_Analogue.deadzones[AU_AILERON] = DZ_SMALL;
			_Analogue.deadzones[AU_ELEVATOR] = DZ_SMALL;
			break;
		}
		case 1:	
		{
			_Analogue.deadzones[AU_AILERON] = DZ_MEDIUM;
			_Analogue.deadzones[AU_ELEVATOR] = DZ_MEDIUM;
			break;
		}
		case 2:	
		{
			_Analogue.deadzones[AU_AILERON] = DZ_LARGE;
			_Analogue.deadzones[AU_ELEVATOR] = DZ_LARGE;
			break;
		}
	}
	
}

void SController::OnTextChangedCboRudderdeadzone(LPCTSTR text) 
{
  	CRCombo* combo;
	combo=GETDLGITEM(IDC_CBO_RUDDERDEADZONE);
	int index = combo->GetIndex();	

	switch (index)
	{
		case 0:	
		{
			_Analogue.deadzones[AU_RUDDER] = DZ_SMALL;
			break;
		}
		case 1:	
		{
			_Analogue.deadzones[AU_RUDDER] = DZ_MEDIUM;
			break;
		}
		case 2:	
		{
			_Analogue.deadzones[AU_RUDDER] = DZ_LARGE;
			break;
		}
	}
}

//DeadCode DAW 22Dec98 BOOL SController::OnInitDialog() 
//DeadCode DAW 22Dec98 {
//DeadCode DAW 22Dec98 	CDialog::OnInitDialog();
//DeadCode DAW 22Dec98 
//DeadCode DAW 22Dec98 	ControlsPref_Timer=SetTimer(TIMER_PREFSCONTROLS,0,NULL);
//DeadCode DAW 22Dec98 	
//DeadCode DAW 22Dec98 	// TODO: Add extra initialization here
//DeadCode DAW 22Dec98 	
//DeadCode DAW 22Dec98 	return TRUE;  // return TRUE unless you set the focus to a control
//DeadCode DAW 22Dec98 	              // EXCEPTION: OCX Property Pages should return FALSE
//DeadCode DAW 22Dec98 }

BOOL SController::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRCombo* combo;
	
	if (_DPlay.PlayerCreated)									//AMM 12Jul99
	{															//AMM 12Jul99
		_DPlay.UISendInPrefsMessage();							//AMM 12Jul99
		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_PREFS;		//AMM 12Jul99
	}															//AMM 12Jul99

	ControlsPref_Timer=SetTimer(TIMER_PREFSCONTROLS,0,NULL);	//AMM 12Jul99

	int index;
	if (_Analogue.deadzones[AU_RUDDER] == DZ_SMALL)
		index = 0;
	else if (_Analogue.deadzones[AU_RUDDER] == DZ_MEDIUM)
		index = 1;
	else 
		index = 2;
	combo=GETDLGITEM(IDC_CBO_RUDDERDEADZONE);
	combo->RESCOMBO(SMALL,3)->SetIndex(index);

	if (_Analogue.deadzones[AU_AILERON] == DZ_SMALL)
		index = 0;
	else if (_Analogue.deadzones[AU_AILERON] == DZ_MEDIUM)
		index = 1;
	else 
		index = 2;
	combo=GETDLGITEM(IDC_CBO_CONTROLCOLDEADZONE);
	combo->RESCOMBO(SMALL,3)->SetIndex(index);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
