//------------------------------------------------------------------------------
//Filename       modvec.h
//System         
//Author         Andrew McRae
//Date           Mon 6 Jan 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	MODVEC_Included
#define	MODVEC_Included

#define	DEFAULT_MODVEC 0

#define F1PIE2	1.570796326795
#define FPIE	3.14159265359
#define F3PIE2	4.712388980385
#define F2PIE	6.28318530718

#define FANGLE_330	5.759586532

//enum {MIN_TEMP = 255, MAX_TEMP = 310};
//typedef double FP, *PFP;
//class	FP
//{
//	Float	val;
//public:
//	FP(Float v=0.0)	{val=v;}
//	FP(Angles a)		{val=a;}
//	FP(ANGLES a)		{val=a;}
//	int operator=(int i)	{val=i;return i;}
//	Float operator=(FP f)	{val=f.val;return val;}
//	Float operator=(const Float f) {return val=f;}
//	Angles	operator=(Angles a) {val=(int)a;return a;}
//	ANGLES	operator=(ANGLES a) {val=(int)a;return a;}
//	operator Float& ()		{return val;}
//};

typedef float FP, *PFP;

//DeadCode AMM 01Jul98 struct	CleverFP
//DeadCode AMM 01Jul98 {
//DeadCode AMM 01Jul98 	static CleverFP* FPLISTER;
//DeadCode AMM 01Jul98 	static int count;
//DeadCode AMM 01Jul98 	CleverFP* next;
//DeadCode AMM 01Jul98 	union
//DeadCode AMM 01Jul98 	{
//DeadCode AMM 01Jul98 		struct
//DeadCode AMM 01Jul98 		{
//DeadCode AMM 01Jul98 			const char* s;
//DeadCode AMM 01Jul98 			int i1;
//DeadCode AMM 01Jul98 		};
//DeadCode AMM 01Jul98 		FP v[1];
//DeadCode AMM 01Jul98 	};
//DeadCode AMM 01Jul98 	CleverFP()
//DeadCode AMM 01Jul98 		{	next=FPLISTER;
//DeadCode AMM 01Jul98 			FPLISTER=this;
//DeadCode AMM 01Jul98 			if (count++==0x12345678)
//DeadCode AMM 01Jul98 				count=count;
//DeadCode AMM 01Jul98 		}
//DeadCode AMM 01Jul98 	void operator = (FP f)	{v[0]=f;}
//DeadCode AMM 01Jul98 	void operator += (double f)	{v[0]+=f;}
//DeadCode AMM 01Jul98 //	void operator += (long double f)	{v+=f;}
//DeadCode AMM 01Jul98 //	void operator *= (double f)	{v*=f;}
//DeadCode AMM 01Jul98 //	void operator -= (double f)	{v-=f;}
//DeadCode AMM 01Jul98 //	void operator = (long double f)	{v=f;}
//DeadCode AMM 01Jul98 //	void operator = (int f)	{v=f;}
//DeadCode AMM 01Jul98 //#ifdef	RANGES_Included
//DeadCode AMM 01Jul98 //	bool operator < (ranges	 f)	{return (v<f);}
//DeadCode AMM 01Jul98 //#endif
//DeadCode AMM 01Jul98 //	bool operator > (int	 f)	{return (v>f);}
//DeadCode AMM 01Jul98 	void	setstring(const char* st,int flag=0xffffffff) {i1=flag;s=st;}
//DeadCode AMM 01Jul98 	operator FP() {return v[0];}
//DeadCode AMM 01Jul98 //	operator int () {return (int)v;}
//DeadCode AMM 01Jul98 //	operator long () {return (int)v;}
//DeadCode AMM 01Jul98 //	operator FP& () {return v;}
//DeadCode AMM 01Jul98 };
//DeadCode AMM 01Jul98 //inline void	operator=(FP& f,CleverFP& v) {f=v.v;}

typedef struct _fcrd {
			FP	x,y,z;
} FCRD, *PFCRD;

