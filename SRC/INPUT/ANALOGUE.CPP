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


//------------------------------------------------------------------------------
//Filename       analogue.cpp
//System         
//Author         Jim Taylor
//Date           Thu 14 Mar 1996
//Description    Top level analogue control code.
	#define F_GRAFIX
	#define F_SOUNDS
	#define F_BATTLE
#include	"dosdefs.h"
//#include <afx.h>
#include	"analogue.h"
#include	"display.h"
#include	"files.g"
#include	"dinput.h"
#include	"stub3d.h"
#include	"scontrol.h"
#include	"myerror.h"
#include "monotxt.h"
#include "cstring.h"

//#include	<initguid.h>

#include	"sw_force.h"	//standard header, but all the functions are inline

Analogue	_Analogue;
BITABLE(Bool);
#undef LoadLibrary			//used to have my own loadlibrary


HRESULT SWFF_CreateAxisCenter(
	IN LPDIRECTINPUTDEVICE2 pDIDevice, 
	IN OUT LPDIRECTINPUTEFFECT * ppDIEffect,
	IN LONG lMagnitude,
	IN LONG lCentre,
	IN DWORD dwAxis);

HRESULT SWFF_ChangeAxisCenter(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN LONG lMagnitude,
	IN LONG lCentre);
HRESULT SWFF_ChangeRawAxisForceEffect(
	IN LPDIRECTINPUTEFFECT ppDIEffect,
	IN LONG lMagnitude);
HRESULT SWFF_CreateAxisDamping(
	IN LPDIRECTINPUTDEVICE2 pDIDevice, 
	IN OUT LPDIRECTINPUTEFFECT * ppDIEffect,
	IN LONG lMagnitude,
//	IN LONG lCentre,
	IN DWORD dwAxis);
HRESULT SWFF_ChangeAxisDamping(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN LONG lMagnitude
//	,IN LONG lCentre
	);


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Analogue
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//
//Description	Clear all drivers and axes
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON		Analogue::Analogue()
{
		readytopoll=false;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Analogue
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DES		Analogue::~Analogue()
{
//DeadCode DAW 04Apr96 	INT3();
	CloseDown();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Initialise
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//
//Description	Init whole system - load all drivers and init them
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode DAW 02Nov99 enum	{AX_FLAG_HATASBUTTON=0x200,AX_FLAG_HATASAXIS=0x400,AX_FLAG_AXIS=0x480,AX_FLAG_AXIS_IGNORE=0x4ff};
enum	{AX_FLAG_HATASBUTTON=0x200,AX_FLAG_HATASAXIS=0x400,AX_FLAG_AXIS=0x480,AX_FLAG_RELAXIS=0x4c0,AX_FLAG_AXIS_IGNORE=0x4ff};
static int axiscount,hatcount,buttoncount,buttonbase;
static int objectcount;
static bool	makerelative;
DIOBJECTDATAFORMAT	dataobjects[100];

static	BOOL CALLBACK DIEnumDeviceObjectsProc(LPCDIDEVICEOBJECTINSTANCE ddoi,LPVOID pvRef)
{
	RunTimeDevDesc*	dev=(RunTimeDevDesc*)pvRef;
	if (ddoi->guidType==GUID_Button || ddoi->guidType==GUID_Key)
	{	//_DIOBJECTDATAFORMAT
		dataobjects[objectcount&0xff].pguid=0;
		dataobjects[objectcount].dwOfs=buttonbase+buttoncount;
		dataobjects[objectcount].dwType=ddoi->dwType;
		dataobjects[objectcount].dwFlags=0;
		buttoncount++;
		objectcount++;
	}
	else
	if (ddoi->guidType==GUID_POV)
	{
		dataobjects[objectcount].pguid=0;
		if (dev->hatmaps[hatcount]==AU_UNUSED)
			dataobjects[objectcount].dwOfs=AX_FLAG_HATASBUTTON+buttonbase+50-8*(hatcount+1);
		else
		{
			dataobjects[objectcount].dwOfs=AX_FLAG_HATASAXIS+dev->hatmaps[hatcount];
			if (dev->hatmaps[hatcount]==AU_UI_X)
			{
				_Analogue.axisscales[dev->hatmaps[hatcount]]=40;
				_Analogue.axisscales[dev->hatmaps[hatcount]+1]=-40;
			}
			else
			{
				_Analogue.axisscales[dev->hatmaps[hatcount]]=500;
				_Analogue.axisscales[dev->hatmaps[hatcount]+1]=500;
			}
		}
		dataobjects[objectcount].dwType=ddoi->dwType;
		dataobjects[objectcount].dwFlags=0;
		hatcount++;
		objectcount++;
	}
	else
	{
		if (dev->axismaps[axiscount]!=AU_UNUSED)
		{	//DIDFT_ABSAXIS DIDFT_MAKEINSTANCE
			dataobjects[objectcount].pguid=0;
				dataobjects[objectcount].dwOfs=AX_FLAG_AXIS+(dev->axismaps[axiscount]<<2);
			dataobjects[objectcount].dwType=(ddoi->dwType);//&DIDFT_ANYINSTANCE)+DIDFT_AXIS;// DIDFT_ABSAXIS;
			dataobjects[objectcount].dwFlags=0;
			if (DIDFT_GETTYPE(ddoi->dwType)==DIDFT_RELAXIS)	   //MOUSE AXES
			{
				makerelative=true;
				dataobjects[objectcount].dwOfs=AX_FLAG_RELAXIS+(dev->axismaps[axiscount]<<2);
				_Analogue.axisbases[dev->axismaps[axiscount]]=0;//0x80000000;
				if (axiscount<2)
					_Analogue.axisscales[dev->axismaps[axiscount]]=256*100;
				else
					_Analogue.axisscales[dev->axismaps[axiscount]]=256*3;
			}
			else
				if (dev->axismaps[axiscount]==AU_THROTTLE)
				{
					_Analogue.axisbases[dev->axismaps[axiscount]]=-32767;
					_Analogue.axisscales[dev->axismaps[axiscount]]=-128;
				}
				else
				{
					_Analogue.axisbases[dev->axismaps[axiscount]]=0x80000000;
					_Analogue.axisscales[dev->axismaps[axiscount]]=0;
				}

			objectcount++;
		}
		axiscount++;
		if (dev->useff)
		{	//pick up first 5 axes on selected FF device:
			//I really want to make sure they are X and Y axes...
			if (ddoi->dwFlags&DIDOI_FFACTUATOR)
				for (int i=0;i<MAXFORCEAXES;i++)
					if (!_Analogue.ForceAxes[i])
					{
						_Analogue.ForceAxes[i]=ddoi->dwType;
						break;
					}
		}
	}
	return DIENUM_CONTINUE;
}
BOOL CALLBACK DIEnumEffectsProc(LPCDIEFFECTINFO pdei,LPVOID pvRef)
{
	return	DIENUM_CONTINUE;	  //DIEP_ENVELOPE
}
 

Bool	Analogue::Initialise(int HWNDw,int HINSTANCEi)
{
	{for (int i=0;i<MAXFORCEAXES;i++)	   ForceAxes[i]=NULL;}
	{for (int i=0;i<AU_MAX;i++)	   axisdeltas[i]=0;}

	HWND w=(HWND)HWNDw;
	HINSTANCE i=(HINSTANCE)HINSTANCEi;
	DIdev=Master_3d.g_lpDI;
//	DirectInputCreate(i,DIRECTINPUT_VERSION,&DIdev,NULL);
	if (runtimedevices[0].devid.Data1==0)
	{
		SController::BuildEnumerationTables();
		SController::GetAxisConfig(true);			//fn used on config screen to set defaults
		SController::SetAxisConfig();
//##		runtimedevices[0].useff=true;
	}
	FFdevice=NULL;
	int gotprimdevs=0;
	int secdevscount=2;
	DIPROPDWORD	buffprop={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},150};
	DIPROPDWORD	absprop={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},DIPROPAXISMODE_ABS };
	for (int devnum=0;runtimedevices[devnum].devid.Data1;devnum++)
	{
		GUID	devid=runtimedevices[devnum].devid;
		if (devid.Data1==1)
			GetFirstJoystick(devid);
		else
		if (devid.Data1==2)
			GetFirstMouse(devid);
		if (devid.Data1>2)
		{
			DIdev->CreateDevice(devid,&runtimedevices[devnum].dev,NULL);
			int hres = runtimedevices[devnum].dev->QueryInterface(IID_IDirectInputDevice2,(LPVOID *)&runtimedevices[devnum].dev2); 
			axiscount=0;hatcount=0;
			buttoncount=0;
			if (runtimedevices[devnum].ismouse)
				if (gotprimdevs&1)
					buttonbase=250+50*secdevscount++;
				else
				{
					buttonbase=300;
					gotprimdevs|=1;
				}
			else
				if (gotprimdevs&2)
					buttonbase=250+50*secdevscount++;
				else
				{
					buttonbase=250;
					gotprimdevs|=2;
				}
			objectcount=0;
			makerelative=false;
			if (!SUCCEEDED(hres))
			{
				runtimedevices[devnum].dev->EnumObjects(DIEnumDeviceObjectsProc,runtimedevices+devnum,DIDFT_BUTTON+DIDFT_AXIS+DIDFT_POV);
				runtimedevices[devnum].dev->SetProperty(DIPROP_BUFFERSIZE,&buffprop.diph);
	//			runtimedevices[devnum].dev->SetProperty(DIPROP_AXISMODE,&absprop.diph);


				// DI_PROPNOEFFECT(0001) DIERR_INVALIDPARAM (57) 
				// DIERR_NOTINITIALIZED DIERR_OBJECTNOTFOUND(0002) DIERR_UNSUPPORTED(40001)
				
				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),makerelative?DIDF_RELAXIS:DIDF_ABSAXIS ,0x500,objectcount,dataobjects};
//DeadCode DAW 02Nov99 				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),DIDF_ABSAXIS ,0x500,objectcount,dataobjects};
				runtimedevices[devnum].dev->SetDataFormat(&dataform);
	//			int hres = runtimedevices[devnum].dev->QueryInterface(IID_IDirectInputDevice2,(LPVOID *)&runtimedevices[devnum].dev2); 
				runtimedevices[devnum].dev2=NULL;
#ifdef	NDEBUG
				runtimedevices[devnum].dev->SetCooperativeLevel(w,DISCL_FOREGROUND+DISCL_EXCLUSIVE);
#else
				runtimedevices[devnum].dev->SetCooperativeLevel(w,DISCL_BACKGROUND+DISCL_NONEXCLUSIVE);
#endif
				runtimedevices[devnum].dev->Acquire();
			}
			else
			{
				runtimedevices[devnum].dev->Release();
				runtimedevices[devnum].dev=NULL;
				runtimedevices[devnum].dev2->EnumObjects(DIEnumDeviceObjectsProc,runtimedevices+devnum,DIDFT_BUTTON+DIDFT_AXIS+DIDFT_POV);
				runtimedevices[devnum].dev2->SetProperty(DIPROP_BUFFERSIZE,&buffprop.diph);

				// DI_PROPNOEFFECT(0001) DIERR_INVALIDPARAM (57) 
				// DIERR_NOTINITIALIZED DIERR_OBJECTNOTFOUND(0002) DIERR_UNSUPPORTED(40001)
				
				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),makerelative?DIDF_RELAXIS:DIDF_ABSAXIS ,0x500,objectcount,dataobjects};
