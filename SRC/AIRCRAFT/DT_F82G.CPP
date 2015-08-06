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
//Filename       F82G.cpp
//System         
//Author         Andrew McRae
//Date           Tue 4 Feb 1997
//Description    Mustang
//------------------------------------------------------------------------------
/*
#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"


void F82G_Setup (AirStrucPtr const ControlledAC, ULong Version)
{

	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
//DeadCode CSB 10/12/98		ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;

	Model.Type = AT_F82G;

//DeadCode CSB 06/11/98		PMAINPLANE pMainPlane = new MAINPLANE (pModel, ST_DUALMAINPLANE, SD_MAINPLANE, 379000, 242);
//DeadCode CSB 06/11/98		pMainPlane->SetPosition(300, -50, -100);	//Generic Values	//CSB 03/11/98
//DeadCode CSB 06/11/98		pMainPlane->SetOrientation (0.5, 0, -6);
//DeadCode CSB 06/11/98		pMainPlane->SetCurves ("F82G", "Cl", "Cd", "CompCd", "Cm");
//DeadCode CSB 06/11/98		pMainPlane->SetDragPolar (0.0068, 0.0186);
//DeadCode CSB 06/11/98		pMainPlane->SeperateAngle = 0.34906585;			//20.0 deg
//DeadCode CSB 06/11/98		pMainPlane->ReattachAngle = 0.0872664625;		// 5.0 deg
	PMAINPLANE pMainPlane = new MAINPLANE (pModel, 71010, 265, 265, 56270, 205, 205);//F86E Data	//CSB 06/11/98
	pMainPlane->SetPosition(175, -55, 15, 420, -40, -165);//F86E Data	//CSB 06/11/98
//SetOrientation (incidence, sweep, dihedral for starboard wing in degrees)
//centre of wing is at y=0,z=0 for a/c and x is +ve for starboard 
	pMainPlane->SetOrientation (0, 0, -3, 0, 0, -3);		//IGNORE SWEEP//F86E Data	//CSB 06/11/98
//DeadCode CSB 25/11/98		pMainPlane->Sweep[0][0] = -0.95993;		//Stbd Inn		-(90% - 1/4 chord sweep)//F86E Data	//CSB 06/11/98
//DeadCode CSB 25/11/98		pMainPlane->Sweep[0][1] = -0.95993;		//Stbd Out//F86E Data	//CSB 06/11/98
//DeadCode CSB 25/11/98		pMainPlane->Sweep[1][0] =  0.95993;		//Port Inn//F86E Data	//CSB 06/11/98
//DeadCode CSB 25/11/98		pMainPlane->Sweep[1][1] =  0.95993;		//Port Out//F86E Data	//CSB 06/11/98

	pMainPlane->buffetAoa0 = 0.2618;	
	pMainPlane->buffetAoa1 = 0.3491;
	pMainPlane->buffetM0  = 0.95;	
	pMainPlane->buffetM1  = 1.05;	
	pMainPlane->ACMmaxaoa = 0.2618;

	PSURFACE pTailPlane = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 64000, 83);
	pTailPlane->SetPosition (0,50,-575);
	pTailPlane->SetOrientation (-0.5,0,0);
	pTailPlane->AmountInSlipstream = 46;
	pTailPlane->SetCurves ("F82G", "TailCl", "COMM", "TailCd", "", "", "COMM", "CompK");

	PSURFACE pFin1 = new SURFACE (pModel, ST_PLANE, SD_FIN, 32517, 140);
	pFin1->SetPosition (-220,112,-665);
	pFin1->SetOrientation (0,0,-90);
	pFin1->AmountInSlipstream = 80;
	pFin1->SetCurves ("F82G", "FinCl", "COMM", "TailCd", "", "", "COMM", "CompK");

	PSURFACE pFin2 = new SURFACE (pModel, ST_PLANE, SD_FIN, 32517, 140);
	pFin2->SetPosition (220,112,-665);
	pFin2->SetOrientation (0,0,-90);
	pFin1->AmountInSlipstream = 80;
	pFin2->SetCurves ("F82G", "FinCl", "COMM", "TailCd", "", "", "COMM", "CompK");

//DeadCode CSB 05/11/98		Model.RotDamping.x = 400;	// Effective Average Half length of fuselage
//DeadCode CSB 05/11/98		Model.RotDamping.y = 400;
//DeadCode CSB 05/11/98		Model.RotDamping.z = 100;	// Average Xpos of tail
//DeadCode CSB 05/11/98		
//DeadCode CSB 05/11/98		Model.RotDampFactor.x = 4.0;//???????????????
//DeadCode CSB 05/11/98		Model.RotDampFactor.y = 2.0;
//DeadCode CSB 05/11/98		Model.RotDampFactor.z = 2.0;

	new NEWCTRL (pMainPlane, &Model.Aileron, 0.25, 0.25);
	new NEWCTRL (pTailPlane, &Model.Elevator, 0.75/1.05, 1.4/1.05);
	new NEWCTRL (pFin1, &Model.Rudder, 0.75/1.05, 0.75/1.05);
	new NEWCTRL (pFin2, &Model.Rudder, 0.75/1.05, 0.75/1.05);
//DeadCode CSB 03/11/98		new NEWCTRL (pMainPlane, &Model.Aileron, 0.96);
//DeadCode CSB 03/11/98		new NEWCTRL (pTailPlane, &Model.Elevator, 2.6);
//DeadCode CSB 03/11/98		new NEWCTRL (pFin1, &Model.Rudder, 2.0);
//DeadCode CSB 03/11/98		new NEWCTRL (pFin2, &Model.Rudder, 2.0);

	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_FLAPS, 0.2, 0.005, -0.1, DEGS2RADS(4), 512, FLAPSUPDOWN, &adptr->acflaps);//RJS 14May98
	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_GEAR, 0, 0.007, -0.05, 0, 256, GEARUPDOWN, NULL, 0);

	Model.MaxG = 9 * GRAVITY;
	Model.MinG = -4 * GRAVITY;

//	Model.MinMass = 725600;
//	Model.MaxMass = 1174400;

//	Model.Mass = (Model.MaxMass + Model.MinMass) * 0.5;
//DeadCode CSB 98		pModel->SetupMassPoints (ControlledAC,16000, 28000);
	pModel->SetMassInertias (ControlledAC, 18460, 30000, 8100);	//F86 slug ft2

	PENGINE pEngine1 = new ENGINE (pModel, ET_PISTON);
 	pEngine1->RotateDirection = 1;			//Clockwise from behind
 	pEngine1->IdleSpeed = RPM2RADSPERCSEC (500);
	pEngine1->MoI = 32e6;
	pEngine1->BladeRadius = 166.372;
	pEngine1->BladeArea = 22144;	// 4x AR=5	//7771;
	pEngine1->GearRatio = 0.478;
	pEngine1->pPower100 = _CurveRsc.FindCurve ("F82G", "Power100");
	pEngine1->pPower0 = _CurveRsc.FindCurve ("F82G", "Power0");
	pEngine1->pPowerAlt = _CurveRsc.FindCurve ("F82G", "PowerAlt");
	pEngine1->pPowerAltSuper = _CurveRsc.FindCurve ("F82G", "PowerAltSuper");		//CSB
//	pEngine1->pPropEff = _CurveRsc.FindCurve ("F82G", "PropEff");
//	pEngine1->pPropTq = _CurveRsc.FindCurve ("F82G", "PropTq");
	pEngine1->HighBlowerAlt = 365764;	//High Gear Supercharger cuts in at 12000ft //CSB
	pEngine1->LowBlowerAlt  = 320044;	//High Gear Supercharger cuts out at 10500ft //CSB
	pEngine1->BlowerHigh	   = FALSE;
	pEngine1->EngineCount = 1;

	PENGINE pEngine2 = new ENGINE (pModel, ET_PISTON);
 	pEngine2->RotateDirection = -1;			//AntiClockwise from behind
 	pEngine2->IdleSpeed = RPM2RADSPERCSEC (500);
	pEngine2->MoI = 32e6;
	pEngine2->BladeRadius = 166.372;
	pEngine2->BladeArea = 22144;	// 4x AR=5	//7771;
	pEngine2->GearRatio = 0.479;
	pEngine2->pPower100 = _CurveRsc.FindCurve ("F82G", "Power100");
	pEngine2->pPower0 = _CurveRsc.FindCurve ("F82G", "Power0");
	pEngine2->pPowerAlt = _CurveRsc.FindCurve ("F82G", "PowerAlt");
	pEngine2->pPowerAltSuper = _CurveRsc.FindCurve ("F82G", "PowerAltSuper");		//CSB
//	pEngine2->pPropEff = _CurveRsc.FindCurve ("F82G", "PropEff");
//	pEngine2->pPropTq = _CurveRsc.FindCurve ("F82G", "PropTq");
	pEngine2->HighBlowerAlt = 365764;	//High Gear Supercharger cuts in at 12000ft //CSB
	pEngine2->LowBlowerAlt  = 320044;	//High Gear Supercharger cuts out at 10500ft //CSB
	pEngine2->BlowerHigh	   = FALSE;
	pEngine2->EngineCount = 1;

	PTHRUSTPOINT pThrust1 = new THRUSTPOINT (pModel, TT_PROP, -220,0,400, 0,0);
	PTHRUSTPOINT pThrust2 = new THRUSTPOINT (pModel, TT_PROP,  220,0,400, 0,0);

	pThrust1->SetEngine (pEngine1);
	pEngine1->SetThrustPoint (pThrust1);

	pThrust2->SetEngine (pEngine2);
	pEngine2->SetThrustPoint (pThrust2);


	PGEAR pTail = new GEAR (pModel, TAIL);
	pTail->SetDimensions (0,-20,-500,0,0,-500);
//DeadCode CSB 12/01/99		pTail->SetSuspension (0.96, 0.98 ,330);
//DeadCode CSB 12/01/99		pTail->SetTyres (80, 2, 2, 500, 200, 5000);
//DeadCode CSB 12/01/99	
	PGEAR pMainPort = new GEAR (pModel, PORT);
	pMainPort->SetDimensions (-170,-100,50,-170,-60,50);
//DeadCode CSB 12/01/99		pMainPort->SetSuspension (0.96, 0.98 ,700);
//DeadCode CSB 12/01/99		pMainPort->SetTyres (80, 2, 2, 1500, 2000, 15000);
//DeadCode CSB 12/01/99	
	PGEAR pMainStbd = new GEAR (pModel, STBD);
	pMainStbd->SetDimensions (170,-100,50,170,-60,50);
//DeadCode CSB 12/01/99		pMainStbd->SetSuspension (0.96, 0.98 ,700);
//DeadCode CSB 12/01/99		pMainStbd->SetTyres (80, 2, 2, 1500, 2000, 15000);

	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl, 32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator, 32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);//RJS 14May98
	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &ControlledAC->fly.rpm, &adptr->acrpm, 65536);//RJS 05May99
//DeadCode RJS 05May99 	new MODELANIM (ControlledAC,MA_SUSPENSION, pTail, &adptr->aclegsuspb, 0, 255);
//DeadCode RJS 05May99 	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
//DeadCode RJS 05May99 	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);

	Model.CoordRudder = 768;
	Model.PowerBoost = 1.4;

	Model.ContrailBand = FEET2CM(10000);
	Model.ContrailDuration = 1.0;

	F82G_SetupAI (ControlledAC, Version);
}
//DeadCode CSB 10/12/98	//	ACM.pModel = pModel;
//DeadCode CSB 10/12/98		
//DeadCode CSB 10/12/98		ACM.BrakePower = 14;
//DeadCode CSB 10/12/98		ACM.SteerRatio = 8e-6;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//	ACM.ClimbRate_Elevator_Damping_Power = 5000;
//DeadCode CSB 10/12/98	//	ACM.ClimbRate_Elevator_Offset_Power = 50;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//	ACM.Height_Elevator_Offset_Power = 0.1;
//DeadCode CSB 10/12/98	//	ACM.Height_Elevator_Limit = 500;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//	ACM.RollRate_Aileron_Offset_Power = 12500;
//DeadCode CSB 10/12/98		
//DeadCode CSB 10/12/98	//	ACM.Roll_Aileron_Offset_Power = 5000;
//DeadCode CSB 10/12/98	//	ACM.Roll_Aileron_MaxBankOffset_Power = 25000;
//DeadCode CSB 10/12/98		ACM.MaxAileron = 32767;
//DeadCode CSB 10/12/98	//	ACM.lastdeltaroll = 0;
//DeadCode CSB 10/12/98		
//DeadCode CSB 10/12/98	//	ACM.Heading_Aileron_Limit = DEGS2RADS(45);
//DeadCode CSB 10/12/98	 //	ACM.Heading_Aileron_Offset_Power = 5000;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//	ACM.PitchRate_Elevator_Offset_Power = 2048;
//DeadCode CSB 10/12/98	//	ACM.PitchRate_Elevator_Damping_Power = 262144;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//DeadCode RDH 17Apr98 	ACM.Pitch_Elevator_Offset_Power = 2048;
//DeadCode CSB 10/12/98	//DeadCode RDH 17Apr98 	ACM.Pitch_Elevator_Damping_Power = 262144;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98		ACM.DeltaPitchForMaxElevator	= 1.0472;
//DeadCode CSB 10/12/98		ACM.MaxElevatorForTightTurn	= 25000;
//DeadCode CSB 10/12/98	//	ACM.DiffPitchForMaxElevator	= 0.1745;
//DeadCode CSB 10/12/98		ACM.lastdeltapitch = 0;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//	ACM.Speed_Throttle_Offset_Power = 0.5;
//DeadCode CSB 10/12/98	//	ACM.Speed_Throttle_Damping_Power = 64;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//DeadCode CSB 06/11/98		Model.ClAileronLoss = 1.50;
//DeadCode CSB 10/12/98		Model.MElevatorLoss = 1.10;	
//DeadCode CSB 10/12/98		
//DeadCode CSB 10/12/98	}
*/
