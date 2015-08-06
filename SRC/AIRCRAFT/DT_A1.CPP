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
//Filename       A1.cpp
//System         
//Author         Andrew McRae
//Date           Tue 4 Feb 1997
//Description    Mustang
//------------------------------------------------------------------------------

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"


void A1_Setup (AirStrucPtr const ControlledAC, ULong Version)
{

	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
	ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;

	Model.Type = AT_A1;

	PMAINPLANE pMainPlane = new MAINPLANE (pModel, ST_DUALMAINPLANE, SD_MAINPLANE, 306600, 271, 245, 2.2);
	pMainPlane->SetOrientation (0, 0, -5);
	pMainPlane->SetCurves ("A1", "Cl", "Cd", "CompCd", "Cm");
	pMainPlane->SetDragPolar (0.0102, 0.0232);

	PSURFACE pTailPlane = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 50437, 113.7, 3.5);
	pTailPlane->SetPosition (0,42,-540);
	pTailPlane->SetOrientation (-0.5,0,0);
	pTailPlane->LinPropWash = 30;
	pTailPlane->SetCurves ("A1", "TailCl", "COMM", "TailCd", "", "");

	PSURFACE pFin = new SURFACE (pModel, ST_PLANE, SD_FIN, 32517, 154.4, 2.0);
	pFin->SetPosition (0,112,-632);
	pFin->SetOrientation (0,0,-90);
	pFin->RotPropWash = 0.02;
	pFin->SetCurves ("A1", "FinCl", "COMM", "TailCd", "", "");

	new NEWCTRL (pMainPlane, &Model.Aileron, 0.32);
	new NEWCTRL (pTailPlane, &Model.Elevator, 1.1);
	new NEWCTRL (pFin, &Model.Rudder, 0.8);

	new AERODEVICE (pModel, AeroDevice::DT_FLAPS, 0.2, 0.005, -0.1, DEGS2RADS(4), 512, FLAPSUPDOWN, &adptr->acflaps, 64);
	new AERODEVICE (pModel, AeroDevice::DT_GEAR, 0, 0.007, -0.05, 0, 256, GEARUPDOWN, NULL, 0);

	Model.MaxG = 9 * GRAVITY;
	Model.MinG = -4 * GRAVITY;

	Model.MinMass = 447200;
	Model.MaxMass = 707600;

	Model.Mass = (Model.MaxMass + Model.MinMass) * 0.5;
	pModel->SetupMassPoints (8000, 14000);

	PENGINE pEngine = new ENGINE (pModel, ET_PISTON);
 	pEngine->IdleSpeed = RPM2RADSPERCSEC (500);
	pEngine->MoI = 32e6;
	pEngine->BladeRadius = 127.64;
	pEngine->BladeArea = 7771;
	pEngine->GearRatio = 0.479;
	pEngine->pPower100 = _CurveRsc.FindCurve ("A1", "Power100");
	pEngine->pPower0 = _CurveRsc.FindCurve ("A1", "Power0");
	pEngine->pPowerAlt = _CurveRsc.FindCurve ("A1", "PowerAlt");
	pEngine->pPropEff = _CurveRsc.FindCurve ("A1", "PropEff");
	pEngine->pPropTq = _CurveRsc.FindCurve ("A1", "PropTq");
	pEngine->EngineCount = 1;

	PTHRUSTPOINT pThrust = new THRUSTPOINT (pModel, TT_PROP, 0,0,350, 0,0);

	pThrust->SetEngine (pEngine);
	pEngine->SetThrustPoint (pThrust);

	PGEAR pTail = new GEAR (pModel, TAIL);
	pTail->SetDimensions (0,-20,-500,0,0,-500);
	pTail->SetSuspension (0.96, 0.98 ,330);
	pTail->SetTyres (80, 2, 2, 500, 200, 5000);

	PGEAR pMainPort = new GEAR (pModel, PORT);
	pMainPort->SetDimensions (-150,-150,50,-150,-90,50);
	pMainPort->SetSuspension (0.96, 0.98 ,700);
	pMainPort->SetTyres (80, 2, 2, 1500, 2000, 15000);

	PGEAR pMainStbd = new GEAR (pModel, STBD);
	pMainStbd->SetDimensions (150,-150,50,150,-90,50);
	pMainStbd->SetSuspension (0.96, 0.98 ,700);
	pMainStbd->SetTyres (80, 2, 2, 1500, 2000, 15000);

	new MODELANIM (MA_SURFACE, pModel, &Model.Aileron, &adptr->acaileronr, 64);
	new MODELANIM (MA_SURFACE, pModel, &Model.Aileron, &adptr->acaileronl, -64);
	new MODELANIM (MA_SURFACE, pModel, &Model.Elevator, &adptr->acelevator, -64);
	new MODELANIM (MA_SURFACE, pModel, &Model.Rudder, &adptr->acrudder, 64);
	new MODELANIM (MA_GENERICFP, pModel, &pModel->Inst.Rpm1, &adptr->acrpm, 2048);
	new MODELANIM (MA_SUSPENSION, pTail, &adptr->aclegsuspb, 0, 255);
	new MODELANIM (MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
	new MODELANIM (MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);

	Model.CoordRudder = 768;
	Model.PowerBoost = 1.4;

	Model.ContrailBand = FEET2CM(10000);
	Model.ContrailDuration = 1.0;

	ACM.pModel = pModel;
	
	ACM.BrakePower = 14;
	ACM.SteerRatio = 8e-6;

	ACM.ClimbRate_Elevator_Damping_Power = 5000;
	ACM.ClimbRate_Elevator_Offset_Power = 50;

	ACM.Height_Elevator_Offset_Power = 0.1;
	ACM.Height_Elevator_Limit = 500;

	ACM.RollRate_Aileron_Offset_Power = 12500;
	
//DeadCode RDH 17Apr98 	ACM.Roll_Aileron_Offset_Power = 5000;
//DeadCode RDH 17Apr98 d	ACM.Roll_Aileron_MaxBankOffset_Power = 25000;
	ACM.MaxAileron = 32767;
	ACM.lastdeltaroll = 0;

	ACM.Heading_Aileron_Limit = DEGS2RADS(45);
	ACM.Heading_Aileron_Offset_Power = 5000;

	ACM.PitchRate_Elevator_Offset_Power = 2048;
	ACM.PitchRate_Elevator_Damping_Power = 262144;

//DeadCode RDH 17Apr98 	ACM.Pitch_Elevator_Offset_Power = 2048;
//DeadCode RDH 17Apr98 	ACM.Pitch_Elevator_Damping_Power = 262144;

	ACM.DeltaPitchForMaxElevator	= 1.0472;
	ACM.MaxElevatorForTightTurn	= 25000;
	ACM.DiffPitchForMaxElevator	= 0.1745;
	ACM.lastdeltapitch = 0;

	ACM.Speed_Throttle_Offset_Power = 0.5;
	ACM.Speed_Throttle_Damping_Power = 64;

	pMainPlane->buffetCl0 = 1.00	
	pMainPlane->buffetCl1 = 1.25
	pMainPlane->buffetM0  = 0.90	
	pMainPlane->buffetM1  = 1.10;	
	pMainPlane->ACMmaxaoa = 0.20;	
}