//DeadCode DAW 02Nov99 				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),DIDF_ABSAXIS ,0x500,objectcount,dataobjects};
				int rv=runtimedevices[devnum].dev2->SetDataFormat(&dataform);
				if (rv!=DI_OK)
					_Error.ReallyEmitSysErr("Could not setup data format for analogue device %i",devnum);
	//			int hres = runtimedevices[devnum].dev->QueryInterface(IID_IDirectInputDevice2,(LPVOID *)&runtimedevices[devnum].dev2); 
				if (!ForceAxes[1])
					runtimedevices[devnum].useff=false;
				if (runtimedevices[devnum].useff)
				{
 
					FFdevice=runtimedevices[devnum].dev2;
//TEMPCODE DAW 06/05/99 					FFdevice->EnumEffects( DIEnumEffectsProc,NULL,DIEFT_ALL);  
					DIPROPDWORD	centreprop={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},};
					FFdevice->SetProperty(DIPROP_AUTOCENTER,&centreprop.diph);
//5=XF,6=XB,9=SF,10=SB 
#ifdef	NDEBUG
					runtimedevices[devnum].dev2->SetCooperativeLevel(w,DISCL_FOREGROUND+DISCL_EXCLUSIVE);
#else
					runtimedevices[devnum].dev2->SetCooperativeLevel(w,DISCL_BACKGROUND+DISCL_EXCLUSIVE);
#endif
				}
				else
#ifdef	NDEBUG
					runtimedevices[devnum].dev2->SetCooperativeLevel(w,DISCL_FOREGROUND+DISCL_EXCLUSIVE);
#else
					runtimedevices[devnum].dev2->SetCooperativeLevel(w,DISCL_BACKGROUND+DISCL_NONEXCLUSIVE);
