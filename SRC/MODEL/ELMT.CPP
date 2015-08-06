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
//Filename       elmt.cpp
//System         
//Author         Andrew McRae
//Date           Thu 24 Apr 1997
//Description    Aircraft Element Module
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
#include "replay.h"

#define	CylinderCD 0.75
#define EasyModel (!Save_Data.flightdifficulty[FD_SPINS])
#define IsPlayer  (Manual_Pilot.ControlledAC2 == ControlledAC)
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Process
//Author		Andrew McRae			Craig Beeston
//Date			Fri 17 Oct 1997			Fri 6 Nov 1998
//
//Description	This calculates the forces and moments acting on the wings of the aircraft
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MainPlane::Process (AirStrucPtr const ControlledAC)
{
	Bool BUFFET_ON = TRUE;

//DeadCode CSB 26/02/99	 	PCTRL pCtrl;

	if(!(pModel->FrameCount & EVERY8cs) || (pModel->FirstCycle) )
	{
		if(pCompCd0Curve != NULL) fCd0Mach = pCompCd0Curve->GetValue (pModel->Inst.MachNo);
		if(pCompKCurve != NULL)   fKMach   = pCompKCurve->GetValue (pModel->Inst.MachNo);
	
//Buffet Boundaries at aircraft mach number
		FP _buffetM0 = buffetM0;
		FP _buffetM1 = buffetM1;
		if(Save_Data.flightdifficulty[FD_POWERBOOST])
		{
			_buffetM0 *= 1.414213562;	// sqrt(2)
			_buffetM1 *= 1.414213562;
		}

		BuffetAoaMin = pModel->Inst.MachNo / _buffetM0;
		BuffetAoaMin = BuffetAoaMin * BuffetAoaMin * BuffetAoaMin * BuffetAoaMin;	// (M/M0)^4
		BuffetAoaMin = buffetAoa0 * (1 - BuffetAoaMin);	// Cl(Min) = Cl0 * (1-(M/M0)^4)
		if(BuffetAoaMin < 0) BuffetAoaMin = 0;
		
		BuffetAoaMax = pModel->Inst.MachNo / _buffetM1;
		BuffetAoaMax = BuffetAoaMax * BuffetAoaMax * BuffetAoaMax * BuffetAoaMax;	// (M/M1)^4
		BuffetAoaMax = buffetAoa1 * (1 - BuffetAoaMax);	// Cl(Max) = Cl1 * (1-(M/M1)^4)
		if(BuffetAoaMax < 0) BuffetAoaMax = 0;
	}

////////////////////////////////////////////////////////////////////////////////////////
	for(SWord wing = 0; wing < 2; wing++)						//[0]Stbd,    [1]Port
		for(SWord section = 0; section < 2; section++)			//[0]Inboard, [1]Outboard
		{
			Bool TIP_STALL = FALSE;
			FCRD Vel;			//Movement of wings due to rotation of Aircraft
			FCRD AirVelAc;		//Local air speed in aircraft coordinates
			FCRD AirVelEl;		//Local air speed in wing element coordinates
			FP	 airspeed;		//Total air speed
			FP	 Aoa;			//Angle of attack
			FP	 Cl, Cd, Cmx, Cmy, Cmz;//Coefficients of Lift, Drag, Pitching moment, Yawing moment, Rolling
			FP	 dAoa, dCl, dCd, dCm;	//Increase in Aoa/coefficients due to control surface deflection
			FP	 DynPressSF;	//Local dynamic pressure times area times maskingfactor
			FP	 fMasking;		//Factor to account for wing masked by fuselage
			FP	 lift, drag, momX, momY, momZ;	
			FCRD Lift, Drag, Mom;

			CPrd(Vel, Pos[wing][section], pModel->RotVel);
			SubVec(AirVelAc, pModel->AirVel, Vel);

			if((IsPlayer) && (Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS]) && (pSlipThrustPoint != NULL) && (section == 0) )
				if(pSlipThrustPoint->pEngine->Type == ET_PISTON)
				{
					FCRD dist;
					FCRD SlipstreamVel;
					FCRD SlipstreamRot;	
	
					SubVec(dist, Pos[wing][section], pSlipThrustPoint->Pos);	

					SlipstreamRot.x = 0;
					SlipstreamRot.y = 0;
					SlipstreamRot.z = pSlipThrustPoint->pEngine->SlipRot;	
					SlipstreamRot.z *= pSlipThrustPoint->pEngine->RotateDirection;	

					CPrd (SlipstreamVel, dist, SlipstreamRot);
					SlipstreamVel.z = -pSlipThrustPoint->pEngine->SlipVel;

					FP slip_fact = pSlipThrustPoint->pEngine->PropVel / pSlipThrustPoint->pEngine->SlipVel;
//DEADCODE DAW 14/06/99 PrintVar(70, 24, "SF: %.2f ", slip_fact);
					FP slip_area = 0.01 * AmountInSlipstream * FSqrt(slip_fact);
					if(slip_area > 1) slip_area = 1;
//DeadCode CSB 31/05/99						FP slip_area = 0.01 * AmountInSlipstream;
			
					SlipstreamVel.x *= 1;
					SlipstreamVel.y *= 1;

					AirVelAc.x += slip_area * SlipstreamVel.x;
					AirVelAc.y += slip_area * SlipstreamVel.y;
					AirVelAc.z =  slip_area * SlipstreamVel.z + (1 - slip_area) * AirVelAc.z;
				}

			TnsAxs(AirVelAc, AirVelEl, Ori[wing][section]);

			airspeed = VecLen  (AirVelEl);
			FP AirVelHori = VecLen2D(AirVelEl.x, AirVelEl.z);
			if(AirVelEl.z > 0) AirVelHori *= -1;
			Aoa		 = AngleSign( CalcAngle(AirVelHori, AirVelEl.y) );	

			if((IsPlayer) && (!EasyModel))
				if((section == 1) && ((pModel->Type == AT_MIG15) || (pModel->Type == AT_MIG15BIS)) )
					if((pModel->Pos.y < 300000) && (pModel->Speed > 285))
						if(Aoa > aoa[1-wing][1])		//This wing at higher aoa than other wing
							TIP_STALL = TRUE;

					
			Cl = Cd = Cmx = Cmy = Cmz = 0.0;
			dAoa = dCl = dCd = dCm    = 0.0;

//Flaps etc.
			if(section == 0)
			{
				dAoa = pModel->DeltaAlpha;
				dCl  = pModel->DeltaCl;
				dCd  = pModel->DeltaCd;
				dCm  = pModel->DeltaCm;
			}

//Ailerons
			else if ((pNewCtrls != NULL) && (!TIP_STALL))
				{
					if (wing == 0) pNewCtrls->Process(dAoa, dCl, TRUE);
					if (wing == 1) pNewCtrls->Process(dAoa, dCl, FALSE);
					
					if(Aoa * dAoa < 0)
					{
						FP factor = Aoa;
						if(factor < 0) factor *= -1;

						for(;;)
						{
							if(factor < Degs2Rads(15) )
							{
								factor = 1;
								break;
							}
							if(factor > Degs2Rads(22.5) )
							{
								factor = 0;
								break;
							}
							factor = (factor - Degs2Rads(15) ) / Degs2Rads(22.5 - 15);
							factor = 1 - factor * factor;
							break;
						}
						dAoa *= factor;
						dCl  *= factor;
					}
				}

			if(TIP_STALL)
			{
				dAoa = 0;
				dCl  = 0;
				dCm  = 0;
//DeadCode CSB 28/04/99	PrintString(0, 2, "TIP_STALL");
			}
//DeadCode CSB 28/04/99	else PrintString(0, 2, "        ");


			if(AirVelEl.z > 0) 
			{
				dAoa *= -1;
				dCl	  =  0;
				dCm	  =  0;
			}
			Aoa += dAoa;

			if (pClCurve != NULL) Cl = pClCurve->GetValue(Aoa);
			Cl += dCl;

			if ((Aoa > AoaMin) && (Aoa < AoaMax))
				Cd = Cdo * fCd0Mach + (k * Cl * Cl) * fKMach;
			else
			{
				if (pCdCurve != NULL)
				{
					Cd = pCdCurve->GetValue(Aoa);
					FP KCl2 = Cd - Cdo;
					Cd = Cdo * fCd0Mach + KCl2 * fKMach;
				}
			}
			Cd += dCd;

/* TEST CODE CSB 08/06/99 */			
//DeadCode CSB 08/06/99				if((IsPlayer) && (!EasyModel) && (pCmCurve != NULL)) Cmx = pCmCurve->GetValue (Aoa);	//Fix This !!!!
/* TEST CODE CSB 08/06/99 */			

			//DeadCode CSB 17/05/99				if((!IsPlayer) && 
//DeadCode CSB 17/05/99					((pModel->Type == AT_F86A)  || (pModel->Type == AT_F86E) || (pModel->Type == AT_F86F) ||
//DeadCode CSB 17/05/99					 (pModel->Type == AT_MIG15) || (pModel->Type == AT_MIG15BIS)) )
//DeadCode CSB 17/05/99					Cmx = 0;
			
			Cmx += dCm;
			
			if(TIP_STALL)
			{
				Cl *= 0.8;
				Cd *= 1.1;
			}

			FP AbsAoa = Aoa;
			if(AbsAoa < 0) AbsAoa *= -1;

//@@			if( (StallAoa > 0) && (AbsAoa > StallAoa) )
//@@				stalled[wing][section] = TRUE;
//@@			
//@@			if(stalled[wing][section])
//@@			{
//@@				if(Aoa > 0)
//@@				{
//@@					if(Aoa < UnStallAoa) stalled[wing][section] = FALSE;
//@@					if( (Aoa > UnStallAoa) && (Aoa < StallAoa) )
//@@					{
//@@						FP CL0 = pClCurve->GetValue(UnStallAoa);
//@@						FP CL1 = pClCurve->GetValue(StallAoa);
//@@						Cl = CL0 + (CL1 - CL0) * (Aoa - UnStallAoa) / (StallAoa - UnStallAoa);
//@@
//@@//DeadCode CSB 29/01/99							FP CD0 = pCdCurve->GetValue(UnStallAoa);
//@@//DeadCode CSB 29/01/99							FP CD1 = pCdCurve->GetValue(StallAoa);
//@@//DeadCode CSB 29/01/99							Cd = CD0 + (CD1 - CD0) * (Aoa - UnStallAoa) / (StallAoa - UnStallAoa);
//@@//DeadCode CSB 29/01/99							FP KCl2 = Cd - Cdo;
//@@//DeadCode CSB 29/01/99							Cd = Cdo * fCd0Mach + KCl2 * fKMach;
//@@						Cd = pCdCurve->GetValue(StallAoa);
//@@
//@@//DeadCode CSB 29/01/99							FP CM0 = pCmCurve->GetValue(UnStallAoa);
//@@//DeadCode CSB 29/01/99							FP CM1 = pCmCurve->GetValue(StallAoa);
//@@//DeadCode CSB 29/01/99							Cmx = CM0 + (CM1 - CM0) * (Aoa - UnStallAoa) / (StallAoa - UnStallAoa);
//@@						Cmx = pCmCurve->GetValue(StallAoa);
//@@					}
//@@				}
//@@				else
//@@				{
//@@					if(Aoa > -UnStallAoa) stalled[wing][section] = FALSE;
//@@					if( (Aoa < -UnStallAoa) && (Aoa > -StallAoa) )
//@@					{
//@@						FP CL0 = pClCurve->GetValue(-UnStallAoa);
//@@						FP CL1 = pClCurve->GetValue(-StallAoa);
//@@						Cl = CL0 + (CL1 - CL0) * (-Aoa - UnStallAoa) / (StallAoa - UnStallAoa);
//@@
//@@//DeadCode CSB 29/01/99							FP CD0 = pCdCurve->GetValue(UnStallAoa);
//@@//DeadCode CSB 29/01/99							FP CD1 = pCdCurve->GetValue(StallAoa);
//@@//DeadCode CSB 29/01/99							Cd = CD0 + (CD1 - CD0) * (-Aoa - UnStallAoa) / (StallAoa - UnStallAoa);
//@@//DeadCode CSB 29/01/99							FP KCl2 = Cd - Cdo;
//@@//DeadCode CSB 29/01/99							Cd = Cdo * fCd0Mach + KCl2 * fKMach;
//@@						Cd = pCdCurve->GetValue(-StallAoa);
//@@
//@@//DeadCode CSB 29/01/99							FP CM0 = pCmCurve->GetValue(UnStallAoa);
//@@//DeadCode CSB 29/01/99							FP CM1 = pCmCurve->GetValue(StallAoa);
//@@//DeadCode CSB 29/01/99							Cmx = CM0 + (CM1 - CM0) * (-Aoa - UnStallAoa) / (StallAoa - UnStallAoa);
//@@						Cmx = pCmCurve->GetValue(-StallAoa);
//@@					}
//@@				}
//@@			}


//Buffet
			FP BuffetIntensity = 0.0;	
		
			if ( (!pModel->bACM) && (BUFFET_ON) )
				if(AbsAoa < BuffetAoaMin)		BuffetIntensity = 0.0;
				else if(AbsAoa > BuffetAoaMax) 	BuffetIntensity = 1.0;
				else 
					BuffetIntensity = (AbsAoa - BuffetAoaMin) / (BuffetAoaMax - BuffetAoaMin);
//DeadCode CSB 26/02/99						PrintVar (12 - (1-2*wing)*(1+section)*5, 24, "%.2f", BuffetIntensity);

			pModel->TotalBuffet += BuffetIntensity;// * BuffetIntensity;




			FCRD ExtraDamping;
			NullVec(ExtraDamping);

			if(IsPlayer)
			{
				if((EasyModel) || (Key_Tests.KeyHeld3d (SPINRECOVERY)))
				{
					ExtraDamping.x += -5.0;
					ExtraDamping.y += -0.5;
					ExtraDamping.z += -0.5;
				}
			}
			else
				if((pModel->Type == AT_F51D) || (pModel->Type == AT_YAK9))
				{
//DeadCode CSB 29/06/99						ExtraDamping.x += -5.0;
					ExtraDamping.y += -1;
//DeadCode CSB 29/06/99						ExtraDamping.z += -0.5;
				}

			if(airspeed > 0)
			{
				FP One_Over_2v = 1 / (2 * airspeed);
				Cmx += (dCMdq + ExtraDamping.x) * pModel->RotVel.x * Chord * One_Over_2v;	//CSB 09/12/98	Pitch Rate
				Cmy  = (dCMdr + ExtraDamping.y) * pModel->RotVel.y * Span  * One_Over_2v;	//CSB 10/12/98	Roll Rate
				Cmz  = (dCMdp + ExtraDamping.z) * pModel->RotVel.z * Span  * One_Over_2v;	//CSB 10/12/98	Yaw Rate
			}

//Ground Effect		//CSB	//20/8/98
			if( (pModel->Pos.y - pModel->GroundHeight) < 2000)
			{
				FP HeightAboveGround  =  pModel->Pos.y - pModel->GroundHeight;
				HeightAboveGround *= 0.01;	//metres
				FP GroundEffectFactor =  0.56142 - 0.056142 * HeightAboveGround 
										 + 0.00140355 * HeightAboveGround * HeightAboveGround;
				GroundEffectFactor    /= 2.5 + HeightAboveGround;
				Cl *= 1 + GroundEffectFactor;
			}


//Fuselage masking inboard wing due to sideslip
//@@			if( (section == 0) && (MaskAngle[wing][section] != 0.0) )	//Inboard section only
//@@			{
//@@				FP sideslip = CalcAngle(-AirVelEl.z, -AirVelEl.x);
//@@				sideslip = AngleSign(sideslip);
//@@				fMasking = sideslip / MaskAngle[wing][section];
//@@				MODMAXMIN(fMasking, 0, 1);
//@@				if(fMasking > 0)
//@@					fMasking = 1 - MaskArea[wing][section] * 0.01 * fMasking;
//@@				else fMasking = 1.0;
//@@			}
//@@			else 
//@@				fMasking = 1.0;


			if(section == 0)
				DownWashAng[wing] = 2 * Cl / (FPIE * (FP)Span / (FP)Chord);

//Calculate Forces and Moments

			DynPressSF = 0.5 * pModel->AmbDensity * airspeed * airspeed * wArea[section];// * fMasking;
			lift = Cl * DynPressSF;
			drag = Cd * DynPressSF;
			momX = Cmx * DynPressSF * wChord[section];
			momY = Cmy * DynPressSF * wSpan[section];
			momZ = Cmz * DynPressSF * wSpan[section];


			if(!IsPlayer)
			{
				FP	FightingFactor = (FP)ControlledAC->FlyingFactor() / 256;
				lift *= 0.5 + 0.75 * FightingFactor * FightingFactor * FightingFactor;

//DeadCode CSB 14/06/99					if 	(FightingFactor < 128)
//DeadCode CSB 14/06/99						FightingFactor = 128;
//DeadCode CSB 14/06/99					FP LiftInc = (FightingFactor - 192)/128;
//DeadCode CSB 14/06/99					LiftInc =  1.5 * LiftInc;
//DeadCode CSB 14/06/99					lift *= (1 + LiftInc);
			}


//Implement the effects of damage
			AircraftAnimData*	adptr;
			adptr = (AircraftAnimData *)ControlledAC->Anim;

			FP fDamage;
			if( (wing == 0) && (section == 0) )	fDamage = adptr->RIGHTWINGIN;	//Stbd Inn
			if( (wing == 0) && (section == 1) )	fDamage = adptr->RIGHTWINGOUT;	//Stbd Out
			if( (wing == 1) && (section == 0) )	fDamage = adptr->LEFTWINGIN;	//Port Inn
			if( (wing == 1) && (section == 1) )	fDamage = adptr->LEFTWINGOUT;	//Port Out
	
			if(fDamage == BS_DEAD) 
			{
				lift = 0;
				drag = 0;
				momX = 0;
				momY = 0;
				momZ = 0;
			} 
			else if(fDamage)
			{
				fDamage =  fDamage / 512;
				lift    *= 1 - fDamage;
				drag    *= 1 + fDamage;
				momX    *= 1 - fDamage;
				momY    *= 1 - fDamage;
				momZ    *= 1 - fDamage;
			}

// calc direction of Force & moment

			CPrd(Lift, AirVelAc, Ori[wing][section].y);	//Lift = Line within XZ plane of wing, perpendicular to flow
			CPrd(Lift, Lift, AirVelAc);					//Lift = Perpendicular to flow with components in x and z
			NrmVec(Lift, Lift);

			Lift.x *= lift;
			Lift.y *= lift;
			Lift.z *= lift;
			NrmVec(AirVelAc, Drag);

			Drag.x *= drag;
			Drag.y *= drag;
			Drag.z *= drag;

			AddVec(eForce[wing][section], Lift, Drag);

			Mom.x = momX;
			Mom.y = momY;
			Mom.z = momZ;

//DeadCode CSB 16/02/99	NullVec(Mom);	//fix this !!!!

			TnsPnt(Mom, eMoment[wing][section], Ori[wing][section]);

			aoa[wing][section] = Aoa;
		}	//Next Section
			//Next Wing

