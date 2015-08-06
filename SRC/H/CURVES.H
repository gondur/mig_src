//------------------------------------------------------------------------------
//Filename       curves.h
//System         
//Author         Andrew McRae
//Date           Mon 10 Feb 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	CRSC_Included
#define	CRSC_Included

#include "link.h"

#define	DEFAULT_CRSC 0

#define CURVENAMESIZE 12
#define LINESIZE 256

#define CURVEMIN(a,b) ((a)<=(b) ? (a) : (b))

typedef struct CurvePoint {

	FP index;
	FP value;

} CURVEPNT, *PCURVEPNT;

// index types
#define IDT_WRAP 1
#define IDT_LIMIT 2

typedef class View *PVIEW;

class Curve {

public:

	ULong Active;

	ULong cPoints;
	ULong iPoint;

	PCURVEPNT CurveData;

	FP MinIndex;
	FP MaxIndex;
	FP DeltaIndex;

//#ifdef CURVEEDITOR
	FP MinValue;	// ceditor only
	FP MaxValue;
//#endif

	UWord IndexType;

	char AircraftName [CURVENAMESIZE];
	char CurveName [CURVENAMESIZE];

	Curve (char*, char*, ULong, FP, FP, UWord, PCURVEPNT);
	~Curve ();

	LINKEDLIST<Curve> List;

	void AddPoint (FP, FP);
	FP GetValue (FP);
	Bool GetIndex (FP, FP&);
	Bool GetClIndex (FP, FP&);
	void GetMaxValue (FP& value, FP& index);

#ifdef CURVEEDITOR
	// ceditor functions - exist in ceditor.cpp
	void CalcCurveLimits (FP&, FP&, FP&, FP&);
	void CalcCurveLimitsAll (FP&, FP&, FP&, FP&);
	void DrawGrads (PVIEW);
	void DrawCurve (PVIEW);
	void UnDrawCurve (PVIEW);
	ULong movepoint (ULong);
	ULong addpoint (ULong);
	ULong deletepoint (ULong);
	ULong DuplicateCl (ULong);

#endif

};
typedef	 Curve CURVE, *PCURVE, **PPCURVE;
typedef class CurveResource {

public:

	PCURVE pCurves;

	CurveResource ();
	~CurveResource ();

	PCURVE FindCurve (char*, char*);

} CRSC, *PCRSC;

extern CurveResource _CurveRsc;

// Curve Data File Setup Functions

void LoadCurvesCOMM ();

void LoadCurvesF86E ();
void LoadCurvesMIG15 ();
void LoadCurvesF84E ();
void LoadCurvesF80C ();
void LoadCurvesF51D ();
void LoadCurvesF9F2 ();

//DeadCode CSB 27/10/98	void LoadCurvesATMOS ();
void LoadCurvesF94A ();
void LoadCurvesF8 ();
void LoadCurvesF82G ();
void LoadCurvesYAK9 ();
void LoadCurvesF4U5 ();
void LoadCurvesSFURY ();
void LoadCurvesFFLY ();
void LoadCurvesA1 ();

#endif
