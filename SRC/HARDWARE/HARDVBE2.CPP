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
//Filename       hardvbe2.cpp
//System         
//Author         Jim Taylor
//Date           Wed 21 Feb 1996
//Description    2 screen VBE using frame buffer
//------------------------------------------------------------------------------

#include	"Wrapper.h"
#include	"Hardpasm.h"
#define MK_FP(__s,__o) (((unsigned short)(__s)):>((void __near *)(__o)))

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		XX_SetGraphicsMode
//Author		Jim Taylor
//Date			Mon 21 Oct 1996
//
//Description	Set the mode... but that's the easy bit!
//				Also want to set a virtual width of 3xnormal
//				If that works I need to choose a flipping technique:
//					1) 4f07	BL = 80 = wait?
//					2) 4f07	BL = 0 = no wait?
//					3) VGA regs
//				If that fails then set a virtual height use flipping (1)
//
//				Use LineShift and ColShift as control variables
//				
//		The reason for these magic figures is to arrange that 
//		by flipping just the VGA HIGH screen pos reg the screen moves the 
//		required ammount.
//		The VGA LOW and SVGA screen pos regs remain zeroed, although they will
//		get written to by the VESA calls.
//		This should defeat any hardware register mismatches during a VBL, and
//		allow non-synchronized flipping in all circumstances!
//
//		Cheats:	Using BytesPerScanLine rather than pixels per scanline=BPSL/BPP
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Display::XX_SetGraphicsMode()
{
	//set the mode
	DPMIregs	regs;
	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=regs.l.esp=0;
	regs.s.ds=regs.s.es=regs.s.cs=regs.s.ss=regs.s.fs=regs.s.gs=0;
//DeadCode JIM 13Dec96 	regs.flags=;
	regs.l.eax=0x4f02;
	regs.l.ecx=VFLAT.mode;
	regs.l.ebx=VFLAT.mode;
	regs.l.edi=0;
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);

	//Arrange virtual screen which is 3 screens wide,
	//and set up screen flip between them
	//Today's theory... Ensure that the screens are exactly n*1024 bytes appart
	//by performing vertical shifts of the correct OOM.
	//This should stabilise on line 5 for any display width divisible by 64
	//3 scrs wide * 5 lines = 15 scrs wide, + 1 scr wide offset ==> 16 
	//If divisible by 128, then need 8. First is line 5 again, but now 2K
	//If divisible by 512, then need 4. First is line 1 (==3 ==>4). Line 5 gives 4K
	//If divisible by 1024 then no problem immediately.
	//Having width divisible by 64 is also good 'cos most hardware should cope!
	//So make it divisible by 64...
	VFLAT.scrsize=BytesPerScanLine;
	BytesPerScanLine+=63;
	BytesPerScanLine&=-64;
	BytesPerScanLine*=3;

	//if width not possible, then consider wether height*width mod 256K is  possible:
	//640x480x256 works on above system -> 1920 wide - page 2@16*640=10K, 3@20K
	//640x480x32K -> 1280*3=3840 wide				page2@4*1280=5K, 3@10K
	//640x480x32b -> 2560*3=7680 wide				page2@4*2560=10K, 3@20K
	//800x600x256=480,000. 512K is not far off

	//1024*768=3*256K.
	//if not, consider 2 screen system (max width=2* instead of 3*).

	//if not try pseudoscreening again. - given this up...

	if (NumberOfScreens!=2)
	{
		regs.l.eax=0x4f06;
		regs.l.ebx=2;
		regs.l.ecx=(UWord)BytesPerScanLine;
		ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
		if (	regs.l.eax!=0x004f || regs.l.ecx!=BytesPerScanLine)
			NumberOfScreens=2;
	}
	if (NumberOfScreens==2)
	{	//failed to set width
		VFLAT.mode=0;
 		BytesPerScanLine=PhysicalWidth*BytesPerPixel;
		VFLAT.lineshift=PhysicalHeight;
		VFLAT.colshift=0;
		VFLAT.scrsize=BytesPerScanLine*PhysicalHeight;
		regs.s.ds=regs.s.es=regs.s.cs=regs.s.ss=regs.s.fs=regs.s.gs=0;
		regs.l.eax=0x4f06;
		regs.l.ebx=2;
		regs.l.ecx=(UWord)BytesPerScanLine;
		ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//TempCode JIM 21Oct96 		regs.l.eax=0x4f06;
	}
	else
	{
		VFLAT.mode=1;
		VFLAT.scrsize+=63;
		VFLAT.scrsize&=-64;
		VFLAT.scrsize*=4;
		while (VFLAT.scrsize&1023) VFLAT.scrsize+=BytesPerScanLine;
		VFLAT.colshift=VFLAT.scrsize;
		VFLAT.colshift/=BytesPerPixel;
		VFLAT.lineshift=0;
	}

	//need to know wether BX=00 or BX=80 is fastest

	int	tickBX0=10;	//slight bias for this one...
	int	tickBX1=0;
	//wait for 1/18 counter to change
	int	th18=*(volatile ULong*)0x46C;
	while (th18==*(volatile ULong*)0x46C)	{}
	th18+=4;				
	while (th18!=*(volatile ULong*)0x46C)
	{
		tickBX0+=8;			// 4/18 of second @ 100Hz=25 frames max.
		regs.l.eax=0x4f07;	// 4/18 of second @ DOSvia31 setup time @ 100us =2500 frames max
		regs.l.ebx=0x0000;
		regs.l.edx=tickBX0 & 255;
		regs.l.ecx=tickBX0 & 255;
		ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	}

	th18=*(volatile ULong*)0x46C;
	while (th18==*(volatile ULong*)0x46C)	{}
	th18+=4;
	while (th18!=*(volatile ULong*)0x46C)
	{
		tickBX1+=8;
		regs.l.eax=0x4f07;
		regs.l.ebx=0x0080;
		regs.l.edx=tickBX1 & 255;
		regs.w.cx=tickBX1 & 255;
		ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	}
	th18=VFLAT.mode;
	if (!!(tickBX1>tickBX0) == !!(VFLAT.mode==1))
		//mode1 faster than mode0  and want faster screen
		VFLAT.mode=0x80;
	else
		//mode0 faster than mode1  and want faster screen
		VFLAT.mode=0x00;

	if (th18==1)	//fast mode requested
	{
		VFLAT.lineshift+=VFLAT.colshift/BytesPerScanLine;
		VFLAT.colshift%=BytesPerScanLine;
		//need to know scaling factor and success for direct h/w write
		//choose slower VESA call:
		//Have chosen faster driver.. if both drivers were slow,
		//then lets try a hardware hitting approach.
		//Max monitor speed= 200Hz @ 4/18.2 seconds = 44
		//Lets use 80 to be on safe side
		if (tickBX1<80 && tickBX0<80)
		{
			th18=0x80-VFLAT.mode;
			//set address at zero:
			regs.l.eax=0x4f07;
			regs.l.ebx=th18;
			regs.l.edx=0;
			regs.w.cx=0;
			ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	  		while (!ASM_TestVBL());
			if (	(ASM_OutDxAl(0x03d4,0x0c),ASM_InDxAl(0x03d5)==0)
				&&	(ASM_OutDxAl(0x03d4,0x0d),ASM_InDxAl(0x03d5)==0)	)
			{
				regs.l.eax=0x4f07;
				regs.l.ebx=th18;
				regs.l.edx=VFLAT.lineshift;
				regs.l.ecx=VFLAT.colshift;
				ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	  			while (!ASM_TestVBL());
				if (	(ASM_OutDxAl(0x03d4,0x0d),ASM_InDxAl(0x03d5)==0)	)
				{
					ASM_OutDxAl(0x03d4,0x0c);
					tickBX0=ASM_InDxAl(0x03d5);
					if (tickBX0)
					{
						regs.l.eax=0x4f07;
						regs.l.ebx=th18;
						regs.l.edx=VFLAT.lineshift*2;
						regs.l.ecx=VFLAT.colshift*2;
						ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
			  			while (!ASM_TestVBL());
						if (	(ASM_OutDxAl(0x03d4,0x0d),ASM_InDxAl(0x03d5)==0)	)
						{
							ASM_OutDxAl(0x03d4,0x0c);
							if (tickBX0+tickBX0==ASM_InDxAl(0x03d5))
							{	//fast hardware hitting mode!!!
								ASM_OutDxAl(0x03d4,0x0d);
								ASM_OutDxAl(0x03d5,0);
								ASM_OutDxAl(0x03d4,0x0c);
								ASM_OutDxAl(0x03d5,tickBX0);
								regs.l.eax=0x4f07;
								regs.l.ebx=1;
					  			while (!ASM_TestVBL());
								ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
								if (regs.w.dx==VFLAT.lineshift && regs.w.cx==VFLAT.colshift)
								{
									//If you think this is bad, you should see the old engine!
									VFLAT.colshift=tickBX0<<8;
									VFLAT.lineshift=0;
	}	}	}	}	}	}	}	}
	else
	{	//slow requested, but was it slow enough?
		//wait for 4/18.2 seconds. 
		//If display is fastest 200Hz, that is 50 frames
		//if both counters are>50 then need manual VBL wait!
		if (tickBX1>50 && tickBX0>50)
			VFLAT.mode=0x100;
	}
	regs.l.eax=0x4f07;
	regs.l.ebx=0;
	regs.l.edx=0;
	regs.l.ecx=0;
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);

	//get the linear address
	regs.l.eax=0x0800;
	regs.l.ecx=(UWord) VFLAT.screen;
	regs.l.ebx=(UWord) (VFLAT.screen>>16);
	if (NumberOfScreens==2)
	{
		regs.l.edi=(UWord) ((BytesPerScanLine*(PhysicalHeight+5)*2));
		regs.l.esi=(UWord) ((BytesPerScanLine*(PhysicalHeight+5)*2)>>16);
	}
	else
	{
		regs.l.edi=(UWord) ((BytesPerScanLine*PhysicalHeight+VFLAT.scrsize*2));
		regs.l.esi=(UWord) ((BytesPerScanLine*PhysicalHeight+VFLAT.scrsize*2)>>16);
	}
	ASM_DEXint31(&regs);
	VFLAT.screen=(regs.l.ebx<<16)+regs.l.ecx;
	ScreenNumOnLogical=1;
	logicalscreenptr=(LogicalPtr) VFLAT.screen+VFLAT.scrsize;

}