//DeadCode DAW 11Mar99 	if	((	aoa[1][1] > Degs2Rads(22.5)) || (aoa[0][1] > Degs2Rads(22.5)) )
//DeadCode DAW 11Mar99 		if( (pModel->RotVel.y > 0.0025) || (pModel->RotVel.y < -0.0025) )
//DeadCode DAW 11Mar99 			pModel->Spinning = TRUE;
//it would be handy if you could keep the indentations the same	//DAW 11Mar99

	if(!EasyModel)
		if	(	( (aoa[1][1] > Degs2Rads(22.5)) || (aoa[0][1] > Degs2Rads(22.5)) )	//RDH 01/03/99
			&&	( (pModel->RotVel.y > 0.0025) || (pModel->RotVel.y < -0.0025) )		//RDH 01/03/99
			)																		//RDH 01/03/99
			{																		//RDH 01/03/99
				if  (		(Manual_Pilot.ControlledAC2 == ControlledAC)			//RDH 01/03/99
						&&	(pModel->Spinning == FALSE)				  //RDH 01/03/99
					)												  //RDH 01/03/99
					_Miles.SequenceAudible(FIL_MUSIC_SPIRALLING);	  //RDH 01/03/99
				pModel->Spinning = TRUE;							  //RDH 01/03/99
			}else													  //RDH 01/03/99
			{
				if  (		(Manual_Pilot.ControlledAC2 == ControlledAC)			//RDH 01/03/99
						&&	(pModel->Spinning == TRUE)				  //RDH 01/03/99
					)												  //RDH 01/03/99
					_Miles.SequenceMute(500);						  //RJS 18/06/99
				pModel->Spinning = FALSE;							  //RDH 01/03/99
			}

}


 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSurface
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calculates Force and moment produced by this surface.
//				Force & moment are in aircraft coords
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Surface::Process (AirStrucPtr const ControlledAC)
{
	FCRD Vel;
	FCRD AirVel;
	FCRD AcAirVel;

	FP Cl,Cd;//,Cm;
	FP aoa;

	FCRD Lift;
	FCRD Drag;
 
	// Process Rotation Controls
 
 	PCTRL pCtrl;
 	
	// calc element vel relative to aircraft cg
	CPrd (Vel, Pos, pModel->RotVel);

	FCRD localairvec;

	localairvec.x = pModel->AirVel.x;
	localairvec.y = pModel->AirVel.y;
	localairvec.z = pModel->AirVel.z;

//Effect of Downwash on TailPlane
	if(pModel->MainPlaneList != NULL)	//fix this !!!!
	{
		if(Pos.x > 0) localairvec.y += localairvec.z * pModel->MainPlaneList->DownWashAng[0];
		if(Pos.x < 0) localairvec.y += localairvec.z * pModel->MainPlaneList->DownWashAng[1];
	}

	// calc air speed of surface (ac coords)
	SubVec (AcAirVel, localairvec, Vel);

//Propellor SlipStream
	if( (Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS]) && (pSlipThrustPoint != NULL) )
		for(;;)
		{
			if(pSlipThrustPoint->pEngine->Type != ET_PISTON) break;
			
			FCRD dist;
			FCRD SlipstreamVel;
			FCRD SlipstreamRot;	
	
			SubVec(dist, Pos, pSlipThrustPoint->Pos);	

			SlipstreamRot.x = 0;
			SlipstreamRot.y = 0;
			SlipstreamRot.z = pSlipThrustPoint->pEngine->SlipRot;	
			SlipstreamRot.z *= pSlipThrustPoint->pEngine->RotateDirection;	

			CPrd (SlipstreamVel, dist, SlipstreamRot);
			SlipstreamVel.z = -pSlipThrustPoint->pEngine->SlipVel;

			FP slip_fact = pSlipThrustPoint->pEngine->PropVel / pSlipThrustPoint->pEngine->SlipVel;
			FP slip_area = 0.01 * AmountInSlipstream * FSqrt(slip_fact);
			if(slip_area > 1) slip_area = 1;
			
			SlipstreamVel.x *= 1;
			SlipstreamVel.y *= 1;

			AcAirVel.x += slip_area * SlipstreamVel.x;
			AcAirVel.y += slip_area * SlipstreamVel.y;
			AcAirVel.z =  slip_area * SlipstreamVel.z + (1 - slip_area) * AcAirVel.z;

			break;
		}

	// rotate into element coords
	TnsAxs (AcAirVel, AirVel, Ori);

	FCRD LocalRotVel;
	TnsAxs(pModel->RotVel, LocalRotVel, Ori);

	
	// calc airvel & aoa
	FP airspeed; // wrt element shape


	airspeed = VecLen(AirVel);
	FP AirVelHori = VecLen2D(AirVel.z, AirVel.x);
	if(AirVel.z > 0) AirVelHori *= -1;
	aoa = AngleSign( CalcAngle( AirVelHori, AirVel.y) );

	Cl = Cd = 0.0;// Cm = 0.0;

	FP dCl  = 0.0;
	FP dAoa = 0.0;

	SWord TempRudder   = pModel->Rudder;
	SWord TempElevator = pModel->Elevator;

	if(Desc == SD_FIN)
		pModel->Rudder = (FP)pModel->Rudder * (1 - pModel->Inst.MachNo * pModel->Inst.MachNo);

