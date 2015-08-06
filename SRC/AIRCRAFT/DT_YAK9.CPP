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
//Filename       YAK9.cpp
//System         
//Author         Andrew McRae
//Date           Tue 4 Feb 1997
//Description    Mustang
//------------------------------------------------------------------------------

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"


void YAK9_Setup (AirStrucPtr const ControlledAC, ULong Version)
{

	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;

	Model.Type = AT_YAK9;

	FP CoG = -352;//26%MAC

	PTHRUSTPOINT pThrust = new THRUSTPOINT (pModel, TT_PROP, 0, 0, -45-CoG, 0, 0);

	PMAINPLANE pMainPlane = new MAINPLANE (pModel, 45750, 230, 345, 40000, 165, 215);
	pMainPlane->SetPosition(140, -45, -350-CoG, 430, -20, -350-CoG);
	pMainPlane->SetOrientation (1, 0, 5, 1, 0, 5);
	pMainPlane->SetMaskAngle(0, 0, 0, 0);//-0.865, -1.089);//
	pMainPlane->SetDragPolar (0.0163, 0.0724);
	pMainPlane->SetCurves ("F80C", "Cl", "Cd", "CompCd0", "CompK", "Cm");
//DeadCode AMM 29Jun99 	pMainPlane->StallAoa = Degs2Rads(0);//22.5);
//DeadCode AMM 29Jun99 	pMainPlane->UnStallAoa = Degs2Rads(12.5);
	pMainPlane->dCMdq = 0;
	pMainPlane->dCMdp = 0;
	pMainPlane->dCMdr = -1;


	pMainPlane->SetSlipstream(pThrust, 50);
	

	pMainPlane->buffetAoa0 = Degs2Rads(15);	
	pMainPlane->buffetAoa1 = Degs2Rads(20);
	pMainPlane->buffetM0  = 0.95;	
	pMainPlane->buffetM1  = 1.05;	
	pMainPlane->ACMmaxaoa = Degs2Rads(17.5);


	PSURFACE pTailPlane1 = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 19000);//, 95);
	pTailPlane1->SetPosition (75, 30, -825-CoG);
	pTailPlane1->SetOrientation (0, 0, 0);
	pTailPlane1->SetMaskAngle(0, 0);
	pTailPlane1->SetCurves ("P51D", "TailCl", "COMM", "TailCd");//, "", "", "COMM", "CompK");
	pTailPlane1->SetSlipstream(pThrust, 50);//84);
	
	PSURFACE pTailPlane2 = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 19000);//, 95);
	pTailPlane2->SetPosition (-75, 30, -825-CoG);
	pTailPlane2->SetOrientation (0, 0, 0);
	pTailPlane2->SetMaskAngle(0, 0);
	pTailPlane2->SetCurves ("P51D", "TailCl", "COMM", "TailCd");//, "", "", "COMM", "CompK");
	pTailPlane2->SetSlipstream(pThrust, 50);//84);
	
	PSURFACE pFin = new SURFACE (pModel, ST_PLANE, SD_FIN, 20800);//, 135);
	pFin->SetPosition (0, 80, -875-CoG);
	pFin->SetOrientation (0, 0, -90);
	pFin->SetMaskAngle(0, 0);//-0.153);
	pFin->SetCurves ("P51D", "FinCl", "COMM", "TailCd");//, "", "", "COMM", "CompK");
	pFin->SetSlipstream(pThrust, 50);//90);		

	
	PCYLINDER pCylinder1 = new CYLINDER (pModel, 280, 85, 115);
	pCylinder1->SetPosition(0, 0, -150-CoG);
	pCylinder1->SetOrientation(0, 0, 0);

	PCYLINDER pCylinder2 = new CYLINDER (pModel, 305, 90, 165);
	pCylinder2->SetPosition(0, 0, -450-CoG);
	pCylinder2->SetOrientation(0, 0, 0);

	PCYLINDER pCylinder3 = new CYLINDER (pModel, 410, 50, 90);
	pCylinder3->SetPosition(0, 0, -775-CoG);
	pCylinder3->SetOrientation(0, 0, 0);

	
	new NEWCTRL (pMainPlane,  &Model.Aileron,  17.5, Degs2Rads(10), Degs2Rads(10) );
	new NEWCTRL (pTailPlane1, &Model.Elevator, 30, Degs2Rads(20), Degs2Rads(30) );
	new NEWCTRL (pTailPlane2, &Model.Elevator, 30, Degs2Rads(20), Degs2Rads(30) );
	new NEWCTRL (pFin,        &Model.Rudder,   40, Degs2Rads(30), Degs2Rads(30) );

	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_FLAPS, 0.75,  0.15, -0.25, DEGS2RADS(5), 256, FLAPSUPDOWN, &adptr->acflaps);//RJS 14May98
	new AERODEVICE (ControlledAC,pModel, AeroDevice::DT_GEAR,  0,    0.05, -0.01, 0, 4096/*128*/, GEARUPDOWN, NULL, 0);


	PENGINE pEngine = new ENGINE (pModel, ET_PISTON);
 	pEngine->RotateDirection = 1;			//Clockwise from behind
 	pEngine->IdleSpeed = RPM2RADSPERCSEC (500);
	pEngine->MoI = 64e6;
	pEngine->PropInertia.x = 10000000;
	pEngine->PropInertia.y = 10000000;
	pEngine->PropInertia.z = 20000000;
	pEngine->BladeRadius = 170;
	pEngine->BladeArea = 17000;	// 4x AR=5	//7771;
	pEngine->GearRatio = 0.479;
	pEngine->pPower100 = _CurveRsc.FindCurve ("YAK9", "Power100");
	pEngine->pPower0 = _CurveRsc.FindCurve ("F51D", "Power0");
	pEngine->pPowerAlt = _CurveRsc.FindCurve ("F51D", "PowerAlt");
	pEngine->pPowerAltSuper = _CurveRsc.FindCurve ("F51D", "PowerAltSuper");	//CSB
