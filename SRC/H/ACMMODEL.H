//------------------------------------------------------------------------------
//Filename       acmmodel.h
//System         
//Author         Andrew McRae
//Date           Wed 16 Apr 1997
//				major tidy up 20/9/98, rdh
//
//Description    
//------------------------------------------------------------------------------
//variables commented to indicate action required for replay, rdh
//				save			need to savethe variable in the replay file
//				set by ***		use the function *** to set the variable
//				unchanged		the variable, once set is never changed
//				zero			the variable should be zeroed on replaying 



#ifndef	ACMMODEL_Included
#define	ACMMODEL_Included
#include	<math.h>
#include	"bitfield.h"											//RJS 02Dec97
#include	"winmove.h"
typedef class Model* PMODEL;									//ARM 07Mar97
typedef class AcmModel* PACMMODEL;								//ARM 14May97

#define MAXCTRLDYNPRESS 0.18

typedef class AcmModel {

public:

	enum ACM_COMMAND
	{
		ACM_MIN = 0,
		ACM_NOTHING = 0,

		ACM_SETTHRUST,
		ACM_ROLLRATE,
		ACM_PITCHRATE,
		ACM_PITCH,
		ACM_ROLL,
		ACM_FASTROLL,	//CSB 21/03/99	
		ACM_SPEED,
		ACM_CLIMBRATE,
		ACM_TURNRATE,
		ACM_HEIGHT,
		ACM_MINHEIGHT,
		ACM_HEADING,
		ACM_DESIREDROLL,
		ACM_FLYDESIREDROLL,
		ACM_VECTOR,
		ACM_KEEPWINGSLEVEL,
		ACM_MAXBANK,
		ACM_STAYVERTICAL,
		ACM_ZEROSPECIFICPOWER,
		ACM_YAWRATE,
		ACM_LIFTLIMIT,
		ACM_SPEEDWITHELEVATORS,
		ACM_RUDDER,
		ACM_ELEVATOR,
		ACM_AILERON,
		ACM_AOA,
		ACM_RELAOA,

		ACM_AERODEVICE_START,
		ACM_GEARIN,
		ACM_GEAROUT,
		ACM_FLAPSIN,
		ACM_FLAPSOUT,
		ACM_SLATSIN,
		ACM_SLATSOUT,
		ACM_SPEEDBRAKESIN,
		ACM_SPEEDBRAKESOUT,
		ACM_TANKSIN,
		ACM_TANKSOUT,

		ACM_MAX
	};

	MAKEFIELD (ACM_COMMAND, ACM_MIN, ACM_MAX);


	// Controls
//	int LastElevator;


	// Simple gear calcs
	FP BrakePower;							//unchanged
	FP SteerRatio;							//unchanged
//	FP pitch;								//used in GroundCalcs, but usage seems odd


// ***************************************************************

	// ACM Vars



	
	FP MaxAileron;							//unchanged
//	FP lastdeltaroll;



	FP DeltaPitchForMaxElevator;			//unchanged
	FP MaxElevatorForTightTurn;				//unchanged
//	FP DiffPitchForMaxElevator;
	FP lastdeltapitch;						//save
	FP deltapitchsum;						//save
	FP deltarollsum;						//save
	FP deltayawsum;							//save
	FP maxdeltaforclosework;				//save


	FP yawmodifier;				//unchanged

	FP yawintmodifier;			//unchanged
	FP turnmodifier;			//unchanged
	FP turnintmodifier;			//unchanged
	FP rollmodifier;			//unchanged
	FP pitchratemodifier;		//unchanged
	FP aoamodifier;				//unchanged
	FP pitchmodifier;			//unchanged
	FP pitchintmodifier;		//unchanged
	FP liftmodifier;			//unchanged

	FP rollintmodifier;			//unchanged
	FP IntPitchForMaxElevator;	//unchanged
	FP IntRollForMaxAileron;	//unchanged


// ***************************************************************



	void Calc ();
	void Pilot (AirStrucPtr const ControlledAC);
	void ActionAeroDeviceCommands (AirStrucPtr const ControlledAC);
	Bool Logic (AirStrucPtr const ControlledAC);
	void Control (FORI&, FP);
	void Null ();
	// fly to aim ????
	
//	FP LimitAcceleration (FP);

//	void MaxMinNormalAcceleration (FP& maxg, FP& ming);

	// ACM Pilot mode switches & target params (model units)
	ACM_COMMANDField AcmMode;
	SWord CtrlThrust;						//zero
	FP CtrlRollRate;						//zero
	FP CtrlPitchRate;						//zero
	FP CtrlPitch;							//zero
//	FP OldCtrlPitch;
	FP CtrlRoll;							//zero
	FP OldCtrlRoll;									//save
	FP CtrlSpeed;							//zero
	FP CtrlMach;							//zero
	FP CtrlClimbRate;						//zero
	FP CtrlTurnRate;						//zero
	FP OldCtrlTurnRate;								//save
	FP CtrlYawRate;							//zero
	FP OldCtrlYawRate;								//save
	FP CtrlHeight;							//zero
	FP CtrlMinHeight;						//zero
	FP CtrlHeading;							//zero
	FCRD CtrlVector;						//zero
	FP CtrlMaxBank;							//zero
	SLong	CtrlRudder;						//zero
	SLong	CtrlElevator;					//zero
	SLong	CtrlAileron;					//zero
	FP	CtrlAoA, OldAoa;					//zero

	FP desiredRoll;	// ARM 14 Apr 98

	// Acm Pilot Control Calc Functions
	inline void SetThrust (AirStrucPtr const ControlledAC);
	inline void ModRollRate (AirStrucPtr const ControlledAC);
	inline void ModPitchRate (AirStrucPtr const ControlledAC);
	inline void ModPitch (AirStrucPtr const ControlledAC);
	inline void ModRoll (AirStrucPtr const ControlledAC);
	inline void ModFastRoll (AirStrucPtr const ControlledAC);
	inline void ModSpeed (AirStrucPtr const ControlledAC);
	inline void ModClimbRate (AirStrucPtr const ControlledAC);

	inline void ModTurnRate (AirStrucPtr const ControlledAC);
	inline void ModSpeedWithElevators (AirStrucPtr const ControlledAC);
	inline void ModHeight (AirStrucPtr const ControlledAC);
	inline void ModMinHeight (AirStrucPtr const ControlledAC);
	inline void ModVector (AirStrucPtr const ControlledAC);
	inline void ModKeepWingsLevel (AirStrucPtr const ControlledAC);
	inline void ModStayVertical (Bool);
	inline void	ModZeroSpecificPower(AirStrucPtr const ControlledAC);
	inline void ModLiftLimit (AirStrucPtr const ControlledAC);
	inline void ModRudder (AirStrucPtr const ControlledAC);
	inline void ModElevator (AirStrucPtr const ControlledAC);
	inline void ModAileron (AirStrucPtr const ControlledAC);
	inline void ModAoA (AirStrucPtr const ControlledAC);
	inline void ModRelAoA (AirStrucPtr const ControlledAC);

	inline void	ModYawRate(AirStrucPtr const ControlledAC);

	void AcmModel::ZeroIntControl();

	Bool NearMaxAoA(AirStrucPtr const ControlledAC);



	void Clear ()
	{
		AcmMode = ACM_NOTHING;
	}

	void Thrust (SWord thrust)
	{
		CtrlThrust = thrust;
		AcmMode |= ACM_SETTHRUST;
	}

	void ClimbRate (FP climbrate)
	{
		CtrlClimbRate = FEETPERMIN2MPS(climbrate);
		AcmMode |= ACM_CLIMBRATE;
	}
	void DisableClimbRate ()
	{
		AcmMode %= ACM_CLIMBRATE;
	}

	void Height (FP height)
	{
		CtrlHeight = height;
		AcmMode |= ACM_HEIGHT;
	}

	void MinHeight (FP minheight)
	{
		CtrlMinHeight = minheight;
		AcmMode |= ACM_MINHEIGHT;
	}

	void RollRate (FP rollrate)
	{
		CtrlRollRate = Rowan2Rads(rollrate);
		AcmMode |= ACM_ROLLRATE;
	}

	void Roll (FP roll)
	{
		CtrlRoll = Rowan2Rads(roll);
		AcmMode |= ACM_ROLL;
	}

	void FastRoll (FP roll)
	{
		CtrlRoll = Rowan2Rads(roll);
		AcmMode |= ACM_FASTROLL;
	}

	void Heading (FP heading)
	{
		CtrlHeading = Rowan2Rads(heading);	//rdh
		AcmMode |= ACM_HEADING;
	}

	void DesiredRoll (FP desRoll)
	{
		desiredRoll = Rowan2Rads (desRoll);
	}

	void FlyDesiredRoll ()
	{
		AcmMode |= ACM_FLYDESIREDROLL;
	}

	void PitchRate (FP pitchrate)
	{
		CtrlPitchRate = pitchrate;
		AcmMode |= ACM_PITCHRATE;
	}
	void DisablePitchRate ()
	{
		AcmMode %= ACM_PITCHRATE;
	}

	void Pitch (FP pitch)
	{
		CtrlPitch = Rowan2Rads(pitch);		//rdh
		AcmMode |= ACM_PITCH;
	}
	void DisablePitch ()
	{
		AcmMode %= ACM_PITCH;
	}

	void Speed (FP speed)
	{
		CtrlSpeed = speed;
		AcmMode |= ACM_SPEED;
	}

	void SpeedWithElevators(FP mach)
	{
		CtrlMach = mach;
		AcmMode |= ACM_SPEEDWITHELEVATORS;
	}
	void TurnRate (FP turnrate)
	{
		CtrlTurnRate = turnrate;
		AcmMode |= ACM_TURNRATE;
	}
	void YawRate (FP yawrate)
	{
		CtrlYawRate = yawrate;
		AcmMode |= ACM_YAWRATE;
	}
	void LiftLimit ()
	{
		AcmMode |= ACM_LIFTLIMIT;
	}

	void SetRudder (int rudder)
	{
		CtrlRudder = rudder;
		AcmMode |= ACM_RUDDER;
	}
	void SetElevator (int elevator)
	{
		CtrlElevator = elevator;
		AcmMode |= ACM_ELEVATOR;
	}

	void SetAileron (int aileron)
	{
		CtrlAileron = aileron;
		AcmMode |= ACM_AILERON;
	}

	void SetAoA (int aoa)
	{
		CtrlAoA = Rowan2Rads(aoa);
		AcmMode |= ACM_AOA;
	}
	void SetRelAoA (int aoa)
	{
		CtrlAoA = Rowan2Rads(aoa);
		AcmMode |= ACM_RELAOA;
	}

	void Vector (FP i, FP j, FP k)
	{
		CtrlVector.x = i;
		CtrlVector.y = j;
		CtrlVector.z = k;
		AcmMode |= ACM_VECTOR;
	}

	void KeepWingsLevel ()
	{
		AcmMode |= ACM_KEEPWINGSLEVEL;
	}

	void MaxBank (FP angle)
	{
		CtrlMaxBank = Rowan2Rads(angle);
		AcmMode |= ACM_MAXBANK;
	}

	void StayVertical (AirStrucPtr const ControlledAC);

	void	ZeroSpecificPower()
	{
		AcmMode |= ACM_ZEROSPECIFICPOWER;

	}

	// Secondary Controls


	void GearUp ()
	{
		AcmMode |= ACM_GEARIN;
	}

	void GearDown ()
	{
		AcmMode |= ACM_GEAROUT;
	}

	void FlapsUp ()
	{
		AcmMode |= ACM_FLAPSIN;
	}

	void FlapsDown ()
	{
		AcmMode |= ACM_FLAPSOUT;
	}

	void SpeedBrakesIn ()
	{
		AcmMode |= ACM_SPEEDBRAKESIN;
	}

	void SpeedBrakesOut ()
	{
		AcmMode |= ACM_SPEEDBRAKESOUT;
	}

} ACMMODEL, *PACMMODEL;

inline SWord DeltaAngle (UWord, UWord);
FP DeltaAngle (FP, FP);
//inline FP AngleSign (FP a){return(fmod(a,FPIE));}
SWord ControlAttractor (SWord, SWord, UWord);
SWord CtrlShiftRight (SWord, SWord);
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AngleSign
//Author		Andrew McRae
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline Float AngleSign (Float ang)
{
	ang=fmod(ang,F2PIE);
	if (ang > FPIE)
		ang = ang - F2PIE;
	if (ang < -FPIE)
		ang = ang + F2PIE;

	return ang;
}

#endif
