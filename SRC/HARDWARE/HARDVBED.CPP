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
//Filename       hardvbed.cpp
//System         
//Author         Jim Taylor
//Date           Wed 21 Feb 1996
//Description    debugging for flat memory vbe
//------------------------------------------------------------------------------
#include	"Wrapper.h"
#include	"Hardpasm.h"

void	Display::XX_SetGraphicsMode()
{

	NumberOfScreens=1;
	DPMIregs	regs;											//PD 01Oct96
	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;				//PD 01Oct96
	regs.l.edi=regs.l.ebp=regs.l.esi=regs.l.esp=0;				//PD 01Oct96
	regs.s.ds=regs.s.es=regs.s.cs=regs.s.ss=regs.s.fs=regs.s.gs=0;//PD 01Oct96
//DeadCode JIM 13Dec96 	regs.flags=0;												//PD 01Oct96

	regs.l.eax=0x4f02;
	regs.l.ecx=VFLAT.mode;
	regs.l.ebx=VFLAT.mode;
	regs.l.edi=0;
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	if (regs.w.ax!=0x004f)
		INT3();

	regs.l.eax=0x4f06;											//PD 10Apr96
	regs.l.ebx=2;												//PD 10Apr96
	regs.l.ecx=BytesPerScanLine;									//PD 10Apr96
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);//PD 10Apr96
	if (	regs.w.ax!=0x004f || regs.w.cx!=BytesPerScanLine	)//PD 10Apr96
		INT3();													//PD 10Apr96
	//get the linear address
	regs.l.eax=0x0800;
	regs.l.ecx=(UWord) VFLAT.screen;
	regs.l.ebx=(UWord) (VFLAT.screen>>16);
	regs.l.edi=(UWord) ((BytesPerScanLine*PhysicalHeight)<<1);
	regs.l.esi=(UWord) ((BytesPerScanLine*PhysicalHeight)>>15);
	ASM_DEXint31(&regs);
	VFLAT.screen=(regs.w.bx<<16)+regs.w.cx;
	ScreenNumOnLogical=0;
	logicalscreenptr=(LogicalPtr) VFLAT.screen;

}

void	Display::XX_ScreenFlip()
{
};

void	Display::XX_PalChange()
{
 		while (ASM_TestVBL());
		ASM_OutDxAl(0x3c8,0);
		ASM_OutSB(0x3c9,Palette,768);
}

//DeadCode RJS 14Mar96 void	Display::XX_PhysMouseMove(MouseSave* oldpos,void* MouseShape,MouseSave* newpos)
//DeadCode RJS 14Mar96 {
//DeadCode RJS 14Mar96 	INT3();
//DeadCode RJS 14Mar96 }

ULong	Display::XX_PlotPixelNoClip(UWord	x, UWord	y, ULong	thecol)
{
	ULong		old_col;
	LogicalPtr	screenaddr;
	SLong		yoffset, xoffset;


	yoffset = BytesPerScanLine * y;
	xoffset = BytesPerPixel * x;

	screenaddr = logicalscreenptr + xoffset + yoffset;

	old_col = (ULong)	(*screenaddr);
	*screenaddr = thecol;

	return(old_col);
}

Bool	Display::XX_CopyP2L(LogicalPtr,int ,int )
{
	return(FALSE);
}

void	Display::XX_ResetGraphicsMode()
{
		logicalscreenptr=NULL;	//block deletion
}

	STUBEND(Display);