//DeadCode CSB 28/04/99		PrintString (0, 20, "        "); 
	if(	(Save_Data.flightdifficulty[FD_SPINS]) && (pModel->Spinning) )
		for(;;)
		{
//DeadCode CSB 28/04/99				PrintString (0, 20, "**SPIN**"); 
			if(pModel->Type == AT_MIG15)
			{
//DeadCode CSB 27/04/99					pModel->Elevator = -32767;
//DeadCode CSB 27/04/99					if(TempElevator > 0) pModel->Elevator += TempElevator / 3;
//DeadCode CSB 08/06/99					if(pModel->RotVel.y > 0) pModel->Rudder = -16383 + pModel->Rudder / 2;
				pModel->Elevator = -16384 + pModel->Elevator / 4;
				pModel->Rudder   = pModel->Rudder / 3;
				break;
			}
			if(pModel->Type == AT_F80C)
			{
				pModel->Elevator = -8192 + (3 * pModel->Elevator) / 4;
//DeadCode CSB 08/06/99					pModel->Rudder   = pModel->Rudder;
				break;
			}
			if(pModel->Type == AT_F84E)
			{
				pModel->Elevator = -16384 + pModel->Elevator / 2;
//DeadCode CSB 08/06/99					pModel->Rudder   = pModel->Rudder;
				break;
			}
			if((pModel->Type == AT_F86A) || (pModel->Type == AT_F86E) || (pModel->Type == AT_F86F))
			{
				pModel->Elevator = -16384 + pModel->Elevator / 2;
//DeadCode CSB 08/06/99					pModel->Rudder   = pModel->Rudder;
				break;
			}
			break;
		}
	if (pNewCtrls != NULL)
		pNewCtrls->Process (dAoa, dCl, FALSE);
	
	pModel->Rudder   = TempRudder;
	pModel->Elevator = TempElevator;

	if(aoa * dAoa < 0)
	{
		FP factor = aoa;
		if(factor < 0) factor *= -1;

		for(;;)
		{
			if(factor < Degs2Rads(15) )
			{
				factor = 1;
				break;
			}
			if(factor > Degs2Rads(22.5) )
			{
				factor = 0;
				break;
			}
			factor = (factor - Degs2Rads(15) ) / Degs2Rads(22.5 - 15);
			factor = 1 - factor * factor;
			break;
		}
		dAoa *= factor;
		dCl  *= factor;
	}
					

	if(AirVel.z > 0) 
	{
		dAoa *= -1;
		dCl   =  0;
	}

	aoa += dAoa;

