//------------------------------------------------------------------------------
//Filename       vector.h
//System         
//Author         Paul.   
//Date           Tue 19 Mar 1996
//Description    HEY PAUL... YOU HAVEN@T PUT THE HIGH DWORD FIRST?????//JIM 06Aug96
//				My alternate codings put low dword first.
//
//				I would also suggest making the register math work with registers in and out.
//				That would mean dirtily using far pointers, probably.
//
//------------------------------------------------------------------------------
#ifndef	VECTOR_Included
#define	VECTOR_Included

#define	DEFAULT_VECTOR 0

class	sdlong;
class	vector;

typedef	class	sdlong	SDLong, *SDLongP;
typedef	class	vector	Vector,	*VectorP;


#ifdef	__WATCOMC__

extern	SLong	LMulDiv(SLong, SLong, SLong);

#pragma	aux		LMulDiv =	\
				"imul	ebx"\
				"idiv	ecx"\
				parm	[eax] [ebx] [ecx] \
				modify	[edx] \
				value	[eax]

#else
#ifdef	__MSVC__

inline SLong LMulDiv( SLong num, SLong num2, SLong num3 )
{
	SLong	retval;
   __asm
   {
	mov		eax,num;
	mov		ebx,num2;
	mov		ecx,num3;
	imul	ebx;
	idiv	ecx;
	mov		retval,eax
   }
   /* Return with result in EAX */
   return retval;
}

#endif
#endif

#ifdef __WATCOMC__
extern	SLong	MakeSign(SLong );
#pragma	aux		MakeSign =	\
				"mov	edx,eax"\
				"sar	edx,0x1F"\
				parm	[eax]\
				value	[edx]
#else
#ifdef __MSVC__

inline SLong MakeSign(SLong num)
{
	SLong retval;
	__asm
	{
		mov		eax,num;
		mov		edx,eax;
		sar		edx,0x1F;
		mov		retval,edx;
	}
	return retval;
}

#endif
#endif

#ifdef __WATCOMC__
extern	void	SDLongAdd(sdlong&, sdlong& );
#pragma	aux		SDLongAdd = \
				"mov	edx,[edi]"\
				"mov	eax,[edi+4]"\
				"add	[esi+4],eax"\
				"adc	[esi],edx"\
				parm	[esi] [edi]\
				modify	[eax edx]
#else
#ifdef __MSVC__
inline void SDLongAdd(sdlong& num, sdlong& num2)
{
	__asm
	{
		mov		esi,num;
		mov		edi,num2;
		mov		edx,[edi];
		mov		eax,[edi+4];
		add		[esi+4],eax;
		adc		[esi],edx;
	}
}
#endif
#endif

#ifdef __WATCOMC__
extern	void	SDLongSub(sdlong&, sdlong& );
#pragma	aux		SDLongSub = \
				"mov	edx,[edi]"\
				"mov	eax,[edi+4]"\
				"sub	[esi+4],eax"\
				"sbb	[esi],edx"\
				parm	[esi] [edi]\
				modify	[eax edx]
#else
#ifdef __MSVC__
inline  void SDLongSub(sdlong& num1, sdlong& num2)
{
	__asm
	{
		mov		esi,num1;
		mov		edi,num2;
		mov		edx,[edi];
		mov		eax,[edi+4];
		sub		[esi+4],eax;
		sbb		[esi],edx;
	}
}
#endif
#endif

#ifdef __WATCOMC__
extern	void	SDLongMul(sdlong&, sdlong& );
//					A		B*
//					C		D
//				===============
//					BDh		BDl
//			ADh		ADl
//			CBh		CBl+
//	 ACh	ACl	
//	 discarded	===============
//
//If you discard overflow digits mul and imul give same result.
//
//				mov	eax,[esi]
//				mov	edx,[edi]
//				mov	ebx,[esi+4]
//				mov	ecx,[edi+4]
//				imul	ecx,eax
//				imul	ebx,edx
//				mul		edx
//				add		edx,ebx
//				add		edx,ecx
//				mov		[esi],eax
//				mov		[esi+4],edx
//

