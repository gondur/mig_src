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
//Filename       acmai.cpp
//System         
//Author         Andrew McRae
//Date           Mon 17 Mar 1997
//Description    Flight Model ACM
//------------------------------------------------------------------------------
//
//RANGES_Included
//
#define F_GRAFIX											//DAW 05Aug96
#define F_COMMON
#define F_BATTLE

#include <stdio.h>
#include <string.h>


#include "collided.h"										//PD 06Sep96
#include "Dosdefs.h"		
#include "Worldinc.h"

#include "ranges.h"
#include "modvec.h"
#include "model.h"



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
#include "monotxt.h"

#include "matrix.h"
#include "winmove.h"

//#define PRINT_AI_DATA	//CSB 16/03/99
//MATHABLE	(ANGLES)

// ROD don't use STALL_ANGLE
ANGLES const	STALL_ANGLE = ANGLES_15Deg;

ANGLES const	STALL_ANGLE_MINUSONE = STALL_ANGLE - ANGLES_1Deg;
ANGLES const	STALL_ANGLE_MINUSTWO = STALL_ANGLE - ANGLES_2Deg;
ANGLES const	STALL_ANGLE_MINUSTHREE = STALL_ANGLE - ANGLES_3Deg;
//DeadCode RDH 09Jul96 SLong	const	ELEVATOR_DELTA = 160;
SLong	const	ELEVATOR_DELTA = 40;
SLong	const	ELEVATOR_DELTA_DOWN = ELEVATOR_DELTA * 2;
SLong	const	RUDDER_DELTA = 1000;
//SLong	const	MAXAUTOTHRUST = 80;	

ANGLES const	DSLIPFORMAXRUDDER = ANGLES_10Deg;
ANGLES const	DPITCHFORMAXELEVATOR = ANGLES_60Deg;
ANGLES const	DAOAFORMAXELEVATOR = ANGLES_15Deg;
//sensitivity for Diferential control
ANGLES const	DIFFPITCHFORMAXELEVATOR = ANGLES_10Deg;
ANGLES const	DHDGFORMAXAILERON = ANGLES_22Deg;
//DeadCode RDH 02Jul96 SLong const MAXELEVATORFORTIGHTTURN = -30000;
//DeadCode RDH 30Oct96 SLong const MAXELEVATORFORTIGHTTURN = -20000;
SLong const MAXELEVATORFORTIGHTTURN = -25000;
SLong const SLIGHTPULLELEVATOR = -4000;
SLong const MEDIUMPULLELEVATOR = -12000;
SLong const HEAVYPULLELEVATOR = -20352;							//RDH 21Aug96




