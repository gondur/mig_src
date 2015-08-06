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
		#include	"polygon.h"
		#include	"matrix.h"

//TempCode PD 16May96 #define	DUMPALIASTABLE	TRUE

		class polygon POLYGON;

extern	SLong ASM_AmulBdivC(SLong,SLong,SLong);
#pragma	aux ASM_AmulBdivC = 	\
		"imul	ebx"			\
		"idiv	ecx"			\
		parm  [eax] [ebx] [ecx]	\
		value [eax]				\
		modify[edx]

////////////////////////////////////////////////////////////////////////////////
//
//	FIRST THE CREATEPOLY ROUTINES - these setup jumps to poly type specific
//	routines as well as reseting a few variables.
//
////////////////////////////////////////////////////////////////////////////////
		
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCrossProduct
//Author		Paul.   
//Date			Fri 3 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool polygon::SetCrossProduct(Bool flag)
{
	Bool	ret_val = crossprod;
	crossprod = flag;
	return(ret_val);
}

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
	polycolour = colour;										//PD 30Jan96

	if (polycolour == ARTWORKMASK)								//PD 14Jun96
		SetPixelWidth(4);										//PD 14Jun96

	vertex_index = vertex_list;
	vertexcount = 0;
	zclip = 											//PD 10May96
		dzclip = FALSE;								//PD 10May96

	currscreen->SetColour(colour);									//PD 29Nov95
	polytype=PLAIN;												//PD 03Jan96
	horilinertn = currscreen->GetScanLineAddr(polytype);		//PD 03Jan96

	scanconvert		= &polygon::cpolyscancnvrt;
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
void polygon::createpoly(Colour basecol, ColourRange rng)		//JIM 12Dec95
{
	polycolour = basecol;										//PD 30Jan96
	polyrange = rng;											//PD 30Jan96

//DeadCode PD 05Feb96 	vertices_allocated = 0;
	vertex_index = vertex_list;
	vertexcount = 0;
	zclip = 											//PD 10May96
		dzclip = FALSE;								//PD 10May96
	
	currscreen->SetColour(basecol,rng);							//PD 29Nov95
	polytype=GOURAUD;											//PD 03Jan96
	horilinertn = currscreen->GetScanLineAddr(polytype);		//PD 03Jan96

	scanconvert		= &polygon::gpolyscancnvrt;
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
void polygon::createpoly(ImageMapNumber imapno)
{
	polyimage = imapno;											//PD 30Jan96

//DeadCode PD 05Feb96 	vertices_allocated = 0;
	vertex_index = vertex_list;
	vertexcount = 0;
	zclip = 											//PD 10May96
		dzclip = FALSE;								//PD 10May96
	
	ImageMapNumber	realmapno;

	realmapno 		= (imapno>0)?imapno:(ImageMapNumber)-imapno;

	scanconvert		= &polygon::ipolyscancnvrt;

	if(realmapno!=imapno)
		polytype=IMAPPED_M;										//PD 03Jan96
	else
		polytype=IMAPPED;										//PD 03Jan96

	currscreen->SetColour(realmapno);								//PD 29Nov95
	horilinertn = currscreen->GetScanLineAddr(polytype);		//PD 03Jan96
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
	zclip 			=											//PD 10May96
		dzclip = FALSE;											//PD 10May96
	scanconvert		= &polygon::ipolyscancnvrt;
	polytype		= IMAPPED;
	horilinertn 	= currscreen->GetScanLineAddr(polytype);
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

//DeadCode PD 05Feb96 	vertices_allocated = 0;
	vertex_index = vertex_list;
	vertexcount = 0;
	zclip = 											//PD 10May96
		dzclip = FALSE;								//PD 10May96
	
	ImageMapNumber	realmapno;

	realmapno 		= (ImageMapNumber )((imapno>0)?imapno:(ImageMapNumber)-imapno);

	scanconvert		= &polygon::ipolyscancnvrt;

	if(realmapno!=(ImageMapNumber)imapno)
		polytype=OMAPPED_M;
	else
		polytype=OMAPPED;

	currscreen->SetColour(realmapno);
	horilinertn = currscreen->GetScanLineAddr(polytype);
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

//DeadCode PD 05Feb96 	vertices_allocated = 0;
	vertex_index = vertex_list;
	vertexcount = 0;
	zclip = 											//PD 10May96
		dzclip = FALSE;								//PD 10May96

	if(crng==(ColourRange)-1)									//DAW 18Dec95
	{
		ImageMapNumber	realmapno;
		Colour			basecol = RANGE00;						//DAW 18Dec95
		ColourRange	rng = (ColourRange)SPREAD00;				//DAW 18Dec95
	
		realmapno 		= (imapno>0)?imapno:(ImageMapNumber)-imapno;
	
		scanconvert		= &polygon::sipolyscancnvrt;
	
		if(realmapno!=imapno)
			_Error.EmitSysErr(__FILE__"Masking not available.");
		else
			polytype=IMAPPED_SH;								//PD 03Jan96
	
		currscreen->SetColour(basecol,rng);
		currscreen->SetColour(realmapno);
		horilinertn = currscreen->GetScanLineAddr(polytype);	//PD 03Jan96
	}
	else
	{
		_Error.EmitSysErr(__FILE__"Bad colour range value");
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
	polyimage	= imapno;										//PD 30Jan96
	polycolour	= basecol;										//PD 30Jan96

//DeadCode PD 05Feb96 	vertices_allocated = 0;
	vertex_index = vertex_list;
	vertexcount = 0;
	zclip = 											//PD 10May96
		dzclip = FALSE;								//PD 10May96
	
	ImageMapNumber	realmapno;

	realmapno 		= (imapno>0)?imapno:(ImageMapNumber)-imapno;

	scanconvert		= &polygon::ipolyscancnvrt;

	if(realmapno!=imapno)
		_Error.EmitSysErr(__FILE__":masked draw routine not available.");
	else
		polytype=IMAPPED_B;										//PD 03Jan96

	currscreen->SetColour(basecol);								//PD 29Nov95
	currscreen->SetColour(realmapno);								//PD 29Nov95
	horilinertn = currscreen->GetScanLineAddr(polytype);		//PD 03Jan96
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

//DeadCode PD 05Feb96 	vertices_allocated = 0;
	vertex_index = vertex_list;
	vertexcount = 0;
	zclip = 											//PD 10May96
		dzclip = FALSE;								//PD 10May96
	
	ImageMapNumber	realmapno;

	realmapno 		= (imapno>0)?imapno:(ImageMapNumber)-imapno;

	scanconvert		= &polygon::sipolyscancnvrt;

	if(realmapno!=imapno)
		_Error.EmitSysErr(__FILE__":masked draw routine not available.");
	else
		polytype=IMAPPED_S;										//PD 03Jan96

	currscreen->SetColour(realmapno);								//PD 29Nov95
	currscreen->SetColour(basecol,rng);							//PD 29Nov95
	horilinertn = currscreen->GetScanLineAddr(polytype);		//PD 03Jan96
}

////////////////////////////////////////////////////////////////////////////////
//
//	THE CREATEVERTEX ROUTINES - these copy over the vertex data required for
//	the different types of poly. They also check to see if any zclipping is
//	required.
//
////////////////////////////////////////////////////////////////////////////////

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
	UWord	scalefactor;

	if(vertexcount>MaxIVertz)
		_Error.EmitSysErr(__FILE__":IVERTZ buffer o'flow");

	VERTEX_PTR temp = AllocateVertex();

	scalefactor = dopoint.scalefactor;

	zplane = _matrix.realZ(scalefactor);

	temp->bx = dopoint.bodyx;
	temp->by = dopoint.bodyy;
	temp->bz = dopoint.bodyz;
	temp->scalefactor = dopoint.scalefactor;

	temp->sx = dopoint.screenx;
	temp->sy = dopoint.screeny;

	if(temp->bz < zplane)	zclip = TRUE;

	if(usdistzplane)												//PD 16May96
		if(temp->bz>>(16-scalefactor)>usdistzplane)				//AM 16May96
			dzclip = TRUE;								//PD 09May96

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
	UWord	scalefactor;

	if(vertexcount>MaxIVertz)
		_Error.EmitSysErr(__FILE__":IVERTZ buffer o'flow");

	VERTEX_PTR temp = AllocateVertex();

	scalefactor = dopoint.scalefactor;

	zplane = _matrix.realZ(scalefactor);

	temp->bx = dopoint.bodyx;
	temp->by = dopoint.bodyy;
	temp->bz = dopoint.bodyz;
	temp->scalefactor = dopoint.scalefactor;

	temp->sx = dopoint.screenx;
	temp->sy = dopoint.screeny;
	temp->intensity = (intens&0x0FF)<<12;	//16;				//PD 10Jun96

	if(temp->bz < zplane)	zclip = TRUE;

	if(usdistzplane)												//PD 16May96
		if(temp->bz>>(16-temp->scalefactor)>usdistzplane)		//AM 16May96
			dzclip = TRUE;								//PD 09May96

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
	UWord	scalefactor;

	if(vertexcount>MaxIVertz)
		_Error.EmitSysErr(__FILE__":IVERTZ buffer o'flow");

	VERTEX_PTR temp = AllocateVertex();

	scalefactor = dopoint.scalefactor;

	zplane = _matrix.realZ(scalefactor);

	temp->bx = dopoint.bodyx;
	temp->by = dopoint.bodyy;
	temp->bz = dopoint.bodyz;
	temp->scalefactor = dopoint.scalefactor;

	temp->sx = dopoint.screenx;
	temp->sy = dopoint.screeny;
	temp->ix = imagex<<16;
	temp->iy = imagey<<16;

	if(temp->bz < zplane )	zclip = TRUE;

	if(usdistzplane)												//PD 16May96
		if(temp->bz>>(16-temp->scalefactor)>usdistzplane)		//AM 16May96
			dzclip = TRUE;								//PD 09May96

	nvertptr[vertexcount] = temp;

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
void polygon::createvert(landvertex& landvert)
{
	UWord	scalefactor;

	if(vertexcount>MaxIVertz)
		_Error.EmitSysErr(__FILE__":IVERTZ buffer o'flow");

	VERTEX_PTR temp = AllocateVertex();

	scalefactor = landvert.scale;

	zplane = _matrix.realZ(scalefactor);

	temp->bx = landvert.bodyx;
	temp->by = landvert.bodyy;
	temp->bz = landvert.bodyz;
	temp->scalefactor = landvert.scale;

	temp->sx = landvert.sx;
	temp->sy = landvert.sy;

	if(temp->bz < zplane)	zclip = TRUE;

	if(usdistzplane)												//PD 16May96
		if(temp->bz>>(16-temp->scalefactor)>usdistzplane)		//AM 16May96
			dzclip = TRUE;								//PD 09May96

	nvertptr[vertexcount] = temp;

	vertexcount++;

	nvertptr[vertexcount] = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		createvert
//Author		Paul.   
//Date			Mon 10 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::createvert(landvertex& landvert, SWord &intens)
{
	UWord	scalefactor;

	if(vertexcount>MaxIVertz)
		_Error.EmitSysErr(__FILE__":IVERTZ buffer o'flow");

	VERTEX_PTR temp = AllocateVertex();

	scalefactor = landvert.scale;

	zplane = _matrix.realZ(scalefactor);

	temp->bx = landvert.bodyx;
	temp->by = landvert.bodyy;
	temp->bz = landvert.bodyz;
	temp->scalefactor = landvert.scale;

	temp->sx = landvert.sx;
	temp->sy = landvert.sy;
	temp->intensity = (intens&0x0FF)<<12; //16;					//PD 10Jun96

	if(temp->bz < zplane)	zclip = TRUE;

	if(usdistzplane)												//PD 16May96
		if(temp->bz>>(16-temp->scalefactor)>usdistzplane)		//AM 16May96
			dzclip = TRUE;								//PD 09May96

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
void polygon::createvert(landvertex& landvert, SWord &imagex, SWord &imagey)//PD 25Jan96
{
	UWord	scalefactor;

	if(vertexcount>MaxIVertz)
		_Error.EmitSysErr(__FILE__":IVERTZ buffer o'flow");

	VERTEX_PTR temp = AllocateVertex();

	scalefactor = landvert.scale;

	zplane = _matrix.realZ(scalefactor);

	temp->bx = landvert.bodyx;
	temp->by = landvert.bodyy;
	temp->bz = landvert.bodyz;
	temp->scalefactor = landvert.scale;

	temp->sx = landvert.sx;
	temp->sy = landvert.sy;
	temp->ix = imagex<<16;
	temp->iy = imagey<<16;

	if(temp->bz < zplane )	zclip = TRUE;

	if(usdistzplane)												//PD 16May96
		if(temp->bz>>(16-temp->scalefactor)>usdistzplane)		//AM 16May96
			dzclip = TRUE;								//PD 09May96

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
	UWord	scalefactor;

	if(vertexcount>MaxIVertz)
		_Error.EmitSysErr(__FILE__":IVERTZ buffer o'flow");

	VERTEX_PTR temp = AllocateVertex();

	scalefactor = dopoint.scalefactor;

	zplane = _matrix.realZ(scalefactor);

	temp->bx = dopoint.bodyx;
	temp->by = dopoint.bodyy;
	temp->bz = dopoint.bodyz;
	temp->scalefactor = dopoint.scalefactor;

	temp->sx = dopoint.screenx;
	temp->sy = dopoint.screeny;
	temp->ix = imagex<<16;
	temp->iy = imagey<<16;
	temp->intensity = (intens&0x0FF)<<12; //16;					//PD 10Jun96

	if(temp->bz < zplane )	zclip = TRUE;

	if(usdistzplane)												//PD 16May96
		if(temp->bz>>(16-temp->scalefactor)>usdistzplane)		//AM 16May96
			dzclip = TRUE;								//PD 09May96

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
void polygon::createvert(landvertex& landvert,SWord& imagex,SWord& imagey,SWord& intens)
{
	UWord	scalefactor;

	if(vertexcount>MaxIVertz)
		_Error.EmitSysErr(__FILE__":IVERTZ buffer o'flow");

	VERTEX_PTR temp = AllocateVertex();

	scalefactor = landvert.scale;

	zplane = _matrix.realZ(scalefactor);

	temp->bx = landvert.bodyx;
	temp->by = landvert.bodyy;
	temp->bz = landvert.bodyz;
	temp->scalefactor = landvert.scale;

	temp->sx = landvert.sx;
	temp->sy = landvert.sy;
	temp->ix = imagex<<16;
	temp->iy = imagey<<16;
	temp->intensity = (intens&0x0FF)<<12; //16;					//PD 10Jun96

	if(temp->bz < zplane )	zclip = TRUE;

	if(usdistzplane)												//PD 16May96
		if(temp->bz>>(16-temp->scalefactor)>usdistzplane)		//AM 16May96
			dzclip = TRUE;								//PD 09May96

	nvertptr[vertexcount] = temp;

	vertexcount++;

	nvertptr[vertexcount] = NULL;
}

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
	UWord	scalefactor;

	if(vertexcount>MaxIVertz)
		_Error.EmitSysErr(__FILE__":IVERTZ buffer o'flow");

	VERTEX_PTR temp = AllocateVertex();

	scalefactor = vertx.scalefactor;

	zplane = _matrix.realZ(scalefactor);

	copyvertex(*temp,vertx);

	if(temp->bz < zplane )	zclip = TRUE;

	if(usdistzplane)												//PD 16May96
		if(temp->bz>>(16-temp->scalefactor)>usdistzplane)		//AM 16May96
			dzclip = TRUE;								//PD 09May96

	nvertptr[vertexcount] = temp;

	vertexcount++;

	nvertptr[vertexcount] = NULL;
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
Bool polygon::setpolyscrn(Window* w)
{
	currscreen = w;

	SLong	temp = currscreen->PhysicalWidth-1;

	LeftX = currscreen->PhysicalMinX;
	RightX = currscreen->PhysicalMinX+temp;

	temp = currscreen->PhysicalHeight;

	TopY	= currscreen->PhysicalMinY;
	BotY	= currscreen->PhysicalMinY + temp;

//DeadCode PD 19Feb96 	AllocateYList(currscreen);

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
void polygon::drawpoly()
{

	HLINELIST	whll;

	DIRECTION	led;

	SLong		dxn,	dyn,	dxp,
				dyp,	miny,	maxy;

	VERTEX_PTR	*nindp,	*pindp,	*tempp,
				*maxip,	*minilp,*minirp;

	//discard polygons with too few points

	if(vertexcount<3)
		return;

	if(zclip)
		if(!zclippoly())
			return;

	if(dzclip && usdistzplane)									//PD 16May96
		if(!zclippoly2())										//PD 16May96
			return;												//PD 16May96

	if (crossprod )
		if(!checkpoly())
			return;

//TempCode PD 01Feb96 	if(subdivide)
//TempCode PD 01Feb96 		SubDivide();

	if(!clippoly())
		return;

	if(PolyHidden())											//PD 16Feb96
		return;													//PD 16Feb96

	//Scan the list to find the top and bottom of the polygon

	minilp =
		maxip = nvertptr;

	maxy =
		miny = (*nvertptr)->sy;

	tempp = nvertptr+1;

	while(*tempp)
	{
		if((*tempp)->sy<miny)
		{
			minilp = tempp;
			miny = (*tempp)->sy;
		}
		else
		{
			if((*tempp)->sy>maxy)
			{
				maxip = tempp;
				maxy = (*tempp)->sy;
			}
		}
		tempp++;
	}

	//Quick exit for flat polygons

	if(miny==maxy)
		return;

	//Scan in ascending order to find last top-edge point

	minirp = minilp;

	while((*minirp)->sy == miny)
	{
		minirp++;
		if(!*minirp) minirp = nvertptr;
	}

	minirp--;

	if(!*minirp) minirp+=vertexcount;

	//Now scan in descending order to find first top-edge point

	while((*minilp)->sy == miny)
	{
		minilp--;
		if(!*minilp) minilp+=vertexcount;
	}

	minilp++;
	if(!*minilp) minilp = nvertptr;

	//Figure out which direction to go through the vertex list from the
	//top vertex which is the left and which is the right.

	led = BACKWARDS;

	if((*minilp)->sx!=(*minirp)->sx)
	{
		//If the top is flat just see which end is leftmost

		if((*minilp)->sx>(*minirp)->sx)
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

		dxn = (*nindp)->sx-(*minilp)->sx;
		dyn = (*nindp)->sy-(*minilp)->sy;

		dxp = (*pindp)->sx-(*minirp)->sx;
		dyp = (*pindp)->sy-(*minirp)->sy;

		if((dxn*dyp)<(dyn*dxp))
		{
			led = FORWARDS;
			tempp = minilp;
			minilp = minirp;
			minirp = tempp;
		}
	}

	if((whll.length = maxy-miny)==0)	return;

	whll.starty = miny;
	whll.endy	= maxy;
	whll.led	= led;
	whll.minilp	= minilp;
	whll.minirp	= minirp;
	whll.maxip	= maxip;

	//The actual scan conversion is poly type specific
	//Useful variables at this stage are:
	//
	//whll.length		=	total scan lines in polygon
	//whll.starty		=	top scan line of the polygon
	//whll.endy			=	last scan line in the polygon
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
}

////////////////////////////////////////////////////////////////////////////////
//
//	GENERAL ROUTINES ie. screen clip, z-clip, cross product checks
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		checkpoly
//Author		Paul.   
//Date			Fri 20 Oct 1995
//
//Description	Does screen clip & cross product checks
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool polygon::checkpoly()
{
	Bool	retval;

	DoPointStruc	p0,p1,p2;

	//cross product first

	p0.screenx = nvertptr[0]->sx;
	p0.screeny = nvertptr[0]->sy;

	p1.screenx = nvertptr[1]->sx;
	p1.screeny = nvertptr[1]->sy;

	p2.screenx = nvertptr[2]->sx;
	p2.screeny = nvertptr[2]->sy;

	retval = _matrix.crossproduct(p0,p1,p2);

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		zclippoly
//Author		Paul.   
//Date			Wed 25 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool polygon::zclippoly()
{

	int		count;												//PD 12Dec95

	int		newvertcount=0;

	SLong	screenscale;										//PD 12Jun96

	VERTEX	v0,v1,v2;

	VERTEX_PTR	temp,
				left 	= &v0,
				right	= &v1,
				chop	= &v2;

	//Some setting up for various body coordinate scalings

	setscale();

	screenscale = currscreen->PhysicalWidth>>1;					//PD 12Jun96

	VERTEX_PTR	*cind,
				*nind,
				*newpnt;

	cind = nvertptr;
	nind = nvertptr+1;
	newpnt = zvertptr;


	for(count=vertexcount;count--;)
	{
		if((*cind)->bz>=zplane)
		{
			//This vertex is okay

			if(newvertcount>MaxIVertz)
				_Error.EmitSysErr(__FILE__":ZVERTZ buffer o'flow");

			*newpnt++ = *cind;

			newvertcount++;

			//Next vertex is -ve so needs clipping

			if((*nind)->bz<zplane)
			{
				//binary chop time!

				copyvertex(*left,**cind);

				copyvertex(*right,**nind);

				if(left->bz>right->bz)
				{
					temp = right;
					right = left;
					left = temp;
				}

//Old_Code PD 11Jun96 				chopvertex(*chop,*left,*right);

				SLong	dbz = (right->bz>>1) - (left->bz>>1);

				SLong	cbz = (zplane>>1) - (left->bz>>1);

				chop->bz = zplane;

				chop->bx = 	left->bx +
							ASM_AmulBdivC(	right->bx - left->bx,
											cbz,
											dbz
											);
				chop->by = 	left->by +
							ASM_AmulBdivC(	right->by - left->by,
											cbz,
											dbz
											);

				chop->ix = 	left->ix +
							ASM_AmulBdivC(	right->ix - left->ix,
											cbz,
											dbz
											);
				chop->iy = 	left->iy +
							ASM_AmulBdivC(	right->iy - left->iy,
											cbz,
											dbz
											);

				chop->intensity = 	left->intensity +
									ASM_AmulBdivC(	right->intensity - left->intensity,
													cbz,
													dbz
													);

				chop->sx = ASM_AmulBdivC(	chop->bx,
											screenscale,
											zplane
											);

				chop->sy = -ASM_AmulBdivC(	chop->by,
											screenscale,
											zplane
											);

//DeadCode PD 11Jun96 				while((chop->bz&zmask)!=zplane)
//DeadCode PD 11Jun96 				{
//DeadCode PD 11Jun96 					if(chop->bz>=zplane)
//DeadCode PD 11Jun96 					{
//DeadCode PD 11Jun96 						temp = right;
//DeadCode PD 11Jun96 						right = chop;
//DeadCode PD 11Jun96 						chop = temp;
//DeadCode PD 11Jun96 					}
//DeadCode PD 11Jun96 					else
//DeadCode PD 11Jun96 					{
//DeadCode PD 11Jun96 						temp = left;
//DeadCode PD 11Jun96 						left = chop;
//DeadCode PD 11Jun96 						chop = temp;
//DeadCode PD 11Jun96 					}
//DeadCode PD 11Jun96 					chopvertex(*chop,*left,*right);
//DeadCode PD 11Jun96 				}

				//New vertex to add is 'chop'

				if(newvertcount>MaxIVertz)
					_Error.EmitSysErr(__FILE__":ZVERTZ buffer o'flow");

				*newpnt = AllocateVertex();

				copyvertex(**newpnt,*chop);

//DeadCode PD 12Jun96 				//Calculate new screen coordinates

//DeadCode PD 12Jun96 				_matrix.body2screen(currscreen,**newpnt);

				newpnt++;

				newvertcount++;
			}
		}
		else
		{
			if((*nind)->bz>=zplane)
			{
				//This vertex is -ve & the next one is +ve so
				//create a new clipped vertex between the two

				//binary chop time!

				copyvertex(*left,**cind);

				copyvertex(*right,**nind);

				if(left->bz>right->bz)
				{
					temp = right;
					right = left;
					left = temp;
				}

//DeadCode PD 11Jun96 				chopvertex(*chop,*left,*right);

				SLong	dbz = (right->bz>>1) - (left->bz>>1);

				SLong	cbz = (zplane>>1) - (left->bz>>1);

				chop->bz = zplane;

				chop->bx = 	left->bx +
							ASM_AmulBdivC(	right->bx - left->bx,
											cbz,
											dbz
											);
				chop->by = 	left->by +
							ASM_AmulBdivC(	right->by - left->by,
											cbz,
											dbz
											);

				chop->ix = 	left->ix +
							ASM_AmulBdivC(	right->ix - left->ix,
											cbz,
											dbz
											);
				chop->iy = 	left->iy +
							ASM_AmulBdivC(	right->iy - left->iy,
											cbz,
											dbz
											);

				chop->intensity = 	left->intensity +
									ASM_AmulBdivC(	right->intensity - left->intensity,
													cbz,
													dbz
													);

				chop->sx = ASM_AmulBdivC(	chop->bx,
											screenscale,
											zplane
											);

				chop->sy = -ASM_AmulBdivC(	chop->by,
											screenscale,
											zplane
											);

//DeadCode PD 11Jun96 				while((chop->bz&zmask)!=zplane)
//DeadCode PD 11Jun96 				{
//DeadCode PD 11Jun96 					if(chop->bz>=zplane)
//DeadCode PD 11Jun96 					{
//DeadCode PD 11Jun96 						temp = right;
//DeadCode PD 11Jun96 						right = chop;
//DeadCode PD 11Jun96 						chop = temp;
//DeadCode PD 11Jun96 					}
//DeadCode PD 11Jun96 					else
//DeadCode PD 11Jun96 					{
//DeadCode PD 11Jun96 						temp = left;
//DeadCode PD 11Jun96 						left = chop;
//DeadCode PD 11Jun96 						chop = temp;
//DeadCode PD 11Jun96 					}
//DeadCode PD 11Jun96 					chopvertex(*chop,*left,*right);
//DeadCode PD 11Jun96 				}

				//New vertex to add is 'chop'

				if(newvertcount>MaxIVertz)
					_Error.EmitSysErr(__FILE__":ZVERTZ buffer o'flow");

				*newpnt = AllocateVertex();

				copyvertex(**newpnt,*chop);

//DeadCode PD 12Jun96 				//Calculate new screen coordinates

//DeadCode PD 12Jun96 				_matrix.body2screen(currscreen,**newpnt);

				newpnt++;

				newvertcount++;
			}
			//else, both are -ve so do nothing
		}
		cind = nind;

		nind++;

		if(!*nind)
			nind = nvertptr;
	}

	if(newvertcount<3)	return(FALSE);

	//Copy back the new set of vertices

	for(count=newvertcount;count--;)							//PD 12Dec95
		nvertptr[count]=zvertptr[count];							//PD 12Dec95

	nvertptr[newvertcount]=NULL;

	vertexcount = newvertcount;

	VertexOFlowTest();											//PD 07Feb96

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	zclippoly2
//------------------------------------------------------------------------------
//Author	Paul    
//Date		Fri 10 May 1996
//Modified	
//
//Description	z-clip to distant z-plane
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Bool polygon::zclippoly2()
{
	int		count;												//PD 12Dec95

	int		newvertcount=0;

//TempCode PD 12Jun96 	SLong	screenscale;										//PD 12Jun96

	VERTEX	v0,v1,v2;

	VERTEX_PTR	temp,
				left 	= &v0,
				right	= &v1,
				chop	= &v2;

	//Some setting up for various body coordinate scalings

	setscale();

//TempCode PD 12Jun96 	screenscale = currscreen->PhysicalWidth>>1;					//PD 12Jun96

	VERTEX_PTR	*cind,
				*nind,
				*newpnt;

	cind = nvertptr;
	nind = nvertptr+1;
	newpnt = zvertptr;

	for(count=vertexcount;count--;)
	{
		if((*cind)->bz<=distzplane)
		{
			//This vertex is okay

			if(newvertcount>MaxIVertz)
				_Error.EmitSysErr(__FILE__":ZVERTZ buffer o'flow");

			*newpnt++ = *cind;

			newvertcount++;

			//Next vertex is -ve so needs clipping

			if((*nind)->bz>=distzplane)
			{
				//binary chop time!

				copyvertex(*left,**cind);

				copyvertex(*right,**nind);

				if(left->bz>right->bz)
				{
					temp = right;
					right = left;
					left = temp;
				}

//DeadCode PD 12Jun96 				chopvertex(*chop,*left,*right);

				SLong	dbz = (right->bz>>1) - (left->bz>>1);

				SLong	cbz = (distzplane>>1) - (left->bz>>1);

				chop->bz = distzplane;

				chop->bx = 	left->bx +
							ASM_AmulBdivC(	right->bx - left->bx,
											cbz,
											dbz
											);
				chop->by = 	left->by +
							ASM_AmulBdivC(	right->by - left->by,
											cbz,
											dbz
											);

				chop->ix = 	left->ix +
							ASM_AmulBdivC(	right->ix - left->ix,
											cbz,
											dbz
											);
				chop->iy = 	left->iy +
							ASM_AmulBdivC(	right->iy - left->iy,
											cbz,
											dbz
											);

				chop->intensity = 	left->intensity +
									ASM_AmulBdivC(	right->intensity - left->intensity,
													cbz,
													dbz
													);

//TempCode PD 12Jun96 				chop->sx = ASM_AmulBdivC(	chop->bx,
//TempCode PD 12Jun96 											screenscale,
//TempCode PD 12Jun96 											distzplane
//TempCode PD 12Jun96 											);
//TempCode PD 12Jun96 
//TempCode PD 12Jun96 				chop->sy = -ASM_AmulBdivC(	chop->by,
//TempCode PD 12Jun96 											screenscale,
//TempCode PD 12Jun96 											distzplane
//TempCode PD 12Jun96 											);

//DeadCode PD 12Jun96 				while((chop->bz&zmask)!=distzplane)
//DeadCode PD 12Jun96 				{
//DeadCode PD 12Jun96 					if(chop->bz>=distzplane)
//DeadCode PD 12Jun96 					{
//DeadCode PD 12Jun96 						temp = right;
//DeadCode PD 12Jun96 						right = chop;
//DeadCode PD 12Jun96 						chop = temp;
//DeadCode PD 12Jun96 					}
//DeadCode PD 12Jun96 					else
//DeadCode PD 12Jun96 					{
//DeadCode PD 12Jun96 						temp = left;
//DeadCode PD 12Jun96 						left = chop;
//DeadCode PD 12Jun96 						chop = temp;
//DeadCode PD 12Jun96 					}
//DeadCode PD 12Jun96 					chopvertex(*chop,*left,*right);
//DeadCode PD 12Jun96 				}

				//New vertex to add is 'chop'

				if(newvertcount>MaxIVertz)
					_Error.EmitSysErr(__FILE__":ZVERTZ buffer o'flow");

				*newpnt = AllocateVertex();

				chop->intensity=255<<12; //16;					//PD 10Jun96

				copyvertex(**newpnt,*chop);

 				//Calculate new screen coordinates

 				_matrix.body2screen(**newpnt);					//PD 25Jul96

				newpnt++;

				newvertcount++;
			}
		}
		else
		{
			if((*nind)->bz<=distzplane)
			{
				//This vertex is -ve & the next one is +ve so
				//create a new clipped vertex between the two

				//binary chop time!

				copyvertex(*left,**cind);

				copyvertex(*right,**nind);

				if(left->bz>right->bz)
				{
					temp = right;
					right = left;
					left = temp;
				}

//DeadCode PD 12Jun96 				chopvertex(*chop,*left,*right);

				SLong	dbz = (right->bz>>1) - (left->bz>>1);

				SLong	cbz = (distzplane>>1) - (left->bz>>1);

				chop->bz = distzplane;

				chop->bx = 	left->bx +
							ASM_AmulBdivC(	right->bx - left->bx,
											cbz,
											dbz
											);
				chop->by = 	left->by +
							ASM_AmulBdivC(	right->by - left->by,
											cbz,
											dbz
											);

				chop->ix = 	left->ix +
							ASM_AmulBdivC(	right->ix - left->ix,
											cbz,
											dbz
											);
				chop->iy = 	left->iy +
							ASM_AmulBdivC(	right->iy - left->iy,
											cbz,
											dbz
											);

				chop->intensity = 	left->intensity +
									ASM_AmulBdivC(	right->intensity - left->intensity,
													cbz,
													dbz
													);

//TempCode PD 12Jun96 				chop->sx = ASM_AmulBdivC(	chop->bx,
//TempCode PD 12Jun96 											screenscale,
//TempCode PD 12Jun96 											distzplane
//TempCode PD 12Jun96 											);
//TempCode PD 12Jun96 
//TempCode PD 12Jun96 				chop->sy = -ASM_AmulBdivC(	chop->by,
//TempCode PD 12Jun96 											screenscale,
//TempCode PD 12Jun96 											distzplane
//TempCode PD 12Jun96 											);

//DeadCode PD 12Jun96 				while((chop->bz&zmask)!=distzplane)
//DeadCode PD 12Jun96 				{
//DeadCode PD 12Jun96 					if(chop->bz>=distzplane)
//DeadCode PD 12Jun96 					{
//DeadCode PD 12Jun96 						temp = right;
//DeadCode PD 12Jun96 						right = chop;
//DeadCode PD 12Jun96 						chop = temp;
//DeadCode PD 12Jun96 					}
//DeadCode PD 12Jun96 					else
//DeadCode PD 12Jun96 					{
//DeadCode PD 12Jun96 						temp = left;
//DeadCode PD 12Jun96 						left = chop;
//DeadCode PD 12Jun96 						chop = temp;
//DeadCode PD 12Jun96 					}
//DeadCode PD 12Jun96 					chopvertex(*chop,*left,*right);
//DeadCode PD 12Jun96 				}

				//New vertex to add is 'chop'

				if(newvertcount>MaxIVertz)
					_Error.EmitSysErr(__FILE__":ZVERTZ buffer o'flow");

				*newpnt = AllocateVertex();

				chop->intensity=255<<12; //16;					//PD 10Jun96

				copyvertex(**newpnt,*chop);

 				//Calculate new screen coordinates

 				_matrix.body2screen(**newpnt);					//PD 25Jul96

				newpnt++;

				newvertcount++;
			}
			//else, both are -ve so do nothing
		}
		cind = nind;

		nind++;

		if(!*nind)
			nind = nvertptr;
	}

	if(newvertcount<3)	return(FALSE);

	//Copy back the new set of vertices

	for(count=newvertcount;count--;)							//PD 12Dec95
		nvertptr[count]=zvertptr[count];							//PD 12Dec95

	nvertptr[newvertcount]=NULL;

	vertexcount = newvertcount;

	VertexOFlowTest();											//PD 07Feb96

	return(TRUE);
}

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
	int		count;									//PD 11Dec95
	SWord	scalefactor;								//PD 11Dec95

	//Find the largest scale factor

	scalefactor = nvertptr[0]->scalefactor;

	for(count=1;count<vertexcount;count++)
	{
		if(nvertptr[count]->scalefactor>scalefactor)
			scalefactor = nvertptr[count]->scalefactor;
	}

	//Make sure all points are scaled the same

	for(count=vertexcount;count--;)								//PD 12Dec95
	{
		if(nvertptr[count]->scalefactor!=scalefactor)
		{
			SWord	scaledif =									//PD 12Dec95
					(SWord )(scalefactor-nvertptr[count]->scalefactor);//PD 12Dec95

			nvertptr[count]->bx >>= scaledif;
			nvertptr[count]->by >>= scaledif;
			nvertptr[count]->bz >>= scaledif;
			nvertptr[count]->scalefactor = scalefactor;
		}
	}

	distzplane = usdistzplane<<(16-scalefactor);				//PD 16May96

	zplane = _matrix.realZ(scalefactor);
	zmask = _matrix.realZmsk(scalefactor);
//DeadCode PD 12Jun96 	newscreenshift = (SWord )(24 - scalefactor);				//PD 12Dec95

	newscreenshift = scalefactor;								//PD 12Jun96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		clippoly
//Author		Paul.   
//Date			Tue 24 Oct 1995
//
//Description	Polygon screen clipping routine
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool polygon::clippoly()
{
	int		newvertcount;

	VERTEX_PTR	*cind,
				*nind,
				*newpnt;

	//Quick test to see if all points are on screen

	cind = nvertptr;

	do
	{
		if((*cind)->sy<TopY || (*cind)->sy>BotY || (*cind)->sx<LeftX || (*cind)->sx>RightX)
			break;
		cind++;
	}
	while(*cind);

	if(!*cind)	return(TRUE);

	//-----------------------------------------
	//Test against top edge of the screen first
	//-----------------------------------------

	cind = nvertptr;

	nind = nvertptr+1;

	newpnt = cvertptr;

	newvertcount=0;

	do
	{
		if((*cind)->sy>=TopY)
		{
			//This point doesn't need clipping

			*newpnt++ = *cind;

			newvertcount++;

			if((*nind)->sy<TopY)
			{
				*newpnt = AllocateVertex();
				GenericHoriClip(TopY,*cind,*nind,*newpnt++);
				newvertcount++;
			}
		}
		else
		{
			if((*nind)->sy>=TopY)
			{
				*newpnt = AllocateVertex();
				GenericHoriClip(TopY,*nind,*cind,*newpnt++);
				newvertcount++;
			}
		}

		nind++;
			
		if(!*nind) nind = nvertptr;

		cind++;
	}
	while(*cind);

	if((vertexcount=newvertcount)<3)
		return(FALSE);

	*newpnt=NULL;

	//--------------------------------------
	//Test against bottom edge of the screen
	//--------------------------------------

	cind = cvertptr;

	nind = cvertptr+1;

	newpnt = nvertptr;

	newvertcount = 0;

	do
	{
		if((*cind)->sy<=BotY)
		{
			//This point doesn't need clipping

			*newpnt++ = *cind;

			newvertcount++;

			if((*nind)->sy>BotY)
			{
				*newpnt = AllocateVertex();
				GenericHoriClip(BotY,*cind,*nind,*newpnt++);
				newvertcount++;
			}
		}
		else
		{
			if((*nind)->sy<=BotY)
			{
				*newpnt = AllocateVertex();
				GenericHoriClip(BotY,*nind,*cind,*newpnt++);
				newvertcount++;
			}
		}

		nind++;

		if(!*nind) nind = cvertptr;

		cind++;
	}
	while(*cind);

	if((vertexcount=newvertcount)<3)
		return(FALSE);

	*newpnt=NULL;

	//--------------------------------------
	//Test against left edge of the screen
	//--------------------------------------

	cind = nvertptr;

	nind = nvertptr+1;

	newpnt = cvertptr;

	newvertcount = 0;

	do
	{
		if((*cind)->sx>=LeftX)
		{
			//This point doesn't need clipping

			*newpnt++ = *cind;

			newvertcount++;

			if((*nind)->sx<LeftX)
			{
				*newpnt = AllocateVertex();
				GenericVertClip(LeftX,*cind,*nind,*newpnt++);
				newvertcount++;
			}
		}
		else
		{
			if((*nind)->sx>=LeftX)
			{
				*newpnt = AllocateVertex();
				GenericVertClip(LeftX,*nind,*cind,*newpnt++);
				newvertcount++;
			}
		}

		nind++;

		if(!*nind) nind = nvertptr;

		cind++;
	}
	while(*cind);

	if((vertexcount=newvertcount)<3)
		return(FALSE);

	*newpnt=NULL;

	//--------------------------------------
	//Test against right edge of the screen
	//--------------------------------------

	cind = cvertptr;

	nind = cvertptr+1;

	newpnt = nvertptr;

	newvertcount = 0;

	do
	{
		if((*cind)->sx<=RightX)
		{
			//This point doesn't need clipping

			*newpnt++ = *cind;

			newvertcount++;

			if((*nind)->sx>RightX)
			{
				*newpnt = AllocateVertex();
				GenericVertClip(RightX,*cind,*nind,*newpnt++);
				newvertcount++;
			}
		}
		else
		{
			if((*nind)->sx<=RightX)
			{
				*newpnt = AllocateVertex();
				GenericVertClip(RightX,*nind,*cind,*newpnt++);
				newvertcount++;
			}
		}

		nind++;

		if(!*nind) nind = cvertptr;

		cind++;
	}
	while(*cind);

	if((vertexcount=newvertcount)<3)
		return(FALSE);

	*newpnt=NULL;

	VertexOFlowTest();											//PD 07Feb96

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenericHoriClip
//Author		Paul.   
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::GenericHoriClip(SLong& yclip,VERTEX* v1,VERTEX* v2,VERTEX* out)
{
	//screen (X,Y) clip

	SLong	temp;												//PD 17Jan96

	SLong	dsy = yclip-v1->sy;									//PD 12Jun96

	//find the intersection point y==yclip on the line v1->v2

	SLong	v2sy_minus_v1sy = v2->sy-v1->sy;

	//No point of intersection if 'v2sy_minus_v1sy' == 0

	if(!v2sy_minus_v1sy)	return;

	out->sy = yclip;

	temp = (v2->sx-v1->sx);
	
//TempCode PD 12Jun96 	if(sign(temp)==sign(temp<<8))
//TempCode PD 12Jun96 	{
//TempCode PD 12Jun96 		temp = (temp<<8)/v2sy_minus_v1sy;
//TempCode PD 12Jun96 
//TempCode PD 12Jun96 		temp *= (yclip-v1->sy);
//TempCode PD 12Jun96 
//TempCode PD 12Jun96 		out->sx = v1->sx + (temp>>8);
//TempCode PD 12Jun96 	}
//TempCode PD 12Jun96 	else
//TempCode PD 12Jun96 	{
//TempCode PD 12Jun96 		temp = temp/v2sy_minus_v1sy;
//TempCode PD 12Jun96 
//TempCode PD 12Jun96 		temp *= (yclip-v1->sy);
//TempCode PD 12Jun96 
//TempCode PD 12Jun96 		out->sx = v1->sx + temp;
//TempCode PD 12Jun96 	}

	out->sx = v1->sx + ASM_AmulBdivC(	temp,					//PD 12Jun96
										dsy,
										v2sy_minus_v1sy
									);
	switch(polytype)
	{
		case GOURAUD:
		case IMAPPED_S:
		case IMAPPED_SH:

			//Intensity

			out->intensity = v1->intensity 	+					//PD 12Jun96
							 ASM_AmulBdivC(	v2->intensity-v1->intensity,
											dsy,
											v2sy_minus_v1sy
											);
			if(polytype==GOURAUD)
				break;

		case OMAPPED:											//PD 18Jan96
		case OMAPPED_M:											//PD 18Jan96
		case IMAPPED:
		case IMAPPED_M:
		case IMAPPED_B:

			//Image (X,Y)

			if(subdivide)
 				CalcNewIXY(v1,v2,out);								//PD 30Jan96
			else
			{
				out->ix = v1->ix +								//PD 12Jun96
						  ASM_AmulBdivC(v2->ix-v1->ix,
										dsy,
										v2sy_minus_v1sy
										);

				out->iy = v1->iy +								//PD 12Jun96
						  ASM_AmulBdivC(v2->iy-v1->iy,
										dsy,
										v2sy_minus_v1sy
										);
			}
		default:
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenericVertClip
//Author		Paul.   
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::GenericVertClip(SLong& xclip,VERTEX* v1,VERTEX* v2,VERTEX* out)
{
	//screen (X,Y) clip

 	//find the intersection point x==xclip on the line v1->v2

	SLong	v2sx_minus_v1sx = v2->sx-v1->sx;

	SLong	temp;

	SLong	dsx = xclip-v1->sx;									//PD 12Jun96

	//No point of intersection if 'v2sx_minus_v1sx' == 0

	if(!v2sx_minus_v1sx)	return;

	out->sx = xclip;

	temp = (v2->sy-v1->sy);

//Old_Code PD 12Jun96 	if(sign(temp)==sign(temp<<8))
//Old_Code PD 12Jun96 	{
//Old_Code PD 12Jun96 		temp = (temp<<8)/v2sx_minus_v1sx;
//Old_Code PD 12Jun96 
//Old_Code PD 12Jun96 		temp *= (xclip-v1->sx);
//Old_Code PD 12Jun96 
//Old_Code PD 12Jun96 		out->sy = v1->sy + (temp>>8);
//Old_Code PD 12Jun96 	}
//Old_Code PD 12Jun96 	else
//Old_Code PD 12Jun96 	{
//Old_Code PD 12Jun96 		temp /= v2sx_minus_v1sx;
//Old_Code PD 12Jun96 
//Old_Code PD 12Jun96 		temp *= (xclip-v1->sx);
//Old_Code PD 12Jun96 
//Old_Code PD 12Jun96 		out->sy = v1->sy + temp;
//Old_Code PD 12Jun96 	}

	out->sy = v1->sy + ASM_AmulBdivC(	temp,					//PD 12Jun96
										dsx,
										v2sx_minus_v1sx
									);

	switch(polytype)
	{
		case GOURAUD:
		case IMAPPED_S:
		case IMAPPED_SH:

			//Intensity

//DeadCode PD 12Jun96 			temp = (v2->intensity-v1->intensity)/v2sx_minus_v1sx;
//DeadCode PD 12Jun96 
//DeadCode PD 12Jun96 			temp *= (xclip-v1->sx);

			out->intensity = v1->intensity +
							 ASM_AmulBdivC(	v2->intensity-v1->intensity,
											dsx,
											v2sx_minus_v1sx
											);

			if(polytype==GOURAUD)
				break;

		case OMAPPED:											//PD 18Jan96
		case OMAPPED_M:											//PD 18Jan96
		case IMAPPED:
		case IMAPPED_M:
		case IMAPPED_B:

			//Image (X,Y)

			if(subdivide)
				CalcNewIXY(v1,v2,out);
			else
			{
				out->ix = v1->ix + ASM_AmulBdivC(v2->ix-v1->ix,	//PD 12Jun96
												dsx,
												v2sx_minus_v1sx
												);

				out->iy = v1->iy + ASM_AmulBdivC(v2->iy-v1->iy,	//PD 12Jun96
												dsx,
												v2sx_minus_v1sx
												);
			}
		default:
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//						PLAIN MAPPING POLY DRAW ROUTINE
//
////////////////////////////////////////////////////////////////////////////////

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
	VERTEX_PTR	*cindrp,*cindlp;								//PD 29Jan96
	VERTEX_PTR	*nindrp,*nindlp;								//PD 29Jan96

	LogicalPtr	scradr;

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;

	SLong	ld_sx,rd_sx;

	SLong	last_leftsx,last_rightsx;							//PD 12Apr96

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
				if(!*nindlp) nindlp += vertexcount;				//PD 16Feb96
				break;
		}
		leftvertex.sx = (*cindlp)->sx<<16;

		ld_sy = (*nindlp)->sy-(*cindlp)->sy;
	}
	while(!ld_sy);

	ld_sx = (((*nindlp)->sx-(*cindlp)->sx)<<16)/ld_sy;

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
		rightvertex.sx = (*cindrp)->sx<<16;

		rd_sy = (*nindrp)->sy-(*cindrp)->sy;
	}
	while(!rd_sy);

	rd_sx = (((*nindrp)->sx-(*cindrp)->sx)<<16)/rd_sy;

	last_leftsx = leftvertex.sx;								//PD 12Apr96
	last_rightsx= rightvertex.sx;								//PD 12Apr96

	//Now start the real DDA stuff

	while(hll.length--)
	{
		//Do a single scan line

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		//index left and right by left and right delta sx

		leftvertex.sx += ld_sx;
		rightvertex.sx += rd_sx;

		if (leftvertex.sx>last_rightsx)							//PD 12Apr96
			leftvertex.sx = last_rightsx;						//PD 12Apr96

		if (rightvertex.sx<last_leftsx)							//PD 12Apr96
			rightvertex.sx = last_leftsx;						//PD 12Apr96

		last_leftsx = leftvertex.sx;							//PD 12Apr96
		last_rightsx= rightvertex.sx;							//PD 12Apr96

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
				leftvertex.sx = (*cindlp)->sx<<16;

				ld_sy = (*nindlp)->sy-(*cindlp)->sy;
			}
			while(!ld_sy);

			ld_sx = (((*nindlp)->sx-(*cindlp)->sx)<<16)/ld_sy;
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
				rightvertex.sx = (*cindrp)->sx<<16;

				rd_sy = (*nindrp)->sy-(*cindrp)->sy;
			}
			while(!rd_sy);

			rd_sx = (((*nindrp)->sx-(*cindrp)->sx)<<16)/rd_sy;
		}
	
		scradr += currscreen->BytesPerScanLine;
	}
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
	VERTEX_PTR	*cindrp,*cindlp;								//PD 29Jan96
	VERTEX_PTR	*nindrp,*nindlp;								//PD 29Jan96

	LogicalPtr	scradr;											//JIM 12Dec95

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;

	SLong	ld_sx,rd_sx;

	SLong	ld_in,rd_in;

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
		leftvertex.sx = (*cindlp)->sx<<16;
		leftvertex.intensity = (*cindlp)->intensity;

		ld_sy = (*nindlp)->sy-(*cindlp)->sy;
	}
	while(!ld_sy);

	ld_sx = (((*nindlp)->sx-(*cindlp)->sx)<<16)/ld_sy;
	ld_in = ((*nindlp)->intensity-(*cindlp)->intensity)/ld_sy;

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
		rightvertex.sx = (*cindrp)->sx<<16;
		rightvertex.intensity = (*cindrp)->intensity;		//PD 31Oct95

		rd_sy = (*nindrp)->sy-(*cindrp)->sy;
	}
	while(!rd_sy);

	rd_sx = (((*nindrp)->sx-(*cindrp)->sx)<<16)/rd_sy;
	rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;

	//Now start the real DDA stuff

	leftvertex.sy = hll.starty;									//PD 10Jun96

	while(hll.length--)
	{
		//Do a single scan line

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		//index left and right by left and right delta sx

		leftvertex.sx += ld_sx;
		rightvertex.sx += rd_sx;

		leftvertex.intensity += ld_in;
		rightvertex.intensity += rd_in;

		leftvertex.sy++;										//PD 10Jun96

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
				leftvertex.sx = (*cindlp)->sx<<16;
				leftvertex.intensity = (*cindlp)->intensity;

				ld_sy = (*nindlp)->sy-(*cindlp)->sy;
			}
			while(!ld_sy);

			ld_sx = (((*nindlp)->sx-(*cindlp)->sx)<<16)/ld_sy;
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
				rightvertex.sx = (*cindrp)->sx<<16;
				rightvertex.intensity = (*cindrp)->intensity;

				rd_sy = (*nindrp)->sy-(*cindrp)->sy;
			}
			while(!rd_sy);

			rd_sx = (((*nindrp)->sx-(*cindrp)->sx)<<16)/rd_sy;
			rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;
		}
	
		scradr += currscreen->BytesPerScanLine;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//						IMAGE MAPPING POLY DRAW ROUTINE
//
////////////////////////////////////////////////////////////////////////////////

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
void polygon::ipolyscancnvrt(HLINELIST &hll)
{
	VERTEX_PTR	*cindrp,*cindlp,
				*nindrp,*nindlp;

	LogicalPtr	scradr;

	VERTEX	leftvertex,
			rightvertex;

	SLong	ld_sy,rd_sy;

	SLong	ld_sx,rd_sx;

	SLong	ld_ix,rd_ix;

	SLong	ld_iy,rd_iy;

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
		leftvertex.sx = (*cindlp)->sx<<16;
		leftvertex.ix = (*cindlp)->ix;
		leftvertex.iy = (*cindlp)->iy;

		ld_sy = (*nindlp)->sy-(*cindlp)->sy;
	}
	while(!ld_sy);

	ld_sx = (((*nindlp)->sx-(*cindlp)->sx)<<16)/ld_sy;
	ld_ix = ((*nindlp)->ix-(*cindlp)->ix)/ld_sy;
	ld_iy = ((*nindlp)->iy-(*cindlp)->iy)/ld_sy;

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
		rightvertex.sx = (*cindrp)->sx<<16;
		rightvertex.ix = (*cindrp)->ix;
		rightvertex.iy = (*cindrp)->iy;

		rd_sy = (*nindrp)->sy-(*cindrp)->sy;
	}
	while(!rd_sy);

	rd_sx = (((*nindrp)->sx-(*cindrp)->sx)<<16)/rd_sy;
	rd_ix = ((*nindrp)->ix-(*cindrp)->ix)/rd_sy;
	rd_iy = ((*nindrp)->iy-(*cindrp)->iy)/rd_sy;

	//Now start the real DDA stuff
	int	bd_sy=ld_sy;
	if (bd_sy>rd_sy)
		bd_sy=rd_sy;
	if (bd_sy>hll.length)
		bd_sy=hll.length;
	if (hll.length)
	do
	{
		hll.length-=bd_sy;
		if (ld_sx || rd_sx || ld_ix || rd_ix || (ld_iy!=rd_iy))
			while (bd_sy)
			{
				ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

				//index left and right by left and right delta sx

				leftvertex.sx += ld_sx;
				rightvertex.sx += rd_sx;

				leftvertex.ix += ld_ix;
				leftvertex.iy += ld_iy;

				rightvertex.ix += rd_ix;
				rightvertex.iy += rd_iy;
				scradr += currscreen->BytesPerScanLine;
				ld_sy--;
				rd_sy--;
				bd_sy--;
			}
		else
			while (bd_sy)
			{
				ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

				//index left and right by left and right delta sx

//DeadCode JIM 09Aug96 				leftvertex.sx += ld_sx;
//DeadCode JIM 09Aug96 				rightvertex.sx += rd_sx;

//DeadCode JIM 09Aug96 				leftvertex.ix += ld_ix;
//DeadCode JIM 09Aug96 				rightvertex.ix += rd_ix;
				leftvertex.iy =	//+= ld_iy;
					rightvertex.iy += rd_iy;
				scradr += currscreen->BytesPerScanLine;
				ld_sy--;
				rd_sy--;
				bd_sy--;
			}

		if (hll.length>0)
		{	//one of rd or ld is zero
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
					leftvertex.sx = (*cindlp)->sx<<16;
					leftvertex.ix = (*cindlp)->ix;
					leftvertex.iy = (*cindlp)->iy;

					ld_sy = (*nindlp)->sy-(*cindlp)->sy;
				}
				while(!ld_sy);
				ld_sx = (((*nindlp)->sx-(*cindlp)->sx)<<16)/ld_sy;
				ld_ix = ((*nindlp)->ix-(*cindlp)->ix)/ld_sy;
				ld_iy = ((*nindlp)->iy-(*cindlp)->iy)/ld_sy;
			}

//DeadCode JIM 09Aug96 			rd_sy--;

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
					rightvertex.sx = (*cindrp)->sx<<16;
					rightvertex.ix = (*cindrp)->ix;
					rightvertex.iy = (*cindrp)->iy;

					rd_sy = (*nindrp)->sy-(*cindrp)->sy;
				}
				while(!rd_sy);

				rd_sx = (((*nindrp)->sx-(*cindrp)->sx)<<16)/rd_sy;
				rd_ix = ((*nindrp)->ix-(*cindrp)->ix)/rd_sy;
				rd_iy = ((*nindrp)->iy-(*cindrp)->iy)/rd_sy;
			}
			bd_sy=ld_sy;
			if (bd_sy>rd_sy)
				bd_sy=rd_sy;
			if (bd_sy>hll.length)
				bd_sy=hll.length;
		}
	}
	while (hll.length>0);


