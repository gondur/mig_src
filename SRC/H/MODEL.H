//------------------------------------------------------------------------------
//Filename       model.h
//System         
//Author         Andrew McRae
//Date           Tue 7 Jan 1997
//Description    
//------------------------------------------------------------------------------
//variables commented to indicate action required for replay, rdh
//				save			need to save the variable in the replay file
//				set by ***		use the function *** to set the variable
//				unchanged		the variable, once set is never changed
//				zero			the variable should be zeroed on replaying 
//				transient		don't bother with this variable, it is a working variable




#ifndef	MODEL_Included
#define	MODEL_Included

typedef class Ctrl *PCTRL;
typedef class NewCtrl *PNEWCTRL;
typedef class Surface *PSURFACE;
typedef class MainPlane *PMAINPLANE;
typedef class Cylinder *PCYLINDER;
//DeadCode CSB 98	typedef class MassPoint *PMASSPOINT;
//DeadCode RDH 10Sep98 typedef class DragPoint *PDRAGPOINT;
typedef class ThrustPoint *PTHRUSTPOINT;
typedef class AeroDevice *PAERODEVICE;
//DeadCode CSB 26/02/99	typedef class AeroCtrl *PAEROCTRL;
//DeadCode CSB 26/02/99	typedef class AeroCouple *PAEROCOUPLE;
#include "keytest.h"
#include "link.h"
#include "curves.h"

#include "collided.h"
#include "sky.h"
#include "gear.h"
#include "modint.h"
#include "aerodev.h"
#include "acmmodel.h"
#include "engine.h"

//TempCode ARM 02May97 #include "flymodel.h"
#include "modinst.h"

#include "animdata.h"

#include "3DCode.h"

#define	DEFAULT_MODEL 0

#define FRAMESPERCALC 128		// This is the number of operations of the flight model per 
								// calculation of atmosphere, fuel burn, etc.
#define EVERY512cs 0x00ff											  //DAW 02/07/99
#define EVERY256cs 0x007f
#define EVERY64cs  0x001f
#define EVERY8cs   0x0003

#define GRAVITY 0.098065

#define AILERONCTRL (FP)0.35	// 0.15 24/7/97

//#define MAXGROUNDHEIGHT 275000
#define MAXAIRCRAFTSIZE 1200

#define MODLIMIT(val,lim) 	if (val>lim) val=lim; \
							elseif (val<-lim) val=-lim

#define MODSTEPUP(val,step)	if (val>0) val+=step; \
							elseif (val<0) val-=step

#define MODMAXMIN(val,min,max)	if (val<min) val=min; \
								elseif (val>max) val=max

#define CONTROL_RESET 999.999

//#define CALIBRATION_CODE
//rdh moved to monotxt.h#define DISPLAY_MONO_DATA
#define CALC_FORCE_MOMENT_LIMITS
#define FULL_RANGE_JOYSTICK
//#define PRINT_PREFS
//#define COPY_ACM_INTO_PLAYER_AC
//#define LOCK_X_Z_POS
//#define CALC_CG_POS
//#define RESET_AC_POS
//#define WRITE_MODEL_LOG

//remove // for next 3 defines to get calib data
//#define EMIT_HM_DATA
//#define EMIT_DOGHOUSE_DATA
//#define PS_CALCS


#define	ANIM_GEAR_UP	255										//RJS 08Apr98
#define	ANIM_GEAR_DOWN	0										//RJS 08Apr98
#define	ANIM_GEAR_AUTO	-32768									//RJS 08Apr98

enum AIRCRAFT_TYPE
{
	AT_VOID,

	// jets

	AT_F86A,		// Sabre A			North American
	AT_F86E,		// Sabre E			North American
	AT_F86F,		// Sabre F			North American
	AT_MIG15,		// 					Mikoyan-Gurevich
	AT_MIG15BIS,	// 					Mikoyan-Gurevich
	AT_F84E,		// ThunderJet		Republic
	AT_F80C,		// ShootingStar		Lockheed
	AT_F9F2,		// Panther			Grumman
	AT_F8,			// Meteor			Gloster

