//------------------------------------------------------------------------------
//Filename       angles.h
//System         
//Author         Paul.   
//Date           Tue 22 Aug 1995
//Description    
//------------------------------------------------------------------------------

#ifndef	ANGLES_Included
#define	ANGLES_Included

enum	AnglesFract			{ANGLES_FRACT=32768};
enum	AnglesShift			{ANGLES_SHIFT=15};
enum	AnglesShiftTwice	{ANGLES_SHIFT_TWICE=30};

inline	int	operator	/	(int i,AnglesFract)	{return((i+16384)>>15);}
inline	int	operator	>>	(int i,AnglesShift)	{return((i+16384)>>15);}

inline	SLong	operator	/	(SLong i,AnglesFract)	{return((i+16384)>>15);}
inline	SLong	operator	>>	(SLong i,AnglesShift)	{return((i+16384)>>15);}
inline	ULong	operator	/	(ULong i,AnglesFract)	{return((i+16384)>>15);}
inline	ULong	operator	>>	(ULong i,AnglesShift)	{return((i+16384)>>15);}

enum	Angles
{
	ANGLES_0Deg = 0x00000,
	ANGLES_BitDeg = 0x00001,
	ANGLES_FifthDeg = 0x00020,
	ANGLES_ThirdDeg = 0x0003d,
	ANGLES_HalfDeg = 0x0005B,
	ANGLES_1Deg = 0x000B7,
	ANGLES_1_33Deg = 0x000f2,
	ANGLES_1_67Deg = 0x00130,
	ANGLES_2Deg = 0x0016C,
	ANGLES_2_5Deg = 0x001C7,
	ANGLES_3Deg = 0x00222,
	ANGLES_3_5Deg = 0x0027D,
	ANGLES_4Deg = 0x002D8,
	ANGLES_5Deg = 0x0038D,
	ANGLES_5_5Deg = 0x003e9,
	ANGLES_6Deg = 0x00444,
	ANGLES_7Deg = 0x004FA,
	ANGLES_8Deg = 0x005b0,
	ANGLES_9Deg = 0x00666,
	ANGLES_10Deg = 0x0071C,
	ANGLES_11Deg = 0x007d2,
	ANGLES_12Deg = 0x00889,
	ANGLES_13Deg = 0x0093f,
	ANGLES_14Deg = 0x009f5,
	ANGLES_15Deg = 0x00AAB,
	ANGLES_16Deg = 0x00b60,
	ANGLES_18Deg = 0x00ccd,
	ANGLES_20Deg = 0x00E39,
	ANGLES_22Deg = 0x00FA5,
	ANGLES_25Deg = 0x011c7,
	ANGLES_30Deg = 0x01555,
	ANGLES_34Deg = 0x0182e,
	ANGLES_35Deg = 0x018E4,
	ANGLES_40Deg = 0x01C72,
	ANGLES_45Deg = 0x02000,
	ANGLES_50Deg = 0x0238E,
	ANGLES_60Deg = 0x02AAB,
	ANGLES_70Deg = 0x031C7,
	ANGLES_70_5Deg = 0x03222,
	ANGLES_75_5Deg = 0x035b0,
	ANGLES_78_5Deg = 0x037d2,
	ANGLES_80Deg = 0x038E4,
	ANGLES_80_4Deg = 0x0392c,
	ANGLES_81_8Deg = 0x03a2b,
	ANGLES_82_8Deg = 0x03ae1,
	ANGLES_83_6Deg = 0x03b73,
	ANGLES_84_3Deg = 0x03bf2,
	ANGLES_84_8Deg = 0x03c4d,
	ANGLES_85Deg = 0x03C72,
	ANGLES_90Deg = 0x04000,
	ANGLES_100Deg = 0x0471c,
	ANGLES_110Deg = 0x4e39,
	ANGLES_112Deg = 0x04fa5,
	ANGLES_120Deg = 0x05555,
	ANGLES_135Deg = 0x06000,
	ANGLES_140Deg = 0x0638e,
	ANGLES_150Deg = 0x06AAB,
	ANGLES_153_4Deg = 0x06d16,
	ANGLES_160Deg = 0x071c7,
	ANGLES_161_5Deg = 0x072d8,
	ANGLES_165Deg = 0x07555,	
	ANGLES_170Deg = 0x078E4,
	ANGLES_180BareDeg = 0x07fff,
	ANGLES_180Deg = 0x08000,
	ANGLES_186Deg = 0x08444,
	ANGLES_195Deg = 0x08aab,
	ANGLES_210Deg = 0x09555,
	ANGLES_215Deg = 0x098e4,
	ANGLES_225Deg = 0x0A000,
	ANGLES_235Deg = 0x0A71C,
	ANGLES_240Deg = 0x0AAAB,
	ANGLES_260Deg = 0x0b8e4,
	ANGLES_270Deg = 0x0C000,
	ANGLES_275Deg = 0x0C38e,
	ANGLES_280Deg = 0x0C71C,
	ANGLES_285Deg = 0x0CAAB,
	ANGLES_290Deg = 0x0CE39,
	ANGLES_300Deg = 0x0D555,
	ANGLES_305Deg = 0x0D8E4,
	ANGLES_310Deg = 0x0DC72,
	ANGLES_315Deg = 0x0E000,
	ANGLES_320Deg = 0x0E38E,
	ANGLES_330Deg = 0x0EAAB,
	ANGLES_340Deg = 0x0F1C7,
	ANGLES_345Deg = 0x0F555,
	ANGLES_347Deg = 0x0F6C1,
	ANGLES_350Deg = 0x0F8E4,
	ANGLES_355Deg = 0x0FC72,
	ANGLES_357Deg = 0x0FDDE,
	ANGLES_358Deg = 0x0FE94,
	ANGLES_359Deg = 0x0FF4A,
	ANGLES_359halfDeg = 0x0FFA5,
	
