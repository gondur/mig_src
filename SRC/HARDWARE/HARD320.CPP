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
//Filename       hard320.cpp
//System         
//Author         Jim Taylor
//Date           Mon 19 Feb 1996
//Description    
//------------------------------------------------------------------------------
#include	"Wrapper.h"
#include	"Hardpasm.h"

void	Display::XX_SetGraphicsMode()
{
	DPMIregs	regs;
	regs.w.ax=0x0013;
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	ASM_OutDxAx(0x03C4,0x0604);
	ASM_OutDxAl(0x03C2,0xE3);
	ASM_OutDxAx(0x03d4,0x0E11);
	ASM_OutDxAx(0x03d4,0x0D06);
	ASM_OutDxAx(0x03d4,0x3E07);
	ASM_OutDxAx(0x03d4,0xEA10);
	ASM_OutDxAx(0x03d4,0xAE11);
	ASM_OutDxAx(0x03d4,0xDF12);
	ASM_OutDxAx(0x03D4,0x0014);
	ASM_OutDxAx(0x03d4,0xE715);
	ASM_OutDxAx(0x03d4,0x0616);
	ASM_OutDxAx(0x03D4,0xE317);
}

#define	Copy4ILaceDivisor	(4*4)
extern void	ASM_Copy4ILace(void*,void*,UWord);
#ifdef __WATCOMC__
#pragma aux	ASM_Copy4ILace	=		\
	"sub	edi,4"					\
	"@@L1:"							\
 	"mov	bl,[esi]"				\
	"mov	al,[esi+8]"				\
	"add	edi,4"					\
	"mov	ah,[esi+12]"			\
 	"mov	bh,[esi+4]"				\
	"shl	eax,16"					\
	"add	esi,16"					\
	"mov	ax,bx"					\
	"dec	cx"						\
	"mov	[edi],eax"				\
	"jnz	@@L1"					\
	parm	[esi] [edi] [cx]		\
	modify	[eax ebx]
#else
#ifdef __MSVC__
inline void ASM_Copy4ILace(void* num1,void* num2,UWord num3)
{
    __asm
    {
		mov esi,num1;
		mov edi,num2;
		mov cx,num3;
		sub	edi,4;
		L1:;
 		mov	bl,[esi];
		mov	al,[esi+8];
		add	edi,4;
		mov	ah,[esi+12];
		mov	bh,[esi+4];
		shl	eax,16;
		add	esi,16;
		mov	ax,bx;
		dec	cx;
		mov	[edi],eax;
		jnz L1;
    }
}

#endif
#endif

void	Display::XX_ScreenFlip()
{
	ScreenNumOnLogical^=1;
//DeadCode JIM 19Feb96 	ASM_CopyMainRAM2VidRAM(logicalscreenptr,(char *)(0xA0000+(ScreenNumOnLogical<<15)));
	ASM_OutDxAl(0x3ce,4);		//setup the hardware
	ASM_OutDxAl(0x3c4,2);
	ASM_OutDxAl(0x3c5,1);		//stompetty
	ASM_Copy4ILace(logicalscreenptr,(void*)(0xA0000+(ScreenNumOnLogical<<15)),(320*240)/Copy4ILaceDivisor);
	ASM_OutDxAl(0x3c5,2);		//stompetty
	ASM_Copy4ILace(logicalscreenptr+1,(void*)(0xA0000+(ScreenNumOnLogical<<15)),(320*240)/Copy4ILaceDivisor);
	ASM_OutDxAl(0x3c5,4);		//stomp
	ASM_Copy4ILace(logicalscreenptr+2,(void*)(0xA0000+(ScreenNumOnLogical<<15)),(320*240)/Copy4ILaceDivisor);
	ASM_OutDxAl(0x3c5,8);		//...
	ASM_Copy4ILace(logicalscreenptr+3,(void*)(0xA0000+(ScreenNumOnLogical<<15)),(320*240)/Copy4ILaceDivisor);

	ASM_OutDxAx(0x03d4,(UWord)(0x0C+(ScreenNumOnLogical<<15)));
	ASM_OutDxAx(0x03D4,0x0D);	//screen flip
}
void	Display::XX_PalChange()
{
 		while (ASM_TestVBL());
		ASM_OutDxAl(0x3c8,0);
		ASM_OutSB(0x3c9,Palette,768);
}

ULong	Display::XX_PlotPixelNoClip(UWord	x, UWord	y, ULong	thecol)
{
	LogicalPtr	screenaddr;
	SLong		yoffset, xoffset, scroffset;
	ULong		interlacevalue, n;
	ULong		oldcol;


	yoffset = BytesPerScanLine * y;
	xoffset = BytesPerPixel * x;

	scroffset = (xoffset/4) + (yoffset/4);

	ScreenNumOnLogical^=1;

	screenaddr = (LogicalPtr) (0xA0000+(ScreenNumOnLogical<<15));
	screenaddr = screenaddr + scroffset;

	// To work out interlace value:
	//		Mask off bottom 2 bits of xoffset to find n,
	// 		then shift 1 left by n, to effectively get 2^n...

	n = (xoffset&3);

	interlacevalue = 1<<n;


	ASM_OutDxAl(0x3ce,4);					// To read the memory
	ASM_OutDxAl(0x3cf,n);

	oldcol = *screenaddr;


	ASM_OutDxAl(0x3c4,2);					// To write to the memory
	ASM_OutDxAl(0x3c5,interlacevalue);

	*screenaddr = thecol;
	
	return(oldcol);
}

//DeadCode RJS 14Mar96 void	Display::XX_PhysMouseMove(MouseSave* oldpos,void* MouseShape,MouseSave* newpos)
//DeadCode RJS 14Mar96 {
//DeadCode RJS 14Mar96 	INT3();
//DeadCode RJS 14Mar96 }

Bool	Display::XX_CopyP2L(LogicalPtr	,int ,int )
{
	return(FALSE);
}

void	Display::XX_ResetGraphicsMode()
{
//DeadCode RDH 30Oct96 	if (NumberOfScreens>1)
//DeadCode RDH 30Oct96 		LogicalScreenPtr=NULL;	//block deletion
}

	STUBEND(Display);											//JIM 21Feb96


