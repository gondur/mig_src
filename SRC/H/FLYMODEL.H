//------------------------------------------------------------------------------
//Filename       flymodel.h
//System         
//Author         R. Hyde 
//Date           Thu 26 Oct 1995
//Description    flymodel.cpp header file
//------------------------------------------------------------------------------
#ifndef	FLYMODEL_Included
#define	FLYMODEL_Included

	#include	"PlaneTyp.h"									//PD 01Nov95


 enum	{	MAXAILERON	=	32767,	//38,								//RDH 15Dec95
			AILERONFACTOR = 32767/38,
			MAXELEVATOR	=	32767,	//56,								//RDH 15Dec95
			ELEVATORFACTOR = 32767/56,
			RUDDERFACTOR = 32767/64,
			RUDDER_B000	=	-20480,
			MAXELEVATORMOD=	29000,
			MAXRUDDER	=	32767};	//64};							//RDH 19Dec95


#define	DEFAULT_FLYMODEL 0

typedef	void	*INSTABILITY;
//
// SupAirstruc replacements: Manual pilot replaces flight model bits
//
const int STALLTIME = 500;
class	ViewPoint;
class	ManualPilot
{
	ViewPoint*	View_Point;
	WorldStuff*	myworld;										//PD 25Jun96
public:
	enum	CONTROLMODE	{AUTO = 0,
						MANUAL,
						PILOTDEAD,
						TOGGLE,
						AUTOACCEL_WAYPT,
						AUTOACCEL_FWD,
						AUTOACCEL_MSG,
						AUTOACCEL_MISS,
						AUTOACCEL_HOME};
	CONTROLMODE	controlmode;		//auto/manual  			// piloted ac only (normal or acclerated)
	AirStruc*	ControlledAC2;
	ItemBasePtr	acceltochanged;
	UWord		pilotframetime;
	SLong		lift;											//RDH 30Mar96
	SWord		right_aoa,
				aoa_correction_right,
				aoa_correction_left,
				left_aoa;

private:
//DeadCode RDH 15Dec95 	PTypePtr	classtype;
//DeadCode RDH 28Feb96 	SWord		aileron,
//DeadCode RDH 28Feb96 				elevator,
//DeadCode RDH 28Feb96 				rudder;
//DeadCode RDH 28Feb96 
//DeadCode RDH 20Dec95 	INSTABILITY	Instability;

//DeadCode RDH 28Feb96 	ANGLES		oldpitch,
//DeadCode RDH 28Feb96 				oldroll,
//DeadCode RDH 28Feb96 				acroll,
//DeadCode RDH 28Feb96 //DeadCode RDH 18Dec95 				cpitch,
//DeadCode RDH 28Feb96 				croll, 
//DeadCode RDH 28Feb96 				chdg,  
//DeadCode RDH 28Feb96 				coldpitch, 
//DeadCode RDH 28Feb96 				coldroll,  
//DeadCode RDH 28Feb96 				oldacpitch,
//DeadCode RDH 28Feb96 				oldacroll, 
//DeadCode RDH 28Feb96 				oldachdg,  
//DeadCode RDH 28Feb96 				stalldirection;
//DeadCode RDH 28Feb96 
//DeadCode RDH 28Feb96 	SLong		cposy;
//DeadCode RDH 28Feb96 
//DeadCode RDH 28Feb96 //DeadCode RDH 20Dec95 	SWord		idle,
//DeadCode RDH 28Feb96 	SWord		rpm_lastcycle,
//DeadCode RDH 28Feb96 				rpmtrimtime,
//DeadCode RDH 28Feb96 //DeadCode RDH 20Dec95 				xextra,
//DeadCode RDH 28Feb96 				oldvelx,
//DeadCode RDH 28Feb96 				oldvely,
//DeadCode RDH 28Feb96 				oldvelz,
//DeadCode RDH 28Feb96 				cvely,
//DeadCode RDH 28Feb96 				vel_cms,
//DeadCode RDH 28Feb96 				rotr_xbl,
//DeadCode RDH 28Feb96 				rotr_ybl,
//DeadCode RDH 28Feb96 				rotr_zbl;
//temp vars														//RDH 20Dec95
	SWord		airdensity,
				cl_coeff,
				sos,
//DeadCode RDH 22Jul96 				trim,     
				sinoldacpitch,
				cosoldacpitch,
				sinoldachdg,
				cosoldachdg,
				sinslip,
				cosslip,
				totalslip,
				sinoldacroll,
				cosoldacroll;

