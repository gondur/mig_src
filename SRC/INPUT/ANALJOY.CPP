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
//Filename       analjoy.cpp
//System         
//Author         Jim Taylor
//Date           Thu 14 Mar 1996
//Description    Analogue reading for DOS joystick
//				The basic calibration and scaling code should not need any work,
//				but the hardware reading may change to reflect different environments.
//
//				Input values between 0 and 65535 are scaled to -32767..0..32767
//				Inputs can range between:
//					left..centred..right
//					1..100..200			-	slow PC hardware 
//					1..1000..2000		-	typical pc hardware
//					1..3000..6000		-	fast pc hardware
//											- faster is h/w reader mod. anyway
//					1..32767..65536		-	typical windows driver
//
//				Scale1 and Scale2 are scale factors. 
//				For DOS they work ok as multipliers: d=1000*(s=32) --> 32K
//				But for windows it don't! For d=32K+, s=0!
//				So I am using divider factors:	d=1000*16K / (s=500) -> 32K
//				For windows:					d=32K+*16K / (s=16K+) -> 32K
//				For poor windows:				d=50K *16K / (s=25K) -> 32K
//				For poor DOS:					d=100 *16K / (s=50)  -> 32K
//
//------------------------------------------------------------------------------
#include	"analogue.h"
#include "i86.h"												//RDH 03Jun96
#pragma	intrinsic(_disable,_enable)
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
	devicename=JOYSTICK_DEVICE_NAME;
	return(TRUE);
}

Bool	Device::LoadGame(UByte*const  workspace,Axis	axes[])
{
	return(TRUE);
}

