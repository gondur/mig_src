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
//Filename       f80c.cpp
//System         
//Author         Andrew McRae
//Date           Wed 29 Jan 1997
//Description    F80C Shooting Star flight data
//------------------------------------------------------------------------------

#include "dosdefs.h"
#include "worldinc.h"
#include "3DCom.h"
#include "modvec.h"
#include "model.h"

void F80C_Setup (AirStrucPtr const ControlledAC, ULong Version)
{
	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;

	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;

	Model.Type = AT_F80C;
	SWord CoG = -495;//-450;//	//26%MAC

	PMAINPLANE pMainPlane = new MAINPLANE (pModel, 75000, 230, 320, 35000, 135, 260);
	pMainPlane->SetPosition(125, -45, -490-CoG, 425, -25, -500-CoG);
	pMainPlane->SetOrientation (0.75, 0, 4, 0.75, 0, 4);		//IGNORE SWEEP
	pMainPlane->SetMaskAngle(0, 0, 0, 0);//-0.553, -0.829, 67, 67);//

	pMainPlane->SetCurves ("F80C", "Cl", "Cd", "CompCd0", "CompK", "Cm");
	pMainPlane->SetDragPolar (0.0231, 0.0585);	
//DeadCode AMM 29Jun99 	pMainPlane->StallAoa = Degs2Rads(0);//22.5);//
//DeadCode AMM 29Jun99 	pMainPlane->UnStallAoa = Degs2Rads(10);
	pMainPlane->dCMdq = 0;
	pMainPlane->dCMdp = 0;
	pMainPlane->dCMdr = 0;

	pMainPlane->buffetAoa0 = Degs2Rads(15);	
	pMainPlane->buffetAoa1 = Degs2Rads(20);
	pMainPlane->buffetM0  = 0.95;	
	pMainPlane->buffetM1  = 1.05;	
	pMainPlane->ACMmaxaoa = Degs2Rads(17.5);

	PSURFACE pTailPlane1 = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 20000);//, 115);
	pTailPlane1->SetPosition (70, 55, -950-CoG);
	pTailPlane1->SetOrientation (0, 0, 0);
	pTailPlane1->SetMaskAngle(0, 0);//-0.742);//
	pTailPlane1->SetCurves ("F80C", "TailCl", "COMM", "TailCd");//, "", "", "COMM", "CompK");

	PSURFACE pTailPlane2 = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 20000);//, 115);
	pTailPlane2->SetPosition (-70, 55, -950-CoG);
	pTailPlane2->SetOrientation (0, 0, 0);
	pTailPlane2->SetMaskAngle(0, 0);//0.742);//
	pTailPlane2->SetCurves ("F80C", "TailCl", "COMM", "TailCd");//, "", "", "COMM", "CompK");

	PSURFACE pFin = new SURFACE (pModel, ST_PLANE, SD_FIN, 23000);//, 160);
	pFin->SetPosition (0, 90, -950-CoG);
	pFin->SetOrientation (0, 0, -90);
	pFin->SetMaskAngle(0, 0);//-0.253, 50);//
	pFin->SetCurves ("F80C", "FinCl", "COMM", "TailCd");//, "", "", "COMM", "CompK");

	PCYLINDER pCylinder1 = new CYLINDER (pModel, 375, 130, 125);
	pCylinder1->SetPosition(0, 0, -200-CoG);

	PCYLINDER pCylinder2 = new CYLINDER (pModel, 325, 175, 125);
	pCylinder2->SetPosition(0, 0, -550-CoG);

	PCYLINDER pCylinder3 = new CYLINDER (pModel, 350, 120, 115);
	pCylinder3->SetPosition(0, 0, -950-CoG);


	new NEWCTRL (pMainPlane,  &Model.Aileron,  20, Degs2Rads(10), Degs2Rads(10));
	new NEWCTRL (pTailPlane1, &Model.Elevator, 30, Degs2Rads(20), Degs2Rads(30));
	new NEWCTRL (pTailPlane2, &Model.Elevator, 30, Degs2Rads(20), Degs2Rads(30));
	new NEWCTRL (pFin,        &Model.Rudder,   20, Degs2Rads(20), Degs2Rads(20));

