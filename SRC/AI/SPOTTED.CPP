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
//Filename       spotted.cpp
//System         
//Author         R. Hyde 
//Date           Tue 3 Mar 1998
//Description    
//
//				These routines called from visiblecheck() in msgai.com
//
//				Note the data structure does not have the concept of elements
//				We have flights.
//				The code must compensate
//
//------------------------------------------------------------------------------
//	Both SpottedUnfriendly and AlertFighters can result in a force splitting (don't confuse with 
//	split manoeuvre)
//
//	The difference is that SpottedUnfirendly will result in leader set going and others remaining
//	and AlertFighter will result in a SendFlight, ie leader staying
//
//
//

//On moving from precombat to visible range need equivalent to SpottedUnfr
//	Check decoy
//	Explore FirstTactics
//	Consider starting BVR
//
//
//Notes on airstruc pointers
//
//for caller:
//	if caller->leader == null caller is element leader
//	if caller->Follower()
//		nex wingman in element
//
//
//
//There are 3 candidates for Group Leader:
//		currac
//		currac->leader
//		currac->fly.leadflight
//
//To find all fighter leaders
//		found = AirStruc::AircraftList
//
//		while found
//		{
//			if (found->formpos == 0)
//				this is a leader
//			found = found->nextmobile;
//		}
//	if leader of group escorting something else 
//		then leadflight points to escortee lead
//	else leadflight  == NULL
//
//can use leadelt() to find leader of next element up
//
//	VisibleCheck code is used for either group leader or any ac not information
//
//
#include	"dosdefs.h"
	#define F_COMMON
	#define F_GRAFIX
	#define F_BATTLE
#include	"files.g"
#include	"worldinc.h"
#include	"ai.h"
#include	"myerror.h"
#include	"mymath.h"
#include	"landscap.h"
#include	"ranges.h"
#include	"planetyp.h"
#include	"mytime.h"
#include	"flymodel.h"
#include	"persons2.h"
#include	"savegame.h"
#include	"miles.h"
//#include	"winmove.h"											//ARM 06Dec96
#include	"textref.h"
#include	"replay.h"

extern ArtInt	Art_Int;

DECISIONAI(Rendezvous,AirStrucPtr);

DECISIONAI(DefensiveManoeuvre, AirStrucPtr);
DECISIONAI(AttackingManoeuvre,AirStrucPtr);
DECISIONAI(UnFriendlyFar, AirStrucPtr);
DECISIONAI(PotentialBounce, AirStrucPtr);
DECISIONAI(FriendliesUnderAttack, AirStrucPtr);

OPTIONAI(SetUpDefensiveSplit, AirStrucPtr);
OPTIONAI(SendFlight, AirStrucPtr);
OPTIONAI(AllGo, AirStrucPtr);
OPTIONAI(RelaySighting, AirStrucPtr);
OPTIONAI(DoNothing,AirStrucPtr);
OPTIONAI(SelectTarget,AirStrucPtr);
OPTIONAI(SetupLineAbreast,AirStrucPtr)
OPTIONAI(SetupRoundAbout,AirStrucPtr)
OPTIONAI(SetupLineAstern,AirStrucPtr)
OPTIONAI(SetupDiveAndZoom,AirStrucPtr)


OPTIONAI(SetUpPincerAttack, AirStrucPtr);
OPTIONAI(SetUpMultiWave, AirStrucPtr);
OPTIONAI(SetUpDefensiveSplitRightHi, AirStrucPtr);
OPTIONAI(SetUpDefensiveSplitLeftHi, AirStrucPtr);
OPTIONAI(SetUpDefensiveSplitBothHi, AirStrucPtr);


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedUnknown
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	Do we want a closer look?
//			   	Only if threatlevel >=BANDITANYWHERE
//				and aggressionlevel >=AL_DEFENSIVE
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::SpottedUnknown(AirStruc* caller,AirStruc* trg)
{
//no autovectoring
//
	RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);	
	InterceptRangeFromTo(caller,trg);
	AirStruc* trgldr = trg->FindGroupLeader();

	if (		(caller->nationality==trg->nationality)		
			||	(		(caller->formpos != 0)								//only leaders can respond
					&&	(caller->information)
				)
			||	(caller->ai.unfriendly!=NULL)
			||	(		(trg->formpos != 0)								//only respond to leaders
					&&	(		(trg->information)
							||	(AircraftAreClose(trg, trgldr))
						)
				)
	   )
		return false; 

	if (caller->nationality == Manual_Pilot.ControlledAC2->nationality)
	{
		if (caller->IsUsingPilotedAcLog())
		{
			if (		(!trg->ai.attacker)
					&&	(!trg->IsUsingPilotedAcLog())
			   )
			{
				caller->PlayerSequenceAudible(FIL_MUSIC_SPOTTED_UNKNOWN);
				Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);

				if ((TargetOnCallerTail(caller, trg, ANGLES_10Deg)	&&	(rndpc >RND50PC)))
 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BOGEY_SIX, MSG_BOGEYCALL, caller, trg, Manual_Pilot.ControlledAC2));
 				else if ((CallerFacingTarget(caller, trg, ANGLES_20Deg)&&	(rndpc >RND50PC)))
 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BOGEY_AHEAD, MSG_BOGEYCALL, caller, trg, Manual_Pilot.ControlledAC2));
 				else
 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BOGEY, MSG_BOGEYCALL, caller, trg, Manual_Pilot.ControlledAC2));

			}
		}elseif (!trg->IsUsingPilotedAcLog())
		{
			if (!trg->ai.attacker)
			{
				if (trg->ai.eventlog->stage < EventLog::SEENBYOTHERS)
				{
					int range = RangeFromTo(trg, Persons2::PlayerGhostAC);
					InterceptRangeFromTo(Manual_Pilot.ControlledAC2,trg);
					if (range < VISIBLERANGE)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DENTIST_TRACES_CLOSE, MSG_BOGEYCALLDENTIST, VOICE_DENTIST, trg, Manual_Pilot.ControlledAC2));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DENTIST_TRACES_FAR, MSG_BOGEYCALLDENTIST, VOICE_DENTIST, trg, Manual_Pilot.ControlledAC2));
					Persons2::UpdateLog(trg,0,EventLog::SEENBYOTHERS);
				}				
			}
		}
	}
	if  (			((caller->duty&ACTIONCODE)==DA_CAP)
				&&	(caller->classtype->aerobaticfactor != AEROBATIC_LOW) //RDH 21/06/99
				&&	(caller->ai.unfriendly==NULL)
		)
	{
		
		AirStruc*	buddy = caller->FindABuddyWithPlayerGivenPriority();
		if (buddy)
		{
			if  (	(caller->ai.threatlevel >=BANDITANYWHERE)
					&&	caller->movecode < AUTO_TRACKINGBOGIE
					&&	caller->ai.aggressionlevel >= AL_DEFENSIVE
				)
			{
					AllChangeMovecode(caller, trg, AUTO_TRACKINGBOGIE);
					trg->ai.attacker = caller;
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLOSERLOOK, MSG_BOGEYCALL, caller, trg, buddy));
			}else
			{
				if (Escorting(caller) && 	(rndpc >RND50PC))
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STAYWITHBOMBERS, MSG_BOGEYCALL, caller, trg, buddy));
				else
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_LETGO, MSG_BOGEYCALL, caller, trg, buddy));
			}
		}
	}
	return(true);
}

//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------

INSTANCEAI(DoNothing,AirStrucPtr)
{
	return(false);
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SelectTarget,AirStrucPtr)
{
 	AirStruc* follower = caller->Follower();
	if (	(follower)	&& (caller->ai.elementtactics == WELDEDWING))
 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COVERME, MSG_FOLLOWME, caller, NULL, follower));

	if (caller->IsUsingPilotedAcLog())
		if (!trg->IsUsingPilotedAcLog())
			 Persons2::UpdateLog(trg,0,EventLog::ATTACKED);
	SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg,FALSE);
 	return(true);
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date																  //RDH 24/02/99
//
//Description			   red manoeuvre
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetupLineAbreast,AirStrucPtr)
{

	SetEngage(caller,trg, MANOEUVRE_LINEABREAST,ANGLES_0Deg,ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_LINEABREAST,ANGLES_0Deg,ANGLES_0Deg,FALSE);
 	return(true);
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date																  //RDH 24/02/99
//
//Description			   red manoeuvre
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetupLineAstern,AirStrucPtr)
{

	SetEngage(caller,trg, MANOEUVRE_LINEASTERN,ANGLES_0Deg,ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_LINEASTERN,ANGLES_0Deg,ANGLES_0Deg,FALSE);
 	return(true);
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date																  //RDH 24/02/99
//
//Description			   red manoeuvre
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetupDiveAndZoom,AirStrucPtr)
{

	SetEngage(caller,trg, MANOEUVRE_DIVEANDZOOM,ANGLES_0Deg,ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_DIVEANDZOOM,ANGLES_0Deg,ANGLES_0Deg,FALSE);
 	return(true);
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date																  //RDH 24/02/99
//
//Description			   red manoeuvre
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetupRoundAbout,AirStrucPtr)
{

	SetEngage(caller,trg, MANOEUVRE_ROUNDABOUT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_ROUNDABOUT,ANGLES_0Deg,ANGLES_0Deg,FALSE);
 	return(true);
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetUpPincerAttack, AirStrucPtr)
{
	AirStruc* callee2;
	tGroupLevel group;
	FindGroupAndLeader2(caller, callee2, group);
	if (!callee2)
	{
		SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg, ANGLES_0Deg,  FALSE);
	}else
	{
				
		if (prioritymessage)
		{																  //RDH 23/02/99
			callee = callee2;
			prioritymessage->callee = callee;
			prioritymessage->scriptno = SCRIPT_PINCER_LEAD2_RIGHT;		//RJS 09Mar99
			if (CallerOnRight(caller,callee))
				prioritymessage->scriptno = SCRIPT_PINCER_LEAD2_LEFT;	//RJS 09Mar99
		}
		callee->information=FALSE;
		SwitchCallerToLeft(caller, callee);

		
		
		tGroupLevel trggroup;
		AirStruc* trg2;
		trg = trg->FindGroupLeaderClose();								  //RDH 23/06/99
		FindGroupAndLeader2(trg, trg2, trggroup);			//trg on the left
		if (!trg2)
			trg2 = trg;
		SwitchCallerToLeft(trg,trg2);

		if (!trg2) 														  //rdh 23/04/99
			trg2 = trg;													  //rdh 23/04/99
		SWord deltahdg = (SWord)caller->hdg - (SWord)trg->hdg;
		if (deltahdg < 0)
		   deltahdg = -deltahdg;
		 if (deltahdg > (SWord)ANGLES_90Deg)
		 {//if trg is facing caller then reverse
			AirStruc* tmp = trg;
			trg = trg2;
			trg2 = tmp;
		 }
			
	   //set first half

		SetEngage(caller,trg,MANOEUVRE_PINCER, ANGLES_320Deg, ANGLES_0Deg,FALSE);
		SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_PINCER, ANGLES_260Deg, ANGLES_0Deg,FALSE);
		//find caller's second half
		SetEngage(callee,trg2,MANOEUVRE_PINCER, ANGLES_40Deg, ANGLES_0Deg,FALSE);
		SetUpRemainderOfGroupToEngage(callee,trg2,MANOEUVRE_PINCER, ANGLES_100Deg, ANGLES_0Deg,FALSE);
	}
 	return(true);
}

//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetUpMultiWave, AirStrucPtr)
{
//DEADCODE RDH 12/06/99 		if (prioritymessage)
	{																  //RDH 23/02/99
		tGroupLevel group;
		FindGroupAndLeader2(caller, callee, group);
	}
	if (!callee)
	{
		SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg, ANGLES_0Deg,  FALSE);
	}else
	{
 		MANOEUVRE manoeuvre = MANOEUVRE_SELECT;
		if  (		CallerFacingTarget(caller, trg, ANGLES_45Deg)
				&&	TargetFacingCaller(caller, trg, ANGLES_45Deg)
			)
			manoeuvre = MANOEUVRE_HEADON;

		callee->information=FALSE;
		
		SetEngage(caller,trg,manoeuvre, ANGLES_0Deg, ANGLES_0Deg,FALSE);
		SetUpRemainderOfGroupToEngage(caller,trg,manoeuvre, ANGLES_0Deg, ANGLES_0Deg,FALSE);
		

		SetEngage(callee,trg,MANOEUVRE_MULTIWAVE, ANGLES_0Deg, ANGLES_0Deg,FALSE);
		SetUpRemainderOfGroupToEngage(callee,trg,MANOEUVRE_MULTIWAVE, ANGLES_0Deg, ANGLES_0Deg,FALSE);
	}
 	return(true);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DefensiveSplit
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
void	ArtInt::DefensiveSplit(AirStruc* caller,AirStruc* trg, ANGLES leftpitch,ANGLES rightpitch)
{
	tGroupLevel group;
	AirStruc* caller2;
	FindGroupAndLeader2(caller, caller2, group);
	if (!caller2)
	{
		SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg, ANGLES_0Deg,  FALSE);
	}else
	{
		caller2->information=FALSE;
		SwitchCallerToLeft(caller, caller2);


		tGroupLevel trggroup;
		AirStruc* trg2;
		trg = trg->FindGroupLeaderClose();								  //RDH 23/06/99
		FindGroupAndLeader2(trg, trg2, trggroup);			//trg on the left
		if (!trg2)
			trg2 = trg;
		SwitchCallerToLeft(trg,trg2);


		Angles desiredhdg = (Angles)((SWord)ANGLES_195Deg + caller->hdg);
	   //set first half
		SetEngage(caller,trg,MANOEUVRE_SPLITMANOEUVRE, desiredhdg,leftpitch,true);
		SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_SPLITMANOEUVRE, desiredhdg,leftpitch,true);
 		if (	(caller->Follower())	&& (caller->ai.elementtactics == WELDEDWING))
 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_CALLEE_FOLLOWME, MSG_FOLLOWME, caller, NULL, caller->Follower()));
		
		//find caller's second half
		desiredhdg = (Angles)((SWord)ANGLES_170Deg + caller2->hdg);

		SetEngage(caller2,trg2,MANOEUVRE_SPLITMANOEUVRE, desiredhdg,rightpitch,true); //RDH 27/06/99
		SetUpRemainderOfGroupToEngage(caller2,trg,MANOEUVRE_SPLITMANOEUVRE, desiredhdg, rightpitch,true);
 		if (	(caller2->Follower())	&& (caller2->ai.elementtactics == WELDEDWING))
 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_CALLEE_FOLLOWME, MSG_FOLLOWME, caller2, NULL, caller2->Follower()));
	}	
}

//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetUpDefensiveSplitRightHi, AirStrucPtr)
{
   DefensiveSplit(caller,trg, ANGLES_0Deg,BESTCLIMBPITCH);
   return(true);
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetUpDefensiveSplitLeftHi, AirStrucPtr)
{
   DefensiveSplit(caller,trg, BESTCLIMBPITCH,ANGLES_0Deg);
   return(true);
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetUpDefensiveSplitBothHi, AirStrucPtr)
{
   DefensiveSplit(caller,trg, BESTCLIMBPITCH, BESTCLIMBPITCH);
   return(true);
}