#pragma	aux		SDLongMul = \
				"mov	edx,[esi]"	\
				"mov	eax,[edi]"	\
				"sar	edx,0x1F"	\
				"sar	eax,0x1F"	\
				"mov	ebx,eax"	\
				"xor	ebx,edx"	\
				"push	ebx"		\
				"mov	ebx,edx"	\
				"mov	edx,[esi]"	\
				"mov	eax,[esi+4]"\
				"xor	edx,ebx"	\
				"xor	eax,ebx"	\
				"sub	eax,ebx"	\
				"sbb	edx,ebx"	\
				"mov	[esi],edx"	\
				"mov	[esi+4],eax"\
				"mov	edx,[edi]"	\
				"mov	ebx,edx"	\
				"sar	ebx,0x1F"	\
				"mov	eax,[edi+4]"\
				"xor	edx,ebx"	\
				"xor	eax,ebx"	\
				"sub	eax,ebx"	\
				"sbb	edx,ebx"	\
				"push	eax"		\
				"push	edx"		\
				"mov	ecx,[esi]"	\
				"mul	ecx"		\
				"mov	ebx,eax"	\
				"pop	edx"		\
				"pop	eax"		\
				"mov	ecx,[esi+4]"\
				"mul	ecx"		\
				"add	edx,ebx"	\
				"pop	ebx"		\
				"add	eax,ebx"	\
				"adc	edx,ebx"	\
				"xor	eax,ebx"	\
				"xor	edx,ebx"	\
				"mov	[esi],edx"	\
				"mov	[esi+4],eax"\
				parm	[esi] [edi]	\
				modify	[eax ebx ecx edx]
#else
#ifdef __MSVC__

inline void SDLongMul(sdlong& num1, sdlong& num2)
{
	__asm
	{
		mov esi,num1;
		mov edi,num2;
		mov	edx,[esi];
		mov	eax,[edi];
		sar	edx,0x1F;
		sar	eax,0x1F;
		mov	ebx,eax;
		xor	ebx,edx;
		push	ebx;
		mov	ebx,edx;
		mov	edx,[esi];
		mov	eax,[esi+4];
		xor	edx,ebx;
		xor	eax,ebx;
		sub	eax,ebx;
		sbb	edx,ebx;
		mov	[esi],edx;
		mov	[esi+4],eax;
		mov	edx,[edi];
		mov	ebx,edx;
		sar	ebx,0x1F;
		mov	eax,[edi+4];
		xor	edx,ebx;
		xor	eax,ebx;
		sub	eax,ebx;
		sbb	edx,ebx;
		push	eax;
		push	edx;
		mov	ecx,[esi];
		mul	ecx;
		mov	ebx,eax;
		pop	edx;
		pop	eax;
		mov	ecx,[esi+4];
		mul	ecx;
		add	edx,ebx;
		pop	ebx;
		add	eax,ebx;
		adc	edx,ebx;
		xor	eax,ebx;
		xor	edx,ebx;
		mov	[esi],edx;
		mov	[esi+4],eax;
	}
}
#endif
#endif

#ifdef __WATCOMC__

extern	void	SDLongAbs(sdlong&);
//
//	mov	eax,upper
//	mov	ebx,lower
//	cdq
//	xor	ebx,edx		//if neg then not
//	xor	eax,edx
//	sub	ebx,edx		//if neg then inc
//	sbb	eax,edx
//

#pragma	aux		SDLongAbs = \
				"mov	edx,[esi]"	\
				"mov	ebx,edx"	\
				"sar	ebx,0x1F"	\
				"mov	eax,[esi+4]"\
				"xor	edx,ebx"	\
				"xor	eax,ebx"	\
				"sub	eax,ebx"	\
				"sbb	edx,ebx"	\
				"mov	[esi+4],eax"\
				"mov	[esi],edx"	\
				parm	[esi]		\
				modify	[eax edx]

//	This ver uses shld
//	I have never tried shld above 32 bits
//	It should work ok
//				"mov	eax,[esi]"	\
//				"mov	edx,[esi+4]"\
//				shld	edx,eax,count
//				shl		eax,count
//				"mov	[esi]	,eax"	\
//				"mov	[esi+4]	,edx"\
//
//
//
#else
#ifdef __MSVC__