#endif
				rv=runtimedevices[devnum].dev2->Acquire();
				if (rv!=DI_OK)
					_Error.ReallyEmitSysErr("Could not aquire analogue device %i",devnum);
				int i=4;
			}
		}
	}
	for (int a=0;a<AU_MAX;a++)
		axisvalues[a]=0x8000;
	if (FFdevice)
	{			 //DIGFFS_ACTUATORSOFF
		DWORD result;
		FFdevice-> GetForceFeedbackState(&result);
		SWFF_DestroyAllEffects(FFdevice);
		FFshake.Init(FFdevice);
		FFstiff.Init(FFdevice);
		FFpush.Init(FFdevice);
		FFdamp.Init(FFdevice);
	}
	readytopoll=true;

	return TRUE;
}
inline	CString	LoadResString(int resnum)
{
	CString s;
	s.LoadString(resnum);
	return s;
};
#include	"..\mfc\resource.h"
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadGame
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Analogue::LoadGame()
{	//check if the selected devices are attatched... if not put up a message!
	for (int devnum=0;runtimedevices[devnum].devid.Data1;devnum++)
		if (runtimedevices[devnum].devid.Data1>2)
			if ((Master_3d.g_lpDI->GetDeviceStatus(runtimedevices[devnum].devid))!=DI_OK)
				if ((Master_3d.g_lpDI->GetDeviceStatus(runtimedevices[devnum].devid))!=DI_NOTATTACHED)
					MessageBox(NULL,LoadResString(IDS_REINSTALLORPREFS),LoadResString(IDS_JOYSTICKNOTDETECTED),MB_OK);
				else
					MessageBox(NULL,LoadResString(IDS_RECONNECTORPREFS),LoadResString(IDS_JOYSTICKNOTDETECTED),MB_OK);
	return(TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseDown
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Analogue::CloseDown()
{
	readytopoll=false;
	for (int devnum=0;runtimedevices[devnum].devid.Data1;devnum++)
	{
		if (runtimedevices[devnum].dev2)
		{
			runtimedevices[devnum].dev2->Unacquire();
			runtimedevices[devnum].dev2->Release();
//			runtimedevices[devnum].dev->Release();
			runtimedevices[devnum].dev2=NULL;
			runtimedevices[devnum].dev=NULL;
		}
		else
		if (runtimedevices[devnum].dev)
		{
			runtimedevices[devnum].dev->Unacquire();
			runtimedevices[devnum].dev->Release();
			runtimedevices[devnum].dev=NULL;
		}
	}
	FFdevice=NULL;
	FFshake.Init(FFdevice);
	FFstiff.Init(FFdevice);
	FFpush.Init(FFdevice);
	FFdamp.Init(FFdevice);
//	if (DIdev)
//		DIdev->Release();
//	DIdev=NULL;
	return TRUE;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadPosition
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//enum	{AX_FLAG_HATASBUTTON=0x200,AX_FLAG_HATASAXIS=0x400,AX_FLAG_AXIS=0x480,AX_FLAG_AXIS_IGNORE=0x4ff};
void	Analogue::PollForces()
{
	if (!FFdevice)
		return;
	FFpush.Tick();
	FFstiff.Tick();
	FFshake.Tick();
	FFdamp.Tick();
	switch	(lastFFeffect)
	{	//intensional fall through
	case 0:		if (FFpush.Poll())	{	lastFFeffect=1;	return;		}
	case 1:		if (FFstiff.Poll())	{	lastFFeffect=2;	return;		}
	case 2:		if (FFshake.Poll())	{	lastFFeffect=3;	return;		}
	case 3:		if (FFdamp.Poll())	{	lastFFeffect=0;	return;		}

	case 4:	//really 0 again
				if (FFpush.Poll())	{	lastFFeffect=1;	return;		}
	case 5:	//really 1 again
				if (FFstiff.Poll())	{	lastFFeffect=2;	return;		}

	case 6:		if (FFshake.Poll())	{	lastFFeffect=3;	return;		}
	}
	
}
void	Analogue::PollPosition()
{
	if (!readytopoll)	
		return;
	DIDEVICEOBJECTDATA	readings[30];
	for (int devnum=0;runtimedevices[devnum].devid.Data1;devnum++)
	if (runtimedevices[devnum].dev || runtimedevices[devnum].dev2)
	{	// DI_BUFFEROVERFLOW
		//DIERR_INPUTLOST (1E) DIERR_INVALIDPARAM (57 ) DIERR_NOTACQUIRED (0c)
		//DIERR_NOTBUFFERED (07) DIERR_NOTINITIALIZED (15)
		int rv;
		if (runtimedevices[devnum].dev2)
		{
			rv=runtimedevices[devnum].dev2->Poll();
			if (rv==DIERR_INPUTLOST)
			{
				runtimedevices[devnum].dev2->Acquire();
				runtimedevices[devnum].dev2->Poll();
			}
		}
		for (int foreverlimit=5;--foreverlimit;)
		{
			ULong numelts=30;
			if (runtimedevices[devnum].dev2)
			{
				rv=runtimedevices[devnum].dev2->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),readings,&numelts,0);
				if (rv==DIERR_INPUTLOST)
				{
					runtimedevices[devnum].dev2->Acquire();
					rv=runtimedevices[devnum].dev2->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),readings,&numelts,0);
				}
			}
			else
			{
				rv=runtimedevices[devnum].dev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),readings,&numelts,0);
				if (rv==DIERR_INPUTLOST)
				{
					runtimedevices[devnum].dev->Acquire();
					rv=runtimedevices[devnum].dev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),readings,&numelts,0);
				}
			}
		breakif (!numelts);
			for (DIDEVICEOBJECTDATA* datum=readings;numelts;datum++,numelts--)
			{
				if (datum->dwOfs>=AX_FLAG_AXIS)
				{
					if (datum->dwOfs>=AX_FLAG_RELAXIS)
					{
						int theaxis=(datum->dwOfs-AX_FLAG_RELAXIS)>>2;
						if (theaxis<32)
							if (axisscales[theaxis])
							{
								if (axisbases[theaxis]==0x80000000)
									axisbases[theaxis]=0;
								axisbases[theaxis]+=(SWord)datum->dwData;
								int newval=MULSHSIN(axisbases[theaxis],axisscales[theaxis],8);
								if (newval<-0x7fff)
									newval=-0x7fff;
								if (newval>0x7fff)
									newval=0x7fff;
								axisvalues[theaxis]=newval;
							}
							else
							{
								int newval=axisvalues[theaxis]+(SWord)datum->dwData;
								if (newval<-0x7fff)
									newval=-0x7fff;
								if (newval>0x7fff)
									newval=0x7fff;
								axisvalues[theaxis]=newval;
							}

					}
					else
					{

						int theaxis=(datum->dwOfs-AX_FLAG_AXIS)>>2;
						if (theaxis<32)
							if (axisscales[theaxis])
							{
								if (axisbases[theaxis]==0x80000000)
									axisbases[theaxis]=MULSHSIN(datum->dwData,axisscales[theaxis],8);
								int newval=(MULSHSIN(datum->dwData,axisscales[theaxis],8)-axisbases[theaxis]);
								if (newval<-0x7fff)
									newval=0-0x7fff;
								if (newval>0x7fff)
									newval=0x7FFF;
		//DEADCODE RDH 20/05/99 						Mono_Text.PrintHexAt(theaxis,theaxis,newval,4);
								axisvalues[theaxis]=newval;
							}
							else
							{
								if (datum->dwData==0)
									axisvalues[theaxis]=-0x7fff;
								else
									axisvalues[theaxis]=datum->dwData-0x8000;
							}
		//temp				Mono_Text.PrintHexAt(20,(datum->dwOfs-AX_FLAG_AXIS)>>2,datum->dwData,4);
					}
				}
				else
				if (datum->dwOfs>=AX_FLAG_HATASAXIS)
				{
					int dx=0,dy=0;
					if ((datum->dwData&0xffff)!=0xffff)
					switch(datum->dwData/1125)	//36000 max... / 32 steps
					{	//this code is not so good if we get proper analogue hats in the short term
						//so I have extended it ready to allow more steps.
					case 32: case 33: case 34:	//extra overflow cases...
					case 0:	case 1: case 30: case 31:	dx=0;dy=1;				break;
					case 2: case 3: case 4: case 5:		dx=1;dy=1;				break;
					case 6: case 7:	case 8: case 9:		dx=1;dy=0;				break;
					case 10: case 11: case 12: case 13:	dx=1,dy=-1;				break;
					case 14: case 15: case 16: case 17:	dx=0;dy=-1;				break;
					case 18: case 19: case 20: case 21:	dx=-1;dy=-1;			break;
					case 22: case 23: case 24: case 25:	dx=-1;dy=0;				break;
					case 26: case 27: case 28: case 29:	dx=-1;dy=1;				break;
					}
					int axis=datum->dwOfs-AX_FLAG_HATASAXIS;
					dx*=axisscales[axis];dy*=axisscales[axis+1];
					if (datum->dwOfs-AX_FLAG_HATASAXIS!=AU_UI_X)
						if (dx==0 && dy==0)
						{
						   axisvalues[axis]=0;
						   axisvalues[axis+1]=0;
						}
					axisdeltas[axis]=dx;
					axisdeltas[axis+1]=dy;
				}
				else
				if (datum->dwOfs>=AX_FLAG_HATASBUTTON)
				{
					int pressing;
					int base=datum->dwOfs-AX_FLAG_HATASBUTTON;
					if ((datum->dwData&0xffff)==0xffff)
						pressing=8;
					else
						pressing=(((datum->dwData/2250)+1)&0x0e)>>1;

					for (int i=0;i<8;i++)
						if (i!=pressing)
							Inst3d::OnKeyUp(base+i);
						else
							Inst3d::OnKeyDown(base+i);
						
				}
				else
				{
					if (datum->dwData&0x80)
						Inst3d::OnKeyDown(datum->dwOfs);
					else
						Inst3d::OnKeyUp(datum->dwOfs);

				}
			}
		};
	}
	for (int i=0,j;i<AU_MAX;i++)									  //DAW 07/05/99
		if ((j=axisdeltas[i])!=0)
		{
			j+=(SWord)axisvalues[i];
			if (j<32767 && j>-32767)
				axisvalues[i]=j;
		}
	PollForces();
}
SWord	Analogue::ReadPosition(AxisUses a)
{
  return axisvalues[a];
}

struct	Inf	{_GUID* g;int buts,hats,axes;bool foundone;};
static BOOL CALLBACK DIEnumDevicesProc(const DIDEVICEINSTANCE *ddi,LPVOID pvRef)
{
	Inf* inf=(Inf*) pvRef;
	inf->g[0]=ddi->guidInstance;
	inf->foundone=true;
	return	DIENUM_STOP;
}
bool	Analogue::GetFirstMouse(struct _GUID &uid,int *numbuts,int *numhats)
{
	Inf inf={&uid};
	DIdev->EnumDevices(DIDEVTYPE_MOUSE,DIEnumDevicesProc,&inf,DIEDFL_ATTACHEDONLY);
	return	inf.foundone;
}
bool	Analogue::GetFirstJoystick(struct _GUID &uid,int * axes,int *numbuts,int *numhats)
{
	Inf inf={&uid};
	DIdev->EnumDevices(DIDEVTYPE_JOYSTICK,DIEnumDevicesProc,&inf,DIEDFL_ATTACHEDONLY);
	return	inf.foundone;
}

//
// Push forces descriptions
//
//
void	FF_Push::Init(IDirectInputDevice2A* d)	
{
	triggerX=triggerZ=false;MX=MZ=0x8000;durationX=durationZ=0;
	dev=d;
	if (pForceX)  pForceX->Release();	pForceX=NULL;
	if (pForceY)  pForceY->Release();	pForceY=NULL;
	if (dev)
	{
		SWFF_CreateRawAxisForceEffect(dev,&pForceX,0,X_AXIS);
		SWFF_CreateRawAxisForceEffect(dev,&pForceY,0,Y_AXIS);
		pForceX->Start(1,0);
		pForceY->Start(1,0);
//DEADCODE DAW 06/05/99 	Set(30000,30000,10);
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Set(-30000,-30000,10);
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Set(0,0,1);
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Poll();
	}

}

bool	FF_Push::Set(SWord x,SWord z,int dur)
{
	if (x==MX && z==MZ && (ULong)(durationX-dur-5)<10 && (ULong)(durationZ-dur-5)<10)
		return false;
	MX=x;MZ=z;
	durationX=durationZ=dur;
	triggerX=triggerZ=true;
	return true;
}

bool	FF_Push::SetX(SWord x,int dur)
{
	if (x==MX && (ULong)(durationX-dur-5)<10)
		return false;
	MX=x;
	durationX=dur;
	triggerX=true;
	return true;
}

bool	FF_Push::SetZ(SWord z,int dur)
{
	if (z==MZ && (ULong)(durationZ-dur-5)<10)
		return false;
	MZ=z;
	durationZ=dur;
	triggerZ=true;
	return true;
}


bool	FF_Push::Poll()
{
	if (!(triggerX||triggerZ))	return false;
	if (durationX<0)
		MX=0;
	if (durationZ<0)
		MZ=0;
	if (triggerX)
	{
		SWFF_ChangeRawAxisForceEffect(pForceX,MZ/4);
		pForceX->Start(1,0);

		triggerX=false;
		return true;
	}
//	if (triggerZ)	//must be!
//	{
		SWFF_ChangeRawAxisForceEffect(pForceY,MZ/4);
		pForceX->Start(1,0);
		triggerZ=false;
		return true;
//	}
//	return false;	//not poss
}
bool	FF_Push::Tick()
{
	if (durationX==0)
		triggerX=true;
	if (durationZ==0)
		triggerZ=true;
	durationX--;
	durationZ--;
	return false;
}
//
// Stiffness and centrepoint descriptions
//
//
//
bool	FF_Stiff::Set(SWord cx,SWord cz,SWord sx,SWord sz)
{
	if (cx==CX && cz==CZ && sx==SX && sz==SZ)
		return false;
	CX=cx;CZ=cz;
	SX=sx;SZ=sz;
	trigger=true;
	return true;
}