	// props

	AT_F51D,		// Mustang			North American
	AT_F82G,		// Twin Mustang		North American
	AT_YAK9,		// 					Yakovlev
	AT_F4U5,		// Corsair			Vought
	AT_SFURY,		// SeaFury			Hawker
	AT_FFLY,		// FireFly			Fairey
	AT_A1,			// Sky Raider		Unknown

	//Non flyable
	AT_B26,
	AT_B29,
	AT_T6
};


enum ITERATION_MASK
{
	ALL,
	Y_ONLY,
	XZ_ONLY,
	YZ_ONLY
};


class Model {

public:

	LINKEDLIST<Model> List;

	ULong Ident;
	UWord FrameCount;	// Used to work out the timing for atmosphere, fuel burn worked out 
						// once every n frames
	Bool FirstCycle;	// Used to set engine speed for first model loop
	AIRCRAFT_TYPE Type;

	FCRD PilotEyePos;

	Bool Controlled;
	Bool bACM;
//DeadCode AMM 29Jun99 	Bool bGear;
//DeadCode AMM 29Jun99 	Bool IsDead;//RJS 14Apr98
	Bool Spinning;

//rdh 9/6/98	AirStrucPtr ControlledAC;

//DeadCode AMM 29Jun99 	ULong MODEL_LOOPS;											//UnChanged at the moment
	FP MODEL_DT;												//UnChanged at the moment
	ACMMODEL ACMModel;

	// World Coords

	FCRDlong Pos;													//set by UpdateModel

	FORI Ori;													//set by UpdateModel
	FORI GunOri;													//set by UpdateModel//RDH 30Nov98
	FORI BakOri;												//for gunsight//RJS 25Jun99
	FCRD BakRotVel;												//Save//RJS 25Jun99
	bool fixgunsight;											//CSB 09Jun99
																
	FCRD Vel;	// rel to ground								//set by UpdateModel
	FCRD GunVel;												//OldVel = Vel//RDH 30Nov98
	FP Speed;	// rel to ground								//set by CalcAirVel
	FCRD CheatAcc;	//CSB 09/12/98 //Used to change the speed of the computer controlled aircraft for easy option

	GUST Gust;													//Zero

// for replay purposes when model is not maintained these values are used

	SWord	replay_roll;										//AMM 31Mar99
	SWord	replay_pitch;										//AMM 31Mar99
	SWord	replay_hdg;											//AMM 31Mar99


	// Aircraft Coords

	FCRD RotVel;												//Save

	FCRD AirVel;	// rel to cg								//Save
	FCRD InstAirVel;											//Transient	
	FP AirSpeed;												//Transient
	FP DynamicPressure;											//Might Need for Slats/Airbrakes, Set by CalcAirVel

	FCRD Acc;	// no gravity									//Transient
	FCRD wAcc;													//Not Used ????
	FCRD RotAcc;

	FCRD NettForce;											//transient
	FCRD NettMoment;										//transient

//DeadCode AMM 29Jun99 	FCRD MainForce;											//Transient
//DeadCode AMM 29Jun99 	FCRD MainMoment;										//Transient
//DeadCode AMM 29Jun99 	FCRD StabForce;											//Transient
//DeadCode AMM 29Jun99 	FCRD StabMoment;										//Transient

	FCRD StoresForce;										//Transient
	FCRD StoresMoment;										//Transient

	// Devices
	FP DeltaCl;												//Transient
	FP DeltaCd;												//Transient
	FP DeltaCm;												//Transient
	FP DeltaAlpha;											//Transient

	Bool GearTouched;	// include gear forces if TRUE		//Set by GearCalcs
	Bool GearSkid;
//DeadCode AMM 29Jun99 	Bool Crashed; // Temporary Flag for when uc MaxPos is below ground	//Not used ????
	Bool RestartEngine;	//CSB 25/11/98
//DeadCode AMM 29Jun99 	FP DefHeight;											//Save
	SLong GroundHeight;										//Set by AccurateGroundAltitude