//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SetUpDefensiveSplit, AirStrucPtr)
{
   	DefensiveSplit(caller,trg, ANGLES_0Deg,ANGLES_0Deg);
	return(true);
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TABLEAI(AttackingManoeuvre,AirStrucPtr)
{
	{PHRASE_PINCER,						&SetUpPincerAttack, SCRIPT_PINCER_LEAD2_LEFT},	
	{PHRASE_MULTIWAVE,					&SetUpMultiWave,	SCRIPT_MULTIWAVE_LEAD2_HANGBACK},
	{PHRASE_SELECTTARGET,				&SelectTarget,	PHRASE_SELECTYOUROWNTARGETS},
	{PHRASE_CONTINUE,					&DoNothing,		PHRASE_IGNOREFORNOW},
	{PHRASE_PARTS_S,		&SetupRoundAbout},
	{PHRASE_CONTINUE,		&SetupLineAbreast},
	{PHRASE_CONTINUE,		&SetupLineAstern},
	{PHRASE_CONTINUE,		&SetupDiveAndZoom},
	{PHRASE_PARTS_S}
};
INSTANCEAI(AttackingManoeuvre,AirStrucPtr)
{
	tGroupLevel group = GroupLevel(caller);
	bool retval = false;
	ScriptTables script, script2;
	bool	splitmanappropriate = false;

	if (		(EngageAppropriate(caller, trg))
			&&	(MakeForceToRespond (caller,trg,group, splitmanappropriate))
		)		
	{
		if (caller->fly.nextflight)
		{
			script = (ScriptTables)PHRASE_SELECTYOUROWNTARGETS;
			callee = caller->fly.nextflight;
		}else if	(		(caller->ai.elementtactics != WELDEDWING)
						&&	(caller->Follower())
					)
		{
   			script = (ScriptTables)PHRASE_SELECTYOUROWNTARGETS;
			callee = caller->Follower();

		}else
		{
			callee = NULL;
			script = (ScriptTables)PHRASE_ENGAGE;			//RJS 09May99
		}

//DEADCODE RDH 06/04/99 		
//DEADCODE RDH 06/04/99  		if 	(caller->nationality != NAT_RED)
//DEADCODE RDH 06/04/99 		{
//DEADCODE RDH 06/04/99 			caller->ai.firsttactic = TACTIC_DIVEANDZOOM;
//DEADCODE RDH 06/04/99 			retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_WELLENGAGE,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupDiveAndZoom);	
//DEADCODE RDH 06/04/99 			return(retval);
//DEADCODE RDH 06/04/99 		}


		

 		if (caller->ai.firsttactic == TACTIC_ROUNDABOUT)
			retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupRoundAbout);	
		else if (caller->ai.firsttactic == TACTIC_SCATTER)
			retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SelectTarget);	
		else if (caller->ai.firsttactic == TACTIC_LINEABREAST)
			retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_ENGAGE,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupLineAbreast);	
		else if (caller->ai.firsttactic == TACTIC_LINEASTERN)
			retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_ENGAGE,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupLineAstern);	
		else if (caller->ai.firsttactic == TACTIC_DIVEANDZOOM)
			retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupDiveAndZoom);	
		else if (	(group != GROUP_LONER)	&&	(splitmanappropriate)	&&	(trg->ai.combatskill <= SKILL_VETERAN))
		{
			if	(trg->classtype->aerobaticfactor == AEROBATIC_LOW)
			{
					RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
					if (rndpc <  RND25PC)
					{
						caller->ai.firsttactic = TACTIC_LINEABREAST;
						retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupLineAbreast);	
					}else if (rndpc <  RND50PC)
					{
						caller->ai.firsttactic = TACTIC_LINEASTERN;
						retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupLineAstern);	
					}
					else if (rndpc <  RND75PC)
					{
						caller->ai.firsttactic = TACTIC_ROUNDABOUT;
						retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupRoundAbout);	
					}
					else
					{
						caller->ai.firsttactic = TACTIC_DIVEANDZOOM;
						retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupDiveAndZoom);	
					}
			}else
			{
				FindGroupAndLeader2(caller, callee, group);
				if (!callee)
					retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SelectTarget);	
				else
				{
					script2 = SCRIPT_PINCER_LEAD2_RIGHT;		  //DAW 23/02/99
					if (CallerOnRight(caller,callee))
						script2 = SCRIPT_PINCER_LEAD2_LEFT;

					if (caller->ai.firsttactic == TACTIC_PINCER)
						retval = SendMsgAndCall(MESSAGE_STRUC(script2,MSG_CHOSENMANOEUVRE,caller,trg,callee  ), SetUpPincerAttack);	
					else if (caller->ai.firsttactic == TACTIC_MULTIWAVE)
	 						retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_MULTIWAVE_LEAD2_HANGBACK,    MSG_CHOSENMANOEUVRE, caller,trg,callee), SetUpMultiWave);
					else
					{
						RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
					if (rndpc >  RND50PC)
							retval = SendMsgAndCall(MESSAGE_STRUC(script2,MSG_CHOSENMANOEUVRE,caller,trg, callee  ), SetUpPincerAttack);	
						else 
						{
							if  (		CallerFacingTarget(caller, trg, ANGLES_45Deg)
									&&	TargetFacingCaller(caller, trg, ANGLES_45Deg)
								)
								retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SelectTarget);	
							else
								retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_MULTIWAVE_LEAD2_HANGBACK,    MSG_CHOSENMANOEUVRE, caller,trg,callee), SetUpMultiWave);
						}

					}
				}
			}
		}else
		{
			if	(trg->classtype->aerobaticfactor == AEROBATIC_LOW)
			{
					RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
//DEADCODE RDH 04/07/99 					if (rndpc <  RND25PC)
//DEADCODE RDH 04/07/99 					{
//DeadCode CSB 05/07/99	//DEADCODE RDH 04/07/99 						caller->ai.firsttactic = TACTIC_LINEABREAST;
//DeadCode CSB 05/07/99							caller->SetFollowersTactic(TACTIC_LINEABREAST);
//DEADCODE RDH 04/07/99 						retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupLineAbreast);	
//DEADCODE RDH 04/07/99 					}else if (rndpc <  RND50PC)

					if(rndpc < RND33PC)	//CSB 07/07/99	
					{
//DeadCode CSB 05/07/99							caller->ai.firsttactic = TACTIC_LINEASTERN;
						caller->SetFollowersTactic(TACTIC_LINEASTERN);
						retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupLineAstern);	
					}
					else if (rndpc < RND67PC)	//CSB 07/07/99	
					{
//DeadCode CSB 05/07/99							caller->ai.firsttactic = TACTIC_ROUNDABOUT;
						caller->SetFollowersTactic(TACTIC_ROUNDABOUT);
						retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupRoundAbout);	
					}
					else
					{
//DeadCode CSB 05/07/99							caller->ai.firsttactic = TACTIC_DIVEANDZOOM;
						caller->SetFollowersTactic(TACTIC_DIVEANDZOOM);
						retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupDiveAndZoom);	
					}
			}else
				retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SelectTarget);	
		}
	}else
	{
		if (trg->ai.eventlog->stage < EventLog::SEENBYOTHERS)
		{
		   	retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_IGNOREFORNOW,MSG_SPOTTEDASNEWUNFRIENDLY,caller,trg,caller->Follower()),DoNothing);
			if (caller->IsUsingPilotedAcLog())
				Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);
			else
				Persons2::UpdateLog(trg,0,EventLog::SEENBYOTHERS);
		}

	}



	return(retval);
}


//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TABLEAI(DefensiveManoeuvre, AirStrucPtr)
{
	{PHRASE_DEFENSIVESPLIT_S,			&SetUpDefensiveSplit,	PHRASE_DEFENSIVESPLIT},		 //DAW 23/02/99
	{PHRASE_DEFENSIVESPLITLEFTHI_S,	&SetUpDefensiveSplitLeftHi,	PHRASE_DSSLEFTHI},
	{PHRASE_DEFENSIVESPLITRIGHTHI_S,	&SetUpDefensiveSplitRightHi, PHRASE_DSSRIGHTHI},
	{PHRASE_DEFENSIVESPLITBOTHHI_S,	&SetUpDefensiveSplitBothHi, PHRASE_DSSBOTHHI},
	{PHRASE_SELECTTARGET,				&SelectTarget,	PHRASE_SELECTYOUROWNTARGETS},
	{PHRASE_CONTINUE,					&DoNothing,		PHRASE_IGNOREFORNOW},
	{PHRASE_PARTS_S},
	{PHRASE_PARTS_S}
};
INSTANCEAI(DefensiveManoeuvre, AirStrucPtr)
{
	tGroupLevel group = GroupLevel(caller);
	bool retval;
	bool	splitmanappropriate = false;


	if (		(EngageAppropriate(caller, trg))
			&&	(MakeForceToRespond (caller,trg,group, splitmanappropriate))
		)		
	{
		if  (	(		((group == GROUP_ELEMENT)	&&	(caller->ai.elementtactics == LOOSEDEUCE))
					||	((group == GROUP_FLIGHT)	&&	(caller->ai.flighttactics == LOOSEDEUCE))
					||	((group == GROUP_SQUADRON)	&&	(caller->ai.squadrontactics == LOOSEDEUCE))
				)
				&&
					(splitmanappropriate)
			)
			{//split appropriate
					RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
					RndVal  trgpc = RND90PC;
					if (caller->ai.combatskill >= SKILL_REGULAR)
						trgpc = RND50PC;
					elseif (caller->ai.combatskill >= SKILL_ACE)
						trgpc = RND10PC;
				if (rndpc >	trgpc)
					{
						if (caller->ai.morale < MORALE_MEDIUM)
							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLIT,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplit);
						else if (	(caller->ai.combatskill > SKILL_REGULAR)	&&	(trgpc > RND75PC))
								retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_DEFENSIVESPLITBOTHHI,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitBothHi);
						else
							if ((Math_Lib.rnd(RndValMAX)) > RND50PC)	
								retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_DEFENSIVESPLITLEFTHI,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitLeftHi);
							else
								retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_DEFENSIVESPLITRIGHTHI,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitRightHi);
					}else
						retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_SELECTYOUROWNTARGETS,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SelectTarget);		
		
			}else
				retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_SELECTYOUROWNTARGETS,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SelectTarget);		

	}else
	   	retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_IGNOREFORNOW,MSG_SPOTTEDASNEWUNFRIENDLY,caller,trg,caller),DoNothing);
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedUnFriendly
//Author		R. Hyde 
//Date			RDH 20Jan99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::SpottedUnfriendly(AirStruc* caller,AirStruc* trg)
{
	bool retval;
	InterceptRangeFromTo(caller,trg);
	if  (		((caller->duty&ACTIONCODE)!=DA_CAP)
			||	(caller->classtype->aerobaticfactor == AEROBATIC_LOW) //RDH 21/06/99
		)

//DEADCODE RDH 12/05/99 	if (caller->classtype->aerobaticfactor == AEROBATIC_LOW)
	{//non cap a/c including medium bomber
		retval = AlertFighters((AirStruc*)caller,trg,caller);
	}else
		retval = ChooseManoeuvre(caller,trg,true);
	return(retval);

}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description		   callee is lowest flight free in caller's group
//						if there isn't a free flight then redirect lowest which is attacking a/c in same flight that eader is attacking		   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(SendFlight, AirStrucPtr)
{

	bool retval;
	if (prioritymessage)
	{
		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);	
 		prioritymessage->callee = callee;
 		if 	((trg->nationality == NAT_RED) && (rndpc >RND50PC))
 			prioritymessage->scriptno = SCRIPT_TAKEFLIGHTTOMIGS;
 		else
 			prioritymessage->scriptno = SCRIPT_TAKEFLIGHTTOBANDITS;
	}
	//better to send msg to 2nd element leader
	AirStruc* buddy = caller->Follower();
	if (caller->ai.elementtactics == WELDEDWING)
		buddy = caller->fly.nextflight;
	if (buddy)
		retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_ENGAGE,MSG_ATTACK,callee,trg,buddy), SelectTarget);

	return(retval);

};
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(AllGo, AirStrucPtr)
{
	//use selecttarget instead
//DEADCODE RDH 20/06/99  	if (	(caller->Follower())	&& (caller->ai.elementtactics == WELDEDWING))
//DEADCODE RDH 20/06/99  		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_CALLEE_FOLLOWME, MSG_FOLLOWME, caller, NULL, caller->Follower()));
//DEADCODE RDH 20/06/99 	SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
//DEADCODE RDH 20/06/99 	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg,FALSE);
	return(true);

};
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
INSTANCEAI(RelaySighting, AirStrucPtr)
{
	bool retval;
	retval = AlertFighters(caller,trg,callee);
	return(retval);
};

//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TABLEAI(UnFriendlyFar, AirStrucPtr)
{
	{PHRASE_ALLGO,			&SelectTarget,			SCRIPT_ALLGO},	
	{PHRASE_SENDAFLIGHT,	&SendFlight,	PHRASE_SENDAFLIGHT},	//this is a dummy, it gets changed by SendFlight //RDH 28/02/99
	{PHRASE_CONTINUE,		&DoNothing,		PHRASE_IGNOREFORNOW},
	{PHRASE_PARTS_S},
	{PHRASE_PARTS_S}
};
INSTANCEAI(UnFriendlyFar, AirStrucPtr)
{
	caller = callee;
	bool retval = false;
	ScriptTables script;

//remove chance of recurse
//DEADCODE DAW 19/05/99 	if	(		(caller->ai.unfriendly != NULL)
//DEADCODE DAW 19/05/99 			&&	( RangeFromTo(caller,trg) > RangeFromTo(caller,(AirStruc*)caller->ai.unfriendly))
//DEADCODE DAW 19/05/99 		)	
//DEADCODE DAW 19/05/99 	{
//DEADCODE DAW 19/05/99 		retval = AlertFighters(caller,trg);
//DEADCODE DAW 19/05/99 	}else 
	if(		TrgIsVulnerable(caller, trg)
			)
	{
		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);

		callee = FindFreeFlight(caller);						//RDH 12Apr99
		if (callee)											//RDH 12Apr99
		{
			if 	((trg->nationality == NAT_RED) && (rndpc >  RND50PC))
				script = SCRIPT_TAKEFLIGHTTOMIGS;
			else
				script = SCRIPT_TAKEFLIGHTTOBANDITS;
			retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_SENDTOINVESTIGATE,caller,trg,callee),SendFlight);
		}else
		{
			callee = FreeUpAFlight(caller, trg);
			if (callee)
			{
				if ((trg->nationality == NAT_RED) && (rndpc >  RND50PC))
					script = SCRIPT_GOFORNEARERMIG;
				else
					script = SCRIPT_GOFORNEARERBANDITS;
				retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_SENDTOINVESTIGATE,caller,trg,callee),SendFlight);
			}else
				retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_ALLGOREDIRECT,MSG_ATTACK, caller,trg,caller),SelectTarget);
		}
	}else
	{
		if (caller->ai.unfriendly == NULL)
			retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_ALLGO,MSG_ATTACK, caller,trg,caller),SelectTarget);
		else
			retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_ALLGOREDIRECT,MSG_ATTACK, caller,trg,caller), SelectTarget);
	}
	return(retval);
}		
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TABLEAI(PotentialBounce, AirStrucPtr)
{
	{PHRASE_ALLGO,			&SelectTarget,			SCRIPT_ALLGO},	
	{PHRASE_SENDAFLIGHT,	&SendFlight,	PHRASE_SENDAFLIGHT},	//this is a dummy, it gets changed by SendFlight //RDH 28/02/99
	{PHRASE_CONTINUE,		&DoNothing,		PHRASE_IGNOREFORNOW},
	{PHRASE_PARTS_S},
	{PHRASE_PARTS_S}
};
INSTANCEAI(PotentialBounce, AirStrucPtr)
{
	caller = callee;
	bool retval = false;
	ScriptTables script;
	if (RangeFromTo(caller, trg) > ENGAGERANGE)
	{
		   	retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_IGNOREFORNOW,MSG_SPOTTEDASNEWUNFRIENDLY,caller,trg,caller->Follower()),DoNothing);
	}else
	{
		if(		TrgIsVulnerable(caller, trg)
				)
		{
			RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);

			callee = FindFreeFlight(caller);						//RDH 12Apr99
			if (callee)											//RDH 12Apr99
			{
				if 	((trg->nationality == NAT_RED) && (rndpc >  RND50PC))
					script = SCRIPT_TAKEFLIGHTTOMIGS;
				else
					script = SCRIPT_TAKEFLIGHTTOBANDITS;
				retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_SENDTOINVESTIGATE,caller,trg,callee),SendFlight);
			}else
			{
				callee = FreeUpAFlight(caller, trg);
				if (callee)
				{
					if ((trg->nationality == NAT_RED) && (rndpc >  RND50PC))
						script = SCRIPT_GOFORNEARERMIG;
					else
						script = SCRIPT_GOFORNEARERBANDITS;
					retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_SENDTOINVESTIGATE,caller,trg,callee),SendFlight);
				}else
					retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_ALLGOREDIRECT,MSG_ATTACK, caller,trg,caller),SelectTarget);
			}
		}else
		{
			if (caller->ai.unfriendly == NULL)
				retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_ALLGO,MSG_ATTACK, caller,trg,caller),SelectTarget);
			else
				retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_ALLGOREDIRECT,MSG_ATTACK, caller,trg,caller), SelectTarget);
		}
	}
	return(retval);
}		
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AlertFighters
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
bool	ArtInt::AlertFighters(AirStruc* caller,AirStruc* trg, AirStruc* friendlythatneedshelp)
{
  bool retval = false;

	AirStruc* callee = NULL;
	AirStruc* currac = (AirStruc*) AirStruc::ACList;
	SLong callertrgrange = RangeFromTo(caller, trg);
	SLong	curractrgrange;
	SLong	range = MILES200;
	AirStruc* callerldr = caller->FindGroupLeader();
	AirStruc* friendlythatneedshelpldr = friendlythatneedshelp->FindGroupLeader();

	if  (		(!trg->ai.attacker)
			&&	(		(trg->formpos == 0)
					||	(		(!trg->information)
							&&	(trg->fly.leadflight)
							&&	(!AircraftAreClose(trg, trg->fly.leadflight))

						)
				)
		)
	{//only concerned with leaders not under attack
		while (	(currac))
		{
//DEADCODE RDH 19/06/99 			if (currac ==  Persons2::PlayerGhostAC)
//DEADCODE RDH 19/06/99 				INT3;
			if  (	((currac->duty&ACTIONCODE)==DA_CAP)
					&&	(currac->classtype->aerobaticfactor != AEROBATIC_LOW) //RDH 21/06/99
					&&	(currac->formpos == 0)
					&&	(		(!currac->ai.unfriendly)						//not busy
							||	(currac->movecode == AUTO_TRACKINGBOGIE)		//busy but just tracking bogies
							||	(		(currac == Persons2::PlayerGhostAC) 		//player busy but just tracking bogies
									&&	 (Persons2::PlayerSeenAC->movecode == AUTO_TRACKINGBOGIE)
								)
						)
					&&	(currac->nationality == caller->nationality)
					&&	(currac != caller)
				)
			{//this is a cap or escort leader
				
				 if  (friendlythatneedshelpldr == currac->fly.leadflight)
				 {//this fighter leader is in same wave as one that needs help
					callee = currac;
					curractrgrange = RangeFromTo(currac, trg);
					break;
				 }else
				 {
					curractrgrange = RangeFromTo(currac, trg);
					if  (		//##idea was to allow steady moving of message down line
								//but it gets stuck when close to (curractrgrange > callertrgrange)
							//&&
									(curractrgrange < range)
						)
					{
						callee = currac;
						range = curractrgrange;
					}
				 }
			}
			currac = (AirStruc*)currac->nextmobile;
		}
		if (callee)
		{
			if 	(curractrgrange < VISIBLERANGE)
 				retval = SendMsgAndCall(ChooseBanditRelMsg(MSG_SPOTTEDBYOTHERS,callee,trg, callee,true),AttackingManoeuvre);
 			else
				retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_DENTIST_LOC_ENEMY,MSG_SPOTTEDBYOTHERS, VOICE_DENTIST,trg,callee), UnFriendlyFar);
		}else
		{//no CAP to go and help
			if (		(friendlythatneedshelpldr->classtype->aerobaticfactor != AEROBATIC_LOW)	  //RDH 01/06/99
					&&	((friendlythatneedshelpldr->duty&ACTIONCODE)!=DA_CAP)
				)
			{// friendly that needs help is not a medium bomber and not CAP, ie is a fighter bomber that should defend
				if (trg->ai.eventlog->stage < EventLog::SEENBYOTHERS)
				{
					retval = SendMsgAndCall(ChooseBanditRelMsg(MSG_SPOTTEDBYOTHERS,callerldr,trg, friendlythatneedshelpldr,true), PotentialBounce);
					if (callerldr->IsUsingPilotedAcLog())
						Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);
					else
						Persons2::UpdateLog(trg,0,EventLog::SEENBYOTHERS);
				}
			}
		}
	}
	return(retval);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedNewUnfriendly
