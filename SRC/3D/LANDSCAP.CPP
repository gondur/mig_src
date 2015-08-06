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
//Filename       landscap.cpp
//System         
//Author         Paul.   
//Date           Mon 6 Nov 1995
//Description    
//------------------------------------------------------------------------------

//#define NO_LIGHT	"YES"

		#include	"Dosdefs.h"
		#include "mystack.h"
#define F_GRAFIX												//DAW 05Aug96
#define F_BATTLE
		#include "Worldinc.h"

		#include "enumbits.m"									//PD 04Dec95
		#include "Palette.h"
		#include "Files.g"
		#include "3DDefs.h"
		#include "ImageMap.h"
		#include "BTree.h"
		#include "Polygon.h"
#define MATRIX_CODE_REQ						//RJS 26Jun98
		#include "Matrix.h"
		#include "WorldInc.h"
		#include "World.h"
		#include "3DCode.h"
		#include "3DCom.h"
		#include "HardpASM.h"
		#include	"gameset.h"									//PD 05Oct98
		#include "LandScap.h"
		#include "myMath.h"
		#include "viewsel.h"										//PD 19Mar96
		#include "Collided.h"									//PD 21Mar96
		#include	"keytest.h"									//PD 20May96
		#include	"flymodel.h"								//PD 24Jun96

#include "ImageMap.g"

		#include "migLand.h"						//PD 19Jan98 
		#include "savegame.h"
		#include	"missman2.h"

		#define	INIT_HDATA										//PD 25Nov97
		#include "hdata.h"										//PD 25Nov97

		#include "monotxt.h"
		#include "prof.h"
		#include	"miles.h"
		#include "tilemake.h"
	#include "overlay.h"
#include "areatype.h"

		class LandScape Land_Scape;


//DeadCode PD 26Feb99 		extern UByte breakpoly;

		MATHABLE(CLIPFLAGS3D);
		BITABLE(CLIPFLAGS3D);

		SLong 	_cloudLayerHeight=15000*33;	//1500ft in cm
		SLong	lowestgroundpoint;
		extern void GreyPalette(UByte*,UByte*,UByte*);
		extern bool mono3d;

struct LandScape::RouteData{
 	UWord type;
	ULong width;
	ULong maxWidth;
	Colour colour;
	LandMapNum plainTexture;
	UWord pX0,pY0,pX1,pY1;
	LandMapNum maskedTexture;
	UWord mX0,mY0,mX1,mY1;
	RouteData() {}
	RouteData(	UWord a, ULong b, ULong bb, Colour c,
				LandMapNum d,UWord ax0,UWord ay0,UWord ax1,UWord ay1,
				LandMapNum e,UWord bx0,UWord by0,UWord bx1,UWord by1)
	{
		type=a;
		width=b;
		maxWidth=bb;
		colour=c;
		plainTexture=d; pX0=ax0; pY0=ay0; pX1=ax1; pY1=ay1;
		maskedTexture=d; mX0=bx0; mY0=by0; mX1=bx1; mY1=by1;
	}
	inline RouteData* find(UWord type){
	 	RouteData* srch=this;
		while (srch->type!=type && srch->type!=0xFFFF) srch++;
		if (srch->type==0xFFFF) return (RouteData*)NULL;
		return srch;
	}
};

void LandScape::ResetItemLog()
{
	if (Save_Data.fSoftware && softGrid!=NULL)
	{
		const SLong length=_wholeAreaSizeMIN*_wholeAreaSizeMIN;
		UByte *ptr=softGrid;
		for (SLong i=(length>>2)-1;i>=0;*(ULong*)ptr=ULong(0),ptr+=4,i--);
		if (length&2L) *(UWord*)ptr=UWord(0),ptr+=2;
		if (length&1L) *(UByte*)ptr=UByte(0);
	}
}

