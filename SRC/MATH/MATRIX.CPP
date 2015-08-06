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
//Filename       matrix.cpp
//System         
//Author         Paul.   
//Date           Tue 22 Aug 1995
//Description    3D transformation matrix generation code
//------------------------------------------------------------------------------

	#include	"DOSDefs.h"
	#include	"myAngles.h"
	#include	"display.h"										//DAW 15Apr96
	#include	"3DDefs.h"
	#include	"Worldinc.h"

	#include	"Matrix.h"
	#include 	"mymath.h"										//RDH 30Oct95
	#include	"vector.h"										//PD 12Apr96
	#include	"vertex.h"										//PD 12Apr96
	#include	"Enumbits.m"
	#include	"polygon.h"

	class	matrix	_matrix;


//	MATRIX ELEMENTS
//  ---------------

//	L11       CH.CR - SP.SH.SR
//  L21       - (SR.CH + SP.SH.CR)
//  L31       - CP.SH
//	L12       SR.CP
//	L22       CP.CR
//	L32       - SP
//	L13       SP.CH.SR + SH.CR
//	L23       CH.CR.SP  - SH.SR
//	L33       CP.CH


#ifdef	__WATCOMC__
extern	"C"	SLong ASMTransform(MATRIX_PTR,SLong&,SLong&,SLong&);
#else
#ifdef	__MSVC__
extern	"C" void XASMTransform(void);
#pragma warning (disable:4035)
inline SLong ASMTransform(MATRIX_PTR a,SLong& b,SLong& c,SLong& d)
{
	_asm
	{
		push	ecx
		mov		eax,a
		mov		edx,b
		mov		ebx,c
		mov		ecx,d
		call	XASMTransform
		pop		ecx
	}
}
#pragma warning (default:4035)
#endif
#endif

#ifdef	__WATCOMC__
extern	"C" Bool ASMDoBigXProd(SLong,SLong,SLong,SLong);		//PD 27Nov96
#else
#ifdef	__MSVC__
//-----------------------------------------------------------------------------
// Procedure    ASMDoBigXProd
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
extern	"C" void XASMDoBigXProd(void);
#pragma warning (disable:4035)
inline	Bool ASMDoBigXProd(SLong a,SLong b,SLong c,SLong d)
{
	_asm {
		push	ecx
		mov		eax,a
		mov		edx,b
		mov		ebx,c
		mov		ecx,d
		call	XASMDoBigXProd
		pop		ecx
	}
}
#pragma warning (default:4035)
#endif
#endif

extern	void ASMBody2Screen(SLong&,SLong&,SLong&,SLong&,SLong&,SLong&);
#ifdef __WATCOMC__
#pragma	aux	 ASMBody2Screen			=		\
"		fild	dword ptr ds:[ecx]			"\
"		fabs								"\
"		mov		ecx,00800000h				"\
"		fild	dword ptr ds:[edx]			"\
"		push	ecx							"\
"		fmulp	st(1),st					"\
"		fild	dword ptr ss:[esp]			"\
"		fdivrp	st(1),st					"\
"		add		esp,4						"\
"		fld		st(0)						"\
"		fild	dword ptr ds:[eax]			"\
"		fmulp	st(1),st					"\
"		fild	dword ptr ds:[ebx]			"\
"		fmulp	st(2),st					"\
"		fistp	dword ptr ds:[esi]			"\
"		fchs								"\
"		fistp	dword ptr ds:[edi]			"\
parm	[eax] [ebx] [ecx] [edx] [esi] [edi]	\
modify	[ecx]
#else
#ifdef __MSVC__
inline 	void ASMBody2Screen(SLong& num1,SLong& num2,SLong& num3,SLong& num4,SLong& num5,SLong& num6)
{
    __asm
    {
		mov eax,num1;
		mov ebx,num2;
		mov ecx,num3;
		mov edx,num4;
		mov esi,num5;
		mov edi,num6;
		fild	dword ptr ds:[ecx];
		fabs;
		mov		ecx,00800000h;
		fild	dword ptr ds:[edx];
		push	ecx;
		fmulp	st(1),st;
		fild	dword ptr ss:[esp];
		fdivrp	st(1),st;
		add		esp,4;
		fld		st(0);
		fild	dword ptr ds:[eax];
		fmulp	st(1),st;
		fild	dword ptr ds:[ebx];
		fmulp	st(2),st;
		fistp	dword ptr ds:[esi];
		fchs;
		fistp	dword ptr ds:[edi];
    }
}

#endif
#endif

//Use maths coprocessor sincos function - converts Rowan degrees
//to radians first
//
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
inline	void fpSin_Cos(ANGLES angle, Float& sin_ang, Float& cos_ang)
{
	int	iang = angle;
    __asm
    {
		mov eax,iang;
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
    }
}

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

#endif
#endif

