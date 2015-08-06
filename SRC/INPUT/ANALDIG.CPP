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
//Filename       analdig.cpp
//System         
//Author         Jim Taylor
//Date           Fri 22 Nov 1996
//Description    Analogue input for digital devices that use joystick port
//
//The MicroSoft SideWinder digital 
//	uses fire buttons 0 and 1 to generate a sequence of pulses
//  there are 14 buttons. Lets pretend there are 16..
//	They are labeled:	F B R L,A B C,X Y Z,U V,S M,? ?
//  Column 0 always shows a gap for each button
//  Column 1 shows corresponding gaps if that button is pressed.
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
	AxisUsesField def;
	def|=AU_AILERON;
	def|=AU_ELEVATOR;
	activeaxes=def;
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
		pages[0][0]=AU_ILLEGAL;
		pages[0][1]=AU_ILLEGAL;
		pages[0][2]=AU_ILLEGAL;
		pages[0][3]=AU_ILLEGAL;
		AxisUsesField def;
		def|=AU_AILERON;
		def|=AU_ELEVATOR;
		activeaxes=def;
		devicename=JOYSTICK_DEVICE_NAME;
		
}

Bool	Device::CalibCenter(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
{
	return(TRUE);
}
	
Bool	Device::CalibExtreme(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
{
	return(TRUE);
}


Bool	Device::ReadPosition(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,keytests* keyboard)
{
	int regc=0,buttons=14,bitnum;
	{	_disable();	
		ASM_OutDxAl(0x201,0);

		while ((ASM_InDxAl(0x201)&0x10)==0)	{}
		while ((ASM_InDxAl(0x201)&0x10))	{}

		while (--buttons)
		{
			regc+=regc;
			if ((ASM_InDxAl(0x201)&0x20)==0)	regc++;
			while ((ASM_InDxAl(0x201)&0x10)==0)	{}
			while ((ASM_InDxAl(0x201)&0x10))	{}
		}
		regc+=regc;
		if ((ASM_InDxAl(0x201)&0x20)==0)	regc++;
		regc+=regc;
		regc+=regc;
	}	_enable();
	axes[AU_AILERON].position=0x8000;	//return no reading
	axes[AU_ELEVATOR].position=0x8000;
	buttons=LastButtons[0];
	LastButtons[0]=regc;
	buttons^=regc;						//toggled bits

	int currbit=0x8000;bitnum=15;
	int	v1=ELEVATOR_FORWARD+(ELEVATOR_BACK<<8)+(AILERON_RIGHT<<16)+(AILERON_LEFT<<24);
	int	v2=ROTDOWN+(ROTRIGHT<<8)+(ZOOMOUT<<16)+(ROTLEFT<<24);
	int	v3=ROTUP+(ZOOMIN<<8)+(SHOOT<<16)+(DROPBOMB<<24);
	if (keyboard && keyboard->ModeIs3D)
	for (int y=0;y<3;y++)
	{
		for (int x=0;x<4;x++)
		{
			if (buttons&currbit)
				if (regc&currbit)	//press
					(keyboard->*keyboard->KeyFake3dThru)((KeyVal3D)(v1&255),TRUE,TRUE);
				else				//release
					(keyboard->*keyboard->KeyFake3dThru)((KeyVal3D)(v1&255),FALSE,FALSE);
			currbit>>=1,bitnum--;
			v1>>=8;
		}
		v1=v2;
		v2=v3;
	}
	return(TRUE);
}



	STUBEND(Device)