Bool	Device::CloseDown(UByte*const  workspace)
{
	return(TRUE);
}
		
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
void	ASM_InsB(UByte* buffer,UWord port,UByte pattern,int maxcount);
inline void	ASM_InsB(UByte* buffer,UWord port,UByte pattern,int maxcount=5000)
{
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


Bool	Device::ReadHWPos(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons)
{
	UByte AxisBits=0,AB2,*ws=workspace;
	if ((LastButtons[3]&255)!=AU_ILLEGAL)
		AxisBits|=3;
	if (((LastButtons[3]>>16)&255)!=AU_ILLEGAL)
		AxisBits|=4;
	if (((LastButtons[3]>>24)&255)!=AU_ILLEGAL)
		AxisBits|=8;
	{	_disable();	
	ASM_OutDxAl(0x201,0);
	ASM_InsB(workspace,0x201,AxisBits);
	}	_enable();

	int i;
	for (i=0;i<20;i++)	ws[i]|=ws[20];

	i=0;
	AxisBits=*ws;
	while (AxisBits)
	{
		while (AxisBits==*++ws)	i++;
		AB2=AxisBits^*ws;
		AxisBits=*ws;
		if (AB2&1)
			if ((LastButtons[3]&255)!=AU_ILLEGAL)
				axes[LastButtons[3]&255].position=i;
		if (AB2&2)
			if (((LastButtons[3]>>8)&255)!=AU_ILLEGAL)
				axes[(LastButtons[3]>>8)&255].position=i;
		if (AB2&4)
			if (((LastButtons[3]>>16)&255)!=AU_ILLEGAL)
				axes[(LastButtons[3]>>16)&255].position=i;
		if (AB2&8)
			if (((LastButtons[3]>>24)&255)!=AU_ILLEGAL)
				axes[(LastButtons[3]>>24)&255].position=i;
	}
	*newbuttons=((*workspace&0xf0)>>4)^0x0f;

	return(TRUE);	//nonsense info
}


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

//DeadCode DAW 09May97 Bool	Device::ReadButtons(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons,keytests* keyboard)
//DeadCode DAW 09May97 {
//DeadCode DAW 09May97 	if (activeaxes[AU_COOLIEHAT])
//DeadCode DAW 09May97 		if (axes[AU_COOLIEHAT].status!=AE_AUTO)
//DeadCode DAW 09May97 		{
//DeadCode DAW 09May97 			int bn=((axes[AU_COOLIEHAT].position>>12)+1)>>1;
//DeadCode DAW 09May97 			if (bn)
//DeadCode DAW 09May97 				if (bn>0)
//DeadCode DAW 09May97 					*newbuttons|=1<<(bn+3);							//RDH 22Jul96
//DeadCode DAW 09May97 				else
//DeadCode DAW 09May97 					*newbuttons|=1<<(3-bn);							//RDH 22Jul96
//DeadCode DAW 09May97 		}
//DeadCode DAW 09May97 		else
//DeadCode DAW 09May97 		{
//DeadCode DAW 09May97 			if ((*newbuttons&3)==3)
//DeadCode DAW 09May97 				*newbuttons=1<<(((*newbuttons>>2)&3)+4);
//DeadCode DAW 09May97 		}
//DeadCode DAW 09May97 	int	butcomp=*newbuttons^LastButtons[0];
//DeadCode DAW 09May97 	if (keyboard && butcomp)
//DeadCode DAW 09May97 		if (keyboard->ModeIs3D)	
//DeadCode DAW 09May97 		{	//3d mode. Generate key press, hold, or release events
//DeadCode DAW 09May97 			if (butcomp&1)
//DeadCode DAW 09May97 				if (*newbuttons&1)
//DeadCode DAW 09May97 					//key pressed
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(SHOOT,TRUE,TRUE);
//DeadCode DAW 09May97 				else
//DeadCode DAW 09May97 					//key released
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(SHOOT,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 //RDH 23Jul96 other buttons added
//DeadCode DAW 09May97 			if (butcomp&2)
//DeadCode DAW 09May97 				if (*newbuttons&2)
//DeadCode DAW 09May97 					//key pressed
//DeadCode DAW 09May97 //DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(INSIDETOG,TRUE,TRUE);
//DeadCode DAW 09May97 //DeadCode RDH 14Nov96 					(keyboard->*keyboard->KeyFake3dThru)(DROPBOMB,TRUE,TRUE);
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTRESET,TRUE,TRUE);//RDH 14Nov96
//DeadCode DAW 09May97 				else
//DeadCode DAW 09May97 					//key released
//DeadCode DAW 09May97 //DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(INSIDETOG,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 //DeadCode RDH 14Nov96 					(keyboard->*keyboard->KeyFake3dThru)(DROPBOMB,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTRESET,FALSE,FALSE);	//RDH 14Nov96
//DeadCode DAW 09May97 			if (butcomp&4)
//DeadCode DAW 09May97 				if (*newbuttons&4)
//DeadCode DAW 09May97 					//key pressed
//DeadCode DAW 09May97 //DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(OUTSIDETOG,TRUE,TRUE);
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(INOUTTOG,TRUE,TRUE);
//DeadCode DAW 09May97 				else
//DeadCode DAW 09May97 					//key released
//DeadCode DAW 09May97 //DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(OUTSIDETOG,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(INOUTTOG,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 			if (butcomp&8)
//DeadCode DAW 09May97 				if (*newbuttons&8)
//DeadCode DAW 09May97 					//key pressed
//DeadCode DAW 09May97 //DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(ENEMYVIEW,TRUE,TRUE);
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(PADLOCKTOG,TRUE,TRUE);
//DeadCode DAW 09May97 				else
//DeadCode DAW 09May97 					//key released
//DeadCode DAW 09May97 //DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(ENEMYVIEW,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(PADLOCKTOG,FALSE,FALSE);
//DeadCode DAW 09May97 			if (butcomp&16)
//DeadCode DAW 09May97 				if (*newbuttons&16)
//DeadCode DAW 09May97 					//key pressed
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTLEFT,TRUE,TRUE);
//DeadCode DAW 09May97 				else
//DeadCode DAW 09May97 					//key released
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTLEFT,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 			if (butcomp&32)
//DeadCode DAW 09May97 				if (*newbuttons&32)
//DeadCode DAW 09May97 					//key pressed
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTDOWN,TRUE,TRUE);
//DeadCode DAW 09May97 				else
//DeadCode DAW 09May97 					//key released
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTDOWN,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 			if (butcomp&64)
//DeadCode DAW 09May97 				if (*newbuttons&64)
//DeadCode DAW 09May97 					//key pressed
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTRIGHT,TRUE,TRUE);
//DeadCode DAW 09May97 				else
//DeadCode DAW 09May97 					//key released
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTRIGHT,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 			if (butcomp&128)
//DeadCode DAW 09May97 				if (*newbuttons&128)
//DeadCode DAW 09May97 					//key pressed
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTUP,TRUE,TRUE);
//DeadCode DAW 09May97 				else
//DeadCode DAW 09May97 					//key released
//DeadCode DAW 09May97 					(keyboard->*keyboard->KeyFake3dThru)(ROTUP,FALSE,FALSE);	//wrong...
//DeadCode DAW 09May97 		}
//DeadCode DAW 09May97 		else
//DeadCode DAW 09May97 		{	//UI mode. Generate LMB and RMB key presses
//DeadCode DAW 09May97 
//DeadCode DAW 09May97 		}
//DeadCode DAW 09May97 	LastButtons[0]=*newbuttons;
//DeadCode DAW 09May97 	return (*newbuttons&0x0f)?TRUE:FALSE;	//coolie buttons disabled
//DeadCode DAW 09May97 }
//DeadCode DAW 09May97 

