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



#define F_GRAFIX											//DAW 05Aug96
#define F_COMMON
#define F_BATTLE



#include "collided.h"										//PD 06Sep96
#include "Dosdefs.h"		
#include "Worldinc.h"


#include "modvec.h"
#include "model.h"
#include "acmmodel.h"



#include "FlyModel.h"
#include "mymath.h"
#include "enumbits.m"
#include "mytime.h"											//RDH 25Apr96
#include "ranges.h"
#include "missman2.h"										//JIM 22Aug96
#include "movement.h"
#include "transite.h"


#include "ai.h"
#include "miles.h"											//RDH 25Jul96
#include "landscap.h"										//RDH 18Dec96
#include "viewsel.h"										//RDH 25Jul96
#include "3dcom.h"											//RJS 22Aug96
#include "speed.h"											//RDH 01Oct96
#include "persons2.h"

#include "model.h"




SLong	const	MAXAUTOTHRUST = 100;	
//static 
RequiredBankDataElement 	CombatReqBankData[] =
			{
				{ANGLES_FifthDeg, ANGLES_10Deg},
				{ANGLES_2Deg, ANGLES_20Deg},
				{ANGLES_10Deg, ANGLES_45Deg},
				{ANGLES_45Deg, MAXCOMBATROLL},
				{ANGLES_180BareDeg, MAXCOMBATROLL}
//DeadCode CSB 28/03/99					{ANGLES_FifthDeg, ANGLES_0Deg},
//DeadCode CSB 28/03/99					{ANGLES_HalfDeg, ANGLES_3Deg},
//DeadCode CSB 28/03/99					{ANGLES_1Deg, ANGLES_4Deg},
//DeadCode CSB 28/03/99					{ANGLES_2Deg, ANGLES_5Deg},
//DeadCode CSB 28/03/99					{ANGLES_3Deg, ANGLES_10Deg},
//DeadCode CSB 28/03/99					{ANGLES_4Deg, ANGLES_15Deg},
//DeadCode CSB 28/03/99					{ANGLES_5Deg, ANGLES_22Deg},
//DeadCode CSB 28/03/99					{ANGLES_6Deg, ANGLES_30Deg},
//DeadCode CSB 28/03/99					{ANGLES_10Deg, ANGLES_45Deg},
//DeadCode CSB 28/03/99	//DeadCode RDH 17Jul96 				{ANGLES_22Deg, ANGLES_60Deg},
//DeadCode CSB 28/03/99					{ANGLES_30Deg, MAXCOMBATROLL},
//DeadCode CSB 28/03/99					{ANGLES_180BareDeg, MAXCOMBATROLL}
			};