	ANGLES_N	 = 0x00000,
	ANGLES_NE	 = 0x02000,
	ANGLES_E	 = 0x04000,
	ANGLES_SE	 = 0x06000,
	ANGLES_S	 = 0x08000,
	ANGLES_SW	 = 0x0A000,
	ANGLES_W	 = 0x0C000,
	ANGLES_NW	 = 0x0E000,

	BESTCLIMBPITCH = ANGLES_12Deg,

 	MAXROLL 		= 0x031C7,
// 	MAXCOMBATROLL   = 13653,
 	MAXCOMBATROLL   = 15110,

	ANGLES_FIDDLEMAX = 0x0FFFF
};


//USE ONLY WHEN DESPARATE

#define	ANGLES_CARDINAL		0x000C0

#define	ANGLES_RTO7BIT		(3+6)

#define	ANGLES_SA8BITTO10DEG(areg)		(areg)<<=3
 
#define	ANGLES_MAKEINDEX(inreg)\
		(inreg) >>= 5;\
		(inreg) &= 0x0FFFE;


class	ANGLES
{
	typedef SWord IType;
	typedef SLong XType;
	IType	val;
	ANGLES()			{}
	ANGLES(Angles a)	{val=IType(a);}
	ANGLES& operator= (ANGLES a) {return val=a.val;}
	ANGLES& operator= (Angles a) {return val=IType(a);}
	operator Angles()const {return Angles(val);}
};

class	ANGLESAggri
{	//Angles used in aggrigate initialiser.
	//I assume this means its a constant value
	//so I AM NOT SUPPLYING RUN-TIME ASSIGNMENT OPERATORS!
	ANGLES::IType	val;
	operator Angles()const {return Angles(val);}
	operator ANGLES()const {return ANGLES(val);}
}

inline Angles operator + (Angles a,Angles b)
{return (ANGLES::XType)a+(ANGLES::XType)b;}
inline Angles operator - (Angles a,Angles b)
{return (ANGLES::XType)a-(ANGLES::XType)b;}
inline Angles operator += (Angles& a,Angles b)
{return (ANGLES::XType&)a+=(ANGLES::XType)b;}
inline Angles operator -= (Angles& a,Angles b)
{return (ANGLES::XType&)a-=(ANGLES::XType)b;}

inline Angles operator ++ (Angles a&)
{return (++(ANGLES::XType&)a);}
inline Angles operator ++ (Angles a&,int)
{return ((ANGLES::XType&)a)++;}
inline Angles operator -- (Angles a&)
{return (--(ANGLES::XType&)a);}
inline Angles operator -- (Angles a&,int)
{return ((ANGLES::XType&)a)--;}

inline bool operator == (Angles& a,Angles b)
{return (ANGLES::IType)(a-b)==0;}
inline bool operator != (Angles& a,Angles b)
{return (ANGLES::IType)(a-b)!=0;}

//These tests use the relationship Masked(a-b)<0 rather than 
//the relationship (a<b)
//This means it 'works' for signed and unsigned cases (I hope)
//always covering 180deg as less and 180deg as greater
//
//The difference is that in the OLD system,
//a<90deg covered 0..89deg
//a<<90deg covered -180 to 89
//In the new system,
//a<90deg covers -90deg to 89deg
//Every case will have to be compiled on its merits...

inline bool operator < (Angles& a,Angles b)
{return (ANGLES::IType)(a-b)<0;}
inline bool operator <= (Angles& a,Angles b)
{return (ANGLES::IType)(a-b)<=0;}
inline bool operator > (Angles& b,Angles a)
{return (ANGLES::IType)(a-b)>0;}
inline bool operator >= (Angles& b,Angles a)
{return (ANGLES::IType)(a-b)>=0;}