extern RequiredBankDataElement 	CombatReqBankData[];
// =
//			{
//				{ANGLES_FifthDeg, ANGLES_0Deg},
//				{ANGLES_HalfDeg, ANGLES_3Deg},
//				{ANGLES_1Deg, ANGLES_4Deg},
//				{ANGLES_2Deg, ANGLES_5Deg},
//				{ANGLES_3Deg, ANGLES_10Deg},
//				{ANGLES_4Deg, ANGLES_15Deg},
//				{ANGLES_5Deg, ANGLES_22Deg},
//				{ANGLES_6Deg, ANGLES_30Deg},
//				{ANGLES_10Deg, ANGLES_45Deg},
////DeadCode RDH 17Jul96 				{ANGLES_22Deg, ANGLES_60Deg},
//				{ANGLES_30Deg, MAXCOMBATROLL},
//				{ANGLES_180BareDeg, MAXCOMBATROLL}
//			};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveToPitch
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	based on difference between desired and actual pitch, fix elevator
//DeadCode RDH 26Mar98 //				old model trim will be used to stabilise
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::MoveToPitch (ANGLES desiredpitch,SWord modifier)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	// Uses elevator to control pitch in woorld coords
//DeadCode RDH 26Mar98 	// Assumes roll is okay
//DeadCode RDH 26Mar98 	// and aircrfat is not upside down
//DeadCode RDH 26Mar98 	// modifier is ignored
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 26Mar98 	UWord	deltapitch_pos;
//DeadCode RDH 26Mar98 	SWord	deltapitch_sign;
//DeadCode RDH 26Mar98 	SLong	elevator;
//DeadCode RDH 26Mar98  	SWord	deltadeltapitch;
//DeadCode RDH 26Mar98 //DeadCode RDH 01Apr96 	SWord	elevator_pos,elevator_sign,maxelevator_pos;
//DeadCode RDH 26Mar98 	SWord	sinroll,cosroll;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 	if (	((SWord) (classtype->stallangle - fly.aoa) < ANGLES_4Deg)
//DeadCode RDH 26Mar98 	if (	((SWord) (classtype->stallangle - fly.aoa) < ANGLES_2Deg)
//DeadCode RDH 26Mar98 		 &&	(fly.rotr_xbl >=0)
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 		modifier = 1;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	deltapitch = desiredpitch -	fly.cpitch;
//DeadCode RDH 26Mar98 	Math_Lib.Pos (((SWord)deltapitch),deltapitch_pos,deltapitch_sign);
//DeadCode RDH 26Mar98 	if ((Angles)(modifier * deltapitch_pos)    > DPITCHFORMAXELEVATOR)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		elevator = -MAXELEVATORFORTIGHTTURN;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		elevator = (Angles)(modifier * -MAXELEVATORFORTIGHTTURN * deltapitch_pos)/ DPITCHFORMAXELEVATOR;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if (deltapitch_sign == MathLib::POSITIVE)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		elevator = (SWord) -elevator;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	//D control
//DeadCode RDH 26Mar98 	deltadeltapitch = deltapitch - (SWord) ai.lastdeltapitch;
//DeadCode RDH 26Mar98  	Math_Lib.Pos (deltadeltapitch,deltapitch_pos,deltapitch_sign);
//DeadCode RDH 26Mar98  	if ((Angles)deltapitch_pos >= DIFFPITCHFORMAXELEVATOR)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98 		if (deltapitch_sign== MathLib::NEGATIVE)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			elevator +=  MAXELEVATORFORTIGHTTURN;
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 	 		elevator -= MAXELEVATORFORTIGHTTURN;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98 		elevator -=	-MAXELEVATORFORTIGHTTURN * (deltapitch - (SWord) ai.lastdeltapitch) / (int)DIFFPITCHFORMAXELEVATOR;
//DeadCode RDH 26Mar98 	}	
//DeadCode RDH 26Mar98 	if (elevator > -MAXELEVATORFORTIGHTTURN)
//DeadCode RDH 26Mar98 		elevator = -MAXELEVATORFORTIGHTTURN;
//DeadCode RDH 26Mar98 	if (elevator < MAXELEVATORFORTIGHTTURN)
//DeadCode RDH 26Mar98 		elevator = MAXELEVATORFORTIGHTTURN;
//DeadCode RDH 26Mar98 	fly.elevator = (SWord) elevator;
//DeadCode RDH 26Mar98 	fly.unmod_elevator = fly.elevator;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //-----------------------------------------------------------------
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (	(fly.acroll > ANGLES_90Deg)							//RDH 24Jul96
//DeadCode RDH 26Mar98 		|| (fly.acroll <= ANGLES_270Deg))						//RDH 24Jul96
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		fly.elevator = (SWord) -fly.elevator;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	ai.lastdeltapitch = (Angles) deltapitch;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SetControlSurfaces ();
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveToRudder
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 17 May 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::MoveToRudder (SWord desiredrudder)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	allowedchange;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (fly.rudder <= desiredrudder)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		allowedchange = desiredrudder - Timer_Code.FRAMETIME* RUDDER_DELTA; //DAW 31Jul96
//DeadCode RDH 26Mar98 		if ((SLong) fly.rudder <
//DeadCode RDH 26Mar98 			 allowedchange)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			fly.rudder += Timer_Code.FRAMETIME* RUDDER_DELTA;	//DAW 31Jul96
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			fly.rudder = desiredrudder;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		allowedchange = desiredrudder + Timer_Code.FRAMETIME* RUDDER_DELTA; //DAW 31Jul96
//DeadCode RDH 26Mar98 		if ((SLong) fly.rudder >
//DeadCode RDH 26Mar98 			 allowedchange)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			fly.rudder -= Timer_Code.FRAMETIME* RUDDER_DELTA;	//DAW 31Jul96
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			fly.rudder = desiredrudder;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MovetoAoA
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 26 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::MoveToAoA (ANGLES desiredAoA)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 //DeadCode RDH 14May96 SLong	const	ELEVATOR_DELTA = 160;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //TempCode ARM 09May97 	fly.elevator = Rads2Rowan (((FP)desiredAoA - fly.pModel->ACMModel.Incidence) / fly.pModel->ACMModel.ElevatorCtrl);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ((SWord)fly.aoa > (SWord) desiredAoA)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (fly.elevator <
//DeadCode RDH 26Mar98 			 (-MAXELEVATORFORTIGHTTURN - Timer_Code.FRAMETIME* ELEVATOR_DELTA_DOWN))//DAW 31Jul96
//DeadCode RDH 26Mar98 			fly.elevator = fly.elevator + Timer_Code.FRAMETIME* ELEVATOR_DELTA_DOWN;//DAW 31Jul96
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (fly.elevator >
//DeadCode RDH 26Mar98 			 (MAXELEVATORFORTIGHTTURN + Timer_Code.FRAMETIME* ELEVATOR_DELTA))//DAW 31Jul96
//DeadCode RDH 26Mar98 		fly.elevator = fly.elevator - Timer_Code.FRAMETIME* ELEVATOR_DELTA;//DAW 31Jul96
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	fly.unmod_elevator = fly.elevator;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
void	AirStruc::MoveToThrust (SWord thrust)
{
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
 void	AirStruc::MoveToHdg (ANGLES desiredhdg, ANGLES desiredpitch)
 {
  	ACMMODEL& ACM = *fly.pAcmModel;

	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltapitch,reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;

	reqdeltahdg = (SWord)hdg - (SWord)desiredhdg;
	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

	reqdeltapitch = (SWord)desiredpitch - (SWord)fly.cpitch;
	Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);

	if((reqdeltahdg > ANGLES_10Deg) || (reqdeltahdg < -ANGLES_10Deg))
		TurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, ANGLES_0Deg);
	else
	{
		if( ((SWord)roll > ANGLES_45Deg) || ((SWord)roll < -ANGLES_45Deg) )
			;
//DeadCode CSB 19/03/99				ACM.Pitch(0);	
		else
			ACM.Pitch(desiredpitch);
		SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
		ACM.Roll(reqroll);
	}

	ACM.SetRudder(0);


//DEADCODE RDH 21/02/99  	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DEADCODE RDH 21/02/99 	ACM.Roll ((Angles)reqroll);

  
  }
 
//DeadCode RDH 26Mar98  //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98  //Procedure		MoveToHdgOnThisRoll
//DeadCode RDH 26Mar98  //Author		R. Hyde 
//DeadCode RDH 26Mar98  //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Description	don't change the roll direction
//DeadCode RDH 26Mar98  //				
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Inputs		
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Returns	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98  void	AirStruc::MoveToHdgOnThisRoll (ANGLES desiredhdg,ANGLES maxroll)
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  {
//DeadCode RDH 26Mar98 // 	SWord	reqdeltahdg;
//DeadCode RDH 26Mar98 //	UWord	reqdeltahdg_pos;
//DeadCode RDH 26Mar98 //	SWord	reqdeltahdg_sign;
//DeadCode RDH 26Mar98 //	SWord	reqroll,deltaroll;
//DeadCode RDH 26Mar98 //	UWord	reqroll_pos;
//DeadCode RDH 26Mar98 //	SWord	reqroll_sign;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 // 	reqdeltahdg = 	(SWord) hdg - (SWord) desiredhdg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 // 	Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //	reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 22Mar96  	if ( ((SWord) fly.acroll < ANGLES_0Deg) == (reqroll < ANGLES_0Deg))
//DeadCode RDH 26Mar98 //DeadCode RDH 22Mar96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 22Mar96 		reqroll = -reqroll;
//DeadCode RDH 26Mar98 //DeadCode RDH 22Mar96 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 // 	Math_Lib.Pos (reqroll, reqroll_pos,reqroll_sign);
//DeadCode RDH 26Mar98 //	if (reqroll_pos > maxroll)
//DeadCode RDH 26Mar98 //		reqroll_pos = maxroll;
//DeadCode RDH 26Mar98 //	if (reqroll_sign == MathLib::NEGATIVE)
//DeadCode RDH 26Mar98 //		reqroll = -reqroll_pos;
//DeadCode RDH 26Mar98 //	else
//DeadCode RDH 26Mar98 //		reqroll = reqroll_pos;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //	if ( !!((SWord) fly.acroll < ANGLES_0Deg) != !!(reqroll < ANGLES_0Deg))
//DeadCode RDH 26Mar98 // 		reqroll = -reqroll;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 30Mar96 	deltaroll = (SWord) (reqroll - (SWord) fly.acroll);
//DeadCode RDH 26Mar98 //	MoveToRoll (reqroll,1);
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveToRoll
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 18 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::MoveToRoll (SWord desiredroll,SWord modifier)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 ANGLES const	DROLLFORMAXAILERON = ANGLES_90Deg;
//DeadCode RDH 26Mar98 ANGLES const	DIFFAILERONFORMAXAILERON = ANGLES_45Deg;
//DeadCode RDH 26Mar98 //the flat zone is where no effective control is obtained
//DeadCode RDH 26Mar98 SLong const	FLATZONE = 0;
//DeadCode RDH 26Mar98 	SLong	aileron;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	SWord	deltaroll,deltadeltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	deltaroll = desiredroll - fly.acroll;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	if ((Angles)(modifier * deltaroll_pos) >= DROLLFORMAXAILERON)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		aileron = (SLong) MAXAILERON;
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		aileron = modifier * MAXAILERON * deltaroll_pos/(int)DROLLFORMAXAILERON;
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98  	
//DeadCode RDH 26Mar98  	if (deltaroll_sign == MathLib::NEGATIVE)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		aileron =  -aileron;
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	//D control
//DeadCode RDH 26Mar98 	deltadeltaroll = deltaroll - (SWord) ai.lastdeltaroll;
//DeadCode RDH 26Mar98  	Math_Lib.Pos (deltadeltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98  	if ((Angles)(modifier * deltaroll_pos) >= DIFFAILERONFORMAXAILERON)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98 		if (deltaroll_sign== MathLib::NEGATIVE)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			aileron -=  MAXAILERON;
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 	 		aileron += MAXAILERON;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98 		aileron +=	modifier * MAXAILERON * (deltaroll - (SWord) ai.lastdeltaroll) / (int)DIFFAILERONFORMAXAILERON;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ai.lastdeltaroll = (Angles) deltaroll;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (aileron > MAXAILERON)
//DeadCode RDH 26Mar98 		aileron = MAXAILERON;
//DeadCode RDH 26Mar98 	if (aileron < -MAXAILERON)
//DeadCode RDH 26Mar98 		aileron = -MAXAILERON;
//DeadCode RDH 26Mar98 	fly.aileron =(SWord) aileron;
//DeadCode RDH 26Mar98 	SetControlSurfaces ();
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveToDesiredPitch
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 18 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 SWord	AirStruc::MoveToDesiredPitch (ANGLES desiredpitch,ANGLES target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	retval;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	MoveToPitch (desiredpitch,2);
//DeadCode RDH 26Mar98 	retval = DesiredPitchChk (desiredpitch,target);
//DeadCode RDH 26Mar98 	return (retval);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		DesiredPitchChk
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 18 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 SWord	AirStruc::DesiredPitchChk (ANGLES desiredpitch,ANGLES target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord deltapitch;
//DeadCode RDH 26Mar98 	UWord	deltapitch_pos;
//DeadCode RDH 26Mar98 	SWord	deltapitch_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	deltapitch = desiredpitch -	fly.cpitch;
//DeadCode RDH 26Mar98 	Math_Lib.Pos (((SWord)deltapitch),deltapitch_pos,deltapitch_sign);
//DeadCode RDH 26Mar98 	if (deltapitch_pos < target)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		return (TRUE);
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		return (FALSE);
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		DesiredAcPitchChk
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 18 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 SWord	AirStruc::DesiredAcPitchChk (ANGLES desiredpitch,ANGLES target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord deltapitch;
//DeadCode RDH 26Mar98 	UWord	deltapitch_pos;
//DeadCode RDH 26Mar98 	SWord	deltapitch_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	deltapitch = desiredpitch -	pitch;
//DeadCode RDH 26Mar98 	Math_Lib.Pos (((SWord)deltapitch),deltapitch_pos,deltapitch_sign);
//DeadCode RDH 26Mar98 	if (deltapitch_pos < target)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		return (TRUE);
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		return (FALSE);
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
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
Bool	AirStruc::MoveToDesiredHdg (ANGLES desiredhdg,ANGLES desiredpitch,ANGLES target)

{
	Bool	retval;

	MoveToHdg (desiredhdg, desiredpitch);
	retval = ChkAtDesiredHdg (desiredhdg,target);
	return (retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRequiredRoll
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	Find the roll to put trgitem on lift vector of srcitem
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ANGLES GetRequiredRoll(rotitem& srcItem,COORDS3D trg, Float& pitch, Float& hdg)

{
	//const Float _PI=22/7;
 	FPMATRIX fpmMatrix;
	_matrix.generate(-srcItem.hdg,-srcItem.pitch,-srcItem.roll,&fpmMatrix);
	IFShare	x,y,z;
	x.i=trg.X-srcItem.World.X;
	y.i=trg.Y-srcItem.World.Y;
	z.i=trg.Z-srcItem.World.Z;
	_matrix.transform(&fpmMatrix,x,y,z);
	if (z.f<0.) z.f=-z.f;
	x.f/=z.f;
	hdg = x.f;
	y.f/=z.f;
	_asm {
		fld x.f;
		fld y.f;
		fpatan;
		fstp x.f;
	}
	//x.f is required angle in radians
	x.f=Float(32768)*x.f/FPIE;
	pitch = y.f;
	return (Angles)(UWord)x.f;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LookAround
//Author		R. Hyde 
//Date			Mon 19 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::LookAround ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;

			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (500);
//DeadCode CSB 18/03/99	 			ai.desiredroll = -(ANGLES)ANGLES_30Deg +
//DeadCode CSB 18/03/99						(Angles)(ANGLES_60Deg * Math_Lib.rnd(2)); 
 			ai.desiredroll = -(ANGLES)ANGLES_60Deg +	//CSB 18/03/99	
					(Angles)(ANGLES_120Deg * Math_Lib.rnd(2));	//CSB 18/03/99	


			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll (ai.desiredroll);
			ACM.Pitch (BestClimbAngle());
			ACM.MinHeight (FT_2000);

			if  (!ManoeuvreTimeLeft())
			{
 		    	ai.ManStep = PHASE0;
 				if (formpos == 0)
 				{
 					if (AllButLdrNotOnCombat ())
 					{
 						ai.manoeuvre=MANOEUVRE_TOPCOVER;
 					}else
 					{
 						ai.manoeuvre=MANOEUVRE_LOOKROUND;
 					}
 
 				}else
 				{
 					ai.manoeuvre=MANOEUVRE_TOPCOVER;
 				}

			}

		}
	}
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.desiredroll = -(ANGLES)ANGLES_45Deg +
//DeadCode RDH 26Mar98  						(Angles)(ANGLES_90Deg * Math_Lib.rnd(2)); 
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 			TightClimbingTurn (ANGLES_15Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 			if (World.Y > classtype->fightceiling)
//DeadCode RDH 26Mar98 				TightClimbingTurn (ANGLES_0Deg);
//DeadCode RDH 26Mar98 			else
//DeadCode RDH 26Mar98 				TightClimbingTurn (ANGLES_15Deg);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 		    	ai.ManStep = PHASE0;
//DeadCode RDH 26Mar98 				if (formpos == 0)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					if (AllButLdrNotOnCombat ())
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						ai.manoeuvre=MANOEUVRE_TOPCOVER;
//DeadCode RDH 26Mar98 					}else
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						ai.manoeuvre=MANOEUVRE_LOOKROUND;
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					ai.manoeuvre=MANOEUVRE_TOPCOVER;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeldedWingMan
//Author		R. Hyde 
//Date			Mon 2 Mar 1998
//
//Description	Formation flag not set so a/c can spot
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::WeldedWingMan()
{
	
//	stick to the leaders tail, range about 1000ft and weave
//	However for low morale bring wingman closer
//	For very low morale it should appear as if he is trying to stay in formation
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			ai.ManStep = PHASE1;
			ACM.maxdeltaforclosework = 0.0;
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
				
				if (!leader)
					ai.manoeuvre = MANOEUVRE_SELECT;
				else
				{
	//DEADCODE PD 26/02/99 				FP desiredturn;
					double	desiredturn;

					COORDS3D	target;
					target = leader->World; 									//JIM 02Aug96
					target.Y +=	FT_500;
					InterceptandRange(&target);

					SWord	reqdeltahdg,reqdeltahdg_sign;
					UWord	reqdeltahdg_pos;
					reqdeltahdg = 	hdg - HdgIntercept;
					Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

					SWord	reqdeltapitch,reqdeltapitch_sign;
					UWord	reqdeltapitch_pos;
					reqdeltapitch = (SWord)PitchIntercept - (SWord)fly.cpitch;
					Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);

									
					if  (		(		(reqdeltahdg_pos < ANGLES_40Deg)
						&&	(ACM.maxdeltaforclosework == 0.0)
						)
						||
							(		(reqdeltahdg_pos < ANGLES_45Deg)
								&&	(ACM.maxdeltaforclosework != 0.0)
							)		
						)
					{
				 		SWord reqroll = RollforTurn(reqdeltapitch, reqdeltahdg, desiredturn, target);
						ACM.Roll ((Angles)reqroll);
		
					}else
					{
						ACM.maxdeltaforclosework = 0.0;
						TurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, ANGLES_0Deg);
						ACM.SetRudder(0);
					}
					InterceptandRange (&leader->World);
					UWord DesRange = 256 * ai.morale;	// up to 650 metres
					if(DesRange < WEAPONSRANGE) DesRange = WEAPONSRANGE;

					if (Range < DesRange)
						ACM.Thrust (0);
					else
						ACM.Thrust (ThrustfromFF());
				
				}
			}
		}
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BailOut
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::BailOut()
{
//pilot ejects or bails out depending on ac type
//ac in slow turning dive

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(0);	 
			ACM.Roll(0);
			ACM.Pitch(ANGLES_0Deg);
			SetManoeuvreTime(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll(0);
			ACM.Pitch(ANGLES_0Deg);
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
			ACM.Roll(0);
			ACM.Pitch(ANGLES_0Deg);
			if(!TimeLeft())
			{
				Trans_Obj.LaunchParachute(this,*mobileitem::currworld);
				movecode = AUTO_DEATHSEQUENCE;
			}
		}
	}
//DeadCode CSB 13/06/99		switch (ai.ManStep)
//DeadCode CSB 13/06/99		{
//DeadCode CSB 13/06/99			case PHASE0:
//DeadCode CSB 13/06/99			{
//DeadCode CSB 13/06/99				ACM.Thrust (0);
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99				SetManoeuvreTime (300);
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99				Trans_Obj.LaunchCanopyEject(this,*mobileitem::currworld);
//DeadCode CSB 13/06/99				Trans_Obj.LaunchParachute(this,*mobileitem::currworld);
//DeadCode CSB 13/06/99			 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 13/06/99				unfriendly->ai.unfriendly = NULL;
//DeadCode CSB 13/06/99				ai.ManStep = PHASE1;
//DeadCode CSB 13/06/99				break;
//DeadCode CSB 13/06/99			}
//DeadCode CSB 13/06/99			case PHASE1:
//DeadCode CSB 13/06/99			{
//DeadCode CSB 13/06/99				ACM.Roll(0);
//DeadCode CSB 13/06/99				ACM.Pitch(0);
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99				if  (!ManoeuvreTimeLeft())
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99				{
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99					Trans_Obj.LaunchParachute(this,*mobileitem::currworld);
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99					ai.ManStep = PHASE2;
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99				 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99					unfriendly->ai.unfriendly = NULL;
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99				}
//DeadCode CSB 13/06/99				break;
//DeadCode CSB 13/06/99			}
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99			case PHASE2:
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99			{
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99				MOD.Aileron = MOD.Aileron - MOD.Aileron/10;	
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99				MOD.Elevator = MOD.Elevator - MOD.Elevator/10;
//DeadCode CSB 13/06/99	//DeadCode CSB 13/06/99			}
//DeadCode CSB 13/06/99		}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TopCover
//Author		R. Hyde 
//Date			Mon 19 Aug 1996
//
//Description	The followers are supposed to go near to home line or
//				not depending on skill
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::TopCover ()

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	UByte	FF = FlyingFactor();

   if (formpos == 0)
   {//leader
 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;

			ACM.Thrust (ThrustfromFF());

 			SetManoeuvreTime (500);			//rdh 25/6/99
 			ai.desiredroll = -(ANGLES)ANGLES_60Deg +
  						(Angles)(ANGLES_120Deg * Math_Lib.rnd(2)); 
 			ai.ManStep = PHASE1;
 		}
 
 
 		case PHASE1:
 		{
			ACM.Roll (ai.desiredroll);
			ACM.Pitch (BestClimbAngle());

 			if (!ManoeuvreTimeLeft())
 			{
 				SetManoeuvreTime (1000);
 				ai.ManStep = PHASE2;
  			}
 
 			break;
 		}
 		case PHASE2:
 		{
			ACM.Roll (ai.desiredroll);
			ACM.Pitch (ANGLES_0Deg);
 
 			if (!ManoeuvreTimeLeft())
 			{
 				ai.ManStep = PHASE3;
  			}
 
 			break;
 		}
 		case PHASE3:
 		{
			ACM.Roll (ai.desiredroll);
			ACM.Pitch (ANGLES_0Deg);
 
 			if (AllOnTopCover ())
 			{
 				Art_Int.AllBreakOff(this);						//JIM 11Oct96
 
//##				if (ai.eventlog->stage==EventLog::TAKEOFF)		//JIM 06Dec96
//##					if (formpos!=0 || follower || fly.nextflight)
//##					 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_SQUADRONREGROUPED,NULL);
 			}
 			else
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
					MOD.Rudder = 0;

					ACM.Thrust (ThrustfromFF());
 					SetManoeuvreTime (500);
 					ai.desiredroll = -(ANGLES)ANGLES_60Deg +
  								(Angles)(ANGLES_120Deg * Math_Lib.rnd(2)); 
 					ai.ManStep = PHASE1;
 				}
 
 
 				case PHASE1:
 				{
					ACM.Roll (ai.desiredroll);
					ACM.Pitch (BestClimbAngle());
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
						ACM.Roll (ai.desiredroll);
						ACM.Pitch (ANGLES_0Deg);
 					}else
 					{
						ACM.Roll (ai.desiredroll);
						ACM.Pitch (ANGLES_5Deg);
 					}
 					break;
 				}
 
   			}
	   }
   }






//DeadCode RDH 26Mar98   if (formpos == 0)
//DeadCode RDH 26Mar98   {//leader
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 			ai.desiredroll = -(ANGLES)ANGLES_30Deg +
//DeadCode RDH 26Mar98  						(Angles)(ANGLES_60Deg * Math_Lib.rnd(2)); 
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 			TightClimbingTurn (ANGLES_15Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 			TightClimbingTurn (ANGLES_15Deg);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 			TightClimbingTurn (ANGLES_0Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 			TightClimbingTurn (ANGLES_0Deg);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 			TightClimbingTurn (ANGLES_0Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 			TightClimbingTurn (ANGLES_0Deg);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (AllOnTopCover ())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				Art_Int.AllBreakOff(this);						//JIM 11Oct96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //TEMP				if (ai.eventlog->stage==EventLog::TAKEOFF)		//JIM 06Dec96
//DeadCode RDH 26Mar98 //TEMP					if (formpos!=0 || follower || fly.nextflight)
//DeadCode RDH 26Mar98 //TEMP					 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_SQUADRONREGROUPED,NULL);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 		    	ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98   }else
//DeadCode RDH 26Mar98   {
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 			ai.desiredroll = -(ANGLES)ANGLES_30Deg +
//DeadCode RDH 26Mar98  						(Angles)(ANGLES_60Deg * Math_Lib.rnd(2)); 
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 			TightClimbingTurn (ANGLES_15Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 			TightClimbingTurn (ANGLES_15Deg);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (fly.leadflight->World.Y > World.Y)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 				TightClimbingTurn (ANGLES_0Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 				TightClimbingTurn (ANGLES_0Deg);
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 				TightClimbingTurn (ANGLES_8Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 				TightClimbingTurn (ANGLES_8Deg);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98   }

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
void	AirStruc::LineAbreast()
{


	//only followers go line abreast. We don't link flights
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	if (!leader) 
	{//leader, do same as roundabout, get height, dive and then zoom
	 //at end of zoom, choose manoeuvre based on firsttactic
			ai.ManStep = PHASE0;
			ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;			
	}else
	{//follower
		if (Range < DANGERRANGE)
		{
			FireABullet(30);
		}
		else
		{
			switch (ai.ManStep)
			{
				case PHASE0:
				{
					MOD.Rudder = 0;
					ACM.Thrust (ThrustfromFF());
					ai.ManStep = PHASE1;
					ACM.maxdeltaforclosework = 0.0;

				}
				case PHASE1:
				{

					
					if (!leader)
						ai.manoeuvre = MANOEUVRE_SELECT;					//if no leader break manoeuvre
					else
					{

 						COORDS3D	target;
 						target = leader->World; 
 						InterceptandRange(&target);

						SWord c,s;
						SWord newhdg;
						SLong range;
						newhdg = leader->hdg + ANGLES_90Deg;
						Math_Lib.high_sin_cos((Angles)newhdg,s,c);
						range = METRES20;
						target.X = target.X + MULSHSIN(s, range, ANGLES_SHIFT);
						target.Y = target.Y;
						target.Z = target.Z + MULSHSIN(c, range, ANGLES_SHIFT);


						Float fpitch, fhdg;
						SWord reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
						if  (		(	(fpitch < ACM.maxdeltaforclosework)
									&&	(fpitch > -ACM.maxdeltaforclosework)
									&&	(fhdg < ACM.maxdeltaforclosework)
									&&	(fhdg > -ACM.maxdeltaforclosework)
									)
							)
						{
							TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
						}else
						{
							ANGLES rroll;
							rroll = (Angles)(reqroll + roll);
							ACM.Roll (rroll);
							ACM.ZeroSpecificPower();
						}
					}

				}
			}
		}
	}
}


//
//use leader's unfriendly
//also use leader's phase
//Phase 0: stay out of way until separation say 100-200m
//
//phase 1: highest speed dive down to target + offset to avoid collision
//			AutoShoot() will do firing, all fire with  leader	
//phase 2:	at 200 yards, zoom climb
//				success depends on flyingskill
//				will break out of manoeuvre if attacked, damaged, winchester, bingo
//phase 3: establish circle around target, go to phase 0				



//

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scatter
//Author		R. Hyde 
//Date			Mon 30 Ma 1998
//
//Description	this is for a group of aircraft
//				all aircraft go into break turns
//				then mush around, easy targets
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::Scatter()
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
void	AirStruc::Pincer()
{

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
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


			MoveToDesiredHdg (HdgIntercept,PitchIntercept, ANGLES_5Deg);
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


//
//split force into 2: right and left
//find rightmost  ac in trg group
//find leftmost  ac in trg group
//set manoeuvretime to allow pass
//
//right unfriendly = rightmost in trg group
//fly to unfriendly beam(use desired hdg to set up which beam)

//exit when manoeuvretime up (something went wrong)
//or targeton tail
//reset unfriedly to one with lowest HdgIntercept 
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
void	AirStruc::MultiWave()
{
 //The second wave gets set to this manoeuvre.
 //Aircraft are set to climb. This should provide separation and an advantage
 //Only exit when time is up and in engage range
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
			MoveToDesiredHdg (HdgIntercept, ANGLES_10Deg, ANGLES_5Deg);
			if  (		(!ManoeuvreTimeLeft())
					&&	(Range < ENGAGERANGE)
				)
					ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}



//	until range to unfriendly is < ENGAGERANGE
//		followleader using formpos to determine distance
//	then slect manoeuvre
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
void	AirStruc::DiveAndZoom ()

{
 	SWord	deltapitch_pos,deltapitch_sign;
 	SLong	temp_range;
 	COORDS3D	target;
 	SLong		t,actualrange;
 	AirStrucPtr	unfriendly = *ai.unfriendly;
  	SWord		deltaroll;										//RDH 14Mar96
 	SWord		easestickforward;
 	ANGLES		local_PI;
   	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	FP desiredturn;
	SWord	reqdeltapitch,reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;

 
 	local_PI  = PitchIntercept;
	reqdeltahdg = 	hdg - HdgIntercept;
 	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
	reqdeltapitch = PitchIntercept - fly.cpitch;//	fly.cpitch - PitchIntercept;

 
 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
  			MoveToThrust (100);
 			ai.ManStep = PHASE1;
			SetManoeuvreTime (2000);

 		}
 		case PHASE1:
 		{
  			if  (SubjectOnTargetTail(ANGLES_120Deg))
  			{
  				ai.ManStep = PHASE2;
  			}
			if (!ManoeuvreTimeLeft())
 			{
 				ai.manoeuvre = MANOEUVRE_SELECT;
 			}
			target = ai.unfriendly->World;
			
			target.X = ai.unfriendly->World.X;
			target.Y = ai.unfriendly->World.Y + FT_3000;
			target.Z = ai.unfriendly->World.Z;
			InterceptandRange (&target);


			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode RDH 16Dec98 			TurnFightSub(HdgIntercept, TRUE, ANGLES_0Deg, target);
//			SWord reqroll;
//			if (reqdeltahdg > 0)
//				reqroll = ANGLES_290Deg;
//			else
//				reqroll = ANGLES_70Deg;
//			ACM.Roll ((Angles)reqroll);
////DeadCode DAW 25Nov98 			ACM.LiftLimit();
//			ACM.ZeroSpecificPower();

 			break;
 		}

 		case PHASE2:
 		{
  			if  (		(ClosureLessThan(MPH50))
					&&	(SubjectOnTargetTail(ANGLES_45Deg))
					&&	((World.Y - ai.unfriendly->World.Y) < FT_1000)
				)
  			{
  				GainSpeed ();									//RDH 05Jan99
  			}else
  			{
  				LeadUnFriendly ();
  			}
  			if  ((Range - (World.Y - ai.unfriendly->World.Y)) < ENGAGERANGE)
 
  			{
 				SetManoeuvreTime (5000);
  				ai.ManStep = PHASE3;
				ACM.maxdeltaforclosework = 0.3;
  			}
  			if (local_PI << ANGLES_90Deg)
  			{
  				ai.manoeuvre = MANOEUVRE_SELECT;
  			}
 			break;
 		}
 		case PHASE3:
 		{
 			temp_range = Range; 
			SLong vx, vy, vz;

			CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);

			target.X = ai.unfriendly->World.X + vx;
			target.Y = ai.unfriendly->World.Y + vy;
			target.Z = ai.unfriendly->World.Z + vz;
			InterceptandRange (&target);

			Float fpitch, fhdg;
			SWord reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
				if  (	(	(fpitch < ACM.maxdeltaforclosework)
					&&	(fpitch > -ACM.maxdeltaforclosework)
					&&	(fhdg < ACM.maxdeltaforclosework)
					&&	(fhdg > -ACM.maxdeltaforclosework)
				)
			)
			{
				TurnFightPhase1(HdgIntercept, FALSE, ANGLES_0Deg, target);
			}else
			{
				ANGLES rroll;
				rroll = (Angles)(reqroll + roll);
				ACM.Roll (rroll);
				ACM.ZeroSpecificPower();
			}
//DeadCode RDH 25Nov98 			ACM.LiftLimit();

			if  (	(!ManoeuvreTimeLeft())
					 ||
					(		(TargetOnSubjectTail(ANGLES_90Deg))
					&&	((World.Y - ai.unfriendly->World.Y) < FT_1000)
					)
				)
			{
			 	ai.ManStep = PHASE0;
				ai.manoeuvre=MANOEUVRE_ZOOM;
			}
 			if  (	(ai.combatskill < SKILL_VETERAN)
 			  	&&	(ChkAtDesiredHdg (HdgIntercept,ANGLES_5Deg))
 				)
 				FireABullet(30);
  			
 			break;
 		}
 
 	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PanicTurn
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
void	AirStruc::PanicTurn()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	COORDS3D	target;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
 			ai.desiredhdg = hdg + ANGLES_60Deg; 

			SetManoeuvreTime (1500);

			ai.ManStep = PHASE1;
		}
		case PHASE1:
 		{
 			if  (		(!ManoeuvreTimeLeft())
				)
 			{
 				ai.ManStep = PHASE3;
				SetManoeuvreTime (6000);
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg, ANGLES_5Deg, ANGLES_5Deg))
 			{
				if (Math_Lib.rnd(6))
				{
					ai.ManStep = PHASE3;
					SetManoeuvreTime (6000);
				}else
				{
 					ai.ManStep = PHASE2;
 					ai.desiredhdg = hdg - ANGLES_120Deg; 
				}
 			}
 			break;
 		}
 		case PHASE2:
 		{
 			if (	(!ManoeuvreTimeLeft())
 					||	(Range > COMBATRANGE)
 					)
 			{
 				ai.ManStep = PHASE3;
				SetManoeuvreTime (6000);
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg,ANGLES_5Deg))
 			{
				if (Math_Lib.rnd(6))
				{
					ai.ManStep = PHASE3;
					SetManoeuvreTime (6000);
				}else
				{
	 				ai.ManStep = PHASE1;
 					ai.desiredhdg = hdg + ANGLES_120Deg; 
				}
 			}
 			break;
 		}

		case PHASE3:
		{
			ACM.maxdeltaforclosework = 0.1;
//DeadCode RDH 16Dec98 			ai.ManStep = PHASE1;
			target.X = ai.unfriendly->World.X;
			target.Y = ai.unfriendly->World.Y;
			target.Z = ai.unfriendly->World.Z;
			InterceptandRange (&target);
			TurnFightPhase1(HdgIntercept, FALSE, ANGLES_0Deg, target);
//DeadCode RDH 16Dec98 			TurnWithPitchChange(HdgIntercept, FALSE,target);
//DeadCode RDH 16Dec98 			if (ai.ManStep == PHASE1)
//DeadCode RDH 16Dec98 				ai.ManStep = PHASE3;
 			if (!ManoeuvreTimeLeft())
 			{
  				ai.manoeuvre = MANOEUVRE_SELECT;
 			}

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
void	AirStruc::LeadPursuit()
{
//	ifcombatakill high
//		turn in parallel plane so that target still visible
//
//	calc ideal lead
//		could base calc on maintaining collision course(hdg-hdgintercept?)
//	actual lead depends also on skill
//
// end after x secs or within DANGERRANGE

//DONE IN TURNING FIGHT	
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
void	AirStruc::LagPursuit()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	COORDS3D	target;
	SLong		time;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());

			SetManoeuvreTime (2000);
			ai.ManStep = PHASE1;
			ai.desiredroll = unfriendly->roll;
			if (unfriendly->roll << ANGLES_180Deg)
				ai.desiredhdg = ANGLES_270Deg;
			else
				ai.desiredhdg = ANGLES_90Deg;

		}
		case PHASE1:
		{
				SWord c,s;
				SWord newhdg;
				SLong range;
				newhdg = unfriendly->hdg + ai.desiredhdg;
				Math_Lib.high_sin_cos((Angles)newhdg,s,c);
				if (SubjectOnTargetTail(ANGLES_90Deg))
					range = METRES200;
				else
					ai.manoeuvre = MANOEUVRE_SELECT;

				target.X = unfriendly->World.X + MULSHSIN(s, range, ANGLES_SHIFT);
				target.Y = unfriendly->World.Y;
				target.Z = unfriendly->World.Z + MULSHSIN(c, range, ANGLES_SHIFT);
				InterceptandRange (&target);

			TurnFightPhase1(HdgIntercept, FALSE, ANGLES_0Deg, target);
//DeadCode RDH 16Dec98 			TurnFightSub(HdgIntercept, FALSE,ANGLES_0Deg,target);
			if  (		(!ManoeuvreTimeLeft())
					||	(		(ai.desiredroll << ANGLES_180Deg)
							&&	(unfriendly->roll >>ANGLES_180Deg)
						)
					||	(		(ai.desiredroll >> ANGLES_180Deg)
							&&	(unfriendly->roll << ANGLES_180Deg)
						)
				)
				ai.manoeuvre = MANOEUVRE_SELECT;

		}
	}





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
void	AirStruc::Circumvent()
{
	//will not be implemented
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
//rdhvoid	AirStruc::DecoyActive()
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
//rdh void	AirStruc::DecoyPassive()
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
void	AirStruc::RoundAbout()
{

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;

			ACM.Thrust (ThrustfromFF());
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
			ACM.Roll ((Angles)desroll);

			ACM.Pitch (BestClimbAngle());
 			if  (		((Range - (World.Y - ai.unfriendly->World.Y)) < ENGAGERANGE)
					&&	((World.Y - ai.unfriendly->World.Y) > FT_3000)
				)
			{
 		    	ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
			}

		}

//DEADCODE RDH 05/04/99 		case PHASE1:
//DEADCODE RDH 05/04/99 		{
//DEADCODE RDH 05/04/99 			ACM.Roll (ai.desiredroll);
//DEADCODE RDH 05/04/99 			ACM.Pitch (BestClimbAngle());
//DEADCODE RDH 05/04/99 			ACM.MinHeight (FT_2000);
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 			if  (!ManoeuvreTimeLeft())
//DEADCODE RDH 05/04/99 			{
//DEADCODE RDH 05/04/99  		    	ai.ManStep = PHASE0;
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 				if (ai.firsttactic == TACTIC_LINEABREAST)
//DEADCODE RDH 05/04/99 					ai.manoeuvre = MANOEUVRE_LINEABREAST;
//DEADCODE RDH 05/04/99 				else if (ai.firsttactic == TACTIC_LINEASTERN)
//DEADCODE RDH 05/04/99 					ai.manoeuvre = MANOEUVRE_LINEASTERN;
//DEADCODE RDH 05/04/99 				else
//DEADCODE RDH 05/04/99 					ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE RDH 05/04/99 			}
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 		}
	}
//	if leader attain the desiredalt
//	else line astern
//	if unfriendly is set
//			fly towards for x secs
//			flyaway and repeat
//	else
//			circle

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
void	AirStruc::ResetUnfriendly()
{
//	reset the unfriendlies, so that ac goes after a more appropriate one
//	good to do after a pass or a split manoeuvre
//
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
void	AirStruc::SplitManoeuvre()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
			if  (		(MoveToDesiredHdg (ai.desiredhdg, ai.desiredpitch, ANGLES_40Deg))
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
void	AirStruc::HeadOn ( )
{
	//just pass to the side
	//poor pilots may turn too early
	//good pilots may turn early
	//on passing pilot skill will dtermine action

		ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
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
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
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
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca )
				ACM.Pitch (bca);
			else
				ACM.Pitch (PitchIntercept);

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
		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			ACM.Roll ((Angles)reqroll);


			int decisionpoint = Math_Lib.rnd(2);

			if  (		(Range < (2 * BREAKTURNRADIUS ))
					&&	(FF < 200)
				)
			{//poor pilot might turn too early
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
			{//good pilot might turn early to get advantage
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
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca )
				ACM.Pitch (bca);
			else
				ACM.Pitch (PitchIntercept);

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
			MODLIMIT(reqroll, ANGLES_45Deg);
			ACM.Roll ((Angles)reqroll);

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


//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 	ACMMODEL& ACM = *fly.pAcmModel;
//DEADCODE DAW 31/03/99 	MODEL& MOD = *fly.pModel;
//DEADCODE DAW 31/03/99 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 	SLong temp_range;
//DEADCODE DAW 31/03/99 	temp_range = Range; 	
//DEADCODE DAW 31/03/99 	COORDS3D	target;
//DEADCODE DAW 31/03/99 	SWord c,s;
//DEADCODE DAW 31/03/99 	SWord newhdg;
//DEADCODE DAW 31/03/99 	UByte	FF = FlyingFactor();
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 	switch (ai.ManStep)
//DEADCODE DAW 31/03/99 	{
//DEADCODE DAW 31/03/99 		case PHASE0:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			MOD.Rudder = 0;
//DEADCODE DAW 31/03/99 			ACM.Thrust (ThrustfromFF());
//DEADCODE DAW 31/03/99 			SetManoeuvreTime (2000);
//DEADCODE DAW 31/03/99 			SWord dhdg = HdgIntercept - hdg;
//DEADCODE DAW 31/03/99 			if ((dhdg) > 0)
//DEADCODE DAW 31/03/99 				ai.desiredhdg = ANGLES_90Deg + hdg;
//DEADCODE DAW 31/03/99 			else
//DEADCODE DAW 31/03/99 				ai.desiredhdg = ANGLES_270Deg + hdg;
//DEADCODE DAW 31/03/99 			if (FF < 120)
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				newhdg = unfriendly->hdg + ai.desiredhdg;
//DEADCODE DAW 31/03/99 				Math_Lib.high_sin_cos((Angles)newhdg,s,c);
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 				target.X = unfriendly->World.X + METRES30 * s / ANGLES_SHIFT;
//DEADCODE DAW 31/03/99 				target.Y = unfriendly->World.Y;
//DEADCODE DAW 31/03/99 				target.Z = unfriendly->World.Z + METRES30 * c / ANGLES_SHIFT;
//DEADCODE DAW 31/03/99 				InterceptandRange (&target);
//DEADCODE DAW 31/03/99  				ai.desiredhdg = HdgIntercept;
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 			ai.ManStep = PHASE1;
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 		case PHASE1:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			SWord bca = (SWord) BestClimbAngle();
//DEADCODE DAW 31/03/99 			SWord pitch = PitchIntercept;
//DEADCODE DAW 31/03/99 			if (pitch > bca)
//DEADCODE DAW 31/03/99 				pitch = bca;
//DEADCODE DAW 31/03/99 			ACM.Pitch (pitch);
//DEADCODE DAW 31/03/99 			if  (		(ai.desiredhdg == ANGLES_90Deg )
//DEADCODE DAW 31/03/99 					||	(ai.desiredhdg == ANGLES_270Deg )
//DEADCODE DAW 31/03/99 				)
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				newhdg = unfriendly->hdg + ai.desiredhdg;
//DEADCODE DAW 31/03/99 				Math_Lib.high_sin_cos((Angles)newhdg,s,c);
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 				target.X = unfriendly->World.X + METRES30 * s / ANGLES_SHIFT;
//DEADCODE DAW 31/03/99 				target.Y = unfriendly->World.Y;
//DEADCODE DAW 31/03/99 				target.Z = unfriendly->World.Z + METRES30 * c / ANGLES_SHIFT;
//DEADCODE DAW 31/03/99 				InterceptandRange (&target);
//DEADCODE DAW 31/03/99  				ai.desiredhdg = HdgIntercept;
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			SWord	reqdeltahdg = hdg - ai.desiredhdg;
//DEADCODE DAW 31/03/99 		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DEADCODE DAW 31/03/99 			ACM.Roll ((Angles)reqroll);
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			if  (!ManoeuvreTimeLeft())
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE DAW 31/03/99 			if (Range < (3 * BREAKTURNRADIUS /2))
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				
//DEADCODE DAW 31/03/99 				FF = Math_Lib.rnd((int) FF);
//DEADCODE DAW 31/03/99 				if (FF < 90)
//DEADCODE DAW 31/03/99 				{
//DEADCODE DAW 31/03/99 					ai.manoeuvre = MANOEUVRE_PANICTURN;
//DEADCODE DAW 31/03/99 					ai.ManStep = PHASE0;
//DEADCODE DAW 31/03/99 				}else if (FF < 180)
//DEADCODE DAW 31/03/99 				{
//DEADCODE DAW 31/03/99 					ai.manoeuvre = MANOEUVRE_BREAKTURN;
//DEADCODE DAW 31/03/99 					ai.ManStep = PHASE0;
//DEADCODE DAW 31/03/99 				}else
//DEADCODE DAW 31/03/99 					ai.ManStep = PHASE2;
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 			break;
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 		case PHASE2:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			ANGLES bca = BestClimbAngle();
//DEADCODE DAW 31/03/99 			if (PitchIntercept > bca )
//DEADCODE DAW 31/03/99 				ACM.Pitch (bca);
//DEADCODE DAW 31/03/99 			else
//DEADCODE DAW 31/03/99 				ACM.Pitch (PitchIntercept);
//DEADCODE DAW 31/03/99 			SWord	reqdeltahdg = hdg - ai.desiredhdg;
//DEADCODE DAW 31/03/99 		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DEADCODE DAW 31/03/99 			ACM.Roll ((Angles)reqroll);
//DEADCODE DAW 31/03/99 			if  (!ManoeuvreTimeLeft())
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE DAW 31/03/99 			if	(SubjectOnTargetTail(ANGLES_80Deg))
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				if	(		(ai.unfriendly == Manual_Pilot.ControlledAC2)
//DEADCODE DAW 31/03/99 						&&	(((AirStruc*)ai.unfriendly)->Follower())
//DEADCODE DAW 31/03/99 					)
//DEADCODE DAW 31/03/99 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEADON, MSG_HEADON, ((AirStruc*)ai.unfriendly)->Follower(), this, ((AirStruc*)ai.unfriendly)));
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 	  			int startpoint = Math_Lib.rnd(6);
//DEADCODE DAW 31/03/99 				ai.ManStep = PHASE0;
//DEADCODE DAW 31/03/99 	  			switch (startpoint)
//DEADCODE DAW 31/03/99   				{
//DEADCODE DAW 31/03/99   					case	0:
//DEADCODE DAW 31/03/99   						{
//DEADCODE DAW 31/03/99 							ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
//DEADCODE DAW 31/03/99 							break;
//DEADCODE DAW 31/03/99 						}
//DEADCODE DAW 31/03/99   					case	1:
//DEADCODE DAW 31/03/99   						{
//DEADCODE DAW 31/03/99 							ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
//DEADCODE DAW 31/03/99 							break;
//DEADCODE DAW 31/03/99 						}
//DEADCODE DAW 31/03/99 	  				case	2:
//DEADCODE DAW 31/03/99   						{
//DEADCODE DAW 31/03/99 							ai.manoeuvre = MANOEUVRE_EXTENSION;
//DEADCODE DAW 31/03/99 							break;
//DEADCODE DAW 31/03/99 						}
//DEADCODE DAW 31/03/99 	  				case	3:
//DEADCODE DAW 31/03/99   						{
//DEADCODE DAW 31/03/99 							ai.manoeuvre = MANOEUVRE_JINK;
//DEADCODE DAW 31/03/99 							break;
//DEADCODE DAW 31/03/99 						}
//DEADCODE DAW 31/03/99 	 				case	4:
//DEADCODE DAW 31/03/99   						{
//DEADCODE DAW 31/03/99 							ai.manoeuvre = MANOEUVRE_BREAKTURN;
//DEADCODE DAW 31/03/99 							break;
//DEADCODE DAW 31/03/99 						}
//DEADCODE DAW 31/03/99 	  				case	5:
//DEADCODE DAW 31/03/99   						{
//DEADCODE DAW 31/03/99 							ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
//DEADCODE DAW 31/03/99 							break;
//DEADCODE DAW 31/03/99 						}
//DEADCODE DAW 31/03/99 				}
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 	}
//DEADCODE DAW 31/03/99 	
//DEADCODE DAW 31/03/99 }
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
void	AirStruc::LineAstern()
{
//only followers go line astern. We don't link flights
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	if (!leader) 
	{//leader, do same as roundabout, get height, dive and then zoom
	 //at end of zoom, choose manoeuvre based on firsttactic
			ai.ManStep = PHASE0;
			ai.manoeuvre = MANOEUVRE_ROUNDABOUT;			
	}else
	{//follower
		if (Range < WEAPONSRANGE)
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
					MOD.Rudder = 0;
					ACM.Thrust (ThrustfromFF());
					ai.ManStep = PHASE1;
					ACM.maxdeltaforclosework = 0.0;

				}
				case PHASE1:
				{

					
					if (!leader)
						ai.manoeuvre = MANOEUVRE_SELECT;					//if no leader break manoeuvre
					else
					{

 						COORDS3D	target;
 						target = leader->World; 
 						InterceptandRange(&target);
						Float fpitch, fhdg;
						SWord reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
						if  (		(	(fpitch < ACM.maxdeltaforclosework)
									&&	(fpitch > -ACM.maxdeltaforclosework)
									&&	(fhdg < ACM.maxdeltaforclosework)
									&&	(fhdg > -ACM.maxdeltaforclosework)
									)
							)
						{
							TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
						}else
						{
							ANGLES rroll;
							rroll = (Angles)(reqroll + roll);
							ACM.Roll (rroll);
							ACM.ZeroSpecificPower();
						}
						if (Range < METRES200)
 							   ACM.SpeedBrakesOut();
 						else
 							ACM.SpeedBrakesIn();
 						if (Range < METRES400)
 							ACM.Thrust (0);
 						else
 							ACM.Thrust (ThrustfromFF());

					}
//DEADCODE PD 26/02/99 						FP desiredturn;
//DEADCODE RDH 05/04/99 						double desiredturn;
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 						COORDS3D	target;
//DEADCODE RDH 05/04/99 						target = leader->World; 									//JIM 02Aug96
//DEADCODE RDH 05/04/99 						InterceptandRange(&target);
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 						SWord	reqdeltahdg,reqdeltahdg_sign;
//DEADCODE RDH 05/04/99 						UWord	reqdeltahdg_pos;
//DEADCODE RDH 05/04/99 						reqdeltahdg = 	hdg - HdgIntercept;
//DEADCODE RDH 05/04/99 						Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 						SWord	reqdeltapitch,reqdeltapitch_sign;
//DEADCODE RDH 05/04/99 						UWord	reqdeltapitch_pos;
//DEADCODE RDH 05/04/99 						reqdeltapitch = (SWord)PitchIntercept - (SWord)fly.cpitch;
//DEADCODE RDH 05/04/99 						Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 										
//DEADCODE RDH 05/04/99 						if  (		(		(reqdeltahdg_pos < ANGLES_40Deg)
//DEADCODE RDH 05/04/99 							&&	(ACM.maxdeltaforclosework == 0.0)
//DEADCODE RDH 05/04/99 							)
//DEADCODE RDH 05/04/99 							||
//DEADCODE RDH 05/04/99 								(		(reqdeltahdg_pos < ANGLES_45Deg)
//DEADCODE RDH 05/04/99 									&&	(ACM.maxdeltaforclosework != 0.0)
//DEADCODE RDH 05/04/99 								)		
//DEADCODE RDH 05/04/99 							)
//DEADCODE RDH 05/04/99 						{
//DEADCODE RDH 05/04/99 				 			SWord reqroll = RollforTurn(reqdeltapitch, reqdeltahdg, desiredturn, target);
//DEADCODE RDH 05/04/99 							ACM.Roll ((Angles)reqroll);
//DEADCODE RDH 05/04/99 			
//DEADCODE RDH 05/04/99 						}else
//DEADCODE RDH 05/04/99 						{
//DEADCODE RDH 05/04/99 							ACM.maxdeltaforclosework = 0.0;
//DEADCODE RDH 05/04/99 							TurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, ANGLES_0Deg);
//DEADCODE RDH 05/04/99 							ACM.SetRudder(0);
//DEADCODE RDH 05/04/99 						}
//DEADCODE RDH 05/04/99 						InterceptandRange (&leader->World);
//DEADCODE RDH 05/04/99 						if (Range < METRES200)
//DEADCODE RDH 05/04/99 							   ACM.SpeedBrakesOut();
//DEADCODE RDH 05/04/99 						else
//DEADCODE RDH 05/04/99 							ACM.SpeedBrakesIn();
//DEADCODE RDH 05/04/99 						if (Range < METRES400)
//DEADCODE RDH 05/04/99 							ACM.Thrust (0);
//DEADCODE RDH 05/04/99 						else
//DEADCODE RDH 05/04/99 							ACM.Thrust (ThrustfromFF());
//DEADCODE RDH 05/04/99 					
//DEADCODE RDH 05/04/99 					}

				}
			}
		}
	}
}


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

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BarrelRollAttack
//Author		Andrew McRae
//Date			Mon 2 Jun 1997
//
//Description	1.69
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::BarrelRollAttack ( )
{
//roll wings level
//pull up
//slow roll towads enemy to keep him in view
//when upside down and behind, pull down

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust (100);
			SetManoeuvreTime (1500);
 			ai.desiredroll = ANGLES_0Deg; 
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll (ai.desiredroll);
			ACM.SetRelAoA(ANGLES_4Deg);

//			ACM.Pitch (ANGLES_30Deg);
//			ACM.MinHeight (FT_2000);
//DEADCODE RDH 27/05/99 			if (TooLow())
//DEADCODE RDH 27/05/99 			{
//DEADCODE RDH 27/05/99 				ai.ManStep = PHASE0;
//DEADCODE RDH 27/05/99 				ai.manoeuvre = MANOEUVRE_LOWALT;
//DEADCODE RDH 27/05/99 			}

			if  ( !ManoeuvreTimeLeft())
  				ai.manoeuvre = MANOEUVRE_SELECT;
			if (TargetOnSubjectTail(ANGLES_40Deg))
				ai.ManStep = PHASE2;
			break;

		}
		case PHASE2:
		{
			COORDS3D	target;
			Float fpitch,fhdg;
			AirStrucPtr	unfriendly = *ai.unfriendly;
			target = ai.unfriendly->World;

			SWord	reqdeltahdg,reqdeltahdg_sign;
			UWord	reqdeltahdg_pos;
			reqdeltahdg = 	hdg - HdgIntercept;
 			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

			ANGLES reqroll = roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
			ACM.Roll (reqroll);
			ACM.TurnRate(fpitch);
//DEADCODE RDH 27/05/99 			if (TooLow())
//DEADCODE RDH 27/05/99 			{
//DEADCODE RDH 27/05/99 				ai.ManStep = PHASE0;
//DEADCODE RDH 27/05/99 				ai.manoeuvre = MANOEUVRE_LOWALT;
//DEADCODE RDH 27/05/99 			}

			if  (		
						(reqdeltahdg_pos < ANGLES_50Deg)
					||	(World.Y < unfriendly->World.Y)
				)
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = PHASE0;
			}
//			ACM.MinHeight (FT_2000);

		}
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scissors
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
void AirStruc::Scissors ( )

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
 			ACM.Thrust (70);
			SetManoeuvreTime (1500);
 			ai.ManStep = PHASE1;
 			ai.desiredhdg = hdg - ANGLES_60Deg; 
 		}
 		case PHASE1:
 		{
 			if (!ManoeuvreTimeLeft())
 			{
 				ai.ManStep = PHASE3;
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg, ANGLES_5Deg))
 			{
 				ai.ManStep = PHASE2;
 				ai.desiredhdg = hdg + ANGLES_120Deg; 
 			}
 			break;
 		}
 		case PHASE2:
 		{
 			if (	(!ManoeuvreTimeLeft())
 				||	 (!(TargetFacingSubject(ANGLES_40Deg)))
 					||	(Range > COMBATRANGE)
 					)
 			{
 				ai.ManStep = PHASE3;
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg,ANGLES_5Deg))
 			{
 				ai.ManStep = PHASE1;
 				ai.desiredhdg = hdg - ANGLES_120Deg; 
 			}
 			break;
 		}
 		case PHASE3:
 		{
 
 			ai.manoeuvre = MANOEUVRE_SELECT;
 			break;
 		}
 	}

	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			ai.desiredhdg = hdg + ANGLES_120Deg; 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_4Deg,1);
//DeadCode RDH 26Mar98 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_100Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				ai.desiredhdg = hdg - ANGLES_240Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (	(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				||	 (!(TargetFacingSubject(ANGLES_40Deg)))
//DeadCode RDH 26Mar98 					||	(Range > COMBATRANGE)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_4Deg,1);
//DeadCode RDH 26Mar98 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_100Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 				ai.desiredhdg = hdg + ANGLES_240Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 		case PHASE3:
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 			ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 			break;
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MildScissors
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
void AirStruc::MildScissors ( )

