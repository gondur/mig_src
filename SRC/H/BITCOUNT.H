//------------------------------------------------------------------------------
//Filename       bitfield.h
//System         
//Author         Jim Taylor
//Date           Mon 24 Nov 1997
//Description    Enum Bitfields in microsoft
//				Microsoft doesn't like enums to be concatenated in bitfields,
//				so it falls on me to do the relevent farting about, as usual!
//
//	FIRSTFIELD(size,	Type,name,maxbitnum);
//		BITFIELD(		Type,name,minbitnum,maxbitnum);
//		BITFIELD(		Type,name,minbitnum,maxbitnum);
//	LASTFIELD(			Type,name,minbitnum,maxbitnum)
//or
//	SPAREFIELD(			minbitnum,maxbitnum)
//
//	size is one of SByte/UByte/SWord/UWord/SLong/ULong
//	Type is a standard enum type
//	name is the name you want to use to access this field
//	minbitnum,maxbitnum is the range of bit numbers you want to use
//	It is up to the user to ensure that the bitnums are sequential and big enough
//
//NEW BUG:
//	Can't overload copy operator = inside union.
//	I don't know why. Barmy rules!
//	This means a straight assignment of 1 instance of a bitfield to another is illegal!
//	To find them you MUST compile occationally with TRACKBADASSIGNMENTS set.
//	This unpacks the structure so that the miscreants can be found.
//------------------------------------------------------------------------------
#ifndef	BITF2_Included
#define	BITF2_Included
//   "limits.h"
#define	DEFAULT_BITF2 0
//TEMPCODE RDH 24/05/99 #define	TRACKBADASSIGNMENTS
#ifdef	TRACKBADASSIGNMENTS
#define	BITFIELD_AGGREGATOR	struct
#define	BITFIELD_COPY(t)	private: void	operator = (t& v)	{}
#else
#define	BITFIELD_AGGREGATOR	union
#define	BITFIELD_COPY(t)	/*not defined*/
#endif

//#define	Bits_UByte	8
//#define	Bits_SByte	8
//#define	Bits_UWord	16
//#define	Bits_SWord	16
//#define	Bits_ULong	32
//#define	Bits_SLong	32

#define	ONLYFIELD(Size,Type,name)								\
	struct	T_##name{											 \
			Size	value;										  \
			operator Type()	{return (Type(value));}				   \
			Type operator = (Type v)	{return (Type(value=Size(v)));}   \
		}	name;	

#define	BOOLFIELDS(n0,n1,n2,n3,n4,n5,n6,n7)				\
	BITFIELD_AGGREGATOR									 \
	{													  \
		UByte	overview_n0;							   \
		struct	T_##n0{	UByte	value:1,trailing:1;			\
		operator bool()	{return (value!=0);}				 \
		bool operator = (bool v)	{return ((value=v)!=0);}  \
		BITFIELD_COPY(T_##n0)								   \
				}	n0;										    \
		BOOLFIELD(n1,1)						\
		BOOLFIELD(n2,2)						\
		BOOLFIELD(n3,3)						\
		BOOLFIELD(n4,4)						\
		BOOLFIELD(n5,5)						\
		BOOLFIELD(n6,6)						\			 \
		struct	T_##n7{	UByte	leading:7,value:1;		  \
		operator bool()	{return (value!=0);}			   \
		bool operator = (bool v)	{return ((value=v)!=0);}\
				}	n7;									     \
	};														  \

#ifdef	__MSVC__
//Built in enums are not efficiently stored
//This mechanism allows us to compact them into bitfields as needed.
//


#define	FIRSTFIELD(size,Type,name,maxbitnum)		\
BITFIELD_AGGREGATOR	{								 \
	struct	OverView								  \
	{												   \
		typedef	size	ovtype;							\
		ovtype	value;									 \
	}	overview_##name;								  \
	struct	T_##name{									   \
		OverView::ovtype									\
			value:(maxbitnum+1),							 \
			trailing:1;										  \
		operator Type()	{return (Type(value));}				   \
		Type operator = (Type v)	{return (Type(value=v));}   \
		BITFIELD_COPY(T_##name)									 \
	}	name;



#define	SPAREFIELD(minbitnum,maxbitnum)				\
struct	Spare{										\
	OverView::ovtype								\
		leading:minbitnum,							\
		value:maxbitnum+1-minbitnum;				\
	}	spare;										\
} ;

#define	LASTFIELD(Type,name,minbitnum,maxbitnum)		 	\
struct	T_##name{										 	\
	OverView::ovtype									 	\
		leading:minbitnum,								 	\
		value:maxbitnum+1-minbitnum;					 	\
	operator Type()	{return (Type(value));}				 	\
	Type operator = (Type v)	{return (Type(value=v));}	\
		BITFIELD_COPY(T_##name)								\
	}	name;											 	\
} ;

#define	BOOLFIELD(name,minbitnum)						\
struct	T_##name{										 \
		OverView::ovtype								  \
			leading:minbitnum,							   \
			value:1,										\
			trailing:1;										 \
		operator bool()	{return (value!=0);}				  \
		bool operator = (bool v)	{return ((value=v)!=0);}   \
		BITFIELD_COPY(T_##name)									\
		}	name;



#define	BITFIELD(Type,name,minbitnum,maxbitnum)			\
struct	T_##name{										 \
		OverView::ovtype								  \
			leading:minbitnum,							   \
			value:(maxbitnum+1-minbitnum),					\
			trailing:1;										 \
		operator Type()	{return (Type(value));}				  \
		Type operator = (Type v)	{return (Type(value=v));}  \
		BITFIELD_COPY(T_##name)									\
		}	name;


#else
//rely on built in enums being efficient:
#define	FIRSTFIELD(size,Type,name,maxb)		Type	name:(maxb+1) ;
#define	BITFIELD(Type,name,minb,maxb)		Type	name:(maxb+1-minb);
#define	SPAREFIELD(minb,maxb)		//NOWT
#define	LASTFIELD(Type,name,minb,maxb)		Type	name:(maxb+1-minb);
#define	ONLYFIELD(size,Type,name)			Type	name
#endif
#endif
