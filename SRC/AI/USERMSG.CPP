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

////////////////////////////////////////////////////////////////////////
//
// Module:      usermsg.cpp
//
// Created:     15/02/99 by RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
//
//Macros defined:
////Use in header file ai.h to inter-ref between modules
//	EXTERNAI(name,type);		
//
////Use at top of defining module
//	DECISIONAI(name,type);			//If it has a decision table
//								
//	OPTIONAI(name,type);			//If it has no decision table
//
////Use in body of file
//	TABLEAI(name,type)				//To define the decision table			
//	{								//Usually preceeds INSTANCEAI()
//		{text,routine,speech}
//	};
//
//	INSTANCEAI(name,type)			//To define the AI actions
//	{
//		//actions
//		return false;
//	}
//
//
class DecisionAI *  DecisionAI::optiontable[DecisionAI::OPTIONTABLEMAX]={NULL};
int  DecisionAI::optiontablemax=0;

#include "worldinc.h"
#include "ai.h"
#include "node.h"
#include "rchatter.h"
//Dead#include	"messengn.h"

DECISIONAI(GroupInfoMsg,ItemPtr);
OPTIONAI(CallIn,ItemPtr);
OPTIONAI(CallPosition,ItemPtr);
OPTIONAI(CallFuel,ItemPtr);
OPTIONAI(CallStatus,ItemPtr);
OPTIONAI(SendEveryOneHome,ItemPtr);
OPTIONAI(SendHome,ItemPtr);
//DEADCODE RDH 05/03/99 OPTIONAI(SendHomeUrgent,ItemPtr);


DECISIONAI(CombatMsg,ItemPtr);
OPTIONAI(AutovectoringOff,ItemPtr);
OPTIONAI(AutovectoringOn,ItemPtr);
OPTIONAI(SightingRequest,ItemPtr);
OPTIONAI(CallSpotted,ItemPtr);
OPTIONAI(CallBreak,ItemPtr);
OPTIONAI(Padlocked,ItemPtr);
OPTIONAI(SixClr,ItemPtr);
OPTIONAI(NotClr,ItemPtr);

DECISIONAI(TowerMsg,ItemPtr);
OPTIONAI(MayDay,ItemPtr);
OPTIONAI(CallHomeTower,ItemPtr);
OPTIONAI(CallNearestTower,ItemPtr);
OPTIONAI(WindUpdateLow,ItemPtr);
OPTIONAI(WindUpdateHigh,ItemPtr);
OPTIONAI(HomeLandClear,ItemPtr);
OPTIONAI(NearLandClear,ItemPtr);

DECISIONAI(PreCombatMsg,ItemPtr);
OPTIONAI(TestGuns,ItemPtr);
OPTIONAI(JettisonStores,ItemPtr);
OPTIONAI(JettisonTanks,ItemPtr);
OPTIONAI(SpreadOut,ItemPtr);
OPTIONAI(CloseUp,ItemPtr);
OPTIONAI(MiGActivity,ItemPtr);
OPTIONAI(NearestMiGs,ItemPtr);
OPTIONAI(PatrolArea,ItemPtr);
OPTIONAI(RealTestGuns,ItemPtr);

DECISIONAI(PostCombatMsg,ItemPtr);
OPTIONAI(InitialPoint,ItemPtr);
OPTIONAI(AllDisengage,ItemPtr);
OPTIONAI(Regroup,ItemPtr);
OPTIONAI(TakeOverGroup,ItemPtr);

DECISIONAI(FACMsg,ItemPtr);
DECISIONAI(BombMsg,ItemPtr);
OPTIONAI(InitiateContact,ItemPtr);
OPTIONAI(LostSight,ItemPtr);
OPTIONAI(RemarkTarget,ItemPtr);
OPTIONAI(MoreTargets,ItemPtr);
OPTIONAI(LeaveArea,ItemPtr);
OPTIONAI(BeginRun,ItemPtr);
OPTIONAI(BombsAway,ItemPtr);

DECISIONAI(SecretMessages,ItemPtr);
OPTIONAI(SecretStartTrucks,ItemPtr);

//TempCode RDH 22Feb99 DECISIONAI(CommsPlyrMsg,ItemPtr)
//TempCode RDH 22Feb99 DECISIONAI(CommsMsgMsg,ItemPtr)


////////////////////////////////////////////////////////////////////////
//
// Function:    Top Level
// Date:        //RDH 22/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////

//Jim wants Paul to do this using his system
//DeadCode RDH 22Feb99 TABLEAI(SendMsg,ItemPtr)
//DeadCode RDH 22Feb99 {
//DeadCode RDH 22Feb99 	{GROUPINFO,	&GroupInfoMsg},
//DeadCode RDH 22Feb99 	{PRECOMBAT,	&PreCombatMsg}, 
//DeadCode RDH 22Feb99 	{COMBAT,	&CombatMsg}, 
//DeadCode RDH 22Feb99 	{POSTCOMBAT,&PostCombatMsg}, 
//DeadCode RDH 22Feb99 	{TOWER,		&TowerMsg},	
//DeadCode RDH 22Feb99 	{FAC,		&FACMsg},
//DeadCode RDH 22Feb99 	{COMMSPLAYER,&CommsPlyrMsg},
//DeadCode RDH 22Feb99 	{COMMSMSG,	&CommsMsgMsg}
//DeadCode RDH 22Feb99 
//DeadCode RDH 22Feb99 };
//DeadCode RDH 22Feb99 INSTANCEAI(SendMsg,ItemPtr)	{return false;}
//DeadCode RDH 22Feb99 


////////////////////////////////////////////////////////////////////////
//
// Function:    GroupInfoMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////

TABLEAI(GroupInfoMsg,ItemPtr)
{
	{PHRASE_CALLIN,			&CallIn, 			SCRIPT_CALLIN},	
	{PHRASE_CALLPOSN,		&CallPosition,	 	SCRIPT_CALLPOSN},
	{PHRASE_CALLFUEL,		&CallFuel,			SCRIPT_CALLFUEL},
	{PHRASE_CALLSTATUS,		&CallStatus,		SCRIPT_CALLSTATUS},
//DEADCODE RDH 08/03/99 	{PHRASE_SENDALLHOME,	&SendEveryOneHome, 	SCRIPT_ALLGOHOME},	
//DEADCODE RDH 08/03/99 	{PHRASE_SENDHOME,		&SendHome,	 		SCRIPT_SENDHOME},	
//DEADCODE RDH 05/03/99 can't see this working 	{PHRASE_URGHOME0,		&SendHomeUrgent, 	SCRIPT_CALLEE_URGGOHOME}
	{PHRASE_PARTS_S}, 
	{PHRASE_PARTS_S}

};
INSTANCEAI(GroupInfoMsg,ItemPtr)	{return false;}