//DeadCode JIM 09Aug96 	while(hll.length--)
//DeadCode JIM 09Aug96 	{
//DeadCode JIM 09Aug96 		//Do a single scan line
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 		//index left and right by left and right delta sx
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 		leftvertex.sx += ld_sx;
//DeadCode JIM 09Aug96 		rightvertex.sx += rd_sx;
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 		leftvertex.ix += ld_ix;
//DeadCode JIM 09Aug96 		leftvertex.iy += ld_iy;
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 		rightvertex.ix += rd_ix;
//DeadCode JIM 09Aug96 		rightvertex.iy += rd_iy;
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 		ld_sy--;
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 		if(!ld_sy)
//DeadCode JIM 09Aug96 		{
//DeadCode JIM 09Aug96 			//get next left index
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 			do
//DeadCode JIM 09Aug96 			{
//DeadCode JIM 09Aug96 				cindlp = nindlp;
//DeadCode JIM 09Aug96 				switch(hll.led)
//DeadCode JIM 09Aug96 				{
//DeadCode JIM 09Aug96 					case FORWARDS:
//DeadCode JIM 09Aug96 						nindlp++;
//DeadCode JIM 09Aug96 						if(!*nindlp) nindlp = nvertptr;
//DeadCode JIM 09Aug96 						break;
//DeadCode JIM 09Aug96 					case BACKWARDS:
//DeadCode JIM 09Aug96 						nindlp--;
//DeadCode JIM 09Aug96 						if(!*nindlp) nindlp += vertexcount;
//DeadCode JIM 09Aug96 						break;
//DeadCode JIM 09Aug96 				}
//DeadCode JIM 09Aug96 				leftvertex.sx = (*cindlp)->sx<<16;
//DeadCode JIM 09Aug96 				leftvertex.ix = (*cindlp)->ix;
//DeadCode JIM 09Aug96 				leftvertex.iy = (*cindlp)->iy;
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 				ld_sy = (*nindlp)->sy-(*cindlp)->sy;
//DeadCode JIM 09Aug96 			}
//DeadCode JIM 09Aug96 			while(!ld_sy);
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 			ld_sx = (((*nindlp)->sx-(*cindlp)->sx)<<16)/ld_sy;
//DeadCode JIM 09Aug96 			ld_ix = ((*nindlp)->ix-(*cindlp)->ix)/ld_sy;
//DeadCode JIM 09Aug96 			ld_iy = ((*nindlp)->iy-(*cindlp)->iy)/ld_sy;
//DeadCode JIM 09Aug96 		}
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 		rd_sy--;
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 		if(!rd_sy)
//DeadCode JIM 09Aug96 		{
//DeadCode JIM 09Aug96 			//get next right index
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 			do
//DeadCode JIM 09Aug96 			{
//DeadCode JIM 09Aug96 				cindrp = nindrp;
//DeadCode JIM 09Aug96 				switch(hll.led)
//DeadCode JIM 09Aug96 				{
//DeadCode JIM 09Aug96 					case BACKWARDS:
//DeadCode JIM 09Aug96 						nindrp++;
//DeadCode JIM 09Aug96 						if(!*nindrp) nindrp = nvertptr;
//DeadCode JIM 09Aug96 						break;
//DeadCode JIM 09Aug96 					case FORWARDS:
//DeadCode JIM 09Aug96 						nindrp--;
//DeadCode JIM 09Aug96 						if(!*nindrp) nindrp += vertexcount;
//DeadCode JIM 09Aug96 						break;
//DeadCode JIM 09Aug96 				}
//DeadCode JIM 09Aug96 				rightvertex.sx = (*cindrp)->sx<<16;
//DeadCode JIM 09Aug96 				rightvertex.ix = (*cindrp)->ix;
//DeadCode JIM 09Aug96 				rightvertex.iy = (*cindrp)->iy;
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 				rd_sy = (*nindrp)->sy-(*cindrp)->sy;
//DeadCode JIM 09Aug96 			}
//DeadCode JIM 09Aug96 			while(!rd_sy);
//DeadCode JIM 09Aug96 
//DeadCode JIM 09Aug96 			rd_sx = (((*nindrp)->sx-(*cindrp)->sx)<<16)/rd_sy;
//DeadCode JIM 09Aug96 			rd_ix = ((*nindrp)->ix-(*cindrp)->ix)/rd_sy;
//DeadCode JIM 09Aug96 			rd_iy = ((*nindrp)->iy-(*cindrp)->iy)/rd_sy;
//DeadCode JIM 09Aug96 		}
//DeadCode JIM 09Aug96 	
//DeadCode JIM 09Aug96 		scradr += currscreen->BytesPerScanLine;
//DeadCode JIM 09Aug96 	}
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
	VERTEX_PTR	*cindrp,*cindlp;								//PD 29Jan96
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
		leftvertex.sx = (*cindlp)->sx<<16;
		leftvertex.ix = (*cindlp)->ix;
		leftvertex.iy = (*cindlp)->iy;
		leftvertex.intensity = (*cindlp)->intensity;

		ld_sy = (*nindlp)->sy-(*cindlp)->sy;
	}
	while(!ld_sy);

	ld_sx = (((*nindlp)->sx-(*cindlp)->sx)<<16)/ld_sy;
	ld_ix = ((*nindlp)->ix-(*cindlp)->ix)/ld_sy;
	ld_iy = ((*nindlp)->iy-(*cindlp)->iy)/ld_sy;
	ld_in = ((*nindlp)->intensity-(*cindlp)->intensity)/ld_sy;

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
		rightvertex.sx = (*cindrp)->sx<<16;
		rightvertex.ix = (*cindrp)->ix;
		rightvertex.iy = (*cindrp)->iy;
		rightvertex.intensity = (*cindrp)->intensity;		//PD 31Oct95

		rd_sy = (*nindrp)->sy-(*cindrp)->sy;
	}
	while(!rd_sy);

	rd_sx = (((*nindrp)->sx-(*cindrp)->sx)<<16)/rd_sy;
	rd_ix = ((*nindrp)->ix-(*cindrp)->ix)/rd_sy;
	rd_iy = ((*nindrp)->iy-(*cindrp)->iy)/rd_sy;
	rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;

	//Now start the real DDA stuff

	leftvertex.sy = hll.starty;									//PD 16May96

	while(hll.length--)
	{
		//Do a single scan line

		ASM_Call(horilinertn,scradr,leftvertex,rightvertex);	//PD 03Jan96

		//index left and right by left and right delta sx

		leftvertex.sx += ld_sx;
		rightvertex.sx += rd_sx;

		leftvertex.ix += ld_ix;
		leftvertex.iy += ld_iy;

		leftvertex.sy++;										//PD 16May96

		rightvertex.ix += rd_ix;
		rightvertex.iy += rd_iy;

		leftvertex.intensity += ld_in;
		rightvertex.intensity += rd_in;

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
				leftvertex.sx = (*cindlp)->sx<<16;
				leftvertex.ix = (*cindlp)->ix;
				leftvertex.iy = (*cindlp)->iy;
				leftvertex.intensity = (*cindlp)->intensity;

				ld_sy = (*nindlp)->sy-(*cindlp)->sy;
			}
			while(!ld_sy);

			ld_sx = (((*nindlp)->sx-(*cindlp)->sx)<<16)/ld_sy;
			ld_ix = ((*nindlp)->ix-(*cindlp)->ix)/ld_sy;
			ld_iy = ((*nindlp)->iy-(*cindlp)->iy)/ld_sy;
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
				rightvertex.sx = (*cindrp)->sx<<16;
				rightvertex.ix = (*cindrp)->ix;
				rightvertex.iy = (*cindrp)->iy;
				rightvertex.intensity = (*cindrp)->intensity;

				rd_sy = (*nindrp)->sy-(*cindrp)->sy;
			}
			while(!rd_sy);

			rd_sx = (((*nindrp)->sx-(*cindrp)->sx)<<16)/rd_sy;
			rd_ix = (((*nindrp)->ix-(*cindrp)->ix))/rd_sy;
			rd_iy = (((*nindrp)->iy-(*cindrp)->iy))/rd_sy;
			rd_in = ((*nindrp)->intensity-(*cindrp)->intensity)/rd_sy;
		}
	
		scradr += currscreen->BytesPerScanLine;
	}
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
//Procedure		polygon
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
//TempCode ARM 04Jun96 polygon::polygon(PolygonP p)
//TempCode ARM 04Jun96 {
//TempCode ARM 04Jun96 	vertex_end = &vertex_list[MaxIVertz*2];
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	int	j;
//TempCode ARM 04Jun96 	for(j=MaxIVertz+2;j--;)
//TempCode ARM 04Jun96 	{
//TempCode ARM 04Jun96 		buffered_nvertptr[j] = NULL;
//TempCode ARM 04Jun96 		buffered_cvertptr[j] = NULL;
//TempCode ARM 04Jun96 	}
//TempCode ARM 04Jun96 	nvertptr = &buffered_nvertptr[1];
//TempCode ARM 04Jun96 	cvertptr =
//TempCode ARM 04Jun96 		zvertptr = &buffered_cvertptr[1];
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	setpolyscrn(p->currscreen);
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	(void )SetCrossProduct(p->crossprod);
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	switch(p->polytype)
//TempCode ARM 04Jun96 	{
//TempCode ARM 04Jun96 		case PLAIN:
//TempCode ARM 04Jun96 			return;
//TempCode ARM 04Jun96 		case GOURAUD:
//TempCode ARM 04Jun96 			createpoly(p->polycolour,p->polyrange);
//TempCode ARM 04Jun96 			break;
//TempCode ARM 04Jun96 		case IMAPPED:
//TempCode ARM 04Jun96 		case IMAPPED_M:
//TempCode ARM 04Jun96 			createpoly(p->polyimage);
//TempCode ARM 04Jun96 			break;
//TempCode ARM 04Jun96 		case IMAPPED_S:
//TempCode ARM 04Jun96 			createpoly(p->polyimage,p->polycolour);
//TempCode ARM 04Jun96 			break;
//TempCode ARM 04Jun96 		case IMAPPED_B:
//TempCode ARM 04Jun96 			createpoly(p->polyimage,p->polycolour,p->polyrange);
//TempCode ARM 04Jun96 			break;
//TempCode ARM 04Jun96 		case IMAPPED_SH:
//TempCode ARM 04Jun96 			createpoly(p->polyimage,p->polycolour,p->polyrange);
//TempCode ARM 04Jun96 			break;
//TempCode ARM 04Jun96 		case OMAPPED:
//TempCode ARM 04Jun96 		case OMAPPED_M:
//TempCode ARM 04Jun96 			createpoly(p->polyoimage);
//TempCode ARM 04Jun96 			break;
//TempCode ARM 04Jun96 	}
//TempCode ARM 04Jun96 	subdivide = p->subdivide;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	subdivlevel = p->subdivlevel+1;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	if(subdivlevel > __MAX_SUBDIVIDE__)
//TempCode ARM 04Jun96 		subdivide = FALSE;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubDivide
//Author		Paul.   
//Date			Tue 30 Jan 1996
//
//Description	Subdivides a polygon using body Z. The original polygon is
//				left as the most distant poly segment and a new polygon
//				is created using the nearest segment.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::SubDivide()
{
//TempCode ARM 04Jun96 	PolygonP newpoly = new Polygon(this);
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	//find the most distant and nearest vertices in the current polygon
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	VERTEX_PTR *cindp,*nindp,*distp,*nearp;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	VERTEX_PTR	new1,new2;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	new1 = AllocateVertex();
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	new2 = AllocateVertex();
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	distp =
//TempCode ARM 04Jun96 		nearp = nvertptr;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	cindp = distp+1;
//TempCode ARM 04Jun96 	
//TempCode ARM 04Jun96 	while(*cindp)
//TempCode ARM 04Jun96 	{
//TempCode ARM 04Jun96 		if((*cindp)->bz>(*distp)->bz)
//TempCode ARM 04Jun96 			distp = cindp;
//TempCode ARM 04Jun96 		else
//TempCode ARM 04Jun96 			if((*cindp)->bz<(*nearp)->bz)
//TempCode ARM 04Jun96 				nearp = cindp;
//TempCode ARM 04Jun96 		cindp++;
//TempCode ARM 04Jun96 	}
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	if((*distp)->bz==(*nearp)->bz)
//TempCode ARM 04Jun96 		return;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	//split in ratio 25% : 75% to account for perspective?
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	SLong	mid_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	mid_bz = (*distp)->bz - (*nearp)->bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	mid_bz = (*nearp)->bz + (mid_bz>>2);
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	//generate two new verties at the 'mid_bz' boundary
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	int	i;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	for (nindp=nvertptr,i=vertexcount;i--;)
//TempCode ARM 04Jun96 	{
//TempCode ARM 04Jun96 		cindp = nindp;
//TempCode ARM 04Jun96 		nindp++;
//TempCode ARM 04Jun96 		if(!*nindp) nindp = nvertptr;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 		if((*cindp)->bz>mid_bz && (*nindp)->bz<mid_bz)
//TempCode ARM 04Jun96 		{
//TempCode ARM 04Jun96 			SLong	delta_bz,temp;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	 		//generate vertex 'new1'
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 			new1->scalefactor = (*cindp)->scalefactor;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 			new1->bz = mid_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 			temp = mid_bz - (*cindp)->bz;
//TempCode ARM 04Jun96 			delta_bz = (*nindp)->bz - (*cindp)->bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 			new1->bx = (*nindp)->bx - (*cindp)->bx;
//TempCode ARM 04Jun96 			new1->bx = (*cindp)->bx + (new1->bx * temp)/delta_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 			new1->by = (*nindp)->by - (*cindp)->by;
//TempCode ARM 04Jun96 			new1->by = (*cindp)->by + (new1->by * temp)/delta_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 			new1->ix = (*nindp)->ix - (*cindp)->ix;
//TempCode ARM 04Jun96 			new1->ix = (*cindp)->ix + (new1->ix * temp)/delta_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 			new1->iy = (*nindp)->iy - (*cindp)->iy;
//TempCode ARM 04Jun96 			new1->iy = (*cindp)->iy + (new1->iy * temp)/delta_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 			_matrix.body2screen(currscreen,*new1);
//TempCode ARM 04Jun96 		}
//TempCode ARM 04Jun96 		else
//TempCode ARM 04Jun96 		{
//TempCode ARM 04Jun96 			if((*cindp)->bz<mid_bz && (*nindp)->bz>mid_bz)
//TempCode ARM 04Jun96 			{
//TempCode ARM 04Jun96 				SLong	delta_bz,temp;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	 			//generate vertex 'new2'
//TempCode ARM 04Jun96 				new2->scalefactor = (*cindp)->scalefactor;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 				new2->bz = mid_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 				temp = mid_bz - (*nindp)->bz;
//TempCode ARM 04Jun96 				delta_bz = (*cindp)->bz - (*nindp)->bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 				new2->bx = (*cindp)->bx - (*nindp)->bx;
//TempCode ARM 04Jun96 				new2->bx = (*nindp)->bx + (new2->bx * temp)/delta_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 				new2->by = (*cindp)->by - (*nindp)->by;
//TempCode ARM 04Jun96 				new2->by = (*nindp)->by + (new2->by * temp)/delta_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 				new2->ix = (*cindp)->ix - (*nindp)->ix;
//TempCode ARM 04Jun96 				new2->ix = (*nindp)->ix + (new2->ix * temp)/delta_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 				new2->iy = (*cindp)->iy - (*nindp)->iy;
//TempCode ARM 04Jun96 				new2->iy = (*nindp)->iy + (new2->iy * temp)/delta_bz;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 				_matrix.body2screen(currscreen,*new2);
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 			}
//TempCode ARM 04Jun96 		}
//TempCode ARM 04Jun96 	}
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	//two new vertices have been created along the mid_bz boundary
//TempCode ARM 04Jun96 	//line. now, create the two new polygons.
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	for(nindp=nvertptr,i=vertexcount;i--;)
//TempCode ARM 04Jun96 	{
//TempCode ARM 04Jun96 		cindp = nindp;
//TempCode ARM 04Jun96 		nindp++;
//TempCode ARM 04Jun96 		if(!*nindp) nindp = nvertptr;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 		if((*cindp)->bz<=mid_bz)
//TempCode ARM 04Jun96 		{
//TempCode ARM 04Jun96 			//add this vertex to the new polygon
//TempCode ARM 04Jun96 			newpoly->createvert(**cindp);
//TempCode ARM 04Jun96 		}
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 		if((*cindp)->bz>mid_bz && (*nindp)->bz<=mid_bz)
//TempCode ARM 04Jun96 		{
//TempCode ARM 04Jun96 			//add vertex new1 to the new polygon
//TempCode ARM 04Jun96 			newpoly->createvert(*new1);	
//TempCode ARM 04Jun96 		}
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 		if((*cindp)->bz<=mid_bz && (*nindp)->bz>mid_bz)
//TempCode ARM 04Jun96 		{
//TempCode ARM 04Jun96 			//add vertex new2 to the new polygon
//TempCode ARM 04Jun96 			newpoly->createvert(*new2);	
//TempCode ARM 04Jun96 		}
//TempCode ARM 04Jun96 	}
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	newpoly->drawpoly();
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	delete(newpoly);
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	//remove vertices from the old polygon
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	int	newvertcount=0;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	VERTEX_PTR *newpnt;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	newpnt = zvertptr;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	for(nindp=nvertptr,i=vertexcount;i--;)
//TempCode ARM 04Jun96 	{
//TempCode ARM 04Jun96 		cindp = nindp;
//TempCode ARM 04Jun96 		nindp++;
//TempCode ARM 04Jun96 		if(!*nindp) nindp = nvertptr;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 		if((*cindp)->bz>=mid_bz)
//TempCode ARM 04Jun96 		{
//TempCode ARM 04Jun96 			//add this vertex to the new polygon
//TempCode ARM 04Jun96 			*newpnt++=*cindp;
//TempCode ARM 04Jun96 			newvertcount++;
//TempCode ARM 04Jun96 		}
//TempCode ARM 04Jun96 		
//TempCode ARM 04Jun96 		if((*cindp)->bz>mid_bz && (*nindp)->bz<=mid_bz)
//TempCode ARM 04Jun96 		{
//TempCode ARM 04Jun96 			//add vertex new1 to the new polygon
//TempCode ARM 04Jun96 			*newpnt++ = new1;	
//TempCode ARM 04Jun96 			newvertcount++;
//TempCode ARM 04Jun96 		}
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 		if((*cindp)->bz<=mid_bz && (*nindp)->bz>mid_bz)
//TempCode ARM 04Jun96 		{
//TempCode ARM 04Jun96 			//add vertex new2 to the new polygon
//TempCode ARM 04Jun96 			*newpnt++ = new2;	
//TempCode ARM 04Jun96 			newvertcount++;
//TempCode ARM 04Jun96 		}
//TempCode ARM 04Jun96 	}
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	cindp = zvertptr;
//TempCode ARM 04Jun96 	newpnt = nvertptr;
//TempCode ARM 04Jun96 
//TempCode ARM 04Jun96 	for(vertexcount=newvertcount;newvertcount--;)
//TempCode ARM 04Jun96 	{
//TempCode ARM 04Jun96 		*newpnt++ = *cindp++;
//TempCode ARM 04Jun96 	}
//TempCode ARM 04Jun96 	*newpnt = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcNewIXY
//Author		Paul.   
//Date			Tue 30 Jan 1996
//
//Description	Binary chops to generate new image mapping coordinates
//				for a screen clipped pair of vertices.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::CalcNewIXY(VERTEX* v1,VERTEX* v2,VERTEX* out)
{
	VERTEX	av,bv,xv;

	VERTEX_PTR	temp,
				lv = &av,
				rv = &bv,
				cv = &xv;

	SLong		lastchopval;

	copyvertex(*lv,*v1);
	copyvertex(*rv,*v2);

	SLong dsx = lv->sx - rv->sx;
	SLong dsy = lv->sy - rv->sy;

	if(dsx<0)	dsx = -dsx;

	if(dsy<0)	dsy = -dsy;

	if(dsx>dsy)
	{
		if(lv->sx>rv->sx)
		{
			temp=rv;rv=lv;lv=temp;
		}
		chopvertex(*cv,*lv,*rv);

		_matrix.body2screen(*cv);								//PD 25Jul96

		lastchopval = cv->sx;

		while(cv->sx!=out->sx)
		{
			if(cv->sx>=out->sx)
			{
				temp=rv;rv=cv;cv=temp;
			}
			else
			{
				temp=lv;lv=cv;cv=temp;
			}
			chopvertex(*cv,*lv,*rv);

			_matrix.body2screen(*cv);							//PD 25Jul96

			if(cv->sx==lastchopval)	break;

			lastchopval = cv->sx;
		}
	}
	else
	{
		if(lv->sy>rv->sy)
		{
			temp=rv;rv=lv;lv=temp;
		}
		chopvertex(*cv,*lv,*rv);
		
		_matrix.body2screen(*cv);								//PD 25Jul96

		lastchopval = cv->sy;

		while(cv->sy!=out->sy)
		{
			if(cv->sy>=out->sy)
			{
				temp=rv;rv=cv;cv=temp;
			}
			else
			{
				temp=lv;lv=cv;cv=temp;
			}
			chopvertex(*cv,*lv,*rv);
			
			_matrix.body2screen(*cv);							//PD 25Jul96

			if(cv->sy==lastchopval)	break;

			lastchopval = cv->sy;
		}
	}
	out->bx = cv->bx;
	out->by = cv->by;
	out->bz = cv->bz;
	out->ix = cv->ix;
	out->iy = cv->iy;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScaleImage
//Author		Paul.   
//Date			Wed 14 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode PD 14Feb96 void polygon::ScaleImage(ImageMapNumber image,SWord srcx,SWord srcy,SWord srcwh,SWord dstwh)
//DeadCode PD 14Feb96 {
//DeadCode PD 14Feb96 	ImageMapDescPtr ip = Image_Map.GetImageMapPtr(image);
//DeadCode PD 14Feb96 
//DeadCode PD 14Feb96 	if(srcwh>=dstwh)
//DeadCode PD 14Feb96 		_Error.EmitSysErr(__FILE__"Scale image is designed to scale up ONLY!");
//DeadCode PD 14Feb96 
//DeadCode PD 14Feb96 	SLong	image_width = (0x00000001<<ip->width)-1;
//DeadCode PD 14Feb96 
//DeadCode PD 14Feb96 	UByteP	sourcep = &(ip->data) + srcy*image_width + srcx;
//DeadCode PD 14Feb96 
//DeadCode PD 14Feb96 	UByteP  destinationp = new UByte[dstwh*dstwh];
//DeadCode PD 14Feb96 
//DeadCode PD 14Feb96 
//DeadCode PD 14Feb96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateYList
//Author		Paul.   
//Date			Fri 16 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::AllocateYList(Window *win)
{
	if(!polyclip)
		polyclip = new YClipper[win->PhysicalWidth];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateYList
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool polygon::UpdateYList(ANGLES hdg,ANGLES pitch,ANGLES roll)
{
	if(polyclip)
	{
		if(hdg==lasthdg && pitch==lastpitch && roll==lastroll)
			return(FALSE);
	}
	else
	{
		AllocateYList(currscreen);
	}
	lasthdg = hdg; lastpitch = pitch; lastroll = roll;
	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillYList
//LastModified:	PD 14Jun96
//Author		Paul.   
//Date			Fri 16 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::FillYList()
{
	LogicalPtr	top,bot;

	//Point 'top' to the top left pixel on screen and
	// 'bot' to the bottom left pixel on screen

	SLong	offset = currscreen->PhysicalMinX + (currscreen->PhysicalMinY * currscreen->BytesPerScanLine);

	top = currscreen->logicalscreenptr + offset;

	bot = top + ((currscreen->PhysicalHeight-1) * currscreen->BytesPerScanLine);

	SLong	column;
	SLong	ymin,ymax,yclip;

	for(column=0;column<currscreen->PhysicalWidth;column++,top++,bot++)
	{
		if ((column&0x03)==0)									//PD 28Jun96
		{														//PD 14Jun96
			//Top down scan

			ymin = currscreen->PhysicalMinY;
			yclip= ymin + currscreen->PhysicalHeight;			//PD 28Jun96

			{
				LogicalPtr	topscan = top;

				while(*topscan==(UByte )ARTWORKMASK)
				{
					topscan += currscreen->BytesPerScanLine;
					ymin++;
					if (ymin>=yclip) break;						//PD 28Jun96
				}
			}

			//Bottom up scan

			ymax = yclip;
			yclip= ymin;										//PD 28Jun96

			{
				LogicalPtr	botscan = bot;
			
				while(*botscan==(UByte )ARTWORKMASK)
				{
					botscan -= currscreen->BytesPerScanLine;
					ymax--;
					if (ymax<=yclip) break;						//PD 28Jun96
				}
			}
		}														//PD 14Jun96

		polyclip[column].ymin = ymin;
		polyclip[column].ymax = ymax;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PolyHidden
//Author		Paul.   
//Date			Fri 16 Feb 1996
//
//Description	Test to see if the current polygon is obscured by the poly
//				cockpit.
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool polygon::PolyHidden()
{
	if(!realpolyclip)
		return(FALSE);

	if(polycolour == ARTWORKMASK && polytype == PLAIN)
		return(FALSE);

	VERTEX_PTR	*cind,*nind;

	//Test for clipped against bottom of the visible area

	Bool isclipped = TRUE;

	cind = nvertptr;

	while(*cind)
	{
		if((*cind)->sy <= realpolyclip[(*cind)->sx-currscreen->PhysicalMinX].ymax)
		{
			isclipped = FALSE;
			break;
		}
		cind++;
	}
	if(isclipped)	return(isclipped);

	//Test for clipped against top of visible area

	cind = nvertptr;

	while(*cind)
	{
		if((*cind)->sy >= realpolyclip[(*cind)->sx-currscreen->PhysicalMinX].ymin)
		{
			isclipped = FALSE;
			break;
		}
		cind++;
	}
	return(isclipped);
}

#if	DEBUGGING
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShowClippedRegion
//Author		Paul.   
//Date			Fri 16 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::ShowClippedRegion()
{
	return;

//TempCode RDH 11Mar96 	if(!polyclip)
//TempCode RDH 11Mar96 		return;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 	SLong	offset = currscreen->PhysicalMinX;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 	LogicalPtr	top;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 	//Point 'top' to the top left pixel on screen
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 	top = currscreen->logicalscreenptr + offset;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 	SLong	column;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 	for(column=0;column<currscreen->PhysicalWidth;column++,top++)
//TempCode RDH 11Mar96 	{
//TempCode RDH 11Mar96 		SLong	topoffset,bottomoffset;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 		topoffset = polyclip[column].ymin * (SLong )currscreen->BytesPerScanLine;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 		bottomoffset = polyclip[column].ymax * (SLong )currscreen->BytesPerScanLine;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 		LogicalPtr	botscan = top + bottomoffset;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 		LogicalPtr	topscan = top + topoffset;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 		*topscan = (UByte )RED04;
//TempCode RDH 11Mar96 
//TempCode RDH 11Mar96 		*botscan = (UByte )RED04;
//TempCode RDH 11Mar96 	}
}

#endif
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
		(*ptr)->iy += (shift<<16);

		ptr++;
	}
}

extern	"C" void ASM_SetAliasTblPtr(UByteP );
extern	"C" void ASM_AliasMappingLo(SLong,SLong,UByteP);
extern	"C" void ASM_AliasMappingHi(SLong,SLong,UByteP);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasMapping
//Author		Paul.   
//Date			Fri 15 Mar 1996
//
//Description	Convert an 8x8 image into an aliased 16x16 image
//
//Inputs		src = source image map number
//				(ix,iy) = coordinates of starting square on the 
//					source image
//				dst = destination image map number
//Returns	
//
//------------------------------------------------------------------------------
void polygon::AliasMappingLo(ImageMapNumber src, SWord ix, SWord iy, ImageMapNumber dst)
{
	currscreen->SetColour(src);

	ImageMapDescPtr	dstptr;

	dstptr = Image_Map.GetImageMapPtr(dst);

	ASM_AliasMappingLo((SLong )ix,(SLong )iy,(UByteP )&dstptr->data);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasMapping
//Author		Paul.   
//Date			Fri 15 Mar 1996
//
//Description	Convert an 8x8 image into an aliased 16x16 image
//
//Inputs		src = source image map number
//				(ix,iy) = coordinates of starting square on the 
//					source image
//				dst = destination image map number
//Returns	
//
//------------------------------------------------------------------------------
void polygon::AliasMappingHi(ImageMapNumber src, SWord ix, SWord iy, ImageMapNumber dst)
{
	currscreen->SetColour(src);

	ImageMapDescPtr	dstptr;

	dstptr = Image_Map.GetImageMapPtr(dst);

	ASM_AliasMappingHi((SLong )ix,(SLong )iy,(UByteP )&dstptr->data);
}


#include	"vector.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeAliasTable
//Author		Paul.   
//Date			Fri 22 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::MakeAliasTable()
{
	int	i, j, k;

	///////////////////////////

	if (aliastable)
		return;

//DeadCode PD 10Jul96 	#ifdef	DUMPALIASTABLE										//PD 26Mar96
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	aliastable=new UByte [256*256];
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	UByteP	index = aliastable;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	RGBTripletP	palptr = (RGBTripletP )currscreen->Palette;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	RGBTripletP	optr = palptr;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	vector	OutCol;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	index=aliastable;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	for (i=0;i<256;i++)
//DeadCode PD 10Jul96 	{
//DeadCode PD 10Jul96 		SLong	outred	= 	(0x0FF & (SLong )optr->r)<<2;
//DeadCode PD 10Jul96 		SLong	outgreen= 	(0x0FF & (SLong )optr->g)<<2;
//DeadCode PD 10Jul96 		SLong	outblue = 	(0x0FF & (SLong )optr->b)<<2;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 		OutCol = vector(outred,outgreen,outblue);
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 		RGBTripletP	iptr = palptr;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 		vector	InCol;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 		for (j=0;j<256;j++)
//DeadCode PD 10Jul96 		{
//DeadCode PD 10Jul96 			SLong	inred	=	(0x0FF & (SLong )iptr->r)<<2;
//DeadCode PD 10Jul96 			SLong	ingreen	=	(0x0FF & (SLong )iptr->g)<<2;
//DeadCode PD 10Jul96 			SLong	inblue	=	(0x0FF & (SLong )iptr->b)<<2;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 			InCol = vector(inred,ingreen,inblue);
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 			InCol = (InCol + OutCol)/(SLong )2;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 			RGBTripletP	sptr = palptr;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 			vector SCol,Diff;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 			SLong	scancol,scanmag;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 			scancol = -1;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 			scanmag = 256*256*256;	//64*64*64;					//PD 16May96
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 			for (k=0;k<256;k++)
//DeadCode PD 10Jul96 			{
//DeadCode PD 10Jul96 				SLong	scanred		=	(0x0FF & (SLong )sptr->r)<<2;
//DeadCode PD 10Jul96 				SLong	scangreen	=	(0x0FF & (SLong )sptr->g)<<2;
//DeadCode PD 10Jul96 				SLong	scanblue	=	(0x0FF & (SLong )sptr->b)<<2;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 				SCol = vector(scanred,scangreen,scanblue);
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 				Diff = SCol-InCol;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 				if (Diff.magnitude()<scanmag)
//DeadCode PD 10Jul96 				{
//DeadCode PD 10Jul96 					scanmag=Diff.magnitude();
//DeadCode PD 10Jul96 					scancol=k;
//DeadCode PD 10Jul96 				}
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 				sptr++;
//DeadCode PD 10Jul96 			}
//DeadCode PD 10Jul96 			*index++=(UByte )scancol;
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 			iptr++;
//DeadCode PD 10Jul96 		}
//DeadCode PD 10Jul96 		optr++;
//DeadCode PD 10Jul96 	}
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	#include "fileman.h"
//DeadCode PD 10Jul96 	#include "files.g"
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	string	nom=FILEMAN.namenumberedfile(FIL_ALIASTABLE);
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	FILE	*fp=fopen(nom,"wb");
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	if (fp)
//DeadCode PD 10Jul96 		fwrite(aliastable,1,65536,fp);
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	fclose (fp);
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	_Error.EmitSysErr(__FILE__":Alias data saved.");
//DeadCode PD 10Jul96 
//DeadCode PD 10Jul96 	#else

//Old_Code PD 23Jul96 	fileblock*	temp;
//Old_Code PD 23Jul96 
//Old_Code PD 23Jul96 	temp = new fileblock(FIL_ALIASTABLE);
//Old_Code PD 23Jul96 
//Old_Code PD 23Jul96 	aliastable= (UByteP )getdata(temp);
//Old_Code PD 23Jul96 	aliastable = aliastable + 1;								//RJS 10Jul96

	ImageMapDescPtr	imgp;										//PD 23Jul96

	ImageMapNumber	imno = (ImageMapNumber )(FIL_ALIASTABLE - DIR_IMAGEMAP);//PD 23Jul96

	imgp = Image_Map.GetImageMapPtr(imno);						//PD 23Jul96

	aliastable = &(imgp->data);									//PD 23Jul96

	ASM_SetAliasTblPtr(aliastable);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetImage
//Author		Paul.   
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ImageMapDescPtr	Alias_Cache::GetImage(const BlockID& req)
{
	ImageCacheP	reqblk;

	reqblk = IsCached(req);

	if (reqblk)
	{
		reqblk->framestamp = TRUE;
		return (reqblk->blockdata);
	}

	if (count==maxsize)	CacheTidy();

	if (count==maxperframe)
		return ((ImageMapDescPtr )NULL);

	//Generate the aliased version of this image

	count++;

	ImageCacheP	newblock = new ImageCache;

	newblock->blockid = req;

	newblock->framestamp=TRUE;

	ImageMapDescPtr	imageptr;

	imageptr = (this->*aliascode)(*newblock);

	//Add the new block to the cache for next time

	ImageCacheP	temp = root;

	root = newblock;

	newblock->next = temp;

	return (imageptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillCacheEntry
//Author		Paul.   
//Date			Fri 3 May 1996
//
//Description	Removes the requested entry from the cache
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Alias_Cache::KillCacheEntry(const BlockID& req)
{
	Bool	deleted = FALSE;

	if (root->blockid.worldx==req.worldx &&
		root->blockid.worldz==req.worldz)
	{

	 	deleted = TRUE;
	}
	else
	{
		ImageCacheP prev = root;
		ImageCacheP	scan = prev->next;

		while (scan)
		{
			if (scan->blockid.worldx==req.worldx &&
				scan->blockid.worldz==req.worldz)
			{
				//Remove this link from the list

				prev->next = scan->next;

				deleted = TRUE;

				delete (scan->blockdata);

				delete (scan);

				break;
			}
			prev = scan;
			scan = prev->next;
		}
	}
	return (deleted);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CacheTidy
//Author		Paul.   
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Alias_Cache::CacheTidy()
{
	ImageCacheP	thisblock,
				prevblock;
					
	if (!root)	return;
	
	while (!root->framestamp)
	{
		prevblock = root->next;
	
		count--;

		delete (root);

		root = prevblock;

		if (!root)	return;
	}

	thisblock = prevblock->next;

	while (thisblock)
	{
		if (!thisblock->framestamp)
		{
			count--;
	
			prevblock->next = thisblock;
							
			delete (thisblock);
		}
		else
		{
			prevblock = thisblock;
		}
		thisblock = prevblock->next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CacheStmp
//Author		Paul.   
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Alias_Cache::CacheStmp()
{
	ImageCacheP	thisblock;
								
	thisblock = root;

	while (thisblock)
	{
		thisblock->framestamp = FALSE;

		thisblock=thisblock->next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasImageHi
//Author		Paul.   
//Date			Fri 3 May 1996
//
//Description	Generates an aliased image map
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ImageMapDescPtr Alias_Cache::AliasImageHi(ImageCache& img)
{
	//The resulting image will be 32x32 pixels in size

	//Allocate buffer area to store the aliased image

	UByte*	buf = new UByte[HiResImageSize];

	img.blockdata = (ImageMapDescPtr )buf;

	img.blockdata->width = 5;	// 1<<5 = 32
	img.blockdata->height= 5;	// 1<<5 = 32

	currscreen->SetColour(img.blockid.src);

	ASM_AliasMappingHi((SLong )img.blockid.worldx,(SLong )img.blockid.worldz,&img.blockdata->data);

	return (img.blockdata);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasImageLo
//Author		Paul.   
//Date			Fri 3 May 1996
//
//Description	Generates an aliased image map
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ImageMapDescPtr Alias_Cache::AliasImageLo(ImageCache& img)
{
	//The resulting image will be 16x16 pixels in size
	
	//Allocate buffer area to store the aliased image

	UByte*	buf = new UByte[LoResImageSize];

	img.blockdata = (ImageMapDescPtr )buf;

	img.blockdata->width = 4;	// 1<<4 = 16
	img.blockdata->height= 4;	// 1<<4 = 16

	currscreen->SetColour(img.blockid.src);

	ASM_AliasMappingLo((SLong )img.blockid.worldx,(SLong )img.blockid.worldz,&img.blockdata->data);

	return (img.blockdata);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitAliasCache
//Author		Paul.   
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void polygon::InitAliasCache()
{
	loalias = new AliasCache(	currscreen,
								MaxTotalLoAlias,MaxLoAliasPerFrame,
								FALSE
							);

	hialias = new AliasCache(	currscreen,
								MaxTotalHiAlias,MaxHiAliasPerFrame,
								TRUE
							);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteAliasCache
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
void polygon::DeleteAliasCache()
{
	if (loalias)
	{
		delete (loalias);
		loalias = NULL;
	}

	if (hialias)
	{
		delete (hialias);
		hialias = NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasMappingHi
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
Bool polygon::AliasMappingHi(ImageMapNumber src,SWord ix,SWord iy)
{
	Bool	gotalias = FALSE;

	ImageMapDescPtr	imageptr;

	BlockID* req = new BlockID;

	req->worldx = ix;
	req->worldz = iy;
	req->src = src;

	imageptr = hialias->GetImage(*req);

	if (imageptr)
	{
		//Got a pointer to the aliased image

		gotalias = TRUE;

		currscreen->SetColour(imageptr);

		loalias->KillCacheEntry(*req);
	}

	return (gotalias);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasMappingLo
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
Bool polygon::AliasMappingLo(ImageMapNumber src,SWord ix,SWord iy)
{
	Bool	gotalias = FALSE;

	ImageMapDescPtr	imageptr;

	BlockID* req = new BlockID;

	req->worldx = ix;
	req->worldz = iy;
	req->src = src;

	imageptr = loalias->GetImage(*req);

	if (imageptr)
	{
		//Got a pointer to the aliased image

		gotalias = TRUE;

		currscreen->SetColour(imageptr);

		hialias->KillCacheEntry(*req);
	}

	return (gotalias);
}
