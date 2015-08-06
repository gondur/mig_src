//------------------------------------------------------------------------------
//Filename       hardpasm.h
//System         
//Author         Jim Taylor
//Date           Mon 6 Nov 1995
//Description    Replacement for some of trivial functions in hardpasm.asm
//					by using #pragma aux
//------------------------------------------------------------------------------
#ifndef	HARDPASM_Included
#define	HARDPASM_Included

#define	DEFAULT_HARDPASM 0

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//ASM_OutDxAx
//------------------------------------------------------------------------------
//Author	Jim Taylor
//Date		Mon 6 Nov 1995
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

#ifdef __WATCOMC__
extern	void	ASM_OutDxAx(UWord,UWord);
#pragma	aux	ASM_OutDxAx	=		\
		"out dx,ax"				\
		parm	[dx]	[ax]
#else
#ifdef __MSVC__
inline void	ASM_OutDxAx(UWord num1,UWord num2)
{
	__asm
	{
		mov dx,num1;
		mov ax,num2;
		out dx,ax;
	}
}
#endif
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//	ASM_OutDxAl
//------------------------------------------------------------------------------
//Author	Jim Taylor
//Date		Mon 6 Nov 1995
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
#ifdef __WATCOMC__
extern	void	ASM_OutDxAl(UWord,UByte);
#pragma	aux	ASM_OutDxAl	=		\
		"out dx,al"				\
		parm	[dx]	[al]
#else
#ifdef __MSVC__
inline void ASM_OutDxAl(UWord num1,UByte num2)
{
	__asm
	{
		mov dx,num1;
		mov al,num2;
		out dx,al;
	}
}
#endif
#endif


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//	ASM_OutLoop
//------------------------------------------------------------------------------
//Author	Jim Taylor
//Date		Mon 6 Nov 1995
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
#ifdef __WATCOMC__
extern	void	ASM_OutSB(UWord,void *,UWord);					//ARM 24Jun96
#pragma	aux	ASM_OutSB	=		\
		"here:"					\
		"lodsb"					\
		"shr	al,2"			\
		"out dx,al"				\
		"loop here"				\
		parm	[dx] [esi]	[cx]
#else
#ifdef __MSVC__
inline void ASM_OutSB(UWord num1, void * num2, UWord num3)
{
	__asm
	{
		mov dx,num1;
		mov esi,num2;
		mov cx,num3;
		here:;
		lodsb;
		shr	al,2;
		out dx,al;
		loop here;
	}
}
#endif
#endif


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//	ASM_InDxAl
//------------------------------------------------------------------------------
//Author	Jim Taylor
//Date		Mon 6 Nov 1995
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
#ifdef __WATCOMC__
extern	UByte	ASM_InDxAl(UWord);
#pragma	aux	ASM_InDxAl	=		\
		"in		al,dx"			\
		parm	[dx]			\
		value	[al]
#else
#ifdef __MSVC__
inline UByte ASM_InDxAl(UWord num)
{
	UByte retval;
	__asm
	{
		mov dx,num;
		in al,dx;
		mov retval,al;
	}
	return retval;
}
#endif
#endif


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//	ASM_TestVBL
//------------------------------------------------------------------------------
//Author	Jim Taylor
//Date		Mon 6 Nov 1995
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

#ifdef __WATCOMC__
extern	Bool	ASM_TestVBL(void);
#pragma	aux	ASM_TestVBL	=	\
		"mov	dx,03dah"	\
		"in		al,dx"		\
		"and	al,08h"		\
		value	[al]		\
		modify	[dx]
//
//AH = hbl
//AL = vbl
//
#else
#ifdef __MSVC__
inline Bool ASM_TestVBL(void)
{
	UByte retval;
	__asm
	{
		mov	dx,03dah;
		in		al,dx;
		and	al,08h;
		mov retval,al;
	}
	return (Bool)retval;
}
#endif
#endif

#ifdef __WATCOMC__
extern	UWord	ASM_TestHBL(void);
#pragma	aux	ASM_TestHBL	=	\
		"mov	dx,03dah"	\
		"in		al,dx"		\
		"shr	al,1"		\
		"sbb	ah,ah"		\
		"shr	al,3"		\
		"sbb	al,al"		\
		value	[ax]		\
		modify	[dx]
