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
//Filename       wrapper.cpp
//System         
//Author         Paul.   
//Date           Mon 3 Jul 1995
//Description    Wrapper.CPP provides a wrapper layer around the hardware 
//			   primitives and graphics primitives libraries. This file 
//			   provides the routines we are familiar with and translation 
//			   from virtual resolution and 256 colours as well as providing 
//			   memory blocks on request from the lower level.
//------------------------------------------------------------------------------
#include	<StdLIb.H>

#include	"DOSDefs.H"
#include	"stub3d.h"
#include 	"myerror.h"
#include	"Palette.H"
#include	"Fonts.H"
#include	"FileMan.h"
#include	"display.h"
//#include	"HardPrim.H"
//#include	"Wrapper.H"
#include	"myAngles.h"
#include	"Worldinc.h"
#include	"World.h"
//#include	"Main.H"
#include	"ImageMap.h"										//PD 30Oct95
#include	"HardPasm.h"
#include	"savegame.h"										//DAW 18Aug97

#include	"KeyTest.h"
#include	"TextRef.h"
#include	"mouse.h"
#include	"Mytime.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Graphic
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
CON		Graphic::Graphic(Bool& unp,IntensityIndex*	ii,void*&p,FontPtr& fp,FontPtr& mp):
	UseNewPal(unp),
	intensityindex(*ii),
	Palette(p),
	fontptr(fp),
	mousefontptr(mp)
{
};

