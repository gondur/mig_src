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
//Filename       migland.cpp
//System         
//Author         Paul.   
//Date           Tue 2 Dec 1997
//Description    
//------------------------------------------------------------------------------

#include	<stdio.h>
#include	<windows.h>
#include	"math.h"
//DeadCode PD 13Aug99 #include	"c:\program files\devstudio\vc\include\math.h"
#define		F_GRAFIX
#define		F_SOUNDS
#define		F_BATTLE
#include	"dosdefs.h"
#include	"fileman.h"
#include	"hardpasm.h"
#include	"mathasm.h"
#include	"mymath.h"
#include	"display.h"
#include	"AreaType.h"
//#include	"landscap.h"

#include "prof.h"

#ifndef 	IN_MIGLAND_CPP
	#define		IN_MIGLAND_CPP	0
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DebugPrintBlock
//Author		Paul.   
//Date			Thu 17 Dec 1998
//------------------------------------------------------------------------------
void DebugPrintBlock(SLong world_x,SLong world_z)
{
	UByte block[128];
	block[4]=UByte(0);
	SLong xof=(world_x&0x1FFFFF)>>10;	//0..2048
	SLong val=world_x>>(17+4);
	block[2]=UByte(val&0x7)+'1';		//x (lo)
	val>>=3;
	block[0]=UByte(val)+'1';			//x (hi)
	SLong zof=2047-((world_z&0x1FFFFF)>>10);
	val=world_z>>(17+4);
	block[3]=UByte(val&0x7)+'1';		//z (lo)
	val>>=3;
	block[1]=UByte(val)+'1';			//z (hi)
	OutputDebugString((char*)block);	//print block number
	sprintf((char*)block,", xoff %d",xof);
	OutputDebugString((char*)block);
	sprintf((char*)block,", zoff %d\n",zof);
	OutputDebugString((char*)block);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		_northIndex
//Author		Paul.   
//Date			Wed 21 Oct 1998
//------------------------------------------------------------------------------
inline ULong _northIndex(SLong x,SLong z)
{
	return (0x3FF&z)*5+(0x7&(x>>7))-1;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		_southIndex
//Author		Paul.   
//Date			Wed 21 Oct 1998
//------------------------------------------------------------------------------
//DEAD inline ULong _southIndex(SLong x,SLong z)
//DEAD{
//DEAD	return (0x3FF-(0x3FF&z))*5+(0x7&(x>>7))-1;
//DEAD}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		_eastIndex
//Author		Paul.   
//Date			Wed 21 Oct 1998
//------------------------------------------------------------------------------
inline ULong _eastIndex(SLong x,SLong z)
{
	SLong real_x=(x&~0x7F)+(0x7F-(x&0x7F));
	return ((real_x&0x3FF)-0x80)*8+((z>>7)&7);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		_westIndex
//Author		Paul.   
//Date			Wed 21 Oct 1998
//------------------------------------------------------------------------------
//DEADinline ULong _westIndex(SLong x,SLong z)
//DEAD{
//DEAD	SLong real_x=(x&~0x7F)+(0x7F-(x&0x7F));
//DEAD 	return ((0x3FF-(real_x&0x3FF))-0x100)*8+((z>>7)&7);
//DEAD}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

typedef class LSFileBlock
{
	void*			data;
	public:
	LSFileBlock(	FileNum myfile,
					SLong length=0x1000,
					SLong offset=0,
					Bool skipread=TRUE)
	{data=FILEMAN.loadCDfile(myfile,length,offset,skipread);}
	~LSFileBlock()
	{if (data!=NULL) /*delete[] ((unsigned char*)data);*/data=NULL;}
	void *GetData()	{return (data);}
}
*LSFileBlockPtr;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

#include	"MigLand.h"

//static _timerData iblocktimer;
//static ULong iblockcounter=0;

//************ DEBUG CODE HERE !!!!!!!!!!!!

//************ END OF DEBUG CODE !!!!!!!!!!!

#pragma auto_inline(off)

//#include "trimaker.cpp"
#include "jimtri.cpp"

const double PI = 22./7.;

///////////////////////////////////////////////////////////////////////////////
////																	   ////
//// CDataBlock Methods													   ////
////																	   ////
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Procedure    CDataBlock::CDataBlock
// Author       Paul
// Date         15/01/98
//-----------------------------------------------------------------------------
CDataBlock::CDataBlock(CCacheBlock* pCacheBlk,ULong dlen,UByte* pData)
{
	pCacheBlock=pCacheBlk;
	pCacheBlock->pData=this;
	dataLen=dlen;
	UByte*	pDataDest=&pDataStart;
	_asm {
	push	esi
	push	edi
	push	ecx
	mov		esi,pData;
    mov		edi,pDataDest;
    mov		ebx,dlen
    mov		ecx,4
    sub		ecx,edi
    and		ecx,3
    sub		ebx,ecx
    rep		movsb
    mov		ecx,ebx
    shr		ecx,2
    rep		movsd
    and		ebx,3
    mov		ecx,ebx
    rep		movsb
	pop		ecx
	pop		edi
	pop		esi
	}
}

//-----------------------------------------------------------------------------
// Procedure    CDataBlock::~CDataBlock
// Author       Paul
// Date         15/01/98
//-----------------------------------------------------------------------------
CDataBlock::~CDataBlock()
{
	//This objects destructor code is responsible for 
	//removing references to its self from the cache 
	//search tree

	CCacheBlock* pTmp = pCacheBlock;

	pCacheBlock = NULL;
	if (pTmp!=NULL)	pTmp->Remove();
}

//-----------------------------------------------------------------------------
// Procedure    new
// Author       Paul
// Date         14/01/98
//-----------------------------------------------------------------------------
#undef new
void* CDataBlock::operator new(size_t sz,ULong dataLen)
{
	assert(pAlloc!=NULL&&" data block allocator not initialised");
	return (void*)pAlloc->Alloc(dataLen+sz);
}
#define new DEBUG_NEW
///////////////////////////////////////////////////////////////////////////////
////																	   ////
//// CPrimaryDB Methods													   ////
////																	   ////
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Procedure    CPrimaryDB::CPrimaryDB
// Author       Paul
// Date         15/01/98
//-----------------------------------------------------------------------------
CPrimaryDB::CPrimaryDB(CPrimaryCB* pCacheBlk,ULong dlen,UByte* pData)
{
	pCacheBlock=pCacheBlk;
	pCacheBlock->pData=this;
	dataLen=dlen;
	UByte*	pDataDest=&pDataStart;
	_asm {
	push	esi
	push	edi
	push	ecx
	mov		esi,pData;
    mov		edi,pDataDest;
    mov		ebx,dlen
    mov		ecx,4
    sub		ecx,edi
    and		ecx,3
    sub		ebx,ecx
    rep		movsb
    mov		ecx,ebx
    shr		ecx,2
    rep		movsd
    and		ebx,3
    mov		ecx,ebx
    rep		movsb
	pop		ecx
	pop		edi
	pop		esi
	}
}

//-----------------------------------------------------------------------------
// Procedure    CPrimaryDB::~CPrimaryDB
// Author       Paul
// Date         15/01/98
//-----------------------------------------------------------------------------
CPrimaryDB::~CPrimaryDB()
{
	//This objects destructor code is responsible for 
	//removing references to its self from the cache 
	//search tree

	CPrimaryCB* pTmp = pCacheBlock;

	pCacheBlock = NULL;
	if (pTmp!=NULL)	pTmp->Remove();
}

//-----------------------------------------------------------------------------
// Procedure    new
// Author       Paul
// Date         14/01/98
//-----------------------------------------------------------------------------
#undef new
void* CPrimaryDB::operator new(size_t sz,ULong dataLen)
{
	assert(pAlloc!=NULL&&" data block allocator not initialised");
	return (void*)pAlloc->Alloc(dataLen+sz);
}
#define new DEBUG_NEW

ULong l1st,l2nd,l3rd,l4th;

///////////////////////////////////////////////////////////////////////////////
////																	   ////
//// CDecompressData Methods											   ////
////																	   ////
///////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		putline
//Author		Paul.   
//Date			Tue 9 Dec 1997
//------------------------------------------------------------------------------
void CDecompressData::putline(SLong sx,SLong sy,SLong ex,SLong ey,SLong colour)
{
}

//-----------------------------------------------------------------------------
// Procedure    CDecompressData::putpixel
// Author       Paul
// Date         09/12/97
//-----------------------------------------------------------------------------
void CDecompressData::putpixel(SLong col,SLong x,SLong y)
{
}

//const int _altitudeScale=50;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalculateNVecs
//Author		Paul.   
//Date			Wed 3 Jun 1998
//------------------------------------------------------------------------------
void CDecompressData::CalculateNVecs(	PointDef* pntArray,UByte* polyDesc,
										NormalList* nList)
{
	if (!lightShadingEnabled) return;

	int fanCnt=*polyDesc++;

	while (fanCnt--)
	{
		int triCnt=*polyDesc++;
		int v1=*polyDesc++;
		int v3=*polyDesc++;

		NormalList fanPointNormal;
		fanPointNormal.count=0;
		fanPointNormal.ni=
		fanPointNormal.nj=
		fanPointNormal.nk=0.;

		while (triCnt--)
		{
		 	int v2=v3;
			v3=*polyDesc++;

			struct fVec
			{
				Float i,j,k;
			}
			a,b,c;

			a.i=512.*Float(pntArray[v1].x);
			a.j=_altitudeScale*Float(pntArray[v1].alt);
			a.k=130560.-512.*Float(pntArray[v1].z);

			b.i=512.*Float(pntArray[v2].x);
			b.j=_altitudeScale*Float(pntArray[v2].alt);
			b.k=130560.-512.*Float(pntArray[v2].z);

			c.i=512.*Float(pntArray[v3].x);
			c.j=_altitudeScale*Float(pntArray[v3].alt);
			c.k=130560.-512.*Float(pntArray[v3].z);

			b.i-=a.i; b.j-=a.j; b.k-=a.k;
			c.i-=a.i; c.j-=a.j; c.k-=a.k;

			a.i=(b.j*c.k)-(b.k*c.j);
			a.j=(b.k*c.i)-(b.i*c.k);
			a.k=(b.i*c.j)-(b.j*c.i);

			Float mag=(a.i*a.i)+(a.j*a.j)+(a.k*a.k);
			_asm
			{
				fld mag;
				fsqrt;
				fstp mag;
			}
			if (mag!=0.)
			{
				a.i/=mag; a.j/=mag; a.k/=mag;

				//Add this normal vector to all points in
				//this polygon

				fanPointNormal.ni+=a.i;
				fanPointNormal.nj+=a.j;
				fanPointNormal.nk+=a.k;
				fanPointNormal.count++;

				nList[v2].ni+=a.i;
				nList[v2].nj+=a.j;
				nList[v2].nk+=a.k;
				nList[v2].count++;

				nList[v3].ni+=a.i;
				nList[v3].nj+=a.j;
				nList[v3].nk+=a.k;
				nList[v3].count++;
			}
		}
		if (fanPointNormal.count>1)
		{
			Float mag=	(fanPointNormal.ni*fanPointNormal.ni)+
						(fanPointNormal.nj*fanPointNormal.nj)+
						(fanPointNormal.nk*fanPointNormal.nk);
			_asm
			{
				fld mag;
				fsqrt;
				fstp mag;
			}
			fanPointNormal.ni/=mag;
			fanPointNormal.nj/=mag;
			fanPointNormal.nk/=mag;
		}
		nList[v1].ni+=fanPointNormal.ni;
		nList[v1].nj+=fanPointNormal.nj;
		nList[v1].nk+=fanPointNormal.nk;
		nList[v1].count++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CDecompressData
//Author		Paul.   
//Date			Thu 4 Dec 1997
//------------------------------------------------------------------------------
CDecompressData::CDecompressData()
{
	lightShadingEnabled=false;

	//Callback fn for triangle generation
	pGenTri=genTri2;

	static PointList plReset =
	{0,0,
	{NULLCON,NULLCON,NULLCON,NULLCON},
	0,
	NULLCON,NULLCON,0,
	{NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON}
	};

	static PointList plPoint0 =
	{0,0,
	{1,NULLCON,NULLCON,NULLCON},
	0,
	1,3,0,
	{NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON}
	};

	static PointList plPoint1 =
	{256,0,
	{2,NULLCON,NULLCON,NULLCON},
	0,
	2,0,0,
	{NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON}
	};

	static PointList plPoint2 =
	{256,256,
	{3,NULLCON,NULLCON,NULLCON},
	0,
	3,1,0,
	{NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON}
	};

	static PointList plPoint3 =
	{0,256,
	{0,NULLCON,NULLCON,NULLCON},
	0,
	0,2,0,
	{NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON,NULLCON}
	};

	pplReset = &plReset;
	pplPoint0 = &plPoint0;
	pplPoint1 = &plPoint1;
	pplPoint2 = &plPoint2;
	pplPoint3 = &plPoint3;

	pDataStart=new UByte[TEMP_DECOMP_BUFF_SIZE];
}

//-----------------------------------------------------------------------------
// Procedure    CDecompressData::~CDecompressData
// Author       Paul
// Date         15/01/98
//-----------------------------------------------------------------------------
CDecompressData::~CDecompressData()
{
	delete [] pDataStart;
}

void CDecompressData::FakePointsLinesPolys(UByte*& inptr,UWord result)
{
	Max_Points=4;
	topEdgeCnt=rightEdgeCnt=bottomEdgeCnt=leftEdgeCnt=0;
	lowestAlt=highestAlt=0;
	*PolyPtr++=JOIN_POLY_NEXT;
	*PolyPtr++=UByte(result);
	*PolyPtr++=3;
	*PolyPtr++=0;
	*PolyPtr++=1;
	*PolyPtr++=2;
	*PolyPtr++=3;
	*PolyPtr++=JOIN_ROAD_NEXT;
	*LinePtr++=JOIN_POLY_NEXT;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnPack
//Author		Paul.   
//Date			Thu 4 Dec 1997
//------------------------------------------------------------------------------
void CDecompressData::UnPack(ULong x,ULong z,UByte*& ip,CDataBlock*& pDataBlk)
{
	UByte* inptr=ip;
	UByte LineBuff[1500];
	UByte PolyBuff[1500];
	PolyStream=PolyPtr=PolyBuff;
	LineStream=LinePtr=LineBuff;

	lowestAlt=0x7FFFFFFF;
	highestAlt=0;

	UWord result=FindEdgePoints(inptr);

	if (result&0x8000)	FakePointsLinesPolys(inptr,result);
	else				FindPointsLinesPolys(inptr);

	//Light shading stuff
	MakeIntermediateData();

	//Add the newly decompressed data to the cache
	//pDecompData is ptr to decompressed data
	//decompDataLen is length of the data

	CCacheBlock* pCacheBlk;
#undef new
	pCacheBlk = new CCacheBlock(x,z);
	pDataBlk = new(dataLen) CDataBlock(pCacheBlk,dataLen,pDataStart);
#define	new DEBUG_NEW
	pCacheBlk->Insert();

	ip=inptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DebugDumpIData
//Author		Paul.   
//Date			Wed 27 May 1998
//------------------------------------------------------------------------------
//DEBUG CODE!!!
SLong lastX,lastZ,lastRez;
//DEBUG CODE!!!
void CDecompressData::DebugDumpIData(void* pVData)
{
	FILE* debFile=fopen("deb.txt","wt");

	UByte* pData=UByteP(pVData);

// -------- Dump out some data to identify this tile ---------

	fprintf(debFile,"lastX: %d lastZ: %d lastRez: %d\n\n",lastX,lastZ,lastRez);

// -------- first we have the header ---------

	AltPointsHdr& aph=*(AltPointsHdr*)pData;

	fprintf(debFile,"struct AltPointsHdr\n");
	fprintf(debFile,"\tvertexCount: %d\n",aph.vertexCount);
	fprintf(debFile,"\ttopEdgePoints: %d\n",aph.topEdgePoints);
	fprintf(debFile,"\trightEdgePoints: %d\n",aph.rightEdgePoints);
	fprintf(debFile,"\tbottomEdgePoints: %d\n",aph.bottomEdgePoints);
	fprintf(debFile,"\tleftEdgePoints: %d\n",aph.leftEdgePoints);
	fprintf(debFile,"\tedgePointsStart: %d\n",aph.edgePointsStart);
	fprintf(debFile,"\tedgeListStart: %d\n",aph.edgeListStart);
	fprintf(debFile,"\tpolyDataStart: %d\n",aph.polyDataStart);
	fprintf(debFile,"\tedgeCount: %d\n\n",aph.edgeCount);

// -------- followed by the point definitions ---------

	PointDef* ppd=(PointDef*)(pData+sizeof(AltPointsHdr));

	for (int i=0;i<aph.vertexCount;i++){
		PointDef& pd=ppd[i];

		fprintf(debFile,"struct PointDef\n");
		fprintf(debFile,"\tx: %d\n",pd.x);
		fprintf(debFile,"\tz: %d\n",pd.z);
		fprintf(debFile,"\talt: %d\n",pd.alt);
		fprintf(debFile,"\tshadeVal: %d\n\n",pd.shadeVal);
	}

// -------- followed by the edge definitions ---------

	pData=UByteP(&ppd[i]);
	EdgeDef* ped=(EdgeDef*)pData;
	for (i=0;i<aph.edgeCount;i++){
		EdgeDef& ed=ped[i];
		fprintf(debFile,"struct EdgeDef\n");
		fprintf(debFile,"\tstartPoint: %d\n",ed.startPoint);
		fprintf(debFile,"\tendPoint: %d\n",ed.endPoint);
		fprintf(debFile,"\tlength: %d\n",ed.length);
		fprintf(debFile,"\tnoOfPoints: %d\n",ed.noOfPoints);
		fprintf(debFile,"\tedgeOffset: %d\n",ed.edgeOffset);

		//dump the list of edge points for each edge

		UByte* pEdgePointList=UByteP(&aph)+aph.edgePointsStart;
		if (ed.noOfPoints!=0){
			UByte* ptr=pEdgePointList+ed.edgeOffset;
			fprintf(debFile,"Edge points: ");
			for (int j=0;j<ed.noOfPoints;j++)
				fprintf(debFile,"%d,",ptr[j]);
			fprintf(debFile,"\n");
		}
	}

// -------- followed by draw data header ---------

	pData=UByteP(&aph)+aph.polyDataStart;

	DrawDataHdr& ddh=*(DrawDataHdr*)pData;

	fprintf(debFile,"struct DrawDataHdr\n");
	fprintf(debFile,"\tnoOfPolys: %d\n",ddh.noOfPolys);
	fprintf(debFile,"\tnoOfLines: %d\n\n",ddh.noOfLines);

	pData+=sizeof(DrawDataHdr);

// -------- and finally, the draw information ---------

	fprintf(debFile,"Poly draw data\n");

	UByte* pDrw=pData;

	for (i=0;i<ddh.noOfPolys;i++){
		fprintf(debFile,"Colour: %d ",*pDrw++);
		int edges=*pDrw++;
		fprintf(debFile,"Edges: %d EdgeList: ",edges);
		for (int j=0;j<edges;j++){
		 	fprintf(debFile,"%d ",*pDrw++);
		}
		fprintf(debFile,"DirList: ");
		for (j=0;j<edges;j++){
			if (BITTEST(pDrw,j))	fprintf(debFile,"b");
			else					fprintf(debFile,"f");
		}
		fprintf(debFile,"\n");
		pDrw+=(edges+7)>>3;
	}

	fclose(debFile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeIntData
//Author		Paul.   
//Date			Tue 26 May 1998
//------------------------------------------------------------------------------
void CDecompressData::MakeIntData(	ULong x,ULong z,ULong rez,
									void* pData,
									CPrimaryDB*& pDataBlk)
{
	UnpackIntData((UByte*)pData,rez);

 	//Add the newly decompressed data to the cache
 	//pDecompData is ptr to decompressed data
 	//decompDataLen is length of the data
 
 	CPrimaryCB*	pCacheBlk;
#undef new
 	pCacheBlk = new CPrimaryCB(x,z,rez);
 	pDataBlk = new(dataLen) CPrimaryDB(pCacheBlk,dataLen,pDataStart);
#define	new DEBUG_NEW
 	pCacheBlk->Insert();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindAltNType
//Author		Paul.   
//Date			Mon 8 Jun 1998
//------------------------------------------------------------------------------
void CDecompressData::FindAltNType(SLong x,SLong z,DataRecord& dr,
									SLong& alt,UByte& type)
{
	UByte* pDataStream=UByteP(dr.pData);

	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;

	pDataStream+=sizeof(AltPointsHdr);

	PointDef* pntArray=(PointDef*)pDataStream;

	//quick check to see if it's worth doing the remaining
	//tests

	alt-=FT_500;
	if (alt<0)	alt=0;
	else		alt/=_altitudeScale;

	for (SLong i=0;i<aph.vertexCount;i++)
		if (pntArray[i].alt>=UWord(alt))
			break;

	if (i==aph.vertexCount)
	{
		alt=pntArray[0].alt;
		for (SLong i=1;i<aph.vertexCount;i++)						  //MS 29/04/99
			if (pntArray[i].alt>alt)
				alt=pntArray[i].alt;
		alt*=_altitudeScale;
		return;
	}

	pDataStream+=sizeof(PointDef)*aph.vertexCount;

	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;

	pDataStream+=sizeof(DrawDataHdr);

	int polyCnt=ddh.noOfPolys;

	while (polyCnt--)
	{
		type=*pDataStream++;
	 	int fanCount=*pDataStream++;
		while (fanCount--)
		{
			int triCnt=*pDataStream++;
			int v1=*pDataStream++;
			int v3=*pDataStream++;
			while (triCnt--)
			{
				int v2=v3;
				v3=*pDataStream++;

				//test to see if the point we're interested in is inside
				//this triangle
				PointDef& p1=pntArray[v1];
				PointDef& p2=pntArray[v2];
				PointDef& p3=pntArray[v3];

				ULong minX,maxX;
				minMax(p1.x,p2.x,p3.x,minX,maxX);
				minX<<=9;
				maxX<<=9;

				if (x>=minX&&x<=maxX)
				{
					ULong minZ,maxZ;
					minMax(p1.z,p2.z,p3.z,minZ,maxZ);
					minZ<<=9;
					maxZ<<=9;

					if (z>=minZ&&z<=maxZ)
					{
						bool pointIn=HitTest(x,z,p1,p2,p3,alt);
						if (pointIn){
							if (Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS]&&
								IsForest(type))
								alt+=TREE_HEIGHT;
							else if (alt==0) alt=1;
							return;
						}
					}
				}
			}
		}
	}
	alt=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindRoughAlt
//Author		Paul.   
//Date			Wed 3 Mar 1999
//------------------------------------------------------------------------------
void CDecompressData::FindRoughAlt(SLong x,SLong y,SLong z,DataRecord& dr,SLong& alt)
{
	const SCALED_FT_2000=FT_2000/_altitudeScale;
	UByte* pDataStream=UByteP(dr.pData);
	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pntArray=(PointDef*)pDataStream;
	y/=_altitudeScale;
	alt=0;
	for (SLong i=0;i<aph.vertexCount;i++)
	{
		if (pntArray[i].alt>=UWord(alt))
		{
			alt=pntArray[i].alt;
		 	if (alt+SCALED_FT_2000<y) break;
		}
	}
	alt*=_altitudeScale;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HitTest
//Author		Paul.   
//Date			Mon 8 Jun 1998
//------------------------------------------------------------------------------
bool CDecompressData::HitTest(	SLong x,SLong z,
								PointDef& p1,PointDef& p2,PointDef& p3,
								SLong& alt)
{
	if ((ULong(p1.x)<<9)==x&&(ULong(p1.z)<<9)==z){
		alt=_altitudeScale*p1.alt;
		return true;
	}
	else if ((ULong(p2.x)<<9)==x&&(ULong(p2.z)<<9)==z){
		alt=_altitudeScale*p2.alt;
		return true;
	}
	else if ((ULong(p3.x)<<9)==x&&(ULong(p3.z)<<9)==z){
		alt=_altitudeScale*p3.alt;
		return true;
	}

	PointDef* pnt[3];

	pnt[0]=&p1;
	pnt[1]=&p2;
	pnt[2]=&p3;

	for (int i=0;i<3;i++){
		UWord val=PointInTriangle(x,z,*pnt[i],*pnt[(i+1)%3],*pnt[(i+2)%3],alt);
		if (val==0)	return false;
		else if (val==1)  return true;
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PointInTriangle
//Author		Paul.   
//Date			Mon 8 Jun 1998
//returns		1=got alt
//				0=missed triangle
//				0xFFFF = failed so try again
//------------------------------------------------------------------------------
UWord CDecompressData::PointInTriangle(	SLong x,SLong z,
										PointDef& p1,PointDef& p2,PointDef& p3,
										SLong& alt)
{
	const Float ABIT=.00000001;
	const Float ONE_PLUS_A_BIT=1.+ABIT;
	const Float ZERO_MINUS_A_BIT=0.-ABIT;

	struct fPnt{Float x,z,alt;};

	fPnt fp1,fp2,fp3,fpTest;

	fp1.x=Float(ULong(p1.x)<<9); fp1.z=Float(ULong(p1.z)<<9); fp1.alt=Float(p1.alt);
	fp2.x=Float(ULong(p2.x)<<9); fp2.z=Float(ULong(p2.z)<<9); fp2.alt=Float(p2.alt);
	fp3.x=Float(ULong(p3.x)<<9); fp3.z=Float(ULong(p3.z)<<9); fp3.alt=Float(p3.alt);

	fpTest.x=Float(x); fpTest.z=Float(z);

	fPnt a,b,q;

	a.x=fp3.x-fp1.x;
	a.z=fp3.z-fp1.z;
	a.alt=fp3.alt-fp1.alt;

	b.x=fp2.x-fp1.x;
	b.z=fp2.z-fp1.z;
	b.alt=fp2.alt-fp1.alt;

	if (a.z==0. || b.z==0. || (a.x*b.z==b.x*a.z)) return UWord(0xFFFF);

	q.x=fpTest.x-fp1.x;
	q.z=fpTest.z-fp1.z;

	Float u,v;

	if (a.z!=0.){
		v=(q.x*a.z-q.z*a.x)/(b.x*a.z-b.z*a.x);
		u=(q.z-v*b.z)/a.z;
	}
	else{
		u=(q.x*b.z-q.z*b.x)/(a.x*b.z-b.x*a.z);
		v=(q.z-u*a.z)/b.z;
	}

	//the point is inside the triangle if the following 3 conditions
	//are satisfied...

	//	0 <= u <= 1
	//	0 <= v <= 1
	//	u + v <= 1

	if (u<ZERO_MINUS_A_BIT||u>ONE_PLUS_A_BIT) return UWord(0);	//missed
	if (v<ZERO_MINUS_A_BIT||v>ONE_PLUS_A_BIT) return UWord(0);	//missed

	if (u+v>ONE_PLUS_A_BIT) return UWord(0);	//missed

	//the point is inside the triangle so calculate the
	//correct altitude

	q.alt=u*a.alt+v*b.alt;

	fpTest.alt=q.alt+fp1.alt;

	alt=SLong(_altitudeScale*fpTest.alt);

	return UWord(1);	//hit
}	

//-----------------------------------------------------------------------------
// Procedure    CDecompressData::Skip
// Author       Paul
// Date         09/12/97
//-----------------------------------------------------------------------------
void CDecompressData::Skip(UByte*& ip,ULong blkCnt)
{
	UByte* inptr=ip;
	while(blkCnt--)
	{
		UWord result=SkipEdgePoints(inptr);
		if (result==1)		skipToNextFFFF(inptr);
		else if (result==0)	SkipPointsLinesPolys(inptr);
		//if result==2 then nothing else needs to be done
	}
	ip=inptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyData
//Author		Paul.   
//------------------------------------------------------------------------------
void CDecompressData::CopyData(UByte*& ip,UByte* pdst)
{
	UByte* inptr=ip;
	//copy a single block of compressed data from 'inptr' to 'pdst'

	UWord result=copyHeader(inptr,pdst);
	if (result==1)		copyToNextFFFF(inptr,pdst);
	else if(result==0)	copyBody(inptr,pdst);
	//if result == 2 then the data has already been coppied
	ip=inptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		copyToNextFFFF
//Author		Paul.   
//------------------------------------------------------------------------------
void CDecompressData::copyToNextFFFF(UByte*& ip,UByte* pdst)
{
	UByte* inptr=ip;
	while (*(UWord*)inptr!=UWord(0xFFFF)) *pdst++=*inptr++;
	*(UWord*)pdst=UWord(0xFFFF);
	inptr+=2;
	ip=inptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		skipToNextFFFF
//Author		Paul    
//------------------------------------------------------------------------------
void CDecompressData::skipToNextFFFF(UByte*& ip)
{
	UByte* inptr=ip;
	while (*(UWord*)inptr!=UWord(0xFFFF)) inptr++;
	inptr+=2;
	ip=inptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SkipEdgePoints
//Author		Paul.   
//Date			Fri 26 Jun 1998
//Returns		0 - use slower scan of the data to get past this blocks data
//				1 - use skip to next FFFF to get past this blocks data
//				2 - special tile (already skipped the data)
//------------------------------------------------------------------------------
UWord CDecompressData::SkipEdgePoints(UByte*& ip)
{
	UByte* inptr=ip;
	UByte	tmp[5];

	pointdec[0]=*pplPoint0;
	pointdec[1]=*pplPoint1;
	pointdec[2]=*pplPoint2;
	pointdec[3]=*pplPoint3;

	for (int i=4;i<256;pointdec[i++]=*pplReset);

	Max_Points=4;

	UByte*	b0=tmp;
	tmp[0]=*inptr++;
	tmp[1]=*inptr++;
	tmp[2]=*inptr++;
	tmp[3]=*inptr++;
	if (tmp[0]==0xFF && tmp[1]==0xFF && tmp[3]==0xFF)	
	{
		//special case compressed tile 'tmp[2]' contains the tile coloue
		ip=inptr;
		return UWord(2);	//skip done
	}
	tmp[4]=*inptr++;

	//test to see if altitude data is present...
	altData=NO_ALT;
	if (tmp[0]&0x80)
	{
		tmp[0]&=0x7F;
		//this means that some extra bytes follow..

		UByte x0=*inptr++;
		UByte x1=*inptr++;

		if (x0==0xFF && x1==0xFF)
		{
			altData=WORD_ALT;
			inptr+=12;
			ip=inptr;
			return UWord(1);		//true;		//FASTER SKIP!!
		}
		else
		{
			altData=BYTE_ALT;
			inptr+=4;
		}
	}
	int pts=*b0++;
	int upf=0;
	pointdec[upf].unpairedfrom[0]=1;
	if (pts)

	do{
		if (altData==NO_ALT)		inptr++;
		else if (altData==BYTE_ALT)	inptr+=2;
		else if (altData==WORD_ALT)	inptr+=4;

		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=1;
		pointdec[Max_Points].lastto=upf;
		pointdec[upf].lastfrom=
			pointdec[upf].unpairedfrom[0]=
				Max_Points;
		pointdec[1].lastto=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,1);

	pts=*b0++;
	upf=1;
	pointdec[upf].unpairedfrom[0]=2;
	if (pts)
	do{
		if (altData==NO_ALT)		inptr++;
		else if (altData==BYTE_ALT)	inptr+=2;
		else if (altData==WORD_ALT)	inptr+=4;

		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=2;
		pointdec[Max_Points].lastto=upf;
		pointdec[upf].lastfrom=
			pointdec[upf].unpairedfrom[0]=Max_Points;
		pointdec[2].lastto=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,2);

	pts=*b0++;
	upf=3;
	pointdec[2].unpairedfrom[0]=(UByte)upf;
	if (pts)
	do{
		if (altData==NO_ALT)		inptr++;
		else if (altData==BYTE_ALT)	inptr+=2;
		else if (altData==WORD_ALT)	inptr+=4;

		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=(UByte)upf;
		pointdec[Max_Points].lastto=2;
		pointdec[upf].lastto=Max_Points;
		pointdec[2].lastfrom=
			pointdec[2].unpairedfrom[0]=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,2);

	pts=*b0++;
	upf=0;
	pointdec[3].unpairedfrom[0]=(UByte)upf;
	if (pts)
	do{
		if (altData==NO_ALT)		inptr++;
		else if (altData==BYTE_ALT)	inptr+=2;
		else if (altData==WORD_ALT)	inptr+=4;

		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=(UByte)upf;
		pointdec[Max_Points].lastto=3;
		pointdec[upf].lastto=Max_Points;
		pointdec[3].lastfrom=
			pointdec[3].unpairedfrom[0]=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,3);

	Highest_Point_Defined=Max_Points;
	pts=*b0++;
	if (pts)
	do{
			Max_Points++;
	}while (--pts!=0);

	ip=inptr;
	return UWord(0);	//false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		copyHeader
//Author		Paul.   
//Returns		0 - use slow copy
//				1 - use fast copy
//				2 - special tile (already coppied)
//------------------------------------------------------------------------------
UWord CDecompressData::copyHeader(UByte*& ip,UByte*& pdst)
{
	UByte* inptr=ip;
	UByte	tmp[5];

	pointdec[0]=*pplPoint0;
	pointdec[1]=*pplPoint1;
	pointdec[2]=*pplPoint2;
	pointdec[3]=*pplPoint3;

	for (int i=4;i<256;pointdec[i++]=*pplReset);

	Max_Points=4;

	UByte*	b0=tmp;
	*pdst++=tmp[0]=*inptr++;
	*pdst++=tmp[1]=*inptr++;
	*pdst++=tmp[2]=*inptr++;
	*pdst++=tmp[3]=*inptr++;

	if (tmp[0]==0xFF && tmp[1]==0xFF && tmp[3]==0xFF)	
	{
		//special case compressed tile 'tmp[2]' contains the tile coloue
		ip=inptr;
		return UWord(2);	//skip done
	}

	*pdst++=tmp[4]=*inptr++;

	//test to see if altitude data is present...
	altData=NO_ALT;
	if (tmp[0]&0x80)
	{
		tmp[0]&=0x7F;
		//this means that some extra bytes follow..

		*pdst++=*inptr;
		*pdst++=*(inptr+1);

		if ((((*inptr++)<<8)+*inptr++)==0xFFFF)
		{
			altData=WORD_ALT;
			memcpy(pdst,inptr,12);
			pdst+=12;
			inptr+=12;
			ip=inptr;
			return UWord(1);	//true;		//FASTER SKIP!!
		}
		else
		{
			altData=BYTE_ALT;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
		}
	}
	int pts=*b0++;
	int upf=0;
	pointdec[upf].unpairedfrom[0]=1;
	if (pts)

	do{
		if (altData==NO_ALT)
		{
			*pdst++=*inptr++;
		}
		else if (altData==BYTE_ALT)
		{
			*pdst++=*inptr++;
			*pdst++=*inptr++;
		}
		else if (altData==WORD_ALT)
		{
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
		}
		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=1;
		pointdec[Max_Points].lastto=upf;
		pointdec[upf].lastfrom=
			pointdec[upf].unpairedfrom[0]=
				Max_Points;
		pointdec[1].lastto=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,1);

	pts=*b0++;
	upf=1;
	pointdec[upf].unpairedfrom[0]=2;
	if (pts)
	do{
		if (altData==NO_ALT)
		{
			*pdst++=*inptr++;
		}
		else if (altData==BYTE_ALT)
		{
			*pdst++=*inptr++;
			*pdst++=*inptr++;
		}
		else if (altData==WORD_ALT)
		{
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
		}
		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=2;
		pointdec[Max_Points].lastto=upf;
		pointdec[upf].lastfrom=
			pointdec[upf].unpairedfrom[0]=Max_Points;
		pointdec[2].lastto=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,2);

	pts=*b0++;
	upf=3;
	pointdec[2].unpairedfrom[0]=(UByte)upf;
	if (pts)
	do{
		if (altData==NO_ALT)
		{
			*pdst++=*inptr++;
		}
		else if (altData==BYTE_ALT)
		{
			*pdst++=*inptr++;
			*pdst++=*inptr++;
		}
		else if (altData==WORD_ALT)
		{
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
		}
		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=(UByte)upf;
		pointdec[Max_Points].lastto=2;
		pointdec[upf].lastto=Max_Points;
		pointdec[2].lastfrom=
			pointdec[2].unpairedfrom[0]=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,2);

	pts=*b0++;
	upf=0;
	pointdec[3].unpairedfrom[0]=(UByte)upf;
	if (pts)
	do{
		if (altData==NO_ALT)
		{
			*pdst++=*inptr++;
		}
		else if (altData==BYTE_ALT)
		{
			*pdst++=*inptr++;
			*pdst++=*inptr++;
		}
		else if (altData==WORD_ALT)
		{
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
			*pdst++=*inptr++;
		}
		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=(UByte)upf;
		pointdec[Max_Points].lastto=3;
		pointdec[upf].lastto=Max_Points;
		pointdec[3].lastfrom=
			pointdec[3].unpairedfrom[0]=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,3);

	Highest_Point_Defined=Max_Points;
	pts=*b0++;
	if (pts)
	do{
			Max_Points++;
	}while (--pts!=0);

	ip=inptr;
	return UWord(0);	//false;
}


#define FAST_LAND "YES"
#include "decomp.cpp"
#undef FAST_LAND
#include "decomp.cpp"

void CDecompressData::FastSkipPLP(UByte*& inptr)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SkipPointsLinesPolys
//Author		Paul.   
//Date			Fri 26 Jun 1998
//------------------------------------------------------------------------------
void CDecompressData::SkipPointsLinesPolys(UByte*& ip)
{
	UByte* inptr=ip;
	int	coordslastpoint=0;
	UByte endcode=*inptr++;
	for (int point=0;point<Max_Points;point++)
		while (pointdec[point].lastto==NULLCON || pointdec[point].unpairedfrom[0]!=NULLCON)
			if (endcode==JOIN_POLY_NEXT)
			{
				inptr++;
				coordslastpoint=point;

				int curr=point;
				int last=NULLCON;
				if (pointdec[curr].unpairedfrom)
					endcode=pointdec[curr].unpairedfrom[0];
				else
					endcode=*inptr++;

				while (endcode<JOIN_ROAD_NEXT)
				{
					if (endcode==JOIN_FOLLOW_TO)
						endcode=(UByte)pointdec[curr].lastto;
					elseif (endcode==JOIN_FOLLOW_FROM)
						endcode=(UByte)pointdec[curr].lastfrom;
					elseif (endcode==JOIN_NEW_COORDS)
					{
						endcode=Highest_Point_Defined++;

						if (altData==NO_ALT)		inptr+=2;
						else if (altData==BYTE_ALT)	inptr+=3;
						else if (altData==WORD_ALT)	inptr+=5;
					}
					coordslastpoint=endcode;
					PointsConnected(curr,endcode);

					if (last!=NULLCON)
						pointdec[curr].lastfrom=last;
					pointdec[curr].lastto=endcode;
					for (int i=0;i<4;i++)
						if (pointdec[curr].unpairedfrom[i]==endcode)
						{
							for (int j=i+1;j<4;j++)
								breakif (pointdec[curr].unpairedfrom[j]==NULLCON);
							pointdec[curr].unpairedfrom[i]=pointdec[curr].unpairedfrom[j-1];
							pointdec[curr].unpairedfrom[j-1]=NULLCON;
							break;
						}
					if (i==4)
					{
						for (int i=0;i<4;i++)
							breakif (pointdec[endcode].unpairedfrom[i]==NULLCON);
						//assert i!=4;
						pointdec[endcode].unpairedfrom[i]=(UByte)curr;
					}
					last=curr;
					curr=endcode;
					endcode=*inptr++;	//CSB 10/11/98	FAILS HERE !!!!
				}
				PointsConnected(curr,point);
				pointdec[curr].lastfrom=last;
				pointdec[curr].lastto=point;
				pointdec[point].lastfrom=curr;
				for (int i=0;i<4;i++)
					if (pointdec[curr].unpairedfrom[i]==point)
					{
						for (int j=i+1;j<4;j++)
							breakif (pointdec[curr].unpairedfrom[j]==NULLCON);
						pointdec[curr].unpairedfrom[i]=pointdec[curr].unpairedfrom[j-1];
						pointdec[curr].unpairedfrom[j-1]=NULLCON;
						break;
					}
				if (i==4)
				{
					for (int i=0;i<4;i++)
						breakif (pointdec[point].unpairedfrom[i]==NULLCON);
					//assert i!=4;
					pointdec[point].unpairedfrom[i]=(UByte)curr;
				}

			}
			else
			{	//its a road
				inptr++;
				int curr=point;
				endcode=(UByte)point;
				coordslastpoint=endcode;


				if (pointdec[curr].unpairedfrom)
					endcode=pointdec[curr].unpairedfrom[0];
				else
					endcode=*inptr++;
				int last=NULLCON;
				while (endcode<JOIN_ROAD_NEXT)
				{
					if (endcode==JOIN_FOLLOW_TO)
						endcode=(UByte)pointdec[curr].lastto;
					elseif (endcode==JOIN_FOLLOW_FROM)
						endcode=(UByte)pointdec[curr].lastfrom;
					elseif (endcode==JOIN_NEW_COORDS)
					{
						endcode=Highest_Point_Defined++;
						if (altData==NO_ALT)		inptr+=2;
						else if (altData==BYTE_ALT)	inptr+=3;
						else if (altData==WORD_ALT)	inptr+=5;
					}
					PointsConnected(curr,endcode);
					coordslastpoint=endcode;

					if (last!=NULLCON)
						pointdec[curr].lastfrom=last;
					pointdec[curr].lastto=endcode;
					last=curr;
					curr=endcode;
					endcode=*inptr++;	//CSB 10/11/98		FAILS HERE !!!!
				}
			}
	coordslastpoint=0;
	//extra lines:
	while (endcode!=JOIN_POLY_NEXT)
	{
		inptr++;
		endcode=*inptr++;
		if (endcode==JOIN_NEW_COORDS)
		{
			endcode=Highest_Point_Defined++;

			if (altData==NO_ALT)		inptr+=2;
			else if (altData==BYTE_ALT)	inptr+=3;
			else if (altData==WORD_ALT)	inptr+=5;
		}
		point=endcode;
		coordslastpoint=endcode;
		endcode=*inptr++;
		int curr=point;
		int last=NULLCON;
		while (endcode<JOIN_ROAD_NEXT)
		{
			if (endcode==JOIN_FOLLOW_TO)
				endcode=(UByte)pointdec[curr].lastto;
			elseif (endcode==JOIN_FOLLOW_FROM)
				endcode=(UByte)pointdec[curr].lastfrom;
			elseif (endcode==JOIN_NEW_COORDS)
			{
				endcode=Highest_Point_Defined++;

				if (altData==NO_ALT)		inptr+=2;
				else if (altData==BYTE_ALT)	inptr+=3;
				else if (altData==WORD_ALT)	inptr+=5;
			}
			PointsConnected(curr,endcode);
			coordslastpoint=endcode;
			if (last!=NULLCON)
				pointdec[curr].lastfrom=last;
			pointdec[curr].lastto=endcode;
			last=curr;
			curr=endcode;
			endcode=*inptr++;
		}
	}
	if (altData==WORD_ALT) inptr++;
	ip=inptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		copyBody
//Author		Paul.   
//------------------------------------------------------------------------------
void CDecompressData::copyBody(UByte*& ip,UByte* pdst)
{
	UByte* inptr=ip;
	int	coordslastpoint=0;
	UByte endcode=*pdst++=*inptr++;
	for (int point=0;point<Max_Points;point++)
		while (pointdec[point].lastto==NULLCON || pointdec[point].unpairedfrom[0]!=NULLCON)
			if (endcode==JOIN_POLY_NEXT)
			{
				*pdst++=*inptr++;
				coordslastpoint=point;

				int curr=point;
				int last=NULLCON;
				if (pointdec[curr].unpairedfrom)
					endcode=pointdec[curr].unpairedfrom[0];
				else
					endcode=*pdst++=*inptr++;

				while (endcode<JOIN_ROAD_NEXT)
				{
					if (endcode==JOIN_FOLLOW_TO)
						endcode=(UByte)pointdec[curr].lastto;
					elseif (endcode==JOIN_FOLLOW_FROM)
						endcode=(UByte)pointdec[curr].lastfrom;
					elseif (endcode==JOIN_NEW_COORDS)
					{
						endcode=Highest_Point_Defined++;

						if (altData==NO_ALT)
						{
							*pdst++=*inptr++;
							*pdst++=*inptr++;
						}
						else if (altData==BYTE_ALT)
						{
							*pdst++=*inptr++;
							*pdst++=*inptr++;
							*pdst++=*inptr++;
						}
						else if (altData==WORD_ALT)
						{
							*pdst++=*inptr++;
							*pdst++=*inptr++;
							*pdst++=*inptr++;
							*pdst++=*inptr++;
							*pdst++=*inptr++;
						}
					}
					coordslastpoint=endcode;
					PointsConnected(curr,endcode);

					if (last!=NULLCON)
						pointdec[curr].lastfrom=last;
					pointdec[curr].lastto=endcode;
					for (int i=0;i<4;i++)
						if (pointdec[curr].unpairedfrom[i]==endcode)
						{
							for (int j=i+1;j<4;j++)
								breakif (pointdec[curr].unpairedfrom[j]==NULLCON);
							pointdec[curr].unpairedfrom[i]=pointdec[curr].unpairedfrom[j-1];
							pointdec[curr].unpairedfrom[j-1]=NULLCON;
							break;
						}
					if (i==4)
					{
						for (int i=0;i<4;i++)
							breakif (pointdec[endcode].unpairedfrom[i]==NULLCON);
						//assert i!=4;
						pointdec[endcode].unpairedfrom[i]=(UByte)curr;
					}
					last=curr;
					curr=endcode;
					endcode=*pdst++=*inptr++;
				}
				PointsConnected(curr,point);
				pointdec[curr].lastfrom=last;
				pointdec[curr].lastto=point;
				pointdec[point].lastfrom=curr;
				for (int i=0;i<4;i++)
					if (pointdec[curr].unpairedfrom[i]==point)
					{
						for (int j=i+1;j<4;j++)
							breakif (pointdec[curr].unpairedfrom[j]==NULLCON);
						pointdec[curr].unpairedfrom[i]=pointdec[curr].unpairedfrom[j-1];
						pointdec[curr].unpairedfrom[j-1]=NULLCON;
						break;
					}
				if (i==4)
				{
					for (int i=0;i<4;i++)
						breakif (pointdec[point].unpairedfrom[i]==NULLCON);
					//assert i!=4;
					pointdec[point].unpairedfrom[i]=(UByte)curr;
				}

			}
			else
			{	//its a road
				*pdst++=*inptr++;
				int curr=point;
				endcode=(UByte)point;
				coordslastpoint=endcode;


				if (pointdec[curr].unpairedfrom)
					endcode=pointdec[curr].unpairedfrom[0];
				else
					endcode=*pdst++=*inptr++;
				int last=NULLCON;
				while (endcode<JOIN_ROAD_NEXT)
				{
					if (endcode==JOIN_FOLLOW_TO)
						endcode=(UByte)pointdec[curr].lastto;
					elseif (endcode==JOIN_FOLLOW_FROM)
						endcode=(UByte)pointdec[curr].lastfrom;
					elseif (endcode==JOIN_NEW_COORDS)
					{
						endcode=Highest_Point_Defined++;
						if (altData==NO_ALT)
						{
							*pdst++=*inptr++;
							*pdst++=*inptr++;
						}
						else if (altData==BYTE_ALT)
						{
							*pdst++=*inptr++;
							*pdst++=*inptr++;
							*pdst++=*inptr++;
						}
						else if (altData==WORD_ALT)
						{
							*pdst++=*inptr++;
							*pdst++=*inptr++;
							*pdst++=*inptr++;
							*pdst++=*inptr++;
							*pdst++=*inptr++;
						}
					}
					PointsConnected(curr,endcode);
					coordslastpoint=endcode;

					if (last!=NULLCON)
						pointdec[curr].lastfrom=last;
					pointdec[curr].lastto=endcode;
					last=curr;
					curr=endcode;
					endcode=*pdst++=*inptr++;
				}
			}
	coordslastpoint=0;
	//extra lines:
	while (endcode!=JOIN_POLY_NEXT)
	{
		*pdst++=*inptr++;
		endcode=*pdst++=*inptr++;
		if (endcode==JOIN_NEW_COORDS)
		{
			endcode=Highest_Point_Defined++;

			if (altData==NO_ALT)
			{
				*pdst++=*inptr++;
				*pdst++=*inptr++;
			}
			else if (altData==BYTE_ALT)
			{
				*pdst++=*inptr++;
				*pdst++=*inptr++;
				*pdst++=*inptr++;
			}
			else if (altData==WORD_ALT)
			{
				*pdst++=*inptr++;
				*pdst++=*inptr++;
				*pdst++=*inptr++;
				*pdst++=*inptr++;
				*pdst++=*inptr++;
			}
		}
		point=endcode;
		coordslastpoint=endcode;
		endcode=*pdst++=*inptr++;
		int curr=point;
		int last=NULLCON;
		while (endcode<JOIN_ROAD_NEXT)
		{
			if (endcode==JOIN_FOLLOW_TO)
				endcode=(UByte)pointdec[curr].lastto;
			elseif (endcode==JOIN_FOLLOW_FROM)
				endcode=(UByte)pointdec[curr].lastfrom;
			elseif (endcode==JOIN_NEW_COORDS)
			{
				endcode=Highest_Point_Defined++;

				if (altData==NO_ALT)
				{
					*pdst++=*inptr++;
					*pdst++=*inptr++;
				}
				else if (altData==BYTE_ALT)
				{
					*pdst++=*inptr++;
					*pdst++=*inptr++;
					*pdst++=*inptr++;
				}
				else if (altData==WORD_ALT)
				{
					*pdst++=*inptr++;
					*pdst++=*inptr++;
					*pdst++=*inptr++;
					*pdst++=*inptr++;
					*pdst++=*inptr++;
				}
			}
			PointsConnected(curr,endcode);
			coordslastpoint=endcode;
			if (last!=NULLCON)
				pointdec[curr].lastfrom=last;
			pointdec[curr].lastto=endcode;
			last=curr;
			curr=endcode;
			endcode=*pdst++=*inptr++;
		}
	}
	if (altData==WORD_ALT) *pdst++=*inptr++;
	ip=inptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveStupids
//Author		Paul.   
//Date			Wed 18 Mar 1998
//------------------------------------------------------------------------------
inline void CDecompressData::RemoveStupids(UByte& pntCnt,UByte* orgPolyDesc)
{
	//strip out duplicate points...
	int i=0;
	while (i<pntCnt){
	 	int j=(i+1)%pntCnt;
		if (orgPolyDesc[i]==orgPolyDesc[j]){
		 	//remove this duplicate point
			pntCnt--;
			if (j!=0)
				for (int k=i+1;k<pntCnt;k++) orgPolyDesc[k]=orgPolyDesc[k+1];
		}
		else i++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildTreeList
//Author		Paul.   
//Date			Thu 13 Aug 1998
//------------------------------------------------------------------------------
SLong CDecompressData::BuildTreeList(UByte* psrc,PointDef* ppd,SmallPoint*& smp)
{
	SmallPoint* ppoints=smp;
	ULong ave;
	SLong tot=0;
	//to start with, just insert 1 tree per triangle in each fan
	UByte fanCnt=*psrc++;
	while (fanCnt--)
	{
		UByte triCnt=*psrc++;
		PointDef *pp0,*pp1,*pp2;
		pp0=ppd+*psrc++;
		pp2=ppd+*psrc++;
		while (triCnt--)
		{
			pp1=pp2;
			pp2=ppd+*psrc++;
			if (triCnt&1){
				ave=pp0->x+pp1->x+pp2->x; ave/=3;
				ppoints->x=UByte(ave);
				ave=pp0->z+pp1->z+pp2->z; ave/=3;
				ppoints->z=UByte(ave);
				ave=pp0->alt+pp1->alt+pp2->alt; ave/=3;
				ppoints->alt=UWord(ave);
				ppoints++;
				tot++;
			}
		}
	}
	smp=ppoints;
	return tot;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildWaveList
//Author		Paul.   
//Date			Tue 24 Nov 1998
//------------------------------------------------------------------------------
SLong CDecompressData::BuildWaveList(UByte* psrc,PointDef* ppd,SmallPoint*& smp)
{
	SmallPoint* ppoints=smp;
	ULong ave;
	SLong tot=0;
	//to start with, just insert 1 tree per triangle in each fan
	UByte fanCnt=*psrc++;
	while (fanCnt--)
	{
		UByte triCnt=*psrc++;
		PointDef *pp0,*pp1,*pp2;
		pp0=ppd+*psrc++;
		pp2=ppd+*psrc++;
		while (triCnt--)
		{
			pp1=pp2;
			pp2=ppd+*psrc++;
			if (triCnt&1){
				ave=pp0->x+pp1->x+pp2->x; ave/=3;
				ppoints->x=UByte(ave);
				ave=pp0->z+pp1->z+pp2->z; ave/=3;
				ppoints->z=UByte(ave);
				ave=pp0->alt+pp1->alt+pp2->alt; ave/=3;
				ppoints->alt=UWord(ave);
				ppoints++;
				tot++;
			}
		}
	}
	smp=ppoints;
	return tot;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnpackIntData
//Author		Paul.   
//Date			Thu 21 May 1998
//------------------------------------------------------------------------------
void CDecompressData::UnpackIntData(UByte* pSrc,ULong rez)
{

	SmallPoint ltl[128+32];
	SmallPoint* localTreeListPtr;
	localTreeListPtr=ltl;

	UByte* pDst=pDataStart;
	//Copy over the header & point definitions
	AltPointsHdr& aphSrc=*(AltPointsHdr*)pSrc;

	AltPointsHdr& aphDst=*(AltPointsHdr*)pDst;
	aphDst=aphSrc;

	UByte* pBase=pSrc;	//use this as a base for
						//the offsets stored in the source header

	pSrc+=sizeof(AltPointsHdr);
	pDst+=sizeof(AltPointsHdr);

	UByte* usageTbl=new UByte[256];
	memset(usageTbl,0,aphSrc.vertexCount);

	//Copy over the point definitions
	PointDef* ppdSrc=(PointDef*)pSrc;
	PointDef* ppdDst=(PointDef*)pDst;

	pSrc=(UByte*)(ppdSrc+aphSrc.vertexCount);

	//time to de-rez the polygon edge definitions as required
	DeRezEdges(	aphSrc.edgeCount,(EdgeDef*)pSrc,
				pBase+aphSrc.edgePointsStart,rez,
				usageTbl);

	int destPntCnt=0;

	for (int i=0;i<aphSrc.vertexCount;i++){
		if (usageTbl[i]!=0x00)
		{
			usageTbl[i]=UByte(destPntCnt);
			PointDef& pds=ppdSrc[i];
			PointDef& pdd=ppdDst[destPntCnt++];
			pdd=pds;
		}
	}
	aphDst.vertexCount=destPntCnt;

	pDst=(UByte*)&ppdDst[destPntCnt];

	//At this point in the destination data we insert a draw
	//data header
	DrawDataHdr& ddhDst=*(DrawDataHdr*)pDst;
	pDst+=sizeof(DrawDataHdr);

	DrawDataHdr& ddhSrc=*(DrawDataHdr*)(pBase+aphSrc.polyDataStart);
	pSrc=UByteP(&ddhSrc)+sizeof(DrawDataHdr);

	ddhDst.noOfPolys=ddhSrc.noOfPolys;
	ddhDst.noOfLines=ddhSrc.noOfLines;
	ddhDst.noOfTrees=0;
	ddhDst.noOfWaves=0;

	//convert the source draw data into the correct dest draw
	//data format

	globalTriCount=0;

	for (i=0;i<ddhSrc.noOfPolys;i++){

		UByte* abortPolyPtr=pDst;

		//copy over polygon colour data first
		UByte areaType=*pSrc++;
		*pDst++=areaType;

		UByte* insTriCntHere=pDst++;

		//next byte of source is the polygon edge count
		UByte polyEdges=*pSrc++;

		//build a local poly definition
		UByte localPoly[256];
		UByte localPolyLen=0;
		UByte* dirFlags=pSrc+polyEdges;		//edge direction flags for this
											//polygon
		for (int j=0;j<polyEdges;j++){

			UByte edgeIndex=pSrc[j];
			UByte* pep=edgeLists[edgeIndex];
		 	bool edgeFlipped=(BITTEST(dirFlags,j))?true:false;

			UByte pointsOnEdge=*pep++; 	//no of points on edge inc start &
										//end points
			if (!edgeFlipped){
				for (int k=0;k<pointsOnEdge-1;k++)
					localPoly[localPolyLen++]=usageTbl[pep[k]];
			}
			else{
				for (int k=pointsOnEdge-1;k>0;k--)
					localPoly[localPolyLen++]=usageTbl[pep[k]];
			}
		}
		//localPoly & localPolyLen now contain the draw information
		//for the current polygon

		RemoveStupids(localPolyLen,localPoly);

		if (localPolyLen<3){
			pDst=abortPolyPtr;
			ddhDst.noOfPolys--;
		}
		else
		{
			int totalFans=(*pGenTri)(localPolyLen,ppdDst,localPoly,pDst);
			if (totalFans==0)
			{
				pDst=abortPolyPtr;
				ddhDst.noOfPolys--;
			}
			else
			{
				*insTriCntHere=totalFans;

				//generate trees on this set of poly data

				if (treesEnabled && 
					IsWooded(areaType) &&
					ddhDst.noOfTrees<128)
					ddhDst.noOfTrees+=BuildTreeList(insTriCntHere,ppdDst,localTreeListPtr);
			}
		}

		//move the src pointer on to the next poly definition
		pSrc+=polyEdges+((polyEdges+7)>>3);
	}

	//assert(globalTriCount>=ddhDst.noOfPolys);

	ddhDst.totalTris=globalTriCount;	//for HW execute buffer fill test

	for (i=0;i<ddhSrc.noOfLines;i++){

		UByte* abortLinePtr=pDst;

		//copy over the line colour data first
		*pDst++=*pSrc++;
		UByte* insLinCntHere=pDst++;

		//next byte of source is the line edge count
		UByte lineEdges=*pSrc++;

		//Build a local line definition
		UByte localLine[256];
		UByte localLineLen=0;
		UByte* dirFlags=pSrc+lineEdges;

		for (int j=0;j<lineEdges-1;j++) 
		{
			UByte edgeIndex=pSrc[j];
			UByte* pep=edgeLists[edgeIndex];
		 	bool edgeFlipped=(BITTEST(dirFlags,j))?true:false;

			UByte pointsOnEdge=*pep++; 	//no of points on edge inc start &
										//end points
			if (!edgeFlipped){
				for (int k=0;k<pointsOnEdge-1;k++)
					localLine[localLineLen++]=usageTbl[pep[k]];
			}
			else{
				for (int k=pointsOnEdge-1;k>0;k--)
					localLine[localLineLen++]=usageTbl[pep[k]];
			}
		}
		for (;j<lineEdges;j++) 
		{
			UByte edgeIndex=pSrc[j];
			UByte* pep=edgeLists[edgeIndex];
		 	bool edgeFlipped=(BITTEST(dirFlags,j))?true:false;

			UByte pointsOnEdge=*pep++; 	//no of points on edge inc start &
										//end points
			if (!edgeFlipped){
				for (int k=0;k<pointsOnEdge;k++)
					localLine[localLineLen++]=usageTbl[pep[k]];
			}
			else{
				for (int k=pointsOnEdge-1;k>=0;k--)
					localLine[localLineLen++]=usageTbl[pep[k]];
			}
		}

		//localLine & localLineLen now contain the draw information
		//for the current line

		RemoveStupids(localLineLen,localLine);

		if (localLineLen<2){
			pDst=abortLinePtr;
			ddhDst.noOfLines--;
		}
		else{
		 	*insLinCntHere=localLineLen;
			for (j=0;j<localLineLen;*pDst++=localLine[j],j++) {}
		}
		//move the src pointer on to the next line definition
		pSrc+=lineEdges+((lineEdges+7)>>3);
	}

	//add tree data to the end of the list

	ddhDst.treeOffset=ULong(pDst)-ULong(pDataStart);

	for (i=0;i<ddhDst.noOfTrees;i++)
	{
		*(SmallPoint*)pDst=ltl[i];
		pDst+=sizeof(SmallPoint);
	}

	ddhDst.waveOffset=ULong(pDst)-ULong(pDataStart);

	for (i=0;i<ddhDst.noOfWaves;i++)
	{
		*(SmallPoint*)pDst=ltl[i];
		pDst+=sizeof(SmallPoint);
	}

	delete[]usageTbl;

	aphDst.MakeChecksum();		//CHECKSUM!!!

	dataLen=ULong(pDst)-ULong(pDataStart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeRezEdges
//Author		Paul.   
//Date			Thu 21 May 1998
//------------------------------------------------------------------------------
void CDecompressData::DeRezEdges(	ULong edgeCnt,EdgeDef* ped,
									UByte* pfrep,ULong rez,
									UByte* usageTbl)
{
	UByte* pep=edgePoints;
	ULong dropCounter=0;
	for (int i=0;i<edgeCnt;i++){
		UByte edgeLength=0;
		EdgeDef& ed=ped[i];
		edgeLists[i]=pep;

		//step through an edge at a time and remove points when required
		UByte* insertEdgeLengthHere=pep++;

		//always add the first and last points to the edge list
		*pep++=ed.startPoint;
		edgeLength++;

		UByte* epl=pfrep+ed.edgeOffset;
		for (int j=0;j<ed.noOfPoints;j++){
		 	if (dropCounter==rez){			//add a point to the edge
				UByte edgePoint=*epl++;
				*(usageTbl+edgePoint)=0xFF;
				*pep++=edgePoint;
				edgeLength++;
			}
			else epl++;
			dropCounter++;
			if (dropCounter>rez) dropCounter=0;
		}
		//always add the last point to the edge list
		*pep++=ed.endPoint;
		edgeLength++;
		*insertEdgeLengthHere=edgeLength;

		*(usageTbl+ed.startPoint)=0xFF;
		*(usageTbl+ed.endPoint)=0xFF;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeIntermediateData
//Author		Paul.   
//Date			Wed 20 May 1998
//------------------------------------------------------------------------------
void CDecompressData::MakeIntermediateData()
{
	UByte* pDst=pDataStart;
	//Copy over the header
	AltPointsHdr& aph=*(AltPointsHdr*)pDst;
	aph.vertexCount=Max_Points;

	aph.topEdgePoints=topEdgeCnt;
  	aph.rightEdgePoints=rightEdgeCnt;
   	aph.bottomEdgePoints=bottomEdgeCnt;
	aph.leftEdgePoints=leftEdgeCnt;

	aph.minAlt=lowestAlt;
	aph.maxAlt=highestAlt;

	UWord edgePointCount=4+topEdgeCnt+rightEdgeCnt+bottomEdgeCnt+leftEdgeCnt;

	//Skip the header data
	pDst+=sizeof(aph);

	//copy over the point data
	PointDef* ppd=(PointDef*)pDst;
	PointList* ppl=(PointList*)pointdec;
	for (int i=0;i<aph.vertexCount;i++){
	 	PointDef& pd=*ppd++;
		PointList& pl=*ppl++;
		pd.x=UWord(pl.x);
		pd.z=UWord(pl.y);
		pd.alt=UWord(pl.alt);
		pd.shadeVal=pl.shadeVal;
		pointFlags[i]=0;
	}

	//Find out which points are edge points and which are junction points
	GeneratePointFlags(edgePointCount);

	//Prepare to record the edge definitions
	EdgeDef* ped=(EdgeDef*)ppd;
	edgeDefs=ped;
	aph.edgeListStart=ULong(ped)-ULong(&aph);

	//Rearrange the draw data
	GenerateEdges();

	aph.edgeCount=edgeCount;	//record total edge count for later

	pDst=(UByte*)ped;
	pDst+=sizeof(EdgeDef)*edgeCount;
	aph.edgePointsStart=ULong(pDst)-ULong(&aph);

	//Copy back the edge point data
	for (i=0;i<edgePointLen;i++) *pDst++=edgePoints[i];

	aph.polyDataStart=ULong(pDst)-ULong(&aph);

	DrawDataHdr& ddh=*(DrawDataHdr*)pDst;
	pDst+=sizeof(ddh);
	ddh.noOfPolys=globalPolyCount;
	ddh.noOfLines=globalLineCount;

	//Copy back the new draw data
	for (i=0;i<polyStreamLen;i++) *pDst++=newPolyStream[i];
	for (i=0;i<lineStreamLen;i++) *pDst++=newLineStream[i];

	aph.MakeChecksum();		//CHECKSUM!!!

	dataLen=ULong(pDst)-ULong(&aph);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetRouteCon
//Author		Paul.   
//Date			Wed 10 Jun 1998
//------------------------------------------------------------------------------
inline void CDecompressData::ResetRouteCon(UByte pntCnt)
{
 	for (int i=0;i<pntCnt;routeCon[i].flags=0,routeCon[i].count=0,i++) {}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateEdges
//Author		Paul.   
//Date			Wed 20 May 1998
//------------------------------------------------------------------------------
void CDecompressData::GenerateEdges()
{
	//Find polygon edges. An edge is defined as a set of points betweeen
	//2 junction points
	UByte polyBuf[256];
	UByte miniBuf[256];
	UByte pointCount=0;

	UByte* pData=PolyStream;

	UByte* ppd=newPolyStream;
	UByte* pld=newLineStream;
	UByte* pep=edgePoints;

	edgeCount=0;

	UByte code;

	globalPolyCount=0;
	globalLineCount=0;

	while ((code=*pData++)!=JOIN_ROAD_NEXT){
		if (code==JOIN_POLY_NEXT){
			if (pointCount!=0){
				globalPolyCount++;
				InsertEdgeDefs(pointCount,polyBuf,pep,ppd);
				pointCount=0;
			}
	 		*ppd++=*pData++;	// add the colour of this polygon to the
			pData++;			// new def & skip the previous point
								// definition
			polyBuf[pointCount++]=*pData++;
		}
		else polyBuf[pointCount++]=code;
	}
	if (pointCount!=0) 
	{
		globalPolyCount++;
		InsertEdgeDefs(pointCount,polyBuf,pep,ppd);
	}

	//don't forget the routes

	pData=LineStream;

	pointCount=0;

	UByte initialRouteType;

	while ((code=*pData++)!=JOIN_POLY_NEXT)
	{
		if (code==JOIN_ROAD_NEXT)
		{
			if (pointCount!=0)
			{
				if (IsValidRoute(initialRouteType))
				{
					SLong lastIndex=0;
					*miniBuf=*polyBuf;
					for (SLong x=1;x<pointCount;x++)
					{
						SLong w=x-lastIndex;
						miniBuf[w]=polyBuf[x];
						if (pointFlags[miniBuf[w]]==PT_JUNCTION)
						{
							if (routeCon[miniBuf[w]].flags&&routeCon[*miniBuf].flags)
								*pld++=RT_magic;
							else
								*pld++=initialRouteType;
							InsertEdgeDefs2(w+1,miniBuf,pep,pld);
							globalLineCount++;
							lastIndex=x;
							*miniBuf=miniBuf[w];
						}
					}
				}
				pointCount=0;
			}
			initialRouteType=*pData++;
			polyBuf[pointCount++]=*pData++;
		}
		else polyBuf[pointCount++]=code;
	}
	if (pointCount!=0 && IsValidRoute(initialRouteType)) 
	{
		SLong lastIndex=0;
		*miniBuf=*polyBuf;
		for (SLong x=1;x<pointCount;x++)
		{
			SLong w=x-lastIndex;
			miniBuf[w]=polyBuf[x];
			if (pointFlags[miniBuf[w]]==PT_JUNCTION)
			{
				if (routeCon[miniBuf[w]].flags&&routeCon[*miniBuf].flags)
					*pld++=RT_magic;
				else
					*pld++=initialRouteType;
				InsertEdgeDefs2(w+1,miniBuf,pep,pld);
				globalLineCount++;
				lastIndex=x;
				*miniBuf=miniBuf[w];
			}
		}
	}

	polyStreamLen=ULong(ppd)-ULong(newPolyStream);
	lineStreamLen=ULong(pld)-ULong(newLineStream);
	edgePointLen=ULong(pep)-ULong(edgePoints);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InsertEdgeDefs
//Author		Paul.   
//Date			Wed 20 May 1998
//------------------------------------------------------------------------------
void CDecompressData::InsertEdgeDefs(	UByte pntCnt,UByte* poly,
										UByte*& xpep,UByte*& xppd)
{
	UByte* pep=xpep;
	UByte* ppd=xppd;

	//Clear direction flags for use later...
	UByte dirFlags[32];
	for (UByte i=0;i<8;i++) *(ULong*)(dirFlags+(i<<2))=0L;

	//find the first junction point in this poly def
	for (i=0;i<pntCnt;i++){
		UByte point=poly[i];
		if (pointFlags[point]==PT_JUNCTION) break;
	}
	assert(i!=pntCnt&&"No junction points in poly?");

	UByte jStart=i;
	UByte jEnd;

	UByte localPoly[256];
	UByte localPolyLen=0;

	UByte* insertEdgeCountHere=ppd++;
	UByte  edgeCounter=0;

	for (UByte j=(i+1)%pntCnt;j!=i;j=(j+1)%pntCnt){
		jEnd=j;
		UByte point=poly[jEnd];
		if (pointFlags[point]==PT_JUNCTION){
			UWord edgeIndex=AddEdge(poly[jStart],point,localPolyLen,localPoly,pep);
			*ppd++=UByte(edgeIndex);
			if (edgeIndex&0x8000){
			 	BITSET(dirFlags,edgeCounter);
			}
			edgeCounter++;
			localPolyLen=0;
			jStart=jEnd;
		}
		else localPoly[localPolyLen++]=poly[j];
	}
	UWord edgeIndex=AddEdge(poly[jStart],poly[i],localPolyLen,localPoly,pep);
	*ppd++=UByte(edgeIndex);
	if (edgeIndex&0x8000){
		BITSET(dirFlags,edgeCounter);
	}
	edgeCounter++;

	//fill in the edge count for this polygon
	*insertEdgeCountHere=edgeCounter;
	//copy over the direction flags
	j=(edgeCounter+7)>>3;
	for (i=0;i<j;i++) *ppd++=dirFlags[i];

	xpep=pep;
	xppd=ppd;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InsertEdgeDefs2
//Author		Paul.   
//Date			Wed 10 Jun 1998
//------------------------------------------------------------------------------
void CDecompressData::InsertEdgeDefs2(	UByte pntCnt,UByte* line,
										UByte*& xpep,UByte*& xpld)
{
	UByte* pep=xpep;
	UByte* pld=xpld;

	//Clear direction flags for use later...
	UByte dirFlags[32];
	for (UByte i=0;i<8;i++) *(ULong*)(dirFlags+(i<<2))=0L;

	//first and last points on the line must be junction points
	//or this isn't going to work

	assert(	pointFlags[*line]==PT_JUNCTION &&
			pointFlags[*(line+pntCnt-1)]==PT_JUNCTION &&
			"First/Last point in line must be a junction point");

	UByte jStart=0;
	UByte jEnd;

	UByte localLine[256];
	UByte localLineLen=0;

	UByte* insertEdgeCountHere=pld++;
	UByte  edgeCounter=0;

	for (UByte j=1;j<pntCnt;j++){
		jEnd=j;
		UByte point=line[jEnd];
		if (pointFlags[point]==PT_JUNCTION){
			UWord edgeIndex=AddEdge(line[jStart],point,localLineLen,localLine,pep);
			*pld++=UByte(edgeIndex);
			if (edgeIndex&0x8000){
			 	BITSET(dirFlags,edgeCounter);
			}
			edgeCounter++;
			localLineLen=0;
			jStart=jEnd;
		}
		else localLine[localLineLen++]=line[j];
	}

	//fill in the edge count for this line
	*insertEdgeCountHere=edgeCounter;
	//copy over the direction flags
	j=(edgeCounter+7)>>3;
	for (i=0;i<j;i++) *pld++=dirFlags[i];

	xpep=pep;
	xpld=pld;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddEdge
//Author		Paul.   
//Date			Wed 20 May 1998
//------------------------------------------------------------------------------
UWord CDecompressData::AddEdge(	UByte jStart,UByte jEnd,
								UByte pntCnt,UByte* pntLst,
								UByte*& xpep)
{
	UByte* pep=xpep;

	//Check to see if this edge has already been inserted
	UWord dirFlipped=0;
	bool foundMatch=false;

	for (int i=0;i<edgeCount&&!foundMatch;i++)
	{
		EdgeDef& ed=edgeDefs[i];

		//check to see if this edge matches forwards
		if (ed.startPoint==jStart &&
			ed.endPoint==jEnd &&
			ed.noOfPoints==pntCnt)
		{
			//it's a potential match but just make sure...
			UByte* testEdge=edgePoints+ed.edgeOffset;
			for (int j=0;j<pntCnt&&testEdge[j]==pntLst[j];j++) {}
			if (j==pntCnt) foundMatch=true;
		}

		//check to see if this edge matches backwards
		if (ed.startPoint==jEnd &&
			ed.endPoint==jStart &&
			ed.noOfPoints==pntCnt)
		{
			//it's a potential match but just make sure...
			UByte* testEdge=edgePoints+ed.edgeOffset;
			for (int j=0;j<pntCnt&&testEdge[j]==pntLst[pntCnt-1-j];j++) {}
			if (j==pntCnt)
			{
				dirFlipped=0x8000;
				foundMatch=true;
			}
		}
	}

	if (foundMatch) return dirFlipped+UWord(i-1);	//Already inserted

	EdgeDef& ed=edgeDefs[i];
	edgeCount++;
	assert(edgeCount<=256&&"Edge list overflow");
	ed.startPoint=jStart;
	ed.endPoint=jEnd;
	ed.noOfPoints=pntCnt;
	//calculate edge length here later
	if (pntCnt==0)
		ed.edgeOffset=UWord(0);
	else{
		ed.edgeOffset=UWord(ULong(pep)-ULong(edgePoints));
		for (int j=0;j<pntCnt;j++) *pep++=*pntLst++;
	}

	xpep=pep;
	return UWord(i);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GeneratePointFlags
//Author		Paul.   
//Date			Wed 20 May 1998
//------------------------------------------------------------------------------
void CDecompressData::GeneratePointFlags(UWord edgePointCount)
{
	ResetRouteCon(Max_Points);

	if (edgePointCount<Max_Points){
		UByte* pData=PolyStream;
		UByte code;
		UByte type;
		UByte flag;

		while ((code=*pData++)!=JOIN_ROAD_NEXT){
	 		if (code==JOIN_POLY_NEXT){
				type=*pData++;				//skip the colour for this polygon
				if (IsForest(type))	flag=1;
				else flag=0;
				pData++;					//Skip 'previous' point definition
				UByte point=*pData++;
				pointFlags[point]++;		//Increment first point usage count
				UByte rIndex=routeCon[point].count;
				routeCon[point].types[rIndex++]=type;
				routeCon[point].flags|=flag;
				assert(rIndex<9&&"More than 8 connection points?");
				routeCon[point].count=rIndex;
			}
			else{
				pointFlags[code]++;
			 	UByte rIndex=routeCon[code].count;
				routeCon[code].types[rIndex++]=type;
				routeCon[code].flags|=flag;
				assert(rIndex<9&&"More than 8 connection points?");
				routeCon[code].count=rIndex;
			}
		}

		//line start & end points must also be 
		//clasified as junction points

		pData=LineStream;

		UByte lastCode=JOIN_ROAD_NEXT;

		while ((code=*pData++)!=JOIN_POLY_NEXT){
			if (code==JOIN_ROAD_NEXT){
				//skip the colour byte
				type=*pData++;
				if (IsForest(type))	flag=1;
				else flag=0;
				UByte point=*pData++;
				pointFlags[point]=3;			//forced to be a junction
				UByte rIndex=routeCon[point].count;
				routeCon[point].types[rIndex++]=type;
				assert(rIndex<9&&"More than 8 connection points?");
				routeCon[point].count=rIndex;
				routeCon[point].flags|=flag;
				if (lastCode!=JOIN_ROAD_NEXT)
					pointFlags[lastCode]=3;		//forced to be a junction
			}
			else{
			 	UByte rIndex=routeCon[code].count;
				routeCon[code].types[rIndex++]=type;
				routeCon[code].flags|=flag;
				assert(rIndex<9&&"More than 8 connection points?");
				routeCon[code].count=rIndex;
			}
			lastCode=code;
		}
		if (lastCode!=JOIN_ROAD_NEXT) pointFlags[lastCode]=3;
	}

	//convert point usage count to flags
	for (int i=0;i<edgePointCount;pointFlags[i++]=UByte(PT_JUNCTION)){}
	for (;i<Max_Points;i++){
		if (pointFlags[i]>2)	pointFlags[i]=UByte(PT_JUNCTION);
		else					pointFlags[i]=UByte(PT_EDGE);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PointsConnected
//Author		Paul.   
//Date			Thu 4 Dec 1997
//------------------------------------------------------------------------------
inline void CDecompressData::PointsConnected(SLong a,SLong b)
{
	UByte* ptr=pointdec[a].directionsused;
	while (*ptr!=NULLCON) if (*ptr++==UByte(b)) return;
	*ptr=UByte(b);
	ptr=pointdec[b].directionsused-1;
	while (*(++ptr)!=NULLCON) {}
	*ptr=UByte(a);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLVector
//Author		Paul.   
//Date			Tue 31 Mar 1998
//------------------------------------------------------------------------------
inline void CDecompressData::SetLVector(SLong li,SLong lj,SLong lk)
{
	wLi=double(li);	//world position of the sun
	wLj=double(lj);
	wLk=double(lk);
	//normalise
	double mag=wLi*wLi+wLj*wLj+wLk*wLk;
	_asm
	{
		fld mag;
		fsqrt;
		fstp mag;
	}
	wLi/=mag;
	wLj/=mag;
	wLk/=mag;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AverageNormals
//Author		Paul.   
//Date			Tue 31 Mar 1998
//------------------------------------------------------------------------------
void CDecompressData::AverageNormals(SLong pntCnt,PointDef* pntArray,UByte* renumber)
{
	if (!lightShadingEnabled) return;

	NormalList* nList=normalList;
	for (int x=0;x<pntCnt;x++)
	{
		NormalList& n=nList[renumber[x]];
		if (n.count!=1){
			//re-normalise the averaged vector...
			Float mag=n.ni*n.ni+n.nj*n.nj+n.nk*n.nk;
			_asm
			{
				fld mag;
				fsqrt;
				fstp mag;
			}
			n.ni/=mag;
			n.nj/=mag;
			n.nk/=mag;
		}

		//Do dot product with light vector to get
		//fade value
		Float dotp=n.ni*wLi+n.nj*wLj+n.nk*wLk;

		UByte val;
		if (dotp<0.) val=0;
		else val=UByte(255.*dotp);
		pntArray->shadeVal=val;
		pntArray++;
	}
}


const int MAX_CACHE_BLOCKS = 4096<<1;
const int MAIN_CACHE_MEM = 0x80000<<1;

CCacheBlock*		CCacheBlock::pHead=NULL;
CPrimaryCB*			CPrimaryCB::pHead=NULL;

CCacheBlockAlloc*	CCacheBlock::pAlloc=NULL;
CPrimaryCBAlloc*	CPrimaryCB::pAlloc=NULL;

CDataBlockAllocator* CDataBlock::pAlloc=NULL;
CPrimaryDBAllocator* CPrimaryDB::pAlloc=NULL;

///////////////////////////////////////////////////////////////////////////////
////																	   ////
//// CCacheBlock Methods												   ////
////																	   ////
///////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CCacheBlock
//Author		Paul.   
//Date			Thu 29 Jan 1998
//-----------------------------------------------------------------------------
CCacheBlock::~CCacheBlock()
{
	if (pData!=NULL) pData->pCacheBlock=NULL,pData=NULL;
}

//-----------------------------------------------------------------------------
// Procedure    new
// Author       Paul
// Date         13/01/98
//-----------------------------------------------------------------------------
#undef new
void* CCacheBlock::operator new(size_t)
{
	CCacheBlock* pCB=pAlloc->Alloc();
	return (void*)pCB;
}
#define	new DEBUG_NEW
//-----------------------------------------------------------------------------
// Procedure    delete
// Author       Paul
// Date         13/01/98
//-----------------------------------------------------------------------------
void CCacheBlock::operator delete(void* pDMe)
{
	CCacheBlock* pDelMe=(CCacheBlock*)pDMe;
	pAlloc->Free(pDelMe);
	pDelMe->pParent=pDelMe->pNorth=pDelMe->pEast=(CCacheBlock*)0xCDCDCDCD;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Insert
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
void CCacheBlock::Insert()
{
	//The list is empty at present so just insert this new
	//element at the head of the list
	if (pHead==NULL){
		pNorth=pEast=pParent=NULL;
		pHead=this;
	}
	else{
		//Find the correct position in the list to insert the
		//new element
		CCacheBlock* pScan = pHead;
		CCacheBlock* pPrev = NULL;

		//Search in Wz first
		while (pScan!=NULL && pScan->blockWz<blockWz){
			pPrev=pScan; pScan=pScan->pNorth;
		}
		//If pScan==NULL then this block needs to be added to the
		//end of the northern branch
		if (pScan==NULL){
			pPrev->pNorth=this;
			pParent=pPrev;
			pNorth=pEast=NULL;
		}
		else{
			if (pScan->blockWz!=blockWz){
				//If pPrev==NULL then we are inserting the new element 
				//at the head of the list
				if (pPrev==NULL){
					pHead=pScan->pParent=this;
					pNorth=pScan;
					pEast=pParent=NULL;
				}
				else{
					//Otherwise, we are adding a new entry to the northern 
					//branch of the tree
					pPrev->pNorth=pScan->pParent=this;
					pNorth=pScan;
					pParent=pPrev;
					pEast=NULL;
				}
			}
			else{
				//Now search in Wx
				pPrev = NULL;
				while (pScan!=NULL && pScan->blockWx<blockWx){
			 		pPrev=pScan; pScan=pScan->pEast;
				}
				//If pScan==NULL then we are adding the new element at the end
				//of an eastern branch of the tree
				if (pScan==NULL){
					pPrev->pEast=this;
					pParent=pPrev;
					pNorth=pEast=NULL;
				}
				else{
					assert(pScan->blockWx!=blockWx&&" entry already cached");
					//If pPrev==NULL then the new element is being inserted
					//at the start of the eastern branch of the tree
					if (pPrev==NULL){
						pPrev=pScan->pParent;
						//If pPrev==NULL then the eastern branch starts at the
						//head of the list
						if (pPrev==NULL){
							pHead=this;
							pParent=NULL;
							pEast=pScan;
							pNorth=pScan->pNorth;
							pScan->pParent=this;
							pScan->pNorth=NULL;
							if (pNorth!=NULL) pNorth->pParent=this;
						}
						else{
							pPrev->pNorth=this;
							pParent=pPrev;
							pNorth=pScan->pNorth;
							pEast=pScan;
							pScan->pParent=this;
							pScan->pNorth=NULL;
							if (pNorth!=NULL) pNorth->pParent=this;
						}
					}
					else{
						pPrev->pEast=this;
						pParent=pPrev;
						pNorth=NULL;
						pEast=pScan;
						pScan->pParent=this;
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Remove
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
void CCacheBlock::Remove()
{
	//pParent==NULL => this item is at the head of the list
	if (pParent==NULL){
		//If this block has a branch to the east then
		//then the first element to the east of this one
		//will become the new head of the list
		if (pEast!=NULL){
			pHead=pEast;
			pHead->pParent=NULL;
			//If the old block had an entry to the north then the new
			//blocks north pointer needs to point to that entry
			if ((pHead->pNorth=pNorth)!=NULL) pHead->pNorth->pParent=pHead;
		}
		//If this block has a branch to the north then
		//the first element to the north becomes the new
		//head of the list
		else if (pNorth!=NULL){
			pHead=pNorth;
			pHead->pParent=NULL;
		}
		//This must have been the only entry in the list so just
		//set the list head pointer to NULL
		else pHead=NULL;
	}
	else{
		//If we get here then the element being removed is NOT at the
		//head of the list

		//(1) If the eastern branch of this blocks parent points
		//to it then we know that the element to be removed is on
		//an eastern branch.
		if (pParent->pEast==this){
			if ((pParent->pEast=pEast)!=NULL) pEast->pParent=pParent;
		}
		//If we get here then the element being removed is on a
		//northern branch
		//(2) Handle the case when the element being removed is on the
		//northern branch but has elements to the east
		else if (pEast!=NULL){
			pParent->pNorth=pEast;
			pEast->pParent=pParent;
			if ((pEast->pNorth=pNorth)!=NULL) pEast->pNorth->pParent=pEast;
		}
		//(3) Handle the case when the element being removed is on the
		//northern branch and has no elements to the east
		else if (pNorth!=NULL){
			pParent->pNorth=pNorth;
			pNorth->pParent=pParent;
		}
		//(4) The element being removed is on a northern branch at the very
		//end of the list
		else pParent->pNorth = NULL;
	}
	//To be safe, set the links in the removed block to duff values
	pNorth=pEast=pParent=(CCacheBlock*)0xCDCDCDCD;
	delete this;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Search
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
bool CCacheBlock::Search(int wx,int wz,CDataBlock*& pDBlk)
{
	bool retval=true;

	wx>>=COORD_SCALE;
	wz>>=COORD_SCALE;

	CCacheBlock* pScan = pHead;

	while (pScan!=NULL && pScan->blockWz<wz) pScan=pScan->pNorth;

	if (pScan==NULL || pScan->blockWz!=wz)	retval=false;

	if (retval){
		while (pScan!=NULL && pScan->blockWx<wx) pScan=pScan->pEast;

		if (pScan==NULL || pScan->blockWx!=wx)	retval=false;
	}

	if (retval)	pDBlk = pScan->pData;

	return retval;
}

///////////////////////////////////////////////////////////////////////////////
////																	   ////
//// CPrimaryCB Methods												   	   ////
////																	   ////
///////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CPrimaryCB
//Author		Paul.   
//Date			Thu 29 Jan 1998
//-----------------------------------------------------------------------------
CPrimaryCB::~CPrimaryCB()
{
	if (pData!=NULL) pData->pCacheBlock=NULL,pData=NULL;
}

//-----------------------------------------------------------------------------
// Procedure    new
// Author       Paul
// Date         13/01/98
//-----------------------------------------------------------------------------
#undef new
void* CPrimaryCB::operator new(size_t)
{
	CPrimaryCB* pCB=pAlloc->Alloc();
	return (void*)pCB;
}
#define	new DEBUG_NEW
//-----------------------------------------------------------------------------
// Procedure    delete
// Author       Paul
// Date         13/01/98
//-----------------------------------------------------------------------------
void CPrimaryCB::operator delete(void* pDMe)
{
	CPrimaryCB* pDelMe=(CPrimaryCB*)pDMe;
	pAlloc->Free(pDelMe);
	pDelMe->pParent=pDelMe->pNorth=pDelMe->pEast=(CPrimaryCB*)0xCDCDCDCD;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Insert
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
void CPrimaryCB::Insert()
{
	//The list is empty at present so just insert this new
	//element at the head of the list
	if (pHead==NULL){
		pNorth=pEast=pParent=NULL;
		pHead=this;
	}
	else{
		//Find the correct position in the list to insert the
		//new element
		CPrimaryCB* pScan = pHead;
		CPrimaryCB* pPrev = NULL;

		//Search in Wz first
		while (pScan!=NULL && pScan->blockWz<blockWz){
			pPrev=pScan; pScan=pScan->pNorth;
		}
		//If pScan==NULL then this block needs to be added to the
		//end of the northern branch
		if (pScan==NULL){
			pPrev->pNorth=this;
			pParent=pPrev;
			pNorth=pEast=NULL;
		}
		else{
			if (pScan->blockWz!=blockWz){
				//If pPrev==NULL then we are inserting the new element 
				//at the head of the list
				if (pPrev==NULL){
					pHead=pScan->pParent=this;
					pNorth=pScan;
					pEast=pParent=NULL;
				}
				else{
					//Otherwise, we are adding a new entry to the northern 
					//branch of the tree
					pPrev->pNorth=pScan->pParent=this;
					pNorth=pScan;
					pParent=pPrev;
					pEast=NULL;
				}
			}
			else{
				//Now search in Wx
				pPrev = NULL;
				while (pScan!=NULL && pScan->blockWx<blockWx){
			 		pPrev=pScan; pScan=pScan->pEast;
				}
				//If pScan==NULL then we are adding the new element at the end
				//of an eastern branch of the tree
				if (pScan==NULL){
					pPrev->pEast=this;
					pParent=pPrev;
					pNorth=pEast=NULL;
				}
				else{
					//assert(pScan->blockWx!=blockWx&&" entry already cached");
					//If pPrev==NULL then the new element is being inserted
					//at the start of the eastern branch of the tree
					if (pPrev==NULL){
						pPrev=pScan->pParent;
						//If pPrev==NULL then the eastern branch starts at the
						//head of the list
						if (pPrev==NULL){
							pHead=this;
							pParent=NULL;
							pEast=pScan;
							pNorth=pScan->pNorth;
							pScan->pParent=this;
							pScan->pNorth=NULL;
							if (pNorth!=NULL) pNorth->pParent=this;
						}
						else{
							pPrev->pNorth=this;
							pParent=pPrev;
							pNorth=pScan->pNorth;
							pEast=pScan;
							pScan->pParent=this;
							pScan->pNorth=NULL;
							if (pNorth!=NULL) pNorth->pParent=this;
						}
					}
					else{
						pPrev->pEast=this;
						pParent=pPrev;
						pNorth=NULL;
						pEast=pScan;
						pScan->pParent=this;
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Remove
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
void CPrimaryCB::Remove()
{
	//pParent==NULL => this item is at the head of the list
	if (pParent==NULL){
		//If this block has a branch to the east then
		//then the first element to the east of this one
		//will become the new head of the list
		if (pEast!=NULL){
			pHead=pEast;
			pHead->pParent=NULL;
			//If the old block had an entry to the north then the new
			//blocks north pointer needs to point to that entry
			if ((pHead->pNorth=pNorth)!=NULL) pHead->pNorth->pParent=pHead;
		}
		//If this block has a branch to the north then
		//the first element to the north becomes the new
		//head of the list
		else if (pNorth!=NULL){
			pHead=pNorth;
			pHead->pParent=NULL;
		}
		//This must have been the only entry in the list so just
		//set the list head pointer to NULL
		else pHead=NULL;
	}
	else{
		//If we get here then the element being removed is NOT at the
		//head of the list

		//(1) If the eastern branch of this blocks parent points
		//to it then we know that the element to be removed is on
		//an eastern branch.
		if (pParent->pEast==this){
			if ((pParent->pEast=pEast)!=NULL) pEast->pParent=pParent;
		}
		//If we get here then the element being removed is on a
		//northern branch
		//(2) Handle the case when the element being removed is on the
		//northern branch but has elements to the east
		else if (pEast!=NULL){
			pParent->pNorth=pEast;
			pEast->pParent=pParent;
			if ((pEast->pNorth=pNorth)!=NULL) pEast->pNorth->pParent=pEast;
		}
		//(3) Handle the case when the element being removed is on the
		//northern branch and has no elements to the east
		else if (pNorth!=NULL){
			pParent->pNorth=pNorth;
			pNorth->pParent=pParent;
		}
		//(4) The element being removed is on a northern branch at the very
		//end of the list
		else pParent->pNorth = NULL;
	}
	//To be safe, set the links in the removed block to duff values
	pNorth=pEast=pParent=(CPrimaryCB*)0xCDCDCDCD;
	delete this;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Search
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
UWord CPrimaryCB::Search(int wx,int wz,int rez,CPrimaryDB*& pDBlk)
{
	UWord retval=2;

	wx>>=COORD_SCALE;
	wz>>=COORD_SCALE;

	CPrimaryCB* pScan = pHead;

	while (pScan!=NULL && pScan->blockWz<wz) pScan=pScan->pNorth;

	if (pScan==NULL || pScan->blockWz!=wz)	retval=0;

	if (retval){
		while (pScan!=NULL && pScan->blockWx<wx) pScan=pScan->pEast;

		if (pScan==NULL || pScan->blockWx!=wx)	retval=0;
	}
	if (retval!=0){
		//found a block with a position match - now, test for a resolution
		//match
		CPrimaryCB* pFound=NULL;
		int rezDelta=0x7FFFFFFF;
		while (pScan!=NULL && pScan->blockWx==wx){
			int thisDelta=rez-(int)pScan->resolution;
			thisDelta=(thisDelta<0)?-thisDelta:thisDelta;
			if (thisDelta<rezDelta){
				pFound=pScan;
				rezDelta=thisDelta;
			}
			pScan=pScan->pEast;
		}
		pDBlk = pFound->pData;
		if (pFound->resolution!=UWord(rez)) retval=1;
	}
	return retval;
}

///////////////////////////////////////////////////////////////////////////////
////																	   ////
//// CMigLand Methods													   ////
////																	   ////
///////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClampAngle
//Author		Paul.   
//Date			Wed 3 Dec 1997
//------------------------------------------------------------------------------
ANGLES CMigLand::ClampAngle(ANGLES a)
{
	a+=ANGLES_45Deg;
	return (Angles)((int)a & 0xC000);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CMigLand
//Author		Paul.   
//Date			Wed 3 Dec 1997
//------------------------------------------------------------------------------
CMigLand::CMigLand()
{
	CCacheBlock::pHead=NULL;
	CPrimaryCB::pHead=NULL;

	CCacheBlock::pAlloc=NULL;
	CPrimaryCB::pAlloc=NULL;

	CDataBlock::pAlloc=NULL;
	CPrimaryDB::pAlloc=NULL;

 	currentFile	= CF_BAD;
	pMigIndex=new CMigIndex();
	pMigFMan=new CMigFMan();

	currentDirection = (Angles)0xFFFF;

	pMigFile = new CMigFile(0);
	pMigFile->pNorth=pMigIndex->pNorth;
	pMigFile->pEast=pMigIndex->pEast;
//DEAD	pMigFile->pSouth=pMigIndex->pSouth;
//DEAD	pMigFile->pWest=pMigIndex->pWest;

	pMigLandDecomp = new CDecompressData();
	pMigLandDecomp->treesEnabled=true;

	pMigFile->pDecomp=pMigLandDecomp;

	if (!CCacheBlock::pAlloc) CCacheBlock::pAlloc=new CCacheBlockAlloc(MAX_CACHE_BLOCKS);
	if (!CDataBlock::pAlloc) CDataBlock::pAlloc=new CDataBlockAllocator(MAIN_CACHE_MEM);

	if (!CPrimaryCB::pAlloc) CPrimaryCB::pAlloc=new CPrimaryCBAlloc(MAX_CACHE_BLOCKS);
	if (!CPrimaryDB::pAlloc) CPrimaryDB::pAlloc=new CPrimaryDBAllocator(MAIN_CACHE_MEM);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CMigLand
//Author		Paul.   
//Date			Wed 3 Dec 1997
//------------------------------------------------------------------------------
CMigLand::~CMigLand()
{
	delete pMigIndex;
	delete pMigFMan;
	pMigIndex=NULL;
	pMigFMan=NULL;

	if (CCacheBlock::pAlloc) delete CCacheBlock::pAlloc,CCacheBlock::pAlloc=NULL;
	if (CDataBlock::pAlloc) delete CDataBlock::pAlloc,CDataBlock::pAlloc=NULL;

	if (CPrimaryCB::pAlloc) delete CPrimaryCB::pAlloc,CPrimaryCB::pAlloc=NULL;
	if (CPrimaryDB::pAlloc) delete CPrimaryDB::pAlloc,CPrimaryDB::pAlloc=NULL;

	delete pMigLandDecomp;
	delete pMigFile;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BigInit
//Author		Paul    
//Date			Mon 28 Sep 1998
//------------------------------------------------------------------------------
void CMigLand::BigInit(MovingItem* vp)
{
	pMigFile->SetViewpoint(vp);
	pMigFile->BigInit();
	pMigFile->ProcessSeekRequestsNF();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDirection
//Author		Paul.   
//Date			Wed 3 Dec 1997
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetData
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
DataRecord CMigLand::GetData(ULong x,ULong z,ULong rez,DataRecord& dr)
{
	DataRecord retVal;

	CPrimaryCB* pPrimaryCB=CPrimaryCB::pHead;
	CPrimaryDB* pPrimaryDB=NULL;
	UWord located=0;

	if (pPrimaryCB) located=pPrimaryCB->Search(x,z,rez,pPrimaryDB);

	//returns,
	//		located==0 ... block not found at any resolution
	//		located==1 ... block found but not at requested resolution
	//		located==2 ... block found at requested resolution

	if (located==2 || (located==1 && blocksDecompressed>MAX_DECOMP_BLOCKS)){
		retVal.pData=pPrimaryDB->DataStart();
		retVal.dataLen=pPrimaryDB->DataLen();
		return retVal;
	}
	blocksDecompressed++;

	pMigLandDecomp->MakeIntData(x,z,rez,dr.pData,pPrimaryDB);

	retVal.pData=pPrimaryDB->DataStart();
	retVal.dataLen=pPrimaryDB->DataLen();

	return retVal;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetData
//Author		Paul.   
//Date			Mon 20 Jul 1998
//------------------------------------------------------------------------------
DataRecord CMigLand::GetData(ULong x,ULong z)
{
	DataRecord retVal;

	CCacheBlock* pCache=CCacheBlock::pHead;
	CDataBlock* pData=NULL;
	bool bFound=false;

	if (pCache) bFound=pCache->Search(x,z,pData);

	if (!bFound){
		UByte* ptr=pMigFMan->getdata(*pMigFile,*pMigLandDecomp,x,z);
		pMigLandDecomp->UnPack(x,z,ptr,pData);
	}
	retVal.pData=pData->DataStart();
	retVal.dataLen=pData->DataLen();

	return retVal;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeIData
//Author		Paul.   
//Date			Mon 20 Jul 1998
//------------------------------------------------------------------------------
UByte* CMigLand::MakeIData(const DataRecord& dr,const ULong rez)
{
	pMigLandDecomp->UnpackIntData((UByte*)dr.pData,ULong(rez));
	return (UByte*)pMigLandDecomp->pDataStart;
}

LandMapNumRecord	lmnr;
LandMapNumRecord*	LandMapNum::pRecord=&lmnr;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLandMapPtr
//Author		Paul.   
//Date			Mon 19 Jan 1998
//------------------------------------------------------------------------------
ImageMapDescPtr LandMapNum::GetLandMapPtr()
{
	return (*pRecord)[no];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LandMapNumRecord
//Author		Paul.   
//Date			Mon 19 Jan 1998
//------------------------------------------------------------------------------
LandMapNumRecord::LandMapNumRecord()
{
	whichDir=DIR_LANDMAPS;
	for(int i=0;i<MAXMAPS;i++)		 			//RJS 09Feb98
	{
		lm[i].body=NULL;						//RJS 09Feb98
		lm[i].palette=NULL;						//RJS 09Feb98
		lm[i].alpha=NULL;						//RJS 09Feb98
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LandMapNumRecord
//Author		Paul.   
//Date			Mon 19 Jan 1998
//------------------------------------------------------------------------------
LandMapNumRecord::~LandMapNumRecord()
{
	for(int i=0;i<MAXMAPS;i++)
		if (lm[i].body!=NULL)
		{
			delete lm[i].body;						//RJS 09Feb98
			delete lm[i].palette;					//RJS 09Feb98
			delete lm[i].alpha;						//RJS 09Feb98
			lm[i].body=NULL;						//RJS 09Feb98
			lm[i].palette=NULL;						//RJS 09Feb98
			lm[i].alpha=NULL;						//RJS 09Feb98
		}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Reset
//Author		Paul.   
//Date			Mon 19 Jan 1998
//------------------------------------------------------------------------------
void LandMapNumRecord::Reset(FileNum dir)
{
	whichDir=dir;
	for (int i=0;i<MAXMAPS;i++)
		if (lm[i].body != NULL)			 //RJS 09Feb98
		{
			delete lm[i].body;			//RJS 09Feb98
			lm[i].body=NULL;			//RJS 09Feb98
		}
}

//-----------------------------------------------------------------------------
// Procedure    LandMapNumRecord::Switch
// Author       Paul
// Date         19/01/98
//-----------------------------------------------------------------------------
void LandMapNumRecord::Switch(FileNum dir)
{
	if (dir==whichDir) return;
	whichDir=dir;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		operator[]
//Author		Paul.   
//Date			Mon 19 Jan 1998
//------------------------------------------------------------------------------
ImageMapDescPtr LandMapNumRecord::operator[] (int i)
{
	assert(i<MAXMAPS&&i>=0&&" landmapnumrecord index out of range");
	if (lm[i].body==NULL)										//RJS 09Feb98
	{
		FileNum f=FileNum(whichDir+i);
		fileblock	fblock = f;									//RJS 09Feb98

		lm[i].FixLbmImageMap(&fblock);							//RJS 09Feb98
		assert(lm[i].body&&" land map load failed");			//RJS 09Feb98
	}
	return &lm[i];
}

LandMapNum::LandMapNum(FileNum f,FileNum dir)
{
	no=SWord(f-DIR_LANDMAPS);
	pRecord->Switch(dir);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLVector
//Author		Paul.   
//Date			Mon 11 May 1998
//------------------------------------------------------------------------------
void CMigLand::SetLVector(SLong li,SLong lj,SLong lk)
{
	pMigLandDecomp->SetLVector(li,lj,lk);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetShadowAngles
//Author		Paul.   
//Date			Mon 8 Jun 1998
//------------------------------------------------------------------------------
void CMigLand::GetShadowAngles(	COORDS3D& pos,ANGLES ang,
								ANGLES& reqPitch,ANGLES& reqRoll)
{
	pos.Y=0;
	pos.Y=GetAltitude(pos);
	COORDS3D frnt,side;
	frnt=side=pos;
	SWord sin_ang,cos_ang;
	Math_Lib.high_sin_cos(ang,sin_ang,cos_ang);
	frnt.X+=SLong(sin_ang);
	frnt.Z+=SLong(cos_ang);
	frnt.Y=0;
	frnt.Y=GetAltitude(frnt);
	ang+=ANGLES_90Deg;
	Math_Lib.high_sin_cos(ang,sin_ang,cos_ang);
	side.X+=SLong(sin_ang);
	side.Z+=SLong(cos_ang);
	side.Y=0;
	side.Y=GetAltitude(side);
	SWord hdgI,ptchI;
	SLong range;
	Math_Lib.HighIntercept(frnt.X-pos.X,frnt.Y-pos.Y,frnt.Z-pos.Z,range,hdgI,ptchI);
	reqPitch=(Angles)ptchI;
	Math_Lib.HighIntercept(side.X-pos.X,side.Y-pos.Y,side.Z-pos.Z,range,hdgI,ptchI);
	reqRoll=(Angles)-ptchI;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAltitude
//Author		Paul.   
//Date			Mon 8 Jun 1998
//------------------------------------------------------------------------------
SLong CMigLand::GetAltitude(COORDS3D& pos,UByte* pAreaType,bool fReallyGetData)
{
	DataRecord retVal;

	CPrimaryCB* pPrimaryCB=CPrimaryCB::pHead;
	CPrimaryDB* pPrimaryDB=NULL;
	UWord located=0;

	if (pPrimaryCB) located=pPrimaryCB->Search(pos.X,pos.Z,0,pPrimaryDB);

	//returns,
	//		located==0 ... block not found at any resolution
	//		located==1 ... block found but not at requested resolution
	//		located==2 ... block found at requested resolution

	if (located!=0)
	{
		//We have some data to extract altitude information from
		retVal.pData=pPrimaryDB->DataStart();
		retVal.dataLen=pPrimaryDB->DataLen();
		SLong xPos=(pos.X&0x1FFFF);
		SLong zPos=0x1FFFF-(pos.Z&0x1FFFF);
		SLong alt=pos.Y;
		pMigLandDecomp->FindAltNType(xPos,zPos,retVal,alt,lastGroundHit);
		if (pAreaType) *pAreaType=lastGroundHit;
		return alt;
	}
	else if (fReallyGetData && !Three_Dee.nomorereallygetdata)
	{
		//only for bfield setup stuff
		const ULong GMask=~ULong(131072-1);
		SLong px,pz;
		px=pos.X>>17;
		pz=pos.Z>>17;
		pz=_northIndex(px,pz);	//offset index
		SInfo sinfo=pMigFile->pNorth[pz];
		px&=0x7f;				//skip count
		SeekStruc ss;
		ss.fileNum=FIL_AREAN_NUM;
		ss.seekPos=sinfo.offset;
		ss.dataLen=sinfo.length;
		ss.firstSkipIndex=px;
		ss.numBlocks=1;
		px=pos.X&GMask;
		pz=pos.Z&GMask;
		pMigFile->OneShotSeekRequest(px,pz,&ss,&retVal);
		SLong xPos=(pos.X&0x1FFFF);
		SLong zPos=0x1FFFF-(pos.Z&0x1FFFF);
		SLong alt=pos.Y;
		pMigLandDecomp->FindAltNType(xPos,zPos,retVal,alt,lastGroundHit);
		if (pAreaType) *pAreaType=lastGroundHit;
		return alt;
	}
	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRoughAltitude
//Author		Paul.   
//Date			Wed 3 Mar 1999
//------------------------------------------------------------------------------
SLong CMigLand::GetRoughAltitude(SLong x,SLong y,SLong z)
{
	DataRecord retVal;

	CPrimaryCB* pPrimaryCB=CPrimaryCB::pHead;
	CPrimaryDB* pPrimaryDB=NULL;
	UWord located=0;

	if (pPrimaryCB) located=pPrimaryCB->Search(x,z,0,pPrimaryDB);

	//returns,
	//		located==0 ... block not found at any resolution
	//		located==1 ... block found but not at requested resolution
	//		located==2 ... block found at requested resolution

	if (located!=0)
	{
		//We have some data to extract altitude information from
		retVal.pData=pPrimaryDB->DataStart();
		retVal.dataLen=pPrimaryDB->DataLen();
		SLong xPos=(x>>9)&0xFF;
		SLong zPos=0xFF-(z>>9)&0xFF;
		SLong alt=0;
		pMigLandDecomp->FindRoughAlt(xPos,y,zPos,retVal,alt);
		return alt;
	}
	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAreaType
//Author		Paul.   
//Date			Fri 12 Jun 1998
//------------------------------------------------------------------------------
inline UByte CMigLand::GetAreaType() { return lastGroundHit&AT_MASK; }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	AttemptSeek
//------------------------------------------------------------------------------
bool CRectangularCache::AttemptSeek(SeekStrucP pSeek)
{
	LSFileBlockPtr reqFileP;

	reqFileP=new LSFileBlock(pSeek->fileNum,pSeek->dataLen,pSeek->seekPos,FALSE);

	UByte* srcP=(UByte*)reqFileP->GetData();

	if (srcP==NULL)
	{
		delete reqFileP;
		return false;
	}

	//data loaded and ready to process

	pDecomp->Skip(srcP,pSeek->firstSkipIndex);

	for (int i=0;i<pSeek->numBlocks;i++)
	{
		UByte* pdst=(UByte*)pSeek->blockPtrs[i];
		pDecomp->CopyData(srcP,pdst);
	}

	delete reqFileP;
	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	AddSeekRequest
//------------------------------------------------------------------------------
void CRectangularCache::AddSeekRequest(SeekStrucP pNewSeek)
{
	//debug code!
#if !defined(NDEBUG)
	for (int i=pNewSeek->numBlocks-1;i>=0;i--)
		if (pNewSeek->blockPtrs[i]==NULL)
			_asm {int 3}
#endif

	if (masterseeklist==NULL)
	{
		masterseeklist=new SeekStruc;
		*masterseeklist=*pNewSeek;
	}
	else
	{
		SeekStrucP pInsert=masterseeklist;

		while (pInsert->pNext!=NULL)
			pInsert=pInsert->pNext;

		pInsert->pNext=new SeekStruc;
		*(pInsert->pNext)=*pNewSeek;
		pInsert->pNext->pNext=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OneShotSeekRequest
//Author		Paul.   
//Date			Wed 3 Feb 1999
//------------------------------------------------------------------------------
void CRectangularCache::OneShotSeekRequest(SLong x,SLong z,SeekStrucP pSeek,DataRecord* pDR)
{
	CCacheBlock* pCache=CCacheBlock::pHead;
	CDataBlock* pData=NULL;
	if (pCache && pCache->Search(x,z,pData))
		return;

	static UByte destBuf[LARGEST_BLOCK_SIZE];
	LSFileBlockPtr reqFileP;
	reqFileP=new LSFileBlock(pSeek->fileNum,pSeek->dataLen,pSeek->seekPos,FALSE);
	UByte* pSrcData=(UByte*)reqFileP->GetData();
	pDecomp->Skip(pSrcData,pSeek->firstSkipIndex);
	pDecomp->CopyData(pSrcData,destBuf);
	UByte* pdb=destBuf;
	pDecomp->UnPack(x,z,pdb,pData);
	pDR->pData=pData->DataStart();
	pDR->dataLen=pData->DataLen();
	CPrimaryDB* pDB;
	pDecomp->MakeIntData(x,z,0,pDR->pData,pDB);
	pDR->pData=pDB->DataStart();
	pDR->dataLen=pDB->DataLen();

	delete reqFileP;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	ProcessSeekRequests2
//------------------------------------------------------------------------------
void CRectangularCache::ProcessSeekRequests2()
{
	if (masterseeklist==NULL)
		return;

	SeekStrucP pThisReq=masterseeklist;

	//attempt to get the data for this SeekStruc block

	if (AttemptSeek(pThisReq)==true)
	{
		//if this seek was a success then remove
		//the request from the queue

		masterseeklist=pThisReq->pNext;
		delete pThisReq;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSeekRequestsNF
//------------------------------------------------------------------------------
void CRectangularCache::ProcessSeekRequestsNF()
{
	while (masterseeklist!=NULL)
	{
		SeekStrucP pThisReq=masterseeklist;
		masterseeklist=pThisReq->pNext;

		LSFileBlockPtr reqFileP;

		reqFileP=new LSFileBlock(pThisReq->fileNum,pThisReq->dataLen,pThisReq->seekPos,FALSE);

		UByte* pSrcData=(UByte*)reqFileP->GetData();

		pDecomp->Skip(pSrcData,pThisReq->firstSkipIndex);

		for (int i=0;i<pThisReq->numBlocks;i++)
		{
			UByte* pdst=(UByte*)pThisReq->blockPtrs[i];
			pDecomp->CopyData(pSrcData,pdst);
		}

		delete reqFileP;

		delete pThisReq;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	CRectangularCache
//------------------------------------------------------------------------------
CRectangularCache::CRectangularCache(UWord dir)
{
	const SLong blksize=LARGEST_BLOCK_SIZE;

	fselitemp=NULL;
	masterseeklist=NULL;
	pingcounter=0;
	pingtimer=0;

	assert(blksize!=0&&"Try again!");

	pCBlkData=new SByteP[CENTER_WH*CENTER_WH];

	assert(pCBlkData!=NULL&&"Bugger!");

	for (int i=0;i<CENTER_WH;i++)
	{
		for (int j=0;j<CENTER_WH;j++)
		{
			pCBlkData[i*CENTER_WH+j]=new SByte[blksize];
			assert(pCBlkData[i*CENTER_WH+j]!=NULL&&"Bugger!");
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	~CRectangularCache
//------------------------------------------------------------------------------
CRectangularCache::~CRectangularCache()
{
	while (masterseeklist!=NULL)
	{
		SeekStrucP ptr=masterseeklist;
		masterseeklist=ptr->pNext;
		delete ptr;
	}
	for (int i=0;i<CENTER_WH;i++)
	{
		for (int j=0;j<CENTER_WH;j++)
		{
			delete[]pCBlkData[i*CENTER_WH+j];
		}
	}
	delete[]pCBlkData;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	ScrollSouth
//------------------------------------------------------------------------------
void CRectangularCache::ScrollSouth()
{
	SLong row,column;

	const SLong ROW_INDEX=(CENTER_WH-1)*CENTER_WH;

	//copy the bottom row into a temporary buffer

	SByteP temp[CENTER_WH];

	for (column=0;column<CENTER_WH;column++)
		temp[column]=pCBlkData[ROW_INDEX+column];

	//now scroll the main buffer down 1 row

	for (row=CENTER_WH-1;row>0;row--)
	{
		SLong rowIndex=row*CENTER_WH;

		for (column=0;column<CENTER_WH;column++)
			pCBlkData[rowIndex+column]=pCBlkData[rowIndex-CENTER_WH+column];
	}

	//now, refill the top line of the buffer with the row saved from the
	//bottom of the buffer

	for (column=0;column<CENTER_WH;column++)
		pCBlkData[column]=temp[column];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	ScrollNorth
//------------------------------------------------------------------------------
void CRectangularCache::ScrollNorth()
{
	SLong row,column,rowIndex;

	//copy the top row into a temporary buffer

	SByteP temp[CENTER_WH];

	for (column=0;column<CENTER_WH;column++)
		temp[column]=pCBlkData[column];

	//now scroll the main buffer up 1 row

	for (row=0;row<CENTER_WH-1;row++)
	{
		rowIndex=row*CENTER_WH;

		for (column=0;column<CENTER_WH;column++)
			pCBlkData[rowIndex+column]=pCBlkData[rowIndex+CENTER_WH+column];
	}

	//now, refill the bottom line of the buffer with the row saved from the
	//top of the buffer

	rowIndex=(CENTER_WH-1)*CENTER_WH;

	for (column=0;column<CENTER_WH;column++)
		pCBlkData[rowIndex+column]=temp[column];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	ScrollWest
//------------------------------------------------------------------------------
void CRectangularCache::ScrollWest()
{
	SLong row,column,rowIndex;

	//copy the left column into a temporary buffer

	SByteP temp[CENTER_WH];

	for (row=0;row<CENTER_WH;row++)
	{
		rowIndex=row*CENTER_WH;

		temp[row]=pCBlkData[rowIndex];
	}

	//now scroll the main buffer left 1 column

	for (column=0;column<CENTER_WH-1;column++)
	{
		for (row=0;row<CENTER_WH;row++)
		{
			rowIndex=row*CENTER_WH;
			pCBlkData[rowIndex+column]=pCBlkData[rowIndex+column+1];
		}
	}

	//now, refill the right column of the buffer with the column saved from the
	//left of the buffer

	for (row=0;row<CENTER_WH;row++)
	{
		rowIndex=(CENTER_WH-1)+(row*CENTER_WH);

		pCBlkData[rowIndex]=temp[row];
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	ScrollEast
//------------------------------------------------------------------------------
void CRectangularCache::ScrollEast()
{
	SLong row,column,rowIndex;

	//copy the right column into a temporary buffer

	SByteP temp[CENTER_WH];

	for (row=0;row<CENTER_WH;row++)
	{
		rowIndex=(CENTER_WH-1)+(row*CENTER_WH);

		temp[row]=pCBlkData[rowIndex];
	}

	//now scroll the main buffer right 1 column

	for (column=CENTER_WH-1;column>0;column--)
	{
		for (row=0;row<CENTER_WH;row++)
		{
			rowIndex=row*CENTER_WH;

			pCBlkData[rowIndex+column]=pCBlkData[rowIndex+column-1];
		}
	}

	//now, refill the left column of the buffer with the column saved from the
	//right of the buffer

	for (row=0;row<CENTER_WH;row++)
	{
		rowIndex=row*CENTER_WH;

		pCBlkData[rowIndex]=temp[row];
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	RecenterBuffer
//------------------------------------------------------------------------------
void CRectangularCache::RecenterBuffer(SLong oldx,SLong oldz,SLong newx,SLong newz)
{
	SLong newxindex,newzindex;

	newxindex=(newx-oldx)/BLOCK_WIDTH;
	newzindex=(newz-oldz)/BLOCK_WIDTH;

	if (newxindex>0)		while (newxindex--)	{ScrollWest();}
	else if (newxindex<0)	while (newxindex++)	{ScrollEast();}
	if (newzindex>0)		while (newzindex--)	{ScrollSouth();}
	else if (newzindex<0)	while (newzindex++)	{ScrollNorth();}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildNorthRequests
//------------------------------------------------------------------------------
void CRectangularCache::BuildNorthRequests()
{
	COORDS3D base=bufferbase;

	base.Z-=(CENTER_WH-1)*BLOCK_WIDTH;

	ULong farX=base.X+((CENTER_WH-1)*BLOCK_WIDTH);

	bool fTwoStrips=false;

	ULong westXIndex=(base.X>>24)&0x7;
	ULong eastXIndex=(farX>>24)&0x7;

	//test whether one or two east-west strips are needed

	if (eastXIndex!=westXIndex) fTwoStrips=true;

	SByte** pDest=pCBlkData+(CENTER_WH*(CENTER_WH-1));

	for (int i=0;i<CENTER_WH;i++)
	{
		SByte** pLocalDest=pDest;
		pDest-=CENTER_WH;

		SeekStruc newSeek;

		SLong localX,localZ;
		localX=base.X>>17;
		localZ=base.Z>>17;
		base.Z+=BLOCK_WIDTH;

		if (!fTwoStrips)
		{
			ULong index,skipCnt;
			index=_northIndex(localX,localZ);
			skipCnt=0x7F&localX;

			SInfo info=pNorth[index];
			newSeek.fileNum=FIL_AREAN_NUM;
			newSeek.seekPos=info.offset;
			newSeek.dataLen=info.length;
			newSeek.firstSkipIndex=skipCnt;
			newSeek.numBlocks=CENTER_WH;
			SByte** pbptrs=newSeek.blockPtrs;
			for (int j=0;j<CENTER_WH;j++) *pbptrs++=*pLocalDest++;

			AddSeekRequest(&newSeek);
		}
		else
		{
			ULong index,skipCnt,numBlocks;
			index=_northIndex(localX,localZ);
			skipCnt=0x7F&localX;
			numBlocks=(128-skipCnt);

			SInfo info=pNorth[index];
			newSeek.fileNum=FIL_AREAN_NUM;
			newSeek.seekPos=info.offset;
			newSeek.dataLen=info.length;
			newSeek.firstSkipIndex=skipCnt;
			newSeek.numBlocks=numBlocks;
			SByte** pbptrs=newSeek.blockPtrs;
			for (int j=0;j<numBlocks;j++) *pbptrs++=*pLocalDest++;

			AddSeekRequest(&newSeek);

			numBlocks=CENTER_WH-numBlocks;
			info=pNorth[index+1];
			newSeek.seekPos=info.offset;
			newSeek.dataLen=info.length;
			newSeek.firstSkipIndex=0;
			newSeek.numBlocks=numBlocks;
			pbptrs=newSeek.blockPtrs;
			for (j=0;j<numBlocks;j++) *pbptrs++=*pLocalDest++;

			AddSeekRequest(&newSeek);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildEastRequests
//------------------------------------------------------------------------------
void CRectangularCache::BuildEastRequests()
{
	COORDS3D base=bufferbase;

	ULong farZ=bufferbase.Z-(CENTER_WH-1)*BLOCK_WIDTH;

	bool fTwoStrips=false;

	ULong southZIndex=(farZ>>24)&0x07;
	ULong northZIndex=(base.Z>>24)&0x07;

	//test whether one or two north-south strips are needed

	if (northZIndex!=southZIndex) fTwoStrips=true;

	SByte** pDest=pCBlkData;

	for (int i=0;i<CENTER_WH;i++)
	{
		SByte** pLocalDest=pDest;
		pDest++;

		SeekStruc newSeek;
		SeekStruc newSeek2;

		SLong localX,localZ;
		localX=base.X>>17;
		localZ=base.Z>>17;
		base.X+=BLOCK_WIDTH;

		if (!fTwoStrips)
		{
			ULong index,skipCnt;

			index=_eastIndex(localX,localZ);
			skipCnt=0x7F-(localZ&0x7F);							//PD 29Oct98

			SInfo info=pEast[index];
			newSeek.fileNum=FIL_AREAE_NUM;
			newSeek.seekPos=info.offset;
			newSeek.dataLen=info.length;
			newSeek.firstSkipIndex=skipCnt;
			newSeek.numBlocks=CENTER_WH;
			SByte** pbptrs=newSeek.blockPtrs;
			for (int j=0;j<CENTER_WH;j++)
			{
				*pbptrs++=*pLocalDest;
				pLocalDest+=CENTER_WH;
			}
			AddSeekRequest(&newSeek);
		}
		else
		{
			ULong index,skipCnt,numBlocks;
			index=_eastIndex(localX,localZ);
			skipCnt=0x7F-(localZ&0x7F);							//PD 29Oct98
			numBlocks=128-skipCnt;

			SInfo info=pEast[index];
			newSeek.fileNum=FIL_AREAE_NUM;
			newSeek.seekPos=info.offset;
			newSeek.dataLen=info.length;
			newSeek.firstSkipIndex=skipCnt;
			newSeek.numBlocks=numBlocks;
			SByte** pbptrs=newSeek.blockPtrs;
			for (int j=0;j<numBlocks;j++)
			{
				*pbptrs++=*pLocalDest;
				pLocalDest+=CENTER_WH;
			}
			numBlocks=CENTER_WH-numBlocks;
			info=pEast[index+1];
			newSeek2.fileNum=FIL_AREAE_NUM;
			newSeek2.seekPos=info.offset;
			newSeek2.dataLen=info.length;
			newSeek2.firstSkipIndex=0;
			newSeek2.numBlocks=numBlocks;
			pbptrs=newSeek2.blockPtrs;
			for (j=0;j<numBlocks;j++)
			{
				*pbptrs++=*pLocalDest;
				pLocalDest+=CENTER_WH;
			}
			AddSeekRequest(&newSeek2);
			AddSeekRequest(&newSeek);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildSouthRequests
//------------------------------------------------------------------------------
void CRectangularCache::BuildSouthRequests()
{
	BuildNorthRequests();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildWestRequests
//------------------------------------------------------------------------------
void CRectangularCache::BuildWestRequests()
{
	BuildEastRequests();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	BigRebuild
//------------------------------------------------------------------------------
void CRectangularCache::BigRebuild()
{
	//prepare to recenter buffer

	SLong lastbuffx,lastbuffz;

	lastbuffx=bufferbase.X; lastbuffz=bufferbase.Z;

	//currentdirection has been updated already

	WhichWay whichway=currentdirection;

	FileNum	 whichfile;

	COORDS3D coords=fselitemp->World;

	coords.X&=0xFFFE0000;
	coords.Z&=0xFFFE0000;

	bufferbase.X=coords.X-(CENTER_HALF*BLOCK_WIDTH);
	bufferbase.Z=coords.Z+(CENTER_HALF*BLOCK_WIDTH);
	RecenterBuffer(	lastbuffx,lastbuffz,
					bufferbase.X,bufferbase.Z);

	//Select file based on the heading of the input item

	BuildNorthRequests();

	switch (whichway)
	{
	case WW_north:
	whichfile=FIL_AREAN_NUM;
	break;

	case WW_east:
	whichfile=FIL_AREAE_NUM;
	break;

	case WW_south:
	whichfile=FIL_AREAN_NUM;
	break;

	case WW_west:
	whichfile=FIL_AREAE_NUM;
	break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	StillGoingNorth
//------------------------------------------------------------------------------
void CRectangularCache::StillGoingNorth()
{
	ScrollSouth();
 	
	//add request for a new strip of data to be loaded

	bufferbase.Z+=BLOCK_WIDTH;

	COORDS3D base=bufferbase;

	ULong farX=base.X+((CENTER_WH-1)*BLOCK_WIDTH);

	ULong westXIndex=(base.X>>24)&0x7;
	ULong eastXIndex=(farX>>24)&0x7;

	//test whether one or two east-west strips are needed

	bool fTwoStrips=false;

	if (eastXIndex!=westXIndex) fTwoStrips=true;

	SByte** pDest=pCBlkData;

	SeekStruc newSeek;

	SLong localX,localZ;
	localX=base.X>>17;
	localZ=base.Z>>17;

	if (!fTwoStrips)
	{
		ULong index,skipCnt;
		index=_northIndex(localX,localZ);
		skipCnt=0x7F&localX;

		SInfo info=pNorth[index];
		newSeek.fileNum=FIL_AREAN_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=CENTER_WH;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<CENTER_WH;j++) *pbptrs++=*pDest++;

		AddSeekRequest(&newSeek);
	}
	else
	{
		ULong index,skipCnt,numBlocks;
		index=_northIndex(localX,localZ);
		skipCnt=0x7F&localX;
		numBlocks=(128-skipCnt);

		SInfo info=pNorth[index];
		newSeek.fileNum=FIL_AREAN_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=numBlocks;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<numBlocks;j++) *pbptrs++=*pDest++;

		AddSeekRequest(&newSeek);

		numBlocks=CENTER_WH-numBlocks;
		info=pNorth[index+1];
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=0;
		newSeek.numBlocks=numBlocks;
		pbptrs=newSeek.blockPtrs;
		for (j=0;j<numBlocks;j++) *pbptrs++=*pDest++;

		AddSeekRequest(&newSeek);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	StillGoingEast
//------------------------------------------------------------------------------
void CRectangularCache::StillGoingEast()
{
	ScrollWest();
 	
	bufferbase.X+=BLOCK_WIDTH;

	//add request for a new strip of data to be loaded

	COORDS3D base=bufferbase;
	base.X+=((CENTER_WH-1)*BLOCK_WIDTH);

	ULong farZ=bufferbase.Z-(CENTER_WH-1)*BLOCK_WIDTH;

	ULong southZIndex=(farZ>>24)&0x7;
	ULong northZIndex=(base.Z>>24)&0x7;

	//test whether one or two east-west strips are needed

	bool fTwoStrips=false;

	if (northZIndex!=southZIndex) fTwoStrips=true;

	SByte** pDest=pCBlkData+CENTER_WH-1;	//(CENTER_WH*CENTER_WH)-1;

	SeekStruc newSeek;

	SLong localX,localZ,otherZ;
	localX=base.X>>17;
	localZ=base.Z>>17;
	otherZ=farZ>>17;

	if (!fTwoStrips)
	{
		ULong index,skipCnt;
		index=_eastIndex(localX,localZ);
		skipCnt=0x7F-(localZ&0x7F);	//localZ&0x7F;

		SInfo info=pEast[index];
		newSeek.fileNum=FIL_AREAE_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=CENTER_WH;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<CENTER_WH;j++)
		{
			*pbptrs++=*pDest;
			pDest+=CENTER_WH;
		}
		AddSeekRequest(&newSeek);
	}
	else
	{
		ULong index,skipCnt,numBlocks;
		index=_eastIndex(localX,localZ);
		skipCnt=0x7F-(localZ&0x7F);	//0x7F&localZ;
		numBlocks=(128-skipCnt);

		SInfo info=pEast[index];
		newSeek.fileNum=FIL_AREAE_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=numBlocks;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<numBlocks;j++)
		{
			*pbptrs++=*pDest;
			pDest+=CENTER_WH;
		}
		AddSeekRequest(&newSeek);

		numBlocks=CENTER_WH-numBlocks;
//		info=pEast[index+1];
		index=_eastIndex(localX,otherZ);
		info=pEast[index];
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=0;
		newSeek.numBlocks=numBlocks;
		pbptrs=newSeek.blockPtrs;
		for (j=0;j<numBlocks;j++)
		{
			*pbptrs++=*pDest;
			pDest+=CENTER_WH;
		}
		AddSeekRequest(&newSeek);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	StillGoingSouth
//------------------------------------------------------------------------------
void CRectangularCache::StillGoingSouth()
{
	ScrollNorth();
 	
	bufferbase.Z-=BLOCK_WIDTH;

	COORDS3D base=bufferbase;

	ULong farX=base.X+((CENTER_WH-1)*BLOCK_WIDTH);

	ULong westXIndex=(base.X>>24)&0x7;
	ULong eastXIndex=(farX>>24)&0x7;

	//test whether one or two east-west strips are needed

	bool fTwoStrips=false;

	if (eastXIndex!=westXIndex) fTwoStrips=true;

	SByte** pDest=pCBlkData+(CENTER_WH-1)*CENTER_WH;

	SeekStruc newSeek;

	SLong localX,localZ;
	base.Z-=(CENTER_WH-1)*BLOCK_WIDTH;
	localX=base.X>>17;
	localZ=base.Z>>17;

	if (!fTwoStrips)
	{
		ULong index,skipCnt;
		index=_northIndex(localX,localZ);
		skipCnt=0x7F&localX;

		SInfo info=pNorth[index];
		newSeek.fileNum=FIL_AREAN_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=CENTER_WH;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<CENTER_WH;j++) *pbptrs++=*pDest++;

		AddSeekRequest(&newSeek);
	}
	else
	{
		ULong index,skipCnt,numBlocks;
		index=_northIndex(localX,localZ);
		skipCnt=0x7F&localX;
		numBlocks=(128-skipCnt);

		SInfo info=pNorth[index];
		newSeek.fileNum=FIL_AREAN_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=numBlocks;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<numBlocks;j++) *pbptrs++=*pDest++;

		AddSeekRequest(&newSeek);

		numBlocks=CENTER_WH-numBlocks;
		info=pNorth[index+1];
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=0;
		newSeek.numBlocks=numBlocks;
		pbptrs=newSeek.blockPtrs;
		for (j=0;j<numBlocks;j++) *pbptrs++=*pDest++;

		AddSeekRequest(&newSeek);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	StillGoingWest
//------------------------------------------------------------------------------
void CRectangularCache::StillGoingWest()
{
	ScrollEast();
 	
	//add request for a new strip of data to be loaded

	bufferbase.X-=BLOCK_WIDTH;

	COORDS3D base=bufferbase;

	ULong farZ=bufferbase.Z-(CENTER_WH-1)*BLOCK_WIDTH;

	ULong southZIndex=(farZ>>24)&0x7;
	ULong northZIndex=(base.Z>>24)&0x7;

	//test whether one or two east-west strips are needed

	bool fTwoStrips=false;

	if (northZIndex!=southZIndex) fTwoStrips=true;

	SByte** pDest=pCBlkData;		//+CENTER_WH-1;	//(CENTER_WH*(CENTER_WH-1));

	SeekStruc newSeek;

	SLong localX,localZ,otherZ;
	localX=base.X>>17;
	localZ=base.Z>>17;
	otherZ=farZ>>17;

	if (!fTwoStrips)
	{
		ULong index,skipCnt;
		index=_eastIndex(localX,localZ);
		skipCnt=0x7F-(localZ&0x7F);	//localZ&0x7F;

		SInfo info=pEast[index];
		newSeek.fileNum=FIL_AREAE_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=CENTER_WH;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<CENTER_WH;j++)
		{
			*pbptrs++=*pDest;
			pDest+=CENTER_WH;
		}
		AddSeekRequest(&newSeek);
	}
	else
	{
		ULong index,skipCnt,numBlocks;
		index=_eastIndex(localX,localZ);
		skipCnt=0x7F-(localZ&0x7F);	//0x7F&localZ;
		numBlocks=(128-skipCnt);

		SInfo info=pEast[index];
		newSeek.fileNum=FIL_AREAE_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=numBlocks;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<numBlocks;j++)
		{
			*pbptrs++=*pDest;
			pDest+=CENTER_WH;
		}
		AddSeekRequest(&newSeek);

		numBlocks=CENTER_WH-numBlocks;
//		info=pEast[index+1];
		index=_eastIndex(localX,otherZ);
		info=pEast[index];
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=0;
		newSeek.numBlocks=numBlocks;
		pbptrs=newSeek.blockPtrs;
		for (j=0;j<numBlocks;j++)
		{
			*pbptrs++=*pDest;
			pDest+=CENTER_WH;
		}
		AddSeekRequest(&newSeek);
	}
/*
	SeekStruc newSeek;
	SeekStruc newSeek2;

	SLong localX,localZ;
	localX=base.X>>17;
	localZ=base.Z>>17;

	if (!fTwoStrips)
	{
		ULong index,skipCnt;
		index=_westIndex(localX,localZ);
		skipCnt=localZ&0x7F;

		SInfo info=pWest[index];
		newSeek.fileNum=FIL_AREAW_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=CENTER_WH;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<CENTER_WH;j++)
		{
			*pbptrs++=*pDest;
//			pDest-=CENTER_WH;
			pDest+=CENTER_WH;
		}
		AddSeekRequest(&newSeek);
	}
	else
	{
		ULong index,skipCnt,numBlocks;
		index=_westIndex(localX,localZ);
		skipCnt=localZ&0x7F;
		numBlocks=128-skipCnt;

		SInfo info=pWest[index];
		newSeek.fileNum=FIL_AREAW_NUM;
		newSeek.seekPos=info.offset;
		newSeek.dataLen=info.length;
		newSeek.firstSkipIndex=skipCnt;
		newSeek.numBlocks=numBlocks;
		SByte** pbptrs=newSeek.blockPtrs;
		for (int j=0;j<numBlocks;j++)
		{
			*pbptrs++=*pDest;
//			pDest-=CENTER_WH;
			pDest+=CENTER_WH;
		}

		numBlocks=CENTER_WH-numBlocks;
		info=pWest[index-1];
		newSeek2.fileNum=FIL_AREAW_NUM;
		newSeek2.seekPos=info.offset;
		newSeek2.dataLen=info.length;
		newSeek2.firstSkipIndex=0;
		newSeek2.numBlocks=numBlocks;
		pbptrs=newSeek2.blockPtrs;
		for (j=0;j<numBlocks;j++)
		{
			*pbptrs++=*pDest;
//			pDest-=CENTER_WH;
			pDest+=CENTER_WH;
		}
		AddSeekRequest(&newSeek2);
		AddSeekRequest(&newSeek);
	}
	TEMP*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	NowGoingNorth
//------------------------------------------------------------------------------
void CRectangularCache::NowGoingNorth()
{
	currentdirection=WW_north;
	currentfilenum=FIL_AREAN_NUM;
	BigRebuild();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	NowGoingEast
//------------------------------------------------------------------------------
void CRectangularCache::NowGoingEast()
{
	currentdirection=WW_east;
	currentfilenum=FIL_AREAE_NUM;
	BigRebuild();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	NowGoingSouth
//------------------------------------------------------------------------------
void CRectangularCache::NowGoingSouth()
{
	currentdirection=WW_south;
	currentfilenum=FIL_AREAN_NUM;
	BigRebuild();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	NowGoingWest
//------------------------------------------------------------------------------
void CRectangularCache::NowGoingWest()
{
	currentdirection=WW_west;
	currentfilenum=FIL_AREAE_NUM;
	BigRebuild();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDirectionFlags
//------------------------------------------------------------------------------
CRectangularCache::WhichWay CRectangularCache::GetDirectionFlags()
{
	UWord		lhdg;
	WhichWay 	whichway;

	lhdg = (UWord )fselitemp->hdg;

	if (lhdg<=0x2000 || lhdg>0xE000)
		whichway=WW_north;
	else
	{
		if (lhdg>0x2000 && lhdg<=0x6000)
 			whichway=WW_east;
		else
		{
			if (lhdg>0x6000 && lhdg<=0xA000)
				whichway=WW_south;
			else
				whichway=WW_west;
		}
	}
	return (whichway);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDirectionFlags2
//------------------------------------------------------------------------------
CRectangularCache::WhichWay CRectangularCache::GetDirectionFlags2()
{
	SLong xindex,zindex;
	COORDS3D lcoords;

	lcoords=fselitemp->World;
	xindex=(lcoords.X>>8+(int)XZ_COL_SCALE) - (bufferbase.X>>8+(int)XZ_COL_SCALE);
	zindex=(bufferbase.Z>>8+(int)XZ_COL_SCALE) - (lcoords.Z>>8+(int)XZ_COL_SCALE);

	if (zindex<=MIN_BOUND)	return(WW_north);
	if (zindex>=MAX_BOUND)	return(WW_south);
	if (xindex<=MIN_BOUND)	return(WW_west);

	return(WW_east);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	ProcessSeekRequests
// Returns		true if the buffer is still okay to use..
//------------------------------------------------------------------------------
bool CRectangularCache::ProcessSeekRequests()
{
	if (v_p && v_p->Accel() && (v_p->drawSpecialFlags&VIEW_SPECIAL_MAP))
		return true;

	//no new requests until the last lot have
	//been loaded

	if (masterseeklist!=NULL)
	{
		pingtimer=0;
		pingcounter=0;

//		if (v_p && v_p->Accel())
//			ProcessSeekRequestsNF();
//		else
		{
			ProcessSeekRequests2();
			return masterseeklist==NULL?true:false;
		}
	}

	SLong xindex,zindex;
	COORDS3D lcoords,bcoords;

	lcoords=fselitemp->World;
	bcoords=bufferbase;

	//if the item is less than 6 blocks away
	//from the edge of the 33x33 buffer then don't
	//do anything

	lcoords.X&=0xFFFE0000;
	lcoords.Z&=0xFFFE0000;

	xindex=(lcoords.X-bcoords.X)/BLOCK_WIDTH;
	zindex=(bcoords.Z-lcoords.Z)/BLOCK_WIDTH;

	if (xindex>MIN_BOUND && xindex<MAX_BOUND &&
		zindex>MIN_BOUND && zindex<MAX_BOUND)
	{
//dead		FILEMAN.pingCD();	//let the ping code do the counting!
		return true;
	}

	//Gets direction based on the nearest boundary now

	WhichWay whichway=GetDirectionFlags2();

	if (whichway==currentdirection)
	{
		switch (whichway)
		{
		case WW_north:
		StillGoingNorth();
		break;
		case WW_east:
		StillGoingEast();
		break;
		case WW_south:
		StillGoingSouth();
		break;
		case WW_west:
		StillGoingWest();
		break;
		}
	}
	else
	{
		switch (whichway)
		{
		case WW_north:
		NowGoingNorth();
		break;
		case WW_east:
		NowGoingEast();
		break;
		case WW_south:
		NowGoingSouth();
		break;
		case WW_west:
		NowGoingWest();
		break;
		}
	}
	if (masterseeklist!=NULL && v_p && v_p->Accel())
		ProcessSeekRequestsNF();

	return masterseeklist==NULL?true:false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetData
//------------------------------------------------------------------------------
UByte* CRectangularCache::GetData(SLong x,SLong z)
{
	UByte*		retval = NULL;

	COORDS3D	lcoords;
	COORDS3D	bcoords=bufferbase;

	lcoords.X=x;
	lcoords.Y=0;
	lcoords.Z=z;

	lcoords.X&=0xFFFE0000;
	lcoords.Z&=0xFFFE0000;

	SLong xindex,zindex;

	xindex=(lcoords.X-bcoords.X)/BLOCK_WIDTH;
	zindex=(bcoords.Z-lcoords.Z)/BLOCK_WIDTH;

	if (xindex<0 || xindex>=CENTER_WH)	return(retval);
	if (zindex<0 || zindex>=CENTER_WH)	return(retval);

	retval=(UByte*)pCBlkData[xindex+(CENTER_WH*zindex)];

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BigInit
//Author		Paul    
//Date			Mon 28 Sep 1998
//------------------------------------------------------------------------------
void CRectangularCache::BigInit()
{
	FileNum whichfile;
	WhichWay whichway=GetDirectionFlags();

	COORDS3D coords=fselitemp->World;

	currentdirection=whichway;

	coords.X&=0xFFFE0000;
	coords.Z&=0xFFFE0000;

	bufferbase.X=coords.X-(CENTER_HALF*BLOCK_WIDTH);
	bufferbase.Z=coords.Z+(CENTER_HALF*BLOCK_WIDTH);

	//Select file based on the heading of the input item
	//Don't forget North is West, West is South, South is East, 
	//East is North, Up is Down, Down is Up and Oranges are purple!!!!!

//	switch (whichway)
//	{
//	case WW_north:
		whichfile = FIL_AREAN_NUM;
		BuildNorthRequests();
//		break;
//
//	case WW_east:
//		whichfile = FIL_AREAE_NUM;
//		BuildEastRequests();
//		break;
//
//	case WW_south:
//		whichfile = FIL_AREAS_NUM;
//		BuildSouthRequests();
//		break;
//
//	case WW_west:
//		whichfile = FIL_AREAW_NUM;
//		BuildWestRequests();
//		break;
//	}
	currentfilenum = whichfile;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetViewpoint
//Author		Paul    
//------------------------------------------------------------------------------
void CMigLand::SetViewpoint(MovingItem* ip)
{
	pMigFile->SetViewpoint(ip);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSeekRequests
//Author		Paul    
//------------------------------------------------------------------------------
bool CMigLand::ProcessSeekRequests()
{
	return pMigFile->ProcessSeekRequests();
}