#else
#ifdef __MSVC__
inline UWord ASM_TestHBL(void)
{
	UWord retval;
	__asm
	{
		mov	dx,03dah;
		in		al,dx;
		shr	al,1;
		sbb	ah,ah;
		shr	al,3;
		sbb	al,al;
		mov retval,ax
	}
	return retval;
}
#endif
#endif

#ifdef __WATCOMC__
//------------------------------------------------------------------------------
extern	void	ASM_Blat(void*,void*,ULong);
//
// This blat attempts to get at least one register on a longword boundary.
// As it is often used for screen copying, I have chosen the target.
// This will reduce bus accesses a little.
//
#pragma	aux	ASM_Blat	=			\
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
		modify	[ecx]
#else
#ifdef __MSVC__
inline void ASM_Blat(void* num1,void* num2,ULong num3)
{
	__asm
	{
		mov esi,num1;
		mov edi,num2;
		mov ebx,num3;
		mov	ecx,4;
		sub	ecx,edi;
		and	ecx,3;
		sub	ebx,ecx;
		rep	movsb;
		mov	ecx,ebx;
		shr	ecx,2;
		rep	movsd;
		and	ebx,3;
		mov	ecx,ebx;
		rep	movsb;
	}
}
#endif
#endif

#ifdef __WATCOMC__
//------------------------------------------------------------------------------
extern	void	ASM_Splat(ULong,void*,ULong);
//
#pragma	aux	ASM_Splat	=			\
		"mov	ecx,4"				\
		"sub	ecx,edi"			\
		"and	ecx,3"				\
		"sub	ebx,ecx"			\
		"rep	stosb"				\
		"mov	ecx,ebx"			\
		"shr	ecx,2"				\
		"rep	stosd"				\
		"and	ebx,3"				\
		"mov	ecx,ebx"			\
		"rep	stosb"				\
		parm	[eax] [edi] [ebx]	\
		modify	[ecx]