INSTANCEAI(CallIn,ItemPtr)
{		 
	AirStrucPtr leader=callee->GroupLeader();
	prioritymessage->caller=leader;
	AirStrucPtr	sayto=leader;
	if (leader!=callee)
		sayto=callee;

	bool	buddy = false;											  //RDH 10/05/99
	for (AirStrucPtr eltlead=leader;eltlead;eltlead=eltlead->fly.nextflight)
		for (AirStrucPtr eltwing=eltlead;eltwing;eltwing=eltwing->Follower())
			if ((eltwing!=leader) &&	(!eltwing->Status.deadtime))	// not comms players
			{
				buddy = true;										  //RDH 10/05/99
 				if (eltwing!=callee)
				{
//					_Radio.TriggerMsg(MESSAGE_STRUC(to sayto,from eltwing).SetPriority(PRI_LOW));

//					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER, STATUSRESPONSE_DELAY_LP_RPT, eltwing, NULL, leader));
					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER, MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, NULL, sayto));
				}
				else
				{
//					_Radio.TriggerMsg(MESSAGE_STRUC(to leader,from eltwing).SetPriority(PRI_LOW));
					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER, MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, NULL, leader));
				}
			}

	if (!buddy)														  //RDH 10/05/99
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99

	return true;
}
INSTANCEAI(CallPosition,ItemPtr)
{
	AirStrucPtr leader=callee->GroupLeader();
	prioritymessage->caller=leader;
	AirStrucPtr	sayto=leader;
	SLong range;

	if (leader!=callee)
		sayto=callee;
	bool	buddy = false;											  //RDH 10/05/99

	for (AirStrucPtr eltlead=leader;eltlead;eltlead=eltlead->fly.nextflight)
		for (AirStrucPtr eltwing=eltlead;eltwing;eltwing=eltwing->Follower())
			if (eltwing!=leader && !eltwing->uniqueID.commsmove)
			{
				buddy = true;										  //RDH 10/05/99
				range = Art_Int.RangeFromTo(leader,eltwing);
				if (eltwing!=callee)
				{
//					_Radio.TriggerMsg(MESSAGE_STRUC(to sayto,from eltwing).SetPriority(PRI_LOW));
					if (range > MILES01)
						_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLPOSNREP , MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, eltwing, sayto));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLPOSNREPCLOSE , MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, eltwing, sayto));
				}
				else
				{
//					_Radio.TriggerMsg(MESSAGE_STRUC(to leader,from eltwing).SetPriority(PRI_LOW));
					if (range > MILES01)
						_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLPOSNREP , MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, eltwing, leader));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLPOSNREPCLOSE , MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, eltwing, leader));
				}
			}
	if (!buddy)														  //RDH 10/05/99
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99
	return true;
}
INSTANCEAI(CallFuel,ItemPtr)
{
	AirStrucPtr leader=callee->GroupLeader();
	prioritymessage->caller=leader;
	AirStrucPtr	sayto=leader;
	if (leader!=callee)
		sayto=callee;

	bool	buddy = false;											  //RDH 10/05/99
	for (AirStrucPtr eltlead=leader;eltlead;eltlead=eltlead->fly.nextflight)
		for (AirStrucPtr eltwing=eltlead;eltwing;eltwing=eltwing->Follower())
			if (eltwing!=leader && !eltwing->uniqueID.commsmove)
			{
				buddy = true;										  //RDH 10/05/99

				if (eltwing!=callee)
				{
					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLFUELREP, MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, NULL, sayto));
//					_Radio.TriggerMsg(MESSAGE_STRUC(to sayto,from eltwing).SetPriority(PRI_LOW));
				}
				else
				{
					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLFUELREP, MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, NULL, leader));
//					_Radio.TriggerMsg(MESSAGE_STRUC(to leader,from eltwing).SetPriority(PRI_LOW));
				}
			}
	if (!buddy)														  //RDH 10/05/99
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99
	return true;
}
INSTANCEAI(CallStatus,ItemPtr)
{
   	ScriptTables script;
	AirStrucPtr leader=callee->GroupLeader();
	prioritymessage->caller=leader;
	AirStrucPtr	sayto=leader;
	if (leader!=callee)
		sayto=callee;
	bool	buddy = false;											  //RDH 10/05/99
	for (AirStrucPtr eltlead=leader;eltlead;eltlead=eltlead->fly.nextflight)
		for (AirStrucPtr eltwing=eltlead;eltwing;eltwing=eltwing->Follower())
			if (eltwing!=leader && !eltwing->uniqueID.commsmove)
			{
				buddy = true;										  //RDH 10/05/99

				if(eltwing->ai.manoeuvre == MANOEUVRE_WELDEDWINGMAN) 
					script = SCRIPT_STATUSWING; 
				else
				{
					script = SCRIPT_STATUSFREE;
					if((eltwing->ai.unfriendly) && (eltwing->ai.unfriendly->Status.size==AirStrucSize))
					{
						for(;;)
						{
//DeadCode CSB 07/07/99								if (eltwing->AcIsPlayer())				//RJS 25May99
//DeadCode CSB 07/07/99									break;
							AirStrucPtr trg = AirStrucPtr(eltwing->ai.unfriendly);
							eltwing->Range = eltwing->Distance3D(&trg->World);

							FP fChasing  = (trg->World.X - eltwing->World.X) * eltwing->velx
										 + (trg->World.Y - eltwing->World.Y) * eltwing->vely
										 + (trg->World.Z - eltwing->World.Z) * eltwing->velz;
							fChasing     /= FP(eltwing->vel * eltwing->Range);

							FP fChased   = (eltwing->World.X - trg->World.X) * trg->velx
										 + (eltwing->World.Y - trg->World.Y) * trg->vely
										 + (eltwing->World.Z - trg->World.Z) * trg->velz;
							fChased      /= FP(trg->vel * eltwing->Range);

//DeadCode CSB 09/07/99								if( (eltwing->SubjectOnTargetTail(ANGLES_90Deg)) && (eltwing->SubjectFacingTarget(ANGLES_45Deg)) )
							if((fChasing > 0.5) && (fChased < 0.5))	//60 deg cone
							{
								if((AirStrucPtr(eltwing->ai.unfriendly))->classtype->phrasename == PHRASE_MIGS)
									script = SCRIPT_STATUSCHASEMIG;
								else 
								  script = SCRIPT_STATUSENGAGED;

								break;
							}
//DeadCode CSB 09/07/99								if( (eltwing->TargetOnSubjectTail(ANGLES_90Deg)) && (eltwing->TargetFacingSubject(ANGLES_45Deg)) )
							if((fChased > 0.5) && (fChasing < 0.5))	//60 deg cone
							{
								script = SCRIPT_STATUSATTACKED;
								break;
							}
							script = SCRIPT_STATUSENGAGED;
							break;
						}
					}
				}

				if (eltwing!=callee)
				{
//					_Radio.TriggerMsg(MESSAGE_STRUC(to sayto,from eltwing).SetPriority(PRI_LOW));
					_Radio.TriggerMsg(MESSAGE_STRUC (script, MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, NULL, sayto));
				}
				else
				{
//					_Radio.TriggerMsg(MESSAGE_STRUC(to leader,from eltwing).SetPriority(PRI_LOW));
					_Radio.TriggerMsg(MESSAGE_STRUC (script, MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, NULL, leader));
				}
			}
	if (!buddy)														  //RDH 10/05/99
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99
	return true;
}

