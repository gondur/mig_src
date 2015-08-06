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
//Filename       analmous.cpp
//System         
//Author         Jim Taylor
//Date           Thu 14 Mar 1996
//Description    
//------------------------------------------------------------------------------
#define	SPECIAL_KEYMAPS 0
#define	NDEBUG
#include	"analogue.h"
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
Bool	Device::Initialise(UByte*const  workspace,Axis axes[])
{
	devicename=MOUSE_DEVICE_NAME;
	axes[AU_UI_X].axisname=MOUSE_X_NAME;
	axes[AU_UI_Y].axisname=MOUSE_Y_NAME;
	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
		if (activeaxes[x])
		{
			axes[x].position=0;
			axes[x].status=AE_AUTO;
		}
	DPMIregs	regs;
	regs.w.ax=0;
	regs.flags=DPMIregs::CLEAR;
	ASM_DOSvia31(0x33,&regs,workspace,WORKSPACESIZE);
	if (regs.w.ax==0xffff)
		return TRUE;
	else
	{
		activeaxes=0;
		return FALSE;
	}
}
Bool	Device::LoadGame(UByte*const  workspace,Axis axes[])
{
	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
		if (activeaxes[x])
		{
			axes[x].position=0;
			axes[x].status=AE_AUTO;
		}
	DPMIregs	regs;
	regs.w.ax=0;
	regs.flags=DPMIregs::CLEAR;
	ASM_DOSvia31(0x33,&regs,workspace,WORKSPACESIZE);
	if (regs.w.ax==0xffff)
		return TRUE;
	else
	{
		activeaxes=0;
		return FALSE;
	}
}
Bool	Device::CloseDown(UByte*const  workspace)
{return(TRUE);}
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreCalib
//Author		Jim Taylor
//Date			Thu 21 Mar 1996
//
//Description	This screams 'do not attempt to calibrate me!'
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Device::PreCalib(UByte*const  workspace,Axis	axes[],axisconfigpages& pages)
{
	for (AxisUses x=AU_MIN;x<=AU_MAX;x++)
		if (activeaxes[x])
		{
			axes[x].position=0;
			axes[x].status=AE_AUTO;
		}
		pages[0][0]=pages[0][1]=pages[0][2]=pages[0][3]=AU_ILLEGAL;
}

Bool	Device::CalibCenter(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
{return(FALSE);}

Bool	Device::CalibExtreme(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes)
{return(FALSE);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadPosition
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
Bool	Device::ReadPosition(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,keytests* keyboard)
{
	DPMIregs	regs;
	regs.w.ax=0x000b;
	regs.flags=DPMIregs::CLEAR;
	ASM_DOSvia31(0x33,&regs,workspace,WORKSPACESIZE);
	int	dx=regs.w.cx;
	int	dy=regs.w.dx;
	if (reqaxes[AU_UI_X])	axes[AU_UI_X].position=dx*50;
	if (reqaxes[AU_UI_Y])	axes[AU_UI_Y].position=dy*50;
	if (reqaxes[AU_VIEWH])	axes[AU_VIEWH].position=dx;
	if (reqaxes[AU_VIEWP])	axes[AU_VIEWP].position=dy;
	if (reqaxes[AU_GUNH])	axes[AU_GUNH].position=dx;
	if (reqaxes[AU_GUNP])	axes[AU_GUNP].position=dy;
	if (reqaxes[AU_AILERON])	axes[AU_AILERON].position+=dx;
	if (reqaxes[AU_ELEVATOR])	axes[AU_ELEVATOR].position+=dy;

	regs.w.ax=0x0003;
	regs.flags=DPMIregs::CLEAR;
	ASM_DOSvia31(0x33,&regs,workspace,WORKSPACESIZE);
	ULong	button=regs.w.bx&7;
	return(ReadButtons(workspace,axes,reqaxes,&button,keyboard));
}	

Bool	Device::ReadButtons(UByte*const  workspace,Axis	axes[],const AxisUsesField& reqaxes,ULong* newbuttons,keytests* keyboard)
{
	UIKeyNoMouse	myfakekey;
	if (keyboard)
		if (keyboard->ModeIs3D)	
		{
		 	//3d keyboard
		}
		else
			for (int i=0;i<3;i++)
			{
				if (*newbuttons&(1<<i))
					if (LastButtons[0]&(1<<i))
					{
						//insert key held for LMB+i
						myfakekey.keycode=Raw_Extra0ML+i;
						myfakekey.keyshifts=0;
						myfakekey.keyhit=KEYHELD;
						(keyboard->*keyboard->InsertUIKeyThru)(myfakekey);
						//
					}
					else
					{
					 	//insert key press for LMB+i
						myfakekey.keycode=Raw_Extra0ML+i;
						myfakekey.keyshifts=0;
						myfakekey.keyhit=KEYHIT;
						(keyboard->*keyboard->InsertUIKeyThru)(myfakekey);
					}
				elseif (LastButtons[0]&(1<<i))
				{
				 	//insert key rls for LMB+i
					myfakekey.keycode=Raw_Extra0ML+i;
					myfakekey.keyshifts=0;
					myfakekey.keyhit=KEYREL;
					(keyboard->*keyboard->InsertUIKeyThru)(myfakekey);
				}
			}
	LastButtons[0]=*newbuttons;
	if (*newbuttons)
		return(TRUE);
	elser
		return(FALSE);
}


	STUBEND(Device)