inline void SDLongAbs(sdlong& num)
{
	__asm
	{
		mov	esi,num;
		mov	edx,[esi];
		mov	ebx,edx;
		sar	ebx,0x1F;
		mov	eax,[esi+4];
		xor	edx,ebx;
		xor	eax,ebx;
		sub	eax,ebx;
		sbb	edx,ebx;
		mov	[esi+4],eax;
		mov	[esi],edx;
	}
}
#endif
#endif

#ifdef __WATCOMC__

extern	void	SDLongSHL(sdlong&,SLong );
#pragma	aux		SDLongSHL = \
				"mov	edx,[esi]"	\
				"mov	eax,[esi+4]"\
				"l1:"				\
				"add	eax,eax"	\
				"adc	edx,edx"	\
				"dec	ecx"		\
				"jnz	short l1"	\
				"mov	[esi],edx"	\
				"mov	[esi+4],eax"\
				parm	[esi] [ecx]	\
				modify	[eax ecx edx]


//	This ver uses shrd
//	I have never tried shrd above 32 bits
//	You may have to write a cleverer wrapper
//	which simply moves high to low and subtracts 32 first.
//
//				"mov	eax,[esi]"	\
//				"mov	edx,[esi+4]"\
//				shrd	eax,edx,count
//				sar		edx,count
//				"mov	[esi]	,eax"	\
//				"mov	[esi+4]	,edx"\
//
//
//
#else
#ifdef __MSVC__

inline void SDLongSHL(sdlong& num1,SLong num2 )
{
	__asm
	{
		mov esi,num1;
		mov ecx,num2;
		mov	edx,[esi];
		mov	eax,[esi+4];
		l1:;
		add	eax,eax;
		adc	edx,edx;
		dec	ecx;
		jnz	short l1;
		mov	[esi],edx;
		mov	[esi+4],eax;
	}
}
#endif
#endif

#ifdef __WATCOMC__
extern	void	SDLongSHR(sdlong&,SLong );
#pragma	aux		SDLongSHR = \
				"mov	edx,[esi]"	\
				"mov	eax,[esi+4]"\
				"l1:"				\
				"shr	edx,1"		\
				"rcr	eax,1"		\
				"dec	ecx"		\
				"jnz	short l1"	\
				"mov	[esi],edx"	\
				"mov	[esi+4],eax"\
				parm	[esi] [ecx]	\
				modify	[eax ecx edx]

//
//	This is OK... cdq is actually quite slow
//  cmp [esi],0
//	setl	al
#else
#ifdef __MSVC__
inline	void	SDLongSHR(sdlong& num1,SLong num2)
{
	__asm
	{
		mov esi,num1;
		mov ecx,num2;
		mov	edx,[esi];
		mov	eax,[esi+4];
		l1:;
		shr	edx,1;
		rcr	eax,1;
		dec	ecx;
		jnz	short l1;
		mov	[esi],edx;
		mov	[esi+4],eax;
	}
}
#endif
#endif

#ifdef __WATCOMC__
extern	SLong	SDLongSGN(sdlong&);
#pragma	aux		SDLongSGN = \
				"mov	eax,[esi]"	\
				"shr	eax,0x1F"	\
				parm	[esi]		\
				value	[eax]

//Returns TRUE if SDLong will fit into a SLong					//PD 24Apr96
//Or	  FALSE if it will overflow								//PD 24Apr96
				//
				// Surely it will fit if esi+4 == sign(esi)
				//	mov	eax,[esi]
				//	sar	eax,32
				//	xor	eax,[esi+4]
				//	sete	al
				//
#else
#ifdef __MSVC__

inline SLong SDLongSGN(sdlong& num)
{
	SLong retval;
	__asm
	{
		mov esi,num;
		mov	eax,[esi];
		shr	eax,0x1F;
		mov retval,eax;
	}
	return retval;
}
#endif
#endif

#ifdef __WATCOMC__

extern	Bool	SDLong2Long(sdlong&);
#pragma	aux		SDLong2Long = \
				"mov	eax,[esi]"		\
				"mov	edx,[esi+4]"	\
				"mov	ebx,eax"		\
				"sar	ebx,0x1F"		\
				"xor	eax,ebx"		\
				"xor	edx,ebx"		\
				"sub	eax,ebx"		\
				"mov	al,0"			\
				"jnz	short False"	\
				"sbb	edx,ebx"		\
				"and	edx,0x080000000"\
				"jnz	short False"	\
				"inc	al"				\
				"False:"				\
				parm	[esi]			\
				modify	[eax ebx edx]	\
				value	[al]
