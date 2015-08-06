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
//Filename       polygon.cpp
//System         
//Author         Paul.   
//Date           Wed 18 Oct 1995
//Description    
//------------------------------------------------------------------------------

#define F_GRAFIX												//DAW 05Aug96
#define F_SOUNDS
#define F_BATTLE
#include <windows.h>
		#include	"polygon.h"
		#include	"matrix.h"
#include "savegame.h"
		#include	"migLand.h"									//PD 19Jan98
		class polygon POLYGON;

extern	SLong ASM_AmulBdivC(SLong,SLong,SLong);
#ifdef __MSVC__
inline SLong ASM_AmulBdivC(SLong num1,SLong num2,SLong num3)
{
	SLong	retval;
    __asm
    {
		mov eax,num1;
		mov ebx,num2;
		mov ecx,num3;
		imul ebx;
		idiv ecx;
		mov retval,edx;
    }
    return retval;
}

#endif

	static	SWord	Circle_CosTable[] =							//RJS 17Nov97
	{
		0x7fff,0x7ffe,0x7ffe,0x7ffc,0x7ffa,0x7ff8,0x7ff5,0x7ff2,0x7fee,
		0x7fea,0x7fe5,0x7fe0,0x7fda,0x7fd4,0x7fcd,0x7fc6,0x7fbe,0x7fb6,
		0x7fad,0x7fa4,0x7f9a,0x7f90,0x7f85,0x7f7a,0x7f6e,0x7f62,0x7f55,
		0x7f48,0x7f3a,0x7f2c,0x7f1d,0x7f0d,0x7efd,0x7eed,0x7edc,0x7ecb,
		0x7eb9,0x7ea6,0x7e94,0x7e80,0x7e6c,0x7e58,0x7e43,0x7e2d,0x7e17,
		0x7e00,0x7de9,0x7dd2,0x7db9,0x7da1,0x7d87,0x7d6e,0x7d53,0x7d39,
		0x7d1d,0x7d01,0x7ce5,0x7cc8,0x7caa,0x7c8c,0x7c6e,0x7c4f,0x7c2f,
		0x7c0f,0x7bee,0x7bcd,0x7bab,0x7b88,0x7b65,0x7b42,0x7b1e,0x7af9,
		0x7ad4,0x7aae,0x7a88,0x7a61,0x7a39,0x7a11,0x79e9,0x79bf,0x7995,
		0x796b,0x7940,0x7914,0x78e8,0x78bc,0x788e,0x7860,0x7832,0x7803,
		0x77d3,0x77a2,0x7771,0x7740,0x770e,0x76db,0x76a7,0x7673,0x763f,
		0x7609,0x75d3,0x759d,0x7565,0x752d,0x74f5,0x74bc,0x7482,0x7447,
		0x740c,0x73d0,0x7393,0x7356,0x7318,0x72da,0x729a,0x725a,0x721a,
		0x71d8,0x7196,0x7153,0x7110,0x70cb,0x7086,0x7041,0x6ffa,0x6fb3,
		0x6f6b,0x6f22,0x6ed9,0x6e8e,0x6e43,0x6df7,0x6dab,0x6d5d,0x6d0f,
		0x6cc0,0x6c70,0x6c20,0x6bce,0x6b7c,0x6b28,0x6ad4,0x6a80,0x6a2a,
		0x69d3,0x697c,0x6923,0x68ca,0x6870,0x6815,0x67b8,0x675b,0x66fd,
		0x669f,0x663f,0x65de,0x657c,0x6519,0x64b5,0x6450,0x63ea,0x6383,
		0x631b,0x62b2,0x6248,0x61dc,0x6170,0x6102,0x6094,0x6024,0x5fb3,
		0x5f40,0x5ecd,0x5e58,0x5de2,0x5d6b,0x5cf2,0x5c79,0x5bfd,0x5b81,
		0x5b03,0x5a84,0x5a03,0x5981,0x58fd,0x5878,0x57f2,0x576a,0x56e0,
		0x5655,0x55c8,0x5539,0x54a9,0x5417,0x5383,0x52ed,0x5256,0x51bd,
		0x5122,0x5084,0x4fe5,0x4f44,0x4ea1,0x4dfb,0x4d53,0x4caa,0x4bfd,
		0x4b4f,0x4a9d,0x49ea,0x4933,0x487b,0x47bf,0x4700,0x463f,0x457a,
		0x44b3,0x43e8,0x431a,0x4248,0x4173,0x409a,0x3fbd,0x3edc,0x3df7,
		0x3d0d,0x3c1f,0x3b2c,0x3a34,0x3937,0x3834,0x372b,0x361b,0x3506,
		0x33e9,0x32c5,0x3198,0x3063,0x2f25,0x2ddd,0x2c8a,0x2b2b,0x29bf,
		0x2845,0x26ba,0x251d,0x236c,0x21a3,0x1fbf,0x1dba,0x1b8c,0x192c,
		0x1689,0x1389,0xff7,0xb4d,0x0
	};															//RJS 17Nov97