//DEADCODE RDH 08/03/99 INSTANCEAI(SendHomeUrgent,ItemPtr)
//DEADCODE RDH 08/03/99 {
//DEADCODE RDH 08/03/99 	bool retval = false;
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 	if prioritymsg 
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 	{
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 		callee = AcShouldGoHome();
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 		if (!callee)
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 		{
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 			prioritymsg->scriptno  = SCRIPT_ALLHEALTHY;
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 		}else
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 		{
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 			script = SCRIPT_CALLEE_GOHOME;
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 		}
//DEADCODE RDH 08/03/99 //TempCode RDH 22Feb99 	}
//DEADCODE RDH 08/03/99 	return false;
//DEADCODE RDH 08/03/99 }


////////////////////////////////////////////////////////////////////////
//
// Function:    PreCombatMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(PreCombatMsg,ItemPtr)
{
	{PHRASE_TESTGUNS,			&TestGuns, 			SCRIPT_TESTGUNS},	
	{PHRASE_JETTISONSTORES0,	&JettisonStores, 	SCRIPT_JETTISONSTORES},	
	{PHRASE_JETTISONTANK0,		&JettisonTanks, 	SCRIPT_JETTISONTANK}, 
	{PHRASE_SPREADOUT,			&SpreadOut,			SCRIPT_SPREADOUT},
	{PHRASE_CLOSEUP,			&CloseUp,			SCRIPT_CLOSEUP},
	{PHRASE_MIGACTIVITY,		&MiGActivity,	 	SCRIPT_MIGACTIVITY},
	{PHRASE_NEARESTMIGSSHORT,	&NearestMiGs, 		SCRIPT_NEARESTMIGS},
	{PHRASE_PATROLAREASHORT,	&PatrolArea,		SCRIPT_PATROLAREALONG},
	{PHRASE_PARTS_S,			&RealTestGuns,		NULL}, 
	{PHRASE_PARTS_S}	
};
INSTANCEAI(PreCombatMsg,ItemPtr)	{return false;}

INSTANCEAI(TestGuns,ItemPtr)
{

	if (caller==Persons2::PlayerGhostAC)
		gunstimer=2;
	return false;
}


INSTANCEAI(RealTestGuns,ItemPtr)
{
	bool retval = false;

	//All in group test guns
	//never a problem so no more messages needed
	AirStrucPtr grplead = callee->FindGroupLeader();

	for (AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
		for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
			if(foll != Persons2::PlayerGhostAC && !foll->uniqueID.commsmove)
				foll->PublicFireABullet(0,FALSE);			//RJS 27May99

return retval;
}

INSTANCEAI(JettisonStores,ItemPtr)
{
	bool retval = false;
	//All in group JettisonStores
	//never a problem so no more messages needed

	AirStrucPtr grplead = callee->FindGroupLeader();
	for (AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
		for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
			if(foll != Persons2::PlayerGhostAC && !foll->uniqueID.commsmove)	
			{
				WorldStuff*	worldptr = mobileitem::currworld;
				Trans_Obj.DumpWeapons((AirStrucPtr)foll,*worldptr);
			}
	return retval;
}

INSTANCEAI(JettisonTanks,ItemPtr)
{
	bool retval = false;
//TempCode RDH 22Feb99 	//To minimise work, there is no chance that the player or a leader can //get a hung tank.
//TempCode RDH 22Feb99 
//TempCode RDH 22Feb99 	for each a/c in group
//TempCode RDH 22Feb99 	{//jettison tanks
//TempCode RDH 22Feb99 		if tanks don't release
//TempCode RDH 22Feb99 		{
//TempCode RDH 22Feb99 			TriggerMsg(MESSAGE_STRUC (SCRIPT__HUNGTANK, STATUSRESPONSE_DELAY_LP_RPT, currac, NULL, caller));
//TempCode RDH 22Feb99 		
//TempCode RDH 22Feb99 			TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLEE_HUNGTANKREPLY, STATUSRESPONSEREPLY_DELAY_LP_RPT, caller, NULL, currac));
//TempCode RDH 22Feb99 		}
//TempCode RDH 22Feb99 	}

	_Radio.ClearMessages(MSG_STATUSREPORT);										//RJS 03Jun99
	AirStrucPtr grplead = callee->FindGroupLeader();
	for (AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
		for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
			if(foll != Persons2::PlayerGhostAC && !foll->uniqueID.commsmove)	
			{
				WorldStuff*	worldptr = mobileitem::currworld;
				Trans_Obj.DumpFuel((AirStrucPtr)foll,*worldptr);
			}	
return retval;
}

INSTANCEAI(SpreadOut,ItemPtr)
{
	bool retval = false;
//TempCode RDH 22Feb99 	for each a/c in group
//TempCode RDH 22Feb99 		combat form
	AirStrucPtr flightlead = NULL;
	
	AirStrucPtr grplead = callee->FindGroupLeader();
	for (AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
		for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
			if(!foll->AcIsFlightLeader())
			{
				foll->formation = SQUAD_COMBAT_FLATV;
				foll->information = FALSE;
			}

	return retval;
}


INSTANCEAI(CloseUp,ItemPtr)
{
	bool retval = false;
//TempCode RDH 22Feb99 	for each a/c in group
//TempCode RDH 22Feb99 		 close form
	AirStrucPtr grplead = callee->FindGroupLeader();
	for (AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
		for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
			if(!foll->AcIsFlightLeader())
			{
				foll->formation = (FORMATIONDESC)grplead->formation;
				foll->information = FALSE;
			}

	return retval;
}




INSTANCEAI(MiGActivity,ItemPtr)
{
	bool retval = false;

	AirStruc*	bandit = NULL;
	int count = 0;
	SLong	range;
	bandit = caller->FindAnyBandit(range, count);

	if (count  ==0)
	{
		if (caller->classtype->phrasename == PHRASE_MIGS)
			_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller));
		else// only for UN
 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DENTIST_NOMIGACTIVITY, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, NULL, caller));
	}
	else if (count  == 1)
 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DENTIST_ONETRACE, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, bandit, caller));
 	else if  (		(count < 4)
				||	(caller->classtype->phrasename == PHRASE_MIGS)				
			 )
 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DENTIST_MANYTRACES, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, bandit, caller));
 	else //next msg only for UN
	 	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DENTIST_MULTIPLETRACE, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, bandit, caller));

	return retval;
}

INSTANCEAI(NearestMiGs,ItemPtr)
{
	bool retval = false;

	SLong range;
	int count=0;
	AirStruc* bandit = caller->FindAnyBandit(range, count);

 	if(!bandit)
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DENTIST_NOMIGACTIVITY, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, NULL, caller));
		return retval;
	}

	RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
	
	if 	(range > VISIBLERANGE)
	{
		if (rndpc >  RND50PC)
 			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER_TRACES_PLACENAME, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, bandit, caller));
		else
 			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER_TRACES_VECTOR, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, bandit, caller));
 	}else
 	{
 		if (rndpc >  RND50PC)
	 		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER_TRACES_HEADSUP, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, bandit, caller));
	 	else
	 		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER_TRACES_VECTOR, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, bandit, caller));
 	}
	
	return retval;
}
INSTANCEAI(PatrolArea,ItemPtr)
{
	bool retval = false;
		WayPointPtr	newwp;

	//find wp of type ip
	newwp = caller->waypoint->FindWP(WPNAME_Target);
	if (newwp)
	{
		caller->InterceptandRange (&caller->World, &newwp->World);
 		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_PATROLAREALONG_REPLY, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, newwp, caller));
	}
	return retval;
}


////////////////////////////////////////////////////////////////////////
//
// Function:    CombatMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(CombatMsg,ItemPtr)
{
	{PHRASE_GIVEFREEDOM,		&AutovectoringOn,	SCRIPT_PICKOWNTARGETS},
	{PHRASE_TAKECOMMAND,		&AutovectoringOff,	SCRIPT_WAITFORORDER},
	{PHRASE_SIGHTINGREQUEST,	&SightingRequest,	SCRIPT_WHEREISMIG},	
//DEADCODE RDH 05/03/99 can't see this one working	{PHRASE_REPORTMIGS,			&CallSpotted,	 	SCRIPT_REPORTMIGS},
	{PHRASE_BREAK,				&CallBreak,			SCRIPT_BRKBAD},			//RJS 11May99
	{PHRASE_PADLOCKED,			&Padlocked,			SCRIPT_PADLOCKED},
	{PHRASE_SIXCLR,				&SixClr,			SCRIPT_YOUCLEAR},
	{PHRASE_NOTCLEAR0,			&NotClr,			SCRIPT_NOTCLEAR}, //DAW 23/02/99,
	{PHRASE_PARTS_S}, 
	{PHRASE_PARTS_S}
};
INSTANCEAI(CombatMsg,ItemPtr)	{return	false;}