#else
#ifdef __MSVC__
inline	Bool	SDLong2Long(sdlong& num)
{
	UByte retval;
	__asm
	{
		mov esi,num;
		mov	eax,[esi];
		mov	edx,[esi+4];
		mov	ebx,eax;
		sar	ebx,0x1F;
		xor	eax,ebx;
		xor	edx,ebx;
		sub	eax,ebx;
		mov	al,0;
		jnz	short False;
		sbb	edx,ebx;
		and	edx,0x080000000;
		jnz	short False;
		inc	al;
		False:;
		mov retval,al;
	}
	return (Bool)retval;
}
#endif
#endif



class	sdlong
{
	public:
		SLong	hi;
		ULong	lo;

		CON		sdlong()	{};

		CON		sdlong(SLong x)
				{
					lo = (ULong )x;
					hi = MakeSign(x);
				};

		//Maths operator overloads

		friend	sdlong	operator+(sdlong,sdlong);
		friend	sdlong	operator-(sdlong,sdlong);
		friend	sdlong	operator*(sdlong,sdlong);
		friend	sdlong	operator/(sdlong,sdlong);

		friend	sdlong	operator<<(sdlong,SLong);
		friend	sdlong	operator>>(sdlong,SLong);

		sdlong&	operator+=(sdlong);
		sdlong&	operator-=(sdlong);
		sdlong&	operator*=(sdlong);
		sdlong&	operator/=(sdlong);

		sdlong&	operator>>=(SLong);
		sdlong&	operator<<=(SLong);

		//Logical operator overloads

		friend	sdlong	operator|(sdlong,sdlong);
		friend	sdlong	operator&(sdlong,sdlong);
		friend	sdlong	operator^(sdlong,sdlong);

		sdlong&	operator|=(sdlong);
		sdlong&	operator&=(sdlong);
		sdlong&	operator^=(sdlong);

		//Comparison operator overloads
			//for completeness make the parameter types const...
		friend	Bool	operator>(sdlong,sdlong);
		friend	Bool	operator>=(const sdlong&,const sdlong&);
		friend	Bool	operator==(sdlong,sdlong);
		friend	Bool	operator!=(sdlong,sdlong);
		friend	Bool	operator<=(sdlong,sdlong);
		friend	Bool	operator<(sdlong,sdlong);
};

//--------------------------------------------------
//
//	Comparison operator overloads
//
//--------------------------------------------------

inline	Bool operator==(sdlong a,sdlong b)
{
	if (a.hi != b.hi)	return	(Bool)FALSE;
	if (a.lo != b.lo)	return	(Bool)FALSE;
	return	(Bool)TRUE;
}

inline	Bool operator!=(sdlong a,sdlong b)
{
	if (a.hi != b.hi)	return	(Bool)TRUE;
	if (a.lo != b.lo)	return	(Bool)TRUE;
	return	(Bool)FALSE;
}

//
// Surely better to perform register math?
//
//

inline	Bool operator>(sdlong a,sdlong b)
{
	if (a.hi > b.hi)	return	(Bool)TRUE;
	
	if (a.hi < b.hi)	return	(Bool)FALSE;

	if (a.lo == b.lo)	return	(Bool)FALSE;

	if (a.hi >= 0)
	{
		if (a.lo > b.lo)return	(Bool)TRUE;
		return	(Bool)FALSE;
	}
	if (a.lo < b.lo)	return	(Bool)FALSE;
	return	(Bool)TRUE;
}

inline	Bool operator>=(const sdlong& a,const sdlong& b)		//PD 02Apr96
{
	if (a.hi > b.hi)	return	(Bool)TRUE;
	
	if (a.hi < b.hi)	return	(Bool)FALSE;

	if (a.lo == b.lo)	return	(Bool)TRUE;

	if (a.hi >= 0)
	{
		if (a.lo > b.lo)return	(Bool)TRUE;
		return	(Bool)FALSE;
	}
	if (a.lo < b.lo)	return	(Bool)FALSE;
	return	(Bool)TRUE;
}

