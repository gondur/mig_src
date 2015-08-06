//------------------------------------------------------------------------------
//Filename       enumbits.m
//System         
//Author         Jim Taylor
//Date           Wed 18 Oct 1995
//This module defines various manipulators for ENUMS. 
//Execute the relevent macro on an ENUM 
//to enable the extra functionality you want
//
//BITABLE(b)		Basic bit manipulation (and/or/xor) between elements
//					|, |=, &, &=, ^, ^=
//NOTABLE(b)		Complement and difference. % is nand
//					~, -, %, %=
//MASKABLE(b,m)		More structured than BITABLE. Uses 2 ENUMS to distinguish
//					values and masks.	b=b&m, b&=m, b=b%m, b%=m, m=m|m, m|=m 
//SHIFTABLE(b,s,z)	Additional manipulation to shift fields to zero base
//					b=z<<s, z=b>>s		Z may be int
//ADDORABLE(b)		Basic OR function is aliased to +. And is *,xor is -
//					b+=b ==> b|=b, b=b+b ==> b=b|b,
//					b*=b ==> b&=b, b=b*b ==> b=b&b,
//					b-=b ==> b^=b, b=b-b ==> b^=b
//MATHABLE(b)		Basic math operations enabled 
//					b=b+b, b+=b, b=b-b, b-=b, b=-b, a++, ++a, --a, a--
//DELTABLE(b,d)		b=b+d, b=b-d, b+=d, b-=d
//MULABLE(b,m)		Basic multiplication by another enum or int
//					b=b*m, b*=m, b=b/m, b=b%m, m=b/b, m=b%b
//------------------------------------------------------------------------------
#ifndef	ENUMBITS_Included
#define	ENUMBITS_Included
//------------------------------------------------------------------------------
//MACRO BITABLE
//Generates operator overloads for bitwise manipulation of ENUMS to hide casting
//These functions should all go inline so cost nothing.
//Input 	name: name of enum
//Operators defined:
//	|	|=	bitwise OR
//	+	+=	bitwise OR
//	&	&=	bitwise AND
//	*	*=	bitwise AND
//	^	^=	bitwise XOR
//  -	-=	bitwise XOR
//------------------------------------------------------------------------------
#define	BITABLE(nnn) inline	nnn	operator	|	(nnn	a,nnn	b) 			\
			{return ((nnn)	((int)a|(int)b));}					   			\
	inline	nnn	operator	|=	(nnn& a,nnn	b)	{return (a=a|b);}  			\
																   			\
	inline	nnn	operator	&	(nnn	a,nnn	b)				   			\
			{return ((nnn) ((int)a&(int)b));}					   			\
	inline	nnn	operator	&=	(nnn& a,nnn	b)	{return (a=a&b);}  			\
								 								   			\
	inline	nnn	operator	^	(nnn	a,nnn	b)				   			\
			{return ((nnn) ((int)a^(int)b));}					   			\
	inline	nnn	operator	^=	(nnn& a,nnn	b)	{return (a=a^b);}  			\
	

//------------------------------------------------------------------------------
//MACRO	NOTABLE
//Generates additional operator overloadsfor bitwise enums to hide casting
//Inputs:	name: name of enum
//			mask: mask value to apply for NOT
//Operators defined:
//	~		bitwise complement
//	-		bitwise complement
//  %	%=	bitwise mask remainder: a & ~b
//
//------------------------------------------------------------------------------
#define	NOTABLE(name,mask)													\
	inline	name	operator	~	(name a)								\
				{return (a^(name) mask);}												\
	inline	name	operator	-	(name a)								\
				{return (a^(name) mask);}											\
	inline	name	operator	%	(name a,name b)							\
				{return	name(int(a) & ~int(b));}											\
	inline	name	operator	%=	(name& a,name b)						\
				{return	a=name(int(a)&~int(b));}											\