INSTANCEAI(AutovectoringOff,ItemPtr)
{
	AirStrucPtr leader=callee->GroupLeader();						  //RDH 16/05/99
	prioritymessage->caller=leader;
																	  //RDH 16/05/99
	Save_Data.gamedifficulty %= GD_AUTOVECTORING;
	bool retval = false;
	return retval;
}
INSTANCEAI(AutovectoringOn,ItemPtr)
{
	AirStrucPtr leader=callee->GroupLeader();						  //RDH 16/05/99
	prioritymessage->caller=leader;									  //RDH 16/05/99

	Save_Data.gamedifficulty |= GD_AUTOVECTORING;
	bool retval = false;
	return retval;
}
INSTANCEAI(SightingRequest,ItemPtr)
{
	AirStruc* buddy = caller->FindAcInGroup();
	AirStruc* bandit;
	if (prioritymessage) 
	{
		if (caller->classtype->phrasename == PHRASE_MIGS)
			prioritymessage->scriptno = SCRIPT_WHEREISBANDIT;

		prioritymessage->callee = buddy;		//null if no buddy
	}	

	if (buddy)
	{
		
		bandit= NULL;
		if (		(caller->ai.unfriendly)
				&&	(caller->ai.unfriendly->Status.size==AIRSTRUCSIZE)
		   )
		{
			bandit = (AirStruc*)caller->ai.unfriendly;
			caller->InterceptandRange(bandit);
		}
		int  count = -1;
			
		if (!bandit)
			bandit = caller->FindBandit(count);
		if ((!bandit)	||	(caller->Range > VISIBLERANGE))
		{
			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLEE_NOMIGS,
				MSG_NOBANDITCALL_DELAY_LP_RPT, buddy , NULL, caller));	
		}else
		{
			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_BANDIT_RELPOS,
				MSG_BANDITCALL_DELAY_LP_RPT, buddy, bandit, caller));
		}
	}else
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99

	bool retval = false;
	return retval;
}
INSTANCEAI(CallSpotted,ItemPtr)
{
	bool retval = false;
	return retval;
}
INSTANCEAI(CallBreak,ItemPtr)
{{
	tGroupLevel group = GroupLevelNotInFormation(caller);
	bool unffound = false;
	AirStrucPtr unf = NULL;
	AirStrucPtr victim = caller->AcCloseAttackingOneOfGroup(unffound);
	if (victim)
		unf = victim->ai.attacker;
	if (!unf)
	{
		SLong range;
		int count=0;
		unf = caller->FindAnyBandit(range, count);
		if (range > REDUCEDVISIBILITY)
			unf = NULL;
	}

	if (	(victim)	&&	(victim->ai.unfriendly))
	{//there is some one in trouble and they are in combat
		victim->InterceptandRange (&victim->World, &unf->World);
			SWord dhdg = victim->hdg - victim->HdgIntercept;
			bool onright = false;
			if (dhdg > 0)
				onright = true;
			if (victim->Range < (DANGERRANGE) + METRES200)
			{
				prioritymessage->callee = victim;
				prioritymessage->target = unf;
				prioritymessage->scriptno = BreakCall((AirStruc*)prioritymessage->caller, onright);
				caller->BreakCallReaction(victim, unf);
//DEADCODE RDH 27/06/99 				victimfound = true;
			}
	}else if (unf)
	{
		AirStrucPtr lead = caller->FindGroupLeaderClose();								  //RDH 12/07/99
		SendMsgAndCall(MESSAGE_STRUC(PHRASE_SELECTYOUROWNTARGETS,MSG_CHOSENMANOEUVRE,lead,unf,NULL), SelectTarget);	
	}else if (group == GROUP_LONER)
	{
		prioritymessage->callee = NULL;
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller));
	}else if (!unffound)
		{
			AirStruc* buddy = caller->FindAcInGroup();
			if (buddy)
			{
				prioritymessage->callee = buddy;
				_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_WOLF,
					MSG_BREAKCALL_REPLY_DELAY, buddy, NULL, prioritymessage->caller));
			}
		}
	bool retval = false;
	return retval;
}}
INSTANCEAI(Padlocked,ItemPtr)
{
	AirStruc*	buddy =caller->FindBuddy();

	if (		(buddy)
			&&	(Art_Int.AircraftAreClose(caller, buddy))
		)
	{
		if (prioritymessage) 
				prioritymessage->callee = buddy;
			

		AirStruc* bandit = caller->FindBanditOnTail();				  //RDH 12/06/99

		if (bandit)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTCLEAR, MSG_CLEAR_RPT, buddy, NULL, caller));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_YOUCLEAR, MSG_CLEAR_RPT , buddy, NULL, caller));
	}else
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller));

	}


	bool retval = false;
	return retval;
}
INSTANCEAI(SixClr,ItemPtr)
{
	//leader carries on, no action required
	AirStruc*	buddy =caller->FindBuddy();
	if (!buddy)
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller));

	bool retval = false;
	return retval;
}
INSTANCEAI(NotClr,ItemPtr)
{
	AirStruc*	buddy =caller->FindBuddy();
	if (buddy)
	{
		AirStruc* bandit = buddy->FindBanditOnTail();
		if (bandit)
		{
			if (buddy->ai.unfriendly !=bandit)
				SetEngage(buddy,bandit,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);

		}else
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WHERE, MSG_NOTCLEAR_RPT_DELAY, buddy, NULL, prioritymessage->caller));
		}
	}else
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller));

	bool retval = false;
	return retval;
}
////////////////////////////////////////////////////////////////////////
//
// Function:    PostCombatMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(PostCombatMsg,ItemPtr)
{
	{PHRASE_INITIALPOINT/*FORM*/,			&InitialPoint, 		SCRIPT_INITIALPOINT/*FORM*/},	 //DAW 23/02/99
	{PHRASE_DISENGAGE/*ALL*/,	&AllDisengage, 	SCRIPT_DISENGAGE_GOTPROBLEM/*ALL*/},	 //DAW 23/02/99 //DAW 23/02/99
	{PHRASE_REGROUP,		&Regroup, 	SCRIPT_REGROUP},
	{PHRASE_TAKEOVER,		&TakeOverGroup,	SCRIPT_TAKEOVER},
	{PHRASE_SENDALLHOME,	&SendEveryOneHome, 	SCRIPT_ALLGOHOME},	
	{PHRASE_SENDHOME,		&SendHome,	 		SCRIPT_CALLEE_GOHOME},	
	{PHRASE_PARTS_S}, 
	{PHRASE_PARTS_S}

};
INSTANCEAI(PostCombatMsg,ItemPtr)	{return false;}

