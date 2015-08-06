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
//Filename       GrafPrim.cpp
//System         
//Author         Paul.   
//Date           Mon 3 Jul 1995
//Description    
//------------------------------------------------------------------------------
#include	"display.h"
#include	"libdefs.h"
#include    "mymath.h"
#include    "matrix.h"
#include	"mouse.h"
#include	"Worldinc.h"
#include	"polygon.h"
#include	"fonts.h"
#pragma warning (disable: 4701)
#ifdef	__MSVC__

	extern "C"	void XASM_SetColour(void);
	extern "C"	void XASM_SetPixelWidth(void);
	extern "C"	void XASM_GetPaletteTable(void);
	extern "C"	void XASM_SetTransparency(void);
	extern "C"	void XASM_PlainLine(void);
	extern "C"	void XASM_HoriLineAddr(void);
	extern "C"	void XASM_SmokedGlassLine(void);
	extern "C"	void XASM_GetTransparency(void);
	extern "C"	void XASM_SetLuminosity(void);
	extern "C"	void XASM_SetHeatHaze(void);
	extern "C"	void XASM_SelectPalette(void);
	extern "C"	void XASM_GetLandFadeTable(void);
	extern "C"	void XASM_GetHorizonFadeTable(void);
	extern "C"	void XASM_GetPaletteEntry(void);
	extern "C"	void XASM_SetPaletteEntry(void);

//-----------------------------------------------------------------------------
// Procedure    ASM_SetColour
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
inline void ASM_SetColour(Colour a,SLong b,SLong c,UByteP d)
{
	_asm
	{
		push	ecx
		mov		eax,a
		mov		edx,b
		mov		ebx,c
		mov		ecx,d
		call	XASM_SetColour
		pop		ecx
	}
}

#pragma warning (disable:4035)
inline void* ASM_GetPaletteTable()
{
	_asm {	call XASM_GetPaletteTable }
}

inline UWord ASM_GetPaletteEntry(UWord c)
{
	_asm{
		movzx eax,c;
		call XASM_GetPaletteEntry;
	}
}

inline void ASM_SetPaletteEntry(UWord c,UWord v)
{
	_asm{
		movzx	eax,c;
		mov		dx,v;
		call	XASM_SetPaletteEntry;
	}
}

inline void ASM_SelectPalette(SWord palNum)
{
	_asm {
		mov	ax,palNum
		call XASM_SelectPalette
	}
}
inline void* ASM_GetLandFadeTable()
{
	_asm{
		call XASM_GetLandFadeTable
	}
}
inline void* ASM_GetSkyFadeTable()
{
	_asm {
		call XASM_GetLandFadeTable;
		mov eax,edx
	}
}

inline void* ASM_GetHorizonFadeTable()
{
	_asm { call XASM_GetHorizonFadeTable }
}

//-----------------------------------------------------------------------------
// Procedure    ASM_SetPixelWidth
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
inline SWord	ASM_SetPixelWidth(SWord pw)
{
	_asm
	{
		mov		ax,pw
		call	XASM_SetPixelWidth
	}
}
#pragma warning (default:4035)