	FP TotalBuffet;

	// joystick
//DeadCode AMM 29Jun99 	enum LANDINGJOLT {NOTHING,JUSTTOUCHED,HASTOUCHED} TouchedOnce;
//DeadCode AMM 29Jun99 	SLong LandingJoltMag;									//Not Used ????

	// from "HaveWeLanded" function, 1 loop behind.
//DeadCode AMM 29Jun99 	ANGLES grndpitch,grndroll;								//Transient
//DeadCode AMM 29Jun99 	ANGLES grndhdg;											//Transient
//DeadCode AMM 29Jun99 	SLong grndheight;										//Transient
//DeadCode AMM 29Jun99 	Collide::Pos landed;

//DeadCode AMM 29Jun99 	SLong CoordRudder;	// k * 16384;						//UnChanged
	FP PowerBoost;											//UnChanged

	// Non Vector Parameters

	FP Mass;												//Save
	FCRD InertiaEmpty;		//CSB  08/09/98		The inertia of the aircraft without stores, fuel		//UnChanged
	FCRD RotInertia;										//Save

	FP MaxG, MinG;	// cm/csec^2 (G * GRAVITY)				//UnChanged
	FCRD InertiaMoment;		//The moment produced due to the aircraft rotating around two or more axis at once
	FCRD ShapeCoG;

	FP fHdg,fPitch,fRoll;	// calculated attitude angles	//Set by SetAirStrucOrientation
//DeadCode AMM 29Jun99 	FP OldfRoll;	// ACM BarrelRoll termination test		//OldfRoll = fRoll

	INSTRUMENTS Inst;										//Set by SetInstruments

//DeadCode AMM 29Jun99 	ULong max_itc, itc;	// gear its							//Only used for Monotxt

	// Player inputs
	int Elevator;											//Save
	int ElevatorTrim;										//Save
	int Aileron;											//Save
	int Rudder;												//Save
//DeadCode AMM 29Jun99 	FP ControlPower;	
//DeadCode AMM 29Jun99 	FP ControlResistance;	

	SWord DesiredRPM;	// CSB // for piston engine with constant speed propellor		//Save
	SWord LeftWheelBrake;									//Save
	SWord RightWheelBrake;									//Save

	FP SlatOutPressure;										//UnChanged
	FP SlatInPressure;										//UnChanged

	FP MControlLoss0;		//For loss of elevator power at high speeds	/CSB
	FP MControlLoss1;		//For loss of elevator power at high speeds	/CSB
	FP MControlPower;

	int ControlForce;		// % of max available control force feedback
	int BuffetForce;		// % of max available buffet force feedback

	Bool Gear;	// flag for anims

//DeadCode AMM 29Jun99 	FCRD PropWashEffect;

	// Atmosphere
	FP AmbDensity;											//Set by MMC.Sky.Ambient every 128 frames in latest version
	FP AmbTemp;												//Set by MMC.Sky.Ambient every 128 frames in latest version
	FP AmbPres;												//Set by MMC.Sky.Ambient every 128 frames in latest version

//DeadCode AMM 29Jun99 	FP ContrailBand, ContrailDuration;						//UnChanged
	FP ContrailDuration;						//UnChanged		//AMM 29Jun99

//DeadCode AMM 29Jun99 	FCRD ElevatorAirVel;									//Not Used ????
//DeadCode AMM 29Jun99 	FCRD RudderAirVel;										//Not Used ????

	UWord	CrashTime;//RJS 25Aug98							//Save
//DeadCode AMM 29Jun99 	UWord	UniqueID;									//RJS 18Sep98

	FP Blood;	//CSB 09/06/99

	// Functions

	void ClearLists ();

	void SetupAircraft (AirStrucPtr const ControlledAC);
	void RemoveStore(weap_info*,SLong,int mass, int drag, Bool fueltank);//RJS 13May98
	void RemoveMass(FP amount, FP massX, FP massY, FP massZ);
	void AddMass(FP amount, FP massX, FP massY, FP massZ);
	void SetMassInertias (AirStrucPtr const ControlledAC, FP EmptyIxx, FP EmptyIyy, FP EmptyIzz);
	void UpdateMassInertias (AirStrucPtr const ControlledAC);
	