Float	AirStruc::CalcSimpleAccel ()
{
	if(classtype->aerobaticfactor == AEROBATIC_LOW)
	{
		INT3;
		return(0);
	}
	
	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	extern enum ACM_COMMAND;
	Float Thrust, Drag, Lift;
	Float mass;		//kg		
	Float accel;
	Float fvel = vel * 0.1;	//m/s
	SWord sinroll, cosroll;
	Float N;
//DeadCode CSB 24/09/98		Float	aoa;
//DeadCode CSB 24/09/98		Float	Ps;			//m/s
//DeadCode CSB 24/09/98		Float	area;		//m^2
//DeadCode CSB 24/09/98		Float	CD;
//DeadCode CSB 24/09/98		Float	accel, accelh;
//DeadCode CSB 24/09/98		SWord	sinroll, cosroll, c, s;

//***************************************************************************************
	//CSB 24/09/98
	mass = classtype->weightempty * 0.01 + (weap.left.int_fuel + weap.centre.int_fuel + weap.right.int_fuel) * 0.00001;	// -> kg
	PMAINPLANE pMainPlane = MOD.MainPlaneList;

	FP qS = 0.5 * MOD.AmbDensity * /* 10000 * */ fvel * fvel * pMainPlane->Area; //* 0.0001;

	Math_Lib.high_sin_cos(roll, sinroll, cosroll);
	if(cosroll == 0) 
		Lift = mass * 9 * 9.8065;
	else
		Lift = mass * 32767 / cosroll * 9.8065;
	if(Lift < 0) Lift *= -1;

	if(Lift > 1.25 * qS) Lift = 1.25 * qS;

	Drag = pMainPlane->Cdo * qS + pMainPlane->k * Lift * Lift / qS;

	PENGINE pEngine = MOD.EngineList;

	UByte	FF = FlyingFactor();
//DeadCode CSB 03/06/99		fly.thrustpercent = 70 + (FF * FF * 30)/65536;
	AircraftAnimData*	adptr = (AircraftAnimData *)Anim;

	Float ThrustPercent =  fly.thrustpercent;
	ThrustPercent       *= (255.0 - Float(adptr->ENGINELEFTIN)) / 255.0;

	if(pEngine->Type == ET_JET)
		Thrust = pEngine->T100 * ThrustPercent * MOD.AmbDensity / 0.0001225 * 0.01;
	else
		Thrust = pEngine->T100 * ThrustPercent * MOD.AmbDensity / 0.0001225 * 0.1 / vel;

	Drag *= (2048 - adptr->LEFTWINGOUT - adptr->LEFTWINGIN - adptr->RIGHTWINGIN - adptr->RIGHTWINGOUT);
	Drag /= 2048;

	Drag *= (512.0 - FP(FF)) / 256.0;

//DeadCode CSB 29/04/99		if(!fly.thrustpercent)
//DeadCode CSB 29/04/99			Drag += fvel * fvel;	//AirBrakes
	
	accel = (Thrust - Drag)/mass;
	if(fvel != 0)
		accel -= 9.8065 * 0.1 * vely/fvel ; 

	return(accel);


//***************************************************************************************
	
//DeadCode CSB 24/09/98	//	Float temp, pres;
//DeadCode CSB 24/09/98		Float dens;									//kg/m^3
//DeadCode CSB 24/09/98	//DeadCode CSB 15/09/98		MMC.Sky.Ambient (World.Y, dens, temp, pres);
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98		dens = MOD.AmbDensity * 10000;
//DeadCode CSB 24/09/98	//	pres = MOD.AmbPres;
//DeadCode CSB 24/09/98	//	temp = MOD.AmbTemp;
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98		mass = 0.00001 * (weap.centre.int_fuel +						//cg
//DeadCode CSB 24/09/98							   classtype->weightempty * 1000);		//centi kilo g
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98		area = 0;
//DeadCode CSB 24/09/98		PMAINPLANE pMainPlane = MOD.MainPlaneList;
//DeadCode CSB 24/09/98		while (pMainPlane != NULL)
//DeadCode CSB 24/09/98		{
//DeadCode CSB 24/09/98			area += pMainPlane->Area * 0.0001;				//cm^2
//DeadCode CSB 24/09/98			pMainPlane = pMainPlane->List.NextItem ();
//DeadCode CSB 24/09/98		}
//DeadCode CSB 24/09/98		FP modincArea = area;
//DeadCode CSB 24/09/98		FP moddecArea = area;
//DeadCode CSB 24/09/98		if (Manual_Pilot.ControlledAC2 != this)
//DeadCode CSB 24/09/98		{
//DeadCode CSB 24/09/98			UByte	FightingFactor = FlyingFactor();
//DeadCode CSB 24/09/98			FP areainc = area * (256 - FightingFactor)/1024;
//DeadCode CSB 24/09/98			modincArea = area + areainc * 2;
//DeadCode CSB 24/09/98			moddecArea = area - areainc;
//DeadCode CSB 24/09/98		}
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98		Math_Lib.high_sin_cos(roll, sinroll, cosroll); 
//DeadCode CSB 24/09/98		Float	n; 
//DeadCode CSB 24/09/98		if (cosroll == 0)
//DeadCode CSB 24/09/98			n = 10;
//DeadCode CSB 24/09/98		else
//DeadCode CSB 24/09/98		{
//DeadCode CSB 24/09/98			n = 32767;
//DeadCode CSB 24/09/98			n = n/cosroll;
//DeadCode CSB 24/09/98		}
//DeadCode CSB 24/09/98		if (n < 0)
//DeadCode CSB 24/09/98			n = -n;
//DeadCode CSB 24/09/98		if (n > 7 )
//DeadCode CSB 24/09/98			n = 7;
//DeadCode CSB 24/09/98	 	Float wCL = (2 * n * mass * 9.80655) / (dens * fvel * fvel * moddecArea);
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98		//assume only one set of wings
//DeadCode CSB 24/09/98		pMainPlane = MOD.MainPlaneList;
//DeadCode CSB 24/09/98		// Calc aoa
//DeadCode CSB 24/09/98		if (!pMainPlane->pClCurve->GetIndex (wCL, aoa))
//DeadCode CSB 24/09/98		{
//DeadCode CSB 24/09/98			wCL = 0;
//DeadCode CSB 24/09/98			pMainPlane->pClCurve->GetMaxValue (wCL, aoa);
//DeadCode CSB 24/09/98		}
//DeadCode CSB 24/09/98		// Calc CD
//DeadCode CSB 24/09/98		if ((aoa > pMainPlane->AoaMin) && (aoa < (pMainPlane->AoaMax)))
//DeadCode CSB 24/09/98			CD = pMainPlane->Cdo + (pMainPlane->k * wCL * wCL);
//DeadCode CSB 24/09/98		else
//DeadCode CSB 24/09/98			CD = pMainPlane->pCdCurve->GetValue (aoa);
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98	//perhaps we don't need this?	CD *= MainPlaneList->pCompCdCurve->GetValue (Mach);
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98		// Calc Drag
//DeadCode CSB 24/09/98		Drag = CD * 0.5 * dens * fvel * fvel * modincArea;
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98		MOD.ProcessEngines (this);
//DeadCode CSB 24/09/98	
//DeadCode CSB 24/09/98	   	PENGINE pEngine = MOD.EngineList;
//DeadCode CSB 24/09/98		Thrust = 0;
//DeadCode CSB 24/09/98		while (pEngine != NULL)
//DeadCode CSB 24/09/98		{
//DeadCode CSB 24/09/98			Thrust += pEngine->Thrust;
//DeadCode CSB 24/09/98			pEngine = pEngine->List.NextItem();
//DeadCode CSB 24/09/98		}
//DeadCode CSB 24/09/98		if (fvel == 0)
//DeadCode CSB 24/09/98		{
//DeadCode CSB 24/09/98			accel = (Thrust - Drag)/ mass; 
//DeadCode CSB 24/09/98		}else
//DeadCode CSB 24/09/98		{
//DeadCode CSB 24/09/98			Ps = ((Thrust - Drag) * fvel) / (mass * 9.80655);
//DeadCode CSB 24/09/98			accel = (Ps - vely/10) * 9.80655/fvel;
//DeadCode CSB 24/09/98		}
//DeadCode CSB 24/09/98		return(accel);
//DeadCode CSB 24/09/98	//	Math_Lib.high_sin_cos(pitch, s, c);
//DeadCode CSB 24/09/98	//
//DeadCode CSB 24/09/98	//	accely = s * accel / 32768;
//DeadCode CSB 24/09/98	//	accelh = c * accel / 32768;
//DeadCode CSB 24/09/98	//
//DeadCode CSB 24/09/98	//	Math_Lib.high_sin_cos(hdg, s, c);
//DeadCode CSB 24/09/98	//	accelx = s * accelh / 32768;
//DeadCode CSB 24/09/98	//	accelz = c * accelh / 32768;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcMaxPitchRate
//Author		Craig Beeston 
//Date			Tue 1 June 1999
//
//Description	Calculates the maximum pitch rate for a simple movecode
//				Limited by G and stall limit
//
//Inputs		
//
//Returns		Max Pitch rate in Rowans per second
//
//------------------------------------------------------------------------------
UWord AirStruc::CalcMaxPitchRate()
{
	if(classtype->aerobaticfactor == AEROBATIC_LOW)
		return(classtype->maxpitchrate);

	SWord FF = FlyingFactor();
	SWord maxG = 1 + (10 * FF) / 256;
	ULong pitchrateMG = ANGLES_90Deg;
	if(vel > 150) pitchrateMG = (1043100 * maxG) / vel;	//rowans/sec for 9 g
	FP maxpitchrate = (ANGLES_50Deg * FlyingFactor()) / 256.0;
	maxpitchrate *= vel * fly.pModel->AmbDensity / (0.0001225 * classtype->maxvel);
		//Pretty good figure for all MiG Alley Aircraft		//CSB 01/06/99	

	if(maxpitchrate > pitchrateMG) 
		maxpitchrate = pitchrateMG;
	
/* TEST CODE CSB 01/06/99 */	
/* TEST CODE CSB 01/06/99 */		
/* TEST CODE CSB 01/06/99 */	
/*	MODEL& MOD = *fly.pModel;
	int flightno = formpos & 0x03;
	int flightpo = (formpos & 0x30) / 16;
	int grouppos = 1 + flightno * 4 + flightpo;
	int line = grouppos + 1;
	if((MOD.Type == AT_MIG15) || (MOD.Type == AT_MIG15BIS))
		line += 9;

	PrintVar(60, line, "F %.0f ", FP(FF));

	FP MPR = maxpitchrate / 182.04;
	if(maxpitchrate == pitchrateMG)
	{
		PrintVar(65, line, "%.0f x G ", FP(maxG));
		PrintVar(70, line, " %.2f ", FP(MPR));
	}
	else
		PrintVar(65, line, "STALL %.2f ", FP(MPR));

	FP APR = Model_InstTurnRate(this) * 5730.0;
	if(APR < 0) APR *= -1;
	if(APR > MPR)
		PrintVar(76, line, "%.1f", FP(APR));
*/
/* TEST CODE CSB 01/06/99 */
/* TEST CODE CSB 01/06/99 */
/* TEST CODE CSB 01/06/99 */
	return((UWord)maxpitchrate);
}


//DeadCode CSB 29/03/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 29/03/99	//Procedure		TurnFight
//DeadCode CSB 29/03/99	//Author		R. Hyde 
//DeadCode CSB 29/03/99	//Date			Fri 13 Mar 1998
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//Description	
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//Inputs		
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//Returns	
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//------------------------------------------------------------------------------
//DeadCode CSB 29/03/99	void	AirStruc::SimpleTurningFight()
//DeadCode CSB 29/03/99	{
//DeadCode CSB 29/03/99		SWord	reqdeltahdg,reqdeltahdg_sign;
//DeadCode CSB 29/03/99		UWord	reqdeltahdg_pos;
//DeadCode CSB 29/03/99		COORDS3D	target;
//DeadCode CSB 29/03/99		MODEL& MOD = *fly.pModel;
//DeadCode CSB 29/03/99		AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 29/03/99		SLong vx, vy, vz;
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		reqdeltahdg = 	hdg - HdgIntercept;
//DeadCode CSB 29/03/99		Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		if (!ai.unfriendly)			//AMM13nov98
//DeadCode CSB 29/03/99			return;			//AMM13nov98
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		if (	(reqdeltahdg_pos < (SWord)ANGLES_90Deg)
//DeadCode CSB 29/03/99			)		
//DeadCode CSB 29/03/99		{
//DeadCode CSB 29/03/99			CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99			target.X = ai.unfriendly->World.X + vx;
//DeadCode CSB 29/03/99			target.Y = ai.unfriendly->World.Y + vy;
//DeadCode CSB 29/03/99			target.Z = ai.unfriendly->World.Z + vz;
//DeadCode CSB 29/03/99			InterceptandRange (&target);
//DeadCode CSB 29/03/99		}else
//DeadCode CSB 29/03/99			target = ai.unfriendly->World;
//DeadCode CSB 29/03/99		if (		(classtype->visible == MIG15)
//DeadCode CSB 29/03/99				&&	(		(ai.combatskill >= SKILL_ACE)
//DeadCode CSB 29/03/99						||	(ai.morale < MORALE_GOOD)
//DeadCode CSB 29/03/99					)
//DeadCode CSB 29/03/99			)
//DeadCode CSB 29/03/99			SimpleTurnWithPitchChange(HdgIntercept, FALSE, target);
//DeadCode CSB 29/03/99		else
//DeadCode CSB 29/03/99			SimpleTurnWithPitchChange(HdgIntercept, TRUE, target);
//DeadCode CSB 29/03/99	}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurnFight
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleTurningFight()
{
	COORDS3D	target;
	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	SLong vx, vy, vz;
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltapitch,reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;
	
	if (!ai.unfriendly)		
		return;			

	target.X = ai.unfriendly->World.X;
	target.Y = ai.unfriendly->World.Y;
	target.Z = ai.unfriendly->World.Z;
	InterceptandRange (&target);

	reqdeltahdg   =	HdgIntercept - hdg;
	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
	SimpleMoveToThrust (ThrustfromFF());							  //RDH 06/05/99

//DeadCode CSB 03/06/99		if((reqdeltahdg_pos < ANGLES_90Deg) && (Range < ENGAGERANGE))
	if((reqdeltahdg_pos < ANGLES_45Deg) && (Range < WEAPONSRANGE))
	{
		if (	(classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 		if( (classtype->visible == MIG15)
			&& ((ai.combatskill >= SKILL_ACE) || (ai.morale < MORALE_GOOD)) )
			if(reqdeltahdg_pos < ANGLES_90Deg)
			{
				if	(		(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)			  //RDH 04/07/99
						&&	(unfriendly->classtype->aerobaticfactor != AEROBATIC_LOW)						
					)
				{
					if(Range < WEAPONSRANGE)
						SimpleMoveToThrust(0);
					else
						SimpleMoveToThrust (ThrustfromFF());
					if(Range < 0.5 * WEAPONSRANGE)
						ACM.SpeedBrakesOut();
					else
						ACM.SpeedBrakesIn();
				}
			}

		CalcLead(*this, *ai.unfriendly,vx,vy,vz, FALSE);
		target.X = ai.unfriendly->World.X + vx;
		target.Y = ai.unfriendly->World.Y + vy;
		target.Z = ai.unfriendly->World.Z + vz;
		InterceptandRange (&target);
		reqdeltahdg   =	HdgIntercept - hdg;
		reqdeltapitch =	PitchIntercept - pitch;
		Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
		Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
//DeadCode CSB 06/04/99	PrintVar(60, 5, "DeltaPitch %.0f ", (FP)( (PitchIntercept - pitch) / 182.04) );
//DeadCode CSB 06/04/99	PrintVar(60, 6, "DeltaHeadg %.0f ", (FP)( (HdgIntercept - hdg) / 182.04) );
//DeadCode CSB 06/04/99	PrintVar(60, 7, "Targ Range %.0f ", (FP)( (Range) / 100.0) );
		
		if(reqdeltapitch != 0)
		{
			SWord DesRoll = Math_Lib.arctan(reqdeltahdg, reqdeltapitch);
			SimpleMoveToRoll(DesRoll);
		}

		SWord sin_roll, cos_roll;
		Math_Lib.high_sin_cos(roll, sin_roll, cos_roll);
//DeadCode CSB 01/06/99			FP MaxDeltaPitch = (FP)classtype->maxpitchrate * (FP)Timer_Code.FRAMETIME / 100.0 / 32768.0;
		FP MaxDeltaPitch = (FP)CalcMaxPitchRate() * (FP)Timer_Code.FRAMETIME / (100.0 * 32768.0);
		FP MaxDeltaYaw   = MaxDeltaPitch * sin_roll;
		MaxDeltaPitch	 = MaxDeltaPitch * cos_roll;

		SWord	maxdeltapitch_sign, maxdeltayaw_sign;
		UWord	maxdeltapitch_pos,  maxdeltayaw_pos;
		Math_Lib.Pos((SWord)MaxDeltaPitch, maxdeltapitch_pos, maxdeltapitch_sign);
		Math_Lib.Pos((SWord)MaxDeltaYaw  , maxdeltayaw_pos,   maxdeltayaw_sign);
		FP factor1 = 1, factor2 = 1;
		if(maxdeltapitch_pos > reqdeltapitch_pos) factor1 = reqdeltapitch_pos / maxdeltapitch_pos;
		if(maxdeltayaw_pos   > reqdeltahdg_pos)   factor2 = reqdeltahdg_pos / maxdeltayaw_pos;
		if(factor1 > factor2) factor1 = factor2;
		pitch += SWord((FP)MaxDeltaPitch * (FP)factor1);
		hdg   += SWord((FP)MaxDeltaYaw   * (FP)factor1);
		fly.cpitch = pitch;

		hdg -= (Angles) CalcHdg ();	//This means that all the heading change is done inside this routine
	}
	else
	{
		if((roll > ANGLES_90Deg) || (roll < ANGLES_270Deg))
			SimpleMoveToRoll(0);
		else
			SimpleMoveToHdg (HdgIntercept);	
		AutoCalcPitch();
	}
	
	if	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)			  //RDH 04/07/99
	{
		if((reqdeltahdg_pos < ANGLES_10Deg) && (reqdeltapitch_pos < ANGLES_10Deg))
		{
			advantage = TRUE;
			disadvantage = FALSE;
			MoraleMod();
			SetManoeuvreTime (1000);
		}

		if (		(fly.leadflight)					
				&&	 (fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER)
			)//force manoeuvre to allow disengage
				ai.manoeuvre = MANOEUVRE_SELECT;

		if(!TimeLeft())
		{
			if(    (World.Y < FT_1000)
				|| (Range > ENGAGERANGE)
				|| (pitch > ANGLES_30Deg)
				|| (pitch < ANGLES_330Deg) )
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
		if(Math_Lib.rnd(4 * 65536) < (256 - FlyingFactor()))	//Poor skill -> every 20 secs
			ai.manoeuvre = MANOEUVRE_SCISSORS;
	}
}				

//DeadCode CSB 29/03/99		reqdeltahdg = 	hdg - HdgIntercept;
//DeadCode CSB 29/03/99		Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		if (!ai.unfriendly)			//AMM13nov98
//DeadCode CSB 29/03/99			return;			//AMM13nov98
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		if (	(reqdeltahdg_pos < (SWord)ANGLES_90Deg)
//DeadCode CSB 29/03/99			)		
//DeadCode CSB 29/03/99		{
//DeadCode CSB 29/03/99			CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99			target.X = ai.unfriendly->World.X + vx;
//DeadCode CSB 29/03/99			target.Y = ai.unfriendly->World.Y + vy;
//DeadCode CSB 29/03/99			target.Z = ai.unfriendly->World.Z + vz;
//DeadCode CSB 29/03/99			InterceptandRange (&target);
//DeadCode CSB 29/03/99		if (		(classtype->visible == MIG15)
//DeadCode CSB 29/03/99				&&	(		(ai.combatskill >= SKILL_ACE)
//DeadCode CSB 29/03/99						||	(ai.morale < MORALE_GOOD)
//DeadCode CSB 29/03/99					)
//DeadCode CSB 29/03/99			)
//DeadCode CSB 29/03/99			SimpleTurnWithPitchChange(HdgIntercept, FALSE, target);
//DeadCode CSB 29/03/99		else
//DeadCode CSB 29/03/99			SimpleTurnWithPitchChange(HdgIntercept, TRUE, target);
//DeadCode CSB 29/03/99	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
void	AirStruc::SimpleTurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget,COORDS3D	target)
{
	if (CombatFactor() > 200)
	{
		if (classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 		if (classtype->visible == MIG15)
			SimpleTurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_5Deg, target);	
		else if (World.Y > FT_10000)
			SimpleTurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	
		else
			SimpleTurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	

	}else
		SimpleTurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurnFightSub
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleTurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target)
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	SLong temp_range;
	temp_range = Range; 	

	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltapitch,reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;
	FP desiredturn;
	SLong		time;

	reqdeltahdg = 	hdg - HdgIntercept;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (1000);
			ACM.maxdeltaforclosework = 0.0;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.MinHeight (FT_2000);
 			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
			reqdeltapitch = PitchIntercept - fly.cpitch;//	fly.cpitch - PitchIntercept;		//CHECK THIS !!!!
			Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);

			ANGLES delta = unfriendly->hdg + ANGLES_180Deg + ANGLES_30Deg - hdg;

			{
				if (sitbehindtarget)
					SlowDown(reqdeltahdg_pos);
	
				SimpleTurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, deltapitch);

				if  (		(!ManoeuvreTimeLeft())
					)
				{
					if	(ACM.maxdeltaforclosework <= 0.1)
						ai.manoeuvre = MANOEUVRE_SELECT;
					else
					{
						if (		(fly.leadflight)					
								&&	 (fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER)
							)//force manoeuvre to allow disengage
						{
								ai.manoeuvre = MANOEUVRE_SELECT;
						}else
						{//on tail of target so keep in manoeuvre and up morale
							advantage = TRUE;
							disadvantage = FALSE;
							MoraleMod();
							SetManoeuvreTime (1000);
						}
					}
				}
			}
		}
	}

}
void	AirStruc::SimpleTurnFightTargetNotOnNose(SWord	reqdeltahdg, SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos, ANGLES	deltapitch)
{

	SWord delta;
	SWord reqroll;
	SWord dpitch;

	SWord PI = PitchIntercept;
	if  (		(PI < 0)
			&&	(Range > WEAPONSRANGE)
		)
		PI = 0;
	delta = PI + deltapitch;
	if  (		(delta < ANGLES_0Deg)
			&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
			&&	(deltapitch << ANGLES_180Deg)				//if he really wants to go down then let him
			&&	(		(Range > WEAPONSRANGE)
					||	(classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 					||	(classtype->visible == MIG15)
						
				)
		)	
		delta = ANGLES_0Deg;
	reqdeltapitch = 	delta - fly.cpitch;
	Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
	if (reqdeltapitch_pos > ANGLES_40Deg)
		dpitch = ANGLES_40Deg;
	else
		dpitch = reqdeltapitch_pos;
	if (reqdeltapitch_sign < 0)
		dpitch = - dpitch;

	
	SimpleMoveToHdg (HdgIntercept);	
	PitchIntercept = (Angles) dpitch;
	AutoCalcPitch();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChkAtDesiredHdg
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::ChkAtDesiredHdg (ANGLES desiredhdg,ANGLES target)

{
	SWord deltahdg;
	UWord	deltahdg_pos;
	SWord	deltahdg_sign;

	deltahdg = desiredhdg -	hdg;
	Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);
	if (deltahdg_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChkAtDesiredHdg
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::ChkAtDesiredRoll (ANGLES desiredroll,ANGLES target)

{
	SWord deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;

	deltaroll = desiredroll -	roll;
	Math_Lib.Pos (((SWord)deltaroll),deltaroll_pos,deltaroll_sign);
	if (deltaroll_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}
}
 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DesiredPitchChk
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	AirStruc::DesiredPitchChk (ANGLES desiredpitch,ANGLES target)

{
	SWord deltapitch;
	UWord	deltapitch_pos;
	SWord	deltapitch_sign;

	deltapitch = desiredpitch -	fly.cpitch;
	Math_Lib.Pos (((SWord)deltapitch),deltapitch_pos,deltapitch_sign);
	if (deltapitch_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DesiredAcPitchChk
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	AirStruc::DesiredAcPitchChk (ANGLES desiredpitch,ANGLES target)

{
	SWord deltapitch;
	UWord	deltapitch_pos;
	SWord	deltapitch_sign;

	deltapitch = desiredpitch -	pitch;
	Math_Lib.Pos (((SWord)deltapitch),deltapitch_pos,deltapitch_sign);
	if (deltapitch_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChkAtDesiredAcHdg
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::ChkAtDesiredAcHdg (ANGLES desiredhdg,ANGLES target)

{
	SWord deltahdg;
	UWord	deltahdg_pos;
	SWord	deltahdg_sign;

	deltahdg = desiredhdg -	hdg;
	Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);
	if (deltahdg_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}
}

void  AirStruc::SimpleMakeForFriendly()
{
}
void  AirStruc::SimpleImmelmann()
{
}

void  AirStruc::SimpleGainSpeed()
{
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (2000);
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SimpleMoveToRoll (ANGLES_0Deg);
			if (World.Y < FT_1000)
				PitchIntercept =  ANGLES_0Deg;
			else
				PitchIntercept =  ANGLES_350Deg;
			AutoCalcPitch();

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LeadUnFriendly
//Author		R. Hyde 
//Date			Fri 15 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleLeadUnFriendly ()
{

	COORDS3D	target;
	SLong		t,actualrange;
	AirStrucPtr	unfriendly = *ai.unfriendly;

			target.X = ai.unfriendly->World.X;
			target.Y = ai.unfriendly->World.Y;
			target.Z = ai.unfriendly->World.Z;
			InterceptandRange (&target);
			actualrange = Range;

			//closing velocity
			SLong deltax = velx - unfriendly->velx;
			SLong deltay = vely - unfriendly->vely;
			SLong deltaz = velz - unfriendly->velz;
			Math_Lib.Intercept (deltax,deltay,deltaz,Range,HdgIntercept,PitchIntercept);
			//Range is a velocity in 10cm/s
			if (Range != 0)
			{
				t = actualrange / Range;
			}else
			{
				t = 0;
			}
			//when a long way off don't attempt to lead
			if (t >2000)
			t = 0;

			target.X = ai.unfriendly->World.X + (unfriendly->velx * t / 10);
			target.Y = ai.unfriendly->World.Y + (unfriendly->vely * t / 10);
			target.Z = ai.unfriendly->World.Z + (unfriendly->velz * t / 10);
			InterceptandRange (&target);
			AutoCalcPitch();
			SimpleMoveToHdg (HdgIntercept);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GatherSpeed
//Author		R. Hyde 
//Date			Fri 15 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleGatherSpeed ()

{
	COORDS3D	target;

		target.X = ai.unfriendly->World.X;
		target.Y = ai.unfriendly->World.Y;
		target.Z = ai.unfriendly->World.Z;
		InterceptandRange (&target);
		PitchIntercept = ANGLES_330Deg;
		AutoCalcPitch();
 		SimpleMoveToHdg (HdgIntercept);
}



//Simple acm routines											//RDH 11Oct96

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleTopCover
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	The followers are supposed to go near to home line or
//				not depending on skill
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleTopCover ()

{
  if (formpos == 0)
  {//leader
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (500);
			ai.desiredroll = - (ANGLES)ANGLES_30Deg +
 						(Angles)(ANGLES_60Deg * Math_Lib.rnd(2)); 
			ai.ManStep = PHASE1;
		}


		case PHASE1:
		{
			SimpleTightClimbingTurn (ANGLES_5Deg);
		if (!ManoeuvreTimeLeft())
			{
				SetManoeuvreTime (500);
				ai.ManStep = PHASE2;
 			}

			break;
		}
		case PHASE2:
		{
			SimpleTightClimbingTurn (ANGLES_0Deg);

			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE3;
 			}

			break;
		}
		case PHASE3:
		{
			SimpleTightClimbingTurn (ANGLES_0Deg);

			if (AllOnTopCover ())								//JIM 25Nov96
			{													//JIM 25Nov96
				Art_Int.AllBreakOff(this);	//fly.leadflight);	//JIM 25Nov96
//TEMP			 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_SQUADRONREGROUPED,NULL);
			}													//JIM 25Nov96
			else												//JIM 25Nov96
			{
		    	ai.ManStep = PHASE1;
				SetManoeuvreTime (1000);
			}

			break;
		}
  	}
  }else
  {
  	   AirStruc* leader = FindGroupLeader();
	   if (leader == Persons2::PlayerGhostAC)
	   {
			Art_Int.BreakOff(this);
	   }else
	   {

			switch (ai.ManStep)
			{
				case PHASE0:
				{
 					SimpleMoveToThrust (100);
					SetManoeuvreTime (500);
					ai.desiredroll = -(ANGLES)ANGLES_30Deg +
 								(Angles)(ANGLES_60Deg * Math_Lib.rnd(2)); 
					ai.ManStep = PHASE1;
				}


				case PHASE1:
				{
		//DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_10Deg);
					SimpleTightClimbingTurn (ANGLES_5Deg);				//RDH 13Dec96
					if (!ManoeuvreTimeLeft())
					{
						SetManoeuvreTime (1000);
						ai.ManStep = PHASE2;
 					}

					break;
				}
				case PHASE2:
				{
					if (fly.leadflight->World.Y > World.Y)
					{
					SimpleTightClimbingTurn (ANGLES_0Deg);
					}else
					{
		//DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_8Deg);
					SimpleTightClimbingTurn (ANGLES_5Deg);
					}
					break;
				}

  			}
	   }
  }

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleTightClimbingTurn
//Author		R. Hyde 
//Date			Sat 30 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleTightClimbingTurn (ANGLES desiredpitch)
{
 
 	SWord	deltapitch;
 
 	deltapitch = desiredpitch - fly.cpitch;
 	PitchIntercept = desiredpitch; 
 	SimpleTightTurnSubSub (deltapitch);
 
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleLookAround
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleLookAround ()
{

	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (500);								//RDH 25/6/99
			ai.desiredroll = - (ANGLES)ANGLES_45Deg +
 						(Angles)(ANGLES_90Deg * Math_Lib.rnd(2)); 
			ai.ManStep = PHASE1;
		}


		case PHASE1:
		{
			if (World.Y > classtype->fightceiling)
				SimpleTightClimbingTurn (ANGLES_0Deg);
			else
				SimpleTightClimbingTurn (ANGLES_5Deg);			//RDH 14Nov96
			if (!ManoeuvreTimeLeft())
			{
		    	ai.ManStep = PHASE0;
				if (formpos == 0)
				{
					if (AllButLdrNotOnCombat ())				//RDH 26Nov96
					{											//RDH 26Nov96
						ai.manoeuvre=MANOEUVRE_TOPCOVER;		//RDH 26Nov96
					}else										//RDH 26Nov96
					{											//RDH 26Nov96
						ai.manoeuvre=MANOEUVRE_LOOKROUND;		//RDH 26Nov96
					}											//RDH 26Nov96
				}else
				{
					ai.manoeuvre=MANOEUVRE_TOPCOVER;
				}
 			}

			break;
		}
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BarrelRoll
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleBarrelRollAttack ( )

{
	SimpleScissors ( );
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scissors
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleScissors ( )

{
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;
			ai.desiredhdg = hdg + ANGLES_120Deg; 
		}
		case PHASE1:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE3;
			}
			PitchIntercept = ANGLES_2Deg;
			AutoCalcPitch();
			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_100Deg))
			{
				ai.ManStep = PHASE2;
				ai.desiredhdg = hdg - ANGLES_240Deg; 
			}
			break;
		}
		case PHASE2:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE3;
			}
			PitchIntercept = ANGLES_2Deg;
			AutoCalcPitch();
			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_100Deg))
			{
				ai.ManStep = PHASE1;
				ai.desiredhdg = hdg + ANGLES_240Deg; 
			}
			break;
		}
		case PHASE3:
		{

			ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MildScissors
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleMildScissors ( )

{
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;
			ai.desiredhdg = hdg - ANGLES_15Deg; 
		}
		case PHASE1:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE3;
			}
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
			{
				ai.ManStep = PHASE2;
				ai.desiredhdg = hdg + ANGLES_30Deg; 
			}
			break;
		}
		case PHASE2:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE3;
			}
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
			{
				ai.ManStep = PHASE1;
				ai.desiredhdg = hdg - ANGLES_30Deg; 
			}
			break;
		}
		case PHASE3:
		{

			ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveToDesiredHdg
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::SimpleMoveToDesiredHdg (ANGLES desiredhdg,ANGLES target)

{
	Bool	retval;

	SimpleMoveToHdg (desiredhdg);
	retval = ChkAtDesiredHdg (desiredhdg,target);
	return (retval);
}

 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 //Procedure		MoveToHdg
 //Author		R. Hyde 
 //Date			Wed 13 Dec 1995
 //
 //Description	based on difference between desired and actual hdg, fix aileron
 //				to give a roll, morale and skill will fix maxroll				
 //
 //Inputs		
 //
 //Returns	
 //
 //------------------------------------------------------------------------------
void	AirStruc::SimpleMoveToHdg (ANGLES desiredhdg)
 
{
 	SWord	reqdeltahdg, reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
 	SWord	reqroll,deltaroll;
 
 	reqdeltahdg = 	hdg - desiredhdg;
 	Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
 	reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
 
//DeadCode RDH 30Mar96  	deltaroll = (SWord) (reqroll - fly.acroll);
	ai.desiredroll = (Angles) reqroll;
	SimpleMoveToRoll (reqroll);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveToRoll
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleMoveToRoll (SWord desiredroll)

{	//RequiredDRollSub: parameter is desired roll, return val is delta roll

	roll += (Angles) (RequiredDRollSub (desiredroll));
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveToDesiredPitch
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	AirStruc::SimpleMoveToDesiredPitch (ANGLES desiredpitch,ANGLES target)

{
	SWord	retval;


	PitchIntercept = desiredpitch;
	AutoCalcPitch();
	retval = DesiredPitchChk (desiredpitch,target);
	return (retval);


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StraightandLevel
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleStraightandLevel ( )

{
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (2000);
//DEADCODE RDH 20/06/99  			SimpleMoveToThrust (80);
			ai.ManStep = PHASE1;
	 		ai.desiredroll = ANGLES_0Deg;
		}
		case PHASE1:
		{
			//this manoeuvre is only done by poor pilots so we can reduce speed so that
			//other can catch up and attack							  //RDH 20/06/99
			if (vel < MPH250)
				SimpleMoveToThrust (80);
			else
				SimpleMoveToThrust (0);

			if (World.Y < FT_1000)
				PitchIntercept = ANGLES_4Deg;
			else
				PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();

			deltaroll = (SWord) (ai.desiredroll - roll);
			SimpleMoveToRoll (ai.desiredroll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_2Deg)
			{
				ai.ManStep = PHASE2;
			}

			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;

		}
		case PHASE2:
		{
			//this manoeuvre is only done by poor pilots so we can reduce speed so that
			//other can catch up and attack							  //RDH 20/06/99
			if (vel < MPH250)
				SimpleMoveToThrust (80);
			else
				SimpleMoveToThrust (0);

			if (World.Y < FT_1000)
				PitchIntercept = ANGLES_10Deg;
			else
				PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SimpleMoveToRoll (ai.desiredroll);
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;

		}

	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AcmSideSlip
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleAcmSideSlip ( )

{
	
	SimpleSustainedTurn ();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpinRecovery
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleSpinRecovery ()
{
	SimpleSustainedTurn ();

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpinOut
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleSpinOut ( )

{
	SWord	deltaroll;
	UWord	deltayaw_pos;
	SWord	deltayaw_sign;


	
	SLong groundlevel = _Collide.LowestSafeAlt(this,			//RDH 16Dec96
											this->pitch,		//RDH 16Dec96
											this->roll);		//RDH 16Dec96


	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (1);
			ai.ManStep = PHASE1;
			SetManoeuvreTime (600);
			ai.desiredroll = ANGLES_45Deg;
		}
		case PHASE1:
		{
			if ((World.Y - groundlevel) < FT_1000)				//RDH 16Dec96
				PitchIntercept =  ANGLES_8Deg;					//RDH 16Dec96
			else												//RDH 16Dec96
				PitchIntercept =  ANGLES_305Deg;

			AutoCalcPitch();
			SimpleMoveToRoll (ai.desiredroll);
			if (!ManoeuvreTimeLeft())
			{
				ai.desiredroll = ANGLES_0Deg;
				ai.ManStep = PHASE2;
				SetManoeuvreTime (400);
			}

			break;
		}
		case PHASE2:
		{
			if ((World.Y - groundlevel) < FT_1000)				//RDH 16Dec96
				PitchIntercept =  ANGLES_8Deg;					//RDH 16Dec96
			else												//RDH 16Dec96
			PitchIntercept =  ANGLES_340Deg;
			AutoCalcPitch();
			SimpleMoveToRoll (ai.desiredroll);
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
	 			SimpleMoveToThrust (100);

			}else
			{
				
			}
			break;
		}

	}
		SetControlSurfaces ();

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiveforHome
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleDiveforHome ( )

{
	SLong	temp_range;

	temp_range = Range; 	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
			InterceptandRange (&ai.homebase->World);
			ai.desiredhdg = HdgIntercept; 
			SetManoeuvreTime(0);
		}
		case PHASE1:
		{
			if(!TimeLeft())
			{
				Range = temp_range; 	
				if (Range < DANGERRANGE)
				{
					ai.manoeuvre = MANOEUVRE_SELECT;
				}

				if (World.Y < FT_1000)
					PitchIntercept = ANGLES_0Deg;
				else
					PitchIntercept = ANGLES_10Deg;
				Bool level = SimpleMoveToDesiredHdg (ai.desiredhdg, ANGLES_1Deg);
				if((AutoCalcPitch()) && (level))
					SetManoeuvreTime (1000);
				Range = temp_range; 	
				if (Range > ENGAGERANGE)
				{
					ai.manoeuvre = MANOEUVRE_SELECT;
				}
			}
		}
	}
}


//DeadCode CSB 28/03/99	{
//DeadCode CSB 28/03/99		SLong	temp_range;
//DeadCode CSB 28/03/99		temp_range = Range; 	
//DeadCode CSB 28/03/99	
//DeadCode CSB 28/03/99		switch (ai.ManStep)
//DeadCode CSB 28/03/99		{
//DeadCode CSB 28/03/99			case PHASE0:
//DeadCode CSB 28/03/99			{
//DeadCode CSB 28/03/99				if (World.Y < FT_1000)
//DeadCode CSB 28/03/99				{
//DeadCode CSB 28/03/99					PitchIntercept =  ANGLES_0Deg;
//DeadCode CSB 28/03/99					AutoCalcPitch();
//DeadCode CSB 28/03/99				}else
//DeadCode CSB 28/03/99				{
//DeadCode CSB 28/03/99					PitchIntercept =  ANGLES_340Deg;
//DeadCode CSB 28/03/99					AutoCalcPitch();
//DeadCode CSB 28/03/99					InterceptandRange (&ai.homebase->World);
//DeadCode CSB 28/03/99					SimpleMoveToHdg (HdgIntercept);
//DeadCode CSB 28/03/99				}
//DeadCode CSB 28/03/99				if (Range < MILES01)
//DeadCode CSB 28/03/99				{//within mile of home
//DeadCode CSB 28/03/99					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 28/03/99				}
//DeadCode CSB 28/03/99				Range = temp_range; 	
//DeadCode CSB 28/03/99				if (Range > MILES01)
//DeadCode CSB 28/03/99				{//mile from action, reconsider
//DeadCode CSB 28/03/99					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 28/03/99				}
//DeadCode CSB 28/03/99			}
//DeadCode CSB 28/03/99		}
//DeadCode CSB 28/03/99	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbforHome
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleClimbforHome ( )

{
	SLong	temp_range;

	temp_range = Range; 	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
			InterceptandRange (&ai.homebase->World);
			ai.desiredhdg = HdgIntercept; 
			SetManoeuvreTime(0);
		}
		case PHASE1:
		{
			if(!TimeLeft())
			{
				Range = temp_range; 	
				if (Range < DANGERRANGE)
				{
					ai.manoeuvre = MANOEUVRE_SELECT;
				}
				PitchIntercept =  ANGLES_10Deg;
				Bool level = SimpleMoveToDesiredHdg (ai.desiredhdg, ANGLES_1Deg);
				if((AutoCalcPitch()) && (level))
					SetManoeuvreTime (1000);
				Range = temp_range; 	
				if (Range > ENGAGERANGE)
				{
					ai.manoeuvre = MANOEUVRE_SELECT;
				}
			}
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StraightDive
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleStraightDive ( )

{
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (2000);
 			SimpleMoveToThrust (90);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SimpleMoveToRoll (ANGLES_0Deg);
			PitchIntercept =  ANGLES_340Deg;
			AutoCalcPitch();
			if (World.Y < FT_1000)
				ai.manoeuvre = MANOEUVRE_SELECT;
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			break;
		}
	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StandOnTail
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleStandOnTail ( )

{
	COORDS3D	target;
	SLong		time;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (800);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			target.X = ai.unfriendly->World.X;
			target.Y = ai.unfriendly->World.Y;
			target.Z = ai.unfriendly->World.Z;
			InterceptandRange (&target);

			//time for bullets to arrive at current unfriendly position
			time = Range / MUZZELVEL;
			//calc lead position using this time
			target.X = ai.unfriendly->World.X + (unfriendly->velx * time );
			target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
			target.Z = ai.unfriendly->World.Z + (unfriendly->velz * time );
			InterceptandRange (&target);


			SimpleMoveToHdg (HdgIntercept);
			if (vel < MPH55)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}else
			{
				if ((SWord) fly.cpitch < (SWord) PitchIntercept)
				{
					AutoCalcPitch();
				}else
				{
					AutoCalcPitch();
					FireABullet(10);
				}
			}
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}

	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShootToFrighten
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleShootToFrighten ( )

{
	AirStrucPtr	unfriendly = *ai.unfriendly;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (200);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if (!ManoeuvreTimeLeft())
			{
			   	ai.ManStep = PHASE0;
				ai.manoeuvre=MANOEUVRE_SUSTAINEDTURN;
			}
			SimpleTightTurn (FT_1000);
			FireABullet(10);
			break;
		}
	}
}