	SLong		totaldrag,
				trim,											//RDH 15Nov96
				parasiticdrag,
				shockdrag,
				taildrag,
				rudderdrag,
				taillift,
				rudderlift,
				rightwinglift,
				leftwinglift,
				rightwingdrag,
				leftwingdrag,
				sideforce,
				dynamicpressure,
				groundlevel,
				vel_from_yaw,
//DeadCode RDH 02Jul96 				aoa_from_roll,
				aoa_from_dihedral,
				vel_from_roll,
				hori_vel_left,
				hori_vel_right,
				vert_vel_left,
				vert_vel_right,
				aoa_from_aileron,
				vel_from_turn,
				aoa_from_turn,
				vel_from_pitch,
				aoa_from_pitch,
				mass,
				lastmsgtime,
				thrust;
//DeadCode AMM 29Jun99 	ANGLES		grndhdg;
	SWord		grndvel;
	SWord		flapsitu,flapcl,flapcmo;
	SWord	keyboardcontrol;									//RDH 29Apr96
//DeadCode RDH 01Mar96 	UWord		pilotframetime;
	SLong		velocity_p2;
	UWord		cycletimeres;
//manual ac specific		   
	UWord		//sensitivity,										  //JIM 11/06/99
				cntstick_f,
				cntstick_b,
				cntstick_l,
				cntstick_r,
				cntrudder_l,
				cntrudder_r;
	SWord		device;	

UWordP		elevatordeflectiondata,
			machdata,
				airdensitydata,
				airdensityratio,
				shokdata,
				parasiticdata;

//DeadCode RDH 25Jun96 static UWord airdensityratiosquareroot[];

private:
	void	SubManualPilot(AirStrucPtr const ControlledAC);
//	void	ModifyControlInput(AirStrucPtr const ControlledAC);	//RDH 01Apr96
	void	FlightModelFixedTime(AirStrucPtr const ControlledAC2);
	void	MachDensity (AirStrucPtr const ControlledAC);
	void	WW2Thrust(AirStrucPtr const ControlledAC);
	void	CalcTailLift (AirStrucPtr const ControlledAC);
	void	CalcTailDrag (AirStrucPtr const ControlledAC);
	SLong	CalcTailLiftSub (AirStrucPtr const ControlledAC,SWord elevator,SWord aoa);
	void	CalcRudderLift (AirStrucPtr const ControlledAC);
	void	CalcRudderDrag (AirStrucPtr const ControlledAC);
//DeadCode RDH 30Mar96 	void	CalcLift (AirStrucPtr const ControlledAC);
	SLong	CalcLiftSub(AirStrucPtr const ControlledAC,SWord aoa,SLong vel);
	void	CalcSideForce (AirStrucPtr const ControlledAC);
	SWord	CalcK2 (AirStrucPtr const ControlledAC,SWord elevator);
	SWord	CalcK2Rudder (AirStrucPtr const ControlledAC);
	void	CalcDrag (AirStrucPtr const ControlledAC);
	void	CalcParasiteDrag (AirStrucPtr const ControlledAC);
	SLong	CalcDragSub(AirStrucPtr const ControlledAC,SWord aoa,SLong vel);
	void	CalcTrim (AirStrucPtr const ControlledAC);			//RDH 15Nov96
	void	CalcRotas (AirStrucPtr const ControlledAC);
	void	CalcDeltas (AirStrucPtr const ControlledAC);

	void 	TransformAngles(ANGLES, ANGLES, ANGLES, SLong&, SLong&, SLong&);//PD 01Jul96

	#ifndef	PUBLICVERSION										//PD 01Jul96
	void	CalcDeltasDebug ();									//PD 01Jul96
	#endif														//PD 01Jul96

	void	CalcVel (AirStrucPtr const ControlledAC);
	void	VcoAlfaBeta (AirStrucPtr const ControlledAC);
	void	CalcPosition (AirStrucPtr const ControlledAC);
	void	ChkLandedLocation (AirStrucPtr const ControlledAC);
	void	MoveToGrndPitchRoll(AirStrucPtr const ControlledAC,ANGLES grndroll,ANGLES grndpitch);//RJS 02Oct96
	void	CalcGrndInfo (AirStrucPtr const ControlledAC);		//RDH 05Jun96
	void	DataTrans (AirStrucPtr const ControlledAC);
//**	void	SetFlags ();
	void	DoTrim (AirStrucPtr const ControlledAC);			//RDH 15Nov96
//DeadCode RDH 10Apr96 	void	RotasFixedRate(AirStrucPtr const ControlledAC);
	void	RotasFixedRate_x(AirStrucPtr const ControlledAC);	//RDH 19Mar96
	void	RotasFixedRate_y(AirStrucPtr const ControlledAC);	//RDH 09Apr96
	void	RotasFixedRate_z(AirStrucPtr const ControlledAC);	//RDH 09Apr96
//DeadCode RDH 30Nov95 	void 	CalcNewPos(SLong ,SLong,SLong);
	void	GetStickKeys (AirStrucPtr const ControlledAC);
	void	GetRPMABKeys(AirStrucPtr const ControlledAC);
	void	SensitivityMsg(AirStrucPtr const ControlledAC);		//RDH 03Dec96
	void	GetKeyCommon(AirStrucPtr const ControlledAC);
	void	SecondaryControls (AirStrucPtr const ControlledAC2);//ARM 12Aug97