void	Display::WindowMoved(LogicalPtr	oldplace,LogicalPtr newplace)
{
	FILE* fp;
Graphic*	window=windowlink;
if (oldplace!=newplace)

	while (window)
	{	//being longwinded here to ensure legality!
		window->logicalscreenptr=newplace+(window->logicalscreenptr-oldplace);
		window->BytesPerScanLine = BytesPerScanLine;
		window=window->windowlink;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Window
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
CON	Window::Window(Bool& unp,IntensityIndex*	ii,void*&p,FontPtr& fp,FontPtr& mp):
		Graphic(unp,ii,p,fp,mp)
{
	master=this;
	windowlink=NULL;
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Window
//Author		Jim Taylor
//Date			Wed 13 Dec 1995
//
//Description	Generate a clipping zone on the current display
//
//				Reposition the physical coords based on the logical coords movements
//				Regenerate the scale factors based on scale
//				Regenerate the logical coords using physical and scale
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON	Window::Window(const Window& src,const InitWindowDef& pos,SWord scale,Bool nofitfatal):
		Graphic(src.UseNewPal,&src.intensityindex,src.Palette,src.fontptr,src.mousefontptr)
{	//Window on existing screen
	master=src.master;
	windowlink=master->windowlink;
	master->windowlink=this;

	iffartnum		=src.iffartnum;
	ifflinenum		=src.ifflinenum;
	iffoffset		=src.iffoffset;
	logicalscreenptr=src.logicalscreenptr;
	BytesPerPixel	=src.BytesPerPixel;

	RedBits			=src.RedBits;								//PD 17Oct97
	GreenBits		=src.GreenBits;								//PD 17Oct97
	BlueBits 		=src.BlueBits;								//PD 17Oct97
	RedShift		=src.RedShift;								//PD 17Oct97
	GreenShift		=src.GreenShift;							//PD 17Oct97
	BlueShift 		=src.BlueShift;								//PD 17Oct97

	BytesPerScanLine=src.BytesPerScanLine;
	glasscolour		=src.glasscolour;
	colour			=src.colour;
	range			=src.range;
	fontptr			=src.fontptr;
	CharX			=src.CharX;
	CharY			=src.CharY;
	imageptr		=src.imageptr;
	shadetable		=src.shadetable;
	NumberOfScreens	=src.NumberOfScreens;
//TempCode DAW 08Feb96 	horiline		=src.horiline;


	PhysicalWidth=(pos.VirtualWidth)/src.virtualXscale;
	PhysicalHeight=(pos.VirtualHeight)/src.virtualYscale;
	PhysicalMinX=pos.VirtualMinX/src.virtualXscale;
	PhysicalMinY=pos.VirtualMinY/src.virtualYscale;
	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1;
	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1;
	if (	(PhysicalMinX<src.PhysicalMinX)
		||	(PhysicalMinY<src.PhysicalMinY)
		||	((PhysicalMinX+PhysicalWidth)>(src.PhysicalMinX+src.PhysicalWidth))
		||	((PhysicalMinY+PhysicalHeight)>(src.PhysicalMinY+src.PhysicalHeight))
		)
	{
		if (PhysicalMinX<src.PhysicalMinX)
		{
			PhysicalWidth-=src.PhysicalMinX-PhysicalMinX;
			PhysicalMinX=src.PhysicalMinX;
		}
		if (PhysicalMinY<src.PhysicalMinY)
		{
			PhysicalHeight-=src.PhysicalMinY-PhysicalMinY;
			PhysicalMinY=src.PhysicalMinY;
		}
		if ((PhysicalMinX+PhysicalWidth)>(src.PhysicalMinX+src.PhysicalWidth))
			PhysicalWidth=(src.PhysicalMinX+src.PhysicalWidth)-PhysicalMinX;
		if ((PhysicalMinY+PhysicalHeight)>(src.PhysicalMinY+src.PhysicalHeight))
			PhysicalHeight=(src.PhysicalMinY+src.PhysicalHeight)-PhysicalMinY;

		if (nofitfatal)
			_Error.EmitSysErr("Window is outside source screen area");
	}
	virtualXscale=src.virtualXscale*scale;
	virtualYscale=src.virtualYscale*scale;

	VirtualWidth	=PhysicalWidth		*virtualXscale;
	VirtualHeight	=PhysicalHeight		*virtualYscale;
	VirtualMinX		=PhysicalMinX		*virtualXscale;
	VirtualMinY		=PhysicalMinY		*virtualYscale;
};

//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		Window
//FIX10-2//Author		Jim Taylor
//FIX10-2//Date			Mon 2 Sep 1996
//FIX10-2//
//FIX10-2//Description	Shift origin of window by pixels
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2CON	Window::Window(const Window& src,const ScreenXY& delta,SWord scale):
//FIX10-2		Graphic(src.UseNewPal,&src.intensityindex,src.Palette,src.fontptr,src.mousefontptr)
//FIX10-2{	//Window on existing screen
//FIX10-2	master=src.master//FIX10-2
//FIX10-2	windowlink=master->windowlink//FIX10-2
//FIX10-2	master->windowlink=this//FIX10-2
//FIX10-2
//FIX10-2	iffartnum		=src.iffartnum//FIX10-2
//FIX10-2	ifflinenum		=src.ifflinenum//FIX10-2
//FIX10-2	iffoffset		=src.iffoffset//FIX10-2
//FIX10-2	logicalscreenptr=src.logicalscreenptr//FIX10-2
//FIX10-2	BytesPerPixel	=src.BytesPerPixel//FIX10-2
//FIX10-2
//FIX10-2	RedBits			=src.RedBits//FIX10-2								//PD 17Oct97
//FIX10-2	GreenBits		=src.GreenBits//FIX10-2								//PD 17Oct97
//FIX10-2	BlueBits 		=src.BlueBits//FIX10-2								//PD 17Oct97
//FIX10-2	RedShift		=src.RedShift//FIX10-2								//PD 17Oct97
//FIX10-2	GreenShift		=src.GreenShift//FIX10-2							//PD 17Oct97
//FIX10-2	BlueShift 		=src.BlueShift//FIX10-2								//PD 17Oct97
//FIX10-2
//FIX10-2	BytesPerScanLine=src.BytesPerScanLine//FIX10-2
//FIX10-2	glasscolour		=src.glasscolour//FIX10-2
//FIX10-2	colour			=src.colour//FIX10-2
//FIX10-2	range			=src.range//FIX10-2
//FIX10-2	fontptr			=src.fontptr//FIX10-2
//FIX10-2	CharX			=src.CharX//FIX10-2
//FIX10-2	CharY			=src.CharY//FIX10-2
//FIX10-2	imageptr		=src.imageptr//FIX10-2
//FIX10-2	shadetable		=src.shadetable//FIX10-2
//FIX10-2	NumberOfScreens	=src.NumberOfScreens//FIX10-2
//FIX10-2//TempCode DAW 08Feb96 	horiline		=src.horiline//FIX10-2
//FIX10-2
//FIX10-2
//FIX10-2
//FIX10-2
//FIX10-2	PhysicalWidth	=src.PhysicalWidth//FIX10-2
//FIX10-2	PhysicalHeight	=src.PhysicalHeight//FIX10-2
//FIX10-2	PhysicalMinX	=src.PhysicalMinX//FIX10-2
//FIX10-2	PhysicalMinY	=src.PhysicalMinY//FIX10-2
//FIX10-2	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1//FIX10-2
//FIX10-2	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1//FIX10-2
//FIX10-2	virtualXscale	=src.virtualXscale//FIX10-2
//FIX10-2	virtualYscale	=src.virtualYscale//FIX10-2
//FIX10-2
//FIX10-2	int	dx=delta.x/virtualXscale//FIX10-2
//FIX10-2	int	dy=delta.y/virtualYscale//FIX10-2
//FIX10-2	PhysicalMinX+=dx//FIX10-2
//FIX10-2	PhysicalMinY+=dy//FIX10-2
//FIX10-2	logicalscreenptr-=dy*BytesPerScanLine+dx*BytesPerPixel//FIX10-2
//FIX10-2
//FIX10-2	virtualXscale*=scale//FIX10-2
//FIX10-2	virtualYscale*=scale//FIX10-2
//FIX10-2
//FIX10-2	VirtualWidth	=PhysicalWidth		*virtualXscale//FIX10-2
//FIX10-2	VirtualHeight	=PhysicalHeight		*virtualYscale//FIX10-2
//FIX10-2	VirtualMinX		=PhysicalMinX		*virtualXscale//FIX10-2
//FIX10-2	VirtualMinY		=PhysicalMinY		*virtualYscale//FIX10-2
//FIX10-2	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1//FIX10-2
//FIX10-2	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1//FIX10-2
//FIX10-2
//FIX10-2}//FIX10-2

CON	Window::Window(const Window& src,const int deltax,const int deltay,SWord scale):
		Graphic(src.UseNewPal,&src.intensityindex,src.Palette,src.fontptr,src.mousefontptr)
{	//Window on existing screen
	master=src.master;
	windowlink=master->windowlink;
	master->windowlink=this;

	iffartnum		=src.iffartnum;
	ifflinenum		=src.ifflinenum;
	iffoffset		=src.iffoffset;
	logicalscreenptr=src.logicalscreenptr;
	BytesPerPixel	=src.BytesPerPixel;

	RedBits			=src.RedBits;								//PD 17Oct97
	GreenBits		=src.GreenBits;								//PD 17Oct97
	BlueBits 		=src.BlueBits;								//PD 17Oct97
	RedShift		=src.RedShift;								//PD 17Oct97
	GreenShift		=src.GreenShift;							//PD 17Oct97
	BlueShift 		=src.BlueShift;								//PD 17Oct97

	BytesPerScanLine=src.BytesPerScanLine;
	glasscolour		=src.glasscolour;
	colour			=src.colour;
	range			=src.range;
	fontptr			=src.fontptr;
	CharX			=src.CharX;
	CharY			=src.CharY;
	imageptr		=src.imageptr;
	shadetable		=src.shadetable;
	NumberOfScreens	=src.NumberOfScreens;
//TempCode DAW 08Feb96 	horiline		=src.horiline;




	PhysicalWidth	=src.PhysicalWidth;
	PhysicalHeight	=src.PhysicalHeight;
	PhysicalMinX	=src.PhysicalMinX;
	PhysicalMinY	=src.PhysicalMinY;
	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1;
	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1;
	virtualXscale	=src.virtualXscale;
	virtualYscale	=src.virtualYscale;

	int	dx=deltax/virtualXscale;
	int	dy=deltay/virtualYscale;
	PhysicalMinX+=dx;
	PhysicalMinY+=dy;
	logicalscreenptr-=dy*BytesPerScanLine+dx*BytesPerPixel;

	virtualXscale*=scale;
	virtualYscale*=scale;

	VirtualWidth	=PhysicalWidth		*virtualXscale;
	VirtualHeight	=PhysicalHeight		*virtualYscale;
	VirtualMinX		=PhysicalMinX		*virtualXscale;
	VirtualMinY		=PhysicalMinY		*virtualYscale;
	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1;
	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1;

};
	
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Window
//Author		Jim Taylor
//Date			Tue 19 Dec 1995
//
//Description	Create a virtual screen on the current window
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON	Window::Window(const Window& src,WinShiftDef X,WinShiftDef Y,SWord scale):
		Graphic(src.UseNewPal,&src.intensityindex,src.Palette,src.fontptr,src.mousefontptr)
{
	master=src.master;
	windowlink=master->windowlink;
	master->windowlink=this;

	iffartnum		=src.iffartnum;
	ifflinenum		=src.ifflinenum;
	iffoffset		=src.iffoffset;
	BytesPerPixel	=src.BytesPerPixel;
	BytesPerScanLine=src.BytesPerScanLine;
	glasscolour		=src.glasscolour;
	colour			=src.colour;
	range			=src.range;
	CharX			=src.CharX;
	CharY			=src.CharY;
	imageptr		=src.imageptr;
	shadetable		=src.shadetable;
	NumberOfScreens	=src.NumberOfScreens;
//TempCode DAW 08Feb96 	horiline		=src.horiline;
	PhysicalWidth	=(src.PhysicalWidth);
	PhysicalHeight	=(src.PhysicalHeight);
	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1;
	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1;


	//Place screen origin on top LHS of window
	logicalscreenptr=	src.logicalscreenptr			
					 +	src.PhysicalMinX*BytesPerPixel
					 +	src.PhysicalMinY*BytesPerScanLine;

	//Now shift origin to requested place
	if (X==WINSH_MAX)
		PhysicalMinX=-PhysicalWidth;
	elseif (X==WINSH_MID)
		PhysicalMinX=-PhysicalWidth>>1;
	elseif (X==WINSH_MIN)
		PhysicalMinX=0;
	else
		PhysicalMinX=src.PhysicalMinX;


	if (Y==WINSH_MAX)
		PhysicalMinY=-PhysicalHeight;
	elseif (Y==WINSH_MID)
		PhysicalMinY=-PhysicalHeight>>1;
	elseif (Y==WINSH_MIN)
		PhysicalMinY=0;
	else
		PhysicalMinY=src.PhysicalMinY;
	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1;
	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1;

	//Place screen memory of window
	logicalscreenptr=	logicalscreenptr			
					 -	PhysicalMinX*BytesPerPixel
					 -	PhysicalMinY*BytesPerScanLine;

	virtualXscale=src.virtualXscale*scale;
	virtualYscale=src.virtualYscale*scale;

	VirtualWidth	=PhysicalWidth		*virtualXscale;
	VirtualHeight	=PhysicalHeight		*virtualYscale;
	VirtualMinX		=PhysicalMinX		*virtualXscale;
	VirtualMinY		=PhysicalMinY		*virtualYscale;
	

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Window
//Author		Paul.   
//Date			Fri 28 Jun 1996
//
//Description	Make an imagemap look like a window
//				so we can draw to it
//
//Inputs		ptr to imagemap desc	
//
//Returns	
//
//------------------------------------------------------------------------------
CON	Window::Window(const Window& src,ImageMap_Desc &image):
		Graphic(src.UseNewPal,&src.intensityindex,src.Palette,src.fontptr,src.mousefontptr)
{
	//Keep this to keep the destructor happy
	master=src.master;
	windowlink=master->windowlink;
	master->windowlink=this;

	PhysicalWidth = image.w;						//RJS 06Feb98
	PhysicalHeight= image.h;						//RJS 06Feb98

	logicalscreenptr=image.body;					//RJS 06Feb98
	iffartnum		=src.iffartnum;
	ifflinenum		=src.ifflinenum;
	iffoffset		=src.iffoffset;
	BytesPerPixel	=src.BytesPerPixel;
	BytesPerScanLine=PhysicalWidth;
	glasscolour		=src.glasscolour;
	colour			=src.colour;
	range			=src.range;
	fontptr			=src.fontptr;
	CharX			=src.CharX;
	CharY			=src.CharY;
	imageptr		=src.imageptr;
	shadetable		=src.shadetable;
	NumberOfScreens	=1;

	PhysicalMinX=0;
	PhysicalMinY=0;
	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1;
	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1;

	virtualXscale=src.virtualXscale;
	virtualYscale=src.virtualYscale;

	VirtualWidth	=PhysicalWidth		*virtualXscale;
	VirtualHeight	=PhysicalHeight		*virtualYscale;
	VirtualMinX		=PhysicalMinX		*virtualXscale;
	VirtualMinY		=PhysicalMinY		*virtualYscale;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Display
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
#pragma  warning(disable:4355)
CON	Display::Display(View3d* v):
		Window(this->UseNewPal,&this->intensityindex,Palette,fontptr,mousefontptr)
#pragma  warning(default:4355)
		{
			view3dwin=v;
			prevmodeAX=prevmodeBX=0;
			Palette=NULL;
			Graphic::shadetable=shadetable;
			logicalscreenptr=NULL;
			fontptr=NULL;
			mousefontptr = NULL;
			mouseimagenumber = 1;
			iffartnum=-1;
			currsmk=0;
			FillExpandBuff();
		};


DES	Display::~Display()
{

	ExitDirectDraw ();
	delete	Palette;
	Palette=NULL;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Window
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
DES	Window::~Window()
{
Graphic*	chase=master;
	if (chase!=this)
		while (chase->windowlink!=this)
			chase=chase->windowlink;
//Old_Code DAW 01Feb96 	else
//Old_Code DAW 01Feb96 		assert((windowlink==NULL)&&("Display closed, but not all windows"));
	chase->windowlink=windowlink;
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::Init
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
short	Display::Init(WinMode::Mode v,int L,int T,int R,int B)
{
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[2]='a';
	InitDisplayDef	mode={640,480,8,0};
	if 		(FindModeWin(mode))				// Returns TRUE
		LoadGraphicsLib(SelectLibWin());	// SelectLibWin() returns INVALIDFILENUM
//	elseif	(FindModeVESA(mode))
//		LoadGraphicsLib(SelectLibVESA());
//	elseif	(FindModeDirty(mode))
//		LoadGraphicsLib(SelectLibDirty());
	else
		_Error.EmitSysErr("Couldn't find match for mode!!!");

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[2]='b';
	SetGraphicsMode();
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[2]='c';

//DEAD	if(logicalscreenptr == NULL)
//DEAD		if((logicalscreenptr = (LogicalPtr) new char[PhysicalWidth * PhysicalHeight+1000])==NULL)//JIM 28Mar96
//DEAD			return(FALSE);
	PhysicalMaxX=PhysicalMinX+PhysicalWidth-1;
	PhysicalMaxY=PhysicalMinY+PhysicalHeight-1;

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::GetFontInfo
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
void Window::GetFontInfo(short& width, short& delta,short& height)
{

	//Get info on the space character

	delta = (short)	((-fontptr->charentries[0].YShift)*virtualYscale);

	//t3 is a pointer to the fonts SIZETABLE & space is the first character

	width = (short)	(fontptr->charentries[0].NextXShift*virtualXscale);//RDH 20Dec95
	height = (short) (fontptr->charentries[0].Height*virtualYscale);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::GetCharacterWidth
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Mon 3 Jul 1995
//Modified	
//
//Description	Called by justification routines to estimate character positions
//
//Inputs	
//
//Returns	The NextXShift - Width is an internal thing...
//			Of course, really clever justification would use width for the last char
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
short Window::GetCharacterWidth(short character)
{
	return(SWord)(fontptr->charentries[character-32].NextXShift*virtualXscale);
}

//------------------------------------------------------------------------------
void	FixupFontHeader(void*	&fontdata,ULong&)
{	//fixup offsets into pointers:

	Font*
	f=(Font*)	fontdata;
CharTableEntryPtr
	c=(f->charentries);
int	i;
int j = f->maxchar;
	for (i=0;i<j;i++)
		c[i].pixeldata =(void*)((ULong) c[i].pixeldata + (ULong) &c[j]);
  }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::RegisterFontActive
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Mon 3 Jul 1995
//Modified	
//
//Description	Sets up current font to be used
//
//Inputs		ScreenRecord, font filenumber
//
//Returns	width = width of space
//			delta = delta to top of space
//			height = height of space
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//short Window::RegisterFontActive
//				(FileNum filenumber,short& width, short& delta, short& height)
//{
//static	fileblockptr	loadedhandle=NULL;
//
//	//Dispose old font if any
//
//	if(fontptr != NULL)	delete(loadedhandle);
//
//	//Load new font data
//
//	loadedhandle=new fileblock(filenumber,FixupFontHeader);
//
//	fontptr=(FontPtr)getdata(*loadedhandle);
//
////TempCode JIM 03Oct95 	if((screen->FontPtr = _DiskIO.LoadNumberedFile(filenumber))==NULL)
////TempCode JIM 03Oct95 		_Error.EmitSysErr(__FILE__":Failed to set new font\n");
//
//	//Get info on the space character
//
//	GetFontInfo(width,delta,height);
//
//	return(TRUE);
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPixelWidth
//Author		Paul.   
//Date			Wed 3 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::SetPixelWidth(SWord &pixwid)
{
	Graphic::SetPixelWidth(pixwid);
}
void* Window::GetPaletteTable()
{
	return Graphic::GetPaletteTable();
}

void* Window::GetLandFadeTable()
{
	return Graphic::GetLandFadeTable();
}

void* Window::GetSkyFadeTable()
{
	return Graphic::GetSkyFadeTable();
}

void* Window::GetHorizonFadeTable()
{
	return Graphic::GetHorizonFadeTable();
}

void Window::SelectPalette(SWord palNum)
{
	Graphic::SelectPalette(palNum);
}

UWord Window::GetPaletteEntry(UWord c)
{
	return Graphic::GetPaletteEntry(c);
}

void Window::SetPaletteEntry(UWord c,UWord v)
{
	Graphic::SetPaletteEntry(c,v);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTransparency
//Author		Paul.   
//Date			Tue 2 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::SetTransparency(SWord flag)
{
	Graphic::SetTransparency(flag);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLuminosity
//Author		Robert Slater
//Date			Mon 19 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::SetLuminosity(SWord flag)
{
	Graphic::SetLuminosity(flag);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetHeatHaze
//Author		Robert Slater
//Date			Fri 30 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::SetHeatHaze(SWord flag)
{
	Graphic::SetHeatHaze(flag);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::SetColour
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
void Window::SetColour(Colour colour)							//PD 29Nov95
{
	Graphic::SetColour(colour);								//PD 29Nov95
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::SetColour
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
void Window::SetColour(Colour colour, ColourRange range)		//PD 29Nov95
{
		Graphic::SetColour(colour,range);						//PD 29Nov95
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGlassRange
//Author		Paul.   
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::SetGlassRange(Colour colour)
{
 	Graphic::SetGlassRange(colour);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::SetColour
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
void Window::SetColour(ImageMapNumber imap)					//PD 29Nov95
{
	//Convert image number to a pointer to the image map data

	ImageMapDescPtr	imageptr;

	imageptr = Image_Map.GetImageMapPtr(imap);					//PD 29Nov95

	Graphic::SetColour(imageptr);								//PD 29Nov95
}

void Window::SetColour(ROWANSURFACEDESC* rsd)
{
	Graphic::SetColour(rsd);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetColour
//Author		Paul.   
//Date			Fri 3 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::SetColour(ImageMapDescPtr imapptr)
{
	Graphic::SetColour(imapptr);
}

//TempCode JIM 12Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode JIM 12Dec95 //Procedure	Window::CloneWindow
//TempCode JIM 12Dec95 //------------------------------------------------------------------------------
//TempCode JIM 12Dec95 //Author		Paul.   
//TempCode JIM 12Dec95 //Date		Mon 3 Jul 1995
//TempCode JIM 12Dec95 //Modified	
//TempCode JIM 12Dec95 //
//TempCode JIM 12Dec95 //Description	
//TempCode JIM 12Dec95 //
//TempCode JIM 12Dec95 //Inputs	
//TempCode JIM 12Dec95 //
//TempCode JIM 12Dec95 //Returns	
//TempCode JIM 12Dec95 //
//TempCode JIM 12Dec95 //Externals
//TempCode JIM 12Dec95 //------------------------------------------------------------------------------
//TempCode JIM 12Dec95 //------------------------------------------------------------------------------
//TempCode JIM 12Dec95 ScreenRecord *Window::CloneWindow(ScreenRecord *screen)
//TempCode JIM 12Dec95 {
//TempCode JIM 12Dec95 	int	i;
//TempCode JIM 12Dec95 
//TempCode JIM 12Dec95 	char	*src,
//TempCode JIM 12Dec95 		*dest;
//TempCode JIM 12Dec95 
//TempCode JIM 12Dec95 	ScreenRecord	*newscreen;
//TempCode JIM 12Dec95 
//TempCode JIM 12Dec95 	if((newscreen = new ScreenRecord)==0)
//TempCode JIM 12Dec95 	{
//TempCode JIM 12Dec95 		return(NULL);
//TempCode JIM 12Dec95 	}
//TempCode JIM 12Dec95 
//TempCode JIM 12Dec95 	src = (char *)screen;
//TempCode JIM 12Dec95 	dest = (char *)newscreen;
//TempCode JIM 12Dec95 
//TempCode JIM 12Dec95 	for(i=sizeof(ScreenRecord);i;--i,*src++ = *dest++);
//TempCode JIM 12Dec95 
//TempCode JIM 12Dec95 	return(newscreen);
//TempCode JIM 12Dec95 }

//TempCode JIM 12Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode JIM 12Dec95 //Procedure	DestroyWindow
//TempCode JIM 12Dec95 //------------------------------------------------------------------------------
//TempCode JIM 12Dec95 //Author		Paul.   
//TempCode JIM 12Dec95 //Date		Mon 14 Aug 1995
//TempCode JIM 12Dec95 //Modified	
//TempCode JIM 12Dec95 //
//TempCode JIM 12Dec95 //Description	DEADED MOST OF THIS 'COS THEY ARE one-off SCREEN structures 
//TempCode JIM 12Dec95 //				rather than WINDOW structures.
//TempCode JIM 12Dec95 //				I am coming to the conclusion that we will need a hardware class 
//TempCode JIM 12Dec95 //				arround the window class, where the card-specific vars for the
//TempCode JIM 12Dec95 //				graphics driver go. 
//TempCode JIM 12Dec95 //				This will need deleting, and these bits 'o memory can be freed there.
//TempCode JIM 12Dec95 //
//TempCode JIM 12Dec95 //Inputs	
//TempCode JIM 12Dec95 //
//TempCode JIM 12Dec95 //Returns	
//TempCode JIM 12Dec95 //
//TempCode JIM 12Dec95 //Externals
//TempCode JIM 12Dec95 //------------------------------------------------------------------------------
//TempCode JIM 12Dec95 //------------------------------------------------------------------------------
//TempCode JIM 12Dec95 void Window::DestroyWindow(ScreenRecord *screen)
//TempCode JIM 12Dec95 {
//TempCode JIM 12Dec95 //DeadCode JIM 09Nov95 	if(screen->LogicalScreenPtr!=NULL)	free(screen->LogicalScreenPtr);	//NOOO!! What if proper pseudo-screening using flat hardware?
//TempCode JIM 12Dec95 //DeadCode JIM 09Nov95 	if(screen->Palette!=NULL) free(screen->Palette);	//NOOOOOOO!! Windows share pallettes
//TempCode JIM 12Dec95 //DeadCode JIM 09Nov95 	if(screen->fontptr!=NULL) free(screen->FontPtr);	//NOOOOOOO!! Windows share fonts
//TempCode JIM 12Dec95 	screen->LogicalScreenPtr = screen->Palette = screen->fontptr = NULL;
//TempCode JIM 12Dec95 	delete(screen);
//TempCode JIM 12Dec95 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::MouseRedraw
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
void Display::MouseRedraw()
{

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::GetCharPos
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
void Window::GetCharPos(short& cursorx, short& cursory)
{
	cursorx = (short) (CharX*virtualXscale);
	cursory = (short) (CharY*virtualYscale);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
SWord Window::GetCharPos()					//JIM 09Nov95
{																//JIM 09Nov95
	return((short)(CharX*virtualXscale));		//JIM 10Nov95
}																//JIM 09Nov95

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::SetCharPos
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
void Window::SetCharPos(short cursorx, short cursory)
{
	CharX = (short)(cursorx/virtualXscale);
	CharY = (short)(cursory/virtualYscale);
}
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		SetMouseSaveInfo
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Wed 13 Mar 1996
//FIX10-2//
//FIX10-2//Description	Sets up width, height, x and y information in the mouse save
//FIX10-2//
//FIX10-2//Inputs		The mouse save index
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2void	Display::SetMouseSaveInfo(short	savenum, short	imagenum, SWord	newx, SWord	newy)
//FIX10-2{
//FIX10-2	mousesave[savenum].Info->WH.w = mousefontptr->charentries[imagenum].Width;
//FIX10-2	mousesave[savenum].Info->WH.h = mousefontptr->charentries[imagenum].Height;
//FIX10-2
//FIX10-2	// Update the x and y mouse fields if we have new ones...
//FIX10-2
//FIX10-2	mousesave[savenum].Info->XY.x = newx;
//FIX10-2	mousesave[savenum].Info->XY.y = newy;
//FIX10-2
//FIX10-2	mousesave[savenum].Info->XY.x /= virtualXscale;
//FIX10-2	mousesave[savenum].Info->XY.y /= virtualYscale;
//FIX10-2
//FIX10-2	mousesave[savenum].Info->XY.x -= mousefontptr->charentries[imagenum].NextXShift;
//FIX10-2	mousesave[savenum].Info->XY.y += mousefontptr->charentries[imagenum].YShift;
//FIX10-2	
//FIX10-2}
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		MousePixelData
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Wed 13 Mar 1996
//FIX10-2//
//FIX10-2//Description	Returns the pointer to the mouse image pixel data
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns														 
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2UByte*	Display::MousePixelData(short	imagenum)
//FIX10-2{
//FIX10-2	UByte	*pixdata, *pixdata2;
//FIX10-2
//FIX10-2	pixdata = (UByte*) mousefontptr->charentries[imagenum].pixeldata;
//FIX10-2
//FIX10-2	pixdata2 = (UByte*) mousefontptr->charentries[imagenum+1].pixeldata;
//FIX10-2	
//FIX10-2	if (pixdata2 > pixdata)
//FIX10-2	{
//FIX10-2		if ((pixdata2 - pixdata) > mousesave[0].datasize)
//FIX10-2			_Error.EmitSysErr("Mouse character too big for buffer!");
//FIX10-2	}
//FIX10-2
//FIX10-2 	return(pixdata);
//FIX10-2}
//FIX10-2
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::ScreenSwap
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Mon 3 Jul 1995
//Modified	
//
//Description	The many ways to swap the screen and hide the mouse redraw
//				Also incoorporates the 2cs delay
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	Display::ScreenSwap()
{
//ScreenXY	tmpxy, &mpos=Key_Tests.mousepos();
//MouseSave*	thru;
UByte		*mouseimage;

	LogicalPtr	oldscr=logicalscreenptr;

//	mouseimage = MousePixelData(mouseimagenumber);
//	tmpxy=Key_Tests.mousepos();
	if (NumberOfScreens==0)	//debug physical - need better test...
	{
//		SetMouseSaveInfo(0,mouseimagenumber,tmpxy.x,tmpxy.y);
//		LogMouseDrawSave(mouseimage,mousesave[0].Info);
	}

	ULong	counter = 1000000;
//TEMP
//	while	(Timer_Code.TestLoopTime()<2)	//WAIT FOR FRAMEMIN
//	{	//this is only time you see mouse on single screener
//		//put a smacker call here as well!
  //
	//	if (--counter==0)
	//		_Error.EmitSysErr("Timer interrupts have died!");
	  //
		//if (currsmk)
		//	SmackLoad(currsmk);
//  	//	_Mouse.Move();
	//}
//Old_Code PD 18Nov97 	while	(Timer_Code.TestLoopTime()<Timer_Code.FRAMEMIN)	//WAIT FOR FRAMEMIN
//Old_Code PD 18Nov97 	{	//this is only time you see mouse on single screener
//Old_Code PD 18Nov97 		//put a smacker call here as well!
//Old_Code PD 18Nov97 
//Old_Code PD 18Nov97 		if (--counter==0)
//Old_Code PD 18Nov97 			_Error.EmitSysErr("Timer interrupts have died!");
//Old_Code PD 18Nov97 
//Old_Code PD 18Nov97 		if (currsmk)
//Old_Code PD 18Nov97 			SmackLoad(currsmk);
//Old_Code PD 18Nov97   		_Mouse.Move();
//Old_Code PD 18Nov97 	}

//	tmpxy=Key_Tests.mousepos();

	switch (NumberOfScreens)
	{
	case 0:	//debug physical - need better test...

		Display::ScreenFlip();										//JIM 13Dec95
		if (UseNewPal)
			Display::PalChange();
		UseNewPal=FALSE;
		WindowMoved(oldscr,logicalscreenptr);
//DEAD 		LockBackScreen (TRUE,ZEROLOCK);										//ARM 22Jul96
//DEAD 		UnLockBackScreen (ZEROLOCK);									//ARM 22Jul96
//		LogMouseRestore(mousesave[0].Info);
	break;
	case 1:		//single copy screen

//		tmpxy=Key_Tests.mousepos();

//		SetMouseSaveInfo(0,mouseimagenumber,tmpxy.x,tmpxy.y);

//		LogMouseDrawSave(mouseimage,mousesave[0].Info);
		Display::ScreenFlip();										//JIM 13Dec95
		static char i;
		if ((i+=4)==0 || UseNewPal)
			Display::PalChange();
		UseNewPal=FALSE;
		WindowMoved(oldscr,logicalscreenptr);
//DEAD 		LockBackScreen (TRUE,ZEROLOCK);										//ARM 22Jul96
//DEAD 		UnLockBackScreen (ZEROLOCK);									//ARM 22Jul96
//		LogMouseRestore(mousesave[0].Info);
	break;
	case 2:
//		thru=mousesave[0].Info;
//		mousesave[0].Info=mousesave[1].Info;
//		mousesave[1].Info=thru;
//
//		tmpxy=Key_Tests.mousepos();
//
//		SetMouseSaveInfo(0,mouseimagenumber,tmpxy.x,tmpxy.y);
//
//		LogMouseDrawSave(mouseimage,mousesave[0].Info);
		Display::ScreenFlip();										//JIM 13Dec95
		if (UseNewPal)
			Display::PalChange();
		UseNewPal=FALSE;
		WindowMoved(oldscr,logicalscreenptr);
//DEAD 		LockBackScreen (TRUE,ZEROLOCK);
//DEAD 		UnLockBackScreen (ZEROLOCK);

//DeadCode ARM 23Jul96 		MemScreen(SCREEN_SPARE);
//		LogMouseRestore(mousesave[1].Info);
//DeadCode ARM 23Jul96 		MemScreen(SCREEN_LOGICAL);
		
	break;
	case 3:
//		thru=mousesave[0].Info;					//curr physical	//JIM 04Aug96
//		mousesave[0].Info=mousesave[2].Info;	//curr spare
//		mousesave[2].Info=thru;									//JIM 04Aug96
																//JIM 04Aug96
//		MemScreen(SCREEN_SPARE);
//		LogMouseRestore(mousesave[0].Info);	//should be spare
//		MemScreen(SCREEN_LOGICAL);

//		tmpxy=Key_Tests.mousepos();

//		SetMouseSaveInfo(0,mouseimagenumber,tmpxy.x,tmpxy.y);

//		LogMouseDrawSave(mouseimage,mousesave[0].Info);
		//old phys --> spare
		//old log  --> phys
		//old spare--> log
		Display::ScreenFlip();										//JIM 13Dec95
		if (UseNewPal)
			Display::PalChange();
		UseNewPal=FALSE;
		WindowMoved(oldscr,logicalscreenptr);					//JIM 04Aug96
//DEAD 		LockBackScreen (TRUE,ZEROLOCK);										//JIM 04Aug96
//DEAD 		UnLockBackScreen (ZEROLOCK);									//JIM 04Aug96

	break;
	}

//	Timer_Code.publicframetime=Timer_Code.FullResTestLoopTime();		//PD 18Sep97

//	while	(Timer_Code.TestLoopTime()<Timer_Code.FRAMEMIN)	//WAIT FOR FRAMEMIN
//	{	//this is only time you see mouse on single screener
//		//put a smacker call here as well!
  //
	//	if (--counter==0)
	//		_Error.EmitSysErr("Timer interrupts have died!");
	  //
	//	if (currsmk)
	//		SmackLoad(currsmk);
//  		_Mouse.Move();
	//}

//static  UWord	count=0;
//	count++;
//	logicalscreenptr[count]++;
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoHardPoly
//Author		Paul.   
//Date			Fri 7 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::DoHardPoly(LPPOLYTYPE lpPolyType){return (HardPoly(lpPolyType));}

void Display::DoPushViewData() {PushViewData();}
void Display::DoPopViewData() {PopViewData();}
void Display::DoSet3DWin(SLong x,SLong y,SLong w,SLong h) {Set3DWin(x,y,w,h);}

bool Display::DoScanForBottomPixelsOfText(SWord a,SWord b,SWord c)
{
	return ScanForBottomPixelsOfText(a,b,c);
}

void Display::DoPushPull(UByte a) {PushPull(a);}

void	Display::DoMakePaletteFadeTable(UByte* a,UWord* b,UByte c,UByte d,UByte e)
{	MakePaletteFadeTable(a,b,c,d,e);}

void Display::DoMakeColourRangeFadeTable(UWord* a,UByte b,UByte c,UByte d,UByte e,UByte f,UByte g)
{
	MakeColourRangeFadeTable(a,b,c,d,e,f,g);
}

void Display::DoGetColourInfo(UWord& a,SWord& b,SWord& c,UWord& d,SWord& e,SWord& f,UWord& g,SWord& h,SWord& i)
{GetColourInfo(a,b,c,d,e,f,g,h,i);}

void	Display::DoLockScr(ROWANSURFACEDESC* a) {LockScr(a);}
void	Display::DoUnlockScr(ROWANSURFACEDESC* a) {UnlockScr(a);}

void Display::DoPutLine(SWord a,SWord b,SWord c,SWord d,Colour e){PutLine(a,b,c,d,e);}
void	Display::DoScreenSwap() {ScreenSwap();}
void	Display::DoCaptureScreen() {CaptureScreen();}
void	Display::DoSaveVideoBuffer() {SaveVideoBuffer();}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoGammaCorr
//Author		Paul.   
//Date			Wed 23 Dec 1998
//------------------------------------------------------------------------------
void Display::DoGammaCorr(UByte& r,UByte& g,UByte& b)
{GammaCorr(r,g,b);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetEdgeTest
//Author		Paul.   
//Date			Thu 10 Dec 1998
//------------------------------------------------------------------------------
bool Display::DoSetEdgeTest(bool a) {return SetEdgeTest(a);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetSunPos
//Author		Paul.   
//Date			Fri 27 Nov 1998
//------------------------------------------------------------------------------
void Display::DoSetSunPos(DoPointStruc& a){SetSunPos(a);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetMipMap
//Author		Paul.   
//Date			Tue 24 Nov 1998
//------------------------------------------------------------------------------
bool Display::DoSetMipMap(bool a) {return SetMipMap(a);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoPeripheralBlob
//Author		Paul.   
//Date			Mon 23 Nov 1998
//------------------------------------------------------------------------------
void Display::DoPeripheralBlob(Float* a,Float* b,Float* c,UByte d,SLong e)
{PeripheralBlob(a,b,c,d,e);}

void Display::DoSetFontColour(ULong a)
{SetFontColour(a);}

void Display::DoGetSurfaceDimensions(SLong& a,SLong& b)
{GetSurfaceDimensions(a,b);}

void Display::DoPutC(ImageMapDesc* a,DoPointStruc* b,bool fRefresh)
{PutC(a,b,fRefresh);}

void Display::DoPutA(ImageMapDesc* a,DoPointStruc* b)
{PutA(a,b);}

void Display::Do2DLine(UWord a,UWord b,UWord c,UWord d)
{D2DLine(a,b,c,d);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoRenderTileToDDSurface
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void Display::DoRenderTileToDDSurface(UByte* a,const HTEXT& b)
{RenderTileToDDSurface(a,b);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoGetTextureScales
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void Display::DoGetTextureScales(SLong& a,SLong& b,SLong& c,SLong& d,SLong& e,SLong& f)
{GetTextureScales(a,b,c,d,e,f);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoFreeTexture
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void	Display::DoFreeTexture(const HTEXT& a) {FreeTexture(a);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoFreeTexture
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void	Display::DoFreeTextures() {FreeTextures();}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoAllocateTexture
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
HTEXT	Display::DoAllocateTexture(UByte a) {return AllocateTexture(a);}

void Display::DoFlushAll(Bool f){FlushAll(f);}

SWord	Display::DoForceTQ(SWord a) {return ForceTQ(a);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCalcItemFog
//Author		Paul.   
//Date			Wed 9 Sep 1998
//------------------------------------------------------------------------------
void Display::DoCalcItemFog(bool a,Float& b,Float& c,Float& d)
{
	CalcItemFog(a,b,c,d);
}

bool  Display::DoSetTranspFade(bool a)
{
	return SetTranspFade(a);
}

bool	Display::DoTestAsyncBlt() {return TestAsyncBlt();}

void Display::DoCreateLandTBuffers() {CreateLandTBuffers();}
void*	Display::DoGetLandBufferPtr(SWord a) {return GetLandBufferPtr(a);}
void*	Display::DoGetLandPalLookup() {return GetLandPalLookup();}
void	Display::DoSetLandPalLookup(UByte* a) {SetLandPalLookup(a);}
SWord	Display::DoGetLandBpp() {return GetLandBpp();}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoNewTile
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void Display::DoNewTile(SLong z,DoPointStruc* a,SLong b,UByte* c,SLong d)
{
	NewTile(z,a,b,c,d);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCNewTile
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void Display::DoCNewTile(SLong z,DoPointStruc* a,SLong b,UByte* c,SLong d)
{	
	CNewTile(z,a,b,c,d);
}

void	Display::DoBeginTextureScroll(const SWord a,void* b,void* c)
{
	BeginTextureScroll(a,b,c);
}
void	Display::DoWaitTextureScrollComplete(const SWord a)
{
	WaitTextureScrollComplete(a);
}

void	Display::DoPartialTextureUpload(const SWord a,void* b,void* c)
{
	PartialTextureUpload(a,b,c);
}
void	Display::DoShowLoaderArt(void* pArt)
{
	ShowLoaderArt(pArt);
}

void Display::DoFlushLandDraw() {FlushLandDraw();}
void Display::DoSetAspectRatio(Float ar,Float fov) {SetAspectRatio(ar,fov);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCLEB
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void Display::DoCLEB() {CLEB();}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoAddTile
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void Display::DoAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d)
{AddTile(a,aa,b,c,d);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCAddTile
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void Display::DoCAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d)
{CAddTile(a,aa,b,c,d);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoAddTile
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void Display::DoNearAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d,ULong e)
{NearAddTile(a,aa,b,c,d,e);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCNearAddTile
//Author		Paul.   
//Date			Wed 24 Jun 1998
//------------------------------------------------------------------------------
void Display::DoCNearAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d,ULong e)
{CNearAddTile(a,aa,b,c,d,e);}

void	Display::DoCNearAddTileX(ULong a,ULong b,DoPointStruc* c,ULong d,UByte*& e,const HTEXT& f,UWord flag)
{CNearAddTileX(a,b,c,d,e,f,flag);}

void	Display::DoNearAddTileX(ULong a,ULong b,DoPointStruc* c,ULong d,UByte*& e,const HTEXT& f,UWord flag)
{NearAddTileX(a,b,c,d,e,f,flag);}

void	Display::DoNearAddDitherX(ULong a,ULong b,DoPointStruc* c,ULong d,UByte*& e)
{NearAddDitherX(a,b,c,d,e);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSmokedGlassBox
//Author		Paul    
//Date			Sun 7 Jun 1998
//------------------------------------------------------------------------------
void Display::DoSmokedGlassBox(SWord a,SWord b,SWord c,SWord d,ULong e)
{
	SmokedGlassBox(a,b,c,d,e);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoBeginFan
//Author		Paul.   
//Date			Tue 2 Jun 1998
//------------------------------------------------------------------------------
void Display::DoBeginFan(ULong hTexture) {BeginFan(hTexture);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoBeginFan
//Author		Paul.   
//Date			Tue 2 Jun 1998
//------------------------------------------------------------------------------
void Display::DoBeginFan(ImageMapDesc* pImage) {BeginFan(pImage);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoAddFanPoint
//Author		Paul.   
//Date			Tue 2 Jun 1998
//------------------------------------------------------------------------------
void Display::DoAddFanPoint(DoPointStruc* pdp,SLong vCnt,UByte*& pData)
{AddFanPoint(pdp,vCnt,pData);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoUploadLandTexture
//Author		Paul.   
//Date			Mon 18 May 1998
//------------------------------------------------------------------------------
void Display::DoUploadLandTexture(ULong hTexture,ImageMapDesc* lpImage)
{UploadLandTexture(hTexture,lpImage);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetClipState
//Author		Paul.   
//Date			Wed 29 Apr 1998
//------------------------------------------------------------------------------
bool Display::DoSetClipState(bool newState){return SetClipState(newState);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoReleaseTextures
//Author		Paul.   
//Date			Tue 21 Apr 1998
//------------------------------------------------------------------------------
void Display::DoReleaseTextures(){ReleaseTextures();}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetTextureQuality
//Author		Paul.   
//Date			Mon 20 Apr 1998
//------------------------------------------------------------------------------
void Display::DoSetTextureQuality(bool b){SetTextureQuality(b);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetRangeFog
//Author		Paul.   
//Date			Wed 8 Apr 1998
//------------------------------------------------------------------------------
bool Display::DoSetRangeFog(bool b){return SetRangeFog(b);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoGetHorizonColour
//Author		Paul.   
//Date			Mon 6 Apr 1998
//------------------------------------------------------------------------------
void Display::DoGetHorizonColour(UByte& a,UByte& b,UByte& c)
{GetHorizonColour(a,b,c);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetHorizonColour
//Author		Paul.   
//Date			Mon 6 Apr 1998
//------------------------------------------------------------------------------
void Display::DoSetHorizonColour(UByte a,UByte b,UByte c){SetHorizonColour(a,b,c);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetShadeVals
//Author		Paul.   
//Date			Wed 1 Apr 1998
//------------------------------------------------------------------------------
void Display::DoSetShadeVals(SLong nr,SLong ng,SLong nb,SLong er,SLong eg,SLong eb){SetShadeVals(nr,ng,nb,er,eg,eb);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetLShade
//Author		Paul.   
//Date			Wed 1 Apr 1998
//------------------------------------------------------------------------------
bool Display::DoSetLShade(bool b){return SetLShade(b);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetGlobalAlpha
//Author		Paul.   
//Date			Fri 27 Mar 1998
//------------------------------------------------------------------------------
UByte Display::DoSetGlobalAlpha(UByte a)
{
	return SetGlobalAlpha(a);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoForceRender
//Author		Paul.   
//Date			Tue 24 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoForceRender()
{
	ForceRender();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DomeHorizon
//Author		Paul.   
//Date			Wed 26 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoDomeHorizon(void* lpData,void* lpPolys)
{
	DomeHorizon(lpData,lpPolys);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupLogicalPtr
//Author		Paul.   
//Date			Tue 21 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoBackupLogicalPtr() {BackupLogicalPtr();}		//PD 21Oct97
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetLogicalPtr
//Author		Paul.   
//Date			Tue 21 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoResetLogicalPtr() {ResetLogicalPtr();}			//PD 21Oct97

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetFogState
//Author		Paul.   
//Date			Thu 9 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoSetFogState(Bool bFogState)
{
	SetFogState(bFogState);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoBody2Screen
//Author		Paul.   
//Date			Wed 25 Nov 1998
//------------------------------------------------------------------------------
void Display::DoBody2Screen(DoPointStruc& a)
{
	Body2Screen(a);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetFadeValue
//Author		Paul.   
//Date			Sat 7 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoSetFadeValue(UByte newValue)
{
 	SetFadeValue(newValue);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoEnableBackClip
//Author		Paul.   
//Date			Thu 5 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::DoEnableBackClip(Bool bFlag)
{
 	return (EnableBackClip(bFlag));
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetFade
//Author		Paul.   
//Date			Thu 5 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoSetFade(Colour trgCol,SLong step,TwoDeeEffect tdfx)
{
	SetFade(trgCol,step,tdfx);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		XModeSupported
//Author		Paul.   
//Date			Thu 29 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::XModeSupported(ScreenRez* lpSRez)
{
 	return (ModeSupported(lpSRez));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		XDriverIsCapable
//Author		Paul.   
//Date			Thu 29 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::XDriverIsCapable(SWord drvno)
{
 	return (DriverIsCapable(drvno));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoNameNumberedDriver
//Author		Paul.   
//Date			Fri 23 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte* Display::DoNameNumberedDriver(SWord driverno)
{
 	return (NameNumberedDriver(driverno));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCountDrivers
//Author		Paul.   
//Date			Tue 27 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	Display::DoCountDrivers()
{
	return (CountDrivers());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoHardLine
//Author		Paul.   
//Date			Mon 28 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::DoHardLine(LPLINETYPE lpLineType)
{
	return (HardLine(lpLineType));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoHardPoint
//Author		Paul.   
//Date			Mon 28 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::DoHardPoint(LPPOINTTYPE lpPointType)
{
	return (HardPoint(lpPointType));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoHardPlainRectFill
//Author		Paul.   
//Date			Fri 18 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::DoHardPlainRectFill(Window*win,SWord x, SWord y, SWord w, SWord h)
{
 	return(HardPlainRectFill(win,x,y,w,h));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetViewParams
//Author		Paul.   
//Date			Fri 18 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoSetViewParams(ANGLES a,Window* w,ViewPoint* v)
{
 	SetViewParams(a,w,v);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetZUpdate
//Author		Paul.   
//Date			Mon 7 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::DoSetZUpdate(Bool flag)
{
	return (SetZUpdate(flag));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetPlayerTextures
//Author		Paul.   
//Date			Thu 8 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::DoSetPlayerTextures(Bool flag)
{
	return (SetPlayerTextures(flag));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoingHardware3D
//Author		Paul.   
//Date			Tue 25 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::DoingHardware3D()
{
 	return (Hardware3D());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetMatrices
//Author		Paul.   
//Date			Mon 24 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::DoSetMatrices(SLong viewrange,ANGLES viewang)
{
 	return (SetMatrices(viewrange,viewang));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetFog
//Author		Paul.   
//Date			Mon 24 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoSetFog(UByte r,UByte g,UByte b,SLong start,SLong end)
{
	if (!Save_Data.fSoftware)	SetFog(r,g,b,start,end);
	else						POLYGON.SetFog(r,g,b,start,end);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetFog
//Author		Paul.   
//Date			Fri 23 Oct 1998
//------------------------------------------------------------------------------
void	Display::DoSetFog(UByte r,UByte g,UByte b)
{
	if (!Save_Data.fSoftware)	SetFog(r,g,b);
	else						POLYGON.SetFog(r,g,b);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoGetFog
//Author		Paul.   
//Date			Fri 23 Oct 1998
//------------------------------------------------------------------------------
void	Display::DoGetFog(UByte& r,UByte& g,UByte& b,SLong& s,SLong& e)
{
	if (!Save_Data.fSoftware)	GetFog(r,g,b,s,e);
	else						POLYGON.GetFog(r,g,b,s,e);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoBeginScene
//Author		Paul.   
//Date			Mon 17 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoBeginScene()
{
	BeginScene();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoEndScene
//Author		Paul.   
//Date			Mon 17 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoEndScene()
{
	EndScene();
}

void Display::DoEnd3DScene()
{
	End3DScene();
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HClearScreen
//Author		Paul.   
//Date			Mon 10 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::HClearScreen()
{
 	HCls(FALSE);												//PD 10Jun97
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::PlotLogicalPixel
//------------------------------------------------------------------------------
//Author	Paul.   
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
Colour	Window::PlotLogicalPixel(SWord X, SWord Y,Colour C)//PD 29Nov95
{
	return(Graphic::PlotPixel(X/virtualXscale,Y/virtualYscale,C));//JIM 05Feb96
}

Colour	Window::PlotLogicalPixel(SWord X, SWord Y)//PD 29Nov95
{
	return(Graphic::PlotPixel(X/virtualXscale,Y/virtualYscale));//JIM 05Feb96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Window::ClearScreen
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 5 Jul 1995
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
void Window::ClearScreen(Colour colour)	//PD 29Nov95
{
	SetColour(colour);								//PD 29Nov95
	Graphic::ClearScreen();								//PD 29Nov95
}

//DeadCode JIM 29Mar99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 29Mar99 //Procedure	Window::ShowPic
//DeadCode JIM 29Mar99 //------------------------------------------------------------------------------
//DeadCode JIM 29Mar99 //Author		Paul.   
//DeadCode JIM 29Mar99 //Date		Fri 7 Jul 1995
//DeadCode JIM 29Mar99 //Modified	
//DeadCode JIM 29Mar99 //
//DeadCode JIM 29Mar99 //Description	
//DeadCode JIM 29Mar99 //
//DeadCode JIM 29Mar99 //Inputs	
//DeadCode JIM 29Mar99 //
//DeadCode JIM 29Mar99 //Returns	
//DeadCode JIM 29Mar99 //
//DeadCode JIM 29Mar99 //Externals
//DeadCode JIM 29Mar99 //------------------------------------------------------------------------------
//DeadCode JIM 29Mar99 //------------------------------------------------------------------------------
//DeadCode JIM 29Mar99 void Window::ShowPic(FileNum filenumber)	//PD 29Nov95
//DeadCode JIM 29Mar99 {
//DeadCode JIM 29Mar99 	UByte	*buffer;
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 	if (master->iffartnum!=filenumber)
//DeadCode JIM 29Mar99 	{
//DeadCode JIM 29Mar99 		master->iffartnum=filenumber;
//DeadCode JIM 29Mar99 		master->ifflinenum=1000000;
//DeadCode JIM 29Mar99 	}
//DeadCode JIM 29Mar99 	fileblock art_file(filenumber);
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 	buffer = (UByte *)getdata(art_file);
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 	Graphic::ShowPic(buffer);							//PD 29Nov95
//DeadCode JIM 29Mar99 }
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 void Window::ShowPicScaled(FileNum filenumber,const int scale)	//PD 29Nov95
//DeadCode JIM 29Mar99 {
//DeadCode JIM 29Mar99 	UByte	*buffer;
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 	if (master->iffartnum!=filenumber)
//DeadCode JIM 29Mar99 	{
//DeadCode JIM 29Mar99 		master->iffartnum=filenumber;
//DeadCode JIM 29Mar99 		master->ifflinenum=1000000;
//DeadCode JIM 29Mar99 	}
//DeadCode JIM 29Mar99 	fileblock art_file(filenumber);
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 	buffer = (UByte *)getdata(art_file);
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 	Graphic::ShowPicScaled(buffer,scale);							//PD 29Nov95
//DeadCode JIM 29Mar99 }
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 29Mar99 //Procedure	CharacterPrint
//DeadCode JIM 29Mar99 //------------------------------------------------------------------------------
//DeadCode JIM 29Mar99 //Author		Paul.   
//DeadCode JIM 29Mar99 //Date		Tue 8 Aug 1995
//DeadCode JIM 29Mar99 //Modified	
//DeadCode JIM 29Mar99 //
//DeadCode JIM 29Mar99 //Description	
//DeadCode JIM 29Mar99 //
//DeadCode JIM 29Mar99 //Inputs	
//DeadCode JIM 29Mar99 //
//DeadCode JIM 29Mar99 //Returns	
//DeadCode JIM 29Mar99 //
//DeadCode JIM 29Mar99 //Externals
//DeadCode JIM 29Mar99 //------------------------------------------------------------------------------
//DeadCode JIM 29Mar99 //------------------------------------------------------------------------------
//DeadCode JIM 29Mar99 short Window::CharacterPrint(short character)
//DeadCode JIM 29Mar99 {
//DeadCode JIM 29Mar99 	short	clip_var;
//DeadCode JIM 29Mar99 	if	(character>=fontptr->maxchar+32)
//DeadCode JIM 29Mar99 		character='?';
//DeadCode JIM 29Mar99 CharTableEntryPtr
//DeadCode JIM 29Mar99 	cptr = &(fontptr->charentries[character-32]);
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 	switch	(fontptr->type)
//DeadCode JIM 29Mar99 	{
//DeadCode JIM 29Mar99 		case	FNT_MONOBMP:
//DeadCode JIM 29Mar99 			clip_var = PrintMonoBMP(cptr);
//DeadCode JIM 29Mar99 			break;
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 		case	FNT_MONORUN:
//DeadCode JIM 29Mar99 			clip_var = PrintMonoRUN(cptr);
//DeadCode JIM 29Mar99 			break;
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 		case	FNT_SHADE:
//DeadCode JIM 29Mar99 			clip_var = PrintShade(cptr);
//DeadCode JIM 29Mar99 			break;
//DeadCode JIM 29Mar99 
//DeadCode JIM 29Mar99 		case	FNT_COLOUR:
//DeadCode JIM 29Mar99 			clip_var = PrintColour(cptr);
//DeadCode JIM 29Mar99 			break;
//DeadCode JIM 29Mar99 	}
//DeadCode JIM 29Mar99 	
//DeadCode JIM 29Mar99 	//Update the cursor position
//DeadCode JIM 29Mar99 	CharX+= cptr->NextXShift;							//JIM 09Nov95
//DeadCode JIM 29Mar99 	return(clip_var);
//DeadCode JIM 29Mar99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlainLine
//Author		Paul.   
//Date			Tue 19 Sep 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::PlainLine(SLong x1,SLong y1,SLong x2,SLong y2)//PD 29Nov95
{
	switch (BytesPerPixel)
	{
		case 1:
	 	Graphic::PlainLine(	(SWord)(x1/virtualXscale), (SWord)(y1/virtualYscale),
						   	(SWord)(x2/virtualXscale), (SWord)(y2/virtualYscale));
		break;
		case 2:
	 	Graphic::PlainLine16(	(SWord)(x1/virtualXscale), (SWord)(y1/virtualYscale),
						   		(SWord)(x2/virtualXscale), (SWord)(y2/virtualYscale));
		break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipLine
//Author		Martin Alderton
//Date			Fri 22 Sep 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::ClipLine(SLong x1,SLong y1,SLong x2,SLong y2)//PD 29Nov95
{
 	Graphic::ClipLine(	(SWord)(x1/virtualXscale), 	(SWord)(y1/virtualYscale),
					   	(SWord)(x2/virtualXscale),	(SWord)(y2/virtualYscale));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipLine
//Author		Martin Alderton
//Date			Fri 22 Sep 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::ClipLine3D(SLong x1,SLong y1,SLong x2,SLong y2)//MGA19Feb96
{
 	Graphic::ClipLine3D(	x1, y1,
					   	x2,	y2,
						virtualXscale,
						virtualYscale);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipLine3D
//Author		Robert Slater
//Date			Tue 25 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::ClipLine3D(Float x1,Float y1,Float x2,Float y2)
{
 	Graphic::ClipLine3D(x1, y1, x2,	y2,
						virtualXscale,
						virtualYscale);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		zclipline
//Author		Martin Alderton
//Date			Wed 6 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::zclipline(DoPointStruc& start_vertex, DoPointStruc& end_vertex)
{
	Graphic::zclipline(start_vertex,end_vertex);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlainCircle
//Author		Martin Alderton
//Date			Fri 22 Sep 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::PlainCircle(SLong radius, SLong x1,SLong y1)//PD 29Nov95
{	//should we scale radius by x or y? usually they are the same.
	Graphic::PlainCircle(	(SWord)	(radius/virtualXscale),
							(SWord)	(x1/virtualXscale),	(SWord)	(y1/virtualYscale));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TransparentBlob
//Author		Paul.   
//Date			Mon 28 Jul 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::TransparentBlob(	SWord clipInfo,
								SWord intens,
								SLong radius,
								SLong x,
								SLong y)
{
 	Graphic::TransparentBlob(	clipInfo, intens,
								(SWord)(radius/virtualXscale),
								(SWord)(x/virtualXscale),
								(SWord)(y/virtualYscale));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRealSxy
//Author		Paul.   
//Date			Thu 26 Oct 1995
//
//Description	Scales virtual screen coordinates to physical screen coordinates
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::GetTrunkSxy(SLong &screenx, SLong &screeny)		//PD 29Nov95
{
	screenx-=screenx%virtualXscale;
	screeny-=screeny%virtualYscale;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetScanLineAddr
//Author		Paul.   
//Date			Wed 3 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
HoriLineRtnPtr Window::GetScanLineAddr(SCANLINETYPE type)
{
	return(Graphic::GetScanLineAddr(type));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeIntensityData
//Author		Paul.   
//Date			Wed 8 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::MakeIntensityData()
{
	Graphic::MakeIntensityData();								//PD 29Nov95
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RectangleFill
//Author		Paul.   
//Date			Fri 18 Apr 1997
//
//Description	Plain colour rectangle fill (now tries hardware accel first
//				before doing a software version)
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::RectangleFill(SLong x,SLong y,ULong w,ULong h)
{
	SWord	sx,sy,sw,sh;

	sx = (SWord)(x/virtualXscale);
	sy = (SWord)(y/virtualYscale);
	sw = (SWord)(w/virtualXscale);
	sh = (SWord)(h/virtualYscale);

	if (!Master()->DoHardPlainRectFill(this,sx,sy,sw,sh))
 		Graphic::PlainRectangleFill(sx,sy,sw,sh);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AilRectFill
//Author		Paul.   
//Date			Fri 21 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::AilRectFill(ULong x,ULong y,ULong w,ULong h)
{
 	Graphic::AilRectangleFill(
		(SWord)(x/virtualXscale),
		(SWord)(y/virtualYscale),
		(SWord)(w/virtualXscale),
		(SWord)(h/virtualYscale));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GlassRectFill
//Author		Paul.   
//Date			Tue 2 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::GlassRectFill(ULong x,ULong y,ULong w,ULong h)
{
 	Graphic::GlassRectangleFill(
		(SWord)(x/virtualXscale),
		(SWord)(y/virtualYscale),
		(SWord)(w/virtualXscale),
		(SWord)(h/virtualYscale));
}

//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		conv
//FIX10-2//Author		Jim Taylor
//FIX10-2//Date			Wed 24 Jul 1996
//FIX10-2//
//FIX10-2//Description	Converts coords from 1 window to another
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2ScreenXY	Window::conv(ScreenXY srcxy,const Graphic* srcwin) const
//FIX10-2{
//FIX10-2	static SLong olddelta=0;
//FIX10-2	static	SWord	x=0,y=0;
//FIX10-2SLong	delta=(srcwin->logicalscreenptr-logicalscreenptr);
//FIX10-2
//FIX10-2	if (delta!=olddelta)
//FIX10-2		if (delta)
//FIX10-2		{
//FIX10-2			olddelta=delta;
//FIX10-2			y=delta/BytesPerScanLine;
//FIX10-2			x=delta%BytesPerScanLine;
//FIX10-2			x=x/BytesPerPixel;
//FIX10-2			y=y*virtualYscale;
//FIX10-2			x=x*virtualXscale;
//FIX10-2		}
//FIX10-2		else
//FIX10-2		{
//FIX10-2			olddelta=delta;
//FIX10-2		 	y=0;
//FIX10-2			x=0;
//FIX10-2		}
//FIX10-2	srcxy.x+=x;
//FIX10-2	srcxy.y+=y;
//FIX10-2	return(srcxy);
//FIX10-2}
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		inside
//FIX10-2//Author		Jim Taylor
//FIX10-2//Date			Tue 30 Jan 1996
//FIX10-2//
//FIX10-2//Description	Needs to cope with local window rescaling
//FIX10-2//				No, I don't know how I am going to do this!
//FIX10-2//
//FIX10-2//Inputs		mouse is master based
//FIX10-2//				box is window based
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2Bool	Window::inside(const ScreenXY& mouse,const ScreenXY& boxxy,const ScreenWH& boxwh) const
//FIX10-2{
//FIX10-2	ScreenXY	cm=conv(mouse,master);
//FIX10-2
//FIX10-2	if (cm.x<boxxy.x)	return(FALSE);
//FIX10-2	if (cm.x>boxxy.x+boxwh.w)	return(FALSE);
//FIX10-2	if (cm.y<boxxy.y)	return(FALSE);
//FIX10-2	if (cm.y>boxxy.y+boxwh.h)	return(FALSE);
//FIX10-2	return(TRUE);
//FIX10-2}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScreenShot
//Author		Dave Whiteside
//Date			Mon 19 Feb 1996
//
//Description	take ScreenShot
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Window::ScreenShot()
{
	if (BytesPerPixel==1)
		Graphic::ScreenShot();
	else
		Graphic::ScreenShot16();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScreenShot16
//Author		Paul.   
//Date			Mon 21 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Window::ScreenShot16()
{
	Graphic::ScreenShot16();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyP2L
//Author		Jim Taylor
//Date			Tue 27 Feb 1996
//
//Description	Copy region from physical to logical.
//				This is wonderfully dodgy code...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Graphic::CopyP2L(SWord X,SWord Y,SWord W,SWord H)
{
		LogicalPtr	S=logicalscreenptr;
		S+=X*BytesPerPixel;
		S+=Y*BytesPerScanLine;
		return(((Display*)master)->CopyP2L(S,W,H));

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyP2L
//Author		Jim Taylor
//Date			Tue 27 Feb 1996
//
//Description	Copy region from physical to logical - may do nothing on single/debug
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Window::CopyP2L(SWord X,SWord Y,SWord W,SWord H)
{
 	return	Graphic::CopyP2L(
								(SWord)(X/virtualXscale),
								(SWord)(Y/virtualYscale),
								(SWord)(W/virtualXscale),
								(SWord)(H/virtualYscale));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlotPixel
//Author		Robert Slater
//Date			Thu 14 Mar 1996
//
//Description	Plots a pixel to the display with clipping
//
//Inputs		X, Y and new colour for the pixel
//
//Returns		Old colour of the pixel
//
//------------------------------------------------------------------------------
Colour	Display::PlotPixel(SWord	x, SWord	y, Colour	thecol)
{
	SWord		MinX,MaxX,MinY,MaxY;

	MinX = PhysicalMinX;
	MaxX = MinX + PhysicalWidth;

	MinY = PhysicalMinY;
	MaxY = MinY + PhysicalHeight;

	if(x >= MinX && x < MaxX && y >= MinY && y < MaxY)
		return((Colour)PlotPixelNoClip(x,y,thecol));

	return((Colour)-1);

}
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		PlotMouseScanline
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Mon 11 Mar 1996
//FIX10-2//
//FIX10-2//Description	Plots the mouse pointer
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2void	Display::PlotMouseScanline(SWord	x, SWord	y, SWord	w, UByte	*&pos)
//FIX10-2{
//FIX10-2	int		code;
//FIX10-2
//FIX10-2	UByte	*image = pos;
//FIX10-2
//FIX10-2	SWord	endx = x + w;
//FIX10-2
//FIX10-2
//FIX10-2	while (x < endx)
//FIX10-2	{
//FIX10-2		code = *(image++);
//FIX10-2
//FIX10-2		if (code == 0x80)
//FIX10-2		{
//FIX10-2			x = x + 1 + *(image++);
//FIX10-2		}
//FIX10-2		elseif (code < 0x80)
//FIX10-2			{
//FIX10-2				while (code >= 0)
//FIX10-2				{
//FIX10-2					PlotPixel(x++, y, (Colour)*(image++));
//FIX10-2
//FIX10-2					code--;
//FIX10-2				}
//FIX10-2			}
//FIX10-2			else
//FIX10-2			{
//FIX10-2#ifdef __WATCOMC__
//FIX10-2				INT3();
//FIX10-2#else
//FIX10-2#ifdef __MSVC__
//FIX10-2				INT3;
//FIX10-2#endif
//FIX10-2#endif
//FIX10-2			}
//FIX10-2	}
//FIX10-2
//FIX10-2	pos = image;
//FIX10-2}
//FIX10-2
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		PlotAndSaveMouseScanline
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Mon 11 Mar 1996
//FIX10-2//
//FIX10-2//Description	Saves current image and plots the mouse pointer over it
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2void	Display::PlotAndSaveMouseScanline(SWord	x, SWord	y, SWord	w, UByte	*&oldpos, UByte	*&newpos)
//FIX10-2{
//FIX10-2	int		code, gap, colour;
//FIX10-2	UByte	*newimage = newpos;
//FIX10-2	UByte	*oldimage = oldpos;
//FIX10-2	
//FIX10-2	SWord	endx = x + w;
//FIX10-2
//FIX10-2
//FIX10-2	while (x < endx)
//FIX10-2	{
//FIX10-2		code = *(oldimage++);
//FIX10-2
//FIX10-2		*(newimage++) = (UByte) code;
//FIX10-2
//FIX10-2		if (code == 0x80)
//FIX10-2		{
//FIX10-2			gap = *(oldimage++);
//FIX10-2
//FIX10-2			*(newimage++) = (UByte) gap;
//FIX10-2
//FIX10-2			x = x + gap + 1;
//FIX10-2		}
//FIX10-2		elseif (code < 0x80)
//FIX10-2			{
//FIX10-2				while (code >= 0)
//FIX10-2				{
//FIX10-2					colour = *(oldimage++);
//FIX10-2
//FIX10-2					*(newimage++) = (UByte) PlotPixel(x++, y, (Colour)colour);
//FIX10-2
//FIX10-2					code--;
//FIX10-2				}
//FIX10-2			}
//FIX10-2			else
//FIX10-2			{
//FIX10-2#ifdef __WATCOMC__
//FIX10-2				INT3();
//FIX10-2#else
//FIX10-2#ifdef __MSVC__
//FIX10-2				INT3;
//FIX10-2#endif
//FIX10-2#endif
//FIX10-2			}
//FIX10-2	}
//FIX10-2
//FIX10-2	newpos = newimage;
//FIX10-2	oldpos = oldimage;
//FIX10-2
//FIX10-2}
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		PlotMouseScanline
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Tue 12 Mar 1996
//FIX10-2//
//FIX10-2//Description	
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2void	Graphic::PlotMouseScanline(SWord	x, SWord	y, SWord	w, UByte	*&pos)
//FIX10-2{
//FIX10-2	int		code;
//FIX10-2
//FIX10-2	UByte	*image = pos;
//FIX10-2
//FIX10-2	SWord	endx = x + w;
//FIX10-2
//FIX10-2
//FIX10-2	while (x < endx)
//FIX10-2	{
//FIX10-2		code = *(image++);
//FIX10-2
//FIX10-2		if (code == 0x80)
//FIX10-2		{
//FIX10-2			x = x + 1 + *(image++);
//FIX10-2		}
//FIX10-2		elseif (code < 0x80)
//FIX10-2			{
//FIX10-2				while (code >= 0)
//FIX10-2				{
//FIX10-2					PlotPixel(x++, y, (Colour)*(image++));
//FIX10-2
//FIX10-2					code--;
//FIX10-2				}
//FIX10-2			}
//FIX10-2			else
//FIX10-2			{
//FIX10-2#ifdef __WATCOMC__
//FIX10-2				INT3();
//FIX10-2#else
//FIX10-2#ifdef __MSVC__
//FIX10-2				INT3;
//FIX10-2#endif
//FIX10-2#endif
//FIX10-2			}
//FIX10-2	}
//FIX10-2
//FIX10-2	pos = image;
//FIX10-2}
//FIX10-2
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		PlotAndSaveMouseScanline
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Mon 11 Mar 1996
//FIX10-2//
//FIX10-2//Description	
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2void	Graphic::PlotAndSaveMouseScanline(SWord	x, SWord	y, SWord	w, UByte	*&oldpos, UByte	*&newpos)
//FIX10-2{
//FIX10-2	int		code, colour;
//FIX10-2	UByte	*newimage = newpos;
//FIX10-2	UByte	*oldimage = oldpos;
//FIX10-2	
//FIX10-2	SWord	endx = x + w;
//FIX10-2
//FIX10-2
//FIX10-2	while (x < endx)
//FIX10-2	{
//FIX10-2		code = *(oldimage++);
//FIX10-2
//FIX10-2		*(newimage++) = (UByte) code;
//FIX10-2
//FIX10-2		if (code == 0x80)
//FIX10-2		{
//FIX10-2			x = x + 1 + (*(newimage++) = *(oldimage++));
//FIX10-2
//FIX10-2
//FIX10-2		}
//FIX10-2		elseif (code < 0x80)
//FIX10-2			{
//FIX10-2				while (code >= 0)
//FIX10-2				{
//FIX10-2					colour = *(oldimage++);
//FIX10-2
//FIX10-2					*(newimage++) = (UByte) PlotPixel(x++, y, (Colour)colour);
//FIX10-2
//FIX10-2					code--;
//FIX10-2				}
//FIX10-2			}
//FIX10-2			else
//FIX10-2			{
//FIX10-2#ifdef __WATCOMC__
//FIX10-2				INT3();
//FIX10-2#else
//FIX10-2#ifdef __MSVC__
//FIX10-2				INT3;
//FIX10-2#endif
//FIX10-2#endif
//FIX10-2			}
//FIX10-2	}
//FIX10-2
//FIX10-2	newpos = newimage;
//FIX10-2	oldpos = oldimage;
//FIX10-2
//FIX10-2}
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		PhysMouseMove
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Mon 11 Mar 1996
//FIX10-2//
//FIX10-2//Description	
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2void	Display::PhysMouseMove(SWord	newx, SWord	newy, short	imagenum)
//FIX10-2{
//FIX10-2
//FIX10-2	if (BytesPerPixel!=1)
//FIX10-2//DeadCode JIM 19Jan98 	if (Whole_Screen->BytesPerPixel!=1)
//FIX10-2		return;
//FIX10-2	SWord		oldx, oldy, oldw, oldh;
//FIX10-2	SWord		neww, newh;
//FIX10-2	SWord		y, botnew, botold;
//FIX10-2	UByte		*tmpmouseshape, *tmpnewimage, *tmpoldimage;
//FIX10-2//	MouseSave	*oldpos, *newpos, *thru;
//FIX10-2
//FIX10-2
//FIX10-2	// Set up the new mouse information
//FIX10-2
//FIX10-2	
//FIX10-2	if (imagenum!=0)
//FIX10-2	{
//FIX10-2		SetMouseSaveInfo(1,imagenum,newx,newy);
//FIX10-2		tmpmouseshape = MousePixelData(imagenum);
//FIX10-2	}
//FIX10-2	else
//FIX10-2	{
//FIX10-2		SetMouseSaveInfo(1,mouseimagenumber,newx,newy);
//FIX10-2		tmpmouseshape = MousePixelData(mouseimagenumber);
//FIX10-2	}
//FIX10-2	oldpos = mousesave[0].Info;
//FIX10-2	newpos = mousesave[1].Info;
//FIX10-2
//FIX10-2
//FIX10-2	oldx = oldpos->XY.x;
//FIX10-2	oldy = oldpos->XY.y;
//FIX10-2	oldw = oldpos->WH.w;
//FIX10-2	oldh = oldpos->WH.h;
//FIX10-2
//FIX10-2	newx = newpos->XY.x;
//FIX10-2	newy = newpos->XY.y;
//FIX10-2	neww = newpos->WH.w;
//FIX10-2	newh = newpos->WH.h;
//FIX10-2
//FIX10-2	tmpnewimage = (UByte*) newpos->dataptr;
//FIX10-2	tmpoldimage = (UByte*) oldpos->dataptr;
//FIX10-2
//FIX10-2
//FIX10-2	// Check if new position is above old position on screen
//FIX10-2
//FIX10-2	botnew = newy + newh;
//FIX10-2	botold = oldy + oldh;			
//FIX10-2
//FIX10-2	if (newy < oldy)
//FIX10-2	{
//FIX10-2		y = newy;
//FIX10-2
//FIX10-2		if (botnew < oldy)
//FIX10-2		{
//FIX10-2			//	Case 1...
//FIX10-2
//FIX10-2
//FIX10-2			while (y < botnew)
//FIX10-2				PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2
//FIX10-2
//FIX10-2			// Restore old image...
//FIX10-2
//FIX10-2			y = oldy;
//FIX10-2
//FIX10-2			while (y < botold)
//FIX10-2				PlotMouseScanline(oldx, y++, oldw, tmpoldimage);
//FIX10-2		}
//FIX10-2		else
//FIX10-2		{
//FIX10-2			if (botnew < botold)
//FIX10-2			{
//FIX10-2				// 	Case 5...
//FIX10-2
//FIX10-2
//FIX10-2				while (y < oldy)
//FIX10-2					PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2
//FIX10-2				while (y < botnew)
//FIX10-2				{
//FIX10-2					PlotMouseScanline(oldx, y, oldw, tmpoldimage);
//FIX10-2					PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2				}
//FIX10-2
//FIX10-2				while (y < botold)
//FIX10-2					PlotMouseScanline(oldx, y++, oldw, tmpoldimage);
//FIX10-2			}
//FIX10-2			else
//FIX10-2			{
//FIX10-2				// 	Case 6...
//FIX10-2
//FIX10-2
//FIX10-2				while (y < oldy)
//FIX10-2					PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2
//FIX10-2				while (y < botold)
//FIX10-2				{
//FIX10-2					PlotMouseScanline(oldx, y, oldw, tmpoldimage);
//FIX10-2					PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2				}
//FIX10-2
//FIX10-2				while (y < botnew)
//FIX10-2					PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2			}
//FIX10-2		}
//FIX10-2	}
//FIX10-2	else
//FIX10-2	{
//FIX10-2		y = oldy;
//FIX10-2
//FIX10-2		if (newy > botold)
//FIX10-2		{
//FIX10-2			//	Case 2
//FIX10-2
//FIX10-2
//FIX10-2			while (y < botold)
//FIX10-2				PlotMouseScanline(oldx, y++, oldw, tmpoldimage);
//FIX10-2
//FIX10-2			y = newy;
//FIX10-2
//FIX10-2			while (y < botnew)
//FIX10-2				PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2
//FIX10-2		}
//FIX10-2		else
//FIX10-2		{
//FIX10-2			if (botold < botnew)
//FIX10-2			{
//FIX10-2				//	Case 4
//FIX10-2
//FIX10-2
//FIX10-2				while (y < newy)
//FIX10-2					PlotMouseScanline(oldx, y++, oldw, tmpoldimage);
//FIX10-2
//FIX10-2				while (y < botold)
//FIX10-2				{
//FIX10-2					PlotMouseScanline(oldx, y, oldw, tmpoldimage);
//FIX10-2					PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2				}
//FIX10-2
//FIX10-2				while (y < botnew)
//FIX10-2					PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2			}
//FIX10-2			else
//FIX10-2			{
//FIX10-2				//	Case 3
//FIX10-2
//FIX10-2
//FIX10-2				while (y < newy)
//FIX10-2					PlotMouseScanline(oldx, y++, oldw, tmpoldimage);
//FIX10-2
//FIX10-2				while (y < botnew)
//FIX10-2				{
//FIX10-2					PlotMouseScanline(oldx, y, oldw, tmpoldimage);
//FIX10-2					PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2				}
//FIX10-2
//FIX10-2				while (y < botold)
//FIX10-2					PlotMouseScanline(oldx, y++, oldw, tmpoldimage);
//FIX10-2			}
//FIX10-2		}
//FIX10-2	}
//FIX10-2
//FIX10-2	thru = mousesave[0].Info;
//FIX10-2	mousesave[0].Info = mousesave[1].Info;
//FIX10-2	mousesave[1].Info = thru;
//FIX10-2
//FIX10-2}
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		LogMouseDrawSave
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Mon 11 Mar 1996
//FIX10-2//
//FIX10-2//Description	Draws new image to logical screen and saves the old one	
//FIX10-2//
//FIX10-2//Inputs		The new image and mouse shape		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2void	Graphic::LogMouseDrawSave(void	*MouseShape, MouseSave	*newpos)
//FIX10-2{
//FIX10-2	SWord	newx, newy, neww, newh;
//FIX10-2	SWord	y, botnew;
//FIX10-2	UByte	*tmpmouseshape, *tmpnewimage;
//FIX10-2
//FIX10-2	newx = newpos->XY.x;
//FIX10-2	newy = newpos->XY.y;
//FIX10-2	neww = newpos->WH.w;
//FIX10-2	newh = newpos->WH.h;
//FIX10-2
//FIX10-2	tmpmouseshape = (UByte*)	MouseShape;
//FIX10-2	tmpnewimage = (UByte*) newpos->dataptr;
//FIX10-2
//FIX10-2	y = newy;
//FIX10-2
//FIX10-2	botnew = newy + newh;
//FIX10-2
//FIX10-2	while (y < botnew)
//FIX10-2		PlotAndSaveMouseScanline(newx, y++, neww, tmpmouseshape, tmpnewimage);
//FIX10-2
//FIX10-2}
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		LogMouseRestore
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Mon 11 Mar 1996
//FIX10-2//
//FIX10-2//Description	Do mouse repair to logical screen
//FIX10-2//
//FIX10-2//Inputs		Mouse information
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2void	Graphic::LogMouseRestore(MouseSave	*oldpos)
//FIX10-2{
//FIX10-2	SWord	oldx, oldy, oldw, oldh;
//FIX10-2	SWord	y, botold;
//FIX10-2
//FIX10-2	UByte	*tmpoldimage;
//FIX10-2
//FIX10-2	Master()->LockBackScreen (TRUE,LOWLOCK);					//AMM 02May97
//FIX10-2
//FIX10-2	oldx = oldpos->XY.x;
//FIX10-2	oldy = oldpos->XY.y;
//FIX10-2	oldw = oldpos->WH.w;
//FIX10-2	oldh = oldpos->WH.h;
//FIX10-2
//FIX10-2	tmpoldimage = (UByte*) oldpos->dataptr;
//FIX10-2
//FIX10-2	y = oldy;
//FIX10-2
//FIX10-2	botold = oldy + oldh;
//FIX10-2
//FIX10-2
//FIX10-2	while (y < botold)
//FIX10-2		PlotMouseScanline(oldx, y++, oldw, tmpoldimage);
//FIX10-2
//FIX10-2	Master()->UnLockBackScreen (LOWLOCK);					//AMM 02May97
//FIX10-2}
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		LoadMouseImage
//FIX10-2//Author		Robert Slater
//FIX10-2//Date			Tue 12 Mar 1996
//FIX10-2//
//FIX10-2//Description	Load the mouse image as a font
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2void	Display::LoadMouseImage(FileNum filenumber)
//FIX10-2{
//FIX10-2	static	fileblockptr	loadedhandle = NULL;
//FIX10-2	short					width, delta, height, x,y;
//FIX10-2	ULong					size;
//FIX10-2
//FIX10-2	//Dispose old font if any
//FIX10-2
//FIX10-2	if (mousefontptr != NULL)
//FIX10-2		delete(loadedhandle);
//FIX10-2
//FIX10-2
//FIX10-2	//Load new font data
//FIX10-2
//FIX10-2	loadedhandle = new fileblock(filenumber,FixupFontHeader);
//FIX10-2
//FIX10-2	mousefontptr = (FontPtr)	getdata(*loadedhandle);
//FIX10-2
//FIX10-2
//FIX10-2
//FIX10-2	width = (short)	(mousefontptr->charentries[0].NextXShift);
//FIX10-2	height = (short) (mousefontptr->charentries[0].Height);
//FIX10-2
//FIX10-2	size = width * height;
//FIX10-2
//FIX10-2	// Allocate 2 or more buffers for the mouse data...
//FIX10-2
//FIX10-2
//FIX10-2	mousesave[0].dataptr = new	char[size];
//FIX10-2	mousesave[0].datasize = size;
//FIX10-2
//FIX10-2	mousesave[1].dataptr = new	char[size];
//FIX10-2	mousesave[1].datasize = size;
//FIX10-2
//FIX10-2	if (NumberOfScreens > 2)
//FIX10-2	{
//FIX10-2		mousesave[2].dataptr = new char[size];
//FIX10-2		mousesave[2].datasize = size;
//FIX10-2	}
//FIX10-2
//FIX10-2
//FIX10-2
//FIX10-2}
//FIX10-2
//FIX10-2
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrintIcon
//Author		Jim Taylor
//Date			Thu 18 Apr 1996
//
//Description	Print a character from the mouse font as an icon...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Window::PrintIcon(int x,int y,int iconnum)
{
	if (iconnum>=mousefontptr->maxchar)
		iconnum=2;
CharTableEntryPtr
	cptr = & mousefontptr->charentries[iconnum];
	Graphic::PrintIcon(x/virtualXscale,y/virtualYscale,iconnum,cptr);
}

void	Graphic::PrintIcon(int sx,int sy,int iconnum,CharTableEntryPtr cptr)
{
	SWord	width,height;	//Width and height of the packed data
	UByte	*src;
	sx-=cptr->NextXShift;
	sy+=cptr->YShift;
	src = (UByte *) cptr->pixeldata;								//DAW 29Nov95
	
	width = cptr->Width;
	height = cptr->Height+sy;
	if (height>(PhysicalMinY+PhysicalHeight))
	{
		while(sy<PhysicalMinY)
		{
			src = Graphic::SkipRow(src,width);
			sy++;
		}
		while(sy<(PhysicalMinY+PhysicalHeight))
			src = Graphic::UnpackRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth);
	}
	else
	{
		while(sy<PhysicalMinY)
		{
			src = Graphic::SkipRow(src,width);
			sy++;
		}
		while(sy<height)
			src = Graphic::UnpackRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RegisterPalette
//Author		Robert Slater
//Date			Tue 22 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::RegisterPalette(UByte* src,SLong length)
{
 	Graphic::RegisterPalette(src,length);
	Master()->HWRegisterPal(src,ULong(length));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReinitDisplay
//Author		Paul.   
//Date			Thu 3 Jul 1997
//
//Description	Resets logical ptr & palette after windows task switch
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Window::ReinitDisplay()
{
	Graphic::ReinitDisplay();
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoTestHW3D
//Author		Paul.   
//Date			Tue 23 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DoTestHW3D(Window* w)
{
	TestHW3D(w);
}