//------------------------------------------------------------------------------
//MACRO	MASKABLE
//An alternative to BITABLE and NOTABLE 
//where the mask fields are provided by a second enum
//Inputs:	name:	name of basic enum
//			mask:	name of masking enum. This must have a mask__ALL entry
//Operators defined:
//	n&m	n&=m	bitwise mask
//	n%m	n%=m	bitwise mask remainder
//  m|m	m|=m	mask merging
//	m+m m+=m
//  n|n	n|=n	value merging	- but mask and value can't be merged
//  n+n n+=n
//------------------------------------------------------------------------------
#define	MASKABLE(name,mask)													\
	inline	name	operator&	(name a,mask b)								\
			{return	((name) ((int)a&(int)b));}								\
	inline	name	operator	&=	(name& a,mask b)	{return (a=a&b);}	\
	inline	name	operator	%	(name a,mask b)							\
			{return (a&(mask) (b^mask##__ALL));}					   		\
	inline	name	operator	%=	(name& a,mask b)	{return (a=a%b);}	\
																			\
	inline	name	operator	|	(name	a,name	b)						\
			{return ((name)	(((int)a|(int)b)));}							\
	inline	name	operator	|=	(name&	a,name	b)	{return (a=a|b);}	\
																			\
	inline	mask	operator	|	(mask	a,mask	b)						\
			{return ((mask)	((int)a|(int)b));}								\
	inline	mask	operator	|=	(mask&	a,mask	b)	{return (a=a|b);}	\
	inline	mask	operator	+	(mask	a,mask	b)						\
			{return ((a|b));}												\
	inline	mask	operator	+=	(mask&	a,mask	b)	{return (a=a|b);}	\
																			
//------------------------------------------------------------------------------
//MACRO	ADDORABLE
//Input:	name:	name of basic enum
//Operators defined:
//  n+n n+=n	is equivalent to   n|n	n|=n	
//------------------------------------------------------------------------------
#define	ADDORABLE(nnn)														\
	inline	nnn	operator	+	(nnn	a,nnn	b)							\
			{return ((a|b));}												\
	inline	nnn	operator	+=	(nnn&	a,nnn	b)	{return (a=a|b);}		\
	inline	nnn	operator	*	(nnn	a,nnn	b)	{return a&b;}  			\
	inline	nnn	operator	*=	(nnn& a,nnn	b)	{return (a=a&b);}  			\
	inline	nnn	operator	-	(nnn	a,nnn	b)	{return a^b;}  			\
	inline	nnn	operator	-=	(nnn& a,nnn	b)	{return (a=a^b);}  			\

//------------------------------------------------------------------------------
//MACRO	SHIFTABLE																			
//Yet another alternative. This one is complicated.
//There are three enum inputs:
//masked		is the traditional multi-field enum
//shifts		is an enum specifying shifts for each field
//based			is the field based at bit zero - i.e. shifted down
//				this may be int.
//Operators defined:
//	b = m >> s	shift down to integer
//	m = b << s	shift up to mask
//
//
//------------------------------------------------------------------------------
#define	SHIFTABLE(masked,shifts,based)										\
	inline	masked	operator<<	(based	b,shifts s)							\
			{return ((masked) ((int)b<<(int)s));}							\
	inline	based	operator>>	(masked	b,shifts s)							\
			{return ((masked) ((int)b>>(int)s));}							\

//------------------------------------------------------------------------------
//MACRO	MATHABLE
//Enables simple addition/subtraction - not modulo!
//Operations:
//	b+b	b+=b		addition
//	b-b	b-=b		subtraction
//	-b				negation
//------------------------------------------------------------------------------
#define	MATHABLE(name)				 										\
	inline	name	operator+(name a,name b)								\
			{return ((name) ((int) a + (int) b));}							\
	inline	name	operator+=(name& a,name b)								\
			{return a=a+b;}													\
	inline	name	operator-(name a,name b)								\
			{return ((name) ((int) a - (int) b));}							\
	inline	name	operator-=(name& a,name b)								\
			{return a=a-b;}													\
	inline	name	operator-(name a)										\
			{return ((name) (- (int) a));}									\
	inline	name	operator ++ (name& a)									\
			{return a= (name) (a+1);}										\
	inline	name	operator--(name& a)										\
			{return a=(name)(a-1);}											\
	inline	name	operator++( name & a,int)								\
			{ name x=a;++a;return x;}										\
	inline	name	operator--( name & a,int)								\
			{ name x=a;--a;return x;}										\

//------------------------------------------------------------------------------
//MACRO	DELTABLE
//Enables simple addition/subtraction of a delta - not modulo!
//Operations:
//	b+d	b+=d		addition
//	b-d	b-=d		subtraction
//------------------------------------------------------------------------------
#define	DELTABLE(bbb,ddd)													\
	inline	bbb		operator+(bbb a,ddd b)									\
			{return ((bbb) ((int) a + (int) b));}							\
	inline	bbb		operator+(ddd a,bbb b)									\
			{return ((bbb) ((int) a + (int) b));}							\
	inline	bbb	operator+=(bbb& a,ddd b)									\
			{return a=(bbb)((int)a+(int)b);}													\
	inline	bbb		operator-(bbb a,ddd b)									\
			{return ((bbb) ((int) a - (int) b));}							\
	inline	bbb		operator-(ddd a,bbb b)									\
			{return ((bbb) ((int) a - (int) b));}							\
	inline	bbb	operator-=(bbb& a,ddd b)									\
			{return a=(bbb)((int)a-(int)b);}													\

//------------------------------------------------------------------------------
//MACRO	MULABLE
//Enables mutiplication between enums
//The principle is that b=m*q
//Inputs:	b	basic enum
//			m	multiplier enum
//			q	quotient enum
//			rm	remainder from division by multiplier
//			rq	remainder from division by quotient
//Generally these won't be 5 different enums, but will share.
//Note that abreviated operations are not supported.
//
//Operations:
//	b=m*q		multiplication
//	q=b/m		division1
//	m=b/q		division2
//	rm=b%m		remainder from (1)
//	rq=b%q		remainder from (2)
//------------------------------------------------------------------------------
#define	MULABLE(b,q,m,rm,rq)	   											\
	inline	b	operator*(m mm,q qq)										\
			{return	((b) ((ULong) mm * (ULong) qq));}						\
	inline	q	operator/(b bb,m mm)										\
			{return ((q)  ((ULong) bb / (ULong) mm));}						\
	inline	m	operator/(b bb,q qq)										\
			{return ((m)  ((ULong) bb / (ULong) qq));}						\
	inline	rq	operator/(b bb,q qq)										\
			{return ((rq)  ((ULong) bb % (ULong) qq));}						\
	inline	rm	operator/(b bb,m mm)										\
			{return ((rm)  ((ULong) bb % (ULong) mm));}						\

//------------------------------------------------------------------------------
//END OF FILE
//------------------------------------------------------------------------------
#endif