typedef struct _fcrdlong {
			Float x,y,z;
} FCRDlong, *PFCRDlong;
//DeadCode AMM 01Jul98 typedef FP& FPrefbad;
//DeadCode AMM 01Jul98 struct Clever_fcrd {
//DeadCode AMM 01Jul98 			CleverFP me;
//DeadCode AMM 01Jul98 			_fcrd f;
//DeadCode AMM 01Jul98 			FPrefbad	x,y,z;
//DeadCode AMM 01Jul98 			Clever_fcrd(): x(f.x),y(f.y),z(f.z)
//DeadCode AMM 01Jul98 			{me.setstring("V",0xfffffffE);}
//DeadCode AMM 01Jul98 			Clever_fcrd& operator=(_fcrd& s) {f=s;return *this;}
//DeadCode AMM 01Jul98 			operator _fcrd& () {return f;}
//DeadCode AMM 01Jul98 			void	setstring(const char*s) {me.setstring(s,0xfffffffe);}
//DeadCode AMM 01Jul98 };

typedef struct _fori {
	_fcrd x,y,z;
} FORI, *PFORI;

//DeadCode AMM 01Jul98 typedef _fcrd&	fcrdrefbad;
//DeadCode AMM 01Jul98 struct Clever_fori {
//DeadCode AMM 01Jul98 	CleverFP me;
//DeadCode AMM 01Jul98 	_fori f;
//DeadCode AMM 01Jul98 	fcrdrefbad x,y,z;
//DeadCode AMM 01Jul98 	Clever_fori():x(f.x),y(f.y),z(f.z)	{me.setstring("O",0xfffffffd);}
//DeadCode AMM 01Jul98 	operator _fori& () {return f;}
//DeadCode AMM 01Jul98 	void	setstring(const char*s) {me.setstring(s,0xfffffffd);}
//DeadCode AMM 01Jul98 };



//DeadCode AMM 01Jul98 #define	VARSCLASSDERIVED(name,name2)
//DeadCode AMM 01Jul98 class	name##vars1:public name2
//DeadCode AMM 01Jul98 {
//DeadCode AMM 01Jul98 	typedef	CleverFP FP;
//DeadCode AMM 01Jul98 	typedef	Clever_fcrd	  FCRD, *PFCRD;
//DeadCode AMM 01Jul98 	typedef	Clever_fori   FORI, *PFORI;
//DeadCode AMM 01Jul98 };
//DeadCode AMM 01Jul98 class	name##vars:public name##vars1
//DeadCode AMM 01Jul98
//DeadCode AMM 01Jul98 #define	VARSCLASS(name)
//DeadCode AMM 01Jul98 class	name##vars1
//DeadCode AMM 01Jul98 {
//DeadCode AMM 01Jul98 	typedef	CleverFP FP;
//DeadCode AMM 01Jul98 	typedef	Clever_fcrd	  FCRD, *PFCRD;
//DeadCode AMM 01Jul98 	typedef	Clever_fori   FORI, *PFORI;
//DeadCode AMM 01Jul98 };
//DeadCode AMM 01Jul98 class	name##vars:public name##vars1
//DeadCode AMM 01Jul98
//DeadCode AMM 01Jul98 #define	PROCCLASS(name)
//DeadCode AMM 01Jul98 class	name##proc:public name##vars
//DeadCode AMM 01Jul98 {
//DeadCode AMM 01Jul98 	typedef	Float	FP;
//DeadCode AMM 01Jul98 	typedef	_fcrd	  FCRD, *PFCRD;
//DeadCode AMM 01Jul98 	typedef	_fori   FORI, *PFORI;
//DeadCode AMM 01Jul98 };
//DeadCode AMM 01Jul98 class	name:public name##proc


// General conversion macros
#define RPM2RADSPERCSEC(spd) spd * 0.001047197
#define DEGS2ROWAN(ang) (SWord)((SLong)(ang * 182.04444444) & 0xffff)
#define DEGS2RADS(ang) ang / 57.29577951
#define RATEDTORQUE(p,s) ((p*1359.62*6000)/(s*F2PIE))
#define mBARS2PRESSURE(p) (p*0.01)
#define ROWAN2RADS(ang) ((FP)ang /  10430.37835047);
#define FEETPERMIN2MPS(val) (val * 0.00508)
#define FEET2CM(val) (val * 30.48)