#else
#ifdef __MSVC__
inline void ASM_Splat(ULong num1,void* num2,ULong num3)
{
	__asm
	{
		mov eax,num1;
		mov edi,num2;
		mov ebx,num3;
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
#endif
#endif

//------------------------------------------------------------------------------
struct	DPMIb
{
	ULong	edi;
	ULong	esi;
	ULong	ebp;
	ULong	esp;
	UByte	bl,bh,ebl,ebh;
	UByte	dl,dh,edl,edh;
	UByte	cl,ch,ecl,ech;
	UByte	al,ah,eal,eah;
};

struct	DPMIw
{
	UWord	di,exdi;
	UWord	si,exsi;
	UWord	bp,exbp;
	UWord	sp,exsp;
	UWord	bx,exbx;
	UWord	dx,exdx;
	UWord	cx,excx;
	UWord	ax,exax;
};

struct	DPMIl
{
	ULong	edi;
	ULong	esi;
	ULong	ebp;
	ULong	esp;
	ULong	ebx;
	ULong	edx;
	ULong	ecx;
	ULong	eax;
};

struct	DPMIsb
{
	SLong	edi;
	SLong	esi;
	SLong	ebp;
	SLong	esp;
	SByte	bl,bh,ebl,ebh;
	SByte	dl,dh,edl,edh;
	SByte	cl,ch,ecl,ech;
	SByte	al,ah,eal,eah;
};

struct	DPMIsw
{
	SWord	di,exdi;
	SWord	si,exsi;
	SWord	bp,exbp;
	SWord	sp,exsp;
	SWord	bx,exbx;
	SWord	dx,exdx;
	SWord	cx,excx;
	SWord	ax,exax;
};

struct	DPMIsl
{
	SLong	edi;	//0
	SLong	esi;	//4
	SLong	ebp;	//8
	SLong	esp;	//12
	SLong	ebx;	//16
	SLong	edx;	//20
	SLong	ecx;	//24
	SLong	eax;	//28
};


struct	Ubytereg
{
	UByte	l,h,hl,hh;
};
struct	Sbytereg
{
	SByte	l,h,hl,hh;
};

struct	DPMIseg
{
	UWord	es,ds,fs,gs,ip,cs,sp,ss;
};

struct	DPMIregs2
{
	union	{	ULong	edi;	SLong	Edi;	UWord	di;	SWord	Di;};
	union	{	ULong	esi;	SLong	Esi;	UWord	si;	SWord	Si;};
	union	{	ULong	ebp;	SLong	Ebp;	UWord	bp;	SWord	Bp;};
	union	{	ULong	esp2;	SLong	Esp2;	UWord	sp2;SWord	Sp2;};
	union	{	ULong	ebx;	SLong	Ebx;	UWord	bx;	SWord	Bx;	Ubytereg	b;	Sbytereg	B;};
	union	{	ULong	edx;	SLong	Edx;	UWord	dx;	SWord	Dx;	Ubytereg	d;	Sbytereg	D;};
	union	{	ULong	ecx;	SLong	Ecx;	UWord	cx;	SWord	Cx;	Ubytereg	c;	Sbytereg	C;};
	union	{	ULong	eax;	SLong	Eax;	UWord	ax;	SWord	Ax;	Ubytereg	a;	Sbytereg	A;};
	enum	Flags
		{
    		CF	= 0x0001,	/* carry */
    		PF	= 0x0004,	/* parity */
    		AF	= 0x0010,	/* auxiliary carry */
    		ZF	= 0x0040,	/* zero */
    		SF	= 0x0080,	/* sign */
    		TF	= 0x0100,	/* trace */
    		IF	= 0x0200,	/* interrupt */
    		DF	= 0x0400,	/* direction */
    		OF	= 0x0800,	/* overflow */
    		IOPL=0x3000,	/* overflow */
    		NT	= 0x4000	/* overflow */
		}	flags;
	UWord	es,ds,fs,gs,ip,cs,sp,ss;
};

struct	DPMIregs
{
	CON	DPMIregs()	{flags=CLEAR;}
	union	{	DPMIb	b;	DPMIsb	sb;
				DPMIw	w;	DPMIsw	sw;
			 	DPMIl	l;	DPMIsl	sl;
			};
	enum	Flags
		{
			CLEAR=0,
    		CF	= 0x0001,	/* carry */
    		PF	= 0x0004,	/* parity */
    		AF	= 0x0010,	/* auxiliary carry */
    		ZF	= 0x0040,	/* zero */
    		SF	= 0x0080,	/* sign */
    		TF	= 0x0100,	/* trace */
    		IF	= 0x0200,	/* interrupt */
    		DF	= 0x0400,	/* direction */
    		OF	= 0x0800,	/* overflow */
    		IOPL=0x3000,	/* overflow */
    		NT	= 0x4000,	/* overflow */
		}	flags;
	DPMIseg	s;
};

//DeadCode JIM 13Dec95 MATHABLE(DPMIregs::Flags);

#ifdef __WATCOMC__
extern	Bool	ASM_DOSvia31(	UWord	intnum,			//Interrupt number. add 256 for flags
								DPMIregs* registerimage,	
								void* 	stackspacebot=NULL,
								UWord 	stackspacesize=0,
								UWord	stackcopysize=0);
//
// THIS HAS NOW BEEN TESTED!!!!!!!								//JIM 22Feb96
//
// This routine will execute the given real-mode interrupt via dpmi31 fn300
// All the segment registers will be set to the stackspacebot value, 
// which **MUST** be on a paragraph boundary. (Not if stackspacebot=0)
// It is assumed that any data areas used for parameter passing have been 
// placed there already, and that the relevent offsets (bx,dx,si,di, or bp)
// have already been set up.
//
// First, convert stack ptr to segment
// Next, generate 0 in dx if segment non-zero
// Generate -1 if zero. This is to mask other segment registers
// 
//	Parameters to int31 fn 300:
//	AX=300h
//	BL=int num
//	BH=0
//	CX=param list copy size
//	es:edi=registers
//
// The CARRY flag is echoed on the return
//
//
//

#pragma aux		ASM_DOSvia31	=			\
		"mov	dx,ax"						\
		"and	dx,15"						\
		"add	bx,dx"						\
		"shr	eax,4"						\
		"mov	dx,ax"						\
		"sub	dx,1"						\
		"sbb	dx,dx"						\
											\
		"and	ds:[edi+22h],dx"			\
		"and	ds:[edi+24h],dx"			\
		"and	ds:[edi+26h],dx"			\
		"and	ds:[edi+28h],dx"			\
		"and	ds:[edi+2eh],dx"			\
		"and	ds:[edi+30h],dx"			\
		"not	dx"	  						\
		"and	si,dx"						\
		"and	dx,ax"						\
		"add	ds:[edi+22h],dx"			\
		"add	ds:[edi+24h],dx"			\
		"add	ds:[edi+26h],dx"			\
		"add	ds:[edi+28h],dx"			\
		"mov	ds:[edi+2eh],si"			\
		"mov	ds:[edi+30h],ax"			\
		 									\
		"mov	ax,300h"					\
		"int	31h"						\
		"sbb	al,al"						\
		"neg	al"							\
		parm	[bx] [edi] [eax] [si] [cx]	\
		modify	[dx]						\
		value	[al]

//
//		Cheep and cheerful DEX interrupt interfaces...
//		Return carry flag echo
//		Registers as in call above
//		These calls don't handle segment or stack registers.
//		Flags supported:
//			DF	0400H		--set first
//
//			CF	0001H		--can be complement of math result
//			SF	0080H
//			ZF	0040H
// 01 80 40
// CF SF ZF		Shift left op
// 0  0  0		20	0010
// 1  0  0		A0	1010
// 0  1  0		60	0110
// 1  1  0		E0	1110
// 0  0  1		00	0000
// 1  0  1		80	1000
// 0  1  1		40	0100//not poss will zet zero
// 1  1  1		C0	1100
//
// Therefore mask, rotate right, and shift left
//
#else
#ifdef __MSVC__
inline	Bool	ASM_DOSvia31(	UWord	intnum,			//Interrupt number. add 256 for flags
								DPMIregs* registerimage,	
								void* 	stackspacebot=NULL,
								UWord 	stackspacesize=0,
								UWord	stackcopysize=0)
{
	UByte retval;
	__asm
	{
		mov bx,intnum;
		mov edi,registerimage;
		mov eax,stackspacebot;
		mov si,stackspacesize;
		mov cx,stackcopysize;
		mov	dx,ax;
		and	dx,15;
		add	bx,dx;
		shr	eax,4;
		mov	dx,ax;
		sub	dx,1;
		sbb	dx,dx;
											
		and	ds:[edi+22h],dx;
		and	ds:[edi+24h],dx;
		and	ds:[edi+26h],dx;
		and	ds:[edi+28h],dx;
		and	ds:[edi+2eh],dx;
		and	ds:[edi+30h],dx;
		not	dx;
		and	si,dx;
		and	dx,ax;
		add	ds:[edi+22h],dx;
		add	ds:[edi+24h],dx;
		add	ds:[edi+26h],dx;
		add	ds:[edi+28h],dx;
		mov	ds:[edi+2eh],si;
		mov	ds:[edi+30h],ax;

		mov	ax,300h;
		int	31h;
		sbb	al,al;
		neg	al;
		mov retval,al;
	}
	return (Bool)retval;
}
#endif
#endif

#ifdef __WATCOMC__
extern	Bool	ASM_DEXint10(DPMIregs*	registers);
extern	Bool	ASM_DEXint21(DPMIregs*	registers);
extern	Bool	ASM_DEXint31(DPMIregs*	registers);

#define	ASM_DEXtop									\
		"pushf"										\
		"pushad"									\
													\
		"push	esi"								\
													\
		"push	dword ptr	[esi+4]"				\
		"push	dword ptr	[esi+28]"			\
													\
		"mov	edi,dword ptr	[esi+0]"			\
		"mov	ebx,dword ptr	[esi+16]"		\
		"mov	ecx,dword ptr	[esi+24]"		\
		"mov 	edx,dword ptr	[esi+20]"		\
		"mov 	ebp,dword ptr	[esi+8]"			\
													\
		"mov	ax,es:[esi+32]"						\
		"std"										\
		"test	ax,0400h"							\
		"jnz	@@setdec"							\
		"cld"										\
	"@@setdec:"										\
		"xor	al,40h"								\
		"and	al,0E0h"							\
		"ror	al,1"								\
		"shl	al,1"								\
													\
		"pop	eax"								\
		"pop	esi"

//
//		"int	nn"
//

#define	ASM_DEXbot									\
													\
		"xchg	esi,ss:[esp]"						\
		  											\
		"pushf"										\
		"pop	word ptr	[esi+32]"			\
												\
		"mov	dword ptr	[esi+8],ebp"			\
												\
		"mov	dword ptr	[esi+20],edx"		\
		"mov	dword ptr	[esi+24],ecx"		\
		"mov	dword ptr	[esi+16],ebx"		\
		"mov	dword ptr	[esi+28],eax"		\
												\
		"mov	dword ptr	[esi+0],edi"			\
		"pop	dword ptr	[esi+4]"				\
		"popad"										\
		"sbb   	al,al"								\
		"neg	al"									\
		"popf"										\
		parm	[esi]								\
		value	[al]

#pragma	aux		ASM_DEXint10	=				\
		ASM_DEXtop								\
		"int	10h"							\
		ASM_DEXbot

#pragma	aux		ASM_DEXint31	=				\
		ASM_DEXtop								\
		"int	31h"							\
		ASM_DEXbot

#pragma	aux		ASM_DEXint21	=				\
		ASM_DEXtop								\
		"int	21h"							\
		ASM_DEXbot
#else
#ifdef __MSVC__
/*
#define	ASM_DEXtop  \
	UByte retval;  \
	__asm  \
	{  \
		mov esi,registers;  \
		pushf;  \
		pushad;  \
\
		push	esi; \
\
		push	dword ptr	[esi+4]; \
		push	dword ptr	[esi+28]; \
\
		mov	edi,dword ptr	[esi+0];  \
		mov	ebx,dword ptr	[esi+16]; \
		mov	ecx,dword ptr	[esi+24]; \
		mov 	edx,dword ptr	[esi+20]; \
		mov 	ebp,dword ptr	[esi+8]; \
\
		mov	ax,es:[esi+32]; \
		std; \
		test	ax,0400h; \
		jnz	@@setdec; \
		cld; \
	    @@setdec:; \
		xor	al,40h; \
		and	al,0E0h; \
		ror	al,1; \
		shl	al,1; \
		pop	eax; \
		pop	esi;

#define	ASM_DEXbot \
		xchg	esi,ss:[esp]; \
\
		pushf; \
		pop	word ptr	[esi+32]; \
\
		mov	dword ptr	[esi+8],ebp; \
\
		mov	dword ptr	[esi+20],edx; \
		mov	dword ptr	[esi+24],ecx; \
		mov	dword ptr	[esi+16],ebx; \
		mov	dword ptr	[esi+28],eax; \
\
		mov	dword ptr	[esi+0],edi; \
		pop	dword ptr	[esi+4]; \
		popad; \
		sbb   	al,al; \
		neg	al; \
		popf; \
		mov retval,al; \
	} \
	return (Bool)retval;
*/
inline	Bool	ASM_DEXint10(DPMIregs*	registers)
{
//		ASM_DEXtop
//		int	10h;
//		ASM_DEXbot
		return FALSE;
}
inline	Bool	ASM_DEXint21(DPMIregs*	registers)
{
//		ASM_DEXtop
//		int	21h;
//		ASM_DEXbot
		return FALSE;
}
inline	Bool	ASM_DEXint31(DPMIregs*	registers)
{
//		ASM_DEXtop
//		int	31h;
//		ASM_DEXbot
		return FALSE;
}
#endif
#endif

#include	"MathAsm.h"

#endif