INSTANCEAI(InitialPoint,ItemPtr)
{
	bool retval = false;

	AirStrucPtr leader=callee->GroupLeader();						  //RDH 16/05/99
	prioritymessage->caller=leader;
	WayPointPtr	newwp;

	
	//find wp of type ip
	newwp = caller->waypoint->FindWP(WPNAME_Target);
	caller->SetGroupWP(newwp);

	DisEngageAll(caller, prioritymessage);

	return retval;
}
INSTANCEAI(AllDisengage,ItemPtr)
{
	bool retval = false;
	AirStrucPtr leader=callee->GroupLeader();						  //RDH 16/05/99
	prioritymessage->caller=leader;
	DisEngageAll(caller, prioritymessage);

	return retval;
}
INSTANCEAI(Regroup,ItemPtr)
{
	AirStrucPtr leader=callee->GroupLeader();						  //RDH 16/05/99
	prioritymessage->caller=leader;

	bool retval = false;
	WayPointPtr	newwp;

	
	//find wp of type regroup
	newwp = caller->waypoint->FindWP(WPNAME_Regroup);
	caller->SetGroupWP(newwp);

	DisEngageAll(caller, prioritymessage);

	return retval;
}
INSTANCEAI(TakeOverGroup,ItemPtr)
{
	bool retval = false;
	if (caller->fly.nextflight)
	{
		prioritymessage->callee = caller->fly.nextflight;
		caller->RemoveElement();
	}else
	{
		prioritymessage->scriptno = SCRIPT_NOBODYAVAIL;
		prioritymessage->SetVoice(VOICE_REST);			//RJS 11May99
	}
	 
	return retval;
}
INSTANCEAI(SendHome,ItemPtr)
{
	AirStrucPtr leader=callee->GroupLeader();						  //RDH 16/05/99
	prioritymessage->caller=leader;

	WayPointPtr	newwp;
	bool retval = false;
	AirStruc*	 responder;
	if (prioritymessage) 
	{
		callee = caller->AcShouldGoHome();
		if (!callee)
		{
//DEADCODE RDH 11/05/99 				prioritymessage->caller  = NULL;
				prioritymessage->scriptno = SCRIPT_ALLHEALTHY;
				prioritymessage->SetVoice(VOICE_REST);

		}else
		{
			
			callee = caller->FindBuddy();		//##test
			AirStruc* buddy = callee->FindBuddy();
			RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
			if (buddy)
			{
				if (rndpc >  RND50PC)
				{
					prioritymessage->callee = buddy;
					prioritymessage->scriptno = SCRIPT_CALLEE_ESCORT;
					newwp = buddy->waypoint->FindWP(WPNAME_Landing);
					responder = buddy;
					if (newwp)
						buddy->waypoint = newwp;
				}else
				{
					responder = callee;
					prioritymessage->scriptno = SCRIPT_CALLEE_GOHOME;
				}

			}else
			{
					responder = callee;
					prioritymessage->scriptno = SCRIPT_CALLEE_GOHOME;
			}
			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER_GOHOME_REPLY, MSG_GOHOMEREPLY_DELAY_LP_RPT,responder, NULL, caller));
			newwp = callee->waypoint->FindWP(WPNAME_Landing);
			if (newwp)
				callee->waypoint = newwp;
			
		}
	}
	return false;
}
INSTANCEAI(SendEveryOneHome,ItemPtr)
{
	AirStrucPtr leader=callee->GroupLeader();						  //RDH 16/05/99
	prioritymessage->caller=leader;
	bool retval = false;
	WayPointPtr	newwp;

	_Miles.SequenceAudible(FIL_MUSIC_SNEAKING_AWAY);
	//always go for landing wp
	//find wp of type  land
	newwp = caller->waypoint->FindWP(WPNAME_Landing);
	caller->SetGroupWP(newwp);

	DisEngageAll(caller, prioritymessage);

	return false;
}


////////////////////////////////////////////////////////////////////////
//
// Function:    TowerMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////

TABLEAI(TowerMsg,ItemPtr)
{
	{PHRASE_MAYDAY,				&MayDay,			SCRIPT_MAYDAY},
	{PHRASE_HOMETOWER,			&CallHomeTower,		SCRIPT_GIMMEAVECTOR},
	{PHRASE_NEARESTTOWER,		&CallNearestTower,	SCRIPT_GIMMEAVECTOR},
	{PHRASE_SURFACEWIND,		&WindUpdateLow,		SCRIPT_SURFACEWINDREQUEST}, 
	{PHRASE_ALTWIND,			&WindUpdateHigh,	SCRIPT_ALTWINDREQUEST}, 
	{PHRASE_HOMELANDCLEARANCE,	&HomeLandClear,		SCRIPT_LANDCLEARANCE}, 
	{PHRASE_NEARLANDCLEARANCE,	&NearLandClear,		SCRIPT_LANDCLEARANCE},
	{PHRASE_PARTS_S}, 
	{PHRASE_PARTS_S} 
};
INSTANCEAI(TowerMsg,ItemPtr)   {return false;}

INSTANCEAI(MayDay,ItemPtr)
{	
	bool retval = false;
	
	itemptr NearestAF;// = caller->ai.homebase;
	int AFRange = -1;

	int EnemyColour = NAT_ALIGN;
	if (callee->nationality==NAT_BLUE) EnemyColour = NAT_RED;
	if (callee->nationality==NAT_RED)  EnemyColour = NAT_BLUE;

	SWord i = 0;
	while (SupplyTree::airfieldinfo[i].nationality != NAT_ALIGN)
	{
		if	(		(SupplyTree::airfieldinfo[i].nationality != EnemyColour) //RDH 12/07/99
				&&	(SupplyTree::airfieldinfo[i].nationality != NAT_AMBER) //RDH 12/07/99
			)														  //RDH 12/07/99
		{
			itemptr	ThisAF = *Persons2::ConvertPtrUID(SupplyTree::airfieldinfo[i].airfield);
			callee->InterceptandRange(ThisAF);
			if (		((AFRange == -1) || (callee->Range < AFRange)) //RDH 12/07/99
					&&	(SupplyTree::airfieldinfo[i].attackstats.damagelevel<90)  //RDH 12/07/99
			   )													  //RDH 12/07/99
			{
				NearestAF = ThisAF;			
				AFRange = callee->Range;
			}
		}
		i++;
	}

	//find nearest airfield
	if(AFRange != -1)
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_NEARESTAIRFIELD, MSG_MAYDAYREPLY_DELAY_RPT, VOICE_TOWER, NearestAF, callee));
	return retval;
}

INSTANCEAI(CallHomeTower,ItemPtr)
{
	bool retval = false;
	//for home field
	itemptr HomeAF = caller->ai.homebase;
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_STEER_RANGE, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, HomeAF, callee));

	return retval;
}

INSTANCEAI(CallNearestTower,ItemPtr)
{
	bool retval = false;
//for nearest field
	//find nearest tower
	itemptr NearestAF;// = caller->ai.homebase;
	int AFRange = -1;

	int EnemyColour = NAT_ALIGN;
	if (callee->nationality==NAT_BLUE) EnemyColour = NAT_RED;
	if (callee->nationality==NAT_RED)  EnemyColour = NAT_BLUE;

	SWord i = 0;
	while (SupplyTree::airfieldinfo[i].nationality != NAT_ALIGN)
	{
		if	(		(SupplyTree::airfieldinfo[i].nationality != EnemyColour) //RDH 12/07/99
				&&	(SupplyTree::airfieldinfo[i].nationality != NAT_AMBER) //RDH 12/07/99
			)														  //RDH 12/07/99
		{
			itemptr	ThisAF = *Persons2::ConvertPtrUID(SupplyTree::airfieldinfo[i].airfield);
			callee->InterceptandRange(ThisAF);
			if (		((AFRange == -1) || (callee->Range < AFRange)) //RDH 12/07/99
					&&	(SupplyTree::airfieldinfo[i].attackstats.damagelevel<90)  //RDH 12/07/99
			   )													  //RDH 12/07/99
			{
				NearestAF = ThisAF;			
				AFRange = callee->Range;
			}
		}
		i++;
	}
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_STEER_RANGE, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, NearestAF, callee));
	return retval;
}

INSTANCEAI(WindUpdateLow,ItemPtr)
{
	bool retval = false;
 	if(Save_Data.flightdifficulty [FD_WINDGUSTS])
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED_GUSTS, MSG_STATUSRESPONSE_DELAY_LP_RPT,
									VOICE_TOWER, NULL, callee));
	else
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED, MSG_STATUSRESPONSE_DELAY_LP_RPT,
									VOICE_TOWER, NULL, callee));

	return retval;
}

INSTANCEAI(WindUpdateHigh,ItemPtr)
{
	bool retval = false;
 	if(Save_Data.flightdifficulty [FD_WINDGUSTS])
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_ALTWIND_BEARINGNO_SPEED_GUSTS, MSG_STATUSRESPONSE_DELAY_LP_RPT,
									VOICE_TOWER, NULL, callee));
	else
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_ALTWIND_BEARINGNO_SPEED, MSG_STATUSRESPONSE_DELAY_LP_RPT,
									VOICE_TOWER, NULL, callee));

	return retval;
}