inline	Bool operator<(sdlong a,sdlong b)
{
	if (a.hi < b.hi)	return	(Bool)TRUE;
	
	if (a.hi > b.hi)	return	(Bool)FALSE;

	if (a.lo == b.lo)	return	(Bool)FALSE;

	if (a.hi >= 0)
	{
		if (a.lo < b.lo)return	(Bool)TRUE;
		return	(Bool)FALSE;
	}
	if (a.lo > b.lo)	return	(Bool)FALSE;
	return	(Bool)TRUE;
}

inline	Bool operator<=(sdlong a,sdlong b)
{
	if (a.hi < b.hi)	return	(Bool)TRUE;
	
	if (a.hi > b.hi)	return	(Bool)FALSE;

	if (a.lo == b.lo)	return	(Bool)TRUE;

	if (a.hi >= 0)
	{
		if (a.lo < b.lo)return	(Bool)TRUE;
		return	(Bool)FALSE;
	}
	if (a.lo > b.lo)	return	(Bool)FALSE;
	return	(Bool)TRUE;
}

//--------------------------------------------------
//
//	Logical operator overloads
//
//--------------------------------------------------

inline	sdlong&	sdlong::operator|=(sdlong a)
{
	hi |= a.hi; lo |= a.lo;

	return	*this;
}

inline	sdlong&	sdlong::operator&=(sdlong a)
{
	hi &= a.hi; lo &= a.lo;

	return	*this;
}

inline	sdlong&	sdlong::operator^=(sdlong a)
{
	hi ^= a.hi; lo ^= a.lo;

	return	*this;
}

inline	sdlong	operator|(sdlong a,sdlong b)
{
	sdlong	res = a;
	res	|= b;
	return	res;
}

inline	sdlong	operator&(sdlong a,sdlong b)
{
	sdlong	res = a;
	res	&= b;
	return	res;
}

inline	sdlong	operator^(sdlong a,sdlong b)
{
	sdlong	res	= a;
	res	^= b;
	return	res;
}

//--------------------------------------------------
//
//	Signed 64bit addition
//
//--------------------------------------------------
inline	sdlong& sdlong::operator+=(sdlong x)
{
	SDLongAdd(*this,x);
	return *this;
}

inline	sdlong	operator+(sdlong a,sdlong b)
{
	sdlong	sum = a;
	sum += b;
	return	sum;
}

//--------------------------------------------------
//
//	Signed 64bit subtraction
//
//--------------------------------------------------
inline	sdlong& sdlong::operator-=(sdlong x)
{
	SDLongSub(*this,x);
	return *this;
}

inline	sdlong	operator-(sdlong a,sdlong b)
{
	sdlong	dif = a;
	dif -= b;
	return	dif;
}

//--------------------------------------------------
//
//	Signed 64bit multiplication
//
//--------------------------------------------------
inline	sdlong& sdlong::operator*=(sdlong x)
{
	SDLongMul(*this,x);
	return *this;
}

inline	sdlong	operator*(sdlong a,sdlong b)
{
	sdlong	prod = a;
	prod *= b;
	return	prod;
}

//--------------------------------------------------
//
//	Signed 64bit shift left
//
//--------------------------------------------------
inline	sdlong&	sdlong::operator<<=(SLong s)
{
	SDLongSHL(*this,s);
	return	*this;
}

inline	sdlong	operator<<(sdlong a,SLong s)
{
	sdlong	val = a;
	SDLongSHL(val,s);
	return	val;
}

//--------------------------------------------------
//
//	Signed 64bit shift right
//
//--------------------------------------------------
inline	sdlong&	sdlong::operator>>=(SLong s)
{
	SDLongSHR(*this,s);
	return	*this;
}

inline	sdlong	operator>>(sdlong a,SLong s)
{
	sdlong	val = a;
	SDLongSHR(val,s);
	return	val;
}

extern	void	SDLongDivU(sdlong&, sdlong& );
//
//	Simplest fix is to accept a small error.
//	Sign extend high bit of divisor
//	While high byte of divisor != extended
//		sar divisor
//		sar	dividend
//	if divisorlow top bit != extended
//		sar divisor
//		sar	dividend
//	if |dividendhigh|<2*|divisorlow| result=max & sort sign
//	else
//		result= dividend63/divisor31
//
//