//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GoHome
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleGoHome ( )

{
	
//DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
	SLong	temp_range;

	temp_range = Range; 	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (1000);
			ai.ManStep = PHASE1;
			InterceptandRange (&ai.homebase->World);
			ai.desiredhdg = HdgIntercept; 
			Range = temp_range;
//jink a bit possibly
			if	(		TargetOnSubjectTail(ANGLES_10Deg)
					&&	(Range < 4 * WEAPONSRANGE)
					&&	(ai.combatskill >= SKILL_REGULAR)
				)
				ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 
		}
		case PHASE1:
		{
			if (!ManoeuvreTimeLeft())
			{
				SetManoeuvreTime (500);
				ai.ManStep = PHASE2;
				InterceptandRange (&ai.homebase->World);
				ai.desiredhdg = HdgIntercept; 
				Range = temp_range;
				if	(		TargetOnSubjectTail(ANGLES_10Deg)
						&&	(Range < 4 * WEAPONSRANGE)
						&&	(ai.combatskill >= SKILL_REGULAR)
					)
					ai.desiredhdg = HdgIntercept + ANGLES_340Deg; 
			}
			if (Range < WEAPONSRANGE)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			PitchIntercept =  ANGLES_0Deg;
			AutoCalcPitch();
			SimpleMoveToHdg (ai.desiredhdg);
			if (Range > COMBATRANGE +METRES1400)
//DeadCode RDH 25Oct96 			if (Range > COMBATRANGE + METRES1400)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
		case PHASE2:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE1;
				SetManoeuvreTime (500);
				InterceptandRange (&ai.homebase->World);


				ai.desiredhdg = HdgIntercept; 
				Range = temp_range;
				if	(		TargetOnSubjectTail(ANGLES_10Deg)
						&&	(Range < 4 * WEAPONSRANGE)
						&&	(ai.combatskill >= SKILL_REGULAR)
					)
					ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 
			}
			if (Range < WEAPONSRANGE)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			PitchIntercept =  ANGLES_0Deg;
			AutoCalcPitch();
			SimpleMoveToHdg (ai.desiredhdg);
