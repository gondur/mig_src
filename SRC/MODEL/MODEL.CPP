/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       model.cpp
//System         
//Author         Andrew McRae
//Date           Tue 7 Jan 1997
//Description    Mig Alley Flight Model
//------------------------------------------------------------------------------
//
//When handing in a version
//		define DISPLAY_MONO_DATA in monotxt.h
//		auto_toggle: commment out in spotted.cpp twice

//To get calib data define following inmodel.h
//		#define EMIT_HM_DATA
//		#define EMIT_DOGHOUSE_DATA
//		#define PS_CALCS
//
//
//Curve editor is used to provide data for aircraft. See p36 of Andrew's notes for key usage
//
//
//Notes on dealing with weight/mass change
//																				done
//1	In SetAnimData, Rob fills in weap_info										*
//			set int_fuel to 0 (Rod fills in)
//			set all leakages to 0
//2	Rob tidies up weap_ctl														*
//
//3	Rod add stores weight at SetUpMassPoint										*
//
//4 Rob to define an instrument flag to show whether on int/ext fuel			*
//	Rod will set it based on the info in weap_info								*
//
//5 Rob to call Model::RemoveStore() when he releases a weapon or ejects fuel	*
//6 Rod to handle fuel leakage once data is initialised
//7 Craig to introduce drag points and modify them on stores release
//8 Rob to handle package choice as parameter for SetAnimData					*
//
//
//
#include <stdio.h>
#include <string.h>

#include "dosdefs.h"
#include "monotxt.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "ranges.h"
#include "myangles.h"
#include "planetyp.h"
#include "collided.h"
#include "mytime.h"
#include "myerror.h"
#include "savegame.h"
#include "3dinstr.h"												//RJS 02Dec97
#include "miles.h"
#include "replay.h"
#include "persons2.h"
#include "flymodel.h"
#include "stdio.h"
#include "aerodev.h"
extern Replay _Replay;

//#define LOGVALS

#ifdef DISPLAY_MONO_DATA
#pragma message(__HERE__ "Mono fm output enabled!!!!!!!!!!!")
#else
#pragma message(__HERE__ "Mono fm output disabled")
#endif

static FCRD AveRotVel;

// **********************************************************
//
// Notes:
//
// Units								
//
// Displacement			UNITY = 0.01 Metres
// Force				UNITY = 1 Newton
// Mass					UNITY = 0.01 Kilogrammes
// Time					UNITY = 0.01 Seconds
// Temperature			UNITY = 1 Kelvin
// Angle				UNITY = UNITY
//
// Parameter units								SI equiv
//
// Position				1 = 1cm					= 1e-2 M				
// Velocity				1 = 1cm / 1csec			= 1e+0 M/s
// Acceleration			1 = 1cm / 1csec^2		= 1e+2 M/s^2
// Angle				1 = 1radian				= 1e+0 1
// Angular Velocity		1 = 1rad / 1csec		= 1e+2 1/s 
// Angular Accel		1 = 1rad / 1csec^2		= 1e+4 1/s^2
// Torque				1 = 1N * 1cm			= 1e-2 N.M
// Moment of inertia	1 = 0.01kg * 1cm^2		= 1e-6 kg.M^2
// Density				1 = 0.01kg / 1cm^3		= 1e+4 kg/M^3
// Pressure				1 = 1N / 1cm^2			= 1e+4 pascals
// Area					1 = 1cm^2				= 1e-4 M^2
// Temperature			1 = 1K					= 1e+0 K
// Stiffness			1 = 1N / 1cm			= 1e+2 N/M
// Linear Damping		1 = 1N * 1csec / 1cm	= 1e+0 Ns/M
// Power				1 = 1N * 1cm / 1csec	= 1e+0 Watts
// Energy				1 = 1N * 1cm			= 1e-2 Joules
// Specific Heat		1 = (1N*1cm)/(K*0.01kg)	= 1e+0 Joules/(Kelvin.Kg)
//
// **********************************************************

//ATMOSPHERE Sky;