bool	FF_Stiff::SetX(SWord cx,SWord sx)
{
	if (cx==CX && sx==SX)
		return false;
	CX=cx;
	SX=sx;
	trigger=true;
	return true;
}

bool	FF_Stiff::SetZ(SWord cz,SWord sz)
{
	if (cz==CZ && sz==SZ)
		return false;
	CZ=cz;
	SZ=sz;
	trigger=true;
	return true;
}

void	FF_Stiff::Init(IDirectInputDevice2A* d)	
{
	trigger=false;
	CX=CZ=SX=SZ=0x0000;
	dev=d;
	if (pStiffX)	pStiffX->Release();
	if (pStiffY)	pStiffY->Release();
	pStiffX=pStiffY=NULL;
	if (d)
	{
		SWFF_CreateAxisCenter(dev,&pStiffX,0,0,X_AXIS);
		SWFF_CreateAxisCenter(dev,&pStiffY,0,0,Y_AXIS);
		if (pStiffX)
		{
//			DIPROPDWORD	centreprop={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},};
//			d->SetProperty(DIPROP_AUTOCENTER,&centreprop.diph);
			pStiffX->Start(1,0);
			pStiffY->Start(1,0);
		}
//DEADCODE DAW 06/05/99 		SetX(25000,30000);
//DEADCODE DAW 06/05/99 		SetZ(25000,30000);
//DEADCODE DAW 06/05/99 		Poll();
//DEADCODE DAW 06/05/99 		Poll();
	}
}
bool	FF_Stiff::Poll()
{
	if (!trigger)	return false;
	SWFF_ChangeAxisCenter(pStiffX,(SX)/3,CX/3);
//TEMPCODE DAW 05/05/99 	pStiffX->Start(1,0);
	SWFF_ChangeAxisCenter(pStiffY,(SZ)/3,CZ/3);
//TEMPCODE DAW 05/05/99 	pStiffX->Start(1,0);
	trigger=false;
	return true;
}

//
// This will put a damper on the whole routine
//
//
//
//
//
bool	FF_Damp::Set(SWord mx,SWord mz)
{
	if (mx!=MX || mz!=MZ)
	{
		trigger=true;
		MX=mx;
		MZ=mz;
		return true;
	}
	else
		return	false;

}
bool	FF_Damp::SetX(SWord mx)
{
	if (mx!=MX)
	{
		trigger=true;
		MX=mx;
		return true;
	}
	else
		return	false;
}
bool	FF_Damp::SetZ(SWord mz)
{
	if (mz!=MZ)
	{
		trigger=true;
		MZ=mz;
		return true;
	}
	else
		return	false;
}
void	FF_Damp::Init(IDirectInputDevice2A* d)	
{
	trigger=false;
	MX=MZ=3000;
	dev=d;
	if (pDampX)	pDampX->Release();
	if (pDampY)	pDampY->Release();
	pDampX=pDampY=NULL;
	if (d)
	{
		SWFF_CreateAxisDamping(dev,&pDampX,1000,X_AXIS);
		SWFF_CreateAxisDamping(dev,&pDampY,1000,Y_AXIS);
		if (pDampX)
		{
			pDampX->Start(1,0);
			pDampY->Start(1,0);
		}
//DEADCODE DAW 06/05/99 		SetX(25000,30000);
//DEADCODE DAW 06/05/99 		SetZ(25000,30000);
//DEADCODE DAW 06/05/99 		Poll();
//DEADCODE DAW 06/05/99 		Poll();
	}
}
bool	FF_Damp::Poll()
{
	if (!trigger)	return false;
	SWFF_ChangeAxisDamping(pDampX,(MX)/3);
//TEMPCODE DAW 05/05/99 	pStiffX->Start(1,0);
	SWFF_ChangeAxisDamping(pDampY,(MZ)/3);
//TEMPCODE DAW 05/05/99 	pStiffX->Start(1,0);
	trigger=false;
	return true;
}

//
// Shakes descriptions
//
//
//
//
//

bool	FF_Shake::Set(SWord mx,SWord mz,SWord fx,SWord fz,bool rnd)
{
	if (MX==mx && MZ==mz && FX==fx && FZ==fz && randomX==rnd && randomZ==rnd)
		return false;
	if (rnd && pRandX==NULL)
		return false;
	MX=mx;MZ=mz;
	FX=fx;FZ=fz;
	randomX=randomZ=rnd;
	triggerX=triggerZ=true;
	return true;
}

bool	FF_Shake::SetX(SWord mx,SWord fx,bool rnd)
{
//DEADCODE RDH 23/05/99 	long qMX = mx;
//DEADCODE RDH 23/05/99 	long qFX = fx;
//DEADCODE RDH 23/05/99 	Mono_Text.PrintAt(5, 5, qMX, UByteP("M X "));
//DEADCODE RDH 23/05/99 	Mono_Text.PrintAt(5, 6, qFX, UByteP("F X "));
	if (MX==mx && FX==fx && randomX==rnd)
		return false;
	if (rnd && pRandX==NULL)
		return false;
	MX=mx;
	FX=fx;
	randomX==rnd;
	triggerX=true;
	return true;
}

bool	FF_Shake::SetZ(SWord mz,SWord fz,bool rnd)
{
//DEADCODE RDH 23/05/99 	long qMZ = mz;
//DEADCODE RDH 23/05/99 	long qFZ = fz;
//DEADCODE RDH 23/05/99 	Mono_Text.PrintAt(5, 8, qMZ, UByteP("M Z "));
//DEADCODE RDH 23/05/99 	Mono_Text.PrintAt(5, 9, qFZ, UByteP("F Z "));
	if (MZ==mz && FZ==fz && randomZ==rnd)
		return false;
	if (rnd && pRandY==NULL)
		return false;
	MZ=mz;
	FZ=fz;
	randomZ==rnd;
	triggerZ=true;
	return true;
}

void	FF_Shake::Init(IDirectInputDevice2A* d)	
{
	triggerX=triggerZ=randomX=randomZ=false;MX=MZ=FX=FZ=0x8000;dev=d;
	if (pShakeX)	pShakeX->Release();	pShakeX=NULL;
	if (pShakeY)	pShakeY->Release();	pShakeY=NULL;				  //JIM 03/03/99
	if (pRandX)		pRandX->Release();	pRandX=NULL;
	if (pRandY)		pRandY->Release();	pRandY=NULL;				  //JIM 03/03/99
	if (d)
	{
		SWFF_CreateROMEffect(dev,&pRandX,GUID_RandomNoise,INFINITE,0,0,-1);
		SWFF_CreateROMEffect(dev,&pRandY,GUID_RandomNoise,INFINITE,0,9000,-1);
		SWFF_CreatePeriodicEffect(dev,&pShakeX,SQUARE_HIGH,INFINITE,0,0,0,0,0,0,0,0,-1);
		SWFF_CreatePeriodicEffect(dev,&pShakeY,SQUARE_HIGH,INFINITE,0,0,0,0,0,0,0,0,-1);
		if (pRandX)
		{
			pRandX->Start(1,0);
			pRandY->Start(1,0);
		}
		pShakeX->Start(1,0);
		pShakeY->Start(1,0);
	}
//DEADCODE DAW 06/05/99 	Set(30000,30000,20,20,false);
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Set(30000,30000,20,20,true);
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Set(0,0,0,0,false);
//DEADCODE DAW 06/05/99 	Poll();
//DEADCODE DAW 06/05/99 	Poll();

}
bool	FF_Shake::Poll()
{
	if (!(triggerX || triggerZ))
		return false;
	if (triggerX)
	{
		if (randomX!=lastrandomX)
			if (lastrandomX)
			{
				SWFF_SetGain(pRandX,0);
//TEMPCODE DAW 05/05/99 				pRandX->Start(1,0);
			}
			else
			{
				SWFF_SetPeriodic(pShakeX,0,0,0,0);
//TEMPCODE DAW 05/05/99 				pShakeX->Start(1,0);
			}
		if (randomX)
		{
			SWFF_SetGain(pRandX,MX/3);
//TEMPCODE DAW 05/05/99 			pRandX->Start(1,0);
		}
		else
		{
			SWFF_SetPeriodic(pShakeX,MX/4,0,0,HZ_TO_uS(FX));
//TEMPCODE DAW 05/05/99 		 	pShakeX->Start(1,0);
		}
		triggerX=false;
		lastrandomX=randomX;
		return true;
	}
	//if (triggerZ)
	{
		if (randomZ!=lastrandomZ)
			if (lastrandomZ)
			{
				SWFF_SetGain(pRandY,0);
//TEMPCODE DAW 05/05/99 				pRandY->Start(1,0);
			}
			else
			{
				SWFF_SetPeriodic(pShakeY,0,0,0,0);
//TEMPCODE DAW 05/05/99 			 	pShakeY->Start(1,0);
			}
		if (randomZ)
		{
			SWFF_SetGain(pRandY,MZ/3);
//TEMPCODE DAW 05/05/99 			pRandY->Start(1,0);
		}
		else
		{
//DEADCODE RDH 23/05/99 	long qMZ = MZ;
//DEADCODE RDH 23/05/99 	long qFZ = FZ;
//DEADCODE RDH 23/05/99 	Mono_Text.PrintAt(25, 8, qMZ, UByteP("M Z "));
//DEADCODE RDH 23/05/99 	Mono_Text.PrintAt(25, 9, qFZ, UByteP("F Z "));
			SWFF_SetPeriodic(pShakeY,MZ/4,0,0,HZ_TO_uS(FZ));
//TEMPCODE DAW 05/05/99 		 	pShakeY->Start(1,0);
		}
		triggerZ=false;
		lastrandomZ=randomZ;
		return true;
	}
}

