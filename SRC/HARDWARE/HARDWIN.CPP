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
//Filename       hardwin.cpp
//System         
//Author         Andrew McRae
//Date           Fri 7 Jun 1996
//Description    Direct Draw Stuff
//------------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN

#include	<stdio.h>
#include	<stdlib.h>

#include	"DOSDefs.H"

#include 	<windows.h>
#include 	<windowsx.h>
#include 	<mmsystem.h>

#include	<ddraw.h>

#include	"myerror.h"

#include	"DISPLAY.h"											//RDH 31Jul97

#include "mathasm.h"											//PD 24Aug98

#include	"Win3d.h"											//PD 31Jan97

#include "mathasm.h"

//#define DDSCAPS_LOCALVIDMEM 0x10000000l
#define DDSCAPS_LOCALVIDMEM 0x00000000l

#define		WINDOWED_PALETTE

inline void directdraw_ClearSurface(LPDIRECTDRAWSURFACE pDDS)
{
	LPDIRECTDRAWSURFACE lpDDS=pDDS;
	if (!lpDDS->IsLost())
		while (lpDDS!=NULL)
		{
			HRESULT hr;
			DDSURFACEDESC sd;
			DDSCAPS sc;
			sc.dwCaps=DDSCAPS_BACKBUFFER;
			memset(&sd,0,sizeof(sd));
			sd.dwSize=sizeof(sd);
			do{hr=lpDDS->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);}
			while (hr!=DD_OK);
			ULong sw=sd.dwWidth>>1;

			if (sd.lPitch!=0){
				UByte* pDst=(UByte*)sd.lpSurface;
				for (SLong i=sd.dwHeight;i>0;i--){
					ULong* pDst2=(ULong*)pDst;
					for (SLong j=sw;j>0;j--) *pDst2++=ULong(0);
					pDst+=sd.lPitch;
				}
			}
			else{
				ULong* pDst=(ULong*)sd.lpSurface;
				for (SLong i=sw*sd.dwHeight;i>0;i--) *pDst++=ULong(0);
			}
			lpDDS->Unlock(sd.lpSurface);
			hr=lpDDS->GetAttachedSurface(&sc,&lpDDS);
		}
}

static LogicalPtr
bupLogicalScreenPtr=NULL;

