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
//Filename       engine.cpp
//System         
//Author         Andrew McRae
//Date           Thu 24 Apr 1997
//Description    Engines
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "ranges.h"
#include "myangles.h"
#include "planetyp.h"
#include "collided.h"
#include "mytime.h"
#include "myerror.h"
#include "monotxt.h"
#include "savegame.h"

//DeadCode RJS 02Dec97 #include "3dcom.h"



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Engine
//Author		Craig Beeston
//Date			Thu 12 Nov 1998
//
//Description	Jet Engine Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Engine::Engine (PMODEL pmodel,
				ENGINE_TYPE type,
				FP		t100,			// static thrust & sea level (lbf)
				FP		rpm100,			// max RPM
				FP		oneovermoi,		// 1 / Moment of Inertia
				PCURVE	machfact,		// thrust variation with mach number
				PCURVE	thrustrpm,		// thrust variation with engine rpm
				PCURVE	windmilldrag,	// windmill drag variation with true air speed
				PCURVE	windmillrpm)	// idle rpm variation with true air speed
{

	NullThis ();

	pModel = pmodel;
	Type = type;

	T100		= t100;
	Rpm100		= rpm100;
	OneOverMoI	= oneovermoi;
	MachFact	= machfact;
	ThrustRpm	= thrustrpm;
	WindMillDrag= windmilldrag;
	WindMillRpm = windmillrpm;

	EngineOut = FALSE;

	List.Attach (&pModel->EngineList, this);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Engine
//Author		Andrew McRae
//Date			Mon 27 Jan 1997
//
//Description	Piston Engine Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Engine::Engine (PMODEL pmodel, ENGINE_TYPE type)
{

	// Initialise

	NullThis ();

	pModel = pmodel;
	Type = type;

	FP ACspeed = VecLen(pModel->Vel);
	if(ACspeed < 10) ACspeed = 10;
	PropVel = ACspeed;				//Speed of airflow through prop			/CSB
	SlipVel = ACspeed;				//Speed of airflow in slipstream		/CSB
	SlipRot = 0;				//Rotation of airflow in slipstream		/CSB
	PropInc = 44;	//CSB 04/06/99	

	List.Attach (&pModel->EngineList, this);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NullThis
//Author		Andrew McRae
//Date			Fri 13 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Engine::NullThis ()
{
	ULong n = sizeof(Engine);
	for (UByte* p=(UByte*)this;n;n--,p++) {	*p = 0;	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Engine
//Author		Andrew McRae
//Date			Mon 27 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Engine::~Engine ()
{

	List.Detach (this);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessPistonEngine
//Author		Craig Beeston
//Date			Tue 11 Aug 98
//
//Description	Processes a piston engine
//					Calculates Thrust, Torque, Engine power and Engine speed
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Engine::ProcessPistonEngine (AirStrucPtr const ControlledAC)
{
	if(ControlledAC->weap.centre.int_fuel <= 0)
		EngineOut = TRUE;

	FP MaxSpeed = pPower100->MaxIndex * 0.001047197;	//RPM 2 Rads/cs

	if (Speed < IdleSpeed) Speed = IdleSpeed;		//500rpm
	if (Speed > MaxSpeed)  Speed = MaxSpeed;		//5000rpm

	FP EngRPM    = Speed * 954.9296586;
	FP PropSpeed = Speed * GearRatio;
	FP PropSwirl = SlipRot * 0.5;


	FCRD Vel;
	CPrd(Vel, pThrustPoint->Pos, pModel->RotVel);
	Vel.z -= pModel->AirVel.z;				//Velocity of air ahead of prop
	
	FP PropAirVel = 0.75 * (PropSpeed - PropSwirl) * BladeRadius;
	FP InflowAng = CalcAngle (PropAirVel, PropVel);

	if((!Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL]) || (ControlledAC != Persons2::PlayerSeenAC))		//Automatic engine speed setting//AMM 29Jun99
//DeadCode AMM 29Jun99 	if (!Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL])		//Automatic engine speed setting
	{
		if(ControlledAC->fly.thrustpercent <= 50)
			pModel->DesiredRPM = 1800;
		else
			pModel->DesiredRPM = 600 + 24 * ControlledAC->fly.thrustpercent;
	}

	FP PropPitchRate = (EngRPM - pModel->DesiredRPM) * 0.0001;
//DeadCode CSB 11/02/99		MODLIMIT(PropPitchRate, 0.5);
	PropInc          += PropPitchRate * pModel->MODEL_DT;

	MODMAXMIN(PropInc, 23, 65);

	FP BladeSpeed = FSqrt(PropAirVel * PropAirVel + PropVel * PropVel);
	FP BladeQS  =  0.5 * pModel->AmbDensity * BladeSpeed * BladeArea;
	
//DeadCode AMM 29Jun99 	J = PropVel / ((PropSpeed - PropSwirl) * 0.75 * BladeRadius);	//Only Used for Text Screen

	FP BladeL = 4.805 * (DEGS2RADS(PropInc) - InflowAng);// * PropEff;	// k = 2.PI / (1+2/AR)   //p302 TOF
	FP BladeD = 0.04 + (0.1 * BladeL * BladeL);	// b = PI.AR //p302 TOF
	MODMAXMIN(BladeL, -1.0, 1.5);

	BladeL *= BladeQS;
	BladeD *= BladeQS;

	Thrust = BladeL * PropAirVel - BladeD * PropVel;
	Torque = BladeD * PropAirVel + BladeL * PropVel;
	Torque *= BladeRadius * 0.5;	//effective overall moment


//Engine Power Output
	AircraftAnimData* adptr = (AircraftAnimData *)ControlledAC->Anim;

	FP fDamage = 1 - adptr->ENGINELEFTIN / 255;
	
	Power100 = pPower100->GetValue (EngRPM) * fDamage;
	Power0   = pPower0->GetValue (EngRPM);

	if(EngineOut)
		Power = Power0;
	else 
		Power = Power0 + ((Power100 - Power0) * ControlledAC->fly.thrustpercent * 1e-2);

	if( (pModel->Pos.y > HighBlowerAlt) && (!BlowerHigh) ) BlowerHigh = TRUE;
	if( (pModel->Pos.y < LowBlowerAlt ) && ( BlowerHigh) ) BlowerHigh = FALSE;

	if(BlowerHigh)													//High Gear
		Power *= pPowerAltSuper->GetValue (pModel->Pos.y * 0.032808);
	else															//Low Gear
		Power *= pPowerAlt->GetValue (pModel->Pos.y * 0.032808);
	
	FP EngTorque = Power * 745 / Speed;

//DeadCode AMM 29Jun99 	eff = Thrust * Vel.z / (Power * 745);
//Slipstream Conditions
	FP OldSlipRot = SlipRot;
	FP SlipInertia = BladeRadius * BladeRadius * BladeRadius * BladeRadius 
		              * 0.5 * FPIE * PropVel * pModel->AmbDensity;
	SlipRot		   = (Torque / SlipInertia + OldSlipRot) * 0.5;
	if(SlipRot > PropSpeed) SlipRot = PropSpeed;

	FP OldSlipVel = SlipVel;
	FP PropArea = FPIE * BladeRadius * BladeRadius;
	FP TempSlip = 2 * Thrust / (pModel->AmbDensity * PropArea) + Vel.z * Vel.z;
	if (TempSlip < 0) SlipVel = -Vel.z;
	else 
		SlipVel = sqrt(TempSlip);
	SlipVel = (SlipVel + OldSlipVel) * 0.5;
	PropVel = 0.5 * (0.5 * (Vel.z + SlipVel) + PropVel);

// calc engine speed
	FP EngRotAcc = (EngTorque - Torque * GearRatio) / MoI;

	if (!Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL])
		EngRotAcc *= 2;												//Fast Spooling

	Speed += pModel->MODEL_DT * EngRotAcc;
	
	if (Speed < IdleSpeed) Speed = IdleSpeed;				//500rpm
	if (Speed > MaxSpeed)  Speed = MaxSpeed;				//5000rpm
				
//DeadCode AMM 29Jun99 	Thrust *= EngineCount;
//DeadCode AMM 29Jun99 	Torque *= EngineCount;
	
//	if(pModel->Type == AT_F82G)	//Counter Rotating Engines and Props	//CSB
//	{
//		Torque = 0.0;
//		Swirl2 = 0.0;
//	}

//DeadCode CSB 22/12/98		if (Save_Data.flightdifficulty [FD_POWERBOOST])
//DeadCode CSB 22/12/98			Thrust *= pModel->PowerBoost;

//Export values back to original variables
//DeadCode CSB 18/01/99		Speed   = EngRot * 0.01;
//DeadCode CSB 18/01/99		PropVel = Speed1;				//Speed of air through propellor
//DeadCode CSB 18/01/99		SlipVel = Speed2;				//Speed of air in slipstream
//DeadCode CSB 18/01/99		SlipRot = Swirl2 * 0.01;		//Swirl in Slipstream (Rad/s)
	Torque	= -Torque * RotateDirection;//(EngTorque - Torque / GearRatio);				//Reacted into Airframe

	if (Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS])
	{
		FCRD TempRot;
		CopyVec(pModel->RotVel, TempRot);
		TempRot.z += Speed * RotateDirection;

		moment.x = TempRot.x * PropInertia.x;
		moment.y = TempRot.y * PropInertia.y;
		moment.z = TempRot.z * PropInertia.z;
		
		CPrd(moment, moment, TempRot);
		moment.x *= -1;
		moment.y *= -1;
		moment.z *= -1;
	}
	else 
		NullVec(moment);

//DeadCode CSB 28/04/99		PrintVar(60, 0, "RPM %.0f ", (FP)EngRPM);
}	


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessJetEngine
//Author		Craig Beeston
//Date			Fri 13 Nov 1998
//
//Description	Processes a jet engine
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Engine::ProcessJetEngine (AirStrucPtr const ControlledAC)
{
	if(ControlledAC->weap.centre.int_fuel <= 0)
		EngineOut = TRUE;

	// For turbo jet only.
	PMODEL pModel = ControlledAC->fly.pModel;

	if( (Save_Data.flightdifficulty [FD_JETFLAMEOUT]) && (Manual_Pilot.ControlledAC2 == ControlledAC) )
		if( (pModel->AirSpeed > 15) && (pModel->AirSpeed > -2.0 * pModel->AirVel.z) )	//60 deg cone
//DeadCode CSB 03/03/99			if ((pModel->AirVel.z > 10) )//&& (pModel->AirSpeed < 20))
			if(!EngineOut)
			{
				AirStrucPtr buddy = ControlledAC->FindBuddy();
				if(buddy)
				{
					if(Math_Lib.rnd(2) == 1)	
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAMEOUT0, MSG_STATUSRESPONSE_DELAY_LP_RPT, ControlledAC, NULL, buddy));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAMEOUT1, MSG_STATUSRESPONSE_DELAY_LP_RPT, ControlledAC, NULL, buddy));
				}
				else
				{
					if(Math_Lib.rnd(2) == 1)	
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAMEOUT0, MSG_STATUSRESPONSE_DELAY_LP_RPT, ControlledAC, NULL, ControlledAC));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAMEOUT1, MSG_STATUSRESPONSE_DELAY_LP_RPT, ControlledAC, NULL, ControlledAC));
				}


				EngineOut = TRUE;
			}

	if(EngineOut) ControlledAC->fly.thrustpercent = 0;

	FP Throttle = 0.01 * ControlledAC->fly.thrustpercent;

	FP VeryMinRpm = Rpm100 * WindMillRpm->GetValue(0);
	FP MinVal = 1000;
	if(!EngineOut) MinVal = 0.25 * Rpm100;

	if(VeryMinRpm < MinVal) VeryMinRpm = MinVal;
	if(SpeedRpm < VeryMinRpm) SpeedRpm = VeryMinRpm;