//DeadCode CSB 28/04/99		pEngine->pPropEff = _CurveRsc.FindCurve ("F51D", "PropEff");
//DeadCode CSB 28/04/99		pEngine->pPropTq = _CurveRsc.FindCurve ("F51D", "PropTq");
//DeadCode AMM 29Jun99 	pEngine->EngineCount = 1;
	pEngine->HighBlowerAlt = 457205;	//High Gear Supercharger cuts in at 15000ft //CSB
	pEngine->LowBlowerAlt  = 411485;	//High Gear Supercharger cuts out at 13500ft //CSB
	pEngine->BlowerHigh	   = FALSE;
	pEngine->p0 = 1590;
	pEngine->T100 = 1185000;
	
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

	SHAPE.GetContactPoint(ControlledAC, CT_WHLBACK, w, c1, c2);
	PGEAR pTail = new GEAR (pModel, TAIL);
	pTail->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pTail->SetSuspension (10000, 250000);
	pTail->SetTyres (0.02, 0.75, 0);

	SHAPE.GetContactPoint(ControlledAC, CT_WHLLEFT, w, c1, c2);
	PGEAR pMainPort = new GEAR (pModel, PORT);
	pMainPort->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pMainPort->SetSuspension (40000, 1000000);
	pMainPort->SetTyres (0.02, 0.75, 10000);
	
	SHAPE.GetContactPoint(ControlledAC, CT_WHLRIGHT, w, c1, c2);
	PGEAR pMainStbd = new GEAR (pModel, STBD);
	pMainStbd->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
	pMainStbd->SetSuspension (40000, 1000000);
	pMainStbd->SetTyres (0.02, 0.75, 10000);

	
	Model.ControlForce = 100;			// Relative amount of force feedback
	Model.BuffetForce  = 100; 

	pModel->SetMassInertias (ControlledAC, 0.75*26500, 0.75*36800, 0.75*11000);				//0.75 * F80
//DeadCode CSB 22/03/99		pModel->SetMassInertias (ControlledAC, 18460, 30000, 8100);		//Don't know
//DeadCode CSB 22/03/99		pModel->SetMassInertias (ControlledAC, 26500, 36800, 11000);	//F86E

	Model.MaxG = 9;
	Model.MinG = -5;

	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl,32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator,32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);
	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &ControlledAC->fly.rpm, &adptr->acrpm, 0, 65536);
//	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &pModel->Inst.Rpm1, &adptr->acrpm, 0, 65536);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pTail, &adptr->aclegsuspb, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);

//DeadCode AMM 29Jun99 	Model.CoordRudder = 768;
	Model.PowerBoost = 1.4;

//DeadCode AMM 29Jun99 	Model.ContrailBand = FEET2CM(10000);
	Model.ContrailDuration = 1.0;

	F51D_SetupAI (ControlledAC, Version);
}