void NullVec (FCRD&);
void NullVec (FCRDlong&);
void NullOri (FORI&);
void CopyVec (FCRD&, FCRD&);
void CopyOri (FORI&, FORI&);

#ifdef	__WATCOMC__

// Square Root Function
extern FP FSqrt(FP);
#pragma aux FSqrt parm [8087] = \
"fsqrt";

// Sine Function
extern FP FSin(FP);
#pragma aux FSin parm [8087] = \
"fsin";

// Cosine Function
extern FP FCos(FP);
#pragma aux FCos parm [8087] = \
"fcos";

// Partial Inverse Tangent Function
extern void FPATan(FP& opp, FP& adj, FP& ans);
#pragma aux	FPATan = 				\
"	fld		qword ptr ds:[eax]	"	\
"	fld		qword ptr ds:[ebx]	"	\
"	fpatan						"	\
"	fstp	qword ptr ds:[ecx]	"	\
parm	[eax] [ebx]	[ecx]			\

// X^Y Function
// only works when -1 < y.log2x < 1
extern void FXPowerY (FP& x, FP& y, FP& ans);
#pragma aux FXPowerY = 				\
"	fld		qword ptr ds:[ebx]	"	\
"	fld		qword ptr ds:[eax]	"	\
"	fyl2x						"	\
"	f2xm1						"	\
"	fld1						"	\
"	fadd						"	\
"	fstp	qword ptr ds:[ecx]	"	\
parm	[eax] [ebx] [ecx]			\

#else
#ifdef	__MSVC__

inline FP FSqrt(FP n)
{
	_asm
	{
		fld		n
		fsqrt
		fstp	n
	}
	return n;
}

inline FP FSin(FP n)
{
	_asm
	{
		fld		n
		fsin
		fstp	n
	}
	return n;
}
inline FP FCos(FP n)
{
	_asm
	{
		fld		n
		fcos
		fstp	n
	}
	return n;
}
/*inline FP FPATan(FP opp,FP adj)
{
	FP	ans;
	_asm 
	{
		fld		opp
		fld		adj
		fpatan
		fstp	ans
	}
	return ans;
}*/
inline FP FXPowerY(FP x,FP y)
{
	FP	ans;
	_asm
	{
		fld		x
		fld		y
		fyl2x
		f2xm1
		fld1
		fadd
		fstp	ans
	}
	return ans;
}

#endif
#endif

SWord Rads2Rowan (FP);
FP Rads2Degs (FP);
SWord Degs2Rowan (FP);
FP Degs2Rads (FP);
FP Rowan2Rads (UWord);
FP Rowan2Degs (UWord);

FP Rpm2RadsPerCSec (FP);
SWord	RadPerCSec2RowanPerMin(FP);
SWord	RadPerCSec2RowanPerMin(FP	angle);
SWord	RadPerCSec2DegsPerMin(FP	angle);


FP CalcAngle (FP, FP);

FP VecLen2D (FP, FP);
FP VecLen (FCRD&);

Bool NrmVec2D (FP&, FP&);
Bool NrmVec (FCRD&, FCRD&);

void RotateVec2D (FP&, FP&, FP);

void RotVecXSC (FCRD&, FCRD&, FP, FP);
void RotVecYSC (FCRD&, FCRD&, FP, FP);
void RotVecZSC (FCRD&, FCRD&, FP, FP);

void TnsAxs (FCRD&, FCRD&, FORI&);
void TnsPnt (FCRD&, FCRD&, FORI&);

void AddVec (FCRD&, FCRD&, FCRD&);
void SubVec (FCRD&, FCRD&, FCRD&);

void AddVec (FCRDlong&, FCRDlong&, FCRDlong&);
void SubVec (FCRDlong&, FCRDlong&, FCRDlong&);

void CPrdX(FORI&);
void CPrdY(FORI&);
void CPrdZ(FORI&);
void CPrd (FCRD&, FCRD&, FCRD&);

FP DotPrd (FCRD&, FCRD&);

void RotOriXVec (FORI&, FP);
void RotOriYVec (FORI&, FP);
void RotOriZVec (FORI&, FP);

void SetOri (FORI&, FP, FP, FP);


#endif