{
	
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
 			ACM.Thrust (70);
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
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg,ANGLES_5Deg))
 			{
 				ai.ManStep = PHASE2;
 				ai.desiredhdg = hdg + ANGLES_30Deg; 
 			}
 			break;
 		}
 		case PHASE2:
 		{
 			if (	(!ManoeuvreTimeLeft())
 				||	 (!(TargetFacingSubject(ANGLES_40Deg)))
 					||	(Range > COMBATRANGE)
 					)
 			{
 				ai.ManStep = PHASE3;
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg,ANGLES_5Deg))
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
//Procedure		TurningFight
//Author		R. Hyde 
//Date			Wed 13 Dec 1995
//
//Description	attempt to lead, find Hdgintercept and delta, set roll
//				roll should not give alt lose
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void AirStruc::TurningFight ()
//
//{
//	ACMMODEL& ACM = *fly.pAcmModel;
//	MODEL& MOD = *fly.pModel;
//
//	SLong temp_range;
//	temp_range = Range; 	
//
//	switch (ai.ManStep)
//	{
//		case PHASE0:
//		{
//			ACM.Clear ();
//			if (ai.skill > SKILL_REGULAR)
//				ACM.Thrust (100);
//			else
//				ACM.Thrust (70);
//
//			SetManoeuvreTime (400);
//			ai.ManStep = PHASE1;
//		}
//		case PHASE1:
//		{
//
//			ACM.MinHeight (FT_2000);
//
//		 	SWord	reqdeltahdg = 	Rads2Rowan(MOD.fHdg) - HdgIntercept;
//		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//			ACM.Roll ((Angles)reqroll);
////test
//		UWord y = 0;
//		if (ai.skill > SKILL_REGULAR)
//				y = 4;
//		char strg [32];
//		for (UWord n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "DHdgIntercept  %d ",reqdeltahdg);
//		if (strg[31] == 0)
//			Mono_Text.PrintAt (40,y,(UByte*)strg);
//
//		for (n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "Range,m  %d ",Range/100);
//		if (strg[31] == 0)
//			Mono_Text.PrintAt (40,y+1,(UByte*)strg);
//
//		for (n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "ReqRoll  %d ",reqroll);
//		if (strg[31] == 0)
//			Mono_Text.PrintAt (40,y+2,(UByte*)strg);
///

//DeadCode RDH 17Apr98 			if (HdgIntercept > Rads2Rowan (MOD.fHdg))
//DeadCode RDH 17Apr98 			{
//DeadCode RDH 17Apr98 //				ACM.DesiredRoll (ANGLES_30Deg);
//DeadCode RDH 17Apr98 				ACM.Roll (ANGLES_30Deg);
//DeadCode RDH 17Apr98 			}
//DeadCode RDH 17Apr98 			else
//DeadCode RDH 17Apr98 			{
//DeadCode RDH 17Apr98 //				ACM.DesiredRoll (ANGLES_330Deg);
//DeadCode RDH 17Apr98 				ACM.Roll (ANGLES_330Deg);
//DeadCode RDH 17Apr98 			}

//			ACM.Pitch (PitchIntercept);


			// test
//			ACM.DesiredRoll (ANGLES_0Deg);
//			ACM.KeepWingsLevel ();
//			ACM.FlyDesiredRoll ();

//			if  (!ManoeuvreTimeLeft())
//				ai.manoeuvre = MANOEUVRE_SELECT;
//
//		}
//	}

//DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		time;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 	UWord	acroll_pos,aoa_pos;
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll,aoa_sign;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Jul96 			ANGLES tmp =fly.aoa;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Jul96 			tmp =fly.acroll;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Jul96 			tmp =fly.croll ;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Jul96 			tmp =hdg ;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Jul96 			tmp =fly.cpitch;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (	(TargetFacingSubject(ANGLES_10Deg))
//DeadCode RDH 26Mar98 				&&	SubjectFacingTarget(ANGLES_10Deg)
//DeadCode RDH 26Mar98 				&&	(Range < METRES150)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					HdgIntercept = HdgIntercept + ANGLES_90Deg;
//DeadCode RDH 26Mar98 					PitchIntercept = PitchIntercept + ANGLES_10Deg;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			TightTurn (FT_1000);
//DeadCode RDH 26Mar98 		break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}

//}

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
void	AirStruc::SplitS ()

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
 	SWord 	deltaroll;
 	UWord	deltaroll_pos;
 	SWord	deltaroll_sign;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	Float fpitch, fhdg;

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
				MOD.Rudder = 0;
				ACM.Thrust (ThrustfromFF());
				COORDS3D	target;
				target = unfriendly->World;
				ANGLES reqroll = (roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch,fhdg ));
				if (	(reqroll >> ANGLES_120Deg)
					&&	(reqroll << ANGLES_240Deg)
					)
					ai.desiredroll = reqroll;
				else
					ai.desiredroll = ANGLES_180Deg;
				SetManoeuvreTime (1000);

				ai.ManStep = PHASE1;
			}
		}
		case PHASE1:
		{

			ACM.Roll (ai.desiredroll);
			deltaroll = (SWord) (ai.desiredroll - roll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if  (		( roll >> ANGLES_90Deg)
					&&	(roll << ANGLES_270Deg)
					&&	(deltaroll_pos <ANGLES_30Deg)
				)
				ACM.LiftLimit();
			else
				ACM.SetElevator(0);

			if (deltaroll_pos <ANGLES_20Deg)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime (1500);
			}
			break;
		}
 		case PHASE2:
		{
			MOD.Aileron = 0;
			ACM.LiftLimit();
			if  ( 		(!ManoeuvreTimeLeft())
					||  (		(DesiredPitchChk (ANGLES_315Deg,ANGLES_20Deg))
							&&	(		(roll << ANGLES_90Deg)
									||	(roll >> ANGLES_270Deg)
								)						
						)
				)
	 			{
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
//Zoom for only a few seconds in hope of gettig other a/c to slip under
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::ZoomandDrop ()
{

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

//	ACM.Step = ai.ManStep;

		
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (1000);
			MOD.Rudder = 0;
			ACM.Thrust (0);
			ACM.SpeedBrakesOut ();

			ai.ManStep = PHASE1;
		}

		case PHASE1:
		{
			ACM.KeepWingsLevel ();
			ACM.Pitch (ANGLES_40Deg);
			if  (	(MOD.Inst.MachNo < 0.3)
				||	(!ManoeuvreTimeLeft ())
				)
			{
				ACM.Clear ();
				ACM.Thrust (ThrustfromFF());
				ACM.SpeedBrakesIn ();
				SWord	reqdeltahdg,reqdeltahdg_sign;
				UWord	reqdeltahdg_pos;
				reqdeltahdg = 	hdg - HdgIntercept;
	 			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
				if (reqdeltahdg_pos < ANGLES_30Deg)
				{
					ai.ManStep = PHASE0;
					ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
				}
				else
				{
					SetManoeuvreTime (700);
					ai.ManStep = PHASE2;
				}
			}

			break;
		}


		case PHASE2:
		{
			ACM.Pitch (ANGLES_290Deg);
			ACM.KeepWingsLevel ();
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}

	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StraightandLevel
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::StraightandLevel ()
{

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;


	UByte	FF = FlyingFactor();

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (2000);
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			//this manoeuvre is only done by poor pilots so we can reduce speed so that
			//other can catch up and attack
				FP	Mach = MOD.Inst.MachNo;
			if (Mach < 0.5)
				ACM.Thrust (ThrustfromFF());
			else
				ACM.Thrust (0);

			if (FF > 160)
			{
				if (Mach > 0.9)
					Mach = 0.9;
				if (Mach < 0.3)
					Mach = 0.3;

				ANGLES desiredpitch;
				SWord deltapitch;
				deltapitch = ANGLES_5Deg * ((Mach - 0.3)/0.6);
				desiredpitch = (Angles)((SWord)ANGLES_355Deg + deltapitch);
				ACM.Pitch (desiredpitch);

			}else
				ACM.Pitch (ANGLES_1Deg);
			ACM.KeepWingsLevel ();
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpinOut
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
void AirStruc::SpinOut ( )

{
	SWord	deltaroll;
	UWord	deltayaw_pos;
	SWord	deltayaw_sign;

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust (0);
			ACM.SetElevator(-MAXELEVATOR/2);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if (MOD.RotVel.y > 0)
			{
				MOD.Rudder = MAXRUDDER;
			}else
			{
				MOD.Rudder = -MAXRUDDER;
			}
			ai.ManStep = PHASE2;
			SetManoeuvreTime (2000);
			break;
		}
		case PHASE2:
		{
			ACM.SetElevator(-MAXELEVATOR);
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE0;
				ACM.SetElevator(0);
				MOD.Rudder = 0;
				ai.manoeuvre = MANOEUVRE_SPINRECOVERY;

			}
			break;
		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiveforHome
//Author		Andrew McRae
//Date			Tue 3 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::DiveforHome ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 //DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
 	SLong	temp_range;
 
 	temp_range = Range; 	
 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{

			MOD.Rudder = 0;
  			MoveToThrust (100);
 			SetManoeuvreTime (2000);
 			ai.ManStep = PHASE1;

			ACM.Thrust (ThrustfromFF());

			if (ai.homebase)
				InterceptandRange (&ai.homebase->World);
			else
				ai.manoeuvre = MANOEUVRE_SELECT;
 			ai.desiredhdg = HdgIntercept; 
 		}
 		case PHASE1:
 		{
//##			if (Range < MILES01)
//			{//within mile of home
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
//			Range = temp_range; 	
//			if (Range > BREAKOFFRANGE)
//			{//xx from action, reconsider
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
			if (Range < DANGERRANGE)
			{//xx from action, reconsider
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;


			ANGLES	desiredpitch;
			if (MOD.Pos.y < FT_3000)
				desiredpitch = ANGLES_0Deg;
			else
				desiredpitch = ANGLES_340Deg;

			MoveToHdg (ai.desiredhdg, desiredpitch);
 		}
 	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GoHome
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
void AirStruc::GoHome ( )

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 //DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
 	SLong	temp_range;
 
 	temp_range = Range; 	
 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
  			MoveToThrust (100);
 			SetManoeuvreTime (2000);
 			ai.ManStep = PHASE1;

			ACM.Thrust (ThrustfromFF());

			if (ai.homebase)
				InterceptandRange (&ai.homebase->World);
			else
				ai.manoeuvre = MANOEUVRE_SELECT;
 			ai.desiredhdg = HdgIntercept; 
			Range = temp_range;
 			if	(		TargetOnSubjectTail(ANGLES_10Deg)
 					&&	(Range < 2 * WEAPONSRANGE)
 					&&	(ai.combatskill >= SKILL_REGULAR)
 				)
 				ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 

 		}
 		case PHASE1:
 		{
//##			if (Range < MILES01)
//			{//within mile of home
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
			Range = temp_range; 	
//			if (Range > BREAKOFFRANGE)
//			{//xx from action, reconsider
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
			if (Range < DANGERRANGE)
			{//xx from action, reconsider
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;


				FP	Mach = MOD.Inst.MachNo;
				if (Mach > 0.9)
					Mach = 0.9;
				if (Mach < 0.3)
					Mach = 0.3;

				ANGLES desiredpitch;
				SWord deltapitch;
				deltapitch = ANGLES_5Deg * ((Mach - 0.3)/0.6);
				desiredpitch = (Angles)((SWord)ANGLES_355Deg + deltapitch);
//				ACM.Pitch (desiredpitch);

 			MoveToHdg (ai.desiredhdg, desiredpitch);
 		}
 	}

}
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
//DeadCode RDH 26Mar98 	SLong	temp_range;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	temp_range = Range; 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 			lastwaypoint = waypoint;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 			while (lastwaypoint->next)
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 				lastwaypoint = lastwaypoint->next;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 			InterceptandRange (&lastwaypoint->World);
//DeadCode RDH 26Mar98 			InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			ai.desiredhdg = HdgIntercept; 
//DeadCode RDH 26Mar98 			Range = temp_range;
//DeadCode RDH 26Mar98 //jink a bit possibly
//DeadCode RDH 26Mar98 			if	(		TargetOnSubjectTail(ANGLES_10Deg)
//DeadCode RDH 26Mar98 					&&	(Range < 4 * WEAPONSRANGE)
//DeadCode RDH 26Mar98 					&&	(ai.skill >= SKILL_REGULAR)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 				ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (500);
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 				lastwaypoint = waypoint;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 				while (lastwaypoint->next)
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 					lastwaypoint = lastwaypoint->next;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 				InterceptandRange (&lastwaypoint->World);
//DeadCode RDH 26Mar98 			InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				ai.desiredhdg = HdgIntercept; 
//DeadCode RDH 26Mar98 			Range = temp_range;
//DeadCode RDH 26Mar98 				if	(		TargetOnSubjectTail(ANGLES_10Deg)
//DeadCode RDH 26Mar98 						&&	(Range < 4 * WEAPONSRANGE)
//DeadCode RDH 26Mar98 						&&	(ai.skill >= SKILL_REGULAR)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 					ai.desiredhdg = HdgIntercept + ANGLES_340Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < WEAPONSRANGE)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			MoveToHdg (ai.desiredhdg);
//DeadCode RDH 26Mar98 			if (Range > (BREAKOFFRANGE + METRES1400))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (500);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 				lastwaypoint = waypoint;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 				while (lastwaypoint->next)
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 					lastwaypoint = lastwaypoint->next;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 				InterceptandRange (&lastwaypoint->World);
//DeadCode RDH 26Mar98 			InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				ai.desiredhdg = HdgIntercept; 
//DeadCode RDH 26Mar98 			Range = temp_range;
//DeadCode RDH 26Mar98 				if	(		TargetOnSubjectTail(ANGLES_10Deg)
//DeadCode RDH 26Mar98 						&&	(Range < 4 * WEAPONSRANGE)
//DeadCode RDH 26Mar98 						&&	(ai.skill >= SKILL_REGULAR)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 					ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < WEAPONSRANGE)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			MoveToHdg (ai.desiredhdg);
//DeadCode RDH 26Mar98 			if (Range > (BREAKOFFRANGE + METRES1400))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeForFriendly
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
void AirStruc::MakeForFriendly ( )

{
	
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveAway
//Author		Andrew McRae
//Date			Mon 2 Jun 1997
//
//Description	
//	Not much different from extension. Ant need for both?
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::MoveAway ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (2000);
			ai.ManStep = PHASE1;
			break;
		}
		case PHASE1:
		{
			ACM.MinHeight (FT_1000);
//			ACM.Pitch (ANGLES_5Deg);
			MoveToHdg (HdgIntercept + ANGLES_180Deg, ANGLES_5Deg);
 
			if (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}

}	

//DeadCode RDH 06Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 06Jan99 //Procedure		AccidentalSpinOut
//DeadCode RDH 06Jan99 //Author		R. Hyde 
//DeadCode RDH 06Jan99 //Date			Tue 12 Dec 1995
//DeadCode RDH 06Jan99 //
//DeadCode RDH 06Jan99 //Description	similar to SpinOut, but longer recovery
//DeadCode RDH 06Jan99 //				In some games the accidental manoeuvre can be more different
//DeadCode RDH 06Jan99 //
//DeadCode RDH 06Jan99 //Inputs		
//DeadCode RDH 06Jan99 //
//DeadCode RDH 06Jan99 //Returns	
//DeadCode RDH 06Jan99 //
//DeadCode RDH 06Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 06Jan99 void AirStruc::AccidentalSpinOut ( )
//DeadCode RDH 06Jan99 
//DeadCode RDH 06Jan99 {
//DeadCode RDH 06Jan99 	SWord	deltaroll;
//DeadCode RDH 06Jan99 	UWord	deltayaw_pos;
//DeadCode RDH 06Jan99 	SWord	deltayaw_sign;
//DeadCode RDH 06Jan99 
//DeadCode RDH 06Jan99 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 06Jan99 	MODEL& MOD = *fly.pModel;
//DeadCode RDH 06Jan99 
//DeadCode RDH 06Jan99 	
//DeadCode RDH 06Jan99 	switch (ai.ManStep)
//DeadCode RDH 06Jan99 	{
//DeadCode RDH 06Jan99 		case PHASE0:
//DeadCode RDH 06Jan99 		{
//DeadCode RDH 06Jan99 			ACM.Thrust (0);
//DeadCode RDH 06Jan99 			ACM.SetElevator(-MAXELEVATOR);
//DeadCode RDH 06Jan99 			ai.ManStep = PHASE1;
//DeadCode RDH 06Jan99 		}
//DeadCode RDH 06Jan99 		case PHASE1:
//DeadCode RDH 06Jan99 		{
//DeadCode RDH 06Jan99 			if (MOD.RotVel.y > 0)
//DeadCode RDH 06Jan99 			{
//DeadCode RDH 06Jan99 				MOD.Rudder = MAXRUDDER;
//DeadCode RDH 06Jan99 			}else
//DeadCode RDH 06Jan99 			{
//DeadCode RDH 06Jan99 				MOD.Rudder = -MAXRUDDER;
//DeadCode RDH 06Jan99 			}
//DeadCode RDH 06Jan99 			ai.ManStep = PHASE2;
//DeadCode RDH 06Jan99 			SetManoeuvreTime (4000);
//DeadCode RDH 06Jan99 			break;
//DeadCode RDH 06Jan99 		}
//DeadCode RDH 06Jan99 		case PHASE2:
//DeadCode RDH 06Jan99 		{
//DeadCode RDH 06Jan99 			ACM.SetElevator(-MAXELEVATOR);
//DeadCode RDH 06Jan99 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 06Jan99 			{
//DeadCode RDH 06Jan99 				ai.ManStep = PHASE0;
//DeadCode RDH 06Jan99 				ACM.SetElevator(0);
//DeadCode RDH 06Jan99 				MOD.Rudder = 0;
//DeadCode RDH 06Jan99 				ai.manoeuvre = MANOEUVRE_SPINRECOVERY;
//DeadCode RDH 06Jan99 
//DeadCode RDH 06Jan99 			}
//DeadCode RDH 06Jan99 			break;
//DeadCode RDH 06Jan99 		}
//DeadCode RDH 06Jan99 	}
//DeadCode RDH 06Jan99 
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 	{
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 		{
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98  			MoveToThrust (0);
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			fly.elevator = -MAXELEVATOR;
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			if ((SWord) fly.turnrate > 0)
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			{
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 				fly.rudder = MAXRUDDER;
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			}else
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			{
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 				fly.rudder = -MAXRUDDER;
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			}
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			ai.manoeuvre = MANOEUVRE_SPINOUT;
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			ai.ManStep = PHASE2;
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 			break;
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 		}
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 	}
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 
//DeadCode RDH 06Jan99 //DeadCode RDH 26Mar98 	SetControlSurfaces ();
//DeadCode RDH 06Jan99 
//DeadCode RDH 06Jan99 }

//DeadCode RDH 30Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 30Mar98 //Procedure		LowGYoYo
//DeadCode RDH 30Mar98 //Author		R. Hyde 
//DeadCode RDH 30Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 30Mar98 //
//DeadCode RDH 30Mar98 //Description	
//DeadCode RDH 30Mar98 //
//DeadCode RDH 30Mar98 //Inputs		
//DeadCode RDH 30Mar98 //
//DeadCode RDH 30Mar98 //Returns	
//DeadCode RDH 30Mar98 //
//DeadCode RDH 30Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 30Mar98 void AirStruc::LowGYoYo ( )
//DeadCode RDH 30Mar98 
//DeadCode RDH 30Mar98 {
//DeadCode RDH 26Mar98 	UWord	dhdg_pos;
//DeadCode RDH 26Mar98 	SWord	dhdg_sign;
//DeadCode RDH 26Mar98 	SWord dhdg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			dhdg = (SWord) (hdg - HdgIntercept);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 			if (dhdg_pos < ANGLES_45Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				dhdg_pos = 5*dhdg_pos/4;  
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1);
//DeadCode RDH 26Mar98 			if (	(MoveToDesiredPitch (ANGLES_340Deg,ANGLES_15Deg))
//DeadCode RDH 26Mar98 				||	(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (500);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			dhdg = (SWord) (hdg - HdgIntercept);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 			if (dhdg_pos < ANGLES_45Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				dhdg_pos = 5*dhdg_pos/4;  
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}


//rdh}

