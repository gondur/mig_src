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
//Filename       dervs.cpp
//System         
//Author         Andrew McRae
//Date           Tue 17 Jun 1997
//Description    
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
#include "time.h"
#include "myerror.h"
#include "monotxt.h"
#include "savegame.h"
//DeadCode RJS 02Dec97 #include "3dcom.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DerivativeBase
//Author		Andrew McRae
//Date			Tue 17 Jun 1997
//
//Description	Used to calibrate model with linearized
//				stability derivatives
//
//				This model is aerodynamically accurate
//				for small disturbances from level flight.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::DerivativeBase ()
{

/*

	Stability Derivatives

	Forces X,Y,Z
	Moments L,M,N

	Velocity u,v,w
	Angular Velocity p,q,r
	Roll, Pitch, Yaw inputs a,b,c
	Downward Acceleration wd (za)

	(r = density)
	(everything has 0.5)

	Forces									Moments

	Forward		Stbd		Down			Roll		Pitch		Yaw

	Xu	rVS		Yu	...		Zu	rVS			Lu	...		Mu	rVSc	Nu	...
	Xv	...		Yv	rVS		Zv	...			Lv	rVSb	Mv	...		Nv	rVSb
	Xw	rVS		Yw	...		Zw	rVS			Lw	...		Mw	rVSc	Nw	...

	Xp	...		Yp	rVSb	Zp	...			Lp	rVSb2	Mp	...		Np	rVSb2
	Xq	rVSc	Yq	...		Zq	rVSc		Lq	...		Mq	rVSc2	Nq	...
	Xr	...		Yr	rVSb	Zr	...			Lr	rVSb2	Mr	...		Nr	rVSb2

	Xa	...		Ya	rV2S	Za	...			La	rV2Sb	Ma	...		Na	rV2Sb
	Xb	rV2S	Yb	...		Zb	rV2S		Lb	...		Mb	rV2Sc	Nb	...
	Xc	...		Yc	rV2S	Zc	...			Lc	rV2Sb	Mc	...		Nc	rV2Sb

	Xwd	rSc		Ywd	...		Zwd	rSc			Lwd	...		Mwd	rSc2	Nwd	...

*/

	typedef struct vel { FP u,v,w; } VEL;
	typedef struct rotvel { FP p,q,r; } ROTVEL;
	typedef struct ctrl { FP a,b,c; } CTRL;
	typedef struct acc { FP ud,vd,wd; } ACC;

	typedef struct veldervs { VEL X,Y,Z,L,M,N; } VELDERVS;
	typedef struct rotveldervs { ROTVEL X,Y,Z,L,M,N; } ROTVELDERVS;
	typedef struct ctrldervs { CTRL X,Y,Z,L,M,N; } CTRLDERVS;
	typedef struct accdervs { ACC X,Y,Z,L,M,N; } ACCDERVS;

	VELDERVS V;
	ROTVELDERVS RV;
	CTRLDERVS C;
	ACCDERVS A;

	MODEL_DT = 3;
	MODEL_LOOPS = 1;

	static Bool setup = TRUE;

	FP testalpha = -Degs2Rads ((FP)Elevator / 3000);
	if (testalpha > DEGS2RADS(10)) testalpha = DEGS2RADS(10);
	if (testalpha < DEGS2RADS(-10)) testalpha = DEGS2RADS(-10);

	if (setup)
	{

		// temp
		Pos.y = FT_3000;

		Vel.x = 0;
		Vel.y = 0;
		Vel.z = 150;

		Ori.x.x = 1;
		Ori.x.y = 0;
		Ori.x.z = 0;
		Ori.y.x = 0;
		Ori.y.y = 1;
		Ori.y.z = 0;
		Ori.z.x = 0;
		Ori.z.y = 0;
		Ori.z.z = 1;

//		RotOriXVec (Ori, testalpha);

//		RotOriXVec (Ori, DEGS2RADS(5));
		RotOriYVec (Ori, DEGS2RADS(10));

		RotVel.x = 0;
		RotVel.y = 0;
		RotVel.z = 0;

		RotVel.y = 0.00105;	// 1 rpm
		RotVel.z = -0.00105;

		// temp end
		setup = FALSE;
	}

//	UpdateAirStruc ();

	Sky.Ambient (Pos.y, AmbDensity, AmbTemp, AmbPres);

	CalcAirVel ();

	GearTouched = FALSE;

	// Set Mass and Rot Inertia
	Mass = 0;
	NullVec (RotInertia);
	PMODEL pModel = ControlledAC->fly.pModel;

	PMASSPOINT pMass = MassList;
	while (pMass != NULL)
	{
		pMass->Process (pModel);
		pMass = pMass->List.NextItem ();
	}

//	ProcessEngines ();

	Mass = 617415;
	RotInertia.x = 1.49534e10;
	RotInertia.y = 3.59877e10;
	RotInertia.z = 4.98958e10;

	// WORK IN STANDARD UNITS

	// Calc Derivative Mutipliers
	FP B = (MainPlaneList->Area / MainPlaneList->Chord) * 0.01;
	FP Ch = MainPlaneList->Chord * 0.01;

	FP rS = 0.5 * (AmbDensity * 10000) * (MainPlaneList->Area * 0.0001);

	FP rVS = rS * AirSpeed;
	FP rVSb = rVS * B;
	FP rVSc = rVS * Ch;
	FP rVSb2 = rVSb * B;
	FP rVSc2 = rVSc * Ch;

	FP rV2S = rVS * AirSpeed;
	FP rV2Sb = rV2S * B;
	FP rV2Sc = rV2S * Ch;

	FP rSc = rS * Ch;
	FP rSc2 = rSc * Ch;

	// Get derivative inputs

	// Velocities
	FP u = -AirVel.z;
	FP v = -AirVel.x;
	FP w = AirVel.y;

	// Rotational velocities
	FP p = RotVel.z * 100;
	FP q = RotVel.x * 100;
	FP r = -RotVel.y * 100;

	// Calc Control inputs
	FP a = -((FP)Aileron * F2PIE * 20) / (32768 * 360);
	FP b = ((FP)Elevator * F2PIE * 20) / (32768 * 360);
	FP c = -((FP)Rudder * F2PIE * 20) / (32768 * 360);

	// Acceleration
	FP ud = 0;
	FP vd = 0;
	FP wd = 0;


	// Calc alpha
	FP alpha = CalcAngle (VecLen2D (u,v), w);
	if (alpha > DEGS2RADS(180)) alpha -= DEGS2RADS(360);
	alpha += DEGS2RADS (3);

//	alpha = testalpha;

//	if (alpha > DEGS2RADS(10)) alpha = DEGS2RADS(10);
//	if (alpha < DEGS2RADS(-10)) alpha = DEGS2RADS(-10);

	FP Sin = FSin (alpha);
	FP Cos = FCos (alpha);

	// Calc Cl, Cd

	FP Cl = alpha * 5.27;
	FP Cd = alpha * 0.29;

#ifdef PRINT_DERV_DATA
	PrintVar (30, 16, "alp %.2f  ", Rads2Degs(alpha));
	PrintVar (45, 16, "Cl %.2f  ", Cl);
	PrintVar (60, 16, "Cd %.2f  ", Cd);

	PrintVar (30, 18, "u %.4f  ", u);
	PrintVar (45, 18, "v %.4f  ", v);
	PrintVar (60, 18, "w %.4f  ", w);

	PrintVar (30, 19, "p %.4f  ", p);
	PrintVar (45, 19, "q %.4f  ", q);
	PrintVar (60, 19, "r %.4f  ", r);

#endif

	// Force Velocity dervs
	V.X.u = -Cd * u * rVS;			V.Y.u = 0 * u * rVS;	   		V.Z.u = -Cl * u * rVS;
	V.X.v = 0 * v * rVS;	   		V.Y.v = -0.546 * v * rVS;		V.Z.v = 0 * v * rVS;
	V.X.w = Cl * w * rVS;			V.Y.w = 0 * w * rVS;	   		V.Z.w = -Cd * w * rVS;

	// Moment Velocity dervs
	V.L.u = 0 * u * rVSb;			V.M.u = 0 * u * rVSc;			V.N.u = 0 * u * rVSb;
	V.L.v = -0.0654 * v * rVSb;		V.M.v = 0 * v * rVSc;			V.N.v = 0.118 * v * rVSb;
	V.L.w = 0 * w * rVSb;			V.M.w = -0.44 * w * rVSc;		V.N.w = 0 * w * rVSb;

	// *****************
	// * V.M.w is iffy *
	// *****************

	// Force RotVel dervs
	RV.X.p = 0;						RV.Y.p = 0 * p * rVSb;	  		RV.Z.p = 0;
	RV.X.q = 0 * q * rVSc;			RV.Y.q = 0;						RV.Z.q = 0 * q * rVSc;
	RV.X.r = 0;						RV.Y.r = 0.1435 * r * rVSb;		RV.Z.r = 0;

	// Moment RotVel dervs
	RV.L.p = -0.195 * p * rVSb2;	RV.M.p = 0;						RV.N.p = -0.008 * p * rVSb2;
	RV.L.q = 0;	   					RV.M.q = -0.032 * q * rVSc2;	RV.N.q = 0;
	RV.L.r = 0.0575 * r * rVSb2;	RV.M.r = 0;						RV.N.r = -0.067 * r * rVSb2;
	// Check M.q (c/2U ?????)


	// Force Control dervs
	C.X.a = 0;							C.Y.a = 0 * a * rV2S;				C.Z.a = 0;
	C.X.b = 0.43 * Sin * b * rV2S;		C.Y.b = 0;							C.Z.b = 0.43 * b * Cos * rV2S;
	C.X.c = 0;							C.Y.c = 0.149 * c * rV2S;			C.Z.c = 0;

	// Moment Control dervs
	C.L.a = -0.114 * a * rV2Sb;			C.M.a = 0;							C.N.a = 0.009 * a * rV2Sb;
	C.L.b = 0;							C.M.b = -0.934 * b * rV2Sc;			C.N.b = 0;
	C.L.c = 0.0057 * c * rV2Sb;			C.M.c = 0;							C.N.c = -0.069 * c * rV2Sb;

	// Z Acc dervs
	// use Cm alpha dot	in F94A derv tables

#ifdef PRINT_DERV_DATA
	PrintVar (30, 0, "V.X.u %.0f  ", V.X.u);
	PrintVar (45, 0, "V.Y.u %.0f  ", V.Y.u);
	PrintVar (60, 0, "V.Z.u %.0f  ", V.Z.u);

	PrintVar (30, 1, "V.X.v %.0f  ", V.X.v);
	PrintVar (45, 1, "V.Y.v %.0f  ", V.Y.v);
	PrintVar (60, 1, "V.Z.v %.0f  ", V.Z.v);

	PrintVar (30, 2, "V.X.w %.0f  ", V.X.w);
	PrintVar (45, 2, "V.Y.w %.0f  ", V.Y.w);
	PrintVar (60, 2, "V.Z.w %.0f  ", V.Z.w);

	PrintVar (30, 4, "V.L.u %.0f  ", V.L.u);
	PrintVar (45, 4, "V.M.u %.0f  ", V.M.u);
	PrintVar (60, 4, "V.N.u %.0f  ", V.N.u);

	PrintVar (30, 5, "V.L.v %.0f  ", V.L.v);
	PrintVar (45, 5, "V.M.v %.0f  ", V.M.v);
	PrintVar (60, 5, "V.N.v %.0f  ", V.N.v);

	PrintVar (30, 6, "V.L.w %.0f  ", V.L.w);
	PrintVar (45, 6, "V.M.w %.0f  ", V.M.w);
	PrintVar (60, 6, "V.N.w %.0f  ", V.N.w);


	PrintVar (30, 8, "RV.X.p %.0f  ", RV.X.p);
	PrintVar (45, 8, "RV.Y.p %.0f  ", RV.Y.p);
	PrintVar (60, 8, "RV.Z.p %.0f  ", RV.Z.p);

	PrintVar (30, 9, "RV.X.q %.0f  ", RV.X.q);
	PrintVar (45, 9, "RV.Y.q %.0f  ", RV.Y.q);
	PrintVar (60, 9, "RV.Z.q %.0f  ", RV.Z.q);

	PrintVar (30, 10, "RV.X.r %.0f  ", RV.X.r);
	PrintVar (45, 10, "RV.Y.r %.0f  ", RV.Y.r);
	PrintVar (60, 10, "RV.Z.r %.0f  ", RV.Z.r);

	PrintVar (30, 12, "RV.L.p %.0f  ", RV.L.p);
	PrintVar (45, 12, "RV.M.p %.0f  ", RV.M.p);
	PrintVar (60, 12, "RV.N.p %.0f  ", RV.N.p);

	PrintVar (30, 13, "RV.L.q %.0f  ", RV.L.q);
	PrintVar (45, 13, "RV.M.q %.0f  ", RV.M.q);
	PrintVar (60, 13, "RV.N.q %.0f  ", RV.N.q);

	PrintVar (30, 14, "RV.L.r %.0f  ", RV.L.r);
	PrintVar (45, 14, "RV.M.r %.0f  ", RV.M.r);
	PrintVar (60, 14, "RV.N.r %.0f  ", RV.N.r);

#endif

	// calc forces

	FCRD force;

	force.x = V.X.u + V.X.v + V.X.w + RV.X.p + RV.X.q + RV.X.r + C.X.a + C.X.b + C.X.c;
	force.y = V.Y.u + V.Y.v + V.Y.w + RV.Y.p + RV.Y.q + RV.Y.r + C.Y.a + C.Y.b + C.Y.c;
	force.z = V.Z.u + V.Z.v + V.Z.w + RV.Z.p + RV.Z.q + RV.Z.r + C.Z.a + C.Z.b + C.Z.c;

	NettForce.x = force.y;
	NettForce.y = -force.z;
	NettForce.z = force.x;

	// calc moments

	FCRD moment;
	moment.x = V.L.u + V.L.v + V.L.w + RV.L.p + RV.L.q + RV.L.r + C.L.a + C.L.b + C.L.c;
	moment.y = V.M.u + V.M.v + V.M.w + RV.M.p + RV.M.q + RV.M.r + C.M.a + C.M.b + C.M.c;
	moment.z = V.N.u + V.N.v + V.N.w + RV.N.p + RV.N.q + RV.N.r + C.N.a + C.N.b + C.N.c;

	NettMoment.x = moment.y * 100;
	NettMoment.y = -moment.z * 100;
	NettMoment.z = moment.x * 100;

	// Engines

	PTHRUSTPOINT pThrust = ThrustList;
	while (pThrust != NULL)
	{
		pThrust->Process ();
		NettForce.x += pThrust->Force.x;
		NettForce.y += pThrust->Force.y;
		NettForce.z += pThrust->Force.z;
		pThrust = pThrust->List.NextItem ();
	}


	MODLIMIT (NettForce.x, 600000);
	MODLIMIT (NettForce.y, 2500000);
	MODLIMIT (NettForce.z, 600000);

	MODLIMIT (NettMoment.x, 250000000);
	MODLIMIT (NettMoment.y, 250000000);
	MODLIMIT (NettMoment.z, 250000000);

	CalcAcc ();
//TempCode ARM 15Jul97 	{
//TempCode ARM 15Jul97 		OldAcc.x = Acc.x;
//TempCode ARM 15Jul97 		OldAcc.y = Acc.y;
//TempCode ARM 15Jul97 		OldAcc.z = Acc.z;
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		Acc.x = (NettForce.x / Mass);
//TempCode ARM 15Jul97 		Acc.y = (NettForce.y / Mass);
//TempCode ARM 15Jul97 		Acc.z = (NettForce.z / Mass);
//TempCode ARM 15Jul97 	}

	CalcRotAcc ();
//TempCode ARM 15Jul97 	{
//TempCode ARM 15Jul97 		OldRotAcc.x = RotAcc.x;
//TempCode ARM 15Jul97 		OldRotAcc.y = RotAcc.y;
//TempCode ARM 15Jul97 		OldRotAcc.z = RotAcc.z;
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		RotAcc.x = (NettMoment.x / RotInertia.x);
//TempCode ARM 15Jul97 		RotAcc.y = (NettMoment.y / RotInertia.y);
//TempCode ARM 15Jul97 		RotAcc.z = (NettMoment.z / RotInertia.z);
//TempCode ARM 15Jul97 	}
			
	TransInt (ALL);
//TempCode ARM 15Jul97 	{
//TempCode ARM 15Jul97 		FCRD acc;
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		acc.x = (OldAcc.x + Acc.x) * 0.5;
//TempCode ARM 15Jul97 		acc.y = (OldAcc.y + Acc.y) * 0.5;
//TempCode ARM 15Jul97 		acc.z = (OldAcc.z + Acc.z) * 0.5;
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		TnsPnt (acc, acc, Ori);
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		OldVel.x = Vel.x;
//TempCode ARM 15Jul97 		OldVel.y = Vel.y;
//TempCode ARM 15Jul97 		OldVel.z = Vel.z;
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		Vel.x += acc.x * MODEL_DT;
//TempCode ARM 15Jul97 		Vel.y += (acc.y - GRAVITY) * MODEL_DT;
//TempCode ARM 15Jul97 		Vel.z += acc.z * MODEL_DT;
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		OldPos.x = Pos.x;
//TempCode ARM 15Jul97 		OldPos.y = Pos.y;
//TempCode ARM 15Jul97 		OldPos.z = Pos.z;
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		Pos.x += ((OldVel.x + Vel.x) * MODEL_DT) * 0.5;
//TempCode ARM 15Jul97 		Pos.y += ((OldVel.y + Vel.y) * MODEL_DT) * 0.5;
//TempCode ARM 15Jul97 		Pos.z += ((OldVel.z + Vel.z) * MODEL_DT) * 0.5;
//TempCode ARM 15Jul97 	}

	RotInt (ALL);
//TempCode ARM 15Jul97 	{
//TempCode ARM 15Jul97 		OldRotVel.x = RotVel.x;
//TempCode ARM 15Jul97 		OldRotVel.y = RotVel.y;
//TempCode ARM 15Jul97 		OldRotVel.z = RotVel.z;
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		RotVel.x += ((OldRotAcc.x + RotAcc.x) * MODEL_DT) * 0.5;
//TempCode ARM 15Jul97 		RotVel.y += ((OldRotAcc.y + RotAcc.y) * MODEL_DT) * 0.5;
//TempCode ARM 15Jul97 		RotVel.z += ((OldRotAcc.z + RotAcc.z) * MODEL_DT) * 0.5;
//TempCode ARM 15Jul97 
//TempCode ARM 15Jul97 		RotVelInt ();
//TempCode ARM 15Jul97 	}

//	UpdateAirStruc ();

//	Ground ();

//	Instruments (ControlledAC);

}