// Set Spring Constants function by DBM most of it stolen from CreateCondition
HRESULT SWFF_SetSpringConstants(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN DWORD lXCoefficient,
	IN DWORD lXOffset,
	IN DWORD lYCoefficient,
	IN DWORD lYOffset)
{
//	if(pDIEffect == NULL)
//		return SFERR_INVALID_PARAM;

	DIEFFECT thisEffect = { sizeof(DIEFFECT) };
	DICONDITION DIConditionStruct[2];
	DIConditionStruct[0].lOffset				= lXOffset;
	DIConditionStruct[0].lPositiveCoefficient	= lXCoefficient;
	DIConditionStruct[0].lNegativeCoefficient	= lXCoefficient;
	DIConditionStruct[0].dwPositiveSaturation	= 10000;
	DIConditionStruct[0].dwNegativeSaturation	= 10000;
	DIConditionStruct[0].lDeadBand				= 0;
	DIConditionStruct[1].lOffset				= lYOffset;
	DIConditionStruct[1].lPositiveCoefficient	= lYCoefficient;
	DIConditionStruct[1].lNegativeCoefficient	= lYCoefficient;
	DIConditionStruct[1].dwPositiveSaturation	= 10000;
	DIConditionStruct[1].dwNegativeSaturation	= 10000;
	DIConditionStruct[1].lDeadBand				= 0;

//	DWORD rgdwAxes[2];
//	int nAxisCount = 0;
//	if(lXCoefficient != 0)
//	{
//		rgdwAxes[nAxisCount] = _Analogue.ForceAxes[0];
//		nAxisCount++;
//	}
//	if(lYCoefficient != 0)
//	{
//		rgdwAxes[nAxisCount] = _Analogue.ForceAxes[1];
//		nAxisCount++;
//	}
//	if(lXCoefficient == 0 && lYCoefficient == 0)
//	{
//		nAxisCount = 2;
//		rgdwAxes[0] = _Analogue.ForceAxes[0];
//		rgdwAxes[1] = _Analogue.ForceAxes[1];
//	}

	DWORD cbTypeSpecificParams;
	PVOID pvTypeSpecificParams;
//	if(nAxisCount == 1)
//	{
//		cbTypeSpecificParams = sizeof(DICONDITION[1]);
//		if(lXCoefficient != 0)
//			pvTypeSpecificParams = &DIConditionStruct[0];
//		else
//			pvTypeSpecificParams = &DIConditionStruct[1];
//	}
//	else
//	{
		cbTypeSpecificParams = sizeof(DICONDITION[2]);
		pvTypeSpecificParams = &DIConditionStruct[0];
//	}
	thisEffect.cbTypeSpecificParams		= cbTypeSpecificParams;
	thisEffect.lpvTypeSpecificParams	= pvTypeSpecificParams;

	return pDIEffect->SetParameters(&thisEffect, DIEP_TYPESPECIFICPARAMS);
}
	
// ----------------------------------------------------------------------------
// Function: 	SWFF_SetGain
// Purpose:		Sets Gain for the Effect
// Parameters:	LPDIRECTINPUTEFFECT	pDIEffect	- Pointer to effect to set the gain for
//				DWORD dwGain					- Gain in 1 to 10000
// Returns:
// Algorithm:	
// Comments:
// 
// ----------------------------------------------------------------------------
HRESULT SWFF_SetGain(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN DWORD dwGain)
{
	if(pDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	DIEFFECT thisEffect = { sizeof(DIEFFECT) };
	thisEffect.dwGain = dwGain;
	return pDIEffect->SetParameters(&thisEffect, DIEP_GAIN);
}
// ----------------------------------------------------------------------------
// Function: 	SWFF_CreateRawAxisForceEffect
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice		- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect		- Receives pointer to created effect
//				LONG lMagnitude						- -10000 to 10000
//				DWORD dwAxis						- Either X_AXIS or Y_AXIS
//
//				
// Returns:		
// Algorithm:
// Comments:	Create this Effect once, then use SetParameter(...) to play the
//				force value
//
// ----------------------------------------------------------------------------
HRESULT SWFF_CreateAxisCenter(
	IN LPDIRECTINPUTDEVICE2 pDIDevice, 
	IN OUT LPDIRECTINPUTEFFECT * ppDIEffect,
	IN LONG lMagnitude,
	IN LONG lCentre,
	IN DWORD dwAxis)
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	if(!(dwAxis == X_AXIS || dwAxis == Y_AXIS))
		return SFERR_INVALID_PARAM;

	// Always clear return IPtr
	*ppDIEffect = NULL;

	GUID guid=GUID_Spring;

	LPDIRECTINPUTEFFECT  pRawForce;

	DICONSTANTFORCE DIConstantForceStruct;
	DIConstantForceStruct.lMagnitude = lMagnitude;

	DICONDITION DIConditionStruct;
	DIConditionStruct.lOffset				= lCentre;
	DIConditionStruct.lPositiveCoefficient	= lMagnitude;
	DIConditionStruct.lNegativeCoefficient	= lMagnitude;
	DIConditionStruct.dwPositiveSaturation	= 10000;
	DIConditionStruct.dwNegativeSaturation	= 10000;
	DIConditionStruct.lDeadBand				= 100;

	DWORD rgdwAxes[1];
	if(dwAxis == X_AXIS)
		rgdwAxes[0] = _Analogue.ForceAxes[0];
	else
		rgdwAxes[0] = _Analogue.ForceAxes[1];

	LONG rglDirection[1];
	rglDirection[0] = 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffect.dwDuration				= INFINITE;
	DIEffect.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffect.dwGain					= 10000;
	DIEffect.dwTriggerButton		= DIEB_NOTRIGGER;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 1;
	DIEffect.rgdwAxes				= rgdwAxes;
	DIEffect.rglDirection			= rglDirection;
	DIEffect.lpEnvelope				= NULL;
	DIEffect.cbTypeSpecificParams	= sizeof(DICONDITION);
	DIEffect.lpvTypeSpecificParams	= &DIConditionStruct;

	HRESULT hRet;
	hRet = pDIDevice->CreateEffect(GUID_Spring, &DIEffect, &pRawForce, NULL);
	if(FAILED(hRet)) return hRet;

	*ppDIEffect = pRawForce;
	return SUCCESS;
}
HRESULT SWFF_ChangeAxisCenter(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN LONG lMagnitude,
	IN LONG lCentre)
{
	if(pDIEffect == NULL)
		return SFERR_INVALID_PARAM;



//	DICONSTANTFORCE DIConstantForceStruct;
//	DIConstantForceStruct.lMagnitude = lMagnitude;

	DICONDITION DIConditionStruct;
	DIConditionStruct.lOffset				= lCentre;
	DIConditionStruct.lPositiveCoefficient	= lMagnitude;
	DIConditionStruct.lNegativeCoefficient	= lMagnitude;
	DIConditionStruct.dwPositiveSaturation	= 10000;
	DIConditionStruct.dwNegativeSaturation	= 10000;
	DIConditionStruct.lDeadBand				= 100;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffect.dwDuration				= INFINITE;
	DIEffect.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffect.dwGain					= 10000;
	DIEffect.dwTriggerButton		= DIEB_NOTRIGGER;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 1;
	DIEffect.rgdwAxes				= NULL;
	DIEffect.rglDirection			= NULL;
	DIEffect.lpEnvelope				= NULL;
	DIEffect.cbTypeSpecificParams	= sizeof(DICONDITION);
	DIEffect.lpvTypeSpecificParams	= &DIConditionStruct;

	return pDIEffect->SetParameters(&DIEffect, DIEP_TYPESPECIFICPARAMS);
}
// ----------------------------------------------------------------------------
// Function: 	SWFF_CreateAxisDamping
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice		- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect		- Receives pointer to created effect
//				LONG lMagnitude						- -10000 to 10000
//				DWORD dwAxis						- Either X_AXIS or Y_AXIS
//
//				
// Returns:		
// Algorithm:
// Comments:	Create this Effect once, then use SetParameter(...) to play the
//				force value
//
// ----------------------------------------------------------------------------
HRESULT SWFF_CreateAxisDamping(
	IN LPDIRECTINPUTDEVICE2 pDIDevice, 
	IN OUT LPDIRECTINPUTEFFECT * ppDIEffect,
	IN LONG lMagnitude,
//	IN LONG lCentre,
	IN DWORD dwAxis)
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	if(!(dwAxis == X_AXIS || dwAxis == Y_AXIS))
		return SFERR_INVALID_PARAM;

	// Always clear return IPtr
	*ppDIEffect = NULL;

