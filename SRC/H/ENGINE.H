//------------------------------------------------------------------------------
//Filename       engine.h
//System         
//Author         Andrew McRae
//Date           Thu 24 Apr 1997
//Description    
//------------------------------------------------------------------------------

#ifndef	ENGINE_Included
#define	ENGINE_Included


enum ENGINE_TYPE
{
	ET_VOID,
	ET_PISTON,
	ET_JET
};

class Engine {

public:

	ENGINE_TYPE Type;

	PMODEL pModel;

	// general
	FP Speed; // rads per centisec									//Save for Prop Anim
	FP SpeedRpm;
	FP Torque;	// piston or turbo prop
	FP Thrust;
	FP MaxThrust;
	FP IdleSpeed;
	PTHRUSTPOINT pThrustPoint;

	// Jet stuff
	FP T100;
	FP Rpm100;
	FP OneOverMoI;
	PCURVE MachFact;
	PCURVE ThrustRpm;
	PCURVE WindMillDrag;
	PCURVE WindMillRpm;
	Bool EngineOut;

	// Prop stuff
	FP p0;
	FP MoI;
	FCRD PropInertia;
	FP BladeArea;
	FP GearRatio;	// (prop speed / engine speed)
	FP BladeRadius;
	FP PropInc;
	FP PropVel;			//Speed of airflow through prop		(cm/csec) 	/CSB
	FP SlipVel;			//Speed of airflow in slipstream	(cm/csec)	/CSB
	FP SlipRot;			//Rotation of airflow in slipstream	(Rads/csec)	/CSB
	FP RotateDirection;	// 1 = Clockwise from behind, -1 = AntiClockwise from behind	//Save
	FCRD moment;	//Gyroscopic effect of prop

	PCURVE pPower100;
	PCURVE pPower0;
	PCURVE pPowerAlt;		//Low Blower
	PCURVE pPowerAltSuper;	//High Blower
//DeadCode CSB 28/04/99		PCURVE pPropEff;
//DeadCode CSB 28/04/99		PCURVE pPropTq;
//DeadCode AMM 29Jun99 	FP EngineCount;
	int HighBlowerAlt;			//CSB //Altitude at which supercharger changes to high gear
	int LowBlowerAlt;			//CSB //Altitude at which supercharger changes to low gear
	Bool BlowerHigh;			//CSB //TRUE for High gear - FALSE for low gear
	// for printing
	FP Power, Power100, Power0;//, J, eff;						//AMM 29Jun99
//DeadCode AMM 29Jun99 	FP Power, Power100, Power0, J, eff;

	void ProcessPistonEngine (AirStrucPtr const ControlledAC);
	void ProcessJetEngine (AirStrucPtr const ControlledAC);

	Engine (PMODEL, ENGINE_TYPE, FP, FP, FP, PCURVE, PCURVE, PCURVE, PCURVE);	// Jet
	Engine (PMODEL, ENGINE_TYPE);	// Piston
	~Engine ();

//DeadCode CSB 12/11/98		void SetNewJetVars (FP _p0, FP _p1, FP chokemach) { p0 = _p0 * 4.44898; p1 = _p1 * 4.44898; ChokeMach = chokemach;}

	void NullThis ();

	LINKEDLIST<Engine> List;

	void SetThrustPoint (PTHRUSTPOINT thrust) { pThrustPoint = thrust; }

//DeadCode CSB 12/11/98		void CalcJetThrust (AirStrucPtr const ControlledAC);

};
typedef class  Engine ENGINE, *PENGINE, **PPENGINE;

#endif
