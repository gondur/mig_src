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
//Filename       hardprim.cpp
//System         
//Author         Paul.   
//Date           Mon 3 Jul 1995
//Description    This is the hardware primitives library and provides the 
//			   following...
//
//				1) Set graphics mode
//				2) Screen swap + update w/o screenswap debug entry point
//				3) Single pixel plot to physical
//				4) Set text mode
//
//------------------------------------------------------------------------------

//DeadCode JIM 12Dec95 #include	<graph.h>

#include	<dos.h>

#include	"DosDefs.H"
#include "Palette.H"
//DeadCode DAW 15Apr96 #include "Screen.H"
#include	"Display.h"
#include	"myError.h"

extern	"C"	void		ASM_CopyMainRAM2VidRAM(char *, char *);
extern	"C"	void		ASM_CopyMainRAM2VidRAMF(char *, char *);
extern	"C"	void		ASM_SetPalette(char *);
extern	"C"	void		ASM_WaitVBL(void );
extern	"C"	void		ASM_OutDxAx(int ,int);
extern	"C"	void		ASM_OutDxAl(int ,int);
extern	"C"	short	ASM_PlotPixel(long, long, long, short);

//DeadCode JIM 12Dec95 static	struct	ScreenList
//DeadCode JIM 12Dec95 {
//DeadCode JIM 12Dec95 	long	Physical;
//DeadCode JIM 12Dec95 	long	Logical;
//DeadCode JIM 12Dec95 	long	Other;
//DeadCode JIM 12Dec95 }	
//DeadCode JIM 12Dec95 screenlist;

//DeadCode JIM 12Dec95 static	struct	rminfo	RMI;
//DeadCode JIM 12Dec95 	
//DeadCode JIM 12Dec95 union 	REGS 	regs;
//DeadCode JIM 12Dec95 struct 	SREGS	sregs;