//	GUID guid=GUID_Damper;

	LPDIRECTINPUTEFFECT  pRawForce;

	DICONSTANTFORCE DIConstantForceStruct;
	DIConstantForceStruct.lMagnitude = lMagnitude;

	DICONDITION DIConditionStruct;
	DIConditionStruct.lOffset				= 0;//lCentre;
	DIConditionStruct.lPositiveCoefficient	= lMagnitude;
	DIConditionStruct.lNegativeCoefficient	= lMagnitude;
	DIConditionStruct.dwPositiveSaturation	= 10000;
	DIConditionStruct.dwNegativeSaturation	= 10000;
	DIConditionStruct.lDeadBand				= 0;

	DWORD rgdwAxes[1];
	if(dwAxis == X_AXIS)
		rgdwAxes[0] = _Analogue.ForceAxes[0];
	else
		rgdwAxes[0] = _Analogue.ForceAxes[1];

	LONG rglDirection[1];
	rglDirection[0] = 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffect.dwDuration				= INFINITE;
	DIEffect.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffect.dwGain					= 10000;
	DIEffect.dwTriggerButton		= DIEB_NOTRIGGER;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 1;
	DIEffect.rgdwAxes				= rgdwAxes;
	DIEffect.rglDirection			= rglDirection;
	DIEffect.lpEnvelope				= NULL;
	DIEffect.cbTypeSpecificParams	= sizeof(DICONDITION);
	DIEffect.lpvTypeSpecificParams	= &DIConditionStruct;

	HRESULT hRet;
	hRet = pDIDevice->CreateEffect(GUID_Damper, &DIEffect, &pRawForce, NULL);
	if(FAILED(hRet)) return hRet;

	*ppDIEffect = pRawForce;
	return SUCCESS;
}

HRESULT SWFF_ChangeAxisDamping(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN LONG lMagnitude
//	,IN LONG lCentre
	)
{
	if(pDIEffect == NULL)
		return SFERR_INVALID_PARAM;



//	DICONSTANTFORCE DIConstantForceStruct;
//	DIConstantForceStruct.lMagnitude = lMagnitude;

	DICONDITION DIConditionStruct;
	DIConditionStruct.lOffset				= 0;
	DIConditionStruct.lPositiveCoefficient	= lMagnitude;
	DIConditionStruct.lNegativeCoefficient	= lMagnitude;
	DIConditionStruct.dwPositiveSaturation	= 10000;
	DIConditionStruct.dwNegativeSaturation	= 10000;
	DIConditionStruct.lDeadBand				= 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffect.dwDuration				= INFINITE;
	DIEffect.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffect.dwGain					= 10000;
	DIEffect.dwTriggerButton		= DIEB_NOTRIGGER;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 1;
	DIEffect.rgdwAxes				= NULL;
	DIEffect.rglDirection			= NULL;
	DIEffect.lpEnvelope				= NULL;
	DIEffect.cbTypeSpecificParams	= sizeof(DICONDITION);
	DIEffect.lpvTypeSpecificParams	= &DIConditionStruct;

	return pDIEffect->SetParameters(&DIEffect, DIEP_TYPESPECIFICPARAMS);
}

HRESULT SWFF_ChangeRawAxisForceEffect(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN LONG lMagnitude)
{
	if(pDIEffect == NULL)
		return SFERR_INVALID_PARAM;


	GUID guid=GUID_Spring;

	DICONSTANTFORCE DIConstantForceStruct;
	DIConstantForceStruct.lMagnitude = lMagnitude;

//	DICONDITION DIConditionStruct;
//	DIConditionStruct.lOffset				= lCentre;
//	DIConditionStruct.lPositiveCoefficient	= lMagnitude;
//	DIConditionStruct.lNegativeCoefficient	= lMagnitude;
//	DIConditionStruct.dwPositiveSaturation	= 10000;
//	DIConditionStruct.dwNegativeSaturation	= 10000;
//	DIConditionStruct.lDeadBand				= 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffect.dwDuration				= INFINITE;
	DIEffect.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffect.dwGain					= 10000;
	DIEffect.dwTriggerButton		= DIEB_NOTRIGGER;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 1;
	DIEffect.rgdwAxes				= NULL;
	DIEffect.rglDirection			= NULL;
	DIEffect.lpEnvelope				= NULL;
	DIEffect.cbTypeSpecificParams	= sizeof(DICONSTANTFORCE);
	DIEffect.lpvTypeSpecificParams	= &DIConstantForceStruct;

	return pDIEffect->SetParameters(&DIEffect, DIEP_TYPESPECIFICPARAMS);
}

HRESULT SWFF_CreateRawAxisForceEffect(
	IN LPDIRECTINPUTDEVICE2 pDIDevice, 
	IN OUT LPDIRECTINPUTEFFECT * ppDIEffect,
	IN LONG lMagnitude,
	IN DWORD dwAxis)
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	if(!(dwAxis == X_AXIS || dwAxis == Y_AXIS))
		return SFERR_INVALID_PARAM;

	// Always clear return IPtr
	*ppDIEffect = NULL;

	LPDIRECTINPUTEFFECT  pRawForce;

	DICONSTANTFORCE DIConstantForceStruct;
	DIConstantForceStruct.lMagnitude = lMagnitude;

	DWORD rgdwAxes[1];
	if(dwAxis == X_AXIS)
		rgdwAxes[0] = _Analogue.ForceAxes[0];
	else
		rgdwAxes[0] = _Analogue.ForceAxes[1];

	LONG rglDirection[1];
	rglDirection[0] = 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffect.dwDuration				= INFINITE;
	DIEffect.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffect.dwGain					= 10000;
	DIEffect.dwTriggerButton		= DIEB_NOTRIGGER;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 1;
	DIEffect.rgdwAxes				= rgdwAxes;
	DIEffect.rglDirection			= rglDirection;
	DIEffect.lpEnvelope				= NULL;
	DIEffect.cbTypeSpecificParams	= sizeof(DICONSTANTFORCE);
	DIEffect.lpvTypeSpecificParams	= &DIConstantForceStruct;

	HRESULT hRet;
	hRet = pDIDevice->CreateEffect(GUID_ConstantForce, &DIEffect, &pRawForce, NULL);
	if(FAILED(hRet)) return hRet;

	*ppDIEffect = pRawForce;
	return SUCCESS;
}

// ----------------------------------------------------------------------------
// Function: 	SWFF_CreateROMEffect
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect	- Receives pointer to created effect
//				REFGUID refGUID					- GUID for ROM Effect
//				DWORD dwDuration				- uS
//				DWORD dwGain					- 1 to 10000
//				DWORD dwDirection				- 0 to 35999
//				LONG lButton					- Index of playback button, -1 for none
//
// Returns:		
// Algorithm:
// Comments:	Assumes valid GUID for the ROM Effect
// Note:		If unmodified ROM Effect, user has to pass
//				   DEFAULT_ROM_EFFECT_DURATION,  DEFAULT_ROM_EFFECT_GAIN
// ----------------------------------------------------------------------------
HRESULT SWFF_CreateROMEffect(
	IN LPDIRECTINPUTDEVICE2 pDIDevice, 
	IN OUT LPDIRECTINPUTEFFECT * ppDIEffect,
	IN REFGUID refGUID,
	IN DWORD dwDuration,		
	IN DWORD dwGain,
	IN DWORD dwDirection,		
	IN LONG lButton)			
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;
	// Always clear return IPtr
	*ppDIEffect = NULL;

	LPDIRECTINPUTEFFECT  pROMEffect = NULL;

	// Default NO Envelope
	DIENVELOPE DIEnvelopeStruct;				
	DIEnvelopeStruct.dwSize = sizeof(DIENVELOPE);
	DIEnvelopeStruct.dwAttackTime = 0;
	DIEnvelopeStruct.dwAttackLevel = 10000;
	DIEnvelopeStruct.dwFadeTime = 0;
	DIEnvelopeStruct.dwFadeLevel = 10000;

	// 2DOF
	DWORD rgdwAxes[2];
	rgdwAxes[0] = _Analogue.ForceAxes[0];
	rgdwAxes[1] = _Analogue.ForceAxes[1];

	LONG rglDirection[2];
	rglDirection[0] = dwDirection;
	rglDirection[1] = 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_POLAR;
	// Set Duration and Gain to use Default ROM Effect params unless overridden
	DIEffect.dwDuration				= dwDuration;	// can be DEFAULT_ROM_EFFECT_DURATION
	DIEffect.dwSamplePeriod			= DEFAULT_ROM_EFFECT_OUTPUTRATE;
	DIEffect.dwGain					= dwGain;		// can be DEFAULT_ROM_EFFECT_GAIN;	
	//
	DIEffect.dwTriggerButton		= lButton == -1 ? DIEB_NOTRIGGER : FIELD_OFFSET(DIJOYSTATE, rgbButtons) + lButton;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 2;
	DIEffect.rgdwAxes				= rgdwAxes;
	DIEffect.rglDirection			= rglDirection;
	DIEffect.lpEnvelope				= &DIEnvelopeStruct;
	DIEffect.cbTypeSpecificParams	= 0;
	DIEffect.lpvTypeSpecificParams	= NULL;

	HRESULT hRet = pDIDevice->CreateEffect(refGUID, &DIEffect, &pROMEffect, NULL);
	if(FAILED(hRet)) return hRet;

	*ppDIEffect = pROMEffect;
	return SUCCESS;
}