//DeadCode RDH 25Oct96 			if (Range > COMBATRANGE + METRES1400)
			if (Range > COMBATRANGE+METRES1400)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveAway
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleMoveAway ( )

{
	UWord	roll_pos;
	SWord	roll_sign;
	SWord	desiredaoa;
	SWord deltahdg;
	UWord	deltahdg_pos;
	SWord	deltahdg_sign;
	UWord	elevator_pos;
	SWord	elevator_sign;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (2000);
			ai.ManStep = PHASE1;
			break;
		}
		case PHASE1:
		{
			if  		(!ManoeuvreTimeLeft())
				
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}

			PitchIntercept =  ANGLES_0Deg;
			AutoCalcPitch();
			SimpleMoveToHdg (HdgIntercept+ANGLES_180Deg);	//get aidesiredroll

			deltahdg = hdg - (HdgIntercept+ANGLES_180Deg);
			Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);

			if (deltahdg_pos <ANGLES_5Deg)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime (1500);
			}
			break;
		}

		case PHASE2:
		{
			SimpleMoveToHdg (HdgIntercept+ANGLES_180Deg);	//get aidesiredroll
			PitchIntercept =  ANGLES_4Deg;
			AutoCalcPitch();
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}

}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AccidentalSpinOut
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	similar to SpinOut, but longer recovery
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleAccidentalSpinOut ( )

{
	SimpleSpinOut ( );
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurningFight
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	attempt to lead, find Hdgintercept and delta, set roll
//				roll should not give alt lose
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void AirStruc::SimpleTurningFight ()
//
//{
//	SWord	deltapitch;
//	COORDS3D	target;
//	SLong		time;
//	AirStrucPtr	unfriendly = *ai.unfriendly;
//	UWord	acroll_pos,aoa_pos;
//	SWord	acroll_sign,reqroll,aoa_sign;
//	
//	switch (ai.ManStep)
//	{
//		case PHASE0:
//		{
//			SimpleMoveToThrust (100);
//			SetManoeuvreTime (1500);
//			ai.ManStep = PHASE1;
//			break;
//		}
//		case PHASE1:
//		{
//			if (!ManoeuvreTimeLeft())
//			{
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
//			if (	(TargetFacingSubject(ANGLES_10Deg))
//				&&	SubjectFacingTarget(ANGLES_10Deg)
//				&&	(Range < METRES150)
//				)
//				{
//					HdgIntercept = HdgIntercept + ANGLES_90Deg;
//					PitchIntercept = PitchIntercept + ANGLES_10Deg;
//				}
//			SimpleTightTurn (FT_1000);
//			break;
//
//		}
//	}
//
//}		
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowGYoYo
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleLowGYoYo ( )

{
	UWord	dhdg_pos;
	SWord	dhdg_sign;
	SWord dhdg;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (1000);
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			dhdg = (SWord) (hdg - HdgIntercept);
			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
			if (dhdg_pos < ANGLES_45Deg)
			{
				dhdg_pos = 5*dhdg_pos/4;  
			}
			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);

		 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
			SimpleMoveToRoll (ai.desiredroll);
			if (	(SimpleMoveToDesiredPitch (ANGLES_340Deg,ANGLES_15Deg))
				||	(!ManoeuvreTimeLeft())
				)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime (500);

			}
			break;
		}
		case PHASE2:
		{
			dhdg = (SWord) (hdg - HdgIntercept);
			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
			if (dhdg_pos < ANGLES_45Deg)
			{
				dhdg_pos = 5*dhdg_pos/4;  
			}
			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);

		 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
			SimpleMoveToRoll (ai.desiredroll);
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VerticalLoop
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleVerticalLoop ( )

