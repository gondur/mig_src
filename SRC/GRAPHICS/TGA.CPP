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
//Filename       tga.cpp
//System         
//Author         Paul.   
//Date           Mon 21 Apr 1997
//Description    
//------------------------------------------------------------------------------
	#include	"dosdefs.h"
	#include	<stdlib.h>
	#include	<stdio.h>
	#include	<memory.h>
	#include	<string.h>
	#define		F_GRAFIX
	#include	"display.h"
	#include	<fstream.h>
	#include	"fileman.h"
	#include	"tga.h"

#include "lbm.h"

//const int DEFAULT_LBM 	= 8;
const int RLCompressed  = FALSE;
const int RLCount 		= 0;
const int RLMode  		= RLRUN;

extern UWord screenshotnum;

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
void Graphic::ScreenShot16()
{
//	#pragma message (__HERE__"VidRAM read outside of lock")

	TGA		screenShot;
	ULong	packedlength;

	screenShot.redScale 	= RedShift;							//PD 24Oct97
	screenShot.redMask 		= (1<<RedBits)-1;					//PD 24Oct97
	screenShot.redBits		= RedBits;							//DAW 24Oct97

	screenShot.greenScale 	= GreenShift;						//PD 24Oct97
	screenShot.greenMask	= (1<<GreenBits)-1;					//PD 24Oct97
	screenShot.greenBits	= GreenBits;						//DAW 24Oct97

	screenShot.blueScale	= BlueShift;						//PD 24Oct97
	screenShot.blueMask		= (1<<BlueBits)-1;					//PD 24Oct97
	screenShot.blueBits		= BlueBits;							//DAW 24Oct97

	ROWANSURFACEDESC rsd;
	Master()->DoLockScr(&rsd);

	screenShot.MakeHead(rsd.dwWidth,rsd.dwHeight);
	packedlength = screenShot.MakeBody(&rsd);		//logicalscreenptr,BytesPerScanLine);
	screenShot.Save(screenshotnum++,packedlength);
	if (screenshotnum>99)	screenshotnum=0;

	Master()->DoUnlockScr(&rsd);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TGA
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
CON TGA::TGA()
{
	hdrPtr = new TGAHeader;
	memset (hdrPtr,0,sizeof(TGAHeader));
	hdrPtr->w = 640;
	hdrPtr->h = 480;
	hdrPtr->nPlanes = 24;
	hdrPtr->flags = 0x20;
	bodyPtr = new UWord[DEFAULT_LBM*DEFAULT_LBM];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TGA
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
DES TGA::~TGA()
{
	delete [] (bodyPtr);
	delete (hdrPtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TGA
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
TGA::TGA(Window *screen)
{
	hdrPtr = new TGAHeader;
	memset (hdrPtr,0,sizeof(TGAHeader));
	hdrPtr->w = screen->VirtualWidth/screen->virtualXscale;
	hdrPtr->h = screen->VirtualHeight/screen->virtualYscale;
	hdrPtr->nPlanes = 24;
	hdrPtr->flags = 0x20;

	bodyPtr = new UWord[DEFAULT_LBM*DEFAULT_LBM];
}
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeHead
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
void TGA::MakeHead(UWord PhysicalWidth,UWord PhysicalHeight)
{
	delete (hdrPtr);

	hdrPtr = new TGAHeader;
	memset (hdrPtr,0,sizeof(TGAHeader));
	hdrPtr->w = PhysicalWidth;
	hdrPtr->h = PhysicalHeight;
	hdrPtr->nPlanes = 24;
	hdrPtr->flags = 0x20;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeBody
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
ULong TGA::MakeBody(ROWANSURFACEDESC* rsd) //LogicalPtr logicalscreenptr,int BytesPerScanLine)
{
	int		x, y;

	UWord	*srcPtr,
			*dstPtr;

	delete [] (bodyPtr);
	
	bodyPtr = new UWord[hdrPtr->w*hdrPtr->h];

	dstPtr = bodyPtr;

	UByteP psurf=(UByteP)rsd->lpSurface;

	for (y=0;y<hdrPtr->h;y++)
	{
		srcPtr = (UWord*)psurf;	//logicalscreenptr;

//		logicalscreenptr+=BytesPerScanLine;
		psurf+=rsd->lPitch;

		for (x=0;x<hdrPtr->w;x++,*dstPtr++=*srcPtr++);
	}

	return (2*hdrPtr->w*hdrPtr->h);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Save
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
void TGA::Save(UWord ScreenShot,ULong packedLength)
{
	ULong	bodyLen;
	FileNum	fil;
	FILE	*fp;
	div_t	val;
	char	*p;
	char	c;

	string nom=FILEMAN.namenumberedfile(FIL_STILLS_START);
	val = div(ScreenShot,10);
	p= 	strrchr(nom,'0');
	*p	=(val.rem)+'0';
	p--;
	*p	=(val.quot)+'0';
	p= 	strrchr(nom,'.');										//DAW 03Jun97
	p++;
	*p ='T';
	p++;
	*p='G';
	p++;
	*p='A';

	fp=fopen(nom,"wb");
	if (fp)
	{
		bodyLen=packedLength>>1;
		hdrPtr->Compression = 0x02;
		PutTGAHeader(fp,hdrPtr);
		PutTGABody(fp,bodyPtr,bodyLen);
		fclose(fp);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PutTGAWord
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
void TGA::PutTGAWord(FILE *fp,UWord i)
{
	UByte	c;

	c = (0xFF & i);	putc(c,fp);
	c = (0xFF00 & i)>>8; putc(c,fp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PutTGAHeader
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
void TGA::PutTGAHeader(FILE* fp,TGAHeaderP tgaHeader)
{
	putc(tgaHeader->JD00,fp);
	putc(tgaHeader->JD01,fp);
	putc(tgaHeader->Compression,fp);
	putc(tgaHeader->JD03,fp);
	putc(tgaHeader->JD04,fp);
	putc(tgaHeader->JD05,fp);
	putc(tgaHeader->JD06,fp);
	putc(tgaHeader->JD07,fp);
	putc(tgaHeader->JD08,fp);
	putc(tgaHeader->JD09,fp);
	putc(tgaHeader->JD10,fp);
	putc(tgaHeader->JD11,fp);
	PutTGAWord(fp,tgaHeader->w);
	PutTGAWord(fp,tgaHeader->h);
	putc(tgaHeader->nPlanes,fp);
	putc(tgaHeader->flags,fp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PutTGABody
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
void TGA::PutTGABody(FILE* fp,UWord* srcptr, ULong length)
{
	ULong	count;

	for (count=0;count<length;count++)
	{
		//Convert 5-bit RGB into 8-bit RGB

		UWord	inval = *srcptr++;

//Old_Code PD 24Oct97 			int	b = inval & 0x1F; inval >>= 5;
//Old_Code PD 24Oct97 			int	g = inval & 0x3F; inval >>= 6;
//Old_Code PD 24Oct97 			int	r = inval & 0x1F;

		int	r = (inval >> redScale) & redMask;				//PD 24Oct97
		int	g = (inval >> greenScale) & greenMask;			//PD 24Oct97
		int	b = (inval >> blueScale) & blueMask;			//PD 24Oct97

		r <<= (8-redBits);									//DAW 24Oct97
		g <<= (8-greenBits);								//DAW 24Oct97
		b <<= (8-blueBits);									//DAW 24Oct97

		putc(b,fp); putc(g,fp); putc(r,fp);
//		putc(b<<3,fp); putc(g<<2,fp); putc(r<<3,fp);
	}
}





















