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
//Filename       mig15.cpp
//System         
//Author         Andrew McRae
//Date           Wed 29 Jan 1997
//Description    F86E Sabre flight data
//------------------------------------------------------------------------------

#include "dosdefs.h"
#include "worldinc.h"
#include "3DCom.h"
#include "modvec.h"
#include "model.h"

void MIG15_Setup (AirStrucPtr const ControlledAC, ULong Version)
{
	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;

	switch (Version)
	{
		case 1:	
			Model.Type = AT_MIG15;
			break;
		case 2:
			Model.Type = AT_MIG15BIS;
			break;
	}

	SWord CoG = -388;//484;	//Max 388 (Wing 26%MAC)
	PMAINPLANE pMainPlane = new MAINPLANE (pModel, 71000, 240, 390, 32000, 190, 220);
	pMainPlane->SetPosition(125, 0, -330-CoG, 370, -15, -510-CoG);
	pMainPlane->SetOrientation (0.75, 0, -3, 0.75, 0, -3);		//IGNORE SWEEP
	pMainPlane->SetMaskAngle(0, 0, 0, 0);//-0.534, -0.666, 50, 50);//
	pMainPlane->SetDragPolar (0.0175, 0.0825);

	pMainPlane->SetCurves ("MIG15", "Cl", "Cd", "CompCd0", "CompK", "Cm");
	pMainPlane->dCMdq = 0;//-0.01;//
	pMainPlane->dCMdp = 0;
	pMainPlane->dCMdr = 0;
//DeadCode AMM 29Jun99 	pMainPlane->StallAoa   = Degs2Rads(0);//20.5);//
//DeadCode AMM 29Jun99 	pMainPlane->UnStallAoa = Degs2Rads(10.0);

	pMainPlane->buffetAoa0 = Degs2Rads(13);
	pMainPlane->buffetAoa1 = Degs2Rads(17.5);
	pMainPlane->buffetM0  = 0.8;	
	pMainPlane->buffetM1  = 1.0;	
	pMainPlane->ACMmaxaoa = Degs2Rads(15);


	PSURFACE pTailPlane1 = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 15000);//, 110);
	pTailPlane1->SetPosition (55, 175, -875-CoG);
	pTailPlane1->SetOrientation (0, 0, 0);
	pTailPlane1->SetMaskAngle(0, 0);//-0.675, 50);//
	pTailPlane1->SetCurves ("MIG15", "TailCl", "COMM", "TailCd");//, "", "", "COMM", "CompK");

	PSURFACE pTailPlane2 = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 15000);//, 110);
	pTailPlane2->SetPosition (-55, 175, -875-CoG);
	pTailPlane2->SetOrientation (0, 0, 0);
	pTailPlane2->SetMaskAngle(0, 0);//0.675, 50);//
	pTailPlane2->SetCurves ("MIG15", "TailCl", "COMM", "TailCd");//, "", "", "COMM", "CompK");

	PSURFACE pFin = new SURFACE (pModel, ST_PLANE, SD_FIN, 40000);//40000);//, 260);
	pFin->SetPosition (0, 100, -730-CoG);
	pFin->SetOrientation (0, 0, -90);
	pFin->SetMaskAngle(0, 0);//-0.207, 50);//-0.1, 100);//
	pFin->SetCurves ("MIG15", "FinCl", "COMM", "TailCd");//, "", "", "COMM", "CompK");


	PCYLINDER pCylinder1 = new CYLINDER (pModel, 275, 135, 145);
	pCylinder1->SetPosition(0, 0, -135-CoG);
	pCylinder1->SetOrientation (0, 0, 0);

	PCYLINDER pCylinder2 = new CYLINDER (pModel, 275, 145, 145);
	pCylinder2->SetPosition(0, 0, -410-CoG);
	pCylinder2->SetOrientation (0, 0, 0);

	PCYLINDER pCylinder3 = new CYLINDER (pModel, 275, 115, 115);
	pCylinder3->SetPosition(0, 0, -685-CoG);
	pCylinder3->SetOrientation (0, 0, 0);


	new NEWCTRL (pMainPlane,  &Model.Aileron,  17.5, Degs2Rads(15), Degs2Rads(15) );
	new NEWCTRL (pTailPlane1, &Model.Elevator, 30, Degs2Rads(16), Degs2Rads(32) );
	new NEWCTRL (pTailPlane2, &Model.Elevator, 30, Degs2Rads(16), Degs2Rads(32) );
	new NEWCTRL (pFin,        &Model.Rudder,   25, Degs2Rads(20), Degs2Rads(20) );