//DeadCode PD 13Oct98 fpmatrix_ matrix::IDENTITY={1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	matrix
//LastModified:	PD 20Dec95
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	Removed old code and added coordinate scaling
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
void matrix::generate(ANGLES heading, ANGLES pitch, ANGLES roll, MATRIX_PTR matrix)//PD 25Jul96
{
	SWord	sh,sp,sr,ch,cp,cr;

	Math_Lib.high_sin_cos(heading,sh,ch);						//PD 23Feb96
																//RDH 30Oct95
	Math_Lib.high_sin_cos(pitch,sp,cp);							//PD 23Feb96

	Math_Lib.high_sin_cos(roll,sr,cr);							//PD 23Feb96

	SWord	sr_sh,sr_ch,cr_sh,cr_ch;

	sr_sh = (sh * sr)>>15;

	sr_ch = (sr * ch)>>15;

	cr_sh = (cr * sh)>>15;

	cr_ch = (cr * ch)>>15;

	matrix->L11 = cr_ch - ((sp * sr_sh)>>15);

	matrix->L21 = -(sr_ch + ((sp * cr_sh)>>15));

	matrix->L31 = -((cp * sh)>>15);



	matrix->L12 = (sr * cp)>>15;

	matrix->L22 = (cp * cr)>>15;

	matrix->L32 = -sp;



	matrix->L13 = ((sp * sr_ch)>>15) + cr_sh;

	matrix->L23 = ((sp * cr_ch)>>15) - sr_sh;

	matrix->L33 = (cp * ch)>>15;

//PD 16Apr96 - nice idea but can't use it 'cos bz is no longer a range in cm for use with
//				the rest of the code (shading , cone checking , draw ranges etc.)
//TempCode PD 16Apr96 	//Introduce scaling factors for different screen resolutions//PD 16Apr96
//TempCode PD 16Apr96 
//TempCode PD 16Apr96 	SWord	width = screen->PhysicalWidth;
//TempCode PD 16Apr96 
//TempCode PD 16Apr96 	SWord	scalefactor = ((320<<15)/width);
//TempCode PD 16Apr96 
//TempCode PD 16Apr96 	matrix->L31 = (matrix->L31 * scalefactor)>>15;
//TempCode PD 16Apr96 
//TempCode PD 16Apr96 	matrix->L32 = (matrix->L32 * scalefactor)>>15;
//TempCode PD 16Apr96 
//TempCode PD 16Apr96 	matrix->L33 = (matrix->L33 * scalefactor)>>15;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		generate2
//Author		Paul.   
//Date			Mon 26 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::generate2(ANGLES heading, ANGLES pitch, ANGLES roll, MATRIX_PTR matrix)
{
	SWord	sh,sp,sr,ch,cp,cr;

	SWord	sp_sh,sr_ch,sp_ch,ch_cr;

	Math_Lib.high_sin_cos(heading,sh,ch);						//PD 23Feb96

	Math_Lib.high_sin_cos(pitch,sp,cp);							//PD 23Feb96

	Math_Lib.high_sin_cos(roll,sr,cr);							//PD 23Feb96

	sp_sh = (sp * sh)>>15;

	sr_ch = (sr * ch)>>15;

	sp_ch = (sp * ch)>>15;

	ch_cr = (ch * cr)>>15;

	matrix->L11 = ch_cr + ((sp_sh * sr)>>15);

	matrix->L12 = sr_ch - ((sp_sh * cr)>>15);

	matrix->L13 = (cp * sh)>>15;

	matrix->L21 = -((sr *cp)>>15);								//PD 26Feb96

	matrix->L22 = (cp * cr)>>15;

	matrix->L23 = sp;

	matrix->L31 = ((sp * sr_ch)>>15) - ((sh * cr)>>15);

	matrix->L32 = -(((cr * sp_ch)>>15) + ((sh * sr)>>15));

	matrix->L33 = (cp * ch)>>15;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		generater
//Author		Paul.   
//Date			Wed 5 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::generater(ANGLES roll,MATRIX_PTR m)
{
	SWord	sin_roll,cos_roll;

	roll = ANGLES_0Deg-roll;

	Math_Lib.high_sin_cos(roll,sin_roll,cos_roll);

	m->L11 =
		m->L22 = cos_roll;

	m->L21 = sin_roll;

	m->L12 = -sin_roll;

	m->L31 = m->L32 = m->L13 = m->L23 = 0;
	
	m->L33 = 0x07FFF;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		generatep
//Author		Paul.   
//Date			Thu 6 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::generatep(ANGLES pitch, MATRIX_PTR m)
{
	SWord	sin_pitch,cos_pitch;

	pitch = ANGLES_0Deg-pitch;

	Math_Lib.high_sin_cos(pitch,sin_pitch,cos_pitch);

	m->L11 = 0x07FFF;

	m->L21 = m->L31 = m->L12 = m->L13 = 0;

	m->L22 = m->L33 = cos_pitch;

	m->L32 = sin_pitch;

	m->L23 = -sin_pitch;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		generateh
//Author		Paul.   
//Date			Tue 2 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::generateh(ANGLES hdg,MATRIX_PTR m)
{
	SWord	sin_hdg,cos_hdg;

	Math_Lib.high_sin_cos(hdg,sin_hdg,cos_hdg);

	m->L11 =
		m->L33 = cos_hdg;

	m->L31 = -sin_hdg;

	m->L13 = sin_hdg;

	m->L21 = m->L12 = m->L32 = m->L23 = 0;

	m->L22 = 0x07FFF;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		inverse
//Author		Paul.   
//Date			Fri 17 Nov 1995
//
//Description	Generates the inverse of the current transformation
//				matrix.
//
//L11	=	CR.CH + SR.SP.SH
//L21	=	-SR.CP
//L31	=	SR.SP.CH - CR.SH
//
//
//L12	=	SR.CH - CR.SP.SH
//L22	=	CR.CP
//L32	=	-(SR.SH + CR.SP.CH)
//
//
//L13	=	CP.SH
//L23	=	SP
//L33	=	CP.CH
//
// For the following version, the angles don't need reversing
// uses cos(-theta) == cos(theta) and sin(-theta) == -sin(theta)
// to simplify the method above.
//	
//L11	=	CR.CH - SR.SP.SH
//L21	=	SR.CP
//L31	=	SR.SP.CH + CR.SH
//
//
//L12	=	-SR.CH - CR.SP.SH
//L22	=	CR.CP
//L32	=	-(SR.SH - CR.SP.CH)
//
//
//L13	=	-CP.SH
//L23	=	-SP
//L33	=	CP.CH
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::inverse(ANGLES heading, ANGLES pitch, ANGLES roll, MATRIX_PTR matrix)
{
	SWord	sh,sp,sr,ch,cp,cr;

	SLong	cr_ch,sr_sp,cr_sp,temp;

	//Get the sines/cosines of these angles

	Math_Lib.high_sin_cos(heading,sh,ch);						//PD 23Feb96

	Math_Lib.high_sin_cos(pitch,sp,cp);							//PD 23Feb96

	Math_Lib.high_sin_cos(roll,sr,cr);							//PD 23Feb96

	//Generate some intermediate values

	cr_ch = cr * ch;
	sr_sp = sr * sp;
	cr_sp = cr * sp;

	//Fill in the new matrix

	temp		=	cr_ch - ((sr_sp>>15) * sh);
	matrix->L11	=	temp>>15;

	temp		=	sr * cp;
	matrix->L21	=	temp>>15;

	temp		=	((sr_sp>>15) * ch) + (cr * sh);
	matrix->L31	=	temp>>15;

	temp		=	-(sr * ch) - ((cr_sp>>15) * sh);
	matrix->L12	=	temp>>15;

	temp		=	cr * cp;
	matrix->L22	=	temp>>15;

	temp		=	((cr_ch>>15) * sp)-(sr * sh);
	matrix->L32	=	temp>>15;

	temp		=	-(cp * sh);
	matrix->L13	=	temp>>15;

	matrix->L23	=	-sp;

	temp		=	cp * ch;
	matrix->L33	=	temp>>15;

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getxdeltas
//Author		Paul.   
//Date			Tue 31 Oct 1995
//
//Description	Returns the body x,y,z deltas required to move 1 cm in the
//				positive world X direction
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//TempCode PD 4Mar98 void matrix::getxdeltas(MATRIX_PTR T, SLong& x, SLong& y, SLong& z)
//TempCode PD 4Mar98 {
//TempCode PD 4Mar98 	SLong tx,ty,tz;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	tx = T->L11;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	ty = T->L21;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	tz = T->L31;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	x = tx>>1;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	y = ty>>1;
//TempCode PD 4Mar98 	
//TempCode PD 4Mar98 	z = tz>>1;
//TempCode PD 4Mar98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getzdeltas
//Author		Paul.   
//Date			Tue 31 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//TempCode PD 4Mar98 void matrix::getzdeltas(MATRIX_PTR T, SLong& x, SLong& y, SLong& z)
//TempCode PD 4Mar98 {
//TempCode PD 4Mar98 	SLong tx,ty,tz;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	tx = T->L13;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	ty = T->L23;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	tz = T->L33;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	x = tx>>1;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	y = ty>>1;
//TempCode PD 4Mar98 	
//TempCode PD 4Mar98 	z = tz>>1;
//TempCode PD 4Mar98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		transform_y
//LastModified:	PD 13Mar96
//Author		Paul.   
//Date			Thu 23 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	extern SLong TestOFlowY(SLong a);
#ifdef __WATCOMC__
	#pragma aux TestOFlowY =					\
				"mov	edx,eax"				\
				"sar	edx,0x1F"				\
				"add	eax,eax"				\
				"adc	edx,edx"				\
				"mov	ebx,eax"				\
				"sar	ebx,0x1F"				\
				"xor	ebx,edx"				\
				"jz		short noover"			\
				"sar	edx,1"					\
				"rcr	eax,1"					\
			"noover:"							\
				parm	[eax]					\
				modify	[edx ebx]				\
				value	[eax]
#else
#ifdef __MSVC__
inline  SLong TestOFlowY(SLong a)
{
	SLong	retval;
    __asm
    {
		mov eax,a;
		mov	edx,eax;
		sar	edx,0x1F;
		add	eax,eax;
		adc	edx,edx;
		mov	ebx,eax;
		sar	ebx,0x1F;
		xor	ebx,edx;
		jz		short noover;
		sar	edx,1;
		rcr	eax,1;
	noover:
		mov retval,eax;
    }
    return retval;
}

#endif
#endif

//TempCode PD 4Mar98 void matrix::transform_y(	MATRIX_PTR T, SLong y, SWord scale,
//TempCode PD 4Mar98 							SLong& rtx, SLong& rty, SLong& rtz)
//TempCode PD 4Mar98 {
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	SLong	tx,ty,tz;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	SLong	temp = (y>=0)?y:-y;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	SWord	y_scale=0;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	while(temp>0x07FFF)
//TempCode PD 4Mar98 	{
//TempCode PD 4Mar98 		temp>>=1;
//TempCode PD 4Mar98 		y_scale++;
//TempCode PD 4Mar98 	}
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	y>>=y_scale;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	tx = y * T->L12;										//PD 13Mar96
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	ty = y * T->L22;										//PD 13Mar96
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	tz = y * T->L32;										//PD 13Mar96
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	if((rtx = TestOFlowY(tx))==tx)
//TempCode PD 4Mar98 	{
//TempCode PD 4Mar98 		y_scale++;
//TempCode PD 4Mar98 		rty = ty;
//TempCode PD 4Mar98 		rtz = tz;
//TempCode PD 4Mar98 	}
//TempCode PD 4Mar98 	else
//TempCode PD 4Mar98 	{
//TempCode PD 4Mar98 		if((rty = TestOFlowY(ty))==ty)
//TempCode PD 4Mar98 		{
//TempCode PD 4Mar98 			y_scale++;
//TempCode PD 4Mar98 			rtx = tx;
//TempCode PD 4Mar98 			rtz = tz;
//TempCode PD 4Mar98 		}
//TempCode PD 4Mar98 		else
//TempCode PD 4Mar98 		{
//TempCode PD 4Mar98 			if((rtz = TestOFlowY(tz))==tz)
//TempCode PD 4Mar98 			{
//TempCode PD 4Mar98 				y_scale++;
//TempCode PD 4Mar98 				rtx = tx;
//TempCode PD 4Mar98 				rty = ty;
//TempCode PD 4Mar98 			}
//TempCode PD 4Mar98 		}
//TempCode PD 4Mar98 	}
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	SWord	scale_diff;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	scale_diff = scale - y_scale;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	if(scale_diff<=0)
//TempCode PD 4Mar98 		return;
//TempCode PD 4Mar98 
//TempCode PD 4Mar98 	rtx >>= scale_diff;
//TempCode PD 4Mar98 	rty >>= scale_diff;
//TempCode PD 4Mar98 	rtz >>= scale_diff;
//TempCode PD 4Mar98 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	transform
//LastModified:	PD 31Oct95
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Fri 25 Aug 1995
//Modified	
//
//Description	Transforms a point (Now includes a shift factor to avoid any
//				overflows later).
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
UWord matrix::transform(MATRIX_PTR T, SLong& x, SLong& y, SLong& z)
{
	return ((UWord )ASMTransform(T,x,y,z));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		rotate
//Author		Paul.   
//Date			Wed 5 Jun 1996
//
//Description	Transformation with no scaling tests
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::rotate(MATRIX_PTR T, SLong& x, SLong& y, SLong& z)
{
	SLong txa,tya,tza;

	SLong txb,tyb,tzb;

	SLong txc,tyc,tzc;

	txa = (T->L11)*x; txb = (T->L12)*y; txc = (T->L13)*z;

	tya = (T->L21)*x; tyb = (T->L22)*y; tyc = (T->L23)*z;

	tza = (T->L31)*x; tzb = (T->L32)*y; tzc = (T->L33)*z;

	x = (txa + txb + txc)/ANGLES_FRACT;

	y = (tya + tyb + tyc)/ANGLES_FRACT;

	z = (tza + tzb + tzc)/ANGLES_FRACT;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		multiply
//Author		Paul											//PD 27Feb96
//Date			Wed 25 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::multiply(MATRIX_PTR t,MATRIX_PTR sip)
{
	MATRIX		tmat;											//PD 25Jul96
	MATRIX_PTR	dip = &tmat;									//PD 25Jul96

	SWord	*si,*di;

	si = &sip->L11;
	di = &dip->L11;

	int	j;

	SLong	temp;

	for(j=0;j<3;j++)
	{
		temp = (*si * t->L11)
			+ (*(si+1) * t->L21)
				+ (*(si+2) * t->L31);

		*di++ = (SWord )(temp>>15);

		temp = (*si * t->L12)
			+ (*(si+1) * t->L22)
				+ (*(si+2) * t->L32);

		*di++ = (SWord )(temp>>15);

		temp = (*si * t->L13)
			+ (*(si+1) * t->L23)
				+ (*(si+2) * t->L33);

		*di++ = (SWord )(temp>>15);

		si += 3;
	}

	//copy the new matrix back to sip

	si = &t->L11;
	di = &dip->L11;

	for(j=0;j<9;j++)
	{
		*si++ = *di++;
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		scaleto16bit
//Author		Paul.   
//Date			Tue 31 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord matrix::scaleto16bit(SLong& x, SLong& y, SLong& z)
{
extern SWord GetScale(SLong x,SLong y,SLong z);
#ifdef __WATCOMC__
#pragma aux GetScale =							\
			"mov	edx,eax"					\
			"sar	edx,0x1F"					\
			"xor	eax,edx"					\
			"sub	eax,edx"					\
			"mov	edx,ebx"					\
			"sar	edx,0x1F"					\
			"xor	ebx,edx"					\
			"sub	ebx,edx"					\
			"mov	edx,ecx"					\
			"sar	edx,0x1F"					\
			"xor	ecx,edx"					\
			"sub	ecx,edx"					\
			"or		eax,ebx"					\
			"or		ecx,eax"					\
			"bsr	eax,ecx"					\
			"sub	eax,0x0E"					\
			"jnc	short done"					\
			"xor	eax,eax"					\
			"done:"								\
			parm  	[eax] [ebx] [ecx]			\
			modify	[edx]						\
			value 	[ax]
#else
#ifdef __MSVC__
inline  SWord GetScale(SLong x,SLong y,SLong z);
{
	SWord	retval;
    __asm
    {
		mov eax,x;
		mov ebx,y;
		mov ecx,z;
		mov	edx,eax;
		sar	edx,0x1F;
		xor	eax,edx;
		sub	eax,edx;
		mov	edx,ebx;
		sar	edx,0x1F;
		xor	ebx,edx;
		sub	ebx,edx;
		mov	edx,ecx;
		sar	edx,0x1F;
		xor	ecx,edx;
		sub	ecx,edx;
		or		eax,ebx;
		or		ecx,eax;
		bsr	eax,ecx;
		sub	eax,0x0E;
		jnc	short done;
		xor	eax,eax;
		done:;
		mov retval,ax;
    }
    return retval;
}

#endif
#endif

	SWord	ret_val;

	ret_val = GetScale(x,y,z);

	if(ret_val!=0)
	{
		x>>=ret_val;

		y>>=ret_val;

		z>>=ret_val;
	}

	return(ret_val);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Body2Screen
//Author		Paul.   
//Date			Mon 25 Sep 1995
//
//Description	Transform from body coordinate system to screen 
//				coordinate system
//
//Inputs		
//
//Returns		FALSE if the body Z for the point was negative.
//
//------------------------------------------------------------------------------
void matrix::body2screen(DoPointStruc &dopoint)					//PD 25Jul96
{
	if (mat_win->DoingHardware3D())
	{
		Float scalex,scaley;
		scalex=Float(mat_win->VirtualWidth)/Float(mat_win->PhysicalWidth);
		scaley=Float(mat_win->VirtualHeight)/Float(mat_win->PhysicalHeight);
		mat_win->DoBody2Screen(dopoint);
		dopoint.screenx.f*=scalex;
		dopoint.screeny.f*=scaley;
	}
	else
	{
		R3DVALUE rw=R3DVALUE(1./(POLYGON.viewdata.hoD*dopoint.bodyz.f));	
		dopoint.screenx.f=R3DVALUE(POLYGON.viewdata.scalex*dopoint.bodyx.f*rw+POLYGON.viewdata.originx);
		dopoint.screeny.f=R3DVALUE(-POLYGON.viewdata.scaley*dopoint.bodyy.f*rw+POLYGON.viewdata.originy);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		body2screen
//Author		Paul.   
//Date			Thu 23 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*DEAD void matrix::body2screen(landvertex& lvert)						//PD 25Jul96
{
	if (mat_win->DoingHardware3D())
	{
		DoPointStruc temp;
		temp.bodyx.f=lvert.bodyx.f;
		temp.bodyy.f=lvert.bodyy.f;
		temp.bodyz.f=lvert.bodyz.f;
		Float scalex,scaley;
		scalex=Float(mat_win->VirtualWidth)/Float(mat_win->PhysicalWidth);
		scaley=Float(mat_win->VirtualHeight)/Float(mat_win->PhysicalHeight);
		mat_win->DoBody2Screen(temp);
		temp.screenx.f*=scalex;
		temp.screeny.f*=scaley;
		lvert.sx.f=temp.screenx.f;
		lvert.sy.f=temp.screeny.f;
	}
	else
	{
		DoPointStruc temp;
		temp.bodyx.f=lvert.bodyx.f;
		temp.bodyy.f=lvert.bodyy.f;
		temp.bodyz.f=lvert.bodyz.f;
		R3DVALUE rw=R3DVALUE(1./(POLYGON.viewdata.hoD*temp.bodyz.f));	
		temp.screenx.f=R3DVALUE(POLYGON.viewdata.scalex*temp.bodyx.f*rw+POLYGON.viewdata.originx);
		temp.screeny.f=R3DVALUE(-POLYGON.viewdata.scaley*temp.bodyy.f*rw+POLYGON.viewdata.originy);
		lvert.sx.f=temp.screenx.f;
		lvert.sy.f=temp.screeny.f;
	}
}
DEAD*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Body2Screen
//LastModified:	PD 04Jan96
//Author		Paul.   
//Date			Mon 25 Sep 1995
//
//Description	Transform from body coordinate system to screen 
//				coordinate system
//
//Inputs		
//
//Returns		FALSE if the body Z for the point was negative.
//
//------------------------------------------------------------------------------
void matrix::body2screen(VERTEX &vertex)						//PD 25Jul96
{
	if (mat_win->DoingHardware3D())
	{
		DoPointStruc temp;
		temp.bodyx.f=vertex.bx.f;
		temp.bodyy.f=vertex.by.f;
		temp.bodyz.f=vertex.bz.f;
		Float scalex,scaley;
		scalex=Float(mat_win->VirtualWidth)/Float(mat_win->PhysicalWidth);
		scaley=Float(mat_win->VirtualHeight)/Float(mat_win->PhysicalHeight);
		mat_win->DoBody2Screen(temp);
		temp.screenx.f*=scalex;
		temp.screeny.f*=scaley;
		vertex.sx.f=temp.screenx.f;
		vertex.sy.f=temp.screeny.f;
	}
	else
	{
		DoPointStruc dopoint;
		dopoint.bodyx.f=vertex.bx.f;
		dopoint.bodyy.f=vertex.by.f;
		dopoint.bodyz.f=vertex.bz.f;
		R3DVALUE rw=R3DVALUE(1./(POLYGON.viewdata.hoD*dopoint.bodyz.f));	
		dopoint.screenx.f=R3DVALUE(POLYGON.viewdata.scalex*dopoint.bodyx.f*rw+POLYGON.viewdata.originx);
		dopoint.screeny.f=R3DVALUE(-POLYGON.viewdata.scaley*dopoint.bodyy.f*rw+POLYGON.viewdata.originy);
		vertex.sx.f=dopoint.screenx.f;
		vertex.sy.f=dopoint.screeny.f;
	}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		crossproduct
//Author		Paul.   
//Date			Tue 17 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns		TRUE for clockwise, FALSE for anti-clockwise
//
//------------------------------------------------------------------------------
Bool matrix::crossproduct(DoPointStruc &v1,DoPointStruc &v2,DoPointStruc &v3)
{
	Float	y[3],x[3];

	x[0]=v1.bodyx.f/v1.bodyz.f;
	y[0]=v1.bodyy.f/v1.bodyz.f;

	x[1]=v2.bodyx.f/v2.bodyz.f;
	y[1]=v2.bodyy.f/v2.bodyz.f;

	x[2]=v3.bodyx.f/v3.bodyz.f;
	y[2]=v3.bodyy.f/v3.bodyz.f;

	Float y2y1=y[1]-y[0];
	Float x2x3=x[1]-x[2];

	Float temp=y2y1*x2x3;

	Float x2x1=x[1]-x[0];
	Float y2y3=y[1]-y[2];

	Float temp2=x2x1*y2y3;

	temp-=temp2;

	if (temp<=0.)
		return TRUE;

	return FALSE;
}

//Old_Code PD 28Oct98 {
//Old_Code PD 28Oct98 	IFShare	temp1,temp2;
//Old_Code PD 28Oct98 	IFShare	y2y1, x2x3, x2x1, y2y3;
//Old_Code PD 28Oct98 
//Old_Code PD 28Oct98 	Bool	retval;
//Old_Code PD 28Oct98 
//Old_Code PD 28Oct98 	y2y1.f = v2.screeny.f-v1.screeny.f;
//Old_Code PD 28Oct98 	x2x3.f = v2.screenx.f-v3.screenx.f;
//Old_Code PD 28Oct98 
//Old_Code PD 28Oct98 	temp1.f= y2y1.f*x2x3.f;
//Old_Code PD 28Oct98 
//Old_Code PD 28Oct98 	x2x1.f = v2.screenx.f-v1.screenx.f;
//Old_Code PD 28Oct98 	y2y3.f = v2.screeny.f-v3.screeny.f;
//Old_Code PD 28Oct98 
//Old_Code PD 28Oct98 	temp2.f= x2x1.f*y2y3.f;
//Old_Code PD 28Oct98 
//Old_Code PD 28Oct98 	temp1.f-=temp2.f;
//Old_Code PD 28Oct98 
//Old_Code PD 28Oct98 	if(temp1.f<(Float)0.0)
//Old_Code PD 28Oct98 		retval = FALSE;
//Old_Code PD 28Oct98 	else
//Old_Code PD 28Oct98 		retval = TRUE;
//Old_Code PD 28Oct98 
//Old_Code PD 28Oct98 	return(retval);
//Old_Code PD 28Oct98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		accuratecrossproduct
//Author		Paul.   
//Date			Wed 27 Nov 1996
//
//Description	Cross product test using body coordinates (not screen
//				coordinates). This means it can be used before zclipping
//				and should be more accurate.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool matrix::accuratecrossproduct(DoPointStruc &v1,DoPointStruc &v2,DoPointStruc &v3)
{
//TempCode PD 08Jan97 	//Make my two vectors
//TempCode PD 08Jan97 
//TempCode PD 08Jan97 	Float	vect0[2],vect1[2];
//TempCode PD 08Jan97 
//TempCode PD 08Jan97 	vect0[0] = v2.bodyx.f - v1.bodyx.f;
//TempCode PD 08Jan97 	vect0[1] = v2.bodyy.f - v1.bodyy.f;
//TempCode PD 08Jan97 
//TempCode PD 08Jan97 	vect1[0] = v2.bodyx.f - v3.bodyx.f;
//TempCode PD 08Jan97 	vect1[1] = v2.bodyy.f - v3.bodyy.f;
//TempCode PD 08Jan97 
//TempCode PD 08Jan97 	//Only interested in the sign of the
//TempCode PD 08Jan97 	//resulting Z component
//TempCode PD 08Jan97 
//TempCode PD 08Jan97 	return (ASMDoBigXProd(vect0[0],vect0[1],vect1[0],vect1[1]));

	//FIX ME!!!

	return(FALSE);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TransformAngles
//Author		Paul.   
//Date			Wed 3 Jul 1996
//
//Description	Given a set of angular deltas in an items coordinate system
//				determine the resultant angles in the world coordinate system
//
//Inputs		hdg, pitch, roll = items current h,p,r
//				deltahdg, deltapitch, deltaroll = requested angular changes
//						in the item coordinate system
//Returns		deltahdg, deltapitch, deltaroll = new values for
//
//------------------------------------------------------------------------------
void matrix::TransformAngles(	ANGLES thdg, ANGLES tpitch, ANGLES troll,
								ANGLES& dhdg, ANGLES& dpitch, ANGLES& droll)
{
	MATRIX	tma,tmb,tmc;										//PD 25Jul96

	MATRIX_PTR	mNegHdg =&tma;									//PD 25Jul96
	MATRIX_PTR	mTemp	=&tmb;									//PD 25Jul96
	MATRIX_PTR	mDelta 	=&tmc;									//PD 25Jul96

	ANGLES	a,b,c;
	ANGLES	cdhdg,cdpitch,cdroll;
	SLong	x, y, z;

	a = dpitch; b = dhdg; c = droll;

	generate2(b,a,c,mDelta);			//PD 25Jul96
	generate2(thdg,tpitch,troll,mTemp);							//PD 25Jul96
	multiply(mDelta,mTemp);

	x = 0; y = 0; z = 0x7FFF;

	rotate(mDelta,x,y,z);

	cdhdg = Math_Lib.HighArcTan((SWord )x,(SWord )z);

	generateh((Angles)(0-cdhdg), mNegHdg);
	rotate(mNegHdg,x,y,z);

	cdpitch = Math_Lib.HighArcTan((SWord )y,(SWord )z);

	x = 0; y = 0x7FFF; z = 0;

	rotate(mDelta,x,y,z);
	rotate(mNegHdg,x,y,z);
	generatep((Angles)(0-cdpitch), mTemp);
	rotate(mTemp,x,y,z);

	cdroll = Math_Lib.HighArcTan((SWord )x,(SWord )y);

	dpitch = cdpitch; dhdg = cdhdg; droll = cdroll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TransformAngles
//Author		Paul.   
//Date			Wed 3 Jul 1996
//
//Description	Given a set of angular deltas in an items coordinate system
//				determine the resultant angles in the world coordinate system
//
//Inputs		hdg, pitch, roll = items current h,p,r
//				deltahdg, deltapitch, deltaroll = requested angular changes
//						in the item coordinate system
//Returns		deltahdg, deltapitch, deltaroll = new values for
//
//------------------------------------------------------------------------------
void matrix::ViewAnglesTransform(	ANGLES thdg, ANGLES tpitch, ANGLES troll,
									ANGLES reqhdg, ANGLES reqpitch,
									ANGLES& dhdg, ANGLES& dpitch, ANGLES& droll)
{
	MATRIX	tma,tmb,tmc;										//PD 25Jul96

	MATRIX_PTR	mNegHdg =&tma;									//PD 25Jul96
	MATRIX_PTR	mTemp	=&tmb;									//PD 25Jul96
	MATRIX_PTR	mDelta 	=&tmc;									//PD 25Jul96

	ANGLES	a,b,c;
	ANGLES	cdhdg,cdpitch,cdroll;
	SLong	x, y, z;

	a = dpitch; b = dhdg; c = droll;

	generate2(b,a,c,mDelta);			//PD 25Jul96
	generate2(thdg,tpitch,troll,mTemp);							//PD 25Jul96
	multiply(mDelta,mTemp);

	cdhdg = reqhdg;
	cdpitch = reqpitch;

	x = 0; y = 0x7FFF; z = 0;

	generateh((Angles)(0-cdhdg), mNegHdg);
	rotate(mDelta,x,y,z);
	rotate(mNegHdg,x,y,z);
	generatep((Angles)(0-cdpitch), mTemp);
	rotate(mTemp,x,y,z);
	cdroll = Math_Lib.HighArcTan((SWord )x,(SWord )y);
	dhdg = reqhdg;
	dpitch = reqpitch;
	droll = cdroll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TransformAnglesB
//Author		Paul.   
//Date			Thu 4 Jul 1996
//
//Description	
//
//Inputs		thdg, tpitch, troll = items current hdg,pitch,roll
//				dhdg, dpitch  		= requested new hdg, pitch in world
//									  coordinate system
//
//Returns		
//
//------------------------------------------------------------------------------
void matrix::TransformAnglesB(	SLong	x, SLong y, SLong z,
							  	ANGLES& itemhdg,
								ANGLES& itempitch,
								ANGLES& itemroll,
								ANGLES&	relhdg,
								ANGLES&	relpitch)
{
	ANGLES	cdhdg,cdpitch,cdroll;

	MATRIX	tma,tmb,tmc,tmd,tme;								//PD 03Sep96

	MATRIX_PTR	mHdg,mPitch,mRoll,mNegHdg,mNegPitch;			//PD 03Sep96

	mHdg = &tma; mPitch = &tmb; mRoll = &tmc; mNegHdg = &tmd;

	mNegPitch = &tme;											//PD 03Sep96

	generateh((Angles )(0-itemhdg),mHdg);
	generatep((Angles )(0-itempitch),mPitch);
	generater((Angles )(0-itemroll),mRoll);

	(void )scaleto16bit(x,y,z);

	rotate(mRoll, x,y,z);
	rotate(mPitch, x,y,z);
	rotate(mHdg, x,y,z);

	x>>=1; y>>=1; z>>=1;										//PD 03Sep96

	cdhdg = Math_Lib.HighArcTan((SWord )x,(SWord )z);

	generateh((Angles )(0-cdhdg),mNegHdg);
	rotate(mNegHdg, x,y,z);

	x>>=1; y>>=1; z>>=1;										//PD 03Sep96

	cdpitch = Math_Lib.HighArcTan((SWord )y,(SWord )z);

	generatep((Angles )(0-cdpitch),mNegPitch);						//PD 03Sep96
	rotate(mNegPitch,x,y,z);									//PD 03Sep96
	x>>=1; y>>=1; z>>=1;										//PD 03Sep96
	cdroll = Math_Lib.HighArcTan((SWord )x,(SWord )y);			//PD 03Sep96

	relhdg = cdhdg; relpitch = cdpitch;

	TransformAngles(itemhdg,itempitch,itemroll,
					cdhdg,cdpitch,cdroll);

	itemhdg 	= cdhdg;
	itempitch 	= cdpitch;
	itemroll 	= cdroll;
}

extern SWord winmode_w,winmode_h;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetZScale
//Author		Paul.   
//Date			Thu 25 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::SetZScale(Window *screen)
{
	fpzscale=(Float)FULLW/2;
	fpxscale=Float(winmode_w>>1);
	fpyscale=Float(winmode_h>>1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		generate
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
void matrix::generate(ANGLES heading, ANGLES pitch, ANGLES roll, FPMATRIX_PTR matrix)
{
	Float	sh,sp,sr,ch,cp,cr;

	fpSin_Cos(heading,	sh,	ch);
	fpSin_Cos(pitch,	sp,	cp);
	fpSin_Cos(roll,		sr,	cr);

	Float	sr_sh,sr_ch,cr_sh,cr_ch;

	sr_sh = sr * sh;
	sr_ch = sr * ch;
	cr_sh = cr * sh;
	cr_ch = cr * ch;

	matrix->L11 = cr_ch - (sp * sr_sh);
	matrix->L21 = -(sr_ch + (sp * cr_sh));
	matrix->L31 = -(cp * sh);

	matrix->L12 = sr * cp;
	matrix->L22 = cp * cr;
	matrix->L32 = -sp;

	matrix->L13 = (sp * sr_ch) + cr_sh;
	matrix->L23 = (sp * cr_ch) - sr_sh;
	matrix->L33 = cp * ch;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		generate2
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
void matrix::generate2(ANGLES heading, ANGLES pitch, ANGLES roll, FPMATRIX_PTR matrix)
{
	Float	sh,sp,sr,ch,cp,cr;

	Float	sp_sh,sr_ch,sp_ch,ch_cr;

	fpSin_Cos(heading,	sh,	ch);
	fpSin_Cos(pitch,	sp,	cp);
	fpSin_Cos(roll,		sr,	cr);

	sp_sh = sp * sh;
	sr_ch = sr * ch;
	sp_ch = sp * ch;
	ch_cr = ch * cr;

	matrix->L11 = ch_cr + (sp_sh * sr);
	matrix->L12 = sr_ch - (sp_sh * cr);
	matrix->L13 = cp * sh;

	matrix->L21 = -(sr *cp);
	matrix->L22 = cp * cr;
	matrix->L23 = sp;

	matrix->L31 = (sp * sr_ch) - (sh * cr);
	matrix->L32 = -((cr * sp_ch) + (sh * sr));
	matrix->L33 = cp * ch;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		inverse
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
void matrix::inverse(ANGLES heading, ANGLES pitch, ANGLES roll, FPMATRIX_PTR matrix)
{
	Float	sh,sp,sr,ch,cp,cr;

	Float	cr_ch,sr_sp,cr_sp,temp;

	//Get the sines/cosines of these angles

	fpSin_Cos(heading,	sh,	ch);
	fpSin_Cos(pitch,	sp,	cp);
	fpSin_Cos(roll,		sr,	cr);

	//Generate some intermediate values

	cr_ch = cr * ch;
	sr_sp = sr * sp;
	cr_sp = cr * sp;

	//Fill in the new matrix

	matrix->L11	=	cr_ch - (sr_sp * sh);
	matrix->L21	=	sr * cp;
	matrix->L31	=	(sr_sp * ch) + (cr * sh);

	matrix->L12	=	-(sr * ch) - (cr_sp * sh);
	matrix->L22	=	cr * cp;
	matrix->L32	=	(cr_ch * sp) - (sr * sh);

	matrix->L13	=	-(cp * sh);
	matrix->L23	=	-sp;
	matrix->L33	=	cp * ch;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getxdeltas
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
void matrix::getxdeltas(FPMATRIX_PTR T, IFShare& x, IFShare& y, IFShare& z)
{
	x.f = T->L11;
	y.f = T->L21;
	z.f = T->L31;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getzdeltas
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
void matrix::getzdeltas(FPMATRIX_PTR T, IFShare& x, IFShare& y, IFShare& z)
{
	x.f = T->L13;
	y.f = T->L23;
	z.f = T->L33;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		transform
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
UWord matrix::transform(FPMATRIX_PTR T, IFShare& x, IFShare& y, IFShare& z)
{
	Float	fx = (Float)x.i,
			fy = (Float)y.i,
			fz = (Float)z.i;

	x.f = (T->L11 * fx) + (T->L12 * fy) + (T->L13 * fz);
	y.f = (T->L21 * fx) + (T->L22 * fy) + (T->L23 * fz);
	z.f = (T->L31 * fx) + (T->L32 * fy) + (T->L33 * fz);

	//Now generates clip flags based 
	//on the current view cone

	UWord retval;
	_clipFB(retval,z.f,1.,fpMaximumZ);
	_clipLR(retval,x.f,z.f);
	_clipTB(retval,y.f,z.f);
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		transformNC
//Author		Paul.   
//Date			Fri 24 Apr 1998
//------------------------------------------------------------------------------
UWord matrix::transformNC(FPMATRIX_PTR T, IFShare& x, IFShare& y, IFShare& z)
{
	Float	fx = (Float)x.i,
			fy = (Float)y.i,
			fz = (Float)z.i;

	x.f = (T->L11 * fx);
	x.f += (T->L12 * fy);
	x.f += (T->L13 * fz);

	y.f = (T->L21 * fx);
	y.f += (T->L22 * fy);
	y.f += (T->L23 * fz);

	z.f = (T->L31 * fx);
	z.f += (T->L32 * fy);
	z.f += (T->L33 * fz);

	return CF3D_NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		transform
//Author		Jim Taylor
//Date			Wed 4 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::transform(FPMATRIX_PTR T, DoPointStruc& dp)
{
	Float	fx = Float(dp.bodyx.i),
			fy = Float(dp.bodyy.i),
			fz = Float(dp.bodyz.i);
	dp.bodyx.f = (T->L11 * fx) + (T->L12 * fy) + (T->L13 * fz);
	dp.bodyy.f = (T->L21 * fx) + (T->L22 * fy) + (T->L23 * fz);
	dp.bodyz.f = (T->L31 * fx) + (T->L32 * fy) + (T->L33 * fz);

	//Now generates clip flags based 
	//on the current view cone

	SetClipFlags(dp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		transformNC
//Author		Paul.   
//Date			Fri 24 Apr 1998
//------------------------------------------------------------------------------
/*inline void matrix::transformNC(FPMATRIX_PTR T, DoPointStruc* dp)
{
	double f[3];
	double* mp=(double*)T;
	f[0]=double(dp->bodyx.i);
	f[1]=double(dp->bodyy.i);
	f[2]=double(dp->bodyz.i);
	dp->bodyx.f=f[0]*mp[0]+f[1]*mp[1]+f[2]*mp[2];
	dp->bodyy.f=f[0]*mp[3]+f[1]*mp[4]+f[2]*mp[5];
	dp->bodyz.f=f[0]*mp[6]+f[1]*mp[7]+f[2]*mp[8];
	dp->clipFlags=CF3D_NULL;
}*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		transform
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
UWord matrix::fptrans(FPMATRIX_PTR T, IFShare& x, IFShare& y, IFShare& z)
{
	Float	fx = x.f,
			fy = y.f,
			fz = z.f;
	x.f = (T->L11 * fx) + (T->L12 * fy) + (T->L13 * fz);
	y.f = (T->L21 * fx) + (T->L22 * fy) + (T->L23 * fz);
	z.f = (T->L31 * fx) + (T->L32 * fy) + (T->L33 * fz);

	//Now generates clip flags based 
	//on the current view cone

	UWord retval;
	_clipFB(retval,z.f,1.,fpMaximumZ);

	_clipLR(retval,x.f,z.f);
	_clipTB(retval,y.f,z.f);
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		transform_y
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
void matrix::transform_y(FPMATRIX_PTR T, SLong y,
						IFShare& rtx, IFShare& rty, IFShare& rtz)
{
	Float	fy = (Float)y;
	rtx.f = fy * T->L12;
	rty.f = fy * T->L22;
	rtz.f = fy * T->L32;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		multiply
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
void matrix::multiply(FPMATRIX_PTR t, FPMATRIX_PTR sip)
{
	FPMATRIX		tmat;
	FPMATRIX_PTR	dip = &tmat;

	Float	*si,*di;

	int	j;

	si = &sip->L11;
	di = &dip->L11;

	for(j=0;j<3;j++)
	{
		*di++	= (*si * t->L11)
				+ (*(si+1) * t->L21)
				+ (*(si+2) * t->L31);

		*di++ 	= (*si * t->L12)
				+ (*(si+1) * t->L22)
				+ (*(si+2) * t->L32);

		*di++ 	= (*si * t->L13)
				+ (*(si+1) * t->L23)
				+ (*(si+2) * t->L33);

		si += 3;
	}

	//copy the new matrix back to sip

	*t = *dip;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetViewParams
//Author		Paul.   
//Date			Mon 2 Feb 1998
//
//Description	
//
//Inputs		view cone angle + distance to back clipping plane in cm	
//
//------------------------------------------------------------------------------
void matrix::SetViewParams(Window* win,ANGLES viewCone,SLong viewRange)
{
	//Clip the view cone to min/max
	if (viewCone<ANGLES_40Deg)		viewCone=ANGLES_40Deg;
	else if (viewCone>ANGLES_90Deg)	viewCone=ANGLES_90Deg;

	viewConeAngle=Angles(UWord(viewCone)>>1);
	fpTan(viewConeAngle,FoV);

	aspectRatio=Float(win->VirtualHeight)/Float(win->VirtualWidth);
	aspectRatio*=FoV;

 	fpMaximumZ=Float(viewRange);

	win->DoSetAspectRatio(aspectRatio,FoV);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		generateh
//Author		Paul.   
//Date			Mon 24 Aug 1998
//------------------------------------------------------------------------------
void matrix::generateh(ANGLES hdg,FPMATRIX& m)
{
	Float sin_hdg,cos_hdg;
	fpSin_Cos(hdg,sin_hdg,cos_hdg);
	m.L11=m.L33=cos_hdg;
	m.L31=-sin_hdg;
	m.L13=sin_hdg;
	m.L21=m.L12=m.L32=m.L23=0.0;
	m.L22=1.0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		generatep
//Author		Paul.   
//Date			Mon 24 Aug 1998
//------------------------------------------------------------------------------
void matrix::generatep(ANGLES pitch, FPMATRIX& m)
{
	Float sin_pitch,cos_pitch;
	pitch=ANGLES_0Deg-pitch;
	fpSin_Cos(pitch,sin_pitch,cos_pitch);
	m.L11=1.0;
	m.L21=m.L31=m.L12=m.L13=0.0;
	m.L22=m.L33=cos_pitch;
	m.L32=sin_pitch;
	m.L23=-sin_pitch;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		generater
//Author		Paul.   
//Date			Mon 24 Aug 1998
//------------------------------------------------------------------------------
void matrix::generater(ANGLES roll,FPMATRIX& m)
{
	Float sin_roll,cos_roll;
	roll=ANGLES_0Deg-roll;
	fpSin_Cos(roll,sin_roll,cos_roll);
	m.L11=m.L22=cos_roll;
	m.L21=sin_roll;
	m.L12=-sin_roll;
	m.L31=m.L32=m.L13=m.L23=0.0;
	m.L33=1.0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		inverseMobileMatrix
//Author		Paul.   
//Date			Mon 24 Aug 1998
//------------------------------------------------------------------------------
void matrix::inverseMobileMatrix(ANGLES hdg,ANGLES pitch,ANGLES roll,FPMATRIX& m)
{
	FPMATRIX h,p,r;

	hdg=ANGLES_0Deg-hdg;
	pitch=ANGLES_0Deg-pitch;
	roll=ANGLES_0Deg-roll;

	generateh(hdg,h);
	generatep(pitch,p);
	generater(roll,r);

	m=h;
	multiply(&m,&p);
	multiply(&m,&r);

//	m=r;
//	multiply(&m,&p);
//	multiply(&m,&h);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Generate
//Author		Paul.   
//Date			Mon 12 Oct 1998
//------------------------------------------------------------------------------
void matrix::Generate(ANGLES heading,ANGLES pitch,ANGLES roll,FPMATRIX* matrix)
{
	Float	sh,sp,sr,ch,cp,cr;

	fpSin_Cos(heading,	sh,	ch);
	fpSin_Cos(pitch,	sp,	cp);
	fpSin_Cos(roll,		sr,	cr);

	Float	sr_sh,sr_ch,cr_sh,cr_ch;

	sr_sh = sr * sh;
	sr_ch = sr * ch;
	cr_sh = cr * sh;
	cr_ch = cr * ch;

	matrix->L11 = cr_ch - (sp * sr_sh);
	matrix->L21 = -(sr_ch + (sp * cr_sh));
	matrix->L31 = -(cp * sh);

	matrix->L12 = sr * cp;
	matrix->L22 = cp * cr;
	matrix->L32 = -sp;

	matrix->L13 = (sp * sr_ch) + cr_sh;
	matrix->L23 = (sp * cr_ch) - sr_sh;
	matrix->L33 = cp * ch;

	FPMATRIX viewMat;

	viewMat.L11=1./FoV;
	viewMat.L21=0.;
	viewMat.L31=0.;

	viewMat.L12=0.;
	viewMat.L22=1./aspectRatio;
	viewMat.L32=0.;

	viewMat.L13=0.;
	viewMat.L23=0.;
	viewMat.L33=1.;

	multiply(matrix,&viewMat);
}

void matrix::GenerateV(ANGLES heading,ANGLES pitch,ANGLES roll,FPMATRIX* matrix)
{
	Float	sh,sp,sr,ch,cp,cr;

	fpSin_Cos(heading,	sh,	ch);
	fpSin_Cos(pitch,	sp,	cp);
	fpSin_Cos(roll,		sr,	cr);

	Float	sr_sh,sr_ch,cr_sh,cr_ch;

	sr_sh = sr * sh;
	sr_ch = sr * ch;
	cr_sh = cr * sh;
	cr_ch = cr * ch;

	matrix->L11 = cr_ch - (sp * sr_sh);
	matrix->L21 = -(sr_ch + (sp * cr_sh));
	matrix->L31 = -(cp * sh);

	matrix->L12 = sr * cp;
	matrix->L22 = cp * cr;
	matrix->L32 = -sp;

	matrix->L13 = (sp * sr_ch) + cr_sh;
	matrix->L23 = (sp * cr_ch) - sr_sh;
	matrix->L33 = cp * ch;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Generate2
//Author		Paul.   
//Date			Mon 12 Oct 1998
//------------------------------------------------------------------------------
void matrix::Generate2(	ANGLES heading,ANGLES pitch,ANGLES roll,
						Float scale,
						FPMATRIX* mp)
	{
	Float* matrix=(Float*)mp;
	Float sh,sp,sr,ch,cp,cr;
	Float sp_sh,sr_ch,sp_ch,ch_cr;

	fpSin_Cos(heading,sh,ch);
	fpSin_Cos(pitch,sp,cp);
	fpSin_Cos(roll,sr,cr);

	sp_sh=sp*sh;
	sr_ch=sr*ch;
	sp_ch=sp*ch;
	ch_cr=ch*cr;

	Float temp=Float(scale);
	matrix[0]=(ch_cr+(sp_sh*sr))*temp;
	matrix[1]=(sr_ch-(sp_sh*cr))*temp;
	matrix[2]=cp*sh*temp;

	matrix[3]=-sr*cp*temp;
	matrix[4]=cp*cr*temp;
	matrix[5]=sp*temp;

	matrix[6]=((sp*sr_ch)-(sh*cr))*temp;
	matrix[7]=-((cr*sp_ch)+(sh*sr))*temp;
	matrix[8]=cp*ch*temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateXY
//Author		Robert Slater
//Date			Wed 2 Dec 1998
//
//Description	For spheres and cylinders.......
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::GenerateXY(Float	&xscale,Float	&yscale)
{
	xscale = 1./FoV;
	yscale = 1./aspectRatio;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateRadar
//Author		Robert Slater
//Date			Fri 14 May 1999
//
//Description	Generates a 20 degree viewcone for radar locking
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void matrix::GenerateRadar(ANGLES heading,ANGLES pitch,ANGLES roll,FPMATRIX* matrix)
{
	Float	sh,sp,sr,ch,cp,cr;

	fpSin_Cos(-heading,	sh,	ch);
	fpSin_Cos(-pitch,	sp,	cp);
	fpSin_Cos(-roll,		sr,	cr);

	Float	sr_sh,sr_ch,cr_sh,cr_ch;

	sr_sh = sr * sh;
	sr_ch = sr * ch;
	cr_sh = cr * sh;
	cr_ch = cr * ch;

	matrix->L11 = cr_ch - (sp * sr_sh);
	matrix->L21 = -(sr_ch + (sp * cr_sh));
	matrix->L31 = -(cp * sh);

	matrix->L12 = sr * cp;
	matrix->L22 = cp * cr;
	matrix->L32 = -sp;

	matrix->L13 = (sp * sr_ch) + cr_sh;
	matrix->L23 = (sp * cr_ch) - sr_sh;
	matrix->L33 = cp * ch;

	FPMATRIX viewMat;

	Float	MYFoV;

	fpTan(ANGLES_10Deg,MYFoV);

	viewMat.L11=1./MYFoV;
	viewMat.L21=0.;
	viewMat.L31=0.;

	viewMat.L12=0.;
	viewMat.L22=1./MYFoV;
	viewMat.L32=0.;

	viewMat.L13=0.;
	viewMat.L23=0.;
	viewMat.L33=1.;

	multiply(matrix,&viewMat);
}

void matrix::PushViewData()
{
}
void matrix::PopViewData()
{
}
void matrix::Set3DWin(SLong x,SLong y,SLong w,SLong h)
{
}