	void	ApplyDeadZone(AirStrucPtr const ControlledAC, SWord SrcVal, int& DstVal, SWord DeadZone);
	void	ApplyDeadZone2(AirStrucPtr const ControlledAC, SWord SrcVal, int& DstVal, SWord DeadZone);
	void	ApplyDeadZone3(AirStrucPtr const ControlledAC, SWord SrcVal, int& DstVal, SWord DeadZone);
	//	void	FindMaxRPM (AirStrucPtr const ControlledAC);

//automove test
//DeadCode RDH 01Mar96 	void	MoveToHdg (ANGLES);
//DeadCode RDH 01Mar96 	void	MoveToPitch (ANGLES);
//DeadCode RDH 01Mar96 	SWord	MoveToDesiredPitch (ANGLES);
//DeadCode RDH 01Mar96 	SWord	DesiredPitchChk (ANGLES);
//DeadCode RDH 01Mar96 	SWord	MoveToDesiredHdg (ANGLES,ANGLES);
//DeadCode RDH 01Mar96 	void	MoveToRoll (SWord);
//DeadCode RDH 01Mar96 	void	MoveToRPM (SWord);
//DeadCode RDH 01Mar96 	void 	SetManoeuvreTime (SWord);
//DeadCode RDH 01Mar96 	SWord 	ManoeuvreTimeLeft ();
//DeadCode RDH 01Mar96 
//DeadCode RDH 01Mar96 	void	TightTurn (ANGLES);
//DeadCode RDH 01Mar96 	void	SplitS ();
//DeadCode RDH 01Mar96 	void	ZoomandDrop ();
//DeadCode RDH 01Mar96 	void	ZoomAndTurn (SWord,SWord);
//DeadCode RDH 01Mar96 	void	BarrelRoll (SWord,SWord);
//DeadCode RDH 01Mar96 	void	Scissors (SWord,SWord);
//DeadCode RDH 01Mar96 	void	MildScissors (SWord,SWord);
//DeadCode RDH 01Mar96 	void	StraightandLevel (SWord,SWord);
//DeadCode RDH 01Mar96 	void	SideSlip (SWord,SWord);
//DeadCode RDH 01Mar96 	void	SpinOut (SWord,SWord);
//DeadCode RDH 01Mar96 	void	DiveforHome (SWord,SWord);
//DeadCode RDH 01Mar96 	void	GoHome (SWord,SWord);
//DeadCode RDH 01Mar96 	void	MakeForFriendly (SWord,SWord);
//DeadCode RDH 01Mar96 	void	MoveAway (SWord,SWord);
//DeadCode RDH 01Mar96 	void	AccidentalSpinOut (SWord,SWord);
//DeadCode RDH 01Mar96 	void	TurningFight (SWord,SWord);
//DeadCode RDH 01Mar96 	void	LowGYoYo (SWord,SWord);
//DeadCode RDH 01Mar96 	void	RollAway (SWord,SWord);
//DeadCode RDH 01Mar96 	void	VerticalLoop (SWord,SWord);
//DeadCode RDH 01Mar96 	void	ImmelmannTurn (SWord,SWord);
//DeadCode RDH 01Mar96 	void	HeadOnOffset (SWord,SWord);
//DeadCode RDH 01Mar96 	void	Immelmann (SWord,SWord);
//DeadCode RDH 01Mar96 	void	StayWithPrey (SWord,SWord);
//DeadCode RDH 01Mar96 




public:
	ManualPilot();
	void	CalcLift (AirStrucPtr const A);
	void	MainManualPilot();
	void	ACMManualPilot(AirStrucPtr const A);
	void	InitManualPilot (AirStrucPtr const A);				//RDH 05May96
	void	InitManualPilotSub (AirStrucPtr const A);				//RDH 01Nov96
//rdh	void	InitAircraft(AirStrucPtr const ControlledAC, Bool players);
	void ManualPilot::InitFlightModelPos(AirStrucPtr const ControlledAC);
	void ManualPilot::AutoToggleAircraft(AirStrucPtr const ControlledAC, CONTROLMODE mode);

	void ManualPilot::InitSimpleAc(AirStrucPtr const ControlledAC);

	void	PrintStatistics (class Window*);
	void	Associate(
			AirStruc*	manualas,				//item to move
			CONTROLMODE		inmanual=MANUAL);			//flag for man/auto
	void	SetWorldPtr(WorldStuff *worldptr)					//PD 25Jun96
			{myworld=worldptr;};								//PD 25Jun96
	void	AutoToggle(CONTROLMODE dead=TOGGLE);

	Bool	IsPiloted(ItemBasePtr i)	{return (Bool) (i==ControlledAC2);}//JIM 26Jul96

//DeadCode AMM 26Jan99 	Bool	DeathSequenceOverride(ItemPtr,int);					//DAW 03Sep98
	Bool	DeathSequenceOverride(ItemPtr,int,bool commscalled=false);					//AMM 26Jan99

};

	extern	class ManualPilot Manual_Pilot;

#endif

