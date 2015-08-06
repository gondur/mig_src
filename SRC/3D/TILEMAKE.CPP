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
//Filename       tilemake.cpp
//System         
//Author         Paul.   
//Date           Wed 15 Jul 1998
//Description    
//------------------------------------------------------------------------------

#define F_GRAFIX
#define F_SOUNDS
#define F_BATTLE

#include "dosdefs.h"
#include "fileman.h"
#include "files.g"
#include "ImageMap.h"
#include "ImageMap.g"
#include "MigLand.h"
#include "display.h"
#include "worldinc.h"
#include "3dcode.h"
#include "mymath.h"
#include "TileMake.h"
#include "gameset.h"
#include "world.h"
#include "shapes.h"
#include "shpinstr.h"
#include "savegame.h"
#include "areatype.h"
#include "overlay.h"
#include "shapenum.g"

TMake* tMake=NULL;													  //JIM 29/03/99
UByte* landPalette=NULL;

namespace TileMake
{

const SLong SOFT_256_TEXTURES=8;
const SLong SOFT_128_TEXTURES=16;
const SLong SOFT_64_TEXTURES=64;
const SLong SOFT_32_TEXTURES=64;
const SLong SOFT_16_TEXTURES=48;
const SLong SOFT_8_TEXTURES=64;
ROWANSURFACEDESC** sysram256maps=NULL;
ROWANSURFACEDESC** sysram128maps=NULL;
ROWANSURFACEDESC** sysram64maps=NULL;
ROWANSURFACEDESC** sysram32maps=NULL;
ROWANSURFACEDESC** sysram16maps=NULL;
ROWANSURFACEDESC** sysram8maps=NULL;
UByte landTextureUsage[256];

const SLong _wholeAreaSizeMAX=33;
const SLong _wholeAreaSizeMIN=17;
const SLong _cornerLengthMAX=_wholeAreaSizeMAX+1;
const SLong _cornerLengthMIN=_wholeAreaSizeMIN+1;
const SLong _areaBufferSizeMAX=_wholeAreaSizeMAX*_wholeAreaSizeMAX;
const SLong _areaBufferSizeMIN=_wholeAreaSizeMIN*_wholeAreaSizeMIN;
const SLong _cornerBufferSizeMAX=_cornerLengthMAX*_cornerLengthMAX;
const SLong _cornerBufferSizeMIN=_cornerLengthMIN*_cornerLengthMIN;

const SLong Grid_Width=131072;
const ULong Grid_Mask=~ULong(Grid_Width-1);

const SLong DataGridSizeMAX=33;
const SLong DataGridSizeMIN=17;

const SLong Max_TextureLevelsMAX=6;
const SLong Max_TextureLevelsMIN=5;

const SLong Max_Edges=256;
const SLong Indexable_Edges=Max_Edges;
const SLong Real_Max_Edges=Max_Edges+1024;

const SLong Max_Textures=32;
const SLong Max_Scales=4;

const FileNum BaseTexture=FIL_IMG10000;
const FileNum LoRezBase=FIL_IMG20000;

const SLong TextureWidth=256;
const SWord SpanMin=0;
const SWord SSpanMax=SWord(TextureWidth-1);
const SWord ESpanMax=SWord(TextureWidth);

const UByte cf_null=0;
const UByte cf_top=1;
const UByte cf_bot=2;
const UByte cf_lft=4;
const UByte cf_rgt=8;
const UByte cf_all=cf_top+cf_bot+cf_lft+cf_rgt;

const UWord _offleft=0x0001;
const UWord _offright=0x0002;
const UWord _offtop=0x0004;
const UWord _offbottom=0x0008;

static ShapeNum noShadowShapes[]=
{
TREES,
TREE1,
TREE2,
TREE3,
TREE4,
EMPTY2
};

static ShapeNum noShadowGroups[]=
{
FOREST1,
FOREST2,
WOOD1,
WOOD2,
WOOD3,
EMPTY
};

const SLong noShadowShapeEntries=sizeof(noShadowShapes)/sizeof(ShapeNum);
const SLong noShadowGroupEntries=sizeof(noShadowGroups)/sizeof(ShapeNum);

inline bool groupHasShadow(ShapeNum grp)
{
 	for (int i=noShadowGroupEntries-1;i>=0;i--)
		if (noShadowGroups[i]==grp)
			return false;
	return true;
}

inline bool shapeHasShadow(ShapeNum shp)
{
 	for (int i=noShadowShapeEntries-1;i>=0;i--)
		if (noShadowShapes[i]==shp)
			return false;
	return true;
}

template<class t> inline void Swap(t& a,t& b) 
							{a^=b;b^=a;a^=b;}
template<class t> inline t Min(const t a,const t b) 
							{return (a<b)?a:b;}
template<class t> inline t Max(const t a,const t b) 
							{return (a>b)?a:b;}
template<class t> inline t Abs(const t a) 
							{return (a>t(0))?a:-a;}
template<class t> inline t Clamp(const t a,const t min,const t max)
							{return (a<min)?min:(a>max)?max:a;}
template<class t> inline t Absolute(const t i,const t j,t& k)
							{return ((i-j)*(k=((i-j)<0?-1:1)));}

template<class t>
inline
void ClipResult(const t x,const t z,const Rect& r,UWord& flags,UWord& edges)
{
	if (x<r.l) 		flags=_offleft;
	else if (x>r.r) flags=_offright;
	else 			flags=0;

	if (z<r.t) 		flags+=_offtop;
	else if (z>r.b) flags+=_offbottom;

	if (x==r.l) 		edges=_offleft;
	else if (x==r.r)	edges=_offright;
	else				edges=0;
		
	if (z==r.t)			edges+=_offtop;
	else if (z==r.b)	edges+=_offbottom;
}

typedef struct EdgeTag
{
	SLong 	ymin,
			ymax;
	SLong 	xi,
			dxi;
}
Edge,*EdgePtr;

typedef struct EdgeTag2
{
	Edge	tri;
	Edge	texture;
}
Edge2,Edge2Ptr;
	
typedef struct VDataTag
{
	SWord v;
	SWord x;
	SWord y;
}
VData,*VDataPtr;

typedef struct VTriTag
{
	VData v1,v2,v3;
}
VTri,*VTriPtr;



typedef struct XDataTag : VData
{
	UByte cf;
}
XData,*XDataPtr;

typedef struct BoxTag
{
	SLong left,top,right,bottom;
}
Box,*BoxPtr;

UByte		edgeRecord[Max_Edges*Max_Edges];
UByte		clipRecord[Max_Edges];
Edge		EdgeList[Real_Max_Edges];
//DEAD fileblock*	fileData[Max_Textures];	//*Max_Scales];
//DEAD fileblock*	fileData2[Max_Textures];	//*Max_Scales];
UByte* 		imageData[Max_Textures]; //*Max_Scales];
ImageMapDesc* imagePtrs[Max_Textures];
//DEAD UByte* 		imageData2[Max_Textures]; //*Max_Scales];
UByte*		imagePalette;
PointDef* 	pointdef;
SWord 		tile_scale;
bool		ispalettised;
UWord*		palLookup;
SWord		byteScale;
//SWord		byteMask;
SWord		physWidth;
SWord		pixelSkip;
SLong*		land_x;
SLong*		land_z;
bool*		update_req;
SWord		detail_min;
UByte		tileRnd[256];

UWord		currentRouteColor16=0xFFFF;
UByte		currentRouteColor8=0xFF;

Box			targetBox;

SLong gridRecordBase_x;
SLong gridRecordBase_z;

struct ShadowStruc
{
	SLong world_x,world_z;
};

DataRecord*	gridRecords;
ShadowStruc* shadowRecords;
ShadowStruc currentShadowRec;

SLong clipRectCnt;
Rect*  clipRects;

UByte* gridClipper;

WorldStuff* worldPtr;
SLong numShadows;
ULong curSec;
UWord shadowSectors[9];
SLong shadowDX,shadowDZ;

static SLong	recordsUsed=Max_Edges;
static SLong	clipRecsUsed=Max_Edges;
static EdgePtr	curEdge=EdgeList;
static UByte*	pdsttxt=NULL;
static UByte*	psrctxt=NULL;
static SWord 	xoffset=0;
static SWord 	yoffset=0;
static SWord  uoffset=0;
static SWord  voffset=0;
static bool 	hardwareVersion=true;
static bool 	loadedTextures=false;
static Window*	win=NULL;
static bool		aliasingEdges=true;
inline UByte permb(const UByte x) {return tileRnd[x];}
inline SLong perm(const SLong x) {return tileRnd[x&0xFF];}
inline UByte index2d(const SLong x,const SLong y) {return UByte(perm(x+perm(y)));}
inline UByte index3d(const SLong x,const SLong y,const SLong z) {return UByte(perm(x+perm(y+perm(z))));}

void DDSymLine(ROWANSURFACEDESC*,SLong,SLong,SLong,SLong);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Swap<VData>
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
template<> inline void Swap<VData>(VData& a,VData& b)
{
	assert(3*sizeof(UWord)==sizeof(VData)&&"Swap<VData> struct size has altered");
 	*(ULong*)&a.v^=*(ULong*)&b.v;
 	*(ULong*)&b.v^=*(ULong*)&a.v;
 	*(ULong*)&a.v^=*(ULong*)&b.v;
 	*(UWord*)&a.y^=*(UWord*)&b.y;
 	*(UWord*)&b.y^=*(UWord*)&a.y;
 	*(UWord*)&a.y^=*(UWord*)&b.y;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Swap<Edge>
//Author		Paul.   
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
template<> inline void Swap<Edge>(Edge& a,Edge& b)
{
	Swap(a.ymin,b.ymin);
	Swap(a.ymax,b.ymax);
	Swap(a.xi,b.xi);
	Swap(a.dxi,b.dxi);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetClipFlags
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline UByte SetClipFlags(const SWord v)
{
	UByte r;
	if (0xFF!=clipRecord[v])
	{
		r=clipRecord[v];
	}
	else
	{
		SWord x,y;
		r=cf_null;
		x=xoffset+(pointdef[v].x>>tile_scale);
		y=yoffset+(256-pointdef[v].z>>tile_scale);
		if (x<targetBox.left) 			r+=cf_lft;
		else if (x>targetBox.right)		r+=cf_rgt;
		if (y<targetBox.top)			r+=cf_top;
		else if (y>targetBox.bottom) 	r+=cf_bot;
		clipRecord[v]=r;
	}
	return r;
}

typedef void (*plotpixelfn) (SLong,SLong);
typedef void (*ddpixelfn) (ROWANSURFACEDESC*,SLong,SLong);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawSpan8
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline void DrawSpan8(const SWord x1,const SWord x2,UByte* p,UByte* t)
{
	SWord x=Clamp(x1,SpanMin,SSpanMax);
	SWord xx=Clamp(x2,SpanMin,ESpanMax);
	t+=(uoffset+(x<<byteScale))&0xFF;
	UByte* bp=p+x+xoffset;
	for (;x<xx;*bp++=*t,t+=pixelSkip,x++) {}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DarkSpan8
//Author		Paul.   
//Date			Thu 22 Oct 1998
//------------------------------------------------------------------------------
inline void DarkSpan8(const SWord x1,const SWord x2,UByte* p)
{
	SWord x=Clamp(x1,SpanMin,SSpanMax);
	SWord xx=Clamp(x2,SpanMin,ESpanMax);
	UByte* bp=p+x;
	for (;x<xx;*bp++=0,x++) {}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawSpan16
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
inline void DrawSpan16(const SWord x1,const SWord x2,UWord* p,UByte* t)
{
	SWord x=Clamp(x1,SpanMin,SSpanMax);
	SWord xx=Clamp(x2,SpanMin,ESpanMax);
	t+=(uoffset+(x<<byteScale))&0xFF;
 	UWord* bp=p+x+xoffset;
	for (;x<xx;*bp++=palLookup[*t],t+=pixelSkip,x++) {}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DarkSpan16
//Author		Paul.   
//Date			Thu 22 Oct 1998
//------------------------------------------------------------------------------
inline void DarkSpan16(const SWord x1,const SWord x2,UWord* p)
{
	SWord x=Clamp(x1,SpanMin,SSpanMax);
	SWord xx=Clamp(x2,SpanMin,ESpanMax);
	UWord* bp=p+x;
	for (;x<xx;x++) *bp++=((*bp)>>2)&~UWord(0x0618);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EdgeScan
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline SLong EdgeScan(EdgePtr e)
{
 	const SLong x=e->xi>>16;
	e->xi+=e->dxi;
	return x;
}

inline EdgePtr EdgeSetup(const VData*,const VData*);
inline EdgePtr EdgeSetup2(const VData&,const VData&);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDestTexturePtr
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline void SetDestTexturePtr(const SWord index)
{
	if (hardwareVersion)
	{
		pdsttxt=(UByte*)win->DoGetLandBufferPtr(index);
	}
	else
		pdsttxt=NULL;	//fix software version if we want one
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPalLookup
//Author		Paul.   
//Date			Tue 21 Jul 1998
//------------------------------------------------------------------------------
inline void GetPalLookup()
{
	if (hardwareVersion && !ispalettised)
		palLookup=(UWord*)win->DoGetLandPalLookup();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPalLookup
//Author		PAul
//Date			Mon 16 Nov 1998
//------------------------------------------------------------------------------
inline void SetPalLookup()
{
 	if (hardwareVersion && imagePalette!=NULL)
		win->DoSetLandPalLookup(imagePalette);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateLandTBuffer
//Author		Paul.   
//Date			Sat 17 Apr 1999
//------------------------------------------------------------------------------
inline ROWANSURFACEDESC* CreateLandTBuffer(SLong size)
{
 	void* ptr=(void*)new UByte[sizeof(ROWANSURFACEDESC)+size*size];
	if (ptr)
	{
		ROWANSURFACEDESC* rsd=(ROWANSURFACEDESC*)ptr;
		rsd->dwWidth=rsd->dwHeight=size;
		rsd->lPitch=size;
		rsd->dwRGBBitCount=8;
		rsd->lpSurface=(void*)(ULong(ptr)+sizeof(ROWANSURFACEDESC));
	}
	return (ROWANSURFACEDESC*)ptr;
}

void DoGetTextureScales(SLong& num256,SLong& num128,SLong& num64,SLong& num32,SLong& num16,SLong& num8)
{
	num256=SOFT_256_TEXTURES;
	num128=SOFT_128_TEXTURES;
	num64=SOFT_64_TEXTURES;
	num32=SOFT_32_TEXTURES;
	num16=SOFT_16_TEXTURES;
	num8=SOFT_8_TEXTURES;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoFreeLandTextureBuffers
//Author		Paul.   
//Date			Sat 17 Apr 1999
//------------------------------------------------------------------------------
void DoFreeLandTextureBuffers()
{
	const SLong NUM_256_TEXTURES=SOFT_256_TEXTURES;
	const SLong	NUM_128_TEXTURES=SOFT_128_TEXTURES;
	const SLong	NUM_64_TEXTURES=SOFT_64_TEXTURES;
	const SLong	NUM_32_TEXTURES=SOFT_32_TEXTURES;
	const SLong NUM_16_TEXTURES=SOFT_16_TEXTURES;
	const SLong NUM_8_TEXTURES=SOFT_8_TEXTURES;

	if (sysram256maps)
	{
		for (int i=NUM_256_TEXTURES-1;i>=0;i--)	delete[](UByte*)sysram256maps[i];
		delete[]sysram256maps,sysram256maps=NULL;
	}
	if (sysram128maps)
	{
		for (int i=NUM_128_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram128maps[i];
		delete[]sysram128maps,sysram128maps=NULL;
	}
	if (sysram64maps)
	{
		for (int i=NUM_64_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram64maps[i];
		delete[]sysram64maps,sysram64maps=NULL;
	}
	if (sysram32maps)
	{
		for (int i=NUM_32_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram32maps[i];
		delete[]sysram32maps,sysram32maps=NULL;
	}
	if (sysram16maps)
	{
		for (int i=NUM_16_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram16maps[i];
		delete[]sysram16maps,sysram16maps=NULL;
	}
	if (sysram8maps)
	{
		for (int i=NUM_8_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram8maps[i];
		delete[]sysram8maps,sysram8maps=NULL;
	}
}

void DoFreeTexture(const HTEXT& hText)
{
	if (hText!=HTEXTNULL) landTextureUsage[hText()]=0x00;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoFreeTextures
//Author		Paul.   
//Date			Sat 17 Apr 1999
//------------------------------------------------------------------------------
void DoFreeTextures()
{
	for (int i=255;i>=0;i--) landTextureUsage[i]=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoAllocateTexture
//Author		Paul.   
//Date			Sat 17 Apr 1999
//------------------------------------------------------------------------------
HTEXT DoAllocateTexture(UByte textRez)
{
	const SLong NUM_256_TEXTURES=SOFT_256_TEXTURES;
	const SLong	NUM_128_TEXTURES=SOFT_128_TEXTURES;
	const SLong	NUM_64_TEXTURES=SOFT_64_TEXTURES;
	const SLong	NUM_32_TEXTURES=SOFT_32_TEXTURES;
	const SLong NUM_16_TEXTURES=SOFT_16_TEXTURES;
	const SLong NUM_8_TEXTURES=SOFT_8_TEXTURES;

	UByte *pmin,*pmax;
	switch (textRez)
	{
	case 0:
	pmin=landTextureUsage;
	pmax=landTextureUsage+NUM_256_TEXTURES;
	break;
	case 1:
	pmin=landTextureUsage+NUM_256_TEXTURES;
	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES;
	break;
	case 2:
	pmin=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES;
	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES;
	break;
	case 3:
	pmin=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES;
	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES;
	break;
	case 4:
	pmin=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES;
	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES;
	break;
	case 5:
	pmin=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES;
	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES+NUM_8_TEXTURES;
	break;
	default:
	assert(false&&"Bad texture resolution requestsed");
	break;
	}
	while (ULong(pmin)!=ULong(pmax))
	{
		if (*pmin==0x00)
		{
			HTEXT retVal=HTEXT((ULong(pmin)-ULong(landTextureUsage)));
			*pmin=0xFF;
			return retVal;
		}
		pmin++;
	}
	return HTEXTNULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCreateLandTBuffers
//Author		Paul.   
//Date			Sat 17 Apr 1999
//------------------------------------------------------------------------------
void DoCreateLandTBuffers()
{
	const SLong NUM_256_TEXTURES=SOFT_256_TEXTURES;
	const SLong	NUM_128_TEXTURES=SOFT_128_TEXTURES;
	const SLong	NUM_64_TEXTURES=SOFT_64_TEXTURES;
	const SLong	NUM_32_TEXTURES=SOFT_32_TEXTURES;
	const SLong NUM_16_TEXTURES=SOFT_16_TEXTURES;
	const SLong NUM_8_TEXTURES=SOFT_8_TEXTURES;

	typedef ROWANSURFACEDESC* LPROWANSURFACEDESC;

	sysram256maps=new LPROWANSURFACEDESC[NUM_256_TEXTURES];
	sysram128maps=new LPROWANSURFACEDESC[NUM_128_TEXTURES];
	sysram64maps=new LPROWANSURFACEDESC[NUM_64_TEXTURES];
	sysram32maps=new LPROWANSURFACEDESC[NUM_32_TEXTURES];
	sysram16maps=new LPROWANSURFACEDESC[NUM_16_TEXTURES];
	sysram8maps=new LPROWANSURFACEDESC[NUM_8_TEXTURES];

	if (!sysram256maps ||
		!sysram128maps ||
		!sysram64maps ||
		!sysram32maps ||
		!sysram16maps ||
		!sysram8maps)
		_Error.EmitSysErr("Failed to create software landscape textures");
	for (int i=NUM_256_TEXTURES-1;i>=0;i--)	sysram256maps[i]=CreateLandTBuffer(256);
	for (i=NUM_128_TEXTURES-1;i>=0;i--)		sysram128maps[i]=CreateLandTBuffer(128);
	for (i=NUM_64_TEXTURES-1;i>=0;i--)		sysram64maps[i]=CreateLandTBuffer(64);
	for (i=NUM_32_TEXTURES-1;i>=0;i--)		sysram32maps[i]=CreateLandTBuffer(32);
	for (i=NUM_16_TEXTURES-1;i>=0;i--)		sysram16maps[i]=CreateLandTBuffer(16);
	for (i=NUM_8_TEXTURES-1;i>=0;i--)		sysram8maps[i]=CreateLandTBuffer(8);
	DoFreeTextures();
}
inline void ClearTexturePointers();
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTexturePointers
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
void SetTexturePointers(const bool hardVer=true)
{
	SWord fileNumOffset;
	SWord i,j;
	FileNum fn;
	fileblockptr fbp;

	if (loadedTextures) ClearTexturePointers();		

	hardwareVersion=hardVer;
	loadedTextures=true;

	fileNumOffset=SWord(FIL_IMG10000H-FIL_IMG10000);

	imagePalette=NULL;

	for (j=0;j<Max_Textures;j++)
	{
		fn=FileNum(j+BaseTexture+fileNumOffset);
		fileblock fb(fn);
		imagePtrs[j]=new ImageMapDesc;
		imagePtrs[j]->FixLbmImageMap(&fb);
		imageData[j]=imagePtrs[j]->body;
		if (j==0 && ULong(imagePtrs[0]->palette)>256)
		{
			imagePalette=imagePtrs[0]->palette;
			imagePalette[255*3+1]=0xFF;
			imagePalette[255*3+2]=
				imagePalette[255*3]=0;
			landPalette=new UByte[3*256];
			for (int k=(3*256)-1;k>=0;k--)
				landPalette[k]=imagePalette[k];
		}
	}
	if (hardwareVersion)
	{
		ispalettised=win->DoGetLandBpp()==8?true:false;
		SetPalLookup();
		GetPalLookup();
	 	win->DoCreateLandTBuffers();
	}
	else
	{
		ispalettised=true;
		palLookup=NULL;
		DoCreateLandTBuffers();
		//make the landscape palette lookup table here
		UWord* plup=(UWord*)win->GetPaletteTable();
		UByte* palp=imagePalette;
		plup-=256;

		UWord redMask,greenMask,blueMask;
		SWord redShift1,greenShift1,blueShift1;
		SWord redShift2,greenShift2,blueShift2;
		win->DoGetColourInfo(redMask,redShift1,redShift2,greenMask,greenShift1,greenShift2,blueMask,blueShift1,blueShift2);
		for (j=255;j>=0;j--)
		{
			UWord red,green,blue;
			blue=UWord(*palp++)&0xFF;
			red=UWord(*palp++)&0xFF;
			green=UWord(*palp++)&0xFF;
			red=((red>>redShift2)&redMask);
			green=((green>>greenShift2)&greenMask);
			blue=((blue>>blueShift2)&blueMask);
			*plup++=(red<<redShift1)+(green<<greenShift1)+(blue<<blueShift1);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearTexturePointers
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
inline void ClearTexturePointers()
{
	SWord i;

	if (loadedTextures)
	{
		for (i=0;i<Max_Textures;i++) delete imagePtrs[i],imagePtrs[i]=NULL;
		loadedTextures=false;
	}
	if (Save_Data.fSoftware) DoFreeLandTextureBuffers();
	delete[]landPalette;
	landPalette=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetMem
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline void ResetMem(void* pp,ULong ll)
{
	_asm{
	xor	eax,eax;
	dec	eax;
	mov edi,pp;
	mov ebx,ll;
	mov	ecx,4;
	sub	ecx,edi;
	and	ecx,3;
	sub	ebx,ecx;
	rep	stosb;
	mov	ecx,ebx;
	shr	ecx,2;
	rep	stosd;
	and	ebx,3;
	mov	ecx,ebx;
	rep	stosb;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearRecords
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline void ClearRecords(const UByte count)
{
	ULong dlen=recordsUsed*recordsUsed;
	void* dstart=(void*)edgeRecord;
	ResetMem(dstart,dlen);
	if (0!=clipRecsUsed)
	{
		dlen=clipRecsUsed;
		dstart=(void*)clipRecord;
		ResetMem(dstart,dlen);
		clipRecsUsed=0;
	}
	recordsUsed=count;
	curEdge=EdgeList;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeRecIndex
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
template<class t> inline t MakeRecIndex(const t a,const t b)
{
	return (a>=b)?b*recordsUsed+a:a*recordsUsed+b;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EdgeSetup
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline EdgePtr EdgeSetup(const VData* va,const VData* vb)
{
	const ULong _indexableLimit=ULong(EdgeList+Indexable_Edges);
	const ULong _realEdgeLimit=ULong(EdgeList+Real_Max_Edges);

	//check whether we have already created the data for this edge

	SWord ri=MakeRecIndex(va->v,vb->v);

	EdgePtr e=curEdge++;

	if (ULong(e)<_indexableLimit &&	0xFF!=edgeRecord[ri])
		return EdgeList+edgeRecord[ri];

	ULong ei=e-EdgeList;
	edgeRecord[ri]=ei;

	assert(ULong(e)<_realEdgeLimit&&"Edge record o'flow");

	SLong sf,dx=vb->x-va->x,dy=vb->y-va->y;

	e->ymin=va->y;
	e->ymax=vb->y;

	if (dy)
	{
		e->xi=va->x<<16;
		e->dxi=(dx<<16)/dy;
	}
	return e;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EdgeSetup
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
inline EdgePtr EdgeSetup(const VData* va,const VData* vb,SWord scale)
{
	const ULong _indexableLimit=ULong(EdgeList+Indexable_Edges);
	const ULong _realEdgeLimit=ULong(EdgeList+Real_Max_Edges);

	//check whether we have already created the data for this edge

	SWord ri=MakeRecIndex(va->v,vb->v);

	EdgePtr e=curEdge++;

	if (ULong(e)<_indexableLimit &&	0xFF!=edgeRecord[ri])
		return EdgeList+edgeRecord[ri];

	ULong ei=e-EdgeList;
	edgeRecord[ri]=ei;

	assert(ULong(e)<_realEdgeLimit&&"Edge record o'flow");

	SLong sf,dx=vb->x-va->x,dy=vb->y-va->y;

	e->ymin=va->y;
	e->ymax=vb->y;

	if (dy)
	{
		e->xi=va->x<<16;
		e->dxi=(dx<<(16+scale))/dy;
	}
	return e;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EdgeSetup2
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
inline EdgePtr EdgeSetup2(const VData& va,const VData& vb)
{
	const ULong _realEdgeLimit=ULong(EdgeList+Real_Max_Edges);

	EdgePtr e=curEdge++;

	assert(ULong(e)<_realEdgeLimit&&"Edge record o'flow");

	SLong sf,dx=vb.x-va.x,dy=vb.y-va.y;

	e->ymin=va.y;
	e->ymax=vb.y;

	if (dy)
	{
		e->xi=va.x<<16;
		e->dxi=(dx<<16)/dy;
	}
	return e;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScaledTextureWidth
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline void ScaledTextureWidth(const SWord scale)
{
	if (scale<3) 
	{
		physWidth=256>>scale;
		pixelSkip=1<<scale;
		byteScale=scale;
	}
	else 
	{
		physWidth=256>>scale;
		pixelSkip=1<<(scale-3);
		byteScale=scale-3;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BoxClipTest
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline SWord BoxClipTest(const SWord x,const SWord y)
{
	//return 0 if the box is completely off the target area

	if (x+physWidth<0 || y+physWidth<0 ||
		x>TextureWidth || y>TextureWidth)
		return SWord(0);

	//return 1 if the box is completely contained within
	//the target area

	if (x>=0 && x+physWidth<=TextureWidth &&
		y>=0 && y+physWidth<=TextureWidth)
		return SWord(1);

	//return -1 if some overlap is detected

	return SWord(-1);
}

void SortedTriangle8(VData*);
void SortedTriangle16(VData*);

void SortedTriangle28(VData,VData,VData);
void SortedTriangle216(VData,VData,VData);

void ShadowTriangle8(VData,VData,VData);
void ShadowTriangle16(VData,VData,VData);

void DDShadowTriangle8(ROWANSURFACEDESC*,VData,VData,VData,SWord);
void DDShadowTriangle16(ROWANSURFACEDESC*,VData,VData,VData,SWord);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Triangle
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
void Triangle(SWord v1,SWord v2,SWord v3)
{
	VData v[3];

	v[0].x=pointdef[v1].x>>tile_scale;
	v[0].y=(256-pointdef[v1].z)>>tile_scale;
	v[0].v=v1;

	v[1].x=pointdef[v2].x>>tile_scale;
	v[1].y=(256-pointdef[v2].z)>>tile_scale;
	v[1].v=v2;

	v[2].x=pointdef[v3].x>>tile_scale;
	v[2].y=(256-pointdef[v3].z)>>tile_scale;
	v[2].v=v3;

	if (v[0].y>v[1].y) Swap(v[0],v[1]);
	if (v[0].y>v[2].y) Swap(v[0],v[2]);
	if (v[1].y>v[2].y) Swap(v[1],v[2]);

	if (ispalettised)	SortedTriangle8(v);
	else				SortedTriangle16(v);
}

typedef void (*clipfn) (const XData*,const XData*,XData*);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToTop
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline void ClipToTop(const XData* vin,const XData* vout,XData* vclip)
{
	SLong dx=vout->x-vin->x;
	SLong dy=vout->y-vin->y;
	SLong ndy=targetBox.top-vin->y;

	if (dy==0)
		*vclip=*vin;
	else
	{
		vclip->y=targetBox.top;
		vclip->x=vin->x+((dx)?dx*ndy/dy:dx);
	}

	//fill in clip codes for the clipped point

	if (vclip->x<targetBox.left)			vclip->cf=cf_lft;
	else if (vclip->x>targetBox.right)		vclip->cf=cf_rgt;
	else									vclip->cf=cf_null;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToBot
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline void ClipToBot(const XData* vin,const XData* vout,XData* vclip)
{
	SLong dx=vout->x-vin->x;
	SLong dy=vout->y-vin->y;
	SLong ndy=targetBox.bottom-vin->y;

	if (dy==0)
		*vclip=*vin;
	else
	{
		vclip->y=targetBox.bottom;
		vclip->x=vin->x+((dx)?dx*ndy/dy:dx);
	}

	//fill in clip codes for the clipped point

	if (vclip->x<targetBox.left)			vclip->cf=cf_lft;
	else if (vclip->x>targetBox.right)		vclip->cf=cf_rgt;
	else									vclip->cf=cf_null;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToLft
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline void ClipToLft(const XData* vin,const XData* vout,XData* vclip)
{
	SLong dy=vout->y-vin->y;
	SLong dx=vout->x-vin->x;
	SLong ndx=targetBox.left-vin->x;

	if (dx==0)
		*vclip=*vin;
	else
	{
		vclip->x=targetBox.left;
		vclip->y=vin->y+((dy)?dy*ndx/dx:dy);
	}
	vclip->cf=cf_null;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToRgt
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
inline void ClipToRgt(const XData* vin,const XData* vout,XData* vclip)
{
	SLong dy=vout->y-vin->y;
	SLong dx=vout->x-vin->x;
	SLong ndx=targetBox.right-vin->x;

	if (dx==0)
		*vclip=*vin;
	else
	{
		vclip->x=targetBox.right;
		vclip->y=vin->y+((dy)?dy*ndx/dx:dy);
	}
	vclip->cf=cf_null;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Clip
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
inline void Clip(	const 		clipfn crtn,
					const 		UByte f,
					XDataPtr* 	spoly,
					SWord 		si,
					SWord 		ni,
					XDataPtr*	dpoly,
					SWord& 		di,
					XData*&		allocv)
{
	if (0==(spoly[si]->cf&f)){

		dpoly[di++]=spoly[si];

		if (0!=(spoly[ni]->cf&f)){

		 	(*crtn)(spoly[si],spoly[ni],allocv);

			dpoly[di++]=allocv++;
		}
	}
	else if (0==(spoly[ni]->cf&f)){

		(*crtn)(spoly[ni],spoly[si],allocv);

		dpoly[di++]=allocv++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoClip
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
SWord DoClip(const SWord v1,const SWord v2,const SWord v3,XDataPtr*& np)
{
	static XData vc[16];
	static XDataPtr polydef[16];

	XDataPtr newv=vc+3;
	XDataPtr newdef[16];

	SWord pntcnt,limit;
	SWord newpc;

	np=polydef;

	vc[0].x=xoffset+(pointdef[v1].x>>tile_scale);
	vc[0].y=yoffset+(256-pointdef[v1].z>>tile_scale);
	vc[0].cf=clipRecord[v1];

	vc[1].x=xoffset+(pointdef[v2].x>>tile_scale);
	vc[1].y=yoffset+(256-pointdef[v2].z>>tile_scale);
	vc[1].cf=clipRecord[v2];

	vc[2].x=xoffset+(pointdef[v3].x>>tile_scale);
	vc[2].y=yoffset+(256-pointdef[v3].z>>tile_scale);
	vc[2].cf=clipRecord[v3];

	polydef[0]=vc;
	polydef[1]=vc+1;
	polydef[2]=vc+2;

	pntcnt=3;
	limit=pntcnt-1;
	newpc=0;

	//clip against the top of the target area

	for (SWord i=0,j=1;i<limit;i++,j++)
		Clip(ClipToTop,cf_top,polydef,i,j,newdef,newpc,newv);
	Clip(ClipToTop,cf_top,polydef,i,0,newdef,newpc,newv);

	if (3>(pntcnt=newpc)) return pntcnt;

	limit=pntcnt-1;
	newpc=0;

	//clip against the base of the target area

	for (i=0,j=1;i<limit;i++,j++)
	 	Clip(ClipToBot,cf_bot,newdef,i,j,polydef,newpc,newv);
 	Clip(ClipToBot,cf_bot,newdef,i,0,polydef,newpc,newv);

	if (3>(pntcnt=newpc)) return pntcnt;

	limit=pntcnt-1;
	newpc=0;

	//clip against the left of the target area

	for (i=0,j=1;i<limit;i++,j++)
	 	Clip(ClipToLft,cf_lft,polydef,i,j,newdef,newpc,newv);
 	Clip(ClipToLft,cf_lft,polydef,i,0,newdef,newpc,newv);

	if (3>(pntcnt=newpc)) return pntcnt;

	limit=pntcnt-1;
	newpc=0;

	//clip against the right of the target area

	for (i=0,j=1;i<limit;i++,j++)
	 	Clip(ClipToRgt,cf_rgt,newdef,i,j,polydef,newpc,newv);
 	Clip(ClipToRgt,cf_rgt,newdef,i,0,polydef,newpc,newv);

	return newpc;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Triangle2
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
void Triangle2(VData v1,VData v2,VData v3)
{
	if (v1.y>v2.y) Swap(v1,v2);
	if (v1.y>v3.y) Swap(v1,v3);
	if (v2.y>v3.y) Swap(v2,v3);

	if (ispalettised)	SortedTriangle28(v1,v2,v3);
	else				SortedTriangle216(v1,v2,v3);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClippedTriangle
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
void ClippedTriangle(SWord v1,SWord v2,SWord v3)
{
	XDataPtr* cpp;
	XDataPtr cp;
	VData poly[3];

	SWord pntCnt;

	pntCnt=DoClip(v1,v2,v3,cpp);

	if (pntCnt>=3)
	{
		cp=*cpp++;
		poly[0].x=cp->x-xoffset;
		poly[0].y=cp->y-yoffset;
		cp=*cpp++;
		poly[2].x=cp->x-xoffset;
		poly[2].y=cp->y-yoffset;
		cp=*cpp++;
		pntCnt-=2;

		while (pntCnt--)
		{
		 	poly[1]=poly[2];
			poly[2].x=cp->x-xoffset;
			poly[2].y=cp->y-yoffset;
			cp=*cpp++;
			Triangle2(poly[0],poly[1],poly[2]);
		}
	}
}

void PolyOutline(UByte*);
void DoLine(const SWord,const SWord);
void DoLClip(const SWord,const SWord);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Render2Map
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
void Render2Map(UByte* p,const SWord xo,const SWord yo,const SWord scale)
{
	AltPointsHdr* a;
	DrawDataHdr* d;
	UByte** pt;
	SWord clipFlag;
	SWord primCount;
	UByte lineCol;
	UByte sectionCount;

	tile_scale=scale;

	SetDestTexturePtr(tile_scale);

	a=(AltPointsHdr*)p;
	p+=sizeof(AltPointsHdr);

	//clear records of generated edges
	ClearRecords(a->vertexCount);

	pointdef=(PointDef*)p;
	p+=sizeof(PointDef)*a->vertexCount;

	d=(DrawDataHdr*)p;
	p+=sizeof(DrawDataHdr);

	ScaledTextureWidth(scale);

	//Initialise pointer to texture data
	pt=/*(scale<3)?*/imageData;		//DEAD :imageData2;

	xoffset=xo;
	yoffset=yo;

	clipFlag=BoxClipTest(xo,yo);

	if (!clipFlag) return;

	if (1==clipFlag)
	{
		//no clipping is needed
		primCount=d->noOfPolys;

		while (primCount--)
		{
			//get pointer to source texture
			psrctxt=pt[(*p&0x1F)];
			p++;
			UByte triCount=*p++;
			while (triCount--)
			{
				UByte fanCount=*p++;
				SWord v1=*p++;
				SWord v3=*p++;
				while (fanCount--)
				{
					SWord v2=v3;
					v3=*p++;
					Triangle(v1,v2,v3);
				}
			}
		}

		//add roads, railways and rivers

		if (((Save_Data.detail_3d[DETAIL3D_ROUTES] && scale<4)||OverLay.fZoomedMap) && d->noOfLines!=0) 
		{
			primCount=d->noOfLines;

			while (primCount--) 
			{
				lineCol=*p++;

				//check line color against route types

				switch (lineCol)
				{
					case RT_river:
						lineCol=196;
						break;
					case RT_track:
						lineCol=181;
						break;
					case RT_rail:
						lineCol=OverLay.fZoomedMap?255:1;
						break;
					case RT_road:
						lineCol=181;
						break;
					case RT_magic:
						lineCol=111;
						break;
					default:
						lineCol=0;
						break;
				}

				if (lineCol)
				{
					if (ispalettised)	currentRouteColor8=lineCol;
				 	else	currentRouteColor16=palLookup[lineCol];
				}

				sectionCount=*p++;
				SWord v2=*p++;

				while (--sectionCount!=0) 
				{
					SWord v1=v2;
					v2=*p++;
					if (lineCol) DoLine(v1,v2);
				}
			}
		}
	}
	else
	{
		//some clipping is needed

		clipRecsUsed=a->vertexCount;

		primCount=d->noOfPolys;

		while (primCount--)
		{
			//get pointer to source texture
			psrctxt=pt[(*p&0x1F)];
			p++;

			UByte triCount=*p++;
			while (triCount--)
			{
				UByte fanCount=*p++;
				SWord v1=*p++;
				SWord v3=*p++;
				UByte c1,c3;

				c1=SetClipFlags(v1);
				c3=SetClipFlags(v3);
				while (fanCount--)
				{
					SWord v2=v3;
					UByte c2=c3;
					v3=*p++;
					c3=SetClipFlags(v3);

					if ((c1|c2|c3)==cf_null)
						Triangle(v1,v2,v3);
					else if ((c1&c2&c3)==cf_null)
					     	ClippedTriangle(v1,v2,v3);
				}
			}
		}

		//add roads, railways and rivers

		if ((scale<4 || OverLay.fZoomedMap) && d->noOfLines!=0) 
		{
			primCount=d->noOfLines;

			while (primCount--) 
			{
				lineCol=*p++;

				//check line color against route types

				switch (lineCol)
				{
					case RT_river:
						lineCol=196;
						break;
					case RT_track:
						lineCol=181;
						break;
					case RT_rail:
						lineCol=OverLay.fZoomedMap?255:1;
						break;
					case RT_road:
						lineCol=181;
						break;
					case RT_magic:
						lineCol=111;
						break;
					default:
						lineCol=0;
						break;
				}

				if (lineCol)
				{
					if (ispalettised)	currentRouteColor8=lineCol;
				 	else	currentRouteColor16=palLookup[lineCol];
				}

				sectionCount=*p++;
				SWord v2=*p++;
				UByte c2=SetClipFlags(v2);

				while (--sectionCount!=0) 
				{
					SWord v1=v2;
					v2=*p++;

					if (lineCol!=0)
					{
						UByte c1=c2;
						c2=SetClipFlags(v2);
						if ((c1|c2)==cf_null)	DoLine(v1,v2);
						else if ((c1&c2)==cf_null)	DoLClip(v1,v2);
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInitialLandTextureCoordinates
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void SetInitialLandTextureCoordinates(const SLong x,const SLong z)
{
	//set initial coordinates for landscape update tests
	//the inner level (0) will cover a 1.3km square area
	//and will be updated after every 80m of travel.
	//Subsequent squares will cover 4 times the area and
	//will require updates at half the rate of the previous
	//level.

	SLong	update_size,
			square_halfsize;
	ULong	update_mask;
	SLong	maxTextureLevels;

//	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//						Max_TextureLevelsMAX:Max_TextureLevelsMIN;
	maxTextureLevels=Max_TextureLevelsMIN;
	
	update_size=Grid_Width>>3;
	square_halfsize=Grid_Width>>1;

	for (int i=0;i<maxTextureLevels;i++)
	{
		update_mask=~ULong(update_size-1);

		land_x[i]=(x&update_mask)-square_halfsize;
		land_z[i]=(z&update_mask)-square_halfsize;

		//signal that all the blocks 
		//need to be regenerated

		update_req[i]=true;
		update_size+=update_size;
		square_halfsize+=square_halfsize;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckForLandUpdate
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
bool CheckForLandUpdate(const SLong x,const SLong z)
{
	//check each landscape detail level to 
	//see if any update is required

	bool retval=false;

	ULong	mask_value;
	SLong	update_size;
	SLong	square_halfsize;

	SLong 	level_basex,
			level_basez;

	SLong	maxTextureLevels;

///	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//						Max_TextureLevelsMAX:Max_TextureLevelsMIN;
	maxTextureLevels=Max_TextureLevelsMIN;

	update_size=Grid_Width>>3;
	square_halfsize=Grid_Width>>1;

	for (int i=0;i<maxTextureLevels;i++)
	{
		mask_value=~ULong(update_size-1);
		level_basex=(x&mask_value)-square_halfsize;
		level_basez=(z&mask_value)-square_halfsize;

		if (Abs(land_x[i]-level_basex)>=update_size ||
			Abs(land_z[i]-level_basez)>=update_size)
			update_req[i]=retval=true;

		update_size+=update_size;
		square_halfsize+=square_halfsize;
	}
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLandBaseDetail
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
inline void SetLandBaseDetail(const SWord dl)
{
//	assert(dl>=0&&dl<Max_TextureLevels&&"Bad landscape detail level");
	detail_min=dl;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScrollTexture
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
inline void ScrollTexture(const SLong lvl,const Box& src,const Box& dst)
{
	if (hardwareVersion)
	{
		//for cards that support async video-video blits I can get the
		//data shift started here and it should be complete by the time
		//the new data has been generated for the rest of the texture.

		win->DoBeginTextureScroll(lvl,(void*)&src,(void*)&dst);
	}
	else assert(false&&"code needed for software version here");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WaitForTextureScrollComplete
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
inline void WaitForTextureScrollComplete(const SLong lvl)
{
	//If using the hardware version then wait for any blits that
	//are still in progress to complete

	if (hardwareVersion)
		win->DoWaitTextureScrollComplete(lvl);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PartialTextureUpload
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
inline void PartialTextureUpload(const Box& src,const Box& dst,const SWord lvl)
{
	if (hardwareVersion)
		win->DoPartialTextureUpload(lvl,(void*)&src,(void*)&dst);
	else
		assert(false);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTargetClip
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
inline void SetTargetClip(const Box& b) {targetBox=b;}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeDataGridIndex
//Author		Paul.   
//Date			Mon 20 Jul 1998
//------------------------------------------------------------------------------
inline SLong MakeDataGridIndex(const SLong x,const SLong z)
{
//	SLong dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//						DataGridSizeMAX:DataGridSizeMIN;
	SLong dataGridSize=DataGridSizeMIN;
 	SLong xi=(x-gridRecordBase_x)/Grid_Width;
	if (xi<0 || xi>dataGridSize-1) return -1;
	SLong zi=(z-gridRecordBase_z)/Grid_Width;
	if (zi<0 || zi>dataGridSize-1) return -1;
	return (zi*dataGridSize)+xi;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeDataGridIndex
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
inline SLong MakeDataGridIndex(const UWord offset)
{
	return (SLong)offset;
}

void RenderShadow(ROWANSURFACEDESC*,ShapeDescPtr,SLong,SLong,SLong);
void RenderShadowRotated(ROWANSURFACEDESC*,ShapeDescPtr,SLong,SLong,SLong,SLong);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderRotatedShad
//Author		Paul.   
//Date			Tue 23 Feb 1999
//------------------------------------------------------------------------------
inline void RenderRotatedShad(ROWANSURFACEDESC* prsd,SLong* x,SLong* z,SLong lvl)
{
	VData vertex[8];

	for (SLong i=0;i<8;i++)
	{
		vertex[i].v=i;
		vertex[i].x=x[i]<0?0:x[i]>255?255:x[i];
		vertex[i].y=z[i]<0?0:z[i]>255?255:z[i];
	}

	if (ispalettised)
	{
		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);

		DDShadowTriangle8(prsd,vertex[4],vertex[5],vertex[6],lvl);
		DDShadowTriangle8(prsd,vertex[4],vertex[6],vertex[7],lvl);

		DDShadowTriangle8(prsd,vertex[0],vertex[4],vertex[3],lvl);
		DDShadowTriangle8(prsd,vertex[3],vertex[4],vertex[7],lvl);

		DDShadowTriangle8(prsd,vertex[1],vertex[5],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[2],vertex[5],vertex[6],lvl);

	}
	else
	{
		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);

		DDShadowTriangle16(prsd,vertex[4],vertex[5],vertex[6],lvl);
		DDShadowTriangle16(prsd,vertex[4],vertex[6],vertex[7],lvl);

		DDShadowTriangle16(prsd,vertex[0],vertex[4],vertex[3],lvl);
		DDShadowTriangle16(prsd,vertex[3],vertex[4],vertex[7],lvl);

		DDShadowTriangle16(prsd,vertex[1],vertex[5],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[2],vertex[5],vertex[6],lvl);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadOctant0
//Author		Paul.   
//Date			Mon 26 Oct 1998
//------------------------------------------------------------------------------
inline void RenderShadOctant0(ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
{
	//shadow is North facing 4 points & 2 polys required

	VData vertex[4];

	SLong shape2Pix=5;	//lvl+5;

	if ((sdp->Size>>shape2Pix)==0)
		return;

	SLong shapeSx=sdp->sx>>shape2Pix;
	SLong shapeSy=sdp->sy>>shape2Pix;
	SLong shapeSz=sdp->sz>>shape2Pix;

	if (shapeSy==0) return;	//shapeSy=1;
	if (shapeSx==0) return; //shapeSx=1;
	if (shapeSz==0) return; //shapeSz=1;

	//scale shadow DX,DZ based on the shapes height

	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;

	vertex[0].v=0;
	vertex[0].x=x+shapeSx;
	vertex[0].y=z+shapeSz;

	vertex[1].v=1;
	vertex[1].x=x-shapeSx;
	vertex[1].y=z+shapeSz;

	vertex[2].v=2;
	vertex[2].x=x-shapeSx;
	vertex[2].y=z+sdz-shapeSz;

	vertex[3].v=3;
	vertex[3].x=x+shapeSx;
	vertex[3].y=z+sdz-shapeSz;

	for (SLong i=0;i<4;i++)
	{
		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
	}

	if (ispalettised)
	{
		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
	}
	else
	{
		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadOctant1
//Author		Paul.   
//Date			Mon 26 Oct 1998
//------------------------------------------------------------------------------
inline void RenderShadOctant1(ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
{
	//shadow is NE facing 6 points & 4 polys required

	VData vertex[6];

	SLong shape2Pix=5;	//lvl+5;

	if ((sdp->Size>>shape2Pix)==0)
		return;

	SLong shapeSx=sdp->sx>>shape2Pix;
	SLong shapeSy=sdp->sy>>shape2Pix;
	SLong shapeSz=sdp->sz>>shape2Pix;

	if (shapeSy==0) return;	//shapeSy=1;
	if (shapeSx==0) return; //shapeSx=1;
	if (shapeSz==0) return; //shapeSz=1;

	//scale shadow DX,DZ based on the shapes height

	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;

	vertex[0].v=0;
	vertex[0].x=x+shapeSx;
	vertex[0].y=z-shapeSz;

	vertex[1].v=1;
	vertex[1].x=x-shapeSx;
	vertex[1].y=z-shapeSz;

	vertex[2].v=2;
	vertex[2].x=x-shapeSx;
	vertex[2].y=z+shapeSz;

	vertex[3].v=3;
	vertex[3].x=x-shapeSx+sdx;
	vertex[3].y=z+shapeSz-sdz;

	vertex[4].v=4;
	vertex[4].x=x+shapeSx+sdx;
	vertex[4].y=z+shapeSz-sdz;

	vertex[5].v=5;
	vertex[5].x=x+shapeSx+sdx;
	vertex[5].y=z-shapeSz-sdz;

	for (SLong i=0;i<6;i++)
	{
		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
	}

	if (ispalettised)
	{
		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[5],lvl);
		DDShadowTriangle8(prsd,vertex[2],vertex[3],vertex[5],lvl);
		DDShadowTriangle8(prsd,vertex[3],vertex[4],vertex[5],lvl);
	}
	else
	{
		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[5],lvl);
		DDShadowTriangle16(prsd,vertex[2],vertex[3],vertex[5],lvl);
		DDShadowTriangle16(prsd,vertex[3],vertex[4],vertex[5],lvl);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadOctant2
//Author		Paul.   
//Date			Mon 26 Oct 1998
//------------------------------------------------------------------------------
inline void RenderShadOctant2(ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
{
	//shadow is E facing 4 points & 2 polys required

	VData vertex[4];

	SLong shape2Pix=5;	//lvl+5;

	if ((sdp->Size>>shape2Pix)==0)
		return;

	SLong shapeSx=sdp->sx>>shape2Pix;
	SLong shapeSy=sdp->sy>>shape2Pix;
	SLong shapeSz=sdp->sz>>shape2Pix;

	if (shapeSy==0) return;	//shapeSy=1;
	if (shapeSx==0) return; //shapeSx=1;
	if (shapeSz==0) return; //shapeSz=1;

	//scale shadow DX,DZ based on the shapes height

	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;

	vertex[0].v=0;
	vertex[0].x=x-shapeSx;
	vertex[0].y=z+shapeSz;

	vertex[1].v=1;
	vertex[1].x=x-shapeSx;
	vertex[1].y=z-shapeSz;

	vertex[2].v=2;
	vertex[2].x=x+shapeSx+sdx;
	vertex[2].y=z-shapeSz;

	vertex[3].v=3;
	vertex[3].x=x+shapeSx+sdx;
	vertex[3].y=z+shapeSz;

	for (SLong i=0;i<4;i++)
	{
		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
	}

	if (ispalettised)
	{
		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
	}
	else
	{
		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadOctant3
//Author		Paul.   
//Date			Mon 26 Oct 1998
//------------------------------------------------------------------------------
inline void RenderShadOctant3(ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
{
	//shadow is SE facing 6 points & 4 polys required

	VData vertex[6];

	SLong shape2Pix=5;	//lvl+5;

	if ((sdp->Size>>shape2Pix)==0)
		return;

	SLong shapeSx=sdp->sx>>shape2Pix;
	SLong shapeSy=sdp->sy>>shape2Pix;
	SLong shapeSz=sdp->sz>>shape2Pix;

	if (shapeSy==0) return;	//shapeSy=1;
	if (shapeSx==0) return; //shapeSx=1;
	if (shapeSz==0) return; //shapeSz=1;

	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;

	//scale shadow DX,DZ based on the shapes height

	vertex[0].v=0;
	vertex[0].x=x-shapeSx;
	vertex[0].y=z+shapeSz;

	vertex[1].v=1;
	vertex[1].x=x-shapeSx;
	vertex[1].y=z-shapeSz;

	vertex[2].v=2;
	vertex[2].x=x+shapeSx;
	vertex[2].y=z-shapeSz;

	vertex[3].v=3;
	vertex[3].x=x+sdx+shapeSx;
	vertex[3].y=z-sdz-shapeSz;

	vertex[4].v=4;
	vertex[4].x=x+sdx+shapeSx;
	vertex[4].y=z-sdz+shapeSz;

	vertex[5].v=5;
	vertex[5].x=x+sdx-shapeSx;
	vertex[5].y=z-sdz+shapeSz;

	for (SLong i=0;i<6;i++)
	{
		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
	}
	
	if (ispalettised)
	{
		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[3],vertex[5],lvl);
		DDShadowTriangle8(prsd,vertex[3],vertex[4],vertex[5],lvl);
	}
	else
	{
		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[3],vertex[5],lvl);
		DDShadowTriangle16(prsd,vertex[3],vertex[4],vertex[5],lvl);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadOctant4
//Author		Paul.   
//Date			Mon 26 Oct 1998
//------------------------------------------------------------------------------
inline void RenderShadOctant4(ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
{
	//shadow is S facing 4 points & 2 polys required

	VData vertex[4];

	SLong shape2Pix=5;	//lvl+5;

	if ((sdp->Size>>shape2Pix)==0)
		return;

	SLong shapeSx=sdp->sx>>shape2Pix;
	SLong shapeSy=sdp->sy>>shape2Pix;
	SLong shapeSz=sdp->sz>>shape2Pix;

	if (shapeSy==0) return;	//shapeSy=1;
	if (shapeSx==0) return; //shapeSx=1;
	if (shapeSz==0) return; //shapeSz=1;

	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;

	//scale shadow DX,DZ based on the shapes height

	vertex[0].v=0;
	vertex[0].x=x-shapeSx;
	vertex[0].y=z-shapeSz;

	vertex[1].v=1;
	vertex[1].x=x+shapeSx;
	vertex[1].y=z-shapeSz;

	vertex[2].v=2;
	vertex[2].x=x+shapeSx;
	vertex[2].y=z+shadowDZ+shapeSz;

	vertex[3].v=3;
	vertex[3].x=x-shapeSx;
	vertex[3].y=z+shadowDZ+shapeSz;

	for (SLong i=0;i<4;i++)
	{
		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
	}

	if (ispalettised)
	{
		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
	}
	else
	{
		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadOctant5
//Author		Paul.   
//Date			Mon 26 Oct 1998
//------------------------------------------------------------------------------
inline void RenderShadOctant5(ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
{
	//shadow is SW facing 6 points & 4 polys required

	VData vertex[6];

	SLong shape2Pix=5;	//lvl+5;

	if ((sdp->Size>>shape2Pix)==0)
		return;

	SLong shapeSx=sdp->sx>>shape2Pix;
	SLong shapeSy=sdp->sy>>shape2Pix;
	SLong shapeSz=sdp->sz>>shape2Pix;

	if (shapeSy==0) return;	//shapeSy=1;
	if (shapeSx==0) return; //shapeSx=1;
	if (shapeSz==0) return; //shapeSz=1;

	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;

	//scale shadow DX,DZ based on the shapes height

	vertex[0].v=0;
	vertex[0].x=x-shapeSx;
	vertex[0].y=z-shapeSz;

	vertex[1].v=1;
	vertex[1].x=x+shapeSx;
	vertex[1].y=z-shapeSz;

	vertex[2].v=2;
	vertex[2].x=x+shapeSx;
	vertex[2].y=z+shapeSz;

	vertex[3].v=3;
	vertex[3].x=x+shadowDX+shapeSx;
	vertex[3].y=z+shadowDZ+shapeSz;

	vertex[4].v=4;
	vertex[4].x=x+shadowDX-shapeSx;
	vertex[4].y=z+shadowDZ+shapeSz;

	vertex[5].v=5;
	vertex[5].x=x+shadowDX-shapeSx;
	vertex[5].y=z+shadowDZ-shapeSz;

	for (SLong i=0;i<6;i++)
	{
		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
	}

	if (ispalettised)
	{
		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[3],vertex[5],lvl);
		DDShadowTriangle8(prsd,vertex[3],vertex[4],vertex[5],lvl);
	}
	else
	{
		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[3],vertex[5],lvl);
		DDShadowTriangle16(prsd,vertex[3],vertex[4],vertex[5],lvl);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadOctant6
//Author		Paul.   
//Date			Mon 26 Oct 1998
//------------------------------------------------------------------------------
inline void RenderShadOctant6(ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
{
	//shadow is W facing 4 points & 2 polys required

	VData vertex[4];

	SLong shape2Pix=5;	//lvl+5;

	if ((sdp->Size>>shape2Pix)==0)
		return;

	SLong shapeSx=sdp->sx>>shape2Pix;
	SLong shapeSy=sdp->sy>>shape2Pix;
	SLong shapeSz=sdp->sz>>shape2Pix;

	if (shapeSy==0) return;	//shapeSy=1;
	if (shapeSx==0) return; //shapeSx=1;
	if (shapeSz==0) return; //shapeSz=1;

	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;

	//scale shadow DX,DZ based on the shapes height

	vertex[0].v=0;
	vertex[0].x=x+shapeSx;
	vertex[0].y=z-shapeSz;

	vertex[1].v=1;
	vertex[1].x=x+shapeSx;
	vertex[1].y=z+shapeSz;

	vertex[2].v=2;
	vertex[2].x=x+shadowDX-shapeSx;
	vertex[2].y=z+shapeSz;

	vertex[3].v=3;
	vertex[3].x=x+shadowDX-shapeSx;
	vertex[3].y=z-shapeSz;

	for (SLong i=0;i<4;i++)
	{
		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
	}

	if (ispalettised)
	{
		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
	}
	else
	{
		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadOctant7
//Author		Paul.   
//Date			Mon 26 Oct 1998
//------------------------------------------------------------------------------
inline void RenderShadOctant7(ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
{
	//shadow is NW facing 6 points & 4 polys required

	VData vertex[6];

	SLong shape2Pix=5;	//lvl+5;

	if ((sdp->Size>>shape2Pix)==0)
		return;

	SLong shapeSx=sdp->sx>>shape2Pix;
	SLong shapeSy=sdp->sy>>shape2Pix;
	SLong shapeSz=sdp->sz>>shape2Pix;

	if (shapeSy==0) return;	//shapeSy=1;
	if (shapeSx==0) return; //shapeSx=1;
	if (shapeSz==0) return; //shapeSz=1;

	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;

	//scale shadow DX,DZ based on the shapes height

	vertex[0].v=0;
	vertex[0].x=x+shapeSx;
	vertex[0].y=z+shapeSz;

	vertex[1].v=1;
	vertex[1].x=x-shapeSx;
	vertex[1].y=z+shapeSz;

	vertex[2].v=2;
	vertex[2].x=x+shadowDX-shapeSx;
	vertex[2].y=z+shadowDZ+shapeSz;

	vertex[3].v=3;
	vertex[3].x=x+shadowDX-shapeSx;
	vertex[3].y=z+shadowDZ-shapeSz;

	vertex[4].v=4;
	vertex[4].x=x+shadowDX+shapeSx;
	vertex[4].y=z+shadowDZ-shapeSz;

	vertex[5].v=5;
	vertex[5].x=x+shapeSx;
	vertex[5].y=z-shapeSz;

	for (SLong i=0;i<6;i++)
	{
		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
	}

	if (ispalettised)
	{
		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[5],lvl);
		DDShadowTriangle8(prsd,vertex[2],vertex[3],vertex[4],lvl);
		DDShadowTriangle8(prsd,vertex[2],vertex[4],vertex[5],lvl);
	}
	else
	{
		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[5],lvl);
		DDShadowTriangle16(prsd,vertex[2],vertex[3],vertex[4],lvl);
		DDShadowTriangle16(prsd,vertex[2],vertex[4],vertex[5],lvl);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadow
//Author		Paul.   
//Date			Fri 23 Oct 1998
//------------------------------------------------------------------------------
void RenderShadow(ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
{
	ClearRecords(UByte(6));

	if (shadowDX==0)
	{
		if (shadowDZ>0)					RenderShadOctant0(prsd,sdp,x,z,lvl);
		else if (shadowDZ<0)			RenderShadOctant4(prsd,sdp,x,z,lvl);
	}
	else if (shadowDZ==0)
	{
		if (shadowDX>0)					RenderShadOctant2(prsd,sdp,x,z,lvl);
		else if (shadowDX<0)			RenderShadOctant6(prsd,sdp,x,z,lvl);
	}
	else if (shadowDX>0 && shadowDZ>0)	RenderShadOctant1(prsd,sdp,x,z,lvl);
	else if (shadowDX>0 && shadowDZ<0)	RenderShadOctant3(prsd,sdp,x,z,lvl);
	else if (shadowDX<0 && shadowDZ<0)	RenderShadOctant5(prsd,sdp,x,z,lvl);
	else if (shadowDX<0 && shadowDZ>0)	RenderShadOctant7(prsd,sdp,x,z,lvl);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadowRotated
//Author		Paul.   
//Date			Tue 23 Feb 1999
//------------------------------------------------------------------------------
void RenderShadowRotated(	ROWANSURFACEDESC* prsd,ShapeDescPtr sdp,
							SLong ix,SLong iz,
							SLong hdg,SLong lvl)
{
	SLong shape2Pix=5;

	if ((sdp->Size>>shape2Pix)==0)
		return;

	SLong shapeSx=sdp->sx>>shape2Pix;
	SLong shapeSy=sdp->sy>>shape2Pix;
	SLong shapeSz=sdp->sz>>shape2Pix;

	if (shapeSy==0) return;	//shapeSy=1;
	if (shapeSx==0) return; //shapeSx=1;
	if (shapeSz==0) return; //shapeSz=1;

	//scale shadow DX,DZ based on the shapes height

	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;
	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;

 	SWord sinAng,cosAng;

	ANGLES hdgAng=(Angles)hdg;

	Math_Lib.high_sin_cos(hdgAng,sinAng,cosAng);

	SLong m[4];
	SLong x[8];
	SLong z[8];

	//generate 2D rotation matrix

	m[0]=m[3]=SLong(cosAng);
	m[1]=SLong(sinAng);
	m[2]=-SLong(sinAng);

	x[0]=x[1]=shapeSx;
	x[2]=x[3]=-shapeSx;

	z[0]=z[3]=shapeSz;
	z[1]=z[2]=-shapeSz;

	for (int i=0;i<4;i++)
	{
	 	SLong tx=ix+((m[0]*x[i])/ANGLES_FRACT+(m[1]*z[i])/ANGLES_FRACT);
	 	SLong tz=iz+((m[2]*x[i])/ANGLES_FRACT+(m[3]*z[i])/ANGLES_FRACT);
		x[i]=tx;
		x[i+4]=tx+sdx;
		z[i]=tz;
		z[i+4]=tz-sdz;
	}

	ClearRecords(UByte(8));

	RenderRotatedShad(prsd,x,z,lvl);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PatchColorData
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void PatchColorData(const SLong x,const SLong z,const SLong lvl,const Box& b)
{
	//set target texture clipping values to match 'b' and
	//then decompress color data to the area of the target
	//texture that needs an update

	SLong xoff,yoff,ixoff;

	SetTargetClip(b);
	SetDestTexturePtr(lvl);

	const SLong gridSx=x&Grid_Mask;
	const SLong gridSz=z&Grid_Mask;
	const SLong gridEx=(x+(Grid_Width<<lvl))&Grid_Mask;
	const SLong gridEz=(z+(Grid_Width<<lvl))&Grid_Mask;

	//Find out how many tiles are needed to cover this area

	const SLong block_width=Grid_Width<<lvl;

	xoff=(gridSx-x)>>(9+lvl);
	yoff=(gridSz-z)>>(9+lvl);

	SWord duv;
	SWord resetu;

	if (lvl<3) 
	{
		resetu=duv=uoffset=voffset=0;
	}
	else 
	{
		resetu=uoffset=((gridSx>>17)&7)<<5;
		voffset=((gridSz>>17)&7)<<5;
		duv=32;
	}

	for (int i=gridSz;i<=gridEz;i+=Grid_Width)
	{
		ixoff=xoff;
		uoffset=resetu;

		for (int j=gridSx;j<=gridEx;j+=Grid_Width)
		{
			//make an index into the data record table
			//for the coordinate (j,i)

			SLong dgi=MakeDataGridIndex(j,i);

			if (dgi!=-1 && yoff<256 && ixoff<256)
  			{
				UByte* pdata=Three_Dee.pMigLand->MakeIData(gridRecords[dgi],lvl>>1);
	  
				Render2Map(pdata,ixoff,yoff,lvl);
		  	}
		  	ixoff+=physWidth;
			uoffset+=duv;
		}
		yoff+=physWidth;
		voffset+=duv;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateColorData
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void UpdateColorData(const SLong x,const SLong z,const SLong lvl)
{
	Box src_rect,dst_rect;

	//first find out how much of the current set of data can be
	//retained
	
	const SLong nx=x;
	const SLong nz=z;
	const SLong TextureFin=TextureWidth;

	//if there is no change or the change is
	//greater than the area covered by this tile
	//then update the whole area

	//if we get here then the full tile needs rebuilding

	src_rect.left=src_rect.top=0;
	src_rect.right=src_rect.bottom=TextureFin;
	dst_rect=src_rect;

	PatchColorData(nx,nz,lvl,src_rect);

	//upload the full tile

	PartialTextureUpload(src_rect,dst_rect,lvl);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateGridRecords
//Author		Paul.   
//Date			Mon 20 Jul 1998
//------------------------------------------------------------------------------
void UpdateGridRecords(const SLong x,const SLong z)
{
	DataRecord* pdr=gridRecords;
	ShadowStruc* psr=shadowRecords;
	SLong ox,oz,ix;
	SLong dataGridSize;

	dataGridSize=DataGridSizeMIN;

	ox=(x&Grid_Mask)-((dataGridSize>>1)*Grid_Width);
	oz=(z&Grid_Mask)-((dataGridSize>>1)*Grid_Width);

	SLong dx=Abs(gridRecordBase_x-ox);
	SLong dz=Abs(gridRecordBase_z-oz);

	if (dx!=0 || dz!=0)
	{
		gridRecordBase_x=ox;
		gridRecordBase_z=oz;

		for (int j=0;j<dataGridSize;j++)
		{
			ix=ox;
			for (int k=0;k<dataGridSize;k++)
			{
				*pdr++=Three_Dee.pMigLand->GetData(ix,oz);
				psr->world_x=ix;
				psr->world_z=oz;
				psr++;
				ix+=Grid_Width;
			}
			oz+=Grid_Width;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitGridRecords
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void InitGridRecords(const SLong x,const SLong z)
{
	SLong ox,oz,ix;
	SLong dataGridSize;
	DataRecord* pdr;
	ShadowStruc* psr=shadowRecords;

//	dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//					DataGridSizeMAX:DataGridSizeMIN;
	dataGridSize=DataGridSizeMIN;

	pdr=gridRecords;
	ox=(x&Grid_Mask)-((dataGridSize>>1)*Grid_Width);
	oz=(z&Grid_Mask)-((dataGridSize>>1)*Grid_Width);

	gridRecordBase_x=ox;
	gridRecordBase_z=oz;

	for (int j=0;j<dataGridSize;j++)
	{
		ix=ox;
		for (int k=0;k<dataGridSize;k++)
		{
			*pdr++=Three_Dee.pMigLand->GetData(ix,oz);
			psr->world_x=ix;
			psr->world_z=oz;
			psr++;
			ix+=Grid_Width;
		}
		oz+=Grid_Width;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessLandUpdateRequests
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void ProcessLandUpdateRequests(const SLong x,const SLong z,bool firstTime=false)
{
	SLong	update_size;
	SLong	square_halfsize;
	ULong	update_mask;
	SLong	maxTextureLevels;

//	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//					Max_TextureLevelsMAX:Max_TextureLevelsMIN;
	maxTextureLevels=Max_TextureLevelsMIN;

	update_size=(Grid_Width>>3)<<detail_min;
	square_halfsize=(Grid_Width>>1)<<detail_min;

	for (int i=detail_min;i<maxTextureLevels;i++)
	{
		if (update_req[i])
		{
			update_req[i]=false;

			update_mask=~ULong(update_size-1);

			land_x[i]=(x&update_mask)-square_halfsize;
			land_z[i]=(z&update_mask)-square_halfsize;

			UpdateColorData(land_x[i],land_z[i],i);

			//allow for complete update on first frame of 3D
			if (!firstTime)
				return;
		}
		square_halfsize+=square_halfsize;
		update_size+=update_size;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBlock
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
inline DataRecord GetBlock(const SLong x,const SLong z)
{
//	SLong dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?DataGridSizeMAX:DataGridSizeMIN;
	SLong dataGridSize=DataGridSizeMIN;
	SLong ix=(x&Grid_Mask)-gridRecordBase_x;
	SLong iz=(z&Grid_Mask)-gridRecordBase_z;
	ix/=Grid_Width;
	iz/=Grid_Width;
	return gridRecords[(iz*dataGridSize)+ix];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSquares
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
void GetSquares(Rect* squares)
{
	SLong square_size=131072;
	SLong maxTextureLevels;
//	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?Max_TextureLevelsMAX:Max_TextureLevelsMIN;
	maxTextureLevels=Max_TextureLevelsMIN;
	for (int i=0;i<maxTextureLevels;i++)
	{
		Rect& r=squares[i];
		r.t=land_z[i];
		r.l=land_x[i];
		r.b=r.t+square_size;
		r.r=r.l+square_size;
		square_size+=square_size;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeClipRects
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void MakeClipRects()
{
//	Rect squares[Max_TextureLevels];
//	SLong maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//							Max_TextureLevelsMAX:Max_TextureLevelsMIN;
	SLong maxTextureLevels=Max_TextureLevelsMIN;

	Rect* squares=new Rect[maxTextureLevels];

	Rect* pcr=clipRects;
	bool splitlr=true;

	GetSquares(squares);
	clipRectCnt=0;

	for (int i=maxTextureLevels-1;i>0;i--)
	{
		int j=i-1;

		Rect& outer=squares[i];
		Rect& inner=squares[j];

		*pcr++=outer;

		if (splitlr)
		{
			pcr->l=outer.l;
			pcr->r=inner.l;
			pcr->t=outer.t;
			pcr->b=outer.b;
			pcr++;

			pcr->l=inner.l;
			pcr->r=inner.r;
			pcr->t=outer.t;
			pcr->b=inner.t;
			pcr++;

			pcr->l=inner.r;
			pcr->r=outer.r;
			pcr->t=outer.t;
			pcr->b=outer.b;
			pcr++;

			pcr->l=inner.l;
			pcr->r=inner.r;
			pcr->t=inner.b;
			pcr->b=outer.b;
			pcr++;
		}
		else
		{
			pcr->l=outer.l;
			pcr->r=inner.l;
			pcr->t=inner.t;
			pcr->b=inner.b;
			pcr++;

			pcr->l=outer.l;
			pcr->r=outer.r;
			pcr->t=outer.t;
			pcr->b=inner.t;
			pcr++;

			pcr->l=inner.r;
			pcr->r=outer.r;
			pcr->t=inner.t;
			pcr->b=inner.b;
			pcr++;

			pcr->l=outer.l;
			pcr->r=outer.r;
			pcr->t=inner.b;
			pcr->b=outer.b;
			pcr++;
		}
		splitlr=splitlr?false:true;
		clipRectCnt+=5;
	}
	*pcr++=squares[0];
	clipRectCnt++;

	delete[]squares;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetClipRegion
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void GetClipRegion(const UByte index,Rect& clip)
{
	clip=clipRects[index];
}

const SLong _tl=0;
const SLong _tr=1;
const SLong _bl=2;
const SLong _br=3;

SquareClips* wholeAreaClips;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		clip_recurse
//Author		Paul.   
//Date			Wed 29 Jul 1998
//------------------------------------------------------------------------------
void clip_recurse(SLong* xvals,SLong* zvals,SLong level,SquareClips* psqc)
{
	SLong maxTextureLevels;
	SLong levelBase=5*level;
	SLong levelNext=levelBase+5;

	UWord clipFlags[4];
	UWord edgeFlags[4];
	UWord andedFlags;
	UWord oredFlags;

//	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//						Max_TextureLevelsMAX:Max_TextureLevelsMIN;
	maxTextureLevels=Max_TextureLevelsMIN;

	Rect& out=clipRects[levelBase];

	//handle very last area check as a special case

	if (level==maxTextureLevels-1)
	{
		//if any other clipping has already been added then
		//all we need to do is add this clip area to the
		//current list and return

		if (psqc->count!=0)
		{
	  		ClipInfo& ci=psqc->clipInfo[psqc->count++];
			ci.level=maxTextureLevels-1-level;
			ci.clipRecIndex=levelBase;
		}
		return;
	}

	Rect& in=clipRects[levelNext];

	//generate clip flags based on the inner tile

	andedFlags=_offleft+_offright+_offtop+_offbottom;
	oredFlags=0;

	for (int t=0;t<4;t++)
	{
		//Make sure that points on an edge have no influence
		//on inside/outside tests

		ClipResult(xvals[t],zvals[t],in,clipFlags[t],edgeFlags[t]);
		andedFlags&=clipFlags[t]|edgeFlags[t];
		oredFlags|=clipFlags[t];
	}

	//oredFlags==0 if all of the points in the 
	//	tile currently being considered are inside the
	//	inner area

	if (oredFlags==0)
	{
		level++;
		clip_recurse(xvals,zvals,level,psqc);
		return;
	}

	//andedFlags!=0 if all of the points in the
	//	tile currently being considered are outside the
	//	inner area

	if (andedFlags!=0)
	{
		//if psqc->count==0 then no clipping has been
		//set for this tile yet. This means that it is
		//safe to say that no clipping is needed at all

		if (psqc->count==0)
		{
			//just fill in the correct texture level index
			//and return
			psqc->clipInfo[0].level=maxTextureLevels-1-level;
			return;
		}
		else
		{
			//some clipping data has already been generated for 
			//this tile so I need to add some more for this
			//level

			//first stage is to check whether this tile is contained
			//entirely within one of the 4 cliping regions surrounding
			//the central area

			for (int s=1;s<5;s++)
			{
			 	Rect& cr=clipRects[levelBase+s];
				oredFlags=0;

				for (t=0;t<4;t++)
				{
					//points on edges have no influence on the inside
					//outside tests done later

					ClipResult(xvals[t],zvals[t],cr,clipFlags[t],edgeFlags[t]);
					oredFlags|=clipFlags[t];
				}

				//if oredFlags==0 then the tile is completly inside
				//the current region under test

				if (oredFlags==0)
				{
			  		ClipInfo& ci=psqc->clipInfo[psqc->count++];
					ci.level=maxTextureLevels-1-level;
					ci.clipRecIndex=levelBase+s;
					return;
				}
			}

			//if we get here then this tile must span multiple
			//clip regions at this level so just add all clip 
			//regions that contain a point to our list

			for (s=1;s<5;s++)
			{
				Rect& cr=clipRects[levelBase+s];

				andedFlags=_offleft+_offright+_offtop+_offbottom;

				for (t=0;t<4;t++)
				{
					//points on edges have no influence on the inside
					//outside tests done later

					ClipResult(xvals[t],zvals[t],cr,clipFlags[t],edgeFlags[t]);
					andedFlags&=clipFlags[t]|edgeFlags[t];
				}

				//if andedFlags==0 then at least one of the tiles
				//points was inside the current clipregion so add
				//it to the list

				if (andedFlags==0)
				{
			  		ClipInfo& ci=psqc->clipInfo[psqc->count++];
					ci.level=maxTextureLevels-1-level;
					ci.clipRecIndex=levelBase+s;
				}
			}
			return;
		}
	}

	//some part of the current tile is in this level and some is in the
	//next. Add the clip areas to be used for the current level. Clip the
	//tile to the central section and recurse

	SLong newxvals[4],newzvals[4];

	newxvals[_tl]=(clipFlags[_tl]&_offleft)?in.l:xvals[_tl];
	newxvals[_bl]=(clipFlags[_bl]&_offleft)?in.l:xvals[_bl];
	newxvals[_tr]=(clipFlags[_tr]&_offright)?in.r:xvals[_tr];
	newxvals[_br]=(clipFlags[_br]&_offright)?in.r:xvals[_br];
	newzvals[_tl]=(clipFlags[_tl]&_offtop)?in.t:zvals[_tl];
	newzvals[_tr]=(clipFlags[_tr]&_offtop)?in.t:zvals[_tr];
	newzvals[_bl]=(clipFlags[_bl]&_offtop)?in.b:zvals[_bl];
	newzvals[_br]=(clipFlags[_br]&_offtop)?in.b:zvals[_br];

	for (int s=1;s<5;s++)
	{
		Rect& cr=clipRects[levelBase+s];

		andedFlags=_offleft+_offright+_offtop+_offbottom;

		for (t=0;t<4;t++)
		{
			//points on edges have no influence on the inside
			//outside tests done later

			ClipResult(xvals[t],zvals[t],cr,clipFlags[t],edgeFlags[t]);
			andedFlags&=clipFlags[t]|edgeFlags[t];
		}

		//if andedFlags==0 then at least one of the tiles
		//points was inside the current clipregion so add
		//it to the list

		if (andedFlags==0)
		{
	  		ClipInfo& ci=psqc->clipInfo[psqc->count++];
			ci.level=maxTextureLevels-1-level;
			ci.clipRecIndex=levelBase+s;
		}
	}
	level++;
	clip_recurse(newxvals,newzvals,level,psqc);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TileClipCone
//Author		Paul.   
//Date			Wed 29 Jul 1998
//Description	This routine needs to examine each tile based on the CD grid 
//				block system and determine (a) whether the tile needs to be
//				clipped against any of the previously generated clip regions
//				and (b) which level of the texture based grid should be used
//				when the tile is rendered.
//				if the tile crosses the boundary between levels on the texture
//				grid then 
//------------------------------------------------------------------------------
void TileClipCone(const SLong wx,const SLong wz)
{
	SquareClips* pSquareClips;
	SLong ox,oz,ix;
	SLong dataGridSize;
	SLong wholeAreaSize;

//	dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//					DataGridSizeMAX:DataGridSizeMIN;

//	wholeAreaSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//					_wholeAreaSizeMAX:_wholeAreaSizeMIN;
	dataGridSize=DataGridSizeMIN;
	wholeAreaSize=_wholeAreaSizeMIN;

	ox=(wx&Grid_Mask)-((dataGridSize>>1)*Grid_Width);
	oz=(wz&Grid_Mask)-((dataGridSize>>1)*Grid_Width);

	pSquareClips=wholeAreaClips;

	for (int r=0;r<wholeAreaSize;r++)
	{
		ix=ox;

	 	for (int c=0;c<wholeAreaSize;c++)
		{
			SLong xvals[4],zvals[4];

			//set up world coordinates for the corner points of the
			//tile currently under consideration

			xvals[_tl]=ix;
			zvals[_tl]=oz;

			xvals[_tr]=ix+Grid_Width;
			zvals[_tr]=oz;

			xvals[_bl]=ix;
			zvals[_bl]=oz+Grid_Width;

			xvals[_br]=ix+Grid_Width;
			zvals[_br]=oz+Grid_Width;

			pSquareClips->count=0;

			clip_recurse(xvals,zvals,0,pSquareClips);

			pSquareClips++;
			ix+=Grid_Width;
		}
		oz+=Grid_Width;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTileClipData
//Author		Paul.   
//Date			Thu 30 Jul 1998
//------------------------------------------------------------------------------
void GetTileClipData(SquareClips*& psc)
{
	psc=wholeAreaClips;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrepareNoiseFn
//Author		Paul.   
//Date			Fri 7 Aug 1998
//------------------------------------------------------------------------------
void PrepareNoiseFn()
{
	for (int x=0;x<256;x++) tileRnd[x]=Math_Lib.rnd(SLong(0xFF));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasPixel8
//Author		Paul.   
//Date			Fri 7 Aug 1998
//------------------------------------------------------------------------------
void SAliasPixel8(SLong x,SLong y)
{
	x=Clamp(SWord(x),SpanMin,SSpanMax);
	y=Clamp(SWord(y),SpanMin,SSpanMax);
	UByte* ptxtadr=((UByte*)pdsttxt)+(x<<8)+y;
	*ptxtadr=currentRouteColor8;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasPixel8
//Author		Paul.   
//Date			Fri 7 Aug 1998
//------------------------------------------------------------------------------
void NAliasPixel8(SLong x,SLong y)
{
	x=Clamp(SWord(x),SpanMin,SSpanMax);
	y=Clamp(SWord(y),SpanMin,SSpanMax);
	UByte* ptxtadr=((UByte*)pdsttxt)+(y<<8)+x;
	*ptxtadr=currentRouteColor8;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasPixel16
//Author		Paul.   
//Date			Fri 7 Aug 1998
//------------------------------------------------------------------------------
void SAliasPixel16(SLong x,SLong y)
{
	x=Clamp(SWord(x),SpanMin,SSpanMax);
	y=Clamp(SWord(y),SpanMin,SSpanMax);
	UWord* ptxtadr=((UWord*)pdsttxt)+(x<<8)+y;
	*ptxtadr=currentRouteColor16;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasPixel16
//Author		Paul.   
//Date			Fri 7 Aug 1998
//------------------------------------------------------------------------------
void NAliasPixel16(SLong x,SLong y)
{
	x=Clamp(SWord(x),SpanMin,SSpanMax);
	y=Clamp(SWord(y),SpanMin,SSpanMax);
	UWord* ptxtadr=((UWord*)pdsttxt)+(y<<8)+x;
	*ptxtadr=currentRouteColor16;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SDDAliasPixel8
//Author		Paul.   
//Date			Wed 11 Nov 1998
//------------------------------------------------------------------------------
void SDDAliasPixel8(ROWANSURFACEDESC* prsd,SLong x,SLong y)
{
	UByte* ptxtadr=((UByte*)prsd->lpSurface)+(x*prsd->lPitch)+y;
	*ptxtadr=currentRouteColor8;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NDDAliasPixel8
//Author		Paul.   
//Date			Wed 11 Nov 1998
//------------------------------------------------------------------------------
void NDDAliasPixel8(ROWANSURFACEDESC* prsd,SLong x,SLong y)
{
	UByte* ptxtadr=((UByte*)prsd->lpSurface)+(y*prsd->lPitch)+x;
	*ptxtadr=currentRouteColor8;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SDDAliasPixel16
//Author		Paul.   
//Date			Wed 11 Nov 1998
//------------------------------------------------------------------------------
void SDDAliasPixel16(ROWANSURFACEDESC* prsd,SLong x,SLong y)
{
	UWord* ptxtadr=((UWord*)(SLong(prsd->lpSurface)+x*prsd->lPitch))+y;
	*ptxtadr=currentRouteColor16;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NDDAliasPixel16
//Author		Paul.   
//Date			Wed 11 Nov 1998
//------------------------------------------------------------------------------
void NDDAliasPixel16(ROWANSURFACEDESC* prsd,SLong x,SLong y)
{
	UWord* ptxtadr=((UWord*)(SLong(prsd->lpSurface)+y*prsd->lPitch))+x;
	*ptxtadr=currentRouteColor16;
}

void SymLine(SLong,SLong,SLong,SLong);

void DoLClip(const SWord v1,const SWord v2)
{
	static XData vc[16];
	static XDataPtr linedef[2];

	XDataPtr newv;

	vc[0].x=xoffset+(pointdef[v1].x>>tile_scale);
	vc[0].y=yoffset+(256-pointdef[v1].z>>tile_scale);
	vc[0].cf=clipRecord[v1];

	vc[1].x=xoffset+(pointdef[v2].x>>tile_scale);
	vc[1].y=yoffset+(256-pointdef[v2].z>>tile_scale);
	vc[1].cf=clipRecord[v2];

	linedef[0]=vc;
	linedef[1]=vc+1;
	newv=vc+2;

	//clip against the top of the target area

	if (linedef[0]->cf&cf_top) 
	{
		ClipToTop(linedef[1],linedef[0],newv);
		linedef[0]=newv++;
	}
	else if (linedef[1]->cf&cf_top)
	{
		ClipToTop(linedef[0],linedef[1],newv);
		linedef[1]=newv++;
	}

	//clip against the bottom of the target area

	if (linedef[0]->cf&cf_bot) 
	{
		ClipToBot(linedef[1],linedef[0],newv);
		linedef[0]=newv++;
	}
	else if (linedef[1]->cf&cf_bot)
	{
		ClipToBot(linedef[0],linedef[1],newv);
		linedef[1]=newv++;
	}

	//clip against the left of the target area

	if (linedef[0]->cf&cf_lft) 
	{
		ClipToLft(linedef[1],linedef[0],newv);
		linedef[0]=newv++;
	}
	else if (linedef[1]->cf&cf_lft)
	{
		ClipToLft(linedef[0],linedef[1],newv);
		linedef[1]=newv++;
	}

	//clip against the right of the target area

	if (linedef[0]->cf&cf_rgt) 
	{
		ClipToRgt(linedef[1],linedef[0],newv);
		linedef[0]=newv++;
	}
	else if (linedef[1]->cf&cf_rgt)
	{
		ClipToRgt(linedef[0],linedef[1],newv);
		linedef[1]=newv++;
	}

	//draw what's left of the line

	SymLine(linedef[0]->x,linedef[0]->y,linedef[1]->x,linedef[1]->y);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoLine
//Author		Paul.   
//Date			Thu 13 Aug 1998
//------------------------------------------------------------------------------
void DoLine(const SWord v1,const SWord v2)
{
	SLong x1,x2,y1,y2;

	x1=xoffset+(pointdef[v1].x>>tile_scale);
	y1=yoffset+(256-pointdef[v1].z>>tile_scale);
	x2=xoffset+(pointdef[v2].x>>tile_scale);
	y2=yoffset+(256-pointdef[v2].z>>tile_scale);

	SymLine(x1,y1,x2,y2);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SymLine
//Author		Paul.   
//Date			Fri 7 Aug 1998
//------------------------------------------------------------------------------
void SymLine(SLong a1, SLong b1, SLong a2, SLong b2)
{
	plotpixelfn ppf;
	SLong dx,dy,incr1,incr2,D,x,y,xend,c,pixels_left;
	SLong x1,y1;
	SLong sign_x,sign_y,step,i;

	dx=Absolute(a2,a1,sign_x);
	dy=Absolute(b2,b1,sign_y);

	if (sign_x==sign_y)	step=1;
	else				step=-1;

	if (dy>dx)
	{
		Swap(a1,b1);
		Swap(a2,b2);
		Swap(dx,dy);
		ppf=ispalettised?SAliasPixel8:SAliasPixel16;
	}
	else ppf=ispalettised?NAliasPixel8:NAliasPixel16;

	if (a1>a2)
	{
		x=a2;
		y=b2;
		x1=a1;
		y1=b1;
	}
	else
	{
		x=a1;
		y=b1;
		x1=a2;
		y1=b2;
	}

	xend=(dx-1)/4;
	pixels_left=(dx-1)%4;	

	(*ppf)(x,y);
	(*ppf)(x1,y1);	

	incr2=4*dy-2*dx;
	if (incr2<0)
	{
		c=2*dy;
		incr1=2*c;
		D=incr1-dx;

		for(i=0;i<xend;i++)
		{
			++x;
			--x1;
			if (D<0)
			{
				(*ppf)(x,y);
				(*ppf)(++x,y);
				(*ppf)(x1,y1);
				(*ppf)(--x1,y1);
				D+=incr1;
			}
			else
			{
				if (D<c)
				{
					(*ppf)(x,y);
					(*ppf)(++x,y+=step);
					(*ppf)(x1,y1);
					(*ppf)(--x1,y1-=step);	
				}
				else
				{
					(*ppf)(x,y+=step);
					(*ppf)(++x,y);
					(*ppf)(x1,y1-=step);
					(*ppf)(--x1,y1);
				}
				D+=incr2;
			}
		}

		if (pixels_left)
		{
			if (D<0)
			{
				(*ppf)(++x,y);
				if (pixels_left>1)	(*ppf)(++x,y);
				if (pixels_left>2)	(*ppf)(--x1,y1);
			}
			else
			{
				if (D<c)
				{
					(*ppf)(++x,y);
					if (pixels_left>1)	(*ppf)(++x,y+=step);
					if (pixels_left>2)	(*ppf)(--x1,y1);
				}
				else
				{
					(*ppf)(++x,y+=step);
					if(pixels_left>1)	(*ppf)(++x,y);
					if(pixels_left>2)	(*ppf)(--x1,y1-=step);
				}
			}
		}
	}
	else
	{
		c=2*(dy-dx);
		incr1=2*c;
		D=incr1+dx;
		for (i=0;i<xend;i++)
		{
			++x;
			--x1;
			if (D>0)
			{
				(*ppf)(x,y+=step);
				(*ppf)(++x,y+=step);
				(*ppf)(x1,y1-=step);
				(*ppf)(--x1,y1-=step);
				D+=incr1;
			}
			else
			{
				if (D<c)
				{
					(*ppf)(x,y);
					(*ppf)(++x,y+=step);
					(*ppf)(x1,y1);
					(*ppf)(--x1,y1-=step);
				}
				else
				{
					(*ppf)(x,y+=step);
					(*ppf)(++x,y);
					(*ppf)(x1,y1-=step);
					(*ppf)(--x1,y1);
				}
				D+=incr2;
			}
		}

		if (pixels_left)
		{
			if (D>0)
			{
				(*ppf)(++x,y+=step);	
				if (pixels_left>1)	(*ppf)(++x,y+=step);
				if (pixels_left>2)	(*ppf)(--x1,y1-=step);
			}
			else
			{
				if (D<c)
				{
					(*ppf)(++x,y);	
					if (pixels_left>1)	(*ppf)(++x,y+=step);
					if (pixels_left>2)	(*ppf)(--x1,y1);
				}
				else
				{
					(*ppf)(++x,y+=step);
					if (pixels_left>1)	(*ppf)(++x,y);
					if (pixels_left>2)
					{
						if (D>c)		(*ppf)(--x1,y1-=step);
						else			(*ppf)(--x1,y1);
                    }
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DDSymLine
//Author		Paul.   
//Date			Wed 11 Nov 1998
//------------------------------------------------------------------------------
void DDSymLine(ROWANSURFACEDESC* prsd,SLong a1, SLong b1, SLong a2, SLong b2)
{
	ddpixelfn ppf;
	SLong dx,dy,incr1,incr2,D,x,y,xend,c,pixels_left;
	SLong x1,y1;
	SLong sign_x,sign_y,step,i;

	dx=Absolute(a2,a1,sign_x);
	dy=Absolute(b2,b1,sign_y);

	if (sign_x==sign_y)	step=1;
	else				step=-1;

	if (dy>dx)
	{
		Swap(a1,b1);
		Swap(a2,b2);
		Swap(dx,dy);
		ppf=ispalettised?SDDAliasPixel8:SDDAliasPixel16;
	}
	else ppf=ispalettised?NDDAliasPixel8:NDDAliasPixel16;

	if (a1>a2)
	{
		x=a2;
		y=b2;
		x1=a1;
		y1=b1;
	}
	else
	{
		x=a1;
		y=b1;
		x1=a2;
		y1=b2;
	}

	xend=(dx-1)/4;
	pixels_left=(dx-1)%4;	

	(*ppf)(prsd,x,y);
	(*ppf)(prsd,x1,y1);	

	incr2=4*dy-2*dx;
	if (incr2<0)
	{
		c=2*dy;
		incr1=2*c;
		D=incr1-dx;

		for(i=0;i<xend;i++)
		{
			++x;
			--x1;
			if (D<0)
			{
				(*ppf)(prsd,x,y);
				(*ppf)(prsd,++x,y);
				(*ppf)(prsd,x1,y1);
				(*ppf)(prsd,--x1,y1);
				D+=incr1;
			}
			else
			{
				if (D<c)
				{
					(*ppf)(prsd,x,y);
					(*ppf)(prsd,++x,y+=step);
					(*ppf)(prsd,x1,y1);
					(*ppf)(prsd,--x1,y1-=step);	
				}
				else
				{
					(*ppf)(prsd,x,y+=step);
					(*ppf)(prsd,++x,y);
					(*ppf)(prsd,x1,y1-=step);
					(*ppf)(prsd,--x1,y1);
				}
				D+=incr2;
			}
		}

		if (pixels_left)
		{
			if (D<0)
			{
				(*ppf)(prsd,++x,y);
				if (pixels_left>1)	(*ppf)(prsd,++x,y);
				if (pixels_left>2)	(*ppf)(prsd,--x1,y1);
			}
			else
			{
				if (D<c)
				{
					(*ppf)(prsd,++x,y);
					if (pixels_left>1)	(*ppf)(prsd,++x,y+=step);
					if (pixels_left>2)	(*ppf)(prsd,--x1,y1);
				}
				else
				{
					(*ppf)(prsd,++x,y+=step);
					if(pixels_left>1)	(*ppf)(prsd,++x,y);
					if(pixels_left>2)	(*ppf)(prsd,--x1,y1-=step);
				}
			}
		}
	}
	else
	{
		c=2*(dy-dx);
		incr1=2*c;
		D=incr1+dx;
		for (i=0;i<xend;i++)
		{
			++x;
			--x1;
			if (D>0)
			{
				(*ppf)(prsd,x,y+=step);
				(*ppf)(prsd,++x,y+=step);
				(*ppf)(prsd,x1,y1-=step);
				(*ppf)(prsd,--x1,y1-=step);
				D+=incr1;
			}
			else
			{
				if (D<c)
				{
					(*ppf)(prsd,x,y);
					(*ppf)(prsd,++x,y+=step);
					(*ppf)(prsd,x1,y1);
					(*ppf)(prsd,--x1,y1-=step);
				}
				else
				{
					(*ppf)(prsd,x,y+=step);
					(*ppf)(prsd,++x,y);
					(*ppf)(prsd,x1,y1-=step);
					(*ppf)(prsd,--x1,y1);
				}
				D+=incr2;
			}
		}

		if (pixels_left)
		{
			if (D>0)
			{
				(*ppf)(prsd,++x,y+=step);	
				if (pixels_left>1)	(*ppf)(prsd,++x,y+=step);
				if (pixels_left>2)	(*ppf)(prsd,--x1,y1-=step);
			}
			else
			{
				if (D<c)
				{
					(*ppf)(prsd,++x,y);	
					if (pixels_left>1)	(*ppf)(prsd,++x,y+=step);
					if (pixels_left>2)	(*ppf)(prsd,--x1,y1);
				}
				else
				{
					(*ppf)(prsd,++x,y+=step);
					if (pixels_left>1)	(*ppf)(prsd,++x,y);
					if (pixels_left>2)
					{
						if (D>c)		(*ppf)(prsd,--x1,y1-=step);
						else			(*ppf)(prsd,--x1,y1);
                    }
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PolyOutline
//Author		Paul.   
//Date			Fri 7 Aug 1998
//------------------------------------------------------------------------------
void PolyOutline(UByte* p)
{
	SLong xs,ys,xe,ye;
	SWord vs,ve;
	UByte polyCount;
	UByte edgeCount;

	polyCount=*p++;

	while (polyCount--)
	{
		edgeCount=*p++;
		vs=ve=*p++;
		xe=(pointdef[ve].x>>tile_scale)+xoffset;
		ye=((256-pointdef[ve].z)>>tile_scale)+yoffset;

		while (edgeCount--)
		{
			xs=xe;
			ys=ye;
			ve=*p++;
			xe=(pointdef[ve].x>>tile_scale)+xoffset;
			ye=((256-pointdef[ve].z)>>tile_scale)+yoffset;
			SymLine(xs,ys,xe,ye);
		}
		//and the last section

		xs=(pointdef[vs].x>>tile_scale)+xoffset;
		ys=((256-pointdef[vs].z)>>tile_scale)+yoffset;
		SymLine(xs,ys,xe,ye);
	}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateBuffers
//Author		Paul.   
//Date			Tue 6 Oct 1998
//------------------------------------------------------------------------------
void AllocateBuffers()
{
//	if (Save_Data.detail_3d[DETAIL3D_HORIZONDIST])
//	{
		//full horizon

//		land_x=new SLong[Max_TextureLevelsMAX];
//		land_z=new SLong[Max_TextureLevelsMAX];
//		update_req=new bool[Max_TextureLevelsMAX];
 //		gridRecords=new DataRecord[DataGridSizeMAX*DataGridSizeMAX];
//		shadowRecords=new ShadowStruc[DataGridSizeMAX*DataGridSizeMAX];
//		clipRects=new Rect[5*(Max_TextureLevelsMAX-1)+1];
//		gridClipper=new UByte[_areaBufferSizeMAX];
//		wholeAreaClips=new SquareClips[_areaBufferSizeMAX];
//	}
//	else
	{
		//reduced horizon

		land_x=new SLong[Max_TextureLevelsMIN];
		land_z=new SLong[Max_TextureLevelsMIN];
		update_req=new bool[Max_TextureLevelsMIN];
 		gridRecords=new DataRecord[DataGridSizeMIN*DataGridSizeMIN];
		shadowRecords=new ShadowStruc[DataGridSizeMIN*DataGridSizeMIN];
		clipRects=new Rect[5*(Max_TextureLevelsMIN-1)+1];
		gridClipper=new UByte[_areaBufferSizeMIN];
		wholeAreaClips=new SquareClips[_areaBufferSizeMIN];
	}

	numShadows=0;
	curSec=-1L;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseBuffers
//Author		Paul.   
//Date			Tue 6 Oct 1998
//------------------------------------------------------------------------------
void ReleaseBuffers()
{
	delete[]land_x,land_x=NULL;
	delete[]land_z,land_z=NULL;
	delete[]update_req,update_req=NULL;
	delete[]gridRecords,gridRecords=NULL;
	delete[]shadowRecords,shadowRecords=NULL;
	delete[]clipRects,clipRects=NULL;
	delete[]gridClipper,gridClipper=NULL;
	delete[]wholeAreaClips,wholeAreaClips=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildShadowList
//Author		Paul.   
//Date			Thu 22 Oct 1998
//------------------------------------------------------------------------------
void BuildShadowList(WorldStuff *wP,itemptr itemp)
{
	worldPtr=wP;

	//generate a shadow template shape

 	SWord sinAng,cosAng;

	ANGLES hdgAng=Math_Lib.HighArcTan(worldPtr->sunpos.X,worldPtr->sunpos.Z);

	Math_Lib.high_sin_cos(hdgAng,sinAng,cosAng);

	SLong m[4];

	m[0]=m[3]=SLong(cosAng);
	m[1]=SLong(sinAng);
	m[2]=-SLong(sinAng);

	const SLong dx=0x00000;
	const SLong dz=0x10000>>1;

	shadowDX=(m[0]*dx)/ANGLES_FRACT+(m[1]*dz)/ANGLES_FRACT;
	shadowDZ=(m[2]*dx)/ANGLES_FRACT+(m[3]*dz)/ANGLES_FRACT;

	UWord sec_x,sec_y;

	worldPtr->getsectornos(itemp,sec_x,sec_y);

	ULong new_sec=worldPtr->makeindex(sec_x,sec_y);

	if (new_sec==curSec) return;

	curSec=new_sec;

 	numShadows=0;

	SLong sec_cnt=12;

	for (UWord cs_x=sec_x-1;sec_cnt;cs_x++)
		for (UWord cs_y=sec_y-1;--sec_cnt&3;cs_y++)
			shadowSectors[numShadows++]=worldPtr->makeindex(cs_x,cs_y);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SortedTriangle8
//Author		Paul.   
//Date			Tue 27 Oct 1998
//------------------------------------------------------------------------------
void SortedTriangle8(VData* v)
{
	SLong det;
	SLong yi,xmin,xmax,ymax;
	Edge left,right;
	UByte* p;
	UByte* t;
	
	det=(v[1].y-v[0].y)*(v[2].x-v[0].x)-(v[1].x-v[0].x)*(v[2].y-v[0].y);

	if (det<0)
	{
	 	left=*EdgeSetup(v,v+2);
		right=*EdgeSetup(v,v+1);
	}
	else
	{
	 	right=*EdgeSetup(v,v+2);
		left=*EdgeSetup(v,v+1);
	}

	yi=left.ymin;

	p=(UByte*)pdsttxt+(yi+yoffset)*TextureWidth;

	ymax=Min(left.ymax,right.ymax);

 	UWord texture_inc=(voffset+(yi<<byteScale))<<8;
	UWord texture_dda=1<<(byteScale+8);

	for (;yi<ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
	{
		t=psrctxt+texture_inc;

		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DrawSpan8(xmin,xmax,p,t);
	}

	if (det>=0)	left=*EdgeSetup(v+1,v+2);
	else		right=*EdgeSetup(v+1,v+2);

	yi=Max(left.ymin,right.ymin);
	p=(UByte*)pdsttxt+(yi+yoffset)*TextureWidth;

 	texture_inc=(voffset+(yi<<byteScale))<<8;

	for (;yi<left.ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
	{
		t=psrctxt+texture_inc;
	 	xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DrawSpan8(xmin,xmax,p,t);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SortedTriangle16
//Author		Paul.   
//Date			Tue 27 Oct 1998
//------------------------------------------------------------------------------
void SortedTriangle16(VData* v)
{
	SLong det;
	SLong yi,xmin,xmax,ymax;
	Edge left,right;
	UWord* p;
	UByte* t;
	
	det=(v[1].y-v[0].y)*(v[2].x-v[0].x)-(v[1].x-v[0].x)*(v[2].y-v[0].y);

	if (det<0)
	{
	 	left=*EdgeSetup(v,v+2);
		right=*EdgeSetup(v,v+1);
	}
	else
	{
	 	right=*EdgeSetup(v,v+2);
		left=*EdgeSetup(v,v+1);
	}

	yi=left.ymin;

	p=((UWord*)pdsttxt)+(yi+yoffset)*TextureWidth;

	ymax=Min(left.ymax,right.ymax);

 	UWord texture_inc=(voffset+(yi<<byteScale))<<8;
	UWord texture_dda=1<<(byteScale+8);

 	for (;yi<ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
	{
 		t=psrctxt+texture_inc;
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DrawSpan16(xmin,xmax,p,t);
	}

	if (det>=0)	left=*EdgeSetup(v+1,v+2);
	else		right=*EdgeSetup(v+1,v+2);

	yi=Max(left.ymin,right.ymin);
	p=((UWord*)pdsttxt)+(yi+yoffset)*TextureWidth;

 	texture_inc=(voffset+(yi<<byteScale))<<8;

 	for (;yi<left.ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
	{
 		t=psrctxt+texture_inc;
	 	xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DrawSpan16(xmin,xmax,p,t);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShadowTriangle8
//Author		Paul.   
//Date			Tue 27 Oct 1998
//------------------------------------------------------------------------------
void ShadowTriangle8(VData v1,VData v2,VData v3)
{
	if (v1.y>v2.y) Swap(v1,v2);
	if (v1.y>v3.y) Swap(v1,v3);
	if (v2.y>v3.y) Swap(v2,v3);

	SLong det;
	SLong yi,xmin,xmax,ymax;
	Edge left,right;
	UByte* p;

	det=(v2.y-v1.y)*(v3.x-v1.x)-(v2.x-v1.x)*(v3.y-v1.y);

	if (det<0)
	{
	 	left=*EdgeSetup2(v1,v3);
		right=*EdgeSetup2(v1,v2);
	}
	else
	{
	 	right=*EdgeSetup2(v1,v3);
		left=*EdgeSetup2(v1,v2);
	}

	yi=left.ymin;
	p=(UByte*)pdsttxt+yi*TextureWidth;

	ymax=Min(left.ymax,right.ymax);

	for (;yi<ymax;yi++,p+=TextureWidth)
	{
	 	xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DarkSpan8(xmin,xmax,p);
	}

	if (det>=0)	left=*EdgeSetup2(v2,v3);
	else		right=*EdgeSetup2(v2,v3);

	yi=Max(left.ymin,right.ymin);
	p=(UByte*)pdsttxt+yi*TextureWidth;

	for (;yi<left.ymax;yi++,p+=TextureWidth)
	{
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DarkSpan8(xmin,xmax,p);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShadowTriangle16
//Author		Paul.   
//Date			Tue 27 Oct 1998
//------------------------------------------------------------------------------
void ShadowTriangle16(VData v1,VData v2,VData v3)
{
	if (v1.y>v2.y) Swap(v1,v2);
	if (v1.y>v3.y) Swap(v1,v3);
	if (v2.y>v3.y) Swap(v2,v3);

	SLong det;
	SLong yi,xmin,xmax,ymax;
	Edge left,right;
	UWord* p;

	det=(v2.y-v1.y)*(v3.x-v1.x)-(v2.x-v1.x)*(v3.y-v1.y);

	if (det<0)
	{
	 	left=*EdgeSetup2(v1,v3);
		right=*EdgeSetup2(v1,v2);
	}
	else
	{
	 	right=*EdgeSetup2(v1,v3);
		left=*EdgeSetup2(v1,v2);
	}

	yi=left.ymin;
	p=((UWord*)pdsttxt)+yi*TextureWidth;

	ymax=Min(left.ymax,right.ymax);

	for (;yi<ymax;yi++,p+=TextureWidth)
	{
	 	xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DarkSpan16(xmin,xmax,p);
	}

	if (det>=0)	left=*EdgeSetup2(v2,v3);
	else		right=*EdgeSetup2(v2,v3);

	yi=Max(left.ymin,right.ymin);
	p=((UWord*)pdsttxt)+yi*TextureWidth;
	for (;yi<left.ymax;yi++,p+=TextureWidth)
	{
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DarkSpan16(xmin,xmax,p);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SortedTriangle28
//Author		Paul.   
//Date			Tue 27 Oct 1998
//------------------------------------------------------------------------------
void SortedTriangle28(VData v1,VData v2,VData v3)
{
	SLong det;
	SLong yi,xmin,xmax,ymax;
	Edge left,right;
	UByte* p;
	UByte* t;

	det=(v2.y-v1.y)*(v3.x-v1.x)-(v2.x-v1.x)*(v3.y-v1.y);

	if (det<0)
	{
	 	left=*EdgeSetup2(v1,v3);
		right=*EdgeSetup2(v1,v2);
	}
	else
	{
	 	right=*EdgeSetup2(v1,v3);
		left=*EdgeSetup2(v1,v2);
	}

	yi=left.ymin;

	p=(UByte*)pdsttxt+(yi+yoffset)*TextureWidth;

	ymax=Min(left.ymax,right.ymax);

 	UWord texture_inc=(voffset+(yi<<byteScale))<<8;
	UWord texture_dda=1<<(byteScale+8);

	for (;yi<ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
	{
		t=psrctxt+texture_inc;
	 	xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DrawSpan8(xmin,xmax,p,t);
	}

	if (det>=0)	left=*EdgeSetup2(v2,v3);
	else		right=*EdgeSetup2(v2,v3);

	yi=Max(left.ymin,right.ymin);
	p=(UByte*)pdsttxt+(yi+yoffset)*TextureWidth;

 	texture_inc=(voffset+(yi<<byteScale))<<8;

	for (;yi<left.ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
	{
		t=psrctxt+texture_inc;
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DrawSpan8(xmin,xmax,p,t);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SortedTriangle216
//Author		Paul.   
//Date			Tue 27 Oct 1998
//------------------------------------------------------------------------------
void SortedTriangle216(VData v1,VData v2,VData v3)
{
	SLong det;
	SLong yi,xmin,xmax,ymax;
	Edge left,right;
	UWord* p;
	UByte* t;

	det=(v2.y-v1.y)*(v3.x-v1.x)-(v2.x-v1.x)*(v3.y-v1.y);

	if (det<0)
	{
	 	left=*EdgeSetup2(v1,v3);
		right=*EdgeSetup2(v1,v2);
	}
	else
	{
	 	right=*EdgeSetup2(v1,v3);
		left=*EdgeSetup2(v1,v2);
	}

	yi=left.ymin;
	p=((UWord*)pdsttxt)+(yi+yoffset)*TextureWidth;

	ymax=Min(left.ymax,right.ymax);

 	UWord texture_inc=(voffset+(yi<<byteScale))<<8;
	UWord texture_dda=1<<(byteScale+8);

	for (;yi<ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
	{
		t=psrctxt+texture_inc;
	 	xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DrawSpan16(xmin,xmax,p,t);
	}

	if (det>=0)	left=*EdgeSetup2(v2,v3);
	else		right=*EdgeSetup2(v2,v3);

	yi=Max(left.ymin,right.ymin);
	p=((UWord*)pdsttxt)+(yi+yoffset)*TextureWidth;

 	texture_inc=(voffset+(yi<<byteScale))<<8;

	for (;yi<left.ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
	{
		t=psrctxt+texture_inc;
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);
		DrawSpan16(xmin,xmax,p,t);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DDSortedTriangle8
//Author		Paul.   
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
void DDSortedTriangle8(	VTriPtr sTri,
						ROWANSURFACEDESC* prsd,
						UByte* ptxt,SWord scale)
{
	const SLong XMIN=0;
	const SLong XMAX=255;

	Edge *left,*right,edge1,edge2;
	SLong yi,xmin,xmax,ymax;
	SLong src_dx,src_dy;
	UByte* pdst;
	UByte* psrc;

	bool det=((sTri->v2.y-sTri->v1.y)*(sTri->v3.x-sTri->v1.x)-
				(sTri->v2.x-sTri->v1.x)*(sTri->v3.y-sTri->v1.y)<0)?true:false;

	edge1=*EdgeSetup(&sTri->v1,&sTri->v3,scale);
	edge2=*EdgeSetup(&sTri->v1,&sTri->v2,scale);

	if (det)	{left=&edge1;right=&edge2;}
	else		{right=&edge1;left=&edge2;}

	yi=left->ymin>>scale;

	src_dx=1<<scale;
	src_dy=TextureWidth<<scale;

	pdst=(UByte*)prsd->lpSurface+(yi*prsd->lPitch);
	psrc=ptxt+(left->ymin<<8);

	ymax=Min(left->ymax,right->ymax)>>scale;

	for (;yi<ymax;yi++)
	{
		xmin=EdgeScan(left);
		xmax=EdgeScan(right);

		xmin=Clamp(xmin,XMIN,XMAX);
		xmax=Clamp(xmax,XMIN,XMAX);

		UByte* psrc2=psrc+xmin;	//texture data ptr

		xmin>>=scale;
		xmax>>=scale;
		
		UByte* pdst2=pdst+xmin;	//DD surface ptr
		
		if (xmin<=xmax)
			for (xmax-=(xmin-1);xmax--;)
			{
				*pdst2++=*psrc2;
				psrc2+=src_dx;
			}
		pdst+=prsd->lPitch;
		psrc+=src_dy;
	}

	if (!det)	*left=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
	else		*right=*EdgeSetup(&sTri->v2,&sTri->v3,scale);

	yi=Max(left->ymin,right->ymin);

	psrc=ptxt+(yi<<8);
	yi>>=scale;
	pdst=(UByte*)prsd->lpSurface+(yi*prsd->lPitch);

	ymax=left->ymax>>scale;

	for (;yi<ymax;yi++)
	{
		xmin=EdgeScan(left);
		xmax=EdgeScan(right);

		xmin=Clamp(xmin,XMIN,XMAX);
		xmax=Clamp(xmax,XMIN,XMAX);

		UByte* psrc2=psrc+xmin;	//texture data ptr

		xmin>>=scale;
		xmax>>=scale;
		
		UByte* pdst2=pdst+xmin;	//DD surface ptr
		
		if (xmin<=xmax)
			for (xmax-=(xmin-1);xmax--;)
			{
				*pdst2++=*psrc2;
				psrc2+=src_dx;
			}
		pdst+=prsd->lPitch;
		psrc+=src_dy;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DDSortedTriangle16
//Author		Paul.   
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
void DDSortedTriangle16(VTriPtr sTri,
						ROWANSURFACEDESC* prsd,
						UByte* ptxt,SWord scale)
{
	const SLong XMIN=0;
	const SLong XMAX=255;

	Edge left,right;
	SLong yi,xmin,xmax,ymax;
	SLong src_dx,src_dy;
	UWord* pdst;
	UByte* psrc;

	bool det=((sTri->v2.y-sTri->v1.y)*(sTri->v3.x-sTri->v1.x)-
				(sTri->v2.x-sTri->v1.x)*(sTri->v3.y-sTri->v1.y)<0)?true:false;

	left=*EdgeSetup(&sTri->v1,&sTri->v3,scale);
	right=*EdgeSetup(&sTri->v1,&sTri->v2,scale);

	if (!det) Swap(left,right);

	yi=left.ymin>>scale;

	src_dx=1<<scale;
	src_dy=TextureWidth<<scale;

	pdst=(UWord*)(ULong(prsd->lpSurface)+ULong(yi*prsd->lPitch));
	psrc=ptxt+(left.ymin<<8);

	ymax=Min(left.ymax,right.ymax)>>scale;

	for (;yi<ymax;yi++)
	{
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);

		xmin=Clamp(xmin,XMIN,XMAX);
		xmax=Clamp(xmax,XMIN,XMAX);

		UByte* psrc2=psrc+xmin;	//texture data ptr

		xmin>>=scale;
		xmax>>=scale;
		
		UWord* pdst2=pdst+xmin;	//DD surface ptr
		
		if (xmin<=xmax)
			for (xmax-=(xmin-1);xmax--;)
			{
				*pdst2++=palLookup[*psrc2];
				psrc2+=src_dx;
			}
		pdst=(UWord*)(ULong(pdst)+ULong(prsd->lPitch));
		psrc+=src_dy;
	}

	if (!det)	left=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
	else		right=*EdgeSetup(&sTri->v2,&sTri->v3,scale);

	yi=Max(left.ymin,right.ymin);

	psrc=ptxt+(yi<<8);
	yi>>=scale;
	pdst=(UWord*)(ULong(prsd->lpSurface)+ULong(yi*prsd->lPitch));

	ymax=left.ymax>>scale;

	for (;yi<ymax;yi++)
	{
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);

		xmin=Clamp(xmin,XMIN,XMAX);
		xmax=Clamp(xmax,XMIN,XMAX);

		UByte* psrc2=psrc+xmin;	//texture data ptr

		xmin>>=scale;
		xmax>>=scale;
		
		UWord* pdst2=pdst+xmin;	//DD surface ptr
	
		if (xmin<=xmax)
			for (xmax-=(xmin-1);xmax--;)
			{
				*pdst2++=palLookup[*psrc2];
				psrc2+=src_dx;
			}
		pdst=(UWord*)(ULong(pdst)+ULong(prsd->lPitch));
		psrc+=src_dy;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DDShadowTriangle8
//Author		Paul.   
//Date			Tue 1 Dec 1998
//------------------------------------------------------------------------------
void DDShadowTriangle8(	ROWANSURFACEDESC* prsd,
						VData v0,VData v1,VData v2,
						SWord scale)
{
	VTri xTri,*sTri=&xTri;
	xTri.v1=v0;
	xTri.v2=v1;
	xTri.v3=v2;
	if (xTri.v1.y>xTri.v2.y)	Swap(xTri.v1,xTri.v2);
	if (xTri.v1.y>xTri.v3.y)	Swap(xTri.v1,xTri.v3);
	if (xTri.v2.y>xTri.v3.y)	Swap(xTri.v2,xTri.v3);

	const SLong XMIN=0;
	const SLong XMAX=255;

	Edge left,right;
	SLong yi,xmin,xmax,ymax;
	UByte* pdst;

	bool det=((sTri->v2.y-sTri->v1.y)*(sTri->v3.x-sTri->v1.x)-
				(sTri->v2.x-sTri->v1.x)*(sTri->v3.y-sTri->v1.y)<0)?true:false;

	left=*EdgeSetup(&sTri->v1,&sTri->v3,scale);
	right=*EdgeSetup(&sTri->v1,&sTri->v2,scale);

	if (!det) Swap(left,right);

	yi=left.ymin>>scale;

	pdst=(UByte*)prsd->lpSurface+(yi*prsd->lPitch);

	ymax=Min(left.ymax,right.ymax)>>scale;

	for (;yi<ymax;yi++)
	{
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);

		xmin=Clamp(xmin,XMIN,XMAX);
		xmax=Clamp(xmax,XMIN,XMAX);

		xmin>>=scale;
		xmax>>=scale;
		
		UByte* pdst2=pdst+xmin;	//DD surface ptr
		
		if (xmin<=xmax)
			for (xmax-=(xmin-1);xmax--;)
			{
				*pdst2++=8;	//CHANGE HERE TO ALTER SHADOW COLOUR
			}
		pdst+=prsd->lPitch;
	}

	if (!det)	left=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
	else		right=*EdgeSetup(&sTri->v2,&sTri->v3,scale);

	yi=Max(left.ymin,right.ymin);

	yi>>=scale;
	pdst=(UByte*)prsd->lpSurface+(yi*prsd->lPitch);

	ymax=left.ymax>>scale;

	for (;yi<ymax;yi++)
	{
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);

		xmin=Clamp(xmin,XMIN,XMAX);
		xmax=Clamp(xmax,XMIN,XMAX);

		xmin>>=scale;
		xmax>>=scale;
		
		UByte* pdst2=pdst+xmin;	//DD surface ptr
		
		if (xmin<=xmax)
			for (xmax-=(xmin-1);xmax--;)
			{
				*pdst2++=8;	//CHANGE HERE TO ALTER SHADOW COLOUR
			}
		pdst+=prsd->lPitch;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DDShadowTriangle16
//Author		Paul.   
//Date			Tue 1 Dec 1998
//------------------------------------------------------------------------------
void DDShadowTriangle16(ROWANSURFACEDESC* prsd,
						VData v0,VData v1,VData v2,
						SWord scale)
{
	VTri xTri,*sTri=&xTri;
	xTri.v1=v0;
	xTri.v2=v1;
	xTri.v3=v2;
	if (xTri.v1.y>xTri.v2.y)	Swap(xTri.v1,xTri.v2);
	if (xTri.v1.y>xTri.v3.y)	Swap(xTri.v1,xTri.v3);
	if (xTri.v2.y>xTri.v3.y)	Swap(xTri.v2,xTri.v3);

	const SLong XMIN=0;
	const SLong XMAX=255;

	Edge left,right;
	SLong yi,xmin,xmax,ymax;
	UWord* pdst;

	bool det=((sTri->v2.y-sTri->v1.y)*(sTri->v3.x-sTri->v1.x)-
				(sTri->v2.x-sTri->v1.x)*(sTri->v3.y-sTri->v1.y)<0)?true:false;

	left=*EdgeSetup(&sTri->v1,&sTri->v3,scale);
	right=*EdgeSetup(&sTri->v1,&sTri->v2,scale);

	if (!det) Swap(left,right);

	yi=left.ymin>>scale;

	pdst=(UWord*)(ULong(prsd->lpSurface)+ULong(yi*prsd->lPitch));

	ymax=Min(left.ymax,right.ymax)>>scale;

	for (;yi<ymax;yi++)
	{
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);

		xmin=Clamp(xmin,XMIN,XMAX);
		xmax=Clamp(xmax,XMIN,XMAX);

		xmin>>=scale;
		xmax>>=scale;
		
		UWord* pdst2=pdst+xmin;	//DD surface ptr
		
		if (xmin<=xmax)
			for (xmax-=(xmin-1);xmax--;)
			{
				*pdst2++=0;
			}
		pdst=(UWord*)(ULong(pdst)+ULong(prsd->lPitch));
	}

	if (!det)	left=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
	else		right=*EdgeSetup(&sTri->v2,&sTri->v3,scale);

	yi=Max(left.ymin,right.ymin);

	yi>>=scale;
	pdst=(UWord*)(ULong(prsd->lpSurface)+ULong(yi*prsd->lPitch));

	ymax=left.ymax>>scale;

	for (;yi<ymax;yi++)
	{
		xmin=EdgeScan(&left);
		xmax=EdgeScan(&right);

		xmin=Clamp(xmin,XMIN,XMAX);
		xmax=Clamp(xmax,XMIN,XMAX);

		xmin>>=scale;
		xmax>>=scale;
		
		UWord* pdst2=pdst+xmin;	//DD surface ptr
	
		if (xmin<=xmax)
			for (xmax-=(xmin-1);xmax--;)
			{
				*pdst2++=0;
			}
		pdst=(UWord*)(ULong(pdst)+ULong(prsd->lPitch));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTile2Surface
//Author		Paul.   
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
void RenderTile2Surface(UByte* pdata,ROWANSURFACEDESC* prsd)
{

	VTri vTri,sTri;

	AltPointsHdr*	aph;
	DrawDataHdr*	ddh;

	aph=(AltPointsHdr*)pdata;
	pdata+=sizeof(AltPointsHdr);

	ClearRecords(aph->vertexCount);

	pointdef=(PointDef*)pdata;
	pdata+=aph->vertexCount*sizeof(PointDef);

	ddh=(DrawDataHdr*)pdata;
	pdata+=sizeof(DrawDataHdr);

	SWord primCount=ddh->noOfPolys;

	SWord scale=3;													  //JIM 29/03/99

	if (prsd->dwWidth==256)			scale=0;
	else if (prsd->dwWidth==128)	scale=1;
	else if (prsd->dwWidth==64)		scale=2;
	else if (prsd->dwWidth==32)		scale=3;
	else if (prsd->dwWidth==16)		scale=4;
	else if (prsd->dwWidth==8)		scale=5;
	else assert(false&&"ERROR:Silly scale factor");

	while (primCount--)
	{
	 	UByte* ptxt=imageData[*pdata&0x1F];
		pdata++;

		UByte fanCount=*pdata++;
		
		while (fanCount--)
		{
			UByte triCount=*pdata++;

			SWord v=*pdata++;
			vTri.v1.x=pointdef[v].x;
			vTri.v1.y=(256-pointdef[v].z);
			vTri.v1.v=v;
			v=*pdata++;
			vTri.v3.x=pointdef[v].x;
			vTri.v3.y=(256-pointdef[v].z);
			vTri.v3.v=v;

			while (triCount--)
			{
			 	vTri.v2=vTri.v3;
				v=*pdata++;
				vTri.v3.x=pointdef[v].x;
				vTri.v3.y=(256-pointdef[v].z);
				vTri.v3.v=v;
				sTri=vTri;
				if (sTri.v1.y>sTri.v2.y)	Swap(sTri.v1,sTri.v2);
				if (sTri.v1.y>sTri.v3.y)	Swap(sTri.v1,sTri.v3);
				if (sTri.v2.y>sTri.v3.y)	Swap(sTri.v2,sTri.v3);

				//sTri contains the triangle vertex coordinates unscaled

				if (prsd->dwRGBBitCount==8)
					DDSortedTriangle8(&sTri,prsd,ptxt,scale);
				else if (prsd->dwRGBBitCount==16)
					DDSortedTriangle16(&sTri,prsd,ptxt,scale);
			}
		}
	}

	if (OverLay.fZoomedMap)
		primCount=ddh->noOfLines;
	else
		primCount=((scale<2) && Save_Data.detail_3d[DETAIL3D_ROUTES])?
					ddh->noOfLines:0;

	while (primCount--)
	{
		UByte lineCol;

		switch (*pdata++)
		{
		case RT_river:
			lineCol=196;
			break;
		case RT_track:
			lineCol=181;
			break;
		case RT_rail:
			lineCol=OverLay.fZoomedMap?255:1;
			break;
		case RT_road:
			lineCol=181;
			break;
		case RT_magic:
			lineCol=111;
			break;
		default:
			lineCol=0;
			break;
		}

		if (prsd->dwRGBBitCount==8)
			currentRouteColor8=lineCol;
	 	else
			currentRouteColor16=palLookup[lineCol];

		UByte sectionCount=*pdata++;

		if (lineCol==0)
			pdata+=sectionCount;
		else
		{
			SWord v=*pdata++;
			SLong x2,y2;
			x2=pointdef[v].x;
			y2=256-pointdef[v].z;
			x2=x2<0?0:x2>255?255>>scale:x2>>scale;
			y2=y2<0?0:y2>255?255>>scale:y2>>scale;

			while (--sectionCount!=0)
			{
				SLong x1,y1;
				x1=x2;
				y1=y2;
				v=*pdata++;
				x2=pointdef[v].x;
				y2=256-pointdef[v].z;
				x2=x2<0?0:x2>255?255>>scale:x2>>scale;
				y2=y2<0?0:y2>255?255>>scale:y2>>scale;
				DDSymLine(prsd,x1,y1,x2,y2);
			}
		}
	}

	//check for shadow rendering to this tile
	if (scale<2 && Save_Data.detail_3d[DETAIL3D_ITEMSHADOWS])
	{
		//currentShadowRec contains world coordinates for sector search
		item dummyItem,*itemPtr;
		UWord sec_x,sec_y;
		dummyItem.World.X=currentShadowRec.world_x+(Grid_Width>>1);
		dummyItem.World.Z=currentShadowRec.world_z+(Grid_Width>>1);
		worldPtr->getsectornos(&dummyItem,sec_x,sec_y);
		ULong sec_index=worldPtr->makeindex(sec_x,sec_y);
		itemPtr=worldPtr->getfirstitem(sec_index);
		while (itemPtr)
		{
			const SLong gridSx=currentShadowRec.world_x;
			const SLong gridSz=currentShadowRec.world_z;
			const SLong gridEx=gridSx+Grid_Width;
			const SLong gridEz=gridSz+Grid_Width;
			const SLong world2Pix=9;	//+scale;

		 	if (itemPtr->Status.size<=RotatedSize)
			{
				ShapeDescPtr shapePtr=SHAPESTUFF.GetShapePtr(itemPtr->shape);

				if (SHAPESTUFF.GetShapeScale(shapePtr)==SHP_GRP)
				{
					if (groupHasShadow(itemPtr->shape))
					{
						UByte* inst_ptr=(UByte*)shapePtr+shapePtr->liveshpref;

						for (SWord inst=*inst_ptr++;inst==dogroupno;inst=*inst_ptr++)
						{
							DOGROUP_PTR gptr=(DOGROUP_PTR)inst_ptr;

							SLong cx=itemPtr->World.X+gptr->xoffset;
							SLong cz=itemPtr->World.Z+gptr->zoffset;

							if (cx>gridSx && cx<gridEx && cz>gridSz && cz<gridEz && shapeHasShadow((ShapeNum)gptr->shapenum))
							{
								SWord hdg=gptr->angle;
								cx=(cx-gridSx)>>world2Pix;
								cz=(cz-gridSz)>>world2Pix;

								ShapeDescPtr groupPtr=SHAPESTUFF.GetShapePtr((ShapeNum)gptr->shapenum);

								if (hdg==0)	RenderShadow(prsd,groupPtr,cx,cz,scale);
								else   		RenderShadowRotated(prsd,groupPtr,cx,cz,hdg,scale);
							}
							inst_ptr+=sizeof(DOGROUP);
						}
					}
				}
				else if (	itemPtr->World.X>gridSx &&
							itemPtr->World.X<gridEx &&
							itemPtr->World.Z>gridSz &&
							itemPtr->World.Z<gridEz &&
							shapeHasShadow(itemPtr->shape))
				{
					SWord hdg;
					SLong tx,tz;
					hdg=itemPtr->Status.size<HdgSize?0:((hdgitem*)itemPtr)->hdg;

					tx=(itemPtr->World.X-gridSx)>>world2Pix;
					tz=(itemPtr->World.Z-gridSz)>>world2Pix;
					if (hdg==0)	RenderShadow(prsd,shapePtr,tx,tz,scale);
					else		RenderShadowRotated(prsd,shapePtr,tx,tz,hdg,scale);
				}
			}
			itemPtr=itemPtr->Next;
		}
	}
}

void DoRenderTileToRowanSurface(UByte* pTileData,const HTEXT& hTexture)
{
	//Select correct Rowan surface from hTexture
	ROWANSURFACEDESC* rsd;
	ULong ht=hTexture();
	if (ht<SOFT_256_TEXTURES)
		rsd=sysram256maps[ht];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES)
		rsd=sysram128maps[ht-SOFT_256_TEXTURES];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES)
		rsd=sysram64maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES)
		rsd=sysram32maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES+SOFT_16_TEXTURES)
		rsd=sysram16maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES-SOFT_32_TEXTURES];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES+SOFT_16_TEXTURES+SOFT_8_TEXTURES)
		rsd=sysram8maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES-SOFT_32_TEXTURES-SOFT_16_TEXTURES];
	else 
		assert(false&&"Bad Texture handle");
	Three_Dee.pTMake->RenderTile2Surface(pTileData,rsd);
}

ROWANSURFACEDESC* GetRSD(const HTEXT& hTexture)
{
	ROWANSURFACEDESC* rsd;
	ULong ht=hTexture();
	if (ht<SOFT_256_TEXTURES)
		rsd=sysram256maps[ht];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES)
		rsd=sysram128maps[ht-SOFT_256_TEXTURES];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES)
		rsd=sysram64maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES)
		rsd=sysram32maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES+SOFT_16_TEXTURES)
		rsd=sysram16maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES-SOFT_32_TEXTURES];
	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES+SOFT_16_TEXTURES+SOFT_8_TEXTURES)
		rsd=sysram8maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES-SOFT_32_TEXTURES-SOFT_16_TEXTURES];
	else assert(false&&"Bad Texture handle");
	return rsd;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Render2Surface
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void Render2Surface(const HTEXT& hTexture,UByte rezTexture,UWord offset)
{
	SLong dgi=MakeDataGridIndex(offset);
	UByte* pdata=Three_Dee.pMigLand->MakeIData(gridRecords[dgi],rezTexture>>1);
	currentShadowRec=shadowRecords[dgi];
	if (!Save_Data.fSoftware) win->DoRenderTileToDDSurface(pdata,hTexture);
	else DoRenderTileToRowanSurface(pdata,hTexture);
}

bool CheckCache()
{
	for (int i=DataGridSizeMIN*DataGridSizeMIN-1;i>=0;i--)
	{
		AltPointsHdr *aph=(AltPointsHdr*)gridRecords[i].pData;
		if (!aph->CheckChecksum())
			return false;
	}
	return true;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void GetMinMaxAlt(const SLong x,const SLong z,const SWord dir,SLong& min,SLong& max)
{
	SLong dataGridSize=DataGridSizeMIN;
	SLong ix=(x&Grid_Mask)-gridRecordBase_x;
	SLong iz=(z&Grid_Mask)-gridRecordBase_z;
	ix/=Grid_Width;
	iz/=Grid_Width;

	DataRecord* dr=&gridRecords[(iz*dataGridSize)+ix];
	AltPointsHdr* aph=(AltPointsHdr*)dr->pData;

	min=aph->minAlt;
	max=aph->maxAlt;

	if (dir==0)			iz++;
	else if (dir==1)	ix++;
	else if (dir==2)	iz--;
	else if (dir==3)	ix--;

	dr=&gridRecords[(iz*dataGridSize)+ix];
	aph=(AltPointsHdr*)dr->pData;

	if (aph->minAlt<min) min=aph->minAlt;
	if (aph->maxAlt>max) max=aph->maxAlt;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void GetMinMaxAlt(const SLong x,const SLong z,SLong& min,SLong& max)
{
//	SLong dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?DataGridSizeMAX:DataGridSizeMIN;
	SLong dataGridSize=DataGridSizeMIN;
	SLong ix=(x&Grid_Mask)-gridRecordBase_x;
	SLong iz=(z&Grid_Mask)-gridRecordBase_z;
	ix/=Grid_Width;
	iz/=Grid_Width;
	if (ix<0 || iz<0 || ix>=dataGridSize || iz>=dataGridSize)
	{
		min=0;
		max=257000/_altitudeScale;
	}
	else
	{
		DataRecord* dr=&gridRecords[(iz*dataGridSize)+ix];
		AltPointsHdr* aph=(AltPointsHdr*)dr->pData;
		min=aph->minAlt;
		max=aph->maxAlt;
	}
}

}

using namespace TileMake;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Init
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------

void TMake::Reinit(const SLong x,const SLong z,Window* w) const
{
	win=w;
	ClearRecords(UByte(0));
	SetLandBaseDetail(0);
	InitGridRecords(x,z);
	SetInitialLandTextureCoordinates(x,z);
}

void TMake::Init(const SLong x,const SLong z,Window* w) const
{
	OverLay.LoaderScreen((1<<8)+96);
	win=w;
	SetTexturePointers(!Save_Data.fSoftware);
	OverLay.LoaderScreen((1<<8)+128);
	ClearRecords(UByte(0));
	SetLandBaseDetail(0);
	OverLay.LoaderScreen((1<<8)+128+32);
	InitGridRecords(x,z);
	OverLay.LoaderScreen((1<<8)+128+64);
	SetInitialLandTextureCoordinates(x,z);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Exit
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
void TMake::Exit() const
{
	ClearTexturePointers();
	win=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChkUpdate
//Author		Paul.   
//Date			Mon 20 Jul 1998
//------------------------------------------------------------------------------
void TMake::ChkUpdate(const SLong x,const SLong z) const
{
	GetPalLookup();
	UpdateGridRecords(x,z);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildShadowList
//Author		Paul.   
//Date			Thu 22 Oct 1998
//------------------------------------------------------------------------------
void TMake::BuildShadowList(WorldStuff *worldPtr,itemptr itemp)
{
	TileMake::BuildShadowList(worldPtr,itemp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBlock
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
DataRecord TMake::GetBlock(const SLong x,const SLong z) const
{
	return TileMake::GetBlock(x,z);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSquares
//Author		Paul.   
//Date			Wed 22 Jul 1998
//
//Description	Debug code that returns a series of boxes showing the area
//				of the view covered by each texture map level
//
//------------------------------------------------------------------------------
void TMake::GetSquares(Rect* squares) const
{
	TileMake::GetSquares(squares);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetClipRegion
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void TMake::GetClipRegion(const UByte index,Rect& clip) const
{
	TileMake::GetClipRegion(index,clip);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTileClipData
//Author		Paul.   
//Date			Thu 30 Jul 1998
//------------------------------------------------------------------------------
void TMake::GetTileClipData(SquareClips*& psc)
{
	TileMake::GetTileClipData(psc);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TMake
//Author		Paul.   
//Date			Thu 6 Aug 1998
//------------------------------------------------------------------------------
TMake::TMake()
{
	PrepareNoiseFn();
	AllocateBuffers();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TMake
//Author		Paul.   
//Date			Tue 6 Oct 1998
//------------------------------------------------------------------------------
TMake::~TMake()
{
 	ReleaseBuffers();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTile2Surface
//Author		Paul.   
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
void TMake::RenderTile2Surface(UByte* pdata,ROWANSURFACEDESC* prsd)
{
	TileMake::RenderTile2Surface(pdata,prsd);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Render2Surface
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void TMake::Render2Surface(const HTEXT& hTexture,UByte rezTexture,UWord offset)
{
	TileMake::Render2Surface(hTexture,rezTexture,offset);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void TMake::GetMinMaxAlt(const SLong x,const SLong z,SLong& min,SLong& max)
{
	TileMake::GetMinMaxAlt(x,z,min,max);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void TMake::GetMinMaxAlt(const SLong x,const SLong z,const SWord dir,SLong& min,SLong& max)
{
	TileMake::GetMinMaxAlt(x,z,dir,min,max);
}

void TMake::DoGetTextureScales(SLong& num256,SLong& num128,SLong& num64,SLong& num32,SLong& num16,SLong& num8)
{
	TileMake::DoGetTextureScales(num256,num128,num64,num32,num16,num8);
}

ROWANSURFACEDESC* TMake::GetRSD(const HTEXT& ht) const
{
	return TileMake::GetRSD(ht);
}

void TMake::DoFreeTextures()
{
	TileMake::DoFreeTextures();
}

void TMake::DoFreeTexture(const HTEXT& ht) const
{
	TileMake::DoFreeTexture(ht);
}

HTEXT TMake::DoAllocateTexture(UByte textRez)
{
	return TileMake::DoAllocateTexture(textRez);
}

bool TMake::CheckCache()
{
	return TileMake::CheckCache();
}