// calc Cl, Cd & Cm
	if (pClCurve != NULL)  Cl = pClCurve->GetValue (aoa);
//DeadCode CSB 13/07/99		else
//DeadCode CSB 13/07/99			FP DoNothingForABreakpoint5 = 0.0;

	Cl += dCl;

	if (pCdCurve != NULL)  Cd = pCdCurve->GetValue (aoa);
//DeadCode CSB 13/07/99		else
//DeadCode CSB 13/07/99			FP DoNothingForABreakpoint6 = 0.0;

//DeadCode CSB 25/02/99		if (pCdMCurve != NULL) Cd *= pCdMCurve->GetValue (pModel->Inst.MachNo);
//DeadCode CSB 25/02/99		else
//DeadCode CSB 25/02/99			FP DoNothingForABreakpoint7 = 0.0;
//DeadCode CSB 25/02/99	
//DeadCode CSB 25/02/99		if (pCmCurve != NULL) Cm = pCmCurve->GetValue (aoa);


	// Compressibilty Drag

//	Cd *= pModel->pCompCd->GetValue (pModel->Inst.MachNo);
	FP fMasking = 1.0;
	if(MaskAngle != 0.0)
	{
		FP sideslip = CalcAngle(-AirVel.z, -AirVel.x);
		sideslip = AngleSign(sideslip);
		fMasking = sideslip / MaskAngle;
		MODMAXMIN(fMasking, 0, 1);
		if(fMasking > 0)
			fMasking = 1 - MaskArea * 0.01 * fMasking;
		else fMasking = 1.0;
	}