//DIERR_DEVICENOTREG  
//DIERR_DEVICEFULL  
//DIERR_INVALIDPARAM  
//DIERR_NOTINITIALIZED  

//
// ----------------------------------------------------------------------------
// Function: 	SWFF_CreatePeriodicEffect
// Purpose:		Creates a Periodic type Effect with specified params
// Parameters:  LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect	- Receives pointer to created effect
//				DWORD dwType			- Type of PERIODIC Effect (SINE | COSINE | ...)
//				DWORD dwDuration		- uS
//				DWORD dwPeriod			- uS
//				DWORD dwDirection		- 0 to 35999
//				DWORD dwMagnitude		- 0 to 10000
//				LONG lOffset			- Offset in -10000 to 10000
//				DWORD dwAttackTime		- Envelope Attack Time in uS
//				DWORD dwAttackLevel		- Envelope Attack Level in 0 to 10000
//				DWORD dwFadeTime		- Envelope Fade time in uS
//				DWORD dwFadeLevel		- Envelope Fade Level
//				LONG lButton			- Index of playback button, -1 for none
//
// Returns:
// Algorithm:	
// Comments:
// 
// ----------------------------------------------------------------------------
HRESULT SWFF_CreatePeriodicEffect(	IN LPDIRECTINPUTDEVICE2 pDIDevice,
								IN OUT LPDIRECTINPUTEFFECT* ppDIEffect,
								IN DWORD dwType,
								IN DWORD dwDuration,		
								IN DWORD dwPeriod,			
								IN DWORD dwDirection,		
								IN DWORD dwMagnitude,		
								IN LONG lOffset,			
								IN DWORD dwAttackTime,		
								IN DWORD dwAttackLevel,		
								IN DWORD dwFadeTime,		
								IN DWORD dwFadeLevel,		
								IN LONG lButton)			
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;
	// Always clear return IPtr
	*ppDIEffect = NULL;

	// type-specific stuff
	DWORD dwPhase = 0;
	GUID guid;
	switch(dwType)
	{
		case SINE:
			guid = GUID_Sine;
			break;
		case COSINE:
			guid = GUID_Sine;
			dwPhase = 9000;
			break;
		case SQUARE_HIGH:
			guid = GUID_Square;
			break;
		case SQUARE_LOW:
			guid = GUID_Square;
			dwPhase = 18000;
			break;
		case TRIANGLE_UP:
			guid = GUID_Triangle;
			break;
		case TRIANGLE_DOWN:
			guid = GUID_Triangle;
			dwPhase = 18000;
			break;
		case SAWTOOTH_UP:
			guid = GUID_SawtoothUp;
			break;
		case SAWTOOTH_DOWN:
			guid = GUID_SawtoothDown;
			break;
		default:
			// illegal
			break;
	}

	DIPERIODIC DIPeriodicStruct;
	DIPeriodicStruct.dwMagnitude = dwMagnitude;
	DIPeriodicStruct.lOffset = lOffset;
	DIPeriodicStruct.dwPhase = dwPhase;
	DIPeriodicStruct.dwPeriod = dwPeriod;

	DIENVELOPE DIEnvelopeStruct;
	DIEnvelopeStruct.dwSize = sizeof(DIENVELOPE);
	DIEnvelopeStruct.dwAttackTime = dwAttackTime;
	DIEnvelopeStruct.dwAttackLevel = dwAttackLevel;
	DIEnvelopeStruct.dwFadeTime = dwFadeTime;
	DIEnvelopeStruct.dwFadeLevel = dwFadeLevel;

	DWORD rgdwAxes[2];
	rgdwAxes[0] = _Analogue.ForceAxes[0];
	rgdwAxes[1] = _Analogue.ForceAxes[1];

	LONG rglDirection[2];
	rglDirection[0] = dwDirection;
	rglDirection[1] = 0;

	DIEFFECT DIEffectStruct;
	DIEffectStruct.dwSize					= sizeof(DIEFFECT);
	DIEffectStruct.dwFlags					= DIEFF_OBJECTIDS | DIEFF_POLAR;
	DIEffectStruct.dwDuration				= dwDuration;
	DIEffectStruct.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffectStruct.dwGain					= 10000;
	DIEffectStruct.dwTriggerButton			= lButton == -1 ? DIEB_NOTRIGGER : FIELD_OFFSET(DIJOYSTATE, rgbButtons) + lButton;
	DIEffectStruct.dwTriggerRepeatInterval	= 0;
	DIEffectStruct.cAxes					= 2;
	DIEffectStruct.rgdwAxes					= rgdwAxes;
	DIEffectStruct.rglDirection				= rglDirection;
	DIEffectStruct.lpEnvelope				= &DIEnvelopeStruct;
	DIEffectStruct.cbTypeSpecificParams		= sizeof(DIPeriodicStruct);
	DIEffectStruct.lpvTypeSpecificParams	= &DIPeriodicStruct;

	HRESULT hResult;
	hResult = pDIDevice->CreateEffect(guid, &DIEffectStruct, ppDIEffect, NULL);

	return hResult;
}