PMODEL ModelList = NULL;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewModel
//Author		Andrew McRae
//Date			Thu 1 May 1997
//
//Description	Creates a Model (for Airstruc Constructor)
//
//Inputs		AirStrucPtr
//
//Returns		Bool
//
//------------------------------------------------------------------------------
Bool NewModel (AirStrucPtr const ControlledAC)
{

	static ULong Count = 0;

	ControlledAC->fly.AeroDeviceCnt = 0;//RJS 18Sep98
	ControlledAC->fly.pModel = NULL;
	ControlledAC->fly.pModel = new Model ();
	if (ControlledAC->fly.pModel == NULL)
		return FALSE;

	ControlledAC->fly.pModel->Ident = Count;
	Count ++;

	ControlledAC->fly.pModel->FrameCount = ControlledAC->fly.pModel->Ident;	

//	ControlledAC->fly.pModel->ControlledAC = ControlledAC;
	ControlledAC->fly.pAcmModel = &ControlledAC->fly.pModel->ACMModel;
//	ControlledAC->fly.pAcmModel->ac = ControlledAC;
	ControlledAC->fly.pInst = &ControlledAC->fly.pModel->Inst;
	ControlledAC->World.X = 0;
	ControlledAC->World.Y = 0;
	ControlledAC->World.Z = 0;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteModel
//Author		Andrew McRae
//Date			Thu 1 May 1997
//
//Description	Deletes a Model (for AirStruc Destructor)
//
//Inputs		AirStrucPtr
//
//Returns	
//
//------------------------------------------------------------------------------
void DeleteModel (AirStrucPtr const ControlledAC)
{
	if (ControlledAC->fly.pModel != NULL)
	{
		delete ControlledAC->fly.pModel;
		ControlledAC->fly.pModel = NULL;
	}
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Model
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Model Class Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Model::Model ()
{

	NullVec (Pos);
	NullOri (Ori);

	NullVec (Vel);
	NullVec (ShapeCoG);

	EngineList = NULL;
	GearList = NULL;
	AnimList = NULL;
	ThrustList = NULL;
	SurfaceList = NULL;
	MainPlaneList = NULL;
	CylinderList = NULL;
	DeviceList = NULL;
//DeadCode CSB 01/03/99		AeroCtrlList = NULL;
//DeadCode CSB 01/03/99		AeroCoupleList = NULL;

//DeadCode AMM 29Jun99 	ControlPower = 0.1;
//DeadCode AMM 29Jun99 	ControlResistance = 0;
	MControlLoss0 = 8;
	MControlLoss1 = 9;
	
	ControlForce = 100;			// Relative amount of force feedback
	BuffetForce  = 100; 

	List.Attach (&ModelList, this);

	CrashTime = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Model
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Destructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Model::~Model ()
{
	ClearLists ();
	List.Detach (this);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearLists
//Author		Andrew McRae
//Date			Fri 21 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ClearLists ()
{
	while (EngineList != NULL) delete EngineList;
	while (GearList != NULL) delete GearList;
 	while (AnimList != NULL) delete AnimList;

	while (ThrustList != NULL) delete ThrustList;
	while (SurfaceList != NULL) delete SurfaceList;
	while (MainPlaneList != NULL) delete MainPlaneList;
	while (CylinderList != NULL) delete CylinderList;
	while (DeviceList != NULL) delete DeviceList;
//DeadCode CSB 01/03/99		while (AeroCtrlList != NULL) delete AeroCtrlList;
//DeadCode CSB 01/03/99		while (AeroCoupleList != NULL) delete AeroCoupleList;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Initialise
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Set up model params
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::Initialise (AirStrucPtr const ControlledAC, Bool status)
{
	FirstCycle = TRUE;
	Type = AT_VOID;
	MODEL_DT = 2;

	Spinning = FALSE;												  //RDH 01/03/99

	ACMModel.Clear ();;//AcmMode &= 0;

	Controlled = status;
	bACM = FALSE;
//DeadCode AMM 29Jun99 	bGear = FALSE;
	RestartEngine = FALSE;

	ACMModel.Null ();

	NullVec(Vel);
	NullVec(RotVel);
	NullVec(AveRotVel);

	NullVec (Acc);
	NullVec (RotAcc);
	NullVec (NettForce);
	NullVec (NettMoment);

	NullVec (StoresForce);
	NullVec (StoresMoment);
	TotalBuffet = 0.0;

	AmbDensity = 0.0001225;
	AmbTemp = 288.15;
	AmbPres = 10.3215;
	NullVec (AirVel);
	AirSpeed = 0;
	DynamicPressure = 0;
	CheatAcc.x = 32767;
	CheatAcc.y = 32767;
	CheatAcc.z = 32767;

	GearTouched = FALSE;
	GearSkid = FALSE;
//DeadCode AMM 29Jun99 	Crashed = FALSE;
//DeadCode AMM 29Jun99 	DefHeight = 0;
	GroundHeight = 0;
//DeadCode AMM 29Jun99 	grndpitch = ANGLES_0Deg;
//DeadCode AMM 29Jun99 	grndroll = ANGLES_0Deg;
//DeadCode AMM 29Jun99 	grndhdg = ANGLES_0Deg;										//RJS 05May98
//DeadCode AMM 29Jun99 	landed = _Collide.LANDED_OK;
//DeadCode AMM 29Jun99 	grndheight = 0;

	Mass = 0;
	NullVec (RotInertia);
	NullVec (InertiaMoment);

	fRoll = 0;
	fPitch = 0;
	fHdg = 0;
//DeadCode AMM 29Jun99 	OldfRoll = 0;

	Inst.Null ();


	Elevator = 0;
	ElevatorTrim = 0;
	Aileron = 0;
	Rudder = 0;

	DesiredRPM = 3000;	// CSB	//For Constant Speed Propellor
	LeftWheelBrake = 0;
	RightWheelBrake = 0;
	SlatOutPressure = 0;
	SlatInPressure = 0;

//DeadCode AMM 29Jun99 	CoordRudder = 0;
	PowerBoost = 1;

//DeadCode AMM 29Jun99 	NullVec (PropWashEffect);
//DeadCode AMM 29Jun99 	NullVec (ElevatorAirVel);
//DeadCode AMM 29Jun99 	NullVec (RudderAirVel);

//DeadCode AMM 29Jun99 	ContrailBand = 0;											//D 02Apr98
	ContrailDuration = 0;										//D 02Apr98
//DeadCode AMM 29Jun99 	IsDead = FALSE;												//RJS 14Apr98

#ifdef RESET_AC_POS
	// Temporary
	if (Controlled)
	{
		if (ControlledAC->World.X == 0)
		{
			ControlledAC->World.X = 0x1215242;
			ControlledAC->World.Y = FT_15000;
			ControlledAC->World.Y = FT_2000;
			ControlledAC->World.Z = 0x194049c;
		}
	}
	if (!Controlled)
	{
		if (ControlledAC->World.X == 0)
		{
			ControlledAC->World.X = 0x1215242;
			ControlledAC->World.Y = FT_15000;
			ControlledAC->World.Y = FT_2000;
			ControlledAC->World.Z = 0x194049c;
		}
		ControlledAC->World.Y = FT_15000;
		ControlledAC->World.Y = FT_2000;
	}

//	if (!Controlled)
	{
		ControlledAC->vel *= 8;
	}

#endif

//	ControlledAC->World.Y = FT_20000;		//temp rdh
	UpdateModel (ControlledAC);
	SetupAircraft (ControlledAC);
	UpdateAirStruc (ControlledAC);



//for a/c in the air put up gear
	GearUp (ControlledAC);

///ControlledAC->fly.thrustpercent = 0;
	ControlledAC->ai.desiredturn = 0;

	// Temporary Prefs Settings
	// for testing purposes

//	Save_Data.flightdifficulty %= FD_THRUSTPOWERCONTROL;		// done for jet, but not prop
//	Save_Data.flightdifficulty %= FD_TORQUEEFFECTS;				// done
//	Save_Data.flightdifficulty %= FD_JETFLAMEOUT;				// done
//	Save_Data.flightdifficulty %= FD_LIMITEDFUEL;				// wait for Robert
//	Save_Data.flightdifficulty %= FD_POWERBOOST;				// done
//	Save_Data.flightdifficulty %= FD_WINDEFFECTS;				// done
//	Save_Data.flightdifficulty %= FD_WINDGUSTS;					// done
//	Save_Data.flightdifficulty %= FD_AIRCRAFTINTERFERENCE;		// wait for ACM to be implemented
//	Save_Data.flightdifficulty %= FD_IDEALSANDCONTROL;			// Big job, implement jointly with ACM model
//	Save_Data.flightdifficulty %= FD_COORDINATEDRUDDER;			// done
//	Save_Data.flightdifficulty |= FD_SPINS;						// done
//	Save_Data.flightdifficulty %= FD_SLIPSTREAMEFFECTS;			// done
//	Save_Data.flightdifficulty |= FD_GEARSUSPENSION;			// done, but upgrade "SimpleGearCalcs" & "Ground"
//	Save_Data.flightdifficulty %= FD_EXCESSIVEACCELDAMAGE;		// wait for Robert
//	Save_Data.flightdifficulty %= FD_STORESWEIGHTDRAG;			// wait for Robert
//	Save_Data.gamedifficulty |= GD_VULNERABLE;
	// Crappy weapon init fix.....								//RJS 10Jun97
	ControlledAC->weap.weapontype = LT_BULLET;					//RJS 11May98
	fixgunsight = true;	//CSB 09/06/99	

	if (Controlled)
	{
		animptr	oldadptr	= ControlledAC->Anim;				//AMM 28Apr99

		Inst.DialCnt = 0;										//AMM 28Apr99

		ControlledAC->Anim = sizeof(AircraftAnimData) + (1<<MINANIM) + (1<<AIRCRAFTANIM) + (1<<POLYPITANIM);
		PolyPitAnimData*	adptr = (PolyPitAnimData*) ControlledAC->Anim;

		Inst.AddAutoDial(adptr,&adptr->acaltitude,&Inst,&Inst.Altitude,0,10000000,100000);
		Inst.AddAutoDial(adptr,&adptr->acalt1000,&Inst,&Inst.Altitude,0,10000000,10000);
		Inst.AddAutoDial(adptr,&adptr->acalt100,&Inst,&Inst.Altitude,0,10000000,1000000);
		Inst.AddAutoDial(adptr,&adptr->acmach,&Inst,&Inst.MachNo,0.5,1.5);//RJS 24Apr98
		Inst.AddAutoDial(adptr,&adptr->acclimb,&Inst,&Inst.RateOfClimb,-6500,6500);//RJS 24Apr98
		Inst.AddAutoDial(adptr,&adptr->acaccel,&Inst,&Inst.NormalAcc,-3.0,9.0);//RJS 24Apr98
		Inst.AddAutoDial(adptr,&adptr->accompass,&Inst,&Inst.HdgAngle,0.0,360.0);//RJS 24Apr98
 		Inst.AddAutoDial(adptr,&adptr->acgyrocompass,&Inst,&Inst.HdgAngle,0.0,360.0,-182.04);
		Inst.AddAutoDial(adptr,&adptr->acfuelint,&Inst,(SWordP)&Inst.FuelContentInt,0,3000);//RJS 14Apr99
		Inst.AddAutoDial(adptr,&adptr->acslip,&Inst,&Inst.Slip, -3641, 3641);//RJS 16Feb99
//DeadCode RJS 31Mar99 		Inst.AddAutoDial(adptr,&adptr->acpitch,ControlledAC,&ControlledAC->fly.elevator,-32767,16384,52792);//RJS 27May98
		Inst.AddAutoDial(adptr,&adptr->acpitch,&Inst,&Inst.HorizStab,0,52427);//RJS 31Mar99
		Inst.AddAutoDial(adptr,&adptr->acvoltage,&Inst,&Inst.Voltage,0,30000);	//RJS 14Apr99
		Inst.AddAutoDial(adptr,&adptr->acfueltot,&Inst,(SWordP)&Inst.FuelContentTot,0,12000);//CSB 25Feb00

		switch ((int)ControlledAC->shape)
		{
		case F84:
			Inst.AddAutoDial(adptr,&adptr->acrpmtotal,&Inst,&Inst.Rpm1,0.0,7800.0,0.03269);
		case F80:
		case F86:
			Inst.AddAutoDial(adptr,&adptr->acspeed,&Inst,&Inst.IndicatedAirSpeed,50.0,650.0,0.426667);
			Inst.AddAutoDial(adptr,&adptr->acrpmdial,&Inst,&Inst.Power,500,1100);//RJS 31Mar99
			Inst.AddAutoDial(adptr,&adptr->acrpmpercent,&Inst,&Inst.Power,0,500);//RJS 31Mar99
			Inst.AddAutoDial(adptr,&adptr->actempair,&Inst,&Inst.TempFreeAir,-70.0,50.0,2.125);
			Inst.AddAutoDial(adptr,&adptr->acturn,&Inst,&Inst.Turn, -3641, 3641);//RJS 16Feb99
			Inst.AddAutoDial(adptr,&adptr->actempexhaust,&Inst,&Inst.ExhaustTemp,0,255);//RJS 01Apr99
			break;
		case CMIG15:
		case MIG15:
			Inst.AddAutoDial(adptr,&adptr->acspeed,&Inst,&Inst.IndicatedAirSpeed,0.0,700.0,2.55);
			Inst.AddAutoDial(adptr,&adptr->acrpmtotal,&Inst,&Inst.Rpm1,0.0,11500.0,0.02217);
			Inst.AddAutoDial(adptr,&adptr->acspeed100,&Inst,&Inst.IndicatedAirSpeed,0.0,700.0,0.364285);
			Inst.AddAutoDial(adptr,&adptr->actempair,&Inst,&Inst.TempFreeAir,-50.0,150.0,1.25);
			Inst.AddAutoDial(adptr,&adptr->acbank,&Inst,&Inst.BankAngle,-45.0,45.0,2.8333333);
			Inst.AddAutoDial(adptr,&adptr->actempexhaust,&Inst,&Inst.ExhaustTemp,0,255);//RJS 01Apr99
			ControlledAC->weap.weapontype = LT_CANNON;					//RJS 11May98
			break;
		case F51:
			Inst.AddAutoDial(adptr,&adptr->acspeed,&Inst,&Inst.IndicatedAirSpeed,50.0,450.0);
			Inst.AddAutoDial(adptr,&adptr->acrpmtotal,&Inst,&Inst.Rpm1,0.0,4500.0,0.057);
			Inst.AddAutoDial(adptr,&adptr->acmanifoldpress,&Inst,&Inst.ManifoldPressure,36,273);
			Inst.AddAutoDial(adptr,&adptr->acsuctionguage,&Inst,&Inst.SuctionGuage,0,255);
			Inst.AddAutoDial(adptr,&adptr->accarburettor,&Inst,&Inst.CarburettorAirTemp,0,255);
			break;
		}

//DeadCode CSB 14/04/99			Inst.AddTimedDial(adptr,&adptr->acvoltage,ARC_30SEC,ARC_240SEC);
//		Inst.AddTimedDial(adptr,&adptr->actempexhaust,ARC_30SEC,ARC_30SEC);
		Inst.AddTimedDial(adptr,&adptr->acgyrocompass,ARC_1SEC,ARC_1SEC<<1);
//		Inst.AddTimedDial(adptr,&adptr->acpitch,ARC_1SEC<<1,ARC_1SEC<<1);
		Inst.AddTimedDial(adptr,&adptr->achydraulicpress,ARC_1SEC<<4,ARC_30SEC);
		Inst.AddTimedDial(adptr,&adptr->acfuelpress,ARC_30SEC,ARC_30SEC);
		Inst.AddTimedDial(adptr,&adptr->accabinpress,ARC_30SEC,ARC_30SEC);
		Inst.AddTimedDial(adptr,&adptr->acoxygenpress,ARC_30SEC,ARC_30SEC);
		Inst.AddTimedDial(adptr,&adptr->acoilpress,ARC_30SEC,ARC_30SEC);
		Inst.AddTimedDial(adptr,&adptr->actempgas,ARC_30SEC,ARC_30SEC);
		Inst.AddTimedDial(adptr,&adptr->acfuelint,ARC_1SEC<<1,ARC_1SEC<<3);

		_Miles.SetEngine();

		ControlledAC->Anim = oldadptr;							//AMM 28Apr99
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupAircraft
//Author		Andrew McRae
//Date			Fri 31 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetupAircraft (AirStrucPtr const ControlledAC)
{
	ClearLists ();
//DeadCode AMM 29Jun99 	DefHeight = 0;
	ACMModel.BrakePower = 1;
	ACMModel.SteerRatio = 8e-6;

	// Probably will need switch statement to call correct setup function
	// for ACM aircraft

//	ControlledAC->classtype->pSetupFunction (ControlledAC, 1);

	ControlledAC->classtype->pSetupFunction (ControlledAC, ControlledAC->classtype->version);
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Base
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Flight Model Main Function,	called every movecode loop.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::Base (AirStrucPtr const ControlledAC)
{
//DeadCode CSB 03/03/99		static SLong c = 0;	//CSB 02/03/99
//DeadCode CSB 03/03/99		LARGE_INTEGER	t1;	//CSB 02/03/99
//DeadCode CSB 03/03/99		QueryPerformanceCounter(&t1);	//CSB 02/03/99
//DeadCode CSB 03/03/99		LARGE_INTEGER d;
//DeadCode CSB 03/03/99		if(c == 0) QueryPerformanceFrequency(&d);


#ifdef WRITE_MODEL_LOG
	WriteModelLog ();
#endif

//	ControlledAC->fly.LastfHdg = fHdg;

	for (ULong n = 0; n < 1; n++)
	{
		SubBase (ControlledAC);
	}

#ifdef DISPLAY_MONO_DATA

	PMODEL pModel = ModelList;
	ULong x = 25;
	ULong c = 0;

	while (pModel != NULL)
	{
		if(this == pModel)
		{
 			if(pModel->Controlled)	PrintModelData (ControlledAC,this,0,0);
			else if(x <= 50)		PrintModelData (ControlledAC,this,x,0);
		}
		if(!pModel->Controlled) x += 25;

		pModel = pModel->List.NextItem ();
		c++;
	}

//DeadCode CSB 28/04/99		PrintVar (76,0, "%ld ", c); 

#endif

//DeadCode CSB 03/03/99		LARGE_INTEGER	t2;	//CSB 02/03/99
//DeadCode CSB 03/03/99		QueryPerformanceCounter(&t2);
//DeadCode CSB 03/03/99		int t=t2.LowPart-t1.LowPart;
//DeadCode CSB 03/03/99	
//DeadCode CSB 03/03/99		if( (c >= 0) && (c < 25*256) && !(c & 0x00ff) )
//DeadCode CSB 03/03/99		{
//DeadCode CSB 03/03/99			if(c == 0)	PrintVar(50, 0, "Units/s %.0f", (FP)d.LowPart);
//DeadCode CSB 03/03/99	
//DeadCode CSB 03/03/99			if(!bACM)
//DeadCode CSB 03/03/99			{
//DeadCode CSB 03/03/99				PrintVar( 5, c/256, "Frame %.0f", (FP)c);
//DeadCode CSB 03/03/99				PrintVar(20, c/256, "DTime  %.0f", (FP)t);
//DeadCode CSB 03/03/99			}
//DeadCode CSB 03/03/99			else PrintVar(35, c/256, "DTime  %.0f", (FP)t);
//DeadCode CSB 03/03/99		}
//DeadCode CSB 03/03/99		if(!bACM) c++;	//CSB 02/03/99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubBase
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Flight Model Main Function,	called !!!TWICE!!! every movecode loop.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SubBase (AirStrucPtr const ControlledAC)
{

#ifdef PRINT_PREFS
	PrintVar (54, 0,	"FD_THRUSTPOWERCONTROL %ld",	(ULong)Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL]);
	PrintVar (54, 1,	"FD_TORQUEEFFECTS %ld",			(ULong)Save_Data.flightdifficulty [FD_TORQUEEFFECTS]);
	PrintVar (54, 2,	"FD_JETFLAMEOUT %ld",			(ULong)Save_Data.flightdifficulty [FD_JETFLAMEOUT]);
	PrintVar (54, 3,	"FD_LIMITEDFUEL %ld",			(ULong)Save_Data.flightdifficulty [FD_LIMITEDFUEL]);
	PrintVar (54, 4,	"FD_POWERBOOST %ld",			(ULong)Save_Data.flightdifficulty [FD_POWERBOOST]);
	PrintVar (54, 5,	"FD_WINDEFFECTS %ld",			(ULong)Save_Data.flightdifficulty [FD_WINDEFFECTS]);
	PrintVar (54, 6,	"FD_WINDGUSTS %ld",				(ULong)Save_Data.flightdifficulty [FD_WINDGUSTS]);
	PrintVar (54, 7,	"FD_AIRCRAFTINTERFERENCE %ld",	(ULong)Save_Data.flightdifficulty [FD_AIRCRAFTINTERFERENCE]);
	PrintVar (54, 8,	"FD_IDEALSANDCONTROL %ld",		(ULong)Save_Data.flightdifficulty [FD_IDEALSANDCONTROL]);
	PrintVar (54, 9,	"FD_COORDINATEDRUDDER %ld",   	(ULong)Save_Data.flightdifficulty [FD_COORDINATEDRUDDER]);
	PrintVar (54, 10,	"FD_SPINS %ld",					(ULong)Save_Data.flightdifficulty [FD_SPINS]);
	PrintVar (54, 11,	"FD_SLIPSTREAMEFFECTS %ld",		(ULong)Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS]);
	PrintVar (54, 12,	"FD_GEARSUSPENSION %ld",		(ULong)Save_Data.flightdifficulty [FD_GEARSUSPENSION]);
	PrintVar (54, 13,	"FD_EXCESSIVEACCELDAMAGE %ld",	(ULong)Save_Data.flightdifficulty [FD_EXCESSIVEACCELDAMAGE]);
	PrintVar (54, 14,	"FD_STORESWEIGHTDRAG %ld",		(ULong)Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG]);
#endif

	ControlledAC->fly.gforce = 0;

#ifdef COPY_ACM_INTO_PLAYER_AC
	static COORDS3D acPos = { 0,0,0 };

	static ANGLES acHdg = ANGLES_0Deg;
	static ANGLES acPitch = ANGLES_0Deg;
	static ANGLES acRoll = ANGLES_0Deg;
#endif

	if (Save_Data.flightdifficulty [FD_IDEALSANDCONTROL])
		bACM = TRUE;
	else
		bACM = FALSE;

	if (!Controlled)
		bACM = TRUE;

//DeadCode AMM 29Jun99 	if (Save_Data.flightdifficulty [FD_GEARSUSPENSION])
//DeadCode AMM 29Jun99 		bGear = TRUE;

//	if (bACM)
//		bGear = FALSE;

#ifdef COPY_ACM_INTO_PLAYER_AC
	if (Controlled)
	{

		ControlledAC->World.X = acPos.X;
		ControlledAC->World.Y = acPos.Y + 743;
		ControlledAC->World.Z = acPos.Z - FT_75;

		ControlledAC->hdg = ANGLES_0Deg;
		ControlledAC->pitch = ANGLES_342Deg;
		ControlledAC->roll = ANGLES_0Deg;

		return;
	}
#endif

	// if (you don't want the model to do anything miss this out)
	// If not deathmovecode, do this

//	if (!_Replay.Playback || ControlledAC!=Persons2::PlayerGhostAC)
	{

//PD 07Dec98 - 'IsDead' is NEVER set to TRUE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//DeadCode PD 07Dec98 		if (IsDead)													//RJS 14Apr98
//DeadCode PD 07Dec98 			DeathBase(ControlledAC);							//DAW 15Jun98
//DeadCode PD 07Dec98 		else														//RJS 14Apr98
//DeadCode PD 07Dec98 		{															//RJS 14Apr98
			if (!bACM)											//DAW 15Jun98
				RealBase (ControlledAC);						//DAW 15Jun98
			if (bACM)											//DAW 15Jun98
				ACMBase (ControlledAC);							//DAW 15Jun98
//DeadCode PD 07Dec98 		}
	}															//RJS 14Apr98

#ifdef COPY_ACM_INTO_PLAYER_AC
	if (!Controlled)
	{
		acPos.X = ControlledAC->World.X;
		acPos.Y = ControlledAC->World.Y;
		acPos.Z = ControlledAC->World.Z;

		acHdg = ControlledAC->hdg;
		acPitch = ControlledAC->pitch;
		acRoll = ControlledAC->roll;
	}
#endif

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RealBase
//Author		Andrew McRae
//Date			Thu 8 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RealBase (AirStrucPtr const ControlledAC)
{
//**********************************************
//********  TEST CODE	//CSB 07/05/99	********
//**********************************************

//DeadCode CSB 09/07/99	PrintVar( 0, 24, "Time %.0f ", FP(int(ControlledAC->timeofday / (100 * 60 * 60))));	
//DeadCode CSB 09/07/99	PrintVar( 8, 24, ":%.0f ", FP(int(ControlledAC->timeofday / (100 * 60)) - 60 * int(ControlledAC->timeofday / (100 * 60 * 60))));
//DeadCode CSB 09/07/99	PrintVar(11, 24, ":%.0f ", FP(int(ControlledAC->timeofday / (100)) - 60 * int(ControlledAC->timeofday / (100 * 60))));

//DeadCode CSB 13/06/99		int _col = 2 + (FrameCount & 0x1f);
//DeadCode CSB 13/06/99		if((_col <= 18) && (_col != 10))
//DeadCode CSB 13/06/99			PrintString(0, _col, "................................................................................");
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99		PrintVar(0, 22, "VX %.1f ", FP(ControlledAC->velx * 0.1));
//DeadCode CSB 13/06/99		PrintVar(0, 23, "VY %.1f ", FP(ControlledAC->vely * 0.1));
//DeadCode CSB 13/06/99		PrintVar(0, 24, "VZ %.1f ", FP(ControlledAC->velz * 0.1));
//DeadCode CSB 11/06/99		Blood = 1;
//DeadCode CSB 11/06/99		ControlledAC->SimpleACM();
//DeadCode CSB 11/06/99		return;
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 */
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 */	if (Key_Tests.KeyPress3d (SENS_UP))
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 */	{
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 */		AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 */
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 */		SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->LEFTWINGIN, BS_DAMLV2);//BS_DEAD);
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 */		SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->LEFTWINGOUT, BS_DAMLV2);//BS_DEAD);
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 *///DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->RIGHTWINGIN, BS_DEAD);
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 *///DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->RIGHTWINGOUT, BS_DEAD);
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 *///DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->TAIL, BS_DEAD);
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 *///DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->PILOTLEFT, BS_DEAD);
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 */	}
//DeadCode CSB 18/05/99	/* TEST CODE CSB 18/05/99 */
//DeadCode CSB 28/05/99	/* TEST CODE CSB 18/05/99 */	static SLong NewElev = 0;
//DeadCode CSB 28/05/99	/* TEST CODE CSB 18/05/99 */	Pos.y = 67000;
//DeadCode CSB 28/05/99	/* TEST CODE CSB 18/05/99 */	FP ClimbPitch = AngleSign(CalcAngle(ControlledAC->velhori, ControlledAC->vely));
//DeadCode CSB 28/05/99	/* TEST CODE CSB 18/05/99 */	FP DesPitch = Degs2Rads(-80);
//DeadCode CSB 28/05/99	/* TEST CODE CSB 18/05/99 */	NewElev -= 1000 * (DesPitch - ClimbPitch);
//DeadCode CSB 28/05/99	/* TEST CODE CSB 18/05/99 */	MODLIMIT(NewElev, 32767);
//DeadCode CSB 28/05/99	/* TEST CODE CSB 18/05/99 */	Elevator = NewElev - 10000 * (DesPitch - ClimbPitch);
//DeadCode CSB 28/05/99	/* TEST CODE CSB 18/05/99 */	MODLIMIT(Elevator, 32767);
//DeadCode CSB 28/05/99	/* TEST CODE CSB 18/05/99 */
//DeadCode CSB 28/05/99		Ori.x.x = 1;
//DeadCode CSB 28/05/99		Ori.x.y = 0;
//DeadCode CSB 28/05/99		Ori.x.z = 0;
//DeadCode CSB 28/05/99		Ori.y.x = 0;
//DeadCode CSB 28/05/99		Ori.y.y = 0;
//DeadCode CSB 28/05/99		Ori.y.z = 1;
//DeadCode CSB 28/05/99		Ori.z.x = 0;
//DeadCode CSB 28/05/99		Ori.z.y = -1;
//DeadCode CSB 28/05/99		Ori.z.z = 0;
//DeadCode CSB 28/05/99	
//DeadCode CSB 28/05/99	//DeadCode CSB 28/05/99		Pos.y = 67000;
//DeadCode CSB 28/05/99	//DeadCode CSB 28/05/99		Pos.y = 1167000;
//DeadCode CSB 28/05/99		Pos.y = 1867000;
//DeadCode CSB 28/05/99		FP d      = AmbDensity * 10000;
//DeadCode CSB 28/05/99		FP AltISA = 802729 * d*d*d*d*d*d - 3358891 * d*d*d*d*d + 5531629 * d*d*d*d - 4561006 * d*d*d + 2002783 * d*d - 508295 * d + 98238;

//DeadCode CSB 28/05/99		PrintVar(40, 18, "Alt  %.0f ", AltISA);
//DeadCode CSB 28/05/99		PrintVar(40, 20, "Velx %.2f ", Vel.x);
//DeadCode CSB 28/05/99		PrintVar(40, 21, "Vely %.2f ", Vel.y);
//DeadCode CSB 28/05/99		PrintVar(40, 22, "Velz %.2f ", Vel.z);
//DeadCode CSB 28/05/99		PrintVar(40, 23, "Accz %.4f ", Acc.z);

//DeadCode CSB 01/06/99		{
//DeadCode CSB 01/06/99			PrintVar(40, 5, "Pitch   %.1f ", FP(ControlledAC->pitch / 182.0));
//DeadCode CSB 01/06/99			PrintVar(40, 6, "Vel     %.1f ", FP(ControlledAC->vel / 10.0));
//DeadCode CSB 01/06/99			PrintVar(40, 7, "ROC     %.1f ", FP(ControlledAC->vely / 10.0));
//DeadCode CSB 01/06/99			PrintVar(40, 9, "Acc     %.1f ", FP(Acc.z));
//DeadCode CSB 01/06/99			PrintVar(40, 12, "Stores  %.1f ", FP(ControlledAC->weap.left.drag + ControlledAC->weap.centre.drag + ControlledAC->weap.right.drag));
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99			PrintVar(40, 15, "M Velx  %.2f ", Vel.x);
//DeadCode CSB 01/06/99			PrintVar(40, 16, "M Vely  %.2f ", Vel.y);
//DeadCode CSB 01/06/99			PrintVar(40, 17, "M Velz  %.2f ", Vel.z);
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99			PrintVar(60, 15, "A Velx  %.1f ", FP(ControlledAC->velx / 10.0));
//DeadCode CSB 01/06/99			PrintVar(60, 16, "A Vely  %.1f ", FP(ControlledAC->vely / 10.0));
//DeadCode CSB 01/06/99			PrintVar(60, 17, "A Velz  %.1f ", FP(ControlledAC->velz / 10.0));
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99		}

//DeadCode CSB 03/06/99		PrintString(0, 21, "F86 ME");
//DeadCode CSB 03/06/99		PrintVar(10, 21, "Vel       %.2f ", FP(Speed));
//DeadCode CSB 03/06/99		PrintVar(10, 22, "PitchRate %.2f ", FP(RotVel.x * 5730.0));
//DeadCode CSB 03/06/99		PrintVar(10, 23, "Mass      %.2f ", FP(Mass * 0.01));
//DeadCode CSB 03/06/99		PrintVar(10, 24, "Density   %.3f ", FP(AmbDensity * 10000.0));


//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar( 0, 10, "Left %.0f "  , FP(ControlledAC->weap.left.drag));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar(30, 10, "Centre %.0f ", FP(ControlledAC->weap.centre.drag));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar(60, 10, "Right %.0f " , FP(ControlledAC->weap.right.drag));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar( 0, 12, "Left %.0f "  , FP(ControlledAC->weap.left.mass * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar(30, 12, "Centre %.0f ", FP(ControlledAC->weap.centre.mass * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar(60, 12, "Right %.0f " , FP(ControlledAC->weap.right.mass * 0.00001));
//DeadCode CSB 25/06/99	
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar( 0, 15, "Left %.0f "  , FP(ControlledAC->weap.left.int_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar(30, 15, "Centre %.0f ", FP(ControlledAC->weap.centre.int_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar(60, 15, "Right %.0f " , FP(ControlledAC->weap.right.int_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar( 0, 16, "Left %.0f "  , FP(ControlledAC->weap.left.ext_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar(30, 16, "Centre %.0f ", FP(ControlledAC->weap.centre.ext_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */	PrintVar(60, 16, "Right %.0f " , FP(ControlledAC->weap.right.ext_fuel * 0.00001));

//DeadCode CSB 09/07/99		PrintVar(40, 24, "Frame %.0f ", FP(FrameCount));

//**********************************************
//********  TEST CODE	//CSB 07/05/99	********
//**********************************************
	
	if(!(FrameCount & EVERY256cs))	//This will do the following commands for each aircraft
	{								//once every n operations.
		MMC.Sky.Ambient (Pos.y, AmbDensity, AmbTemp, AmbPres);
		FP FuelUsageRate = CalcFuelRate(ControlledAC);
		ControlledAC->FuelLeft(FuelUsageRate);
		UpdateMassInertias(ControlledAC);
		Persons2::PlayerGhostAC->weap.right=ControlledAC->weap.right;
		Persons2::PlayerGhostAC->weap.left=ControlledAC->weap.left;
		Persons2::PlayerGhostAC->weap.centre=ControlledAC->weap.centre;
		//Calculates the rate of fuel burn and subtacts it from the fuel and total mass
	}
	FrameCount++;

	if((FirstCycle) && (ControlledAC->vel > 100))
		TrimAircraft(ControlledAC);

	CalcAirVel (ControlledAC);


#ifdef CALIBRATION_CODE
	CalibrationInputs ();
#endif

	MODEL_DT = 2;						//rdh	
//DeadCode AMM 29Jun99 	MODEL_LOOPS = 1;

//DeadCode CSB 03/03/99	if(!(FrameCount & 0x0001))
//DeadCode AMM 29Jun99 	for (ULong loops = MODEL_LOOPS; loops; loops--)
	{
		GearTouched = FALSE;
		GearSkid = FALSE;

		if(!(FrameCount & EVERY8cs) || (FirstCycle) )
		{
			MODEL_DT *= 4;
			ProcessEngines (ControlledAC);
			MODEL_DT /= 4;
		}

		ProcessDevices ();

		TotalBuffet = 0.0;
		ProcessMainElements (ControlledAC);
	
		FCRD force;
		FCRD moment;

		NullVec (force);
		NullVec (moment);

		CalcNettForceMoment (force, moment);

		if( (Save_Data.flightdifficulty [FD_EXCESSIVEACCELDAMAGE]) && (!(FrameCount & EVERY8cs)) )
			WingDamage(ControlledAC, force.y);
		
		force.z += ControlledAC->weap.weapforce;

	
		ProcessGears(ControlledAC, force.x);

		PTHRUSTPOINT pThrust = ThrustList;
		while (pThrust != NULL)
		{
			if((Save_Data.flightdifficulty [FD_POWERBOOST]) && (!GearTouched))
			{
				pThrust->Force.x *= PowerBoost;
				pThrust->Force.y *= PowerBoost;
				pThrust->Force.z *= PowerBoost;
			}
			FCRD dmoment;
			AddVec (force, force, pThrust->Force);
			AddVec (moment, moment, pThrust->Moment);
			CPrd (dmoment, pThrust->Force, pThrust->Pos);
			AddVec (moment, moment, dmoment);
			pThrust = pThrust->List.NextItem ();
		}

		// Gear
		PGEAR pGear = GearList;
		while( (pGear != NULL) && (GearTouched) )
		{
			if(pGear->Touched)
			{
				FCRD dmoment;
				AddVec(force, force, pGear->TyreForce);
				CPrd (dmoment, pGear->TyreForce, pGear->WheelPos);
				AddVec (moment, moment, dmoment);
			}
			pGear = pGear->List.NextItem ();
		}

		
		if(Type == AT_F51D)
			if((GearTouched) && (Speed < 25))
				if(moment.x < 0)
					moment.x += (25.0 - Speed) * (1000000.0 / 25.0);	//Stops P51D falling over on its nose with easy flight options on	//CSB 04/06/99	
	
		CopyVec (force, NettForce);
		CopyVec (moment, NettMoment);


//DeadCode CSB 01/03/99			ProcessAeroCtrls ();
//DeadCode CSB 01/03/99			ProcessAeroCouples ();

		CalcAcc ();
		CalcRotAcc ();

		MovePilotEye();
  
//DeadCode CSB 22/12/98			if(Save_Data.flightdifficulty [FD_POWERBOOST]) Acc.z *= 3;
//DeadCode CSB 02/03/99	FP Energy = 0;
//DeadCode CSB 02/03/99	if ( (Manual_Pilot.ControlledAC2 == ControlledAC) )
//DeadCode CSB 02/03/99	{
//DeadCode CSB 02/03/99		Energy = Mass/100 * (9.8065 * Pos.y / 100 + 0.5 * (Vel.x*Vel.x + Vel.y*Vel.y + Vel.z*Vel.z) );
//DeadCode CSB 02/03/99		Energy   += 0.5 /100 * (RotInertia.x*RotVel.x*RotVel.x + RotInertia.y*RotVel.y*RotVel.y + RotInertia.z*RotVel.z*RotVel.z);
//DeadCode CSB 02/03/99	}


#ifdef LOCK_X_Z_POS
		FP posx = Pos.x;
		FP posy = Pos.y;
		FP posz = Pos.z;
		TransInt (ALL);
		Pos.x = posx;
		Pos.y = posy;
		Pos.z = posz;
		RotInt (ALL);
#else
//DeadCode CSB 23/02/99			TransInt (ALL, 0.5);
		RotInt (ALL);	//Fix This !!!!
		TransInt (ALL, 1);	//Fix This !!!!
	
//DeadCode CSB 05/04/99	//CHEAT SPEED UP !!!!!!!!!!!			//CSB 03/04/99	
//DeadCode CSB 05/04/99	if(Key_Tests.KeyHeld3d (SENS_UP))
//DeadCode CSB 05/04/99	{
//DeadCode CSB 05/04/99		TransInt (ALL, 1);
//DeadCode CSB 05/04/99		TransInt (ALL, 1);
//DeadCode CSB 05/04/99	}
//DeadCode CSB 05/04/99	//END CHEAT !!!!!!!!!!!!!

#endif

	}
	CheckGearPos(ControlledAC);

//DeadCode DAW 07May99 	UpdateAirStruc (ControlledAC);
	SetPlayerMoving(ControlledAC);


	Instruments (ControlledAC);

	Animations (ControlledAC);
	Ground (ControlledAC);

	AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;

	if(EngineList)
	{
		SWord ThrustVol;
		if (EngineList->Type == ET_PISTON)
			ThrustVol = (255.0 * EngineList->Power) / 1590.0;			//RJS 14Jan99 CSB 15Sep99

		if (EngineList->Type == ET_JET)
		{
			ThrustVol = (170 * EngineList->Thrust) / EngineList->T100;			//RJS 14Jan99
			
			if(Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL])
				if(Inst.ExhaustTemp > 225)	//Throttle advanced too quickly
					if(FrameCount & 0x0002)
						ThrustVol = (ThrustVol * (255 - Inst.ExhaustTemp)) / (255 - 225);
		}
		_Miles.PlayEngine(adptr->CANOPY1,ControlledAC,Inst.Rpm1,ControlledAC->vel, ThrustVol);//RJS 06Oct98
	}

	_Miles.PlayWindyMiller(ControlledAC);										//RJS 21May99
	
//	Force Feedback Stuff		//CSB		21/8/98
	if (_Analogue.ForceAxes[0])
		CalcStickForceFeedback();	//fix this !!!!

//DeadCode CSB 01/07/99		static FCRD AveRotVel;
	if(FirstCycle)
		NullVec(AveRotVel);

	const fSmooth = 75;
	AveRotVel.x = ((fSmooth - 1) * AveRotVel.x + RotVel.x) / fSmooth;//AMM 25Jun99
	AveRotVel.y = ((fSmooth - 1) * AveRotVel.y + RotVel.y) / fSmooth;//AMM 25Jun99
	AveRotVel.z = ((fSmooth - 1) * AveRotVel.z + RotVel.z) / fSmooth;//AMM 25Jun99
	FirstCycle = FALSE;

	
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	static SLong OldX = Persons2::PlayerSeenAC->World.X;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	static SLong OldY = Persons2::PlayerSeenAC->World.Y;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	static SLong OldZ = Persons2::PlayerSeenAC->World.Z;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	SLong _oldX = OldX;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	SLong _oldY = OldY;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	SLong _oldZ = OldZ;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	if(Persons2::PlayerSeenAC->World.X != OldX)
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */		int breakpoint0 = 0;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	if(Persons2::PlayerSeenAC->World.Y != OldY)
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */		int breakpoint0 = 0;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	if(Persons2::PlayerSeenAC->World.Z != OldZ)
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */		int breakpoint0 = 0;

	UpdateAirStruc (ControlledAC);

//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	OldX = Persons2::PlayerSeenAC->World.X;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	OldY = Persons2::PlayerSeenAC->World.Y;
//DeadCode CSB 23/06/99	/* TEST CODE CSB 23/06/99 */	OldZ = Persons2::PlayerSeenAC->World.Z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ACMBase
//Author		Andrew McRae
//Date			Thu 8 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ACMBase (AirStrucPtr const ControlledAC)
{
//**********************************************
//********  TEST CODE	//CSB 07/05/99	********
//**********************************************
/*
	if (Key_Tests.KeyPress3d (SENS_UP))
	{
		AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;
		SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->LEFTWINGIN, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->RIGHTWINGIN, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->LEFTWINGOUT, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->RIGHTWINGOUT, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->TAIL, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->PILOTLEFT, BS_DEAD);
	}
*/

//DeadCode CSB 01/06/99		PrintVar(20, 2, "Range  %.0f ", (FP)(ControlledAC->Range / 100.0));
//DeadCode CSB 01/06/99		PrintVar(20, 3, "Vel    %.1f ", (FP)(ControlledAC->vel / 10.0));
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99		PrintVar(20, 5, "Accel  %.4f ", (FP)(ControlledAC->CalcAccel(32000) / 2560.0));
//DeadCode CSB 01/06/99		PrintVar(20, 6, "Deccel %.4f ", (FP)(ControlledAC->CalcAccel(0)     / 2560.0));
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99		PrintVar(20, 8, "Acc.z  %.4f ", (FP)(Acc.z * 100.0));
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99		
//DeadCode CSB 01/06/99		PrintVar(20, 10, "Thrust %.0f ", (FP)ControlledAC->fly.thrustpercent);
	
//**********************************************
//********  TEST CODE	//CSB 07/05/99	********
//**********************************************

		
	if(!(FrameCount & EVERY256cs))		//This will do the following commands for each aircraft
	{								//once every n operations.
		MMC.Sky.Ambient (Pos.y, AmbDensity, AmbTemp, AmbPres);
//DeadCode AMM 29Jun99 		FP FuelUsageRate = CalcFuelRate(ControlledAC);
//DeadCode AMM 29Jun99 		ControlledAC->FuelLeft(FuelUsageRate);	
	}
//DeadCode AMM 29Jun99 	FrameCount++;

	if(FirstCycle) TrimAircraft(ControlledAC);

	CalcAirVel (ControlledAC);

	if (!Controlled) ACMModel.Pilot (ControlledAC);

	MODEL_DT = 2;
//DeadCode AMM 29Jun99 	MODEL_LOOPS = 1;

//DeadCode AMM 29Jun99 	for (ULong loops = MODEL_LOOPS; loops; loops--)
	{
		GearTouched = FALSE;
		GearSkid = FALSE;

		if(!(FrameCount & EVERY8cs) || (FirstCycle) )
		{
			MODEL_DT *= 4;
			ProcessEngines (ControlledAC);
			MODEL_DT /= 4;
		}

		ProcessDevices ();

		TotalBuffet = 0;
		ProcessMainElements (ControlledAC);

		FCRD force;
		FCRD moment;

		NullVec (force);
		NullVec (moment);

		CalcNettForceMoment (force, moment);

		force.z += ControlledAC->weap.weapforce;
		
		// ThrustPoints
		PTHRUSTPOINT pThrust = ThrustList;
		while (pThrust != NULL)
		{
			FCRD dmoment;
			AddVec (force, force, pThrust->Force);
			AddVec (moment, moment, pThrust->Moment);
			CPrd (dmoment, pThrust->Force, pThrust->Pos);
			AddVec (moment, moment, dmoment);
			pThrust = pThrust->List.NextItem ();
		}

//DeadCode CSB 18/03/99			ProcessGears(ControlledAC, force.x);
//DeadCode CSB 18/03/99			// Gear
//DeadCode CSB 18/03/99			PGEAR pGear = GearList;
//DeadCode CSB 18/03/99			while( (pGear != NULL) && (GearTouched) )
//DeadCode CSB 18/03/99			{
//DeadCode CSB 18/03/99				if(pGear->Touched)
//DeadCode CSB 18/03/99				{
//DeadCode CSB 18/03/99					FCRD dmoment;
//DeadCode CSB 18/03/99					AddVec(force, force, pGear->TyreForce);
//DeadCode CSB 18/03/99					CPrd (dmoment, pGear->TyreForce, pGear->WheelPos);
//DeadCode CSB 18/03/99					AddVec (moment, moment, dmoment);
//DeadCode CSB 18/03/99				}
//DeadCode CSB 18/03/99				pGear = pGear->List.NextItem ();
//DeadCode CSB 18/03/99			}


		CopyVec (force, NettForce);
		CopyVec (moment, NettMoment);

		CalcAcc ();
	   
		CalcRotAcc ();

		
		if( (CheatAcc.x != 32767) || (CheatAcc.y != 32767) || (CheatAcc.z != 32767) )
		{
			FCRD OldAcc;
			OldAcc.x = NettForce.x / Mass;
			OldAcc.y = NettForce.y / Mass;
			OldAcc.z = NettForce.z / Mass;
			ModifyAcc(OldAcc, CheatAcc);
		}

#ifdef LOCK_X_Z_POS
		FP posx = Pos.x;
		FP posz = Pos.z;
		TransInt (ALL);
		Pos.x = posx;
		Pos.z = posz;
		RotInt (ALL);
#else
//DeadCode CSB 23/02/99			TransInt (ALL, 0.5);
		RotInt (ALL);
		TransInt (ALL, 1.0);
#endif

	}

	if(!(FrameCount & EVERY256cs))		//This will do the following commands for each aircraft
	{								//once every n operations.
		FP FuelUsageRate = CalcFuelRate(ControlledAC);
		ControlledAC->FuelLeft(FuelUsageRate);	
	}
	FrameCount++;

	CheatAcc.x = 32767;
	CheatAcc.y = 32767;
	CheatAcc.z = 32767;

//DeadCode CSB 18/03/99		CheckGearPos(ControlledAC);

	UpdateAirStruc (ControlledAC);


	Instruments (ControlledAC);

	Animations (ControlledAC);
	Ground (ControlledAC);

	FirstCycle = FALSE;

//#define ACM_PILOT_DATA
//Testing ACM Manoeuvres !!!!!!!!!!!!!!!
#ifdef ACM_PILOT_DATA
	PrintVar( 0,  2, "Alt  %.0f ", (FP)Pos.y / 100);
	PrintVar( 0,  3, "Vel  %.1f ", AirSpeed   );
	PrintVar( 0,  4, "Mach %.2f ", Inst.MachNo);

	PrintVar(15,  2, "Pitch %.1f ", Inst.PitchAngle);
	PrintVar(15,  3, "Roll  %.1f ", Inst.BankAngle );
	PrintVar(15,  4, "Headg %.1f ", Inst.HdgAngle  );

	PrintVar(30,  2, "AirVel.x %.1f ", -AirVel.x);
	PrintVar(30,  3, "AirVel.y %.1f ", -AirVel.y);
	PrintVar(30,  4, "AirVel.z %.1f ", -AirVel.z);

	PrintVar(45,  2, "Elevator %.0f ", (FP)(Elevator / 327.67));
	PrintVar(45,  3, "Aileron  %.0f ", (FP)(Aileron  / 327.67));
	PrintVar(45,  4, "Rudder   %.0f ", (FP)(Rudder   / 327.67));
	PrintVar(45,  5, "Throttle %.0f ", (FP)(ControlledAC->fly.thrustpercent));

	PMAINPLANE pMainPlane = MainPlaneList;
	PrintVar( 0,  8, "Aoa  %.1f ", (FP)(57.3 * pMainPlane->aoa[1][1]) );
	PrintVar(15,  8, " %.1f " 	 , (FP)(57.3 * pMainPlane->aoa[1][0]) );
	PrintVar(25,  8, " %.1f "	 , (FP)(57.3 * pMainPlane->aoa[0][0]) );
	PrintVar(35,  8, " %.1f "	 , (FP)(57.3 * pMainPlane->aoa[0][1]) );

	PrintVar(0,  10, "T Pitch %.1f ", (FP)( (ControlledAC->PitchIntercept - ControlledAC->pitch) / 182.04) );
	PrintVar(0,  11, "T Headg %.1f ", (FP)( (ControlledAC->HdgIntercept - ControlledAC->hdg)  / 182.04) );
	PrintVar(0,  12, "T Range %.0f ", (FP)(ControlledAC->Range / 100) );

	PrintVar(20,  10, "C Pitch %.0f ", (FP)( (ControlledAC->PitchIntercept) / 182.04) );
	PrintVar(20,  11, "C Roll  %.0f ", (FP)( (ACMModel.CtrlRoll           ) / 182.04) );
	PrintVar(20,  12, "C Headg %.0f ", (FP)( (ControlledAC->HdgIntercept  ) / 182.04) );


	switch (Type)
	{
		case AT_F86A:		{ PrintString(0, 23, "AT_F86A		");    break; }
		case AT_F86E:		{ PrintString(0, 23, "AT_F86E		");    break; }
		case AT_F86F:		{ PrintString(0, 23, "AT_F86F		");    break; }
		case AT_MIG15:		{ PrintString(0, 23, "AT_MIG15		");    break; }
		case AT_MIG15BIS:	{ PrintString(0, 23, "AT_MIG15BIS	");    break; }
		case AT_F84E:		{ PrintString(0, 23, "AT_F84E		");    break; }
		case AT_F80C:		{ PrintString(0, 23, "AT_F80C		");    break; }
		case AT_F9F2:		{ PrintString(0, 23, "AT_F9F2		");    break; }
		case AT_F8:			{ PrintString(0, 23, "AT_F8			");    break; }
		case AT_F51D:		{ PrintString(0, 23, "AT_F51D		");    break; }
		case AT_F82G:		{ PrintString(0, 23, "AT_F82G		");    break; }
		case AT_YAK9:		{ PrintString(0, 23, "AT_YAK9		");    break; }
		case AT_F4U5:		{ PrintString(0, 23, "AT_F4U5		");    break; }
		case AT_SFURY:		{ PrintString(0, 23, "AT_SFURY		");    break; }
		case AT_FFLY:		{ PrintString(0, 23, "AT_FFLY		");    break; }
		case AT_A1:			{ PrintString(0, 23, "AT_A1			");    break; }
	}
	
	switch (ControlledAC->ai.manoeuvre)
	{
		case MANOEUVRE_SELECT:						{ PrintString(0,  24, "MANOEUVRE_SELECT						");    break; }
		case MANOEUVRE_LOOKROUND:					{ PrintString(0,  24, "MANOEUVRE_LOOKROUND					");    break; }
		case MANOEUVRE_WELDEDWINGMAN:				{ PrintString(0,  24, "MANOEUVRE_WELDEDWINGMAN				");    break; }
		case MANOEUVRE_BAILOUT:						{ PrintString(0,  24, "MANOEUVRE_BAILOUT					");    break; }
		case MANOEUVRE_TOPCOVER:					{ PrintString(0,  24, "MANOEUVRE_TOPCOVER					");    break; }
		case MANOEUVRE_LINEABREAST:					{ PrintString(0,  24, "MANOEUVRE_LINEABREAST				");    break; }
		case MANOEUVRE_SCATTER:						{ PrintString(0,  24, "MANOEUVRE_SCATTER					");    break; }
		case MANOEUVRE_PINCER:						{ PrintString(0,  24, "MANOEUVRE_PINCER						");    break; }
		case MANOEUVRE_MULTIWAVE:					{ PrintString(0,  24, "MANOEUVRE_MULTIWAVE					");    break; }
		case MANOEUVRE_DIVEANDZOOM:					{ PrintString(0,  24, "MANOEUVRE_DIVEANDZOOM				");    break; }
		case MANOEUVRE_LEADPURSUIT:					{ PrintString(0,  24, "MANOEUVRE_LEADPURSUIT				");    break; }
		case MANOEUVRE_LAGPURSUIT:					{ PrintString(0,  24, "MANOEUVRE_LAGPURSUIT					");    break; }
		case MANOEUVRE_CIRCUMVENT:					{ PrintString(0,  24, "MANOEUVRE_CIRCUMVENT					");    break; }
		case MANOEUVRE_ROUNDABOUT:					{ PrintString(0,  24, "MANOEUVRE_ROUNDABOUT					");    break; }
		case MANOEUVRE_SPLITMANOEUVRE:				{ PrintString(0,  24, "MANOEUVRE_SPLITMANOEUVRE				");    break; }
		case MANOEUVRE_HEADON:						{ PrintString(0,  24, "MANOEUVRE_HEADON						");    break; }
		case MANOEUVRE_LINEASTERN:					{ PrintString(0,  24, "MANOEUVRE_LINEASTERN					");    break; }
		case MANOEUVRE_BARRELROLLATTACK:			{ PrintString(0,  24, "MANOEUVRE_BARRELROLLATTACK			");    break; }
		case MANOEUVRE_SCISSORS:					{ PrintString(0,  24, "MANOEUVRE_SCISSORS					");    break; }
		case MANOEUVRE_MILDSCISSORS:				{ PrintString(0,  24, "MANOEUVRE_MILDSCISSORS				");    break; }
		case MANOEUVRE_TURNINGFIGHT:				{ PrintString(0,  24, "MANOEUVRE_TURNINGFIGHT				");    break; }
		case MANOEUVRE_SPLITS:						{ PrintString(0,  24, "MANOEUVRE_SPLITS						");    break; }
		case MANOEUVRE_ZOOMANDDROP:					{ PrintString(0,  24, "MANOEUVRE_ZOOMANDDROP				");    break; }
		case MANOEUVRE_STRAIGHTANDLEVEL:			{ PrintString(0,  24, "MANOEUVRE_STRAIGHTANDLEVEL			");    break; }
		case MANOEUVRE_SPINOUT:						{ PrintString(0,  24, "MANOEUVRE_SPINOUT					");    break; }
		case MANOEUVRE_DIVEFORHOME:					{ PrintString(0,  24, "MANOEUVRE_DIVEFORHOME				");    break; }
		case MANOEUVRE_GOHOME:						{ PrintString(0,  24, "MANOEUVRE_GOHOME						");    break; }
		case MANOEUVRE_MAKEFORFRIENDLY:				{ PrintString(0,  24, "MANOEUVRE_MAKEFORFRIENDLY			");    break; }
		case MANOEUVRE_MOVEAWAY:					{ PrintString(0,  24, "MANOEUVRE_MOVEAWAY					");    break; }
		case MANOEUVRE_ACCIDENTALSPINOUT:			{ PrintString(0,  24, "MANOEUVRE_ACCIDENTALSPINOUT			");    break; }
		case MANOEUVRE_VERTICALLOOP:				{ PrintString(0,  24, "MANOEUVRE_VERTICALLOOP				");    break; }
		case MANOEUVRE_IMMELMANNTURN:				{ PrintString(0,  24, "MANOEUVRE_IMMELMANNTURN				");    break; }
		case MANOEUVRE_HEADONOFFSET:				{ PrintString(0,  24, "MANOEUVRE_HEADONOFFSET				");    break; }
		case MANOEUVRE_IMMELMANN:					{ PrintString(0,  24, "MANOEUVRE_IMMELMANN					");    break; }
		case MANOEUVRE_STAYWITHPREY:				{ PrintString(0,  24, "MANOEUVRE_STAYWITHPREY				");    break; }
		case MANOEUVRE_CLIMBFORHOME:				{ PrintString(0,  24, "MANOEUVRE_CLIMBFORHOME				");    break; }
		case MANOEUVRE_STRAIGHTDIVE:				{ PrintString(0,  24, "MANOEUVRE_STRAIGHTDIVE				");    break; }
		case MANOEUVRE_STANDONTAIL:					{ PrintString(0,  24, "MANOEUVRE_STANDONTAIL				");    break; }
		case MANOEUVRE_SHOOTTOFRIGHTEN:				{ PrintString(0,  24, "MANOEUVRE_SHOOTTOFRIGHTEN			");    break; }
		case MANOEUVRE_SHOOTTOOEARLY:				{ PrintString(0,  24, "MANOEUVRE_SHOOTTOOEARLY				");    break; }
		case MANOEUVRE_GAINHEIGHT:					{ PrintString(0,  24, "MANOEUVRE_GAINHEIGHT					");    break; }
		case MANOEUVRE_LAGROLL:						{ PrintString(0,  24, "MANOEUVRE_LAGROLL					");    break; }
		case MANOEUVRE_EXTENSION:					{ PrintString(0,  24, "MANOEUVRE_EXTENSION					");    break; }
		case MANOEUVRE_DIVINGSPIN:					{ PrintString(0,  24, "MANOEUVRE_DIVINGSPIN					");    break; }
		case MANOEUVRE_REVERSETURN:					{ PrintString(0,  24, "MANOEUVRE_REVERSETURN				");    break; }
		case MANOEUVRE_SELFASBAIT:					{ PrintString(0,  24, "MANOEUVRE_SELFASBAIT					");    break; }
		case MANOEUVRE_JINK:						{ PrintString(0,  24, "MANOEUVRE_JINK						");    break; }
		case MANOEUVRE_BREAKTURN:					{ PrintString(0,  24, "MANOEUVRE_BREAKTURN					");    break; }
		case MANOEUVRE_LAZYTURN:					{ PrintString(0,  24, "MANOEUVRE_LAZYTURN					");    break; }
		case MANOEUVRE_BREAK180:					{ PrintString(0,  24, "MANOEUVRE_BREAK180					");    break; }
		case MANOEUVRE_BREAKLOW:					{ PrintString(0,  24, "MANOEUVRE_BREAKLOW					");    break; }
		case MANOEUVRE_BREAKHIGH:					{ PrintString(0,  24, "MANOEUVRE_BREAKHIGH					");    break; }
		case MANOEUVRE_BREAK90:						{ PrintString(0,  24, "MANOEUVRE_BREAK90					");    break; }
		case MANOEUVRE_HIGBARRELROLL:				{ PrintString(0,  24, "MANOEUVRE_HIGBARRELROLL				");    break; }
		case MANOEUVRE_PANICTURN:					{ PrintString(0,  24, "MANOEUVRE_PANICTURN					");    break; }
		case MANOEUVRE_UNBALANCEDFLIGHT:			{ PrintString(0,  24, "MANOEUVRE_UNBALANCEDFLIGHT			");    break; }
		case MANOEUVRE_LOWALT:						{ PrintString(0,  24, "MANOEUVRE_LOWALT						");    break; }
		case MANOEUVRE_SNAPSHOT:					{ PrintString(0,  24, "MANOEUVRE_SNAPSHOT					");    break; }
		case MANOEUVRE_STAYONTAIL:					{ PrintString(0,  24, "MANOEUVRE_STAYONTAIL					");    break; }
		case MANOEUVRE_TURNTOHDGANDPITCH:			{ PrintString(0,  24, "MANOEUVRE_TURNTOHDGANDPITCH			");    break; }
		case MANOEUVRE_HOTSIDELAGPURSUITFIGHT:		{ PrintString(0,  24, "MANOEUVRE_HOTSIDELAGPURSUITFIGHT		");    break; }
		case MANOEUVRE_SANDWICHMANOEUVRES:			{ PrintString(0,  24, "MANOEUVRE_SANDWICHMANOEUVRES			");    break; }
		case MANOEUVRE_SUSTAINEDTURN:				{ PrintString(0,  24, "MANOEUVRE_SUSTAINEDTURN				");    break; }
		case MANOEUVRE_HIGHYOYO:					{ PrintString(0,  24, "MANOEUVRE_HIGHYOYO					");    break; }
		case MANOEUVRE_ZOOM:						{ PrintString(0,  24, "MANOEUVRE_ZOOM						");    break; }
		case MANOEUVRE_LOWYOYO:						{ PrintString(0,  24, "MANOEUVRE_LOWYOYO					");    break; }
		case MANOEUVRE_INTERCEPTHIGH:				{ PrintString(0,  24, "MANOEUVRE_INTERCEPTHIGH				");    break; }
		case MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED:	{ PrintString(0,  24, "MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED	");    break; }
		case MANOEUVRE_GAINSPEED:					{ PrintString(0,  24, "MANOEUVRE_GAINSPEED					");    break; }
		case MANOEUVRE_SPINRECOVERY:				{ PrintString(0,  24, "MANOEUVRE_SPINRECOVERY				");    break; }
	}

	PrintVar(30, 24, "Phase %.0f ", (FP)ControlledAC->ai.ManStep);
	PrintVar(40, 24, "Time %.0f ", (FP)ControlledAC->manoeuvretime);
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcAirVel
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calcs Air velocity in local coords relative to aircraft cg
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcAirVel (AirStrucPtr const ControlledAC)
{
//	Sky.SetGusts (Save_Data.flightdifficulty [FD_WINDGUSTS]);

	FCRD wind;
	NullVec(wind);

	if((Save_Data.flightdifficulty [FD_WINDEFFECTS]) || (Save_Data.flightdifficulty [FD_WINDGUSTS]))
		MMC.Sky.GetWind (ControlledAC, wind, Pos.y);

//DeadCode CSB 03/12/98		if (!_Replay.Record && _Replay.Playback)
//DeadCode CSB 03/12/98		{
//DeadCode CSB 03/12/98			MMC.Sky.GetWind (ControlledAC,wind, Pos.y);									//D 02Apr98
//DeadCode CSB 03/12/98		}
//DeadCode CSB 03/12/98		else
//DeadCode CSB 03/12/98		{
//DeadCode CSB 03/12/98			wind.x=0;
//DeadCode CSB 03/12/98			wind.y=0;
//DeadCode CSB 03/12/98			wind.z=0;
//DeadCode CSB 03/12/98		}

	Speed = VecLen (Vel);

	// Botch to prevent aircraft rotating into					
	// wind when on ground and not moving.						
	FP wind_frac = 1;											
//DeadCode CSB 09/02/99		if (GearTouched && (Speed < 10)) wind_frac = Speed * 0.1;	


	AirVel.x = (wind_frac * wind.x) - Vel.x;
	AirVel.y = (wind_frac * wind.y) - Vel.y;
	AirVel.z = (wind_frac * wind.z) - Vel.z;

	TnsAxs (AirVel, AirVel, Ori);

//@	OldAirSpeed = AirSpeed;
	AirSpeed = VecLen (AirVel);

	// Instrument Version of AirVel - without above botch
	InstAirVel.x = wind.x - Vel.x;								
	InstAirVel.y = wind.y - Vel.y;								
	InstAirVel.z = wind.z - Vel.z;								
	TnsAxs (InstAirVel, InstAirVel, Ori);						

	DynamicPressure = 0.5 * AmbDensity * AirSpeed * AirSpeed;

	Inst.MachNo = AirSpeed / FSqrt (402.7 * AmbTemp);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrimAircraft
//Author		Craig Beeston
//Date			Thu 26 Nov 1998
//
//Description	When a model is processed for the first time, the pitch is set to achieve 
//				1 g flight
//				Assumes only one Wing
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::TrimAircraft(AirStrucPtr const ControlledAC)
{
	MMC.Sky.Ambient (Pos.y, AmbDensity, AmbTemp, AmbPres);
	long wx, wy, wz;
//DeadCode CSB 10/06/99		MMC.Sky.GetWind(Pos.y, wx, wy, wz);
//DeadCode CSB 10/06/99		Vel.x += wx * 0.1;
//DeadCode CSB 10/06/99		Vel.y += wy * 0.1;
//DeadCode CSB 10/06/99		Vel.z += wz * 0.1;
	CalcAirVel(ControlledAC);
	ProcessDevices();
	UWord n = 0;

	FP OldAirVely = AirVel.y;

//DeadCode CSB 02/03/99		AirVel.z += 175;	//set speed to 75 m/s
//DeadCode CSB 02/03/99		AirVel.y =  25;
	
	for(;;)
	{
		FCRD NettForce, NettMoment;
		NullVec(NettForce);
		NullVec(NettMoment);

		ProcessMainElements(ControlledAC);
		CalcNettForceMoment(NettForce, NettMoment);

		FP NormG  = NettForce.y / (Mass * GRAVITY);
		
		FP GError = NormG - 1.0;
		if( (GError > -0.001) && (GError < 0.001) ) break;
		AirVel.y += AirVel.z * GError * 0.02;
		n += 1;
		if(n > 100) return;
	}

//DeadCode CSB 16/02/99		n = 0;
//DeadCode CSB 16/02/99		for(;;)
//DeadCode CSB 16/02/99		{
//DeadCode CSB 16/02/99			FCRD NettForce, NettMoment;
//DeadCode CSB 16/02/99			NullVec(NettForce);
//DeadCode CSB 16/02/99			NullVec(NettMoment);
//DeadCode CSB 16/02/99	
//DeadCode CSB 16/02/99			ProcessMainElements(ControlledAC);
//DeadCode CSB 16/02/99			CalcNettForceMoment(NettForce, NettMoment);
//DeadCode CSB 16/02/99			if( (NettMoment.x > -5000) && (NettMoment.x < 5000) ) break;
//DeadCode CSB 16/02/99			Elevator += (SWord)(NettMoment.x * 0.0005);//0.00025);
//DeadCode CSB 16/02/99			n += 1;
//DeadCode CSB 16/02/99			if(n > 100) return;
//DeadCode CSB 16/02/99		}

	FCRD DeltaVel;
	DeltaVel.x = 0;
	DeltaVel.y = OldAirVely - AirVel.y ;
	DeltaVel.z = 0;

//DEADCODE RDH 03/03/99 	DeltaVel.z = -175;

	TnsPnt(DeltaVel, DeltaVel, Ori);

	AddVec(Vel, Vel, DeltaVel);
	CalcAirVel(ControlledAC);

//DeadCode CSB 26/01/99		ElevatorTrim = Elevator;
	Elevator = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLocalGust
//Author		Craig Beeston
//Date			Mon 18 Jan 1999
//
//Description	Used to set the gust for an individual aircraft due to an explosion in the area
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetLocalGust(COORDS3D AcPos, COORDS3D HitPos, SWord Strength)
{
	FCRD DirVec;
	DirVec.x = AcPos.X - HitPos.X;
	DirVec.y = AcPos.Y - HitPos.Y;
	DirVec.z = AcPos.Z - HitPos.Z;

	NrmVec(DirVec, DirVec);

	Gust.ACTIVE = TRUE;
	
	Gust.Vec.x = DirVec.x * (FP)Strength;
	Gust.Vec.y = DirVec.y * (FP)Strength;
	Gust.Vec.z = DirVec.z * (FP)Strength;

	Gust.Time = 100;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitialiseEngines
//Author		Craig Beeston
//Date			Tue 24 Nov 1998
//
//Description	Processes all aircraft engines so that they start at approx the right speed
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::InitialiseEngines (AirStrucPtr const ControlledAC)
{
	PENGINE pEngine = EngineList;
	PGEAR   pGear   = GearList;
//DeadCode CSB 31/05/99		FP OldSpeed = 0.0;
//DeadCode CSB 31/05/99		FP SpeedDif = 0.0;

	if(Speed < 50)
		GearTouched = TRUE;

	SWord Temp_DT = MODEL_DT;
	if(Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL]) MODEL_DT	= 400;
	else MODEL_DT = 50;

	while(pEngine != NULL)
	{
		switch (pEngine->Type)
		{
			case ET_VOID:
			break;
				
			case ET_PISTON:
			{
//DeadCode CSB 31/05/99					if(GearTouched)
//DeadCode CSB 31/05/99					{
//DeadCode CSB 31/05/99						pEngine->Speed = 0.0;
//DeadCode CSB 31/05/99						pEngine->ProcessPistonEngine (ControlledAC);
//DeadCode CSB 31/05/99					}
//DeadCode CSB 31/05/99					else for(;;)
//DeadCode CSB 31/05/99					for(;;)
//DeadCode CSB 31/05/99					{
//DeadCode CSB 31/05/99						OldSpeed = pEngine->Speed;
//DeadCode CSB 31/05/99						pEngine->ProcessPistonEngine (ControlledAC);
//DeadCode CSB 31/05/99						SpeedDif = pEngine->Speed - OldSpeed;
//DeadCode CSB 31/05/99						if(SpeedDif < 0) SpeedDif *= -1;
//DeadCode CSB 31/05/99						if(SpeedDif < 10) break;
//DeadCode CSB 31/05/99					}
				if(GearTouched)
				{
					pEngine->Speed = ControlledAC->fly.thrustpercent * 2500 * 0.00001047197;
					pEngine->PropInc = 23;
					pEngine->SlipVel = 15.0 + 0.55 * ControlledAC->fly.thrustpercent;
					pEngine->PropVel = pEngine->SlipVel / 2.0;
					pEngine->SlipRot = 0;						//AMM 19Jan00
				}
				else
				{
					pEngine->Speed = 3000 * 0.001047197;
					pEngine->PropInc = 44;
					pEngine->SlipVel = Speed;
					pEngine->PropVel = Speed;
					pEngine->SlipRot = 0;						//AMM 19Jan00
				}
				break;
			}
		
			case ET_JET:
			{
				FP RootTempRatio = FSqrt(AmbTemp / 288.15);
				FP ThrustRatio = 0.01 * ControlledAC->fly.thrustpercent;
				pEngine->ThrustRpm->GetIndex(ThrustRatio, pEngine->SpeedRpm);
				pEngine->SpeedRpm *= pEngine->Rpm100;
				pEngine->SpeedRpm *= RootTempRatio;
				break;
			}
		}
		pEngine = pEngine->List.NextItem();
	}
	MODEL_DT = Temp_DT;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessEngines
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Process all aircraft engines
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ProcessEngines (AirStrucPtr const ControlledAC)
{
	if(FirstCycle) 
	{
		InitialiseEngines(ControlledAC);	//CSB 24/11/98
		return;
	}

	if(RestartEngine) 
	{
		RestartEngines(ControlledAC);
		RestartEngine = FALSE;
	}

	PENGINE pEngine = EngineList;
		AircraftAnimData*	adptr;
		adptr = (AircraftAnimData *)ControlledAC->Anim;
		ULong	damflagstate;

	if (pEngine == NULL)
		return;

	for (;;)
	{

		damflagstate = adptr->ENGINELEFTIN;								//RJS 21Feb97
		if  (		(adptr->ENGINELEFTOUT == BS_DEAD)
				||	(adptr->ENGINERIGHTOUT == BS_DEAD)
				||	(adptr->ENGINELEFTIN == BS_DEAD)
				||	(adptr->ENGINERIGHTIN == BS_DEAD)
			)
		{
			pEngine->Thrust = 0;
		}else
		{// Scale to 80% max thrust loss....

			damflagstate *= 5;										//RJS 21Feb97
			damflagstate >>= 4;										//RJS 21Feb97
			if (ControlledAC->fly.thrustpercent > (100 - damflagstate))//RJS 21Feb97
			{
				ControlledAC->fly.thrustpercent = 100 - damflagstate;//RJS 21Feb97
			}
			switch (pEngine->Type)
			{
				case ET_VOID:
				break;

				case ET_PISTON:
					{
						damflagstate = adptr->PROPLEFTIN;									//RJS 21Feb97
						if  (		(adptr->PROPLEFTOUT == BS_DEAD)
							||	(adptr->PROPRIGHTOUT == BS_DEAD)
							||	(adptr->PROPLEFTIN == BS_DEAD)
							||	(adptr->PROPRIGHTIN == BS_DEAD)
							)
						{
							pEngine->Thrust = 0;
						}else
						{// Scale to 50% max thrust loss....
							damflagstate *= 3;										//RJS 21Feb97
							damflagstate /= 15;										//RJS 21Feb97
							if (ControlledAC->fly.thrustpercent > (100 - damflagstate))//RJS 21Feb97
								ControlledAC->fly.thrustpercent = 100 - damflagstate;//RJS 21Feb97
							pEngine->ProcessPistonEngine (ControlledAC);
						}
						break;
					}
			
				case ET_JET:
					pEngine->ProcessJetEngine (ControlledAC);
					break;

			}
		}

		if(Manual_Pilot.ControlledAC2 == ControlledAC)
		{
//DeadCode CSB 04/06/99				if(Save_Data.flightdifficulty [FD_POWERBOOST])
//DeadCode CSB 04/06/99					pEngine->Thrust *= PowerBoost;
		}
		else
			if(ControlledAC->fly.thrustpercent == 0) 
				pEngine->Thrust = 0;

		pEngine = pEngine->List.NextItem();

		if (pEngine == NULL)
			break;

	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestartEngines
//Author		Craig Beeston
//Date			Tue 25 Nov 1998
//
//Description	Restarts all aircraft jet engines
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RestartEngines (AirStrucPtr const ControlledAC)
{
	PENGINE pEngine = EngineList;

	while (pEngine != NULL)
	{
		if( (pEngine->Type == ET_JET) && (pEngine->EngineOut) )
		{
			_Miles.PlaySample(FIL_SFX_NO_AMMO_CLICK, 8191);//5120);
//DeadCode CSB 03/03/99				_Miles.PlaySample(FIL_SFX_OFFICE_DRAWER2, 5120);
			_Miles.PlaySample(FIL_SFX_GUN_TANK2, 32767);
			if( (ControlledAC->fly.thrustpercent <= 25) )
//DeadCode CSB 03/03/99					(ControlledAC->fly.thrustpercent <= 50) )
				pEngine->EngineOut = FALSE;
		}
		pEngine = pEngine->List.NextItem ();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcFuelRate
//Author		Craig Beeston
//Date			Tue 15 Sep 1998
//
//Description	Calculates the total rate of fuel usage for all engines as a fraction
//				of the maximum fuel rate per engine.  i.e. 1 engine at < max thrust- usage < 1
//														   1 engine at max thrust  - usage = 1
//														   2 engines at max thrust - usage = 2
//
//Inputs		
//
//Returns		The rate of fuel usage for whole aircraft
//
//------------------------------------------------------------------------------
FP Model::CalcFuelRate (AirStrucPtr const ControlledAC)
{
	FP usage = 0;

	PENGINE pEngine = EngineList;

	while (pEngine != NULL)
	{
		FP RateTemp;
		if(pEngine->Type == ET_JET)
			RateTemp = pEngine->Thrust / pEngine->T100;// * (1 + 0.45 * Inst.MachNo);
		else
			RateTemp = pEngine->Power / pEngine->p0;
	
		if(RateTemp < 0.1) RateTemp = 0.1;

		usage += RateTemp;
		pEngine = pEngine->List.NextItem ();
	}

	return(usage);
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessDevices
//Author		Andrew McRae
//Date			Tue 12 Aug 1997
//
//Description	Flaps, slats, speed brakes, etc.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ProcessDevices ()
{

	DeltaCl = 0;
	DeltaCd = 0;
	DeltaCm = 0;
	DeltaAlpha = 0;

	PAERODEVICE pDevice = DeviceList;

	while (pDevice != NULL)
	{
		pDevice->Process ();
		pDevice = pDevice->List.NextItem ();
	}

}

void Model::GearUp (AirStrucPtr const ControlledAC)
{

	PAERODEVICE pDevice = DeviceList;

	while (pDevice != NULL)
	{
		pDevice->GearUp ();
		pDevice = pDevice->List.NextItem ();
	}
	SetGearAnimPos(ControlledAC,ANIM_GEAR_UP);
	SHAPE.NavigationLightsActive(ControlledAC, FALSE);
}

void Model::GearDown (AirStrucPtr const ControlledAC)
{

	PAERODEVICE pDevice = DeviceList;

	while (pDevice != NULL)
	{
		pDevice->GearDown ();
		pDevice = pDevice->List.NextItem ();
	}
	SetGearAnimPos(ControlledAC,ANIM_GEAR_DOWN);
	SHAPE.NavigationLightsActive(ControlledAC, TRUE);
}

//DeadCode CSB 01/03/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 01/03/99	//Procedure		ProcessAeroCtrls
//DeadCode CSB 01/03/99	//Author		Andrew McRae
//DeadCode CSB 01/03/99	//Date			Fri 31 Oct 1997
//DeadCode CSB 01/03/99	//
//DeadCode CSB 01/03/99	//Description	
//DeadCode CSB 01/03/99	//
//DeadCode CSB 01/03/99	//Inputs		
//DeadCode CSB 01/03/99	//
//DeadCode CSB 01/03/99	//Returns	
//DeadCode CSB 01/03/99	//
//DeadCode CSB 01/03/99	//------------------------------------------------------------------------------
//DeadCode CSB 01/03/99	void Model::ProcessAeroCtrls ()
//DeadCode CSB 01/03/99	{
//DeadCode CSB 01/03/99		// AeroCtrls
//DeadCode CSB 01/03/99	
//DeadCode CSB 01/03/99		PAEROCTRL pAeroCtrl = AeroCtrlList;
//DeadCode CSB 01/03/99		while (pAeroCtrl != NULL)
//DeadCode CSB 01/03/99		{
//DeadCode CSB 01/03/99			pAeroCtrl->Process ();
//DeadCode CSB 01/03/99			pAeroCtrl = pAeroCtrl->List.NextItem ();
//DeadCode CSB 01/03/99		}
//DeadCode CSB 01/03/99	
//DeadCode CSB 01/03/99	}
//DeadCode CSB 01/03/99	
//DeadCode CSB 01/03/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 01/03/99	//Procedure		ProcessAeroCouples
//DeadCode CSB 01/03/99	//Author		Andrew McRae
//DeadCode CSB 01/03/99	//Date			Fri 31 Oct 1997
//DeadCode CSB 01/03/99	//
//DeadCode CSB 01/03/99	//Description	
//DeadCode CSB 01/03/99	//
//DeadCode CSB 01/03/99	//Inputs		
//DeadCode CSB 01/03/99	//
//DeadCode CSB 01/03/99	//Returns	
//DeadCode CSB 01/03/99	//
//DeadCode CSB 01/03/99	//------------------------------------------------------------------------------
//DeadCode CSB 01/03/99	void Model::ProcessAeroCouples ()
//DeadCode CSB 01/03/99	{
//DeadCode CSB 01/03/99		// AeroCouples
//DeadCode CSB 01/03/99	
//DeadCode CSB 01/03/99		PAEROCOUPLE pAeroCouple = AeroCoupleList;
//DeadCode CSB 01/03/99		while (pAeroCouple != NULL)
//DeadCode CSB 01/03/99		{
//DeadCode CSB 01/03/99			pAeroCouple->Process ();
//DeadCode CSB 01/03/99			pAeroCouple = pAeroCouple->List.NextItem ();
//DeadCode CSB 01/03/99		}
//DeadCode CSB 01/03/99	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessMainElements
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Processes all aircraft elements
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ProcessMainElements (AirStrucPtr const ControlledAC)
{
//DeadCode CSB 25/02/99		PMODEL pModel = ControlledAC->fly.pModel;

	if(Inst.MachNo < MControlLoss0) MControlPower = 1;
	else if(Inst.MachNo > MControlLoss1) MControlPower = 0.2;
	else
	{
		MControlPower = (Inst.MachNo - MControlLoss0) / (MControlLoss1 - MControlLoss0);
		MControlPower = 1 - MControlPower * MControlPower;
		if(MControlPower < 0.25) MControlPower = 0.25;
	}

//DEADCODE RDH 01/03/99 	Spinning = FALSE;
	// MainPlane
	PMAINPLANE pMainPlane = MainPlaneList;
	while (pMainPlane != NULL)
	{
		pMainPlane->Process (ControlledAC);
		pMainPlane = pMainPlane->List.NextItem ();
	}


	// Surfaces
	PSURFACE pSurface = SurfaceList;
	while (pSurface != NULL)
	{
		if (pSurface->Type != ST_MAINPLANE)
			pSurface->Process (ControlledAC);
		pSurface = pSurface->List.NextItem ();
	}


	// Cylinder	//CSB 05/11/98
	PCYLINDER pCylinder = CylinderList;
	while (pCylinder != NULL)
	{
		pCylinder->Process (ControlledAC);
		pCylinder = pCylinder->List.NextItem ();
	}


	// ThrustPoints
	PTHRUSTPOINT pThrust = ThrustList;
	while (pThrust != NULL)
	{
		pThrust->Process ();
		pThrust = pThrust->List.NextItem ();
	}

	
	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])		//CSB	//03 Sep 98
		ProcessStoresDrag(ControlledAC);

//CSB  11/09/98
//Calculate the Moment which acts of the aircraft do to rotation about two or more axis at once

	FCRD TempFCRD;
	TempFCRD.x = RotVel.x * RotInertia.x;
	TempFCRD.y = RotVel.y * RotInertia.y;
	TempFCRD.z = RotVel.z * RotInertia.z;

	CPrd(InertiaMoment, TempFCRD, RotVel);
	
	InertiaMoment.x *= -1;
	InertiaMoment.y *= -1;
	InertiaMoment.z *= -1;
}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessStoresDrag
//Author		Craig Beeston
//Date			Thu 03 Sep 1998
//
//Description	Calculated the drag and yawing moment on the aircraft due to the 
//				weapons/drop tanks.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ProcessStoresDrag (AirStrucPtr const ControlledAC)
{
	StoresForce.x = 0.0;
	StoresForce.y = 0.0;
	StoresForce.z = -( ControlledAC->weap.left.drag + ControlledAC->weap.centre.drag 
						+ ControlledAC->weap.right.drag );
	StoresForce.z *= DynamicPressure;

	FP Pos = ControlledAC->fly.pModel->MainPlaneList->Pos[0][1].x;
	StoresMoment.x = 0.0;
	StoresMoment.y =  ControlledAC->weap.right.drag - ControlledAC->weap.left.drag;
	StoresMoment.y *= DynamicPressure * Pos;
	StoresMoment.z = 0.0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcNettForceMoment
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calculates total force and moment on the aircraft
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcNettForceMoment (FCRD& Force, FCRD& Moment)
{
	FCRD dmoment;

	// MainPlane
	PMAINPLANE pMainPlane = MainPlaneList;
	while (pMainPlane != NULL)
	{
		for(SWord wing = 0; wing < 2; wing++)
			for(SWord section = 0; section < 2; section++)
			{
				AddVec (Force,  Force,  pMainPlane->eForce[wing][section]);
				AddVec (Moment, Moment, pMainPlane->eMoment[wing][section]);
		
				CPrd (dmoment, pMainPlane->eForce[wing][section], pMainPlane->Pos[wing][section]);
				AddVec (Moment, Moment, dmoment);
			}
		pMainPlane = pMainPlane->List.NextItem ();
	}

	// Surfaces
	PSURFACE pSurface = SurfaceList;
	while (pSurface != NULL)
	{
		AddVec (Force, Force, pSurface->Force);
//DeadCode CSB 25/02/99			AddVec (Moment, Moment, pSurface->Moment);

		CPrd (dmoment, pSurface->Force, pSurface->Pos);
		AddVec (Moment, Moment, dmoment);

		pSurface = pSurface->List.NextItem ();
	}

// Cylinders	//CSB 05/11/98
	PCYLINDER pCylinder = CylinderList;
	while (pCylinder != NULL)
	{
		AddVec (Force, Force, pCylinder->Force);

		CPrd (dmoment, pCylinder->Force, pCylinder->Pos);
		AddVec (Moment, Moment, dmoment);

		pCylinder = pCylinder->List.NextItem ();
	}

	// StoresDrag	//CSB	03 Sep 98
	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
	{
		AddVec (Force, Force, StoresForce);
		AddVec (Moment, Moment, StoresMoment);
	}


	// Moment due to complex rotation
	AddVec (Moment, Moment, InertiaMoment);


//DeadCode CSB 04/06/99		// ThrustPoints
//DeadCode CSB 04/06/99		PTHRUSTPOINT pThrust = ThrustList;
//DeadCode CSB 04/06/99		while (pThrust != NULL)
//DeadCode CSB 04/06/99		{
//DeadCode CSB 04/06/99			AddVec (Force, Force, pThrust->Force);
//DeadCode CSB 04/06/99			AddVec (Moment, Moment, pThrust->Moment);
//DeadCode CSB 04/06/99			CPrd (dmoment, pThrust->Force, pThrust->Pos);
//DeadCode CSB 04/06/99			AddVec (Moment, Moment, dmoment);
//DeadCode CSB 04/06/99			pThrust = pThrust->List.NextItem ();
//DeadCode CSB 04/06/99		}


	// Spin recovery
	// if (Spin Recovery Key pressed) Moment.y += RotVel.y * factor; // factor is + or -

	// Limit forces and moments to sensible limits

#ifdef CALC_FORCE_MOMENT_LIMITS

	static FCRD MaxForce = {0,0,0};
	static FCRD MinForce = {0,0,0};

	static FCRD MaxMoment = {0,0,0};
	static FCRD MinMoment = {0,0,0};

	if (Force.x > MaxForce.x) MaxForce.x = Force.x;
	if (Force.y > MaxForce.y) MaxForce.y = Force.y;
	if (Force.z > MaxForce.z) MaxForce.z = Force.z;

	if (Force.x < MinForce.x) MinForce.x = Force.x;
	if (Force.y < MinForce.y) MinForce.y = Force.y;
	if (Force.z < MinForce.z) MinForce.z = Force.z;

	if (Moment.x > MaxMoment.x) MaxMoment.x = Moment.x;
	if (Moment.y > MaxMoment.y) MaxMoment.y = Moment.y;
	if (Moment.z > MaxMoment.z) MaxMoment.z = Moment.z;

	if (Moment.x < MinMoment.x) MinMoment.x = Moment.x;
	if (Moment.y < MinMoment.y) MinMoment.y = Moment.y;
	if (Moment.z < MinMoment.z) MinMoment.z = Moment.z;

	#define XFORCELIMIT 600000
	#define YFORCELIMIT 2500000
	#define ZFORCELIMIT 600000

	#define XMOMENTLIMIT 250000000
	#define YMOMENTLIMIT 250000000
	#define ZMOMENTLIMIT 250000000

	UWord bits = 0;

	if (Force.x > XFORCELIMIT)
	{
		Force.x = XFORCELIMIT;
		bits |= 0x4000;
	}
	if (Force.x < -XFORCELIMIT)
	{
		Force.x = -XFORCELIMIT;
		bits |= 0x400;
	}
	if (Force.y > YFORCELIMIT)
	{
		Force.y = YFORCELIMIT;
		bits |= 0x2000;
	}
	if (Force.y < -YFORCELIMIT)
	{
		Force.y = -YFORCELIMIT;
		bits |= 0x200;
	}
	if (Force.z > ZFORCELIMIT)
	{
		Force.z = ZFORCELIMIT;
		bits |= 0x1000;
	}
	if (Force.z < -ZFORCELIMIT)
	{
		Force.z = -ZFORCELIMIT;
		bits |= 0x100;
	}

	if (Moment.x > XMOMENTLIMIT)
	{
		Moment.x = XMOMENTLIMIT;
		bits |= 0x40;
	}
	if (Moment.x < -XMOMENTLIMIT)
	{
		Moment.x = -XMOMENTLIMIT;
		bits |= 0x4;
	}
	if (Moment.y > YMOMENTLIMIT)
	{
		Moment.y = YMOMENTLIMIT;
		bits |= 0x20;
	}
	if (Moment.y < -YMOMENTLIMIT)
	{
		Moment.y = -YMOMENTLIMIT;
		bits |= 0x2;
	}
	if (Moment.z > ZMOMENTLIMIT)
	{
		Moment.z = ZMOMENTLIMIT;
		bits |= 0x10;
	}
	if (Moment.z < -ZMOMENTLIMIT)
	{
		Moment.z = -ZMOMENTLIMIT;
		bits |= 0x1;
	}

#endif


}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WingDamage
//Author		Craig Beeston
//Date			Fri 22 Jan 1999
//
//Description	Check to see in the aircraft is pulling V high G 
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::WingDamage (AirStrucPtr const ControlledAC, FP forcey)
{
	FP NumG = forcey / (Mass * GRAVITY);
	if( (NumG > MinG) && (NumG < MaxG) ) return;

	FP StressLevel = 0;

	if(NumG > MaxG) StressLevel = NumG / MaxG;
	if(NumG < MinG) StressLevel = NumG / MinG;

	if(StressLevel < 1.5)
		_Miles.PlayOnce(FIL_SFX_CREAK7, (int)(128.0 * (StressLevel - 0.5)));//RJS 20May99
	else
	{
		if(Math_Lib.rnd() <= 655 * Timer_Code.FRAMETIME)	// 1 second	//CSB 17/05/99	
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;
			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->LEFTWINGIN, BS_DEAD);
			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->RIGHTWINGIN, BS_DEAD);
	//DeadCode AMM 26Apr99 		_Miles.PlaySample(FIL_SFX_EXPLOSION_ENGINE, 128);	//fix this !!!!
			_Miles.PlayOnce(FIL_SFX_METAL_SNAP,ControlledAC);					//RJS 26Apr99
		}
		else
			_Miles.PlayOnce(FIL_SFX_CREAK7);					//RJS 20May99
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcAcc
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calculates acceleration on the aircraft, in local coords
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcAcc ()
{
//DeadCode CSB 10/06/99		FCRD GroundVel;
//DeadCode CSB 10/06/99		TnsAxs(Vel, GroundVel, Ori);

	Acc.x = NettForce.x / Mass - GRAVITY * Ori.x.y;// + RotVel.y * GroundVel.z - RotVel.z * GroundVel.y;
	Acc.y = NettForce.y / Mass - GRAVITY * Ori.y.y;// + RotVel.z * GroundVel.x - RotVel.x * GroundVel.z;
	Acc.z = NettForce.z / Mass - GRAVITY * Ori.z.y;// + RotVel.x * GroundVel.y - RotVel.y * GroundVel.x;

	TnsPnt(NettForce, wAcc, Ori);	//Calc acc in world coords
	
	wAcc.x /= Mass;
	wAcc.y /= Mass;
	wAcc.z /= Mass;

	wAcc.y -= GRAVITY;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcRotAcc
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	calculates rotation acceleration on ac, in local coords
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcRotAcc ()
{
	RotAcc.x = (NettMoment.x / RotInertia.x);
	RotAcc.y = (NettMoment.y / RotInertia.y);
	RotAcc.z = (NettMoment.z / RotInertia.z);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MovePilotEye
//Author		Craig Beeston
//Date			Fri 30 Oct 1998
//
//Description	Moves the eye position to model an elastic neck
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::MovePilotEye ()
{
	CockpitBuf EyePos;
	CockpitBuf* pEyePos = &EyePos;

	FCRD NumG;
	FCRD DeltaEye;
	FP OneOverMass = 1 / Mass;
	FP OneOverG	   = 1 / GRAVITY;

	CPrd(NumG, PilotEyePos, RotAcc);

	NumG.x += NettForce.x * OneOverMass;
	NumG.y += NettForce.y * OneOverMass;
	NumG.z += NettForce.z * OneOverMass;

	NumG.x *= OneOverG;
	NumG.y *= OneOverG;
	NumG.z *= OneOverG;

//DeadCode CSB 08/01/99		if((NumG.x > -0.25) && (NumG.x < 0.25)) DeltaEye.x = 100 * NumG.x;
//DeadCode CSB 08/01/99		else 
//DeadCode CSB 08/01/99			if(NumG.x > 0)	DeltaEye.x =  9.375 + 2.5 * NumG.x;
//DeadCode CSB 08/01/99			else			DeltaEye.x = -9.375 + 2.5 * NumG.x;
//DeadCode CSB 08/01/99	
//DeadCode CSB 08/01/99		if((NumG.y > -0.25) && (NumG.y < 0.25)) DeltaEye.y = 100 * NumG.y;
//DeadCode CSB 08/01/99		else 
//DeadCode CSB 08/01/99			if(NumG.y > 0)	DeltaEye.y =  4.375 + 2.5 * NumG.y;
//DeadCode CSB 08/01/99			else			DeltaEye.y = -4.375 + 2.5 * NumG.y;
//DeadCode CSB 08/01/99	
//DeadCode CSB 08/01/99		if((NumG.z > -0.25) && (NumG.z < 0.25)) DeltaEye.z = 100 * NumG.z;
//DeadCode CSB 08/01/99		else 
//DeadCode CSB 08/01/99			if(NumG.z > 0)	DeltaEye.z =  9.375 + 2.5 * NumG.z;
//DeadCode CSB 08/01/99			else			DeltaEye.z = -9.375 + 2.5 * NumG.z;
//DeadCode CSB 08/01/99	
//DeadCode CSB 08/01/99	
//DeadCode CSB 08/01/99		EyePos.delta.X = DeltaEye.x;
//DeadCode CSB 08/01/99		EyePos.delta.Y = DeltaEye.y - (50 * 0.25 + 2.5 * 0.75);
//DeadCode CSB 08/01/99		EyePos.delta.Z = DeltaEye.z;

	
	FP Scale = 100;

	DeltaEye.x = NumG.x * 20;	
	DeltaEye.y = (NumG.y - 1) * 2;	
	DeltaEye.z = NumG.z * 20;	
	
	EyePos.delta.X = (int)DeltaEye.x;
	EyePos.delta.Y = (int)DeltaEye.y;
	EyePos.delta.Z = (int)DeltaEye.z;
	

	EyePos.hdg   = 0;
	EyePos.pitch = 0;
	EyePos.roll  = 0;

	if( (TotalBuffet) && (!GearTouched) )
	{	
//DeadCode CSB 09/02/99			if(FrameCount & 0x0004)
//DeadCode CSB 09/02/99				EyePos.pitch += TotalBuffet * 5;
//DeadCode CSB 09/02/99			else
//DeadCode CSB 09/02/99				EyePos.pitch += 65536 - TotalBuffet * 5;
//DeadCode CSB 09/02/99	
//DeadCode CSB 09/02/99			if(FrameCount & 0x0002)
//DeadCode CSB 09/02/99				EyePos.roll += TotalBuffet * 5;
//DeadCode CSB 09/02/99			else
//DeadCode CSB 09/02/99				EyePos.roll += 65536 - TotalBuffet * 5;

		if(FrameCount & 0x0004)
			EyePos.delta.Y += TotalBuffet;// * TotalBuffet * 5;
		else
			EyePos.delta.Y -= TotalBuffet;// * TotalBuffet * 5;

		if(FrameCount & 0x0002)
			EyePos.delta.X += TotalBuffet;// * TotalBuffet * 2;
		else
			EyePos.delta.X -= TotalBuffet;// * TotalBuffet * 2;

		_Miles.PlayBuffet(SLong(64.0 * TotalBuffet));//RJS 29Jan99
	}

//DeadCode CSB 24/03/99		EyePos.delta.X = 0;
//DeadCode CSB 24/03/99		EyePos.delta.Y = 0;
//DeadCode CSB 24/03/99		EyePos.delta.Z = 0;
//DeadCode CSB 24/03/99	
//DeadCode CSB 24/03/99		EyePos.hdg   = 0;
//DeadCode CSB 24/03/99		EyePos.pitch = 0;
//DeadCode CSB 24/03/99		EyePos.roll  = 0;
					
	SetBuffetData(pEyePos);

	if(Save_Data.gamedifficulty[GD_GEFFECTS])
	{
		FP gBlack = 7;	//	5.5;									  //RDH 15/06/99
		FP gRed   = -2;		//-1.5;									  //RDH 15/06/99
		if (Save_Data.flightdifficulty[FD_POWERBOOST])
		{  gBlack *= 1.25;	gRed   *= 1.25;	}

		if(FirstCycle) Blood = 1;
		FP G = Inst.NormalAcc;
		if(Blood <= 1)
		{
			FP OldBlood = Blood;	
			FP BloodFlow = (gBlack - G) * 0.00025;
			if(	   ((BloodFlow > 0) && (Blood < 1))
				|| ((BloodFlow < 0) && (Blood > 0)) )
				Blood += BloodFlow * MODEL_DT;
			if(    ((OldBlood > 0.6667) && (Blood < 0.6667))
				|| ((OldBlood > 0.5)    && (Blood < 0.5)) )
				_Miles.PlayOnce(FIL_SFX_OUT_OF_BREATH2,128);		//RJS 21May99	//CSB 09/06/99	

		}
		else
		{
			FP BloodFlow = (gRed - G) * 0.00025;
			if(	   ((BloodFlow > 0) && (Blood < 1.5))
				|| ((BloodFlow < 0) && (Blood > 1)) )
				Blood += BloodFlow * MODEL_DT;
		}
	}
	else
		Blood = 1;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSpeed
//Author		Craig Beeston
//Date			Wed 12 Dec 1998
//
//Description	Overwrites the acceleration in the z direction in order to keep the target aircraft the 
//				correct distance in front of the player
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetSpeed(AirStrucPtr const ControlledAC, SWord desiredspeed)
{
	FP DesiredSpeed = (FP)(0.1 * desiredspeed);
	PENGINE pEngine = EngineList;
	FP TotalThrust = 0;

	while (pEngine != NULL)
	{
		if(pEngine->Type == ET_JET) TotalThrust += pEngine->MaxThrust;
		pEngine = pEngine->List.NextItem ();
	}
	
	FP MaxAccel = 0;
	if(TotalThrust > 0) MaxAccel = TotalThrust / Mass;
	else MaxAccel = 0.1;	//Quite generous

	MaxAccel *= 4.0;
	if(Save_Data.flightdifficulty [FD_POWERBOOST])
		MaxAccel *= 1.5;
	
	FCRD GroundVel;
	TnsAxs(Vel, GroundVel, Ori);

	FP RequiredAcc = (DesiredSpeed - GroundVel.z) / MODEL_DT;

	FP AbsReqAcc = RequiredAcc;
	if(AbsReqAcc < 0) AbsReqAcc *= -1;
	if(AbsReqAcc > MaxAccel) CheatAcc.z = MaxAccel;
	else
		CheatAcc.z = AbsReqAcc;

	if(RequiredAcc < 0) CheatAcc.z *= -1;


	CheatAcc.z = CheatAcc.z - RotVel.x * GroundVel.y + RotVel.y * GroundVel.x;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSpeed
//Author		Craig Beeston
//Date			Mon 1 Mar 1999
//
//Description	Replaces the existing acceleration (Global) with the given acc (Local) in any of the three axes
//
//Inputs		Old and Desired acceleration in ac local axes
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ModifyAcc(FCRD OldAcc, FCRD NewAcc)
{
	FCRD DeltaAcc;
	NullVec(DeltaAcc);
	if(NewAcc.x != 32767)	DeltaAcc.x = NewAcc.x - OldAcc.x;
	if(NewAcc.y != 32767)	DeltaAcc.y = NewAcc.y - OldAcc.y;
	if(NewAcc.z != 32767)	DeltaAcc.z = NewAcc.z - OldAcc.z;

	TnsPnt(DeltaAcc, DeltaAcc, Ori);
	AddVec(wAcc, wAcc, DeltaAcc);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChangeDirection
//Author		Craig Beeston
//Date			Mon 14 Dec 1998
//
//Description	Overwrites the rotational acceleration of the aircraft so that 
//				in one model loop the directions will change by the specified amounts
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ChangeDirection(AirStrucPtr const ControlledAC, FP DeltaPitch, FP DeltaYaw, FP DeltaRoll)
{
	FCRD GroundVel;	//Aircraft ground velocity in aircraft coordinates
	TnsAxs(Vel, GroundVel, Ori);

	MODMAXMIN(DeltaPitch, -0.00250 * MODEL_DT, 0.00500 * MODEL_DT);
	MODMAXMIN(DeltaYaw  , -0.00125 * MODEL_DT, 0.00125 * MODEL_DT);
	MODMAXMIN(DeltaRoll , -0.02500 * MODEL_DT, 0.02500 * MODEL_DT);

	RotOriXVec(Ori, DeltaPitch);	
	RotOriYVec(Ori, DeltaYaw);	
	RotOriZVec(Ori, DeltaRoll);	

	NrmVec(Ori.y, Ori.y);
	NrmVec(Ori.z, Ori.z);

	CPrdX(Ori);
	NrmVec(Ori.x, Ori.x);
	TnsPnt(GroundVel, Vel, Ori);

	NullVec(RotVel);

	UpdateAirStruc (ControlledAC);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TransInt
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Integrates in translation to get new velocity and position
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::TransInt (ITERATION_MASK mask, FP TimeFactor)
{
	FP dT = MODEL_DT * TimeFactor;

//DeadCode CSB 25/02/99		MODLIMIT(Acc.x, 10 * GRAVITY);
//DeadCode CSB 25/02/99		MODLIMIT(Acc.y, 10 * GRAVITY);
//DeadCode CSB 25/02/99		MODLIMIT(Acc.z, 10 * GRAVITY);
//DeadCode CSB 25/02/99	
//DeadCode CSB 25/02/99		FCRD acc;
//DeadCode CSB 25/02/99	
//DeadCode CSB 25/02/99		TnsPnt (Acc, acc, Ori);
//DeadCode CSB 25/02/99	
//DeadCode CSB 25/02/99		wAcc.x = acc.x;	//fix this !!!!
//DeadCode CSB 25/02/99		wAcc.y = acc.y;
//DeadCode CSB 25/02/99		wAcc.z = acc.z;


	switch (mask)
	{
		case ALL:

//DeadCode CSB 04/03/99				FCRD Vel0;
//DeadCode CSB 04/03/99				TnsAxs(Vel, Vel0, Ori);

			Vel.x += wAcc.x * dT;
			Vel.y += wAcc.y * dT;
			Vel.z += wAcc.z * dT;

			MODLIMIT(Vel.x, 500);	//Mach 1.5
			MODLIMIT(Vel.y, 500);
			MODLIMIT(Vel.z, 500);

//DeadCode CSB 04/03/99				FCRD Vel1;
//DeadCode CSB 04/03/99				TnsAxs(Vel, Vel1, Ori);

/* TEST CODE CSB 18/06/99 */			FCRDlong OldPos = Pos;
			
			Pos.x += Vel.x * dT;
			Pos.y += Vel.y * dT;
			Pos.z += Vel.z * dT;

//DeadCode CSB 13/07/99	/* TEST CODE CSB 18/06/99 */			if(		(OldPos.x - Pos.x > 1000) || (Pos.x - OldPos.x > 1000) 
//DeadCode CSB 13/07/99	/* TEST CODE CSB 18/06/99 */				||	(OldPos.y - Pos.y > 1000) || (Pos.y - OldPos.y > 1000) 
//DeadCode CSB 13/07/99	/* TEST CODE CSB 18/06/99 */				||	(OldPos.z - Pos.z > 1000) || (Pos.z - OldPos.z > 1000) )
//DeadCode CSB 13/07/99	/* TEST CODE CSB 18/06/99 */				int BreakPoint = 0;

			break;

		case YZ_ONLY:

			Vel.y += wAcc.y * dT;
			Vel.z += wAcc.z * dT;

			Pos.y += Vel.y * dT;
			Pos.z += Vel.z * dT;

			break;

		case Y_ONLY:

			Vel.y += wAcc.y * dT;

			Pos.y += Vel.y * dT;

			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotInt
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Integrates in rotation to get new rot velocity and orientation
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RotInt (ITERATION_MASK mask)
{
	if (mask == XZ_ONLY)
	{
		RotVel.x += RotAcc.x * MODEL_DT;
		RotVel.z += RotAcc.z * MODEL_DT;

		RotOriXVec (Ori, RotVel.x * MODEL_DT);
		RotOriZVec (Ori, RotVel.z * MODEL_DT);
	}

	if (mask == ALL)
	{
		RotVel.x += RotAcc.x * MODEL_DT;
		RotVel.y += RotAcc.y * MODEL_DT;
		RotVel.z += RotAcc.z * MODEL_DT;

		MODLIMIT(RotVel.x, F2PIE * 0.01);	//360 per second
		MODLIMIT(RotVel.y, F2PIE * 0.01);
		MODLIMIT(RotVel.z, F2PIE * 0.01);

		RotVelInt ();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotVelInt
//Author		Andrew McRae
//Date			Fri 18 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RotVelInt ()
{
	RotOriZVec (Ori, RotVel.z * MODEL_DT * 0.5);
	RotOriYVec (Ori, RotVel.y * MODEL_DT * 0.5);
	RotOriXVec (Ori, RotVel.x * MODEL_DT);// * 0.5);
//DeadCode CSB 21/06/99		RotOriXVec (Ori, RotVel.x * MODEL_DT * 0.5);
	RotOriYVec (Ori, RotVel.y * MODEL_DT * 0.5);
	RotOriZVec (Ori, RotVel.z * MODEL_DT * 0.5);

	CPrdX (Ori);
	CPrdZ (Ori);

	NrmVec (Ori.x, Ori.x);
	NrmVec (Ori.y, Ori.y);
	NrmVec (Ori.z, Ori.z);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveStore
//Author		rdh
//Date			
//
//Description	
//				pos < 0   ... left store,
//				pos > 0   ... right store,
//				pos = 0   ... centre store
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RemoveStore(weap_info *weapptr,SLong pos,int mass, int drag, Bool fueltank)
{
	// Mass points stuff needs to be updated to cater for		//RJS 13May98
	// separate left and right store mass reduction....			//RJS 13May98
																//RJS 13May98
//DeadCode RDH 10Sep98 	int masspoints = 2;											//RJS 13May98
//DeadCode RDH 10Sep98 	if (pos == 0)												//RJS 13May98
//DeadCode RDH 10Sep98 		masspoints = 4;											//RJS 13May98
	if(pos > 0) pos = MainPlaneList->Pos[0][1].x;
	if(pos < 0) pos = MainPlaneList->Pos[1][1].x;
																//RJS 13May98
	if (weapptr->mass < mass)									//RJS 13May98
		mass = weapptr->mass; 									//RJS 13May98
																//RJS 13May98
	weapptr->mass -= mass;										//RJS 13May98
//DeadCode CSB 08/09/98		RemoveMass(mass,masspoints);								//RJS 13May98
//DeadCode CSB 22/06/99		if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
//DeadCode CSB 22/06/99			RemoveMass(mass * 0.001, pos, 0, 0);		//CSB						//RJS 13May98
	weapptr->drag -= drag;										//RJS 13May98
	if (weapptr->drag < 0)										//RJS 13May98
		weapptr->drag = 0;										//RJS 13May98
	if (fueltank)												//RJS 13May98
	{															//RJS 13May98
//DeadCode CSB 08/09/98			RemoveMass(weapptr->ext_fuel,masspoints);				//RJS 13May98
//DeadCode CSB 22/06/99			if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
//DeadCode CSB 22/06/99				RemoveMass(weapptr->ext_fuel * 0.001, pos, 0, 0);	//CSB			//RJS 13May98
		weapptr->ext_fuel = 0;									//RJS 13May98
	}
//DeadCode CSB 08/09/98		Mass = FindMass()/1000;

}

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//Procedure		RemoveMass
//Author		Craig Beeston
//Date			Tue 08 Sep 1998
//
//Description	Given a mass and its location, this is removed from the total aircraft mass
//				and the contribution to the 3 rotational inertias are removed.
//
//Inputs		Mass (0.01 ), X,Y,Z (cm)
//
//Returns		-
//--------------------------------------------------------------------------------------------

void Model::RemoveMass(FP amount,FP massX, FP massY, FP massZ)
{
	Mass -= amount;

	FP distance;
	distance     =  VecLen2D (massY, massZ);
	RotInertia.x -= amount * distance * distance;	
	
	distance     =  VecLen2D (massX, massZ);
	RotInertia.y -= amount* distance * distance;	
	
	distance     =  VecLen2D (massX, massY);
	RotInertia.z -= amount * distance * distance;

	if(Mass < 1) Mass = 1;								//fix this to empty mass
	if(RotInertia.x < InertiaEmpty.x) RotInertia.x = InertiaEmpty.x;
	if(RotInertia.y < InertiaEmpty.y) RotInertia.y = InertiaEmpty.y;
	if(RotInertia.z < InertiaEmpty.z) RotInertia.z = InertiaEmpty.z;
}



//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//Procedure		AddMass
//Author		Craig Beeston
//Date			Tue 08 Sep 1998
//
//Description	Given a mass and its location, this is added onto the total aircraft mass
//				and the contribution to the 3 rotational inertias are added.
//
//Inputs		Mass (cg), X,Y,Z (cm)
//
//Returns		-
//--------------------------------------------------------------------------------------------

void Model::AddMass(FP amount,FP massX, FP massY, FP massZ)
{
	Mass += amount;
	
	FP distance;
	distance     =  VecLen2D (massY, massZ);
	RotInertia.x += amount * distance * distance;	
	
	distance     =  VecLen2D (massX, massZ);
	RotInertia.y += amount * distance * distance;	
	
	distance     =  VecLen2D (massX, massY);
	RotInertia.z += amount * distance * distance;	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupMassInertias
//Author		Craig Beeston
//Date			Tue 08 Sep 1998
//
//Description	Sets up the inertia of the aircraft empty, and adds the 
//				mass of fuel and mass and inertia of stores.
//
//Inputs		Aircraft mass, 3 inertias
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetMassInertias (AirStrucPtr const ControlledAC, FP EmptyIxx, FP EmptyIyy, FP EmptyIzz)
{
//for scramble factor is 2 for normal missions factor is 1
	int	fuelfactor = 1;
	
	Mass     = ControlledAC->classtype->weightempty;
	int fuel = ControlledAC->classtype->maxintfuel/fuelfactor;	// 0.01 kg
	Mass += fuel;												// 0.01 kg
	ControlledAC->weap.centre.int_fuel = 500 * fuel;			// 0.01 g	Robs Stuff//RJS 25Mar99
	ControlledAC->weap.left.int_fuel = 250 * fuel;			// 0.01 g	Robs Stuff//RJS 25Mar99
	ControlledAC->weap.right.int_fuel = 250 * fuel;			// 0.01 g	Robs Stuff//RJS 25Mar99
	
	InertiaEmpty.x = EmptyIxx * 1355827;		//slug ft2 -> 0.01 kg cm2
	InertiaEmpty.y = EmptyIyy * 1355827;
	InertiaEmpty.z = EmptyIzz * 1355827;

	RotInertia = InertiaEmpty;

	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])		//CSB	//03 Sep 98
	{	
		AddMass(ControlledAC->weap.right.mass * 0.001,      MainPlaneList->Pos[0][0].x, 0, 0);			//0.01 kg, cm
		AddMass(ControlledAC->weap.right.ext_fuel * 0.001,  MainPlaneList->Pos[0][0].x, 0, 0);
		AddMass(ControlledAC->weap.centre.mass * 0.001,		0,		  0, 0);
		AddMass(ControlledAC->weap.centre.ext_fuel * 0.001, 0,        0, 0);
		AddMass(ControlledAC->weap.left.mass * 0.001,	    MainPlaneList->Pos[1][0].x, 0, 0);	
		AddMass(ControlledAC->weap.left.ext_fuel * 0.001,   MainPlaneList->Pos[1][0].x, 0, 0);
	}

	if(	   (ControlledAC->weap.right.ext_fuel != 0)
		|| (ControlledAC->weap.centre.ext_fuel != 0)
		|| (ControlledAC->weap.left.ext_fuel != 0)
	   )
			ControlledAC->weap.UseIntFuel = FALSE;
}
	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateMassInertias
//Author		Craig Beeston
//Date			Fri 18 Jun 1999
//
//Description	calculates the total mass and iniertias of an aircraft
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::UpdateMassInertias (AirStrucPtr const ControlledAC)
{
	Mass	   = ControlledAC->classtype->weightempty;
	RotInertia = InertiaEmpty;
//DeadCode CSB 24/06/99		FP DistX   = (MainPlaneList->Pos[0][1].x + MainPlaneList->Pos[0][0].x) * 0.5;
//DeadCode AMM 29Jun99 	FP DistX   = MainPlaneList->Pos[0][0].x;
	FP DistX;													//AMM 29Jun99
	if(ControlledAC->classtype->aerobaticfactor != AEROBATIC_LOW)//AMM 29Jun99
		DistX = MainPlaneList->Pos[0][0].x;						//AMM 29Jun99
	else														//AMM 29Jun99
		DistX = 0;												//AMM 29Jun99

	FP FuseMass = ControlledAC->weap.centre.int_fuel;
	FP WingMass = ControlledAC->weap.left.int_fuel + ControlledAC->weap.right.int_fuel;
	Mass += (FuseMass + WingMass) * 0.001;
	
	RotInertia.z += DistX * DistX * WingMass * 0.001;

	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])		//CSB	//03 Sep 98
	{	
		FuseMass = ControlledAC->weap.centre.mass + ControlledAC->weap.centre.ext_fuel;
		WingMass = ControlledAC->weap.left.mass + ControlledAC->weap.left.ext_fuel +
				   ControlledAC->weap.right.mass + ControlledAC->weap.right.ext_fuel;
	
		Mass		 += (FuseMass + WingMass) * 0.001;
		RotInertia.z += DistX * DistX * WingMass * 0.001;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Instruments
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calcs instrument settings
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::Instruments (AirStrucPtr const ControlledAC)
{
	Inst.SetInstruments (ControlledAC,this);
	{
//DeadCode RJS 03Feb98 		if (EngineList->Type == ET_JET)								//RJS 03Feb98
//DeadCode RJS 03Feb98 			Inst.Rpm1 = EngineList->SpeedRpm;						//RJS 03Feb98
//DeadCode RJS 03Feb98 		else														//RJS 03Feb98
//DeadCode RJS 03Feb98 			Inst.Rpm1 = EngineList->Speed * 954.30;					//RJS 03Feb98

	}
//rdh 30nov98
	if (Controlled)
	{
//DEADCODE rdh 13/04/99 		if (ControlledAC->ai.unfriendly)
//DEADCODE rdh 13/04/99 			OverLay.SetInfoLineVals(Inst.ActualSpeed, Inst.MachNo, Inst.Altitude, Inst.HdgAngle, (SWord)((AirStruc*)ControlledAC->ai.unfriendly)->ai.manoeuvre); 
//DEADCODE rdh 13/04/99 		else
 		OverLay.SetInfoLineVals(10 * Inst.ActualSpeed, Inst.MachNo, Inst.Altitude, Inst.HdgAngle, ControlledAC->fly.thrustpercent); 
		if (ControlledAC->ai.unfriendly)
		{
			ControlledAC->InterceptandRange (&ControlledAC->ai.unfriendly->World);
	 		SWord HI = (SWord) (ControlledAC->HdgIntercept - ControlledAC->hdg);
			HI = Rowan2Degs(HI);
//PD 27/04/99 - view code does this!
//DEADCODE PD 27/04/99			SLong dalt = (ControlledAC->ai.unfriendly->World.Y - ControlledAC->World.Y) * 0.03281;
//DEADCODE PD 27/04/99//for miles			OverLay.SetViewVals(ControlledAC->Range*0.000005396,HI,dalt); 
//DEADCODE PD 27/04/99			OverLay.SetViewVals(ControlledAC->Range*0.01,HI,dalt); 
		}
//DEADCODE PD 27/04/99		else
//DEADCODE PD 27/04/99		{
//DEADCODE PD 27/04/99			OverLay.SetViewVals(0,0,0); 
//DEADCODE PD 27/04/99		}
	}


#ifdef PRINTINSTRUMENTS
	PrintInstruments (this);

	PrintVar (0,9,"thrust lbf %.0f  ", EngineList->Thrust * 0.224769611);

#endif
//	Inst.SetInstruments (this);			... already done above RJS 10Feb98

//	if (!bACM)
//		if (MainPlaneList != NULL)
//			ControlledAC->fly.aoa = (Angles)Rads2Rowan ((MainPlaneList->aoa[0] + MainPlaneList->aoa[1]) * 0.5);
//DeadCode ARM 31Oct97 		ControlledAC->fly.aoa = (ANGLES)Rads2Rowan ((SurfaceList->aoa + SurfaceList->List.NextItem()->aoa) * 0.5);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Ground_Collide_Sounds
//Author		Andrew McRae				CSB
//Date			Mon 27 Jan 1997				14/1/99
//
//Description	Ground Collision Interaction		//Checks for parts of aircraft touching ground and plays sounds
//				Not Undercarriage Suspension or Brakes
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::Ground (AirStrucPtr const ControlledAC)
{
	Collide::Pos landed = _Collide.LANDED_OK;					//AMM 29Jun99
	//Tidied by Rob												//RJS 07May99
//DeadCode AMM 29Jun99 	landed = _Collide.HaveWeLanded (ControlledAC,grndpitch,grndroll);
	ANGLES Temp1, Temp2;										//AMM 29Jun99
	landed = _Collide.HaveWeLanded (ControlledAC, Temp1, Temp2);//AMM 29Jun99
	if (landed == _Collide.NOTTOUCHED)
	{
		AircraftAnimData	*adptr = (AircraftAnimData*) ControlledAC->Anim;
		adptr->hasdust = FALSE;					
		adptr->justlanded = FALSE;
	}
	else
	{
		if ((Manual_Pilot.ControlledAC2 == ControlledAC) && GearTouched)		//RJS 20May99
			_Miles.PlayLanded(ControlledAC, (int)(Speed * 100), GearSkid);		//fix this !!!!

		if (landed != _Collide.LANDED_OK)										//RJS 20May99
			Trans_Obj.LandedEffect(ControlledAC,landed);						//RJS 20May99
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeathSequenceOverride
//Author		Robert Slater
//Date			Tue 10 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::DeathSequenceOverride(int	newmovecode)
{
//DeadCode RJS 14Apr98 	Controlled = FALSE;
//
//	IsDead = TRUE;
//	ControlledAC->movecode = (AutoMoveCodeTypeSelect) newmovecode;
//	Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;
}

void	Model::ProcessAeroPacket(AirStrucPtr const ControlledAC, UByte DeviceID, UByte NewFlaps, UByte position)
{
	UByte		devcnt = 0;
	PAERODEVICE pAeroDevice = DeviceList;
	while (pAeroDevice != NULL)
	{
		if (devcnt == DeviceID)
		{
			if (!NewFlaps)
			{
				if (pAeroDevice->OldAttractor)
					pAeroDevice->Attractor = 0x0000;
				else
					pAeroDevice->Attractor = 0x4000;
			}
			else
			{
				switch (position)
				{
				case 0:
					pAeroDevice->Attractor=0x0000;
					break;
				case 1:
					pAeroDevice->Attractor=0x1555;
					break;
				case 2:
					pAeroDevice->Attractor=0x4000;
					break;
				default:
					pAeroDevice->Attractor=0x0000;
				}
			}

			pAeroDevice->Action (ControlledAC, AeroDevice::CT_AUTO,FALSE);
			break;
		}
		else
		{
			pAeroDevice = pAeroDevice->List.NextItem ();
			devcnt++;
		}
	}
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcStickForceFeedback
//Author		Craig Beeston
//Date			Thu 20 Aug 98
//
//Description	Calculates the Stiffness's, Forces and Sine Waves to be sent 
//				to Force Feedbank JoyStick Forces
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcStickForceFeedback()
{
//DEADCODE RDH 23/05/99 	PrintVar(40, 5, "Buffet %.2f ", TotalBuffet);	//CSB
	
//DeadCode CSB 19/05/99		const int _Nothing	= 0;
//DeadCode CSB 19/05/99		const int _ForceX	= 1;
//DeadCode CSB 19/05/99		const int _ForceY	= 2;
//DeadCode CSB 19/05/99		const int _ForceZ	= 3;
//DeadCode CSB 19/05/99		const int _StiffX	= 4;
//DeadCode CSB 19/05/99		const int _StiffY	= 5;
//DeadCode CSB 19/05/99		const int _StiffZ	= 6;
//DeadCode CSB 19/05/99		const int _WaveX	= 7;
//DeadCode CSB 19/05/99		const int _WaveY	= 8;
//DeadCode CSB 19/05/99		const int _WaveZ	= 9;

//DEADCODE CSB 23/05/99 	const int _Nothing	= 0;
	const int _Damping	= 0;
	const int _StiffX	= 1;
	const int _StiffZ	= 2;
	const int _WaveX	= 3;

	SWord WhatThisFrame = _Damping;
	WhatThisFrame = FrameCount & 0x03;
	
	switch(WhatThisFrame)
	{
//DeadCode CSB 19/05/99			case _ForceX:
//DeadCode CSB 19/05/99			{
//DeadCode CSB 19/05/99				_Analogue.FFpush.SetX(0, 100);
//DeadCode CSB 19/05/99				break;
//DeadCode CSB 19/05/99			}
//DeadCode CSB 19/05/99	
//DeadCode CSB 19/05/99			case _ForceZ:
//DeadCode CSB 19/05/99			{
//DeadCode CSB 19/05/99				if(!Save_Data.flightdifficulty[FD_FF_AERODYNAMIC])
//DeadCode CSB 19/05/99					break;
//DeadCode CSB 19/05/99	
//DeadCode CSB 19/05/99				FP ForceZ = 0;
//DeadCode CSB 19/05/99				FP DynPress = DynamicPressure / AirSpeed;
//DeadCode CSB 19/05/99				PENGINE pEngine = EngineList;
//DeadCode CSB 19/05/99				if(pEngine->Type == ET_PISTON)			//Prop Aircraft
//DeadCode CSB 19/05/99					DynPress = 0.5 * AmbDensity * pEngine->SlipVel;// * pEngine->SlipVel;
//DeadCode CSB 19/05/99			
//DeadCode CSB 19/05/99				ForceZ =  AngleSign(CalcAngle(-AirVel.z, AirVel.y) );
//DeadCode CSB 19/05/99				ForceZ *= DynPress * (5000000.0/*2048*/ * 0.01) * (FP)ControlForce;		//TailPlane Incidence
//DeadCode CSB 19/05/99				MODLIMIT(ForceZ, 30000);
//DeadCode CSB 19/05/99		
//DeadCode CSB 19/05/99				_Analogue.FFpush.SetZ(ForceZ, 100);
//DeadCode CSB 19/05/99				break;
//DeadCode CSB 19/05/99			}

		case _Damping:
		{
			FP damp = 1000;
			if(Save_Data.flightdifficulty[FD_FF_AERODYNAMIC])
			{
				damp = DynamicPressure / AirSpeed * (FP)ControlForce * (400000.0 * 0.01);
				MODLIMIT(damp, 30000);
//DEADCODE RDH 23/05/99 				PrintVar(40, 11, "Damping %.0f ", damp);
			}
			_Analogue.FFdamp.Set(damp, damp);
			break;
		}

		case _StiffX:
		{
			FP Stiffx = 20000;
			if(Save_Data.flightdifficulty[FD_FF_AERODYNAMIC])
			{
				Stiffx = DynamicPressure / AirSpeed * (FP)ControlForce * (1500000.0 * 0.01);	//Aileron
				MODLIMIT(Stiffx, 30000);
			}
			_Analogue.FFstiff.SetX(0, Stiffx);
//DeadCode CSB 25/05/99				PrintVar(0, 5, "Stiff X  %.0f ", Stiffx);
			break;
		}

		case _StiffZ:
		{
			FP Stiffz = 20000;
			if(Save_Data.flightdifficulty[FD_FF_AERODYNAMIC])
			{
				FP DynPress = DynamicPressure / AirSpeed;
				PENGINE pEngine = EngineList;
				if(pEngine->Type == ET_PISTON)			//Prop Aircraft
					DynPress = 0.5 * AmbDensity * pEngine->SlipVel;// * pEngine->SlipVel;

				Stiffz = DynPress * (FP)ControlForce * (1500000.0 * 0.01);	//Elevator
				MODLIMIT(Stiffz, 30000);
			}
			_Analogue.FFstiff.SetZ(0, Stiffz);
//DeadCode CSB 25/05/99				PrintVar(0, 6, "Stiff Z  %.0f ", Stiffz);
			break;
		}

		case _WaveX:
		{
			FP FwaveX = 0, MwaveX = 0; 
			Bool SetForce = FALSE;
			if(Save_Data.flightdifficulty[FD_FF_AIRFRAME])
			{
				if(GearTouched)
				{
					FwaveX = Speed;
					MwaveX = Speed * 200.0;
					MODMAXMIN(MwaveX, 0, 20000);
				}
				SetForce = TRUE;
			}
			if((Save_Data.flightdifficulty[FD_FF_BUFFET]) && (!GearTouched))
			{
				if(TotalBuffet > 0)
				{
					FwaveX = 10;
					MwaveX = 4096.0 * TotalBuffet * 0.01 * (FP)BuffetForce;
				}
				SetForce = TRUE;
			}
			if(SetForce)
			{
				MODLIMIT(MwaveX, 30000);
				_Analogue.FFshake.SetX(MwaveX, FwaveX, FALSE);
//DeadCode CSB 25/05/99					PrintVar(0, 7, "WaveF X  %.0f ", FwaveX);
//DeadCode CSB 25/05/99					PrintVar(0, 8, "WaveM X  %.0f ", MwaveX);
			}
			break;
		}

/*		case _WaveZ:
		{
			if(!Save_Data.flightdifficulty[FD_FF_AIRFRAME])
				break;
			
			PENGINE pEngine = EngineList;
			if(pEngine->Type != ET_PISTON)			//Prop Aircraft
				break;

			FP FwaveZ = 0, MwaveZ = 0; 
			FwaveZ = pEngine->Speed * 16;								//Engine Frequency
			MwaveZ = (pEngine->Power + 4000) * 1 * 0.01 * BuffetForce;

			MODLIMIT(MwaveZ, 32767);
			_Analogue.FFshake.SetZ(MwaveZ, FwaveZ, FALSE);
			break;
		}

		case _ForceY:
		case _StiffY:
		case _WaveY:
			break;
*/
		break;
	}
}

/*	PMAINPLANE pMainPlane = MainPlaneList;
	PENGINE	   pEngine    = EngineList;

	FP Stiffx, Stiffy, Stiffz;
	FP Forcex, Forcey, Forcez;
	FP SineMx, SineFx;							//Vibration X Magnitude and Frequency
	FP SineMy, SineFy;							//Vibration Y Magnitude and Frequency

	Forcex = Forcey = Forcez = 0;
	Stiffx = Stiffy = Stiffz = 0;
	SineMx = SineMy = 0;


	Bool Prop = FALSE;
	FP SSDynamicPressure = DynamicPressure;

	if(pEngine->Type == ET_PISTON)			//Prop Aircraft
	{
		Prop = TRUE;	
		int NumOfEngines   = 0;
		FP  AverageSlipVel = 0.0;
		{
			PENGINE pEngine = EngineList;
			while (pEngine != NULL)
			{
				NumOfEngines++;
				AverageSlipVel += pEngine->SlipVel;
			
				pEngine = pEngine->List.NextItem ();
			}
			if(NumOfEngines > 0)
				AverageSlipVel /= NumOfEngines;
		}
		SSDynamicPressure = 0.5 * AmbDensity * AverageSlipVel * AverageSlipVel;
	}

	if(Prop)
	{
		Stiffx = SSDynamicPressure * 2048 * 0.01 * ControlForce;	//Elevator
		Stiffy = SSDynamicPressure * 2048 * 0.01 * ControlForce;	//Rudder
		Stiffz =   DynamicPressure * 2048 * 0.01 * ControlForce;	//Aileron

		Forcex =  0.5 * AngleSign(CalcAngle(AirVel.y, AirVel.z) );
		Forcex *= SSDynamicPressure * 2048 * 0.01 * ControlForce;	//TailPlane Incidence

		SineFy = pEngine->Speed * 16;								//Engine Frequency
		SineMy = pEngine->Power * 16 * 0.01 * BuffetForce;
	}
	else
	{
		Stiffx = DynamicPressure * 2048 * 0.01 * ControlForce;		//Elevator
		Stiffy = DynamicPressure * 2048 * 0.01 * ControlForce;		//Rudder
		Stiffz = DynamicPressure * 2048 * 0.01 * ControlForce;		//Aileron
	
		Forcex =  AngleSign(CalcAngle(AirVel.y, AirVel.z) );
		Forcex *= DynamicPressure * 2048 * 0.01 * ControlForce;		//TailPlane Incidence
	}

	if(GearTouched)
	{
		SineFx = Speed * 10;
		SineMx = 8192;	//Tune this figure down!!
	}
	elseif(TotalBuffet > 0)
	{
		SineFx = 10;
		SineMx = 2048 * TotalBuffet * 0.01 * BuffetForce;
	}

	MODLIMIT(Stiffx,32767);
	MODLIMIT(Stiffy,32767);
	MODLIMIT(Stiffz,32767);
	
	MODLIMIT(Forcex,32767);
	MODLIMIT(Forcey,32767);
	MODLIMIT(Forcez,32767);


	MODLIMIT(SineMx,32767);
	MODLIMIT(SineMy,32767);

	_Analogue.FFstiff.Set (0,0,(SWord)Stiffx/*, (SWord)Stiffy*//*, (SWord)Stiffz);
//	_Analogue.FFstiff.Set (0,0,(SWord)0/*, (SWord)Stiffy*//*, (SWord)0);
	_Analogue.FFpush.Set  ((SWord)Forcex/*, (SWord)Forcey*//*, (SWord)Forcez,10000);
	_Analogue.FFshake.SetX ((SWord)SineMx ,(SWord)SineFx,false);
// Put back in in new version	//	_Analogue.StartYBuffet		((SWord)SineMy ,(SWord)SineFy);
}
*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcLauncherVel
//Author		R. Hyde 
//Date			Mon 30 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::CalcLauncherVel(SWord	mvel, SWord &vx, SWord &vy, SWord &vz)
{
	Float	muzvel = Float(mvel/10);
	Float	vvx; // = GunOri.z.x;								//AMM 31Mar99
	Float	vvy; // = GunOri.z.y;								//AMM 31Mar99
	Float	vvz; // = GunOri.z.z;								//AMM 31Mar99

	if (_Replay.Playback)
	{
		GunOri.x.x = 1;
		GunOri.x.y = 0;
		GunOri.x.z = 0;
		GunOri.y.x = 0;
		GunOri.y.y = 1;
		GunOri.y.z = 0;
		GunOri.z.x = 0;
		GunOri.z.y = 0;
		GunOri.z.z = 1;

		SetOri (GunOri, Rowan2Rads(replay_pitch), Rowan2Rads(replay_hdg), Rowan2Rads(replay_roll));

		GunVel.x = 0;
		GunVel.y = 0;
		GunVel.z = 0;
	}

	vvx = GunOri.z.x;
	vvy = GunOri.z.y;
	vvz = GunOri.z.z;

	vvx *= muzvel;
	vvy *= muzvel;
	vvz *= muzvel;

 	vvx += GunVel.x;
 	vvy += GunVel.y;
 	vvz += GunVel.z;

	vvx *= 10.0;
	vvy *= 10.0;
	vvz *= 10.0;

	// Velocity
	vx = SWord(vvx);
	vy = SWord(vvy);
	vz = SWord(vvz);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupForGunsight
//Author		Robert Slater
//Date			Fri 25 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::BackupForGunsight()
{
	BakRotVel = AveRotVel;
	BakOri = Ori;
}
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcGunsightPos
//Author		Craig Beeston
//Date			Thu 03 Jun 1999
//
//Description	Calculates the position of the gunsight for a GYROSCOPIC LEAD COMPUTING OPTICAL SIGHT
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::CalcGunsightPos(SLong range, SWord gunvel, SLong& dx, SLong& dy, SLong& dz)
{
//DeadCode DAW 25Jun99 	AveRotVel.x = ((fSmooth - 1) * AveRotVel.x + RotVel.x) / fSmooth;
//DeadCode DAW 25Jun99 	AveRotVel.y = ((fSmooth - 1) * AveRotVel.y + RotVel.y) / fSmooth;
//DeadCode DAW 25Jun99 	AveRotVel.z = ((fSmooth - 1) * AveRotVel.z + RotVel.z) / fSmooth;

	if(fixgunsight)
	{
		FP VerticalOffset = 0;//679;	//3 deg 53 mins
		FCRD delta;
		delta.x = 10000 * BakOri.z.x;							//AMM 25Jun99
		delta.y = 10000 * BakOri.z.y - VerticalOffset * BakOri.y.y;//AMM 25Jun99
		delta.z = 10000 * BakOri.z.z;							//AMM 25Jun99
//DeadCode DAW 25Jun99 		delta.x = 10000 * Ori.z.x;
//DeadCode DAW 25Jun99 		delta.y = 10000 * Ori.z.y - VerticalOffset * Ori.y.y;
//DeadCode DAW 25Jun99 		delta.z = 10000 * Ori.z.z;

		dx = (SLong)delta.x;
		dy = (SLong)delta.y;
		dz = (SLong)delta.z;

		return;
	}

	FP fgunvel = FP(gunvel * 0.1);
	FP frange  = FP(range * 0.01);
	FP ftime   = frange / fgunvel;
	FCRD sightoffset;

	FCRD gBulletVel;
	gBulletVel.x = fgunvel * BakOri.z.x;						//AMM 25Jun99
	gBulletVel.y = fgunvel * BakOri.z.y;						//AMM 25Jun99
	gBulletVel.z = fgunvel * BakOri.z.z;						//AMM 25Jun99
//DeadCode DAW 25Jun99 	gBulletVel.x = fgunvel * Ori.z.x;
//DeadCode DAW 25Jun99 	gBulletVel.y = fgunvel * Ori.z.y;
//DeadCode DAW 25Jun99 	gBulletVel.z = fgunvel * Ori.z.z;

	sightoffset.x = gBulletVel.x * ftime;
	sightoffset.y = gBulletVel.y * ftime;
	sightoffset.z = gBulletVel.z * ftime;

	FCRD gRotVel;
	TnsPnt(BakRotVel, gRotVel, BakOri);							//AMM 25Jun99
//DeadCode DAW 25Jun99 	TnsPnt(AveRotVel, gRotVel, Ori);
	gRotVel.x *= 100.0;
	gRotVel.y *= 100.0;
	gRotVel.z *= 100.0;

	FCRD targvel;
	CPrd(targvel, sightoffset, gRotVel);
	
	sightoffset.x -= targvel.x * ftime;
	sightoffset.y -= targvel.y * ftime;
	sightoffset.z -= targvel.z * ftime;

	sightoffset.y -= 0.5 * 9.8065 * ftime * ftime;

	sightoffset.x *= 100.0;										//DAW 28Jun99
	sightoffset.y *= 100.0;										//DAW 28Jun99
	sightoffset.z *= 100.0;										//DAW 28Jun99
																//DAW 28Jun99
	dx = SLong(sightoffset.x);									//DAW 28Jun99
	dy = SLong(sightoffset.y);									//DAW 28Jun99
	dz = SLong(sightoffset.z);									//DAW 28Jun99
}


void	Model::CalcLauncherPos(SLong&	posx, SLong& posy, SLong& posz)
{
	if (_Replay.Playback)
	{
		Ori.x.x = 1;
		Ori.x.y = 0;
		Ori.x.z = 0;
		Ori.y.x = 0;
		Ori.y.y = 1;
		Ori.y.z = 0;
		Ori.z.x = 0;
		Ori.z.y = 0;
		Ori.z.z = 1;

		SetOri (Ori, Rowan2Rads(replay_pitch), Rowan2Rads(replay_hdg), Rowan2Rads(replay_roll));
	}

	Float	posx2, posy2, posz2;
  	Float	fx, fy, fz;

	fx = Float(posx);
	fy = Float(posy);
	fz = Float(posz);

	posx2 = (Ori.x.x * fx);
	posx2 += (Ori.y.x * fy);
	posx2 += (Ori.z.x * fz);

	posy2 = (Ori.x.y * fx);
	posy2 += (Ori.y.y * fy);
	posy2 += (Ori.z.y * fz);

	posz2 = (Ori.x.z * fx);
	posz2 += (Ori.y.z * fy);
	posz2 += (Ori.z.z * fz);

	posx = SLong(posx2);
	posy = SLong(posy2);
	posz = SLong(posz2);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RememberForGunSight
//Author		R. Hyde 
//Date			Mon 30 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::RememberForGunSight(bool fixsight)
{
	GunOri = Ori;
	GunVel = Vel;

	fixgunsight = fixsight;										//CSB 09Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPlayerMoving
//Author		Craig Beeston 
//Date			Thu 11 Feb 1999
//
//Description	Checks the players speed and uses it to set flag to allow flight to take off
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::SetPlayerMoving(AirStrucPtr const ControlledAC)
{
	static Bool WindUp = FALSE;
	static Bool Wait   = FALSE;
	if(AirStruc::playermoving) return;
	
	if(ControlledAC->fly.thrustpercent > 75)
	{
		if(!WindUp)
		{
			WindUp = TRUE;
			if(ControlledAC->Follower())
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_RUNUP0, MSG_TAKEOFFRUNUP, ControlledAC, NULL, ControlledAC->Follower()));
			else
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_RUNUP0, MSG_TAKEOFFRUNUP, ControlledAC->Leader(), NULL, ControlledAC));
		}
		if( (Speed > 1) && (!LeftWheelBrake) && (!RightWheelBrake))
 		{
			if (_DPlay.Implemented || _Replay.Record)			//AMM 22Jun99
			{													//AMM 22Jun99
				_DPlay.NewPlayerMoving();					//AMM 22Jun99
			}													//AMM 22Jun99
			else												//AMM 22Jun99
				AirStruc::playermoving = true;
			if(ControlledAC->Follower())
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ROLLING, MSG_TAKEOFFROLLING, ControlledAC, NULL, ControlledAC->Follower()));
			else
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ROLLING, MSG_TAKEOFFROLLING, ControlledAC->Leader(), NULL, ControlledAC));
		}
	}
	
	if(!Wait)
		if((!LeftWheelBrake) && (!RightWheelBrake) && (ControlledAC->fly.thrustpercent < 75))
		{
			Wait = TRUE;
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WAITFOR, MSG_TAKEOFFBRAKEMSG, ControlledAC->FindBuddy(), NULL, ControlledAC));
		}

//DeadCode jim 01Jul99 	if((Speed > 10) && (!AirStruc::playermoving))
	if((ControlledAC->vel > 100) && (!AirStruc::playermoving))	//jim 01Jul99
	{
		if (_DPlay.Implemented || _Replay.Record)				//AMM 22Jun99
		{														//AMM 22Jun99
			_DPlay.NewPlayerMoving();						//AMM 22Jun99
		}														//AMM 22Jun99
		else													//AMM 22Jun99
			AirStruc::playermoving = true;
		if(ControlledAC == ControlledAC->Leader())
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ROLLING, MSG_TAKEOFFROLLING, ControlledAC, NULL, ControlledAC->Follower()));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ROLLING, MSG_TAKEOFFROLLING, ControlledAC->Leader(), NULL, ControlledAC));
	}
}

///////////////////////////////////////////////////////////////////////////////	

#ifdef DISPLAY_MONO_DATA

void PrintModelData (AirStrucPtr const ControlledAC,Model* mod, ULong x, ULong y)
{

	Bool Pos		 = FALSE;
	Bool Instruments = FALSE;//TRUE;//
	Bool Engine		 = FALSE;//TRUE;//
	Bool Controls	 = FALSE;//TRUE;//
	Bool Aoas		 = FALSE;
	Bool Atmosphere	 = FALSE;//TRUE;//
	Bool Mass		 = FALSE;//TRUE;
	Bool Anims		 = FALSE;
	Bool Gear		 = FALSE;//TRUE;//
	Bool Acm		 = FALSE;
	Bool AnglesForces= FALSE;//TRUE;//	//CSB 07/12/98
	Bool Fin		 = FALSE;//TRUE;//	//CSB 07/05/99	
	Bool Tune		 = FALSE;//TRUE;//	//CSB 13/05/99	
//	char strg [32];
	char strg [100];

	ULong n;

//DeadCode CSB 10/11/98		if (mod->Controlled)
//DeadCode CSB 10/11/98			PrintString (x, y++, "Manual");
//DeadCode CSB 10/11/98		else
//DeadCode CSB 10/11/98			PrintString (x, y++, "Auto");


	if (Pos)
	{
		y++;

		// POSITION

		PrintVar(x, y++, "X: %.0f  ", (FP)mod->Pos.x);
		PrintVar(x, y++, "Z: %.0f  ", (FP)mod->Pos.z);
	}


	if (Instruments)
	{
//		y++;

		// INSTRUMENTS

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "mph  %.0f m/s  %.0f ",mod->Inst.ActualSpeed,mod->Inst.ActualSpeed * 1600/3600);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

//DeadCode CSB 04/12/98			for (n=0; n<32; n++) strg[n] = 0;
//DeadCode CSB 04/12/98			sprintf (strg, "IAS  %.0f ",mod->Inst.IndicatedAirSpeed);
//DeadCode CSB 04/12/98			if (strg[31] == 0)
//DeadCode CSB 04/12/98				Mono_Text.PrintAt (x,y++,(UByte*)strg);

		PrintVar(x, y++, "Mach %.2f ",mod->Inst.MachNo);

		PrintVar(x, y++, "feet %ld ",mod->Inst.Altitude);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "rate %ld ",mod->Inst.RateOfClimb);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "NrmG %.2f ",mod->Inst.NormalAcc);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

//DeadCode CSB 04/12/98			FP AveAoa =  +  + 
//DeadCode CSB 04/12/98			AveAoa *= 0.25 * 180 / FPIE;

		for (n=0; n<50; n++) strg[n] = 0;									//CSB 
		sprintf (strg, "Aoa  %.1f  %.1f  %.1f  %.1f  ", mod->MainPlaneList->aoa[1][1] * 180 / FPIE,
														mod->MainPlaneList->aoa[1][0] * 180 / FPIE,
														mod->MainPlaneList->aoa[0][0] * 180 / FPIE,
														mod->MainPlaneList->aoa[0][1] * 180 / FPIE);
		if (strg[49] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;									//CSB 
		sprintf (strg, "Slip  %.2f ",180/FPIE * AngleSign(CalcAngle(-mod->AirVel.z,-mod->AirVel.x)) );
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "ptch %.2f ",mod->Inst.PitchAngle);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "bank %.2f ",mod->Inst.BankAngle);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "hdg  %.2f ",mod->Inst.HdgAngle);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		if (mod->Inst.Turn/60 < 100)
			sprintf (strg, "turn %.2f ",mod->Inst.Turn/60);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

//		for (n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "time %.2f ",mod->Inst.time);
//		if (strg[31] == 0)
//			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "turn2 %.2f ",mod->Inst.Turn2);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

	}

	if (Engine)
	{

		y++;

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "Rpm1 %.0f ",mod->Inst.Rpm1);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "Thrust (lbf) %.0f ",mod->EngineList->Thrust * 0.224769611);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		if (mod->EngineList->Type == ET_PISTON)
		{

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "bhp %.0f ",mod->EngineList->Power);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

//			for (n=0; n<32; n++) strg[n] = 0;
//			sprintf (strg, "p100 %.0f ",mod->EngineList->Power100);
//			if (strg[31] == 0)
//				Mono_Text.PrintAt (x,y++,(UByte*)strg);

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "p0 %.0f ",mod->EngineList->Power0);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "PropInc %.2f ",mod->EngineList->PropInc);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "Swirl %.2f ",mod->EngineList->SlipRot * 100);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "Slipstream %.2f ",mod->EngineList->SlipVel);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

//			for (n=0; n<32; n++) strg[n] = 0;
//			sprintf (strg, "eff %.2f ",mod->EngineList->eff);
//			if (strg[31] == 0)
//				Mono_Text.PrintAt (x,y++,(UByte*)strg);

		}

	}	


	if (Controls)
	{
//		y++;

		// CONTROLS
	
		for (n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "Aileron  %d    ",ControlledAC->fly.aileron);
		sprintf (strg, "Aileron  %d    ",mod->Aileron);
//		sprintf (strg, "Aileron  %d    ",ControlledAC->fly.pAcmModel->CtrlAileron);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "Elevator  %d    ",ControlledAC->fly.elevator);
		sprintf (strg, "Elevator  %d    ",mod->Elevator - mod->ElevatorTrim);
//		sprintf (strg, "Elevator  %d    ",ControlledAC->fly.pAcmModel->CtrlElevator);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "ElevTrim  %d    ",mod->ElevatorTrim);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "Rudder  %d    ",ControlledAC->fly.rudder);
		sprintf (strg, "Rudder  %d    ",mod->Rudder);
//		sprintf (strg, "Rudder  %d    ",ControlledAC->fly.pAcmModel->CtrlRudder);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "Throttle  %d  ",ControlledAC->fly.thrustpercent);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		
		

	}

	if (Atmosphere)
	{

		y++;

		// ATMOSPHERE

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "kg/m^2  %.3f  ", mod->AmbDensity*10000);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "Celcius %.0f  ", mod->AmbTemp-273.15);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "mBars   %.0f  ", mod->AmbPres*100);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (x,y++,(UByte*)strg);

//		if (MMC.Sky.GUSTS)
//		{
//			PrintString (x,y++,"GUSTS");
//			if (MMC.Sky.Gust.ACTIVE)
//			{
//				PrintVar (x, y++, "time %ld     ", MMC.Sky.Gust.Time);
//				PrintVar (x, y++, "g.x %ld     ", MMC.Sky.Gust.Vec.x);
//				PrintVar (x, y++, "g.y %ld     ", MMC.Sky.Gust.Vec.y);
//				PrintVar (x, y++, "g.z %ld     ", MMC.Sky.Gust.Vec.z);
//			}
//		}
//		else
//			PrintString (x,y++,"NO GUSTS");

	}

	if (Mass)
	{

		y++;

		PrintVar (x,y++, "Mass (Kg) %.3f", mod->Mass / 100);
		PrintVar (x,y++, "Ixx (Slug.ft^2) %.0f ", mod->RotInertia.x / 1355827);
		PrintVar (x,y++, "Iyy (Slug.ft^2) %.0f ", mod->RotInertia.y / 1355827);
		PrintVar (x,y++, "Izz (Slug.ft^2) %.0f ", mod->RotInertia.z / 1355827);
//		PrintVar (x,y++, "Cg.x (cm) %.2f", mod->CGPos.x);
//		PrintVar (x,y++, "Cg.y (cm) %.2f", mod->CGPos.y);
//		PrintVar (x,y++, "Cg.z (cm) %.2f", mod->CGPos.z);
	}

	if (Anims)
	{

		y++;

		PMODELANIM pAnim = mod->AnimList;

		while (pAnim != NULL)
		{
			PrintVar (x, y++, "%d   ", *(UByte*)(pAnim->pAnim));
			pAnim = pAnim->List.NextItem ();
		}
	}

	if (Gear)
	{
		PrintVar( 0, 3, "Vel.Z %.2f ", FP(-mod->AirVel.z));
		PrintVar( 0, 4, "Vel.X %.2f ", FP(-mod->AirVel.x));
		PrintVar( 0, 5, "Roll  %.4f ", FP(mod->fRoll * 57.3));
		PrintVar( 0, 6, "Pitch %.4f ", FP(mod->fPitch * 57.3));

		PGEAR pGear = mod->GearList;

		while (pGear != NULL)
		{
			FCRD GlobForce;
			TnsPnt(pGear->TyreForce, GlobForce, mod->Ori);

			switch(pGear->Ident)
			{
				case NOSE:
				{
					PrintVar(30,  5, "LegPos  %.4f ", FP(pGear->LegPos));
					PrintVar(30,  6, "Force.X %.0f ", FP(GlobForce.x));
					PrintVar(30,  7, "Force.Y %.0f ", FP(GlobForce.y));
					PrintVar(30,  8, "Force.Z %.0f ", FP(GlobForce.z));
					break;
				}
				case PORT:
				{
					PrintVar( 0, 10, "LegPos  %.4f ", FP(pGear->LegPos));
					PrintVar( 0, 11, "Force.X %.0f ", FP(GlobForce.x));
					PrintVar( 0, 12, "Force.Y %.0f ", FP(GlobForce.y));
					PrintVar( 0, 13, "Force.Z %.0f ", FP(GlobForce.z));
					break;
				}
				case STBD:
				{
					PrintVar(60, 10, "LegPos  %.4f ", FP(pGear->LegPos));
					PrintVar(60, 11, "Force.X %.0f ", FP(GlobForce.x));
					PrintVar(60, 12, "Force.Y %.0f ", FP(GlobForce.y));
					PrintVar(60, 13, "Force.Z %.0f ", FP(GlobForce.z));
					break;
				}
				case TAIL:
				{
					PrintVar(30, 15, "LegPos  %.4f ", FP(pGear->LegPos));
					PrintVar(30, 16, "Force.X %.0f ", FP(GlobForce.x));
					PrintVar(30, 17, "Force.Y %.0f ", FP(GlobForce.y));
					PrintVar(30, 18, "Force.Z %.0f ", FP(GlobForce.z));
					break;
				}
			}
			pGear = pGear->List.NextItem ();
		}
	}
//DeadCode PD 13Nov97 #undef VOID


	if (Acm && !mod->Controlled)
	{
		y++;
		PrintVar (x,y++, "ACM  %.8x   ", (ULong)ControlledAC->ai.manoeuvre);
		PrintVar (x,y++, "Phase %ld   ", ControlledAC->ai.ManStep);
	}	

//*****************************************************************************	
	if( (AnglesForces) && /*!(mod->FrameCount & 0x0003) &&*/ (!mod->bACM) )	//CSB 07/12/98
	{
		x = 35;
		y = 0;

//Conditions
		PrintVar(x+0 , y, "Alt: %.2f ", (FP)mod->Pos.y / 100);
		PrintVar(x+13, y, "Rho: %.3f ", (FP)mod->AmbDensity * 10000);
		PrintVar(x+25, y, "M: %.2f ", (FP)mod->Inst.MachNo);

		PrintVar(x+33, y, "M: %.2f ", (FP)(mod->Mass * 0.01));
//Controls
		y++;
		PrintVar(x+0, y++, "Ail: %.0f ", (FP)mod->Aileron);
		PrintVar(x+0, y++, "Ele: %.0f ", (FP)mod->Elevator);
		PrintVar(x+0, y++, "Rud: %.0f ", (FP)mod->Rudder);

//Gusts
//DeadCode CSB 30/04/99			x = 50;
//DeadCode CSB 30/04/99			y = 1;
//DeadCode CSB 30/04/99	
//DeadCode CSB 30/04/99			PrintVar(x+0, y++, "Gust.x: %.2f ", (FP)mod->Gust.Vec.x);
//DeadCode CSB 30/04/99			PrintVar(x+0, y++, "Gust.y: %.2f ", (FP)mod->Gust.Vec.y);
//DeadCode CSB 30/04/99			PrintVar(x+0, y++, "Gust.z: %.2f ", (FP)mod->Gust.Vec.z);

//Angles
		x = 50;
		y = 1;

		PrintVar(x+0, y++, "Pitch: %.2f ", (FP)(mod->fPitch * 57.3));
		PrintVar(x+0, y++, "Hdg:   %.2f ", (FP)(mod->fHdg * 57.3));
		PrintVar(x+0, y++, "Roll   %.2f ", (FP)(mod->fRoll * 57.3));

		
//Velocities
		x = 0;
		y = 0;

		PrintVar(0 , y, "V :x %.1f ", (FP)-mod->AirVel.x);
		PrintVar(12, y, "V :y %.1f ", (FP)-mod->AirVel.y);
		PrintVar(20, y, "V :z %.1f ", (FP)-mod->AirVel.z);

//Acceleration
		y++;
		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "A :x %.1f ", 100*mod->Acc.x);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (0, y, (UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "y %.1f ", 100*mod->Acc.y);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (12, y, (UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "z %.1f ", 100*mod->Acc.z);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (20, y, (UByte*)strg);
//Rotational Velocities
		y++;
		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "RV:x %.2f ", 100*mod->RotVel.x);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (0, y, (UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "y %.2f ", 100*mod->RotVel.y);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (12, y, (UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "z %.2f ", 100*mod->RotVel.z);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (20, y, (UByte*)strg);
//Rotational Acceleration
		y++;
		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "RA:x %.2f ", 10000*mod->RotAcc.x);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (0, y, (UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "y %.2f ", 10000*mod->RotAcc.y);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (12, y, (UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "z %.2f ", 10000*mod->RotAcc.z);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (20, y, (UByte*)strg);
//Wings
		y++;
		SWord yy = 0;

		PMAINPLANE pMainPlane = mod->MainPlaneList;
		while (pMainPlane != NULL)
		{
			y++;

			for(SWord wing = 0; wing < 2; wing++)
				for(SWord section = 0; section < 2; section++)
				{
					x = 39 + (40 * pMainPlane->Pos[wing][section].x) / 500 - 5;
					yy = y;

					for (n=0; n<32; n++) strg[n] = 0;
					sprintf (strg, "W Aa: %.2f ", 180/FPIE * pMainPlane->aoa[wing][section]);
					if (strg[31] == 0)
	 					Mono_Text.PrintAt (x, yy++, (UByte*)strg);
			
					for (n=0; n<32; n++) strg[n] = 0;
					sprintf (strg, "W Fx: %.0f ", pMainPlane->eForce[wing][section].x);
					if (strg[31] == 0)
	 					Mono_Text.PrintAt (x, yy++, (UByte*)strg);
					
					for (n=0; n<32; n++) strg[n] = 0;
					sprintf (strg, "W Fy: %.0f ", pMainPlane->eForce[wing][section].y);
					if (strg[31] == 0)
	 					Mono_Text.PrintAt (x, yy++, (UByte*)strg);
			
					for (n=0; n<32; n++) strg[n] = 0;
					sprintf (strg, "W Fz: %.0f ", pMainPlane->eForce[wing][section].z);
					if (strg[31] == 0)
	 					Mono_Text.PrintAt (x, yy++, (UByte*)strg);
			
					for (n=0; n<32; n++) strg[n] = 0;
					sprintf (strg, "W Mx: %.0f ", pMainPlane->eMoment[wing][section].x);
					if (strg[31] == 0)
	 					Mono_Text.PrintAt (x, yy++, (UByte*)strg);
			
					for (n=0; n<32; n++) strg[n] = 0;
					sprintf (strg, "W My: %.0f ", pMainPlane->eMoment[wing][section].y);
					if (strg[31] == 0)
	 					Mono_Text.PrintAt (x, yy++, (UByte*)strg);
			
					for (n=0; n<32; n++) strg[n] = 0;
					sprintf (strg, "W Mz: %.0f ", pMainPlane->eMoment[wing][section].z);
					if (strg[31] == 0)
	 					Mono_Text.PrintAt (x, yy++, (UByte*)strg);

//DeadCode CSB 30/06/99						if(pMainPlane->stalled[wing][section]) Mono_Text.PrintAt (x, yy++, (UByteP)"* STALLED *" );
//DeadCode CSB 30/06/99						else  								   Mono_Text.PrintAt (x, yy++, (UByteP)"           " );
				}
			pMainPlane = pMainPlane->List.NextItem ();
			if(yy>20)
				FP BreakPoint0 = 0.0;
		}

		PrintVar(60, 15, "Buffet %.1f ", FP(mod->TotalBuffet));

		PrintVar(50, 13, "DownWash S %.1f ", FP(mod->MainPlaneList->DownWashAng[0] * 57.3));
		PrintVar(50, 14, "DownWash P %.1f ", FP(mod->MainPlaneList->DownWashAng[1] * 57.3));
		
//DeadCode CSB 08/12/98			y = yy;
//DeadCode CSB 08/12/98			y--;

		PCYLINDER Cylinder = mod->CylinderList;
		while (Cylinder != NULL)
		{
			x = 39 + (40 * Cylinder->Pos.x) / 500 - 5;
			y++;

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "C Fx: %.0f ",  Cylinder->Force.x);
			if (strg[31] == 0)
		 		Mono_Text.PrintAt (x, y++, (UByte*)strg);
			
			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "C Fy: %.0f ", Cylinder->Force.y);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x, y++, (UByte*)strg);

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "C Fz: %.0f ", Cylinder->Force.z);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x, y++, (UByte*)strg);

			Cylinder = Cylinder->List.NextItem ();
		}
	
		y++;
		y++;

		PSURFACE Surface = mod->SurfaceList;
		while (Surface != NULL)
		{
			x = 39 + (40 * Surface->Pos.x) / 150 - 5;
			yy = y;

//DEADCODE RDH 30/06/99 			for (n=0; n<32; n++) strg[n] = 0;
//DEADCODE RDH 30/06/99 			sprintf (strg, "S Aa: %.2f ", 180/FPIE * AngleSign(Surface->aoa) );
//DEADCODE RDH 30/06/99 			if (strg[31] == 0)
//DEADCODE RDH 30/06/99 		 		Mono_Text.PrintAt (x, yy++, (UByte*)strg);
			
			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "S Fx: %.0f ", Surface->Force.x);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x, yy++, (UByte*)strg);
	
			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "S Fy: %.0f ", Surface->Force.y);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x, yy++, (UByte*)strg);
	
			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "S Fz: %.0f ", Surface->Force.z);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x, yy++, (UByte*)strg);
	
			Surface = Surface->List.NextItem ();
		}

		y = yy;

		PTHRUSTPOINT ThrustPoint = mod->ThrustList;
		while (ThrustPoint != NULL)
		{
			x = 39 + (40 * ThrustPoint->Pos.x) / 500 - 5;
			y++;

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "T Fz: %.0f ", ThrustPoint->Force.z);
			if (strg[31] == 0)
		 		Mono_Text.PrintAt (x, y, (UByte*)strg);
			
			if(ThrustPoint->pEngine->Type == ET_PISTON)
			{
				for (n=0; n<32; n++) strg[n] = 0;
				sprintf (strg, "E Rpm: %.0f ", ThrustPoint->pEngine->Speed * 954.9296586);
				if (strg[31] == 0)
			 		Mono_Text.PrintAt (x+15, y, (UByte*)strg);
			}
			else
			{
				for (n=0; n<32; n++) strg[n] = 0;
				sprintf (strg, "E Rpm: %.0f ", ThrustPoint->pEngine->SpeedRpm);
				if (strg[31] == 0)
			 		Mono_Text.PrintAt (x+15, y, (UByte*)strg);
			}

			ThrustPoint = ThrustPoint->List.NextItem ();
		}

		PGEAR Gear = mod->GearList;
		while(Gear != NULL)
		{
			switch(Gear->Ident)
			{
				case NOSE:
	 				PrintVar(10, 13, "G y: %.4f ", FP(Gear->LegPos));
	 				PrintVar(10, 14, "G F: %.0f ", FP(Gear->TyreForce.y));
					break;
				case PORT:
	 				PrintVar( 0, 15, "G y: %.4f ", FP(Gear->LegPos));
	 				PrintVar( 0, 16, "G F: %.0f ", FP(Gear->TyreForce.y));
					break;
				case STBD:
	 				PrintVar(20, 15, "G y: %.4f ", FP(Gear->LegPos));
	 				PrintVar(20, 16, "G F: %.0f ", FP(Gear->TyreForce.y));
					break;
				case TAIL:
	 				PrintVar(10, 17, "G y: %.4f ", FP(Gear->LegPos));
	 				PrintVar(10, 18, "G F: %.0f ", FP(Gear->TyreForce.y));
					break;
			}
			Gear = Gear->List.NextItem();
		}
	}
	
	if(Fin)
	{
		PSURFACE Surface = mod->SurfaceList;
		while (Surface != NULL)
		{
			if(Surface->Pos.x == 0)
			{
//DEADCODE RDH 30/06/99 				PrintVar(60, 15, "Aoa     %.2f ", FP(180/FPIE * AngleSign(Surface->aoa)) );
				PrintVar(60, 16, "Vel 0   %.2f ", FP(-mod->AirVel.z));
				PrintVar(60, 17, "Vel 1   %.2f ", FP(Surface->pSlipThrustPoint->pEngine->SlipVel));
				PrintVar(60, 18, "ForceX  %.0f ", FP(Surface->Force.x));
				PrintVar(60, 19, "ForceZ  %.0f ", FP(Surface->Force.z));
			}
			Surface = Surface->List.NextItem ();
		}
	}

	if(Tune)
	{
		FP d      = mod->AmbDensity * 10000;
		FP AltISA = 802729 * d*d*d*d*d*d - 3358891 * d*d*d*d*d + 5531629 * d*d*d*d - 4561006 * d*d*d + 2002783 * d*d - 508295 * d + 98238;
		PrintVar( 0,  5, "Alt     %.0f ", FP(mod->Pos.y / 100));
		PrintVar( 0,  6, "ROC     %.2f ", FP(mod->Vel.y));
		PrintVar( 0,  7, "Pitch   %.2f ", FP(-mod->Vel.y / mod->AirVel.z * 57.3));
		PrintVar( 0,  8, "Density %.3f ", FP(d));
		PrintVar( 0,  9, "Vel     %.2f ", FP(-mod->AirVel.z));
		PrintVar( 0, 10, "Accel   %.2f ", FP(100 * mod->Acc.z));
		PrintVar( 0, 11, "AltISA  %.0f ", FP(AltISA));
		PrintVar( 0, 13, "Elev    %.0f ", FP(mod->Elevator));
	}

}

#endif

void PrintVar (ULong x, ULong y, char* text, ULong var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, SLong var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, FP var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, SWord var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, UWord var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, UByte var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, SByte var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintString (ULong x, ULong y, char* text)
{
#ifdef NO_MONO_DATA
	return;
#endif
	Mono_Text.PrintAt (x,y,(UByte*)text);
}

void PrintHLine (ULong x, ULong y, ULong size, char* c)
{
#ifdef NO_MONO_DATA
	return;
#endif
	for (ULong p=x;p<x+size;p++) Mono_Text.PrintAt (p,y,(UByte*)c);
}
void PrintVLine (ULong x, ULong y, ULong size, char* c)
{
#ifdef NO_MONO_DATA
	return;
#endif
	for (ULong p=y;p<y+size;p++) Mono_Text.PrintAt (x,p,(UByte*)c);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcCanopyVel
//Author		Robert Slater
//Date			Tue 23 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::CalcParachuteVel(SWord &vvx,
								SWord &vvy,
								SWord &vvz,
								SWord	thehdg,
								SWord	thepitch,
								SWord	theroll,
								SWord	vel,
								SWord	pushvel,
								SLong Alt)	//CSB 13/06/99	
{
	Float	vx;
	Float	vy;
	Float	vz;

	if ((!Controlled && !bACM) || _Replay.Playback)
	{
		Ori.x.x = 1;
		Ori.x.y = 0;
		Ori.x.z = 0;
		Ori.y.x = 0;
		Ori.y.y = 1;
		Ori.y.z = 0;
		Ori.z.x = 0;
		Ori.z.y = 0;
		Ori.z.z = 1;

		SetOri (Ori, Rowan2Rads(thepitch), Rowan2Rads(thehdg), Rowan2Rads(theroll));

		Vel.x = Float(vel) * Ori.z.x;
		Vel.y = Float(vel) * Ori.z.y;
		Vel.z = Float(vel) * Ori.z.z;

		SLong wx, wy, wz;					//CSB 13/06/99	
		MMC.Sky.GetWind(Alt, wx, wy, wz);	//CSB 13/06/99	
											//CSB 13/06/99	
		Vel.x += wx * 0.1;					//CSB 13/06/99	
		Vel.y += wy * 0.1;					//CSB 13/06/99	
		Vel.z += wz * 0.1;					//CSB 13/06/99	
	}

	vx = Ori.y.x;
	vy = Ori.y.y;
	vz = Ori.y.z;

	vx *= Float(pushvel);				//RJS 10May99
	vy *= Float(pushvel);				//RJS 10May99
	vz *= Float(pushvel);				//RJS 10May99

	vx += Vel.x;
	vy += Vel.y;
	vz += Vel.z;

	vvx = SWord(vx*10);
	vvy = SWord(vy*10);
	vvz = SWord(vz*10);
}