//DeadCode CSB 26/02/99	if(!pModel->bACM)
//DeadCode CSB 26/02/99	{
//DeadCode CSB 26/02/99		if(Pos.x == 0)
//DeadCode CSB 26/02/99			PrintVar (65, 17, "%.3f", fMasking);
//DeadCode CSB 26/02/99		if(Pos.x < 0) 
//DeadCode CSB 26/02/99			PrintVar (60, 16, "%.3f", fMasking);
//DeadCode CSB 26/02/99		if(Pos.x > 0) 
//DeadCode CSB 26/02/99			PrintVar (70, 16, "%.3f", fMasking);
//DeadCode CSB 26/02/99	}

	// calc lift, drag & moment
	FP dynpres = 0.5 * pModel->AmbDensity * airspeed * airspeed;// * fMasking;

//DeadCode CSB 07/06/99		FP fTurbulence = (4.0 - pModel->TotalBuffet) / 4.0;

	FP lift   = Cl * dynpres * Area;// * fTurbulence;
	FP drag   = Cd * dynpres * Area;// * fTurbulence;
//DeadCode CSB 25/02/99		FP moment = Cm * dynpres * Area * Chord;

// calc direction of Force & moment

	//implement damage 
	AircraftAnimData*	adptr;
	adptr = (AircraftAnimData *)ControlledAC->Anim;

	FP fDamage;
	if(Desc == SD_FIN)			fDamage = adptr->FIN;
	if(Desc == SD_TAILPLANE)	fDamage = adptr->TAIL;

	if(fDamage == BS_DEAD) 
	{
		lift = 0;
		drag = 0;
	} 
	else if(fDamage)
	{
		fDamage =  fDamage / 512;
		lift    *= 1 - fDamage;
		drag    *= 1 + fDamage;
	}

	CPrd(Lift, AcAirVel, Ori.y);	//Lift = Line within XZ plane of wing, perpendicular to flow
	CPrd(Lift, Lift, AcAirVel);		//Lift = Perpendicular to flow with components in x and z
	NrmVec(Lift, Lift);

	Lift.x *= lift;
	Lift.y *= lift;
	Lift.z *= lift;

	NrmVec (AcAirVel, Drag);	//CSB 10/12/98
	Drag.x *= drag;
	Drag.y *= drag;
	Drag.z *= drag;
	

	Force.x = Lift.x + Drag.x;
	Force.y = Lift.y + Drag.y;
	Force.z = Lift.z + Drag.z;