//DeadCode AMM 29Jun99 	Model.ControlPower		= 0.5;
//DeadCode AMM 29Jun99 	Model.ControlResistance = 0.0;
	Model.MControlLoss0		= 0.3;
	Model.MControlLoss1		= 0.9;

	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_FLAPS, 0.5, 0.15, -0.25, DEGS2RADS(2.5), 256, FLAPSUPDOWN, &adptr->acflaps);//RJS 14May98
	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_SPEEDBRAKES, 0, 0.05, 0, 0, 256, SPEEDBRAKE, &adptr->acbreak);//RJS 14May98
	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_GEAR,  -0.1,   0.04, -0.01, 0, /*35*/128, GEARUPDOWN, NULL, 0);


	PENGINE pEngine;
	switch (Version)
	{
		case 1:
			pEngine = new ENGINE (pModel, ET_JET, 22269, 11500, 0.00000005,
								  _CurveRsc.FindCurve ("MIG15", "JetMachFact"),
								  _CurveRsc.FindCurve ("F86E", "JetThrustRpm"),
								  _CurveRsc.FindCurve ("F86E", "JetWindMillDrag"),
								  _CurveRsc.FindCurve ("F86E", "JetWindMillRpm"));
			break;
		case 2:
			pEngine = new ENGINE (pModel, ET_JET, 26476, 11500, 0.00000005,
								  _CurveRsc.FindCurve ("MIG15", "JetMachFact"),
								  _CurveRsc.FindCurve ("F86E", "JetThrustRpm"),
								  _CurveRsc.FindCurve ("F86E", "JetWindMillDrag"),
								  _CurveRsc.FindCurve ("F86E", "JetWindMillRpm"));
			break;
	}

	PTHRUSTPOINT pThrust = new THRUSTPOINT (pModel, TT_JET, 0, 0, -1110-CoG, 0,0);
	
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
	pNose->SetSuspension (15000, 100000);
	pNose->SetTyres (0.02, 1, 0);

	SHAPE.GetContactPoint(ControlledAC, CT_WHLLEFT, w, c1, c2);
	PGEAR pMainPort = new GEAR (pModel, PORT);
	pMainPort->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pMainPort->SetSuspension (55000, 500000);
	pMainPort->SetTyres (0.02, 1, 12500);
	
	SHAPE.GetContactPoint(ControlledAC, CT_WHLRIGHT, w, c1, c2);
	PGEAR pMainStbd = new GEAR (pModel, STBD);
	pMainStbd->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pMainStbd->SetSuspension (55000, 500000);
	pMainStbd->SetTyres (0.02, 1, 12500);

	SHAPE.GetContactPoint(ControlledAC, CT_BACK, w, c1, c2);	//FAKE GEAR TO STOP TAIL HITTING GROUND
	PGEAR pTail = new GEAR (pModel, TAIL);
	pTail->SetDimensions (c1.X - CG.x, c1.Y - CG.y - 10, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pTail->SetSuspension (100000, 100000);
	pTail->SetTyres (0.1, 1, 0);

	
//DeadCode CSB 07/06/99		pModel->SetMassInertias (ControlledAC, 0.7*19500, 0.7*26250, 0.7*8000);
//DeadCode CSB 06/07/99		pModel->SetMassInertias (ControlledAC, 9750,	15250,	5750);
	pModel->SetMassInertias (ControlledAC, 7862, 10539, 4675);
										 

	Model.MaxG = 9;
	Model.MinG = -5;

//DeadCode CSB 04/03/99		Model.PilotEyePos.x = 0;
//DeadCode CSB 04/03/99		Model.PilotEyePos.y = 90;
//DeadCode CSB 04/03/99		Model.PilotEyePos.z = -205-CoG;

	Model.ControlForce = 100;			// Relative amount of force feedback
	Model.BuffetForce  = 100; 

//DeadCode AMM 29Jun99 	Model.CoordRudder = 512;
	Model.PowerBoost = (FP)1.25;

//DeadCode AMM 29Jun99 	Model.ContrailBand = FEET2CM(10000);
	Model.ContrailDuration = 1.0;

	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl, 32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator, 32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SUSPENSION, pNose, &adptr->aclegsuspf, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);

	
	Mig15_SetupAI(ControlledAC, Version);
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
//DeadCode CSB 10/12/98	//	ACM.Heading_Aileron_Offset_Power = 5000;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//	ACM.PitchRate_Elevator_Offset_Power = 2048;
//DeadCode CSB 10/12/98	//	ACM.PitchRate_Elevator_Damping_Power = 262144;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//DeadCode RDH 17Apr98 	ACM.Pitch_Elevator_Offset_Power = 2048;//8;//2048;
//DeadCode CSB 10/12/98	//DeadCode RDH 17Apr98 	ACM.Pitch_Elevator_Damping_Power = 262144;//1024;//262144;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98		ACM.DeltaPitchForMaxElevator	= 1.0472;
//DeadCode CSB 10/12/98		ACM.MaxElevatorForTightTurn	= 32767;
//DeadCode CSB 10/12/98	//	ACM.DiffPitchForMaxElevator	= 0.1745;
//DeadCode CSB 10/12/98		ACM.lastdeltapitch = 0;
//DeadCode CSB 10/12/98		ACM.deltapitchsum = 0;
//DeadCode CSB 10/12/98		ACM.deltayawsum = 0;
//DeadCode CSB 10/12/98			ACM.yawmodifier = 6;//8;	//10;		//12;	
//DeadCode CSB 10/12/98		ACM.yawintmodifier = 3;		//0.5;		//1.5;		//0.25;
//DeadCode CSB 10/12/98		ACM.turnmodifier = 0.8;//1;	//1.3;		//1.3;	//2.2;		//1.3;			//2;
//DeadCode CSB 10/12/98		ACM.turnintmodifier = 10;	//2		;//2.2;		//3.3;		//1.8;		//1.5;
//DeadCode CSB 10/12/98		ACM.rollmodifier = 0.3;//0.8;			//0.4;
//DeadCode CSB 10/12/98		ACM.pitchratemodifier = 100000;
//DeadCode CSB 10/12/98		ACM.aoamodifier = 1000;		//1000;
//DeadCode CSB 10/12/98		ACM.pitchmodifier = 1;
//DeadCode CSB 10/12/98		ACM.pitchintmodifier = 1.5;
//DeadCode CSB 10/12/98		ACM.liftmodifier = 1000;			//1000; 
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98		ACM.deltarollsum = 0;
//DeadCode CSB 10/12/98		ACM.rollintmodifier = 2;
//DeadCode CSB 10/12/98		ACM.IntRollForMaxAileron = 80;
//DeadCode CSB 10/12/98		ACM.IntPitchForMaxElevator	= 1000;
//DeadCode CSB 10/12/98		ACM.maxdeltaforclosework = 0;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//	ACM.Speed_Throttle_Offset_Power = 0.5;
//DeadCode CSB 10/12/98	//	ACM.Speed_Throttle_Damping_Power = 64;
//DeadCode CSB 10/12/98	
//DeadCode CSB 10/12/98	//DeadCode CSB 06/11/98		Model.ClAileronLoss = 1.50;
//DeadCode CSB 10/12/98		Model.MElevatorLoss = 0.95;	
//DeadCode CSB 10/12/98		
//DeadCode CSB 10/12/98	}
