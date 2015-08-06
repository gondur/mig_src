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
//Filename       lstream.cpp
//System         
//Author         Paul.   
//Date           Thu 11 Jul 1996
//Description    
//------------------------------------------------------------------------------
#ifdef COMMENT

#define F_GRAFIX												//DAW 05Aug96
#define F_SOUNDS
#define F_BATTLE
#include	"lstream.h"
#include	"3dcode.h"											//PD 29Aug96
#include	"savegame.h"										//PD 05Sep96
#include	"collided.h"										//PD 26Oct96
#include	<stdio.h>
#include	"polygon.h"											//RJS 29Oct96
#include	"flymodel.h"

const	int	DOSFILE_SEEKSTEP = 8*2048;							//PD 14Jun97

extern "C" UByte FadeData2;										//PD 28Aug96

Land_Stream	LandStream;

extern	void fpSqrt(Float& );
#ifdef __WATCOMC__
#pragma aux fpSqrt = \
"	fld 	qword ptr ds:[esi]	"\
"	fsqrt						"\
"	fstp	qword ptr ds:[esi]	"\
parm	[esi]
#else
#ifdef __MSVC__
inline void fpSqrt(Float& num)
{
    _asm
    {
		push	esi
		mov 	esi,num;
		fld 	qword ptr ds:[esi];
		fsqrt;
		fstp	qword ptr ds:[esi];
		pop		esi
    }
}

#endif
#endif

extern	void DestWipe(UByte *destptr);
#ifdef __WATCOMC__
#pragma	aux	DestWipe = \
		"push 	0x0FEFEFEFE"		\
		"push	0x0FEFEFEFE"		\
		"fld	qword ss:[esp]"		\
		"mov	ecx,8255"			\
		"sub	edi,8"				\
		"add	esp,6"				\
"Lp1:	 add	edi,8"				\
		"dec	ecx"				\
		"fst	qword ds:[edi]"		\
		"jnz	short Lp1"			\
		"add	edi,8"				\
		"fstp	qword ds:[edi]"		\
		"pop	word ptr ds:[edi+8]"\
		parm 	[edi]				\
		modify 	[edi ecx]
#else
#ifdef __MSVC__
inline void DestWipe(UByte* destptr)
{ 
	_asm
	{
		push	eax;
		push	ecx;
		push	edi;
		mov		edi,destptr;
		mov		eax,0xFEFEFEFE;
		mov		ecx,16512
		rep		stosd
		stosw
		pop		edi;
		pop		ecx;
		pop		eax;
	}
}

#endif
#endif

extern void ASMSampleTile200pcNoAlias(UByte* src,UByte* dest);
#ifdef __WATCOMC__
#pragma	aux ASMSampleTile200pcNoAlias=	\
	"sub	edi,2"						\
	"mov	edx,16"						\
	"lea	ebx,dword ptr ds:[edi+32]"	\
"rlp:"									\
	"mov	ecx,16"						\
"clp:"									\
	"mov	al,byte ptr ds:[esi]"		\
	"add	edi,2"						\
	"mov	ah,al"						\
	"add	ebx,2"						\
	"mov	word ptr ds:[edi],ax"		\
	"inc	esi"						\
	"dec	ecx"						\
	"mov	word ptr ds:[ebx],ax"		\
	"jnz	short clp"					\
	"add	edi,32"						\
	"add	ebx,32"						\
	"sub	esi,257+16"					\
	"dec	edx"						\
	"jnz	short rlp"					\
	parm	[esi] [edi]					\
	modify	[eax ebx edx esi edi]
#else
#ifdef __MSVC__
inline void ASMSampleTile200pcNoAlias(UByte* src,UByte* dest)
{
    _asm
    {
		push	eax
		push	ebx
		push	ecx
		push	edx
		push	esi
		push	edi
		mov 	esi,src
		mov 	edi,dest
		sub		edi,2
		mov		edx,16
		lea		ebx,dword ptr ds:[edi+32]
	rlp:
		mov		ecx,16
	clp:
		mov		al,byte ptr ds:[esi]
		add		edi,2
		mov		ah,al
		add		ebx,2
		mov		word ptr ds:[edi],ax
		inc		esi
		dec		ecx
		mov		word ptr ds:[ebx],ax
		jnz		short clp
		add		edi,32
		add		ebx,32
		sub		esi,257+16
		dec		edx
		jnz		short rlp
		pop		edi
		pop		esi
		pop		edx
		pop		ecx
		pop		ebx
		pop		eax
    }
}

#endif
#endif
extern void	ASMSampleTile100pc(UByte* src,UByte* dest);
#ifdef __WATCOMC__
#pragma	aux	ASMSampleTile100pc = 	\
	"sub	esi,8"					\
	"sub	edi,8"					\
	"mov	ebx,esi"				\
	"mov	edx,edi"				\
	"add	ebx,4"					\
	"add	edx,4"					\
	"mov	ecx,16"					\
"rlp:"								\
	"add	esi,8"					\
	"add	ebx,8"					\
	"mov	eax,dword ptr ds:[esi]"	\
	"mov	ebp,dword ptr ds:[ebx]"	\
	"add	edi,8"					\
	"add	edx,8"					\
	"mov	dword ptr ds:[edi],eax"	\
	"mov	dword ptr ds:[edx],ebp"	\
	"add	esi,8"					\
	"add	ebx,8"					\
	"mov	eax,dword ptr ds:[esi]"	\
	"mov	ebp,dword ptr ds:[ebx]"	\
	"add	edi,8"					\
	"add	edx,8"					\
	"mov	dword ptr ds:[edi],eax"	\
	"mov	dword ptr ds:[edx],ebp"	\
	"add	esi,8"					\
	"add	ebx,8"					\
	"mov	eax,dword ptr ds:[esi]"	\
	"mov	ebp,dword ptr ds:[ebx]"	\
	"add	edi,8"					\
	"add	edx,8"					\
	"mov	dword ptr ds:[edi],eax"	\
	"mov	dword ptr ds:[edx],ebp"	\
	"add	esi,8"					\
	"add	ebx,8"					\
	"mov	eax,dword ptr ds:[esi]"	\
	"mov	ebp,dword ptr ds:[ebx]"	\
	"add	edi,8"					\
	"add	edx,8"					\
	"dec	ecx"					\
	"mov	dword ptr ds:[edi],eax"	\
	"mov	dword ptr ds:[edx],ebp"	\
	"jnz	short rlp"				\
	parm	[esi] [edi]				\
	modify	[eax ebx ecx edx esi edi ebp]
#else
#ifdef __MSVC__
inline void	ASMSampleTile100pc(UByte* src,UByte* dest)
{
    _asm
    {
		push	eax
		push	ebx
		push	ecx
		push	edx
		push	esi
		push	edi
		push	ebp

		mov 	esi,src
		mov 	edi,dest
		sub		esi,8
		sub		edi,8
		mov		ebx,esi
		mov		edx,edi
		add		ebx,4
		add		edx,4
		mov		ecx,16
rlp:
		add		esi,8
		add		ebx,8
		mov		eax,dword ptr ds:[esi]
		mov		ebp,dword ptr ds:[ebx]
		add		edi,8
		add		edx,8
		mov		dword ptr ds:[edi],eax
		mov		dword ptr ds:[edx],ebp
		add		esi,8
		add		ebx,8
		mov		eax,dword ptr ds:[esi]
		mov		ebp,dword ptr ds:[ebx]
		add		edi,8
		add		edx,8
		mov		dword ptr ds:[edi],eax
		mov		dword ptr ds:[edx],ebp
		add		esi,8
		add		ebx,8
		mov		eax,dword ptr ds:[esi]
		mov		ebp,dword ptr ds:[ebx]
		add		edi,8
		add		edx,8
		mov		dword ptr ds:[edi],eax
		mov		dword ptr ds:[edx],ebp
		add		esi,8
		add		ebx,8
		mov		eax,dword ptr ds:[esi]
		mov		ebp,dword ptr ds:[ebx]
		add		edi,8
		add		edx,8
		dec		ecx
		mov		dword ptr ds:[edi],eax
		mov		dword ptr ds:[edx],ebp
		jnz		short rlp

		pop		ebp
		pop		edi
		pop		esi
		pop		edx
		pop		ecx
		pop		ebx
		pop		eax
    }
}

#endif
#endif

extern void AltDDA(UByte* scanp,int startval,int endval,int length);
#ifdef __WATCOMC__
#pragma aux	AltDDA = 						\
"		sal		eax,8						"\
"		sal		edx,8						"\
"		mov		ebx,edx						"\
"		sub		eax,edx						"\
"		mov		edx,eax						"\
"		sar		edx,0x1F					"\
"		idiv	ecx							"\
"		add		ebx,eax						"\
"ADLp:	mov		byte ptr ds:[edi],bh		"\
"		inc		edi							"\
"		add		ebx,eax						"\
"		dec		ecx							"\
"		jnz		short ADLp					"\
parm	[edi] [edx] [eax] [ecx]				\
modify	[eax ebx edx ecx edi]
#else
#ifdef __MSVC__
inline void AltDDA(UByte* scanp,int startval,int endval,int lngth)
{
    _asm
    {
		push	eax
		push	ebx
		push	ecx
		push	edx
		push	esi
		push	edi

		mov 	edi,scanp
		mov 	edx,startval
		mov 	eax,endval
		mov 	ecx,lngth
		sal		eax,8
		sal		edx,8
		mov		ebx,edx
		sub		eax,edx
		mov		edx,eax
		sar		edx,0x1F
		idiv	ecx
		add		ebx,eax
ADLp:	
		mov		byte ptr ds:[edi],bh
		inc		edi
		add		ebx,eax
		dec		ecx
		jnz		short ADLp

		pop		edi
		pop		esi
		pop		edx
		pop		ecx
		pop		ebx
		pop		eax
    }
}

#endif
#endif
extern void AltDDA2(UByte* scanp,int startval,int endval,int length);
#ifdef __WATCOMC__
#pragma aux	AltDDA2 = 						\
"		sal		eax,8						"\
"		sal		edx,8						"\
"		mov		ebx,edx						"\
"		sub		eax,edx						"\
"		mov		edx,eax						"\
"		sar		edx,0x1F					"\
"		idiv	ecx							"\
"		add		ebx,eax						"\
"ADLp:	mov		byte ptr ds:[edi],bh		"\
"		add		edi,35						"\
"		add		ebx,eax						"\
"		dec		ecx							"\
"		jnz		short ADLp					"\
parm	[edi] [edx] [eax] [ecx]				\
modify	[eax ebx edx ecx edi]
#else
#ifdef __MSVC__
inline void AltDDA2(UByte* scanp,int startval,int endval,int lngth)
{
    _asm
    {
		push	eax
		push	ebx
		push	ecx
		push	edx
		push	esi
		push	edi
		mov 	edi,scanp
		mov 	edx,startval
		mov 	eax,endval
		mov 	ecx,lngth
		sal		eax,8
		sal		edx,8
		mov		ebx,edx
		sub		eax,edx
		mov		edx,eax
		sar		edx,0x1F
		idiv	ecx
		add		ebx,eax
ADLp:	
		mov		byte ptr ds:[edi],bh
		add		edi,35
		add		ebx,eax
		dec		ecx
		jnz		short ADLp
		pop		edi
		pop		esi
		pop		edx
		pop		ecx
		pop		ebx
		pop		eax
    }
}

#endif
#endif

extern void AltDDA3(UByte* scanp,int startval,int endval,int length);
#ifdef __WATCOMC__
#pragma aux	AltDDA3 = 						\
"		sal		eax,8						"\
"		sal		edx,8						"\
"		mov		ebx,edx						"\
"		sub		eax,edx						"\
"		mov		edx,eax						"\
"		sar		edx,0x1F					"\
"		idiv	ecx							"\
"ADLp:	mov		byte ptr ds:[edi],bh		"\
"		inc		edi							"\
"		add		ebx,eax						"\
"		dec		ecx							"\
"		jnz		short ADLp					"\
parm	[edi] [edx] [eax] [ecx]				\
modify	[eax ebx edx ecx edi]
#else
#ifdef __MSVC__
inline void AltDDA3(UByte* scanp,int startval,int endval,int lngth)
{
    _asm
    {
		push	eax
		push	ebx
		push	ecx
		push	edx
		push	esi
		push	edi
		mov 	edi,scanp
		mov 	edx,startval
		mov 	eax,endval
		mov 	ecx,lngth
		sal		eax,8
		sal		edx,8
		mov		ebx,edx
		sub		eax,edx
		mov		edx,eax
		sar		edx,0x1F
		idiv	ecx
ADLp:	
		mov		byte ptr ds:[edi],bh
		inc		edi
		add		ebx,eax
		dec		ecx
		jnz		short ADLp
		pop		edi
		pop		esi
		pop		edx
		pop		ecx
		pop		ebx
		pop		eax
    }
}

#endif
#endif

extern	void ASM_DivMod(int divisor,int dividend,
						int* result,int* remainder);
#ifdef __WATCOMC__
#pragma	aux ASM_DivMod =					\
"		xor		edx,edx						"\
"		div		ebx							"\
"		mov		ds:[esi],eax				"\
"		mov		ds:[edi],edx				"\
parm	[eax] [ebx] [esi] [edi]				\
modify	[eax edx]
#else
#ifdef __MSVC__
inline	void ASM_DivMod(int divisor,int dividend,
						int* result,int* remainder)

{
    _asm
    {
		push	eax
		push	ebx
		push	ecx
		push	edx
		push	esi
		push	edi
		mov 	eax,divisor
		mov 	ebx,dividend
		mov 	esi,result
		mov 	edi,remainder
		xor		edx,edx
		div		ebx
		mov		ds:[esi],eax
		mov		ds:[edi],edx
		pop		edi
		pop		esi
		pop		edx
		pop		ecx
		pop		ebx
		pop		eax
    }
}

#endif
#endif

extern	void ASM_CopyImage(UByte* srcp,UByte* dstp,int count);
// Mods to block big values and negative values
//
// I know rep movs is fast, but I thought movs was slow compared to move and add?
//
// I also took out "or ecx,ecx" from "NoWord:", as Movs doesn't change flags
//
//
#ifdef __WATCOMC__
#pragma	aux	 ASM_CopyImage =				\
"			or	cx,cx						"\
"			jle	short CopyDone				"\
"			shr	ecx,1						"\
"			jnc	short NoByte				"\
"			movsb							"\
"NoByte:	shr	ecx,1						"\
"			jnc	short NoWord				"\
"			movsw							"\
"NoWord:	"								\
"			jle	short CopyDone				"\
"			rep	movsd						"\
"CopyDone:									"\
parm	[esi] [edi] [ecx]					\
modify	[esi edi ecx]
#else
#ifdef __MSVC__
inline 	void ASM_CopyImage(UByte* srcp,UByte* dstp,int count)
{
    _asm
    {
		push	eax
		push	ecx
		push	esi
		push	edi
		mov 	esi,srcp
		mov 	edi,dstp
		mov 	ecx,count
		or		cx,cx
		jle		short CopyDone
		shr		ecx,1
		jnc		short NoByte
		movsb
NoByte:	shr		ecx,1
		jnc		short NoWord
		movsw
NoWord:
		jle		short CopyDone
		rep		movsd
CopyDone:
		pop		edi
		pop		esi
		pop		ecx
		pop		eax
    }
}

#endif
#endif

#ifdef	__WATCOMC__
	extern "C" void ASM_WidenRoutes(UByte*);
	extern "C" void ASM_AliasTile(UByte*,UByte*,UByte*,UByte*);
	extern "C" void ASM_NoAliasTile(UByte*,UByte*,UByte*,UByte*);
#else
#ifdef	__MSVC__
	extern "C" void XASM_WidenRoutes(void);
	extern "C" void XASM_AliasTile(void);
	extern "C" void XASM_NoAliasTile(void);

//-----------------------------------------------------------------------------
// Procedure    ASM_WidenRoutes
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
inline	void ASM_WidenRoutes(UByte* p)
{
	_asm {
		push	eax
		mov		eax,p
		call	XASM_WidenRoutes
		pop		eax
	}
}

//-----------------------------------------------------------------------------
// Procedure    ASM_AliasTile
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
inline	void ASM_AliasTile(UByte* a,UByte* b,UByte* c,UByte* d)
{
	_asm {
		push	eax
		push	ebx
		push	ecx
		push	edx
		mov		eax,a
		mov		edx,b
		mov		ebx,c
		mov		ecx,d
		call	XASM_AliasTile
		pop		edx
		pop		ecx
		pop		ebx
		pop		eax
	}
}

//-----------------------------------------------------------------------------
// Procedure    ASM_NoAliasTile
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
inline	void ASM_NoAliasTile(UByte* a,UByte* b,UByte* c,UByte* d)
{
	_asm {
		push	eax
		push	ebx
		push	ecx
		push	edx
		mov		eax,a
		mov		edx,b
		mov		ebx,c
		mov		ecx,d
		call	XASM_NoAliasTile
		pop		edx
		pop		ecx
		pop		ebx
		pop		eax
	}
}
#endif
#endif

const	ROADCOLOUR8		=	165	;
const	RAILCOLOUR8		=	192	;
const	BTRENCHCOL8		=	192	;
const	GTRENCHCOL8		=	194	;