//-----------------------------------------------------------------------------
// Procedure    ASM_SetTransparency
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
inline	void ASM_SetTransparency(SWord t)
{
	_asm 
	{
		mov		ax,t
		call	XASM_SetTransparency
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ASM_SetLuminosity
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
inline	void ASM_SetLuminosity(SWord t)
{
	_asm 
	{
		push	eax
		mov		ax,t
		call	XASM_SetLuminosity
		pop		eax
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ASM_SetHeatHaze
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
inline	void ASM_SetHeatHaze(SWord t)
{
	_asm 
	{
		push	eax
		mov		ax,t
		call	XASM_SetHeatHaze
		pop		eax
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ASM_GetTransparency
//Author		Robert Slater
//Date			Tue 13 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline	SWord ASM_GetTransparency(void)
{
	SWord	t;
	_asm 
	{
		push	eax
		call	XASM_GetTransparency
		mov		t,ax
		pop		eax
	}
	return t;
}


//-----------------------------------------------------------------------------
// Procedure    ASM_SetFadeData
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
//inline	void ASM_SetFadeData(SLong a)
//{
//	_asm
//	{
//		mov		eax,a
//		call	XASM_SetFadeData
//	}
//}

//-----------------------------------------------------------------------------
// Procedure    ASM_PlainLine
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
inline	void ASM_PlainLine(SLong* a,SLong* b,UByte* c,SLong d)
{
	_asm
	{
		push	ecx
		mov		eax,a
		mov		edx,b
		mov		ebx,c
		mov		ecx,d
		call	XASM_PlainLine
		pop		ecx
	}
}

//-----------------------------------------------------------------------------
// Procedure    ASM_SetGrey3D
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
//#pragma warning (disable:4035)
//inline	GREY3DTYPE ASM_SetGrey3D(GREY3DTYPE t)
//{
//	_asm
//	{
//		mov		eax,t
//		call	XASM_SetGrey3D
//	}
//}
//#pragma warning (default:4035)

//-----------------------------------------------------------------------------
// Procedure    ASM_SetFaded3D
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
//#pragma warning (disable:4035)
//inline	GREY3DTYPE ASM_SetFaded3D(GREY3DTYPE t)
//{
//	_asm
//	{
//		mov		eax,t
//		call	XASM_SetFaded3D
//	}
//}
//#pragma warning (default:4035)

//-----------------------------------------------------------------------------
// Procedure    ASM_HoriLineAddr
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
#pragma warning (disable:4035)
inline	HoriLineRtnPtr ASM_HoriLineAddr(SCANLINETYPE t)
{
	_asm
	{
		mov		eax,t
		call	XASM_HoriLineAddr
	}
}
#pragma warning (default:4035)

//-----------------------------------------------------------------------------
// Procedure    ASM_SmokedGlassLine
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
inline	void ASM_SmokedGlassLine(UByte * a, VERTEX& b, VERTEX& c)
{
	_asm
	{
		mov		eax,a
		mov		edx,b
		mov		ebx,c
		call	XASM_SmokedGlassLine
	}
}
#endif
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim::ClearScreen
//------------------------------------------------------------------------------
//Author		JIM
//Date			Mon 3 Jul 1995
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
void Graphic::ClearScreen()
{
	short	wx1,wy1;
	short	w,h;

	wx1 = 	PhysicalMinX;
	w = 	PhysicalWidth;
	wy1 = 	PhysicalMinY;
	h = 	PhysicalHeight;

	PlainRectangleFill(wx1,wy1,w,h);			//PD 29Nov95

}

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
void Graphic::SetPixelWidth(SWord &pixwid)
{
	pixwid = ASM_SetPixelWidth(pixwid);
}

void* Graphic::GetPaletteTable()
{
	void* pal=ASM_GetPaletteTable();
	return pal;
}

void* Graphic::GetLandFadeTable()
{
	void* ptable=ASM_GetLandFadeTable();
	return ptable;
}

void* Graphic::GetSkyFadeTable()
{
	void *ptable=ASM_GetSkyFadeTable();
	return ptable;
}

void* Graphic::GetHorizonFadeTable()
{
	void* ptable=ASM_GetHorizonFadeTable();
	return ptable;
}

void Graphic::SelectPalette(SWord palNum)
{
	ASM_SelectPalette(palNum);
}

UWord Graphic::GetPaletteEntry(UWord c)
{
	return ASM_GetPaletteEntry(c);
}

void Graphic::SetPaletteEntry(UWord c,UWord v)
{
	ASM_SetPaletteEntry(c,v);
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
void Graphic::SetTransparency(SWord flag)
{
//DEAD	POLYGON.SelectAliasTable(flag);								//RJS 17Jun97
//DEAD 	ASM_SetTransparency(flag);
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
void Graphic::SetLuminosity(SWord flag)							//RJS 19Jan98
{																//RJS 19Jan98
//DEAD	POLYGON.SelectLuminousTable(flag);							//RJS 19Jan98
//DEAD 	ASM_SetLuminosity(flag);									//RJS 19Jan98
}																//RJS 19Jan98

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
void Graphic::SetHeatHaze(SWord flag)
{
//DEAD	POLYGON.SelectAliasTable(SMOKED_ON);
//DEAD 	ASM_SetHeatHaze(flag);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetColour
//Author		Paul.   
//Date			Wed 29 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::SetColour(Colour Col)
{
//DeadCode PD 07Nov95 	UWord	temp;

	colour = Col;

	//Identify which colour range we are in and set 'Range' to be 
	//the full range

//DeadCode PD 07Nov95 	temp = (UWord )Col;

	//The first sixteen colours are fixed single colours
	//Followed by one 16 colour range
	//Then one 32 colour range
	//Then ten 16 colour ranges
	//Then the explosion range
	//Then two masking colours
	//Then a single off-white colour

	if(Col<16 || Col>=FONTMASK)
	{
		range = 1;
	}
	else
	{
//DeadCode JIM 25Apr96 		if(Col>=RANGE01 && Col <(RANGE01+SPREAD01))
//DeadCode JIM 25Apr96 		{
//DeadCode JIM 25Apr96 			range	= SPREAD01;
//DeadCode JIM 25Apr96 		}
//DeadCode JIM 25Apr96 		else
//DeadCode PD 22Jul96 		{
//DeadCode PD 22Jul96 			if(Col>=EXPLO00)
//DeadCode PD 22Jul96 			{
//DeadCode PD 22Jul96 				range = 1;
//DeadCode PD 22Jul96 			}
//DeadCode PD 22Jul96 			else
		range	= SPREAD00;
	}

//DeadCode RJS 09Feb98 	ASM_SetColour(colour,0x02,0x02,imageptr);					//PD 04Jan96
	ASM_SetColour(colour,4,4,imageptr);					//RJS 09Feb98
//DeadCode PD 03Jan96 	makeshadetable();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	SetColour
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Mon 14 Aug 1995
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
void Graphic::SetColour(Colour Col,ColourRange CRng)
{
	if(CRng==-1)
	{
		//The first sixteen colours are fixed single colours
		//Followed by one 16 colour range
		//Then one 32 colour range
		//Then ten 16 colour ranges
		//Then the explosion range
		//Then two masking colours
		//Then a single off-white colour
	
		if(Col<16 || Col>=FONTMASK)
		{
			range = 1;
		}
		else
		{
//DeadCode PD 22Jul96 			if(Col>=RANGE01 && Col <(RANGE01+SPREAD01))
//DeadCode PD 22Jul96 			{
//DeadCode PD 22Jul96 				range = SPREAD01-(Col&(SPREAD01-1));
//DeadCode PD 22Jul96 			}
//DeadCode PD 22Jul96 			else
//DeadCode PD 22Jul96 			{
//DeadCode PD 22Jul96 				if(Col>=EXPLO00)
//DeadCode PD 22Jul96 				{
//DeadCode PD 22Jul96 					range = 1;
//DeadCode PD 22Jul96 				}
//DeadCode PD 22Jul96 				else
					range = SPREAD00 - (Col&(SPREAD00-1));
//DeadCode PD 22Jul96 			}
		}
	}
	else
	{
		range 	= CRng;
	}
	colour 	= Col;

	ASM_SetColour(colour,4,4,imageptr);					//RJS 09Feb98
//DeadCode RJS 09Feb98 	ASM_SetColour(colour,0x02,0x02,imageptr);					//PD 04Jan96
//DeadCode PD 03Jan96 	makeshadetable();
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
void Graphic::SetGlassRange(Colour clr)
{
	glasscolour = clr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetColour
//Author		Paul.   
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::SetColour(ImageMapDescPtr image)
{
	SWord	image_width,										//PD 05Dec95
			image_height;										//PD 05Dec95

	image_width = image->w-1;									//RJS 06Feb98
	image_height= image->h-1;									//RJS 06Feb98

	image_x_mask	= ((SLong )image_width)<<16;				//PD 05Dec95
	image_y_mask	= ((SLong )image_height)<<16;				//PD 05Dec95
//	image_y_shift	= (16-image->width);						//PD 05Dec95

	imageptr = image->body;										//RJS 06Feb98

	Colour c=(Colour)(ULong)image->alpha;

	ASM_SetColour(c,image->w,image->h,imageptr);	//PD 21Dec95
}

void Graphic::SetColour(ROWANSURFACEDESC* rsd)
{
	SWord image_width,image_height;
	image_width=rsd->dwWidth-1;
	image_height=rsd->dwHeight-1;
	image_x_mask=SLong(image_width)<<16;
	image_y_mask=SLong(image_height)<<16;
	imageptr=(UByte*)rsd->lpSurface;
	ASM_SetColour(colour,image_width+1,image_height+1,imageptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		makeshadetable
//Author		Paul.   
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode PD 03Jan96 void Graphic::makeshadetable()
//DeadCode PD 03Jan96 {
//DeadCode PD 03Jan96 	int	counter;
//DeadCode PD 03Jan96 
//DeadCode PD 03Jan96 	SLong	start_colour,
//DeadCode PD 03Jan96 			range_colour,
//DeadCode PD 03Jan96 			delta_colour;
//DeadCode PD 03Jan96 
//DeadCode PD 03Jan96 	start_colour= 	colour<<16;									//JIM 12Dec95
//DeadCode PD 03Jan96 
//DeadCode PD 03Jan96 	range_colour=	range<<16;									//JIM 12Dec95
//DeadCode PD 03Jan96 
//DeadCode PD 03Jan96 	delta_colour=	range_colour/SHADECOLOURMAX;
//DeadCode PD 03Jan96 
//DeadCode PD 03Jan96 	for(counter=0;counter<SHADECOLOURMAX;counter++)
//DeadCode PD 03Jan96 	{
//DeadCode PD 03Jan96 		shadetable[counter] = (Colour)(start_colour>>16);		//JIM 12Dec95
//DeadCode PD 03Jan96 		start_colour+=delta_colour;
//DeadCode PD 03Jan96 	}
//DeadCode PD 03Jan96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CirclePoints
//Author		Martin Alderton
//Date			Thu 21 Sep 1995
//
//Description	Dead Code.
//				
//Returns		
//
//Inputs			
//
//------------------------------------------------------------------------------
void Graphic::CirclePoints(SWord x, SWord y, SWord radius)
{
//DeadCode PD 30Oct95 	SetColour(WHITE);
//DeadCode MGA 13Nov95 	PlotPixel(screen,x,y);		   
//DeadCode MGA 13Nov95 	PlotPixel(screen,x-(radius/2),y-(3*radius/2));
//DeadCode MGA 13Nov95 	PlotPixedl(screen,x-(radius/2),y-(radius/2));
//DeadCode MGA 13Nov95 	PlotPixel(screen,x,y-(2*radius));
//DeadCode MGA 13Nov95 	PlotPixel(screen,x+radius,y-radius);
//DeadCode MGA 13Nov95 	PlotPixel(screen,x+(radius/2),y-(3*radius/2));
//DeadCode MGA 13Nov95 	PlotPixel(screen,x+(radius/2),y-(radius/2));
//DeadCode MGA 13Nov95 	PlotPixel(screen,x-radius,y-radius);
	
}


//DeadCode MGA 06Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
//DeadCode MGA 06Dec95 //Procedure	GrafPrim::PlainCircle
//DeadCode MGA 06Dec95 //------------------------------------------------------------------------------
//DeadCode MGA 06Dec95 //Author		Paul.   
//DeadCode MGA 06Dec95 //Date		Mon 3 Jul 1995
//DeadCode MGA 06Dec95 //Modified	
//DeadCode MGA 06Dec95 //
//DeadCode MGA 06Dec95 //Description	
//DeadCode MGA 06Dec95 //
//DeadCode MGA 06Dec95 //Inputs	
//DeadCode MGA 06Dec95 //
//DeadCode MGA 06Dec95 //Returns	
//DeadCode MGA 06Dec95 //
//DeadCode MGA 06Dec95 //Externals
//DeadCode MGA 06Dec95 //------------------------------------------------------------------------------
//DeadCode MGA 06Dec95 //------------------------------------------------------------------------------
//DeadCode MGA 06Dec95 void GrafPrim::PlainCircle(ScreenRecord *screen,short radius,short x1,short y1)
//DeadCode MGA 06Dec95 {
//DeadCode PD 29Nov95 	float angle,theta;
//DeadCode PD 29Nov95 	float x[60],y[60];
//DeadCode PD 29Nov95 	int i;
//DeadCode PD 29Nov95 	int n=60;
//DeadCode PD 29Nov95 	float M_PI=3.14257;
//DeadCode PD 29Nov95 	SWord sin_ang,cos_ang;
//DeadCode PD 29Nov95 
//DeadCode PD 29Nov95 	theta = 2*M_PI/n;
//DeadCode PD 29Nov95 
//DeadCode PD 29Nov95 	for (i=1;i<n+1;i++)
//DeadCode PD 29Nov95 	{
//DeadCode PD 29Nov95 		angle = theta * i;
//DeadCode PD 29Nov95  		Math_Lib.sin_cos((ANGLE)angle,sin_ang,cos_ang);			//PD 29Nov95
//DeadCode PD 29Nov95  		x[i] = (radius * sin_ang);
//DeadCode PD 29Nov95  		y[i] = (radius * cos_ang);
//DeadCode PD 29Nov95 	}
//DeadCode PD 29Nov95 	PlotPixel(screen,x[n-1]+x1,y[n-1]+y1);
//DeadCode PD 29Nov95 	for (i=1;i<n+1;i++)
//DeadCode PD 29Nov95 	{
//DeadCode PD 29Nov95 		if (i==1)
//DeadCode PD 29Nov95 			ClipLine(screen,x[n-1]+x1,y[n-1]+y1,x[1]+x1,y[1]+y1);
//DeadCode PD 29Nov95 		else
//DeadCode PD 29Nov95 			ClipLine(screen,x[i]+x1,y[i]+y1,x[i+1]+x1,y[i+1]+y1);
//DeadCode PD 29Nov95 	}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	grafprim::PlainCircle
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Mon 3 Jul 1995
//Modified	Martin 29 Nov 1995.
//
//Description Circle drawing routine using integer maths.	
//			  rewritten but untested. Problems with circles look here first.
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Graphic::PlainCircle(SWord radius, SWord x, SWord y)
{
	short x1,y1,x2,y2,x3,y3,x4,y4,d;
	SWord dist,sin_ang,cos_ang;

	Math_Lib.sin_cos(ANGLES_45Deg,sin_ang,cos_ang);

	dist = radius*cos_ang;

	x1=x3=x;
	y1=y+radius;
	y2=y4=y;
	x2=x+radius;
	y3=y-radius;
	x4=x-radius;
	d=1-radius;
	PlotPixel(x1,y1);
	PlotPixel(x2,y2);
	PlotPixel(x3,y3);
	PlotPixel(x4,y4);

	while (y1>y)
	{
		if (y1>=(y+dist))
		{
			if (d<0)
			{
				d+=x*2+3;
				x1++;
				y2--;
				x3--;
				y4++;
			}
			else
			{
				d+=(x-y)*2+5;
				x1++;
				y2--;
				x3--;
				y4++;
				y1--;
				x2--;
				y3++;
				x4++;
			}
		}
		else
		{
			if (d<0)
			{
				d+=x*2+3;
				y1--;
				x2--;
				y3++;
				x4++;
			}
			else
			{
				d+=(x-y)*2+5;
				y1--;
				x2--;
				y3++;
				x4++;
				x1++;
				y2--;
				x3--;
				y4++;
			}

		}
		PlotPixel(x1,y1);
		PlotPixel(x2,y2);
		PlotPixel(x3,y3);
		PlotPixel(x4,y4);
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim::PlainLine
//------------------------------------------------------------------------------
//Author	Paul & Martin   
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
void Graphic::PlainLine(SWord x1,SWord y1,SWord x2,SWord y2)
{
	SWord		transp = ASM_GetTransparency();

//	if (transp)
//		PlainLineTransparent(x1,y1,x2,y2,transp);
//	else
	{
		ROWANSURFACEDESC rsd;
		Master()->DoLockScr(&rsd);

		UWord*		scradr;

		SLong 		distx,	disty,
					x,		y,
					const1,	const2,
					p;

		UByte		linecol = colour;


		distx = x2 - x1;

		disty = y2 - y1;

		if (distx < 0)	distx = -distx;

		if (disty < 0)	disty = -disty;

		//Vertical case

		if (distx == 0)
		{
			y = (y2>y1)?y1:y2;

			x = x1;

			scradr = (UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch)+(x<<1));

			*scradr = linecol;	// PlotPixel(x,y);

			for (;disty--;scradr=(UWord*)(ULong(scradr)+rsd.lPitch),y++)
				*scradr = linecol;	//	PlotPixel(x,y);

			Master()->DoUnlockScr(&rsd);
			return;
		}

		//Horizontal case

		if (disty==0)
		{
			x = (x2>x1)?x1:x2;

			y = y1;

			scradr = (UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch)+(x<<1));

			*scradr = linecol;	// PlotPixel(x,y);

			for (;distx--;scradr++,x++)	*scradr = linecol;	// PlotPixel(x,y);

			Master()->DoUnlockScr(&rsd);
			return;
		}

		if (distx>disty)
		{
			const1 = disty + disty;

			const2 = const1 - distx - distx;

			p = const1 - distx;

			if (x1>x2)
			{
				x = x2; y = y2;
			}
			else
			{
				x = x1; y = y1;
			}

			scradr = (UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch)+(x<<1));

			*scradr = linecol;	// PlotPixel(x,y);

			if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
			{
				for (;distx--;)
				{
					x++;

					scradr++;

					if (p<0)
						p += const1;
					else
					{
						y++;

						scradr=(UWord*)(ULong(scradr)+rsd.lPitch);

						p += const2;
					}

					*scradr = linecol;	// PlotPixel(x,y);
				}
				Master()->DoUnlockScr(&rsd);
				return;
			}
			else
			{
				for (;distx--;)
				{
					x++;

					scradr++;

					if (p<0)
						p += const1;
					else
					{
						y--;

						scradr=(UWord*)(ULong(scradr)-rsd.lPitch);

						p += const2;
					}

					*scradr = linecol;	// PlotPixel(x,y);

				}
				Master()->DoUnlockScr(&rsd);
				return;
			}
		}

		if (disty>distx)
		{
			const1 = distx + distx;

			const2 = const1 - disty - disty;

			p = const1 - disty;

			if (y1>y2)
	 		{
	 			x = x2; y = y2;
	 		}
			else
	 		{
	 			x = x1; y = y1;
	 		}

			scradr = (UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch)+(x<<1));

			*scradr = linecol;	// PlotPixel(x,y);
		
			if ((y==y1 && x2>x1) || (y==y2 && x1>x2))
 			{
 				for (;disty--;)
 				{
 					y++;

					scradr=(UWord*)(ULong(scradr)+rsd.lPitch);

	 				if (p<0)
	 					p += const1;
	 				else
	 				{
	 					x++;

						scradr++;

	 					p += const2;
	 				}

	 				*scradr = linecol;	// PlotPixel(x,y);
	 			}
				Master()->DoUnlockScr(&rsd);
				return;
	 		}
			else
	 		{
	 			for (;disty--;)
	 			{
	 				y++;

					scradr=(UWord*)(ULong(scradr)+rsd.lPitch);

	 				if (p<0)
	 					p += const1;
	 				else
	 				{
	 					x--;

						scradr--;

	 					p += const2;
	 				}

	 				*scradr = linecol;	// PlotPixel(x,y);
	 			}
				Master()->DoUnlockScr(&rsd);
				return;
	 		}
		}

		//If we get here distx == disty

		if (x1>x2)
		{
			x = x2; y = y2;
		}
		else
		{
	 		x = x1; y = y1;
		}

		scradr = (UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch)+(x<<1));

		*scradr = linecol;	// PlotPixel(x,y);

		if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
		{
			for (;distx--;)
			{
				x++; y++;

				scradr=(UWord*)(ULong(scradr)+rsd.lPitch+2);

				*scradr = linecol;	// PlotPixel(x,y);
			}
		}
		else 
		{
			for (;distx--;)
			{
				x++; y--;

				scradr=(UWord*)(ULong(scradr)-rsd.lPitch+2);

				*scradr = linecol;	// PlotPixel(x,y);
			}
		}
		Master()->DoUnlockScr(&rsd);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlainLine16
//Author		Paul.   
//Date			Wed 28 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
extern UWord polyRedBits,polyRedShift,polyGreenBits,polyGreenShift,polyBlueBits,polyBlueShift;

void Graphic::PlainLine16(SWord x1,SWord y1,SWord x2,SWord y2)
{
	UWord*	scradr;
	ROWANSURFACEDESC rsd;
	Master()->DoLockScr(&rsd);

	SLong 		distx,	disty,
				x,		y,
				const1,	const2,
				p;

	UWord		red,green,blue;

	typedef	struct rgb { UByte r,g,b; }	*rgbptr;

	rgbptr	lpPal = (rgbptr)Palette;

	red = lpPal[colour].r; green = lpPal[colour].g; blue = lpPal[colour].b;

	UWord
	linecol =	(red>>(8-polyRedBits))		<< polyRedShift;			//RDH 16Oct97
	linecol += 	(green>>(8-polyGreenBits))	<< polyGreenShift;			//RDH 16Oct97
	linecol += 	(blue>>(8-polyBlueBits))	<< polyBlueShift;			//RDH 16Oct97

	distx = x2 - x1;

	disty = y2 - y1;

	if (distx < 0)	distx = -distx;

	if (disty < 0)	disty = -disty;

	//Vertical case

	if (distx == 0)
	{
		y = (y2>y1)?y1:y2;

		x = x1;

		scradr = (UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch)+(x<<1));

		*(UWord*)scradr = linecol;					// PlotPixel(x,y);

		for (;disty--;scradr=(UWord*)(ULong(scradr)+rsd.lPitch),y++)
			*(UWord*)scradr = linecol;				//	PlotPixel(x,y);

		Master()->DoUnlockScr(&rsd);
		return;
	}

	//Horizontal case

	if (disty==0)
	{
		x = (x2>x1)?x1:x2;

		y = y1;

		scradr=(UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch) + (x<<1));

		*(UWord*)scradr = linecol;					// PlotPixel(x,y);

		for (;distx--;scradr++,x++)
			*(UWord*)scradr = linecol;				// PlotPixel(x,y);

		Master()->DoUnlockScr(&rsd);
		return;
	}

	if (distx>disty)
	{
		const1 = disty + disty;

		const2 = const1 - distx - distx;

		p = const1 - distx;

		if (x1>x2)
		{
			x = x2; y = y2;
		}
		else
		{
			x = x1; y = y1;
		}

		scradr = (UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch)+(x<<1));

		*(UWord*)scradr = linecol;					// PlotPixel(x,y);

		if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
		{
			for (;distx--;)
			{
				x++;

				scradr++;

				if (p<0)
					p += const1;
				else
				{
					y++;

					scradr=(UWord*)(ULong(scradr)+rsd.lPitch);

					p += const2;
				}

				*(UWord*)scradr = linecol;			// PlotPixel(x,y);
			}
			Master()->DoUnlockScr(&rsd);
			return;
		}
		else
		{
			for (;distx--;)
			{
				x++;

				scradr++;

				if (p<0)
					p += const1;
				else
				{
					y--;

					scradr=(UWord*)(ULong(scradr)-rsd.lPitch);

					p += const2;
				}

				*(UWord*)scradr = linecol;				// PlotPixel(x,y);

			}
			Master()->DoUnlockScr(&rsd);
			return;
		}
	}

	if (disty>distx)
	{
		const1 = distx + distx;

		const2 = const1 - disty - disty;

		p = const1 - disty;

		if (y1>y2)
	 	{
	 		x = x2; y = y2;
	 	}
		else
	 	{
	 		x = x1; y = y1;
	 	}

		scradr = (UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch)+(x<<1));

		*(UWord*)scradr = linecol;			// PlotPixel(x,y);
		
		if ((y==y1 && x2>x1) || (y==y2 && x1>x2))
 		{
 			for (;disty--;)
 			{
 				y++;

				scradr=(UWord*)(ULong(scradr)+rsd.lPitch);

	 			if (p<0)
	 				p += const1;
	 			else
	 			{
	 				x++;

					scradr++;

	 				p += const2;
	 			}

	 			*(UWord*)scradr = linecol;			// PlotPixel(x,y);
	 		}
			Master()->DoUnlockScr(&rsd);
			return;
	 	}
		else
	 	{
	 		for (;disty--;)
	 		{
	 			y++;

				scradr=(UWord*)(ULong(scradr)+rsd.lPitch);

	 			if (p<0)
	 				p += const1;
	 			else
	 			{
	 				x--;

					scradr--;

	 				p += const2;
	 			}

	 			*(UWord*)scradr = linecol;				// PlotPixel(x,y);
	 		}
			Master()->DoUnlockScr(&rsd);
			return;
	 	}
	}

	//If we get here distx == disty

	if (x1>x2)
	{
		x = x2; y = y2;
	}
	else
	{
	 	x = x1; y = y1;
	}

	scradr = (UWord*)(ULong(rsd.lpSurface)+(y*rsd.lPitch)+(x<<1));

	*(UWord*)scradr = linecol;							// PlotPixel(x,y);

	if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
	{
		for (;distx--;)
		{
			x++; y++;

			scradr=(UWord*)(ULong(scradr)+rsd.lPitch+2);

			*(UWord*)scradr = linecol;					// PlotPixel(x,y);
		}
	}
	else 
	{
		for (;distx--;)
		{
			x++; y--;

			scradr=(UWord*)(ULong(scradr)-rsd.lPitch+2);

			*(UWord*)scradr = linecol;					// PlotPixel(x,y);
		}
	}
	Master()->DoUnlockScr(&rsd);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlainLineTransparent
//Author		Robert Slater
//Date			Tue 13 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::PlainLineTransparent(SWord x1,SWord y1,SWord x2,SWord y2, SWord depth)
{
//TempCode PD 17Apr99 	LogicalPtr	scradr;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	SLong 		distx,	disty,
//TempCode PD 17Apr99 				x,		y,
//TempCode PD 17Apr99 				const1,	const2,
//TempCode PD 17Apr99 				p;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	UByte		linecol = colour;
//TempCode PD 17Apr99 	UByteP		aliasptr = POLYGON.WhichAliasTable(depth);
//TempCode PD 17Apr99 	UByteP		aliaslineptr;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	distx = x2 - x1;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	disty = y2 - y1;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	if (distx < 0)	distx = -distx;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	if (disty < 0)	disty = -disty;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	//Vertical case
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	if (depth > SMOKED_LIGHT)
//TempCode PD 17Apr99 	{
//TempCode PD 17Apr99 		aliaslineptr = (UByteP) (aliasptr + (linecol<<8));
//TempCode PD 17Apr99 		if (distx == 0)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			y = (y2>y1)?y1:y2;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			x = x1;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			*scradr = linecol;	// PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			for (;disty--;scradr+=BytesPerScanLine,y++)
//TempCode PD 17Apr99 				*scradr = aliaslineptr[*scradr];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			Master()->UnLockBackScreen (LOWLOCK);				//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			return;
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		//Horizontal case
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if (disty==0)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			x = (x2>x1)?x1:x2;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			y = y1;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			for (;distx--;scradr+=BytesPerPixel,x++)
//TempCode PD 17Apr99 				*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			Master()->UnLockBackScreen (LOWLOCK);				//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			return;
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if (distx>disty)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			const1 = disty + disty;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			const2 = const1 - distx - distx;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			p = const1 - distx;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			if (x1>x2)
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				x = x2; y = y2;
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 			else
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				x = x1; y = y1;
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 			*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				for (;distx--;)
//TempCode PD 17Apr99 				{
//TempCode PD 17Apr99 					x++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					scradr += BytesPerPixel;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					if (p<0)
//TempCode PD 17Apr99 						p += const1;
//TempCode PD 17Apr99 					else
//TempCode PD 17Apr99 					{
//TempCode PD 17Apr99 						y++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						scradr += BytesPerScanLine;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						p += const2;
//TempCode PD 17Apr99 					}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 				}
//TempCode PD 17Apr99 				Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				return;
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 			else
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				for (;distx--;)
//TempCode PD 17Apr99 				{
//TempCode PD 17Apr99 					x++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					scradr += BytesPerPixel;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					if (p<0)
//TempCode PD 17Apr99 						p += const1;
//TempCode PD 17Apr99 					else
//TempCode PD 17Apr99 					{
//TempCode PD 17Apr99 						y--;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						scradr -= BytesPerScanLine;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						p += const2;
//TempCode PD 17Apr99 					}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				}
//TempCode PD 17Apr99 				Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				return;
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if (disty>distx)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			const1 = distx + distx;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			const2 = const1 - disty - disty;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			p = const1 - disty;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			if (y1>y2)
//TempCode PD 17Apr99 	 		{
//TempCode PD 17Apr99 	 			x = x2; y = y2;
//TempCode PD 17Apr99 	 		}
//TempCode PD 17Apr99 			else
//TempCode PD 17Apr99 	 		{
//TempCode PD 17Apr99 	 			x = x1; y = y1;
//TempCode PD 17Apr99 	 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 			*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 			
//TempCode PD 17Apr99 			if ((y==y1 && x2>x1) || (y==y2 && x1>x2))
//TempCode PD 17Apr99  			{
//TempCode PD 17Apr99  				for (;disty--;)
//TempCode PD 17Apr99  				{
//TempCode PD 17Apr99  					y++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					scradr += BytesPerScanLine;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 				if (p<0)
//TempCode PD 17Apr99 	 					p += const1;
//TempCode PD 17Apr99 	 				else
//TempCode PD 17Apr99 	 				{
//TempCode PD 17Apr99 	 					x++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						scradr += BytesPerPixel;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 					p += const2;
//TempCode PD 17Apr99 	 				}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 				*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 	 			}
//TempCode PD 17Apr99 				Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				return;
//TempCode PD 17Apr99 	 		}
//TempCode PD 17Apr99 			else
//TempCode PD 17Apr99 	 		{
//TempCode PD 17Apr99 	 			for (;disty--;)
//TempCode PD 17Apr99 	 			{
//TempCode PD 17Apr99 	 				y++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					scradr += BytesPerScanLine;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 				if (p<0)
//TempCode PD 17Apr99 	 					p += const1;
//TempCode PD 17Apr99 	 				else
//TempCode PD 17Apr99 	 				{
//TempCode PD 17Apr99 	 					x--;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						scradr -= BytesPerPixel;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 					p += const2;
//TempCode PD 17Apr99 	 				}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 				*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 	 			}
//TempCode PD 17Apr99 				Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				return;
//TempCode PD 17Apr99 	 		}
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		//If we get here distx == disty
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if (x1>x2)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			x = x2; y = y2;
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 		else
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 	 		x = x1; y = y1;
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			for (;distx--;)
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				x++; y++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				scradr += BytesPerScanLine + BytesPerPixel;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 		else 
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			for (;distx--;)
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				x++; y--;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				scradr += BytesPerPixel - BytesPerScanLine;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				*scradr = aliaslineptr[*scradr];	// PlotPixel(x,y);
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 	}
//TempCode PD 17Apr99 	else
//TempCode PD 17Apr99 	{
//TempCode PD 17Apr99 		if (distx == 0)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			y = (y2>y1)?y1:y2;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			x = x1;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			*scradr = linecol;	// PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			for (;disty--;scradr+=BytesPerScanLine,y++)
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 				*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			Master()->UnLockBackScreen (LOWLOCK);				//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			return;
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		//Horizontal case
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if (disty==0)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			x = (x2>x1)?x1:x2;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			y = y1;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 			*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			for (;distx--;scradr+=BytesPerPixel,x++)
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 				*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			Master()->UnLockBackScreen (LOWLOCK);				//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			return;
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if (distx>disty)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			const1 = disty + disty;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			const2 = const1 - distx - distx;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			p = const1 - distx;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			if (x1>x2)
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				x = x2; y = y2;
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 			else
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				x = x1; y = y1;
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 			aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 			*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				for (;distx--;)
//TempCode PD 17Apr99 				{
//TempCode PD 17Apr99 					x++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					scradr += BytesPerPixel;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					if (p<0)
//TempCode PD 17Apr99 						p += const1;
//TempCode PD 17Apr99 					else
//TempCode PD 17Apr99 					{
//TempCode PD 17Apr99 						y++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						scradr += BytesPerScanLine;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						p += const2;
//TempCode PD 17Apr99 					}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 					*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 				}
//TempCode PD 17Apr99 				Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				return;
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 			else
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				for (;distx--;)
//TempCode PD 17Apr99 				{
//TempCode PD 17Apr99 					x++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					scradr += BytesPerPixel;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					if (p<0)
//TempCode PD 17Apr99 						p += const1;
//TempCode PD 17Apr99 					else
//TempCode PD 17Apr99 					{
//TempCode PD 17Apr99 						y--;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						scradr -= BytesPerScanLine;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						p += const2;
//TempCode PD 17Apr99 					}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 					*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 				}
//TempCode PD 17Apr99 				Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				return;
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if (disty>distx)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			const1 = distx + distx;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			const2 = const1 - disty - disty;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			p = const1 - disty;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			if (y1>y2)
//TempCode PD 17Apr99 	 		{
//TempCode PD 17Apr99 	 			x = x2; y = y2;
//TempCode PD 17Apr99 	 		}
//TempCode PD 17Apr99 			else
//TempCode PD 17Apr99 	 		{
//TempCode PD 17Apr99 	 			x = x1; y = y1;
//TempCode PD 17Apr99 	 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 			scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 			aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 			*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 			
//TempCode PD 17Apr99 			if ((y==y1 && x2>x1) || (y==y2 && x1>x2))
//TempCode PD 17Apr99  			{
//TempCode PD 17Apr99  				for (;disty--;)
//TempCode PD 17Apr99  				{
//TempCode PD 17Apr99  					y++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					scradr += BytesPerScanLine;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 				if (p<0)
//TempCode PD 17Apr99 	 					p += const1;
//TempCode PD 17Apr99 	 				else
//TempCode PD 17Apr99 	 				{
//TempCode PD 17Apr99 	 					x++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						scradr += BytesPerPixel;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 					p += const2;
//TempCode PD 17Apr99 	 				}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 					*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 	 			}
//TempCode PD 17Apr99 				Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				return;
//TempCode PD 17Apr99 	 		}
//TempCode PD 17Apr99 			else
//TempCode PD 17Apr99 	 		{
//TempCode PD 17Apr99 	 			for (;disty--;)
//TempCode PD 17Apr99 	 			{
//TempCode PD 17Apr99 	 				y++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					scradr += BytesPerScanLine;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 				if (p<0)
//TempCode PD 17Apr99 	 					p += const1;
//TempCode PD 17Apr99 	 				else
//TempCode PD 17Apr99 	 				{
//TempCode PD 17Apr99 	 					x--;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 						scradr -= BytesPerPixel;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	 					p += const2;
//TempCode PD 17Apr99 	 				}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 					aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 					*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 	 			}
//TempCode PD 17Apr99 				Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				return;
//TempCode PD 17Apr99 	 		}
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		//If we get here distx == disty
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if (x1>x2)
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			x = x2; y = y2;
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 		else
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 	 		x = x1; y = y1;
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);
//TempCode PD 17Apr99 		aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 		*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 		if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			for (;distx--;)
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				x++; y++;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				scradr += BytesPerScanLine + BytesPerPixel;
//TempCode PD 17Apr99 				aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 				*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 		else 
//TempCode PD 17Apr99 		{
//TempCode PD 17Apr99 			for (;distx--;)
//TempCode PD 17Apr99 			{
//TempCode PD 17Apr99 				x++; y--;
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 				scradr += BytesPerPixel - BytesPerScanLine;
//TempCode PD 17Apr99 				aliaslineptr = (UByteP) (aliasptr + (*scradr<<8));
//TempCode PD 17Apr99 				*scradr = aliaslineptr[linecol];	//	PlotPixel(x,y);
//TempCode PD 17Apr99 			}
//TempCode PD 17Apr99 		}
//TempCode PD 17Apr99 	}
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 
//TempCode PD 17Apr99 	Master()->UnLockBackScreen (LOWLOCK);					//AMM 02May97
	
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CompOutCode
//Author		Martin Alderton
//Date			Wed 20 Sep 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
OutCode Graphic::CompOutCode(SWord x,SWord y)
{
	short XMin,XMax,YMin,YMax;
	OutCode code;
	code.top=0,code.bottom=0,code.right=0,code.left=0,code.all=0;
	XMin = PhysicalMinX;
	XMax = PhysicalMaxX;	// + PhysicalWidth;					//RDH 06Nov96
	YMin = PhysicalMinY;
	YMax = PhysicalMaxY;	// + PhysicalHeight;				//RDH 06Nov96

	if (y>YMax)
		{
			code.top=8;
			code.all +=code.top;
		}
	else if (y<YMin)
		{
			code.bottom=4;
			code.all +=code.bottom;
		}
	if (x>XMax)
		{
			code.right=2;
			code.all +=code.right;
		}
	else if (x<XMin)
		{
			code.left=1;
			code.all +=code.left;
		}
	return code;
}
	


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipLine
//Author		Martin Alderton
//Date			Wed 20 Sep 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::ClipLine(SWord x1, SWord y1, SWord x2, SWord y2)
{
	SWord done,accept,x,y,XMin,XMax,YMin,YMax;
	outcode outcode1, outcode2, outcodeOut,ClipCode;


	XMin = PhysicalMinX;
	XMax = PhysicalMaxX; //+ PhysicalWidth;						//RDH 06Nov96
	YMin = PhysicalMinY;
	YMax = PhysicalMaxY; //+ PhysicalHeight;					//RDH 06Nov96
	
	done=0;
	accept=0;
	outcode1=CompOutCode(x1,y1);
	outcode2=CompOutCode(x2,y2);
	do
		{
			if (outcode1.all==0 && outcode2.all==0)
				{
					done=1;
					accept=1;
				}
			else if ((outcode1.all & outcode2.all) !=0)
				{
					done =1;
				}
			else
				{
					if(outcode1.all != 0)
						ClipCode=outcodeOut=outcode1;
					else
						ClipCode=outcodeOut=outcode2;
					if (outcodeOut.top)
						{
							x=x1+(((x2-x1)*(YMax-y1))/(y2-y1));
							y=YMax;
						}
					else if(outcodeOut.bottom)
						{
							x=x1+(((x2-x1)*(YMin-y1))/(y2-y1));
							y=YMin;
						}
					else if(outcodeOut.right)
						{
							y=y1+(((y2-y1)*(XMax-x1))/(x2-x1));
							x=XMax;
						}
					else if(outcodeOut.left)
						{
							y=y1+(((y2-y1)*(XMin-x1))/(x2-x1));
							x=XMin;
						}
					if (outcodeOut.all==outcode1.all)
						{
							x1=x;
							y1=y;
							outcode1=CompOutCode(x1,y1);
						}
					else
						{
							x2=x;
							y2=y;
							outcode2=CompOutCode(x2,y2);
						}
				}
		}
	while (done !=1);

	if (accept==1)
		{
		if (BytesPerPixel==1)		PlainLine(x1,y1,x2,y2);
		else if (BytesPerPixel==2)	PlainLine16(x1,y1,x2,y2);
		}
							

//DeadCode PD 29Nov95 	return (0);	//temp value.
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CompOutCode
//Author		Martin Alderton
//Date			Wed 20 Sep 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
OutCode Graphic::Comp3DOutCode(SLong x,SLong y)
{
	SLong XMin,XMax,YMin,YMax;
	OutCode code;
	code.top=0,code.bottom=0,code.right=0,code.left=0,code.all=0;
	XMin = 0;
	XMax = PhysicalWidth;
	YMin = 0;
	YMax = PhysicalHeight;

	if (y>YMax)
		{
			code.top=8;
			code.all +=code.top;
		}
	else if (y<YMin)
		{
			code.bottom=4;
			code.all +=code.bottom;
		}
	if (x>XMax)
		{
			code.right=2;
			code.all +=code.right;
		}
	else if (x<XMin)
		{
			code.left=1;
			code.all +=code.left;
		}
	return code;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipLine
//Author		Martin Alderton
//Date			Wed 20 Sep 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
enum	OutCodes
{
	oc_NULL		= 0x0000,
	oc_Top		= 0x0001,
	oc_Bottom	= 0x0002,
	oc_Left		= 0x0004,
	oc_Right	= 0x0008
};

OutCodes operator|=(OutCodes oc,OutCodes oc2) {return (OutCodes)((int)oc|(int)oc2);}

void Graphic::ClipLine3D(SLong x1, SLong y1, SLong x2, SLong y2,SWord Xscale,SWord Yscale)
{

#define COMPOCODE(x,y,oc)\
{\
	if ((x)<PhysicalMinX)		oc=oc_Left;\
	else if ((x)>PhysicalMaxX)	oc=oc_Right;\
	else						oc=oc_NULL;\
	\
	if ((y)<PhysicalMinY)		oc|=oc_Top;\
	else if ((y)>PhysicalMaxY)	oc|=oc_Bottom;\
}

#define COMPFCODE(x,y,oc)\
{\
	if ((x)<XMin)		oc=oc_Left;\
	else if ((x)>XMax)	oc=oc_Right;\
	else						oc=oc_NULL;\
	\
	if ((y)<YMin)		oc|=oc_Top;\
	else if ((y)>YMax)	oc|=oc_Bottom;\
}

#define	CLIPPER(inval,outval,clipval,otherin,otherout)\
{\
	Float	frac;\
	frac = ((clipval)-(inval))/((outval)-(inval));\
	(outval)=(clipval);\
	(otherout)=(otherin) + frac * ((otherout)-(otherin));\
}

	OutCodes	oc1,oc2;

	COMPOCODE(x1,y1,oc1);

	COMPOCODE(x2,y2,oc2);

	//Test for trivial accept/reject

	if ((oc1 & oc2)!=oc_NULL)	return;		//REJECT!

	if ((oc1 | oc2)==oc_NULL)
	{
	 	//ACCEPT!

		if (BytesPerPixel==1)
			PlainLine((SWord)x1,(SWord)y1,(SWord)x2,(SWord)y2);
		else if (BytesPerPixel==2)
			PlainLine16((SWord)x1,(SWord)y1,(SWord)x2,(SWord)y2);
	}
	else
	{
		//CLIP!!
	
		Float	XMin,	XMax,	YMin,	YMax;

		Float	fx1,	fy1,	fx2,	fy2;

		XMin = PhysicalMinX;	XMax = PhysicalMaxX;
		YMin = PhysicalMinY;	YMax = PhysicalMaxY;

		fx1 = x1;	fy1 = y1;
		fx2 = x2;	fy2 = y2;

		//Clip to top

		if ((oc1 & oc_Top)!=oc_NULL)
		{
			CLIPPER(fy2,fy1,YMin,fx2,fx1);

			COMPFCODE(fx1,fy1,oc1);
		}
		else if ((oc2 & oc_Top)!=oc_NULL)
		{
			CLIPPER(fy1,fy2,YMin,fx1,fx2);

			COMPFCODE(fx2,fy2,oc2);
		}

		if ((oc1 & oc2)!=oc_NULL)	return;		//REJECT!

		//Clip to bottom

		if ((oc1 & oc_Bottom)!=oc_NULL)
		{
			CLIPPER(fy2,fy1,YMax,fx2,fx1);

			COMPFCODE(fx1,fy1,oc1);
		}
		else if ((oc2 & oc_Bottom)!=oc_NULL)
		{
			CLIPPER(fy1,fy2,YMax,fx1,fx2);

			COMPFCODE(fx2,fy2,oc2);
		}

		if ((oc1 & oc2)!=oc_NULL)	return;		//REJECT!

		//Clip to left

		if ((oc1 & oc_Left)!=oc_NULL)
		{
			CLIPPER(fx2,fx1,XMin,fy2,fy1);

			COMPFCODE(fx1,fy1,oc1);
		}
		else if ((oc2 & oc_Left)!=oc_NULL)
		{
			CLIPPER(fx1,fx2,XMin,fy1,fy2);

			COMPFCODE(fx2,fy2,oc2);
		}

		if ((oc1 & oc2)!=oc_NULL)	return;		//REJECT!

		//Clip to right

		if ((oc1 & oc_Right)!=oc_NULL)
		{
			CLIPPER(fx2,fx1,XMax,fy2,fy1);

			COMPFCODE(fx1,fy1,oc1);
		}
		else if ((oc2 & oc_Right)!=oc_NULL)
		{
			CLIPPER(fx1,fx2,XMax,fy1,fy2);

			COMPFCODE(fx2,fy2,oc2);
		}

		if ((oc1 & oc2)!=oc_NULL)	return;		//REJECT!

		x1 = fx1; y1 = fy1;
		x2 = fx2; y2 = fy2;

		if (BytesPerPixel==1)
			PlainLine((SWord)x1,(SWord)y1,(SWord)x2,(SWord)y2);
		else if (BytesPerPixel==2)
			PlainLine16((SWord)x1,(SWord)y1,(SWord)x2,(SWord)y2);
	}
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
void Graphic::ClipLine3D(Float X1, Float Y1, Float X2, Float Y2,
							SWord	Xscale, SWord	Yscale)
{
	SLong	x1,y1,x2,y2;
	SLong x,y,XMin,XMax,YMin,YMax;
	outcode outcode1, outcode2, outcodeOut,ClipCode;
	Bool  done,accept;

	x1 = X1;// / (Float)Xscale;
	x2 = X2;// / (Float)Xscale;
	y1 = Y1;// / (Float)Yscale;
	y2 = Y2;// / (Float)Yscale;

	XMin = 0;	//PhysicalMinX;
	XMax = PhysicalWidth;						//RDH 06Nov96
	YMin = 0;	//PhysicalMinY;
	YMax = PhysicalHeight;					//RDH 06Nov96
	
	done=FALSE;
	accept=FALSE;
	outcode1=Comp3DOutCode(x1,y1);
	outcode2=Comp3DOutCode(x2,y2);
	do
	{
		if (outcode1.all==0 && outcode2.all==0)
		{
			done=TRUE;
			accept=TRUE;
		}
		else if ((outcode1.all & outcode2.all) !=0)
			{
				done =TRUE;
			}
		else
			{
				if(outcode1.all != 0)
					ClipCode=outcodeOut=outcode1;
				else
					ClipCode=outcodeOut=outcode2;

				if (outcodeOut.top)
				{
					x=x1+(((x2-x1)*(YMax-y1))/(y2-y1));
					y=YMax;
				}
				else if(outcodeOut.bottom)
					{
						x=x1+(((x2-x1)*(YMin-y1))/(y2-y1));
						y=YMin;
					}
				else if(outcodeOut.right)
					{
						y=y1+(((y2-y1)*(XMax-x1))/(x2-x1));
						x=XMax;
					}
				else if(outcodeOut.left)
					{
						y=y1+(((y2-y1)*(XMin-x1))/(x2-x1));
						x=XMin;
					}
				if (outcodeOut.all==outcode1.all)
				{
					x1=x;
					y1=y;
					outcode1=CompOutCode(x1,y1);
				}
				else
				{
					x2=x;
					y2=y;
					outcode2=CompOutCode(x2,y2);
				}
			}
	}
	while (!done);

	if (accept)
	{
 		PlainLine16((SWord)x1,(SWord)y1,(SWord)x2,(SWord)y2);
	}
}




//DeadCode PD 30Oct95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode PD 30Oct95 //Procedure	GrafPrim::PlaneHoriLine
//DeadCode PD 30Oct95 //------------------------------------------------------------------------------
//DeadCode PD 30Oct95 //Author		Paul.   
//DeadCode PD 30Oct95 //Date		Mon 3 Jul 1995
//DeadCode PD 30Oct95 //Modified	
//DeadCode PD 30Oct95 //
//DeadCode PD 30Oct95 //Description	
//DeadCode PD 30Oct95 //
//DeadCode PD 30Oct95 //Inputs	
//DeadCode PD 30Oct95 //
//DeadCode PD 30Oct95 //Returns	
//DeadCode PD 30Oct95 //
//DeadCode PD 30Oct95 //Externals
//DeadCode PD 30Oct95 //------------------------------------------------------------------------------
//DeadCode PD 30Oct95 //------------------------------------------------------------------------------
//DeadCode PD 30Oct95 Bool GrafPrim::PlaneHoriLine(ScreenRecord *screen, SWord leftx, SWord rightx, SWord y)
//DeadCode PD 30Oct95 {
//DeadCode PD 30Oct95 	return(TRUE);
//DeadCode PD 30Oct95 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim::RegisterPalette
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
void Graphic::RegisterPalette(UByte *src, SLong length)
{
	int		i;
	UByte	*dest;

	if(Palette == NULL)
		Palette = new PAL;

	dest = (UByte *)Palette;

	while(--length!=0)
	{
		if (*dest++ != *src++)
		{
			*(dest-1) = *(src-1);
			while (--length!=0)
				*dest++ = *src++;
			UseNewPal = TRUE;
			return;
		}
	}
//DeadCode ARM 04Jul96 	UseNewPal = TRUE;
//	UseNewPal = FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReinitDisplay
//Author		Paul.   
//Date			Thu 3 Jul 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::ReinitDisplay()
{
	UseNewPal=TRUE;
}

//DeadCode ARM 27Jun96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode ARM 27Jun96 //Procedure	GrafPrim::RegisterPaletteSmk
//DeadCode ARM 27Jun96 //------------------------------------------------------------------------------
//DeadCode ARM 27Jun96 //Procedure		Date
//DeadCode ARM 27Jun96 //Author		Dave Whiteside
//DeadCode ARM 27Jun96 //Date			Wed 7 Feb 1996
//DeadCode ARM 27Jun96 //
//DeadCode ARM 27Jun96 //Description	Register a palette from the smack buffer
//DeadCode ARM 27Jun96 //
//DeadCode ARM 27Jun96 //Inputs		smack pointer
//DeadCode ARM 27Jun96 //
//DeadCode ARM 27Jun96 //Returns		new Palette flag set
//DeadCode ARM 27Jun96 //
//DeadCode ARM 27Jun96 //------------------------------------------------------------------------------
//DeadCode ARM 27Jun96 void Graphic::RegisterPaletteSmk(Smack* smk)
//DeadCode ARM 27Jun96 {
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	UByte	*dest;
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	UByte	*src;
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	if (smk->CurPalette==1)
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		src=(UByte *)smk->Col1;
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	else
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		src=(UByte *)smk->Col2;
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	if(Palette == NULL)
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		Palette = new PAL;
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	dest = (UByte *)Palette;
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	for (int i=768;i;i--)
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		*dest++ = *src++;
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	UseNewPal = TRUE;
//DeadCode ARM 27Jun96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim::PlainCircleFill
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
void Graphic::PlainCircleFill()
{

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim::PlainRectangleFill
//LastModified:	PD 20Dec95
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Mon 3 Jul 1995
//Modified		Put Jims optimised version back in and made alterations to
//				fit in with his other graphics library edits. 
//				New version is nothing like the old one!!!!!!!
//
//Description	
//
//Inputs	
//
//Returns	clip result
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
UWord Graphic::PlainRectangleFill(SWord X,SWord Y,SWord W,SWord H)
{	
	LogicalPtr	scradr,
				scanlineaddr;

	int		i,j;

	UWord	clipvar = 0;

	//Clip the rectangle to the screen

	if((Y+H) <= PhysicalMinY)
		clipvar |= 0x0003;

	if(Y >= PhysicalMinY+PhysicalHeight)
		clipvar |= 0x0003;
	
	if((X+W) <= PhysicalMinX)
		clipvar |= 0x000C;

	if(X >= PhysicalMinX+PhysicalWidth)
		clipvar |= 0x000C;

	if(clipvar)
		return(clipvar);

	if(Y < PhysicalMinY)
	{
		H -=	(PhysicalMinY-Y);
		Y = 	PhysicalMinY;
		clipvar |= 0x0001;
	}

	if((Y+H) > (PhysicalMinY+PhysicalHeight))
	{
		H -=	((Y+H)-(PhysicalMinY+PhysicalHeight));
		clipvar |= 0x0002;
	}

	if(X < PhysicalMinX)
	{
		W -= (PhysicalMinX-X);
		X = 	PhysicalMinX;
		clipvar |= 0x0004;
	}

	if((X+W) > (PhysicalMinX+PhysicalWidth))
	{
		W -= ((X+W)-(PhysicalMinX+PhysicalWidth));
		clipvar |= 0x0008;
	}

	//Calculate the screen address of the top left corner of the rectangle

	scradr = logicalscreenptr +
			 BytesPerScanLine * Y +
			 BytesPerPixel * X;

	ULong	lcolour=((ULong)0x01010101)* ((UByte) colour);

//DEAD 	Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97

	for(i=H;i>0;i--)
	{
		scanlineaddr = scradr;
		j=W-3;
		if	((ULong )scanlineaddr &0x00000003)
		{
			*(char*) (scanlineaddr++) = colour;
			j--;
			if	((ULong )scanlineaddr &0x00000003)
			{
				*(char*) (scanlineaddr++) = colour;
				j--;
				if	((ULong )scanlineaddr &0x00000003)
				{
					*(char*) (scanlineaddr++) = colour;
					j--;
		}	}	}
		scradr += BytesPerScanLine;
		while(j>0)
		{
			*(ULong *)scanlineaddr = lcolour;
			scanlineaddr+=4;
			j-=4;
		}
		for(j=j+3;j>0;j--)
			*(char*) (scanlineaddr++) = colour;
	}

//DEAD 	Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97

	return(clipvar);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim::GlassRectangleFill
//LastModified:	PD 02Apr96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Tue 2 April 1996
//
//Description	
//
//Inputs	
//
//Returns	clip result
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
UWord Graphic::GlassRectangleFill(SWord X,SWord Y,SWord W,SWord H)
{
	LogicalPtr	scradr,
				scanlineaddr;

	int		i,j;

	UWord	clipvar = 0;

	//Clip the rectangle to the screen

	if((Y+H) <= PhysicalMinY)
		clipvar |= 0x0003;

	if(Y >= PhysicalMinY+PhysicalHeight)
		clipvar |= 0x0003;
	
	if((X+W) <= PhysicalMinX)
		clipvar |= 0x000C;

	if(X >= PhysicalMinX+PhysicalWidth)
		clipvar |= 0x000C;

	if(clipvar)
		return(clipvar);

	if(Y < PhysicalMinY)
	{
		H -=	(PhysicalMinY-Y);
		Y = 	PhysicalMinY;
		clipvar |= 0x0001;
	}

	if((Y+H) > (PhysicalMinY+PhysicalHeight))
	{
		H -=	((Y+H)-(PhysicalMinY+PhysicalHeight));
		clipvar |= 0x0002;
	}

	if(X < PhysicalMinX)
	{
		W -= (PhysicalMinX-X);
		X = 	PhysicalMinX;
		clipvar |= 0x0004;
	}

	if((X+W) > (PhysicalMinX+PhysicalWidth))
	{
		W -= ((X+W)-(PhysicalMinX+PhysicalWidth));
		clipvar |= 0x0008;
	}	

	//Calculate the screen address of the top left corner of the rectangle

	scradr = logicalscreenptr +
			 BytesPerScanLine * Y +
			 BytesPerPixel * X;

	UByte	rngmin,rngmax,val;

//DEAD 	Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97

	rngmin = glasscolour;
	rngmax = glasscolour + range;

	for(i=H;i>0;i--)
	{
		scanlineaddr = scradr;

		for (j=W;j>0;j--)
		{
			val = *(UByte *)scanlineaddr;

			if (val>= rngmin && val<rngmax)						//RDH 14Aug96
			{
				val = val - glasscolour + colour;
				*(UByte *) (scanlineaddr++) = val;
			}
			else
				scanlineaddr++;
		}
		scradr += BytesPerScanLine;
	}

//DEAD 	Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97

	return(clipvar);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AilRectangleFill
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
UWord Graphic::AilRectangleFill(SWord X,SWord Y,SWord W,SWord H)
{
	LogicalPtr	scradr,
				scanlineaddr;

	int		i,j;

	UWord	clipvar = 0;

	//Clip the rectangle to the screen

	if((Y+H) <= PhysicalMinY)
		clipvar |= 0x0003;

	if(Y >= PhysicalMinY+PhysicalHeight)
		clipvar |= 0x0003;
	
	if((X+W) <= PhysicalMinX)
		clipvar |= 0x000C;

	if(X >= PhysicalMinX+PhysicalWidth)
		clipvar |= 0x000C;

	if(clipvar)
		return(clipvar);

	if(Y < PhysicalMinY)
	{
		H -=	(PhysicalMinY-Y);
		Y = 	PhysicalMinY;
		clipvar |= 0x0001;
	}

	if((Y+H) > (PhysicalMinY+PhysicalHeight))
	{
		H -=	((Y+H)-(PhysicalMinY+PhysicalHeight));
		clipvar |= 0x0002;
	}

	if(X < PhysicalMinX)
	{
		W -= (PhysicalMinX-X);
		X = 	PhysicalMinX;
		clipvar |= 0x0004;
	}

	if((X+W) > (PhysicalMinX+PhysicalWidth))
	{
		W -= ((X+W)-(PhysicalMinX+PhysicalWidth));
		clipvar |= 0x0008;
	}	

	//Calculate the screen address of the top left corner of the rectangle

	scradr = logicalscreenptr +
			 BytesPerScanLine * Y;

	VERTEX	lv,rv;

//DEAD 	Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97

	lv.sx.i = X; rv.sx.i = X + W -1;

	for(i=H;i>0;i--)
	{
// Bug found in this function - 11 Jul 96
//		ASM_SmokedGlassLine((UByte *)scradr, lv, rv);
		scradr += BytesPerScanLine;
	}

//DEAD 	Master()->UnLockBackScreen (LOWLOCK);					//AMM 02May97

	return(clipvar);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim::PlainPolygonFill
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
void Graphic::PlainPolygonFill()
{

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Graphic::TranslateColour
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
ULong Graphic::TranslateColour(Colour C)
{
	return(C);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Graphic::PlotPixel
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
Colour Graphic::PlotPixel(SWord X, SWord Y,Colour colour)
{
	SWord		MinX,MaxX,MinY,MaxY;
	Colour		ret_val;
	LogicalPtr	screenaddr;
	SLong		yoffset,xoffset;

	MinX = PhysicalMinX;
	MaxX = MinX + PhysicalWidth;//-1							//JIM 09Apr96

	MinY = PhysicalMinY;
	MaxY = MinY + PhysicalHeight;//-1							//JIM 09Apr96

	if(X>=MinX && X<MaxX && Y>=MinY && Y<MaxY)				//PD 28Jul97
	{
//DEAD 		Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97

		yoffset = BytesPerScanLine * Y;
		xoffset = BytesPerPixel * X;
		screenaddr = logicalscreenptr + xoffset + yoffset;

		if (BytesPerPixel<2)
		{
			ret_val = (Colour)(*screenaddr);
			*screenaddr = colour;
		}
		else
		if (BytesPerPixel==2)
		{
			UWord t=*(UWord*)screenaddr;
			ret_val=(Colour)((t&0xff00)>>8);
			t=(t&0xffff00ff)+(colour<<8);
			*(UWord*)screenaddr=t;
		}
		else
		{
			ULong t=*(ULong*)screenaddr;
			ret_val=(Colour)((t&0xff00)>>8);
			t=(t&0xffff00ff)+(colour<<8);
			*(ULong*)screenaddr=t;
		}

//DEAD 		Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
	}

	return(ret_val);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Graphic::PlotPixel
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
Colour Graphic::PlotPixel(SWord X, SWord Y)
{
	SWord		MinX,MaxX,MinY,MaxY;
	Colour		ret_val;
	LogicalPtr	screenaddr;
	SLong		yoffset,xoffset;

	MinX = PhysicalMinX;
	MaxX = MinX + PhysicalWidth;//-1;							//PD 28Jul97

	MinY = PhysicalMinY;
	MaxY = MinY + PhysicalHeight;//-1;							//PD 28Jul97

	if(X>=MinX && X<MaxX && Y>=MinY && Y<MaxY)					//PD 07Nov95
	{
//DEAD 		Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97

		yoffset = BytesPerScanLine * Y;
		xoffset = BytesPerPixel * X;
		screenaddr = logicalscreenptr + xoffset + yoffset;
		if (BytesPerPixel<2)
		{
			ret_val = (Colour)(*screenaddr);
			*screenaddr = colour;
		}
		else
		if (BytesPerPixel==2)
		{
			UWord t=*(UWord*)screenaddr;
			ret_val=(Colour)((t&0xff00)>>8);
			t=(t&0xffff00ff)+(colour<<8);
			*(UWord*)screenaddr=t;
		}
		else
		{
			ULong t=*(ULong*)screenaddr;
			ret_val=(Colour)((t&0xff00)>>8);
			t=(t&0xffff00ff)+(colour<<8);
			*(ULong*)screenaddr=t;
		}

//DEAD 		Master()->UnLockBackScreen (LOWLOCK);				//AMM 02May97
	}

	return(ret_val);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Graphic::PlotPixelNoClip
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 12 Jul 1995
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
void	Graphic::PlotPixelNoClip(short X, short Y, short colour)
{
	register	long	scradr;
	
//DEAD 	Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97

	scradr = ((long )BytesPerScanLine * Y) + ((long )BytesPerPixel * X) + ((long )logicalscreenptr);
	if (BytesPerPixel<2)
		*(char *)scradr = colour;
	else
	if (BytesPerPixel==2)
	{
		UWord t= *(UWord *)scradr;
		t=(t&0x00ff)+colour<<8;
		*(UWord *)scradr=t;
	}
	else
	{
		ULong t= *(ULong *)scradr;
		t=(t&0x00ff00ff)+colour<<8;
		*(ULong *)scradr=t;
	}

//DEAD 	Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Graphic::PlotPixelNoClip
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 12 Jul 1995
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
void	Graphic::PlotPixelNoClip(short X, short Y)
{
	register	long	scradr;
	
//DEAD 	Master()->LockBackScreen (TRUE,LOWLOCK);			//AMM 02May97

	scradr = ((long )BytesPerScanLine * Y) + ((long )BytesPerPixel * X) + ((long )logicalscreenptr);
	if (BytesPerPixel<2)
		*(char *)scradr = colour;
	else
	if (BytesPerPixel==2)
	{
#ifdef __WATCOMC__
		INT3();
#endif
#ifdef __MSVC__
		INT3;
#endif
		UWord t= *(UWord *)scradr;
		t=(t&0x00ff)+colour<<8;
		*(UWord *)scradr=t;
	}
	else
	{
		ULong t= *(ULong *)scradr;
		t=(t&0x00ff00ff)+colour<<8;
		*(ULong *)scradr=t;
	}

//DEAD 	Master()->UnLockBackScreen (LOWLOCK);			//AMM 02May97
}

//DeadCode JIM 08Apr97 Moved to LBM.CPP
//DeadCode JIM 08Apr97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 08Apr97 //Procedure	Graphic::ShowPic
//DeadCode JIM 08Apr97 //------------------------------------------------------------------------------
//DeadCode JIM 08Apr97 //Author		Paul.   
//DeadCode JIM 08Apr97 //Date			Thu 6 Jul 1995
//DeadCode JIM 08Apr97 //Modified		DAW 22Jan96
//DeadCode JIM 08Apr97 //
//DeadCode JIM 08Apr97 //Description	Made it more cunning by use of a new SearchIFFHunk routine
//DeadCode JIM 08Apr97 //
//DeadCode JIM 08Apr97 //Inputs		mem pointer to lbm image
//DeadCode JIM 08Apr97 //
//DeadCode JIM 08Apr97 //Returns	
//DeadCode JIM 08Apr97 //
//DeadCode JIM 08Apr97 //Externals
//DeadCode JIM 08Apr97 //------------------------------------------------------------------------------
//DeadCode JIM 08Apr97 //------------------------------------------------------------------------------
//DeadCode JIM 08Apr97 void Graphic::ShowPic(UByte *buffer)
//DeadCode JIM 08Apr97 {
//DeadCode JIM 08Apr97 	UByte* start=buffer;
//DeadCode JIM 08Apr97 	UByte	*tmp;
//DeadCode JIM 08Apr97 	SWord	picwidth,picheight,picy,picx,x,y;
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 	tmp = SearchIFFHunk((UByte *)"BMHD",buffer);		//Process PBM header
//DeadCode JIM 08Apr97 	if (tmp)
//DeadCode JIM 08Apr97 	{
//DeadCode JIM 08Apr97 		tmp = ReadWord(tmp,picwidth);
//DeadCode JIM 08Apr97 		tmp = ReadWord(tmp,picheight);
//DeadCode JIM 08Apr97 		tmp = ReadWord(tmp,picx);
//DeadCode JIM 08Apr97 		tmp = ReadWord(tmp,picy);
//DeadCode JIM 08Apr97 	}
//DeadCode JIM 08Apr97 		x = picx;				//Only display the part of the image contained within
//DeadCode JIM 08Apr97 		y = picy;				//the window defined by the screen structure
//DeadCode JIM 08Apr97 		picheight+=y;
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 	if (PhysicalMinY<master->ifflinenum)
//DeadCode JIM 08Apr97 	{
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 	tmp = SearchIFFHunk((UByte *)"CMAP",buffer);		//Process CMAP hunk - palette
//DeadCode JIM 08Apr97 	if (tmp)
//DeadCode JIM 08Apr97 		RegisterPalette(tmp,0x300);		//Signal to update palette on next screen swap
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 	tmp = SearchIFFHunk((UByte *)"BODY",buffer);		//Process BODY hunk
//DeadCode JIM 08Apr97 	}
//DeadCode JIM 08Apr97 	else
//DeadCode JIM 08Apr97 	{
//DeadCode JIM 08Apr97 		tmp = start+master->iffoffset;
//DeadCode JIM 08Apr97 		y = master->ifflinenum;
//DeadCode JIM 08Apr97 	}
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 	if (PhysicalMinY>picheight)	return();
//DeadCode JIM 08Apr97 	if (PhysicalMinX>picwidth)	return();
//DeadCode JIM 08Apr97 	if (PhysicalMaxY<picy)		return();
//DeadCode JIM 08Apr97 	if (PhysicalMaxX<picx)		return();
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 	if (tmp)
//DeadCode JIM 08Apr97 	{
//DeadCode JIM 08Apr97 		while(picheight>y && PhysicalMinY>y)
//DeadCode JIM 08Apr97 		{
//DeadCode JIM 08Apr97 			tmp = SkipRow(tmp,picwidth);
//DeadCode JIM 08Apr97 			y++;
//DeadCode JIM 08Apr97 		}
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 		if (PhysicalMinY>0 && PhysicalMinY<master->ifflinenum)
//DeadCode JIM 08Apr97 		{
//DeadCode JIM 08Apr97 			master->ifflinenum=PhysicalMinY;
//DeadCode JIM 08Apr97 			master->iffoffset=tmp-start;
//DeadCode JIM 08Apr97 		}
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 		int maxy=picheight;
//DeadCode JIM 08Apr97 		if (PhysicalMinY+PhysicalHeight<maxy)
//DeadCode JIM 08Apr97 			maxy=PhysicalMinY+PhysicalHeight;
//DeadCode JIM 08Apr97 		const	int	LINESPERMOUSE	=	50;
//DeadCode JIM 08Apr97 		int	yblock=((maxy-y)%LINESPERMOUSE)+y;
//DeadCode JIM 08Apr97 		while(yblock>y)
//DeadCode JIM 08Apr97 			tmp = UnpackRow(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DeadCode JIM 08Apr97 		while (maxy>yblock)
//DeadCode JIM 08Apr97 		{
//DeadCode JIM 08Apr97 			_Mouse.Move();
//DeadCode JIM 08Apr97 			yblock+=LINESPERMOUSE;
//DeadCode JIM 08Apr97 			while(yblock>y)
//DeadCode JIM 08Apr97 				tmp = UnpackRow(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DeadCode JIM 08Apr97 		}
//DeadCode JIM 08Apr97 	}
//DeadCode JIM 08Apr97 }

//DeadCode ARM 27Jun96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode ARM 27Jun96 //Procedure		Graphic::DoSmack(smk)
//DeadCode ARM 27Jun96 //Author		Dave Whiteside
//DeadCode ARM 27Jun96 //Date			Wed 31 Jan 1996
//DeadCode ARM 27Jun96 //
//DeadCode ARM 27Jun96 //Description	Play a frame of smack if needed
//DeadCode ARM 27Jun96 //
//DeadCode ARM 27Jun96 //Inputs		smacker to play
//DeadCode ARM 27Jun96 //
//DeadCode ARM 27Jun96 //Returns		current frame number
//DeadCode ARM 27Jun96 //
//DeadCode ARM 27Jun96 //------------------------------------------------------------------------------
//DeadCode ARM 27Jun96 UWord Graphic::DoSmack(Smack *smk, UWord hsmk)
//DeadCode ARM 27Jun96 {
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	LogicalPtr	scrnpos=logicalscreenptr;
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	if (hsmk)
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	{
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		scrnpos+=(BytesPerScanLine*((PhysicalHeight - hsmk)/2));
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		CopyP2L(0,((PhysicalHeight - hsmk)/2),PhysicalWidth*BytesPerPixel,hsmk);
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	}
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	else
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		CopyP2L(0,0,PhysicalWidth*BytesPerPixel,PhysicalHeight);
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	if (smk->FrameNum>0)				//only if not the 1st frame
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	{
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		if (SmackWait(smk)==0)			//should I wait
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		{
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 			SmackToBuffer(smk,0,0,BytesPerScanLine,PhysicalHeight,scrnpos,0);
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 			SmackDoFrame(smk);
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 			SmackNextFrame(smk);
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		}
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	}
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	else								//1st frame smack it anyway
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	{
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		SmackToBuffer(smk,0,0,BytesPerScanLine,PhysicalHeight,scrnpos,0);
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		SmackDoFrame(smk);
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 		SmackNextFrame(smk);
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	}
//DeadCode ARM 27Jun96 //TempCode ARM 05Jun96 	return(smk->FrameNum);
//DeadCode ARM 27Jun96 
//DeadCode ARM 27Jun96 	return (FALSE);
//DeadCode ARM 27Jun96 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim.PrintMonoBMP
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 8 Aug 1995
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
short Graphic::PrintMonoBMP(CharTableEntryPtr)
{
	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GrafPrim.PrintMonoRUN
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 8 Aug 1995
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
short Graphic::PrintMonoRUN(CharTableEntryPtr)
{
	return(0);
}

//Old_Code PD 19Nov97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Old_Code PD 19Nov97 //Procedure	GrafPrim.PrintShade
//Old_Code PD 19Nov97 //------------------------------------------------------------------------------
//Old_Code PD 19Nov97 //Author		Paul.   
//Old_Code PD 19Nov97 //Date		Tue 8 Aug 1995
//Old_Code PD 19Nov97 //Modified	
//Old_Code PD 19Nov97 //
//Old_Code PD 19Nov97 //Description	
//Old_Code PD 19Nov97 //
//Old_Code PD 19Nov97 //Inputs	
//Old_Code PD 19Nov97 //
//Old_Code PD 19Nov97 //Returns	
//Old_Code PD 19Nov97 //
//Old_Code PD 19Nov97 //Externals
//Old_Code PD 19Nov97 //------------------------------------------------------------------------------
//Old_Code PD 19Nov97 //------------------------------------------------------------------------------
//Old_Code PD 19Nov97 short Graphic::PrintShade(CharTableEntryPtr cte)
//Old_Code PD 19Nov97 {
//Old_Code PD 19Nov97 	SWord	sx,sy;					//Character start x and y coordinates
//Old_Code PD 19Nov97 	SWord	width,height;			//Width and height of the packed data
//Old_Code PD 19Nov97 	UByte	*src;
//Old_Code PD 19Nov97 
//Old_Code PD 19Nov97 	sx = CharX;
//Old_Code PD 19Nov97 	sy = CharY + cte->YShift;
//Old_Code PD 19Nov97 
//Old_Code PD 19Nov97 	width = cte->Width;
//Old_Code PD 19Nov97 	height = cte->Height+sy;
//Old_Code PD 19Nov97 
//Old_Code PD 19Nov97 	src = (UByte *) cte->pixeldata;								//DAW 29Nov95
//Old_Code PD 19Nov97 	if (height>(PhysicalMaxY))									//RDH 06Nov96
//Old_Code PD 19Nov97 	{
//Old_Code PD 19Nov97 		while(sy<PhysicalMinY)
//Old_Code PD 19Nov97 		{
//Old_Code PD 19Nov97 			src = Graphic::SkipRow(src,width);
//Old_Code PD 19Nov97 			sy++;
//Old_Code PD 19Nov97 		}
//Old_Code PD 19Nov97 		while(sy<=(PhysicalMaxY))								//RDH 06Nov96
//Old_Code PD 19Nov97 			src = Graphic::UnpackShadeRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//Old_Code PD 19Nov97 	}
//Old_Code PD 19Nov97 	else
//Old_Code PD 19Nov97 	{
//Old_Code PD 19Nov97 		while(sy<PhysicalMinY)
//Old_Code PD 19Nov97 		{
//Old_Code PD 19Nov97 			src = Graphic::SkipRow(src,width);
//Old_Code PD 19Nov97 			sy++;
//Old_Code PD 19Nov97 		}
//Old_Code PD 19Nov97 		while(sy<height)
//Old_Code PD 19Nov97 			src = Graphic::UnpackShadeRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//Old_Code PD 19Nov97 	}
//Old_Code PD 19Nov97 	return(0);
//Old_Code PD 19Nov97 }


//DeadCode JIM 08Apr97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 08Apr97 //Procedure	GrafPrim.PrintColour
//DeadCode JIM 08Apr97 //------------------------------------------------------------------------------
//DeadCode JIM 08Apr97 //Author		Paul.   
//DeadCode JIM 08Apr97 //Date		Tue 8 Aug 1995
//DeadCode JIM 08Apr97 //Modified	
//DeadCode JIM 08Apr97 //
//DeadCode JIM 08Apr97 //Description	
//DeadCode JIM 08Apr97 //
//DeadCode JIM 08Apr97 //Inputs	
//DeadCode JIM 08Apr97 //
//DeadCode JIM 08Apr97 //Returns	
//DeadCode JIM 08Apr97 //
//DeadCode JIM 08Apr97 //Externals
//DeadCode JIM 08Apr97 //------------------------------------------------------------------------------
//DeadCode JIM 08Apr97 //------------------------------------------------------------------------------
//DeadCode JIM 08Apr97 short Graphic::PrintColour(CharTableEntryPtr cte)
//DeadCode JIM 08Apr97 {
//DeadCode JIM 08Apr97 	SWord	sx,sy;		//Character start x and y coordinates
//DeadCode JIM 08Apr97 	SWord	width,height;	//Width and height of the packed data
//DeadCode JIM 08Apr97 	UByte	*src;
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 	sx = CharX;
//DeadCode JIM 08Apr97 	sy = CharY + cte->YShift;
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 	width = cte->Width;
//DeadCode JIM 08Apr97 	height = cte->Height+sy;
//DeadCode JIM 08Apr97 
//DeadCode JIM 08Apr97 	src = (UByte *) cte->pixeldata;								//DAW 29Nov95
//DeadCode JIM 08Apr97 	if (height>(PhysicalMaxY))
//DeadCode JIM 08Apr97 	{
//DeadCode JIM 08Apr97 		while(sy<PhysicalMinY)
//DeadCode JIM 08Apr97 		{
//DeadCode JIM 08Apr97 			src = Graphic::SkipRow(src,width);
//DeadCode JIM 08Apr97 			sy++;
//DeadCode JIM 08Apr97 		}
//DeadCode JIM 08Apr97 		while(sy<=(PhysicalMaxY))
//DeadCode JIM 08Apr97 			src = Graphic::UnpackRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DeadCode JIM 08Apr97 	}
//DeadCode JIM 08Apr97 	else
//DeadCode JIM 08Apr97 	{
//DeadCode JIM 08Apr97 		while(sy<PhysicalMinY)
//DeadCode JIM 08Apr97 		{
//DeadCode JIM 08Apr97 			src = Graphic::SkipRow(src,width);
//DeadCode JIM 08Apr97 			sy++;
//DeadCode JIM 08Apr97 		}
//DeadCode JIM 08Apr97 		while(sy<height)
//DeadCode JIM 08Apr97 			src = Graphic::UnpackRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DeadCode JIM 08Apr97 	}
//DeadCode JIM 08Apr97 	return(0);
//DeadCode JIM 08Apr97 }
//DeadCode JIM 08Apr97 
//DeadCode JIM 12Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 12Dec95 //Procedure		GetRealSxy
//DeadCode JIM 12Dec95 //Author		Paul.   
//DeadCode JIM 12Dec95 //Date			Thu 26 Oct 1995
//DeadCode JIM 12Dec95 //
//DeadCode JIM 12Dec95 //Description	
//DeadCode JIM 12Dec95 //
//DeadCode JIM 12Dec95 //Inputs		
//DeadCode JIM 12Dec95 //
//DeadCode JIM 12Dec95 //Returns	
//DeadCode JIM 12Dec95 //
//DeadCode JIM 12Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 12Dec95 void Graphic::GetRealSxy(SLong &screenx, SLong &screeny)
//DeadCode JIM 12Dec95 {
//DeadCode JIM 12Dec95 	screenx-=screenx%XRESFACTOR;
//DeadCode JIM 12Dec95 	screeny-=screeny%YRESFACTOR;
//DeadCode JIM 12Dec95 }

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
HoriLineRtnPtr Graphic::GetScanLineAddr(SCANLINETYPE type)
{
	return(ASM_HoriLineAddr(type));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGrey3DType
//Author		Paul.   
//Date			Sun 7 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::SetGrey3DType(GREY3DTYPE &grey3dtype)
{
//	grey3dtype=ASM_SetGrey3D(grey3dtype);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFadeData
//Author		Paul.   
//Date			Mon 24 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::SetFadeData(SLong ftdt)
{
//	ASM_SetFadeData(ftdt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFaded3DType
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
void Graphic::SetFaded3DType(GREY3DTYPE &grey3dtype)
{
//	grey3dtype=ASM_SetFaded3D(grey3dtype);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		cpolyhoriline
//Author		Paul.   
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//Old_Code PD 03Jan96 void Graphic::cpolyhoriline(UByte *scradr, VERTEX &left, VERTEX &right)
//Old_Code PD 03Jan96 {
//Old_Code PD 03Jan96 	SWord	length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	length = (right.sx>>16)-(left.sx>>16);
//Old_Code PD 03Jan96 	length++;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	if(length>0)
//Old_Code PD 03Jan96 	{
//Old_Code PD 03Jan96 		scradr += (left.sx>>16);
//Old_Code PD 03Jan96 		while(length--)	*scradr++=colour;
//Old_Code PD 03Jan96 	}
//Old_Code PD 03Jan96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		gpolyhoriline
//Author		Paul.   
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//Old_Code PD 03Jan96 void Graphic::gpolyhoriline(UByte *scradr, VERTEX &left, VERTEX &right)
//Old_Code PD 03Jan96 {
//Old_Code PD 03Jan96 	SWord	length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	dintens,intens;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	length = (right.sx>>16)-(left.sx>>16);
//Old_Code PD 03Jan96 	length++;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	if(length>0)
//Old_Code PD 03Jan96 	{
//Old_Code PD 03Jan96 		intens = left.intensity;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		dintens = (right.intensity-intens)/length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		scradr += (left.sx>>16);
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		while(length--)
//Old_Code PD 03Jan96 		{
//Old_Code PD 03Jan96 			*scradr++=shadetable[makecolindex(intens)];
//Old_Code PD 03Jan96 			intens += dintens;
//Old_Code PD 03Jan96 		}
//Old_Code PD 03Jan96 	}
//Old_Code PD 03Jan96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ipolyhoriline
//Author		Paul.   
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//Old_Code PD 03Jan96 void Graphic::ipolyhoriline(UByte *scradr, VERTEX &left, VERTEX &right)
//Old_Code PD 03Jan96 {
//Old_Code PD 03Jan96 	ASM_ImageHoriLine4(scradr,left,right);
//Old_Code PD 03Jan96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		bipolyhoriline
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
//Old_Code PD 03Jan96 void Graphic::bipolyhoriline(UByte *scradr, VERTEX &left, VERTEX &right)
//Old_Code PD 03Jan96 {
//Old_Code PD 03Jan96 	UByte	*imagesrc;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SWord	length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	ix,iy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	dix,diy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	length = (right.sx>>16)-(left.sx>>16);
//Old_Code PD 03Jan96 	length++;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	if(length>0)
//Old_Code PD 03Jan96 	{
//Old_Code PD 03Jan96 		ix = left.ix;
//Old_Code PD 03Jan96 		iy = left.iy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		dix = (right.ix-ix)/length;
//Old_Code PD 03Jan96 		diy = (right.iy-iy)/length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		scradr += (left.sx>>16);
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		while(length--)
//Old_Code PD 03Jan96 		{
//Old_Code PD 03Jan96 			imagesrc = makemapindex(ix,iy);
//Old_Code PD 03Jan96 			*scradr++=(colour&0xF0) + (0x0F & *imagesrc);
//Old_Code PD 03Jan96 			ix+=dix;
//Old_Code PD 03Jan96 			iy+=diy;
//Old_Code PD 03Jan96 		}
//Old_Code PD 03Jan96 	}
//Old_Code PD 03Jan96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ipolyhorilinem
//Author		Paul.   
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//Old_Code PD 03Jan96 void Graphic::ipolyhorilinem(UByte *scradr, VERTEX &left, VERTEX &right)
//Old_Code PD 03Jan96 {
//Old_Code PD 03Jan96 	UByte	*imagesrc;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SWord	counter,length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	ix,iy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	dix,diy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	length = (right.sx>>16)-(left.sx>>16);
//Old_Code PD 03Jan96 	length++;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	if(length>0)
//Old_Code PD 03Jan96 	{
//Old_Code PD 03Jan96 		ix = left.ix;
//Old_Code PD 03Jan96 		iy = left.iy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		dix = (right.ix-ix)/length;
//Old_Code PD 03Jan96 		diy = (right.iy-iy)/length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		scradr += (left.sx>>16);
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		for(counter=0;counter<length;counter++)
//Old_Code PD 03Jan96 		{
//Old_Code PD 03Jan96 			if(*(imagesrc = makemapindex(ix,iy))!=0x0FE)
//Old_Code PD 03Jan96 			{
//Old_Code PD 03Jan96 				*scradr++=*imagesrc;
//Old_Code PD 03Jan96 			}
//Old_Code PD 03Jan96 			ix+=dix;
//Old_Code PD 03Jan96 			iy+=diy;
//Old_Code PD 03Jan96 		}
//Old_Code PD 03Jan96 	}
//Old_Code PD 03Jan96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		sipolyhoriline
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
//Old_Code PD 03Jan96 void Graphic::sipolyhoriline(UByte *scradr, VERTEX &left, VERTEX &right)
//Old_Code PD 03Jan96 {
//Old_Code PD 03Jan96 	SWord	intensity;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	UByte	*imagesrc;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SWord	length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	ix,iy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	dix,diy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	dintens,intens;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	length = (right.sx>>16)-(left.sx>>16);
//Old_Code PD 03Jan96 	length++;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	if(length>0)
//Old_Code PD 03Jan96 	{
//Old_Code PD 03Jan96 		ix = left.ix;
//Old_Code PD 03Jan96 		iy = left.iy;
//Old_Code PD 03Jan96 		intens = left.intensity;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		dix = (right.ix-ix)/length;
//Old_Code PD 03Jan96 		diy = (right.iy-iy)/length;
//Old_Code PD 03Jan96 		dintens = (right.intensity-intens)/length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		scradr += (left.sx>>16);
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		while(length--)
//Old_Code PD 03Jan96 		{
//Old_Code PD 03Jan96 			imagesrc = makemapindex(ix,iy);
//Old_Code PD 03Jan96 			intensity= ((*imagesrc)&0x0F);
//Old_Code PD 03Jan96 			intensity= intensityindex[intensity][makecolindex(intens)];
//Old_Code PD 03Jan96 			*scradr++= ((colour&0xF0) + (0x0F & *imagesrc) + intensity); 
//Old_Code PD 03Jan96 			ix+=dix;
//Old_Code PD 03Jan96 			iy+=diy;
//Old_Code PD 03Jan96 			intens += dintens;
//Old_Code PD 03Jan96 		}
//Old_Code PD 03Jan96 	}
//Old_Code PD 03Jan96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		shpolyhoriline
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
//Old_Code PD 03Jan96 void Graphic::shpolyhoriline(UByte *scradr, VERTEX &left, VERTEX &right)
//Old_Code PD 03Jan96 {
//Old_Code PD 03Jan96 	SWord	intensity;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	UByte	*imagesrc;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SWord	length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	ix,iy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	dix,diy;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	SLong	dintens,intens;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	length = (right.sx>>16)-(left.sx>>16);
//Old_Code PD 03Jan96 	length++;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 	if(length>0)
//Old_Code PD 03Jan96 	{
//Old_Code PD 03Jan96 		ix = left.ix;
//Old_Code PD 03Jan96 		iy = left.iy;
//Old_Code PD 03Jan96 		intens = left.intensity;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		dix = (right.ix-ix)/length;
//Old_Code PD 03Jan96 		diy = (right.iy-iy)/length;
//Old_Code PD 03Jan96 		dintens = (right.intensity-intens)/length;
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		scradr += (left.sx>>16);
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 		while(length--)
//Old_Code PD 03Jan96 		{
//Old_Code PD 03Jan96 			imagesrc = makemapindex(ix,iy);
//Old_Code PD 03Jan96 			intensity= ((*imagesrc)&0x0F);
//Old_Code PD 03Jan96 			intensity= intensityindex[intensity][makecolindex(intens)];
//Old_Code PD 03Jan96 			*scradr++= (*imagesrc + intensity); 
//Old_Code PD 03Jan96 			ix+=dix;
//Old_Code PD 03Jan96 			iy+=diy;
//Old_Code PD 03Jan96 			intens += dintens;
//Old_Code PD 03Jan96 		}
//Old_Code PD 03Jan96 	}
//Old_Code PD 03Jan96 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	SWord	intensity;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	UWordP	destptr = (UWord *)scradr;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	UByte	*imagesrc;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	SWord	length;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	SLong	ix,iy;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	SLong	dix,diy;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	SLong	dintens,intens;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	length = (right.sx>>16)-(left.sx>>16);
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	length++;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	length>>=1;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	if(length>0)
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	{
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		ix = left.ix;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		iy = left.iy;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		intens = left.intensity;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		dix = (right.ix-ix)/length;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		diy = (right.iy-iy)/length;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		dintens = (right.intensity-intens)/length;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		destptr += (left.sx>>17);
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		UWord value;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		while(length--)
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		{
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 			imagesrc = makemapindex(ix,iy);
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 			intensity= ((*imagesrc)&0x0F);
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 			intensity= intensityindex[intensity][makecolindex(intens)];
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 			value = *(imagesrc + intensity);
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 			value += (value<<8);
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 			*destptr++= value;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 			ix+=dix;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 			iy+=diy;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 			intens += dintens;
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 		}
//Old_Code PD 03Jan96 //TempCode PD 18Dec95 	}
//Old_Code PD 03Jan96 }

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
void Graphic::MakeIntensityData()
{
	int	i,j;

	SLong	range,base,delta;

	for(i=0;i<16;i++)
	{
		range = (16-i)<<8;

		base = 0;

		delta = range/32;

		for(j=0;j<32;j++)
		{
			intensityindex[i][j]=base>>8;
			base += delta;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillIntensityTable
//Author		Martin Alderton
//Date			Fri 10 Nov 1995
//
//Description Scans the current palette and builds up a table of colour
//				intensities for each entry in the palette.	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void Graphic::FillIntensityTable(UByte MAPPING_BASE, UByte MAPPING_RANGE)
//{
//	Colour Mapped_Colour;
//	Colour IntensityTable[256];
//	int i;
//	UByte j=0;
//
//	for (i=0;i<256;i++)
//	{
//		
//		MapColourToBase(j,MAPPING_BASE,MAPPING_RANGE,Mapped_Colour);
//		IntensityTable[i] = Mapped_Colour;
//		j++;
//	}
//
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MapColourToBase
//Author		Martin Alderton
//Date			Fri 10 Nov 1995
//
//Description	
//
//Inputs	RGB triplet  3 values in the range 0-63;
//			MAPPING_BASE;
//			MAPPING_RANGE;	
//
//Returns	a colour mapped between mapping_base and (mapping_base + mapping_range)
//
//------------------------------------------------------------------------------
//Colour Graphic::MapColourToBase
//		(UByte j,UByte MAPPING_BASE,UByte MAPPING_RANGE, Colour Mapped_Colour)
//{
//	UWord Intensity,scale,temp;
//	
//	UByte red,green,blue;
// 	UByte *PAL_ptr =(UByte *)Palette;
//	
//	j=j*3;
//	PAL_ptr = PAL_ptr + (j*sizeof(UByte));
//  	red =(UByte)(PAL_ptr);
//	PAL_ptr++;
//  	green =(UByte)(PAL_ptr);
//	PAL_ptr++;
// 	blue =(UByte)(PAL_ptr);
//
//	Intensity = (red * green * blue)>>8;
//
//	temp = Intensity >>6;
//	
//	scale = temp * MAPPING_RANGE;
//
//	Mapped_Colour = (Colour)(MAPPING_BASE + (Colour)scale);
//
//	return(Mapped_Colour); 	
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CompZOutCode
//Author		Martin Alderton
//Date			Tue 21 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ZOutCode Graphic::CompZOutCode(SLong z,SLong ZMin)
{
	ZOutCode code;
	code.behind=code.all=0;										//RJS 13Jun97
																//RJS 13Jun97
	if (z<ZMin)													//RJS 13Jun97
	{															//RJS 13Jun97
		code.behind=1;											//RJS 13Jun97
		code.all +=code.behind;									//RJS 13Jun97
	}															//RJS 13Jun97
	return code;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		zclipline
//Author		Martin Alderton
//Date			Mon 20 Nov 1995
//
//Description	takes in two dopointstrucs works out where (if anywhere) they
//				cross the zclipping planes and adjusts the bodyx and bodyy
//				coordinates of each point as required. Hey Presto a line
//				clipped in the z plane ready to go to ClipLine function
//
//Inputs		2* dopointstruc
//
//Returns		2 * adjusted DoPointStruc	
//
//------------------------------------------------------------------------------
void Graphic::zclipline(DoPointStruc &start_vertex,DoPointStruc &end_vertex)
{
	Bool	accept, done;
//DeadCode RJS 25Feb97  	short done,accept;
//DeadCode RJS 25Feb97  	SWord z,x,y,x1,x0,y0,y1,z0,z1;
 	Float	z,x,y,x1,x0,y0,y1,z0,z1;
 	SLong	ZMin;												//RJS 25Feb97
 	ZOutCode outcode1, outcode2, outcodeOut;
 
 	x0 = start_vertex.bodyx.f;									//RJS 25Feb97
 	x1 = end_vertex.bodyx.f;									//RJS 25Feb97
 	y0 = start_vertex.bodyy.f;									//RJS 25Feb97
 	y1 = end_vertex.bodyy.f;									//RJS 25Feb97
 	z0 = start_vertex.bodyz.f;									//RJS 25Feb97
 	z1 = end_vertex.bodyz.f;									//RJS 25Feb97
 
   	ZMin = 100;													//RJS 25Jun97
 		 
 	done=FALSE;													//RJS 25Feb97
 	accept=FALSE;												//RJS 25Feb97
 	outcode1=CompZOutCode(z0,ZMin);
 	outcode2=CompZOutCode(z1,ZMin);
 	do
 	{
 		if (!outcode1.all && !outcode2.all)
 		{
 			done=TRUE;									//RJS 25Feb97
 			accept=TRUE;								//RJS 25Feb97
 		}
 		else if ((outcode1.all & outcode2.all) !=0)
 			{
 				done =TRUE;									//RJS 25Feb97
 			}
 		else
 		{
 			if(outcode1.all)									//RJS 13Jun97
 			{
 				outcodeOut=outcode1;
 				z=z0;
 				x=x0;
 				y=y0;
 			}
 			else
 			{
 				outcodeOut=outcode2;
 				z=z1;
 				x=x1;
 				y=y1;
 			}
 			if (outcodeOut.behind)
 			{
 				x= x0 + (((ZMin-z0)*(x1-x0))/(z1-z0));
 				y= y0 + (((ZMin-z0)*(y1-y0))/(z1-z0));
 				z=ZMin;
 			}
 			if (outcodeOut.all==outcode1.all)
 			{
 				z0=z;
 				x0=x;
 				y0=y;
 				outcode1=CompZOutCode(z,ZMin);
 			}
 			else
 			{
 				z1=z;
 				x1=x;
 				y1=y;
 				outcode2=CompZOutCode(z,ZMin);
 			}
 		}
 	}
 	while (!done);												//RJS 25Feb97
 
 	if (accept)													//RJS 25Feb97
 	{
 		start_vertex.bodyx.f = x0;
 		end_vertex.bodyx.f = x1;
 		start_vertex.bodyy.f = y0;
 		end_vertex.bodyy.f = y1;
 		start_vertex.bodyz.f = z0;
 		end_vertex.bodyz.f = z1;
 	}
 
//DeadCode RJS 25Feb97 //FIX ME!!!
//DeadCode RJS 25Feb97 	INT3();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillPalFxTable
//Author		Paul.   
//Date			Fri 5 Jan 1996
//
//Description	Uses the current palette to set up the colour tables
//				used for palette indirection in the 'grey' 3D horizontal
//				line draw routines.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::FillPalFxTable()
{
//DeadCode PD 02Apr96 	typedef	struct	rgb
//DeadCode PD 02Apr96 	{
//DeadCode PD 02Apr96 		UByte	r,g,b;
//DeadCode PD 02Apr96 	}
//DeadCode PD 02Apr96 	*rgbptr;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	int		j,k,l;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96  	ULongP	dest;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	UByteP	table;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	SLong	dest_red,dest_green,dest_blue;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	rgbptr	scanptr,palptr,resetptr;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	resetptr=(rgbptr )Palette;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	dest_red=(resetptr[GREY26].r)<<8;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	dest_green=(resetptr[GREY26].g)<<8;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	dest_blue=(resetptr[GREY26].b)<<8;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	dest = ASM_GetPalFxTableAddr();
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 	for(j=CLOUD20;j--;)
//DeadCode PD 02Apr96 	{
//DeadCode PD 02Apr96 		int	div_factor=j+1;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 		palptr=resetptr;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 		table=(UByteP )(*dest++);
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 		for(k=256;k--;)
//DeadCode PD 02Apr96 		{
//DeadCode PD 02Apr96 			SLong	this_red,this_green,this_blue;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			SLong	delta_red,delta_green,delta_blue;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			///////////////////////////////////////////
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			this_red=(palptr->r)<<8;
//DeadCode PD 02Apr96 			
//DeadCode PD 02Apr96 			this_green=(palptr->g)<<8;
//DeadCode PD 02Apr96 			
//DeadCode PD 02Apr96 			this_blue=(palptr->b)<<8;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			///////////////////////////////////////////
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			delta_red=(dest_red-this_red)/div_factor;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			delta_green=(dest_green-this_green)/div_factor;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			delta_blue=(dest_blue-this_blue)/div_factor;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			///////////////////////////////////////////
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			this_red=(this_red+delta_red+128)>>8;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			this_green=(this_green+delta_green+128)>>8;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			this_blue=(this_blue+delta_blue+128)>>8;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			///////////////////////////////////////////
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			//Now, find the palette entry closest to this value
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			UByte	selected=0;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			SLong	nearest_range=64*64*64;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			for(l=256,scanptr=resetptr;l--;)
//DeadCode PD 02Apr96 			{
//DeadCode PD 02Apr96 				SLong	scan_red,scan_green,scan_blue,scan_range;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 				scan_red=scanptr->r;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 				scan_green=scanptr->g;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 				scan_blue=scanptr->b;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 				scan_red-=this_red;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 				scan_blue-=this_blue;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 				scan_green-=this_green;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 				scan_range=	scan_red*scan_red+
//DeadCode PD 02Apr96 							scan_green*scan_green+
//DeadCode PD 02Apr96 							scan_blue*scan_blue;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 				if(scan_range<nearest_range)
//DeadCode PD 02Apr96 				{
//DeadCode PD 02Apr96 					nearest_range=scan_range;
//DeadCode PD 02Apr96 					selected=(UByte )(255-l);
//DeadCode PD 02Apr96 				}
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 				scanptr++;
//DeadCode PD 02Apr96 			}
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			*table++=selected;
//DeadCode PD 02Apr96 
//DeadCode PD 02Apr96 			palptr++;
//DeadCode PD 02Apr96 		}
//DeadCode PD 02Apr96 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TransparentBlob
//Author		Paul.   
//Date			Mon 28 Jul 1997
//
//Description	
//
//Inputs		clipInfo =  /|\
//						   |_|_| .... 0
//							___
//						   | | | .... 1
//						    \|/
//						   
//						   |-\  
//						   |--	 .... 2
//						   |-/
//
//						    /-| 
//							--|	 .... 3
//							\-|
//
//Returns	
//
//------------------------------------------------------------------------------

#define CIRCLE_POINTS()\
		FuzzyLine2(CentXLocal,CentYLocal,var_ax,-var_si,radius,intens);\
		FuzzyLine2(CentXLocal,CentYLocal,var_ax,var_si,radius,intens);\
		FuzzyLine2(CentXLocal,CentYLocal,var_si,-var_ax,radius,intens);\
		FuzzyLine2(CentXLocal,CentYLocal,var_si,var_ax,radius,intens);

void Graphic::TransparentBlob(	SWord clipInfo,
								SWord intens,
								SWord radius,
								SWord x,
								SWord y)
{
//DEAD 	Master()->LockBackScreen (TRUE);

	SWord	var_ax,var_si,var_dx,var_bp;

	SWord	CentXLocal,CentYLocal;

	if (intens > 255)
		intens = 255;

	CentXLocal = x;
	CentYLocal = y;

	var_si = 0;
	var_ax = var_dx = radius;

	var_dx = 3;
	var_dx -= var_ax<<1;

loopC:

	CIRCLE_POINTS();

	if (var_dx>=0)	goto Over;

	var_dx += 6;

	var_bp = var_si<<2;

	var_dx += var_bp;

	var_si++;

	if (var_si<var_ax)	goto loopC;

	if (var_si!=var_ax)	goto Out;
	
	CIRCLE_POINTS();

	goto Out;

Over:
	var_bp = var_si;

	var_bp -= var_ax;

	var_bp >>= 2;

	var_dx += var_bp;

	var_dx += 10;

	var_ax--;

	var_si++;

	if (var_si<var_ax) goto loopC;

	if (var_si!=var_ax)	goto Out;

	CIRCLE_POINTS();
Out:
//DEAD 	Master()->UnLockBackScreen();

	return;
}

#undef	CIRCLE_POINTS					//PD 13Nov97

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FuzzyLine
//Author		Paul.   
//Date			Mon 28 Jul 1997
//
//Description	Draws a horizontal line from (cx-dx,cy+dy) to
//				(cx+dx,cy+dy) transparent at endpoints but
//				of opacity cInt in the center
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::FuzzyLine(SWord cx,SWord cy,SWord dx,SWord dy,SWord rad,SWord cInt)
{
	SWord		MinX,MaxX,MinY,MaxY;

	MinY = PhysicalMinY;
	MaxY = MinY + PhysicalHeight;

	// Y-clipping

	if (cy+dy<MinY || cy+dy>=MaxY || dx==0)	return;

	MinX = PhysicalMinX;
	MaxX = MinX + PhysicalWidth;

	LogicalPtr	scradr;

	SLong		xoffset,yoffset;

	//use dx,dy & cInt to generate an intensity
	//value at either end of the line and at it's
	//center point.

	dx = (dx<0)?-dx:dx;

	//y first

	SWord	abs_dy = dy<0?-dy:dy;

	abs_dy <<= 8;

	abs_dy /= rad;

	abs_dy = 256 - abs_dy;

	//abs_dy == 256 when dy == +/- radius
	//abs_dy == 0   when dy == 0

	SWord	dInt,rInt,lInt;

	dInt = abs_dy/dx;

	rInt = 0;

	yoffset = BytesPerScanLine * (cy+dy);
	xoffset = BytesPerPixel * (cx-dx+1);

	scradr = logicalscreenptr + xoffset + yoffset;
	
	int	tmpx = cx-dx+1;

	int	cnt;

	UWord	*wscradr;

	switch (BytesPerPixel)
	{
		case 1:

		lInt = rInt;

		for (cnt=1;cnt<=dx;cnt++,tmpx++)
		{
			if (tmpx<MinX || tmpx>=MaxX)
				scradr++;
			else
				*scradr++ = GREY00 + (lInt>>4);

			rInt+=dInt;

			lInt = rInt;

			if (lInt>0xFF)	lInt=0xFF;
		}

		for (cnt=0;cnt<dx;cnt++,tmpx++)
		{
			if (tmpx<MinX || tmpx>=MaxX)
				scradr++;
			else
				*scradr++ = GREY00 + (lInt>>4);

			rInt-=dInt;

			lInt = rInt;

			if (lInt<0)	lInt=0;
		}
		break;

		case 2:

		rInt = 0xFF - rInt;

		dInt =- dInt;

		wscradr = (UWord*)scradr;

		lInt = rInt;

		for (cnt=1;cnt<=dx;cnt++,tmpx++)
		{
			if (tmpx<MinX || tmpx>=MaxX)
				wscradr++;
			else
			{
				UWord	srccol,newcol;

				ULong	tmp;

				srccol = *wscradr;

				tmp = srccol & 0x001F; tmp *= lInt; tmp >>= 8;

				newcol = (UWord)tmp;

				tmp = srccol & 0x07E0; tmp *= lInt; tmp >>= 8;

				newcol += (UWord)(tmp & 0x07E0);

				tmp = srccol & 0xF800; tmp *= lInt; tmp >>= 8;

				newcol += (UWord)(tmp & 0xF800);

				*wscradr++ = newcol;
			}

			rInt+=dInt;

			lInt = rInt;

			if (lInt<0)	lInt=0;
		}

		for (cnt=0;cnt<dx;cnt++,tmpx++)
		{
			if (tmpx<MinX || tmpx>=MaxX)
				wscradr++;
			else
			{
				UWord	srccol,newcol;
				
				ULong	tmp;

				srccol = *wscradr;

				tmp = srccol & 0x001F; tmp *= lInt; tmp >>= 8;

				newcol = (UWord)tmp;

				tmp = srccol & 0x07E0; tmp *= lInt; tmp >>= 8;

				newcol += (UWord)(tmp & 0x07E0);

				tmp = srccol & 0xF800; tmp *= lInt; tmp >>= 8;

				newcol += (UWord)(tmp & 0xF800);

				*wscradr++ = newcol;
			}

			rInt-=dInt;

			lInt = rInt;

			if (lInt>0xFF)	lInt=0xFF;
		}
		break;

		default:
		break;
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FuzzyLine2
//Author		Robert Slater
//Date			Thu 6 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Graphic::FuzzyLine2(SWord cx,SWord cy,SWord dx,SWord dy,SWord rad,SWord cInt)
{
	SWord		MinX,MaxX,MinY,MaxY;

	MinY = PhysicalMinY;
	MaxY = MinY + PhysicalHeight;

	// Y-clipping

	if (cy+dy<MinY || cy+dy>=MaxY || dx==0)	return;

	MinX = PhysicalMinX;
	MaxX = MinX + PhysicalWidth;

	LogicalPtr	scradr;

	SLong		xoffset,yoffset;

	//use dx,dy & cInt to generate an intensity
	//value at either end of the line and at it's
	//center point.

	dx = (dx<0)?-dx:dx;

	//y first

	SWord	abs_dy = dy<0?-dy:dy;

	abs_dy <<= 8;

	abs_dy /= rad;

	abs_dy = 256 - abs_dy;

	//abs_dy == 256 when dy == +/- radius
	//abs_dy == 0   when dy == 0

	SWord	dInt,rInt,lInt;
	SWord	BaseCol = 16;
	SWord	ColRange = cInt - BaseCol;

	dInt = abs_dy/dx;

	rInt = BaseCol;

	yoffset = BytesPerScanLine * (cy+dy);
	xoffset = BytesPerPixel * (cx-dx+1);

	scradr = logicalscreenptr + xoffset + yoffset;
	
	int	tmpx = cx-dx+1;

	int	cnt;

	UWord	*wscradr;

	switch (BytesPerPixel)
	{
		case 1:

		lInt = rInt;

		for (cnt=1;cnt<=dx;cnt++,tmpx++)
		{
			if (tmpx<MinX || tmpx>=MaxX)
				scradr++;
			else
				*scradr++ = lInt;

 			rInt = ((rInt*dx)+ColRange)/dx;

			lInt = rInt;

			if (lInt>cInt)	lInt=cInt;
		}

		for (cnt=0;cnt<dx;cnt++,tmpx++)
		{
			if (tmpx<MinX || tmpx>=MaxX)
				scradr++;
			else
				*scradr++ = lInt;

 			rInt = ((rInt*dx)-ColRange)/dx;

			lInt = rInt;

			if (lInt<BaseCol)	lInt=BaseCol;
		}
		break;

		case 2:

		rInt = 0xFF - rInt;

		dInt =- dInt;

		wscradr = (UWord*)scradr;

		lInt = rInt;

		for (cnt=1;cnt<=dx;cnt++,tmpx++)
		{
			if (tmpx<MinX || tmpx>=MaxX)
				wscradr++;
			else
			{
				UWord	srccol,newcol;

				ULong	tmp;

				srccol = *wscradr;

				tmp = srccol & 0x001F; tmp *= lInt; tmp >>= 8;

				newcol = (UWord)tmp;

				tmp = srccol & 0x07E0; tmp *= lInt; tmp >>= 8;

				newcol += (UWord)(tmp & 0x07E0);

				tmp = srccol & 0xF800; tmp *= lInt; tmp >>= 8;

				newcol += (UWord)(tmp & 0xF800);

				*wscradr++ = newcol;
			}

			rInt+=dInt;

			lInt = rInt;

			if (lInt<0)	lInt=0;
		}

		for (cnt=0;cnt<dx;cnt++,tmpx++)
		{
			if (tmpx<MinX || tmpx>=MaxX)
				wscradr++;
			else
			{
				UWord	srccol,newcol;
				
				ULong	tmp;

				srccol = *wscradr;

				tmp = srccol & 0x001F; tmp *= lInt; tmp >>= 8;

				newcol = (UWord)tmp;

				tmp = srccol & 0x07E0; tmp *= lInt; tmp >>= 8;

				newcol += (UWord)(tmp & 0x07E0);

				tmp = srccol & 0xF800; tmp *= lInt; tmp >>= 8;

				newcol += (UWord)(tmp & 0xF800);

				*wscradr++ = newcol;
			}

			rInt-=dInt;

			lInt = rInt;

			if (lInt>0xFF)	lInt=0xFF;
		}
		break;

		default:
		break;
	}

}






//DeadCode JIM 05Feb96 void	Graphic::LogMouseDrawSave(void* MouseShape,MouseSave* newpos)
//DeadCode JIM 05Feb96 {
//DeadCode JIM 05Feb96 	newpos->dataptr[0]=
//DeadCode JIM 05Feb96 		PlotPixel(newpos->XY.x,newpos->XY.y,(newpos->dataptr[1])++);
//DeadCode JIM 05Feb96 	newpos->WH.w=1;
//DeadCode JIM 05Feb96 	newpos->WH.h=1;
//DeadCode JIM 05Feb96 
//DeadCode JIM 05Feb96 
//DeadCode JIM 05Feb96 }
//DeadCode JIM 05Feb96 void	Graphic::LogMouseRestore(MouseSave* newpos)
//DeadCode JIM 05Feb96 {
//DeadCode JIM 05Feb96 	if (newpos->WH.w && newpos->WH.h)
//DeadCode JIM 05Feb96 		PlotPixel(newpos->XY.x,newpos->XY.y,(newpos->dataptr[0]));
//DeadCode JIM 05Feb96 	newpos->WH.w=0;
//DeadCode JIM 05Feb96 	newpos->WH.h=0;
//DeadCode JIM 05Feb96 }

//DeadCode PD 13Nov97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode PD 13Nov97 //Procedure		TransparentBlob
//DeadCode PD 13Nov97 //Author		Paul.   
//DeadCode PD 13Nov97 //Date			Mon 28 Jul 1997
//DeadCode PD 13Nov97 //
//DeadCode PD 13Nov97 //Description	
//DeadCode PD 13Nov97 //
//DeadCode PD 13Nov97 //Inputs		clipInfo =  /|\
//DeadCode PD 13Nov97 //						   |_|_| .... 0
//DeadCode PD 13Nov97 //							___
//DeadCode PD 13Nov97 //						   | | | .... 1
//DeadCode PD 13Nov97 //						    \|/
//DeadCode PD 13Nov97 //						   
//DeadCode PD 13Nov97 //						   |-\  
//DeadCode PD 13Nov97 //						   |--	 .... 2
//DeadCode PD 13Nov97 //						   |-/
//DeadCode PD 13Nov97 //
//DeadCode PD 13Nov97 //						    /-| 
//DeadCode PD 13Nov97 //							--|	 .... 3
//DeadCode PD 13Nov97 //							\-|
//DeadCode PD 13Nov97 //
//DeadCode PD 13Nov97 //Returns	
//DeadCode PD 13Nov97 //
//DeadCode PD 13Nov97 //------------------------------------------------------------------------------
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 #define CIRCLE_POINTS()\
//DeadCode PD 13Nov97 		FuzzyLine(CentXLocal,CentYLocal,var_ax,-var_si,radius,intens);\
//DeadCode PD 13Nov97 		FuzzyLine(CentXLocal,CentYLocal,var_ax,var_si,radius,intens);\
//DeadCode PD 13Nov97 		FuzzyLine(CentXLocal,CentYLocal,var_si,-var_ax,radius,intens);\
//DeadCode PD 13Nov97 		FuzzyLine(CentXLocal,CentYLocal,var_si,var_ax,radius,intens);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 //Old_Code PD 28Jul97 #define CIRCLE_POINTS()\
//DeadCode PD 13Nov97 //Old_Code PD 28Jul97 		PlotPixel(CentXLocal+var_ax,CentYLocal-var_si);\
//DeadCode PD 13Nov97 //Old_Code PD 28Jul97 		PlotPixel(CentXLocal-var_ax,CentYLocal-var_si);\
//DeadCode PD 13Nov97 //Old_Code PD 28Jul97 		PlotPixel(CentXLocal+var_ax,CentYLocal+var_si);\
//DeadCode PD 13Nov97 //Old_Code PD 28Jul97 		PlotPixel(CentXLocal-var_ax,CentYLocal+var_si);\
//DeadCode PD 13Nov97 //Old_Code PD 28Jul97 		PlotPixel(CentXLocal+var_si,CentYLocal+var_ax);\
//DeadCode PD 13Nov97 //Old_Code PD 28Jul97 		PlotPixel(CentXLocal-var_si,CentYLocal+var_ax);\
//DeadCode PD 13Nov97 //Old_Code PD 28Jul97 		PlotPixel(CentXLocal+var_si,CentYLocal-var_ax);\
//DeadCode PD 13Nov97 //Old_Code PD 28Jul97 		PlotPixel(CentXLocal-var_si,CentYLocal-var_ax);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 xvoid Graphic::TransparentBlob(	SWord clipInfo,
//DeadCode PD 13Nov97 								SWord intens,
//DeadCode PD 13Nov97 								SWord radius,
//DeadCode PD 13Nov97 								SWord x,
//DeadCode PD 13Nov97 								SWord y)
//DeadCode PD 13Nov97 {
//DeadCode PD 13Nov97 	SWord	var_ax,var_si,var_dx,var_bp;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	SWord	CentXLocal,CentYLocal;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	CentXLocal = x;
//DeadCode PD 13Nov97 	CentYLocal = y;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_si = 0;
//DeadCode PD 13Nov97 	var_ax = var_dx = radius;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_dx = 3;
//DeadCode PD 13Nov97 	var_dx -= var_ax<<1;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 loopC:
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	CIRCLE_POINTS();
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	if (var_dx>=0)	goto Over;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_dx += 6;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_bp = var_si<<2;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_dx += var_bp;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_si++;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	if (var_si<var_ax)	goto loopC;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	if (var_si!=var_ax)	goto Out;
//DeadCode PD 13Nov97 	
//DeadCode PD 13Nov97 	CIRCLE_POINTS();
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	goto Out;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 Over:
//DeadCode PD 13Nov97 	var_bp = var_si;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_bp -= var_ax;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_bp >>= 2;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_dx += var_bp;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_dx += 10;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_ax--;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	var_si++;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	if (var_si<var_ax) goto loopC;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	if (var_si!=var_ax)	goto Out;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	CIRCLE_POINTS();
//DeadCode PD 13Nov97 Out:
//DeadCode PD 13Nov97 	return;
//DeadCode PD 13Nov97 	}
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 #undef	CIRCLE_POINTS			//PD 13Nov97
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode PD 13Nov97 //Procedure		FuzzyLine
//DeadCode PD 13Nov97 //Author		Paul.   
//DeadCode PD 13Nov97 //Date			Mon 28 Jul 1997
//DeadCode PD 13Nov97 //
//DeadCode PD 13Nov97 //Description	Draws a horizontal line from (cx-dx,cy+dy) to
//DeadCode PD 13Nov97 //				(cx+dx,cy+dy) transparent at endpoints but
//DeadCode PD 13Nov97 //				of opacity cInt in the center
//DeadCode PD 13Nov97 //Inputs		
//DeadCode PD 13Nov97 //
//DeadCode PD 13Nov97 //Returns	
//DeadCode PD 13Nov97 //
//DeadCode PD 13Nov97 //------------------------------------------------------------------------------
//DeadCode PD 13Nov97 void Graphic::FuzzyLine(SWord cx,SWord cy,SWord dx,SWord dy,SWord rad,SWord cInt)
//DeadCode PD 13Nov97 {
//DeadCode PD 13Nov97 	SWord		MinX,MaxX,MinY,MaxY;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	MinY = PhysicalMinY;
//DeadCode PD 13Nov97 	MaxY = MinY + PhysicalHeight;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	// Y-clipping
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	if (cy+dy<MinY || cy+dy>=MaxY || dx==0)	return;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	MinX = PhysicalMinX;
//DeadCode PD 13Nov97 	MaxX = MinX + PhysicalWidth;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	LogicalPtr	scradr;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	SLong		xoffset,yoffset;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	//use dx,dy & cInt to generate an intensity
//DeadCode PD 13Nov97 	//value at either end of the line and at it's
//DeadCode PD 13Nov97 	//center point.
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	dx = (dx<0)?-dx:dx;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	//y first
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	SWord	abs_dy = dy<0?-dy:dy;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	abs_dy <<= 8;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	abs_dy /= rad;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	abs_dy = 256 - abs_dy;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	//abs_dy == 256 when dy == +/- radius
//DeadCode PD 13Nov97 	//abs_dy == 0   when dy == 0
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	SWord	dInt,rInt;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	dInt = abs_dy/dx;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	rInt = 0;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	Master()->LockBackScreen (TRUE,LOWLOCK);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	yoffset = BytesPerScanLine * (cy+dy);
//DeadCode PD 13Nov97 	xoffset = BytesPerPixel * (cx-dx+1);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	scradr = logicalscreenptr + xoffset + yoffset;
//DeadCode PD 13Nov97 	
//DeadCode PD 13Nov97 	int	tmpx = cx-dx+1;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	int	cnt;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	UWord	*wscradr;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 	switch (BytesPerPixel)
//DeadCode PD 13Nov97 	{
//DeadCode PD 13Nov97 		case 1:
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 		for (cnt=1;cnt<=dx;cnt++,tmpx++)
//DeadCode PD 13Nov97 		{
//DeadCode PD 13Nov97 			if (tmpx<MinX || tmpx>=MaxX)
//DeadCode PD 13Nov97 				scradr++;
//DeadCode PD 13Nov97 			else
//DeadCode PD 13Nov97 				*scradr++ = GREY00 + (rInt>>4);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 			rInt+=dInt;
//DeadCode PD 13Nov97 		}
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 		for (cnt=0;cnt<dx;cnt++,tmpx++)
//DeadCode PD 13Nov97 		{
//DeadCode PD 13Nov97 			if (tmpx<MinX || tmpx>=MaxX)
//DeadCode PD 13Nov97 				scradr++;
//DeadCode PD 13Nov97 			else
//DeadCode PD 13Nov97 				*scradr++ = GREY00 + (rInt>>4);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 			rInt-=dInt;
//DeadCode PD 13Nov97 		}
//DeadCode PD 13Nov97 		break;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 		case 2:
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 		rInt = 0xFF - rInt;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 		dInt =- dInt;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 		wscradr = (UWord*)scradr;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 		for (cnt=1;cnt<=dx;cnt++,tmpx++)
//DeadCode PD 13Nov97 		{
//DeadCode PD 13Nov97 			if (tmpx<MinX || tmpx>=MaxX)
//DeadCode PD 13Nov97 				wscradr++;
//DeadCode PD 13Nov97 			else
//DeadCode PD 13Nov97 			{
//DeadCode PD 13Nov97 				UWord	srccol,newcol;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				ULong	tmp;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				srccol = *wscradr;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				tmp = srccol & 0x001F; tmp *= rInt; tmp >>= 8;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				newcol = (UWord)tmp;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				tmp = srccol & 0x07E0; tmp *= rInt; tmp >>= 8;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				newcol += (UWord)(tmp & 0x07E0);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				tmp = srccol & 0xF800; tmp *= rInt; tmp >>= 8;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				newcol += (UWord)(tmp & 0xF800);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				*wscradr++ = newcol;
//DeadCode PD 13Nov97 			}
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 			rInt+=dInt;
//DeadCode PD 13Nov97 		}
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 		for (cnt=0;cnt<dx;cnt++,tmpx++)
//DeadCode PD 13Nov97 		{
//DeadCode PD 13Nov97 			if (tmpx<MinX || tmpx>=MaxX)
//DeadCode PD 13Nov97 				wscradr++;
//DeadCode PD 13Nov97 			else
//DeadCode PD 13Nov97 			{
//DeadCode PD 13Nov97 				UWord	srccol,newcol;
//DeadCode PD 13Nov97 				
//DeadCode PD 13Nov97 				ULong	tmp;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				srccol = *wscradr;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				tmp = srccol & 0x001F; tmp *= rInt; tmp >>= 8;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				newcol = (UWord)tmp;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				tmp = srccol & 0x07E0; tmp *= rInt; tmp >>= 8;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				newcol += (UWord)(tmp & 0x07E0);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				tmp = srccol & 0xF800; tmp *= rInt; tmp >>= 8;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				newcol += (UWord)(tmp & 0xF800);
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 				*wscradr++ = newcol;
//DeadCode PD 13Nov97 			}
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 			rInt-=dInt;
//DeadCode PD 13Nov97 		}
//DeadCode PD 13Nov97 		break;
//DeadCode PD 13Nov97 
//DeadCode PD 13Nov97 		default:
//DeadCode PD 13Nov97 		break;
//DeadCode PD 13Nov97 	}
//DeadCode PD 13Nov97 	Master()->UnLockBackScreen (LOWLOCK);
//DeadCode PD 13Nov97 }





