	void CalcAirVel (AirStrucPtr const ControlledAC);
	void TrimAircraft(AirStrucPtr const ControlledAC);
	void SetLocalGust(COORDS3D AcPos, COORDS3D HitPos, SWord Strength);
	FP   CalcFuelRate(AirStrucPtr const ControlledAC);		//CSB
	void InitialiseEngines(AirStrucPtr const ControlledAC);	//CSB 24/11/98
	void ProcessEngines (AirStrucPtr const ControlledAC);
	void RestartEngines (AirStrucPtr const ControlledAC);
	void ProcessMainElements (AirStrucPtr const ControlledAC);
//DeadCode CSB 05/11/98		void ProcessStabElements (AirStrucPtr const ControlledAC);
	void ProcessDevices ();
	void GearUp (AirStrucPtr const ControlledAC);
	void GearDown (AirStrucPtr const ControlledAC);
	void FlapsDown (AirStrucPtr const ControlledAC);
	
	void ProcessStoresDrag (AirStrucPtr const ControlledAC);			//CSB 03Sep98

	void ProcessCylinders (AirStrucPtr const ControlledAC);		//CSB 05/11/98

//DeadCode CSB 26/02/99		void ProcessAeroCtrls ();
//DeadCode CSB 26/02/99		void ProcessAeroCouples ();

//DeadCode CSB 01/02/99		void GearCalcs (AirStrucPtr const ControlledAC);
	void ProcessGears (AirStrucPtr const ControlledAC, FP forcex);	//CSB 11/01/99
	void CheckGearPos (AirStrucPtr const ControlledAC);	//CSB 12/01/99
//DeadCode CSB 17/05/99		UC_STATUS CalcLegIntersects ();
//DeadCode CSB 01/02/99		void CalcGearForces (Bool);
//DeadCode CSB 01/02/99		void Reset2Ground ();

	void CalcNettForceMoment (FCRD&, FCRD&);
	void WingDamage (AirStrucPtr const ControlledAC, FP forcey);

	void CalcAcc ();
	void CalcRotAcc ();

	void MovePilotEye();

	void SetSpeed(AirStrucPtr const ControlledAC, SWord desiredspeed);	//CSB 09/12/98
	void ModifyAcc(FCRD OldAcc, FCRD NewAcc);
	void ChangeDirection(AirStrucPtr const ControlledAC, FP DeltaPitch, FP DeltaYaw, FP DeltaRoll);	//CSB 14/12/98
	void TransInt (ITERATION_MASK, FP);
	void RotInt (ITERATION_MASK);
	void RotVelInt ();

	void Ground (AirStrucPtr const ControlledAC);
//DeadCode CSB 01/02/99		void GroundCalcs ();	// Simple Gear calcs

	void CalcStickForceFeedback ();	//CSB
	void ResetGearPos(bool);									//RJS 30Jun99


//DeadCode RDH 10Sep98 	void StickForces ();

#ifdef CALIBRATION_CODE
	void CalibrationInputs ();
#endif

public:

	// Software Params

	PENGINE EngineList;
	PGEAR GearList;
	PMODELANIM AnimList;
//DeadCode RDH 10Sep98 	PMASSPOINT MassList;
//DeadCode RDH 10Sep98 	PDRAGPOINT DragList;
	PTHRUSTPOINT ThrustList;
	PSURFACE SurfaceList;
	PMAINPLANE MainPlaneList;
	PCYLINDER CylinderList;
	PAERODEVICE DeviceList;
//DeadCode CSB 26/02/99		PAEROCTRL AeroCtrlList;
//DeadCode CSB 26/02/99		PAEROCOUPLE AeroCoupleList;

	Model ();
	~Model ();