//DeadCode CSB 19/11/98		FP RelPres	 = pModel->AmbPres / 10.13;
	FP RelDens	 = pModel->AmbDensity / 0.0001225;
	FP RelTemp	 = pModel->AmbTemp / 288.15;
	
	FP MachFactor =  MachFact->GetValue(pModel->Inst.MachNo);
	Thrust		  =  T100 * ThrustRpm->GetValue(SpeedRpm / (Rpm100 * FSqrt(RelTemp)));
	Thrust  	  *= RelDens * MachFactor;
	if(EngineOut) Thrust = 0;

	FP WindDrag =  T100 * WindMillDrag->GetValue(pModel->AirSpeed);
	Thrust		+= WindDrag;


	AircraftAnimData* adptr = (AircraftAnimData *)ControlledAC->Anim;
	FP fDamage = 1 - adptr->ENGINELEFTIN / 255;

	MaxThrust		 = T100 * RelDens * MachFactor * fDamage;	//Maximum available thrust at present altitude and mach number
	FP DesiredThrust = MaxThrust * Throttle;

	FP ThrottleFactor = 1 - Throttle;
	ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^2
	ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^4
	ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^16
	ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^32
	ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^64
	ThrottleFactor = 1 - ThrottleFactor;

	FP IdleRpm	   = Rpm100 * WindMillRpm->GetValue(pModel->AirSpeed);
	FP DeltaRpm100 = (SpeedRpm / Rpm100) * ThrottleFactor * (DesiredThrust - Thrust);
	FP DeltaRpm0   = (1 - ThrottleFactor) * (IdleRpm - SpeedRpm);
	FP DeltaRpm    = DeltaRpm100 + DeltaRpm0;
	