INSTANCEAI(HomeLandClear,ItemPtr)
{
	bool retval = false;
	itemptr HomeAF = caller->ai.homebase;
	callee->InterceptandRange(HomeAF);
	if(callee->PlayerInGroup())
	{
		if(callee->Range < MILES05)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOLAND, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, callee, callee));//, TRUE));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TOWER_NOTSEEN_STEER_RANGE, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, HomeAF, callee));//, TRUE));
	}
	return retval;
}

INSTANCEAI(NearLandClear,ItemPtr)
{
	bool retval = false;
	
	itemptr NearestAF;// = caller->ai.homebase;
	int AFRange = -1;

	int EnemyColour = NAT_ALIGN;
	if (callee->nationality==NAT_BLUE) EnemyColour = NAT_RED;
	if (callee->nationality==NAT_RED)  EnemyColour = NAT_BLUE;

	SWord i = 0;
	while (SupplyTree::airfieldinfo[i].nationality != NAT_ALIGN)
	{
		if(SupplyTree::airfieldinfo[i].nationality != EnemyColour)
		{
			itemptr	ThisAF = *Persons2::ConvertPtrUID(SupplyTree::airfieldinfo[i].airfield);
			callee->InterceptandRange(ThisAF);
			if((AFRange == -1) || (callee->Range < AFRange))
			{
				NearestAF = ThisAF;			
				AFRange = callee->Range;
			}
		}
		i++;
	}

	callee->InterceptandRange(NearestAF);
	if(callee->Range < MILES05)
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOLAND, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, NULL, callee));//, TRUE));
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TOWER_NOTSEEN_STEER_RANGE, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, NearestAF, callee));//, TRUE));
	return retval;
}

////////////////////////////////////////////////////////////////////////
//
// Function:    FACMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(FACMsg,ItemPtr)
{
//DEADCODE DAW 23/02/99 	{PHRASE_INITIATECONTACT,	&InitiateContact, SCRIPT_MAKECONTACTWITHFAC},	
	{PHRASE_BEGINYOURRUN,	&BeginRun,		SCRIPT_STARTAPPROACH_L},
	{PHRASE_LOSTSIGHTSHORT,	&LostSight, 	SCRIPT_LOSTSIGHTOFFAC},	
	{PHRASE_REMARKTARGETSHORT,	&RemarkTarget, 	SCRIPT_REMARKTARGET},
	{PHRASE_MISSEDTARGETSHORT,	&RemarkTarget, 	SCRIPT_MISSEDTARGET},		//is missed target going to fit in?
	{PHRASE_MORETARGETSSHORT,	&MoreTargets, 	SCRIPT_MORETARGETSREQUST},
	{PHRASE_LEAVEAREA,			&LeaveArea,		SCRIPT_LEAVEAREA},
#ifndef NDEBUG
	{PHRASE_BOMBSAWAY,		&BombsAway,			0},
#else
	{PHRASE_PARTS_S,		&BombsAway,			0},
#endif
	{PHRASE_PARTS_S}	//real end of list
};

TABLEAI(BombMsg,ItemPtr)
{
//DEADCODE DAW 23/02/99 	{PHRASE_INITIATECONTACT,	&InitiateContact, SCRIPT_MAKECONTACTWITHFAC},	
	{PHRASE_BEGINYOURRUN,	&BeginRun,		SCRIPT_STARTAPPROACH_L},
	{PHRASE_LEAVEAREA,			&LeaveArea,		SCRIPT_LEAVEAREA},
#ifndef NDEBUG
	{PHRASE_BOMBSAWAY,		&BombsAway,			SCRIPT_DROPBOMBS_F},
#else
	{PHRASE_PARTS_S,		&BombsAway,			SCRIPT_DROPBOMBS_F},
#endif
	{PHRASE_PARTS_S}	//real end of list
};

INSTANCEAI(FACMsg,ItemPtr)	{return false;}
INSTANCEAI(BombMsg,ItemPtr)	{return false;}

INSTANCEAI(BeginRun,ItemPtr)
{
	ItemPtr target=*trg;
	if (!target && caller->ai.unfriendly && caller->ai.unfriendly->Status.size<=FORMATIONSIZE)
		target=*caller->ai.unfriendly;
	bool retval = false;
	AirStrucPtr grplead=caller;
	if (caller->formpos)
		grplead=caller->fly.leadflight;
	if (target && target->Status.size<=FORMATIONSIZE && caller->waypoint) //JIM 16/06/99
		if  ((caller->duty&ACTIONCODE)!=DA_CAP)
			if (caller->IsLocalLeader())
			{
				caller->ai.manoeuvre.value=caller->SelectElement(target);
				UniqueID	skipunder=caller->waypoint->skipunder,
							skipover=caller->waypoint->skipover;
				if ((caller->duty&DUTYMASK)==DC_CAS)
				{	//tell everyone in the group to go for this target!
					int skip=-1;//-ve=before player;0=player;+ve=afterplayer
					for (AirStrucPtr fl=grplead;fl;fl=fl->fly.nextflight)
						for (AirStrucPtr w=fl;w;w=w->Follower())
							if (w->uniqueID.count>=skipunder && w->uniqueID.count<=skipover) 
							{
								if (w->movecode!=AUTO_CAS)
								{
									w->movecode=AUTO_CAS;
									w->ai.unfriendly=*target;
									w->ai.ManStep=0;
								}
								if (w->uniqueID.count==skipunder)
									grplead=w;
								if (skip<0)
								{
									if (w==caller)
									{
										w->ai.unfriendly=*target;
										w->ai.ManStep=2;
//DEADCODE JIM 21/05/99 										if ((w->duty&ACTIONSUBCODE)<=DA_SINGLEFILE)
//DEADCODE JIM 21/05/99 											skip=1;
//DEADCODE JIM 21/05/99 										else
											skip=0;
									}
									else
									{}
								}
								else
									if (skip==0)
										if (w->IsLocalLeader())
											skip=-1;
										else
										{
											w->ai.unfriendly=*target;
											if ((w->duty&ACTIONSUBCODE)>DA_SINGLEFILE) //JIM 21/05/99
											{						  //JIM 21/05/99
												w->ai.ManStep=1;
												w->manoeuvretime=10*SECS100;
											}						  //JIM 21/05/99
										}
							}
				}
				else
				{
					int skip=-1;//-ve=before player;0=player;+ve=afterplayer
					for (AirStrucPtr fl=grplead;fl;fl=fl->fly.nextflight)
						for (AirStrucPtr w=fl;w;w=w->Follower())
							if (w->uniqueID.count>=skipunder && w->uniqueID.count<=skipover) 
							{
								if (w->movecode!=AUTO_BOMB)
								{
									w->movecode=AUTO_BOMB;
									w->ai.unfriendly=*target;
									w->ai.ManStep=0;
								}
								if (w->uniqueID.count==skipunder)
									grplead=w;
								if (skip<0)
								{
									if (w==caller)
									{
										w->ai.unfriendly=*target;
										w->ai.manoeuvre.value=caller->ai.manoeuvre.value;
										w->ai.ManStep=2;
										if ((w->duty&ACTIONSUBCODE)<=DA_SINGLEFILE)
											skip=1;
										else
											skip=0;
									}
									else
									{}
								}
								else
									if (skip==0)
										if (w->IsLocalLeader())
											skip=-1;
										else
										{
											w->ai.unfriendly=*target;
											w->ai.ManStep=1;
											w->manoeuvretime=10*SECS100;
										}
							}

				}
				AirStrucPtr buddy=caller->FindABuddyNotPlayer();
				if (buddy)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ROGER,(MsgType)(MSG_CLEAR_RPT+MSG_BLOCKCHATTER) , buddy, NULL, callee));//RJS 06Jul99

			}
			else
			{	//not local leader
				if (grplead==caller)
					grplead=caller->FindBuddy();
				if (grplead)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TARGETNOTIDENTIFIED, MSG_CLEAR_RPT , grplead, NULL, callee));
				
			}
		else
		{	//mig cap
			if (grplead==caller)
				grplead=caller->FindBuddy();
			if (grplead)
				_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_ORBIT, MSG_CLEAR_RPT , grplead, NULL, callee));
		}
	else
	{	//no target
		if (grplead==caller)
			grplead=caller->FindBuddy();
		if (grplead)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TARGETNOTIDENTIFIED, MSG_CLEAR_RPT , grplead, NULL, callee));