//DeadCode JIM 13Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 13Dec95 //Procedure	HardPrim::SetGraphicsMode
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //Author		Paul.   
//DeadCode JIM 13Dec95 //Date		Mon 3 Jul 1995
//DeadCode JIM 13Dec95 //Modified	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Description	Does the same job as old 'SetMode320x200'
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Inputs	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Returns	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Externals
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 short Display::SetGraphicsMode(InitDisplayDef&)
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 	short ret_val;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	//Allocate conventional DOS RAM for DPMI real mode stack
//DeadCode JIM 13Dec95 	stkhndl = GetDOSRAM((long& )real_mode_stack,REALMODE_STACK_SIZE);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	logicalscreenptr =	NULL;
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 		CharColourTable = 
//DeadCode JIM 13Dec95 	Palette =			NULL;
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 				HardPage = 
//DeadCode JIM 13Dec95 	MouseSave =			NULL;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 	switch(mode)
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 	{
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 		default:		//Default is set 320x200
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 		case MODE_320x200:
//DeadCode JIM 13Dec95 			screenlist.Physical = 0x0A0000;
//DeadCode JIM 13Dec95 			screenlist.Logical = 0x0A3F00;
//DeadCode JIM 13Dec95 			screenlist.Other = 0x0A7E00;
//DeadCode JIM 13Dec95 			ret_val = SetMode320x200();							//JIM 12Dec95
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 			break;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 		case	MODE_640x480:
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 			screenlist.Physical = screenlist.Logical = screenlist.Other = 0x0A0000;
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 			ret_val = SetMode640x480(screen);
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 			break;
//DeadCode JIM 13Dec95 //TempCode JIM 12Dec95 	}
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	NumberOfScreens = 3;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	ScreenNumOnLogical = PhysicalMinX = PhysicalMinY =
//DeadCode JIM 13Dec95 	CharX =
//DeadCode JIM 13Dec95 		CharY = 0;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	BytesPerScanLine = PhysicalWidth * BytesPerPixel;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	VirtualMinX = V_MINX;
//DeadCode JIM 13Dec95 	VirtualWidth = V_MAXX;
//DeadCode JIM 13Dec95 	VirtualMinY = V_MINY;
//DeadCode JIM 13Dec95 	VirtualHeight = V_MAXY;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 	PrevMode = MODE_TEXT;
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 	CurrMode = mode;
//DeadCode JIM 13Dec95 	fontptr =	NULL;
//DeadCode JIM 13Dec95 	return(ret_val);
//DeadCode JIM 13Dec95 }

//DeadCode JIM 13Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 13Dec95 //Procedure	SetMode640x480
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //Author		Paul.   
//DeadCode JIM 13Dec95 //Date		Mon 24 Jul 1995
//DeadCode JIM 13Dec95 //Modified	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Description	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Inputs	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Returns	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Externals
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 short Display::SetMode640x480()
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 	_setvideomode(_VRES256COLOR);
//DeadCode JIM 13Dec95 	return(TRUE);
//DeadCode JIM 13Dec95 }
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 13Dec95 //Procedure	SetMode320x200
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //Author		Paul.   
//DeadCode JIM 13Dec95 //Date		Mon 24 Jul 1995
//DeadCode JIM 13Dec95 //Modified	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Description	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Inputs	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Returns	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Externals
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 short Display::SetMode320x200()
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 	RMI.EAX = 0x00000012;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	regs.w.cx = 0;
//DeadCode JIM 13Dec95 	sregs.es = FP_SEG(&RMI);
//DeadCode JIM 13Dec95 	regs.x.edi = FP_OFF(&RMI);
//DeadCode JIM 13Dec95 	regs.w.ax = 0x0300;
//DeadCode JIM 13Dec95 	regs.w.bx = 0x0010;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	int386x(0x31, &regs, &regs, &sregs);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	RMI.EAX = 0x00000013;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	regs.w.cx = 0;
//DeadCode JIM 13Dec95 	sregs.es = FP_SEG(&RMI);
//DeadCode JIM 13Dec95 	regs.x.edi = FP_OFF(&RMI);
//DeadCode JIM 13Dec95 	regs.w.ax = 0x0300;
//DeadCode JIM 13Dec95 	regs.w.bx = 0x0010;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	int386x(0x31, &regs, &regs, &sregs);
//DeadCode JIM 13Dec95 	
//DeadCode JIM 13Dec95 	ASM_OutDxAx(0xE317,0x03D4);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	ASM_OutDxAx(0x0014,0x03D4);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	ASM_OutDxAx(0x0604,0x03C4);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //Old_Code DAW 23Nov95 	screen->LogicalScreenPtr=(void*) 0xA0000;
//DeadCode JIM 13Dec95 	return(TRUE);
//DeadCode JIM 13Dec95 }
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 13Dec95 //Procedure	SetMode320x200Debug
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //Author		Paul.   
//DeadCode JIM 13Dec95 //Date		Mon 24 Jul 1995
//DeadCode JIM 13Dec95 //Modified	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Description	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Inputs	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Returns	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Externals
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 short Display::SetMode320x200Debug()
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 	RMI.EAX = 0x00000012;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	regs.w.cx = 0;
//DeadCode JIM 13Dec95 	sregs.es = FP_SEG(&RMI);
//DeadCode JIM 13Dec95 	regs.x.edi = FP_OFF(&RMI);
//DeadCode JIM 13Dec95 	regs.w.ax = 0x0300;
//DeadCode JIM 13Dec95 	regs.w.bx = 0x0010;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	int386x(0x31, &regs, &regs, &sregs);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	RMI.EAX = 0x00000013;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	regs.w.cx = 0;
//DeadCode JIM 13Dec95 	sregs.es = FP_SEG(&RMI);
//DeadCode JIM 13Dec95 	regs.x.edi = FP_OFF(&RMI);
//DeadCode JIM 13Dec95 	regs.w.ax = 0x0300;
//DeadCode JIM 13Dec95 	regs.w.bx = 0x0010;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	int386x(0x31, &regs, &regs, &sregs);
//DeadCode JIM 13Dec95 	
//DeadCode JIM 13Dec95 //DeadCode PD 03Nov95 	ASM_OutDxAx(0xE317,0x03D4);
//DeadCode JIM 13Dec95 //DeadCode PD 03Nov95 
//DeadCode JIM 13Dec95 //DeadCode PD 03Nov95 	ASM_OutDxAx(0x0014,0x03D4);
//DeadCode JIM 13Dec95 //DeadCode PD 03Nov95 
//DeadCode JIM 13Dec95 //DeadCode PD 03Nov95 	ASM_OutDxAx(0x0604,0x03C4);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	return(TRUE);
//DeadCode JIM 13Dec95 }
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 13Dec95 //Procedure	HardPrim::ScreenSwap
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //Author		Paul.   
//DeadCode JIM 13Dec95 //Date		Mon 3 Jul 1995
//DeadCode JIM 13Dec95 //Modified	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Description	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Inputs	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Returns	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Externals
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 void Display::ScreenSwap(short UseNewPal)
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 	char	*src,*dest;
//DeadCode JIM 13Dec95 	long	tmp;
//DeadCode JIM 13Dec95 	short tmp2,tmp3;
//DeadCode JIM 13Dec95 	short i,visualpage;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	if((ScreenNumOnLogical++)>NumberOfScreens)
//DeadCode JIM 13Dec95 		ScreenNumOnLogical = 0;
//DeadCode JIM 13Dec95 	
//DeadCode JIM 13Dec95 	tmp = screenlist.Physical;
//DeadCode JIM 13Dec95 	screenlist.Physical = screenlist.Logical;
//DeadCode JIM 13Dec95 	screenlist.Logical = screenlist.Other;
//DeadCode JIM 13Dec95 	screenlist.Other = tmp;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 	switch(screen->CurrMode)
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 	{
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 		case MODE_320x200Debug:									//PD 03Nov95
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 			break;												//PD 03Nov95
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 		default:		//Default is set 320x200
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 		case MODE_320x200:
//DeadCode JIM 13Dec95 			ASM_CopyMainRAM2VidRAM(logicalscreenptr,(char *)screenlist.Physical);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 			//Now actually swap the displayed screen
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 			tmp2 = (short )((screenlist.Physical - 0x0A0000)>>8);
//DeadCode JIM 13Dec95 			tmp3 = tmp2;
//DeadCode JIM 13Dec95 			tmp2 = (tmp2<<8) + 0x0C;				//hi byte
//DeadCode JIM 13Dec95 			tmp3 = (tmp3 & 0xFF00) + 0x0D;		//lo byte
//DeadCode JIM 13Dec95 			ASM_OutDxAx(tmp2,0x03D4);
//DeadCode JIM 13Dec95 			ASM_OutDxAx(tmp3,0x03D4);
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 			break;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 		case	MODE_640x480:
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 			src = (char *)screen->LogicalScreenPtr;
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 			dest = (char *)screenlist.Physical;
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 			for(i=visualpage=_getvisualpage();i<visualpage+4;i++){
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 				_setvisualpage(i);
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 				ASM_CopyMainRAM2VidRAMF(src,dest);
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 			}
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 			break;
//DeadCode JIM 13Dec95 //DeadCode JIM 12Dec95 	}
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	if(UseNewPal == TRUE)
//DeadCode JIM 13Dec95 	{
//DeadCode JIM 13Dec95 		ASM_WaitVBL();
//DeadCode JIM 13Dec95 		ASM_SetPalette((char *)Palette);
//DeadCode JIM 13Dec95 	}
//DeadCode JIM 13Dec95 }
//DeadCode DAW 18Dec95 >>>>>>>>>>  hardprim.cpp  Rev "PD branch" (1.2.9.0)
//DeadCode DAW 18Dec95 		case MODE_320x200Debug:									//PD 01Dec95
//DeadCode DAW 18Dec95 			screen->LogicalScreenPtr = (void *)0x0A0000;		//PD 01Dec95
//DeadCode DAW 18Dec95 				screenlist.Physical = 							//PD 01Dec95
//DeadCode DAW 18Dec95 					screenlist.Logical = 						//PD 01Dec95
//DeadCode DAW 18Dec95 						screenlist.Other = 0x0A0000;			//PD 01Dec95
//DeadCode DAW 18Dec95 			ret_val = SetMode320x200Debug(screen);				//PD 01Dec95
//DeadCode DAW 18Dec95 			break;												//PD 01Dec95
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 		default:		//Default is set 320x200
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 		case MODE_320x200:
//DeadCode DAW 18Dec95 			screenlist.Physical = 0x0A0000;
//DeadCode DAW 18Dec95 			screenlist.Logical = 0x0A3F00;
//DeadCode DAW 18Dec95 			screenlist.Other = 0x0A7E00;
//DeadCode DAW 18Dec95 			ret_val = SetMode320x200(screen);
//DeadCode DAW 18Dec95 			break;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 		case	MODE_640x480:
//DeadCode DAW 18Dec95 			screenlist.Physical = screenlist.Logical = screenlist.Other = 0x0A0000;
//DeadCode DAW 18Dec95 			ret_val = SetMode640x480(screen);
//DeadCode DAW 18Dec95 			break;
//DeadCode DAW 18Dec95 	}
//DeadCode DAW 18Dec95 e
//DeadCode DAW 18Dec95 	screen->NumberOfScreens = 3;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	screen->ScreenNumOnLogical = screen->PhysicalMinX = screen->PhysicalMinY =
//DeadCode DAW 18Dec95 	screen->CharX = screen->CharY = 0;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	screen->BytesPerScanLine = screen->PhysicalWidth * screen->BytesPerPixel;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	screen->VirtualMinX = V_MINX;
//DeadCode DAW 18Dec95 	screen->VirtualWidth = V_MAXX;
//DeadCode DAW 18Dec95 	screen->VirtualMinY = V_MINY;
//DeadCode DAW 18Dec95 	screen->VirtualHeight = V_MAXY;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	screen->PrevMode = MODE_TEXT;
//DeadCode DAW 18Dec95 	screen->CurrMode = mode;
//DeadCode DAW 18Dec95 	screen->fontptr =	NULL;
//DeadCode DAW 18Dec95 	return(ret_val);
//DeadCode DAW 18Dec95 }
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 18Dec95 //Procedure	SetMode640x480
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 //Author		Paul.   
//DeadCode DAW 18Dec95 //Date		Mon 24 Jul 1995
//DeadCode DAW 18Dec95 //Modified	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Description	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Inputs	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Returns	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Externals
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 short HardPrim::SetMode640x480(ScreenRecord *screen)
//DeadCode DAW 18Dec95 {
//DeadCode DAW 18Dec95 	_setvideomode(_VRES256COLOR);
//DeadCode DAW 18Dec95 	return(TRUE);
//DeadCode DAW 18Dec95 }
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 18Dec95 //Procedure	SetMode320x200
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 //Author		Paul.   
//DeadCode DAW 18Dec95 //Date		Mon 24 Jul 1995
//DeadCode DAW 18Dec95 //Modified	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Description	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Inputs	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Returns	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Externals
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 short HardPrim::SetMode320x200(ScreenRecord *screen)
//DeadCode DAW 18Dec95 {
//DeadCode DAW 18Dec95 	RMI.EAX = 0x00000012;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	regs.w.cx = 0;
//DeadCode DAW 18Dec95 	sregs.es = FP_SEG(&RMI);
//DeadCode DAW 18Dec95 	regs.x.edi = FP_OFF(&RMI);
//DeadCode DAW 18Dec95 	regs.w.ax = 0x0300;
//DeadCode DAW 18Dec95 	regs.w.bx = 0x0010;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	int386x(0x31, &regs, &regs, &sregs);
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	RMI.EAX = 0x00000013;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	regs.w.cx = 0;
//DeadCode DAW 18Dec95 	sregs.es = FP_SEG(&RMI);
//DeadCode DAW 18Dec95 	regs.x.edi = FP_OFF(&RMI);
//DeadCode DAW 18Dec95 	regs.w.ax = 0x0300;
//DeadCode DAW 18Dec95 	regs.w.bx = 0x0010;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	int386x(0x31, &regs, &regs, &sregs);
//DeadCode DAW 18Dec95 	
//DeadCode DAW 18Dec95 	ASM_OutDxAx(0xE317,0x03D4);
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	ASM_OutDxAx(0x0014,0x03D4);
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	ASM_OutDxAx(0x0604,0x03C4);
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 //Old_Code DAW 23Nov95 	screen->LogicalScreenPtr=(void*) 0xA0000;
//DeadCode DAW 18Dec95 	return(TRUE);
//DeadCode DAW 18Dec95 }
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 18Dec95 //Procedure	SetMode320x200Debug
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 //Author		Paul.   
//DeadCode DAW 18Dec95 //Date		Mon 24 Jul 1995
//DeadCode DAW 18Dec95 //Modified	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Description	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Inputs	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Returns	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Externals
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 short HardPrim::SetMode320x200Debug(ScreenRecord *screen)
//DeadCode DAW 18Dec95 {
//DeadCode DAW 18Dec95 	RMI.EAX = 0x00000012;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	regs.w.cx = 0;
//DeadCode DAW 18Dec95 	sregs.es = FP_SEG(&RMI);
//DeadCode DAW 18Dec95 	regs.x.edi = FP_OFF(&RMI);
//DeadCode DAW 18Dec95 	regs.w.ax = 0x0300;
//DeadCode DAW 18Dec95 	regs.w.bx = 0x0010;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	int386x(0x31, &regs, &regs, &sregs);
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	RMI.EAX = 0x00000013;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	regs.w.cx = 0;
//DeadCode DAW 18Dec95 	sregs.es = FP_SEG(&RMI);
//DeadCode DAW 18Dec95 	regs.x.edi = FP_OFF(&RMI);
//DeadCode DAW 18Dec95 	regs.w.ax = 0x0300;
//DeadCode DAW 18Dec95 	regs.w.bx = 0x0010;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	int386x(0x31, &regs, &regs, &sregs);
//DeadCode DAW 18Dec95 	
//DeadCode DAW 18Dec95 //DeadCode PD 03Nov95 	ASM_OutDxAx(0xE317,0x03D4);
//DeadCode DAW 18Dec95 //DeadCode PD 03Nov95 
//DeadCode DAW 18Dec95 //DeadCode PD 03Nov95 	ASM_OutDxAx(0x0014,0x03D4);
//DeadCode DAW 18Dec95 //DeadCode PD 03Nov95 
//DeadCode DAW 18Dec95 //DeadCode PD 03Nov95 	ASM_OutDxAx(0x0604,0x03C4);
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	return(TRUE);
//DeadCode DAW 18Dec95 }
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 18Dec95 //Procedure	HardPrim::ScreenSwap
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 //Author		Paul.   
//DeadCode DAW 18Dec95 //Date		Mon 3 Jul 1995
//DeadCode DAW 18Dec95 //Modified	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Description	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Inputs	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Returns	
//DeadCode DAW 18Dec95 //
//DeadCode DAW 18Dec95 //Externals
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 //------------------------------------------------------------------------------
//DeadCode DAW 18Dec95 void HardPrim::ScreenSwap(ScreenRecord *screen,short UseNewPal)
//DeadCode DAW 18Dec95 {
//DeadCode DAW 18Dec95 	char	*src,*dest;
//DeadCode DAW 18Dec95 	long	tmp;
//DeadCode DAW 18Dec95 	short tmp2,tmp3;
//DeadCode DAW 18Dec95 	short i,visualpage;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	if((screen->ScreenNumOnLogical++)>screen->NumberOfScreens)
//DeadCode DAW 18Dec95 		screen->ScreenNumOnLogical = 0;
//DeadCode DAW 18Dec95 	
//DeadCode DAW 18Dec95 	tmp = screenlist.Physical;
//DeadCode DAW 18Dec95 	screenlist.Physical = screenlist.Logical;
//DeadCode DAW 18Dec95 	screenlist.Logical = screenlist.Other;
//DeadCode DAW 18Dec95 	screenlist.Other = tmp;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	switch(screen->CurrMode)
//DeadCode DAW 18Dec95 	{
//DeadCode DAW 18Dec95 		case MODE_320x200Debug:									//PD 03Nov95
//DeadCode DAW 18Dec95 			break;												//PD 03Nov95
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 		default:		//Default is set 320x200
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 		case MODE_320x200:
//DeadCode DAW 18Dec95 			ASM_CopyMainRAM2VidRAM((char *)screen->LogicalScreenPtr,
//DeadCode DAW 18Dec95 				(char *)screenlist.Physical);
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 			//Now actually swap the displayed screen
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 			tmp2 = (short )((screenlist.Physical - 0x0A0000)>>8);
//DeadCode DAW 18Dec95 			tmp3 = tmp2;
//DeadCode DAW 18Dec95 			tmp2 = (tmp2<<8) + 0x0C;				//hi byte
//DeadCode DAW 18Dec95 			tmp3 = (tmp3 & 0xFF00) + 0x0D;		//lo byte
//DeadCode DAW 18Dec95 			ASM_OutDxAx(tmp2,0x03D4);
//DeadCode DAW 18Dec95 			ASM_OutDxAx(tmp3,0x03D4);
//DeadCode DAW 18Dec95 			break;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 		case	MODE_640x480:
//DeadCode DAW 18Dec95 			src = (char *)screen->LogicalScreenPtr;
//DeadCode DAW 18Dec95 			dest = (char *)screenlist.Physical;
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 			for(i=visualpage=_getvisualpage();i<visualpage+4;i++){
//DeadCode DAW 18Dec95 				_setvisualpage(i);
//DeadCode DAW 18Dec95 				ASM_CopyMainRAM2VidRAMF(src,dest);
//DeadCode DAW 18Dec95 			}
//DeadCode DAW 18Dec95 			break;
//DeadCode DAW 18Dec95 	}
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 	if(UseNewPal == TRUE)
//DeadCode DAW 18Dec95 	{
//DeadCode DAW 18Dec95 		ASM_WaitVBL();
//DeadCode DAW 18Dec95 		ASM_SetPalette((char *)screen->Palette);
//DeadCode DAW 18Dec95 	}
//DeadCode DAW 18Dec95 }
//DeadCode DAW 18Dec95 
//DeadCode DAW 18Dec95 <<<<<<<<<<  hardprim.cpp  Rev "Tip" (1.2.7.0)
//DeadCode DAW 18Dec95 ==========

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	HardPrim::PlotPixel
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Mon 3 Jul 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Colour Display::PlotPixel(SWord X, SWord Y, Colour colour)
{
	short	MinX,MaxX,MinY,MaxY;
	short	ret_val = colour;
	long		screenbase;
	long		yoffset,xoffset;

	MinX = PhysicalMinX;
	MaxX = MinX + PhysicalWidth;

	MinY = PhysicalMinY;
	MaxY = MinY + PhysicalHeight;

	if(X>=MinX && X<=MaxX && Y>=MinY && Y<=MaxY)
	{
		yoffset = BytesPerScanLine * Y;
		xoffset = BytesPerPixel * X;
		screenbase = VESA.writeaddr;//screenlist.Physical;

		ret_val = ASM_PlotPixel(screenbase,xoffset,yoffset,colour);
	}
	return((Colour)ret_val);
}

//DeadCode JIM 13Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 13Dec95 //Procedure	HardPrim::SetTextMode
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //Author		Paul.   
//DeadCode JIM 13Dec95 //Date		Mon 3 Jul 1995
//DeadCode JIM 13Dec95 //Modified	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Description	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Inputs	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Returns	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Externals
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 void Display::SetTextMode(void )
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 	RMI.EAX = 0x00000003;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	regs.w.cx = 0;
//DeadCode JIM 13Dec95 	sregs.es = FP_SEG(&RMI);
//DeadCode JIM 13Dec95 	regs.x.edi = FP_OFF(&RMI);
//DeadCode JIM 13Dec95 	regs.w.ax = 0x0300;
//DeadCode JIM 13Dec95 	regs.w.bx = 0x0010;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	int386x(0x31, &regs, &regs, &sregs);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	//deallocate conventional DOS RAM used for DPMI real mode stack
//DeadCode JIM 13Dec95 	FreeDOSRAM(stkhndl);
//DeadCode JIM 13Dec95 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	HardPrim::ClearScreen
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Mon 3 Jul 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Display::ClearScreen(short colour)
{
	short	wx1,wx2,wy1,wy2;
	short	w,h;

	wx1 = PhysicalMinX;
	wx2 = wx1 + PhysicalWidth;

	wy1 = PhysicalMinY;
	wy2 = wy1 + PhysicalHeight;

	for(h=wy1;h<wy2;h++)
		for(w=wx1;w<wx2;w++)
			PlotPixel(w,h,Colour(colour));

}

//DeadCode JIM 13Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 13Dec95 //Procedure	GetDOSRAM
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //Author		Paul.   
//DeadCode JIM 13Dec95 //Date		Tue 25 Jul 1995
//DeadCode JIM 13Dec95 //Modified	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Description	Allocate a block of DOS RAM.	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Inputs		buffer = variable to point @ the allocated RAM
//DeadCode JIM 13Dec95 //			size   = no of bytes to allocate (rounded up to paras).	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Returns	handle to memory for free
//DeadCode JIM 13Dec95 //			buffer contains the address of the allocated RAM or NULL
//DeadCode JIM 13Dec95 //			if the alloc failed.
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Externals
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 short Display::GetDOSRAM(long& buffer, short size)
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 	//convert bytes to paragraphs
//DeadCode JIM 13Dec95 	if(size & 0x000F) size = (size >> 4) + 1;
//DeadCode JIM 13Dec95 	else size = size >> 4;
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	regs.w.ax=0x0100;
//DeadCode JIM 13Dec95 	regs.w.bx=size;												//JIM 25Oct95
//DeadCode JIM 13Dec95 	int386x( 0x031, &regs, &regs, &sregs);
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 	buffer = regs.w.ax<<4;
//DeadCode JIM 13Dec95 	return(regs.w.dx);
//DeadCode JIM 13Dec95 }
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 Bool Display::GetDOSRAM(DPMIMem&	dpmimem,			//Definition for mem region
//DeadCode JIM 13Dec95 						ULong	size,		//0		//Size overiding dpmimem.size
//DeadCode JIM 13Dec95 						ULong	off			//-1	//Offset overriding dpmimem.off
//DeadCode JIM 13Dec95 						)
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 	if	(size)
//DeadCode JIM 13Dec95 		dpmimem.size=size;
//DeadCode JIM 13Dec95 	if	(off!=-1)
//DeadCode JIM 13Dec95 		dpmimem.off=off;
//DeadCode JIM 13Dec95 	//convert bytes to paragraphs
//DeadCode JIM 13Dec95 	size=(dpmimem.size+0x0f)>>4;
//DeadCode JIM 13Dec95 	regs.w.ax=0x0100;
//DeadCode JIM 13Dec95 	regs.w.bx=size;												//JIM 25Oct95
//DeadCode JIM 13Dec95 	int386x( 0x031, &regs, &regs, &sregs);
//DeadCode JIM 13Dec95 	if (regs.w.cflag && rminfo::CF)
//DeadCode JIM 13Dec95 		_Error.EmitSysErr("DOS mem request failed for %d",dpmimem.size);
//DeadCode JIM 13Dec95 	dpmimem.desc=regs.w.dx;
//DeadCode JIM 13Dec95 	dpmimem.seg=regs.w.ax;
//DeadCode JIM 13Dec95 	dpmimem.flat=(void*) (((ULong) regs.w.ax)<<4+off);
//DeadCode JIM 13Dec95 	return(TRUE);
//DeadCode JIM 13Dec95 }
//DeadCode JIM 13Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 13Dec95 //Procedure	FreeDOSRAM
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //Author	Paul.   
//DeadCode JIM 13Dec95 //Date		Tue 25 Jul 1995
//DeadCode JIM 13Dec95 //Modified	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Description	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Inputs	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Returns	
//DeadCode JIM 13Dec95 //
//DeadCode JIM 13Dec95 //Externals
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 13Dec95 void Display::FreeDOSRAM(short handle)
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 	regs.w.ax=0x0101;
//DeadCode JIM 13Dec95 	regs.w.dx=handle;
//DeadCode JIM 13Dec95 	int386x( 0x031, &regs, &regs, &sregs);
//DeadCode JIM 13Dec95 }
//DeadCode JIM 13Dec95 
//DeadCode JIM 13Dec95 void Display::FreeDOSRAM(DPMIMem& handle)
//DeadCode JIM 13Dec95 {
//DeadCode JIM 13Dec95 		FreeDOSRAM(handle.desc);
//DeadCode JIM 13Dec95 }
//DeadCode JIM 13Dec95 
