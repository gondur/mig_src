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

//DeadCode ARM 12Sep97 //------------------------------------------------------------------------------
//DeadCode ARM 12Sep97 //Filename       p51d.cpp
//DeadCode ARM 12Sep97 //System         
//DeadCode ARM 12Sep97 //Author         Andrew McRae
//DeadCode ARM 12Sep97 //Date           Tue 4 Feb 1997
//DeadCode ARM 12Sep97 //Description    Mustang
//DeadCode ARM 12Sep97 //------------------------------------------------------------------------------
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 #include "dosdefs.h"
//DeadCode ARM 12Sep97 #include "worldinc.h"
//DeadCode ARM 12Sep97 #include "modvec.h"
//DeadCode ARM 12Sep97 #include "model.h"
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 void P51D_Setup (AirStrucPtr const ControlledAC)
//DeadCode ARM 12Sep97 {
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	ClassPtr data = ControlledAC->classtype;
//DeadCode ARM 12Sep97 	PMODEL pModel = ControlledAC->fly.pModel;
//DeadCode ARM 12Sep97 	Model& Model = *ControlledAC->fly.pModel;
//DeadCode ARM 12Sep97 	ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;
//DeadCode ARM 12Sep97 	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	Model.Type = AT_P51D;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// ACM Model
//DeadCode ARM 12Sep97 	ACM.BrakePower = 8;
//DeadCode ARM 12Sep97 	ACM.SteerRatio = 8e-6;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// Misc
//DeadCode ARM 12Sep97 	Model.CoordRudder = 768;
//DeadCode ARM 12Sep97 	Model.PowerBoost = (FP)1.4;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	PELMT pElmt;
//DeadCode ARM 12Sep97 	PCTRL pCtrl;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// fuselage
//DeadCode ARM 12Sep97 //TempCode ARM 18Feb97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 //TempCode ARM 18Feb97 
//DeadCode ARM 12Sep97 //TempCode ARM 17Feb97 	pElmt->Type = AET_SURFACE;
//DeadCode ARM 12Sep97 //TempCode ARM 17Feb97 	pElmt->SurfaceType = AEST_CYLINDER;
//DeadCode ARM 12Sep97 //TempCode ARM 17Feb97 	pElmt->Area = 18000;
//DeadCode ARM 12Sep97 //TempCode ARM 17Feb97 	pElmt->SetPosition (0,80,0);
//DeadCode ARM 12Sep97 //TempCode ARM 17Feb97 	pElmt->SetOrientation (0,0,0);
//DeadCode ARM 12Sep97 //TempCode ARM 17Feb97 
//DeadCode ARM 12Sep97 //TempCode ARM 17Feb97 	pElmt->pClCurve = _CurveRsc.FindCurve ("P51D", "FuseCl");
//DeadCode ARM 12Sep97 //TempCode ARM 17Feb97 	pElmt->pCdCurve = _CurveRsc.FindCurve ("P51D", "FuseCd");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// root stbd wing
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->Type = AET_SURFACE;
//DeadCode ARM 12Sep97 	pElmt->SurfaceType = AEST_PLANE;
//DeadCode ARM 12Sep97 	pElmt->Area = 48000;
//DeadCode ARM 12Sep97 	pElmt->Chord = 180;
//DeadCode ARM 12Sep97 	pElmt->RotDamping = 1.0;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (250,0,0);
//DeadCode ARM 12Sep97 	pElmt->SetOrientation (1,0,-5);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->pClCurve = _CurveRsc.FindCurve ("P51D", "WingCl");
//DeadCode ARM 12Sep97 	pElmt->pCdCurve = _CurveRsc.FindCurve ("P51D", "WingCd");
//DeadCode ARM 12Sep97 	pElmt->pCmCurve = _CurveRsc.FindCurve ("P51D", "WingCm");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// tip stbd wing
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->Type = AET_SURFACE;
//DeadCode ARM 12Sep97 	pElmt->SurfaceType = AEST_PLANE;
//DeadCode ARM 12Sep97 	pElmt->Area = 32000;
//DeadCode ARM 12Sep97 	pElmt->Chord = 180;
//DeadCode ARM 12Sep97 	pElmt->RotDamping = 1.0;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (500,0,0);
//DeadCode ARM 12Sep97 	pElmt->SetOrientation (1,0,-5);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->pClCurve = _CurveRsc.FindCurve ("P51D", "WingCl");
//DeadCode ARM 12Sep97 	pElmt->pCdCurve = _CurveRsc.FindCurve ("P51D", "WingCd");
//DeadCode ARM 12Sep97 	pElmt->pCmCurve = _CurveRsc.FindCurve ("P51D", "WingCm");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pCtrl = new CTRL (pElmt, CT_AERODYNAMIC, &Model.Aileron, 0x8001, 0x0000, 0x7fff, 1, 0, -1);
//DeadCode ARM 12Sep97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("P51D", "CtrlCl");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// root port wing
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->Type = AET_SURFACE;
//DeadCode ARM 12Sep97 	pElmt->SurfaceType = AEST_PLANE;
//DeadCode ARM 12Sep97 	pElmt->Area = 48000;
//DeadCode ARM 12Sep97 	pElmt->Chord = 180;
//DeadCode ARM 12Sep97 	pElmt->RotDamping = 1.0;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (-250,0,0);
//DeadCode ARM 12Sep97 	pElmt->SetOrientation (1,0,5);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->pClCurve = _CurveRsc.FindCurve ("P51D", "WingCl");
//DeadCode ARM 12Sep97 	pElmt->pCdCurve = _CurveRsc.FindCurve ("P51D", "WingCd");
//DeadCode ARM 12Sep97 	pElmt->pCmCurve = _CurveRsc.FindCurve ("P51D", "WingCm");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// tip port wing
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->Type = AET_SURFACE;
//DeadCode ARM 12Sep97 	pElmt->SurfaceType = AEST_PLANE;
//DeadCode ARM 12Sep97 	pElmt->Area = 32000;
//DeadCode ARM 12Sep97 	pElmt->Chord = 180;
//DeadCode ARM 12Sep97 	pElmt->RotDamping = 1.0;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (-500,0,0);
//DeadCode ARM 12Sep97 	pElmt->SetOrientation (1,0,5);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->pClCurve = _CurveRsc.FindCurve ("P51D", "WingCl");
//DeadCode ARM 12Sep97 	pElmt->pCdCurve = _CurveRsc.FindCurve ("P51D", "WingCd");
//DeadCode ARM 12Sep97 	pElmt->pCmCurve = _CurveRsc.FindCurve ("P51D", "WingCm");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pCtrl = new CTRL (pElmt, CT_AERODYNAMIC, &Model.Aileron, 0x8001, 0x0000, 0x7fff, -1, 0, 1);
//DeadCode ARM 12Sep97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("P51D", "CtrlCl");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// tail plane
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->Type = AET_SURFACE;
//DeadCode ARM 12Sep97 	pElmt->SurfaceType = AEST_PLANE;
//DeadCode ARM 12Sep97 	pElmt->Area = 15000;
//DeadCode ARM 12Sep97 	pElmt->Chord = 100;
//DeadCode ARM 12Sep97 	pElmt->RotDamping = 1.0;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (0,100,-1500);
//DeadCode ARM 12Sep97 	pElmt->SetOrientation (-0.5,0,0);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->pClCurve = _CurveRsc.FindCurve ("P51D", "TailCl");
//DeadCode ARM 12Sep97 	pElmt->pCdCurve = _CurveRsc.FindCurve ("P51D", "TailCd");
//DeadCode ARM 12Sep97 	pElmt->pCmCurve = _CurveRsc.FindCurve ("P51D", "WingCm");
//DeadCode ARM 12Sep97 	pElmt->LinPropWash = 30;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pCtrl = new CTRL (pElmt, CT_AERODYNAMIC, &Model.Elevator, 0x8001, 0x0000, 0x7fff, -1.5, 0, 1.5);
//DeadCode ARM 12Sep97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("P51D", "CtrlCl");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// fin
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->Type = AET_SURFACE;
//DeadCode ARM 12Sep97 	pElmt->SurfaceType = AEST_PLANE;
//DeadCode ARM 12Sep97 	pElmt->Area = 20000;
//DeadCode ARM 12Sep97 	pElmt->Chord = 80;
//DeadCode ARM 12Sep97 	pElmt->RotDamping = 1.0;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (0,100,-2000);
//DeadCode ARM 12Sep97 	pElmt->SetOrientation (0,0,-90);
//DeadCode ARM 12Sep97 	pElmt->RotPropWash = 0.02;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pElmt->pClCurve = _CurveRsc.FindCurve ("P51D", "FinCl");
//DeadCode ARM 12Sep97 	pElmt->pCdCurve = _CurveRsc.FindCurve ("P51D", "FinCd");
//DeadCode ARM 12Sep97 	pElmt->pCmCurve = _CurveRsc.FindCurve ("P51D", "WingCm");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pCtrl = new CTRL (pElmt, CT_AERODYNAMIC, &Model.Rudder, 0x8001, 0x0000, 0x7fff, -1, 0, 1);
//DeadCode ARM 12Sep97 	pCtrl->pDeltaClCurve = _CurveRsc.FindCurve ("P51D", "CtrlCl");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// mass
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// aft
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 	pElmt->Type = AET_MASS;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (0,0,-225);
//DeadCode ARM 12Sep97 	pElmt->Mass = 150000;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// fwd
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 	pElmt->Type = AET_MASS;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (0,0,450);
//DeadCode ARM 12Sep97 	pElmt->Mass = 75000;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// stbd
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 	pElmt->Type = AET_MASS;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (250,0,0);
//DeadCode ARM 12Sep97 	pElmt->Mass = 50000;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// port
//DeadCode ARM 12Sep97 	pElmt = new ELMT (pModel);
//DeadCode ARM 12Sep97 	pElmt->Type = AET_MASS;
//DeadCode ARM 12Sep97 	pElmt->SetPosition (-250,0,0);
//DeadCode ARM 12Sep97 	pElmt->Mass = 50000;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// Order specific
//DeadCode ARM 12Sep97 	// engine
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	PENGINE pEngine = new ENGINE (pModel, ET_PISTON);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// rating - 1380 (metric assumption)bhp @ 3000 rpm
//DeadCode ARM 12Sep97 	// max torque is 597237.07 N.cm
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pEngine->IdleSpeed = RPM2RADSPERCSEC (250);
//DeadCode ARM 12Sep97 	pEngine->RatedSpeed = RPM2RADSPERCSEC (3000); // was 2700
//DeadCode ARM 12Sep97 	pEngine->RatedTorque = RATEDTORQUE (1380,3000);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pEngine->MoI = 8e6;//32e6;
//DeadCode ARM 12Sep97 	pEngine->BladeRadius = 117.3;
//DeadCode ARM 12Sep97 	pEngine->BladeArea = 7771;
//DeadCode ARM 12Sep97 	pEngine->GearRatio = 0.42;
//DeadCode ARM 12Sep97 	pEngine->PropInc = DEGS2RADS(14);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pEngine->pTorque100 = _CurveRsc.FindCurve ("P51D", "Torque100");
//DeadCode ARM 12Sep97 	pEngine->pTorque0 = _CurveRsc.FindCurve ("P51D", "Torque0");
//DeadCode ARM 12Sep97 	pEngine->pBladeCl = _CurveRsc.FindCurve ("P51D", "BladeCl");
//DeadCode ARM 12Sep97 	pEngine->pBladeCd = _CurveRsc.FindCurve ("P51D", "BladeCd");
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// could have min/max prop pitch curves indexed on Speed
//DeadCode ARM 12Sep97 	pEngine->MinPropInc = DEGS2RADS (1);
//DeadCode ARM 12Sep97 	pEngine->MaxPropInc = DEGS2RADS (35);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 	pEngine->ppBlades = new PELMT [4];
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 	pEngine->cBlades = 4;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 	for (ULong iBlade=0; iBlade<4; iBlade++)
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 	{
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		PELMT pBlade = new ELMT (pModel);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		pEngine->ppBlades[iBlade] = pBlade;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		pBlade->Type = AET_BLADE;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		pBlade->SurfaceType = AEST_PLANE;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		pBlade->Area = 3250;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		switch (iBlade)
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		{
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			// NOTE THESE ORIENTATIONS ARE RELATIVE
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			// TO AIRCRAFT COORDS
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			// NOT THRUST Z AXIS
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			// NOT TRUE IF ROTATED IN THRUST INIT BELOW
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			// THEN IS RELATIVE TO THRUST AXIS
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			// we wnat DefOri to be relative to aircrfat coords in the end
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			case 0:
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				pBlade->SetPosition (0,180,800);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				pBlade->SetOrientation (-90,0,-90);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				break;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			case 1:
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				pBlade->SetPosition (180,0,800);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				pBlade->SetOrientation (-90,0,0);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				break;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			case 2:
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				pBlade->SetPosition (0,-180,800);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				pBlade->SetOrientation (-90,0,90);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				break;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 			case 3:
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				pBlade->SetPosition (-180,0,800);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				pBlade->SetOrientation (-90,0,180);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 				break;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		}
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		pBlade->pClCurve = _CurveRsc.FindCurve ("P51D", "BladeCl");
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		pBlade->pCdCurve = _CurveRsc.FindCurve ("P51D", "BladeCd");
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		pCtrl = new CTRL (pBlade, CT_ROTATION, &pEngine->CtrlPropInc, DEGS2ROWAN(0), DEGS2ROWAN(90), 0, 90);
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 		pBlade->pEngine = pEngine;
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 
//DeadCode ARM 12Sep97 //TempCode ARM 19Mar97 	}
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// thrust
//DeadCode ARM 12Sep97 	PELMT pThrust = new ELMT (pModel);
//DeadCode ARM 12Sep97 	pThrust->Type = AET_THRUST;
//DeadCode ARM 12Sep97 	pThrust->ThrustType = AETT_PROP;
//DeadCode ARM 12Sep97 	pThrust->SetPosition (0,0,-500);
//DeadCode ARM 12Sep97 	pThrust->SetOrientation (0,0,0);
//DeadCode ARM 12Sep97 	pThrust->pEngine = pEngine;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// SHOULD ROTATE BLADE DefOris BY THIS THRUST Z AXIS
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	pEngine->ThrustElmt = pThrust;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// UnderCarriage
//DeadCode ARM 12Sep97 	// tail, port then stbd
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	PGEAR pGear;
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// nose
//DeadCode ARM 12Sep97 	pGear = new GEAR (pModel, TAIL);
//DeadCode ARM 12Sep97 //	pGear->SetParams (100,220,500);
//DeadCode ARM 12Sep97 	pGear->SetDimensions (0,-80,-500,0,-40,-500);
//DeadCode ARM 12Sep97 	pGear->SetSuspension (0.96, 0.98 ,330);
//DeadCode ARM 12Sep97 	pGear->SetTyres (80, 2, 2, 500, 200, 5000); 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// port
//DeadCode ARM 12Sep97 	pGear = new GEAR (pModel, PORT);
//DeadCode ARM 12Sep97 //	pGear->SetParams (200,487.5,1000);
//DeadCode ARM 12Sep97 	pGear->SetDimensions (-150,-150,90,-150,-60,90);
//DeadCode ARM 12Sep97 	pGear->SetSuspension (0.96, 0.98 ,487.5);
//DeadCode ARM 12Sep97 	pGear->SetTyres (80, 2, 2, 1500, 2000, 15000); 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 	// stbd
//DeadCode ARM 12Sep97 	pGear = new GEAR (pModel, STBD);
//DeadCode ARM 12Sep97 //	pGear->SetParams (200,487.5,1000);
//DeadCode ARM 12Sep97 	pGear->SetDimensions (150,-150,90,150,-60,90);
//DeadCode ARM 12Sep97 	pGear->SetSuspension (0.96, 0.98 ,487.5);
//DeadCode ARM 12Sep97 	pGear->SetTyres (80, 2, 2, 1500, 2000, 15000); 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 }
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
