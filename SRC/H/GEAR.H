//------------------------------------------------------------------------------
//Filename       gear.h
//System         
//Author         Andrew McRae
//Date           Thu 27 Feb 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	GEAR_Included
#define	GEAR_Included

#define	DEFAULT_GEAR 0

enum UC_STATUS
{
	OFFGROUND,
	TOUCHING,
	BOTTOMEDOUT,
	ALLBOTTOMEDOUT,
	CRASHED,
	UNDEFINED
};

enum GEAR_IDENT
{
	NOSE,
	TAIL,
	PORT,
	STBD
};

// Undercarraige
class Gear {

public:

	GEAR_IDENT Ident;

	PMODEL pModel;

	// suspension
//DeadCode CSB 11/01/99		FP yDamping;
//DeadCode CSB 11/01/99		FP rotDamping;
//DeadCode CSB 11/01/99		FP Stiffness;
	FP CStiffness;
	FP CDamping;

	// tyres & brakes
//DeadCode CSB 11/01/99		FP RollRes;
//DeadCode CSB 11/01/99		FP xVelOffset;
//DeadCode CSB 11/01/99		FP zVelOffset;
//DeadCode CSB 11/01/99		FP SideGrip;
//DeadCode CSB 11/01/99		FP Brakes;
//DeadCode CSB 11/01/99		FP TyreGrip;
	FP RollRes;
	FP CFriction;
	FP CBrake;

	// in ac coords
	FCRD pos0;
	FCRD pos1;
	FP LegLength;
	FCRD UnitVec;
	FCRD LegVec;

	FCRD GroundForce;
	FCRD LegForce;
	FCRD TyreForce;

	FP LegPos;		//[0,1]
	FP OldLegPos;	//[0,1]
	FCRD WheelPos;

	FCRD IntPos;
	FP IntL;


//DeadCode CSB 11/01/99		// in world coords
//DeadCode CSB 11/01/99		FCRD wpos0;
//DeadCode CSB 11/01/99		FCRD wpos1;
//DeadCode CSB 11/01/99		FP g0;	// ground height @ wpos0/1
//DeadCode CSB 11/01/99		FP g1;

	// Note:
	// Max(1) is fully pushed in.
	// Min(0) is fully extended.

	Bool Touched;
//DeadCode CSB 11/01/99		FCRD LegForce;
//DeadCode CSB 11/01/99		FCRD TyreForce;
//DeadCode CSB 11/01/99	
//DeadCode CSB 11/01/99		FCRD oldtyremoment;

	void SetDimensions (FP, FP, FP, FP, FP, FP);
	void SetSuspension (FP, FP);
	void SetTyres (FP, FP, FP);

	Bool CalcIntL (UByte*);
	void CalcIntPos ();

//DeadCode CSB 01/02/99		void CalcLegForce ();
//DeadCode CSB 01/02/99		void CalcTyreForce ();

	void CalcLegForce_Reaction(AirStrucPtr const ControlledAC, UByte* Texture);
	void Gear::CalcTyreSideForce (AirStrucPtr const ControlledAC, FP TotalReaction, FP forcex, UByte Texture);
//DeadCode DAW 26Feb99 	void CalcTyreSideForce(AirStrucPtr const ControlledAC, FP TotalReaction);

//TempCode ARM 10Mar97 	void CalcGPos (FCRD&);
//TempCode ARM 10Mar97 	void CalcWorldGPos (FCRD&);
//TempCode ARM 10Mar97 	void CalcWPos (FCRD&);
//TempCode ARM 10Mar97 	void CalcWorldWPos (FCRD&);

	Gear (PMODEL, GEAR_IDENT);
	~Gear ();

	LINKEDLIST<Gear> List;

};
typedef class Gear  GEAR, *PGEAR, **PPGEAR;
//TempCode ARM 10Mar97 void CalcOriFromPoints (FORI& ori, FCRD& p1, FCRD& p2, FCRD& p3, Bool Tail);

#endif