//DeadCode CSB 25/02/99		Moment.x = moment;
//DeadCode CSB 25/02/99		Moment.y = 0;
//DeadCode CSB 25/02/99		Moment.z = 0;
//DeadCode CSB 25/02/99	
//DeadCode CSB 25/02/99		TnsPnt(Moment, Moment, Ori);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessCylinder
//Author		Craig Beeston
//Date			Thu 05 Nov 1998
//
//Description	Calculates Force produced by this cylinder.
//				Force & moment are in aircraft coords
//				//Note - Cylinders are always along the z-axis of the aircraft. (Fuselages)
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Cylinder::Process (AirStrucPtr const ControlledAC)
{
	CPrd(Vel, Pos, pModel->RotVel);
	FCRD AirVelAC, AirVelEl;
	SubVec (AirVelAC, pModel->AirVel, Vel);

	TnsAxs(AirVelAC, AirVelEl, Ori);

	FP airspeed = VecLen (AirVelEl);
	
	FP HalfRhoLCd = 0.5 * pModel->AmbDensity * Length * CylinderCD * airspeed; 

	Force.x = HalfRhoLCd * DiameterY * AirVelEl.x;

	Force.y = HalfRhoLCd * DiameterX * AirVelEl.y;
	
	Force.z = 0;

	TnsPnt(Force, Force, Ori);
}