// ----------------------------------------------------------------------------
// Function: 	SWFF_CreateSpringEffect
// Purpose:		Creates a Spring type Effect with specified params
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect	- Receives pointer to created effect
//				DWORD dwDuration				- Duration in uS
//				LONG lKx						- X-Axis K Coefficient in -10000 to 10000
//				LONG lCenterx					- X-Axis Center in -10000 to 10000
//				LONG lKy						- Y-Axis K Coefficient in -10000 to 10000
//				LONG lCentery					- Y-Axis Center in -10000 to 10000
//				LONG lButton					- Index of playback button, -1 for none
//
// Returns:
// Algorithm:	
// Comments:
//			To create a 1D spring, set the lKx or lKy parameter to 0
//			To create a 2D spring, set both lKx and lKy parameter to non-zero
//				or set both lFx and lFy to zero
//  
// ----------------------------------------------------------------------------
//DEADCODE RDH 23/05/99 HRESULT SWFF_CreateSpringEffect(	IN LPDIRECTINPUTDEVICE2 pDIDevice,
//DEADCODE RDH 23/05/99 							IN OUT LPDIRECTINPUTEFFECT* ppDIEffect,
//DEADCODE RDH 23/05/99 							IN DWORD dwDuration,
//DEADCODE RDH 23/05/99 							IN LONG lKx,
//DEADCODE RDH 23/05/99 							IN LONG lCenterx,
//DEADCODE RDH 23/05/99 							IN LONG lKy,
//DEADCODE RDH 23/05/99 							IN LONG lCentery,
//DEADCODE RDH 23/05/99 							IN LONG lButton)
//DEADCODE RDH 23/05/99 {
//DEADCODE RDH 23/05/99 	if(pDIDevice == NULL || ppDIEffect == NULL)
//DEADCODE RDH 23/05/99 		return SFERR_INVALID_PARAM;
//DEADCODE RDH 23/05/99 	
//DEADCODE RDH 23/05/99 	// Always clear return IPtr
//DEADCODE RDH 23/05/99 	*ppDIEffect = NULL;
//DEADCODE RDH 23/05/99 
//DEADCODE RDH 23/05/99 	HRESULT hResult = SWFF_CreateConditionEffect(pDIDevice,
//DEADCODE RDH 23/05/99 											ppDIEffect,
//DEADCODE RDH 23/05/99 											SPRING,
//DEADCODE RDH 23/05/99 											dwDuration,
//DEADCODE RDH 23/05/99 											lKx, lCenterx,
//DEADCODE RDH 23/05/99 											lKy, lCentery,
//DEADCODE RDH 23/05/99 											lButton);
//DEADCODE RDH 23/05/99 
//DEADCODE RDH 23/05/99 	return hResult;
//DEADCODE RDH 23/05/99 }
//DEADCODE RDH 23/05/99 
//DEADCODE RDH 23/05/99 HRESULT SWFF_CreateDamperEffect(	IN LPDIRECTINPUTDEVICE2 pDIDevice,
//DEADCODE RDH 23/05/99 							IN OUT LPDIRECTINPUTEFFECT* ppDIEffect,
//DEADCODE RDH 23/05/99 							IN DWORD dwDuration,
//DEADCODE RDH 23/05/99 							IN LONG lKx,
//DEADCODE RDH 23/05/99 							IN LONG lCenterx,
//DEADCODE RDH 23/05/99 							IN LONG lKy,
//DEADCODE RDH 23/05/99 							IN LONG lCentery,
//DEADCODE RDH 23/05/99 							IN LONG lButton)
//DEADCODE RDH 23/05/99 {
//DEADCODE RDH 23/05/99 	if(pDIDevice == NULL || ppDIEffect == NULL)
//DEADCODE RDH 23/05/99 		return SFERR_INVALID_PARAM;
//DEADCODE RDH 23/05/99 	
//DEADCODE RDH 23/05/99 	// Always clear return IPtr
//DEADCODE RDH 23/05/99 	*ppDIEffect = NULL;
//DEADCODE RDH 23/05/99 
//DEADCODE RDH 23/05/99 	HRESULT hResult = SWFF_CreateConditionEffect(pDIDevice,
//DEADCODE RDH 23/05/99 											ppDIEffect,
//DEADCODE RDH 23/05/99 											DAMPER,
//DEADCODE RDH 23/05/99 											dwDuration,
//DEADCODE RDH 23/05/99 											lKx, lCenterx,
//DEADCODE RDH 23/05/99 											lKy, lCentery,
//DEADCODE RDH 23/05/99 											lButton);
//DEADCODE RDH 23/05/99 
//DEADCODE RDH 23/05/99 	return hResult;
//DEADCODE RDH 23/05/99 }
//DEADCODE RDH 23/05/99 
//DEADCODE RDH 23/05/99 
// Set Periodic function by DBM
HRESULT SWFF_SetPeriodic(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN DWORD dwMagnitude,
	IN DWORD lOffset,
	IN DWORD dwPhase,
	IN DWORD dwPeriod)
{
	if(pDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	DIEFFECT thisEffect = { sizeof(DIEFFECT) };
	DIPERIODIC DIPeriodicStruct;
	DIPeriodicStruct.dwMagnitude=dwMagnitude;
	DIPeriodicStruct.lOffset=lOffset;
	DIPeriodicStruct.dwPhase=dwPhase;
	DIPeriodicStruct.dwPeriod=dwPeriod;

	thisEffect.cbTypeSpecificParams		= sizeof(DIPeriodicStruct);
	thisEffect.lpvTypeSpecificParams	= &DIPeriodicStruct;

	return pDIEffect->SetParameters(&thisEffect, DIEP_TYPESPECIFICPARAMS);
}

// ----------------------------------------------------------------------------
// Function: 	SWFF_CreateConditionEffect
// Purpose:		Creates a Condition type Effect with specified params
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect	- Receives pointer to created effect
//				DWORD dwType					- SPRING | INERTIA | DAMPER | FRICTION
//				DWORD dwDuration				- Duration in uS
//				LONG lXCoefficient				- Coefficient in -10000 to 10000
//				LONG lXOffset					- Offset in -10000 to 10000
//				LONG lYCoefficient				- Coefficient in -10000 to 10000
//				LONG lYOffset					- Offset in -10000 to 10000
//				LONG lButton					- Index of playback button, -1 for none
// Returns:
// Algorithm:	
// Comments:
//			To create a 1D Friction, set the lFx or lFy parameter to 0
//			To create a 2D Friction, set both lFx and lFy parameter to non-zero
//				or set both lFx and lFy to zero
// 
// ----------------------------------------------------------------------------
HRESULT SWFF_CreateConditionEffect(	
	IN LPDIRECTINPUTDEVICE2 pDIDevice,
	IN OUT LPDIRECTINPUTEFFECT* ppDIEffect,
	IN DWORD dwType,
	IN DWORD dwDuration,
	IN LONG lXCoefficient,
	IN LONG lXOffset,
	IN LONG lYCoefficient,
	IN LONG lYOffset,
	IN LONG lButton)
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	// Always clear return IPtr
	*ppDIEffect = NULL;

	GUID guid;
	switch(dwType)
	{
		case SPRING:		  //this one for us!
			guid = GUID_Spring;
			break;
		case INERTIA:
			guid = GUID_Inertia;
			break;
		case DAMPER:
			guid = GUID_Damper;
			break;
		case FRICTION:
			guid = GUID_Friction;
			break;
		default:
			break;
	}

	DICONDITION DIConditionStruct[2];
	DIConditionStruct[0].lOffset				= lXOffset;
	DIConditionStruct[0].lPositiveCoefficient	= lXCoefficient;
	DIConditionStruct[0].lNegativeCoefficient	= lXCoefficient;
	DIConditionStruct[0].dwPositiveSaturation	= 10000;
	DIConditionStruct[0].dwNegativeSaturation	= 10000;
	DIConditionStruct[0].lDeadBand				= 0;
	DIConditionStruct[1].lOffset				= lYOffset;
	DIConditionStruct[1].lPositiveCoefficient	= lYCoefficient;
	DIConditionStruct[1].lNegativeCoefficient	= lYCoefficient;
	DIConditionStruct[1].dwPositiveSaturation	= 10000;
	DIConditionStruct[1].dwNegativeSaturation	= 10000;
	DIConditionStruct[1].lDeadBand				= 0;

	DWORD rgdwAxes[2];
	int nAxisCount = 0;
	if(lXCoefficient != 0 && lYCoefficient==0)
	{
		rgdwAxes[nAxisCount] = _Analogue.ForceAxes[0];
		nAxisCount++;
	}
	else
	if(lYCoefficient != 0 && lXCoefficient == 0)
	{
		rgdwAxes[nAxisCount] = _Analogue.ForceAxes[1];
		nAxisCount++;
	}
	else
	{
		nAxisCount = 2;
		rgdwAxes[0] = _Analogue.ForceAxes[0];
		rgdwAxes[1] = _Analogue.ForceAxes[1];
	}
	DWORD cbTypeSpecificParams;
	PVOID pvTypeSpecificParams;
	if(nAxisCount == 1)
	{
		cbTypeSpecificParams = sizeof(DICONDITION[1]);
		if(lXCoefficient != 0)
			pvTypeSpecificParams = &DIConditionStruct[0];
		else
			pvTypeSpecificParams = &DIConditionStruct[1];
	}
	else
	{
		cbTypeSpecificParams = sizeof(DICONDITION[2]);
		pvTypeSpecificParams = &DIConditionStruct[0];
	}

	LONG rglDirection[2];
	rglDirection[0] = 1;//was 0
	rglDirection[1] = 0;

	DIEFFECT DIEffectStruct;
	DIEffectStruct.dwSize					= sizeof(DIEFFECT);
	DIEffectStruct.dwFlags					= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffectStruct.dwDuration				= dwDuration;
	DIEffectStruct.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffectStruct.dwGain					= 10000;
	DIEffectStruct.dwTriggerButton			= lButton == -1 ? DIEB_NOTRIGGER : FIELD_OFFSET(DIJOYSTATE, rgbButtons) + lButton;
	DIEffectStruct.dwTriggerRepeatInterval	= 0;
	DIEffectStruct.cAxes					= nAxisCount;
	DIEffectStruct.rgdwAxes					= rgdwAxes;
	DIEffectStruct.rglDirection				= rglDirection;
	DIEffectStruct.lpEnvelope				= NULL;
	DIEffectStruct.cbTypeSpecificParams		= cbTypeSpecificParams;
	DIEffectStruct.lpvTypeSpecificParams	= pvTypeSpecificParams;

	HRESULT hResult;
	hResult = pDIDevice->CreateEffect(guid, &DIEffectStruct, ppDIEffect, NULL);

	return hResult;
}

// ----------------------------------------------------------------------------
// Function: 	SWFF_DestroyAllEffects
// Purpose:		Destroys all created effects
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
// Returns:
// Algorithm:	
// Comments:
// 
// ----------------------------------------------------------------------------
BOOL CALLBACK DIEnumAndDestroyCreatedEffectsProc(LPDIRECTINPUTEFFECT pDIEffect, LPVOID lpvRef)
{
	pDIEffect->Release();

	return DIENUM_CONTINUE;
}
HRESULT SWFF_DestroyAllEffects(
	IN LPDIRECTINPUTDEVICE2 pDIDevice)
{
	HRESULT hResult;

	if(pDIDevice == NULL)
		return SFERR_INVALID_PARAM;

	hResult = pDIDevice->EnumCreatedEffectObjects(DIEnumAndDestroyCreatedEffectsProc, NULL, 0);

	return hResult;
}