//DeadCode CSB 11/12/98		if(Manual_Pilot.ControlledAC2 != ControlledAC)
//DeadCode CSB 11/12/98		{
//DeadCode CSB 11/12/98			FP FightingFactor = (FP)ControlledAC->FlyingFactor();
//DeadCode CSB 11/12/98			FP ThrustInc = (FightingFactor - 128)/256;
//DeadCode CSB 11/12/98			Thrust *= (1 + ThrustInc);
//DeadCode CSB 11/12/98		}

//DeadCode CSB 30/11/98		if( (Save_Data.flightdifficulty [FD_POWERBOOST]) && (pModel->Controlled) )
//DeadCode CSB 30/11/98			Thrust *= pModel->PowerBoost;

	if( (!Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL]) || (Manual_Pilot.ControlledAC2 != ControlledAC) )//(pModel->ACM) )
		DeltaRpm *= 8;//Fast Spooling

	if((Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL]) && (Manual_Pilot.ControlledAC2 == ControlledAC))
		if(pModel->Inst.ExhaustTemp > 225)	//Throttle advanced too quickly
		{
			if(pModel->FrameCount & 0x0002)
				DeltaRpm *= -0.5;
			if(Math_Lib.rnd(256) < pModel->Inst.ExhaustTemp - 225) 
				if(adptr->ENGINELEFTIN < 255)
					adptr->ENGINELEFTIN += 1;
//DeadCode CSB 28/04/99				PrintVar(60, 1, "EGT %.0f ", (FP)pModel->Inst.ExhaustTemp);
//DeadCode CSB 28/04/99				PrintVar(60, 2, "ENG %.0f ", (FP)adptr->ENGINELEFTIN);
		}
	
	SpeedRpm += T100 * DeltaRpm * pModel->MODEL_DT * OneOverMoI;

	if( (pModel->Speed < 10) && (Thrust < 0) ) Thrust = 0;

//DeadCode CSB 28/04/99		PrintVar(60, 0, "RPM %.0f ", (FP)SpeedRpm);
}
