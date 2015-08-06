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
//Filename       hardvbe1.cpp
//System         
//Author         Jim Taylor
//Date           Tue 20 Feb 1996
//Description    Vesa Bios Extensions: 1 pseudoscreen
//------------------------------------------------------------------------------
#include	"Wrapper.h"
#include	"Hardpasm.h"

void	Display::XX_SetGraphicsMode()
{
	DPMIregs	regs;
	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;
	regs.w.ax=0x4f02;
	regs.w.cx=VESA.mode;
	regs.w.bx=VESA.mode;
	VESA.mode=-1;
	regs.w.di=0;
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	if (regs.w.ax!=0x004f)
		INT3();
	regs.w.ax=0x4f06;
	regs.w.bx=0;
	regs.w.cx=VESA.BytesPerScanLine/VESA.BytesPerPixel;
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
}

extern	void*	copydata(void* src,void* trg,int longs);
#ifdef __WATCOMC__
#pragma aux copydata=	"rep movsd"	parm [esi] [edi] [ecx] value [esi]
#else
#ifdef __MSVC__
inline void*	copydata(void* src,void* trg,int longs)
{
	void*	retval;
    __asm
    {
		mov esi,src;
		mov edi,trg;
		mov ecx,longs;
		rep movsd;
		mov retval,esi;
    }
    return retval;
}

#endif
#endif

void	Display::XX_ScreenFlip()
{
	DPMIregs	regs;
	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;
int	skipbytes,Lines,Columns,page;
	if (++VESA.ScreenNum>=VESA.Screens)
		VESA.ScreenNum=0;
int	physicaloffset=VESA.ScreenNum*VESA.BytesPerScanLine*VESA.ScanLines;
	page=
		VESA.pagetop=physicaloffset/VESA.PageShift;
	VESA.pageoff=physicaloffset%VESA.PageShift;

	if (VESA.BytesPerScanLine==BytesPerScanLine)
	{
		skipbytes=0;
		Lines=1;
		Columns=BytesPerScanLine*PhysicalHeight;
	}
	else
	{
		skipbytes=VESA.BytesPerScanLine-BytesPerScanLine;
		Lines=PhysicalHeight;
		Columns=BytesPerScanLine;
	}

	LogicalPtr	src=logicalscreenptr;
	char		*trg2,*trg=(char*)VESA.writeaddr;
	int			off=VESA.pageoff;

	//set to page
	regs.w.ax=0x4f05;
	regs.w.bx=VESA.writewin;
	regs.w.dx=page;
	VESA.mode=page;
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);

	while (Lines--)
	{
int		colleft=Columns;
		while (off+colleft>VESA.PageSize)
		{
int			tmpleft=VESA.PageSize-off;
			colleft=colleft-tmpleft;
//TempCode JIM 14Dec95 			ASM_blat(trg+off,src,tmpleft);
//TempCode JIM 14Dec95 			src+=tmpleft;
			if (tmpleft>0)
			{
				tmpleft=tmpleft>>2;
				trg2=off+trg;
				src=(LogicalPtr)copydata(src,trg2,tmpleft);
			}
			else
				src+=tmpleft;
//DeadCode JIM 19Nov96 			tmpleft=tmpleft>>2;
//DeadCode JIM 19Nov96 			trg2=off+trg;
//DeadCode JIM 19Nov96 			while (tmpleft--)
//DeadCode JIM 19Nov96 			{
//DeadCode JIM 19Nov96 				*((ULong*) (trg2))=*((LogicalLPtr) src);
//DeadCode JIM 19Nov96 				src+=4;
//DeadCode JIM 19Nov96 				trg2+=4;
//DeadCode JIM 19Nov96 			}
			off=0;

			//set to next page
			page+=VESA.PageShift;
			regs.w.ax=0x4f05;
			regs.w.bx=VESA.writewin;
			regs.w.dx=page;
	        VESA.mode=page;
			ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);

		}
//TempCode JIM 14Dec95 			ASM_blat(trg+off,src,colleft);
//TempCode JIM 14Dec95 			src+=colleft;
//TempCode JIM 14Dec95 		off+=colleft;
		trg2=off+trg;
		off+=colleft;
		colleft=colleft>>2;
		if (colleft)
			src=(LogicalPtr)copydata(src,trg2,colleft);
//DeadCode JIM 19Nov96 		while (colleft--)
//DeadCode JIM 19Nov96 		{
//DeadCode JIM 19Nov96 			*((ULong*) (trg2))=*((LogicalLPtr) src);
//DeadCode JIM 19Nov96 			src+=4;
//DeadCode JIM 19Nov96 			trg2+=4;
//DeadCode JIM 19Nov96 		}
		off+=skipbytes;
	}
};

void	Display::XX_PalChange()
{
 		while (ASM_TestVBL());
		ASM_OutDxAl(0x3c8,0);
		ASM_OutSB(0x3c9,Palette,768);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlotPixelNoClip
//Author		Robert Slater
//Date			Tue 12 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ULong	Display::XX_PlotPixelNoClip(UWord	x, UWord	y, ULong	thecol)
{
    int 		page = 0;
    DPMIregs    regs;
	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;

    int 		stoffset =
            		((page*VESA.ScanLines+y)*VESA.BytesPerScanLine) +
					(x*VESA.BytesPerPixel);

    int 		pagenum = (stoffset/VESA.PageSize)*VESA.PageShift;


    stoffset %= VESA.PageSize;

    if (pagenum != VESA.mode) //this is significant, but the
    {                           //code in hardvbe1 interferes.


    regs.w.ax = 0x4f05;
    regs.w.bx = VESA.writewin;
    regs.w.dx = pagenum;

    ASM_DOSvia31(0x10, &regs, real_mode_stack, REALMODE_STACK_SIZE, 0);

        VESA.mode=pagenum;
    }


    char*   addr = 	(char*)	VESA.writeaddr + stoffset;

    int		rv	= *addr;

    *addr = thecol;

    return(rv);
}


Bool	Display::XX_CopyP2L(LogicalPtr	,int ,int )
{
	return(FALSE);
}

void	Display::XX_ResetGraphicsMode()
{
//DeadCode RDH 30Oct96 	if (NumberOfScreens>1)
//DeadCode RDH 30Oct96 		LogicalScreenPtr=NULL;	//block deletion
}


	STUBEND(Display);
