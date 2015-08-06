//------------------------------------------------------------------------------
//Filename       bitfield.h
//System         
//Author         Jim Taylor
//Date           Sun 26 Nov 1995
//Description    A bitfields class.
//				In principal, this is a container class...
//1) Macro MAKEFIELD (srctype,minval,maxval) 
//		this defines a srctypeField type, and operations possible on that type:
//			srcField|=src		sets a bit	-commutes: srcField|=src|=src works
//			srcField%=src		clears a bit
//			srcField^=src		xors a bit
//			srcField|=srcField	logical or of all bits
//			srcField&=srcField	logical and of all bits
//			srcField^=srcField	logical xor of all bits
//			+srcField			any bits set? true/false
//			srcField>=srcField	set contains set? true/false
//			srcField<=srcField	set contains set? true/false
//			srcField==srcField	set contains set? true/false
//			srcField[src]		set contains bit? true/false
//			srcField>=src		set contains bit? true/false
//		Any other logical op should be illegal!
//------------------------------------------------------------------------------
#ifndef	BITFIELD_Included
#define	BITFIELD_Included
#ifndef	assert
//DeadCode DAW 01Oct96 	 #define assert(__ignore) ((void)0)
	#define assert(txt)	
#pragma warnmsg("Assert is non functional!!!")
#endif
	#include	"hardpasm.h"
#define	DEFAULT_BITFIELD 0


#define	MAKEFIELD(src,minval,maxval)					\
class	src##Field										\
{														\
public:													\
enum	fieldsize	{	MAX=maxval,MIN=minval,			\
						RANGE=((int)maxval-(int)minval)+1,		\
						BYTES=((int)maxval-(int)minval+8)/8		\
					};									\
private:												\
void	errorcheck(int val,int min,int max) const		\
	{assert ((val<=max && val>=min) && ("Bit field index out of range"));}	\
char	dataspace[BYTES];								\
public:													\
	char*	FuckingDirtyAccess()	{return dataspace;}	\
/*constructor*/											\
	src##Field()										\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		dataspace[i]=0;									\
}														\
	src##Field(src minset,src maxset)					\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		dataspace[i]=0;									\
	for (i=minset;i<=(int)maxset;i++)					\
		operator |=((src)i);							\
}														\
/*------------------------------						\
/ operator |=											\
/ set a bit in the bitfield								\
/														\
/------------------------------*/						\
src##Field&	operator	|=(src	s)						\
{														\
	errorcheck(s,MIN,MAX);								\
	BITSET(dataspace,(int)s-(int)MIN);					\
	return(*this);										\
}														\
														\
/*------------------------------						\
/ operator |=											\
/ set a bit in the bitfield								\
/														\
/------------------------------*/						\
src##Field&	operator	=(SLong	s)						\
{														\
	assert(((s==0)||(s==-1))&&("Can set to 0 or -1 only"));\
	int i;												\
	for (i=BYTES;i--;)									\
		dataspace[i]=(char)s;							\
	return(*this);										\
}														\
														\
/*------------------------------						\
/ operator %=											\
/ clear a bit in the bitfield							\
/ this is the remainder function						\
/------------------------------*/						\
src##Field&	operator	%=(src	s)						\
{														\
	errorcheck(s,MIN,MAX);								\
	BITRESET(dataspace,(int)s-(int)MIN);				\
	return(*this);										\
}														\
														\
/*------------------------------						\
/ operator ^=											\
/ not a bit in the bitfield								\
/														\
/------------------------------*/						\
src##Field&	operator	^=(src	s)						\
{														\
	errorcheck(s,MIN,MAX);								\
	BITCOMP(dataspace,(int)s-(int)MIN);					\
	return(*this);										\
}														\
														\
/*------------------------------						\
/ operator |=											\
/ or together two bit fields							\
/ 'destroys' the target field							\
/------------------------------*/						\
src##Field& operator	|=(const src##Field& s)				\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		dataspace[i]|=s.dataspace[i];					\
	return(*this);										\
}														\
														\
/*------------------------------						\
/ operator &=											\
/ and together two bit fields							\
/ 'destroys' the target field							\
/------------------------------*/						\
src##Field& operator	&=(const src##Field& s)				\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		dataspace[i]&=s.dataspace[i];					\
	return(*this);										\
}														\
														\
/*------------------------------						\
/ operator ^=											\
/ xor together two bit fields							\
/ 'destroys' the target field							\
/------------------------------*/						\
src##Field& operator	^=(const src##Field& s)				\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		dataspace[i]^=s.dataspace[i];					\
	return(*this);										\
}														\
/*------------------------------						\
/ operator -=											\
/ xor together two bit fields							\
/ 'destroys' the target field							\
/------------------------------*/						\
src##Field& operator	-=(const src##Field& s)				\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		dataspace[i]&=~s.dataspace[i];					\
	return(*this);										\
}														\
														\
/*------------------------------						\
/ operator int											\
/ result from an int conversion							\
/ specifically when used in an if						\
/------------------------------*/						\
/* THIS IS TOO DANGEROUS BY HALF!!!						\
 Any missing operation is defaulting to this conversion \
operator	int	()										\
{														\
	int i;												\
	for (i=BYTES;i--;)									\
		if(dataspace[i])	return(TRUE);				\
	return(FALSE);										\
}														\
*/														\
/*------------------------------						\
/ operator int											\
/ result from an int conversion							\
/ specifically when used in an if						\
/------------------------------*/						\
bool	operator	+()	const							\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		if(dataspace[i])	return(true);				\
	return(false);										\
}														\
/*------------------------------						\
/ operator >=											\
/ this contains s,										\
/ i.e. there would be no change if						\
/ you performed an OR operation							\
/------------------------------*/						\
bool	operator	>=(const src##Field& s) const		\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		if (	(dataspace[i]&s.dataspace[i])			\
			!=	s.dataspace[i]	)						\
			return(false);								\
	return(true);										\
}														\
/*------------------------------						\
/ operator <=											\
/ s contains this,										\
/ i.e. there would be no change if						\
/ you performed an OR operation							\
/------------------------------	*/						\
bool	operator	<=(const src##Field& s) const		\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		if (	(dataspace[i]&s.dataspace[i])			\
			!=	dataspace[i]	)						\
			return(false);								\
	return(true);										\
}														\
														\
/*------------------------------						\
/ operator ==											\
/ s contains this,										\
/ i.e. there would be no change if						\
/ you performed an OR operation							\
/------------------------------*/						\
bool	operator	==(const src##Field& s) const		\
{														\
	int i;												\
	for (i=(int)BYTES;i--;)								\
		if (dataspace[i]!=s.dataspace[i])				\
			return(false);								\
	return(true);										\
}														\
/*------------------------------						\
/ operator []											\
/ element s is set test									\
/------------------------------*/						\
bool	operator	[] (const src s) const				\
{														\
	errorcheck(s,MIN,MAX);								\
	return BITTEST(dataspace,(int)s-(int)MIN);			\
}														\
														\
	friend	bool	operator	>=						\
		(const src##Field& f,src s);					\
														\
};	/* class end*/										\
														\
/*---------------------------------------------------*/ \

//----------------------------------------------------------------------------
//
#endif