//DEADCODE DAW 17/05/99 		if (prioritymessage)
//DEADCODE DAW 17/05/99 		{
//DEADCODE DAW 17/05/99 			prioritymessage->caller=grplead;
//DEADCODE DAW 17/05/99 		}
		retval=true;
	}
	return retval;

}
INSTANCEAI(BombsAway,ItemPtr)
{
	bool retval = true;
	if ((caller->duty&ACTIONCODE)!=DA_CAP)
	{
		int eltnum=0;
		if (trg)
		{
			trg=caller->SelectTarget(trg,&eltnum);
		}
		caller->ai.unfriendly=trg;
		caller->ai.manoeuvre.value=eltnum;
		caller->ai.ManStep=15;

		if (caller==Persons2::PlayerGhostAC)
		{
			Persons2::PlayerSeenAC->ai.unfriendly=trg;
			Persons2::PlayerSeenAC->ai.manoeuvre.value=eltnum;
			Persons2::PlayerSeenAC->ai.ManStep=15;
		}
	}
	return retval;
}
INSTANCEAI(LeaveArea,ItemPtr)
{
	bool retval = false;
//TempCode RDH 22Feb99 	if prioritymsg 
//TempCode RDH 22Feb99 	{
//TempCode RDH 22Feb99 		prioritymsg->callee = FindFAC()
//TempCode RDH 22Feb99 		if winchester
//TempCode RDH 22Feb99 			prioritymsg->scriptno = SCRIPT_ADVISEFACWINCHESTER;
//TempCode RDH 22Feb99 		else
//TempCode RDH 22Feb99 			prioritymsg->scriptno = SCRIPT_ADVISEFACBINGO; 
//TempCode RDH 22Feb99 		TriggerMsg(MESSAGE_STRUC(SCRIPT_ADVISEFACFINISHEDREPLY, ADVISEFACFINISHEDREPLY_DELAY_LP_RPT, prioritymsg->callee, NULL, caller));
//TempCode RDH 22Feb99 	}
	if (caller==Persons2::PlayerSeenAC)
		caller=Persons2::PlayerGhostAC;
	if (caller->formpos)
		caller=caller->fly.leadflight;
	if (caller->movecode!=AUTO_FOLLOWWP)
	{
//DeadCode jim 01Jul99 		if (caller==Persons2::PlayerSeenAC)
//DeadCode jim 01Jul99 			caller=Persons2::PlayerGhostAC;
		if ((caller->duty&ACTIONCODE)!=DA_CAP)
			if ((caller->duty&DUTYMASK)==DC_CAS)
			{
				AirStrucPtr fac=caller->FindMyFAC();
				if (fac)
				{
					if (prioritymessage)
						prioritymessage->callee=fac;
					while (fac->GetFACStage()<FAC_EXTRAS)
						fac->waypoint=fac->waypoint->next;
					fac->SendFACMessage(FAC_EXTRAS);
					fac->ai.ManStep=FAC_EXTRAS;
				}
			}
//DeadCode jim 01Jul99 		if (caller->formpos)
//DeadCode jim 01Jul99 			caller=caller->fly.leadflight;
		WayPointPtr wp=caller->waypoint,
					oldwp=wp;
		wp=wp->FindWP(WPNAME_Regroup);
		if (wp)
		{
			for (AirStrucPtr fl=caller;fl;fl=fl->fly.nextflight)
				for (AirStrucPtr w=fl;w;w=w->Follower())
				{
					w->movecode=AUTO_FOLLOWWP;
					w->information=FALSE;
					w->manoeuvretime=0;
					if (w->waypoint && w->waypoint->wpname==WPNAME_Target) //DAW 28/09/99
						w->waypoint=wp;
//DeadCode jim 01Jul99 				if (w->waypoint==oldwp)
//DeadCode jim 01Jul99 					w->waypoint=wp;
				}
			callee->waypoint=wp;
		}
	}
	return retval;
}


INSTANCEAI(InitiateContact,ItemPtr)	//THIS IS DEAD!
{
	bool retval = false;
//TempCode RDH 22Feb99 	FindFAC();
//TempCode RDH 22Feb99 	TriggerMsg(MESSAGE_STRUC(SCRIPT_FACMAKESCONTACT, FACCONTACTREPLY_DELAY_LP_RPT, fac, NULL, caller));
	return retval;
}
INSTANCEAI(LostSight,ItemPtr)
{
	bool retval = false;
	if  ((caller->duty&ACTIONCODE)!=DA_CAP && (caller->duty&DUTYMASK)==DC_CAS)
	{
		AirStrucPtr fac=caller->FindMyFAC();
		if (fac)
		{
			if (prioritymessage)
				prioritymessage->callee=fac;
			fac->SendFACMessage(FAC_WAITRECONNECT);		
		}
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , caller, NULL, caller));
	}


	return retval;
}

INSTANCEAI(RemarkTarget,ItemPtr)
{
	bool retval = false;
//TempCode RDH 22Feb99 	TriggerMsg(MESSAGE_STRUC(SCRIPT_ROGERTRYAGAIN, FACREMARKREPLY_DELAY_LP_RPT, fac, NULL, this));
//TempCode RDH 22Feb99 //Then slip into FAC_WATCHRROCKETS
	if  ((caller->duty&ACTIONCODE)!=DA_CAP && (caller->duty&DUTYMASK)==DC_CAS)
	{
		AirStrucPtr fac=caller->FindMyFAC();
		if (fac)
		{
			if (prioritymessage)
				prioritymessage->callee=fac;
			int stage=fac->GetFACStage();
			if (stage>=FAC_EXTRAS)
			{
				fac->SendFACMessage(FAC_NOMORETARGETS);
			}
			else
			if (stage>=FAC_ROCKETEER)
			{
				fac->SendFACMessage(FAC_WATCHROCKETS);
 				fac->ai.ManStep=FAC_ROCKETEER;
				fac->SetManoeuvreTime(500);
			}
			else
				fac->SendFACMessage(FAC_WAITRECONNECT);
		}
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , caller, NULL, caller));
	}
	return retval;
}

INSTANCEAI(MoreTargets,ItemPtr)
{
	bool retval = false;
//Then slip into FAC selects next target
	if  ((caller->duty&ACTIONCODE)!=DA_CAP)
		if ((caller->duty&DUTYMASK)==DC_CAS)
		{
			AirStrucPtr fac=caller->FindMyFAC();
			if (fac)
			{
				if (prioritymessage)
					prioritymessage->callee=fac;
				int stage=fac->GetFACStage();
				if (stage>=FAC_TARGETAREA && stage<FAC_EXTRAS)
				{
					if (stage<FAC_ROCKETEER)
						fac->waypoint=fac->waypoint->next->next;
					else
						fac->waypoint=fac->waypoint->next;
					stage=fac->GetFACStage();
					if (stage>=FAC_EXTRAS)
						while (fac->waypoint->prev->action==wpengagetargetno)
							fac->waypoint=fac->waypoint->prev->prev;
					fac->ai.unfriendly=fac->waypoint->next->target;
					fac->ai.ManStep=FAC_DESCRIBETARGETS;
				}
				else
					if (stage<FAC_TARGETAREA)
						fac->SendFACMessage(FAC_WELCOME_LONGRANGE);		
					else
						fac->SendFACMessage(FAC_NOMORETARGETS);
				caller->ai.unfriendly=fac->ai.unfriendly;
			}
			else
			{
				_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , caller, NULL, caller));
			}
			if (caller->formpos)
				caller=caller->fly.leadflight;
			for (AirStrucPtr fllead=caller;fllead;fllead=fllead->fly.nextflight)
				for (AirStrucPtr follower=fllead;follower;follower=follower->Follower())
					if (follower->ai.unfriendly)
					{
						follower->ai.unfriendly=NULL;
					}