//DeadCode RDH 07Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 07Jan99 //Procedure		VerticalLoop
//DeadCode RDH 07Jan99 //Author		Andrew McRae
//DeadCode RDH 07Jan99 //Date			Mon 2 Jun 1997
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Description	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Inputs		
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Returns	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 07Jan99 void AirStruc::VerticalLoop ( )
//DeadCode RDH 07Jan99 {
//DeadCode RDH 07Jan99 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 07Jan99 	MODEL& MOD = *fly.pModel;
//DeadCode RDH 07Jan99 	Float fpitch, fhdg;
//DeadCode RDH 07Jan99 //	ACM.Step = ai.ManStep;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 	switch (ai.ManStep)
//DeadCode RDH 07Jan99 	{
//DeadCode RDH 07Jan99 		case PHASE0:
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 			MOD.Rudder = 0;
//DeadCode RDH 07Jan99 			ACM.Thrust (100);
//DeadCode RDH 07Jan99 			SetManoeuvreTime (2000);
//DeadCode RDH 07Jan99 			if (MOD.Inst.MachNo < 0.55)
//DeadCode RDH 07Jan99 			{
//DeadCode RDH 07Jan99 				ai.manoeuvre = MANOEUVRE_IMMELMANNTURN;
//DeadCode RDH 07Jan99 			}else
//DeadCode RDH 07Jan99 				ai.ManStep = PHASE1;
//DeadCode RDH 07Jan99 			break;
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 		case PHASE1:
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 			ACM.Pitch (ANGLES_355Deg);
//DeadCode RDH 07Jan99 			if (!ManoeuvreTimeLeft ())
//DeadCode RDH 07Jan99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 07Jan99 			if (MOD.Inst.MachNo > 0.6)
//DeadCode RDH 07Jan99 			{
//DeadCode RDH 07Jan99 					COORDS3D	target;
//DeadCode RDH 07Jan99 					target = unfriendly->World;
//DeadCode RDH 07Jan99 					ai.desiredroll = (roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg ));
//DeadCode RDH 07Jan99 					if  (		(ai.desiredroll >> ANGLES_45Deg)
//DeadCode RDH 07Jan99 							&&	(ai.desiredroll << ANGLES_180Deg)
//DeadCode RDH 07Jan99 						)
//DeadCode RDH 07Jan99 						ai.desiredroll = ANGLES_45Deg;
//DeadCode RDH 07Jan99 					if  (		(ai.desiredroll >> ANGLES_180Deg)
//DeadCode RDH 07Jan99 							&&	(ai.desiredroll << ANGLES_315Deg)
//DeadCode RDH 07Jan99 						)
//DeadCode RDH 07Jan99 						ai.desiredroll = ANGLES_315Deg;
//DeadCode RDH 07Jan99 					SetManoeuvreTime (1000);
//DeadCode RDH 07Jan99 					ai.ManStep = PHASE2;
//DeadCode RDH 07Jan99 			}
//DeadCode RDH 07Jan99 			break;
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 		case PHASE2:
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 			SWord 	deltaroll;
//DeadCode RDH 07Jan99 			UWord	deltaroll_pos;
//DeadCode RDH 07Jan99 		 	SWord	deltaroll_sign;
//DeadCode RDH 07Jan99 			ACM.Roll (ai.desiredroll);
//DeadCode RDH 07Jan99  			deltaroll = (SWord) (ai.desiredroll - roll);
//DeadCode RDH 07Jan99  			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 07Jan99  			if (deltaroll_pos <ANGLES_5Deg)
//DeadCode RDH 07Jan99 			{
//DeadCode RDH 07Jan99 				ai.ManStep = PHASE3;
//DeadCode RDH 07Jan99 				SetManoeuvreTime (1000);
//DeadCode RDH 07Jan99 			}
//DeadCode RDH 07Jan99 			if (!ManoeuvreTimeLeft ())
//DeadCode RDH 07Jan99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 07Jan99 			break;
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 		case PHASE3:
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 			ACM.LiftLimit();
//DeadCode RDH 07Jan99  			if  (	(roll >> ANGLES_90Deg)
//DeadCode RDH 07Jan99 				&&	(roll << ANGLES_270Deg)
//DeadCode RDH 07Jan99 				)
//DeadCode RDH 07Jan99 			{
//DeadCode RDH 07Jan99 				ai.ManStep = PHASE4;
//DeadCode RDH 07Jan99 				SetManoeuvreTime (1000);
//DeadCode RDH 07Jan99 			}
//DeadCode RDH 07Jan99 			if (!ManoeuvreTimeLeft ())
//DeadCode RDH 07Jan99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 07Jan99 			break;
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 		case PHASE4:
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 			ACM.LiftLimit();
//DeadCode RDH 07Jan99 			if   (	(DesiredPitchChk (ANGLES_0Deg, ANGLES_10Deg))
//DeadCode RDH 07Jan99 				 ||	(!ManoeuvreTimeLeft ())
//DeadCode RDH 07Jan99 				 )
//DeadCode RDH 07Jan99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 	}
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 }
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 07Jan99 //Procedure		ImmelmannTurn
//DeadCode RDH 07Jan99 //Author		R. Hyde 
//DeadCode RDH 07Jan99 //Date			Wed 13 Dec 1995
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Description	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Inputs		
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Returns	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 07Jan99 void AirStruc::ImmelmannTurn ( )
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 {
//DeadCode RDH 07Jan99  	SWord 	deltaroll;
//DeadCode RDH 07Jan99  	UWord	deltaroll_pos;
//DeadCode RDH 07Jan99  	SWord	deltaroll_sign;
//DeadCode RDH 07Jan99  	MODEL& MOD = *fly.pModel;
//DeadCode RDH 07Jan99 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 07Jan99 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 07Jan99 	Float fpitch, fhdg;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99  	switch (ai.ManStep)
//DeadCode RDH 07Jan99  	{
//DeadCode RDH 07Jan99  		case PHASE0:
//DeadCode RDH 07Jan99  		{
//DeadCode RDH 07Jan99 			MOD.Rudder = 0;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99  			ACM.Thrust (100);
//DeadCode RDH 07Jan99 			COORDS3D	target;
//DeadCode RDH 07Jan99 			target = unfriendly->World;
//DeadCode RDH 07Jan99 //			ai.desiredroll = (Angles)(Rads2Rowan(MOD.fRoll) + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg ));
//DeadCode RDH 07Jan99 //			if  (		(ai.desiredroll >> ANGLES_60Deg)
//DeadCode RDH 07Jan99 //					&&	(ai.desiredroll << ANGLES_180Deg)
//DeadCode RDH 07Jan99 //				)
//DeadCode RDH 07Jan99 //				ai.desiredroll = ANGLES_60Deg;
//DeadCode RDH 07Jan99 //			if  (		(ai.desiredroll >> ANGLES_180Deg)
//DeadCode RDH 07Jan99 //					&&	(ai.desiredroll << ANGLES_300Deg)
//DeadCode RDH 07Jan99 //				)
//DeadCode RDH 07Jan99 //				ai.desiredroll = ANGLES_300Deg;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 			if (roll << ANGLES_180Deg)
//DeadCode RDH 07Jan99 			{
//DeadCode RDH 07Jan99 				if (roll << ANGLES_45Deg)
//DeadCode RDH 07Jan99 					ai.desiredroll = ANGLES_45Deg;
//DeadCode RDH 07Jan99 				else
//DeadCode RDH 07Jan99 					ai.desiredroll = roll;
//DeadCode RDH 07Jan99 			}else
//DeadCode RDH 07Jan99 			{
//DeadCode RDH 07Jan99 				if (roll >> ANGLES_315Deg)
//DeadCode RDH 07Jan99 					ai.desiredroll = ANGLES_315Deg;
//DeadCode RDH 07Jan99 				else
//DeadCode RDH 07Jan99 					ai.desiredroll = roll;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 			}
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 			ai.ManStep = PHASE1;
//DeadCode RDH 07Jan99  			break;	
//DeadCode RDH 07Jan99  		}
//DeadCode RDH 07Jan99  		case PHASE1:
//DeadCode RDH 07Jan99  		{	
//DeadCode RDH 07Jan99 			ACM.Roll (ai.desiredroll);
//DeadCode RDH 07Jan99 // 			MOD.Elevator = HEAVYPULLELEVATOR;
//DeadCode RDH 07Jan99 //			UByte	FF = FlyingFactor();
//DeadCode RDH 07Jan99 //			FP aoa0 = AngleSign (MOD.MainPlaneList->aoa[0]);
//DeadCode RDH 07Jan99 //			FP aoa1 = AngleSign (MOD.MainPlaneList->aoa[1]);
//DeadCode RDH 07Jan99 //			FP maxaoa = MOD.MainPlaneList->AoaMax - 	((256 - FF) * 0.174)/256;	//* 10 degs
//DeadCode RDH 07Jan99 //			if (	(aoa0 > maxaoa)
//DeadCode RDH 07Jan99 //				||	(aoa1 > maxaoa)
//DeadCode RDH 07Jan99 //				)
//DeadCode RDH 07Jan99  //				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 07Jan99 			ACM.SetRelAoA(ANGLES_1Deg);
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99  			deltaroll = (SWord) (ai.desiredroll - roll);
//DeadCode RDH 07Jan99  			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 07Jan99  			if (deltaroll_pos <ANGLES_5Deg)
//DeadCode RDH 07Jan99 			{
//DeadCode RDH 07Jan99 				ai.ManStep = PHASE2;
//DeadCode RDH 07Jan99 				SetManoeuvreTime (1000);
//DeadCode RDH 07Jan99 				ai.desiredroll = roll;
//DeadCode RDH 07Jan99 			}
//DeadCode RDH 07Jan99 			break;
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 		case PHASE2:
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 			ACM.SetAileron(0);
//DeadCode RDH 07Jan99 			ACM.LiftLimit();
//DeadCode RDH 07Jan99  			if  (		(	(roll >> ANGLES_90Deg)
//DeadCode RDH 07Jan99 						&&	(roll << ANGLES_270Deg)
//DeadCode RDH 07Jan99 						)
//DeadCode RDH 07Jan99 					||
//DeadCode RDH 07Jan99 						(MOD.Inst.MachNo < 0.32)
//DeadCode RDH 07Jan99 					||	(		(roll << ANGLES_180Deg)
//DeadCode RDH 07Jan99 							&&	(roll << ai.desiredroll)
//DeadCode RDH 07Jan99 						)
//DeadCode RDH 07Jan99 					||	(
//DeadCode RDH 07Jan99 								(roll >> ANGLES_180Deg)
//DeadCode RDH 07Jan99 							&&	(roll >> ai.desiredroll)
//DeadCode RDH 07Jan99 						)
//DeadCode RDH 07Jan99 			
//DeadCode RDH 07Jan99 				)
//DeadCode RDH 07Jan99 			{
//DeadCode RDH 07Jan99 				ai.ManStep = PHASE3;
//DeadCode RDH 07Jan99 			}
//DeadCode RDH 07Jan99 			ai.desiredroll = roll;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 			if (!ManoeuvreTimeLeft ())
//DeadCode RDH 07Jan99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 			break;
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 		case PHASE3:
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 //			SWord	reqdeltahdg,reqdeltahdg_sign;
//DeadCode RDH 07Jan99 //			UWord	reqdeltahdg_pos;
//DeadCode RDH 07Jan99 //			SWord	reqdeltapitch,reqdeltapitch_sign;
//DeadCode RDH 07Jan99 //			UWord	reqdeltapitch_pos;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 			ACM.Roll (ai.desiredroll);
//DeadCode RDH 07Jan99 			ACM.LiftLimit();
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 //			reqdeltahdg = 	hdg - HdgIntercept;
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //			reqdeltapitch = 	fly.cpitch - PitchIntercept;
//DeadCode RDH 07Jan99 //			Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //			TurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, ANGLES_0Deg);
//DeadCode RDH 07Jan99 			if  (		!(TargetOnSubjectTail(ANGLES_50Deg))
//DeadCode RDH 07Jan99 					||	!(SubjectOnTargetTail(ANGLES_50Deg))
//DeadCode RDH 07Jan99 				)
//DeadCode RDH 07Jan99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 07Jan99 			if (!ManoeuvreTimeLeft ())
//DeadCode RDH 07Jan99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 07Jan99 		}	
//DeadCode RDH 07Jan99  	}
//DeadCode RDH 07Jan99 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HeadOnOffset
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
void AirStruc::HeadOnOffset ( )

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	SLong temp_range;
	temp_range = Range; 	
	COORDS3D	target;
	SWord c,s;
	SWord newhdg;
	UByte	FF; 
	SWord	reqdeltahdg;


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
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
//DEADCODE RDH 06/04/99 //			ANGLES bca = BestClimbAngle();
//DEADCODE RDH 06/04/99 //			if (PitchIntercept >> bca )
//DEADCODE RDH 06/04/99 //				ACM.Pitch (bca);
//DEADCODE RDH 06/04/99 //			else
//DEADCODE RDH 06/04/99 //			if (PitchIntercept >> pitch)
//DEADCODE RDH 06/04/99 			if  (	(		(PitchIntercept >> ANGLES_180Deg)
//DEADCODE RDH 06/04/99 						&&	(MOD.Elevator <= 0)
//DEADCODE RDH 06/04/99 					)
//DEADCODE RDH 06/04/99 					||
//DEADCODE RDH 06/04/99 					(
//DEADCODE RDH 06/04/99 							(PitchIntercept << ANGLES_180Deg)
//DEADCODE RDH 06/04/99 						&&	(MOD.Elevator > 0)
//DEADCODE RDH 06/04/99 					)
//DEADCODE RDH 06/04/99 					||		(		(roll >> ANGLES_40Deg)
//DEADCODE RDH 06/04/99 								&&	(roll << ANGLES_320Deg)
//DEADCODE RDH 06/04/99 							)
//DEADCODE RDH 06/04/99 				)
//DEADCODE RDH 06/04/99 			{
//DEADCODE RDH 06/04/99 				ACM.SetElevator(0);
//DEADCODE RDH 06/04/99 			}else
//DEADCODE RDH 06/04/99 				ACM.Pitch (PitchIntercept);
//DEADCODE RDH 06/04/99 //			else
//DEADCODE RDH 06/04/99 //				ACM.Pitch (pitch + ANGLES_3Deg);

			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca )
				ACM.Pitch (bca);
			else
				ACM.Pitch (PitchIntercept);




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
			if  (		(reqroll >> ANGLES_30Deg)
					&&	(reqroll << ANGLES_180Deg)
				)
				reqroll = ANGLES_30Deg;
			if  (		(reqroll << ANGLES_330Deg)
					&&	(reqroll >> ANGLES_180Deg)
				)	
				reqroll = ANGLES_330Deg;

			ACM.Roll (reqroll);

			if (unfRange < Range)
				Range = unfRange;
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			if	(		(SubjectOnTargetTail(ANGLES_85Deg))
					||	(TargetOnSubjectTail(ANGLES_85Deg))
				)
			{
		  		ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						
			}else if (Range < (BREAKTURNRADIUS))
			{
				FF = Math_Lib.rnd(4);
				if (		(FF  < 2)
						&&	(		(unfriendly->roll >> ANGLES_30Deg)
								&&	(unfriendly->roll << ANGLES_330Deg)
							)
					)
				{//turn in
					reqdeltahdg = 	hdg - unfHdgIntercept;
					if (reqdeltahdg < 0)
					{
						ai.desiredroll = ANGLES_85Deg;
						ai.desiredhdg = ANGLES_90Deg + hdg;
					}else
					{
						ai.desiredhdg = ANGLES_270Deg + hdg;
						ai.desiredroll = ANGLES_275Deg;
					}
					ai.ManStep = PHASE2;
				}else
				{//wait
					ai.ManStep = PHASE3;
				}
			}
			break;
		}
		case PHASE2:
		{
			ACM.Roll (ai.desiredroll);
			ACM.ZeroSpecificPower();
//DeadCode RDH 25Nov98 			ACM.LiftLimit();
			if (ChkAtDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
			{
		  		ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						
			}
			break;
		}
		case PHASE3:
		{
//			if (PitchIntercept >> pitch)
				ACM.Pitch (PitchIntercept);
//			else
//				ACM.Pitch (pitch + ANGLES_3Deg);
			ANGLES desiredhdg = ai.desiredhdg;

			newhdg = unfriendly->hdg + ai.desiredhdg;
			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((BREAKTURNRADIUS * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((BREAKTURNRADIUS * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - desiredhdg;
		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			if  (		(reqroll >> ANGLES_30Deg)
					&&	(reqroll << ANGLES_180Deg)
				)
				reqroll = ANGLES_30Deg;
			if  (		(reqroll << ANGLES_330Deg)
					&&	(reqroll >> ANGLES_180Deg)
				)	
				reqroll = ANGLES_330Deg;

			ACM.Roll ((Angles)reqroll);

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			else if	(		(SubjectOnTargetTail(ANGLES_80Deg))
					||	(TargetOnSubjectTail(ANGLES_80Deg))
				)
			{
				if  (		(unfriendly->roll << ANGLES_30Deg)
						||	(unfriendly->roll >> ANGLES_330Deg)
					)
				{
			  		ai.ManStep = PHASE0;
					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						

				}else 
				{
					if (		(roll >> ANGLES_30Deg)
							&&	(roll << ANGLES_180Deg)
						)
					{
						ai.desiredroll = ANGLES_85Deg;
						ai.desiredhdg = ANGLES_90Deg + hdg;
					}else if (	(roll << ANGLES_330Deg)
								&&	(roll >> ANGLES_180Deg)
							 )
					{
						ai.desiredhdg = ANGLES_270Deg + hdg;
						ai.desiredroll = ANGLES_275Deg;
					}else if ((hdg - HdgIntercept) < 0)
					{
						ai.desiredroll = ANGLES_85Deg;
						ai.desiredhdg = ANGLES_90Deg + hdg;
					}else
					{
						ai.desiredhdg = ANGLES_270Deg + hdg;
						ai.desiredroll = ANGLES_275Deg;
					}
					
//					if  (		(Math_Lib.rnd(3) == 0)
//						||	(Range > BREAKTURNRADIUS/2)
//					)
//					{
//						if  (		(unfriendly->roll << ANGLES_180Deg)
//								||	(roll >> ANGLES_20Deg)
//							)
//						{
//							ai.desiredroll = ANGLES_85Deg;
//							ai.desiredhdg = ANGLES_90Deg + hdg;
//						}else
//						{
//							ai.desiredhdg = ANGLES_270Deg + hdg;
//							ai.desiredroll = ANGLES_275Deg;
//						}
//					}else
//					{
//						if (	(unfriendly->roll >> ANGLES_180Deg)
//							||	(roll << ANGLES_340Deg)	
//							)
//						{
//							ai.desiredroll = ANGLES_85Deg;
//							ai.desiredhdg = ANGLES_90Deg + hdg;
//						}else
//						{
//							ai.desiredhdg = ANGLES_270Deg + hdg;
//							ai.desiredroll = ANGLES_275Deg;
//						}
//					}
			  		ai.ManStep = PHASE4;
				}
			}		
			break;

		}
		case PHASE4:
		{
			ACM.Roll (ai.desiredroll);
			ACM.ZeroSpecificPower();
//DeadCode RDH 25Nov98 			ACM.LiftLimit();
			if (ChkAtDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
			{
		  		ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						
			}

		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StayWithPrey
//Author		R. Hyde 
//Date			Wed 13 Dec 1995
//
//Description	As target looses alt, stay until explosion or hits ground or alt <???
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::StayWithPrey ( )

{
	
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll;
//DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 26Mar98 	UWord	acroll_pos;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if  (		(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					||	(World.Y < FT_700)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			TightTurn (FT_500);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Immelmann
//Author		R. Hyde 
//Date			Wed 13 Dec 1995
//
//Description	not used and so not coded for Flying Corps
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::Immelmann ( )

{
	AirStrucPtr	unfriendly = *ai.unfriendly;

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

//	ACM.Step = ai.ManStep;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (100);
			SetManoeuvreTime (2000);
			if (		(MOD.Inst.MachNo != 0)		//really just for test purposes, first time in mchno is not set
					&&	(MOD.Inst.MachNo < 0.55)
				)
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
			}else
				ai.ManStep = PHASE1;
			break;
		}
		case PHASE1:
		{
			ACM.Pitch (ANGLES_355Deg);
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			if (MOD.Inst.MachNo > 0.6)
			{
				ai.desiredroll = ANGLES_0Deg;
				SetManoeuvreTime (1000);
				ai.ManStep = PHASE2;
			}
			break;
		}
		case PHASE2:
		{
			SWord 	deltaroll;
			UWord	deltaroll_pos;
		 	SWord	deltaroll_sign;
			ACM.Roll (ai.desiredroll);
 			deltaroll = (SWord) (ai.desiredroll - roll);
 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
 			if (deltaroll_pos <ANGLES_5Deg)
			{
				ai.ManStep = PHASE3;
				SetManoeuvreTime (1000);
				ai.desiredhdg = hdg;
			}
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE3:
		{
			ACM.LiftLimit();
			ACM.Roll (ANGLES_0Deg);
 			if  (	(roll >> ANGLES_90Deg)
				&&	(roll << ANGLES_270Deg)
				)
			{
				ai.ManStep = PHASE4;
				SetManoeuvreTime (1000);
			}
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE4:
		{
			SWord 	deltaroll;
			UWord	deltaroll_pos;
		 	SWord	deltaroll_sign;
			Float fpitch,fhdg;
			COORDS3D	target;
			target = ai.unfriendly->World;

			ANGLES reqroll = roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
			ACM.Roll (reqroll);

			int ele = MOD.Elevator + MOD.MODEL_DT * 3000;
			if (ele >0)
				ele = 0;
			ACM.SetElevator(ele);
			
			deltaroll = (SWord) (reqroll - roll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_5Deg)
			{
				ai.ManStep = PHASE5;
				SetManoeuvreTime (1000);
			}
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE5:
		{
			ACM.KeepWingsLevel ();
			ACM.LiftLimit();
			if   (	(DesiredPitchChk (ANGLES_0Deg, ANGLES_10Deg))
				 ||	(!ManoeuvreTimeLeft ())
				 )
				ai.manoeuvre = MANOEUVRE_SELECT;

		}
	}



}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbforHome
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
void AirStruc::ClimbforHome ( )

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 //DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
 	SLong	temp_range;
 
 	temp_range = Range; 	
 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
  			MoveToThrust (100);
 			SetManoeuvreTime (2000);
 			ai.ManStep = PHASE1;

			ACM.Thrust (ThrustfromFF());

 			InterceptandRange (&ai.homebase->World);
 			ai.desiredhdg = HdgIntercept; 
 		}
 		case PHASE1:
 		{
//##			if (Range < MILES01)
//			{//within mile of home
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
			Range = temp_range; 	
//			if (Range > BREAKOFFRANGE)
//			{//xx from action, reconsider
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
			if (Range < DANGERRANGE)
			{//xx from action, reconsider
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

//			ACM.Pitch (BestClimbAngle());
 			MoveToHdg (ai.desiredhdg, BestClimbAngle());
 		}
 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StraightDive
//Author		Andrew McRae
//Date			Tue 3 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::StraightDive ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			SetManoeuvreTime (2000);
			ACM.Thrust (ThrustfromFF());

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll (ANGLES_0Deg);
			ACM.Pitch (ANGLES_330Deg);
			if (MOD.Pos.y < FT_2000)
				ai.manoeuvre = MANOEUVRE_SELECT;
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}


}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StandOnTail
//Author		
//Date			Mon 8 Sep 1997
//
//Description	
//Zoom until low speed, then roll 180 and pull level
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::StandOnTail ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			SetManoeuvreTime (2000);	//800
			ACM.Thrust (100);

			ACM.ClimbRate (0);
			ACM.KeepWingsLevel ();
			ai.ManStep = PHASE1;
			break;
		}

		case PHASE1:
		{
			if (MOD.Inst.IndicatedAirSpeed > 450)
			{

				ACM.Clear ();
				ACM.Thrust (100);
//				ACM.StayVertical ();

				ai.ManStep = PHASE2;
			}
			break;
		}

		case PHASE2:
		{
 			if (!ManoeuvreTimeLeft())
 				ai.manoeuvre = MANOEUVRE_SELECT;

// 			if (ACM.pModel->Vel.y <= 0)
//				ai.manoeuvre = MANOEUVRE_SELECT;

			break;
		}
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShootToFrighten
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
void AirStruc::ShootToFrighten ( )

{
	ACMMODEL& ACM = *fly.pAcmModel;
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Clear ();
			SetManoeuvreTime (1000);
			ACM.maxdeltaforclosework = 0.0;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord	reqdeltahdg,reqdeltahdg_sign;
			UWord	reqdeltahdg_pos;
			COORDS3D	target;
			SLong		time;
			MODEL& MOD = *fly.pModel;
			AirStrucPtr	unfriendly = *ai.unfriendly;
		//DeadCode AMM 01Jul98 	MODEL& UNFMOD = *(unfriendly->fly).pModel;	


			reqdeltahdg = 	Rads2Rowan(MOD.fHdg) - HdgIntercept;
			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

			if (		(Range < METRES400)
					&&	(reqdeltahdg_pos < (SWord)ANGLES_30Deg)
				)		
			{
				//this method just extrapolates position
				//to get turn:
				//get distance travelled and turn in time to work out offset
				time = Range / classtype->muzzlevel;		//MUZZELVEL;
				//calc lead position using this time
				target.X = ai.unfriendly->World.X + (unfriendly->velx * time );
				target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
				target.Z = ai.unfriendly->World.Z + (unfriendly->velz * time );
				InterceptandRange (&target);
			}else
				target = ai.unfriendly->World;

			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
		//DeadCode RDH 16Dec98 	TurnFightSub(HdgIntercept, TRUE, ANGLES_5Deg,target);
			if (		(Range < ENGAGERANGE)
					&&	((unfriendly->vel - vel) > 0)
					&&	(		(unfriendly->roll << ANGLES_10Deg)
							||	(unfriendly->roll >> ANGLES_350Deg)
						)
				)	
			{
						FireABullet(120);
						if	(	(		(unfriendly->ai.morale < MORALE_GOOD)
									||	(unfriendly->ai.combatskill < SKILL_VETERAN)
								)
								&&
								(ai.unfriendly != Persons2::PlayerGhostAC)
							)
						{
							unfriendly->ai.manoeuvre = MANOEUVRE_PANICTURN;
							unfriendly->ai.ManStep = PHASE0;
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
void AirStruc::ShootTooEarly()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Clear ();
			SetManoeuvreTime (1000);
			ACM.maxdeltaforclosework = 0.0;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{

				SWord	reqdeltahdg,reqdeltahdg_sign;
			UWord	reqdeltahdg_pos;
			COORDS3D	target;
			SLong		time;
			MODEL& MOD = *fly.pModel;
			AirStrucPtr	unfriendly = *ai.unfriendly;
		//DeadCode AMM 01Jul98 	MODEL& UNFMOD = *(unfriendly->fly).pModel;	

			target = ai.unfriendly->World;

			reqdeltahdg = 	Rads2Rowan(MOD.fHdg) - HdgIntercept;
			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

			if (		(Range < METRES400)
					&&	(reqdeltahdg_pos < (SWord)ANGLES_30Deg)
				)		
			{
				//this method just extrapolates position
				//to get turn:
				//get distance travelled and turn in time to work out offset
				time = Range / classtype->muzzlevel;		//MUZZELVEL;
				//calc lead position using this time
				target.X = ai.unfriendly->World.X + (unfriendly->velx * time );
				target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
				target.Z = ai.unfriendly->World.Z + (unfriendly->velz * time );
				InterceptandRange (&target);
			}else
				target = ai.unfriendly->World;

			if (		(Range < ENGAGERANGE)
					&&	((unfriendly->vel - vel) < 0)
				)	
						FireABullet(10);

			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
		//DeadCode RDH 16Dec98 	TurnFightSub(HdgIntercept, TRUE, ANGLES_5Deg,target);
		}
	}

}

ANGLES AirStruc::BestClimbAngle()
{
//## needs rewrite
//DEADCODE DAW 31/03/99 	MODEL& MOD = *fly.pModel;
//DEADCODE DAW 31/03/99 	ACMMODEL& ACM = *fly.pAcmModel;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			FP	Mach = MOD.Inst.MachNo;
//DEADCODE DAW 31/03/99 			if (Mach > 0.6)
//DEADCODE DAW 31/03/99 				Mach = 0.6;
//DEADCODE DAW 31/03/99 			if (Mach < 0.3)
//DEADCODE DAW 31/03/99 				Mach = 0.3;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			ANGLES desiredpitch;
//DEADCODE DAW 31/03/99 			SWord deltapitch;
//DEADCODE DAW 31/03/99 			deltapitch = ANGLES_20Deg * ((Mach - 0.3)/0.3);
//DEADCODE DAW 31/03/99 			desiredpitch = (Angles)((SWord)ANGLES_350Deg + deltapitch);
//DEADCODE DAW 31/03/99 			return (desiredpitch);
//DEADCODE DAW 31/03/99 
		return ( classtype->bestclimbpitch);
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
void AirStruc::GainHeight ( )

{
	
	// ##Select Max power
	// and maintain best climb speed
	// fly flat if < bestclimb speed
	

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

//	ACM.Step = ai.ManStep;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SWord reqdeltahdg = 	hdg - HdgIntercept;
			ACM.Thrust (ThrustfromFF());
//			if (reqdeltahdg > 0)
//				ai.desiredroll = ANGLES_330Deg;
//			else
//				ai.desiredroll = ANGLES_30Deg;

			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{

//			Angles gcurve [] =
//			{//0-11g
//				ANGLES_0Deg,ANGLES_0Deg,ANGLES_60Deg,ANGLES_70_5Deg,ANGLES_75_5Deg,ANGLES_78_5Deg,ANGLES_80_4Deg,
//				ANGLES_81_8Deg,ANGLES_82_8Deg,ANGLES_83_6Deg,ANGLES_84_3Deg,ANGLES_84_8Deg,
//			};
//
 //			SWord reqroll;
//
//			int g, g100;
//			FP gfp;
//			gfp = MOD.Inst.NormalAcc;
//			FP modifier = 10;
//
//
//			gfp = gfp + ((modifier * (SWord)(fly.cpitch))/ ((SWord)ANGLES_70Deg));
//
//
//
//			SWord d1,d2;
//			g =	(int)gfp;
//			g100 = 100 * gfp;
//				
//			SWord rroll;
//			if (g <0)
//				g = 0;
//			if (g > 10)
//				g = 10;
//			d1 = gcurve[g];
 //			d2 = gcurve[g + 1];
//		 	rroll = d1+ (d2-d1) * (g100 - g * 100)/100;
//			if (rroll < ANGLES_50Deg)
//				rroll = ANGLES_50Deg;
//			ACM.Roll ((Angles)rroll);
//			ACM.LiftLimit();

//##should attempt to get to side
			ACM.Pitch (BestClimbAngle());
			SWord	reqdeltahdg = hdg - HdgIntercept;
		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			//##skill factor
			if (reqroll > ANGLES_30Deg)
				reqroll = ANGLES_30Deg;
			if (reqroll < ANGLES_330Deg)
				reqroll = ANGLES_330Deg;
			ACM.Roll ((Angles)reqroll);

			if  (		(!ManoeuvreTimeLeft())
					||	(		(Range < ENGAGERANGE)
							&&	SubjectFacingTarget(ANGLES_45Deg)
						)	
				)
				ai.manoeuvre = MANOEUVRE_SELECT;
			
			
			
			break;	
			
			
			
			
			
//			MOD.Rudder = 0;
//			SetManoeuvreTime (2000);
//			ACM.GearUp ();
//			UByte	FF = FlyingFactor();
//			SWord thrust = 85 + (FF * 15)/256;	
//			if (thrust > 95)
//				thrust = 100;
//			ACM.Thrust (thrust);
//			if (ai.combatskill > SKILL_REGULAR)
//			{
//				SWord	reqdeltahdg;
//				reqdeltahdg = 	hdg - HdgIntercept;
//				if (reqdeltahdg > 0)
//					ai.desiredhdg = HdgIntercept + ANGLES_20Deg;
//				else
//					ai.desiredhdg = HdgIntercept - ANGLES_20Deg;
//
//			}
//			else
//				ai.desiredhdg = HdgIntercept;
//
////			ACM.ClimbRate (-1500);
//			ai.ManStep = PHASE1;
		}
//		case PHASE1:
//		{
 //			MoveToHdg (ai.desiredhdg);
//			ACM.Pitch (BestClimbAngle());
////			if (MOD.Inst.MachNo < 0.4)
//			if (vel <= SustainedTurnSpeed())
//				ACM.Pitch (ANGLES_355Deg);
//			else
//				ACM.Pitch (ANGLES_5Deg);


//			if (!ManoeuvreTimeLeft())
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			break;
//		}
	}

//DeadCode RDH 26Mar98 	AirStrucPtr		unfriendly;	
//DeadCode RDH 26Mar98 	SWord 	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign,desiredaoa;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 			if (	(unfriendly->ai.attacker == this)
//DeadCode RDH 26Mar98 				||	(World.Y > classtype->fightceiling)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre=MANOEUVRE_SUSTAINEDTURN;
//DeadCode RDH 26Mar98 				TurningFight ();
//DeadCode RDH 26Mar98 				break;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			if ((SWord) fly.turnrate > 0)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 		 		ai.desiredroll = ANGLES_20Deg;
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 		 		ai.desiredroll = ANGLES_340Deg;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Jul96 			desiredaoa = ANGLES_7Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 13Jul96 			if (desiredaoa > (SWord)(STALL_ANGLE_MINUSONE - (fly.highest_aoa - fly.aoa)))
//DeadCode RDH 26Mar98 //DeadCode RDH 13Jul96 				desiredaoa = STALL_ANGLE_MINUSONE - (fly.highest_aoa - fly.aoa);
//DeadCode RDH 26Mar98 //DeadCode RDH 13Jul96 			MoveToAoA ((ANGLES) desiredaoa);
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_10Deg,6);
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1);							//RDH 14May96
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}

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
void	AirStruc::LagRoll()
{
//maintain throttle
//roll towards unfriendly for 10-20deg hdg (f(AOT))
//go upside down
//climb to loose speed to corner speed
//exit manoeuvre when unfriendly goes behind or time out

//treat the same as lagroll
	HighYoYo();

//DEADCODE DAW 31/03/99 	ACMMODEL& ACM = *fly.pAcmModel;
//DEADCODE DAW 31/03/99 	MODEL& MOD = *fly.pModel;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 	switch (ai.ManStep)
//DEADCODE DAW 31/03/99 	{
//DEADCODE DAW 31/03/99 		case PHASE0:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			ACM.Thrust (100);
//DEADCODE DAW 31/03/99 			SetManoeuvreTime (1500);
//DEADCODE DAW 31/03/99  			ai.desiredroll = ANGLES_0Deg; 
//DEADCODE DAW 31/03/99 			ai.ManStep = PHASE1;
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 		case PHASE1:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			ACM.Roll (ai.desiredroll);
//DEADCODE DAW 31/03/99 			ACM.SetRelAoA(ANGLES_4Deg);
//DEADCODE DAW 31/03/99 //			ACM.MinHeight (FT_2000);
//DEADCODE DAW 31/03/99 			if (TooLow())
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				ai.ManStep = PHASE0;
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_LOWALT;
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			if  (!ManoeuvreTimeLeft())
//DEADCODE DAW 31/03/99   				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE DAW 31/03/99 			if (TargetOnSubjectTail(ANGLES_90Deg))
//DEADCODE DAW 31/03/99 				ai.ManStep = PHASE2;
//DEADCODE DAW 31/03/99 			break;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 		case PHASE2:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			COORDS3D	target;
//DEADCODE DAW 31/03/99 			Float fpitch,fhdg;
//DEADCODE DAW 31/03/99 			AirStrucPtr	unfriendly = *ai.unfriendly;
//DEADCODE DAW 31/03/99 			target = ai.unfriendly->World;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			SWord	reqdeltahdg,reqdeltahdg_sign;
//DEADCODE DAW 31/03/99 			UWord	reqdeltahdg_pos;
//DEADCODE DAW 31/03/99 			reqdeltahdg = 	hdg - HdgIntercept;
//DEADCODE DAW 31/03/99  			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			ANGLES reqroll = roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
//DEADCODE DAW 31/03/99 			ACM.Roll (reqroll);
//DEADCODE DAW 31/03/99 			ACM.TurnRate(fpitch);
//DEADCODE DAW 31/03/99 			if (TooLow())
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				ai.ManStep = PHASE0;
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_LOWALT;
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			if  (		(reqdeltahdg_pos < ANGLES_50Deg)
//DEADCODE DAW 31/03/99 					||	(World.Y < unfriendly->World.Y)
//DEADCODE DAW 31/03/99 				)
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
//DEADCODE DAW 31/03/99 				ai.ManStep = PHASE0;
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 //			ACM.MinHeight (FT_2000);
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 	}
//DEADCODE DAW 31/03/99 

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
void	AirStruc::ExtensionManoeuvre()
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
//## if turning good pilots will initially unload and
//retain roll to disguise manoeuvre 
//
//initially aircraft could be closing

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			if ( (World.Y - ai.unfriendly->World.Y) > FT_1000)
			{//above him
				ai.desiredpitch = ANGLES_0Deg;
			}else if ( (ai.unfriendly->World.Y - World.Y) > FT_1000)
			{//below him
				if (classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 				if (classtype->visible == MIG15)
					ai.desiredpitch = ANGLES_0Deg;
				else
					ai.desiredpitch = ANGLES_350Deg;
			}else
			{
				if (classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 				if (classtype->visible == MIG15)
					ai.desiredpitch = ANGLES_10Deg;
				else
					ai.desiredpitch = ANGLES_350Deg;
			}

			SetManoeuvreTime (2000);
			ai.ManStep = PHASE1;
			break;
		}
		case PHASE1:
		{
//			ACM.Pitch (ai.desiredpitch);
			ACM.MinHeight (FT_1000);
			MoveToHdg (HdgIntercept + ANGLES_180Deg,ai.desiredpitch);
 			if  (		(Range > ENGAGERANGE)
					||	(!ManoeuvreTimeLeft())
				)
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}


}
void	AirStruc::DivingSpin()
{
		ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
 	SWord 	deltaroll;
 	UWord	deltaroll_pos;
 	SWord	deltaroll_sign;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	Float fpitch, fhdg;
	UByte	FF = FlyingFactor();

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;

			
			ACM.Thrust (ThrustfromFF());
			COORDS3D	target;
			target = unfriendly->World;
			ANGLES reqroll = (roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch,fhdg ));
			if (	(reqroll >> ANGLES_120Deg)
				&&	(reqroll << ANGLES_240Deg)
				)
				ai.desiredroll = reqroll;
			else
				ai.desiredroll = ANGLES_180Deg;
			SetManoeuvreTime (1000);

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{ //get upside down or therabouts

			ACM.FastRoll (ai.desiredroll);
			deltaroll = (SWord) (ai.desiredroll - roll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if  (		( roll >> ANGLES_90Deg)
					&&	(roll << ANGLES_270Deg)
					&&	(deltaroll_pos <ANGLES_30Deg)
				)
				ACM.LiftLimit();
			else
				ACM.Pitch (ANGLES_0Deg);

			if (deltaroll_pos <ANGLES_20Deg)
			{
				if (deltaroll >= 0 )
					ai.desiredroll = (Angles)1;
				else
					ai.desiredroll = (Angles)-1;

				ai.ManStep = PHASE2;
				SetManoeuvreTime (1000);
			}
			break;
		}
 		case PHASE2:
		{// pull and roll until pointing down
			ACM.LiftLimit();

			if ((SWord)ai.desiredroll >= 0)
				ACM.RollRate (400 * FF/256);		//deg/cs gets converted to rad/cs

			else
				ACM.RollRate (-400 * FF/256);

			if  ( 		(!ManoeuvreTimeLeft())
					||  (DesiredPitchChk (ANGLES_270Deg,ANGLES_45Deg))
				)
	 			{
					SetManoeuvreTime (1000);
					ai.ManStep = PHASE3;
 	 			}
	 			break;
		}
 		case PHASE3:
		{//pull and roll until clear or time up
			ACM.LiftLimit();

			if ((SWord)ai.desiredroll >= 0)
				ACM.RollRate (400 * FF/256);		//rad/cs
			else
				ACM.RollRate (-400 * FF/256);
			if  ( 				(!ManoeuvreTimeLeft())
							||	(Range > ENGAGERANGE)							
					
				)
				ai.manoeuvre = MANOEUVRE_SELECT;

 			break;
		}
	}

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
void	AirStruc::ReverseTurn()
{
//	DesiredRoll = opposite of existing
//	Move to desired and hold for 3 secs
//	if (good)
//		out of plane
//	Close brakes if open at end of manoeuvre(used in selfasbait())
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());

			SetManoeuvreTime (600);
			ai.desiredroll = -roll;

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord	droll_sign, droll;
			UWord	droll_pos;

			ACM.Roll (ai.desiredroll);
			ACM.Pitch (PitchIntercept);
//			ACM.MinHeight (FT_2000);
			droll = ai.desiredroll - roll;
			Math_Lib.Pos ((SWord)droll, droll_pos, droll_sign);
//DEADCODE RDH 27/05/99 			if (TooLow())
//DEADCODE RDH 27/05/99 			{
//DEADCODE RDH 27/05/99 				ai.ManStep = PHASE0;
//DEADCODE RDH 27/05/99 				ai.manoeuvre = MANOEUVRE_LOWALT;
//DEADCODE RDH 27/05/99 			}

			if  (		
						(!ManoeuvreTimeLeft())
					||	(droll_pos < ANGLES_5Deg)
				)
				ai.manoeuvre = MANOEUVRE_SELECT;

		}
	}


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
void	AirStruc::SelfAsBait()
{
//
//this could be where bandit is on your tail, wait for him to get close 
//before turning
//keep buddy in combat spread so that you can sandwich him

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	SWord	reqdeltahdg;
	reqdeltahdg = 	hdg - HdgIntercept;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (50);
			SetManoeuvreTime (1500);
			if (roll << ANGLES_90Deg)
				ai.desiredroll = ANGLES_30Deg;
			else
				ai.desiredroll = ANGLES_330Deg;

			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
			ACM.Roll (ai.desiredroll);
			if (ChkAtDesiredRoll(ai.desiredroll, ANGLES_5Deg))
				ACM.Pitch (ANGLES_10Deg);
			ACM.MinHeight (FT_2000);

			if  (		(Range < WEAPONSRANGE)
					||	(!ManoeuvreTimeLeft())
				)
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = PHASE0;
			}


		}
	}

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
void	AirStruc::Jink()
{
//
//fast 90 deg roll
//hard push or pull on stick
//hold for 2-3 secs
//
//flyingability determines rollrate and stick push pull
//combatablity determines length of manoeuvre
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
 			SetManoeuvreTime (500);
 			ai.desiredhdg = (Angles)(1 + Math_Lib.rnd(2));
 			ai.ManStep = PHASE1;
 			if (MOD.Aileron >= 0)
			{
				ai.desiredroll = ANGLES_90Deg;
				ACM.SetAileron(32767);
			}
			else
			{
				ai.desiredroll = ANGLES_270Deg;
 				ACM.SetAileron(-32767);
			}
 		}
 		case PHASE1:
 		{
			SWord 	deltaroll;
			UWord	deltaroll_pos;
		 	SWord	deltaroll_sign;

			deltaroll = (SWord) (ai.desiredroll - roll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_10Deg)
				ACM.LiftLimit();
//DeadCode CSB 21/03/99				ACM.Roll(ai.desiredroll);
			ACM.FastRoll(ai.desiredroll);	//CSB 21/03/99	
 			if (!ManoeuvreTimeLeft())
 			{
				ai.desiredhdg--;
				if (((SWord)ai.desiredhdg) <0)
 					ai.manoeuvre = MANOEUVRE_SELECT;
				else
				{
					if (Math_Lib.rnd(2) == 0)
						ai.desiredroll = (Angles)(ANGLES_50Deg + Math_Lib.rnd((SWord)(ANGLES_45Deg)));
					else	
						ai.desiredroll = (Angles)(ANGLES_260Deg+ Math_Lib.rnd((SWord)(ANGLES_45Deg)));
		 			SetManoeuvreTime (200 + Math_Lib.rnd(300));
				}
 			}
 			break;
 		}
 	}


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
void	AirStruc::BreakTurn()
{
//	roll = cos -1 (1/maxg)
//ability to reach roll = f(flyingskill)
//ability to hold corner vel = f(flyingskill)
//	option to nose down to keep speed up and nose up to reduce speed
//hold for 4-5 secs
//
//low morale gives a very lazy turn
//
	SWord	reqdeltahdg;
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	reqdeltahdg = 	hdg - HdgIntercept;


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());

			SetManoeuvreTime (200);
			RndVal	rndnum = Math_Lib.rnd();
			if (FlyingFactor() > 120)
			{
				if (reqdeltahdg < 0)
					ai.desiredroll = ANGLES_85Deg;
				else
					ai.desiredroll = ANGLES_275Deg;
			}else
			{
				if (rndnum > RND50PC)
					ai.desiredroll = ANGLES_60Deg;
				else
					ai.desiredroll = ANGLES_300Deg;
			}
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{

			ACM.Roll (ai.desiredroll);

		 	SWord 	deltaroll;
		 	UWord	deltaroll_pos;
		 	SWord	deltaroll_sign;
 			deltaroll = (SWord) (ai.desiredroll - roll);
 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
 			if (deltaroll_pos <ANGLES_5Deg)
				ACM.LiftLimit();
//			ACM.MinHeight (FT_2000);
//DEADCODE RDH 27/05/99 			if (TooLow())
//DEADCODE RDH 27/05/99 			{
//DEADCODE RDH 27/05/99 				ai.ManStep = PHASE0;
//DEADCODE RDH 27/05/99 				ai.manoeuvre = MANOEUVRE_LOWALT;
//DEADCODE RDH 27/05/99 			}

			if  (		(!ManoeuvreTimeLeft())
				)
				if (	(classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 				if  (		(classtype->visible == MIG15)
						&&	(fly.cpitch >> ANGLES_180Deg)
					)
				{
					ai.ManStep = PHASE2;
					SetManoeuvreTime (600);

				}else
					ai.manoeuvre = MANOEUVRE_SELECT;
			break;

		}
		case PHASE2:
		{
			COORDS3D	target = ai.unfriendly->World;
//DeadCode RDH 16Dec98 			ai.ManStep = PHASE1;
//DeadCode RDH 16Dec98 			TurnWithPitchChange(HdgIntercept, TRUE,target);
//DeadCode RDH 16Dec98 			if (ai.ManStep == PHASE1)
//DeadCode RDH 16Dec98 				ai.ManStep = PHASE2;
			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
			if  (		(!ManoeuvreTimeLeft())
				)
				ai.manoeuvre = MANOEUVRE_SELECT;

		}

	}

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
void	AirStruc::LazyTurn()
{
//
//	Choose a roll 10-40deg
//		= f(morale)
//	continue on turn for 20s
//	if (ai.morale > MORALE_GOOD)
//		if (Range < WEAPONS)
//			end manoeuvre
//
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (80);

			SetManoeuvreTime (2000);
   			RndVal	rndnum = Math_Lib.rnd();
			if (rndnum > RND50PC)
				ai.desiredroll = ANGLES_60Deg;
			else
				ai.desiredroll = ANGLES_300Deg;

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll (ai.desiredroll);
			SWord pitch = PitchIntercept;
			if (pitch > ANGLES_10Deg)
				pitch = ANGLES_10Deg;
			if (pitch < ANGLES_2Deg)
				pitch = ANGLES_2Deg;
			ACM.Pitch (pitch);
			ACM.MinHeight (FT_2000);
			if  (		(!ManoeuvreTimeLeft())
					||	(		(Range < WEAPONSRANGE)
							&&	(ai.morale > MORALE_GOOD)
						)
				)
				ai.manoeuvre = MANOEUVRE_SELECT;

		}
	}

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
void	AirStruc::Break180()
{
//roll 180
//pull hard until pitch 45 deg down
//slowly unroll for x secs
		ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
 	SWord 	deltaroll;
 	UWord	deltaroll_pos;
 	SWord	deltaroll_sign;
	AirStrucPtr	unfriendly = *ai.unfriendly;


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			ai.desiredroll = ANGLES_180Deg;
			SetManoeuvreTime (1000);

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{

			ACM.Roll (ai.desiredroll);
			deltaroll = (SWord) (ai.desiredroll - roll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_10Deg)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime (1500);
			}
			break;
		}
 		case PHASE2:
		{
			MOD.Aileron = 0;
			ACM.LiftLimit();
			if  ( 		(!ManoeuvreTimeLeft())
					||  (		(DesiredPitchChk (ANGLES_270Deg,ANGLES_10Deg))
						)
				)
	 			{
 					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
					ai.ManStep = PHASE0;
	 			}
	 			break;
		}
	}

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
void	AirStruc::BreakLow()
{
//decide which way to roll to go down
//roll 90
//pull hard until pitch 45 deg down
 	SWord 	deltaroll;
 	UWord	deltaroll_pos;
 	SWord	deltaroll_sign;
 	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;


 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
 			MoveToThrust (100);
			if ((hdg - HdgIntercept) > 0)
					ai.desiredroll = ANGLES_225Deg;
				else
					ai.desiredroll = ANGLES_135Deg;
			ai.ManStep = PHASE1;
 			break;	
 		}
 		case PHASE1:
 		{	
			ACM.Roll (ai.desiredroll);
 			ACM.LiftLimit();
			UByte	FF = FlyingFactor();
			FP aoa0 = AngleSign (MOD.MainPlaneList->aoa[0][0]) + AngleSign (MOD.MainPlaneList->aoa[0][1]);
			FP aoa1 = AngleSign (MOD.MainPlaneList->aoa[1][0]) + AngleSign (MOD.MainPlaneList->aoa[1][1]);
			aoa0 *= 0.5;
			aoa1 *= 0.5;
			FP maxaoa = MOD.MainPlaneList->AoaMax - 	((256 - FF) * 0.174)/256;	//* 10 degs
			if (	(aoa0 > maxaoa)
				||	(aoa1 > maxaoa)
				)
 				ai.manoeuvre = MANOEUVRE_SELECT;
 			deltaroll = (SWord) (ai.desiredroll - roll);
 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
 			if (deltaroll_pos <ANGLES_5Deg)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime (1000);
			}
			break;
		}
		case PHASE2:
		{
			ACM.LiftLimit();
 			if  (	(	(roll >> ANGLES_90Deg)
					&&	(roll << ANGLES_270Deg)
					)
					||
					(MOD.Inst.MachNo < 0.35)
				)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;

			break;
		}
 	}

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
void	AirStruc::BreakHigh()
{
//decide which way to roll to go up
//roll 90
//pull hard until pitch 45 deg up
 	SWord 	deltaroll;
 	UWord	deltaroll_pos;
 	SWord	deltaroll_sign;
 	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;


 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
 			MoveToThrust (100);
			if ((hdg - HdgIntercept) > 0)
					ai.desiredroll = ANGLES_315Deg;
				else
					ai.desiredroll = ANGLES_45Deg;
			ai.ManStep = PHASE1;
 			break;	
 		}
 		case PHASE1:
 		{	
			ACM.Roll (ai.desiredroll);
 			ACM.LiftLimit();
			UByte	FF = FlyingFactor();
			FP aoa0 = AngleSign (MOD.MainPlaneList->aoa[0][0]) + AngleSign (MOD.MainPlaneList->aoa[0][1]);
			FP aoa1 = AngleSign (MOD.MainPlaneList->aoa[1][0]) + AngleSign (MOD.MainPlaneList->aoa[1][1]);
			aoa0 *= 0.5;
			aoa1 *= 0.5;
			FP maxaoa = MOD.MainPlaneList->AoaMax - 	((256 - FF) * 0.174)/256;	//* 10 degs
			if (	(aoa0 > maxaoa)
				||	(aoa1 > maxaoa)
				)
 				ai.manoeuvre = MANOEUVRE_SELECT;
 			deltaroll = (SWord) (ai.desiredroll - roll);
 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
 			if (deltaroll_pos <ANGLES_5Deg)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime (1000);
			}
			break;
		}
		case PHASE2:
		{
			ACM.LiftLimit();
 			if  (	(	(roll >> ANGLES_90Deg)
					&&	(roll << ANGLES_270Deg)
					)
					||
					(MOD.Inst.MachNo < 0.35)
				)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;

			break;
		}
 	}

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
void	AirStruc::Break90()
{
	if (classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 	if (classtype->visible == MIG15)
		BreakHigh();
	else if (	(ai.morale > MORALE_MEDIUM)
			&&	(ClosureLessThan(MPH50))
			)
		{
				ai.manoeuvre = MANOEUVRE_BREAKHIGH;
				BreakHigh();
		}else
		{
				ai.manoeuvre = MANOEUVRE_BREAKLOW;
				BreakLow();
		}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HiGBarrelRoll
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.30	
//				Defensive manoeuvre, used when attacker has high overtake and
//				is close range
//				Method is to pull max g and roll rapidly
//				Supposed to inscribe circle around attacker's flight path
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::HiGBarrelRoll()
{
//max g, roll in one direction
//nose low or high
//unbalanced flight, power reduction, increased drag for better pilots
//
//
//treat the same as lagroll
	HighYoYo();


//DEADCODE DAW 31/03/99 	ACMMODEL& ACM = *fly.pAcmModel;
//DEADCODE DAW 31/03/99 	MODEL& MOD = *fly.pModel;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 	static FP dRoll = 0;
//DEADCODE DAW 31/03/99 	UByte	FF = FlyingFactor();
//DEADCODE DAW 31/03/99 	switch (ai.ManStep)
//DEADCODE DAW 31/03/99 	{
//DEADCODE DAW 31/03/99 		case PHASE0:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			MOD.Rudder = 0;
//DEADCODE DAW 31/03/99 	
//DEADCODE DAW 31/03/99 			SWord thrust = 100 - (FF * 50)/256;	
//DEADCODE DAW 31/03/99 			if (thrust > 95)
//DEADCODE DAW 31/03/99 				thrust = 100;
//DEADCODE DAW 31/03/99 			ACM.Thrust (thrust);
//DEADCODE DAW 31/03/99 			if  ( roll << ANGLES_180Deg)
//DEADCODE DAW 31/03/99 				ai.desiredroll = (Angles)1;
//DEADCODE DAW 31/03/99 			else
//DEADCODE DAW 31/03/99 				ai.desiredroll = (Angles)-1;
//DEADCODE DAW 31/03/99 			SetManoeuvreTime (1000);	// 400
//DEADCODE DAW 31/03/99 			ai.ManStep = PHASE1;
//DEADCODE DAW 31/03/99 			break;
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 		case PHASE1:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			ACM.LiftLimit();
//DEADCODE DAW 31/03/99 			if ((SWord)ai.desiredroll >= 0)
//DEADCODE DAW 31/03/99 				ACM.RollRate (400 * FF/256);		//deg/cs gets converted to rad/cs
//DEADCODE DAW 31/03/99 			else
//DEADCODE DAW 31/03/99 				ACM.RollRate (-400 * FF/256);
//DEADCODE DAW 31/03/99 			if (!ManoeuvreTimeLeft())
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE DAW 31/03/99 			break;
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 	}

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
void	AirStruc::UnBalancedFlight()
{
//skid and slip while making turns
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
 			SetManoeuvreTime (200);
			if  (roll << ANGLES_20Deg)
				ai.desiredhdg = hdg + ANGLES_60Deg;
			else if  (roll >> ANGLES_340Deg)
				ai.desiredhdg = hdg - ANGLES_60Deg;
			else if ( roll == ANGLES_0Deg)
			{
				RndVal	rndnum = Math_Lib.rnd();
				if (rndnum > RND50PC)
					ai.desiredhdg = hdg + ANGLES_60Deg;
				else
					ai.desiredhdg = hdg - ANGLES_60Deg;
			}else
 				ai.desiredhdg = hdg;
			ai.desiredroll = (Angles)(2 + Math_Lib.rnd(2));
 			ai.ManStep = PHASE1;
 			if (MOD.Aileron >= 0)
 			{
 				ACM.SetRudder(MAXRUDDER);
 			}else
 			{
 				ACM.SetRudder(-MAXRUDDER);
 			}
			RndVal	rndnum = Math_Lib.rnd();
			if (rndnum > RND50PC)
				ai.desiredpitch = ANGLES_5Deg;
			else
				ai.desiredpitch = ANGLES_355Deg;
 			
 		}
 		case PHASE1:
 		{
// 			ACM.Pitch(ai.desiredpitch);
 			SWord TempCtrlRudder = ACM.CtrlRudder;
			MoveToHdg (ai.desiredhdg, ai.desiredpitch);
			ACM.CtrlRudder = TempCtrlRudder;
 			if (!ManoeuvreTimeLeft())
 			{
				ai.desiredroll--;
				if (((SWord)ai.desiredroll) < 0)
				{
	 				MOD.Rudder = 0;
					ACM.CtrlRudder = 0;
					ai.manoeuvre = MANOEUVRE_SELECT;
 
				}else
				{
					if (MOD.Rudder > 0)
		 				ACM.SetRudder(-MAXRUDDER);
 					else
		 				ACM.SetRudder(MAXRUDDER);
					RndVal	rndnum = Math_Lib.rnd();
					if (rndnum > RND50PC)
						ai.desiredpitch = ANGLES_5Deg;
					else
						ai.desiredpitch = ANGLES_355Deg;
		 			SetManoeuvreTime (200);
				}
 			}
 			break;
 		}
 	}

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
void	AirStruc::LowAlt()
{
	SWord	reqdeltahdg = 	hdg - HdgIntercept;	
	SWord dpitch;
 	ACMMODEL& ACM = *fly.pAcmModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust (ThrustfromFF());

			SetManoeuvreTime (800);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if (TargetFacingSubject(ANGLES_45Deg))
				dpitch = ANGLES_5Deg;
			else
				dpitch = ANGLES_10Deg;

//DeadCode CSB 28/06/99				if((reqdeltahdg > ANGLES_45Deg) || (reqdeltahdg < -ANGLES_45Deg))
//DeadCode CSB 28/06/99					RollAndPull(reqdeltahdg,dpitch);
//DeadCode CSB 28/06/99				else
//DeadCode CSB 28/06/99					MoveToHdg(HdgIntercept, (Angles)dpitch);
			ACM.Pitch(dpitch);
			ACM.Roll(ANGLES_0Deg);

			if  (!ManoeuvreTimeLeft())
							ai.manoeuvre = MANOEUVRE_SELECT;

					

		}
	}

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
void	AirStruc::SnapShot()
{
//
//similar to turningfight 21/5/98
// but don't slow down
//
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	COORDS3D	target;
	SLong		time;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	reqdeltahdg = 	Rads2Rowan(MOD.fHdg) - HdgIntercept;
	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

	if (		(Range < DANGERRANGE)
			&&	(reqdeltahdg_pos < (SWord)ANGLES_30Deg)
		)		
	{
		//this method just extrapolates position
		//to get turn:
		//get distance travelled and turn in time to work out offset
		time = Range / classtype->muzzlevel;		//MUZZELVEL;
		//calc lead position using this time
		target.X = ai.unfriendly->World.X + (unfriendly->velx * time );
		target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
		target.Z = ai.unfriendly->World.Z + (unfriendly->velz * time );
		InterceptandRange (&target);
	}else
		target = ai.unfriendly->World;

	if (Range < THRUST_0_RANGE)
	{
		ai.ManStep = PHASE0;
		ai.manoeuvre=MANOEUVRE_ZOOM;
	}
	else
//DeadCode RDH 16Dec98 		TurnFightSub(HdgIntercept, FALSE, ANGLES_5Deg, target);
		TurnFightPhase1(HdgIntercept, FALSE, ANGLES_0Deg, target);

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
void	AirStruc::StayOnTail()
{
//	if necessary shed energy:
//		turn
//		brakes
//		throttle
//	to stay on tail
//
//same as turningfight 21/5/98
//
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	COORDS3D	target;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	SLong vx = 0, vy = 0, vz = 0;

	reqdeltahdg = 	hdg - HdgIntercept;
	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

	if (	(reqdeltahdg_pos < (SWord)ANGLES_90Deg)
		)		
	{
		CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);

		target.X = ai.unfriendly->World.X + vx;
		target.Y = ai.unfriendly->World.Y + vy;
		target.Z = ai.unfriendly->World.Z + vz;
		InterceptandRange (&target);
	}else
		target = ai.unfriendly->World;

	TurnWithPitchChange(HdgIntercept, TRUE, target);

//DEADCODE RDH 28/03/99 	SWord	reqdeltahdg,reqdeltahdg_sign;
//DEADCODE RDH 28/03/99 	UWord	reqdeltahdg_pos;
//DEADCODE RDH 28/03/99 	COORDS3D	target;
//DEADCODE RDH 28/03/99 	SLong		time;
//DEADCODE RDH 28/03/99 	MODEL& MOD = *fly.pModel;
//DEADCODE RDH 28/03/99 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DEADCODE RDH 28/03/99 
//DEADCODE RDH 28/03/99 	reqdeltahdg = 	Rads2Rowan(MOD.fHdg) - HdgIntercept;
//DEADCODE RDH 28/03/99 	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DEADCODE RDH 28/03/99 
//DEADCODE RDH 28/03/99 	if (		(Range < DANGERRANGE)
//DEADCODE RDH 28/03/99 			&&	(reqdeltahdg_pos < (SWord)ANGLES_30Deg)
//DEADCODE RDH 28/03/99 		)		
//DEADCODE RDH 28/03/99 	{
//DEADCODE RDH 28/03/99 		//this method just extrapolates position
//DEADCODE RDH 28/03/99 		//to get turn:
//DEADCODE RDH 28/03/99 		//get distance travelled and turn in time to work out offset
//DEADCODE RDH 28/03/99 		time = Range / classtype->muzzlevel;		//MUZZELVEL;
//DEADCODE RDH 28/03/99 		//calc lead position using this time
//DEADCODE RDH 28/03/99 		target.X = ai.unfriendly->World.X + (unfriendly->velx * time );
//DEADCODE RDH 28/03/99 		target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
//DEADCODE RDH 28/03/99 		target.Z = ai.unfriendly->World.Z + (unfriendly->velz * time );
//DEADCODE RDH 28/03/99 		InterceptandRange (&target);
//DEADCODE RDH 28/03/99 	}else
//DEADCODE RDH 28/03/99 		target = ai.unfriendly->World;
//DEADCODE RDH 28/03/99 
//DEADCODE RDH 28/03/99 	TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DEADCODE RDH 28/03/99 //DeadCode RDH 16Dec98 	TurnFightSub(HdgIntercept, TRUE, ANGLES_5Deg, target);

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
Bool	AirStruc::TurnToHdgAndPitch()
{
	//return true on success
	return(TRUE);
}

//DeadCode RDH 07Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 07Jan99 //Procedure		LagFight
//DeadCode RDH 07Jan99 //Author		R. Hyde 
//DeadCode RDH 07Jan99 //Date			Fri 13 Mar 1998
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Description	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Inputs		
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Returns	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 07Jan99 void	AirStruc::HotSideLagPursuitFight()
//DeadCode RDH 07Jan99 {
//DeadCode RDH 07Jan99 //1	trgItem is behind target
//DeadCode RDH 07Jan99 //	TurningFightSub()
//DeadCode RDH 07Jan99 //## need to distinguish between this and LagPursuit
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 07Jan99 	MODEL& MOD = *fly.pModel;
//DeadCode RDH 07Jan99 	COORDS3D	target;
//DeadCode RDH 07Jan99 	SLong		time;
//DeadCode RDH 07Jan99 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 	switch (ai.ManStep)
//DeadCode RDH 07Jan99 	{
//DeadCode RDH 07Jan99 		case PHASE0:
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 			ACM.Thrust (ThrustfromFF());
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 			SetManoeuvreTime (800);
//DeadCode RDH 07Jan99 			ai.ManStep = PHASE1;
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 		case PHASE1:
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 			time	= 20;				//in tenths of sec
//DeadCode RDH 07Jan99 			target.X = ai.unfriendly->World.X - (unfriendly->velx * time );
//DeadCode RDH 07Jan99 			target.Y = ai.unfriendly->World.Y - (unfriendly->vely * time );
//DeadCode RDH 07Jan99 			target.Z = ai.unfriendly->World.Z - (unfriendly->velz * time );
//DeadCode RDH 07Jan99 			InterceptandRange (&target);
//DeadCode RDH 07Jan99 			TurnFightPhase1(HdgIntercept, FALSE, ANGLES_0Deg, target);
//DeadCode RDH 07Jan99 //DeadCode RDH 16Dec98 			TurnFightSub(HdgIntercept, FALSE,ANGLES_5Deg, target);
//DeadCode RDH 07Jan99 			if  (!ManoeuvreTimeLeft())
//DeadCode RDH 07Jan99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 	}
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 }