inline void FtoITexture(VERTEX_PTR* ppv)
{
	while (*ppv)
	{
		(*ppv)->ix.i=SLong((*ppv)->ix.f);
		(*ppv)->iy.i=SLong((*ppv)->iy.f);
		ppv++;
	}
}
bool fNoFogOrClip=false;
////////////////////////////////////////////////////////////////////////////////
//
//	FIRST THE CREATEPOLY ROUTINES - these setup jumps to poly type specific
//	routines as well as reseting a few variables.
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetOpacityON
//Author		Paul.   
//Date			Wed 17 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::SetOpacityON()
{
	horilinertn = currscreen->GetScanLineAddr(polytype);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createhaze
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
void polygon::createhaze(Colour colour)
{
	polycolour = colour;										

//DEAD	if (polycolour == ARTWORKMASK)								
//DEAD		SetPixelWidth(4);										

	vertex_index = vertex_list;
	vertexcount = 0;

	currscreen->SetColour(colour);								

	polyType.ptType = POLYTYPE::PT_PlainColour;					
	polyType.colour = colour;									

	polytype=PLAIN;												

	scanconvert		= &polygon::chazescancnvrt;
	scanconvertflat	= &polygon::chazescancnvrt;					
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createsphere
//Author		Robert Slater
//Date			Fri 14 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createsphere(Colour colour)
{
	SelectPalette(0);
	polycolour = colour;										

//DEAD	if (polycolour == ARTWORKMASK)								
//DEAD		SetPixelWidth(4);										

	vertex_index = vertex_list;
	vertexcount = 0;

	currscreen->SetColour(colour);								

	polyType.ptType = POLYTYPE::PT_PlainColour;					
	polyType.colour = colour;									

	polytype=PLAIN;												
	horilinertn = currscreen->GetScanLineAddr(polytype);		

	scanconvert		= &polygon::cspherescancnvrt;
	scanconvertflat	= &polygon::cspherescancnvrt;					
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createsphere
//Author		Robert Slater
//Date			Tue 18 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createsphere(Colour colour, SWord depth)
{
	SelectPalette(0);
	polycolour = colour;										

//DEAD	if (polycolour == ARTWORKMASK)								
//DEAD		SetPixelWidth(4);										

	vertex_index = vertex_list;
	vertexcount = 0;

	currscreen->SetColour(colour);								

	polyType.ptType = POLYTYPE::PT_PlainColour;					
	polyType.colour = colour;									

	polytype=PLAIN;												

	SphereDepth = depth;											//RJS 25Nov97

	horilinertn = currscreen->GetScanLineAddr(polytype);		

	scanconvert		= &polygon::csphfadescancnvrt;
	scanconvertflat	= &polygon::csphfadescancnvrt;					
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createsphere
//Author		Robert Slater
//Date			Tue 20 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createsphere(Colour colour, LUMINOSITYTYPE depth)
{
	SelectPalette(0);
	polycolour = colour;										

//DEAD	if (polycolour == ARTWORKMASK)								
//DEAD		SetPixelWidth(4);										

	vertex_index = vertex_list;
	vertexcount = 0;

	currscreen->SetColour(colour);								

	polyType.ptType = POLYTYPE::PT_PlainColour;					
	polyType.colour = colour;									

	polytype=PLAIN;												

	SphereDepth = depth;											//RJS 25Nov97

	horilinertn = currscreen->GetScanLineAddr(polytype);

	if ((colour >= 240) && (depth > LUM_OFF))
	{
		scanconvert		= &polygon::csphlumscancnvrt;
		scanconvertflat	= &polygon::csphlumscancnvrt;
	}
	else
	{
		SphereDepth = SMOKED_SOLID;

		scanconvert		= &polygon::csphfadescancnvrt;
		scanconvertflat	= &polygon::csphfadescancnvrt;					
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createhalo
//Author		Robert Slater
//Date			Fri 16 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createhalo(Colour colour, SWord depth)
{
	SelectPalette(0);
	polycolour = colour;										

//DEAD	if (polycolour == ARTWORKMASK)								
//DEAD		SetPixelWidth(4);										

	vertex_index = vertex_list;
	vertexcount = 0;

	currscreen->SetColour(colour);								

	polyType.ptType = POLYTYPE::PT_PlainColour;					
	polyType.colour = colour;									

	polytype=PLAIN;												

	SphereDepth = depth;											//RJS 25Nov97

	scanconvert		= &polygon::chalofadescancnvrt;
	scanconvertflat	= &polygon::chalofadescancnvrt;					
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createsphere
//Author		Robert Slater
//Date			Fri 14 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createsphere(ImageMapNumber imapno)
{
	polyimage = imapno;								
	vertex_index = vertex_list;
	vertexcount = 0;
	ImageMapNumber	realmapno;
	realmapno 		= imapno;
	scanconvert		= &polygon::ispherescancnvrt;
	scanconvertflat	= &polygon::ispherescancnvrt;					
	currscreen->SetColour(realmapno);							
	polyType.ptType = POLYTYPE::PT_PlainImagem;					
	polyType.imapno = realmapno;								
	polyType.lpImageMap = Image_Map.GetImageMapPtr(realmapno);
	SWord pali=SWord(polyType.lpImageMap->paletteindex);
	if (pali<8)	
		SelectPalette(pali);
	else										
		SelectPalette(0);
	if (fSoftware && polyType.lpImageMap->alpha!=NULL)	polytype=IMAPPED_ALPHA;
	else if (polyType.lpImageMap->isMasked)				polytype=IMAPPED_M;
	else												polytype=IMAPPED;
	horilinertn = currscreen->GetScanLineAddr(polytype);		
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
//Author		Paul.   
//Date			Wed 18 Oct 1995
//
//Description	Sets up poly routine for a plain poly draw
//				If the colour is ARTWORKMASK then use the polygon to 
//				generate a list of clip areas.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createpoly(Colour colour)
{
	SelectPalette(0);
	polycolour = colour;										//PD 30Jan96

	vertex_index = vertex_list;
	vertexcount = 0;

	polyType.ptType = POLYTYPE::PT_PlainColour;					//PD 12Feb97
	polyType.colour = colour;									//PD 12Feb97

	polytype=PLAIN;												//PD 03Jan96

	if (fSoftware)
	{
		fFoggingRequired=false;
		doclip=0;
		horilinertn = currscreen->GetScanLineAddr(polytype);		//PD 03Jan96
		currscreen->SetColour(colour);									//PD 29Nov95
		scanconvert		= &polygon::cpolyscancnvrt;
		scanconvertflat	= &polygon::cflatscancnvrt;					//PD 24Oct96
		clipperflag=CLIPF_NULL;
	}
}

//Software gouraud plain colour polygon create

void polygon::createpoly(UByte sR,UByte sG,UByte sB,UByte dR,UByte dG,UByte dB)
{
	if (fSoftware)
	{
		SelectPalette(0);
		if (currscreen)
		{
			UWord* ptbl=(UWord*)currscreen->GetHorizonFadeTable();
			currscreen->DoMakeColourRangeFadeTable(ptbl,sR,sG,sB,dR,dG,dB);
		}
		vertex_index=vertex_list;
		vertexcount=0;
		polytype=GOURAUD;
		fFoggingRequired=false;
		fFoggingActive=false;
		doclip=0;
		horilinertn=currscreen->GetScanLineAddr(polytype);
		scanconvert=&polygon::gpolyscancnvrt;
		scanconvertflat=&polygon::gflatscancnvrt;
		clipperflag=CLIPF_INTENSITY;
	}
	else _asm {int 3}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
//Author		Paul.   
//Date			Wed 18 Oct 1995
//
//Description	Sets up poly routine for an imagemapped draw
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createfakefog(ImageMapNumber imapno)
{
	polyimage = imapno;											//PD 30Jan96

	vertex_index = vertex_list;
	vertexcount = 0;
	
	polyType.imapno 	= imapno;								//RJS 19Feb98
	polyType.lpImageMap = Image_Map.GetImageMapPtr(imapno);		//RJS 19Feb98
	if (polyType.lpImageMap->isMasked)							//RJS 26Mar98
	{															//RJS 26Mar98
		polytype=IMAPPED_M;										//RJS 26Mar98
		polyType.ptType = POLYTYPE::PT_MaskedImagem;			//RJS 26Mar98
	}															//RJS 26Mar98
	else														//RJS 26Mar98
	{															//RJS 26Mar98
		polytype=IMAPPED;										//RJS 26Mar98
		polyType.ptType = POLYTYPE::PT_FakeFog;				//RJS 26Mar98
	}															//RJS 26Mar98

	if (fSoftware)
	{
		SWord pali=SWord(polyType.lpImageMap->paletteindex);
		if (pali<8)	
			SelectPalette(pali);
		else										
			SelectPalette(0);
		fFoggingRequired=false;
		doclip=0;
		scanconvert		= &polygon::ipolyscancnvrt;
		scanconvertflat	= &polygon::iflatscancnvrt;					//PD 24Oct96
		currscreen->SetColour(imapno);								//RJS 19Feb98
		horilinertn = currscreen->GetScanLineAddr(polytype);		//PD 03Jan96
		clipperflag=CLIPF_TEXTURE;
	}
}

void polygon::createpoly(ImageMapNumber imapno)
{
	polyimage = imapno;											//PD 30Jan96

	vertex_index = vertex_list;
	vertexcount = 0;
	
	polyType.imapno 	= imapno;								//RJS 19Feb98
	polyType.lpImageMap = Image_Map.GetImageMapPtr(imapno);		//RJS 19Feb98
	if (fSoftware && polyType.lpImageMap->alpha!=NULL)
	{
		polytype=IMAPPED_ALPHA;										//RJS 26Mar98
		polyType.ptType = POLYTYPE::PT_MaskedImagem;			//RJS 26Mar98
	}
	else if (polyType.lpImageMap->isMasked)							//RJS 26Mar98
	{															//RJS 26Mar98
		polytype=IMAPPED_M;										//RJS 26Mar98
		polyType.ptType = POLYTYPE::PT_MaskedImagem;			//RJS 26Mar98
	}															//RJS 26Mar98
	else														//RJS 26Mar98
	{															//RJS 26Mar98
		polytype=IMAPPED;										//RJS 26Mar98
		polyType.ptType = POLYTYPE::PT_PlainImagem;				//RJS 26Mar98
	}															//RJS 26Mar98

	if (fSoftware)
	{
		SWord pali=SWord(polyType.lpImageMap->paletteindex);
		if (pali<8)	
			SelectPalette(pali);
		else										
			SelectPalette(0);
		fFoggingRequired=false;
		doclip=0;
		scanconvert		= &polygon::ipolyscancnvrt;
		scanconvertflat	= &polygon::iflatscancnvrt;					//PD 24Oct96
		currscreen->SetColour(imapno);								//RJS 19Feb98
		horilinertn = currscreen->GetScanLineAddr(polytype);		//PD 03Jan96
		clipperflag=CLIPF_TEXTURE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
//Author		Paul.   
//Date			Fri 2 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createpoly(ImageMapDescPtr imapp)
{
	vertex_index = vertex_list;

	vertexcount = 0;

	polytype=IMAPPED;

	polyType.ptType = POLYTYPE::PT_PlainImagem;					//PD 12Feb97
	polyType.imapno = (ImageMapNumber)-1;						//PD 14Feb97
	polyType.lpImageMap = imapp;								//PD 12Feb97

	if (fSoftware)
	{
		SWord pali=SWord(polyType.lpImageMap->paletteindex);
		if (pali<8)	
			SelectPalette(pali);
		else										
			SelectPalette(0);
		fFoggingRequired=false;
		doclip=0;
		scanconvert	= &polygon::ipolyscancnvrt;
		scanconvertflat	= &polygon::iflatscancnvrt;					//PD 24Oct96
		currscreen->SetColour(imapp);
		horilinertn = currscreen->GetScanLineAddr(polytype);
		clipperflag=CLIPF_TEXTURE;
	}
}

void polygon::createpoly(ImageMapDescPtr imapp,SCANLINETYPE slt)
{
	vertex_index = vertex_list;
	vertexcount = 0;
	polytype=slt;
	fFoggingRequired=false;
	doclip=0;
	scanconvert	= &polygon::sipolyscancnvrt;
	scanconvertflat	= &polygon::siflatscancnvrt;
	currscreen->SetColour(imapp);
	horilinertn = currscreen->GetScanLineAddr(polytype);
	SWord pali=SWord(imapp->paletteindex);
	if (pali<8)	
		SelectPalette(pali);
	else										
		SelectPalette(0);
	clipperflag=CLIPF_TEXTURE|CLIPF_INTENSITY;
}

void polygon::createpoly(ROWANSURFACEDESC* rsd,Float& range)
{
	SelectPalette(-1);
	if (fNoFogOrClip || range<viewdata.FogStart)
	{
		fFoggingRequired=false;
		fFoggingActive=false;
		polytype=IMAPPED;
		scanconvert=&polygon::ipolyscancnvrt;
		scanconvertflat=&polygon::iflatscancnvrt;
	}
	else
	{
		fFoggingRequired=false;
		fFoggingActive=true;
		polytype=IMAPPED_S;
		scanconvert=&polygon::sipolyscancnvrt;
		scanconvertflat=&polygon::iflatscancnvrt;
	}
	doclip=0;
	vertex_index = vertex_list;
	vertexcount = 0;
	currscreen->SetColour(rsd);
	horilinertn=currscreen->GetScanLineAddr(polytype);
	clipperflag=CLIPF_TEXTURE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
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
void polygon::createpoly()
{
	vertex_index	= vertex_list;
	vertexcount 	= 0;
	polytype		= IMAPPED;

	if (fSoftware)
	{
		fFoggingRequired=false;
		doclip=0;
		scanconvert		= &polygon::ipolyscancnvrt;
		scanconvertflat	= &polygon::iflatscancnvrt;					//PD 24Oct96
		horilinertn 	= currscreen->GetScanLineAddr(polytype);
		clipperflag=CLIPF_TEXTURE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
//Author		Paul.   
//Date			Thu 18 Jan 1996
//
//Description	Sets up poly routine for an opacity mapped draw
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createpoly(OpacityMapNumber imapno)
{
	polyoimage = imapno;											//PD 30Jan96

	vertex_index = vertex_list;
	vertexcount = 0;
	
	ImageMapNumber	realmapno;

	realmapno 		= (ImageMapNumber )imapno;

	polyType.imapno 	= realmapno;							//PD 28May97
	polyType.lpImageMap = Image_Map.GetImageMapPtr(realmapno);	//PD 28May97
	if (polyType.lpImageMap->isMasked)							//RJS 26Mar98
	{															//RJS 26Mar98
		polytype=OMAPPED_M;										//RJS 26Mar98
		polyType.ptType = POLYTYPE::PT_MaskedImagem;			//RJS 26Mar98
	}															//RJS 26Mar98
	else														//RJS 26Mar98
	{															//RJS 26Mar98
		polytype=OMAPPED;										//RJS 26Mar98
		polyType.ptType = POLYTYPE::PT_PlainImagem;				//RJS 26Mar98
	}	

	if (fSoftware)
	{
		SWord pali=SWord(polyType.lpImageMap->paletteindex);
		if (pali<8)	
			SelectPalette(pali);
		else										
			SelectPalette(0);
		fFoggingRequired=false;
		doclip=0;
		scanconvert		= &polygon::ipolyscancnvrt;
		scanconvertflat	= &polygon::iflatscancnvrt;					//PD 24Oct96
		currscreen->SetColour(realmapno);
		horilinertn = currscreen->GetScanLineAddr(polytype);
		clipperflag=CLIPF_TEXTURE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
//Author		Paul.   
//Date			Wed 6 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createpoly(ImageMapNumber imapno, ColourRange crng)
{
	polyimage	= imapno;										//PD 30Jan96
	polyrange	= crng;											//PD 30Jan96

	vertex_index = vertex_list;
	vertexcount = 0;
	{
		ImageMapNumber	realmapno;
		Colour			basecol = RANGE00;						//DAW 18Dec95
		ColourRange	rng = (ColourRange)SPREAD00;				//DAW 18Dec95
	
		realmapno 		= imapno;								//DAW 27Oct98
	
		if (ditherflag)
			polytype=IMAPPED_SH;								//PD 03Jan96
		else
			polytype=NDIMAPPED_SH;
	
		if (realmapno==imapno)	polyType.ptType = POLYTYPE::PT_PlainImagem;
		else					polyType.ptType = POLYTYPE::PT_MaskedImagem;

		polyType.imapno 	= realmapno;						//PD 28May97
		polyType.lpImageMap = Image_Map.GetImageMapPtr(realmapno);//PD 28May97

		if (fSoftware)
		{
			SWord pali=SWord(polyType.lpImageMap->paletteindex);
			if (pali<8)	
				SelectPalette(pali);
			else											
				SelectPalette(0);
			fFoggingRequired=false;
			doclip=0;
			scanconvert		= &polygon::sipolyscancnvrt;
			scanconvertflat	= &polygon::siflatscancnvrt;			//PD 24Oct96
			currscreen->SetColour(basecol,rng);
			currscreen->SetColour(realmapno);
			horilinertn = currscreen->GetScanLineAddr(polytype);	//PD 03Jan96
			clipperflag=CLIPF_TEXTURE;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
//Author		Paul.   
//Date			Fri 2 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createpoly(ImageMapDescPtr imapp, ColourRange crng)
{
	polyrange	= crng;

	vertex_index = vertex_list;

	vertexcount = 0;

	Colour		basecol = RANGE00;

	ColourRange	rng = (ColourRange)SPREAD00;
	
	if (ditherflag)
		polytype=IMAPPED_SH;
	else
		polytype=NDIMAPPED_SH;
	
	polyType.ptType = POLYTYPE::PT_PlainImagem;					//PD 12Feb97
	polyType.imapno = (ImageMapNumber)-1;						//PD 14Feb97
	polyType.lpImageMap = imapp;								//PD 12Feb97

	if (fSoftware)
	{
		SWord pali=SWord(polyType.lpImageMap->paletteindex);
		if (pali<8)	
			SelectPalette(pali);
		else										
			SelectPalette(0);
		fFoggingRequired=false;
		doclip=0;
		currscreen->SetColour(basecol,rng);
		currscreen->SetColour(imapp);
		scanconvert	= &polygon::widesipolyscancnvrt;
		scanconvertflat	= &polygon::siflatscancnvrt;				//PD 24Oct96
		horilinertn = currscreen->GetScanLineAddr(polytype);
		clipperflag=CLIPF_TEXTURE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
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
void polygon::createpoly(ImageMapNumber imapno,Colour basecol)	//JIM 12Dec95
{
#ifdef __WATCOMC__
	INT3();
#endif
#ifdef __MSVC__
	INT3;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
//Author		Paul.   
//Date			Wed 8 Nov 1995
//
//Description	Faded/colour shifted imagemap draw
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createpoly(ImageMapNumber imapno,Colour basecol,ColourRange rng)
{
	polyimage	= imapno;										//PD 30Jan96
	polycolour	= basecol;										//PD 30Jan96
	polyrange	= rng;											//PD 30Jan96

	vertex_index = vertex_list;
	vertexcount = 0;
	
	ImageMapNumber	realmapno;

	realmapno 		= (imapno>0)?imapno:(ImageMapNumber)-imapno;

	polytype=IMAPPED_S;										//PD 03Jan96

	if (realmapno==imapno)	polyType.ptType = POLYTYPE::PT_PlainImagem;
	else					polyType.ptType = POLYTYPE::PT_MaskedImagem;

	polyType.imapno 	= realmapno;							//PD 28May97
	polyType.lpImageMap = Image_Map.GetImageMapPtr(realmapno);	//PD 28May97

	if (fSoftware)
	{
		SWord pali=SWord(polyType.lpImageMap->paletteindex);
		if (pali<8)	
			SelectPalette(pali);
		else										
			SelectPalette(0);
		fFoggingRequired=false;
		doclip=0;
		scanconvert		= &polygon::sipolyscancnvrt;
		scanconvertflat	= &polygon::siflatscancnvrt;				//PD 24Oct96
		currscreen->SetColour(realmapno);								//PD 29Nov95
		currscreen->SetColour(basecol,rng);							//PD 29Nov95
		horilinertn = currscreen->GetScanLineAddr(polytype);		//PD 03Jan96
		clipperflag=CLIPF_TEXTURE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
//Author		Paul.   
//Date			Tue 7 Apr 1998
//------------------------------------------------------------------------------
void polygon::createpoly(PolyType::PolyTypes pt)
{
	polycolour=ARTWORKMASK;
	vertex_index=vertex_list;
	vertexcount=0;
	polyType.ptType=POLYTYPE::PT_GColour;
	polyType.colour=ARTWORKMASK;
	polytype=PLAIN;
	if (fSoftware)
	{
		SelectPalette(0);
		fFoggingRequired=false;
		doclip=0;
		currscreen->SetColour(ARTWORKMASK);
		horilinertn=currscreen->GetScanLineAddr(polytype);
		scanconvert		= &polygon::cpolyscancnvrt;
		scanconvertflat	= &polygon::cflatscancnvrt;
		clipperflag=CLIPF_NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createpoly
//Author		Paul.   
//Date			Mon 18 May 1998
//------------------------------------------------------------------------------
void polygon::createpoly(ULong hTexture)
{
	polycolour=ARTWORKMASK;
	vertex_index=vertex_list;
	vertexcount=0;
	polyType.ptType=POLYTYPE::PT_HighLand;
	polyType.hTexture=hTexture;
	polytype=PLAIN;

	if (fSoftware)
	{
		fFoggingRequired=false;
		doclip=0;
		SelectPalette(-1);
		horilinertn=currscreen->GetScanLineAddr(polytype);
		scanconvert		= &polygon::cpolyscancnvrt;
		scanconvertflat	= &polygon::cflatscancnvrt;
		clipperflag=CLIPF_NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//	THE CREATEVERTEX ROUTINES - these copy over the vertex data required for
//	the different types of poly. They also check to see if any zclipping is
//	required.
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createsphvert
//Author		Robert Slater
//Date			Mon 17 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createsphvert(DoPointStruc dopoint, SWord	Radius)
{
	VERTEX_PTR temp = AllocateVertex();

	temp->bx.f = dopoint.bodyx.f;
	temp->by.f = dopoint.bodyy.f;
	temp->bz.f = dopoint.bodyz.f;
	temp->sx.f = dopoint.screenx.f;
	temp->sy.f = dopoint.screeny.f;

	nvertptr[vertexcount] = temp;
	SphereRadius = Radius;
	
	vertexcount++;

	nvertptr[vertexcount] = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createsphvert
//Author		Robert Slater
//Date			Fri 16 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createsphvert(DoPointStruc dopoint, SWord	Radius, SWord Halowidth)
{
	VERTEX_PTR temp = AllocateVertex();

	temp->bx.f = dopoint.bodyx.f;
	temp->by.f = dopoint.bodyy.f;
	temp->bz.f = dopoint.bodyz.f;
	temp->sx.f = dopoint.screenx.f;
	temp->sy.f = dopoint.screeny.f;

	nvertptr[vertexcount] = temp;
	SphereRadius = Radius;
	HaloWidth = Halowidth;
	
	vertexcount++;

	nvertptr[vertexcount] = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createsphvert
//Author		Robert Slater
//Date			Mon 17 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createsphvert(	DoPointStruc dopoint,
								SWord		Radius,
								SLong		ix0,
								SLong		iy0,
								SLong		imagex,
								SLong		imagey)
{
	VERTEX_PTR temp = AllocateVertex();

	temp->bx.f = dopoint.bodyx.f;
	temp->by.f = dopoint.bodyy.f;
	temp->bz.f = dopoint.bodyz.f;
	temp->sx.f = dopoint.screenx.f;
	temp->sy.f = dopoint.screeny.f;

	SphIxStart = ix0 << 16;
	SphIyStart = iy0 << 16;

	temp->ix.i = imagex<<16;
	temp->iy.i = imagey<<16;

	nvertptr[vertexcount] = temp;
	SphereRadius = Radius;
	
	vertexcount++;

	nvertptr[vertexcount] = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		creatvert
//Author		Paul.   
//Date			Fri 20 Oct 1995
//
//Description	Vertex creation routine for single colour polygons
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createvert(DoPointStruc &dopoint)
{
	VERTEX_PTR temp = AllocateVertex();
	temp->bx.f = dopoint.bodyx.f;
	temp->by.f = dopoint.bodyy.f;
	temp->bz.f = dopoint.bodyz.f;
	temp->intensity = 0xFF<<12;
	temp->specular=dopoint.specular==-1?-1:dopoint.specular<<12;
	temp->mist=dopoint.mist;
	temp->snow=dopoint.snow;
	temp->clipFlags=dopoint.clipFlags;
	doclip|=temp->clipFlags;
	nvertptr[vertexcount] = temp;
	vertexcount++;
	nvertptr[vertexcount] = NULL;
}

void polygon::softwarevert(DoPointStruc &dopoint)
{
	VERTEX_PTR temp = AllocateVertex();
	temp->bx.f = dopoint.bodyx.f;
	temp->by.f = dopoint.bodyy.f;
	temp->bz.f = dopoint.bodyz.f;
	temp->intensity = 0xFF<<12;
	temp->specular=dopoint.specular==-1?-1:dopoint.specular<<12;
	temp->ix.f = (Float)dopoint.ix*(Float)(65536.0/128.0);
	temp->iy.f = (Float)dopoint.iy*(Float)(65536.0/128.0);
	temp->mist=dopoint.mist;
	temp->snow=dopoint.snow;
	temp->clipFlags=dopoint.clipFlags;
	doclip|=temp->clipFlags;
	nvertptr[vertexcount] = temp;
	vertexcount++;
	nvertptr[vertexcount] = NULL;
}

void polygon::gouraudvert(DoPointStruc&dopoint,UWord ival)
{
	VERTEX_PTR temp = AllocateVertex();
	temp->bx.f=dopoint.bodyx.f;
	temp->by.f=dopoint.bodyy.f;
	temp->bz.f=dopoint.bodyz.f;
	temp->intensity=ival<<12;
	temp->specular=-1;
	temp->clipFlags=dopoint.clipFlags;
	doclip|=temp->clipFlags;
	nvertptr[vertexcount] = temp;
	vertexcount++;
	nvertptr[vertexcount] = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		creatvert
//Author		Paul.   
//Date			Fri 20 Oct 1995
//
//Description	Vertex creation routine for Gouraud shaded polygons
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createvert(DoPointStruc &dopoint, SWord &intens)
{
	VERTEX_PTR temp = AllocateVertex();
	temp->bx.f = dopoint.bodyx.f;
	temp->by.f = dopoint.bodyy.f;
	temp->bz.f = dopoint.bodyz.f;
	temp->intensity = intens<<12;
	temp->specular=dopoint.specular==-1?-1:dopoint.specular<<12;
	temp->mist=dopoint.mist;
	temp->snow=dopoint.snow;
	temp->clipFlags=dopoint.clipFlags;
	doclip|=temp->clipFlags;
	nvertptr[vertexcount] = temp;
	vertexcount++;
	nvertptr[vertexcount] = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createvert
//Author		Paul.   
//Date			Wed 18 Oct 1995
//
//Description	Vertex creation routine for imagemapped polygons	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createvert(DoPointStruc &dopoint, SWord &imagex, SWord &imagey)//PD 25Jan96
{
	VERTEX_PTR temp = AllocateVertex();
	temp->bx.f = dopoint.bodyx.f;
	temp->by.f = dopoint.bodyy.f;
	temp->bz.f = dopoint.bodyz.f;
	temp->intensity = 0xFF<<12;
	temp->specular=dopoint.specular==-1?-1:dopoint.specular<<12;
	temp->mist=dopoint.mist;
	temp->snow=dopoint.snow;
	temp->clipFlags=dopoint.clipFlags;
	doclip|=temp->clipFlags;

	temp->ix.f = (Float)imagex*(Float)65536.0;
	temp->iy.f = (Float)imagey*(Float)65536.0;

	nvertptr[vertexcount] = temp;
	vertexcount++;
	nvertptr[vertexcount] = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createvert
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
void polygon::createvert(DoPointStruc& dopoint,SWord& imagex,SWord& imagey,SWord& intens)//PD 25Jan96
{
	VERTEX_PTR temp = AllocateVertex();

	temp->bx.f = dopoint.bodyx.f;
	temp->by.f = dopoint.bodyy.f;
	temp->bz.f = dopoint.bodyz.f;

	temp->ix.f = (Float)imagex*(Float)65536.0;
	temp->iy.f = (Float)imagey*(Float)65536.0;
	temp->intensity = intens<<12;
	temp->specular=dopoint.specular==-1?-1:dopoint.specular<<12;
	temp->mist=dopoint.mist;
	temp->snow=dopoint.snow;
	temp->clipFlags=dopoint.clipFlags;
	doclip|=temp->clipFlags;

	nvertptr[vertexcount] = temp;
	vertexcount++;
	nvertptr[vertexcount] = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createvert
//Author		Paul.   
//Date			Thu 16 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void polygon::createvert(landvertex& landvert,SWord& imagex,SWord& imagey,SWord& intens)
//{
//	VERTEX_PTR temp = AllocateVertex();
//
//	temp->bx.f = landvert.bodyx.f;
//	temp->by.f = landvert.bodyy.f;
//	temp->bz.f = landvert.bodyz.f;

//	temp->ix.f = (Float)imagex*(Float)65536.0;
//	temp->iy.f = (Float)imagey*(Float)65536.0;
//	temp->intensity = intens<<12;
//	temp->specular=0x00<<12;
//	nvertptr[vertexcount] = temp;
//	vertexcount++;
//	nvertptr[vertexcount] = NULL;
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createvert
//Author		Paul.   
//Date			Tue 30 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createvert(VERTEX& vertx)
{
	VERTEX_PTR temp = AllocateVertex();

	*temp = vertx;

	nvertptr[vertexcount] = temp;
	vertexcount++;
	nvertptr[vertexcount] = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createvert
//Author		Paul.   
//Date			Tue 7 Apr 1998
//------------------------------------------------------------------------------
void polygon::createvert(DoPointStruc& dp,UByte r,UByte g,UByte b,UByte a)
{
	VERTEX_PTR temp=AllocateVertex();
	temp->bx.f=dp.bodyx.f;
	temp->by.f=dp.bodyy.f;
	temp->bz.f=dp.bodyz.f;
	temp->intensity = 0xFF<<12;
	temp->mist=dp.mist;
	temp->snow=dp.snow;
	temp->clipFlags=dp.clipFlags;
	doclip|=temp->clipFlags;
	temp->col.r=r;
	temp->col.g=g;
	temp->col.b=b;
	temp->col.a=a;
	nvertptr[vertexcount]=temp;
	vertexcount++;
	nvertptr[vertexcount]=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createvert
//Author		Paul.   
//Date			Tue 5 May 1998
//------------------------------------------------------------------------------
void polygon::createvert(DoPointStruc& dopoint,
						SWord& imagex,SWord& imagey,
						SWord& intens,
						SWord& spec)
{
	VERTEX& temp=*AllocateVertex();
	temp.bx=dopoint.bodyx;
	temp.by=dopoint.bodyy;
	temp.bz=dopoint.bodyz;
	temp.ix.f=(Float)imagex*(Float)65536.0;
	temp.iy.f=(Float)imagey*(Float)65536.0;
	temp.intensity=intens<<12;
	temp.specular=spec<<12;
	temp.mist=dopoint.mist;
	temp.snow=dopoint.snow;
	temp.clipFlags=dopoint.clipFlags;
	doclip|=temp.clipFlags;
	nvertptr[vertexcount++]=&temp;
	nvertptr[vertexcount]=NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
//	DRAWPOLY is the generic polygon draw code. It calls routines as set up in
//	'createpoly'
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setpolyscrn
//Author		Jim Taylor
//Date			Thu 14 Dec 1995
//
//Description	Sets the screen pointer in the polygon routine
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool polygon::setpolyscrn(Window* w,SLong maxvisrange,ANGLES viewang)
{
	currscreen = w;

	fSoftware=Save_Data.fSoftware;

//dead	LeftX = (Float)currscreen->VirtualMinX;
//dead	RightX = LeftX + (Float)currscreen->VirtualWidth - 1;

//dead	TopY	= (Float)currscreen->VirtualMinY;
//dead	BotY	= TopY + (Float)currscreen->VirtualHeight - 1;

	Float sin_ang,cos_ang,h,D,F;
	SLong win_width,win_height;

	currscreen->DoGetSurfaceDimensions(win_width,win_height);
	viewdata.originx = win_width>>1;
	viewdata.originy = win_height>>1;

	viewdata.scalex = viewdata.originx;
	viewdata.scaley = viewdata.originy;

	viewdata.clipLft = 	viewdata.originx-viewdata.scalex;
	viewdata.clipRgt = 	viewdata.originx+viewdata.scalex;
	viewdata.clipTop =	viewdata.originy-viewdata.scaley;
	viewdata.clipBot =	viewdata.originy+viewdata.scaley;

	Float fMaxVisRange = (Float)maxvisrange;
	Float frMaxVisRange=.99999/fMaxVisRange;

	const Float SZ_SCALE=4.;

	//h = half the height of viewing frustrum
	//D = distance of projection plane from the viewer (always 1.0)
	//F = distance between the front and back clipping planes
	//		(fMaxVisRange-1.0)
	D=1.0;
	F=fMaxVisRange-D;
	viewdata.viewang=viewang;
	viewang=(Angles)(viewang>>1);
	h=D*1.0;							// h = D.tan(theta/2)
	viewdata.D=D;
	viewdata.F=fMaxVisRange;
	viewdata.h=h;
	viewdata.hoD=h/D;
	viewdata.R=F-D;
	viewdata.FoR=viewdata.F/viewdata.R;
	viewdata.sD=viewdata.D*SZ_SCALE;
//dead	SelectPalette(0);
	return(TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drawpoly
//Author		Paul.   
//Date			Wed 18 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#define SINGLE_PIXEL_RANGE 200000
#define DOUBLE_PIXEL_RANGE 800000

void polygon::drawpoly()
{
	if (fSoftware)	
	{
		if (doclip && !GenericPolyClip()) return;
		if (!PolyCross()) return;
		Float nearestZ=FtoIPoly();
		if (fPerspective && nearestZ<(SINGLE_PIXEL_RANGE>>1))
		{
			SetPixelWidth(1);
			perspectivepoly();
		}
		else if ((*nvertptr)->bz.f<SINGLE_PIXEL_RANGE)	SetPixelWidth(1);
		else if ((*nvertptr)->bz.f<DOUBLE_PIXEL_RANGE)	SetPixelWidth(2);
		else											SetPixelWidth(4);
		FtoITexture(nvertptr);
		softpoly();
	}
	else hardpoly();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		hardpoly
//Author		Paul.   
//Date			Tue 13 Apr 1999
//------------------------------------------------------------------------------
void polygon::hardpoly()
{
	polyType.points=vertexcount;
	polyType.lplpVertices=nvertptr;
	currscreen->DoHardPoly(&polyType);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		softpoly
//Author		Paul.   
//Date			Tue 13 Apr 1999
//------------------------------------------------------------------------------
void polygon::softpoly()
{
	HLINELIST	whll;

	DIRECTION	led;

	SLong		dxn,	dyn,	dxp,
				dyp,	miny,	maxy;

	VERTEX_PTR	*nindp,	*pindp,	*tempp,
				*maxip,	*minilp,*minirp;

	//Scan the list to find the top and bottom of the polygon

	minilp =
		maxip = nvertptr;

	maxy =
		miny = (*nvertptr)->sy.i;

	tempp = nvertptr+1;

	while(*tempp)
	{
		if((*tempp)->sy.i<miny)
		{
			minilp = tempp;
			miny = (*tempp)->sy.i;
		}
		else
		{
			if((*tempp)->sy.i>maxy)
			{
				maxip = tempp;
				maxy = (*tempp)->sy.i;
			}
		}
		tempp++;
	}

	//Quick exit for flat polygons

	if(miny!=maxy)
	{

		//Scan in ascending order to find last top-edge point

		minirp = minilp;

		while((*minirp)->sy.i == miny)
		{
			minirp++;
			if(!*minirp) minirp = nvertptr;
		}

		minirp--;

		if(!*minirp) minirp+=vertexcount;

		//Now scan in descending order to find first top-edge point

		while((*minilp)->sy.i == miny)
		{
			minilp--;
			if(!*minilp) minilp+=vertexcount;
		}
	
		minilp++;
		if(!*minilp) minilp = nvertptr;

		//Figure out which direction to go through the vertex list from the
		//top vertex which is the left and which is the right.

		led = BACKWARDS;
	
		if((*minilp)->sx.i!=(*minirp)->sx.i)
		{
			//If the top is flat just see which end is leftmost
	
			if((*minilp)->sx.i>(*minirp)->sx.i)
			{
				led = FORWARDS;
				tempp = minilp;
				minilp = minirp;
				minirp = tempp;
			}
		}
		else
		{
			//Point to the downward end of the first line of the two edges
			//down from the top
	
			nindp = minirp+1;
			if(!*nindp)	nindp = nvertptr;
	
			pindp = minilp-1;
			if(!*pindp) pindp += vertexcount;
	
			//Calculate X and Y lengths from the top vertex to the end of the
			//first line down each edge; use those to compare slopes and see
			//which line is leftmost
	
			dxn = (*nindp)->sx.i-(*minilp)->sx.i;
			dyn = (*nindp)->sy.i-(*minilp)->sy.i;
	
			dxp = (*pindp)->sx.i-(*minirp)->sx.i;
			dyp = (*pindp)->sy.i-(*minirp)->sy.i;
	
			if((dxn*dyp)<(dyn*dxp))
			{
				led = FORWARDS;
				tempp = minilp;
				minilp = minirp;
				minirp = tempp;
			}
		}
	
		whll.length = maxy-miny+1;	//inclusive					//PD 21Nov96
		whll.starty = miny;
		whll.led	= led;
		whll.minilp	= minilp;
		whll.minirp	= minirp;
		whll.maxip	= maxip;
	
		//The actual scan conversion is poly type specific
		//Useful variables at this stage are:
		//
		//whll.length		=	total scan lines in polygon
		//whll.starty		=	top scan line of the polygon
		//
		//whll.led			=	direction to travel through the vertex
		//						list to scan the left edge of the poly
		//
		//whll.minilp		=	index to first left edge point
		//
		//whll.minirp		=	index to first right edge point
		//
		//whll.maxip		=	index of bottom point of the polygon
		//
	
		(this->*scanconvert)(whll);

		return;
	}

	//Flat poly code here

	whll.starty = miny;
	(this->*scanconvertflat)(whll);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drawsphere
//Author		Robert Slater
//Date			Fri 14 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::drawsphere()
{
	HLINELIST	whll;

	whll.minilp = nvertptr;

	(this->*scanconvert)(whll);
}

////////////////////////////////////////////////////////////////////////////////
//
//	GENERAL ROUTINES ie. screen clip, z-clip, cross product checks
//
////////////////////////////////////////////////////////////////////////////////


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setscale
//Author		Paul.   
//Date			Wed 1 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::setscale()
{
}

////////////////////////////////////////////////////////////////////////////////
//
//						PLAIN MAPPING POLY DRAW ROUTINE
//
////////////////////////////////////////////////////////////////////////////////

void polygon::Sparkle(SWord	x, SWord y, SWord colour)
{
/*	LogicalPtr	scradr;
	SWord		MinX,MaxX,MinY,MaxY;
	SWord		xmin, xmax, ymin, ymax;
	SWord		count;
	SLong		yoffset,yoffset2,xoffset;
	SLong		bpsl = currscreen->BytesPerScanLine;
	SLong		bpp = currscreen->BytesPerPixel;
	LogicalPtr	scrnbase = currscreen->logicalscreenptr;
	VERTEX		leftvertex,
				rightvertex;

	MinX = currscreen->PhysicalMinX;
	MaxX = MinX + currscreen->PhysicalWidth;

	MinY = currscreen->PhysicalMinY;
	MaxY = MinY + currscreen->PhysicalHeight;

	xmin = x - 2;
	xmax = x + 2;
	ymin = y - 2;
	ymax = y + 2;

	if (	((xmin < MinX) || (xmax >= MaxX))
		||	((ymin < MinY) || (ymax >= MaxY))	)
		return;

	currscreen->SetColour((Colour)(colour-2));

	horilinertn = currscreen->GetScanLineAddr(PLAIN);

	scradr = scrnbase + (bpsl * y);

	leftvertex.sx.i = xmin<<16;
	rightvertex.sx.i = xmax<<16;

 	ASM_Call(horilinertn,scradr,leftvertex,rightvertex);

	scradr = scrnbase + (bpsl * ymin);

	leftvertex.sx.i = x<<16;
	rightvertex.sx.i = x<<16;

	for (count=0; count < 5; count++)
	{
 		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
		scradr += bpsl;
	}

	scradr = scrnbase + (bpsl * y) + (bpp * x);
	*scradr = colour;
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		chazescancnvrt
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
void polygon::chazescancnvrt(HLINELIST &hll)
{
/*	VERTEX_PTR	*vptr = hll.minilp;
	SWord	x = (*vptr)->sx.f / (Float)currscreen->virtualXscale;
	SWord	y = (*vptr)->sy.f / (Float)currscreen->virtualYscale;
	SWord	Radius = SphereRadius / currscreen->virtualXscale;

	if ((Radius > 0) && (Radius < 256))
	{
		SWord 		cos_ang;
		SLong		dx, dy;
		SLong		xmax, y1, ymin, ymax;
		SLong		xmin, xpos2, ypos, ypos2, xsave;
		LogicalPtr	scradr;
		LogicalPtr	scradr2;
		SWord		MinX,MaxX,MinY,MaxY;
		SLong		yoffset,yoffset2,xoffset;
		SLong		bpsl = currscreen->BytesPerScanLine;
		SLong		bpp = currscreen->BytesPerPixel;
		LogicalPtr	scrnbase = currscreen->logicalscreenptr;
		SLong		dystep, dyfrac;

		VERTEX	leftvertex,
				rightvertex;

		MinX = currscreen->PhysicalMinX;
		MaxX = MinX + currscreen->PhysicalWidth - 4;

		MinY = currscreen->PhysicalMinY;
		MaxY = MinY + currscreen->PhysicalHeight;

		xmin = x - Radius;
		xmax = x + Radius;
		ypos = y;
		ymin = y - Radius;
		ymax = y + Radius;

		if (	((xmax >= MaxX) || (xmin < MinX))			//RJS 18Feb98
			||	((ymin < MinY) || (ymax >= MaxY))	)		//RJS 18Feb98
			return;											//RJS 18Feb98

		currscreen->SetHeatHaze(1);
		horilinertn = currscreen->GetScanLineAddr(PLAIN);

		dystep = 65536 / Radius;							//RJS 18Feb98
		dyfrac = dystep;									//RJS 18Feb98
															//RJS 18Feb98
		ypos = y+1;											//RJS 18Feb98
		ypos2 = y;											//RJS 18Feb98

		yoffset = bpsl * ypos;
		yoffset2 = bpsl * ypos2;

		scradr = scrnbase + yoffset;
		scradr2 = scrnbase + yoffset2;

		for (dy = 1; dy <= Radius; dy++)
		{
			cos_ang = Circle_CosTable[dyfrac>>8];

			dx = (Radius*cos_ang)>>15;

			xmin = x - dx;
			xmax = x + dx;									//RJS 18Feb98

			// Main clipping moved to above....

			leftvertex.sx.i = xmin<<16;
			rightvertex.sx.i = xmax<<16;

			ASM_Call(horilinertn,scradr,leftvertex,rightvertex);

			leftvertex.sx.i = xmin<<16;
			rightvertex.sx.i = xmax<<16;

			ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);

			dyfrac += dystep;

			scradr += bpsl;
			scradr2 -= bpsl;

			ypos++;
			ypos2--;
		}

		currscreen->SetHeatHaze(0);
	}
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		cspherescancnvrt
//Author		Robert Slater
//Date			Fri 14 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::cspherescancnvrt(HLINELIST &hll)
{
/*	VERTEX_PTR	*vptr = hll.minilp;
	SWord	x = (*vptr)->sx.f / (Float)currscreen->virtualXscale;
	SWord	y = (*vptr)->sy.f / (Float)currscreen->virtualYscale;
	SWord	Radius = SphereRadius / currscreen->virtualXscale;

	if (Radius > 0)
	{
		SWord 		cos_ang;
		SLong		dx, dy;
		SLong		xmax, y1, ymin, ymax;
		SLong		xpos, xpos2, ypos, ypos2, xsave;
		LogicalPtr	scradr;
		LogicalPtr	scradr2;
		SWord		MinX,MaxX,MinY,MaxY;
		SLong		yoffset,yoffset2,xoffset;
		SLong		bpsl = currscreen->BytesPerScanLine;
		SLong		bpp = currscreen->BytesPerPixel;
		LogicalPtr	scrnbase = currscreen->logicalscreenptr;
		SLong		dystep, dyfrac;

		VERTEX	leftvertex,
				rightvertex;

		MinX = currscreen->PhysicalMinX;
		MaxX = MinX + currscreen->PhysicalWidth;

		MinY = currscreen->PhysicalMinY;
		MaxY = MinY + currscreen->PhysicalHeight;

		xpos = x - Radius;
		xmax = x + Radius + 1;
		ypos = y;
		ymin = y - Radius;
		ymax = y + Radius;

		if (	((xpos >= MaxX) || (xmax < MinX))
			||	((ymin >= MaxY) || (ymax < MinY))	)
			return;

		if (xpos < MinX)
			xpos = MinX;

		if (xmax >= MaxX)
			xmax = MaxX -1;

		if ((ypos >= MinY) && (ypos < MaxY))
		{
			yoffset = bpsl * ypos;
			scradr = scrnbase + yoffset;

			leftvertex.sx.i = xpos<<16;
			rightvertex.sx.i = xmax<<16;

 			ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
		}

		dystep = 65536 / Radius;
		dyfrac = dystep;

		ypos = y+1;
		ypos2 = y-1;

		yoffset = bpsl * ypos;
		yoffset2 = bpsl * ypos2;

		scradr = scrnbase + yoffset;
		scradr2 = scrnbase + yoffset2;

		for (dy = 1; dy <= Radius; dy++)
		{
			cos_ang = Circle_CosTable[dyfrac>>8];

			dx = (Radius*cos_ang)>>15;

			xpos = x - dx;
			xmax = x + dx + 1;

			if ((xpos < MaxX) || (xmax > MinX))
			{
				if (xpos < MinX)
					xpos = MinX;

				if (xmax >= MaxX)
					xmax = MaxX -1;

				if ((ypos >= MinY) && (ypos < MaxY))
				{
					leftvertex.sx.i = xpos<<16;
					rightvertex.sx.i = xmax<<16;

 					ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
				}

				if ((ypos2 >= MinY) && (ypos2 < MaxY))
				{
					leftvertex.sx.i = xpos<<16;
					rightvertex.sx.i = xmax<<16;

 					ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
				}
			}

			dyfrac += dystep;

			scradr += bpsl;
			scradr2 -= bpsl;

			ypos++;
			ypos2--;
		}
	}
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		csphfadescancnvrt
//Author		Robert Slater
//Date			Tue 18 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::csphfadescancnvrt(HLINELIST &hll)
{
/*	VERTEX_PTR	*vptr = hll.minilp;
	SWord	x = (*vptr)->sx.f / (Float)currscreen->virtualXscale;
	SWord	y = (*vptr)->sy.f / (Float)currscreen->virtualYscale;
	SWord	Radius = SphereRadius / currscreen->virtualXscale;

	if (Radius < 512)
	{
		SWord 		cos_ang;
		SLong		dx, dy ,dx2;
		SLong		xmax, y1, ymin, ymax;
		SLong		xmin, xmin2, ypos, ypos2, xsave,xmax2;
		LogicalPtr	scradr;
		LogicalPtr	scradr2;
		SWord		MinX,MaxX,MinY,MaxY;
		SLong		yoffset,yoffset2,xoffset;
		SLong		bpsl = currscreen->BytesPerScanLine;
		SLong		bpp = currscreen->BytesPerPixel;
		LogicalPtr	scrnbase = currscreen->logicalscreenptr;
		SWord		Rads[5];
		SWord		RadMax;
		SWord		dxx[513];
		SLong		dmax;
		SLong		dyfrac, dystep;
		VERTEX	leftvertex,
				rightvertex;
		UWord	depth = SphereDepth;
		int					i;

		MinX = currscreen->PhysicalMinX;
		MaxX = MinX + currscreen->PhysicalWidth;

		MinY = currscreen->PhysicalMinY;
		MaxY = MinY + currscreen->PhysicalHeight;

		if (Radius > 0)
		{
			if (Radius < 3)
			{
				Radius = 2;
				RadMax = 2;

				depth -= 75;
			}
			else
			{
				if (Radius < 5)
					depth -= 25;

				Rads[0] = 0;
				Rads[1] = (Radius*3)>>2;
				Rads[2] = Rads[1] + ((Radius-Rads[1])>>1);
				Rads[3] = Rads[2] + ((Radius-Rads[2])>>1);
				Rads[4] = Radius;

				Radius = Rads[1];
				RadMax = Rads[4];

				//horilinertn = currscreen->GetScanLineAddr(PLAIN);
			}

			if (depth <= 0)
				return;

			currscreen->SetTransparency(depth);					//RJS 30Mar98

			horilinertn = currscreen->GetScanLineAddr(PLAIN);

			xmin = x - Radius;
			xmax = x + Radius + 1;
			ymin = y - Radius;
			ymax = y + Radius;

			if (	((xmin >= MaxX) || (xmax < MinX))
				||	((ymin >= MaxY) || (ymax < MinY))	)
				return;

			dystep = 65536 / Radius;
			dyfrac = dystep;

			ypos = y+1;
			ypos2 = y;

			yoffset = bpsl * ypos;
			yoffset2 = bpsl * ypos2;

			scradr = scrnbase + yoffset;
			scradr2 = scrnbase + yoffset2;

			for (dy = 1; dy <= RadMax; dy++)
			{
				if (dyfrac > 65536)
					dxx[dy] = 0;
				else
				{
					cos_ang = Circle_CosTable[dyfrac>>8];
					dx = dxx[dy] = (Radius*cos_ang)>>15;

					xmin = x - dx;
					xmax = x + dx;

					if ((xmin < MaxX) && (xmax > MinX))
					{
						if (xmin < MinX)
							xmin = MinX;

						if (xmax >= MaxX)
							xmax = MaxX -1;

						if ((ypos >= MinY) && (ypos < MaxY))
						{
							leftvertex.sx.i = xmin<<16;
							rightvertex.sx.i = xmax<<16;

 							ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
						}

						if ((ypos2 >= MinY) && (ypos2 < MaxY))
						{
							leftvertex.sx.i = xmin<<16;
							rightvertex.sx.i = xmax<<16;

 							ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
						}
					}
				}

				dyfrac += dystep;
				ypos++;
				ypos2--;

				scradr += bpsl;
				scradr2 -= bpsl;
			}

			dmax = 5;
			if (depth != SMOKED_LIGHT)
			{
				SLong	poohead;

				depth -= 25;
				if ((Rads[4] - Rads[3]) < 2)
				{
					depth -= 25;
					dmax = 3;
				}

				dmax = (100 / (100 - depth)) + 1;

				RadMax = Rads[4];

				for (i=2; i < dmax; i++)
				{
					Radius = Rads[i];

					currscreen->SetTransparency(depth);
					horilinertn = currscreen->GetScanLineAddr(PLAIN);

					ypos = y+1;
					ypos2 = y;

					yoffset = bpsl * ypos;
					yoffset2 = bpsl * ypos2;

					scradr = scrnbase + yoffset;
					scradr2 = scrnbase + yoffset2;

					dystep = 65536 / Radius;
					dyfrac = dystep;

					for (dy = 1; dy <= Radius; dy++)
					{
						dx2 = dxx[dy];
						dx = dxx[dy] = (Radius*Circle_CosTable[dyfrac>>8])>>15;

						xmin = x - dx;
						if (dx2)
						{
							xmax = x - dx2 - 1;

							if ((xmin < MaxX) && (xmax > MinX))
							{
								if (xmin < MinX)
									xmin = MinX;

								if (xmax >= MaxX)
									xmax = MaxX -1;

								if ((ypos >= MinY) && (ypos < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
								}

								if ((ypos2 >= MinY) && (ypos2 < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
								}
							}

							xmin = x + dx2+1;
							xmax = x + dx;

							if ((xmin < MaxX) && (xmax > MinX))
							{
								if (xmin < MinX)
									xmin = MinX;

								if (xmax >= MaxX)
									xmax = MaxX -1;

								if ((ypos >= MinY) && (ypos < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
								}

								if ((ypos2 >= MinY) && (ypos2 < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
								}
							}
						}
						else
						{
							xmax = x + dx + 1;
							if ((xmin < MaxX) && (xmax > MinX))
							{
								if (xmin < MinX)
									xmin = MinX;

								if (xmax >= MaxX)
									xmax = MaxX -1;

								if ((ypos >= MinY) && (ypos < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
								}

								if ((ypos2 >= MinY) && (ypos2 < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
								}
							}
						}

						dyfrac += dystep;

						ypos++;
						ypos2--;

						scradr += bpsl;
						scradr2 -= bpsl;
					}

					depth -= 25;
				}
			}
		}
		else
		{
			if (Radius == 0)
			{
				if (	((x >= MaxX) || (x <= MinX))
					||	((y >= MaxY) || (y <= MinY))	)
					return;

				currscreen->SetTransparency(SMOKED_ON);

				scradr = scrnbase + (bpsl * y);

				leftvertex.sx.i = x<<16;
				rightvertex.sx.i = x<<16;

				ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
			}
		}
	}
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		csphlumscancnvrt
//Author		Robert Slater
//Date			Tue 20 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::csphlumscancnvrt(HLINELIST &hll)
{
/*	VERTEX_PTR	*vptr = hll.minilp;
	SWord	x = (*vptr)->sx.f / (Float)currscreen->virtualXscale;
	SWord	y = (*vptr)->sy.f / (Float)currscreen->virtualYscale;
	SWord	Radius = SphereRadius / currscreen->virtualXscale;

	if (Radius < 512)
	{
		SWord 		cos_ang;
		SLong		dx, dy ,dx2;
		SLong		xmax, y1, ymin, ymax;
		SLong		xmin, xmin2, ypos, ypos2, xsave,xmax2;
		LogicalPtr	scradr;
		LogicalPtr	scradr2;
		SWord		MinX,MaxX,MinY,MaxY;
		SLong		yoffset,yoffset2,xoffset;
		SLong		bpsl = currscreen->BytesPerScanLine;
		SLong		bpp = currscreen->BytesPerPixel;
		LogicalPtr	scrnbase = currscreen->logicalscreenptr;
		SWord		Rads[5];
		SWord		RadMax;
		SWord		dxx[513];
		SLong		dmax;
		SLong		dyfrac, dystep;
		VERTEX	leftvertex,
				rightvertex;
		SWord	depth = SphereDepth;
		int					i;

		MinX = currscreen->PhysicalMinX;
		MaxX = MinX + currscreen->PhysicalWidth;

		MinY = currscreen->PhysicalMinY;
		MaxY = MinY + currscreen->PhysicalHeight;

		if (Radius > 0)
		{
			if (Radius < 3)
			{
				Radius = 2;
				RadMax = 2;

				depth = 2;
			}
			else
			{
				if (Radius < 5)
					depth = 3;

				Rads[0] = 0;
				Rads[1] = (Radius*3)>>2;
				Rads[2] = Rads[1] + ((Radius-Rads[1])>>1);
				Rads[3] = Rads[2] + ((Radius-Rads[2])>>1);
				Rads[4] = Radius;

				Radius = Rads[1];
				RadMax = Rads[4];
			}

			if (depth < 0)
				depth = 0;

			currscreen->SetLuminosity(depth);

			horilinertn = currscreen->GetScanLineAddr(PLAIN);

			xmin = x - Radius;
			xmax = x + Radius + 1;
			ymin = y - Radius;
			ymax = y + Radius;

			if (	((xmin >= MaxX) || (xmax < MinX))
				||	((ymin >= MaxY) || (ymax < MinY))	)
				return;

			dystep = 65536 / Radius;
			dyfrac = dystep;

			ypos = y+1;
			ypos2 = y;

			yoffset = bpsl * ypos;
			yoffset2 = bpsl * ypos2;

			scradr = scrnbase + yoffset;
			scradr2 = scrnbase + yoffset2;

			for (dy = 1; dy <= RadMax; dy++)
			{
				if (dyfrac > 65536)
					dxx[dy] = 0;
				else
				{
					cos_ang = Circle_CosTable[dyfrac>>8];
					dx = dxx[dy] = (Radius*cos_ang)>>15;

					xmin = x - dx;
					xmax = x + dx;

					if ((xmin < MaxX) && (xmax > MinX))
					{
						if (xmin < MinX)
							xmin = MinX;

						if (xmax >= MaxX)
							xmax = MaxX -1;

						if ((ypos >= MinY) && (ypos < MaxY))
						{
							leftvertex.sx.i = xmin<<16;
							rightvertex.sx.i = xmax<<16;

 							ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
						}

						if ((ypos2 >= MinY) && (ypos2 < MaxY))
						{
							leftvertex.sx.i = xmin<<16;
							rightvertex.sx.i = xmax<<16;

 							ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
						}
					}
				}

				dyfrac += dystep;
				ypos++;
				ypos2--;

				scradr += bpsl;
				scradr2 -= bpsl;
			}

			dmax = 5;
			if (depth != LUM_ONE)
			{
				SLong	poohead;

				depth -= 1;
				if ((Rads[4] - Rads[3]) < 2)
				{
					depth -= 1;
					dmax = 3;
				}

				switch (depth)
				{
				case 0:
				case 1:
				case 2:
					dmax = 0;
					break;
				case 3:
					dmax = 4;
					break;
				default:
					dmax = 5;
					break;
				}

				RadMax = Rads[4];

				for (i=2; i < dmax; i++)
				{
					Radius = Rads[i];

					currscreen->SetLuminosity(depth);
					horilinertn = currscreen->GetScanLineAddr(PLAIN);

					ypos = y+1;
					ypos2 = y;

					yoffset = bpsl * ypos;
					yoffset2 = bpsl * ypos2;

					scradr = scrnbase + yoffset;
					scradr2 = scrnbase + yoffset2;

					dystep = 65536 / Radius;
					dyfrac = dystep;

					for (dy = 1; dy <= Radius; dy++)
					{
						dx2 = dxx[dy];
						dx = dxx[dy] = (Radius*Circle_CosTable[dyfrac>>8])>>15;

						xmin = x - dx;
						if (dx2)
						{
							xmax = x - dx2 - 1;

							if ((xmin < MaxX) && (xmax > MinX))
							{
								if (xmin < MinX)
									xmin = MinX;

								if (xmax >= MaxX)
									xmax = MaxX -1;

								if ((ypos >= MinY) && (ypos < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
								}

								if ((ypos2 >= MinY) && (ypos2 < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
								}
							}

							xmin = x + dx2+1;
							xmax = x + dx;

							if ((xmin < MaxX) && (xmax > MinX))
							{
								if (xmin < MinX)
									xmin = MinX;

								if (xmax >= MaxX)
									xmax = MaxX -1;

								if ((ypos >= MinY) && (ypos < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
								}

								if ((ypos2 >= MinY) && (ypos2 < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
								}
							}
						}
						else
						{
							xmax = x + dx + 1;
							if ((xmin < MaxX) && (xmax > MinX))
							{
								if (xmin < MinX)
									xmin = MinX;

								if (xmax >= MaxX)
									xmax = MaxX -1;

								if ((ypos >= MinY) && (ypos < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
								}

								if ((ypos2 >= MinY) && (ypos2 < MaxY))
								{
									leftvertex.sx.i = xmin<<16;
									rightvertex.sx.i = xmax<<16;

 									ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
								}
							}
						}

						dyfrac += dystep;

						ypos++;
						ypos2--;

						scradr += bpsl;
						scradr2 -= bpsl;
					}

					depth -= 1;
				}
			}
		}
		else
		{
			if (Radius == 0)
			{
				if (	((x >= MaxX) || (x <= MinX))
					||	((y >= MaxY) || (y <= MinY))	)
					return;

				currscreen->SetLuminosity(4);

				scradr = scrnbase + (bpsl * y);

				leftvertex.sx.i = x<<16;
				rightvertex.sx.i = x<<16;

				ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
			}
		}
	}
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		chalofadescancnvrt
//Author		Robert Slater
//Date			Fri 16 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::chalofadescancnvrt(HLINELIST &hll)
{
/*	VERTEX_PTR	*vptr = hll.minilp;
	SWord	x = (*vptr)->sx.f / (Float)currscreen->virtualXscale;
	SWord	y = (*vptr)->sy.f / (Float)currscreen->virtualYscale;
	SWord	Radius = SphereRadius / currscreen->virtualXscale;
	SWord	HWidth = HaloWidth / currscreen->virtualXscale;

	if ((Radius > 0) && (Radius < 512))
	{
		SWord 		cos_ang;
		SLong		dx, dy ,dx2;
		SLong		xmax, y1, ymin, ymax;
		SLong		xmin, xmin2, ypos, ypos2, xsave,xmax2;
		LogicalPtr	scradr;
		LogicalPtr	scradr2;
		SWord		MinX,MaxX,MinY,MaxY;
		SLong		yoffset,yoffset2,xoffset;
		SLong		bpsl = currscreen->BytesPerScanLine;
		SLong		bpp = currscreen->BytesPerPixel;
		LogicalPtr	scrnbase = currscreen->logicalscreenptr;
		SWord		dxx[513];
		SWord		dxx2[513];
		SLong		dmax;
		SLong		dyfracIn, dystepIn;
		SLong		dyfracOut, dystepOut;
		VERTEX	leftvertex,
				rightvertex;
		UWord	depth = SphereDepth;
		int					i;

		if (HWidth < 1)
			HWidth = 1;

		MinX = currscreen->PhysicalMinX;
		MaxX = MinX + currscreen->PhysicalWidth;

		MinY = currscreen->PhysicalMinY;
		MaxY = MinY + currscreen->PhysicalHeight;

		if (Radius < 3)
		{
			Radius = 2;
			depth -= 2;
		}
		else
		{
			if (Radius < 5)
				depth -= 1;
		}

		if (depth <= 0)
			return;

		if (depth > LUM_MAX)
			currscreen->SetLuminosity(LUM_OFF);
		else
			currscreen->SetLuminosity(depth);

		horilinertn = currscreen->GetScanLineAddr(PLAIN);

		xmin = x - Radius - 1;
		xmax = x + Radius + 1;
		ymin = y - Radius;
		ymax = y + Radius;

		if (	((xmin >= MaxX) || (xmax < MinX))
			||	((ymin >= MaxY) || (ymax < MinY))	)
			return;

		int		RadiusIn = Radius - HWidth;
		if (RadiusIn < 1)
			RadiusIn = 1;

		dystepIn = 65536 / RadiusIn;
		dyfracIn = dystepIn;

		dystepOut = 65536 / Radius;
		dyfracOut = dystepOut;

		ypos = y+1;
		ypos2 = y;

		yoffset = bpsl * ypos;
		yoffset2 = bpsl * ypos2;

		scradr = scrnbase + yoffset;
		scradr2 = scrnbase + yoffset2;

		for (dy = 1; dy <= Radius; dy++)
		{
			dx = (Radius*Circle_CosTable[dyfracOut>>8])>>15;
			dxx[dy] = dx + 1;

			xmin = x - dx;

			if (dyfracIn > 65536)
			{
				dxx2[dy] = 0;

				xmax = x + dx;
				if ((xmin < MaxX) && (xmax > MinX))
				{
					if (xmin < MinX)
						xmin = MinX;

					if (xmax >= MaxX)
						xmax = MaxX -1;

					if ((ypos >= MinY) && (ypos < MaxY))
					{
						leftvertex.sx.i = xmin<<16;
						rightvertex.sx.i = xmax<<16;

 						ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
					}

					if ((ypos2 >= MinY) && (ypos2 < MaxY))
					{
						leftvertex.sx.i = xmin<<16;
						rightvertex.sx.i = xmax<<16;

 						ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
					}
				}
			}
			else
			{
				dx2 = (RadiusIn*Circle_CosTable[dyfracIn>>8])>>15;
				dxx2[dy] = dx2 - 1;

				xmax = x - dx2;

				if ((xmin < MaxX) && (xmax > MinX))
				{
					if (xmin < MinX)
						xmin = MinX;

					if (xmax >= MaxX)
						xmax = MaxX -1;

					if ((ypos >= MinY) && (ypos < MaxY))
					{
						leftvertex.sx.i = xmin<<16;
						rightvertex.sx.i = xmax<<16;

 						ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
					}

					if ((ypos2 >= MinY) && (ypos2 < MaxY))
					{
						leftvertex.sx.i = xmin<<16;
						rightvertex.sx.i = xmax<<16;

 						ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
					}
				}

				xmin = x + dx2;
				xmax = x + dx;

				if ((xmin < MaxX) && (xmax > MinX))
				{
					if (xmin < MinX)
						xmin = MinX;

					if (xmax >= MaxX)
						xmax = MaxX -1;

					if ((ypos >= MinY) && (ypos < MaxY))
					{
						leftvertex.sx.i = xmin<<16;
						rightvertex.sx.i = xmax<<16;

 						ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
					}

					if ((ypos2 >= MinY) && (ypos2 < MaxY))
					{
						leftvertex.sx.i = xmin<<16;
						rightvertex.sx.i = xmax<<16;

 						ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
					}
				}
			}

			dyfracIn += dystepIn;
			dyfracOut += dystepOut;

			ypos++;
			ypos2--;

			scradr += bpsl;
			scradr2 -= bpsl;
		}

 		depth -= 1;
 		if (depth > 0)
 		{
 			SWord	dxNext,dx2Next;
 			SWord	RealDx, RealDx2;
 
 			scradr = scrnbase + yoffset;
 			scradr2 = scrnbase + yoffset2;
 
 			ypos = y+1;
 			ypos2 = y;

 			dxx[Radius+1] = 0;
 			dxx2[Radius+1] = 0;

			dxx[0] = 0;
 			dxx2[0] = 0;

 			currscreen->SetLuminosity(depth);
 			horilinertn = currscreen->GetScanLineAddr(PLAIN);
 
 			for (dy = 1; dy <= Radius; dy++)
 			{
 				dx = dxx[dy];
 				dx2 = dxx2[dy];
 
 				dxNext = dxx[dy-1];
 				dx2Next = dxx2[dy+1];
 
 				RealDx = (dxNext + dx)>>1;
				if (!RealDx)
					RealDx = 1;
 
 				if (!dx2)
 				{
 					xmin = x - RealDx;
 					xmax = x - dx;
 
 					if ((xmin < MaxX) && (xmax > MinX))
 					{
 						if (xmin < MinX)
 							xmin = MinX;
 
 						if (xmax >= MaxX)
 							xmax = MaxX -1;
 
 						if ((ypos >= MinY) && (ypos < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
 						}
 
 						if ((ypos2 >= MinY) && (ypos2 < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
 						}
 					}
 
 					xmin = x + dx;
 					xmax = x + RealDx;
 
 					if ((xmin < MaxX) && (xmax > MinX))
 					{
 						if (xmin < MinX)
 							xmin = MinX;
 
 						if (xmax >= MaxX)
 							xmax = MaxX -1;
 
 						if ((ypos >= MinY) && (ypos < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
 						}
 
 						if ((ypos2 >= MinY) && (ypos2 < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
 						}
 					}
 				}
 				else
 				{
 					RealDx2 = (dx2Next + dx2)>>1;
					if (!RealDx2)
						RealDx2 = 1;
 
 					xmin = x - RealDx;
 					xmax = x - dx;
 
 					if ((xmin < MaxX) && (xmax > MinX))
 					{
 						if (xmin < MinX)
 							xmin = MinX;
 
 						if (xmax >= MaxX)
 							xmax = MaxX -1;
 
 						if ((ypos >= MinY) && (ypos < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
 						}
 
 						if ((ypos2 >= MinY) && (ypos2 < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
 						}
 					}
 
 					xmin = x + dx;
 					xmax = x + RealDx;
 
 					if ((xmin < MaxX) && (xmax > MinX))
 					{
 						if (xmin < MinX)
 							xmin = MinX;
 
 						if (xmax >= MaxX)
 							xmax = MaxX -1;
 
 						if ((ypos >= MinY) && (ypos < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
 						}
 
 						if ((ypos2 >= MinY) && (ypos2 < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
 						}
 					}
 
 					xmin = x - dx2;
 					xmax = x - RealDx2;
 
 					if ((xmin < MaxX) && (xmax > MinX))
 					{
 						if (xmin < MinX)
 							xmin = MinX;
 
 						if (xmax >= MaxX)
 							xmax = MaxX -1;
 
 						if ((ypos >= MinY) && (ypos < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
 						}
 
 						if ((ypos2 >= MinY) && (ypos2 < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
 						}
 					}
 
 					xmin = x + RealDx2;
 					xmax = x + dx2;
 
 					if ((xmin < MaxX) && (xmax > MinX))
 					{
 						if (xmin < MinX)
 							xmin = MinX;
 
 						if (xmax >= MaxX)
 							xmax = MaxX -1;
 
 						if ((ypos >= MinY) && (ypos < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
 						}
 
 						if ((ypos2 >= MinY) && (ypos2 < MaxY))
 						{
 							leftvertex.sx.i = xmin<<16;
 							rightvertex.sx.i = xmax<<16;
 
  							ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
 						}
 					}
 				}
 
 				ypos++;
 				ypos2--;
 
 				scradr += bpsl;
 				scradr2 -= bpsl;
 			}
 		}
	}
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		cpolyscancnvrt
//Author		Paul.   
//Date			Thu 19 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::cpolyscancnvrt(HLINELIST &hll)
{
	ROWANSURFACEDESC rsd;

	VERTEX_PTR	*cindrp,*cindlp;								//PD 29Jan96
	VERTEX_PTR	*nindrp,*nindlp;								//PD 29Jan96

	UWord*	scradr;

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;

	SLong	ld_sx,rd_sx;

	SLong	last_leftsx,last_rightsx;							//PD 12Apr96

	currscreen->DoLockScr(&rsd);

	scradr = (UWord*)(ULong(rsd.lpSurface)+hll.starty*rsd.lPitch);

	//Initialise left edge interpolation stuff

	nindlp = hll.minilp;

	do
	{
		cindlp = nindlp;
		switch(hll.led)
		{
			case FORWARDS:
				nindlp++;
				if(!*nindlp) nindlp = nvertptr;
				break;
			case BACKWARDS:
				nindlp--;
				if(!*nindlp) nindlp += vertexcount;				//PD 16Feb96
				break;
		}
		leftvertex.sx.i = (*cindlp)->bigsx.i;

		ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
	}
	while(!ld_sy);

	ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;		//PD 21Nov96

	ld_sy++;													//PD 21Nov96

	//Initialise right edge interpolation stuff

	nindrp = hll.minirp;

	do
	{
		cindrp = nindrp;
		switch(hll.led)
		{
			case BACKWARDS:
				nindrp++;
				if(!*nindrp) nindrp = nvertptr;
				break;
			case FORWARDS:
				nindrp--;
				if(!*nindrp) nindrp += vertexcount;
				break;
		}
		rightvertex.sx.i = (*cindrp)->bigsx.i;

		rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
	}
	while(!rd_sy);

	rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;		//PD 21Nov96

	rd_sy++;													//PD 21Nov96

	last_leftsx = leftvertex.sx.i;								//PD 12Apr96
	last_rightsx= rightvertex.sx.i;								//PD 12Apr96

	//Now start the real DDA stuff

	while(hll.length--)
	{
		//Do a single scan line

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		//index left and right by left and right delta sx

		ld_sy--;

		if(!ld_sy)
		{
			//get next left index

			do
			{
				cindlp = nindlp;
				switch(hll.led)
				{
					case FORWARDS:
						nindlp++;
						if(!*nindlp) nindlp = nvertptr;
						break;
					case BACKWARDS:
						nindlp--;
						if(!*nindlp) nindlp += vertexcount;		//PD 16Feb96
						break;
				}
				ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
			}
			while(!ld_sy);

			leftvertex.sx.i = (*cindlp)->bigsx.i;
			ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;
		}

		rd_sy--;

		if(!rd_sy)
		{
			//get next right index

			do
			{
				cindrp = nindrp;
				switch(hll.led)
				{
					case BACKWARDS:
						nindrp++;
						if(!*nindrp) nindrp = nvertptr;
						break;
					case FORWARDS:
						nindrp--;
						if(!*nindrp) nindrp += vertexcount;
						break;
				}
				rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
			}
			while(!rd_sy);

			rightvertex.sx.i = (*cindrp)->bigsx.i;
			rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;
		}
	
		leftvertex.sx.i += ld_sx;
		rightvertex.sx.i += rd_sx;

		if (leftvertex.sx.i>last_rightsx)
			leftvertex.sx.i = last_rightsx;

		if (rightvertex.sx.i<last_leftsx)
			rightvertex.sx.i = last_leftsx;

		last_leftsx = leftvertex.sx.i;
		last_rightsx= rightvertex.sx.i;

		scradr=(UWord*)(ULong(scradr)+rsd.lPitch);
	}
	currscreen->DoUnlockScr(&rsd);
}

////////////////////////////////////////////////////////////////////////////////
//
//						GOURAUD POLY DRAW ROUTINE
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		gpolyscancnvrt
//Author		Paul.   
//Date			Thu 19 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::gpolyscancnvrt(HLINELIST &hll)
{
	ROWANSURFACEDESC rsd;

	VERTEX_PTR	*cindrp,*cindlp;								//PD 29Jan96
	VERTEX_PTR	*nindrp,*nindlp;								//PD 29Jan96

	UWord*	scradr;											//JIM 12Dec95

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;

	SLong	ld_sx,rd_sx;

	SLong	ld_in,rd_in;

	currscreen->DoLockScr(&rsd);

	scradr = (UWord*)(ULong(rsd.lpSurface)+hll.starty*rsd.lPitch);

	//Initialise left edge interpolation stuff

	nindlp = hll.minilp;

	do
	{
		cindlp = nindlp;
		switch(hll.led)
		{
			case FORWARDS:
				nindlp++;
				if(!*nindlp) nindlp = nvertptr;
				break;
			case BACKWARDS:
				nindlp--;
				if(!*nindlp) nindlp += vertexcount;
				break;
		}
		leftvertex.sx.i = (*cindlp)->bigsx.i;
		leftvertex.intensity = (*cindlp)->intensity;

		ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
	}
	while(!ld_sy);

	ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;		//PD 21Nov96
	ld_in = ((*nindlp)->intensity-(*cindlp)->intensity)/ld_sy;

	ld_sy++;													//PD 21Nov96

	//Initialise right edge interpolation stuff

	nindrp = hll.minirp;

	do
	{
		cindrp = nindrp;
		switch(hll.led)
		{
			case BACKWARDS:
				nindrp++;
				if(!*nindrp) nindrp = nvertptr;
				break;
			case FORWARDS:
				nindrp--;
				if(!*nindrp) nindrp += vertexcount;
				break;
		}
		rightvertex.sx.i = (*cindrp)->bigsx.i;
		rightvertex.intensity = (*cindrp)->intensity;		//PD 31Oct95

		rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
	}
	while(!rd_sy);

	rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;		//PD 21Nov96
	rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;

	rd_sy++;													//PD 21Nov96

	//Now start the real DDA stuff

	leftvertex.sy.i = hll.starty;									//PD 10Jun96

	while(hll.length--)
	{
		//Do a single scan line

		SLong	lin,rin;

		lin = leftvertex.intensity;
		rin = rightvertex.intensity;

		if (lin<0)	leftvertex.intensity=0;
		if (rin<0)	rightvertex.intensity=0;

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		leftvertex.intensity=lin;
		rightvertex.intensity=rin;

		//index left and right by left and right delta sx

		ld_sy--;

		if(!ld_sy)
		{
			//get next left index

			do
			{
				cindlp = nindlp;
				switch(hll.led)
				{
					case FORWARDS:
						nindlp++;
						if(!*nindlp) nindlp = nvertptr;
						break;
					case BACKWARDS:
						nindlp--;
						if(!*nindlp) nindlp += vertexcount;
						break;
				}
				leftvertex.intensity = (*cindlp)->intensity;

				ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
			}
			while(!ld_sy);

			leftvertex.sx.i = (*cindlp)->bigsx.i;
			ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;
			ld_in = ((*nindlp)->intensity-(*cindlp)->intensity)/ld_sy;
		}

		rd_sy--;

		if(!rd_sy)
		{
			//get next right index

			do
			{
				cindrp = nindrp;
				switch(hll.led)
				{
					case BACKWARDS:
						nindrp++;
						if(!*nindrp) nindrp = nvertptr;
						break;
					case FORWARDS:
						nindrp--;
						if(!*nindrp) nindrp += vertexcount;
						break;
				}
				rightvertex.intensity = (*cindrp)->intensity;

				rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
			}
			while(!rd_sy);

			rightvertex.sx.i = (*cindrp)->bigsx.i;
			rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;
			rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;
		}
	
		leftvertex.sx.i += ld_sx;
		rightvertex.sx.i += rd_sx;

		leftvertex.intensity += ld_in;
		rightvertex.intensity += rd_in;

		leftvertex.sy.i++;										//PD 10Jun96

		scradr=(UWord*)(ULong(scradr)+rsd.lPitch);
	}
	currscreen->DoUnlockScr(&rsd);
}

////////////////////////////////////////////////////////////////////////////////
//
//						IMAGE MAPPING POLY DRAW ROUTINE
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ispherescancnvrt
//Author		Robert Slater
//Date			Fri 14 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::ispherescancnvrt(HLINELIST &hll)
{
	ROWANSURFACEDESC rsd;

	currscreen->DoLockScr(&rsd);

	VERTEX_PTR	*vptr=hll.minilp;

	SWord	x=(*vptr)->sx.f/currscreen->virtualXscale,
			y=(*vptr)->sy.f/currscreen->virtualYscale,
			Radius=SphereRadius/currscreen->virtualXscale;

	if (Radius>0)
	{
		VERTEX		leftvertex,rightvertex;
		SLong		dx,dy,
					xmax,y1,ymin,ymax,
					xpos,xpos2,ypos,ypos2,xsave,
					xoffset,
					iwidth,iheight,iyscale,
					ixpos,ixmax,iypos,iypos2,ix,iy,idx,
					dyfrac,dystep;
		SWord 		cos_ang,
					MinX,MaxX,MinY,MaxY;
		UWord		*scradr,*scradr2;

		iwidth=((*vptr)->ix.i-SphIxStart)/2;
		iheight=((*vptr)->iy.i-SphIyStart)/2;
		ix=SphIxStart+iwidth;
		iy=SphIyStart+iheight;

		MinX=0;		MaxX=rsd.dwWidth;
		MinY=0;		MaxY=rsd.dwHeight;

		xpos=x-Radius;
		xmax=x+Radius+1;
		ypos=y;
		ymin=y-Radius;
		ymax=y+Radius;

		if (((xpos>=MaxX)||(xmax<MinX))||((ymin>=MaxY)||(ymax<MinY)))
		{
			currscreen->DoUnlockScr(&rsd);
			return;
		}

		if (xpos<MinX)	xpos=MinX;
		if (xmax>=MaxX)	xmax=MaxX-1;

		iyscale=iheight/Radius;
		dystep=65536/Radius;
		dyfrac=dystep;

		if ((ypos>=MinY)&&(ypos<MaxY))
		{
			scradr=(UWord*)(ULong(rsd.lpSurface)+ypos*rsd.lPitch);
			leftvertex.sy.i=rightvertex.sy.i=ypos;
			leftvertex.sx.i=xpos<<16;
			leftvertex.ix.i=SphIxStart;
			leftvertex.iy.i=iy;
			rightvertex.sx.i=xmax<<16;
			rightvertex.ix.i=(*vptr)->ix.i;
			rightvertex.iy.i=iy;
 			ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
		}

		// And the rest...
		ypos=y+1;
		ypos2=y-1;
		iypos=iy+iyscale;
		iypos2=iy-iyscale;
		scradr=(UWord*)(ULong(rsd.lpSurface)+ypos*rsd.lPitch);
		scradr2=(UWord*)(ULong(rsd.lpSurface)+ypos2*rsd.lPitch);

		for (dy=1;dy<=Radius;dy++)
		{
			cos_ang=Circle_CosTable[dyfrac>>8];
			dx=(Radius*cos_ang)>>15;
			idx=iwidth>>15;
			idx*=cos_ang;
			ixpos=ix-idx;
			ixmax=ix+idx+1;
			xpos=x-dx;
			xmax=x+dx+1;
			if ((xpos<MaxX)||(xmax>MinX))
			{
				if (xpos<MinX)	xpos=MinX;
				if (xmax>=MaxX)	xmax=MaxX-1;
				if ((ypos>=MinY)&&(ypos<MaxY))
				{
					leftvertex.sy.i=rightvertex.sy.i=ypos;
					leftvertex.sx.i=xpos<<16;
					leftvertex.ix.i=ixpos;
					leftvertex.iy.i=iypos;
					rightvertex.sx.i=xmax<<16;
					rightvertex.ix.i=ixmax;
					rightvertex.iy.i=iypos;
 					ASM_Call(horilinertn,scradr,leftvertex,rightvertex);
				}
				if ((ypos2>=MinY)&&(ypos2<MaxY))
				{
					leftvertex.sy.i=rightvertex.sy.i=ypos2;
					leftvertex.sx.i=xpos<<16;
					leftvertex.ix.i=ixpos;
					leftvertex.iy.i=iypos2;
					rightvertex.sx.i=xmax<<16;
					rightvertex.ix.i=ixmax;
					rightvertex.iy.i=iypos2;
 					ASM_Call(horilinertn,scradr2,leftvertex,rightvertex);
				}
			}
			dyfrac+=dystep;
			iypos+=iyscale;
			iypos2-=iyscale;
			ypos++;
			ypos2--;
			scradr=(UWord*)(ULong(scradr)+rsd.lPitch);
			scradr2=(UWord*)(ULong(scradr)-rsd.lPitch);
		}
	}
	currscreen->DoUnlockScr(&rsd);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ipolyscancnvrt
//Author		Paul.   
//Date			Thu 19 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*TEMPvoid polygon::ipolyscancnvrt(HLINELIST &hll)
{
	ROWANSURFACEDESC rsd;

	VERTEX_PTR	*cindrp,*cindlp,
				*nindrp,*nindlp;

	UWord*	scradr;

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;

	SLong	ld_sx,rd_sx;

	SLong	ld_ix,rd_ix;

	SLong	ld_iy,rd_iy;

	SLong	last_leftsx,last_rightsx;

	currscreen->DoLockScr(&rsd);

	scradr=(UWord*)(ULong(rsd.lpSurface)+hll.starty*rsd.lPitch);

	leftvertex.sy.i=rightvertex.sy.i=hll.starty;

	//Initialise left edge interpolation stuff

	nindlp = hll.minilp;

	do
	{
		cindlp = nindlp;
		switch(hll.led)
		{
			case FORWARDS:
				nindlp++;
				if(!*nindlp) nindlp = nvertptr;
				break;
			case BACKWARDS:
				nindlp--;
				if(!*nindlp) nindlp += vertexcount;
				break;
		}
		ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
	}
	while(!ld_sy);
	leftvertex.sx.i = (*cindlp)->bigsx.i;
	leftvertex.ix.i = (*cindlp)->ix.i;
	leftvertex.iy.i = (*cindlp)->iy.i;
	ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;		//PD 21Nov96
	ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
	ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;

	ld_sy++;													//PD 21Nov96

	//Initialise right edge interpolation stuff

	nindrp = hll.minirp;

	do
	{
		cindrp = nindrp;
		switch(hll.led)
		{
			case BACKWARDS:
				nindrp++;
				if(!*nindrp) nindrp = nvertptr;
				break;
			case FORWARDS:
				nindrp--;
				if(!*nindrp) nindrp += vertexcount;
				break;
		}
		rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
	}
	while(!rd_sy);
	rightvertex.sx.i = (*cindrp)->bigsx.i;
	rightvertex.ix.i = (*cindrp)->ix.i;
	rightvertex.iy.i = (*cindrp)->iy.i;
	rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;		//PD 21Nov96
	rd_ix = ((*nindrp)->ix.i-(*cindrp)->ix.i)/rd_sy;
	rd_iy = ((*nindrp)->iy.i-(*cindrp)->iy.i)/rd_sy;

	rd_sy++;													//PD 21Nov96

	last_leftsx = leftvertex.sx.i;
	last_rightsx= rightvertex.sx.i;

	//Now start the real DDA stuff

	while(hll.length--)
	{
		//Do a single scan line

		SLong	lx,rx;

		lx=leftvertex.sx.i;
		rx=rightvertex.sx.i;

		if (leftvertex.sx.i>last_rightsx)
			leftvertex.sx.i = last_rightsx;

		if (rightvertex.sx.i<last_leftsx)
			rightvertex.sx.i = last_leftsx;

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		leftvertex.sx.i=lx;
		rightvertex.sx.i=rx;

		leftvertex.sy.i=rightvertex.sy.i=rightvertex.sy.i+1;

		//index left and right by left and right delta sx

		ld_sy--;

		if(!ld_sy)
		{
			//get next left index

			do
			{
				cindlp = nindlp;
				switch(hll.led)
				{
					case FORWARDS:
						nindlp++;
						if(!*nindlp) nindlp = nvertptr;
						break;
					case BACKWARDS:
						nindlp--;
						if(!*nindlp) nindlp += vertexcount;
						break;
				}
				ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
			}
			while(!ld_sy);
			leftvertex.ix.i = (*cindlp)->ix.i;
			leftvertex.iy.i = (*cindlp)->iy.i;
			leftvertex.sx.i = (*cindlp)->bigsx.i;
			ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;
			ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
			ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;
		}

		rd_sy--;

		if(!rd_sy)
		{
			//get next right index

			do
			{
				cindrp = nindrp;
				switch(hll.led)
				{
					case BACKWARDS:
						nindrp++;
						if(!*nindrp) nindrp = nvertptr;
						break;
					case FORWARDS:
						nindrp--;
						if(!*nindrp) nindrp += vertexcount;
						break;
				}
				rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
			}
			while(!rd_sy);
			rightvertex.ix.i = (*cindrp)->ix.i;
			rightvertex.iy.i = (*cindrp)->iy.i;
			rightvertex.sx.i = (*cindrp)->bigsx.i;
			rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;
			rd_ix = ((*nindrp)->ix.i-(*cindrp)->ix.i)/rd_sy;
			rd_iy = ((*nindrp)->iy.i-(*cindrp)->iy.i)/rd_sy;
		}

		last_leftsx = leftvertex.sx.i;
		last_rightsx= rightvertex.sx.i;
	
		leftvertex.sx.i += ld_sx;
		rightvertex.sx.i += rd_sx;

		leftvertex.ix.i += ld_ix;
		leftvertex.iy.i += ld_iy;

		rightvertex.ix.i += rd_ix;
		rightvertex.iy.i += rd_iy;

		scradr=(UWord*)(ULong(scradr)+rsd.lPitch);
	}
	currscreen->DoUnlockScr(&rsd);
}TEMP*/

void polygon::ipolyscancnvrt(HLINELIST &hll)
{
	ROWANSURFACEDESC rsd;

	VERTEX_PTR	*cindrp,*cindlp,
				*nindrp,*nindlp;

	UWord*	scradr;

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;

	SLong	ld_sx,rd_sx;

	Float	ld_ix,rd_ix,l_ix,r_ix;

	Float	ld_iy,rd_iy,l_iy,r_iy;

	SLong	last_leftsx,last_rightsx;

	currscreen->DoLockScr(&rsd);

	scradr=(UWord*)(ULong(rsd.lpSurface)+hll.starty*rsd.lPitch);

	leftvertex.sy.i=rightvertex.sy.i=hll.starty;

	//Initialise left edge interpolation stuff

	nindlp = hll.minilp;

	do
	{
		cindlp = nindlp;
		switch(hll.led)
		{
			case FORWARDS:
				nindlp++;
				if(!*nindlp) nindlp = nvertptr;
				break;
			case BACKWARDS:
				nindlp--;
				if(!*nindlp) nindlp += vertexcount;
				break;
		}
		ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
	}
	while(!ld_sy);
	leftvertex.sx.i = (*cindlp)->bigsx.i;
//	leftvertex.ix.i = (*cindlp)->ix.i;
//	leftvertex.iy.i = (*cindlp)->iy.i;
	l_ix = (*cindlp)->ix.i;
	l_iy = (*cindlp)->iy.i;
	ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;		//PD 21Nov96
	ld_ix = ((*nindlp)->ix.i-l_ix)/ld_sy;
	ld_iy = ((*nindlp)->iy.i-l_iy)/ld_sy;

	ld_sy++;													//PD 21Nov96

	//Initialise right edge interpolation stuff

	nindrp = hll.minirp;

	do
	{
		cindrp = nindrp;
		switch(hll.led)
		{
			case BACKWARDS:
				nindrp++;
				if(!*nindrp) nindrp = nvertptr;
				break;
			case FORWARDS:
				nindrp--;
				if(!*nindrp) nindrp += vertexcount;
				break;
		}
		rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
	}
	while(!rd_sy);
	rightvertex.sx.i = (*cindrp)->bigsx.i;
//	rightvertex.ix.i = (*cindrp)->ix.i;
//	rightvertex.iy.i = (*cindrp)->iy.i;
	r_ix = (*cindrp)->ix.i;
	r_iy = (*cindrp)->iy.i;
	rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;		//PD 21Nov96
	rd_ix = ((*nindrp)->ix.i-r_ix)/rd_sy;
	rd_iy = ((*nindrp)->iy.i-r_iy)/rd_sy;

	rd_sy++;													//PD 21Nov96

	last_leftsx = leftvertex.sx.i;
	last_rightsx= rightvertex.sx.i;

	//Now start the real DDA stuff

	while(hll.length--)
	{
		//Do a single scan line

		SLong	lx,rx;

		lx=leftvertex.sx.i;
		rx=rightvertex.sx.i;

		if (leftvertex.sx.i>last_rightsx)
			leftvertex.sx.i = last_rightsx;

		if (rightvertex.sx.i<last_leftsx)
			rightvertex.sx.i = last_leftsx;

		leftvertex.ix.i=l_ix;
		leftvertex.iy.i=l_iy;
		rightvertex.ix.i=r_ix;
		rightvertex.iy.i=r_iy;

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		leftvertex.sx.i=lx;
		rightvertex.sx.i=rx;

		leftvertex.sy.i=rightvertex.sy.i=rightvertex.sy.i+1;

		//index left and right by left and right delta sx

		ld_sy--;

		if(!ld_sy)
		{
			//get next left index

			do
			{
				cindlp = nindlp;
				switch(hll.led)
				{
					case FORWARDS:
						nindlp++;
						if(!*nindlp) nindlp = nvertptr;
						break;
					case BACKWARDS:
						nindlp--;
						if(!*nindlp) nindlp += vertexcount;
						break;
				}
				ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
			}
			while(!ld_sy);
//			leftvertex.ix.i = (*cindlp)->ix.i;
//			leftvertex.iy.i = (*cindlp)->iy.i;
			l_ix = (*cindlp)->ix.i;
			l_iy = (*cindlp)->iy.i;
			leftvertex.sx.i = (*cindlp)->bigsx.i;
			ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;
			ld_ix = ((*nindlp)->ix.i-l_ix)/ld_sy;
			ld_iy = ((*nindlp)->iy.i-l_iy)/ld_sy;
		}

		rd_sy--;

		if(!rd_sy)
		{
			//get next right index

			do
			{
				cindrp = nindrp;
				switch(hll.led)
				{
					case BACKWARDS:
						nindrp++;
						if(!*nindrp) nindrp = nvertptr;
						break;
					case FORWARDS:
						nindrp--;
						if(!*nindrp) nindrp += vertexcount;
						break;
				}
				rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
			}
			while(!rd_sy);
//			rightvertex.ix.i = (*cindrp)->ix.i;
//			rightvertex.iy.i = (*cindrp)->iy.i;
			r_ix = (*cindrp)->ix.i;
			r_iy = (*cindrp)->iy.i;
			rightvertex.sx.i = (*cindrp)->bigsx.i;
			rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;
			rd_ix = ((*nindrp)->ix.i-r_ix)/rd_sy;
			rd_iy = ((*nindrp)->iy.i-r_iy)/rd_sy;
		}

		last_leftsx = leftvertex.sx.i;
		last_rightsx= rightvertex.sx.i;
	
		leftvertex.sx.i += ld_sx;
		rightvertex.sx.i += rd_sx;

//		leftvertex.ix.i += ld_ix;
//		leftvertex.iy.i += ld_iy;
		l_ix += ld_ix;
		l_iy += ld_iy;

//		rightvertex.ix.i += rd_ix;
//		rightvertex.iy.i += rd_iy;
		r_ix += rd_ix;
		r_iy += rd_iy;

		scradr=(UWord*)(ULong(scradr)+rsd.lPitch);
	}
	currscreen->DoUnlockScr(&rsd);
}

/*TEMPvoid polygon::ipolyscancnvrt(HLINELIST &hll)
{
	ROWANSURFACEDESC rsd;

	VERTEX_PTR	*cindrp,*cindlp,
				*nindrp,*nindlp;

	UWord*	scradr;

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;

	SLong	ld_sx,rd_sx;

	SLong	ld_ix,rd_ix;

	SLong	ld_iy,rd_iy;

	SLong	last_leftsx,last_rightsx;

	currscreen->DoLockScr(&rsd);

	scradr=(UWord*)(ULong(rsd.lpSurface)+hll.starty*rsd.lPitch);

	leftvertex.sy.i=rightvertex.sy.i=hll.starty;

	//Initialise left edge interpolation stuff

	nindlp = hll.minilp;

	do
	{
		cindlp = nindlp;
		switch(hll.led)
		{
			case FORWARDS:
				nindlp++;
				if(!*nindlp) nindlp = nvertptr;
				break;
			case BACKWARDS:
				nindlp--;
				if(!*nindlp) nindlp += vertexcount;
				break;
		}
		leftvertex.sx.i = (*cindlp)->bigsx.i;
		leftvertex.ix.i = (*cindlp)->ix.i;
		leftvertex.iy.i = (*cindlp)->iy.i;

		ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
	}
	while(!ld_sy);

	ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;		//PD 21Nov96
	ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
	ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;

	ld_sy++;													//PD 21Nov96

	//Initialise right edge interpolation stuff

	nindrp = hll.minirp;

	do
	{
		cindrp = nindrp;
		switch(hll.led)
		{
			case BACKWARDS:
				nindrp++;
				if(!*nindrp) nindrp = nvertptr;
				break;
			case FORWARDS:
				nindrp--;
				if(!*nindrp) nindrp += vertexcount;
				break;
		}
		rightvertex.sx.i = (*cindrp)->bigsx.i;
		rightvertex.ix.i = (*cindrp)->ix.i;
		rightvertex.iy.i = (*cindrp)->iy.i;

		rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
	}
	while(!rd_sy);

	rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;		//PD 21Nov96
	rd_ix = ((*nindrp)->ix.i-(*cindrp)->ix.i)/rd_sy;
	rd_iy = ((*nindrp)->iy.i-(*cindrp)->iy.i)/rd_sy;

	rd_sy++;													//PD 21Nov96

	last_leftsx = leftvertex.sx.i;
	last_rightsx= rightvertex.sx.i;

	//Now start the real DDA stuff

	while(hll.length--)
	{
		//Do a single scan line

		SLong	lx,rx;

		lx=leftvertex.sx.i;
		rx=rightvertex.sx.i;

		if (leftvertex.sx.i>last_rightsx)
			leftvertex.sx.i = last_rightsx;

		if (rightvertex.sx.i<last_leftsx)
			rightvertex.sx.i = last_leftsx;

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		leftvertex.sx.i=lx;
		rightvertex.sx.i=rx;

		leftvertex.sy.i=rightvertex.sy.i=rightvertex.sy.i+1;

		//index left and right by left and right delta sx

		ld_sy--;

		if(!ld_sy)
		{
			//get next left index

			do
			{
				cindlp = nindlp;
				switch(hll.led)
				{
					case FORWARDS:
						nindlp++;
						if(!*nindlp) nindlp = nvertptr;
						break;
					case BACKWARDS:
						nindlp--;
						if(!*nindlp) nindlp += vertexcount;
						break;
				}
				leftvertex.ix.i = (*cindlp)->ix.i;
				leftvertex.iy.i = (*cindlp)->iy.i;

				ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
			}
			while(!ld_sy);

			leftvertex.sx.i = (*cindlp)->bigsx.i;
			ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;
			ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
			ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;
		}

		rd_sy--;

		if(!rd_sy)
		{
			//get next right index

			do
			{
				cindrp = nindrp;
				switch(hll.led)
				{
					case BACKWARDS:
						nindrp++;
						if(!*nindrp) nindrp = nvertptr;
						break;
					case FORWARDS:
						nindrp--;
						if(!*nindrp) nindrp += vertexcount;
						break;
				}
				rightvertex.ix.i = (*cindrp)->ix.i;
				rightvertex.iy.i = (*cindrp)->iy.i;

				rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
			}
			while(!rd_sy);

			rightvertex.sx.i = (*cindrp)->bigsx.i;
			rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;
			rd_ix = ((*nindrp)->ix.i-(*cindrp)->ix.i)/rd_sy;
			rd_iy = ((*nindrp)->iy.i-(*cindrp)->iy.i)/rd_sy;
		}

		last_leftsx = leftvertex.sx.i;
		last_rightsx= rightvertex.sx.i;
	
		leftvertex.sx.i += ld_sx;
		rightvertex.sx.i += rd_sx;

		leftvertex.ix.i += ld_ix;
		leftvertex.iy.i += ld_iy;

		rightvertex.ix.i += rd_ix;
		rightvertex.iy.i += rd_iy;

		scradr=(UWord*)(ULong(scradr)+rsd.lPitch);
	}
	currscreen->DoUnlockScr(&rsd);
}TEMP*/

/*inline R3DVALUE MAKE_BZ(VERTEX* v,const R3DVALUE K) 
{
	return R3DVALUE(K*(v->by.f)/(Float(v->sy.i-POLYGON.viewdata.originy)+.001));
}

void polygon::ipolyscancnvrt(HLINELIST &hll)
{
	ROWANSURFACEDESC	rsd;
	VERTEX_PTR			*cindrp,*cindlp,*nindrp,*nindlp;
	UWord*				scradr;
	VERTEX				leftvertex,rightvertex;
	SLong				ld_sy,rd_sy,
						ld_sx,rd_sx,
						ld_ix,rd_ix,
						ld_iy,rd_iy,
						ls_ix,ls_iy,
						rs_ix,rs_iy;
	const R3DVALUE		K=-viewdata.scaley/viewdata.hoD;
	R3DVALUE			ld_bz,rd_bz,
						ls_bz,rs_bz,
						ld_by,rd_by;

	currscreen->DoLockScr(&rsd);
	scradr=(UWord*)(ULong(rsd.lpSurface)+hll.starty*rsd.lPitch);


	//Initialise left edge interpolation stuff
	nindlp=hll.minilp;
	do
	{
		cindlp=nindlp;
		switch(hll.led)
		{
		case FORWARDS:	nindlp++; if(!*nindlp) nindlp=nvertptr; break;
		case BACKWARDS:	nindlp--; if(!*nindlp) nindlp+=vertexcount; break;
		}
	}
	while((ld_sy=(*nindlp)->sy.i-(*cindlp)->sy.i)==0);
	leftvertex.sx.i=(*cindlp)->bigsx.i;
	leftvertex.sy.i=(*cindlp)->sy.i;
	leftvertex.ix.i=ls_ix=(*cindlp)->ix.i;
	leftvertex.iy.i=ls_iy=(*cindlp)->iy.i;
	leftvertex.by.f=(*cindlp)->by.f;
	leftvertex.bz.f=ls_bz=MAKE_BZ(&leftvertex,K);

	ld_sx=((*nindlp)->bigsx.i-leftvertex.sx.i)/ld_sy;
	ld_by=((*nindlp)->by.f-leftvertex.by.f)/ld_sy;
	ld_bz=(MAKE_BZ((*nindlp),K)-leftvertex.bz.f);
	ld_ix=(*nindlp)->ix.i-leftvertex.ix.i;
	ld_iy=(*nindlp)->iy.i-leftvertex.iy.i;
	ld_sy++;

	//Initialise right edge interpolation stuff
	nindrp=hll.minirp;
	do
	{
		cindrp=nindrp;
		switch(hll.led)
		{
		case BACKWARDS:	nindrp++; if(!*nindrp) nindrp=nvertptr; break;
		case FORWARDS:	nindrp--; if(!*nindrp) nindrp+=vertexcount; break;
		}
	}
	while((rd_sy=(*nindrp)->sy.i-(*cindrp)->sy.i)==0);
	rightvertex.sx.i=(*cindrp)->bigsx.i;
	rightvertex.sy.i=(*cindrp)->sy.i;
	rightvertex.ix.i=rs_ix=(*cindrp)->ix.i;
	rightvertex.iy.i=rs_iy=(*cindrp)->iy.i;
	rightvertex.by.f=(*cindrp)->by.f;
	rightvertex.bz.f=rs_bz=MAKE_BZ(&rightvertex,K);

	rd_sx=((*nindrp)->bigsx.i-rightvertex.sx.i)/rd_sy;
	rd_by=((*nindrp)->by.f-rightvertex.by.f)/rd_sy;
	rd_bz=(MAKE_BZ((*nindrp),K)-rightvertex.bz.f);
	rd_ix=(*nindrp)->ix.i-rightvertex.ix.i;
	rd_iy=(*nindrp)->iy.i-rightvertex.iy.i;
	rd_sy++;													//PD 21Nov96

	//Now start the real DDA stuff
	while(hll.length--)
	{
		//Do a single scan line
		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		//index left and right by left and right delta sx
		ld_sy--;
		if(!ld_sy)
		{
			//get next left index
			do
			{
				cindlp=nindlp;
				switch(hll.led)
				{
				case FORWARDS:	nindlp++; if(!*nindlp) nindlp=nvertptr; break;
				case BACKWARDS:	nindlp--; if(!*nindlp) nindlp+=vertexcount; break;
				}
			}
			while((ld_sy=(*nindlp)->sy.i-(*cindlp)->sy.i)==0);
			leftvertex.sx.i=(*cindlp)->bigsx.i;
			leftvertex.sy.i=(*cindlp)->sy.i;
			leftvertex.ix.i=ls_ix=(*cindlp)->ix.i;
			leftvertex.iy.i=ls_iy=(*cindlp)->iy.i;
			leftvertex.by.f=(*cindlp)->by.f;
			leftvertex.bz.f=ls_bz=MAKE_BZ(&leftvertex,K);

			ld_sx=((*nindlp)->bigsx.i-leftvertex.sx.i)/ld_sy;
			ld_by=((*nindlp)->by.f-leftvertex.by.f)/ld_sy;
			ld_bz=(MAKE_BZ((*nindlp),K)-leftvertex.bz.f);
			ld_ix=(*nindlp)->ix.i-leftvertex.ix.i;
			ld_iy=(*nindlp)->iy.i-leftvertex.iy.i;
		}
		rd_sy--;
		if(!rd_sy)
		{
			//get next right index
			do
			{
				cindrp=nindrp;
				switch(hll.led)
				{
				case BACKWARDS:	nindrp++; if(!*nindrp) nindrp=nvertptr; break;
				case FORWARDS:	nindrp--; if(!*nindrp) nindrp+=vertexcount; break;
				}
				;
			}
			while((rd_sy=(*nindrp)->sy.i-(*cindrp)->sy.i)==0);
			rightvertex.sx.i=(*cindrp)->bigsx.i;
			rightvertex.sy.i=(*cindrp)->sy.i;
			rightvertex.ix.i=rs_ix=(*cindrp)->ix.i;
			rightvertex.iy.i=rs_iy=(*cindrp)->iy.i;
			rightvertex.by.f=(*cindrp)->by.f;
			rightvertex.bz.f=rs_bz=MAKE_BZ(&rightvertex,K);

			rd_sx=((*nindrp)->bigsx.i-rightvertex.sx.i)/rd_sy;
			rd_by=((*nindrp)->by.f-rightvertex.by.f)/rd_sy;
			rd_bz=(MAKE_BZ((*nindrp),K)-rightvertex.bz.f);
			rd_ix=(*nindrp)->ix.i-rightvertex.ix.i;
			rd_iy=(*nindrp)->iy.i-rightvertex.iy.i;
		}

		leftvertex.sy.i++;
		leftvertex.sx.i+=ld_sx;
		leftvertex.by.f+=ld_by;
		leftvertex.bz.f=MAKE_BZ(&leftvertex,K);
		leftvertex.ix.i=ls_ix+ld_ix*(leftvertex.bz.f-ls_bz)/ld_bz;
		leftvertex.iy.i=ls_iy+ld_iy*(leftvertex.bz.f-ls_bz)/ld_bz;

		rightvertex.sy.i++;
		rightvertex.sx.i+=rd_sx;
		rightvertex.by.f+=rd_by;
		rightvertex.bz.f=MAKE_BZ(&rightvertex,K);
		rightvertex.ix.i=rs_ix+rd_ix*(rightvertex.bz.f-rs_bz)/rd_bz;
		rightvertex.iy.i=rs_iy+rd_iy*(rightvertex.bz.f-rs_bz)/rd_bz;

		scradr=(UWord*)(ULong(scradr)+rsd.lPitch);
	}
	currscreen->DoUnlockScr(&rsd);
}*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		wideipolyscancnvrt
//Author		Paul.   
//Date			Thu 19 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::wideipolyscancnvrt(HLINELIST &hll)
{
/*	VERTEX_PTR	*cindrp,*cindlp,
				*nindrp,*nindlp;

	LogicalPtr	scradr;

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;

	SLong	ld_sx,rd_sx;

	SLong	ld_ix,rd_ix;

	SLong	ld_iy,rd_iy;

	SLong	last_leftsx,last_rightsx;

	scradr = currscreen->logicalscreenptr
			+hll.starty*currscreen->BytesPerScanLine;

	//Initialise left edge interpolation stuff

	nindlp = hll.minilp;

	do
	{
		cindlp = nindlp;
		switch(hll.led)
		{
			case FORWARDS:
				nindlp++;
				if(!*nindlp) nindlp = nvertptr;
				break;
			case BACKWARDS:
				nindlp--;
				if(!*nindlp) nindlp += vertexcount;
				break;
		}
		leftvertex.sx.i = (*cindlp)->bigsx.i;
		leftvertex.ix.i = (*cindlp)->ix.i;
		leftvertex.iy.i = (*cindlp)->iy.i;

		ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
	}
	while(!ld_sy);

	ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;		//PD 21Nov96
	ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
	ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;

	ld_sy++;													//PD 21Nov96

	//Initialise right edge interpolation stuff

	nindrp = hll.minirp;

	do
	{
		cindrp = nindrp;
		switch(hll.led)
		{
			case BACKWARDS:
				nindrp++;
				if(!*nindrp) nindrp = nvertptr;
				break;
			case FORWARDS:
				nindrp--;
				if(!*nindrp) nindrp += vertexcount;
				break;
		}
		rightvertex.sx.i = (*cindrp)->bigsx.i;
		rightvertex.ix.i = (*cindrp)->ix.i;
		rightvertex.iy.i = (*cindrp)->iy.i;

		rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
	}
	while(!rd_sy);

	rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;		//PD 21Nov96
	rd_ix = ((*nindrp)->ix.i-(*cindrp)->ix.i)/rd_sy;
	rd_iy = ((*nindrp)->iy.i-(*cindrp)->iy.i)/rd_sy;

	rd_sy++;													//PD 21Nov96

	last_leftsx = leftvertex.sx.i;
	last_rightsx= rightvertex.sx.i;

	//Now start the real DDA stuff

	while(hll.length--)
	{
		//Do a single scan line

		SLong	lx,rx;

		lx = leftvertex.sx.i; rx = rightvertex.sx.i;

		if (lx>LeftX)	leftvertex.sx.i--;

		if (rx<RightX)	rightvertex.sx.i++;

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		leftvertex.sx.i = lx;
		rightvertex.sx.i = rx;

		//index left and right by left and right delta sx

		ld_sy--;

		if(!ld_sy)
		{
			//get next left index

			do
			{
				cindlp = nindlp;
				switch(hll.led)
				{
					case FORWARDS:
						nindlp++;
						if(!*nindlp) nindlp = nvertptr;
						break;
					case BACKWARDS:
						nindlp--;
						if(!*nindlp) nindlp += vertexcount;
						break;
				}
				leftvertex.ix.i = (*cindlp)->ix.i;
				leftvertex.iy.i = (*cindlp)->iy.i;

				ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
			}
			while(!ld_sy);

			leftvertex.sx.i = (*cindlp)->bigsx.i;
			ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;
			ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
			ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;
		}

		rd_sy--;

		if(!rd_sy)
		{
			//get next right index

			do
			{
				cindrp = nindrp;
				switch(hll.led)
				{
					case BACKWARDS:
						nindrp++;
						if(!*nindrp) nindrp = nvertptr;
						break;
					case FORWARDS:
						nindrp--;
						if(!*nindrp) nindrp += vertexcount;
						break;
				}
				rightvertex.ix.i = (*cindrp)->ix.i;
				rightvertex.iy.i = (*cindrp)->iy.i;

				rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
			}
			while(!rd_sy);

			rightvertex.sx.i = (*cindrp)->bigsx.i;
			rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;
			rd_ix = ((*nindrp)->ix.i-(*cindrp)->ix.i)/rd_sy;
			rd_iy = ((*nindrp)->iy.i-(*cindrp)->iy.i)/rd_sy;
		}
	
		leftvertex.sx.i += ld_sx;
		rightvertex.sx.i += rd_sx;

		if (leftvertex.sx.i>last_rightsx)
			leftvertex.sx.i = last_rightsx;

		if (rightvertex.sx.i<last_leftsx)
			rightvertex.sx.i = last_leftsx;

		last_leftsx = leftvertex.sx.i;
		last_rightsx= rightvertex.sx.i;
		leftvertex.ix.i += ld_ix;
		leftvertex.iy.i += ld_iy;

		rightvertex.ix.i += rd_ix;
		rightvertex.iy.i += rd_iy;

		scradr += currscreen->BytesPerScanLine;
	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		sipolyscanconvert
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
void polygon::sipolyscancnvrt(HLINELIST &hll)
{
	ROWANSURFACEDESC rsd;

	VERTEX_PTR	*cindrp,*cindlp;								//PD 29Jan96
	VERTEX_PTR	*nindrp,*nindlp;								//PD 29Jan96

	UWord	*scradr;

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;
	SLong	ld_sx,rd_sx;
	SLong	ld_ix,rd_ix;
	SLong	ld_iy,rd_iy;
	SLong	ld_in,rd_in;

	currscreen->DoLockScr(&rsd);

	scradr = (UWord *)(ULong(rsd.lpSurface)+hll.starty*rsd.lPitch);

	//Initialise left edge interpolation stuff

	nindlp = hll.minilp;

	do
	{
		cindlp = nindlp;
		switch(hll.led)
		{
			case FORWARDS:
				nindlp++;
				if(!*nindlp) nindlp = nvertptr;
				break;
			case BACKWARDS:
				nindlp--;
				if(!*nindlp) nindlp += vertexcount;
				break;
		}
		ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
	}
	while(!ld_sy);
	leftvertex.sx.i = (*cindlp)->bigsx.i;
	leftvertex.ix.i = (*cindlp)->ix.i;
	leftvertex.iy.i = (*cindlp)->iy.i;
	leftvertex.intensity = (*cindlp)->intensity;
	ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;		//PD 21Nov96
	ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
	ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;
	ld_in = ((*nindlp)->intensity-(*cindlp)->intensity)/ld_sy;

	ld_sy++;													//PD 21Nov96

	//Initialise right edge interpolation stuff

	nindrp = hll.minirp;

	do
	{
		cindrp = nindrp;
		switch(hll.led)
		{
			case BACKWARDS:
				nindrp++;
				if(!*nindrp) nindrp = nvertptr;
				break;
			case FORWARDS:
				nindrp--;
				if(!*nindrp) nindrp += vertexcount;
				break;
		}
		rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
	}
	while(!rd_sy);
	rightvertex.sx.i = (*cindrp)->bigsx.i;
	rightvertex.ix.i = (*cindrp)->ix.i;
	rightvertex.iy.i = (*cindrp)->iy.i;
	rightvertex.intensity = (*cindrp)->intensity;		//PD 31Oct95
	rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;		//PD 21Nov96
	rd_ix = ((*nindrp)->ix.i-(*cindrp)->ix.i)/rd_sy;
	rd_iy = ((*nindrp)->iy.i-(*cindrp)->iy.i)/rd_sy;
	rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;

	rd_sy++;													//PD 21Nov96

	//Now start the real DDA stuff

	leftvertex.sy.i = hll.starty;									//PD 16May96

	while(hll.length--)
	{
		//Do a single scan line

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		//index left and right by left and right delta sx

		ld_sy--;

		if(!ld_sy)
		{
			//get next left index

			do
			{
				cindlp = nindlp;
				switch(hll.led)
				{
					case FORWARDS:
						nindlp++;
						if(!*nindlp) nindlp = nvertptr;
						break;
					case BACKWARDS:
						nindlp--;
						if(!*nindlp) nindlp += vertexcount;
						break;
				}
				ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
			}
			while(!ld_sy);
			leftvertex.ix.i = (*cindlp)->ix.i;
			leftvertex.iy.i = (*cindlp)->iy.i;
			leftvertex.intensity = (*cindlp)->intensity;
			leftvertex.sx.i = (*cindlp)->bigsx.i;
			ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;
			ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
			ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;
			ld_in = ((*nindlp)->intensity-(*cindlp)->intensity)/ld_sy;
		}

		rd_sy--;

		if(!rd_sy)
		{
			//get next right index

			do
			{
				cindrp = nindrp;
				switch(hll.led)
				{
					case BACKWARDS:
						nindrp++;
						if(!*nindrp) nindrp = nvertptr;
						break;
					case FORWARDS:
						nindrp--;
						if(!*nindrp) nindrp += vertexcount;
						break;
				}
				rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
			}
			while(!rd_sy);
			rightvertex.ix.i = (*cindrp)->ix.i;
			rightvertex.iy.i = (*cindrp)->iy.i;
			rightvertex.intensity = (*cindrp)->intensity;
			rightvertex.sx.i = (*cindrp)->bigsx.i;
			rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;
			rd_ix = (((*nindrp)->ix.i-(*cindrp)->ix.i))/rd_sy;
			rd_iy = (((*nindrp)->iy.i-(*cindrp)->iy.i))/rd_sy;
			rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;
		}
	
		leftvertex.sx.i += ld_sx;
		rightvertex.sx.i += rd_sx;

		leftvertex.ix.i += ld_ix;
		leftvertex.iy.i += ld_iy;

		leftvertex.sy.i++;										//PD 16May96

		rightvertex.ix.i += rd_ix;
		rightvertex.iy.i += rd_iy;

		leftvertex.intensity += ld_in;
		rightvertex.intensity += rd_in;

		scradr=(UWord*)(ULong(scradr)+rsd.lPitch);
	}
	currscreen->DoUnlockScr(&rsd);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		sipolyscanconvert
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
void polygon::widesipolyscancnvrt(HLINELIST &hll)
{
	/*VERTEX_PTR	*cindrp,*cindlp;								//PD 29Jan96
	VERTEX_PTR	*nindrp,*nindlp;								//PD 29Jan96

	UByte	*scradr;

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;
	SLong	ld_sx,rd_sx;
	SLong	ld_ix,rd_ix;
	SLong	ld_iy,rd_iy;
	SLong	ld_in,rd_in;

	scradr = (UByte *)currscreen->logicalscreenptr
			+hll.starty*currscreen->BytesPerScanLine;

	//Initialise left edge interpolation stuff

	nindlp = hll.minilp;

	do
	{
		cindlp = nindlp;
		switch(hll.led)
		{
			case FORWARDS:
				nindlp++;
				if(!*nindlp) nindlp = nvertptr;
				break;
			case BACKWARDS:
				nindlp--;
				if(!*nindlp) nindlp += vertexcount;
				break;
		}
		leftvertex.sx.i = (*cindlp)->bigsx.i;
		leftvertex.ix.i = (*cindlp)->ix.i;
		leftvertex.iy.i = (*cindlp)->iy.i;
		leftvertex.intensity = (*cindlp)->intensity;

		ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
	}
	while(!ld_sy);

	ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;		//PD 21Nov96
	ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
	ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;
	ld_in = ((*nindlp)->intensity-(*cindlp)->intensity)/ld_sy;

	ld_sy++;													//PD 21Nov96

	//Initialise right edge interpolation stuff

	nindrp = hll.minirp;

	do
	{
		cindrp = nindrp;
		switch(hll.led)
		{
			case BACKWARDS:
				nindrp++;
				if(!*nindrp) nindrp = nvertptr;
				break;
			case FORWARDS:
				nindrp--;
				if(!*nindrp) nindrp += vertexcount;
				break;
		}
		rightvertex.sx.i = (*cindrp)->bigsx.i;
		rightvertex.ix.i = (*cindrp)->ix.i;
		rightvertex.iy.i = (*cindrp)->iy.i;
		rightvertex.intensity = (*cindrp)->intensity;		//PD 31Oct95

		rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
	}
	while(!rd_sy);

	rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;		//PD 21Nov96
	rd_ix = ((*nindrp)->ix.i-(*cindrp)->ix.i)/rd_sy;
	rd_iy = ((*nindrp)->iy.i-(*cindrp)->iy.i)/rd_sy;
	rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;

	rd_sy++;													//PD 21Nov96

	//Now start the real DDA stuff

	leftvertex.sy.i = hll.starty;									//PD 16May96

	while(hll.length--)
	{
		//Do a single scan line

		SLong	lx,rx;
		SLong	lin,rin;

		lin = leftvertex.intensity;
		rin = rightvertex.intensity;

		if (lin<0)	leftvertex.intensity=0;
		if (rin<0)	rightvertex.intensity=0;

		lx = leftvertex.sx.i; rx = rightvertex.sx.i;

		if (lx>LeftX)	leftvertex.sx.i--;

		if (rx<RightX)	rightvertex.sx.i++;

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		leftvertex.sx.i = lx;
		leftvertex.intensity=lin;
		rightvertex.sx.i = rx;
		rightvertex.intensity=rin;

		//index left and right by left and right delta sx

		ld_sy--;

		if(!ld_sy)
		{
			//get next left index

			do
			{
				cindlp = nindlp;
				switch(hll.led)
				{
					case FORWARDS:
						nindlp++;
						if(!*nindlp) nindlp = nvertptr;
						break;
					case BACKWARDS:
						nindlp--;
						if(!*nindlp) nindlp += vertexcount;
						break;
				}
				leftvertex.ix.i = (*cindlp)->ix.i;
				leftvertex.iy.i = (*cindlp)->iy.i;
				leftvertex.intensity = (*cindlp)->intensity;

				ld_sy = (*nindlp)->sy.i-(*cindlp)->sy.i;
			}
			while(!ld_sy);

			leftvertex.sx.i = (*cindlp)->bigsx.i;
			ld_sx = ((*nindlp)->bigsx.i-(*cindlp)->bigsx.i)/ld_sy;
			ld_ix = ((*nindlp)->ix.i-(*cindlp)->ix.i)/ld_sy;
			ld_iy = ((*nindlp)->iy.i-(*cindlp)->iy.i)/ld_sy;
			ld_in = ((*nindlp)->intensity-(*cindlp)->intensity)/ld_sy;
		}

		rd_sy--;

		if(!rd_sy)
		{
			//get next right index

			do
			{
				cindrp = nindrp;
				switch(hll.led)
				{
					case BACKWARDS:
						nindrp++;
						if(!*nindrp) nindrp = nvertptr;
						break;
					case FORWARDS:
						nindrp--;
						if(!*nindrp) nindrp += vertexcount;
						break;
				}
				rightvertex.ix.i = (*cindrp)->ix.i;
				rightvertex.iy.i = (*cindrp)->iy.i;
				rightvertex.intensity = (*cindrp)->intensity;

				rd_sy = (*nindrp)->sy.i-(*cindrp)->sy.i;
			}
			while(!rd_sy);

			rightvertex.sx.i = (*cindrp)->bigsx.i;
			rd_sx = ((*nindrp)->bigsx.i-(*cindrp)->bigsx.i)/rd_sy;
			rd_ix = (((*nindrp)->ix.i-(*cindrp)->ix.i))/rd_sy;
			rd_iy = (((*nindrp)->iy.i-(*cindrp)->iy.i))/rd_sy;
			rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;
		}
	
		leftvertex.sx.i += ld_sx;
		rightvertex.sx.i += rd_sx;

		leftvertex.ix.i += ld_ix;
		leftvertex.iy.i += ld_iy;

		leftvertex.sy.i++;										//PD 16May96

		rightvertex.ix.i += rd_ix;
		rightvertex.iy.i += rd_iy;

		leftvertex.intensity += ld_in;
		rightvertex.intensity += rd_in;

		scradr += currscreen->BytesPerScanLine;
	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VertexSpaceError
//Author		Paul.   
//Date			Wed 13 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::VertexSpaceError()
{
	_Error.EmitSysErr(__FILE__"Out of vertex space");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShiftIY
//Author		Martin Alderton
//Date			Wed 21 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::ShiftIY(SLong shift)
{
	VERTEX_PTR	*ptr;

	ptr = nvertptr;

	while(*ptr)
	{
		(*ptr)->iy.f += (Float)(shift<<16);

		ptr++;
	}
}

////////////// FLAT (single scanline ) poly routines

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		cflatscancnvrt
//Author		Paul.   
//Date			Thu 24 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::cflatscancnvrt(HLINELIST& hll)
{
/*	VERTEX_PTR	*leftp,*rightp,*tempp;

	LogicalPtr	scradr;

	scradr = currscreen->logicalscreenptr
			+hll.starty*currscreen->BytesPerScanLine;

	//Find the leftmost and rightmost vertices

	leftp = rightp = nvertptr;

	tempp = nvertptr+1;

	while (*tempp!=NULL)
	{
		if ((*tempp)->sx.i<(*leftp)->sx.i)
			leftp = tempp;
		else
			if ((*tempp)->sx.i>(*rightp)->sx.i)
				rightp = tempp;

		tempp++;
	}
	if (leftp==rightp)	return;

	VERTEX	leftvertex,
			rightvertex;

	leftvertex.sy.i =
		rightvertex.sy.i = hll.starty;
	leftvertex.sx.i 	= (*leftp)->bigsx.i;
	rightvertex.sx.i 	= (*rightp)->bigsx.i;

	ASM_Call(horilinertn,scradr,leftvertex,rightvertex);*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		gflatscancnvrt
//Author		Paul.   
//Date			Thu 24 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::gflatscancnvrt(HLINELIST& hll)
{
	/*VERTEX_PTR	*leftp,*rightp,*tempp;

	LogicalPtr	scradr;

	scradr = currscreen->logicalscreenptr
			+hll.starty*currscreen->BytesPerScanLine;

	//Find the leftmost and rightmost vertices

	leftp = rightp = nvertptr;

	tempp = nvertptr+1;

	while (*tempp!=NULL)
	{
		if ((*tempp)->sx.i<(*leftp)->sx.i)
			leftp = tempp;
		else
			if ((*tempp)->sx.i>(*rightp)->sx.i)
				rightp = tempp;

		tempp++;
	}
	if (leftp==rightp)	return;

	VERTEX	leftvertex,
			rightvertex;

	leftvertex.sy.i =
		rightvertex.sy.i = hll.starty;
	leftvertex.sx.i 			= (*leftp)->bigsx.i;
	leftvertex.intensity 	= (*leftp)->intensity;
	rightvertex.sx.i 			= (*rightp)->bigsx.i;
	rightvertex.intensity 	= (*rightp)->intensity;

	if (leftvertex.intensity<0)	leftvertex.intensity=0;
	if (rightvertex.intensity<0)	rightvertex.intensity=0;

	ASM_Call(horilinertn,scradr,leftvertex,rightvertex);*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		iflatscancnvrt
//Author		Paul.   
//Date			Thu 24 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::iflatscancnvrt(HLINELIST& hll)
{
	/*VERTEX_PTR	*leftp,*rightp,*tempp;

	LogicalPtr	scradr;

	scradr = currscreen->logicalscreenptr
			+hll.starty*currscreen->BytesPerScanLine;

	//Find the leftmost and rightmost vertices

	leftp = rightp = nvertptr;

	tempp = nvertptr+1;

	while (*tempp!=NULL)
	{
		if ((*tempp)->sx.i<(*leftp)->sx.i)
			leftp = tempp;
		else
			if ((*tempp)->sx.i>(*rightp)->sx.i)
				rightp = tempp;

		tempp++;
	}
	if (leftp==rightp)	return;

	VERTEX	leftvertex,
			rightvertex;

	leftvertex.sy.i =
		rightvertex.sy.i = hll.starty;
	leftvertex.sx.i 	= (*leftp)->bigsx.i;
	leftvertex.ix.i 	= (*leftp)->ix.i;
	leftvertex.iy.i 	= (*leftp)->iy.i;
	rightvertex.sx.i 	= (*rightp)->bigsx.i;
	rightvertex.ix.i 	= (*rightp)->ix.i;
	rightvertex.iy.i 	= (*rightp)->iy.i;

	ASM_Call(horilinertn,scradr,leftvertex,rightvertex);*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		siflatscancnvrt
//Author		Paul.   
//Date			Thu 24 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::siflatscancnvrt(HLINELIST& hll)
{
	/*VERTEX_PTR	*leftp,*rightp,*tempp;

	LogicalPtr	scradr;

	scradr = currscreen->logicalscreenptr
			+hll.starty*currscreen->BytesPerScanLine;

	//Find the leftmost and rightmost vertices

	leftp = rightp = nvertptr;

	tempp = nvertptr+1;

	while (*tempp!=NULL)
	{
		if ((*tempp)->sx.i<(*leftp)->sx.i)
			leftp = tempp;
		else
			if ((*tempp)->sx.i>(*rightp)->sx.i)
				rightp = tempp;

		tempp++;
	}
	if (leftp==rightp)	return;

	VERTEX	leftvertex,
			rightvertex;

	leftvertex.sy.i =
		rightvertex.sy.i = hll.starty;
	leftvertex.sx.i 			= (*leftp)->bigsx.i;
	leftvertex.ix.i 			= (*leftp)->ix.i;
	leftvertex.iy.i 			= (*leftp)->iy.i;
	leftvertex.intensity 	= (*leftp)->intensity;
	rightvertex.sx.i 			= (*rightp)->bigsx.i;
	rightvertex.ix.i 			= (*rightp)->ix.i;
	rightvertex.iy.i 			= (*rightp)->iy.i;
	rightvertex.intensity 	= (*rightp)->intensity;

	if (leftvertex.intensity<0)	leftvertex.intensity=0;
	if (rightvertex.intensity<0)	rightvertex.intensity=0;

	ASM_Call(horilinertn,scradr,leftvertex,rightvertex);*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FtoIPoly
//Author		Paul.   
//Date			Mon 6 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Float polygon::FtoIPoly()
{
	VERTEX_PTR*	cind;

	SLong lx,rx,ty,by;

	lx=viewdata.clipLft;
	rx=SLong(viewdata.clipRgt)-1;
	ty=viewdata.clipTop;
	by=SLong(viewdata.clipBot)-1;

	Float nearest=(*nvertptr)->bz.f;

	for (cind=nvertptr;*cind;cind++)
	{
		BodyToScreen(*cind);
		if ((*cind)->bz.f<nearest)	nearest=(*cind)->bz.f;
		if ((*cind)->sx.i<lx)		(*cind)->sx.i=lx;
		else if ((*cind)->sx.i>rx)	(*cind)->sx.i=rx;
		if ((*cind)->sy.i<ty)		(*cind)->sy.i=ty;
		else if ((*cind)->sy.i>by)	(*cind)->sy.i=by;
		(*cind)->bigsx.i=(*cind)->sx.i<<16;
	}
	return nearest;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLightVector
//Author		Paul.   
//Date			Tue 14 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::SetLightVector(IFShare& lx,IFShare& ly,IFShare& lz)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Cos_ArcSin
//Author		Robert Slater
//Date			Fri 13 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	polygon::Cos_ArcSin(SWord	frac8bit)
{
	return (Circle_CosTable[frac8bit]);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PolyCross
//Author		Paul.   
//Date			Tue 13 Apr 1999
//------------------------------------------------------------------------------
bool polygon::PolyCross()
{
	R3DVALUE sx[3],sy[3];
	for (int i=0;i<3;i++)
		GetSxy(nvertptr[i],sx[i],sy[i]);
	sx[0]-=sx[1];
	sx[2]-=sx[1];
	sy[0]-=sy[1];
	sy[2]-=sy[1];
	if (sx[0]*sy[2]-sy[0]*sx[2]<=R3DVALUE(0))	return true;
	return false;
}

inline void polygon::FullBodyToScreen(VERTEX_PTR pv)
{
	SLong	lx=viewdata.clipLft,
			rx=SLong(viewdata.clipRgt)-1,
			ty=viewdata.clipTop,
			by=SLong(viewdata.clipBot)-1;
	double rw=1./(viewdata.hoD*pv->bz.f);	
	pv->sx.i=double(viewdata.scalex*pv->bx.f*rw+viewdata.originx);
	pv->sy.i=double(-viewdata.scaley*pv->by.f*rw+viewdata.originy);;
	if (pv->sx.i<lx)		pv->sx.i=lx;
	else if (pv->sx.i>rx)	pv->sx.i=rx;
	if (pv->sy.i<ty)		pv->sy.i=ty;
	else if (pv->sy.i>by)	pv->sy.i=by;
	pv->bigsx.i=pv->sx.i<<16;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BodyToScreen
//Author		Paul.   
//Date			Tue 13 Apr 1999
//------------------------------------------------------------------------------
inline void polygon::BodyToScreen(VERTEX_PTR pv)
{
	if (fFoggingActive)
	{
		UWord fogVal;
		if (pv->bz.f<viewdata.FogStart)	fogVal=0;
		else if (pv->bz.f>viewdata.FogEnd) fogVal=0xFF;
		else fogVal=UByte(255.*(pv->bz.f-viewdata.FogStart)/(viewdata.FogEnd-viewdata.FogStart));
		pv->intensity=fogVal<<12;
	}
	double rw=1./(viewdata.hoD*pv->bz.f);	
	pv->sx.i=double(viewdata.scalex*pv->bx.f*rw+viewdata.originx);
	pv->sy.i=double(-viewdata.scaley*pv->by.f*rw+viewdata.originy);;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSxy
//Author		Paul.   
//Date			Tue 13 Apr 1999
//------------------------------------------------------------------------------
inline void polygon::GetSxy(VERTEX_PTR pv,R3DVALUE& sx,R3DVALUE& sy)
{
	R3DVALUE rw=R3DVALUE(1./(viewdata.hoD*pv->bz.f));	
	if (rw<0.) rw=-rw;
	sx=R3DVALUE(viewdata.scalex*pv->bx.f*rw+viewdata.originx);
	sy=R3DVALUE(-viewdata.scaley*pv->by.f*rw+viewdata.originy);
}
#define CLAMP(val)	if ((val)>-.00001 && (val)<.00001) (val)=.0
void polygon::ClipToFront(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip)
{
	vclip->bz.f=viewdata.D;
	double frac=(vclip->bz.f-vin->bz.f)/(vout->bz.f-vin->bz.f);
	vclip->bx.f=vin->bx.f+frac*(vout->bx.f-vin->bx.f);
	vclip->by.f=vin->by.f+frac*(vout->by.f-vin->by.f);
	if (clipperflag&CLIPF_TEXTURE)
	{
		vclip->ix.f=vin->ix.f+frac*(vout->ix.f-vin->ix.f);
		vclip->iy.f=vin->iy.f+frac*(vout->iy.f-vin->iy.f);
	}
	if (clipperflag&CLIPF_INTENSITY)
		vclip->intensity=vin->intensity+SLong(frac*R3DVALUE(vout->intensity-vin->intensity));
	vclip->clipFlags=CF3D_NULL;
	_clipLR(vclip->clipFlags,vclip->bx.f,vclip->bz.f);
	_clipTB(vclip->clipFlags,vclip->by.f,vclip->bz.f);
}
void polygon::ClipToBack(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip)
{
	vclip->bz.f=viewdata.F;
	double frac=(vclip->bz.f-vin->bz.f)/(vout->bz.f-vin->bz.f);
	vclip->bx.f=vin->bx.f+frac*(vout->bx.f-vin->bx.f);
	vclip->by.f=vin->by.f+frac*(vout->by.f-vin->by.f);
	if (clipperflag&CLIPF_TEXTURE)
	{
		vclip->ix.f=vin->ix.f+frac*(vout->ix.f-vin->ix.f);
		vclip->iy.f=vin->iy.f+frac*(vout->iy.f-vin->iy.f);
	}
	if (clipperflag&CLIPF_INTENSITY)
		vclip->intensity=vin->intensity+SLong(frac*R3DVALUE(vout->intensity-vin->intensity));
	vclip->clipFlags=CF3D_NULL;
	_clipLR(vclip->clipFlags,vclip->bx.f,vclip->bz.f);
	_clipTB(vclip->clipFlags,vclip->by.f,vclip->bz.f);
}
void polygon::ClipToEast(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip)
{
	double dZ=vout->bz.f-vin->bz.f; CLAMP (dZ);
	double dX=vout->bx.f-vin->bx.f; CLAMP (dX);
	double frac;

	if (dX==0.0)
	{
		vclip->bx.f=vclip->bz.f=vin->bx.f;
		frac=(vclip->bz.f-vin->bz.f)/(vout->bz.f-vin->bz.f);
	}
	else if (dZ==0.0)
	{
		vclip->bx.f=vclip->bz.f=vin->bz.f;
		frac=(vclip->bx.f-vin->bx.f)/(vout->bx.f-vin->bx.f);
	}
	else
	{
		double clipGradient=dZ/dX;
		double clipConst=vin->bz.f-clipGradient*vin->bx.f;
		vclip->bx.f=clipConst/(1.0-clipGradient);
		vclip->bz.f=vclip->bx.f;
		frac=(vclip->bx.f-vin->bx.f)/(vout->bx.f-vin->bx.f);
	}
	vclip->by.f=vin->by.f+frac*(vout->by.f-vin->by.f);
	if (clipperflag&CLIPF_TEXTURE)
	{
		vclip->ix.f=vin->ix.f+frac*(vout->ix.f-vin->ix.f);
		vclip->iy.f=vin->iy.f+frac*(vout->iy.f-vin->iy.f);
	}
	if (clipperflag&CLIPF_INTENSITY)
		vclip->intensity=vin->intensity+SLong(frac*R3DVALUE(vout->intensity-vin->intensity));
	vclip->clipFlags=CF3D_NULL;
	_clipTB(vclip->clipFlags,vclip->by.f,vclip->bz.f);
}
void polygon::ClipToWest(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip)
{
	double dZ=vout->bz.f-vin->bz.f; CLAMP (dZ);
	double dX=vout->bx.f-vin->bx.f; CLAMP (dX);
	double frac;

	if (dX==0.0)
	{
		vclip->bx.f=vin->bx.f;
		vclip->bz.f=-vin->bx.f;
		frac=(vclip->bz.f-vin->bz.f)/(vout->bz.f-vin->bz.f);
	}
	else if (dZ==0.0)
	{
		vclip->bx.f=-vin->bz.f;
		vclip->bz.f=vin->bz.f;
		frac=(vclip->bx.f-vin->bx.f)/(vout->bx.f-vin->bx.f);
	}
	else
	{
		double clipGradient=dZ/dX;
		double clipConst=vin->bz.f-clipGradient*vin->bx.f;
		vclip->bx.f=clipConst/(-1.0-clipGradient);
		vclip->bz.f=-vclip->bx.f;
		frac=(vclip->bx.f-vin->bx.f)/(vout->bx.f-vin->bx.f);
	}
	vclip->by.f=vin->by.f+frac*(vout->by.f-vin->by.f);
	if (clipperflag&CLIPF_TEXTURE)
	{
		vclip->ix.f=vin->ix.f+frac*(vout->ix.f-vin->ix.f);
		vclip->iy.f=vin->iy.f+frac*(vout->iy.f-vin->iy.f);
	}
	if (clipperflag&CLIPF_INTENSITY)
		vclip->intensity=vin->intensity+SLong(frac*R3DVALUE(vout->intensity-vin->intensity));
	vclip->clipFlags=CF3D_NULL;
	_clipTB(vclip->clipFlags,vclip->by.f,vclip->bz.f);
}
void polygon::ClipToTop(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip)
{
	double dZ=vout->bz.f-vin->bz.f; CLAMP (dZ);
	double dY=vout->by.f-vin->by.f; CLAMP (dY);
	double frac;

	if (dY==0.0)
	{
		vclip->by.f=vin->by.f;
		vclip->bz.f=vin->by.f;
		frac=(vclip->bz.f-vin->bz.f)/(vout->bz.f-vin->bz.f);
	}
	else if (dZ==0.0)
	{
		vclip->by.f=vin->bz.f;
		vclip->bz.f=vin->bz.f;
		frac=(vclip->by.f-vin->by.f)/(vout->by.f-vin->by.f);
	}
	else
	{
		double clipGradient=dZ/dY;
		double clipConst=vin->bz.f-clipGradient*vin->by.f;
		vclip->by.f=clipConst/(1.0-clipGradient);
		vclip->bz.f=vclip->by.f;
		frac=(vclip->by.f-vin->by.f)/(vout->by.f-vin->by.f);
	}
	vclip->bx.f=vin->bx.f+frac*(vout->bx.f-vin->bx.f);
	if (clipperflag&CLIPF_TEXTURE)
	{
		vclip->ix.f=vin->ix.f+frac*(vout->ix.f-vin->ix.f);
		vclip->iy.f=vin->iy.f+frac*(vout->iy.f-vin->iy.f);
	}
	if (clipperflag&CLIPF_INTENSITY)
		vclip->intensity=vin->intensity+SLong(frac*R3DVALUE(vout->intensity-vin->intensity));
	vclip->clipFlags=CF3D_NULL;
}
void polygon::ClipToBottom(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip)
{
	double dZ=vout->bz.f-vin->bz.f; CLAMP (dZ);
	double dY=vout->by.f-vin->by.f; CLAMP (dY);
	double frac;

	if (dY==0.0)
	{
		vclip->by.f=vin->by.f;
		vclip->bz.f=-vin->by.f;
		frac=(vclip->bz.f-vin->bz.f)/(vout->bz.f-vin->bz.f);
	}
	else if (dZ==0.0)
	{
		vclip->by.f=-vin->bz.f;
		vclip->bz.f=vin->bz.f;
		frac=(vclip->by.f-vin->by.f)/(vout->by.f-vin->by.f);
	}
	else
	{
		double clipGradient=dZ/dY;
		double clipConst=vin->bz.f-clipGradient*vin->by.f;
		vclip->by.f=-clipConst/(1.0+clipGradient);
		vclip->bz.f=-vclip->by.f;
		frac=(vclip->by.f-vin->by.f)/(vout->by.f-vin->by.f);
	}
	vclip->bx.f=vin->bx.f+frac*(vout->bx.f-vin->bx.f);
	if (clipperflag&CLIPF_TEXTURE)
	{
		vclip->ix.f=vin->ix.f+frac*(vout->ix.f-vin->ix.f);
		vclip->iy.f=vin->iy.f+frac*(vout->iy.f-vin->iy.f);
	}
	if (clipperflag&CLIPF_INTENSITY)
		vclip->intensity=vin->intensity+SLong(frac*R3DVALUE(vout->intensity-vin->intensity));
	vclip->clipFlags=CF3D_NULL;
}

// cv = current VERTEX_PTR*
// nv = next VERTEX_PTR*
// np = new VERTEX_PTR*
// crtn = clipper routine
// cf = 3d clip flag
// vc = vertex count

#define DOCLIP(cv,nv,np,crtn,cf,vc)\
	if (!((*(cv))->clipFlags&(cf)))\
	{\
		*(np)++=*(cv);\
		(vc)++;\
		if ((*(nv))->clipFlags&(cf))\
		{\
			*(np)=AllocateVertex();\
			(crtn)(*(cv),*(nv),*(np));\
			(np)++;\
			(vc)++;\
		}\
	}\
	else if (!((*(nv))->clipFlags&(cf)))\
	{\
		*(np)=AllocateVertex();\
		(crtn)(*(nv),*(cv),*(np));\
		(np)++;\
		(vc)++;\
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenericPolyClip
//Author		Paul.   
//Date			Tue 13 Apr 1999
//------------------------------------------------------------------------------
bool polygon::GenericPolyClip()
{
	VERTEX_PTR *cind,*nind,*newpnt;

	int newvertcount;

	if (fNoFogOrClip)
		KillBackClipFlags();

/************************************
 *	Clip against near clipping plane
 ************************************/

	for (cind=nvertptr,nind=cind+1,newpnt=cvertptr,newvertcount=0;*nind;)
	{
		DOCLIP(cind,nind,newpnt,ClipToFront,CF3D_BEHINDNEARZ,newvertcount);
		cind++;
		nind=cind+1;
	}
	DOCLIP(cind,nvertptr,newpnt,ClipToFront,CF3D_BEHINDNEARZ,newvertcount);

	if ((vertexcount=newvertcount)<3) return false;

	*newpnt=NULL;

/***************************************
 *	Clip against the far clipping plane
 ***************************************/

	for (cind=cvertptr,nind=cind+1,newpnt=nvertptr,newvertcount=0;*nind;)
	{
		DOCLIP(cind,nind,newpnt,ClipToBack,CF3D_PASTFARZ,newvertcount);
		cind++;
		nind=cind+1;
	}
	DOCLIP(cind,cvertptr,newpnt,ClipToBack,CF3D_PASTFARZ,newvertcount);

	if ((vertexcount=newvertcount)<3) return false;

	*newpnt=NULL;

/****************************************
 *	Clip against the east clipping plane
 ****************************************/

	for (cind=nvertptr,nind=cind+1,newpnt=cvertptr,newvertcount=0;*nind;)
	{
		DOCLIP(cind,nind,newpnt,ClipToEast,CF3D_OFFRIGHT,newvertcount);
		cind++;
		nind=cind+1;
	}
	DOCLIP(cind,nvertptr,newpnt,ClipToEast,CF3D_OFFRIGHT,newvertcount);

	if ((vertexcount=newvertcount)<3) return false;

	*newpnt=NULL;

/****************************************
 *	Clip against the west clipping plane
 ****************************************/

	for (cind=cvertptr,nind=cind+1,newpnt=nvertptr,newvertcount=0;*nind;)
	{
		DOCLIP(cind,nind,newpnt,ClipToWest,CF3D_OFFLEFT,newvertcount);
		cind++;
		nind=cind+1;
	}
	DOCLIP(cind,cvertptr,newpnt,ClipToWest,CF3D_OFFLEFT,newvertcount);

	if ((vertexcount=newvertcount)<3) return false;

	*newpnt=NULL;

/***************************************
 *	Clip against the top clipping plane
 ***************************************/

	for (cind=nvertptr,nind=cind+1,newpnt=cvertptr,newvertcount=0;*nind;)
	{
		DOCLIP(cind,nind,newpnt,ClipToTop,CF3D_OFFTOP,newvertcount);
		cind++;
		nind=cind+1;
	}
	DOCLIP(cind,nvertptr,newpnt,ClipToTop,CF3D_OFFTOP,newvertcount);

	if ((vertexcount=newvertcount)<3) return false;

	*newpnt=NULL;

/******************************************
 *	Clip against the bottom clipping plane
 ******************************************/

	for (cind=cvertptr,nind=cind+1,newpnt=nvertptr,newvertcount=0;*nind;)
	{
		DOCLIP(cind,nind,newpnt,ClipToBottom,CF3D_OFFBOTTOM,newvertcount);
		cind++;
		nind=cind+1;
	}
	DOCLIP(cind,cvertptr,newpnt,ClipToBottom,CF3D_OFFBOTTOM,newvertcount);

	if ((vertexcount=newvertcount)<3) return false;

	*newpnt=NULL;

	return true;
}

extern UByte* landPalette;

void	polygon::SetFog(UByte r,UByte g,UByte b,SLong s,SLong e)
{
	SetFog(r,g,b);
	fogStart=s;
	fogEnd=e;
	viewdata.FogStart=Float(s);
	viewdata.FogEnd=Float(e);
}
void	polygon::SetFog(UByte r,UByte g,UByte b)
{
	if (r!=fogRed || g!=fogGreen || b!=fogBlue)
	{
		fogRed=r;
		fogGreen=g;
		fogBlue=b;
		//generate fade tables
		if (currscreen && landPalette) 
		{
			UWord* pdst=(UWord*)currscreen->GetLandFadeTable();
			currscreen->DoMakePaletteFadeTable(landPalette,pdst,r,g,b);
			pdst=(UWord*)currscreen->GetSkyFadeTable();
			currscreen->DoMakePaletteFadeTable((UByte*)currscreen->Palette,pdst,r,g,b);
		}
	}
}
void	polygon::GetFog(UByte& r,UByte& g,UByte& b,SLong& s,SLong& e)
{
	r=fogRed;
	g=fogGreen;
	b=fogBlue;
	s=fogStart;
	e=fogEnd;
}
UWord polyRedBits,polyRedShift,polyGreenBits,polyGreenShift,polyBlueBits,polyBlueShift;

static SLong softFadeRedMask,softFadeGreenMask,softFadeBlueMask;
static UWord softFadeRedDelta,softFadeGreenDelta,softFadeBlueDelta;

void polygon::SoftwareWhiteOut()
{
	ROWANSURFACEDESC rsd;
	currscreen->DoLockScr(&rsd);
	UWord	redInc=fadeStage*softFadeRedDelta,
			greenInc=fadeStage*softFadeGreenDelta,
			blueInc=fadeStage*softFadeBlueDelta;
	UWord	redMask=softFadeRedMask,
			greenMask=softFadeGreenMask,
			blueMask=softFadeBlueMask;
	UWord* pscr=(UWord*)rsd.lpSurface;
	if (rsd.lPitch!=0)
	{
		for (int i=rsd.dwHeight-1;i>=0;i--)
		{
			UWord* ptr=pscr;
			pscr=(UWord*)(ULong(pscr)+rsd.lPitch);
			for (int j=rsd.dwWidth-1;j>=0;j--)
			{
				UWord in=*ptr;
				SLong out=SLong(in)&redMask;
				out+=redInc;
				if (out>redMask) out=redMask;
				SLong tmp=SLong(in)&greenMask;
				tmp+=greenInc;
				if (tmp>greenMask) tmp=greenMask;
				out|=tmp;
				tmp=SLong(in)&blueMask;
				tmp+=blueInc;
				if (tmp>blueMask) tmp=blueMask;
				out|=tmp;
				*ptr++=UWord(out);
			}
		}
	}
	else
	{
		for (int i=(rsd.dwWidth*rsd.dwHeight)-1;i>=0;i--)
		{
			UWord in=*pscr;
			SLong out=SLong(in)&redMask;
			out+=redInc;
			if (out>redMask) out=redMask;
			SLong tmp=SLong(in)&greenMask;
			tmp+=greenInc;
			if (tmp>greenMask) tmp=greenMask;
			out|=tmp;
			tmp=SLong(in)&blueMask;
			tmp+=blueInc;
			if (tmp>blueMask) tmp=blueMask;
			out|=tmp;
			*pscr++=UWord(out);
		}
	}
	currscreen->DoUnlockScr(&rsd);
}

void polygon::SoftwareBlackOut()
{
	ROWANSURFACEDESC rsd;
	currscreen->DoLockScr(&rsd);
	UWord	redDec=fadeStage*softFadeRedDelta,
			greenDec=fadeStage*softFadeGreenDelta,
			blueDec=fadeStage*softFadeBlueDelta;
	UWord	redMask=softFadeRedMask,
			greenMask=softFadeGreenMask,
			blueMask=softFadeBlueMask;
	UWord* pscr=(UWord*)rsd.lpSurface;

	if (rsd.lPitch!=0)
	{
		for (int i=rsd.dwHeight-1;i>=0;i--)
		{
			UWord* ptr=pscr;
			pscr=(UWord*)(ULong(pscr)+rsd.lPitch);
			for (int j=rsd.dwWidth-1;j>=0;j--)
			{
				UWord in=*ptr;
				SLong out=SLong(in)&redMask;
				out-=redDec;
				if (out<0) out=0;
				SLong tmp=SLong(in)&greenMask;
				tmp-=greenDec;
				if (tmp<0) tmp=0;
				out|=tmp;
				tmp=SLong(in)&blueMask;
				tmp-=blueDec;
				if (tmp<0) tmp=0;
				out|=tmp;
				*ptr++=UWord(out);
			}
		}
	}
	else
	{
		for (int i=(rsd.dwWidth*rsd.dwHeight)-1;i>=0;i--)
		{
			UWord in=*pscr;
			SLong out=SLong(in)&redMask;
			out-=redDec;
			if (out<0) out=0;
			SLong tmp=SLong(in)&greenMask;
			tmp-=greenDec;
			if (tmp<0) tmp=0;
			out|=tmp;
			tmp=SLong(in)&blueMask;
			tmp-=blueDec;
			if (tmp<0) tmp=0;
			out|=tmp;
			*pscr++=UWord(out);
		}
	}
	currscreen->DoUnlockScr(&rsd);
}

void polygon::SoftwareRedOut()
{
	ROWANSURFACEDESC rsd;
	currscreen->DoLockScr(&rsd);
	UWord	redInc=fadeStage*softFadeRedDelta,
			greenDec=fadeStage*softFadeGreenDelta,
			blueDec=fadeStage*softFadeBlueDelta;
	UWord	redMask=softFadeRedMask,
			greenMask=softFadeGreenMask,
			blueMask=softFadeBlueMask;
	UWord* pscr=(UWord*)rsd.lpSurface;

	if (rsd.lPitch!=0)
	{
		for (int i=rsd.dwHeight-1;i>=0;i--)
		{
			UWord* ptr=pscr;
			pscr=(UWord*)(ULong(pscr)+rsd.lPitch);
			for (int j=rsd.dwWidth-1;j>=0;j--)
			{
				UWord in=*ptr;
				SLong out=SLong(in)&redMask;
				out+=redInc;
				if (out>redMask) out=redMask;
				SLong tmp=SLong(in)&greenMask;
				tmp-=greenDec;
				if (tmp<0) tmp=0;
				out|=tmp;
				tmp=SLong(in)&blueMask;
				tmp-=blueDec;
				if (tmp<0) tmp=0;
				out|=tmp;
				*ptr++=UWord(out);
			}
		}
	}
	else
	{
		for (int i=(rsd.dwWidth*rsd.dwHeight)-1;i>=0;i--)
		{
			UWord in=*pscr;
			SLong out=SLong(in)&redMask;
			out+=redInc;
			if (out>redMask) out=redMask;
			SLong tmp=SLong(in)&greenMask;
			tmp-=greenDec;
			if (tmp<0) tmp=0;
			out|=tmp;
			tmp=SLong(in)&blueMask;
			tmp-=blueDec;
			if (tmp<0) tmp=0;
			out|=tmp;
			*pscr++=UWord(out);
		}
	}
	currscreen->DoUnlockScr(&rsd);
}

void polygon::DoSoftwareFades()
{
	if (!Save_Data.gamedifficulty[GD_GEFFECTS] &&
	!Save_Data.gamedifficulty[GD_WHITEOUT])
	return;

	if (fadeStage!=0)
	{
		SelectPalette(0);
		UWord minBits=polyRedBits<polyGreenBits?polyRedBits:polyGreenBits;
		minBits=minBits<polyBlueBits?minBits:polyBlueBits;
		UWord redExtra=polyRedBits-minBits;
		UWord greenExtra=polyGreenBits-minBits;
		UWord blueExtra=polyBlueBits-minBits;

		softFadeRedMask=SLong(((1<<polyRedBits)-1)<<polyRedShift)&0xFFFF;
		softFadeRedDelta=1<<(polyRedShift+redExtra);

		softFadeGreenMask=SLong(((1<<polyGreenBits)-1)<<polyGreenShift)&0xFFFF;
		softFadeGreenDelta=1<<(polyGreenShift+greenExtra);

		softFadeBlueMask=SLong(((1<<polyBlueBits)-1)<<polyBlueShift)&0xFFFF;
		softFadeBlueDelta=1<<(polyBlueShift+blueExtra);

		switch (fadeType)
		{
		case 0: SoftwareBlackOut(); break;
		case 1: SoftwareRedOut(); break;
		case 2: SoftwareWhiteOut(); break;
		default: break;
		}
	}
	fadeStage=0;
}

void polygon::DoPutC(ImageMapDesc* pmap,DoPointStruc* pdp)
{
	SelectPalette(0);
	UWord oldVal=currscreen->GetPaletteEntry(252);
	currscreen->SetPaletteEntry(252,currscreen->GetPaletteEntry(fontColour));
	vertex_index=vertex_list;
	vertexcount=0;
	if (*pmap->body==UByte(ARTWORKMASK))polytype=IMAPPED_M;
	else								polytype=IMAPPED;
	fFoggingRequired=false;
	doclip=0;
	scanconvert=&polygon::ipolyscancnvrt;
	scanconvertflat=&polygon::iflatscancnvrt;					//PD 24Oct96
	currscreen->SetColour(pmap);
	horilinertn=currscreen->GetScanLineAddr(polytype);
	clipperflag=CLIPF_TEXTURE;
	
	for (int i=0;i<4;i++)	
		createvert(pdp[i],pdp[i].ix,pdp[i].iy);

	for (VERTEX_PTR *cind=nvertptr;*cind;cind++)
	{
		(*cind)->sx.i=(*cind)->bx.f;
		(*cind)->bigsx.i=(*cind)->sx.i<<16;
		(*cind)->sy.i=(*cind)->by.f;
		(*cind)->ix.i = (SLong)(*cind)->ix.f;
		(*cind)->iy.i = (SLong)(*cind)->iy.f;
		(*cind)->bz.f=0;
	}
	softpoly();
	currscreen->SetPaletteEntry(252,oldVal);
}

void polygon::DoLine2D(Colour cc,SWord x1,SWord y1,SWord x2,SWord y2)
{
	if (x1<viewdata.clipLft)		x1=viewdata.clipLft;
	else if (x1>=viewdata.clipRgt)	x1=viewdata.clipRgt-1;
	if (y1<viewdata.clipTop)		y1=viewdata.clipTop;
	else if (y1>=viewdata.clipBot)	y1=viewdata.clipBot-1;
	if (x2<viewdata.clipLft)		x2=viewdata.clipLft;
	else if (x2>=viewdata.clipRgt)	x2=viewdata.clipRgt-1;
	if (y2<viewdata.clipTop)		y2=viewdata.clipTop;
	else if (y2>=viewdata.clipBot)	y2=viewdata.clipBot-1;
	currscreen->SetColour(cc);
	currscreen->PlainLine16(x1,y1,x2,y2);
}

void polygon::DoLine3D(Colour cc,DoPointStruc& svt,DoPointStruc& evt)
{
	if ((svt.clipFlags&evt.clipFlags)!=CF3D_NULL) return;	/* line is off screen */

	VERTEX vin,vout,vclip;
	vin.bx.f=svt.bodyx.f;
	vin.by.f=svt.bodyy.f;
	vin.bz.f=svt.bodyz.f;
	vin.clipFlags=svt.clipFlags;
	vout.bx.f=evt.bodyx.f;
	vout.by.f=evt.bodyy.f;
	vout.bz.f=evt.bodyz.f;
	vout.clipFlags=evt.clipFlags;

	if ((vin.clipFlags|vout.clipFlags)!=CF3D_NULL)
	{
/************************************
 *	Clip against near clipping plane
 ************************************/
		if ((vin.clipFlags|vout.clipFlags)&CF3D_BEHINDNEARZ)
		{
			if (vin.clipFlags&CF3D_BEHINDNEARZ) {VERTEX t=vin;vin=vout;vout=t;}
			ClipToFront(&vin,&vout,&vclip);
			vout=vclip;
		}
/***************************************
 *	Clip against the far clipping plane
 ***************************************/
		if ((vin.clipFlags|vout.clipFlags)&CF3D_PASTFARZ)
		{
			if (vin.clipFlags&CF3D_PASTFARZ) {VERTEX t=vin;vin=vout;vout=t;}
			ClipToBack(&vin,&vout,&vclip);
			vout=vclip;
		}
/****************************************
 *	Clip against the east clipping plane
 ****************************************/
		if ((vin.clipFlags|vout.clipFlags)&CF3D_OFFRIGHT)
		{
			if (vin.clipFlags&CF3D_OFFRIGHT) {VERTEX t=vin;vin=vout;vout=t;}
			ClipToEast(&vin,&vout,&vclip);
			vout=vclip;
		}
/****************************************
 *	Clip against the west clipping plane
 ****************************************/
		if ((vin.clipFlags|vout.clipFlags)&CF3D_OFFLEFT)
		{
			if (vin.clipFlags&CF3D_OFFLEFT) {VERTEX t=vin;vin=vout;vout=t;}
			ClipToWest(&vin,&vout,&vclip);
			vout=vclip;
		}
/***************************************
 *	Clip against the top clipping plane
 ***************************************/
		if ((vin.clipFlags|vout.clipFlags)&CF3D_OFFTOP)
		{
			if (vin.clipFlags&CF3D_OFFTOP) {VERTEX t=vin;vin=vout;vout=t;}
			ClipToTop(&vin,&vout,&vclip);
			vout=vclip;
		}
/******************************************
 *	Clip against the bottom clipping plane
 ******************************************/
		if ((vin.clipFlags|vout.clipFlags)&CF3D_OFFBOTTOM)
		{
			if (vin.clipFlags&CF3D_OFFBOTTOM) {VERTEX t=vin;vin=vout;vout=t;}
			ClipToBottom(&vin,&vout,&vclip);
			vout=vclip;
		}
	}
	if ((vin.clipFlags|vout.clipFlags)==CF3D_NULL)
	{
		/* draw the line segment if any of it is still visible */
		BodyToScreen(&vin);
		BodyToScreen(&vout);
		SWord x1,y1,x2,y2;
		x1=vin.sx.i;
		y1=vin.sy.i;
		x2=vout.sx.i;
		y2=vout.sy.i;
		if (x1<viewdata.clipLft)		x1=viewdata.clipLft;
		else if (x1>=viewdata.clipRgt)	x1=viewdata.clipRgt-1;
		if (y1<viewdata.clipTop)		y1=viewdata.clipTop;
		else if (y1>=viewdata.clipBot)	y1=viewdata.clipBot-1;

		if (x2<viewdata.clipLft)		x2=viewdata.clipLft;
		else if (x2>=viewdata.clipRgt)	x2=viewdata.clipRgt-1;
		if (y2<viewdata.clipTop)		y2=viewdata.clipTop;
		else if (y2>=viewdata.clipBot)	y2=viewdata.clipBot-1;
		currscreen->SetColour(cc);
		currscreen->PlainLine16(x1,y1,x2,y2);
	}
}

//no of pixels difference that must be exceeded
//before subdivision is needed
#define MIN_FOR_SUBDIVIDE 4
#define AXIS_BZ		0
#define AXIS_BY		1
#define AXIS_BX		2
#define AXIS_NONE	3
#define	EQUAL	0
#define TOP		1
#define BOTTOM	2
#define NOTEQUAL 4

bool polygon::subdivisionneeded(VERTEX_PTR* cind,SLong vertcount)
{
	VERTEX bc;
	SLong bc_sx,bc_sy;
	bc.bx.f=bc.by.f=bc.bz.f=0;
	bc_sx=bc_sy=0;
	for (;*cind;cind++)
	{
		bc.bx.f+=(*cind)->bx.f;
		bc.by.f+=(*cind)->by.f;
		bc.bz.f+=(*cind)->bz.f;
		bc_sx+=(*cind)->sx.i;
		bc_sy+=(*cind)->sy.i;
	}
	bc.bx.f/=vertcount;
	bc.by.f/=vertcount;
	bc.bz.f/=vertcount;
	FullBodyToScreen(&bc);

	bc_sx/=vertcount;
	bc_sx-=bc.sx.i; if (bc_sx<0) bc_sx=-bc_sx;
	bc_sy/=vertcount;
	bc_sy-=bc.sy.i; if (bc_sy<0) bc_sy=-bc_sy;
	if (bc_sx>MIN_FOR_SUBDIVIDE || bc_sy>MIN_FOR_SUBDIVIDE)
		return true;
	return false;		//no more subdivision is needed
}

UWord polygon::subdivisionaxis(VERTEX_PTR* cind,SLong vertcount)
{
	VERTEX bc;
	SLong bc_sx,bc_sy;
	bc.bx.f=bc.by.f=bc.bz.f=0;
	bc_sx=bc_sy=0;
	Float minx,maxx,miny,maxy,minz,maxz;
	minx=maxx=(*cind)->bx.f;
	miny=maxy=(*cind)->by.f;
	minz=maxz=(*cind)->bz.f;
	for (;*cind;cind++)
	{
		bc.bx.f+=(*cind)->bx.f;
		if ((*cind)->bx.f>maxx)	maxx=(*cind)->bx.f;
		if ((*cind)->bx.f<minx)	minx=(*cind)->bx.f;
		bc.by.f+=(*cind)->by.f;
		if ((*cind)->by.f>maxy)	maxy=(*cind)->by.f;
		if ((*cind)->by.f<miny)	miny=(*cind)->by.f;
		bc.bz.f+=(*cind)->bz.f;
		if ((*cind)->bz.f>maxz)	maxz=(*cind)->bz.f;
		if ((*cind)->bz.f<minz)	minz=(*cind)->bz.f;
		bc_sx+=(*cind)->sx.i;
		bc_sy+=(*cind)->sy.i;
	}
	bc.bx.f/=vertcount;
	bc.by.f/=vertcount;
	bc.bz.f/=vertcount;
	FullBodyToScreen(&bc);

	bc_sx/=vertcount;
	bc_sx-=bc.sx.i; if (bc_sx<0) bc_sx=-bc_sx;
	bc_sy/=vertcount;
	bc_sy-=bc.sy.i; if (bc_sy<0) bc_sy=-bc_sy;
	if (bc_sx>MIN_FOR_SUBDIVIDE || bc_sy>MIN_FOR_SUBDIVIDE)
	{
		minx=minx>maxx?minx-maxx:maxx-minx;
		miny=miny>maxy?miny-maxy:maxy-miny;
		minz=minz>maxz?minz-maxz:maxz-minz;
		return (minx>miny)?(minx>minz)?AXIS_BX:AXIS_BZ:(miny>minz)?AXIS_BY:AXIS_BZ;
	}
	return AXIS_NONE;		//no more subdivision is needed
}

void polygon::split(PolyRecord* original,PolyRecord* newfragment,UWord whichaxis)
{
	Float		min,max,split;		//min,max and split values for BZ
	Float		frac;
	SLong		i,
				vertcount=original->vertexcount;
	VERTEX_PTR	*cur,
				*nxt,
				*top,
				*bot;
	PolyRecord	copy=*original;

	//find min & max values for poly BZ

	cur=original->vptr;

	if (whichaxis==AXIS_BZ)
	{
		min=max=(*cur)->bz.f;
		for (++cur,i=vertcount-2;i>=0;i--,cur++){
			if ((*cur)->bz.f>max)	max=(*cur)->bz.f;
			if ((*cur)->bz.f<min)	min=(*cur)->bz.f;
		}
	}
	else if (whichaxis==AXIS_BY){
		min=max=(*cur)->by.f;
		for (++cur,i=vertcount-2;i>=0;i--,cur++){
			if ((*cur)->by.f>max)	max=(*cur)->by.f;
			if ((*cur)->by.f<min)	min=(*cur)->by.f;
		}
	}
	else{	//AXIS_BX
		min=max=(*cur)->bx.f;
		for (++cur,i=vertcount-2;i>=0;i--,cur++){
			if ((*cur)->bx.f>max)	max=(*cur)->bx.f;
			if ((*cur)->bx.f<min)	min=(*cur)->bx.f;
		}
	}

	//split along BZ==(min+max)/2
	split=(min+max)*.5;
	
	original->vertexcount=newfragment->vertexcount=0;
	top=original->vptr;
	bot=newfragment->vptr;

	for (i=vertcount-1,nxt=copy.vptr,cur=nxt+i;i>=0;i--)
	{
		Float testval,nextval,frac;
		
		if (whichaxis==AXIS_BZ)			testval=(*cur)->bz.f, nextval=(*nxt)->bz.f;
		else if (whichaxis==AXIS_BY)	testval=(*cur)->by.f, nextval=(*nxt)->by.f;
		else							testval=(*cur)->bx.f, nextval=(*nxt)->bx.f;

		UWord testflag=testval>split?TOP:testval<split?BOTTOM:EQUAL;
		UWord nextflag=nextval>split?TOP:nextval<split?BOTTOM:EQUAL;

		//cases to handle are...
		//		both values on same side
		//		values on opposite sides
		//		one or both values on the boundary

		if (testflag&nextflag)
		{
			//both values are on the same side of the boundary
			//Insert the current point into the correct list
			if (testflag&TOP)	{*top++=*cur; original->vertexcount++;}
			else				{*bot++=*cur; newfragment->vertexcount++;}
		}
		else if (testflag==EQUAL)
		{
			//current value is on the boundary so add it to both lists
			*top++=*cur;
			*bot++=*cur;
			original->vertexcount++;
			newfragment->vertexcount++;
		}
		else if (nextflag==EQUAL)
		{
			//next value is on the boundary so just insert the
			//current point into the correct list
			if (testflag&TOP)	{*top++=*cur; original->vertexcount++;}
			else				{*bot++=*cur; newfragment->vertexcount++;}
		}
		else
		{
			//calculate point of intersection with the test plane
			VERTEX_PTR tmp=AllocateVertex();
			VERTEX_PTR in,out;

			if (testflag&TOP)	
			{
				in=*cur; out=*nxt;
				frac=(split-testval)/(nextval-testval);
			}
			else				
			{
				in=*nxt; out=*cur;
				frac=(split-nextval)/(testval-nextval);
			}
			//in=*cur;
			//out=*nxt;
			//frac=(split-testval)/(nextval-testval);

			if (whichaxis==AXIS_BZ){
				tmp->bz.f=split;
				tmp->bx.f=in->bx.f+frac*(out->bx.f-in->bx.f);
				tmp->by.f=in->by.f+frac*(out->by.f-in->by.f);
			}
			else if (whichaxis==AXIS_BY){
				tmp->by.f=split;
				tmp->bx.f=in->bx.f+frac*(out->bx.f-in->bx.f);
				tmp->bz.f=in->bz.f+frac*(out->bz.f-in->bz.f);
			}
			else{
				tmp->bx.f=split;
				tmp->bz.f=in->bz.f+frac*(out->bz.f-in->bz.f);
				tmp->by.f=in->by.f+frac*(out->by.f-in->by.f);
			}
			tmp->ix.f=in->ix.f+frac*(out->ix.f-in->ix.f);
			tmp->iy.f=in->iy.f+frac*(out->iy.f-in->iy.f);

			FullBodyToScreen(tmp);

			if (testflag&TOP)
			{
				*top++=*cur;
				*top++=tmp;
				original->vertexcount+=2;
				*bot++=tmp;
				newfragment->vertexcount++;
			}
			else
			{
				*bot++=*cur;
				*bot++=tmp;
				newfragment->vertexcount+=2;
				*top++=tmp;
				original->vertexcount++;
			}
		}
		cur=nxt;
		nxt++;
	}
	*top++=NULL;
	*bot++=NULL;
}

void polygon::perspectivepoly()
{
	if (!subdivisionneeded(nvertptr,vertexcount))
	{
		FtoITexture(nvertptr);
		softpoly();
		return;
	}

	bool flag;
	UWord whichaxis=0;
	subdivisioncount=0;	
	
	//insert original poly into subdivision list
	VERTEX_PTR *cind=nvertptr,*iind=polyrecord[0].vptr;
	for (;*cind;*iind++=*cind++);
	*iind=NULL;
	polyrecord[subdivisioncount++].vertexcount=vertexcount;

	do 
	{
		flag=false;
		for (SLong i=subdivisioncount-1;i>=0;i--)
		{
			if (subdivisioncount<MaxSubdivisions &&
				polyrecord[i].vertexcount>0)
			{
				if (subdivisionneeded(polyrecord[i].vptr,polyrecord[i].vertexcount))
				{
					split(polyrecord+i,polyrecord+subdivisioncount,whichaxis);
					subdivisioncount++;
					flag=true;
				}
				else polyrecord[i].vertexcount=-polyrecord[i].vertexcount;
			}
		}
		if (++whichaxis>2) whichaxis=0;
	}
	while (flag);	//no more subdivision is needed OR possible

	//convert all texture coordinates to integers

	for (VERTEX_PTR vp=vertex_list;vp!=vertex_index;vp++)
	{
		vp->ix.i=SLong(vp->ix.f);
		vp->iy.i=SLong(vp->iy.f);
	}

	//render all of the polygon fragments

	for (SLong i=subdivisioncount-1;i>=0;i--)
	{
		vertexcount=polyrecord[i].vertexcount;
		if (vertexcount<0) vertexcount=-vertexcount;
		VERTEX_PTR *cind=nvertptr;
		for (SLong j=0;j<vertexcount;*cind=polyrecord[i].vptr[j],cind++,j++);
		*cind=NULL;
		softpoly();
	}
}

void polygon::DoSmokedGlassBox(SWord x,SWord y,SWord w,SWord h,Colour colour)
{
	polytype=PLAIN;
	fFoggingRequired=false;
	doclip=0;
	horilinertn=currscreen->GetScanLineAddr(polytype);
	currscreen->SetColour(colour);
	scanconvert=&polygon::cpolyscancnvrt;
	scanconvertflat=&polygon::cflatscancnvrt;					//PD 24Oct96
	clipperflag=CLIPF_NULL;
	vertex_index=vertex_list;
	for (vertexcount=0;vertexcount<4;vertexcount++) nvertptr[vertexcount]=AllocateVertex();
	nvertptr[vertexcount]=NULL;
	nvertptr[0]->sx.i=x;
	nvertptr[0]->bigsx.i=x<<16;
	nvertptr[0]->sy.i=y;
	nvertptr[1]->sx.i=(x+w-1);
	nvertptr[1]->bigsx.i=(x+w-1)<<16;
	nvertptr[1]->sy.i=y;
	nvertptr[2]->sx.i=(x+w-1);
	nvertptr[2]->bigsx.i=(x+w-1)<<16;
	nvertptr[2]->sy.i=(y+h-1);
	nvertptr[3]->sx.i=x;
	nvertptr[3]->bigsx.i=x<<16;
	nvertptr[3]->sy.i=(y+h-1);
	softpoly();
}
void polygon::PushViewData()
{
	saveviewdata=viewdata;
	//disable fogging and back plane clipping
	fNoFogOrClip=true;
}
void polygon::PopViewData()
{
	viewdata=saveviewdata;
	//restore fogging and back plane clipping
	fNoFogOrClip=false;
}
void polygon::Set3DWin(SLong x,SLong y,SLong w,SLong h)
{
	viewdata.originx=(x+(w>>1));
	viewdata.originy=(y+(h>>1));
	viewdata.clipLft=(x);
	viewdata.clipRgt=(x+w);
	viewdata.clipTop=(y);
	viewdata.clipBot=(y+h);
}

void polygon::KillBackClipFlags()
{
	for (VERTEX_PTR *cind=nvertptr;*cind;cind++)
		(*cind)->clipFlags&=~CF3D_PASTFARZ;
}
