{

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (1000);
 			SimpleMoveToThrust (100);
			ai.desiredroll = - (ANGLES)ANGLES_45Deg +
 						(Angles)(ANGLES_90Deg * Math_Lib.rnd(2)); 
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
//DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_15Deg);
			SimpleTightClimbingTurn (ANGLES_7Deg);				//RDH 13Dec96
			if  (!ManoeuvreTimeLeft())
			{
 				ai.manoeuvre = MANOEUVRE_SELECT;

			}
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ImmelmannTurn
//Author		R. Hyde 
//Date			Wed 13 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleImmelmannTurn ( )

{
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
//DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_15Deg);
			SimpleTightClimbingTurn (ANGLES_7Deg);
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HeadOnOffset
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleHeadOnOffset ( )

{
	AirStrucPtr	unfriendly = *ai.unfriendly;

	SLong temp_range;
	temp_range = Range; 	
	COORDS3D	target;
	SWord c,s;
	SWord newhdg;
	UByte	FF = FlyingFactor();

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			InterceptandRange(ai.unfriendly);
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (2000);
			SWord dhdg = HdgIntercept - hdg;
			if ((dhdg) > 0)
				ai.desiredhdg = ANGLES_90Deg;
			else
				ai.desiredhdg = ANGLES_270Deg;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			InterceptandRange(ai.unfriendly);
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca) PitchIntercept = bca;
			AutoCalcPitch();

			ANGLES desiredhdg = ai.desiredhdg;
			ANGLES unfHdgIntercept = HdgIntercept;
			SLong	unfRange = Range;
			newhdg = unfriendly->hdg + ai.desiredhdg;

			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((BREAKTURNRADIUS * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((BREAKTURNRADIUS * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - desiredhdg;
		 	ANGLES reqroll = (Angles)FindRequiredRoll (reqdeltahdg,CombatReqBankData);

			int decisionpoint = Math_Lib.rnd(2);

			if  (		(Range < (2 * BREAKTURNRADIUS ))
					&&	(FF < 200)
				)
			{
				if (decisionpoint)
				{
					if (FF < 90)
					{
						ai.manoeuvre = MANOEUVRE_PANICTURN;
						ai.ManStep = PHASE0;
					}else  
					{
						ai.manoeuvre = MANOEUVRE_BREAKTURN;
						ai.ManStep = PHASE0;
					}
				}else
				{
					ai.ManStep = PHASE2;
				}

			}else if	(		(Range < BREAKTURNRADIUS)
							
						)
			{
				if (decisionpoint)
				{
					ai.manoeuvre = MANOEUVRE_BREAKTURN;
					ai.ManStep = PHASE0;
				}else
				{
					ai.desiredhdg = ai.desiredhdg  + ANGLES_180Deg;
					ai.ManStep = PHASE2;
				}
			}

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE2:
		{
			InterceptandRange(ai.unfriendly);
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca ) PitchIntercept = bca;
			AutoCalcPitch();

			ANGLES desiredhdg = ai.desiredhdg;
			ANGLES unfHdgIntercept = HdgIntercept;
			SLong	unfRange = Range;
			newhdg = unfriendly->hdg + ai.desiredhdg;

			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((METRES30 * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((METRES30 * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - ai.desiredhdg;
		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			SimpleMoveToRoll((Angles)reqroll);

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			if	(SubjectOnTargetTail(ANGLES_80Deg))
			{
				if	(		(ai.unfriendly == Manual_Pilot.ControlledAC2)
						&&	(((AirStruc*)ai.unfriendly)->Follower())
					)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEADON, MSG_HEADON, ((AirStruc*)ai.unfriendly)->Follower(), this, ((AirStruc*)ai.unfriendly)));

				int startpoint = Math_Lib.rnd(2);
				ai.ManStep = PHASE0;
				if (FF < 90)
				{
					if (startpoint)
						ai.manoeuvre = MANOEUVRE_JINK;
					else
						ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
				}else if (FF < 200)
				{
					if (startpoint)
							ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
					else
							ai.manoeuvre = MANOEUVRE_EXTENSION;
				}else 
				{
					if (startpoint)
							ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
					else
							ai.manoeuvre = MANOEUVRE_BREAKTURN;
				}
			}
		}
	}
	
//DeadCode CSB 05/04/99		UWord	roll_pos,turn_pos;
//DeadCode CSB 05/04/99		SWord	turn_sign,roll_sign;
//DeadCode CSB 05/04/99		
//DeadCode CSB 05/04/99		switch (ai.ManStep)
//DeadCode CSB 05/04/99		{
//DeadCode CSB 05/04/99			case PHASE0:
//DeadCode CSB 05/04/99			{
//DeadCode CSB 05/04/99				SimpleMoveToThrust (100);
//DeadCode CSB 05/04/99				ai.ManStep = PHASE1;
//DeadCode CSB 05/04/99				break;
//DeadCode CSB 05/04/99			}
//DeadCode CSB 05/04/99			case PHASE1:
//DeadCode CSB 05/04/99			{
//DeadCode CSB 05/04/99	
//DeadCode CSB 05/04/99				if  (	(!SubjectFacingTarget(ANGLES_15Deg))
//DeadCode CSB 05/04/99					 || (!TargetFacingSubject(ANGLES_15Deg))
//DeadCode CSB 05/04/99					)
//DeadCode CSB 05/04/99				{
//DeadCode CSB 05/04/99					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 05/04/99				}
//DeadCode CSB 05/04/99				AutoCalcPitch();
//DeadCode CSB 05/04/99				SimpleMoveToHdg (HdgIntercept);
//DeadCode CSB 05/04/99				if  (	(Range < METRES150)
//DeadCode CSB 05/04/99					&&	(ai.combatskill < SKILL_VETERAN)
//DeadCode CSB 05/04/99					&&	(ai.morale < MORALE_MEDIUM)
//DeadCode CSB 05/04/99					)
//DeadCode CSB 05/04/99				{
//DeadCode CSB 05/04/99					ai.desiredhdg = hdg + ANGLES_120Deg;
//DeadCode CSB 05/04/99					ai.ManStep = PHASE2;
//DeadCode CSB 05/04/99	
//DeadCode CSB 05/04/99				}
//DeadCode CSB 05/04/99				if (Range < METRES80)
//DeadCode CSB 05/04/99				{
//DeadCode CSB 05/04/99					ai.desiredhdg = hdg + ANGLES_120Deg;
//DeadCode CSB 05/04/99					ai.ManStep = PHASE2;
//DeadCode CSB 05/04/99	
//DeadCode CSB 05/04/99				}
//DeadCode CSB 05/04/99				break;
//DeadCode CSB 05/04/99			}
//DeadCode CSB 05/04/99			case PHASE2:
//DeadCode CSB 05/04/99			{
//DeadCode CSB 05/04/99	
//DeadCode CSB 05/04/99				AutoCalcPitch();
//DeadCode CSB 05/04/99				SimpleMoveToHdg (ai.desiredhdg);
//DeadCode CSB 05/04/99				if  (!SubjectFacingTarget(ANGLES_85Deg))
//DeadCode CSB 05/04/99				{
//DeadCode CSB 05/04/99					ai.ManStep = PHASE3;
//DeadCode CSB 05/04/99					SetManoeuvreTime (1000);
//DeadCode CSB 05/04/99	
//DeadCode CSB 05/04/99				}
//DeadCode CSB 05/04/99	
//DeadCode CSB 05/04/99				break;
//DeadCode CSB 05/04/99			}
//DeadCode CSB 05/04/99			case PHASE3:
//DeadCode CSB 05/04/99			{
//DeadCode CSB 05/04/99	
//DeadCode CSB 05/04/99				SimpleTightTurn (FT_500);
//DeadCode CSB 05/04/99				if 	(!ManoeuvreTimeLeft())
//DeadCode CSB 05/04/99				{
//DeadCode CSB 05/04/99					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 05/04/99				}
//DeadCode CSB 05/04/99	
//DeadCode CSB 05/04/99				break;
//DeadCode CSB 05/04/99			}
//DeadCode CSB 05/04/99		}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StayWithPrey
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	As target looses alt, stay until explosion or hits ground or alt <???
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleStayWithPrey ( )

{
	
	SWord	acroll_sign,reqroll;
	SWord	deltapitch;
	UWord	acroll_pos;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if  (		(!ManoeuvreTimeLeft())
					||	(World.Y < FT_700)
				)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			SimpleTightTurn (FT_500);


		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GainHeight
//Author		R. Hyde 
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleGainHeight ( )

{
	
	AirStrucPtr		unfriendly;	
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign,desiredaoa;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			unfriendly = *ai.unfriendly;
			if (	(unfriendly->ai.attacker == this)
				||	(World.Y > classtype->fightceiling)
				)
			{
				ai.manoeuvre=MANOEUVRE_SUSTAINEDTURN;
				SimpleSustainedTurn ();
				break;
			}
			SetManoeuvreTime (2000);
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
//##			if ((SWord) fly.turnrate > 0)
//			{
//		 		ai.desiredroll = ANGLES_20Deg;
//			}else
//			{
//		 		ai.desiredroll = ANGLES_340Deg;
//			}
		}
		case PHASE1:
		{
			PitchIntercept = ANGLES_10Deg;
			AutoCalcPitch();
			if(roll > 0)
				SimpleMoveToRoll(ANGLES_30Deg);
			else
				SimpleMoveToRoll(ANGLES_330Deg);

			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;

		}

	}

}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SplitS
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleSplitS ()

{
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			int groundlevel = Land_Scape.GetGroundLevel(this);
			if(World.Y - groundlevel < 150000)	//5000 ft
			{
				if(Math_Lib.rnd(1))
					ai.manoeuvre = MANOEUVRE_SCISSORS;
				else
 					ai.manoeuvre = MANOEUVRE_BREAKTURN;
				SetManoeuvreTime(0);
			}
			else
			{
				ai.desiredroll = ANGLES_180Deg;
 				SimpleMoveToThrust (100);
				ai.ManStep = PHASE1;
				if((this != Persons2::PlayerSeenAC) && (this != Persons2::PlayerGhostAC))
					fly.elevator = 0;
			}
		}
		case PHASE1:
		{
			deltaroll = (SWord) (ai.desiredroll - roll);
			SimpleMoveToRoll (ai.desiredroll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_10Deg)
			{
				ai.ManStep = PHASE2;
	 			SimpleMoveToThrust (0);
//rdh				ai.lastdeltapitch = ANGLES_0Deg;
				SetManoeuvreTime (1500);

			}
			break;
		}

		case PHASE2:
		{

			PitchIntercept = ANGLES_280Deg;
			AutoCalcPitch();
			if ( 		(!ManoeuvreTimeLeft())
					|| (    DesiredPitchChk (ANGLES_270Deg,ANGLES_20Deg)
						)										//RDH 24Jul96
				)
			{
	 			SimpleMoveToThrust (100);
				ai.manoeuvre = MANOEUVRE_SELECT;
			}


			break;
		}


	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ZoomandDrop
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleZoomandDrop ()

{
	SWord phase,deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;

	phase = (SWord) ai.ManStep;
	switch (phase)
	{
		case PHASE0:
		{
			ai.desiredroll = ANGLES_0Deg;
 			SimpleMoveToThrust (0);
			SetManoeuvreTime (500);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SimpleMoveToRoll (ai.desiredroll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_20Deg)
			{
				SetManoeuvreTime (500);
				ai.ManStep = PHASE2;
			}
			break;
		}
		case PHASE2:
		{
			PitchIntercept = ANGLES_70Deg;
			AutoCalcPitch();
			if (	(SimpleMoveToDesiredPitch (ANGLES_70Deg,ANGLES_10Deg))
				||	(!ManoeuvreTimeLeft())
				)
			{
				ai.ManStep = PHASE3;
 				SimpleMoveToThrust (100);
			}
		break;
		}

		case PHASE3:
		{
			if (SimpleMoveToDesiredPitch (ANGLES_315Deg,ANGLES_10Deg))
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}


	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiveAndZoom
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleDiveAndZoom ()

{
	SWord	deltapitch_pos,deltapitch_sign;
	SLong	temp_range;
	COORDS3D	target;
	SLong		t,actualrange;
	AirStrucPtr	unfriendly = *ai.unfriendly;
 	SWord		deltaroll;										//RDH 14Mar96
	SWord		easestickforward;
	ANGLES		local_PI;


	local_PI  = PitchIntercept;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
			SetManoeuvreTime (12000);
		}
		case PHASE1:
		{
 			if  (	(		(!ManoeuvreTimeLeft())
						||	((Range - (World.Y - ai.unfriendly->World.Y)) < ENGAGERANGE)
					)
					&&
					(SubjectFacingTarget(ANGLES_45Deg))
				 )
  			{
  				ai.ManStep = PHASE2;
				SetManoeuvreTime (5000);
  			}
   			if (local_PI << ANGLES_90Deg)
  			{
  				ai.manoeuvre = MANOEUVRE_SELECT;
  			}
 

			PitchIntercept = ANGLES_5Deg;
			AutoCalcPitch();
			SimpleMoveToHdg (HdgIntercept);
			break;
		}
		case PHASE2:
		{
			SimpleTurningFight();
			if  (			(!ManoeuvreTimeLeft())
					 ||
							(TargetOnSubjectTail(ANGLES_90Deg))
					 ||	
							(Range < METRES200)
				)
			{
			 	ai.ManStep = PHASE0;
				ai.manoeuvre=MANOEUVRE_ZOOM;
			}
 	
			break;
		}

	}

}

//DeadCode RDH 06Aug98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 06Aug98 //Procedure		TightTurn
//DeadCode RDH 06Aug98 //Author		R. Hyde 
//DeadCode RDH 06Aug98 //Date			//RDH 11Oct96
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Description	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Inputs		
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Returns	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //------------------------------------------------------------------------------
void AirStruc::SimpleTightTurn (SLong recovery_alt)
{
}
//DeadCode RDH 06Aug98 {
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	SWord	sinturn,costurn;
//DeadCode RDH 06Aug98 	SWord	turn;
//DeadCode RDH 06Aug98 	SLong	desiredroll,deltax,deltaz,delta; 
//DeadCode RDH 06Aug98 	SWord	deltapitch;
//DeadCode RDH 06Aug98 	COORDS3D	target;
//DeadCode RDH 06Aug98 	SLong		time;
//DeadCode RDH 06Aug98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 06Aug98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos;
//DeadCode RDH 06Aug98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 06Aug98 	SWord dhdg;
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	target.X = ai.unfriendly->World.X;
//DeadCode RDH 06Aug98 	target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 06Aug98 	target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 06Aug98 	InterceptandRange (&target);
//DeadCode RDH 06Aug98 	SimpleTightTurnSub (recovery_alt,target);
//DeadCode RDH 06Aug98 }
//DeadCode RDH 06Aug98 

//DeadCode RDH 06Aug98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 06Aug98 //Procedure		TightTurnSub
//DeadCode RDH 06Aug98 //Author		R. Hyde 
//DeadCode RDH 06Aug98 //Date			//RDH 11Oct96
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Description	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Inputs		
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Returns	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //------------------------------------------------------------------------------
//DeadCode RDH 06Aug98 void AirStruc::SimpleTightTurnSub (SLong recovery_alt,COORDS3D	target)
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 {
//DeadCode RDH 06Aug98 	SLong		time;
//DeadCode RDH 06Aug98 	SWord	sinturn,costurn;
//DeadCode RDH 06Aug98 	SWord	turn;
//DeadCode RDH 06Aug98 	SLong	desiredroll,deltax,deltaz,delta; 
//DeadCode RDH 06Aug98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 06Aug98 	SWord	deltapitch,maxroll,minroll;
//DeadCode RDH 06Aug98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos,targetroll,olddesiredroll_pos;
//DeadCode RDH 06Aug98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 06Aug98 	SWord dhdg;
//DeadCode RDH 06Aug98 	dhdg = (SWord) (hdg - HdgIntercept);
//DeadCode RDH 06Aug98 	Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		if (	(TargetFacingSubject(ANGLES_70Deg))
//DeadCode RDH 06Aug98 			&& 	(((SWord) PitchIntercept) > 0)
//DeadCode RDH 06Aug98 				)
//DeadCode RDH 06Aug98 		{
//DeadCode RDH 06Aug98 			PitchIntercept = ANGLES_0Deg;
//DeadCode RDH 06Aug98 		}	
//DeadCode RDH 06Aug98 		deltapitch = PitchIntercept - fly.cpitch;
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	if	(	(SubjectOnTargetTail(ANGLES_50Deg))
//DeadCode RDH 06Aug98 		&&	(SubjectFacingTarget(ANGLES_70Deg))
//DeadCode RDH 06Aug98 		&&	(Range < (WEAPONSRANGE-METRES20))
//DeadCode RDH 06Aug98 		)
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 		time = dhdg_pos /400;
//DeadCode RDH 06Aug98 		if (time > 20)
//DeadCode RDH 06Aug98 			time =20;
//DeadCode RDH 06Aug98 //##		turn = time * unfriendly->fly.turnrate/10;	//in s
//DeadCode RDH 06Aug98 //		turn = unfriendly->hdg + turn;
//DeadCode RDH 06Aug98 		delta = unfriendly->vel * time;		//cm/s
//DeadCode RDH 06Aug98 		Math_Lib.high_sin_cos((Angles)turn,sinturn,costurn);
//DeadCode RDH 06Aug98 		deltax = MULSHSIN(sinturn,delta,ANGLES_SHIFT);
//DeadCode RDH 06Aug98 		deltaz = MULSHSIN(costurn,delta,ANGLES_SHIFT);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		//calc lead position using this time
//DeadCode RDH 06Aug98 		target.X = ai.unfriendly->World.X + deltax;
//DeadCode RDH 06Aug98 		target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
//DeadCode RDH 06Aug98 		target.Z = ai.unfriendly->World.Z + deltaz;
//DeadCode RDH 06Aug98 		InterceptandRange (&target);
//DeadCode RDH 06Aug98 		dhdg = (SWord) (hdg - HdgIntercept);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		Math_Lib.Pos ((SWord)ai. desiredroll,olddesiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	}else
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		Math_Lib.Pos ((SWord)ai. desiredroll,olddesiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 		dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 06Aug98 	 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	}
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	Math_Lib.Pos ((SWord)ai. desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	if (	(deltapitch > ANGLES_2Deg)
//DeadCode RDH 06Aug98 		&&	(!(TargetFacingSubject(ANGLES_20Deg)))
//DeadCode RDH 06Aug98 			)
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 		if (olddesiredroll_pos <= desiredroll_pos)
//DeadCode RDH 06Aug98 		{
//DeadCode RDH 06Aug98 			desiredroll_pos = olddesiredroll_pos - 64;
//DeadCode RDH 06Aug98 			if (desiredroll_pos > ANGLES_20Deg)
//DeadCode RDH 06Aug98 				ai.desiredroll = (Angles) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 		}
//DeadCode RDH 06Aug98 	}
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	Math_Lib.Pos ((SWord)ai. desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 	if (	(deltapitch < ((SWord)ANGLES_350Deg))
//DeadCode RDH 06Aug98 		&& (desiredroll_pos >= MAXCOMBATROLL)
//DeadCode RDH 06Aug98 			)
//DeadCode RDH 06Aug98 			{
//DeadCode RDH 06Aug98 				desiredroll_pos = ANGLES_180Deg - (ANGLES)MAXCOMBATROLL;
//DeadCode RDH 06Aug98 				ai.desiredroll = (Angles) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 			}
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	if ( target.Y >= recovery_alt)
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 		deltapitch = PitchIntercept - fly.cpitch;
//DeadCode RDH 06Aug98 		SimpleTightTurnSubSub(deltapitch);
//DeadCode RDH 06Aug98 	}else
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		SLong groundlevel = _Collide.LowestSafeAlt(this,
//DeadCode RDH 06Aug98 											this->pitch,
//DeadCode RDH 06Aug98 											this->roll);//RDH 21Oct96
//DeadCode RDH 06Aug98 		if ((World.Y - groundlevel) < FT_100)
//DeadCode RDH 06Aug98 		{
//DeadCode RDH 06Aug98 			//## attempt to disengage
//DeadCode RDH 06Aug98 			SimpleMoveToThrust (100);
//DeadCode RDH 06Aug98 			PitchIntercept = ANGLES_5Deg;
//DeadCode RDH 06Aug98 			AutoCalcPitch();
//DeadCode RDH 06Aug98 			SimpleMoveToRoll (ANGLES_0Deg);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		}
//DeadCode RDH 06Aug98 	}
//DeadCode RDH 06Aug98 }
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 06Aug98 //Procedure		SimpleTightTurnSubSub
//DeadCode RDH 06Aug98 //Author		R. Hyde 
//DeadCode RDH 06Aug98 //Date			//RDH 11Oct96
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Description	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Inputs		
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Returns	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //------------------------------------------------------------------------------
void AirStruc::SimpleTightTurnSubSub (SWord deltapitch)
{
	SLong	desiredroll; 
	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos;
	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
		//now do pitch
		PitchIntercept = (Angles)deltapitch + fly.cpitch;
		{
			if (	(deltapitch > 0)
				&&	((SWord) fly.cpitch < ANGLES_15Deg)	//sustainable max climbrate
				)
			{
				AutoCalcPitch();
		
			}else
			{
				if (	(deltapitch <= 0)
					)
				{//can push down
					AutoCalcPitch();
				}else
				{
					PitchIntercept = ANGLES_0Deg;
					AutoCalcPitch();
				}
			}
			Math_Lib.Pos ((SWord)ai.desiredroll,desiredroll_pos,desiredroll_sign);
			
			if (	(fly.cpitch > ANGLES_5Deg)
				&& (desiredroll_pos > ANGLES_20Deg)
				&& (deltapitch > 0)
					)
			
			{
				if (fly.cpitch > ANGLES_15Deg)
				{
						desiredroll_pos = ANGLES_20Deg;
				}else
				{
					desiredroll = ANGLES_20Deg +  (desiredroll_pos - ANGLES_20Deg) *
								(ANGLES_15Deg - fly.cpitch) / ANGLES_15Deg;
					desiredroll_pos = (Angles) desiredroll;
				}
				ai.desiredroll = (Angles) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
			}
			SimpleMoveToRoll (ai.desiredroll);
		}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleCalcVel
//Author		R. Hyde 
//Date			Fri 25 Oct 1996
//
//Description	rewritten to use the accel calculated via Ps 3/9/98
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleCalcVel ()
{

   		Float	accel, fvel;
		bool positive = true;
		SWord		tvel;
		accel = CalcSimpleAccel ();
		fvel	=  accel * Timer_Code.FRAMETIME * 0.1;
		if (fvel < 0)
		{
			positive = false;
			fvel = -fvel;
		}
		tvel = fvel;
		fvel = 65536 * (fvel - tvel);
		int rnd = Math_Lib.rnd();
		if (fvel > rnd)
			tvel++;
		if (!positive)
			tvel = -tvel;
		vel = vel + tvel;



//	SWord thrust;
//	SLong reqvel;
//
//	thrust = fly.thrustpercent;
//	if (thrust > 10)
//	{
//		reqvel = classtype->maxvel*thrust*thrust/10000;
//	}else
//	{
//DeadCode RDH 27Oct96 		reqvel = classtype->bestclimbvel;
//		reqvel = MPH30;
//	}
//	if (fly.cpitch >> ANGLES_90Deg)
//	{
//		reqvel = classtype->bestclimbvel + (classtype->maxvel - classtype->bestclimbvel) *
//									(SWord) (classtype->bestclimbpitch - pitch)/(ANGLES)classtype->bestclimbpitch;
//	}
//	CalcVelSub (reqvel);
//	//if we want to go slow then have a double decell
//	if (	(reqvel == MPH30)
//		&&	(Range <METRES70)
//		)
//		CalcVelSub (reqvel);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleMoveToThrust
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleMoveToThrust (SWord thrust)

{
	fly.thrustpercent =  thrust * thrust / 100;;

//FC code:
//	SLong	reqvel;
//	SLong	accel;
//	SWord	deltavel,deltavel_sign;	
//	UWord	deltavel_pos;
//	SLong	climb_vel;
//
//	if  (thrust == -100)
//	{
//		if (fly.thrustpercent ==0)
//			fly.thrustpercent =  MAXAUTOTHRUST;
//	}
//	elseif  (thrust == -1)
//	{
//		if (fly.thrustpercent ==MAXAUTOTHRUST)
//			fly.thrustpercent =  0;
//	}
//	else
//		fly.thrustpercent =  thrust;
//	if (fly.thrustpercent > MAXAUTOTHRUST)
//		fly.thrustpercent = MAXAUTOTHRUST;	

}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeldedWingMan
//Author		R. Hyde							Craig Beeston
//Date			Mon 2 Mar 1998					Tue 27 Apr 1999
//
//Description	Formation flag not set so a/c can spot
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleWeldedWingMan()
{
	
//	stick to the leaders tail, range about 1000ft and weave
//	However for low morale bring wingman closer
//	For very low morale it should appear as if he is trying to stay in formation

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			fly.thrustpercent = ThrustfromFF();
			ai.ManStep = PHASE1;
			SetManoeuvreTime (3000);

		}
		case PHASE1:
		{
			if (WeldedWingSixOK())
			{
				if (		(fly.leadflight)					
						&&	 (fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER)
					)//force manoeuvre to allow disengage
						ai.manoeuvre = MANOEUVRE_SELECT;
				else if (!leader)
					ai.manoeuvre = MANOEUVRE_SELECT;
				else
				{
					Bool PullHard = FALSE;
					COORDS3D	target;
					SWord	reqdeltahdg,reqdeltahdg_sign;
					UWord	reqdeltahdg_pos;
					SWord	reqdeltapitch,reqdeltapitch_sign;
					UWord	reqdeltapitch_pos;

					target = leader->World; 									//JIM 02Aug96
					target.Y +=	60 * ai.morale;//FT_500;		Top Moral gives 500 ft

					InterceptandRange(&target);


					reqdeltahdg   =	HdgIntercept - hdg;
					reqdeltapitch =	PitchIntercept - pitch;
					Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
					Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
					
					SWord DesRoll	= 0;
					SWord IdealRoll = 0;
					if(reqdeltapitch != 0)
						IdealRoll = Math_Lib.arctan(reqdeltahdg, reqdeltapitch);
					else
					{
						if(reqdeltahdg > 0) IdealRoll += ANGLES_90Deg;
						if(reqdeltahdg < 0) IdealRoll -= ANGLES_90Deg;
					}

					if((reqdeltahdg_pos > ANGLES_10Deg) || (reqdeltapitch_pos > ANGLES_10Deg))
					{
						DesRoll = IdealRoll;
						PullHard = TRUE;
					}
					else
					{
						if((leader->roll > MAXCOMBATROLL) || (-leader->roll > MAXCOMBATROLL))
						{
							DesRoll = IdealRoll;
							PullHard = TRUE;
						}
						else
						{
							DesRoll = leader->roll;
							DesRoll += 4 * reqdeltahdg;
							MODLIMIT(DesRoll, ANGLES_90Deg);
							PullHard = FALSE;
						}
					}
					SimpleMoveToRoll(DesRoll);

					if(PullHard)
					{
						SWord RollError = (SWord)roll - IdealRoll;
						if((RollError < ANGLES_90Deg) && (-RollError < ANGLES_90Deg))
						{
							SWord sin_roll, cos_roll;
							Math_Lib.high_sin_cos(roll, sin_roll, cos_roll);
	//DeadCode CSB 01/06/99							FP MaxDeltaPitch = (FP)classtype->maxpitchrate * (FP)Timer_Code.FRAMETIME / 100.0 / 32768.0;
							FP MaxDeltaPitch = (FP)CalcMaxPitchRate() * (FP)Timer_Code.FRAMETIME / (100.0 * 32768.0);
							FP MaxDeltaYaw   = MaxDeltaPitch * sin_roll;
							MaxDeltaPitch	 = MaxDeltaPitch * cos_roll;

							SWord	maxdeltapitch_sign, maxdeltayaw_sign;
							UWord	maxdeltapitch_pos,  maxdeltayaw_pos;
							Math_Lib.Pos((SWord)MaxDeltaPitch, maxdeltapitch_pos, maxdeltapitch_sign);
							Math_Lib.Pos((SWord)MaxDeltaYaw  , maxdeltayaw_pos,   maxdeltayaw_sign);
							FP factor1 = 1, factor2 = 1;
							if(maxdeltapitch_pos > reqdeltapitch_pos) factor1 = (FP)reqdeltapitch_pos / (FP)maxdeltapitch_pos;
							if(maxdeltayaw_pos   > reqdeltahdg_pos)   factor2 = (FP)reqdeltahdg_pos / (FP)maxdeltayaw_pos;
							if(factor1 > factor2) factor1 = factor2;
							pitch += SWord((FP)MaxDeltaPitch * (FP)factor1);
							hdg   += SWord((FP)MaxDeltaYaw   * (FP)factor1);
						}
						fly.cpitch = pitch;

						hdg -= (Angles) CalcHdg ();	//This means that all the heading change is done inside this routine
					}
					else
						AutoCalcPitch();

					UWord DesRange = 256 * ai.morale;	// up to 650 metres
					if(DesRange < WEAPONSRANGE) DesRange = WEAPONSRANGE;

					FP DeltaVel = (Range - DesRange) * 0.025;
					MODLIMIT(DeltaVel, 200);
					UWord DesVel = leader->vel + DeltaVel;
					if(vel > DesVel)
					{
						fly.thrustpercent = 0;
						if(vel > leader->vel + 200) vel = leader->vel + 200;
					}
					else
					{
						fly.thrustpercent = 200;
						if(vel < leader->vel - 200) vel = leader->vel - 200;
					}
					
	//#define PRINT_WWM_DATA
	#ifdef PRINT_WWM_DATA
	PrintVar(0, 1, "D_Range %.1f ", (FP)(DesRange / 100.0));
	PrintVar(0, 2, "Range   %.1f ", (FP)(Range / 100.0));
	PrintVar(0, 3, "Pitch   %.1f ", (FP)((SWord)pitch / 182.04));
	PrintVar(0, 4, "Pitch_I %.1f ", (FP)((SWord)PitchIntercept / 182.04));
	PrintVar(0, 5, "Headg   %.1f ", (FP)((SWord)hdg / 182.04));
	PrintVar(0, 6, "Headg_I %.1f ", (FP)((SWord)HdgIntercept / 182.04));
	PrintVar(0, 8, "D_Pitch %.1f ", (FP)(reqdeltapitch / 182.04));
	PrintVar(0, 9, "D_Headg %.1f ", (FP)(reqdeltahdg / 182.04));
	PrintVar(0,10, "DesRoll %.1f ", (FP)(DesRoll / 182.04));

	if(PullHard) PrintString(0, 12, "PULL HARD");
	else		 PrintString(0, 12, "         ");

	PrintVar(0,14, "L_Vel   %.1f ", (FP)(leader->vel / 10));
	PrintVar(0,15, "DesVel  %.1f ", (FP)(DesVel / 10));
	PrintVar(0,16, "Vel     %.1f ", (FP)(vel / 10));

	#endif
				}
			}
		}
	}
	
}				
/*	switch (ai.ManStep)
	{
		case PHASE0:
		{
			fly.thrustpercent = ThrustfromFF();
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if (!leader)
				ai.manoeuvre = MANOEUVRE_SELECT;
			else
			{
				COORDS3D target;
				target = leader->World; 									//JIM 02Aug96
				target.Y +=	FT_500;
				InterceptandRange(&target);

				SWord reqdeltahdg, reqdeltahdg_sign;
				UWord reqdeltahdg_pos;
				reqdeltahdg = HdgIntercept - hdg;
				Math_Lib.Pos(reqdeltahdg, reqdeltahdg_pos, reqdeltahdg_sign);

				SWord reqdeltapitch, reqdeltapitch_sign;
				UWord reqdeltapitch_pos;
				reqdeltapitch = (SWord)PitchIntercept - (SWord)pitch;
				Math_Lib.Pos (reqdeltapitch, reqdeltapitch_pos, reqdeltapitch_sign);

				
				hdg -= (Angles) CalcHdg ();

				if((reqdeltahdg_pos < ANGLES_1Deg) && (reqdeltapitch_pos < ANGLES_1Deg))
					SimpleMoveToRoll(ANGLES_0Deg);
				else
				{
					if(reqdeltahdg_pos < ANGLES_180Deg)
					{
						SWord DesRoll = 0;
						if(reqdeltapitch != 0)
							DesRoll = Math_Lib.arctan(reqdeltahdg, reqdeltapitch);
						else
						{
							if(reqdeltahdg > 0) DesRoll += ANGLES_90Deg;
							if(reqdeltahdg < 0) DesRoll -= ANGLES_90Deg;
						}
						SimpleMoveToRoll(DesRoll);

#define PRINT_WWM_DATA
#ifdef PRINT_WWM_DATA
PrintVar(0, 2, "Range   %.0f ", (FP)(Range / 100.0));
PrintVar(0, 3, "Pitch   %.0f ", (FP)((SWord)pitch / 182.04));
PrintVar(0, 4, "Pitch_I %.0f ", (FP)((SWord)PitchIntercept / 182.04));
PrintVar(0, 5, "Headg   %.0f ", (FP)((SWord)hdg / 182.04));
PrintVar(0, 6, "Headg_I %.0f ", (FP)((SWord)HdgIntercept / 182.04));
PrintVar(0, 8, "D_Pitch %.0f ", (FP)(reqdeltapitch / 182.04));
PrintVar(0, 9, "D_Headg %.0f ", (FP)(reqdeltahdg / 182.04));
PrintVar(0,10, "DesRoll %.0f ", (FP)(DesRoll / 182.04));
#endif
						SWord rollerror = DesRoll - (SWord)roll;
						if((rollerror < ANGLES_45Deg) && (-rollerror < ANGLES_45Deg))
						{
							SWord sin_roll, cos_roll;
							Math_Lib.high_sin_cos(roll, sin_roll, cos_roll);
							FP MaxDeltaPitch = (FP)classtype->maxpitchrate * (FP)Timer_Code.FRAMETIME / 100.0 / 32768.0;
							FP MaxDeltaYaw   = MaxDeltaPitch * sin_roll;
							MaxDeltaPitch	 = MaxDeltaPitch * cos_roll;

	//DeadCode CSB 28/04/99							SWord	maxdeltapitch_sign, maxdeltayaw_sign;
	//DeadCode CSB 28/04/99							UWord	maxdeltapitch_pos,  maxdeltayaw_pos;
	//DeadCode CSB 28/04/99							Math_Lib.Pos((SWord)MaxDeltaPitch, maxdeltapitch_pos, maxdeltapitch_sign);
	//DeadCode CSB 28/04/99							Math_Lib.Pos((SWord)MaxDeltaYaw  , maxdeltayaw_pos,   maxdeltayaw_sign);
							FP factor1 = 1, factor2 = 1;
	//DeadCode CSB 28/04/99							if(maxdeltapitch_pos > reqdeltapitch_pos) factor1 = reqdeltapitch_pos / maxdeltapitch_pos;
	//DeadCode CSB 28/04/99							if(maxdeltayaw_pos   > reqdeltahdg_pos)   factor2 = reqdeltahdg_pos / maxdeltayaw_pos;
	//DeadCode CSB 28/04/99							if(factor1 > factor2) factor1 = factor2;
							pitch += SWord((FP)MaxDeltaPitch * (FP)factor1);
							hdg   += SWord((FP)MaxDeltaYaw   * (FP)factor1);
							fly.cpitch = pitch;
						}
					}
					else 
					{
						AutoCalcPitch();				
						SimpleMoveToHdg(HdgIntercept);
					}
				}				
//DeadCode CSB 28/04/99					InterceptandRange (&leader->World);
				vel = leader->vel;
				if (Range < DANGERRANGE)
					vel -= 100;//CalcVelAlt(0);
				else
					vel += 100;//CalcVelAlt(32000);
			}

		}
	}


}
*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BailOut				
//Author		R. Hyde 			CSB
//Date			Tue 3 Mar 1998		Sun 28 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleBailOut()
{
//pilot ejects or bails out depending on ac type
//ac in slow turning dive

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust (0);	 
			SimpleMoveToRoll (0);
			SimpleMoveToDesiredPitch (ANGLES_0Deg, ANGLES_0Deg);
			SetManoeuvreTime(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SimpleMoveToThrust (0);	 
			SimpleMoveToRoll (0);
			if(!TimeLeft())
			{
				Trans_Obj.LaunchCanopyEject(this,*mobileitem::currworld);
				AirStrucPtr	unfriendly = *ai.unfriendly;
				unfriendly->ai.unfriendly = NULL;
				ai.ManStep = PHASE2;
				SetManoeuvreTime(100);
			}
			break;
		}
		case PHASE2:
		{
			SimpleMoveToRoll (0);
			SimpleMoveToDesiredPitch (ANGLES_0Deg, ANGLES_0Deg);
			if(!TimeLeft())
			{
				Trans_Obj.LaunchParachute(this,*mobileitem::currworld);
				movecode = AUTO_DEATHSEQUENCE;
			}
		}
	}

//DeadCode CSB 30/03/99		switch (ai.ManStep)
//DeadCode CSB 30/03/99		{
//DeadCode CSB 30/03/99			case PHASE0:
//DeadCode CSB 30/03/99			{
//DeadCode CSB 30/03/99				SimpleMoveToThrust (0);
//DeadCode CSB 30/03/99				SetManoeuvreTime (300);
//DeadCode CSB 30/03/99				ai.ManStep = PHASE1;
//DeadCode CSB 30/03/99			}
//DeadCode CSB 30/03/99			case PHASE1:
//DeadCode CSB 30/03/99			{
//DeadCode CSB 30/03/99				SimpleMoveToRoll (0);
//DeadCode CSB 30/03/99				SimpleMoveToDesiredPitch (ANGLES_0Deg, ANGLES_0Deg);
//DeadCode CSB 30/03/99				if  (!ManoeuvreTimeLeft())
//DeadCode CSB 30/03/99				{
//DeadCode CSB 30/03/99					Trans_Obj.LaunchParachute(this,*mobileitem::currworld);
//DeadCode CSB 30/03/99					ai.ManStep = PHASE2;
//DeadCode CSB 30/03/99					ai.desiredroll = - (ANGLES)ANGLES_45Deg +
//DeadCode CSB 30/03/99	 								(Angles)(ANGLES_90Deg * Math_Lib.rnd(2)); 
//DeadCode CSB 30/03/99					AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 30/03/99					unfriendly->ai.unfriendly = NULL;
//DeadCode CSB 30/03/99					movecode = AUTO_DEATHSEQUENCE;
//DeadCode CSB 30/03/99				}
//DeadCode CSB 30/03/99			}
//DeadCode CSB 30/03/99		}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LineAbreast
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleLineAbreast()
{
	//only followers go line abreast. We don't link flights

	if (!leader) 
	{//leader, do same as roundabout, get height, dive and then zoom
	 //at end of zoom, choose manoeuvre based on firsttactic
			ai.ManStep = PHASE0;
			ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;			
	}else
	{//follower
		if (		(Range < WEAPONSRANGE)
				&&	(information)
			)
		{
			FireABullet(30);
		}
		{
			switch (ai.ManStep)
			{
				case PHASE0:
				{
		 			SimpleMoveToThrust (100);
					ai.ManStep = PHASE1;
				}
				case PHASE1:
				{

					
					if (!leader)
						ai.manoeuvre = MANOEUVRE_SELECT;					//if no leader break manoeuvre
					else
					{
						AutoFollowWpWing();

					}

				}
			}
		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scatter
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleScatter()
{
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Pincer
//Author		R. Hyde 
//Date			Thu 5 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimplePincer()
{
  	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (2000);
			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
			AirStrucPtr	unfriendly = *ai.unfriendly;
			SWord	sinbearing,cosbearing;
			SLong	range = METRES1200;
			ANGLES brg;

			brg = (Angles)((SWord)ai.desiredhdg + (SWord)unfriendly->hdg);
			Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);

			despos = unfriendly->World; 			
			despos.X += MULDIVSIN (sinbearing,range,ANGLES_FRACT);
			despos.Z += MULDIVSIN (cosbearing,range,ANGLES_FRACT);
			despos.Y += FT_500;
			InterceptandRange (&despos);

			PitchIntercept = PitchIntercept;
			AutoCalcPitch();
			SimpleMoveToHdg (HdgIntercept);

			if	(	(		(!ManoeuvreTimeLeft())
						&&	(Range < COMBATRANGE)
					)
					||
					(!SubjectFacingTarget(ANGLES_80Deg))
				 )

			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MultiWave
//Author		R. Hyde 
//Date			Wed 18 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleMultiWave()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (3000);
			ai.ManStep = PHASE1;
   		}
		case PHASE1:
		{
			PitchIntercept = ANGLES_10Deg;
			AutoCalcPitch();
			SimpleMoveToHdg (HdgIntercept);

			if  (		(!ManoeuvreTimeLeft())
					&&	(Range < ENGAGERANGE)
				)
					ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LeadPursuit
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.63
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleLeadPursuit()
{
//	ifcombatakill high
//		turn in parallel plane so that target still visible
//
//	calc ideal lead
//		could base calc on maintaining collision course(hdg-hdgintercept?)
//	actual lead depends also on skill
//
// end after x secs or within DANGERRANGE
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LagPursuit
//Author		R. Hyde 
//Date			Tue 10 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleLagPursuit()
{
//
//aim for a point off target's tail
//
//
//	acutal lag depends also on skill
//
//
//
// end after x secs or when go behind traget's tail
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Circumvent
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleCircumvent()
{
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecoyActive
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//rdhvoid	AirStruc::SimpleDecoyActive()
//{
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecoyPassive
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//rdhvoid	AirStruc::SimpleDecoyPassive()
//{
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RoundAbout
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleRoundAbout()
{
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust(ThrustfromFF());
			SetManoeuvreTime (1500);
 			ai.desiredroll = -(ANGLES)ANGLES_60Deg +
					(Angles)(ANGLES_120Deg * Math_Lib.rnd(2)); 


			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord desroll = ai.desiredroll;
			UWord desroll_pos;
			SWord desroll_sign;
			Math_Lib.Pos (desroll,desroll_pos,desroll_sign);
			if	(SubjectFacingTarget(ANGLES_45Deg))
			//when facing unfriendly unroll to move towards it
				desroll_pos = desroll_pos/2;
			else
				desroll_pos = desroll_pos;
			if (desroll_sign==MathLib::NEGATIVE)
				desroll_pos = -desroll_pos;
			desroll = desroll_pos;
			SimpleMoveToRoll ((Angles)desroll);

			PitchIntercept = BestClimbAngle();
			AutoCalcPitch ();
 			if  (		((Range - (World.Y - ai.unfriendly->World.Y)) < ENGAGERANGE)
					&&	((World.Y - ai.unfriendly->World.Y) > FT_3000)
				)
			{
 		    	ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
			}

		}
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SplitManoeuvre
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleSplitManoeuvre()
{


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
			PitchIntercept = ai.desiredpitch;
			AutoCalcPitch();
			SimpleMoveToHdg (ai.desiredhdg);
			if  (		(ChkAtDesiredHdg (ai.desiredhdg,ANGLES_40Deg))
					||	(!ManoeuvreTimeLeft())
				)
			{
				RndVal	rndnum = Math_Lib.rnd();
				if (		(rndnum > RND50PC)
						&&	(ai.morale < MORALE_MEDIUM)
					)
				{
					ai.ManStep = PHASE0;
					ai.manoeuvre = MANOEUVRE_EXTENSION;
				}else
					ai.manoeuvre = MANOEUVRE_SELECT;
			}

		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HeadOn
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	Theoretically no offset, 
//				However use a little to avoid collision
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleHeadOn ( )
{
//use desiredpitch and desiredhdg to determine offset
// distance = 2 WINGSPANS
	//just pass to the side
	//poor pilots may turn too early
	//good pilots may turn early
	//on passing pilot skill will dtermine action

	AirStrucPtr	unfriendly = *ai.unfriendly;

	SLong temp_range;
	temp_range = Range; 	
	COORDS3D	target;
	SWord c,s;
	SWord newhdg;
	UByte	FF = FlyingFactor();

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			InterceptandRange(ai.unfriendly);
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (2000);
			SWord dhdg = HdgIntercept - hdg;
			if ((dhdg) > 0)
				ai.desiredhdg = ANGLES_90Deg;
			else
				ai.desiredhdg = ANGLES_270Deg;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			InterceptandRange(ai.unfriendly);
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca) PitchIntercept = bca;
			AutoCalcPitch();

			ANGLES desiredhdg = ai.desiredhdg;
			ANGLES unfHdgIntercept = HdgIntercept;
			SLong	unfRange = Range;
			newhdg = unfriendly->hdg + ai.desiredhdg;

			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((METRES30 * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((METRES30 * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - desiredhdg;
		 	ANGLES reqroll = (Angles)FindRequiredRoll (reqdeltahdg,CombatReqBankData);

			int decisionpoint = Math_Lib.rnd(2);

			if  (		(Range < (2 * BREAKTURNRADIUS ))
					&&	(FF < 200)
				)
			{
				if (decisionpoint)
				{
					if (FF < 90)
					{
						ai.manoeuvre = MANOEUVRE_PANICTURN;
						ai.ManStep = PHASE0;
					}else  
					{
						ai.manoeuvre = MANOEUVRE_BREAKTURN;
						ai.ManStep = PHASE0;
					}
				}else
				{
					ai.ManStep = PHASE2;
				}

			}else if	(		(Range < BREAKTURNRADIUS)
							
						)
			{
				if (decisionpoint)
				{
					ai.manoeuvre = MANOEUVRE_BREAKTURN;
					ai.ManStep = PHASE0;
				}else
				{
					ai.desiredhdg = ai.desiredhdg  + ANGLES_180Deg;
					ai.ManStep = PHASE2;
				}
			}

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE2:
		{
			InterceptandRange(ai.unfriendly);
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca ) PitchIntercept = bca;
			AutoCalcPitch();

			ANGLES desiredhdg = ai.desiredhdg;
			ANGLES unfHdgIntercept = HdgIntercept;
			SLong	unfRange = Range;
			newhdg = unfriendly->hdg + ai.desiredhdg;

			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((METRES30 * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((METRES30 * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - ai.desiredhdg;
		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			SimpleMoveToRoll((Angles)reqroll);

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			if	(SubjectOnTargetTail(ANGLES_80Deg))
			{
				if	(		(ai.unfriendly == Manual_Pilot.ControlledAC2)
						&&	(((AirStruc*)ai.unfriendly)->Follower())
					)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEADON, MSG_HEADON, ((AirStruc*)ai.unfriendly)->Follower(), this, ((AirStruc*)ai.unfriendly)));

				int startpoint = Math_Lib.rnd(2);
				ai.ManStep = PHASE0;
				if (FF < 90)
				{
					if (startpoint)
						ai.manoeuvre = MANOEUVRE_JINK;
					else
						ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
				}else if (FF < 200)
				{
					if (startpoint)
							ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
					else
							ai.manoeuvre = MANOEUVRE_EXTENSION;
				}else 
				{
					if (startpoint)
							ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
					else
							ai.manoeuvre = MANOEUVRE_BREAKTURN;
				}
			}
		}
	}
	
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LineAstern
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleLineAstern()
{
//
//use leader's unfriendly
//also use leader's phase
//Phase 0: stay out of way until separation exceeds say 400m
//
//phase 1: if leader 
//				highest speed dive down to target
//			else
//				follow using formation data
//phase 2: when leader in DANGERRANGE
//				do highest speed dive down to target
//			AutoShoot() will do firing	(avoid firing at buddy)
//phase 2:	at 200 yards, zoom climb
//				success depends on flyingskill
//				will break out of manoeuvre if attacked, damaged, winchester, bingo
//phase 3: establish circle around target, go to phase 0				
//
	if (!leader) 
	{//leader, do same as roundabout, get height, dive and then zoom
	 //at end of zoom, choose manoeuvre based on firsttactic
			ai.ManStep = PHASE0;
			ai.manoeuvre = MANOEUVRE_ROUNDABOUT;			
	}else
	{//follower
		if (Range < 2 * WEAPONSRANGE)
		{
			ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
			ai.ManStep = PHASE0;
		}
		else
		{
			switch (ai.ManStep)
			{
				case PHASE0:
				{
//DeadCode CSB 05/07/99						MOD.Rudder = 0;
					SimpleMoveToThrust (ThrustfromFF());
					ai.ManStep = PHASE1;
//DeadCode CSB 05/07/99						ACM.maxdeltaforclosework = 0.0;
				}
				case PHASE1:
				{
					if (!leader)
						ai.manoeuvre = MANOEUVRE_SELECT;					//if no leader break manoeuvre
					else
					{
 						COORDS3D	target;
						AirStrucPtr MyLeader = Leader();
						for(;;)
						{
							AirStrucPtr Foll = MyLeader->Follower();
							if(Foll == this)
								break;			 
							MyLeader = Foll;
						}
 						target = MyLeader->World; 
						target.X += 10 * MyLeader->velx;
						target.Y += 10 * MyLeader->vely;
						target.Z += 10 * MyLeader->velz;
 						InterceptandRange(&target);

						AutoCalcPitch();
						SWord DeltaHdg = HdgIntercept - hdg;
						if((DeltaHdg > ANGLES_0Deg) && (DeltaHdg < ANGLES_HalfDeg))
							HdgIntercept = hdg + ANGLES_HalfDeg;
						if((-DeltaHdg > ANGLES_0Deg) && (-DeltaHdg < ANGLES_HalfDeg))
							HdgIntercept = hdg - ANGLES_HalfDeg;

						CalcHdgRoll();
//DeadCode CSB 05/07/99							if( roll > ANGLES_60Deg) roll = ANGLES_60Deg;
//DeadCode CSB 05/07/99							if(-roll > ANGLES_60Deg) {roll = ANGLES_60Deg; roll = -roll;}
//DeadCode CSB 05/07/99							Float fpitch, fhdg;
//DeadCode CSB 05/07/99							SWord reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
//DeadCode CSB 05/07/99							if  (		(	(fpitch < ACM.maxdeltaforclosework)
//DeadCode CSB 05/07/99										&&	(fpitch > -ACM.maxdeltaforclosework)
//DeadCode CSB 05/07/99										&&	(fhdg < ACM.maxdeltaforclosework)
//DeadCode CSB 05/07/99										&&	(fhdg > -ACM.maxdeltaforclosework)
//DeadCode CSB 05/07/99										)
//DeadCode CSB 05/07/99								)
//DeadCode CSB 05/07/99							{
//DeadCode CSB 05/07/99								TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode CSB 05/07/99							}else
//DeadCode CSB 05/07/99							{
//DeadCode CSB 05/07/99								ANGLES rroll;
//DeadCode CSB 05/07/99								rroll = (Angles)(reqroll + roll);
//DeadCode CSB 05/07/99								ACM.Roll (rroll);
//DeadCode CSB 05/07/99								ACM.ZeroSpecificPower();
//DeadCode CSB 05/07/99							}
						SLong DesVel = MyLeader->vel;
						Range -= MyLeader->vel * 10;
						if (Range < METRES200)
							DesVel -= 100;
 						else
						{
							SLong DeltaVel = (Range - METRES400) / 10;
							MODLIMIT(DeltaVel, 100);
							DesVel += DeltaVel;
						}
						if(DesVel > vel) SimpleMoveToThrust(200);
						else			 SimpleMoveToThrust(0);	

					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShootTooEarly
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SimpleShootTooEarly()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LagRoll
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	Ref1.67..	
//				manoeuvre incorporates barrel roll attack(1.69..)
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleLagRoll()
{
//maintain throttle
//roll towards unfriendly for 10-20deg hdg (f(AOT))
//go upside down
//climb to loose speed to corner speed
//exit manoeuvre when unfriendly goes behind or time out

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExtensionManoeuvre
//Author		R. Hyde 
//Date			Thu 5 Mar 1998
//
//Description	1.23
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleExtensionManoeuvre()
{
//attempt to get to extend range to ENGAGERANGE safely
//this is to try to escape
//or get distance to try again
//if at same level
//	good mig pilots should go up
//	good us pilots should go down
//if higher than bogey
//	
//
//ref1.70
//if turning good pilots will initially unload and
//retain roll to disguise manoeuvre 
//
//initially aircraft could be closing

}
void	AirStruc::SimpleDivingSpin()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReverseTurn
//Author		R. Hyde 
//Date			Thu 5 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleReverseTurn()
{
//	DesiredRoll = opposite of existing
//	Move to desired and hold for 3 secs
//	if (good)
//		out of plane
//	Close brakes if open at end of manoeuvre(used in selfasbait())
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelfAsBait
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	Ref19
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleSelfAsBait()
{
//
//let bandit out turn you
//just as he get lead, pop brakes
//goto RevereTurn
//
//this could be where bandit is on your tail, wait for him to get close 
//before turning
//keep buddy in combat spread so that you can sandwich him
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Jink
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleJink()
{
//
//fast 90 deg roll
//hard push or pull on stick
//hold for 2-3 secs
//
//flyingability determines rollrate and stick push pull
//combatablity determines length of manoeuvre
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakTurn
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//				Maximum performance turn towards unfriendly
//				Aim for corner speed (see summary at top of acmman.cpp)
//				When quoted as IAS, corner speed is practically a constant
//				cornerspeed should be part of the planetype
//				corner speed occurs at max g allowed for ac
//				max g should be part of the planetype 
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleBreakTurn()
{
//	roll = cos -1 (1/maxg)
//ability to reach roll = f(flyingskill)
//ability to hold corner vel = f(flyingskill)
//	option to nose down to keep speed up and nose up to reduce speed
//hold for 4-5 secs
//
//low morale gives a very lazy turn
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LazyTurn
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleLazyTurn()
{
//
//	Choose a roll 10-40deg
//		= f(morale)
//	continue on turn for 10s
//	if (ai.morale > MORALE_GOOD)
//		if (Range < WEAPONS)
//			end manoeuvre
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Break180
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.26
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleBreak180()
{
//roll 180
//pull hard until pitch 45 deg down
//slowly unroll for x secs
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakLow
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleBreakLow()
{
//decide which way to roll to go down
//roll 90
//pull hard until pitch 45 deg down
//slowly unroll for x secs
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakHigh
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleBreakHigh()
{
//decide which way to roll to go up
//roll 90
//pull hard until pitch 45 deg up
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Break90
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.27
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleBreak90()
{
//	if (classtype->aerobaticfactor == AEROBATIC_MIG)
//		BreakHigh();
//	else if (	(ai.morale > MORALE_MEDIUM)
//			&&	(ClosureLessThan(MPH50))
//			)
//				BreakHigh();
//			else
//				BreakLow();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HiGBarrelRoll
//Author		R. Hyde						Craig Beeston
//Date			Mon 9 Mar 1998				Sun 13 Jun 1999
//
//Description	1.30	
//				Defensive manoeuvre
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleHiGBarrelRoll()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust(0);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SWord DesRoll = ANGLES_45Deg;	DesRoll = -DesRoll;
			SimpleMoveToRoll(DesRoll);

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
				ai.ManStep = PHASE2;
		
			break;
		}
		case PHASE2:
		{
			PitchIntercept = ANGLES_45Deg;
			AutoCalcPitch();
			SWord DesRoll = 2 * SWord(pitch);
			SimpleMoveToRoll(DesRoll);

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
				ai.ManStep = PHASE3;
		
			break;
		}
		case PHASE3:
		{
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SWord DesRoll = ANGLES_180Deg - 2 * SWord(pitch);
			SimpleMoveToRoll(DesRoll);

			SWord dHdg = CalcHdg();
			hdg -= 2 * dHdg;

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
				ai.ManStep = PHASE4;
		
			break;
		}
		case PHASE4:
		{
			PitchIntercept = ANGLES_45Deg;	PitchIntercept = -PitchIntercept;
			AutoCalcPitch();
			SWord DesRoll =  -2 * SWord(pitch) - ANGLES_180Deg;
			SimpleMoveToRoll(DesRoll);

			SWord dHdg = CalcHdg();
			hdg -= 2 * dHdg;

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
				ai.ManStep = PHASE5;
		
			break;
		}
		case PHASE5:
		{
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SWord DesRoll =  2 * SWord(pitch);
			SimpleMoveToRoll(DesRoll);

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
			{
				SimpleMoveToThrust(ThrustfromFF());
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
		
			break;
		}
	}
		
//DeadCode CSB 13/06/99			case PHASE1:
//DeadCode CSB 13/06/99			{
//DeadCode CSB 13/06/99				SimpleMoveToRoll(-ANGLES_45Deg);
//DeadCode CSB 13/06/99				PitchIntercept = ANGLES_0Deg;
//DeadCode CSB 13/06/99				AutoCalcPitch();
//DeadCode CSB 13/06/99				if(-(SWord)roll == ANGLES_45Deg)
//DeadCode CSB 13/06/99					ai.ManStep = PHASE2;
//DeadCode CSB 13/06/99				break;
//DeadCode CSB 13/06/99			}
//DeadCode CSB 13/06/99			case PHASE2:
//DeadCode CSB 13/06/99			{
//DeadCode CSB 13/06/99				SimpleMoveToRoll(roll + ANGLES_90Deg);
//DeadCode CSB 13/06/99				SWord sin, cos;
//DeadCode CSB 13/06/99				Math_Lib.high_sin_cos(roll, sin, cos);
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99				PitchIntercept = (Angles)(sin / 2);
//DeadCode CSB 13/06/99	 			AutoCalcPitch();
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99				if(-(SWord)roll > ANGLES_90Deg)
//DeadCode CSB 13/06/99					ai.ManStep = PHASE3;
//DeadCode CSB 13/06/99				break;
//DeadCode CSB 13/06/99			}
//DeadCode CSB 13/06/99			case PHASE3:
//DeadCode CSB 13/06/99			{
//DeadCode CSB 13/06/99				SimpleMoveToRoll(roll + ANGLES_90Deg);
//DeadCode CSB 13/06/99				SWord sin, cos;
//DeadCode CSB 13/06/99				Math_Lib.high_sin_cos(roll, sin, cos);
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99				PitchIntercept = (Angles)(sin / 2);
//DeadCode CSB 13/06/99	  			AutoCalcPitch();
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99				if((SWord)roll > ANGLES_0Deg)
//DeadCode CSB 13/06/99				{
//DeadCode CSB 13/06/99					SimpleMoveToThrust(ThrustfromFF());
//DeadCode CSB 13/06/99					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 13/06/99				}
//DeadCode CSB 13/06/99				break;
//DeadCode CSB 13/06/99			}
//DeadCode CSB 13/06/99		}
	
//max g, roll in one direction
//nose low or high
//unbalanced flight, power reduction, increased drag for better pilots
//
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PanicTurn
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.30
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimplePanicTurn()
{
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnBalancedFlight
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleUnBalancedFlight()
{
//skid and slip while making turns
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrackingShot
//Author		R. Hyde 
//Date			Tue 10 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleTrackingShot()
{
//aim for gun solution
//actually modify pitch and heading within limits on top of changes produced by manoeuvre
//just enough lead
//modify speed(rpm and airbrakes) to stay on tail
//
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SnapShot
//Author		R. Hyde 
//Date			Tue 10 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleSnapShot()
{
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StayOnTail
//Author		R. Hyde 
//Date			Fri 20 Mar 1998
//
//Description	This is not a good idea, very aggressive
//				Stay at corner speed or less
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleStayOnTail()
{
//	if necessayr shed energy:
//		turn
//		brakes
//		throttle
//	to stay on tail

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurnToHdgAndPitch
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	move to within 5 deg of desiredpitch and desiredhdg 
//				break or sustained turn depending on circumstances
//				if break then nose down if <corner vel
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::SimpleTurnToHdgAndPitch()
{
	//return true on success
	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LagFight
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleHotSideLagPursuitFight()
{
//1	trgItem is behind target
//	TurningFightSub()
}

//------------------------------------------------------------------------------
Bool	AirStruc::SimpleSandwichManoeuvres()
{
	return(TRUE);
}
//void	AirStruc::SimpleTurningFight()
//{
//}
//void	AirStruc::SimpleTightTurnSubtSub(ANGLES	HdgIntercept)
//{
//}
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SustainedTurn
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleSustainedTurn()
{
//1	GetRequiredRoll(srcItem,trgItem)
//2	pull on elevators so that Drag = Thrust 
//			this is the max sustainable turn, in-plane
//turn to minimise the difference between hdgintercept and hdg, go shortest way
//
//
//	roll = f(morale, flyingskill)
//	drag = f(combatskill)
//
//
//	if (skill high)
//			check lead/lag to avoid turning into target
//
//	turn at best sustained turnrate  (how near = f(skill), maintain altitude if possible
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HighYoYo
//Author		R. Hyde 
//Date			Wed 11 Mar 1998
//
//Description	Ref1.70
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleHighYoYo()
{
//approach from 30-60 AOT, cospeed
//
//roll wings level
//pull up
//when in rear hemisphere (say near 6 o'clock)
//	roll towards target then lead or lag pursuit
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Zoom
//Author		R. Hyde 
//Date			Wed 11 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleZoom()
{
//roll wings nearly level
//pull up then zoom climb for x secs or near stall
//roll 180 and pull level
//
//
//	ACM.Step = ai.ManStep;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (2000);

			SimpleMoveToThrust (100);			//rdh
//			ACM.ClimbRate (0);
//			ACM.KeepWingsLevel ();

			ai.ManStep = PHASE1;
			break;
		}
		case PHASE1:
		{
				SimpleMoveToRoll (ANGLES_0Deg);
				PitchIntercept = ANGLES_40Deg;
				AutoCalcPitch ();
			

			if  (		(!ManoeuvreTimeLeft ())
					||
						(vel <= CornerSpeed())
					||
						((World.Y - ai.unfriendly->World.Y)	>	FT_4000)
				)
			{
 				if (ai.firsttactic == TACTIC_ROUNDABOUT)
 					ai.manoeuvre = MANOEUVRE_ROUNDABOUT;
 				else if (ai.firsttactic == TACTIC_LINEABREAST)
 					ai.manoeuvre = MANOEUVRE_LINEABREAST;
 				else if (ai.firsttactic == TACTIC_LINEASTERN)
 					ai.manoeuvre = MANOEUVRE_LINEASTERN;
 				else if (ai.firsttactic == TACTIC_DIVEANDZOOM)
 					ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
				else
					ai.manoeuvre = MANOEUVRE_SELECT;

			}
			break;
		}
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowYoYo
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	Ref1.73	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleLowYoYo ( )
{
//used when closure is insufficient
//
//in turning fight, attacker increases horizontal component of turn rate by nose down
//lead target
//level wings and pull up
//
//Note may have to write so that the ac doesn't try to get advantage in one 
//manoeuvre (see btm 1.73)
//
//
//
//Note can also be used when in tailchase to pick up speed to get just inside gun range
//
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptHigh
//Author		R. Hyde 
//Date			Wed 11 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleInterceptHigh()
{
//intercept but stay at alt
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbAtSustainedTurnSpeed
//Author		R. Hyde 
//Date			Fri 20 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleClimbAtSustainedTurnSpeed()
{
//climb but don't go below sustained turn speed
//aim towards unfriendly plus offset = f(desiredrange,desiredhdg)

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		R. Hyde 
//Date			 //RDH 25/05/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleLowAlt()
{

	ANGLES dpitch;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (800);
			if (TargetFacingSubject(ANGLES_45Deg))
				ai.desiredpitch = ANGLES_5Deg;
			else
				ai.desiredpitch = ANGLES_10Deg;
			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
//DEADCODE RDH 18/06/99 			if (TargetFacingSubject(ANGLES_45Deg))
//DEADCODE RDH 18/06/99 				dpitch = ANGLES_5Deg;
//DEADCODE RDH 18/06/99 			else
//DEADCODE RDH 18/06/99 				dpitch = ANGLES_10Deg;

			PitchIntercept = ai.desiredpitch;
			AutoCalcPitch();
			SimpleMoveToHdg (HdgIntercept);

			if  (!ManoeuvreTimeLeft())
							ai.manoeuvre = MANOEUVRE_SELECT;

		}
	}


}
