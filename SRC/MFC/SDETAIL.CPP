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

// SDetaimfc\l.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SDetail.h"
#include "rcombo.h"
#include "savegame.h"
#include "display.h"
#include "overlay.h"
#include "gameset.h"
extern void GetDrivers(int&,char**&);
extern void GetModes(int&,SDrvrModes*&);

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDetail dialog


CSDetail::CSDetail(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSDetail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSDetail)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSDetail)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL5,m_IDC_RSTATICCTRL5);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_RSTATICCTRL8,m_IDC_RSTATICCTRL8);
	DDX_Control(pDX,IDC_RSTATICCTRL9,m_IDC_RSTATICCTRL9);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_RSTATICCTRL12,m_IDC_RSTATICCTRL12);
	DDX_Control(pDX,IDC_CBO_DISPLAYDRIVERS,m_IDC_CBO_DISPLAYDRIVERS);
	DDX_Control(pDX,IDC_CBO_RESOLUTIONS,m_IDC_CBO_RESOLUTIONS);
	DDX_Control(pDX,IDC_CBO_AUTOFRAMERATE,m_IDC_CBO_AUTOFRAMERATE);
	DDX_Control(pDX,IDC_CBO_LOWESTFRAMERATE,m_IDC_CBO_LOWESTFRAMERATE);
	DDX_Control(pDX,IDC_CBO_DISPLAYDRIVERS,m_IDC_CBO_DISPLAYDRIVERS);
	DDX_Control(pDX,IDC_CBO_RESOLUTIONS,m_IDC_CBO_RESOLUTIONS);
	DDX_Control(pDX,IDC_CBO_GAMMACORRECTION,m_IDC_CBO_GAMMACORRECTION);
	DDX_Control(pDX,IDC_CBO_GROUNDSHADING,m_IDC_CBO_GROUNDSHADING);
	DDX_Control(pDX,IDC_CBO_ITEMSHADING,m_IDC_CBO_ITEMSHADING);
//DEADCODE RDH 15/02/99 	DDX_Control(pDX,IDC_CBO_SHOWIRONWORK,m_IDC_CBO_SHOWIRONWORK);
	DDX_Control(pDX,IDC_CBO_REFLECTIONS,m_IDC_CBO_REFLECTIONS);
	DDX_Control(pDX,IDC_RSTATICCTRL48,m_IDC_RSTATICCTRL48);
	DDX_Control(pDX,IDC_CBO_WEATHER,m_IDC_CBO_WEATHER);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSDetail, CDialog)
	//{{AFX_MSG_MAP(CSDetail)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDetail message handlers	  //IDS_L_DIST_NEAR

#define OPTIONS	\
	SETFIELD(CHAR(gammacorrection,0,1),				IDC_CBO_GAMMACORRECTION,RESCOMBO(BLMHT_BOT,5),NOLEVEL)	\
	SETFIELD(ADDBIT(detail_3d,DETAIL3D_AUTODETAIL,DETAIL3D_FASTFRAME),									\
													IDC_CBO_AUTOFRAMERATE,RESCOMBO(OFF,3),	NOLEVEL)	\
	SETFIELD(CHAR(desiredfps,5,1),					IDC_CBO_LOWESTFRAMERATE,MakeNumList(30,5),NOLEVEL)	\
	SETFIELD(BIT(detail_3d,DETAIL3D_GROUNDSHADING),	IDC_CBO_GROUNDSHADING,RESCOMBO(OFF,2),	NOLEVEL)	\
	SETFIELD(BIT(detail_3d,DETAIL3D_ITEMSHADING),	IDC_CBO_ITEMSHADING,RESCOMBO(OFF,2),	NOLEVEL)	\
	SETFIELD(BIT(cockpit3Ddetail,COCK3D_SKYIMAGES),	IDC_CBO_REFLECTIONS,RESCOMBO(OFF,2),	NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_WEATHEREFFECTS),	IDC_CBO_WEATHER,RESCOMBO(OFF,2),		NOLEVEL)	\

int	ironlevels;