	void Initialise (AirStrucPtr const ControlledAC, Bool);
	void Base (AirStrucPtr const ControlledAC);
	void SubBase (AirStrucPtr const ControlledAC);
	void RealBase (AirStrucPtr const ControlledAC);
	void ACMBase (AirStrucPtr const ControlledAC);
	void DerivativeBase ();
//DeadCode CSB 11/02/99		void DeathBase (AirStrucPtr const ControlledAC);											//RJS 14Apr98

	// Interface Functions

//TempCode ARM 27Aug97 	Collide::Pos HaveWeLanded (AirStruc*ac, ANGLES& pitch, ANGLES& roll);
	
	void ResetDeltaPos (AirStrucPtr const ControlledAC,SLong, SLong, SLong);
	void ResetPosition (AirStrucPtr const ControlledAC,SLong, SLong, SLong);
	void ResetVelocity (AirStrucPtr const ControlledAC,SLong, SLong, SLong, Bool);
	void ResetAngles (AirStrucPtr const ControlledAC,UWord, UWord, UWord);

	void UpdateAirStruc (AirStrucPtr const ControlledAC);
	void SetAirStrucPosition (AirStrucPtr const ControlledAC);
	void SetAirStrucOrientation (AirStrucPtr const ControlledAC);
	void SetAirStrucVelocity (AirStrucPtr const ControlledAC);
	void UpdateModel (AirStrucPtr const ControlledAC);
	void SetPlayerMoving (AirStrucPtr const ControlledAC);

	void Instruments (AirStrucPtr const ControlledAC);
	void Animations (AirStrucPtr const ControlledAC);

	void	DeathSequenceOverride(int);

	void	SetGearAnimPos(AirStrucPtr const ControlledAC,SWord,Bool killnow=FALSE);//RJS 07Sep98
	void	ProcessAeroPacket(AirStrucPtr const ControlledAC, UByte	DeviceID, UByte, UByte);	//CSB 11/05/99	
	void	CalcLauncherVel(SWord,SWord&,SWord&, SWord&);		//RDH 30Nov98
	void	CalcGunsightPos(SLong range, SWord gunvel, SLong& dx, SLong& dy, SLong& dz);		//CSB 03/06/99	
	void	RememberForGunSight(bool);							//CSB 09Jun99
	void	CalcParachuteVel(SWord&,SWord&,SWord&,SWord,SWord,SWord,SWord,SWord, SLong);//RJS 10May99	//CSB 13/06/99	
	void	CalcLauncherPos(SLong&,SLong&,SLong&);				//RJS 02Jun99
	void	BackupForGunsight();								//RJS 25Jun99

#ifdef WRITE_MODEL_LOG
void WriteModelLog ();
#endif

#define PSRANGE	5
#define MACHRANGE	52
#define LIFTLIMITRANGE	26
struct	TurnData
{
	FP			Ps;
	FP			rate[MACHRANGE];
//	FP			rate[13];
};
struct ThrustData
{
	FP			alt;
	FP			thrust[14];
};
struct	DogHouseData
{
	FP			alt;
	FP			stallspd;
	FP			stallmach;
	FP			maxspd;
	FP			maxmachSL;
	FP			maxPs;
	FP			machatmaxPs;
	FP			ceiling;
	FP			thrust;
	FP			mass;
	FP			liftlimit[LIFTLIMITRANGE];
	TurnData	turndata[PSRANGE];
	FP			minmach[PSRANGE];
	FP			maxmach[PSRANGE];
	ThrustData	thrustatvel[11];
//	TurnData	turndata[5];
	FP			timeto16400;
	FP			timeto20000;
	FP			timeto30000;
	FP			timeto32800;
	FP			timeto40000;
};

#ifdef EMIT_HM_DATA
	void EmitHMData (AirStrucPtr const ControlledAC);
	DogHouseData	doghousedata;
#endif
 
#ifdef EMIT_DOGHOUSE_DATA
	void EmitDoghouseData (AirStrucPtr const ControlledAC,FP Height);
#endif

#ifdef PS_CALCS 
	Bool CalcPs (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP& Vel, FP& Ps);
	void Model::CalcnAtPs (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP& Vel, FP& Ps, FP& n);
	void Model::CalcnAtMaxLift (FP Height, FP Mach, FP& Vel,FP& n);
	void Model::CalcTurnRate(FP n, FP Vel, FP& TurnRate);
	Bool Model::FindFastestAtPsReq (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel, FP PsReq);
	void Model::EmitDoghouseData2 (AirStrucPtr const ControlledAC,FP Height);
	Bool Model::FindSlowestAtPsReq (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel, FP PsReq);
	void Model::EmitLiftLimitedData (FP Height);
	void Model::EmitThrustData (AirStrucPtr const ControlledAC,FP Height);
	void Model::CalcStallSpeed (FP Height, FP& Mach, FP& Vel);
	void Model::PrintDogHouseData(AirStrucPtr const ControlledAC,FP Height);
	void Model::ClrDogHouseData(FP Height);
	void EmitPsData (AirStrucPtr const ControlledAC,FP currheight);
	Bool PsSlope (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP& Slope, FP& Ps);
	Bool FindMaxPs (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel, FP& Ps);
	Bool FindFastestZeroPs (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel);
	Bool FindCeiling (AirStrucPtr const ControlledAC,FP& Height, FP& Mach, FP& Vel);
	void CalibCalcThrust (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP Vel, FP& Thrust);
#endif
	
};
typedef class Model MODEL;


