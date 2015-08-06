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

//DeadCode ARM 03Nov97 //------------------------------------------------------------------------------
//DeadCode ARM 03Nov97 //Filename       mig15.cpp
//DeadCode ARM 03Nov97 //System         
//DeadCode ARM 03Nov97 //Author         Andrew McRae
//DeadCode ARM 03Nov97 //Date           Wed 29 Jan 1997
//DeadCode ARM 03Nov97 //Description    F86E Sabre flight data
//DeadCode ARM 03Nov97 //------------------------------------------------------------------------------
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 #include "dosdefs.h"
//DeadCode ARM 03Nov97 #include "worldinc.h"
//DeadCode ARM 03Nov97 #include "modvec.h"
//DeadCode ARM 03Nov97 #include "model.h"
//DeadCode ARM 03Nov97 #include "3dcom.h"
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 void MIG15_Setup (AirStrucPtr const ControlledAC)
//DeadCode ARM 03Nov97 {
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	ClassPtr data = ControlledAC->classtype;
//DeadCode ARM 03Nov97 	PMODEL pModel = ControlledAC->fly.pModel;
//DeadCode ARM 03Nov97 	Model& Model = *ControlledAC->fly.pModel;
//DeadCode ARM 03Nov97 	ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;
//DeadCode ARM 03Nov97 	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	Model.Type = AT_MIG15;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	PSURFACE pSurface;
//DeadCode ARM 03Nov97 	PMAINPLANE pMainPlane;
//DeadCode ARM 03Nov97 	PCTRL pCtrl;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	pMainPlane = new MAINPLANE (pModel, ST_DUALMAINPLANE, SD_MAINPLANE, 237000, 222, 235, 1.0);
//DeadCode ARM 03Nov97 	pMainPlane->SetOrientation (1, -10, 3);
//DeadCode ARM 03Nov97 	pMainPlane->SetCurves ("MIG15", "Cl", "Cd", "CompCd", "Cm");
//DeadCode ARM 03Nov97 	pMainPlane->SetDragPolar (0.015, 0.06);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// tail plane
//DeadCode ARM 03Nov97 	pSurface = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 31876, 99.8, 3.5);
//DeadCode ARM 03Nov97 	pSurface->SetPosition (0,149.7, -1474.1);
//DeadCode ARM 03Nov97 	pSurface->SetOrientation (2,0,0);
//DeadCode ARM 03Nov97 	pSurface->SetCurves ("MIG15", "TailCl", "COMM", "TailCd", "", "");
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// fin
//DeadCode ARM 03Nov97 	pSurface = new SURFACE (pModel, ST_PLANE, SD_FIN, 54616, 254.5, 3.0);
//DeadCode ARM 03Nov97 	pSurface->SetPosition (0,107.3,-1374.3);
//DeadCode ARM 03Nov97 	pSurface->SetOrientation (0,0,-90);
//DeadCode ARM 03Nov97 	pSurface->SetCurves ("MIG15", "FinCl", "COMM", "TailCd", "", "");
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new AEROCTRL (pModel, &Model.Aileron, &Model.NettMoment.z, 250);
//DeadCode ARM 03Nov97 	new AEROCTRL (pModel, &Model.Elevator, &Model.NettMoment.x, -1100);
//DeadCode ARM 03Nov97 	new AEROCTRL (pModel, &Model.Rudder, &Model.NettMoment.y, 400);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SURFACE, pModel, &Model.Aileron, &adptr->acaileronr, 64);
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SURFACE, pModel, &Model.Aileron, &adptr->acaileronl, -64);
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SURFACE, pModel, &Model.Elevator, &adptr->acelevator, -64);
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SURFACE, pModel, &Model.Rudder, &adptr->acrudder, 64);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new AERODEVICE (pModel, AeroDevice::DT_FLAPS, 0.2, 0.005, -0.1, DEGS2RADS(4), 512, FLAPSUPDOWN, &adptr->acflaps, 64);
//DeadCode ARM 03Nov97 	new AERODEVICE (pModel, AeroDevice::DT_SPEEDBRAKES, 0, 0.015, 0.2, 0, 512, SPEEDBRAKE, &adptr->acbreak, 64);
//DeadCode ARM 03Nov97 	new AERODEVICE (pModel, AeroDevice::DT_GEAR, 0, 0.007, -0.05, 0, 256, GEARUPDOWN, NULL, 0);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// mass
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	Model.Mass = 424300;
//DeadCode ARM 03Nov97 	pModel->SetupMassPoints (9500, 15000);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// Order specific
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	PENGINE pEngine = new ENGINE (pModel, ET_JET,
//DeadCode ARM 03Nov97 							5005, _CurveRsc.FindCurve ("MIG15", "JetCr"),
//DeadCode ARM 03Nov97 							0.1, 12300, 1000, 0.005);
//DeadCode ARM 03Nov97 	pEngine->SetNewJetVars (5005, 7000, 1.2);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// thrust
//DeadCode ARM 03Nov97 	PTHRUSTPOINT pThrust = new THRUSTPOINT (pModel, TT_JET, 0,0,-500, 0,0);
//DeadCode ARM 03Nov97 	
//DeadCode ARM 03Nov97 	pThrust->SetEngine (pEngine);
//DeadCode ARM 03Nov97 	pEngine->SetThrustPoint (pThrust);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// UnderCarriage
//DeadCode ARM 03Nov97 	// order specific
//DeadCode ARM 03Nov97 	// always nose/tail first (x=0)
//DeadCode ARM 03Nov97 	// then port (-x)
//DeadCode ARM 03Nov97 	// then stbd (+x)
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// main gear legs must have equal z positions
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	PGEAR pGear;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// nose
//DeadCode ARM 03Nov97 	pGear = new GEAR (pModel, NOSE);
//DeadCode ARM 03Nov97 	pGear->SetDimensions (0,-170,400,0,-110,400);
//DeadCode ARM 03Nov97 	pGear->SetSuspension (0.96, 0.98 ,400);
//DeadCode ARM 03Nov97 	pGear->SetTyres (80, 2, 2, 1000, 0, 20000);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SUSPENSION, pGear, &adptr->aclegsuspf, 0, 255);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// port
//DeadCode ARM 03Nov97 	pGear = new GEAR (pModel, PORT);
//DeadCode ARM 03Nov97 	pGear->SetDimensions (-150,-160,-35,-150,-110,-35);
//DeadCode ARM 03Nov97 	pGear->SetSuspension (0.96, 0.98 ,1250);
//DeadCode ARM 03Nov97 	pGear->SetTyres (80, 2, 2, 2000, 8000, 20000);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SUSPENSION, pGear, &adptr->aclegsuspl, 0, 255);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// stbd
//DeadCode ARM 03Nov97 	pGear = new GEAR (pModel, STBD);
//DeadCode ARM 03Nov97 	pGear->SetDimensions (150,-160,-35,150,-110,-35);
//DeadCode ARM 03Nov97 	pGear->SetSuspension (0.96, 0.98 ,1250);
//DeadCode ARM 03Nov97 	pGear->SetTyres (80, 2, 2, 2000, 8000, 20000);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SUSPENSION, pGear, &adptr->aclegsuspr, 0, 255);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// Misc
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	Model.CoordRudder = 512;
//DeadCode ARM 03Nov97 	Model.PowerBoost = (FP)1.3;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// ACM Model
//DeadCode ARM 03Nov97 	ACM.pModel = pModel;
//DeadCode ARM 03Nov97 	
//DeadCode ARM 03Nov97 	ACM.BrakePower = 14;
//DeadCode ARM 03Nov97 	ACM.SteerRatio = 8e-6;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	ACM.ClimbRate_Elevator_Damping_Power = 5000;
//DeadCode ARM 03Nov97 	ACM.ClimbRate_Elevator_Offset_Power = 50;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	ACM.Height_Elevator_Offset_Power = 0.1;
//DeadCode ARM 03Nov97 	ACM.Height_Elevator_Limit = 500;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	ACM.RollRate_Aileron_Offset_Power = 12500;	// 25000 5/9/97
//DeadCode ARM 03Nov97 	
//DeadCode ARM 03Nov97 	ACM.Roll_Aileron_Offset_Power = 5000;
//DeadCode ARM 03Nov97 	ACM.Roll_Aileron_MaxBankOffset_Power = 25000;
//DeadCode ARM 03Nov97 	
//DeadCode ARM 03Nov97 	ACM.Heading_Aileron_Limit = DEGS2RADS(45);
//DeadCode ARM 03Nov97 	ACM.Heading_Aileron_Offset_Power = 5000;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	ACM.PitchRate_Elevator_Offset_Power = 2048;
//DeadCode ARM 03Nov97 	ACM.PitchRate_Elevator_Damping_Power = 262144;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	ACM.Pitch_Elevator_Offset_Power = 2048;
//DeadCode ARM 03Nov97 	ACM.Pitch_Elevator_Damping_Power = 262144;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	ACM.Speed_Throttle_Offset_Power = 0.5;
//DeadCode ARM 03Nov97 	ACM.Speed_Throttle_Damping_Power = 64;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 }
//DeadCode ARM 03Nov97 
