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

#include	"analogue.h"

#include	<windows.h>
#include	<windowsx.h>
#include	<mmsystem.h>
extern "C"
{
#include	"i-force.h"
};			

//DeadCode JIM 30Apr97 #include "i86.h"												//RDH 03Jun96
//DeadCode JIM 30Apr97 #pragma	intrinsic(_disable,_enable)

// Global Structure
// Cannot include Windows header files in Analouge.h
JOYINFOEX JoyInfoEx;
JOYCAPS	JoyCaps;
UINT	JoyID;
DeviceI Dummyinst;
Device  Dummyinst2;


int	WINAPI	DllMain(HINSTANCE hInstance,DWORD fdxReason,PVOID pvRes)
{
	return TRUE;
}

extern "C" __declspec (dllexport)	string	CALLBACK	DEVICEHOOK(int ** d,char* idstr)
{
	if (strcmp(idstr,DeviceI::stubstart2()))
		return DeviceI::stubstart2();

	DeviceS *s=&Dummyinst;	//points to DOS jump table virtual table
	DeviceS *t=(DeviceS*)d;
	char* smem=**(char***)s;	//assumes virtual table is @ 0
	char* tmem=**(char***)t;
	//do some checking, please!
	for (int i=-16;++i;)
		if (*(smem+i)!=*(tmem+i))
			return DeviceI::stubstart2();
	while (*(int*)(tmem+i)!=*(int*)"ROWA")	i++;
	if (*(int*)(smem+i)!=*(int*)"ROWA")
		return DeviceI::stubstart2();

	*d=*(int**)&Dummyinst2;
	return NULL;		//GOOD!
}


static Bool	IForceOK=FALSE;
static int port=0;
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
Bool	Device::Initialise(UByte*const  workspace,Axis	axes[])
{
	while (port<5)
	{
	 	SetJoystickPort(port);
		breakif (InitStick(NULL));
		CloseStick();
		port++;
	}

	char	b[4];
	if (port!=5)
		GetStickStatus(b);

	if (port!=5 && (b[0]&8))
	{
		IForceOK=TRUE;
		ClearForces();
		EnableForces();
	}
	


	devicename=JOYSTIC_SPARE_0;
//DeadCode ARM 09Jul96 	return(TRUE);

	static ULong firsttimein = 0;

	if (firsttimein == 0)
		activeaxes = 0;

	firsttimein++;

	// Joystick Caps

	MMRESULT	mmrJoyCaps;




	// Joystick Init

	MMRESULT	mmrJoyPos;

	JoyInfoEx.dwSize = sizeof (JOYINFOEX);
	JoyInfoEx.dwFlags = (JOY_RETURNBUTTONS + JOY_RETURNCENTERED + JOY_RETURNX + JOY_RETURNY + JOY_RETURNZ + JOY_RETURNR + JOY_RETURNPOV);

	if (joyGetNumDevs())
	{
		mmrJoyPos = joyGetPosEx (JOYSTICKID1, &JoyInfoEx);
		if (mmrJoyPos == JOYERR_NOERROR)
			JoyID = JOYSTICKID1;
		else
		{
			mmrJoyPos = joyGetPosEx (JOYSTICKID2, &JoyInfoEx);
			if (mmrJoyPos == JOYERR_NOERROR)
				JoyID = JOYSTICKID2;
			else
				return FALSE;
		}
		mmrJoyCaps = joyGetDevCaps(JoyID, &JoyCaps, sizeof (JOYCAPS));
		if (mmrJoyCaps != JOYERR_NOERROR)
			return FALSE;

	}
	else
		return FALSE;

	return TRUE;

}

Bool	Device::LoadGame(UByte*const  workspace,Axis	axes[])
{
	return(TRUE);
}

