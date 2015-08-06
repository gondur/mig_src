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
//Filename       hardinit.cpp
//System         
//Author         Jim Taylor
//Date           Tue 12 Dec 1995
//Description    Graphics hardware initialisation. Selecting the correct driver.
//				The stuff in here is to do with low level graphics, 
//				does not live in the runtime library - either because it is
//				choosing which runtime library, or because it is not a 
//				'low level' feature.
//
//------------------------------------------------------------------------------

#include	<dos.h>

#define	F_GRAFIX
#include	"DosDefs.H"
#include "Palette.H"
#define	F_BATTLE
#define	F_GRAFIX
#include	"Display.H"
#include	"myError.h"
#include	"hardpasm.h"
#include	"polygon.h"
extern	"C"	void		ASM_SetPalette(char *);
extern	"C"	void		ASM_WaitVBL(void );

//TempCode JIM 08Jul96 #include	"time.h"

// debug only
ULong marker = 0;												//ARM 27Nov96

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GetDOSRAM
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 25 Jul 1995
//Modified	
//
//Description	Allocate a block of DOS RAM.	
//
//Inputs		buffer = variable to point @ the allocated RAM
//			size   = no of bytes to allocate (rounded up to paras).	
//
//Returns	handle to memory for free
//			buffer contains the address of the allocated RAM or NULL
//			if the alloc failed.
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
short Display::GetDOSRAM(long& buffer, short size)
{

#ifndef WIN95

	DPMIregs regs;
	//convert bytes to paragraphs
	if(size & 0x000F) size = (short) ((size >> 4) + 1);
	else size = (short)(size >> 4);

	regs.w.ax=0x0100;
	regs.w.bx=size;												//JIM 25Oct95
	ASM_DEXint31(&regs);
//DeadCode ARM 04Jun96 	int386( 0x031, &regs, &regs);

	buffer = regs.w.ax<<4;
	return(regs.w.dx);

#else

	buffer = (int)new char [size];

	return TRUE;

#endif

}