void	Display::XX_ScreenFlip()
{
	int	newps=ScreenNumOnLogical;
	logicalscreenptr+=VFLAT.scrsize;	//*BytesPerPixel;
	if (++ScreenNumOnLogical==NumberOfScreens)
	{
		ScreenNumOnLogical=0;
		logicalscreenptr=(LogicalPtr)VFLAT.screen;
	}
	if (VFLAT.lineshift==0)
	{	//fastest method
		UWord rp=VFLAT.colshift;
		rp*=newps;
		ASM_OutDxAx(0x03d4,0x0C+rp);
		ASM_OutDxAx(0x03D4,0x0D);	//screen flip - fast!
	}
	else
	{	//slower method
		DPMIregs	regs;
		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
		regs.l.edi=regs.l.ebp=regs.l.esi=0;
		regs.l.eax=0x4f07;
		regs.b.bl=VFLAT.mode;
		regs.l.edx=VFLAT.lineshift*newps;
		regs.l.ecx=VFLAT.colshift*newps;
		ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
		if (VFLAT.mode>0x80)
	  		while (!ASM_TestVBL());
	}
}

void	Display::XX_PalChange()
{
  		while (!ASM_TestVBL());
		ASM_OutDxAl(0x3c8,0);
		ASM_OutSB(0x3c9,Palette,768);
}