//Author		Jim Taylor
//Date			Tue 22 Oct 1996
//
//Description	
//
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::SpottedNewUnfriendly(AirStruc* caller,AirStruc* trg)
{
//DEADCODE RDH 20/05/99 	bool retval = FALSE;
//DEADCODE RDH 20/05/99 	
//DEADCODE RDH 20/05/99 	AirStruc* trggrplead = trg->FindGroupLeader();
//DEADCODE RDH 20/05/99 	AirStruc* unfgrplead = (AirStruc*)caller->ai.unfriendly;
//DEADCODE RDH 20/05/99 	if (caller->ai.unfriendly)
//DEADCODE RDH 20/05/99 	{
//DEADCODE RDH 20/05/99 		 unfgrplead = ((AirStruc*)caller->ai.unfriendly)->FindGroupLeader();
//DEADCODE RDH 20/05/99 	}
//DEADCODE RDH 20/05/99 	if (((AirStruc*)caller->ai.unfriendly)->nationality == caller->nationality)
//DEADCODE RDH 20/05/99 		retval = ChooseManoeuvre(caller,trg,FALSE);
//DEADCODE RDH 20/05/99 	else if (trggrplead != unfgrplead)
//DEADCODE RDH 20/05/99 	{
//DEADCODE RDH 20/05/99 		InterceptRangeFromTo(caller,trg);
//DEADCODE RDH 20/05/99 		if 	(caller->Range  < ENGAGERANGE)
//DEADCODE RDH 20/05/99 			if (caller->leader==NULL)
//DEADCODE RDH 20/05/99 				if (trg->ai.attacker==NULL)
//DEADCODE RDH 20/05/99 					retval = ChooseManoeuvre(caller,trg,FALSE);
//DEADCODE RDH 20/05/99 	}
//DEADCODE RDH 20/05/99 	return(retval);

	bool retval = FALSE;
	
	AirStruc* trggrplead = trg->FindGroupLeader();
	AirStruc* unfgrplead = NULL;
	if (		(caller->ai.unfriendly)
			&&	(caller->ai.unfriendly->Status.size==AIRSTRUCSIZE)
	   )
	{
		unfgrplead = ((AirStruc*)caller->ai.unfriendly)->FindGroupLeader();
	
		if (trggrplead != unfgrplead)
		{
			InterceptRangeFromTo(caller,trg);
			if 	(caller->Range  < ENGAGERANGE)
				if (caller->leader==NULL)
					if (trg->ai.attacker==NULL)
					{
						if (caller->IsUsingPilotedAcLog())
							if (!unfgrplead->IsUsingPilotedAcLog())
								Persons2::UpdateLog(unfgrplead,0,EventLog::APPROACHED);


						retval = ChooseManoeuvre(caller,trg,FALSE);
					}
		}
	}
	return(retval);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseManoeuvre
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
bool	ArtInt::ChooseManoeuvre(AirStruc* caller,AirStruc* trg, bool newspot)
{
	bool retval;
	tGroupLevel group = GroupLevel(caller);
	if (group == GROUP_LONER)
	{
		retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_ENGAGE,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SelectTarget);	
	}else
	{
		RndVal	rndnum = ((RndVal)Math_Lib.rnd(2));

		trg = trg->FindGroupLeaderInFormation();

		if  (		TargetOnCallerTail(caller, trg, ANGLES_80Deg)
				&&	TargetFacingCaller(caller, trg, ANGLES_80Deg)
				&&	((caller->World.Y - trg->World.Y) < FT_2000)
			)
		{//attacked from rear and no height advantage
			if (EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
			{
				if (caller->Range > DANGERRANGE)
					_Miles.SequenceAudible(MOOD_TROUBLED);
				else
					_Miles.SequenceAudible(MOOD_DOOMED);

			}
			retval = SendMsgAndCall(ChooseBanditOnTailMsg(MSG_SPOTTED,caller,trg, caller,newspot),DefensiveManoeuvre);
		}else if  (		CallerFacingTarget(caller, trg, ANGLES_45Deg)
					&&	TargetFacingCaller(caller, trg, ANGLES_45Deg)
					)
		{//head on
			if (EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
				_Miles.SequenceAudible(MOOD_TENSE);

			retval = SendMsgAndCall(ChooseBanditHeadOnMsg(MSG_SPOTTED,caller,trg, caller,newspot),AttackingManoeuvre);
		
		}else
		{
			if (EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
			{
				if (		CallerOnTargetTail(caller, trg, ANGLES_45Deg)
						&&	CallerFacingTarget(caller, trg, ANGLES_45Deg)
					)
					_Miles.SequenceAudible(MOOD_HOPEFUL);
				else
					_Miles.SequenceAudible(MOOD_NEUTRAL);

			}
			retval = SendMsgAndCall(ChooseBanditRelMsg(MSG_SPOTTED,caller,trg, caller,newspot),AttackingManoeuvre);
		}
	}
	return ((bool)retval);
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseBanditRelMsg
//Author		R. Hyde 
//Date			Wed 20 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_STRUC	ArtInt::ChooseBanditRelMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot)
{
	ScriptTables script;

	if (newspot)
	{
			script = SCRIPT_BANDIT_RELPOS;
	}else
	{
		if (caller->Range < DANGERRANGE)
			script = SCRIPT_MOREBANDITSEXCITED;
		else
			script = SCRIPT_MOREBANDITS;
	}
	return(MESSAGE_STRUC(script, mtype,caller,trg, callee));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseBanditOnTailMsg
//Author		R. Hyde 
//Date			Wed 20 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_STRUC	ArtInt::ChooseBanditOnTailMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot)
{
	ScriptTables script;

	if (newspot)
	{
		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
		if (rndpc >  RND50PC)
		{
				if (caller->Range < DANGERRANGE)
					script = SCRIPT_BANDITSBEHINDEXCITED;
				else
					script = SCRIPT_BANDITSBEHIND;
		}else
			script = SCRIPT_BANDIT_RELPOS;
	}else
	{
		if (caller->Range < DANGERRANGE)
			script = SCRIPT_MOREBANDITSEXCITED;
		else
			script = SCRIPT_MOREBANDITS;
	}
	return(MESSAGE_STRUC(script, mtype,caller,trg, callee));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseBanditHeadOnMsg
//Author		R. Hyde 
//Date			Wed 20 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_STRUC	ArtInt::ChooseBanditHeadOnMsg(MsgType mtype, AirStruc* caller,AirStruc* trg,AirStruc*  callee, bool newspot)
{
	ScriptTables script;

	if (newspot)
	{
		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
		if (rndpc >  RND50PC)
			script = SCRIPT_BANDITSAHEAD;
		else
			script = SCRIPT_BANDIT_RELPOS;
	}else
	{
		if (caller->Range < DANGERRANGE)
			script = SCRIPT_MOREBANDITSEXCITED;
		else
			script = SCRIPT_MOREBANDITS;
	}
	return(MESSAGE_STRUC(script, mtype,caller,trg, callee));
}
//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TABLEAI(FriendliesUnderAttack, AirStrucPtr)
{
	{PHRASE_WELLGOHELP,		&SelectTarget,	PHRASE_ASSISTCONFIRM},	  //RDH 24/05/99
	{PHRASE_CONTINUE,	&DoNothing,		PHRASE_IGNOREFORNOW},
	{PHRASE_PARTS_S},
	{PHRASE_PARTS_S}
};
INSTANCEAI(FriendliesUnderAttack, AirStrucPtr)
{
	bool retval = false;
	if (caller->ai.morale >= MORALE_GOOD)
	{
		AirStruc*	recipient = caller;
		if 	(		(trg->ai.unfriendly)
				&&	(trg->ai.unfriendly->Status.size==AIRSTRUCSIZE)
			)
			  recipient = (AirStruc*)trg->ai.unfriendly;
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OUTNUMBEREDREPLY, MSG_MIGREPORTED_REPLY, caller, trg, recipient));
		retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_SELECTYOUROWNTARGETS, MSG_ASSISTFRIENDLIESUNDERATTACK,caller, trg, caller),SelectTarget);
	}
	return(retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoesFriendNeedHelp
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	Assess whether friendly needs helping out
//				caller and trg are same nationality
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::DoesFriendNeedHelp(AirStruc* caller,AirStruc* trg)
{
	SLong	RangeEyeTrg = caller->Range;
	bool retval = FALSE;
	if  (		((trg->duty&ACTIONCODE)==DA_CAP)
			&&	(trg->classtype->aerobaticfactor != AEROBATIC_LOW) //RDH 21/06/99
		)
	{
		if (	trg->ai.attacker
			&&	trg->ai.attacker->Status.size==AIRSTRUCSIZE
			&&	(!trg->ai.attacker->ai.attacker)
			&&	(trg->Range < VISIBLERANGE)
			)
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BANDIT_RELPOS, MSG_BOGEYCALL, caller, trg->ai.attacker,trg));
		}
	}else if  (		((caller->duty&ACTIONCODE)==DA_CAP)
				&&	(caller->classtype->aerobaticfactor != AEROBATIC_LOW)								//RDH 09/05/99
			   )
	{//non CAP a/c including bombers cannot consider helping
		if (	trg->ai.attacker
			&&	trg->ai.attacker->Status.size==AIRSTRUCSIZE
			)
		{//trg has attacker that is an aircraft
			caller->InterceptandRange(&trg->ai.attacker->World);
			if (	(	(!caller->ai.unfriendly)
					||	(	((AirStruc*)caller->ai.unfriendly)->nationality == caller->nationality)
					||	((RangeEyeTrg - caller->Range) > MILES01)
					||	(caller->movecode == AUTO_TRACKINGBOGIE)		//busy but just tracking bogies
					||	(		(caller == Persons2::PlayerGhostAC) 		//player busy but just tracking bogies
							&&	 (Persons2::PlayerSeenAC->movecode == AUTO_TRACKINGBOGIE)
						)

					)
				)
			{//caller doesn't have unf or unf is really on caller's side or this attacker closer

				if 	(!((AirStruc*)*trg->ai.attacker)->ai.attacker)
				{//trg attacker is not under attack

					if (trg->classtype->aerobaticfactor == AEROBATIC_LOW)
						SendMsgAndCall(MESSAGE_STRUC(SCRIPT_UNPROTECTEDBOMBERUNDERATTACK,MSG_FRIENDLIESUNDERATTACK,caller,(AirStruc*)*trg->ai.attacker,caller),FriendliesUnderAttack);
					else
						SendMsgAndCall(MESSAGE_STRUC(SCRIPT_FIGHTERSNEEDHELP,MSG_FRIENDLIESUNDERATTACK,caller,(AirStruc*)*trg->ai.attacker,caller),FriendliesUnderAttack);
				}else
				{
					if (trg->classtype->aerobaticfactor == AEROBATIC_LOW)
						SendMsgAndCall(MESSAGE_STRUC(SCRIPT_PROTECTEDBOMBERUNDERATTACK,MSG_FRIENDLIESUNDERATTACK,caller,(AirStruc*)*trg->ai.attacker,caller),FriendliesUnderAttack);
					else
					{
						if (EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
						{
							if (trg->ai.eventlog->stage < EventLog::SPOTTEDDOGFIGHT
								&& !trg->IsUsingPilotedAcLog()				  //JIM 21/07/99
								)
							{
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DOGFIGHT, MSG_FRIENDLIESUNDERATTACK, caller, trg, Manual_Pilot.ControlledAC2));
								Persons2::UpdateLog(trg,0,EventLog::SPOTTEDDOGFIGHT);
							}

						}
					}
				}
			}else
			{//friendly needs help but we are busy

				AlertFighters(caller,trg->ai.attacker,trg);
			}
		}else
		{//seen friendly not under attack
				if  (		(Manual_Pilot.ControlledAC2->fly.pModel)
				&&	(!Manual_Pilot.ControlledAC2->fly.pModel->GearTouched)
				)
				if (trg->Range<RECOGNISERANGE-METRES500)
				if	(		(EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
						&&	(trg->movecode != AUTO_FAC)			//don't want to be told about fac
						&&	(!caller->InSameWave(trg))
						&&	(!caller->formpos)					//only let group leaders through
						&& !trg->IsUsingPilotedAcLog()				  //JIM 21/07/99
					)
					{
						if (trg->ai.eventlog->stage < EventLog::SEENBYPLAYERS)
						{
	 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FRIENDLIES, MSG_FRIENDLIESNOTUNDERATTACK, caller, trg, Manual_Pilot.ControlledAC2));
							caller->PlayerSequenceAudible(FIL_MUSIC_FRIENDLY_SEEN);
						}
						Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);
					}
		}

	//	caller->PlayerSequenceAudible(FIL_MUSIC_FRIENDLY_SEEN);		
	//	caller->PlayerSequenceAudible(FIL_MUSIC_SNEAKING_AWAY);		
	}else
	{
		if  (		(Manual_Pilot.ControlledAC2->fly.pModel)
		&&	(!Manual_Pilot.ControlledAC2->fly.pModel->GearTouched)
		)
		if (trg->Range<RECOGNISERANGE-METRES500)
		if	(		(EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
				&&	(trg->movecode != AUTO_FAC)			//don't want to be told about fac
				&&	(!caller->InSameWave(trg))
				&&	(!caller->formpos)					//only let group leaders through
				&& !trg->IsUsingPilotedAcLog()				  //JIM 21/07/99
			)
			{
				if (trg->ai.eventlog->stage < EventLog::SEENBYPLAYERS)
				{
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FRIENDLIES, MSG_FRIENDLIESNOTUNDERATTACK, caller, trg, Manual_Pilot.ControlledAC2));
					caller->PlayerSequenceAudible(FIL_MUSIC_FRIENDLY_SEEN);
				}
				Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);
			}
	}
	caller->Range = RangeEyeTrg;
	return(retval);
}		
			
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IfEyeIsAndTrgIsNotUsingPilotedAcLog
//Author		R. Hyde 
//Date			Wed 20 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::EyeIsAndTrgIsNotInPlayersGroup(AirStruc* caller,AirStruc* trg)
{
	if  (		(caller->PlayerInGroup())
			&&	(!trg->PlayerInGroup())
		)
	   	return(true);
	else
		return(false);

//DEADCODE RDH 22/06/99  	if 	(		(caller->IsUsingPilotedAcLog())
//DEADCODE RDH 22/06/99  			&& (!trg->IsUsingPilotedAcLog())
//DEADCODE RDH 22/06/99  		)
//DEADCODE RDH 22/06/99  			return(true);
//DEADCODE RDH 22/06/99  		else
//DEADCODE RDH 22/06/99  			return(false);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EngageAppropriate()
//Author		R. Hyde 
//Date			29/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::EngageAppropriate(AirStruc* caller,AirStruc* trg)
{
	bool retval;
	if (	(caller->ai.threatlevel > BANDITFIRING)
		||	((caller->Range < WEAPONSRANGE) &&	(caller->ai.threatlevel >= BANDITINWEAPONSRANGE))
		||	((caller->Range < DANGERRANGE) &&	(caller->ai.threatlevel >= BANDITINDANGERRANGE))
		||	((caller->Range < ENGAGERANGE) &&	(caller->ai.threatlevel >= BANDITINENGAGERANGE))
		||	((caller->Range < COMBATRANGE) &&	(caller->ai.threatlevel >= BANDITINCOMBATRANGE))
		||	(caller->ai.threatlevel >= BANDITANYWHERE)
		||	(		(caller->ai.threatlevel == BANDITINENGAGERANGEOFFRIENDLY)
				&& 	(trg->ai.unfriendly)
				&& 	(RangeFromTo(trg, (AirStruc*)trg->ai.unfriendly) < ENGAGERANGE)
			)
	   )
	{//according to threat level it is ok for caller to respond 

//DEADCODE RDH 08/03/99 		if 	(!DecoysInGroup(caller))
//DEADCODE RDH 08/03/99 		{
			if (!(	(caller->Range > DANGERRANGE)
					&&
					(		(caller->ai.aggressionlevel == AL_TRAINING)
						||	(		(caller->ai.aggressionlevel == AL_DEFENSIVE) 
								&&	(		((trg->nationality == NAT_RED) && (!AcHasBombs(trg)))
										||	((trg->nationality == NAT_BLUE) && ((caller->World.Y - trg->World.Y) > FT_3000)))
									)
						||	((caller->ai.aggressionlevel == AL_ATTACKBOMBERSONLY) && (trg->classtype->aerobaticfactor >= AEROBATIC_FIGHTER))
						||	((caller->ai.aggressionlevel == AL_SPLITFORCE) && (!ForceHasBombers(trg)))
						||	(		(caller->ai.aggressionlevel == AL_ATTACKWEAKNESSES) 
								&&	(		!BingoFuel(trg)
										&&	!trg->AircraftDamaged()
										&&	!Winchester(trg)
									)
							)															
						 ||	(		(caller->nationality == NAT_BLUE) //RDH 30/06/99
								&&	(trg->World.Y >= FT_45000)		  //RDH 30/06/99

							)
					)
				))
			{
					retval = true;
			}else
				retval = false;
//DEADCODE RDH 08/03/99 		}else
//DEADCODE RDH 08/03/99 			retval = false;
	}else
		//## wait for threatlevel is setup, change to false then 
		retval = true;
	return(retval);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindGroupLeaderInFormation()
//Author		R. Hyde 
//Date			29/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStruc* AirStruc::FindGroupLeaderInFormation()
{
	AirStruc* grplead;
	grplead = this;
	//find the leader to go for
	//Always go for leader of target's flight
	if (grplead->information && grplead->leader)
		grplead=*grplead->leader;
	//go for their group leader
	if (grplead->formpos && grplead->fly.leadflight && grplead->information)
		grplead=grplead->fly.leadflight;

	return(grplead);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindGroupLeaderClose()
//Author		R. Hyde 
//Date			29/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStruc* AirStruc::FindGroupLeaderClose()
{
	AirStruc* grplead;
	grplead = this;
	//find the leader to go for
	//Always go for leader of target's flight
	if (grplead->leader && Art_Int.AircraftAreClose(grplead, (AirStruc*)grplead->leader))
		grplead=*grplead->leader;
	//go for their group leader
	if (grplead->formpos && grplead->fly.leadflight && Art_Int.AircraftAreClose(grplead, grplead->fly.leadflight))
		grplead=grplead->fly.leadflight;

	return(grplead);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindGroupLeader()
//Author		R. Hyde 
//Date			 //RDH 18/02/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStruc* AirStruc::FindGroupLeader()
{
	AirStruc* grplead;
	grplead = this;
	//find the leader to go for
	if (grplead->leader)
		grplead=*grplead->leader;
	//go for their group leader
	if (grplead->formpos && grplead->fly.leadflight)
		grplead=grplead->fly.leadflight;

	return(grplead);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		R. Hyde 
//Date			 //RDH 18/02/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::Escorting(AirStruc* ac)
{
	AirStruc* grplead = ac->FindGroupLeader();
	if (grplead->fly.leadflight)
		return (true);
	else
		return(false);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroupLevel
//Author		R. Hyde 
//Date			Mon 16 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ArtInt::tGroupLevel ArtInt::GroupLevel(AirStruc* caller)
{
	if (		(caller->leader)
	   		&&  (caller->leader->information)
		)
		caller = (AirStruc*)caller->leader;

	if (		(caller->fly.leadflight)
	   		&&  (caller->fly.leadflight->information)
		)
		caller = (AirStruc*)caller->fly.leadflight;

	if 	(		(caller->fly.nextflight)
	   		&&  (caller->fly.nextflight->information)
		)
	{
		if 	(		(caller->fly.nextflight->fly.nextflight)
		   		&&  (caller->fly.nextflight->fly.nextflight->information)
			)
			return(GROUP_SQUADRON);
		else
			return(GROUP_FLIGHT);

//DEADCODE RDH 23/02/99 		 AirStruc*	currac = caller->fly.nextflight;
//DEADCODE RDH 23/02/99 		 int count = 1;
//DEADCODE RDH 23/02/99 		 while  (		(currac->fly.nextflight)
//DEADCODE RDH 23/02/99 					&&	(currac->fly.nextflight->information)
//DEADCODE RDH 23/02/99 				)
//DEADCODE RDH 23/02/99 		 {
//DEADCODE RDH 23/02/99 			currac = currac->fly.nextflight;
//DEADCODE RDH 23/02/99 			count++;
//DEADCODE RDH 23/02/99 		 }
//DEADCODE RDH 23/02/99 		if (count >= 6)
//DEADCODE RDH 23/02/99 			//squadron is 6 or more "elements" or flights in internal naming
//DEADCODE RDH 23/02/99 			return(GROUP_SQUADRON);
//DEADCODE RDH 23/02/99 		else
//DEADCODE RDH 23/02/99 			return(GROUP_FLIGHT);

	}else
	{
		if  (	(caller->Follower())
	   		&&  (caller->Follower()->information)
			)
			return(GROUP_ELEMENT);
		else
			return(GROUP_LONER);
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroupLevelNotInFormation
//Author		R. Hyde 
//Date			Mon 16 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ArtInt::tGroupLevel ArtInt::GroupLevelNotInFormation(AirStruc* caller)
{
	if (caller->leader)
		caller = (AirStruc*)caller->leader;

	if (caller->fly.leadflight)
		caller = (AirStruc*)caller->fly.leadflight;

	if 	(		(caller->fly.nextflight)
		)
	{
		if 	(		(caller->fly.nextflight->fly.nextflight)
			)
			return(GROUP_SQUADRON);
		else
			return(GROUP_FLIGHT);

	}else
	{
		if  (	(caller->Follower())
			)
			return(GROUP_ELEMENT);
		else
			return(GROUP_LONER);
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptandRange
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description		
//
//Inputs		
//
//Returns	"Global" Range, HdgIntercept and PitchIntercept
//
//------------------------------------------------------------------------------
void ArtInt::InterceptRangeFromTo(AirStruc* from, AirStruc* to)

{


	SLong deltax = to->World.X - from->World.X;
	SLong deltay = to->World.Y - from->World.Y;
	SLong deltaz = to->World.Z - from->World.Z;
	Math_Lib.Intercept (deltax,deltay,deltaz,from->Range,from->HdgIntercept,from->PitchIntercept);
}
SLong ArtInt::RangeFromTo(AirStruc* from, AirStruc* to)
{
	ANGLES	oldhdgint, oldpitchint;
	SLong	oldrange;
	SLong range;
	
	oldhdgint = from->HdgIntercept;
	oldpitchint = from->PitchIntercept;
	oldrange  = from->Range;

	InterceptRangeFromTo(from, to);
	range = from->Range;

	from->PitchIntercept = oldpitchint;
	from->HdgIntercept = oldhdgint;
	from->Range = oldrange;


	return (range);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AcHasBombs
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::AcHasBombs(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceHasBombers(trg)
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::ForceHasBombers(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BingoFuel
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::BingoFuel(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Winchester
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::Winchester(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpRemainderOfGroupToEngage
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
void	ArtInt::SetUpRemainderOfGroupToEngage(AirStruc* caller,AirStruc* trg,MANOEUVRE manoeuvre,ANGLES desiredhdg,ANGLES  desiredpitch, bool surprised)
{
	//send everyone in our flight against everyone in his flight
	AirStrucPtr	currtrg=trg;
	AirStrucPtr	currfol=caller;
	while	(		((currfol=*currfol->Follower())!=NULL)
				&&	(		(currfol->information)
//DEADCODE RDH 19/05/99 when needed? relying on information for split force						||	(AircraftAreClose(currfol, caller))
					)
			)
		currtrg=SetFollowerEngage(currfol,currtrg, manoeuvre,desiredhdg, desiredpitch,surprised);

	//send each flight in our squad against each of his flights

//DEADCODE RDH 06/04/99 	force back to ordinary stuff for testing only
//DEADCODE RDH 06/04/99 	manoeuvre = MANOEUVRE_SELECT;

	currtrg=trg;
	currfol=caller;
//DEADCODE RDH 23/02/99 	need to be able to set upon a follower if (currtrg->leader==NULL)
	while 	(		((currfol=currfol->fly.nextflight)!=NULL)
				&&	(		(currfol->information)
//DEADCODE RDH 19/05/99 when needed? relying on information for split force						||	(AircraftAreClose(currfol, caller))
					)
				
			)
		currtrg=SetFlightEngage(currfol,currtrg, manoeuvre,desiredhdg, desiredpitch,surprised);
		
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrepareForCombat
//Author		 //RDH 04/03/99
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::PrepareForCombat(AirStrucPtr caller)
{
	if (		(caller->nationality == Manual_Pilot.ControlledAC2->nationality)
			&&	(caller->AcIsGroupLeader()) 
			&& (!caller->AcIsPlayer())
			&&	(!caller->weap.FuelDumped)
		)
	{
		AirStruc*	callee = caller->FindABuddyWithPlayerGivenPriority();
		if (!callee)
			//if there is no buddy pilot talks to himself
			callee = caller;
 		SendMsgAndCall(MESSAGE_STRUC(SCRIPT_JETTISONTANK, MSG_STATUSREQUEST, caller, NULL, callee), JettisonTanks);	
 
  		if	(		(caller->classtype->visible != F86)
				&&	(caller->classtype->phrasename != PHRASE_MIGS)
//DEADCODE RDH 10/05/99   				&&	(caller->classtype->visible != MIG15)
 				&&	(!caller->weap.StoresDumped)
  			)
  			SendMsgAndCall(MESSAGE_STRUC(SCRIPT_JETTISONSTORES, MSG_STATUSREQUEST, caller, NULL, callee), JettisonStores);	
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetEngage
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
void	ArtInt::SetEngage(AirStrucPtr caller,AirStrucPtr trg,MANOEUVRE manoeuvre,ANGLES   desiredhdg,ANGLES   desiredpitch, bool surprised)
{
#ifndef	NDEBUG
 	if(caller->classtype->aerobaticfactor == AEROBATIC_LOW)
 		INT3;													//CSB 06/05/99
 	//TRYING TO PUT A HEAVY BOMBER INTO COMBAT
#endif
	if (caller->IsUsingPilotedAcLog() || (trg && trg->IsUsingPilotedAcLog()))//JIM 03Jun99
		OverLay.CancelAccel();									//JIM 03Jun99

	if (caller==Persons2::PlayerSeenAC)							//AMM 28Aug98
		caller=Persons2::PlayerGhostAC;							//AMM 28Aug98

//I don't know why we did this, it messes up links 
//DEADCODE RDH 13/06/99 	if (	caller->ai.unfriendly
//DEADCODE RDH 13/06/99 		&&	caller->ai.unfriendly->Status.size==AIRSTRUCSIZE
//DEADCODE RDH 13/06/99 		&& ((AirStrucPtr)*caller->ai.unfriendly)->ai.attacker==caller
//DEADCODE RDH 13/06/99 		)
//DEADCODE RDH 13/06/99 		((AirStrucPtr)*caller->ai.unfriendly)->ai.attacker=NULL;
	if (trg)
	{
		if (Manual_Pilot.ControlledAC2 == trg)
		{
			trg = Persons2::PlayerGhostAC;
		}
//DeadCode AMM 28Aug98 		if (!_Replay.Playback && caller==Persons2::PlayerGhostAC)
//DeadCode AMM 28Aug98 		{
//DeadCode AMM 28Aug98 	//		Manual_Pilot.AutoToggle(Manual_Pilot.AUTO);
//DeadCode AMM 28Aug98 //			Manual_Pilot.AutoToggle(Manual_Pilot.AUTO);
//DeadCode AMM 28Aug98 			caller= Manual_Pilot.ControlledAC2;
//DeadCode AMM 28Aug98 		}

		if  (		(caller->ai.unfriendly==trg)
				&&	(caller->movecode != AUTO_TRACKINGBOGIE)
			)
		{	//informational
			//usually set up already 
			//if coming from precombat we need to switch to combat
				if (		(caller->Range  < COMBATRANGE)
						&&	(caller->movecode==AUTO_PRECOMBAT)
					)
				{
					caller->information=FALSE;
					caller->manoeuvretime=0;
					caller->movecode=AUTO_COMBAT;
//DEADCODE RDH 06/04/99 					caller->ai.manoeuvre = MANOEUVRE_SELECT;

				}else if (caller->movecode != AUTO_COMBAT)
				{
					caller->movecode=AUTO_PRECOMBAT;
				}

		}else
		{//new engage

			PrepareForCombat(caller);
			caller->ai.ManStep = PHASERESET;
			if (manoeuvre != MANOEUVRE_SELECT)
			{
				caller->ai.manoeuvre = manoeuvre;
				caller->ai.desiredhdg = desiredhdg;
				caller->ai.desiredpitch = desiredpitch;
			}else
			{
				caller->ai.desiredhdg = ANGLES_0Deg;
				caller->ai.desiredpitch = ANGLES_0Deg;
			
//DEADCODE RDH 24/02/99 				if (caller->ai.firsttactic == TACTIC_LINEASTERN)
//DEADCODE RDH 24/02/99 					caller->ai.manoeuvre = MANOEUVRE_LINEASTERN;
//DEADCODE RDH 24/02/99 				else if (caller->ai.firsttactic == TACTIC_LINEABREAST)
//DEADCODE RDH 24/02/99 					caller->ai.manoeuvre = MANOEUVRE_LINEABREAST;
//DEADCODE RDH 24/02/99 				else if (caller->ai.firsttactic == TACTIC_DIVEANDZOOM)
//DEADCODE RDH 24/02/99 					caller->ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
//DEADCODE RDH 24/02/99 				else if (caller->ai.firsttactic == TACTIC_SCATTER)
//DEADCODE RDH 24/02/99 					caller->ai.manoeuvre = MANOEUVRE_LEADPURSUIT;
//DEADCODE RDH 05/04/99 				if (	(caller->ai.firsttactic == TACTIC_ROUNDABOUT)
//DEADCODE RDH 05/04/99 							&&		(caller->ai.threatlevel != BANDITFIRING)	
//DEADCODE RDH 05/04/99 							&&		(caller->ai.threatlevel != BANDITINENGAGERANGEOFFRIENDLY)
//DEADCODE RDH 05/04/99 						)
//DEADCODE RDH 05/04/99 					SetRoundAboutAc(caller);
//DEADCODE RDH 05/04/99 				else
					caller->ai.manoeuvre=MANOEUVRE_SELECT;
			}
			if (trg)
			{

				if (	!trg->ai.attacker
					||	AirStrucPtr(*trg->ai.attacker)->ai.unfriendly!=trg
					)
				{
					if (	caller->ai.unfriendly
							&&	caller->ai.unfriendly->Status.size==AIRSTRUCSIZE
							&& ((AirStrucPtr)*caller->ai.unfriendly)->ai.attacker==caller
						)//reset old link
						((AirStrucPtr)*caller->ai.unfriendly)->ai.attacker=NULL;

					trg->ai.attacker=caller;
				}
			}
			caller->ai.unfriendly=trg;

			caller->manoeuvretime=0;	//CSB 24/06/99	


			if (		(caller->Range >COMBATRANGE)
					&&	(manoeuvre == MANOEUVRE_SELECT)
				)
				caller->movecode=AUTO_PRECOMBAT;
			else
			{
				caller->information=FALSE;
//DeadCode CSB 24/06/99					caller->manoeuvretime=0;
				caller->movecode=AUTO_COMBAT;
			}
//DEADCODE RDH 19/05/99 			if (caller->Range < INSIDEWEAPONSRANGE)
//DEADCODE RDH 19/05/99 				caller->ai.manoeuvre=MANOEUVRE_SELECT;			//surprised so no preplanning
//##rdh test purposes
			if (caller==Persons2::PlayerGhostAC)
			{
				caller= Manual_Pilot.ControlledAC2;
				caller->ai.unfriendly=trg;
				caller->information=FALSE;
//DeadCode CSB 24/06/99					caller->manoeuvretime=0;
				caller->movecode=AUTO_COMBAT;
				caller->ai.manoeuvre=MANOEUVRE_SELECT;

			}

			_DPlay.OwnerChangeDecision(caller,trg);				//AMM 27Nov98

			//##	if (surprised)
			//##modify morale based on range
		}
	}else
	{//assume that if we get here with no target then weldedwing was required
		//Just follow leader...
		if	(		(caller->leader)
				&&	(((AirStrucPtr)caller->leader)->ai.unfriendly)
				&& (((AirStrucPtr)caller->leader)->ai.unfriendly->Status.size == AIRSTRUCSIZE)
			)
			//20Apr99
			caller->ai.unfriendly = ((AirStrucPtr)caller->leader)->ai.unfriendly;		//RJS 08Apr99
		else
			caller->ai.unfriendly = NULL;

		caller->ai.ManStep = PHASERESET;
		caller->information = TRUE;
		caller->ai.desiredhdg = ANGLES_0Deg;
		caller->ai.desiredpitch = ANGLES_0Deg;
		caller->ai.manoeuvre = MANOEUVRE_WELDEDWINGMAN; 
		if (caller->Range >COMBATRANGE)
			caller->movecode=AUTO_PRECOMBAT;
		else
		{
			
			caller->manoeuvretime=0;
			caller->movecode=AUTO_COMBAT;
		}
	}
}			
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedNeutral
//Author		R. Hyde 
//Date			Fri 6 Mar 1998
//
//Description	Not needed for MiG Alley
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::SpottedNeutral(AirStruc* caller,AirStruc* trg)
{
	return(false);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeForceToRespond
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
bool ArtInt::MakeForceToRespond (AirStruc* caller, AirStruc* trg, tGroupLevel group, bool& splitmanappropriate)
{
//Confusion is possible here because we are considering two splits:
//		split force to respond from rest of force
//		split force that is responding into 2 for tactical advantage

	int trgnum = GuessFormationSize(caller, trg);
	int callernum = CountFormationSize(caller);
	splitmanappropriate = false;
	int	respondnum;

	if  (	(		(caller->ai.morale < MORALE_MEDIUM) && (callernum < trgnum*2)
				||	(caller->ai.morale < MORALE_GOOD) && (callernum < trgnum)
			)
			&&	(callernum > 1)		//singleton get stuck in just t omake it interesting //RDH 18/06/99
		)
		{
			return(false);
		}else
		{
			if (caller->ai.morale < MORALE_MEDIUM)
				respondnum = 2*trgnum;
			else
				respondnum = trgnum;
			//respondnum is the number of ac we want to respond with
			if (respondnum < callernum)
			{// 	consider split manoeuvre
				int minacnum = 2 * respondnum;
				
//DEADCODE RDH 23/02/99 				int minacnum;
//DEADCODE RDH 23/02/99 				 if  (group == GROUP_ELEMENT)
//DEADCODE RDH 23/02/99 					 minacnum = 2;
//DEADCODE RDH 23/02/99 				else  if (group == GROUP_FLIGHT)
//DEADCODE RDH 23/02/99 					 minacnum = 4;
//DEADCODE RDH 23/02/99 				else if (group == GROUP_SQUADRON)
//DEADCODE RDH 23/02/99 					 minacnum = 8;

				if (minacnum <= callernum )
				{//can split force into 2 for tactical advantage
					respondnum = minacnum;
					splitmanappropriate = true;
//DEADCODE DAW 13/05/99 					else
//DEADCODE DAW 13/05/99 						splitmanappropriate = false;		
				}
// 	consider split force
				int	count = 1;
				AirStruc*	foll = caller;
				while (foll->Follower() !=NULL)
				{
					count++;
					foll =(AirStruc*)foll->Follower();
				}
				int	respondingelements = respondnum/count;
				count = 0;
				AirStruc*	lead2 = caller;
				while (	(lead2->fly.nextflight != NULL) &&	(count < respondingelements))
				{
					lead2 = lead2->fly.nextflight;		
					count++;
				}
				if (	(lead2 != NULL)	&&	(count >= respondingelements) )
					//break the link with the remaining forces
					lead2->information=FALSE;


			}
			return(true);
		}	

}
bool	ArtInt::CallerFacingTarget(AirStruc*  caller, AirStruc*  trg, ANGLES angle)
{
	ANGLES delta = caller->HdgIntercept + angle - caller->hdg;		  //RDH 12/06/99
	ANGLES anglerange = angle + angle;								  //RDH 12/06/99
	if (delta << anglerange)										  //RDH 12/06/99
	 	return(true);
	else
		return(false);

}
bool	ArtInt::TargetFacingCaller(AirStruc*  caller, AirStruc*  trg,ANGLES angle)
{
	ANGLES delta = trg->HdgIntercept + ANGLES_180Deg + angle - trg->hdg;		  //RDH 12/06/99
	ANGLES anglerange = angle + angle;								  //RDH 12/06/99
	if (delta << anglerange)										  //RDH 12/06/99
	 	return(true);
	else
		return(false);

}
bool	ArtInt::TargetOnCallerTail(AirStruc*  caller, AirStruc*  trg, ANGLES angle)
{
	ANGLES delta = caller->HdgIntercept + ANGLES_180Deg + angle - caller->hdg; //RDH 12/06/99
	ANGLES anglerange = angle + angle;								  //RDH 12/06/99
	if (delta << anglerange)										  //RDH 12/06/99
	 	return(true);
	else
		return(false);

}
bool	ArtInt::CallerOnTargetTail(AirStruc*  caller, AirStruc*  trg, ANGLES angle)
{
	ANGLES delta = caller->HdgIntercept + angle - caller->hdg;		  //RDH 12/06/99
	ANGLES anglerange = angle + angle;								  //RDH 12/06/99
	if (delta << anglerange)										  //RDH 12/06/99
	 	return(true);
	else
		return(false);

}
//DEADCODE RDH 08/03/99 bool	ArtInt::DecoysInGroup(AirStruc*  caller)
//DEADCODE RDH 08/03/99 {
//DEADCODE RDH 08/03/99 
//DEADCODE RDH 08/03/99 		AirStrucPtr	currfol=caller;
//DEADCODE RDH 08/03/99 
//DEADCODE RDH 08/03/99 		
//DEADCODE RDH 08/03/99 		if (caller->leader==NULL)
//DEADCODE RDH 08/03/99 		{
//DEADCODE RDH 08/03/99 			while 	(		((currfol=currfol->fly.nextflight)!=NULL)
//DEADCODE RDH 08/03/99 							&&	(currfol->information)
//DEADCODE RDH 08/03/99 					)
//DEADCODE RDH 08/03/99 			{
//DEADCODE RDH 08/03/99 				if	(	(currfol->ai.firsttactic == TACTIC_DECOYACTIVE)
//DEADCODE RDH 08/03/99 					||	(currfol->ai.firsttactic == TACTIC_DECOYPASSIVE)
//DEADCODE RDH 08/03/99 					)
//DEADCODE RDH 08/03/99 					{
//DEADCODE RDH 08/03/99 						SetDecoysInGroup(currfol);
//DEADCODE RDH 08/03/99 						return(true);
//DEADCODE RDH 08/03/99 					}
//DEADCODE RDH 08/03/99 			}
//DEADCODE RDH 08/03/99 		}
//DEADCODE RDH 08/03/99 		return(false);
//DEADCODE RDH 08/03/99 }
//------------------------------------------------------------------------------
AirStrucPtr	ArtInt::SetFlightWhoCanEngage(AirStrucPtr caller,AirStrucPtr trg)
{
	AirStrucPtr	tmpt=trg;
	if (tmpt==NULL)	return(tmpt);
	switch (caller->ai.flighttactics)
	{
		case TOPCOVER:
		case SWORDANDSHIELD:
		case WELDEDWING:
		{	
			tmpt=NULL;
			break;
		}
		case LOOSEDEUCE:
		{		 
			tmpt=nextfl(trg,true);								//JIM 19Sep97
			if (!tmpt)
				//can't fimd a next flight so go down the followers
				tmpt=nextfol(trg,true);
				if (!tmpt)
				{
 					if (trg->fly.leadflight)
					{	
						if (trg->information)
 							tmpt=trg->fly.leadflight;
						else
						{
							SLong	oldrange = trg->Range;
						   trg->InterceptandRange(&trg->fly.leadflight->World);
						   if (trg->Range < RECOGNISERANGE)
								tmpt = trg->fly.leadflight;			  //RDH 23/06/99
					   		trg->Range = oldrange; 
						}
					}
				}

			break;
		}

	}
	return (tmpt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFollowerWhoCanEngage
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
AirStrucPtr	ArtInt::SetFollowerWhoCanEngage(AirStrucPtr caller,AirStrucPtr trg)
{
	AirStrucPtr	tmpt=trg;
	if (tmpt==NULL)	return(tmpt);
	switch (caller->ai.elementtactics)
	{
		case TOPCOVER:
		case SWORDANDSHIELD:
		case WELDEDWING:
		{	
			tmpt=NULL;
			break;
		}
		case LOOSEDEUCE:
		{
			tmpt=nextfol(trg,true);								//JIM 19Sep97
			if (!tmpt)
			{
				//can't find a follower so try next flight
				if (trg->leader)
					trg = trg->Leader();
				tmpt=nextfl(trg,true);								  //RDH 12/05/99
				if (!tmpt)
				{
 					if (trg->fly.leadflight)
					{	
						if (trg->information)
 							tmpt=trg->fly.leadflight;
						else
						{
							SLong	oldrange = trg->Range;
						   trg->InterceptandRange(&trg->fly.leadflight->World);
						   if (trg->Range < RECOGNISERANGE)
								tmpt = trg->fly.leadflight;
					   		trg->Range = oldrange; 
						}
					}
				}

			}

			break;
		}
		default:
			tmpt=NULL;
			break;


	}
	return (tmpt);
}

//------------------------------------------------------------------------------
AirStrucPtr	ArtInt::SetFlightEngage(AirStrucPtr caller,AirStrucPtr trg,MANOEUVRE  manoeuvre,ANGLES desiredhdg, ANGLES desiredpitch, bool surprised)
{
	caller->information=FALSE;
	AirStrucPtr	tmpt=trg;

	if (caller->movecode<AUTO_COMBAT)
	{
		tmpt=SetFlightWhoCanEngage(caller,trg);
		//null means not found or not allowed
//DEADCODE RDH 12/05/99 		if (!tmpt)
//DEADCODE RDH 12/05/99 		{
//DEADCODE RDH 12/05/99 			if (caller->ai.flighttactics == LOOSEDEUCE)
//DEADCODE RDH 12/05/99 				 tmpt = trg;
//DEADCODE RDH 12/05/99 		}
//DEADCODE RDH 12/05/99 		if ((tmpt) && !(tmpt->information))
//DEADCODE RDH 12/05/99 			tmpt = trg;
		if (tmpt)	trg=tmpt;
		//assign a/c from tmpt to flight
		if (!caller->AircraftDamaged() && caller->classtype->aerobaticfactor!=AEROBATIC_LOW)								//JIM 29Aug96
			SetEngage(caller,tmpt, manoeuvre,desiredhdg, desiredpitch,  surprised);
		AirStrucPtr	currtrg=tmpt;
		AirStrucPtr	currfol=caller;
		while ((currfol=*currfol->Follower())!=NULL)
			currtrg=SetFollowerEngage(currfol,currtrg, manoeuvre,desiredhdg, desiredpitch,  surprised);
	}
	RETURN	(trg);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFollowerEngage
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
AirStrucPtr	ArtInt::SetFollowerEngage(AirStrucPtr caller,AirStrucPtr trg, MANOEUVRE  manoeuvre,ANGLES desiredhdg, ANGLES desiredpitch, bool surprised)
{
	caller->information=FALSE;
	AirStrucPtr	tmpt=trg;
	if (!caller->AircraftDamaged() && caller->classtype->aerobaticfactor!=AEROBATIC_LOW)								//JIM 29Aug96
	if (caller->movecode<AUTO_COMBAT)
	{
		if (		(manoeuvre == MANOEUVRE_LINEASTERN)
				||	(manoeuvre == MANOEUVRE_LINEABREAST)
		   )
		{//all followers go after the same as the lead in these manoeuvres
			tmpt = trg;
		}else
		{
			tmpt = SetFollowerWhoCanEngage(caller,trg);			
			//null means not found or not allowed
			if (!tmpt)
			{
				if (caller->ai.elementtactics == LOOSEDEUCE)
					 tmpt = trg;
			}
//DEADCODE RDH 12/05/99 			if ((tmpt) && !(tmpt->information))
//DEADCODE RDH 12/05/99 				tmpt = trg;
		}
		SetEngage(caller,tmpt, manoeuvre,desiredhdg, desiredpitch, surprised);
		if (tmpt)
			trg=tmpt;
	}
	return(trg);
}
bool ArtInt::CallerOnRight(AirStruc* ac,AirStruc* trg)
{
	ANGLES	relhdg;
	relhdg =  HdgIntFromTo(ac,trg) - ac->hdg;
	if 	(relhdg << ANGLES_180Deg)
		return (false);
	else
		return(true);
	
}
void	ArtInt::FindGroupAndLeader2(AirStruc*& caller, AirStruc*& caller2,tGroupLevel& group)
{
	group = GroupLevelNotInFormation(caller);						  //RDH 23/06/99
	caller2 = NULL;													  //RDH 02/06/99
	int count = 0;
	if  (group == GROUP_ELEMENT)
	{
		caller2 = caller;
		do
		{
			count++;
			caller2 = ((AirStruc *)caller2->Follower());
		}while (caller2);
		count = count/2;
		int  i = 0;
		caller2 = caller;
		while (i < count)
		{
			i++;
			caller2 = ((AirStruc *)caller2->Follower());
		}
		
	}
	else if (group == GROUP_FLIGHT)
		caller2 =  caller->fly.nextflight;
	else if (group == GROUP_SQUADRON)
	{
		//GROUP_SQUADRON means bigger than a flight
		//should never be more tha 3 flights, so split at end of first flight
		if (caller->fly.nextflight)
			caller2 =  caller->fly.nextflight->fly.nextflight;

//DEADCODE RDH 23/02/99 		int count = 1;
//DEADCODE RDH 23/02/99 		caller2 = caller->fly.nextflight;
//DEADCODE RDH 23/02/99 		while ((count < 6) && (caller2->fly.nextflight != NULL))
//DEADCODE RDH 23/02/99 		{
//DEADCODE RDH 23/02/99 			caller2 = caller2->fly.nextflight;
//DEADCODE RDH 23/02/99 			count++;
//DEADCODE RDH 23/02/99 		}
//DEADCODE RDH 23/02/99 		if (count < 6)
//DEADCODE RDH 23/02/99 			caller2 =  caller->fly.nextflight;

	}else
		caller2 = NULL;


}
void	ArtInt::SwitchCallerToLeft(AirStruc*& caller, AirStruc*& callee)
{
	if (callee)
	{
		//we want caller on the left for standard move
		//can invert later if we want them to cross
		if (CallerOnRight(caller,callee))
		{
			AirStruc* tmp = callee;
			callee = caller;
			caller = tmp;
		}
	}

}

void	ArtInt::SetRoundAboutAc(AirStruc*  ac)
{

//DEADCODE RDH 03/03/99 	AirStrucPtr	currldr, lastldr;
//DEADCODE RDH 03/03/99 	AirStrucPtr	squadldr = ac->fly.leadflight;
//DEADCODE RDH 03/03/99 
//DEADCODE RDH 03/03/99 	int	countelement = 0;
//DEADCODE RDH 03/03/99 	int thiselement = 0;
//DEADCODE RDH 03/03/99 		
//DEADCODE RDH 03/03/99 		if (squadldr != NULL)
//DEADCODE RDH 03/03/99 		{
//DEADCODE RDH 03/03/99 			currldr = squadldr;
//DEADCODE RDH 03/03/99 			while 	(		((currldr=currldr->fly.nextflight)!=NULL)
//DEADCODE RDH 03/03/99 							&&	(currldr->information)
//DEADCODE RDH 03/03/99 					)
//DEADCODE RDH 03/03/99 			{
//DEADCODE RDH 03/03/99 				if	(currldr->fly.position() == FLIGHTLEADER)		  //JIM 20/01/99
//DEADCODE RDH 03/03/99 					countelement++;
//DEADCODE RDH 03/03/99 				if  (		(currldr == ac)
//DEADCODE RDH 03/03/99 						||	(currldr == ac->fly.leadflight)
//DEADCODE RDH 03/03/99 					)
//DEADCODE RDH 03/03/99 					thiselement = countelement;
//DEADCODE RDH 03/03/99 			}
//DEADCODE RDH 03/03/99 		}
//DEADCODE RDH 03/03/99 	if (countelement <= 1)
//DEADCODE RDH 03/03/99 	{//not sufficient aircraft to do roundabout
//DEADCODE RDH 03/03/99 		ac->ai.threatlevel = BANDITANYWHERE;
//DEADCODE RDH 03/03/99 		ac->ai.manoeuvre=MANOEUVRE_SELECT;
//DEADCODE RDH 03/03/99 
//DEADCODE RDH 03/03/99 	}else
//DEADCODE RDH 03/03/99 	{
//DEADCODE RDH 03/03/99 		ac->ai.manoeuvre = MANOEUVRE_ROUNDABOUT;
//DEADCODE RDH 03/03/99 		if (countelement == thiselement)
//DEADCODE RDH 03/03/99 		{
//DEADCODE RDH 03/03/99 			ac->ai.threatlevel = BANDITFIRING;	
//DEADCODE RDH 03/03/99 		}else
//DEADCODE RDH 03/03/99 		{
//DEADCODE RDH 03/03/99 			ac->ai.threatlevel = BANDITINENGAGERANGEOFFRIENDLY;
//DEADCODE RDH 03/03/99 		}
//DEADCODE RDH 03/03/99 		ac->ai.desiredalt = ac->World.Y - FT_2000 + (countelement - thiselement) * FT_2000;
//DEADCODE RDH 03/03/99 	}
}
//DEADCODE RDH 08/03/99 void	ArtInt::SetDecoysInGroup(AirStruc*  ac)
//DEADCODE RDH 08/03/99 {
//DEADCODE RDH 08/03/99 	ac->information = FALSE;
//DEADCODE RDH 08/03/99 	AirStrucPtr	currfol=ac;
//DEADCODE RDH 08/03/99 	do
//DEADCODE RDH 08/03/99 	{
//DEADCODE RDH 08/03/99 			currfol->movecode = AUTO_FOLLOWWP;
//DEADCODE RDH 08/03/99 			currfol->ai.threatlevel = BANDITINWEAPONSRANGE;
//DEADCODE RDH 08/03/99 			if (currfol->ai.firsttactic == TACTIC_DECOYACTIVE)
//DEADCODE RDH 08/03/99 				currfol->NextWayPoint ();
//DEADCODE RDH 08/03/99 			currfol=currfol->fly.nextflight;
//DEADCODE RDH 08/03/99 	}
//DEADCODE RDH 08/03/99 	while 	(		(currfol!=NULL)
//DEADCODE RDH 08/03/99 				&&	(currfol->information)
//DEADCODE RDH 08/03/99 			);
//DEADCODE RDH 08/03/99 	
//DEADCODE RDH 08/03/99 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		nextfl
//Author		Jim Taylor
//Date			Wed 26 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStrucPtr	ArtInt::nextfl(AirStrucPtr trg,bool unassigned)
{
//DEADCODE RDH 12/05/99 	AirStrucPtr	t2=trg;
//DEADCODE RDH 12/05/99 	if (trg)
//DEADCODE RDH 12/05/99 		repeat
//DEADCODE RDH 12/05/99 		{
//DEADCODE RDH 12/05/99 			if (	(trg->fly.nextflight)	&&	(trg->fly.nextflight->information))
//DEADCODE RDH 12/05/99 				trg=trg->fly.nextflight;
//DEADCODE RDH 12/05/99 			else
//DEADCODE RDH 12/05/99 				if (	(trg->fly.leadflight)	&&	(trg->information))
//DEADCODE RDH 12/05/99 					trg=trg->fly.leadflight;
//DEADCODE RDH 12/05/99 				else
//DEADCODE RDH 12/05/99 					return(NULL);
//DEADCODE RDH 12/05/99 ////			if (!!trg->ai.attacker <=unassigned)
//DEADCODE RDH 12/05/99 			if (!trg->ai.attacker || unassigned)
//DEADCODE RDH 12/05/99 				return(trg);
//DEADCODE RDH 12/05/99 		}	while (t2!=trg);
//DEADCODE RDH 12/05/99 	return(NULL);

	SLong	oldrange = trg->Range;
 	AirStrucPtr	t2=NULL;
	
	if (trg->fly.nextflight)
	{
		if (trg->fly.nextflight->information)
			t2 = trg->fly.nextflight;
		else
		{
		   trg->InterceptandRange(&trg->fly.nextflight->World);
			   if (trg->Range < RECOGNISERANGE)
					t2 = trg->fly.nextflight;				
		}
	}


	trg->Range = oldrange; 
	return(t2);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		nextfol
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
bool	ArtInt::AircraftAreClose(AirStrucPtr trg, AirStrucPtr foll)
{

	
//DEADCODE RDH 23/06/99 	SLong	oldrange = trg->Range;
//DEADCODE RDH 23/06/99  	AirStrucPtr	t2=NULL;

//DEADCODE RDH 23/06/99    trg->InterceptandRange(&foll->World);
	SLong deltax = trg->World.X - foll->World.X;
	if (deltax < 0)
		deltax = -deltax;
	SLong deltaz = trg->World.Z - foll->World.Z;
	if (deltaz < 0)
		deltaz = -deltaz;

  if (		(deltax < RECOGNISERANGE)
		&&	(deltaz < RECOGNISERANGE)
	 )
	return(true);
  else
	return(false);


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		nextfol
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
AirStrucPtr	ArtInt::nextfol(AirStrucPtr trg,bool unassigned)
{
//DEADCODE RDH 12/05/99 	AirStrucPtr	t2=trg;
//DEADCODE RDH 12/05/99 	if (trg)
//DEADCODE RDH 12/05/99 		repeat
//DEADCODE RDH 12/05/99 		{
//DEADCODE RDH 12/05/99 			if (		(trg->Follower())	&&	(trg->Follower()->information))
//DEADCODE RDH 12/05/99 				trg=*trg->Follower();
//DEADCODE RDH 12/05/99 			else
//DEADCODE RDH 12/05/99 				if ((	trg->leader)	&&	(trg->information))
//DEADCODE RDH 12/05/99 					trg=*trg->leader;
//DEADCODE RDH 12/05/99 //				else
//DEADCODE RDH 12/05/99   //					return(NULL);
//DEADCODE RDH 12/05/99 ////			if (!!trg->ai.attacker <=unassigned)
//DEADCODE RDH 12/05/99 			if (!trg->ai.attacker || unassigned)
//DEADCODE RDH 12/05/99 				return(trg);
//DEADCODE RDH 12/05/99 		}	while (t2!=trg);
//DEADCODE RDH 12/05/99 	return(NULL);

	SLong	oldrange = trg->Range;
 	AirStrucPtr	t2=NULL;

	if (trg->Follower())
	{
		if	(trg->Follower()->information)	
			t2 = trg->Follower();
		else
		{
		   trg->InterceptandRange(&trg->Follower()->World);
		   if (trg->Range < RECOGNISERANGE)
				t2 = trg->Follower();				
		}
	}

 	trg->Range = oldrange; 
	return(t2);

}
ANGLES ArtInt::HdgIntFromTo(AirStruc* ac,AirStruc* trg)
{
	ANGLES	oldhdgint, oldpitchint;
	SLong	oldrange;
	ANGLES	hdgint;
	oldhdgint = ac->HdgIntercept;
	oldpitchint = ac->PitchIntercept;
	oldrange  = ac->Range;

	InterceptRangeFromTo(ac, trg);
	hdgint = ac->HdgIntercept;

	ac->PitchIntercept = oldpitchint;
	ac->HdgIntercept = oldhdgint;
	ac->Range = oldrange;
	return(hdgint);

}
bool ArtInt::TrgIsVulnerable(AirStruc* caller, AirStruc* trg)
{
	int trgnum = GuessFormationSize(caller, trg);
	int callernum = CountFormationSize(caller);
	if ((trgnum <= 4) && (callernum >=4))
		return (true);
	else
		return (false);


}
AirStruc* ArtInt::FreeUpAFlight(AirStruc* caller, AirStruc*  currtrg)
{//if there isn't a free flight then redirect lowest 
	//which is attacking a/c in same flight that leader is attacking
	//but don't redirect if currtrgldr is same as foller leader

	AirStruc* leader;
	leader = caller->FindGroupLeaderInFormation();
	currtrg = currtrg->FindGroupLeader();
	AirStruc* callee =  leader;
	int count = 0;
	while (callee->fly.nextflight != NULL)
	  {//find last element
		callee = callee->fly.nextflight;		
		count++;
	  }
	if ((count % 2) == 1)
		count--;			//find last flight

	ItemBase* ldrtrg = 	(AirStrucPtr(*leader)->ai.unfriendly);
	if (		(!ldrtrg)
			||	(ldrtrg->Status.size!=AIRSTRUCSIZE)
//DEADCODE RDH 06/06/99 			||	(AirStrucPtr(*ldrtrg)->ai.unfriendly->Status.size!=AIRSTRUCSIZE)
	   )
	{
		callee = leader;
	}else
	{
		ldrtrg = AirStrucPtr(*ldrtrg)->FindGroupLeader();	
		AirStruc* folltrg; 
									 
		do
		{
			int i = 0;
			callee= leader;
			while (i < count)
			{
				callee = callee->fly.nextflight;
				i++;
			}
			count = count - 2;
			folltrg = (AirStruc*)((AirStruc*)callee->ai.unfriendly);
			if (folltrg->Status.size == AIRSTRUCSIZE)
				folltrg = folltrg->FindGroupLeader();				  //RDH 06/06/99
		}while (	(count >= 0)	&&	(folltrg != ldrtrg)&&	(currtrg != folltrg));
		if (leader == callee)
			callee = NULL;
	}	
	return(callee); 
}


AirStruc* ArtInt::FindFreeFlight(AirStruc* caller)
{
	AirStruc* leader = caller->FindGroupLeaderInFormation();
	AirStruc* callee =  leader;
	int count = 0;
	while (callee->fly.nextflight != NULL)
	  {//find last element
		callee = callee->fly.nextflight;		
		count++;
	  }
	if ((count % 2) == 1)
		count--;			//find last flight
	int flight = count;
	int i;
	do
	{
		i = 0;
		callee =  leader;
		while (i < count)
		{
			callee = callee->fly.nextflight;
			i++;
		}
		count = count - 2;
	}
	while (	(count >= 0)	&&	(callee->ai.unfriendly !=NULL));

  	if (callee->ai.unfriendly != NULL)
		callee = NULL;
	if (leader == callee)
		callee = NULL;
	return(callee);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakCall
//Author		R. Hyde 
//Date			Thu 4 Mar 1999
//
//Description	Worst call first, try to assess skill and morale and then choose
// 				returns the desired script
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ScriptTables ArtInt::BreakCall(AirStruc* caller, bool onright)
{

ScriptTables leftset[] = {
							SCRIPT_BRKLEFT_BRKPANIC,
							SCRIPT_BRKLEFT_BRKBAD,
							SCRIPT_BRKLEFT_BRK,
							SCRIPT_CALLEE_BRKBAD,
							SCRIPT_CALLEE_RAND_ALERT,
							SCRIPT_RAND_ALERT_L,
							SCRIPT_CALLEE_BRKLEFT_BRKPANIC,
							SCRIPT_CALLEE_BRKLEFT_BRKBAD,
							SCRIPT_CALLEE_BRKLEFT_BRK,
							SCRIPT_CALLEE_BRKLEFT
						};	
ScriptTables rightset[] = {
							SCRIPT_BRKRIGHT_BRKPANIC,
							SCRIPT_BRKRIGHT_BRKBAD,
							SCRIPT_BRKRIGHT_BRK,
							SCRIPT_CALLEE_BRKBAD,
							SCRIPT_CALLEE_RAND_ALERT,
							SCRIPT_RAND_ALERT_L,
							SCRIPT_CALLE_BRKRIGHT_BRKPANIC,
							SCRIPT_CALLE_BRKRIGHT_BRKBAD,
							SCRIPT_CALLEE_BRKRIGHT_BRK,
							SCRIPT_CALLEE_BRKRIGHT
						};

	ScriptTables	script;
	int max = 3+(caller->ai.combatskill/2);	//equivalent too!		 * 10)/SKILL_MAX
	int range = Math_Lib.rnd(3);
	int index = max - range;
	if (index > 9)
		index = 9;
	if (index < 0)
		index = 0;
	if (onright)
		script = rightset[index];
	else
		script = leftset[index];

	if  (caller->classtype->phrasename != PHRASE_MIGS)
	{//there is a MiG option we can use
	if (index == 4) 
		script = SCRIPT_CALLEE_RAND_ALERT_MIGS;	
	if (index == 5)
		script = SCRIPT_RAND_ALERT_L_MIGS;		
	}
	return script;

}

//////////////////////////////////////////////////////////////////////
//
// Function:    Rendezvous
// Date:		04/04/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
TABLEAI(Rendezvous,AirStrucPtr)
{	{PHRASE_PARTS_S}
};

INSTANCEAI(Rendezvous,AirStrucPtr)
{
	return false;
}

/*
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedUnknown
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	Do we want a closer look?
//			   	Only if threatlevel >=BANDITANYWHERE
//				and aggressionlevel >=AL_DEFENSIVE
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::SpottedUnknown(AirStruc* caller,AirStruc* trg)
{
//rdh 19/1/99	if (caller->ai.unfriendly==NULL)
//rdh 19/1/99	{
//rdh 19/1/99//DEADCODE JIM 21/12/98 			caller->ai.unfriendly=trg;
//rdh 19/1/99
//rdh 19/1/99//##temp rdh			if  (	(caller->ai.threatlevel >=BANDITANYWHERE)
//rdh 19/1/99//				&&	caller->movecode < AUTO_TRACKINGBOGIE
//rdh 19/1/99//				&&	caller->ai.aggressionlevel >= AL_DEFENSIVE
//rdh 19/1/99//				)
//rdh 19/1/99//DEADCODE JIM 21/12/98 				caller->movecode = AUTO_TRACKINGBOGIE;
//rdh 19/1/99
//rdh 19/1/99}

	if (caller->IsUsingPilotedAcLog())
	{
		if (!trg->IsUsingPilotedAcLog())
		{
//TempCode RDH 27Mar98 			Persons_2.AddMESSAGE_STRUC(UserMsg::SIGHTED,TEXT_UNKNOWNSIGHTED,caller);
			caller->PlayerSequenceAudible(FIL_MUSIC_SPOTTED_UNKNOWN);
			Persons2::UpdateLog(trg->ai.eventlog,0,EventLog::SEENBYPLAYERS);
		}
	}
	elseif (!trg->IsUsingPilotedAcLog())
	{
		Persons2::UpdateLog(trg->ai.eventlog,0,EventLog::SEENBYOTHERS);
	}
	if (caller->ai.unfriendly==NULL)
	{
//DEADCODE JIM 21/12/98 			caller->ai.unfriendly=trg;

//##temp rdh			if  (	(caller->ai.threatlevel >=BANDITANYWHERE)
//				&&	caller->movecode < AUTO_TRACKINGBOGIE
//				&&	caller->ai.aggressionlevel >= AL_DEFENSIVE
//				)
//DEADCODE JIM 21/12/98 				caller->movecode = AUTO_TRACKINGBOGIE;

	}
	return(true);


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedContrails
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::SpottedContrails(AirStruc* caller,AirStruc* trg)
{
//like spotted unknown
//given higher priority?
//do we know who has set contrails, if we could track it easily if required
}	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedOldContrails
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::SpottedOldContrails(AirStruc* caller,AirStruc* trg)
{
//like spotted unknown
//given lower priority?
//do we know who has set contrails, if we could track it easily if required
}	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoesFriendNeedHelp
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	Assess whether friendly needs helping out
//				caller and trg are same nationality
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::DoesFriendNeedHelp(AirStruc* caller,AirStruc* trg)
{
	SLong	RangeEyeTrg = caller->Range;
	
	if (	trg->ai.attacker
		&&	trg->ai.attacker->Status.size==AIRSTRUCSIZE
		&&	!((AirStruc*)*trg->ai.attacker)->ai.attacker
		)
	{//trg has attacker that is an aircraft that is not under attack
		caller->InterceptandRange(&trg->ai.attacker->World);

		if (	(	(!caller->ai.unfriendly)
				||	(	((AirStruc*)caller->ai.unfriendly)->nationality == caller->nationality)
				||	((RangeEyeTrg - caller->Range) > MILES01)
				)
				&& (caller->ai.morale > MORALE_MEDIUM)
			)
		{//caller doesn't have unf or unf is really on caller's side or this attacker closer
		 //and morale high 
			return(SpottedUnfriendly(caller,*trg->ai.attacker));
		}else
			return(false);
//TempCode RDH 27Mar98 		if (trg->ai.eventlog->stage!=EventLog::TAKEOFF) //player flight
//TempCode RDH 27Mar98 			//##message to differentiate between bomber,fb and fight//##er
//TempCode RDH 27Mar98 			Persons_2.AddMessageIfPlayerSq(caller,UserMsg::SIGHTED,TEXT_DOGFIGHTSIGHTED,trg);
		
	}else
	{
		return(false);
		if (trg->Range>RECOGNISERANGE-METRES500)
			if (caller->ai.eventlog->stage==EventLog::TAKEOFF)	//player flight
			if (trg->ai.eventlog->stage!=EventLog::TAKEOFF)	//non-player flight
			{
 				Persons_2.UpdateLog(trg->ai.eventlog,0,EventLog::SEENBYPLAYERS);
				caller->PlayerSequenceAudible(FIL_MUSIC_FRIENDLY_SEEN);
			}
	}

	caller->Range = RangeEyeTrg;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedNewUnfriendly
//Author		Jim Taylor
//Date			Tue 22 Oct 1996
//
//Description	
//				if caller is leader
//					if trg has no attacker
//						if range < DANGER THEN attack
//						if range < ENGAGE
//							if caller has no unfriendly or is a friendly THEN attack
//							if range to caller->unf > ENGAGERANGE THEN attack
//
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::SpottedNewUnfriendly(AirStruc* caller,AirStruc* trg)
{
	if (caller->leader==NULL)
		if (trg->ai.attacker==NULL)
		{
			int	newrange=trg->Range;
			if (newrange<ENGAGERANGE)
				return(SpottedUnfriendly(caller,trg));
			if (newrange<COMBATRANGE)
			{
				if (	(caller->ai.unfriendly==NULL)
//##					||	(caller->ai.unfriendly->nationality == caller->nationality)
					)
					return(SpottedUnfriendly(caller,trg));
				caller->InterceptandRange(caller->ai.unfriendly);
				if (caller->Range>COMBATRANGE)
					return(SpottedUnfriendly(caller,trg));
			}
		}
	return(false);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptandRange
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description		
//
//Inputs		
//
//Returns	"Global" Range, HdgIntercept and PitchIntercept
//
//------------------------------------------------------------------------------
void ArtInt::InterceptRangeFromTo(AirStruc* from, AirStruc* to)

{


	SLong deltax = to->World.X - from->World.X;
	SLong deltay = to->World.Y - from->World.Y;
	SLong deltaz = to->World.Z - from->World.Z;
	Math_Lib.Intercept (deltax,deltay,deltaz,from->Range,from->HdgIntercept,from->PitchIntercept);
	
	
	

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AcHasBombs
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::AcHasBombs(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceHasBombers(trg)
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::ForceHasBombers(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BingoFuel
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::BingoFuel(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Winchester
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::Winchester(AirStruc* trg)
{
	return(true);
}
//DeadCode AMM 14Jul99 /*
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		SpottedUnFriendly
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Fri 27 Feb 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 bool	ArtInt::SpottedUnfriendly(AirStruc* caller,AirStruc* trg)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 //temp
//DeadCode AMM 14Jul99 	caller->ai.threatlevel = BANDITANYWHERE;
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 	if (caller->classtype->aerobaticfactor == AEROBATIC_LOW)
//DeadCode AMM 14Jul99 	{//medium bomber
//DeadCode AMM 14Jul99 		return(AlertFighters(caller,trg));
//DeadCode AMM 14Jul99 	}else if (	(caller->ai.threatlevel > BANDITFIRING)
//DeadCode AMM 14Jul99 		||	((caller->Range < WEAPONSRANGE) &&	(caller->ai.threatlevel >= BANDITINWEAPONSRANGE))
//DeadCode AMM 14Jul99 		||	((caller->Range < DANGERRANGE) &&	(caller->ai.threatlevel >= BANDITINDANGERRANGE))
//DeadCode AMM 14Jul99 		||	((caller->Range < ENGAGERANGE) &&	(caller->ai.threatlevel >= BANDITINENGAGERANGE))
//DeadCode AMM 14Jul99 		||	((caller->Range < COMBATRANGE) &&	(caller->ai.threatlevel >= BANDITINCOMBATRANGE))
//DeadCode AMM 14Jul99 		||	(caller->ai.threatlevel >= BANDITANYWHERE)
//DeadCode AMM 14Jul99 		||	(		(caller->ai.threatlevel == BANDITINENGAGERANGEOFFRIENDLY)
//DeadCode AMM 14Jul99 				&& 	(trg->ai.unfriendly)
//DeadCode AMM 14Jul99 //##				&& 	(RangeFromTo(trg, trg->ai.unfriendly) < ENGAGERANGE)
//DeadCode AMM 14Jul99 			)
//DeadCode AMM 14Jul99 	   )
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 		if 	(!DecoysInGroup(caller))
//DeadCode AMM 14Jul99 		{
//DeadCode AMM 14Jul99 			if	(	(caller->Range > DANGERRANGE)
//DeadCode AMM 14Jul99 					&&
//DeadCode AMM 14Jul99 					(	(caller->ai.aggressionlevel == AL_TRAINING)
//DeadCode AMM 14Jul99 					||	(	(caller->ai.aggressionlevel == AL_DEFENSIVE) 
//DeadCode AMM 14Jul99 							&&
//DeadCode AMM 14Jul99 							(		((trg->nationality == NAT_RED) && (!AcHasBombs(trg)))
//DeadCode AMM 14Jul99 								||	((trg->nationality == NAT_BLUE) && ((caller->World.Y - trg->World.Y) > FT_3000)))
//DeadCode AMM 14Jul99 							)
//DeadCode AMM 14Jul99 					||	((caller->ai.aggressionlevel == AL_ATTACKBOMBERSONLY) && (trg->classtype->aerobaticfactor >= AEROBATIC_FIGHTER))
//DeadCode AMM 14Jul99 					||	((caller->ai.aggressionlevel == AL_SPLITFORCE) && (!ForceHasBombers(trg)))
//DeadCode AMM 14Jul99 					||	((caller->ai.aggressionlevel == AL_ATTACKWEAKNESSES) &&	(	!BingoFuel(trg)
//DeadCode AMM 14Jul99 																				&&	!trg->AircraftDamaged()
//DeadCode AMM 14Jul99 																				&&	!Winchester(trg)
//DeadCode AMM 14Jul99 																				)
//DeadCode AMM 14Jul99 						)															
//DeadCode AMM 14Jul99 					)
//DeadCode AMM 14Jul99 				)
//DeadCode AMM 14Jul99 			{//may have to evade first
//DeadCode AMM 14Jul99 				//##ChooseBanditRelToPilotMsg()
//DeadCode AMM 14Jul99 				caller->movecode = AUTO_FOLLOWWP;
//DeadCode AMM 14Jul99 				return(false);
//DeadCode AMM 14Jul99 			}else
//DeadCode AMM 14Jul99 			{//should move to precombat or combat
//DeadCode AMM 14Jul99 			
//DeadCode AMM 14Jul99 				//find the leader to go for
//DeadCode AMM 14Jul99 				//Always go for leader of current flight
//DeadCode AMM 14Jul99 				if (trg->information && trg->leader)
//DeadCode AMM 14Jul99 					trg=*trg->leader;
//DeadCode AMM 14Jul99 				GroupEngage(caller,trg);
//DeadCode AMM 14Jul99 				return(true);
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 			}
//DeadCode AMM 14Jul99 		}
//DeadCode AMM 14Jul99 	}
//DeadCode AMM 14Jul99 	return(false);
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 	
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		GroupLevel
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Mon 16 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 ArtInt::tGroupLevel ArtInt::GroupLevel(AirStruc* caller)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 	if 	(		(caller->fly.nextflight)
//DeadCode AMM 14Jul99 	   		&&  (caller->fly.nextflight->information)
//DeadCode AMM 14Jul99 		)
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 		if 	(		(caller->fly.nextflight->fly.nextflight)
//DeadCode AMM 14Jul99 		   		&&  (caller->fly.nextflight->fly.nextflight->information)
//DeadCode AMM 14Jul99 			)
//DeadCode AMM 14Jul99 			return(GROUP_SQUADRON);
//DeadCode AMM 14Jul99 		else
//DeadCode AMM 14Jul99 			return(GROUP_FLIGHT);
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 	}else
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 		if  (	(caller->Follower())
//DeadCode AMM 14Jul99 	   		&&  (caller->Follower()->information)
//DeadCode AMM 14Jul99 			)
//DeadCode AMM 14Jul99 			return(GROUP_ELEMENT);
//DeadCode AMM 14Jul99 		else
//DeadCode AMM 14Jul99 			return(GROUP_LONER);
//DeadCode AMM 14Jul99 	}
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		DefensiveSplit
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Tue 17 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 void	ArtInt::DefensiveSplit(AirStruc* caller,AirStruc* caller2,AirStruc* trg,ANGLES leftpitch,ANGLES rightpitch)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 	SetEngage(caller,trg,MANOEUVRE_SPLITMANOEUVRE, ANGLES_270Deg,leftpitch,true);
//DeadCode AMM 14Jul99 	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_SPLITMANOEUVRE, ANGLES_270Deg,leftpitch,true);
//DeadCode AMM 14Jul99 	SetEngage(caller2,trg,MANOEUVRE_SPLITMANOEUVRE, ANGLES_270Deg,leftpitch,true);
//DeadCode AMM 14Jul99 	SetUpRemainderOfGroupToEngage(caller2,trg,MANOEUVRE_SPLITMANOEUVRE, ANGLES_90Deg, rightpitch,true);
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		SetUpBracket
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Tue 17 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 void	ArtInt::SetUpPincer(AirStruc* caller,AirStruc* caller2,AirStruc* trg)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 	SetEngage(caller,trg,MANOEUVRE_PINCER, ANGLES_270Deg,ANGLES_90Deg,FALSE);
//DeadCode AMM 14Jul99 	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_PINCER, ANGLES_90Deg, ANGLES_0Deg,FALSE);
//DeadCode AMM 14Jul99 	SetEngage(caller2,trg,MANOEUVRE_PINCER, ANGLES_270Deg,ANGLES_270Deg,FALSE);
//DeadCode AMM 14Jul99 	SetUpRemainderOfGroupToEngage(caller2,trg,MANOEUVRE_PINCER, ANGLES_270Deg, ANGLES_0Deg,FALSE);
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		SetUpMultiWave
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Wed 18 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 void	ArtInt::SetUpMultiWave(AirStruc* caller,AirStruc* caller2,AirStruc* trg)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 	SetEngage(caller,trg,MANOEUVRE_HEADON, ANGLES_0Deg, ANGLES_0Deg,FALSE);
//DeadCode AMM 14Jul99 	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_HEADON, ANGLES_0Deg, ANGLES_0Deg,FALSE);
//DeadCode AMM 14Jul99 	SetEngage(caller2,trg,MANOEUVRE_HEADON, ANGLES_0Deg, ANGLES_0Deg,FALSE);
//DeadCode AMM 14Jul99 	SetUpRemainderOfGroupToEngage(caller2,trg,MANOEUVRE_MULTIWAVE, ANGLES_0Deg, ANGLES_0Deg,FALSE);
//DeadCode AMM 14Jul99 }	
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		DefensiveSplitHiHi
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Tue 17 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 void	ArtInt::DefensiveSplitHiLo(AirStruc* caller,AirStruc* caller2,AirStruc* trg)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 	ANGLES	rightpitch, leftpitch;
//DeadCode AMM 14Jul99 	if ((Math_Lib.rnd(RndValMAX)) > RND50PC)	
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 		leftpitch == ANGLES_0Deg;
//DeadCode AMM 14Jul99 		rightpitch = BESTCLIMBPITCH;
//DeadCode AMM 14Jul99 	}else
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 		leftpitch = BESTCLIMBPITCH;
//DeadCode AMM 14Jul99 		rightpitch = ANGLES_0Deg;
//DeadCode AMM 14Jul99 	}
//DeadCode AMM 14Jul99 	DefensiveSplit(caller,caller2,trg, leftpitch, rightpitch);
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		ChooseSplitManoeuvre
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Tue 17 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 void	ArtInt::ChooseSplitManoeuvre(AirStruc* caller,AirStruc* caller2,AirStruc* trg)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 //we want caller on the left for standard move
//DeadCode AMM 14Jul99 //can invert later if we want them to cross
//DeadCode AMM 14Jul99 	if (RelHdgIntFromTo(caller,caller2))
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 		AirStruc* tmp = caller;
//DeadCode AMM 14Jul99 		caller = caller2;
//DeadCode AMM 14Jul99 		caller2 = tmp;
//DeadCode AMM 14Jul99 	}
//DeadCode AMM 14Jul99 	RndVal	rndnum = ((RndVal)Math_Lib.rnd(2));
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 	if  (		TargetOnCallerTail(caller, trg, ANGLES_45Deg)
//DeadCode AMM 14Jul99 			&&	TargetFacingCaller(caller, trg, ANGLES_45Deg)
//DeadCode AMM 14Jul99 		)
//DeadCode AMM 14Jul99 	{//attacked from rear
//DeadCode AMM 14Jul99 		if (caller->classtype->visible != MIG15)
//DeadCode AMM 14Jul99 		{
//DeadCode AMM 14Jul99 			if (caller->ai.morale < MORALE_MEDIUM)
//DeadCode AMM 14Jul99 			{
//DeadCode AMM 14Jul99 				if (RndVal)
//DeadCode AMM 14Jul99 					DefensiveSplit(caller,caller2,trg, ANGLES_0Deg,ANGLES_0Deg);
//DeadCode AMM 14Jul99 				else
//DeadCode AMM 14Jul99 					DefensiveSplitHiLo(caller2,caller,trg);
//DeadCode AMM 14Jul99 			}
//DeadCode AMM 14Jul99 			else if (caller->ai.combatskill > SKILL_REGULAR)
//DeadCode AMM 14Jul99 				DefensiveSplit(caller,caller2,trg, BESTCLIMBPITCH, BESTCLIMBPITCH);
//DeadCode AMM 14Jul99 			else
//DeadCode AMM 14Jul99 				DefensiveSplitHiLo(caller,caller2,trg);
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 		}else
//DeadCode AMM 14Jul99 		{
//DeadCode AMM 14Jul99 			if (caller->ai.morale < MORALE_MEDIUM)
//DeadCode AMM 14Jul99 				if (RndVal)
//DeadCode AMM 14Jul99 					DefensiveSplit(caller,caller2,trg, BESTCLIMBPITCH, BESTCLIMBPITCH);
//DeadCode AMM 14Jul99 				else
//DeadCode AMM 14Jul99 					DefensiveSplitHiLo(caller2,caller,trg);
//DeadCode AMM 14Jul99 			else if (caller->ai.combatskill >  SKILL_REGULAR)
//DeadCode AMM 14Jul99 				DefensiveSplit(caller,caller2,trg, ANGLES_0Deg,ANGLES_0Deg);
//DeadCode AMM 14Jul99 			else
//DeadCode AMM 14Jul99 				DefensiveSplitHiLo(caller,caller2,trg);
//DeadCode AMM 14Jul99 		}
//DeadCode AMM 14Jul99 	}else if  (		CallerFacingTarget(caller, trg, ANGLES_45Deg)
//DeadCode AMM 14Jul99 				&&	TargetFacingCaller(caller, trg, ANGLES_45Deg)
//DeadCode AMM 14Jul99 				)
//DeadCode AMM 14Jul99 	{//head on
//DeadCode AMM 14Jul99 		if (caller->ai.firsttactic == TACTIC_PINCER)
//DeadCode AMM 14Jul99 			SetUpPincer(caller,caller2,trg);
//DeadCode AMM 14Jul99 		else if (caller->ai.firsttactic == TACTIC_MULTIWAVE)
//DeadCode AMM 14Jul99 			SetUpMultiWave(caller,caller2,trg);
//DeadCode AMM 14Jul99 		else
//DeadCode AMM 14Jul99 		{
//DeadCode AMM 14Jul99 			SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
//DeadCode AMM 14Jul99 			SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg,FALSE);		
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 		}
//DeadCode AMM 14Jul99 	}else
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 		if (caller->ai.firsttactic == TACTIC_MULTIWAVE)
//DeadCode AMM 14Jul99 			SetUpMultiWave(caller,caller2,trg);
//DeadCode AMM 14Jul99 		else
//DeadCode AMM 14Jul99 		{
//DeadCode AMM 14Jul99 			SetEngage(caller,trg,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, true);
//DeadCode AMM 14Jul99 			SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg,FALSE);		
//DeadCode AMM 14Jul99 		}
//DeadCode AMM 14Jul99 	}
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 }	
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		Engage
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Mon 16 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 void	ArtInt::GroupEngage(AirStruc* caller,AirStruc* trg)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 //try to include: 	High morale, low ability
//DeadCode AMM 14Jul99 //					hothead: break form and attack alone
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 	//find the leader to go for
//DeadCode AMM 14Jul99 	//Always go for leader of target's flight
//DeadCode AMM 14Jul99 	if (trg->information && trg->leader)
//DeadCode AMM 14Jul99 		trg=*trg->leader;
//DeadCode AMM 14Jul99 	//go for their squad leader
//DeadCode AMM 14Jul99 	if (trg->fly.leadflight && trg->information)
//DeadCode AMM 14Jul99 		trg=trg->fly.leadflight;
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 	//caller is either a leader or loner
//DeadCode AMM 14Jul99 	tGroupLevel group = GroupLevel(caller);
//DeadCode AMM 14Jul99 	if (MakeForceToRespond (caller,trg,group))
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 	
//DeadCode AMM 14Jul99 			
//DeadCode AMM 14Jul99 		if  ((group == GROUP_ELEMENT)	&&	(caller->ai.elementtactics == LOOSEDEUCE))
//DeadCode AMM 14Jul99 			ChooseSplitManoeuvre(caller,((AirStruc *)caller->Follower()),trg);
//DeadCode AMM 14Jul99 		else if ((group == GROUP_FLIGHT)	&&	(caller->ai.flighttactics == LOOSEDEUCE))
//DeadCode AMM 14Jul99 			ChooseSplitManoeuvre(caller,caller->fly.nextflight,trg);
//DeadCode AMM 14Jul99 		else if ((group == GROUP_SQUADRON)	&&	(caller->ai.squadrontactics == LOOSEDEUCE))
//DeadCode AMM 14Jul99 			ChooseSplitManoeuvre(caller,caller->fly.nextflight->fly.nextflight,trg);
//DeadCode AMM 14Jul99 		else
//DeadCode AMM 14Jul99 		{
//DeadCode AMM 14Jul99 			//attack him!
//DeadCode AMM 14Jul99 			SetEngage(caller,trg, MANOEUVRE_SELECT, ANGLES_0Deg,ANGLES_0Deg, FALSE);
//DeadCode AMM 14Jul99 			SetUpRemainderOfGroupToEngage(caller,trg, MANOEUVRE_SELECT, ANGLES_0Deg,ANGLES_0Deg, FALSE);
//DeadCode AMM 14Jul99 		}
//DeadCode AMM 14Jul99 	}
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		SubsequentIDasUnfriendly
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Tue 3 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 //void	ArtInt::SubsequentIDasUnfriendly(AirStruc* caller,AirStruc* trg)
//DeadCode AMM 14Jul99 //{
//DeadCode AMM 14Jul99 //}
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		AlertFighters
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Tue 3 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 /*bool	ArtInt::AlertFighters(AirStruc* caller,AirStruc* trg)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 	return(false);
//DeadCode AMM 14Jul99 //TempCode RDH 27Mar98 	Blue ac will call out sightings
//DeadCode AMM 14Jul99 //TempCode RDH 27Mar98 	Blue Fighter have to decide whether to respond
//DeadCode AMM 14Jul99 //TempCode RDH 27Mar98 	if (respond())
//DeadCode AMM 14Jul99 //TempCode RDH 27Mar98 		TrackBogey();
//DeadCode AMM 14Jul99 //TempCode RDH 27Mar98 
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		InCombatWithoutUnfriendly
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Fri 27 Feb 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	What does wingman do when he spots enemy ac with leader in combat
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 void	ArtInt::InCombatWithoutUnfriendly(AirStruc* caller,AirStruc*  trg)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 	switch(caller->ai.elementtactics)
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 		case	WELDEDWING:
//DeadCode AMM 14Jul99 		case	TOPCOVER:
//DeadCode AMM 14Jul99 		{
//DeadCode AMM 14Jul99 			if	(	(	(trg == ((AirStruc*)caller->leader)->ai.attacker)
//DeadCode AMM 14Jul99 					||	(trg == caller->ai.attacker)
//DeadCode AMM 14Jul99 					)
//DeadCode AMM 14Jul99 //				&&	trgtonsix
//DeadCode AMM 14Jul99 				&&	(caller->Range < DANGERRANGE)
//DeadCode AMM 14Jul99 				)
//DeadCode AMM 14Jul99 				{
//DeadCode AMM 14Jul99 					caller->ai.unfriendly = trg;
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 					_DPlay.OwnerChangeDecision(caller,trg);		//AMM 27Nov98
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 				}
//DeadCode AMM 14Jul99 			break;
//DeadCode AMM 14Jul99 		}	
//DeadCode AMM 14Jul99 	}
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode AMM 14Jul99 //Procedure		ResetUnfriendly()
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			Tue 17 Mar 1998
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 void ArtInt::ResetUnfriendly()
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 	//look through the leader unfriendlies group and fix on best target
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 //Procedure		
//DeadCode AMM 14Jul99 //Author		R. Hyde 
//DeadCode AMM 14Jul99 //Date			21 Jan 1999
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Description	
//DeadCode AMM 14Jul99 //			   	
//DeadCode AMM 14Jul99 //				
//DeadCode AMM 14Jul99 //Inputs		
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //Returns	
//DeadCode AMM 14Jul99 //
//DeadCode AMM 14Jul99 //------------------------------------------------------------------------------
//DeadCode AMM 14Jul99 //at top
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 TABLEAI(DefensiveManoeuvre, AirStrucPtr)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 	{PHRASE_DEFENSIVESPLITSHORT,			&SetUpDefensiveSplit,	PHRASE_DEFENSIVESPLIT},		
//DeadCode AMM 14Jul99 	{PHRASE_DEFENSIVESPLITLEFTHISHORT,	&SetUpDefensiveSplitLeftHi,	PHRASE_DEFENSIVESPLITLEFTHI},
//DeadCode AMM 14Jul99 	{PHRASE_DEFENSIVESPLITRIGHTHISHORT,	&SetUpDefensiveSplitRightHi, PHRASE_DEFENSIVESPLITRIGHTHI},
//DeadCode AMM 14Jul99 	{PHRASE_DEFENSIVESPLITBOTHHISHORT,	&SetUpDefensiveSplitBothHi, PHRASE_DEFENSIVESPLITBOTHHI},
//DeadCode AMM 14Jul99 	{PHRASE_SELECTTARGETS,				&SelectTarget,	PHRASE_SELECTYOUROWNTARGETS},
//DeadCode AMM 14Jul99 	{PHRASE_CONTINUE,					&DoNothing,		PHRASE_IGNOREFORNOW}
//DeadCode AMM 14Jul99 	{PHRASE_PARTS_S},
//DeadCode AMM 14Jul99 	{PHRASE_PARTS_S}
//DeadCode AMM 14Jul99 };
//DeadCode AMM 14Jul99 INSTANCEAI(DefensiveManoeuvre, AirStrucPtr)
//DeadCode AMM 14Jul99 {
//DeadCode AMM 14Jul99 /*	tGroupLevel group = GroupLevel(caller);
//DeadCode AMM 14Jul99 	
//DeadCode AMM 14Jul99 	if (		(EngageAppropriate())
//DeadCode AMM 14Jul99 			&&	(MakeForceToRespond (caller,trg,group))
//DeadCode AMM 14Jul99 		)		
//DeadCode AMM 14Jul99 	{
//DeadCode AMM 14Jul99 		if  (		((group == GROUP_ELEMENT)	&&	(caller->ai.elementtactics == LOOSEDEUCE))
//DeadCode AMM 14Jul99 				||	((group == GROUP_FLIGHT)	&&	(caller->ai.flighttactics == LOOSEDEUCE))
//DeadCode AMM 14Jul99 				||	((group == GROUP_SQUADRON)	&&	(caller->ai.squadrontactics == LOOSEDEUCE))
//DeadCode AMM 14Jul99 			)
//DeadCode AMM 14Jul99 			{//split appropriate
//DeadCode AMM 14Jul99 				if (caller->classtype->visible != MIG15)
//DeadCode AMM 14Jul99 				{
//DeadCode AMM 14Jul99 					if (caller->ai.morale < MORALE_MEDIUM)
//DeadCode AMM 14Jul99 					{
//DeadCode AMM 14Jul99 						if (RndVal)
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLIT,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplit);
//DeadCode AMM 14Jul99 call for sender to do his part of his split
//DeadCode AMM 14Jul99 						else
//DeadCode AMM 14Jul99 							if ((Math_Lib.rnd(RndValMAX)) > RND50PC)	
//DeadCode AMM 14Jul99 								retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITLEFTHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitLeftHi);
//DeadCode AMM 14Jul99 							else
//DeadCode AMM 14Jul99 								retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITRIGHTHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitRightHi);
//DeadCode AMM 14Jul99 						
//DeadCode AMM 14Jul99 					}
//DeadCode AMM 14Jul99 					else if (caller->ai.combatskill > SKILL_REGULAR)
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITBOTHHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitBothHi);
//DeadCode AMM 14Jul99 					else
//DeadCode AMM 14Jul99 						if ((Math_Lib.rnd(RndValMAX)) > RND50PC)	
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITLEFTHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitLeftHi);
//DeadCode AMM 14Jul99 						else
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITRIGHTHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitRightHi);
//DeadCode AMM 14Jul99 		
//DeadCode AMM 14Jul99 				}else
//DeadCode AMM 14Jul99 				{
//DeadCode AMM 14Jul99 					if (caller->ai.morale < MORALE_MEDIUM)
//DeadCode AMM 14Jul99 					{
//DeadCode AMM 14Jul99 						if (RndVal)
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITBOTHHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitBothHi);
//DeadCode AMM 14Jul99 						else
//DeadCode AMM 14Jul99 						if ((Math_Lib.rnd(RndValMAX)) > RND50PC)	
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITLEFTHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitLeftHi);
//DeadCode AMM 14Jul99 						else
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITRIGHTHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitRightHi);
//DeadCode AMM 14Jul99 					}else if (caller->ai.combatskill >  SKILL_REGULAR)
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLIT,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplit);
//DeadCode AMM 14Jul99 					else
//DeadCode AMM 14Jul99 						if ((Math_Lib.rnd(RndValMAX)) > RND50PC)	
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITLEFTHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitLeftHi);
//DeadCode AMM 14Jul99 						else
//DeadCode AMM 14Jul99 							retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLITRIGHTHI,CHOSENMANOEUVRE,caller,trg,caller), SetUpDefensiveSplitRightHi);
//DeadCode AMM 14Jul99 				}
//DeadCode AMM 14Jul99 			}else
//DeadCode AMM 14Jul99 				retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_SELECTYOUROWNTARGETS,caller,trg,NULL, SelectTarget);		
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 	}else
//DeadCode AMM 14Jul99 	   	retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_IGNOREFORNOW,SPOTTEDASNEWUNFRIENDLY,caller,trg,caller),DoNothing);
//DeadCode AMM 14Jul99 
//DeadCode AMM 14Jul99 	return(retval);
//DeadCode AMM 14Jul99 }
//DeadCode AMM 14Jul99  */
//DeadCode AMM 14Jul99 
