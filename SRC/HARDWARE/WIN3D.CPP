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
//Filename       win3d.cpp
//System         
//Author         Paul
//Date           Thu 30 Jan 1997
//Description    
//------------------------------------------------------------------------------

#define INWIN3D
#include	"DosDefs.h"
#define F_GRAFIX
#define F_SOUNDS
#define F_BATTLE
#include	"files.g"											//PD 23Feb98
#include	"myError.h"
#include	"Mytime.h"
#include	"worldinc.h"
#include	"landscap.h"
#include	"migland.h"
#include	"savegame.h"
#include 	"missman2.h"										//PD 03Jun97
#include	"viewsel.h"
#include	"vertex.h"
#include	"3ddefs.h"
#include	"3dcode.h"
#include	<stdio.h>
#include	"mymath.h"
#include	"hdata.h"											//PD 26Nov97
#include	"hardpasm.h"
#include	"win3d.h"
#include	"Display.h"
#include	"gameset.h"
#include	"tilemake.h"
#include "areatype.h"
#include "prof.h"

//#define DDSCAPS_LOCALVIDMEM 0x10000000l
#define DDSCAPS_LOCALVIDMEM 0x00000000l

UByte videoBuffer =0;	//OFF==0 ON==1;

const SLong _ditherMapScale=1;
bool mono3d=false;
static double gamma_values[]={0.8, 0.9, 1.0, 1.015, 1.03,};

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

inline void ZeroMem(void* pp,ULong ll)
{
	_asm{
	push eax
	push edi
	push ebx
	push ecx
	xor	eax,eax;
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
	pop ecx
	pop ebx
	pop edi
	pop eax
	}
}

typedef	struct _DirectDraw DirectD,*DirectDP;

#include	"Win3d.h"

#include	"imagemap.g"

const Float Max_Z_Scale	= 1.0;

//replacement structure for D3DTLVERTEX & D3DCOLOR

UByte plainShadeFlag;

BITABLE(CLIPFLAGS3D);

#define	FAR_RHW_VALUE	0.0										//PD 17Nov97
#define	NEAR_RHW_VALUE	1.0										//PD 17Nov97

#define FAR_SZ_VALUE	1.0										//PD 17Nov97

extern	void fpSqrt(Float& );
#ifdef __WATCOMC__
#pragma aux fpSqrt = \
"	fld 	qword ptr ds:[esi]	"\
"	fsqrt						"\
"	fstp	qword ptr ds:[esi]	"\
parm	[esi]
#else
#ifdef __MSVC__
inline Float fpSqrt(Float num)
{
    __asm
    {
		fld 	num
		fsqrt
		fstp	num
    }
	return num;
}

#endif
#endif

extern	void fpSin_Cos(Angles angle, Float& sin_ang, Float& cos_ang);
#ifdef __WATCOMC__
#pragma	aux	 fpSin_Cos =					\
"		and		eax,0x0000FFFF				"\
"		fldpi								"\
"		push	eax							"\
"		fild	dword ptr ss:[esp]			"\
"		fmulp	st(1),st					"\
"		mov		dword ptr ss:[esp],32768	"\
"		fild	dword ptr ss:[esp]			"\
"		fdivp	st(1),st					"\
"		fsincos								"\
"		fstp	qword ptr ds:[ebx]			"\
"		fstp	qword ptr ds:[edx]			"\
"		add		esp,4						"\
parm	[eax] [edx] [ebx]					\
modify	[eax]
#else
#ifdef __MSVC__
inline void fpSin_Cos(Angles angle, Float& sin_ang, Float& cos_ang)
{
   __asm
    {
		push eax
		push edx
		push ebx
	   mov eax,angle;
	   mov edx,sin_ang;
	   mov ebx,cos_ang;
		and		eax,0x0000FFFF;
		fldpi;
		push	eax;
		fild	dword ptr ss:[esp];
		fmulp	st(1),st;
		mov		dword ptr ss:[esp],32768;
		fild	dword ptr ss:[esp];
		fdivp	st(1),st;
		fsincos;
		fstp	qword ptr ds:[ebx];
		fstp	qword ptr ds:[edx];
		add		esp,4;
		pop ebx
		pop edx
		pop eax
    }
}

#endif
#endif


#ifdef __WATCOMC__

extern	void	ASM_Blat2(void*,void*,ULong);
//
// This blat attempts to get at least one register on a longword boundary.
// As it is often used for screen copying, I have chosen the target.
// This will reduce bus accesses a little.
//
#pragma	aux	ASM_Blat2	=			\
		"mov	ecx,4"				\
		"sub	ecx,edi"			\
		"and	ecx,3"				\
		"sub	ebx,ecx"			\
		"rep	movsb"				\
		"mov	ecx,ebx"			\
		"shr	ecx,2"				\
		"rep	movsd"				\
		"and	ebx,3"				\
		"mov	ecx,ebx"			\
		"rep	movsb"				\
		parm	[esi] [edi] [ebx]	\
		modify	[ecx esi edi]

#endif
#ifdef __MSVC__
inline void	ASM_Blat2(void* src,void* dst,ULong len)
{
	_asm{
	push	eax
	push	ecx
	push	esi
	push	edi
	mov		esi,src
	mov		edi,dst
	mov		ebx,len
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
	pop		edi
	pop		esi
	pop		ecx
	pop		eax
	}
}
#endif

UByte lastFogRed,lastFogGreen,lastFogBlue;

//inline void Flush(LPD3DDEVICE lpD3DDevice)
//{
//	lpD3DDevice->BeginScene();
//	lpD3DDevice->EndScene();
//}

#if !defined(NDEBUG)
#define FLUSH(p1) Flush(p1)
#else
#define FLUSH(p1)
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GreyPalette
//Author		Paul.   
//Date			Wed 3 Mar 1999
//------------------------------------------------------------------------------
void GreyPalette(UByte* rgb)
{
	if (mono3d)
	{
 		UByte r=rgb[0];
		r=r<rgb[1]?rgb[1]:r;
		r=r<rgb[2]?rgb[2]:r;
		rgb[0]=rgb[1]=rgb[2]=r;
	}
}
void GreyPalette(UByte* r,UByte* g,UByte* b)
{
	if (mono3d)
	{
		UByte local[3];
		local[0]=*r;
		local[1]=*g;
		local[2]=*b;
		GreyPalette(local);
		*r=local[0];
		*g=local[0];
		*b=local[0];
	}
}

const D3DCOLOR specularNULL=RGBA_MAKE(0x00,0x00,0x00,0xFF);
const D3DCOLOR White=RGBA_MAKE(0xff,0xff,0xff,0xFF);
D3DCOLOR AmbientLight=White;

class CPolyTree
{
	enum {POLY_LIMIT=384,BUFFER_SIZE=65536*4};
	struct SPolyRec
	{
		SPolyRec *lptr,*rptr;
		Float sort_z;
		UByte globalAlphaValue;
		UByte isLightShaded;
		UByte isTranspFade;
		UByte fogRed,fogGreen,fogBlue;
		UByte shadeRed,shadeGreen,shadeBlue;
		POLYTYPE poly_type;
	};

	UByte* pBufferSpace;
	UByte* pBufferCur;
	SLong ppf;
	SPolyRec* pHead;
	direct_3d* pd3d;
	struct _DirectDraw* pDD;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiscardDistantPoly
//Author		Paul.   
//Date			Fri 11 Dec 1998
//------------------------------------------------------------------------------
	bool DiscardDistantPoly(Float sz)
	{
		SPolyRec *pLast,*pScan;
		pScan=pHead;
		pLast=NULL;

		while (pScan->rptr!=NULL) 
		{
			pLast=pScan;
			pScan=pScan->rptr;
		}
		//pScan is a pointer to the furthest poly away so far

		if (sz>pScan->sort_z)	//if the new poly is further away than the
			return false;		//new one then return false to indicate that the
								//new poly should be discarded

		//check for any polys closer than pScan
		if (pScan->lptr!=NULL)
		{
			if (pLast==NULL)	pHead=pScan->lptr;
			else				pLast->rptr=pScan->lptr;
		}
		else					pLast->rptr=NULL;
		return true;
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPolyRec
//Author		Paul.   
//Date			Fri 11 Dec 1998
//------------------------------------------------------------------------------
	SPolyRec* GetPolyRec(LPPOLYTYPE pPoly)
	{
		//don't forget to NULL the left & right pointers
		//					generate a z sort value
		//					backup the vertices of the poly

		SPolyRec* ret_val;
		vertex *vertex_ptr,**vertex_ptr_ptr;
		vertex *source_ptr,**source_ptr_ptr;
		void *void_ptr;

		//allocates RAM for the following data structure...
		//
		//	A SPolyRec structure followed immediately by an array of pointers
		//	to the polygons vertices followed by the polygon 
		//	vertices themselves.

		const ULong _SpaceToAllocate=sizeof(SPolyRec)+pPoly->points*(sizeof(vertex)+sizeof(vertex*));
		UByte* _BackupBuffer=pBufferCur;

		if (ULong(pBufferCur)+_SpaceToAllocate-ULong(pBufferSpace)>=BUFFER_SIZE)
			return NULL;

		void_ptr=(void*)pBufferCur;
		pBufferCur+=_SpaceToAllocate;

		ret_val=(SPolyRec*)void_ptr;
		ret_val->lptr=ret_val->rptr=NULL;
		ret_val->poly_type=*pPoly;

		ret_val->poly_type.lplpVertices=
		vertex_ptr_ptr=
		(vertex**)(ULong(ret_val)+sizeof(SPolyRec));

		vertex_ptr=
		(vertex*)(ULong(ret_val)+sizeof(SPolyRec)+ret_val->poly_type.points*sizeof(vertex*));

		source_ptr_ptr=pPoly->lplpVertices;

		UWord andClip=CF3D_ALL;

		Float far_z=0;

		for (SLong x=0;x<pPoly->points;x++)
		{
			source_ptr=*source_ptr_ptr++;
			vertex_ptr_ptr[0]=vertex_ptr;
			vertex_ptr[0]=source_ptr[0];
			if (vertex_ptr[0].bz.f>far_z) far_z=vertex_ptr[0].bz.f;
			vertex_ptr++;
			vertex_ptr_ptr++;
			andClip&=source_ptr[0].clipFlags;
		}

		if (andClip!=CF3D_NULL)
		{
			pBufferCur=_BackupBuffer;
			return NULL;
		}

		ret_val->sort_z=far_z;	//source_ptr[-1].bz.f;

		ppf++;

		if (ppf>POLY_LIMIT && DiscardDistantPoly(ret_val->sort_z)==false)
		{
			pBufferCur=_BackupBuffer;
			return NULL;
		}

		ret_val->globalAlphaValue=pd3d->globalAlphaValue;
		ret_val->isTranspFade=pd3d->isTranspFade?1:0;
		ret_val->isLightShaded=pd3d->isLightShaded?1:0;
		ret_val->fogRed=lastFogRed;
		ret_val->fogGreen=lastFogGreen;
		ret_val->fogBlue=lastFogBlue;
		ret_val->shadeRed=pd3d->vShadeRed;
		ret_val->shadeGreen=pd3d->vShadeGreen;
		ret_val->shadeBlue=pd3d->vShadeBlue;
		return ret_val;
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderRecurse
//Author		Paul.   
//Date			Mon 14 Dec 1998
//------------------------------------------------------------------------------
	void RenderRecurse(SPolyRec* next_index)
	{
		SPolyRec* scan_index;

		do
		{
			scan_index=next_index;

			if ((next_index=scan_index->rptr)!=NULL)
				RenderRecurse(next_index);

			pd3d->isTranspFade=scan_index->isTranspFade?true:false;
			pd3d->isLightShaded=scan_index->isLightShaded?true:false;
			pd3d->globalAlphaValue=scan_index->globalAlphaValue;

			pd3d->vShadeRed=scan_index->shadeRed;
			pd3d->vShadeGreen=scan_index->shadeGreen;
			pd3d->vShadeBlue=scan_index->shadeBlue;
			AmbientLight=RGBA_MAKE(scan_index->shadeRed,scan_index->shadeGreen,scan_index->shadeBlue,0xFF);

			if (scan_index->fogRed!=lastFogRed || 
				scan_index->fogGreen!=lastFogGreen ||
				scan_index->fogBlue!=lastFogBlue)
				pd3d->SetFog(scan_index->fogRed,scan_index->fogGreen,scan_index->fogBlue);

			pd3d->RenderPolyCallback(pDD,&(scan_index->poly_type));

			next_index=scan_index->lptr;
		} 
		while (next_index!=NULL);
	}

	public:

	CPolyTree(struct _DirectDraw* pdd=NULL) 
	{
		pDD=pdd;
		pHead=NULL;
		ppf=0;
		pBufferSpace=new UByte[BUFFER_SIZE];
		pBufferCur=pBufferSpace;
	}

	~CPolyTree() 
	{
		delete[] pBufferSpace;
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPoly
//Author		Paul.   
//Date			Fri 11 Dec 1998
//------------------------------------------------------------------------------
	void AddPoly(LPPOLYTYPE pPoly)
	{
		bool		inserted=false;

		SPolyRec 	*new_index,
					*next_index,
					*scan_index;

		new_index=GetPolyRec(pPoly);

		if (new_index==NULL)
			return;

		if (pHead==NULL)
			pHead=new_index;
		else
		{
		 	next_index=pHead;

			while (!inserted)
			{
				scan_index=next_index;

				if (scan_index->sort_z>new_index->sort_z)
				{
					if ((next_index=scan_index->lptr)==NULL)
					{
						scan_index->lptr=new_index;
						inserted=true;
					}
				}
				else
				{
					if ((next_index=scan_index->rptr)==NULL)
					{
						scan_index->rptr=new_index;
						inserted=true;
					}
				}
			}
		}
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnumPolys
//Author		Paul.   
//Date			Fri 11 Dec 1998
//------------------------------------------------------------------------------
	void RenderPolys(direct_3d* d3dptr)
	{
		//backup some flags
		SLong bupShadeRed,bupShadeGreen,bupShadeBlue;
		bool isTranspFade,isLightShaded;
		UByte globalAlphaValue;
		pd3d=d3dptr;
		isTranspFade=pd3d->isTranspFade;
		isLightShaded=pd3d->isLightShaded;
		globalAlphaValue=pd3d->globalAlphaValue;
		bupShadeRed=pd3d->vShadeRed;
		bupShadeGreen=pd3d->vShadeGreen;
		bupShadeBlue=pd3d->vShadeBlue;
		D3DCOLOR bupAmbientLight=AmbientLight;

		if (pHead!=NULL) 
		{
			RenderRecurse(pHead);
			pHead=NULL;
		}
		ppf=0;
		pBufferCur=pBufferSpace;

		//restore some flags
		pd3d->isTranspFade=isTranspFade;
		pd3d->isLightShaded=isLightShaded;
		pd3d->globalAlphaValue=globalAlphaValue;
		pd3d->vShadeRed=bupShadeRed;
		pd3d->vShadeGreen=bupShadeGreen;
		pd3d->vShadeBlue=bupShadeBlue;
		AmbientLight=bupAmbientLight;
	}
};

#include "monotxt.h"

const SLong MistRED=0xBf;
const SLong MistGREEN=0xBf;
const SLong MistBLUE=0xBf;

const SLong SnowRED=0x4f;
const SLong SnowGREEN=0x4f;
const SLong SnowBLUE=0x4f;

//SLong		stored_wx,stored_wz;								//PD 03Jun97

ViewData	viewdata,saveviewdata;

SLong	executecount;

#ifndef	__FAR_LAND__											//PD 22Aug97
const	int	maxLevel = 5;										//PD 22Aug97
#else															//PD 22Aug97
const	int	maxLevel = 6;										//PD 22Aug97
#endif															//PD 22Aug97

const	ULong	TWO_MEG = 2*1024*1024;
const	ULong	FOUR_MEG = 4*1024*1024;
const	ULong	EIGHT_MEG = 8*1024*1024;

const	Float	SZ_SCALE = 4.0;
const	Float	RHW_SCALE= 10.0;

//-------------------------
//3D - clipping bits'n'bobs
//-------------------------

UByte	CurrentFadeValue;

int driverCount=0;
int numModes=0;

char dn00[64], dn01[64], dn02[64], dn03[64];
char dn04[64], dn05[64], dn06[64], dn07[64];
char dn08[64], dn09[64], dn0A[64], dn0B[64];
char dn0C[64], dn0D[64], dn0E[64], dn0F[64];

char* driverNames[]=
{
	dn00,dn01,dn02,dn03,
	dn04,dn05,dn06,dn07,
	dn08,dn09,dn0A,dn0B,
	dn0C,dn0D,dn0E,dn0F
};

ULong driverRAM[64];

SDrvrModes driverModes[128];

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDrivers
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void GetDrivers(int& dc,char**& dn)
{
	dc=driverCount;
	dn=driverNames;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetModes
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void GetModes(int& nm,SDrvrModes*& dm)
{
	nm=numModes;
	dm=driverModes;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDriverAndMode
//Author		Paul.   
//Date			Thu 21 Jan 1999
//------------------------------------------------------------------------------
void GetDriverAndMode(int& driverIndex,int& modeIndex,int& this_width,int& this_height)
{
	SLong i,k;

	if (driverCount>0)
	{
		//there is more than just the primary
		//display driver

		for (i=driverCount;i-->=0;)
		{
		 	if (driverRAM[i]>=800*600*3*2)
				for (SLong j=0,k=0;j<numModes;j++)
					if (driverModes[j].driverNo-1==i &&
						driverModes[j].displayBPP==16)
					{
						//k++;
						if (driverModes[j].displayWidth==800 &&
							driverModes[j].displayHeight==600)
						{
							driverIndex=i+1;
							modeIndex=k;
							this_width=800;
							this_height=600;
							return;
						}
						k++;
					}

			for (SLong j=0,k=0;j<numModes;j++)
				if (driverModes[j].driverNo-1==i &&
					driverModes[j].displayBPP==16)
				{
					//k++;
					if (driverModes[j].displayWidth==640 &&
						driverModes[j].displayHeight==480)
					{
						driverIndex=i+1;
						modeIndex=k;
						this_width=640;
						this_height=480;
						return;
					}
					k++;
				}
		}
	}

	k=0;
	for (SLong j=0;j<numModes;j++)
		if (driverModes[j].driverNo==0 &&
			driverModes[j].displayBPP==16)
		{
			//k++;
			if (driverModes[j].displayWidth==640 &&
				driverModes[j].displayHeight==480)
			{
				driverIndex=0;
				modeIndex=k;
				this_width=640;
				this_height=480;
				return;
			}
			k++;
		}

	k=0;
	for (j=0;j<numModes;j++)
		if (driverModes[j].driverNo==0 &&
			driverModes[j].displayBPP==16)
		{
			//k++;
			if (driverModes[j].displayWidth==512 &&
				driverModes[j].displayHeight==384)
			{
				driverIndex=0;
				modeIndex=k;
				this_width=512;
				this_height=384;
				return;
			}
			k++;
		}

	driverIndex=modeIndex=0;
	this_width=640;
	this_height=480;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALC_RANGE_FOG
//Author		Paul.   
//Date			Wed 8 Apr 1998
//------------------------------------------------------------------------------
inline UByte direct_3d::CALC_RANGE_FOG(Float dx,Float dy,Float dz)
{
	if (bItemFoggingActive)	return itemFogVal;

	if (dz<viewdata.FogStart) return UByte(255);
	if (dz>viewdata.FogEnd) return UByte(0);
	Float range=255.*(dz-viewdata.FogStart)/
		(viewdata.FogEnd-viewdata.FogStart);
	if (range<0.) return UByte(255);
	else if (range>255.) return UByte(0);
	else return UByte(0xFF-UByte(range));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VidRamTexture
//Author		Paul.   
//Date			Wed 8 Apr 1998
//------------------------------------------------------------------------------
direct_3d::VidRamTexture::VidRamTexture(ImageMapDescPtr p)
{
	lpOlderTexture=lpNewerTexture=NULL;
	bInUse=0;
	lpImageMap=p;
	dwWidth=p->w;
	dwHeight=p->h;
	if (lpImageMap->alpha!=NULL){
		bHasAlpha=true;
		bIsMasked=true;
	}
	else{
		bHasAlpha=false;
		bIsMasked=(lpImageMap->isMasked)?true:false;
	}
//	if (gameSettings.m_bUseMipMapping)
	if (Save_Data.filtering>=2)
	{
		UWord maxWH=dwWidth>dwHeight?dwWidth:dwHeight;

		if (maxWH>=256)			mipMapLevels=5;
		else if (maxWH==128)	mipMapLevels=4;
		else if (maxWH==64)		mipMapLevels=3;
		else if (maxWH==32)		mipMapLevels=2;
		else 					mipMapLevels=0;

		if (Save_Data.textureQuality<=2)
		{
			mipMapLevels--;
			if (mipMapLevels=-1) mipMapLevels=0;
		}
	}
	else mipMapLevels=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MAKE_SZ
//Author		Paul.   
//Date			Tue 14 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline Float direct_3d::MAKE_SZ(Float bodyZ)
{
	Float retval;
	if (bodyZ<fZBufScaleSwitchRange)	retval=8*bodyZ/fMaxVisRange;
	else
		retval=(8*fZBufScaleSwitchRange/fMaxVisRange)+
				(bodyZ-fZBufScaleSwitchRange)/(fMaxVisRange-fZBufScaleSwitchRange);
	if (retval>.99999*Max_Z_Scale) return Max_Z_Scale*.99999;//Max allowable Z Value
	return retval;
}

//OLD_CODE	Float retval=frMaxVisRange*(4*bodyZ);
//	Float retval=bodyZ*4/fMaxVisRange;
//	if (retval>.99999*Max_Z_Scale) return Max_Z_Scale*.99999;//Max allowable Z Value
//	return retval;
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MAKE_RHW
//Author		Paul.   
//Date			Tue 7 Apr 1998
//------------------------------------------------------------------------------
inline Float direct_3d::MAKE_RHW(Float screenZ)
{
	return fMaxVisRange/(8191.0*screenZ);
}

#define CLIP_XVAL(xval)\
			if ((xval)<viewdata.clipLft)		(xval)=viewdata.clipLft;\
			else if ((xval)>viewdata.clipRgt)	(xval)=viewdata.clipRgt;	/*\*/
//			else (xval)=D3DVALUE(SLong((xval)+.5));

#define CLIP_YVAL(yval)\
			if ((yval)<viewdata.clipTop)		(yval)=viewdata.clipTop;\
			else if ((yval)>viewdata.clipBot)	(yval)=viewdata.clipBot;	/*\*/
//			else (yval)=D3DVALUE(SLong((yval)+.5));

//#define LCLIP_YVAL(yval)\
//			if ((yval)<1) (yval)=1;\
//			else if ((yval)>479) (yval)=479;

//#define LCLIP_XVAL(xval)\
//			if ((xval)<1) (xval)=1;\
//			else if ((xval)>639) (xval)=639;

#define LCLIP_YVAL(yval)\
			if ((yval)<viewdata.clipTop+1.0)(yval)=viewdata.clipTop+1.0;\
			else if ((yval)>viewdata.clipBot-1.0)(yval)=viewdata.clipBot-1.0;

#define LCLIP_XVAL(xval)\
			if ((xval)<viewdata.clipLft+1.0)(xval)=viewdata.clipLft+1.0;\
			else if ((xval)>viewdata.clipRgt-1.0)(xval)=viewdata.clipRgt-1.0;

#define CLAMP(val)	if ((val)>-.00001 && (val)<.00001) (val)=.0

enum	WhichDirection											//PD 12Sep97
{
	wd_NULL = 	0x0000,
	wd_N	=	0x0001,		wd_S	=	0x0002,
	wd_E	=	0x0004,		wd_W	=	0x0008,
	wd_NW	=	wd_N+wd_W,	wd_NE	=	wd_N+wd_E,
	wd_SW	= 	wd_S+wd_W,	wd_SE	=	wd_S+wd_E
};

extern	SWord	winmode_w;
extern	SWord	winmode_h;
extern	SWord	winmode_bpp;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		D3DErrorCodes
//Author		Paul.   
//Date			Thu 6 Feb 1997
//
//Description	Translate random number into error string
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void D3DErrorCodes(char* file,int lineno,HRESULT dderr)
{
	if (dderr==D3D_OK)	return;

	_asm {int 3}

	char ErrorString[256];

	sprintf(ErrorString,"%s (%d): ",file,lineno);

	switch (dderr)
	{
		case E_NOINTERFACE:
		lstrcat (ErrorString,"E_NOINTERFACE");
		break;

		case DDERR_INVALIDOBJECT:
		lstrcat (ErrorString,"DDERR_INVALIDOBJECT");
		break;

		case DDERR_INVALIDPARAMS:
		lstrcat (ErrorString,"DDERR_INVALIDPARAMS");
		break;

		case DDERR_OUTOFMEMORY:
		lstrcat (ErrorString,"DDERR_OUTOFMEMORY");
		break;

		case D3DERR_BADMAJORVERSION:
		lstrcat (ErrorString,"D3DERR_BADMAJORVERSION");
		break;

		case D3DERR_BADMINORVERSION:
		lstrcat (ErrorString,"D3DERR_BADMINORVERSION");
		break;

		case D3DERR_EXECUTE_CLIPPED_FAILED:
		lstrcat (ErrorString,"D3DERR_EXECUTE_CLIPPED_FAILED");
		break;

		case D3DERR_EXECUTE_CREATE_FAILED:
		lstrcat (ErrorString,"D3DERR_EXECUTE_CREATE_FAILED");
		break;

		case D3DERR_EXECUTE_DESTROY_FAILED:
		lstrcat (ErrorString,"D3DERR_EXECUTE_DESTROY_FAILED");
		break;

		case D3DERR_EXECUTE_FAILED:
		lstrcat (ErrorString,"D3DERR_EXECUTE_FAILED");
		break;

		case D3DERR_EXECUTE_LOCK_FAILED:
		lstrcat (ErrorString,"D3DERR_EXECUTE_LOCK_FAILED");
		break;

		case D3DERR_EXECUTE_LOCKED:
		lstrcat (ErrorString,"D3DERR_EXECUTE_LOCKED");
		break;

		case D3DERR_EXECUTE_NOT_LOCKED:
		lstrcat (ErrorString,"D3DERR_EXECUTE_NOT_LOCKED");
		break;

		case D3DERR_EXECUTE_UNLOCK_FAILED:
		lstrcat (ErrorString,"D3DERR_EXECUTE_UNLOCK_FAILED");
		break;

		case D3DERR_LIGHT_SET_FAILED:
		lstrcat (ErrorString,"D3DERR_LIGHT_SET_FAILED");
		break;

		case D3DERR_MATERIAL_CREATE_FAILED:
		lstrcat (ErrorString,"D3DERR_MATERIAL_CREATE_FAILED");
		break;

		case D3DERR_MATERIAL_DESTROY_FAILED:
		lstrcat (ErrorString,"D3DERR_MATERIAL_DESTROY_FAILED");
		break;

		case D3DERR_MATERIAL_GETDATA_FAILED:
		lstrcat (ErrorString,"D3DERR_MATERIAL_GETDATA_FAILED");
		break;

		case D3DERR_MATERIAL_SETDATA_FAILED:
		lstrcat (ErrorString,"D3DERR_MATERIAL_SETDATA_FAILED");
		break;

		case D3DERR_MATRIX_CREATE_FAILED:
		lstrcat (ErrorString,"D3DERR_MATRIX_CREATE_FAILED");
		break;

		case D3DERR_MATRIX_DESTROY_FAILED:
		lstrcat (ErrorString,"D3DERR_MATRIX_DESTROY_FAILED");
		break;

		case D3DERR_MATRIX_GETDATA_FAILED:
		lstrcat (ErrorString,"D3DERR_MATRIX_GETDATA_FAILED");
		break;

		case D3DERR_MATRIX_SETDATA_FAILED:
		lstrcat (ErrorString,"D3DERR_MATRIX_SETDATA_FAILED");
		break;

		case D3DERR_SCENE_BEGIN_FAILED:
		lstrcat (ErrorString,"D3DERR_SCENE_BEGIN_FAILED");
		break;

		case D3DERR_SCENE_END_FAILED:
		lstrcat (ErrorString,"D3DERR_SCENE_END_FAILED");
		break;

		case D3DERR_SCENE_IN_SCENE:
		lstrcat (ErrorString,"D3DERR_SCENE_IN_SCENE");
		break;

		case D3DERR_SCENE_NOT_IN_SCENE:
		lstrcat (ErrorString,"D3DERR_SCENE_NOT_IN_SCENE");
		break;

		case D3DERR_SETVIEWPORTDATA_FAILED:
		lstrcat (ErrorString,"D3DERR_SETVIEWPORTDATA_FAILED");
		break;

		case D3DERR_TEXTURE_CREATE_FAILED:
		lstrcat (ErrorString,"D3DERR_TEXTURE_CREATE_FAILED");
		break;

		case D3DERR_TEXTURE_DESTROY_FAILED:
		lstrcat (ErrorString,"D3DERR_TEXTURE_DESTROY_FAILED");
		break;

		case D3DERR_TEXTURE_GETSURF_FAILED:
		lstrcat (ErrorString,"D3DERR_TEXTURE_GETSURF_FAILED");
		break;

		case D3DERR_TEXTURE_LOAD_FAILED:
		lstrcat (ErrorString,"D3DERR_TEXTURE_LOAD_FAILED");
		break;

		case D3DERR_TEXTURE_LOCK_FAILED:
		lstrcat (ErrorString,"D3DERR_TEXTURE_LOCK_FAILED");
		break;

		case D3DERR_TEXTURE_LOCKED:
		lstrcat (ErrorString,"D3DERR_TEXTURE_LOCKED");
		break;

		case D3DERR_TEXTURE_NO_SUPPORT:
		lstrcat (ErrorString,"D3DERR_TEXTURE_NO_SUPPORT");
		break;

		case D3DERR_TEXTURE_NOT_LOCKED:
		lstrcat (ErrorString,"D3DERR_TEXTURE_NOT_LOCKED");
		break;

		case D3DERR_TEXTURE_SWAP_FAILED:
		lstrcat (ErrorString,"D3DERR_TEXTURE_SWAP_FAILED");
		break;

		case D3DERR_TEXTURE_UNLOCK_FAILED:
		lstrcat (ErrorString,"D3DERR_TEXTURE_UNLOCK_FAILED");
		break;

		default:
		lstrcat (ErrorString,"Unrecognised error code");
		break;
	}	
	OutputDebugString(ErrorString);
	_Error.EmitSysErr(ErrorString);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DDErrorCodes
//Author		Paul.   
//Date			Wed 12 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void DDErrorCodes(char* file,int lineno,HRESULT dderr)
{
	if (dderr==DD_OK)	return;

//DEADCODE JIM 20/07/99 	_asm {int 3}

	char ErrorString[256];

	sprintf(ErrorString,"%s (%d): %08x= ",file,lineno,dderr);

	switch (dderr)
	{
		case DDERR_ALREADYINITIALIZED:
		lstrcat (ErrorString,"DDERR_ALREADYINITIALIZED");
		break;
	
		case DDERR_BLTFASTCANTCLIP:
		lstrcat (ErrorString,"DDERR_BLTFASTCANTCLIP");
		break;
	
		case DDERR_CANNOTATTACHSURFACE:
		lstrcat (ErrorString,"DDERR_CANNOTATTACHSURFACE");
		break;
	
		case DDERR_CANNOTDETACHSURFACE:
		lstrcat (ErrorString,"DDERR_CANNOTDETACHSURFACE");
		break;
	
		case DDERR_CANTCREATEDC:
		lstrcat (ErrorString,"DDERR_CANTCREATEDC");
		break;
	
		case DDERR_CANTDUPLICATE:
		lstrcat (ErrorString,"DDERR_CANTDUPLICATE");
		break;
	
		case DDERR_CANTLOCKSURFACE:
		lstrcat (ErrorString,"DDERR_CANTLOCKSURFACE");
		break;
	
		case DDERR_CANTPAGELOCK:
		lstrcat (ErrorString,"DDERR_CANTPAGELOCK");
		break;
	
		case DDERR_CANTPAGEUNLOCK:
		lstrcat (ErrorString,"DDERR_CANTPAGEUNLOCK");
		break;
	
		case DDERR_CLIPPERISUSINGHWND:
		lstrcat (ErrorString,"DDERR_CLIPPERISUSINGHWND");
		break;
	
		case DDERR_COLORKEYNOTSET:
		lstrcat (ErrorString,"DDERR_COLORKEYNOTSET");
		break;
	
		case DDERR_CURRENTLYNOTAVAIL:
		lstrcat (ErrorString,"DDERR_CURRENTLYNOTAVAIL");
		break;
	
		case DDERR_DCALREADYCREATED:
		lstrcat (ErrorString,"DDERR_DCALREADYCREATED");
		break;
	
		case DDERR_DIRECTDRAWALREADYCREATED:
		lstrcat (ErrorString,"DDERR_DIRECTDRAWALREADYCREATED");
		break;
	
		case DDERR_EXCEPTION:
		lstrcat (ErrorString,"DDERR_EXCEPTION");
		break;
	
		case DDERR_EXCLUSIVEMODEALREADYSET:
		lstrcat (ErrorString,"DDERR_EXCLUSIVEMODEALREADYSET");
		break;
	
		case DDERR_GENERIC:
		lstrcat (ErrorString,"DDERR_GENERIC");
		break;
	
		case DDERR_HEIGHTALIGN:
		lstrcat (ErrorString,"DDERR_HEIGHTALIGN");
		break;
	
		case DDERR_HWNDALREADYSET:
		lstrcat (ErrorString,"DDERR_HWNDALREADYSET");
		break;
	
		case DDERR_HWNDSUBCLASSED:
		lstrcat (ErrorString,"DDERR_HWNDSUBCLASSED");
		break;
	
		case DDERR_IMPLICITLYCREATED:
		lstrcat (ErrorString,"DDERR_IMPLICITLYCREATED");
		break;
	
		case DDERR_INCOMPATIBLEPRIMARY:
		lstrcat (ErrorString,"DDERR_INCOMPATIBLEPRIMARY");
		break;
	
		case DDERR_INVALIDCAPS:
		lstrcat (ErrorString,"DDERR_INVALIDCAPS");
		break;
	
		case DDERR_INVALIDCLIPLIST:
		lstrcat (ErrorString,"DDERR_INVALIDCLIPLIST");
		break;
	
		case DDERR_INVALIDDIRECTDRAWGUID:
		lstrcat (ErrorString,"DDERR_INVALIDDIRECTDRAWGUID");
		break;
	
		case DDERR_INVALIDMODE:
		lstrcat (ErrorString,"DDERR_INVALIDMODE");
		break;
	
		case DDERR_INVALIDOBJECT:
		lstrcat (ErrorString,"DDERR_INVALIDOBJECT");
		break;
	
		case DDERR_INVALIDPARAMS:
		lstrcat (ErrorString,"DDERR_INVALIDPARAMS");
		break;
	
		case DDERR_INVALIDPIXELFORMAT:
		lstrcat (ErrorString,"DDERR_INVALIDPIXELFORMAT");
		break;
	
		case DDERR_INVALIDPOSITION:
		lstrcat (ErrorString,"DDERR_INVALIDPOSITION");
		break;
	
		case DDERR_INVALIDRECT:
		lstrcat (ErrorString,"DDERR_INVALIDRECT");
		break;
	
		case DDERR_INVALIDSURFACETYPE:
		lstrcat (ErrorString,"DDERR_INVALIDSURFACETYPE");
		break;
	
		case DDERR_LOCKEDSURFACES:
		lstrcat (ErrorString,"DDERR_LOCKEDSURFACES");
		break;
	
		case DDERR_NO3D:
		lstrcat (ErrorString,"DDERR_NO3D");
		break;
	
		case DDERR_NOALPHAHW:
		lstrcat (ErrorString,"DDERR_NOALPHAHW");
		break;
	
		case DDERR_NOBLTHW:
		lstrcat (ErrorString,"DDERR_NOBLTHW");
		break;
	
		case DDERR_NOCLIPLIST:
		lstrcat (ErrorString,"DDERR_NOCLIPLIST");
		break;
	
		case DDERR_NOCLIPPERATTACHED:
		lstrcat (ErrorString,"DDERR_NOCLIPPERATTACHED");
		break;
	
		case DDERR_NOCOLORCONVHW:
		lstrcat (ErrorString,"DDERR_NOCOLORCONVHW");
		break;
	
		case DDERR_NOCOLORKEY:
		lstrcat (ErrorString,"DDERR_NOCOLORKEY");
		break;
	
		case DDERR_NOCOLORKEYHW:
		lstrcat (ErrorString,"DDERR_NOCOLORKEYHW");
		break;
	
		case DDERR_NOCOOPERATIVELEVELSET:
		lstrcat (ErrorString,"DDERR_NOCOOPERATIVELEVELSET");
		break;
	
		case DDERR_NODC:
		lstrcat (ErrorString,"DDERR_NODC");
		break;
	
		case DDERR_NODDROPSHW:
		lstrcat (ErrorString,"DDERR_NODDROPSHW");
		break;
	
		case DDERR_NODIRECTDRAWHW:
		lstrcat (ErrorString,"DDERR_NODIRECTDRAWHW");
		break;
	
		case DDERR_NODIRECTDRAWSUPPORT:
		lstrcat (ErrorString,"DDERR_NODIRECTDRAWSUPPORT");
		break;
	
		case DDERR_NOEMULATION:
		lstrcat (ErrorString,"DDERR_NOEMULATION");
		break;
	
		case DDERR_NOEXCLUSIVEMODE:
		lstrcat (ErrorString,"DDERR_NOEXCLUSIVEMODE");
		break;
	
		case DDERR_NOFLIPHW:
		lstrcat (ErrorString,"DDERR_NOFLIPHW");
		break;
	
		case DDERR_NOGDI:
		lstrcat (ErrorString,"DDERR_NOGDI");
		break;
	
		case DDERR_NOHWND:
		lstrcat (ErrorString,"DDERR_NOHWND");
		break;
	
		case DDERR_NOMIPMAPHW:
		lstrcat (ErrorString,"DDERR_NOMIPMAPHW");
		break;
	
		case DDERR_NOMIRRORHW:
		lstrcat (ErrorString,"DDERR_NOMIRRORHW");
		break;
	
		case DDERR_NOOVERLAYDEST:
		lstrcat (ErrorString,"DDERR_NOOVERLAYDEST");
		break;
	
		case DDERR_NOOVERLAYHW:
		lstrcat (ErrorString,"DDERR_NOOVERLAYHW");
		break;
	
		case DDERR_NOPALETTEATTACHED:
		lstrcat (ErrorString,"DDERR_NOPALETTEATTACHED");
		break;
	
		case DDERR_NOPALETTEHW:
		lstrcat (ErrorString,"DDERR_NOPALETTEHW");
		break;
	
		case DDERR_NORASTEROPHW:
		lstrcat (ErrorString,"DDERR_NORASTEROPHW");
		break;
	
		case DDERR_NOROTATIONHW:
		lstrcat (ErrorString,"DDERR_NOROTATIONHW");
		break;
	
		case DDERR_NOSTRETCHHW:
		lstrcat (ErrorString,"DDERR_NOSTRETCHHW");
		break;
	
		case DDERR_NOT4BITCOLOR:
		lstrcat (ErrorString,"DDERR_NOT4BITCOLOR");
		break;
	
		case DDERR_NOT4BITCOLORINDEX:
		lstrcat (ErrorString,"DDERR_NOT4BITCOLORINDEX");
		break;
	
		case DDERR_NOT8BITCOLOR:
		lstrcat (ErrorString,"DDERR_NOT8BITCOLOR");
		break;
	
		case DDERR_NOTAOVERLAYSURFACE:
		lstrcat (ErrorString,"DDERR_NOTAOVERLAYSURFACE");
		break;
	
		case DDERR_NOTEXTUREHW:
		lstrcat (ErrorString,"DDERR_NOTEXTUREHW");
		break;
	
		case DDERR_NOTFLIPPABLE:
		lstrcat (ErrorString,"DDERR_NOTFLIPPABLE");
		break;
	
		case DDERR_NOTFOUND:
		lstrcat (ErrorString,"DDERR_NOTFOUND");
		break;
	
		case DDERR_NOTINITIALIZED:
		lstrcat (ErrorString,"DDERR_NOTINITIALIZED");
		break;
	
		case DDERR_NOTLOCKED:
		lstrcat (ErrorString,"DDERR_NOTLOCKED");
		break;
	
		case DDERR_NOTPAGELOCKED:
		lstrcat (ErrorString,"DDERR_NOTPAGELOCKED");
		break;
	
		case DDERR_NOTPALETTIZED:
		lstrcat (ErrorString,"DDERR_NOTPALETTIZED");
		break;
	
		case DDERR_NOVSYNCHW:
		lstrcat (ErrorString,"DDERR_NOVSYNCHW");
		break;
	
		case DDERR_NOZBUFFERHW:
		lstrcat (ErrorString,"DDERR_NOZBUFFERHW");
		break;
	
		case DDERR_NOZOVERLAYHW:
		lstrcat (ErrorString,"DDERR_NOZOVERLAYHW");
		break;
	
		case DDERR_OUTOFCAPS:
		lstrcat (ErrorString,"DDERR_OUTOFCAPS");
		break;
	
		case DDERR_OUTOFMEMORY:
		lstrcat (ErrorString,"DDERR_OUTOFMEMORY");
		break;
	
		case DDERR_OUTOFVIDEOMEMORY:
		lstrcat (ErrorString,"DDERR_OUTOFVIDEOMEMORY");
		break;
	
		case DDERR_OVERLAYCANTCLIP:
		lstrcat (ErrorString,"DDERR_OVERLAYCANTCLIP");
		break;
	
		case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
		lstrcat (ErrorString,"DDERR_OVERLAYCOLORKEYONLYONEACTIVE");
		break;
	
		case DDERR_OVERLAYNOTVISIBLE:
		lstrcat (ErrorString,"DDERR_OVERLAYNOTVISIBLE");
		break;
	
		case DDERR_PALETTEBUSY:
		lstrcat (ErrorString,"DDERR_PALETTEBUSY");
		break;
	
		case DDERR_PRIMARYSURFACEALREADYEXISTS:
		lstrcat (ErrorString,"DDERR_PRIMARYSURFACEALREADYEXISTS");
		break;
	
		case DDERR_REGIONTOOSMALL:
		lstrcat (ErrorString,"DDERR_REGIONTOOSMALL");
		break;
	
		case DDERR_SURFACEALREADYATTACHED:
		lstrcat (ErrorString,"DDERR_SURFACEALREADYATTACHED");
		break;
	
		case DDERR_SURFACEALREADYDEPENDENT:
		lstrcat (ErrorString,"DDERR_SURFACEALREADYDEPENDENT");
		break;
	
		case DDERR_SURFACEBUSY:
		lstrcat (ErrorString,"DDERR_SURFACEBUSY");
		break;
	
		case DDERR_SURFACEISOBSCURED:
		lstrcat (ErrorString,"DDERR_SURFACEISOBSCURED");
		break;
	
		case DDERR_SURFACELOST:
		lstrcat (ErrorString,"DDERR_SURFACELOST");
		break;
	
		case DDERR_SURFACENOTATTACHED:
		lstrcat (ErrorString,"DDERR_SURFACENOTATTACHED");
		break;
	
		case DDERR_TOOBIGHEIGHT:
		lstrcat (ErrorString,"DDERR_TOOBIGHEIGHT");
		break;
	
		case DDERR_TOOBIGSIZE:
		lstrcat (ErrorString,"DDERR_TOOBIGSIZE");
		break;
	
		case DDERR_TOOBIGWIDTH:
		lstrcat (ErrorString,"DDERR_TOOBIGWIDTH");
		break;
	
		case DDERR_UNSUPPORTED:
		lstrcat (ErrorString,"DDERR_UNSUPPORTED");
		break;
	
		case DDERR_UNSUPPORTEDFORMAT:
		lstrcat (ErrorString,"DDERR_UNSUPPORTEDFORMAT");
		break;
	
		case DDERR_UNSUPPORTEDMASK:
		lstrcat (ErrorString,"DDERR_UNSUPPORTEDMASK");
		break;
	
		case DDERR_UNSUPPORTEDMODE:
		lstrcat (ErrorString,"DDERR_UNSUPPORTEDMODE");
		break;
	
		case DDERR_VERTICALBLANKINPROGRESS:
		lstrcat (ErrorString,"DDERR_VERTICALBLANKINPROGRESS");
		break;
	
		case DDERR_WASSTILLDRAWING:
		lstrcat (ErrorString,"DDERR_WASSTILLDRAWING");
		break;
	
		case DDERR_WRONGMODE:
		lstrcat (ErrorString,"DDERR_WRONGMODE");
		break;
	
		case DDERR_XALIGN:
		lstrcat (ErrorString,"DDERR_XALIGN");
		break;
	
		default:
		lstrcat (ErrorString,"Unrecognised error code");
		break;
	}
	OutputDebugString(ErrorString);
//DEADCODE JIM 20/07/99 	Mono_Text.Print((UByte*)ErrorString);
	_Error.ReallyEmitSysErr(ErrorString);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		direct_draw
//Author		Paul.   
//Date			Fri 31 Jan 1997
//
//Description	Replacement for old 'DirectDrawCreate' call that
//				will scan available drivers for a 3D capeable one
//				and use that in preference to any others
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON	direct_draw::direct_draw()
{
	HRESULT		dderrval;
	LPDIRECT3D	lpD3D;

	lockLevel=0;
	gotShifts=false;

	lpDD=NULL;
	lpD3D=NULL;
	NumDrivers=0;
	CurrDriver=0;
	softpallookup=NULL;

	//Search for a 3D capable DirectDraw hardware driver and create it.

	dderrval =
	DirectDrawEnumerate(enumDDDrivers,(LPVOID)this);

	if (dderrval!=DD_OK)	lpDD=NULL;

	NumModes=0;

	if (NumDrivers!=0)
	{
		//Check each driver for supported display modes tha fit our 
		//requirements

		for (CurrDriver=0;CurrDriver<NumDrivers;CurrDriver++)
		{
			dderrval =
			DirectDrawCreate(&Drivers[CurrDriver].Guid,&lpDD,NULL);

			if (dderrval==DD_OK)
			{
				dderrval =
				lpDD->QueryInterface(IID_IDirectDraw2,(LPVOID *)&lpDD2);

				if (dderrval==DD_OK)
				{
//DEADCODE					EightBitOnly=FALSE;
					dderrval =
					lpDD2->EnumDisplayModes(DDEDM_REFRESHRATES,NULL,(LPVOID)this,
											(LPDDENUMMODESCALLBACK)&enumDisplayModes);

					RELEASE(lpDD2,dderrval);
				}

				RELEASE(lpDD,dderrval);
			}
		}
	}

	for (SLong q=0;q<NumDrivers && q<16;q++)
	{
		strcpy(driverNames[q],Drivers[q].About);
		driverRAM[q]=Drivers[q].vidMem;
	}
	driverCount=NumDrivers;

	//Scan for additional modes with no hardware support

	CurrDriver=-1;

	bPrimaryDisplayDriverDoesHw3D = FALSE;
	bButNotVeryWell	= FALSE;
	bFogVertexMode	= FALSE;									//PD 08Sep97
	bFogTableMode	= FALSE;									//PD 08Sep97

	dderrval =
	DirectDrawCreate(NULL,&lpDD,NULL);

	if (dderrval==DD_OK)
	{
		dderrval =
		lpDD->QueryInterface(IID_IDirectDraw2,(LPVOID *)&lpDD2);

		if (dderrval==DD_OK)
		{
			//check a few of the capabilities of this driver here...

			DDCAPS driverCaps;
			ZeroMem(&driverCaps,sizeof(DDCAPS));
			driverCaps.dwSize=sizeof(DDCAPS);
			dderrval=lpDD2->GetCaps(&driverCaps,NULL);

			//check blit operation caps...
			primaryDoesAsyncBlt=(driverCaps.dwCaps&DDCAPS_BLTQUEUE)?TRUE:FALSE;
			primaryCanBltSysMem=(driverCaps.dwCaps&DDCAPS_CANBLTSYSMEM)?TRUE:FALSE;

 			dderrval =
 			lpDD2->QueryInterface(IID_IDirect3D,(LPVOID*)&lpD3D);

			if (dderrval==DD_OK)
			{
				CanDoHardware3D=0;

				dderrval =
				lpD3D->EnumDevices(enum3DDevices,(LPVOID)this);

				RELEASE(lpD3D,dderrval);
			}

			{
			ULong	memAvail;
			DDSCAPS	ddscaps;
			ddscaps.dwCaps = DDSCAPS_VIDEOMEMORY;

			dderrval =
			lpDD2->GetAvailableVidMem(&ddscaps,&memAvail,NULL);

			primaryDisplayDriverMem = memAvail;

			//Now, add on the video RAM allocated for the
			//windows desktop (probably)

			DDSURFACEDESC	ddsdTemp,*lpddsdTemp=&ddsdTemp;

			ZeroMem (lpddsdTemp,sizeof(DDSURFACEDESC));
			ddsdTemp.dwSize = sizeof(DDSURFACEDESC);
			dderrval = lpDD2->GetDisplayMode(lpddsdTemp);

			winmode_w = ddsdTemp.dwWidth;
			winmode_h = ddsdTemp.dwHeight;
			winmode_bpp = ddsdTemp.ddpfPixelFormat.dwRGBBitCount;

			memAvail = 	ddsdTemp.dwHeight *
						ddsdTemp.lPitch;// *

			primaryDisplayDriverMem += memAvail;

			}

//DEADCODE			EightBitOnly=(CanDoHardware3D==0)?TRUE:FALSE;

			dderrval =
			lpDD2->EnumDisplayModes(DDEDM_REFRESHRATES,NULL,(LPVOID)this,
									(LPDDENUMMODESCALLBACK)&enumDisplayModes);

			RELEASE(lpDD2,dderrval);
		}

		RELEASE(lpDD,dderrval);
	}

	for (q=0;q<NumModes && q<128;q++)
	{
		driverModes[q].driverNo=Modes[q].Driver+1;
		driverModes[q].displayWidth=Modes[q].Width;
		driverModes[q].displayHeight=Modes[q].Height;
		driverModes[q].displayBPP=Modes[q].Bpp;
	}
	numModes=NumModes;

	//Determine which modes can be supported based on the
	//ammount of video memory available

	int counter;

	//Initially need a driver that supports the current 
	//windows mode front end of the game

	fullScreenRequired=false;

	//first, check for a full screen 640x480 
	//hardware accelerated mode NOT using primary
	//display device (ie 3dfx)

	BOOL bFullScreenRequested=gameSettings.m_bFullScreenMode;

	if (bFullScreenRequested)
	{
//		gameSettings.m_bUseSecondary=Save_Data.dddriver!=-1?TRUE:FALSE;
		gameSettings.m_dwWidth=Save_Data.displayW;
		gameSettings.m_dwHeight=Save_Data.displayH;
//DEADCODE JIM 20/07/99  		Mono_Text.Print(Save_Data.displayH,UByteP("gameSettings.m_dwHeight from Save_Data"));

	}

	DWORD dwWidth=gameSettings.m_dwWidth;
	DWORD dwHeight=gameSettings.m_dwHeight;

//	if (gameSettings.m_bUseSecondary==TRUE)
	if (bFullScreenRequested)
	{
		for (counter=0;counter<NumModes;counter++){
			if (Modes[counter].Width==dwWidth &&
				Modes[counter].Height==dwHeight &&
				Modes[counter].Bpp==16 &&
				Modes[counter].Driver==Save_Data.dddriver){
				//now check for hardware support in this mode
				int possDriver=Modes[counter].Driver;
				if (Drivers[possDriver].bHardware3D){
					fullScreenRequired=true;
					break;
				}
			}
		}
	}
	else counter=NumModes;

	if (counter==NumModes)
	{
		if (bFullScreenRequested)
		{
			for (counter=0;counter<NumModes;counter++)
			{
				if (Modes[counter].Width==dwWidth &&
					Modes[counter].Height==dwHeight &&
					Modes[counter].Bpp==16 &&
					Modes[counter].Driver==-1 &&
					bPrimaryDisplayDriverDoesHw3D)
				{
					fullScreenRequired=true;
					break;
				}
			}
		}

		if (counter==NumModes)
		{
			for (counter=0;counter<NumModes;counter++){
				if (Modes[counter].Width==winmode_w &&
					Modes[counter].Height==winmode_h &&
					Modes[counter].Bpp==winmode_bpp &&
					Modes[counter].Driver==-1)
					break;
			}
			if (counter==NumModes)
			{
				if (winmode_bpp==8){
					if (counter==D3DAPP_MAXD3DMODES)
						counter--;
					Modes[counter].Width=winmode_w;
					Modes[counter].Height=winmode_h;
					Modes[counter].Bpp=8;
					Modes[counter].Driver=-1;
					NumModes=counter+1;
				}
			}
		}
	}

	if (counter<NumModes)
	{
		if (Modes[counter].Driver!=-1)
			dderrval =
			DirectDrawCreate(&Drivers[Modes[counter].Driver].Guid,
								&lpDD,NULL);
		else
			dderrval =
			DirectDrawCreate(NULL,&lpDD,NULL);

		if (dderrval!=DD_OK)
			lpDD=NULL;

		CurrMode=counter;
		CurrDriver=Modes[counter].Driver;
	}
	//Obtain a DirectDraw2 interface
	if (lpDD!=NULL)
	{
		dderrval =
		lpDD->QueryInterface(IID_IDirectDraw2,(LPVOID *)&lpDD2);

		if (dderrval!=DD_OK)
		{
			RELEASE(lpDD,dderrval);
			lpDD2=NULL;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		enum3DDevices
//Author		Paul.   
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
HRESULT WINAPI
direct_draw::enum3DDevices(	LPGUID 			lpGuid,
							LPSTR 			lpDeviceDescription,
                      		LPSTR 			lpDeviceName,
							LPD3DDEVICEDESC lpHWDesc,
                      		LPD3DDEVICEDESC lpHELDesc,
							LPVOID 			lpContext)
{
	DirectDDP	directddp;

    directddp = (DirectDDP)lpContext;

    if (lpHWDesc->dcmColorModel)
	{
       	directddp->CanDoHardware3D=1;
		directddp->bPrimaryDisplayDriverDoesHw3D=TRUE;

		if (lpHWDesc->dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_FOGVERTEX)
		{
			directddp->bFogVertexMode=TRUE;
		}
		else if	(lpHWDesc->dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_FOGTABLE)
		{
			directddp->bFogTableMode=TRUE;
		}
		//Alpha based transparency  / Color key test

		if (!directddp->bButNotVeryWell)
		{
		if ((lpHWDesc->dpcTriCaps.dwSrcBlendCaps & D3DPBLENDCAPS_SRCALPHA) &&
			(lpHWDesc->dpcTriCaps.dwDestBlendCaps & D3DPBLENDCAPS_INVSRCALPHA) &&
			(lpHWDesc->dpcTriCaps.dwTextureBlendCaps & D3DPTBLENDCAPS_MODULATEALPHA))
		{
			directddp->bButNotVeryWell=FALSE;
		}
		else if (lpHWDesc->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_TRANSPARENCY)//PD 08Oct97
		{
			directddp->bButNotVeryWell=FALSE;
		}
		else directddp->bButNotVeryWell=TRUE;
		}
    }
    return (D3DENUMRET_OK);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		direct_draw
//Author		Paul.   
//Date			Fri 31 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DES direct_draw::~direct_draw()
{
	if (softpallookup) delete[]softpallookup,softpallookup=NULL;

	HRESULT	dderrval;

	RELEASE(lpDD2,dderrval);

	RELEASE(lpDD,dderrval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NameNuberedDriver
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
UByte*	direct_draw::NameNumberedDriver(SWord drvno)
{
	if (drvno<NumDrivers && drvno>=0)
		return ((UByte*)Drivers[drvno].About);
	 
	return (NULL);	
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
Bool direct_draw::ModeSupported(ScreenRez* lpSRez)
{
	ULong	memForUse,memRequired;

	memForUse =	(lpSRez->driver==-1)?
				primaryDisplayDriverMem:
				Drivers[lpSRez->driver].vidMem;

	SLong	displayWidth, displayHeight, displayBytesPerPixel;

	displayWidth = (lpSRez->width>0)?lpSRez->width:-lpSRez->width;

	displayHeight = displayWidth * 3/4;

	displayBytesPerPixel = lpSRez->colourdepth>>3;

	if (displayBytesPerPixel==1)	return (TRUE);

	if (displayBytesPerPixel!=2)	return (FALSE);

	//Need at least 2 screens + Z-buffer

	memRequired = 2 * displayWidth * displayHeight * displayBytesPerPixel;

	memRequired+= 2 * displayWidth * displayHeight;

	//Need room for ground textures
	//And piloted a/c textures

	if (lpSRez->driver!=-1)
	{
		memRequired+= 1024*1024;								//PD 24Jun97
		memRequired += 1024*1024;								//PD 24Jun97
	}
	else
	{
		memRequired+=0x23E000;									//PD 08Sep97
	}

	if (memForUse>=memRequired)	return (TRUE);

	return (FALSE);
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
Bool direct_draw::DriverIsCapable(SWord drvno)
{
	if (drvno==-1 && bPrimaryDisplayDriverDoesHw3D==TRUE && bButNotVeryWell==TRUE)
		return (FALSE);

	return (TRUE);
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
SWord direct_draw::CountDrivers()
{
	SWord	retval;

	retval = NumDrivers;

	for (int i=0;i<NumModes;i++)
		if (Modes[i].Driver==-1 && Modes[i].Bpp!=8)
		{
			retval -= 1000;
			break;
		}

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DriverDoesHardware3D
//Author		Paul.   
//Date			Thu 27 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOOL direct_draw::DriverDoesHardware3D()
{
	int	driverno = Modes[CurrMode].Driver;

	if (driverno==-1)	return (bPrimaryDisplayDriverDoesHw3D);

	return (Drivers[driverno].bHardware3D);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBltCaps
//Author		Paul.   
//Date			Tue 21 Jul 1998
//------------------------------------------------------------------------------
void direct_draw::GetBltCaps(bool& dab,bool& cbsm)
{
	int driverno=Modes[CurrMode].Driver;

	if (driverno==-1)
	{
		dab=(primaryDoesAsyncBlt!=0)?true:false;
		cbsm=(primaryCanBltSysMem!=0)?true:false;
	}
	else
	{
		dab=(Drivers[driverno].bDoesAsyncBlt!=0)?true:false;
		cbsm=(Drivers[driverno].bCanBltSysMem!=0)?true:false;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		enumDDDrivers
//Author		Paul.   
//Date			Fri 31 Jan 1997
//
//Description	Callback function used during enumeration of DirectDraw drivers.
//				During enumeration, if a 3D capable hardware device is found, it 
//				is created and *(LPDIRECTDRAW*)lpContext is set to it.  
//				Otherwise, does nothing.
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOOL FAR PASCAL
direct_draw::enumDDDrivers(	GUID FAR* lpGUID,	LPSTR lpDriverDesc,
							LPSTR lpDriverName, LPVOID lpContext)
{
	DirectDDP		directddp;
	HRESULT			dderrval;
    LPDIRECTDRAW 	lpDD;
    LPDIRECTDRAW2 	lpDD2;
    DDCAPS 			DriverCaps,
					HELCaps;

	directddp=(DirectDDP)lpContext;

	// A NULL GUID* indicates the DirectDraw HEL.

	if (lpGUID!=NULL)
	{
		DDAppD3DDriver& driver=directddp->Drivers[directddp->NumDrivers];

		// Create the DirectDraw device using this driver.  If it fails,
		// just move on to the next driver.

		dderrval=DirectDrawCreate(lpGUID,&lpDD,NULL);

		if (dderrval!=DD_OK)	return (DDENUMRET_OK);

		dderrval=lpDD->QueryInterface(IID_IDirectDraw2,(LPVOID *)&lpDD2);

		if (dderrval!=DD_OK)
		{
			RELEASE(lpDD,dderrval);
			return (DDENUMRET_OK);
		}

	    // Get the capabilities of this DirectDraw driver.  If it fails,
    	// just move on to the next driver.

	    ZeroMem(&DriverCaps, sizeof(DDCAPS));
    	DriverCaps.dwSize = sizeof(DDCAPS);
	    ZeroMem(&HELCaps, sizeof(DDCAPS));
    	HELCaps.dwSize = sizeof(DDCAPS);

		dderrval=lpDD2->GetCaps(&DriverCaps, &HELCaps);
		
		if (dderrval!=DD_OK)
		{
    	    RELEASE(lpDD2,dderrval);
    	    RELEASE(lpDD,dderrval);
    		return (DDENUMRET_OK);
	    }

    	// We have found a direct draw driver.  Add it to our list

	   	memcpy(&driver.Guid,lpGUID, sizeof(GUID));
   		lstrcpy(driver.About,lpDriverDesc);
	   	lstrcpy(driver.Name,lpDriverName);

		driver.bHardware3D=(DriverCaps.dwCaps&DDCAPS_3D)?TRUE:FALSE;
		driver.bDoesAsyncBlt=(DriverCaps.dwCaps&DDCAPS_BLTQUEUE)?TRUE:FALSE;
		driver.bCanBltSysMem=(DriverCaps.dwCaps&DDCAPS_CANBLTSYSMEM)?TRUE:FALSE;

		ULong	totalmemavail,memAvail;

		DDSCAPS	ddsCaps;
		ddsCaps.dwCaps=DDSCAPS_VIDEOMEMORY;

		dderrval=lpDD2->GetAvailableVidMem(&ddsCaps,&memAvail,NULL);

		if (dderrval==DD_OK)			totalmemavail = memAvail;
		else							totalmemavail = 0;

		driver.vidMem=totalmemavail;

	    directddp->NumDrivers++;

    	RELEASE(lpDD2,dderrval);
    	RELEASE(lpDD,dderrval);

		if (directddp->NumDrivers==D3DAPP_MAXDDDRIVERS)
			return (DDENUMRET_CANCEL);
	}

    return (DDENUMRET_OK);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		enumDisplayModes
//Author		Paul.   
//Date			Mon 3 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
HRESULT WINAPI
direct_draw::enumDisplayModes(	LPDDSURFACEDESC lpDDSurfaceDesc,
								LPVOID			lpContext)
{
	DirectDDP	directddp;

	directddp=(DirectDDP)lpContext;

	//Scan the supported mode list - this mode may already be supported
	//by another driver

//DEADCODE	if (directddp->EightBitOnly==TRUE)
	if (lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount!=16)
		return (DDENUMRET_OK);

/*	if (lpDDSurfaceDesc->dwWidth<512 || (3*lpDDSurfaceDesc->dwWidth!=4*lpDDSurfaceDesc->dwHeight))
		return DDENUMRET_OK;
*/
	for (int counter=0;counter<directddp->NumModes;counter++)
	{
		if (directddp->Modes[counter].Driver==directddp->CurrDriver &&
			directddp->Modes[counter].Width==lpDDSurfaceDesc->dwWidth &&
			directddp->Modes[counter].Height==lpDDSurfaceDesc->dwHeight &&
			directddp->Modes[counter].Bpp==lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount)
			return (DDENUMRET_OK);
	}

	//Throw away modes with color depths higher than 16-bits 
	//(just to prevent mode list from overflowing in the
	//graphics config. screen)

//DEADCODE	if (lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount>16)
//DEADCODE		return (DDENUMRET_OK);

	//found a real 'new mode'

	directddp->Modes[directddp->NumModes].Width=lpDDSurfaceDesc->dwWidth;
	directddp->Modes[directddp->NumModes].Height=lpDDSurfaceDesc->dwHeight;
	directddp->Modes[directddp->NumModes].Bpp=lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount;
	directddp->Modes[directddp->NumModes].Driver=directddp->CurrDriver;

	if (lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount!=8)
	{
		//Get RED bits/shift factor

		DWORD	bits,shift,mask;

		for (	shift=0,
				mask =lpDDSurfaceDesc->ddpfPixelFormat.dwRBitMask;
				!(mask & 1);
				shift++,
				mask>>=1);

		for (	bits=0; mask & 1; bits++, mask>>=1);
			
		directddp->Modes[directddp->NumModes].dwRedBits = bits;
		directddp->Modes[directddp->NumModes].dwRedShift = shift;

		for (	shift=0,
				mask =lpDDSurfaceDesc->ddpfPixelFormat.dwGBitMask;
				!(mask & 1);
				shift++,
				mask>>=1);

		for (	bits=0; mask & 1; bits++, mask>>=1);

		directddp->Modes[directddp->NumModes].dwGreenBits = bits;
		directddp->Modes[directddp->NumModes].dwGreenShift = shift;

		for (	shift=0,
				mask =lpDDSurfaceDesc->ddpfPixelFormat.dwBBitMask;
				!(mask & 1);
				shift++,
				mask>>=1);

		for (	bits=0; mask & 1; bits++, mask>>=1);

		directddp->Modes[directddp->NumModes].dwBlueBits = bits;
		directddp->Modes[directddp->NumModes].dwBlueShift = shift;
	}
	else
	{
		directddp->Modes[directddp->NumModes].dwRedBits =
		directddp->Modes[directddp->NumModes].dwRedShift =

		directddp->Modes[directddp->NumModes].dwGreenBits =
		directddp->Modes[directddp->NumModes].dwGreenShift =

		directddp->Modes[directddp->NumModes].dwBlueBits =
		directddp->Modes[directddp->NumModes].dwBlueShift = 0;
	}

	directddp->NumModes++;

	if (directddp->NumModes==D3DAPP_MAXD3DMODES)
		return (DDENUMRET_CANCEL);

	return (DDENUMRET_OK);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetModes
//Author		Paul.   
//Date			Tue 4 Feb 1997
//
//Description	Copy available mode list back to old
//				structure	
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_draw::GetModes(DirectD& dd)
{
	dd.cModes=NumModes;

	for (int counter=0;counter<NumModes;counter++)
	{
		dd.DDModes[counter].width=Modes[counter].Width;
		dd.DDModes[counter].height=Modes[counter].Height;
		dd.DDModes[counter].colourdepth=Modes[counter].Bpp;
		dd.DDModes[counter].driver=Modes[counter].Driver;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMode
//Author		Paul.   
//Date			Mon 3 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns		TRUE = driver changed 
//				FALSE= driver *NOT* changed
//
//------------------------------------------------------------------------------
BOOL direct_draw::SetMode(int mode)
{
	HRESULT	dderrval;

	BOOL	retval=FALSE;

	if (mode==CurrMode)	return (retval);

	if (Modes[CurrMode].Driver!=Modes[mode].Driver)
	{
		retval=TRUE;

		//Need to swap DirectDraw drivers to change
		//to the new mode

		RELEASE(lpDD2,dderrval);
		RELEASE(lpDD,dderrval);

		//Switch to the new driver

		if (Modes[mode].Driver!=-1)
		{
			dderrval =
			DirectDrawCreate(	&Drivers[Modes[mode].Driver].Guid,
								&lpDD,NULL);
		}
		else
		{
			dderrval =
			DirectDrawCreate(NULL,&lpDD,NULL);
		}

		if (dderrval==DD_OK)
		{
			dderrval =
			lpDD->QueryInterface(IID_IDirectDraw2,(LPVOID*)&lpDD2);

			if (dderrval!=DD_OK)
			{
				RELEASE(lpDD,dderrval);
				lpDD2=NULL;
			}
		}

		if (dderrval!=DD_OK)
			_Error.EmitSysErr("Couldn't create new mode - sorry!");

	}
	CurrMode=mode;

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SExtraDetail
//Author		Paul.   
//Date			Thu 3 Dec 1998
//------------------------------------------------------------------------------
direct_3d::SExtraDetail::SExtraDetail(	SLong numT,ImageMapNumber* pNums,
										SLong numA,AreaType* pAreas,
										SLong tReset)
{
	//set animation data

	timerCur=timerReset=tReset;
	
	//set source texture data

	numTextures=numT;
	curTexture=0;

	for (SLong x=0;x<numT;x++)	images[x]=Image_Map.GetImageMapPtr(pNums[x]);
	for (;x<MAX_IMAGES;x++)		images[x]=NULL;

	//set area type data

	numAreas=numA;
	for (x=0;x<numA;x++)	areaTypes[x]=pAreas[x];
	for (;x<MAX_AREAS;x++)	areaTypes[x]=(AreaType)NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupExtraLandDetail
//Author		Paul.   
//Date			Thu 3 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::SetupExtraLandDetail(DirectD* pDirectD)
{
#define AT AreaType

	ImageMapNumber imnDetail00[]={DITHERNO};		//steel
	ImageMapNumber imnDetail01[]={DITHER1NO};		//town
	ImageMapNumber imnDetail02[]={DITHER2NO};		//city
	ImageMapNumber imnDetail03[]={DITHER3NO};		//concrete
	ImageMapNumber imnDetail04[]={DITHER4NO};		//rough
	ImageMapNumber imnDetail05[]={DITHER5NO};		//green
	ImageMapNumber imnDetail06[]={DITHER6NO};		//cultivated
	ImageMapNumber imnDetail07[]={DITHER7NO};		//water
	ImageMapNumber imnDetail08[]={DITHER8NO};		//rock

	AT	atDetail00[]={AT(28)};
	AT	atDetail01[]={AT(25),AT(27)};
	AT	atDetail02[]={AT(29),AT(30),AT(31)};
	AT	atDetail03[]={AT(22)};
	AT	atDetail04[]={AT(1),AT(2),AT(5),AT(9),AT(10),AT(24)};
	AT	atDetail05[]={AT(0),AT(6),AT(7),AT(8),AT(15),AT(21)};
	AT	atDetail06[]={AT(11),AT(26)};
	AT	atDetail07[]={AT(13),AT(14),AT(17)};
	AT	atDetail08[]={AT(3),AT(4),AT(16),AT(18),AT(19),AT(20),AT(23),AT(12)};

	SLong imcDetail00=sizeof(imnDetail00)/sizeof(ImageMapNumber);
	SLong imcDetail01=sizeof(imnDetail01)/sizeof(ImageMapNumber);
	SLong imcDetail02=sizeof(imnDetail02)/sizeof(ImageMapNumber);
	SLong imcDetail03=sizeof(imnDetail03)/sizeof(ImageMapNumber);
	SLong imcDetail04=sizeof(imnDetail04)/sizeof(ImageMapNumber);
	SLong imcDetail05=sizeof(imnDetail05)/sizeof(ImageMapNumber);
	SLong imcDetail06=sizeof(imnDetail06)/sizeof(ImageMapNumber);
	SLong imcDetail07=sizeof(imnDetail07)/sizeof(ImageMapNumber);
	SLong imcDetail08=sizeof(imnDetail08)/sizeof(ImageMapNumber);

	SLong atcDetail00=sizeof(atDetail00)/sizeof(AreaType);
	SLong atcDetail01=sizeof(atDetail01)/sizeof(AreaType);
	SLong atcDetail02=sizeof(atDetail02)/sizeof(AreaType);
	SLong atcDetail03=sizeof(atDetail03)/sizeof(AreaType);
	SLong atcDetail04=sizeof(atDetail04)/sizeof(AreaType);
	SLong atcDetail05=sizeof(atDetail05)/sizeof(AreaType);
	SLong atcDetail06=sizeof(atDetail06)/sizeof(AreaType);
	SLong atcDetail07=sizeof(atDetail07)/sizeof(AreaType);
	SLong atcDetail08=sizeof(atDetail08)/sizeof(AreaType);

	numExtraDetails=9;

	extraDetails[0]=new SExtraDetail(imcDetail00,imnDetail00,atcDetail00,atDetail00);
	extraDetails[1]=new SExtraDetail(imcDetail01,imnDetail01,atcDetail01,atDetail01);
	extraDetails[2]=new SExtraDetail(imcDetail02,imnDetail02,atcDetail02,atDetail02);
	extraDetails[3]=new SExtraDetail(imcDetail03,imnDetail03,atcDetail03,atDetail03);
	extraDetails[4]=new SExtraDetail(imcDetail04,imnDetail04,atcDetail04,atDetail04);
	extraDetails[5]=new SExtraDetail(imcDetail05,imnDetail05,atcDetail05,atDetail05);
	extraDetails[6]=new SExtraDetail(imcDetail06,imnDetail06,atcDetail06,atDetail06);
	extraDetails[7]=new SExtraDetail(imcDetail07,imnDetail07,atcDetail07,atDetail07);
	extraDetails[8]=new SExtraDetail(imcDetail08,imnDetail08,atcDetail08,atDetail08);

	//get the palette for these textures from the first land texture imagemap

	//now, prepare all the D3D textures

	//create a single system memory texture surface to re-use
	//for all textures

	DDSCAPS scaps;
	DDSURFACEDESC sd;
	LPDIRECTDRAW2 pDD2;
	LPDIRECTDRAWSURFACE pSys;
	LPDIRECTDRAWSURFACE2 pSys2;
	LPDIRECT3DTEXTURE pSysT;
	HRESULT hr;

	UWord alphaMask=((1<<transpTexture.AlphaBPP)-1)<<transpTexture.AlphaShift;
	UWord alphaShift=transpTexture.AlphaShift-8+transpTexture.AlphaBPP;

	scaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_MIPMAP;

	pDD2=pDirectD->lpDD2;
	
	const DWORD surfFlags=
	DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS|DDSD_MIPMAPCOUNT;

	const DWORD sysSurfCaps=
	DDSCAPS_TEXTURE|DDSCAPS_SYSTEMMEMORY|DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;


	const DWORD vidSurfCaps=
	DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY|DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;

	const SLong _ditherMipLevels=5;
	const SLong _ditherWH=32;

	sd=transpTexture.ddsd;
	sd.dwFlags=surfFlags;
	sd.ddsCaps.dwCaps=sysSurfCaps;
	sd.dwMipMapCount=_ditherMipLevels;	
	sd.dwWidth=sd.dwHeight=_ditherWH;

	hr=pDD2->CreateSurface(&sd,&pSys,NULL);
	DIRECTDRAWERROR(hr);
	hr=pSys->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&pSys2);
	DIRECTDRAWERROR(hr);
	hr=pSys2->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&pSysT);
	DIRECTDRAWERROR(hr);

	UWord* pLUT=(UWord*)lpDDTLandPalLookup;
	
	for (SLong x=0;x<numExtraDetails;x++)
	{
		SExtraDetail& ed=*extraDetails[x];

		for (SLong y=0;y<ed.numTextures;y++)
		{
			//copy the image data onto the system memory surface

			ImageMapDesc* pMap=ed.images[y];
			assert(pMap->w==pMap->h&&"Dither images must be square");
			assert(pMap->w==_ditherWH&&"Dither image must be the correct size");

			SLong mipSize=_ditherWH*_ditherWH;
			SLong mipSkip=1;

			LPDIRECTDRAWSURFACE2 pTemp,pTempV;

			pTemp=pSys2;

			for (SLong z=0;z<_ditherMipLevels-1 && pTemp!=NULL;z++)
			{
				UByte* pCol=pMap->body;
				UByte* pTrn=pMap->alpha;
				UWord* pDst;

				do
				{
					hr=
					pTemp->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|
								DDLOCK_WAIT,NULL);
				}
				while (hr!=DD_OK);

				pDst=(UWord*)sd.lpSurface;

				for (SLong a=0;a<mipSize;a++)
				{
					UWord val,val2;
					
					val=pLUT[*pCol];
					val&=~alphaMask;
					val2=*pTrn;
					val2<<=alphaShift;
					val2&=alphaMask;
					val+=val2;
					*pDst=val;
					pDst++;
					pCol+=mipSkip;
					pTrn+=mipSkip;
				}
				mipSize>>=2;
				mipSkip<<=1;

				pTemp->Unlock(sd.lpSurface);

				pTemp->GetAttachedSurface(&scaps,&pTemp);
			}

			//make sure the last mip map level is blank so that
			//the fade out effect works correctly

			for (;z<_ditherMipLevels && pTemp!=NULL;z++)
			{
				UWord* pDst;

				do
				{
					hr=
					pTemp->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|
								DDLOCK_WAIT,NULL);
				}
				while (hr!=DD_OK);

				pDst=(UWord*)sd.lpSurface;

				for (SLong a=0;a<mipSize;a++)
					*pDst++=0x0000;
				pTemp->Unlock(sd.lpSurface);
			}

			//now, create the video RAM version of this texture

			EDVidTex& evt=ed.vidTex[y];

			sd=transpTexture.ddsd;
			sd.dwFlags=surfFlags;
			sd.ddsCaps.dwCaps=vidSurfCaps;
			sd.dwMipMapCount=_ditherMipLevels;	
			sd.dwWidth=sd.dwHeight=_ditherWH;

			hr=pDD2->CreateSurface(&sd,&evt.pdds,NULL);
			DIRECTDRAWERROR(hr);
			hr=evt.pdds->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&evt.pdds2);
			DIRECTDRAWERROR(hr);
			hr=evt.pdds2->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&evt.pd3dt);
			DIRECTDRAWERROR(hr);
			hr=evt.pd3dt->GetHandle(lpD3DDevice,&evt.d3dht);
			DIRECT3DERROR(hr);

			DDBLTFX	bltfx;
			ZeroMem(&bltfx,sizeof(bltfx));
			bltfx.dwSize=sizeof(bltfx);

			pTemp=pSys2;
			pTempV=evt.pdds2;

			while (pTemp)
			{
				pTempV->Blt(NULL,pTemp,NULL,DDBLT_WAIT,&bltfx);
				while (pTempV->GetBltStatus(DDGBS_ISBLTDONE)!=DD_OK) {}	
				pTemp->GetAttachedSurface(&scaps,&pTemp);
				pTempV->GetAttachedSurface(&scaps,&pTempV);
			}
		}
	}

	RELEASE(pSysT,hr);
	RELEASE(pSys2,hr);
	RELEASE(pSys,hr);

	for (x=0;x<32;x++)
		ditherHandles[x]=0;

	for (x=0;x<numExtraDetails;x++)
	{
		SExtraDetail& ed=*extraDetails[x];

		D3DTEXTUREHANDLE hTexture=ed.vidTex[ed.curTexture].d3dht;

		for (SLong y=0;y<ed.numAreas;y++)
			ditherHandles[ed.areaTypes[y]]=hTexture;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeExtraLandDetail
//Author		Paul.   
//Date			Thu 3 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::FreeExtraLandDetail()
{
	HRESULT hr;

	for (SLong x=0;x<numExtraDetails;x++)
	{
		SExtraDetail& ed=*extraDetails[x];

		for (SLong y=0;y<ed.numTextures;y++)
		{
			EDVidTex& evt=ed.vidTex[y];
			RELEASE(evt.pd3dt,hr);
			RELEASE(evt.pdds2,hr);
			RELEASE(evt.pdds,hr);
		}
		delete extraDetails[x];
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateLandDetailAnimFrames
//Author		Paul.   
//Date			Thu 3 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::UpdateLandDetailAnimFrames(SLong elapsedTime)
{
	for (SLong x=0;x<numExtraDetails;x++)
	{
		SExtraDetail* pED=extraDetails[x];
		if (pED->numTextures>1)
		{
			pED->timerCur-=elapsedTime;
			if (pED->timerCur<0)
			{
				pED->timerCur+=pED->timerReset;
				pED->curTexture++;
				if (pED->curTexture>=pED->numTextures)
					pED->curTexture=0;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		direct_3d
//Author		Paul
//Date			Thu 30 Jan 1997
//
//Description	Initialise an IDirect3D interface
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON direct_3d::direct_3d(DirectDP lpdirectd)
{
	refreshTexture=false;
	lightingEffectsEnabled=TRUE;
	numExtraDetails=0;
	pPolyTree=NULL;
	plainShadeFlag=0;

	LPDIRECTDRAW2	lpDD2;
	lpDD2 			= lpdirectd->lpDD2;
	lpD3D 			= NULL;
	lpD3DDevice 	= NULL;
	lpD3DViewport 	= NULL;

	for (int i=0;i<MAX_PALS;i++){								//PD 06Mar98
		lpDDPalette[i]		= NULL;								//PD 06Mar98
		lpDDPalLookup[i]	= NULL;								//PD 06Mar98
		lpDMPalLookup[i]	= NULL;								//PD 06Mar98
	}
	
	lpDDLandPal=NULL;
	lpDDLandPalLookup=NULL;
	lpDDTLandPalLookup=NULL;

	//PD 06Mar98
	lpD3DLight		= NULL;
	CurrDriver		= -1;
	NumTextures		= 0;
	NumVidTextures	= 0;
	CurrFogColour	= RGBA_MAKE(0xFF,0x00,0xFF,0xFF);			//Magenta fog?
	CurrentFadeValue= 0xFF;										//PD 29Jul97

	bBackClipEnabled= TRUE;										//PD 05Jun97
	TargetFadeColour=(Colour)0;											//PD 05Jun97
	CurrentFadeStep=0;											//PD 05Jun97

	nWhichLandPalette=0;		//Default is Daytime palette	//PD 09Jun97

	//Initialise video ramtexture storeage information

	lpOldestTexture =
	lpNewestTexture = NULL;

	LPVIDRAMTEXTURE	lpVidramtexture = vidramtextures;

	for (int q=0;q<D3DAPP_MAXVIDTEXTURES;q++)
	{
		lpVidramtexture->lpOlderTexture = NULL;
		lpVidramtexture->lpNewerTexture = NULL;
		lpVidramtexture->bInUse = 0;
		lpVidramtexture++;
	}

	InitPaletteData();

	//get blit capabilities
	lpdirectd->lpDirectDD->GetBltCaps(driverDoesAsyncBlt,driverDoesSysMemBlt);

	HRESULT	dderrval;

 	dderrval =
 	lpDD2->QueryInterface(IID_IDirect3D,(LPVOID *)&lpD3D);

	if (dderrval==D3D_OK)
	{
		if (!EnumDevices())
		{
			RELEASE(lpD3D,dderrval);
		}
		else
		{
			if (NumDrivers!=0)
			{
				//find the first hardware accelerated
				//driver

				for (int counter=0;counter<NumDrivers;counter++)
				{
					if (Driver[counter].bIsHardware)
						break;
				}
				if (counter==NumDrivers)	counter=0;

				CurrDriver=counter;
			}
		}
	}
	else
		_Error.EmitSysErr("Creation of IDirect3D failed");

	textureQuality=Save_Data.textureQuality;

	ULong* pp=(ULong*)lastPals;
	for (int bum=0;bum<64*3;*pp++=0xCDCDCDCD,bum++){}

	pPolyTree=new CPolyTree(lpdirectd);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		direct_3d
//Author		Dave Whiteside
//Date			Thu 30 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DES direct_3d::~direct_3d()
{
	ReleaseVideoBuffer();
	delete pPolyTree;
	pPolyTree=NULL;
	CloseDown();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnumDevices
//Author		Dave Whiteside
//Date			Thu 30 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOOL direct_3d::EnumDevices()
{
	HRESULT	dderrval;

	NumDrivers=0;

	dderrval =
	lpD3D->EnumDevices(enumDeviceFunc,(LPVOID)this);

	if (dderrval!=DD_OK)	return (FALSE);

	CurrDriver=0;

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		enumDeviceFunc
//Author		Dave Whiteside
//Date			Thu 30 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
HRESULT WINAPI
direct_3d::enumDeviceFunc(	LPGUID 			lpGuid,
							LPSTR 			lpDeviceDescription,
                      		LPSTR 			lpDeviceName,
							LPD3DDEVICEDESC lpHWDesc,
                      		LPD3DDEVICEDESC lpHELDesc,
							LPVOID 			lpContext)
{
	Direct3DP	direct3dp;

    direct3dp = (Direct3DP)lpContext;

	// Record the D3D driver's inforamation

    memcpy(&direct3dp->Driver[direct3dp->NumDrivers].Guid, lpGuid, sizeof(GUID));
    lstrcpy(direct3dp->Driver[direct3dp->NumDrivers].About, lpDeviceDescription);
    lstrcpy(direct3dp->Driver[direct3dp->NumDrivers].Name, lpDeviceName);

	//Complete description of the drivers hardware caps

	direct3dp->Driver[direct3dp->NumDrivers].Desc = *lpHWDesc;

	// Is this a hardware device or software emulation?  Checking the color
	// model for a valid model works.

    if (lpHWDesc->dcmColorModel)
	{
        direct3dp->Driver[direct3dp->NumDrivers].bIsHardware = TRUE;
        memcpy(&direct3dp->Driver[direct3dp->NumDrivers].Desc, lpHWDesc, sizeof(D3DDEVICEDESC));
    }
	else
	{
        direct3dp->Driver[direct3dp->NumDrivers].bIsHardware = FALSE;
        memcpy(&direct3dp->Driver[direct3dp->NumDrivers].Desc, lpHELDesc, sizeof(D3DDEVICEDESC));
    }

	// Does this driver do texture mapping?

    direct3dp->Driver[direct3dp->NumDrivers].bDoesTextures =
        (direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwTextureCaps &
         D3DPTEXTURECAPS_PERSPECTIVE) ? TRUE : FALSE;

	// Can this driver use a z-buffer?

    direct3dp->Driver[direct3dp->NumDrivers].bDoesZBuffer =
        direct3dp->Driver[direct3dp->NumDrivers].Desc.dwDeviceZBufferBitDepth
                ? TRUE : FALSE;

	// Can this driver do various fog styles

	direct3dp->Driver[direct3dp->NumDrivers].bDoesFogTable =
        direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwRasterCaps &
		D3DPRASTERCAPS_FOGTABLE ? TRUE : FALSE;

	direct3dp->Driver[direct3dp->NumDrivers].bDoesFogVertex =
        direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwRasterCaps &
		D3DPRASTERCAPS_FOGVERTEX ? TRUE : FALSE;

	//get filter mode for TEXTUREMAG

	DWORD tfflags=direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwTextureFilterCaps;

	if (Save_Data.filtering!=0 && tfflags&D3DPTFILTERCAPS_LINEAR)
		direct3dp->Driver[direct3dp->NumDrivers].tfFilterMAG=D3DFILTER_LINEAR;
	else
		direct3dp->Driver[direct3dp->NumDrivers].tfFilterMAG=D3DFILTER_NEAREST;

	//get filter mode for TEXTUREMIN

//	if (gameSettings.m_bUseMipMapping)
	if (Save_Data.filtering>=2)
	{
		if (tfflags&D3DPTFILTERCAPS_LINEARMIPLINEAR)
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMIN=D3DFILTER_LINEARMIPLINEAR;
		else if (tfflags&D3DPTFILTERCAPS_LINEARMIPNEAREST)
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMIN=D3DFILTER_LINEARMIPNEAREST;
		else if (tfflags&D3DPTFILTERCAPS_MIPLINEAR)
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMIN=D3DFILTER_MIPLINEAR;
		else if (tfflags&D3DPTFILTERCAPS_MIPNEAREST)
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMIN=D3DFILTER_MIPNEAREST;
		else if (tfflags&D3DPTFILTERCAPS_MIPNEAREST)
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMIN=D3DFILTER_MIPNEAREST;
		else
		{
			Save_Data.filtering=1;
//		 	gameSettings.m_bUseMipMapping=false;	
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMIN=
				direct3dp->Driver[direct3dp->NumDrivers].tfFilterMAG;
		}

		if (tfflags&D3DPTFILTERCAPS_MIPNEAREST)
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMSK=D3DFILTER_MIPNEAREST;
		else if (tfflags&D3DPTFILTERCAPS_MIPLINEAR)
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMSK=D3DFILTER_MIPLINEAR;
		else 
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMSK=
				direct3dp->Driver[direct3dp->NumDrivers].tfFilterMAG;
	}
	else
	{
		direct3dp->Driver[direct3dp->NumDrivers].tfFilterMIN=
			direct3dp->Driver[direct3dp->NumDrivers].tfFilterMAG;
	}

	if (direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwTextureBlendCaps&D3DPTBLENDCAPS_MODULATEALPHA)
		direct3dp->Driver[direct3dp->NumDrivers].tbBlendMode=D3DTBLEND_MODULATEALPHA;
	else
		direct3dp->Driver[direct3dp->NumDrivers].tbBlendMode=D3DTBLEND_MODULATE;

	//Check source alpha blending caps

	direct3dp->Driver[direct3dp->NumDrivers].bDoesSrcOne =
        direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwSrcBlendCaps &
		D3DPBLENDCAPS_ONE ? TRUE : FALSE;

	direct3dp->Driver[direct3dp->NumDrivers].bDoesSrcSrcAlpha =
        direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwSrcBlendCaps &
		D3DPBLENDCAPS_SRCALPHA ? TRUE : FALSE;

	//Check destination alpha blending caps

	direct3dp->Driver[direct3dp->NumDrivers].bDoesDestZero =
        direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwDestBlendCaps &
		D3DPBLENDCAPS_ZERO ? TRUE : FALSE;

	direct3dp->Driver[direct3dp->NumDrivers].bDoesDestInvSrcAlpha =
        direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwDestBlendCaps &
		D3DPBLENDCAPS_INVSRCALPHA ? TRUE : FALSE;

	direct3dp->Driver[direct3dp->NumDrivers].bDoesAllowZDisable =
		direct3dp->Driver[direct3dp->NumDrivers].Desc.dpcTriCaps.dwMiscCaps &
		D3DPMISCCAPS_MASKZ ? FALSE : FALSE;	//TRUE : FALSE;

	direct3dp->Driver[direct3dp->NumDrivers].bCanDoWindow = FALSE;

    direct3dp->NumDrivers++;

    if (direct3dp->NumDrivers == D3DAPP_MAXD3DDRIVERS)
        return (D3DENUMRET_CANCEL);

    return (D3DENUMRET_OK);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectDriver
//Author		Paul.   
//Date			Fri 31 Jan 1997
//
//Description	Currently selects the first compatible driver
//				needs altering to pick the best available driver
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOOL direct_3d::SelectDriver(DirectDP lpdirectd)
{
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[8]='A';
	globalSpecular=TRUE;	//FALSE;
	globalLighting=TRUE;

	HRESULT		dderrval;

	D3DVIEWPORT	d3dviewportdata;

	fullScreen=lpdirectd->lpDirectDD->isFullScreen();

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[8]='B';
	for (CurrDriver=0;CurrDriver<NumDrivers;CurrDriver++)
		if (VerifyDriver(CurrDriver))
			break;

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[8]='C';
	if (CurrDriver==NumDrivers)	return (FALSE);

	ThisDriver=Driver[CurrDriver];

	maxVertexCount=ThisDriver.Desc.dwMaxVertexCount;
	if (maxVertexCount==0)
		maxVertexCount=D3DAPP_MAXSCENEVERTEXCOUNT;
	else if (maxVertexCount>D3DAPP_MAXSCENEVERTEXCOUNT)
		maxVertexCount=D3DAPP_MAXSCENEVERTEXCOUNT;

	if ((D3DAppExecuteBufferSize=ThisDriver.Desc.dwMaxBufferSize)==0)
		D3DAppExecuteBufferSize=D3DAPP_EXECUTEBUFFERSIZE;

	//Create the D3D device using the selected driver
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[8]='D';

	if (CreateDevice(CurrDriver,lpdirectd))
	{
	 ///	_Error.EmitSysErr("Failed to create D3DDevice");
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[8]='E';

		if (lpD3DDevice!=NULL)
		{
			//Create viewport

			dderrval =
			lpD3D->CreateViewport(&lpD3DViewport,NULL);

			DIRECT3DERROR(dderrval);

			//Attach the viewport to the current D3D device

			dderrval =
			lpD3DDevice->AddViewport(lpD3DViewport);

			DIRECT3DERROR(dderrval)

			//Set the viewport data up

			int	width,height;

			RECT	rect;
			if (!lpdirectd->lpDirectDD->isFullScreen())
				::GetWindowRect(lpdirectd->hWnd,&rect);
			else{
			 	rect.top=rect.left=0;
				rect.bottom=lpdirectd->DDModes[lpdirectd->DDCurrMode].height;
				rect.right=lpdirectd->DDModes[lpdirectd->DDCurrMode].width;
			}
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;

			ZeroMem (&d3dviewportdata,sizeof(d3dviewportdata));

		    d3dviewportdata.dwSize=sizeof (D3DVIEWPORT);
	    	d3dviewportdata.dwX = 0;
			d3dviewportdata.dwY = 0;
			d3dviewportdata.dwWidth = width;
			d3dviewportdata.dwHeight = height;
			d3dviewportdata.dvScaleX = (Float)width/2.0;
			d3dviewportdata.dvScaleY = (Float)height/2.0;
			d3dviewportdata.dvMaxX = 1.0;
			d3dviewportdata.dvMaxY = 1.0;
			d3dviewportdata.dvMaxZ = Max_Z_Scale;
			d3dviewportdata.dvMinZ = Max_Z_Scale/fMaxVisRange;
		
			lpD3DViewport->SetViewport(&d3dviewportdata);

			InitView(lpdirectd);
		}

		SLong minTextureRAM=opaqueTexture.bPalettized?512*1024:1024*1024;
		SLong spareTextureRAM=SLong(TextureRAMFree)-(minTextureRAM<<1);

		if (gameSettings.m_bBypassMemCheck==FALSE&&TextureRAMFree<minTextureRAM)
			_Error.EmitSysErr("Not enough texture RAM for landscape");

		if (spareTextureRAM<=0 || !lpdirectd->lpDirectDD->isFullScreen())
		{
			NUM_256_TEXTURES=0;
			NUM_128_TEXTURES=8;
			NUM_64_TEXTURES=64;
			NUM_32_TEXTURES=16;
			NUM_16_TEXTURES=0;
			NUM_8_TEXTURES=0;
		}
		else
		{		
			if (!opaqueTexture.bPalettized) spareTextureRAM>>=1;

			SLong testVal0,testVal1,testVal2;

			testVal0=1024*1024;
			testVal1=(1024+512)*1024;
			testVal2=2048*1024;

			if (Save_Data.filtering>=2)
			{
				testVal0=testVal0+(testVal0>>1)+(testVal0>>2)+(testVal0>>3);
				testVal1=testVal1+(testVal1>>1)+(testVal1>>2)+(testVal1>>3);
				testVal2=testVal2+(testVal2>>1)+(testVal2>>2)+(testVal2>>3);
			}

			if (spareTextureRAM<testVal0)
			{
				NUM_256_TEXTURES=0;
				NUM_128_TEXTURES=16;
				NUM_64_TEXTURES=32-8;
				NUM_32_TEXTURES=48+32;
				NUM_16_TEXTURES=0;
				NUM_8_TEXTURES=0;
				//TOTAL=96-8+32=120
			}
			else
			{
				NUM_256_TEXTURES=8;
				NUM_128_TEXTURES=14;	//16;
				NUM_64_TEXTURES=24;		//32;
				NUM_32_TEXTURES=96;		//32;
				NUM_16_TEXTURES=0;
				NUM_8_TEXTURES=0;
				//TOTAL=				//88
			}
/*			else if (spareTextureRAM<testVal1)
			{
				NUM_256_TEXTURES=8;
				NUM_128_TEXTURES=16;
				NUM_64_TEXTURES=32;
				NUM_32_TEXTURES=32;
				//TOTAL=88
			}
			else if (spareTextureRAM<testVal2)
			{
				NUM_256_TEXTURES=8;
				NUM_128_TEXTURES=16;
				NUM_64_TEXTURES=32;
				NUM_32_TEXTURES=32;
				//TOTAL=88
			}
			else
			{
				NUM_256_TEXTURES=8;
				NUM_128_TEXTURES=16;
				NUM_64_TEXTURES=32;
				NUM_32_TEXTURES=32;
				//TOTAL=88
			}
*/
		}

		vidram256maps=NUM_256_TEXTURES!=0?new VIDRAMTEXTURE[NUM_256_TEXTURES]:NULL;
		vidram128maps=NUM_128_TEXTURES!=0?new VIDRAMTEXTURE[NUM_128_TEXTURES]:NULL;
		vidram64maps=NUM_64_TEXTURES!=0?new VIDRAMTEXTURE[NUM_64_TEXTURES]:NULL;
		vidram32maps=NUM_32_TEXTURES!=0?new VIDRAMTEXTURE[NUM_32_TEXTURES]:NULL;
		vidram16maps=NUM_16_TEXTURES!=0?new VIDRAMTEXTURE[NUM_16_TEXTURES]:NULL;
		vidram8maps=NUM_8_TEXTURES!=0?new VIDRAMTEXTURE[NUM_8_TEXTURES]:NULL;
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[8]='F';

		CreateLandTextureBuffers(lpdirectd);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[8]='G';

		CreateLandExecuteBuffer();
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[8]='H';

		return (TRUE);
	}
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[8]='I';

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitView
//Author		Paul.   
//Date			Thu 13 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOOL direct_3d::InitView(DirectDP lpdirectd)
{
	D3DEXECUTEBUFFERDESC	xbufdesc;
	LPDIRECT3DEXECUTEBUFFER	lpxbuf;
	D3DEXECUTEDATA			ExData;

	RECT	rect;
	if (!lpdirectd->lpDirectDD->isFullScreen())
		::GetWindowRect(lpdirectd->hWnd,&rect);
	else{
	 	rect.top=rect.left=0;
		rect.bottom=lpdirectd->DDModes[lpdirectd->DDCurrMode].height;
		rect.right=lpdirectd->DDModes[lpdirectd->DDCurrMode].width;
	}
	float fwidth = rect.right - rect.left;
	float fheight = rect.bottom - rect.top;

	float fmaxvisrange = 100000;

	fMaxVisRange = fmaxvisrange;
	frMaxVisRange = Max_Z_Scale*.99999/fMaxVisRange;

//DeadCode PD 16Dec98 	float e1 = fmaxvisrange/(2.0*(fmaxvisrange-fwidth));
//DeadCode PD 16Dec98 	float e2 = -((fwidth/2.0)*fmaxvisrange)/(fmaxvisrange-fwidth);

	HRESULT	dderrval;

	LPVOID				lpBufStart,
						lpInsStart,
						lpPointer;

    ZeroMem(&xbufdesc, sizeof(D3DEXECUTEBUFFERDESC));
    xbufdesc.dwSize			= sizeof(D3DEXECUTEBUFFERDESC);
    xbufdesc.dwFlags 	 	= D3DDEB_BUFSIZE;
    xbufdesc.dwBufferSize 	= D3DAPP_EXECUTEBUFFERSIZE;

	lpD3DDevice->CreateExecuteBuffer(&xbufdesc,&lpxbuf,NULL);

	lpxbuf->Lock(&xbufdesc);

	lpBufStart = xbufdesc.lpData;

	lpPointer = lpBufStart;

	lpInsStart = lpPointer;

	//General status setting

	int	dwWidth,dwHeight;

	dwWidth = rect.right - rect.left;
	dwHeight = rect.bottom - rect.top;

	//Render state setting

	D3DTEXTUREFILTER tfFilterMIN,tfFilterMAG;
	D3DTEXTUREBLEND	tbBlendMode;

	tfFilterMIN=Driver[CurrDriver].tfFilterMIN;
	tfFilterMAG=Driver[CurrDriver].tfFilterMAG;
	tbBlendMode=Driver[CurrDriver].tbBlendMode;

 	OP_STATE_RENDER(17, lpPointer);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_ONE,lpPointer);	//PD 06Oct97
	STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ZERO,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SHADEMODE,D3DSHADE_GOURAUD,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREPERSPECTIVE,TRUE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_ZENABLE,TRUE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL,lpPointer);
	STATE_DATA(D3DRENDERSTATE_FILLMODE,D3DFILL_SOLID,lpPointer);
	STATE_DATA(D3DRENDERSTATE_DITHERENABLE,TRUE,lpPointer);

	STATE_DATA(D3DRENDERSTATE_ANTIALIAS,FALSE,lpPointer);

	STATE_DATA(D3DRENDERSTATE_WRAPU, FALSE, lpPointer);
	STATE_DATA(D3DRENDERSTATE_WRAPV, FALSE, lpPointer);

	STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,tbBlendMode,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,tfFilterMAG,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,tfFilterMIN,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,lpPointer);

	OP_EXIT(lpPointer);

	lpxbuf->Unlock();

	ZeroMem(&ExData,sizeof(ExData));

	ExData.dwSize = sizeof(D3DEXECUTEDATA);
	ExData.dwInstructionOffset = (ULONG) 0;
	ExData.dwInstructionLength = (ULONG)((char*)lpPointer - (char*)lpInsStart);

	lpxbuf->SetExecuteData(&ExData);

	lpD3DDevice->BeginScene();

	lpD3DDevice->Execute(lpxbuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);

	lpD3DDevice->EndScene();

	RELEASE(lpxbuf,dderrval);

	bPlayerTextures = FALSE;

	return (TRUE);
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
Bool direct_3d::SetPlayerTextures(struct _DirectDraw* lpDirectD, Bool flag)
{
	Bool	retval = bPlayerTextures;
	bPlayerTextures = flag;
	return (retval);
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
Bool direct_3d::SetZUpdate(struct _DirectDraw* lpDirectD,Bool flag)
{
	Bool oldState=currZWriteState;
	currZWriteState=flag;

 	pPolyTree->RenderPolys(this);

	bool bubfedge=fEdgeTestActive;
	fEdgeTestActive=true;

  	FlushNZDraw(lpDirectD,nzbufXXB);

	fEdgeTestActive=bubfedge;

	return oldState;
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
void direct_3d::SetViewParams(ANGLES fov,Window* w,DirectDP lpdirectd)
{
	Float	temp;

	Float	orgx, orgy;

	Float	window_width, window_height;

	RECT	rect;
	if (!lpdirectd->lpDirectDD->isFullScreen())
		::GetWindowRect(lpdirectd->hWnd,&rect);
	else{
	 	rect.top=rect.left=0;
		rect.bottom=lpdirectd->DDModes[lpdirectd->DDCurrMode].height;
		rect.right=lpdirectd->DDModes[lpdirectd->DDCurrMode].width;
	}
	float screen_height = rect.bottom - rect.top;

	winHeight=rect.bottom-rect.top;
	winWidth=rect.right-rect.left;

	//calc width & height of window on screen

	window_width = w->VirtualWidth/w->virtualXscale;
	window_height = w->VirtualHeight/w->virtualYscale;

	fov=Angles(UWord(fov)>>1);
	fpTan(fov,FoV);
	rFoV=1./FoV;
	aspectRatio=FoV*(window_height/window_width);
	recipAspectRatio=1./aspectRatio;

	//origin is in the center of this window

	viewdata.originx = window_width/2.0;
	viewdata.originy = (Float)	screen_height - window_height/2.0;

	viewdata.scalex = window_width/2.0;
	viewdata.scaley = window_height/2.0;

	viewdata.clipLft = 	viewdata.originx-viewdata.scalex;
	viewdata.clipRgt = 	viewdata.originx+viewdata.scalex;
	viewdata.clipTop =	viewdata.originy-viewdata.scaley;
	viewdata.clipBot =	viewdata.originy+viewdata.scaley;
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
BOOL direct_3d::SetMatrices(DirectDP lpdirectd,SLong maxvisrange,ANGLES viewang)
{
	Float 	sin_ang,
			cos_ang;
	Float 	h, D, F;

	int		width,
			height;

	fMaxVisRange = (Float)maxvisrange;
	frMaxVisRange=.99999/fMaxVisRange;
	fZBufScaleSwitchRange=8000;	//maxvisrange>>5;

	//h = half the height of viewing frustrum
	//D = distance of projection plane from the viewer (always 1.0)
	//F = distance between the front and back clipping planes
	//		(fMaxVisRange-1.0)

	D = 1.0;

	F = fMaxVisRange - D;

	viewdata.viewang = viewang;

	viewang = (Angles)(viewang>>1);

	h = D * 1.0; //sin_ang/cos_ang;	// h = D.tan(theta/2)

	fConeGradient = h;

	width=winWidth;
	height=winHeight;

	viewdata.D = D;
	viewdata.F = fMaxVisRange;
	viewdata.h = h;

	viewdata.hoD = h/D;
	viewdata.R = F-D;
	viewdata.FoR = viewdata.F/viewdata.R;						//PD 12Jun97
	viewdata.sD = viewdata.D*SZ_SCALE;							//PD 13Jun97

	//Modify the viewport data accordingly

	D3DVIEWPORT	d3dviewportdata;
	ZeroMem (&d3dviewportdata,sizeof(d3dviewportdata));
    d3dviewportdata.dwSize=sizeof (D3DVIEWPORT);
    d3dviewportdata.dwX = 0;
	d3dviewportdata.dwY = 0;
	d3dviewportdata.dwWidth = width;
	d3dviewportdata.dwHeight = height;
	d3dviewportdata.dvScaleX = (Float)width/2.0;
	d3dviewportdata.dvScaleY = (Float)height/2.0;
	d3dviewportdata.dvMaxX = 1.0;
	d3dviewportdata.dvMaxY = 1.0;
	d3dviewportdata.dvMaxZ = Max_Z_Scale;
	d3dviewportdata.dvMinZ = Max_Z_Scale/fMaxVisRange;

	lpD3DViewport->SetViewport(&d3dviewportdata);

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFog
//Author		Paul.   
//Date			Fri 23 Oct 1998
//------------------------------------------------------------------------------
void direct_3d::SetFog(UByte r,UByte g,UByte b)
{
	lastFogRed=r;
	lastFogGreen=g;
	lastFogBlue=b;

	void *pinst=(void*)(((UByte*)normalXXB.xbDesc.lpData)+normalXXB.instOffset);
	void *pistart=pinst;
	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGCOLOR,RGB_MAKE(r,g,b),pinst);
	normalXXB.instOffset+=ULong(pinst)-ULong(pistart);

	pinst=(void*)(((UByte*)transpXXB.xbDesc.lpData)+transpXXB.instOffset);
	pistart=pinst;
	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGCOLOR,RGB_MAKE(r,g,b),pinst);
	transpXXB.instOffset+=ULong(pinst)-ULong(pistart);

	pinst=(void*)(((UByte*)nzbufXXB.xbDesc.lpData)+nzbufXXB.instOffset);
	pistart=pinst;
	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGCOLOR,RGB_MAKE(r,g,b),pinst);
	nzbufXXB.instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFog
//Author		Paul.   
//Date			Fri 23 Oct 1998
//------------------------------------------------------------------------------
void direct_3d::GetFog(UByte& r,UByte& g,UByte& b,SLong&,SLong&)
{
	r=fogRedVal;
	g=fogGreenVal;
	b=fogBlueVal;
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
void direct_3d::SetFog(UByte r,UByte g,UByte b, SLong start, SLong end)
{
	D3DCOLOR dcFogColor=RGB_MAKE(r,g,b);

//	colour=(Colour)(colour&0xFF);
	CurrFogStart=start;
	CurrFogEnd=end;
	viewdata.FogStart=(Float)start;
	viewdata.sqFogStart=viewdata.FogStart*viewdata.FogStart;
	viewdata.FogEnd=(Float)end;
	viewdata.sqFogEnd=viewdata.FogEnd*viewdata.FogEnd;
	viewdata.rangeFogConst=255./(viewdata.FogEnd-viewdata.FogStart);

//	if (colour==CurrFogColour)	return;
	if (dcFogColor==CurrFogColour)	return;

	CurrFogColour=dcFogColor;	//colour;

//	dcFogColor = RGB_MAKE(	peSrcPalette[colour].peRed,
//							peSrcPalette[colour].peGreen,
//							peSrcPalette[colour].peBlue);

	fogRedVal 	= 	r;//peSrcPalette[colour].peRed; 
	fogGreenVal = 	g;//peSrcPalette[colour].peGreen; 
	fogBlueVal 	= 	b;//peSrcPalette[colour].peBlue; 

	dcGlobalFogColour=dcFogColor;								//PD 01Oct97

	D3DEXECUTEBUFFERDESC	xbufdesc;
	LPDIRECT3DEXECUTEBUFFER	lpxbuf;
	D3DEXECUTEDATA			ExData;

	HRESULT	dderrval;

	LPVOID				lpBufStart,
						lpInsStart,
						lpPointer;

    ZeroMem(&xbufdesc, sizeof(D3DEXECUTEBUFFERDESC));
    xbufdesc.dwSize = sizeof(D3DEXECUTEBUFFERDESC);
    xbufdesc.dwFlags = D3DDEB_BUFSIZE;
    xbufdesc.dwBufferSize = 1024;								//PD 25Feb97

	lpD3DDevice->CreateExecuteBuffer(&xbufdesc,&lpxbuf,NULL);

	lpxbuf->Lock(&xbufdesc);

	lpBufStart = xbufdesc.lpData;

	lpPointer = lpBufStart;

	lpInsStart = lpPointer;

	// Fog settings

	Float	FOG_TABLESTART,
			FOG_TABLEEND,
			FOG_TABLEDENSITY;

	FOG_TABLESTART = 0.1;	//(Float)start;
	FOG_TABLEEND = 1.0;		//(Float)end;
	FOG_TABLEDENSITY = 1.0;

	#define FOG_START         FOG_TABLESTART
	#define FOG_END           FOG_TABLEEND  
	#define FOG_DENSITY       FOG_TABLEDENSITY

	if (!Driver[CurrDriver].bDoesFogVertex)						//RDH 15Sep97
	{
    OP_STATE_RENDER(6, lpPointer);
	STATE_DATA	(D3DRENDERSTATE_FOGENABLE,		FALSE,lpPointer);
	STATE_DATA	(D3DRENDERSTATE_FOGCOLOR,		RGBA_MAKE(255,0,0,0),lpPointer);
	STATE_DATA	(D3DRENDERSTATE_FOGTABLEMODE,	D3DFOG_LINEAR,lpPointer);
	STATE_DATA	(D3DRENDERSTATE_FOGTABLESTART,	D3DVAL(1.0),lpPointer);
	STATE_DATA	(D3DRENDERSTATE_FOGTABLEEND,	D3DVAL(0.0),lpPointer);
	STATE_DATA	(D3DRENDERSTATE_FOGTABLEDENSITY,D3DVAL(0.0),lpPointer);

	}else{

	OP_STATE_LIGHT(1,lpPointer);
	STATE_DATA (D3DLIGHTSTATE_FOGMODE,D3DFOG_NONE,lpPointer);

    OP_STATE_RENDER(3, lpPointer);
	STATE_DATA	(D3DRENDERSTATE_FOGENABLE,		bGlobalFogFlag,lpPointer);//PD 09Oct97
	STATE_DATA	(D3DRENDERSTATE_FOGCOLOR,		dcFogColor,lpPointer);
	STATE_DATA	(D3DRENDERSTATE_FOGTABLEMODE,	D3DFOG_NONE,lpPointer);

	}

	OP_EXIT(lpPointer);

	lpxbuf->Unlock();

	ZeroMem(&ExData,sizeof(ExData));

	ExData.dwSize = sizeof(D3DEXECUTEDATA);
	ExData.dwInstructionOffset = (ULONG) 0;
	ExData.dwInstructionLength = (ULONG)((char*)lpPointer - (char*)lpInsStart);

	lpxbuf->SetExecuteData(&ExData);

	lpD3DDevice->Execute(lpxbuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);

	RELEASE(lpxbuf,dderrval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginScene
//Author		Paul.   
//Date			Thu 6 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::BeginScene(struct _DirectDraw* lpDirectD)
{
	//flag all vidram textures as available for recycling...
	for (int j=0;j<NumVidTextures;vidramtextures[j++].bInUse=0);

	if (lpD3DDevice==NULL)										//PD 30Jul97
	_Error.ReallyEmitSysErr("3D Hardware acceleration is not enabled");//PD 30Jul97

	lpD3DDevice->BeginScene();

	globalAlphaValue=AmbientALPHA;
	isLightShaded=false;
	isTranspFade=false;
	rangeFogEnabled=false;
	textureUploads=0;
	clipTestEnabled=true;
	bItemFoggingActive=false;
	currZWriteState=TRUE;
	lastPolyType=T_NONE;
	fMipMapEnabled=true;
	periphData.count=0;
	fEdgeTestActive=false;
	decreaseTextureQuality=false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPlainLine
//Author		Paul.   
//Date			Mon 7 Sep 1998
//------------------------------------------------------------------------------
void direct_3d::AddPlainLine(DirectD* pDirectD,LPLINETYPE lpLineType)
{
	//if the new line won't fit in the buffer
	//then execute the current contents of the 
	//buffer first

	const SLong _LineDataLen=	sizeof(D3DINSTRUCTION)+
								sizeof(D3DPROCESSVERTICES)+
								sizeof(D3DINSTRUCTION)+
								sizeof(D3DINSTRUCTION)+
								sizeof(D3DLINE);

	if (lineXB.vertCount+2>lineXB._max_verts ||
		_LineDataLen>(lineXB._inst_len-lineXB.instOffset))
	{
		FlushPLDraw(pDirectD,lineXB);
	}

	ULong vBase=lineXB.vertCount;

	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)lineXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)lineXB.xbDesc.lpData)+lineXB.instOffset);
	void* pistart=pinst;

	//get a pointer to the current input poly definition
	vertex** ppv=&lpLineType->lpStartVertex;
	vertex* pv=*ppv++;		//start vertex

	//initialise clipping flags...
	UWord orClip,andClip;
	orClip=CF3D_NULL;
	andClip=CF3D_ALL;

	R3DTLVERTEX startVert,endVert;

	//this routine will not get called unless the line
	//is at least partly visible so prepare to clip if
	//needed

	R3DCOLOR shadePolyColor;
	R3DCOLOR& paletteEntry=*(R3DCOLOR*)&palette[lpLineType->colour].dcColorVal;

	ULong interpFlag=IF3D_NULL;
	
	R3DCOLOR basePolyColor;
	basePolyColor.r=((SLong(paletteEntry.r)*vShadeRed)>>8);
	basePolyColor.g=((SLong(paletteEntry.g)*vShadeGreen)>>8);
	basePolyColor.b=((SLong(paletteEntry.b)*vShadeBlue)>>8);

	if (pv->intensity!=-1)
	{
		SWord cval=pv->intensity;
		shadePolyColor.r=(basePolyColor.r*cval)>>8;
		shadePolyColor.g=(basePolyColor.g*cval)>>8;
		shadePolyColor.b=(basePolyColor.b*cval)>>8;
	}
	else *(D3DCOLOR*)&shadePolyColor=*(D3DCOLOR*)&basePolyColor;	//paletteEntry;

	shadePolyColor.a=AmbientALPHA;

	UWord cf=pv->clipFlags;
	orClip|=cf;
	andClip&=cf;

	startVert.sx=D3DVALUE(pv->bx.f);
	startVert.sy=D3DVALUE(pv->by.f);
	startVert.sz=D3DVALUE(pv->bz.f);
	startVert.clipFlags=cf+interpFlag;
	startVert.color=*(D3DCOLOR*)&shadePolyColor;

	pv=*ppv;				//end vertex
	cf=pv->clipFlags;
	orClip|=cf;
	andClip&=cf;

	endVert.sx=D3DVALUE(pv->bx.f);
	endVert.sy=D3DVALUE(pv->by.f);
	endVert.sz=D3DVALUE(pv->bz.f);
	endVert.clipFlags=cf+interpFlag;
	endVert.color=*(D3DCOLOR*)&shadePolyColor;

	//just on the off chance that something has
	//gone wrong (Not that it ever does!) check
	//the state of the clip flags and quit if
	//we need to

	if (andClip!=CF3D_NULL)	return;	//ABORT NOW!!

	if (orClip!=CF3D_NULL && GenericLineClip(startVert,endVert)<0)
		return; //ABORT NOW!!

	*ptlvert++=startVert;
	*ptlvert=endVert;

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	*(D3DCOLOR*)&shadePolyColor=specularNULL;

	shadePolyColor.a=0xFF;

	for (int i=0;i<2;i++)
	{
		ptlvert->specular=*(D3DCOLOR*)&shadePolyColor;
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx);
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy);
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);
		ptlvert++;
	}

	OP_LINE_LIST(1,pinst);
	LPD3DLINE pD3DLine=(LPD3DLINE)pinst;
	pD3DLine->v1=vBase++;
	pD3DLine->v2=vBase++;
	pD3DLine++;
	pinst=(void*)pD3DLine;

	lineXB.vertCount=vBase;
	lineXB.instOffset+=ULong(pinst)-ULong(pistart);
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPlainPoint
//Author		Paul.   
//Date			Mon 7 Sep 1998
//------------------------------------------------------------------------------
#pragma optimize("y",off)
void direct_3d::AddPlainPoint(DirectD* pDirectD,LPPOINTTYPE lpPointType)
{
				  
	//get a pointer to the current input poly definition
	vertex* pv=lpPointType->lpVertex;

	if (pv->clipFlags!=CF3D_NULL) return;	//ABORT NOW!!

	//if the new point won't fit in the buffer
	//then execute the current contents of the 
	//buffer first

	const SLong _PointDataLen=	sizeof(D3DINSTRUCTION)+
								sizeof(D3DPROCESSVERTICES)+
								sizeof(D3DINSTRUCTION)+
								sizeof(D3DINSTRUCTION)+
								sizeof(D3DPOINT);

	if (pointXB.vertCount+2>pointXB._max_verts ||
		_PointDataLen>(pointXB._inst_len-pointXB.instOffset))
	{
		FlushPPDraw(pDirectD,pointXB);
	}

	ULong vBase=pointXB.vertCount;

	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)pointXB.xbDesc.lpData)+vBase;
	void* pinst=(void*)(((UByte*)pointXB.xbDesc.lpData)+pointXB.instOffset);
	void* pistart=pinst;

	R3DCOLOR shadePolyColor;
	R3DCOLOR& paletteEntry=*(R3DCOLOR*)&palette[lpPointType->colour].dcColorVal;

	ULong interpFlag=IF3D_NULL;
	
	R3DCOLOR basePolyColor;
	basePolyColor.r=((SLong(paletteEntry.r)*vShadeRed)>>8);
	basePolyColor.g=((SLong(paletteEntry.g)*vShadeGreen)>>8);
	basePolyColor.b=((SLong(paletteEntry.b)*vShadeBlue)>>8);
	basePolyColor.a=AmbientALPHA;

	*(D3DCOLOR*)&shadePolyColor=*(D3DCOLOR*)&basePolyColor;	//paletteEntry;

	shadePolyColor.a=AmbientALPHA;

	ptlvert->sx=D3DVALUE(pv->bx.f);
	ptlvert->sy=D3DVALUE(pv->by.f);
	ptlvert->sz=D3DVALUE(pv->bz.f);
	ptlvert->clipFlags=interpFlag;
	ptlvert->color=*(D3DCOLOR*)&shadePolyColor;

	//do the body 2 screen style thing

	*(D3DCOLOR*)&shadePolyColor=specularNULL;

	shadePolyColor.a=0xFF;
	ptlvert->specular=*(D3DCOLOR*)&shadePolyColor;
	D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
	ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
	LCLIP_XVAL(ptlvert->sx);
	ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
	LCLIP_YVAL(ptlvert->sy);
	ptlvert->rhw=MAKE_RHW(ptlvert->sz);
	ptlvert->sz=MAKE_SZ(ptlvert->sz);

//DeadCode PD 01Apr99 	OP_POINT_LIST(1,vBase++,pinst);
	OP_POINT_LIST(vBase,1,pinst);
	vBase++;

	pointXB.vertCount=vBase;

	pointXB.instOffset+=ULong(pinst)-ULong(pistart);
				
}
#pragma optimize("",on)

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EndScene
//Author		Paul.   
//Date			Thu 6 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::EndScene(struct _DirectDraw* lpDirectD)
{
	FlushPTDraw(lpDirectD,normalXXB);
	FlushPCDraw(lpDirectD,plaincXB);

	FlushPPDraw(lpDirectD,pointXB);

	FlushPTDraw(lpDirectD,maskedXXB);
	FlushPTDraw(lpDirectD,transpXXB);

	FlushPTDraw(lpDirectD,fontXXB);
	FlushPLDraw(lpDirectD,lineXB);

	if (pPolyTree) pPolyTree->RenderPolys(this);

	FlushNZDraw(lpDirectD,nzbufXXB);

	if (periphData.count)
		RenderPeripheralBlobs(lpDirectD,transpXXB);

	Add2DEffect(lpDirectD,(TWODEFFECT)0);

	lpD3DDevice->EndScene();

	if (decreaseTextureQuality)
	{
		//not enough texture RAM on the last frame so 
		//change some options on the next frame so that there is a better
		//chance of the textures fitting
		if (Save_Data.filtering==3)		FreeExtraLandDetail();

		if (Save_Data.filtering>=2)
			Save_Data.filtering--;
		else if (Save_Data.textureQuality>0)
		{
			Save_Data.textureQuality--;
			textureQuality=Save_Data.textureQuality;
		}
		ReleaseTextures();
	}
}

void direct_3d::End3DScene(struct _DirectDraw* lpDirectD)
{
	FlushPTDraw(lpDirectD,normalXXB);
	FlushPCDraw(lpDirectD,plaincXB);

	FlushPPDraw(lpDirectD,pointXB);

	FlushPTDraw(lpDirectD,maskedXXB);
	FlushPTDraw(lpDirectD,transpXXB);

	FlushPTDraw(lpDirectD,fontXXB);
	FlushPLDraw(lpDirectD,lineXB);

	if (pPolyTree) pPolyTree->RenderPolys(this);

	FlushNZDraw(lpDirectD,nzbufXXB);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TextureLoaded
//Author		Paul.   
//Date			Tue 10 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
direct_3d::LPVIDRAMTEXTURE direct_3d::TextureLoaded(VIDRAMTEXTURE& vrt)
{
	LPVIDRAMTEXTURE pvrt=lpNewestTexture;

	while (pvrt)
	{
		if (pvrt->lpImageMap==vrt.lpImageMap)
			return pvrt;
		else
			pvrt=pvrt->lpOlderTexture;
	}
	return (LPVIDRAMTEXTURE)NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrepTexture
//Author		Paul.   
//Date			Mon 23 Feb 1998
//------------------------------------------------------------------------------
void direct_3d::PrepTexture(LPDIRECTDRAWSURFACE2 lpDDTSurf,
							DDSURFACEDESC& tmsd,
							VIDRAMTEXTURE& newtexture,int nTScale)
{
	HRESULT	dderrval;

	D3DAppTextureFormat* pCurFmt;

	if (newtexture.bHasAlpha)		pCurFmt=&transpTexture;
	else if (newtexture.bIsMasked)	pCurFmt=&maskedTexture;
	else							pCurFmt=&opaqueTexture;

	D3DAppTextureFormat& curFmt=*pCurFmt;

	// Copy the texture map data onto the
	// new surface
	do
	{
		dderrval=lpDDTSurf->Lock(NULL,
							&tmsd,
							DDLOCK_SURFACEMEMORYPTR |
							DDLOCK_WAIT,
							NULL);
	}
	while (dderrval!=DD_OK);

	UByte* srcp = (UByte*)(newtexture.lpImageMap->body);
	UByte* alphap = (UByte*)(newtexture.lpImageMap->alpha);
	UByte* dstp = (UByte*)tmsd.lpSurface;
	ULong palIndex=ULong(newtexture.lpImageMap->paletteindex);
	ULong offset=ULong(tmsd.lPitch);

	int	bytesPerPixel=curFmt.ddsd.ddpfPixelFormat.dwRGBBitCount>>3;
	int textureWidth;

	if (nTScale==1) 		textureWidth=newtexture.dwWidth;
	else if (nTScale==2) 	textureWidth=newtexture.dwWidth<<2;
	else textureWidth=		newtexture.dwWidth<<4;

	int	row;
	switch (bytesPerPixel)
	{
	case 1:
		for (row=0;row<newtexture.dwHeight;row++)
		{
			UByte* src2p=srcp;
			UByte* dst2p=dstp;
			for (int col=0;col<newtexture.dwWidth;col++,src2p+=nTScale)
			{
				if (*src2p==0x00)						*dstp++=ARTWORKMASK;
				else if (*src2p==UByte(ARTWORKMASK))	*dstp++=0x00;
				else									*dstp++=*src2p;
			}
			srcp+=textureWidth;
			dstp=dst2p+offset;
		}
		break;

	case 2:
		if (newtexture.bHasAlpha){
			//Prepare to insert alpha information
			UWord alphaScale=8-curFmt.AlphaBPP;
			UWord alphaShift=curFmt.AlphaShift;
			UWord alphaMask=((1<<curFmt.AlphaBPP)-1)<<alphaShift;

			for (row=0;row<newtexture.dwHeight;row++){
				UByte* alpha2p=alphap;
				UByte* src2p=srcp;
				UWord* lpLUT=(UWord*)lpDMPalLookup[palIndex];
				UByte* dst2p=dstp;
				for (int col=0;col<newtexture.dwWidth;col++,src2p+=nTScale,alpha2p+=nTScale){
					UWord tmp=lpLUT[*src2p]&~alphaMask;
					UWord alp=((*alpha2p)>>alphaScale)<<alphaShift;
					*(UWord*)dstp=(tmp+alp);
					dstp+=2;
				}
				srcp+=textureWidth;
				alphap+=textureWidth;
				dstp=dst2p+offset;
			}
		}else{
			UWord* lpLUT=(UWord*)((newtexture.bIsMasked)?lpDMPalLookup[palIndex]:lpDDPalLookup[palIndex]);
			for (row=0;row<newtexture.dwHeight;row++){
				UByte* src2p=srcp;
				UByte* dst2p=dstp;
				for (int col=0;col<newtexture.dwWidth;col++,src2p+=nTScale){
					*(UWord*)dstp=lpLUT[*src2p];
					dstp+=2;
				}
				srcp+=textureWidth;
				dstp=dst2p+offset;
			}
		}
		break;
	}
	lpDDTSurf->Unlock(tmsd.lpSurface);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrepMipMap
//Author		Paul.   
//Date			Tue 3 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::PrepMipMap(	LPDIRECTDRAWSURFACE2 lpDDTTopSurf,
							DDSURFACEDESC tmsd,
							VIDRAMTEXTURE& newtexture)
{
	HRESULT	dderrval;

	D3DAppTextureFormat* pCurFmt;

	if (newtexture.bHasAlpha)		pCurFmt=&transpTexture;
	else if (newtexture.bIsMasked)	pCurFmt=&maskedTexture;
	else							pCurFmt=&opaqueTexture;

	D3DAppTextureFormat& curFmt=*pCurFmt;

	LPDIRECTDRAWSURFACE2 lpDDTSurf=lpDDTTopSurf;

	for (SLong mipLevels=0;/*mipLevels<newtexture.mipMapLevels*/;mipLevels++)
	{
		// Copy the texture map data onto the
		// new surface

		do
		{
			dderrval=lpDDTSurf->Lock(NULL,
								&tmsd,
								DDLOCK_SURFACEMEMORYPTR |
								DDLOCK_WAIT,
								NULL);
		}
		while (dderrval!=DD_OK);

		UByte* srcp = (UByte*)(newtexture.lpImageMap->body);
		UByte* alphap = (UByte*)(newtexture.lpImageMap->alpha);
		UByte* dstp = (UByte*)tmsd.lpSurface;
		ULong palIndex=ULong(newtexture.lpImageMap->paletteindex);
		ULong offset=ULong(tmsd.lPitch);

		int	bytesPerPixel=curFmt.ddsd.ddpfPixelFormat.dwRGBBitCount>>3;

		int dx=newtexture.lpImageMap->w/tmsd.dwWidth;
		int dy=newtexture.lpImageMap->w*(newtexture.lpImageMap->h/tmsd.dwHeight);

		int	row;
		switch (bytesPerPixel)
		{
		case 1:
			for (row=0;row<tmsd.dwHeight;row++)
			{
				UByte* src2p=srcp;
				UByte* dst2p=dstp;
				for (int col=0;col<tmsd.dwWidth;col++,src2p+=dx)
				{
					if (*src2p==0x00)		*dstp++=0xFE;
					else if (*src2p==0xFE)	*dstp++=0x00;
					else					*dstp++=*src2p;
				}
				srcp+=dy;
				dstp=dst2p+offset;
			}
			break;

		case 2:
			if (newtexture.bHasAlpha){
				//Prepare to insert alpha information
				UWord alphaScale=8-curFmt.AlphaBPP;
				UWord alphaShift=curFmt.AlphaShift;
				UWord alphaMask=((1<<curFmt.AlphaBPP)-1)<<alphaShift;

				for (row=0;row<tmsd.dwHeight;row++)
				{
					UByte* alpha2p=alphap;
					UByte* src2p=srcp;
					UByte* dst2p=dstp;
					UWord* lpLUT=(UWord*)lpDMPalLookup[palIndex];
					for (int col=0;col<tmsd.dwWidth;col++,src2p+=dx,alpha2p+=dx)
					{
						UWord tmp=lpLUT[*src2p]&~alphaMask;
						UWord alp=((*alpha2p)>>alphaScale)<<alphaShift;
						*(UWord*)dstp=(tmp+alp);
						dstp+=2;
					}
					srcp+=dy;
					alphap+=dy;
					dstp=dst2p+offset;
				}
			}
			else
			{
				UWord* lpLUT=(UWord*)((newtexture.bIsMasked)?lpDMPalLookup[palIndex]:lpDDPalLookup[palIndex]);
				for (row=0;row<tmsd.dwHeight;row++)
				{
					UByte* src2p=srcp;
					UByte* dst2p=dstp;
					for (int col=0;col<tmsd.dwWidth;col++,src2p+=dx)
					{
						*(UWord*)dstp=lpLUT[*src2p];
						dstp+=2;
					}
					srcp+=dy;
					dstp=dst2p+offset;
				}
			}
			break;
		}
		lpDDTSurf->Unlock(tmsd.lpSurface);

		DDSCAPS scaps;
		scaps.dwCaps=DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE|DDSCAPS_MIPMAP;

		lpDDTSurf->GetAttachedSurface(&scaps,&lpDDTSurf);

		if (lpDDTSurf==NULL)	break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTextureScale
//Author		Paul.   
//Date			Tue 21 Apr 1998
//------------------------------------------------------------------------------
int direct_3d::SetTextureScale(VIDRAMTEXTURE& vrt)
{
	int nTScale=1;
	//Now takes account of textureQuality...
	//textures with dimensions greater than 256x256 are always reduced by
	//at least 50%

	//if textureQuality==4 use textures at full resolution
	//if textureQuality==3 halve all textures except piloted a/c textures
	//if textureQuality==2 halve all textures inc piloted a/c textures
	//if textureQuality==1 halve piloted a/c textures & quarter the rest
	//if textureQuality==0 quarter all textures inc piloted a/c textures

	bool tooBig=(vrt.dwWidth>256||vrt.dwHeight>256)?true:false;

	SWord tq=textureQuality;

	switch(tq){
	case 4:
	if (tooBig){
		nTScale=2;
		vrt.dwWidth>>=1; vrt.dwHeight>>=1;
	}
	break;
	case 3:
	if (tooBig || !vrt.bPlayerTexture){
		nTScale=2;
		vrt.dwWidth>>=1; vrt.dwHeight>>=1;
	}
	break;
	case 2:
	nTScale=2;
	vrt.dwWidth>>=1; vrt.dwHeight>>=1;
	break;
	case 1:
	if (vrt.bPlayerTexture){
		nTScale=2;
		vrt.dwWidth>>=1; vrt.dwHeight>>=1;
	}
	else{
		nTScale=4;
		vrt.dwWidth>>=2; vrt.dwHeight>>=2;
	}
	break;
	case 0:
	nTScale=4;
	vrt.dwWidth>>=2; vrt.dwHeight>>=2;
	break;
	}
	return nTScale;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemakeTexture
//Author		Paul.   
//------------------------------------------------------------------------------
void direct_3d::RemakeTexture(DirectDP lpDirectD,ImageMapDescPtr pMap,LPVIDRAMTEXTURE pVrt,int nTScale)
{
	const DWORD dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;
	ULong palIndex=ULong(pMap->paletteindex);

	bool pixelFormat;
	D3DAppTextureFormat* pCurFmt;
	if (pVrt->bHasAlpha)
	{
		pCurFmt=&transpTexture;
		pixelFormat=true;
	}
	else if (pVrt->bIsMasked)
	{
		pCurFmt=&maskedTexture;
		pixelFormat=(!maskedTexture.bPalettized)?true:false;
	}
	else
	{
		pCurFmt=&opaqueTexture;
		pixelFormat=false;
	}

	D3DAppTextureFormat& curFmt=*pCurFmt;

	bool bPal=curFmt.bPalettized;

	DDSURFACEDESC tmsd=curFmt.ddsd;
	HRESULT dderrval;

	tmsd.dwWidth=pVrt->dwWidth;
	tmsd.dwHeight=pVrt->dwHeight;
	tmsd.dwFlags=dwFlags;
	tmsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_SYSTEMMEMORY;

	if (pVrt->mipMapLevels!=0)
	{
		tmsd.dwFlags|=DDSD_MIPMAPCOUNT;
		tmsd.ddsCaps.dwCaps|=DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
		tmsd.dwMipMapCount=pVrt->mipMapLevels;
	}

	LPDIRECTDRAWSURFACE lpDD1TSurf;

	dderrval=lpDirectD->lpDD2->CreateSurface(&tmsd,&lpDD1TSurf,NULL);
	DIRECTDRAWERROR(dderrval)

	LPDIRECTDRAWSURFACE2 lpDD2TSurf;
	dderrval=lpDD1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&lpDD2TSurf);
	DIRECTDRAWERROR(dderrval)

	if (bPal) dderrval=lpDD2TSurf->SetPalette(lpDDPalette[palIndex]);
	DIRECTDRAWERROR(dderrval)

	LPDIRECT3DTEXTURE lpD3DText;

	dderrval=
	lpDD2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&lpD3DText);
	DIRECTDRAWERROR(dderrval)

	// Copy the texture map data onto the
	// new surface

	if (pVrt->mipMapLevels==0)	PrepTexture(lpDD2TSurf,tmsd,*pVrt,nTScale);
	else						PrepMipMap(lpDD2TSurf,tmsd,*pVrt);

	//Page lock the system memory surface to allow hardware Blt transfer of
	//data later...

	lpDD2TSurf->PageLock(0);

	dderrval=pVrt->lpd3dTexture->Unload();
	dderrval=pVrt->lpd3dTexture->Load(lpD3DText);

	while (lpDD2TSurf->GetBltStatus(DDGBS_ISBLTDONE)!=DD_OK){};
	lpDD2TSurf->PageUnlock(0);
	RELEASE(lpD3DText,dderrval);
	RELEASE(lpDD2TSurf,dderrval);
	RELEASE(lpDD1TSurf,dderrval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateTexture
//Author		Paul.   
//Date			Thu 6 Feb 1997
//
//Description	Convert a Rowan texture into a DD surface in video RAM
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
direct_3d::LPVIDRAMTEXTURE direct_3d::CreateTexture(	ImageMapDescPtr lpImageMap,
														DirectDP 		lpDirectD,
														bool			fRefresh)
{
	const DWORD dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;

	HRESULT dderrval;

	//Fill in texture map description

	VIDRAMTEXTURE newtexture(lpImageMap);

	ULong palIndex=ULong(lpImageMap->paletteindex);

	bool pixelFormat;
	D3DAppTextureFormat* pCurFmt;
	if (newtexture.bHasAlpha)
	{
		pCurFmt=&transpTexture;
		pixelFormat=true;
	}
	else if (newtexture.bIsMasked)
	{
		pCurFmt=&maskedTexture;
		pixelFormat=(!maskedTexture.bPalettized)?true:false;
	}
	else
	{
		pCurFmt=&opaqueTexture;
		pixelFormat=false;
	}

	D3DAppTextureFormat& curFmt=*pCurFmt;
	newtexture.pixelFormat=pixelFormat;

	//If bPlayerTextures is not set OR if the texture width>256 or the
	//texture height>256 then halve the resolution of the texture

	newtexture.bPlayerTexture=bPlayerTextures;

	int nTScale=SetTextureScale(newtexture);

	//Check to see if this map is already loaded

	LPVIDRAMTEXTURE pVidRAMTexture=TextureLoaded(newtexture);

	if (!fRefresh)
	{
		if (pVidRAMTexture!=NULL){
			pVidRAMTexture->bInUse=USED_BYUNCLIPPED;
			return pVidRAMTexture;
		}
	}
	else if (pVidRAMTexture!=NULL)
	{
		//remake this texture
		RemakeTexture(lpDirectD,lpImageMap,pVidRAMTexture,nTScale);
		pVidRAMTexture->bInUse=USED_BYUNCLIPPED;
		return pVidRAMTexture;
	}

	textureUploads++;

	newtexture.fWidth=Float(nTScale*newtexture.dwWidth)*65536.0;
	newtexture.fHeight=Float(nTScale*newtexture.dwHeight)*65536.0;

	//If we haven't exceeded our own limit on the number of
	//texture maps that we can keep a record of then just try
	//to copy the texture up to the card.
	//If it fails with an out of texture RAM error then discard 
	//textures until it fits

	bool bPal=curFmt.bPalettized;

	//step 1 is now to create a texture in system RAM ready
	//to blit up to the card

	DDSURFACEDESC tmsd=curFmt.ddsd;

	tmsd.dwWidth=newtexture.dwWidth;
	tmsd.dwHeight=newtexture.dwHeight;
	tmsd.dwFlags=dwFlags;
	tmsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_SYSTEMMEMORY;

	if (newtexture.mipMapLevels!=0)
	{
		tmsd.dwFlags|=DDSD_MIPMAPCOUNT;
		tmsd.ddsCaps.dwCaps|=DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
		tmsd.dwMipMapCount=newtexture.mipMapLevels;
	}

	LPDIRECTDRAWSURFACE lpDD1TSurf;

	dderrval=lpDirectD->lpDD2->CreateSurface(&tmsd,&lpDD1TSurf,NULL);
	DIRECTDRAWERROR(dderrval)

	LPDIRECTDRAWSURFACE2 lpDD2TSurf;
	dderrval=lpDD1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&lpDD2TSurf);
	DIRECTDRAWERROR(dderrval)

	if (bPal) dderrval=lpDD2TSurf->SetPalette(lpDDPalette[palIndex]);
	DIRECTDRAWERROR(dderrval)

	LPDIRECT3DTEXTURE lpD3DText;

	dderrval=
	lpDD2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&lpD3DText);
	DIRECTDRAWERROR(dderrval)

	// Copy the texture map data onto the
	// new surface
	if (newtexture.mipMapLevels==0)
		PrepTexture(lpDD2TSurf,tmsd,newtexture,nTScale);
	else
		PrepMipMap(lpDD2TSurf,tmsd,newtexture);

	//Page lock the system memory surface to allow hardware Blt transfer of
	//data later...

	lpDD2TSurf->PageLock(0);

	if (NumVidTextures<D3DAPP_MAXVIDTEXTURES)
	{
		tmsd.dwFlags=dwFlags;
		tmsd.ddsCaps.dwCaps=DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY|DDSCAPS_ALLOCONLOAD;

		if (newtexture.mipMapLevels!=0)
		{
			tmsd.dwFlags|=DDSD_MIPMAPCOUNT;
			tmsd.ddsCaps.dwCaps|=DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
			tmsd.dwMipMapCount=newtexture.mipMapLevels;
		}

		dderrval=
		lpDirectD->lpDD2->CreateSurface(&tmsd,&newtexture.lpdds1TSurf,NULL);

		//Catch first lot of upload failures here
		if (dderrval==DD_OK)
		{
			dderrval=
			newtexture.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&newtexture.lpdds2TSurf);

			if (bPal) dderrval=newtexture.lpdds2TSurf->SetPalette(lpDDPalette[palIndex]);
			DIRECTDRAWERROR(dderrval)

			dderrval=
			newtexture.lpdds2TSurf->QueryInterface(	IID_IDirect3DTexture,
									(LPVOID *)&newtexture.lpd3dTexture);
			DIRECTDRAWERROR(dderrval)

			//Upload data to video RAM

			dderrval=newtexture.lpd3dTexture->Load(lpD3DText);

			//Catch other upload failures here!
			if (dderrval==D3D_OK)
			{
				while (lpDD2TSurf->GetBltStatus(DDGBS_ISBLTDONE)!=DD_OK){};
				lpDD2TSurf->PageUnlock(0);
				RELEASE(lpD3DText,dderrval);
				RELEASE(lpDD2TSurf,dderrval);
				RELEASE(lpDD1TSurf,dderrval);
				VIDRAMTEXTURE& vrt=vidramtextures[NumVidTextures++];
				vrt=newtexture;
				dderrval=vrt.lpd3dTexture->GetHandle(lpD3DDevice,&vrt.d3dhTexture);
				DIRECT3DERROR(dderrval)
				MakeNewest(&vrt);
				SetColorKey(BLACK,&vrt);
				vrt.bInUse=USED_BYUNCLIPPED;
				return &vrt;
			}
			RELEASE(newtexture.lpd3dTexture,dderrval);
			RELEASE(newtexture.lpdds2TSurf,dderrval);
			RELEASE(newtexture.lpdds1TSurf,dderrval);
		}
	}
	//Some texture RAM needs to be freed to get this one onto
	//the card...
	//If we reach this point then some textures need to be discarded before
	//the new one can be uploaded...
	//Keep discarding textures until the new one uploads successfully...
 	pVidRAMTexture=&vidramtextures[NumVidTextures-1];
 	while (NumVidTextures!=0)
 	{
 		VIDRAMTEXTURE& vrt=pVidRAMTexture[0];
 		if (vrt.bInUse!=0)
 		{
 			lpDD2TSurf->PageUnlock(0);
 			RELEASE(lpD3DText,dderrval);
 			RELEASE(lpDD2TSurf,dderrval);
 			RELEASE(lpDD1TSurf,dderrval);
 			return (LPVIDRAMTEXTURE)NULL;
 		}
 		else
 		{
 			//Release a texture...
 			NumVidTextures--;
 			dderrval=vrt.lpd3dTexture->Unload();
 			DIRECT3DERROR(dderrval);
 			RELEASE(vrt.lpd3dTexture,dderrval);
 			RELEASE(vrt.lpdds2TSurf,dderrval);
 			RELEASE(vrt.lpdds1TSurf,dderrval);
 			UnlinkTexture(&vrt);
 
 			//Try to upload the new texture...
 			tmsd.dwFlags=dwFlags;
 			tmsd.ddsCaps.dwCaps=DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY|DDSCAPS_ALLOCONLOAD;
 
			if (newtexture.mipMapLevels!=0)
			{
				tmsd.dwFlags|=DDSD_MIPMAPCOUNT;
				tmsd.ddsCaps.dwCaps|=DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
				tmsd.dwMipMapCount=newtexture.mipMapLevels;
			}

 			dderrval=
 			lpDirectD->lpDD2->CreateSurface(&tmsd,&newtexture.lpdds1TSurf,NULL);
 
 			if (dderrval==DD_OK)
 			{
 				dderrval=
 				newtexture.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&newtexture.lpdds2TSurf);
 
 				if (bPal) dderrval=newtexture.lpdds2TSurf->SetPalette(lpDDPalette[palIndex]);
 				DIRECTDRAWERROR(dderrval)
 
 				dderrval=newtexture.lpdds2TSurf->QueryInterface(	IID_IDirect3DTexture,
 												(LPVOID *)&newtexture.lpd3dTexture);
 				DIRECTDRAWERROR(dderrval)
 
 				dderrval=newtexture.lpd3dTexture->Load(lpD3DText);
 				if (dderrval==D3D_OK)
 				{
 					while (lpDD2TSurf->GetBltStatus(DDGBS_ISBLTDONE)!=DD_OK){};
 					lpDD2TSurf->PageUnlock(0);
 					RELEASE(lpD3DText,dderrval);
 					RELEASE(lpDD2TSurf,dderrval);
 					RELEASE(lpDD1TSurf,dderrval);
 					VIDRAMTEXTURE& vrt=vidramtextures[NumVidTextures++];
 					vrt=newtexture;
 					dderrval=vrt.lpd3dTexture->GetHandle(lpD3DDevice,&vrt.d3dhTexture);
 					DIRECT3DERROR(dderrval)
 					MakeNewest(&vrt);
 					SetColorKey(BLACK,&vrt);
 					vrt.bInUse=USED_BYUNCLIPPED;
 					return &vrt;
 				}
 				RELEASE(newtexture.lpd3dTexture,dderrval);
 				RELEASE(newtexture.lpdds2TSurf,dderrval);
 				RELEASE(newtexture.lpdds1TSurf,dderrval);
 			}
 		}
 		pVidRAMTexture--;
 	}
	lpDD2TSurf->PageUnlock(0);
	RELEASE(lpD3DText,dderrval);
	RELEASE(lpDD2TSurf,dderrval);
	RELEASE(lpDD1TSurf,dderrval);
	//If we get here then we probably need to execute the current scene
	//before the new texture can be uploaded...
	return (LPVIDRAMTEXTURE)NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAvailableTextureRAM
//Author		Paul.   
//Date			Fri 14 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DWORD direct_3d::GetAvailableTextureRAM(LPDIRECTDRAW2 llpDD2)
{
	HRESULT	dderrval;
	DDSCAPS	ddsCaps;
	DWORD	dwTotal;
	DWORD	dwFree;

	ddsCaps.dwCaps = DDSCAPS_LOCALVIDMEM|DDSCAPS_VIDEOMEMORY;

	dderrval =
	llpDD2->GetAvailableVidMem(&ddsCaps, &dwTotal, &dwFree);

	DIRECTDRAWERROR(dderrval)

	ddsCaps.dwCaps = DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE;

	dderrval =
	llpDD2->GetAvailableVidMem(&ddsCaps, &dwTotal, &dwFree);

	DIRECTDRAWERROR(dderrval)

	return (dwFree);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VerifyDriver
//Author		Paul.   
//Date			Fri 31 Jan 1997
//
//Description	Verifies the selected driver and mode combination.  
//				If the driver is not compatible one will be selected which is
//				compatible with the specified mode. If none are compatible a
//				value of FALSE will be returned.
//Inputs		
//
//Returns		TRUE if requested driver is compatible with the current 
//				display mode and FALSE if it is not.
//
//------------------------------------------------------------------------------
BOOL direct_3d::VerifyDriver(int driverno)
{
	if (!Driver[driverno].bIsHardware)
		return (FALSE);

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDevice
//Author		Paul.   
//Date			Fri 31 Jan 1997
//
//Description	Create the D3D devive and enumerate texture formats
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOOL direct_3d::CreateDevice(int driverno,DirectDP lpdirectd)
{
	HRESULT	dderrval;
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='a';

	RELEASE(lpD3DDevice,dderrval);

	RECT	rect;
	if (!lpdirectd->lpDirectDD->isFullScreen())
		::GetWindowRect(lpdirectd->hWnd,&rect);
	else{
	 	rect.top=rect.left=0;
		rect.bottom=lpdirectd->DDModes[lpdirectd->DDCurrMode].height;
		rect.right=lpdirectd->DDModes[lpdirectd->DDCurrMode].width;
	}
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='b';

	int	window_width = rect.right - rect.left;
	int	window_height = rect.bottom - rect.top;

	//Make me a Z-buffer

	DDSURFACEDESC	ddsd;

	ZeroMem (&ddsd,sizeof(DDSURFACEDESC));
	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddsd.dwFlags= 	DDSD_WIDTH |
					DDSD_HEIGHT |
					DDSD_CAPS |
					DDSD_ZBUFFERBITDEPTH;

	if (lpdirectd->lpDirectDD->DriverDoesHardware3D())
    	ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
	else
    	ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_SYSTEMMEMORY;

	ddsd.dwWidth = window_width;	//lpdirectd->DDModes[lpdirectd->DDCurrMode].width;
    ddsd.dwHeight = window_height;	//lpdirectd->DDModes[lpdirectd->DDCurrMode].height;

	DWORD	devDepth;

	devDepth = Driver[driverno].Desc.dwDeviceZBufferBitDepth;

    if (devDepth & DDBD_32)
        ddsd.dwZBufferBitDepth = 32;
    else if (devDepth & DDBD_24)
        ddsd.dwZBufferBitDepth = 24;
    else if (devDepth & DDBD_16)
        ddsd.dwZBufferBitDepth = 16;
    else if (devDepth & DDBD_8)
        ddsd.dwZBufferBitDepth = 8;
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='c';

//DEADCODE JIM 20/07/99 //DEADCODE JIM 20/07/99 	if (this==NULL)				UByteP(0xB0000)[12]='A';
//DEADCODE JIM 20/07/99 	if (lpdirectd==NULL)		UByteP(0xB0000)[12]='B';
//DEADCODE JIM 20/07/99 	if (lpdirectd->lpDD2==NULL)	UByteP(0xB0000)[12]='C';
	dderrval =	lpdirectd->lpDD2->CreateSurface(&ddsd,&lpZBuffer,NULL);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='d';
	DIRECTDRAWERROR(dderrval)
//DEADCODE JIM 20/07/99 	if (dderrval)
//DEADCODE JIM 20/07/99 		UByteP(0xB0000)[12]='@'+ dderrval;
//DEADCODE JIM 20/07/99 	DDErrorCodes(__HERE__,0,dderrval);

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='x';
	{//PD 21Oct97
	DDSURFACEDESC 		tmsd;
	ZeroMem (&tmsd,sizeof(DDSURFACEDESC));
	tmsd.dwSize=sizeof(DDSURFACEDESC);

	//Test to see if it's possible to get a lock on the
	//ZBuffer surface ( If it fails then this is probably
	// a powervr card)
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='y';
	dderrval =
	lpZBuffer->Lock(NULL,&tmsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='z';
	if (dderrval==DD_OK)
	{
		lpZBuffer->Unlock(tmsd.lpSurface);
		bCantLockZBuffer=FALSE;
	}
	else bCantLockZBuffer=TRUE;

	}//PD 21Oct97

	//attatch the z-buffer to the back buffer
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='e';

	dderrval =
	lpdirectd->lpDDSBack->AddAttachedSurface(lpZBuffer);

	DIRECTDRAWERROR(dderrval)

	dderrval =
	lpdirectd->lpDDSBack->QueryInterface(Driver[driverno].Guid,
										(LPVOID*)&lpD3DDevice);

//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='f';

	DIRECTDRAWERROR(dderrval);

	NumTextureFormats=0;

	if (!EnumTextureFormats())
	{
		RELEASE(lpD3DDevice,dderrval);
		return (FALSE);
	}
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='g';

	AmbientALPHA = 0xFF;

	TextureRAMFree = AvailableTextureRAM(lpdirectd);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[10]='h';

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnumTextureFormats
//Author		Paul.   
//Date			Fri 31 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOOL direct_3d::EnumTextureFormats()
{
	HRESULT dderrval;
	NumTextureFormats=0;
	dderrval=lpD3DDevice->EnumTextureFormats(enumTextureFormat,(LPVOID)this);
	DIRECTDRAWERROR(dderrval);

	//Select two types of texture format;
	//(1) Format for non-transparent textures	(prefered 8bpp palettized)
	//(2) Format for transparent textures		(prefered 16bpp RGBA)
	bool foundOpaque=false;
	bool foundTransp=false;
	int i;
	for (i=0;i<NumTextureFormats&&(foundOpaque==false||foundTransp==false);i++){
		D3DAppTextureFormat& curFmt=TextureFormat[i];

		if (foundOpaque==false &&
			curFmt.bPalettized==true && curFmt.IndexBPP==8){
			//Found an 8-bit palettized texture format
			opaqueTexture=curFmt;
			foundOpaque=true;
		}
		else if (foundTransp==false &&
				curFmt.ddsd.ddpfPixelFormat.dwRGBBitCount==0x10 &&
				curFmt.ddsd.ddpfPixelFormat.dwFlags&DDPF_ALPHAPIXELS &&
				curFmt.AlphaBPP==4){ 
			transpTexture=curFmt;
			foundTransp=true;
		}
	}
	for (i=0;foundTransp==false&&i<NumTextureFormats;i++){
		D3DAppTextureFormat& curFmt=TextureFormat[i];
		if (curFmt.ddsd.ddpfPixelFormat.dwRGBBitCount==0x10 &&
			curFmt.ddsd.ddpfPixelFormat.dwFlags&DDPF_ALPHAPIXELS)
		{ 
			transpTexture=curFmt;
			foundTransp=true;
		}
	}
	//If we failed to find an 8bpp palettized format then
	//rescan for a 16bpp RGB format (Note: that's RGB not RGBA!)

	if (gameSettings.m_bUse16==TRUE) foundOpaque=false;

	for (i=0;foundOpaque==false&&i<NumTextureFormats;i++){
		D3DAppTextureFormat& curFmt=TextureFormat[i];

		if (curFmt.ddsd.ddpfPixelFormat.dwRGBBitCount==0x10 &&
			!(curFmt.ddsd.ddpfPixelFormat.dwFlags&DDPF_ALPHAPIXELS)){
			opaqueTexture=curFmt;
			foundOpaque=true;
		}
	}
	//If we failed to find an 8bpp palettized format then try to use 
	//the RGBA format selected for transpTexture
	if (foundOpaque==false)
		if (foundTransp==true){
			opaqueTexture=transpTexture;
			foundOpaque=true;
		}
		else return FALSE;

	if (foundTransp==false)	transpTexture=opaqueTexture;

	maskedTexture=transpTexture;

	return (TRUE);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		enumTextureFormat
//Author		Paul.   
//Date			Fri 31 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
HRESULT CALLBACK
direct_3d::enumTextureFormat(LPDDSURFACEDESC lpDDSD, LPVOID lpContext)
{
	Direct3DP	direct3dp;

	direct3dp=(Direct3DP)lpContext;

	ULong	m;

    int 	r, g, b, a;

    // Record the DDSURFACEDESC of this texture format

    ZeroMem(&direct3dp->TextureFormat[direct3dp->NumTextureFormats],
           sizeof(D3DAppTextureFormat));

    memcpy(&direct3dp->TextureFormat[direct3dp->NumTextureFormats].ddsd, lpDDSD,
           sizeof(DDSURFACEDESC));
 
	// Is this format palettized?  How many bits?  Otherwise, how many RGB
    // bits?

    if (lpDDSD->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8)
	{
        direct3dp->TextureFormat[direct3dp->NumTextureFormats].bPalettized = true;
        direct3dp->TextureFormat[direct3dp->NumTextureFormats].IndexBPP = 8;
    }
	else if (lpDDSD->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED4)
			return DDENUMRET_OK;
	else if (lpDDSD->ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS)
	{
		int	tIndex;

		tIndex = direct3dp->NumTextureFormats;

   		direct3dp->TextureFormat[tIndex].bPalettized = false;
   		direct3dp->TextureFormat[tIndex].IndexBPP = 0;

   		for (	r = 0, m = lpDDSD->ddpfPixelFormat.dwRBitMask;
				!(m & 1);
				r++, m >>= 1);

		direct3dp->TextureFormat[tIndex].RedShift = r;

   		for (	r = 0;
				m & 1;
				r++, m >>= 1);

   		direct3dp->TextureFormat[tIndex].RedBPP = r;

   		for (	g = 0, m = lpDDSD->ddpfPixelFormat.dwGBitMask;
				!(m & 1);
				g++, m >>= 1);

		direct3dp->TextureFormat[tIndex].GreenShift = g;

   		for (	g = 0;
				m & 1;
				g++, m >>= 1);

   		direct3dp->TextureFormat[tIndex].GreenBPP = g;

   		for (	b = 0, m = lpDDSD->ddpfPixelFormat.dwBBitMask;
				!(m & 1);
                b++, m >>= 1);

		direct3dp->TextureFormat[tIndex].BlueShift = b;

   		for (	b = 0;
				m & 1;
				b++, m >>= 1);

   		direct3dp->TextureFormat[tIndex].BlueBPP = b;

		for (	a = 0, m = lpDDSD->ddpfPixelFormat.dwRGBAlphaBitMask;
				!(m & 1);
				a++, m >>= 1);

		direct3dp->TextureFormat[tIndex].AlphaShift = a;

		for (	a = 0;
				m & 1;
				a++, m >>= 1);

		direct3dp->TextureFormat[tIndex].AlphaBPP = a;
	}
	else if (lpDDSD->ddpfPixelFormat.dwRGBBitCount==0x10)
	{
		int	tIndex;

		tIndex = direct3dp->NumTextureFormats;

   		direct3dp->TextureFormat[tIndex].bPalettized = false;
   		direct3dp->TextureFormat[tIndex].IndexBPP = 0;

		for (	r = 0, m = lpDDSD->ddpfPixelFormat.dwRBitMask;
				!(m & 1);
				r++, m >>= 1);

		direct3dp->TextureFormat[tIndex].RedShift = r;

		for (	r = 0;
				m & 1;
				r++, m >>= 1);

   		direct3dp->TextureFormat[tIndex].RedBPP = r;

   		for (	g = 0, m = lpDDSD->ddpfPixelFormat.dwGBitMask;
				!(m & 1);
				g++, m >>= 1);

		direct3dp->TextureFormat[tIndex].GreenShift = g;

		for (	g = 0;
				m & 1;
				g++, m >>= 1);

		direct3dp->TextureFormat[tIndex].GreenBPP = g;

		for (	b = 0, m = lpDDSD->ddpfPixelFormat.dwBBitMask;
				!(m & 1);
                b++, m >>= 1);

		direct3dp->TextureFormat[tIndex].BlueShift = b;

		for (	b = 0;
				m & 1;
				b++, m >>= 1);

   		direct3dp->TextureFormat[tIndex].BlueBPP = b;

		direct3dp->TextureFormat[tIndex].AlphaShift = 0;
		direct3dp->TextureFormat[tIndex].AlphaBPP = 0;
	}
	else return DDENUMRET_OK;

    direct3dp->NumTextureFormats++;

    return (DDENUMRET_OK);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitPalette
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
void direct_3d::InitPaletteData()
{
	for (int counter=0;counter<256;counter++)
	{
		palette[counter].hTexture=NULL;
	}

	backgroundMaterial.lpMaterial = NULL;
	backgroundMaterial.hMaterial = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakePALLookup
//Author		Paul.   
//Date			Mon 23 Feb 1998
//
//------------------------------------------------------------------------------
void direct_3d::MakePALLookup(	D3DAppTextureFormat& curFmt,
								UByte*& lpDDPalLookup,R3DPalP rpalptr)
{
	int bytesPerEntry=curFmt.ddsd.ddpfPixelFormat.dwRGBBitCount>>3;
	if (lpDDPalLookup!=NULL) delete [] lpDDPalLookup;
	lpDDPalLookup=new UByte[256*bytesPerEntry];
	UByte* lpPalLookup=lpDDPalLookup;

	for (int count=0;count<256;count++){
		int	shiftVal, maskVal;
		//Convert 256 entry 24-bit palette into whatever is required
		//Blue component...
		shiftVal = 8 - curFmt.BlueBPP;
		maskVal = (1<<curFmt.BlueBPP)-1;
		int	blueVal = rpalptr->b;
		blueVal >>= shiftVal; blueVal &= maskVal;
		//Red component...
		shiftVal = 8 - curFmt.RedBPP;
		maskVal = (1<<curFmt.RedBPP)-1;
		int	redVal = rpalptr->r;
		redVal >>= shiftVal; redVal &= maskVal;
		//Green component...
		shiftVal = 8 - curFmt.GreenBPP;
		maskVal = (1<<curFmt.GreenBPP)-1;
		int	greenVal = rpalptr->g;
		greenVal >>= shiftVal; greenVal &= maskVal;
		//Alpha component...
		shiftVal = 8 - curFmt.AlphaBPP;
		maskVal = (1<<curFmt.AlphaBPP)-1;
		int	alphaVal=(count!=ARTWORKMASK)?0xFF:0x00;
		alphaVal >>= shiftVal; alphaVal &= maskVal;
		ULong	cval;
		cval =  redVal<<curFmt.RedShift;
		cval += greenVal<<curFmt.GreenShift;
		cval += blueVal<<curFmt.BlueShift;
		cval += alphaVal<<curFmt.AlphaShift;
		if (bytesPerEntry==2){
			*(UWord*)lpPalLookup = (UWord)cval;
			lpPalLookup+=2;
		}
		rpalptr++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPalette
//Author		Paul.   
//Date			Fri 7 Feb 1997
//
//Description	expects 'newpalptr' to point to 'MAX_PALS' palettes
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::SetPalette(struct _DirectDraw* lpDirectD,UByte* newpalptr)
{
	double gamma_value=gamma_values[Save_Data.gammacorrection];

	ULong* pp=(ULong*)lastPals;
	ULong* pn=(ULong*)newpalptr;
	bool palChanged=false;
	for (int bum=0;bum<64*3;bum++){
		if (*pp!=*pn){
			palChanged=true;
			*pp=*pn;
		}
		pp++;pn++;
	}
	if (palChanged==false) return;
	//Invalidate current fog colour value by setting it to ARTWORKMASK
	CurrFogColour=RGBA_MAKE(0xFF,0x00,0xFF,0xFF);	//ARTWORKMASK;
	//There's always at least 1 palette and it needs to be treated
	//as a special case anyway.
	//Make a local copy of the new palette first
	UByte localPal[3*256];
	ULong* pSrc=(ULong*)newpalptr;
	ULong* pDst=(ULong*)localPal;
	for (int x=0;x<3*64;*pDst++=*pSrc++,x++) {}
	//knobble some entries
	UByte* pPal=localPal+3;
	localPal[3*BLACK]=localPal[3*BLACK+1]=localPal[3*BLACK+2]=0x00;
	localPal[3*255]=localPal[3*255+1]=localPal[3*255+2]=0x08;
	localPal[3*ARTWORKMASK]=localPal[3*ARTWORKMASK+1]=localPal[3*ARTWORKMASK+2]=0x08;
	localPal[3*FONTMASK]=localPal[3*FONTMASK+1]=localPal[3*FONTMASK+2]=0x08;
	for (x=BLACK+1;x<FONTMASK;x++,pPal+=3){
		if (pPal[0]<0x08 && pPal[1]<0x08 && pPal[2]<0x08){
			pPal[0]=pPal[1]=pPal[2]=0x08;
		}
	}

	for (x=0;x<256;x++) GreyPalette(localPal+(x*3));

	R3DPalP pRPal=(R3DPalP)localPal;
	D3DVALUE cvRed=Float(lpDirectD->hcRed)/255.0,
			cvGreen=Float(lpDirectD->hcGreen)/255.0,
			cvBlue=Float(lpDirectD->hcBlue)/255.0;

	for (x=0;x<256;x++,pRPal++){
	 	GammaCorrectRGB(pRPal,gamma_value);						//PD 10Dec98
		PALETTEENTRY& pe=peSrcPalette[x];
		D3DMaterial& me=palette[x];
		R3DPal& rp=*pRPal;
		pe.peRed=rp.r;
		pe.peGreen=rp.g;
		pe.peBlue=rp.b;
		pe.peFlags=0;
		me.dcColorVal=RGBA_MAKE(rp.r,rp.g,rp.b,AmbientALPHA);
		me.dcColorVal16=((rp.r&0xF8)<<8)|((rp.g&0xF8)<<3)|((rp.b&0xF8)>>3);
	}
	//Set up the background material for the horizon
	HRESULT dderrval;
	RELEASE(backgroundMaterial.lpMaterial,dderrval);
	dderrval=lpD3D->CreateMaterial(&backgroundMaterial.lpMaterial,NULL);
	DIRECT3DERROR(dderrval);
	D3DMATERIAL& md=backgroundMaterial.MaterialDesc;
	ZeroMem(&md,sizeof(D3DMATERIAL));
	md.dwSize=sizeof(D3DMATERIAL);
	md.diffuse.r=cvRed;
	md.diffuse.g=cvGreen;
	md.diffuse.b=cvBlue;
	md.diffuse.a=1.0;
	md.ambient.r=cvRed;
	md.ambient.g=cvGreen;
	md.ambient.b=cvBlue;
	md.power=(Float)20.0;
	md.dwRampSize=16;
	md.hTexture=NULL;
	backgroundMaterial.lpMaterial->SetMaterial(&backgroundMaterial.MaterialDesc);
	backgroundMaterial.lpMaterial->GetHandle(lpD3DDevice,&backgroundMaterial.hMaterial);
	//Set up texture palette 0 
	if (lpDDPalette[0]!=NULL)
		dderrval=lpDDPalette[0]->SetEntries(NULL,0,256,peSrcPalette);
	else
		dderrval=lpDirectD->lpDD2->CreatePalette(DDPCAPS_8BIT|DDPCAPS_ALLOW256,peSrcPalette,&lpDDPalette[0],NULL);
	DIRECTDRAWERROR(dderrval);
	//palette lookup table used for >256 colour texture modes
	MakePALLookup(opaqueTexture,lpDDPalLookup[0],(R3DPalP)localPal);
	MakePALLookup(transpTexture,lpDMPalLookup[0],(R3DPalP)localPal);
	//Now, set up palettes 1..MAX_PALS
	for (x=1;x<MAX_PALS;x++){
		//Make a local copy of the new palette first
		newpalptr+=3*256;
		pSrc=(ULong*)newpalptr;
		pDst=(ULong*)localPal;
		for (int y=0;y<3*64;*pDst++=*pSrc++,y++) {}
		//knobble some entries
		pPal=localPal;	//+3;
		for (y=0;y<256;y++,pPal+=3){
			if (pPal[0]<0x08 && pPal[1]<0x08 && pPal[2]<0x08){
				pPal[0]=pPal[1]=pPal[2]=0x08;
			}
		}
		localPal[3*BLACK]=localPal[3*BLACK+1]=localPal[3*BLACK+2]=0x00;
		localPal[3*ARTWORKMASK]=localPal[3*ARTWORKMASK+1]=localPal[3*ARTWORKMASK+2]=0x08;
		localPal[3*FONTMASK]=localPal[3*FONTMASK+1]=localPal[3*FONTMASK+2]=0x08;

		for (y=0;y<256;y++) GreyPalette(localPal+(y*3));

		PALETTEENTRY peNextPal[256];
		pRPal=(R3DPalP)localPal;
		for (y=0;y<256;y++,pRPal++){
	 		GammaCorrectRGB(pRPal,gamma_value);					//PD 10Dec98
			PALETTEENTRY& pe=peNextPal[y];
			R3DPal& rp=*pRPal;
			pe.peRed=rp.r;
			pe.peGreen=rp.g;
			pe.peBlue=rp.b;
			pe.peFlags=0;
		}
		//Set up texture palette 'x'
		if (lpDDPalette[x]!=NULL)
			dderrval=lpDDPalette[x]->SetEntries(NULL,0,256,peNextPal);
		else
			dderrval=lpDirectD->lpDD2->CreatePalette(DDPCAPS_8BIT|DDPCAPS_ALLOW256,peNextPal,&lpDDPalette[x],NULL);
		DIRECTDRAWERROR(dderrval);
		MakePALLookup(opaqueTexture,lpDDPalLookup[x],(R3DPalP)localPal);
		MakePALLookup(transpTexture,lpDMPalLookup[x],(R3DPalP)localPal);
	}
	//Force a full re-load of all textures (for non-palettized version)

	if (!opaqueTexture.bPalettized ||
		!transpTexture.bPalettized ||
		!maskedTexture.bPalettized)
		ReleaseTextures();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TranslateColour16
//Author		Paul.   
//Date			Thu 22 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord direct_3d::TranslateColour16(Colour c)
{
	UWord* lpLUT;

	if (lpDDPalLookup==NULL)	return (0);

	lpLUT = (UWord*)lpDDPalLookup;

	return (lpLUT[c]);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseTextures
//Author		Paul.   
//Date			Thu 15 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::ReleaseTextures()
{
	HRESULT dderrval;
	//Initialise video ramtexture storeage information

	lpOldestTexture =
	lpNewestTexture = NULL;

	LPVIDRAMTEXTURE	lpVidramtexture = vidramtextures;

	//Discard textures in video+system memory

	for (int j=0;j<NumVidTextures;j++)
	{
		RELEASE(lpVidramtexture->lpd3dTexture,dderrval);
		RELEASE(lpVidramtexture->lpdds2TSurf,dderrval);
		RELEASE(lpVidramtexture->lpdds1TSurf,dderrval);
		lpVidramtexture->lpOlderTexture = NULL;
		lpVidramtexture->lpNewerTexture = NULL;
		lpVidramtexture->bInUse = 0;
		lpVidramtexture++;
	}
	NumVidTextures=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakePaletteMods
//Author		Paul.   
//Date			Thu 1 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::MakePaletteMods(R3DPalP palptr)
{
	int	  cnt;

	for (cnt=0;cnt<256;cnt++)
		if (palptr[cnt].r<0x08 && palptr[cnt].g<0x08 && palptr[cnt].b<0x08)
		{
			palptr[cnt].r = 0x08; palptr[cnt].g = 0x08; palptr[cnt].b = 0x08;
		}

	palptr[ARTWORKMASK].r	= 0x08;
	palptr[ARTWORKMASK].g	= 0x08;
	palptr[ARTWORKMASK].b	= 0x08;
	palptr[FONTMASK].r		= 0x08;
	palptr[FONTMASK].g		= 0x08;
	palptr[FONTMASK].b		= 0x08;
	palptr[BLACK].r			= 0x00;
	palptr[BLACK].g			= 0x00;
	palptr[BLACK].b			= 0x00;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetColorKey
//Author		Paul.   
//Date			Wed 30 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::SetColorKey(DWORD color,LPVIDRAMTEXTURE lpVRT)
{
	DDCOLORKEY ddColorKey;
	ddColorKey.dwColorSpaceLowValue=ddColorKey.dwColorSpaceHighValue=color;
	DWORD dwFlagVal=DDCKEY_SRCBLT;

	if (lpVRT==NULL){//set them all
		for (int x=0;x<NumVidTextures;x++){
			VIDRAMTEXTURE& vrt=vidramtextures[x];
			
			D3DAppTextureFormat* pCTF;
			
			if (vrt.bHasAlpha)		pCTF=&transpTexture;
			else if (vrt.bIsMasked)	pCTF=&maskedTexture;
			else 					pCTF=&opaqueTexture;

			D3DAppTextureFormat& curFmt=*pCTF;

			if (curFmt.bPalettized)
			{
				HRESULT dderrval=vrt.lpdds2TSurf->SetColorKey(dwFlagVal,&ddColorKey);
				DIRECTDRAWERROR(dderrval);
			}
		}
	}
	else
	{
		D3DAppTextureFormat* pCTF;
			
		if (lpVRT->bHasAlpha)		pCTF=&transpTexture;
		else if (lpVRT->bIsMasked)	pCTF=&maskedTexture;
		else 						pCTF=&opaqueTexture;

		D3DAppTextureFormat& curFmt=*pCTF;

		if (curFmt.bPalettized)
		{
			HRESULT dderrval=lpVRT->lpdds2TSurf->SetColorKey(dwFlagVal,&ddColorKey);
			DIRECTDRAWERROR(dderrval);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearViewport
//LastModified:	PD 10Jun97
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
void direct_3d::ClearViewport(struct _DirectDraw* lpDirectD,Bool bFlag)
{
	RECT rect;
	if (!lpDirectD->lpDirectDD->isFullScreen())
		::GetWindowRect(lpDirectD->hWnd,&rect);
	else{
	 	rect.top=rect.left=0;
		rect.bottom=lpDirectD->DDModes[lpDirectD->DDCurrMode].height;
		rect.right=lpDirectD->DDModes[lpDirectD->DDCurrMode].width;
	}
	if (lpD3DViewport!=NULL)
	{
		if (bFlag==FALSE)
		{
			D3DRECT		Rect;
			LPD3DRECT	lpRect=&Rect;

			lpRect->x1	=	rect.left;		//viewdata.originx - viewdata.scalex;
			lpRect->y1	=	rect.top;		//viewdata.originy - viewdata.scaley;
			lpRect->x2	=	rect.right;		//viewdata.originx + viewdata.scalex;
			lpRect->y2	=	rect.bottom;	//viewdata.originy + viewdata.scaley;

			lpD3DViewport->Clear(1,lpRect,D3DCLEAR_ZBUFFER);
		}
		else
		{
			D3DVALUE	cvRed,cvBlue,cvGreen;

//Old_Code PD 18Jan99 			cvRed = ((Float)peSrcPalette[lpDirectD->hColour].peRed)/255.0;
//Old_Code PD 18Jan99 			cvGreen = ((Float)peSrcPalette[lpDirectD->hColour].peGreen)/255.0;
//Old_Code PD 18Jan99 			cvBlue = ((Float)peSrcPalette[lpDirectD->hColour].peBlue)/255.0;

			cvRed = Float(lpDirectD->hcRed)/255.0;
			cvGreen = Float(lpDirectD->hcGreen)/255.0;
			cvBlue = Float(lpDirectD->hcBlue)/255.0;

			if (backgroundMaterial.MaterialDesc.diffuse.r != cvRed ||
				backgroundMaterial.MaterialDesc.diffuse.g != cvGreen ||
				backgroundMaterial.MaterialDesc.diffuse.b != cvBlue)
			{

			backgroundMaterial.MaterialDesc.diffuse.r = cvRed;
			backgroundMaterial.MaterialDesc.diffuse.g = cvGreen;
			backgroundMaterial.MaterialDesc.diffuse.b = cvBlue;

			backgroundMaterial.MaterialDesc.ambient.r = cvRed;
			backgroundMaterial.MaterialDesc.ambient.g = cvGreen;
			backgroundMaterial.MaterialDesc.ambient.b = cvBlue;

			backgroundMaterial.lpMaterial->
				SetMaterial(&backgroundMaterial.MaterialDesc);

			backgroundMaterial.lpMaterial->
				GetHandle(lpD3DDevice,&backgroundMaterial.hMaterial);
			}

			D3DRECT		Rect;
			LPD3DRECT	lpRect=&Rect;

			lpRect->x1	=	rect.left;	//viewdata.clipLft;					//PD 26Sep97
			lpRect->y1	=	rect.top;	//viewdata.clipTop;					//PD 26Sep97
			lpRect->x2	=	rect.right;	//viewdata.clipRgt;					//PD 26Sep97
			lpRect->y2	=	rect.bottom;//viewdata.clipBot;					//PD 26Sep97

			lpD3DViewport->SetBackground(backgroundMaterial.hMaterial);
			lpD3DViewport->Clear(1,lpRect,D3DCLEAR_TARGET);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseDown
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
void direct_3d::CloseDown()
{
	FreeExecuteBuffers();

	HRESULT	dderrval;
	int		j;

	//Initialise video ramtexture storeage information

	ReleaseTextures();

	ReleaseLandTextureBuffers();

	for (j=0;j<MAX_PALS;j++){
		RELEASE(lpDDPalette[j],dderrval);
		if (lpDDPalLookup[j]!=NULL)
			{delete [] lpDDPalLookup[j];lpDDPalLookup[j]=NULL;}
		if (lpDMPalLookup[j]!=NULL)
			{delete [] lpDMPalLookup[j];lpDMPalLookup[j]=NULL;}
	}

	RELEASE(lpDDLandPal,dderrval);
	if (lpDDLandPalLookup)
		delete[]lpDDLandPalLookup,
			lpDDLandPalLookup=NULL;

	if (lpDDTLandPalLookup)
		delete[]lpDDTLandPalLookup,
			lpDDTLandPalLookup=NULL;

	RELEASE(backgroundMaterial.lpMaterial,dderrval);

	ReleaseExecuteBuffer();

	RELEASE(lpD3DLight,dderrval);

	RELEASE(lpD3DViewport,dderrval);

	RELEASE(lpD3DDevice,dderrval);

	if (!fullScreen) RELEASE(lpZBuffer,dderrval);

	lpZBuffer=NULL;

	RELEASE(lpD3D,dderrval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateExecuteBuffer
//Author		Paul.   
//Date			Wed 5 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::CreateExecuteBuffer()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseExecuteBuffer
//Author		Paul.   
//Date			Wed 5 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::ReleaseExecuteBuffer()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateLandTextureBuffers
//Author		Paul.   
//Date			Thu 20 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::CreateLandTextureBuffers(struct _DirectDraw* lpDirectD)
{
 	if (lpDDPalette[0]==NULL){
 		UByte* tmpp = new UByte[MAX_PALS*3*256];
 		ZeroMem(tmpp,MAX_PALS*3*256);
 		SetPalette(lpDirectD,tmpp);
 		delete [] tmpp;
 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrepLandMap
//Author		Paul.   
//Date			Mon 18 May 1998
//------------------------------------------------------------------------------
void direct_3d::PrepLandMap(VIDRAMTEXTURE& vrt,ImageMapDesc* lpImageMap)
{
	HRESULT	dderrval;
	DDSURFACEDESC tmsd=opaqueTexture.ddsd;

	//Copy the texture map data onto the new surface
	dderrval=vrt.lpdds1TSurf->Lock(NULL,&tmsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);

	DIRECTDRAWERROR(dderrval);

	UByte* srcp = (UByte*)(lpImageMap->body);
	UByte* dstp = (UByte*)tmsd.lpSurface;

	int	bytesPerPixel=opaqueTexture.ddsd.ddpfPixelFormat.dwRGBBitCount>>3;
	int textureWidth=vrt.dwWidth;
	int	row;
	switch (bytesPerPixel){
	case 1:
		for (row=0;row<vrt.dwHeight;row++){
			UByte* src2p=srcp;
			for (int col=0;col<vrt.dwWidth;col++,*dstp++=*src2p++){}
			srcp+=textureWidth;
		}
		break;

	case 2:
		UWord* lpLUT=(UWord*)lpDDPalLookup[0];
		for (row=0;row<vrt.dwHeight;row++){
			UByte* src2p=srcp;
			for (int col=0;col<vrt.dwWidth;col++){
				*(UWord*)dstp=lpLUT[*src2p++];
				dstp+=2;
			}
			srcp+=textureWidth;
		}
		break;
	}
	vrt.lpdds1TSurf->Unlock(tmsd.lpSurface);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UploadLandTexture
//Author		Paul.   
//Date			Mon 18 May 1998
//------------------------------------------------------------------------------
void direct_3d::UploadLandTexture(struct _DirectDraw* lpDirectD,ULong hTexture,ImageMapDesc* lpImageMap)
{
	VIDRAMTEXTURE& sysTex=sysramlandmaps[hTexture];
	VIDRAMTEXTURE& vidTex=vidramlandmaps[hTexture];
	//Copy image map data to the system ram texture surface doing any
	//colour conversions required on the way..
	PrepLandMap(sysTex,lpImageMap);
	//Blit the texture up to video RAM
	DDBLTFX	bltfx;
	ZeroMem(&bltfx,sizeof(bltfx));
	bltfx.dwSize=sizeof(bltfx);
	RECT rect;
	rect.top=rect.left=0;
	rect.bottom=rect.right=_landTextureWH;
	HRESULT dderrval=
	vidTex.lpdds2TSurf->Blt(&rect,sysTex.lpdds2TSurf,&rect,DDBLT_WAIT,&bltfx);
	while (vidTex.lpdds2TSurf->GetBltStatus(DDGBS_ISBLTDONE)!=DD_OK) {}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseLandTextureBuffers
//Author		Paul.   
//Date			Mon 18 May 1998
//------------------------------------------------------------------------------
void direct_3d::ReleaseLandTextureBuffers()
{
 	HRESULT dderrval;

//	if (gameSettings.m_bHighLandTexture)
//	{
		for (int i=0;i<NUM_256_TEXTURES;i++)
		{
			VIDRAMTEXTURE& vrt=vidram256maps[i];
			RELEASE(vrt.lpd3dTexture,dderrval);
			RELEASE(vrt.lpdds2TSurf,dderrval);
			RELEASE(vrt.lpdds1TSurf,dderrval);
		}

		for (i=0;i<NUM_128_TEXTURES;i++)
		{
			VIDRAMTEXTURE& vrt=vidram128maps[i];
			RELEASE(vrt.lpd3dTexture,dderrval);
			RELEASE(vrt.lpdds2TSurf,dderrval);
			RELEASE(vrt.lpdds1TSurf,dderrval);
		}

		for (i=0;i<NUM_64_TEXTURES;i++)
		{
			VIDRAMTEXTURE& vrt=vidram64maps[i];
			RELEASE(vrt.lpd3dTexture,dderrval);
			RELEASE(vrt.lpdds2TSurf,dderrval);
			RELEASE(vrt.lpdds1TSurf,dderrval);
		}

		for (i=0;i<NUM_32_TEXTURES;i++)
		{
			VIDRAMTEXTURE& vrt=vidram32maps[i];
			RELEASE(vrt.lpd3dTexture,dderrval);
			RELEASE(vrt.lpdds2TSurf,dderrval);
			RELEASE(vrt.lpdds1TSurf,dderrval);
		}

		for (i=0;i<NUM_16_TEXTURES;i++)
		{
			VIDRAMTEXTURE& vrt=vidram16maps[i];
			RELEASE(vrt.lpd3dTexture,dderrval);
			RELEASE(vrt.lpdds2TSurf,dderrval);
			RELEASE(vrt.lpdds1TSurf,dderrval);
		}

		for (i=0;i<NUM_8_TEXTURES;i++)
		{
			VIDRAMTEXTURE& vrt=vidram8maps[i];
			RELEASE(vrt.lpd3dTexture,dderrval);
			RELEASE(vrt.lpdds2TSurf,dderrval);
			RELEASE(vrt.lpdds1TSurf,dderrval);
		}

		for (i=0;i<NUM_SCALES;i++)
		{
			VIDRAMTEXTURE& vrt=sysramALLmaps[i];
			RELEASE(vrt.lpd3dTexture,dderrval);
			RELEASE(vrt.lpdds2TSurf,dderrval);
			RELEASE(vrt.lpdds1TSurf,dderrval);
		}

//		if (gameSettings.m_bUseMipMapping)
		if (Save_Data.filtering==3)
			FreeExtraLandDetail();

		if (vidram256maps) delete[]vidram256maps,vidram256maps=NULL;
		if (vidram128maps) delete[]vidram128maps,vidram128maps=NULL;
		if (vidram64maps) delete[]vidram64maps,vidram64maps=NULL;
		if (vidram32maps) delete[]vidram32maps,vidram32maps=NULL;
		delete[]landTextureUsage;
		landTextureUsage=NULL;
//	}
//	else
//	{
//		for (int i=0;i<_landscapeTextures;i++){
//			VIDRAMTEXTURE& vrt=vidramlandmaps[i];
//			RELEASE(vrt.lpd3dTexture,dderrval);
//			RELEASE(vrt.lpdds2TSurf,dderrval);
//			RELEASE(vrt.lpdds1TSurf,dderrval);
//			vidramlandptr[i]=NULL;
  //
	//		//remove the page lock on the system memory surface...
	//		VIDRAMTEXTURE& srt=sysramlandmaps[i];
	//		srt.lpdds2TSurf->PageUnlock(0);
	//		RELEASE(srt.lpd3dTexture,dderrval);
	//		RELEASE(srt.lpdds2TSurf,dderrval);
	//		RELEASE(srt.lpdds1TSurf,dderrval);
	//		sysramlandptr[i]=NULL;
	//	}
	//}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenericLineClip
//Author		Paul.   
//Date			Tue 8 Sep 1998
//------------------------------------------------------------------------------
SWord direct_3d::GenericLineClip(R3DTLVERTEX& startVert,R3DTLVERTEX& endVert)
{
	R3DTLVERTEX tempVert;

	//-----------------------------
	// Clip to front clipping plane
	//-----------------------------

	if (startVert.clipFlags&CF3D_BEHINDNEARZ)
	{
		RClipToFront(&endVert,&startVert,&tempVert);
		startVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}
	else if (endVert.clipFlags&CF3D_BEHINDNEARZ)
	{
		RClipToFront(&startVert,&endVert,&tempVert);
		endVert=startVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}

	//-----------------------------
	// Clip to back clipping plane
	//-----------------------------

	if (startVert.clipFlags&CF3D_PASTFARZ)
	{
		RClipToBack(&endVert,&startVert,&tempVert);
		startVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}
	else if (endVert.clipFlags&CF3D_PASTFARZ)
	{
		RClipToBack(&startVert,&endVert,&tempVert);
		endVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}

	//-----------------------------
	// Clip to east clipping plane
	//-----------------------------

	if (startVert.clipFlags&CF3D_OFFRIGHT)
	{
		RClipToEast(&endVert,&startVert,&tempVert);
		startVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}
	else if (endVert.clipFlags&CF3D_OFFRIGHT)
	{
		RClipToEast(&startVert,&endVert,&tempVert);
		endVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}

	//-----------------------------
	// Clip to west clipping plane
	//-----------------------------

	if (startVert.clipFlags&CF3D_OFFLEFT)
	{
		RClipToWest(&endVert,&startVert,&tempVert);
		startVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}
	else if (endVert.clipFlags&CF3D_OFFLEFT)
	{
		RClipToWest(&startVert,&endVert,&tempVert);
		endVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}

	//-----------------------------
	// Clip to top clipping plane
	//-----------------------------

	if (startVert.clipFlags&CF3D_OFFTOP)
	{
		RClipToTop(&endVert,&startVert,&tempVert);
		startVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}
	else if (endVert.clipFlags&CF3D_OFFTOP)
	{
		RClipToTop(&startVert,&endVert,&tempVert);
		endVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}

	//-----------------------------
	// Clip to bottom clipping plane
	//-----------------------------

	if (startVert.clipFlags&CF3D_OFFBOTTOM)
	{
		RClipToBottom(&endVert,&startVert,&tempVert);
		startVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}
	else if (endVert.clipFlags&CF3D_OFFBOTTOM)
	{
		RClipToBottom(&startVert,&endVert,&tempVert);
		endVert=tempVert;
		if ((startVert.clipFlags|endVert.clipFlags)==CF3D_NULL)
			return 0;
	}
	return (-1);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateLandscapePalette
//Author		Paul.   
//Date			Fri 25 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::CreateLandscapePalette(struct _DirectDraw* lpDirectD)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GammaCorrectRGB
//Author		Paul.   
//Date			Tue 6 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void direct_3d::GammaCorrectRGB(R3DPalP rgbCol,Float g_corr)
{
	if (g_corr==1.) return;

	double dtemp; SLong ltemp;
	
	dtemp=double(SLong(rgbCol->r)&0xFF);
	ltemp=(SLong)pow(dtemp,double(g_corr));
	if (ltemp>255) ltemp=255;
	else if (ltemp<0) ltemp=0;
	rgbCol->r=UByte(ltemp);

	dtemp=double(SLong(rgbCol->g)&0xFF);
	ltemp=(SLong)pow(dtemp,double(g_corr));
	if (ltemp>255) ltemp=255;
	else if (ltemp<0) ltemp=0;
	rgbCol->g=UByte(ltemp);

	dtemp=double(SLong(rgbCol->b)&0xFF);
	ltemp=(SLong)pow(dtemp,double(g_corr));
	if (ltemp>255) ltemp=255;
	else if (ltemp<0) ltemp=0;
	rgbCol->b=UByte(ltemp);

/*	Float	H, S, V;

	Float	gR, gB, gG;

	Float	fR, fG, fB;

	Float	maxCol, minCol;

	Bool	bHueUndefined = FALSE;

	//convert RGB -> HSV

	fR = rgbCol->r; fG = rgbCol->g; fB = rgbCol->b;

//	fR /= 255.0; fG /= 255.0; fB /= 255.0;
	fR /= 2.550; fG /= 2.550; fB /= 2.550;

	if (fR>fG)	{maxCol = fR; minCol = fG;}
	else		{maxCol = fG; minCol = fR;}

	if (maxCol<fB)			maxCol = fB;
	else if (minCol>fB)		minCol = fB;

	V = maxCol;

	if (maxCol==minCol)	{S=0.0;bHueUndefined=TRUE;}	//H is undefined
	else
	{
		S = (maxCol-minCol)/maxCol;

		if (minCol==fB)			H = 120.0*(0.0+(fG-minCol)/(fR+fG-2.0*minCol));
		else if (minCol==fR)	H = 120.0*(1.0+(fB-minCol)/(fB+fG-2.0*minCol));
		else					H = 120.0*(2.0+(fR-minCol)/(fR+fB-2.0*minCol));
	}

	// Do something

	V = (Float)pow((double)V,(double)g_corr);
	
	// Convert HSV -> RGB

	if (bHueUndefined)	{fR = fG = fB = V;}
	else
	{
		minCol = V * (1.0 - S);

		if (H<=120.0)
		{
			fB = minCol;

			if (H<=60.0)
			{
				fR = V;
				fG = minCol+H*(V-minCol)/(120.0-H);
			}
			else
			{
				fG = V;
				fR = minCol+(120.0-H)*(V-minCol)/H;
			}
		}
		else if (H<=240.0)
		{
			fR = minCol;

			if (H<=180.0)
			{
				fG = V;
				fB = minCol + (H-120.0)*(V-minCol)/(240.0-H);
			}
			else
			{
				fB = V;
				fG = minCol + (240.0-H)*(V-minCol)/(H-120.0);
			}
		}
		else
		{
			fG = minCol;

			if (H<=300.0)
			{
				fB = V;
				fR = minCol + (H-240.0)*(V-minCol)/(360.0-H);
			}
			else
			{
				fR = V;
				fB = minCol + (360.0-H)*(V-minCol)/(H-240.0);
			}
		}
	}

//	fR *= 255.0; fG *= 255.0; fB *= 255.0;
	fR *= 2.550; fG *= 2.550; fB *= 2.550;

	rgbCol->r = fR; rgbCol->g = fG; rgbCol->b = fB;
*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PointDraw16
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
/*void direct_3d::PointDraw16(	struct _DirectDraw* lpDirectD,
								UWord	color,
								SWord	x,SWord y)
{
	UByteP	logicalscreenptr,
			scradr;

	SLong	BytesPerPixel = 2;

	SLong	BytesPerScanLine;

	UWord	linecol = color;

	while (lpDirectD->lpDDSBack->Lock(	NULL,
										lpDirectD->lpddsd,
										DDLOCK_SURFACEMEMORYPTR|
										DDLOCK_WAIT,
										NULL)!=DD_OK){};

	logicalscreenptr = (UByteP)lpDirectD->lpddsd->lpSurface;

	BytesPerScanLine = lpDirectD->lpddsd->lPitch;

	scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);

	*(UWord*)scradr = linecol;	// PlotPixel(x,y);

	lpDirectD->lpDDSBack->Unlock(lpDirectD->lpddsd->lpSurface);
}*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LineDraw16
//Author		Paul.   
//Date			Wed 7 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*void direct_3d::LineDraw16(	struct _DirectDraw* lpDirectD,
						 	UWord	color,
						 	SWord	x1,		SWord	y1,
							SWord	x2,		SWord	y2)
{
	SLong 	distx,	disty,
			x,		y,
			const1,	const2,
			p;

	UByteP	logicalscreenptr,
			scradr;

	SLong	BytesPerPixel;

	SLong	BytesPerScanLine;

	UWord	linecol = color;

	while (lpDirectD->lpDDSBack->Lock(	NULL,
										lpDirectD->lpddsd,
										DDLOCK_SURFACEMEMORYPTR|
										DDLOCK_WAIT,
										NULL)!=DD_OK){};

	logicalscreenptr = (UByteP)lpDirectD->lpddsd->lpSurface;

	BytesPerPixel = lpDirectD->lpddsd->ddpfPixelFormat.dwRGBBitCount>>3;

	BytesPerScanLine = lpDirectD->lpddsd->lPitch;

	distx = x2 - x1;

	disty = y2 - y1;

	if (distx < 0)	distx = -distx;

	if (disty < 0)	disty = -disty;

	//Vertical case

	if (distx == 0)
	{
		y = (y2>y1)?y1:y2;

		x = x1;

		scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);

		*(UWord*)scradr = linecol;	// PlotPixel(x,y);

		for (;disty--;scradr+=BytesPerScanLine,y++)	*(UWord*)scradr = linecol;	//	PlotPixel(x,y);

		lpDirectD->lpDDSBack->Unlock(lpDirectD->lpddsd->lpSurface);

		return;
	}

	//Horizontal case

	if (disty==0)
	{
		x = (x2>x1)?x1:x2;

		y = y1;

		scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);

		*(UWord*)scradr = linecol;	// PlotPixel(x,y);

		for (;distx--;scradr+=BytesPerPixel,x++)	*(UWord*)scradr = linecol;	// PlotPixel(x,y);

		lpDirectD->lpDDSBack->Unlock(lpDirectD->lpddsd->lpSurface);

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

		scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);

		*(UWord*)scradr = linecol;	// PlotPixel(x,y);

		if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
		{
			for (;distx--;)
			{
				x++;

				scradr += BytesPerPixel;

				if (p<0)
					p += const1;
				else
				{
					y++;

					scradr += BytesPerScanLine;

					p += const2;
				}

				*(UWord*)scradr = linecol;	// PlotPixel(x,y);
			}

			lpDirectD->lpDDSBack->Unlock(lpDirectD->lpddsd->lpSurface);

			return;
		}
		else
		{
			for (;distx--;)
			{
				x++;

				scradr += BytesPerPixel;

				if (p<0)
					p += const1;
				else
				{
					y--;

					scradr -= BytesPerScanLine;

					p += const2;
				}

				*(UWord*)scradr = linecol;	// PlotPixel(x,y);

			}

			lpDirectD->lpDDSBack->Unlock(lpDirectD->lpddsd->lpSurface);

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

		scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);

		*(UWord*)scradr = linecol;	// PlotPixel(x,y);
		
		if ((y==y1 && x2>x1) || (y==y2 && x1>x2))
 		{
 			for (;disty--;)
 			{
 				y++;

				scradr += BytesPerScanLine;

	 			if (p<0)
	 				p += const1;
	 			else
	 			{
	 				x++;

					scradr += BytesPerPixel;

	 				p += const2;
	 			}

	 			*(UWord*)scradr = linecol;	// PlotPixel(x,y);
	 		}

			lpDirectD->lpDDSBack->Unlock(lpDirectD->lpddsd->lpSurface);

			return;
	 	}
		else
	 	{
	 		for (;disty--;)
	 		{
	 			y++;

				scradr += BytesPerScanLine;

	 			if (p<0)
	 				p += const1;
	 			else
	 			{
	 				x--;

					scradr -= BytesPerPixel;

	 				p += const2;
	 			}

	 			*(UWord*)scradr = linecol;	// PlotPixel(x,y);
	 		}

			lpDirectD->lpDDSBack->Unlock(lpDirectD->lpddsd->lpSurface);

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

	scradr = logicalscreenptr + (y * BytesPerScanLine) + (x * BytesPerPixel);

	*(UWord*)scradr = linecol;	// PlotPixel(x,y);

	if ((x==x1 && y2>y1) || (x==x2 && y1>y2))
	{
		for (;distx--;)
		{
			x++; y++;

			scradr += BytesPerScanLine + BytesPerPixel;

			*(UWord*)scradr = linecol;	// PlotPixel(x,y);
		}
	}
	else 
	{
		for (;distx--;)
		{
			x++; y--;

			scradr += BytesPerPixel - BytesPerScanLine;

			*(UWord*)scradr = linecol;	// PlotPixel(x,y);
		}
	}
	lpDirectD->lpDDSBack->Unlock(lpDirectD->lpddsd->lpSurface);
}*/

static TWODEFFECT tdeffect=TDE_UNIFORM;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Add2DEffect
//Author		Paul.   
//Date			Wed 22 Apr 1998
//------------------------------------------------------------------------------
void direct_3d::Add2DEffect(struct _DirectDraw* lpDirectD, TWODEFFECT tdeEffect)
{
	if (!Save_Data.gamedifficulty[GD_GEFFECTS] &&
		!Save_Data.gamedifficulty[GD_WHITEOUT])
		return;

	tdeEffect=tdeffect;

   	if (CurrentFadeStep!=0)
	{
   	 	switch (tdeEffect)
		{
 			case TDE_INSIDE2OUT:
   			FadeIn2Out(CurrentFadeStep);
     		break;

			case TDE_OUTSIDE2IN:
			FadeOut2In(CurrentFadeStep);
  			break;

   			case TDE_UNIFORM:
			default:
   			FadeUniform(CurrentFadeStep);
     		break;
 		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFade
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
void direct_3d::SetFade(Colour tCol,SLong step,TwoDeeEffect tdfx)
{
	SLong	oldFadeStep=CurrentFadeStep;
	tdeffect=tdfx;

	TargetFadeColour	= tCol;
	if (step<0)			CurrentFadeStep = 0;
	else if (step>31)	CurrentFadeStep = 31;
//	else if (step>15)	CurrentFadeStep = 15;
	else				CurrentFadeStep = step;
	if (oldFadeStep==CurrentFadeStep)	return;

	fadeRed = peSrcPalette[tCol].peRed;
	fadeGreen = peSrcPalette[tCol].peGreen;
	fadeBlue = peSrcPalette[tCol].peBlue;
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
Bool direct_3d::EnableBackClip(Bool bFlag)
{
	Bool	retval;
	retval = bBackClipEnabled;
	bBackClipEnabled = bFlag;
	return (retval);
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
void direct_3d::SetFadeValue(UByte newValue)
{
	CurrentFadeValue = newValue;
}

D3DVALUE sunXpos,sunYpos;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Body2Screen
//Author		Paul.   
//Date			Wed 25 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::Body2Screen(DoPointStruc& dp)
{
	D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*dp.bodyz.f));
	D3DVALUE sx=D3DVALUE(viewdata.scalex*dp.bodyx.f*rw);
	D3DVALUE sy=D3DVALUE(-(viewdata.scaley*dp.bodyy.f*rw));
	dp.screenx.f=sx;
	dp.screeny.f=sy;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSunPos
//Author		Paul.   
//Date			Fri 27 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::SetSunPos(DoPointStruc& dp)
{
	sunXpos=dp.screenx.f+viewdata.originx;
	sunYpos=dp.screeny.f+viewdata.originy;
}

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
void direct_3d::TestHW3D(struct _DirectDraw* lpdirectd,Window*)
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
void direct_3d::SetFogState(Bool bFogOn)
{
	if (!Driver[CurrDriver].bDoesFogVertex && !Driver[CurrDriver].bDoesFogTable)
		bGlobalFogFlag = FALSE;
	else
		bGlobalFogFlag = bFogOn;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceRender
//Author		Paul.   
//Date			Tue 24 Mar 1998
//------------------------------------------------------------------------------
void direct_3d::ForceRender(struct _DirectDraw* lpdirectd)
{
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGlobalAlpha
//Author		Paul.   
//Date			Fri 27 Mar 1998
//------------------------------------------------------------------------------
UByte direct_3d::SetGlobalAlpha(UByte aVal)
{
	UByte oldVal=globalAlphaValue;
	globalAlphaValue=aVal;
	return oldVal;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetShadeVals
//Author		Paul.   
//Date			Wed 1 Apr 1998
//------------------------------------------------------------------------------
void direct_3d::SetShadeVals(SLong nr,SLong ng,SLong nb,SLong er,SLong eg,SLong eb)
{
	vEffectsRed=er;
	vEffectsGreen=eg;
	vEffectsBlue=eb;

	vNormalRed=nr;
	vNormalGreen=ng;
	vNormalBlue=nb;

	vShadeRed=nr;
	vShadeGreen=ng;
	vShadeBlue=nb;

	AmbientLight=RGBA_MAKE(nr,ng,nb,0xFF);	//White;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTextureQuality
//Author		Paul.   
//Date			Mon 20 Apr 1998
//------------------------------------------------------------------------------
void direct_3d::SetTextureQuality(struct _DirectDraw* lpDirectD,bool increase)
{
	SWord oldTextureQuality=textureQuality;
 	if (increase && ++textureQuality>TQ_High) textureQuality=TQ_High;
	else if (--textureQuality<TQ_Low) textureQuality=TQ_Low;
	if (textureQuality==oldTextureQuality) return;
	//Execute all outstanding draw commands & then release all textures
	//currently on the card
	ReleaseTextures();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FadeIn2Out
//Author		Paul.   
//Date			Tue 28 Apr 1998
//------------------------------------------------------------------------------
void direct_3d::FadeIn2Out(SLong step)
{
	struct PolyCoords{Float x,y;};
	struct PolyDefs{SLong a,b,c;};
	const int _pointCnt=9;
	const int _polyCnt=8;
	static PolyCoords _coords[_pointCnt]=
	{
		{-1,-1},
		{0,-1},
		{1,-1},
		{1,0},
		{1,1},
		{0,1},
		{-1,1},
		{-1,0},
		{0,0}
	};
	static PolyDefs _polys[_polyCnt]={{8,0,1},{8,1,2},{8,2,3},{8,3,4},{8,4,5},{8,5,6},{8,6,7},{8,7,0}};
	static UByte _fadeVals[_pointCnt];

	//generate fade values for this frame...
	if (step>15){
	 	for (int i=0;i<_pointCnt-1;_fadeVals[i++]=(step-16)<<4){}
		_fadeVals[i]=0xFF;
	}
	else{
	 	for (int i=0;i<_pointCnt-1;_fadeVals[i++]=0){}
		_fadeVals[i]=step<<4;
	}
	//draw the polys on screen
	HRESULT dderrval;

	//Create an execute buffer
	D3DEXECUTEBUFFERDESC xbufdesc;
	LPDIRECT3DEXECUTEBUFFER	lpxbuf;
    ZeroMem(&xbufdesc,sizeof(D3DEXECUTEBUFFERDESC));
    xbufdesc.dwSize=sizeof(D3DEXECUTEBUFFERDESC);
    xbufdesc.dwFlags=D3DDEB_BUFSIZE;
    xbufdesc.dwBufferSize=1024;
	lpD3DDevice->CreateExecuteBuffer(&xbufdesc,&lpxbuf,NULL);
	lpxbuf->Lock(&xbufdesc);

	LPVOID lpBufStart=xbufdesc.lpData;
	LPVOID lpPointer=lpBufStart;

	//Add vertices to the execute buffer
	LPD3DTLVERTEX lpD3DTLVertex=(LPD3DTLVERTEX)lpPointer;

	for (int i=0;i<_pointCnt;i++){
		D3DTLVERTEX& vt=*lpD3DTLVertex++;
		PolyCoords& pc=_coords[i];

		if (i==_pointCnt-1)
		{
			vt.sx=sunXpos;
			vt.sy=sunYpos;
		}
		else
		{
			vt.sx=viewdata.originx+pc.x*viewdata.scalex;
			vt.sy=viewdata.originy+pc.y*viewdata.scaley;
		}
		vt.sz=0.0;
		vt.rhw=0.9999;
 		vt.color=RGBA_MAKE(fadeRed,fadeGreen,fadeBlue,_fadeVals[i]);
		vt.specular=specularNULL;
		vt.tu=0;
		vt.tv=0;
	}
	LPVOID lpInsStart=lpPointer=(LPVOID)lpD3DTLVertex;

	OP_STATE_RENDER(7,lpPointer);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,FALSE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATEALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,lpPointer);

	//Process vertices instruction
	OP_PROCESS_VERTICES(1,lpPointer);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,0,_pointCnt,lpPointer);

	if (!QWORD_ALIGNED(lpPointer))	{OP_NOP(lpPointer);}

	//Triangle data
	OP_TRIANGLE_LIST(_polyCnt,lpPointer);
	LPD3DTRIANGLE lpD3DTriangle=(LPD3DTRIANGLE)lpPointer;

	for (i=0;i<_polyCnt;i++){
		D3DTRIANGLE& tri=*lpD3DTriangle++;
		PolyDefs& pd=_polys[i];
		tri.v1		= pd.a;
		tri.v2 		= pd.b;
		tri.v3 		= pd.c;
		tri.wFlags	= D3DTRIFLAG_START;
	}
	lpPointer=(LPVOID)lpD3DTriangle;

	OP_STATE_RENDER(2,lpPointer);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,bGlobalFogFlag,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,lpPointer);
	OP_EXIT(lpPointer);
	lpxbuf->Unlock();

	DWORD	dwStatus = 	D3DSTATUS_CLIPUNIONALL |
						D3DSTATUS_CLIPINTERSECTIONALL |
						D3DSTATUS_ZNOTVISIBLE;

	D3DEXECUTEDATA	ExData;
	ZeroMem(&ExData,sizeof(ExData));
	ExData.dwSize 				= sizeof(D3DEXECUTEDATA);
	ExData.dwVertexCount 		= _pointCnt;
	ExData.dwInstructionOffset 	= (ULONG)((char*)lpInsStart - (char*)lpBufStart);
	ExData.dwInstructionLength 	= (ULONG)((char*)lpPointer - (char*)lpInsStart);
	ExData.dsStatus.dwFlags 	= D3DSETSTATUS_ALL;
	ExData.dsStatus.dwStatus	= dwStatus;
	ExData.dsStatus.drExtent.x1 = 256;
	ExData.dsStatus.drExtent.y1 = 256;
	ExData.dsStatus.drExtent.x2 = 0;
	ExData.dsStatus.drExtent.y2 = 0;

	lpxbuf->SetExecuteData(&ExData);
	lpD3DDevice->Execute(lpxbuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
	RELEASE(lpxbuf,dderrval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FadeOut2In
//Author		Paul.   
//Date			Tue 28 Apr 1998
//------------------------------------------------------------------------------
void direct_3d::FadeOut2In(SLong step)
{
	struct PolyCoords{Float x,y;};
	struct PolyDefs{SLong a,b,c;};
	const int _pointCnt=9;
	const int _polyCnt=8;
	static PolyCoords _coords[_pointCnt]=
	{
		{-1,-1},
		{0,-1},
		{1,-1},
		{1,0},
		{1,1},
		{0,1},
		{-1,1},
		{-1,0},
		{0,0}
	};
	static PolyDefs _polys[_polyCnt]={{8,0,1},{8,1,2},{8,2,3},{8,3,4},{8,4,5},{8,5,6},{8,6,7},{8,7,0}};
	static UByte _fadeVals[_pointCnt];

	//generate fade values for this frame...
	if (step>15){
	 	for (int i=0;i<_pointCnt-1;_fadeVals[i++]=0xFF){}
		_fadeVals[i]=(step-16)<<4;
	}
	else{
	 	for (int i=0;i<_pointCnt-1;_fadeVals[i++]=step<<4){}
		_fadeVals[i]=0;
	}
	//draw the polys on screen
	HRESULT dderrval;

	//Create an execute buffer
	D3DEXECUTEBUFFERDESC xbufdesc;
	LPDIRECT3DEXECUTEBUFFER	lpxbuf;
    ZeroMem(&xbufdesc,sizeof(D3DEXECUTEBUFFERDESC));
    xbufdesc.dwSize=sizeof(D3DEXECUTEBUFFERDESC);
    xbufdesc.dwFlags=D3DDEB_BUFSIZE;
    xbufdesc.dwBufferSize=1024;
	lpD3DDevice->CreateExecuteBuffer(&xbufdesc,&lpxbuf,NULL);
	lpxbuf->Lock(&xbufdesc);

	LPVOID lpBufStart=xbufdesc.lpData;
	LPVOID lpPointer=lpBufStart;

	//Add vertices to the execute buffer
	LPD3DTLVERTEX lpD3DTLVertex=(LPD3DTLVERTEX)lpPointer;

	for (int i=0;i<_pointCnt;i++){
		D3DTLVERTEX& vt=*lpD3DTLVertex++;
		PolyCoords& pc=_coords[i];
		vt.sx=viewdata.originx+pc.x*viewdata.scalex;
		vt.sy=viewdata.originy+pc.y*viewdata.scaley;
		vt.sz=0.0;
		vt.rhw=0.9999;
 		vt.color=RGBA_MAKE(fadeRed,fadeGreen,fadeBlue,_fadeVals[i]);
		vt.specular=specularNULL;
		vt.tu=0;
		vt.tv=0;
	}
	LPVOID lpInsStart=lpPointer=(LPVOID)lpD3DTLVertex;

	OP_STATE_RENDER(7,lpPointer);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,FALSE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATEALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,lpPointer);

	//Process vertices instruction
	OP_PROCESS_VERTICES(1,lpPointer);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,0,_pointCnt,lpPointer);

	if (!QWORD_ALIGNED(lpPointer))	{OP_NOP(lpPointer);}

	//Triangle data
	OP_TRIANGLE_LIST(_polyCnt,lpPointer);
	LPD3DTRIANGLE lpD3DTriangle=(LPD3DTRIANGLE)lpPointer;

	for (i=0;i<_polyCnt;i++){
		D3DTRIANGLE& tri=*lpD3DTriangle++;
		PolyDefs& pd=_polys[i];
		tri.v1		= pd.a;
		tri.v2 		= pd.b;
		tri.v3 		= pd.c;
		tri.wFlags	= D3DTRIFLAG_START;
	}
	lpPointer=(LPVOID)lpD3DTriangle;

	OP_STATE_RENDER(2,lpPointer);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,bGlobalFogFlag,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,lpPointer);
	OP_EXIT(lpPointer);
	lpxbuf->Unlock();

	DWORD	dwStatus = 	D3DSTATUS_CLIPUNIONALL |
						D3DSTATUS_CLIPINTERSECTIONALL |
						D3DSTATUS_ZNOTVISIBLE;

	D3DEXECUTEDATA	ExData;
	ZeroMem(&ExData,sizeof(ExData));
	ExData.dwSize 				= sizeof(D3DEXECUTEDATA);
	ExData.dwVertexCount 		= _pointCnt;
	ExData.dwInstructionOffset 	= (ULONG)((char*)lpInsStart - (char*)lpBufStart);
	ExData.dwInstructionLength 	= (ULONG)((char*)lpPointer - (char*)lpInsStart);
	ExData.dsStatus.dwFlags 	= D3DSETSTATUS_ALL;
	ExData.dsStatus.dwStatus	= dwStatus;
	ExData.dsStatus.drExtent.x1 = 256;
	ExData.dsStatus.drExtent.y1 = 256;
	ExData.dsStatus.drExtent.x2 = 0;
	ExData.dsStatus.drExtent.y2 = 0;

	lpxbuf->SetExecuteData(&ExData);
	lpD3DDevice->Execute(lpxbuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
	RELEASE(lpxbuf,dderrval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmokedGlassBox
//Author		Paul    
//Date			Sun 7 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::SmokedGlassBox(DirectD* lpDirectD,SWord x,SWord y,SWord w,SWord h,ULong colour)
{
	FlushPTDraw(lpDirectD,normalXXB);
	FlushPCDraw(lpDirectD,plaincXB);

	FlushPLDraw(lpDirectD,lineXB);
	FlushPPDraw(lpDirectD,pointXB);

	FlushPTDraw(lpDirectD,maskedXXB);
	FlushPTDraw(lpDirectD,transpXXB);

	FlushPTDraw(lpDirectD,fontXXB);

	struct PolyCoords{Float x,y;};
	struct PolyDefs{SLong a,b,c;};
	const int _pointCnt=4;
	const int _polyCnt=2;
	static PolyCoords _coords[_pointCnt];//=
	static PolyDefs _polys[_polyCnt]={{3,0,1},{3,1,2}};
	static UByte _fadeVals[_pointCnt];

	//draw the polys on screen
	HRESULT dderrval;

	_coords[0].x=D3DVALUE(x);		//fx-1.;
	_coords[0].y=D3DVALUE(y);		//-1.;

	_coords[1].x=D3DVALUE(x+w-1);	//fx-1.+fw;
	_coords[1].y=D3DVALUE(y);		//fy-1.;

	_coords[2].x=D3DVALUE(x+w-1);	//fx-1.+fw;
	_coords[2].y=D3DVALUE(y+h-1);	//fy-1.+fh;

	_coords[3].x=D3DVALUE(x);		//fx-1.;
	_coords[3].y=D3DVALUE(y+h-1);	//fy-1.+fh;

	//Create an execute buffer
	D3DEXECUTEBUFFERDESC xbufdesc;
	LPDIRECT3DEXECUTEBUFFER	lpxbuf;
    ZeroMem(&xbufdesc,sizeof(D3DEXECUTEBUFFERDESC));
    xbufdesc.dwSize=sizeof(D3DEXECUTEBUFFERDESC);
    xbufdesc.dwFlags=D3DDEB_BUFSIZE;
    xbufdesc.dwBufferSize=1024;
	lpD3DDevice->CreateExecuteBuffer(&xbufdesc,&lpxbuf,NULL);
	lpxbuf->Lock(&xbufdesc);

	LPVOID lpBufStart=xbufdesc.lpData;
	LPVOID lpPointer=lpBufStart;

	//Add vertices to the execute buffer
	LPD3DTLVERTEX lpD3DTLVertex=(LPD3DTLVERTEX)lpPointer;

	for (int i=0;i<_pointCnt;i++){
		D3DTLVERTEX& vt=*lpD3DTLVertex++;
		PolyCoords& pc=_coords[i];
		vt.sx=pc.x;	//viewdata.originx+pc.x*viewdata.scalex;
		vt.sy=pc.y;	//viewdata.originy+pc.y*viewdata.scaley;
		vt.sz=0.0;
		vt.rhw=0.99999;
 		vt.color=D3DCOLOR(colour);
		vt.specular=specularNULL;
		vt.tu=0;
		vt.tv=0;
	}
	LPVOID lpInsStart=lpPointer=(LPVOID)lpD3DTLVertex;

	OP_STATE_RENDER(7,lpPointer);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,FALSE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATEALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,lpPointer);

	//Process vertices instruction
	OP_PROCESS_VERTICES(1,lpPointer);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,0,_pointCnt,lpPointer);

	if (!QWORD_ALIGNED(lpPointer))	{OP_NOP(lpPointer);}

	//Triangle data
	OP_TRIANGLE_LIST(_polyCnt,lpPointer);
	LPD3DTRIANGLE lpD3DTriangle=(LPD3DTRIANGLE)lpPointer;

	for (i=0;i<_polyCnt;i++){
		D3DTRIANGLE& tri=*lpD3DTriangle++;
		PolyDefs& pd=_polys[i];
		tri.v1		= pd.a;
		tri.v2 		= pd.b;
		tri.v3 		= pd.c;
		tri.wFlags	= D3DTRIFLAG_START;
	}
	lpPointer=(LPVOID)lpD3DTriangle;

	OP_STATE_RENDER(2,lpPointer);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,bGlobalFogFlag,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,lpPointer);
	OP_EXIT(lpPointer);
	lpxbuf->Unlock();

	DWORD	dwStatus = 	D3DSTATUS_CLIPUNIONALL |
						D3DSTATUS_CLIPINTERSECTIONALL |
						D3DSTATUS_ZNOTVISIBLE;

	D3DEXECUTEDATA	ExData;
	ZeroMem(&ExData,sizeof(ExData));
	ExData.dwSize 				= sizeof(D3DEXECUTEDATA);
	ExData.dwVertexCount 		= _pointCnt;
	ExData.dwInstructionOffset 	= (ULONG)((char*)lpInsStart - (char*)lpBufStart);
	ExData.dwInstructionLength 	= (ULONG)((char*)lpPointer - (char*)lpInsStart);
	ExData.dsStatus.dwFlags 	= D3DSETSTATUS_ALL;
	ExData.dsStatus.dwStatus	= dwStatus;
	ExData.dsStatus.drExtent.x1 = 256;
	ExData.dsStatus.drExtent.y1 = 256;
	ExData.dsStatus.drExtent.x2 = 0;
	ExData.dsStatus.drExtent.y2 = 0;

	lpxbuf->SetExecuteData(&ExData);
	lpD3DDevice->Execute(lpxbuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
	RELEASE(lpxbuf,dderrval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Uniform
//Author		Paul.   
//Date			Tue 28 Apr 1998
//------------------------------------------------------------------------------
void direct_3d::FadeUniform(SLong step)
{
	struct PolyCoords{Float x,y;};
	struct PolyDefs{SLong a,b,c;};
	const int _pointCnt=4;
	const int _polyCnt=2;
	static PolyCoords _coords[_pointCnt]=
	{
		{-1,-1},
		{1,-1},
		{1,1},
		{-1,1}
	};
	static PolyDefs _polys[_polyCnt]={{3,0,1},{3,1,2}};
	static UByte _fadeVals[_pointCnt];

	//generate fade values for this frame...
 	for (int i=0;i<_pointCnt;_fadeVals[i++]=step<<3){}

	//draw the polys on screen
	HRESULT dderrval;

	//Create an execute buffer
	D3DEXECUTEBUFFERDESC xbufdesc;
	LPDIRECT3DEXECUTEBUFFER	lpxbuf;
    ZeroMem(&xbufdesc,sizeof(D3DEXECUTEBUFFERDESC));
    xbufdesc.dwSize=sizeof(D3DEXECUTEBUFFERDESC);
    xbufdesc.dwFlags=D3DDEB_BUFSIZE;
    xbufdesc.dwBufferSize=1024;
	lpD3DDevice->CreateExecuteBuffer(&xbufdesc,&lpxbuf,NULL);
	lpxbuf->Lock(&xbufdesc);

	LPVOID lpBufStart=xbufdesc.lpData;
	LPVOID lpPointer=lpBufStart;

	//Add vertices to the execute buffer
	LPD3DTLVERTEX lpD3DTLVertex=(LPD3DTLVERTEX)lpPointer;

	for (i=0;i<_pointCnt;i++){
		D3DTLVERTEX& vt=*lpD3DTLVertex++;
		PolyCoords& pc=_coords[i];
		vt.sx=viewdata.originx+pc.x*viewdata.scalex;
		vt.sy=viewdata.originy+pc.y*viewdata.scaley;
		vt.sz=0.0;
		vt.rhw=0.9999;
 		vt.color=RGBA_MAKE(fadeRed,fadeGreen,fadeBlue,_fadeVals[i]);
		vt.specular=specularNULL;
		vt.tu=0;
		vt.tv=0;
	}
	LPVOID lpInsStart=lpPointer=(LPVOID)lpD3DTLVertex;

	OP_STATE_RENDER(7,lpPointer);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,FALSE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,lpPointer);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATEALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,lpPointer);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,lpPointer);

	//Process vertices instruction
	OP_PROCESS_VERTICES(1,lpPointer);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,0,_pointCnt,lpPointer);

	if (!QWORD_ALIGNED(lpPointer))	{OP_NOP(lpPointer);}

	//Triangle data
	OP_TRIANGLE_LIST(_polyCnt,lpPointer);
	LPD3DTRIANGLE lpD3DTriangle=(LPD3DTRIANGLE)lpPointer;

	for (i=0;i<_polyCnt;i++){
		D3DTRIANGLE& tri=*lpD3DTriangle++;
		PolyDefs& pd=_polys[i];
		tri.v1		= pd.a;
		tri.v2 		= pd.b;
		tri.v3 		= pd.c;
		tri.wFlags	= D3DTRIFLAG_START;
	}
	lpPointer=(LPVOID)lpD3DTriangle;

	OP_STATE_RENDER(2,lpPointer);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,bGlobalFogFlag,lpPointer);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,lpPointer);
	OP_EXIT(lpPointer);
	lpxbuf->Unlock();

	DWORD	dwStatus = 	D3DSTATUS_CLIPUNIONALL |
						D3DSTATUS_CLIPINTERSECTIONALL |
						D3DSTATUS_ZNOTVISIBLE;

	D3DEXECUTEDATA	ExData;
	ZeroMem(&ExData,sizeof(ExData));
	ExData.dwSize 				= sizeof(D3DEXECUTEDATA);
	ExData.dwVertexCount 		= _pointCnt;
	ExData.dwInstructionOffset 	= (ULONG)((char*)lpInsStart - (char*)lpBufStart);
	ExData.dwInstructionLength 	= (ULONG)((char*)lpPointer - (char*)lpInsStart);
	ExData.dsStatus.dwFlags 	= D3DSETSTATUS_ALL;
	ExData.dsStatus.dwStatus	= dwStatus;
	ExData.dsStatus.drExtent.x1 = 256;
	ExData.dsStatus.drExtent.y1 = 256;
	ExData.dsStatus.drExtent.x2 = 0;
	ExData.dsStatus.drExtent.y2 = 0;

	lpxbuf->SetExecuteData(&ExData);
	lpD3DDevice->Execute(lpxbuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
	RELEASE(lpxbuf,dderrval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetClipState
//Author		Paul.   
//Date			Wed 29 Apr 1998
//------------------------------------------------------------------------------
bool direct_3d::SetClipState(bool newState)
{
	bool oldState=clipTestEnabled;
	clipTestEnabled=newState;
	clipTestEnabled=true;
	return oldState;
}

static bool fanIsNear=false;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginFan
//Author		Paul.   
//Date			Tue 2 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::BeginFan(ULong hTexture)
{
	assert(false&&"Dead routine");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginFan
//Author		Paul.   
//Date			Tue 2 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::BeginFan(struct _DirectDraw* lpdirectd,ImageMapDesc* pImage)
{
	assert(false&&"Dead routine");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddFanPoint
//Author		Paul.   
//Date			Tue 2 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::AddFanPoint(struct _DirectDraw* lpdirectd,
							DoPointStruc* pdp,
							SLong vertexCount,
							UByte*& pDataStream)
{
	assert(false&&"Dead routine");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateLandExecuteBuffer
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::CreateLandExecuteBuffer()
{
	// normal unclipped land tile execute buffer
	SetupExecuteBuffer(lpD3DDevice,65536,&landXB);
	SetInitialRenderStatesLand(&landXB);

	//normal clipped land tile execute buffer
	SetupExecuteBuffer(lpD3DDevice,65536,&clandXB);
	SetInitialRenderStatesLand(&clandXB);

	//near tile execute buffer
	SetupExecuteBuffer(lpD3DDevice,65536,&nearlndXB);
	SetInitialRenderStatesLand(&nearlndXB);

	//clipped version of near tile execute buffer
	SetupExecuteBuffer(lpD3DDevice,65536,&cnearlndXB);
	SetInitialRenderStatesLand(&cnearlndXB);

	SetupExecuteBuffer(lpD3DDevice,65536,&ditherlndXB);
	SetInitialRenderStatesTransp(&ditherlndXB);

	SetupExecuteBuffer(lpD3DDevice,65536,&cditherlndXB);
	SetInitialRenderStatesTransp(&cditherlndXB);

	//plain colored polygons execute buffer
	SetupExecuteBuffer(lpD3DDevice,32768,&plaincXB);
	SetInitialRenderStatesPlain(&plaincXB);

	//plain textured polygons execute buffer
	SetupExecuteBuffer(lpD3DDevice,65536,&normalXXB);
	SetInitialRenderStatesTextured(&normalXXB);

	//non z-buffered polys
	SetupExecuteBuffer(lpD3DDevice,65536,&nzbufXXB);
	SetInitialRenderStatesTextured(&nzbufXXB);

	//font execute buffer
	SetupExecuteBuffer(lpD3DDevice,16384,&fontXXB);
	SetInitialRenderStatesFont(&fontXXB);

	//masked textured polygons execute buffer
	SetupExecuteBuffer(lpD3DDevice,65536,&maskedXXB);
	SetInitialRenderStatesMasked(&maskedXXB);

	//transp textured polygons execute buffer
	SetupExecuteBuffer(lpD3DDevice,65536,&transpXXB);
	SetInitialRenderStatesTransp(&transpXXB);

	//plain line execute buffer
	SetupExecuteBuffer(lpD3DDevice,16384,&lineXB);
	SetInitialRenderStatesLines(&lineXB);

	//plain point execute buffer
	SetupExecuteBuffer(lpD3DDevice,16384,&pointXB);
	SetInitialRenderStatesPoints(&pointXB);

	ResetBufferUse(landXB.bufUse);
	ResetBufferUse(clandXB.bufUse);
	ResetBufferUse(normalXXB.bufUse);
	ResetBufferUse(maskedXXB.bufUse);
	ResetBufferUse(transpXXB.bufUse);
	ResetBufferUse(nzbufXXB.bufUse);
	ResetBufferUse(fontXXB.bufUse);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushLandDraw
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::FlushLandDraw(struct _DirectDraw* pDirectD,struct XBuf& xb)
{
	HRESULT dderrval;

	//add op-exit to the end of the buffer

	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pistart=pinst;

	OP_EXIT(pinst);

	dderrval=xb.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	xb.bLocked=false;

 	xb.instOffset+=ULong(pinst)-ULong(pistart);

	//DumpXBuffer(xb);

	assert(xb._inst_len>=(ULong(xb.instOffset)-xb._inst_start)&&"Execute buffer o'flow");

	//DumpXBuffer(xb);
	if (xb.vertCount>0)
	{
		const DWORD dwStatus=
		D3DSTATUS_CLIPUNIONALL|D3DSTATUS_CLIPINTERSECTIONALL|D3DSTATUS_ZNOTVISIBLE;

		//execute the current execute buffer
		D3DEXECUTEDATA xData;
		ZeroMem(&xData,sizeof(D3DEXECUTEDATA));
		xData.dwSize=sizeof(D3DEXECUTEDATA);
		xData.dwVertexCount=xb.vertCount;
		xData.dwInstructionOffset=xb._inst_start;
		xData.dwInstructionLength=ULong(xb.instOffset)-xb._inst_start;
		xData.dsStatus.dwFlags=D3DSETSTATUS_ALL;
		xData.dsStatus.dwStatus=dwStatus;

		xData.dsStatus.drExtent.x2=0;
		xData.dsStatus.drExtent.y2=0;

		xData.dsStatus.drExtent.x1=winWidth;
		xData.dsStatus.drExtent.y1=winHeight;
		dderrval=xb.pxBuf->SetExecuteData(&xData);
		DIRECT3DERROR(dderrval);
		dderrval=lpD3DDevice->Execute(xb.pxBuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
		DIRECT3DERROR(dderrval);
	}
	//reset for the next set of poly data

	xb.vertCount=0;
	xb.instOffset=xb._inst_start;

	//fill in initial state changes
	SetInitialRenderStatesLand(&xb);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushDitherDraw
//Author		Paul.   
//Date			Wed 2 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::FlushDitherDraw(struct _DirectDraw* pDirectD,struct XBuf& xb)
{
	HRESULT dderrval;

	//add op-exit to the end of the buffer

	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pistart=pinst;

	OP_EXIT(pinst);

	dderrval=xb.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	xb.bLocked=false;

 	xb.instOffset+=ULong(pinst)-ULong(pistart);

	//DumpXBuffer(xb);

	assert(xb._inst_len>=(ULong(xb.instOffset)-xb._inst_start)&&"Execute buffer o'flow");

	//DumpXBuffer(xb);
	if (xb.vertCount>0)
	{
		const DWORD dwStatus=
		D3DSTATUS_CLIPUNIONALL|D3DSTATUS_CLIPINTERSECTIONALL|D3DSTATUS_ZNOTVISIBLE;

		//execute the current execute buffer
		D3DEXECUTEDATA xData;
		ZeroMem(&xData,sizeof(D3DEXECUTEDATA));
		xData.dwSize=sizeof(D3DEXECUTEDATA);
		xData.dwVertexCount=xb.vertCount;
		xData.dwInstructionOffset=xb._inst_start;
		xData.dwInstructionLength=ULong(xb.instOffset)-xb._inst_start;
		xData.dsStatus.dwFlags=D3DSETSTATUS_ALL;
		xData.dsStatus.dwStatus=dwStatus;

		xData.dsStatus.drExtent.x2=0;
		xData.dsStatus.drExtent.y2=0;

		xData.dsStatus.drExtent.x1=winWidth;
		xData.dsStatus.drExtent.y1=winHeight;
		dderrval=xb.pxBuf->SetExecuteData(&xData);
		DIRECT3DERROR(dderrval);
		dderrval=lpD3DDevice->Execute(xb.pxBuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
		DIRECT3DERROR(dderrval);
	}
	//reset for the next set of poly data

	xb.vertCount=0;
	xb.instOffset=xb._inst_start;

	//fill in initial state changes
	SetInitialRenderStatesTransp(&xb);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NearAddTileVertices
//Author		Paul    
//Date			Sun 21 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::NearAddTileVertices(struct _DirectDraw* pDirectD,
									ULong pntCnt,
									ULong totalTris,
									DoPointStruc* pdp,
									ULong drwCnt,
									UByte*& pdd,
									ULong hT)
{
	UByte* pdrawdata=pdd;

	if (nearlndXB.vertCount+pntCnt>nearlndXB._max_verts)
	{	
		FlushLandDraw(pDirectD,nearlndXB);
	}
	else
	{	//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*totalTris+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(nearlndXB._inst_len-nearlndXB.instOffset))
			FlushLandDraw(pDirectD,nearlndXB);
	}

	//add to the current buffer

	ULong vBase=nearlndXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)nearlndXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)nearlndXB.xbDesc.lpData)+nearlndXB.instOffset);
	void* pistart=pinst;

	for (int i=0;i<pntCnt;i++,pdp++,ptlvert++)
	{
		ptlvert->sx=D3DVALUE(pdp->bodyx.f);
		ptlvert->sy=D3DVALUE(pdp->bodyy.f);
		ptlvert->sz=D3DVALUE(pdp->bodyz.f);

		if (lightingEffectsEnabled)		SetVertexColor(ptlvert,pdp);
		else							ptlvert->color=AmbientLight;	//D3DCOLOR(0x00FFFFFF);

		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert->tu=D3DVALUE(pdp->ix)*D3DVALUE(1./256.);
		ptlvert->tv=D3DVALUE(pdp->iy)*D3DVALUE(1./256.);
	}

	VIDRAMTEXTURE* pVrt=vidramlandptr[hT];
	D3DTEXTUREHANDLE hTexture=pVrt->d3dhTexture;

	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,hTexture,pinst);

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);

	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	while (drwCnt--)
	{
		pdrawdata++;	//skip the colour byte

		ULong fanCnt=*pdrawdata++;
		while (fanCnt--){
			ULong triCnt=*pdrawdata++;
			OP_TRIANGLE_LIST(triCnt,pinst);
			int v1=vBase+*pdrawdata++;
			int v2=vBase+*pdrawdata++;
			int v3=vBase+*pdrawdata++;

			((D3DTRIANGLE*)pinst)->v1=v1;
			((D3DTRIANGLE*)pinst)->v2=v2;
			((D3DTRIANGLE*)pinst)->v3=v3;
			((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
			pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
			triCnt--;
			while (triCnt--)
			{
				v2=v3;
				v3=vBase+*pdrawdata++;
				((D3DTRIANGLE*)pinst)->v1=v1;
				((D3DTRIANGLE*)pinst)->v2=v2;
				((D3DTRIANGLE*)pinst)->v3=v3;
				((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
				pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
			}
		}
	}
	nearlndXB.vertCount+=pntCnt;
	nearlndXB.instOffset+=ULong(pinst)-ULong(pistart);
	pdd=pdrawdata;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InsFan
//Author		Paul.   
//Date			Wed 24 Jun 1998
//------------------------------------------------------------------------------
inline void direct_3d::InsFan(	ULong vBase,UByte* renumber,
								ULong pntCnt,UByte* twsp,
								void*& pinst)
{
	if (pntCnt>2)
	{
		pntCnt-=2;
		OP_TRIANGLE_LIST(pntCnt--,pinst);
		int v1=vBase+renumber[*twsp++];
		int v2=vBase+renumber[*twsp++];
		int v3=vBase+renumber[*twsp++];

		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

		while (pntCnt--)
		{
			v2=v3;
			v3=vBase+renumber[*twsp++];
			((D3DTRIANGLE*)pinst)->v1=v1;
			((D3DTRIANGLE*)pinst)->v2=v2;
			((D3DTRIANGLE*)pinst)->v3=v3;
			((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
			pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InsStrip
//Author		Paul.   
//Date			Wed 24 Jun 1998
//------------------------------------------------------------------------------
inline void direct_3d::InsStrip(	ULong vBase,UByte* renumber,
									ULong pntCnt,UByte* twsp,bool dir,
									void*& pinst)
{
	if (pntCnt>2)
	{
		pntCnt-=2;
		OP_TRIANGLE_LIST(pntCnt,pinst);
		int v1=vBase+renumber[*twsp++];
		int v2=vBase+renumber[*twsp++];
		int v3=vBase+renumber[*twsp++];
		while (pntCnt--)
		{
			if (dir)
			{
				((D3DTRIANGLE*)pinst)->v1=v1;
				((D3DTRIANGLE*)pinst)->v2=v2;
				((D3DTRIANGLE*)pinst)->v3=v3;
			}
			else
			{
				((D3DTRIANGLE*)pinst)->v1=v1;
				((D3DTRIANGLE*)pinst)->v2=v3;
				((D3DTRIANGLE*)pinst)->v3=v2;
			}
			((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
			pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
			v1=v2;
			v2=v3;
			v3=vBase+renumber[*twsp++];
			dir=!dir;
		}
	}
}

#define _makeRecIndex(a,b)\
		(a)>=(b)?\
		((b)*recordsused+(a)):\
		((a)*recordsused+(b));

#define _makeSimpleIndex(a,b)\
		(b)*recordsused+(a);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CNearAddTileVertices
//Author		Paul.   
//Date			Wed 24 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::CNearAddTileVertices(	struct _DirectDraw* pDirectD,
										ULong pntCnt,
										ULong totalTris,
										DoPointStruc* pdp,
										ULong drwCnt,
										UByte*& pdd,
										ULong hT)
{
	UByte* pdrawdata=pdd;

	ULong interpFlag;

	interpFlag=	IF3D_TEXTURE+
				((globalSpecular)?IF3D_SPECULAR:0)+
				((globalLighting)?IF3D_COLOR:0);

	DoPointStruc* psdp=pdp;

	static UByte renumber[256];

	ULong pntEstimate=pntCnt+pntCnt+pntCnt;
	ULong trisEstimate=totalTris+totalTris;

	if (cnearlndXB.vertCount+pntEstimate>cnearlndXB._max_verts)
	{	
		FlushLandDraw(pDirectD,cnearlndXB);
	}
	else
	{	//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						(2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE))*drwCnt+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(cnearlndXB._inst_len-cnearlndXB.instOffset))
			FlushLandDraw(pDirectD,cnearlndXB);
	}

	//add to the current buffer

	ULong vBase=cnearlndXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)cnearlndXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)cnearlndXB.xbDesc.lpData)+cnearlndXB.instOffset);
	void* pistart=pinst;

	int renumberIndex=0;

	for (int srcPntIndex=0;srcPntIndex<pntCnt;srcPntIndex++,psdp++)
	{
		if (psdp->clipFlags==CF3D_NULL)
		{
			ptlvert->sx=D3DVALUE(psdp->bodyx.f);
			ptlvert->sy=D3DVALUE(psdp->bodyy.f);
			ptlvert->sz=D3DVALUE(psdp->bodyz.f);
			SetVertexColor(ptlvert,psdp);
			ptlvert->clipFlags=psdp->clipFlags|interpFlag;
			ptlvert->tu=D3DVALUE(psdp->ix)*D3DVALUE(1./256.);
			ptlvert->tv=D3DVALUE(psdp->iy)*D3DVALUE(1./256.);
			ptlvert++;
			renumber[srcPntIndex]=renumberIndex++;
		}
	}
	pntCnt=renumberIndex;

	VIDRAMTEXTURE* pVrt=vidramlandptr[hT];
	D3DTEXTUREHANDLE hTexture=pVrt->d3dhTexture;

	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,hTexture,pinst);

	//Add the process vertices instruction but leave the
	//count field blank 'til later
	OP_PROCESS_VERTICES(1,pinst);
	D3DPROCESSVERTICES* ppv=(D3DPROCESSVERTICES*)pinst;
	ppv->dwFlags=D3DPROCESSVERTICES_COPY;
	ppv->wStart=ppv->wDest=vBase;
	ppv->dwReserved=0;
	pinst=(void*)(ppv+1);

	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	static UByte wkspc[256];

	while (drwCnt--)
	{
		pdrawdata++;					//skip colour byte
		ULong fanCount=*pdrawdata++;
		
		while (fanCount--)
		{
			//reset index into temporary workspace
			ULong wkspcindex=0;

			//number of triangles in the fan
			ULong triCount=*pdrawdata++; 

			//fan base point
			UByte p1=*pdrawdata++;
			UByte p2;
			UByte p3=*pdrawdata++;

			//clip flags for fan base point
			UWord basecf=(pdp[p1].clipFlags&CF3D_ALL);
			UWord cfp2;
			UWord cfp3=(pdp[p3].clipFlags&CF3D_ALL);

			while (triCount--)
			{
				p2=p3;
				cfp2=cfp3;
				p3=*pdrawdata++;
				cfp3=(pdp[p3].clipFlags&CF3D_ALL);

				if ((CF3D_ALL&basecf&cfp2&cfp3)==CF3D_NULL)
				{
					//some of this triangle is visible
				 	if ((CF3D_ALL&(basecf|cfp2|cfp3))==CF3D_NULL)
					{
					 	//no clipping required for this triangle
						//add the triangle to the execute buffer

						OP_TRIANGLE_LIST(1,pinst);
						((D3DTRIANGLE*)pinst)->v1=vBase+renumber[p1];
						((D3DTRIANGLE*)pinst)->v2=vBase+renumber[p2];
						((D3DTRIANGLE*)pinst)->v3=vBase+renumber[p3];
						((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
						pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
					}
					else
					{
						//this triangle needs clipping

						ULong pc=3;

						R3DTLVERTEX tstore[64];
						R3DTLVERTEX* ptstore=tstore;
						R3DTLVERTEX* polydef[64];
						R3DTLVERTEX** pptlv=polydef;

						if (basecf&CF3D_ALL)
						{
							ptstore->sx=D3DVALUE(pdp[p1].bodyx.f);
							ptstore->sy=D3DVALUE(pdp[p1].bodyy.f);
							ptstore->sz=D3DVALUE(pdp[p1].bodyz.f);
							SetVertexColor(ptstore,pdp+p1);
							ptstore->clipFlags=pdp[p1].clipFlags|interpFlag;
							ptstore->tu=D3DVALUE(pdp[p1].ix)*D3DVALUE(1./256.);
							ptstore->tv=D3DVALUE(pdp[p1].iy)*D3DVALUE(1./256.);
							polydef[0]=ptstore++;
						}
						else
						{
						 	polydef[0]=ptlvstart+renumber[p1];
						}

						if (cfp2&CF3D_ALL)
						{
							ptstore->sx=D3DVALUE(pdp[p2].bodyx.f);
							ptstore->sy=D3DVALUE(pdp[p2].bodyy.f);
							ptstore->sz=D3DVALUE(pdp[p2].bodyz.f);
							SetVertexColor(ptstore,pdp+p2);
							ptstore->clipFlags=pdp[p2].clipFlags|interpFlag;
							ptstore->tu=D3DVALUE(pdp[p2].ix)*D3DVALUE(1./256.);
							ptstore->tv=D3DVALUE(pdp[p2].iy)*D3DVALUE(1./256.);
							polydef[1]=ptstore++;
						}
						else
						{
						 	polydef[1]=ptlvstart+renumber[p2];
						}

						if (cfp3&CF3D_ALL)
						{
							ptstore->sx=D3DVALUE(pdp[p3].bodyx.f);
							ptstore->sy=D3DVALUE(pdp[p3].bodyy.f);
							ptstore->sz=D3DVALUE(pdp[p3].bodyz.f);
							SetVertexColor(ptstore,pdp+p3);
							ptstore->clipFlags=pdp[p3].clipFlags|interpFlag;
							ptstore->tu=D3DVALUE(pdp[p3].ix)*D3DVALUE(1./256.);
							ptstore->tv=D3DVALUE(pdp[p3].iy)*D3DVALUE(1./256.);
							polydef[2]=ptstore++;
						}
						else
						{
						 	polydef[2]=ptlvstart+renumber[p3];
						}

						GenericPolyClip(pc,polydef,ptlvert,ptstore);

						if (pc>2)
						{
							int i=0;
							ULong tc=pc-2;
							OP_TRIANGLE_LIST(tc,pinst);
							int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
							int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
							int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
							tc--;
							((D3DTRIANGLE*)pinst)->v1=v1;
							((D3DTRIANGLE*)pinst)->v2=v2;
							((D3DTRIANGLE*)pinst)->v3=v3;
							((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
							pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

							while (tc--)
							{
								v2=v3;
								v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
								((D3DTRIANGLE*)pinst)->v1=v1;
								((D3DTRIANGLE*)pinst)->v2=v2;
								((D3DTRIANGLE*)pinst)->v3=v3;
								((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
								pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
							}
						}
					}
				}
			}
		}
	}

	//fix up half generated points...

	pntCnt=(ULong(ptlvert)-ULong(ptlvstart))>>5;

	ptlvert=ptlvstart;

	for (srcPntIndex=0;srcPntIndex<pntCnt;srcPntIndex++)
	{
		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert++;
	}

	ppv->dwCount=pntCnt;

	cnearlndXB.vertCount+=pntCnt;
	cnearlndXB.instOffset+=ULong(pinst)-ULong(pistart);
	pdd=pdrawdata;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Clipping macros
//
///////////////////////////////////////////////////////////////////////////////

#define lrTest(testBx,testBz)\
		(testBx)>(testBz)?\
		CF3D_OFFRIGHT:\
		((testBx)<0.&&-(testBx)>(testBz))?\
		CF3D_OFFLEFT:\
		CF3D_NULL

#define tbTest(testBy,testBz)\
		(testBy)>(testBz)?\
		CF3D_OFFTOP:\
		((testBy)<0.&&-(testBy)>(testBz))?\
		CF3D_OFFBOTTOM:\
		CF3D_NULL

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetColor
//Author		Paul    
//Date			Sun 5 Jul 1998
//------------------------------------------------------------------------------
inline void direct_3d::SetVertexColor(R3DTLVERTEX* ptlvert,DoPointStruc* pdp)
{
	if (globalLighting)
	{
		SWord cval=SWord(pdp->intensity);
		cval=cval<0?0:cval>255?255:cval;

		ptlvert->col.r=(vShadeRed*cval)>>8;
		ptlvert->col.g=(vShadeGreen*cval)>>8;
		ptlvert->col.b=(vShadeBlue*cval)>>8;
		ptlvert->col.a=AmbientALPHA;

		if (!globalSpecular || pdp->specular==-1)
		{
			ptlvert->specular=specularNULL;
		}
		else if (globalSpecular && pdp->specular!=-1)
		{
			cval=pdp->specular;
			ptlvert->spec.r=(vShadeRed*cval)>>8;
			ptlvert->spec.g=(vShadeGreen*cval)>>8;
			ptlvert->spec.b=(vShadeBlue*cval)>>8;
		}
		else if (pdp->mist)
		{
			cval=pdp->mist;
			cval*=MistRED;
			cval>>=8;
			ptlvert->spec.r=
				ptlvert->spec.g=
				ptlvert->spec.b=UByte(cval);
		}
		else if (pdp->snow)
		{
			cval=pdp->snow;
			cval*=SnowRED;
			cval>>=8;
			ptlvert->spec.r=
				ptlvert->spec.g=
				ptlvert->spec.b=UByte(cval);
		}
		else ptlvert->specular=specularNULL;
	}
	else
	{
		ptlvert->color=AmbientLight;	//White;
		ptlvert->specular=specularNULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTileVertices
//Author		Paul.   
//Date			Fri 19 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::AddTileVertices(struct _DirectDraw* pDirectD,
								ULong pntCnt,
								ULong totalTris,
								DoPointStruc* pdp,
								ULong drwCnt,
								UByte*& pdd)
{
	UByte* pdrawdata=pdd;

	bool doflush=false;

	if (landXB.vertCount+pntCnt>landXB._max_verts)
	{	
		FlushPTDraw(pDirectD,landXB);
	}
	else
	{
		//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						(2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE))*drwCnt+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*totalTris+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(landXB._inst_len-landXB.instOffset))
		{
			FlushPTDraw(pDirectD,landXB);
		}
	}

	//add to the current buffer

	ULong vBase=landXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)landXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)landXB.xbDesc.lpData)+landXB.instOffset);
	void* pibase=(void*)(((UByte*)landXB.xbDesc.lpData)+landXB._inst_start);
	void* pistart=pinst;

	for (int i=0;i<pntCnt;i++,pdp++,ptlvert++)
	{
		ptlvert->sx=D3DVALUE(pdp->bodyx.f);
		ptlvert->sy=D3DVALUE(pdp->bodyy.f);
		ptlvert->sz=D3DVALUE(pdp->bodyz.f);
		SetVertexColor(ptlvert,pdp);
		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert->tu=D3DVALUE(pdp->ix)*D3DVALUE(1./256.);
		ptlvert->tv=D3DVALUE(pdp->iy)*D3DVALUE(1./256.);
	}

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);

	while (drwCnt--)
	{
		//CLandColor landCol(*pdrawdata++);
		//ImageMapDescPtr pmap=landCol.pImg();
		pdrawdata++;
		ImageMapDescPtr pmap=NULL;

		OP_STATE_RENDER(1,pinst);
   		void* poff=(void*)(ULong(pinst)+4);
		STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
		if (pmap)
		{
			UWord* pOffset;
			if (RecordTextureUse(pmap,pOffset,landXB.bufUse))
				*pOffset=UWord(ULong(poff)-ULong(pibase));
			else
				doflush=true;
		}

		if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

		ULong fanCnt=*pdrawdata++;
		while (fanCnt--){
			ULong triCnt=*pdrawdata++;
			OP_TRIANGLE_LIST(triCnt,pinst);
			int v1=vBase+*pdrawdata++;
			int v2=vBase+*pdrawdata++;
			int v3=vBase+*pdrawdata++;

			((D3DTRIANGLE*)pinst)->v1=v1;
			((D3DTRIANGLE*)pinst)->v2=v2;
			((D3DTRIANGLE*)pinst)->v3=v3;
			((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
			pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
			triCnt--;

			while (triCnt--)
			{
				v2=v3;
				v3=vBase+*pdrawdata++;
				((D3DTRIANGLE*)pinst)->v1=v1;
				((D3DTRIANGLE*)pinst)->v2=v2;
				((D3DTRIANGLE*)pinst)->v3=v3;
				((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
				pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
			}
		}
	}
	landXB.vertCount+=pntCnt;
	landXB.instOffset+=ULong(pinst)-ULong(pistart);

	if (doflush) FlushPTDraw(pDirectD,landXB);
	pdd=pdrawdata;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CAddTileVertices
//Author		Paul.   
//Date			Tue 23 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::CAddTileVertices(struct _DirectDraw* pDirectD,
								ULong pntCnt,
								ULong totalTris,
								DoPointStruc* pdp,
								ULong drwCnt,
								UByte*& pdd)
{
	UByte* pdrawdata=pdd;

	ULong interpFlag=	IF3D_TEXTURE+
						((globalSpecular)?IF3D_SPECULAR:0)+
						((globalLighting)?IF3D_COLOR:0);

	bool doflush=false;

	DoPointStruc* psdp=pdp;

	static UByte renumber[256];

	ULong pntEstimate=pntCnt+pntCnt+pntCnt;
	ULong trisEstimate=totalTris+totalTris;

	if (clandXB.vertCount+pntEstimate>clandXB._max_verts)
	{	
		FlushPTDraw(pDirectD,clandXB);
	}
	else
	{	//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						(2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE))*drwCnt+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(clandXB._inst_len-clandXB.instOffset))
			FlushPTDraw(pDirectD,clandXB);
	}

	//add to the current buffer

	ULong vBase=clandXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)clandXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)clandXB.xbDesc.lpData)+clandXB.instOffset);
	void* pibase=(void*)(((UByte*)clandXB.xbDesc.lpData)+clandXB._inst_start);
	void* pistart=pinst;

	int renumberIndex=0;

	for (int srcPntIndex=0;srcPntIndex<pntCnt;srcPntIndex++,psdp++)
	{
		if (psdp->clipFlags==CF3D_NULL)
		{
			ptlvert->sx=D3DVALUE(psdp->bodyx.f);
			ptlvert->sy=D3DVALUE(psdp->bodyy.f);
			ptlvert->sz=D3DVALUE(psdp->bodyz.f);
			SetVertexColor(ptlvert,psdp);
			ptlvert->clipFlags=psdp->clipFlags|interpFlag;
			ptlvert->tu=D3DVALUE(psdp->ix)*D3DVALUE(1./256.);
			ptlvert->tv=D3DVALUE(psdp->iy)*D3DVALUE(1./256.);
			ptlvert++;
			renumber[srcPntIndex]=renumberIndex++;
		}
	}
	pntCnt=renumberIndex;

	//Add the process vertices instruction but leave the
	//count field blank 'til later
	OP_PROCESS_VERTICES(1,pinst);
	D3DPROCESSVERTICES* ppv=(D3DPROCESSVERTICES*)pinst;
	ppv->dwFlags=D3DPROCESSVERTICES_COPY;
	ppv->wStart=ppv->wDest=vBase;
	ppv->dwReserved=0;
	pinst=(void*)(ppv+1);

	static UByte wkspc[256];

	while (drwCnt--)
	{
		pdrawdata++;
		ImageMapDescPtr pmap=NULL;

		OP_STATE_RENDER(1,pinst);
   		void* poff=(void*)(ULong(pinst)+4);
		STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
		if (pmap)
		{
			UWord* pOffset;
			if (RecordTextureUse(pmap,pOffset,clandXB.bufUse))
				*pOffset=UWord(ULong(poff)-ULong(pibase));
			else
				doflush=true;
		}

		if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

		ULong fanCount=*pdrawdata++;
		
		while (fanCount--)
		{
			//reset index into temporary workspace
			ULong wkspcindex=0;

			//number of triangles in the fan
			ULong triCount=*pdrawdata++; 

			//fan base point
			UByte p1=*pdrawdata++;
			UByte p2;
			UByte p3=*pdrawdata++;

			//clip flags for fan base point
			UWord basecf=(pdp[p1].clipFlags&CF3D_ALL);
			UWord cfp2;
			UWord cfp3=(pdp[p3].clipFlags&CF3D_ALL);

			while (triCount--)
			{
				p2=p3;
				cfp2=cfp3;
				p3=*pdrawdata++;
				cfp3=(pdp[p3].clipFlags&CF3D_ALL);

				if ((CF3D_ALL&basecf&cfp2&cfp3)==CF3D_NULL)
				{
					//some of this triangle is visible
				 	if ((CF3D_ALL&(basecf|cfp2|cfp3))==CF3D_NULL)
					{
					 	//no clipping required for this triangle
						//add the triangle to the execute buffer

						OP_TRIANGLE_LIST(1,pinst);
						((D3DTRIANGLE*)pinst)->v1=vBase+renumber[p1];
						((D3DTRIANGLE*)pinst)->v2=vBase+renumber[p2];
						((D3DTRIANGLE*)pinst)->v3=vBase+renumber[p3];
						((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
						pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
					}
					else
					{
						//this triangle needs clipping

						ULong pc=3;

						R3DTLVERTEX tstore[64];
						R3DTLVERTEX* ptstore=tstore;
						R3DTLVERTEX* polydef[64];
						R3DTLVERTEX** pptlv=polydef;

						if (basecf&CF3D_ALL)
						{
							ptstore->sx=D3DVALUE(pdp[p1].bodyx.f);
							ptstore->sy=D3DVALUE(pdp[p1].bodyy.f);
							ptstore->sz=D3DVALUE(pdp[p1].bodyz.f);
							SetVertexColor(ptstore,pdp+p1);
							ptstore->clipFlags=pdp[p1].clipFlags|interpFlag;
							ptstore->tu=D3DVALUE(pdp[p1].ix)*D3DVALUE(1./256.);
							ptstore->tv=D3DVALUE(pdp[p1].iy)*D3DVALUE(1./256.);
							polydef[0]=ptstore++;
						}
						else
						{
						 	polydef[0]=ptlvstart+renumber[p1];
						}

						if (cfp2&CF3D_ALL)
						{
							ptstore->sx=D3DVALUE(pdp[p2].bodyx.f);
							ptstore->sy=D3DVALUE(pdp[p2].bodyy.f);
							ptstore->sz=D3DVALUE(pdp[p2].bodyz.f);
							SetVertexColor(ptstore,pdp+p2);
							ptstore->clipFlags=pdp[p2].clipFlags|interpFlag;
							ptstore->tu=D3DVALUE(pdp[p2].ix)*D3DVALUE(1./256.);
							ptstore->tv=D3DVALUE(pdp[p2].iy)*D3DVALUE(1./256.);
							polydef[1]=ptstore++;
						}
						else
						{
						 	polydef[1]=ptlvstart+renumber[p2];
						}

						if (cfp3&CF3D_ALL)
						{
							ptstore->sx=D3DVALUE(pdp[p3].bodyx.f);
							ptstore->sy=D3DVALUE(pdp[p3].bodyy.f);
							ptstore->sz=D3DVALUE(pdp[p3].bodyz.f);
							SetVertexColor(ptstore,pdp+p3);
							ptstore->clipFlags=pdp[p3].clipFlags|interpFlag;
							ptstore->tu=D3DVALUE(pdp[p3].ix)*D3DVALUE(1./256.);
							ptstore->tv=D3DVALUE(pdp[p3].iy)*D3DVALUE(1./256.);
							polydef[2]=ptstore++;
						}
						else
						{
						 	polydef[2]=ptlvstart+renumber[p3];
						}

						GenericPolyClip(pc,polydef,ptlvert,ptstore);

						if (pc>2)
						{
							int i=0;
							ULong tc=pc-2;
							OP_TRIANGLE_LIST(tc,pinst);
							int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
							int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
							int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
							tc--;
							((D3DTRIANGLE*)pinst)->v1=v1;
							((D3DTRIANGLE*)pinst)->v2=v2;
							((D3DTRIANGLE*)pinst)->v3=v3;
							((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
							pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

							while (tc--)
							{
								v2=v3;
								v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
								((D3DTRIANGLE*)pinst)->v1=v1;
								((D3DTRIANGLE*)pinst)->v2=v2;
								((D3DTRIANGLE*)pinst)->v3=v3;
								((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
								pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
							}
						}
					}
				}
			}
		}
	}

	//fix up half generated points...

	pntCnt=(ULong(ptlvert)-ULong(ptlvstart))>>5;

	ptlvert=ptlvstart;

	for (srcPntIndex=0;srcPntIndex<pntCnt;srcPntIndex++)
	{
		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert++;
	}

	ppv->dwCount=pntCnt;

	clandXB.vertCount+=pntCnt;
	clandXB.instOffset+=ULong(pinst)-ULong(pistart);

	if (doflush) FlushPTDraw(pDirectD,clandXB);
	pdd=pdrawdata;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		clipRGBA
//Author		Paul.   
//Date			Mon 29 Jun 1998
//
//------------------------------------------------------------------------------
inline void clipRGBA(R3DCOLOR inc,R3DCOLOR outc,R3DCOLOR* clipc,double frac)
{
	if (inc==outc)
	{
		*clipc=inc;
	}
	else
	{
		SLong ifrac=SLong(frac*65536);

		//clip red component

		if (inc.r==outc.r)
			clipc->r=inc.r;
		else
		{
			SLong newr=SLong(inc.r)+(((SLong(outc.r)-SLong(inc.r))*ifrac)>>16);
			clipc->r=newr<0?UByte(0):newr>255?UByte(255):UByte(newr);
		}

		//clip green component

		if (inc.g==outc.g)
			clipc->g=inc.g;
		else
		{
			SLong newg=SLong(inc.g)+(((SLong(outc.g)-SLong(inc.g))*ifrac)>>16);
			clipc->g=newg<0?UByte(0):newg>255?UByte(255):UByte(newg);
		}

		//clip blue component

		if (inc.b==outc.b)
			clipc->b=inc.b;
		else
		{
			SLong newb=SLong(inc.b)+(((SLong(outc.b)-SLong(inc.b))*ifrac)>>16);
			clipc->b=newb<0?UByte(0):newb>255?UByte(255):UByte(newb);
		}

		//clip alpha component

		if (inc.a==outc.a)
			clipc->a=inc.a;
		else
		{
			SLong newa=SLong(inc.a)+(((SLong(outc.a)-SLong(inc.a))*ifrac)>>16);
			clipc->a=newa<0?UByte(0):newa>255?UByte(255):UByte(newa);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		clipRGB
//Author		Paul.   
//Date			Mon 29 Jun 1998
//
//------------------------------------------------------------------------------
inline void clipRGB(R3DCOLOR inc,R3DCOLOR outc,R3DCOLOR* clipc,double frac)
{
	if (inc==outc)
	{
		*clipc=inc;
	}
	else
	{
		SLong ifrac=SLong(frac*65536);

		//clip red component

		if (inc.r==outc.r)
			clipc->r=inc.r;
		else
		{
			SLong newr=SLong(inc.r)+(((SLong(outc.r)-SLong(inc.r))*ifrac)>>16);
			clipc->r=newr<0?UByte(0):newr>255?UByte(255):UByte(newr);
		}

		//clip green component

		if (inc.g==outc.g)
			clipc->g=inc.g;
		else
		{
			SLong newg=SLong(inc.g)+(((SLong(outc.g)-SLong(inc.g))*ifrac)>>16);
			clipc->g=newg<0?UByte(0):newg>255?UByte(255):UByte(newg);
		}

		//clip blue component

		if (inc.b==outc.b)
			clipc->b=inc.b;
		else
		{
			SLong newb=SLong(inc.b)+(((SLong(outc.b)-SLong(inc.b))*ifrac)>>16);
			clipc->b=newb<0?UByte(0):newb>255?UByte(255):UByte(newb);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RClipToFront
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::RClipToFront(	R3DTLVERTEX* vIn,R3DTLVERTEX* vOut,
								R3DTLVERTEX* vClip)
{
	UWord typeFlag=vIn->clipFlags&IF3D_ALL;

	vClip->sz=D3DVALUE(viewdata.D);
	double frac=(vClip->sz-vIn->sz)/(vOut->sz-vIn->sz);
	vClip->sx=D3DVALUE(vIn->sx+frac*(vOut->sx-vIn->sx));
	vClip->sy=D3DVALUE(vIn->sy+frac*(vOut->sy-vIn->sy));

	//clip texture coordinates if required
	if (typeFlag&IF3D_TEXTURE)
	{
		vClip->tu=D3DVALUE(vIn->tu+frac*(vOut->tu-vIn->tu));
		vClip->tv=D3DVALUE(vIn->tv+frac*(vOut->tv-vIn->tv));
	}

	//clip color field if required
	if (typeFlag&IF3D_COLOR)
	 	clipRGBA(vIn->col,vOut->col,&vClip->col,frac);
	else
		vClip->color=vIn->color;

	//clip specular field if required
	if (typeFlag&IF3D_SPECULAR)
	 	clipRGB(vIn->spec,vOut->spec,&vClip->spec,frac);
	else
		vClip->specular=vIn->specular;

	//Set clipping flags for the new clipped vertex

	vClip->clipFlags=typeFlag;
	_clipLR(vClip->clipFlags,vClip->sx,vClip->sz);
	_clipTB(vClip->clipFlags,vClip->sy,vClip->sz);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RClipToBack
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::RClipToBack(R3DTLVERTEX* vIn,R3DTLVERTEX* vOut,
							R3DTLVERTEX* vClip)
{
	UWord typeFlag=vIn->clipFlags&IF3D_ALL;

	vClip->sz=D3DVALUE(viewdata.F);

	double frac=(vClip->sz-vIn->sz)/(vOut->sz-vIn->sz);

	vClip->sx=D3DVALUE(vIn->sx+frac*(vOut->sx-vIn->sx));
	vClip->sy=D3DVALUE(vIn->sy+frac*(vOut->sy-vIn->sy));

	if (typeFlag&IF3D_TEXTURE)
	{
		vClip->tu=D3DVALUE(vIn->tu+frac*(vOut->tu-vIn->tu));
		vClip->tv=D3DVALUE(vIn->tv+frac*(vOut->tv-vIn->tv));
	}

	//clip color field if required
	if (typeFlag&IF3D_COLOR)
		clipRGBA(vIn->col,vOut->col,&vClip->col,frac);
	else
		vClip->color=vIn->color;

	//clip specular field if required
	if (typeFlag&IF3D_SPECULAR)
		clipRGB(vIn->spec,vOut->spec,&vClip->spec,frac);
	else
		vClip->specular=vIn->specular;

	//Set clipping flags for the new clipped vertex

	vClip->clipFlags=typeFlag;
	_clipLR(vClip->clipFlags,vClip->sx,vClip->sz);
	_clipTB(vClip->clipFlags,vClip->sy,vClip->sz);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RClipToEast
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::RClipToEast(R3DTLVERTEX* vIn,R3DTLVERTEX* vOut,
							R3DTLVERTEX* vClip)
{
	UWord typeFlag=vIn->clipFlags&IF3D_ALL;

	double dZ=vOut->sz-vIn->sz; CLAMP (dZ);
	double dX=vOut->sx-vIn->sx; CLAMP (dX);

	double frac;

	if (dX==0.0)
	{
		vClip->sx=vClip->sz=vIn->sx;
		frac=(vClip->sz-vIn->sz)/(vOut->sz-vIn->sz);
	}
	else if (dZ==0.0)
	{
		vClip->sx=vClip->sz=vIn->sz;
		frac=(vClip->sx-vIn->sx)/(vOut->sx-vIn->sx);
	}
	else
	{
		double clipGradient=dZ/dX;
		double clipConst=vIn->sz-clipGradient*vIn->sx;
		vClip->sx=D3DVALUE(clipConst/(1.0-clipGradient));
		vClip->sz=vClip->sx;
		frac=(vClip->sx-vIn->sx)/(vOut->sx-vIn->sx);
	}

	vClip->sy=D3DVALUE(vIn->sy+frac*(vOut->sy-vIn->sy));

	//clip texture coordinates if required
	if (typeFlag&IF3D_TEXTURE)
	{
		vClip->tu=D3DVALUE(vIn->tu+frac*(vOut->tu-vIn->tu));
		vClip->tv=D3DVALUE(vIn->tv+frac*(vOut->tv-vIn->tv));
	}

	if (typeFlag&IF3D_COLOR)
	 	clipRGBA(vIn->col,vOut->col,&vClip->col,frac);
	else
		vClip->color=vIn->color;

	//clip specular field if required
	if (typeFlag&IF3D_SPECULAR)
	 	clipRGB(vIn->spec,vOut->spec,&vClip->spec,frac);
	else
		vClip->specular=vIn->specular;

	//Set clipping flags for the new clipped vertex

	vClip->clipFlags=typeFlag;
	_clipTB(vClip->clipFlags,vClip->sy,vClip->sz);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RClipToWest
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::RClipToWest(R3DTLVERTEX* vIn,R3DTLVERTEX* vOut,
							R3DTLVERTEX* vClip)
{
	UWord typeFlag=vIn->clipFlags&IF3D_ALL;

	double dZ=vOut->sz-vIn->sz; CLAMP (dZ);
	double dX=vOut->sx-vIn->sx; CLAMP (dX);

	double frac;

	if (dX==0.0)
	{
		vClip->sx=vIn->sx;
		vClip->sz=D3DVALUE(-vIn->sx);
		frac=(vClip->sz-vIn->sz)/(vOut->sz-vIn->sz);
	}
	else if (dZ==0.0)
	{
		vClip->sx=D3DVALUE(-vIn->sz);
		vClip->sz=vIn->sz;
		frac=(vClip->sx-vIn->sx)/(vOut->sx-vIn->sx);
	}
	else
	{
		double clipGradient=dZ/dX;
		double clipConst=vIn->sz-clipGradient*vIn->sx;
		vClip->sx=D3DVALUE(clipConst/(-1.0-clipGradient));
		vClip->sz=D3DVALUE(-vClip->sx);
		frac=(vClip->sx-vIn->sx)/(vOut->sx-vIn->sx);
	}

	vClip->sy=D3DVALUE(vIn->sy+frac*(vOut->sy-vIn->sy));

	//clip texture coordinates if required
	if (typeFlag&IF3D_TEXTURE)
	{
		vClip->tu=D3DVALUE(vIn->tu+frac*(vOut->tu-vIn->tu));
		vClip->tv=D3DVALUE(vIn->tv+frac*(vOut->tv-vIn->tv));
	}

	//clip color field if required
	if (typeFlag&IF3D_COLOR)
	 	clipRGBA(vIn->col,vOut->col,&vClip->col,frac);
	else
		vClip->color=vIn->color;

	//clip specular field if required
	if (typeFlag&IF3D_SPECULAR)
	 	clipRGB(vIn->spec,vOut->spec,&vClip->spec,frac);
	else
		vClip->specular=vIn->specular;

	//Set clipping flags for the new clipped vertex

	vClip->clipFlags=typeFlag;
	_clipTB(vClip->clipFlags,vClip->sy,vClip->sz);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RClipToTop
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::RClipToTop(	R3DTLVERTEX* vIn,R3DTLVERTEX* vOut,
							R3DTLVERTEX* vClip)
{
	UWord typeFlag=vIn->clipFlags&IF3D_ALL;

	double dZ=vOut->sz-vIn->sz; CLAMP (dZ);
	double dY=vOut->sy-vIn->sy; CLAMP (dY);

	double frac;

	if (dY==0.0)
	{
		vClip->sy=vIn->sy;
		vClip->sz=vIn->sy;
		frac=(vClip->sz-vIn->sz)/(vOut->sz-vIn->sz);
	}
	else if (dZ==0.0)
	{
		vClip->sy=vIn->sz;
		vClip->sz=vIn->sz;
		frac=(vClip->sy-vIn->sy)/(vOut->sy-vIn->sy);
	}
	else
	{
		double clipGradient=dZ/dY;
		double clipConst=vIn->sz-clipGradient*vIn->sy;
		vClip->sy=D3DVALUE(clipConst/(1.0-clipGradient));
		vClip->sz=vClip->sy;
		frac=(vClip->sy-vIn->sy)/(vOut->sy-vIn->sy);
	}
	vClip->sx=D3DVALUE(vIn->sx+frac*(vOut->sx-vIn->sx));

	//clip texture coordinates if required
	if (typeFlag&IF3D_TEXTURE)
	{
		vClip->tu=D3DVALUE(vIn->tu+frac*(vOut->tu-vIn->tu));
		vClip->tv=D3DVALUE(vIn->tv+frac*(vOut->tv-vIn->tv));
	}

	//clip color field if required
	if (typeFlag&IF3D_COLOR)
	 	clipRGBA(vIn->col,vOut->col,&vClip->col,frac);
	else
		vClip->color=vIn->color;

	//clip specular field if required
	if (typeFlag&IF3D_SPECULAR)
	 	clipRGB(vIn->spec,vOut->spec,&vClip->spec,frac);
	else
		vClip->specular=vIn->specular;

	//Set clipping flags for the new clipped vertex
	vClip->clipFlags=typeFlag;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RClipToBottom
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::RClipToBottom(	R3DTLVERTEX* vIn,R3DTLVERTEX* vOut,
								R3DTLVERTEX* vClip)
{
	UWord typeFlag=vIn->clipFlags&IF3D_ALL;

	double dZ=vOut->sz-vIn->sz; CLAMP (dZ);
	double dY=vOut->sy-vIn->sy; CLAMP (dY);

	double frac;

	if (dY==0.0)
	{
		vClip->sy=vIn->sy;
		vClip->sz=D3DVALUE(-vIn->sy);
		frac=(vClip->sz-vIn->sz)/(vOut->sz-vIn->sz);
	}
	else if (dZ==0.0)
	{
		vClip->sy=D3DVALUE(-vIn->sz);
		vClip->sz=vIn->sz;
		frac=(vClip->sy-vIn->sy)/(vOut->sy-vIn->sy);
	}
	else
	{
		double clipGradient=dZ/dY;
		double clipConst=vIn->sz-clipGradient*vIn->sy;
		vClip->sy=D3DVALUE(-clipConst/(1.0+clipGradient));
		vClip->sz=D3DVALUE(-vClip->sy);
		frac=(vClip->sy-vIn->sy)/(vOut->sy-vIn->sy);
	}
	vClip->sx=D3DVALUE(vIn->sx+frac*(vOut->sx-vIn->sx));

	//clip texture coordinates if required
	if (typeFlag&IF3D_TEXTURE)
	{
		vClip->tu=D3DVALUE(vIn->tu+frac*(vOut->tu-vIn->tu));
		vClip->tv=D3DVALUE(vIn->tv+frac*(vOut->tv-vIn->tv));
	}

	//clip color field if required
	if (typeFlag&IF3D_COLOR)
	 	clipRGBA(vIn->col,vOut->col,&vClip->col,frac);
	else
		vClip->color=vIn->color;

	//clip specular field if required
	if (typeFlag&IF3D_SPECULAR)
	 	clipRGB(vIn->spec,vOut->spec,&vClip->spec,frac);
	else
		vClip->specular=vIn->specular;

	//Set clipping flags for the new clipped vertex

	vClip->clipFlags=typeFlag;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DOCLIP
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
#define DOCLIP(srcpoly,srcindex,srcnext,dstpoly,dstindex,flag,cliprtn)\
if (!((srcpoly)[(srcindex)]->clipFlags&(flag)))\
{\
	(dstpoly)[(dstindex)++]=(srcpoly)[(srcindex)];\
	if ((srcpoly)[(srcnext)]->clipFlags&(flag))\
	{\
		(cliprtn)((srcpoly)[(srcindex)],(srcpoly)[(srcnext)],ptltemp);\
		if (!(ptltemp->clipFlags&CF3D_ALL))\
		{\
			*ptlvert=*ptltemp;\
			(dstpoly)[(dstindex)++]=ptlvert++;\
		}\
		else\
		{\
			(dstpoly)[(dstindex)++]=ptltemp++;\
		}\
	}\
}\
else if (!((srcpoly)[(srcnext)]->clipFlags&(flag)))\
{\
	(cliprtn)((srcpoly)[(srcnext)],(srcpoly)[(srcindex)],ptltemp);\
	if (!(ptltemp->clipFlags&CF3D_ALL))\
	{\
		*ptlvert=*ptltemp;\
		(dstpoly)[(dstindex)++]=ptlvert++;\
	}\
	else\
	{\
	  	(dstpoly)[(dstindex)++]=ptltemp++;\
	}\
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenericPolyClip
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::GenericPolyClip(ULong& pntCnt,
								R3DTLVERTEX** polydef,
								R3DTLVERTEX*& xptlvert,
								R3DTLVERTEX* ptltemp)
{
	R3DTLVERTEX* ptlvert=xptlvert;
	R3DTLVERTEX* localpolydef[64];

	//clip against near clipping plane

	ULong newPntCnt=0;

	int limit=int(pntCnt)-1;

	for (int i=0;i<limit;i++)
	{
	 	int j=i+1;

		DOCLIP(polydef,i,j,localpolydef,newPntCnt,CF3D_BEHINDNEARZ,RClipToFront);
	}
	DOCLIP(polydef,i,0,localpolydef,newPntCnt,CF3D_BEHINDNEARZ,RClipToFront);

	if ((pntCnt=newPntCnt)<3)
	{
		xptlvert=ptlvert;
		return;	//ABORT if <3 points in the polygon
	}

	newPntCnt=0;

	//clip against the far clipping plane

	limit=int(pntCnt)-1;

	for (i=0;i<limit;i++)
	{
		int j=i+1;

		DOCLIP(localpolydef,i,j,polydef,newPntCnt,CF3D_PASTFARZ,RClipToBack);
	}
	DOCLIP(localpolydef,i,0,polydef,newPntCnt,CF3D_PASTFARZ,RClipToBack);

	if ((pntCnt=newPntCnt)<3)
	{
		xptlvert=ptlvert;
		return;	//ABORT if <3 points in the polygon
	}

	newPntCnt=0;

	//clip against the east clipping plane

	limit=int(pntCnt)-1;

	for (i=0;i<limit;i++)
	{
		int j=i+1;

 		DOCLIP(polydef,i,j,localpolydef,newPntCnt,CF3D_OFFRIGHT,RClipToEast);
	}
	DOCLIP(polydef,i,0,localpolydef,newPntCnt,CF3D_OFFRIGHT,RClipToEast);

	if ((pntCnt=newPntCnt)<3)
	{
		xptlvert=ptlvert;
		return;	//ABORT if <3 points in the polygon
	}

	newPntCnt=0;

	//clip against the west clipping plane

	limit=int(pntCnt)-1;

	for (i=0;i<limit;i++)
	{
		int j=i+1;

		DOCLIP(localpolydef,i,j,polydef,newPntCnt,CF3D_OFFLEFT,RClipToWest);
	}
	DOCLIP(localpolydef,i,0,polydef,newPntCnt,CF3D_OFFLEFT,RClipToWest);

	if ((pntCnt=newPntCnt)<3)
	{
		xptlvert=ptlvert;
		return;	//ABORT if <3 points in the polygon
	}

	newPntCnt=0;

	//clip against the top clipping plane

	limit=int(pntCnt)-1;

	for (i=0;i<limit;i++)
	{
		int j=i+1;

		DOCLIP(polydef,i,j,localpolydef,newPntCnt,CF3D_OFFTOP,RClipToTop);
	}
	DOCLIP(polydef,i,0,localpolydef,newPntCnt,CF3D_OFFTOP,RClipToTop);

	if ((pntCnt=newPntCnt)<3)
	{
		xptlvert=ptlvert;
		return;	//ABORT if <3 points in the polygon
	}

	newPntCnt=0;

	//clip against the bottom clipping plane

	limit=int(pntCnt)-1;

	for (i=0;i<limit;i++)
	{
		int j=i+1;

		DOCLIP(localpolydef,i,j,polydef,newPntCnt,CF3D_OFFBOTTOM,RClipToBottom);
	}
	DOCLIP(localpolydef,i,0,polydef,newPntCnt,CF3D_OFFBOTTOM,RClipToBottom);

	pntCnt=newPntCnt;
	xptlvert=ptlvert;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushPTDraw
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::FlushPTDraw(struct _DirectDraw* pDirectD,struct XXBuf& xb)
{
	HRESULT dderrval;

	//add op-exit to the end of the buffer

	RegisterTextureUse(	pDirectD,
						xb.bufUse,
						(void*)(ULong(xb.xbDesc.lpData)+xb._inst_start));

	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pistart=pinst;

	OP_EXIT(pinst);

	dderrval=xb.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	xb.bLocked=false;

	xb.instOffset+=ULong(pinst)-ULong(pistart);

	//DumpXBuffer(xb);

	assert(xb._inst_len>=(ULong(xb.instOffset)-xb._inst_start)&&"Execute buffer o'flow");

	if (xb.vertCount>0)
	{

		const DWORD dwStatus=
		D3DSTATUS_CLIPUNIONALL|D3DSTATUS_CLIPINTERSECTIONALL|D3DSTATUS_ZNOTVISIBLE;

		//execute the current execute buffer
		D3DEXECUTEDATA xData;
		ZeroMem(&xData,sizeof(D3DEXECUTEDATA));
		xData.dwSize=sizeof(D3DEXECUTEDATA);
		xData.dwVertexCount=xb.vertCount;
		xData.dwInstructionOffset=xb._inst_start;
		xData.dwInstructionLength=ULong(xb.instOffset)-xb._inst_start;
		xData.dsStatus.dwFlags=D3DSETSTATUS_ALL;
		xData.dsStatus.dwStatus=dwStatus;
		xData.dsStatus.drExtent.x2=0;
		xData.dsStatus.drExtent.y2=0;
		xData.dsStatus.drExtent.x1=winWidth;
		xData.dsStatus.drExtent.y1=winHeight;
		dderrval=xb.pxBuf->SetExecuteData(&xData);
		DIRECT3DERROR(dderrval);
		dderrval=lpD3DDevice->Execute(xb.pxBuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
		DIRECT3DERROR(dderrval);
	}
	//reset for the next set of poly data
	xb.vertCount=0;
	xb.instOffset=xb._inst_start;

	//fill in initial state changes

	if (&xb==&transpXXB)		SetInitialRenderStatesTransp(&xb);
	else if (&xb==&maskedXXB)	SetInitialRenderStatesMasked(&xb);
	else if (&xb==&normalXXB)	SetInitialRenderStatesTextured(&xb);
	else						SetInitialRenderStatesFont(&xb);

	//clear texture usage records
	ResetBufferUse(xb.bufUse);

	//Flag video RAM textures as available for re-use
	for (int j=0;j<NumVidTextures;vidramtextures[j++].bInUse=0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushPCDraw
//Author		Paul.   
//Date			Wed 1 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::FlushPCDraw(struct _DirectDraw* pDirectD,struct XBuf& xb)
{
	HRESULT dderrval;

	//add op-exit to the end of the buffer

	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pistart=pinst;

	OP_EXIT(pinst);

	dderrval=xb.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	xb.bLocked=false;

	xb.instOffset+=ULong(pinst)-ULong(pistart);

	assert(xb._inst_len>=(ULong(xb.instOffset)-xb._inst_start)&&"Execute buffer o'flow");

	if (xb.vertCount>0)
	{
		const DWORD dwStatus=
		D3DSTATUS_CLIPUNIONALL|D3DSTATUS_CLIPINTERSECTIONALL|D3DSTATUS_ZNOTVISIBLE;

		//execute the current execute buffer
		D3DEXECUTEDATA xData;
		ZeroMem(&xData,sizeof(D3DEXECUTEDATA));
		xData.dwSize=sizeof(D3DEXECUTEDATA);
		xData.dwVertexCount=xb.vertCount;
		xData.dwInstructionOffset=xb._inst_start;
		xData.dwInstructionLength=ULong(xb.instOffset)-xb._inst_start;
		xData.dsStatus.dwFlags=D3DSETSTATUS_ALL;
		xData.dsStatus.dwStatus=dwStatus;
		xData.dsStatus.drExtent.x2=0;
		xData.dsStatus.drExtent.y2=0;
		xData.dsStatus.drExtent.x1=winWidth;
		xData.dsStatus.drExtent.y1=winHeight;
		dderrval=xb.pxBuf->SetExecuteData(&xData);
		DIRECT3DERROR(dderrval);
		dderrval=lpD3DDevice->Execute(xb.pxBuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
		DIRECT3DERROR(dderrval);
	}
	//reset for the next set of poly data

	xb.vertCount=0;
	xb.instOffset=xb._inst_start;

	//fill in initial state changes
	SetInitialRenderStatesPlain(&xb);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPlainPoly
//Author		Paul.   
//Date			Tue 30 Jun 1998
//------------------------------------------------------------------------------
void direct_3d::AddPlainPoly(DirectD* pDirectD,LPPOLYTYPE lpPolyType)
{
	//get an initial estimate of the number of points and polys
	ULong pntCnt=lpPolyType->points;

 	ULong pntEstimate=(pntCnt+pntCnt);
	ULong trisEstimate=pntEstimate-2;

	if (plaincXB.vertCount+pntEstimate>plaincXB._max_verts)
	{
		FlushPCDraw(pDirectD,plaincXB);
	}
	else
	{
		//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);

		if (totalSize>(plaincXB._inst_len-plaincXB.instOffset))
			FlushPCDraw(pDirectD,plaincXB);
	}
	//there is definately enough room in the current execute buffer
	//to add the new polygon if required

	ULong vBase=plaincXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)plaincXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)plaincXB.xbDesc.lpData)+plaincXB.instOffset);
	void* pistart=pinst;

	//get a pointer to the current input poly definition
	vertex** ppv=lpPolyType->lplpVertices;

	//initialise clipping flags...
	UWord orClip,andClip;
	orClip=CF3D_NULL;
	andClip=CF3D_ALL;

	R3DTLVERTEX tstore[64];
	R3DTLVERTEX* ptstore=tstore;
	R3DTLVERTEX* polydef[64];
	R3DTLVERTEX** pptlv=polydef;

	//this routine will not get called unless the polygon
	//is at least partly visible so prepare to clip if
	//needed

	R3DCOLOR basePolyColor;
	R3DCOLOR shadePolyColor;
	R3DCOLOR& paletteEntry=*(R3DCOLOR*)&palette[lpPolyType->colour].dcColorVal;

	SLong rscale,gscale,bscale;

	ULong interpFlag=IF3D_NULL;

	vertex* pv=*ppv;
	
	basePolyColor.r=((SLong(paletteEntry.r)*vShadeRed)>>8);
	basePolyColor.g=((SLong(paletteEntry.g)*vShadeGreen)>>8);
	basePolyColor.b=((SLong(paletteEntry.b)*vShadeBlue)>>8);
	basePolyColor.a=AmbientALPHA;

	if (plainShadeFlag)
	{
		//relies on item fogging being active!
		Float dummyval=0;
		ULong scaleFactor=CALC_RANGE_FOG(dummyval,dummyval,dummyval);
		shadePolyColor.r=UByte(ULong((ULong(basePolyColor.r)*scaleFactor)+(ULong(fogRedVal)*(0x000000FF-scaleFactor)))>>8);
		shadePolyColor.g=UByte(ULong((ULong(basePolyColor.g)*scaleFactor)+(ULong(fogGreenVal)*(0x000000FF-scaleFactor)))>>8);
		shadePolyColor.b=UByte(ULong((ULong(basePolyColor.b)*scaleFactor)+(ULong(fogBlueVal)*(0x000000FF-scaleFactor)))>>8);
	}
	else if (isLightShaded)
	{
//		rscale=SLong(paletteEntry.r)-SLong(basePolyColor.r);
//		gscale=SLong(paletteEntry.g)-SLong(basePolyColor.g);
//		bscale=SLong(paletteEntry.b)-SLong(basePolyColor.b);
//		SLong darkness=(256<<12)-pv->intensity;
//		darkness=darkness<0?0:darkness>((256<<12)-1)?((256<<12)-1):darkness;
//		shadePolyColor.r=UByte(SLong(basePolyColor.r)+((rscale*darkness)>>20));
//		shadePolyColor.g=UByte(SLong(basePolyColor.g)+((gscale*darkness)>>20));
//		shadePolyColor.b=UByte(SLong(basePolyColor.b)+((bscale*darkness)>>20));
		SWord cval=pv->intensity>>12;
		cval=(cval<0x00)?0x00:(cval>0xFF)?0xFF:cval;
		shadePolyColor.r=(basePolyColor.r*cval)>>8;
		shadePolyColor.g=(basePolyColor.g*cval)>>8;
		shadePolyColor.b=(basePolyColor.b*cval)>>8;
		shadePolyColor.a=AmbientALPHA;
//PaulCode DAW 03May99 		rscale=SLong(paletteEntry.r)-SLong(basePolyColor.r);
//PaulCode DAW 03May99 		gscale=SLong(paletteEntry.g)-SLong(basePolyColor.g);
//PaulCode DAW 03May99 		bscale=SLong(paletteEntry.b)-SLong(basePolyColor.b);
//PaulCode DAW 03May99 		SLong darkness=(256<<12)-pv->intensity;
//PaulCode DAW 03May99 		darkness=darkness<0?0:darkness>((256<<12)-1)?((256<<12)-1):darkness;
//PaulCode DAW 03May99 		shadePolyColor.r=UByte(SLong(basePolyColor.r)+((rscale*darkness)>>20));
//PaulCode DAW 03May99 		shadePolyColor.g=UByte(SLong(basePolyColor.g)+((gscale*darkness)>>20));
//PaulCode DAW 03May99 		shadePolyColor.b=UByte(SLong(basePolyColor.b)+((bscale*darkness)>>20));
	}
	else *(D3DCOLOR*)&shadePolyColor=*(D3DCOLOR*)&basePolyColor;	//paletteEntry;

	shadePolyColor.a=AmbientALPHA;

	for (int i=0;i<pntCnt;i++)
	{
		pv=*ppv++;
		UWord cf=pv->clipFlags;
		orClip|=cf;
		andClip&=cf;

		if (cf==CF3D_NULL)
		{
			//if the point is in the view cone then put
			//it straight into the current execute buffer

			ptlvert->sx=D3DVALUE(pv->bx.f);
			ptlvert->sy=D3DVALUE(pv->by.f);
			ptlvert->sz=D3DVALUE(pv->bz.f);
			ptlvert->clipFlags=cf+interpFlag;
			ptlvert->color=*(D3DCOLOR*)&shadePolyColor;
			*pptlv++=ptlvert;
			ptlvert++;
		}
		else
		{
			//if the point is outside the current view cone
			//then add it to a temporary buffer

			ptstore->sx=D3DVALUE(pv->bx.f);
			ptstore->sy=D3DVALUE(pv->by.f);
			ptstore->sz=D3DVALUE(pv->bz.f);
			ptstore->clipFlags=cf+interpFlag;
			ptstore->color=*(D3DCOLOR*)&shadePolyColor;
			*pptlv++=ptstore;
			ptstore++;
		}
	}
	//just on the off chance that something has
	//gone wrong (Not that it ever does!) check
	//the state of the clip flags and quit if
	//we need to

	if (andClip!=CF3D_NULL)
	{
		//ABORT NOW!!
		return;
	}

	if (orClip!=CF3D_NULL)
	{
	 	//this poly needs to be clipped
		GenericPolyClip(pntCnt,polydef,ptlvert,ptstore);
		
		//check that there is still something to draw after
		//the clipping has been done

		if (pntCnt<3)
		{
			//ABORT NOW!!
			return;
		}
	}

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	*(D3DCOLOR*)&shadePolyColor=specularNULL;

	for (i=0;i<pntCnt;i++)
	{
		shadePolyColor.a=AmbientALPHA;	//CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		ptlvert->specular=*(D3DCOLOR*)&shadePolyColor;
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx);
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy);
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);
		ptlvert++;
	}

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);
	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	ULong triCnt=pntCnt-2;

	OP_TRIANGLE_LIST(triCnt,pinst);

	//first one first
	i=0;
	int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);

	triCnt--;

	((D3DTRIANGLE*)pinst)->v1=v1;
	((D3DTRIANGLE*)pinst)->v2=v2;
	((D3DTRIANGLE*)pinst)->v3=v3;
	((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
	pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

	while (triCnt--)
	{
		v2=v3;
		v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
	}

	plaincXB.vertCount+=pntCnt;
	plaincXB.instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddGouraudPoly
//Author		Paul    
//Date			Sun 5 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::AddGouraudPoly(DirectD* pDirectD,LPPOLYTYPE lpPolyType)
{
	//get an initial estimate of the number of points and polys
	ULong pntCnt=lpPolyType->points;

 	ULong pntEstimate=(pntCnt+pntCnt);
	ULong trisEstimate=pntEstimate-2;

	if (plaincXB.vertCount+pntEstimate>plaincXB._max_verts)
	{
		FlushPCDraw(pDirectD,plaincXB);
	}
	else
	{
		//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);

		if (totalSize>(plaincXB._inst_len-plaincXB.instOffset))
			FlushPCDraw(pDirectD,plaincXB);
	}
	//there is definately enough room in the current execute buffer
	//to add the new polygon if required

	ULong vBase=plaincXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)plaincXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)plaincXB.xbDesc.lpData)+plaincXB.instOffset);
	void* pistart=pinst;

	//get a pointer to the current input poly definition
	vertex** ppv=lpPolyType->lplpVertices;

	//initialise clipping flags...
	UWord orClip,andClip;
	orClip=CF3D_NULL;
	andClip=CF3D_ALL;

	R3DTLVERTEX tstore[64];
	R3DTLVERTEX* ptstore=tstore;
	R3DTLVERTEX* polydef[64];
	R3DTLVERTEX** pptlv=polydef;

	//this routine will not get called unless the polygon
	//is at least partly visible so prepare to clip if
	//needed

	for (int i=0;i<pntCnt;i++)
	{
		vertex* pv=*ppv++;
		UWord cf=pv->clipFlags;
		orClip|=cf;
		andClip&=cf;

		if (cf==CF3D_NULL)
		{
			//if the point is in the view cone then put
			//it straight into the current execute buffer

			ptlvert->sx=D3DVALUE(pv->bx.f);
			ptlvert->sy=D3DVALUE(pv->by.f);
			ptlvert->sz=D3DVALUE(pv->bz.f);
			ptlvert->clipFlags=cf+IF3D_COLOR;
			ptlvert->col.r=pv->col.r;
			ptlvert->col.g=pv->col.g;
			ptlvert->col.b=pv->col.b;
			ptlvert->col.a=AmbientALPHA;
			*pptlv++=ptlvert;
			ptlvert++;
		}
		else
		{
			//if the point is outside the current view cone
			//then add it to a temporary buffer

			ptstore->sx=D3DVALUE(pv->bx.f);
			ptstore->sy=D3DVALUE(pv->by.f);
			ptstore->sz=D3DVALUE(pv->bz.f);
			ptstore->clipFlags=cf+IF3D_COLOR;
			ptstore->col.r=pv->col.r;
			ptstore->col.g=pv->col.g;
			ptstore->col.b=pv->col.b;
			ptstore->col.a=AmbientALPHA;
			*pptlv++=ptstore;
			ptstore++;
		}
	}
	//just on the off chance that something has
	//gone wrong (Not that it ever does!) check
	//the state of the clip flags and quit if
	//we need to

	if (andClip!=CF3D_NULL)
	{
		//ABORT NOW!!
		return;
	}

	if (orClip!=CF3D_NULL)
	{
	 	//this poly needs to be clipped
		GenericPolyClip(pntCnt,polydef,ptlvert,ptstore);
		
		//check that there is still something to draw after
		//the clipping has been done

		if (pntCnt<3)
		{
			//ABORT NOW!!
			return;
		}
	}

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	for (i=0;i<pntCnt;i++)
	{
		ptlvert->specular=specularNULL;
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx);
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy);
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);
		ptlvert++;
	}

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);
	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	ULong triCnt=pntCnt-2;

	OP_TRIANGLE_LIST(triCnt,pinst);

	//first one first
	i=0;
	int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);

	triCnt--;

	((D3DTRIANGLE*)pinst)->v1=v1;
	((D3DTRIANGLE*)pinst)->v2=v2;
	((D3DTRIANGLE*)pinst)->v3=v3;
	((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
	pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

	while (triCnt--)
	{
		v2=v3;
		v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
	}

	plaincXB.vertCount+=pntCnt;
	plaincXB.instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeExecuteBuffers
//Author		Paul.   
//Date			Wed 1 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::FreeExecuteBuffers()
{
	HRESULT dderrval;

	//make sure that all execute buffers are unlocked before they are
	//released

	if (landXB.pxBuf==NULL)
	  	_Error.EmitSysErr("Execute buffers already freed");


	if (landXB.bLocked)		dderrval=landXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	if (nearlndXB.bLocked)	dderrval=nearlndXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	if (clandXB.bLocked)	dderrval=clandXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	if (cnearlndXB.bLocked)	dderrval=cnearlndXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	if (plaincXB.bLocked)	dderrval=plaincXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	if (transpXXB.bLocked)	dderrval=transpXXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	if (maskedXXB.bLocked)	dderrval=maskedXXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	if (normalXXB.bLocked)	dderrval=normalXXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);

//	if (cditherlndXB.bLocked)	dderrval=cditherlndXB.pxBuf->Unlock();
//	DIRECT3DERROR(dderrval);
//	if (ditherlndXB.bLocked)	dderrval=ditherlndXB.pxBuf->Unlock();
//	DIRECT3DERROR(dderrval);

	if (nzbufXXB.bLocked)	dderrval=nzbufXXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	if (fontXXB.bLocked)	dderrval=fontXXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);

	if (lineXB.bLocked)		dderrval=lineXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	if (pointXB.bLocked)	dderrval=pointXB.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);

 	RELEASE(landXB.pxBuf,dderrval);
 	RELEASE(nearlndXB.pxBuf,dderrval);
 	RELEASE(clandXB.pxBuf,dderrval);
 	RELEASE(cnearlndXB.pxBuf,dderrval);

//	RELEASE(ditherlndXB.pxBuf,dderrval);
//	RELEASE(cditherlndXB.pxBuf,dderrval);

 	RELEASE(plaincXB.pxBuf,dderrval);
 	RELEASE(transpXXB.pxBuf,dderrval);
 	RELEASE(maskedXXB.pxBuf,dderrval);
 	RELEASE(normalXXB.pxBuf,dderrval);

 	RELEASE(nzbufXXB.pxBuf,dderrval);
 	RELEASE(fontXXB.pxBuf,dderrval);

	RELEASE(lineXB.pxBuf,dderrval);
	RELEASE(pointXB.pxBuf,dderrval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushLandscapeBuffers
//Author		Dallas  
//Date			Wed 1 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::FlushLandscapeBuffers(struct _DirectDraw* pDirectD)
{
	//make sure that all landscape execute buffers are
	//empty
	FlushLandDraw(pDirectD,nearlndXB);
	FlushDitherDraw(pDirectD,ditherlndXB);
	FlushPTDraw(pDirectD,landXB);
	FlushPTDraw(pDirectD,clandXB);
	FlushLandDraw(pDirectD,cnearlndXB);
	FlushDitherDraw(pDirectD,cditherlndXB);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DumpXBuffer
//Author		Paul.   
//Date			Thu 2 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::DumpXBuffer(XBuf& xb)
{
	FILE* debF=fopen("xdump.txt","wt");

	HRESULT dderrval;

	dderrval=xb.pxBuf->Lock(&xb.xbDesc);
	DIRECT3DERROR(dderrval);

	D3DTLVERTEX* ptlvert=(D3DTLVERTEX*)xb.xbDesc.lpData;
	void* pinst=(void*)(ULong(ptlvert)+xb._inst_start);

	//dump vertices first

	fprintf(debF,"Execute Buffer Dump\n===================\n");

	for (int i=0;i<xb.vertCount;i++)
	{
		fprintf(debF,"D3DTLVERTEX %d\n",i);
		fprintf(debF,"sx:\t\t%f\n",ptlvert->sx);
		fprintf(debF,"sy:\t\t%f\n",ptlvert->sy);
		fprintf(debF,"sz:\t\t%f\n",ptlvert->sz);
		fprintf(debF,"rhw:\t\t%f\n",ptlvert->rhw);
		fprintf(debF,"color:\t\t0x%8x\n",ULong(ptlvert->color));
		fprintf(debF,"specular:\t0x%8x\n",ULong(ptlvert->specular));
		fprintf(debF,"tu:\t\t%f\n",ptlvert->tu);
		fprintf(debF,"tv:\t\t%f\n",ptlvert->tv);
		ptlvert++;
	}

	fprintf(debF,"Instruction data\n================\n");

	LPD3DINSTRUCTION pi=LPD3DINSTRUCTION(pinst);

	bool bDone=false;
	bool bError=false;

	while (!bDone && !bError)
	{
		switch (pi->bOpcode)
		{
		case D3DOP_POINT:
		{
			int i=pi->wCount;
			pi++;
			fprintf(debF,"POINT (x%d)\n",i);
			LPD3DPOINT pp=LPD3DPOINT(pi);
			for (int j=0;j<i;j++)
			{
				fprintf(debF,"(%d) wCount: %d wFirst: %d\n",j,pp->wCount,pp->wFirst);
				pp++;
			}
			pi=LPD3DINSTRUCTION(pp);
		}
		break;
		case D3DOP_LINE:
		{
			int i=pi->wCount;
			pi++;
			fprintf(debF,"LINE (x%d)\n",i);
			LPD3DLINE pl=LPD3DLINE(pi);
			for (int j=0;j<i;j++)
			{
				fprintf(debF,"(%d) v1: %d v2 %d\n",j,pl->v1,pl->v2);
				pl++;
			}
			pi=LPD3DINSTRUCTION(pl);
		}
		break;
		case D3DOP_TRIANGLE:
		{
			int i=pi->wCount;
			pi++;
			fprintf(debF,"TRIANGLE (x%d)\n",i);
			LPD3DTRIANGLE pt=LPD3DTRIANGLE(pi);
			for (int j=0;j<i;j++)
			{
				fprintf(debF,"(%d) v1: %d v2: %d v3: %d wFlags: %4x\n",
					j,pt->v1,pt->v2,pt->v3,pt->wFlags);
				pt++;
			}
			pi=LPD3DINSTRUCTION(pt);
		}
		break;
		case D3DOP_MATRIXLOAD:
		{
			fprintf(debF,"MATRIXLOAD (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		case D3DOP_MATRIXMULTIPLY:
		{
			fprintf(debF,"MATRIXMULTIPLY (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		case D3DOP_STATETRANSFORM:
		{
			fprintf(debF,"STATETRANSFORM (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		case D3DOP_STATELIGHT:
		{
			fprintf(debF,"STATELIGHT (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		case D3DOP_STATERENDER:
		{
			fprintf(debF,"STATERENDER (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		case D3DOP_PROCESSVERTICES:
		{
			fprintf(debF,"PROCESSVERTICES (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			LPD3DPROCESSVERTICES vdp=(LPD3DPROCESSVERTICES)pi;
			fprintf(debF,"\twFlags %d wStart %d wDest %d dwCount %d\n",
				vdp->wStart,vdp->wDest,vdp->dwCount);
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		case D3DOP_TEXTURELOAD:
		{
			fprintf(debF,"TEXTURELOAD (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		case D3DOP_EXIT:
			fprintf(debF,"EXIT (x%d)\n",pi->wCount);
			bDone=true;
		break;
		case D3DOP_BRANCHFORWARD:
		{
			fprintf(debF,"BRANCHFORWARD (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		case D3DOP_SPAN:
		{
			fprintf(debF,"SPAN (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		case D3DOP_SETSTATUS:
		{
			fprintf(debF,"SETSTATUS (x%d)\n",pi->wCount);
			ULong dataLen=pi->wCount*pi->bSize;
			pi++;
			pi=LPD3DINSTRUCTION(ULong(pi)+dataLen);
		}
		break;
		default:
			fprintf(debF,"duff instruction data\n");
			bError=true;
		break;
		}

		if (ULong(pi)>ULong(pinst)+xb._inst_len) bError=true;
	}

	if (bError)
		fprintf(debF,"*** ERROR *** execute buffer not terminated correctly\n");

	fprintf(debF,"\nBuffer Stats\n============\n");

	float pcnt=100.0f*float(xb.vertCount)/float(xb._max_verts);

	fprintf(debF,"Vertex space usage: %f\n",pcnt);

	pcnt=100.0f*float(ULong(pi)-ULong(pinst))/float(xb._inst_len);

	fprintf(debF,"Instruction space usage: %f\n",pcnt);

	dderrval=xb.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);

	fclose(debF);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetBufferUse
//Author		Paul    
//Date			Mon 6 Jul 1998
//------------------------------------------------------------------------------
inline void direct_3d::ResetBufferUse(BufferUse& bufUse)
{
	bufUse.count=-1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RecordTextureUse
//Author		Paul    
//Date			Mon 6 Jul 1998
//				(returns false if the texture couldn't be recorded)
//------------------------------------------------------------------------------
bool direct_3d::RecordTextureUse(	ImageMapDescPtr pmap,
									UWord*& pOffset,
									BufferUse& bufUse)
{
	//now, check whether the texture has already been recorded

	MapUse* pmapUse=bufUse.mapUse;

	for (int i=0;i<=bufUse.count;i++,pmapUse++)
	{
		if (pmapUse->pmap==pmap) break;
	}
	
	if (i>bufUse.count)	//not recorded this one yet!
	{
		if (bufUse.count==MAX_RECORD_RECORDS-1) return false;
 	 	bufUse.count++;
		pmapUse->count=-1;
		pmapUse->textureQuality=textureQuality;
		pmapUse->flags=(fMipMapEnabled)?MUF_NULL:MUF_NOMIP;
		if (refreshTexture) pmapUse->flags|=MUF_REFRESH;
		pmapUse->pmap=pmap;
	}

	//record the execute buffer offset for this use

	if (pmapUse->count==MAX_MAP_RECORDS-1) return false;

	pmapUse->count++;

	pOffset=pmapUse->offset+pmapUse->count;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WipeLastTexture
//Author		Paul    
//Date			Mon 6 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::WipeLastTexture(ImageMapDescPtr pmap,BufferUse& bufUse)
{
	MapUse* pmapUse=bufUse.mapUse;

	for (int i=0;i<=bufUse.count;i++,pmapUse++)
	{
		if (pmapUse->pmap==pmap)
		{
			pmapUse->count--;
		 	return;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RegisterTextureUse
//Author		Paul    
//Date			Mon 6 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::RegisterTextureUse(	struct _DirectDraw* pDirectD,
									BufferUse& bufUse,
									void* pBase)
{
	//Make sure that all recorded textures are in video RAM

	SWord bupTextureQuality=textureQuality;
	SWord bupMip=Save_Data.filtering;

	MapUse* pmapUse=bufUse.mapUse;

	for (int i=0;i<=bufUse.count;i++,pmapUse++)
	{
		textureQuality=pmapUse->textureQuality;
		Save_Data.filtering=(pmapUse->flags&MUF_NOMIP)!=0?1:bupMip;
		bool fRefresh=pmapUse->flags&MUF_REFRESH?true:false;

		VIDRAMTEXTURE* pvrt=
		CreateTexture(pmapUse->pmap,pDirectD,fRefresh);

		D3DTEXTUREHANDLE hTexture;

		if (pvrt)
			hTexture=pvrt->d3dhTexture;
		else
		{
			hTexture=NULL;
			decreaseTextureQuality=true;
		}

		for (int j=0;j<=pmapUse->count;j++)
		{
		 	void* pinst=(void*)(ULong(pBase)+ULong(pmapUse->offset[j]));
	  		*(DWORD*)pinst=DWORD(hTexture);
		}
	}
	textureQuality=bupTextureQuality;
	Save_Data.filtering=bupMip;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTextPoly
//Author		Paul.   
//Date			Tue 30 Jun 1998
//
//Description	Adds a plain (unmasked & not transparent) poly to the
//				current execute buffer
//
//------------------------------------------------------------------------------
void direct_3d::AddTexturedPoly(DirectD* pDirectD,LPPOLYTYPE lpPolyType)
{
	ULong interpFlag;

	interpFlag=	IF3D_TEXTURE+
				((globalSpecular)?IF3D_SPECULAR:0)+
				((globalLighting)?IF3D_COLOR:0);

	//check which type of texture we're looking at here...

	bool isMasked,hasAlpha,alphaOverride,fakeFog;

	ImageMapDescPtr pmap=lpPolyType->lpImageMap;

	D3DVALUE fWidth=D3DVALUE(pmap->w)*65536.;
	D3DVALUE fHeight=D3DVALUE(pmap->h)*65536.;

	alphaOverride=bool(globalAlphaValue!=AmbientALPHA);

	fakeFog=lpPolyType->ptType==POLYTYPE::PT_FakeFog?true:false;

	if (pmap->alpha)
	{
		hasAlpha=isMasked=true;
	}
	else
	{
	 	hasAlpha=false;
		isMasked=(pmap->isMasked)?true:false;
	}

	XXBuf* pxxb;

	if (hasAlpha||isTranspFade||alphaOverride||(isMasked&&!maskedTexture.bPalettized))
	{
		if (Save_Data.detail_3d[DETAIL3D_TRANSSMOKE])
			pxxb=&transpXXB;	//for polys with transparency
		else
			pxxb=&maskedXXB;	//for polys with masking
	}
	else if (isMasked)	
		pxxb=&maskedXXB;	//for polys with masking
	else				
		pxxb=&normalXXB;	//for normal textured polygons

	XXBuf& xxb=*pxxb;

	//get an initial estimate of the number of points and polys
	ULong pntCnt=lpPolyType->points;

 	ULong pntEstimate=(pntCnt+pntCnt);
	ULong trisEstimate=pntEstimate-2;

	UWord* pOffset;

	bool flushedDraw=false;

	//flush the current buffer contents if max no of
	//vertices/buffer will be exceeded

	if (xxb.vertCount+pntEstimate>xxb._max_verts)
	{
		FlushPTDraw(pDirectD,xxb);
		flushedDraw=true;
	}

	//flush the current buffer contents if max no of
	//faces/buffer will be exceeded

	if (!flushedDraw)
	{
		//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);

		if (totalSize>(xxb._inst_len-xxb.instOffset))
		{
			FlushPTDraw(pDirectD,xxb);
			flushedDraw=true;
		}
	}

	//flush the current buffer contents if texture record space is exceeded

	if (!flushedDraw)
	{
		if (!RecordTextureUse(pmap,pOffset,xxb.bufUse))
		{
			FlushPTDraw(pDirectD,xxb);
			RecordTextureUse(pmap,pOffset,xxb.bufUse);
		}
	}
	else RecordTextureUse(pmap,pOffset,xxb.bufUse);

	//there is definately enough room in the current execute buffer
	//to add the new polygon if required

	ULong vBase=xxb.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)xxb.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb.instOffset);
	void* pibase=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb._inst_start);
	void* pistart=pinst;

	//get a pointer to the current input poly definition
	vertex** ppv=lpPolyType->lplpVertices;

	//initialise clipping flags...
	UWord orClip,andClip;
	orClip=CF3D_NULL;
	andClip=CF3D_ALL;

	R3DTLVERTEX tstore[64];
	R3DTLVERTEX* ptstore=tstore;
	R3DTLVERTEX* polydef[64];
	R3DTLVERTEX** pptlv=polydef;

	//this routine will not get called unless the polygon
	//is at least partly visible so prepare to clip if
	//needed

	R3DCOLOR shadePolyColor;
	R3DCOLOR specularPolyColor;

	for (int i=0;i<pntCnt;i++)
	{
		vertex* pv=*ppv++;
		UWord cf=pv->clipFlags;
		orClip|=cf;
		andClip&=cf;

		if (fakeFog || isTranspFade) 
		{
			SWord cval=pv->intensity>>12;
			cval=cval<0?0:cval>255?255:cval;
			shadePolyColor.r=vShadeRed;
			shadePolyColor.g=vShadeGreen;
			shadePolyColor.b=vShadeBlue;
			shadePolyColor.a=cval;
		}
		else if (alphaOverride)
		{
			shadePolyColor.r=vShadeRed;
			shadePolyColor.g=vShadeGreen;
			shadePolyColor.b=vShadeBlue;
			shadePolyColor.a=globalAlphaValue;
		}
		else if (isLightShaded)
		{
			SWord cval=pv->intensity>>12;
			cval=(cval<0x00)?0x00:(cval>0xFF)?0xFF:cval;
			shadePolyColor.r=(vShadeRed*cval)>>8;
			shadePolyColor.g=(vShadeGreen*cval)>>8;
			shadePolyColor.b=(vShadeBlue*cval)>>8;
			shadePolyColor.a=AmbientALPHA;
		}
		else *(D3DCOLOR*)&shadePolyColor=AmbientLight;	//D3DCOLOR(0xFFFFFFFF);

		if (globalSpecular && pv->specular!=-1)
		{
			SWord cval=pv->specular>>12;
			cval=(cval<0x00)?0x00:(cval>0xFF)?0xFF:cval;
			specularPolyColor.r=(vShadeRed*cval)>>8;
			specularPolyColor.g=(vShadeGreen*cval)>>8;
			specularPolyColor.b=(vShadeBlue*cval)>>8;
		}
		else *(ULong*)&specularPolyColor=specularNULL;

		if (cf==CF3D_NULL)
		{
			//if the point is in the view cone then put
			//it straight into the current execute buffer

			ptlvert->sx=D3DVALUE(pv->bx.f);
			ptlvert->sy=D3DVALUE(pv->by.f);
			ptlvert->sz=D3DVALUE(pv->bz.f);
			ptlvert->clipFlags=cf+interpFlag;
			ptlvert->color=*(D3DCOLOR*)&shadePolyColor;
			ptlvert->specular=*(D3DCOLOR*)&specularPolyColor;
			ptlvert->tu=D3DVALUE(pv->ix.f);
			ptlvert->tv=D3DVALUE(pv->iy.f);
			*pptlv++=ptlvert;
			ptlvert++;
		}
		else
		{
			//if the point is outside the current view cone
			//then add it to a temporary buffer

			ptstore->sx=D3DVALUE(pv->bx.f);
			ptstore->sy=D3DVALUE(pv->by.f);
			ptstore->sz=D3DVALUE(pv->bz.f);
			ptstore->clipFlags=cf+interpFlag;
			ptstore->color=*(D3DCOLOR*)&shadePolyColor;
			ptstore->specular=*(D3DCOLOR*)&specularPolyColor;
			ptstore->tu=D3DVALUE(pv->ix.f);
			ptstore->tv=D3DVALUE(pv->iy.f);
			*pptlv++=ptstore;
			ptstore++;
		}
	}
	//just on the off chance that something has
	//gone wrong (Not that it ever does!) check
	//the state of the clip flags and quit if
	//we need to

	if (andClip!=CF3D_NULL)
	{
		//ABORT NOW!!
		WipeLastTexture(pmap,xxb.bufUse);
		return;
	}

	if (orClip!=CF3D_NULL)
	{
	 	//this poly needs to be clipped
		GenericPolyClip(pntCnt,polydef,ptlvert,ptstore);
		
		//check that there is still something to draw after
		//the clipping has been done

		if (pntCnt<3)
		{
			//ABORT NOW!!
			WipeLastTexture(pmap,xxb.bufUse);
			return;
		}
	}

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	for (i=0;i<pntCnt;i++)
	{
		if (!fakeFog)
			((R3DCOLOR*)&(ptlvert->specular))->a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		else 
		{
			((R3DCOLOR*)&(ptlvert->specular))->a=((R3DCOLOR*)&(ptlvert->color))->a;
			((R3DCOLOR*)&(ptlvert->color))->a=0xFF;
		}
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);
		ptlvert->tu/=fWidth;
		ptlvert->tv/=fHeight;
		ptlvert++;
	}

	//record location to store the texture handle for later
	OP_STATE_RENDER(1,pinst);
    void* poff=(void*)(ULong(pinst)+4);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
	*pOffset=UWord(ULong(poff)-ULong(pibase));

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);
	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	ULong triCnt=pntCnt-2;

	OP_TRIANGLE_LIST(triCnt,pinst);

	//first one first
	i=0;
	int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);

	triCnt--;

	((D3DTRIANGLE*)pinst)->v1=v1;
	((D3DTRIANGLE*)pinst)->v2=v2;
	((D3DTRIANGLE*)pinst)->v3=v3;
	((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
	pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

	while (triCnt--)
	{
		v2=v3;
		v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
	}

	xxb.vertCount+=pntCnt;
	xxb.instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderPolyCallback
//Author		Paul.   
//Date			Tue 15 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::RenderPolyCallback(DirectD* pDirectD,LPPOLYTYPE pPoly)
{
	if (PolySplit(pPoly))
	{
		SaveClipFlags(pPoly);
		const Float BIT=.01;
		Float save;
		save=viewdata.D;
		viewdata.D=fZBufScaleSwitchRange+BIT;
		UpdateClipFlagsFrontChanged(pPoly);
		RenderPolyCallback2(pDirectD,pPoly);					//render far poly section
		RestoreClipFlags(pPoly);
		viewdata.D=save;
		save=viewdata.F;
		viewdata.F=fZBufScaleSwitchRange;
		UpdateClipFlagsBackChanged(pPoly);
		RenderPolyCallback2(pDirectD,pPoly); //render near poly section
		viewdata.F=save;
	}
	else RenderPolyCallback2(pDirectD,pPoly);
}

void direct_3d::RenderPolyCallback2(DirectD* pDirectD,LPPOLYTYPE pPoly)
{
	//add all poly types to the same buffer

	XXBuf& xb=nzbufXXB;

	//first, test to see if this poly is the same type as the last...

	PTYPE thisType=T_NONE;
	bool alphaOverride=bool(globalAlphaValue!=AmbientALPHA);

	if (pPoly->ptType==POLYTYPE::PT_PlainColour ||
		pPoly->ptType==POLYTYPE::PT_GColour)
		thisType=T_PLAIN;
	else
	{
		//need to check the texture to be sure of this polygon type

		ImageMapDescPtr pmap=pPoly->lpImageMap;

		bool isMasked,hasAlpha;

		if (pmap->alpha)
			hasAlpha=isMasked=true;
		else
		{
			hasAlpha=false;
			isMasked=bool(pmap->isMasked);
		}
		if (hasAlpha||isTranspFade||alphaOverride)	thisType=T_TRANSP;
		else if (isMasked)							thisType=T_MASKED;
		else										thisType=T_TEXT;
	}

	bool flushed=false;

	ULong pntEstimate=pPoly->points<<2;
	ULong triEstimate=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
					sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
					(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*(pntEstimate-2)+
					sizeof(D3DINSTRUCTION);
	
	if (xb.vertCount+pntEstimate>xb._max_verts||triEstimate>(xb._inst_len-xb.instOffset))
	{
		FlushNZDraw(pDirectD,xb);
		flushed=true;
	}

	UWord* textureOffset=NULL;

	if (thisType==T_TEXT || thisType==T_MASKED || thisType==T_TRANSP)
	{
		if (!RecordTextureUse(pPoly->lpImageMap,textureOffset,xb.bufUse))
		{
			FlushNZDraw(pDirectD,xb);
			RecordTextureUse(pPoly->lpImageMap,textureOffset,xb.bufUse);
			flushed=true;
		}
	}

	if (flushed || thisType!=lastPolyType)
	{
		WriteStateChanged(pDirectD,xb,thisType,lastPolyType);
		lastPolyType=thisType;
	}

	switch (lastPolyType)
	{
		case T_PLAIN:
			AddPlainPolyNZ(pPoly,xb);
			break;
		case T_TEXT:
		case T_MASKED:
		case T_TRANSP:
			AddTexturedPolyNZ(pPoly,xb,textureOffset,alphaOverride);
			break;
		default:
			break;
	}
}

UWord backupClipFlags[512];

void direct_3d::SaveClipFlags(LPPOLYTYPE pPoly)
{
	vertex **ppv=pPoly->lplpVertices,*pv;
	for (int i=pPoly->points-1;i>=0;i--)
	{
		pv=*ppv++;
		backupClipFlags[i]=pv->clipFlags;
	}
}

void direct_3d::RestoreClipFlags(LPPOLYTYPE pPoly)
{
	vertex **ppv=pPoly->lplpVertices,*pv;
	for (int i=pPoly->points-1;i>=0;i--)
	{
		pv=*ppv++;
		pv->clipFlags=backupClipFlags[i];
	}
}

void direct_3d::UpdateClipFlagsFrontChanged(LPPOLYTYPE pPoly)
{
	vertex **ppv=pPoly->lplpVertices,*pv;
	for (int i=pPoly->points-1;i>=0;i--)
	{
		pv=*ppv++;
		if (pv->bz.f<viewdata.D) pv->clipFlags|=CF3D_BEHINDNEARZ;
		else					 pv->clipFlags&=~CF3D_BEHINDNEARZ;
	}
}

void direct_3d::UpdateClipFlagsBackChanged(LPPOLYTYPE pPoly)
{
	vertex **ppv=pPoly->lplpVertices,*pv;
	for (int i=pPoly->points-1;i>=0;i--)
	{
		pv=*ppv++;
		if (pv->bz.f>viewdata.F) pv->clipFlags|=CF3D_PASTFARZ;
		else					 pv->clipFlags&=~CF3D_PASTFARZ;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddNZPoly
//Author		Paul.   
//Date			Wed 28 Oct 1998
//------------------------------------------------------------------------------
void direct_3d::AddPoly(DirectD* pDirectD,LPPOLYTYPE pPoly)
{
	if (!PolyCross(pPoly)) return;

	bool fDoSplit=true;
	if (globalAlphaValue!=AmbientALPHA)	fDoSplit=false;
	if (pPoly->ptType!=POLYTYPE::PT_PlainColour &&
		pPoly->ptType!=POLYTYPE::PT_GColour &&
		(pPoly->lpImageMap->alpha || pPoly->lpImageMap->isMasked))
		fDoSplit=false;

	if (fDoSplit && PolySplit(pPoly))
	{
		SaveClipFlags(pPoly);
		const Float BIT=.01;
		Float save;
		save=viewdata.D;
		viewdata.D=fZBufScaleSwitchRange+BIT;
		UpdateClipFlagsFrontChanged(pPoly);
		AddPoly2(pDirectD,pPoly);					//render far poly section
		RestoreClipFlags(pPoly);
		viewdata.D=save;
		save=viewdata.F;
		viewdata.F=fZBufScaleSwitchRange;
		UpdateClipFlagsBackChanged(pPoly);
		AddPoly2(pDirectD,pPoly); //render near poly section
		viewdata.F=save;
	}
	else AddPoly2(pDirectD,pPoly);
}

void direct_3d::AddPoly2(DirectD* pDirectD,LPPOLYTYPE pPoly)
{
	vShadeRed=vNormalRed;
	vShadeGreen=vNormalGreen;
	vShadeBlue=vNormalBlue;
	AmbientLight=RGBA_MAKE(vShadeRed,vShadeGreen,vShadeBlue,0xFF);

	PTYPE thisType=T_NONE;

	bool alphaOverride=bool(globalAlphaValue!=AmbientALPHA);

	if (pPoly->ptType==POLYTYPE::PT_PlainColour||pPoly->ptType==POLYTYPE::PT_GColour)
		thisType=T_PLAIN;
	else
	{
		//need to check the texture to be sure of this polygon type

		ImageMapDescPtr pmap=pPoly->lpImageMap;

		if (pmap->paletteindex!=0)
		{
			vShadeRed=vEffectsRed;
			vShadeGreen=vEffectsGreen;
			vShadeBlue=vEffectsBlue;
			AmbientLight=RGBA_MAKE(vShadeRed,vShadeGreen,vShadeBlue,0xFF);
		}

		bool isMasked,hasAlpha;

		if (pmap->alpha)
			hasAlpha=isMasked=true;
		else
		{
			hasAlpha=false;
			isMasked=bool(pmap->isMasked);
		}

		if (hasAlpha||isTranspFade||alphaOverride)	thisType=T_TRANSP;
		else if (isMasked)							thisType=T_MASKED;
		else										thisType=T_TEXT;
	}

	bool fIsHorizontal;

	if (fEdgeTestActive && EdgeOnTest(pPoly,fIsHorizontal))
	{
		//Aswell not Instead...
		AddLineInstead(pDirectD,pPoly,fIsHorizontal);
	}

	if (currZWriteState==TRUE)
	{
		switch (pPoly->ptType)
		{
			case POLYTYPE::PT_PlainColour:
				AddPlainPoly(pDirectD,pPoly);
				break;
			case POLYTYPE::PT_MaskedImagem:
			case POLYTYPE::PT_PlainImagem:
			case POLYTYPE::PT_FakeFog:
				if (thisType!=T_TEXT)
					pPolyTree->AddPoly(pPoly);
				else
					AddTexturedPoly(pDirectD,pPoly);
				break;
			case POLYTYPE::PT_GColour:
				AddGouraudPoly(pDirectD,pPoly);
				break;
			default:
				break;
		}
		return;
	}

	//add all poly types to the same buffer

	XXBuf& xb=nzbufXXB;

	bool flushed=false;

	ULong pntEstimate=pPoly->points<<2;
	ULong triEstimate=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
					sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
					(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*(pntEstimate-2)+
					sizeof(D3DINSTRUCTION);
	
	if (xb.vertCount+pntEstimate>xb._max_verts||triEstimate>(xb._inst_len-xb.instOffset))
	{
		FlushNZDraw(pDirectD,xb);
		flushed=true;
	}

	UWord* textureOffset=NULL;

	if (thisType==T_TEXT || thisType==T_MASKED || thisType==T_TRANSP)
	{
		if (!RecordTextureUse(pPoly->lpImageMap,textureOffset,xb.bufUse))
		{
			FlushNZDraw(pDirectD,xb);
			RecordTextureUse(pPoly->lpImageMap,textureOffset,xb.bufUse);
			flushed=true;
		}
	}

	//Test to see if this poly is the same type as the last...

	if (flushed || thisType!=lastPolyType)
	{
		WriteStateChanged(pDirectD,xb,thisType,lastPolyType);
		lastPolyType=thisType;
	}

	switch (lastPolyType)
	{
		case T_PLAIN:
			AddPlainPolyNZ(pPoly,xb);
			break;
		case T_TEXT:
		case T_MASKED:
		case T_TRANSP:
			AddTexturedPolyNZ(pPoly,xb,textureOffset,alphaOverride);
			break;
		default:
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushNZDraw
//Author		Paul.   
//Date			Tue 24 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::FlushNZDraw(DirectD* pDirectD,struct XXBuf& xb)
{
	//flush all other buffers first!

	FlushPTDraw(pDirectD,normalXXB);
	FlushPCDraw(pDirectD,plaincXB);
//	if (fEdgeTestActive)
//		FlushPLDraw(pDirectD,lineXB);
	FlushPPDraw(pDirectD,pointXB);
	FlushPTDraw(pDirectD,maskedXXB);
	FlushPTDraw(pDirectD,transpXXB);
	FlushPTDraw(pDirectD,fontXXB);

	HRESULT dderrval;

	//add op-exit to the end of the buffer

	RegisterTextureUse(	pDirectD,
						xb.bufUse,
						(void*)(ULong(xb.xbDesc.lpData)+xb._inst_start));

	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pistart=pinst;

	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	OP_EXIT(pinst);

	dderrval=xb.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	xb.bLocked=false;

	xb.instOffset+=ULong(pinst)-ULong(pistart);

	assert(xb._inst_len>=(ULong(xb.instOffset)-xb._inst_start)&&"Execute buffer o'flow");

	if (xb.vertCount>0)
	{
		const DWORD dwStatus=
		D3DSTATUS_CLIPUNIONALL|D3DSTATUS_CLIPINTERSECTIONALL|D3DSTATUS_ZNOTVISIBLE;

		//execute the current execute buffer
		D3DEXECUTEDATA xData;
		ZeroMem(&xData,sizeof(D3DEXECUTEDATA));
		xData.dwSize=sizeof(D3DEXECUTEDATA);
		xData.dwVertexCount=xb.vertCount;
		xData.dwInstructionOffset=xb._inst_start;
		xData.dwInstructionLength=ULong(xb.instOffset)-xb._inst_start;
		xData.dsStatus.dwFlags=D3DSETSTATUS_ALL;
		xData.dsStatus.dwStatus=dwStatus;
		xData.dsStatus.drExtent.x2=0;
		xData.dsStatus.drExtent.y2=0;
		xData.dsStatus.drExtent.x1=winWidth;
		xData.dsStatus.drExtent.y1=winHeight;
		dderrval=xb.pxBuf->SetExecuteData(&xData);
		DIRECT3DERROR(dderrval);
		dderrval=lpD3DDevice->Execute(xb.pxBuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
		DIRECT3DERROR(dderrval);
	}
	//reset for the next set of poly data
	xb.vertCount=0;
	xb.instOffset=xb._inst_start;

	//fill in initial state changes
	if (&xb==&transpXXB)
	{
		SetInitialRenderStatesTransp(&xb);
	}
	else if (&xb==&maskedXXB)
	{
		SetInitialRenderStatesMasked(&xb);
	}
	else
	{
		SetInitialRenderStatesTextured(&xb);
	}

	//clear texture usage records
	ResetBufferUse(xb.bufUse);

	//Flag video RAM textures as available for re-use
	for (int j=0;j<NumVidTextures;vidramtextures[j++].bInUse=0);

	lastPolyType=T_NONE;

	if (fEdgeTestActive)
		FlushPLDraw(pDirectD,lineXB);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPlainPolyNZ
//Author		Paul.   
//Date			Tue 24 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::AddPlainPolyNZ(LPPOLYTYPE pPoly,XXBuf& xb)
{
	ULong pntCnt=pPoly->points;
	ULong vBase=xb.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)xb.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pistart=pinst;

	//get a pointer to the current input poly definition
	vertex** ppv=pPoly->lplpVertices;

	//initialise clipping flags...
	UWord orClip,andClip;
	orClip=CF3D_NULL;
	andClip=CF3D_ALL;

	R3DTLVERTEX tstore[64];
	R3DTLVERTEX* ptstore=tstore;
	R3DTLVERTEX* polydef[64];
	R3DTLVERTEX** pptlv=polydef;

	//this routine will not get called unless the polygon
	//is at least partly visible so prepare to clip if
	//needed

	R3DCOLOR basePolyColor;
	R3DCOLOR shadePolyColor;
	R3DCOLOR& paletteEntry=*(R3DCOLOR*)&palette[pPoly->colour].dcColorVal;

	SLong rscale,gscale,bscale;

	vertex* pv=*ppv;

	bool fIsGouraud=pPoly->ptType==POLYTYPE::PT_GColour?true:false;
	
	ULong interpFlag=fIsGouraud?IF3D_COLOR:IF3D_NULL;
	
	basePolyColor.r=((SLong(paletteEntry.r)*vShadeRed)>>8);
	basePolyColor.g=((SLong(paletteEntry.g)*vShadeGreen)>>8);
	basePolyColor.b=((SLong(paletteEntry.b)*vShadeBlue)>>8);
	basePolyColor.a=AmbientALPHA;

	if (isLightShaded && !fIsGouraud)
	{
		SWord cval=pv->intensity>>12;
		cval=(cval<0x00)?0x00:(cval>0xFF)?0xFF:cval;
		shadePolyColor.r=(basePolyColor.r*cval)>>8;
		shadePolyColor.g=(basePolyColor.g*cval)>>8;
		shadePolyColor.b=(basePolyColor.b*cval)>>8;
		shadePolyColor.a=AmbientALPHA;
//		rscale=SLong(paletteEntry.r)-SLong(basePolyColor.r);
//		gscale=SLong(paletteEntry.g)-SLong(basePolyColor.g);
//		bscale=SLong(paletteEntry.b)-SLong(basePolyColor.b);
//		SLong darkness=(256<<12)-pv->intensity;
//		darkness=darkness<0?0:darkness>((256<<12)-1)?((256<<12)-1):darkness;
//		shadePolyColor.r=UByte(SLong(basePolyColor.r)+((rscale*darkness)>>20));
//		shadePolyColor.g=UByte(SLong(basePolyColor.g)+((gscale*darkness)>>20));
//		shadePolyColor.b=UByte(SLong(basePolyColor.b)+((bscale*darkness)>>20));
	}
	else *(D3DCOLOR*)&shadePolyColor=*(D3DCOLOR*)&basePolyColor;	//paletteEntry;

	shadePolyColor.a=AmbientALPHA;

	for (int i=0;i<pntCnt;i++)
	{
		pv=*ppv++;
		UWord cf=pv->clipFlags;
		orClip|=cf;
		andClip&=cf;

		if (cf==CF3D_NULL)
		{
			//if the point is in the view cone then put
			//it straight into the current execute buffer

			ptlvert->sx=D3DVALUE(pv->bx.f);
			ptlvert->sy=D3DVALUE(pv->by.f);
			ptlvert->sz=D3DVALUE(pv->bz.f);
			ptlvert->clipFlags=cf+interpFlag;

			if (!fIsGouraud)	ptlvert->color=*(D3DCOLOR*)&shadePolyColor;
			else
			{
				ptlvert->col.r=pv->col.r;
				ptlvert->col.g=pv->col.g;
				ptlvert->col.b=pv->col.b;
				ptlvert->col.a=AmbientALPHA;
			}

			*pptlv++=ptlvert;
			ptlvert++;
		}
		else
		{
			//if the point is outside the current view cone
			//then add it to a temporary buffer

			ptstore->sx=D3DVALUE(pv->bx.f);
			ptstore->sy=D3DVALUE(pv->by.f);
			ptstore->sz=D3DVALUE(pv->bz.f);
			ptstore->clipFlags=cf+interpFlag;

			if (!fIsGouraud)	ptstore->color=*(D3DCOLOR*)&shadePolyColor;
			else
			{
				ptstore->col.r=pv->col.r;
				ptstore->col.g=pv->col.g;
				ptstore->col.b=pv->col.b;
				ptstore->col.a=AmbientALPHA;
			}

			*pptlv++=ptstore;
			ptstore++;
		}
	}
	//just on the off chance that something has
	//gone wrong (Not that it ever does!) check
	//the state of the clip flags and quit if
	//we need to

	if (andClip!=CF3D_NULL)
	{
		//ABORT NOW!!
		return;
	}

	if (orClip!=CF3D_NULL)
	{
	 	//this poly needs to be clipped
		GenericPolyClip(pntCnt,polydef,ptlvert,ptstore);
		
		//check that there is still something to draw after
		//the clipping has been done

		if (pntCnt<3)
		{
			//ABORT NOW!!
			return;
		}
	}

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	*(D3DCOLOR*)&shadePolyColor=specularNULL;

	for (i=0;i<pntCnt;i++)
	{
		shadePolyColor.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		ptlvert->specular=*(D3DCOLOR*)&shadePolyColor;
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx);
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy);
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);
		ptlvert++;
	}

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);
	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	ULong triCnt=pntCnt-2;

	OP_TRIANGLE_LIST(triCnt,pinst);

	//first one first
	i=0;
	int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);

	triCnt--;

	((D3DTRIANGLE*)pinst)->v1=v1;
	((D3DTRIANGLE*)pinst)->v2=v2;
	((D3DTRIANGLE*)pinst)->v3=v3;
	((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
	pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

	while (triCnt--)
	{
		v2=v3;
		v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
	}

	xb.vertCount+=pntCnt;
	xb.instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTexturedPolyNZ
//Author		Paul.   
//Date			Tue 24 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::AddTexturedPolyNZ(LPPOLYTYPE pPoly,XXBuf& xb,UWord* pOffset,bool alphaOverride)
{
	ImageMapDescPtr pmap=pPoly->lpImageMap;
	D3DVALUE fWidth=D3DVALUE(pmap->w)*65536.;
	D3DVALUE fHeight=D3DVALUE(pmap->h)*65536.;

	ULong interpFlag;

	interpFlag=	IF3D_TEXTURE+IF3D_COLOR+
				((globalSpecular)?IF3D_SPECULAR:0);

	ULong pntCnt=pPoly->points;

	bool fakeFog=pPoly->ptType==POLYTYPE::PT_FakeFog?true:false;

	ULong vBase=xb.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)xb.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pibase=(void*)(((UByte*)xb.xbDesc.lpData)+xb._inst_start);
	void* pistart=pinst;

	//get a pointer to the current input poly definition
	vertex** ppv=pPoly->lplpVertices;

	//initialise clipping flags...
	UWord orClip,andClip;
	orClip=CF3D_NULL;
	andClip=CF3D_ALL;

	R3DTLVERTEX tstore[64];
	R3DTLVERTEX* ptstore=tstore;
	R3DTLVERTEX* polydef[64];
	R3DTLVERTEX** pptlv=polydef;

	//this routine will not get called unless the polygon
	//is at least partly visible so prepare to clip if
	//needed

	R3DCOLOR shadePolyColor;
	R3DCOLOR specularPolyColor;

	for (int i=0;i<pntCnt;i++)
	{
		vertex* pv=*ppv++;
		UWord cf=pv->clipFlags;
		orClip|=cf;
		andClip&=cf;

		if (isTranspFade || fakeFog) 
		{
			SWord cval=pv->intensity>>12;
			cval=cval<0?0:cval>255?255:cval;
			shadePolyColor.r=vShadeRed;
			shadePolyColor.g=vShadeGreen;
			shadePolyColor.b=vShadeBlue;
			shadePolyColor.a=cval;
		}
		else if (alphaOverride)
		{
			shadePolyColor.r=vShadeRed;
			shadePolyColor.g=vShadeGreen;
			shadePolyColor.b=vShadeBlue;
			shadePolyColor.a=globalAlphaValue;
		}
		else if (isLightShaded)
		{
			SWord cval=pv->intensity>>12;
			cval=(cval<0x00)?0x00:(cval>0xFF)?0xFF:cval;
			shadePolyColor.r=(vShadeRed*cval)>>8;
			shadePolyColor.g=(vShadeGreen*cval)>>8;
			shadePolyColor.b=(vShadeBlue*cval)>>8;
			shadePolyColor.a=AmbientALPHA;
		}
		else *(D3DCOLOR*)&shadePolyColor=AmbientLight;	//D3DCOLOR(0xFFFFFFFF);

		if (globalSpecular && pv->specular!=-1)
		{
			SWord cval=pv->specular>>12;
			cval=(cval<0x00)?0x00:(cval>0xFF)?0xFF:cval;
			specularPolyColor.r=(vShadeRed*cval)>>8;
			specularPolyColor.g=(vShadeGreen*cval)>>8;
			specularPolyColor.b=(vShadeBlue*cval)>>8;
		}
		else *(ULong*)&specularPolyColor=specularNULL;

		if (cf==CF3D_NULL)
		{
			//if the point is in the view cone then put
			//it straight into the current execute buffer

			ptlvert->sx=D3DVALUE(pv->bx.f);
			ptlvert->sy=D3DVALUE(pv->by.f);
			ptlvert->sz=D3DVALUE(pv->bz.f);
			ptlvert->clipFlags=cf+interpFlag;
			ptlvert->color=*(D3DCOLOR*)&shadePolyColor;
			ptlvert->specular=*(D3DCOLOR*)&specularPolyColor;
			ptlvert->tu=D3DVALUE(pv->ix.f);
			ptlvert->tv=D3DVALUE(pv->iy.f);
			*pptlv++=ptlvert;
			ptlvert++;
		}
		else
		{
			//if the point is outside the current view cone
			//then add it to a temporary buffer

			ptstore->sx=D3DVALUE(pv->bx.f);
			ptstore->sy=D3DVALUE(pv->by.f);
			ptstore->sz=D3DVALUE(pv->bz.f);
			ptstore->clipFlags=cf+interpFlag;
			ptstore->color=*(D3DCOLOR*)&shadePolyColor;
			ptstore->specular=*(D3DCOLOR*)&specularPolyColor;
			ptstore->tu=D3DVALUE(pv->ix.f);
			ptstore->tv=D3DVALUE(pv->iy.f);
			*pptlv++=ptstore;
			ptstore++;
		}
	}
	//just on the off chance that something has
	//gone wrong (Not that it ever does!) check
	//the state of the clip flags and quit if
	//we need to

	if (andClip!=CF3D_NULL)
	{
		//ABORT NOW!!
		WipeLastTexture(pmap,xb.bufUse);
		return;
	}

	if (orClip!=CF3D_NULL)
	{
	 	//this poly needs to be clipped
		GenericPolyClip(pntCnt,polydef,ptlvert,ptstore);
		
		//check that there is still something to draw after
		//the clipping has been done

		if (pntCnt<3)
		{
			//ABORT NOW!!
			WipeLastTexture(pmap,xb.bufUse);
			return;
		}
	}

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	for (i=0;i<pntCnt;i++)
	{
		if (!fakeFog)
			((R3DCOLOR*)&(ptlvert->specular))->a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		else
		{
			((R3DCOLOR*)&(ptlvert->specular))->a=((R3DCOLOR*)&(ptlvert->color))->a;
			((R3DCOLOR*)&(ptlvert->color))->a=0xFF;
		}
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);
		ptlvert->tu/=fWidth;
		ptlvert->tv/=fHeight;
		ptlvert++;
	}

	//record location to store the texture handle for later
	OP_STATE_RENDER(1,pinst);
    void* poff=(void*)(ULong(pinst)+4);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
	*pOffset=UWord(ULong(poff)-ULong(pibase));

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);
	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	ULong triCnt=pntCnt-2;

	OP_TRIANGLE_LIST(triCnt,pinst);

	//first one first
	i=0;
	int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);

	triCnt--;

	((D3DTRIANGLE*)pinst)->v1=v1;
	((D3DTRIANGLE*)pinst)->v2=v2;
	((D3DTRIANGLE*)pinst)->v3=v3;
	((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
	pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

	while (triCnt--)
	{
		v2=v3;
		v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
	}

	xb.vertCount+=pntCnt;
	xb.instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WriteStateChanged
//Author		Paul.   
//Date			Wed 28 Oct 1998
//------------------------------------------------------------------------------
void direct_3d::WriteStateChanged(	DirectD* pDirectD,
									XXBuf& xb,
									PTYPE thisType,
									PTYPE lastType)
{
	const ULong stateRenderSize=4;
	const ULong stateDataSize=8;

	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pistart=pinst;

	switch (thisType)
	{
		case T_PLAIN:
		{
		ULong stateChangeSize=10*(stateRenderSize+4*stateDataSize);

		if (stateChangeSize>(xb._inst_len-xb.instOffset))
			FlushNZDraw(pDirectD,xb);

		OP_STATE_RENDER(4,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_FOGENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,pinst);
		}
		break;

		case T_TEXT:
		{
		ULong stateChangeSize=10*(stateRenderSize+7*stateDataSize);

		if (stateChangeSize>(xb._inst_len-xb.instOffset))
			FlushNZDraw(pDirectD,xb);

		OP_STATE_RENDER(7,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATE,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
		D3DTEXTUREFILTER tfFilterMAG,tfFilterMIN;
		tfFilterMAG=Driver[CurrDriver].tfFilterMAG;
		tfFilterMIN=Driver[CurrDriver].tfFilterMIN;
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,tfFilterMAG,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,tfFilterMIN,pinst);
		STATE_DATA(D3DRENDERSTATE_FOGENABLE,bGlobalFogFlag,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,pinst);
		}
		break;

		case T_MASKED:
		{
		if (maskedTexture.bPalettized)
		{
			ULong stateChangeSize=10*(stateRenderSize+6*stateDataSize);

			if (stateChangeSize>(xb._inst_len-xb.instOffset))
				FlushNZDraw(pDirectD,xb);

			OP_STATE_RENDER(6,pinst);
			STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATE,pinst);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,D3DFILTER_NEAREST,pinst);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,D3DFILTER_NEAREST,pinst);
			STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
		}
		else
		{
			ULong stateChangeSize=10*(stateRenderSize+8*stateDataSize);

			if (stateChangeSize>(xb._inst_len-xb.instOffset))
				FlushNZDraw(pDirectD,xb);

			OP_STATE_RENDER(8,pinst);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATEALPHA,pinst);
			STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,pinst);
			STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,pinst);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,pinst);
			STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
			D3DTEXTUREFILTER tfFilterMAG,tfFilterMIN;
			tfFilterMAG=Driver[CurrDriver].tfFilterMAG;
			tfFilterMIN=Driver[CurrDriver].tfFilterMIN;
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,tfFilterMAG,pinst);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,tfFilterMIN,pinst);
			STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
		}
		}
		break;

		case T_TRANSP:
		{
		ULong stateChangeSize=10*(stateRenderSize+9*stateDataSize);

		if (stateChangeSize>(xb._inst_len-xb.instOffset))
			FlushNZDraw(pDirectD,xb);

		D3DTEXTUREBLEND	tbBlendMode=Driver[CurrDriver].tbBlendMode;
		OP_STATE_RENDER(9,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,tbBlendMode,pinst);
		STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
		D3DTEXTUREFILTER tfFilterMAG,tfFilterMIN;
		tfFilterMAG=Driver[CurrDriver].tfFilterMAG;
		tfFilterMIN=Driver[CurrDriver].tfFilterMIN;
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,tfFilterMAG,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,tfFilterMIN,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_FOGENABLE,bGlobalFogFlag,pinst);
		}
		break;
	}

	//switch off zbuffering on first use

	if (lastType==T_NONE)
	{
		OP_STATE_RENDER(1,pinst);
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,FALSE,pinst);
	}

	xb.instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestoreZWriteState
//Author		Paul.   
//Date			Tue 24 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::RestoreZWriteState(XBuf* pxb)
{
	void* pinst=(void*)(ULong(pxb->xbDesc.lpData)+pxb->instOffset);
	void* pistart=pinst;
	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	pxb->instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddDebugPoly
//Author		Paul.   
//Date			Thu 23 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::AddDebugPoly(DirectD* pDirectD,LPPOLYTYPE lpPolyType)
{
	//check which type of texture we're looking at here...

	D3DVALUE fWidth=256*65536;
	D3DVALUE fHeight=256*65536;

	ULong hT=vidramlandptr[lpPolyType->hTexture]->d3dhTexture;

	XXBuf* pxxb;

	pxxb=&normalXXB;	//for normal textured polygons

	XXBuf& xxb=*pxxb;

	//get an initial estimate of the number of points and polys
	ULong pntCnt=lpPolyType->points;

 	ULong pntEstimate=(pntCnt+pntCnt);
	ULong trisEstimate=pntEstimate-2;

	UWord* pOffset;

	bool flushedDraw=false;

	//flush the current buffer contents if max no of
	//vertices/buffer will be exceeded

	if (xxb.vertCount+pntEstimate>xxb._max_verts)
	{
		FlushPTDraw(pDirectD,xxb);
		flushedDraw=true;
	}

	//flush the current buffer contents if max no of
	//faces/buffer will be exceeded

	if (!flushedDraw)
	{
		//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);

		if (totalSize>(xxb._inst_len-xxb.instOffset))
		{
			FlushPTDraw(pDirectD,xxb);
			flushedDraw=true;
		}
	}

	//there is definately enough room in the current execute buffer
	//to add the new polygon if required

	ULong vBase=xxb.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)xxb.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb.instOffset);
	void* pibase=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb._inst_start);
	void* pistart=pinst;

	//get a pointer to the current input poly definition
	vertex** ppv=lpPolyType->lplpVertices;

	//initialise clipping flags...
	UWord orClip,andClip;
	orClip=CF3D_NULL;
	andClip=CF3D_ALL;

	R3DTLVERTEX tstore[64];
	R3DTLVERTEX* ptstore=tstore;
	R3DTLVERTEX* polydef[64];
	R3DTLVERTEX** pptlv=polydef;

	//this routine will not get called unless the polygon
	//is at least partly visible so prepare to clip if
	//needed

	R3DCOLOR shadePolyColor;

	for (int i=0;i<pntCnt;i++)
	{
		vertex* pv=*ppv++;
		UWord cf=pv->clipFlags;
		orClip|=cf;
		andClip&=cf;

		if (isLightShaded)
		{
			SWord cval=pv->intensity>>12;
			cval=(cval<0x00)?0x00:(cval>0xFF)?0xFF:cval;
			shadePolyColor.r=
				shadePolyColor.g=
				shadePolyColor.b=cval;
			shadePolyColor.a=AmbientALPHA;
		}
		else *(D3DCOLOR*)&shadePolyColor=AmbientLight;	//D3DCOLOR(0xFFFFFFFF);

		if (cf==CF3D_NULL)
		{
			//if the point is in the view cone then put
			//it straight into the current execute buffer

			ptlvert->sx=D3DVALUE(pv->bx.f);
			ptlvert->sy=D3DVALUE(pv->by.f);
			ptlvert->sz=D3DVALUE(pv->bz.f);
			ptlvert->clipFlags=cf+IF3D_ALL;
			ptlvert->color=*(D3DCOLOR*)&shadePolyColor;
			ptlvert->tu=D3DVALUE(pv->ix.f/fWidth);
			ptlvert->tv=D3DVALUE(pv->iy.f/fHeight);
			*pptlv++=ptlvert;
			ptlvert++;
		}
		else
		{
			//if the point is outside the current view cone
			//then add it to a temporary buffer

			ptstore->sx=D3DVALUE(pv->bx.f);
			ptstore->sy=D3DVALUE(pv->by.f);
			ptstore->sz=D3DVALUE(pv->bz.f);
			ptstore->clipFlags=cf+IF3D_ALL;
			ptstore->color=*(D3DCOLOR*)&shadePolyColor;
			ptstore->tu=D3DVALUE(pv->ix.f/fWidth);
			ptstore->tv=D3DVALUE(pv->iy.f/fHeight);
			*pptlv++=ptstore;
			ptstore++;
		}
	}
	//just on the off chance that something has
	//gone wrong (Not that it ever does!) check
	//the state of the clip flags and quit if
	//we need to

	if (andClip!=CF3D_NULL)
	{
		//ABORT NOW!!
		return;
	}

	if (orClip!=CF3D_NULL)
	{
	 	//this poly needs to be clipped
		GenericPolyClip(pntCnt,polydef,ptlvert,ptstore);
		
		//check that there is still something to draw after
		//the clipping has been done

		if (pntCnt<3)
		{
			//ABORT NOW!!
			return;
		}
	}

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	*(D3DCOLOR*)&shadePolyColor=specularNULL;

	for (i=0;i<pntCnt;i++)
	{
		shadePolyColor.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		ptlvert->specular=*(D3DCOLOR*)&shadePolyColor;
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);
		ptlvert++;
	}

	//record location to store the texture handle for later
	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,hT,pinst);

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);
	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	ULong triCnt=pntCnt-2;

	OP_TRIANGLE_LIST(triCnt,pinst);

	//first one first
	i=0;
	int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);

	triCnt--;

	((D3DTRIANGLE*)pinst)->v1=v1;
	((D3DTRIANGLE*)pinst)->v2=v2;
	((D3DTRIANGLE*)pinst)->v3=v3;
	((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
	pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

	while (triCnt--)
	{
		v2=v3;
		v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
	}

	xxb.vertCount+=pntCnt;
	xxb.instOffset+=ULong(pinst)-ULong(pistart);

	//DumpXBuffer((XBuf)xxb);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupExecuteBuffer
//Author		Paul.   
//Date			Tue 7 Jul 1998
//------------------------------------------------------------------------------
inline void direct_3d::SetupExecuteBuffer(LPDIRECT3DDEVICE pd3ddev,ULong sz,XBuf* pxb)
{
	//create the buffer
	ZeroMem(&pxb->xbDesc,sizeof(D3DEXECUTEBUFFERDESC));
	pxb->xbDesc.dwSize=sizeof(D3DEXECUTEBUFFERDESC);
	pxb->xbDesc.dwFlags=D3DDEB_BUFSIZE;
	pxb->xbDesc.dwBufferSize=sz;
	HRESULT dderrval=
	pd3ddev->CreateExecuteBuffer(&pxb->xbDesc,&pxb->pxBuf,NULL);
	DIRECT3DERROR(dderrval);

	//check the memory allocated is correct
	ULong realSize=pxb->xbDesc.dwBufferSize;
	pxb->_xbuffer_size=realSize;
	pxb->_max_verts=realSize/(sizeof(R3DTLVERTEX)*2);
	pxb->_inst_start=pxb->_max_verts*sizeof(R3DTLVERTEX);
	pxb->_inst_len=realSize-pxb->_inst_start;

	pxb->vertCount=0;
	pxb->instOffset=pxb->_inst_start;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInitialRenderStatesPlain
//Author		Paul.   
//Date			Tue 7 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::SetInitialRenderStatesPlain(XBuf* pxb)
{
 	HRESULT dderrval;

	dderrval=pxb->pxBuf->Lock(&pxb->xbDesc);
	DIRECT3DERROR(dderrval);
	pxb->bLocked=true;

	void* pinst=(void*)(ULong(pxb->xbDesc.lpData)+pxb->instOffset);
	void* pistart=pinst;

	OP_STATE_RENDER(5,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,pinst);
	STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);


//keeps lock on buffers for as long as possible now
	pxb->instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInitialRenderStatesTextured
//Author		Paul.   
//Date			Tue 7 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::SetInitialRenderStatesTextured(XBuf* pxb)
{
 	HRESULT dderrval;

	dderrval=pxb->pxBuf->Lock(&pxb->xbDesc);
	DIRECT3DERROR(dderrval);
	pxb->bLocked=true;

	void* pinst=(void*)(ULong(pxb->xbDesc.lpData)+pxb->instOffset);
	void* pistart=pinst;

	OP_STATE_RENDER(8,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATE,pinst);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
	D3DTEXTUREFILTER tfFilterMIN=Driver[CurrDriver].tfFilterMIN;
	D3DTEXTUREFILTER tfFilterMAG=Driver[CurrDriver].tfFilterMAG;
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,tfFilterMAG,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,tfFilterMIN,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,bGlobalFogFlag,pinst);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,pinst);
	STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);

//keeps lock on buffers for as long as possible now
	pxb->instOffset+=ULong(pinst)-ULong(pistart);
}

void direct_3d::SetInitialRenderStatesLand(XBuf* pxb)
{
 	HRESULT dderrval;

	dderrval=pxb->pxBuf->Lock(&pxb->xbDesc);
	DIRECT3DERROR(dderrval);
	pxb->bLocked=true;

	void* pinst=(void*)(ULong(pxb->xbDesc.lpData)+pxb->instOffset);
	void* pistart=pinst;

	OP_STATE_RENDER(9,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_CLAMP,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATE,pinst);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
	D3DTEXTUREFILTER tfFilterMIN=Driver[CurrDriver].tfFilterMIN;
	D3DTEXTUREFILTER tfFilterMAG=Driver[CurrDriver].tfFilterMAG;
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,tfFilterMAG,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,tfFilterMIN,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,bGlobalFogFlag,pinst);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGCOLOR,CurrFogColour,pinst);
	STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);

//keeps lock on buffers for as long as possible now
	pxb->instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInitialRenderStatesTransp
//Author		Paul.   
//Date			Tue 7 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::SetInitialRenderStatesTransp(XBuf* pxb)
{
 	HRESULT dderrval;

	dderrval=pxb->pxBuf->Lock(&pxb->xbDesc);
	DIRECT3DERROR(dderrval);
	pxb->bLocked=true;

	void* pinst=(void*)(ULong(pxb->xbDesc.lpData)+pxb->instOffset);
	void* pistart=pinst;

	D3DTEXTUREBLEND	tbBlendMode=Driver[CurrDriver].tbBlendMode;

	OP_STATE_RENDER(10,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,tbBlendMode,pinst);
	STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,pinst);
	STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,pinst);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
	D3DTEXTUREFILTER tfFilterMAG=Driver[CurrDriver].tfFilterMAG;
	D3DTEXTUREFILTER tfFilterMIN=Driver[CurrDriver].tfFilterMIN;
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,tfFilterMAG,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,tfFilterMIN,pinst);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,bGlobalFogFlag,pinst);
	STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);

//keeps lock on buffers for as long as possible now
	pxb->instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInitialRenderStatesMasked
//Author		Paul.   
//Date			Wed 8 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::SetInitialRenderStatesMasked(XBuf* pxb)
{
 	HRESULT dderrval;

	dderrval=pxb->pxBuf->Lock(&pxb->xbDesc);
	DIRECT3DERROR(dderrval);
	pxb->bLocked=true;

	void* pinst=(void*)(ULong(pxb->xbDesc.lpData)+pxb->instOffset);
	void* pistart=pinst;

	if (maskedTexture.bPalettized)
	{
		OP_STATE_RENDER(7,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATE,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,Driver[CurrDriver].tfFilterMSK,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	}
	else
	{
		D3DTEXTUREBLEND	tbBlendMode=Driver[CurrDriver].tbBlendMode;

		OP_STATE_RENDER(9,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,tbBlendMode,pinst);
		STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
		D3DTEXTUREFILTER tfFilterMAG=Driver[CurrDriver].tfFilterMAG;
		D3DTEXTUREFILTER tfFilterMIN=Driver[CurrDriver].tfFilterMIN;
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,tfFilterMAG,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,tfFilterMIN,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	}

//keeps lock on buffers for as long as possible now
	pxb->instOffset+=ULong(pinst)-ULong(pistart);
}

void direct_3d::SetInitialRenderStatesFont(XBuf* pxb)
{
 	HRESULT dderrval;

	dderrval=pxb->pxBuf->Lock(&pxb->xbDesc);
	DIRECT3DERROR(dderrval);
	pxb->bLocked=true;

	void* pinst=(void*)(ULong(pxb->xbDesc.lpData)+pxb->instOffset);
	void* pistart=pinst;

	if (maskedTexture.bPalettized)
	{
		OP_STATE_RENDER(7,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATE,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	}
	else
	{
		OP_STATE_RENDER(9,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATEALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	}

//keeps lock on buffers for as long as possible now
	pxb->instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInitialRenderStatesLines
//Author		Paul.   
//Date			Mon 7 Sep 1998
//------------------------------------------------------------------------------
void direct_3d::SetInitialRenderStatesLines(LXBuf* pxb)
{
 	HRESULT dderrval;

	dderrval=pxb->pxBuf->Lock(&pxb->xbDesc);
	DIRECT3DERROR(dderrval);
	pxb->bLocked=true;

	void* pinst=(void*)(ULong(pxb->xbDesc.lpData)+pxb->instOffset);
	void* pistart=pinst;

	OP_STATE_RENDER(6,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_SHADEMODE,D3DSHADE_FLAT,pinst);
	STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);

	OP_PROCESS_VERTICES(1,pinst);
	LPD3DPROCESSVERTICES pPV=(LPD3DPROCESSVERTICES)pinst;
	pxb->pPV=pPV;
	pPV->dwFlags=D3DPROCESSVERTICES_COPY;
	pPV->wStart=pPV->wDest=0;
	pPV->dwReserved=0;
	pPV++;
	pinst=(void*)pPV;

//keeps lock on buffers for as long as possible now
	pxb->instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInitialRenderStatesPoints
//Author		Paul.   
//Date			Mon 7 Sep 1998
//------------------------------------------------------------------------------
void direct_3d::SetInitialRenderStatesPoints(LXBuf* pxb)
{
 	HRESULT dderrval;

	dderrval=pxb->pxBuf->Lock(&pxb->xbDesc);
	DIRECT3DERROR(dderrval);
	pxb->bLocked=true;

	void* pinst=(void*)(ULong(pxb->xbDesc.lpData)+pxb->instOffset);
	void* pistart=pinst;

	OP_STATE_RENDER(6,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
	STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_FOGENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,FALSE,pinst);
	STATE_DATA(D3DRENDERSTATE_SHADEMODE,D3DSHADE_FLAT,pinst);
	STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);

	OP_PROCESS_VERTICES(1,pinst);
	LPD3DPROCESSVERTICES pPV=(LPD3DPROCESSVERTICES)pinst;
	pxb->pPV=pPV;
	pPV->dwFlags=D3DPROCESSVERTICES_COPY;
	pPV->wStart=pPV->wDest=0;
	pPV->dwReserved=0;
	pPV++;
	pinst=(void*)pPV;

//keeps lock on buffers for as long as possible now
	pxb->instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateLandTBuffers
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::CreateLandTBuffers(struct _DirectDraw* pdirectd)
{

//	if (gameSettings.m_bHighLandTexture)
//	{
		CreateLandTBuffers2(pdirectd);
//		return;
//	}

	//make 8*256*256 textures in Sys & Vid RAM for landscape texture
	//data
/*	bool bPal=(opaqueTexture.bPalettized)?true:false;

	const DWORD dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;

	HRESULT dderrval;
	DDSURFACEDESC tmsd=opaqueTexture.ddsd;
	tmsd.dwWidth=_landTextureWH;
	tmsd.dwHeight=_landTextureWH;
	tmsd.dwFlags=dwFlags;
	tmsd.ddsCaps.dwCaps=DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY;

	if (gameSettings.m_bUseMipMapping)
	{
		tmsd.dwFlags|=DDSD_MIPMAPCOUNT;
		tmsd.ddsCaps.dwCaps|=DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
		tmsd.dwMipMapCount=3;
	}

	for (int i=0;i<_landscapeTextures;i++){
		VIDRAMTEXTURE& vrt=vidramlandmaps[i];
		vrt.dwWidth=vrt.dwHeight=_landTextureWH;
		vrt.fWidth=vrt.fHeight=Float(_landTextureWH)*65536.0;
		dderrval=pdirectd->lpDD2->CreateSurface(&tmsd,&vrt.lpdds1TSurf,NULL);
		DIRECTDRAWERROR(dderrval);
		dderrval=vrt.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&vrt.lpdds2TSurf);
		if (bPal) dderrval=vrt.lpdds2TSurf->SetPalette(lpDDPalette[0]);
		DIRECTDRAWERROR(dderrval);
		dderrval=vrt.lpdds2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID *)&vrt.lpd3dTexture);
		DIRECTDRAWERROR(dderrval);
		dderrval=vrt.lpd3dTexture->GetHandle(lpD3DDevice,&vrt.d3dhTexture);
		DIRECT3DERROR(dderrval);
		vidramlandptr[i]=&vrt;
	}

	//Create a compatible texture in system RAM & leave it page 
	//locked permenantly for faster surface->surface blits

	tmsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_SYSTEMMEMORY;

	if (gameSettings.m_bUseMipMapping)
		tmsd.ddsCaps.dwCaps|=DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;

	for (i=0;i<_landscapeTextures;i++){
		VIDRAMTEXTURE& srt=sysramlandmaps[i];
		srt.dwWidth=srt.dwHeight=_landTextureWH;
		srt.fWidth=srt.fHeight=Float(_landTextureWH)*65536.0;
		dderrval=pdirectd->lpDD2->CreateSurface(&tmsd,&srt.lpdds1TSurf,NULL);
		DIRECTDRAWERROR(dderrval);
		dderrval=srt.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&srt.lpdds2TSurf);
		if (bPal) dderrval=srt.lpdds2TSurf->SetPalette(lpDDPalette[0]);
		DIRECTDRAWERROR(dderrval);
		dderrval=srt.lpdds2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID *)&srt.lpd3dTexture);
		DIRECTDRAWERROR(dderrval);
		sysramlandptr[i]=&srt;

		srt.lpdds2TSurf->PageLock(0);
		DDSURFACEDESC tsd=opaqueTexture.ddsd;
		do{
			dderrval=
			srt.lpdds2TSurf->Lock(NULL,&tsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
		}
		while (dderrval!=DD_OK);
		srt.pSurface=tsd.lpSurface;
		srt.lpdds2TSurf->Unlock(tsd.lpSurface);

		//page lock remains active during the 3D so the texture RAM can't move
		//from this location.
	}*/
}

void direct_3d::EatTextureRAM(DirectD* pdirectd,ULong ramSize)
{
//#ifdef PAULS_DEBUG
//	ramSize/=(256*256);
//	if (opaqueTexture.ddsd.ddpfPixelFormat.dwRGBBitCount==16)
//		ramSize>>1;
//
//	while (ramSize--)
//	{
//		LPDIRECTDRAW2 lpDD2=pdirectd->lpDD2;
//		DDSURFACEDESC sd;
//		LPDIRECTDRAWSURFACE lpDDS;
//		LPDIRECTDRAWSURFACE2 lpDDS2;
//		LPDIRECT3DTEXTURE lpD3DT;
//		HRESULT hr;
//		sd=opaqueTexture.ddsd;
//		sd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;
//		sd.dwWidth=sd.dwHeight=256;
//		sd.ddsCaps.dwCaps=DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY;
//		hr=lpDD2->CreateSurface(&sd,&lpDDS,NULL);
//		if (hr!=DD_OK) break;
//		hr=lpDDS->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&lpDDS2);
//		if (hr!=DD_OK) break;
//		hr=lpDDS2->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&lpD3DT);
//		if (hr!=D3D_OK) break;
//	}
//#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateLandTBuffers2
//Author		Paul.   
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::CreateLandTBuffers2(DirectD* pdirectd)
{
//#ifdef PAULS_DEBUG
//	EatTextureRAM(pdirectd,4*1024*1024);	//throw away 2Mb of texture space
//#endif

	const DWORD LAND_MIP_LEVELS=4;
	const DWORD dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;

	//make textures in Sys & Vid RAM for landscape texture
	//data

	LPDIRECTDRAW2 lpDD2;
	HRESULT hr;
	DDSURFACEDESC sd;
	sd=opaqueTexture.ddsd;
	sd.dwFlags=dwFlags;
	sd.ddsCaps.dwCaps=DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY;

	bool bPal=(opaqueTexture.bPalettized)?true:false;

	lpDD2=pdirectd->lpDD2;

	if (Save_Data.filtering>=2)
	{
		sd.dwFlags|=DDSD_MIPMAPCOUNT;
		sd.ddsCaps.dwCaps|=DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
		sd.dwMipMapCount=LAND_MIP_LEVELS;
	}

	sd.dwWidth=sd.dwHeight=256;

	for (SLong i=0;i<NUM_256_TEXTURES;i++)
	{
		VIDRAMTEXTURE& vrt=vidram256maps[i];

		vrt.dwWidth=vrt.dwHeight=sd.dwWidth;
		vrt.fWidth=vrt.fHeight=D3DVALUE(vrt.dwWidth)*65536.0;

		hr=lpDD2->CreateSurface(&sd,&vrt.lpdds1TSurf,NULL);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&vrt.lpdds2TSurf);
		DIRECTDRAWERROR(hr);
		if (bPal) hr=vrt.lpdds2TSurf->SetPalette(lpDDLandPal);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&vrt.lpd3dTexture);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpd3dTexture->GetHandle(lpD3DDevice,&vrt.d3dhTexture);
		DIRECT3DERROR(hr);
	}

	sd.dwWidth=(sd.dwHeight>>=1);

	for (i=0;i<NUM_128_TEXTURES;i++)
	{
		VIDRAMTEXTURE& vrt=vidram128maps[i];

		vrt.dwWidth=vrt.dwHeight=sd.dwWidth;
		vrt.fWidth=vrt.fHeight=D3DVALUE(vrt.dwWidth)*65536.0;

		hr=lpDD2->CreateSurface(&sd,&vrt.lpdds1TSurf,NULL);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&vrt.lpdds2TSurf);
		DIRECTDRAWERROR(hr);
		if (bPal) hr=vrt.lpdds2TSurf->SetPalette(lpDDLandPal);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&vrt.lpd3dTexture);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpd3dTexture->GetHandle(lpD3DDevice,&vrt.d3dhTexture);
		DIRECT3DERROR(hr);
	}

	sd.dwWidth=(sd.dwHeight>>=1);

	for (i=0;i<NUM_64_TEXTURES;i++)
	{
		VIDRAMTEXTURE& vrt=vidram64maps[i];

		vrt.dwWidth=vrt.dwHeight=sd.dwWidth;
		vrt.fWidth=vrt.fHeight=D3DVALUE(vrt.dwWidth)*65536.0;

		hr=lpDD2->CreateSurface(&sd,&vrt.lpdds1TSurf,NULL);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&vrt.lpdds2TSurf);
		DIRECTDRAWERROR(hr);
		if (bPal) hr=vrt.lpdds2TSurf->SetPalette(lpDDLandPal);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&vrt.lpd3dTexture);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpd3dTexture->GetHandle(lpD3DDevice,&vrt.d3dhTexture);
		DIRECT3DERROR(hr);
	}

	sd.dwWidth=(sd.dwHeight>>=1);

	for (i=0;i<NUM_32_TEXTURES;i++)
	{
		VIDRAMTEXTURE& vrt=vidram32maps[i];

		vrt.dwWidth=vrt.dwHeight=sd.dwWidth;
		vrt.fWidth=vrt.fHeight=D3DVALUE(vrt.dwWidth)*65536.0;

		hr=lpDD2->CreateSurface(&sd,&vrt.lpdds1TSurf,NULL);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&vrt.lpdds2TSurf);
		DIRECTDRAWERROR(hr);
		if (bPal) hr=vrt.lpdds2TSurf->SetPalette(lpDDLandPal);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&vrt.lpd3dTexture);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpd3dTexture->GetHandle(lpD3DDevice,&vrt.d3dhTexture);
		DIRECT3DERROR(hr);
	}

	sd.dwWidth=(sd.dwHeight>>=1);

	for (i=0;i<NUM_16_TEXTURES;i++)
	{
		VIDRAMTEXTURE& vrt=vidram16maps[i];

		vrt.dwWidth=vrt.dwHeight=sd.dwWidth;
		vrt.fWidth=vrt.fHeight=D3DVALUE(vrt.dwWidth)*65536.0;

		hr=lpDD2->CreateSurface(&sd,&vrt.lpdds1TSurf,NULL);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&vrt.lpdds2TSurf);
		DIRECTDRAWERROR(hr);
		if (bPal) hr=vrt.lpdds2TSurf->SetPalette(lpDDLandPal);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&vrt.lpd3dTexture);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpd3dTexture->GetHandle(lpD3DDevice,&vrt.d3dhTexture);
		DIRECT3DERROR(hr);
	}

	sd.dwWidth=(sd.dwHeight>>=1);

	for (i=0;i<NUM_8_TEXTURES;i++)
	{
		VIDRAMTEXTURE& vrt=vidram8maps[i];

		vrt.dwWidth=vrt.dwHeight=sd.dwWidth;
		vrt.fWidth=vrt.fHeight=D3DVALUE(vrt.dwWidth)*65536.0;

		hr=lpDD2->CreateSurface(&sd,&vrt.lpdds1TSurf,NULL);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&vrt.lpdds2TSurf);
		DIRECTDRAWERROR(hr);
		if (bPal) hr=vrt.lpdds2TSurf->SetPalette(lpDDLandPal);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&vrt.lpd3dTexture);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpd3dTexture->GetHandle(lpD3DDevice,&vrt.d3dhTexture);
		DIRECT3DERROR(hr);
	}

	//also, create one texture of each dimension in main RAM

	sd.dwWidth=sd.dwHeight=256;
	sd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_SYSTEMMEMORY;

	if (Save_Data.filtering>=2)
		sd.ddsCaps.dwCaps|=DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;

	for (i=0;i<NUM_SCALES;i++)
	{
		VIDRAMTEXTURE& vrt=sysramALLmaps[i];

		vrt.dwWidth=vrt.dwHeight=sd.dwWidth;
		vrt.fWidth=vrt.fHeight=D3DVALUE(vrt.dwWidth)*65536.0;

		hr=lpDD2->CreateSurface(&sd,&vrt.lpdds1TSurf,NULL);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds1TSurf->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&vrt.lpdds2TSurf);
		DIRECTDRAWERROR(hr);
		if (bPal) hr=vrt.lpdds2TSurf->SetPalette(lpDDLandPal);
		DIRECTDRAWERROR(hr);
		hr=vrt.lpdds2TSurf->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&vrt.lpd3dTexture);
		DIRECTDRAWERROR(hr);

		sd.dwWidth=(sd.dwHeight>>=1);
	}

	if (Save_Data.filtering==3)
		SetupExtraLandDetail(pdirectd);

	//clear usage tables
	landTextureUsage=new UByte[NUM_256_TEXTURES+NUM_128_TEXTURES+
							NUM_64_TEXTURES+NUM_32_TEXTURES+
							NUM_16_TEXTURES+NUM_8_TEXTURES];

	ZeroMem(landTextureUsage,NUM_256_TEXTURES+NUM_128_TEXTURES+
							NUM_64_TEXTURES+NUM_32_TEXTURES+
							NUM_16_TEXTURES+NUM_8_TEXTURES);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLandBufferPtr
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
void* direct_3d::GetLandBufferPtr(struct _DirectDraw* pdirectd,SWord index)
{
	//given an index, return a pointer to the surface memory of the correct
	//Sys RAM texture
	return sysramlandptr[index]->pSurface;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLandPalLookup
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
void* direct_3d::GetLandPalLookup(struct _DirectDraw* pdirectd)
{
	//Only really of use to non-palettised versions of landscape
	//textures - returns a lookup table to convert 8 bit texel data
	//to the correct format for the surface

//	return (void*)lpDDPalLookup[0];	//assumes landscape uses palette 0
	return lpDDLandPalLookup;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLandPalLookup
//Author		PAul
//Date			Mon 16 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::SetLandPalLookup(struct _DirectDraw* pdirectd,UByte* pPal)
{
	HRESULT hr;
	LPDIRECTDRAW2 lpDD2;
	PALETTEENTRY  peNewpal[256];
	R3DPal* rpNewpal=(R3DPal*)pPal;

	double gamma_value=gamma_values[Save_Data.gammacorrection];
	lpDD2=pdirectd->lpDD2;

	for (SLong i=0;i<256;i++)
	{
	 	GammaCorrectRGB(&rpNewpal[i],gamma_value);
		GreyPalette((UByte*)&rpNewpal[i]);
		peNewpal[i].peRed=rpNewpal[i].g;
		peNewpal[i].peGreen=rpNewpal[i].b;
		peNewpal[i].peBlue=rpNewpal[i].r;

		rpNewpal[i].r=peNewpal[i].peRed;
		rpNewpal[i].g=peNewpal[i].peGreen;
		rpNewpal[i].b=peNewpal[i].peBlue;
	}

	if (lpDDLandPal!=NULL)
		hr=lpDDLandPal->SetEntries(NULL,0,256,peNewpal);
	else
		hr=lpDD2->CreatePalette(DDPCAPS_8BIT|DDPCAPS_ALLOW256,peNewpal,&lpDDLandPal,NULL);

	MakePALLookup(opaqueTexture,lpDDLandPalLookup,rpNewpal);

	MakePALLookup(transpTexture,lpDDTLandPalLookup,rpNewpal);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLandBpp
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
SWord direct_3d::GetLandBpp(struct _DirectDraw* pdirectd)
{
	pdirectd=pdirectd;
	return opaqueTexture.bPalettized?8:16;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginTextureScroll
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::BeginTextureScroll(	struct _DirectDraw* pdirectd,
									const SWord lvl,
									void* psrc,
									void* pdst)
{
	HRESULT dderrval;
	LPDIRECTDRAWSURFACE2 pssrc;
	LPDIRECTDRAWSURFACE2 psdst;

	//convert the void pointers back to something sensible
	RECT* prsrc=(RECT*)psrc;
	RECT* prdst=(RECT*)pdst;

	pssrc=vidramlandptr[lvl]->lpdds2TSurf;
	psdst=vidramlandptr[_landscapeTextures-1]->lpdds2TSurf;

	//swap over the texture pointers

	VIDRAMTEXTURE* pvrt=vidramlandptr[lvl];
	vidramlandptr[lvl]=vidramlandptr[_landscapeTextures-1];
	vidramlandptr[_landscapeTextures-1]=pvrt;

	DDBLTFX bltfx;

	ZeroMem(&bltfx,sizeof(DDBLTFX));
	bltfx.dwSize=sizeof(DDBLTFX);

	//last texture in the buffer of landscape textures is 
	//available as temporary workspace so I can blit the
	//area defined by prsrc on the source texture to the
	//area defined by prdst on the destination texture and
	//then just swap texture pointers in vidramlandptr

	dderrval=psdst->Blt(prdst,pssrc,prsrc,DDBLT_ASYNC,&bltfx);
	DIRECTDRAWERROR(dderrval);

	//return without waiting for the blit to complete
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WaitTextureScrollComplete
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::WaitTextureScrollComplete(	struct _DirectDraw* pdirectd,
											const SWord lvl)
{
	LPDIRECTDRAWSURFACE2 pdds;
	pdds=vidramlandptr[lvl]->lpdds2TSurf;
	while (pdds->GetBltStatus(DDGBS_ISBLTDONE)!=DD_OK) {}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PartialTextureUpload
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::PartialTextureUpload(	struct _DirectDraw* pdirectd,
										const SWord lvl,
										void* psrc,
										void* pdst)
{
	HRESULT dderrval;
	LPDIRECTDRAWSURFACE2 pssrc;
	LPDIRECTDRAWSURFACE2 psdst;

	//convert the void pointers back to something sensible
//	RECT* prsrc=(RECT*)psrc;
//	RECT* prdst=(RECT*)pdst;

	pssrc=sysramlandptr[lvl]->lpdds2TSurf;
	psdst=vidramlandptr[lvl]->lpdds2TSurf;

	DDBLTFX bltfx;

	ZeroMem(&bltfx,sizeof(DDBLTFX));
	bltfx.dwSize=sizeof(DDBLTFX);

	dderrval=psdst->Blt(NULL,pssrc,NULL,DDBLT_WAIT,&bltfx);
	DIRECTDRAWERROR(dderrval);

	if (Save_Data.filtering<2) return;

	//generate the remaining mipmap levels here

	LPDIRECTDRAWSURFACE2 psnext,psnextv;
	DDSURFACEDESC ddsdSrc,ddsdNext;
	ZeroMem(&ddsdSrc,sizeof(DDSURFACEDESC));
	ZeroMem(&ddsdNext,sizeof(DDSURFACEDESC));
	ddsdSrc.dwSize=ddsdNext.dwSize=sizeof(DDSURFACEDESC);

	//get a surface memory ptr for the source surface

	do
	{
		dderrval=
		pssrc->Lock(NULL,&ddsdSrc,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
	}
	while (dderrval!=DD_OK);

	DDSCAPS scaps;
	scaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_MIPMAP;

	pssrc->GetAttachedSurface(&scaps,&psnext);
	psdst->GetAttachedSurface(&scaps,&psnextv);

	SWord bytesPerPixel=ddsdSrc.ddpfPixelFormat.dwRGBBitCount>>3;

	while (psnext!=NULL)
	{
		do
		{
			dderrval=
			psnext->Lock(NULL,&ddsdNext,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
		}
		while (dderrval!=DD_OK);

		if (bytesPerPixel==1)
		{
			SLong sdx=ddsdSrc.dwWidth/ddsdNext.dwWidth;
			SLong sdy=ddsdSrc.lPitch*(ddsdSrc.dwHeight/ddsdNext.dwHeight);

			UByte *psrc,*pdst;

			psrc=(UByte*)ddsdSrc.lpSurface;
			pdst=(UByte*)ddsdNext.lpSurface;

			for (int row=0;row<ddsdNext.dwHeight;row++)
			{
				UByte* psrc2=psrc;
				UByte* pdst2=pdst;

				for (int col=0;col<ddsdNext.dwWidth;col++)
				{
					*pdst2++=*psrc2;
					psrc2+=sdx;
				}
				psrc+=sdy;
				pdst+=ddsdNext.lPitch;
			}
		}
		else if (bytesPerPixel==2)
		{
			SLong sdx=ddsdSrc.dwWidth/ddsdNext.dwWidth;
			SLong sdy=ddsdSrc.lPitch*(ddsdSrc.dwHeight/ddsdNext.dwHeight);

			UWord *psrc,*pdst;

			psrc=(UWord*)ddsdSrc.lpSurface;
			pdst=(UWord*)ddsdNext.lpSurface;

			for (int row=0;row<ddsdNext.dwHeight;row++)
			{
				UWord* psrc2=psrc;
				UWord* pdst2=pdst;

				for (int col=0;col<ddsdNext.dwWidth;col++)
				{
					*pdst2++=*psrc2;
					psrc2+=sdx;
				}
				psrc=(UWord*)(ULong(psrc)+sdy);
				pdst=(UWord*)(ULong(pdst)+ddsdNext.lPitch);
			}
		}

		psnext->Unlock(ddsdNext.lpSurface);

		//copy up to video RAM

		dderrval=psnextv->Blt(NULL,psnext,NULL,DDBLT_WAIT,&bltfx);
		DIRECTDRAWERROR(dderrval);

		psnext->GetAttachedSurface(&scaps,&psnext);
		psnextv->GetAttachedSurface(&scaps,&psnextv);
	}

	//release the lock on the source surface

	pssrc->Unlock(ddsdSrc.lpSurface);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewTile
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::NewTile(struct _DirectDraw* pdirectd,
						SLong pntcnt,
						DoPointStruc* pdp,
						SLong tricount,
						UByte* tridata,
						SLong hT)
{
	if (nearlndXB.vertCount+pntcnt>nearlndXB._max_verts)
	{	
		FlushLandDraw(pdirectd,nearlndXB);
	}
	else
	{	//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*tricount+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(nearlndXB._inst_len-nearlndXB.instOffset))
			FlushLandDraw(pdirectd,nearlndXB);
	}

	//add to the current buffer

	ULong vBase=nearlndXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)nearlndXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)nearlndXB.xbDesc.lpData)+nearlndXB.instOffset);
	void* pistart=pinst;

	for (int i=0;i<pntcnt;i++,pdp++,ptlvert++)
	{
		ptlvert->sx=D3DVALUE(pdp->bodyx.f);
		ptlvert->sy=D3DVALUE(pdp->bodyy.f);
		ptlvert->sz=D3DVALUE(pdp->bodyz.f);

		if (lightingEffectsEnabled)		SetVertexColor(ptlvert,pdp);
		else							ptlvert->color=AmbientLight;	//D3DCOLOR(0x00FFFFFF);

		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert->tu=D3DVALUE(pdp->ix)*D3DVALUE(1./256.);
		ptlvert->tv=D3DVALUE(pdp->iy)*D3DVALUE(1./256.);
	}

	VIDRAMTEXTURE* pVrt=vidramlandptr[hT];
	D3DTEXTUREHANDLE hTexture=pVrt->d3dhTexture;

	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,hTexture,pinst);

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntcnt,pinst);

	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	OP_TRIANGLE_LIST(tricount,pinst);
	while (tricount--)
	{
		int v1=vBase+*tridata++;
		int v2=vBase+*tridata++;
		int v3=vBase+*tridata++;
		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
	}
	nearlndXB.vertCount+=pntcnt;
	nearlndXB.instOffset+=ULong(pinst)-ULong(pistart);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CNewTile
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
void direct_3d::CNewTile(	struct _DirectDraw* pdirectd,
							SLong pntcnt,
							DoPointStruc* pdp,
							SLong tricount,
							UByte* tridata,
							SLong hT)
{
	ULong interpFlag=	IF3D_TEXTURE+
						((globalSpecular)?IF3D_SPECULAR:0)+
						((globalLighting)?IF3D_COLOR:0);

	bool doflush=false;

	DoPointStruc* psdp=pdp;

	static UByte renumber[256];

	ULong pntEstimate=pntcnt+pntcnt+pntcnt;
	ULong trisEstimate=tricount+tricount;

	if (clandXB.vertCount+pntEstimate>clandXB._max_verts)
	{	
		FlushPTDraw(pdirectd,clandXB);
	}
	else
	{	//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						(2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE))+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(clandXB._inst_len-clandXB.instOffset))
			FlushPTDraw(pdirectd,clandXB);
	}

	//add to the current buffer

	ULong vBase=clandXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)clandXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)clandXB.xbDesc.lpData)+clandXB.instOffset);
	void* pibase=(void*)(((UByte*)clandXB.xbDesc.lpData)+clandXB._inst_start);
	void* pistart=pinst;

	int renumberIndex=0;

	for (int srcPntIndex=0;srcPntIndex<pntcnt;srcPntIndex++,psdp++)
	{
		if (psdp->clipFlags==CF3D_NULL)
		{
			ptlvert->sx=D3DVALUE(psdp->bodyx.f);
			ptlvert->sy=D3DVALUE(psdp->bodyy.f);
			ptlvert->sz=D3DVALUE(psdp->bodyz.f);
			SetVertexColor(ptlvert,psdp);
			ptlvert->clipFlags=psdp->clipFlags|interpFlag;
			ptlvert->tu=D3DVALUE(psdp->ix)*D3DVALUE(1./256.);
			ptlvert->tv=D3DVALUE(psdp->iy)*D3DVALUE(1./256.);
			ptlvert++;
			renumber[srcPntIndex]=renumberIndex++;
		}
	}
	pntcnt=renumberIndex;

	//Add the process vertices instruction but leave the
	//count field blank 'til later
	OP_PROCESS_VERTICES(1,pinst);
	D3DPROCESSVERTICES* ppv=(D3DPROCESSVERTICES*)pinst;
	ppv->dwFlags=D3DPROCESSVERTICES_COPY;
	ppv->wStart=ppv->wDest=vBase;
	ppv->dwReserved=0;
	pinst=(void*)(ppv+1);

	static UByte wkspc[256];

	VIDRAMTEXTURE* pVrt=vidramlandptr[hT];
	D3DTEXTUREHANDLE hTexture=pVrt->d3dhTexture;

	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,hTexture,pinst);

	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	while (tricount--)
	{
		//reset index into temporary workspace
		ULong wkspcindex=0;

		UByte p1=*tridata++;
		UByte p2=*tridata++;
		UByte p3=*tridata++;

		//clip flags for fan base point
		UWord basecf=(pdp[p1].clipFlags&CF3D_ALL);
		UWord cfp2=(pdp[p2].clipFlags&CF3D_ALL);
		UWord cfp3=(pdp[p3].clipFlags&CF3D_ALL);

		if ((CF3D_ALL&basecf&cfp2&cfp3)==CF3D_NULL)
		{
			//some of this triangle is visible
		 	if ((CF3D_ALL&(basecf|cfp2|cfp3))==CF3D_NULL)
			{
			 	//no clipping required for this triangle
				//add the triangle to the execute buffer

				OP_TRIANGLE_LIST(1,pinst);
				((D3DTRIANGLE*)pinst)->v1=vBase+renumber[p1];
				((D3DTRIANGLE*)pinst)->v2=vBase+renumber[p2];
				((D3DTRIANGLE*)pinst)->v3=vBase+renumber[p3];
				((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
				pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
			}
			else
			{
				//this triangle needs clipping

				ULong pc=3;

				R3DTLVERTEX tstore[64];
				R3DTLVERTEX* ptstore=tstore;
				R3DTLVERTEX* polydef[64];
				R3DTLVERTEX** pptlv=polydef;

				if (basecf&CF3D_ALL)
				{
					ptstore->sx=D3DVALUE(pdp[p1].bodyx.f);
					ptstore->sy=D3DVALUE(pdp[p1].bodyy.f);
					ptstore->sz=D3DVALUE(pdp[p1].bodyz.f);
					SetVertexColor(ptstore,pdp+p1);
					ptstore->clipFlags=pdp[p1].clipFlags|interpFlag;
					ptstore->tu=D3DVALUE(pdp[p1].ix)*D3DVALUE(1./256.);
					ptstore->tv=D3DVALUE(pdp[p1].iy)*D3DVALUE(1./256.);
					polydef[0]=ptstore++;
				}
				else
				{
				 	polydef[0]=ptlvstart+renumber[p1];
				}

				if (cfp2&CF3D_ALL)
				{
					ptstore->sx=D3DVALUE(pdp[p2].bodyx.f);
					ptstore->sy=D3DVALUE(pdp[p2].bodyy.f);
					ptstore->sz=D3DVALUE(pdp[p2].bodyz.f);
					SetVertexColor(ptstore,pdp+p2);
					ptstore->clipFlags=pdp[p2].clipFlags|interpFlag;
					ptstore->tu=D3DVALUE(pdp[p2].ix)*D3DVALUE(1./256.);
					ptstore->tv=D3DVALUE(pdp[p2].iy)*D3DVALUE(1./256.);
					polydef[1]=ptstore++;
				}
				else
				{
				 	polydef[1]=ptlvstart+renumber[p2];
				}

				if (cfp3&CF3D_ALL)
				{
					ptstore->sx=D3DVALUE(pdp[p3].bodyx.f);
					ptstore->sy=D3DVALUE(pdp[p3].bodyy.f);
					ptstore->sz=D3DVALUE(pdp[p3].bodyz.f);
					SetVertexColor(ptstore,pdp+p3);
					ptstore->clipFlags=pdp[p3].clipFlags|interpFlag;
					ptstore->tu=D3DVALUE(pdp[p3].ix)*D3DVALUE(1./256.);
					ptstore->tv=D3DVALUE(pdp[p3].iy)*D3DVALUE(1./256.);
					polydef[2]=ptstore++;
				}
				else
				{
				 	polydef[2]=ptlvstart+renumber[p3];
				}

				GenericPolyClip(pc,polydef,ptlvert,ptstore);

				if (pc>2)
				{
					int i=0;
					ULong tc=pc-2;
					OP_TRIANGLE_LIST(tc,pinst);
					int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
					int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
					int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
					tc--;
					((D3DTRIANGLE*)pinst)->v1=v1;
					((D3DTRIANGLE*)pinst)->v2=v2;
					((D3DTRIANGLE*)pinst)->v3=v3;
					((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
					pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

					while (tc--)
					{
						v2=v3;
						v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
						((D3DTRIANGLE*)pinst)->v1=v1;
						((D3DTRIANGLE*)pinst)->v2=v2;
						((D3DTRIANGLE*)pinst)->v3=v3;
						((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
						pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
					}
				}
			}
		}
	}

	//fix up half generated points...

	pntcnt=(ULong(ptlvert)-ULong(ptlvstart))>>5;

	ptlvert=ptlvstart;

	for (srcPntIndex=0;srcPntIndex<pntcnt;srcPntIndex++)
	{
		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert++;
	}

	ppv->dwCount=pntcnt;

	clandXB.vertCount+=pntcnt;
	clandXB.instOffset+=ULong(pinst)-ULong(pistart);
}

bool direct_3d::SetTranspFade(bool newVal)
{
	bool lastVal=isTranspFade;
	isTranspFade=newVal;
	return lastVal;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushPLDraw
//Author		Paul.   
//Date			Mon 7 Sep 1998
//------------------------------------------------------------------------------
void direct_3d::FlushPLDraw(DirectD* pDirectD,LXBuf& xb)
{
	HRESULT dderrval;

	//add op-exit to the end of the buffer

	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pistart=pinst;

	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_SHADEMODE,D3DSHADE_GOURAUD,pinst);
	OP_EXIT(pinst);

	xb.pPV->dwCount=xb.vertCount;

	dderrval=xb.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	xb.bLocked=false;

	//DumpXBuffer(xb);

	xb.instOffset+=ULong(pinst)-ULong(pistart);

	assert(xb._inst_len>=(ULong(xb.instOffset)-xb._inst_start)&&"Execute buffer o'flow");

	if (xb.vertCount>0)
	{
		const DWORD dwStatus=
		D3DSTATUS_CLIPUNIONALL|D3DSTATUS_CLIPINTERSECTIONALL|D3DSTATUS_ZNOTVISIBLE;

		//execute the current execute buffer
		D3DEXECUTEDATA xData;
		ZeroMem(&xData,sizeof(D3DEXECUTEDATA));
		xData.dwSize=sizeof(D3DEXECUTEDATA);
		xData.dwVertexCount=xb.vertCount;
		xData.dwInstructionOffset=xb._inst_start;
		xData.dwInstructionLength=ULong(xb.instOffset)-xb._inst_start;
		xData.dsStatus.dwFlags=D3DSETSTATUS_ALL;
		xData.dsStatus.dwStatus=dwStatus;
		xData.dsStatus.drExtent.x2=0;
		xData.dsStatus.drExtent.y2=0;
		xData.dsStatus.drExtent.x1=winWidth;
		xData.dsStatus.drExtent.y1=winHeight;
		dderrval=xb.pxBuf->SetExecuteData(&xData);
		DIRECT3DERROR(dderrval);
		dderrval=lpD3DDevice->Execute(xb.pxBuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
		DIRECT3DERROR(dderrval);
	}
	//reset for the next set of poly data

	xb.vertCount=0;
	xb.instOffset=xb._inst_start;

	//fill in initial state changes
	SetInitialRenderStatesLines(&xb);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushPPDraw
//Author		Paul.   
//Date			Mon 7 Sep 1998
//------------------------------------------------------------------------------
void direct_3d::FlushPPDraw(DirectD* pDirectD,LXBuf& xb)
{
	HRESULT dderrval;

	//add op-exit to the end of the buffer

	void* pinst=(void*)(((UByte*)xb.xbDesc.lpData)+xb.instOffset);
	void* pistart=pinst;

	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_SHADEMODE,D3DSHADE_GOURAUD,pinst);
	OP_EXIT(pinst);

	xb.pPV->dwCount=xb.vertCount;

	dderrval=xb.pxBuf->Unlock();
	DIRECT3DERROR(dderrval);
	xb.bLocked=false;

	//DumpXBuffer(xb);

	xb.instOffset+=ULong(pinst)-ULong(pistart);

	assert(xb._inst_len>=(ULong(xb.instOffset)-xb._inst_start)&&"Execute buffer o'flow");

	if (xb.vertCount>0)
	{
		const DWORD dwStatus=
		D3DSTATUS_CLIPUNIONALL|D3DSTATUS_CLIPINTERSECTIONALL|D3DSTATUS_ZNOTVISIBLE;

		//execute the current execute buffer
		D3DEXECUTEDATA xData;
		ZeroMem(&xData,sizeof(D3DEXECUTEDATA));
		xData.dwSize=sizeof(D3DEXECUTEDATA);
		xData.dwVertexCount=xb.vertCount;
		xData.dwInstructionOffset=xb._inst_start;
		xData.dwInstructionLength=ULong(xb.instOffset)-xb._inst_start;
		xData.dsStatus.dwFlags=D3DSETSTATUS_ALL;
		xData.dsStatus.dwStatus=dwStatus;
		xData.dsStatus.drExtent.x2=0;
		xData.dsStatus.drExtent.y2=0;
		xData.dsStatus.drExtent.x1=winWidth;
		xData.dsStatus.drExtent.y1=winHeight;
		dderrval=xb.pxBuf->SetExecuteData(&xData);
		DIRECT3DERROR(dderrval);
		dderrval=lpD3DDevice->Execute(xb.pxBuf,lpD3DViewport,D3DEXECUTE_UNCLIPPED);
		DIRECT3DERROR(dderrval);
	}
	//reset for the next set of poly data

	xb.vertCount=0;
	xb.instOffset=xb._inst_start;

	//fill in initial state changes
	SetInitialRenderStatesPoints(&xb);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcItemFog
//Author		Paul.   
//Date			Wed 9 Sep 1998
//------------------------------------------------------------------------------
void direct_3d::CalcItemFog(bool bActivateItemFog,Float& bx,Float& by,Float& bz)
{
	if (bActivateItemFog)
	{
		bItemFoggingActive=false;
		itemFogVal=CALC_RANGE_FOG(bx,by,bz);
	}
	bItemFoggingActive=bActivateItemFog;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RegisterPalette
//Author		Paul.   
//Date			Wed 21 Oct 1998
//------------------------------------------------------------------------------
void direct_3d::RegisterPalette(DirectD* pDirectD,UByte* src,ULong length)
{
	SetPalette(pDirectD,src);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlushAll
//Author		Paul.   
//Date			Wed 28 Oct 1998
//------------------------------------------------------------------------------
void direct_3d::FlushAll(DirectD* pDirectD,Bool zState)
{
	FlushPLDraw(pDirectD,lineXB);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceTQTexture
//Author		Paul.   
//Date			Thu 29 Oct 1998
//------------------------------------------------------------------------------
SWord direct_3d::ForceTQ(SWord newTQ)
{
	if (newTQ<TQ_Low || newTQ>TQ_High)
		return textureQuality;

	SWord oldTQ=textureQuality;

	textureQuality=newTQ;

	return oldTQ;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTileToDDSurface
//Author		Paul.   
//Date			Thu 5 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::RenderTileToDDSurface(	DirectD* pdirectd,UByte* pTileData,
										const HTEXT& hTexture)
{
	//create DD surface pointers from hTexture
	LPDIRECTDRAWSURFACE2 pSurf,pVidSurf;
	ULong ht=hTexture();

	if (ht<NUM_256_TEXTURES)
	{
		pSurf=sysramALLmaps[0].lpdds2TSurf;
		pVidSurf=vidram256maps[ht].lpdds2TSurf;
	}
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES)
	{
		pSurf=sysramALLmaps[1].lpdds2TSurf;
		pVidSurf=vidram128maps[ht-NUM_256_TEXTURES].lpdds2TSurf;
	}
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES)
	{
		pSurf=sysramALLmaps[2].lpdds2TSurf;
		pVidSurf=vidram64maps[ht-
								NUM_256_TEXTURES-
								NUM_128_TEXTURES].lpdds2TSurf;
	}
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES)
	{
		pSurf=sysramALLmaps[3].lpdds2TSurf;
		pVidSurf=vidram32maps[ht-
								NUM_256_TEXTURES-
								NUM_128_TEXTURES-
								NUM_64_TEXTURES].lpdds2TSurf;
	}
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES)
	{
		pSurf=sysramALLmaps[4].lpdds2TSurf;
		pVidSurf=vidram16maps[ht-
								NUM_256_TEXTURES-
								NUM_128_TEXTURES-
								NUM_64_TEXTURES-
								NUM_32_TEXTURES].lpdds2TSurf;
	}
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES+NUM_8_TEXTURES)
	{
		pSurf=sysramALLmaps[5].lpdds2TSurf;
		pVidSurf=vidram8maps[ht-
								NUM_256_TEXTURES-
								NUM_128_TEXTURES-
								NUM_64_TEXTURES-
								NUM_32_TEXTURES-
								NUM_16_TEXTURES].lpdds2TSurf;
	}
	else assert(false&&"Bad Texture handle");

	HRESULT hr;
	DDSURFACEDESC sd,td;
	LPDIRECTDRAWSURFACE2 pNext,pVidNext,pSaveSurf;
	ROWANSURFACEDESC rsd;
	ZeroMem(&sd,sizeof(DDSURFACEDESC));
	ZeroMem(&td,sizeof(DDSURFACEDESC));
	sd.dwSize=td.dwSize=sizeof(DDSURFACEDESC);

	pSaveSurf=pSurf;

	DDSCAPS scaps;
	scaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_MIPMAP;

	do
	{
		hr=pSurf->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
	}
	while (hr!=DD_OK);

	//render landscape data to the target surface here!!!

	rsd.lpSurface=sd.lpSurface;
	rsd.dwWidth=sd.dwWidth;
	rsd.dwHeight=sd.dwHeight;
	rsd.lPitch=sd.lPitch;
	rsd.dwRGBBitCount=sd.ddpfPixelFormat.dwRGBBitCount;

	Three_Dee.pTMake->RenderTile2Surface(pTileData,&rsd);

	//render landscape data to the target surface here!!!

	pSurf->Unlock(sd.lpSurface);

	pSurf->GetAttachedSurface(&scaps,&pNext);

	while (pNext!=NULL)
	{
		//maybe generate mip map levels for this texture here!!

		do
		{
			hr=pSurf->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
		}
		while (hr!=DD_OK);
		
		do
		{
			hr=pNext->Lock(NULL,&td,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
		}
		while (hr!=DD_OK);

		if (sd.ddpfPixelFormat.dwRGBBitCount==8)
		{
			UByte* psrc=(UByte*)sd.lpSurface;
			UByte* pdst=(UByte*)td.lpSurface;

			for (SLong h=td.dwHeight;h--;)
			{
				UWord* psrc2=(UWord*)psrc;
				UByte* pdst2=pdst;
				for (SLong w=td.dwWidth;w--;)
				{
					UWord val=*psrc2++;
					*pdst2++=(UByte)val;
				}
				psrc+=sd.lPitch<<1;
				pdst+=td.lPitch;
			}
		}
		else if (sd.ddpfPixelFormat.dwRGBBitCount==16)
		{
			UWord* psrc=(UWord*)sd.lpSurface;
			UWord* pdst=(UWord*)td.lpSurface;

			for (SLong h=td.dwHeight;h--;)
			{
				ULong* psrc2=(ULong*)psrc;
				UWord* pdst2=pdst;
				for (SLong w=td.dwWidth;w--;) *pdst2++=(UWord)*psrc2++;
				psrc+=sd.lPitch;
				pdst+=td.lPitch>>1;
			}
		}

		pNext->Unlock(td.lpSurface);

		pSurf->Unlock(sd.lpSurface);

		pSurf=pNext;
		pSurf->GetAttachedSurface(&scaps,&pNext);
	}

	//upload the texture to vid ram version

	DDBLTFX	bltfx;
	ZeroMem(&bltfx,sizeof(bltfx));
	bltfx.dwSize=sizeof(bltfx);

	pSurf=pSaveSurf;
	pNext=pSurf;
	pVidNext=pVidSurf;
	do
	{
		pVidNext->Blt(NULL,pNext,NULL,DDBLT_WAIT,&bltfx);
		while (pVidNext->GetBltStatus(DDGBS_ISBLTDONE)!=DD_OK)	{}
		pNext->GetAttachedSurface(&scaps,&pNext);
		pVidNext->GetAttachedSurface(&scaps,&pVidNext);
	}
	while (pNext!=NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeTexture
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::FreeTexture(const HTEXT& hText)
{
	if (hText!=HTEXTNULL)
		landTextureUsage[hText()]=0x00;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeTextures
//Author		Paul.   
//Date			Tue 16 Feb 1999
//------------------------------------------------------------------------------
void direct_3d::FreeTextures()
{
	ZeroMem(landTextureUsage,NUM_256_TEXTURES+NUM_128_TEXTURES+
							NUM_64_TEXTURES+NUM_32_TEXTURES+
							NUM_16_TEXTURES+NUM_8_TEXTURES);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateTexture
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
HTEXT direct_3d::AllocateTexture(UByte textRez)
{
	UByte* pmin;
	UByte* pmax;

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
//Procedure		GetTextureScales
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::GetTextureScales(SLong& a,SLong& b,SLong& c,SLong& d,SLong& e,SLong& f)
{
 	a=NUM_256_TEXTURES;
	b=NUM_128_TEXTURES;
	c=NUM_64_TEXTURES;
	d=NUM_32_TEXTURES;
	e=NUM_16_TEXTURES;
	f=NUM_8_TEXTURES;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTextureCoord
//Author		Paul.   
//Date			Wed 11 Nov 1998
//------------------------------------------------------------------------------
inline D3DVALUE SetTextureCoord(SWord t,D3DVALUE min,D3DVALUE max)
{
	const D3DVALUE scale=(D3DVALUE)1./256.;
	if (t<=0)			return min;
	else if (t>=255)	return max;
	return D3DVALUE(t)*scale;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NearAddTileVerticesX
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
bool direct_3d::TileSplit(ULong pntCnt,DoPointStruc *pdp)
{
	bool fHadTrue=false,fHadFalse=false;
	for (int i=pntCnt-1;i>=0;i--)
	{
		bool fThis=(pdp[i].bodyz.f<=fZBufScaleSwitchRange)?true:false;
		if (!fHadTrue && fThis) {if (fHadFalse) return true; fHadTrue=true;}
		if (!fHadFalse && !fThis) {if (fHadTrue) return true; fHadFalse=true;}
	}
	return false;
}

void direct_3d::SaveClipFlags(ULong pntCnt,DoPointStruc *pdp)
{
	for (int i=pntCnt-1;i>=0;i--,pdp++)
		backupClipFlags[i]=pdp->clipFlags;
}

void direct_3d::RestoreClipFlags(ULong pntCnt,DoPointStruc *pdp)
{
	for (int i=pntCnt-1;i>=0;i--,pdp++)
		pdp->clipFlags=backupClipFlags[i];
}

void direct_3d::UpdateClipFlagsFrontChanged(ULong pntCnt,DoPointStruc *pdp)
{
	for (int i=pntCnt-1;i>=0;i--)
	{
		if (pdp[i].bodyz.f<viewdata.D)	pdp[i].clipFlags|=CF3D_BEHINDNEARZ;
		else							pdp[i].clipFlags&=~CF3D_BEHINDNEARZ;
	}
}

void direct_3d::UpdateClipFlagsBackChanged(ULong pntCnt,DoPointStruc *pdp)
{
	for (int i=pntCnt-1;i>=0;i--)
	{
		if (pdp[i].bodyz.f>viewdata.F)	pdp[i].clipFlags|=CF3D_PASTFARZ;
		else							pdp[i].clipFlags&=~CF3D_PASTFARZ;
	}
}

void direct_3d::NearAddTileVerticesX(struct _DirectDraw* pDirectD,
									ULong pntCnt,
									ULong totalTris,
									DoPointStruc* pdp,
									ULong drwCnt,
									UByte*& pdd,
									const HTEXT& ubHTexture,
									UWord flag)
{
	if (TileSplit(pntCnt,pdp))
	{
		UByte* old_pdd=pdd;
		SaveClipFlags(pntCnt,pdp);
		const Float BIT=.01;
		Float save;
		save=viewdata.D;
		viewdata.D=fZBufScaleSwitchRange+BIT;
		UpdateClipFlagsFrontChanged(pntCnt,pdp);
		CNearAddTileVerticesX2(	pDirectD,
								pntCnt,
								totalTris,
								pdp,
								drwCnt,
								pdd,
								ubHTexture,
								flag);
		pdd=old_pdd;
		RestoreClipFlags(pntCnt,pdp);
		viewdata.D=save;
		save=viewdata.F;
		viewdata.F=fZBufScaleSwitchRange;
		UpdateClipFlagsBackChanged(pntCnt,pdp);
		CNearAddTileVerticesX2(	pDirectD,
								pntCnt,
								totalTris,
								pdp,
								drwCnt,
								pdd,
								ubHTexture,
								flag);
		viewdata.F=save;
		RestoreClipFlags(pntCnt,pdp);
	}
	else NearAddTileVerticesX2(	pDirectD,
								pntCnt,
								totalTris,
								pdp,
								drwCnt,
								pdd,
								ubHTexture,
								flag);
}

void direct_3d::NearAddTileVerticesX2(struct _DirectDraw* pDirectD,
									ULong pntCnt,
									ULong totalTris,
									DoPointStruc* pdp,
									ULong drwCnt,
									UByte*& pdd,
									const HTEXT& ubHTexture,
									UWord flag)
{
	VIDRAMTEXTURE* pVrt;
	bool fIsHiRes=false;

	ULong dPntCnt,dTotalTris,dDrwCnt;
	DoPointStruc* dpdp;
	UByte* dpdd=NULL;

	ULong ht=ubHTexture();
	if (ht<NUM_256_TEXTURES)
	{
		pVrt=vidram256maps+ht;
		fIsHiRes=true;
		dPntCnt=pntCnt;
		dTotalTris=totalTris;
		dpdp=pdp;
		dDrwCnt=drwCnt;
		dpdd=pdd;
	}
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES)
		pVrt=vidram128maps+ht-NUM_256_TEXTURES;
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES)
		pVrt=vidram64maps+ht-NUM_256_TEXTURES-NUM_128_TEXTURES;
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES)
		pVrt=vidram32maps+ht-NUM_256_TEXTURES-NUM_128_TEXTURES-NUM_64_TEXTURES;
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES)
		pVrt=vidram16maps+ht-NUM_256_TEXTURES-NUM_128_TEXTURES-NUM_64_TEXTURES-NUM_32_TEXTURES;
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES+NUM_8_TEXTURES)
		pVrt=vidram8maps+ht-NUM_256_TEXTURES-NUM_128_TEXTURES-NUM_64_TEXTURES-NUM_32_TEXTURES-NUM_16_TEXTURES;
	else
		pVrt=NULL;

	D3DVALUE fMinTexelCoord,fMaxTexelCoord;

	fMinTexelCoord=.5/D3DVALUE(pVrt->dwWidth);
	fMaxTexelCoord=1.-fMinTexelCoord;
	
	UByte* pdrawdata=pdd;

	if (nearlndXB.vertCount+pntCnt>nearlndXB._max_verts)
	{	
		FlushLandDraw(pDirectD,nearlndXB);
	}
	else
	{	//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*totalTris+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(nearlndXB._inst_len-nearlndXB.instOffset))
			FlushLandDraw(pDirectD,nearlndXB);
	}

	//add to the current buffer

	ULong vBase=nearlndXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)nearlndXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)nearlndXB.xbDesc.lpData)+nearlndXB.instOffset);
	void* pistart=pinst;

	for (int i=0;i<pntCnt;i++,pdp++,ptlvert++)
	{
		ptlvert->sx=D3DVALUE(pdp->bodyx.f);
		ptlvert->sy=D3DVALUE(pdp->bodyy.f);
		ptlvert->sz=D3DVALUE(pdp->bodyz.f);

		if (lightingEffectsEnabled)		SetVertexColor(ptlvert,pdp);
		else							ptlvert->color=AmbientLight;	//D3DCOLOR(0x00FFFFFF);

		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert->tu=SetTextureCoord(pdp->ix,fMinTexelCoord,fMaxTexelCoord);
		ptlvert->tv=SetTextureCoord(pdp->iy,fMinTexelCoord,fMaxTexelCoord);
	}

	D3DTEXTUREHANDLE hTexture=(pVrt!=NULL)?pVrt->d3dhTexture:NULL;

	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,hTexture,pinst);

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);

	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	while (drwCnt--)
	{
		UByte at=*pdrawdata++;//skip colour byte
		ULong fanCnt=*pdrawdata++;

		bool whichDraw=(flag!=2&&IsForest(at))?true:false;
		if (flag==1) whichDraw=whichDraw?false:true;

		if (whichDraw)
		{
			while (fanCnt--)
			{
				ULong triCount=*pdrawdata++;
				pdrawdata+=2;
				while (triCount--) pdrawdata++;
			}
		}
		else
		while (fanCnt--){
			ULong triCnt=*pdrawdata++;
			OP_TRIANGLE_LIST(triCnt,pinst);
			int v1=vBase+*pdrawdata++;
			int v2=vBase+*pdrawdata++;
			int v3=vBase+*pdrawdata++;

			((D3DTRIANGLE*)pinst)->v1=v1;
			((D3DTRIANGLE*)pinst)->v2=v2;
			((D3DTRIANGLE*)pinst)->v3=v3;
			((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
			pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
			triCnt--;
			while (triCnt--)
			{
				v2=v3;
				v3=vBase+*pdrawdata++;
				((D3DTRIANGLE*)pinst)->v1=v1;
				((D3DTRIANGLE*)pinst)->v2=v2;
				((D3DTRIANGLE*)pinst)->v3=v3;
				((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
				pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
			}
		}
	}
	nearlndXB.vertCount+=pntCnt;
	nearlndXB.instOffset+=ULong(pinst)-ULong(pistart);
	pdd=pdrawdata;

	if (Save_Data.filtering==3 && fIsHiRes && flag!=1 && dpdd!=NULL)
	{
		NearAddTileDitherX(pDirectD,dPntCnt,dTotalTris,dpdp,dDrwCnt,dpdd);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CNearAddTileVerticesX
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::CNearAddTileVerticesX(struct _DirectDraw* pDirectD,
										ULong pntCnt,
										ULong totalTris,
										DoPointStruc* pdp,
										ULong drwCnt,
										UByte*& pdd,
										const HTEXT& ubHTexture,
										UWord flag)
{
	if (TileSplit(pntCnt,pdp))
	{
		UByte* old_pdd=pdd;
		SaveClipFlags(pntCnt,pdp);
		const Float BIT=.01;
		Float save;
		save=viewdata.D;
		viewdata.D=fZBufScaleSwitchRange+BIT;
		UpdateClipFlagsFrontChanged(pntCnt,pdp);
		CNearAddTileVerticesX2(	pDirectD,
								pntCnt,
								totalTris,
								pdp,
								drwCnt,
								pdd,
								ubHTexture,
								flag);
		pdd=old_pdd;
		RestoreClipFlags(pntCnt,pdp);
		viewdata.D=save;
		save=viewdata.F;
		viewdata.F=fZBufScaleSwitchRange;
		UpdateClipFlagsBackChanged(pntCnt,pdp);
		CNearAddTileVerticesX2(	pDirectD,
								pntCnt,
								totalTris,
								pdp,
								drwCnt,
								pdd,
								ubHTexture,
								flag);
		viewdata.F=save;
		RestoreClipFlags(pntCnt,pdp);
	}
	else CNearAddTileVerticesX2(pDirectD,
								pntCnt,
								totalTris,
								pdp,
								drwCnt,
								pdd,
								ubHTexture,
								flag);
}

void direct_3d::CNearAddTileVerticesX2(	struct _DirectDraw* pDirectD,
										ULong pntCnt,
										ULong totalTris,
										DoPointStruc* pdp,
										ULong drwCnt,
										UByte*& pdd,
										const HTEXT& ubHTexture,
										UWord flag)
{
	VIDRAMTEXTURE* pVrt;
	bool fIsHiRes=false;

	ULong dPntCnt,dTotalTris,dDrwCnt;
	DoPointStruc* dpdp;
	UByte* dpdd=NULL;

	ULong ht=ubHTexture();

	if (ht<NUM_256_TEXTURES)
	{
		pVrt=vidram256maps+ht;
		fIsHiRes=true;
		dPntCnt=pntCnt;
		dTotalTris=totalTris;
		dpdp=pdp;
		dDrwCnt=drwCnt;
		dpdd=pdd;
	}
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES)
		pVrt=vidram128maps+ht-NUM_256_TEXTURES;
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES)
		pVrt=vidram64maps+ht-NUM_256_TEXTURES-NUM_128_TEXTURES;
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES)
		pVrt=vidram32maps+ht-NUM_256_TEXTURES-NUM_128_TEXTURES-NUM_64_TEXTURES;
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES)
		pVrt=vidram16maps+ht-NUM_256_TEXTURES-NUM_128_TEXTURES-NUM_64_TEXTURES-NUM_32_TEXTURES;
	else if (ht<NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES+NUM_8_TEXTURES)
		pVrt=vidram8maps+ht-NUM_256_TEXTURES-NUM_128_TEXTURES-NUM_64_TEXTURES-NUM_32_TEXTURES-NUM_16_TEXTURES;
	else
		pVrt=NULL;

	D3DVALUE fMinTexelCoord,fMaxTexelCoord;

	fMinTexelCoord=.5/D3DVALUE(pVrt->dwWidth);
	fMaxTexelCoord=1.-fMinTexelCoord;
	
	UByte* pdrawdata=pdd;

	ULong interpFlag;

	interpFlag=	IF3D_TEXTURE+
				((globalSpecular)?IF3D_SPECULAR:0)+
				((globalLighting)?IF3D_COLOR:0);

	DoPointStruc* psdp=pdp;

	static UByte renumber[256];

	ULong pntEstimate=pntCnt+pntCnt+pntCnt;
	ULong trisEstimate=totalTris+totalTris;

	if (cnearlndXB.vertCount+pntEstimate>cnearlndXB._max_verts)
	{	
		FlushLandDraw(pDirectD,cnearlndXB);
	}
	else
	{	//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						(2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE))*drwCnt+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(cnearlndXB._inst_len-cnearlndXB.instOffset))
			FlushLandDraw(pDirectD,cnearlndXB);
	}

	//add to the current buffer

	ULong vBase=cnearlndXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)cnearlndXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)cnearlndXB.xbDesc.lpData)+cnearlndXB.instOffset);
	void* pistart=pinst;

	int renumberIndex=0;

	for (int srcPntIndex=0;srcPntIndex<pntCnt;srcPntIndex++,psdp++)
	{
		if (psdp->clipFlags==CF3D_NULL)
		{
			ptlvert->sx=D3DVALUE(psdp->bodyx.f);
			ptlvert->sy=D3DVALUE(psdp->bodyy.f);
			ptlvert->sz=D3DVALUE(psdp->bodyz.f);
			SetVertexColor(ptlvert,psdp);
			ptlvert->clipFlags=psdp->clipFlags|interpFlag;
			ptlvert->tu=SetTextureCoord(psdp->ix,fMinTexelCoord,fMaxTexelCoord);
			ptlvert->tv=SetTextureCoord(psdp->iy,fMinTexelCoord,fMaxTexelCoord);
			ptlvert++;
			renumber[srcPntIndex]=renumberIndex++;
		}
	}
	pntCnt=renumberIndex;

	D3DTEXTUREHANDLE hTexture=(pVrt!=NULL)?pVrt->d3dhTexture:NULL;

	OP_STATE_RENDER(1,pinst);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,hTexture,pinst);

	//Add the process vertices instruction but leave the
	//count field blank 'til later
	OP_PROCESS_VERTICES(1,pinst);
	D3DPROCESSVERTICES* ppv=(D3DPROCESSVERTICES*)pinst;
	ppv->dwFlags=D3DPROCESSVERTICES_COPY;
	ppv->wStart=ppv->wDest=vBase;
	ppv->dwReserved=0;
	pinst=(void*)(ppv+1);

	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	void* ptridatastart=pinst;

	static UByte wkspc[256];

	while (drwCnt--)
	{
		UByte at=*pdrawdata++;//skip colour byte
		ULong fanCount=*pdrawdata++;

		bool whichDraw=(flag!=2&&IsForest(at))?true:false;
		if (flag==1) whichDraw=whichDraw?false:true;

		if (whichDraw)
		{
			while (fanCount--)
			{
				ULong triCount=*pdrawdata++;
				pdrawdata+=2;
				while (triCount--) pdrawdata++;
			}
		}
		else
		while (fanCount--)
		{
			//reset index into temporary workspace
			ULong wkspcindex=0;

			//number of triangles in the fan
			ULong triCount=*pdrawdata++; 

			//fan base point
			UByte p1=*pdrawdata++;
			UByte p2;
			UByte p3=*pdrawdata++;

			//clip flags for fan base point
			UWord basecf=(pdp[p1].clipFlags&CF3D_ALL);
			UWord cfp2;
			UWord cfp3=(pdp[p3].clipFlags&CF3D_ALL);

			while (triCount--)
			{
				p2=p3;
				cfp2=cfp3;
				p3=*pdrawdata++;
				cfp3=(pdp[p3].clipFlags&CF3D_ALL);

				if ((CF3D_ALL&basecf&cfp2&cfp3)==CF3D_NULL)
				{
					//some of this triangle is visible
				 	if ((CF3D_ALL&(basecf|cfp2|cfp3))==CF3D_NULL)
					{
					 	//no clipping required for this triangle
						//add the triangle to the execute buffer

						OP_TRIANGLE_LIST(1,pinst);
						((D3DTRIANGLE*)pinst)->v1=vBase+renumber[p1];
						((D3DTRIANGLE*)pinst)->v2=vBase+renumber[p2];
						((D3DTRIANGLE*)pinst)->v3=vBase+renumber[p3];
						((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
						pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
					}
					else
					{
						//this triangle needs clipping

						ULong pc=3;

						R3DTLVERTEX tstore[64];
						R3DTLVERTEX* ptstore=tstore;
						R3DTLVERTEX* polydef[64];
						R3DTLVERTEX** pptlv=polydef;

						if (basecf&CF3D_ALL)
						{
							ptstore->sx=D3DVALUE(pdp[p1].bodyx.f);
							ptstore->sy=D3DVALUE(pdp[p1].bodyy.f);
							ptstore->sz=D3DVALUE(pdp[p1].bodyz.f);
							SetVertexColor(ptstore,pdp+p1);
							ptstore->clipFlags=pdp[p1].clipFlags|interpFlag;
							ptstore->tu=SetTextureCoord(pdp[p1].ix,fMinTexelCoord,fMaxTexelCoord);
							ptstore->tv=SetTextureCoord(pdp[p1].iy,fMinTexelCoord,fMaxTexelCoord);
							polydef[0]=ptstore++;
						}
						else
						{
						 	polydef[0]=ptlvstart+renumber[p1];
						}

						if (cfp2&CF3D_ALL)
						{
							ptstore->sx=D3DVALUE(pdp[p2].bodyx.f);
							ptstore->sy=D3DVALUE(pdp[p2].bodyy.f);
							ptstore->sz=D3DVALUE(pdp[p2].bodyz.f);
							SetVertexColor(ptstore,pdp+p2);
							ptstore->clipFlags=pdp[p2].clipFlags|interpFlag;
							ptstore->tu=SetTextureCoord(pdp[p2].ix,fMinTexelCoord,fMaxTexelCoord);
							ptstore->tv=SetTextureCoord(pdp[p2].iy,fMinTexelCoord,fMaxTexelCoord);
							polydef[1]=ptstore++;
						}
						else
						{
						 	polydef[1]=ptlvstart+renumber[p2];
						}

						if (cfp3&CF3D_ALL)
						{
							ptstore->sx=D3DVALUE(pdp[p3].bodyx.f);
							ptstore->sy=D3DVALUE(pdp[p3].bodyy.f);
							ptstore->sz=D3DVALUE(pdp[p3].bodyz.f);
							SetVertexColor(ptstore,pdp+p3);
							ptstore->clipFlags=pdp[p3].clipFlags|interpFlag;
							ptstore->tu=SetTextureCoord(pdp[p3].ix,fMinTexelCoord,fMaxTexelCoord);
							ptstore->tv=SetTextureCoord(pdp[p3].iy,fMinTexelCoord,fMaxTexelCoord);
							polydef[2]=ptstore++;
						}
						else
						{
						 	polydef[2]=ptlvstart+renumber[p3];
						}

						GenericPolyClip(pc,polydef,ptlvert,ptstore);

						if (pc>2)
						{
							int i=0;
							ULong tc=pc-2;
							OP_TRIANGLE_LIST(tc,pinst);
							int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
							int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
							int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
							tc--;
							((D3DTRIANGLE*)pinst)->v1=v1;
							((D3DTRIANGLE*)pinst)->v2=v2;
							((D3DTRIANGLE*)pinst)->v3=v3;
							((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
							pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

							while (tc--)
							{
								v2=v3;
								v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
								((D3DTRIANGLE*)pinst)->v1=v1;
								((D3DTRIANGLE*)pinst)->v2=v2;
								((D3DTRIANGLE*)pinst)->v3=v3;
								((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
								pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
							}
						}
					}
				}
			}
		}
	}

	//fix up half generated points...

	pntCnt=(ULong(ptlvert)-ULong(ptlvstart))>>5;

	ptlvert=ptlvstart;

	for (srcPntIndex=0;srcPntIndex<pntCnt;srcPntIndex++)
	{
		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert++;
	}

	ppv->dwCount=pntCnt;

	cnearlndXB.vertCount+=pntCnt;
	cnearlndXB.instOffset+=ULong(pinst)-ULong(pistart);
	pdd=pdrawdata;

	if (Save_Data.filtering==3 && fIsHiRes && flag!=1 && dpdd!=NULL)
		CNearAddTileDitherX(pDirectD,dPntCnt,dTotalTris,dpdp,dDrwCnt,dpdd,pntCnt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NearAddTileDitherX
//Author		Paul.   
//Date			Tue 1 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::NearAddTileDitherX(	struct _DirectDraw* pDirectD,
									ULong pntCnt,
									ULong totalTris,
									DoPointStruc* pdp,
									ULong drwCnt,
									UByte*& pdd)
{
	UByte* pdrawdata=pdd;

	if (ditherlndXB.vertCount+pntCnt>ditherlndXB._max_verts)
	{	
		FlushDitherDraw(pDirectD,ditherlndXB);
	}
	else
	{	//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*totalTris+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(ditherlndXB._inst_len-ditherlndXB.instOffset))
			FlushDitherDraw(pDirectD,ditherlndXB);
	}

	//add to the current buffer

	ULong vBase=ditherlndXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)ditherlndXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)ditherlndXB.xbDesc.lpData)+ditherlndXB.instOffset);
	void* pistart=pinst;

	for (int i=0;i<pntCnt;i++,pdp++,ptlvert++)
	{
		ptlvert->sx=D3DVALUE(pdp->bodyx.f);
		ptlvert->sy=D3DVALUE(pdp->bodyy.f);
		ptlvert->sz=D3DVALUE(pdp->bodyz.f);

		if (lightingEffectsEnabled)		SetVertexColor(ptlvert,pdp);
		else							ptlvert->color=AmbientLight;	//D3DCOLOR(0x00FFFFFF);

		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert->tu=pdp->ix*_ditherMapScale;
		ptlvert->tv=pdp->iy*_ditherMapScale;
	}

	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	while (drwCnt--)
	{
		UByte at=*pdrawdata++;
		D3DTEXTUREHANDLE hTexture=ditherHandles[at&AT_MASK];

		if (!IsForest(at) && hTexture)
		{
			OP_STATE_RENDER(1,pinst);
			STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,hTexture,pinst);
			OP_PROCESS_VERTICES(1,pinst);
			PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);

			ULong fanCnt=*pdrawdata++;
			while (fanCnt--){
				ULong triCnt=*pdrawdata++;
				OP_TRIANGLE_LIST(triCnt,pinst);
				int v1=vBase+*pdrawdata++;
				int v2=vBase+*pdrawdata++;
				int v3=vBase+*pdrawdata++;

				((D3DTRIANGLE*)pinst)->v1=v1;
				((D3DTRIANGLE*)pinst)->v2=v2;
				((D3DTRIANGLE*)pinst)->v3=v3;
				((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
				pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
				triCnt--;
				while (triCnt--)
				{
					v2=v3;
					v3=vBase+*pdrawdata++;
					((D3DTRIANGLE*)pinst)->v1=v1;
					((D3DTRIANGLE*)pinst)->v2=v2;
					((D3DTRIANGLE*)pinst)->v3=v3;
					((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
					pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
				}
			}
		}
		else
		{
			ULong fanCnt=*pdrawdata++;
			while (fanCnt--)
			{
				ULong triCnt=*pdrawdata++;
				pdrawdata++;
				pdrawdata++;
				pdrawdata++;
				triCnt--;
				while (triCnt--)	pdrawdata++;
			}
		}
	}
	ditherlndXB.vertCount+=pntCnt;
	ditherlndXB.instOffset+=ULong(pinst)-ULong(pistart);
	pdd=pdrawdata;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CNearAddTileDitherX
//Author		Paul.   
//Date			Tue 1 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::CNearAddTileDitherX(	struct _DirectDraw* pDirectD,
										ULong pntCnt,
										ULong totalTris,
										DoPointStruc* pdp,
										ULong drwCnt,
										UByte*& pdd,SLong clipCnt)
{
	VIDRAMTEXTURE* pVrt=&vidramdithermap;

	UByte* pdrawdata=pdd;

	ULong interpFlag;

	interpFlag=	IF3D_TEXTURE+
				((globalSpecular)?IF3D_SPECULAR:0)+
				((globalLighting)?IF3D_COLOR:0);

	DoPointStruc* psdp=pdp;

	static UByte renumber[256];

	ULong pntEstimate=pntCnt+pntCnt+pntCnt;
	ULong trisEstimate=totalTris+totalTris;

	if (cditherlndXB.vertCount+pntEstimate>cditherlndXB._max_verts)
	{	
		FlushDitherDraw(pDirectD,cditherlndXB);
	}
	else
	{	//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						(2*sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE))*drwCnt+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);
		if (totalSize>(cditherlndXB._inst_len-cditherlndXB.instOffset))
			FlushDitherDraw(pDirectD,cditherlndXB);
	}

	//add to the current buffer

	ULong vBase=cditherlndXB.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)cditherlndXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)cditherlndXB.xbDesc.lpData)+cditherlndXB.instOffset);
	void* pistart=pinst;

	int renumberIndex=0;

	for (int srcPntIndex=0;srcPntIndex<pntCnt;srcPntIndex++,psdp++)
	{
		if (psdp->clipFlags==CF3D_NULL)
		{
			ptlvert->sx=D3DVALUE(psdp->bodyx.f);
			ptlvert->sy=D3DVALUE(psdp->bodyy.f);
			ptlvert->sz=D3DVALUE(psdp->bodyz.f);
			SetVertexColor(ptlvert,psdp);
			ptlvert->clipFlags=psdp->clipFlags|interpFlag;
			ptlvert->tu=psdp->ix*_ditherMapScale;
			ptlvert->tv=psdp->iy*_ditherMapScale;
			ptlvert++;
			renumber[srcPntIndex]=renumberIndex++;
		}
	}
	pntCnt=renumberIndex;

	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	void* ptridatastart=pinst;

	static UByte wkspc[256];

	while (drwCnt--)
	{
		D3DTEXTUREHANDLE hTexture;
		UByte at=*pdrawdata++;
		hTexture=ditherHandles[at&AT_MASK];
		if (!IsForest(at) && hTexture)
		{
			OP_STATE_RENDER(1,pinst);
			STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,hTexture,pinst);
			OP_PROCESS_VERTICES(1,pinst);
			PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,clipCnt,pinst);

			ULong fanCount=*pdrawdata++;
		
			while (fanCount--)
			{
				//reset index into temporary workspace
				ULong wkspcindex=0;

				//number of triangles in the fan
				ULong triCount=*pdrawdata++; 

				//fan base point
				UByte p1=*pdrawdata++;
				UByte p2;
				UByte p3=*pdrawdata++;

				//clip flags for fan base point
				UWord basecf=(pdp[p1].clipFlags&CF3D_ALL);
				UWord cfp2;
				UWord cfp3=(pdp[p3].clipFlags&CF3D_ALL);

				while (triCount--)
				{
					p2=p3;
					cfp2=cfp3;
					p3=*pdrawdata++;
					cfp3=(pdp[p3].clipFlags&CF3D_ALL);

					if ((CF3D_ALL&basecf&cfp2&cfp3)==CF3D_NULL)
					{
						//some of this triangle is visible
					 	if ((CF3D_ALL&(basecf|cfp2|cfp3))==CF3D_NULL)
						{
					 	//no clipping required for this triangle
						//add the triangle to the execute buffer

							OP_TRIANGLE_LIST(1,pinst);
							((D3DTRIANGLE*)pinst)->v1=vBase+renumber[p1];
							((D3DTRIANGLE*)pinst)->v2=vBase+renumber[p2];
							((D3DTRIANGLE*)pinst)->v3=vBase+renumber[p3];
							((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
							pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
						}
						else
						{
							//this triangle needs clipping

							ULong pc=3;

							R3DTLVERTEX tstore[64];
							R3DTLVERTEX* ptstore=tstore;
							R3DTLVERTEX* polydef[64];
							R3DTLVERTEX** pptlv=polydef;

							if (basecf&CF3D_ALL)
							{
								ptstore->sx=D3DVALUE(pdp[p1].bodyx.f);
								ptstore->sy=D3DVALUE(pdp[p1].bodyy.f);
								ptstore->sz=D3DVALUE(pdp[p1].bodyz.f);
								SetVertexColor(ptstore,pdp+p1);
								ptstore->clipFlags=pdp[p1].clipFlags|interpFlag;
								ptstore->tu=pdp[p1].ix*_ditherMapScale;
								ptstore->tv=pdp[p1].iy*_ditherMapScale;
								polydef[0]=ptstore++;
							}
							else
							{
							 	polydef[0]=ptlvstart+renumber[p1];
							}

							if (cfp2&CF3D_ALL)
							{
								ptstore->sx=D3DVALUE(pdp[p2].bodyx.f);
								ptstore->sy=D3DVALUE(pdp[p2].bodyy.f);
								ptstore->sz=D3DVALUE(pdp[p2].bodyz.f);
								SetVertexColor(ptstore,pdp+p2);
								ptstore->clipFlags=pdp[p2].clipFlags|interpFlag;
								ptstore->tu=pdp[p2].ix*_ditherMapScale;
								ptstore->tv=pdp[p2].iy*_ditherMapScale;
								polydef[1]=ptstore++;
							}
							else
							{
							 	polydef[1]=ptlvstart+renumber[p2];
							}

							if (cfp3&CF3D_ALL)
							{
								ptstore->sx=D3DVALUE(pdp[p3].bodyx.f);
								ptstore->sy=D3DVALUE(pdp[p3].bodyy.f);
								ptstore->sz=D3DVALUE(pdp[p3].bodyz.f);
								SetVertexColor(ptstore,pdp+p3);
								ptstore->clipFlags=pdp[p3].clipFlags|interpFlag;
								ptstore->tu=pdp[p3].ix*_ditherMapScale;
								ptstore->tv=pdp[p3].iy*_ditherMapScale;
								polydef[2]=ptstore++;
							}
							else
							{
							 	polydef[2]=ptlvstart+renumber[p3];
							}

							GenericPolyClip(pc,polydef,ptlvert,ptstore);
					
							if (pc>2)
							{
								int i=0;
								ULong tc=pc-2;
								OP_TRIANGLE_LIST(tc,pinst);
								int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
								int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
								int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
								tc--;
								((D3DTRIANGLE*)pinst)->v1=v1;
								((D3DTRIANGLE*)pinst)->v2=v2;
								((D3DTRIANGLE*)pinst)->v3=v3;
								((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
								pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

								while (tc--)
								{
									v2=v3;
									v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
									((D3DTRIANGLE*)pinst)->v1=v1;
									((D3DTRIANGLE*)pinst)->v2=v2;
									((D3DTRIANGLE*)pinst)->v3=v3;
									((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
									pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
								}
							}
						}
					}
				}
			}
		}
		else
		{
			ULong fanCnt=*pdrawdata++;
			while (fanCnt--)
			{
				ULong triCnt=*pdrawdata++;
				pdrawdata++;
				pdrawdata++;
				pdrawdata++;
				triCnt--;
				while (triCnt--)	pdrawdata++;
			}
		}
	}

	//fix up half generated points...

	pntCnt=(ULong(ptlvert)-ULong(ptlvstart))>>5;

	ptlvert=ptlvstart;

	for (srcPntIndex=0;srcPntIndex<pntCnt;srcPntIndex++)
	{
		ptlvert->spec.a=CALC_RANGE_FOG(ptlvert->sx,ptlvert->sy,ptlvert->sz);
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*ptlvert->sz));
		ptlvert->sx=D3DVALUE(viewdata.scalex*ptlvert->sx*rw+viewdata.originx);
		CLIP_XVAL(ptlvert->sx)
		ptlvert->sy=D3DVALUE(-viewdata.scaley*ptlvert->sy*rw+viewdata.originy);
		CLIP_YVAL(ptlvert->sy)
		ptlvert->rhw=MAKE_RHW(ptlvert->sz);
		ptlvert->sz=MAKE_SZ(ptlvert->sz);	//*1.1f);
		ptlvert++;
	}

//	ppv->dwCount=pntCnt;

	cditherlndXB.vertCount+=pntCnt;
	cditherlndXB.instOffset+=ULong(pinst)-ULong(pistart);
	pdd=pdrawdata;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSurfaceDimensions
//Author		Jim Taylor
//Date			Mon 16 Nov 1998
//------------------------------------------------------------------------------
void direct_draw::GetSurfaceDimensions(DirectD* pdirectd,SLong& width,SLong& height)
{
	ROWANSURFACEDESC rsd;
	LockScr(pdirectd,&rsd);
	UnlockScr(pdirectd,&rsd);
	width=rsd.dwWidth;
	height=rsd.dwHeight;

//	LPDIRECTDRAWSURFACE lpdds;
//	DDSURFACEDESC	ddsd;
//	HRESULT hr;

//	ZeroMem(&ddsd,sizeof(DDSURFACEDESC));
//	ddsd.dwSize=sizeof(DDSURFACEDESC);

//	lpdds=pdirectd->lpDDSBack;

//	do
//	{
//		hr=lpdds->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
//	}
//	while (hr!=DD_OK);

//	lpdds->Unlock(ddsd.lpSurface);

//	width=ddsd.dwWidth;
//	height=ddsd.dwHeight;
}

void direct_3d::PutLine(DirectD* pDirectD,SWord sx,SWord sy,SWord ex,SWord ey,Colour c)
{
	const SLong _LineDataLen=	sizeof(D3DINSTRUCTION)+
								sizeof(D3DPROCESSVERTICES)+
								sizeof(D3DINSTRUCTION)+
								sizeof(D3DINSTRUCTION)+
								sizeof(D3DLINE);

	if (lineXB.vertCount+2>lineXB._max_verts ||
		_LineDataLen>(lineXB._inst_len-lineXB.instOffset))
	{
		FlushPLDraw(pDirectD,lineXB);
	}

	ULong vBase=lineXB.vertCount;

	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)lineXB.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)lineXB.xbDesc.lpData)+lineXB.instOffset);
	void* pistart=pinst;

	//get a pointer to the current input poly definition

	R3DTLVERTEX startVert,endVert;

	//this routine will not get called unless the line
	//is at least partly visible so prepare to clip if
	//needed

	R3DCOLOR shadePolyColor;
	*(D3DCOLOR*)&shadePolyColor=palette[c].dcColorVal;
	shadePolyColor.a=AmbientALPHA;

	startVert.sx=D3DVALUE(sx);
	startVert.sy=D3DVALUE(sy);
	startVert.sz=D3DVALUE(0);
	startVert.clipFlags=0;
	startVert.color=*(D3DCOLOR*)&shadePolyColor;

	endVert.sx=D3DVALUE(ex);
	endVert.sy=D3DVALUE(ey);
	endVert.sz=D3DVALUE(0);
	endVert.clipFlags=0;
	endVert.color=*(D3DCOLOR*)&shadePolyColor;

	*ptlvert++=startVert;
	*ptlvert=endVert;

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	*(D3DCOLOR*)&shadePolyColor=specularNULL;
	shadePolyColor.a=0xFF;

	for (int i=0;i<2;i++)
	{
		ptlvert->specular=*(D3DCOLOR*)&shadePolyColor;
		ptlvert->rhw=D3DVALUE(0.99999);
		ptlvert++;
	}

	OP_LINE_LIST(1,pinst);
	LPD3DLINE pD3DLine=(LPD3DLINE)pinst;
	pD3DLine->v1=vBase++;
	pD3DLine->v2=vBase++;
	pD3DLine++;
	pinst=(void*)pD3DLine;

	lineXB.vertCount=vBase;
	lineXB.instOffset+=ULong(pinst)-ULong(pistart);
}

void direct_3d::PutA(DirectD* pDirectD,ImageMapDesc* pmap,DoPointStruc* pdp)
{
	ULong interpFlag;

	interpFlag=	IF3D_TEXTURE+
				((globalSpecular)?IF3D_SPECULAR:0)+
				((globalLighting)?IF3D_COLOR:0);

	//check which type of texture we're looking at here...

	bool isMasked,hasAlpha,alphaOverride;

	D3DVALUE fWidth=D3DVALUE(pmap->w)*65536.;
	D3DVALUE fHeight=D3DVALUE(pmap->h)*65536.;

	alphaOverride=bool(globalAlphaValue!=AmbientALPHA);

	if (pmap->alpha)
	{
		hasAlpha=isMasked=true;
	}
	else
	{
	 	hasAlpha=false;
		isMasked=(pmap->isMasked)?true:false;
	}

	XXBuf* pxxb;

	pxxb=&fontXXB;

	XXBuf& xxb=*pxxb;

	//get an initial estimate of the number of points and polys
	ULong pntCnt=4;

 	ULong pntEstimate=4;
	ULong trisEstimate=2;

	UWord* pOffset;

	bool flushedDraw=false;

	//flush the current buffer contents if max no of
	//vertices/buffer will be exceeded

	if (xxb.vertCount+pntEstimate>xxb._max_verts)
	{
		FlushPTDraw(pDirectD,xxb);
		flushedDraw=true;
	}

	//flush the current buffer contents if max no of
	//faces/buffer will be exceeded

	if (!flushedDraw)
	{
		//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);

		if (totalSize>(xxb._inst_len-xxb.instOffset))
		{
			FlushPTDraw(pDirectD,xxb);
			flushedDraw=true;
		}
	}

	//flush the current buffer contents if texture record space is exceeded

	if (!flushedDraw)
	{
		if (!RecordTextureUse(pmap,pOffset,xxb.bufUse))
		{
			FlushPTDraw(pDirectD,xxb);
			RecordTextureUse(pmap,pOffset,xxb.bufUse);
		}
	}
	else RecordTextureUse(pmap,pOffset,xxb.bufUse);

	//there is definately enough room in the current execute buffer
	//to add the new polygon if required

	ULong vBase=xxb.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)xxb.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb.instOffset);
	void* pibase=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb._inst_start);
	void* pistart=pinst;

	//get a pointer to the current input poly definition
	//vertex** ppv=lpPolyType->lplpVertices;

	//initialise clipping flags...
	UWord orClip,andClip;
	orClip=CF3D_NULL;
	andClip=CF3D_ALL;

	R3DTLVERTEX tstore[64];
	R3DTLVERTEX* ptstore=tstore;
	R3DTLVERTEX* polydef[64];
	R3DTLVERTEX** pptlv=polydef;

	//this routine will not get called unless the polygon
	//is at least partly visible so prepare to clip if
	//needed

	R3DCOLOR shadePolyColor=*(R3DCOLOR*)&fontColour;
	R3DCOLOR specularPolyColor;

	for (int i=0;i<pntCnt;i++)
	{
		DoPointStruc* pv=pdp+i;

		*(ULong*)&specularPolyColor=specularNULL;

		//if the point is in the view cone then put
		//it straight into the current execute buffer

		ptlvert->sx=D3DVALUE(pv->bodyx.f);
		ptlvert->sy=D3DVALUE(pv->bodyy.f);
		ptlvert->sz=D3DVALUE(0);
		ptlvert->rhw=D3DVALUE(0.99999);
		ptlvert->color=*(D3DCOLOR*)&shadePolyColor;
		ptlvert->specular=*(D3DCOLOR*)&specularPolyColor;
		ptlvert->tu=D3DVALUE(pv->ix)/D3DVALUE(pmap->w);
		ptlvert->tv=D3DVALUE(pv->iy)/D3DVALUE(pmap->h);
		*pptlv++=ptlvert;
		ptlvert++;
	}
	//just on the off chance that something has
	//gone wrong (Not that it ever does!) check
	//the state of the clip flags and quit if
	//we need to

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	//stuff in render state changes here to get aliasing
	if (maskedTexture.bPalettized)
	{
		OP_STATE_RENDER(7,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_CLAMP,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATE,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,Driver[CurrDriver].tfFilterMSK,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,pinst);
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	}
	else
	{
		D3DTEXTUREBLEND	tbBlendMode=Driver[CurrDriver].tbBlendMode;
		OP_STATE_RENDER(9,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,tbBlendMode,pinst);
		STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_CLAMP,pinst);
		D3DTEXTUREFILTER tfFilterMAG=Driver[CurrDriver].tfFilterMAG;
		D3DTEXTUREFILTER tfFilterMIN=Driver[CurrDriver].tfFilterMIN;
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,tfFilterMAG,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,tfFilterMIN,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,pinst);
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	}

	//record location to store the texture handle for later
	OP_STATE_RENDER(1,pinst);
    void* poff=(void*)(ULong(pinst)+4);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
	*pOffset=UWord(ULong(poff)-ULong(pibase));

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);
	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	ULong triCnt=pntCnt-2;

	OP_TRIANGLE_LIST(triCnt,pinst);

	//first one first
	i=0;
	int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);

	triCnt--;

	((D3DTRIANGLE*)pinst)->v1=v1;
	((D3DTRIANGLE*)pinst)->v2=v2;
	((D3DTRIANGLE*)pinst)->v3=v3;
	((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
	pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

	while (triCnt--)
	{
		v2=v3;
		v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
	}
	if (maskedTexture.bPalettized)
	{
		OP_STATE_RENDER(7,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATE,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,FALSE,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,pinst);
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	}
	else
	{
		OP_STATE_RENDER(9,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND,D3DTBLEND_MODULATEALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA,pinst);
		STATE_DATA(D3DRENDERSTATE_BLENDENABLE,TRUE,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREADDRESS,D3DTADDRESS_WRAP,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMAG,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_TEXTUREMIN,D3DFILTER_NEAREST,pinst);
		STATE_DATA(D3DRENDERSTATE_SPECULARENABLE,globalSpecular,pinst);
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE,TRUE,pinst);
	}
	xxb.vertCount+=pntCnt;
	xxb.instOffset+=ULong(pinst)-ULong(pistart);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PutC
//Author		Paul
//Date			Mon 16 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::PutC(DirectD* pDirectD,ImageMapDesc* pmap,DoPointStruc* pdp,bool fRefresh)
{
	refreshTexture=fRefresh;

	ULong interpFlag;

	interpFlag=	IF3D_TEXTURE+
				((globalSpecular)?IF3D_SPECULAR:0)+
				((globalLighting)?IF3D_COLOR:0);

	//check which type of texture we're looking at here...

	bool isMasked,hasAlpha,alphaOverride;

	D3DVALUE fWidth=D3DVALUE(pmap->w)*65536.;
	D3DVALUE fHeight=D3DVALUE(pmap->h)*65536.;

	alphaOverride=bool(globalAlphaValue!=AmbientALPHA);

	if (pmap->alpha)
	{
		hasAlpha=isMasked=true;
	}
	else
	{
	 	hasAlpha=false;
		isMasked=(pmap->isMasked)?true:false;
	}

	XXBuf* pxxb;

	pxxb=&fontXXB;

	XXBuf& xxb=*pxxb;

	//get an initial estimate of the number of points and polys
	ULong pntCnt=4;

 	ULong pntEstimate=4;
	ULong trisEstimate=2;

	UWord* pOffset;

	bool flushedDraw=false;

	//flush the current buffer contents if max no of
	//vertices/buffer will be exceeded

	if (xxb.vertCount+pntEstimate>xxb._max_verts)
	{
		FlushPTDraw(pDirectD,xxb);
		flushedDraw=true;
	}

	//flush the current buffer contents if max no of
	//faces/buffer will be exceeded

	if (!flushedDraw)
	{
		//Work out how much space is needed for instruction data
		ULong totalSize=sizeof(D3DINSTRUCTION)+sizeof(D3DPROCESSVERTICES)+
						sizeof(D3DINSTRUCTION)+sizeof(D3DSTATE)+
						(sizeof(D3DINSTRUCTION)+sizeof(D3DTRIANGLE))*trisEstimate+
						sizeof(D3DINSTRUCTION);

		if (totalSize>(xxb._inst_len-xxb.instOffset))
		{
			FlushPTDraw(pDirectD,xxb);
			flushedDraw=true;
		}
	}

	//flush the current buffer contents if texture record space is exceeded

	if (!flushedDraw)
	{
		if (!RecordTextureUse(pmap,pOffset,xxb.bufUse))
		{
			FlushPTDraw(pDirectD,xxb);
			RecordTextureUse(pmap,pOffset,xxb.bufUse);
		}
	}
	else RecordTextureUse(pmap,pOffset,xxb.bufUse);

	//there is definately enough room in the current execute buffer
	//to add the new polygon if required

	ULong vBase=xxb.vertCount;
	R3DTLVERTEX* ptlvert=((R3DTLVERTEX*)xxb.xbDesc.lpData)+vBase;
	R3DTLVERTEX* ptlvstart=ptlvert;
	void* pinst=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb.instOffset);
	void* pibase=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb._inst_start);
	void* pistart=pinst;

	//get a pointer to the current input poly definition
	//vertex** ppv=lpPolyType->lplpVertices;

	//initialise clipping flags...
	UWord orClip,andClip;
	orClip=CF3D_NULL;
	andClip=CF3D_ALL;

	R3DTLVERTEX tstore[64];
	R3DTLVERTEX* ptstore=tstore;
	R3DTLVERTEX* polydef[64];
	R3DTLVERTEX** pptlv=polydef;

	//this routine will not get called unless the polygon
	//is at least partly visible so prepare to clip if
	//needed

	R3DCOLOR shadePolyColor=*(R3DCOLOR*)&fontColour;
	R3DCOLOR specularPolyColor;

	for (int i=0;i<pntCnt;i++)
	{
		DoPointStruc* pv=pdp+i;

		*(ULong*)&specularPolyColor=specularNULL;

		//if the point is in the view cone then put
		//it straight into the current execute buffer

		ptlvert->sx=D3DVALUE(pv->bodyx.f);
		ptlvert->sy=D3DVALUE(pv->bodyy.f);
		ptlvert->sz=D3DVALUE(0);
		ptlvert->rhw=D3DVALUE(0.99999);
		ptlvert->color=*(D3DCOLOR*)&shadePolyColor;
		ptlvert->specular=*(D3DCOLOR*)&specularPolyColor;
		ptlvert->tu=D3DVALUE(pv->ix)/D3DVALUE(pmap->w);
		ptlvert->tv=D3DVALUE(pv->iy)/D3DVALUE(pmap->h);
		*pptlv++=ptlvert;
		ptlvert++;
	}
	//just on the off chance that something has
	//gone wrong (Not that it ever does!) check
	//the state of the clip flags and quit if
	//we need to

	//do the body 2 screen style thing

	ptlvert=ptlvstart;

	//record location to store the texture handle for later
	OP_STATE_RENDER(1,pinst);
    void* poff=(void*)(ULong(pinst)+4);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
	*pOffset=UWord(ULong(poff)-ULong(pibase));

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,vBase,pntCnt,pinst);
	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	ULong triCnt=pntCnt-2;

	OP_TRIANGLE_LIST(triCnt,pinst);

	//first one first
	i=0;
	int v1=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v2=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
	int v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);

	triCnt--;

	((D3DTRIANGLE*)pinst)->v1=v1;
	((D3DTRIANGLE*)pinst)->v2=v2;
	((D3DTRIANGLE*)pinst)->v3=v3;
	((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_START;
	pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));

	while (triCnt--)
	{
		v2=v3;
		v3=vBase+((ULong(polydef[i++])-ULong(ptlvstart))>>5);
		((D3DTRIANGLE*)pinst)->v1=v1;
		((D3DTRIANGLE*)pinst)->v2=v2;
		((D3DTRIANGLE*)pinst)->v3=v3;
		((D3DTRIANGLE*)pinst)->wFlags=D3DTRIFLAG_EVEN;
		pinst=(void*)(ULong(pinst)+sizeof(D3DTRIANGLE));
	}

	xxb.vertCount+=pntCnt;
	xxb.instOffset+=ULong(pinst)-ULong(pistart);
	refreshTexture=false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateFromPrefs
//Author		Paul.   
//Date			Fri 20 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::UpdateFromPrefs()
{
}

extern int active_lines;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PeripheralBlob
//Author		Paul.   
//Date			Mon 23 Nov 1998
//------------------------------------------------------------------------------
void direct_3d::PeripheralBlob(Float* bx,Float* by,Float* bz,UByte intensity,SLong clipDelta)
{
	if (periphData.count==SPeripheralData::MAX_PERIPHERAL_POLYS)
		return;

	clipDelta=active_lines;
	ViewData localViewData=viewdata;
	Float delta=Float(clipDelta),halfClipDelta=Float(clipDelta>>1);
	localViewData.scaley-=halfClipDelta;
	localViewData.clipBot-=delta;
	localViewData.originy-=halfClipDelta;

//	Float localClipBot=localViewData.clipBot-Float(clipDelta);

	D3DVALUE sx,sy,sz,rw;
	const int pixel_width=16;

	sz=D3DVALUE(*bz);
	rw=D3DVALUE(1./(localViewData.hoD*sz));
	sx=D3DVALUE(localViewData.scalex**bx*rw+localViewData.originx);
	sy=D3DVALUE(-localViewData.scaley**by*rw+localViewData.originy);

	//reject any blobs that are on screen

	if (sx>localViewData.clipLft && sx<localViewData.clipRgt &&
		sy>localViewData.clipTop && sy<localViewData.clipBot)
		return;

	if (sx<localViewData.clipLft)
	{
		D3DVALUE frac=	D3DVALUE(localViewData.clipLft-localViewData.originx)/
						D3DVALUE(sx-localViewData.originx);

		sx=D3DVALUE(localViewData.clipLft);
		sy=D3DVALUE(localViewData.originy)+frac*D3DVALUE(sy-localViewData.originy);
	}
	else if (sx>localViewData.clipRgt)
	{
		D3DVALUE frac=	D3DVALUE(localViewData.clipRgt-localViewData.originx)/
						D3DVALUE(sx-localViewData.originx);

		sx=D3DVALUE(localViewData.clipRgt);
		sy=D3DVALUE(localViewData.originy)+frac*D3DVALUE(sy-localViewData.originy);
	}

	if (sy<localViewData.clipTop)
	{
		D3DVALUE frac=	D3DVALUE(localViewData.clipTop-localViewData.originy)/
						D3DVALUE(sy-D3DVALUE(localViewData.originy));

		sy=D3DVALUE(localViewData.clipTop);
		sx=D3DVALUE(localViewData.originx)+frac*D3DVALUE(sx-localViewData.originx);
	}
	else if (sy>localViewData.clipBot)
	{
		D3DVALUE frac=	D3DVALUE(localViewData.clipBot-localViewData.originy)/
						D3DVALUE(sy-D3DVALUE(localViewData.originy));

		sy=D3DVALUE(localViewData.clipBot);
		sx=D3DVALUE(localViewData.originx)+frac*D3DVALUE(sx-localViewData.originx);
	}

	D3DVALUE pw;

	pw=winmode_w/160;	//(intensity!=0)?D3DVALUE((pixel_width<<6)/intensity):pixel_width>>2;

	R3DCOLOR shadePolyColor;
	*(D3DCOLOR*)&shadePolyColor=palette[intensity].dcColorVal;
	shadePolyColor.a=AmbientALPHA;

	R3DTLVERTEX poly[4];

	poly[0].sx=sx-pw;
	poly[0].sy=sy-pw;
	poly[0].sz=0.;
	poly[0].rhw=.99999;
	poly[0].color=*(D3DCOLOR*)&shadePolyColor;
	poly[0].specular=specularNULL;
	poly[0].tu=0.;
	poly[0].tv=0.;

	poly[1].sx=sx+pw;
	poly[1].sy=sy-pw;
	poly[1].sz=0.;
	poly[1].rhw=.99999;
	poly[1].color=*(D3DCOLOR*)&shadePolyColor;
	poly[1].specular=specularNULL;
	poly[1].tu=1.;
	poly[1].tv=0.;

	poly[2].sx=sx+pw;
	poly[2].sy=sy+pw;
	poly[2].sz=0.;
	poly[2].rhw=.99999;
	poly[2].color=*(D3DCOLOR*)&shadePolyColor;
	poly[2].specular=specularNULL;
	poly[2].tu=1.;
	poly[2].tv=1.;

	poly[3].sx=sx-pw;
	poly[3].sy=sy+pw;
	poly[3].sz=0.;
	poly[3].rhw=.99999;
	poly[3].color=*(D3DCOLOR*)&shadePolyColor;
	poly[3].specular=specularNULL;
	poly[3].tu=0.;
	poly[3].tv=1.;

	UWord allflags=0;
	for (SLong i=0;i<4;i++)
	{
		if (poly[i].sx<localViewData.clipLft)		allflags|=1;
		else if (poly[i].sx>localViewData.clipRgt)	allflags|=2;
		if (poly[i].sy<localViewData.clipTop)		allflags|=4;
		else if (poly[i].sy>localViewData.clipBot)		allflags|=8;
	}

	//will only be off left,off right or no clip. The poly will never be
	//off the left and off the right of the screen at the same time

	if (allflags&1)
	{
		//vertices 0 & 3 need clipping, the rest don't
		D3DVALUE frac=(localViewData.clipLft-poly[0].sx)/(poly[1].sx-poly[0].sx);
		poly[0].sx=poly[3].sx=D3DVALUE(localViewData.clipLft);
		poly[0].tu+=frac*(poly[1].tu-poly[0].tu);
		poly[3].tu=poly[0].tu;
	}
	else if (allflags&2)
	{
		//vertices 2 & 3 need clipping, the rest don't
		D3DVALUE frac=(localViewData.clipRgt-poly[0].sx)/(poly[0].sx-poly[1].sx);
		poly[1].sx=poly[2].sx=D3DVALUE(localViewData.clipRgt);
		poly[2].tu=poly[1].tu=poly[0].tu+frac*(poly[1].tu-poly[0].tu);
	}

	//same thing applies to top & bottom clipping

	if (allflags&4)
	{
		//vertices 0 & 1 need clipping, the rest don't
		D3DVALUE frac=(localViewData.clipTop-poly[0].sy)/(poly[3].sy-poly[0].sy);
		poly[0].sy=poly[1].sy=D3DVALUE(localViewData.clipTop);
		poly[0].tv+=frac*(poly[3].tv-poly[0].tv);
		poly[1].tv=poly[0].tv;
	}
	else if (allflags&8)
	{
		//vertices 2 & 3 need clipping, the rest don't
		D3DVALUE frac=(localViewData.clipBot-poly[0].sy)/(poly[3].sy-poly[0].sy);
		poly[2].sy=poly[3].sy=D3DVALUE(localViewData.clipBot);
		poly[2].tv=poly[3].tv=poly[0].tv+frac*(poly[3].tv-poly[0].tv);
	}

	SLong index=periphData.count;
	periphData.polys[index].v[0]=poly[0];
	periphData.polys[index].v[1]=poly[1];
	periphData.polys[index].v[2]=poly[2];
	periphData.polys[index].v[3]=poly[3];
	periphData.count=++index;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMipMap
//Author		Paul.   
//Date			Tue 24 Nov 1998
//------------------------------------------------------------------------------
bool direct_3d::SetMipMap(bool fNew)
{
	bool fOld=fMipMapEnabled;
	fMipMapEnabled=fNew;
	return fOld;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDitherMap
//Author		Paul.   
//Date			Tue 1 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::CreateDitherMap(DirectD* pdirectd)
{
	ImageMapDescPtr pMap=Image_Map.GetImageMapPtr(DITHERNO);

	assert(pMap->w==pMap->h&&"Dither map must be square!");

	const SLong _ditherWH=pMap->w;
	const SLong _ditherMapSize=_ditherWH*_ditherWH;
	const SLong _ditherMipLevels=5;

	DDSCAPS scaps;
	LPDIRECTDRAW2 lpDD2;
	LPDIRECTDRAWSURFACE pSysDither,pVidDither;
	LPDIRECTDRAWSURFACE2 pSysDither2,pVidDither2,pTemp,pTempV;
	LPDIRECT3DTEXTURE pSysTex,pVidTex;
	D3DTEXTUREHANDLE hVidTex;

	scaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_MIPMAP;

	HRESULT hr;
	DDSURFACEDESC sd;
	sd=transpTexture.ddsd;
	sd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|
				DDSD_PIXELFORMAT|DDSD_CAPS|
				DDSD_MIPMAPCOUNT;
	sd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_SYSTEMMEMORY|
						DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
	sd.dwMipMapCount=_ditherMipLevels;	
	sd.dwWidth=sd.dwHeight=_ditherWH;

	lpDD2=pdirectd->lpDD2;

	hr=lpDD2->CreateSurface(&sd,&pSysDither,NULL);
	DIRECTDRAWERROR(hr);
	hr=pSysDither->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&pSysDither2);
	DIRECTDRAWERROR(hr);
	hr=pSysDither2->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&pSysTex);
	DIRECTDRAWERROR(hr);

	sd.ddsCaps.dwCaps=DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY|
						DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
	
	hr=lpDD2->CreateSurface(&sd,&pVidDither,NULL);
	DIRECTDRAWERROR(hr);
	hr=pVidDither->QueryInterface(IID_IDirectDrawSurface2,(LPVOID*)&pVidDither2);
	DIRECTDRAWERROR(hr);
	hr=pVidDither2->QueryInterface(IID_IDirect3DTexture,(LPVOID*)&pVidTex);
	DIRECTDRAWERROR(hr);
	hr=pVidTex->GetHandle(lpD3DDevice,&hVidTex);
	DIRECT3DERROR(hr);

	//fill the surface of the system memory texture with something

	UByte* pAlpha=pMap->alpha;
	assert(pAlpha!=NULL&&"Where's the transparency!");

	pTemp=pSysDither2;

	UWord alphaShift,alphaMask;

	alphaMask=((1<<transpTexture.AlphaBPP)-1)<<transpTexture.AlphaShift;
	alphaShift=transpTexture.AlphaShift-8+transpTexture.AlphaBPP;

	SLong thisSize=_ditherMapSize;
	SLong thisSkip=1;

	for (SLong y=0;y<_ditherMipLevels-1;y++)
	{
		do
		{
			hr=pTemp->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
		}
		while (hr!=DD_OK);

		UWord* pDst=(UWord*)sd.lpSurface;
		UByte* pSrc=pAlpha;

		for (SLong x=0;x<thisSize;x++)
		{
			UWord v=*pSrc;
			pSrc+=thisSkip;
			v<<=alphaShift;
			v&=alphaMask;
			*pDst++=v;
		}
		pTemp->Unlock(sd.lpSurface);

		pTemp->GetAttachedSurface(&scaps,&pTemp);

		thisSkip+=thisSkip;
		thisSize>>=2;
	}

	if (pTemp)
	{
		do
		{
			hr=pTemp->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
		}
		while (hr!=DD_OK);

		UWord* pDst=(UWord*)sd.lpSurface;
		
		for (SLong x=0;x<thisSize;x++,*pDst++=0);

		pTemp->Unlock(sd.lpSurface);
	}

	//copy the system memory version of the texture to the video memory
	//version

	DDBLTFX	bltfx;
	ZeroMem(&bltfx,sizeof(bltfx));
	bltfx.dwSize=sizeof(bltfx);

	pTemp=pSysDither2;
	pTempV=pVidDither2;

	while (pTemp)
	{
		pTempV->Blt(NULL,pTemp,NULL,DDBLT_WAIT,&bltfx);
		while (pTempV->GetBltStatus(DDGBS_ISBLTDONE)!=DD_OK) {}	
		pTemp->GetAttachedSurface(&scaps,&pTemp);
		pTempV->GetAttachedSurface(&scaps,&pTempV);
	}

	//release the system memory version of the texture

	RELEASE(pSysTex,hr);
	RELEASE(pSysDither2,hr);
	RELEASE(pSysDither,hr);

	//set up the structure containing the info about the video texture

	vidramdithermap.lpdds1TSurf=pVidDither;
	vidramdithermap.lpdds2TSurf=pVidDither2;
	vidramdithermap.lpd3dTexture=pVidTex;
	vidramdithermap.d3dhTexture=hVidTex;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderPeripheralBlobs
//Author		Paul.   
//Date			Tue 8 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::RenderPeripheralBlobs(struct _DirectDraw* pDirectD,
										struct XXBuf& xxb)
{
	UWord* pOffset;

	//record texture usage

	ImageMapDescPtr pmap=Image_Map.GetImageMapPtr(PERIPHNO);
	RecordTextureUse(pmap,pOffset,xxb.bufUse);

	//add vertices to the execute buffer...

	R3DTLVERTEX* ptlvert=(R3DTLVERTEX*)xxb.xbDesc.lpData;

	void* pinst=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb.instOffset);
	void* pibase=(void*)(((UByte*)xxb.xbDesc.lpData)+xxb._inst_start);
	void* pistart=pinst;

	SLong pntCnt=periphData.count;

	for (SLong x=0;x<pntCnt;x++)
	{
		*ptlvert++=periphData.polys[x].v[0];
		*ptlvert++=periphData.polys[x].v[1];
		*ptlvert++=periphData.polys[x].v[2];
		*ptlvert++=periphData.polys[x].v[3];
	}
	pntCnt<<=2;

	//add draw data to the execute buffer...

	OP_STATE_RENDER(1,pinst);
    void* poff=(void*)(ULong(pinst)+4);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE,NULL,pinst);
	*pOffset=UWord(ULong(poff)-ULong(pibase));

	OP_PROCESS_VERTICES(1,pinst);
	PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY,0,pntCnt,pinst);
	if (!(QWORD_ALIGNED(pinst))) {OP_NOP(pinst);}

	SLong triCnt=pntCnt>>1;

	OP_TRIANGLE_LIST(triCnt,pinst);

	D3DTRIANGLE* ptri=(D3DTRIANGLE*)pinst;

	for (x=0;x<periphData.count;x++)
	{
		SLong vind=x<<2;
		ptri->v1=vind;
		ptri->v2=vind+1;
		ptri->v3=vind+2;
		ptri->wFlags=D3DTRIFLAG_START;
		ptri++;
		ptri->v1=vind;
		ptri->v2=vind+2;
		ptri->v3=vind+3;
		ptri->wFlags=D3DTRIFLAG_EVEN;
		ptri++;
	}
	pinst=(void*)ptri;

	xxb.vertCount+=pntCnt;
	xxb.instOffset+=ULong(pinst)-ULong(pistart);

	FlushPTDraw(pDirectD,xxb);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EdgeOnTest
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
bool direct_3d::EdgeOnTest(LPPOLYTYPE pPoly,bool& fIsHz)
{
	Float EDGE_ON_FIDDLE;

	vertex** ppv=pPoly->lplpVertices;

	fpCOORDS3D a,b,n,nflat;

	EDGE_ON_FIDDLE=ppv[0]->bz.f;

	if (pPoly->ptType==PolyType::PT_MaskedImagem) return false;

	if (EDGE_ON_FIDDLE<5000) return false;

	if (EDGE_ON_FIDDLE>20000)	EDGE_ON_FIDDLE=.8;
	else						EDGE_ON_FIDDLE=1-.2*((EDGE_ON_FIDDLE-5000)/(20000-5000));

	a.X.f=ppv[0]->bx.f-ppv[1]->bx.f;
	a.Y.f=ppv[0]->by.f-ppv[1]->by.f;
	a.Z.f=ppv[0]->bz.f-ppv[1]->bz.f;

	b.X.f=ppv[2]->bx.f-ppv[1]->bx.f;
	b.Y.f=ppv[2]->by.f-ppv[1]->by.f;
	b.Z.f=ppv[2]->bz.f-ppv[1]->bz.f;

	n.X.f=(a.Y.f*b.Z.f)-(b.Y.f*a.Z.f);
	n.Y.f=(a.Z.f*b.X.f)-(b.Z.f*a.X.f);
	n.Z.f=(a.X.f*b.Y.f)-(b.X.f*a.Y.f);

	nflat=n; nflat.Z.f=0;

	//n.nflat=|n||nflat|cos(theta)

	Float nDotNflat=(n.X.f*nflat.X.f)+(n.Y.f*nflat.Y.f); //+0 'cos nflat.Z.f==0.

	Float sqMag,mag;

	//first, generate the magnitude of nflat

	sqMag=nflat.X.f*nflat.X.f;

	mag=nflat.Y.f*nflat.Y.f;

	fIsHz=sqMag>mag?true:false;	//more horizontal than vertical test

	sqMag+=mag;

	_asm
	{
	fld sqMag;
	fsqrt;
	fstp mag;
	}

	sqMag+=n.Z.f*n.Z.f;

	_asm
	{
	fld sqMag;
	fsqrt;
	fstp sqMag;
	}

	mag*=sqMag;

	nDotNflat/=mag;

	if (nDotNflat>EDGE_ON_FIDDLE) return true;

	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddLineInstead
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::AddLineInstead(DirectDP pDirectD,LPPOLYTYPE pPoly,bool fHorizontal)
{
	vertex** ppv=pPoly->lplpVertices;

	vertex *pMinV,*pMaxV;

	D3DVALUE min_c,max_c;

	vertex* pv=*ppv++;

	min_c=fHorizontal?pv->by.f:pv->bx.f;
	max_c=min_c/=pv->bz.f;
	pMinV=pMaxV=pv;

	for (SLong x=1;x<pPoly->points;x++)
	{
		pv=*ppv++;

		D3DVALUE this_c=fHorizontal?pv->by.f:pv->bx.f;

		this_c/=pv->bz.f;

		if (this_c<min_c)
		{
			min_c=this_c;
			pMinV=pv;
		}
		else if (this_c>max_c)
		{
			max_c=this_c;
			pMaxV=pv;
		}
	}

	//render the line between pMinV & pMaxV...

	LINETYPE ltype;

	ltype.ltType=LineType::LT_PlainColour;
	ltype.lpStartVertex=pMinV;
	ltype.lpEndVertex=pMaxV;

	if (pPoly->ptType<=PolyType::PT_ShadeColour)
		ltype.colour=pPoly->colour;
	else
		ltype.colour=Colour(pPoly->lpImageMap->body[0]);

	AddPlainLine(pDirectD,&ltype);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetEdgeTest
//Author		Paul.   
//Date			Thu 10 Dec 1998
//------------------------------------------------------------------------------
bool direct_3d::SetEdgeTest(bool fNew)
{
	bool fLast=fEdgeTestActive;
	fEdgeTestActive=fNew;
	return fLast;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GammaCorr
//Author		Paul.   
//Date			Wed 23 Dec 1998
//------------------------------------------------------------------------------
void direct_3d::GammaCorr(UByte& r,UByte& g,UByte& b)
{
	double gamma_value=gamma_values[Save_Data.gammacorrection];
	R3DPal pe;
	pe.r=r; pe.g=g; pe.b=b;
	GammaCorrectRGB(&pe,gamma_value);
	r=pe.r; g=pe.g; b=pe.b;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AvailableTextureRAM
//Author		Paul.   
//Date			Wed 20 Jan 1999
//------------------------------------------------------------------------------
ULong direct_3d::AvailableTextureRAM(struct _DirectDraw* pDirectD)
{
	struct TextureRec
	{
 		LPDIRECTDRAWSURFACE pDDS;
		LPDIRECTDRAWSURFACE2 pDDS2;
		LPDIRECT3DTEXTURE pD3DT;
	};

	HRESULT dderrval;

	const SLong _textureWH=64;
	const SLong _textureRecs=1024;

	TextureRec* tr=new TextureRec[_textureRecs];

	const DWORD dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;

	D3DAppTextureFormat& curFmt=transpTexture;
	DDSURFACEDESC tmsd=curFmt.ddsd;

	tmsd.dwWidth=tmsd.dwHeight=_textureWH;
	tmsd.dwFlags=dwFlags;
	tmsd.ddsCaps.dwCaps=DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY;

	SLong texturesAllocated=0;

	for (;;)
	{
		dderrval=
		pDirectD->lpDD2->CreateSurface(&tmsd,&tr[texturesAllocated].pDDS,NULL);

		if (dderrval!=DD_OK) break;

		dderrval=
		tr[texturesAllocated].pDDS->QueryInterface(IID_IDirectDrawSurface2,
			(LPVOID*)&tr[texturesAllocated].pDDS2);
	
		if (dderrval!=DD_OK)
		{
			RELEASE(tr[texturesAllocated].pDDS,dderrval);
			break;
		}
	
		dderrval=
		tr[texturesAllocated].pDDS2->QueryInterface(IID_IDirect3DTexture,
			(LPVOID*)&tr[texturesAllocated].pD3DT);

		if (dderrval!=DD_OK)
		{
			RELEASE(tr[texturesAllocated].pDDS2,dderrval);
			RELEASE(tr[texturesAllocated].pDDS,dderrval);
			break;
		}
		texturesAllocated++;

		if (texturesAllocated==_textureRecs)
			break;
	}

	for (SLong x=0;x<texturesAllocated;x++)
	{
		RELEASE(tr[x].pDDS2,dderrval);
		RELEASE(tr[x].pDDS,dderrval);
		RELEASE(tr[x].pD3DT,dderrval);
	}

	delete[]tr;

	ULong textureRAMavail=	texturesAllocated*
							_textureWH*
							_textureWH*
							(tmsd.ddpfPixelFormat.dwRGBBitCount>>3);

	return textureRAMavail;
}

typedef struct tagSCREENRECORD
{
	struct tagSCREENRECORD* pNext;
	UByteP pBufferDat;
}
SCREENRECORD,*LPSCREENRECORD;

typedef struct tagVIDEOBUFFER
{
	enum {NUM_RECORDS=120};		//for 80Mb machine
//	enum {NUM_RECORDS=81};		//for 80Mb machine
//	enum {NUM_RECORDS=163};		//for 128Mb machine
//	enum {NUM_RECORDS=382};		//for 256Mb machine
	SLong noRecs;
	SLong frameCounter;
	SLong bufferSizeInBytes;
	SLong imageWidth;
	SLong imageHeight;
	ULong redMask;
	ULong greenMask;
	ULong blueMask;
	SLong redShift;
	SLong greenShift;
	SLong blueShift;
	SLong redBits;
	SLong greenBits;
	SLong blueBits;
	LPSCREENRECORD pHead,pTail;
	LPSCREENRECORD pBegin,pInsert;
}
VIDEOBUFFER,*LPVIDEOBUFFER;

static LPVIDEOBUFFER pVideoBuf=NULL;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitialiseVideoBuffer
//Author		Paul.   
//Date			Mon 8 Feb 1999
//------------------------------------------------------------------------------
void direct_3d::InitialiseVideoBuffer(DirectDP pdirectd)
{
	if (!videoBuffer) return;
	HRESULT hr;
	DDSURFACEDESC sd;
	ZeroMem(&sd,sizeof(DDSURFACEDESC));
	sd.dwSize=sizeof(DDSURFACEDESC);
	pVideoBuf=new VIDEOBUFFER;
	pVideoBuf->noRecs=VIDEOBUFFER::NUM_RECORDS;
	pVideoBuf->frameCounter=0;

	//get surface information from the back buffer...
	do{hr=pdirectd->lpDDSBack->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);}
	while (hr!=DD_OK);

	pdirectd->lpDDSBack->Unlock(sd.lpSurface);

	const SLong _BufferSizeInBytes=sd.dwWidth*sd.dwHeight*(sd.ddpfPixelFormat.dwRGBBitCount>>3);

	pVideoBuf->bufferSizeInBytes=_BufferSizeInBytes;
	pVideoBuf->imageWidth=sd.dwWidth;
	pVideoBuf->imageHeight=sd.dwHeight;

	LPSCREENRECORD pLast;

	for (SLong i=0;i<pVideoBuf->noRecs;i++)
	{
		LPSCREENRECORD pSR=new SCREENRECORD;

		if (i==0)							pVideoBuf->pHead=pSR;
		else
		{
			if (i==pVideoBuf->noRecs-1)	pVideoBuf->pTail=pSR;
			pLast->pNext=pSR;
		}
		pLast=pSR;
		pSR->pBufferDat=new UByte[_BufferSizeInBytes];
	}

	//make into a circular linked list...
	pLast->pNext=pVideoBuf->pHead;
	pVideoBuf->pBegin=pVideoBuf->pHead;
	pVideoBuf->pInsert=NULL;

	//set up red, green and blue values for colour conversion later...
	pVideoBuf->redMask=sd.ddpfPixelFormat.dwRBitMask;
	pVideoBuf->greenMask=sd.ddpfPixelFormat.dwGBitMask;
	pVideoBuf->blueMask=sd.ddpfPixelFormat.dwBBitMask;

	SLong shift,bits;
	ULong mask;

	for (shift=0,mask=pVideoBuf->redMask;!(mask&1);shift++,mask>>=1){}
	for (bits=0;mask&1;bits++,mask>>=1) {}
	pVideoBuf->redShift=shift;
	pVideoBuf->redBits=8-bits;

	for (shift=0,mask=pVideoBuf->greenMask;!(mask&1);shift++,mask>>=1){}
	for (bits=0;mask&1;bits++,mask>>=1) {}
	pVideoBuf->greenShift=shift;
	pVideoBuf->greenBits=8-bits;

	for (shift=0,mask=pVideoBuf->blueMask;!(mask&1);shift++,mask>>=1){}
	for (bits=0;mask&1;bits++,mask>>=1) {}
	pVideoBuf->blueShift=shift;
	pVideoBuf->blueBits=8-bits;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseVideoBuffer
//Author		Paul.   
//Date			Mon 8 Feb 1999
//------------------------------------------------------------------------------
void direct_3d::ReleaseVideoBuffer()
{
	if (!videoBuffer) return;
	if (pVideoBuf)
	{
		LPSCREENRECORD pSR=pVideoBuf->pHead;
		for (SLong i=0;i<pVideoBuf->noRecs;i++)
		{
			LPSCREENRECORD pNextSR;
			pNextSR=pSR->pNext;
			delete[]pSR->pBufferDat;
			delete pSR;
			pSR=pNextSR;
		}
		delete pVideoBuf;
		pVideoBuf=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CaptureScreen
//Author		Paul.   
//Date			Mon 8 Feb 1999
//------------------------------------------------------------------------------
void direct_3d::CaptureScreen(DirectDP pdirectd)
{
	if (!videoBuffer) return;
	HRESULT hr;
	DDSURFACEDESC ssd;
	ZeroMem(&ssd,sizeof(DDSURFACEDESC));
	ssd.dwSize=sizeof(DDSURFACEDESC);
	if (pVideoBuf)
	{
		//first step is to locate the correct place to insert the new screen shot
		LPSCREENRECORD pIns;
		pIns=pVideoBuf->pInsert;
		if (pIns)
		{
			if (pIns==pVideoBuf->pBegin) pVideoBuf->pBegin=pIns->pNext;
		}
		else pIns=pVideoBuf->pBegin;

		pVideoBuf->pInsert=pIns->pNext;

 		//pdirectd->lpDDSBack is the source buffer to grab. Lock the surface and
		//get a surface memory pointer
		do{hr=pdirectd->lpDDSBack->Lock(NULL,&ssd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);}
		while (hr!=DD_OK);

		//copy data from one surface to the other...
	 	ULong *pSrc,*pDst;

		pSrc=(ULong*)ssd.lpSurface;
		pDst=(ULong*)pIns->pBufferDat;

		const SLong _WidthInLongs=(ssd.dwWidth*(ssd.ddpfPixelFormat.dwRGBBitCount>>3))>>2;
		const SLong _SourcePitchInLongs=ssd.lPitch>>2;

		if (_SourcePitchInLongs)
			for (SLong y=0;y<ssd.dwHeight;y++)
			{
				ULong* pSrc2=pSrc;
				for (SLong x=0;x<_WidthInLongs;x++,*pDst++=*pSrc2++) {}
				pSrc+=_SourcePitchInLongs;
			}
		else
		{
			ULong dataLen=_WidthInLongs*ssd.dwHeight;
			while (dataLen--) *pDst++=*pSrc++;
		}
		pdirectd->lpDDSBack->Unlock(ssd.lpSurface);
	}
	else InitialiseVideoBuffer(pdirectd);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveVideoBuffer
//Author		Paul.   
//Date			Mon 8 Feb 1999
//------------------------------------------------------------------------------
void direct_3d::SaveVideoBuffer(DirectDP pdirectd)
{
	if (!videoBuffer) return;
	static char UFileName[8+1+3+1];
	//saves the current contents of the video buffer from pBegin up to but not including
	//pInsert
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	bmfh.bfType=0x4D42;
	bmfh.bfSize=sizeof(BITMAPFILEHEADER)+
				sizeof(BITMAPINFOHEADER)+
				(3*pVideoBuf->imageWidth*pVideoBuf->imageHeight);
	bmfh.bfReserved1=bmfh.bfReserved2=0;
	bmfh.bfOffBits=sizeof(BITMAPFILEHEADER)+
					sizeof(BITMAPINFOHEADER);

	bmih.biSize=sizeof(BITMAPINFOHEADER);
	bmih.biWidth=pVideoBuf->imageWidth;
	bmih.biHeight=pVideoBuf->imageHeight;
	bmih.biPlanes=1;
	bmih.biBitCount=24;
	bmih.biCompression=BI_RGB;
	bmih.biSizeImage=(3*pVideoBuf->imageWidth*pVideoBuf->imageHeight);
	bmih.biXPelsPerMeter=
		bmih.biYPelsPerMeter=0;
	bmih.biClrUsed=0;
	bmih.biClrImportant=0;

	const SLong _ScanWidth=pVideoBuf->imageWidth*3;

	UByte* scanLine=new UByte[_ScanWidth];

	if (pVideoBuf && pVideoBuf->pInsert)
	{
		LPSCREENRECORD pCur=pVideoBuf->pBegin;
		const LPSCREENRECORD pFin=pVideoBuf->pInsert;
		ULong uid=pVideoBuf->frameCounter;

		do
		{
			_Miles.PlaySample(FIL_SFX_NO_AMMO_CLICK, 5120);
			//make unique filenames
			sprintf(UFileName,"%08d.BMP",uid++);
			FILE* f=fopen(UFileName,"wb");

			//write header information
			fwrite(&bmfh,1,sizeof(bmfh),f);
			fwrite(&bmih,1,sizeof(bmih),f);

			//get a surface memory pointer for the direct draw surface being written
			UWord* pSrc=((UWord*)pCur->pBufferDat)+
						(pVideoBuf->imageWidth*(pVideoBuf->imageHeight-1));

			//convert & write the image one scanline at a time

			for (SLong y=0;y<pVideoBuf->imageHeight;y++)
			{
				UByte* pDst=scanLine;

				for (SLong x=0;x<pVideoBuf->imageWidth;x++)
				{
					UWord inval,cval;

					inval=*pSrc++;

					cval=((inval&pVideoBuf->blueMask)>>pVideoBuf->blueShift)<<pVideoBuf->blueBits;
					*pDst++=UByte(cval);

					cval=((inval&pVideoBuf->greenMask)>>pVideoBuf->greenShift)<<pVideoBuf->greenBits;
					*pDst++=UByte(cval);

					cval=((inval&pVideoBuf->redMask)>>pVideoBuf->redShift)<<pVideoBuf->redBits;
					*pDst++=UByte(cval);
				}
				fwrite(scanLine,1,_ScanWidth,f);
				pSrc-=pVideoBuf->imageWidth;
				pSrc-=pVideoBuf->imageWidth;
			}
			fclose(f);
			pCur=pCur->pNext;
		}
		while (pCur!=pFin);
		pVideoBuf->frameCounter=uid;
	}
	delete[]scanLine;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		D2DLine
//Author		Paul.   
//Date			Wed 17 Feb 1999
//------------------------------------------------------------------------------
void direct_3d::D2DLine(struct _DirectDraw* pdirectd,UWord x1,UWord y1,UWord x2,UWord y2)
{

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShowLoaderArt
//Author		Paul    
//Date			Sat 20 Feb 1999
//------------------------------------------------------------------------------
void direct_3d::ShowLoaderArt(struct _DirectDraw* pdirectd,void* pData)
{
	BITMAPFILEHEADER* bmf=(BITMAPFILEHEADER*)pData;
	UByte* pArt=((UByte*)pData)+bmf->bfOffBits;
	bmf++;
	BITMAPINFO* bmi=(BITMAPINFO*)bmf;
	RGBQUAD* pal=bmi->bmiColors;
	HRESULT hr;
	DDSURFACEDESC sd;
	ZeroMem(&sd,sizeof(DDSURFACEDESC));
	sd.dwSize=sizeof(DDSURFACEDESC);

	//get surface information from the back buffer...
	do{hr=pdirectd->lpDDSBack->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);}
	while (hr!=DD_OK);
	pdirectd->lpDDSBack->Unlock(sd.lpSurface);

	SLong shift,bits;
	ULong mask;

	SWord redBits,greenBits,blueBits;
	SWord redShift,greenShift,blueShift;
	UWord redMask,greenMask,blueMask;

	redMask=sd.ddpfPixelFormat.dwRBitMask;
	greenMask=sd.ddpfPixelFormat.dwGBitMask;
	blueMask=sd.ddpfPixelFormat.dwBBitMask;

	for (shift=0,mask=redMask;!(mask&1);shift++,mask>>=1){}
	for (bits=0;mask&1;bits++,mask>>=1) {}
	redShift=shift;
	redBits=8-bits;

	for (shift=0,mask=greenMask;!(mask&1);shift++,mask>>=1){}
	for (bits=0;mask&1;bits++,mask>>=1) {}
	greenShift=shift;
	greenBits=8-bits;

	for (shift=0,mask=blueMask;!(mask&1);shift++,mask>>=1){}
	for (bits=0;mask&1;bits++,mask>>=1) {}
	blueShift=shift;
	blueBits=8-bits;

	//the input image is always 800x600
	//if the screen resolution is lower than or equal to 800x600 then 
	//	the image is centered and clipped
	//if the screen resolution is greater than 800x600 then the image is 
	//	drawn in the lower right corner of the screen

	if (sd.dwWidth>800 && sd.dwHeight>600)
	{
		pArt+=599*800;	//bottom up image

		do{hr=pdirectd->lpDDSBack->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);}
		while (hr!=DD_OK);
		{
			UWord red=(pal[*pArt].rgbRed>>redBits)<<redShift;
			UWord green=(pal[*pArt].rgbGreen>>greenBits)<<greenShift;
			UWord blue=(pal[*pArt].rgbBlue>>blueBits)<<blueShift;
			UWord fillCol=0;	//red|green|blue;

			UByte* pDst=(UByte*)sd.lpSurface;

			for (SLong i=0;i<sd.dwHeight;i++)
			{
				UWord* pDst2=(UWord*)pDst;
				pDst+=sd.lPitch;
				for (SLong j=0;j<sd.dwWidth;j++,*pDst2++=fillCol) {}
			}
		}
		pdirectd->lpDDSBack->Unlock(sd.lpSurface);

		//get surface information from the back buffer...
		do{hr=pdirectd->lpDDSBack->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);}
		while (hr!=DD_OK);

		//copy the bitmap data onto the screen

		UByte* pSrc=pArt;
		UByte* pDst=(UByte*)sd.lpSurface;

		SLong xoff=(sd.dwWidth-800)>>1;
		SLong yoff=(sd.dwHeight-600)>>1;

		pDst+=(xoff*2)+(sd.lPitch*yoff);

		for (SLong i=yoff;i<yoff+600;i++)
		{
			UByte* pSrc2=pSrc;
			UWord* pDst2=(UWord*)pDst;
			pSrc-=800;
			pDst+=sd.lPitch;
			for (SLong j=xoff;j<xoff+800;j++,pSrc2++,pDst2++)
			{
				UWord red=(pal[*pSrc2].rgbRed>>redBits)<<redShift;
				UWord green=(pal[*pSrc2].rgbGreen>>greenBits)<<greenShift;
				UWord blue=(pal[*pSrc2].rgbBlue>>blueBits)<<blueShift;
				*pDst2=red|green|blue;
			}
		}
		pdirectd->lpDDSBack->Unlock(sd.lpSurface);
	}
	else
	{
		do{hr=pdirectd->lpDDSBack->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);}
		while (hr!=DD_OK);

		UByte* pDst=(UByte*)sd.lpSurface;

		SLong xoff=(800-sd.dwWidth)>>1;
		SLong yoff=(600-sd.dwHeight)>>1;

		for (SLong i=0;i<sd.dwHeight;i++)
		{
			UWord* pDst2=(UWord*)pDst;
			pDst+=sd.lPitch;
			UByte* pSrc2=pArt+(599-i-yoff)*800+xoff;
			for (SLong j=0;j<sd.dwWidth;j++,pSrc2++,pDst2++)
			{
				UWord red=(pal[*pSrc2].rgbRed>>redBits)<<redShift;
				UWord green=(pal[*pSrc2].rgbGreen>>greenBits)<<greenShift;
				UWord blue=(pal[*pSrc2].rgbBlue>>blueBits)<<blueShift;
				*pDst2=red|green|blue;
			}
		}
		pdirectd->lpDDSBack->Unlock(sd.lpSurface);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSmackerMode
//Author		Paul.   
//Date			Mon 15 Mar 1999
//------------------------------------------------------------------------------
void direct_draw::SetSmackerMode(bool flag,HWND)
{
	//flag == true ... set mode 
	//	   == false .. restore mode

//#ifdef NDEBUG
	if (flag)
	{
		DEVMODE dmMode;
		memset(&dmMode,0,sizeof(DEVMODE));
		dmMode.dmSize=sizeof(DEVMODE);
		for (int i=0,f=0;(f=EnumDisplaySettings(NULL,i,&dmMode));i++)
			if (dmMode.dmPelsWidth==640 &&
				dmMode.dmPelsHeight==480)
				break;
		if (f)
		{
	 		dmMode.dmFields=DM_PELSWIDTH+DM_PELSHEIGHT;
			ChangeDisplaySettings(&dmMode,CDS_FULLSCREEN);
		}
//Old_Code PD 17Aug99 		DEVMODE dmMode;
//Old_Code PD 17Aug99 		dmMode.dmSize=sizeof(DEVMODE);
//Old_Code PD 17Aug99 		dmMode.dmDriverExtra=0;
//Old_Code PD 17Aug99 		dmMode.dmPelsWidth=640;
//Old_Code PD 17Aug99 		dmMode.dmPelsHeight=480;
//Old_Code PD 17Aug99 		dmMode.dmFields=DM_PELSWIDTH+DM_PELSHEIGHT;
//Old_Code PD 17Aug99 		ChangeDisplaySettings(&dmMode,CDS_FULLSCREEN);
	}
	else ChangeDisplaySettings(NULL,0);
//#endif
}

bool direct_3d::PolySplit(LPPOLYTYPE pIn)
{
	bool fHadTrue=false;
	bool fHadFalse=false;
	vertex **ppv=pIn->lplpVertices,*pv;
	for (int i=pIn->points-1;i>=0;i--)
	{
		pv=*ppv++;
		bool fThis=(pv->bz.f<=fZBufScaleSwitchRange)?true:false;
		if (!fHadFalse && !fThis) {if (fHadTrue) return true; fHadFalse=true;}
		if (!fHadTrue && fThis) {if (fHadFalse) return true; fHadTrue=true;}
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PolyCross
//Author		Paul.   
//Date			Fri 9 Apr 1999
//------------------------------------------------------------------------------
bool direct_3d::PolyCross(LPPOLYTYPE pPoly)
{
	const D3DVALUE ABIT=10*1.192092896e+07F;
	D3DVALUE sx[3],sy[3];
	vertex	**ppv=pPoly->lplpVertices,*pv;
	for (int i=0;i<3;i++)
	{
		pv=*ppv++;
		D3DVALUE rw=D3DVALUE(1./(viewdata.hoD*pv->bz.f));
		if (rw<0.) rw=-rw;
 		sx[i]=D3DVALUE(viewdata.scalex*pv->bx.f*rw+viewdata.originx);
		sy[i]=D3DVALUE(-viewdata.scaley*pv->by.f*rw+viewdata.originy);
	}
	sx[0]-=sx[1];
	sx[2]-=sx[1];
	sy[0]-=sy[1];
	sy[2]-=sy[1];
	if (sx[0]*sy[2]-sy[0]*sx[2]<=ABIT)
		return true;

	return false;
}

void direct_draw::LockScr(struct _DirectDraw* pdirectd,ROWANSURFACEDESC* rsd)
{
	if (lockLevel==0)
	{
		HRESULT hr;
		DDSURFACEDESC sd;
		ZeroMem(&sd,sizeof(DDSURFACEDESC));
		sd.dwSize=sizeof(DDSURFACEDESC);

		do{hr=pdirectd->lpDDSBack->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);}
		while (hr!=DD_OK);
		rsdGlobal.lpSurface=sd.lpSurface;
		rsdGlobal.dwWidth=sd.dwWidth;
		rsdGlobal.dwHeight=sd.dwHeight;
		rsdGlobal.lPitch=sd.lPitch;
		rsdGlobal.dwRGBBitCount=sd.ddpfPixelFormat.dwRGBBitCount;
	}
	lockLevel++;
	*rsd=rsdGlobal;
}

void direct_draw::UnlockScr(struct _DirectDraw* pdirectd,ROWANSURFACEDESC* rsd)
{
	lockLevel--;
	if (lockLevel==0)
		pdirectd->lpDDSBack->Unlock(rsd->lpSurface);
}

void direct_draw::GetColourInfo(struct _DirectDraw* pdirectd,
								UWord& redMask,SWord& redShift1,SWord& redShift2,
								UWord& greenMask,SWord& greenShift1,SWord& greenShift2,
								UWord& blueMask,SWord& blueShift1,SWord& blueShift2)
{
	if (!gotShifts)
	{
		HRESULT hr;
		DDSURFACEDESC sd;
		ZeroMem(&sd,sizeof(DDSURFACEDESC));
		sd.dwSize=sizeof(DDSURFACEDESC);

		do{hr=pdirectd->lpDDSBack->Lock(NULL,&sd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);}
		while (hr!=DD_OK);
		pdirectd->lpDDSBack->Unlock(sd.lpSurface);

		DWORD	bits,shift,mask;

		for (shift=0,mask=sd.ddpfPixelFormat.dwRBitMask;!(mask&1);shift++,mask>>=1);
		redShift1=swRedSh1=shift;
		redMask=swRedMask=mask;
		for (bits=0;mask&1;bits++,mask>>=1);
		redShift2=swRedSh2=8-bits;
		for (shift=0,mask=sd.ddpfPixelFormat.dwGBitMask;!(mask&1);shift++,mask>>=1);
		greenShift1=swGreenSh1=shift;
		greenMask=swGreenMask=mask;
		for (bits=0;mask&1;bits++,mask>>=1);
		greenShift2=swGreenSh2=8-bits;
		for (shift=0,mask=sd.ddpfPixelFormat.dwBBitMask;!(mask&1);shift++,mask>>=1);
		blueShift1=swBlueSh1=shift;
		blueMask=swBlueMask=mask;
		for (bits=0;mask&1;bits++,mask>>=1);
		blueShift2=swBlueSh2=8-bits;
		gotShifts=true;
	}
	else
	{
		redMask=swRedMask;
		greenMask=swGreenMask;
		blueMask=swBlueMask;

		redShift1=swRedSh1;
		greenShift1=swGreenSh1;
		blueShift1=swBlueSh1;

		redShift2=swRedSh2;
		greenShift2=swGreenSh2;
		blueShift2=swBlueSh2;
	}
}

void direct_draw::MakePaletteFadeTable(	struct _DirectDraw* pdirectd,
										UByte* psrcpal,						//source palette
										UWord* plut,						//dest for lookup table
										UByte targR,UByte targG,UByte targB)//target fade rgb
{
	//prepare lookup table on first call...
	if (!softpallookup)
	{
		UByte* palfade=softpallookup=new UByte[16*64*64];

		for (int i=63;i>=0;i--)
		{
			int index=i<<6;
			for (int j=63;j>=0;j--)
			{
				int index2=(index+j)<<4;

				//from i->j in 16 steps
				int src=j<<4,delta=i-j;
				for (int k=15;k>=0;k--)
				{
					palfade[index2+k]=UByte(src>>4);
					src+=delta;
				}
			}
		}
	}

	UWord redMask; SWord redShift1,redShift2;
	UWord greenMask; SWord greenShift1,greenShift2;
	UWord blueMask; SWord blueShift1,blueShift2;

	GetColourInfo(	pdirectd,
					redMask,redShift1,redShift2,
					greenMask,greenShift1,greenShift2,
					blueMask,blueShift1,blueShift2);

	UByte	*redbaseptr=softpallookup+(ULong(targR>>redShift2)<<4),
			*greenbaseptr=softpallookup+(ULong(targG>>greenShift2)<<4),
			*bluebaseptr=softpallookup+(ULong(targB>>blueShift2)<<4);

	UByte* srcRGB;
	int i;
	
	for (i=255,srcRGB=psrcpal+3*i;i>=0;i--,srcRGB-=3)
	{
		UWord*  newCol=(UWord*)(ULong(plut)+(i<<5));
		
		UByte	*redptr=redbaseptr+(ULong(srcRGB[1]>>redShift2)<<10),
				*greenptr=greenbaseptr+(ULong(srcRGB[2]>>greenShift2)<<10),
				*blueptr=bluebaseptr+(ULong(srcRGB[0]>>blueShift2)<<10);

		for (int k=0;k<16;k++)
		{
			UWord	redVal=*redptr++,
					greenVal=*greenptr++,
					blueVal=*blueptr++;

			*newCol++ =	((redVal&redMask)<<redShift1)+
						((greenVal&greenMask)<<greenShift1)+
						((blueVal&blueMask)<<blueShift1);
		}
	}
}

void direct_draw::MakeColourRangeFadeTable(	struct _DirectDraw* pdirectd,
											UWord* plut,
											UByte srcR,UByte srcG,UByte srcB,
											UByte dstR,UByte dstG,UByte dstB)
{
	//prepare lookup table on first call...
	if (!softpallookup)
	{
		UByte* palfade=softpallookup=new UByte[16*64*64];

		for (int i=63;i>=0;i--)
		{
			int index=i<<6;
			for (int j=63;j>=0;j--)
			{
				int index2=(index+j)<<4;

				//from i->j in 16 steps
				int src=j<<4,delta=i-j;
				for (int k=15;k>=0;k--)
				{
					palfade[index2+k]=UByte(src>>4);
					src+=delta;
				}
			}
		}
	}

	UWord redMask; SWord redShift1,redShift2;
	UWord greenMask; SWord greenShift1,greenShift2;
	UWord blueMask; SWord blueShift1,blueShift2;

	GetColourInfo(	pdirectd,
					redMask,redShift1,redShift2,
					greenMask,greenShift1,greenShift2,
					blueMask,blueShift1,blueShift2);
	
	UByte	*redptr=softpallookup+(ULong(srcR>>redShift2)<<10)+(ULong(dstR>>redShift2)<<4),
			*greenptr=softpallookup+(ULong(srcG>>greenShift2)<<10)+(ULong(dstG>>greenShift2)<<4),
			*blueptr=softpallookup+(ULong(srcB>>blueShift2)<<10)+(ULong(dstB>>blueShift2)<<4);

	for (int i=0;i<16;i++)
	{
		UWord	redVal=*redptr++,
				greenVal=*greenptr++,
				blueVal=*blueptr++;
		*plut++ =	((redVal&redMask)<<redShift1)+
					((greenVal&greenMask)<<greenShift1)+
					((blueVal&blueMask)<<blueShift1);
	}
}

void direct_3d::PushPull(UByte a)
{
	plainShadeFlag=a;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScanForBottomPixelsOfText
//Author		Paul.   
//Date			Tue 17 Aug 1999
//
//Description	lock the back surface and scan right ? pixels from point (x,y)
//				and return true if a black pixel is found and false if not
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool direct_3d::ScanForBottomPixelsOfText(struct _DirectDraw* pdd,SWord x,SWord y,SWord width)
{
	bool retval=false;
	LPDIRECTDRAWSURFACE lpDDS=pdd->lpDDSBack;
	DDSURFACEDESC ddsd;
	ZeroMem(&ddsd,sizeof(DDSURFACEDESC));
	ddsd.dwSize=sizeof(DDSURFACEDESC);
	HRESULT hr;
	hr=lpDDS->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
	if (hr!=DD_OK)
		return true;
	ULong ulPix=ULong(ddsd.lpSurface)+y*ddsd.lPitch+x*(ddsd.ddpfPixelFormat.dwRGBBitCount>>3);
	UWord *pPix=(UWord*)ulPix;
	UWord uwRGBBitMask=ddsd.ddpfPixelFormat.dwRBitMask|
						ddsd.ddpfPixelFormat.dwGBitMask|
						ddsd.ddpfPixelFormat.dwBBitMask;
	for (int i=width;i--;)
	{
		UWord val=*pPix;
		*pPix++;	//=UWord(0);
		if ((val&uwRGBBitMask)==0)
		{
			retval=true;
			break;
		}
	}
	lpDDS->Unlock(ddsd.lpSurface);
	return retval;
}
void direct_3d::PushViewData(struct _DirectDraw *pdd)
{
	saveviewdata=viewdata;
}
void direct_3d::PopViewData(struct _DirectDraw *pdd)
{
	viewdata=saveviewdata;
}
void direct_3d::Set3DWin(struct _DirectDraw *pdd,SLong x,SLong y,SLong w,SLong h)
{
	viewdata.originx=D3DVALUE(x+(w>>1));
	viewdata.originy=D3DVALUE(y+(h>>1));
	viewdata.clipLft=D3DVALUE(x);
	viewdata.clipRgt=D3DVALUE(x+w);
	viewdata.clipTop=D3DVALUE(y);
	viewdata.clipBot=D3DVALUE(y+h);
}