//DeadCode RDH 07Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 07Jan99 Bool	AirStruc::SandwichManoeuvres()
//DeadCode RDH 07Jan99 {
//DeadCode RDH 07Jan99 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 	if (Range < ENGAGERANGE)
//DeadCode RDH 07Jan99 	{
//DeadCode RDH 07Jan99 		if (	(ai.combatskill > SKILL_REGULAR)
//DeadCode RDH 07Jan99 			&&	(ai.morale > MORALE_MEDIUM)
//DeadCode RDH 07Jan99 			)
//DeadCode RDH 07Jan99 		{
//DeadCode RDH 07Jan99 			if	(SubjectOnTargetTail(ANGLES_45Deg))
//DeadCode RDH 07Jan99 			{
//DeadCode RDH 07Jan99 				if (	(((AirStrucPtr)unfriendly->Follower())->ai.attacker == this)
//DeadCode RDH 07Jan99 					||	(((AirStrucPtr)unfriendly->Follower())->ai.attacker == NULL)
//DeadCode RDH 07Jan99 					)
//DeadCode RDH 07Jan99 				{//feignt to avoid sandwich
//DeadCode RDH 07Jan99 					ai.unfriendly = unfriendly->Follower();
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 					_DPlay.OwnerChangeDecision(this,(AirStrucPtr)(unfriendly->Follower()));//AMM 27Nov98
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 				}
//DeadCode RDH 07Jan99 			}
//DeadCode RDH 07Jan99 //##			if (TargetOnSubjectTail(ANGLE_45Deg))
//DeadCode RDH 07Jan99 //			{
//DeadCode RDH 07Jan99 //				if (	(	(unfriendly->Follower()->unfriendly == this)
//DeadCode RDH 07Jan99 //						||	(unfriendly->Follower()->unfriendly == NULL)
//DeadCode RDH 07Jan99 //						)
//DeadCode RDH 07Jan99 //					&& (TargetsFollowerOnSubjectTail(ANGLE_45Deg)
//DeadCode RDH 07Jan99 //					)
//DeadCode RDH 07Jan99 //				{// to avoid sandwich
//DeadCode RDH 07Jan99 //					if (	(AboveGround(FEET_4000)
//DeadCode RDH 07Jan99 //						&&	(		(vel < )
//DeadCode RDH 07Jan99 //								||	(rnd())
//DeadCode RDH 07Jan99 //							)
//DeadCode RDH 07Jan99 //					{
//DeadCode RDH 07Jan99 //						roll90/180
//DeadCode RDH 07Jan99 //					}else
//DeadCode RDH 07Jan99 //					{
//DeadCode RDH 07Jan99 //							VERTICALLOOP
//DeadCode RDH 07Jan99 //					}
//DeadCode RDH 07Jan99 //				}
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //			}
//DeadCode RDH 07Jan99 		}
//DeadCode RDH 07Jan99 	}
//DeadCode RDH 07Jan99 	return(TRUE);
//DeadCode RDH 07Jan99 }

void		AirStruc::CalcDesiredPitchRate(SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos)
{
	MODEL& MOD = *fly.pModel;
	SWord dpitch;

	ai.desiredpitchrate = AngleSign (Rowan2Rads(PitchIntercept - (SWord)ai.oldoldoldpitchI));
	ai.desiredpitchrate = ai.desiredpitchrate /(3 * MOD.MODEL_DT);


	FP pitchleadmodifier = 0.0025;
	if (reqdeltapitch_sign >= 0 )
		pitchleadmodifier = 0.1;
	if (reqdeltapitch_pos > ANGLES_70Deg)
		dpitch = ANGLES_70Deg;
	else
		dpitch = reqdeltapitch_pos;
	if (reqdeltapitch_sign < 0)
		dpitch = - dpitch;
	ai.deltapitchsum += dpitch;
	SLong IntPitchForMaxDP = 5000000;
	if (ai.deltapitchsum > IntPitchForMaxDP)
		ai.deltapitchsum = IntPitchForMaxDP;
	else if (ai.deltapitchsum < -IntPitchForMaxDP)
		ai.deltapitchsum = - IntPitchForMaxDP;

	ai.desiredpitchrate = ai.desiredpitchrate + (pitchleadmodifier * dpitch/ANGLES_70Deg);
 	ai.desiredpitchrate = ai.desiredpitchrate + pitchleadmodifier * ai.deltapitchsum / (4*IntPitchForMaxDP); 
}



FP	AirStruc::FineRollAdjust(SWord reqdeltapitch,SWord deltahdg,FP rroll, FP fpitch, FP fhdg)
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	SWord	reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;
	FP altmod;
	FP deltahdgmod = 0.0005;
	SWord	deltahdg_sign, dhdg, dpitch;
	UWord	deltahdg_pos;
	FP	desiredturn;
	
	ACM.maxdeltaforclosework = 0.2;


//DeadCode CSB 09/03/99		Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
//DeadCode CSB 09/03/99		Math_Lib.Pos (deltahdg,deltahdg_pos,deltahdg_sign);
//DeadCode CSB 08/03/99	//find desired turn based on hdg change of target
//DeadCode CSB 08/03/99		desiredturn = AngleSign (Rowan2Rads(HdgIntercept - (SWord)ai.oldoldoldhdgI));
//DeadCode CSB 08/03/99		desiredturn = desiredturn /(3 * MOD.MODEL_DT);
//DeadCode CSB 08/03/99	
//DeadCode CSB 08/03/99		desiredturn = (ai.desiredturn + desiredturn)/2;
//DeadCode CSB 08/03/99		ai.desiredturn = desiredturn;
//DeadCode CSB 08/03/99	
//DeadCode CSB 08/03/99	//modify desired turn to "point" at target. Lead account for by input dhdg
//DeadCode CSB 08/03/99		FP leadmodifier = 0.005;
//DeadCode CSB 08/03/99		if (deltahdg_pos > ANGLES_70Deg)
//DeadCode CSB 08/03/99			dhdg = ANGLES_70Deg;
//DeadCode CSB 08/03/99		else
//DeadCode CSB 08/03/99			dhdg = deltahdg_pos;
//DeadCode CSB 08/03/99		if (deltahdg_sign < 0)
//DeadCode CSB 08/03/99			dhdg = - dhdg;
//DeadCode CSB 08/03/99		if  (		((desiredturn >= 0) && (dhdg < 0))
//DeadCode CSB 08/03/99				||
//DeadCode CSB 08/03/99					((desiredturn < 0) && (dhdg >= 0))
//DeadCode CSB 08/03/99				||
//DeadCode CSB 08/03/99					(	(desiredturn < 0.0001)			//if desired turn < 0.5 deg/s 
//DeadCode CSB 08/03/99						&&
//DeadCode CSB 08/03/99						(desiredturn > -0.0001)
//DeadCode CSB 08/03/99					)
//DeadCode CSB 08/03/99			)
//DeadCode CSB 08/03/99		desiredturn = desiredturn - (leadmodifier * dhdg/ANGLES_70Deg); 

//DeadCode CSB 08/03/99		desiredturn = 0;
//DeadCode CSB 09/03/99		CalcDesiredPitchRate(reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos);	//needed for pushing stick forwards

//Global axis
	{
//DeadCode CSB 10/03/99			SWord sinpitch, cospitch;
//DeadCode CSB 10/03/99			Math_Lib.high_sin_cos(pitch, sinpitch, cospitch);
		
		FP AveHeadgRate = AngleSign (Rowan2Rads(HdgIntercept   - (SWord)ai.oldoldoldhdgI  )) / (3 * MOD.MODEL_DT);
		FP AvePitchRate = AngleSign (Rowan2Rads(PitchIntercept - (SWord)ai.oldoldoldpitchI)) / (3 * MOD.MODEL_DT);
		rroll			= FPATan(MOD.Speed * AveHeadgRate, (MOD.Speed * AvePitchRate + GRAVITY));// * cospitch / 32768);
		FP DeltaRroll = 0;
		if(MOD.RotVel.x > 0)
			DeltaRroll = 0.01 * fhdg / MOD.RotVel.x;			
		MODLIMIT(DeltaRroll, 0.25);
			rroll += DeltaRroll;
	}
	rroll = AngleSign(rroll);
