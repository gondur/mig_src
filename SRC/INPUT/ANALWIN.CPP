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
//Filename       analwin.cpp
//System         
//Author         Andrew McRae
//Date           Fri 5 July 1996
//Description    
//------------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
//#define	DIRECTINPUT_VERSION 0x0300
#include	"analogue.h"
#include	<dinput.h>
#include	<windows.h>
#include	<windowsx.h>
//#include	<mmsystem.h>
#include	"monotxt.h"
#include	<stdio.h>

// Global Structure
// Cannot include Windows header files in Analouge.h
//JOYINFOEX JoyInfoEx;
//JOYINFOEX JoyInfoExbut;
//JOYCAPS	JoyCaps;
UINT	JoyID;
DeviceI Dummyinst;
Device  Dummyinst2;
DIJOYSTATE      js;

static int	srcount=4;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DllMain
//Author		Jim Taylor
//Date			Mon 12 May 1997
//
//Description	It's a DLL!
//
//Inputs		Double indirect pointer to main prog linked in ALALPUB
//				main prog Module name and date string
//
//Returns		IF ERROR:		Module name and date string
//				IF SUCCESS:		Modifies pointer to jump table
//
//------------------------------------------------------------------------------
HINSTANCE hWndMain=0;
int	WINAPI	DllMain(HINSTANCE hInstance,DWORD fdxReason,PVOID pvRes)
{
	if (!hWndMain)
		hWndMain=hInstance;
	return TRUE;
}