bool LandScape::LogItem(ULong vx,ULong vz,COORDS3D& pos)
{
	if (Save_Data.fSoftware && softGrid!=NULL)
	{
		if (pos.Y>HIGHESTGROUND) return false;	//no point logging an item > HIGHESTGROUND

		//generate grid position for this item

		ULong	ox=(vx&~ULong(_blockWidth-1))-_halfAreaSizeMIN*_blockWidth;
		ox=(pos.X>>17)-ox; if (ox>ULong(_wholeAreaSizeMIN-1)) return false; /* object not on grid */

		ULong	oz=(vz&~ULong(_blockWidth-1))-_halfAreaSizeMIN*_blockWidth;
		oz=(pos.Z>>17)-oz; if (oz>ULong(_wholeAreaSizeMIN-1)) return false; /* object not on grid */

		*(softGrid+(oz*_wholeAreaSizeMIN)+ox)=0xFF;

		return true; /* stop any further item insertion tests once one has been inserted successfully */
	}
	/* else */ return true; /* stop attempts to insert any items unless it's the software version */
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderLandscape
//Author		Paul.   
//Date			Mon 6 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::RenderLandscape(Window *screen,					//JIM 12Dec95
								ViewPoint* vp,
								FPMATRIX_PTR matrixptr,
								ULong& wx, ULong& wy, ULong& wz,
								ANGLES heading)
{
	screen->DoSetShadeVals(currentLighting.landAmbientCol.red(),
							currentLighting.landAmbientCol.green(),
							currentLighting.landAmbientCol.blue(),
							currentLighting.effectsAmbientCol.red(),
							currentLighting.effectsAmbientCol.green(),
							currentLighting.effectsAmbientCol.blue());

	Bool	old_xprod;
	Bool	otherfade;

	bool notMap=true;
	
	if (View_Point!=NULL)
		notMap=(View_Point->viewnum.viewmode!=VM_Map || (View_Point->viewnum.viewmode==VM_Map && OverLay.fZoomedMap))?true:false;

	//Initialise variables local to 'LandScape'

	viewer_hdg = heading;
	viewer_x = wx;
	viewer_y = wy;
	viewer_z = wz;

	fpviewer_matrix = matrixptr;

	currscreen = screen;

	View_Point=vp;

	//Set various distance variables up
	View_Ground_Height = SetViewDetail();						//RJS 25Jun98

	//Draw horizon in here
	if (View_Point && notMap)		//RJS 10Sep98
	{
		if (View_Point->drawmap == FALSE)
		{
			InfiniteStrip();
 			DoCloudLayer();
		}
		lowestgroundpoint=0x7FFFFFFF;								//PD 12Dec96
		otherfade=(!Three_Dee.IsPaused())?BadVision():FALSE;

		AutoScaleFrameRate();

		for (int i=2;i>=0;i--) 
			if (GeneratePointData()) break;

		if (i==-1)
			_Error.EmitSysErr(__FILE__":Unrecoverable landscape data problem");

		if (lowestgroundpoint==0x07FFFFFFF)							  //JIM 29/03/99
			lowestgroundpoint=0;	//PD 27Sep97

		if (View_Point->drawmap == FALSE)
		{
			screen->DoSetShadeVals(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
			DoRain(vp,View_Ground_Height);								//RJS 25Jun98
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TidyUp
//Author		Paul.   
//Date			Wed 13 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::TidyUp()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WireFrame
//Author		Paul.   
//Date			Tue 10 Mar 1998
//------------------------------------------------------------------------------
void LandScape::WireFrame(DoPointStruc& p0,DoPointStruc& p1,DoPointStruc& p2)
{
	LINETYPE ltLine;
	struct vertex startVertex,endVertex;
	ltLine.ltType=LineType::LT_PlainColour;
	ltLine.lpStartVertex=&startVertex;
	ltLine.lpEndVertex=&endVertex;
	ltLine.colour=ARTWORKMASK;
	//Draw 3 lines to surround the triangle
	startVertex.bx=p0.bodyx;
	startVertex.by=p0.bodyy;
	startVertex.bz=p0.bodyz;
	startVertex.bx.f*=.5;
	startVertex.by.f*=.5;
	startVertex.bz.f*=.5;
	endVertex.bx=p1.bodyx;
	endVertex.by=p1.bodyy;
	endVertex.bz=p1.bodyz;
	endVertex.bx.f*=.5;
	endVertex.by.f*=.5;
	endVertex.bz.f*=.5;
	currscreen->DoHardLine(&ltLine);
	endVertex.bx=p2.bodyx;
	endVertex.by=p2.bodyy;
	endVertex.bz=p2.bodyz;
	endVertex.bx.f*=.5;
	endVertex.by.f*=.5;
	endVertex.bz.f*=.5;
	currscreen->DoHardLine(&ltLine);
	startVertex.bx=p1.bodyx;
	startVertex.by=p1.bodyy;
	startVertex.bz=p1.bodyz;
	startVertex.bx.f*=.5;
	startVertex.by.f*=.5;
	startVertex.bz.f*=.5;
	currscreen->DoHardLine(&ltLine);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GridCone
//Author		Paul.   
//Date			Mon 22 Jun 1998
//------------------------------------------------------------------------------
void LandScape::GridCone(const SLong px,const SLong pz)
{
	const Float _fbw=Float(_blockWidth);
	FPMATRIX& mat=*fpviewer_matrix;
	fpCOORDS3D tbasepos,tdeltawx,tdeltawy,tdeltawz;

	SLong intbaseposX=px;
	SLong intbaseposZ=pz;

	tbasepos.X.i=px-viewer_x;
	tbasepos.Y.i=-viewer_y;
	tbasepos.Z.i=pz-viewer_z;

	_matrix.transform(&mat,tbasepos.X,tbasepos.Y,tbasepos.Z);

	tdeltawx.X.f=mat.L11*_fbw;
	tdeltawx.Y.f=mat.L21*_fbw;
	tdeltawx.Z.f=mat.L31*_fbw;

	tdeltawy.X.f=mat.L12*Float(_altitudeScale);
	tdeltawy.Y.f=mat.L22*Float(_altitudeScale);
	tdeltawy.Z.f=mat.L32*Float(_altitudeScale);

	tdeltawz.X.f=mat.L13*_fbw;
	tdeltawz.Y.f=mat.L23*_fbw;
	tdeltawz.Z.f=mat.L33*_fbw;

	UByte* ptr=gridCorners;

	SLong cornerLength,wholeAreaSize;

	cornerLength=_cornerLengthMIN;
	wholeAreaSize=_wholeAreaSizeMIN;

	for (int r=0;r<cornerLength;r++)
	{
		fpCOORDS3D 	tbaseinner=tbasepos;
		SLong intinnerposX=intbaseposX;
		SLong intinnerposZ=intbaseposZ;

		for (int c=0;c<cornerLength;c++)
		{
			fpCOORDS3D low,high;
			SLong min,max;

			Three_Dee.pTMake->GetMinMaxAlt(intinnerposX,intinnerposZ,min,max);

			low.X.f=tbaseinner.X.f+tdeltawy.X.f*Float(min);
			low.Y.f=tbaseinner.Y.f+tdeltawy.Y.f*Float(min);
			low.Z.f=tbaseinner.Z.f+tdeltawy.Z.f*Float(min);

			high.X.f=tbaseinner.X.f+tdeltawy.X.f*Float(max);
			high.Y.f=tbaseinner.Y.f+tdeltawy.Y.f*Float(max);
			high.Z.f=tbaseinner.Z.f+tdeltawy.Z.f*Float(max);

			*ptr++=_matrix.GenClipFlags(low)&_matrix.GenClipFlags(high);

			intinnerposX+=_blockWidth;

			tbaseinner.X.f+=tdeltawx.X.f;
			tbaseinner.Y.f+=tdeltawx.Y.f;
			tbaseinner.Z.f+=tdeltawx.Z.f;
		}
		intbaseposZ+=_blockWidth;

		tbasepos.X.f+=tdeltawz.X.f;
		tbasepos.Y.f+=tdeltawz.Y.f;
		tbasepos.Z.f+=tdeltawz.Z.f;
	}
	ptr=gridCorners;
	UByte* res=gridCone;

	for (r=0;r<wholeAreaSize;r++,ptr+=cornerLength)
	{
		UByte* ptr2=ptr;
	 	for (int c=0;c<wholeAreaSize;c++,ptr2++)
		{
			UByte andedFlags=*ptr2;
			andedFlags&=*(ptr2+1);
			andedFlags&=*(ptr2+cornerLength);
			andedFlags&=*(ptr2+cornerLength+1);

			if (andedFlags!=0)	*res++=0;
			else				*res++=1;
		}
	}
//	if (!Manual_Pilot.ControlledAC2)
//		memset(gridCone,1,wholeAreaSize*wholeAreaSize);
}

//Old_Code PD 16Dec98 void LandScape::GridCone(const SLong px,const SLong pz)
//Old_Code PD 16Dec98 {
//Old_Code PD 16Dec98 	const Float _fbw=Float(_blockWidth);
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	FPMATRIX& mat=*fpviewer_matrix;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	fpCOORDS3D 	tbasepos,
//Old_Code PD 16Dec98 				ttoppos;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	fpCOORDS3D	tdeltawx,
//Old_Code PD 16Dec98 				tdeltawz;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	tbasepos.X.i=px-viewer_x;
//Old_Code PD 16Dec98 	tbasepos.Y.i=-viewer_y;
//Old_Code PD 16Dec98 	tbasepos.Z.i=pz-viewer_z;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	_matrix.transform(&mat,tbasepos.X,tbasepos.Y,tbasepos.Z);
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	ttoppos.X.f=tbasepos.X.f+(mat.L12*Float(_maxalt));
//Old_Code PD 16Dec98 	ttoppos.Y.f=tbasepos.Y.f+(mat.L22*Float(_maxalt));
//Old_Code PD 16Dec98 	ttoppos.Z.f=tbasepos.Z.f+(mat.L32*Float(_maxalt));
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	tdeltawx.X.f=mat.L11*_fbw;
//Old_Code PD 16Dec98 	tdeltawx.Y.f=mat.L21*_fbw;
//Old_Code PD 16Dec98 	tdeltawx.Z.f=mat.L31*_fbw;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	tdeltawz.X.f=mat.L13*_fbw;
//Old_Code PD 16Dec98 	tdeltawz.Y.f=mat.L23*_fbw;
//Old_Code PD 16Dec98 	tdeltawz.Z.f=mat.L33*_fbw;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	UByte* ptr=gridCorners;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	SLong cornerLength=	gameSettings.m_wHorizonDistance==1?
//Old_Code PD 16Dec98 						_cornerLengthMAX:
//Old_Code PD 16Dec98 						_cornerLengthMIN;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	for (int r=0;r<cornerLength;r++)
//Old_Code PD 16Dec98 	{
//Old_Code PD 16Dec98 		fpCOORDS3D 	tbaseinner=tbasepos,
//Old_Code PD 16Dec98 					ttopinner=ttoppos;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 		for (int c=0;c<cornerLength;c++)
//Old_Code PD 16Dec98 		{
//Old_Code PD 16Dec98 			*ptr++=	_matrix.GenClipFlags(tbaseinner)&
//Old_Code PD 16Dec98 					_matrix.GenClipFlags(ttopinner);
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 			tbaseinner.X.f+=tdeltawx.X.f;
//Old_Code PD 16Dec98 			tbaseinner.Y.f+=tdeltawx.Y.f;
//Old_Code PD 16Dec98 			tbaseinner.Z.f+=tdeltawx.Z.f;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 			ttopinner.X.f+=tdeltawx.X.f;
//Old_Code PD 16Dec98 			ttopinner.Y.f+=tdeltawx.Y.f;
//Old_Code PD 16Dec98 			ttopinner.Z.f+=tdeltawx.Z.f;
//Old_Code PD 16Dec98 		}
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 		tbasepos.X.f+=tdeltawz.X.f;
//Old_Code PD 16Dec98 		tbasepos.Y.f+=tdeltawz.Y.f;
//Old_Code PD 16Dec98 		tbasepos.Z.f+=tdeltawz.Z.f;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 		ttoppos.X.f+=tdeltawz.X.f;
//Old_Code PD 16Dec98 		ttoppos.Y.f+=tdeltawz.Y.f;
//Old_Code PD 16Dec98 		ttoppos.Z.f+=tdeltawz.Z.f;
//Old_Code PD 16Dec98 	}
//Old_Code PD 16Dec98 	ptr=gridCorners;
//Old_Code PD 16Dec98 	UByte* res=gridCone;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	SLong wholeAreaSize=gameSettings.m_wHorizonDistance==1?
//Old_Code PD 16Dec98 						_wholeAreaSizeMAX:
//Old_Code PD 16Dec98 						_wholeAreaSizeMIN;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	for (r=0;r<wholeAreaSize;r++,ptr+=cornerLength)
//Old_Code PD 16Dec98 	{
//Old_Code PD 16Dec98 		UByte* ptr2=ptr;
//Old_Code PD 16Dec98 	 	for (int c=0;c<wholeAreaSize;c++,ptr2++)
//Old_Code PD 16Dec98 		{
//Old_Code PD 16Dec98 			UByte andedFlags=*ptr2;
//Old_Code PD 16Dec98 			andedFlags&=*(ptr2+1);
//Old_Code PD 16Dec98 			andedFlags&=*(ptr2+cornerLength);
//Old_Code PD 16Dec98 			andedFlags&=*(ptr2+cornerLength+1);
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 			if (andedFlags!=0)	*res++=0;
//Old_Code PD 16Dec98 			else				*res++=1;
//Old_Code PD 16Dec98 		}
//Old_Code PD 16Dec98 	}
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	SLong halfAreaSize=gameSettings.m_wHorizonDistance==1?
//Old_Code PD 16Dec98 						_halfAreaSizeMAX:_halfAreaSizeMIN;
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 	//mono grid cone debugs
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 //	char *grid=(char*)0x0B0000;
//Old_Code PD 16Dec98   //	for (r=0;r<wholeAreaSize && r<25;r++)
//Old_Code PD 16Dec98 	//	for (int c=0;c<wholeAreaSize;c++)
//Old_Code PD 16Dec98 	  //	{
//Old_Code PD 16Dec98 		// 	char ch;
//Old_Code PD 16Dec98 		  //	if (gridCone[r*wholeAreaSize+c]==0)	ch='.';
//Old_Code PD 16Dec98 			//else								ch='V';
//Old_Code PD 16Dec98 			 //
//Old_Code PD 16Dec98 //			grid[(c*2)+(r*160)]=ch;
//Old_Code PD 16Dec98   //		}
//Old_Code PD 16Dec98 
//Old_Code PD 16Dec98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScrollGrid
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void LandScape::ScrollGrid(SLong dx,SLong dz,UByte* pGrid)
{
	const SLong wholeAreaSize=_wholeAreaSizeMIN;
	const SLong GRID_SIZE=wholeAreaSize*wholeAreaSize;

	while (dx>0)
	{
		//scroll data left (west) 'cos we're moving east

		UByte* ptmp=pGrid;

		for (SLong c=wholeAreaSize;c--;)
		{
			for (SLong r=wholeAreaSize-1;r--;)
			{
			 	ptmp[0]=ptmp[1];
				ptmp++;
			}
			*ptmp++=0xFF;
		}
		dx-=_blockWidth;
	}

	while (dx<0)
	{
		//scroll data right (east) 'cos we're moving west

		UByte* ptmp=pGrid+GRID_SIZE-1;

		for (SLong r=wholeAreaSize;r--;)
		{
			for (SLong c=wholeAreaSize-1;c--;)
			{
				ptmp[0]=ptmp[-1];
				ptmp--;
			}
			*ptmp--=0xFF;
		}
		dx+=_blockWidth;
	}

	while (dz>0)
	{
		//scroll data up (south) 'cos we're moving north

		UByte* ptmp=pGrid;
		UByte* ptmp2=ptmp+wholeAreaSize;

		SLong r;

		for (r=GRID_SIZE-wholeAreaSize;r--;)
			*ptmp++=*ptmp2++;
		for (r=wholeAreaSize;r--;)
			*ptmp++=0xFF;

		dz-=_blockWidth;
	}

	while (dz<0)
	{
		//scroll data down (north) 'cos we're moving south

		UByte* ptmp=pGrid+GRID_SIZE-1;
		UByte* ptmp2=ptmp-wholeAreaSize;

		SLong r;

		for (r=GRID_SIZE-wholeAreaSize;r--;)
			*ptmp--=*ptmp2--;
		for (r=wholeAreaSize;r--;)
			*ptmp--=0xFF;

		dz+=_blockWidth;
	}
}

void LandScape::ScrollGridDis(SLong dx,SLong dz,HTEXT* pGrid,Dropped* pDiscarded)
{
	const SLong wholeAreaSize=_wholeAreaSizeMIN;
	const SLong GRID_SIZE=wholeAreaSize*wholeAreaSize;

	while (dx>0)
	{
		//scroll data left (west) 'cos we're moving east
		HTEXT* ptmp=pGrid;
		for (SLong c=wholeAreaSize-1;c>=0;c--)
		{
			if (ptmp[0]!=HTEXTNULL)	pDiscarded->hText[pDiscarded->num++]=ptmp[0];
			for (SLong r=wholeAreaSize-1;r;r--,ptmp++) ptmp[0]=ptmp[1];
			*ptmp++=HTEXTNULL;
		}
		dx-=_blockWidth;
	}

	while (dx<0)
	{
		//scroll data right (east) 'cos we're moving west
		HTEXT* ptmp=pGrid+GRID_SIZE-1;
		for (SLong r=wholeAreaSize-1;r>=0;r--)
		{
			if (ptmp[0]!=HTEXTNULL)	pDiscarded->hText[pDiscarded->num++]=ptmp[0];
			for (SLong c=wholeAreaSize-1;c;c--,ptmp--) ptmp[0]=ptmp[-1];
			*ptmp--=HTEXTNULL;
		}
		dx+=_blockWidth;
	}

	while (dz>0)
	{
		//scroll data up (south) 'cos we're moving north
		HTEXT *ptmp=pGrid,*ptmp2=ptmp+wholeAreaSize;
		for (SLong r=wholeAreaSize-1;r>=0;r--)	if (ptmp[r]!=HTEXTNULL) pDiscarded->hText[pDiscarded->num++]=ptmp[r];
		for (r=GRID_SIZE-wholeAreaSize;r--;)	*ptmp++=*ptmp2++;
		for (r=wholeAreaSize;r--;)				*ptmp++=HTEXTNULL;
		dz-=_blockWidth;
	}

	while (dz<0)
	{
		//scroll data down (north) 'cos we're moving south
		HTEXT *ptmp=pGrid+GRID_SIZE-1,*ptmp2=ptmp-wholeAreaSize;
		for (SLong r=wholeAreaSize-1;r>=0;r--)	if (ptmp[-r]!=HTEXTNULL) pDiscarded->hText[pDiscarded->num++]=ptmp[-r];
		for (r=GRID_SIZE-wholeAreaSize;r--;)	*ptmp--=*ptmp2--;
		for (r=wholeAreaSize;r--;)				*ptmp--=HTEXTNULL;
		dz+=_blockWidth;
	}
}

//DeadCode PD 19Nov98 int texturesReMade;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ManageHighLandTextures
//Author		Paul.   
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
void LandScape::ManageHighLandTextures(SLong px,SLong pz)
{
	SLong NUM_256_TEXTURES,NUM_128_TEXTURES,NUM_64_TEXTURES,NUM_32_TEXTURES,NUM_16_TEXTURES,NUM_8_TEXTURES;

	if (!Save_Data.fSoftware)	currscreen->DoGetTextureScales(	NUM_256_TEXTURES,
																NUM_128_TEXTURES,
																NUM_64_TEXTURES,
																NUM_32_TEXTURES,
																NUM_16_TEXTURES,
																NUM_8_TEXTURES);
	else Three_Dee.pTMake->DoGetTextureScales(	NUM_256_TEXTURES,
												NUM_128_TEXTURES,
												NUM_64_TEXTURES,
												NUM_32_TEXTURES,
												NUM_16_TEXTURES,
												NUM_8_TEXTURES);
	const SLong MAX_TILES_PER_FRAME=8;
	const SLong wholeAreaSize=_wholeAreaSizeMIN;
	const SLong GRID_SIZE=wholeAreaSize*wholeAreaSize;

	struct ChangedTile
	{
		UWord offset;
		HTEXT oldHTexture;
		UByte newRez;
		UByte pad;
	};

	struct NewTile
	{
		UWord offset;
		UByte newRez;
		UByte pad;
	};

	if (pLastGrid==NULL)
	{
		pLastGrid=new UByte[GRID_SIZE];
		pHTextureGrid=new HTEXT[GRID_SIZE];
	 	memset(pLastGrid,0xFF,GRID_SIZE);
	 	memset(pHTextureGrid,0xFF,GRID_SIZE*sizeof(HTEXT));
	}

	ChangedTile* changedTiles=new ChangedTile[GRID_SIZE];
	NewTile* newTiles=new NewTile[GRID_SIZE];

 	if (lastPx!=px || lastPz!=pz)
 	{
 		if (lastPx!=-1 && lastPz!=-1)
 		{
 			Dropped* droppedTextures=new Dropped;
 			ScrollGrid(px-lastPx,pz-lastPz,pLastGrid);
 			ScrollGridDis(px-lastPx,pz-lastPz,pHTextureGrid,droppedTextures);
 			for (SLong i=droppedTextures->num;i>=0;i--)
			{
				if (!Save_Data.fSoftware)	currscreen->DoFreeTexture(droppedTextures->hText[i]);
				else						Three_Dee.pTMake->DoFreeTexture(droppedTextures->hText[i]);
			}
 			delete[]droppedTextures;
 		}
 		lastPx=px;
 		lastPz=pz;
 	}

	UByte* pnewgrid=new UByte[GRID_SIZE];
	memset(pnewgrid,0xFF,GRID_SIZE);

	ULong startPos=GRID_SIZE>>1;

	UByte* psrc=gridCone+startPos;
	UByte* pdst=pnewgrid+startPos;

	SLong h_dda,v_dda;

	UByte dir_state,dir_count,dir_max;

	UByte texture_scale,texture_count,texture_max;

	texture_scale=texture_count=0;
	texture_max=NUM_256_TEXTURES;
	
	dir_state=dir_count=0;
	dir_max=1;
	h_dda=1;
	v_dda=-wholeAreaSize;

	//check to see whether the very high detail textures have
	//been disabled!

	if (texture_max==0)
		while (texture_max==0)
		{
			texture_scale++;
			if (texture_scale==1)		texture_max=NUM_128_TEXTURES;
			else if (texture_scale==2)	texture_max=NUM_64_TEXTURES;
			else if (texture_scale==3)	texture_max=NUM_32_TEXTURES;
			else if (texture_scale==4)	texture_max=NUM_16_TEXTURES;
			else if (texture_scale==5)	texture_max=NUM_8_TEXTURES;
			else assert(false&&"ERROR: Run out of textures(1)");
		}

	for (SLong i=GRID_SIZE;i--;)
	{
		if (*psrc==1)
		{
			*pdst=texture_scale;
			texture_count++;
			if (texture_count==texture_max)
			{
				texture_scale++;
				texture_count=0;
				if (texture_scale==1)		texture_max=NUM_128_TEXTURES;
				else if (texture_scale==2)	texture_max=NUM_64_TEXTURES;
				else if (texture_scale==3)	texture_max=NUM_32_TEXTURES;
				else if (texture_scale==4)	texture_max=NUM_16_TEXTURES;
				else if (texture_scale==5)	texture_max=NUM_8_TEXTURES;
				else assert(false&&"ERROR: Run out of textures(2)");
			}
		}

		if (dir_state==0)
		{
			psrc+=h_dda;
			pdst+=h_dda;
			dir_count++;
			if (dir_count==dir_max)
			{
				dir_count=0;
				dir_state++;
			}
		}
		else
		{
			psrc+=v_dda;
			pdst+=v_dda;
			dir_count++;
			if (dir_count==dir_max)
			{
				h_dda=-h_dda;
				v_dda=-v_dda;
				dir_count=0;
				dir_state=0;
				dir_max++;
			}
		}
	}

	//compare the new grid with the old grid to determine
	//what texture updates are needed

	psrc=pnewgrid;
	pdst=pLastGrid;

	SLong new_tiles,changed_tiles;

	new_tiles=changed_tiles=0;

	for (i=GRID_SIZE;i--;psrc++,pdst++)
		if (*psrc!=*pdst)
		{
		 	//found a difference!!

			UByte srcVal=*psrc;
			UByte dstVal=*pdst;

			//test to see if a new tile that wasn't visible on the
			//last frame has just moved in to view

			if (dstVal==0xFF)
			{
				newTiles[new_tiles].newRez=srcVal;
				newTiles[new_tiles++].offset=
					(UWord)(ULong(pdst)-ULong(pLastGrid));
				*pdst=*psrc;
			}
			//test to see if a tile that was visible on the last frame
			//has just gone out of view

			else if (srcVal==0xFF)
			{
				UWord offset=(UWord)(ULong(pdst)-ULong(pLastGrid));
				if (!Save_Data.fSoftware)	currscreen->DoFreeTexture(*(pHTextureGrid+offset));
				else						Three_Dee.pTMake->DoFreeTexture(*(pHTextureGrid+offset));
				*(pHTextureGrid+offset)=HTEXTNULL;
				*pdst=*psrc;
			}
			//the difference must be due to a tile resolution change

			else
			{
				UWord offset=(UWord)(ULong(pdst)-ULong(pLastGrid));
				changedTiles[changed_tiles].oldHTexture=*(pHTextureGrid+offset);
				if (!Save_Data.fSoftware)	currscreen->DoFreeTexture(changedTiles[changed_tiles].oldHTexture);
				else						Three_Dee.pTMake->DoFreeTexture(changedTiles[changed_tiles].oldHTexture);
				*(pHTextureGrid+offset)=HTEXTNULL;
				changedTiles[changed_tiles].newRez=srcVal;
				changedTiles[changed_tiles++].offset=offset;
			}
		}

	//deal with any tile resolution changes

	ChangedTile* pct=changedTiles;

	while (changed_tiles--)
	{
		//release the old tile
		UWord offset=pct->offset;
		*(pLastGrid+offset)=pct->newRez;
		HTEXT newTH;
		if (!Save_Data.fSoftware)	
		{
			currscreen->DoFreeTexture(*(pHTextureGrid+offset));
			newTH=currscreen->DoAllocateTexture(pct->newRez);
		}
		else
		{
			Three_Dee.pTMake->DoFreeTexture(*(pHTextureGrid+offset));
			newTH=Three_Dee.pTMake->DoAllocateTexture(pct->newRez);
		}
		*(pHTextureGrid+offset)=newTH;

		//render the tile colour data to this DD surface

		if (newTH!=HTEXTNULL)
			Three_Dee.pTMake->Render2Surface(newTH,pct->newRez,offset);
		pct++;
	}

	NewTile* pnt=newTiles;

	while (new_tiles--)
	{
		UWord offset=pnt->offset;
		HTEXT newTH;
		if (!Save_Data.fSoftware)	newTH=currscreen->DoAllocateTexture(pnt->newRez);
		else						newTH=Three_Dee.pTMake->DoAllocateTexture(pnt->newRez);
		*(pHTextureGrid+offset)=newTH;

		//render the tile colour data to this DD surface

		if (newTH!=HTEXTNULL)
			Three_Dee.pTMake->Render2Surface(newTH,pnt->newRez,offset);
		pnt++;
	}

	delete[]pnewgrid;
	delete[]changedTiles;
	delete[]newTiles;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillDataGrid
//Author		Paul.   
//Date			Thu 14 May 1998
//------------------------------------------------------------------------------
bool LandScape::FillDataGrid(SLong ox,SLong oz)
{
	Three_Dee.pMigLand->ResetDecompCount();
	SLong ix;
	UByte* pConeData=gridCone;
	DataRecord* dataBlock=pDataBlocks;
	UByte* pGroundDetail=groundDetail;

	SLong wholeAreaSize=_wholeAreaSizeMIN;

	for (int row=0;row<wholeAreaSize;row++)
	{
		ix=ox;
	 	for (int col=0;col<wholeAreaSize;col++)
		{
			if (*pConeData)
			{
				//Fill in array of land data pointers for later

				DataRecord& dR=*dataBlock;
				UByte gD=*pGroundDetail;
				dR=Three_Dee.pTMake->GetBlock(ix,oz);
				dR=Three_Dee.pMigLand->GetData(ix,oz,gD,dR);
			}
			else
			{
				DataRecord& dR=*dataBlock;
			 	dR.pData=NULL;
				dR.dataLen=0;
			}
			pConeData++;
			dataBlock++;
			pGroundDetail++;
			ix+=_blockWidth;
		}
		oz+=_blockWidth;
	}

	dataBlock=pDataBlocks;
	for (row=wholeAreaSize*wholeAreaSize;row>0;row--)
	{
		DataRecord& dR=*dataBlock;
		if (dR.pData)
		{
			AltPointsHdr *aph=(AltPointsHdr*)dR.pData;
			if (!aph->CheckChecksum())
				return false;
			//if (aph->vertexCount<4 || 
			//	aph->vertexCount<aph->topEdgePoints+aph->rightEdgePoints+aph->bottomEdgePoints+aph->leftEdgePoints)
			//	return false;
		}
		dataBlock++;
	}
	return true;
}

SLong ibase_x,ibase_z,iscale_factor,itexture;

//DEAD static SLong softwarePolyCount;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GeneratePointData
//Author		Paul.   
//Date			Tue 20 Jan 1998
//------------------------------------------------------------------------------
bool LandScape::GeneratePointData()
{
	SLong gx,gz;
	gx=viewer_x;
	gz=viewer_z;
	Three_Dee.pMigLand->SetViewpoint(View_Point);
	Three_Dee.pMigLand->ProcessSeekRequests();
	Three_Dee.pTMake->ChkUpdate(gx,gz);

	SLong ox,oz;

	View_Point->isLightShaded=TRUE;
	currscreen->DoSetLShade(true);
	currscreen->DoSetRangeFog(true);
	currscreen->DoEnableBackClip(FALSE);

	bAnyLandDrawn=FALSE;

	//Generate start position based on the current viewpoint

	SLong halfAreaSize=_halfAreaSizeMIN;
	SLong wholeAreaSize=_wholeAreaSizeMIN;

	ox=(gx&~ULong(_blockWidth-1))-halfAreaSize*_blockWidth;
	oz=(gz&~ULong(_blockWidth-1))-halfAreaSize*_blockWidth;

	if (!Three_Dee.pTMake->CheckCache())
	{
		RefreshLandscape();
		return false;
	}
	GridCone(ox,oz);
	ManageHighLandTextures(ox,oz);
	if (!FillDataGrid(ox,oz))
	{
		RefreshLandscape();
		return false;
	}
	ProcessLights(ox,oz);
	HighDetailTileRender(ox,oz);
	currscreen->DoEnableBackClip(TRUE);
	currscreen->DoSetLShade(false);
	currscreen->DoSetRangeFog(false);
	View_Point->isLightShaded=FALSE;
	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StandardTileRender
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void LandScape::StandardTileRender(SLong ox,SLong oz)
{
	Rect boxes[6];
	SquareClips* psc;

	Three_Dee.pTMake->GetSquares(boxes);
	Three_Dee.pTMake->GetTileClipData(psc);

	SLong wholeAreaSize=_wholeAreaSizeMIN;

	COORDS3D view;

	UByte* pConeData=gridCone;
	UByte* pGroundDetail=groundDetail;
	DataRecord* dataBlock=pDataBlocks;

	view.Y=-viewer_y;

	for (int row=0;row<wholeAreaSize;row++,oz+=_blockWidth)
	{
		view.Z=oz;
		SLong ix=ox;

		for (int col=0;col<wholeAreaSize;col++,ix+=_blockWidth)
		{
			view.X=ix;

			if (*pConeData++)
			{
				UByte groundDetail;
				ULong dataLen;
				UByte* pDataStream;

				groundDetail=*pGroundDetail++;

				dataLen=dataBlock->dataLen;
				pDataStream=(UByte*)dataBlock->pData;

				UByte* psavedata=pDataStream;

				if (psc->count==0)
				{
					itexture=psc->clipInfo[0].level;
					ibase_x=boxes[itexture].l;
					ibase_z=boxes[itexture].b;
					iscale_factor=9+itexture;
					UnclippedTile(pDataStream,dataLen,view);
				}
				else
				{
					UByte* pds;
					ULong dl;
					for (int clips=0;clips<psc->count;clips++)
					{
						Rect clip;
						pds=pDataStream;
						dl=dataLen;

						itexture=psc->clipInfo[clips].level;
						ibase_x=boxes[itexture].l;
						ibase_z=boxes[itexture].b;
						iscale_factor=9+itexture;

						//now get the clip area
						Three_Dee.pTMake->GetClipRegion(psc->clipInfo[clips].clipRecIndex,clip);

						ClippedTile(pds,dl,view,clip);
					}
					pDataStream=pds;
					dataLen=dl;
				}
				if (groundDetail==UByte(_doHighGround))
				{
					RenderTrees(psavedata,view);
				}
			}
			else
			{
				pGroundDetail++;
			}
			dataBlock++;
			psc++;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HighDetailTileRender
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void LandScape::HighDetailTileRender(SLong ox,SLong oz)
{
	SLong wholeAreaSize=_wholeAreaSizeMIN;

	COORDS3D view;

	UByte* pConeData=gridCone;
	UByte* pLightCone=lightCone;
	UByte* pGroundDetail=groundDetail;
	HTEXT* pTextureHandles=pHTextureGrid;
	DataRecord* dataBlock=pDataBlocks;

	view.Y=-viewer_y;

	//generate a value for 'treeHeight'

	if (viewer_y>FT_10000)		treeHeight=0;
	else if (viewer_y<FT_5000)	treeHeight=TREE_HEIGHT;
	else						treeHeight=TREE_HEIGHT-(TREE_HEIGHT*(viewer_y-FT_5000)/(FT_10000-FT_5000));

	for (int row=0;row<wholeAreaSize;row++,oz+=_blockWidth)
	{
		view.Z=oz;
		SLong ix=ox;

		for (int col=0;col<wholeAreaSize;col++,ix+=_blockWidth)
		{
			view.X=ix;

			if (*pConeData++)
			{
				UByte groundDetail;
				HTEXT textureHandle,nullHandle;
				ULong dataLen;
				UByte* pDataStream;

				textureHandle=*pTextureHandles++;
				groundDetail=*pGroundDetail++;

				if (textureHandle!=nullHandle)
				{
					if (lightsActive) lightMe=*pLightCone;

					dataLen=dataBlock->dataLen;
					UByte* psavedata=pDataStream=(UByte*)dataBlock->pData;

					HiRezTile(pDataStream,dataLen,view,textureHandle);

					if (groundDetail==UByte(_doHighGround))
						RenderTrees(psavedata,view);
				}
			}
			else
			{
				pGroundDetail++;
				pTextureHandles++;
			}
			dataBlock++;
			pLightCone++;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FanClipTest
//Author		Paul.   
//Date			Tue 2 Jun 1998
//
//Returns		true => fan can be drawn un-clipped
//				false=> fan requires clipping
//
//------------------------------------------------------------------------------
bool LandScape::FanClipTest(UByte* pFanData)
{
//test the fan to see if it can be drawn un-clipped

	if (!bDoingHardware3D) return false;

	int triCnt=*pFanData++;	//no of triangles in the fan

	triCnt+=2;	//no of points in the fan

	while (triCnt--) if (SHAPE.newco[*pFanData++].clipFlags!=CF3D_NULL) return false;

	return true;
}

//const int _altitudeScale=50;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VHighDetailTile
//Author		Paul.   
//Date			Sat 16 May 1998
//------------------------------------------------------------------------------
int LandScape::VHighDetailTile(	ULong hTexture,
								UByte*& pDS,
								ULong& dataLen,
								COORDS3D& viewCoords)
{
	UByte* pDataStream=pDS;

	//Now render this texture over the whole tile...
	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
	int	vertexCount=aph.vertexCount;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pPointDefs=(PointDef*)pDataStream;

	COORDS3D* pCoordData=tileCoords;
	DoPointStruc* pPoints=SHAPE.newco;
	
	UWord clipTest=0;

	for (int t=0;t<vertexCount;t++){
		//3d coordinate buffer will do for storing
		//this load of vertex information
		COORDS3D& tile=*pCoordData++;
		PointDef& apd=*pPointDefs++;
		DoPointStruc& dp=*pPoints++;

		tile.X=apd.x;
		tile.Z=256-apd.z;
		tile.Y=apd.alt;
		dp.ix=tile.X;
		dp.iy=apd.z;
	
		//Now, scale the points
		tile.X<<=9;
		tile.Z<<=9;
		tile.Y*=_altitudeScale;
		dp.bodyx.i=viewCoords.X+tile.X;
		dp.bodyy.i=tile.Y;
		if (mistenabled) SetMist(dp);
		dp.bodyy.i+=viewCoords.Y;
		dp.bodyz.i=viewCoords.Z+tile.Z;

		dp.intensity=apd.shadeVal;
		dp.specular=-1;

		//And, transform the points...
		_matrix.transform(fpviewer_matrix,dp);

		clipTest|=dp.clipFlags;

		if (!bDoingHardware3D) _matrix.body2screen(dp);
	}

	pDataStream=(UByte*)pPointDefs;
	pPoints=SHAPE.newco;

	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;
	pDataStream+=sizeof(ddh);

	int	polyCount=ddh.noOfPolys;
	int lineCount=ddh.noOfLines;
	int totalTriCount=ddh.totalTris;

	if (clipTest==0)
	{
		currscreen->DoNearAddTile(	vertexCount,
									totalTriCount,
									SHAPE.newco,
									polyCount,
									pDataStream,
									hTexture);
	}
	else
	{
		currscreen->DoCNearAddTile(	vertexCount,
									totalTriCount,
									SHAPE.newco,
									polyCount,
									pDataStream,
									hTexture);
	}

	pDS=pDataStream;
	return lineCount;
}

void LandScape::AddTile(ULong ,ULong ,DoPointStruc* pdp,ULong drwCnt,UByte*& pdd,const HTEXT& hT)
{
	UByte* pdrawdata=pdd;
//DEAD	ROWANSURFACEDESC* rsd=Three_Dee.pTMake->GetRSD(hT);
	while (drwCnt--)
	{
		pdrawdata++;				//skip colour byte
		ULong fanCnt=*pdrawdata++;
		while (fanCnt--){
			ULong triCnt=*pdrawdata++;
			int v1=*pdrawdata++;
			int v2=*pdrawdata++;
			int v3=*pdrawdata++;

			if ((SHAPE.newco[v1].clipFlags & SHAPE.newco[v2].clipFlags & SHAPE.newco[v3].clipFlags)==0)
			{
				Land_Obj* loptr=(Land_Obj*)Three_Dee.bt->Get3DArea(GROUND_TILE_OBJECT);
				loptr->hMaterial=hT;
				loptr->bx[0]=SHAPE.newco[v1].bodyx.f;
				loptr->bx[1]=SHAPE.newco[v2].bodyx.f;
				loptr->bx[2]=SHAPE.newco[v3].bodyx.f;
				loptr->by[0]=SHAPE.newco[v1].bodyy.f;
				loptr->by[1]=SHAPE.newco[v2].bodyy.f;
				loptr->by[2]=SHAPE.newco[v3].bodyy.f;
				loptr->bz[0]=SHAPE.newco[v1].bodyz.f;
				loptr->bz[1]=SHAPE.newco[v2].bodyz.f;
				loptr->bz[2]=SHAPE.newco[v3].bodyz.f;
				loptr->u[0]=SHAPE.newco[v1].ix;
				loptr->u[1]=SHAPE.newco[v2].ix;
				loptr->u[2]=SHAPE.newco[v3].ix;
				loptr->v[0]=SHAPE.newco[v1].iy;
				loptr->v[1]=SHAPE.newco[v2].iy;
				loptr->v[2]=SHAPE.newco[v3].iy;
				loptr->clipFlags[0]=SHAPE.newco[v1].clipFlags;
				loptr->clipFlags[1]=SHAPE.newco[v2].clipFlags;
				loptr->clipFlags[2]=SHAPE.newco[v3].clipFlags;
				Float max_z=0;
				for (int i=2;i>=0;i--)	if (loptr->bz[i]>max_z) max_z=loptr->bz[i];
				loptr->bodyz.f=loptr->realbz.f=max_z;
				Three_Dee.bt->insert_object(loptr);
			}
			triCnt--;
			while (triCnt--)
			{
				v2=v3;
				v3=*pdrawdata++;
				if ((SHAPE.newco[v1].clipFlags & SHAPE.newco[v2].clipFlags & SHAPE.newco[v3].clipFlags)==0)
				{
					Land_Obj* loptr=(Land_Obj*)Three_Dee.bt->Get3DArea(GROUND_TILE_OBJECT);
					loptr->hMaterial=hT;
					loptr->bx[0]=SHAPE.newco[v1].bodyx.f;
					loptr->bx[1]=SHAPE.newco[v2].bodyx.f;
					loptr->bx[2]=SHAPE.newco[v3].bodyx.f;
					loptr->by[0]=SHAPE.newco[v1].bodyy.f;
					loptr->by[1]=SHAPE.newco[v2].bodyy.f;
					loptr->by[2]=SHAPE.newco[v3].bodyy.f;
					loptr->bz[0]=SHAPE.newco[v1].bodyz.f;
					loptr->bz[1]=SHAPE.newco[v2].bodyz.f;
					loptr->bz[2]=SHAPE.newco[v3].bodyz.f;
					loptr->u[0]=SHAPE.newco[v1].ix;
					loptr->u[1]=SHAPE.newco[v2].ix;
					loptr->u[2]=SHAPE.newco[v3].ix;
					loptr->v[0]=SHAPE.newco[v1].iy;
					loptr->v[1]=SHAPE.newco[v2].iy;
					loptr->v[2]=SHAPE.newco[v3].iy;
					loptr->clipFlags[0]=SHAPE.newco[v1].clipFlags;
					loptr->clipFlags[1]=SHAPE.newco[v2].clipFlags;
					loptr->clipFlags[2]=SHAPE.newco[v3].clipFlags;
					Float max_z=0;
					for (int i=2;i>=0;i--)	if (loptr->bz[i]>max_z) max_z=loptr->bz[i];
					loptr->bodyz.f=loptr->realbz.f=max_z;
					Three_Dee.bt->insert_object(loptr);
				}
			}
		}
	}
	pdd=pdrawdata;
}

void btree::drw_special_land(BaseObj3DPtr this_obj3d)
{
	if (OverLay.fZoomedMap)
	{
		SWord qx,qy,qw,qh;
		POLYGON.PushViewData();
		qx=SWord(float(6)*float(OverLay.physicalWidth)/640.);
		qw=SWord(float(316)*float(OverLay.physicalWidth)/640.);
		qy=SWord(float(1)*float(OverLay.physicalHeight)/480.);
		qh=SWord(float(438)*float(OverLay.physicalHeight)/480.);
		POLYGON.Set3DWin(qx,qy,qw,qh);
	}
	LandObj3DPtr real_obj3d=(LandObj3DPtr )this_obj3d;
	Land_Scape.RenderSpecialLandPoly(real_obj3d);
	if (OverLay.fZoomedMap)
		POLYGON.PopViewData();
}
void LandScape::RenderSpecialLandPoly(LandObj3DPtr ptr)
{
	bool f=POLYGON.SetPerspectiveCorrection(true);
	ROWANSURFACEDESC* rsd=Three_Dee.pTMake->GetRSD(ptr->hMaterial);
	POLYGON.createpoly(rsd,ptr->bodyz.f);
	DoPointStruc dp;
	for (int i=0;i<3;i++)
	{
		dp.bodyx.f=ptr->bx[i];
		dp.bodyy.f=ptr->by[i];
		dp.bodyz.f=ptr->bz[i];
		dp.ix=ptr->u[i];
		dp.iy=ptr->v[i];
		dp.clipFlags=ptr->clipFlags[i];
		POLYGON.softwarevert(dp);
	}
	POLYGON.drawpoly();
	POLYGON.SetPerspectiveCorrection(f);
}
void btree::drw_land(BaseObj3DPtr this_obj3d)
{
	if (OverLay.fZoomedMap)
	{
		SWord qx,qy,qw,qh;
		POLYGON.PushViewData();
		qx=SWord(float(6)*float(OverLay.physicalWidth)/640.);
		qw=SWord(float(316)*float(OverLay.physicalWidth)/640.);
		qy=SWord(float(1)*float(OverLay.physicalHeight)/480.);
		qh=SWord(float(438)*float(OverLay.physicalHeight)/480.);
		POLYGON.Set3DWin(qx,qy,qw,qh);
	}
	LandObj3DPtr real_obj3d=(LandObj3DPtr )this_obj3d;
	Land_Scape.RenderLandPoly(real_obj3d);
	if (OverLay.fZoomedMap)
		POLYGON.PopViewData();
}
void LandScape::RenderLandPoly(LandObj3DPtr ptr)
{
	bool f=POLYGON.SetPerspectiveCorrection(true);
	ROWANSURFACEDESC* rsd=Three_Dee.pTMake->GetRSD(ptr->hMaterial);
	POLYGON.createpoly(rsd,ptr->bodyz.f);
	DoPointStruc dp;
	for (int i=0;i<3;i++)
	{
		dp.bodyx.f=ptr->bx[i];
		dp.bodyy.f=ptr->by[i];
		dp.bodyz.f=ptr->bz[i];
		dp.ix=ptr->u[i];
		dp.iy=ptr->v[i];
		dp.clipFlags=ptr->clipFlags[i];
		POLYGON.createvert(dp,dp.ix,dp.iy);
	}
	POLYGON.drawpoly();
	POLYGON.SetPerspectiveCorrection(f);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderWaves
//Author		Paul.   
//Date			Tue 24 Nov 1998
//------------------------------------------------------------------------------
void LandScape::RenderWaves(UByte* pds,COORDS3D& view)
{
/*	fpCOORDS3D wavePos;

	if (gameSettings.m_bTreesEnabled==false) return;

	AltPointsHdr& aph=*(AltPointsHdr*)pds;

	pds+=sizeof(AltPointsHdr)+aph.vertexCount*sizeof(PointDef);

	DrawDataHdr& ddh=*(DrawDataHdr*)pds;

	pds+=sizeof(DrawDataHdr);

	if (ddh.noOfWaves==0) return;

	SLong waveCount=ddh.noOfWaves;

	SmallPoint* psp=(SmallPoint*)(ULong(&aph)+ULong(ddh.waveOffset));

	SLong treeRnd=viewer_x^viewer_y^viewer_z;
	treeRnd=perm(treeRnd);

	while (waveCount--)
	{
		wavePos.X.i=((psp->x<<9)+view.X)-viewer_x+SByte(treeRnd);
		treeRnd=perm(treeRnd);
		wavePos.Y.i=50+(psp->alt*_altitudeScale)-viewer_y;
		wavePos.Z.i=(((256-psp->z)<<9)+view.Z)-viewer_z+SByte(treeRnd);
		treeRnd=perm(treeRnd);

		_matrix.transform(fpviewer_matrix,wavePos.X,wavePos.Y,wavePos.Z);
		UWord clipFlag=_matrix.GenClipFlags(wavePos);

		if (clipFlag==0)
		{
			POINTTYPE point;
			vertex vert;
			point.lpVertex=&vert;
			vert.bx.f=wavePos.X.f;
			vert.by.f=wavePos.Y.f;
			vert.bz.f=wavePos.Z.f;
			vert.clipFlags=CF3D_NULL;
			point.ptType=PointType::PT_PlainColour;
			point.colour=WHITE;
			currscreen->DoHardPoint(&point);
		}
		psp++;
	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTrees
//Author		Paul
//Date			Fri 14 Aug 1998
//------------------------------------------------------------------------------
void LandScape::RenderTrees(UByte* pds,COORDS3D& view)
{
	if (!((!Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS]) ||
		View_Ground_Height>6*FT_250))
	{
	Float dx,dz;
	dx=Float(view.X-viewer_x);
	dz=Float(view.Z-viewer_z);

	Float dd=dx*dx+dz*dz;

	_asm {fld dd;
	fsqrt;
	fstp dd;
	}

	if (SLong(dd)>24*FT_250) return;

	ShapeNum treeShapes[]={TREE1,TREE2,TREE3,TREE4};

	AltPointsHdr& aph=*(AltPointsHdr*)pds;

	pds+=sizeof(AltPointsHdr)+aph.vertexCount*sizeof(PointDef);

	DrawDataHdr& ddh=*(DrawDataHdr*)pds;

	pds+=sizeof(DrawDataHdr);

	if (ddh.noOfTrees==0) return;

	SLong treeCount=ddh.noOfTrees;

	item dummyItem;

	dummyItem.Anim=CloudAnimP;

	SmallPoint* psp=(SmallPoint*)(ULong(&aph)+ULong(ddh.treeOffset));

	SLong treeRnd=perm(ddh.treeOffset>>3);

	while (treeCount--)
	{
		dummyItem.shape=treeShapes[treeRnd&3];
		dummyItem.World.X=(psp->x<<9)+view.X;
		dummyItem.World.Y=(psp->alt*_altitudeScale);
		dummyItem.World.Z=((256-psp->z)<<9)+view.Z;
		//only add trees to empty sectors. Doesn't take sector
		//wrapping into account
		Three_Dee.do_object_dummy(&dummyItem);				//RJS 30Nov98DONT FUCKINGREMOVE!!!!!
		psp++;
		treeRnd=perm(treeRnd);
	}
	dummyItem.Anim=NULL;
	}
	currscreen->DoSetShadeVals(currentLighting.landAmbientCol.red(),
								currentLighting.landAmbientCol.green(),
								currentLighting.landAmbientCol.blue(),
								currentLighting.effectsAmbientCol.red(),
								currentLighting.effectsAmbientCol.green(),
								currentLighting.effectsAmbientCol.blue());
	View_Point->isLightShaded=TRUE;
	currscreen->DoSetLShade(true);
	currscreen->DoSetRangeFog(true);
	currscreen->DoEnableBackClip(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlotNormal
//Author		Paul.   
//Date			Thu 7 Jan 1999
//------------------------------------------------------------------------------
/*void PlotNormal(FPMATRIX* fpviewer_matrix,DoPointStruc* pdp,Window* curScr)
{
	LINETYPE	ltLine;
	DoPointStruc	temp;
	struct		vertex	startVertex,endVertex;

//	if (pdp->intensity<0 || pdp->intensity>255)
//		_asm {int 3}

	ltLine.ltType 			= LineType::LT_PlainColour;
	ltLine.colour			= Colour(0x14);	//ARTWORKMASK;
	ltLine.lpStartVertex 	= &startVertex;
	ltLine.lpEndVertex 		= &endVertex;

	temp=*pdp;
	_matrix.transform(fpviewer_matrix,temp);

	startVertex.bx			= temp.bodyx;
	startVertex.by			= temp.bodyy;
	startVertex.bz			= temp.bodyz;
	startVertex.clipFlags	= temp.clipFlags;
	startVertex.intensity	= 0xFF;

	temp=*pdp;
	temp.bodyx.i+=SLong(Three_Dee.normalDataPtr[pdp->intensity].i*10000);
	temp.bodyy.i+=SLong(Three_Dee.normalDataPtr[pdp->intensity].j*10000);
	temp.bodyz.i+=SLong(Three_Dee.normalDataPtr[pdp->intensity].k*10000);
	_matrix.transform(fpviewer_matrix,temp);

	endVertex.bx.f			= temp.bodyx.f;
	endVertex.by.f			= temp.bodyy.f;
	endVertex.bz.f			= temp.bodyz.f;
	endVertex.clipFlags		= temp.clipFlags;
	endVertex.intensity		= 0xFF;

	curScr->DoHardLine(&ltLine);
}*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnclippedTile
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
int LandScape::UnclippedTile(UByte*& pDS,ULong& dataLen,COORDS3D& view)
{

	UByte* pDataStream=pDS;

	//Now render this texture over the whole tile...
	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
	int	vertexCount=aph.vertexCount;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pPointDefs=(PointDef*)pDataStream;

	COORDS3D* pCoordData=tileCoords;
	DoPointStruc* pPoints=SHAPE.newco;
	
	UWord clipTest=0;

	for (int t=0;t<vertexCount;t++){
		//3d coordinate buffer will do for storing
		//this load of vertex information
		PointDef& apd=*pPointDefs++;
		DoPointStruc& dp=*pPoints++;

		dp.bodyx.i=(apd.x<<9)+view.X;
		dp.bodyy.i=apd.alt*_altitudeScale;
		dp.bodyz.i=((256-apd.z)<<9)+view.Z;

		dp.ix=(dp.bodyx.i-ibase_x)>>iscale_factor;
		dp.iy=(dp.bodyz.i-ibase_z)>>iscale_factor;

		dp.specular=-1;

		//And, transform the points...

		dp.bodyx.i-=viewer_x;
		dp.bodyy.i-=viewer_y;
		dp.bodyz.i-=viewer_z;

		dp.intensity=apd.shadeVal;
		//PlotNormal(fpviewer_matrix,&dp,currscreen);

		if (!Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])
			dp.intensity=0xFF;
		else
			dp.intensity=Three_Dee.pNormalLookup[apd.shadeVal];

		_matrix.transform(fpviewer_matrix,dp);

		clipTest|=dp.clipFlags;

		if (!bDoingHardware3D) _matrix.body2screen(dp);
	}

	pDataStream=(UByte*)pPointDefs;
	pPoints=SHAPE.newco;

	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;
	pDataStream+=sizeof(ddh);

	int	polyCount=ddh.noOfPolys;
	int lineCount=ddh.noOfLines;
	int totalTriCount=ddh.totalTris;

	if (clipTest==0)
	{
		currscreen->DoNearAddTile(	vertexCount,
									totalTriCount,
									SHAPE.newco,
									polyCount,
									pDataStream,
									itexture);
	}
	else
	{
		currscreen->DoCNearAddTile(	vertexCount,
									totalTriCount,
									SHAPE.newco,
									polyCount,
									pDataStream,
									itexture);
	}

	pDS=pDataStream;
	return lineCount;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HiRezTile
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void LandScape::HiRezTile(UByte*& pDS,ULong& dataLen,COORDS3D& view,const HTEXT& hTexture)
{
	UWord flag;

	if (Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS] && treeHeight!=0) flag=0;
	else flag=2;

	UByte* pDataStream=pDS;

	SWord iscale=0;
	if (Save_Data.fSoftware)
	{
		ROWANSURFACEDESC* rsd=Three_Dee.pTMake->GetRSD(hTexture);
		if (rsd->dwWidth<256)	iscale++;
		if (rsd->dwWidth<128)	iscale++;
		if (rsd->dwWidth<64)	iscale++;
	}
	if (Save_Data.fSoftware && !iscale)
	{
		SoftTile(pDS,dataLen,view,hTexture);
		return;
	}
	SWord imax=(1<<(8-iscale))-1;

	//Now render this texture over the whole tile...
	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
	int	vertexCount=aph.vertexCount;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pPointDefs=(PointDef*)pDataStream;

	COORDS3D* pCoordData=tileCoords;
	DoPointStruc* pPoints=SHAPE.newco;
	
	UWord clipTest=0;

	for (int t=0;t<vertexCount;t++)
	{
		//3d coordinate buffer will do for storing
		//this load of vertex information
		PointDef& apd=*pPointDefs++;
		DoPointStruc& dp=*pPoints++;

		dp.bodyx.i=(apd.x<<9)+view.X;
		dp.bodyy.i=apd.alt*_altitudeScale;
		dp.bodyz.i=((256-apd.z)<<9)+view.Z;

		dp.ix=apd.x;
		dp.iy=256-apd.z;

		if (iscale)
		{
			dp.ix>>=iscale;
			dp.iy>>=iscale;
		}
		if (Save_Data.fSoftware)
		{
			if (dp.ix>imax) dp.ix=imax;
			if (dp.iy>imax) dp.iy=imax;
		}

		dp.specular=-1;

		//And, transform the points...

		dp.bodyx.i-=viewer_x;
		dp.bodyy.i-=viewer_y;
		dp.bodyz.i-=viewer_z;

		dp.intensity=apd.shadeVal;
		if (Save_Data.fSoftware || !Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])
			dp.intensity=0xFF;
		else
		{
			dp.intensity=Three_Dee.pNormalLookup[apd.shadeVal];
			if (dp.intensity!=0xFF && lightsActive && lightMe!=0xFF)
			{
				//add lighting information to this vertex...
				for (SLong q=0;q<lightTable[lightMe].numLights && dp.intensity!=0xFF;q++)
				{
					SLong lindex=lightTable[lightMe].lightIndices[q];
					SLong lx0,lx1,lz0,lz1,lrange;
					lx0=lx1=lightList[lindex].pos.X-viewer_x;
					lz0=lz1=lightList[lindex].pos.Z-viewer_z;
					lrange=lightList[lindex].range;
					lx0-=lrange; lx1+=lrange;
					lz0-=lrange; lz1+=lrange;
					if (dp.bodyx.i>=lx0 &&
						dp.bodyx.i<=lx1 &&
						dp.bodyz.i>=lz0 &&
						dp.bodyz.i<=lz1)
						dp.intensity=0xFF;
				}
			}
		}

		_matrix.transform(fpviewer_matrix,dp);

		clipTest|=dp.clipFlags;
	}

	pDataStream=(UByte*)pPointDefs;
	pPoints=SHAPE.newco;

	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;
	pDataStream+=sizeof(ddh);

	int	polyCount=ddh.noOfPolys;
	int totalTriCount=ddh.totalTris;

	UByte* saveDS=pDataStream;

	currscreen->DoSetShadeVals(currentLighting.landAmbientCol.red(),
							currentLighting.landAmbientCol.green(),
							currentLighting.landAmbientCol.blue(),
							currentLighting.effectsAmbientCol.red(),
							currentLighting.effectsAmbientCol.green(),
							currentLighting.effectsAmbientCol.blue());

	View_Point->isLightShaded=TRUE;
	currscreen->DoSetLShade(true);
	currscreen->DoSetRangeFog(true);
	currscreen->DoEnableBackClip(FALSE);

	if (Save_Data.fSoftware)
	{
		AddTile(vertexCount,totalTriCount,SHAPE.newco,polyCount,pDataStream,hTexture);
	}
	else if (clipTest==0)
	{
		currscreen->DoNearAddTileX(	vertexCount,
									totalTriCount,
									SHAPE.newco,
									polyCount,
									pDataStream,
									hTexture,flag);
	}
	else
	{
		currscreen->DoCNearAddTileX(vertexCount,
									totalTriCount,
									SHAPE.newco,
									polyCount,
									pDataStream,
									hTexture,flag);
	}

	pDataStream=saveDS;

	if (!Save_Data.fSoftware && Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS] && treeHeight!=0)
	{
		clipTest=0;

		Float ddx,ddy,ddz;

		ddx=Float(treeHeight)*fpviewer_matrix->L12;
		ddy=Float(treeHeight)*fpviewer_matrix->L22;
		ddz=Float(treeHeight)*fpviewer_matrix->L32;

		for (t=0;t<vertexCount;t++)
		{
			highco[t]=SHAPE.newco[t];
			highco[t].bodyx.f+=ddx;
			highco[t].bodyy.f+=ddy;
			highco[t].bodyz.f+=ddz;
			_matrix.SetClipFlags(highco[t]);
			clipTest|=highco[t].clipFlags;
		}

		if (clipTest==0)
		{
			currscreen->DoNearAddTileX(	vertexCount,
										totalTriCount,
										highco,
										polyCount,
										pDataStream,
										hTexture,1);
		}
		else
		{
			currscreen->DoCNearAddTileX(vertexCount,
										totalTriCount,
										highco,
										polyCount,
										pDataStream,
										hTexture,1);
		}

		//and now for the tree trunks

		pDataStream=saveDS;

		while (polyCount--)
		{
		 	UByte at=*pDataStream++;
			ULong fanCount=*pDataStream++;
			if (IsForest(at))
			{
				while (fanCount--)
				{
					ULong triCount=(*pDataStream++)+1;
					ULong last,first,save;
					first=save=*pDataStream++;
					SWord DeltaIX,DeltaIZ,other=0;

					while (triCount--)
					{
						last=first;
						first=*pDataStream++;
						if ((CF3D_ALL &
							SHAPE.newco[first].clipFlags &
							SHAPE.newco[last].clipFlags &
							highco[first].clipFlags &
							highco[last].clipFlags)==0)
						{
							//work out texture tiling coords
							DeltaIX=highco[last].ix-highco[first].ix;
							if (DeltaIX<0) DeltaIX=-DeltaIX;
							DeltaIZ=highco[last].iy-highco[first].iy;
							if (DeltaIZ<0) DeltaIZ=-DeltaIZ;
							if (DeltaIX<DeltaIZ) DeltaIX=DeltaIZ;

							DeltaIX<<=5;
							DeltaIZ=64;

							POLYGON.createpoly(WOODNO);
							POLYGON.createvert(highco[first],other,other);
							POLYGON.createvert(highco[last],DeltaIX,other);
							POLYGON.createvert(SHAPE.newco[last],DeltaIX,DeltaIZ);
							POLYGON.createvert(SHAPE.newco[first],other,DeltaIZ);
							POLYGON.drawpoly();
						}
					}

					if ((CF3D_ALL &
						SHAPE.newco[first].clipFlags &
						SHAPE.newco[save].clipFlags &
						highco[first].clipFlags &
						highco[save].clipFlags)==0)
					{
						//work out texture tiling coords
						DeltaIX=highco[first].ix-highco[save].ix;
						if (DeltaIX<0) DeltaIX=-DeltaIX;
						DeltaIZ=highco[first].iy-highco[save].iy;
						if (DeltaIZ<0) DeltaIZ=-DeltaIZ;
						if (DeltaIX<DeltaIZ) DeltaIX=DeltaIZ;

						DeltaIX<<=5;
						DeltaIZ=64;

						POLYGON.createpoly(WOODNO);
						POLYGON.createvert(highco[save],other,other);
						POLYGON.createvert(highco[first],DeltaIX,other);
						POLYGON.createvert(SHAPE.newco[first],DeltaIX,DeltaIZ);
						POLYGON.createvert(SHAPE.newco[save],other,DeltaIZ);
						POLYGON.drawpoly();
					}
				}
			}
			else while (fanCount--)
			{
				ULong triCount=*pDataStream++;
				pDataStream+=2;
				while (triCount--) pDataStream++;
			}
		}
	}
	pDataStream=saveDS;
	pDS=pDataStream;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SoftTile
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
void LandScape::SoftTile(UByte*& pDS,ULong& dataLen,COORDS3D& view,const HTEXT& hTexture)
{
	UByte* pDataStream=pDS;

	SWord iscale=0;
	ROWANSURFACEDESC* rsd=Three_Dee.pTMake->GetRSD(hTexture);
	if (rsd->dwWidth<256)	iscale++;
	if (rsd->dwWidth<128)	iscale++;
	if (rsd->dwWidth<64)	iscale++;
	SWord imax=(1<<(8-iscale))-1;
	iscale=7-iscale;

	//Now render this texture over the whole tile...
	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
	int	vertexCount=aph.vertexCount;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pPointDefs=(PointDef*)pDataStream;

	COORDS3D* pCoordData=tileCoords;
	DoPointStruc* pPoints=SHAPE.newco;
	
	UWord clipTest=0;

	for (int t=0;t<vertexCount;t++)
	{
		//3d coordinate buffer will do for storing
		//this load of vertex information
		PointDef& apd=*pPointDefs++;
		DoPointStruc& dp=*pPoints++;

		dp.bodyx.i=(apd.x<<9)+view.X;
		dp.bodyy.i=apd.alt*_altitudeScale;
		SWord flipz=256-apd.z;
		dp.bodyz.i=(flipz<<9)+view.Z;
		dp.ix=apd.x;
		dp.iy=flipz;

		//7bit fractional part available (better than nothing!)
		if (dp.ix>imax) dp.ix=imax<<iscale;
		else			dp.ix<<=iscale;
		if (dp.iy>imax) dp.iy=imax<<iscale;
		else			dp.iy<<=iscale;

		dp.specular=-1;
		//And, transform the points...
		dp.bodyx.i-=viewer_x;
		dp.bodyy.i-=viewer_y;
		dp.bodyz.i-=viewer_z;
		dp.intensity=0xFF;
	}

	pDataStream=(UByte*)pPointDefs;
	pPoints=SHAPE.newco;

	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;
	pDataStream+=sizeof(ddh);

	int	polyCount=ddh.noOfPolys;
	int totalTriCount=ddh.totalTris;
	UByte* saveDS=pDataStream;
	AddTileSub(vertexCount,totalTriCount,SHAPE.newco,polyCount,pDataStream,hTexture);
	pDataStream=saveDS;
	pDS=pDataStream;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTileSub
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
void LandScape::AddTileSub(ULong ,ULong ,DoPointStruc* pdp,ULong drwCnt,UByte*& pdd,const HTEXT& hT)
{
	DoPointStruc dp[3];
	UByte* pdrawdata=pdd;
	while (drwCnt--)
	{
		pdrawdata++;				//skip colour byte
		ULong fanCnt=*pdrawdata++;
		while (fanCnt--){
			ULong triCnt=*pdrawdata++;
			int v1=*pdrawdata++;
			int v2=*pdrawdata++;
			int v3=*pdrawdata++;
			dp[0]=SHAPE.newco[v1];
			dp[1]=SHAPE.newco[v2];
			dp[2]=SHAPE.newco[v3];
			PerspectivePoly(3,dp,hT);
			triCnt--;
			while (triCnt--)
			{
				v2=v3;
				v3=*pdrawdata++;
				dp[1]=dp[2];
				dp[2]=SHAPE.newco[v3];
				PerspectivePoly(3,dp,hT);
			}
		}
	}
	pdd=pdrawdata;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubdivisionNeeded
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
bool LandScape::SubdivisionNeeded(const LPolyDef& inp,bool& axis)
{
	#define MIN_FOR_SUB (512*16)
	//find min and max x & z values
	SLong minx,maxx,minz,maxz;
	minx=maxx=inp.point[0]->bodyx.i;
	minz=maxz=inp.point[0]->bodyz.i;
	for (int i=inp.count-1;i>0;i--)
	{
		if (inp.point[i]->bodyx.i>maxx) maxx=inp.point[i]->bodyx.i;
		if (inp.point[i]->bodyx.i<minx) minx=inp.point[i]->bodyx.i;
		if (inp.point[i]->bodyz.i>maxz) maxz=inp.point[i]->bodyz.i;
		if (inp.point[i]->bodyz.i<minz) minz=inp.point[i]->bodyz.i;
	}
	maxx-=minx;
	maxz-=minz;
	if (maxx>MIN_FOR_SUB || maxz>MIN_FOR_SUB)	axis=maxx>maxz?true:false;
	else										return false;
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Split
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
void LandScape::Split(LPolyDef& inp,LPolyDef& out,bool axis,CVertexAllocator& allocator)
{
	enum SideFlag {EQUAL=0,TOP,BOTTOM};

	SLong		min,max,split,i;
	Float		frac;
	LPolyDef	copy=inp;
	DoPointStruc **top,**bot,**cur,**nxt;

	if (axis)		//wx split
	{
		min=max=inp.point[0]->bodyx.i;
		for (i=inp.count-1;i>0;i--)
		{
			if (inp.point[i]->bodyx.i>max)	max=inp.point[i]->bodyx.i;
			if (inp.point[i]->bodyx.i<min)	min=inp.point[i]->bodyx.i;
		}
	}
	else			//wz split
	{
		min=max=inp.point[0]->bodyz.i;
		for (i=inp.count-1;i>0;i--)
		{
			if (inp.point[i]->bodyz.i>max)	max=inp.point[i]->bodyz.i;
			if (inp.point[i]->bodyz.i<min)	min=inp.point[i]->bodyz.i;
		}
	}
	split=(min+max)>>1;

	inp.count=out.count=0;
	top=inp.point;
	bot=out.point;
	nxt=copy.point;
	cur=copy.point+copy.count-1;

	for (i=copy.count-1;i>=0;i--)
	{
		SLong testval,nextval;

		if (axis)	testval=(*cur)->bodyx.i,nextval=(*nxt)->bodyx.i;
		else		testval=(*cur)->bodyz.i,nextval=(*nxt)->bodyz.i;

		//cases to handle are...
		//		both values on same side
		//		values on opposite sides
		//		one or both values on the boundary

		SideFlag testflag=testval>split?TOP:testval<split?BOTTOM:EQUAL;
		SideFlag nextflag=nextval>split?TOP:nextval<split?BOTTOM:EQUAL;

		if (testflag&nextflag)
		{
			//both values are on the same side of the boundary
			//Insert the current point into the correct list
			if (testflag&TOP) 	{*top++=*cur; inp.count++;}
			else				{*bot++=*cur; out.count++;}
		}
		else if (!testflag)
		{
			//current value is on the boundary so add it to both lists
			*top++=*cur;
			*bot++=*cur;
			inp.count++;
			out.count++;
		}
		else if (!nextflag)
		{
			//next value is on the boundary so just insert the
			//current point into the correct list
			if (testflag&TOP) 	{*top++=*cur; inp.count++;}
			else				{*bot++=*cur; out.count++;}
		}
		else
		{
			//calculate point of intersection with the test plane
			DoPointStruc *tmp=allocator.alloc();
			DoPointStruc *pin,*pout;

			if (testflag&TOP)
			{
				pin=*cur,pout=*nxt;
				frac=Float(split-testval)/Float(nextval-testval);
			}
			else
			{
			 	pin=*nxt,pout=*cur;
				frac=Float(split-nextval)/Float(testval-nextval);
			}
			if (axis)
			{
				tmp->bodyx.i=split;
				tmp->bodyz.i=pin->bodyz.i+frac*(pout->bodyz.i-pin->bodyz.i);
			}
			else
			{
				tmp->bodyz.i=split;
				tmp->bodyx.i=pin->bodyx.i+frac*(pout->bodyx.i-pin->bodyx.i);
			}
			tmp->bodyy.i=pin->bodyy.i+frac*(pout->bodyy.i-pin->bodyy.i);
			tmp->ix=pin->ix+frac*(pout->ix-pin->ix);
			tmp->iy=pin->iy+frac*(pout->iy-pin->iy);
			if (testflag&TOP)
			{
				*top++=*cur;
				*top++=tmp;
				inp.count+=2;
				*bot++=tmp;
				out.count++;
			}
			else
			{
				*bot++=*cur;
				*bot++=tmp;
				out.count+=2;
				*top++=tmp;
				inp.count++;
			}
		}
		cur=nxt;
		nxt++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PerspectivePoly
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
void LandScape::PerspectivePoly(SWord pc,DoPointStruc* pdp,const HTEXT& hT)
{
	CVertexAllocator allocator(256,highco);

	//prepare the poly for subdivision...
	LPolyList poly_list;
	LPolyDef& poly_def=poly_list.poly[0];

	bool flag;
	bool whichAxis;

	poly_list.count=1;
	poly_def.count=pc;

	for (--pc;pc>=0;pc--) poly_def.point[pc]=pdp+pc;

	if (SubdivisionNeeded(poly_def,whichAxis))
		do 
		{
			flag=false;
			for (int i=poly_list.count-1;i>=0;i--)
			{
				LPolyDef& poly_def=poly_list.poly[i];
				if (poly_list.count<LPolyList::Max_Polys && poly_def.count>0)
				{
					if (SubdivisionNeeded(poly_def,whichAxis))
					{
						LPolyDef& new_poly_def=poly_list.poly[poly_list.count];
						poly_list.count++;
						Split(poly_def,new_poly_def,whichAxis,allocator);
						flag=true;
					}
					else poly_def.count=-poly_def.count;
				}
			}
		}
		while (flag);

	//render the polys

	for (int i=poly_list.count-1;i>=0;i--)
	{
		LPolyDef& poly_def=poly_list.poly[i];

		//split each poly into triangles...

		if (poly_def.count<0)
			poly_def.count=-poly_def.count;

		DoPointStruc dp[3];

		dp[0]=*(poly_def.point[0]);
		dp[2]=*(poly_def.point[1]);
		_matrix.transform(fpviewer_matrix,dp[0]);
		_matrix.transform(fpviewer_matrix,dp[2]);

		for (int j=2;j<poly_def.count;j++)
		{
			dp[1]=dp[2];
			dp[2]=*(poly_def.point[j]);
			_matrix.transform(fpviewer_matrix,dp[2]);
			if ((	dp[0].clipFlags&
					dp[1].clipFlags&
					dp[3].clipFlags)==CF3D_NULL)
			{
				Land_Obj *loptr=
					(Land_Obj*)Three_Dee.bt->Get3DArea(SPECIAL_TILE_OBJECT);
				loptr->hMaterial=hT;
				Float max_z=0;
				for (int k=2;k>=0;k--)
				{
					loptr->bx[k]=dp[k].bodyx.f;
					loptr->by[k]=dp[k].bodyy.f;
					loptr->bz[k]=dp[k].bodyz.f;
					if (dp[k].bodyz.f>max_z)
						max_z=dp[k].bodyz.f;
					loptr->u[k]=dp[k].ix;
					loptr->v[k]=dp[k].iy;
					loptr->clipFlags[k]=dp[k].clipFlags;
				}
				loptr->bodyz.f=loptr->realbz.f=max_z;
				Three_Dee.bt->insert_object(loptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetClipFlags
//Author		Paul.   
//Date			Mon 27 Jul 1998
//
//Returns		0x00=visible
//				or some combination of...
//				0x01=off left
//				0x02=off right
//				0x04=off top
//				0x08=off bottom
//------------------------------------------------------------------------------
inline UByte LandScape::SetClipFlags(const SLong x,const SLong z,const Rect& r)
{
	UByte rv;
	if (x<r.l)		rv=0x01;
	else if (x>r.r)	rv=0x02;
	else			rv=0x00;
	if (z<r.t)		rv+=0x04;
	else if (z>r.b)	rv+=0x08;
	return rv;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToTop
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
inline UByte LandScape::ClipToTop(	DoPointStruc* pin,
									DoPointStruc* pout,
									DoPointStruc* pclip,
									Rect& clip)
{
	UByte rv;

	SLong dx=pout->bodyx.i-pin->bodyx.i;
	SLong dy=pout->bodyy.i-pin->bodyy.i;
	SLong dz=pout->bodyz.i-pin->bodyz.i;
	SLong di=(SLong(pout->intensity)-SLong(pin->intensity))<<16;
	SLong ndz=clip.t-pin->bodyz.i;

	pclip->bodyz.i=clip.t;
	pclip->bodyx.i=pin->bodyx.i+((dx)?MULDIVSIN(dx,ndz,dz):dx);
	pclip->bodyy.i=pin->bodyy.i+((dy)?MULDIVSIN(dy,ndz,dz):dy);
	pclip->intensity=pin->intensity+((di)?(MULDIVSIN(di,ndz,dz))>>16:di);
	pclip->intensity=pclip->intensity<0?0:pclip->intensity>255?255:pclip->intensity;
	pclip->specular=-1;

	//return new clipcode for this point

	if (pclip->bodyx.i<clip.l)		rv=1;
	else if (pclip->bodyx.i>clip.r)	rv=2;
	else 							rv=0;

	return rv;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToBottom
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
inline UByte LandScape::ClipToBottom(	DoPointStruc* pin,
										DoPointStruc* pout,
										DoPointStruc* pclip,
										Rect& clip)
{
	UByte rv;

	SLong dx=pout->bodyx.i-pin->bodyx.i;
	SLong dy=pout->bodyy.i-pin->bodyy.i;
	SLong dz=pout->bodyz.i-pin->bodyz.i;
	SLong di=(SLong(pout->intensity)-SLong(pin->intensity))<<16;
	SLong ndz=clip.b-pin->bodyz.i;

	pclip->bodyz.i=clip.b;
	pclip->bodyx.i=pin->bodyx.i+((dx)?MULDIVSIN(dx,ndz,dz):dx);
	pclip->bodyy.i=pin->bodyy.i+((dy)?MULDIVSIN(dy,ndz,dz):dy);
	pclip->intensity=pin->intensity+((di)?(MULDIVSIN(di,ndz,dz))>>16:di);
	pclip->intensity=pclip->intensity<0?0:pclip->intensity>255?255:pclip->intensity;
	pclip->specular=-1;

	//return new clipcode for this point

	if (pclip->bodyx.i<clip.l)		rv=1;
	else if (pclip->bodyx.i>clip.r)	rv=2;
	else 							rv=0;

	return rv;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToLeft
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
inline UByte LandScape::ClipToLeft(	DoPointStruc* pin,
									DoPointStruc* pout,
									DoPointStruc* pclip,
									Rect& clip)
{
	SLong dx=pout->bodyx.i-pin->bodyx.i;
	SLong dy=pout->bodyy.i-pin->bodyy.i;
	SLong dz=pout->bodyz.i-pin->bodyz.i;
	SLong di=(SLong(pout->intensity)-SLong(pin->intensity))<<16;
	SLong ndx=clip.l-pin->bodyx.i;

	pclip->bodyx.i=clip.l;
	pclip->bodyz.i=pin->bodyz.i+((dz)?MULDIVSIN(dz,ndx,dx):dz);
	pclip->bodyy.i=pin->bodyy.i+((dy)?MULDIVSIN(dy,ndx,dx):dy);
	pclip->intensity=pin->intensity+((di)?(MULDIVSIN(di,ndx,dx))>>16:di);
	pclip->intensity=pclip->intensity<0?0:pclip->intensity>255?255:pclip->intensity;
	pclip->specular=-1;

	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToRight
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
inline UByte LandScape::ClipToRight(DoPointStruc* pin,
									DoPointStruc* pout,
									DoPointStruc* pclip,
									Rect& clip)
{
	SLong dx=pout->bodyx.i-pin->bodyx.i;
	SLong dy=pout->bodyy.i-pin->bodyy.i;
	SLong dz=pout->bodyz.i-pin->bodyz.i;
	SLong di=(SLong(pout->intensity)-SLong(pin->intensity))<<16;
	SLong ndx=clip.r-pin->bodyx.i;

	pclip->bodyx.i=clip.r;
	pclip->bodyz.i=pin->bodyz.i+((dz)?MULDIVSIN(dz,ndx,dx):dz);
	pclip->bodyy.i=pin->bodyy.i+((dy)?MULDIVSIN(dy,ndx,dx):dy);
	pclip->intensity=pin->intensity+((di)?(MULDIVSIN(di,ndx,dx))>>16:di);
	pclip->intensity=pclip->intensity<0?0:pclip->intensity>255?255:pclip->intensity;
	pclip->specular=-1;

	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Macro			DoClip
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
#define DoClip(flag,srcflagsi,srcflagsj,dstflags,dstpoly,srcpolyi,srcpolyj,cliprtn)\
if (!((srcflagsi)&(flag)))\
{\
	(dstpoly)[nvc]=(srcpolyi);\
	(dstflags)[nvc++]=(srcflagsi);\
\
	if ((srcflagsj)&(flag))\
	{\
		cf=(cliprtn)((srcpolyi),(srcpolyj),&localPoints[localPointsUsed],clip);\
		if (!cf)\
		{\
		 	*pntAdd=localPoints[localPointsUsed];\
			(dstpoly)[nvc]=pntAdd++;\
			(dstflags)[nvc++]=0;\
		}\
		else\
		{\
			(dstpoly)[nvc]=&localPoints[localPointsUsed++];\
			(dstflags)[nvc++]=cf;\
		}\
	}\
}\
else if (!((srcflagsj)&(flag)))\
{\
	cf=(cliprtn)((srcpolyj),(srcpolyi),&localPoints[localPointsUsed],clip);\
	if (!cf)\
	{\
		*pntAdd=localPoints[localPointsUsed];\
		(dstpoly)[nvc]=pntAdd++;\
		(dstflags)[nvc++]=0;\
	}\
	else\
	{\
		(dstpoly)[nvc]=&localPoints[localPointsUsed++];\
		(dstflags)[nvc++]=cf;\
	}\
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TriClipper
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void LandScape::TriClipper(	SLong& vc,				//polygon vertex count
							DoPointStruc** polydef,	//polygon definition
							UByte* clipFlags,		//poly vertex clip flags
							DoPointStruc*& pntAdd,	//insertion point for new vertices
							Rect& clip)				//clip area
{
	UByte	cf;
	SLong 	nvc;					//new poly vertex count
	SLong	limit;					//no of vertices -1
	SLong	localPointsUsed;		//count of local vertices allocated
	UByte	localClipFlags[32];		//local clip flag buffer (matches poly point defs)
	DoPointStruc* newpolydef[32];	//new polygon definition
	DoPointStruc localPoints[32];	//buffer of local vertices

	localPointsUsed=0;

	limit=vc-1;
	nvc=0;

	//clip against top

	for (int i=0;i<limit;i++)
	{
		int j=i+1;
		DoClip(4,clipFlags[i],clipFlags[j],localClipFlags,newpolydef,polydef[i],polydef[j],ClipToTop);
	}
	DoClip(4,clipFlags[i],clipFlags[0],localClipFlags,newpolydef,polydef[i],polydef[0],ClipToTop);

	if ((vc=nvc)<3) return;
	limit=vc-1;
	nvc=0;

	//clip against bottom

	for (i=0;i<limit;i++)
	{
		int j=i+1;
		DoClip(8,localClipFlags[i],localClipFlags[j],clipFlags,polydef,newpolydef[i],newpolydef[j],ClipToBottom);
	}
	DoClip(8,localClipFlags[i],localClipFlags[0],clipFlags,polydef,newpolydef[i],newpolydef[0],ClipToBottom);

	if ((vc=nvc)<3) return;
	limit=vc-1;
	nvc=0;

	//clip against left

	for (i=0;i<limit;i++)
	{
		int j=i+1;
		DoClip(1,clipFlags[i],clipFlags[j],localClipFlags,newpolydef,polydef[i],polydef[j],ClipToLeft);
	}
	DoClip(1,clipFlags[i],clipFlags[0],localClipFlags,newpolydef,polydef[i],polydef[0],ClipToLeft);

	if ((vc=nvc)<3) return;
	limit=vc-1;
	nvc=0;

	//clip against right

	for (i=0;i<limit;i++)
	{
		int j=i+1;
		DoClip(2,localClipFlags[i],localClipFlags[j],clipFlags,polydef,newpolydef[i],newpolydef[j],ClipToRight);
	}
	DoClip(2,localClipFlags[i],localClipFlags[0],clipFlags,polydef,newpolydef[i],newpolydef[0],ClipToRight);

	vc=nvc;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClippedTile
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
int LandScape::ClippedTile(	UByte*& 	xpds,ULong& dl,
							COORDS3D& 	view,
							Rect& clip)
{
	UByte* pds=xpds;

	int vertexCount;
	int	newVertCount;
	int	polyCount;
	int	newPolyCount;

	int fanCount;
	int triCount;
	int v1,v2,v3;

	PointDef* 		pPointDefs;
	DoPointStruc*	pPoints;
	DoPointStruc*	pClipPoints;
	DoPointStruc*	pNewPoints;
	UByte*			pRenumber;
	UByte*			pnds;
	UByte*			abortPtr;
	UWord			clipTest;

	static UByte 	clipcodes[256];
	static UByte 	renumber[256];
	static UByte	newtiledata[4096];
	static DoPointStruc clippoints[256];

	AltPointsHdr& aph=*(AltPointsHdr*)pds;
	pds+=sizeof(AltPointsHdr);

	vertexCount=aph.vertexCount;

	pPointDefs=(PointDef*)pds;
	pds+=sizeof(PointDef)*vertexCount;

	pPoints=SHAPE.newco;
	pClipPoints=clippoints;
	pRenumber=renumber;
	newVertCount=0;
	pnds=newtiledata;

	//generate clipcodes for each of the tile vertices

	clipTest=0xFF;

	for (int t=0;t<vertexCount;t++)
	{
		PointDef& apd=pPointDefs[t];
		DoPointStruc& cp=pClipPoints[t];
		DoPointStruc& dp=pPoints[newVertCount];

		cp.bodyx.i=(apd.x<<9)+view.X;
		cp.bodyy.i=apd.alt*_altitudeScale;
		cp.bodyz.i=((256-apd.z)<<9)+view.Z;

		if (!Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])
			cp.intensity=0xFF;
		else
			cp.intensity=Three_Dee.pNormalLookup[cp.intensity];

		cp.specular=-1;
		clipcodes[t]=SetClipFlags(cp.bodyx.i,cp.bodyz.i,clip);

		if (!clipcodes[t])
		{
			*pRenumber=newVertCount++;
			dp.bodyx.i=cp.bodyx.i;
			dp.bodyy.i=cp.bodyy.i;
			dp.bodyz.i=cp.bodyz.i;
			dp.intensity=cp.intensity;
			dp.specular=cp.specular;
		}
		clipTest&=clipcodes[t];
		pRenumber++;
	}

	if (clipTest!=0)
	{
		xpds=pds;
		return 0;
	}

	pNewPoints=SHAPE.newco+newVertCount;

	//trawl thru the data for this tile and produce a new set of data
	//clipped to the requested area

	DrawDataHdr& ddh=*(DrawDataHdr*)pds;
	pds+=sizeof(DrawDataHdr);

	polyCount=ddh.noOfPolys;
	newPolyCount=0;

	abortPtr=pnds;

	while (polyCount--)
	{
		pds++;				//poly area type byte - skipped!
		fanCount=*pds++;
		while (fanCount--)
		{
			triCount=*pds++;
			v1=*pds++;
			v3=*pds++;
			while (triCount--)
			{
				v2=v3;
				v3=*pds++;

				//clip this triangle and add to the new data list
				//any visible part of the triangle...

				if (clipcodes[v1]==0x00&&
					clipcodes[v2]==0x00&&
					clipcodes[v3]==0x00)
				{
					//no clipping needed for this triangle
					*pnds++=renumber[v1];
					*pnds++=renumber[v2];
					*pnds++=renumber[v3];
					newPolyCount++;
				}
				else
				{
					if ((clipcodes[v1]&clipcodes[v2]&clipcodes[v3])==0x00)
					{
						//prepare to clip...
						DoPointStruc* polyDef[32];
						DoPointStruc* pLastNewPoints;
						UByte pcf[32];
						SLong pvc=3;
						pcf[0]=clipcodes[v1];
						pcf[1]=clipcodes[v2];
						pcf[2]=clipcodes[v3];

						if (pcf[0]==0)	polyDef[0]=pPoints+renumber[v1];
						else			polyDef[0]=pClipPoints+v1;

						if (pcf[1]==0)	polyDef[1]=pPoints+renumber[v2];
						else			polyDef[1]=pClipPoints+v2;

						if (pcf[2]==0)	polyDef[2]=pPoints+renumber[v3];
						else			polyDef[2]=pClipPoints+v3;

						pLastNewPoints=pNewPoints;
						TriClipper(pvc,polyDef,pcf,pNewPoints,clip);

						if (pvc>2)	//reject degenerate polygons
						{
							int lv1,lv2,lv3;
							newVertCount+=pNewPoints-pLastNewPoints;
							lv1=polyDef[0]-SHAPE.newco;
							lv3=polyDef[1]-SHAPE.newco;
							for (t=2;t<pvc;t++)
							{
								lv2=lv3;
								lv3=polyDef[t]-SHAPE.newco;
								*pnds++=lv1;
								*pnds++=lv2;
								*pnds++=lv3;
								newPolyCount++;
							}
						}
						else
						{
							//remove any points that the clipper
							//may have added
						 	pNewPoints=pLastNewPoints;
						}
					}
					//else this triangle is out of view
				}
			}
		}
	}

	//abort if all polys were clipped

	if (ULong(abortPtr)==ULong(pnds))
	{
		xpds=pds;
		return 0;
	}

	//transform all the vertices for this tile ready to draw...
	
	clipTest=0;

	for (t=0;t<newVertCount;t++)
	{
		DoPointStruc& dp=pPoints[t];

		dp.ix=(dp.bodyx.i-ibase_x)>>iscale_factor;
		dp.iy=(dp.bodyz.i-ibase_z)>>iscale_factor;

		dp.bodyx.i-=viewer_x;
		dp.bodyy.i-=viewer_y;
		dp.bodyz.i-=viewer_z;

		_matrix.transform(fpviewer_matrix,dp);
		clipTest|=dp.clipFlags;
	}
	
	//draw the newly clipped data

	pnds=newtiledata;

	if (!clipTest)
		currscreen->DoNewTile(newVertCount,SHAPE.newco,newPolyCount,pnds,itexture);
	else
		currscreen->DoCNewTile(newVertCount,SHAPE.newco,newPolyCount,pnds,itexture);

	xpds=pds;
	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HighDetailTile
//Author		Paul.   
//Date			Thu 9 Apr 1998
//------------------------------------------------------------------------------
int LandScape::HighDetailTile(UByte*& pDS,ULong& dataLen,COORDS3D& viewCoords)
{
	UByte* pDataStream=pDS;

	//Now have the length of this tiles draw data
	//and a pointer to the start of the data
	//Handle the vertex list first

	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
	int	vertexCount=aph.vertexCount;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pPointDefs=(PointDef*)pDataStream;

	COORDS3D* pCoordData=tileCoords;
	DoPointStruc* pPoints=SHAPE.newco;
	
	UWord clipTest=0;

	for (int t=0;t<vertexCount;t++){
		//3d coordinate buffer will do for storing
		//this load of vertex information
		COORDS3D& tile=*pCoordData++;
		PointDef& apd=*pPointDefs++;
		DoPointStruc& dp=*pPoints++;

		tile.X=apd.x;
		tile.Z=256-apd.z;
		tile.Y=apd.alt;
		dp.ix=tile.X;
		dp.iy=tile.Z;
	
		//Now, scale the points
		tile.X<<=9;
		tile.Z<<=9;
		tile.Y*=_altitudeScale;
		dp.bodyx.i=viewCoords.X+tile.X;
		dp.bodyy.i=tile.Y;
		if (mistenabled) SetMist(dp);
		dp.bodyy.i+=viewCoords.Y;
		dp.bodyz.i=viewCoords.Z+tile.Z;

		dp.intensity=apd.shadeVal;
		dp.specular=-1;

		//And, transform the points...
		_matrix.transform(fpviewer_matrix,dp);

		clipTest|=dp.clipFlags;

		if (!bDoingHardware3D) _matrix.body2screen(dp);
	}

	pDataStream=(UByte*)pPointDefs;
	pPoints=SHAPE.newco;

	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;
	pDataStream+=sizeof(ddh);

	int	polyCount=ddh.noOfPolys;
	int lineCount=ddh.noOfLines;
	int totalTriCount=ddh.totalTris;

	if (clipTest==0)
	{
		currscreen->DoAddTile(	vertexCount,
								totalTriCount,
								SHAPE.newco,
								polyCount,
								pDataStream);
	}
	else
	{
		currscreen->DoCAddTile(	vertexCount,
								totalTriCount,
								SHAPE.newco,
								polyCount,
								pDataStream);
	}
	pDS=pDataStream;
	return lineCount;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MedDetailTile
//Author		Paul.   
//Date			Thu 9 Apr 1998
//------------------------------------------------------------------------------
int LandScape::MedDetailTile(UByte*& pDS,ULong& dataLen,COORDS3D& viewCoords)
{
	UByte* pDataStream=pDS;

	//Now have the length of this tiles draw data
	//and a pointer to the start of the data
	//Handle the vertex list first

	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
	int	vertexCount=aph.vertexCount;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pPointDefs=(PointDef*)pDataStream;

	COORDS3D* pCoordData=tileCoords;
	DoPointStruc* pPoints = SHAPE.newco;

	for (int t=0;t<vertexCount;t++){
		//3d coordinate buffer will do for storing
		//this load of vertex information (probably)
		COORDS3D& tile=*pCoordData++;
		PointDef& apd=*pPointDefs++;
		DoPointStruc& dp=*pPoints++;

		tile.X=apd.x;
		tile.Z=256-apd.z;
		tile.Y=apd.alt;

		//Now, scale the points
		tile.X<<=9;
		tile.Z<<=9;
		tile.Y*=_altitudeScale;
		dp.bodyx.i=viewCoords.X+tile.X;
		dp.bodyy.i=tile.Y;
		if (mistenabled) SetMist(dp);
		dp.bodyy.i+=viewCoords.Y;
		dp.bodyz.i=viewCoords.Z+tile.Z;

		dp.intensity=apd.shadeVal;
		dp.specular=-1;

		//And, transform the points...
		_matrix.transform(fpviewer_matrix,dp);
		if (!bDoingHardware3D) _matrix.body2screen(dp);
	}
	pDataStream=(UByte*)pPointDefs;
	pPoints=SHAPE.newco;

	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;
	pDataStream+=sizeof(ddh);

	int	polyCount=ddh.noOfPolys;
	int lineCount=ddh.noOfLines;

	while (polyCount--){
		CLandColor landCol(*pDataStream++);
		Colour	clr=(Colour)landCol.pCol();
		int		triCount=*pDataStream++;
		while (triCount--){
			int fanCount=*pDataStream++;
			int v1=*pDataStream++;
			int v3=*pDataStream++;
			while (fanCount--){
				int v2=v3;
				v3=*pDataStream++;

				POLYGON.createpoly(clr);
				POLYGON.createvert(pPoints[v1],pPoints[v1].intensity);
				POLYGON.createvert(pPoints[v2],pPoints[v2].intensity);
				POLYGON.createvert(pPoints[v3],pPoints[v3].intensity);
				POLYGON.drawpoly();
			}
		}
	}

	pDS=pDataStream;
	return lineCount;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowDetailTile
//Author		Paul.   
//Date			Tue 14 Apr 1998
//------------------------------------------------------------------------------
int LandScape::LowDetailTile(UByte*& pDataStream,ULong& dataLen,COORDS3D& viewCoords)
{
return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HighDetailRoute
//Author		Paul.   
//Date			Tue 14 Apr 1998
//------------------------------------------------------------------------------
void LandScape::HighDetailRoute(UByte*& pDS,ULong& dataLen,int lineCount,COORDS3D& viewCoords)
{
	UByte* pDataStream=pDS;
	DoPointStruc* pPoints = SHAPE.newco;
	while (lineCount--){
		Colour lineCol;
	 	UByte routeCol=*pDataStream++;
		RouteData* pRD=pRouteData->find(routeCol);
		UByte sectionCnt=(*pDataStream++)-1;	//no of sections in this line
		if (pRD!=NULL&&sectionCnt!=0){
			if (pRD->width==pRD->maxWidth)
				GenerateRoutePoly(viewCoords,sectionCnt,pDataStream,pRD);
			else
				GenerateEdgePoly(viewCoords,sectionCnt,pDataStream,pRD);
		}
		pDataStream+=sectionCnt;
	}
	pDS=pDataStream;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateRoutePoly
//Author		Paul.   
//Date			Wed 15 Apr 1998
//------------------------------------------------------------------------------
void LandScape::GenerateRoutePoly(COORDS3D& viewCoords,int sectCnt,UByte* pntList,RouteData* pRD)
{
	int width=pRD->width;
	SWord u[2],v[2];
	u[0]=pRD->mX0; v[0]=pRD->mY0;
	u[1]=pRD->mX1; v[1]=pRD->mY1;

	ImageMapDescPtr pImage=pRD->maskedTexture.GetLandMapPtr();
	//Step through the point list & generate normal vectors for
	//each of the route segments
	float fWidth=float(width>>1);
	struct nVec{float x,z;};
	struct iVec{SLong x,z;};

	nVec* pSNorm=new nVec[sectCnt];	//Array of vectors for section normals
	iVec* pVNorm=new iVec[sectCnt+1]; //Array of vectors for vertex normals
	SLong* pSLen=new SLong[sectCnt];

	//calculate section normals
	UByte* tPntList=pntList;
	SLong* tLenList=pSLen;
	for (int i=0;i<sectCnt;i++){
		COORDS3D& start=tileCoords[*tPntList++];
		COORDS3D& fin=tileCoords[*tPntList];
		nVec& vec=pSNorm[i];
		vec.x=float(fin.Z-start.Z);
		vec.z=float(start.X-fin.X);
		double mag=vec.x*vec.x+vec.z*vec.z;
		_asm{
		fld mag;
		fsqrt;
		fstp mag;
		}
		vec.x/=mag;
		vec.z/=mag;
		*tLenList++=SLong(mag)>>1;	//.5 section length
	}
	//use the section normals to calculate vertex normals
	//by averageing the two normals for the sections joining
	//each vertex. The first and last vertices are special
	//cases (no averaging can be done)
	pVNorm->x=SLong(pSNorm->x*fWidth);
	pVNorm->z=SLong(pSNorm->z*fWidth);
	nVec* pCur=pSNorm;
	for (i=1;i<sectCnt;i++){
		nVec& start=*pCur++;
		nVec& fin=*pCur;
		iVec& res=pVNorm[i];
		float rx=(start.x+fin.x)/2.;
		float rz=(start.z+fin.z)/2.;
		double mag=rx*rx+rz*rz;
		_asm{
		fld mag;
		fsqrt;
		fstp mag;
		}
		mag/=fWidth;
		res.x=SLong(rx/mag);
		res.z=SLong(rz/mag);
	}
	pVNorm[i].x=SLong(pCur->x*fWidth);
	pVNorm[i].z=SLong(pCur->z*fWidth);

	//generate point information for the route polys
	DoPointStruc* pPoints=SHAPE.newco;
	DoPointStruc* pIns=pPoints;
	tPntList=pntList;
	for (i=0;i<sectCnt+1;i++){
		//Generate 2 points per section
		iVec& off=pVNorm[i];
		COORDS3D& pnt=tileCoords[*tPntList++];
		DoPointStruc& dp0=*pIns++;

		dp0.bodyx.i=pnt.X+off.x+viewCoords.X;
		dp0.bodyy.i=pnt.Y+viewCoords.Y;
		dp0.bodyz.i=pnt.Z+off.z+viewCoords.Z;
		_matrix.transform(fpviewer_matrix,dp0);
		_matrix.body2screen(dp0);

		DoPointStruc& dp1=*pIns++;
		dp1.bodyx.i=pnt.X-off.x+viewCoords.X;
		dp1.bodyy.i=pnt.Y+viewCoords.Y;
		dp1.bodyz.i=pnt.Z-off.z+viewCoords.Z;
		_matrix.transform(fpviewer_matrix,dp1);
		_matrix.body2screen(dp1);
	}
	delete[]pVNorm;
	delete[]pSNorm;
	//render the route polys
	pIns=pPoints;
	for (i=0;i<sectCnt;i++){
		SWord vScale=v[1]*pSLen[i]/pRD->width;
		bool visible;
		CLIPFLAGS3D flag;
		flag=(CLIPFLAGS3D)(pIns[3].clipFlags|pIns[2].clipFlags|pIns[0].clipFlags);
		if (flag==CF3D_NULL) visible=true;
		else{
			flag=(CLIPFLAGS3D)(CF3D_ALL&pIns[3].clipFlags&pIns[2].clipFlags&pIns[0].clipFlags);
			if (flag!=CF3D_NULL) visible=false;
			else visible=true;
		}
		if (visible){
			POLYGON.createpoly(pImage,(ColourRange)-1);
			POLYGON.createvert(pIns[3],u[0],v[0]);
			POLYGON.createvert(pIns[2],u[1],v[0]);
			POLYGON.createvert(pIns[0],u[1],vScale);
			POLYGON.drawpoly();
		}
		flag=(CLIPFLAGS3D)(pIns[1].clipFlags|pIns[3].clipFlags|pIns[0].clipFlags);
		if (flag==CF3D_NULL) visible=true;
		else{
			flag=(CLIPFLAGS3D)(CF3D_ALL&pIns[1].clipFlags&pIns[3].clipFlags&pIns[0].clipFlags);
			if (flag!=CF3D_NULL) visible=false;
			else visible=true;
		}
		if (visible){
			POLYGON.createpoly(pImage,(ColourRange)-1);
			POLYGON.createvert(pIns[1],u[0],vScale);
			POLYGON.createvert(pIns[3],u[0],v[0]);
			POLYGON.createvert(pIns[0],u[1],vScale);
			POLYGON.drawpoly();
		}
		pIns+=2;
	}
	delete[]pSLen;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateEdgePoly
//Author		Paul.   
//Date			Thu 16 Apr 1998
//------------------------------------------------------------------------------
void LandScape::GenerateEdgePoly(COORDS3D& viewCoords,int sectCnt,UByte* pntList,RouteData* pRD)
{
	int width=pRD->width;
	int widthDelta=pRD->maxWidth-width;
	SWord u[2],v[2];
	u[0]=pRD->mX0; v[0]=pRD->mY0;
	u[1]=pRD->mX1; v[1]=pRD->mY1;

	ImageMapDescPtr pImage=pRD->maskedTexture.GetLandMapPtr();
	//Step through the point list & generate normal vectors for
	//each of the route segments
	float fWidth=float(width>>1);
	float fdWidth=float(widthDelta>>1);
	struct nVec{float x,z;};
	struct iVec{SLong x,z;};

	nVec* pSNorm=new nVec[sectCnt];	//Array of vectors for section normals
	iVec* pVNorm=new iVec[sectCnt+1]; //Array of vectors for vertex normals
	SLong* pSLen=new SLong[sectCnt];
	float* pWidths=new float[sectCnt+1];

	//calculate section normals
	UByte* tPntList=pntList;
	SLong* tLenList=pSLen;
	float* tWidthList=pWidths;
	for (int i=0;i<sectCnt;i++){
		COORDS3D& start=tileCoords[*tPntList++];
		COORDS3D& fin=tileCoords[*tPntList];
		*tWidthList++=fWidth+(fdWidth*float(index2d(start.X>>9,start.Z>>9))/256.);
		nVec& vec=pSNorm[i];
		vec.x=float(fin.Z-start.Z);
		vec.z=float(start.X-fin.X);
		double mag=vec.x*vec.x+vec.z*vec.z;
		_asm{
		fld mag;
		fsqrt;
		fstp mag;
		}
		vec.x/=mag;
		vec.z/=mag;
		*tLenList++=SLong(mag)>>1;	//.5 section length
	}
	*tWidthList=fWidth+(fdWidth*float(index2d(tileCoords[*tPntList].X>>9,tileCoords[*tPntList].Z>>9))/256.);
	//use the section normals to calculate vertex normals
	//by averageing the two normals for the sections joining
	//each vertex. The first and last vertices are special
	//cases (no averaging can be done)
	nVec* pCur=pSNorm;
	tWidthList=pWidths;
	pVNorm->x=SLong(pSNorm->x*(*tWidthList));
	pVNorm->z=SLong(pSNorm->z*(*tWidthList++));
	for (i=1;i<sectCnt;i++){
		nVec& start=*pCur++;
		nVec& fin=*pCur;
		iVec& res=pVNorm[i];
		float rx=(start.x+fin.x)/2.;
		float rz=(start.z+fin.z)/2.;
		double mag=rx*rx+rz*rz;
		_asm{
		fld mag;
		fsqrt;
		fstp mag;
		}
		mag/=*tWidthList++;
		res.x=SLong(rx/mag);
		res.z=SLong(rz/mag);
	}
	pVNorm[i].x=SLong(pCur->x*(*tWidthList));
	pVNorm[i].z=SLong(pCur->z*(*tWidthList));
	delete[]pWidths;

	//generate point information for the route polys
	DoPointStruc* pPoints=SHAPE.newco;
	DoPointStruc* pIns=pPoints;
	tPntList=pntList;
	for (i=0;i<sectCnt+1;i++){
		//Generate 2 points per section
		iVec& off=pVNorm[i];
		COORDS3D& pnt=tileCoords[*tPntList++];
		DoPointStruc& dp0=*pIns++;

		dp0.bodyx.i=pnt.X+off.x+viewCoords.X;
		dp0.bodyy.i=pnt.Y+viewCoords.Y;
		dp0.bodyz.i=pnt.Z+off.z+viewCoords.Z;
		_matrix.transform(fpviewer_matrix,dp0);
		_matrix.body2screen(dp0);

		DoPointStruc& dp1=*pIns++;
		dp1.bodyx.i=pnt.X-off.x+viewCoords.X;
		dp1.bodyy.i=pnt.Y+viewCoords.Y;
		dp1.bodyz.i=pnt.Z-off.z+viewCoords.Z;
		_matrix.transform(fpviewer_matrix,dp1);
		_matrix.body2screen(dp1);
	}
	delete[]pVNorm;
	delete[]pSNorm;
	//render the route polys
	pIns=pPoints;
	for (i=0;i<sectCnt;i++){
		SWord vScale=v[1]*pSLen[i]/pRD->width;
		bool visible;
		CLIPFLAGS3D flag;
		flag=(CLIPFLAGS3D)(pIns[3].clipFlags|pIns[2].clipFlags|pIns[0].clipFlags);
		if (flag==CF3D_NULL) visible=true;
		else{
			flag=(CLIPFLAGS3D)(CF3D_ALL&pIns[3].clipFlags&pIns[2].clipFlags&pIns[0].clipFlags);
			if (flag!=CF3D_NULL) visible=false;
			else visible=true;
		}
		if (visible){
			POLYGON.createpoly(pImage,(ColourRange)-1);
			POLYGON.createvert(pIns[3],u[0],v[0]);
			POLYGON.createvert(pIns[2],u[1],v[0]);
			POLYGON.createvert(pIns[0],u[1],vScale);
			POLYGON.drawpoly();
		}
		flag=(CLIPFLAGS3D)(pIns[1].clipFlags|pIns[3].clipFlags|pIns[0].clipFlags);
		if (flag==CF3D_NULL) visible=true;
		else{
			flag=(CLIPFLAGS3D)(CF3D_ALL&pIns[1].clipFlags&pIns[3].clipFlags&pIns[0].clipFlags);
			if (flag!=CF3D_NULL) visible=false;
			else visible=true;
		}
		if (visible){
			POLYGON.createpoly(pImage,(ColourRange)-1);
			POLYGON.createvert(pIns[1],u[0],vScale);
			POLYGON.createvert(pIns[3],u[0],v[0]);
			POLYGON.createvert(pIns[0],u[1],vScale);
			POLYGON.drawpoly();
		}
		pIns+=2;
	}
	delete[]pSLen;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MedDetailRoute
//Author		Paul.   
//Date			Tue 14 Apr 1998
//------------------------------------------------------------------------------
void LandScape::MedDetailRoute(UByte*& pDataStream,ULong& dataLen,int lineCount,COORDS3D& viewCoords)
{
	DoPointStruc* pPoints = SHAPE.newco;
	while (lineCount--){
		Colour lineCol;
	 	UByte routeCol=*pDataStream++;
		RouteData* pRD=pRouteData->find(routeCol);
		UByte sectionCnt=(*pDataStream++)-1;	//no of sections in this line
		if (pRD!=NULL&&pRD->colour!=ARTWORKMASK){
			Colour lineCol=pRD->colour;
			UByte p0=*pDataStream++;
			while (sectionCnt--){
				UByte p1=*pDataStream++;
				//draw line from p0 to p1
				LINETYPE ltLine;
				struct vertex startVertex,endVertex;
				ltLine.ltType=LineType::LT_PlainColour;
				ltLine.lpStartVertex=&startVertex;
				ltLine.lpEndVertex=&endVertex;
				ltLine.colour=lineCol;
				startVertex.bx=pPoints[p0].bodyx;
				startVertex.by=pPoints[p0].bodyy;
				startVertex.bz=pPoints[p0].bodyz;
				endVertex.bx=pPoints[p1].bodyx;
				endVertex.by=pPoints[p1].bodyy;
				endVertex.bz=pPoints[p1].bodyz;
				currscreen->DoHardLine(&ltLine);
				p0=p1;
			}
		}
		else pDataStream+=sectionCnt; //Skip invisible lines
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowDetailRoute
//Author		Paul.   
//Date			Tue 14 Apr 1998
//------------------------------------------------------------------------------
void LandScape::LowDetailRoute(UByte*& pDataStream,ULong& dataLen,int lineCount,COORDS3D& viewCoords)
{
	DoPointStruc* pPoints = SHAPE.newco;
	while (lineCount--){
		Colour lineCol;
	 	UByte routeCol=*pDataStream++;
		RouteData* pRD=pRouteData->find(routeCol);
		UByte sectionCnt=(*pDataStream++)-1;	//no of sections in this line
		if (pRD!=NULL&&pRD->colour!=ARTWORKMASK){
			Colour lineCol=pRD->colour;
			UByte p0=*pDataStream++;
			while (sectionCnt--){
				UByte p1=*pDataStream++;
				//draw line from p0 to p1
				LINETYPE ltLine;
				struct vertex startVertex,endVertex;
				ltLine.ltType=LineType::LT_PlainColour;
				ltLine.lpStartVertex=&startVertex;
				ltLine.lpEndVertex=&endVertex;
				ltLine.colour=lineCol;
				startVertex.bx=pPoints[p0].bodyx;
				startVertex.by=pPoints[p0].bodyy;
				startVertex.bz=pPoints[p0].bodyz;
				endVertex.bx=pPoints[p1].bodyx;
				endVertex.by=pPoints[p1].bodyy;
				endVertex.bz=pPoints[p1].bodyz;
				currscreen->DoHardLine(&ltLine);
				p0=p1;
			}
		}
		else pDataStream+=sectionCnt; //Skip invisible lines
	}
}


////////////////////////////////////////////////////////////////////////////////
//
//					LANDSCAPE POLY THROW OUT ROUTINES
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Macro			COMPCODE
//Author		Paul.   
//Date			Wed 29 Jan 1997
//
//Description	Test a point against all six plains that bound the
//				view cone and returns a set of flags to indicate 
//				which side of each plain the point lies
//
//Inputs		point defined as a fpCOORDS3D struct
//
//Returns		out code as a value of type CLIPFLAGS3D
//
//------------------------------------------------------------------------------
#define COMPCODE(pnt,outcode)				\
		(outcode)=CF3D_NULL;					\
		if ((pnt).Z.f<0.0)					\
		{									\
			(outcode)|=CF3D_BEHINDNEARZ;			\
			(pnt).Z.f = -(pnt).Z.f;			\
		}									\
		else								\
			if ((pnt).Z.f>MaxVRange)		\
				(outcode)|=CF3D_PASTFARZ;		\
											\
		if ((pnt).X.f<0.0)					\
		{									\
			(pnt).X.f = -(pnt).X.f;			\
			if ((pnt).X.f>(pnt).Z.f)		\
				(outcode)|=CF3D_OFFLEFT;		\
		}									\
		else								\
			if ((pnt).X.f>(pnt).Z.f)		\
				(outcode)|=CF3D_OFFRIGHT;		\
											\
		if ((pnt).Y.f<0.0)					\
		{									\
			(pnt).Y.f *= -1.0;				\
			if ((pnt).Y.f>(pnt).Z.f)		\
				(outcode)|=CF3D_OFFBOTTOM;		\
		}									\
		else								\
		{									\
			if ((pnt).Y.f>(pnt).Z.f)		\
				(outcode)|=CF3D_OFFTOP;			\
		}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Macro			XPROD
//Author		Paul.   
//Date			Thu 30 Jan 1997
//
//Description	Cross product macro
//
//Inputs		3 points from the poly defined as landvertex structs
//
//Returns		Bool 	TRUE if the poly faces the viewer
//						FALSE if it faces away from the viewer
//
//------------------------------------------------------------------------------
#define	XPRODUCT(p1,p2,p3,outcode)						\
		{												\
			fpCOORDS3D	v1,v2;							\
			Float		result;							\
								 						\
			v1.X.f = (p1).bodyx.f - (p2).bodyx.f;		\
			v1.Y.f = (p1).bodyy.f - (p2).bodyy.f;		\
														\
			v2.X.f = (p3).bodyx.f - (p2).bodyx.f;		\
			v2.Y.f = (p3).bodyy.f - (p2).bodyy.f;		\
														\
			result = (v1.X.f*v2.Y.f) - (v1.Y.f*v2.X.f);	\
														\
			if (result<0.0)								\
				(outcode)=FALSE;						\
			else										\
				(outcode)=TRUE;							\
		}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroundTileCone
//Author		Paul.   
//Date			Wed 29 Jan 1997
//
//Description	Ground tile visible cone test	
//
//Inputs		Ground tile world coordinates
//
//Returns		TRUE if the tile (or part of the tile) passes
//					through the visible cone
//				FALSE if the tile is not visible
//
//------------------------------------------------------------------------------
/*Bool LandScape::GroundTileCone(SLong wx,SLong wz,SLong width,SLong height)
{
	Float	MaxVRange = (Float)gvisrange;

	fpCOORDS3D	fpcoord;

	SLong	flippedwz;

	CLIPFLAGS3D	pioflags[4],*pioflagp=pioflags;

	//Set up the flags for each corner of the tile
	//If the resulting flags for any of the four points
	//is == CF3D_NULL then the tile can be trivially accepted
	//and the remaining tests are not required

	/************* POINT 1 ************** /

	fpcoord.X.i=wx; fpcoord.Z.i=wz;

	flippedwz=WORLD_BIG_WZ-fpcoord.Z.i;

	GetLandscapeData(fpcoord.X.i,fpcoord.Z.i,fpcoord.Y.i);

	fpcoord.X.i -= viewer_x;
	fpcoord.Y.i -= viewer_y;
	fpcoord.Z.i -= viewer_z;

	_matrix.transform(	fpviewer_matrix,
						fpcoord.X,fpcoord.Y,fpcoord.Z);

	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;

	/************* POINT 2 ************** /

	fpcoord.X.i=wx+width; fpcoord.Z.i=wz;

	flippedwz=WORLD_BIG_WZ-fpcoord.Z.i;

	GetLandscapeData(fpcoord.X.i,fpcoord.Z.i,fpcoord.Y.i);

	fpcoord.X.i -= viewer_x;
	fpcoord.Y.i -= viewer_y;
	fpcoord.Z.i -= viewer_z;

	_matrix.transform(	fpviewer_matrix,
						fpcoord.X,fpcoord.Y,fpcoord.Z);
	
	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;

	/************* POINT 3 ************** /

	fpcoord.X.i=wx+width; fpcoord.Z.i=wz+height;

	flippedwz=WORLD_BIG_WZ-fpcoord.Z.i;

	GetLandscapeData(fpcoord.X.i,fpcoord.Z.i,fpcoord.Y.i);

	fpcoord.X.i -= viewer_x;
	fpcoord.Y.i -= viewer_y;
	fpcoord.Z.i -= viewer_z;

	_matrix.transform(	fpviewer_matrix,
						fpcoord.X,fpcoord.Y,fpcoord.Z);
	
	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;

	/************* POINT 4 ************** /

	fpcoord.X.i=wx; fpcoord.Z.i=wz+height;

	flippedwz=WORLD_BIG_WZ-fpcoord.Z.i;

	GetLandscapeData(fpcoord.X.i,fpcoord.Z.i,fpcoord.Y.i);

	fpcoord.X.i -= viewer_x;
	fpcoord.Y.i -= viewer_y;
	fpcoord.Z.i -= viewer_z;

	_matrix.transform(	fpviewer_matrix,
						fpcoord.X,fpcoord.Y,fpcoord.Z);
	
	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	//Can't trivially accept this tile so more
	//checks are required

	//If all four points are outside the same plane
	//then the tile can be rejected

	if ((pioflags[0] & pioflags[1] & pioflags[2] & pioflags[3])!=CF3D_NULL)
		return (FALSE);

	//If any of the line segments joining the four points
	//may cross the visible area then the tile must be 
	//accepted

	if ((pioflags[0] & pioflags[1])==CF3D_NULL)	return (TRUE);

	if ((pioflags[1] & pioflags[2])==CF3D_NULL)	return (TRUE);

	if ((pioflags[2] & pioflags[3])==CF3D_NULL)	return (TRUE);

	if ((pioflags[3] & pioflags[0])==CF3D_NULL)	return (TRUE);

	//Don't forget the diagonals

	if ((pioflags[0] & pioflags[2])==CF3D_NULL)	return (TRUE);

	if ((pioflags[1] & pioflags[3])==CF3D_NULL)	return (TRUE);

	//If we get here then the tile can be rejected

	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SkyTileCone
//Author		Paul.   
//Date			Wed 29 Jan 1997
//
//Description	Sky tile visible cone test	
//
//Inputs		Sky tile world coordinates
//
//Returns		TRUE if the tile (or part of the tile) passes
//					through the visible cone
//				FALSE if the tile is not visible
//
//------------------------------------------------------------------------------
Bool LandScape::SkyTileCone(SLong wx,SLong wz,SLong width,SLong height)
{
	Float	MaxVRange = (Float)cvisrange;

	fpCOORDS3D	fpcoord;

	CLIPFLAGS3D	pioflags[4],*pioflagp=pioflags;

	//Set up the flags for each corner of the tile
	//If the resulting flags for any of the four points
	//is == CF3D_NULL then the tile can be trivially accepted
	//and the remaining tests are not required

	fpcoord.X.i=wx; fpcoord.Y.i=cloud_base; fpcoord.Z.i=wz;

	fpcoord.X.i -= viewer_x;
	fpcoord.Y.i -= viewer_y;
	fpcoord.Z.i -= viewer_z;

	_matrix.transform(	fpviewer_matrix,
						fpcoord.X,fpcoord.Y,fpcoord.Z);
	
	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;


	fpcoord.X.i=wx+width; fpcoord.Y.i=cloud_base; fpcoord.Z.i=wz;

	fpcoord.X.i -= viewer_x;
	fpcoord.Y.i -= viewer_y;
	fpcoord.Z.i -= viewer_z;

	_matrix.transform(	fpviewer_matrix,
						fpcoord.X,fpcoord.Y,fpcoord.Z);
	
	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;


	fpcoord.X.i=wx+width; fpcoord.Y.i=cloud_base; fpcoord.Z.i=wz+height;

	fpcoord.X.i -= viewer_x;
	fpcoord.Y.i -= viewer_y;
	fpcoord.Z.i -= viewer_z;

	_matrix.transform(	fpviewer_matrix,
						fpcoord.X,fpcoord.Y,fpcoord.Z);
	
	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;


	fpcoord.X.i=wx; fpcoord.Y.i=cloud_base; fpcoord.Z.i=wz+height;

	fpcoord.X.i -= viewer_x;
	fpcoord.Y.i -= viewer_y;
	fpcoord.Z.i -= viewer_z;

	_matrix.transform(	fpviewer_matrix,
						fpcoord.X,fpcoord.Y,fpcoord.Z);
	
	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	//Can't trivially accept this tile so more
	//checks are required

	//If all four points are outside the same plane
	//then the tile can be rejected

	if ((pioflags[0] & pioflags[1] & pioflags[2] & pioflags[3])!=CF3D_NULL)
		return (FALSE);

	//If any of the line segments joining the four points
	//may cross the visible area then the tile must be 
	//accepted

	if ((pioflags[0] & pioflags[1])==CF3D_NULL)	return (TRUE);

	if ((pioflags[1] & pioflags[2])==CF3D_NULL)	return (TRUE);

	if ((pioflags[2] & pioflags[3])==CF3D_NULL)	return (TRUE);

	if ((pioflags[3] & pioflags[0])==CF3D_NULL)	return (TRUE);

	//Don't forget the diagonals

	if ((pioflags[0] & pioflags[2])==CF3D_NULL)	return (TRUE);

	if ((pioflags[1] & pioflags[3])==CF3D_NULL)	return (TRUE);

	//If we get here then the tile can be rejected

	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InCone
//Author		Paul.   
//Date			Wed 29 Jan 1997
//
//Description	Similar to above routine
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*DEAD Bool LandScape::InCone(landvertex& p0,landvertex& p1,landvertex& p2,landvertex& p3)
{
	Float	MaxVRange = (Float)gvisrange;

	fpCOORDS3D	fpcoord;

	CLIPFLAGS3D	pioflags[4],*pioflagp=pioflags;

	//Set up the flags for each corner of the tile
	//If the resulting flags for any of the four points
	//is == CF3D_NULL then the tile can be trivially accepted
	//and the remaining tests are not required


	fpcoord.X.f=p0.bodyx.f;
	fpcoord.Y.f=p0.bodyy.f;
	fpcoord.Z.f=p0.bodyz.f;

	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;


	fpcoord.X.f=p1.bodyx.f;
	fpcoord.Y.f=p1.bodyy.f;
	fpcoord.Z.f=p1.bodyz.f;

	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;


	fpcoord.X.f=p2.bodyx.f;
	fpcoord.Y.f=p2.bodyy.f;
	fpcoord.Z.f=p2.bodyz.f;

	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;


	fpcoord.X.f=p3.bodyx.f;
	fpcoord.Y.f=p3.bodyy.f;
	fpcoord.Z.f=p3.bodyz.f;

	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	//Can't trivially accept this tile so more
	//checks are required

	//If all four points are outside the same plane
	//then the tile can be rejected

	if ((pioflags[0] & pioflags[1] & pioflags[2] & pioflags[3])!=CF3D_NULL)
		return (FALSE);

	//If any of the line segments joining the four points
	//may cross the visible area then the tile must be 
	//accepted

	if ((pioflags[0] & pioflags[1])==CF3D_NULL)	return (TRUE);

	if ((pioflags[1] & pioflags[2])==CF3D_NULL)	return (TRUE);

	if ((pioflags[2] & pioflags[3])==CF3D_NULL)	return (TRUE);

	if ((pioflags[3] & pioflags[0])==CF3D_NULL)	return (TRUE);

	//Don't forget the diagonals

	if ((pioflags[0] & pioflags[2])==CF3D_NULL)	return (TRUE);

	if ((pioflags[1] & pioflags[3])==CF3D_NULL)	return (TRUE);

	//If we get here then the tile can be rejected

	return(FALSE);
}
DEAD*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TriCone
//Author		Paul.   
//Date			Wed 29 Jan 1997
//
//Description	Special cone check for triangular polys
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*DEAD Bool LandScape::TriCone(landvertex& p0,landvertex& p1,landvertex& p2)
{
	Float	MaxVRange = (Float)gvisrange;

	fpCOORDS3D	fpcoord;

	CLIPFLAGS3D	pioflags[3],*pioflagp=pioflags;

	//Set up the flags for each corner of the tile
	//If the resulting flags for any of the four points
	//is == CF3D_NULL then the tile can be trivially accepted
	//and the remaining tests are not required


	fpcoord.X.f=p0.bodyx.f;
	fpcoord.Y.f=p0.bodyy.f;
	fpcoord.Z.f=p0.bodyz.f;

	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;


	fpcoord.X.f=p1.bodyx.f;
	fpcoord.Y.f=p1.bodyy.f;
	fpcoord.Z.f=p1.bodyz.f;

	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	pioflagp++;


	fpcoord.X.f=p2.bodyx.f;
	fpcoord.Y.f=p2.bodyy.f;
	fpcoord.Z.f=p2.bodyz.f;

	COMPCODE(fpcoord,*pioflagp)
	
	//Test to see if this point is visible

	if (*pioflagp==CF3D_NULL)	return (TRUE);

	//Can't trivially accept this triangle so more
	//checks are required

	//If all three points are outside the same plane
	//then the triangle can be rejected

	if ((pioflags[0] & pioflags[1] & pioflags[2])!=CF3D_NULL)
		return (FALSE);

	//If any of the line segments joining the three points
	//may cross the visible area then the tile must be 
	//accepted

	if ((pioflags[0] & pioflags[1])==CF3D_NULL)	return (TRUE);

	if ((pioflags[1] & pioflags[2])==CF3D_NULL)	return (TRUE);

	if ((pioflags[2] & pioflags[0])==CF3D_NULL)	return (TRUE);

	//If we get here then the tile can be rejected

	return(FALSE);
}
DEAD*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TwoTriCone
//Author		Paul.   
//Date			Wed 29 Jan 1997
//
//Description	Specialised cone check routine for a square tile made
//				up from two triangles - also includes a cross product 
//				test.
//
//				A---------------B
//				|              /|
//				|             / |
//				|            /  |
//				|           /   |
//				|    (1)   /    |
//				|         /     |
//				|        /      |
//				|       /       |
//				|      /        |
//				|     /         |
//				|    /          |
//				|   /     (2)   |
//				|  /            |
//				| /             |
//				|/              |
//				D---------------C
//
//Inputs		four corner points of the tile	
//
//Returns		0x0000 .... Both triangles are out of view
//				0x0001 .... Only triangle (1) is visible
//				0x0002 .... Only triangle (2) is visible
//				0x0003 .... Both triangles are visible
//
//------------------------------------------------------------------------------
/*DEAD UWord LandScape::TwoTriCone(landvertex& p0,landvertex& p1,
							landvertex& p2,landvertex& p3)
{
	Float		MaxVRange;
	fpCOORDS3D	fpcoord;
	UWord		result;
	CLIPFLAGS3D	codeA,codeB,codeC,codeD;
	Bool		xpresult;
	
	MaxVRange=(Float)gvisrange;

	result=0x0000;

	//(A)==p0, (B)==p1, (C)==p2, (D)==p3

	//Generate code for point (B)

	fpcoord.X.f=p1.bodyx.f;
	fpcoord.Y.f=p1.bodyy.f;
	fpcoord.Z.f=p1.bodyz.f;

	COMPCODE(fpcoord,codeB)

	//if (B) is visible accept both (1) and (2) as
	//being visible and move on to cross 
	//product check (CPC)

	if (codeB==CF3D_NULL)
		result=0x0001|0x0002;
	else
	{
		//Generate code for point (D)

		fpcoord.X.f=p3.bodyx.f;
		fpcoord.Y.f=p3.bodyy.f;
		fpcoord.Z.f=p3.bodyz.f;

		COMPCODE(fpcoord,codeD)

		//if (D) is visible accept both (1) and (2) as
		//being visible and move on to cross
		//product check (CPC)

		if (codeD==CF3D_NULL)
			result=0x0001|0x0002;
		else
		{
			//if line segment (BD) is visible accept both (1) and (2)
			//as being visible and move on to cross
			//product check (CPC)

			if ((codeB & codeD)==CF3D_NULL)
				result=0x0001|0x0002;
			else
			{
				//Generate code for point (A)

				fpcoord.X.f=p0.bodyx.f;
				fpcoord.Y.f=p0.bodyy.f;
				fpcoord.Z.f=p0.bodyz.f;

				COMPCODE(fpcoord,codeA)

				//if (A) is visible then accept (1) as being visible
				//and move on to other poly checks (OPC)

  				if (codeA==CF3D_NULL)
					result=0x0001;
				else
				{
					//if (ABD) not visible then mark (1) as NOT visible
					//and move on to (OPC)

					if ((codeA & codeB & codeD)==CF3D_NULL)
					{
						//if line segment (AB) is visible accept (1) as being
						//visible and move on to (OPC)

						if ((codeA & codeB)==CF3D_NULL)
							result=0x0001;
						else
						{
							//if line segment (AD) is visible accept (1) as
							//being visible and move on to (OPC)

							if ((codeA & codeD)==CF3D_NULL)
								result=0x0001;

							//else mark (1) as not being visible
						}
					}
				}

//OPC: (other poly checks)

				//Generate code for point (C)

				fpcoord.X.f=p2.bodyx.f;
				fpcoord.Y.f=p2.bodyy.f;
				fpcoord.Z.f=p2.bodyz.f;

				COMPCODE(fpcoord,codeC)

				//if (C) is visible then accept (2) as being visible
				//and move on to (CPC)

				if (codeC==CF3D_NULL)
					result|=0x0002;
				else
				{
					//if (BCD) not visible then mark (2) as NOT visible
					//and move on to (OPC)

					if ((codeB & codeC & codeD)==CF3D_NULL)
					{
						//if line segment (BC) is visible accept (2) as being 
						//visible and move on to (CPC)

						if ((codeB & codeC)==CF3D_NULL)
							result|=0x0002;
						else
						{
							//if line segment (CD) is visible accept (2) as
							//being visible and move on to (CPC)

							if ((codeC & codeD)==CF3D_NULL)
								result|=0x0002;

							//else mark (2) as not being visible
						}
					}
				}
			}
		}
	}

//CPC: (cross product test)

	//if (1) is visible...

	if (result & 0x0001)
	{
		XPRODUCT(p0,p1,p3,xpresult)

		//if cross product (1) fails mark (1) as not
		//being visible

		if (!xpresult)	result &= 0xFFFE;
	}

	//if (2) is visible...

	if (result & 0x0002)
	{
		XPRODUCT(p1,p2,p3,xpresult)

		//if cross product (2) fails mark (2) as not
		//being visible

		if (!xpresult)	result &= 0xFFFD;
	}

	//return is (1) visible + is (2) visible?

	return(result);
}
DEAD*/
////////////////////////////////////////////////////////////////////////////////
//
//					CONTOUR DATA MANIPULATION ROUTINES
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetCloudLevel
//Author		Paul.   
//Date			Mon 16 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetCloudLevel(COORDS3D& world)
{
	return _cloudLayerHeight;	//CEILING_ALT;	//_Collide.CloudAltitude(world);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroundLevel
//Author		Paul.   
//Date			Thu 2 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetGroundLevel(ItemBasePtr src,UByte* pAreaType,bool fReallyGetData)			//RDH 17Jun96
{
	return(GetGroundLevel(src->World,pAreaType,fReallyGetData));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroundLevel
//LastModified:	PD 19Dec95
//Author		Paul.   
//Date			Mon 6 Nov 1995
//
//Description	Need int return rather than modifying coords
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetGroundLevel(COORDS3D& world,UByte* pAreaType,bool fReallyGetData)
{
	return _Collide.GroundAltitude(world,pAreaType,fReallyGetData);
}



////////////////////////////////////////////////////////////////////////////////
//
//						TEXTURE SELECTION ROUTINES
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckRange
//Author		Paul.   
//Date			Wed 7 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*DEAD Bool LandScape::CheckRange(LandObj3DPtr new_object)				//PD 13Mar96
{
	//if the nearest point of this tile > max_body_z then don't
	//insert the object

	Float	min_obj_bz;

	min_obj_bz = new_object->vt0->bodyz.f;

	if(min_obj_bz>new_object->vt1->bodyz.f)
		min_obj_bz=new_object->vt1->bodyz.f;

	if(min_obj_bz>new_object->vt2->bodyz.f)
		min_obj_bz=new_object->vt2->bodyz.f;

	if(min_obj_bz>new_object->vt3->bodyz.f)
		min_obj_bz=new_object->vt3->bodyz.f;

	return(TRUE);
}
DEAD*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderLandPoly
//LastModified:	PD 07Jun96
//Author		Paul.   
//Date			Mon 12 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADvoid LandScape::RenderLandPoly(LandObj3DPtr this_obj3d)			//PD 13Mar96
//DEAD{
//DEAD}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderSkyPoly
//LastModified:	PD 07Jun96
//Author		Paul.   
//Date			Mon 12 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::RenderSkyPoly(LandObj3DPtr this_obj3d)			//PD 13Mar96
{
}

////////////////////////////////////////////////////////////////////////////////
//
//							GENERAL ROUTINES
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LandScape
//LastModified:	PD 20May96
//Author		Paul.   
//Date			Mon 6 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
LandScape::LandScape()
{
//Data for producing roads etc
//type,width(cm),colour,plain texture,x0,y0,x1,y1,masked texture,x0,y0,x1,y1

const LandMapNum coastMap(FIL_ROUTE2_NUM,DIR_LANDMAP2);
const LandMapNum woodMap(FIL_ROUTE1_NUM,DIR_LANDMAP2);
const LandMapNum lakeMap(FIL_ROUTE2_NUM,DIR_LANDMAP2);
const LandMapNum riverMap(FIL_ROUTE3_NUM,DIR_LANDMAP2);
const LandMapNum railMap(FIL_ROUTE1_NUM,DIR_LANDMAP2);
const LandMapNum roadMap(FIL_ROUTE1_NUM,DIR_LANDMAP2);

const LandMapNum coastMsk(FIL_ROUTE2_NUM,DIR_LANDMAP2);
const LandMapNum woodMsk(FIL_ROUTE1_NUM,DIR_LANDMAP2);
const LandMapNum lakeMsk(FIL_ROUTE2_NUM,DIR_LANDMAP2);
const LandMapNum riverMsk(FIL_ROUTE3_NUM,DIR_LANDMAP2);
const LandMapNum railMsk(FIL_ROUTE1_NUM,DIR_LANDMAP2);
const LandMapNum roadMsk(FIL_ROUTE1_NUM,DIR_LANDMAP2);

const RouteData coastRoute(_coast,1000,2000,ARTWORKMASK,coastMap,64,0,127,127,coastMsk,64,0,127,127);
const RouteData woodRoute(_wood,2000,2000,BLACK,woodMap,0,0,63,127,woodMsk,0,0,63,127);
const RouteData lakeRoute(_lake,800,800,ARTWORKMASK,lakeMap,0,0,63,127,lakeMsk,0,0,63,127);
const RouteData riverRoute(_river,4000,8000,Colour(196),riverMap,0,0,63,127,riverMsk,0,0,63,127);
const RouteData railRoute(_rail,3000,3000,Colour(179),railMap,0,0,63,127,railMsk,0,0,63,127);
const RouteData roadRoute(_road,3000,3000,Colour(181),roadMap,64,0,127,127,roadMsk,64,0,127,127);
const RouteData trackRoute(_track,1500,1500,Colour(181),roadMap,64,0,127,127,roadMsk,64,0,127,127);
const RouteData NULLRoute(0xFFFF,2000,2000,BLACK,roadMap,0,0,63,127,roadMsk,0,0,63,127);

	static RouteData routeData[]={
		/* coastRoute,	woodRoute,lakeRoute,*/ 	riverRoute,
		railRoute,	roadRoute, NULLRoute
	};
	pRouteData=routeData;

	cloud_base=CloudsAt10000ft;									//PD 11Oct96
	currscreen=NULL;
	cloudset.X = 0;
	cloudset.Y = 0;
	cloudset.Z = 0;

	gridCorners=NULL;
	gridCone=NULL;
	softGrid=NULL;
	lightCone=NULL;
	pLastGrid=NULL;
	pHTextureGrid=NULL;
	routeDetail=NULL;
	groundDetail=NULL;
	landRnd=NULL;
	tileCoords=NULL;
	pDataBlocks=NULL;
	mistenabled=false;
	FilSkyStrip = FIL_NULL;
	pointList=NULL;
	polyList=NULL;
	meshCreated=false;
	topColor=HORIZON;	//color for top of horizon dome
	midColor=HORIZON;	//color for top of horizon texture strip
	botColor=HORIZON;	//color for horizon fade
	topR=topG=topB=0;
	midR=midG=midB=0;
	imageVTile=1;
	theHorizonStrip=FileNum(NULL);
	highco=NULL;

	CloudAnimP = new UByte[8];									//RJS 21Apr99
	if (CloudAnimP != NULL)										//RJS 21Apr99
	{
		CloudAnimP = sizeof(MinAnimData) + (1<<MINANIM);//RJS 21Apr99

		MinAnimData*	mad = (MinAnimData*) CloudAnimP;
		mad->itemstate = ALIVE;
		mad->nolaunchers = 0;
	}

	#define B(p1) (((p1)<<8)+0xFF)

	static SLightingRGB dawnLighting=
	{
		{B(105), B(84), B(46)},
		{B(158), B(158), B(109)},
		{B(174), B(174), B(94)},
		{B(162), B(165), B(129)},
		{B(252), B(207), B(190)},
		{B(198), B(199), B(223)},
		{B(77), B(59), B(50)},
		{B(206), B(179), B(132)},
		{B(105), B(84), B(46)},
		{B(128),B(128),B(128)},
		{B(255), B(255), B(255)}
	};

	static SLightingRGB dayLighting=
	{
		{B(142), B(166), B(200)},
		{B(208), B(228), B(240)},
		{B(216), B(232), B(248)},
		{B(255), B(255), B(255)},
		{B(159), B(181), B(222)},
		{B(102), B(138), B(201)},
		{B(255), B(255), B(255)},
		{B(248), B(254), B(203)},
		{B(255), B(255), B(255)},
		{B(255), B(255), B(255)},
		{B(255), B(255), B(255)}
	};

	static SLightingRGB duskLighting=
	{
		{B(72), B(77), B(100)},
		{B(199), B(158), B(84)},
		{B(233), B(105), B(50)},
		{B(214), B(113), B(69)},
		{B(149), B(162), B(166)},
		{B(24), B(38), B(63)},
		{B(41), B(55), B(68)},
		{B(236), B(122), B(47)},
		{B(61), B(84), B(112)},
		{B(128),B(128),B(128)},
		{B(255), B(255), B(255)}
	};

	static SLightingRGB niteLighting=
	{
		{B(60), B(82), B(89)},
		{B(94), B(129), B(140)},
		{B(61), B(56), B(116)},
		{B(45), B(43), B(64)},
		{B(82), B(79), B(123)},
		{B(7), B(9), B(30)},
		{B(17), B(23), B(28)},
		{B(60), B(60), B(70)},
		{B(34), B(51), B(71)},
		{B(128),B(128),B(128)},
		{B(255), B(255), B(255)}
	};

	static SLightingRGB badWLighting=
	{
		{0x3fff,0x3fff,0x3fff},		//horizon base
		{0x3fff,0x3fff,0x3fff},		//top of hrzn strip														
		{0x3fff,0x3fff,0x3fff},		//under clouds														
		{0x3fff,0x3fff,0x3fff},		//at clouds														
		{0x3fff,0x3fff,0x3fff},		//above clouds														
		{0x3fff,0x3fff,0x3fff},		//ceiling colour							
		{0x3fff,0x3fff,0x3fff},		//land ambient														
		{0x3fff,0x3fff,0x3fff},		//l-shade ambient														
		{0x3fff,0x3fff,0x3fff},		//other ambient
		{B(255),B(255),B(255)},
		{0x3fff,0x3fff,0x3fff}
	};

	static SLightingRGB mapLighting=
	{
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)},
		{B(255),B(255),B(255)}
	};

	pDawn=&dawnLighting;
	pDay=&dayLighting;
	pDusk=&duskLighting;
	pNite=&niteLighting;
	pBadW=&badWLighting;
	pMapL=&mapLighting;

	currentLighting=dayLighting;	//safe default...
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecDetailLevel
//Author		Paul.   
//Date			Thu 12 Sep 1996
//
//Description	Turns down the detail level by one step
//				if minimum detail is reached then set to maximum
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::DecDetailLevel()
{
	if (Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES])		Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
	else if (Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS])Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
	else if (Save_Data.detail_3d[DETAIL3D_AIRCRAFTSHADOWS])	Save_Data.detail_3d%=DETAIL3D_AIRCRAFTSHADOWS;
	else if (!Save_Data.detail_3d[DETAIL3D_HORIZONFADE])	Save_Data.detail_3d|=DETAIL3D_HORIZONFADE;
	else if (Save_Data.detail_3d[DETAIL3D_ITEMSHADING])		Save_Data.detail_3d%=DETAIL3D_ITEMSHADING;
	else if (Save_Data.detail_3d[DETAIL3D_ITEMSHADOWS])		Save_Data.detail_3d%=DETAIL3D_ITEMSHADOWS;
	else if (Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])	Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;
	else if (Save_Data.detail_3d[DETAIL3D_ROUTES])			Save_Data.detail_3d%=DETAIL3D_ROUTES;
//	else if (Save_Data.detail_3d[DETAIL3D_CONTOURDETAIL])	Save_Data.detail_3d%=DETAIL3D_CONTOURDETAIL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IncDetailLevel
//Author		Paul.   
//Date			Thu 12 Sep 1996
//
//Description	Turns down the detail level by one step
//				if minimum detail is reached then set to maximum
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::IncDetailLevel()
{
//	if (!Save_Data.detail_3d[DETAIL3D_CONTOURDETAIL])		Save_Data.detail_3d|=DETAIL3D_CONTOURDETAIL;
	if (!Save_Data.detail_3d[DETAIL3D_ROUTES])				Save_Data.detail_3d|=DETAIL3D_ROUTES;
	else if (!Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])	Save_Data.detail_3d|=DETAIL3D_GROUNDSHADING;
	else if (!Save_Data.detail_3d[DETAIL3D_ITEMSHADOWS])	Save_Data.detail_3d|=DETAIL3D_ITEMSHADOWS;
	else if (!Save_Data.detail_3d[DETAIL3D_ITEMSHADING])	Save_Data.detail_3d|=DETAIL3D_ITEMSHADING;
	else if (Save_Data.detail_3d[DETAIL3D_HORIZONFADE])		Save_Data.detail_3d%=DETAIL3D_HORIZONFADE;
	else if (!Save_Data.detail_3d[DETAIL3D_AIRCRAFTSHADOWS])Save_Data.detail_3d|=DETAIL3D_AIRCRAFTSHADOWS;
	else if (!Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS])Save_Data.detail_3d|=DETAIL3D_INCONSEQUENTIALS;
	else if (!Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES])	Save_Data.cockpit3Ddetail|=COCK3D_SKYIMAGES;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LandScape
//Author		Paul.   
//Date			Mon 6 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
LandScape::~LandScape()
{
	CloudAnimP.Delete();
//	delete [] CloudAnimP;
//	CloudAnimP = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
//							HORIZON ROUTINES
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoRain
//Author		Robert Slater
//Date			Thu 16 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	LandScape::DoRain(ViewPoint	*vp,SLong	gheight)
{


	// if it is raining and below cloud layer....
	if (Save_Data.gamedifficulty[GD_WEATHEREFFECTS] &&
		vp->World.Y < cloud_base &&
		Manual_Pilot.ControlledAC2 &&
		MMC.Sky.Conditions==1)			//raining!
	{
		int			i;
		SWord		XSeed;
		SWord		YSeed;
		SWord		ZSeed;
		DoPointStruc dp0,dp1;
		LINETYPE	ltLine;
		struct		vertex	startVertex,endVertex;
		Float		z0,z1;
		FPMATRIX		nmat;
		FPMATRIX_PTR	nmatp = &nmat;
		ANGLES			hdg, pitch, roll;
		SLong			theVel = Manual_Pilot.ControlledAC2->velhori;
		SWord			RainHeight = 5;
		SLong			distfromground = gheight;	//vp->World.Y - gheight;
		SLong			theVol;
		UWord			andedFlags;
		Bool			inCockpit = FALSE;
		Bool			drawit;
		Colour			base_colour = (Colour)24;				//RJS 03Jun99

		dp0.intensity=dp1.intensity=-1;

		if (vp->PolyPitEnabled())
			inCockpit = TRUE;

		if (theVel >= 1000)
			theVel = ANGLES_90Deg;
		else
			theVel = (theVel * ANGLES_90Deg)/1000;

		hdg = Manual_Pilot.ControlledAC2->hdg;
		pitch = (Angles) -theVel;
		roll = ANGLES_0Deg;

		_matrix.Generate2(hdg,pitch,roll,1,nmatp);
		_matrix.multiply(nmatp,fpviewer_matrix);

		theVol = 128 - ((distfromground * 128)/10000);
//		if (theVol > 0)
//			_Miles.PlayLooped(FIL_SFX_RAIN_LOOP,NULL,theVol);

		currscreen->DoSetShadeVals(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);

		if (Three_Dee.IsPaused())
		{
			for (i=0; i < 96; i++)
			{
				XSeed = (SByte) SHAPE.Noise(vp->World.X+i,vp->World.Y+i,vp->World.Z+i);
				YSeed = (SByte) SHAPE.Noise(XSeed+i,vp->World.Y+i,vp->World.Z+i);
				ZSeed = (SByte) SHAPE.Noise(vp->World.X+i,YSeed+i,vp->World.Z+i);

				XSeed <<= 4;
				YSeed <<= 4;
				ZSeed <<= 4;

				drawit = TRUE;
				if (inCockpit)
				{
					if (	((XSeed > -800) && (XSeed < 800))
						&&	((YSeed > -800) && (YSeed < 800))
						&&	((ZSeed > -800) && (ZSeed < 800))	)
						drawit = FALSE;
				}

				if (drawit)
				{
					dp0.bodyx.i = XSeed;
					dp0.bodyy.i = YSeed;
					dp0.bodyz.i = ZSeed;
					_matrix.transformNC(nmatp,&dp0);
					_matrix.SetClipFlags(dp0);

					dp1.bodyx.i = XSeed;
					dp1.bodyy.i = YSeed + RainHeight;
					dp1.bodyz.i = ZSeed;
					_matrix.transformNC(nmatp,&dp1);
					_matrix.SetClipFlags(dp1);

					andedFlags=CF3D_ALL;
					andedFlags&=dp0.clipFlags;
					andedFlags&=dp1.clipFlags;
					if (andedFlags == 0 && dp0.bodyz.f>5*100 && dp1.bodyz.f>5*100)
					{
						_matrix.body2screen(dp0);
						_matrix.body2screen(dp1);

						ltLine.ltType 			= LineType::LT_PlainColour;
						ltLine.colour			= base_colour;	//RJS 03Jun99
						ltLine.lpStartVertex 	= &startVertex;
						startVertex.bx			= dp0.bodyx;
						startVertex.by			= dp0.bodyy;
						startVertex.bz			= dp0.bodyz;
						startVertex.clipFlags	= dp0.clipFlags;
						startVertex.intensity	= dp0.intensity;

						ltLine.lpEndVertex 		= &endVertex;
						endVertex.bx			= dp1.bodyx;
						endVertex.by			= dp1.bodyy;
						endVertex.bz			= dp1.bodyz;
						endVertex.clipFlags		= dp1.clipFlags;
						endVertex.intensity		= dp1.intensity;

						currscreen->SetColour(base_colour);		//RJS 03Jun99

						if (currscreen->DoHardLine(&ltLine)==FALSE)
						{
							z0 = dp0.bodyz.f;
							z1 = dp1.bodyz.f;
 							currscreen->zclipline(dp0,dp1);
 							if ((z0>0)&&(z1>0))
							{
 								_matrix.body2screen(dp0);
								_matrix.body2screen(dp1);
 								currscreen->ClipLine3D( dp0.screenx.f,dp0.screeny.f,
							   							dp1.screenx.f,dp1.screeny.f);
							}
						}
					}
				}
			}
		}
		else
		{
			RainHeight = 40;
			for (i=0; i < 96; i++)
			{
				XSeed = Math_Lib.rnd();
				YSeed = Math_Lib.rnd();
				ZSeed = Math_Lib.rnd();
	
				XSeed >>= 4;
				YSeed >>= 4;
				ZSeed >>= 4;

				drawit = TRUE;
				if (inCockpit)
				{
					if (	((XSeed > -600) && (XSeed < 600))
						&&	((YSeed > -400) && (YSeed < 400))
						&&	((ZSeed > -600) && (ZSeed < 600))	)
						drawit = FALSE;
				}

				if (drawit)
				{
					dp0.bodyx.i = XSeed;
					dp0.bodyy.i = YSeed;
					dp0.bodyz.i = ZSeed;
					_matrix.transformNC(nmatp,&dp0);
					_matrix.SetClipFlags(dp0);

					dp1.bodyx.i = XSeed;
					dp1.bodyy.i = YSeed + RainHeight;
					dp1.bodyz.i = ZSeed;
					_matrix.transformNC(nmatp,&dp1);
					_matrix.SetClipFlags(dp1);

					andedFlags=CF3D_ALL;
					andedFlags&=dp0.clipFlags;
					andedFlags&=dp1.clipFlags;
					if (andedFlags == 0 && dp0.bodyz.f>5*100 && dp1.bodyz.f>5*100)
					{
						_matrix.body2screen(dp0);
						_matrix.body2screen(dp1);

						ltLine.ltType 			= LineType::LT_PlainColour;
						ltLine.colour			= base_colour;	//RJS 03Jun99
						ltLine.lpStartVertex 	= &startVertex;
						startVertex.bx			= dp0.bodyx;
						startVertex.by			= dp0.bodyy;
						startVertex.bz			= dp0.bodyz;
						startVertex.clipFlags	= dp0.clipFlags;
						startVertex.intensity	= dp0.intensity;

						ltLine.lpEndVertex 		= &endVertex;
						endVertex.bx			= dp1.bodyx;
						endVertex.by			= dp1.bodyy;
						endVertex.bz			= dp1.bodyz;
						endVertex.clipFlags		= dp1.clipFlags;
						endVertex.intensity		= dp1.intensity;

						currscreen->SetColour(base_colour);		//RJS 03Jun99

						if (currscreen->DoHardLine(&ltLine)==FALSE)
						{
							z0 = dp0.bodyz.f;
							z1 = dp1.bodyz.f;
 							currscreen->zclipline(dp0,dp1);
 							if ((z0>0)&&(z1>0))
							{
 								_matrix.body2screen(dp0);
								_matrix.body2screen(dp1);
 								currscreen->ClipLine3D( dp0.screenx.f,dp0.screeny.f,
							   							dp1.screenx.f,dp1.screeny.f);
							}
						}
					}
				}
			}
		}
	}
}

static UByte scaledToCeil=0;
static int hStep;
//DeadCode PD 18Jan99 static Colour topColour=HORIZON;
//DeadCode PD 18Jan99 static Colour midColour=HORIZON;
//DeadCode PD 18Jan99 static Colour botColour=HORIZON;
//DeadCode PD 18Jan99 static UByte topR=0;
//DeadCode PD 18Jan99 static UByte topG=0;
//DeadCode PD 18Jan99 static UByte topB=0;
//DeadCode PD 18Jan99 static UByte midR=0;
//DeadCode PD 18Jan99 static UByte midG=0;
//DeadCode PD 18Jan99 static UByte midB=0;
//DeadCode PD 18Jan99 static int imageVTile=3;

#include "hdata2.h"

inline void fpTan(ANGLES ang,Float& tanAng)
{
	int iang=ang;
	_asm
	{
	mov eax,iang;
	mov edx,tanAng;
	and eax,0x0000FFFF;
	fldpi;
	push eax;
	fild dword ptr ss:[esp];
	fmulp st(1),st;
	mov dword ptr ss:[esp],32768;
	fild dword ptr ss:[esp];
	fdivp st(1),st;
	fsincos;
	fdivp st(1),st;
	fstp qword ptr ds:[edx];
	add esp,4;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GStrip
//Author		Paul.   
//Date			Tue 19 Jan 1999
//------------------------------------------------------------------------------
void LandScape::GStrip(	DoPointStruc** pp,
						UByte br,UByte bg,UByte bb,
						UByte tr,UByte tg,UByte tb)
{
	if (!(	pp[0]->clipFlags&
			pp[1]->clipFlags&
			pp[2]->clipFlags&
			pp[3]->clipFlags))
	{
		POLYGON.createpoly(POLYTYPE::PT_GColour);
		POLYGON.createvert(*pp[3],br,bg,bb,0xFF);
		POLYGON.createvert(*pp[0],br,bg,bb,0xFF);
		POLYGON.createvert(*pp[1],tr,tg,tb,0xFF);
		POLYGON.createvert(*pp[2],tr,tg,tb,0xFF);
		POLYGON.drawpoly();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateStrip
//Author		Paul.   
//Date			Tue 23 Mar 1999
//------------------------------------------------------------------------------
void LandScape::InfiniteStrip()
{
	const double Max_Range=10.;
	const double cloud_height=.2;
	const int SubDivideLevel=4;

	_cloudLayerHeight=cloud_height*double(CEILING_ALT);

	double fvy=double(viewer_y)/double(CEILING_ALT),fvy2=fvy*fvy;

	DoPointStruc* ptr=SHAPE.newco;

	FPMATRIX mat,scale;

	double *s=(double*)&scale,fvr=double(view_range);

	s[0]=s[8]=fvr;
	s[4]=double(CEILING_ALT);
//OLD_CODE	s[1]=s[2]=s[3]=s[5]=s[6]=s[7]=0;
	s[1]=s[2]=s[5]=s[7]=0;
	s[3]=s[6]=2;
	s[0]*=2;

	_matrix.Generate(ANGLES_0Deg,View_Point->pitch,View_Point->roll,&mat);
	_matrix.multiply(&scale,&mat);

/* 	Generate vertex data for
 *	infinite strip along the
 *	ground
 */
	SLong last_r,last_g,last_b;

	SLong 	r=currentLighting.horizonBase.red()<<8,
			g=currentLighting.horizonBase.green()<<8,
			b=currentLighting.horizonBase.blue()<<8;

	SLong	dr=SLong(currentLighting.horizonMid.red()<<8)-r,
			dg=SLong(currentLighting.horizonMid.green()<<8)-g,
			db=SLong(currentLighting.horizonMid.blue()<<8)-b;

	last_r=r;
	last_g=g;
	last_b=b;

	dr/=3;
	dg/=3;
	db/=3;

	for (int i=0;i<1;i++)
	{
		double this_range=double(i)*Max_Range/4.;
		this_range=this_range*this_range-fvy2;
		if (this_range<0.) this_range=0.;
		else
		{
		_asm{
		fld this_range;
		fsqrt;
		fstp this_range;
		}
		this_range=fvy*(this_range-1.)/this_range;
		}
		SLong rv=r>>8,gv=g>>8,bv=b>>8;
		last_r=r;
		last_g=g;
		last_b=b;
		//r+=dr;
		//g+=dg;
		//b+=db;
		if (this_range>cloud_height)
			break;
		this_range-=fvy;
		ptr->bodyx.f=-s[0]+s[1]*this_range+s[2];
		ptr->bodyy.f=-s[3]+s[4]*this_range+s[5];
		ptr->bodyz.f=-s[6]+s[7]*this_range+s[8];
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
		ptr->bodyx.f=s[0]+s[1]*this_range+s[2];
		ptr->bodyy.f=s[3]+s[4]*this_range+s[5];
		ptr->bodyz.f=s[6]+s[7]*this_range+s[8];
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
	}

	for (i=1;i<SubDivideLevel+1;i++)
	{
		double this_range=double(i)*Max_Range/4.;
		this_range=this_range*this_range-fvy2;
		if (this_range<0.) this_range=0.;
		else
		{
		_asm{
		fld this_range;
		fsqrt;
		fstp this_range;
		}
		this_range=fvy*(this_range-1.)/this_range;
		}
		SLong rv=r>>8,gv=g>>8,bv=b>>8;
		last_r=r;
		last_g=g;
		last_b=b;
		r+=dr;
		g+=dg;
		b+=db;
		if (this_range>cloud_height)
			break;
		this_range-=fvy;
		ptr->bodyx.f=-s[0]+s[1]*this_range+s[2];
		ptr->bodyy.f=-s[3]+s[4]*this_range+s[5];
		ptr->bodyz.f=-s[6]+s[7]*this_range+s[8];
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
		ptr->bodyx.f=s[0]+s[1]*this_range+s[2];
		ptr->bodyy.f=s[3]+s[4]*this_range+s[5];
		ptr->bodyz.f=s[6]+s[7]*this_range+s[8];
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
	}

	double cvy=cloud_height-fvy;
	if (cvy<0) cvy=-cvy;
	fvy2=cvy*cvy;

/* 	Generate vertex data for
 *	infinite strip under the
 *	cloud layer
 */

	r=currentLighting.horizonUnderClouds.red()<<8;
	g=currentLighting.horizonUnderClouds.green()<<8;
	b=currentLighting.horizonUnderClouds.blue()<<8;

	dr=SLong(currentLighting.horizonAtClouds.red()<<8)-r;
	dg=SLong(currentLighting.horizonAtClouds.green()<<8)-g;
	db=SLong(currentLighting.horizonAtClouds.blue()<<8)-b;

	dr>>=2;
	dg>>=2;
	db>>=2;

	for (i=SubDivideLevel+1;--i>=0;)
	{
		double this_range=double(i)*Max_Range/4.;
		this_range=this_range*this_range-fvy2;
		if (this_range<0.) this_range=0.;
		else
		{
		_asm{
		fld this_range;
		fsqrt;
		fstp this_range;
		}
		this_range=cvy*(this_range-1.)/this_range;
		}
		SLong rv=r>>8,gv=g>>8,bv=b>>8;
		last_r=r;
		last_g=g;
		last_b=b;
		r+=dr;
		g+=dg;
		b+=db;
		this_range=cloud_height-this_range;
		if (this_range>cloud_height)
			this_range=cloud_height;
		this_range-=fvy;
		ptr->bodyx.f=-s[0]+s[1]*this_range+s[2];
		ptr->bodyy.f=-s[3]+s[4]*this_range+s[5];
		ptr->bodyz.f=-s[6]+s[7]*this_range+s[8];
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
		ptr->bodyx.f=s[0]+s[1]*this_range+s[2];
		ptr->bodyy.f=s[3]+s[4]*this_range+s[5];
		ptr->bodyz.f=s[6]+s[7]*this_range+s[8];
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
	}

	//cvy=fvy-cloud_height;
	fvy2=cvy*cvy;

/* 	Generate vertex data for
 *	infinite strip above the
 *	cloud layer
 */
	r=currentLighting.horizonAtClouds.red()<<8;
	g=currentLighting.horizonAtClouds.green()<<8;
	b=currentLighting.horizonAtClouds.blue()<<8;

	dr=SLong(currentLighting.horizonAboveClouds.red()<<8)-r;
	dg=SLong(currentLighting.horizonAboveClouds.green()<<8)-g;
	db=SLong(currentLighting.horizonAboveClouds.blue()<<8)-b;

	dr>>=2;
	dg>>=2;
	db>>=2;

	for (i=0;i<SubDivideLevel+1;i++)
	{
		double this_range=double(i)*Max_Range/4.;
		this_range=this_range*this_range-fvy2;
		if (this_range<0.) this_range=0.;
		else
		{
		_asm{
		fld this_range;
		fsqrt;
		fstp this_range;
		}
		this_range=cvy*(this_range-1.)/this_range;
		}
		SLong rv=r>>8,gv=g>>8,bv=b>>8;
		last_r=r;
		last_g=g;
		last_b=b;
		r+=dr;
		g+=dg;
		b+=db;
		this_range=cloud_height+this_range;
		if (this_range<cloud_height) 
		{
			this_range=cloud_height;
			rv=currentLighting.horizonAtClouds.red();
			gv=currentLighting.horizonAtClouds.green();
			bv=currentLighting.horizonAtClouds.blue();
		}
		this_range-=fvy;
		ptr->bodyx.f=-s[0]+s[1]*this_range+s[2];
		ptr->bodyy.f=-s[3]+s[4]*this_range+s[5];
		ptr->bodyz.f=-s[6]+s[7]*this_range+s[8];
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
		ptr->bodyx.f=s[0]+s[1]*this_range+s[2];
		ptr->bodyy.f=s[3]+s[4]*this_range+s[5];
		ptr->bodyz.f=s[6]+s[7]*this_range+s[8];
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
	}

	static double totop_z[]={1.0,.75,.5,.25,0};
	static double fromtop_z[]={-.25,-.5,-.75,-1.0,-1.0,-1.0};
	static double fromtop_y[]={1.0,1.0,1.0,0.9,0.8,0.7};

	SLong steps=sizeof(totop_z)/sizeof(double);
	SLong steps2=sizeof(fromtop_z)/sizeof(double);

	r=last_r=currentLighting.horizonAboveClouds.red()<<8;
	g=last_g=currentLighting.horizonAboveClouds.green()<<8;
	b=last_b=currentLighting.horizonAboveClouds.blue()<<8;

	dr=(SLong(currentLighting.horizonTop.red()<<8)-r)/steps;
	dg=(SLong(currentLighting.horizonTop.green()<<8)-g)/steps;
	db=(SLong(currentLighting.horizonTop.blue()<<8)-b)/steps;

	for (i=0;i<steps;i++)
	{
		double this_z=totop_z[i];
		double this_y=1.-fvy;
		SLong rv=r>>8,gv=g>>8,bv=b>>8;
		last_r=r;
		last_g=g;
		last_b=b;
		r+=dr;
		g+=dg;
		b+=db;
		ptr->bodyx.f=-s[0]+s[1]*this_y+s[2]*this_z;
		ptr->bodyy.f=-s[3]+s[4]*this_y+s[5]*this_z;
		ptr->bodyz.f=-s[6]+s[7]*this_y+s[8]*this_z;
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
		ptr->bodyx.f=s[0]+s[1]*this_y+s[2]*this_z;
		ptr->bodyy.f=s[3]+s[4]*this_y+s[5]*this_z;
		ptr->bodyz.f=s[6]+s[7]*this_y+s[8]*this_z;
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
	}

	r=currentLighting.horizonTop.red()<<8;
	g=currentLighting.horizonTop.green()<<8;
	b=currentLighting.horizonTop.blue()<<8;

	dr=(last_r-r)/steps2;
	dg=(last_g-g)/steps2;
	db=(last_b-b)/steps2;

	for (i=0;i<steps2;i++)
	{
		double this_z=fromtop_z[i];
		double this_y=fromtop_y[i];
		SLong rv=r>>8,gv=g>>8,bv=b>>8;
		last_r=r;
		last_g=g;
		last_b=b;
		r+=dr;
		g+=dg;
		b+=db;
		this_y-=fvy;
		ptr->bodyx.f=-s[0]+s[1]*this_y+s[2]*this_z;
		ptr->bodyy.f=-s[3]+s[4]*this_y+s[5]*this_z;
		ptr->bodyz.f=-s[6]+s[7]*this_y+s[8]*this_z;
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
		ptr->bodyx.f=s[0]+s[1]*this_y+s[2]*this_z;
		ptr->bodyy.f=s[3]+s[4]*this_y+s[5]*this_z;
		ptr->bodyz.f=s[6]+s[7]*this_y+s[8]*this_z;
		ptr->intensity=UByte(rv);
		ptr->specular=UByte(gv);
		ptr->specFlip=UByte(bv);
		_matrix.SetClipFlags(*ptr);
		ptr->clipFlags&=~CF3D_PASTFARZ;
		ptr++;
	}

/*	Calculate the number of
 *	polygons required to
 *	render the horizon
 */

	Float dummy;
	Bool oldZState;

	SLong poly_count=(SLong(ptr-SHAPE.newco)-2)>>1;

	ptr=SHAPE.newco;

	currscreen->DoCalcItemFog(true,dummy,dummy,dummy);
	oldZState=currscreen->DoSetZUpdate(FALSE);
	currscreen->DoEnableBackClip(FALSE);

#define CREATEVERTA(p1)\
	{\
	UByte lr,lg,lb;\
	lr=vr=(p1).intensity;\
	lg=vg=(p1).specular;\
	lb=vb=(p1).specFlip;\
	currscreen->DoGammaCorr(lr,lg,lb);\
	GreyPalette(&lr,&lg,&lb);\
	(p1).intensity=\
	(p1).specular=\
	(p1).specFlip=-1;\
	POLYGON.createvert((p1),lr,lg,lb,0xFF);\
	(p1).intensity=UByte(vr);\
	(p1).specular=UByte(vg);\
	(p1).specFlip=UByte(vb);

#define CREATEVERTB(p1)\
	(p1).intensity=\
	(p1).specular=\
	(p1).specFlip=-1;\
	POLYGON.createvert((p1),lr,lg,lb,0xFF);\
	(p1).intensity=UByte(vr);\
	(p1).specular=UByte(vg);\
	(p1).specFlip=UByte(vb);\
	}
//Old_Code PD 28Apr99 	vr=(p1).intensity;\
//Old_Code PD 28Apr99 	vg=(p1).specular;\
//Old_Code PD 28Apr99 	vb=(p1).specFlip;\
//Old_Code PD 28Apr99 	currscreen->DoGammaCorr(vr,vg,vb);\
//Old_Code PD 28Apr99 	GreyPalette(&vr,&vg,&vb);\
//Old_Code PD 28Apr99 	(p1).intensity=\
//Old_Code PD 28Apr99 	(p1).specular=\
//Old_Code PD 28Apr99 	(p1).specFlip=-1;\
//Old_Code PD 28Apr99 	POLYGON.createvert((p1),vr,vg,vb,0xFF);\
//Old_Code PD 28Apr99 	(p1).intensity=UByte(vr);\
//Old_Code PD 28Apr99 	(p1).specular=UByte(vg);\
//Old_Code PD 28Apr99 	(p1).specFlip=UByte(vb);
//Old_Code PD 28Apr99 
//Old_Code PD 28Apr99 #define CREATEVERTB(p1)\
//Old_Code PD 28Apr99 	(p1).intensity=\
//Old_Code PD 28Apr99 	(p1).specular=\
//Old_Code PD 28Apr99 	(p1).specFlip=-1;\
//Old_Code PD 28Apr99 	POLYGON.createvert((p1),vr,vg,vb,0xFF);\
//Old_Code PD 28Apr99 	(p1).intensity=UByte(vr);\
//Old_Code PD 28Apr99 	(p1).specular=UByte(vg);\
//Old_Code PD 28Apr99 	(p1).specFlip=UByte(vb);


	if (!Save_Data.fSoftware)
	{
		for (i=0;i<poly_count;i++)
		{
			if ((ptr[0].clipFlags&ptr[1].clipFlags&
				ptr[2].clipFlags&ptr[3].clipFlags)==0)
			{
				UByte vr,vg,vb;
				POLYGON.createpoly(POLYTYPE::PT_GColour);
				CREATEVERTA(ptr[1]);
				CREATEVERTB(ptr[0]);
				CREATEVERTA(ptr[2]);
				CREATEVERTB(ptr[3]);
				POLYGON.drawpoly();
			}
			ptr+=2;
		}
	}
	else
	{
		for (i=0;i<poly_count;i++)
		{
			if ((ptr[0].clipFlags&ptr[1].clipFlags&
				ptr[2].clipFlags&ptr[3].clipFlags)==0)
			{
				UByte r1,g1,b1;
				UByte r2,g2,b2;
				r1=UByte(ptr[1].intensity);
				g1=UByte(ptr[1].specular);
				b1=UByte(ptr[1].specFlip);
				r2=UByte(ptr[2].intensity);
				g2=UByte(ptr[2].specular);
				b2=UByte(ptr[2].specFlip);
				currscreen->DoGammaCorr(r1,g1,b1);
				GreyPalette(&r1,&g1,&b1);
				currscreen->DoGammaCorr(r2,g2,b2);
				GreyPalette(&r2,&g2,&b2);
				POLYGON.createpoly(r1,g1,b1,r2,g2,b2);
				POLYGON.gouraudvert(ptr[1],0x00);
				POLYGON.gouraudvert(ptr[0],0x00);
				POLYGON.gouraudvert(ptr[2],0xFF);
				POLYGON.gouraudvert(ptr[3],0xFF);
				POLYGON.drawpoly();
			}
			ptr+=2;
		}
	}

	currscreen->DoSetZUpdate(oldZState);
	currscreen->DoEnableBackClip(TRUE);
	currscreen->DoCalcItemFog(false,dummy,dummy,dummy);

/*	Generate values for fogging
 *	range variables
 */

	UByte 	fr=currentLighting.horizonBase.red(),
			fg=currentLighting.horizonBase.green(),
			fb=currentLighting.horizonBase.blue();

	currscreen->DoGammaCorr(fr,fg,fb);
	GreyPalette(&fr,&fg,&fb);
	currscreen->DoSetHorizonColour(fr,fg,fb);

	SLong fogdist,fogbegin;

	double frsq=double(viewer_y)*double(viewer_y)+fvr*fvr;

	_asm{
	fld frsq;
	fsqrt;
	fstp frsq;
	}

	if (frsq>MMC.Sky.Visibility) frsq=MMC.Sky.Visibility;

	fogdist=SLong(frsq);

	if (!Save_Data.detail_3d[DETAIL3D_HORIZONFADE])	fogbegin=fogdist>>1;
	else											fogbegin=fogdist-(fogdist>>3);
	groundFogBegin=fogbegin;
	groundFogEnd=fogdist;
	SetFogMode(fogbegin,fogdist);

	cloud_base=Cloud_Layer_Height=_cloudLayerHeight;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StripHorizon
//Author		Paul.   
//Date			Fri 9 Oct 1998
//------------------------------------------------------------------------------
void LandScape::StripHorizon()
{
	struct SHCoords	{Float X,Y,Z;} HStripPts[]=
	{
	{-1,0,1}, 		{1,0,1},
	{-1,.125,1},	{1,.125,1},
	{-1,.2-.0125,1},{1,.2-.0125,1},
	{-1,.2,1},		{1,.2,1},		//cloud layer
	{-1,.2125,1},	{1,.2125,1},
	{-1,.4,1},		{1,.4,1},
	{-1,.6,1},		{1,.6,1},
	{-1,.8,1},		{1,.8,1},
	{-1,1,.75},		{1,1,.75},
	{-1,1,.5},		{1,1,.5},
	{-1,1,.25},		{1,1,.25},
	{-1,1,0},		{1,1,0},		//point directly over head
	{-1,1,-.25},	{1,1,-.25},
	{-1,1,-.5},		{1,1,-.5},
	{-1,1,-.75},	{1,1,-.75},
	{-1,.8,-1},		{1,.8,-1}
	};


	
	struct SStripPoly {SLong v[4];}	HStripPoly[]=
	{
	{0,2,3,1},
	{2,4,5,3},
	{4,6,7,5},
	{6,8,9,7},
	{8,10,11,9},
	{10,12,13,11},
	{12,14,15,13},
	{14,16,17,15},
	{16,18,19,17},
	{18,20,21,19},
	{20,22,23,21},
	{22,24,25,23},
	{24,26,27,25},
	{26,28,29,27},
	{28,30,31,29}
	};

	const SLong _stripPoints=sizeof(HStripPts)/sizeof(fpCOORDS3D);
	const SLong _stripPolys=sizeof(HStripPoly)/sizeof(SStripPoly);

	const SLong _topOfTheWorld=10;
	SLong curIndex=0;

	_cloudLayerHeight=HStripPts[6].Y*Float(CEILING_ALT);

	FPMATRIX 	mat,scale;
	Bool 		oldZState;
	Float 		dummy=0.;
	UByte 		br,bg,bb;
	UByte 		tr,tg,tb;

	currscreen->DoCalcItemFog(true,dummy,dummy,dummy);

	br=currentLighting.horizonBase.red();
	bg=currentLighting.horizonBase.green();
	bb=currentLighting.horizonBase.blue();

	tr=currentLighting.horizonMid.red();
	tg=currentLighting.horizonMid.green();
	tb=currentLighting.horizonMid.blue();

	currscreen->DoGammaCorr(br,bg,bb);
	GreyPalette(&br,&bg,&bb);
	currscreen->DoGammaCorr(tr,tg,tb);
	GreyPalette(&tr,&tg,&tb);

	currscreen->DoSetHorizonColour(br,bg,bb);
	oldZState=currscreen->DoSetZUpdate(FALSE);
	currscreen->DoEnableBackClip(FALSE);

	//calculate horizontal scaling factor for the
	//horizon object based on the view cone

	Float fvr=Float(view_range);
	Float fvy=Float(viewer_y)/Float(CEILING_ALT);

	//false horizon test code

//	Float hy=fvy*99./100.;

//	HStripPts[2].Y=HStripPts[3].Y=hy;

	Float 	*m=(Float*)&mat,
			*s=(Float*)&scale;

	_matrix.Generate(ANGLES_0Deg,View_Point->pitch,View_Point->roll,&mat);

	s[0]=s[8]=fvr;
	s[4]=Float(CEILING_ALT);
	s[1]=s[2]=s[3]=s[5]=s[6]=s[7]=0;

	_matrix.multiply(&scale,&mat);

	//transform all the points using this matrix

	DoPointStruc* pdp=SHAPE.newco;
	SHCoords* psp=HStripPts;

	for (SLong i=_stripPoints;i--;)
	{
		Float py=psp->Y-fvy;
		pdp->bodyx.f=s[0]*psp->X+s[1]*py+s[2]*psp->Z;
		pdp->bodyy.f=s[3]*psp->X+s[4]*py+s[5]*psp->Z;
		pdp->bodyz.f=s[6]*psp->X+s[7]*py+s[8]*psp->Z;
		pdp->specular=-1;
		_matrix.SetClipFlags(*pdp);
		pdp->clipFlags&=~CF3D_PASTFARZ;
		pdp++;
		psp++;
	}

	//render the polys

	DoPointStruc* pp[4];

	//draw the strip along the edge of the horizon first

	pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
	pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
	pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
	pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
	GStrip(pp,br,bg,bb,tr,tg,tb);
	curIndex++;

	//next, draw the strip between the last one and the one under
	//the base of the cloud layer

	br=tr;
	bg=tg;
	bb=tb;
//	#pragma message(__HERE__ "PUT THIS BACK AFTER THE RUNNING DEMO")
 	tr=currentLighting.horizonUnderClouds.red();
	tg=currentLighting.horizonUnderClouds.green();
 	tb=currentLighting.horizonUnderClouds.blue();
	currscreen->DoGammaCorr(tr,tg,tb);
	GreyPalette(&tr,&tg,&tb);
	pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
	pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
	pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
	pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
	GStrip(pp,br,bg,bb,tr,tg,tb);
	curIndex++;

	//next, draw the strip under the base of the cloud layer

	br=tr;
	bg=tg;
	bb=tb;
	tr=currentLighting.horizonAtClouds.red();
	tg=currentLighting.horizonAtClouds.green();
	tb=currentLighting.horizonAtClouds.blue();
	currscreen->DoGammaCorr(tr,tg,tb);
	GreyPalette(&tr,&tg,&tb);
	pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
	pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
	pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
	pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
	GStrip(pp,br,bg,bb,tr,tg,tb);
	curIndex++;

	//next, draw the strip above the top of the cloud layer

	br=tr;
	bg=tg;
	bb=tb;
	tr=currentLighting.horizonAboveClouds.red();
	tg=currentLighting.horizonAboveClouds.green();
	tb=currentLighting.horizonAboveClouds.blue();
	currscreen->DoGammaCorr(tr,tg,tb);
	GreyPalette(&tr,&tg,&tb);
	pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
	pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
	pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
	pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
	GStrip(pp,br,bg,bb,tr,tg,tb);
	curIndex++;

	//next, draw all the strips between here and the top of the world

	SLong rval,gval,bval;
	SLong rdda,gdda,bdda;

	br=tr;
	bg=tg;
	bb=tb;
	rval=SLong(br)<<8;
	gval=SLong(bg)<<8;
	bval=SLong(bb)<<8;
	tr=currentLighting.horizonTop.red();
	tg=currentLighting.horizonTop.green();
	tb=currentLighting.horizonTop.blue();
	currscreen->DoGammaCorr(tr,tg,tb);
	GreyPalette(&tr,&tg,&tb);

//	#pragma message(__HERE__ "PUT THIS BACK AFTER THE RUNNING DEMO")
 	rdda=((SLong(tr)<<8)-rval)/(1+_topOfTheWorld-curIndex);
 	gdda=((SLong(tg)<<8)-gval)/(1+_topOfTheWorld-curIndex);
 	bdda=((SLong(tb)<<8)-bval)/(1+_topOfTheWorld-curIndex);
	rdda=gdda=bdda=0;

	for (;curIndex<=_topOfTheWorld;curIndex++)
	{
		pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
		pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
		pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
		pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
		rval+=rdda;
		gval+=gdda;
		bval+=bdda;
		tr=UByte(rval>>8);
		tg=UByte(gval>>8);
		tb=UByte(bval>>8);
		GStrip(pp,br,bg,bb,tr,tg,tb);
		br=tr;
		bg=tg;
		bb=tb;
	}

	for (;curIndex<_stripPolys;curIndex++)
	{
		pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
		pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
		pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
		pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
		GStrip(pp,br,bg,bb,br,bg,bb);
	}

	SLong fogdist,fogbegin;

	Float frsq=Float(viewer_y)*Float(viewer_y)+fvr*fvr;

	_asm
	{
		fld frsq;
		fsqrt;
		fstp frsq;
	}

	//force fog to match visibility settings

	if (frsq>MMC.Sky.Visibility) frsq=MMC.Sky.Visibility;

	//test code... Set visibility to 1km

	fogdist=SLong(frsq);

	if (!Save_Data.detail_3d[DETAIL3D_HORIZONFADE])	fogbegin=fogdist>>1;
	else											fogbegin=fogdist-(fogdist>>2);

	groundFogBegin=fogbegin;
	groundFogEnd=fogdist;
	SetFogMode(fogbegin,fogdist);

	currscreen->DoSetZUpdate(oldZState);						//PD 25Nov98
	currscreen->DoEnableBackClip(TRUE);
	currscreen->DoCalcItemFog(false,dummy,dummy,dummy);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateGroundPoints
//LastModified:	PD 22May96
//Author		Paul.   
//Date			Fri 5 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::GenerateGroundPoints(	SLong range, SLong width,
										SLong& wx1, SLong& wz1, SLong& wx2, SLong& wz2)
{
	SWord	sin_theta,cos_theta;

	SWord	scale;
	SWord	wscale;
	SWord	rsign;

	ANGLES	heading = (ANGLES )(-viewer_hdg);					//PD 12Mar96

	//Scale the range value to prevent o'flows

	if (range<0)
	{
		range= -range;
		rsign= -1;
	}
	else
	{
		rsign= 1;
	}

	for(scale=0;range>0x07FFF;range>>=1,scale++);

	if (rsign==-1)	range= -range;								//PD 22May96

	for(wscale=0;width>0x07FFF;width>>=1,wscale++);				//PD 22May96

	if (bDoingHardware3D)	wscale++;							//PD 15Apr97

	Math_Lib.high_sin_cos(heading,sin_theta,cos_theta);			//PD 23Feb96

	SLong	wx_mid,wz_mid;

	wx_mid = (range * (SLong )sin_theta)/ANGLES_FRACT;			//PD 12Mar96
	
	wx_mid <<= scale;											//PD 12Mar96

	wz_mid = (range * (SLong )cos_theta)/ANGLES_FRACT;			//PD 12Mar96
	
	wz_mid <<= scale;											//PD 12Mar96

	SLong	wx_delta,wz_delta;

	wx_delta = (width * (SLong )cos_theta)/ANGLES_FRACT;		//PD 22May96
	
	wx_delta <<= wscale;										//PD 22May96

	wz_delta = (width * (SLong )sin_theta)/ANGLES_FRACT;		//PD 22May96
	
	wz_delta <<= wscale;										//PD 22May96

	wx1 = viewer_x + wx_mid - wx_delta;

	wz1 = viewer_z + wz_mid + wz_delta;

	wx2 = viewer_x + wx_mid + wx_delta;

	wz2 = viewer_z + wz_mid - wz_delta;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IntenseFromRange
//LastModified:	PD 07Jun96
//Author		Paul.   
//Date			Thu 11 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord LandScape::IntensFromRange(SLong range)
{
	SWord	retval;
	SLong	rangedelta,fadedelta;

	if (range>fade_band_end)	return(255);

	rangedelta = fade_band_end - fade_band_start;

	if (range<fade_band_start-rangedelta)
		return(-255);

	if (range>=fade_band_start)
	{
		fadedelta = range - fade_band_start;

		if (fadedelta<0x7FFFFF)
			retval = (fadedelta<<8)/rangedelta;
		else
			retval = (fadedelta/(rangedelta>>8));
	}
	else
	{
		fadedelta = fade_band_start - range;

		if (fadedelta<0x7FFFFF)
			retval = (fadedelta<<8)/rangedelta;
		else
			retval = (fadedelta/(rangedelta>>8));

		retval =- retval;
	}

	//Clip to max and min.										//PD 26Nov96

	if (retval<-0xFF)	retval=-0xFF;							//PD 27Nov96
	if (retval>0xFF)	retval=0xFF;							//PD 27Nov96

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetViewDetail
//LastModified:	PD 25Mar98
//Author		Paul.   
//Date			Tue 12 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::SetViewDetail()
{
//DeadCode PD 24Nov98 	//rdh need to change to MiG Alley wind
//DeadCode PD 24Nov98 //	switch (MMC.weathernum){
//DeadCode PD 24Nov98 //		case 0:	case 2:	default:
//DeadCode PD 24Nov98 		cloud_base=Cloud_Layer_Height=CloudsAt5000ft;
//DeadCode PD 24Nov98 //		break;
//DeadCode PD 24Nov98 //		case 1: case 3:
//DeadCode PD 24Nov98 //		cloud_base=Cloud_Layer_Height=CloudsAt10000ft;
//DeadCode PD 24Nov98 //		break;
//DeadCode PD 24Nov98 //	}

//DEAD	cloud_base=Cloud_Layer_Height=CloudsAt5000ft;
	bDoingHardware3D=currscreen->DoingHardware3D();

	//Height is the actual height above the current piece of ground data
	SLong height;
	height=viewer_y-GetGroundLevel(*View_Point);				//PD 20Aug98
//DeadCode PD 20Aug98 	if (viewer_y<cloud_base)	height=viewer_y-GetGroundLevel(*View_Point);		//PD 05Jul96
//DeadCode PD 20Aug98 	else						height=viewer_y-cloud_base;

	SLong viewer_range;
	
//	if (Save_Data.detail_3d[DETAIL3D_HORIZONDIST])	viewer_range=0x1F1CDA;
//	else									viewer_range=(0x1F1CDA>>1);
	viewer_range=(0x1F1CDA>>1);

	gnd_band_start=0x160000;//0x5A828;

	if (Key_Tests.KeyPress3d(DETAILUP)) IncDetailLevel();
	else if (Key_Tests.KeyPress3d(DETAILDN)) DecDetailLevel();

	shape_band_start=viewer_range-(viewer_range>>2);

	view_range=viewer_range;
	CalcVisibleRanges(view_range,viewer_y);
//DeadCode PD 01Oct98 	_matrix.SetViewParams(currscreen,ANGLES_90Deg,gvisrange);
	_matrix.SetViewParams(currscreen,Save_Data.fieldOfView,gvisrange);

	gnd_band_end 	= gvisrange;
	sky_band_end 	= cvisrange;
	fade_band_start = gnd_band_start;
	fade_band_end 	= gnd_band_end;

	if (bDoingHardware3D){
		SLong fogstart=gnd_band_start;
		SLong fogend=gvisrange;
		gnd_band_end=sky_band_end=viewer_range;
		currscreen->DoSetFogState(TRUE);
//DeadCode PD 11Aug98 		SetFogMode(gnd_band_start, gnd_band_end);
		currscreen->DoSetMatrices(gvisrange,viewconeangle);
		currscreen->HCls(FALSE);
	}
	POLYGON.setpolyscrn(currscreen,gvisrange,viewconeangle);

	return(height);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVisibleRanges
//Author		Paul.   
//Date			Thu 14 Nov 1996
//
//Description	Caclulates visible ranges for ground and cloud tiles - takes
//				account of the aircrafts altitude
//
//Inputs		flat visible distance
//				viewer_y
//
//Returns		visible ranges for;
//						ground tiles		-	gvisrange
//						cloud tiles			-	cvisrange
//
//------------------------------------------------------------------------------
void LandScape::CalcVisibleRanges(SLong flatd,SLong alt)
{
	//Ground tile distance first

	SLong	dx = (flatd>=0)?flatd:-flatd;
	SLong	dy = (alt>=0)?alt:-alt;								//PD 12Dec96

	if (dy>dx)	{int tmp=dx;dx=dy;dy=tmp;}						//PD 19Aug97

	gvisrange = dx;
	dy >>= 2;
	gvisrange += dy;
	dy >>= 2;
	gvisrange += dy;
	dy >>= 1;
	gvisrange += dy;

	//Under cloud distance next

	dx = (flatd>=0)?flatd:-flatd;								//PD 27Sep97

	dy = (Cloud_Layer_Height - alt);

	dy = (dy>=0)?dy:-dy;

	if (dy>dx)	{int tmp=dx;dx=dy;dy=tmp;}						//PD 02Oct97

	cvisrange = dx;
	dy >>= 2;
	cvisrange += dy;
	dy >>= 2;
	cvisrange += dy;
	dy >>= 1;
	cvisrange += dy;

	//Modify fade ranges based on the viewers altitude for
 	//hardware version ONLY

	if (bDoingHardware3D)
	{
		dx = gnd_band_start;
		dy = (alt<0)?-alt:alt;
		if (dy>dx) {int tmp=dx;dx=dy;dy=tmp;}
		dy>>=2;
		dx+= dy;
		dy>>=2;
		dx+=dy;
		dy>>=1;
		dx+=dy;

		if (dx<gnd_band_end)
			gnd_band_start=dx;
		else
			gnd_band_start=gnd_band_end;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BadVision
//Author		Paul.   
//Date			Thu 20 Jun 1996
//
//Description	Sets blackout stuff going
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool LandScape::BadVision()
{
	if (!Save_Data.gamedifficulty[GD_GEFFECTS] &&
		!Save_Data.gamedifficulty[GD_WHITEOUT])
		return FALSE;

	TDFadeType	tdftFadeType;									//PD 05Jun97

	Bool retval;
	Bool	forceredfade=FALSE;									//RJS 21Oct97

	SLong	fademax = 63;

	AirStruc*	acptr = Manual_Pilot.ControlledAC2;
	if (acptr)
	{
// dont have blackouts in replay playback or in comms sync phase
		if(_Replay.Playback || (_DPlay.Implemented && !_DPlay.synched))
		{
			blackingout = 0;
			redingout   = 0;
		}
		else
		if (Save_Data.gamedifficulty[GD_GEFFECTS])
		{
			FP Blood = acptr->fly.pModel->Blood;	//CSB 09/06/99	
			FP Blackout, Redout;
			for(;;)
			{
				if(Blood < 0.3333)
				{	Redout = 0;		Blackout = 1;				break;	}

				if(Blood < 0.6667)
				{	Redout = 0;		Blackout = 2 - 3 * Blood; 	break;	}

				if(Blood < 1.1667)
				{	Redout = 0;		Blackout = 0;				break;	}
				
				if(Blood < 1.3333)
				{	Blackout = 0;	Redout = 6 * Blood - 7;		break;	}

				Redout	 = 1;
				Blackout = 0;
				break;
			}

			blackingout = UWord(63 * Blackout);
			redingout   = UWord(63 * Redout);
			if((redingout) || (Blood == 1)) forceredfade = TRUE;			//CSB 09/06/99	
		}

//DeadCode CSB 09/06/99			double gforce=acptr->fly.pModel->Inst.NormalAcc;
//DeadCode CSB 09/06/99	
//DeadCode CSB 09/06/99			double	BLACKOUTSTART;
//DeadCode CSB 09/06/99			double	REDOUTSTART;
//DeadCode CSB 09/06/99	
//DeadCode CSB 09/06/99			if (acptr->classtype->phrasename == PHRASE_MIGS) BLACKOUTSTART=6.5; //RDH 10/05/99
//DeadCode CSB 09/06/99			else									BLACKOUTSTART=8.;
//DeadCode CSB 09/06/99	
//DeadCode CSB 09/06/99			REDOUTSTART=-3.;
//DeadCode CSB 09/06/99	
//DeadCode CSB 09/06/99			if (Save_Data.flightdifficulty[FD_POWERBOOST])
//DeadCode CSB 09/06/99			{
//DeadCode CSB 09/06/99				BLACKOUTSTART+=2;
//DeadCode CSB 09/06/99				REDOUTSTART-=1;
//DeadCode CSB 09/06/99			}
//DeadCode CSB 09/06/99	
//DeadCode CSB 09/06/99			//Red out test here
//DeadCode CSB 09/06/99			if (Save_Data.gamedifficulty[GD_GEFFECTS] &&
//DeadCode CSB 09/06/99				gforce<=REDOUTSTART &&
//DeadCode CSB 09/06/99				blackingout==0)								//RJS 14Nov96
//DeadCode CSB 09/06/99			{
//DeadCode CSB 09/06/99				forceredfade = TRUE;								//RJS 21Oct97
//DeadCode CSB 09/06/99				redingout++;
//DeadCode CSB 09/06/99				if (redingout>fademax)								//RJS 12Jun98
//DeadCode CSB 09/06/99					redingout = fademax;							//RJS 12Jun98
//DeadCode CSB 09/06/99			}
//DeadCode CSB 09/06/99			else
//DeadCode CSB 09/06/99			{
//DeadCode CSB 09/06/99				if (redingout-->0)										//RJS 21Oct97
//DeadCode CSB 09/06/99					forceredfade = TRUE;							//RJS 21Oct97
//DeadCode CSB 09/06/99				else
//DeadCode CSB 09/06/99					redingout = 0;
//DeadCode CSB 09/06/99			}
//DeadCode CSB 09/06/99	
//DeadCode CSB 09/06/99			if (!forceredfade)
//DeadCode CSB 09/06/99			{
//DeadCode CSB 09/06/99				if (gforce>=BLACKOUTSTART)								//RJS 21May99
//DeadCode CSB 09/06/99					_Miles.PlayOnce(FIL_SFX_OUT_OF_BREATH2,128);		//RJS 21May99
//DeadCode CSB 09/06/99				//Black out test here
//DeadCode CSB 09/06/99				if (Save_Data.gamedifficulty[GD_GEFFECTS])				//RJS 21Oct97
//DeadCode CSB 09/06/99				{
//DeadCode CSB 09/06/99					if (gforce>=BLACKOUTSTART)
//DeadCode CSB 09/06/99					{
//DeadCode CSB 09/06/99						blackingout++;
//DeadCode CSB 09/06/99						if (blackingout>fademax)							//RJS 12Jun98
//DeadCode CSB 09/06/99							blackingout = fademax;							//RJS 12Jun98
//DeadCode CSB 09/06/99					}
//DeadCode CSB 09/06/99					else
//DeadCode CSB 09/06/99					{
//DeadCode CSB 09/06/99						blackingout--;
//DeadCode CSB 09/06/99						if (blackingout<0)
//DeadCode CSB 09/06/99							blackingout = 0;
//DeadCode CSB 09/06/99					}
//DeadCode CSB 09/06/99				}
//DeadCode CSB 09/06/99				else													//RJS 21Oct97
//DeadCode CSB 09/06/99					blackingout = 0;									//RJS 21Oct97
//DeadCode CSB 09/06/99			}
	}

	if (!blackingout)											//RJS 21Oct97
	{
		//White out test here
 		if (Save_Data.gamedifficulty[GD_WHITEOUT])				//RJS 21Oct97
 		{
			if (SHAPE.SunInVision)
			{
				whitingout++;
				if (whitingout>fademax)									//RJS 12Jun98
					whitingout = fademax;								//RJS 12Jun98
			}
			else
			{
				whitingout--;
				if (whitingout<0)
					whitingout = 0;
			}
 		}
		else													//RJS 21Oct97
 			whitingout = 0;										//RJS 21Oct97
	}

	if (blackingout || forceredfade || whitingout)
	{
		//There will only be 1 fade at a time.
		//The priorities are as follows...
		//red should come first, cos that means you're dead.
		//Redout > Blackout > Whiteout

		GREY3DTYPE	gtdt;

		Bool	fading=FALSE;

		if (forceredfade)										//RJS 21Oct97
		{
			gtdt = (GREY3DTYPE )redingout;						//RJS 21Oct97
			tdftFadeType = _BLACKOUT;							//PD 05Jun97
			fading=TRUE;										//PD 27Nov96
		}
		else
		{
			if (blackingout)									//RJS 21Oct97
			{										
				gtdt = (GREY3DTYPE )blackingout;				//RJS 21Oct97
				tdftFadeType = _REDOUT;							//PD 05Jun97
				fading=TRUE;									//PD 27Nov96
			}
			else
			{
				if (whitingout)									//RJS 21Oct97
				{
					gtdt = (GREY3DTYPE )whitingout;
					tdftFadeType = _WHITEOUT;					//PD 05Jun97
					fading=TRUE;								//PD 27Nov96
				}
			}
		}

		if (fading)												//PD 27Nov96
		{														//PD 09Sep96
			TWODEFFECT tde=TDE_UNIFORM;

			if (!Save_Data.fSoftware)
			{
				Colour	tCol;
				switch (tdftFadeType)
				{
					case _WHITEOUT:	tCol = WHITE; tde = TDE_INSIDE2OUT; break;
					case _BLACKOUT:	tCol = RED; tde = TDE_OUTSIDE2IN; break;
					case _REDOUT:	tCol = BLACK; tde = TDE_OUTSIDE2IN; break;
				}

				currscreen->DoSetFade(tCol,((SLong)gtdt)>>1,tde);//RJS 12Jun98
			}
			else
			{
				switch (tdftFadeType)
				{
				case _WHITEOUT: POLYGON.SetSoftwareFades(2,UWord(gtdt)>>1); break;
				case _BLACKOUT: POLYGON.SetSoftwareFades(1,UWord(gtdt)>>1); break;
				case _REDOUT: POLYGON.SetSoftwareFades(0,UWord(gtdt)>>1); break;
				}
			}
		}														//PD 09Sep96

		retval = TRUE;
	}
	else
	{
		retval = FALSE;
	}

	return (retval);
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFadeStart
//Author		Martin Alderton
//Date			Thu 9 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetFadeStart()
{
	SLong	retval = shape_band_start; //fade_band_start;		//RDH 17Dec96
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFadeEnd
//Author		Martin Alderton
//Date			Thu 9 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetFadeEnd()
{
	SLong	retval = fade_band_end;
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloudLayer
//Author		Paul.   
//Date			Thu 5 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::CloudLayer(ViewPoint* vp)
{
	if (!Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS] || Save_Data.fSoftware)
		return;
	{
  		SLong sectorshift=20;
		SLong sectorsize=1<<sectorshift;
		SLong sectormask=sectorsize-1;
		SLong	sectorsizehalf = sectorsize >> 1;
		SLong	sectorstep;
  
		// All cloud shapes MUST have same anim data...
  		static	ShapeNum	cloudshapes[8]=
  							{
  								CLOUD1,CLOUD2,
  								CLOUD3,CLOUD1,
  								CLOUD1,CLOUD4,
  								CLOUD2,CLOUD2
  							};
  
  		//Insert some clouds in the sky around the viewpoint
  		SLong	oldfaderange=fade_band_end;
		fade_band_end=0x7FFFFFFF;
  
  		item	dummyitem;
  
  		COORDS3D curpos;
  
  		int		cloudselect=0,
				cloudindex;
  
  		int		altselect=0xFF,
				realalt;
  		COORDS3D corner = vp->World;

		UWord	sector_x, sector_z;
		SLong	newX, newZ, newY;
		SLong	wx,wy,wz;
		SLong	RootX;
		int	j,k;

		// For each sector... 4 * 4 clouds...
		// Also fill each neighbouring sector

		sector_x = corner.X >> sectorshift;
		sector_z = corner.Z >> sectorshift;

		corner.X = sector_x << sectorshift;
  		corner.Z = sector_z << sectorshift;
		corner.X -= sectorsize;
		corner.Z -= sectorsize;

//TempCode PD 20Aug98 		sectorstep = sectorsize / 4;
		sectorstep = sectorsize / 2;

 		// corner(X,Y,Z) is start position
		//Init dummy item anim data...
		dummyitem.Anim = CloudAnimP;								//RJS 10Jul98
		RootX = corner.X;

		for (sector_z = 0; sector_z < 3; sector_z++)
		{
			corner.X = RootX;
			for (sector_x = 0; sector_x < 3; sector_x++)
			{
				wy = 0;
				curpos=corner;
  				for (k=0;k<2;k++)
  				{
  					curpos.X = corner.X;
  					for (j=0;j<2;j++)
					{
						wx = corner.X;
						wz = corner.Z;

						newX = curpos.X + ((SHAPE.Noise(wx++,wy++,wz++)-128) << 10);
						newZ = curpos.Z + ((SHAPE.Noise(wx++,wy++,wz++)-128) << 10);
						newY = SHAPE.Noise(newX,wy++,newZ) << 10;

						cloudindex = (7*SHAPE.Noise(newX,newY,newZ))/255;
  
  						dummyitem.World.X = newX;
  						dummyitem.World.Z = newZ;
  						dummyitem.World.Y = FT_15000 + newY;
  						dummyitem.shape = cloudshapes[cloudindex];
  				  
  						Three_Dee.do_object_dummy(&dummyitem,true);	//RJS 30Nov98DONT FUCKING REMOVE!!!
  
  						curpos.X += sectorstep;
  					}
  					curpos.Z += sectorstep;
  				}
				corner.X += sectorsize;
			}
			corner.Z += sectorsize;
		}
  		fade_band_end=oldfaderange;

		dummyitem.Anim = NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DistantClouds
//Author		Paul.   
//Date			Thu 5 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::DistantClouds()
{
//TempCode RJS 09Jul97  	typedef struct	Cloud_Angles
//TempCode RJS 09Jul97  					{
//TempCode RJS 09Jul97  						ANGLES 		hdg,
//TempCode RJS 09Jul97  									pitch;
//TempCode RJS 09Jul97  						ShapeNum 	shape;
//TempCode RJS 09Jul97  					}
//TempCode RJS 09Jul97  					CloudAngles;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  	static	CloudAngles cloudangles[12]=
//TempCode RJS 09Jul97  	{
//TempCode RJS 09Jul97  		{ANGLES_0Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_30Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_60Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_90Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_120Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_150Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_180Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_210Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_240Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_270Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_300Deg	,ANGLES_45Deg	,CLOUD1},
//TempCode RJS 09Jul97  		{ANGLES_330Deg	,ANGLES_45Deg	,CLOUD1}
//TempCode RJS 09Jul97  	};
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  	if (View_Point.World.Y<cloud_base || incloudlayer)
//TempCode RJS 09Jul97  		return;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  	const	SLong farawaybutcloserthanthesun=50000;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  	item	dummyitem;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  	int	k;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  	int	dist,dscale;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  	dist=farawaybutcloserthanthesun;
//TempCode RJS 09Jul97  	dscale=0;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  	while (dist>0x7FFF)	{dist>>=1;dscale++;}
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  	for (k=0;k<12;k++)
//TempCode RJS 09Jul97  	{
//TempCode RJS 09Jul97  		int	deltax,deltay,deltaz;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		SWord	sinang,cosang;
//TempCode RJS 09Jul97  		
//TempCode RJS 09Jul97  		dummyitem.World=View_Point.World;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		dummyitem.shape=cloudangles[k].shape;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		Math_Lib.high_sin_cos(cloudangles[k].pitch,sinang,cosang);
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		deltay=(sinang*dist)/ANGLES_FRACT;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		deltax=(cosang*dist)/ANGLES_FRACT;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		Math_Lib.high_sin_cos(cloudangles[k].pitch,sinang,cosang);
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		deltaz=(cosang*deltax)/ANGLES_FRACT;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		deltax=(sinang*deltax)/ANGLES_FRACT;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		dummyitem.World.X += deltax<<dscale;
//TempCode RJS 09Jul97  		dummyitem.World.Y += deltay<<dscale;
//TempCode RJS 09Jul97  		dummyitem.World.Z += deltaz<<dscale;
//TempCode RJS 09Jul97  
//TempCode RJS 09Jul97  		Three_Dee.do_object(&dummyitem);
//TempCode RJS 09Jul97  	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//	LandScape - first frame setup routines
//				also used while inside cloud layer to make sure the ground is
//				avaliable when the viewer comes out of the clouds
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupGroundData
//Author		Paul.   
//Date			Fri 20 Sep 1996
//
//Description	Loads and pre-fills the cache on entry to the 3D
//				Data is loaded for the area around the piloted a/c
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::SetupGroundData(MovingItem* fselitemp,Bool inclouds)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFogMode
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
void LandScape::SetFogMode(SLong start,SLong end)
{
	Colour	fogcolour;
	UByte hr,hg,hb;

	if (incloudlayer==TRUE)							
	{
		start;
		end <<= 3;
		fogcolour = WHITE;
		hr=hg=hb=0xFF;
	}
	else
	{
		fogcolour = (Colour)0x00;	//currscreen->DoGetHorizonColour();
		hr=currentLighting.horizonBase.red();
		hg=currentLighting.horizonBase.green();
		hb=currentLighting.horizonBase.blue();
	}
	currscreen->DoGammaCorr(hr,hg,hb);
	GreyPalette(&hr,&hg,&hb);
	currscreen->DoSetFog(hr,hg,hb,start,end);
	currscreen->DoSetHorizonColour(hr,hg,hb);
}

void LandScape::SetSkyMap(FileNum	theFile)
{
	FilSkyStrip = theFile;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScaleInsideHorizon
//Author		Paul.   
//Date			Tue 5 May 1998
//------------------------------------------------------------------------------
void LandScape::ScaleInsideHorizon(COORDS3D& pos)
{
	pos.X=gvisrange+viewer_x;
	pos.Y=gvisrange;
	pos.Z=viewer_z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLVector
//Author		Paul.   
//Date			Mon 11 May 1998
//------------------------------------------------------------------------------
void LandScape::SetLVector(COORDS3D& sunPos)
{
	Three_Dee.pMigLand->SetLVector(sunPos.X,sunPos.Y,sunPos.Z);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoScaleFrameRate
//Author		Paul.   
//Date			Wed 18 Nov 1998
//------------------------------------------------------------------------------
void LandScape::AutoScaleFrameRate()
{
	static UByte testingtime=0;
	testingtime++;
	if (testingtime)
		return;
#define FRAMES_RECORDED 20
	static SWord framerec[FRAMES_RECORDED]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	static SWord findex=0;
	if (View_Point && !View_Point->Accel())
	{
		framerec[findex++]=View_Point->RealFrameTime();
		if (findex==FRAMES_RECORDED) findex=0;
	}
	SWord averageFramesPerSec;
	
	if (framerec[FRAMES_RECORDED-1])
	{
		SWord tot=framerec[0];
		for (int i=19;i>0;i--) tot+=framerec[i];
		averageFramesPerSec=(100*FRAMES_RECORDED)/tot;
	}
	else averageFramesPerSec=Save_Data.desiredfps;

#ifdef SHOW_FRAMERATE
	UByte debStr[64];
	sprintf((char*)debStr,"FT: %04d",averageFramesPerSec);
	Mono_Text.PrintAt(0,0,debStr);
#endif

	bool alterDetail;
	SLong wholeAreaSize,halfAreaSize;
	
	wholeAreaSize=_wholeAreaSizeMIN;

	halfAreaSize=wholeAreaSize>>1;

	alterDetail=false;

	if (!Save_Data.detail_3d[DETAIL3D_AUTODETAIL])
	{
		if (!Save_Data.detail_3d[DETAIL3D_CONTOURDETAIL])
		{
			if (land_min_detail!=2)
			{
				land_min_detail=2;
				alterDetail=true;
			}
		}
		else
		{
			if (land_min_detail!=halfAreaSize)
			{
				land_min_detail=halfAreaSize;
				alterDetail=true;
			}
		}

	}
	else if (averageFramesPerSec>(Save_Data.desiredfps+5))
	{
		land_min_detail++;
		if (land_min_detail>halfAreaSize)
			land_min_detail=halfAreaSize;
		else
			alterDetail=true;
		IncDetailLevel();
	}
	else if (averageFramesPerSec<Save_Data.desiredfps)
	{
		land_min_detail--;
		if (land_min_detail<2)
			land_min_detail=2;
		else
			alterDetail=true;
		DecDetailLevel();
	}

	if (alterDetail)
	{
		UByte* pResG=groundDetail;

		UByte min_val;
		if (Save_Data.fSoftware)	min_val=2;
		else						min_val=0;
		for (SLong x=0;x<wholeAreaSize;x++)
		{
			SLong tx=x-halfAreaSize;
			tx*=tx;
			for (SLong y=0;y<wholeAreaSize;y++)
			{
				SLong ty=y-halfAreaSize;
				ty=ty*ty+tx;
				double fp_dist;
				_asm
				{
					fild ty;
					fsqrt;
					fstp fp_dist;
				}
				ty=SLong(fp_dist+.5);
				if (ty<=land_min_detail)	*pResG++=min_val;
				else						*pResG++=254;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Init
//Author		Paul.   
//Date			Thu 14 May 1998
//------------------------------------------------------------------------------
void LandScape::Init()
{
	if (Save_Data.fSoftware)	land_min_detail=4;
	else						land_min_detail=2;

//	SLong cornerBufferSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//							_cornerBufferSizeMAX:_cornerBufferSizeMIN;

//	SLong wholeAreaSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//							_wholeAreaSizeMAX:_wholeAreaSizeMIN;

//	SLong halfAreaSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//							_halfAreaSizeMAX:_halfAreaSizeMIN;
	SLong cornerBufferSize=_cornerBufferSizeMIN;
	SLong wholeAreaSize=_wholeAreaSizeMIN;
	SLong halfAreaSize=_halfAreaSizeMIN;

	if (!gridCorners) gridCorners=new UByte[cornerBufferSize];
	if (!softGrid) softGrid=new UByte[wholeAreaSize*wholeAreaSize];
	if (!gridCone) gridCone=new UByte[wholeAreaSize*wholeAreaSize];
	if (!lightCone) lightCone=new UByte[wholeAreaSize*wholeAreaSize];
	if (!routeDetail) routeDetail=new UByte[wholeAreaSize*wholeAreaSize];
	if (!groundDetail) groundDetail=new UByte[wholeAreaSize*wholeAreaSize];
	if (!landRnd) landRnd=new UByte[256];
	if (!tileCoords) tileCoords=new COORDS3D[256];
	if (!pDataBlocks) pDataBlocks=new DataRecord[wholeAreaSize*wholeAreaSize];

	//Setup random table...
	for (int x=0;x<256;landRnd[x++]=Math_Lib.rnd(SLong(0xFF)));

	//Setup route detail table
	UByte* pResR=routeDetail;
	UByte* pResG=groundDetail;
	for (x=0;x<wholeAreaSize;x++){
		int tx=x-halfAreaSize;
		Float dx=Float(tx); dx*=dx*Float(_blockWidth)*Float(_blockWidth);
	 	for (int y=0;y<wholeAreaSize;y++){
			int ty=y-halfAreaSize;
			Float dy=Float(ty);
			dy*=dy*Float(_blockWidth)*Float(_blockWidth);
			dy+=dx;
			_asm {
			fld dy;
			fsqrt;
			fstp dy;
			}
			ty=int(dy);
			//Fill in route detail grid
			if (ty<_routeMPolySize) *pResR++=UByte(_doMPoly);
			else if (ty<_routePolySize) *pResR++=UByte(_doPoly);
			else if (ty<_routeLineSize) *pResR++=UByte(_doLine);
			else *pResR++=UByte(_doNowt);
			//Fill in land detali grid
			if (ty<_groundHighSize)
				*pResG++=UByte(_doHighGround);
			else if (ty<_groundMedSize)
			{
				ty-=_groundHighSize;
				ty<<=4;
				ty/=(_groundMedSize-_groundHighSize);
				ty++;
				if (ty>3) ty=254;	//overkill to make sure that the tiles
									//are reduced as much as possible
				else ty=0;

				*pResG++=UByte(ty);
			}
			else *pResG++=UByte(254);
		}
	}
	highco=new DoPointStruc[256];
	blackingout=0;
	redingout=0;
	whitingout=0;
	currscreen=NULL;
	lastPx=lastPz=-1;
	ResetLights();

	SHAPE.newprobecnt= 0;		//RJS 01Apr99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Exit
//Author		Paul.   
//Date			Thu 14 May 1998
//------------------------------------------------------------------------------
void LandScape::Exit()
{
	if (gridCorners) delete[]gridCorners,gridCorners=NULL;
	if (gridCone) delete[]gridCone,gridCone=NULL;
	if (lightCone) delete[]lightCone,lightCone=NULL;
	if (routeDetail) delete[]routeDetail,routeDetail=NULL;
	if (groundDetail) delete[]groundDetail,groundDetail=NULL;
	if (landRnd) delete[]landRnd,landRnd=NULL;
	if (tileCoords) delete[]tileCoords,tileCoords=NULL;
	if (pDataBlocks) delete[]pDataBlocks,pDataBlocks=NULL;
	if (polyList) delete[]polyList,polyList=NULL;
	if (pointList) delete[]pointList,pointList=NULL;
	if (pLastGrid) delete[]pLastGrid,pLastGrid=NULL;
	if (pHTextureGrid) delete[]pHTextureGrid,pHTextureGrid=NULL;
	if (highco) delete[]highco,highco=NULL;
	if (softGrid) delete[]softGrid,softGrid=NULL;
	Three_Dee.nomorereallygetdata=false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateImageMap
//Author		Paul.   
//Date			Sat 16 May 1998
//------------------------------------------------------------------------------
ImageMapDesc* LandScape::CreateImageMap(UWord dim)
{
	ImageMapDesc& image=*(ImageMapDescPtr)new UByte[dim*dim+sizeof(ImageMap_Desc)];
	image.w=image.h=dim;
	image.body=UByteP(&image)+sizeof(ImageMapDesc);
	image.alpha=NULL;
	image.palette=NULL;
	image.paletteindex=0;
	image.isMasked=0;
	return &image;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DestroyImageMap
//Author		Paul.   
//Date			Sat 16 May 1998
//------------------------------------------------------------------------------
void LandScape::DestroyImageMap(ImageMapDesc* pImage)
{
	delete[]UByteP(pImage);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTile2ImageMap
//Author		Paul.   
//Date			Sat 16 May 1998
//------------------------------------------------------------------------------
void LandScape::RenderTile2ImageMap(ImageMapDesc* pImage,UByte*& pDataStream,ULong& dataLen)
{
//debug code only!!!
//	memset(pImage->body,0xFE,65536);
//debug code only!!!
	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
	int vertexCount=aph.vertexCount;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pointDefs=(PointDef*)pDataStream;
	pDataStream+=vertexCount*sizeof(PointDef);

	//aph 			- tile header data
	//pointDefs[] 	- tile point coordinates
	//pDataStream 	- ptr to draw data

	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;
	pDataStream+=sizeof(ddh);

	int	polyCount=ddh.noOfPolys;
	int lineCount=ddh.noOfLines;

	while (polyCount--){
	 	CLandColor landCol(*pDataStream++);
		ImageMapDesc* pMap=landCol.pImg();
		UByte rotation=landCol.Rotation();
		int triCount=*pDataStream++;
		while (triCount--){
			int fanCount=*pDataStream++;
			int v1=*pDataStream++;
			int v3=*pDataStream++;
			while (fanCount--){
				int v2=v3;
				v3=*pDataStream++;
				PointDef& p1=pointDefs[v1];
				PointDef& p2=pointDefs[v2];
				PointDef& p3=pointDefs[v3];
				//render this triangle to 'pImage'
				if (pMap!=NULL) RenderTri(rotation,pImage,p1,p2,p3,pMap);
			}		
		}		
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTri
//Author		Paul.   
//Date			Sat 16 May 1998
//------------------------------------------------------------------------------
void LandScape::RenderTri(	UByte rotation,
							ImageMapDesc* pDest,
							PointDef& p1,PointDef& p2,PointDef& p3,
							ImageMapDesc* pImage)
{
	//simple poly scan conversion - no clipping/cross product & only
	//renders triangles

	//find highest point (or points)
	PointDef* pTop=&p1;
	PointDef* pMid=&p2;
	PointDef* pBot=&p3;

	//skip completely flat polys for now...
	if (pTop->z==pMid->z&&pTop->z==pBot->z) return;

	//order the points top to bottom...
	if (pTop->z>pMid->z){
		PointDef* pTemp=pTop; pTop=pMid; pMid=pTemp;
	}
	if (pTop->z>pBot->z){
		PointDef* pTemp=pTop; pTop=pBot; pBot=pTemp;
	}
	if (pMid->z>pBot->z){
		PointDef* pTemp=pMid; pMid=pBot; pBot=pTemp;
	}
	//test for flat top
	bool hasFlatTop=(pTop->z==pMid->z)?true:false;
	//test for flat base
	bool hasFlatBase=(hasFlatTop==false&&pMid->z==pBot->z)?true:false;

	SLong imageWidth=pImage->w;
	SLong imageMask=imageWidth-1;
	UByte* pImageBody=pImage->body;

	if (hasFlatTop){
		//Arrange draw order from left to right...
		if (pTop->x>pMid->x){
			PointDef* pTemp=pTop; pTop=pMid; pMid=pTemp;
		}
		UByte* pScreen=pDest->body;
		SLong sWidth=pDest->w;
		SLong maxWidth=(sWidth-1)<<16;

		SLong scanLines=pBot->z-pTop->z;
		SLong leftX=pTop->x<<16;
		SLong rightX=pMid->x<<16;
		SLong baseX=pBot->x<<16;
		SLong leftDX=(baseX-leftX)/scanLines;
		SLong rightDX=(baseX-rightX)/scanLines;
		SLong startY=pTop->z;
		UByte* pScanLine=pScreen+sWidth*startY;

		for (int i=0;i<scanLines;i++,startY++){
			UByte* pImageScanLine=pImageBody+(startY&imageMask)*imageWidth;
		 	ScanLine(pScanLine,leftX,rightX,pImageScanLine,imageMask);
			leftX+=leftDX;
			if (leftX<0) leftX=0;
			else if (leftX>maxWidth) leftX=maxWidth;
			rightX+=rightDX;
			if (rightX<0) rightX=0;
			else if (rightX>maxWidth) rightX=maxWidth;
			pScanLine+=sWidth;
		}
	}
	else if (hasFlatBase){
		//Arrange draw order from left to right...
		if (pMid->x>pBot->x){
			PointDef* pTemp=pMid; pMid=pBot; pBot=pTemp;
		}
		UByte* pScreen=pDest->body;
		SLong sWidth=pDest->w;
		SLong maxWidth=(sWidth-1)<<16;

		SLong scanLines=pBot->z-pTop->z;
		SLong leftX=pTop->x<<16;
		SLong rightX=leftX;
		SLong leftBaseX=pMid->x<<16;
		SLong rightBaseX=pBot->x<<16;
		SLong leftDX=(leftBaseX-leftX)/scanLines;
		SLong rightDX=(rightBaseX-rightX)/scanLines;
		SLong startY=pTop->z;
		UByte* pScanLine=pScreen+sWidth*startY;

		for (int i=0;i<scanLines;i++,startY++){
			UByte* pImageScanLine=pImageBody+(startY&imageMask)*imageWidth;
		 	ScanLine(pScanLine,leftX,rightX,pImageScanLine,imageMask);
			leftX+=leftDX;
			if (leftX<0) leftX=0;
			else if (leftX>maxWidth) leftX=maxWidth;
			rightX+=rightDX;
			if (rightX<0) rightX=0;
			else if (rightX>maxWidth) rightX=maxWidth;
			pScanLine+=sWidth;
		}
	}
	else if (pMid->x>pTop->x){
		UByte* pScreen=pDest->body;
		SLong sWidth=pDest->w;
		SLong maxWidth=(sWidth-1)<<16;

		SLong leftScanLines=pBot->z-pTop->z;
		SLong rightScanLines=pMid->z-pTop->z;
		SLong leftX=pTop->x<<16;
		SLong rightX=leftX;
		SLong leftBaseX=pBot->x<<16;
		SLong rightBaseX=pMid->x<<16;
		SLong leftDX=(leftBaseX-leftX)/leftScanLines;
		SLong rightDX=(rightBaseX-rightX)/rightScanLines;
		SLong startY=pTop->z;
		UByte* pScanLine=pScreen+sWidth*startY;

		for (int i=0;i<rightScanLines;i++,startY++){
			UByte* pImageScanLine=pImageBody+(startY&imageMask)*imageWidth;
		 	ScanLine(pScanLine,leftX,rightX,pImageScanLine,imageMask);
			leftX+=leftDX;
			if (leftX<0) leftX=0;
			else if (leftX>maxWidth) leftX=maxWidth;
			rightX+=rightDX;
			if (rightX<0) rightX=0;
			else if (rightX>maxWidth) rightX=maxWidth;
			pScanLine+=sWidth;
		}
		rightX=pMid->x<<16;
		rightDX=(leftBaseX-rightX)/(leftScanLines-rightScanLines);

		for (;i<leftScanLines;i++,startY++){
			UByte* pImageScanLine=pImageBody+(startY&imageMask)*imageWidth;
		 	ScanLine(pScanLine,leftX,rightX,pImageScanLine,imageMask);
			leftX+=leftDX;
			if (leftX<0) leftX=0;
			else if (leftX>maxWidth) leftX=maxWidth;
			rightX+=rightDX;
			if (rightX<0) rightX=0;
			else if (rightX>maxWidth) rightX=maxWidth;
			pScanLine+=sWidth;
		}
	}
	else{
		UByte* pScreen=pDest->body;
		SLong sWidth=pDest->w;
		SLong maxWidth=(sWidth-1)<<16;

		SLong leftScanLines=pMid->z-pTop->z;
		SLong rightScanLines=pBot->z-pTop->z;
		SLong leftX=pTop->x<<16;
		SLong rightX=leftX;
		SLong leftBaseX=pMid->x<<16;
		SLong rightBaseX=pBot->x<<16;
		SLong leftDX=(leftBaseX-leftX)/leftScanLines;
		SLong rightDX=(rightBaseX-rightX)/rightScanLines;
		SLong startY=pTop->z;
		UByte* pScanLine=pScreen+sWidth*startY;

		for (int i=0;i<leftScanLines;i++,startY++){
			UByte* pImageScanLine=pImageBody+(startY&imageMask)*imageWidth;
		 	ScanLine(pScanLine,leftX,rightX,pImageScanLine,imageMask);
			leftX+=leftDX;
			if (leftX<0) leftX=0;
			else if (leftX>maxWidth) leftX=maxWidth;
			rightX+=rightDX;
			if (rightX<0) rightX=0;
			else if (rightX>maxWidth) rightX=maxWidth;
			pScanLine+=sWidth;
		}
		leftX=pMid->x<<16;
		leftDX=(rightBaseX-leftX)/(rightScanLines-leftScanLines);

		for (;i<rightScanLines;i++,startY++){
			UByte* pImageScanLine=pImageBody+(startY&imageMask)*imageWidth;
		 	ScanLine(pScanLine,leftX,rightX,pImageScanLine,imageMask);
			leftX+=leftDX;
			if (leftX<0) leftX=0;
			else if (leftX>maxWidth) leftX=maxWidth;
			rightX+=rightDX;
			if (rightX<0) rightX=0;
			else if (rightX>maxWidth) rightX=maxWidth;
			pScanLine+=sWidth;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScanLine
//Author		Paul.   
//Date			Sat 16 May 1998
//------------------------------------------------------------------------------
void LandScape::ScanLine(UByte* pScrAdr,SLong leftX,SLong rightX,UByte* pImage,SLong imageMask)
{
	leftX>>=16;
	rightX>>=16;
	if (leftX>rightX) {SLong tmpX=leftX;leftX=rightX;rightX=tmpX;}
	SLong scanWidth=rightX-leftX;
	pScrAdr+=leftX;
	for (int i=0;i<=scanWidth;i++) *pScrAdr++=pImage[(leftX+i)&imageMask];
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMist
//Author		Paul.   
//Date			Tue 9 Jun 1998
//------------------------------------------------------------------------------
void LandScape::SetMist(DoPointStruc& dp)
{
	//dp is untransformed point
	if (dp.bodyy.i<=_snowLine){
		dp.mist=0;
		if (dp.bodyy.i<=_mistTop){
			SLong temp=((dp.bodyy.i-_mistTop)<<8)/_mistTop;
			if (temp>0xFF) temp=0xFF;
			else if (temp<0) temp=0;
			temp=0xFF-temp;
			dp.snow=UByte(temp);
		}
		else dp.snow=0;
	}
	else if (dp.bodyy.i>=_snowLine+10000)	dp.mist=255;
	else
	{
	 	SLong temp=((dp.bodyy.i-_snowLine)<<8)/10000;
		if (temp>0xFF)		temp=0xFF;
		else if (temp<0)	temp=0;
		dp.mist=UByte(temp);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DisplayBoxes
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
void LandScape::DisplayBoxes()
{
/*	DoPointStruc 	dp[4];
	Rect 			box;
	LINETYPE 		ltLine;
	vertex			sv,ev;
	int	i;

	ltLine.ltType=LineType::LT_PlainColour;
	ltLine.lpStartVertex=&sv;
	ltLine.lpEndVertex=&ev;
	ltLine.colour=Colour(31);

	//Three_Dee.pTMake->GetSquares(boxes);

 	for (i=0;i<25;i++)
//	for (i=1;i<2;i++)
	{
		dp[0].bodyy.i=
			dp[1].bodyy.i=
			dp[2].bodyy.i=
			dp[3].bodyy.i=166666-viewer_y;	//5000ft
		
		//fill in the four dopoint values...

		Three_Dee.pTMake->GetClipRegion(i,box);

		dp[0].bodyx.i=box.l-viewer_x;
		dp[0].bodyz.i=box.t-viewer_z;

		dp[1].bodyx.i=box.r-viewer_x;
		dp[1].bodyz.i=box.t-viewer_z;

		dp[2].bodyx.i=box.r-viewer_x;
		dp[2].bodyz.i=box.b-viewer_z;

		dp[3].bodyx.i=box.l-viewer_x;
		dp[3].bodyz.i=box.b-viewer_z;

		_matrix.transform(fpviewer_matrix,dp[0]);
		_matrix.transform(fpviewer_matrix,dp[1]);
		_matrix.transform(fpviewer_matrix,dp[2]);
		_matrix.transform(fpviewer_matrix,dp[3]);

		//draw four lines to outline each box

		for (int j=0;j<4;j++)
		{
			int k=(j+1)&0x03;

			sv.bx=dp[j].bodyx;
			sv.by=dp[j].bodyy;
			sv.bz=dp[j].bodyz;

			ev.bx=dp[k].bodyx;
			ev.by=dp[k].bodyy;
			ev.bz=dp[k].bodyz;

			currscreen->DoHardLine(&ltLine);
		}
	}
*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		boxClipTest
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
inline UByte boxClipTest(const DoPointStruc& dp,const Rect& r)
{
	UByte rv;

	if (dp.bodyx.i<r.l)	rv=1;
	else if (dp.bodyx.i>r.r) rv=2;
	else rv=0;

	if (dp.bodyz.i<r.t) rv+=4;
	else if (dp.bodyz.i>r.b) rv+=8;

	return rv;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrintDebugs
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
void LandScape::PrintDebugs()
{/*
	UByte block[128];
	block[4]=UByte(0);
	SLong xof=(viewer_x&0x1FFFFF)>>10;	//0..2048
	SLong val=viewer_x>>(17+4);
	block[2]=UByte(val&0x7)+'1';		//x (lo)
	val>>=3;
	block[0]=UByte(val)+'1';			//x (hi)
	SLong zof=2047-((viewer_z&0x1FFFFF)>>10);
	val=viewer_z>>(17+4);
	block[3]=UByte(val&0x7)+'1';		//z (lo)
	val>>=3;
	block[1]=UByte(val)+'1';			//z (hi)
	Mono_Text.PrintAt(0,0,block);		//print block number
	sprintf((char*)block,"xoff %d ",xof);
	Mono_Text.PrintAt(0,1,block);
	sprintf((char*)block,"zoff %d ",zof);
	Mono_Text.PrintAt(0,2,block);
	val=viewer_hdg;
	val=((val&0xFFFF)*90)>>14;
	sprintf((char*)block,"hdg %3d",val);
	Mono_Text.PrintAt(0,3,block);		//print viewer heading
	sprintf((char*)block,"alt %dm ",(viewer_y/100));
	Mono_Text.PrintAt(0,4,block);		//print viewer altitude (meters)
*/}

inline void fpSinCos(ANGLES ang,Float& sinAng,Float& cosAng)
{
	int iang=ang;
	_asm
	{
	mov eax,iang;
	and eax,0x0000FFFF;
	fldpi;
	push eax;
	fild dword ptr ss:[esp];
	fmulp st(1),st;
	mov dword ptr ss:[esp],32768;
	fild dword ptr ss:[esp];
	fdivp st(1),st;
	fsincos;
	mov edx,cosAng;
	fstp qword ptr ds:[edx];
	mov edx,sinAng;
	fstp qword ptr ds:[edx];
	add esp,4;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCloudLayer
//Author		Paul.   
//Date			Fri 23 Oct 1998
//------------------------------------------------------------------------------
void LandScape::DoCloudLayer()
{
	const Float CLOUD_DELTA=.002;
	struct SHCoords
	{
		Float X,Y,Z;	
		SLong flag;
	}
	HStripPtsA[]=
	{
		//outer edge points
		{-1,.202+CLOUD_DELTA,1,0},
		{0,.202+CLOUD_DELTA,1,0},
		{1,.202+CLOUD_DELTA,1,0},
		{1,.202+CLOUD_DELTA,0,0},
		{1,.202+CLOUD_DELTA,-1,0},
		{0,.202+CLOUD_DELTA,-1,0},
		{-1,.202+CLOUD_DELTA,-1,0},
		{-1,.202+CLOUD_DELTA,0,0},

		//end of solid area
		{0,.202,.5,1},
		{.3536,.202,.3536,1},
		{.5,.202,0,1},
		{.3536,.202,-.3536,1},
		{0,.202,-.5,1},
		{-.3536,.202,-.3536,1},
		{-.5,.202,0,1},
		{-.3536,.202,.3536,1},

		//end of transparent area
		{0,.202,.25,2},
		{.1768,.202,.1768,2},
		{.25,.202,0,2},
		{.1768,.202,-.1768,2},
		{0,.202,-.25,2},
		{-.1768,.202,-.1768,2},
		{-.25,.202,0,2},
		{-.1768,.202,.1768,2}
	},
	HStripPtsB[]=
	{
		//outer edge points
		{-1,.202-CLOUD_DELTA,1,0},
		{0,.202-CLOUD_DELTA,1,0},
		{1,.202-CLOUD_DELTA,1,0},
		{1,.202-CLOUD_DELTA,0,0},
		{1,.202-CLOUD_DELTA,-1,0},
		{0,.202-CLOUD_DELTA,-1,0},
		{-1,.202-CLOUD_DELTA,-1,0},
		{-1,.202-CLOUD_DELTA,0,0},

		//end of solid area
		{0,.202,.5,1},
		{.3536,.202,.3536,1},
		{.5,.202,0,1},
		{.3536,.202,-.3536,1},
		{0,.202,-.5,1},
		{-.3536,.202,-.3536,1},
		{-.5,.202,0,1},
		{-.3536,.202,.3536,1},

		//end of transparent area
		{0,.202,.25,2},
		{.1768,.202,.1768,2},
		{.25,.202,0,2},
		{.1768,.202,-.1768,2},
		{0,.202,-.25,2},
		{-.1768,.202,-.1768,2},
		{-.25,.202,0,2},
		{-.1768,.202,.1768,2}
	};

	struct SStripPoly
	{
		SLong v[3];
	}
	SolidPolys[]=
	{
//solid section polys
		{0,1,15},
		{15,1,8},
		{9,8,1},
		{2,9,1},
		{3,9,2},
		{3,10,9},
		{11,10,3},
		{4,11,3},
		{5,11,4},
		{12,11,5},
		{13,12,5},
		{6,13,5},
		{7,13,6},
		{14,13,7},
		{15,14,7},
		{0,15,7}
	},
	TransPolys[]=
	{
//transparent section polys
		{17,16,8},
		{9,17,8},
		{10,17,9},
		{18,17,10},
		{19,18,10},
		{11,19,10},
		{12,19,11},
		{20,19,12},
		{21,20,12},
		{13,21,12},
		{14,21,13},
		{22,21,14},
		{23,22,14},
		{15,23,14},
		{8,23,15},
		{16,23,8}
	};
		
	const SLong _stripPoints=sizeof(HStripPtsA)/sizeof(fpCOORDS3D);
	const SLong _solidPolys=sizeof(SolidPolys)/sizeof(SStripPoly);
	const SLong _transPolys=sizeof(TransPolys)/sizeof(SStripPoly);

	Float fvr=Float(view_range);
	Float fvy=Float(viewer_y)/Float(CEILING_ALT);

	//texture coordinate transformation matrix

	Float iMat[4];
	Float fSinHdg,fCosHdg;

	fpSinCos(-viewer_hdg,fSinHdg,fCosHdg);
	iMat[0]=iMat[3]=fCosHdg;
	iMat[1]=fSinHdg;
	iMat[2]=-fSinHdg;
		
	FPMATRIX 	mat,scale;
	Float 		*m=(Float*)&mat,
				*s=(Float*)&scale;

	_matrix.Generate(ANGLES_0Deg,View_Point->pitch,View_Point->roll,&mat);

	s[0]=fvr;
	s[1]=0;
	s[2]=0;

	s[3]=0;
	s[4]=Float(CEILING_ALT);
	s[5]=0;

	s[6]=0;
	s[7]=0;
	s[8]=fvr;

	_matrix.multiply(&scale,&mat);

	DoPointStruc* pdp=SHAPE.newco;
	SHCoords* psp=HStripPtsA;
	SWord ss=1024;

	Float ix=(viewer_x>>10)&SLong(ss-1),
			iy=(viewer_z>>10)&SLong(ss-1);

	for (SLong i=_stripPoints;i--;)
	{
		Float tu,tv,ttu,ttv;
		tu=(psp->X*ss);	//1 cloud texel per 81.92m
		tv=(psp->Z*ss);

		//2D rotate on texture coordinates
		ttu=tu*iMat[0]+tv*iMat[1];
		ttv=tu*iMat[2]+tv*iMat[3];

		Float py=psp->Y-fvy;
		pdp->bodyx.f=s[0]*psp->X+s[1]*py+s[2]*psp->Z;
		pdp->bodyy.f=s[3]*psp->X+s[4]*py+s[5]*psp->Z;
		pdp->bodyz.f=s[6]*psp->X+s[7]*py+s[8]*psp->Z;
		pdp->ix=SWord(ttu+ix);
		pdp->iy=SWord(ttv+iy);
		pdp->specular=-1;
		_matrix.SetClipFlags(*pdp);
		pdp->clipFlags&=~CF3D_PASTFARZ;
		pdp++;
		psp++;
	}

	psp=HStripPtsB;
	DoPointStruc* other_newco=pdp;
	for (i=_stripPoints;i--;)
	{
		Float tu,tv,ttu,ttv;
		tu=(psp->X*ss);	//1 cloud texel per 81.92m
		tv=(psp->Z*ss);

		//2D rotate on texture coordinates
		ttu=tu*iMat[0]+tv*iMat[1];
		ttv=tu*iMat[2]+tv*iMat[3];

		Float py=psp->Y-fvy;
		pdp->bodyx.f=s[0]*psp->X+s[1]*py+s[2]*psp->Z;
		pdp->bodyy.f=s[3]*psp->X+s[4]*py+s[5]*psp->Z;
		pdp->bodyz.f=s[6]*psp->X+s[7]*py+s[8]*psp->Z;
		pdp->ix=SWord(ttu+ix);
		pdp->iy=SWord(ttv+iy);
		pdp->specular=-1;
		_matrix.SetClipFlags(*pdp);
		pdp->clipFlags&=~CF3D_PASTFARZ;
		pdp++;
		psp++;
	}

	skyFogBegin=SLong(SHAPE.newco[8].bodyz.f);	//DEAD groundFogBegin;
	skyFogEnd=SLong(SHAPE.newco[0].bodyz.f);
	UByte saveR,saveG,saveB;
	SLong dummy;

	currscreen->DoGetFog(saveR,saveG,saveB,dummy,dummy);

	UByte fR,fG,fB;
	bool polysFlipped=viewer_y>_cloudLayerHeight?false:true;
	fR=currentLighting.horizonAtClouds.red();
	fG=currentLighting.horizonAtClouds.green();
	fB=currentLighting.horizonAtClouds.blue();
	currscreen->DoGammaCorr(fR,fG,fB);
	GreyPalette(&fR,&fG,&fB);
	currscreen->DoSetFog(saveR,saveG,saveB,skyFogBegin,skyFogEnd);
	currscreen->DoSetFog(fR,fG,fB);

	//solid section of cloud layer

	ImageMapDesc* pcloudno=Image_Map.GetImageMapPtr(CLOUDNO);

	for (i=0;i<_solidPolys;i++)
	{
		UWord andedFlags=SHAPE.newco[SolidPolys[i].v[0]].clipFlags&
						SHAPE.newco[SolidPolys[i].v[1]].clipFlags&
						SHAPE.newco[SolidPolys[i].v[2]].clipFlags;

		if (andedFlags==0)
		{
			DoPointStruc *p0,*p1,*p2;
			SWord	i0=HStripPtsA[SolidPolys[i].v[0]].flag==0?0xFF:0x00,
					i1=HStripPtsA[SolidPolys[i].v[1]].flag==0?0xFF:0x00,
					i2=HStripPtsA[SolidPolys[i].v[2]].flag==0?0xFF:0x00;
			p0=SHAPE.newco+SolidPolys[i].v[0];
			p1=SHAPE.newco+SolidPolys[i].v[1];
			p2=SHAPE.newco+SolidPolys[i].v[2];
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else						POLYGON.createpoly(pcloudno,IMAPPED_C);
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			POLYGON.drawpoly();
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else						POLYGON.createpoly(pcloudno,IMAPPED_C);
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			POLYGON.drawpoly();

			//and the other side of the cloud layer...
			p0=other_newco+SolidPolys[i].v[0];
			p1=other_newco+SolidPolys[i].v[1];
			p2=other_newco+SolidPolys[i].v[2];
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else						POLYGON.createpoly(pcloudno,IMAPPED_C);
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			POLYGON.drawpoly();
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else						POLYGON.createpoly(pcloudno,IMAPPED_C);
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			POLYGON.drawpoly();
		}
	}
	//transparent section of cloud layer

	currscreen->DoSetTranspFade(true);

	for (i=0;i<_transPolys;i++)
	{
		UWord andedFlags=SHAPE.newco[TransPolys[i].v[0]].clipFlags&
						SHAPE.newco[TransPolys[i].v[1]].clipFlags&
						SHAPE.newco[TransPolys[i].v[2]].clipFlags;

		if (andedFlags==0)
		{
			DoPointStruc *p0,*p1,*p2;
			SWord	i0=HStripPtsA[TransPolys[i].v[0]].flag==1?0xFF:0x00,
					i1=HStripPtsA[TransPolys[i].v[1]].flag==1?0xFF:0x00,
					i2=HStripPtsA[TransPolys[i].v[2]].flag==1?0xFF:0x00;
			p0=SHAPE.newco+TransPolys[i].v[0];
			p1=SHAPE.newco+TransPolys[i].v[1];
			p2=SHAPE.newco+TransPolys[i].v[2];
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else
			{
				ImageMapDescPtr pmap=Image_Map.GetImageMapPtr(CLOUDNO);
				POLYGON.createpoly(pmap,IMAPPED_TF);
			}
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			if (polysFlipped)
			{
				POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
				POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			}
			else
			{
				POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
				POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			}
			POLYGON.drawpoly();
		}
	}
	currscreen->DoSetTranspFade(false);
	currscreen->DoSetFog(saveR,saveG,saveB,groundFogBegin,groundFogEnd);
	currscreen->DoSetFog(saveR,saveG,saveB);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void LandScape::GetMinMaxAlt(AirStrucPtr ac,SLong& min,SLong& max)
{
	if (Three_Dee.pTMake==NULL) min=max=256000;
	else
	{
		ANGLES ac_hdg=ac->hdg;
		ac_hdg+=ANGLES_45Deg;
		ac_hdg=(Angles)((int)ac_hdg&0xC000);

		SWord dir;

		if (ac_hdg==ANGLES_0Deg)		dir=0;
		else if (ac_hdg==ANGLES_90Deg)	dir=1;
		else if (ac_hdg==ANGLES_180Deg)	dir=2;
		else							dir=3;

		Three_Dee.pTMake->GetMinMaxAlt(ac->World.X,ac->World.Z,dir,min,max);

		min*=_altitudeScale;
		max*=_altitudeScale;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterpSLightRGB
//Author		Paul.   
//Date			Mon 18 Jan 1999
//------------------------------------------------------------------------------
void LandScape::InterpSLightRGB(	SLayerRGB& lowRgb,
									SLayerRGB& hiRgb,
									SLayerRGB& outRgb,
									ULong scale)
{
	ULong val;
	Float fs,omfs;
	fs=scale/65536.;
	omfs=1.-fs;
	val=ULong(Float(lowRgb.r)*fs+Float(hiRgb.r)*omfs);
	outRgb.r=(val>0xFFFF)?0xFFFF:val;
	val=ULong(Float(lowRgb.g)*fs+Float(hiRgb.g)*omfs);
	outRgb.g=(val>0xFFFF)?0xFFFF:val;
	val=ULong(Float(lowRgb.b)*fs+Float(hiRgb.b)*omfs);
	outRgb.b=(val>0xFFFF)?0xFFFF:val;
}

#define InterpLight(p1)\
InterpSLightRGB(pLowLight->##p1,pHighLight->##p1,\
currentLighting.##p1,scaleFactor);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RefreshLandscape
//Author		Paul.   
//Date			Tue 16 Feb 1999
//------------------------------------------------------------------------------
void LandScape::RefreshLandscape()
{
	if (pLastGrid) delete[]pLastGrid,pLastGrid=NULL;
	if (pHTextureGrid) delete[]pHTextureGrid,pHTextureGrid=NULL;
//	delete Three_Dee.pMigLand;
//	delete Three_Dee.pTMake;
//	Three_Dee.pMigLand=new CMigLand;
//	Three_Dee.pTMake=new TMake;
	Three_Dee.pMigLand->BigInit(View_Point);
	Three_Dee.pTMake->Reinit(View_Point->World.X,View_Point->World.Z,currscreen);
	if (!Save_Data.fSoftware)	currscreen->DoFreeTextures();
	else						Three_Dee.pTMake->DoFreeTextures();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLighting
//Author		Paul.   
//Date			Mon 18 Jan 1999
//------------------------------------------------------------------------------
Bool LandScape::SetLighting(SLong curTime)			//RJS 15Jun99
{
	//curTime=current time in centiseconds
	
	const SLong fadeTime=3600;	//in centiseconds

	SLightingRGB *pLowLight,
				 *pHighLight;

	SLightingRGB preBadW;

	ULong scaleFactor;
	Bool	lightson = FALSE;									//RJS 15Jun99

	if (View_Point && View_Point->viewnum.viewmode==VM_Map)
	{
		currentLighting=*pMapL;
		return FALSE;											//RJS 15Jun99
	}

	if (curTime<MMC.dawntime-fadeTime)		//it's night time
	{
		pLowLight=
		pHighLight=pNite;
		scaleFactor=0;
		lightson = TRUE;										//RJS 15Jun99
	}
	else if (curTime<=MMC.dawntime)			//it's morning
	{
		//current lighting is a combination of night/dawn
		pLowLight=pNite;
		pHighLight=pDawn;
		scaleFactor=((MMC.dawntime-curTime)<<16)/fadeTime;
		lightson = TRUE;										//RJS 15Jun99
	}
	else if (curTime<MMC.dawntime+fadeTime)
	{
		//current lighting is a combination of dawn/day
		pLowLight=pDawn;
		pHighLight=pDay;
//		scaleFactor=65536-(((MMC.dawntime+fadeTime-curTime)<<16)/fadeTime);
		scaleFactor=(((MMC.dawntime+fadeTime-curTime)<<16)/fadeTime);
	}
	else if (curTime<MMC.dusktime-fadeTime)
	{
	 	pLowLight=
		pHighLight=pDay;
		scaleFactor=0;
	}
	else if (curTime<=MMC.dusktime)
	{
		//current lighting is a combination of day/dusk
		pLowLight=pDay;
		pHighLight=pDusk;
		scaleFactor=((MMC.dusktime-curTime)<<16)/fadeTime;
	}
	else if (curTime<=MMC.dusktime+fadeTime)
	{
		//current lighting is a combination of dusk/night
		pLowLight=pDusk;
		pHighLight=pNite;
//		scaleFactor=65536-(((MMC.dusktime+fadeTime-curTime)<<16)/fadeTime);
		scaleFactor=(((MMC.dusktime+fadeTime-curTime)<<16)/fadeTime);
		lightson = TRUE;										//RJS 15Jun99
	}
	else
	{
		pLowLight=
		pHighLight=pNite;
		scaleFactor=0;
		lightson = TRUE;										//RJS 15Jun99
	}

	if (scaleFactor==0)
		currentLighting=*pLowLight;
	else
	{
		InterpLight(horizonBase);
		InterpLight(horizonMid);
		InterpLight(horizonUnderClouds);
		InterpLight(horizonAtClouds);
		InterpLight(horizonAboveClouds);
		InterpLight(horizonTop);
		InterpLight(landAmbientCol);
		InterpLight(shadedAmbientCol);
		InterpLight(staticAmbientCol);
		InterpLight(cockpitAmbientCol);
		InterpLight(effectsAmbientCol);
	}

	//account for bad weather here...

	if (Save_Data.gamedifficulty[GD_WEATHEREFFECTS] && MMC.Sky.Conditions==1)
  	{
		preBadW=currentLighting;
		pLowLight=&preBadW;
		pHighLight=pBadW;
		scaleFactor=32768;	//how bad 0==very bad 65536=clear weather

		InterpLight(horizonBase);
		InterpLight(horizonMid);
		InterpLight(horizonUnderClouds);
		InterpLight(horizonAtClouds);
		InterpLight(horizonAboveClouds);
		InterpLight(horizonTop);
		InterpLight(landAmbientCol);
		InterpLight(shadedAmbientCol);
		InterpLight(staticAmbientCol);
		InterpLight(cockpitAmbientCol);
		InterpLight(effectsAmbientCol);
	}
	//currentLighting contains the lighting info 
	//for the correct time of day and weather type

	if (mono3d)
	{
		currentLighting.landAmbientCol.g=
			currentLighting.landAmbientCol.b=
			currentLighting.landAmbientCol.r;
		currentLighting.shadedAmbientCol.g=
			currentLighting.shadedAmbientCol.b=
			currentLighting.shadedAmbientCol.r;
		currentLighting.staticAmbientCol.g=
			currentLighting.staticAmbientCol.b=
			currentLighting.staticAmbientCol.r;
		currentLighting.cockpitAmbientCol.g=
			currentLighting.cockpitAmbientCol.b=
			currentLighting.cockpitAmbientCol.r;
		currentLighting.effectsAmbientCol.g=
			currentLighting.effectsAmbientCol.b=
			currentLighting.effectsAmbientCol.r;
	}
	return lightson;												//RJS 15Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetLights
//Author		Paul.   
//Date			Mon 1 Mar 1999
//------------------------------------------------------------------------------
void LandScape::ResetLights()
{
	for (SLong i=0;i<_MaxLights;lightList[i++].timer=0){}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddLight
//Author		Paul.   
//Date			Mon 1 Mar 1999
//------------------------------------------------------------------------------
void LandScape::AddLight(SLandLight* newlight)
{
	for (SLong i=0;i<_MaxLights;i++)
		if (lightList[i].timer==0)
			break;
	if (i<_MaxLights)
		lightList[i]=*newlight;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessLights
//Author		Paul.   
//Date			Mon 1 Mar 1999
//------------------------------------------------------------------------------
void LandScape::ProcessLights(SLong ox,SLong oz)
{
	SLong wholeAreaSize;

	SLong thisTime=currscreen->FrameTime();

	UByte actTbl[_MaxLights];

	UWord addTo=0;

	UByte *pGridCone,*pLightCone;

	lightsActive=0;

	for (SLong i=0;i<_MaxLights;i++)
	{
		if (lightList[i].timer!=0 &&
			(lightList[i].timer-=thisTime)>0)
			actTbl[lightsActive++]=UByte(i);
		else
			if (lightList[i].timer!=0) lightList[i].timer=0;
	}

	if (lightsActive==0) return;

	for (i=0;i<_wholeAreaSizeMAX;lightTable[i++].numLights=0){}

//	wholeAreaSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?_wholeAreaSizeMAX:_wholeAreaSizeMIN;
	wholeAreaSize=_wholeAreaSizeMIN;

	pGridCone=gridCone;
	pLightCone=lightCone;

	for (SLong row=0;row<wholeAreaSize;row++)
	{
		SLong ix=ox;

		for (SLong col=0;col<wholeAreaSize;col++)
		{
			if (*pGridCone)
			{
				//check this cell against active light list
				SLong cx0,cx1,cz0,cz1;
				SLong lx0,lx1,lz0,lz1;
				SLong lrange;
				bool anyAdded=false;
					
				for (SLong lights=0;lights<lightsActive;lights++)
				{
					SLong index=actTbl[lights];
					lrange=lightList[index].range;
					SLong dx=lightList[index].pos.X-ix-_halfBlockWidth;
					if (dx<0) dx=-dx;
					if (dx<_blockWidth)
					{
						SLong dz=lightList[index].pos.Z-oz-_halfBlockWidth;
						if (dz<0) dz=-dz;
						if (dz<_blockWidth)
						{
							bool lightIn=false;
							lx0=lx1=lightList[index].pos.X;
							lz0=lz1=lightList[index].pos.Z;
							lx0-=lrange;
							lz0-=lrange;
							lx1+=lrange;
							lz1+=lrange;
							cx0=ix;
							cx1=ix+_blockWidth;
							cz0=oz;
							cz1=oz+_blockWidth;
							if (lrange>_blockWidth)
							{
								//check to see if this tile lies inside the
								//area covered by the light
								if (cx0>=lx0 && cx0<=lx1 && cz0>=lz0 && cz0<=lz1) lightIn=true;
								if (!lightIn && cx1>=lx0 && cx1<=lx1 && cz0>=lz0 && cz0<=lz1) lightIn=true;
								if (!lightIn && cx1>=lx0 && cx1<=lx1 && cz1>=lz0 && cz1<=lz1) lightIn=true;
								if (!lightIn && cx0>=lx0 && cx0<=lx1 && cz1>=lz0 && cz1<=lz1) lightIn=true;
							}
							else
							{
								//check to see if this light lies inside the
								//area covered by the tile
								if (lx0>=cx0 && lx0<=cx1 && lz0>=cz0 && lz0<=cz1) lightIn=true;
								if (!lightIn && lx1>=cx0 && lx1<=cx1 && lz0>=cz0 && lz0<=cz1) lightIn=true;
								if (!lightIn && lx1>=cx0 && lx1<=cx1 && lz1>=cz0 && lz1<=cz1) lightIn=true;
								if (!lightIn && lx0>=cx0 && lx0<=cx1 && lz1>=cz0 && lz1<=cz1) lightIn=true;
							}
							if (lightIn)
							{
								//find a spare light table entry to use
								UWord thisOne=lightTable[addTo].numLights;
								lightTable[addTo].lightIndices[thisOne++]=index;
								lightTable[addTo].numLights=thisOne;
								anyAdded=true;
							}
						}
					}
				}
				if (anyAdded)
				{
					*pLightCone=UByte(addTo);
					addTo++;
					if (addTo==_wholeAreaSizeMAX)
						return;
				}
			}
			else *pLightCone=0xFF;

			pGridCone++;
			pLightCone++;
			ix+=_blockWidth;
		}
		oz+=_blockWidth;
	}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroundHuggingAltitude
//Author		Paul.   
//Date			Wed 3 Mar 1999
//------------------------------------------------------------------------------
SLong LandScape::GroundHuggingAltitude(MobileItem* itemPtr)
{
	if (itemPtr->World.Y>HIGHESTGROUND) return 0;

	SLong x=(itemPtr->World.X&~ULong(_blockWidth-1))+(_blockWidth>>1);
	SLong y=itemPtr->World.Y;
	SLong z=(itemPtr->World.Z&~ULong(_blockWidth-1))+(_blockWidth>>1);

	SLong maxAlt,thisAlt;

	//always test central tile
	maxAlt=_Collide.RoughGroundAltitude(x,y,z);

	if (y+FT_2000>maxAlt) return 0;

	UWord heading=itemPtr->hdg;

	if (heading<=UWord(ANGLES_45Deg) ||
		heading>UWord(-ANGLES_45Deg))
	{
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
	}
	else if (heading>UWord(ANGLES_45Deg) &&
			heading<=UWord(ANGLES_90Deg)+UWord(ANGLES_45Deg))
	{
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
	}
	else if (heading>UWord(ANGLES_90Deg)+UWord(ANGLES_45Deg) &&
			heading<=UWord(ANGLES_180Deg)-UWord(ANGLES_45Deg))
	{
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
	}
	else
	{
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
	}
	return maxAlt;
}
