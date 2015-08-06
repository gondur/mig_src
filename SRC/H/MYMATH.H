//------------------------------------------------------------------------------
//Filename       math.h
//System         
//Author         Jim Taylor
//Date           Thu 21 Sep 1995
//Description    Starter for 10... base 10 that is!
//------------------------------------------------------------------------------
#ifndef	MATH_Included
#define	MATH_Included

//stuff stolen from the system includes - why we have to use system file names - who knows
extern "C" {
extern double	pow( double __x, double __y );
extern double	exp( double __x );
}


#define	DEFAULT_MATH 0

#include "myangles.h"

#include	"mathasm.h"

enum	RndVal	{	RndValMIN=0,
					RND10PC=6553,
					RND25PC=16384,
					RND33PC=21843,	//CSB 28/06/99	
					RND50PC=32768,
					RND67PC=43686,	//CSB 28/06/99	
					RND75PC=49152,
					RND90PC=58982,
					RND99PC=64880,//RDH 06Oct96
					RndValMAX=65535};

class	MathLib													//PD 29Nov95
{
static	UWord	bval,cval;
		UWord	rndcount;											//ARM 03Sep96
static	SWord	matan[],
				sincos_table[],
				tan_table[];
static	UWord	rndlookup[],
				Days_in_Month[];
public:
	enum	{MAX_RND=64};

	UWord SavedRndCount;										//ARM 04Sep96

	MathLib ()
	{
		rndcount = 0;											//ARM 25Oct96
		MaxRndCount = 0;										//ARM 25Oct96
	}

	UWord GetRndCount () { return rndcount; }					//ARM 03Sep96
	void ResetRndCount () { rndcount = 0; }						//ARM 03Sep96
	UWord MaxRndCount;											//ARM 03Sep96
	UWord thisRndCount;											//ARM 03Sep96

	void TestRndCount ()										//ARM 03Sep96
	{															//ARM 03Sep96
		if (thisRndCount > MaxRndCount)							//ARM 03Sep96
			MaxRndCount = thisRndCount;							//ARM 03Sep96
	}															//ARM 03Sep96

	UWord MathLib::GetRndLookUp (UWord n);						//ARM 04Sep96
	void MathLib::SetRndLookUp (UWord n, UWord val);			//ARM 04Sep96

	UWord Getbval() { return bval; }							//ARM 04Sep96
	UWord Getcval() { return cval; }							//ARM 04Sep96

	void Setbval(UWord val) { bval = val; }					//ARM 04Sep96
	void Setcval(UWord val) { cval = val; }					//ARM 04Sep96

	enum	SignType {POSITIVE=0,NEGATIVE=-1,SIGN_ALIGN=0x7fff};
//DeadCode RDH 30Nov95 	void	sin_cos(ANGLES, SWord&, SWord& );
	ANGLES	arcsin(SWord);
	ANGLES   arccos(SWord);

	ANGLES	high_arc_sin(SWord );								//PD 23May96
	ANGLES	high_arc_cos(SWord );								//PD 23May96

	SWord	tan(ANGLES);
	SLong	hightan(ANGLES ang);

	ULong	distance3d(SLong,SLong,SLong);
	UWord	Distance_Unsigned(UWord,UWord);
ULong	a2iend(string&	srctxt);
ULong	a2iend(string&	srctxt,ULong& datalength);
void	sin_cos(ANGLES ang, SWord& sin_ang, SWord& cos_ang);
void	high_sin_cos(ANGLES ang, SWord& sin_ang, SWord& cos_ang);
ANGLES	arctan(SLong dx, SLong dy);
ANGLES	HighArcTan(SLong, SLong);								//PD 04Jul96
//UWord   Distance_Unsigned(UWord dx, UWord dy);
void    InterceptHdg(ULong Wx1, ULong Wz1, ULong Wx2, ULong Wz2, ULong &dist, UWord &hdg);
ULong   Distance2d(SLong dx, SLong dy);
ULong	DistAbsSum(SLong x,SLong y,SLong z=0,SLong w=0);


void	HighIntercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,SWord &HdgIntercept,SWord &PitchIntercept);		//RDH 01Dec95
void	HighIntercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,ANGLES &HdgIntercept,ANGLES &PitchIntercept)
		{HighIntercept(deltax,deltay,deltaz,Range,
					(SWord&)HdgIntercept,(SWord&)PitchIntercept);}