//DeadCode RJS 14Mar96 void	Display::XX_PhysMouseMove(MouseSave* oldpos,void* MouseShape,MouseSave* newpos)
//DeadCode RJS 14Mar96 {
//DeadCode RJS 14Mar96 	INT3();
//DeadCode RJS 14Mar96 }

extern	void	copydata(void* src,void* trg,int longs);
#ifdef __WATCOMC__
#pragma aux copydata=	"rep movsd"	parm [esi] [edi] [ecx] 
#else
#ifdef __MSVC__
inline void	copydata(void* src,void* trg,int longs);
{
    __asm
    {
		mov esi,src;
		mov edi,trg;
		mov ecx,longs;
		rep movsd;
    }
}

#endif
#endif
//DeadCode JIM 19Nov96 	void	copyloop(void* out,void* in,ULong count);
//DeadCode JIM 19Nov96 	#pragma aux copyloop=				\
//DeadCode JIM 19Nov96 			"push	ebp"				\
//DeadCode JIM 19Nov96 			"add	ecx,15"				\
//DeadCode JIM 19Nov96 			"shr	ecx,4"				\
//DeadCode JIM 19Nov96 			"l:"						\
//DeadCode JIM 19Nov96 			"mov	edx,[esi]"			\
//DeadCode JIM 19Nov96 			"mov	ebp,[esi+4]"			\
//DeadCode JIM 19Nov96 			"mov	eax,[esi+8]"		\
//DeadCode JIM 19Nov96 			"mov	ebx,[esi+12]"		\
//DeadCode JIM 19Nov96 			"add	edi,16"				\
//DeadCode JIM 19Nov96 			"add	esi,16"				\
//DeadCode JIM 19Nov96 			"dec	ecx"				\
//DeadCode JIM 19Nov96 			"mov	[edi-16],edx"		\
//DeadCode JIM 19Nov96 			"mov	[edi+4-16],ebp"		\
//DeadCode JIM 19Nov96 			"mov	[edi+8-16],eax"		\
//DeadCode JIM 19Nov96 			"mov	[edi+12-16],ebx"		\
//DeadCode JIM 19Nov96 			"jnz	l"					\
//DeadCode JIM 19Nov96 			"pop	ebp"				\
//DeadCode JIM 19Nov96 			parm	[edi] [esi] [ecx]	\
//DeadCode JIM 19Nov96 			modify	[ebx eax edx]