//--------------------------------------------------
//
//	Signed 64bit division
//
//--------------------------------------------------
inline	sdlong& sdlong::operator/=(sdlong x)
{
	sdlong	div_this= 	*this;

	sdlong	by_this	=	x;

	SDLongAbs (div_this);

	SDLongAbs (by_this);

	if (div_this < by_this)	return	*this = (SLong )0;




	SLong	shiftcount = 0;

	SLong	result = 0;			//hey!!!! Result can be more than 32 bits!!!

	sdlong	temp = by_this;

	if ( (temp == 0) || (div_this.hi > 0x20000000) )
		return *this;											//RJS 06Aug96

	for (;;)
	{	//this don't work if div_this=O(2G), 'cos temp <0
		if (div_this < temp)	break;

//DeadCode JIM 06Aug96 		by_this = temp;		//use BSR to speed this up

		temp += temp;

		shiftcount++;
	}
	by_this=temp>>1;

	for(;--shiftcount;)
	{	//can't happen more than once
		if (div_this >= by_this)								//JIM 06Aug96
		{
			div_this -= by_this;
			result ++;
		}

//DeadCode JIM 06Aug96 		div_this += by_this;
//DeadCode JIM 06Aug96 
//DeadCode JIM 06Aug96 		result--;

		div_this<<=(SLong )1;

		result<<=1;
	}

	//Restore the sign of the result

	if (SDLongSGN(*this) != SDLongSGN(x))
		result = 0-result;

	return *this = result;
}

inline	sdlong	operator/(sdlong a,sdlong b)
{
	sdlong	div = a;
	div /= b;
	return	div;
}

//--------------------------------------------------
//--------------------------------------------------

class	vector
{
	public:

		SLong	a, b, c;

		CON		vector()	{};

		CON		vector(SLong x, SLong y, SLong z)
				{
					a = x; b = y; c = z;
				}

		DES		~vector()	{};

		friend	vector operator+(vector, vector);
		friend	vector operator-(vector, vector);
		friend	vector operator%(vector, vector);	//Cross product
		friend	SLong  operator*(vector, vector);	//Scalar (dot) product

		friend	vector operator*(vector, SLong );
		friend	vector operator*(SLong, vector );
		friend	vector operator/(vector, SLong );
		friend	vector operator/(SLong, vector );

		friend	vector operator*(vector, SWord );
		friend	vector operator/(vector, SWord );

		friend	Bool	operator==(vector,vector);
		friend	Bool	operator!=(vector,vector);

		vector&	operator+=(vector);
		vector&	operator-=(vector);
		vector&	operator%=(vector);		//Cross product
		SLong	operator*=(vector);		//Scalar (dot) product

		vector& operator*=(SLong );
		vector& operator*=(SWord );

		vector& operator/=(SLong );
		vector& operator/=(SWord );

		static  SLong	RootGuess(SLong	guess,SLong squared);	//RJS 22Nov96
		void	normalise();
		SLong	magnitude();
		vector  normal(vector, vector);
};

//--------------------------------------------------
//
//	Vector addition
//
//--------------------------------------------------
inline	vector& vector::operator+=(vector V)
{
	a += V.a; b += V.b; c += V.c;

	return *this;
}

inline	vector operator+(vector A, vector B)
{
	return vector(A.a + B.a, A.b + B.b, A.c + B.c);
}

//--------------------------------------------------
//
//	Vector subtraction
//
//--------------------------------------------------
inline 	vector& vector::operator-=(vector V)
{
	a -= V.a; b -= V.b; c -= V.c;

	return *this;
}

inline	vector operator-(vector A, vector B)
{
	return vector(A.a - B.a, A.b - B.b, A.c - B.c);
}

//--------------------------------------------------
//
// Vector scalar (dot) product
//
//--------------------------------------------------
inline	SLong vector::operator*=(vector V)
{
	return	(a * V.a) + (b * V.b) + (c * V.c);
}

inline	SLong operator*(vector A, vector B)
{
	return	(A.a * B.a) + (A.b * B.b) + (A.c * B.c);
}