// KEEP THIS

//TempCode ARM 19Mar97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode ARM 19Mar97 //Procedure		ProcessBlade
//TempCode ARM 19Mar97 //Author		Andrew McRae
//TempCode ARM 19Mar97 //Date			Mon 13 Jan 1997
//TempCode ARM 19Mar97 //
//TempCode ARM 19Mar97 //Description	Processes a propeller blade
//TempCode ARM 19Mar97 //
//TempCode ARM 19Mar97 //Inputs		
//TempCode ARM 19Mar97 //
//TempCode ARM 19Mar97 //Returns	
//TempCode ARM 19Mar97 //
//TempCode ARM 19Mar97 //------------------------------------------------------------------------------
//TempCode ARM 19Mar97 void AircraftElement::ProcessBlade ()
//TempCode ARM 19Mar97 {
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	if (SurfaceType != AEST_PLANE) return;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// Process Rotation Controls
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	PCTRL pCtrl;
//TempCode ARM 19Mar97 	
//TempCode ARM 19Mar97 	pCtrl = pCtrls;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	for (;;)
//TempCode ARM 19Mar97 	{
//TempCode ARM 19Mar97 		if (pCtrl == NULL)
//TempCode ARM 19Mar97 			break;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 		if (pCtrl->Type == CT_ROTATION)
//TempCode ARM 19Mar97 			pCtrl->ProcessRotation ();
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 		pCtrl = pCtrl->List.NextItem();
//TempCode ARM 19Mar97 	}
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// calc element vel relative to aircraft cg
//TempCode ARM 19Mar97 	// due to aircraft rotation
//TempCode ARM 19Mar97 	CPrd (Vel, Pos, pModel->RotVel);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// Add speed of rotation
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	FCRD vel;	// due to engine rotation
//TempCode ARM 19Mar97 	CPrd (vel, Pos, pEngine->ThrustElmt->Ori.z);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	FP propspeed = pEngine->Speed * pEngine->GearRatio;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	vel.x *= pEngine->Speed;
//TempCode ARM 19Mar97 	vel.y *= pEngine->Speed;
//TempCode ARM 19Mar97 	vel.z *= pEngine->Speed;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	AddVec (Vel, Vel, vel);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// calc air speed of surface (ac coords)
//TempCode ARM 19Mar97 	SubVec (AcAirVel, pModel->AirVel, Vel);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// rotate into element coords
//TempCode ARM 19Mar97 	TnsAxs (AcAirVel, AirVel, Ori);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// calc airvel & aoa
//TempCode ARM 19Mar97 	FP airvel; // wrt element shape
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	airvel = VecLen2D (AirVel.z, AirVel.y);
//TempCode ARM 19Mar97 	aoa = CalcAngle (-AirVel.z, AirVel.y);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// calc Cl, Cd & Cm
//TempCode ARM 19Mar97 	Cl = pClCurve->GetValue (aoa);
//TempCode ARM 19Mar97 	Cd = pCdCurve->GetValue (aoa);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// calc lift, drag & moment
//TempCode ARM 19Mar97 	DynPres = 0.5 * pModel->AmbDensity * airvel * airvel;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	FP Lift = Cl * DynPres * Area;
//TempCode ARM 19Mar97 	FP Drag = Cd * DynPres * Area;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// calc direction of Force & moment
//TempCode ARM 19Mar97 	FCRD LiftVec;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	CPrd (LiftVec, Ori.x, AcAirVel);
//TempCode ARM 19Mar97 	NrmVec (LiftVec, LiftVec);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	LiftVec.x *= Lift;
//TempCode ARM 19Mar97 	LiftVec.y *= Lift;
//TempCode ARM 19Mar97 	LiftVec.z *= Lift;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	FCRD DragVec;
//TempCode ARM 19Mar97 	NrmVec (AcAirVel, DragVec);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	DragVec.x *= Drag;
//TempCode ARM 19Mar97 	DragVec.y *= Drag;
//TempCode ARM 19Mar97 	DragVec.z *= Drag;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	Force.x = LiftVec.x + DragVec.x;
//TempCode ARM 19Mar97 	Force.y = LiftVec.y + DragVec.y;
//TempCode ARM 19Mar97 	Force.z = LiftVec.z + DragVec.z;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	Moment.x = 0;
//TempCode ARM 19Mar97 	Moment.y = 0;
//TempCode ARM 19Mar97 	Moment.z = 0;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// Resolve Force in Blade DefOri.z axis to get load torque
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	// Remove this from Force
//TempCode ARM 19Mar97 	// (as no load torque passes to airframe from the prop)
//TempCode ARM 19Mar97 	// (but does pass to the engine)
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	FCRD bladeforce;	// Force relative to plane of rotation of the prop
//TempCode ARM 19Mar97 						// at position of this blade
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	TnsAxs (Force, bladeforce, DefOri);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	LoadTorque = bladeforce.z * pEngine->BladeRadius;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	bladeforce.z = 0;
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 	TnsPnt (bladeforce, Force, DefOri);
//TempCode ARM 19Mar97 
//TempCode ARM 19Mar97 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessThrust
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Actions a thrust force into the model
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThrustPoint::Process ()
{
	switch (Type)
	{
		case TT_JET:
			Force.x = Vec.x * pEngine->Thrust;
			Force.y = Vec.y * pEngine->Thrust;
			Force.z = Vec.z * pEngine->Thrust;
			NullVec (Moment);
			break;

		case TT_PROP:
			Force.x = Vec.x * pEngine->Thrust;
			Force.y = Vec.y * pEngine->Thrust;
			Force.z = Vec.z * pEngine->Thrust;
//TempCode RDH 10Sep98 			if (Save_Data.flightdifficulty [FD_TORQUEEFFECTS])
			if( (Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS]) && (pEngine->Type == ET_PISTON) )
			{
				Moment.x = Vec.x * pEngine->Torque;
				Moment.y = Vec.y * pEngine->Torque;
				Moment.z = Vec.z * pEngine->Torque;

				AddVec(Moment, Moment, pEngine->moment);
			}
 			else
				NullVec (Moment);
			break;
	}
}