extern UWord polyRedBits,polyRedShift,polyGreenBits,polyGreenShift,polyBlueBits,polyBlueShift;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		XX_SetGraphicsMode
//Author		Andrew McRae
//Date			Tue 25 Jun 1996
//
//Description	Setup Direct Draw Surfaces & Screen Mode
//
//Inputs		None
//
//Returns		None
//
//------------------------------------------------------------------------------
void	Display::XX_SetGraphicsMode()
{
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[4]='@';

	LogicalPtr	oldscreenaddr;
	int			oldbytesperscanline;
	int			oldbytesperpixel;
	int			oldscalex;
	int			oldscaley;

	if (bupLogicalScreenPtr!=NULL)
	{
		oldscreenaddr=logicalscreenptr;
		oldbytesperscanline=BytesPerScanLine;
		oldbytesperpixel=BytesPerPixel;
		oldscalex=virtualXscale;
		oldscaley=virtualYscale;

	}

	prevmodeAX = 0;

	VirtualMinX = 0;		//these should never be>word
	VirtualWidth  = FULLW;	//note that these virtual mins and sizes
	VirtualMinY = 0;		//must be proportional to 
	VirtualHeight = FULLH;	//physical mins and sizes so zero is in same place

	DD.pScreenB = (UByteP)NULL;

	ULong res;

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[4]='A';
	res = SetDirectDrawMode (DD.DDModes[DD.DDCurrMode]);

	if (res == 0)
	{
//DEAD 		LockBackScreen (FALSE);
//DEAD 		UnLockBackScreen ();
	}
	else
	{
		logicalscreenptr = (LogicalPtr)FALSE;
	}

	// Setup Vars

	BytesPerPixel = DD.DDModes[DD.DDCurrMode].colourdepth/8;

//RDH 16Oct97 - set screen RGB format information for non-8bpp modes

	if (BytesPerPixel!=1)
	{
		DWORD	bits,shift,mask;

		for (	shift=0,
				mask =DD.lpddsd->ddpfPixelFormat.dwRBitMask;
				!(mask & 1);
				shift++,
				mask>>=1);

		for (	bits=0; mask & 1; bits++, mask>>=1);
			
		polyRedBits = RedBits = bits;		polyRedShift = RedShift = shift;

		for (	shift=0,
				mask =DD.lpddsd->ddpfPixelFormat.dwGBitMask;
				!(mask & 1);
				shift++,
				mask>>=1);

		for (	bits=0; mask & 1; bits++, mask>>=1);

		polyGreenBits = GreenBits = bits;	polyGreenShift = GreenShift = shift;

		for (	shift=0,
				mask =DD.lpddsd->ddpfPixelFormat.dwBBitMask;
				!(mask & 1);
				shift++,
				mask>>=1);

		for (	bits=0; mask & 1; bits++, mask>>=1);

		polyBlueBits = BlueBits = bits;	polyBlueShift = BlueShift = shift;
	}
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[4]='B';

	ChangeBytesPerScanLine ();

	RECT	rect;
	if (!DD.lpDirectDD->isFullScreen()){
		::GetWindowRect(DD.hWnd,&rect);
	}
	else{
	 	rect.top=rect.left=0;
		rect.bottom=DD.DDModes[DD.DDCurrMode].height;
		rect.right=DD.DDModes[DD.DDCurrMode].width;
	}
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[4]='C';

	int	window_width = rect.right - rect.left;
	int	window_height = rect.bottom - rect.top;

	PhysicalMinX = 0;
	PhysicalWidth = window_width;		//Width of screen in pixels
	PhysicalMinY = 0;
	PhysicalHeight = window_height;		//Height of screen in pixels

	virtualXscale = (FULLW+window_width-1) / window_width;
	virtualYscale = (FULLH+window_height-1) / window_height;

	// Memory for DirectDraw Palette Table

	if (DD.PaletteBuffer==NULL)
		DD.PaletteBuffer = new MYPALETTEENTRY [256];

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[4]='D';
	if (bupLogicalScreenPtr!=NULL && (int)oldscreenaddr!=-1)
	{
		Window* window;

		window=(Window*)windowlink;

		while (window)
		{
			if (window->logicalscreenptr!=oldscreenaddr)
			{
				int	oldx=window->logicalscreenptr-oldscreenaddr;
				int	oldy=oldx/oldbytesperscanline;
				oldx=oldx%oldbytesperscanline;
				oldx=oldx/oldbytesperpixel;

				oldx*=oldscalex;
				oldy*=oldscaley;
				oldx/=virtualXscale;
				oldy/=virtualYscale;

				oldx =	oldx*BytesPerPixel+
						oldy*BytesPerScanLine;

				window->logicalscreenptr=logicalscreenptr + oldx;
			}
			else
				window->logicalscreenptr=logicalscreenptr;

			window->NumberOfScreens=NumberOfScreens;
			window->virtualXscale*=virtualXscale;
			window->virtualXscale/=oldscalex;
			window->virtualYscale*=virtualYscale;
			window->virtualYscale/=oldscaley;

			window->BytesPerScanLine=BytesPerScanLine;
			window->BytesPerPixel   =BytesPerPixel;
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


			window->RedBits			=RedBits;			//JIM 20Oct97
			window->GreenBits		=GreenBits;		//JIM 20Oct97
			window->BlueBits 		=BlueBits;		//JIM 20Oct97
			window->RedShift		=RedShift;		//JIM 20Oct97
			window->GreenShift		=GreenShift;		//JIM 20Oct97
			window->BlueShift 		=BlueShift;		//JIM 20Oct97

			window=(Window*)window->windowlink;
		}

	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		XX_ScreenFlip
//Author		Andrew McRae
//Date			Tue 25 Jun 1996
//
//Description	Flip Direct Draw Primary and Back surfaces
//
//Inputs		None
//
//Returns		None
//
//------------------------------------------------------------------------------
void	Display::XX_ScreenFlip()
{
	RECT 	rect;
	DDBLTFX	ddbltfx;
	HRESULT ddrval;

	if (DD.ModeX)	return;

	switch (NumberOfScreens)
	{
	case 0:
	break;
	case 1:

		::GetWindowRect(DD.hWnd,&rect);

		ddbltfx.dwSize = sizeof (DDBLTFX);

		ddrval = DD.lpDDSPrimary->Blt(	&rect,
										DD.lpDDSBack,
										NULL,	//&rect,
										DDBLT_WAIT,
										&ddbltfx);
		if (ddrval != DD_OK)
		{			 //DDERR_SURFACELOST
		}

	break;

	case 2:
		if (DD.lpDDSPrimary)
		    ddrval=DD.lpDDSPrimary->Flip ( NULL, DDFLIP_WAIT );
	break;

	case 3:
		if (DD.lpDDSPrimary)
		    DD.lpDDSPrimary->Flip ( DD.Screens[DD.DDSpareScreen],
									DDFLIP_WAIT );
		// rotate indexes
		if (++DD.DDOnScreen == 4) 		DD.DDOnScreen = 1;
		if (++DD.DDSpareScreen == 4) 	DD.DDSpareScreen = 1;
		if (++DD.DDLogicalScreen == 4) 	DD.DDLogicalScreen = 1;

	break;

	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LockBackScreen
//Author		Andrew McRae
//Date			Tue 25 Jun 1996
//
//Description	Locks Direct Draw Back Surface & gets ptr to it
//
//Inputs		none
//
//Returns		none
//
//------------------------------------------------------------------------------
//DEAD void	Display::LockBackScreen (Bool winmov)
//DEAD {
//DEAD 	if (DD.ModeX)	return;

//DEAD 	switch (NumberOfScreens)
//DEAD 	{
//DEAD 	case 0:
//DEAD 		while (DD.lpDDSPrimary->Lock(	NULL,
//DEAD 										DD.lpddsd,
//DEAD 										DDLOCK_SURFACEMEMORYPTR |
//DEAD 										DDLOCK_WAIT,
//DEAD 										NULL) != DD_OK) {};
//DEAD 		if (winmov)
//DEAD 			WindowMoved (logicalscreenptr, (LogicalPtr)DD.lpddsd->lpSurface);

//DEAD 		logicalscreenptr = (LogicalPtr)DD.lpddsd->lpSurface;
//DEAD 	break;
//DEAD 	case 1:
//DEAD 		while (DD.lpDDSBack->Lock(	NULL,
//DEAD 									DD.lpddsd,
//DEAD 									DDLOCK_SURFACEMEMORYPTR |
//DEAD 									DDLOCK_WAIT,
//DEAD 									NULL) != DD_OK) {};
//DEAD 		if (winmov)
//DEAD 			WindowMoved (logicalscreenptr, (LogicalPtr)DD.lpddsd->lpSurface);

//DEAD 		logicalscreenptr = (LogicalPtr)DD.lpddsd->lpSurface;
//DEAD 	break;
//DEAD 	case 2:
//DEAD 		while (DD.lpDDSBack->Lock(	NULL,
//DEAD 									DD.lpddsd,
//DEAD 									DDLOCK_SURFACEMEMORYPTR |
//DEAD 									DDLOCK_WAIT,
//DEAD 									NULL) != DD_OK) {};
//DEAD 		if (winmov)
//DEAD 			WindowMoved (logicalscreenptr, (LogicalPtr)DD.lpddsd->lpSurface);

//DEAD 		logicalscreenptr = (LogicalPtr)DD.lpddsd->lpSurface;
//DEAD 	break;

//DEAD 	case 3:
//DEAD 		while (DD.Screens[DD.DDLogicalScreen]->Lock(NULL,
//DEAD 													DD.lpddsd,
//DEAD 													DDLOCK_SURFACEMEMORYPTR |
//DEAD 													DDLOCK_WAIT,
//DEAD 													NULL) != DD_OK) {};
//DEAD 		if (winmov)
//DEAD 			WindowMoved (logicalscreenptr, (LogicalPtr)DD.lpddsd->lpSurface);

//DEAD 		logicalscreenptr = (LogicalPtr)DD.lpddsd->lpSurface;
//DEAD 	break;
//DEAD 	}	
//DEAD }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnableGUI
//Author		Andrew McRae
//Date			Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::EnableGUI (Bool Ctrl)
{
	if (DD.ModeX)	return;

	HRESULT res;

	res = DD.lpDD2->FlipToGDISurface ();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLockBackScreen
//Author		Andrew McRae
//Date			Tue 25 Jun 1996
//
//Description	Unlocks Direct Draw BAck Surface
//
//Inputs		None
//
//Returns		None
//
//------------------------------------------------------------------------------
//DEAD void	Display::UnLockBackScreen ()
//DEAD {
//DEAD 	if (DD.ModeX)	return;

//DEAD 	switch (NumberOfScreens)
//DEAD 	{
//DEAD 	case 0:
//DEAD 		DD.lpDDSPrimary->Unlock (DD.lpddsd->lpSurface );
//DEAD 	break;
//DEAD 	case 1:
//DEAD 		DD.lpDDSBack->Unlock (DD.lpddsd->lpSurface );
//DEAD 	break;
//DEAD 	case 2:
//DEAD 		DD.lpDDSBack->Unlock (DD.lpddsd->lpSurface );
//DEAD 	break;
//DEAD 	case 3:
//DEAD 		DD.Screens[DD.DDLogicalScreen]->Unlock (DD.lpddsd->lpSurface );
//DEAD 	break;
//DEAD 	}
//DEAD }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		XX_PalChange
//Author		Andrew McRae
//Date			Tue 25 Jun 1996
//
//Description	Changes Primary surface Palette
//
//Inputs		None
//
//Returns		None
//
//------------------------------------------------------------------------------

void	Display::XX_PalChange()
{
	// Palette points to 768 table of colours
	if (Palette)
	{
		ULong n;

		LPPALETTEENTRY pDDPal;
		char * pMyPal;

		pDDPal = (LPPALETTEENTRY)DD.PaletteBuffer;
		pMyPal = (char *)Palette;

		for (int index = 0 /*index = 10*/; index < 256/*246*/; index ++) 
		{ 
 			pDDPal[index].peFlags = PC_NOCOLLAPSE|PC_RESERVED; 
			pDDPal[index].peRed = *pMyPal++; 
			pDDPal[index].peGreen = *pMyPal++; 
			pDDPal[index].peBlue = *pMyPal++; 
		} 

		if (DD.lpDirect3D!=NULL)	DD.lpDirect3D->SetPalette(&DD,(UByte*)Palette);
		else
		{
			UWord* plup=(UWord*)GetPaletteTable();
			UByte* palp=(UByte*)Palette;

			UWord redMask,greenMask,blueMask;
			SWord redShift1,greenShift1,blueShift1;
			SWord redShift2,greenShift2,blueShift2;

			GetColourInfo(	redMask,redShift1,redShift2,
							greenMask,greenShift1,greenShift2,
							blueMask,blueShift1,blueShift2);

			for (int j=0;j<direct_3d::MAX_PALS;j++)
				for (int i=255;i>=0;i--)
				{
					UWord red,green,blue;
					red=UWord(*palp++)&0xFF;
					green=UWord(*palp++)&0xFF;
					blue=UWord(*palp++)&0xFF;
					red=((red>>redShift2)&redMask);
					green=((green>>greenShift2)&greenMask);
					blue=((blue>>blueShift2)&blueMask);
					*plup++=(red<<redShift1)+(green<<greenShift1)+(blue<<blueShift1);
				}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		XX_CopyP2L
//Author		Andrew McRae
//Date			Tue 23 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Display::XX_CopyP2L(LogicalPtr	T, int W,int H)
{
	if (DD.ModeX)	return FALSE;

	RECT rect;
	DDBLTFX	ddbltfx;

	LogicalPtr	S;

	HRESULT ddrval;

	rect.top = (T - logicalscreenptr) / BytesPerScanLine;
	rect.left = ((T - logicalscreenptr) - (rect.top * BytesPerScanLine)) / BytesPerPixel;
	rect.right = rect.left + W;
	rect.bottom = rect.top + H;

	ddbltfx.dwSize = sizeof (DDBLTFX);

	if (NumberOfScreens == 2)
	{

		if (ScreenNumOnLogical)
			ddrval = DD.lpDDSPrimary->Blt(	&rect,
											DD.lpDDSBack,
											&rect,
											DDBLT_WAIT |
											DDBLT_KEYSRC,
											&ddbltfx);
		else
			ddrval = DD.lpDDSBack->Blt(	&rect,
										DD.lpDDSPrimary,
										&rect,
										DDBLT_WAIT |
										DDBLT_KEYSRC,
										&ddbltfx);

		if (ddrval == DD_OK)	return TRUE;

		// Direct Draw Blt Failed - So DIY

		if (ScreenNumOnLogical)
		{
			while (DD.lpDDSBack->Lock(	NULL,
										DD.lpddsd,
										DDLOCK_SURFACEMEMORYPTR |
										DDLOCK_WAIT,
										NULL) != DD_OK) {};

			S = (LogicalPtr)DD.lpddsd->lpSurface;

			DD.lpDDSBack->Unlock (DD.lpddsd->lpSurface );
		}	
		else
		{
			while (DD.lpDDSPrimary->Lock(	NULL,
											DD.lpddsd,
											DDLOCK_SURFACEMEMORYPTR |
											DDLOCK_WAIT,
											NULL) != DD_OK) {};

			S = (LogicalPtr)DD.lpddsd->lpSurface;

			DD.lpDDSPrimary->Unlock (DD.lpddsd->lpSurface );
		}

		S+=(T-logicalscreenptr);

		ULong	wd=1+(W+3)/4;
		ULong	bps=BytesPerScanLine;

		H++;
		while (--H!=0)
		{

			repmovsd(S,T,wd);
			S+=bps;
			T+=bps;
		}

	}
	else if (NumberOfScreens == 3)
	{

		if (ScreenNumOnLogical)
			ddrval = DD.lpDDSPrimary->Blt(	&rect,
											DD.lpDDSBack,
											&rect,
											DDBLT_WAIT |
											DDBLT_KEYSRC,
											&ddbltfx);
		else
			ddrval = DD.lpDDSBack2->Blt(	&rect,
											DD.lpDDSPrimary,
											&rect,
											DDBLT_WAIT |
											DDBLT_KEYSRC,
											&ddbltfx);

		if (ddrval == DD_OK)	return TRUE;

		// Direct Draw Blt Failed - So DIY

		if (ScreenNumOnLogical)
		{
			while (DD.lpDDSBack2->Lock(	NULL,
										DD.lpddsd,
										DDLOCK_SURFACEMEMORYPTR |
										DDLOCK_WAIT,
										NULL) != DD_OK) {};

			S = (LogicalPtr)DD.lpddsd->lpSurface;

			DD.lpDDSBack2->Unlock (DD.lpddsd->lpSurface );
		}	
		else
		{
			while (DD.lpDDSPrimary->Lock(	NULL,
											DD.lpddsd,
											DDLOCK_SURFACEMEMORYPTR |
											DDLOCK_WAIT,
											NULL) != DD_OK) {};

			S = (LogicalPtr)DD.lpddsd->lpSurface;

			DD.lpDDSPrimary->Unlock (DD.lpddsd->lpSurface );
		}

		S+=(T-logicalscreenptr);

		ULong	wd=1+(W+3)/4;
		ULong	bps=BytesPerScanLine;

		H++;
		while (--H!=0)
		{
			ULong*	S1=(ULong*) S;
			ULong*	T1=(ULong*) T;
		 	for (ULong W1=wd;--W1!=0;)
	 			*T1++=*S1++;
			S+=bps;
			T+=bps;
		}
	}
	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		XX_PlotPixelNoClip
//Author		Andrew McRae
//Date			Tue 23 Jul 1996
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
	if (DD.ModeX)	return FALSE;

	ULong		old_col;
	LogicalPtr	screenaddr;
	SLong		yoffset, xoffset;

	switch (NumberOfScreens)
	{
	case 0:
		while (DD.lpDDSPrimary->Lock(	NULL,
										DD.lpddsd,
										DDLOCK_SURFACEMEMORYPTR |
										DDLOCK_WAIT,
										NULL) != DD_OK) {};

		screenaddr = (LogicalPtr)DD.lpddsd->lpSurface;

		yoffset = BytesPerScanLine * y;
		xoffset = BytesPerPixel * x;

		screenaddr += xoffset + yoffset;
	
		old_col = (ULong)	(*screenaddr);
		*screenaddr = thecol;

		DD.lpDDSPrimary->Unlock (DD.lpddsd->lpSurface );

		return(old_col);

	case 1:
		while (DD.lpDDSPrimary->Lock(	NULL,
										DD.lpddsd,
										DDLOCK_SURFACEMEMORYPTR |
										DDLOCK_WAIT,
										NULL) != DD_OK) {};

		screenaddr = (LogicalPtr)DD.lpddsd->lpSurface;

		yoffset = BytesPerScanLine * y;
		xoffset = BytesPerPixel * x;

		screenaddr += xoffset + yoffset;
	
		old_col = (ULong)	(*screenaddr);

		*screenaddr = thecol;

		DD.lpDDSPrimary->Unlock (DD.lpddsd->lpSurface );

		return(old_col);

	case 2:
	{
		while (DD.lpDDSPrimary->Lock(	NULL,
										DD.lpddsd,
										DDLOCK_SURFACEMEMORYPTR |
										DDLOCK_WAIT,
										NULL) != DD_OK) {};

		screenaddr = (LogicalPtr)DD.lpddsd->lpSurface;

		yoffset = BytesPerScanLine * y;
		xoffset = BytesPerPixel * x;

		screenaddr += xoffset + yoffset;
	
		if (BytesPerPixel==1)
		{
			old_col = (ULong)	(*screenaddr);
			*screenaddr = thecol;
		}
		else
		if (BytesPerPixel==2)
		{
			UWord	tempy=*(UWord*)screenaddr;
			old_col=(ULong)tempy>>8;

			tempy = (tempy&0x00FF)+(thecol<<8);

			*(UWord*)screenaddr = tempy;
		}
		else
		{
			ULong	tempy=*(ULong*)screenaddr;
			old_col=((ULong)tempy&0x00ff00)>>8;

			tempy = (tempy&0xffff00FF)+(thecol<<8);

			*(ULong*)screenaddr = tempy;
		}



		DD.lpDDSPrimary->Unlock (DD.lpddsd->lpSurface );

		return(old_col);
	}
	case 3:
		while (DD.Screens[DD.DDOnScreen]->Lock(	NULL,
												DD.lpddsd,
												DDLOCK_SURFACEMEMORYPTR |
												DDLOCK_WAIT,
												NULL) != DD_OK) {};

		screenaddr = (LogicalPtr)DD.lpddsd->lpSurface;

		yoffset = BytesPerScanLine * y;
		xoffset = BytesPerPixel * x;

		screenaddr += xoffset + yoffset;
	
		old_col = (ULong)	(*screenaddr);

		*screenaddr = thecol;

		DD.Screens[DD.DDOnScreen]->Unlock (DD.lpddsd->lpSurface );

		return(old_col);
	}
	return 0;
}


extern void DDErrorCodes(char*,int,HRESULT);

//-----------------------------------------------------------------------------
// Procedure    
// Author       Paul
// Date         20/03/98
//-----------------------------------------------------------------------------
ULong Display::SetDirectDrawMode (InitDisplayDef& Mode)
{
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[6]='a';
    HRESULT         ddrval;
    DDSCAPS         ddscaps;

	bool fullScreen=DD.lpDirectDD->isFullScreen();
	int	curmode=DD.DDCurrMode;

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[6]='b';

	RECT rect;
	if (!fullScreen)	::GetWindowRect(DD.hWnd,&rect);
	else{
		rect.top=0;rect.left=0;
		rect.bottom=DD.DDModes[curmode].height;
		rect.right=DD.DDModes[curmode].width;
	}
	int	window_width=rect.right-rect.left;
	int window_height=rect.bottom-rect.top;
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[6]='c';

	// Select Single or Double Screens
	// If hardware is bank switched choose Single screen mode

	if ((DD.lpDDDriverCaps->dwCaps & DDCAPS_BANKSWITCHED)||!fullScreen)	
			NumberOfScreens=1;
	else	NumberOfScreens=2;

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[6]='d';

	if (fullScreen){
    	ddrval=DD.lpDD2->SetCooperativeLevel(DD.hWndApp,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
    	ddrval=DD.lpDD2->SetCooperativeLevel(DD.hWndApp,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
	    ddrval=DD.lpDD2->SetDisplayMode(DD.DDModes[curmode].width,DD.DDModes[curmode].height,
										DD.DDModes[curmode].colourdepth,0,0);
	}
	else{
		NumberOfScreens=1;
    	ddrval=DD.lpDD2->SetCooperativeLevel(DD.hWndApp,DDSCL_NORMAL);
    	ddrval=DD.lpDD2->SetCooperativeLevel(DD.hWndApp,DDSCL_NORMAL);
	}

    // Set Video Mode

	DD.ModeX = FALSE;

	if (DD.ModeX)	NumberOfScreens = 1;

	DD.lpddsd->dwSize = sizeof(DDSURFACEDESC);

	int d3dcapsrequired = (DD.lpDirect3D==NULL) ? 0 : DDSCAPS_3DDEVICE;

	switch (NumberOfScreens)
	{
	case 0:

	    // Create Primary Surface

		DD.lpddsd->dwFlags = DDSD_CAPS;

		DD.lpddsd->ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|
									DDSCAPS_VIDEOMEMORY|
									DDSCAPS_LOCALVIDMEM|
									d3dcapsrequired;
	    ddrval =
		DD.lpDD2->CreateSurface(DD.lpddsd,&DD.lpDDSPrimary,NULL);

	    if (ddrval!=DD_OK)	return 3;

		//directdraw_ClearSurface(DD.lpDDSPrimary);

		break;

	case 1:

	    // Create Primary Surface

	    DD.lpddsd->dwFlags = DDSD_CAPS;

	    DD.lpddsd->ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|
									DDSCAPS_VIDEOMEMORY|
									DDSCAPS_LOCALVIDMEM;
	    ddrval =
		DD.lpDD2->CreateSurface(DD.lpddsd,&DD.lpDDSPrimary,NULL);

		DDErrorCodes(__FILE__,__LINE__,ddrval);

	   // if (ddrval!=DD_OK)	return 3;

		//directdraw_ClearSurface(DD.lpDDSPrimary);

		if (d3dcapsrequired)
		{
			// Create 3d capeable backbuffer

	    	DD.lpddsd->dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;

			DD.lpddsd->ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|
										DDSCAPS_3DDEVICE|
										DDSCAPS_VIDEOMEMORY|
										DDSCAPS_LOCALVIDMEM;
		}else
		{
			// Create off screen surface - Use system memory

	    	DD.lpddsd->dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;

			DD.lpddsd->ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN |
										DDSCAPS_SYSTEMMEMORY;
		}

		DD.lpddsd->dwHeight =	window_height;	//DD.DDModes[DD.DDCurrMode].height;
		DD.lpddsd->dwWidth = 	window_width;	//DD.DDModes[DD.DDCurrMode].width;

	   	ddrval =
		DD.lpDD2->CreateSurface(DD.lpddsd,&DD.lpDDSBack,NULL);

		if (ddrval!=DD_OK)	return 4;

		break;

	case 2:

	    // Create Primary Surface
	    DD.lpddsd->dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		if (d3dcapsrequired)
		{
	    	DD.lpddsd->ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|
										DDSCAPS_FLIP|
										DDSCAPS_COMPLEX|
										DDSCAPS_3DDEVICE| 
										DDSCAPS_VIDEOMEMORY|
										DDSCAPS_LOCALVIDMEM;
		}else
		{
	    	DD.lpddsd->ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|
										DDSCAPS_FLIP|
										DDSCAPS_COMPLEX| 
										DDSCAPS_VIDEOMEMORY|
										DDSCAPS_LOCALVIDMEM;
		}

	    DD.lpddsd->dwBackBufferCount = 1;

    	ddrval =
		DD.lpDD2->CreateSurface(DD.lpddsd,&DD.lpDDSPrimary,NULL);

		if (ddrval!=DD_OK)	return 3;

		directdraw_ClearSurface(DD.lpDDSPrimary);

		// Attach a Back Surface

		if (d3dcapsrequired)
		{
	    	DD.lpddsd->ddsCaps.dwCaps = DDSCAPS_BACKBUFFER|
							  			DDSCAPS_3DDEVICE| 
										DDSCAPS_VIDEOMEMORY|
										DDSCAPS_LOCALVIDMEM;

		}else
		{
	    	DD.lpddsd->ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
		}

	    ddrval =
		DD.lpDDSPrimary->GetAttachedSurface(&DD.lpddsd->ddsCaps,&DD.lpDDSBack);

    	if (ddrval!=DD_OK)	return 4;

		break;

	case 3:

		// Create 3 surfaces
		// Cant use Primary with 2back buffers because we need ptrs to all 3 screens

	    // Create Primary Surface
	    DD.lpddsd->dwSize			= sizeof (DDSURFACEDESC);
	    DD.lpddsd->dwFlags 			= DDSD_CAPS;// | DDSD_BACKBUFFERCOUNT;
	    DD.lpddsd->ddsCaps.dwCaps 	= DDSCAPS_PRIMARYSURFACE;// | DDSCAPS_FLIP | DDSCAPS_FRONTBUFFER | DDSCAPS_COMPLEX;
	    DD.lpddsd->dwBackBufferCount= 0;//2;

    	ddrval =
		DD.lpDD2->CreateSurface(DD.lpddsd,&DD.lpDDSPrimary,NULL);

		if (ddrval!=DD_OK)	return 3;

		directdraw_ClearSurface(DD.lpDDSPrimary);

	    DD.lpddsd->dwFlags 			= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		DD.lpddsd->ddsCaps.dwCaps 	= DDSCAPS_OFFSCREENPLAIN;// | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		DD.lpddsd->dwHeight 		= DD.DDModes[DD.DDCurrMode].height;
		DD.lpddsd->dwWidth 			= DD.DDModes[DD.DDCurrMode].width;

	    ddrval =
		DD.lpDD2->CreateSurface(DD.lpddsd,&DD.lpDDSBack,NULL);

		if (ddrval!=DD_OK)	return 4;

	    DD.lpddsd->dwFlags 			= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		DD.lpddsd->ddsCaps.dwCaps 	= DDSCAPS_OFFSCREENPLAIN;
		DD.lpddsd->dwHeight 		= DD.DDModes[DD.DDCurrMode].height;
		DD.lpddsd->dwWidth 			= DD.DDModes[DD.DDCurrMode].width;
	    
		ddrval =
		DD.lpDD2->CreateSurface(DD.lpddsd,&DD.lpDDSBack2,NULL);

		if (ddrval!=DD_OK)	return 5;

		DD.Screens[1] = DD.lpDDSPrimary;
		DD.Screens[2] = DD.lpDDSBack;
		DD.Screens[3] = DD.lpDDSBack2;

		DD.DDOnScreen 		= 1;
		DD.DDSpareScreen 	= 2;
		DD.DDLogicalScreen 	= 3;

		break;
	}

	//do a lock/unlock to get the back buffer surface desc
	do
	{
		ddrval=
		DD.lpDDSBack->Lock(NULL,DD.lpddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
	}
	while (ddrval!=DD_OK);
	ddrval=DD.lpDDSBack->Unlock(DD.lpddsd->lpSurface);

	//Only attatch palette if doing SW 3D

	//create a new DD palette object here

	if (DD.PaletteBuffer==NULL)	DD.PaletteBuffer = new MYPALETTEENTRY [256];

	memset(DD.PaletteBuffer,0,256*sizeof(MYPALETTEENTRY));

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[6]='e';

	if (DD.lpDirect3D==NULL)
	{
//		#ifndef WINDOWED_PALETTE

//		DD.lpDD2->CreatePalette(DDPCAPS_8BIT|DDPCAPS_ALLOW256,
//		   						(LPPALETTEENTRY)DD.PaletteBuffer,
//		   						&DD.lpDDPal,
//								NULL);

//		#else

//		for (int x=0;x<256;x++)
//		{
//			DD.PaletteBuffer[x].peFlags = PC_NOCOLLAPSE|PC_RESERVED;
//			DD.PaletteBuffer[x].peRed = 0;
//			DD.PaletteBuffer[x].peGreen = 0;
//			DD.PaletteBuffer[x].peBlue = 0;
//		}

//		DD.lpDD2->CreatePalette(DDPCAPS_8BIT,
//		   						(LPPALETTEENTRY)DD.PaletteBuffer,
//		   						&DD.lpDDPal,
//								NULL);
//		#endif

//		if (NumberOfScreens!=3)
//			DD.lpDDSPrimary->SetPalette(DD.lpDDPal);
//		else
//		{
//			DD.Screens[DD.DDOnScreen]->SetPalette(DD.lpDDPal);
//			DD.Screens[DD.DDSpareScreen]->SetPalette(DD.lpDDPal);
//			DD.Screens[DD.DDLogicalScreen]->SetPalette(DD.lpDDPal);
//		}
	}
	else DD.lpDirect3D->SelectDriver(&DD);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[6]='f';

    return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillSurfaces
//Author		Andrew McRae
//Date			Tue 26 Nov 1996
//
//Description	Release all opened surfaces
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Display::KillSurfaces ()
{
	HRESULT	dderrval;

	//Close down direct 3D bits if active

	if (DD.lpDirect3D!=NULL)									//PD 26Feb97
	{
		delete (DD.lpDirect3D);
		DD.lpDirect3D=NULL;
	}

	//clear the screens before deleing them to stop this frame of 3d being
	//shown on the next time into the 3d.

//Causes full screen wipe on map screen								  //JIM 14/06/99
//TEMPCODE JIM 14/06/99 	directdraw_ClearSurface(DD.lpDDSPrimary);


	switch (NumberOfScreens)
	{
		case 1:
		RELEASE(DD.lpDDSPrimary,dderrval);
		RELEASE(DD.lpDDSBack,dderrval);
		RELEASE(DD.lpDDSBack2,dderrval);
		break;

		case 2:
		directdraw_ClearSurface(DD.lpDDSPrimary);
		RELEASE(DD.lpDDSPrimary,dderrval);
		DD.lpDDSBack=NULL;
		DD.lpDDSBack2=NULL;
		break;

		default:
		OutputDebugString("Divide by cucumber error\n");
		break;
	}

	//Discard palette object (if created)

	if (DD.lpDDPal!=NULL)	{RELEASE(DD.lpDDPal,dderrval);}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DirectDraw_MemScreen
//Author		Andrew McRae
//Date			Tue 23 Jul 1996
//
//Description	Direct Draw version of MemScreen (as in hardinit)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::DirectDraw_MemScreen (ScreenPages dpg)
{
	switch (dpg)
	{
	case SCREEN_LOGICAL:
		while (DD.Screens[DD.DDLogicalScreen]->Lock(NULL,
					   								DD.lpddsd,
					   								00000001L,
					   								NULL) != DD_OK) {};

		logicalscreenptr = (LogicalPtr)DD.lpddsd->lpSurface;

		DD.Screens[DD.DDLogicalScreen]->Unlock (DD.lpddsd->lpSurface );
	break;
	case SCREEN_SPARE:
		while (DD.Screens[DD.DDSpareScreen]->Lock(	NULL,
					   								DD.lpddsd,
					   								00000001L,
					   								NULL) != DD_OK) {};

		logicalscreenptr = (LogicalPtr)DD.lpddsd->lpSurface;

		DD.Screens[DD.DDSpareScreen]->Unlock (DD.lpddsd->lpSurface );
	break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		XX_ResetGraphicsMode
//Author		Paul.   
//Date			Fri 28 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Display::XX_ResetGraphicsMode()
{
	if (NumberOfScreens>1)
		logicalscreenptr=NULL;	//block deletion

	// do something here ... may be not

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChangeBytesPerScanLine
//Author		Paul.   
//Date			Fri 28 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Display::ChangeBytesPerScanLine ()
{
	BytesPerScanLine = DD.lpddsd->lPitch;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Body2Screen
//Author		Paul.   
//Date			Wed 25 Nov 1998
//------------------------------------------------------------------------------
void Display::Body2Screen(DoPointStruc& a)
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->Body2Screen(a);}

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
void	Display::BackupLogicalPtr()
{
	bupLogicalScreenPtr=logicalscreenptr;	
}

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
void	Display::ResetLogicalPtr()
{
	WindowMoved (bupLogicalScreenPtr, logicalscreenptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmokedGlassBox
//Author		Paul    
//Date			Sun 7 Jun 1998
//------------------------------------------------------------------------------
void Display::SmokedGlassBox(SWord a,SWord b,SWord c,SWord d,ULong e)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->SmokedGlassBox(&DD,a,b,c,d,e);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HWRegisterPal
//Author		Paul.   
//Date			Wed 21 Oct 1998
//------------------------------------------------------------------------------
void Display::HWRegisterPal(UByte* src,ULong length)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->RegisterPalette(&DD,src,length);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceTQ
//Author		Paul.   
//Date			Thu 29 Oct 1998
//------------------------------------------------------------------------------
SWord Display::ForceTQ(SWord a)
{
 	if (DD.lpDirect3D!=NULL) return DD.lpDirect3D->ForceTQ(a);
	return a;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeTexture
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void	Display::FreeTexture(const HTEXT& a)
{if (DD.lpDirect3D) DD.lpDirect3D->FreeTexture(a);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeTexture
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void	Display::FreeTextures()
{if (DD.lpDirect3D) DD.lpDirect3D->FreeTextures();}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateTexture
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
HTEXT	Display::AllocateTexture(UByte a)
{if (DD.lpDirect3D) return DD.lpDirect3D->AllocateTexture(a);return HTEXTNULL;}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTextureScales
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void Display::GetTextureScales(SLong& a,SLong& b,SLong& c,SLong& d,SLong& e,SLong& f)
{
	if (DD.lpDirect3D) 	DD.lpDirect3D->GetTextureScales(a,b,c,d,e,f);
	else				a=b=c=d=e=f=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTileToDDSurface
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void Display::RenderTileToDDSurface(UByte* a,const HTEXT& b)
{if (DD.lpDirect3D) DD.lpDirect3D->RenderTileToDDSurface(&DD,a,b);}

void Display::GetSurfaceDimensions(SLong& a,SLong& b)
{if (DD.lpDirectDD!=NULL) DD.lpDirectDD->GetSurfaceDimensions(&DD,a,b);}

void Display::PutC(ImageMapDesc* a,DoPointStruc* b,bool fRefresh)
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->PutC(&DD,a,b,fRefresh);}

void Display::PutA(ImageMapDesc* a,DoPointStruc* b)
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->PutA(&DD,a,b);}

void Display::D2DLine(UWord a,UWord b,UWord c,UWord d)
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->D2DLine(&DD,a,b,c,d);}

void Display::SetFontColour(ULong a)
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->SetFontColour(a);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PeripheralBlob
//Author		Paul.   
//Date			Mon 23 Nov 1998
//------------------------------------------------------------------------------
void Display::PeripheralBlob(Float* a,Float* b,Float* c,UByte d,SLong e)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->PeripheralBlob(a,b,c,d,e);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMipMap
//Author		Paul.   
//Date			Tue 24 Nov 1998
//------------------------------------------------------------------------------
bool Display::SetMipMap(bool a)
{
	if (DD.lpDirect3D!=NULL) return DD.lpDirect3D->SetMipMap(a);
	return a;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSunPos
//Author		Paul.   
//Date			Fri 27 Nov 1998
//------------------------------------------------------------------------------
void Display::SetSunPos(DoPointStruc& a){if (DD.lpDirect3D!=NULL) DD.lpDirect3D->SetSunPos(a);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetEdgeTest
//Author		Paul.   
//Date			Thu 10 Dec 1998
//------------------------------------------------------------------------------
bool Display::SetEdgeTest(bool a)
{
	if (DD.lpDirect3D!=NULL)
		return DD.lpDirect3D->SetEdgeTest(a);

	return a;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GammaCorr
//Author		Paul.   
//Date			Wed 23 Dec 1998
//------------------------------------------------------------------------------
void Display::GammaCorr(UByte& r,UByte& g,UByte& b)
{
	if (DD.lpDirect3D!=NULL)
		DD.lpDirect3D->GammaCorr(r,g,b);
}

void Display::CaptureScreen() {if (DD.lpDirect3D) DD.lpDirect3D->CaptureScreen(&DD);}
void Display::SaveVideoBuffer() {if (DD.lpDirect3D) DD.lpDirect3D->SaveVideoBuffer(&DD);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HardPoly
//Author		Paul.   
//Date			Fri 7 Feb 1997
//
//Description	
//
//Inputs		
//
//
//Returns	
//------------------------------------------------------------------------------
Bool	Display::HardPoly(LPPOLYTYPE lpPolyType)
{
	if (DD.lpDirect3D==NULL)	return (FALSE);

	switch (lpPolyType->ptType)
	{
		default:
		return (FALSE);

		case POLYTYPE::PT_PlainColour:
		case POLYTYPE::PT_MaskedImagem:
		case POLYTYPE::PT_PlainImagem:
		case POLYTYPE::PT_GColour:
		case POLYTYPE::PT_HighLand:
		case POLYTYPE::PT_FakeFog:
		DD.lpDirect3D->AddPoly(&DD,lpPolyType);
		break;
	}
	return (TRUE);
}
void Display::PushViewData() {if (DD.lpDirect3D) DD.lpDirect3D->PushViewData(&DD);}
void Display::PopViewData() {if (DD.lpDirect3D) DD.lpDirect3D->PopViewData(&DD);}
void Display::Set3DWin(SLong x,SLong y,SLong w,SLong h) {if (DD.lpDirect3D) DD.lpDirect3D->Set3DWin(&DD,x,y,w,h);}

bool Display::ScanForBottomPixelsOfText(SWord a,SWord b,SWord c)
{
 	if (DD.lpDirect3D)
		return DD.lpDirect3D->ScanForBottomPixelsOfText(&DD,a,b,c);
	return true;
}
void Display::PushPull(UByte a)
{if (DD.lpDirect3D) DD.lpDirect3D->PushPull(a);}

void	Display::MakePaletteFadeTable(UByte* a,UWord* b,UByte c,UByte d,UByte e)
{
 	if (DD.lpDirectDD)	DD.lpDirectDD->MakePaletteFadeTable(&DD,a,b,c,d,e);
}

void Display::MakeColourRangeFadeTable(UWord* a,UByte b,UByte c,UByte d,UByte e,UByte f,UByte g)
{
	if (DD.lpDirectDD)
		DD.lpDirectDD->MakeColourRangeFadeTable(&DD,a,b,c,d,e,f,g);
}

void Display::LockScr(ROWANSURFACEDESC* a)
{
	if (DD.lpDirectDD) DD.lpDirectDD->LockScr(&DD,a);
}
void Display::UnlockScr(ROWANSURFACEDESC* a)
{
	if (DD.lpDirectDD) DD.lpDirectDD->UnlockScr(&DD,a);
}

void Display::GetColourInfo(UWord& redMask,SWord& redShift1,SWord& redShift2,
							UWord& greenMask,SWord& greenShift1,SWord& greenShift2,
							UWord& blueMask,SWord& blueShift1,SWord& blueShift2)
{
	if (DD.lpDirectDD) DD.lpDirectDD->GetColourInfo(&DD,
										redMask,redShift1,redShift2,
										greenMask,greenShift1,greenShift2,
										blueMask,blueShift1,blueShift2);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PutLine
//Author		Paul.   
//Date			Fri 26 Mar 1999
//------------------------------------------------------------------------------
void Display::PutLine(SWord a,SWord b,SWord c,SWord d,Colour e)
{
 	if (DD.lpDirect3D==NULL)
		return;
	DD.lpDirect3D->PutLine(&DD,a,b,c,d,e);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushAll
//Author		Paul.   
//Date			Wed 28 Oct 1998
//------------------------------------------------------------------------------
void Display::FlushAll(Bool f)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->FlushAll(&DD,f);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcItemFog
//Author		Paul.   
//Date			Wed 9 Sep 1998
//------------------------------------------------------------------------------
void Display::CalcItemFog(bool a,Float& b,Float& c,Float& d)
{
	if (DD.lpDirect3D!=NULL)
		DD.lpDirect3D->CalcItemFog(a,b,c,d);
}

bool  Display::SetTranspFade(bool a)
{
	if (DD.lpDirect3D!=NULL) 
	{
		return DD.lpDirect3D->SetTranspFade(a);
	}
	return a;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewTile
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void Display::NewTile(SLong z,DoPointStruc* a,SLong b,UByte* c,SLong d)
{
	if (DD.lpDirect3D) DD.lpDirect3D->NewTile(&DD,z,a,b,c,d);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CNewTile
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void Display::CNewTile(SLong z,DoPointStruc* a,SLong b,UByte* c,SLong d)
{
 	if (DD.lpDirect3D) DD.lpDirect3D->CNewTile(&DD,z,a,b,c,d);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestAsyncBlt
//Author		Paul.   
//Date			Tue 21 Jul 1998
//
//------------------------------------------------------------------------------
bool	Display::TestAsyncBlt()
{
	if (DD.lpDirect3D) return DD.lpDirect3D->TestAsyncBlt();
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginTextureScroll
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void Display::BeginTextureScroll(const SWord a,void* b,void* c)
{
	if (DD.lpDirect3D) DD.lpDirect3D->BeginTextureScroll(&DD,a,b,c);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WaitTextureScrollComplete
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void Display::WaitTextureScrollComplete(const SWord a)
{
	if (DD.lpDirect3D) DD.lpDirect3D->WaitTextureScrollComplete(&DD,a);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PartialTextureUpload
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void Display::PartialTextureUpload(const SWord a,void* b,void* c)
{
 	if (DD.lpDirect3D) DD.lpDirect3D->PartialTextureUpload(&DD,a,b,c);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShowLoaderArt
//Author		Paul    
//Date			Sat 20 Feb 1999
//------------------------------------------------------------------------------
void Display::ShowLoaderArt(void* pArt)
{
	if (DD.lpDirect3D) DD.lpDirect3D->ShowLoaderArt(&DD,pArt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateLandTBuffers
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
void Display::CreateLandTBuffers()
{
	if (DD.lpDirect3D)	DD.lpDirect3D->CreateLandTBuffers(&DD);
}

void*	Display::GetLandBufferPtr(SWord a)
{
	if (!DD.lpDirect3D)
		return NULL;
	return DD.lpDirect3D->GetLandBufferPtr(&DD,a);
}
void*	Display::GetLandPalLookup()
{
	if (!DD.lpDirect3D)
		return NULL;

	return DD.lpDirect3D->GetLandPalLookup(&DD);
}
void	Display::SetLandPalLookup(UByte* a)
{
	if (!DD.lpDirect3D)
		return;

	DD.lpDirect3D->SetLandPalLookup(&DD,a);
}
SWord	Display::GetLandBpp()
{
	if (!DD.lpDirect3D)
		return NULL;

	return DD.lpDirect3D->GetLandBpp(&DD);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAspectRatio
//Author		Paul.   
//Date			Wed 1 Jul 1998
//------------------------------------------------------------------------------
void Display::SetAspectRatio(Float ar,Float fov)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->SetAspectRatio(ar,fov);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushLandDraw
//Author		Dallas  
//Date			Wed 1 Jul 1998
//------------------------------------------------------------------------------
void Display::FlushLandDraw()
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->FlushLandscapeBuffers(&DD);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CLEB
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void Display::CLEB()
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->CreateLandExecuteBuffer();
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTile
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void Display::AddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->AddTileVertices(&DD,a,aa,b,c,d);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTile
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void Display::CAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->CAddTileVertices(&DD,a,aa,b,c,d);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NearAddTile
//Author		Paul    
//Date			Sun 21 Jun 1998
//------------------------------------------------------------------------------
void Display::NearAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d,ULong e)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->NearAddTileVertices(&DD,a,aa,b,c,d,e);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CNearAddTile
//Author		Paul.   
//Date			Wed 24 Jun 1998
//------------------------------------------------------------------------------
void Display::CNearAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d,ULong e)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->CNearAddTileVertices(&DD,a,aa,b,c,d,e);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CNearAddTileX
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Display::CNearAddTileX(ULong a,ULong b,DoPointStruc* c,ULong d,UByte*& e,const HTEXT& f,UWord flag)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->CNearAddTileVerticesX(&DD,a,b,c,d,e,f,flag);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NearAddTileX
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Display::NearAddTileX(ULong a,ULong b,DoPointStruc* c,ULong d,UByte*& e,const HTEXT& f,UWord flag)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->NearAddTileVerticesX(&DD,a,b,c,d,e,f,flag);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NearAddDitherX
//Author		Paul.   
//Date			Tue 1 Dec 1998
//------------------------------------------------------------------------------
void	Display::NearAddDitherX(ULong a,ULong b,DoPointStruc* c,ULong d,UByte*& e)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->NearAddTileDitherX(&DD,a,b,c,d,e);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoBeginFan
//Author		Paul.   
//Date			Tue 2 Jun 1998
//------------------------------------------------------------------------------
void Display::BeginFan(ULong hTexture)
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->BeginFan(hTexture);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoBeginFan
//Author		Paul.   
//Date			Tue 2 Jun 1998
//------------------------------------------------------------------------------
void Display::BeginFan(ImageMapDesc* pImage)
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->BeginFan(&DD,pImage);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoAddFanPoint
//Author		Paul.   
//Date			Tue 2 Jun 1998
//------------------------------------------------------------------------------
void Display::AddFanPoint(DoPointStruc* pdp,SLong vCnt,UByte*& pData)
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->AddFanPoint(&DD,pdp,vCnt,pData);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UploadLandTexture
//Author		Paul.   
//Date			Mon 18 May 1998
//------------------------------------------------------------------------------
void Display::UploadLandTexture(ULong hTexture,ImageMapDesc* lpImage)
{
 	if (DD.lpDirect3D!=NULL)
		DD.lpDirect3D->UploadLandTexture(&DD,hTexture,lpImage);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetClipState
//Author		Paul.   
//Date			Wed 29 Apr 1998
//------------------------------------------------------------------------------
bool Display::SetClipState(bool newState)
{if (DD.lpDirect3D!=NULL) return DD.lpDirect3D->SetClipState(newState);
return newState;}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseTextures
//Author		Paul.   
//Date			Tue 21 Apr 1998
//------------------------------------------------------------------------------
void Display::ReleaseTextures()
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->ReleaseTextures();}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTextureQuality
//Author		Paul.   
//Date			Mon 20 Apr 1998
//------------------------------------------------------------------------------
void Display::SetTextureQuality(bool b)
{if (DD.lpDirect3D!=NULL) DD.lpDirect3D->SetTextureQuality(&DD,b);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetRangeFog
//Author		Paul.   
//Date			Wed 8 Apr 1998
//------------------------------------------------------------------------------
bool Display::SetRangeFog(bool b)
{
	if (DD.lpDirect3D!=NULL) return DD.lpDirect3D->SetRangeFog(b);
	return b;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoGetHorizonColour
//Author		Paul.   
//Date			Mon 6 Apr 1998
//------------------------------------------------------------------------------
void Display::GetHorizonColour(UByte& a,UByte& b,UByte& c)
{
	a=DD.hcRed;
	b=DD.hcGreen;
	c=DD.hcBlue;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetHorizonColour
//Author		Paul.   
//Date			Mon 6 Apr 1998
//------------------------------------------------------------------------------
void Display::SetHorizonColour(UByte a,UByte b,UByte c)
{
	DD.hcRed=a;
	DD.hcGreen=b;
	DD.hcBlue=c;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetShadeVals
//Author		Paul.   
//Date			Wed 1 Apr 1998
//------------------------------------------------------------------------------
void Display::SetShadeVals(SLong nr,SLong ng,SLong nb,SLong er,SLong eg,SLong eb)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->SetShadeVals(nr,ng,nb,er,eg,eb);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoSetLShade
//Author		Paul.   
//Date			Wed 1 Apr 1998
//------------------------------------------------------------------------------
bool Display::SetLShade(bool b)
{
	if (DD.lpDirect3D!=NULL) return DD.lpDirect3D->SetLShade(b);
	return b;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGlobalAlpha
//Author		Paul.   
//Date			Fri 27 Mar 1998
//------------------------------------------------------------------------------
UByte Display::SetGlobalAlpha(UByte a)
{
	if (DD.lpDirect3D!=NULL) return DD.lpDirect3D->SetGlobalAlpha(a);
	return a;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceRender
//Author		Paul.   
//Date			Tue 24 Mar 1998
//------------------------------------------------------------------------------
void Display::ForceRender()
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->ForceRender(&DD);
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
void Display::DomeHorizon(void* lpData,void* lpPolys)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFogState
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
void Display::SetFogState(Bool bFogState)
{
	if (DD.lpDirect3D==NULL)	return;

	DD.lpDirect3D->SetFogState(bFogState);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFadeValue
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
void Display::SetFadeValue(UByte newValue)
{
	if (DD.lpDirect3D==NULL)	return;

 	DD.lpDirect3D->SetFadeValue(newValue);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnableBackClip
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
Bool Display::EnableBackClip(Bool bFlag)
{
	if (DD.lpDirect3D==NULL)	return (bFlag);

	return (DD.lpDirect3D->EnableBackClip(bFlag));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFade
//Author		Paul.   
//Date			Thu 5 Jun 1997
//
//Description	tCol = colour index into palette	
//				step = current stage of the fade 0(no fade)...31(full fade)
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Display::SetFade(Colour tCol,SLong step,TwoDeeEffect tdfx)
{
	if (DD.lpDirect3D==NULL)	return;
	
	DD.lpDirect3D->SetFade(tCol,step,tdfx);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModeSupported
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
Bool	Display::ModeSupported(ScreenRez* lpSRez)
{
	return (DD.lpDirectDD->ModeSupported(lpSRez));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DriverIsCapable
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
Bool	Display::DriverIsCapable(SWord drvno)
{
	return (DD.lpDirectDD->DriverIsCapable(drvno));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NameNumberedDriver
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
UByte*	Display::NameNumberedDriver(SWord driverno)
{
	if (driverno==-1)	return (NULL);

	return (DD.lpDirectDD->NameNumberedDriver(driverno));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CountDrivers
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
SWord Display::CountDrivers()
{
 	return (DD.lpDirectDD->CountDrivers());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HardLine
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
Bool Display::HardLine(LPLINETYPE lpLineType)
{
	if (DD.lpDirect3D==NULL)	return (FALSE);

	DD.lpDirect3D->AddPlainLine(&DD,lpLineType);

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HardPoint
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
Bool Display::HardPoint(LPPOINTTYPE lpPointType)
{
	if (DD.lpDirect3D==NULL)	return (FALSE);

	DD.lpDirect3D->AddPlainPoint(&DD,lpPointType);

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetViewParams
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
void Display::SetViewParams(ANGLES a,Window* w,ViewPoint*)
{
	if (DD.lpDirect3D==NULL)	return;

	DD.lpDirect3D->SetViewParams(a,w,&DD);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim::PlainRectangleFill
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Mon 3 Jul 1995
//Description	
//Externals
//------------------------------------------------------------------------------
Bool Display::HardPlainRectFill(Window* win,SWord X,SWord Y,SWord W,SWord H)
{
	if (DD.lpDirect3D==NULL)	return (FALSE);

	LogicalPtr	scradr,
				scanlineaddr;

	int		i,j;

	ULong	tColour;

	//Clip the rectangle to the screen

	if((Y+H) <= win->PhysicalMinY)					return (TRUE);
	if(Y >= win->PhysicalMinY+win->PhysicalHeight)	return (TRUE);
	if((X+W) <= win->PhysicalMinX)					return (TRUE);
	if(X >= win->PhysicalMinX+win->PhysicalWidth)	return (TRUE);

	if(Y < win->PhysicalMinY)
	{
		H -=	(win->PhysicalMinY-Y);
		Y = 	win->PhysicalMinY;
	}

	if((Y+H) > (win->PhysicalMinY+win->PhysicalHeight))
	{
		H -=	((Y+H)-(win->PhysicalMinY+win->PhysicalHeight));
	}

	if(X < win->PhysicalMinX)
	{
		W -= (win->PhysicalMinX-X);
		X = 	win->PhysicalMinX;
	}

	if((X+W) > (win->PhysicalMinX+win->PhysicalWidth))
	{
		W -= ((X+W)-(win->PhysicalMinX+win->PhysicalWidth));
	}

	//Calculate the screen address of the top left corner of the rectangle

//DEAD 	LockBackScreen (FALSE);										//PD 11Jul97

	scradr = win->logicalscreenptr +
			 win->BytesPerScanLine * Y +
			 win->BytesPerPixel * X;

	ULong	red,green,blue;

	red = DD.PaletteBuffer[win->colour].peRed;
	green = DD.PaletteBuffer[win->colour].peGreen;
	blue = DD.PaletteBuffer[win->colour].peBlue;

	tColour = 	(red>>(8-RedBits))		<<RedShift;				//DAW 16Oct97
	tColour += 	(green>>(8-GreenBits))	<<GreenShift;			//DAW 16Oct97
	tColour += 	(blue>>(8-BlueBits))	<<BlueShift;			//DAW 16Oct97

	ULong	lcolour=((ULong)0x00010001)*tColour;

	for(i=H;i>0;i--)
	{
		scanlineaddr = scradr;
		j=W-3;
		if	((ULong )scanlineaddr &0x00000003)
		{
			*(UWord*) (scanlineaddr) = tColour;
			scanlineaddr+=2;
			j--;
			if	((ULong )scanlineaddr &0x00000003)
			{
				*(UWord*) (scanlineaddr) = tColour;
				scanlineaddr+=2;
				j--;
				if	((ULong )scanlineaddr &0x00000003)
				{
					*(UWord*) (scanlineaddr) = tColour;
					scanlineaddr+=2;
					j--;
		}	}	}
		scradr += BytesPerScanLine;
		while(j>0)
		{
			*(ULong *)scanlineaddr = lcolour;
			scanlineaddr+=4;
			j-=2;
		}
		for(j=j+3;j>0;scanlineaddr+=2,j--)
			*(UWord*) (scanlineaddr) = tColour;
	}

//DEAD 	UnLockBackScreen ();										//PD 11Jul97

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetZUpdate
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
Bool Display::SetZUpdate(Bool flag)
{
	if (DD.lpDirect3D==NULL)	return (flag);

	return (DD.lpDirect3D->SetZUpdate(&DD,flag));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPlayerTextures
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
Bool Display::SetPlayerTextures(Bool flag)
{
	if (DD.lpDirect3D==NULL)	return (flag);

	return (DD.lpDirect3D->SetPlayerTextures(&DD,flag));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetImageMapTablePtr
//Author		Paul.   
//Date			Mon 10 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void Display::SetImageMapTablePtr(SLong*)
//{
//
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Hardware3D
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
Bool Display::Hardware3D()
{
	if (DD.lpDirect3D==NULL)	return (FALSE);

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMatrices
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
Bool Display::SetMatrices(SLong viewrange,ANGLES viewang)
{
	if (DD.lpDirect3D==NULL)	return (FALSE);

	DD.lpDirect3D->SetMatrices(&DD,viewrange,viewang);

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFog
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
void Display::SetFog(UByte r,UByte g,UByte b)
{
	if (DD.lpDirect3D==NULL)	return;

	DD.lpDirect3D->SetFog(r,g,b);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFog
//Author		Paul.   
//Date			Fri 23 Oct 1998
//------------------------------------------------------------------------------
void	Display::SetFog(UByte r,UByte g,UByte b,SLong s,SLong e)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->SetFog(r,g,b,s,e);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFog
//Author		Paul.   
//Date			Fri 23 Oct 1998
//------------------------------------------------------------------------------
void	Display::GetFog(UByte& r,UByte& g,UByte& b,SLong& s,SLong& e)
{
	if (DD.lpDirect3D!=NULL) DD.lpDirect3D->GetFog(r,g,b,s,e);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginScene
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
void Display::BeginScene()
{
	if (DD.lpDirect3D==NULL)	return;

	DD.lpDirect3D->BeginScene(&DD);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EndScene
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
void Display::EndScene()
{
	if (DD.lpDirect3D==NULL)	return;

	DD.lpDirect3D->EndScene(&DD);
}
void Display::End3DScene()
{
	if (DD.lpDirect3D==NULL)	return;

	DD.lpDirect3D->End3DScene(&DD);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HCls
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
void Display::HCls(Bool bFlag)
{
 	if (DD.lpDirect3D==NULL)	return;

	DD.lpDirect3D->ClearViewport(&DD,bFlag);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LockBackScreen
//Author		Andy McMaster
//Date			Tue 6 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEAD void	Display::LockBackScreen(Bool winmov,UByte low, UByte high)//AMM 06May97
//DEAD {															//AMM 01May97
//DEAD 	if(locklevel>=low && locklevel<=high)					//AMM 01May97
//DEAD 	{														//AMM 01May97
//DEAD 		if(!locked)											//AMM 01May97
//DEAD 		{													//AMM 01May97
//DEAD 			LockBackScreen(winmov);							//AMM 01May97
//DEAD 			locked=TRUE;									//AMM 01May97
//DEAD 		}													//AMM 01May97
//DEAD 	}														//AMM 01May97
//DEAD }															//AMM 01May97

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLockBackScreen
//Author		Andy McMaster
//Date			Tue 6 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEAD void	Display::UnLockBackScreen(UByte low, UByte high)	//AMM 06May97
//DEAD {															//AMM 01May97
//DEAD 	if(locklevel>=low && locklevel<=high)					//AMM 01May97
//DEAD 	{														//AMM 01May97
//DEAD 		if(locked)											//AMM 01May97
//DEAD 		{													//AMM 01May97
//DEAD 			UnLockBackScreen();								//AMM 01May97
//DEAD 			locked=FALSE;									//AMM 01May97
//DEAD 		}													//AMM 01May97
//DEAD 	}														//AMM 01May97
//DEAD }			

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestHW3D
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
void Display::TestHW3D(Window* w)
{
 	if (DD.lpDirect3D==NULL)	return;

	DD.lpDirect3D->TestHW3D(&DD,w);
}