#include "ctrl.h"


#include "elmt.h"

extern void SetBuffetData(CockpitBuf* );


#ifdef DISPLAY_MONO_DATA
void PrintModelData (AirStrucPtr const ControlledAC,Model*, ULong, ULong);
#endif

void PrintVar (ULong, ULong, char*, ULong);
void PrintVar (ULong, ULong, char*, SLong);
void PrintVar (ULong, ULong, char*, FP);
void PrintVar (ULong, ULong, char*, SWord);
void PrintVar (ULong, ULong, char*, UWord);
void PrintVar (ULong, ULong, char*, UByte);
void PrintVar (ULong, ULong, char*, SByte);
void PrintString (ULong, ULong, char*);
void PrintHLine (ULong, ULong, ULong, char*);
void PrintVLine (ULong, ULong, ULong, char*);

extern Model _Model;

extern PMODEL ModelList;

void F86E_Setup (AirStrucPtr const, ULong);
void MIG15_Setup (AirStrucPtr const, ULong);
void F84E_Setup (AirStrucPtr const, ULong);
void F80C_Setup (AirStrucPtr const, ULong);
void F51D_Setup (AirStrucPtr const, ULong);
void F9F2_Setup (AirStrucPtr const, ULong);
void F8_Setup (AirStrucPtr const, ULong);
void F82G_Setup (AirStrucPtr const, ULong);
void YAK9_Setup (AirStrucPtr const, ULong);
void F4U5_Setup (AirStrucPtr const, ULong);
void SFURY_Setup (AirStrucPtr const, ULong);
void FFLY_Setup (AirStrucPtr const, ULong);
void A1_Setup (AirStrucPtr const, ULong);

void B26_Setup (AirStrucPtr const, ULong);
void B29_Setup (AirStrucPtr const, ULong);
void T6_Setup (AirStrucPtr const, ULong);

void F4U5_SetupAI (AirStrucPtr const, ULong);
void Mig15_SetupAI (AirStrucPtr const, ULong);
void F8_SetupAI (AirStrucPtr const, ULong);
void F80C_SetupAI (AirStrucPtr const, ULong);
void F51D_SetupAI (AirStrucPtr const, ULong);
void F82G_SetupAI (AirStrucPtr const, ULong);
void F84E_SetupAI (AirStrucPtr const, ULong);
void F86E_SetupAI (AirStrucPtr const, ULong);
void F9F2_SetupAI (AirStrucPtr const, ULong);
void FFLY_SetupAI (AirStrucPtr const, ULong);
void SFURY_SetupAI (AirStrucPtr const, ULong);
void YAK9_SetupAI (AirStrucPtr const, ULong);


#endif