Bool	Device::ReadButtons(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons,keytests* keyboard)
{
	if (activeaxes[AU_COOLIEHAT])
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
	if (keyboard && butcomp)
		if (keyboard->ModeIs3D)	
		{	//3d mode. Generate key press, hold, or release events
			if (butcomp&1)
				if (*newbuttons&1)
					//key pressed
					(keyboard->*keyboard->KeyFake3dThru)(SHOOT,TRUE,TRUE);
				else
					//key released
					(keyboard->*keyboard->KeyFake3dThru)(SHOOT,FALSE,FALSE);	//wrong...
//RDH 23Jul96 other buttons added
			if (butcomp&2)
				if (*newbuttons&2)
					//key pressed
//DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(INSIDETOG,TRUE,TRUE);
//DeadCode RDH 14Nov96 					(keyboard->*keyboard->KeyFake3dThru)(DROPBOMB,TRUE,TRUE);
					(keyboard->*keyboard->KeyFake3dThru)(ROTRESET,TRUE,TRUE);//RDH 14Nov96
				else
					//key released
//DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(INSIDETOG,FALSE,FALSE);	//wrong...
//DeadCode RDH 14Nov96 					(keyboard->*keyboard->KeyFake3dThru)(DROPBOMB,FALSE,FALSE);	//wrong...
					(keyboard->*keyboard->KeyFake3dThru)(ROTRESET,FALSE,FALSE);	//RDH 14Nov96
			if (butcomp&4)
				if (*newbuttons&4)
					//key pressed
//DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(OUTSIDETOG,TRUE,TRUE);
					(keyboard->*keyboard->KeyFake3dThru)(INOUTTOG,TRUE,TRUE);
				else
					//key released
//DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(OUTSIDETOG,FALSE,FALSE);	//wrong...
					(keyboard->*keyboard->KeyFake3dThru)(INOUTTOG,FALSE,FALSE);	//wrong...
			if (butcomp&8)
				if (*newbuttons&8)
					//key pressed
//DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(ENEMYVIEW,TRUE,TRUE);
					(keyboard->*keyboard->KeyFake3dThru)(PADLOCKTOG,TRUE,TRUE);
				else
					//key released
//DeadCode RDH 30Sep96 					(keyboard->*keyboard->KeyFake3dThru)(ENEMYVIEW,FALSE,FALSE);	//wrong...
					(keyboard->*keyboard->KeyFake3dThru)(PADLOCKTOG,FALSE,FALSE);
			if (butcomp&16)
				if (*newbuttons&16)
					//key pressed
					(keyboard->*keyboard->KeyFake3dThru)(ROTLEFT,TRUE,TRUE);
				else
					//key released
					(keyboard->*keyboard->KeyFake3dThru)(ROTLEFT,FALSE,FALSE);	//wrong...
			if (butcomp&32)
				if (*newbuttons&32)
					//key pressed
					(keyboard->*keyboard->KeyFake3dThru)(ROTDOWN,TRUE,TRUE);
				else
					//key released
					(keyboard->*keyboard->KeyFake3dThru)(ROTDOWN,FALSE,FALSE);	//wrong...
			if (butcomp&64)
				if (*newbuttons&64)
					//key pressed
					(keyboard->*keyboard->KeyFake3dThru)(ROTRIGHT,TRUE,TRUE);
				else
					//key released
					(keyboard->*keyboard->KeyFake3dThru)(ROTRIGHT,FALSE,FALSE);	//wrong...
			if (butcomp&128)
				if (*newbuttons&128)
					//key pressed
					(keyboard->*keyboard->KeyFake3dThru)(ROTUP,TRUE,TRUE);
				else
					//key released
					(keyboard->*keyboard->KeyFake3dThru)(ROTUP,FALSE,FALSE);	//wrong...
		}
		else
		{	//UI mode. Generate LMB and RMB key presses

		}
	LastButtons[0]=*newbuttons;
	return (*newbuttons&0x0f)?TRUE:FALSE;	//coolie buttons disabled
}


	STUBEND(Device)
