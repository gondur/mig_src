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
//Filename		 f9f2.cpp
//System         
//Author         Andrew McRae
//Date           Wed 29 Jan 1997
//Description    
//------------------------------------------------------------------------------
/*
#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
//DeadCode RJS 02Dec97 #include "3dcom.h"

void F9F2_Setup (AirStrucPtr const ControlledAC, ULong Version)
{

	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
//DeadCode CSB 10/12/98		ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;

	Model.Type = AT_F9F2;

//DeadCode CSB 06/11/98		PMAINPLANE pMainPlane = new MAINPLANE (pModel, ST_DUALMAINPLANE, SD_MAINPLANE, 232200, 201);
//DeadCode CSB 06/11/98		pMainPlane->SetPosition(300, -50, -100);	//Generic Values	//CSB 03/11/98
//DeadCode CSB 06/11/98		pMainPlane->SetOrientation (0, 0, 0);
//DeadCode CSB 06/11/98		pMainPlane->SetCurves ("F9F2", "Cl", "Cd", "CompCd", "Cm");
//DeadCode CSB 06/11/98		pMainPlane->SetDragPolar (0.0129, 0.0341);
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

	PSURFACE pTailPlane = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 31876, 83);
	pTailPlane->SetPosition (0,149.7, -1474.1);
	pTailPlane->SetOrientation (2,0,0);
	pTailPlane->SetCurves ("F9F2", "TailCl", "COMM", "TailCd", "", "", "COMM", "CompK");

	PSURFACE pFin = new SURFACE (pModel, ST_PLANE, SD_FIN, 54616, 140);
	pFin->SetPosition (0,107.3,-1374.3);
	pFin->SetOrientation (0,0,-90);
	pFin->SetCurves ("F9F2", "FinCl", "COMM", "TailCd", "", "", "COMM", "CompK");

//DeadCode CSB 05/11/98		Model.RotDamping.x = 400;	// Effective Average Half length of fuselage
//DeadCode CSB 05/11/98		Model.RotDamping.y = 400;
//DeadCode CSB 05/11/98		Model.RotDamping.z = 100;	// Average Xpos of tail
//DeadCode CSB 05/11/98		
//DeadCode CSB 05/11/98		Model.RotDampFactor.x = 4.0;//???????????????
//DeadCode CSB 05/11/98		Model.RotDampFactor.y = 2.0;
//DeadCode CSB 05/11/98		Model.RotDampFactor.z = 2.0;

	new NEWCTRL (pMainPlane, &Model.Aileron, 0.25, 0.25);
	new NEWCTRL (pTailPlane, &Model.Elevator, 0.75/1.05, 1.4/1.05);
	new NEWCTRL (pFin, &Model.Rudder, 0.75/1.05, 0.75/1.05);
//DeadCode CSB 03/11/98		new NEWCTRL (pMainPlane, &Model.Aileron, 0.8);
//DeadCode CSB 03/11/98		new NEWCTRL (pTailPlane, &Model.Elevator, 1.6);
//DeadCode CSB 03/11/98		new NEWCTRL (pFin, &Model.Rudder, 1.6);

	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_FLAPS, 0.2, 0.005, -0.1, DEGS2RADS(4), 512, FLAPSUPDOWN, &adptr->acflaps);//RJS 14May98
	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_SPEEDBRAKES, 0, 0.015, 0.2, 0, 512, SPEEDBRAKE, &adptr->acbreak);//RJS 14May98
	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_GEAR, 0, 0.007, -0.05, 0, 256, GEARUPDOWN, NULL, 0);

	Model.MaxG = 7;
	Model.MinG = -3;

//	Model.MinMass = 460300;
//	Model.MaxMass = 934400;

//	Model.Mass = (Model.MinMass + Model.MaxMass) * 0.5;
//DeadCode CSB 98		pModel->SetupMassPoints (ControlledAC,9500, 15000);
	pModel->SetMassInertias (ControlledAC, 18460, 30000, 8100);	//F86 slug ft2

//DeadCode CSB 12/11/98		PENGINE pEngine = new ENGINE (pModel, ET_JET,
//DeadCode CSB 12/11/98								5005, _CurveRsc.FindCurve ("F9F2", "JetCr"),
//DeadCode CSB 12/11/98								0.1, 12300, 1000, 0.005);
//DeadCode CSB 12/11/98		pEngine->SetNewJetVars (4600, 4163, 1.00);
	PENGINE pEngine = new ENGINE (pModel, ET_JET, 26290, 7950, 0.0000001,	//F86F Data
								  _CurveRsc.FindCurve ("F86E", "JetMachFact"),
								  _CurveRsc.FindCurve ("F86E", "JetThrustRpm"),
								  _CurveRsc.FindCurve ("F86E", "JetWindMillDrag"),
								  _CurveRsc.FindCurve ("F86E", "JetWindMillRpm"));

	PTHRUSTPOINT pThrust = new THRUSTPOINT (pModel, TT_JET, 0,0,-500, 0,0);
	
	pThrust->SetEngine (pEngine);
	pEngine->SetThrustPoint (pThrust);

	PGEAR pNose = new GEAR (pModel, NOSE);
	pNose->SetDimensions (0,-170,400,0,-110,400);
//DeadCode CSB 12/01/99		pNose->SetSuspension (0.96, 0.98 ,400);
//DeadCode CSB 12/01/99		pNose->SetTyres (80, 2, 2, 1000, 0, 20000);
//DeadCode CSB 12/01/99	
	PGEAR pMainPort = new GEAR (pModel, PORT);
	pMainPort->SetDimensions (-150,-160,-35,-150,-110,-35);
//DeadCode CSB 12/01/99		pMainPort->SetSuspension (0.96, 0.98 ,1250);
//DeadCode CSB 12/01/99		pMainPort->SetTyres (80, 2, 2, 2000, 8000, 20000);
//DeadCode CSB 12/01/99	
	PGEAR pMainStbd = new GEAR (pModel, STBD);
	pMainStbd->SetDimensions (150,-160,-35,150,-110,-35);
//DeadCode CSB 12/01/99		pMainStbd->SetSuspension (0.96, 0.98 ,1250);
//DeadCode CSB 12/01/99		pMainStbd->SetTyres (80, 2, 2, 2000, 8000, 20000);

	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl, 32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator, 32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SUSPENSION, pNose, &adptr->aclegsuspf, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);

	Model.CoordRudder = 512;
	Model.PowerBoost = (FP)1.3;

	Model.ContrailBand = FEET2CM(10000);
	Model.ContrailDuration = 1.0;

	F9F2_SetupAI (ControlledAC, Version);
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
