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

//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //Filename       modacm.cpp
//DeadCode RDH 26Mar98 //System         
//DeadCode RDH 26Mar98 //Author         Andrew McRae
//DeadCode RDH 26Mar98 //Date           Mon 17 Mar 1997
//DeadCode RDH 26Mar98 //Description    Fligth Model ACM
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 #define F_GRAFIX											//DAW 05Aug96
//DeadCode RDH 26Mar98 #define F_COMMON
//DeadCode RDH 26Mar98 #define F_BATTLE
//DeadCode RDH 26Mar98 #include "collided.h"										//PD 06Sep96
//DeadCode RDH 26Mar98 #include "Dosdefs.h"		
//DeadCode RDH 26Mar98 #include "Worldinc.h"
//DeadCode RDH 26Mar98 #include "modvec.h"
//DeadCode RDH 26Mar98 #include "model.h"
//DeadCode RDH 26Mar98 #include "FlyModel.h"
//DeadCode RDH 26Mar98 #include "mymath.h"
//DeadCode RDH 26Mar98 #include "enumbits.m"
//DeadCode RDH 26Mar98 #include "mytime.h"											//RDH 25Apr96
//DeadCode RDH 26Mar98 #include "ranges.h"
//DeadCode RDH 26Mar98 #include "missman2.h"										//JIM 22Aug96
//DeadCode RDH 26Mar98 #include "movement.h"
//DeadCode RDH 26Mar98 #include "transite.h"
//DeadCode RDH 26Mar98 #include "ai.h"
//DeadCode RDH 26Mar98 #include "miles.h"											//RDH 25Jul96
//DeadCode RDH 26Mar98 #include "landscap.h"										//RDH 18Dec96
//DeadCode RDH 26Mar98 #include "viewsel.h"										//RDH 25Jul96
//DeadCode RDH 26Mar98 #include "3dcom.h"											//RJS 22Aug96
//DeadCode RDH 26Mar98 #include "speed.h"											//RDH 01Oct96
//DeadCode RDH 26Mar98 #include "persons2.h"
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 MATHABLE	(ANGLES)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 // ROD don't use STALL_ANGLE
//DeadCode RDH 26Mar98 ANGLES const	STALL_ANGLE = ANGLES_15Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 ANGLES const	STALL_ANGLE_MINUSONE = STALL_ANGLE - ANGLES_1Deg;
//DeadCode RDH 26Mar98 ANGLES const	STALL_ANGLE_MINUSTWO = STALL_ANGLE - ANGLES_2Deg;
//DeadCode RDH 26Mar98 ANGLES const	STALL_ANGLE_MINUSTHREE = STALL_ANGLE - ANGLES_3Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 09Jul96 SLong	const	ELEVATOR_DELTA = 160;
//DeadCode RDH 26Mar98 SLong	const	ELEVATOR_DELTA = 40;
//DeadCode RDH 26Mar98 SLong	const	ELEVATOR_DELTA_DOWN = ELEVATOR_DELTA * 2;
//DeadCode RDH 26Mar98 SLong	const	RUDDER_DELTA = 1000;
//DeadCode RDH 26Mar98 SLong	const	MAXAUTOTHRUST = 80;	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 ANGLES const	DSLIPFORMAXRUDDER = ANGLES_10Deg;
//DeadCode RDH 26Mar98 ANGLES const	DPITCHFORMAXELEVATOR = ANGLES_60Deg;
//DeadCode RDH 26Mar98 ANGLES const	DAOAFORMAXELEVATOR = ANGLES_15Deg;
//DeadCode RDH 26Mar98 //sensitivity for Diferential control
//DeadCode RDH 26Mar98 ANGLES const	DIFFPITCHFORMAXELEVATOR = ANGLES_10Deg;
//DeadCode RDH 26Mar98 ANGLES const	DHDGFORMAXAILERON = ANGLES_22Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 02Jul96 SLong const MAXELEVATORFORTIGHTTURN = -30000;
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 SLong const MAXELEVATORFORTIGHTTURN = -20000;
//DeadCode RDH 26Mar98 SLong const MAXELEVATORFORTIGHTTURN = -25000;
//DeadCode RDH 26Mar98 SLong const SLIGHTPULLELEVATOR = -4000;
//DeadCode RDH 26Mar98 SLong const MEDIUMPULLELEVATOR = -12000;
//DeadCode RDH 26Mar98 SLong const HEAVYPULLELEVATOR = -20352;							//RDH 21Aug96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 static RequiredBankDataElement 	CombatReqBankData[] =
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				{ANGLES_FifthDeg, ANGLES_0Deg},
//DeadCode RDH 26Mar98 				{ANGLES_HalfDeg, ANGLES_3Deg},
//DeadCode RDH 26Mar98 				{ANGLES_1Deg, ANGLES_4Deg},
//DeadCode RDH 26Mar98 				{ANGLES_2Deg, ANGLES_5Deg},
//DeadCode RDH 26Mar98 				{ANGLES_3Deg, ANGLES_10Deg},
//DeadCode RDH 26Mar98 				{ANGLES_4Deg, ANGLES_15Deg},
//DeadCode RDH 26Mar98 				{ANGLES_5Deg, ANGLES_22Deg},
//DeadCode RDH 26Mar98 				{ANGLES_6Deg, ANGLES_30Deg},
//DeadCode RDH 26Mar98 				{ANGLES_10Deg, ANGLES_45Deg},
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jul96 				{ANGLES_22Deg, ANGLES_60Deg},
//DeadCode RDH 26Mar98 				{ANGLES_30Deg, MAXCOMBATROLL},
//DeadCode RDH 26Mar98 				{ANGLES_180BareDeg, MAXCOMBATROLL}
//DeadCode RDH 26Mar98 			};
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
//DeadCode RDH 26Mar98 	if ((modifier * deltapitch_pos)    > DPITCHFORMAXELEVATOR)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		elevator = -MAXELEVATORFORTIGHTTURN;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		elevator = (modifier * -MAXELEVATORFORTIGHTTURN * deltapitch_pos)/ DPITCHFORMAXELEVATOR;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if (deltapitch_sign == MathLib::POSITIVE)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		elevator = (SWord) -elevator;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	//D control
//DeadCode RDH 26Mar98 	deltadeltapitch = deltapitch - (SWord) ai.lastdeltapitch;
//DeadCode RDH 26Mar98  	Math_Lib.Pos (deltadeltapitch,deltapitch_pos,deltapitch_sign);
//DeadCode RDH 26Mar98  	if (deltapitch_pos >= DIFFPITCHFORMAXELEVATOR)
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
//DeadCode RDH 26Mar98 		elevator -=	-MAXELEVATORFORTIGHTTURN * (deltapitch - (SWord) ai.lastdeltapitch) / DIFFPITCHFORMAXELEVATOR;
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
//DeadCode RDH 26Mar98 	ai.lastdeltapitch = (ANGLES) deltapitch;
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
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98  //Procedure		MoveToHdg
//DeadCode RDH 26Mar98  //Author		R. Hyde 
//DeadCode RDH 26Mar98  //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Description	based on difference between desired and actual hdg, fix aileron
//DeadCode RDH 26Mar98  //				to give a roll, morale and skill will fix maxroll				
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Inputs		
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Returns	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98  void	AirStruc::MoveToHdg (ANGLES desiredhdg)
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  {
//DeadCode RDH 26Mar98  	SWord	reqdeltahdg, reqdeltahdg_sign;
//DeadCode RDH 26Mar98 	UWord	reqdeltahdg_pos;
//DeadCode RDH 26Mar98  	SWord	reqroll,deltaroll;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	reqdeltahdg = 	fly.chdg - desiredhdg;
//DeadCode RDH 26Mar98  	Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode RDH 26Mar98  	reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 //DeadCode RDH 30Mar96  	deltaroll = (SWord) (reqroll - fly.acroll);
//DeadCode RDH 26Mar98 	ai.desiredroll = (ANGLES) reqroll;
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96  	MoveToRoll (reqroll,1);
//DeadCode RDH 26Mar98 	MoveToRoll (ai.desiredroll,1 + (ai.skill /3));						//RDH 26Jul96
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  }
//DeadCode RDH 26Mar98 
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
//DeadCode RDH 26Mar98  	SWord	reqdeltahdg;
//DeadCode RDH 26Mar98 	UWord	reqdeltahdg_pos;
//DeadCode RDH 26Mar98 	SWord	reqdeltahdg_sign;
//DeadCode RDH 26Mar98  	SWord	reqroll,deltaroll;
//DeadCode RDH 26Mar98 	UWord	reqroll_pos;
//DeadCode RDH 26Mar98 	SWord	reqroll_sign;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	reqdeltahdg = 	(SWord) fly.chdg - (SWord) desiredhdg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 22Mar96  	if ( ((SWord) fly.acroll < ANGLES_0Deg) == (reqroll < ANGLES_0Deg))
//DeadCode RDH 26Mar98 //DeadCode RDH 22Mar96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 22Mar96 		reqroll = -reqroll;
//DeadCode RDH 26Mar98 //DeadCode RDH 22Mar96 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	Math_Lib.Pos (reqroll, reqroll_pos,reqroll_sign);
//DeadCode RDH 26Mar98 	if (reqroll_pos > maxroll)
//DeadCode RDH 26Mar98 		reqroll_pos = maxroll;
//DeadCode RDH 26Mar98  	if (reqroll_sign == MathLib::NEGATIVE)
//DeadCode RDH 26Mar98 		reqroll = -reqroll_pos;
//DeadCode RDH 26Mar98 	else
//DeadCode RDH 26Mar98 		reqroll = reqroll_pos;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	if ( !!((SWord) fly.acroll < ANGLES_0Deg) != !!(reqroll < ANGLES_0Deg))
//DeadCode RDH 26Mar98  		reqroll = -reqroll;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 30Mar96 	deltaroll = (SWord) (reqroll - (SWord) fly.acroll);
//DeadCode RDH 26Mar98 	MoveToRoll (reqroll,1);
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
//DeadCode RDH 26Mar98  	if ((modifier * deltaroll_pos) >= DROLLFORMAXAILERON)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		aileron = (SLong) MAXAILERON;
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		aileron = modifier * MAXAILERON * deltaroll_pos/DROLLFORMAXAILERON;
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
//DeadCode RDH 26Mar98  	if ((modifier * deltaroll_pos) >= DIFFAILERONFORMAXAILERON)
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
//DeadCode RDH 26Mar98 		aileron +=	modifier * MAXAILERON * (deltaroll - (SWord) ai.lastdeltaroll) / DIFFAILERONFORMAXAILERON;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ai.lastdeltaroll = (ANGLES) deltaroll;
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
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveToDesiredHdg
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
//DeadCode RDH 26Mar98 Bool	AirStruc::MoveToDesiredHdg (ANGLES desiredhdg,ANGLES target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	Bool	retval;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	MoveToHdg (desiredhdg);
//DeadCode RDH 26Mar98 	retval = ChkAtDesiredHdg (desiredhdg,target);
//DeadCode RDH 26Mar98 	return (retval);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ChkAtDesiredHdg
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
//DeadCode RDH 26Mar98 Bool	AirStruc::ChkAtDesiredHdg (ANGLES desiredhdg,ANGLES target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord deltahdg;
//DeadCode RDH 26Mar98 	UWord	deltahdg_pos;
//DeadCode RDH 26Mar98 	SWord	deltahdg_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	deltahdg = desiredhdg -	fly.chdg;
//DeadCode RDH 26Mar98 	Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);
//DeadCode RDH 26Mar98 	if (deltahdg_pos < target)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		return (TRUE);
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		return (FALSE);
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ChkAtDesiredAcHdg
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
//DeadCode RDH 26Mar98 Bool	AirStruc::ChkAtDesiredAcHdg (ANGLES desiredhdg,ANGLES target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord deltahdg;
//DeadCode RDH 26Mar98 	UWord	deltahdg_pos;
//DeadCode RDH 26Mar98 	SWord	deltahdg_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	deltahdg = desiredhdg -	hdg;
//DeadCode RDH 26Mar98 	Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);
//DeadCode RDH 26Mar98 	if (deltahdg_pos < target)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		return (TRUE);
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		return (FALSE);
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveToDesiredHdgOnThisRoll
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
//DeadCode RDH 26Mar98 SWord	AirStruc::MoveToDesiredHdgOnThisRoll (ANGLES desiredhdg,ANGLES target,ANGLES maxroll)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord deltahdg;
//DeadCode RDH 26Mar98 	UWord	deltahdg_pos;
//DeadCode RDH 26Mar98 	SWord	deltahdg_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	MoveToHdgOnThisRoll (desiredhdg,maxroll);
//DeadCode RDH 26Mar98 	deltahdg = desiredhdg -	fly.chdg;
//DeadCode RDH 26Mar98 	Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);
//DeadCode RDH 26Mar98 	if (deltahdg_pos < target)
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
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveToThrust
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 18 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	0 and 100 values can be altered by autoshoot range
//DeadCode RDH 26Mar98 //				other values like 1 cannot.
//DeadCode RDH 26Mar98 //				-100 move to max if min
//DeadCode RDH 26Mar98 //				-1 move tomin if max
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::MoveToThrust (SWord thrust)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	if  (thrust == -100)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (fly.thrustpercent ==0)
//DeadCode RDH 26Mar98 			fly.thrustpercent =  100;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	elseif  (thrust == -1)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (fly.thrustpercent ==100)
//DeadCode RDH 26Mar98 			fly.thrustpercent =  0;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	else
//DeadCode RDH 26Mar98 		fly.thrustpercent =  thrust;
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SplitS
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
//DeadCode RDH 26Mar98 void	AirStruc::SplitS ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord 	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_180Deg;
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			fly.elevator = 0;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Jul96 			if (fly.cpitch < ANGLES_90Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Jul96 				MoveToPitch (ANGLES_0Deg);
//DeadCode RDH 26Mar98 			deltaroll = (SWord) (ai.desiredroll - fly.acroll);
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 			if (deltaroll_pos <ANGLES_10Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 	 			MoveToThrust (1);
//DeadCode RDH 26Mar98 				ai.lastdeltapitch = ANGLES_0Deg;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			fly.elevator = SLIGHTPULLELEVATOR;
//DeadCode RDH 26Mar98 			if ( 		(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					|| (    DesiredPitchChk (ANGLES_340Deg,ANGLES_20Deg)
//DeadCode RDH 26Mar98 						&&										//RDH 24Jul96
//DeadCode RDH 26Mar98 							(fly.acroll < ANGLES_90Deg)			//RDH 24Jul96
//DeadCode RDH 26Mar98 						&&	(fly.acroll > ANGLES_270Deg)		//RDH 24Jul96
//DeadCode RDH 26Mar98 						)										//RDH 24Jul96
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 	 			MoveToThrust (100);
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ZoomandDrop
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
//DeadCode RDH 26Mar98 void	AirStruc::ZoomandDrop ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord phase,deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	phase = (SWord) ai.ManStep;
//DeadCode RDH 26Mar98 	switch (phase)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_0Deg;
//DeadCode RDH 26Mar98  			MoveToThrust (0);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1 + (ai.skill /3));						//RDH 26Jul96
//DeadCode RDH 26Mar98 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 			if (	(deltaroll_pos <ANGLES_30Deg)
//DeadCode RDH 26Mar98 				||	(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (200);
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1 + (ai.skill /3));						//RDH 26Jul96
//DeadCode RDH 26Mar98 			MoveToAoA (STALL_ANGLE_MINUSONE - (fly.highest_aoa - fly.aoa));
//DeadCode RDH 26Mar98 			if (	((SWord) (classtype->stallangle - fly.highest_aoa) < ANGLES_3Deg)
//DeadCode RDH 26Mar98 				||	(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98  				MoveToThrust (100);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (MoveToDesiredPitch (ANGLES_315Deg,ANGLES_20Deg))//RDH 19Dec96
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		LeadUnFriendly
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 15 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::LeadUnFriendly ()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		t,actualrange;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			target.X = ai.unfriendly->World.X;
//DeadCode RDH 26Mar98 			target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 26Mar98 			target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 26Mar98 			InterceptandRange (&target);
//DeadCode RDH 26Mar98 			actualrange = Range;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			//closing velocity
//DeadCode RDH 26Mar98 			SLong deltax = velx - unfriendly->velx;
//DeadCode RDH 26Mar98 			SLong deltay = vely - unfriendly->vely;
//DeadCode RDH 26Mar98 			SLong deltaz = velz - unfriendly->velz;
//DeadCode RDH 26Mar98 			Math_Lib.Intercept (deltax,deltay,deltaz,Range,HdgIntercept,PitchIntercept);
//DeadCode RDH 26Mar98 			//Range is a velocity in 10cm/s
//DeadCode RDH 26Mar98 			if (Range != 0)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				t = actualrange / Range;
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				t = 0;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			//when a long way off don't attempt to lead
//DeadCode RDH 26Mar98 			if (t >2000)
//DeadCode RDH 26Mar98 			t = 0;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			target.X = ai.unfriendly->World.X + (unfriendly->velx * t / 10);
//DeadCode RDH 26Mar98 			target.Y = ai.unfriendly->World.Y + (unfriendly->vely * t / 10);
//DeadCode RDH 26Mar98 			target.Z = ai.unfriendly->World.Z + (unfriendly->velz * t / 10);
//DeadCode RDH 26Mar98 			InterceptandRange (&target);
//DeadCode RDH 26Mar98 			MoveToPitch (PitchIntercept,1);
//DeadCode RDH 26Mar98 			MoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		GatherSpeed
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 15 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::GatherSpeed ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		target.X = ai.unfriendly->World.X;
//DeadCode RDH 26Mar98 		target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 26Mar98 		target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 26Mar98 		InterceptandRange (&target);
//DeadCode RDH 26Mar98 		MoveToPitch (ANGLES_330Deg,1);
//DeadCode RDH 26Mar98  		MoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		LeadUnFriendly
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 15 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::SimpleLeadUnFriendly ()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		t,actualrange;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			target.X = ai.unfriendly->World.X;
//DeadCode RDH 26Mar98 			target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 26Mar98 			target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 26Mar98 			InterceptandRange (&target);
//DeadCode RDH 26Mar98 			actualrange = Range;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			//closing velocity
//DeadCode RDH 26Mar98 			SLong deltax = velx - unfriendly->velx;
//DeadCode RDH 26Mar98 			SLong deltay = vely - unfriendly->vely;
//DeadCode RDH 26Mar98 			SLong deltaz = velz - unfriendly->velz;
//DeadCode RDH 26Mar98 			Math_Lib.Intercept (deltax,deltay,deltaz,Range,HdgIntercept,PitchIntercept);
//DeadCode RDH 26Mar98 			//Range is a velocity in 10cm/s
//DeadCode RDH 26Mar98 			if (Range != 0)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				t = actualrange / Range;
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				t = 0;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			//when a long way off don't attempt to lead
//DeadCode RDH 26Mar98 			if (t >2000)
//DeadCode RDH 26Mar98 			t = 0;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			target.X = ai.unfriendly->World.X + (unfriendly->velx * t / 10);
//DeadCode RDH 26Mar98 			target.Y = ai.unfriendly->World.Y + (unfriendly->vely * t / 10);
//DeadCode RDH 26Mar98 			target.Z = ai.unfriendly->World.Z + (unfriendly->velz * t / 10);
//DeadCode RDH 26Mar98 			InterceptandRange (&target);
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		GatherSpeed
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 15 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::SimpleGatherSpeed ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		target.X = ai.unfriendly->World.X;
//DeadCode RDH 26Mar98 		target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 26Mar98 		target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 26Mar98 		InterceptandRange (&target);
//DeadCode RDH 26Mar98 		PitchIntercept = ANGLES_330Deg;
//DeadCode RDH 26Mar98 		AutoCalcPitch();
//DeadCode RDH 26Mar98  		SimpleMoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		DiveAndZoom
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
//DeadCode RDH 26Mar98 void	AirStruc::DiveAndZoom ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	deltapitch_pos,deltapitch_sign;
//DeadCode RDH 26Mar98 	SLong	temp_range;
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		t,actualrange;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98  	SWord		deltaroll;										//RDH 14Mar96
//DeadCode RDH 26Mar98 	SWord		easestickforward;
//DeadCode RDH 26Mar98 	ANGLES		local_PI;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	local_PI  = PitchIntercept;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 29Mar96 			FlatTurn ();
//DeadCode RDH 26Mar98  			if ((vel - unfriendly->vel) < (unfriendly->vel/4))
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  				GatherSpeed ();
//DeadCode RDH 26Mar98  			}else
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  				LeadUnFriendly ();
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98  			if  (Range < METRES300)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98  				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98  			if (local_PI << ANGLES_90Deg)
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			temp_range = Range; 	
//DeadCode RDH 26Mar98 			TightTurn (FT_1000);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if  (	(ai.skill < SKILL_VETERAN)
//DeadCode RDH 26Mar98 			  	&&	(ChkAtDesiredHdg (HdgIntercept,ANGLES_5Deg))
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 				FireABullet();
//DeadCode RDH 26Mar98  			if (temp_range < METRES60)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (500);
//DeadCode RDH 26Mar98  				ai.desiredroll = ANGLES_0Deg - ANGLES_45Deg +
//DeadCode RDH 26Mar98  						(ANGLES)(ANGLES_90Deg * Math_Lib.rnd(2)); 
//DeadCode RDH 26Mar98  				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 			TightClimbingTurn (ANGLES_20Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 			TightClimbingTurn (ANGLES_20Deg);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98  				ai.ManStep = PHASE4;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE4:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 			TightClimbingTurn (ANGLES_10Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 			TightClimbingTurn (ANGLES_10Deg);
//DeadCode RDH 26Mar98 			target.X = unfriendly->World.X;
//DeadCode RDH 26Mar98 			target.Y = unfriendly->World.Y;
//DeadCode RDH 26Mar98 			target.Z = unfriendly->World.Z;
//DeadCode RDH 26Mar98  			InterceptandRange (&target);
//DeadCode RDH 26Mar98 			if (	(ChkAtDesiredHdg (HdgIntercept,ANGLES_45Deg))
//DeadCode RDH 26Mar98 				||(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		AllButLdrNotOnCombat
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 11 Nov 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 Bool AirStruc::AllButLdrNotOnCombat ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	AirStrucPtr		ac,leadac;	
//DeadCode RDH 26Mar98 	if (formpos == 0)
//DeadCode RDH 26Mar98 	{//leader
//DeadCode RDH 26Mar98 		ac = *this;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		ac = fly.leadflight;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	leadac =ac;
//DeadCode RDH 26Mar98 	do
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		do
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if  (	(ac->movecode==AUTO_COMBAT)
//DeadCode RDH 26Mar98 				&&  (	(ac->ai.manoeuvre != MANOEUVRE_TOPCOVER)
//DeadCode RDH 26Mar98 					&&	(ac->ai.manoeuvre != MANOEUVRE_LOOKROUND)
//DeadCode RDH 26Mar98 					&&	(ac->ai.manoeuvre != MANOEUVRE_DIVEFORHOME)	
//DeadCode RDH 26Mar98 					&&	(ac->ai.manoeuvre != MANOEUVRE_CLIMBFORHOME)
//DeadCode RDH 26Mar98 					&&	(ac->ai.manoeuvre != MANOEUVRE_STRAIGHTDIVE)
//DeadCode RDH 26Mar98 					&&	(ac->ai.manoeuvre != MANOEUVRE_GOHOME )		
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 				&&
//DeadCode RDH 26Mar98 					(formpos != 0)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 				return (FALSE);
//DeadCode RDH 26Mar98 			ac = *ac->follower;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		while (ac);
//DeadCode RDH 26Mar98 	leadac = *leadac->fly.nextflight;
//DeadCode RDH 26Mar98 	ac = leadac;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	while (leadac);
//DeadCode RDH 26Mar98 	return (TRUE);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		AllOnTopCover
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 19 Aug 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 Bool AirStruc::AllOnTopCover ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	AirStrucPtr		ac,leadac;	
//DeadCode RDH 26Mar98 	if (formpos == 0)
//DeadCode RDH 26Mar98 	{//leader
//DeadCode RDH 26Mar98 		ac = *this;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		ac = fly.leadflight;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	leadac =ac;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	do
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		do
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (	ac->movecode==AUTO_COMBAT
//DeadCode RDH 26Mar98 				&&	ac->ai.manoeuvre != MANOEUVRE_TOPCOVER
//DeadCode RDH 26Mar98 				&&  (InterceptandRange(ac),Range<METRES4000)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 				return (FALSE);
//DeadCode RDH 26Mar98 			ac = *ac->follower;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		while (ac);
//DeadCode RDH 26Mar98 	leadac = *leadac->fly.nextflight;
//DeadCode RDH 26Mar98 	ac = leadac;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	while (leadac);
//DeadCode RDH 26Mar98 	return (TRUE);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TopCover
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 19 Aug 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	The followers are supposed to go near to home line or
//DeadCode RDH 26Mar98 //				not depending on skill
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::TopCover ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98   if (formpos == 0)
//DeadCode RDH 26Mar98   {//leader
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_0Deg - ANGLES_30Deg +
//DeadCode RDH 26Mar98  						(ANGLES)(ANGLES_60Deg * Math_Lib.rnd(2)); 
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
//DeadCode RDH 26Mar98 				if (ai.eventlog->stage==EventLog::TAKEOFF)		//JIM 06Dec96
//DeadCode RDH 26Mar98 					if (formpos!=0 || follower || fly.nextflight)
//DeadCode RDH 26Mar98 					 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_SQUADRONREGROUPED,NULL);
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
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_0Deg - ANGLES_30Deg +
//DeadCode RDH 26Mar98  						(ANGLES)(ANGLES_60Deg * Math_Lib.rnd(2)); 
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
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		LookAround
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 19 Aug 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::LookAround ()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_0Deg - ANGLES_45Deg +
//DeadCode RDH 26Mar98  						(ANGLES)(ANGLES_90Deg * Math_Lib.rnd(2)); 
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
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		BestClimb
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 10 Sep 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::BestClimb()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98 //DeadCode RDH 27Nov96  			MoveToThrust (90 - ai.skill * 3);
//DeadCode RDH 26Mar98  			MoveToThrust (95);									//RDH 27Nov96
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
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_10Deg,1);
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1);							//RDH 14May96
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		BounceFollower
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 10 Sep 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::BounceFollower()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
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
//DeadCode RDH 26Mar98 			target.X = follower->World.X;
//DeadCode RDH 26Mar98 			target.Y = follower->World.Y;
//DeadCode RDH 26Mar98 			target.Z = follower->World.Z;
//DeadCode RDH 26Mar98 			TightTurnSub (FT_1000,target);
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		BarrelRoll
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::BarrelRoll ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			ai.desiredroll = (ANGLES) fly.turnrate;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if ((SWord)ai.desiredroll >= 0)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				fly.aileron = MAXAILERON;
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				fly.aileron = -MAXAILERON;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98  			if (	(fly.acroll > ANGLES_90Deg)					//RDH 24Jul96
//DeadCode RDH 26Mar98 				|| (fly.acroll <= ANGLES_270Deg))				//RDH 24Jul96
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98 				fly.elevator = -SLIGHTPULLELEVATOR;
//DeadCode RDH 26Mar98  			}else
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98 				fly.elevator = MEDIUMPULLELEVATOR;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jul96 			MoveToPitch (ANGLES_0Deg,6);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	SetControlSurfaces ();
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		Scissors
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::Scissors ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			ai.desiredhdg = fly.chdg + ANGLES_120Deg; 
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
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg - ANGLES_240Deg; 
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
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg + ANGLES_240Deg; 
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
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MildScissors
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::MildScissors ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			ai.desiredhdg = fly.chdg - ANGLES_15Deg; 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_6Deg,1);
//DeadCode RDH 26Mar98 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg + ANGLES_30Deg; 
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
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_6Deg,1);
//DeadCode RDH 26Mar98 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg - ANGLES_30Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		StraightandLevel
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::StraightandLevel ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord 	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98  			MoveToThrust (80);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 	 		ai.desiredroll = ANGLES_0Deg;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (World.Y < FT_1000)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToPitch (ANGLES_4Deg,1);
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				if ((SWord)	fly.cpitch > 0)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					MoveToAoA (ANGLES_0Deg);
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					MoveToAoA (ANGLES_2Deg);
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			deltaroll = (SWord) (ai.desiredroll - fly.acroll);
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 			if (deltaroll_pos <ANGLES_4Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (World.Y < FT_1000)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToPitch (ANGLES_10Deg,1);
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				if ((SWord)	fly.cpitch < 0)
//DeadCode RDH 26Mar98 					MoveToPitch ((fly.cpitch + ANGLES_4Deg),1);
//DeadCode RDH 26Mar98 				else
//DeadCode RDH 26Mar98 					MoveToPitch (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			MoveToRoll (ANGLES_0Deg,1);							//RDH 14May96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		AcmSideSlip
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::AcmSideSlip ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98 			ai.desiredhdg = fly.chdg;
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 			if (fly.rudder >= 0)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				fly.rudder = MAXRUDDER;
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				fly.rudder =-MAXRUDDER;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			MoveToHdg (ai.desiredhdg);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 				fly.rudder = 0;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SpinRecovery
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 21 Aug 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SpinRecovery ()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	UWord	deltayaw_pos;
//DeadCode RDH 26Mar98 	SWord	deltayaw_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (1);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			fly.elevator = 0;
//DeadCode RDH 26Mar98 			fly.rudder = -fly.rudder;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			Math_Lib.Pos (((SWord)fly.rotr_ybl),deltayaw_pos,deltayaw_sign);
//DeadCode RDH 26Mar98 			if (deltayaw_pos <250)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (800);
//DeadCode RDH 26Mar98 				fly.rudder = 0;
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				fly.rotr_zbl = 0;
//DeadCode RDH 26Mar98 				fly.rotr_ybl = 0;
//DeadCode RDH 26Mar98 				fly.rotr_xbl = 0;
//DeadCode RDH 26Mar98 	 			MoveToThrust (100);
//DeadCode RDH 26Mar98 				fly.cpitch = pitch;
//DeadCode RDH 26Mar98 				fly.chdg = hdg;
//DeadCode RDH 26Mar98 				fly.croll = fly.acroll;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			fly.rotr_zbl = 0;
//DeadCode RDH 26Mar98 			fly.rotr_ybl = 0;
//DeadCode RDH 26Mar98 			fly.elevator = SLIGHTPULLELEVATOR;
//DeadCode RDH 26Mar98 			if  ((!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					|| ((SWord)	fly.cpitch > 0)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SpinOut
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SpinOut ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltayaw_pos;
//DeadCode RDH 26Mar98 	SWord	deltayaw_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (1);
//DeadCode RDH 26Mar98 			fly.elevator = -MAXELEVATOR;
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (	((SWord) fly.aoa > (SWord) classtype->stallangle)
//DeadCode RDH 26Mar98 				||	(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				if ((SWord) fly.yawrate > 0)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					fly.rudder = MAXRUDDER;
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					fly.rudder = -MAXRUDDER;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (800);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 				fly.elevator = 0;
//DeadCode RDH 26Mar98 				fly.rudder = -fly.rudder;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			Math_Lib.Pos (((SWord)fly.rotr_ybl),deltayaw_pos,deltayaw_sign);
//DeadCode RDH 26Mar98 			if (deltayaw_pos <250)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (800);
//DeadCode RDH 26Mar98 				fly.rudder = 0;
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE4;
//DeadCode RDH 26Mar98 				fly.rotr_zbl = 0;
//DeadCode RDH 26Mar98 				fly.rotr_ybl = 0;
//DeadCode RDH 26Mar98 				fly.rotr_xbl = 0;
//DeadCode RDH 26Mar98 	 			MoveToThrust (100);
//DeadCode RDH 26Mar98 				fly.cpitch = pitch;
//DeadCode RDH 26Mar98 				fly.chdg = hdg;
//DeadCode RDH 26Mar98 				fly.croll = fly.acroll;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE4:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			fly.rotr_zbl = 0;
//DeadCode RDH 26Mar98 			fly.rotr_ybl = 0;
//DeadCode RDH 26Mar98 			fly.elevator = SLIGHTPULLELEVATOR;
//DeadCode RDH 26Mar98 //DeadCode RDH 11Jul96 			MoveToRoll (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			if  ((!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					|| ((SWord)	fly.cpitch > 0)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 		SetControlSurfaces ();
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		DiveforHome
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::DiveforHome ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	lastwaypoint = waypoint;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	while (lastwaypoint->next)
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 		lastwaypoint = lastwaypoint->next;
//DeadCode RDH 26Mar98 	SLong	temp_range;
//DeadCode RDH 26Mar98 	temp_range = Range; 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (World.Y < FT_1000)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToPitch (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToPitch (ANGLES_340Deg,1);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 			InterceptandRange (&lastwaypoint->World);
//DeadCode RDH 26Mar98 				if (ai.homebase)
//DeadCode RDH 26Mar98 					InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 				else
//DeadCode RDH 26Mar98 					HdgIntercept = ANGLES_0Deg;
//DeadCode RDH 26Mar98 				MoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < MILES01)
//DeadCode RDH 26Mar98 			{//within mile of home
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			Range = temp_range; 	
//DeadCode RDH 26Mar98 			if (Range > MILES01)
//DeadCode RDH 26Mar98 			{//mile from action, reconsider
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ClimbAtBestSpeed
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 18 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::ClimbAtBestSpeed ()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_10Deg,2);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TightClimbingTurn
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Sat 30 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::TightClimbingTurn (ANGLES desiredpitch)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		deltapitch = desiredpitch - fly.cpitch;
//DeadCode RDH 26Mar98 		PitchIntercept = desiredpitch; 
//DeadCode RDH 26Mar98 		TightTurnSubSub (deltapitch);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ClimbforHome
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::ClimbforHome ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
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
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 			lastwaypoint = waypoint;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 			while (lastwaypoint->next)
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 				lastwaypoint = lastwaypoint->next;
//DeadCode RDH 26Mar98 			MoveToThrust (100);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 			InterceptandRange (&lastwaypoint->World);
//DeadCode RDH 26Mar98 			InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 			ai.desiredhdg = HdgIntercept; 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			Range = temp_range; 	
//DeadCode RDH 26Mar98 			if (Range < SHOOTINGRANGE)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if ((SWord) (classtype->stallangle - fly.aoa) > ANGLES_4Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToPitch (ANGLES_15Deg,6);
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToPitch (ANGLES_15Deg,1);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			MoveToHdg (ai.desiredhdg);
//DeadCode RDH 26Mar98 			Range = temp_range; 	
//DeadCode RDH 26Mar98 			if (Range > BREAKOFFRANGE)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		StraightDive
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::StraightDive ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord 	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98  			MoveToThrust (90);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			MoveToRoll (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_340Deg,2);
//DeadCode RDH 26Mar98 			if (World.Y < FT_1000)
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			if  (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		StandOnTail
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::StandOnTail ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		time;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (800);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			target.X = ai.unfriendly->World.X;
//DeadCode RDH 26Mar98 			target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 26Mar98 			target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 26Mar98 			InterceptandRange (&target);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			//time for bullets to arrive at current unfriendly position
//DeadCode RDH 26Mar98 			time = Range / MUZZELVEL;
//DeadCode RDH 26Mar98 			//calc lead position using this time
//DeadCode RDH 26Mar98 			target.X = ai.unfriendly->World.X + (unfriendly->velx * time );
//DeadCode RDH 26Mar98 			target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
//DeadCode RDH 26Mar98 			target.Z = ai.unfriendly->World.Z + (unfriendly->velz * time );
//DeadCode RDH 26Mar98 			InterceptandRange (&target);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			MoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 			if ((SWord) (classtype->stallangle - fly.aoa) < ANGLES_2Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				if ((SWord) fly.cpitch < (SWord) PitchIntercept)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					fly.elevator = HEAVYPULLELEVATOR;
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					MoveToPitch (PitchIntercept,8);
//DeadCode RDH 26Mar98 					FireABullet();
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if ((SWord) (classtype->stallangle - fly.aoa) < ANGLES_5Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				FireABullet();
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		GainHeight
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::GainHeight ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
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
//DeadCode RDH 26Mar98 				ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
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
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ShootToFrighten
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::ShootToFrighten ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (200);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 			   	ai.ManStep = PHASE0;
//DeadCode RDH 26Mar98 				ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			TightTurn (FT_1000);
//DeadCode RDH 26Mar98 			FireABullet();
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		GoHome
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::GoHome ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
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
//DeadCode RDH 26Mar98 					&&	(Range < 4 * SHOOTINGRANGE)
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
//DeadCode RDH 26Mar98 						&&	(Range < 4 * SHOOTINGRANGE)
//DeadCode RDH 26Mar98 						&&	(ai.skill >= SKILL_REGULAR)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 					ai.desiredhdg = HdgIntercept + ANGLES_340Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < SHOOTINGRANGE)
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
//DeadCode RDH 26Mar98 						&&	(Range < 4 * SHOOTINGRANGE)
//DeadCode RDH 26Mar98 						&&	(ai.skill >= SKILL_REGULAR)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 					ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < SHOOTINGRANGE)
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
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MakeForFriendly
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::MakeForFriendly ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveAway
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::MoveAway ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	UWord	roll_pos;
//DeadCode RDH 26Mar98 	SWord	roll_sign;
//DeadCode RDH 26Mar98 	SWord	desiredaoa;
//DeadCode RDH 26Mar98 	SWord deltahdg;
//DeadCode RDH 26Mar98 	UWord	deltahdg_pos;
//DeadCode RDH 26Mar98 	SWord	deltahdg_sign;
//DeadCode RDH 26Mar98 	UWord	elevator_pos;
//DeadCode RDH 26Mar98 	SWord	elevator_sign;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if  		(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			MoveToHdg (HdgIntercept+ANGLES_180Deg);	//get aidesiredroll
//DeadCode RDH 26Mar98 			Math_Lib.Pos (fly.elevator,elevator_pos,elevator_sign);
//DeadCode RDH 26Mar98 			if (elevator_pos > 4000)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				elevator_pos = 4000;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98   			fly.elevator = Math_Lib.UseSign (elevator_pos,elevator_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			deltahdg = fly.chdg - (HdgIntercept+ANGLES_180Deg);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (deltahdg_pos <ANGLES_5Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			MoveToHdg (HdgIntercept+ANGLES_180Deg);	//get aidesiredroll
//DeadCode RDH 26Mar98 			if ((SWord) (classtype->stallangle - fly.aoa) > ANGLES_4Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToPitch (ANGLES_15Deg,6);
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToPitch (ANGLES_15Deg,1);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //{
//DeadCode RDH 26Mar98 //	ReqVel = Max for aircraft
//DeadCode RDH 26Mar98 //	MoveToHdg (HdgIntercept +ANGLES_180Deg);
//DeadCode RDH 26Mar98 //	MoveToPitch (ANGLES_350Deg);
//DeadCode RDH 26Mar98 }	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		AccidentalSpinOut
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	similar to SpinOut, but longer recovery
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::AccidentalSpinOut ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (0);
//DeadCode RDH 26Mar98 			fly.elevator = -MAXELEVATOR;
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			if ((SWord) fly.turnrate > 0)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				fly.rudder = MAXRUDDER;
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				fly.rudder = -MAXRUDDER;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.manoeuvre = MANOEUVRE_SPINOUT;
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SetControlSurfaces ();
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		AutoShoot
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 12 Jul 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::AutoShoot (Bool manual)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	SWord		deltahdg,reqdeltahdg,reqdeltapitch;
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		time;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SLong	allowedturn;
//DeadCode RDH 26Mar98 	UWord	reqdeltahdg_pos;
//DeadCode RDH 26Mar98 	SWord	reqdeltahdg_sign;
//DeadCode RDH 26Mar98 	UWord	reqdeltapitch_pos;
//DeadCode RDH 26Mar98 	SWord	reqdeltapitch_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (	(Range < (SHOOTINGRANGE+METRES50))
//DeadCode RDH 26Mar98 		&&	(ChkAtDesiredHdg (HdgIntercept,ANGLES_30Deg))
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 		&&	SubjectOnTargetTail(ANGLES_30Deg)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		target.X = ai.unfriendly->World.X;
//DeadCode RDH 26Mar98 		target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 26Mar98 		target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 26Mar98 		InterceptandRange (&target);
//DeadCode RDH 26Mar98 		//time for bullets to arrive at current unfriendly position
//DeadCode RDH 26Mar98 		time = Range / MUZZELVEL;
//DeadCode RDH 26Mar98 		//calc lead position using this time
//DeadCode RDH 26Mar98 		target.X = ai.unfriendly->World.X + (unfriendly->velx * time );
//DeadCode RDH 26Mar98 		target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
//DeadCode RDH 26Mar98 		target.Z = ai.unfriendly->World.Z + (unfriendly->velz * time );
//DeadCode RDH 26Mar98 		InterceptandRange (&target);
//DeadCode RDH 26Mar98 		if (Range <SHOOTINGRANGE)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 22Oct96 			if ((Range <METRES70) && (fly.thrustpercent == 100))
//DeadCode RDH 26Mar98 			if (Range <METRES70)
//DeadCode RDH 26Mar98 				if (manual == TRUE)
//DeadCode RDH 26Mar98 	 				MoveToThrust (-1);									//RDH 01Oct96
//DeadCode RDH 26Mar98 				else
//DeadCode RDH 26Mar98 	 				SimpleMoveToThrust (-1);									//RDH 01Oct96
//DeadCode RDH 26Mar98 			else
//DeadCode RDH 26Mar98 				if (manual == TRUE)
//DeadCode RDH 26Mar98  					MoveToThrust (-100);									//RDH 01Oct96
//DeadCode RDH 26Mar98 				else
//DeadCode RDH 26Mar98 	 				SimpleMoveToThrust (-100);									//RDH 01Oct96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //following section revised										//RDH 06Nov96
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 			if  (	(ChkAtDesiredHdg (HdgIntercept,ANGLES_5Deg))
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 				&&	(DesiredPitchChk (PitchIntercept,ANGLES_5Deg))
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 			if  (	(ChkAtDesiredAcHdg (HdgIntercept,ANGLES_10Deg))
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 				&&	(DesiredAcPitchChk (PitchIntercept,ANGLES_10Deg))
//DeadCode RDH 26Mar98 			if  (	(ChkAtDesiredAcHdg (HdgIntercept,ANGLES_12Deg))//RDH 12Dec96
//DeadCode RDH 26Mar98 				&&	(DesiredAcPitchChk (PitchIntercept,ANGLES_12Deg))//RDH 12Dec96
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 //moved to firabullet
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 //DeadCode RDH 17Oct96 				Art_Int.PersonalThreat(*ai.unfriendly,this);	//JIM 01Sep96
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 //DeadCode JIM 25Oct96 				FireABullet();
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 				if (ai.eventlog->stage==EventLog::TAKEOFF)
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 					Persons_2.UpdateLog(unfriendly->ai.eventlog,0,EventLog::ATTACKED);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				if (ai.manoeuvre!=MANOEUVRE_HEADONOFFSET)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					//do a rudder turn to get onto target exactly
//DeadCode RDH 26Mar98 					allowedturn = ANGLES_30Deg * Timer_Code.FRAMETIME/ 100;		//DAW 31Jul96
//DeadCode RDH 26Mar98 					reqdeltahdg = 	(SWord) ((SWord) hdg - HdgIntercept);
//DeadCode RDH 26Mar98 					Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode RDH 26Mar98 					if (reqdeltahdg_pos < allowedturn)
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						hdg = (ANGLES) HdgIntercept;
//DeadCode RDH 26Mar98 				
//DeadCode RDH 26Mar98 					}else
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						if (reqdeltahdg_sign==Math_Lib.POSITIVE)
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							hdg =  hdg - (ANGLES) allowedturn; 
//DeadCode RDH 26Mar98 						}else
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							hdg =  hdg + (ANGLES) allowedturn;
//DeadCode RDH 26Mar98 						}
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 					allowedturn = ANGLES_30Deg * Timer_Code.FRAMETIME/ 100;		//DAW 31Jul96
//DeadCode RDH 26Mar98 					reqdeltapitch = 	(SWord) ((SWord) pitch - PitchIntercept);
//DeadCode RDH 26Mar98 					Math_Lib.Pos ((SWord) reqdeltapitch, reqdeltapitch_pos,reqdeltapitch_sign);
//DeadCode RDH 26Mar98 					if (reqdeltapitch_pos < allowedturn)
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						pitch = (ANGLES) PitchIntercept;
//DeadCode RDH 26Mar98 				
//DeadCode RDH 26Mar98 					}else
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						if (reqdeltapitch_sign==Math_Lib.POSITIVE)
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							pitch =  pitch - (ANGLES) allowedturn; 
//DeadCode RDH 26Mar98 						}else
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							pitch =  pitch + (ANGLES) allowedturn;
//DeadCode RDH 26Mar98 						}
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 					fly.cpitch = pitch - fly.aoa;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 //new shoot conditions											//RDH 05Dec96
//DeadCode RDH 26Mar98 				if	(	(ai.skill < SKILL_REGULAR)				//RDH 05Dec96
//DeadCode RDH 26Mar98 						||	
//DeadCode RDH 26Mar98 						(
//DeadCode RDH 26Mar98 							(	(ChkAtDesiredAcHdg (HdgIntercept,ANGLES_8Deg))//RDH 12Dec96
//DeadCode RDH 26Mar98 							&&	(DesiredAcPitchChk (PitchIntercept,ANGLES_8Deg))//RDH 12Dec96
//DeadCode RDH 26Mar98 							&&	(ai.skill < SKILL_ACE)
//DeadCode RDH 26Mar98 							)
//DeadCode RDH 26Mar98 						)
//DeadCode RDH 26Mar98 						||
//DeadCode RDH 26Mar98 						(
//DeadCode RDH 26Mar98 							(	(ChkAtDesiredAcHdg (HdgIntercept,ANGLES_5Deg))//RDH 12Dec96
//DeadCode RDH 26Mar98 							&&	(DesiredAcPitchChk (PitchIntercept,ANGLES_5Deg))//RDH 12Dec96
//DeadCode RDH 26Mar98 							)
//DeadCode RDH 26Mar98 						)
//DeadCode RDH 26Mar98 					)											//RDH 05Dec96
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 						if (	(ai.eventlog->stage==EventLog::TAKEOFF)
//DeadCode RDH 26Mar98 							 &&	(unfriendly->ai.eventlog->stage!=EventLog::TAKEOFF)
//DeadCode RDH 26Mar98 							)
//DeadCode RDH 26Mar98 						Persons_2.UpdateLog(unfriendly->ai.eventlog,0,EventLog::ATTACKED);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 					FireABullet();									//JIM 25Oct96
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 //preceding section revised										//RDH 06Nov96
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				if (ai.unfriendly == Manual_Pilot.ControlledAC2)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					_Miles.SequenceAudible(FIL_MUSIC_PLAYER_RUNS);
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}	
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		FireABullet
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Sat 13 Jul 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::FireABullet()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	timeleft;
//DeadCode RDH 26Mar98 	WeapAnimData*	weapon;										//RJS 29Aug96
//DeadCode RDH 26Mar98 	SLong			xpos, ypos, zpos;							//RJS 29Aug96
//DeadCode RDH 26Mar98 	UWord			index;										//RJS 03Sep96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	timeleft = weap.ShootDelay-Timer_Code.FRAMETIME;//DAW 31Jul96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (timeleft<0)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		Art_Int.PersonalThreat(*ai.unfriendly,this);				//RDH 17Oct96
//DeadCode RDH 26Mar98 		WorldStuff*	worldptr = mobileitem::currworld;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  		timeleft = 12;											//RDH 01Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  		Trans_Obj.PlayGunSound((mobileitem* )this,*worldptr);//RDH 12Jul96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		for (index = 0; index < 4; index++)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,LT_BULLET);
//DeadCode RDH 26Mar98 			if (   (weapon)
//DeadCode RDH 26Mar98 				&& (weapon->LoadedStores > 0)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 					Trans_Obj.LaunchOneGunBullet((mobileitem* )this,GunfireShape,xpos,ypos,zpos,*worldptr);
//DeadCode RDH 26Mar98 				 	weapon->LoadedStores--;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	weap.ShootDelay = timeleft;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TurningFight
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	attempt to lead, find Hdgintercept and delta, set roll
//DeadCode RDH 26Mar98 //				roll should not give alt lose
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::TurningFight ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
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
//DeadCode RDH 26Mar98 //DeadCode RDH 12Jul96 			tmp =fly.chdg ;
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
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }		
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		LowGYoYo
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::LowGYoYo ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
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
//DeadCode RDH 26Mar98 			dhdg = (SWord) (fly.chdg - HdgIntercept);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 			if (dhdg_pos < ANGLES_45Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				dhdg_pos = 5*dhdg_pos/4;  
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		 	ai.desiredroll = (ANGLES) FindRequiredRoll (dhdg,CombatReqBankData);
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
//DeadCode RDH 26Mar98 			dhdg = (SWord) (fly.chdg - HdgIntercept);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 			if (dhdg_pos < ANGLES_45Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				dhdg_pos = 5*dhdg_pos/4;  
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		 	ai.desiredroll = (ANGLES) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		VerticalLoop
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::VerticalLoop ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (500);
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			MoveToRoll (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			if  (		(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					||(
//DeadCode RDH 26Mar98 						(MoveToDesiredPitch (ANGLES_340Deg,ANGLES_20Deg))
//DeadCode RDH 26Mar98 						&&	(fly.acroll < ANGLES_90Deg)			//RDH 24Jul96
//DeadCode RDH 26Mar98 						&&	(fly.acroll > ANGLES_270Deg)		//RDH 24Jul96
//DeadCode RDH 26Mar98 					  )											//RDH 24Jul96
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (3000);
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (	(fly.acroll < ANGLES_90Deg)					//RDH 24Jul96
//DeadCode RDH 26Mar98 				&&  (fly.acroll > ANGLES_270Deg))				//RDH 24Jul96
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToRoll (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			fly.elevator = HEAVYPULLELEVATOR;
//DeadCode RDH 26Mar98 			if ( 		(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					|| (	(DesiredPitchChk (ANGLES_0Deg,ANGLES_10Deg))
//DeadCode RDH 26Mar98 						&& (fly.acroll >> ANGLES_90Deg)			//RDH 24Jul96
//DeadCode RDH 26Mar98 						&&  (fly.acroll << ANGLES_270Deg))		//RDH 24Jul96
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ImmelmannTurn
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::ImmelmannTurn ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord 	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			MoveToThrust (100);
//DeadCode RDH 26Mar98 			MoveToRoll (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			MoveToAoA (ANGLES_2Deg);
//DeadCode RDH 26Mar98 			deltaroll = (SWord) (ANGLES_0Deg - fly.acroll);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 			if (deltaroll_pos <ANGLES_10Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;	
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{	
//DeadCode RDH 26Mar98 			MoveToRoll (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 //DeadCode RDH 23Oct96 			MoveToAoA (ANGLES_10Deg - (fly.highest_aoa - fly.aoa));
//DeadCode RDH 26Mar98 			fly.elevator = HEAVYPULLELEVATOR;
//DeadCode RDH 26Mar98 			if (SWord(fly.highest_aoa) > STALL_ANGLE_MINUSONE)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (	((SWord)	pitch > ANGLES_30Deg)
//DeadCode RDH 26Mar98 				 || (vel < 350)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (800);
//DeadCode RDH 26Mar98 				if ((SWord)fly.turnrate >= 0)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					ai.desiredroll = ANGLES_90Deg;
//DeadCode RDH 26Mar98 			 		fly.aileron = (SWord) MAXAILERON/100;
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					ai.desiredroll = ANGLES_270Deg;
//DeadCode RDH 26Mar98 			 		fly.aileron = -(SWord) MAXAILERON/100;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;	
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (ai.desiredroll == ANGLES_90Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToRudder ((SWord) MAXRUDDER);
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToRudder ((SWord)RUDDER_B000);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jul96 			MoveToAoA (STALL_ANGLE_MINUSONE - (fly.highest_aoa - fly.aoa));
//DeadCode RDH 26Mar98 			MoveToAoA (ANGLES_10Deg - (fly.highest_aoa - fly.aoa));
//DeadCode RDH 26Mar98 //DeadCode RDH 16May96 			MoveToRoll (ai.desiredroll,1);
//DeadCode RDH 26Mar98 			deltaroll = (SWord) (ai.desiredroll - fly.acroll);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 			if (	(deltaroll_pos <ANGLES_15Deg)
//DeadCode RDH 26Mar98 				|| (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (200);
//DeadCode RDH 26Mar98 				if (ai.desiredroll == ANGLES_90Deg)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					ai.desiredroll = ANGLES_45Deg;
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					ai.desiredroll = ANGLES_315Deg;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			MoveToRudder (0);
//DeadCode RDH 26Mar98 			ANGLES temp = fly.chdg;
//DeadCode RDH 26Mar98 			MoveToAoA (ANGLES_10Deg - (fly.highest_aoa - fly.aoa));
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jul96 			MoveToAoA (STALL_ANGLE_MINUSONE - (fly.highest_aoa - fly.aoa));
//DeadCode RDH 26Mar98 			MoveToRoll (ANGLES_0Deg,1);
//DeadCode RDH 26Mar98 			fly.aileron = fly.aileron/4;
//DeadCode RDH 26Mar98 			deltaroll = (SWord) (ai.desiredroll - fly.acroll);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 			if 	(		(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					||	(deltaroll_pos <ANGLES_20Deg)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 				ai.ManStep = PHASE4;
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 				SetManoeuvreTime (400);
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		HeadOnOffset
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::HeadOnOffset ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	UWord	roll_pos,turn_pos;
//DeadCode RDH 26Mar98 	SWord	turn_sign,roll_sign;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			MoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if  (	(!SubjectFacingTarget(ANGLES_15Deg))
//DeadCode RDH 26Mar98 				 || (!TargetFacingSubject(ANGLES_15Deg))
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			MoveToPitch (PitchIntercept,1);
//DeadCode RDH 26Mar98 			MoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 			if  (	(Range < METRES150)
//DeadCode RDH 26Mar98 				&&	(ai.skill < SKILL_VETERAN)
//DeadCode RDH 26Mar98 				&&	(ai.morale < MORALE_MEDIUM)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg + ANGLES_120Deg;
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < METRES80)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg + ANGLES_120Deg;
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	 		fly.aileron =  MAXAILERON;
//DeadCode RDH 26Mar98 			fly.elevator = MEDIUMPULLELEVATOR;
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jul96 			MoveToPitch (PitchIntercept,1);
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jul96 			MoveToHdg (ai.desiredhdg);
//DeadCode RDH 26Mar98 			if  (!SubjectFacingTarget(ANGLES_85Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			TightTurn (FT_500);
//DeadCode RDH 26Mar98 			if 	(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		Immelmann
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	not used and so not coded for Flying Corps
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::Immelmann ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		StayWithPrey
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	As target looses alt, stay until explosion or hits ground or alt <???
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::StayWithPrey ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
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
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TightTurn
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 12 Jul 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::TightTurn (SLong recovery_alt)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SWord	sinturn,costurn;
//DeadCode RDH 26Mar98 	SWord	turn;
//DeadCode RDH 26Mar98 	SLong	desiredroll,deltax,deltaz,delta; 
//DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		time;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos;
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 26Mar98 	SWord dhdg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	target.X = ai.unfriendly->World.X;
//DeadCode RDH 26Mar98 	target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 26Mar98 	target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 26Mar98 	InterceptandRange (&target);
//DeadCode RDH 26Mar98 	TightTurnSub (recovery_alt,target);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TightTurnSub
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 10 Sep 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::TightTurnSub (SLong recovery_alt,COORDS3D	target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong		time;
//DeadCode RDH 26Mar98 	SWord	sinturn,costurn;
//DeadCode RDH 26Mar98 	SWord	turn;
//DeadCode RDH 26Mar98 	SLong	desiredroll,deltax,deltaz,delta; 
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 	SWord	deltapitch,maxroll,minroll;
//DeadCode RDH 26Mar98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos,targetroll,olddesiredroll_pos;
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 26Mar98 	SWord dhdg;
//DeadCode RDH 26Mar98 	dhdg = (SWord) (fly.chdg - HdgIntercept);
//DeadCode RDH 26Mar98 	Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		if (	(TargetFacingSubject(ANGLES_70Deg))
//DeadCode RDH 26Mar98 			&& 	(((SWord) PitchIntercept) > 0)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_0Deg;
//DeadCode RDH 26Mar98 		}	
//DeadCode RDH 26Mar98 		deltapitch = PitchIntercept - fly.cpitch;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if	(	(SubjectOnTargetTail(ANGLES_50Deg))
//DeadCode RDH 26Mar98 		&&	(SubjectFacingTarget(ANGLES_70Deg))
//DeadCode RDH 26Mar98 		&&	(Range < (SHOOTINGRANGE-METRES20))
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		time = dhdg_pos /400;
//DeadCode RDH 26Mar98 		if (time > 20)
//DeadCode RDH 26Mar98 			time =20;
//DeadCode RDH 26Mar98 		turn = time * unfriendly->fly.turnrate/10;	//in s
//DeadCode RDH 26Mar98 		turn = unfriendly->fly.chdg + turn;
//DeadCode RDH 26Mar98 		delta = unfriendly->vel * time;		//cm/s
//DeadCode RDH 26Mar98 		Math_Lib.high_sin_cos((ANGLES)turn,sinturn,costurn);
//DeadCode RDH 26Mar98 		deltax = MULSHSIN(sinturn,delta,ANGLES_SHIFT);
//DeadCode RDH 26Mar98 		deltaz = MULSHSIN(costurn,delta,ANGLES_SHIFT);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		//calc lead position using this time
//DeadCode RDH 26Mar98 		target.X = ai.unfriendly->World.X + deltax;
//DeadCode RDH 26Mar98 		target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
//DeadCode RDH 26Mar98 		target.Z = ai.unfriendly->World.Z + deltaz;
//DeadCode RDH 26Mar98 		InterceptandRange (&target);
//DeadCode RDH 26Mar98 		dhdg = (SWord) (fly.chdg - HdgIntercept);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		Math_Lib.Pos ((SWord)ai. desiredroll,olddesiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	 	ai.desiredroll = (ANGLES) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		Math_Lib.Pos ((SWord)ai. desiredroll,olddesiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 		dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 	 	ai.desiredroll = (ANGLES) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos ((SWord)ai. desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (	(deltapitch > ANGLES_2Deg)
//DeadCode RDH 26Mar98 		&&	(!(TargetFacingSubject(ANGLES_20Deg)))
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (olddesiredroll_pos <= desiredroll_pos)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			desiredroll_pos = olddesiredroll_pos - 64;
//DeadCode RDH 26Mar98 			if (desiredroll_pos > ANGLES_20Deg)
//DeadCode RDH 26Mar98 				ai.desiredroll = (ANGLES) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos ((SWord)ai. desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 	if (	(deltapitch < ((SWord)ANGLES_350Deg))
//DeadCode RDH 26Mar98 		&& (desiredroll_pos >= MAXCOMBATROLL)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				desiredroll_pos = ANGLES_180Deg - MAXCOMBATROLL;
//DeadCode RDH 26Mar98 				ai.desiredroll = (ANGLES) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	SLong groundlevel;											//RDH 18Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ( target.Y >= FT_1500)									//RDH 18Dec96
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		TightTurnSubSub (deltapitch);
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		groundlevel = Land_Scape.GetGroundLevel(*this);		//RDH 18Dec96
//DeadCode RDH 26Mar98 		if (	(World.Y < (groundlevel + FT_500))				//RDH 20Dec96
//DeadCode RDH 26Mar98 			&&	((fly.cpitch +ANGLES_20Deg) >> ANGLES_180Deg)	//RDH 20Dec96
//DeadCode RDH 26Mar98 			)													//RDH 20Dec96
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_340Deg,1);						//RDH 20Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		if (ai.unfriendly == Manual_Pilot.ControlledAC2)		//RDH 18Dec96
//DeadCode RDH 26Mar98 		{														//RDH 18Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 20Dec96 			groundlevel = Land_Scape.GetGroundLevel(*this);		//RDH 18Dec96
//DeadCode RDH 26Mar98 			if (World.Y > (groundlevel + FT_300))				//DAW 20Dec96
//DeadCode RDH 26Mar98 			{														//RDH 18Dec96
//DeadCode RDH 26Mar98 				TightTurnSubSub (deltapitch);						//RDH 18Dec96
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		//## attempt to disengage
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 		MoveToPitch (ANGLES_5Deg,1);
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 	 	MoveToRoll (ANGLES_20Deg,1);
//DeadCode RDH 26Mar98 		MoveToThrust (100);
//DeadCode RDH 26Mar98 		MoveToPitch (ANGLES_5Deg,1);
//DeadCode RDH 26Mar98 	 	MoveToRoll (ANGLES_45Deg,1);
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TightTurnSubSub
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Sun 13 Oct 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::TightTurnSubSub (SWord	deltapitch)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	desiredroll; 
//DeadCode RDH 26Mar98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos;
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		//now do pitch
//DeadCode RDH 26Mar98 		Math_Lib.Pos (((SWord)fly.aoa),aoa_pos,aoa_sign);
//DeadCode RDH 26Mar98 		if ((SWord)aoa_pos > (SWord) STALL_ANGLE_MINUSONE)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (fly.elevator < 0)
//DeadCode RDH 26Mar98 //DeadCode RDH 31Oct96 				fly.elevator = fly.elevator + Timer_Code.FRAMETIME* ELEVATOR_DELTA;//DAW 31Jul96
//DeadCode RDH 26Mar98 				fly.elevator = 0;								//RDH 31Oct96
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (	(deltapitch > 0)
//DeadCode RDH 26Mar98 				&&	((SWord) fly.cpitch < ANGLES_15Deg)	//sustainable max climbrate
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				MoveToPitch((ANGLES)PitchIntercept,2 + (ai.skill /2));
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				if (	(fly.rotr_xbl >=0)
//DeadCode RDH 26Mar98 						||	(ai.desiredroll << ANGLES_10Deg)	//JIM 24Jul96
//DeadCode RDH 26Mar98 						||	(ai.desiredroll >> ANGLES_350Deg)	//JIM 24Jul96
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 				{//can push down
//DeadCode RDH 26Mar98 					MoveToPitch((ANGLES)PitchIntercept,6);
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 31Oct96 					fly.elevator = fly.elevator - Timer_Code.FRAMETIME* ELEVATOR_DELTA;//DAW 31Jul96
//DeadCode RDH 26Mar98 					fly.elevator = 0;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			Math_Lib.Pos ((SWord)ai. desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 			if ((deltapitch > ANGLES_5Deg) && (desiredroll_pos > ANGLES_20Deg))
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 				if (deltapitch > ANGLES_15Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 						desiredroll_pos = ANGLES_20Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 				}else
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 					desiredroll = ANGLES_20Deg +  (desiredroll_pos - ANGLES_20Deg) *
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 								(ANGLES_15Deg - deltapitch) / ANGLES_15Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 					desiredroll_pos = (ANGLES) desiredroll;
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 				}
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 				ai.desiredroll = (ANGLES) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 01Nov96 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (	(fly.cpitch > ANGLES_5Deg)
//DeadCode RDH 26Mar98 				&& (desiredroll_pos > ANGLES_20Deg)
//DeadCode RDH 26Mar98 				&& (deltapitch > 0)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				if (fly.cpitch > ANGLES_15Deg)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 						desiredroll_pos = ANGLES_20Deg;
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					desiredroll = ANGLES_20Deg +  (desiredroll_pos - ANGLES_20Deg) *
//DeadCode RDH 26Mar98 								(ANGLES_15Deg - fly.cpitch) / ANGLES_15Deg;
//DeadCode RDH 26Mar98 					desiredroll_pos = (ANGLES) desiredroll;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 				ai.desiredroll = (ANGLES) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1 + (ai.skill /3));						//RDH 26Jul96
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		fly.unmod_elevator = fly.elevator;
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ManoeuvreTimeLeft
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 19 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 SWord AirStruc::ManoeuvreTimeLeft ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	return(TimeLeft());
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //Simple acm routines											//RDH 11Oct96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SimpleTopCover
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	The followers are supposed to go near to home line or
//DeadCode RDH 26Mar98 //				not depending on skill
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleTopCover ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98   if (formpos == 0)
//DeadCode RDH 26Mar98   {//leader
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_0Deg - ANGLES_30Deg +
//DeadCode RDH 26Mar98  						(ANGLES)(ANGLES_60Deg * Math_Lib.rnd(2)); 
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_7Deg);
//DeadCode RDH 26Mar98 		if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_0Deg);
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
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_0Deg);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (AllOnTopCover ())								//JIM 25Nov96
//DeadCode RDH 26Mar98 			{													//JIM 25Nov96
//DeadCode RDH 26Mar98 				Art_Int.AllBreakOff(this);	//fly.leadflight);	//JIM 25Nov96
//DeadCode RDH 26Mar98 			 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_SQUADRONREGROUPED,NULL);
//DeadCode RDH 26Mar98 			}													//JIM 25Nov96
//DeadCode RDH 26Mar98 			else												//JIM 25Nov96
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
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_0Deg - ANGLES_30Deg +
//DeadCode RDH 26Mar98  						(ANGLES)(ANGLES_60Deg * Math_Lib.rnd(2)); 
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_10Deg);
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_7Deg);				//RDH 13Dec96
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
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_0Deg);
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_8Deg);
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_7Deg);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98   }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SimpleTightClimbingTurn
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Sat 30 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::SimpleTightClimbingTurn (ANGLES desiredpitch)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	deltapitch = desiredpitch - fly.cpitch;
//DeadCode RDH 26Mar98 	PitchIntercept = desiredpitch; 
//DeadCode RDH 26Mar98 	SimpleTightTurnSubSub (deltapitch);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SimpleLookAround
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleLookAround ()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (6000);
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_0Deg - ANGLES_45Deg +
//DeadCode RDH 26Mar98  						(ANGLES)(ANGLES_90Deg * Math_Lib.rnd(2)); 
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (World.Y > classtype->fightceiling)
//DeadCode RDH 26Mar98 				SimpleTightClimbingTurn (ANGLES_0Deg);
//DeadCode RDH 26Mar98 			else
//DeadCode RDH 26Mar98 				SimpleTightClimbingTurn (ANGLES_7Deg);			//RDH 14Nov96
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 		    	ai.ManStep = PHASE0;
//DeadCode RDH 26Mar98 				if (formpos == 0)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					if (AllButLdrNotOnCombat ())				//RDH 26Nov96
//DeadCode RDH 26Mar98 					{											//RDH 26Nov96
//DeadCode RDH 26Mar98 						ai.manoeuvre=MANOEUVRE_TOPCOVER;		//RDH 26Nov96
//DeadCode RDH 26Mar98 					}else										//RDH 26Nov96
//DeadCode RDH 26Mar98 					{											//RDH 26Nov96
//DeadCode RDH 26Mar98 						ai.manoeuvre=MANOEUVRE_LOOKROUND;		//RDH 26Nov96
//DeadCode RDH 26Mar98 					}											//RDH 26Nov96
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
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		BarrelRoll
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleBarrelRoll ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SimpleScissors ( );
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		Scissors
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleScissors ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			ai.desiredhdg = fly.chdg + ANGLES_120Deg; 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_2Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_100Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg - ANGLES_240Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_2Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_100Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg + ANGLES_240Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MildScissors
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleMildScissors ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			ai.desiredhdg = fly.chdg - ANGLES_15Deg; 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_0Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg + ANGLES_30Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_0Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg - ANGLES_30Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveToDesiredHdg
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
//DeadCode RDH 26Mar98 Bool	AirStruc::SimpleMoveToDesiredHdg (ANGLES desiredhdg,ANGLES target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	Bool	retval;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SimpleMoveToHdg (desiredhdg);
//DeadCode RDH 26Mar98 	retval = ChkAtDesiredHdg (desiredhdg,target);
//DeadCode RDH 26Mar98 	return (retval);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98  //Procedure		MoveToHdg
//DeadCode RDH 26Mar98  //Author		R. Hyde 
//DeadCode RDH 26Mar98  //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Description	based on difference between desired and actual hdg, fix aileron
//DeadCode RDH 26Mar98  //				to give a roll, morale and skill will fix maxroll				
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Inputs		
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Returns	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98  void	AirStruc::SimpleMoveToHdg (ANGLES desiredhdg)
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  {
//DeadCode RDH 26Mar98  	SWord	reqdeltahdg, reqdeltahdg_sign;
//DeadCode RDH 26Mar98 	UWord	reqdeltahdg_pos;
//DeadCode RDH 26Mar98  	SWord	reqroll,deltaroll;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	reqdeltahdg = 	fly.chdg - desiredhdg;
//DeadCode RDH 26Mar98  	Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode RDH 26Mar98  	reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 //DeadCode RDH 30Mar96  	deltaroll = (SWord) (reqroll - fly.acroll);
//DeadCode RDH 26Mar98 	ai.desiredroll = (ANGLES) reqroll;
//DeadCode RDH 26Mar98 	SimpleMoveToRoll (reqroll);
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  }
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
//DeadCode RDH 26Mar98 void	AirStruc::SimpleMoveToRoll (SWord desiredroll)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {	//RequiredDRollSub: parameter is desired roll, return val is delta roll
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	roll += (ANGLES) (RequiredDRollSub (desiredroll));
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
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
//DeadCode RDH 26Mar98 SWord	AirStruc::SimpleMoveToDesiredPitch (ANGLES desiredpitch,ANGLES target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	retval;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	PitchIntercept = desiredpitch;
//DeadCode RDH 26Mar98 	AutoCalcPitch();
//DeadCode RDH 26Mar98 	retval = DesiredPitchChk (desiredpitch,target);
//DeadCode RDH 26Mar98 	return (retval);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		StraightandLevel
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleStraightandLevel ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord 	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (80);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 	 		ai.desiredroll = ANGLES_0Deg;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (World.Y < FT_1000)
//DeadCode RDH 26Mar98 				PitchIntercept = ANGLES_4Deg;
//DeadCode RDH 26Mar98 			else
//DeadCode RDH 26Mar98 				PitchIntercept = ANGLES_0Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			deltaroll = (SWord) (ai.desiredroll - fly.acroll);
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 			if (deltaroll_pos <ANGLES_2Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (World.Y < FT_1000)
//DeadCode RDH 26Mar98 				PitchIntercept = ANGLES_10Deg;
//DeadCode RDH 26Mar98 			else
//DeadCode RDH 26Mar98 				PitchIntercept = ANGLES_0Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		AcmSideSlip
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleAcmSideSlip ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	SimpleTurningFight ();
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SpinRecovery
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleSpinRecovery ()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SimpleTurningFight ();
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SpinOut
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleSpinOut ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltayaw_pos;
//DeadCode RDH 26Mar98 	SWord	deltayaw_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	SLong groundlevel = _Collide.LowestSafeAlt(this,			//RDH 16Dec96
//DeadCode RDH 26Mar98 											this->pitch,		//RDH 16Dec96
//DeadCode RDH 26Mar98 											this->roll);		//RDH 16Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (1);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			SetManoeuvreTime (600);
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_45Deg;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if ((World.Y - groundlevel) < FT_1000)				//RDH 16Dec96
//DeadCode RDH 26Mar98 				PitchIntercept =  ANGLES_8Deg;					//RDH 16Dec96
//DeadCode RDH 26Mar98 			else												//RDH 16Dec96
//DeadCode RDH 26Mar98 				PitchIntercept =  ANGLES_305Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.desiredroll = ANGLES_0Deg;
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (400);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if ((World.Y - groundlevel) < FT_1000)				//RDH 16Dec96
//DeadCode RDH 26Mar98 				PitchIntercept =  ANGLES_8Deg;					//RDH 16Dec96
//DeadCode RDH 26Mar98 			else												//RDH 16Dec96
//DeadCode RDH 26Mar98 			PitchIntercept =  ANGLES_340Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 	 			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 		SetControlSurfaces ();
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		DiveforHome
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleDiveforHome ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	temp_range;
//DeadCode RDH 26Mar98 	temp_range = Range; 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (World.Y < FT_1000)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				PitchIntercept =  ANGLES_0Deg;
//DeadCode RDH 26Mar98 				AutoCalcPitch();
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				PitchIntercept =  ANGLES_340Deg;
//DeadCode RDH 26Mar98 				AutoCalcPitch();
//DeadCode RDH 26Mar98 				InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 				SimpleMoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < MILES01)
//DeadCode RDH 26Mar98 			{//within mile of home
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			Range = temp_range; 	
//DeadCode RDH 26Mar98 			if (Range > MILES01)
//DeadCode RDH 26Mar98 			{//mile from action, reconsider
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ClimbforHome
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleClimbforHome ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	temp_range;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	temp_range = Range; 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 			ai.desiredhdg = HdgIntercept; 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			Range = temp_range; 	
//DeadCode RDH 26Mar98 			if (Range < SHOOTINGRANGE)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			PitchIntercept =  ANGLES_10Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToHdg (ai.desiredhdg);
//DeadCode RDH 26Mar98 			Range = temp_range; 	
//DeadCode RDH 26Mar98 			if (Range > BREAKOFFRANGE)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		StraightDive
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleStraightDive ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord 	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (90);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ANGLES_0Deg);
//DeadCode RDH 26Mar98 			PitchIntercept =  ANGLES_340Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			if (World.Y < FT_1000)
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			if  (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		StandOnTail
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleStandOnTail ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		time;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (800);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			target.X = ai.unfriendly->World.X;
//DeadCode RDH 26Mar98 			target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 26Mar98 			target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 26Mar98 			InterceptandRange (&target);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			//time for bullets to arrive at current unfriendly position
//DeadCode RDH 26Mar98 			time = Range / MUZZELVEL;
//DeadCode RDH 26Mar98 			//calc lead position using this time
//DeadCode RDH 26Mar98 			target.X = ai.unfriendly->World.X + (unfriendly->velx * time );
//DeadCode RDH 26Mar98 			target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
//DeadCode RDH 26Mar98 			target.Z = ai.unfriendly->World.Z + (unfriendly->velz * time );
//DeadCode RDH 26Mar98 			InterceptandRange (&target);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			SimpleMoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 			if (vel < MPH55)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				if ((SWord) fly.cpitch < (SWord) PitchIntercept)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					AutoCalcPitch();
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					AutoCalcPitch();
//DeadCode RDH 26Mar98 					FireABullet();
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ShootToFrighten
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleShootToFrighten ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (200);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 			   	ai.ManStep = PHASE0;
//DeadCode RDH 26Mar98 				ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			SimpleTightTurn (FT_1000);
//DeadCode RDH 26Mar98 			FireABullet();
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		GoHome
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleGoHome ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
//DeadCode RDH 26Mar98 	SLong	temp_range;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	temp_range = Range; 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 			ai.desiredhdg = HdgIntercept; 
//DeadCode RDH 26Mar98 			Range = temp_range;
//DeadCode RDH 26Mar98 //jink a bit possibly
//DeadCode RDH 26Mar98 			if	(		TargetOnSubjectTail(ANGLES_10Deg)
//DeadCode RDH 26Mar98 					&&	(Range < 4 * SHOOTINGRANGE)
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
//DeadCode RDH 26Mar98 				InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 				ai.desiredhdg = HdgIntercept; 
//DeadCode RDH 26Mar98 				Range = temp_range;
//DeadCode RDH 26Mar98 				if	(		TargetOnSubjectTail(ANGLES_10Deg)
//DeadCode RDH 26Mar98 						&&	(Range < 4 * SHOOTINGRANGE)
//DeadCode RDH 26Mar98 						&&	(ai.skill >= SKILL_REGULAR)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 					ai.desiredhdg = HdgIntercept + ANGLES_340Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < SHOOTINGRANGE)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			PitchIntercept =  ANGLES_0Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToHdg (ai.desiredhdg);
//DeadCode RDH 26Mar98 			if (Range > BREAKOFFRANGE +METRES1400)
//DeadCode RDH 26Mar98 //DeadCode RDH 25Oct96 			if (Range > BREAKOFFRANGE + METRES1400)
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
//DeadCode RDH 26Mar98 				InterceptandRange (&ai.homebase->World);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				ai.desiredhdg = HdgIntercept; 
//DeadCode RDH 26Mar98 				Range = temp_range;
//DeadCode RDH 26Mar98 				if	(		TargetOnSubjectTail(ANGLES_10Deg)
//DeadCode RDH 26Mar98 						&&	(Range < 4 * SHOOTINGRANGE)
//DeadCode RDH 26Mar98 						&&	(ai.skill >= SKILL_REGULAR)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 					ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < SHOOTINGRANGE)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			PitchIntercept =  ANGLES_0Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToHdg (ai.desiredhdg);
//DeadCode RDH 26Mar98 //DeadCode RDH 25Oct96 			if (Range > BREAKOFFRANGE + METRES1400)
//DeadCode RDH 26Mar98 			if (Range > BREAKOFFRANGE+METRES1400)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveAway
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleMoveAway ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	UWord	roll_pos;
//DeadCode RDH 26Mar98 	SWord	roll_sign;
//DeadCode RDH 26Mar98 	SWord	desiredaoa;
//DeadCode RDH 26Mar98 	SWord deltahdg;
//DeadCode RDH 26Mar98 	UWord	deltahdg_pos;
//DeadCode RDH 26Mar98 	SWord	deltahdg_sign;
//DeadCode RDH 26Mar98 	UWord	elevator_pos;
//DeadCode RDH 26Mar98 	SWord	elevator_sign;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if  		(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			PitchIntercept =  ANGLES_0Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToHdg (HdgIntercept+ANGLES_180Deg);	//get aidesiredroll
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			deltahdg = fly.chdg - (HdgIntercept+ANGLES_180Deg);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (deltahdg_pos <ANGLES_5Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SimpleMoveToHdg (HdgIntercept+ANGLES_180Deg);	//get aidesiredroll
//DeadCode RDH 26Mar98 			PitchIntercept =  ANGLES_4Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		AccidentalSpinOut
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	similar to SpinOut, but longer recovery
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleAccidentalSpinOut ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SimpleSpinOut ( );
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TurningFight
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	attempt to lead, find Hdgintercept and delta, set roll
//DeadCode RDH 26Mar98 //				roll should not give alt lose
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleTurningFight ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
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
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
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
//DeadCode RDH 26Mar98 			SimpleTightTurn (FT_1000);
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }		
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		LowGYoYo
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleLowGYoYo ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	UWord	dhdg_pos;
//DeadCode RDH 26Mar98 	SWord	dhdg_sign;
//DeadCode RDH 26Mar98 	SWord dhdg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			dhdg = (SWord) (fly.chdg - HdgIntercept);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 			if (dhdg_pos < ANGLES_45Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				dhdg_pos = 5*dhdg_pos/4;  
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		 	ai.desiredroll = (ANGLES) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);
//DeadCode RDH 26Mar98 			if (	(SimpleMoveToDesiredPitch (ANGLES_340Deg,ANGLES_15Deg))
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
//DeadCode RDH 26Mar98 			dhdg = (SWord) (fly.chdg - HdgIntercept);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 			if (dhdg_pos < ANGLES_45Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				dhdg_pos = 5*dhdg_pos/4;  
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		 	ai.desiredroll = (ANGLES) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		VerticalLoop
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleVerticalLoop ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_0Deg - ANGLES_45Deg +
//DeadCode RDH 26Mar98  						(ANGLES)(ANGLES_90Deg * Math_Lib.rnd(2)); 
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_15Deg);
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_7Deg);				//RDH 13Dec96
//DeadCode RDH 26Mar98 			if  (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98  				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ImmelmannTurn
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 13 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleImmelmannTurn ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_15Deg);
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_7Deg);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		HeadOnOffset
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleHeadOnOffset ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	UWord	roll_pos,turn_pos;
//DeadCode RDH 26Mar98 	SWord	turn_sign,roll_sign;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if  (	(!SubjectFacingTarget(ANGLES_15Deg))
//DeadCode RDH 26Mar98 				 || (!TargetFacingSubject(ANGLES_15Deg))
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToHdg (HdgIntercept);
//DeadCode RDH 26Mar98 			if  (	(Range < METRES150)
//DeadCode RDH 26Mar98 				&&	(ai.skill < SKILL_VETERAN)
//DeadCode RDH 26Mar98 				&&	(ai.morale < MORALE_MEDIUM)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg + ANGLES_120Deg;
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (Range < METRES80)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.desiredhdg = fly.chdg + ANGLES_120Deg;
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToHdg (ai.desiredhdg);
//DeadCode RDH 26Mar98 			if  (!SubjectFacingTarget(ANGLES_85Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			SimpleTightTurn (FT_500);
//DeadCode RDH 26Mar98 			if 	(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		StayWithPrey
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	As target looses alt, stay until explosion or hits ground or alt <???
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleStayWithPrey ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll;
//DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 26Mar98 	UWord	acroll_pos;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
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
//DeadCode RDH 26Mar98 			SimpleTightTurn (FT_500);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		GainHeight
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 12 Dec 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleGainHeight ( )
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	
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
//DeadCode RDH 26Mar98 				ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
//DeadCode RDH 26Mar98 				SimpleTurningFight ();
//DeadCode RDH 26Mar98 				break;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
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
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_10Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);							//RDH 14May96
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SplitS
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
//DeadCode RDH 26Mar98 void	AirStruc::SimpleSplitS ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord 	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_180Deg;
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			fly.elevator = 0;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			deltaroll = (SWord) (ai.desiredroll - fly.acroll);
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 			if (deltaroll_pos <ANGLES_10Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 	 			SimpleMoveToThrust (0);
//DeadCode RDH 26Mar98 				ai.lastdeltapitch = ANGLES_0Deg;
//DeadCode RDH 26Mar98 				SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_280Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			if ( 		(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					|| (    DesiredPitchChk (ANGLES_270Deg,ANGLES_20Deg)
//DeadCode RDH 26Mar98 						)										//RDH 24Jul96
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 	 			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ZoomandDrop
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
//DeadCode RDH 26Mar98 void	AirStruc::SimpleZoomandDrop ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord phase,deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	phase = (SWord) ai.ManStep;
//DeadCode RDH 26Mar98 	switch (phase)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			ai.desiredroll = ANGLES_0Deg;
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (0);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);
//DeadCode RDH 26Mar98 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 			if (deltaroll_pos <ANGLES_20Deg)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (500);
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_70Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			if (	(SimpleMoveToDesiredPitch (ANGLES_70Deg,ANGLES_10Deg))
//DeadCode RDH 26Mar98 				||	(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98  				SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (SimpleMoveToDesiredPitch (ANGLES_315Deg,ANGLES_10Deg))
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		DiveAndZoom
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
//DeadCode RDH 26Mar98 void	AirStruc::SimpleDiveAndZoom ()
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	deltapitch_pos,deltapitch_sign;
//DeadCode RDH 26Mar98 	SLong	temp_range;
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		t,actualrange;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98  	SWord		deltaroll;										//RDH 14Mar96
//DeadCode RDH 26Mar98 	SWord		easestickforward;
//DeadCode RDH 26Mar98 	ANGLES		local_PI;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	local_PI  = PitchIntercept;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			SimpleMoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 29Mar96 			FlatTurn ();
//DeadCode RDH 26Mar98  			if ((vel - unfriendly->vel) < (unfriendly->vel/4))
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  				SimpleGatherSpeed ();
//DeadCode RDH 26Mar98  			}else
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  				SimpleLeadUnFriendly ();
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98  			if  (Range < METRES300)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98  				ai.ManStep = PHASE2;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98  			if (local_PI << ANGLES_90Deg)
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE2:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			temp_range = Range; 	
//DeadCode RDH 26Mar98 			SimpleTightTurn (FT_1000);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if  (	(ai.skill < SKILL_VETERAN)
//DeadCode RDH 26Mar98 			  	&&	(ChkAtDesiredHdg (HdgIntercept,ANGLES_5Deg))
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 				FireABullet();
//DeadCode RDH 26Mar98  			if (temp_range < METRES60)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (500);
//DeadCode RDH 26Mar98  				ai.desiredroll = ANGLES_0Deg - ANGLES_45Deg +
//DeadCode RDH 26Mar98  						(ANGLES)(ANGLES_90Deg * Math_Lib.rnd(2)); 
//DeadCode RDH 26Mar98  				ai.ManStep = PHASE3;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE3:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 			TightClimbingTurn (ANGLES_20Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_20Deg);
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_7Deg);
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SetManoeuvreTime (1000);
//DeadCode RDH 26Mar98  				ai.ManStep = PHASE4;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE4:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Oct96 			TightClimbingTurn (ANGLES_10Deg,(SWord)ai.desiredroll);
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_10Deg);
//DeadCode RDH 26Mar98 			SimpleTightClimbingTurn (ANGLES_7Deg);
//DeadCode RDH 26Mar98 			target.X = unfriendly->World.X;
//DeadCode RDH 26Mar98 			target.Y = unfriendly->World.Y;
//DeadCode RDH 26Mar98 			target.Z = unfriendly->World.Z;
//DeadCode RDH 26Mar98  			InterceptandRange (&target);
//DeadCode RDH 26Mar98 			if (	(ChkAtDesiredHdg (HdgIntercept,ANGLES_45Deg))
//DeadCode RDH 26Mar98 				||(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98  			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TightTurn
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleTightTurn (SLong recovery_alt)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SWord	sinturn,costurn;
//DeadCode RDH 26Mar98 	SWord	turn;
//DeadCode RDH 26Mar98 	SLong	desiredroll,deltax,deltaz,delta; 
//DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 26Mar98 	SLong		time;
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos;
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 26Mar98 	SWord dhdg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	target.X = ai.unfriendly->World.X;
//DeadCode RDH 26Mar98 	target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 26Mar98 	target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 26Mar98 	InterceptandRange (&target);
//DeadCode RDH 26Mar98 	SimpleTightTurnSub (recovery_alt,target);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TightTurnSub
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleTightTurnSub (SLong recovery_alt,COORDS3D	target)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong		time;
//DeadCode RDH 26Mar98 	SWord	sinturn,costurn;
//DeadCode RDH 26Mar98 	SWord	turn;
//DeadCode RDH 26Mar98 	SLong	desiredroll,deltax,deltaz,delta; 
//DeadCode RDH 26Mar98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 	SWord	deltapitch,maxroll,minroll;
//DeadCode RDH 26Mar98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos,targetroll,olddesiredroll_pos;
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 26Mar98 	SWord dhdg;
//DeadCode RDH 26Mar98 	dhdg = (SWord) (fly.chdg - HdgIntercept);
//DeadCode RDH 26Mar98 	Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		if (	(TargetFacingSubject(ANGLES_70Deg))
//DeadCode RDH 26Mar98 			&& 	(((SWord) PitchIntercept) > 0)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_0Deg;
//DeadCode RDH 26Mar98 		}	
//DeadCode RDH 26Mar98 		deltapitch = PitchIntercept - fly.cpitch;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if	(	(SubjectOnTargetTail(ANGLES_50Deg))
//DeadCode RDH 26Mar98 		&&	(SubjectFacingTarget(ANGLES_70Deg))
//DeadCode RDH 26Mar98 		&&	(Range < (SHOOTINGRANGE-METRES20))
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		time = dhdg_pos /400;
//DeadCode RDH 26Mar98 		if (time > 20)
//DeadCode RDH 26Mar98 			time =20;
//DeadCode RDH 26Mar98 		turn = time * unfriendly->fly.turnrate/10;	//in s
//DeadCode RDH 26Mar98 		turn = unfriendly->fly.chdg + turn;
//DeadCode RDH 26Mar98 		delta = unfriendly->vel * time;		//cm/s
//DeadCode RDH 26Mar98 		Math_Lib.high_sin_cos((ANGLES)turn,sinturn,costurn);
//DeadCode RDH 26Mar98 		deltax = MULSHSIN(sinturn,delta,ANGLES_SHIFT);
//DeadCode RDH 26Mar98 		deltaz = MULSHSIN(costurn,delta,ANGLES_SHIFT);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		//calc lead position using this time
//DeadCode RDH 26Mar98 		target.X = ai.unfriendly->World.X + deltax;
//DeadCode RDH 26Mar98 		target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
//DeadCode RDH 26Mar98 		target.Z = ai.unfriendly->World.Z + deltaz;
//DeadCode RDH 26Mar98 		InterceptandRange (&target);
//DeadCode RDH 26Mar98 		dhdg = (SWord) (fly.chdg - HdgIntercept);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		Math_Lib.Pos ((SWord)ai. desiredroll,olddesiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	 	ai.desiredroll = (ANGLES) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		Math_Lib.Pos ((SWord)ai. desiredroll,olddesiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 		dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 26Mar98 	 	ai.desiredroll = (ANGLES) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos ((SWord)ai. desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (	(deltapitch > ANGLES_2Deg)
//DeadCode RDH 26Mar98 		&&	(!(TargetFacingSubject(ANGLES_20Deg)))
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (olddesiredroll_pos <= desiredroll_pos)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			desiredroll_pos = olddesiredroll_pos - 64;
//DeadCode RDH 26Mar98 			if (desiredroll_pos > ANGLES_20Deg)
//DeadCode RDH 26Mar98 				ai.desiredroll = (ANGLES) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos ((SWord)ai. desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 	if (	(deltapitch < ((SWord)ANGLES_350Deg))
//DeadCode RDH 26Mar98 		&& (desiredroll_pos >= MAXCOMBATROLL)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				desiredroll_pos = ANGLES_180Deg - MAXCOMBATROLL;
//DeadCode RDH 26Mar98 				ai.desiredroll = (ANGLES) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ( target.Y >= recovery_alt)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		deltapitch = PitchIntercept - fly.cpitch;
//DeadCode RDH 26Mar98 		SimpleTightTurnSubSub(deltapitch);
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		SLong groundlevel = _Collide.LowestSafeAlt(this,
//DeadCode RDH 26Mar98 											this->pitch,
//DeadCode RDH 26Mar98 											this->roll);//RDH 21Oct96
//DeadCode RDH 26Mar98 		if ((World.Y - groundlevel) < FT_100)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			//## attempt to disengage
//DeadCode RDH 26Mar98 			MoveToThrust (100);
//DeadCode RDH 26Mar98 			PitchIntercept = ANGLES_5Deg;
//DeadCode RDH 26Mar98 			AutoCalcPitch();
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ANGLES_0Deg);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SimpleTightTurnSubSub
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void AirStruc::SimpleTightTurnSubSub (SWord deltapitch)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	desiredroll; 
//DeadCode RDH 26Mar98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos;
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 26Mar98 		//now do pitch
//DeadCode RDH 26Mar98 	PitchIntercept = (ANGLES)deltapitch + fly.cpitch;
//DeadCode RDH 26Mar98 		Math_Lib.Pos (((SWord)fly.aoa),aoa_pos,aoa_sign);
//DeadCode RDH 26Mar98 		if ((SWord)aoa_pos > (SWord) STALL_ANGLE_MINUSONE)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 				PitchIntercept =  ANGLES_0Deg;
//DeadCode RDH 26Mar98 				AutoCalcPitch();
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (	(deltapitch > 0)
//DeadCode RDH 26Mar98 				&&	((SWord) fly.cpitch < ANGLES_15Deg)	//sustainable max climbrate
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				AutoCalcPitch();
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				if (	(deltapitch <= 0)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 				{//can push down
//DeadCode RDH 26Mar98 					AutoCalcPitch();
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					PitchIntercept = ANGLES_0Deg;
//DeadCode RDH 26Mar98 					AutoCalcPitch();
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			Math_Lib.Pos ((SWord)ai.desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 			if ((deltapitch > ANGLES_5Deg) && (desiredroll_pos > ANGLES_20Deg))
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 				if (deltapitch > ANGLES_20Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 						desiredroll_pos = ANGLES_20Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 				}else
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 					desiredroll = ANGLES_20Deg +  (desiredroll_pos - ANGLES_20Deg) *
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 								(ANGLES_20Deg - deltapitch) / ANGLES_15Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 					desiredroll_pos = (ANGLES) desiredroll;
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 				}
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 				ai.desiredroll = (ANGLES) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 30Oct96 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			
//DeadCode RDH 26Mar98 			if (	(fly.cpitch > ANGLES_5Deg)
//DeadCode RDH 26Mar98 				&& (desiredroll_pos > ANGLES_20Deg)
//DeadCode RDH 26Mar98 				&& (deltapitch > 0)
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 			
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				if (fly.cpitch > ANGLES_15Deg)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 						desiredroll_pos = ANGLES_20Deg;
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					desiredroll = ANGLES_20Deg +  (desiredroll_pos - ANGLES_20Deg) *
//DeadCode RDH 26Mar98 								(ANGLES_15Deg - fly.cpitch) / ANGLES_15Deg;
//DeadCode RDH 26Mar98 					desiredroll_pos = (ANGLES) desiredroll;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 				ai.desiredroll = (ANGLES) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			SimpleMoveToRoll (ai.desiredroll);
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SimpleCalcVel
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 25 Oct 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::SimpleCalcVel ()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord thrust;
//DeadCode RDH 26Mar98 	SLong reqvel;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	thrust = fly.thrustpercent;
//DeadCode RDH 26Mar98 	if (thrust > 10)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		reqvel = classtype->maxvel*7/8;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 27Oct96 		reqvel = classtype->bestclimbvel;
//DeadCode RDH 26Mar98 		reqvel = MPH30;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if (fly.cpitch >> ANGLES_90Deg)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		reqvel = classtype->bestclimbvel + (classtype->maxvel - classtype->bestclimbvel) *
//DeadCode RDH 26Mar98 									(SWord) (classtype->bestclimbpitch - pitch)/classtype->bestclimbpitch;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	CalcVelSub (reqvel);
//DeadCode RDH 26Mar98 	//if we want to go slow then have a double decell
//DeadCode RDH 26Mar98 	if (	(reqvel == MPH30)
//DeadCode RDH 26Mar98 		&&	(Range <METRES70)
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 		CalcVelSub (reqvel);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		SimpleMoveToThrust
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			//RDH 11Oct96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	AirStruc::SimpleMoveToThrust (SWord thrust)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SLong	reqvel;
//DeadCode RDH 26Mar98 	SLong	accel;
//DeadCode RDH 26Mar98 	SWord	deltavel,deltavel_sign;	
//DeadCode RDH 26Mar98 	UWord	deltavel_pos;
//DeadCode RDH 26Mar98 	SLong	climb_vel;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if  (thrust == -100)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (fly.thrustpercent ==0)
//DeadCode RDH 26Mar98 			fly.thrustpercent =  MAXAUTOTHRUST;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	elseif  (thrust == -1)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (fly.thrustpercent ==MAXAUTOTHRUST)
//DeadCode RDH 26Mar98 			fly.thrustpercent =  0;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	else
//DeadCode RDH 26Mar98 		fly.thrustpercent =  thrust;
//DeadCode RDH 26Mar98 	if (fly.thrustpercent > MAXAUTOTHRUST)
//DeadCode RDH 26Mar98 		fly.thrustpercent = MAXAUTOTHRUST;	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