#ifdef PRINT_AI_DATA
	PrintVar(50, 18, "Rroll     %.1f ", (FP)(57.3 * rroll));	
	PrintVar(50, 19, "RPitch    %.1f ", (FP)(57.3 * fpitch));	
#endif
//DeadCode CSB 09/03/99	
//DeadCode CSB 09/03/99	PrintVar(50, 17, "Rroll     %.1f ", (FP)(57.3 * rroll));	
//DeadCode CSB 09/03/99		if(rollfactor < 1)
//DeadCode CSB 09/03/99		{
//DeadCode CSB 09/03/99			if(fpitch < 0) rroll = AngleSign(FPIE - rroll);
//DeadCode CSB 09/03/99			rroll *= rollfactor;
//DeadCode CSB 09/03/99		}
//DeadCode CSB 09/03/99		if((fpitch > - 0.025) && (fpitch < 0.025) && (fhdg > -0.025) && (fhdg < 0.025)) rroll = deltahdg;	//CSB 08/03/99
//DeadCode CSB 09/03/99	
//DeadCode CSB 09/03/99							PrintString(50, 18, "              ");
//DeadCode CSB 09/03/99	if(rroll == deltahdg)	PrintString(50, 18, "ROLL = HEADING");
//DeadCode CSB 09/03/99	
//DeadCode CSB 09/03/99		if(fpitch < 0)
//DeadCode CSB 09/03/99			rroll = 0;	//when pushing stick, keep roll as is
//DeadCode CSB 09/03/99		rroll = MOD.fRoll + rroll;

//DeadCode CSB 09/03/99		rroll = AngleSign(rroll);
//DeadCode CSB 09/03/99		if (	fpitch < 0
//DeadCode CSB 09/03/99			)
//DeadCode CSB 09/03/99		{
//DeadCode CSB 09/03/99			FP x;
//DeadCode CSB 09/03/99			FP pitchaccel = 0;
//DeadCode CSB 09/03/99			if  (		(roll >> ANGLES_20Deg)
//DeadCode CSB 09/03/99	   				&&	(roll << ANGLES_340Deg)
//DeadCode CSB 09/03/99				)	
//DeadCode CSB 09/03/99				pitchaccel = ai.desiredpitchrate * MOD.Speed;
//DeadCode CSB 09/03/99			if (	(-pitchaccel) < GRAVITY)
//DeadCode CSB 09/03/99			{
//DeadCode CSB 09/03/99				x = 	desiredturn * MOD.Speed / (GRAVITY + pitchaccel);
//DeadCode CSB 09/03/99				rroll = FPATan (x,1);
//DeadCode CSB 09/03/99				rroll = AngleSign(rroll);
//DeadCode CSB 09/03/99			}else
//DeadCode CSB 09/03/99			{
//DeadCode CSB 09/03/99				if (desiredturn > 0)
//DeadCode CSB 09/03/99					rroll = 1.57;
//DeadCode CSB 09/03/99				else
//DeadCode CSB 09/03/99					rroll = -1.57;
//DeadCode CSB 09/03/99			}
//DeadCode CSB 09/03/99		}


//DeadCode CSB 08/03/99		FP DeltaRoll = Rowan2Rads(unfriendly->roll - roll);
//DeadCode CSB 08/03/99		DeltaRoll =  AngleSign(DeltaRoll);		
//DeadCode CSB 08/03/99		FP DeltaRollPos;
//DeadCode CSB 08/03/99		if(DeltaRoll >= 0) DeltaRollPos =  DeltaRoll;
//DeadCode CSB 08/03/99		else			   DeltaRollPos = -DeltaRoll;

//DeadCode CSB 05/03/99		if (				(fpitch <  0.05)
//DeadCode CSB 05/03/99						&&	(fpitch > -0.05)
//DeadCode CSB 05/03/99						&&	(fhdg <  0.05)
//DeadCode CSB 05/03/99						&&	(fhdg > -0.05)
//DeadCode CSB 05/03/99						&&	(DeltaRollPos < F1PIE2 * (256 + FlyingFactor()) / 512)
//DeadCode CSB 05/03/99					)
//DeadCode CSB 05/03/99		{
//DeadCode CSB 05/03/99			MOD.Rudder = 0;
//DeadCode CSB 05/03/99			MOD.Aileron = (SWord)( (FP)(unfriendly->roll - roll) * ACM.rollmodifier );
//DeadCode CSB 05/03/99			MOD.Elevator = 0;
//DeadCode CSB 05/03/99			DeltaRoll *= ACM.rollmodifier * 0.25;
//DeadCode CSB 05/03/99			fly.pModel->ChangeDirection(this,fpitch,-fhdg,DeltaRoll);
//DeadCode CSB 05/03/99	PrintString(0, 21, "LOCKED");
//DeadCode CSB 05/03/99		}
//DeadCode CSB 05/03/99		else
	{
#ifdef PRINT_AI_DATA
	PrintString(0, 20, "FINE ROLL ADJUST");
#endif

		ACM.TurnRate(fpitch);
//DeadCode CSB 12/03/99			ACM.YawRate(fhdg);
//DeadCode CSB 11/03/99			fly.pModel->ChangeDirection(this, fpitch, -fhdg, 0);
	}

	return(rroll);
}


//DeadCode RDH 11Dec98 	MODEL& MOD = *fly.pModel;
//DeadCode RDH 11Dec98 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 	ACM.maxdeltaforclosework = 0.4;
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 	FP	absfpitch = fpitch;
//DeadCode RDH 11Dec98 	if (absfpitch < 0)
//DeadCode RDH 11Dec98 		absfpitch = fpitch;
//DeadCode RDH 11Dec98 	FP	aroll = AngleSign(MOD.fRoll);
//DeadCode RDH 11Dec98 	if (aroll < 0)
//DeadCode RDH 11Dec98 		aroll = -aroll;
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 	//if pointing at target and right way up
//DeadCode RDH 11Dec98 	//then invert excessive roll requests
//DeadCode RDH 11Dec98 //	if  (		(absfpitch < 0.2)
//DeadCode RDH 11Dec98 //			&&	(		(aroll < F1PIE2)
//DeadCode RDH 11Dec98 //				)
//DeadCode RDH 11Dec98 //		)
//DeadCode RDH 11Dec98 //	{
//DeadCode RDH 11Dec98 //		if (rroll > F1PIE2)
//DeadCode RDH 11Dec98 //			rroll = rroll - FPIE;
//DeadCode RDH 11Dec98 //		if (rroll < -F1PIE2)
//DeadCode RDH 11Dec98 //			rroll = rroll + FPIE;
//DeadCode RDH 11Dec98 //	}
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 //	if (		(absfpitch < 0.2)
//DeadCode RDH 11Dec98 //			&&	(absfpitch > -0.2)
//DeadCode RDH 11Dec98 //		)
//DeadCode RDH 11Dec98 //	{
//DeadCode RDH 11Dec98 //		rroll = rroll * (absfpitch)/0.2;
//DeadCode RDH 11Dec98 //	}
//DeadCode RDH 11Dec98 //				if (		(rroll < 0.2)
//DeadCode RDH 11Dec98 //						&&	(rroll > -0.2)
//DeadCode RDH 11Dec98 //					)
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 		rroll =  MOD.fRoll + rroll;
//DeadCode RDH 11Dec98 		ACM.YawRate(fhdg);
//DeadCode RDH 11Dec98 		return(rroll);
//}
FP	AirStruc::CoarseRollAdjust(FP rroll, FP fpitch)
{
#ifdef PRINT_AI_DATA
	PrintString(0, 19, "Coarse Roll Adjust");
#endif

	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;

	ACM.maxdeltaforclosework = 0.1;
	MOD.Rudder = 0;//MOD.Rudder/2;
	ACM.deltayawsum = 0;//ACM.deltayawsum/2;

	if((fpitch > 0) && (ACM.deltapitchsum < 0)) ACM.deltapitchsum = 0;
	if((fpitch < 0) && (ACM.deltapitchsum > 0)) ACM.deltapitchsum = 0;

	rroll = AngleSign(rroll);

//DeadCode CSB 11/03/99		ACM.deltapitchsum = 0;	//CSB 09/03/99
	FP AbsRroll;
	if(rroll > 0)	AbsRroll =  rroll;
	else			AbsRroll = -rroll;

	if((AbsRroll < FPIE / 6) || (AbsRroll > (1 - 1/6) * FPIE))	ACM.TurnRate(fpitch);	//CSB 09/03/99
	else ACM.TurnRate(0);

	rroll += Rowan2Rads(roll);
	rroll = AngleSign(rroll);

	return(rroll);
}


Bool	AirStruc::UnfriendlyOnSameRoll()
{
	MODEL& MOD = *fly.pModel;

	AirStrucPtr	unfriendly = *ai.unfriendly;
	if (	(		(roll << ANGLES_180Deg)
				&&	(unfriendly->roll << ANGLES_180Deg)			
			)
			||
			(		(roll >> ANGLES_180Deg)
				&&	(unfriendly->roll >> ANGLES_180Deg)			
			)
		)
		return (TRUE);
	else
		return(FALSE);


}
SWord	AirStruc::RollforTurn(SWord reqdeltapitch,SWord deltahdg, Float& desiredturn,COORDS3D	target)
{


	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
		
		if(ACM.maxdeltaforclosework < 0.1)
		ACM.maxdeltaforclosework = 0.1;
#ifdef PRINT_AI_DATA
	PrintVar(15, 20, "MaxDelta %.1f ", ACM.maxdeltaforclosework);
#endif

//find roll which would put target on lift line
	FP rroll;
	Float fpitch,fhdg;
//DeadCode CSB 08/03/99		ANGLES reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );

	FP gdpitch =  AngleSign( Rowan2Rads(reqdeltapitch) );
	FP gdhdg   = -AngleSign( Rowan2Rads(deltahdg) );
	SWord sinroll, cosroll;
	Math_Lib.high_sin_cos(roll, sinroll, cosroll);
	fpitch = gdpitch * cosroll / 32768 + gdhdg   * sinroll / 32768;
	fhdg   = gdhdg   * cosroll / 32768 - gdpitch * sinroll / 32768;
	fpitch = AngleSign(fpitch);
	fhdg   = AngleSign(fhdg);
	ANGLES reqroll = Angles(Rads2Rowan(FPATan(fhdg, fpitch) ) );
	
#ifdef PRINT_AI_DATA
	PrintVar(35, 10, "ReqDPitch %.2f ", (FP)(fpitch * 57.3) );
	PrintVar(35, 11, "ReqDRoll  %.2f ", (FP)(reqroll / 182.04) );
	PrintVar(35, 12, "ReqDHeadg %.2f ", (FP)(fhdg * 57.3) );
	PrintVar(35, 13, "Range     %.2f ", (FP)(Range * 0.01) );
#endif

		FP rr = Rowan2Rads(reqroll);
		rroll =  AngleSign(rr);

	if(//(UnfriendlyOnSameRoll())
		//&&	
			(fpitch < ACM.maxdeltaforclosework)
		&&	(fpitch > -ACM.maxdeltaforclosework)
		&&	(fhdg < ACM.maxdeltaforclosework)
		&&	(fhdg > -ACM.maxdeltaforclosework)	)
	{
		rroll = FineRollAdjust(reqdeltapitch, deltahdg, rroll, fpitch, fhdg);
	}
	else
//DeadCode CSB 12/03/99			fly.pModel->ChangeDirection(this, fpitch, -fhdg, 0);
		rroll = CoarseRollAdjust(rroll, fpitch);

	return(Rads2Rowan (rroll));


}

//DeadCode RDH 07Dec98 //if close to pointing at target, 
//DeadCode RDH 07Dec98 		if  (	(	(fpitch < ACM.maxdeltaforclosework)
//DeadCode RDH 07Dec98 					&&	(fpitch > -ACM.maxdeltaforclosework)
//DeadCode RDH 07Dec98 					&&	(fhdg < ACM.maxdeltaforclosework)
//DeadCode RDH 07Dec98 					&&	(fhdg > -ACM.maxdeltaforclosework)
//DeadCode RDH 07Dec98 				)
//DeadCode RDH 07Dec98 			)
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 		{
//DeadCode RDH 07Dec98 			ACM.maxdeltaforclosework = 0.4;
//DeadCode RDH 07Dec98 			{
//DeadCode RDH 07Dec98 				if (rroll > 1.57)
//DeadCode RDH 07Dec98 					rroll = rroll - 3.14159;
//DeadCode RDH 07Dec98 				if (rroll < -1.57)
//DeadCode RDH 07Dec98 					rroll = rroll + 3.14159;
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 //				if (		(rroll < 0.2)
//DeadCode RDH 07Dec98 //						&&	(rroll > -0.2)
//DeadCode RDH 07Dec98 //					)
//DeadCode RDH 07Dec98 					rroll =  MOD.fRoll + rroll;
//DeadCode RDH 07Dec98 				ACM.YawRate(fhdg);
//DeadCode RDH 07Dec98 			}
//DeadCode RDH 07Dec98 		}else
//DeadCode RDH 07Dec98 //not close to pointing at target
//DeadCode RDH 07Dec98 		{
//DeadCode RDH 07Dec98 			{
//DeadCode RDH 07Dec98 				ACM.maxdeltaforclosework = 0.1;
//DeadCode RDH 07Dec98 				rroll =  MOD.fRoll + rroll;
//DeadCode RDH 07Dec98 				MOD.Rudder = MOD.Rudder/2;
//DeadCode RDH 07Dec98 				ACM.deltayawsum = ACM.deltayawsum/2;
//DeadCode RDH 07Dec98 			}
//DeadCode RDH 07Dec98 		}
//DeadCode RDH 07Dec98 		rroll = AngleSign(rroll);
//DeadCode RDH 07Dec98 		ACM.TurnRate(fpitch);
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 	return(Rads2Rowan (rroll));
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 }
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 07Dec98 	MODEL& MOD = *fly.pModel;
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 //find roll which would put target on lift line
//DeadCode RDH 07Dec98 	FP rroll;
//DeadCode RDH 07Dec98 	Float fpitch,fhdg;
//DeadCode RDH 07Dec98 		ANGLES reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
//DeadCode RDH 07Dec98 		FP rr = Rowan2Rads(reqroll);
//DeadCode RDH 07Dec98 		rroll =  AngleSign(rr);
//DeadCode RDH 07Dec98 //if close to pointing at target, 
//DeadCode RDH 07Dec98 		if  (	(	(fpitch < ACM.maxdeltaforclosework)
//DeadCode RDH 07Dec98 					&&	(fpitch > -ACM.maxdeltaforclosework)
//DeadCode RDH 07Dec98 					&&	(fhdg < ACM.maxdeltaforclosework)
//DeadCode RDH 07Dec98 					&&	(fhdg > -ACM.maxdeltaforclosework)
//DeadCode RDH 07Dec98 				)
//DeadCode RDH 07Dec98 			)
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 		{
//DeadCode RDH 07Dec98 			ACM.maxdeltaforclosework = 0.4;
//DeadCode RDH 07Dec98 			{
//DeadCode RDH 07Dec98 				if (rroll > 1.57)
//DeadCode RDH 07Dec98 					rroll = rroll - 3.14159;
//DeadCode RDH 07Dec98 				if (rroll < -1.57)
//DeadCode RDH 07Dec98 					rroll = rroll + 3.14159;
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 //				if (		(rroll < 0.2)
//DeadCode RDH 07Dec98 //						&&	(rroll > -0.2)
//DeadCode RDH 07Dec98 //					)
//DeadCode RDH 07Dec98 					rroll =  MOD.fRoll + rroll;
//DeadCode RDH 07Dec98 				ACM.YawRate(fhdg);
//DeadCode RDH 07Dec98 			}
//DeadCode RDH 07Dec98 		}else
//DeadCode RDH 07Dec98 //not close to pointing at target
//DeadCode RDH 07Dec98 		{
//DeadCode RDH 07Dec98 			{
//DeadCode RDH 07Dec98 				ACM.maxdeltaforclosework = 0.1;
//DeadCode RDH 07Dec98 				rroll =  MOD.fRoll + rroll;
//DeadCode RDH 07Dec98 				MOD.Rudder = MOD.Rudder/2;
//DeadCode RDH 07Dec98 				ACM.deltayawsum = ACM.deltayawsum/2;
//DeadCode RDH 07Dec98 			}
//DeadCode RDH 07Dec98 		}
//DeadCode RDH 07Dec98 		rroll = AngleSign(rroll);
//DeadCode RDH 07Dec98 		ACM.TurnRate(fpitch);
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 	return(Rads2Rowan (rroll));
//DeadCode RDH 07Dec98 
//DeadCode RDH 07Dec98 }













//DeadCode RDH 02Dec98 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 02Dec98 	MODEL& MOD = *fly.pModel;
//DeadCode RDH 02Dec98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 02Dec98 	SWord	reqdeltapitch_sign;
//DeadCode RDH 02Dec98 	UWord	reqdeltapitch_pos;
//DeadCode RDH 02Dec98 	FP altmod;
//DeadCode RDH 02Dec98 	FP deltahdgmod = 0.0005;
//DeadCode RDH 02Dec98 	SWord	deltahdg_sign, dhdg, dpitch;
//DeadCode RDH 02Dec98 	UWord	deltahdg_pos;
//DeadCode RDH 02Dec98 	
//DeadCode RDH 02Dec98 	if(ACM.maxdeltaforclosework < 0.1)
//DeadCode RDH 02Dec98 		ACM.maxdeltaforclosework = 0.1;
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 //	flight_ctl* flight = &unfriendly->fly;
//DeadCode RDH 02Dec98 //	MODEL& UNFMOD = *flight->pModel;
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 //	MODEL& UNFMOD = *(&unfriendly->fly)->pModel;
//DeadCode RDH 02Dec98 //DeadCode AMM 01Jul98 	MODEL& UNFMOD = *(unfriendly->fly).pModel;		//define UNFMOD as a reference to
//DeadCode RDH 02Dec98 													//type MODEL 
//DeadCode RDH 02Dec98 													//star gives the contents of the pointer
//DeadCode RDH 02Dec98 													// temp.foo is equivalent to (&temp)->foo
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 	Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
//DeadCode RDH 02Dec98 	Math_Lib.Pos (deltahdg,deltahdg_pos,deltahdg_sign);
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 //find desired turn based on hdg change of target
//DeadCode RDH 02Dec98 	desiredturn = AngleSign (Rowan2Rads(HdgIntercept - (SWord)ai.oldoldoldhdgI));
//DeadCode RDH 02Dec98 	desiredturn = desiredturn /(3 * MOD.MODEL_DT);
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 	desiredturn = (ai.desiredturn + desiredturn)/2;
//DeadCode RDH 02Dec98 	ai.desiredturn = desiredturn;
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 //modify desired turn to "point" at target. Lead account for by input dhdg
//DeadCode RDH 02Dec98 	FP leadmodifier = 0.005;
//DeadCode RDH 02Dec98 	if (deltahdg_pos > ANGLES_70Deg)
//DeadCode RDH 02Dec98 		dhdg = ANGLES_70Deg;
//DeadCode RDH 02Dec98 	else
//DeadCode RDH 02Dec98 		dhdg = deltahdg_pos;
//DeadCode RDH 02Dec98 	if (deltahdg_sign < 0)
//DeadCode RDH 02Dec98 		dhdg = - dhdg;
//DeadCode RDH 02Dec98 	if  (		((desiredturn >= 0) && (dhdg < 0))
//DeadCode RDH 02Dec98 			||
//DeadCode RDH 02Dec98 				((desiredturn < 0) && (dhdg >= 0))
//DeadCode RDH 02Dec98 			||
//DeadCode RDH 02Dec98 				(	(desiredturn < 0.0001)			//if desired turn < 0.5 deg/s 
//DeadCode RDH 02Dec98 					&&
//DeadCode RDH 02Dec98 					(desiredturn > -0.0001)
//DeadCode RDH 02Dec98 				)
//DeadCode RDH 02Dec98 		)
//DeadCode RDH 02Dec98 	desiredturn = desiredturn - (leadmodifier * dhdg/ANGLES_70Deg); 
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 //	CalcDesiredPitchRate(reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos);
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 //find roll which would put target on lift line
//DeadCode RDH 02Dec98 	FP rroll;
//DeadCode RDH 02Dec98 	Float fpitch,fhdg;
//DeadCode RDH 02Dec98 		ANGLES reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
//DeadCode RDH 02Dec98 		FP rr = Rowan2Rads(reqroll);
//DeadCode RDH 02Dec98 		rroll =  AngleSign(rr);
//DeadCode RDH 02Dec98 //if close to pointing at target, 
//DeadCode RDH 02Dec98 		if  (	(	(fpitch < ACM.maxdeltaforclosework)
//DeadCode RDH 02Dec98 					&&	(fpitch > -ACM.maxdeltaforclosework)
//DeadCode RDH 02Dec98 					&&	(fhdg < ACM.maxdeltaforclosework)
//DeadCode RDH 02Dec98 					&&	(fhdg > -ACM.maxdeltaforclosework)
//DeadCode RDH 02Dec98 				)
//DeadCode RDH 02Dec98 			)
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 		{
//DeadCode RDH 02Dec98 			ACM.maxdeltaforclosework = 0.4;
//DeadCode RDH 02Dec98 			{
//DeadCode RDH 02Dec98 //				if  (	(fpitch < 0.3)
//DeadCode RDH 02Dec98 //					&&	(fpitch > -0.3)
//DeadCode RDH 02Dec98 //					&&	(fhdg < 0.3)
//DeadCode RDH 02Dec98 //					&&	(fhdg > -0.3)
//DeadCode RDH 02Dec98 //					)
//DeadCode RDH 02Dec98 //				{
//DeadCode RDH 02Dec98 //	
//DeadCode RDH 02Dec98 //					FP x;
//DeadCode RDH 02Dec98 //						FP pitchaccel = 0;
//DeadCode RDH 02Dec98 //					 	if  (		(roll >> ANGLES_20Deg)
//DeadCode RDH 02Dec98 //					   			&&	(roll << ANGLES_340Deg)
//DeadCode RDH 02Dec98 //			 			)	
//DeadCode RDH 02Dec98 //						pitchaccel = ai.desiredpitchrate * MOD.Speed;
//DeadCode RDH 02Dec98 //						if	(		(classtype->visible == MIG15)
//DeadCode RDH 02Dec98 //								&&	(!SubjectOnTargetTail(ANGLES_90Deg))
//DeadCode RDH 02Dec98 //								&&	(pitchaccel < 0)
//DeadCode RDH 02Dec98 //							)
//DeadCode RDH 02Dec98 //							pitchaccel = 0;
//DeadCode RDH 02Dec98 //
//DeadCode RDH 02Dec98 //					if (	(-pitchaccel) < GRAVITY)
//DeadCode RDH 02Dec98 //					{
//DeadCode RDH 02Dec98 //						x = 	desiredturn * MOD.Speed / (GRAVITY + pitchaccel);
//DeadCode RDH 02Dec98 //						rroll = FPATan (x,1);
//DeadCode RDH 02Dec98 //						rroll = AngleSign(rroll);
//DeadCode RDH 02Dec98 //					}else
//DeadCode RDH 02Dec98 //					{
//DeadCode RDH 02Dec98 //						if (desiredturn > 0)
//DeadCode RDH 02Dec98 //							rroll = 1.57;
//DeadCode RDH 02Dec98 //						else
//DeadCode RDH 02Dec98 //							rroll = -1.57;
//DeadCode RDH 02Dec98 //					}
//DeadCode RDH 02Dec98 //						ACM.YawRate(fhdg);
//DeadCode RDH 02Dec98 //				}else
//DeadCode RDH 02Dec98 //				{
//DeadCode RDH 02Dec98 					
//DeadCode RDH 02Dec98 					if (rroll > 1.57)
//DeadCode RDH 02Dec98 						rroll = rroll - 1.57;
//DeadCode RDH 02Dec98 					if (rroll < -3.14159)
//DeadCode RDH 02Dec98 						rroll = rroll + 3.14159;
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 //				if  (	(fpitch < 0.2)
//DeadCode RDH 02Dec98 //					&&	(fpitch > -0.2)
//DeadCode RDH 02Dec98 //					&&	(fhdg < 0.2)
//DeadCode RDH 02Dec98 //					&&	(fhdg > -0.2)
//DeadCode RDH 02Dec98 //					)
//DeadCode RDH 02Dec98 //						rroll = rroll/2;			//to minimise roll when in close
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 					rroll =  MOD.fRoll + rroll;
//DeadCode RDH 02Dec98 					ACM.YawRate(fhdg);
//DeadCode RDH 02Dec98 //				}
//DeadCode RDH 02Dec98 			}
//DeadCode RDH 02Dec98 		}else
//DeadCode RDH 02Dec98 //not close to pointing at target
//DeadCode RDH 02Dec98 		{
//DeadCode RDH 02Dec98 //			if  (	(		((desiredturn >= 0) && (dhdg > 0))
//DeadCode RDH 02Dec98 //							||
//DeadCode RDH 02Dec98 //							((desiredturn < 0) && (dhdg < 0))
//DeadCode RDH 02Dec98 //					)
//DeadCode RDH 02Dec98 //				)
//DeadCode RDH 02Dec98   //
//DeadCode RDH 02Dec98 //		{//attempt to predict change of turn
//DeadCode RDH 02Dec98 //					FP x;
//DeadCode RDH 02Dec98 //						FP pitchaccel = 0;
//DeadCode RDH 02Dec98 //					 	if  (		(roll >> ANGLES_20Deg)
//DeadCode RDH 02Dec98 //					   			&&	(roll << ANGLES_340Deg)
//DeadCode RDH 02Dec98 //			 			)	
//DeadCode RDH 02Dec98 //						pitchaccel = ai.desiredpitchrate * MOD.Speed;
//DeadCode RDH 02Dec98 //					if (	(-pitchaccel) < GRAVITY)
//DeadCode RDH 02Dec98 //					{
//DeadCode RDH 02Dec98 //						x = 	desiredturn * MOD.Speed / (GRAVITY + pitchaccel);
//DeadCode RDH 02Dec98 //						rroll = FPATan (x,1);
//DeadCode RDH 02Dec98 //						rroll = AngleSign(rroll);
//DeadCode RDH 02Dec98 //					}else
//DeadCode RDH 02Dec98 //					{
//DeadCode RDH 02Dec98 //						if (desiredturn > 0)
//DeadCode RDH 02Dec98 //							rroll = 1.57;
//DeadCode RDH 02Dec98 //						else
//DeadCode RDH 02Dec98 //							rroll = -1.57;
//DeadCode RDH 02Dec98 //					}
//DeadCode RDH 02Dec98 //
//DeadCode RDH 02Dec98 //			}else
//DeadCode RDH 02Dec98 			{
//DeadCode RDH 02Dec98 				ACM.maxdeltaforclosework = 0.1;
//DeadCode RDH 02Dec98 				rroll =  MOD.fRoll + rroll;
//DeadCode RDH 02Dec98 					if (	(fhdg < 0.15)
//DeadCode RDH 02Dec98 						&&	(fhdg > -0.15)
//DeadCode RDH 02Dec98 						&&	(fpitch < 0.15)
//DeadCode RDH 02Dec98 						&&	(fpitch > -0.15)
//DeadCode RDH 02Dec98 						)
//DeadCode RDH 02Dec98 						ACM.YawRate(fhdg);
//DeadCode RDH 02Dec98 					else
//DeadCode RDH 02Dec98 					{
//DeadCode RDH 02Dec98 						MOD.Rudder = MOD.Rudder/2;
//DeadCode RDH 02Dec98 						ACM.deltayawsum = ACM.deltayawsum/2;
//DeadCode RDH 02Dec98 					}
//DeadCode RDH 02Dec98 			}
//DeadCode RDH 02Dec98 		}
//DeadCode RDH 02Dec98 		rroll = AngleSign(rroll);
//DeadCode RDH 02Dec98 		ACM.TurnRate(fpitch);
//DeadCode RDH 02Dec98 
//DeadCode RDH 02Dec98 	return(Rads2Rowan (rroll));
//DeadCode RDH 02Dec98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
SWord	AirStruc::ThrustfromFF()
{
//simple thrust modified in CalcSimpleAccel
//complex model: instead of modifying thrust we rely on drag effect via reduced lift
//DEADCODE RDH 06/05/99 	SWord thrust;
//DEADCODE RDH 06/05/99 	UByte	FF = FlyingFactor();
//DEADCODE RDH 06/05/99 	thrust = 85 + (FF * FF * 15)/65536;
//DEADCODE RDH 06/05/99 	if (thrust > 96)
//DEADCODE RDH 06/05/99 		thrust = 100;
 	return(100);
//DEADCODE RDH 06/05/99 	return (thrust);												  //RDH 06/05/99
}

void	AirStruc::SpeedUp(FP velc)
{
	//Enter with velc negaticve, ie need to speed up
		FP time;
		MODEL& MOD = *fly.pModel;
   	SWord thrust;
   	SWord maxthrust = ThrustfromFF();
	thrust = maxthrust;
		ACMMODEL& ACM = *fly.pAcmModel;

	velc = -velc;
	time = (Range - IDEALCOMBATRANGE)/velc;				//cs
	if (time > 0)
	{
		FP accell = velc/time;							//cm/cs/cs
			//Told - Dold  = m* accelold
		//Tnew -Dnew = m * accelnew + m* accelold
		//assume Dold and Dnew are same
		//Tn = To + m(an)

//CSB 29Jun99 VVV
		FP fMass = weap.left.int_fuel + weap.centre.int_fuel + weap.right.int_fuel;
		if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
		{
			fMass += weap.left.ext_fuel + weap.centre.ext_fuel + weap.right.ext_fuel;
			fMass += weap.left.mass     + weap.centre.mass     + weap.right.mass;
		}
		fMass = fMass * 0.001 + classtype->weightempty;
//CSB 29Jun99 ^^^

//DeadCode AMM 29Jun99 		FP deltaforce = (accell) * MOD.Mass;//N
		FP deltaforce = (accell) * fMass;//N	//CSB 29Jun99
		FP Tn = MOD.EngineList->Thrust + deltaforce;
		thrust = 100 * Tn/MOD.EngineList->MaxThrust;
		if (thrust < 0)
		{
			if (thrust < - 300)
			{
				thrust = maxthrust;
				ACM.SpeedBrakesIn();
				if (Range < METRES150)
				{
					ai.ManStep = PHASE0;
					if (SubjectLeadingTarget())
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGROLL, MANOEUVRE_TURNINGFIGHT);
					else
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGPURSUIT, MANOEUVRE_TURNINGFIGHT);
				}

			}else
			{
				thrust = 0;
				ACM.SpeedBrakesOut();
			}
		}else
			ACM.SpeedBrakesIn();
		if (thrust > maxthrust)
			thrust = maxthrust;
	}
	else
	{	//stay as you are if inside min range
		thrust = 100 * MOD.EngineList->Thrust/MOD.EngineList->MaxThrust;
	}
	ACM.Thrust (thrust);
}

