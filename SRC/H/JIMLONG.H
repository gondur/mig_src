//------------------------------------------------------------------------------
//Filename       jimlong.h
//System         
//Author         Jim Taylor
//Date           Fri 23 Aug 1996
//Description    my attempt at a fully optimised long number class
//------------------------------------------------------------------------------
#ifndef	JIMLONG_Included
#define	JIMLONG_Included

#define	DEFAULT_JIMLONG 0
typedef	unsigned long	ULong;
typedef	signed long		SLong;

//DeadCode JIM 23Aug96 class	XWord;
//DeadCode JIM 23Aug96 class	XWord::fake;

	struct	fake;
	typedef	fake	__FAR & Xref;
	typedef	fake	__FAR * Xptr;

	struct	fake
	{
		Xref operator - (Xref f2);
		Xref operator * (Xref f2);
		Xref operator % (Xref f2);
	};

#ifdef __WATCOMC__
	#pragma	aux fake_add	=	"mov eax,esi" "mov edx,edi" "add eax,ebx" "adc edx,ecx" parm	[di esi] [cx ebx] modify exact value [dx eax] 										
	Xref	__pragma ("fake_add") operator + (const Xref f1,const Xref f2) ;
#else
#ifdef __MSVC__
	Xref operator + (const Xref f1,const Xref f2)
	{
		fake retval;
		__asm
		{
			int 3;
		}
		return retval;
	}
#endif
#endif

#ifdef __WATCOMC__
	#pragma	aux fake_min	=	"mov eax,esi" "mov edx,edi" "sub eax,ebx" "sbb edx,ecx" parm	[di esi] [cx ebx] modify exact value [dx eax] 										
	Xref	__pragma ("fake_min") operator - (const Xref f1,const Xref f2) ;
#else
#ifdef __MSVC__
	Xref operator - (const Xref f1, const Xref f2)
	{
		fake retval;
		__asm
		{
			int 3;
		}
		return retval;
	}
#endif
#endif
	//
	//		di		si
	//		cx		bx
	//		sibxH	sibxL
	//  	bxdi
	//		cxsi
	//
#ifdef	__WATCOMC__
	#pragma	aux fake_mul	=								\
			"mov		eax,esi	"							\
			"mul		ebx		"							\
			"imul	edi,ebx		"							\
			"add		edx,edi	"							\
			"mov		edi,ecx	"							\
			"imul	edi,esi		"							\
			"add		edx,edi	"							\
		parm	[di esi] [cx ebx] modify exact [edi] value [dx eax]
	Xref	__pragma ("fake_mul") operator * (const Xref f1,const Xref f2) ;
#else
#ifdef	__MSVC__
	Xref operator * (const Xref f1,const Xref f2)
	{
		fake retval;
		__asm
		{
			int 3;
		}
		return retval;
	}
#endif
#endif



	//	Result is approximate..
	//	shift divisor down until 31 bit
	//
	//	If divisor is signed then flip both 
	//
	//	If dividend signed then flip - push signedness
	//
	//	If divisor>16 bit
	//		bsr to get shift required
	//	
	//	If divisor low*2< dividend high skip out with 32767 result
	//
	//	Perform division 63/31
	//skip:
	//	
	//	pop	sign and reapply
	//
	//
	//
#ifdef	__WATCOMC__
	#pragma	aux	fake_div	=								\
"			mov	eax,edi				"						\
"			cdq						"						\
"			xor	esi,edx				"						\
"			xor	edi,edx				"						\
"			sub	esi,edx				"						\
"			sbb	edi,edx				"						\
"			xor	ebx,edx				"						\
"			xor	ecx,edx				"						\
"			sub	ebx,edx				"						\
"			sbb	ecx,edx				"						\
"			mov	eax,ebx				"						\
"			cdq						"						\
"			push	edx				"						\
"			xor	ebx,edx				"						\
"			xor	ecx,edx				"						\
"			sub	ebx,edx				"						\
"			sbb	ecx,edx				"						\
"absolute:							"						\
"			xchg	eax,ecx			"						\
"			bsf		ecx,eax			"						\
"			jz	norot				"						\
"			shrd	ebx,eax,cl		"						\
"			shrd	esi,edi,cl		"						\
"			shr		edi,cl			"						\
"norot:								"						\
"			mov		eax,65535		"						\
"			mov		edx,edi			"						\
"			cmp		ebx,edi			"						\
"			jbe		nodiv			"						\
"			mov		eax,esi			"						\
"			div		ebx				"						\
"nodiv:								"						\
"			pop		edx				"						\
"			xor		eax,edx			"						\
"			sub		eax,edx			"						\
			\
		parm	[di esi] [cx ebx] value [dx eax]
	Xref	__pragma ("fake_div") operator / (const Xref f1,const Xref f2) ;
#else
#ifdef	__MSVC__
	Xref operator / (const Xref f1, const Xref f2)
	{
		fake retval;
		__asm 
		{
			int 3;
		}
		return retval;
	}
#endif
#endif


#ifdef	__WATCOMC__
			extern	Xref fake_long(ULong,SLong);
			#pragma aux fake_long	=	parm	[eax][edx]	value	[dx eax]
			extern	SLong fake_equh(Xref);
			#pragma	aux fake_equh	=	parm	[dx eax] value	[edx]
			extern	ULong fake_equl(Xref);
			#pragma	aux fake_equl	=	parm	[dx eax] value	[eax]

			extern	SLong	fake_sign(SLong);
			#pragma	aux fake_sign	=	"cdq"	parm	[eax] modify exact	value	[edx]
#else
#ifdef __MSVC__
			extern	Xref fake_long(ULong,SLong);
			extern	SLong fake_equh(Xref);
			extern	ULong fake_equl(Xref);
			extern	SLong	fake_sign(SLong);
#endif
#endif


class	XWord
{
public:
	ULong	low;
	SLong	high;

public:

		XWord()	{low=high=0;}
		XWord(SLong l) {low=l;high=fake_sign(l);}
		XWord(ULong l) {low=l;high=0;}
		XWord(SLong h,ULong l) {low=l;high=h;}

#ifdef __WATCOMC__
		operator	Xref ()
		{	Xptr rv=((__segment)high):>((fake*)low);return(*rv);}
#endif

		Xref	operator = (Xref x)
		{
			low=fake_equl(x);
			high=fake_equh(x);
			return(x);
		}

};


//TempCode PD 06Sep96 XWord main(XWord & a)
//TempCode PD 06Sep96 {
//TempCode PD 06Sep96 	XWord	b(0x9abcdef0,0x12345678);
//TempCode PD 06Sep96 	XWord	c;
//TempCode PD 06Sep96 	c=a+b;
//TempCode PD 06Sep96 	a=b-c;
//TempCode PD 06Sep96 	b=c*a;
//TempCode PD 06Sep96 	return(b);
//TempCode PD 06Sep96 }


#endif
