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
//Filename       shpbld.cpp
//System         
//Author         Paul.   
//Date           Mon 22 Jan 1996
//Description    Code to generate shapes on the fly
//------------------------------------------------------------------------------

	#include	<stdlib.h>
	#include	"shpbld.h"
	#include	"shpinstr.h"

	class	ShapeBuild	Shape_Build;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShapeBuild
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ShapeBuild::ShapeBuild()
{
	currentp = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShapeBuild
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ShapeBuild::~ShapeBuild()
{
	if(currentp!=NULL)
	{
		delete [] currentp;
		currentp=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildCloud
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	Generates a cloud shape to be drawn. Shape deletes its self
//				after being drawn.
//
//Inputs		ShapeNumber - index into shape table to place a pointer to 
//				this shape so that it can be drawn/deleted later.
//
//
//
//
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP ShapeBuild::BuildCloud(ImageMapNumber image, ImageMapNumber cntr, SWord sampfreq)
{
	UByteP retval;

	int	i,j;

	SWord	point_scale = 2;

	ImageMapDescPtr	cmapp,imapp;

	ImageMapNumber	absimage,abscntr;

	if(currentp!=NULL) free(currentp);

	abscntr = (ImageMapNumber )((cntr<0)?-cntr:cntr);

	absimage = (ImageMapNumber)((image<0)?-image:image);

	cmapp = Image_Map.GetImageMapPtr(abscntr);

	imapp = Image_Map.GetImageMapPtr(absimage);

	//Use image map dimensions + sampfreq to determine how much space
	//is required to generate the cloud shape

	SLong cntr_width = cmapp->w;//RJS 06Feb98

	SLong cntr_height = cmapp->h;//RJS 06Feb98

	SLong image_width = imapp->w;//RJS 06Feb98

	SLong image_height = imapp->h;//RJS 06Feb98

	SLong dopointcount = (cntr_width/sampfreq) * (cntr_height/sampfreq);

	SLong polygoncount = ((cntr_width-1)/sampfreq) * ((cntr_height-1)/sampfreq);

	polygoncount <<= 1;	//Triangles

	SLong copyvertcount = 3*polygoncount;

	SLong total_space_required =

			dopointcount * (1+sizeof(DOPOINT)) +

			polygoncount * (1+sizeof(DOCREATEBUMPPOLY)) +

			copyvertcount * (1+sizeof(DOCOPYBVERT)) +

			polygoncount * (1) + 			//sizeof(DODRAWBPOLY) == 0

			1;								//sizeof(DORETURN) == 0

	currentp =
		retval = new UByte [total_space_required];				//JIM 28Mar96

	//retval is now a pointer to a buffer of the correct size to 
	//build the new shape into

	//Now, fill the new buffer with shape instructions to be drawn

	SWord	vertex = 0;

	SLong	point_x, point_y, point_z, reset_x;

	SLong	x_step,z_step;

	x_step = point_scale * sampfreq;

	z_step = point_scale * sampfreq;

	//Dopoint definitions first

	point_x =
		reset_x = -(cntr_width>>1)*point_scale;

	point_z = -(cntr_height>>1)*point_scale;

	UByteP	wptr = retval;

	for (i=(cntr_height/sampfreq);i--;)
	{
		for (j=(cntr_width/sampfreq);j--;)
		{
			SLong	offset = (i*sampfreq)*cntr_width + (j*sampfreq);

			point_y = 128-(SWord )*(cmapp->body + offset);//RJS 06Feb98

			point_y <<= 2;

			CreateDoPoint(	wptr,
							vertex,
							(SWord )point_x,
							(SWord )point_y,
							(SWord )point_z
							);

			point_x += x_step;
			vertex++;
		}
		point_x = reset_x;
		point_z += z_step;
	}

	//Now, generate the polygons

	vertex = 0;

	SWord	reset_ix;

	SWord	ix =
			reset_ix = 0;

	SWord	iy = 0;

	SLong	temp;

	temp = (image_width * sampfreq)/cntr_width;

	SWord	ix_step = (SWord )temp;

	temp = (image_height * sampfreq)/cntr_height;

	SWord	iy_step = (SWord )temp;

	for (i=(cntr_height/sampfreq)-1;i--;)
	{
		for (j=(cntr_width/sampfreq)-1;j--;)
		{
			SWord	v0,v1,v2,v3;
			SWord	ix0,ix1,ix2,ix3;
			SWord	iy0,iy1,iy2,iy3;

			v0 = vertex;ix0 = ix;iy0 = iy;
			v1 = vertex + 1;ix1 = ix + ix_step;iy1 = iy;
			v2 = vertex + (cntr_height/sampfreq);ix2=ix;iy2=iy+iy_step;
			v3 = v2 + 1;ix3=ix + ix_step;iy3 = iy+iy_step;

			CreateDoCreateIPoly(wptr,image);
			CreateDoCopyIVert(wptr,v0,ix0,iy0);
			CreateDoCopyIVert(wptr,v1,ix1,iy1);
			CreateDoCopyIVert(wptr,v2,ix2,iy2);
			CreateDoDrawIPoly(wptr);

			CreateDoCreateIPoly(wptr,image);
			CreateDoCopyIVert(wptr,v1,ix1,iy1);
			CreateDoCopyIVert(wptr,v3,ix3,iy3);
			CreateDoCopyIVert(wptr,v2,ix2,iy2);
			CreateDoDrawIPoly(wptr);

			vertex++;
			ix += ix_step;
		}
		vertex++;
		iy += iy_step;
		ix = reset_ix;
	}

	CreateDoReturn(wptr);

	return(retval);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteCloud
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ShapeBuild::DeleteCloud()
{
	if(currentp!=NULL)
	{
		delete []	currentp;
		currentp=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDoPoint
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ShapeBuild::CreateDoPoint(UByteP& iptr,SWord vertex,SWord x,SWord y, SWord z)
{
	*iptr++ = (UByte )(dopointno<<1);
	
	DOPOINT_PTR	p = (DOPOINT_PTR )iptr;

	p->vertex = (UWord )(vertex<<4);

	p->xcoord = x;p->ycoord = y;p->zcoord = z;

	iptr += sizeof(DOPOINT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDoCreateBumpPoly
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ShapeBuild::CreateDoCreateBumpPoly(UByteP& iptr,ImageMapNumber image)
{
	*iptr++ = (UByte )(docreatebumppolyno<<1);

	DOCREATEBUMPPOLY_PTR p = (DOCREATEBUMPPOLY_PTR )iptr;

	p->bump_no =
		p->image_no = (SWord )image;

	iptr += sizeof(DOCREATEBUMPPOLY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDoCopyBVert
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ShapeBuild::CreateDoCopyBVert(UByteP& iptr,SWord vertex, SWord ix, SWord iy)
{
	*iptr++ = (UByte )(docopybvertno<<1);

	DOCOPYBVERT_PTR p = (DOCOPYBVERT_PTR )iptr;

	p->vertex = (UWord )vertex;

	p->image_x = ix;

	p->image_y = iy;

	iptr += sizeof(DOCOPYBVERT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDoDrawBPoly
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ShapeBuild::CreateDoDrawBPoly(UByteP& iptr)
{
	*iptr++ = (UByte )(dodrawbpolyno<<1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreatDoReturn
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ShapeBuild::CreateDoReturn(UByteP& iptr )
{
	*iptr++ = (UByte )(doretno<<1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDoCreateIPoly
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ShapeBuild::CreateDoCreateIPoly(UByteP& iptr,ImageMapNumber image)
{
	*iptr++ = (UByte )(docreateipolyno<<1);

	DOCREATEIPOLY_PTR p = (DOCREATEIPOLY_PTR )iptr;

	p->image_no = (SWord )image;

	iptr += sizeof(DOCREATEIPOLY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDoCopyIVert
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ShapeBuild::CreateDoCopyIVert(UByteP& iptr,SWord vertex,SWord ix,SWord iy)
{
 	*iptr++ = (UByte )(docopyivertno<<1);

	DOCOPYIVERT_PTR p = (DOCOPYIVERT_PTR )iptr;

	p->vertex = (UWord )vertex;

	p->image_x = (UWord )ix;

	p->image_y = (UWord )iy;

	iptr += sizeof(DOCOPYIVERT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDoDrawIPoly
//Author		Paul.   
//Date			Mon 22 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ShapeBuild::CreateDoDrawIPoly(UByteP& iptr)
{
	*iptr++ = (UByte )(dodrawipolyno<<1);
}