inline bool IsValidMode(SModeFlags* pmf,UWord w,UWord h)
{
	if (w*3!=h*4) return false;
	for (int x=0;x<SModeFlags::Max_Modes;x++) if (pmf->widths[x]==w) return true;
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnInitDialog
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
BOOL CSDetail::OnInitDialog()
{
	static char modeString[32];

#define	SG2C_DISPLAY	setlevel
#include "sg2combo.h"
	
	CDialog::OnInitDialog();

	if (_DPlay.PlayerCreated)									//AMM 12Jul99
	{															//AMM 12Jul99
		_DPlay.UISendInPrefsMessage();							//AMM 12Jul99
		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_PREFS;		//AMM 12Jul99
	}															//AMM 12Jul99

	if (RFullPanelDial::gamestate!=RFullPanelDial::TITLE)		//AMM 31Mar99
		_Replay.prefscheck=true;								//AMM 31Mar99
	
	if (Save_Data.desiredfps<5) Save_Data.desiredfps=20;

	//fill in display drivers field

	int driverCount,modesCount,selectedDriver,driver_index;
	char** driverNames;
	SDrvrModes* driverModes;
	GetDrivers(driverCount,driverNames);
	GetModes(modesCount,driverModes);

	CString pdd;
	CRCombo* combo=GETDLGITEM(IDC_CBO_DISPLAYDRIVERS);

	//the first entry must always be the 'Software Display Driver'
	pdd.LoadString(IDS_SOFTWAREDRIVER);
	combo->AddString(pdd);

	//the second entry must always be 'Primary Display Driver' if it is 3D capeable
	if (!Save_Data.fNoHardwareAtAll && Save_Data.sd.fFirstHardIsPrimary)
	{
		pdd.LoadString(IDS_PRIMARYDISPLAYDRIVER);
		combo->AddString(pdd);
	}

	//driver count doesn't include primary!

	for (SLong x=0;x<driverCount;x++) 
		combo->AddString(driverNames[x]);

	if (Save_Data.fSoftware)					selectedDriver=0;
	else if (Save_Data.sd.fFirstHardIsPrimary)	selectedDriver=Save_Data.dddriver+2; //-1 to ... => 1 to ...+2
	else 										selectedDriver=Save_Data.dddriver+1; // 0 to ... => 1 to ...+1

	driver_index=Save_Data.dddriver;
//	if (Save_Data.fNoHardwareAtAll)
//		driver_index--;

	combo->SetIndex(selectedDriver);
	combo=GETDLGITEM(IDC_CBO_RESOLUTIONS);

	SModeFlags* modeFlags;

	if (Save_Data.fSoftware)					modeFlags=&Save_Data.sd.soft_modes;
	else if (Save_Data.sd.fFirstHardIsPrimary)	modeFlags=Save_Data.sd.hard_modes+selectedDriver-1;
	else										modeFlags=Save_Data.sd.hard_modes+selectedDriver;

	SLong rez_index=0,add_index=0;

	for (x=0;x<modesCount;x++)
		if (driverModes[x].driverNo-1==driver_index &&
			driverModes[x].displayBPP==16 &&
			IsValidMode(modeFlags,driverModes[x].displayWidth,driverModes[x].displayHeight))
		{
		 	if (Save_Data.screenresolution==add_index)	rez_index=add_index;
			sprintf(modeString,"%d X %d\0",driverModes[x].displayWidth,driverModes[x].displayHeight);
			combo->AddString(CString(modeString));
			add_index++;
		}

	combo->SetIndex(rez_index);

	OPTIONS
	ThreeDeePref_Timer=SetTimer(TIMER_PREFS3D,0,NULL);
	m_IDC_CBO_DISPLAYDRIVERS.SetCircularStyle(TRUE);
	m_IDC_CBO_RESOLUTIONS.SetCircularStyle(TRUE);
	m_IDC_CBO_GAMMACORRECTION.SetCircularStyle(TRUE);
	m_IDC_CBO_AUTOFRAMERATE.SetCircularStyle(TRUE);
	m_IDC_CBO_LOWESTFRAMERATE.SetCircularStyle(TRUE);
	m_IDC_CBO_GROUNDSHADING.SetCircularStyle(TRUE);
	m_IDC_CBO_ITEMSHADING.SetCircularStyle(TRUE);
	m_IDC_CBO_REFLECTIONS.SetCircularStyle(TRUE);
	m_IDC_CBO_WEATHER.SetCircularStyle(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


#define	SG2C_WRITEBACK
#include "sg2combo.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnClose
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void CSDetail::OnClose()
{
	OPTIONS	
	CDialog::OnClose();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnDestroy
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void CSDetail::OnDestroy()
{
	KillTimer(ThreeDeePref_Timer);
	CDialog::OnDestroy();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreDestroyPanel
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void CSDetail::PreDestroyPanel()
{
	SDrvrModes* driverModes;
	char** driverNames;
	int curMode,selectedMode,selectedDriver;
	int modesCount,driverCount;

	GetDrivers(driverCount,driverNames);
	GetModes(modesCount,driverModes);

	OPTIONS

	CRCombo* combo=GETDLGITEM(IDC_CBO_DISPLAYDRIVERS);
	selectedDriver=combo->GetIndex();

	if (selectedDriver==0)	Save_Data.fSoftware=true;
	else
	{
		Save_Data.fSoftware=false;
		if (Save_Data.sd.fFirstHardIsPrimary)	selectedDriver--;
	}
	selectedDriver--;
	Save_Data.dddriver=selectedDriver;

	combo=GETDLGITEM(IDC_CBO_RESOLUTIONS);
	selectedMode=combo->GetIndex();

	SModeFlags* modeFlags;

	if (Save_Data.fSoftware)	modeFlags=&Save_Data.sd.soft_modes;
	else						modeFlags=Save_Data.sd.hard_modes+selectedDriver+1;

	Save_Data.screenresolution=selectedMode;

	curMode=0;

	for (SLong x=0;x<modesCount;x++)
	{
		if (driverModes[x].driverNo-1==selectedDriver &&
			driverModes[x].displayBPP==16 &&
			IsValidMode(modeFlags,driverModes[x].displayWidth,driverModes[x].displayHeight))
		{
			if (curMode==selectedMode)
			{
				Save_Data.displayW=driverModes[x].displayWidth;
				Save_Data.displayH=driverModes[x].displayHeight;
				break;
			}
			else curMode++;
		}
	}

	if (Save_Data.fSoftware)
	{
		Save_Data.textureQuality=4;
		Save_Data.filtering=0;
		Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
		Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;
		Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
		Save_Data.gamedifficulty%=GD_GEFFECTS;
		Save_Data.gamedifficulty%=GD_INJURYEFFECTS;
		Save_Data.gamedifficulty%=GD_WHITEOUT;
	}
//	else
//	{
//		Save_Data.filtering=1;
//		Save_Data.detail_3d|=DETAIL3D_GROUNDSHADING;
//		Save_Data.gamedifficulty|=GD_GEFFECTS;
//		Save_Data.gamedifficulty|=GD_INJURYEFFECTS;
//	}
}

#define SG2C_CLEANUP
#include "sg2combo.h"

void CSDetail::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==ThreeDeePref_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	
	CDialog::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CSDetail, CDialog)
    //{{AFX_EVENTSINK_MAP(CSDetail)
	ON_EVENT(CSDetail, IDC_CBO_DISPLAYDRIVERS, 1 /* TextChanged */, OnTextChangedCboDisplaydrivers, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnTextChangedCboDisplaydrivers
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void CSDetail::OnTextChangedCboDisplaydrivers(LPCTSTR text)
{
	static char modeString[32];
	int selectedDriver,modesCount;
	SDrvrModes* driverModes;

	GetModes(modesCount,driverModes);
	CRCombo* combo=GETDLGITEM(IDC_CBO_DISPLAYDRIVERS);
	selectedDriver=combo->GetIndex();

	//if Save_Data.sd.fFirstHardIsPrimary then 
	//	selectedDriver==0	for software				=>-1
	//	selectedDriver==1	for primary hardware		=>-1
	//	selectedDriver==2	for secondary hardware		=>0
	//else
	//	selectedDriver==0	for software				=>-1
	//	selectedDriver==1	for secondary hardware		=>0
	if (selectedDriver==0)	Save_Data.fSoftware=true;
	else					Save_Data.fSoftware=false;

	if (Save_Data.sd.fFirstHardIsPrimary)	selectedDriver=selectedDriver==0?-1:selectedDriver-2;
	else									selectedDriver--;

	SModeFlags* modeFlags;

	if (Save_Data.fSoftware)	modeFlags=&Save_Data.sd.soft_modes;
	else						modeFlags=Save_Data.sd.hard_modes+selectedDriver+1;
//dead	else						modeFlags=Save_Data.sd.hard_modes+selectedDriver+1;

	//erase the current list of resolutions

	combo=GETDLGITEM(IDC_CBO_RESOLUTIONS);
	combo->Clear();

	for (SLong x=0;x<modesCount;x++)
		if (driverModes[x].driverNo-1==selectedDriver &&
			driverModes[x].displayBPP==16 &&
			IsValidMode(modeFlags,driverModes[x].displayWidth,driverModes[x].displayHeight))
		{
			sprintf(modeString,"%d X %d\0",
					driverModes[x].displayWidth,
					driverModes[x].displayHeight);

			combo->AddString(CString(modeString));
		}

	Save_Data.screenresolution=0;
	combo->SetIndex(Save_Data.screenresolution);

	if (Save_Data.fSoftware)
	{
		Save_Data.textureQuality=4;
		Save_Data.filtering=0;
		Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
		Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;
		Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
		combo=GETDLGITEM(IDC_CBO_GROUNDSHADING);
		combo->Clear();
		combo->AddString(LoadResString(IDS_L_OFF));
		combo->SetIndex(0);
		combo=GETDLGITEM(IDC_CBO_REFLECTIONS);
		combo->Clear();
		combo->AddString(LoadResString(IDS_L_OFF));
		combo->SetIndex(0);
	}
	else
	{
		combo=GETDLGITEM(IDC_CBO_GROUNDSHADING);
		combo->Clear();
		combo->AddString(LoadResString(IDS_L_OFF));
		combo->AddString(LoadResString(IDS_L_OFF+1));
		combo=GETDLGITEM(IDC_CBO_REFLECTIONS);
		combo->Clear();
		combo->AddString(LoadResString(IDS_L_OFF));
		combo->AddString(LoadResString(IDS_L_OFF+1));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadString
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
char* COverlay::LdStr(SLong resID)
{
	char* retval;
	CString str;
	str.LoadString(resID);
	const char* tmp=LPCTSTR(str);
	retval=new char[strlen(tmp)+1];
	strcpy(retval,tmp);
	return retval;
}
