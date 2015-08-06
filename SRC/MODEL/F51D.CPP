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
//DeadCode ARM 03Nov97 //Filename       f51d.cpp
//DeadCode ARM 03Nov97 //System         
//DeadCode ARM 03Nov97 //Author         Andrew McRae
//DeadCode ARM 03Nov97 //Date           Tue 4 Feb 1997
//DeadCode ARM 03Nov97 //Description    Mustang
//DeadCode ARM 03Nov97 //------------------------------------------------------------------------------
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 #include "dosdefs.h"
//DeadCode ARM 03Nov97 #include "worldinc.h"
//DeadCode ARM 03Nov97 #include "modvec.h"
//DeadCode ARM 03Nov97 #include "model.h"
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 void F51D_Setup (AirStrucPtr const ControlledAC)
//DeadCode ARM 03Nov97 {
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	ClassPtr data = ControlledAC->classtype;
//DeadCode ARM 03Nov97 	PMODEL pModel = ControlledAC->fly.pModel;
//DeadCode ARM 03Nov97 	Model& Model = *ControlledAC->fly.pModel;
//DeadCode ARM 03Nov97 	ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;
//DeadCode ARM 03Nov97 	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	Model.Type = AT_F51D;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	PSURFACE pSurface;
//DeadCode ARM 03Nov97 	PMAINPLANE pMainPlane;
//DeadCode ARM 03Nov97 	PCTRL pCtrl;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 //TempCode ARM 29Oct97 	Model.pCdCurve = _CurveRsc.FindCurve ("F51D", "Cd");
//DeadCode ARM 03Nov97 //TempCode ARM 29Oct97 	Model.Area = 272102;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 //TempCode ARM 29Oct97 	Model.pCompCd = _CurveRsc.FindCurve ("F51D", "CompCd");
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	// root stbd wing
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface = new SURFACE (pModel,	ST_MAINPLANE, SD_INNERSTBDWING,	94004, 252.7, 1.0);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetPosition (186,0,0);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetOrientation (1,0,-5);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetCurves ("F51D", "Cl", "F51D", "Cd", "F51D", "Cm");
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	// root port wing
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface = new SURFACE (pModel, ST_MAINPLANE, SD_INNERPORTWING, 94004, 252.7, 1.0);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetPosition (-186,0,0);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetOrientation (1,0,5);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetCurves ("F51D", "Cl", "F51D", "Cd", "F51D", "Cm");
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	// tip stbd wing
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface = new SURFACE (pModel, ST_MAINPLANE, SD_OUTERSTBDWING, 42047, 171.2, 1.0);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetPosition (494.8,0,0);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetOrientation (0,0,-5);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetCurves ("F51D", "Cl", "F51D", "Cd", "F51D", "Cm");
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pCtrl = new CTRL (pSurface, CT_AERODYNAMIC, &Model.Aileron, 0x8001, 0x0000, 0x7fff, 0.35, 0, -0.35);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("COMM", "CtrlCl");
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	// tip port wing
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface = new SURFACE (pModel, ST_MAINPLANE, SD_OUTERPORTWING, 42047, 171.2, 1.0);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetPosition (-494.8,0,0);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetOrientation (0,0,5);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pSurface->SetCurves ("F51D", "Cl", "F51D", "Cd", "F51D", "Cm");
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pCtrl = new CTRL (pSurface, CT_AERODYNAMIC, &Model.Aileron, 0x8001, 0x0000, 0x7fff, -0.35, 0, 0.35);
//DeadCode ARM 03Nov97 //TempCode ARM 16Oct97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("COMM", "CtrlCl");
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	// stbd wing
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pSurface = new SURFACE (pModel, ST_MAINPLANE, SD_STBDWING, 108250, 192, 1.0);
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pSurface->SetPosition (235,0,0);
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pSurface->SetOrientation (0,0,-5);
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pSurface->SetCurves ("F51D", "Cl", "F51D", "Cd", "F51D", "Cm");
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pCtrl = new CTRL (pSurface, CT_AERODYNAMIC, &Model.Aileron, 0x8001, 0x0000, 0x7fff, 0.35, 0, -0.35);
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("COMM", "CtrlCl");
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	// port wing
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pSurface = new SURFACE (pModel, ST_MAINPLANE, SD_PORTWING, 108250, 192, 1.0);
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pSurface->SetPosition (-235,0,0);
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pSurface->SetOrientation (0,0,5);
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pSurface->SetCurves ("F51D", "Cl", "F51D", "Cd", "F51D", "Cm");
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pCtrl = new CTRL (pSurface, CT_AERODYNAMIC, &Model.Aileron, 0x8001, 0x0000, 0x7fff, -0.35, 0, 0.35);
//DeadCode ARM 03Nov97 //TempCode ARM 30Oct97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("COMM", "CtrlCl");
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	pMainPlane = new MAINPLANE (pModel, ST_DUALMAINPLANE, SD_MAINPLANE, 216500, 235, 192, 1.0);
//DeadCode ARM 03Nov97 	pMainPlane->SetOrientation (0, 0, -5);
//DeadCode ARM 03Nov97 	pMainPlane->SetCurves ("F15D", "Cl", "Cd", "CompCd", "Cm");
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// tail plane
//DeadCode ARM 03Nov97 	pSurface = new SURFACE (pModel, ST_PLANE, SD_TAILPLANE, 50437, 113.7, 3.5);
//DeadCode ARM 03Nov97 	pSurface->SetPosition (0,42,-540);
//DeadCode ARM 03Nov97 	pSurface->SetOrientation (-0.5,0,0);
//DeadCode ARM 03Nov97 	pSurface->LinPropWash = 30;
//DeadCode ARM 03Nov97 	pSurface->SetCurves ("F51D", "TailCl", "COMM", "TailCd", "", "");
//DeadCode ARM 03Nov97 	pCtrl = new CTRL (pSurface, CT_AERODYNAMIC, &Model.Elevator, 0x8001, 0x0000, 0x7fff, -0.8, 0, 0.8);
//DeadCode ARM 03Nov97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("COMM", "CtrlCl");
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// fin
//DeadCode ARM 03Nov97 	pSurface = new SURFACE (pModel, ST_PLANE, SD_FIN, 32517, 154.4, 2.0);
//DeadCode ARM 03Nov97 	pSurface->SetPosition (0,112,-632);
//DeadCode ARM 03Nov97 	pSurface->SetOrientation (0,0,-90);
//DeadCode ARM 03Nov97 	pSurface->RotPropWash = 0.02;
//DeadCode ARM 03Nov97 	pSurface->SetCurves ("F51D", "FinCl", "COMM", "TailCd", "", "");
//DeadCode ARM 03Nov97 	pCtrl = new CTRL (pSurface, CT_AERODYNAMIC, &Model.Rudder, 0x8001, 0x0000, 0x7fff, -1.6, 0, 1.6);
//DeadCode ARM 03Nov97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("COMM", "CtrlCl");
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SURFACE, pModel, &Model.Aileron, &adptr->acaileronr, 64);
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SURFACE, pModel, &Model.Aileron, &adptr->acaileronl, -64);
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SURFACE, pModel, &Model.Elevator, &adptr->acelevator, -64);
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SURFACE, pModel, &Model.Rudder, &adptr->acrudder, 64);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new AERODEVICE (pModel, AeroDevice::DT_FLAPS, 0.2, 0.005, -0.1, DEGS2RADS(4), 512, FLAPSUPDOWN, &adptr->acflaps, 64);
//DeadCode ARM 03Nov97 	new AERODEVICE (pModel, AeroDevice::DT_GEAR, 0, 0.007, -0.05, 0, 256, GEARUPDOWN, NULL, 0);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// mass
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	Model.Mass = 448000;
//DeadCode ARM 03Nov97 	pModel->SetupMassPoints (8000, 14000);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// Order specific
//DeadCode ARM 03Nov97 	// engine
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	PENGINE pEngine = new ENGINE (pModel, ET_PISTON);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// rating -	1490 bhp (metric) @ 3000 rpm 61" boost (takeoff)
//DeadCode ARM 03Nov97 	// max rpm 3240 (diving)
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// 61" boost
//DeadCode ARM 03Nov97 	// critical alt 21400 ft
//DeadCode ARM 03Nov97 	// 1370 bhp @ 3000 rpm
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97  	pEngine->IdleSpeed = RPM2RADSPERCSEC (500);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	pEngine->MoI = 32e6;
//DeadCode ARM 03Nov97 	pEngine->BladeRadius = 127.64;
//DeadCode ARM 03Nov97 	pEngine->BladeArea = 7771;
//DeadCode ARM 03Nov97 	pEngine->GearRatio = 0.479;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	pEngine->pPower100 = _CurveRsc.FindCurve ("F51D", "Power100");
//DeadCode ARM 03Nov97 	pEngine->pPower0 = _CurveRsc.FindCurve ("F51D", "Power0");
//DeadCode ARM 03Nov97 	pEngine->pPowerAlt = _CurveRsc.FindCurve ("F51D", "PowerAlt");
//DeadCode ARM 03Nov97 	pEngine->pPropEff = _CurveRsc.FindCurve ("F51D", "PropEff");
//DeadCode ARM 03Nov97 	pEngine->pPropTq = _CurveRsc.FindCurve ("F51D", "PropTq");
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new MODELANIM (MA_GENERICFP, pModel, &pModel->Inst.Rpm1, &adptr->acrpm, 2048);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// thrust
//DeadCode ARM 03Nov97 	PTHRUSTPOINT pThrust = new THRUSTPOINT (pModel, TT_PROP, 0,0,350, 0,0);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	pThrust->SetEngine (pEngine);
//DeadCode ARM 03Nov97 	pEngine->SetThrustPoint (pThrust);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// UnderCarriage
//DeadCode ARM 03Nov97 	// tail, port then stbd
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	PGEAR pGear;
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// tail
//DeadCode ARM 03Nov97 	pGear = new GEAR (pModel, TAIL);
//DeadCode ARM 03Nov97 	pGear->SetDimensions (0,-20,-500,0,0,-500);
//DeadCode ARM 03Nov97 	pGear->SetSuspension (0.96, 0.98 ,330);
//DeadCode ARM 03Nov97 	pGear->SetTyres (80, 2, 2, 500, 200, 5000);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SUSPENSION, pGear, &adptr->aclegsuspb, 0, 255);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// port
//DeadCode ARM 03Nov97 	pGear = new GEAR (pModel, PORT);
//DeadCode ARM 03Nov97 	pGear->SetDimensions (-150,-150,80,-150,-90,80);
//DeadCode ARM 03Nov97 //	pGear->SetSuspension (0.96, 0.98 ,487.5);
//DeadCode ARM 03Nov97 	pGear->SetSuspension (0.96, 0.98 ,700);
//DeadCode ARM 03Nov97 	pGear->SetTyres (80, 2, 2, 1500, 2000, 15000);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SUSPENSION, pGear, &adptr->aclegsuspl, 0, 255);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// stbd
//DeadCode ARM 03Nov97 	pGear = new GEAR (pModel, STBD);
//DeadCode ARM 03Nov97 	pGear->SetDimensions (150,-150,80,150,-90,80);
//DeadCode ARM 03Nov97 //	pGear->SetSuspension (0.96, 0.98 ,487.5);
//DeadCode ARM 03Nov97 	pGear->SetSuspension (0.96, 0.98 ,700);
//DeadCode ARM 03Nov97 	pGear->SetTyres (80, 2, 2, 1500, 2000, 15000);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	new MODELANIM (MA_SUSPENSION, pGear, &adptr->aclegsuspr, 0, 255);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	// Misc
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 	Model.CoordRudder = 768;
//DeadCode ARM 03Nov97 	Model.PowerBoost = (FP)1.4;
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
//DeadCode ARM 03Nov97 