//DeadCode CSB 26/02/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 26/02/99	//Procedure		Process
//DeadCode CSB 26/02/99	//Author		Andrew McRae
//DeadCode CSB 26/02/99	//Date			Fri 31 Oct 1997
//DeadCode CSB 26/02/99	//
//DeadCode CSB 26/02/99	//Description	
//DeadCode CSB 26/02/99	//
//DeadCode CSB 26/02/99	//Inputs		
//DeadCode CSB 26/02/99	//
//DeadCode CSB 26/02/99	//Returns	
//DeadCode CSB 26/02/99	//
//DeadCode CSB 26/02/99	//------------------------------------------------------------------------------
//DeadCode CSB 26/02/99	void AeroCtrl::Process ()
//DeadCode CSB 26/02/99	{
//DeadCode CSB 26/02/99		*Output += ((FP)*Ctrl * scaler * pModel->DynamicPressure);
//DeadCode CSB 26/02/99	}
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 26/02/99	//Procedure		Process
//DeadCode CSB 26/02/99	//Author		Andrew McRae
//DeadCode CSB 26/02/99	//Date			Fri 31 Oct 1997
//DeadCode CSB 26/02/99	//
//DeadCode CSB 26/02/99	//Description	
//DeadCode CSB 26/02/99	//
//DeadCode CSB 26/02/99	//Inputs		
//DeadCode CSB 26/02/99	//
//DeadCode CSB 26/02/99	//Returns	
//DeadCode CSB 26/02/99	//
//DeadCode CSB 26/02/99	//------------------------------------------------------------------------------
//DeadCode CSB 26/02/99	void AeroCouple::Process ()
//DeadCode CSB 26/02/99	{
//DeadCode CSB 26/02/99		*pDest += (*pSrce * scaler * pModel->DynamicPressure);
//DeadCode CSB 26/02/99	}