Bool Display::GetDOSRAM(DPMIMem&	dpmimem,			//Definition for mem region
						ULong	size,		//0		//Size overiding dpmimem.size
						UWord	off			//-1	//Offset overriding dpmimem.off
						)
{

#ifndef WIN95
	
	DPMIregs	regs;
	if	(size)
		dpmimem.size=size;
	if	(off!=-1)
		dpmimem.off=off;
	//convert bytes to paragraphs
	size=(dpmimem.size+0x0f)>>4;
	regs.w.ax=0x0100;
	regs.w.bx=(UWord)size;												//JIM 25Oct95
	ASM_DEXint31(&regs);
//DeadCode ARM 04Jun96 	int386( 0x031, &regs, &regs);
	if (regs.flags & regs.CF)
		_Error.EmitSysErr("DOS mem request failed for %d",dpmimem.size);
	dpmimem.desc=regs.w.dx;
	dpmimem.seg=regs.w.ax;
	dpmimem.flat=(void*) (((ULong) regs.w.ax)<<4+off);

#else

	dpmimem.flat = new char [size];
	dpmimem.desc = TRUE;
	dpmimem.seg = TRUE;

#endif

	return(TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	FreeDOSRAM
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Tue 25 Jul 1995
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
void Display::FreeDOSRAM(short handle)
{
#ifndef WIN95

	DPMIregs	regs;
	regs.w.ax=0x0101;
	regs.w.dx=handle;
	ASM_DEXint31(&regs);
//DeadCode ARM 04Jun96 	int386( 0x031, &regs, &regs);

#endif

}

void Display::FreeDOSRAM(DPMIMem& handle)
{

#ifndef WIN95
		FreeDOSRAM(handle.desc);
#else

		delete [] handle.flat;

#endif
}
	


//------------------------------------------------------------------------------

void	Display::MemScreen(ScreenPages dpg)
{

#ifndef WIN95

	int	rpg=dpg+ScreenNumOnLogical;
	if (rpg<0)	rpg+=NumberOfScreens;
	if (rpg>=NumberOfScreens) rpg-=NumberOfScreens;
	logicalscreenptr=(LogicalPtr) VFLAT.screen + VFLAT.scrsize * rpg;

#else

	DirectDraw_MemScreen(dpg);										//ARM 23Jul96

#endif

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindModeWin
//Author		Jim Taylor
//Date			Tue 12 Dec 1995
//
//Description	Tests if we can set this mode up under windows
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Display::FindModeWin(InitDisplayDef&)
{

#ifndef WIN95
	return FALSE;
#else
	ScreenNumOnLogical=0;
	prevmodeAX=0xffff;
//TempCode ARM 01Jul96 	csecs = 10;
//TempCode ARM 01Jul96 	accelrate = -1;
	return TRUE;
#endif

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectLibWin
//Author		Jim Taylor
//Date			Tue 12 Dec 1995
//
//Description	Selects correct driver file given general windows support
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
FileNum	Display::SelectLibWin()
{
	return (INVALIDFILENUM);
}
enum	{	VESA_1=31,
			VESA_support=1,VESA_info=2,VESA_bios=4,VESA_colour=8,VESA_graphics=16,
		 	VESA_2=255,
			VESA_nonvga=32,VESA_NoBank=64,VESA_Linear=128};
enum	{VWIN_avail=1,VWIN_read=2,VWIN_write=4};

struct	VesaModeInfo
{
 	UWord	flags;
	UByte	WinAFlags;
	UByte	WinBFlags;
	UWord	Granularity;
	UWord	WinSize;
	UWord	WinASeg;
	UWord	WinBSeg;
	ULong	DirectCall;
	UWord	BytesPerScanLine;
//extended info
	UWord	HoriRes;
	UWord	VertRes;
	UByte	XXCharWid;
	UByte	XXCharHeight;
	UByte	XXBitPlanes;
	UByte	BitPerPixel;
	UByte	XXMemBanks;
	UByte	MemModel;
	UByte	XXMemBanksize;
	UByte	DisplayPages;
	UByte	ResByte1;
//vesa 1.2 info
	UByte	rgbmsp[4][2];
	enum	{V12FLAG_pal68=1,V12FLAG_pl4avail};
	UByte	v12flag;
//vesa 2.0 info
	ULong	linscr1;
	ULong	linscr2;
	ULong	linmemk;
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ListVesaModes
//Author		Jim Taylor
//Date			Wed 23 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Window::ListVesaModes(ScreenRez* modelist)
{
	((Display*)master)->ListVesaModes(modelist);
}

void	Display::ListVesaModes(ScreenRez* modelist)
{
	for (int i=0;i<20;i++)
	{
		modelist[i].width=0;
		modelist[i].colourdepth=8;
		modelist[i].driver=-1;
	}
	DPMIregs	regs;											//JIM 13Dec96

	regs.w.ax=0x4f00;
 	regs.w.di=0;

	*((ULong*) real_mode_stack)=*((ULong*) "VBE2");
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	if (	(regs.w.ax!=0x004f)
		||	(*((ULong*) real_mode_stack)!=*((ULong*) "VESA"))	)
	{
//Old_Code PD 04Feb97 		*(modelist++)=-320;

		modelist->width=-320;									//PD 04Feb97
		modelist++;												//PD 04Feb97
		return;
	}
	Bool	done320=FALSE;

	int	Modeflagmask=VESA_1;
	if (((UWord*) real_mode_stack)[2]>=0x0200)
		Modeflagmask=VESA_2;

	int	videomem=((UWord*) real_mode_stack)[9]*65536;
	
	UWord*	tablesrc=(UWord*)
						(		((UWord*) real_mode_stack)[7]
							+16*((UWord*) real_mode_stack)[8]	);
	int	tableentries=0;
	while(tablesrc[tableentries++]!=0xffff)	{}

	VesaModeInfo	&vesainfo=*((VesaModeInfo*) real_mode_stack);
	{	//declare temporary array big enough to copy list in. 
		UWord tablecopy[100];	//modes supported
		tablecopy[tableentries-1]=0xffff;
		while (tableentries--)
			tablecopy[tableentries]=tablesrc[tableentries];
		//now I can stomp the stack without worrying about the table being there!
		//for each mode, check if its the one I want.
		for (tablesrc=tablecopy;*tablesrc!=0xffff;tablesrc++)
		{
			regs.w.ax=0x4f01;
			regs.w.cx=*tablesrc;
			regs.w.bx=*tablesrc;
		 	regs.w.di=0;
			ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
		 	if (	(regs.w.ax==0x004f)
				&& (vesainfo.flags&(VESA_support+VESA_graphics))
				)
			{
				if (!(vesainfo.flags&VESA_info))
				{	//if no info then fill in from general knowledge
					vesainfo.BitPerPixel=8;
					vesainfo.MemModel=5;
					switch (*tablesrc)
					{
					case 0x100: vesainfo.HoriRes=640; vesainfo.VertRes=400;	break;
					case 0x101: vesainfo.HoriRes=640; vesainfo.VertRes=480;	break;
					case 0x103: vesainfo.HoriRes=800; vesainfo.VertRes=600;	break;
					case 0x105: vesainfo.HoriRes=1024;vesainfo.VertRes=768;	break;
					case 0x107: vesainfo.HoriRes=1280;vesainfo.VertRes=1024;break;
					default:	vesainfo.HoriRes=-1;vesainfo.VertRes=-1;
					}
				}
			
				//now need to do test math...
				int	h=vesainfo.HoriRes;
				if (
						(vesainfo.flags&VESA_graphics)
					&&	vesainfo.BitPerPixel==8
					&&	vesainfo.BitPerPixel==8
					&&	(25600%h)==0 && (h&3)==0
					&& (vesainfo.VertRes*4)/h==3)	//lets through 1280/1024 but stops 640x400(2) and 320x400(5)
				{	//we might be interested... ok... we are interested!
//Old_Code PD 04Feb97 					*(modelist++)=-h;
					modelist->width=-h;							//PD 04Feb97
					modelist++;									//PD 04Feb97

					if (h==320)
						done320=TRUE;
					if (	(vesainfo.flags&Modeflagmask&VESA_Linear)
						&&	videomem>=2*vesainfo.VertRes*h	)
						{
//Old_Code PD 04Feb97 						*(modelist++)=h;
							modelist->width=h;					//PD 04Feb97
							modelist++;							//PD 04Feb97
						}
				}
			}
		}
	}
	if (done320==FALSE)
//Old_Code PD 04Feb97 		*(modelist++)=-320;
	{
		modelist->width=-320;									//PD 04Feb97
		modelist++;												//PD 04Feb97
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindModeVESA
//Author		Jim Taylor
//Date			Tue 12 Dec 1995
//
//Description	Tests to see if given resolution supported by VESA drivers
//
//Inputs		mode defines X,Y,colourdepth
//
//Returns		If TRUE, then sets up most fields.
//
//------------------------------------------------------------------------------
Bool	Display::FindModeVESA(InitDisplayDef& mode)
{
	DPMIregs	regs;											//JIM 13Dec96
	regs.w.ax=0x0f00;
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	if (prevmodeAX==0)
		prevmodeAX=(UWord) (regs.w.ax&0x007f);
	regs.w.ax=0x4f00;
 	regs.w.di=0;
	Bool	debugmode=FALSE;
	svgalibmodefix=SVGA_VESAc;
	if (mode.colourdepth<0)
	{
		svgalibmodefix=SVGA_VESAd;
		mode.colourdepth=-mode.colourdepth;
	 	debugmode=TRUE;
	}
	*((ULong*) real_mode_stack)=*((ULong*) "VBE2");
	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	if (	(regs.w.ax!=0x004f)
		||	(*((ULong*) real_mode_stack)!=*((ULong*) "VESA"))	)
		return(FALSE);

	int	Modeflagmask=VESA_1;
	if (((UWord*) real_mode_stack)[2]>=0x0200)
		Modeflagmask=VESA_2;
	if (mode.width<0)
	{
		Modeflagmask=VESA_1;
		mode.width=-mode.width;
		if (mode.height<0)
			mode.height=-mode.height;
	}

	VESA.videomem=((UWord*) real_mode_stack)[9];
	UWord*	tablesrc=(UWord*)
						(		((UWord*) real_mode_stack)[7]
							+16*((UWord*) real_mode_stack)[8]	);
	int	tableentries=0;
	while(tablesrc[tableentries++]!=0xffff);//intentional

	UWord	perfectmodematch=-1;	//coords and colour depth spot on mode
	UWord	goodmodematch=-1;		//colour depth acceptable. coords fine
	UWord	medmodematch=-1;		//coords close (<25% greater X+Y)
	UWord	poormodematch=-1;		//coords close and depth close
	UWord	badmodematch=-1;		//coords significantly high. depth ok
	VesaModeInfo	&vesainfo=*((VesaModeInfo*) real_mode_stack);
	{	//declare temporary array big enough to copy list in. 
		UWord tablecopy[100];	//modes supported
		tablecopy[tableentries-1]=0xffff;
		while (tableentries--)
			tablecopy[tableentries]=tablesrc[tableentries];
		//now I can stomp the stack without worrying about the table being there!
		//for each mode, check if its the one I want.
		for (tablesrc=tablecopy;*tablesrc!=0xffff;tablesrc++)
		{
			regs.w.ax=0x4f01;
			regs.w.cx=*tablesrc;
			regs.w.bx=*tablesrc;
		 	regs.w.di=0;
			ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
		 	if (	(regs.w.ax==0x004f)
				&& (vesainfo.flags&(VESA_support+VESA_graphics))
				)
			{
				if (!(vesainfo.flags&VESA_info))
				{	//if no info then fill in from general knowledge
					vesainfo.BitPerPixel=8;
					vesainfo.MemModel=5;
					switch (*tablesrc)
					{
					case 0x100: vesainfo.HoriRes=640; vesainfo.VertRes=400;	break;
					case 0x101: vesainfo.HoriRes=640; vesainfo.VertRes=480;	break;
					case 0x103: vesainfo.HoriRes=800; vesainfo.VertRes=600;	break;
					case 0x105: vesainfo.HoriRes=1024;vesainfo.VertRes=768;	break;
					case 0x107: vesainfo.HoriRes=1280;vesainfo.VertRes=1024;break;
					default:	vesainfo.HoriRes=-1;vesainfo.VertRes=-1;
					}
				}
				if (	(vesainfo.HoriRes==mode.width)
				  	&&	(vesainfo.VertRes==mode.height)
					&&	(vesainfo.BitPerPixel==mode.colourdepth)
					)
					perfectmodematch=*tablesrc;
				else	//less than perfect.
				if (	(	(vesainfo.HoriRes>=mode.width)
						&&	(vesainfo.VertRes==mode.height)
						)
					|| 	(	(vesainfo.HoriRes==mode.width)
						&&	(vesainfo.VertRes>=mode.height)
						)
					&&	(vesainfo.BitPerPixel==mode.colourdepth)
					)
					goodmodematch=*tablesrc;
				else
				if (	(	(vesainfo.HoriRes>=mode.width)
						&&	(vesainfo.VertRes>=mode.height)
						)
					&&	(vesainfo.BitPerPixel==mode.colourdepth)
					)
					medmodematch=*tablesrc;
			}
		}

//quicky: what's the current mode?
		if (prevmodeBX==0)
		{
			regs.w.ax=0x4f03;
			ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
			if (regs.w.bx>=0x0100)
			{
				prevmodeAX=0x4f02;
				prevmodeBX=(UWord)(regs.w.bx&0x7fff);
			}
			else
				prevmodeBX=-1;
		}
		
//now use the data collected so-far

		//
		//Work to do:
		//	What if not perfect match?
		//	Detecting a flat memory display?
		//	Debug mode if flat display?
		//	WinA/B cleverness
		//
		if (perfectmodematch==0xFFFF)
			if (goodmodematch!=0xFFFF)
				perfectmodematch=goodmodematch;
//TempCode JIM 27Mar96 			else
//TempCode JIM 27Mar96 				perfectmodematch=medmodematch;

		if (perfectmodematch!=0xFFFF)
		{	//start filling in
			regs.w.ax=0x4f01;
			regs.w.cx=perfectmodematch;
			regs.w.bx=perfectmodematch;
		 	regs.w.di=0;
			ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
			
			BytesPerPixel=(mode.colourdepth+7)>>3;
			BytesPerScanLine=mode.width*BytesPerPixel;
			PhysicalMinX=0;PhysicalMinY=0;
			PhysicalWidth=mode.width;
			PhysicalHeight=mode.height;
	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1;
	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1;
			ScreenNumOnLogical=0;
			VirtualMinX=0;VirtualMinY=0;
			VirtualWidth=V_MAXX;
			VirtualHeight=V_MAXY;
			virtualXscale=V_MAXX/mode.width;
			if (V_MAXX%mode.width)
				_Error.EmitSysErr("Input width is not divisible by virtual resolution!");
			virtualYscale=V_MAXY/mode.height;

			if (	vesainfo.flags&Modeflagmask&VESA_Linear
				&&	VESA.videomem*65536>=mode.width*BytesPerPixel*mode.height*2	//else ignore vbe2
				)
			{

				if (VESA.videomem*65536>=mode.width*BytesPerPixel*mode.height*3)
					NumberOfScreens=3;
				else
					NumberOfScreens=2;
				if (svgalibmodefix==SVGA_VESAc)
					svgalibmodefix=SVGA_VESAf;
				VFLAT.mode=perfectmodematch+0x4000;
				VFLAT.screen=vesainfo.linscr1;
				VFLAT.lineshift=PhysicalHeight;
				VFLAT.colshift=0;
				VFLAT.extrarama=vesainfo.linscr2;
				VFLAT.extrarams=vesainfo.linmemk*1024;
				//moved back to hardware lib
			}
			else
			{
				svgalibmodefix=SVGA_VESAc;
				VESA.mode=perfectmodematch;
				logicalscreenptr=NULL;
			 	NumberOfScreens=1;
				if (vesainfo.DisplayPages>1)
					VESA.Screens=2;
				else
					VESA.Screens=1;
				//a few dirty fixes
				VESA.BytesPerScanLine=vesainfo.BytesPerScanLine;
				VESA.ScanLines=mode.height;
				VESA.BytesPerPixel=BytesPerPixel;
				VESA.BitsPerPixel=vesainfo.BitPerPixel;
				VESA.ScreenNum=0;
				VESA.PageNum=-1;
				VESA.pagetop=0;
				VESA.pageoff=0;
				VESA.PageSize=vesainfo.WinSize*1024;
				VESA.PageShift=VESA.PageSize/(vesainfo.Granularity*1024);	//should always be 1 or more

				//Assuming 'win a read/write'. Use flags to improve this.
				VESA.readaddr=vesainfo.WinASeg*16;
				VESA.writeaddr=vesainfo.WinASeg*16;
				VESA.readwin=0;
				VESA.writewin=0;
			}
			return(TRUE);

		}
	if (debugmode)
		mode.colourdepth=-mode.colourdepth;
	return(FALSE);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectLibVESA
//Author		Jim Taylor
//Date			Tue 12 Dec 1995
//
//Description	Supposed to select the correct vesa driver library based on 
//				info filled in above.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
FileNum	Display::SelectLibVESA()
{
 	
	if (svgalibmodefix==SVGA_VESAc)
		return (LIB_VBE_COPY);
	elser
	if (svgalibmodefix==SVGA_VESAf)
		return (LIB_VBE_SWAP2);
	elser
		return (LIB_VBE_DEBUG);
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindModeDirty
//Author		Jim Taylor
//Date			Tue 12 Dec 1995
//
//Description	Supposed to test for custom driver (eg 320x240)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Display::FindModeDirty(InitDisplayDef& mode)
{
	if (mode.width!=320)
		return(FALSE);
	if (mode.colourdepth==-8)
		svgalibmodefix=SVGA_CUSTOM_1d;
	if (mode.colourdepth==8)
		svgalibmodefix=SVGA_CUSTOM_1c;
	logicalscreenptr=NULL;
	BytesPerPixel=1;
	BytesPerScanLine=320;
	PhysicalMinX=0;PhysicalMinY=0;
	PhysicalWidth=mode.width;
	PhysicalHeight=mode.height;
	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1;
	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1;
	ScreenNumOnLogical=0;
	NumberOfScreens=1;
	VirtualMinX=0;VirtualMinY=0;
	VirtualWidth=V_MAXX;
	VirtualHeight=V_MAXY;
	virtualXscale=V_MAXX/mode.width;
	if (V_MAXX%mode.width)
		_Error.EmitSysErr("Input width is not divisible by virtual resolution!");
	virtualYscale=V_MAXY/mode.height;
	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectLibDirty
//Author		Jim Taylor
//Date			Tue 12 Dec 1995
//
//Description	Supposed to load selected custom driver
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
FileNum	Display::SelectLibDirty()
{
	if(svgalibmodefix==SVGA_CUSTOM_1d)
		return (LIB_320_DEBUG);
	else
		return (LIB_320_COPY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadGraphicsLib
//Author		Jim Taylor
//Date			Wed 13 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Display::LoadGraphicsLib(FileNum f)
{

	if (f == INVALIDFILENUM) return;							//ARM 07Jun96

	STUBLOAD(Display::,f);
}
///
///
///
///	THE STUFF BELOW SHOULDN@T BE HERE!!!!!!!
///
///
///
///
///
///
///
///	THE STUFF BELOW SHOULDN@T BE HERE!!!!!!!
///
///
///
///
///


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChangeRes
//Author		Jim Taylor
//Date			Fri 8 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Display::ChangeRes(ScreenRez& srez)
{
	UseNewPal = TRUE;
	InitDisplayDef	idd=
	{
		srez.width,
		srez.width*3/4,
		8,-1
	};															//PD 20May97
	LogicalPtr	oldscreenaddr=logicalscreenptr;
	int			oldbytesperscanline=BytesPerScanLine;
	int			oldscalex=virtualXscale;
	int			oldscaley=virtualYscale;
	POLYGON.DeleteYList();

	Whole_Screen->Exit();
	Whole_Screen->Init(idd);
	Window*	window=(Window*)	windowlink;
	while (window)
	{
		if (window->logicalscreenptr!=oldscreenaddr)
		{
			int	oldx=window->logicalscreenptr-oldscreenaddr;
			int	oldy=oldx/oldbytesperscanline;
			oldx=oldx%oldbytesperscanline;

			oldx*=oldscalex;
			oldy*=oldscaley;
			oldx/=virtualXscale;
			oldy/=virtualYscale;

			oldx=oldx+oldy*BytesPerScanLine;
			window->logicalscreenptr=logicalscreenptr+oldx;
		}
		else
			window->logicalscreenptr=logicalscreenptr;

		window->NumberOfScreens=NumberOfScreens;
		window->virtualXscale*=virtualXscale;
		window->virtualXscale/=oldscalex;
		window->virtualYscale*=virtualYscale;
		window->virtualYscale/=oldscaley;

		window->BytesPerScanLine=BytesPerScanLine;
		window->NumberOfScreens	=NumberOfScreens;
		window->PhysicalWidth=	window->VirtualWidth	/window->virtualXscale;
		window->PhysicalHeight=	window->VirtualHeight	/window->virtualYscale;
		window->PhysicalMinX=	window->VirtualMinX		/window->virtualXscale;
		window->PhysicalMinY=	window->VirtualMinY		/window->virtualYscale;
		window->PhysicalMaxX=window->PhysicalMinX+window->PhysicalWidth-1;
		window->PhysicalMaxY=window->PhysicalMinY+window->PhysicalHeight-1;
		window->VirtualWidth	=window->PhysicalWidth		*window->virtualXscale;
		window->VirtualHeight	=window->PhysicalHeight		*window->virtualYscale;
		window->VirtualMinX		=window->PhysicalMinX		*window->virtualXscale;
		window->VirtualMinY		=window->PhysicalMinY		*window->virtualYscale;

		window=(Window*)window->windowlink;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Exit
//Author		R. Hyde 
//Date			Wed 30 Oct 1996
//
//Description	release logical screen memory on exit / mode change
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Display::Exit()
{
	ResetGraphicsMode();
	LogicalPtr lp=logicalscreenptr;
	logicalscreenptr=NULL;
	if (lp)
	{
		if (_Error.exitmsg==NULL)
		{
			int	i;
			for (i=0;i<500;i++)
				if (lp[(int)PhysicalWidth * PhysicalHeight+i]!=0xfa)
					_Error.EmitSysErr("Off screen write after screen at %i",i);

			lp-=500;
			for (i=0;i<500;i++)
				if (lp[i]!=0xb4)
					_Error.EmitSysErr("Off screen write before screen at %i",i);
		}
		delete [] lp;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTextMode
//Author		Jim Taylor
//Date			Tue 12 Dec 1995
//
//Description	Set back to remembered text mode
//				Needs to cope with windows!
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Display::SetTextMode()
{
	if (prevmodeAX)
	{

		DPMIregs	regs;
		regs.flags=DPMIregs::CLEAR;
	 	regs.w.ax=prevmodeAX;
	 	regs.w.bx=prevmodeBX;
		ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);

	}
	Exit();
}






//DeadCode JIM 19Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 19Feb96 //Procedure		SetGraphicsMode
//DeadCode JIM 19Feb96 //Author		Jim Taylor
//DeadCode JIM 19Feb96 //Date			Tue 12 Dec 1995
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Description	STUB:	Actually change to the selected mode
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Inputs		
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Returns	
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 void	Display::SetGraphicsMode()
//DeadCode JIM 19Feb96 {
//DeadCode JIM 19Feb96  	switch (svgalibmodefix)
//DeadCode JIM 19Feb96 	{
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_winc:		return	SetGraphicsMode_winc	()
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_winf:		return	SetGraphicsMode_winf	()
//DeadCode JIM 19Feb96 	case SVGA_CUSTOM_1d:	SetGraphicsMode_CUSTOM_1d	();return;
//DeadCode JIM 19Feb96 	case SVGA_CUSTOM_1c:	SetGraphicsMode_CUSTOM_1c	();return;
//DeadCode JIM 19Feb96 	case SVGA_VESAc:	SetGraphicsMode_VESAc	();return;
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_VESAf:	return	SetGraphicsMode_VESAf	()
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_CUSTOM_1:	return	SetGraphicsMode_CUSTOM_1();
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_CUSTOM_2:	return	SetGraphicsMode_CUSTOM_2()
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_CUSTOM_3:	return	SetGraphicsMode_CUSTOM_3()
//DeadCode JIM 19Feb96 	}
//DeadCode JIM 19Feb96 }
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 19Feb96 //Procedure		ScreenFlip
//DeadCode JIM 19Feb96 //Author		Jim Taylor
//DeadCode JIM 19Feb96 //Date			Tue 12 Dec 1995
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Description	Flip/Swap the screen - physically do it!
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Inputs		
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Returns	
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 void	Display::ScreenFlip()
//DeadCode JIM 19Feb96 {
//DeadCode JIM 19Feb96  	switch (svgalibmodefix)
//DeadCode JIM 19Feb96 	{
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_winc:		return	ScreenFlip_winc	()
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_winf:		return	ScreenFlip_winf	()
//DeadCode JIM 19Feb96 	case SVGA_CUSTOM_1d:	ScreenFlip_CUSTOM_1d	();return;
//DeadCode JIM 19Feb96 	case SVGA_CUSTOM_1c:	ScreenFlip_CUSTOM_1c	();return;
//DeadCode JIM 19Feb96 	case SVGA_VESAc:	ScreenFlip_VESAc	();return;
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_VESAf:	return	ScreenFlip_VESAf	()
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_CUSTOM_1:	return	ScreenFlip_CUSTOM_1();
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_CUSTOM_2:	return	ScreenFlip_CUSTOM_2()
//DeadCode JIM 19Feb96 //TempCode JIM 12Dec95 	case SVGA_CUSTOM_3:	return	ScreenFlip_CUSTOM_3()
//DeadCode JIM 19Feb96 	}
//DeadCode JIM 19Feb96 }

//DeadCode JIM 19Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 19Feb96 //Procedure		SetGraphicsMode_VESAc
//DeadCode JIM 19Feb96 //Author		Jim Taylor
//DeadCode JIM 19Feb96 //Date			Tue 12 Dec 1995
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Description	
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Inputs		
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Returns	
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 void	Display::SetGraphicsMode_VESAc	()
//DeadCode JIM 19Feb96 {
//DeadCode JIM 19Feb96 	DPMIregs	regs;
//DeadCode JIM 19Feb96 	regs.w.ax=0x4f02;
//DeadCode JIM 19Feb96 	regs.w.cx=VESA.mode;
//DeadCode JIM 19Feb96 	regs.w.bx=VESA.mode;
//DeadCode JIM 19Feb96 	regs.w.di=0;
//DeadCode JIM 19Feb96 	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode JIM 19Feb96 	if (regs.w.ax!=0x004f)
//DeadCode JIM 19Feb96 	{
//DeadCode JIM 19Feb96 		INT3();
//DeadCode JIM 19Feb96 	}
//DeadCode JIM 19Feb96 }
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 19Feb96 //Procedure		ScreenFlip_VESAc
//DeadCode JIM 19Feb96 //Author		Jim Taylor
//DeadCode JIM 19Feb96 //Date			Tue 12 Dec 1995
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Description	Flip the displayed screen by copying
//DeadCode JIM 19Feb96 //				1) Calculate the base page and offset for the new screen
//DeadCode JIM 19Feb96 //				2) Copy the data a page at a time
//DeadCode JIM 19Feb96 //				3) hardware flip if avaialble
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Inputs		
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Returns	
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 void	Display::ScreenFlip_VESAc()
//DeadCode JIM 19Feb96 {
//DeadCode JIM 19Feb96 	DPMIregs	regs;
//DeadCode JIM 19Feb96 int	skipbytes,Lines,Columns,page;
//DeadCode JIM 19Feb96 	if (++VESA.ScreenNum>=VESA.Screens)
//DeadCode JIM 19Feb96 		VESA.ScreenNum=0;
//DeadCode JIM 19Feb96 int	physicaloffset=VESA.ScreenNum*VESA.BytesPerScanLine*VESA.ScanLines;
//DeadCode JIM 19Feb96 	page=
//DeadCode JIM 19Feb96 		VESA.pagetop=physicaloffset/VESA.PageShift;
//DeadCode JIM 19Feb96 	VESA.pageoff=physicaloffset%VESA.PageShift;
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 	if (VESA.BytesPerScanLine==BytesPerScanLine)
//DeadCode JIM 19Feb96 	{
//DeadCode JIM 19Feb96 		skipbytes=0;
//DeadCode JIM 19Feb96 		Lines=1;
//DeadCode JIM 19Feb96 		Columns=BytesPerScanLine*PhysicalHeight;
//DeadCode JIM 19Feb96 	}
//DeadCode JIM 19Feb96 	else
//DeadCode JIM 19Feb96 	{
//DeadCode JIM 19Feb96 		skipbytes=VESA.BytesPerScanLine-BytesPerScanLine;
//DeadCode JIM 19Feb96 		Lines=PhysicalHeight;
//DeadCode JIM 19Feb96 		Columns=BytesPerScanLine;
//DeadCode JIM 19Feb96 	}
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 	LogicalPtr	src=logicalscreenptr;
//DeadCode JIM 19Feb96 	char*		trg=(char*)VESA.writeaddr;
//DeadCode JIM 19Feb96 	int			off=VESA.pageoff;
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 	//set to page
//DeadCode JIM 19Feb96 	regs.w.ax=0x4f05;
//DeadCode JIM 19Feb96 	regs.w.bx=VESA.writewin;
//DeadCode JIM 19Feb96 	regs.w.dx=page;
//DeadCode JIM 19Feb96 	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 	while (Lines--)
//DeadCode JIM 19Feb96 	{
//DeadCode JIM 19Feb96 int		colleft=Columns;
//DeadCode JIM 19Feb96 		while (off+colleft>VESA.PageSize)
//DeadCode JIM 19Feb96 		{
//DeadCode JIM 19Feb96 int			tmpleft=VESA.PageSize-off;
//DeadCode JIM 19Feb96 			colleft=colleft-tmpleft;
//DeadCode JIM 19Feb96 //TempCode JIM 14Dec95 			ASM_blat(trg+off,src,tmpleft);
//DeadCode JIM 19Feb96 //TempCode JIM 14Dec95 			src+=tmpleft;
//DeadCode JIM 19Feb96 			tmpleft=tmpleft>>2;
//DeadCode JIM 19Feb96 			while (tmpleft--)
//DeadCode JIM 19Feb96 			{
//DeadCode JIM 19Feb96 				*((ULong*) (trg+off))=*((LogicalLPtr) src);
//DeadCode JIM 19Feb96 				src+=4;
//DeadCode JIM 19Feb96 				off+=4;
//DeadCode JIM 19Feb96 			}
//DeadCode JIM 19Feb96 			off=0;
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 			//set to next page
//DeadCode JIM 19Feb96 			page+=VESA.PageShift;
//DeadCode JIM 19Feb96 			regs.w.ax=0x4f05;
//DeadCode JIM 19Feb96 			regs.w.bx=VESA.writewin;
//DeadCode JIM 19Feb96 			regs.w.dx=page;
//DeadCode JIM 19Feb96 			ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 		}
//DeadCode JIM 19Feb96 //TempCode JIM 14Dec95 			ASM_blat(trg+off,src,colleft);
//DeadCode JIM 19Feb96 //TempCode JIM 14Dec95 			src+=colleft;
//DeadCode JIM 19Feb96 //TempCode JIM 14Dec95 		off+=colleft;
//DeadCode JIM 19Feb96 		colleft=colleft>>2;
//DeadCode JIM 19Feb96 		while (colleft--)
//DeadCode JIM 19Feb96 		{
//DeadCode JIM 19Feb96 			*((ULong*) (trg+off))=*((LogicalLPtr) src);
//DeadCode JIM 19Feb96 			src+=4;
//DeadCode JIM 19Feb96 			off+=4;
//DeadCode JIM 19Feb96 		}
//DeadCode JIM 19Feb96 		off+=skipbytes;
//DeadCode JIM 19Feb96 	}
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 }
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 19Feb96 //Procedure		SetGraphicsMode_CUSTOM_1d
//DeadCode JIM 19Feb96 //Author		Jim Taylor
//DeadCode JIM 19Feb96 //Date			Thu 14 Dec 1995
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Description	Debugable 320x200
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Inputs		
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Returns	
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 void	Display::SetGraphicsMode_CUSTOM_1d()
//DeadCode JIM 19Feb96 {
//DeadCode JIM 19Feb96 	DPMIregs	regs;
//DeadCode JIM 19Feb96  	regs.w.ax=0x0013;
//DeadCode JIM 19Feb96 	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode JIM 19Feb96 	logicalscreenptr=(LogicalPtr) ((void*) 0xA0000);
//DeadCode JIM 19Feb96 }
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 void	Display::ScreenFlip_CUSTOM_1d()
//DeadCode JIM 19Feb96 {;
//DeadCode JIM 19Feb96 }
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 void	Display::SetGraphicsMode_CUSTOM_1c()
//DeadCode JIM 19Feb96 {
//DeadCode JIM 19Feb96 	DPMIregs	regs;
//DeadCode JIM 19Feb96  	regs.w.ax=0x0013;
//DeadCode JIM 19Feb96 	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03C4,0x0604);
//DeadCode JIM 19Feb96 	ASM_OutDxAl(0x03C2,0xE3);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03d4,0x0E11);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03d4,0x0D06);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03d4,0x3E07);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03d4,0xEA10);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03d4,0xAE11);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03d4,0xDF12);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03D4,0x0014);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03d4,0xE715);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03d4,0x0616);
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03D4,0xE317);
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 }
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 extern	"C"	void		ASM_CopyMainRAM2VidRAM(LogicalPtr, char *);
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 void	Display::ScreenFlip_CUSTOM_1c()
//DeadCode JIM 19Feb96 {
//DeadCode JIM 19Feb96 	ScreenNumOnLogical^=1;
//DeadCode JIM 19Feb96 	ASM_CopyMainRAM2VidRAM(logicalscreenptr,(char *)(0xA0000+(ScreenNumOnLogical<<15)));
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03d4,(UWord)(0x0C+(ScreenNumOnLogical<<15)));
//DeadCode JIM 19Feb96 	ASM_OutDxAx(0x03D4,0x0D);
//DeadCode JIM 19Feb96 }
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 
//DeadCode JIM 19Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 19Feb96 //Procedure		PalChange
//DeadCode JIM 19Feb96 //Author		Jim Taylor
//DeadCode JIM 19Feb96 //Date			Wed 13 Dec 1995
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Description	
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Inputs		
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //Returns	
//DeadCode JIM 19Feb96 //
//DeadCode JIM 19Feb96 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb96 	void	Display::PalChange()	//short UseNewPal=FALSE);
//DeadCode JIM 19Feb96 {
//DeadCode JIM 19Feb96  	if(UseNewPal == TRUE)
//DeadCode JIM 19Feb96  	{
//DeadCode JIM 19Feb96  		ASM_WaitVBL();
//DeadCode JIM 19Feb96  		ASM_SetPalette((char *)Palette);
//DeadCode JIM 19Feb96  	}
//DeadCode JIM 19Feb96 	UseNewPal=FALSE;
//DeadCode JIM 19Feb96 }
//DeadCode JIM 19Feb96 

//DeadCode DAW 26Feb96 //LastModified:	PD 13Feb96
//DeadCode DAW 26Feb96 //Author		Jim Taylor
//DeadCode DAW 26Feb96 //Date			Tue 12 Dec 1995
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //Description	Flip the displayed screen by copying
//DeadCode DAW 26Feb96 //				1) Calculate the base page and offset for the new screen
//DeadCode DAW 26Feb96 //				2) Copy the data a page at a time
//DeadCode DAW 26Feb96 //				3) hardware flip if avaialble
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //Inputs		
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //Returns	
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 void	Display::ScreenFlip_VESAc()
//DeadCode DAW 26Feb96 {
//DeadCode DAW 26Feb96 	DPMIregs	regs;
//DeadCode DAW 26Feb96 int	skipbytes,Lines,Columns,page;
//DeadCode DAW 26Feb96 	if (++VESA.ScreenNum>=VESA.Screens)
//DeadCode DAW 26Feb96 		VESA.ScreenNum=0;
//DeadCode DAW 26Feb96 int	physicaloffset=VESA.ScreenNum*VESA.BytesPerScanLine*VESA.ScanLines;
//DeadCode DAW 26Feb96 	page=
//DeadCode DAW 26Feb96 		VESA.pagetop=physicaloffset/VESA.PageShift;
//DeadCode DAW 26Feb96 	VESA.pageoff=physicaloffset%VESA.PageShift;
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 	if (VESA.BytesPerScanLine==BytesPerScanLine)
//DeadCode DAW 26Feb96 	{
//DeadCode DAW 26Feb96 		skipbytes=0;
//DeadCode DAW 26Feb96 		Lines=1;
//DeadCode DAW 26Feb96 		Columns=BytesPerScanLine*PhysicalHeight;
//DeadCode DAW 26Feb96 	}
//DeadCode DAW 26Feb96 	else
//DeadCode DAW 26Feb96 	{
//DeadCode DAW 26Feb96 		skipbytes=VESA.BytesPerScanLine-BytesPerScanLine;
//DeadCode DAW 26Feb96 		Lines=PhysicalHeight;
//DeadCode DAW 26Feb96 		Columns=BytesPerScanLine;
//DeadCode DAW 26Feb96 	}
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 	LogicalPtr	src=logicalscreenptr;
//DeadCode DAW 26Feb96 	char*		trg=(char*)VESA.writeaddr;
//DeadCode DAW 26Feb96 	int			off=VESA.pageoff;
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 	//set to page
//DeadCode DAW 26Feb96 	regs.w.ax=0x4f05;
//DeadCode DAW 26Feb96 	regs.w.bx=VESA.writewin;
//DeadCode DAW 26Feb96 	regs.w.dx=page;
//DeadCode DAW 26Feb96 	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 	while (Lines--)
//DeadCode DAW 26Feb96 	{
//DeadCode DAW 26Feb96 int		colleft=Columns;
//DeadCode DAW 26Feb96 		while (off+colleft>VESA.PageSize)
//DeadCode DAW 26Feb96 		{
//DeadCode DAW 26Feb96 int			tmpleft=VESA.PageSize-off;
//DeadCode DAW 26Feb96 			colleft=colleft-tmpleft;
//DeadCode DAW 26Feb96 			tmpleft=tmpleft>>2;
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 extern	void ASM_Cp(ULong *dst,LogicalPtr src,SLong len);		//PD 13Feb96
//DeadCode DAW 26Feb96 #pragma aux	ASM_Cp = 		\
//DeadCode DAW 26Feb96 			"rep movsd"		\
//DeadCode DAW 26Feb96 			"mov src,esi"	\
//DeadCode DAW 26Feb96 			parm [edi] [esi] [ecx]								//PD 13Feb96
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 			ASM_Cp((ULong*)(trg+off),(LogicalPtr )src,tmpleft);
//DeadCode DAW 26Feb96 			off=0;
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 			//set to next page
//DeadCode DAW 26Feb96 			page+=VESA.PageShift;
//DeadCode DAW 26Feb96 			regs.w.ax=0x4f05;
//DeadCode DAW 26Feb96 			regs.w.bx=VESA.writewin;
//DeadCode DAW 26Feb96 			regs.w.dx=page;
//DeadCode DAW 26Feb96 			ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 		}
//DeadCode DAW 26Feb96 		colleft=colleft>>2;
//DeadCode DAW 26Feb96 		ASM_Cp((ULong*)(trg+off),(LogicalPtr )src,colleft);
//DeadCode DAW 26Feb96 //TempCode PD 13Feb96 		while (colleft--)
//DeadCode DAW 26Feb96 //TempCode PD 13Feb96 		{
//DeadCode DAW 26Feb96 //TempCode PD 13Feb96 			*((ULong*) (trg+off))=*((LogicalLPtr) src);
//DeadCode DAW 26Feb96 //TempCode PD 13Feb96 			src+=4;
//DeadCode DAW 26Feb96 //TempCode PD 13Feb96 			off+=4;
//DeadCode DAW 26Feb96 //TempCode PD 13Feb96 		}
//DeadCode DAW 26Feb96 		off+=skipbytes;
//DeadCode DAW 26Feb96 	}
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 }
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 26Feb96 //Procedure		SetGraphicsMode_CUSTOM_1d
//DeadCode DAW 26Feb96 //Author		Jim Taylor
//DeadCode DAW 26Feb96 //Date			Thu 14 Dec 1995
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //Description	Debugable 320x200
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //Inputs		
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //Returns	
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 void	Display::SetGraphicsMode_CUSTOM_1d()
//DeadCode DAW 26Feb96 {
//DeadCode DAW 26Feb96 	DPMIregs	regs;
//DeadCode DAW 26Feb96  	regs.w.ax=0x0013;
//DeadCode DAW 26Feb96 	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode DAW 26Feb96 	logicalscreenptr=(LogicalPtr) ((void*) 0xA0000);
//DeadCode DAW 26Feb96 }
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 void	Display::ScreenFlip_CUSTOM_1d()
//DeadCode DAW 26Feb96 {;
//DeadCode DAW 26Feb96 }
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 void	Display::SetGraphicsMode_CUSTOM_1c()
//DeadCode DAW 26Feb96 {
//DeadCode DAW 26Feb96 	DPMIregs	regs;
//DeadCode DAW 26Feb96  	regs.w.ax=0x0013;
//DeadCode DAW 26Feb96 	ASM_DOSvia31(0x10,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03C4,0x0604);
//DeadCode DAW 26Feb96 	ASM_OutDxAl(0x03C2,0xE3);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03d4,0x0E11);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03d4,0x0D06);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03d4,0x3E07);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03d4,0xEA10);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03d4,0xAE11);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03d4,0xDF12);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03D4,0x0014);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03d4,0xE715);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03d4,0x0616);
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03D4,0xE317);
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 }
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 extern	"C"	void		ASM_CopyMainRAM2VidRAM(LogicalPtr, char *);
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 void	Display::ScreenFlip_CUSTOM_1c()
//DeadCode DAW 26Feb96 {
//DeadCode DAW 26Feb96 	ScreenNumOnLogical^=1;
//DeadCode DAW 26Feb96 	ASM_CopyMainRAM2VidRAM(logicalscreenptr,(char *)(0xA0000+(ScreenNumOnLogical<<15)));
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03d4,(UWord)(0x0C+(ScreenNumOnLogical<<15)));
//DeadCode DAW 26Feb96 	ASM_OutDxAx(0x03D4,0x0D);
//DeadCode DAW 26Feb96 }
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 
//DeadCode DAW 26Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 26Feb96 //Procedure		PalChange
//DeadCode DAW 26Feb96 //Author		Jim Taylor
//DeadCode DAW 26Feb96 //Date			Wed 13 Dec 1995
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //Description	
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //Inputs		
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //Returns	
//DeadCode DAW 26Feb96 //
//DeadCode DAW 26Feb96 //------------------------------------------------------------------------------
//DeadCode DAW 26Feb96 	void	Display::PalChange()	//short UseNewPal=FALSE);
//DeadCode DAW 26Feb96 {
//DeadCode DAW 26Feb96  	if(UseNewPal == TRUE)
//DeadCode DAW 26Feb96  	{
//DeadCode DAW 26Feb96  		ASM_WaitVBL();
//DeadCode DAW 26Feb96  		ASM_SetPalette((char *)Palette);
//DeadCode DAW 26Feb96  	}
//DeadCode DAW 26Feb96 	UseNewPal=FALSE;
//DeadCode DAW 26Feb96 }