Bool	Device::CloseDown(UByte*const  workspace)
{
	ClearForces();
	CloseStick();
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

	if (IForceOK==FALSE && port!=5)
	{
		char	b[4];
		GetStickStatus(b);

		if (b[0]&8)
		{
			IForceOK=TRUE;
			ClearForces();
			EnableForces();
		}
	}

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

		axes[mainaxis+1].axisname=	JOYSTICK_X_NAME;
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

	if (axisy2==AU_COOLIEHAT && (JoyCaps.wCaps&JOYCAPS_HASPOV))
	{
		axes[AU_COOLIEHAT].status=AE_AUTO;
		axes[AU_COOLIEHAT].position=32768;
		LastButtons[3]|=AU_ILLEGAL<<24;
	}

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
	ReadHWPos(workspace,axes,reqaxes,&LastButtons[2]);
	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
	{
		Axis	&axisx=axes[x];
		if (reqaxes[x])
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
						if (axisx.Scale2()-axisx.Scale1()>40)
							axisx.position=((axisx.Position()-axisx.Scale1())*32767L)
											/(axisx.Scale2()-axisx.Scale1());
						else
							axisx.position=0;
					else
						if (axisx.Scale2()-axisx.Scale1()>40)
							axisx.position=((axisx.Position()-axisx.Scale1())*65534L)
											/(axisx.Scale2()-axisx.Scale1())
											-32767;
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
	ReadHWPos(workspace,axes,reqaxes,&LastButtons[2]);
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
				if (axis->scale2 || axis->scale1)
					axis->status=AE_CORRECT;
				else
					axis->status=AE_HIGH;
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
	if (IForceOK==FALSE)
		if (reqaxes[AU_AILERON] && axes[AU_AILERON].status==AE_CORRECT)
		{
			axes[AU_AILERON].axisname=	JOYSTIC_SPARE_0;
			axes[AU_AILERON].minname=	JOYSTIC_SPARE_1;
		 	axes[AU_AILERON].status=	AE_LOW|AE_WARNING;
		}

	return(ReadButtons(workspace,axes,reqaxes,&LastButtons[2],NULL));
}

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
		ReadHWPos(workspace,axes,reqaxes,&LastButtons[2]);
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

#ifdef __WATCOMC__
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
#else
#ifdef __MSVC__
void	ASM_InsB(UByte* buffer,UWord port,UByte pattern,int maxcount=5000)
{
	SLong	retval;
    __asm
    {
		mov edi,buffer;
		mov dx,port;
		mov ah,pattern;
		mov ebx,maxcount;
		mov	ecx,20;
		sub	ebx,ecx;
		l1:;
		in		al,dx;
		stos  	byte ptr es:[edi];
		test	al,ah;
		loop	l1;
		mov	cx,bx;
		l2:;
		in		al,dx;
		stos	byte ptr es:[edi];
		test	al,ah;
		loopnz	l2;
		mov 	byte ptr es:[edi],0;
    }
}

#endif
#endif

int letsseeit=0;

Bool	Device::ReadHWPos(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons)
{

	if (joyGetPosEx (JoyID, &JoyInfoEx) == JOYERR_NOERROR)
	{

		if ((LastButtons[3]&255)!=AU_ILLEGAL)
			axes[(LastButtons[3])&255].position = (SWord)((ULong)JoyInfoEx.dwXpos / 4);
		if (((LastButtons[3]>>8)&255)!=AU_ILLEGAL)
			axes[(LastButtons[3]>>8)&255].position = (SWord)((ULong)JoyInfoEx.dwYpos / 4);
		if (((LastButtons[3]>>24)&255)!=AU_ILLEGAL)
			axes[(LastButtons[3]>>24)&255].position = (SWord)((ULong)JoyInfoEx.dwZpos / 4);	// Throttle input
		if (((LastButtons[3]>>16)&255)!=AU_ILLEGAL)
			axes[(LastButtons[3]>>16)&255].position = (SWord)((ULong)JoyInfoEx.dwRpos / 4);	// Rudder Input

		//send forces:
		if (IForceOK)
		{
			if (axes[AU_FB_CTRLFORCE].position)
			{

				Axis&	axis=	axes[AU_FB_CTRLFORCE];
				if(++axis.position==0)
				{
					axis.FB_LX()=0;
					axis.FB_LY()=0;
					axis.FB_LZ()=0;
					VectorForceClear();
				}
				if (axis.position>0)
				{
					XYVectorForce(axis.FB_RZ()/327,axis.FB_RX()/327);
					axis.position=1-axis.position;
				}
			}
			if (axes[AU_FB_CTRLSTIFF].position)
			{
				Axis&	axis=	axes[AU_FB_CTRLSTIFF];
				axis.position=0;
				XSpring(axis.FB_RZ()/327,axis.FB_LX()/327,axis.FB_LX()/327);
				YSpring(axis.FB_RY()/327,axis.FB_LZ()/327,axis.FB_LZ()/327);
			}
//DeadCode ARM 27May97 			axes[AU_FB_CTRLSHAKE].position=(letsseeit+=20);

			if (axes[AU_FB_CTRLSHAKE].position)
			{
				Axis&	axis=	axes[AU_FB_CTRLSHAKE];
				if (axis.position>1)
				{
					XVibrationClear();
					YVibrationClear();
					Buffeting(axis.position/327);
				}
				else
				{
					BuffetingClear();
					XVibration(axis.FB_LX()/327,axis.FB_LX()/327,axis.FB_RX());
					YVibration(axis.FB_LZ()/327,axis.FB_LZ()/327,axis.FB_RZ());
				}
				axis.position=0;
			}

		}
	}
	else
		return FALSE;

	*newbuttons = JoyInfoEx.dwButtons;

	return(TRUE);	//nonsense info
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
		if (position && axes[x].status!=AE_AUTO)
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
	return(TRUE);
}

extern	UWord*	selftable();
#ifdef __WATCOMC__
#pragma aux selftable=			\
		"call past"				\
		"db	'K','E','Y','S'"	\
		"dw	100"		/*fire*/		\
		"dw	92"		/*b2*/		\
		"dw	148"		/*b3*/		\
		"dw	164"		/*b4*/		\
		"dw	78"		/*coolieL - compatible with dos version*/		\
		"dw	72"		/*coolieB*/		\
		"dw	76"		/*coolieR*/		\
		"dw	74"		/*coolieF*/		\
		"dw	0"		/*b5*/		\
		"dw	0"		/*b6*/		\
		"dw	0"		/*b7*/		\
		"dw	0"		/*b8*/		\
		"dw	0"		/*b9*/		\
		"dw	0"		/*b10*/		\
		"dw	0"		/*b11*/		\
		"dw	0"		/*b12*/		\
		"dw	0"		/*b13*/		\
		"dw	0"		/*b14*/		\
		"dw	0"		/*b15*/		\
		"dw	0"		/*b16*/		\
		"dw	0"		/*b17*/		\
		"dw	0"		/*b18*/		\
		"dw	0"		/*b19*/		\
		"dw	0"		/*b20*/		\
		"dw	0"		/*b21*/		\
		"dw	0"		/*b22*/		\
		"dw	0"		/*b23*/		\
		"dw	0"		/*b24*/		\
		"dw	0"		/*b25*/		\
		"dw	0"		/*b26*/		\
		"dw	0"		/*b27*/		\
		"dw	0"		/*b28 - others not supported!*/		\
		"past:"				\
		"pop	eax"		\
		"add	eax,4"		\
		value	[eax]
#else
#ifdef __MSVC__
inline UWord*	selftable()
{
	UWord*	retval;
    __asm
    {
		call past;			
		db('K') db('E') db('Y') db('S')
		dw	(100)		/*fire*/		
		dw	(92)		/*b2*/		
		dw	(148)		/*b3*/	
		dw	(164)		/*b4*/		
		dw	(78)		/*coolieL - compatible with dos version*/		
		dw	(72)		/*coolieB*/		
		dw	(76)		/*coolieR*/		
		dw	(74)		/*coolieF*/		
		dw	(0)		/*b5*/		
		dw	(0)		/*b6*/	
		dw	(0)		/*b7*/		
		dw	(0)		/*b8*/	
		dw	(0)		/*b9*/		
		dw	(0)		/*b10*/		
		dw	(0)		/*b11*/	
		dw	(0)		/*b12*/		
		dw	(0)		/*b13*/		
		dw	(0)		/*b14*/		
		dw	(0)		/*b15*/		
		dw	(0)		/*b16*/		
		dw	(0)		/*b17*/		
		dw	(0)		/*b18*/		
		dw	(0)		/*b19*/		
		dw	(0)		/*b20*/		
		dw	(0)		/*b21*/		
		dw	(0)		/*b22*/		
		dw	(0)		/*b23*/		
		dw	(0)		/*b24*/		
		dw	(0)		/*b25*/		
		dw	(0)		/*b26*/		
		dw	(0)		/*b27*/		
		dw	(0)		/*b28 - others not supported!*/		
		past:;
		pop	eax;
		add	eax,4;
		mov retval,eax;
    }
    return retval;
}

#endif
#endif

Bool	Device::ReadButtons(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons,keytests* keyboard)
{
	//convert coolie hat to buttons:

	*newbuttons=((*newbuttons&-0x10)<<4)+(*newbuttons&0x0f); //gap for coolie hat

	if (activeaxes[AU_COOLIEHAT])
		if (JoyCaps.wCaps&JOYCAPS_HASPOV)
		{
			int PV=((ULong)JoyInfoEx.dwPOV>>13);
			if (PV<4)
				*newbuttons+=1<<(((PV+1)&3)+3);
		}
		else
		if (axes[AU_COOLIEHAT].status!=AE_AUTO)
		{
			int bn=((axes[AU_COOLIEHAT].position>>12)+1)>>1;
			if (bn)
				if (bn>0)
					*newbuttons|=1<<(bn+3);							//RDH 22Jul96
				else
					*newbuttons|=1<<(3-bn);							//RDH 22Jul96
		}
		else
		{
			if ((*newbuttons&3)==3)
				*newbuttons=1<<(((*newbuttons>>2)&3)+4);
		}
	int	butcomp=*newbuttons^LastButtons[0];

	//convert buttons to key presses
	int bitnum=0;
	int bitval=1;
	UWord*	table=selftable();

	if (keyboard && butcomp)
		if (!keyboard->ModeIs3D)	
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


// THIS IS THE OLD CODE
		
//TempCode ARM 04Oct96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode ARM 04Oct96 //Procedure		PreCalib
//TempCode ARM 04Oct96 //Author		Jim Taylor
//TempCode ARM 04Oct96 //Date			Thu 21 Mar 1996
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Description	prepare for calibration...
//TempCode ARM 04Oct96 //				Flag all axes to be calibrated as ae_med.
//TempCode ARM 04Oct96 //				Only expecting 1 4 axis stick, so only expecting
//TempCode ARM 04Oct96 //				mutually exclusive input calls.
//TempCode ARM 04Oct96 //				Could accept more, but not yet.
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //				First stick is usually Aileron/Elevator, but can also be mapped to
//TempCode ARM 04Oct96 //				UI X/Y, without extra calibration.
//TempCode ARM 04Oct96 //				If first is mapped to Aileron/Elevator or UI and the second is
//TempCode ARM 04Oct96 //				mapped to rudder, collective, throttle, or coolie
//TempCode ARM 04Oct96 //				then it is all done on one screen.
//TempCode ARM 04Oct96 //				If mapped elsewhere then second stick is done as second screen.
//TempCode ARM 04Oct96 //				I admit that this looks horrendous.
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Inputs		activeaxes
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Returns		axisconfigpages + all axes are named
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //------------------------------------------------------------------------------
//TempCode ARM 04Oct96 void	Device::PreCalib(UByte*const  workspace,Axis	axes[],axisconfigpages& pages)
//TempCode ARM 04Oct96 {
//TempCode ARM 04Oct96 	AxisUses 	x=AU_MIN,
//TempCode ARM 04Oct96 				mainaxis=AU_ILLEGAL,
//TempCode ARM 04Oct96 				axisx2=AU_ILLEGAL,
//TempCode ARM 04Oct96 				axisy2=AU_ILLEGAL,
//TempCode ARM 04Oct96 				axis2=AU_ILLEGAL;
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 	for (x=AU_MIN;x<=AU_MAX;x++)
//TempCode ARM 04Oct96 		if (activeaxes[x])
//TempCode ARM 04Oct96 		{
//TempCode ARM 04Oct96 			axes[x].status=AE_MED;
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 	if (activeaxes[AU_AILERON])
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		mainaxis=AU_AILERON;
//TempCode ARM 04Oct96 		if (activeaxes[AU_UI_X])
//TempCode ARM 04Oct96 		{
//TempCode ARM 04Oct96 			axes[AU_UI_X].status=AE_AUTO;
//TempCode ARM 04Oct96 			axes[AU_UI_Y].status=AE_AUTO;
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 	elseif (activeaxes[AU_UI_X])
//TempCode ARM 04Oct96 		mainaxis=AU_UI_X;
//TempCode ARM 04Oct96 	if (mainaxis!=AU_ILLEGAL)
//TempCode ARM 04Oct96 	{	//poss 1 or 2 stick
//TempCode ARM 04Oct96 		if (activeaxes[AU_RUDDER])
//TempCode ARM 04Oct96 			axisx2=AU_RUDDER;
//TempCode ARM 04Oct96 		elseif (activeaxes[AU_COLLECTIVE])
//TempCode ARM 04Oct96 			axisx2=AU_COLLECTIVE;
//TempCode ARM 04Oct96 		if (activeaxes[AU_COOLIEHAT])
//TempCode ARM 04Oct96 			if (activeaxes[AU_THROTTLE])
//TempCode ARM 04Oct96 			{
//TempCode ARM 04Oct96 				axisy2=AU_THROTTLE;
//TempCode ARM 04Oct96 				axes[AU_COOLIEHAT].status=AE_AUTO;
//TempCode ARM 04Oct96 			}
//TempCode ARM 04Oct96 			else
//TempCode ARM 04Oct96 				axisy2=AU_COOLIEHAT;
//TempCode ARM 04Oct96 		elseif (activeaxes[AU_THROTTLE])
//TempCode ARM 04Oct96 			axisy2=AU_THROTTLE;
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 	else
//TempCode ARM 04Oct96 		for (x=AU_MIN;x<=AU_MAX;)
//TempCode ARM 04Oct96 		{	//main can be any 2some
//TempCode ARM 04Oct96 			if (activeaxes[x] && activeaxes[(AxisUses)(x+1)] && x!=mainaxis)
//TempCode ARM 04Oct96 				mainaxis=x;
//TempCode ARM 04Oct96 			x++;
//TempCode ARM 04Oct96 			x++;
//TempCode ARM 04Oct96 		}			
//TempCode ARM 04Oct96 	if (axisx2==AU_ILLEGAL && axisy2==AU_ILLEGAL)
//TempCode ARM 04Oct96 		for (x=AU_MIN;x<=AU_MAX;)
//TempCode ARM 04Oct96 		{
//TempCode ARM 04Oct96 			if (activeaxes[x] && activeaxes[(AxisUses)(x+1)] && x!=mainaxis)
//TempCode ARM 04Oct96 				axis2=x;
//TempCode ARM 04Oct96 			x++;
//TempCode ARM 04Oct96 			x++;
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 	//ok.. at this point.. mainaxis goes on page 0
//TempCode ARM 04Oct96 	//axisx2 and axisy2 also go on main screen (if set)
//TempCode ARM 04Oct96 	//axis2 goes on page 1 (if set)
//TempCode ARM 04Oct96 	//as the (if set) is the same flag I can do some of it blind:
//TempCode ARM 04Oct96 	pages[0][0]=mainaxis;
//TempCode ARM 04Oct96 	pages[0][1]=(AxisUses)(mainaxis+1);
//TempCode ARM 04Oct96 	pages[0][2]=axisx2;
//TempCode ARM 04Oct96 	pages[0][3]=axisy2;
//TempCode ARM 04Oct96 	if (axis2!=AU_ILLEGAL)
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		pages[1][0]=axis2;
//TempCode ARM 04Oct96 		pages[1][1]=(AxisUses)(axis2+1);
//TempCode ARM 04Oct96 		pages[2][0]=AU_ILLEGAL;
//TempCode ARM 04Oct96 		pages[2][1]=AU_ILLEGAL;
//TempCode ARM 04Oct96 		pages[2][2]=AU_ILLEGAL;
//TempCode ARM 04Oct96 		pages[2][3]=AU_ILLEGAL;
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 	else
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		pages[1][0]=AU_ILLEGAL;
//TempCode ARM 04Oct96 		pages[1][1]=AU_ILLEGAL;
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 	pages[1][2]=AU_ILLEGAL;
//TempCode ARM 04Oct96 	pages[1][3]=AU_ILLEGAL;
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 	//need to fill in the text:
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 	if (mainaxis!=AU_ILLEGAL)
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		axes[mainaxis].axisname=	JOYSTICK_X_NAME;
//TempCode ARM 04Oct96 		axes[mainaxis].centerreq=	JOYSTICK_X_CENTER;
//TempCode ARM 04Oct96 		axes[mainaxis].extremereq=	JOYSTICK_X_EXTREME;
//TempCode ARM 04Oct96 		axes[mainaxis].minname=		JOYSTICK_X_MIN;
//TempCode ARM 04Oct96 		axes[mainaxis].maxname=		JOYSTICK_X_MAX;
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 		axes[mainaxis+1].axisname=	JOYSTICK_X_NAME;
//TempCode ARM 04Oct96 		axes[mainaxis+1].centerreq=TEXT_NULL;
//TempCode ARM 04Oct96 		axes[mainaxis+1].extremereq=TEXT_NULL;
//TempCode ARM 04Oct96 		axes[mainaxis+1].minname=	JOYSTICK_Y_MIN;
//TempCode ARM 04Oct96 		axes[mainaxis+1].maxname=	JOYSTICK_Y_MAX;
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 	if (axisx2!=AU_ILLEGAL)
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		axes[axisx2].axisname=	RUDDER_NAME	;
//TempCode ARM 04Oct96 		axes[axisx2].centerreq=RUDDER_CENTER	;
//TempCode ARM 04Oct96 		axes[axisx2].extremereq=RUDDER_EXTREME;
//TempCode ARM 04Oct96 		axes[axisx2].minname=	RUDDER_MIN	;
//TempCode ARM 04Oct96 		axes[axisx2].maxname=	RUDDER_MAX	;
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 	if (axisy2!=AU_ILLEGAL)
//TempCode ARM 04Oct96 		if (axisy2==AU_COOLIEHAT)
//TempCode ARM 04Oct96 		{
//TempCode ARM 04Oct96 			axes[axisy2].axisname=	COOLIE_NAME	;
//TempCode ARM 04Oct96 			axes[axisy2].centerreq=COOLIE_CENTER	;
//TempCode ARM 04Oct96 			axes[axisy2].extremereq=COOLIE_EXTREME;
//TempCode ARM 04Oct96 			axes[axisy2].minname=	TEXT_NULL;
//TempCode ARM 04Oct96 			axes[axisy2].maxname=	COOLIE_MAX	;
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 		else
//TempCode ARM 04Oct96 		{
//TempCode ARM 04Oct96 			axes[axisy2].axisname=	TROTTLE_NAME	;
//TempCode ARM 04Oct96 			axes[axisy2].centerreq=TROTTLE_CENTER	;
//TempCode ARM 04Oct96 			axes[axisy2].extremereq=TROTTLE_EXTREME;
//TempCode ARM 04Oct96 			axes[axisy2].minname=	TEXT_NULL;
//TempCode ARM 04Oct96 			axes[axisy2].maxname=	TROTTLE_MAX	;
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 	if (axis2!=AU_ILLEGAL)
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		axes[axis2].axisname=	JOYSTICK2_X_NAME	;
//TempCode ARM 04Oct96 		axes[axis2].centerreq=	JOYSTICK2_X_CENTER	;
//TempCode ARM 04Oct96 		axes[axis2].extremereq=	JOYSTICK2_X_EXTREME;
//TempCode ARM 04Oct96 		axes[axis2].minname=	JOYSTICK_X_MIN	;
//TempCode ARM 04Oct96 		axes[axis2].maxname=	JOYSTICK_X_MAX	;
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 		axes[axis2+1].axisname=	JOYSTICK2_X_NAME;
//TempCode ARM 04Oct96 		axes[axis2+1].centerreq=TEXT_NULL;
//TempCode ARM 04Oct96 		axes[axis2+1].extremereq=TEXT_NULL;
//TempCode ARM 04Oct96 		axes[axis2+1].minname=	JOYSTICK_Y_MIN;
//TempCode ARM 04Oct96 		axes[axis2+1].maxname=	JOYSTICK_Y_MAX;
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 	if (axis2!=AU_ILLEGAL)
//TempCode ARM 04Oct96 		LastButtons[3]=0x0101*mainaxis+0x01010000*axis2+0x01000100;
//TempCode ARM 04Oct96 	else
//TempCode ARM 04Oct96 		LastButtons[3]=	0x0101*mainaxis+0x0100+
//TempCode ARM 04Oct96 						0x00010000*axisx2+0x01000000*axisy2;
//TempCode ARM 04Oct96 }
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode ARM 04Oct96 //Procedure		CalibCenter
//TempCode ARM 04Oct96 //Author		Jim Taylor
//TempCode ARM 04Oct96 //Date			Thu 21 Mar 1996
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Description	
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Inputs		
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Returns	
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //------------------------------------------------------------------------------
//TempCode ARM 04Oct96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode ARM 04Oct96 //Procedure		CalibCenter
//TempCode ARM 04Oct96 //Author		Jim Taylor
//TempCode ARM 04Oct96 //Date			Thu 21 Mar 1996
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Description	
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Inputs		
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Returns	
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //------------------------------------------------------------------------------
//TempCode ARM 04Oct96 Bool	Device::CalibCenter(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
//TempCode ARM 04Oct96 {
//TempCode ARM 04Oct96 	ReadHWPos(workspace,axes,reqaxes,&LastButtons[2]);
//TempCode ARM 04Oct96 	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		Axis	&axisx=axes[x];
//TempCode ARM 04Oct96 		if (reqaxes[x])
//TempCode ARM 04Oct96 			if (	axisx.position>5 ||	x==AU_THROTTLE || x==AU_COOLIEHAT)
//TempCode ARM 04Oct96 			{
//TempCode ARM 04Oct96 				if (axisx.status==AE_MED)
//TempCode ARM 04Oct96 				{
//TempCode ARM 04Oct96 					axisx.scale1=
//TempCode ARM 04Oct96 						axisx.scale2=
//TempCode ARM 04Oct96 							axisx.centre=
//TempCode ARM 04Oct96 								axisx.min=
//TempCode ARM 04Oct96 									axisx.max=
//TempCode ARM 04Oct96 								 		axisx.position;
//TempCode ARM 04Oct96 					axisx.status=AE_CORRECT;
//TempCode ARM 04Oct96 					axisx.position=0;
//TempCode ARM 04Oct96 				}
//TempCode ARM 04Oct96 				else
//TempCode ARM 04Oct96 				{
//TempCode ARM 04Oct96 					axisx.centre=axisx.position;
//TempCode ARM 04Oct96 					if (axisx.position>axisx.scale2)
//TempCode ARM 04Oct96 						axisx.scale2=axisx.position;
//TempCode ARM 04Oct96 					elseif (axisx.position<axisx.scale1)
//TempCode ARM 04Oct96 						axisx.scale1=axisx.position;
//TempCode ARM 04Oct96 					if (x==AU_THROTTLE || x==AU_COOLIEHAT)
//TempCode ARM 04Oct96 						if (axisx.scale2-axisx.scale1>40)
//TempCode ARM 04Oct96 							axisx.position=((axisx.position-axisx.scale1)*32767L)
//TempCode ARM 04Oct96 											/(axisx.scale2-axisx.scale1);
//TempCode ARM 04Oct96 						else
//TempCode ARM 04Oct96 							axisx.position=0;
//TempCode ARM 04Oct96 					else
//TempCode ARM 04Oct96 						if (axisx.scale2-axisx.scale1>40)
//TempCode ARM 04Oct96 							axisx.position=((axisx.position-axisx.scale1)*65534L)
//TempCode ARM 04Oct96 											/(axisx.scale2-axisx.scale1)
//TempCode ARM 04Oct96 											-32767;
//TempCode ARM 04Oct96 						else
//TempCode ARM 04Oct96 							axisx.position=0;
//TempCode ARM 04Oct96 				}
//TempCode ARM 04Oct96 			}
//TempCode ARM 04Oct96 			else
//TempCode ARM 04Oct96 			{
//TempCode ARM 04Oct96 				axisx.status=AE_MED;
//TempCode ARM 04Oct96 				axisx.position=0;
//TempCode ARM 04Oct96 			}
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 	return(ReadButtons(workspace,axes,reqaxes,&LastButtons[2],NULL));
//TempCode ARM 04Oct96 }
//TempCode ARM 04Oct96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode ARM 04Oct96 //Procedure		CalibExtreme
//TempCode ARM 04Oct96 //Author		Jim Taylor
//TempCode ARM 04Oct96 //Date			Thu 21 Mar 1996
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Description	
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Inputs		
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //Returns	
//TempCode ARM 04Oct96 //
//TempCode ARM 04Oct96 //------------------------------------------------------------------------------
//TempCode ARM 04Oct96 Bool	Device::CalibExtreme(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
//TempCode ARM 04Oct96 {
//TempCode ARM 04Oct96 	ReadHWPos(workspace,axes,reqaxes,&LastButtons[2]);
//TempCode ARM 04Oct96 	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
//TempCode ARM 04Oct96 		if (reqaxes[x])
//TempCode ARM 04Oct96 		{
//TempCode ARM 04Oct96 			if (axes[x].position>axes[x].max)
//TempCode ARM 04Oct96 				axes[x].max=axes[x].position;
//TempCode ARM 04Oct96 			elseif (axes[x].position<axes[x].min)
//TempCode ARM 04Oct96 				axes[x].min=axes[x].position;
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 			if (axes[x].max>axes[x].centre+10)
//TempCode ARM 04Oct96 				axes[x].scale2=32767/(axes[x].max-axes[x].centre);
//TempCode ARM 04Oct96 			else
//TempCode ARM 04Oct96 				axes[x].scale2=0;
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 			if (axes[x].min+10<axes[x].centre)
//TempCode ARM 04Oct96 				axes[x].scale1=32767/(axes[x].centre-axes[x].min);
//TempCode ARM 04Oct96 			else
//TempCode ARM 04Oct96 				axes[x].scale1=0;
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 			if (x!=AU_COOLIEHAT && x!=AU_THROTTLE)
//TempCode ARM 04Oct96 			{
//TempCode ARM 04Oct96 				if (!axes[x].scale2)		//this way 'round 'cos throttle 1 sided
//TempCode ARM 04Oct96 					axes[x].status=AE_HIGH;
//TempCode ARM 04Oct96 				if (!axes[x].scale1)
//TempCode ARM 04Oct96 					axes[x].status=AE_LOW;
//TempCode ARM 04Oct96 				elseif (axes[x].scale2>2*axes[x].scale1)
//TempCode ARM 04Oct96 					axes[x].status=AE_LOW|AE_WARNING;
//TempCode ARM 04Oct96 				elseif (axes[x].scale1>2*axes[x].scale2)
//TempCode ARM 04Oct96 					axes[x].status=AE_HIGH|AE_WARNING;
//TempCode ARM 04Oct96 				else
//TempCode ARM 04Oct96 					axes[x].status=AE_CORRECT;
//TempCode ARM 04Oct96 			}
//TempCode ARM 04Oct96 			else
//TempCode ARM 04Oct96 				if (axes[x].scale2 || axes[x].scale1)
//TempCode ARM 04Oct96 					axes[x].status=AE_CORRECT;
//TempCode ARM 04Oct96 				else
//TempCode ARM 04Oct96 					axes[x].status=AE_HIGH;
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 	if (	(reqaxes[AU_COOLIEHAT])				//may be buttons hat
//TempCode ARM 04Oct96 		&&	(axes[AU_COOLIEHAT].status==AE_HIGH)//especially if unread
//TempCode ARM 04Oct96 		&&  (LastButtons[2]&3)	   				//if 2 buttons pressed
//TempCode ARM 04Oct96 		)										//then we have buttons hat
//TempCode ARM 04Oct96 		{
//TempCode ARM 04Oct96 			axes[AU_COOLIEHAT].status=AE_AUTO;
//TempCode ARM 04Oct96 			axes[AU_COOLIEHAT].position=32768;
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 	ScaleHWPos(workspace,axes,reqaxes);
//TempCode ARM 04Oct96 	return(ReadButtons(workspace,axes,reqaxes,&LastButtons[2],NULL));
//TempCode ARM 04Oct96 }
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 Bool	Device::ReadPosition(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,keytests* keyboard)
//TempCode ARM 04Oct96 {
//TempCode ARM 04Oct96 	if (	reqaxes[(AxisUses)(LastButtons[3]&255)]
//TempCode ARM 04Oct96 		||	reqaxes[AU_AILERON]
//TempCode ARM 04Oct96 		||	reqaxes[AU_UI_X]
//TempCode ARM 04Oct96 		||	reqaxes[AU_THROTTLE]
//TempCode ARM 04Oct96 		||	reqaxes[AU_RUDDER]
//TempCode ARM 04Oct96 		||	reqaxes[AU_COOLIEHAT]
//TempCode ARM 04Oct96 		)
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		ReadHWPos(workspace,axes,reqaxes,&LastButtons[2]);
//TempCode ARM 04Oct96 		ScaleHWPos(workspace,axes,reqaxes);
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
//TempCode ARM 04Oct96 		if (reqaxes[x])
//TempCode ARM 04Oct96 			if (axes[x].status==AE_AUTO)
//TempCode ARM 04Oct96 				if (x&1)
//TempCode ARM 04Oct96 					axes[x].position=axes[(LastButtons[3]>>8)&255].position;
//TempCode ARM 04Oct96 				else
//TempCode ARM 04Oct96 					axes[x].position=axes[LastButtons[3]&255].position;
//TempCode ARM 04Oct96 	return(ReadButtons(workspace,axes,reqaxes,&LastButtons[2],keyboard));
//TempCode ARM 04Oct96 }
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 void	ASM_InsB(UByte* buffer,UWord port,UByte pattern,int maxcount=5000);
//TempCode ARM 04Oct96 #pragma	aux	ASM_InsB	=				\
//TempCode ARM 04Oct96 		"mov	ecx,20"					\
//TempCode ARM 04Oct96 		"sub	ebx,ecx"	   			\
//TempCode ARM 04Oct96 		"l1:"							\
//TempCode ARM 04Oct96 		"in		al,dx"		   			\
//TempCode ARM 04Oct96 		"stos  	byte ptr es:[edi]"		\
//TempCode ARM 04Oct96 		"test	al,ah"					\
//TempCode ARM 04Oct96 		"loop	l1"						\
//TempCode ARM 04Oct96 		"mov	cx,bx"					\
//TempCode ARM 04Oct96 		"l2:"							\
//TempCode ARM 04Oct96 		"in		al,dx"					\
//TempCode ARM 04Oct96 		"stos	byte ptr es:[edi]"		\
//TempCode ARM 04Oct96 		"test	al,ah"					\
//TempCode ARM 04Oct96 		"loopnz	l2"						\
//TempCode ARM 04Oct96 		"mov 	byte ptr es:[edi],0"		\
//TempCode ARM 04Oct96 		parm	[edi] [dx] [ah] [ebx]	\
//TempCode ARM 04Oct96 		modify	[ecx]
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 Bool	Device::ReadHWPos(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons)
//TempCode ARM 04Oct96 {
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 	if (joyGetPosEx (JoyID, &JoyInfoEx) == JOYERR_NOERROR)
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		axes[(LastButtons[3])&255].position = (SWord)((ULong)JoyInfoEx.dwXpos / 32);
//TempCode ARM 04Oct96 		axes[(LastButtons[3]>>8)&255].position = (SWord)((ULong)JoyInfoEx.dwYpos / 32);
//TempCode ARM 04Oct96 		axes[(LastButtons[3]>>24)&255].position = (SWord)((ULong)JoyInfoEx.dwZpos / 32);	// Throttle input
//TempCode ARM 04Oct96 		axes[(LastButtons[3]>>16)&255].position = (SWord)((ULong)JoyInfoEx.dwRpos / 32);	// Rudder Input
//TempCode ARM 04Oct96 	}
//TempCode ARM 04Oct96 	else
//TempCode ARM 04Oct96 		return FALSE;
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 	*newbuttons = JoyInfoEx.dwButtons;
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 	return(TRUE);	//nonsense info
//TempCode ARM 04Oct96 }
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 Bool	Device::ScaleHWPos(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
//TempCode ARM 04Oct96 {
//TempCode ARM 04Oct96 	ULong z=LastButtons[3];
//TempCode ARM 04Oct96 	repeat
//TempCode ARM 04Oct96 	{
//TempCode ARM 04Oct96 		AxisUses x=(AxisUses) (z&255);
//TempCode ARM 04Oct96 		z>>=8;
//TempCode ARM 04Oct96 		SWord position;
//TempCode ARM 04Oct96 		position=axes[x].position-axes[x].centre;
//TempCode ARM 04Oct96 		if (position)
//TempCode ARM 04Oct96 			if (position>0)
//TempCode ARM 04Oct96 				if (axes[x].position>=axes[x].max)
//TempCode ARM 04Oct96 					axes[x].position=32767;
//TempCode ARM 04Oct96 				else
//TempCode ARM 04Oct96 					axes[x].position=position*axes[x].scale2;
//TempCode ARM 04Oct96 			else
//TempCode ARM 04Oct96 				if (axes[x].position<=axes[x].min)
//TempCode ARM 04Oct96 					axes[x].position=-32767;
//TempCode ARM 04Oct96 				else
//TempCode ARM 04Oct96 					axes[x].position=position*axes[x].scale1;
//TempCode ARM 04Oct96 	}while (z);
//TempCode ARM 04Oct96 	return(TRUE);
//TempCode ARM 04Oct96 }
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 Bool	Device::ReadButtons(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons,keytests* keyboard)
//TempCode ARM 04Oct96 {
//TempCode ARM 04Oct96 	if (activeaxes[AU_COOLIEHAT])
//TempCode ARM 04Oct96 		if (axes[AU_COOLIEHAT].status!=AE_AUTO)
//TempCode ARM 04Oct96 		{
//TempCode ARM 04Oct96 			int bn=((axes[AU_COOLIEHAT].position>>12)+1)>>1;
//TempCode ARM 04Oct96 			if (bn)
//TempCode ARM 04Oct96 				*newbuttons+=1<<(bn+4);
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 		else
//TempCode ARM 04Oct96 		{
//TempCode ARM 04Oct96 			if ((*newbuttons&3)==3)
//TempCode ARM 04Oct96 				*newbuttons=1<<(((*newbuttons>>2)&3)+4);
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 	int	butcomp=*newbuttons^LastButtons[0];
//TempCode ARM 04Oct96 	if (keyboard && butcomp)
//TempCode ARM 04Oct96 		if (keyboard->ModeIs3D)	
//TempCode ARM 04Oct96 		{	//3d mode. Generate key press, hold, or release events
//TempCode ARM 04Oct96 			if (butcomp&1)
//TempCode ARM 04Oct96 				if (*newbuttons&1)
//TempCode ARM 04Oct96 					//key pressed
//TempCode ARM 04Oct96 					(keyboard->*keyboard->KeyFake3dThru)(SHOOT,TRUE,TRUE);
//TempCode ARM 04Oct96 				else
//TempCode ARM 04Oct96 					//key released
//TempCode ARM 04Oct96 					(keyboard->*keyboard->KeyFake3dThru)(SHOOT,FALSE,FALSE);	//wrong...
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 		else
//TempCode ARM 04Oct96 		{	//UI mode. Generate LMB and RMB key presses
//TempCode ARM 04Oct96 
//TempCode ARM 04Oct96 		}
//TempCode ARM 04Oct96 	LastButtons[0]=*newbuttons;
//TempCode ARM 04Oct96 	return (*newbuttons&0x0f)?TRUE:FALSE;	//coolie buttons disabled
//TempCode ARM 04Oct96 }
//TempCode ARM 04Oct96 


	STUBEND(Device)