void	Intercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,SWord &HdgIntercept,SWord &PitchIntercept);		//RDH 01Dec95
void	Intercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,ANGLES &HdgIntercept,ANGLES &PitchIntercept)
		{Intercept(deltax,deltay,deltaz,Range,
					(SWord&)HdgIntercept,(SWord&)PitchIntercept);}

static	void 	Pos (SWord inputvar, UWord &posvar,SWord &signvar)		//JIM 02May96
{
	signvar=mathlib_w_getsign(inputvar);
	posvar=mathlib_w_applysign(inputvar,signvar);
}
static	void 	Pos (SLong inputvar, ULong &posvar,SLong &signvar)		//JIM 02May96
{
	signvar=mathlib_l_getsign(inputvar);
	posvar=mathlib_l_applysign(inputvar,signvar);
}
static	SWord 	GetSign (SWord inputvar)
{	return(mathlib_w_getsign(inputvar));}
static	SLong 	GetSign (SLong inputvar)
{	return(mathlib_l_getsign(inputvar));}
static	SWord 	GetSign (ANGLES inputvar)
{	return(mathlib_w_getsign(inputvar));}

static	UWord 	UseSign (SWord inputvar, SWord signvar)
{	return(mathlib_w_applysign(inputvar,signvar));}
static	SLong 	UseSign (SLong inputvar, SLong signvar)
{	return(mathlib_l_applysign(inputvar,signvar));}				//JIM 02May96

static	UWord	AbsSign(SWord	inputvar)
{	return(UseSign(inputvar,GetSign(inputvar)));}
static	SLong	AbsSign(SLong	inputvar)
{	return(UseSign(inputvar,GetSign(inputvar)));}
static	UWord	AbsSign(ANGLES	inputvar)
{	return(UseSign(inputvar,GetSign(inputvar)));}

SWord MonthFromDays (SWord daysinyear, SWord &daysinfullmonth,SWord leapyear );
void DateFromSecs (SLong secs, SWord &day, SWord &month, SWord &year);
SWord YearFromDays (SWord day, SWord &daysinfullyears, SWord &leapyear);
SWord YearFromSecs (SLong secs);
void TimeFromSecs (SLong secs, SWord &hr, SWord &mins);
void SunPosFromSecs(SLong secs, ANGLES& pos);					//PD 22Apr96


SWord DofCampFromSecs (SLong secs,SLong beginning);

RndVal	rnd();
//DeadCode JIM 12Jul96 SWord	rnd(SWord	M)	{return (SWord) ( ((SLong)M*rnd()) >>16);}
SLong	rnd(SLong	M)	{return MULSHSIN(rnd(),M,16);}
Angles	rnd(ANGLES M)	{return (Angles)MULSHSIN(rnd(),M,16);}
};

inline	Angles	operator + (ANGLES a,RndVal b)	{return (Angles)((SWord)a+(SWord)b);}
//inline	Angles	operator += (ANGLES a,SLong b)  {return (Angles)(a=((SWord)a+(SWord)b));}

extern	MathLib	Math_Lib;										//PD 29Nov95
#ifndef	__BCPLUSPLUS__
inline Float FPATan(Float opp,Float adj)
{
	Float	ans;
	_asm
	{
		fld		opp
		fld		adj
		fpatan
		fstp	ans
	}
	return ans;
}

inline Float FPACos(Float x)	//returns arccos(x) in radians
{
	Float ans;

	_asm
	{
		fld1;
		fld x;
		fmul st,st(0);
		fld st;
		fsubp st(2),st;
		fdivp st(1),st;
		fsqrt;
		fld1;
		fpatan;
		fstp ans;
	}

	return ans;
}

#endif



#endif