//DeadCode CJ 04Jul99 			caller->ai.unfriendly=fac->ai.unfriendly;
		}
	else
		if ((caller->duty&DUTYMASK)==DC_AR || (caller->duty&DUTYMASK)==DC_WW)
		{
			AirStrucPtr buddy=caller->FindBuddy();
			if (buddy)
			{
				bool	anybombers=false;
				if (caller->formpos)
				{	//make message from leader to player
					buddy=caller;	
					caller=caller->fly.leadflight;
					prioritymessage->caller=caller;	
				}
				for (AirStrucPtr l=caller;l;l=l->fly.nextflight)
					for (AirStrucPtr w=l;w;w=w->Follower())
						if (w->movecode==AUTO_BOMB)
						{
							w->movecode=AUTO_FOLLOWWP;
							w->manoeuvretime=0;
							w->information=FALSE;
							anybombers=true;
						}
				prioritymessage->scriptno=SCRIPT_CALLER_BREAK_ORBIT;
				prioritymessage->callee=buddy;
				if (anybombers)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_BREAK_ORBITREPLY, MSG_CLEAR_RPT , buddy, NULL, caller));
				else
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE1CONV_OPT_0, MSG_CLEAR_RPT , buddy, NULL, caller));
			}
			else
			{
				caller->movecode=AUTO_FOLLOWWP;
				caller->manoeuvretime=0;
				caller->information=FALSE;
				prioritymessage->scriptno=SCRIPT_CALLER_BREAK_ORBIT;
			}
		}

	return retval;
}


//////////////////////////////////////////////////////////////////////
//
// Function:    SecretMessages
// Date:		10/06/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
TABLEAI(SecretMessages,ItemPtr)
{
//DEADCODE DAW 23/02/99 	{PHRASE_INITIATECONTACT,	&InitiateContact, SCRIPT_MAKECONTACTWITHFAC},	
	{PHRASE_PARTS_S,	&SecretStartTrucks,		PHRASE_PARTS_S},
	{PHRASE_PARTS_S},
	{PHRASE_PARTS_S}
};
INSTANCEAI(SecretMessages,ItemPtr)	{return false;}


INSTANCEAI(SecretStartTrucks,ItemPtr)
{
	GR_TruckMoveCode=GROUND_TAXI;
	return false;
};

////////////////////////////////////////////////////////////////////////
//
// Function:    CommsPlayerMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
//TempCode RDH 22Feb99 TABLEAI(CommsPlyrMsg,ItemPtr)
//TempCode RDH 22Feb99 {
//Display the names of the comms players that can be chatted to
//There are a max of 8 comms players. Exclude the player from the list.
//Add:	send to all and send to my side
//TempCode RDH 22Feb99 };
//TempCode RDH 22Feb99 INSTANCEAI(CommsPlyrMsg,ItemPtr)	{return false;}

////////////////////////////////////////////////////////////////////////
//
// Function:    CommsMsgMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
//TempCode RDH 22Feb99 TABLEAI(CommsMsgMsg,ItemPtr)
//TempCode RDH 22Feb99 {
	//TempCode RDH 22Feb99 {},
	//TempCode RDH 22Feb99 {}
//display the list of user messages that can be sent
//These will be longer than other menus. Perhaps we need to be able to //change the size of the smoked glass panel

//TempCode RDH 22Feb99 };
//TempCode RDH 22Feb99 INSTANCEAI(CommsMsgMsg,ItemPtr)	{return false;}

void	AirStruc::SetGroupWP(WayPoint*	newwp)
{
	AirStruc*	currac = FindGroupLeader();
	while (currac)
	{
		AirStruc*	ac = currac;
		while (ac)
		{
			ac->waypoint = newwp;
			ac=(AirStruc*)ac->follower;
		}
		currac=currac->fly.nextflight;
	}

}
AirStruc*	AirStruc::AcShouldGoHome()
{
	AirStruc*	currac = FindGroupLeader();
	while (currac)
	{
		AirStruc*	ac = currac;
		while (ac)
		{
			if (ac->AircraftDamaged())
				return (ac);
			ac=(AirStruc*)ac->follower;
		}
		currac=currac->fly.nextflight;
	}
	return (NULL);
}
void	ArtInt::DisEngageAll(AirStruc* caller, MESSAGE_STRUC* prioritymessage)
{
	if (caller==Persons2::PlayerSeenAC)								  //RDH 16/05/99
		caller=Persons2::PlayerGhostAC;								  //RDH 16/05/99

	Save_Data.gamedifficulty %= GD_AUTOVECTORING;


	AirStruc* leader = caller->FindGroupLeader();
	AirStruc* callee=caller->FindBuddy();
	if (callee)
	{
		if (leader->fly.leadflight)
			leader = leader->fly.leadflight;
		
		if (leader->movecode==AUTO_COMBAT)
		{
			leader->ai.manoeuvre = MANOEUVRE_TOPCOVER;		//this ensure everybody tries to disengage	
			if (	leader->ai.unfriendly
				&&	leader->ai.unfriendly->Status.size==AIRSTRUCSIZE
				&&	((AirStrucPtr)leader->ai.unfriendly)->ai.attacker==leader
				)
				((AirStrucPtr)leader->ai.unfriendly)->ai.attacker=NULL;
			leader->ai.unfriendly=NULL;
		}else if (leader->movecode==AUTO_PRECOMBAT)
		{
			AllBreakOff(leader);
		}


		if (prioritymessage)
		{
			prioritymessage->caller=leader;
			prioritymessage->callee= callee;
		}
		for (AirStrucPtr lead = leader;lead;lead=lead->fly.nextflight)
			for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
				if ((foll->fly.callnum % 4) == 0)
				{
					if(foll != leader)
					{
						if (	(foll->movecode == AUTO_COMBAT)	||	(foll->movecode == AUTO_PRECOMBAT))
						{
	//DEADCODE RDH 17/05/99 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_DISENGAGING, MSG_DISENGAGE_DELAY_LP_RPT , foll, NULL, caller));
	//we don't have disengaging in the other script so it is silent.
	//solution is to say: roger
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_ROGER, (MsgType)(MSG_DISENGAGE_DELAY_LP_RPT+MSG_BLOCKCHATTER) , foll, NULL, caller));//RJS 06Jul99
						}else
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_ROGER, (MsgType)(MSG_DISENGAGE_DELAY_LP_RPT+MSG_BLOCKCHATTER) , foll, NULL, caller));//RJS 06Jul99
					}
				}
	}else
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, (MsgType)(MSG_CLEAR_RPT+MSG_BLOCKCHATTER) , NULL, NULL, leader));//RJS 06Jul99

}
WayPointPtr		WayPoint::FindWP(WPNames name)
{
	WayPointPtr newwp = this;
	if (!this)
		return this;
	if (newwp->wpname >= name)
	{
		while (	(newwp) && (newwp->wpnum != 0 || newwp->wpname != name))
			newwp = newwp->prev;
		if (newwp)
			return (newwp);
		else
			return (this);
	}else 
	{
		while (	(newwp) && (newwp->wpnum != 0 || newwp->wpname != name))
			newwp = newwp->next;
		if (newwp)
			return (newwp);
		else
			return (this);

	}
}