void	AirStruc::SlowDown(FP velc)
{
	//Enter with velc positive, need to slow down
		FP time;
			MODEL& MOD = *fly.pModel;
		SWord thrust;
  	SWord maxthrust = ThrustfromFF();
		ACMMODEL& ACM = *fly.pAcmModel;
	thrust = maxthrust;


	if (velc != 0)
		time = (Range - IDEALCOMBATRANGE)/velc;				//cs
	else
		time = 100;
	if (time < 0)
	{//inside min range and need to low down
				if (Range < METRES150)
				{
					thrust = maxthrust;
					ACM.SpeedBrakesIn();
					ai.ManStep = PHASE0;
					if (SubjectLeadingTarget())
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGROLL, MANOEUVRE_ZOOM);
					else
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGPURSUIT, MANOEUVRE_ZOOM);
				}else
				{
					thrust = 0;
					ACM.SpeedBrakesOut();
				}
	}
	else
	{
		FP decell = -velc/time;							//cm/cs/cs
			//Told - Dold  = m* accelold
		//Tnew -Dnew = m * accelnew
		//assume Dold and Dnew are same
		//Tn = To + m(an-ao)
//DEADCODE DAW 01/04/99 		FP deltaforce = (decell - MOD.Acc.z) * MOD.Mass;//N

//CSB 29Jun99 VVV
		FP fMass = weap.left.int_fuel + weap.centre.int_fuel + weap.right.int_fuel;
		if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
		{
			fMass += weap.left.ext_fuel + weap.centre.ext_fuel + weap.right.ext_fuel;
			fMass += weap.left.mass     + weap.centre.mass     + weap.right.mass;
		}
		fMass = fMass * 0.001 + classtype->weightempty;
//CSB 29Jun99 ^^^

//DeadCode AMM 29Jun99 		FP deltaforce = (decell) * MOD.Mass;//N
		FP deltaforce = (decell) * fMass;//N	   //CSB 29Jun99
		FP Tn = MOD.EngineList->Thrust + deltaforce;
		thrust = 100 * Tn/MOD.EngineList->MaxThrust;
		if (thrust < 0)
		{
			if  (	(thrust < - 300)
				&&	(Range < METRES150)
				)
			{
				thrust = maxthrust;
				ACM.SpeedBrakesIn();
				ai.ManStep = PHASE0;
				if (SubjectLeadingTarget())
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGPURSUIT, MANOEUVRE_TURNINGFIGHT);
				else
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGPURSUIT, MANOEUVRE_TURNINGFIGHT);
			}else
			{
				thrust = 0;
				ACM.SpeedBrakesOut();
			}
		}else
			ACM.SpeedBrakesIn();
		if (thrust > maxthrust)
			thrust = maxthrust;
	}
	ACM.Thrust (thrust);
}



void	AirStruc::SlowDownCheck(UWord reqdeltahdg_pos)
{
	SWord thrust = 100;
	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

//DeadCode CSB 14/04/99			SLong ReqVel = 0;
//DeadCode CSB 14/04/99		SWord MaxAcc = -CalcAccel(0);	//Ensure requesting decel not accel
//DeadCode CSB 14/04/99		SLong velfactor = unfriendly->vel * unfriendly->vel;
//DeadCode CSB 14/04/99		velfactor += (MaxAcc * (Range - IDEALCOMBATRANGE)) * (2.0 / 2560.0);
//DeadCode CSB 14/04/99		if (velfactor > 0)
//DeadCode CSB 14/04/99			ReqVel = FSqrt(	velfactor);
//DeadCode CSB 14/04/99		else
//DeadCode CSB 14/04/99			ReqVel = unfriendly->vel;

 	if((!SubjectFacingTarget(ANGLES_45Deg)) || (!SubjectOnTargetTail(ANGLES_45Deg)))
		thrust = ThrustfromFF();
	else
	{
		SLong ReqVel = 0;
		SWord MaxAcc = 0;
		Bool TooClose = FALSE;
		if(Range < IDEALCOMBATRANGE) TooClose = TRUE;

		if(TooClose)
			MaxAcc = -CalcAccel(32000);
		else
			MaxAcc = -CalcAccel(0);	//Ensure requesting decel not accel
 		MaxAcc = MaxAcc / 2;

		if(MaxAcc == 0)
		{
			if(TooClose)
				thrust = 0;
			else
				thrust = ThrustfromFF();
		}
		else
		{
			FP velfactor = ((FP)MaxAcc * ((FP)Range - (FP)IDEALCOMBATRANGE)) * (2.0 / 2560.0);
			if (velfactor > 0)
			{
				if(Range > IDEALCOMBATRANGE)
					ReqVel = unfriendly->vel + FSqrt(velfactor);
				else
					ReqVel = unfriendly->vel - FSqrt(velfactor);
			}
			else
				ReqVel = unfriendly->vel;

//DeadCode CSB 01/06/99	PrintVar(40, 3, "Req Vel %.1f ", (FP)(ReqVel * 0.1));

#ifdef PRINT_AI_DATA
PrintVar(40, 2, "Unf Vel %.1f ", (FP)(unfriendly->vel * 0.1));
PrintVar(40, 3, "Req Vel %.1f ", (FP)(ReqVel * 0.1));
PrintVar(40, 4, "Act Vel %.1f ", (FP)(vel * 0.1));
PrintVar(40, 5, "Throttl %.0f ", (FP)(fly.thrustpercent));
#endif

			if(ReqVel > vel)						//CSB 27/05/99	
			{
				thrust = ThrustfromFF();	//CSB 27/05/99	
				if(TooClose) 
		 		   ACM.SpeedBrakesIn();
			}
			else									//CSB 27/05/99	
			{
				thrust = 0;				//CSB 27/05/99	
				if(Range < IDEALCOMBATRANGE / 2) 
		 		   ACM.SpeedBrakesOut();
			}
		}
	}

	ACM.Thrust (thrust);

//DeadCode CSB 27/05/99			FP	velc = (vel - unfriendly->vel)/10.0;
//DeadCode CSB 27/05/99			if	(	(vel > ReqVel)
//DeadCode CSB 27/05/99				)
//DeadCode CSB 27/05/99				SlowDown(velc/2);
//DeadCode CSB 27/05/99			else
//DeadCode CSB 27/05/99				SpeedUp(velc/2);
}

		
void	AirStruc::TurnFightTargetNotOnNose(SWord	reqdeltahdg, SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos, ANGLES	deltapitch)
{


//roll = arccos (1/(g * cos pitch)
//arccos x = arctan (sqr(1-x^2)/x^2)

 	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	SWord delta;
	SWord dpitch;

//	if (reqdeltahdg > 0)
//		reqroll = -1;
//	else
//		reqroll = 1;

//DEADCODE RDH 23/02/99 	SWord PI = PitchIntercept;
//DeadCode RDH 03Dec98 	if  (		(PI < 0)
//DeadCode RDH 03Dec98 			&&	(Range > WEAPONSRANGE)
//DeadCode RDH 03Dec98 		)
//DeadCode RDH 03Dec98 		PI = 0;
//DEADCODE RDH 23/02/99 	delta = PI + deltapitch;
//DeadCode RDH 03Dec98 	if  (		(delta < ANGLES_0Deg)
//DeadCode RDH 03Dec98 			&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
//DeadCode RDH 03Dec98 			&&	(deltapitch << ANGLES_180Deg)				//if he really wants to go down then let him
//DeadCode RDH 03Dec98 			&&	(		(Range > WEAPONSRANGE)
//DeadCode RDH 03Dec98 					||	(classtype->visible == MIG15)
//DeadCode RDH 03Dec98 						
//DeadCode RDH 03Dec98 				)
//DeadCode RDH 03Dec98 		)	
//DeadCode RDH 03Dec98 		delta = ANGLES_0Deg;
//DEADCODE RDH 23/02/99 	reqdeltapitch = 	delta - fly.cpitch;
//DEADCODE RDH 23/02/99 	Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
	if (reqdeltapitch_pos > ANGLES_10Deg)
		dpitch = ANGLES_10Deg;
	else
		dpitch = reqdeltapitch_pos;
	if (reqdeltapitch_sign < 0)
		dpitch = - dpitch;
	RollAndPull(reqdeltahdg,dpitch);

	
	
	
}
void	AirStruc::RollAndPull(SWord	reqdeltahdg, SWord dpitch)
{
	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	
	SWord reqroll;

	if (reqdeltahdg > 0)
		reqroll = -1;
	else
		reqroll = 1;

	SWord c,s;
	Math_Lib.high_sin_cos(fly.cpitch,s,c);
	FP x, r;
	FP g = MOD.Inst.NormalAcc;
	if (g < 1)
		g = 1;
	FP	gmodifier = dpitch;
		gmodifier = 1 + gmodifier/ANGLES_10Deg;
	x = gmodifier/(g * c / 32768);
	if (x > 1)
		x = 1;
	if (x < -1)
		x = -1;
	x = FSqrt((1-x*x)/(x*x));
	r = FPATan (x,1);
	if (r < 0.5)
		r = 0.5;

	if (reqroll > 0)
		reqroll = Rads2Rowan(r);
	else
		reqroll = -Rads2Rowan(r);

#ifdef PRINT_AI_DATA
	PrintVar(60, 11, "R Roll %.1f", (FP)(reqroll/182.04));
#endif

 	if (		(ai.manoeuvre != MANOEUVRE_SPLITMANOEUVRE)
			&&	(BanditOnColdSide())
		)
	//smart fighter realises that bandit has gone cold side in a turning fight: Don't reverse
 		if (	(Range < DANGERRANGE)	&& (ai.combatskill > SKILL_REGULAR))
 				reqroll = -reqroll;

	ACM.Roll ((Angles)reqroll);
	ACM.ZeroSpecificPower();
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
void	AirStruc::TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target)
{
	ACMMODEL& ACM = *fly.pAcmModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Clear ();
			SetManoeuvreTime (1000);
			ACM.maxdeltaforclosework = 0.0;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			TurnFightPhase1(HdgIntercept, sitbehindtarget, deltapitch, target);
		}
	}

}

void	AirStruc::TurnFightPhase1(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target)
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
	Float desiredturn;
	SLong		time;

		reqdeltahdg = 	hdg - HdgIntercept;		//Are You Sure ????	//CSB

//			ACM.MinHeight (FT_2000);
 			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

//DeadCode CSB 10/03/99				reqdeltapitch = PitchIntercept - fly.cpitch;
			reqdeltapitch = PitchIntercept - pitch;
			Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);

			ANGLES delta = unfriendly->hdg + ANGLES_180Deg + ANGLES_30Deg - hdg;

			if	(SubjectFacingTarget(ANGLES_45Deg))
			{
				if	(	(delta << ANGLES_60Deg)
						&&	(Range > DANGERRANGE)
						&&	(reqdeltapitch_pos << ANGLES_15Deg)
						&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
					)
				{
						if  (		(FlyingFactor() < 160)
								||	(classtype->aerobaticfactor < AEROBATIC_FIGHTER)
							)
							ai.manoeuvre = MANOEUVRE_HEADON;
						else
							ai.manoeuvre = MANOEUVRE_HEADONOFFSET;
						ai.ManStep = PHASE0;
				}
				if	(		( Range > WEAPONSRANGE)
						&&	(ai.manoeuvre !=  MANOEUVRE_LOWYOYO)
						&&  (ai.combatskill >= SKILL_VETERAN)
						&&	(ClosureLessThan(MPH15))
						&&	(SubjectOnTargetTail(ANGLES_45Deg))
						&&	(AboveGround(FT_1000))
						&&	((World.Y - ai.unfriendly->World.Y) < FT_100)
						&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
					)
				{
					ai.ManStep = PHASE0;
					ai.manoeuvre = MANOEUVRE_LOWYOYO;
				}
			}
			if  (		(PitchIntercept >> ANGLES_180Deg)
					&&	(PitchIntercept << ANGLES_340Deg)
					&&	((World.Y - ai.unfriendly->World.Y) > FT_3000)
					&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
				)
			{
				ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
			}