//DeadCode AMM 29Jun99 	Model.ControlPower		= 0.1;
//DeadCode AMM 29Jun99 	Model.ControlResistance = 0;//1000;

	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_FLAPS, 0.5, 0.15, -0.25, DEGS2RADS(5), 256, FLAPSUPDOWN, &adptr->acflaps);//RJS 14May98
	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_SPEEDBRAKES, 0, 0.05, -0.01, 0, 256, SPEEDBRAKE, &adptr->acbreak);//RJS 14May98
	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_GEAR,  0,   0.05, -0.01, 0, 128, GEARUPDOWN, NULL, 0);

	Model.MaxG = 9;
	Model.MinG = -4;

//DeadCode CSB 06/07/99		pModel->SetMassInertias (ControlledAC, 26500, 36800, 11000);
	pModel->SetMassInertias (ControlledAC, 13822, 24480, 11474);

	PENGINE pEngine = new ENGINE (pModel, ET_JET, 20475, 11750, 0.0000001,
								  _CurveRsc.FindCurve ("F86E", "JetMachFact"),
								  _CurveRsc.FindCurve ("F86E", "JetThrustRpm"),
								  _CurveRsc.FindCurve ("F86E", "JetWindMillDrag"),
								  _CurveRsc.FindCurve ("F86E", "JetWindMillRpm"));

	PTHRUSTPOINT pThrust = new THRUSTPOINT (pModel, TT_JET, 0, 0, -1050-CoG, 0, 0);
	
	pThrust->SetEngine (pEngine);
	pEngine->SetThrustPoint (pThrust);

	Coords3D w,c1,c2;
	FCRD CG;	//Relative to the centre of the shape

	CG.x = Model.ShapeCoG.x;
	CG.y = Model.ShapeCoG.y;
	CG.z = Model.ShapeCoG.z;

	SHAPE.GetContactPoint(ControlledAC, CT_EYE, w, c1, c2);
	Model.PilotEyePos.x = c1.X - CG.x;
	Model.PilotEyePos.y = c1.Y - CG.y;
	Model.PilotEyePos.z = c1.Z - CG.z;

	SHAPE.GetContactPoint(ControlledAC, CT_WHLFRONT, w, c1, c2);
	PGEAR pNose = new GEAR (pModel, NOSE);
	pNose->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pNose->SetSuspension (17250, 100000);
	pNose->SetTyres (0.02, 1, 0);

	SHAPE.GetContactPoint(ControlledAC, CT_WHLLEFT, w, c1, c2);
	PGEAR pMainPort = new GEAR (pModel, PORT);
	pMainPort->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pMainPort->SetSuspension (67500, 500000);
	pMainPort->SetTyres (0.02, 1, 12500);
	
	SHAPE.GetContactPoint(ControlledAC, CT_WHLRIGHT, w, c1, c2);
	PGEAR pMainStbd = new GEAR (pModel, STBD);
	pMainStbd->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pMainStbd->SetSuspension (67500, 500000);
	pMainStbd->SetTyres (0.02, 1, 12500);

	SHAPE.GetContactPoint(ControlledAC, CT_BACK, w, c1, c2);	//FAKE GEAR TO STOP TAIL HITTING GROUND
	PGEAR pTail = new GEAR (pModel, TAIL);
	pTail->SetDimensions (c1.X - CG.x, c1.Y - CG.y - 10, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pTail->SetSuspension (100000, 100000);
	pTail->SetTyres (0.1, 1, 0);


	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl, 32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator, 32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SUSPENSION, pNose, &adptr->aclegsuspf, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);

//DeadCode AMM 29Jun99 	Model.CoordRudder = 512;
	Model.PowerBoost = (FP)1.5;

//DeadCode AMM 29Jun99 	Model.ContrailBand = FEET2CM(10000);
	Model.ContrailDuration = 1.0;

	F80C_SetupAI(ControlledAC, Version);
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
//DeadCode CSB 10/12/98	//	ACM.RollRate_Aileron_Offset_Power = 12500;	// 25000 5/9/97
//DeadCode CSB 10/12/98		
//DeadCode CSB 10/12/98	//	ACM.Roll_Aileron_Offset_Power = 5000;
//DeadCode CSB 10/12/98	//	ACM.Roll_Aileron_MaxBankOffset_Power = 25000;
//DeadCode CSB 10/12/98		ACM.MaxAileron = 32767;
//DeadCode CSB 10/12/98	//	ACM.lastdeltaroll = 0;
//DeadCode CSB 10/12/98		
//DeadCode CSB 10/12/98	//	ACM.Heading_Aileron_Limit = DEGS2RADS(45);
//DeadCode CSB 10/12/98	//	ACM.Heading_Aileron_Offset_Power = 5000;
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