//--------------------------------------------------
//
//	Vector cross product
//
//--------------------------------------------------
inline	vector& vector::operator%=(vector V)
{
	vector	retval(	(b * V.c - c * V.b),
					(c * V.a - a * V.c),
					(a * V.b - b * V.a)
				);

	*this = retval;

	return *this;
}

inline	vector operator%(vector A, vector B)
{
	vector	prod = A;

	prod %= B;

	return	prod;
}	

//---------------------------------------------------
//
// Vector by scalar multiplication
//
//---------------------------------------------------
inline	vector& vector::operator*=(SLong S)
{
	a *= S; b *= S; c *= S;

	return *this;
}

inline vector& vector::operator*=(SWord S)
{
	return *this *= (SLong )S;
}

inline vector operator*(vector V, SLong S)
{
	vector prod = V;

	prod *= S;

	return prod;
}

inline vector operator*(SLong S, vector V)
{
	return V * S;
}

inline vector operator*(vector V, SWord S)
{
	return V * (SLong )S;
}

inline vector operator*(SWord S, vector V)
{
	return V * S;
}

//---------------------------------------------------
//
// Vector by scalar division
//
//---------------------------------------------------
inline	vector& vector::operator/=(SLong S)
{
	a /= S; b /= S; c /= S;

	return *this;
}

inline vector& vector::operator/=(SWord S)
{
	return *this /= (SLong )S;
}

inline vector operator/(vector V, SLong S)
{
	vector prod = V;

	prod /= S;

	return prod;
}

inline vector operator/(vector V, SWord S)
{
	return V / (SLong )S;
}

//--------------------------------------------------------------
//
// Vector magnitude calculation using approximation
//
// SQRT ( a*a + b*b + c*c ) approx =
//
// MAX(|a|,|b|,|c|) + 11/32MED(|a|,|b|,|c|) + 1/4MIN(|a|,|b|,|c|)
//
//---------------------------------------------------------------
inline SLong vector::magnitude()
{
	SLong	max,med,min,temp;

	max = a<0?-a:a; med = b<0?-b:b; min = c<0?-c:c;

	if (max < med )
	{
		temp = max; max = med; med = temp;
	}

	if (max < min)
	{
		temp = max; max = min; min = max;
	}

	if (med < min)
	{
		temp = med; med = min; min = temp;
	}

	// Now max > med > min

	temp = med >> 2;	//	1/4 med

	med = temp;

	temp >>= 2;			//	1/16 med

	med += temp;

	temp >>= 1;			//	1/32 med

	med += temp;

	min	>>= 2;			//	1/4 min

	return max + med + min;
}

inline SLong	vector::RootGuess(SLong	guess,SLong squared)
{
	return ((squared / (guess<<1)) + (guess >> 1));
}

//---------------------------------------------------
//
// Vector normalisation (creates a vector of
//	magnitude 0x000100)
//
//---------------------------------------------------
inline void vector::normalise()
{
	//Generate a unit vector from a vector of arbitrary
	//magnitude

	SLong	mag = RootGuess(magnitude(),a*a+b*b+c*c);			//RJS 22Nov96

	a = LMulDiv(a,0x0100,mag);									//RJS 22Nov96
	b = LMulDiv(b,0x0100,mag);									//RJS 22Nov96
	c = LMulDiv(c,0x0100,mag);									//RJS 22Nov96
}

//---------------------------------------------------
//
// Normal vector generation
//
//---------------------------------------------------
inline vector vector::normal(vector A,vector B)
{
	vector	normal;

	normal = A % B;

	normal.normalise();

	return normal;
}

//--------------------------------------------------
//
//	Comparison operator overloads
//
//--------------------------------------------------

inline	Bool operator==(vector A,vector B)
{
	if (A.a != B.a)	return	(Bool)FALSE;
	if (A.b != B.b)	return	(Bool)FALSE;
	if (A.c != B.c)	return	(Bool)FALSE;
	return	(Bool)TRUE;
}

inline	Bool operator!=(vector A,vector B)
{
	if (A.a != B.a)	return	(Bool)TRUE;
	if (A.b != B.b)	return	(Bool)TRUE;
	if (A.c != B.c)	return	(Bool)TRUE;
	return	(Bool)FALSE;
}

const vector ORIGIN = vector(0,0,0);

#endif