const	ROADCOLOUR16	=	116;	//140	;
const	RAILCOLOUR16	=	78	;
const	BTRENCHCOL16	=	16	;
const	GTRENCHCOL16	=	20	;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Land_Stream
//Author		Paul.   
//Date			Thu 11 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void operator++ (LandMapNum i,int) {i=LandMapNum(i+1);}
CON	Land_Stream::Land_Stream()
{
	SetupLandStuff();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupLandStuff
//Author		Dave Whiteside
//Date			Mon 27 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SetupLandStuff()
{
	firstcall = TRUE;
	//Clear record of landmaps loaded							//PD 05Sep96

	LandMapNum	lmn;

	landmapfield = &lmnf;										//PD 16Sep96

	for (lmn=LandMapNumMIN;
		lmn<LandMapNumMAX;
		*landmapfield %= lmn,
		lmn = (LandMapNum)(lmn+1));								//PD 05Sep96

	masterseeklist=NULL;										//PD 31Oct96

	for (int cnt=0;cnt<BIG_CACHE_SIZE*BIG_CACHE_SIZE;bigareacahe[cnt]=NULL,cnt++);//PD 13Nov96
	for (cnt=0;cnt<BIG_CACHE_SIZE*BIG_EDGE_SIZE;cnt++)
	{
		rcbuffer0[cnt] =
			rcbuffer1[cnt] = NULL;
	}

	requestcount=0;												//PD 16Dec96

//TempCode PD 18Nov97 	if (Demoversion==FALSE)
//TempCode PD 18Nov97 	{
		BIG_FILE_SIZE =	112;
		Area1SW_X = 16777216;
		Area1SW_Z = 20971520;
		Area1NE_X = 31457280;
		Area1NE_Z = 35651584;
//TempCode PD 18Nov97 	}
//TempCode PD 18Nov97 	else
//TempCode PD 18Nov97 	{
//TempCode PD 18Nov97 		BIG_FILE_SIZE =	56;
//TempCode PD 18Nov97 		Area1SW_X = 0x12e0000;
//TempCode PD 18Nov97 		Area1SW_Z = 0x1800000;
//TempCode PD 18Nov97 		Area1NE_X = 0x19e0000;
//TempCode PD 18Nov97 		Area1NE_Z = 0x1f00000;
//TempCode PD 18Nov97 	}
	Area2SW_X = 34603008;							//PD 27Jan97
	Area2SW_Z = 8388608;
	Area2NE_X = 49283072;
	Area2NE_Z = 23068672;

	ailclrindexp = NULL;										//AM 18Jun97
	shadeindexp = NULL;											//AM 18Jun97
	tbuffer = NULL;												//AM 18Jun97
	dummyimagep = NULL;											//AM 18Jun97

	bigcachep[0] =												//PD 18Jun97
		bigdumpp[0] = NULL;										//PD 18Jun97

	bigcachecount = 0;											//PD 18Jun97
	bigcachemax = BIG_TILES_MAX;								//PD 18Jun97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Land_Stream
//Author		Paul.   
//Date			Thu 11 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DES Land_Stream::~Land_Stream()
{

}

//DeadCode PD 09Dec97 extern void GlobalTestCode(void);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Init
//LastModified:	PD 27Aug96
//Author		Paul.   
//Date			Fri 12 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::Init()
{
	return;
//TempCode PD 9Dec97 	GlobalTestCode();

	const	Colour Range00 = (Colour )0;
	const	Colour Range01 = (Colour )8;
	const	Colour Range02 = (Colour )32;
	const	Colour Range03 = (Colour )40;
	const	Colour Range04 = (Colour )48;
	const	Colour Range05 = (Colour )56;
	const	Colour Range06 = (Colour )64;
	const	Colour Range07 = (Colour )80;
	const	Colour Range08 = (Colour )112;
	const	Colour Range09 = (Colour )96;
	const	Colour Range10 = (Colour )160;
	const	Colour Range11 = (Colour )200;
	const	Colour Range12 = (Colour )144;
	const	Colour Range13 = (Colour )192;

	LandMapNum imcnt;											//PD 27Aug96

	static 
	LandMapNum imno[] =											//PD 27Aug96
	{
		(LandMapNum )(FIL_512FNW_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512FNW_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512FNW_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512FNW_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512FN_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512FN_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512FN_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512FN_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512T_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512T_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512T_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_512T_NUM - DIR_LANDMAPS),

		(LandMapNum )(FIL_256BFN_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256BFNC_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256BFNW_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256BFNWC_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256GRN1_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256GRN2_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256MARSH_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256POTGR_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256TC_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256TOWN_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256TOWNC_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256WATER_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256WOOD_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256WOODC_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256CITY_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256BUSH_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256GRN3_NUM - DIR_LANDMAPS),
		(LandMapNum )(FIL_256POTBR_NUM - DIR_LANDMAPS),

		(LandMapNum )NULL
	};

	Colour	clr[ColourRanges] =
			{
			Range02,Range03,
			Range04,Range05,Range06,Range07,
			Range08,Range09,Range10,Range11,
			Range12,Range13,Range00,Range01						//PD 16Sep96
			};

	static
	UByte	clrindex[16] =
			{
				84,
				84,
				84,
				84,
				ROADCOLOUR8,	//Roads
				84,
				84,
				BTRENCHCOL8,	//British Front line					//AM 04Sep96
				84,
				84,
				GTRENCHCOL8,	//German front line						//AM 04Sep96
				84,
				84,
				84,
				RAILCOLOUR8,	//Railways
				84
			};

	gColindexp 		= clrindex;
	lpLandMapFList 	= imno;

	ReInit();

//PD 24Sep96 - done in constructor
	//Set up imagemap ptrs first


	for (int nCount=LandMapNumMIN; imno[nCount]!=NULL;nCount++)
	{//PD 27Aug96

		int	sillyIndex0,sillyIndex1,sillyIndex2,sillyIndex3;

		sillyIndex0=nCount;
		sillyIndex1=MaxImageMapsNo+nCount;
		sillyIndex2=2*MaxImageMapsNo+nCount;
		sillyIndex3=3*MaxImageMapsNo+nCount;

		colorindex[nCount].imagep =
			colorindex[MaxImageMapsNo+nCount].imagep =
	 		colorindex[2*MaxImageMapsNo+nCount].imagep =
	 		colorindex[3*MaxImageMapsNo+nCount].imagep = GetLandMapPtr(imno[nCount]);
	}

	//Set up plain colour mappings 14 * 8 colour ranges

	int	clrno, clr2no;

	for (clrno=0;clrno<ColourRanges;clrno++)
		for (clr2no=0;clr2no<8;
			colorindex[4*MaxImageMapsNo+(clrno<<3)+clr2no].color =
				(Colour )(clr[clrno]+clr2no), clr2no++);

	ImageMapDescPtr ailimgp = GetLandMapPtr((LandMapNum )(FIL_ALIASTABLE - DIR_LANDMAPS));//PD 27Aug96

	ailtbl16p = &(ailimgp->data);								//PD 10Oct96

	//colour indirection table to generate roads with the correct colours

	if (ailclrindexp==NULL)										//AM 18Jun97
		ailclrindexp = new UByte[256];							//AM 18Jun97

	assert((ailclrindexp)&&(" - alias table load failed!"));		//PD 29Aug96

	for (clrno=0;clrno<16;*(ailclrindexp+clrno)=clrindex[clrno],clrno++);

	for (;clrno<256;*(ailclrindexp+clrno)=(UByte )clrno,clrno++);

	//Generate table of gradients from intensities

	if (shadeindexp == NULL)									//AM 18Jun97
		shadeindexp = new SByte[16*16];							//AM 18Jun97

	assert((shadeindexp)&&(" - alt shaded data table alloc failed!"));//PD 29Aug96

	SByte*	tsindex = shadeindexp;

	int	xgrad, zgrad;

	SByte	val;

	for (	xgrad = 8;
			xgrad >= -7;
			xgrad--)
		for (	zgrad = -7;
				zgrad <= 8;
				val = xgrad,
				*tsindex++ = (SByte )val,
				zgrad++);

	if (dummyimagep == NULL)									//AM 18Jun97
		dummyimagep = CreateNewMap(LDS_Normal);					//AM 18Jun97

	FillTile(GNDGREEN07,&dummyimagep->tilemap.data,32);			//PD 29Aug96

	FadeStartRange = (Save_Data.detail_3d[DETAIL3D_HORIZONFADE])?
					 FadeStartRangeHi:
					 FadeStartRangeLo;

	if (tbuffer == NULL)										//AM 18Jun97
		tbuffer = new UByte[ColourDataSize+AltDataSize+1];		//AM 18Jun97

	RGBVal	thispal[256];
	if (currwin)
		for (SWord cnt=0;cnt<256;cnt++)
		{
			currwin->GetRGB(cnt,	thispal[cnt].red,
										thispal[cnt].green,
										thispal[cnt].blue);
		}

	preshadetable = new UByte[32*256];

	for (SWord cnt=0;cnt<256;cnt++)
	{
		Float rval,gval,bval;

		rval=(Float)thispal[cnt].red;
		gval=(Float)thispal[cnt].green;
		bval=(Float)thispal[cnt].blue;

		const Float maxpc=(Float)0.10;

		for (int perc=0;perc<32;perc++)
		{
			//reduce red val by 'startpc' percent

			Float thispc;

			UByte	newcol;

			SLong	tval;

			int	index = cnt*32+perc;

			if (perc<16)
			{
				Float nr,nb,ng;

				thispc = (15.0-perc);

				nr = rval-thispc;
				ng = gval-thispc;
				nb = bval-thispc;

				if (nr<0.0)	nr=0.0;
				if (ng<0.0)	ng=0.0;
				if (nb<0.0)	nb=0.0;

				//required RGB are nr,ng,nb;

				newcol=GetClosestMatch(nr,ng,nb,thispal);
			}
			if (perc==16)
			{
				newcol=(UByte)cnt;
			}
			if (perc>16)
			{
				Float nr,nb,ng;

				thispc = (perc-16.0)/2.0;

				nr = thispc + rval;
				ng = thispc + gval;
				nb = thispc + bval;

				if (nr>255.0)	nr=255.0;
				if (ng>255.0)	ng=255.0;
				if (nb>255.0)	nb=255.0;

				//required RGB are nr,ng,nb;

				newcol=GetClosestMatch(nr,ng,nb,thispal);
			}
			preshadetable[index]=newcol;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetClosestMatch
//Author		Paul.   
//Date			Thu 16 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte Land_Stream::GetClosestMatch(Float& r,Float& g,Float& b,RGBValP pal)
{
	Float tr,tg,tb,closest;

	UByte selected;

	int i;

	closest=(Float)256.0*(Float)256.0*(Float)3.0;

	for (i=16;i<240;i++)
	{
		tr=(Float)pal[i].red;
		tg=(Float)pal[i].green;
		tb=(Float)pal[i].blue;

		tr-=r; tg-=g; tb-=b;

		tr = tr*tr + tg*tg + tb*tb;

		if (tr<closest)
		{
			closest=tr;
			selected=(UByte)i;
		}
	}

	return(selected);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReInit
//Author		Paul.   
//Date			Fri 25 Apr 1997
//
//Description	Checks to make sure that the correct ground textures
//				have been loaded for a particular graphics mode and
//				switches them if necessary
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ReInit()
{

	LandMapNum	compareValue;
	UByte		*clrindex;
	SLong		modOffset;
	int			clrno;
	Bool		bDoingHW3D;

	UByte	clrindex8[16] =
	{
		84,84,84,84,ROADCOLOUR8,
		84,84,BTRENCHCOL8,
		84,84,GTRENCHCOL8,
		84,84,84,RAILCOLOUR8,
		84
	};

	UByte	clrindex16[16] =
	{
		84,84,84,84,ROADCOLOUR16,
		84,84,BTRENCHCOL16,
		84,84,GTRENCHCOL16,
		84,84,84,RAILCOLOUR16,
		84
	};
	if (currwin)
		bDoingHW3D = currwin->DoingHardware3D();				//PD 19Nov97
	else
		bDoingHW3D = FALSE;

//TempCode PD 19Nov97 	if (bDoingHW3D)
//TempCode PD 19Nov97 	{
//TempCode PD 19Nov97 		compareValue =
//TempCode PD 19Nov97 		(LandMapNum)(FIL_512FNW_NUM-DIR_LANDMAPS+(DIR_LANDMAP2-DIR_LANDMAPS));
//TempCode PD 19Nov97 		modOffset = DIR_LANDMAP2 - DIR_LANDMAPS;
//TempCode PD 19Nov97 		clrindex = clrindex16;
//TempCode PD 19Nov97 	}
//TempCode PD 19Nov97 	else
//TempCode PD 19Nov97 	{
		compareValue =
		(LandMapNum)(FIL_512FNW_NUM-DIR_LANDMAPS);
		modOffset = DIR_LANDMAPS - DIR_LANDMAP2;
		clrindex = clrindex8;
//TempCode PD 19Nov97 	}

	//Exit if no change is required

	if (lpLandMapFList[0]==compareValue)	return;

	//Modify the data in the table of files to load

	LandMapNum*	lpLMN;

	lpLMN = lpLandMapFList;

	while (*lpLMN!=(LandMapNum)NULL)
	{
		SLong	fixupValue;

		fixupValue = *lpLMN;

		fixupValue += modOffset;

		*lpLMN++ = (LandMapNum)fixupValue;
	}

	for (clrno=0;clrno<16;gColindexp[clrno]=clrindex[clrno],clrno++);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Decompress
//Author		Paul.   
//Date			Thu 11 Jul 1996
//
//Description	Decompresses packed landscape data to a 257*257 + 1
//				buffer area (The +1 makes the buffer an even size and
//				helps detect the end of the unpack)
//
//Inputs		srcptr = ptr to compressed data
//
//				cdestptr = ptr to destination buffer for
//							colour data
//
//				adestptr = ptr to destination buffer for
//							altitude data
//
//Returns		CD data decompressed to 'cdestptr' and 'adestptr'
//
//------------------------------------------------------------------------------
void Land_Stream::Decompress(UByte* srcptr,UByte* cdestptr, UByte* adestptr)
{
	//Allocate intermediate buffer

	UByte	*destptr = tbuffer;		//new UByte[257*257+1];

	Bool	altcompressed;

	//Decompress the CD data

	if (*srcptr == 0x0FF)
	{
		altcompressed = FALSE;
		srcptr++;
	}
	else
		altcompressed = TRUE;

	UnpackAltitudeData(altcompressed,srcptr,adestptr);
	if (Save_Data.detail_3d[DETAIL3D_ANTIALIAS] && !currwin->DoingHardware3D())
		UnpackColorData(srcptr,destptr);
	else
		UnpackColorData(srcptr,cdestptr);

	ThreeDee::PossMoveCycle();									//PD 12Nov96

	//Add aliasing for roads etc

	AliasTile(destptr,cdestptr);

	ThreeDee::PossMoveCycle();									//PD 12Nov96

	//Add altitude data shading

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PartialDecompress
//Author		Paul.   
//Date			Tue 8 Oct 1996
//
//Description	decompresses and stores the altitude data
//				also records a colour value for the tile.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::PartialDecompress(UByte*& srcptr)
{
	Bool	altcompressed;

	UByte	*adestptr = tbuffer + ColourDataSize;

	//Decompress the CD data

	if (*srcptr == 0x0FF)
	{
		altcompressed = FALSE;
		srcptr++;
	}
	else
		altcompressed = TRUE;

	UnpackAltitudeData(altcompressed,srcptr,adestptr);

	//Get the first colour from the colour table
	//at the start of the compressed colour data

	srcptr++;

	UByte colindex = *srcptr;

	int	typevar;

	typevar = colindex / MaxImageMapsNo;

	switch (typevar)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			ImageMapDescPtr imapp;

			imapp = colorindex[colindex].imagep;

			if (imapp!=NULL)	colindex = *(&imapp->data);	//first colour on the imagemap
			else				colindex = BLACK;
		}
		break;

		default:	//Plain colour
			colindex = colorindex[colindex].color;

			//Extra level of indirection needed to get
			//the correct value for the 1st 16 colours	

			if (!(colindex&RoadColoursMask))
				colindex = *(ailclrindexp + colindex);
		break;
	}

	srcptr = tbuffer;

	*srcptr = colindex;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnpackColorData
//Author		Paul.   
//Date			Tue 16 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::UnpackColorData(UByte*& srcptr,UByte* destptr)
{
	beginbuffer = destptr;

//DeadCode JIM 09Jan97 	UByte* endbuffer;

	UByte*	lastdest;

	int	typevar, modvar;

	int	numcol,colbits,colmask;

	int bitpos = 0;

	UByte color;

	endbuffer = destptr + (257 * 257); //last byte in the buffer

	//Wipe the destination first

	DestWipe(destptr);

	//Set up number of colour bits and colour indirection table here

	numcol=GetByte(srcptr,bitpos);

	if (numcol==1)			colbits=0;
	elseif (numcol<=2) 		colbits=1;
	elseif (numcol<=4) 		colbits=2;
	elseif (numcol<=8) 		colbits=3;
	elseif (numcol<=16)		colbits=4;
	elseif (numcol<=32) 	colbits=5;
	elseif (numcol<=64) 	colbits=6;
	elseif (numcol<=128)	colbits=7;
	else					colbits=8;

	colmask = (0x01<<colbits)-1;

	for (int i=0;i<numcol;i++)
		incolindex[i]=GetByte(srcptr,bitpos);

	lastdest=NULL;

//Old_Code DAW 07Jan97 	for (;destptr<endbuffer;FindNextPosition(destptr))			//PD 02Jan97
	for (;;)			//PD 02Jan97
	{
		FindNextPosition(destptr);

		if (destptr==lastdest)	break;

		if (destptr>=endbuffer)	break;

		lastdest=destptr;

		color = GetBits(srcptr,bitpos,colbits,colmask);
 		color = incolindex[color];

		typevar = color / MaxImageMapsNo;

		switch (typevar)
		{
			case 0:

			modvar = color % MaxImageMapsNo;

			if (modvar<=Maps512End)
				Maps512NoMirror(color,modvar,srcptr,bitpos,destptr);
			else
				Maps256NoMirror(color,srcptr,bitpos,destptr);
			break;

			case 1:

			modvar = color % MaxImageMapsNo;

			if (modvar<=Maps512End)
				Maps512MirrorY(color,modvar,srcptr,bitpos,destptr);
			else
				Maps256MirrorY(color,srcptr,bitpos,destptr);
			break;

			case 2:

			modvar = color % MaxImageMapsNo;

			if (modvar<=Maps512End)
				Maps512MirrorXY(color,modvar,srcptr,bitpos,destptr);
			else
				Maps256MirrorXY(color,srcptr,bitpos,destptr);
			break;

			case 3:

			modvar = color % MaxImageMapsNo;

			if (modvar<=Maps512End)
				Maps512MirrorX(color,modvar,srcptr,bitpos,destptr);
			else
				Maps256MirrorX(color,srcptr,bitpos,destptr);
			break;

			default:
			PlainColour(color,srcptr,bitpos,destptr);
			break;
		}
	}
	if (bitpos!=0)
	{
		srcptr++; bitpos = 0;
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Maps512NoMirror
//Author		Paul.   
//Date			Mon 15 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::Maps512NoMirror(	UByte srccol,
									int	modvar,
									UByte*& srcptr, int& bitpos,
									UByte* workptr)
{
	ImageMapDescPtr	imagep;

	int	scanlines;

	//Generate index into imagemap

	int	imagex,imagey;

	int	delta = workptr-beginbuffer;

	imagep = colorindex[srccol].imagep;

	ASM_DivMod(delta,DestBytesPerScanLine,&imagey,&imagex);

	if (modvar & 0x01)	imagex += 256;

	if (modvar & 0x02)	imagey += 256;

	imagex &= 0x1FF; imagey &= 0x1FF;

	UByte*	imagescanlinep = &(imagep->data) + (imagey<<9);

	//Test for single pixel first

	scanlines = GetScanLines(srcptr,bitpos);

	if (scanlines==0)
	{
		//Update the image buffer
		*workptr = *(imagescanlinep + imagex);
		return;
	}

	int	lhs_delta,rhs_delta;

	int	polymode,passno,polywidth,mode;

	//Line or polygon

	polymode = 1;
	passno = 1;

	polywidth = GetBits(srcptr,bitpos,7,0x7F);

	//Update the image buffer

	if ((workptr+(ULong)polywidth)>endbuffer)
		goto _abort;

	ASM_CopyImage(imagescanlinep+imagex,workptr,polywidth);

	do
	{
		scanlines--;

		if (scanlines<polymode)	break;

		polymode = 0;

		//Get line or poly mode

		mode = GetBit(srcptr,bitpos);

		//Get deltas

		lhs_delta = GetDelta(srcptr,bitpos);

		if (!mode)
			rhs_delta = GetDelta(srcptr,bitpos);

		while (scanlines-->=passno)
		{
			int	lhs_add = lhs_delta + GetBit(srcptr,bitpos);

			workptr += DestBytesPerScanLine + lhs_add;

			imagex += lhs_add;

			imagey++; imagey &= 0x1FF;

			if (imagey==0)
				imagescanlinep = &(imagep->data);
			else
				imagescanlinep += 512;

			if (!mode)
				polywidth += rhs_delta + GetBit(srcptr,bitpos) - lhs_add;

			//Update the image buffer

			if ((workptr+(ULong)polywidth)>endbuffer)
				goto _abort;

			ASM_CopyImage(imagescanlinep+imagex,workptr,polywidth);
		}
		passno = 0;
	}
	while ((scanlines=GetScanLines(srcptr,bitpos))!=0);		
_abort:
	return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Maps512MirrorY
//Author		Paul.   
//Date			Mon 15 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::Maps512MirrorY(	UByte srccol,
							   		int	modvar,
							   		UByte*& srcptr, int& bitpos,
							   		UByte* workptr)
{
	ImageMapDescPtr	imagep;

	int	scanlines;

	//Generate index into imagemap

	int	imagex,imagey;

	int	delta = workptr-beginbuffer;

	imagep = colorindex[srccol].imagep;

	ASM_DivMod(delta,DestBytesPerScanLine,&imagey,&imagex);

	imagey = 255 - imagey;

	switch	(modvar)
	{
		case 0:
			imagey += 256;
			break;
		case 1:
			break;
		case 2:
			imagex += 256;
			imagey += 256;
			break;
		case 3:
			imagex += 256;
			break;
	}

	imagex &= 0x1FF; imagey &= 0x1FF;

	UByte*	imagescanlinep = &(imagep->data) + (imagey<<9);

	//Test for single pixel first

	scanlines = GetScanLines(srcptr,bitpos);

	if (scanlines==0)
	{
		//Update the image buffer
		*workptr = *(imagescanlinep + imagex);
		return;
	}

	int	lhs_delta,rhs_delta;

	int	polymode,passno,polywidth,mode;

	//Line or polygon

	polymode = 1;
	passno = 1;

	polywidth = GetBits(srcptr,bitpos,7,0x7F);

	//Update the image buffer

	if ((workptr+(ULong)polywidth)>endbuffer)
		goto _abort;

	ASM_CopyImage(imagescanlinep+imagex,workptr,polywidth);

	do
	{
		scanlines--;

		if (scanlines<polymode)	break;

		polymode = 0;

		//Get line or poly mode

		mode = GetBit(srcptr,bitpos);

		//Get deltas

		lhs_delta = GetDelta(srcptr,bitpos);

		if (!mode)
			rhs_delta = GetDelta(srcptr,bitpos);

		while (scanlines-->=passno)
		{
			int	lhs_add = lhs_delta + GetBit(srcptr,bitpos);

			workptr += DestBytesPerScanLine + lhs_add;

			imagex += lhs_add;

			imagey--; imagey &= 0x1FF;

			if (imagey==0x1FF)
				imagescanlinep = &(imagep->data) + 511*512;
			else
				imagescanlinep -= 512;

			if (!mode)
				polywidth += rhs_delta + GetBit(srcptr,bitpos) - lhs_add;

			//Update the image buffer

			if ((workptr+(ULong)polywidth)>endbuffer)
				goto _abort;

			ASM_CopyImage(imagescanlinep+imagex,workptr,polywidth);
		}
		passno = 0;
	}
	while ((scanlines=GetScanLines(srcptr,bitpos))!=0);		

_abort:
	return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Maps512MirrorXY
//Author		Paul.   
//Date			Mon 15 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::Maps512MirrorXY(	UByte srccol,
									int	modvar,
									UByte*& srcptr, int& bitpos,
									UByte* workptr)
{
	ImageMapDescPtr	imagep;

	int	scanlines;

	//Generate index into imagemap

	int	wimagex,imagex,imagey;

	int	imagew,imageh;

	int	imageshift;

	int	delta = workptr-beginbuffer;

	imagep = colorindex[srccol].imagep;

//Old_Code PD 04Dec96 	imagey = delta / DestBytesPerScanLine;
//Old_Code PD 04Dec96 	imagex = delta % DestBytesPerScanLine;

	ASM_DivMod(delta,DestBytesPerScanLine,&imagey,&imagex);

	imageshift = imagep->width;

	imagew = (0x00000001<<imageshift)-1;
	imageh = (0x00000001<<imagep->height)-1;

	imagex = 255 - imagex;

	imagey = 255 - imagey;

	switch (modvar)
	{
		case 0:
			imagex += 256;
			imagey += 256;
			break;
		case 1:
			imagey += 256;
			break;
		case 2:
			imagex += 256;
			break;
		case 3:
			break;
	}

	imagex &= imagew; imagey &= imageh;

	UByte*	imagescanlinep = &(imagep->data) + (imagey<<imageshift);

	//Test for single pixel first

	scanlines = GetScanLines(srcptr,bitpos);

	if (scanlines==0)
	{
		//Update the image buffer
		*workptr = *(imagescanlinep + imagex);
		return;
	}

	int	lhs_delta,rhs_delta;

	int	polymode,passno,polywidth,mode;

	//Line or polygon

	polymode = 1;
	passno = 1;

	polywidth = GetBits(srcptr,bitpos,7,0x7F);

	int	loop;
	UByte*	ptr;

	//Update the image buffer - just plain colour for the moment
	//	but needs to get imagemap data eventually

	if ((workptr+(ULong)polywidth)>endbuffer)
		goto _abort;

	for (	loop = polywidth,
			ptr = workptr,
			wimagex = imagex;
			loop;
			*ptr++ = *(imagescanlinep+wimagex),
			wimagex--,
			wimagex &= imagew,
			--loop
		);

	do
	{
		scanlines--;

		if (scanlines<polymode)	break;

		polymode = 0;

		//Get line or poly mode

		mode = GetBit(srcptr,bitpos);

		//Get deltas

		lhs_delta = GetDelta(srcptr,bitpos);

		if (!mode)
			rhs_delta = GetDelta(srcptr,bitpos);

		while (scanlines-->=passno)
		{
			int	lhs_add = lhs_delta + GetBit(srcptr,bitpos);

			workptr += DestBytesPerScanLine + lhs_add;

			imagex -= lhs_add; imagex &= imagew;

			imagey--; imagey &= imageh;

			imagescanlinep = &(imagep->data) + (imagey<<imageshift);

			if (!mode)
				polywidth += rhs_delta + GetBit(srcptr,bitpos) - lhs_add;

			//Update the image buffer - just plain colour for the moment
			//	but needs to get imagemap data eventually

			if ((workptr+(ULong)polywidth)>endbuffer)
				goto _abort;

			for (	loop = polywidth,
					ptr = workptr,
					wimagex = imagex;
					loop;
					*ptr++ = *(imagescanlinep+wimagex),
					wimagex--,
					wimagex &= imagew,
					--loop
				);
		}
		passno = 0;
	}
	while ((scanlines=GetScanLines(srcptr,bitpos))!=0);		

_abort:
	return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Maps512MirrorX
//Author		Paul.   
//Date			Mon 15 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::Maps512MirrorX(	UByte srccol,
									int	modvar,
									UByte*& srcptr, int& bitpos,
									UByte* workptr)
{
	ImageMapDescPtr	imagep;

	int	scanlines;

	//Generate index into imagemap

	int	wimagex,imagex,imagey;

	int	imagew,imageh;

	int	imageshift;

	int	delta = workptr-beginbuffer;

	imagep = colorindex[srccol].imagep;

//Old_Code PD 04Dec96 	imagey = delta / DestBytesPerScanLine;
//Old_Code PD 04Dec96 	imagex = delta % DestBytesPerScanLine;

	ASM_DivMod(delta,DestBytesPerScanLine,&imagey,&imagex);

	imageshift = imagep->width;

	imagew = (0x00000001<<imageshift)-1;
	imageh = (0x00000001<<imagep->height)-1;

	imagex = 255 - imagex;

	switch (modvar)
	{
		case 0:
			imagex += 256;
			break;
		case 1:
			imagex += 256;
			imagey += 256;
			break;
		case 2:
			break;
		case 3:
			imagey += 256;
			break;
	}

	imagex &= imagew; imagey &= imageh;

	UByte*	imagescanlinep = &(imagep->data) + (imagey<<imageshift);

	//Test for single pixel first

	scanlines = GetScanLines(srcptr,bitpos);

	if (scanlines==0)
	{
		//Update the image buffer
		*workptr = *(imagescanlinep + imagex);
		return;
	}

	int	lhs_delta,rhs_delta;

	int	polymode,passno,polywidth,mode;

	//Line or polygon

	polymode = 1;
	passno = 1;

	polywidth = GetBits(srcptr,bitpos,7,0x7F);

	int	loop;
	UByte*	ptr;

	//Update the image buffer - just plain colour for the moment
	//	but needs to get imagemap data eventually

	if ((workptr+(ULong)polywidth)>endbuffer)
		goto _abort;

	for (	loop = polywidth,
			ptr = workptr,
			wimagex = imagex;
			loop;
			*ptr++ = *(imagescanlinep+wimagex),
			wimagex--,
			wimagex &= imagew,
			--loop
		);

	do
	{
		scanlines--;

		if (scanlines<polymode)	break;

		polymode = 0;

		//Get line or poly mode

		mode = GetBit(srcptr,bitpos);

		//Get deltas

		lhs_delta = GetDelta(srcptr,bitpos);

		if (!mode)
			rhs_delta = GetDelta(srcptr,bitpos);

		while (scanlines-->=passno)
		{
			int	lhs_add = lhs_delta + GetBit(srcptr,bitpos);

			workptr += DestBytesPerScanLine + lhs_add;

			imagex -= lhs_add; imagex &= imagew;

			imagey++; imagey &= imageh;

			imagescanlinep = &(imagep->data) + (imagey<<imageshift);

			if (!mode)
				polywidth += rhs_delta + GetBit(srcptr,bitpos) - lhs_add;

			//Update the image buffer - just plain colour for the moment
			//	but needs to get imagemap data eventually

			if ((workptr+(ULong)polywidth)>endbuffer)
				goto _abort;

			for (	loop = polywidth,
					ptr = workptr,
					wimagex = imagex;
					loop;
					*ptr++ = *(imagescanlinep+wimagex),
					wimagex--,
					wimagex &= imagew,
					--loop
				);
		}
		passno = 0;
	}
	while ((scanlines=GetScanLines(srcptr,bitpos))!=0);		

_abort:
	return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Maps256NoMirror
//Author		Paul.   
//Date			Mon 15 Jul 1996
//
//Description	
//
//Optimised:	Now making the following assumptions...
//				(1) the source imagemaps are all 256x256 (obvios really!)
//				(2) no protection against wrapping around the edges of
//						the source imagemap  is required (I hope!)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::Maps256NoMirror(	UByte srccol,
									UByte*& srcptr, int& bitpos,
									UByte* workptr)
{
	ImageMapDescPtr	imagep;

	int	scanlines;

	//Generate index into imagemap

	int	imagex,imagey;

	int	delta = workptr-beginbuffer;

	imagep = colorindex[srccol].imagep;

	ASM_DivMod(delta,DestBytesPerScanLine,&imagey,&imagex);

	imagey &= 0xFF;	imagex &= 0xFF;

	UByte*	imagescanlinep = &(imagep->data) + (imagey<<8);

	//Test for single pixel first

	scanlines = GetScanLines(srcptr,bitpos);

	if (scanlines==0)
	{
		//Update the image buffer
		*workptr = *(imagescanlinep + imagex);
		return;
	}

	int	lhs_delta,rhs_delta;

	int	polymode,passno,polywidth,mode;

	//Line or polygon

	polymode = 1;
	passno = 1;

	polywidth = GetBits(srcptr,bitpos,7,0x7F);

	//Update the image buffer

	if ((workptr+(ULong)polywidth)>endbuffer)
		goto _abort;

	ASM_CopyImage(imagescanlinep+imagex,workptr,polywidth);

	do
	{
		scanlines--;

		if (scanlines<polymode)	break;

		polymode = 0;

		//Get line or poly mode

		mode = GetBit(srcptr,bitpos);

		//Get deltas

		lhs_delta = GetDelta(srcptr,bitpos);

		if (!mode)
			rhs_delta = GetDelta(srcptr,bitpos);

		while (scanlines-->=passno)
		{
			int	lhs_add = lhs_delta + GetBit(srcptr,bitpos);

			workptr += DestBytesPerScanLine + lhs_add;

			imagex += lhs_add;

			imagey++; imagey &= 0xFF;

			if (imagey==0)
				imagescanlinep = &(imagep->data);
			else
				imagescanlinep += 256;

			if (!mode)
				polywidth += rhs_delta + GetBit(srcptr,bitpos) - lhs_add;

			//Update the image buffer

			if ((workptr+(ULong)polywidth)>endbuffer)
				goto _abort;

			ASM_CopyImage(imagescanlinep+imagex,workptr,polywidth);
		}
		passno = 0;
	}
	while ((scanlines=GetScanLines(srcptr,bitpos))!=0);		

_abort:
	return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Maps256MirrorY
//Author		Paul.   
//Date			Mon 15 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::Maps256MirrorY(	UByte srccol,
									UByte*& srcptr, int& bitpos,
									UByte* workptr)
{
	ImageMapDescPtr	imagep;

	int	scanlines;

	//Generate index into imagemap

	int	imagex,imagey;

	int	delta = workptr-beginbuffer;

	imagep = colorindex[srccol].imagep;

	ASM_DivMod(delta,DestBytesPerScanLine,&imagey,&imagex);

	imagey = 0xFF - imagey;

	imagex &= 0xFF; imagey &= 0xFF;

	UByte*	imagescanlinep = &(imagep->data) + (imagey<<8);

	//Test for single pixel first

	scanlines = GetScanLines(srcptr,bitpos);

	if (scanlines==0)
	{
		//Update the image buffer
		*workptr = *(imagescanlinep + imagex);
		return;
	}

	int	lhs_delta,rhs_delta;

	int	polymode,passno,polywidth,mode;

	//Line or polygon

	polymode = 1;
	passno = 1;

	polywidth = GetBits(srcptr,bitpos,7,0x7F);

	//Update the image buffer

	if ((workptr+(ULong)polywidth)>endbuffer)
		goto _abort;

	ASM_CopyImage(imagescanlinep+imagex,workptr,polywidth);

	do
	{
		scanlines--;

		if (scanlines<polymode)	break;

		polymode = 0;

		//Get line or poly mode

		mode = GetBit(srcptr,bitpos);

		//Get deltas

		lhs_delta = GetDelta(srcptr,bitpos);

		if (!mode)
			rhs_delta = GetDelta(srcptr,bitpos);

		while (scanlines-->=passno)
		{
			int	lhs_add = lhs_delta + GetBit(srcptr,bitpos);

			workptr += DestBytesPerScanLine + lhs_add;

			imagex += lhs_add;

			imagey--; imagey &= 0xFF;
			
			if (imagey==0xFF)
				imagescanlinep = &(imagep->data) + (255*256);
			else
				imagescanlinep -= 256;
			
			if (!mode)
				polywidth += rhs_delta + GetBit(srcptr,bitpos) - lhs_add;

			//Update the image buffer

			if ((workptr+(ULong)polywidth)>endbuffer)
				goto _abort;

			ASM_CopyImage(imagescanlinep+imagex,workptr,polywidth);
		}
		passno = 0;
	}
	while ((scanlines=GetScanLines(srcptr,bitpos))!=0);		

_abort:
	return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Maps256MirrorXY
//Author		Paul.   
//Date			Mon 15 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::Maps256MirrorXY(	UByte srccol,
									UByte*& srcptr, int& bitpos,
									UByte* workptr)
{
	ImageMapDescPtr	imagep;

	int	scanlines;

	//Generate index into imagemap

	int	wimagex,imagex,imagey;

	int	imagew,imageh;

	int	imageshift;

	int	delta = workptr-beginbuffer;

	imagep = colorindex[srccol].imagep;

//Old_Code PD 04Dec96 	imagey = delta / DestBytesPerScanLine;
//Old_Code PD 04Dec96 	imagex = delta % DestBytesPerScanLine;

	ASM_DivMod(delta,DestBytesPerScanLine,&imagey,&imagex);

	imageshift = imagep->width;

	imagew = (0x00000001<<imageshift)-1;
	imageh = (0x00000001<<imagep->height)-1;

	imagex = imagew - imagex;

	imagey = imageh - imagey;

	imagex &= imagew; imagey &= imageh;

	UByte*	imagescanlinep = &(imagep->data) + (imagey<<imageshift);

	//Test for single pixel first

	scanlines = GetScanLines(srcptr,bitpos);

	if (scanlines==0)
	{
		//Update the image buffer
		*workptr = *(imagescanlinep + imagex);
		return;
	}

	int	lhs_delta,rhs_delta;

	int	polymode,passno,polywidth,mode;

	//Line or polygon

	polymode = 1;
	passno = 1;

	polywidth = GetBits(srcptr,bitpos,7,0x7F);

	int	loop;
	UByte*	ptr;

	//Update the image buffer - just plain colour for the moment
	//	but needs to get imagemap data eventually

	if ((workptr+(ULong)polywidth)>endbuffer)
		goto _abort;

	for (	loop = polywidth,
			ptr = workptr,
			wimagex = imagex;
			loop;
			*ptr++ = *(imagescanlinep+wimagex),
			wimagex--,
			wimagex &= imagew,
			--loop
		);

	do
	{
		scanlines--;

		if (scanlines<polymode)	break;

		polymode = 0;

		//Get line or poly mode

		mode = GetBit(srcptr,bitpos);

		//Get deltas

		lhs_delta = GetDelta(srcptr,bitpos);

		if (!mode)
			rhs_delta = GetDelta(srcptr,bitpos);

		while (scanlines-->=passno)
		{
			int	lhs_add = lhs_delta + GetBit(srcptr,bitpos);

			workptr += DestBytesPerScanLine + lhs_add;

			imagex -= lhs_add; imagex &= imagew;

			imagey--; imagey &= imageh;

			imagescanlinep = &(imagep->data) + (imagey<<imageshift);

			if (!mode)
				polywidth += rhs_delta + GetBit(srcptr,bitpos) - lhs_add;

			//Update the image buffer - just plain colour for the moment
			//	but needs to get imagemap data eventually

			if ((workptr+(ULong)polywidth)>endbuffer)
				goto _abort;

			for (	loop = polywidth,
					ptr = workptr,
					wimagex = imagex;
					loop;
					*ptr++ = *(imagescanlinep+wimagex),
					wimagex--,
					wimagex &= imagew,
					--loop
				);
		}
		passno = 0;
	}
	while ((scanlines=GetScanLines(srcptr,bitpos))!=0);		

_abort:
	return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Maps256MirrorX
//Author		Paul.   
//Date			Mon 15 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::Maps256MirrorX(	UByte srccol,
									UByte*& srcptr, int& bitpos,
									UByte* workptr)
{
	ImageMapDescPtr	imagep;

	int	scanlines;

	//Generate index into imagemap

	int	wimagex,imagex,imagey;

	int	imagew,imageh;

	int	imageshift;

	int	delta = workptr-beginbuffer;

	imagep = colorindex[srccol].imagep;

//Old_Code PD 04Dec96 	imagey = delta / DestBytesPerScanLine;
//Old_Code PD 04Dec96 	imagex = delta % DestBytesPerScanLine;

	ASM_DivMod(delta,DestBytesPerScanLine,&imagey,&imagex);

	imageshift = imagep->width;

	imagew = (0x00000001<<imageshift)-1;
	imageh = (0x00000001<<imagep->height)-1;

	imagex = imagew - imagex;

	imagex &= imagew; imagey &= imageh;

	UByte*	imagescanlinep = &(imagep->data) + (imagey<<imageshift);

	//Test for single pixel first

	scanlines = GetScanLines(srcptr,bitpos);

	if (scanlines==0)
	{
		//Update the image buffer
		*workptr = *(imagescanlinep + imagex);
		return;
	}

	int	lhs_delta,rhs_delta;

	int	polymode,passno,polywidth,mode;

	//Line or polygon

	polymode = 1;
	passno = 1;

	polywidth = GetBits(srcptr,bitpos,7,0x7F);

	int	loop;
	UByte*	ptr;

	//Update the image buffer - just plain colour for the moment
	//	but needs to get imagemap data eventually

	if ((workptr+(ULong)polywidth)>endbuffer)
		goto _abort;

	for (	loop = polywidth,
			ptr = workptr,
			wimagex = imagex;
			loop;
			*ptr++ = *(imagescanlinep+wimagex),
			wimagex--,
			wimagex &= imagew,
			--loop
		);

	do
	{
		scanlines--;

		if (scanlines<polymode)	break;

		polymode = 0;

		//Get line or poly mode

		mode = GetBit(srcptr,bitpos);

		//Get deltas

		lhs_delta = GetDelta(srcptr,bitpos);

		if (!mode)
			rhs_delta = GetDelta(srcptr,bitpos);

		while (scanlines-->=passno)
		{
			int	lhs_add = lhs_delta + GetBit(srcptr,bitpos);

			workptr += DestBytesPerScanLine + lhs_add;

			imagex -= lhs_add; imagex &= imagew;

			imagey++; imagey &= imageh;

			imagescanlinep = &(imagep->data) + (imagey<<imageshift);

			if (!mode)
				polywidth += rhs_delta + GetBit(srcptr,bitpos) - lhs_add;

			//Update the image buffer - just plain colour for the moment
			//	but needs to get imagemap data eventually

			if ((workptr+(ULong)polywidth)>endbuffer)
				goto _abort;

			for (	loop = polywidth,
					ptr = workptr,
					wimagex = imagex;
					loop;
					*ptr++ = *(imagescanlinep+wimagex),
					wimagex--,
					wimagex &= imagew,
					--loop
				);
		}
		passno = 0;
	}
	while ((scanlines=GetScanLines(srcptr,bitpos))!=0);		

_abort:
	return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlainColour
//Author		Paul.   
//Date			Mon 15 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::PlainColour(	UByte srccol,
								UByte*& srcptr, int& bitpos,
								UByte* workptr)
{
	int	scanlines;

	UByte color = (UByte )colorindex[srccol].color;

	//Test for single pixel first

	scanlines = GetScanLines(srcptr,bitpos);

	if (scanlines==0)
	{
		//Update the image buffer - just plain colour for the moment
		//	but needs to get imagemap data eventually

		*workptr=color;
		return;
	}

	int	lhs_delta,rhs_delta;

	int	polymode,passno,polywidth,mode;

	//Line or polygon

	polymode = 1;
	passno = 1;

	polywidth = GetBits(srcptr,bitpos,7,0x7F);

	int	loop;
	UByte*	ptr;

	//Update the image buffer - just plain colour for the moment
	//	but needs to get imagemap data eventually

	if ((workptr+(ULong)polywidth)>endbuffer)
		goto _abort;

	for (loop=polywidth,ptr=workptr;loop;*ptr++=color,--loop);

	do
	{
		scanlines--;

		if (scanlines<polymode)	break;

		polymode = 0;

		//Get line or poly mode

		mode = GetBit(srcptr,bitpos);

		//Get deltas

		lhs_delta = GetDelta(srcptr,bitpos);

		if (!mode)
			rhs_delta = GetDelta(srcptr,bitpos);

		while (scanlines-->=passno)
		{
			int	lhs_add = lhs_delta + GetBit(srcptr,bitpos);

			workptr += DestBytesPerScanLine + lhs_add;

			if (!mode)
				polywidth += rhs_delta + GetBit(srcptr,bitpos) - lhs_add;

			//Update the image buffer - just plain colour for the moment
			//	but needs to get imagemap data eventually

			if ((workptr+(ULong)polywidth)>endbuffer)
				goto _abort;

			for (loop=polywidth,ptr=workptr;loop;*ptr++=color,--loop);
		}
		passno = 0;
	}
	while ((scanlines=GetScanLines(srcptr,bitpos))!=0);		

_abort:
	return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnpackAltitudeData
//Author		Paul.   
//Date			Wed 17 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::UnpackAltitudeData(Bool compressed, UByte*& srcptr, UByte* destptr)
{
	//Zero altitude buffer for now

	if (!compressed)
	{
		ASM_Blat(srcptr, destptr, AltDataSize-1);				//PD 08Oct96
		srcptr += AltDataSize-1;								//PD 08Oct96
	}
	else
		DecompressAltitude(srcptr,destptr);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecompressAltitude
//Author		Paul.   
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::DecompressAltitude(UByte*& srcptr,UByte* destptr)
{
	int 	bitpos = 0;
	UByte	altitudes[AltBytesPerScanLine];
	UByte	mainbody[AltDataSize];
	UByte	destdat[AltDataSize];
	UByte	srcpixel;

// read first pixel (0,0)

	srcpixel=GetByte(srcptr,bitpos);

	*destdat = *mainbody = *altitudes = srcpixel;

// get LHS

	BuildAltitudes(34,altitudes,srcptr,bitpos,srcpixel);

	{
	UByte 	*ddp=destdat+AltBytesPerScanLine,
			*mbp=mainbody+AltBytesPerScanLine,
			*alp=altitudes+1,
			*aep=altitudes+AltBytesPerScanLine;
	while (alp<aep)
	{
		*ddp=*mbp=*alp;
		alp++;
		ddp+=AltBytesPerScanLine;
		mbp+=AltBytesPerScanLine;
	}
	}
			
// get top side

	BuildAltitudes(34,altitudes,srcptr,bitpos,srcpixel);

	{
	UWord	*ddp=(UWord*)((UByte*)destdat+1),
			*mbp=(UWord*)((UByte*)mainbody+1),
			*alp=(UWord*)((UByte*)altitudes+1),
			*aep=(UWord*)((UByte*)altitudes+AltBytesPerScanLine);
	while (alp<aep)
	{
		*ddp=*mbp=*alp;
		alp++;
		ddp++;
		mbp++;
	}
	}

// get main body

	BuildMainBody(AltBytesPerScanLine,AltBytesPerScanLine,mainbody,srcptr,bitpos);

	{
	UByte	*ddp=destdat+1+AltBytesPerScanLine,
			*mbp=mainbody+1+AltBytesPerScanLine;

	for (	int q=1;
			q<AltBytesPerScanLine;
			ddp+=AltBytesPerScanLine,
			mbp+=AltBytesPerScanLine,
			q++)
		{
			UByte 	*tddp=ddp,*tmbp=mbp;
			for (int w=0;w<AltBytesPerScanLine;*tddp++=*tmbp++,w++);
		}
	}

	ASM_Blat(&destdat[0], destptr, 35*35);

	if (bitpos!=0)
	{
		srcptr++; bitpos = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildAltitudes
//Author		Paul.   
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::BuildAltitudes(int thislength,UByte* altitudes,UByte*& srcptr,int& bitpos,int srcpixel)
{
	int		delta;
	Bool	recurse,sign;

	if(thislength==1)
		recurse=FALSE;
	else
		recurse=(Bool)GetBit(srcptr,bitpos);

	if(!recurse)
	{
		// no sub division so get delta

		sign = (Bool)GetBit(srcptr,bitpos);

		switch (thislength)
		{
			case 34:
				delta = GetBits(srcptr,bitpos,7,0x7F);
				break;
			case 17:
				delta = GetBits(srcptr,bitpos,6,0x3F);
				break;
			case 8:
			case 9:
				delta = GetBits(srcptr,bitpos,5,0x1F);
				break;
			case 4:
			case 5:
				delta = GetBits(srcptr,bitpos,4,0x0F);
	 			break;
			case 2:
			case 3:
				delta = GetBits(srcptr,bitpos,LEVEL2BITS,LEVEL2BITS_MASK);
				break;
			case 1:
				delta = GetBits(srcptr,bitpos,SINGLEBITS,SINGLEBITS_MASK);

				// if delta is 100 (-0) then get big delta

				if(delta==0 && sign)
				{
					sign = (Bool)GetBit(srcptr,bitpos);
					delta = GetBits(srcptr,bitpos,7,0x7F);
				}
				break;
		}
		if (sign)
			delta = -delta;

		// fill in altitudes

		AltDDA(altitudes+1,srcpixel,srcpixel+delta,thislength);
	}
	else
	{
		// sub division has occured

		switch (thislength)
		{
			case 34:
				BuildAltitudes(17,&altitudes[0],srcptr,bitpos,srcpixel);
				BuildAltitudes(17,&altitudes[17],srcptr,bitpos,altitudes[17]);
				break;

			case 17:
				BuildAltitudes(8,&altitudes[0],srcptr,bitpos,srcpixel);
				BuildAltitudes(9,&altitudes[8],srcptr,bitpos,altitudes[8]);
				break;

			case 8:
				BuildAltitudes(4,&altitudes[0],srcptr,bitpos,srcpixel);
				BuildAltitudes(4,&altitudes[4],srcptr,bitpos,altitudes[4]);
				break;

			case 9:
				BuildAltitudes(4,&altitudes[0],srcptr,bitpos,srcpixel);
				BuildAltitudes(5,&altitudes[4],srcptr,bitpos,altitudes[4]);
				break;

			case 5:
				BuildAltitudes(2,&altitudes[0],srcptr,bitpos,srcpixel);
				BuildAltitudes(3,&altitudes[2],srcptr,bitpos,altitudes[2]);
				break;

			case 4:
				BuildAltitudes(2,&altitudes[0],srcptr,bitpos,srcpixel);
				BuildAltitudes(2,&altitudes[2],srcptr,bitpos,altitudes[2]);
				break;

			case 3:
				BuildAltitudes(1,&altitudes[0],srcptr,bitpos,srcpixel);
				BuildAltitudes(2,&altitudes[1],srcptr,bitpos,altitudes[1]);
				break;

			case 2:
				BuildAltitudes(1,&altitudes[0],srcptr,bitpos,srcpixel);
				BuildAltitudes(1,&altitudes[1],srcptr,bitpos,altitudes[1]);
				break;

			case 1:
			default:
				break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildMainBody
//Author		Paul.   
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::BuildMainBody(int xlength,int ylength,UByte* mainbody,
								UByte*& srcptr,int& bitpos)
{
	int		x,y;
	Bool	recurse,sign;
	int		delta;
	int		xdiff,xdiff2;
	int		ydiff,ydiff2;
	int		top,bottom;
	int		topright,topleft,botleft,botright;

	if(xlength==2 && ylength==2)
	{
		// if area is 1 x 1 (xlength=2,ylength=2)
		// then dont recurse. Use recurse flag as indicator
		// for big delta

		recurse=FALSE;
	}
	else
		recurse = (Bool)GetBit(srcptr,bitpos);

	if(!recurse)
	{
		// no sub division so get delta

		sign = (Bool)GetBit(srcptr,bitpos);

		switch(xlength-1)
		{
			case 34:
				delta = GetBits(srcptr,bitpos,7,0x7F);
				break;
			case 17:
				delta = GetBits(srcptr,bitpos,6,0x3F);
				break;
			case 8:
			case 9:
				delta = GetBits(srcptr,bitpos,5,0x1F);
				break;
			case 4:
			case 5:
				delta = GetBits(srcptr,bitpos,4,0x0F);
	 			break;
			case 2:
			case 3:
				delta = GetBits(srcptr,bitpos,LEVEL2BITS,LEVEL2BITS_MASK);
				break;
			case 1:
				if(ylength==3)
					delta = GetBits(srcptr,bitpos,SINGLEBITS,SINGLEBITS_MASK);
				else
				{
					delta = GetBits(srcptr,bitpos,SINGLEBITS,SINGLEBITS_MASK);

					if(delta==0 && sign)
					{
						sign = (Bool)GetBit(srcptr,bitpos);
						delta = GetBits(srcptr,bitpos,7,0x7F);
					}
				}
				break;
		}

		if (sign)
			delta = -delta;

		// fill in altitudes

		topleft=mainbody[0];
		topright=mainbody[xlength-1];
		botleft=mainbody[(ylength-1)*AltBytesPerScanLine];
		botright=(topright+botleft-topleft)-delta;

		if(xlength==2 && ylength==2)
		{
			mainbody[1+AltBytesPerScanLine]=(UByte)botright;
		}
		else
		{
			// LHS - already known - no need to work out again

			// RHS

			AltDDA2(mainbody+xlength-1+AltBytesPerScanLine,topright,botright,ylength-1);

			top=topright;
			bottom=botright;

			// rows
			if(xlength>2)
			{

				UByte 	*mblp = mainbody+AltBytesPerScanLine,
						*mbrp = mainbody+AltBytesPerScanLine+xlength-1;

				for (y=1;y<ylength;y++)
				{
					top = *mblp;
					bottom = *mbrp;
					AltDDA3(mblp+1,top,bottom,xlength-1);
					mblp += AltBytesPerScanLine;
					mbrp += AltBytesPerScanLine;
				}
			}
		}
	}
	else
	{
		// sub division has occured

		switch(xlength-1)
		{
			case 34:
				BuildMainBody(18,18,mainbody,srcptr,bitpos);
				BuildMainBody(18,18,&mainbody[17],srcptr,bitpos);
				BuildMainBody(18,18,&mainbody[17*AltBytesPerScanLine],srcptr,bitpos);
				BuildMainBody(18,18,&mainbody[17+17*AltBytesPerScanLine],srcptr,bitpos);
				break;

			case 17:
				BuildMainBody(9,9,mainbody,srcptr,bitpos);
				BuildMainBody(10,9,&mainbody[8],srcptr,bitpos);
				BuildMainBody(9,10,&mainbody[8*AltBytesPerScanLine],srcptr,bitpos);
				BuildMainBody(10,10,&mainbody[8+8*AltBytesPerScanLine],srcptr,bitpos);
				break;

			case 9:
				BuildMainBody(5,5,mainbody,srcptr,bitpos);
				BuildMainBody(6,5,&mainbody[4],srcptr,bitpos);
				if((ylength-1)==9)
				{
					BuildMainBody(5,6,&mainbody[4*AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(6,6,&mainbody[4+4*AltBytesPerScanLine],srcptr,bitpos);
				}
				else
				{
					BuildMainBody(5,5,&mainbody[4*AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(6,5,&mainbody[4+4*AltBytesPerScanLine],srcptr,bitpos);
				}
				break;

			case 8:
				BuildMainBody(5,5,mainbody,srcptr,bitpos);
				BuildMainBody(5,5,&mainbody[4],srcptr,bitpos);
				if((ylength-1)==8)
				{
					BuildMainBody(5,5,&mainbody[4*AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(5,5,&mainbody[4+4*AltBytesPerScanLine],srcptr,bitpos);
				}
				else
				{
					BuildMainBody(5,6,&mainbody[4*AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(5,6,&mainbody[4+4*AltBytesPerScanLine],srcptr,bitpos);
				}

				break;

			case 5:
				BuildMainBody(3,3,mainbody,srcptr,bitpos);
				BuildMainBody(4,3,&mainbody[2],srcptr,bitpos);
				if((ylength-1)==5)
				{
					BuildMainBody(3,4,&mainbody[2*AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(4,4,&mainbody[2+2*AltBytesPerScanLine],srcptr,bitpos);
				}
				else
				{
					BuildMainBody(3,3,&mainbody[2*AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(4,3,&mainbody[2+2*AltBytesPerScanLine],srcptr,bitpos);
				}
				break;

			case 4:
				BuildMainBody(3,3,mainbody,srcptr,bitpos);
				BuildMainBody(3,3,&mainbody[2],srcptr,bitpos);
				if((ylength-1)==4)
				{
					BuildMainBody(3,3,&mainbody[2*AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(3,3,&mainbody[2+2*AltBytesPerScanLine],srcptr,bitpos);
				}
				else
				{
					BuildMainBody(3,4,&mainbody[2*AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(3,4,&mainbody[2+2*AltBytesPerScanLine],srcptr,bitpos);
				}
				break;

			case 3:
				BuildMainBody(2,2,mainbody,srcptr,bitpos);
				BuildMainBody(3,2,&mainbody[1],srcptr,bitpos);
				if((ylength-1)==3)
				{
					BuildMainBody(2,3,&mainbody[AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(3,3,&mainbody[1+AltBytesPerScanLine],srcptr,bitpos);
				}
				else
				{
					BuildMainBody(2,2,&mainbody[AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(3,2,&mainbody[1+AltBytesPerScanLine],srcptr,bitpos);
				}
				break;

			case 2:
				BuildMainBody(2,2,mainbody,srcptr,bitpos);
				BuildMainBody(2,2,&mainbody[1],srcptr,bitpos);
				if((ylength-1)==1)
				{
					break;
				}
				if((ylength-1)==2)
				{
					BuildMainBody(2,2,&mainbody[AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(2,2,&mainbody[1+AltBytesPerScanLine],srcptr,bitpos);
				}
				else												    
				{
					BuildMainBody(2,3,&mainbody[AltBytesPerScanLine],srcptr,bitpos);
					BuildMainBody(2,3,&mainbody[1+AltBytesPerScanLine],srcptr,bitpos);
				}
				break;

			case 1:
				if((ylength-1)==2)
				{
					BuildMainBody(2,2,mainbody,srcptr,bitpos);
					BuildMainBody(2,2,&mainbody[AltBytesPerScanLine],srcptr,bitpos);
				}
				break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AliasTile
//Author		Paul.   
//Date			Tue 16 Jul 1996
//
//Description	Route aliasing code
//
//Inputs	beginbuffer = ptr to start of the decompressed data
//			rdestptr = ptr to target area
//
//			ailtbl16p = 1/16 anti-alias table
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::AliasTile(UByte* srcptr,UByte* rdestptr)
{
	Bool	bDoingHW3D=FALSE;
	if (currwin)
		bDoingHW3D = currwin->DoingHardware3D();				//PD 19Nov97

	if (Save_Data.detail_3d[DETAIL3D_ANTIALIAS] && !bDoingHW3D)
	{
		ASM_WidenRoutes(srcptr);
		ASM_AliasTile(srcptr,rdestptr,ailclrindexp,ailtbl16p);
	}
	else
		ASM_NoAliasTile(rdestptr,rdestptr,ailclrindexp,ailtbl16p);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShadeTile
//Author		Paul.   
//Date			Wed 17 Jul 1996
//
//Description	
//					A------B--
//					|	   |
//					|	   |
//					|	   |
//					|	   |
//					|	   |
//					C------D--
//
//
//
//Inputs		cdatap = ptr to decompressed colour data
//				adatap = ptr to decompressed altitude data
//
//Returns		colour data shaded based on the altitude data
//
//------------------------------------------------------------------------------
void Land_Stream::ShadeTile(UByte* cdatap, UByte* adatap)
{
	//Generate light intensity grid for the tile

	SByte	igrid[(AltBytesPerScanLine-1)*(AltBytesPerScanLine-1)];

	int		x,y;

	int		igx,igy;

	for (	igy=0,y=1;
			y<AltBytesPerScanLine;
			igy++,y++)
	{
		int	rowindex 	= y*AltBytesPerScanLine;
		int	igrowindex	= igy*(AltBytesPerScanLine-1);

		for (	igx=0,x=1;
				x<AltBytesPerScanLine;
				igx++,x++)
		{
			int	index 	=	rowindex+x;
			int	igindex =	igrowindex+igx;

		 	int	dYx=adatap[index-1] - adatap[index+1];
			int dYz=adatap[index-AltBytesPerScanLine] -
					adatap[index+AltBytesPerScanLine];

			dYx <<= (Y_RES_SCALE-2);
			dYz <<= (Y_RES_SCALE-2);

			const int dX = 0x1<<XZ_ALT_SCALE;

			//resulting normal vector

			IFShare	a,b,c;

			a.f = (Float)-dYx;
			b.f = (Float)dX;
			c.f = (Float)-dYz;

			Float mag;
					
			mag = (a.f*a.f)+(b.f*b.f)+(c.f*c.f);

			fpSqrt(mag);

			a.f /= mag; b.f /= mag; c.f /= mag;

			IFShare	lx,ly,lz;

			lx.f = (Float)1.0/(Float)1.41421;
			ly.f = (Float)1.0/(Float)1.41421;
			lz.f = (Float)0.0;

			mag = (a.f*lx.f)+(b.f*ly.f)+(c.f*lz.f);

			mag *= (Float)127.0;

			SLong	intensity;

			intensity = ((SLong )mag);

			if (intensity<-127)	intensity = -127;
			if (intensity>127)	intensity = 127;

			igrid[igindex]=(SByte)intensity;
		}
	}

	//Apply intensities to colour map

	for (y=0;y<DestBytesPerScanLine-1;y+=8)
	{
		int	irowindex=(y>>3)*(AltBytesPerScanLine-1);

		int crowindex=y*DestBytesPerScanLine;

		for (x=0;x<DestBytesPerScanLine-1;x+=8)
		{
			int iindex=irowindex+(x>>3);

			int cindex=crowindex+x;

			ApplyLShade(cdatap,cindex,igrid,iindex);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyLShade
//Author		Paul.   
//Date			Wed 15 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ApplyLShade(UByte* cdatap,int cindex,SByte* idatap,int iindex)
{
	UWord	jitter;

	int	i[4];

	i[0] = ((int )idatap[iindex])<<8;
	i[1] = ((int )idatap[iindex+1])<<8;
	i[2] = ((int )idatap[iindex+AltBytesPerScanLine-1])<<8;
	i[3] = ((int )idatap[iindex+AltBytesPerScanLine])<<8;

	jitter = *(UWord*)cdatap;	//Randomish start value

	int	lvdi,rvdi;

	lvdi = (i[2]-i[0])>>3;
	rvdi = (i[3]-i[1])>>3;

	int	li = i[0];
	int	ri = i[1];

	UByte	*crowp;

	crowp = cdatap + cindex;

	for (int row=0;row<8;row++)
	{
		int hdi = (ri-li)>>3;
		int hi = li;

		UByte *lcrowp;

		lcrowp = crowp;

		for (int column=0;column<8;column++)
		{
			SWord	jd;
			jd = ((SWord)jitter)>>8;
			jd += hi;
			jd >>= 12;
			*lcrowp=preshadetable[15+(32**lcrowp)+jd];
			hi += hdi;
			lcrowp++;
			UWord	jitter2;
			jitter 	+= 0x9136;
			jitter2 = (jitter & 0x0007)<<13;
			jitter 	>>= 3;
			jitter 	|= jitter2;
		}
		li += lvdi;
		ri += rvdi;
		crowp += DestBytesPerScanLine;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecompressTile
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::DecompressTile(UByte* dataarea,UByte*& cdestptr)
{
	if (cdestptr==NULL)
		cdestptr = new UByte[ColourDataSize+AltDataSize];

	assert((cdestptr)&&(" - decompress buffer alloc failed!"));	//PD 29Aug96

	UByte* 	adestptr = cdestptr + ColourDataSize;

	Decompress(dataarea, cdestptr, adestptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitialiseCache
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::InitialiseCache()
{


	currwin=NULL;
	if (firstcall)
	{
		Init(); firstcall=FALSE;
	}

	LDataScales	scalecount;

	for (scalecount=LDS_AliasX2;scalecount<LDS_MAX;scalecount = (LDataScales)(scalecount+1))
	{
		cachescale[scalecount] = NULL;
		dumpscale[scalecount] = NULL;
		cachereq[scalecount] = NULL;
		cachecount[scalecount] = 0;
	}
	cachemax[LDS_AliasX2] = MaxLDSAliasX2;
	cachemax[LDS_AliasX1] = MaxLDSAliasX1;
	cachemax[LDS_Normal] = MaxLDSNormal;
	cachemax[LDS_Half] = MaxLDSHalf;
	cachemax[LDS_Quarter] = MaxLDSQuarter;
	cachemax[LDS_Eighth] = MaxLDSEighth;						//PD 15Apr97
	cachemax[LDS_Sixteenth] = MaxLDSSixteenth;					//PD 15Apr97

	bigcachep[0] =
		bigdumpp[0] = NULL;

	if (bigcachecount!=0)
#ifdef __WATCOMC__
		INT3();													//JIM 19Jun97
#endif
#ifdef __MSVC__
		INT3;
#endif
	bigcachecount = 0;
	bigcachemax = BIG_TILES_MAX;

	requestcount=0;												//PD 01Aug96
}

static	Bool	blockdelete=FALSE;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetBlockDelete
//Author		Paul.   
//Date			Thu 9 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SetBlockDelete(Bool newval)
{
	blockdelete=newval;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteDisplayCache
//Author		Jim Taylor
//Date			Mon 6 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Land_Stream::DeleteDisplayCache(Bool onelayeronly)
{
	if (blockdelete)	return(FALSE);
	Bool	rv=FALSE;
	LDataScales	scalecount;
	for (scalecount=LDS_AliasX2;scalecount<LDS_MAX;scalecount=(LDataScales)(scalecount+1))
	{
		CacheBlockP	scanp,nextp;
		
		scanp = dumpscale[scalecount];

		dumpscale[scalecount] = NULL;
		cachescale[scalecount] = NULL;
		cachereq[scalecount] = NULL;
		cachecount[scalecount] = 0;

		if (scanp!=NULL)
		{
			do													//JIM 06Jan97
			{
				nextp = scanp->next;
				delete (scanp->data);
				delete (scanp);
				scanp = nextp;
			}
			while (scanp!=NULL);									//JIM 06Jan97
			rv=TRUE;
			if (onelayeronly)
				RETURN(TRUE);
		}
	}
	return rv;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteCache
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::DeleteCache()
{
	DeleteDisplayCache();

//DeadCode DAW 07Jan97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 07Jan97 //Procedure		DeleteCache
//DeadCode DAW 07Jan97 //Author		Paul.   
//DeadCode DAW 07Jan97 //Date			Wed 31 Jul 1996
//DeadCode DAW 07Jan97 //
//DeadCode DAW 07Jan97 //Description	
//DeadCode DAW 07Jan97 //
//DeadCode DAW 07Jan97 //Inputs		
//DeadCode DAW 07Jan97 //
//DeadCode DAW 07Jan97 //Returns	
//DeadCode DAW 07Jan97 //
//DeadCode DAW 07Jan97 //------------------------------------------------------------------------------
//DeadCode DAW 07Jan97 void Land_Stream::DeleteCache()
//DeadCode DAW 07Jan97 {
//DeadCode DAW 07Jan97 	LDataScales	scalecount;
//DeadCode DAW 07Jan97 
//DeadCode DAW 07Jan97 	for (scalecount=LDS_AliasX2;scalecount<LDS_MAX;scalecount=(LDataScales)(scalecount+1))
//DeadCode DAW 07Jan97 	{
//DeadCode DAW 07Jan97 		CacheBlockP	scanp,nextp;
//DeadCode DAW 07Jan97 		
//DeadCode DAW 07Jan97 		scanp = dumpscale[scalecount];
//DeadCode DAW 07Jan97 
//DeadCode DAW 07Jan97 		while (scanp!=NULL)										//PD 01Aug96
//DeadCode DAW 07Jan97 		{
//DeadCode DAW 07Jan97 			nextp = scanp->next;
//DeadCode DAW 07Jan97 
//DeadCode DAW 07Jan97 			delete (scanp->data);
//DeadCode DAW 07Jan97 
//DeadCode DAW 07Jan97 			delete (scanp);
//DeadCode DAW 07Jan97 
//DeadCode DAW 07Jan97 			scanp = nextp;
//DeadCode DAW 07Jan97 		}
//DeadCode DAW 07Jan97 
//DeadCode DAW 07Jan97 		dumpscale[scalecount] = NULL;
//DeadCode DAW 07Jan97 
//DeadCode DAW 07Jan97 		cachescale[scalecount] = NULL;
//DeadCode DAW 07Jan97 
//DeadCode DAW 07Jan97 		cachereq[scalecount] = NULL;
//DeadCode DAW 07Jan97 
//DeadCode DAW 07Jan97 		cachecount[scalecount] = 0;
//DeadCode DAW 07Jan97 	}

	//dispose of cached 257x257 tiles

	BigCacheBlockP	bscanp,bnextp;

	bscanp = bigdumpp[0];										//PD 19Jun97

	while (bscanp!=NULL)
	{
	 	bnextp = bscanp->next;

		delete (bscanp->data);

		delete (bscanp);

		bscanp = bnextp;
	}
	bigdumpp[0] =
		bigcachep[0] = NULL;

	bigcachecount=0;											//JIM 19Jun97

	requestcount=0;												//PD 01Aug96

	UnLoadLandMaps();											//PD 27Aug96

	if (ailclrindexp!=NULL)										//AM 18Jun97
	{															//AM 18Jun97
		delete [] ailclrindexp;									//AM 18Jun97
		ailclrindexp = NULL;									//AM 18Jun97
	}															//AM 18Jun97

	if (shadeindexp!=NULL)										//AM 18Jun97
	{															//AM 18Jun97
		delete [] shadeindexp;									//AM 18Jun97
		shadeindexp = NULL;										//AM 18Jun97
	}															//AM 18Jun97

	if (tbuffer!=NULL)											//AM 18Jun97
	{															//AM 18Jun97
		delete [] tbuffer;										//AM 18Jun97
		tbuffer = NULL;											//AM 18Jun97
	}															//AM 18Jun97

	if (dummyimagep!=NULL)										//AM 18Jun97
	{															//AM 18Jun97
		delete dummyimagep;										//AM 18Jun97
		dummyimagep = NULL;										//AM 18Jun97
	}															//AM 18Jun97

	firstcall = TRUE;											//PD 02Aug96

	POLYGON.ClearAliasFlag();									//RJS 29Oct96

	//Deallocate the compressed data buffers

	for (int bcz=0;bcz<BIG_CACHE_SIZE*BIG_CACHE_SIZE;bcz++)
	{
		if (bigareacahe[bcz]!=NULL)
			delete (bigareacahe[bcz]);
		bigareacahe[bcz]=NULL;
	}

	for (bcz=0;bcz<BIG_CACHE_SIZE*BIG_EDGE_SIZE;bcz++)
	{
		if (rcbuffer0[bcz]!=NULL)
			delete (rcbuffer0[bcz]);
		if (rcbuffer1[bcz]!=NULL)
			delete (rcbuffer1[bcz]);
		rcbuffer0[bcz] =
			rcbuffer1[bcz] = NULL;
	}

	SeekStrucP	ssp,nssp;

	ssp = masterseeklist;										//PD 13Nov96
	masterseeklist = NULL;

	while (ssp)
	{
		nssp=ssp->next;
		delete(ssp);
		ssp=nssp;
	}

	FILEMAN.CloseAreaFiles();									//PD 18Nov96

	//Reset cached landscape data to all zeros

	if (Land_Scape.landdata!=NULL)								//PD 09Dec96
	{
//Old_Code DAW 24Oct97 		ULong*	lptemp;
//Old_Code DAW 24Oct97 
//Old_Code DAW 24Oct97 		lptemp=(ULong*)&(Land_Scape.landdata->data);
//Old_Code DAW 24Oct97 
//Old_Code DAW 24Oct97 		for (int ldcount=0;ldcount<16*0x4000;*lptemp++=0x0,ldcount++);

		if (currwin && currwin->DoingHardware3D())					//PD 19Nov97
		{
			//Check on the size of the buffer before
			//it gets wiped

			if (Land_Scape.landdata->width!=0x0A)
			{
				delete (UByte*)Land_Scape.landdata;
				Land_Scape.landdata=NULL;
				Land_Scape.LoadLandData();
			}
			else
			{
				ULong*	lptemp;

				lptemp=(ULong*)&(Land_Scape.landdata->data);

				for (int ldcount=0;ldcount<16*0x4000;*lptemp++=0x0,ldcount++);
			}
		}
		else
		{
			//Check on the size of the buffer before
			//it gets wiped

			if (Land_Scape.landdata->width!=0x08)
			{
				delete (UByte*)Land_Scape.landdata;
				Land_Scape.landdata=NULL;
				Land_Scape.LoadLandData();
			}
			else
			{
				ULong*	lptemp;

				lptemp=(ULong*)&(Land_Scape.landdata->data);

				for (int ldcount=0;ldcount<0x4000;*lptemp++=0x0,ldcount++);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RequestBlock
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
LandMapDescPtr
Land_Stream::RequestBlock(SLong wx, SLong wz, SWord iscale)
{
	LDataScales scale = (LDataScales )iscale;

	//Search cachescale[scale] for a matching block

	CacheBlockP scanp;

	if (FindCacheEntry(&cachescale[scale],wx,wz,scanp))
	{
		//Move this block to the head of the discard list

		UpdateDiscardList(scale,scanp);

  		scanp->data->tileseg = TS_Whole;

		return (scanp->data);
	}

	//Unable to find this block in the cache

	//See if this block is available at a lower resolution

	LDataScales	scalecount = (LDataScales)(scale + 1);

	ULong	coordsmask = ~((0x00000001<<(scalecount+3))-1);
	
	SLong	swx = wx & coordsmask;

	SLong	swz = wz & coordsmask;

	if (FindCacheEntry(&cachescale[scalecount],swx,swz,scanp)
		&& scanp->data->tileseg!=TS_NotATileMap)
	{
		if (swz-wz==0)
		{
			if (swx-wx==0)
				scanp->data->tileseg = TS_TopLeft;			//PD 23Sep96
			else
				scanp->data->tileseg = TS_TopRight;			//PD 23Sep96
		}
		else
		{
			if (swx-wx==0)
				scanp->data->tileseg = TS_BottomLeft;				//PD 23Sep96
			else
				scanp->data->tileseg = TS_BottomRight;				//PD 23Sep96
		}
		//Add a request for this block on the next frame
		//We can mannage with the lower resolution one 
		//for this frame

		AddBlockRequest(wx,wz,scale);
		return(scanp->data);
	}

	if (scale<=LDS_Half)
	{
		//Can't cope without some data so decompress this block now

		CacheReqBlock	crb;

		crb.next=NULL;
		crb.wx=wx;
		crb.wz=wz;
		scanp=DecompressBlock(&crb,scale);
		return (scanp->data);
	}

	AddBlockRequest(wx,wz,scale);
	dummyimagep->tileseg = TS_Whole;
	return (dummyimagep);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RequestBlock
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
LandMapDescPtr
Land_Stream::RequestBlockNF(SLong wx, SLong wz, SWord iscale)
{
	CacheBlockP		scanp;

	CacheReqBlock	crb;

	LDataScales scale = (LDataScales )iscale;

	//Search cachescale[scale] for a matching block

	if (FindCacheEntry(&cachescale[scale],wx,wz,scanp))
	{
		//Move this block to the head of the discard list

		UpdateDiscardList(scale,scanp);

  		scanp->data->tileseg = TS_Whole;

		return (scanp->data);
	}

	//Unable to find this block in the cache
	//Can't cope without some data so decompress this block now

	crb.next=NULL;
	crb.wx=wx;
	crb.wz=wz;
	scanp=DecompressBlock(&crb,scale);
	scanp->data->tileseg = TS_Whole;
	return (scanp->data);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RequestInitBlock
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void
Land_Stream::RequestInitBlock(SLong wx, SLong wz, SWord iscale)
{
	LDataScales scale = (LDataScales )iscale;

	//Search cachescale[scale] for a matching block

	CacheBlockP scanp;

	if (FindCacheEntry(&cachescale[scale],wx,wz,scanp))
	{
		//Move this block to the head of the discard list

		UpdateDiscardList(scale,scanp);

		return;
	}

	//Unable to find this block in the cache

	//Add a request for this block on the next frame
	//We can mannage with the lower resolution one 
	//for this frame

	AddBlockRequest(wx,wz,scale);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddBlockReqest
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::AddBlockRequest(SLong x, SLong z, LDataScales scale)
{
	CacheReqP newp = GetCacheReqBlock();

	if (newp!=NULL)
	{
		newp->wx = x; newp->wz = z;

		newp->next = cachereq[scale];

		cachereq[scale] = newp;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindGroundHeight
//Author		Paul.   
//Date			Sun 29 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong Land_Stream::FindGroundHeight(COORDS3D& coords)
{
	return Land_Scape.GetGroundLevel(coords);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessRequestsNoLimit
//Author		Paul.   
//Date			Fri 20 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ProcessRequestsNoLimit()
{
	COORDS3D coords;

	LDataScales	scale = LDS_AliasX2;

	//Get first decompression request

	while (scale < LDS_MAX && cachereq[scale]==NULL)
		scale = (LDataScales)(scale+1);

	if (scale==LDS_MAX)	return;	//No data requests - pretty unlikely!

	for (;;)
	{
		CacheReqP	crbp;

		SeekStruc	seekdata;

		crbp = cachereq[scale];

		coords.X = crbp->wx<<XZ_COL_SCALE;
		coords.Z = crbp->wz<<XZ_COL_SCALE;

		//Process a decompression request

		(void)DecompressBlock(crbp, scale);

		requestcount--;

		//Remove this request from the queue

		cachereq[scale] = crbp->next;

		//Check for time left

		//Move to next request

		if (!cachereq[scale])
		{
			while (scale!=LDS_MAX && !cachereq[scale])
				scale = (LDataScales)(scale+1);

			if (scale==LDS_MAX)	break;	//No more requests
		}
	}

	FlushRequests();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessRequests
//Author		Paul.   
//Date			Mon 7 Oct 1996
//
//Description	Modified to allow only 1 file access per frame of 3D
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ProcessRequests()
{
	COORDS3D coords;

	LDataScales	scale = LDS_AliasX2;

	//Get first decompression request

	while (scale < LDS_MAX && cachereq[scale]==NULL)
		scale = (LDataScales)(scale+1);

	if (scale==LDS_MAX)	return;	//No data requests - pretty unlikely!
//TEMP
	UWord	t_done = 0;	//Timer_Code.TestLoopTime();

//TEMP	t_done += MaxDecompressionTime;		//decompression time

	for (;;)
	{
		CacheReqP	crbp;

		SeekStruc	seekdata;

		crbp = cachereq[scale];

		coords.X = crbp->wx<<XZ_COL_SCALE;
		coords.Z = crbp->wz<<XZ_COL_SCALE;

		//Process a decompression request

		(void)DecompressBlock(crbp, scale);

		requestcount--;

		//Remove this request from the queue

		cachereq[scale] = crbp->next;

		//Check for time left

//TEMP		if (t_done<Timer_Code.TestLoopTime())
			break;

		//Move to next request

		if (!cachereq[scale])
		{
			while (scale!=LDS_MAX && !cachereq[scale])
				scale = (LDataScales)(scale+1);

			if (scale==LDS_MAX)	break;	//No more requests
		}
	}

	FlushRequests();

	ThreeDee::PossMoveCycle();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecompressBlock
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Land_Stream::CacheBlockP Land_Stream::DecompressBlock(CacheReqP crbp,LDataScales scale)
{
	CacheBlockP	scanp;

	if (cachecount[scale]<cachemax[scale])
	{
		//Not reached the caches limit yet!
		blockdelete=TRUE;

		scanp = new CacheBlock;

		assert((scanp)&&(" - cache block create failed!"));		//PD 29Aug96

		scanp->data = CreateNewMap(scale); 	//new imagemap of the right size for
											//this scale
		cachecount[scale]++;
		blockdelete=FALSE;
	}
	else
	{
		//The cache is full at this scale so
		//re-use the block at the end of the
		//discard list. This one should be 
		//the oldest

		scanp = FindDiscardableBlock(scale);

		assert ((scanp)&&(" - no discardable blocks!"));

		//Remove this block from the search list

		UnLinkCacheEntry(&cachescale[scale],scanp);
	}

	scanp->wx = crbp->wx;

	scanp->wz = crbp->wz;

	scanp->discarded = 0L;										//PD 30Sep96

	//copy decompressed and scaled data to 'scanp->data'

	GetColourData(scanp,scale);

	//add new block to the search list

	InsertCacheEntry(&cachescale[scale],scanp);

	//add new block to the head of the discard list

	InsertInDiscardList(scale,scanp);

	return (scanp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PartialDecompressBlock
//Author		Paul.   
//Date			Tue 8 Oct 1996
//
//Description	scale is always LDS_Quarter
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::PartialDecompressBlock(CacheReqP crbp)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetColourData
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	Finally we get to the part that actually unpacks the data
//				and stores the result in an imagemap to be drawn next frame.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::GetColourData(CacheBlockP cbp, LDataScales scale)
{
	COORDS3D coords;

	ULong coordmask = ~((0x00000001<<(XZ_COL_SCALE+8))-1);

	coords.X = cbp->wx<<XZ_COL_SCALE; coords.Z = cbp->wz<<XZ_COL_SCALE;

	UByte* cdestptr = GetBigTile(coords);

	UByte* adestptr = cdestptr + ColourDataSize;

	coords.X &= coordmask;	coords.Z &= coordmask;

	//coords holds the coordinates of the decompressed
	//data block and adestptr points to the decompressed
	//altitude data

	//Update altitude data

	UpdateAltitudeData(coords,adestptr);

	coords.X >>= XZ_COL_SCALE; coords.Z >>= XZ_COL_SCALE;

	//now, coords holds the coordinates of the corner 
	//of the decompressed data block, the cacheblock
	//structure holds the coordinates of the corner of
	//the required area of the data within the block
	//and cdestptr points to the decompressed data block

	switch (scale)
	{
		case LDS_AliasX2:
			if (Save_Data.detail_3d[DETAIL3D_ANTIALIAS])
				SampleTile400pc(cbp,coords,cdestptr);
			else
				SampleTile400pcNoAlias(cbp,coords,cdestptr);
			break;
		case LDS_AliasX1:
			if (Save_Data.detail_3d[DETAIL3D_ANTIALIAS])
				SampleTile200pc(cbp,coords,cdestptr);
			else
				SampleTile200pcNoAlias(cbp,coords,cdestptr);
			break;
		case LDS_Normal:
			SampleTile100pc(cbp,coords,cdestptr);
			break;
		case LDS_Half:
			SampleTile50pc(cbp,coords,cdestptr);
			break;
		case LDS_Quarter:
			SampleTile25pc(cbp,coords,cdestptr);
			break;
		case LDS_Eighth:
			SampleTile12pc(cbp,coords,cdestptr);
			break;
		case LDS_Sixteenth:
			SampleTile6pc(cbp,coords,cdestptr);
			break;
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAltitudeDataOnly
//Author		Paul.   
//Date			Tue 8 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::GetAltitudeDataOnly(CacheBlockP cbp, LDataScales scale)
{
//Old_Code PD 19Nov96 	COORDS3D coords;
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	ULong coordmask = ~((0x00000001<<(XZ_COL_SCALE+8))-1);
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	coords.X = cbp->wx<<XZ_COL_SCALE; coords.Z = cbp->wz<<XZ_COL_SCALE;
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	UByte* cdestptr = GetBigAltTile(coords);
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	UByte* adestptr = cdestptr + ColourDataSize;
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	coords.X &= coordmask;	coords.Z &= coordmask;
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	//coords holds the coordinates of the decompressed
//Old_Code PD 19Nov96 	//data block and adestptr points to the decompressed
//Old_Code PD 19Nov96 	//altitude data
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	//Update altitude data
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	UpdateAltitudeData(coords,adestptr);
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	coords.X >>= XZ_COL_SCALE; coords.Z >>= XZ_COL_SCALE;
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	LandMapDescPtr lmdp = cbp->data;
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	UByte* temp = (UByte*)(&lmdp->tilemap);
//Old_Code PD 19Nov96 
//Old_Code PD 19Nov96 	*temp = *cdestptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTile400pc
//Author		Paul.   
//Date			Thu 1 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SampleTile400pc(CacheBlockP cbp, const COORDS3D& coords, UByte* cdestptr)
{
	//cdestp - ptr to 257 x 257 image

	//cbp - ptr to cache block structure containing the coordinates of
	//		the area required

	//coords - coordinates of the decompressed data block

	SLong	startx = cbp->wx - coords.X;

	SLong	startz = DestBytesPerScanLine-1 - (cbp->wz - coords.Z);//PD 25Nov96

	cdestptr += (startz*DestBytesPerScanLine) + startx;

	int	row,column;

	UByte*	sdestp = &((cbp->data)->tilemap.data);				//PD 27Aug96

	UByte*	dest;
	UByte*	src;

	for (	row = 9,
			dest= sdestp,
			src = cdestptr;
			row;
			dest += 96,
			src	 -= DestBytesPerScanLine + 8,
			row--)
		for (	column=8;
				column;
				ASM_HorizAliasX2(src++,dest,ailtbl16p),
				dest+=4,
				column--);

	for (	row = 8,
			dest= sdestp + 64;
			row;
			dest += 96,
			row--)
		for (	column=32;
				column;
				ASM_VertAliasX2(dest++,ailtbl16p),
				column--);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTile400pcNoAlias
//Author		Paul.   
//Date			Thu 1 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SampleTile400pcNoAlias(CacheBlockP cbp, const COORDS3D& coords, UByte* cdestptr)
{
	//cdestp - ptr to 257 x 257 image

	//cbp - ptr to cache block structure containing the coordinates of
	//		the area required

	//coords - coordinates of the decompressed data block

	SLong	startx = cbp->wx - coords.X;

	SLong	startz = DestBytesPerScanLine-1 - (cbp->wz - coords.Z);//PD 25Nov96

	cdestptr += (startz*DestBytesPerScanLine) + startx;

	int	row,column;

	UByte*	sdestp = &((cbp->data)->tilemap.data);				//PD 27Aug96

	UByte*	dest;
	UByte*	src;

	for (	row = 8,
			dest= sdestp,
			src = cdestptr;
			row;
			src	 -= DestBytesPerScanLine + 8,
			row--)
	{
		UByte*	lsrc = src;
		for (	column=8;
				column;
				*dest++ = *src,
				*dest++ = *src,
				*dest++ = *src,
				*dest++ = *src++,
				column--);
		src = lsrc;
		for (	column=8;
				column;
				*dest++ = *src,
				*dest++ = *src,
				*dest++ = *src,
				*dest++ = *src++,
				column--);
		src = lsrc;
		for (	column=8;
				column;
				*dest++ = *src,
				*dest++ = *src,
				*dest++ = *src,
				*dest++ = *src++,
				column--);
		src = lsrc;
		for (	column=8;
				column;
				*dest++ = *src,
				*dest++ = *src,
				*dest++ = *src,
				*dest++ = *src++,
				column--);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTile200pc
//Author		Paul.   
//Date			Thu 1 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SampleTile200pc(CacheBlockP cbp, const COORDS3D& coords, UByte* cdestptr)
{
	//cdestp - ptr to 257 x 257 image

	//cbp - ptr to cache block structure containing the coordinates of
	//		the area required

	//coords - coordinates of the decompressed data block

	SLong	startx = cbp->wx - coords.X;

	SLong	startz = DestBytesPerScanLine-1 - (cbp->wz - coords.Z);//PD 25Nov96

	cdestptr += (startz*DestBytesPerScanLine) + startx;

	int	row,column;

	UByte*	sdestp = &((cbp->data)->tilemap.data);				//PD 27Aug96

	UByte*	dest;
	UByte*	src;

	for (	row = 17,
			dest= sdestp,
			src = cdestptr;
			row;
			dest += 32,
			src	 -= DestBytesPerScanLine + 16,
			row--)
		for (	column=16;
				column;
				ASM_HorizAliasX1(src++,dest,ailtbl16p),
				dest+=2,
				column--);

	for (	row = 16,
			dest= sdestp + 32;
			row;
			dest += 32,
			row--)
		for (	column=32;
				column;
				ASM_VertAliasX1(dest++,ailtbl16p),
				column--);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTile200pcNoAlias
//Author		Paul.   
//Date			Thu 5 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SampleTile200pcNoAlias(CacheBlockP cbp, const COORDS3D& coords, UByte* cdestptr)
{
	//cdestp - ptr to 257 x 257 image

	//cbp - ptr to cache block structure containing the coordinates of
	//		the area required

	//coords - coordinates of the decompressed data block

	SLong	startx = cbp->wx - coords.X;

	SLong	startz = DestBytesPerScanLine-1 - (cbp->wz - coords.Z);//PD 25Nov96

	cdestptr += (startz*DestBytesPerScanLine) + startx;

	int	row,column;

	UByte*	sdestp = &((cbp->data)->tilemap.data);				//PD 27Aug96

	ASMSampleTile200pcNoAlias(cdestptr,sdestp);					//PD 23Sep96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTile100pc
//Author		Paul.   
//Date			Thu 1 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SampleTile100pc(CacheBlockP cbp, const COORDS3D& coords, UByte* cdestptr)
{
	//cdestp - ptr to 257 x 257 image

	//cbp - ptr to cache block structure containing the coordinates of
	//		the area required

	//coords - coordinates of the decompressed data block

	SLong	startx = cbp->wx - coords.X;

	SLong	startz = DestBytesPerScanLine-1 - (cbp->wz - coords.Z);//PD 25Nov96

	cdestptr += (startz*DestBytesPerScanLine) + startx;

	int	row;

	UByte*	sdestp = &((cbp->data)->tilemap.data);				//PD 27Aug96

	for (row=32;row;row--)
	{
		ASM_Blat(cdestptr,sdestp,32);
		cdestptr -= DestBytesPerScanLine;
		sdestp += 32;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTile50pc
//Author		Paul.   
//Date			Thu 1 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SampleTile50pc(CacheBlockP cbp, const COORDS3D& coords, UByte* cdestptr)
{
	//cdestp - ptr to 257 x 257 image

	//cbp - ptr to cache block structure containing the coordinates of
	//		the area required

	//coords - coordinates of the decompressed data block

	SLong	startx = cbp->wx - coords.X;

	SLong	startz = DestBytesPerScanLine-1 - (cbp->wz - coords.Z);//PD 25Nov96

	cdestptr += (startz*DestBytesPerScanLine) + startx;

	int	row,column;

	UByte*	lcdestp;

	UByte*	sdestp = &((cbp->data)->tilemap.data);				//PD 27Aug96

	for (	row=32;
			row;
			cdestptr -= DestBytesPerScanLine*2,
			row--)
		for (	column=32,
				lcdestp = cdestptr;
				column;
				*sdestp++ = *lcdestp,
				lcdestp += 2,
				column--);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTile25pc
//Author		Paul.   
//Date			Thu 1 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SampleTile25pc(CacheBlockP cbp, const COORDS3D& coords, UByte* cdestptr)
{
	//cdestp - ptr to 257 x 257 image

	//cbp - ptr to cache block structure containing the coordinates of
	//		the area required

	//coords - coordinates of the decompressed data block

	SLong	startx = cbp->wx - coords.X;

	SLong	startz = DestBytesPerScanLine-1 - (cbp->wz - coords.Z);//PD 25Nov96

	cdestptr += (startz*DestBytesPerScanLine) + startx;

	int	row,column;

	UByte*	lcdestp;

	UByte*	sdestp = &((cbp->data)->tilemap.data);				//PD 27Aug96

	for (	row=32;
			row;
			cdestptr -= DestBytesPerScanLine*4,
			row--)
		for (	column=32,
				lcdestp = cdestptr;
				column;
				*sdestp++ = *lcdestp,
				lcdestp += 4,
				column--);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTile12pc
//Author		Paul.   
//Date			Thu 1 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SampleTile12pc(CacheBlockP cbp, const COORDS3D& coords, UByte* cdestptr)
{
	//cdestp - ptr to 257 x 257 image

	//cbp - ptr to cache block structure containing the coordinates of
	//		the area required

	//coords - coordinates of the decompressed data block

	SLong	startx = cbp->wx - coords.X;

	SLong	startz = DestBytesPerScanLine-1 - (cbp->wz - coords.Z);//PD 25Nov96

	cdestptr += (startz*DestBytesPerScanLine) + startx;

	int	row,column;

	UByte*	lcdestp;

	UByte*	sdestp = &((cbp->data)->tilemap.data);

	for (	row=32;
			row;
			cdestptr -= DestBytesPerScanLine*8,
			row--)
		for (	column=32,
				lcdestp = cdestptr;
				column;
				*sdestp++ = *lcdestp,
				lcdestp += 8,
				column--);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTile6pc
//Author		Paul.   
//Date			Tue 15 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SampleTile6pc(CacheBlockP cbp, const COORDS3D& coords, UByte* cdestptr)
{
	//cdestp - ptr to 257 x 257 image

	//cbp - ptr to cache block structure containing the coordinates of
	//		the area required

	//coords - coordinates of the decompressed data block

	SLong	startx = cbp->wx - coords.X;

	SLong	startz = DestBytesPerScanLine-1 - (cbp->wz - coords.Z);//PD 25Nov96

	ULong	start_adr,end_adr;

	start_adr = (ULong)cdestptr;
	end_adr = start_adr+(257*257)-1;

	cdestptr += (startz*DestBytesPerScanLine) + startx;

	int	row,column;

	UByte*	lcdestp;

	UByte*	sdestp = &((cbp->data)->tilemap.data);

	for (	row=32;
			row;
			cdestptr -= DestBytesPerScanLine*16,
			row--)
	{
		for (	column=32,
				lcdestp = cdestptr;
				column;
				column--)
		{
			if (start_adr>(ULong)lcdestp || end_adr<(ULong)lcdestp)
				*sdestp++=(UByte)254;
			else
				*sdestp++ = *lcdestp;
			lcdestp += 16;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillTile
//Author		Paul.   
//Date			Tue 20 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::FillTile(Colour col, UByte* destp, SWord wh )
{
	int	row,
		column;

	for (	row=wh;
			row;
			row--)
		for (	column=wh;
				column;
				*destp++ = (UByte )col,
				column--);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindCacheEntry
//Author		Paul.   
//Date			Wed 21 Aug 1996
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Land_Stream::FindCacheEntry(	CacheBlockP *listheadp,
									SLong wx,
									SLong wz,
									CacheBlockP& retval)
{
	CacheBlockP scanp;

	scanp = *listheadp;

	if (scanp==NULL)
		return (FALSE);

	//Scan for a matching block - by WZ first

	for (;;)
	{
		if (scanp->wz==wz)
			break;

		scanp=scanp->northp;

		if (scanp==NULL)
			return (FALSE);
	}

	//then, search by WX

	for (;;)
	{
		if (scanp->wx==wx)
			break;

		scanp=scanp->eastp;

		if (scanp==NULL)
			return (FALSE);
	}

	retval = scanp;

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindCacheEntry
//Author		Paul.   
//Date			Wed 21 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Land_Stream::FindCacheEntry(	BigCacheBlockP *listheadp,
									SLong wx,
									SLong wz,
									BigCacheBlockP& retval)
{
	BigCacheBlockP scanp = *listheadp;

	if (scanp==NULL)
		return (FALSE);

	//Scan for a matching block - by WZ first

	for (;;)
	{
		if (scanp->wz==wz)
			break;

		scanp=scanp->northp;

		if (scanp==NULL)
			return (FALSE);
	}

	//then, search by WX

	for (;;)
	{
		if (scanp->wx==wx)
			break;

		scanp=scanp->eastp;

		if (scanp==NULL)
			return (FALSE);
	}

	retval = scanp;

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InsertCacheEntry
//Author		Paul.   
//Date			Wed 21 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::InsertCacheEntry(CacheBlockP *listheadp, CacheBlockP newblockp)
{
	CacheBlockP	scanp = *listheadp;

	if (scanp==NULL)
	{
		*listheadp = newblockp;
		newblockp->northp =
			newblockp->eastp =
			newblockp->parent = NULL;
	}
	else
	{
		//Search in WZ first

		CacheBlockP	prevp = NULL;

		for (;;)
		{
			if (scanp->wz>=newblockp->wz)
				break;

			prevp = scanp;

			scanp = scanp->northp;

			if (scanp==NULL)
				break;
		}

		if (scanp==NULL)
		{
			prevp->northp = newblockp;

			newblockp->parent = prevp;

			newblockp->northp =
				newblockp->eastp = NULL;
		}
		else
		{
			if (scanp->wz!=newblockp->wz)
			{
				if (prevp==NULL)
				{
					*listheadp = newblockp;

					newblockp->northp = scanp;

					newblockp->eastp =
						newblockp->parent = NULL;

					scanp->parent = newblockp;
				}
				else
				{
					prevp->northp = newblockp;

					newblockp->parent = prevp;

					newblockp->eastp = NULL;

					newblockp->northp = scanp;

					scanp->parent = newblockp;
				}
			}
			else
			{
				//Search in WX next

				prevp = NULL;

				for (;;)
				{
					if (scanp->wx>=newblockp->wx)
						break;

					prevp = scanp;

					scanp = scanp->eastp;

					if (scanp==NULL)
						break;
				}

				if (scanp==NULL)
				{
					prevp->eastp = newblockp;

					newblockp->parent = prevp;

					newblockp->northp =
						newblockp->eastp = NULL;
				}
				else
				{
					assert((scanp->wx!=newblockp->wx)&&(" - entry is already cached!"));

					if (prevp==NULL)
					{
						prevp = scanp->parent;

						if (prevp==NULL)
						{
							*listheadp = newblockp;

							newblockp->parent = NULL;

							newblockp->eastp = scanp;

							newblockp->northp = scanp->northp;

							scanp->parent = newblockp;

							scanp->northp = NULL;

							if (newblockp->northp!=NULL)
								newblockp->northp->parent = newblockp;
						}
						else
						{
							prevp->northp = newblockp;

							newblockp->parent = prevp;

							newblockp->northp = scanp->northp;

							newblockp->eastp = scanp;

							scanp->parent = newblockp;

							scanp->northp = NULL;

							if (newblockp->northp!=NULL)
								newblockp->northp->parent = newblockp;
						}
					}
					else
					{
						prevp->eastp = newblockp;

						newblockp->parent = prevp;

						newblockp->northp = NULL;

						newblockp->eastp = scanp;

						scanp->parent = newblockp;
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InsertCacheEntry
//Author		Paul.   
//Date			Wed 21 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::InsertCacheEntry(BigCacheBlockP *listheadp, BigCacheBlockP newblockp)
{
	BigCacheBlockP	scanp = *listheadp;

	if (scanp==NULL)
	{
		*listheadp = newblockp;
		newblockp->northp =
			newblockp->eastp =
			newblockp->parent = NULL;
	}
	else
	{
		//Search in WZ first

		BigCacheBlockP	prevp = NULL;

		for (;;)
		{
			if (scanp->wz>=newblockp->wz)
				break;

			prevp = scanp;

			scanp = scanp->northp;

			if (scanp==NULL)
				break;
		}

		if (scanp==NULL)
		{
			prevp->northp = newblockp;

			newblockp->parent = prevp;

			newblockp->northp =
				newblockp->eastp = NULL;
		}
		else
		{
			if (scanp->wz!=newblockp->wz)
			{
				if (prevp==NULL)
				{
					*listheadp = newblockp;

					newblockp->northp = scanp;

					newblockp->eastp =
						newblockp->parent = NULL;

					scanp->parent = newblockp;
				}
				else
				{
					prevp->northp = newblockp;

					newblockp->parent = prevp;

					newblockp->eastp = NULL;

					newblockp->northp = scanp;

					scanp->parent = newblockp;
				}
			}
			else
			{
				//Search in WX next

				prevp = NULL;

				for (;;)
				{
					if (scanp->wx>=newblockp->wx)
						break;

					prevp = scanp;

					scanp = scanp->eastp;

					if (scanp==NULL)
						break;
				}

				if (scanp==NULL)
				{
					prevp->eastp = newblockp;

					newblockp->parent = prevp;

					newblockp->northp =
						newblockp->eastp = NULL;
				}
				else
				{
					assert((scanp->wx!=newblockp->wx)&&(" - entry is already cached!"));

					if (prevp==NULL)
					{
						prevp = scanp->parent;

						if (prevp==NULL)
						{
							*listheadp = newblockp;

							newblockp->parent = NULL;

							newblockp->eastp = scanp;

							newblockp->northp = scanp->northp;

							scanp->parent = newblockp;

							scanp->northp = NULL;

							if (newblockp->northp!=NULL)
								newblockp->northp->parent = newblockp;
						}
						else
						{
							prevp->northp = newblockp;

							newblockp->parent = prevp;

							newblockp->northp = scanp->northp;

							newblockp->eastp = scanp;

							scanp->parent = newblockp;

							scanp->northp = NULL;

							if (newblockp->northp!=NULL)
								newblockp->northp->parent = newblockp;
						}
					}
					else
					{
						prevp->eastp = newblockp;

						newblockp->parent = prevp;

						newblockp->northp = NULL;

						newblockp->eastp = scanp;

						scanp->parent = newblockp;
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLinkCacheEntry
//Author		Paul.   
//Date			Thu 22 Aug 1996
//
//Description	Removes a data block from the cache search list
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::UnLinkCacheEntry(CacheBlockP* listheadp,CacheBlockP blockp)
{
	assert ((*listheadp)&&(" - cache empty!"));

	//Test for block already discarded

	if (blockp->discarded==-1L)
		return;

	CacheBlockP	prevblkp = blockp->parent;

	if (prevblkp == NULL)
	{
		//Block is at the head of the search tree

		//If the block has an eastern element, make it
		//the new head of the tree

		if (blockp->eastp!=NULL)
		{
			CacheBlockP	tempp = blockp->eastp;

			*listheadp = tempp;

			tempp->parent = prevblkp;

			tempp->northp = blockp->northp;

			if (tempp->northp!=NULL) tempp->northp->parent = tempp;
		}
		else
		{
			//Otherwise, if it has a northern element
			//then make that the new head of the tree

			if (blockp->northp!=NULL)
			{
				CacheBlockP tempp = blockp->northp;

				*listheadp = tempp;

				tempp->parent = prevblkp;

				if (tempp->northp!=NULL) tempp->northp->parent = tempp;
			}
			else
			{
				//If this entry was the only one in the cache
				//then just NULL the head of the search tree

				*listheadp = NULL;
			}
		}
	}
	else
	{
		if (prevblkp->eastp == blockp)
		{
			//Block is on a side chain - just shuffle
			//all elements in the chain to the west

			CacheBlockP	tempp = blockp->eastp;

			prevblkp->eastp = tempp;

			if (tempp!=NULL) tempp->parent = prevblkp;
		}
		else
		{
			assert ((prevblkp->eastp!=blockp)&&(" - block incorrectly linked in tree"));

			//Block is on edge chain

			//If the block has an eastern element - shuffle
			//side chain to the west

			if (blockp->eastp!=NULL)
			{
				CacheBlockP	tempp = blockp->eastp;

				prevblkp->northp = tempp;

				tempp->parent = prevblkp;

				tempp->northp = blockp->northp;

				if (tempp->northp!=NULL) tempp->northp->parent = tempp;
			}
			else
			{
				if (blockp->northp!=NULL)
				{
					CacheBlockP	tempp = blockp->northp;

					prevblkp->northp = tempp;

					tempp->parent = prevblkp;
				}
				else
				{
					prevblkp->northp = NULL;
				}
			}	
		}
	}
	blockp->discarded = -1L;									//PD 28Aug96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLinkCacheEntry
//Author		Paul.   
//Date			Thu 22 Aug 1996
//
//Description	Removes a data block from the cache search list
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::UnLinkCacheEntry(BigCacheBlockP* listheadp,BigCacheBlockP blockp)
{
	assert ((*listheadp)&&(" - cache empty!"));

	//Test for block already discarded

	BigCacheBlockP	prevblkp = blockp->parent;

	if (prevblkp == NULL)
	{
		//Block is at the head of the search tree

		//If the block has an eastern element, make it
		//the new head of the tree

		if (blockp->eastp!=NULL)
		{
			BigCacheBlockP	tempp = blockp->eastp;

			*listheadp = tempp;

			tempp->parent = prevblkp;

			tempp->northp = blockp->northp;

			if (tempp->northp!=NULL) tempp->northp->parent = tempp;
		}
		else
		{
			//Otherwise, if it has a northern element
			//then make that the new head of the tree

			if (blockp->northp!=NULL)
			{
				BigCacheBlockP tempp = blockp->northp;

				*listheadp = tempp;

				tempp->parent = prevblkp;

				if (tempp->northp!=NULL) tempp->northp->parent = tempp;
			}
			else
			{
				//If this entry was the only one in the cache
				//then just NULL the head of the search tree

				*listheadp = NULL;
			}
		}
	}
	else
	{
		if (prevblkp->eastp == blockp)
		{
			//Block is on a side chain - just shuffle
			//all elements in the chain to the west

			BigCacheBlockP	tempp = blockp->eastp;

			prevblkp->eastp = tempp;

			if (tempp!=NULL) tempp->parent = prevblkp;
		}
		else
		{
			assert ((prevblkp->eastp!=blockp)&&(" - block incorrectly linked in tree"));

			//Block is on edge chain

			//If the block has an eastern element - shuffle
			//side chain to the west

			if (blockp->eastp!=NULL)
			{
				BigCacheBlockP	tempp = blockp->eastp;

				prevblkp->northp = tempp;

				tempp->parent = prevblkp;

				tempp->northp = blockp->northp;

				if (tempp->northp!=NULL) tempp->northp->parent = tempp;
			}
			else
			{
				if (blockp->northp!=NULL)
				{
					BigCacheBlockP	tempp = blockp->northp;

					prevblkp->northp = tempp;

					tempp->parent = prevblkp;
				}
				else
				{
					prevblkp->northp = NULL;
				}
			}	
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBigTile
//Author		Paul.   
//Date			Fri 20 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte* Land_Stream::GetBigTile(COORDS3D& coords)
{
	UByte*			retval = NULL;
	SLong			x = coords.X & 0x0FFFE0000,
					z = coords.Z & 0x0FFFE0000;

	BigCacheBlockP	scanp;

	if (FindCacheEntry(&bigcachep[0],x,z,scanp))
	{
		//move this block to the head of the discard list
		UpdateDiscardList(bigdumpp,scanp);
	}
	else
	{
		retval = GetBigTileFile(coords);

		//Allocate a cache block record for this block

		if (bigcachecount<bigcachemax)
		{
			//not reached the caches limit yet

			scanp = new BigCacheBlock;

			scanp->data = NULL;

			assert((scanp)&&(" - bigcache block create failed!"));

			bigcachecount++;
		}
		else
		{
			//the cache is full so re-use
			//the block at the end of the 
			//discard list. This should be
			//the oldest block in the cache

			scanp = FindDiscardableBlock(bigdumpp);

			assert ((scanp)&&(" - no discardable big blocks!"));

			//remove this block from the search list

			UnLinkCacheEntry(&bigcachep[0],scanp);
		}

		DecompressTile(retval,scanp->data);

		//add the newly decompressed data to the cache

		scanp->wx = x; scanp->wz = z;

		//add the new block to the search list

		InsertCacheEntry(&bigcachep[0],scanp);

		//add the new block to the head of the discard list

		InsertInDiscardList(&bigdumpp[0],scanp);
	}

	return (scanp->data);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBigAltTile
//Author		Paul.   
//Date			Tue 8 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte* Land_Stream::GetBigAltTile(COORDS3D& coords)
{
	return NULL;

//TempCode PD 9Dec97 	UByte*			retval;
//TempCode PD 9Dec97 	SLong			x = coords.X & 0x0FFFE0000,
//TempCode PD 9Dec97 					z = coords.Z & 0x0FFFE0000;
//TempCode PD 9Dec97 	SLong			length,offset;
//TempCode PD 9Dec97 	FileNum			myfile;
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	MovingItem		tempitem;
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	tempitem.World.X = x;
//TempCode PD 9Dec97 	tempitem.World.Z = z;
//TempCode PD 9Dec97 	tempitem.World.Y = 0;
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	SetArea(&tempitem);
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	myfile = AreaFiles[0];
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	offset = GetFileOffset(WW_north,tempitem.World.X,tempitem.World.Z);
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	length = 0x1000;
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	LSFileBlock	fb(myfile,length,offset,FALSE);
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	retval = (UByte*)fb.GetData();
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	if (retval!=NULL)
//TempCode PD 9Dec97 	{
//TempCode PD 9Dec97 		PartialDecompress(retval);
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 		UpdateAltitudeData(coords,retval+ColourDataSize);
//TempCode PD 9Dec97 	}
//TempCode PD 9Dec97 
//TempCode PD 9Dec97 	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateAltitudeData
//Author		Paul.   
//Date			Tue 24 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::UpdateAltitudeData(COORDS3D& coords,UByte* altdatap)
{
	const 	SLong	world_coord_step = 0x00000001<<XZ_ALT_SCALE;
	const 	SLong	world_coord_mask = ~(world_coord_step-1);

	SLong	ground_x_mask,
			ground_z_mask,
			ground_z_shift;

	SLong	wx,wz;

	int		row,column;

	UByte*	pdest;

	ImageMapDescPtr adestp;

	if (!Land_Scape.landdata)
		Land_Scape.LoadLandData();	//Not really a load!

	adestp = Land_Scape.landdata;

	wx = coords.X & world_coord_mask;
	wz = coords.Z & world_coord_mask;

	ground_z_shift= adestp->width;
	ground_x_mask = (0x00000001<<ground_z_shift)-1;
	ground_z_mask = (0x00000001<<adestp->height)-1;

	wx = (wx>>XZ_ALT_SCALE)&ground_x_mask;
	wz = ((WORLD_BIG_WZ-wz)>>XZ_ALT_SCALE)&ground_z_mask;

	wx &= 0x0FFFFFE0;
	wz &= 0x0FFFFFE0;

	pdest = &(adestp->data) + wx + (wz<<ground_z_shift);

	//altdatap = ptr to source 35x35 decompressed altitude data
	//pdest	   = ptr to destination buffer to store new alt data

	for (int roow=1;roow<=32;roow++)
		for (int coolumn=1;coolumn<=32;coolumn++)
			 *(pdest + ((roow-1)<<ground_z_shift) + (coolumn-1)) = *(altdatap + (35*roow) + coolumn);

}

SLong	adc=0;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OutputAltDataAsH8
//Author		Paul.   
//Date			Thu 3 Oct 1996
//
//Description	Dumps the altitude data for the current viewers position
//				to disk as an .H8 file
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::OutputAltDataAsH8()
{
	COORDS3D coords;

	SLong	wwx,wwz,wwalt;

	coords.X = 24411625;
	coords.Z = 27119200;

	UByte* cdestptr = GetBigTile(coords);

	UByte* adestptr = cdestptr + ColourDataSize;

	FILE* ofile;

	UpdateAltitudeData(coords,adestptr);

	wwx = coords.X;
	wwz = WORLD_BIG_WZ - coords.Z;

	Land_Scape.GetLandscapeData(wwx,wwz,wwalt);

	wwalt = _Collide.AccurateGroundAltitude(coords);

	ofile = fopen("\\fly\\src\\low.h8","wb");

	fputc(0x55,ofile);

	for (int row=1;row<=32;row++)
		for (int column=1;column<=32;column++)
			 fputc(*(adestptr + (AltBytesPerScanLine*row) + column),ofile);

	fclose(ofile);

	coords.X = 24409575;
	coords.Z = 27132707;

	cdestptr = GetBigTile(coords);

	adestptr = cdestptr + ColourDataSize;

	UpdateAltitudeData(coords,adestptr);

	wwx = coords.X;
	wwz = WORLD_BIG_WZ - coords.Z;

	Land_Scape.GetLandscapeData(wwx,wwz,wwalt);

	wwalt = _Collide.AccurateGroundAltitude(coords);

	ofile = fopen("\\fly\\src\\high.h8","wb");

	fputc(0x55,ofile);

	for (row=1;row<=32;row++)
		for (int column=1;column<=32;column++)
			 fputc(*(adestptr + (AltBytesPerScanLine*row) + column),ofile);

	fclose(ofile);

	_Error.EmitSysErr("hsjahgs");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTileCoords
//Author		Paul.   
//Date			Sun 29 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::GetTileCoords(COORDS3D& coords,
								vector& P0,
								vector& P1,
								vector& P2,
								vector& P3)
{
	UByte* altdatap;

	COORDS3D xcoords,zcoords;

	zcoords=coords;

	zcoords.X -= 0x20000;
	zcoords.Z -= 0x20000;

	for (int zcount=0;zcount<3;zcount++)
	{
		xcoords=zcoords;

		zcoords.Z += 0x20000;

		for (int xcount=0;xcount<3;xcount++)
		{
			UByte* tdatap;

			tdatap=GetBigAltTile(xcoords);
			xcoords.X += 0x20000;

			if (xcount==1 && zcount==1)
				altdatap=tdatap;
		}
	}

//Old_Code PD 18Dec96 	altdatap = GetBigAltTile(coords);							//PD 11Oct96

	SLong	world_coord_step = 0x00000001<<XZ_ALT_SCALE;
	SLong	world_coord_mask = ~(world_coord_step-1);

	if (altdatap==NULL)
	{
		P0.b = P1.b = P2.b = P3.b = 0;
	}
	else
	{
		altdatap += ColourDataSize;

		SLong	x = coords.X & 0x00001ffff,
				z = coords.Z & 0x00001ffff;

		x >>= XZ_ALT_SCALE; z >>= XZ_ALT_SCALE;

		x++; z++;

		altdatap += (z * AltBytesPerScanLine) + x;

		P0.b = *altdatap << Y_RES_SCALE;
		P1.b = *(altdatap + AltBytesPerScanLine) << Y_RES_SCALE;
		P2.b = *(altdatap + AltBytesPerScanLine + 1) << Y_RES_SCALE;
		P3.b = *(altdatap + 1) << Y_RES_SCALE;
	}

	P0.a = (coords.X & world_coord_mask);
	P0.c = (coords.Z & world_coord_mask);

	P1.a = (coords.X & world_coord_mask);
	P1.c = (coords.Z & world_coord_mask) + world_coord_step;

	P2.a = (coords.X & world_coord_mask) + world_coord_step;
	P2.c = (coords.Z & world_coord_mask) + world_coord_step;

	P3.a = (coords.X & world_coord_mask) + world_coord_step;
	P3.c = (coords.Z & world_coord_mask);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBigTileFile
//Author		Paul.   
//Date			Sat 9 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte* Land_Stream::GetBigTileFile(COORDS3D& coords)
{
	UByte*		retval = NULL;

	COORDS3D	lcoords = coords;
	COORDS3D	bcoords = bufferbase;

	lcoords.X &= 0xFFFE0000;

	lcoords.Z &= 0xFFFE0000;

	SLong	xindex = (lcoords.X - bcoords.X)/0x20000;

	SLong	zindex = (bcoords.Z - lcoords.Z)/0x20000;

	if (xindex<0 || xindex>=BIG_CACHE_SIZE)	return(retval);

	if (zindex<0 || zindex>=BIG_CACHE_SIZE)	return(retval);

	retval = bigareacahe[xindex + (BIG_CACHE_SIZE*zindex)]->data.data;

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiskAccessRequired
//Author		Paul.   
//Date			Mon 7 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Land_Stream::DiskAccessRequired( COORDS3D&	coords)			//PD 20Aug97
{
	if (GetBigTileFile(coords)==NULL)
		return (TRUE);

	return (FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLandMapPtr
//Author		Paul.   
//Date			Mon 30 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ImageMapDescPtr	Land_Stream::GetLandMapPtr(LandMapNum lmn)
{
	LandMapNum	lmf;

	lmf = lmn;

	lmn = (LandMapNum)(lmn & 0xFF);

	if (!(*landmapfield)[lmn])
	{
		*landmapfield |= lmn;
		FileNum	f = (FileNum)(DIR_LANDMAPS+lmf);
		landmaps[lmn] = new fileblock(f);
		assert((landmaps[lmn])&&(" - land map load failed!"));
	}
	return ((ImageMapDescPtr )getdata(landmaps[lmn]));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CDBlockIndexNumber
//Author		Paul.   
//Date			Wed 2 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong Land_Stream::CDBlockIndexNumber(COORDS3D& coords)
{
	SLong	retval;
	ULong	seekpos;
	ULong	temp1,
			temp2;
	temp1 = (ULong )(coords.X - 0);
	temp2 = temp1 & 0x00700000;	// X sub-sector number
	temp1 &= 0x00000E0000;		// X 4K block number
	seekpos = (temp2>>2) + (temp1>>5);
	temp1 = (ULong )(coords.Z - 0);
	temp2 = temp1 & 0x00700000;	// Z sub-sector number
	temp1 &= 0x00000E0000;		// Z 4K block number
	seekpos |= ((temp2<<1) + (temp1>>2));
	temp1 = (ULong )(coords.X - 0);
	temp2 = (ULong )(coords.Z - 0);
	temp1 &= (0x07<<23);
	temp2 &= (0x07<<23);
	temp1<<=1;
	temp2<<=4;
	seekpos |= (temp1 + temp2);
	retval = (SLong )seekpos;
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CDBlockWorldCoords
//Author		Paul.   
//Date			Fri 25 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::CDBlockWorldCoords(SLong seekpos,COORDS3D& coords)
{
	coords.X	=	(seekpos & 0xF) +
					(((seekpos>>8)&0xF) << 3) +
					(((seekpos>>16)&0xF) << 6);

	coords.Z	=	((seekpos>>4) & 0xF) +
					(((seekpos>>12) & 0xF) << 3) +
					(((seekpos>>20) & 0xF) << 6);

	coords.X *= 4096;
	coords.Z *= 4096;
}
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FakeTile
//Author		Paul.   
//Date			Fri 4 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::FakeTile(Colour clr,UByte*& dest)
{
	if (dest==NULL)
		dest = new UByte[ColourDataSize+AltDataSize];

	UByte* destp = dest;

	for (int j = ColourDataSize;j;j--)
	{
		*destp++ = (UByte )clr;
	}
	for (j = AltDataSize;j;j--)
	{
		*destp++ = (UByte )0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddSeekRequest
//Author		Paul.   
//Date			Thu 31 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::AddSeekRequest(SeekStruc& newseek)
{
	{///////DEUG CODE////////

//DeadCode PD 04Dec96 		if (newseek.seekpos>0x30ff000)
//DeadCode PD 04Dec96 			_Error.EmitSysErr("Request for block past end of file");

		if (newseek.destdata==NULL)
			_Error.EmitSysErr("NULL destination for data request");


	}///////DEUG CODE////////


	if (masterseeklist==NULL)
	{
		SeekStrucP	newinsp = new SeekStruc;

		*newinsp = newseek;

		masterseeklist=newinsp;
	}
	else
	{
		//check that this tile isn't already in the
		//request list

		SeekStrucP	prevp=NULL,
					scanp=masterseeklist;

		while (scanp!=NULL)
		{
			if (scanp->filenum==newseek.filenum &&
				scanp->seekpos==newseek.seekpos)
				return;								//Don't insert

			prevp=scanp;
			scanp=scanp->next;
		}

		SeekStrucP	newinsp = new SeekStruc;

		*newinsp = newseek;

		prevp->next=newinsp;	//Insert
	}

}

int	loadtime=0;

int	loadflag=0;

int	pingcounter=0;
int	pingtimer=0;

int	loadstream[5]={	BIG_EDGE_SIZE,
					(BIG_CACHE_SIZE/3),
					(BIG_CACHE_SIZE/3),
					(BIG_CACHE_SIZE/3),
					BIG_EDGE_SIZE};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSeekRequests
//Author		Paul.   
//Date			Thu 31 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode DAW 14Dec96 static char	fnum=0;
void Land_Stream::ProcessSeekRequests2()
{
	loadtime++;

 	if (loadtime<1)	return;

	loadtime=0;

	//perform loads in sequence 5,7,7,7,5 blocks

	int requestcount = loadstream[loadflag];

	loadflag = (loadflag+1) % 5;

	SeekStrucP		currreqp;
	LSFileBlockPtr	reqfilep;									//PD 18Nov96

	ULong	*srcp,*dstp;

	currreqp = masterseeklist;

	reqfilep = new LSFileBlock(currreqp->filenum,4096,currreqp->seekpos,TRUE);

	srcp = (ULong*)reqfilep->GetData();

	if (srcp==NULL)
	{
		delete (reqfilep);
		return;
	}

	dstp = (ULong*)currreqp->destdata;

	for (int loop2=0;loop2<1024;*dstp++=*srcp++,loop2++);

	delete (reqfilep);

	masterseeklist = currreqp->next;

	delete (currreqp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSeekRequests
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ProcessSeekRequests()
{
//TEMP	MovingItem* fselitemp = (MovingItem*)View_Point;			//PD 18Nov96
	MovingItem* fselitemp = *Manual_Pilot.ControlledAC2;

	if (Timer_Code.accel)	return;								//RDH 13Nov96


	//Don't add any new requests till we've got the
	//last lot loaded

	if (masterseeklist!=NULL)
	{
		pingtimer=0;											//RDH 17Dec96
		pingcounter=0;											//RDH 17Dec96
		ProcessSeekRequests2();
		return;
	}

	SLong		xindex,
				zindex;

	COORDS3D	lcoords;
	COORDS3D	bcoords;

	lcoords = fselitemp->World;
	bcoords = bufferbase;

	//if the item is less than 6 blocks away
	//from the edge of the 21x21 buffer then don't
	//do anything

	lcoords.X &= 0xFFFE0000;

	lcoords.Z &= 0xFFFE0000;

	xindex = (lcoords.X - bcoords.X)/0x20000;

	zindex = (bcoords.Z - lcoords.Z)/0x20000;

	if (xindex>5 && xindex<15)
		if (zindex>5 && zindex<15)
		{
//DeadCode DAW 06Sep97 			//Send a CD seek reqest every 10 seconds
//DeadCode DAW 06Sep97 			//just to stop the CD ROM drive from stopping
//DeadCode DAW 06Sep97 
//DeadCode DAW 06Sep97 			pingtimer++;
//DeadCode DAW 06Sep97 
//DeadCode DAW 06Sep97 			if (pingtimer>150)
//DeadCode DAW 06Sep97 			{
//DeadCode DAW 06Sep97 				pingtimer=0;
//DeadCode DAW 06Sep97 
//DeadCode DAW 06Sep97 				if (pingcounter<(BIG_FILE_SIZE*4096/DOSFILE_SEEKSTEP))//PD 14Jun97
//DeadCode DAW 06Sep97 				{
//DeadCode DAW 06Sep97 					pingcounter++;
//DeadCode DAW 06Sep97 					FILEMAN.pingCD();
//DeadCode DAW 06Sep97 				}
//DeadCode DAW 06Sep97 			}
			FILEMAN.pingCD();	//let the ping code do the counting!
			return;
		}

	//Gets direction based on the nearest boundary now

	WhichWay whichway = GetDirectionFlags2(fselitemp);

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
			NowGoingNorth(fselitemp);
			break;
		case WW_east:
			NowGoingEast(fselitemp);
			break;
		case WW_south:
			NowGoingSouth(fselitemp);
			break;
		case WW_west:
			NowGoingWest(fselitemp);
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RecenterBuffer
//Author		Paul.   
//Date			Thu 21 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::RecenterBuffer(SLong oldx,SLong oldz,SLong newx,SLong newz)
{
	SLong 	newxindex,
			newzindex;

	newxindex=(newx-oldx)/0x20000;
	newzindex=(newz-oldz)/0x20000;

	if (newxindex>0)
		while (newxindex--)	{ScrollWest();}
	else if (newxindex<0)
		while (newxindex++)	{ScrollEast();}

	if (newzindex>0)
		while (newzindex--)	{ScrollSouth();}
	else if (newzindex<0)
		while (newzindex++)	{ScrollNorth();}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StillGoingNorth
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::StillGoingNorth()
{
//TempCode PD 14Nov97 	int startfileoffset = GetFileOffset(currentdirection,bufferbase.X,bufferbase.Z);

	bufferbase.Z += 0x20000;

	//Shuffle all the data south by 1 band

//TempCode PD 14Nov97 	ScrollSouth();
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollEdge(rcbuffer0);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollEdge(rcbuffer1);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//Add request for a new strip of data to be loaded
//TempCode PD 14Nov97 	//requests need to be added in reverse order
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	startfileoffset += (BIG_FILE_SIZE-BIG_CACHE_SIZE-BIG_EDGE_SIZE+1) * 4096;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	SeekStruc	newsp;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//western edge band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	newsp.filenum = currentfilenum;
//TempCode PD 14Nov97 	newsp.seekpos = startfileoffset;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	for (int counter=0;counter<BIG_EDGE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		newsp.destdata= rcbuffer1[counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//central area
//TempCode PD 14Nov97 	
//TempCode PD 14Nov97 	for (counter=0;counter<BIG_CACHE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		bigareacahe[BIG_CACHE_SIZE-1-counter]->fileblk=newsp.seekpos/4096;//PD 21Nov96
//TempCode PD 14Nov97 		newsp.destdata= bigareacahe[BIG_CACHE_SIZE-1-counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//eastern edge band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	for (counter=0;counter<BIG_EDGE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		newsp.destdata= rcbuffer0[counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StillGoingEast
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::StillGoingEast()
{
//TempCode PD 14Nov97 	int startfileoffset = GetFileOffset(currentdirection,bufferbase.X,bufferbase.Z);

	bufferbase.X += 0x20000;

//TempCode PD 14Nov97 	//Shuffle all the data west by 1 band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollWest();
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollEdge(rcbuffer0);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollEdge(rcbuffer1);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//Add request for a new strip of data to be loaded
//TempCode PD 14Nov97 	//requests need to be added in reverse order
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	int	deltaoffset = ((BIG_CACHE_SIZE-1) * BIG_FILE_SIZE) +
//TempCode PD 14Nov97 						(BIG_FILE_SIZE - (BIG_CACHE_SIZE-1) - BIG_EDGE_SIZE);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	startfileoffset += deltaoffset*4096;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	SeekStruc	newsp;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//edge band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	newsp.filenum = currentfilenum;
//TempCode PD 14Nov97 	newsp.seekpos = startfileoffset;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	for (int counter=0;counter<BIG_EDGE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		newsp.destdata= rcbuffer1[counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//central area
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	int	realoffset;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	int	rowindex=(BIG_CACHE_SIZE*BIG_CACHE_SIZE)-1;
//TempCode PD 14Nov97 	
//TempCode PD 14Nov97 	for (counter=0;counter<BIG_CACHE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		realoffset = rowindex-(counter*BIG_CACHE_SIZE);
//TempCode PD 14Nov97 		bigareacahe[realoffset]->fileblk=newsp.seekpos/4096;	//PD 21Nov96
//TempCode PD 14Nov97 		newsp.destdata = bigareacahe[realoffset]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//edge band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	for (counter=0;counter<BIG_EDGE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		newsp.destdata= rcbuffer0[counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StillGoingSouth
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::StillGoingSouth()
{
//TempCode PD 14Nov97 	int startfileoffset = GetFileOffset(currentdirection,bufferbase.X,bufferbase.Z);

	bufferbase.Z -= 0x20000;

	//Shuffle all the data north by 1 band

//TempCode PD 14Nov97 	ScrollNorth();
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollEdge(rcbuffer0);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollEdge(rcbuffer1);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//Add request for a new strip of data to be loaded
//TempCode PD 14Nov97 	//requests need to be added in reverse order
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	startfileoffset += ((BIG_CACHE_SIZE * BIG_FILE_SIZE)-BIG_EDGE_SIZE) * 4096;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	SeekStruc	newsp;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//eastern edge band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	newsp.filenum = currentfilenum;
//TempCode PD 14Nov97 	newsp.seekpos = startfileoffset;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	for (int counter=0;counter<BIG_EDGE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		newsp.destdata= rcbuffer1[counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//central area
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	int	realoffset = (BIG_CACHE_SIZE*(BIG_CACHE_SIZE-1));
//TempCode PD 14Nov97 	
//TempCode PD 14Nov97 	for (counter=0;counter<BIG_CACHE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		bigareacahe[realoffset+counter]->fileblk=newsp.seekpos/4096;
//TempCode PD 14Nov97 		newsp.destdata = bigareacahe[realoffset+counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//western edge band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	for (counter=0;counter<BIG_EDGE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		newsp.destdata= rcbuffer0[counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StillGoingWest
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::StillGoingWest()
{
//TempCode PD 14Nov97 	int startfileoffset = GetFileOffset(currentdirection,bufferbase.X,bufferbase.Z);

	bufferbase.X -= 0x20000;

//TempCode PD 14Nov97 	//Shuffle all the data east by 1 band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollEast();
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollEdge(rcbuffer0);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	ScrollEdge(rcbuffer1);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//Add request for a new strip of data to be loaded
//TempCode PD 14Nov97 	//requests need to be added in reverse order
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	startfileoffset += (BIG_FILE_SIZE-BIG_EDGE_SIZE) * 4096;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	SeekStruc	newsp;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//edge band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	newsp.filenum = currentfilenum;
//TempCode PD 14Nov97 	newsp.seekpos = startfileoffset;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	for (int counter=0;counter<BIG_EDGE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		newsp.destdata= rcbuffer1[counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//central area
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	int	realoffset;
//TempCode PD 14Nov97 	
//TempCode PD 14Nov97 	for (counter=0;counter<BIG_CACHE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		realoffset = (BIG_CACHE_SIZE*counter);
//TempCode PD 14Nov97 		bigareacahe[realoffset]->fileblk=newsp.seekpos/4096;	//PD 21Nov96
//TempCode PD 14Nov97 		newsp.destdata = bigareacahe[realoffset]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//edge band
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	for (counter=0;counter<BIG_EDGE_SIZE;counter++)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		newsp.destdata= rcbuffer0[counter]->data.data;
//TempCode PD 14Nov97 		AddSeekRequest(newsp);
//TempCode PD 14Nov97 		newsp.seekpos += 4096;
//TempCode PD 14Nov97 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NowGoingNorth
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::NowGoingNorth(MovingItem* fselitemp)
{
	currentdirection = WW_north;
	currentfilenum = AreaFiles[WW_north];

	BigRebuild(fselitemp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NowGoingEast
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::NowGoingEast(MovingItem* fselitemp)
{
	currentdirection = WW_east;
	currentfilenum = AreaFiles[WW_east];

	BigRebuild(fselitemp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NowGoingSouth
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::NowGoingSouth(MovingItem* fselitemp)
{
	currentdirection = WW_south;
	currentfilenum = AreaFiles[WW_south];

	BigRebuild(fselitemp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NowGoingWest
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::NowGoingWest(MovingItem* fselitemp)
{
	currentdirection = WW_west;
	currentfilenum = AreaFiles[WW_west];

	BigRebuild(fselitemp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BigRebuild
//Author		Paul.   
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::BigRebuild(MovingItem* fselitemp)
{
	//Prepare to re-center the buffer

	int	lastbuffx,lastbuffz;									//PD 21Nov96

	lastbuffx=bufferbase.X; lastbuffz=bufferbase.Z;				//PD 21Nov96

	//currentdirection has been updated already

	WhichWay whichway = currentdirection;

	SLong	 startfileoffset;

	FileNum	 whichfile;

	COORDS3D	coords = fselitemp->World;

	coords.X &= 0xFFFE0000;
	coords.Z &= 0xFFFE0000;

	bufferbase.X = coords.X - (10*0x20000);
	bufferbase.Z = coords.Z + (10*0x20000);

//TempCode PD 14Nov97 	RecenterBuffer(lastbuffx,lastbuffz,bufferbase.X,bufferbase.Z);//PD 21Nov96
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	//Select file based on the heading of the input item
//TempCode PD 14Nov97 	//Don't forget North is West, West is South, South is East, 
//TempCode PD 14Nov97 	//East is North, Up is Down, Down is Up and Oranges are purple!!!!!
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	int	cachestartindex,
//TempCode PD 14Nov97 		cacheskipindex,
//TempCode PD 14Nov97 		cacheseqindex;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	switch (whichway)
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 	case WW_north:
//TempCode PD 14Nov97 		whichfile = AreaFiles[whichway];
//TempCode PD 14Nov97 		cachestartindex = (BIG_CACHE_SIZE*BIG_CACHE_SIZE) - 1;
//TempCode PD 14Nov97 		cacheskipindex = -BIG_CACHE_SIZE;
//TempCode PD 14Nov97 		cacheseqindex = -1;
//TempCode PD 14Nov97 		coords.X += 10*0x20000;
//TempCode PD 14Nov97 		coords.Z -= 10*0x20000;
//TempCode PD 14Nov97 		break;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	case WW_east:
//TempCode PD 14Nov97 		whichfile = AreaFiles[whichway];
//TempCode PD 14Nov97 		cachestartindex = BIG_CACHE_SIZE*(BIG_CACHE_SIZE-1);
//TempCode PD 14Nov97 		cacheskipindex = 1;
//TempCode PD 14Nov97 		cacheseqindex = -BIG_CACHE_SIZE;
//TempCode PD 14Nov97 		coords.X -= 10*0x20000;
//TempCode PD 14Nov97 		coords.Z -= 10*0x20000;
//TempCode PD 14Nov97 		break;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	case WW_south:
//TempCode PD 14Nov97 		whichfile = AreaFiles[whichway];
//TempCode PD 14Nov97 		cachestartindex = 0;
//TempCode PD 14Nov97 		cacheskipindex = BIG_CACHE_SIZE;
//TempCode PD 14Nov97 		cacheseqindex = 1;
//TempCode PD 14Nov97 		coords.X -= 10*0x20000;
//TempCode PD 14Nov97 		coords.Z += 10*0x20000;
//TempCode PD 14Nov97 		break;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 	case WW_west:
//TempCode PD 14Nov97 		whichfile = AreaFiles[whichway];
//TempCode PD 14Nov97 		cachestartindex = BIG_CACHE_SIZE-1;
//TempCode PD 14Nov97 		cacheskipindex = -1;
//TempCode PD 14Nov97 		cacheseqindex = BIG_CACHE_SIZE;
//TempCode PD 14Nov97 		coords.X += 10*0x20000;
//TempCode PD 14Nov97 		coords.Z += 10*0x20000;
//TempCode PD 14Nov97 		break;
//TempCode PD 14Nov97 	}
//TempCode PD 14Nov97 	{
//TempCode PD 14Nov97 		currentfilenum = whichfile;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 		int	keepfileoffset = GetFileOffset(whichway,coords.X,coords.Z);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 		int	cachecurrentindex;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 		keepfileoffset -= BIG_EDGE_SIZE*4096;	//prepare to fill side buffers too
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 		int	side0bufindex = (BIG_CACHE_SIZE*BIG_EDGE_SIZE)-1;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 		int	side1bufindex = (BIG_CACHE_SIZE*BIG_EDGE_SIZE)-1;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 		for (int loadskip=0;loadskip<BIG_CACHE_SIZE;loadskip++)
//TempCode PD 14Nov97 		{
//TempCode PD 14Nov97 			int 			loadseq;
//TempCode PD 14Nov97 			SeekStruc		newsp;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 			cachecurrentindex = cachestartindex;
//TempCode PD 14Nov97 			cachestartindex += cacheskipindex;
//TempCode PD 14Nov97 			startfileoffset = keepfileoffset;
//TempCode PD 14Nov97 			keepfileoffset += BIG_FILE_SIZE*4096;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 			for (loadseq=0;loadseq<BIG_EDGE_SIZE;loadseq++)
//TempCode PD 14Nov97 			{
//TempCode PD 14Nov97 				newsp.filenum = whichfile;
//TempCode PD 14Nov97 				newsp.seekpos = startfileoffset;
//TempCode PD 14Nov97 				newsp.destdata = rcbuffer0[side0bufindex]->data.data;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 				AddSeekRequest(newsp);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 				startfileoffset += 4096;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 				side0bufindex--;
//TempCode PD 14Nov97 			}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 			for (loadseq=0;loadseq<BIG_CACHE_SIZE;loadseq++)
//TempCode PD 14Nov97 			{
//TempCode PD 14Nov97 				newsp.filenum = whichfile;
//TempCode PD 14Nov97 				newsp.seekpos = startfileoffset;
//TempCode PD 14Nov97 				bigareacahe[cachecurrentindex]->fileblk=newsp.seekpos/4096;//PD 21Nov96
//TempCode PD 14Nov97 				newsp.destdata = bigareacahe[cachecurrentindex]->data.data;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 				AddSeekRequest(newsp);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 				cachecurrentindex += cacheseqindex;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 				startfileoffset += 4096;
//TempCode PD 14Nov97 			}
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 			for (loadseq=0;loadseq<BIG_EDGE_SIZE;loadseq++)
//TempCode PD 14Nov97 			{
//TempCode PD 14Nov97 				newsp.filenum = whichfile;
//TempCode PD 14Nov97 				newsp.seekpos = startfileoffset;
//TempCode PD 14Nov97 				newsp.destdata = rcbuffer1[side1bufindex]->data.data;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 				AddSeekRequest(newsp);
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 				startfileoffset += 4096;
//TempCode PD 14Nov97 
//TempCode PD 14Nov97 				side1bufindex--;
//TempCode PD 14Nov97 			}
//TempCode PD 14Nov97 		}
//TempCode PD 14Nov97 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetArea
//Author		Paul.   
//Date			Tue 12 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::SetArea(MovingItem* fselitemp)
{
//Old_Code DAW 27Jan97 	const	SLong	Area1SW_X = 16777216;
//Old_Code DAW 27Jan97 	const	SLong	Area1SW_Z = 20971520;
//Old_Code DAW 27Jan97 
//Old_Code DAW 27Jan97 	const	SLong	Area1NE_X = 31457280;
//Old_Code DAW 27Jan97 	const	SLong	Area1NE_Z = 35651584;
//Old_Code DAW 27Jan97 
//Old_Code DAW 27Jan97 	const	SLong	Area2SW_X = 34603008;
//Old_Code DAW 27Jan97 	const	SLong	Area2SW_Z = 8388608;
//Old_Code DAW 27Jan97 
//Old_Code DAW 27Jan97 	const	SLong	Area2NE_X = 49283072;
//Old_Code DAW 27Jan97 	const	SLong	Area2NE_Z = 23068672;

	SLong	itemX = fselitemp->World.X;
	SLong	itemZ = fselitemp->World.Z;

	if (itemX>Area1SW_X && itemX<Area1NE_X)
	{
		if (itemZ>Area1SW_Z && itemZ<Area1NE_Z)
		{
			AreaBaseX = Area1SW_X;
			AreaBaseZ = Area1SW_Z;

//DeadCode PD 08Aug97 			if (Demoversion==FALSE)								//PD 28Jan97
//DeadCode PD 08Aug97 			{
				AreaFiles[0] = FIL_AREAW_NUM;
				AreaFiles[1] = FIL_AREAN_NUM;
				AreaFiles[2] = FIL_AREAE_NUM;
				AreaFiles[3] = FIL_AREAS_NUM;
//DeadCode PD 08Aug97 			}
//DeadCode PD 08Aug97 			else
//DeadCode PD 08Aug97 			{
//DeadCode PD 08Aug97 				AreaFiles[0] = FIL_DEMO1W_NUM;
//DeadCode PD 08Aug97 				AreaFiles[1] = FIL_DEMO1N_NUM;
//DeadCode PD 08Aug97 				AreaFiles[2] = FIL_DEMO1E_NUM;
//DeadCode PD 08Aug97 				AreaFiles[3] = FIL_DEMO1S_NUM;
//DeadCode PD 08Aug97 			}

			FILEMAN.SetupAreaFiles(AreaFiles);					//PD 18Nov96

			return;
		}
	}

	AreaBaseX = Area2SW_X;
	AreaBaseZ = Area2SW_Z;

	AreaFiles[0] = FIL_AREAW_NUM;
	AreaFiles[1] = FIL_AREAN_NUM;
	AreaFiles[2] = FIL_AREAE_NUM;
	AreaFiles[3] = FIL_AREAS_NUM;

	FILEMAN.SetupAreaFiles(AreaFiles);							//PD 18Nov96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BigInit
//Author		Paul.   
//Date			Fri 8 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::BigInit(ViewPoint* View_Point)
{
	MovingItem*	fselitemp;

	SLong	 	startfileoffset;
	COORDS3D	coords;
	int			cachestartindex,
				cacheskipindex,
				cacheseqindex,
				cachecurrentindex,
				keepfileoffset;

	FileNum	 	whichfile;
	WhichWay 	whichway;


	if (View_Point)
	{
		fselitemp = (MovingItem*)View_Point;
		View_Point->SelectView();
	}
	else
		fselitemp =*Manual_Pilot.ControlledAC2;	//JIM


	SetArea(fselitemp);

	whichway = GetDirectionFlags(fselitemp);

	coords = fselitemp->World;

	currentdirection = whichway;

	coords.X &= 0xFFFE0000;
	coords.Z &= 0xFFFE0000;

	bufferbase.X = coords.X - (10*0x20000);
	bufferbase.Z = coords.Z + (10*0x20000);

	//Select file based on the heading of the input item
	//Don't forget North is West, West is South, South is East, 
	//East is North, Up is Down, Down is Up and Oranges are purple!!!!!

	switch (whichway)
	{
	case WW_north:
		whichfile = AreaFiles[whichway];
		cachestartindex = (BIG_CACHE_SIZE*BIG_CACHE_SIZE) - 1;
		cacheskipindex = -BIG_CACHE_SIZE;
		cacheseqindex = -1;
		coords.X += 10*0x20000;
		coords.Z -= 10*0x20000;
		break;

	case WW_east:
		whichfile = AreaFiles[whichway];
		cachestartindex = BIG_CACHE_SIZE*(BIG_CACHE_SIZE-1);
		cacheskipindex = 1;
		cacheseqindex = -BIG_CACHE_SIZE;
		coords.X -= 10*0x20000;
		coords.Z -= 10*0x20000;
		break;

	case WW_south:
		whichfile = AreaFiles[whichway];
		cachestartindex = 0;
		cacheskipindex = BIG_CACHE_SIZE;
		cacheseqindex = 1;
		coords.X -= 10*0x20000;
		coords.Z += 10*0x20000;
		break;

	case WW_west:
		whichfile = AreaFiles[whichway];
		cachestartindex = BIG_CACHE_SIZE-1;
		cacheskipindex = -1;
		cacheseqindex = BIG_CACHE_SIZE;
		coords.X += 10*0x20000;
		coords.Z += 10*0x20000;
		break;
	}

	{//Allocate cache memory									//PD 19Nov96

		int	row,
			column,
			rowindex;

		for (row=0;row<BIG_CACHE_SIZE;row++)
		{
			rowindex=row*BIG_CACHE_SIZE;

			for (column=0;column<BIG_CACHE_SIZE;column++)
				if (bigareacahe[rowindex+column]==NULL)			//PD 18Jun97
					bigareacahe[rowindex+column] = new CachedFileBlock;

			rowindex=row*BIG_EDGE_SIZE;

			for (column=0;column<BIG_EDGE_SIZE;column++)
			{
				if (rcbuffer0[rowindex+column]==NULL)			//PD 18Jun97
					rcbuffer0[rowindex+column] = new CachedFileBlock;
				if (rcbuffer1[rowindex+column]==NULL)			//PD 18Jun97
					rcbuffer1[rowindex+column] = new CachedFileBlock;
			}
		}
	}//Cache memory allocated									//PD 19Nov96

	{
		currentfilenum = whichfile;

		keepfileoffset = GetFileOffset(whichway,coords.X,coords.Z);

		keepfileoffset -= BIG_EDGE_SIZE*4096;	//prepare to fill side buffers too

		int	side0bufindex = (BIG_CACHE_SIZE*BIG_EDGE_SIZE)-1;

		int	side1bufindex = (BIG_CACHE_SIZE*BIG_EDGE_SIZE)-1;

		for (int loadskip=0;loadskip<BIG_CACHE_SIZE;loadskip++)
		{
			int 			loadseq;
			LSFileBlockPtr	fbp;

			cachecurrentindex = cachestartindex;
			cachestartindex += cacheskipindex;
			startfileoffset = keepfileoffset;
			keepfileoffset += BIG_FILE_SIZE*4096;

			for (loadseq=0;loadseq<BIG_EDGE_SIZE;loadseq++)
			{
				fbp = new LSFileBlock(whichfile,4096,startfileoffset,FALSE);

				rcbuffer0[side0bufindex]->data=*(CachedDataBlock*)fbp->GetData();

				delete (fbp);

				startfileoffset += 4096;

				side0bufindex--;
			}

			for (loadseq=0;loadseq<BIG_CACHE_SIZE;loadseq++)
			{
				fbp = new LSFileBlock(whichfile,4096,startfileoffset,FALSE);

				bigareacahe[cachecurrentindex]->fileblk=startfileoffset/4096;

//DeadCode DAW 07Jan97 				if (cachecurrentindex==195)
//DeadCode DAW 07Jan97 				{
//DeadCode DAW 07Jan97 					FILE * fp=fopen("\\fly\\src\\poo1.bin","wb");
//DeadCode DAW 07Jan97 					for (int bc=1226;bc<0x1000;bc++)
//DeadCode DAW 07Jan97 						fputc(((UByte*)fbp->GetData())[bc],fp);
//DeadCode DAW 07Jan97 					fclose(fp);
//DeadCode DAW 07Jan97 				}

				bigareacahe[cachecurrentindex]->data=*(CachedDataBlock*)fbp->GetData();

				delete (fbp);

//DeadCode JIM 09Jan97 				if (cachecurrentindex==195)
//DeadCode JIM 09Jan97 				{
//DeadCode JIM 09Jan97 					FILE * fp=fopen("\\fly\\src\\poo2.bin","wb");
//DeadCode JIM 09Jan97 					for (int bc=1226;bc<0x1000;bc++)
//DeadCode JIM 09Jan97 						fputc(bigareacahe[cachecurrentindex]->data.data[bc],fp);
//DeadCode JIM 09Jan97 					fclose(fp);
//DeadCode JIM 09Jan97 				}

				cachecurrentindex += cacheseqindex;

				startfileoffset += 4096;
			}

			for (loadseq=0;loadseq<BIG_EDGE_SIZE;loadseq++)
			{
				fbp = new LSFileBlock(whichfile,4096,startfileoffset,FALSE);

				rcbuffer1[side1bufindex]->data=*(CachedDataBlock*)fbp->GetData();

				delete (fbp);

				startfileoffset += 4096;

				side1bufindex--;
			}
		}
	}

	Land_Scape.SetupGroundData(fselitemp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScrollSouth
//Author		Paul.   
//Date			Tue 19 Nov 1996
//
//Description	scrolls all entries in the big cache one block south
//				the blocks that would drop off the southern edge are
//				placed along the northern edge
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ScrollSouth()
{
	int	row,
		column,
		newrow;

	int	rowindex = (BIG_CACHE_SIZE-1)*BIG_CACHE_SIZE;

	//copy the bottom row into a temporary buffer

	CachedFileBlockP temp[BIG_CACHE_SIZE];

	for (column=0;column<BIG_CACHE_SIZE;column++)
		temp[column]=bigareacahe[rowindex+column];

	//now scroll the main buffer down 1 row

	for (row=BIG_CACHE_SIZE-1;row>0;row--)
	{
		rowindex = row*BIG_CACHE_SIZE;

		for (column=0;column<BIG_CACHE_SIZE;column++)
			bigareacahe[rowindex+column]=bigareacahe[rowindex-BIG_CACHE_SIZE+column];
	}

	//now, refill the top line of the buffer with the row saved from the
	//bottom of the buffer

	for (column=0;column<BIG_CACHE_SIZE;column++)
		bigareacahe[column]=temp[column];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScrollNorth
//Author		Paul.   
//Date			Tue 19 Nov 1996
//
//Description	scrolls all entries in the big cache one block north
//				the blocks that would drop off the northern edge are
//				placed along the southern edge
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ScrollNorth()
{
	int	row,
		column,
		newrow;

	int	rowindex;

	//copy the top row into a temporary buffer

	CachedFileBlockP temp[BIG_CACHE_SIZE];

	for (column=0;column<BIG_CACHE_SIZE;column++)
		temp[column]=bigareacahe[column];

	//now scroll the main buffer up 1 row

	for (row=0;row<BIG_CACHE_SIZE-1;row++)
	{
		rowindex=row*BIG_CACHE_SIZE;

		for (column=0;column<BIG_CACHE_SIZE;column++)
			bigareacahe[rowindex+column]=bigareacahe[rowindex+BIG_CACHE_SIZE+column];
	}

	//now, refill the bottom line of the buffer with the row saved from the
	//top of the buffer

	rowindex=(BIG_CACHE_SIZE-1)*BIG_CACHE_SIZE;

	for (column=0;column<BIG_CACHE_SIZE;column++)
		bigareacahe[rowindex+column]=temp[column];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScrollWest
//Author		Paul.   
//Date			Tue 19 Nov 1996
//
//Description	scrolls all entries in the big cache one block west
//				the blocks that would drop off the western edge are
//				placed along the eastern edge
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ScrollWest()
{
	int	row,
		column,
		newrow;

	int	rowindex;

	//copy the left column into a temporary buffer

	CachedFileBlockP temp[BIG_CACHE_SIZE];

	for (row=0;row<BIG_CACHE_SIZE;row++)
	{
		rowindex=row*BIG_CACHE_SIZE;

		temp[row]=bigareacahe[rowindex];
	}

	//now scroll the main buffer left 1 column

	for (column=0;column<BIG_CACHE_SIZE-1;column++)
	{
		for (row=0;row<BIG_CACHE_SIZE;row++)
		{
			rowindex=row*BIG_CACHE_SIZE;

			bigareacahe[rowindex+column]=bigareacahe[rowindex+column+1];
		}
	}

	//now, refill the right column of the buffer with the column saved from the
	//left of the buffer

	for (row=0;row<BIG_CACHE_SIZE;row++)
	{
		rowindex=(BIG_CACHE_SIZE-1)+(row*BIG_CACHE_SIZE);

		bigareacahe[rowindex]=temp[row];
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScrollEast
//Author		Paul.   
//Date			Tue 19 Nov 1996
//
//Description	scrolls all entries in the big cache one block east
//				the blocks that would drop off the eastern edge are
//				placed along the western edge
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ScrollEast()
{
	int	row,
		column,
		newrow;

	int	rowindex;

	//copy the right column into a temporary buffer

	CachedFileBlockP temp[BIG_CACHE_SIZE];

	for (row=0;row<BIG_CACHE_SIZE;row++)
	{
		rowindex=(BIG_CACHE_SIZE-1)+(row*BIG_CACHE_SIZE);

		temp[row]=bigareacahe[rowindex];
	}

	//now scroll the main buffer right 1 column

	for (column=BIG_CACHE_SIZE-1;column>0;column--)
	{
		for (row=0;row<BIG_CACHE_SIZE;row++)
		{
			rowindex=row*BIG_CACHE_SIZE;

			bigareacahe[rowindex+column]=bigareacahe[rowindex+column-1];
		}
	}

	//now, refill the left column of the buffer with the column saved from the
	//right of the buffer

	for (row=0;row<BIG_CACHE_SIZE;row++)
	{
		rowindex=row*BIG_CACHE_SIZE;

		bigareacahe[rowindex]=temp[row];
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScrollEdge
//Author		Paul.   
//Date			Tue 19 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ScrollEdge(CachedFileBlockP* edge)
{
	int	row,
		column,
		newrow;

	int	rowindex = (BIG_CACHE_SIZE-1)*BIG_EDGE_SIZE;

	//copy the bottom row into a temporary buffer

	CachedFileBlockP temp[BIG_EDGE_SIZE];

	for (column=0;column<BIG_EDGE_SIZE;column++)
		temp[column]=edge[rowindex+column];

	//now scroll the main buffer down 1 row

	for (row=BIG_CACHE_SIZE-1;row>0;row--)
	{
		rowindex = row*BIG_EDGE_SIZE;

		for (column=0;column<BIG_EDGE_SIZE;column++)
			edge[rowindex+column]=edge[rowindex-BIG_EDGE_SIZE+column];
	}

	//now, refill the top line of the buffer with the row saved from the
	//bottom of the buffer

	for (column=0;column<BIG_EDGE_SIZE;column++)
		edge[column]=temp[column];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetEverything
//Author		Paul.   
//Date			Fri 22 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::ResetEverything()
{
	DeleteCache();
	LandStream.InitialiseCache();
	BigInit(NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DataValid
//Author		Paul.   
//Date			Mon 9 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Land_Stream::DataValid(COORDS3D& coords)
{

	if (!_Collide.tdalt)
		return(TRUE);

	SLong		xindex,zindex;

	COORDS3D	lcoords=coords;

	lcoords.X	&= 0xFFFE0000;

	xindex = (lcoords.X - bufferbase.X)/0x20000;

	if (xindex<=5 || xindex >=15)
		return(FALSE);

	lcoords.Z	&= 0xFFFE0000;

	zindex = (bufferbase.Z - lcoords.Z)/0x20000;

	if (zindex<=5 || zindex>=15)
		return(FALSE);

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OverTheEdge
//Author		Paul.   
//Date			Wed 11 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Land_Stream::OverTheEdge(itemptr itmp,SLong& dx,SLong& dz)
{
	const	SLong	TILE_STEP=0x20000;
	const	SLong	BORDER_SIZE=6*TILE_STEP;

//Old_Code DAW 27Jan97 	const	SLong	Area1SW_X = 16777216;
//Old_Code DAW 27Jan97 	const	SLong	Area1SW_Z = 20971520;
//Old_Code DAW 27Jan97 
//Old_Code DAW 27Jan97 	const	SLong	Area1NE_X = 31457280;
//Old_Code DAW 27Jan97 	const	SLong	Area1NE_Z = 35651584;
//Old_Code DAW 27Jan97 
//Old_Code DAW 27Jan97 	const	SLong	Area2SW_X = 34603008;
//Old_Code DAW 27Jan97 	const	SLong	Area2SW_Z = 8388608;
//Old_Code DAW 27Jan97 
//Old_Code DAW 27Jan97 	const	SLong	Area2NE_X = 49283072;
//Old_Code DAW 27Jan97 	const	SLong	Area2NE_Z = 23068672;

	Bool	retval=FALSE;

	SLong	AreaSW_X,
			AreaSW_Z,
			AreaNE_X,
			AreaNE_Z;

	if (AreaBaseX==Area2SW_X &&
		AreaBaseZ==Area2SW_Z)
	{
		//In area 2

		AreaSW_X = Area2SW_X;
		AreaSW_Z = Area2SW_Z;
		AreaNE_X = Area2NE_X;
		AreaNE_Z = Area2NE_Z;
	}
	else
	{
		//In area 1

		AreaSW_X = Area1SW_X;
		AreaSW_Z = Area1SW_Z;
		AreaNE_X = Area1NE_X;
		AreaNE_Z = Area1NE_Z;
	}

	dx=dz=0;

	AreaSW_X += BORDER_SIZE;
	AreaSW_Z += BORDER_SIZE;

	AreaNE_X -= BORDER_SIZE;
	AreaNE_Z -= BORDER_SIZE;

	if (itmp->World.X<=AreaSW_X)
		dx=TILE_STEP;
	else
		if (itmp->World.X>=AreaNE_X)
			dx=-TILE_STEP;

	if (itmp->World.Z<=AreaSW_Z)
		dz=TILE_STEP;
	else
		if (itmp->World.Z>=AreaNE_Z)
			dz=-TILE_STEP;

	if (dx+dz)
		retval=TRUE;

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RezChanged
//LastModified:	PD 10Jun97
//Author		Paul.   
//Date			Fri 6 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Land_Stream::RezChanged(Window* win,ScreenRez& srez)
{
	currwin=win;
	currwin->DoInitLand();									//PD 10Jun97

	if (Three_Dee.b3DRunning)
	{
		SWord	tColorDepth=Save_Data.colourdepth;				//PD 10Jun97
		Save_Data.colourdepth=srez.colourdepth;					//PD 10Jun97
		ResetEverything();										//PD 10Jun97
		Save_Data.colourdepth=tColorDepth;						//PD 10Jun97
	}
}


void ColorTileDump(UByte* lpColorData)
{
	FILE* fo=fopen("Arse.h8","wb");

	UByte	ubHdr=0x88;

	fputc(ubHdr,fo);

	for (int row=0;row<256;row++)
	{
		for (int column=0;column<256;column++)
		{
			fputc(*lpColorData++,fo);
		}
		lpColorData++;
	}

	fclose(fo);

}

#endif		//COMMENT