extern "C" __declspec (dllexport)	string	CALLBACK	DEVICEHOOK(int ** d,char* idstr)
{
//	_asm {INT 3}

	if (_stricmp(idstr,DeviceI::stubstart2()))
	{
//		_asm {INT 3}
		return DeviceI::stubstart2();
	}

	DeviceS *s=&Dummyinst;	//points to DOS jump table virtual table
	DeviceS *t=(DeviceS*)d;
	char* smem=**(char***)s;	//assumes virtual table is @ 0
	char* tmem=**(char***)t;
	//do some checking, please!
//	for (int i=-16;++i;)
//		if (*(smem+i)!=*(tmem+i))
//		{
//			_asm {INT 3}
//			return DeviceI::stubstart2();
//		}
//	while (*(int*)(tmem+i)!=*(int*)"ROWA")	i++;
//	if (*(int*)(smem+i)!=*(int*)"ROWA")
//	{
//		_asm {INT 3}
//		return DeviceI::stubstart2();
//	}
	*d=*(int**)&Dummyinst2;
	return NULL;		//GOOD!
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Initialise
//Author		Jim Taylor
//Date			Thu 21 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
LPDIRECTINPUT  g_lpdi=NULL;
LPDIRECTINPUTDEVICE pdev=NULL;
LPDIRECTINPUTDEVICE pdevT=NULL;
LPDIRECTINPUTDEVICE2 pdev2=NULL;
DIDEVCAPS	capabilities={sizeof(DIDEVCAPS_DX3)};
//------------------------------------------------------------------------------
BOOL FAR PASCAL InitJoystickInput(LPCDIDEVICEINSTANCE pdinst,
                                  LPVOID pvRef)
{
	if (pdevT)
		pdevT->Release();
	pdevT=NULL;

	//these can be doen as parameters to the enumerate...
	if (GET_DIDEVICE_TYPE(pdinst->dwDevType)!=DIDEVTYPE_JOYSTICK)
		return DIENUM_CONTINUE;
	if (g_lpdi->GetDeviceStatus(pdinst->guidInstance)!=DI_OK)
		return DIENUM_CONTINUE;

	// create the DirectInput joystick device 
	if (g_lpdi->CreateDevice(pdinst->guidInstance,&pdevT, NULL) != DI_OK)
		return DIENUM_CONTINUE;
	//try for ver 2

	HRESULT hr;
	hr = pdevT->QueryInterface(IID_IDirectInputDevice2,(void **) &pdev2);
	if (!SUCCEEDED(hr))
	{
		pdev2=NULL;
		if ((pdevT->SetDataFormat(&c_dfDIJoystick) != DI_OK))
			return DIENUM_CONTINUE;
//	if(pdevT->SetCooperativeLevel(hWndMain,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
  //		return DIENUM_CONTINUE;
		pdev=pdevT;
	}
	else
	{
		if ((pdev2->SetDataFormat(&c_dfDIJoystick) != DI_OK))
			return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}
//------------------------------------------------------------------------------
Bool ReaquireInput()
{
	HRESULT hRes;
	
	// if we have a current device 
	// acquire the device 
	if (pdev2)
		hRes = IDirectInputDevice_Acquire(pdev2);
	else
	if (pdev)
		hRes = IDirectInputDevice_Acquire(pdev);
	else
		return FALSE;
	// The call above is a macro that expands to: 
	// g_pdevCurrent->lpVtbl->Acquire(g_pdevCurrent); 

	if (SUCCEEDED(hRes))
	{
		// acquisition successful 
		return TRUE;
	}
	else
	{
		// acquisition failed 
		return FALSE;
	}
}

//------------------------------------------------------------------------------
Bool	InitStick()
{
	HRESULT        hr;
	 
	hr = DirectInputCreate(hWndMain, 0x500, &g_lpdi, NULL);
	if (!FAILED(hr))
	{
		g_lpdi->EnumDevices(DIDEVTYPE_JOYSTICK,
  		                         InitJoystickInput, g_lpdi, DIEDFL_ATTACHEDONLY);
	}
	if (!pdev && !pdev2)
	{
		if (g_lpdi)
			g_lpdi->Release();
		hr = DirectInputCreate(hWndMain, 0x300, &g_lpdi, NULL);
		g_lpdi->EnumDevices(DIDEVTYPE_JOYSTICK,
  		                         InitJoystickInput, g_lpdi, DIEDFL_ATTACHEDONLY);
	}
	
	if (!pdev && !pdev2)
	{
		if (pdevT)
			pdevT->Release();
		pdevT=NULL;
		return FALSE;
	}
	if (!ReaquireInput())
	{
	 	pdev->Release();
		return FALSE;
	}

										  
	if (pdev2)
		pdev2->GetCapabilities(&capabilities);
	else
		pdev->GetCapabilities(&capabilities);

	return TRUE;

}
//------------------------------------------------------------------------------

Bool	Device::Initialise(UByte*const  workspace,Axis	axes[])
{
	devicename=JOYSTICK_DEVICE_NAME;
//DeadCode ARM 09Jul96 	return(TRUE);

//DeadCode JIM 02Jun97 	static ULong firsttimein = 0;
//DeadCode JIM 02Jun97 
//DeadCode JIM 02Jun97 	if (firsttimein == 0)
//DeadCode JIM 02Jun97 		activeaxes = 0;
//DeadCode JIM 02Jun97 
//DeadCode JIM 02Jun97 	firsttimein++;
//DeadCode JIM 02Jun97 
	// Joystick Caps
	InitStick();
	return TRUE;

//	MMRESULT	mmrJoyCaps;

}

Bool	Device::LoadGame(UByte*const  workspace,Axis	axes[])
{
	return(TRUE);
}

Bool	Device::CloseDown(UByte*const  workspace)
{
	if (pdev2)
		pdev2->Release();
	if (pdevT)
	{
		pdevT->Unacquire();
		pdevT->Release();
	}

	if (g_lpdi)
		g_lpdi->Release();
	pdev2=NULL;
	pdev=pdevT=NULL;
	g_lpdi=NULL;
	return(TRUE);
}

//***************** UPDATE HERE ********************

// THIS IS THE NEW CODE


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreCalib
//Author		Jim Taylor
//Date			Thu 21 Mar 1996
//
//Description	prepare for calibration...
//				Flag all axes to be calibrated as ae_med.
//				Only expecting 1 4 axis stick, so only expecting
//				mutually exclusive input calls.
//				Could accept more, but not yet.
//
//				First stick is usually Aileron/Elevator, but can also be mapped to
//				UI X/Y, without extra calibration.
//				If first is mapped to Aileron/Elevator or UI and the second is
//				mapped to rudder, collective, throttle, or coolie
//				then it is all done on one screen.
//				If mapped elsewhere then second stick is done as second screen.
//				I admit that this looks horrendous.
//
//Inputs		activeaxes
//
//Returns		axisconfigpages + all axes are named
//
//------------------------------------------------------------------------------
void	Device::PreCalib(UByte*const  workspace,Axis	axes[],axisconfigpages& pages)
{

	if (!InitStick())
	{
		pages[0][0]=AU_ILLEGAL;
		pages[0][1]=AU_ILLEGAL;
		pages[0][2]=AU_ILLEGAL;
		pages[0][3]=AU_ILLEGAL;
		devicename=TEXT_JOYSTICKDISABLED;
		activeaxes=0;
		return;
	}
	srcount=1;
	AxisUses 	x=AU_MIN,
				mainaxis=AU_ILLEGAL,
				axisx2=AU_ILLEGAL,
				axisy2=AU_ILLEGAL,
				axis2=AU_ILLEGAL;


	for (x=AU_MIN;x<=AU_MAX;x++)
		if (activeaxes[x])
		{
			axes[x].status=AE_MED;
		}

	if (activeaxes[AU_AILERON])
	{
		mainaxis=AU_AILERON;
		if (activeaxes[AU_UI_X])
		{
			axes[AU_UI_X].status=AE_AUTO;
			axes[AU_UI_Y].status=AE_AUTO;
		}
	}
	elseif (activeaxes[AU_UI_X])
		mainaxis=AU_UI_X;
	if (mainaxis!=AU_ILLEGAL)
	{	//poss 1 or 2 stick
		if (activeaxes[AU_RUDDER])
			axisx2=AU_RUDDER;
		elseif (activeaxes[AU_COLLECTIVE])
			axisx2=AU_COLLECTIVE;
		if (activeaxes[AU_COOLIEHAT])
			if (activeaxes[AU_THROTTLE])
			{
				axisy2=AU_THROTTLE;
				axes[AU_COOLIEHAT].status=AE_AUTO;
			}
			else
				axisy2=AU_COOLIEHAT;
		elseif (activeaxes[AU_THROTTLE])
			axisy2=AU_THROTTLE;
	}
	else
		for (x=AU_MIN;x<=AU_MAX;)
		{	//main can be any 2some
			if (activeaxes[x] && activeaxes[(AxisUses)(x+1)] && x!=mainaxis)
				mainaxis=x;
			x++;
			x++;
		}			
	if (axisx2==AU_ILLEGAL && axisy2==AU_ILLEGAL)
		for (x=AU_MIN;x<=AU_MAX;)
		{
			if (activeaxes[x] && activeaxes[(AxisUses)(x+1)] && x!=mainaxis)
				axis2=x;
			x++;
			x++;
		}
	//ok.. at this point.. mainaxis goes on page 0
	//axisx2 and axisy2 also go on main screen (if set)
	//axis2 goes on page 1 (if set)
	//as the (if set) is the same flag I can do some of it blind:
	pages[0][0]=mainaxis;
	pages[0][1]=(AxisUses)(mainaxis+1);
	pages[0][2]=axisx2;
	pages[0][3]=axisy2;
	if (axis2!=AU_ILLEGAL)
	{
		pages[1][0]=axis2;
		pages[1][1]=(AxisUses)(axis2+1);
		pages[2][0]=AU_ILLEGAL;
		pages[2][1]=AU_ILLEGAL;
		pages[2][2]=AU_ILLEGAL;
		pages[2][3]=AU_ILLEGAL;
	}
	else
	{
		pages[1][0]=AU_ILLEGAL;
		pages[1][1]=AU_ILLEGAL;
	}
	pages[1][2]=AU_ILLEGAL;
	pages[1][3]=AU_ILLEGAL;

	//need to fill in the text:

	if (mainaxis!=AU_ILLEGAL)
	{
		axes[mainaxis].axisname=	JOYSTICK_X_NAME;
		axes[mainaxis].centerreq=	JOYSTICK_X_CENTER;
		axes[mainaxis].extremereq=	JOYSTICK_X_EXTREME;
		axes[mainaxis].minname=		JOYSTICK_X_MIN;
		axes[mainaxis].maxname=		JOYSTICK_X_MAX;

		axes[mainaxis+1].axisname=	JOYSTICK_Y_NAME;
		axes[mainaxis+1].centerreq=TEXT_NULL;
		axes[mainaxis+1].extremereq=TEXT_NULL;
		axes[mainaxis+1].minname=	JOYSTICK_Y_MIN;
		axes[mainaxis+1].maxname=	JOYSTICK_Y_MAX;
	}

	if (axisx2!=AU_ILLEGAL)
	{
		axes[axisx2].axisname=	RUDDER_NAME	;
		axes[axisx2].centerreq=RUDDER_CENTER	;
		axes[axisx2].extremereq=RUDDER_EXTREME;
		axes[axisx2].minname=	RUDDER_MIN	;
		axes[axisx2].maxname=	RUDDER_MAX	;
	}
	if (axisy2!=AU_ILLEGAL)
		if (axisy2==AU_COOLIEHAT)
		{
			axes[axisy2].axisname=	COOLIE_NAME	;
			axes[axisy2].centerreq=COOLIE_CENTER	;
			axes[axisy2].extremereq=COOLIE_EXTREME;
			axes[axisy2].minname=	TEXT_NULL;
			axes[axisy2].maxname=	COOLIE_MAX	;
		}
		else
		{
			axes[axisy2].axisname=	TROTTLE_NAME	;
			axes[axisy2].centerreq=TROTTLE_CENTER	;
			axes[axisy2].extremereq=TROTTLE_EXTREME;
			axes[axisy2].minname=	TEXT_NULL;
			axes[axisy2].maxname=	TROTTLE_MAX	;
		}
	if (axis2!=AU_ILLEGAL)
	{
		axes[axis2].axisname=	JOYSTICK2_X_NAME	;
		axes[axis2].centerreq=	JOYSTICK2_X_CENTER	;
		axes[axis2].extremereq=	JOYSTICK2_X_EXTREME;
		axes[axis2].minname=	JOYSTICK_X_MIN	;
		axes[axis2].maxname=	JOYSTICK_X_MAX	;

		axes[axis2+1].axisname=	JOYSTICK2_X_NAME;
		axes[axis2+1].centerreq=TEXT_NULL;
		axes[axis2+1].extremereq=TEXT_NULL;
		axes[axis2+1].minname=	JOYSTICK_Y_MIN;
		axes[axis2+1].maxname=	JOYSTICK_Y_MAX;
	}
	LastButtons[0]=0;
	LastButtons[1]=0;
	LastButtons[2]=0;
	if (axis2!=AU_ILLEGAL)
		LastButtons[3]=0x0101*mainaxis+0x01010000*axis2+0x01000100;
	else
		LastButtons[3]=	0x0101*mainaxis+0x0100+
						0x00010000*axisx2+0x01000000*axisy2;

	if (axisy2==AU_COOLIEHAT && (capabilities.dwPOVs>0))
	{
		axes[AU_COOLIEHAT].status=AE_AUTO;
		axes[AU_COOLIEHAT].position=32768;
		LastButtons[3]|=AU_ILLEGAL<<24;
	}
//	JoyInfoEx.dwFlags = (JOY_RETURNBUTTONS + JOY_RETURNCENTERED + JOY_RETURNPOV + JOY_RETURNX + JOY_RETURNY)
  //			+ (activeaxes[AU_RUDDER]?JOY_RETURNR:0)
	//		+ (activeaxes[AU_THROTTLE]?JOY_RETURNZ:0);
					
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalibCenter
//Author		Jim Taylor
//Date			Thu 21 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalibCenter
//Author		Jim Taylor
//Date			Thu 21 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Device::CalibCenter(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
{
	srcount=1;
	if (ReadHWPos(workspace,axes,reqaxes,&LastButtons[2]))
	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
	{
		Axis	&axisx=axes[x];
		if (reqaxes[x])
		{
			if (	axisx.position>5 ||	x==AU_THROTTLE || x==AU_COOLIEHAT)
			{
				if (axisx.status==AE_MED)
				{
					axisx.scale1=
						axisx.scale2=
							axisx.centre=
								axisx.min=
									axisx.max=
								 		axisx.position;
					axisx.status=AE_CORRECT;
					axisx.position=0;
				}
				else
				{
					axisx.centre=axisx.position;
					if (axisx.Position()>axisx.Scale2())
						axisx.scale2=axisx.position;
					elseif (axisx.Position()<axisx.Scale1())
						axisx.scale1=axisx.position;
					if (x==AU_THROTTLE || x==AU_COOLIEHAT)
						if (axisx.Scale2()-axisx.Scale1()>140)
						{
							axisx.position=((axisx.Position()-axisx.Scale1())*32767L)
											/(axisx.Scale2()-axisx.Scale1());
						}
						else
							axisx.position=0;
					else
						if (axisx.Scale2()-axisx.Scale1()>140)
						{
							axisx.position=((axisx.Position()-axisx.Scale1())*65534L)
											/(axisx.Scale2()-axisx.Scale1())
											-32767;
						}
						else
							axisx.position=0;
				}
			}
			else
			{
				axisx.status=AE_MED;
				axisx.position=0;
			}
		}
	}
	return(ReadButtons(workspace,axes,reqaxes,&LastButtons[2],NULL));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalibExtreme
//Author		Jim Taylor
//Date			Thu 21 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Device::CalibExtreme(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
{
	srcount=1;
	if (ReadHWPos(workspace,axes,reqaxes,&LastButtons[2]))
	{
	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
		if (reqaxes[x] && axes[x].status!=AE_AUTO)
		{
			Axis*	axis=	&axes[x];
			if (axis->Position()>axis->Max())
				axis->max=axis->position;
			elseif (axis->Position()<axis->Min())
				axis->min=axis->position;

			if (axis->Max()>axis->Centre()+10)
				axis->scale2=((axis->Max()-axis->Centre())>>1)+1;
			else
				axis->scale2=0;

			if (axis->Min()+10<axis->Centre())
				axis->scale1=((axis->Centre()-axis->Min())>>1)+1;
			else
				axis->scale1=0;

			if (x!=AU_COOLIEHAT && x!=AU_THROTTLE)
			{
				if (!axis->scale2)		//this way 'round 'cos throttle 1 sided
					axis->status=AE_HIGH;
				if (!axis->scale1)
					axis->status=AE_LOW;
				elseif ((axis->scale2>>1)>axis->scale1)
					axis->status=AE_HIGH|AE_WARNING;
				elseif ((axis->scale1>>1)>axis->scale2)
					axis->status=AE_LOW|AE_WARNING;
				else
					axis->status=AE_CORRECT;
			}
			else
			{
				if (axis->scale2 || axis->scale1)
					axis->status=AE_CORRECT;
				else
					axis->status=AE_HIGH;
				if (axis->Centre()-axis->Min()>axis->Max()-axis->Centre())
					axis->max=axis->centre+1;
				else
					axis->min=axis->centre-1;
			}
		}
	if (	(reqaxes[AU_COOLIEHAT])				//may be buttons hat
		&&  ((LastButtons[2]&3)==3)	   				//if 2 buttons pressed
//TempCode JIM 23Jul96 		&&	(axes[AU_COOLIEHAT].status==AE_HIGH)//especially if unread
		)										//then we have buttons hat
		if (LastButtons[2]!=0x0f)
			LastButtons[2]=0;
		else
		{
			axes[AU_COOLIEHAT].status=AE_AUTO;
			axes[AU_COOLIEHAT].position=32768;

//DeadCode JIM 22Jul96 			if ((LastButtons[3]&0xff000000)==(AU_COOLIEHAT<<24))
			LastButtons[3]|=AU_ILLEGAL<<24;
		}
	ScaleHWPos(workspace,axes,reqaxes);
	}
	return(ReadButtons(workspace,axes,reqaxes,&LastButtons[2],NULL));
}

//-------------------------------------------------------------------
Bool	Device::ReadPosition(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,keytests* keyboard)
{
	if (	reqaxes[(AxisUses)(LastButtons[3]&255)]
		||	reqaxes[AU_AILERON]
		||	reqaxes[AU_UI_X]
		||	reqaxes[AU_THROTTLE]
		||	reqaxes[AU_RUDDER]
		||	reqaxes[AU_COOLIEHAT]
		)
	{
		if (ReadHWPos(workspace,axes,reqaxes,&LastButtons[2]))
			ScaleHWPos(workspace,axes,reqaxes);
	}
	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
		if (x!=AU_COOLIEHAT && reqaxes[x])
			if (axes[x].status==AE_AUTO)
				if (x&1)
					axes[x].position=axes[(LastButtons[3]>>8)&255].position;
				else
					axes[x].position=axes[LastButtons[3]&255].position;
	return(ReadButtons(workspace,axes,reqaxes,&LastButtons[2],keyboard));
}
//-------------------------------------------------------------------
//not used in windows... ah! the good old days!
void	ASM_InsB(UByte* buffer,UWord port,UByte pattern,int maxcount=5000);
#pragma	aux	ASM_InsB	=				\
		"mov	ecx,20"					\
		"sub	ebx,ecx"	   			\
		"l1:"							\
		"in		al,dx"		   			\
		"stos  	byte ptr es:[edi]"		\
		"test	al,ah"					\
		"loop	l1"						\
		"mov	cx,bx"					\
		"l2:"							\
		"in		al,dx"					\
		"stos	byte ptr es:[edi]"		\
		"test	al,ah"					\
		"loopnz	l2"						\
		"mov 	byte ptr es:[edi],0"		\
		parm	[edi] [dx] [ah] [ebx]	\
		modify	[ecx]

UWord table[]={			\
		'K'+'E'*256,
		'Y'+'S'*256,
		100,		/*fire*/		\
		92,		/*b2*/		\
		148,	/*b3*/		\
		164,		/*b4*/		\
		78,		/*coolieL - compatible with dos version*/		\
		72,		/*coolieB*/		\
		76,		/*coolieR*/		\
		74,		/*coolieF*/		\
		0,		/*b5*/		\
		0,		/*b6*/		\
		0,		/*b7*/		\
		0,		/*b8*/		\
		0,		/*b9*/		\
		0,		/*b10*/		\
		0,		/*b11*/		\
		0,		/*b12*/		\
		0,		/*b13*/		\
		0,		/*b14*/		\
		0,		/*b15*/		\
		0,		/*b16*/		\
		0,		/*b17*/		\
		0,		/*b18*/		\
		0,		/*b19*/		\
		0,		/*b20*/		\
		0,		/*b21*/		\
		0,		/*b22*/		\
		0,		/*b23*/		\
		0,		/*b24*/		\
		0,		/*b25*/		\
		0,		/*b26*/		\
		0,		/*b27*/		\
		0};		/*b28 - others not supported!*/	


UWord*	selftable()
{
	return table;
}
;
UWord tune[]={2*8,3*8,1000,3};	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadHWPos
//Author		Jim Taylor
//Date			Fri 10 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Device::ReadHWPos(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons)
{
	if (--srcount<=0)
	{
		LARGE_INTEGER	t1;
		QueryPerformanceCounter(&t1);
		HRESULT hres;
		if (pdev2)
		{
			hres = IDirectInputDevice2_Poll(pdev2);
			if (hres==DIERR_INPUTLOST)
			{
				ReaquireInput();
				hres = IDirectInputDevice2_Poll(pdev2);
			}
			hres = IDirectInputDevice_GetDeviceState(pdev2,sizeof(DIJOYSTATE), &js);
			if (hres==DIERR_INPUTLOST)
			{
				ReaquireInput();
				hres = IDirectInputDevice_GetDeviceState(pdev2,sizeof(DIJOYSTATE), &js);
			}
		}
		else
		{
			hres = IDirectInputDevice_GetDeviceState(pdev,sizeof(DIJOYSTATE), &js);
			if (hres==DIERR_INPUTLOST)
			{
				ReaquireInput();
				hres = IDirectInputDevice_GetDeviceState(pdev,sizeof(DIJOYSTATE), &js);
			}
		}
		if (hres==DI_OK)
		{
			LARGE_INTEGER	t2;
			QueryPerformanceCounter(&t2);
			int t=t2.LowPart-t1.LowPart;
			if(t && QueryPerformanceFrequency(&t2))
			{
				t=t2.LowPart/t;				//this gives parts of a second
				if (t*2<tune[2])			//if 1/500 sec ==> 2ms then big slugdown
					tune[0]=tune[1]+tune[1];
				else
				if (t<tune[2] && tune[0]<tune[1])
				{							//if 1/1000 sec ==> 1ms then small slugdown
					static UWord p=0;
					int i;
					tune[0]=tune[1];
				}
			}
//DeadCode D 18Dec97 			if (--tune[0]>60000)
//DeadCode D 18Dec97 				tune[0]=2<<tune[3];

			srcount=tune[0]>>tune[3];
			tune[0]-=srcount;
			if (tune[0]>60000)
				tune[0]=2<<tune[3];

			
			if ((LastButtons[3]&255)!=AU_ILLEGAL)
				axes[(LastButtons[3])&255].position = (SWord)((ULong)js.lX / 4);
			if (((LastButtons[3]>>8)&255)!=AU_ILLEGAL)
				axes[(LastButtons[3]>>8)&255].position = (SWord)((ULong)js.lY / 4);
			if (((LastButtons[3]>>24)&255)!=AU_ILLEGAL)
				axes[(LastButtons[3]>>24)&255].position = (SWord)((ULong)js.lZ / 4);	// Throttle input
			if (((LastButtons[3]>>16)&255)!=AU_ILLEGAL)
				axes[(LastButtons[3]>>16)&255].position = (SWord)((ULong)js.lRz / 4);	// Rudder Input

			*newbuttons=0;
			int i=0,b=1;
			for (;i<capabilities.dwButtons;i++,b+=b)
				if (js.rgbButtons[i]&0x80)
					*newbuttons+=b;
			for (int h=1;h<capabilities.dwPOVs;h++)
			{
				breakif(i>32-8-4);
				int PV=((ULong)js.rgdwPOV[0]>>12);				//DAW 11Jun97
				if (PV<8)
				{
					*newbuttons+=b<<PV;
				}
				i+=8;
				b<<=8;
			}
			return(TRUE);	//Do scale hardware read
		}
		else
		{
			srcount=0;
//			*(char*)0xb0000+=1;
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}
//DeadCode JIM 09May97 Bool	Device::ReadHWPos(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons)
//DeadCode JIM 09May97 {
//DeadCode JIM 30Apr97 	UByte AxisBits=0,AB2,*ws=workspace;
//DeadCode JIM 30Apr97 	if ((LastButtons[3]&255)!=AU_ILLEGAL)
//DeadCode JIM 30Apr97 		AxisBits|=3;
//DeadCode JIM 30Apr97 	if (((LastButtons[3]>>16)&255)!=AU_ILLEGAL)
//DeadCode JIM 30Apr97 		AxisBits|=4;
//DeadCode JIM 30Apr97 	if (((LastButtons[3]>>24)&255)!=AU_ILLEGAL)
//DeadCode JIM 30Apr97 		AxisBits|=8;
//DeadCode JIM 30Apr97 	{	_disable();	
//DeadCode JIM 30Apr97 	ASM_OutDxAl(0x201,0);
//DeadCode JIM 30Apr97 	ASM_InsB(workspace,0x201,AxisBits);
//DeadCode JIM 30Apr97 	}	_enable();
//DeadCode JIM 30Apr97 
//DeadCode JIM 30Apr97 	int i;
//DeadCode JIM 30Apr97 	for (i=0;i<20;i++)	ws[i]|=ws[20];
//DeadCode JIM 30Apr97 
//DeadCode JIM 30Apr97 	i=0;
//DeadCode JIM 30Apr97 	AxisBits=*ws;
//DeadCode JIM 30Apr97 	while (AxisBits)
//DeadCode JIM 30Apr97 	{
//DeadCode JIM 30Apr97 		while (AxisBits==*++ws)	i++;
//DeadCode JIM 30Apr97 		AB2=AxisBits^*ws;
//DeadCode JIM 30Apr97 		AxisBits=*ws;
//DeadCode JIM 30Apr97 		if (AB2&1)
//DeadCode JIM 30Apr97 			if ((LastButtons[3]&255)!=AU_ILLEGAL)
//DeadCode JIM 30Apr97 				axes[LastButtons[3]&255].position=i;
//DeadCode JIM 30Apr97 		if (AB2&2)
//DeadCode JIM 30Apr97 			if (((LastButtons[3]>>8)&255)!=AU_ILLEGAL)
//DeadCode JIM 30Apr97 				axes[(LastButtons[3]>>8)&255].position=i;
//DeadCode JIM 30Apr97 		if (AB2&4)
//DeadCode JIM 30Apr97 			if (((LastButtons[3]>>16)&255)!=AU_ILLEGAL)
//DeadCode JIM 30Apr97 				axes[(LastButtons[3]>>16)&255].position=i;
//DeadCode JIM 30Apr97 		if (AB2&8)
//DeadCode JIM 30Apr97 			if (((LastButtons[3]>>24)&255)!=AU_ILLEGAL)
//DeadCode JIM 30Apr97 				axes[(LastButtons[3]>>24)&255].position=i;
//DeadCode JIM 30Apr97 	}
//DeadCode JIM 30Apr97 	*newbuttons=((*workspace&0xf0)>>4)^0x0f;
//DeadCode JIM 09May97 
//DeadCode JIM 09May97 	return(TRUE);	//nonsense info
//DeadCode JIM 09May97 }


Bool	Device::ScaleHWPos(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
{
	ULong z=LastButtons[3];
	repeat
	{
		AxisUses x=(AxisUses) (z&255);
		z>>=8;
		SLong position;
		position=axes[x].Position()-axes[x].Centre();
		if (axes[x].status!=AE_AUTO)
		if (position==0)
			axes[x].position=0;
		else
			if (position>0)
				if (axes[x].scale2)
					if (axes[x].Position()>=axes[x].Max())
						axes[x].position=32767;
					else
						axes[x].position=(position<<14)/axes[x].scale2;
				else
					axes[x].position=0;
			else
				if (axes[x].scale1)
					if (axes[x].Position()<=axes[x].Min())
						axes[x].position=-32767;
					else
						axes[x].position=(position<<14)/axes[x].scale1;
				else
					axes[x].position=0;
	}while (z);

	//move from readbuttons. Gets done when read rate reduced!
//DeadCode DAW 19Dec97 	*(char*)0xb0000='0'+(LastButtons[2]&15);
	LastButtons[2]=((LastButtons[2]&-0x10)<<4)+(LastButtons[2]&0x0f); //gap for coolie hat
//DeadCode DAW 19Dec97 	*(char*)0xb0002='0'+(LastButtons[2]&15);

	if (activeaxes[AU_COOLIEHAT])
		if (axes[AU_COOLIEHAT].status!=AE_AUTO)
		{
			int bn=((axes[AU_COOLIEHAT].position>>12)+1)>>1;
			if (bn)
				if (bn>0)
					LastButtons[2]|=1<<(bn+3);							//RDH 22Jul96
				else
					LastButtons[2]|=1<<(3-bn);							//RDH 22Jul96
		}
		else
		if(capabilities.dwPOVs)
		{
			int PV=((ULong)js.rgdwPOV[0]>>13);				//DAW 11Jun97
//DeadCode DAW 19Dec97 			*(char*)0xb0010='0'+PV;
			if (PV<4)
			{
				LastButtons[2]=(LastButtons[2]&-16)+(1<<(((PV+1)&3)+4));					//JIM 09Jun97
			}
		}
		else
		{
			if ((LastButtons[2]&3)==3)
				LastButtons[2]=1<<(((LastButtons[2]>>2)&3)+4);
		}

	return(TRUE);
}

Bool	Device::ReadButtons(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons,keytests* keyboard)
{
	//convert coolie hat to buttons:

	int	butcomp=*newbuttons^LastButtons[0];

	//convert buttons to key presses
	int bitnum=0;
	int bitval=1;

	if (keyboard && butcomp)
		if (keyboard->ModeIs3D)	
			while (bitnum<32)
			{
				if (butcomp&bitval)
					if (*newbuttons&bitval)
						(keyboard->*keyboard->KeyFake3dThru)((KeyVal3D)table[bitnum],TRUE,TRUE);
					else
						(keyboard->*keyboard->KeyFake3dThru)((KeyVal3D)table[bitnum],FALSE,FALSE);	//wrong...
				bitnum++;			
				bitval+=bitval;
			}
		else
		{	//UI mode. Generate LMB and RMB key presses?

		}
	LastButtons[0]=*newbuttons;
	return (*newbuttons&0x0f)?TRUE:FALSE;	//coolie buttons disabled
}




	STUBEND(Device)