Bool	Display::XX_CopyP2L(LogicalPtr	T,int W,int H)
{

	LogicalPtr	S;
	if (ScreenNumOnLogical)
		S=logicalscreenptr-VFLAT.scrsize;
	else
		S=logicalscreenptr+VFLAT.scrsize*(NumberOfScreens-1);
	S+=(T-logicalscreenptr);
//DeadCode JIM 04Sep96 	ULong	wd=(W+3)/(4*2);
	ULong	bps=BytesPerScanLine;
	W>>=2;
	do
	{
		copydata(S,T,W);
//DeadCode JIM 04Sep96 		ULong*	S1=(ULong*) S;
//DeadCode JIM 04Sep96 		ULong*	T1=((ULong*) T) -2;
//DeadCode JIM 04Sep96 		ULong	W1=wd;
//DeadCode JIM 04Sep96 		do
//DeadCode JIM 04Sep96 		{
//DeadCode JIM 04Sep96 			ULong	tmp0=S1[0];
//DeadCode JIM 04Sep96 			ULong	tmp1=S1[1];
//DeadCode JIM 04Sep96 			T1+=2;
//DeadCode JIM 04Sep96 			S1+=2;
//DeadCode JIM 04Sep96 			T1[0]=tmp0;
//DeadCode JIM 04Sep96 			T1[1]=tmp1;
//DeadCode JIM 04Sep96 		}
//DeadCode JIM 04Sep96 		while(--W1);
		S+=bps;
		T+=bps;
	}
	while (--H);
	return(TRUE);
}

ULong	Display::XX_PlotPixelNoClip(UWord	x, UWord	y, ULong	thecol)
{
	ULong		old_col;
	LogicalPtr	screenaddr;
	SLong		yoffset, xoffset;


	screenaddr=logicalscreenptr-VFLAT.scrsize;
	if (ScreenNumOnLogical==0)
		screenaddr+=VFLAT.scrsize*NumberOfScreens;


	yoffset = BytesPerScanLine * y;
	xoffset = BytesPerPixel * x;

	screenaddr += xoffset + yoffset;

	old_col = (ULong)	(*screenaddr);
	*screenaddr = thecol;
	

	return(old_col);
}

void	Display::XX_ResetGraphicsMode()
{
	DPMIregs	regs;
	regs.l.eax=0x0801;
	regs.l.ecx=(UWord) VFLAT.screen;
	regs.l.ebx=(UWord) (VFLAT.screen>>16);
	ASM_DEXint31(&regs);
	logicalscreenptr=NULL;	//block deletion
}

STUBEND(Display);