#ifdef PRINT_AI_DATA
PrintString(0, 18, "                    ");	//CSB 05/03/99
PrintString(0, 19, "                    ");	//CSB 05/03/99
PrintString(0, 20, "                    ");	//CSB 05/03/99
PrintString(0, 21, "                    ");	//CSB 05/03/99
#endif

			{
				if (sitbehindtarget)
					SlowDownCheck(reqdeltahdg_pos);
	
				if  (		(		(reqdeltahdg_pos < ANGLES_40Deg)
							&&	(ACM.maxdeltaforclosework == 0.0)
							)
						||
							(		(reqdeltahdg_pos < ANGLES_45Deg)
								&&	(ACM.maxdeltaforclosework != 0.0)
							)
					)
				{
#ifdef PRINT_AI_DATA
	PrintString(0, 18, "Lift Line Calc");
#endif

					SWord reqroll = RollforTurn(reqdeltapitch, reqdeltahdg, desiredturn, target);
					ai.flatturn = FALSE;
					ACM.Roll ((Angles)reqroll);
				}else
				{
					ACM.maxdeltaforclosework = 0.0;
					SWord rollpos = roll;
					if (rollpos < 0)
						rollpos = -rollpos;
					
//					FP	factor = 0.2 + 0.0000916 * (ANGLES_60Deg - rollpos);	//0.75 / ANGLES_60Deg
					{
						if (!ai.flatturn) 
							fly.pAcmModel->ZeroIntControl();
						ai.flatturn = TRUE;
						TurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, deltapitch);
						ACM.SetRudder(0);
					}

				}
				if  (		(!ManoeuvreTimeLeft())
					)
				{
					
					if (		(Range > ENGAGERANGE)
							&&	(		(ai.firsttactic == TACTIC_LINEABREAST)
									||	(ai.firsttactic == TACTIC_LINEASTERN)
								)
						)
					{
						ai.ManStep = PHASE0;
						if (ai.firsttactic == TACTIC_LINEASTERN)
							ai.manoeuvre = MANOEUVRE_LINEASTERN;
						else
							ai.manoeuvre = MANOEUVRE_LINEABREAST;
					}else
					{
						if	(ACM.maxdeltaforclosework > 0.1)
							ai.manoeuvre = MANOEUVRE_SELECT;
						else 
						{
							if (		(fly.leadflight)					
									&&	 (fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER)
								)//force manoeuvre to allow disengage
								ai.manoeuvre = MANOEUVRE_SELECT;
							else
							{//on tail of target so keep in manoeuvre and up morale

								AirStruc* unf			= (AirStruc*)ai.unfriendly;
								AirStruc* unfbuddy	= unf->FindBuddy();
								if (		(unfbuddy)
										&&	(unf == Persons2::PlayerGhostAC)
										&&	(Range > DANGERRANGE)
										&&	(Range < ENGAGERANGE)
									)
								{
								 	RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);	
									if	((rndpc > RND50PC)	&&	(Range < VISIBLERANGE))
											_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BANDIT_RELPOS, MSG_MIGSCOMING_RPT, unfbuddy, this, unf));
								}
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


Float	AirStruc::Model_InstTurnRate(AirStrucPtr subject)
{//return tr in rads per cs, dhdg in rowans
	FP tr, tr2;


	if (!subject)
		return 0.0;

	tr = subject->fly.dhdg * 0.00009587	/ Timer_Code.FRAMETIME;					

//	if (subject == Persons2::PlayerGhostAC)
//		subject = Manual_Pilot.ControlledAC2;
 //	tr = ((((SWord)subject->hdg)* 0.00009587) - 
 //				AngleSign (subject->fly.LastfHdg)) / Timer_Code.FRAMETIME;
//	FP test;
//	test = tr - tr2;
//	if (abs(test) > 0.0001)
//		test = -test ;

	return(tr);
}


void	AirStruc::CalcLead(AirStrucPtr  subject, AirStrucPtr target, SLong& deltax,SLong& deltay,SLong& deltaz, Bool cutcorner)
{
//	MODEL& TARGETMOD = *(target->fly).pModel;	
	Float time, shoottime, closuretime;
	Float dhdg;
	SWord c,s;
	SWord newhdg;
	SLong	closure;
	SLong dx,dy,dz;

	deltax = 0;
	deltay = 0;
	deltaz = 0;



//al times in 1/10 s
SLong	const	PUREPURSUITRANGE = METRES700;	
SLong	const	DLEADRANGE = PUREPURSUITRANGE - WEAPONSRANGE;
SLong	const	LAGRANGE = METRES2500;
SLong	const	DLAGRANGE = LAGRANGE - PUREPURSUITRANGE;
//DeadCode AMM 19Apr99 #pragma warnmsg("Craig - check that this is not ghostac i.e. NULL flight model")
//DeadCode AMM 13Apr99 	PMODEL pModel = subject->fly.pModel;

//DeadCode CSB 11/03/99		shoottime = Range / (vel + subject->classtype->muzzlevel);		//MUZZELVEL;
	FP targetvelx = target->velx;//10 * ((FP)target->World.X - (FP)ai.oldoldoldufposx) / (3 * (FP)Timer_Code.FRAMETIME);
	FP targetvely = target->vely;//10 * ((FP)target->World.Y - (FP)ai.oldoldoldufposy) / (3 * (FP)Timer_Code.FRAMETIME);
	FP targetvelz = target->velz;//10 * ((FP)target->World.Z - (FP)ai.oldoldoldufposz) / (3 * (FP)Timer_Code.FRAMETIME);

//DeadCode AMM 13Apr99 	if (!pModel)												//AMM 09Apr99
//DeadCode AMM 13Apr99 		pModel=Persons2::PlayerSeenAC->fly.pModel;				//AMM 09Apr99
//DeadCode AMM 13Apr99 
 	FP VelComp;
//DeadCode AMM 13Apr99 	if((pModel->Controlled) || (pModel->bACM))
//DeadCode AMM 13Apr99 		VelComp = pModel->Ori.z.x * targetvelx + pModel->Ori.z.y * targetvely + pModel->Ori.z.z * targetvelz;
//DeadCode AMM 13Apr99 	else
		VelComp = (subject->velx * targetvelx + subject->vely * targetvely + subject->velz * targetvelz) / subject->vel;
	shoottime = (FP)Range / ((FP)vel - VelComp + (FP)subject->classtype->muzzlevel);	//CSB 05/03/99

//DeadCode CSB 11/03/99		deltax = targetvelx * shoottime;
//DeadCode CSB 11/03/99		deltay = targetvely * shoottime;
//DeadCode CSB 11/03/99		deltaz = targetvelz * shoottime;
//DeadCode CSB 11/03/99	return;
//	shoottime = (Range  + (shoottime *  target->vel))/ (subject->classtype->muzzlevel);		//MUZZELVEL;

	ANGLES VelHdg  = Math_Lib.HighArcTan((SLong)targetvelx, (SLong)targetvelz);
	FP	   VelHori = FSqrt(targetvelx * targetvelx + targetvelz * targetvelz);
	FP tr = Model_InstTurnRate(target);	//rads/cs
	dhdg = (Float)(Rads2Rowan (tr * shoottime * 5) );		//10/2: 2 to get ave
	if (dhdg > ANGLES_30Deg)
		dhdg = ANGLES_30Deg;
	if (dhdg < -ANGLES_30Deg)
		dhdg = -ANGLES_30Deg;
//DeadCode CSB 11/03/99		newhdg = dhdg + target->hdg;
	newhdg = (SWord)VelHdg + dhdg;

	Math_Lib.high_sin_cos((Angles)newhdg,s,c);
//DeadCode CSB 11/03/99		dx = MULSHSIN(s, target->velhori,ANGLES_SHIFT);
//DeadCode CSB 11/03/99		dz = MULSHSIN(c, target->velhori,ANGLES_SHIFT);
	dx = MULSHSIN(s, VelHori,ANGLES_SHIFT);
	dz = MULSHSIN(c, VelHori,ANGLES_SHIFT);

	if (Range < PUREPURSUITRANGE)
	{
		deltax = dx * shoottime;
		deltaz = dz * shoottime;
//DeadCode CSB 11/03/99			deltay = target->vely * shoottime;
		deltay = targetvely * shoottime;
		//lift nose to account for bullet drop
		//delta = 0.5 * g * t^2
		//g = 10 cm/ts/ts
		deltay = deltay + 5 * shoottime * shoottime;

		Float dr = Range - WEAPONSRANGE;
		if (dr > 0)
		{
			deltax = deltax * (1-dr/DLEADRANGE);
			deltay = deltay * (1-dr/DLEADRANGE);
			deltaz = deltaz * (1-dr/DLEADRANGE);
		}
	}

	FP	range;

#ifdef PRINT_AI_DATA
	PrintString(0, 17, "          ");
#endif

	if (cutcorner)
	{
		closure = vel - target->vel- MPH10;
		if ((closure ) < 0)
		{
			if (Range > INSIDEWEAPONSRANGE)
			{
#ifdef PRINT_AI_DATA
	PrintString(0, 17, "Cut Corner");
#endif
			
				if (Range > LAGRANGE)
					Range = LAGRANGE;

				dhdg = ANGLES_30Deg * (Range - INSIDEWEAPONSRANGE)/(LAGRANGE - INSIDEWEAPONSRANGE);
				if (tr < 0 )
					dhdg = -dhdg;
				newhdg = dhdg + target->hdg;
	
				Math_Lib.high_sin_cos((Angles)newhdg,s,c);
				SLong	cornerdeltax = (20 * MULSHSIN(s, target->velhori,ANGLES_SHIFT));
				SLong	cornerdeltaz = ( 20 *MULSHSIN(c, target->velhori,ANGLES_SHIFT));
				SLong	cornerdeltay = target->vely * 20;

				if (closure < -MPH100)
					closure = -MPH100;
				cornerdeltax = cornerdeltax * -closure/MPH100;
				cornerdeltaz = cornerdeltaz * -closure/MPH100;
				cornerdeltay = cornerdeltay * -closure/MPH100;

				deltax += cornerdeltax;
				deltay += cornerdeltay;
				deltaz += cornerdeltaz;


			}
		}
	}
}


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
void	AirStruc::TurningFight()
{
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	COORDS3D	target;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	SLong vx = 0, vy = 0, vz = 0;

	reqdeltahdg = 	hdg - HdgIntercept;
	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

	

//	if (		(Range < (DANGERRANGE + METRES200))
//	if (		(Range < (COMBATRANGE+ METRES400))
//			&&	(reqdeltahdg_pos < (SWord)ANGLES_30Deg)
//			&&	(reqdeltahdg_pos < (SWord)ANGLES_60Deg)
//		)		

#ifdef PRINT_AI_DATA
	PrintString(0, 15, "Target Tracking");
	PrintString(0, 16, "               ");
#endif

	if (	(reqdeltahdg_pos < (SWord)ANGLES_90Deg)
		)		
	{
#ifdef PRINT_AI_DATA
	PrintString(0, 15, "               ");
	PrintString(0, 16, "Lead Tracking  ");
#endif

		target.X = ai.unfriendly->World.X;
		target.Y = ai.unfriendly->World.Y;
		target.Z = ai.unfriendly->World.Z;
		InterceptandRange (&target);

		CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);

		target.X += vx;
		target.Y += vy;
		target.Z += vz;
		InterceptandRange (&target);

	}else
		target = ai.unfriendly->World;
	if (		(classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 	if (		(classtype->visible == MIG15)
//			&&	(		(ai.combatskill >= SKILL_ACE)
//					||	(ai.morale < MORALE_GOOD)
			&&	(		(ai.morale < MORALE_GOOD)
				)
		)
		TurnWithPitchChange(HdgIntercept, FALSE, target);
	else
		TurnWithPitchChange(HdgIntercept, TRUE, target);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
void	AirStruc::TurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget,COORDS3D	target)
{
	if (CombatFactor() > 200)
	{
		if (classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 		if (classtype->visible == MIG15)
//			TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_5Deg, target);	
			TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	
		else if (World.Y > FT_10000)
			TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	
		else
			TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	

	}else
		TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);

}
Bool	AirStruc::BanditOnColdSide()
{
	SWord reqdeltahdg = hdg - HdgIntercept;

	if	(		(reqdeltahdg < ANGLES_90Deg)
			||	(reqdeltahdg > ANGLES_270Deg)
		)	
	{
		return (FALSE);
	}

	if	(	(		(reqdeltahdg > 0)
				&&	(roll << ANGLES_90Deg)
			)
			||
			(		(reqdeltahdg < 0)
				&&	(roll >> ANGLES_270Deg)
			)
		)
		return(TRUE);
	else
		return(FALSE);

}
Bool	AirStruc::BanditHasLead()
{
	return(TRUE);
}
//
//DeadCode RDH 07Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 07Jan99 //Procedure		SustainedTurn
//DeadCode RDH 07Jan99 //Author		R. Hyde 
//DeadCode RDH 07Jan99 //Date			Fri 13 Mar 1998
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Description	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Inputs		
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Returns	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 07Jan99 void	AirStruc::SustainedTurn()
//DeadCode RDH 07Jan99 {
//DeadCode RDH 07Jan99 //done in turning fight
//DeadCode RDH 07Jan99 }
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
void	AirStruc::HighYoYo()
{
//approach from 30-60 AOT, cospeed
//
//roll wings level
//pull up
//when in rear hemisphere (say near 6 o'clock), closure 0
//	roll towards target then lead or lag pursuit
//
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust (100);
			SetManoeuvreTime (1500);
 			ai.desiredroll = ANGLES_0Deg; 
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll (ai.desiredroll);
			ACM.Pitch (ANGLES_20Deg);

			if  ( !ManoeuvreTimeLeft())
  				ai.manoeuvre = MANOEUVRE_SELECT;

		 	SWord 	deltaroll;
		 	UWord	deltaroll_pos;
 			SWord	deltaroll_sign;

			deltaroll = (SWord) (ai.desiredroll - roll);
  			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
  			if (		(deltaroll_pos <ANGLES_5Deg)
					&&	((World.Y - ai.unfriendly->World.Y) > FT_100)
				)
 				ai.ManStep = PHASE2;

			break;

		}
		case PHASE2:
		{
			COORDS3D	target;
			Float fpitch,fhdg;
			AirStrucPtr	unfriendly = *ai.unfriendly;
			target = ai.unfriendly->World;


			ANGLES reqroll = roll +  GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
			ACM.Roll (reqroll);
			ACM.Pitch (ANGLES_20Deg);

			if (TargetOnSubjectTail(ANGLES_85Deg))
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = PHASE0;
			}
		}
	}


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
void	AirStruc::Zoom()
{
//roll wings nearly level
//pull up then zoom climb for x secs or near stall
//roll 180 and pull level
//
//
		ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

//	ACM.Step = ai.ManStep;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (2000);
			MOD.Rudder = 0;

			ACM.Thrust (100);			//rdh
//			ACM.ClimbRate (0);
//			ACM.KeepWingsLevel ();

			ai.ManStep = PHASE1;
			break;
		}
		case PHASE1:
		{
				ACM.Roll (ANGLES_0Deg);
				ACM.Pitch (ANGLES_40Deg);
			

			if  (		(!ManoeuvreTimeLeft ())
					||
						(vel <= CornerSpeed())
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
void	AirStruc::LowYoYo ( )
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
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	COORDS3D	target;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	SLong		time;
	SWord	reqdeltapitch,reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;
	SLong dx;
	SLong dy;
	SLong dz;




	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;

			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			CalcLead(*this, *ai.unfriendly,dx,dy,dz, TRUE);
		
			target.X = ai.unfriendly->World.X + dx;
			target.Y = ai.unfriendly->World.Y + dy;
			target.Z = ai.unfriendly->World.Z + dz;

			SWord c,s;
			ANGLES	depression = ANGLES_340Deg;
			Math_Lib.high_sin_cos(depression,s,c);
			SLong deltay = MULSHSIN(s, Range,ANGLES_SHIFT);
			SLong range = Range - WEAPONSRANGE;
			if (range < 0)
				range = 0;
			if (range > ENGAGERANGE)
				range = ENGAGERANGE;
			deltay = deltay * range /ENGAGERANGE;
			target.Y += deltay;
//			depression = ANGLES_0Deg;

			InterceptandRange (&target);

//DeadCode RDH 16Dec98 			TurnFightSub(HdgIntercept, TRUE, ANGLES_0Deg, target);	
			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);

//			ACM.MinHeight (FT_2000);
//DEADCODE RDH 27/05/99 			if (TooLow())
//DEADCODE RDH 27/05/99 				{
//DEADCODE RDH 27/05/99 					ai.ManStep = PHASE0;
//DEADCODE RDH 27/05/99 					ai.manoeuvre = MANOEUVRE_LOWALT;
//DEADCODE RDH 27/05/99 				}

			if  (!ManoeuvreTimeLeft())
			{
				if (Range > INSIDEWEAPONSRANGE)
				{
					if (		(Math_Lib.rnd(2))
							&&	(vel > unfriendly->vel)
						)
						ai.ManStep = PHASE0;
					else
						ai.manoeuvre = MANOEUVRE_SELECT;
				}else
				{
					 ai.manoeuvre = MANOEUVRE_SELECT;
				}

			}
		}
	}

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
void	AirStruc::InterceptHigh()
{
//intercept but stay at alt
//
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	COORDS3D	target;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	SLong		time;
	SWord	reqdeltapitch,reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;
	SLong dx;
	SLong dy;
	SLong dz;




	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;

			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (15000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			CalcLead(*this, *ai.unfriendly,dx,dy,dz, TRUE);
		
			target.X = ai.unfriendly->World.X + dx;
			target.Y = World.Y;
			target.Z = ai.unfriendly->World.Z + dz;


			InterceptandRange (&target);

			SLong deltaalt = World.Y - ai.unfriendly->World.Y;
			if (deltaalt < 0)
				ai.manoeuvre = MANOEUVRE_SELECT;
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
	
			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);

			if  (		((Range - deltaalt ) < DANGERRANGE)
					&&	 (SubjectOnTargetTail(ANGLES_45Deg))
					&&	(SubjectFacingTarget(ANGLES_45Deg))
				)
			{
				 ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
			}

		}
	}


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
void	AirStruc::ClimbAtSustainedTurnSpeed()
{
//climb but don't go below sustained turn speed
//aim towards unfriendly plus offset = f(desiredrange,desiredhdg)


//very similar to gainheight at present
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			SetManoeuvreTime (2000);
			ACM.GearUp ();
			ACM.Thrust (ThrustfromFF());
			if (ai.combatskill > SKILL_REGULAR)
			{
				SWord	reqdeltahdg;
				reqdeltahdg = 	hdg - HdgIntercept;
				if (reqdeltahdg > 0)
					ai.desiredhdg = HdgIntercept + ANGLES_20Deg;
				else
					ai.desiredhdg = HdgIntercept - ANGLES_20Deg;

			}
			else
				ai.desiredhdg = HdgIntercept;

//			ACM.ClimbRate (-1500);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
//			ACM.SpeedWithElevators(0.61);

			ACM.Roll (ANGLES_0Deg);
	
//			MoveToHdg (ai.desiredhdg);


			if (MOD.Inst.MachNo > 0.55)
				ACM.Pitch (BestClimbAngle());
			else
				ACM.Pitch (ANGLES_355Deg);
//			if (MOD.Inst.MachNo < 0.4)
//			if (vel <= SustainedTurnSpeed())
//				ACM.Pitch (ANGLES_355Deg);
//			else
//				ACM.Pitch (ANGLES_5Deg);


			if (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpinRecovery
//Author		R. Hyde 
//Date			Wed 21 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SpinRecovery ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	FP rotvelymod;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust (100);

			SetManoeuvreTime (200);

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			MOD.Elevator = 0;
			MOD.Aileron = 0;
			if (MOD.RotVel.y > 0)
			{
				MOD.Rudder = +MAXRUDDER;
			}else
			{
				MOD.Rudder = -MAXRUDDER;
			}

			MOD.RotVel.y = 0.95 * MOD.RotVel.y;
			rotvelymod =  MOD.RotVel.y;
			if (rotvelymod < 0)
				rotvelymod = - rotvelymod;

			if  (rotvelymod < 0.0005)
				ai.ManStep = PHASE2;
			break;
				
		}
		case PHASE2:
		{
			MOD.Rudder = 0;
			MOD.RotVel.y = MOD.RotVel.y/2;		//at this stage we want spin to definitely stop
			rotvelymod =  MOD.RotVel.y;
			if (rotvelymod < 0)
				rotvelymod = - rotvelymod;
			if  (rotvelymod > 0.0005)
				ai.ManStep = PHASE1;
			ACM.Roll (ANGLES_0Deg);
			ACM.Pitch (ANGLES_5Deg + pitch);
			if (	(pitch >> ANGLES_340Deg)
					||
					(pitch << ANGLES_90Deg)
				)
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

}

//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		BounceFollower
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Tue 10 Sep 1996
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void AirStruc::BounceFollower()
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	{
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		{
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			break;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		}
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		{
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			{
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			}
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			target.X = follower->World.X;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			target.Y = follower->World.Y;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			target.Z = follower->World.Z;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			TightTurnSub (FT_1000,target);
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			break;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		}
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	}
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GainSpeed()
//Author		R. Hyde 
//Date			Tue 10 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::GainSpeed()
{


	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

//	ACM.Step = ai.ManStep;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			SWord reqdeltahdg = 	hdg - HdgIntercept;
			ACM.Thrust (ThrustfromFF());
			if (reqdeltahdg > 0)
				ai.desiredroll = ANGLES_330Deg;
			else
				ai.desiredroll = ANGLES_30Deg;

			SetManoeuvreTime (2000);
			ACM.GearUp ();
			ACM.Thrust (ThrustfromFF());
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if (classtype->phrasename == PHRASE_MIGS)
//DEADCODE RDH 10/05/99 			if (classtype->visible == MIG15)
				ACM.Pitch (ANGLES_3Deg);
			else
				ACM.Pitch (ANGLES_355Deg);
			ACM.Roll (ai.desiredroll);

			if (!ManoeuvreTimeLeft())
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
void	AirStruc::LeadUnFriendly ()
{
	ACMMODEL& ACM = *fly.pAcmModel;

 	COORDS3D	target;
 	SLong		t,actualrange;
 	AirStrucPtr	unfriendly = *ai.unfriendly;
 
 //			target.X = ai.unfriendly->World.X;
 //			target.Y = ai.unfriendly->World.Y;
 //			target.Z = ai.unfriendly->World.Z;
 //			InterceptandRange (&target);
 			actualrange = Range;
 
 			//clofg velocity
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
//DeadCode RDH 16Dec98 //			TurnFightSubWithManStep(HdgIntercept, TRUE, ANGLES_0Deg, target);	
//DeadCode RDH 16Dec98 			ai.ManStep = PHASE1;
//DeadCode RDH 16Dec98 			TurnWithPitchChange(HdgIntercept, TRUE,target);
//DeadCode RDH 16Dec98 			if (ai.ManStep == PHASE1)
//DeadCode RDH 16Dec98 				ai.ManStep = PHASE2;
			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);

// 			ACM.Pitch (PitchIntercept);
//			MoveToHdg (HdgIntercept);
			Range = actualrange;

}
//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		GatherSpeed
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Fri 15 Mar 1996
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void	AirStruc::GatherSpeed ()
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99  	COORDS3D	target;
//DeadCode RDH 05Jan99  
//DeadCode RDH 05Jan99 // 		target.X = ai.unfriendly->World.X;
//DeadCode RDH 05Jan99  //		target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 05Jan99  //		target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 05Jan99  //		InterceptandRange (&target);
//DeadCode RDH 05Jan99  		ACM.Pitch (ANGLES_340Deg);
//DeadCode RDH 05Jan99   		MoveToHdg (HdgIntercept);
//DeadCode RDH 05Jan99 }
//DeadCode RDH 05Jan99 



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllButLdrNotOnCombat
//Author		R. Hyde 
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::AllButLdrNotOnCombat ()

{
	AirStrucPtr		ac,leadac;	
	if (formpos == 0)
	{//leader
		ac = *this;
	}else
	{
		ac = fly.leadflight;
	}
	leadac =ac;
	do
	{
		do
		{
			if  (	(ac->movecode==AUTO_COMBAT)
				&&  (	(ac->ai.manoeuvre != MANOEUVRE_TOPCOVER)
					&&	(ac->ai.manoeuvre != MANOEUVRE_LOOKROUND)
					&&	(ac->ai.manoeuvre != MANOEUVRE_DIVEFORHOME)	
					&&	(ac->ai.manoeuvre != MANOEUVRE_CLIMBFORHOME)
					&&	(ac->ai.manoeuvre != MANOEUVRE_STRAIGHTDIVE)
					&&	(ac->ai.manoeuvre != MANOEUVRE_GOHOME )		
					&&	(ac->ai.manoeuvre != MANOEUVRE_WELDEDWINGMAN )		//rdh 25/6/99
					)
				&&
					(formpos != 0)
				)
				return (FALSE);
			ac = *ac->Follower();
		}
		while (ac);
	leadac = *leadac->fly.nextflight;
	ac = leadac;
	}
	while (leadac);
	return (TRUE);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllOnTopCover
//Author		R. Hyde 
//Date			Mon 19 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::AllOnTopCover ()

{
	AirStrucPtr		ac,leadac;	
	if (formpos == 0)
	{//leader
		ac = *this;
	}else
	{
		ac = fly.leadflight;
	}
	leadac =ac;

	do
	{
		do
		{
			if (	ac->movecode==AUTO_COMBAT
				&&	ac->ai.manoeuvre != MANOEUVRE_TOPCOVER
				&&  (InterceptandRange(ac),Range<METRES4000)
				)
				return (FALSE);
			ac = *ac->Follower();
		}
		while (ac);
	leadac = *leadac->fly.nextflight;
	ac = leadac;
	}
	while (leadac);
	return (TRUE);

}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbAtBestSpeed
//Author		R. Hyde 
//Date			Mon 18 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::ClimbAtBestSpeed ()
{
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_10Deg,2);

}

//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		TightClimbingTurn
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Sat 30 Mar 1996
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void	AirStruc::TightClimbingTurn (ANGLES desiredpitch)
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		deltapitch = desiredpitch - fly.cpitch;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		PitchIntercept = desiredpitch; 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		TightTurnSubSub (deltapitch);
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 }
//DeadCode RDH 05Jan99 


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoShoot
//Author		R. Hyde 
//Date			Fri 12 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AutoShoot (Bool manual)
{

//DeadCode CSB 28/04/99	PrintString(60, 19, "                ");
//DeadCode CSB 28/04/99	PrintString(60, 20, "                ");
//DeadCode CSB 28/04/99	PrintString(60, 21, "                ");
	const	int TARGETSIZE = 400;		//METRES02_50;		//wingspan = 40ft, we want less
	COORDS3D	target;
	Float		time;
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
 	SWord		reqdeltapitch;
	UWord	reqdeltapitch_pos;
	SWord	reqdeltapitch_sign;
	AirStrucPtr	unfriendly = *ai.unfriendly;



	reqdeltahdg = 	hdg - HdgIntercept;
	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
	if  (		(Range < INSIDEWEAPONSRANGE)
//	if  (		(Range < METRES300)
			&&	(reqdeltahdg_pos < ANGLES_70Deg)
		)
	{
		target.X = ai.unfriendly->World.X;
		target.Y = ai.unfriendly->World.Y;
		target.Z = ai.unfriendly->World.Z;
		InterceptandRange (&target);

//		time = Range / classtype->muzzlevel;		//MUZZELVEL;
//		//calc lead position using this time
//		Float velx = unfriendly->velx * time;
//		Float vely = unfriendly->vely * time;
//		Float velz = unfriendly->velz * time;

		SLong vx;
		SLong vy;
		SLong vz;

//#ifndef PRINT_AI_DATA
//#define PRINT_AI_DATA
//#endif

#ifdef PRINT_AI_DATA
	PrintString(0, 3, "                    ");
	PrintString(0, 4, "                    ");
	PrintString(0, 5, "                    ");
#endif

		CalcLead(*this, *ai.unfriendly,vx,vy,vz, FALSE);

		target.X = ai.unfriendly->World.X + vx;
		target.Y = ai.unfriendly->World.Y + vy;
		target.Z = ai.unfriendly->World.Z + vz;
		InterceptandRange (&target);

		reqdeltahdg = 	hdg - HdgIntercept;

		Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
		if (reqdeltahdg_pos < ANGLES_10Deg)
		{
			reqdeltapitch = PitchIntercept - pitch;
			Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
			if (reqdeltapitch_pos < ANGLES_10Deg)
			{
#ifdef PRINT_AI_DATA
	PrintVar(0,  3, "T Pitch %.1f ", (FP)( (PitchIntercept - pitch) / 182.04) );
	PrintVar(0,  4, "T Headg %.1f ", (FP)( (HdgIntercept - hdg)  / 182.04) );
	PrintVar(0,  5, "T Range %.1f ", (FP)( (Range)  / 100.0) );
#endif
//DeadCode CSB 09/03/99	PrintVar(0, 13, "AS Pitch %.1f ", (FP)Rowan2Rads(reqdeltapitch));
//DeadCode CSB 09/03/99	PrintVar(0, 14, "AS Headg %.1f ", (FP)Rowan2Rads(reqdeltahdg));

//DeadCode CSB 04/06/99					if (reqdeltahdg_pos  < reqdeltapitch_pos)
//DeadCode CSB 04/06/99						reqdeltahdg_pos = reqdeltapitch_pos;
//DeadCode CSB 04/06/99					Float  delta = Range * Math_Lib.hightan ((Angles)reqdeltahdg_pos)/65536;

				SWord AngError = reqdeltahdg_pos;	//CSB 04/06/99	
				if (reqdeltahdg_pos  < reqdeltapitch_pos)
					AngError = reqdeltapitch_pos;
				Float delta = (Range * AngError) / 10431;	//CSB 04/06/99	
#ifdef PRINT_AI_DATA
	PrintVar(0, 7, "T Delta %.2f ", (FP)(delta / 100));
#endif
//DeadCode CSB 13/06/99		PrintVar(60, 0, "T Delta %.2f ", (FP)(delta / 100));	//Fix This !!!!
				UByte	FF = FlyingFactor();
//				int		target = TARGETSIZE/4 + 3*TARGETSIZE*(256-FF)/1024;
				int		target = TARGETSIZE/2 + TARGETSIZE*(256-FF)/512;
				
//DeadCode CSB 14/04/99					if  (	(delta < 50)	//CSB 10/03/99
//DeadCode CSB 14/04/99							||
//DeadCode CSB 14/04/99							(		(delta < target)
//DeadCode CSB 14/04/99								&&	(delta > ai.lastdelta)
//DeadCode CSB 14/04/99							)
//DeadCode CSB 14/04/99							||
//DeadCode CSB 14/04/99							(		(delta == 0)
//DeadCode CSB 14/04/99								&&	(Range < METRES300)
//DeadCode CSB 14/04/99							)
//DeadCode CSB 14/04/99							||
//DeadCode CSB 14/04/99							(		(delta < target)
//DeadCode CSB 14/04/99								&&	(delta >= ai.lastdelta)
//DeadCode CSB 14/04/99								&&	(Range < METRES250)
//DeadCode CSB 14/04/99							)
//DeadCode CSB 14/04/99							||
//DeadCode CSB 14/04/99							(		(delta < target)
//DeadCode CSB 14/04/99								&&	(delta >= (ai.lastdelta - 2))
//DeadCode CSB 14/04/99								&&	(Range < METRES150)
//DeadCode CSB 14/04/99							)
//DeadCode CSB 14/04/99						)

//DeadCode CSB 01/07/99					if((delta < 1000 - 2 * FF))// || ((reqdeltahdg_pos < ANGLES_5Deg) && (reqdeltapitch_pos < ANGLES_5Deg))	//CSB 14/04/99		//Fix This !!!!
				if((delta < 1000))// || ((reqdeltahdg_pos < ANGLES_5Deg) && (reqdeltapitch_pos < ANGLES_5Deg))	//CSB 14/04/99		//Fix This !!!!

				{
/* TEST CODE CSB 03/06/99 */
/* TEST CODE CSB 03/06/99 */					
/* TEST CODE CSB 03/06/99 */					
//DeadCode CSB 03/06/99						static int F86Shots = 0;
//DeadCode CSB 03/06/99						static int MiGShots = 0;
//DeadCode CSB 03/06/99						if((fly.pModel->Type == AT_MIG15) || (fly.pModel->Type == AT_MIG15BIS))
//DeadCode CSB 03/06/99						{
//DeadCode CSB 03/06/99							if(ai.unfriendly != Persons2::PlayerGhostAC)
//DeadCode CSB 03/06/99							{
//DeadCode CSB 03/06/99								MiGShots++;
//DeadCode CSB 03/06/99								PrintVar(60, 0, "MiG Shots %.0f ", FP(MiGShots));
//DeadCode CSB 03/06/99							}
//DeadCode CSB 03/06/99						}
//DeadCode CSB 03/06/99						else
//DeadCode CSB 03/06/99						{
//DeadCode CSB 03/06/99							if(ai.unfriendly != Persons2::PlayerGhostAC)
//DeadCode CSB 03/06/99							{
//DeadCode CSB 03/06/99								F86Shots++;
//DeadCode CSB 03/06/99								PrintVar(60, 1, "F86 Shots %.0f ", FP(F86Shots));
//DeadCode CSB 03/06/99							}
//DeadCode CSB 03/06/99						}
/* TEST CODE CSB 03/06/99 */
/* TEST CODE CSB 03/06/99 */
/* TEST CODE CSB 03/06/99 */

#ifdef PRINT_AI_DATA
PrintString(60, 19, " @@@@@@@@@@@@@@ ");
PrintString(60, 20, "@@@  FIRING  @@@");
PrintString(60, 21, " @@@@@@@@@@@@@@ ");
#endif
					ANGLES OldPitch = pitch;
					ANGLES OldHdg   = hdg;
//DeadCode CSB 01/06/99						if((classtype->visible == MIG15) || (classtype->visible == CMIG15))
//DeadCode CSB 01/06/99							FF /= 2;
//DeadCode CSB 02/07/99						if(    (AngError < ANGLES_25Deg) //&& (Math_Lib.rnd(256) < FF) 
//DeadCode CSB 02/07/99							&& (classtype->visible != MIG15) && (classtype->visible != CMIG15) )
//DeadCode CSB 02/07/99						{
//DeadCode CSB 14/04/99							fly.pModel->ChangeDirection(*this, Rowan2Rads(reqdeltapitch), Rowan2Rads(reqdeltahdg), 0);
//DeadCode CSB 04/06/99							if((classtype->visible == MIG15) || (classtype->visible == CMIG15))
//DeadCode CSB 04/06/99							{
//DeadCode CSB 04/06/99								PitchIntercept += Math_Lib.rnd(ANGLES_2Deg) - ANGLES_1Deg;
//DeadCode CSB 04/06/99								HdgIntercept   += Math_Lib.rnd(ANGLES_2Deg) - ANGLES_1Deg;
//DeadCode CSB 04/06/99							}
//DeadCode CSB 02/07/99							pitch = PitchIntercept;
//DeadCode CSB 02/07/99							hdg   = HdgIntercept;
//DeadCode CSB 02/07/99						}

					if((classtype->visible == MIG15) || (classtype->visible == CMIG15))
						if(ai.simpleacm)
						{
							pitch += Math_Lib.rnd(ANGLES_10Deg) - ANGLES_5Deg;
							hdg   += Math_Lib.rnd(ANGLES_10Deg) - ANGLES_5Deg;
						}

					FireABullet(150);			
				
					pitch = OldPitch;
					hdg   = OldHdg;
					
					if (ai.unfriendly == Persons2::PlayerGhostAC)
						 _Miles.SequenceAudible(MOOD_DOOMED);
				}else
				{
					if (follower)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SHOOTHIM, MSG_SHOOTHIM, Follower(), NULL, this));

					if (ai.unfriendly == Persons2::PlayerGhostAC)
						 _Miles.SequenceAudible(MOOD_DESPERATE);
				}
//				if	(classtype->visible != MIG15)
//					FireABullet(480);			
				ai.lastdelta = delta;

			}else
			{
				ai.lastdelta = INSIDEWEAPONSRANGE;
				if (ai.unfriendly == Persons2::PlayerGhostAC)
					 _Miles.SequenceAudible(MOOD_TENSE);
			}
		}else
			ai.lastdelta = INSIDEWEAPONSRANGE;
	}else
		ai.lastdelta = INSIDEWEAPONSRANGE;


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PublicFireABullet
//Author		Craig Beeston 
//Date			Sat 3 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::PublicFireABullet(SWord delaybetweenbursts, Bool isArmed)
{
	FireABullet(delaybetweenbursts,isArmed);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FireABullet
//Author		R. Hyde 
//Date			Sat 13 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::FireABullet(SWord delaybetweenbursts, Bool isArmed)
{
	//	SWord	timeleft;
	WeapAnimData*	weapon;										//RJS 29Aug96
	SLong			xpos, ypos, zpos;							//RJS 29Aug96
	UWord			index;										//RJS 03Sep96
	UWord			mvel,mdelay,mburst;							//RDH 31Jul98
	UWord			theShape;									//RDH 31Jul98

//	timeleft = weap.ShootDelay-Timer_Code.FRAMETIME;//DAW 31Jul96
//DeadCode DAW 24Jun99 	Mono_Text.PrintHexAt(60,15,weap.ShootDelay,4);
//	if (timeleft<0)
	if (weap.ShootDelay <=0)
	{
//done by Robert		Art_Int.PersonalThreat(*ai.unfriendly,this);				//RDH 17Oct96
		WorldStuff*	worldptr = mobileitem::currworld;
		SLong			highestammo = 0;						//RJS 08Sep98
		UWord			indexlist[6];							//RJS 08Sep98
		UWord			indexcnt;								//RJS 08Sep98
		WeapAnimData*	useweapon = NULL;								//RJS 08Sep98
		SLong			usexpos, useypos, usezpos;				//RJS 08Sep98
		UWord			usemvel;								//RJS 08Sep98
		UWord			useindex;								//RJS 08Sep98
		UWord			usemdelay;								//RJS 08Sep98
		UWord			usemburst;								//RJS 08Sep98
		UWord			useShape;								//RJS 08Sep98

//DeadCode RJS 07Jul99  		weap.ShootDelay = delaybetweenbursts;			//rdh

 		Trans_Obj.PlayGunSound((mobileitem* )this,*worldptr);//RDH 12Jul96
		theShape = BULLET;										//RJS 20Nov98

		indexcnt = 0;

		// digadigadiga (alternate fire)
		for (index = 0; index < 6; index++)						//RJS 16Jun98
		{
			weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BULLET,&theShape);//RDH 31Jul98
			if (weapon)
			{
				indexlist[indexcnt++] = index;
				if (weapon->LoadedStores > highestammo)
				{
				 	highestammo = weapon->LoadedStores;
					useweapon = weapon;
					usexpos = xpos;
					useypos = ypos;
					usezpos = zpos;
					useindex = index;
					usemdelay = mdelay;
					usemburst = mburst;
					useShape = theShape;
					usemvel = mvel;
				}
//this was insered by maccas changes ?
//so ROD has been editing on macca machine then ??

					if (this==Persons2::PlayerSeenAC)
					{
						_DPlay.NewBullet(mburst,index);					//RDH 31Jul98
					}
			}
		}

		if (useweapon)
		{
			SLong	i;
			SLong	otherindex = useindex;
			for (i=0; i < indexcnt; i++)
			{
				if (indexlist[i] != useindex)
				{
					otherindex = indexlist[i];
					break;
				}
			}
//DeadCode DAW 24Jun99 #ifdef PRINT_AI_DATA
//DeadCode DAW 24Jun99 	PrintVar(20, 14, "Muz Vel %.1f ", (FP)(usemvel / 10) );
//DeadCode DAW 24Jun99 #endif

			SLong	mydelaybetweenbursts = usemburst * usemdelay;	//RJS 07Jul99
			if (mydelaybetweenbursts > delaybetweenbursts)			//RJS 07Jul99
				delaybetweenbursts = mydelaybetweenbursts;			//RJS 07Jul99

			Trans_Obj.LaunchManyGunBullets(	(mobileitem* )this,
		 									usemvel,
		 									usemburst,				// no bullets//RDH 31Jul98
		 									usemdelay,		// delay between each bullet//DAW 29Jul98
		 									useindex,		// left  /  right
		 									otherindex,		// right /  left
		 									(ShapeNum)useShape,	//RJS 08Sep98
		 									usexpos,
		 									useypos,
		 									usezpos,
		 									*worldptr,
		 									ANGLES_0Deg,
											LT_BULLET,
											isArmed);	//RJS 27May99
		 
			useweapon->LoadedStores--;

		 	// store num bullets and index of launcher

			if (this==Persons2::PlayerSeenAC)					//AMM 17Nov98
			{
			 	_DPlay.NewBullet(usemburst,useindex);				//RJS 08Sep98
			}
		}

		weap.ShootDelay = delaybetweenbursts;			//RJS 07Jul99
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FireARocket
//Author		Craig Beeston
//Date			Thu 25 Mar 1999
//
//Description	Just Like Fire a Bullet but for rockets
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::FireARocket(SWord delaybetweenbursts,Bool isArmed)	//RJS 27May99
{
	WeapAnimData*	weapon;										//RJS 29Aug96
	SLong			xpos, ypos, zpos;							//RJS 29Aug96
	UWord			index;										//RJS 03Sep96
	UWord			mvel,mdelay,mburst;							//RDH 31Jul98
	UWord			theShape;									//RDH 31Jul98

	Mono_Text.PrintHexAt(60,15,weap.ShootDelay,4);
	if (weap.ShootDelay <=0)
	{
		WorldStuff*	worldptr = mobileitem::currworld;
		SLong			highestammo = 0;						//RJS 08Sep98
		UWord			indexlist[6];							//RJS 08Sep98
		UWord			indexcnt;								//RJS 08Sep98
		WeapAnimData*	useweapon = 0;								//RJS 08Sep98
		SLong			usexpos, useypos, usezpos;				//RJS 08Sep98
		UWord			usemvel;								//RJS 08Sep98
		UWord			useindex;								//RJS 08Sep98
		UWord			usemdelay;								//RJS 08Sep98
		UWord			usemburst;								//RJS 08Sep98
		UWord			useShape;								//RJS 08Sep98

//DeadCode CSB 25/03/99	 		Trans_Obj.PlayGunSound((mobileitem* )this,*worldptr);//RDH 12Jul96
		theShape = ROCKET;										//RJS 20Nov98

		indexcnt = 0;

		// digadigadiga (alternate fire)
		for (index = 0; index < 6; index++)						//RJS 16Jun98
		{
			weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_ROCKET,&theShape);//RDH 31Jul98	//CSB 25/03/99	
			if (weapon)
			{
				indexlist[indexcnt++] = index;
				if (weapon->LoadedStores > highestammo)
				{
				 	highestammo = weapon->LoadedStores;
					useweapon = weapon;
					usexpos = xpos;
					useypos = ypos;
					usezpos = zpos;
					useindex = index;
					usemdelay = mdelay;
					usemburst = mburst;
					useShape = theShape;
					usemvel = mvel;
				}
//this was insered by maccas changes ?
//so ROD has been editing on macca machine then ??

					if (this==Persons2::PlayerSeenAC)
					{
						_DPlay.NewBullet(mburst,index);					//RDH 31Jul98
					}
			}
		}

		if (useweapon)
		{
			SLong	i;
			SLong	otherindex = useindex;
			for (i=0; i < indexcnt; i++)
			{
				if (indexlist[i] != useindex)
				{
					otherindex = indexlist[i];
					break;
				}
			}
#ifdef PRINT_AI_DATA
	PrintVar(20, 14, "Muz Vel %.1f ", (FP)(usemvel / 10) );
#endif

			WorldStuff*	worldptr = mobileitem::currworld;
			Trans_Obj.LaunchRocket( (mobileitem*)this,
									(ShapeNum)useShape,
									usexpos, 
									useypos,
									usezpos,			  
									*worldptr);
		 	
//DeadCode CSB 25/03/99				Trans_Obj.LaunchManyGunBullets(	(mobileitem* )this,
//DeadCode CSB 25/03/99			 									usemvel,
//DeadCode CSB 25/03/99			 									usemburst,				// no bullets//RDH 31Jul98
//DeadCode CSB 25/03/99			 									usemdelay,		// delay between each bullet//DAW 29Jul98
//DeadCode CSB 25/03/99			 									useindex,		// left  /  right
//DeadCode CSB 25/03/99			 									otherindex,		// right /  left
//DeadCode CSB 25/03/99			 									(ShapeNum)useShape,	//RJS 08Sep98
//DeadCode CSB 25/03/99			 									usexpos,
//DeadCode CSB 25/03/99			 									useypos,
//DeadCode CSB 25/03/99			 									usezpos,
//DeadCode CSB 25/03/99			 									*worldptr,
//DeadCode CSB 25/03/99			 									ANGLES_0Deg);	//RJS 16Jun98
		 
			useweapon->LoadedStores--;
			weap.ShootDelay = usemdelay;
			

			if (this==Persons2::PlayerSeenAC)					//AMM 17Nov98
			{
			 	_DPlay.NewBullet(usemburst,useindex);				//RJS 08Sep98
			}
		}
	}
//	weap.ShootDelay = timeleft;

}
	
//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		TightTurn
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Fri 12 Jul 1996
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void AirStruc::TightTurn (SLong recovery_alt)
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 }




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ManoeuvreTimeLeft
//Author		R. Hyde 
//Date			Tue 19 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord AirStruc::ManoeuvreTimeLeft ()

{
	return(TimeLeft());

}

//------------------------------------------------------------------------------
 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakCallNecessary
//Author		R. Hyde 
//Date			Tue 19 Dec 1995
//
//Description	
//					Horrible code to retain the globals
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool AirStruc::WeldedWingSixOK()
{
	bool sixok = true;
	int range = ENGAGERANGE;
	if  ( !ManoeuvreTimeLeft())
	{
		if (ai.attacker)
		{
			if (BreakCallNecessary(this, ai.attacker, range))
			{
				sixok = false;
				MANOEUVRE manoeuvre;
				RndVal	rndnum = Math_Lib.rnd();
				if	(rndnum < RND50PC)
					manoeuvre = MANOEUVRE_BREAKTURN;
				else
					manoeuvre = MANOEUVRE_SPLITS;						  //RDH 15/06/99 //RDH 20/06/99

				Art_Int.SetEngage(this,ai.attacker,manoeuvre,ANGLES_0Deg,ANGLES_0Deg, FALSE);
				if (leader)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTCLEAR, MSG_CLEAR_RPT, this, NULL, ((AirStrucPtr)leader)));
			}

		}
		if (	(leader)	&&	(((AirStrucPtr)leader)->ai.attacker))
		{
			if (BreakCallNecessary(((AirStrucPtr)leader), ((AirStrucPtr)leader)->ai.attacker, range))
			{
				sixok = false;
//DEADCODE DAW 05/07/99 			   BreakCallandReaction(this, ((AirStrucPtr)leader)->ai.attacker, ((AirStrucPtr)leader));
			   BreakCallandReaction(this, ((AirStrucPtr)leader), ((AirStrucPtr)leader)->ai.attacker); //DAW 05/07/99


			}
		}
		if(sixok)
		{
			int drange = range - DANGERRANGE;
			if (drange < 0)
				drange = 0;
			int time = 200 + drange/100;
			SetManoeuvreTime (time);
		}else
			SetManoeuvreTime (200);
	}
	return(sixok);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakCallNecessary
//Author		R. Hyde 
//Date			Tue 19 Dec 1995
//
//Description	
//					Horrible code to retain the globals
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool AirStruc::BreakCallNecessary(AirStrucPtr currac,AirStrucPtr unf, int range)
{
	bool Break = false;
	if (		(currac->ai.unfriendly != unf)
			||	(currac->AcIsPlayer())
		)
	{
  		ANGLES	oldhdgint, oldpitchint;
		SLong	oldrange;
		ANGLES	hdgint;
		oldhdgint = HdgIntercept;
		oldpitchint = PitchIntercept;
		oldrange  = Range;

		Art_Int.InterceptRangeFromTo(currac, unf);
		range = Range;
		if (Range < ENGAGERANGE)		//rdh 13/7(DANGERRANGE+ METRES200)) 
		{
			ANGLES delta = HdgIntercept + ANGLES_180Deg + ANGLES_45Deg - currac->hdg;
			if ((delta) << (ANGLES_90Deg))
				Break = true;
		}
		PitchIntercept = oldpitchint;
		HdgIntercept = oldhdgint;
		Range = oldrange;
	}

	return(Break);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFollowerTactic
//Author		Craig Beeston 
//Date			Mon 5 Jul 1999
//
//Description	Sets the ai.FirstTactic for the whole group
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SetFollowersTactic(int TACTIC)
{
	AirStrucPtr Lead, Foll;
	for(Lead = FindGroupLeader(); Lead; Lead = Lead->fly.nextflight)
		for(Foll = Lead; Foll; Foll = Foll->Follower())
			Foll->ai.firsttactic = (tFirstEncounterTactics)TACTIC;

}
