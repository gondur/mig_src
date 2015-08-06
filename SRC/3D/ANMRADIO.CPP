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
//Filename       anmradio.cpp
//System         
//Author         Robert Slater
//Date           Fri 5 Feb 1999
//Description    
//				Radio chatter triggered by damage....
//
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#include	"worldinc.h"
#include	"boxcol.h"
#include	"rchatter.h"
#include	"anmradio.h"										//RJS 04Feb99
#include	"3dinstr.h"											//RJS 13May99



#define		VOX_RAND	4096		//8192									//RJS 30Jun99

DamageChat	_DamageChat;


DamageChat::DamageChat()
{
	acHit = acHitter = buddy = leader = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExecuteRadio
//Author		Robert Slater
//Date			Thu 4 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::ExecuteRadio(	ItemPtr				itm,
									ItemPtr				hitter,
									HitEffectRecord&	hitstruc	)
{
	if (hitter)												//RJS 15Jun99
	{
 		acHit = (AirStrucPtr) itm;
 		acHitter = (AirStrucPtr) hitter;
		if (acHit->nationality != acHitter->nationality)			//RJS 25Jun99
		{
 			buddy = acHit->FindBuddy();
 	
 			if (acHit->nationality != Manual_Pilot.ControlledAC2->nationality)
 			{
 				acHitIsFriend = FALSE;
 				leader = acHitter->GroupLeader();
 			}
 			else
 			{
 				acHitIsFriend = TRUE;
 				leader = acHit->GroupLeader();
 			}
 
 			switch (hitstruc.val)
 			{
 			case RADIO_GENERAL_LV1:
 			{
 				if (!acHitIsFriend)
 					OtherSideDamageLevel1();
 				else
 					PlayerSideDamageLevel1();
 			}
 			break;
 			case RADIO_GENERAL_LV2:
 			{
 				if (!acHitIsFriend)
 					OtherSideDamageLevel2();
 				else
 					PlayerSideDamageLevel2();
 			}
 			break;
			case RADIO_BADNEWS:
 			{
 				if (!acHitIsFriend)
 					OtherSideKilled();
 				else
 					PlayerSideKilled();
 			}
 			break;
 			case RADIO_BLACKSMOKE:
 				BlackSmoke();
 				break;
 			case RADIO_FUELLEAK:
 				FuelLeak();
 				break;
 			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OtherSideDamageLevel1
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::OtherSideDamageLevel1()
{
	MinAnimData*	mad = (MinAnimData*) acHit->Anim;			//RJS 30Jun99
	if (	(Math_Lib.rnd() < VOX_RAND)							//RJS 30Jun99
		&&	(mad->itemstate == ALIVE)	)						//RJS 30Jun99
	{
		AirStrucPtr buddy=acHitter->FindABuddyWithPlayerGivenPriority();
		if (buddy)
		{
			if (!acHitter->AcIsPlayer())
			{
 				if (acHitter->ai.combatskill < SKILL_REGULAR)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE1LOW, MSG_DAMAGELEVEL1, acHitter, acHit, buddy));//RJS 23May99
 				else
 				{
 					if (acHitter->ai.combatskill < SKILL_HERO)			  //RDH 14/05/99
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE1MED, MSG_DAMAGELEVEL1, acHitter, acHit, buddy));
 					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE1HI, MSG_DAMAGELEVEL1, acHitter, acHit, buddy));
 				}
			}
			else
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE1HI, MSG_PLAYERDAMAGELEVEL1, acHitter, acHit, buddy));//RJS 24Jun99
		}
		else
		{
			if (acHitter->AcIsPlayer())
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE1HI, MSG_PLAYERDAMAGELEVEL1, acHitter, acHit, acHitter));//RJS 24Jun99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OtherSideDamageLevel2
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::OtherSideDamageLevel2()
{
	MinAnimData*	mad = (MinAnimData*) acHit->Anim;			//RJS 30Jun99
	if (	(Math_Lib.rnd() < VOX_RAND)							//RJS 30Jun99
		&&	(mad->itemstate == ALIVE)	)						//RJS 30Jun99
	{
		AirStrucPtr buddy=acHitter->FindABuddyWithPlayerGivenPriority();
		if (buddy)
		{
	//DeadCode DAW 25Jun99 		_Radio.ClearMessages(MSG_DAMAGELEVEL1,acHit);					//RJS 15Jun99
			_Radio.ClearMessages(MSG_DAMAGELEVEL1,acHit);			//RJS 24Jun99
			if (!acHitter->AcIsPlayer())
			{
 				if (acHitter->ai.combatskill < SKILL_REGULAR)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE2LOW, MSG_DAMAGELEVEL2, acHitter, acHit, buddy));
 				else
 				{
 					if (acHitter->ai.combatskill < SKILL_HERO)			  //RDH 14/05/99
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE2MED, MSG_DAMAGELEVEL2, acHitter, acHit, buddy));
 					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE2HI, MSG_DAMAGELEVEL2, acHitter, acHit, buddy));
 				}
			}
			else
			{
				_Radio.ClearMessages(MSG_PLAYERDAMAGELEVEL1,acHit);	//RJS 24Jun99
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE2HI, MSG_PLAYERDAMAGELEVEL2, acHitter, acHit, buddy));//RJS 24Jun99
			}
	//DeadCode DAW 25Jun99 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE2HI, MSG_DAMAGELEVEL2, acHitter, acHit, buddy));
		}
		else
		{
			if (acHitter->AcIsPlayer())
			{
				_Radio.ClearMessages(MSG_DAMAGELEVEL1,acHit);		//RJS 24Jun99
				_Radio.ClearMessages(MSG_PLAYERDAMAGELEVEL1,acHit);	//RJS 24Jun99
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE2HI, MSG_PLAYERDAMAGELEVEL2, acHitter, acHit, acHitter));//RJS 24Jun99
	//DeadCode DAW 25Jun99 			_Radio.ClearMessages(MSG_DAMAGELEVEL1,acHit);				//RJS 15Jun99
	//DeadCode DAW 25Jun99 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_OTHERDAMAGE2HI, MSG_DAMAGELEVEL2, acHitter, acHit, acHitter));//RJS 23May99
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayerSideDamageLevel1
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::PlayerSideDamageLevel1()
{
	MinAnimData*	mad = (MinAnimData*) acHit->Anim;			//RJS 30Jun99
	if (	(Math_Lib.rnd() < VOX_RAND)							//RJS 30Jun99
		&&	(mad->itemstate == ALIVE)	)						//RJS 30Jun99
	{
		AirStrucPtr buddy=acHit->FindABuddyWithPlayerGivenPriority();						//RDH 28Apr99
		if (buddy)
		{
 			if (acHit->ai.combatskill < SKILL_REGULAR)
 			{
				if (!acHit->AcIsPlayer())
				{
		 			ScriptTables	theScript;

	 				if ((acHit->ai.morale < MORALE_MEDIUM) && !acHit->InPlayersElement())
 						theScript = SCRIPT_CALLEE_PLAYERDAMAGE1COWARD;
 					else
 						theScript = SCRIPT_CALLEE_PLAYERDAMAGE1LOW;

	 				_Radio.TriggerMsg(MESSAGE_STRUC(theScript, MSG_DAMAGELEVEL1, acHit, acHit, buddy));
				}
 			}
 			else
 			{
 				if ((!acHit->AcIsPlayer()) && (Math_Lib.rnd()>48000))
 				{
					buddy = Persons2::PlayerSeenAC->FindBuddy();						//RJS 24Jun99
					if (buddy)
					{
 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE1CONV, MSG_DAMAGELEVEL1, buddy, acHit, acHit));
 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE1CONVREPLY, MSG_DAMAGELEVEL1REPLY, acHit,acHit,buddy));
					}
	//DeadCode DAW 25Jun99  				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE1CONV, MSG_DAMAGELEVEL1, acHit, acHit, buddy));
	//DeadCode DAW 25Jun99  				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE1CONVREPLY, MSG_DAMAGELEVEL1REPLY, buddy,acHit,acHit));
 				}
 				else
 				{
					if (!acHit->AcIsPlayer())
					{
 						if (acHit->ai.combatskill < SKILL_ACE)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE1MED, MSG_DAMAGELEVEL1, acHit, acHit, buddy));
 						else
						{
							ScriptTables script = SCRIPT_CALLEE_PLAYERDAMAGE1HI;
							if (acHit->classtype->phrasename != PHRASE_MIGS)		//RJS 06Jul99
								script = SCRIPT_CALLEE_PLAYERDAMAGE1HI_MIGS;
							_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_DAMAGELEVEL1, acHit, acHit, buddy));
						}
					}
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE1HI, MSG_PLAYERDAMAGELEVEL1, acHit, acHit, buddy));//RJS 24Jun99
	//DeadCode DAW 25Jun99 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE1HI, MSG_DAMAGELEVEL1, acHit, acHit, buddy));
 				}
 			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayerSideDamageLevel2
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::PlayerSideDamageLevel2()
{
	MinAnimData*	mad = (MinAnimData*) acHit->Anim;			//RJS 30Jun99
	AirStrucPtr buddy=acHit->FindABuddyWithPlayerGivenPriority();
	if (buddy)
	{
		if (!acHit->AcIsPlayer())
		{
 			ScriptTables	theScript;
 			Bool			haveTrigger = TRUE;
 			RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);		  //RDH 28/05/99


 			if (	(acHit->ai.morale < MORALE_GOOD)	&& (rndpc <  RND10PC))
			{
  				Art_Int.BreakOff(acHit);							  //RDH 06/06/99
				acHit->ai.morale = MORALE_ROCKBOTTOM;				  //RDH 28/05/99
				if (	(Math_Lib.rnd() < VOX_RAND)			//RJS 01Jul99
					&&	(mad->itemstate == ALIVE)	)		//RJS 01Jul99
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE2COWARD, MSG_DAMAGELEVEL2, acHit, acHit, buddy));
			}
 			else
 			{
 				if (acHit->ai.combatskill < SKILL_REGULAR)
				{
					if (	(Math_Lib.rnd() < VOX_RAND)			//RJS 01Jul99
						&&	(mad->itemstate == ALIVE)	)		//RJS 01Jul99
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE2LOW, MSG_DAMAGELEVEL2, acHit, acHit, buddy));
				}
 				else
 				{
 					UWord	voxchoice = Math_Lib.rnd();
 					if (!acHit->InPlayersElement() && (voxchoice >= 40000))				  //RJS 28Apr99
 					{
						if (	(Math_Lib.rnd() < VOX_RAND)			//RJS 01Jul99
							&&	(mad->itemstate == ALIVE)	)		//RJS 01Jul99
 							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_PLAYERDAMAGE2CONV0RR,MSG_DAMAGELEVEL2,acHit,acHit,buddy));

						//Eject...
						Trans_Obj.LaunchCanopyEject(acHit,*mobileitem::currworld);				//RJS 28Apr99
 					}
 					else
 					{
						if (	(Math_Lib.rnd() < VOX_RAND)			//RJS 01Jul99
							&&	(mad->itemstate == ALIVE)	)		//RJS 01Jul99
						{
 							if (acHit->ai.combatskill < SKILL_ACE)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE2MED, MSG_DAMAGELEVEL2, acHit, acHit, buddy));
 							else
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE2HI, MSG_DAMAGELEVEL2, acHit, acHit, buddy));
						}
 					}
 				}
 			}
		}
		else
		{
			if (	(Math_Lib.rnd() < VOX_RAND)			//RJS 01Jul99
				&&	(mad->itemstate == ALIVE)	)		//RJS 01Jul99
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_PLAYERDAMAGE2HI, MSG_PLAYERDAMAGELEVEL2, acHit, acHit, buddy));//RJS 24Jun99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FuelLeak
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::FuelLeak()
{
	if (!acHitter->AcIsPlayer())
	{
 		if (!acHitIsFriend)
 		{
			AirStrucPtr buddy=acHit->FindABuddyWithPlayerGivenPriority();
			if (buddy)
			{
//DEADCODE RDH 06/05/99   				if (acHitter->ai.combatskill < SKILL_REGULAR)
	 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GOTHIMLEAKING, MSG_DAMAGELEVEL2, acHitter, acHit, buddy));
//DEADCODE RDH 06/05/99   				else
//DEADCODE RDH 06/05/99  	 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GOTHIMLEAKING, MSG_DAMAGELEVEL2, acHitter, NULL, *acHitter->follower));
			}
 		}
 		else
 		{
 			if (acHit == leader)
 				LeaderLeaking();
 			else
 				FollowerLeaking();
 		}
	}
	else
	{
//DEADCODE RDH 09/05/99 		AirStrucPtr buddy=acHit->FindBuddy();
//DEADCODE RDH 09/05/99 		if (buddy)
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GOTHIMLEAKING, MSG_PLAYERLEAKING, acHitter, acHit, acHitter));
//DeadCode DAW 25Jun99 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GOTHIMLEAKING, (MsgType)(MSG_DAMAGELEVEL2+MSG_DELAY), acHitter, acHit, acHitter));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LeaderLeaking
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::LeaderLeaking()
{
 	if (buddy)
 	{
 		FuelLeakMsg(buddy);
 		if (buddy->ai.morale < MORALE_GOOD)
 		{
 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SEEFUEL, MSG_STATUSRESPONSE_X, buddy, acHit, acHit));//v2
 
 			EjectMsg(buddy);
 		}
 
 		if (!acHit->AcIsPlayer())
 		{
 			if (buddy->ai.morale < MORALE_GOOD)
 			{
 				//TakeOverGroup(THISISCALLER,???);
 				//Eject...;

				Trans_Obj.LaunchCanopyEject(acHit,*mobileitem::currworld);				//RJS 28Apr99
 			}
 			else
 			{
 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HAVELEAK, MSG_DAMAGELEVEL2, buddy, acHit, acHit));//v2
 
 				//TakeOverGroup(THISISCALLER,???);
 			}
 		}
 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FollowerLeaking
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::FollowerLeaking()
{
 	if (leader)
 	{
 		FuelLeakMsg(leader);
 		if (!leader->AcIsPlayer())
 		{
 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SEEFUEL, MSG_STATUSRESPONSE_X, buddy, acHit, acHit));
 			if (leader->ai.morale < MORALE_GOOD)
 				EjectMsg(leader);
 			else
 			{
 				//SendHome();
 
 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_USEORLOSE, MSG_DAMAGELEVEL2, buddy, acHit, acHit));
 			}
 		}
 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FuelLeakMsg
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::FuelLeakMsg(AirStrucPtr	recipient)
{
 	ScriptTables	theScript;
 
 	if ((acHit->ai.combatskill > SKILL_REGULAR) && (acHit->ai.morale > MORALE_MEDIUM))
 		theScript = SCRIPT_FUELLEAKMSG_CALLER;
 	else
 	{
 		if (acHit->ai.combatskill == SKILL_REGULAR)
 			theScript = SCRIPT_FUELLEAKMSG_CALLEE;
 		else
 			theScript = SCRIPT_FUELLEAKMSG;
 	}
 
 	_Radio.TriggerMsg(MESSAGE_STRUC(theScript, MSG_STATUSRESPONSE_X, acHit, acHit, recipient));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BlackSmoke
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::BlackSmoke()
{
 	if (acHitIsFriend)
 	{
 		if (acHit == leader)
 		{
 			if (buddy)
 			{
 				BlackSmokeMsg(buddy);
 				SmokingBadly(buddy);
 				if (!buddy->AcIsPlayer())
 					EjectMsg(buddy);
 
 				//if (acHit != Manual_Pilot.ControlledAC2)
 					//TakeOverGroup(THISISCALLER,???);
 			}
 		}
 		else
 		{
 			if (leader)
 			{
// 				BlackSmokeMsg(leader);
 				if (!leader->AcIsPlayer())
 				{
 					SmokingBadly(leader);
 					EjectMsg(leader);
 				}
 			}
 		}
 	}
 	else
 	{
 		ScriptTables	theScript;

		//Randomly say this if player is the killer...
		UWord			randchance = 0;									//RJS 25Jun99
		if (acHitter->AcIsPlayer())
			randchance = Math_Lib.rnd();
 
		if (randchance < 16384)
		{
			buddy = acHitter->FindABuddyWithPlayerGivenPriority();					//RJS 25May99
 			if (buddy)
 			{
 				if ((acHitter->ai.combatskill < SKILL_REGULAR) || (acHitter->ai.morale < MORALE_MEDIUM))
 					theScript = SCRIPT_ENEMYSMOKING;
 				else
 					theScript = SCRIPT_CALLEE_ENEMYSMOKING;
 
 				_Radio.TriggerMsg(MESSAGE_STRUC(theScript, (MsgType)(MSG_DAMAGELEVEL2+MSG_DELAY), acHitter, acHit, buddy));
 			}
			else
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ENEMYSMOKING, (MsgType)(MSG_DAMAGELEVEL2+MSG_DELAY), acHitter, acHit, acHitter));
		}
 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmokingBadly
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::SmokingBadly(AirStrucPtr	buddy)
{
	if (!buddy->AcIsPlayer())
	{
		if (Math_Lib.rnd() > 32768)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SMOKINGBADLY, MSG_DAMAGELEVEL2, buddy, acHit, acHit));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FIREINENGINE, MSG_DAMAGELEVEL2, buddy, acHit, acHit));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BlackSmokeMsg
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::BlackSmokeMsg(AirStrucPtr	buddy)
{
 	ScriptTables theScript = SCRIPT_NULL;
 
 	if (acHit->ai.morale < MORALE_GOOD)
 	{
 		if ((!acHit->AcIsPlayer()) && (Math_Lib.rnd() > 50000))
		{
 			theScript = SCRIPT_BURNINGUP;
		 	_Radio.TriggerMsg(MESSAGE_STRUC(theScript, MSG_DAMAGELEVEL2, acHit, acHit, buddy));
		}
 	}
 
 	if (theScript != SCRIPT_NULL)
	 	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SMOKE, MSG_DAMAGELEVEL2, acHit, acHit, buddy));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EjectMsg
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::EjectMsg(AirStrucPtr	caller)
{
	if (!caller->AcIsPlayer())									//RDH 14May99
	{
 		ScriptTables	theScript;
 
 		if ((caller->ai.combatskill > SKILL_REGULAR) && (caller->ai.morale > MORALE_MEDIUM))
 			theScript = SCRIPT_EJECT_CALLER;
 		else
 		{
 			if (caller->ai.morale == MORALE_MEDIUM)
 				theScript = SCRIPT_EJECT_CALLEE;
 			else
 				theScript = SCRIPT_EJECT;
 		}
 
 		_Radio.TriggerMsg(MESSAGE_STRUC(theScript, MSG_DAMAGELEVEL2REPLY, caller, acHit, acHit));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayerSideKilled
//Author		R. Hyde 
//Date			Thu 29 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::PlayerSideKilled()
{
	if (Math_Lib.rnd() < VOX_RAND)							//RJS 30Jun99
	{
		buddy = acHit->FindABuddyWithPlayerGivenPriority();
		if (buddy)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERKILLED,MSG_KILLREPORT, acHit, acHit, buddy));//RDH 18May99
	}

	if (!acHit->AcIsPlayer())
		Trans_Obj.LaunchCanopyEject(acHit,*mobileitem::currworld);				//RJS 28Apr99

	if (!acHit->uniqueID.commsmove)									  //AMM 07/07/99
		acHit->ai.radiosilent = TRUE;			//RJS 09Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OtherSideKilled
//Author		R. Hyde 
//Date			Thu 29 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::OtherSideKilled()
{
	if (Math_Lib.rnd() < VOX_RAND)							//RJS 30Jun99
	{
		buddy = acHitter->FindABuddyWithPlayerGivenPriority();
		if (buddy)
		{
			_Radio.ClearMessages(MSG_DAMAGELEVEL2,acHit);					//RJS 15Jun99
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERKILLED,MSG_KILLREPORT, acHitter, acHit, buddy));//RDH 18May99
		}
		else
		{
			if (acHitter->AcIsPlayer())
			{
				_Radio.ClearMessages(MSG_DAMAGELEVEL2,acHit);				//RJS 15Jun99
				_Radio.ClearMessages(MSG_PLAYERDAMAGELEVEL2,acHit);	//RJS 24Jun99
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERKILLED,MSG_PLAYERKILLREPORT, acHitter, acHit, acHitter));//RJS 24Jun99
	//DeadCode DAW 25Jun99 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERKILLED,MSG_KILLREPORT, acHitter, acHit, acHitter));//RDH 18May99
			}
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayerSideBlewUp
//Author		R. Hyde 
//Date			Thu 29 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::PlayerSideBlewUp(AirStrucPtr	ac)
{
	if (ac->AcIsPlayer())										//RJS 01Jul99
	{
		ac->ai.radiosilent = FALSE;			//RJS 09Jun99
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERBLEWUP, (MsgType)(MSG_BLOWUPREPORT+MSG_HIPRIORITY), ac, ac, NULL));//RJS 24Jun99
	}
	else
	{
		if (Math_Lib.rnd() < VOX_RAND)							//RJS 01Jul99
		{
			buddy = ac->FindAcInGroup();
			if (buddy)
			{
				if (ac->PlayerInGroup())
				{
					if (!buddy->AcIsPlayer())
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_PLYRSIDEKILLED0, MSG_BLOWUPREPORT, buddy, ac, Manual_Pilot.ControlledAC2));
				}else
				{
					AirStruc*	lead = ((AirStruc*) buddy->leader);
						if (		(lead)
							&&	(lead->fly.leadflight)	
							&&	(lead->fly.leadflight != ac)	
						)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_PLYRSIDEKILLED0, MSG_BLOWUPREPORT, buddy, ac,lead ));
				}
			}
		}
	}
	if (!ac->uniqueID.commsmove)									  //AMM 07/07/99
		ac->ai.radiosilent = TRUE;			//RJS 09Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OtherSideBlewUp
//Author		R. Hyde 
//Date			Thu 29 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::OtherSideBlewUp(AirStrucPtr	ac,AirStrucPtr	acDead,bool	migdead)
{
	if (ac)														//DAW 01Jun99
	{
		if (ac != acDead)
		{
			AlertGoHome(ac);

			if (Math_Lib.rnd() < VOX_RAND)						//RJS 01Jul99
			{
				if (!ac->AcIsPlayer())
				{
					buddy = ac->FindABuddyWithPlayerGivenPriority();
					if (buddy)
					{
						if (ac->ai.combatskill < SKILL_REGULAR)
						{
							_Radio.ClearMessages(MSG_DAMAGELEVEL2,acDead);			//RJS 15Jun99
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_BOASTKILL,MSG_BLOWUPREPORT, ac, acDead, buddy));//RDH 18May99

							if ((Math_Lib.rnd() > 32000) && (!buddy->AcIsPlayer()))
							{
								ScriptTables script = SCRIPT_BOASTKILLREPLY;
								if (ac->classtype->phrasename != PHRASE_MIGS)
									script = SCRIPT_BOASTKILLREPLY_MIGS;

								_Radio.TriggerMsg(MESSAGE_STRUC(script,MSG_BLOWUPREPORTREPLY, buddy, acDead, ac));//RDH 18May99
							}
						}
						else
						{
							if (ac->ai.combatskill < SKILL_ACE)
							{
								_Radio.ClearMessages(MSG_DAMAGELEVEL2,acDead);		//RJS 15Jun99
								if (migdead)
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERSIDEBLEW_MIGS,MSG_BLOWUPREPORT, ac, acDead, buddy));//RDH 18May99
								else
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERSIDEBLEW,MSG_BLOWUPREPORT, ac, acDead, buddy));//RDH 18May99
							}else
							{
								buddy = ac->FindABuddyNotPlayer();
								if ((!buddy) || (Math_Lib.rnd() > 32000))
								{
									_Radio.ClearMessages(MSG_DAMAGELEVEL2,acDead);		//RJS 15Jun99
									if (migdead)
										_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERSIDEBLEWHIMIG,MSG_BLOWUPREPORT, ac, acDead, buddy));//RDH 18May99
									else
										_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERSIDEBLEWHI,MSG_BLOWUPREPORT, ac, acDead, buddy));//RDH 18May99

									if (!buddy->AcIsPlayer())
										_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_ROGER2,(MsgType)(MSG_BLOWUPREPORTREPLY+MSG_BLOCKCHATTER), buddy, acDead, ac));//RJS 06Jul99
								}
								else
								{
									_Radio.ClearMessages(MSG_DAMAGELEVEL2,acDead);		//RJS 15Jun99
									if (migdead)
										_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERSIDEBLEWHI2,MSG_BLOWUPREPORT, buddy, acDead, ac));//RDH 18May99
									else
										_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERSIDEBLEWHI2_OPT_0,MSG_BLOWUPREPORT, buddy, acDead, ac));//RDH 18May99
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ROGER,(MsgType)(MSG_BLOWUPREPORTREPLY+MSG_BLOCKCHATTER), ac, acDead, buddy));//RJS 06Jul99
								}
							}
						}
					}
				}		 
				else
				{
					//Don't want to hear 'Splash one' all the time, cos it's annoying
//DeadCode RJS 01Jul99 					if (Math_Lib.rnd() > 49152)
//DeadCode RJS 01Jul99 					{
						_Radio.ClearMessages(MSG_DAMAGELEVEL2,acDead);				//RJS 15Jun99
						_Radio.ClearMessages(MSG_PLAYERDAMAGELEVEL2,acDead);//RJS 24Jun99
						buddy = ac->FindBuddy();
						if (buddy)
						{
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERSIDEBLEWHI,MSG_PLAYERBLOWUPREPORT, ac, acDead, buddy));
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ROGER,(MsgType)(MSG_BLOWUPREPORTREPLY+MSG_BLOCKCHATTER), buddy, acDead, ac));//RJS 06Jul99
						}
						else
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OTHERSIDEBLEWHI,MSG_PLAYERBLOWUPREPORT, ac, acDead, ac));
//DeadCode RJS 01Jul99 					}
				}
			}
		}
		else
		{
			if (acDead->lasthitter.count)
			{
				ItemPtr	lasthitter = (ItemPtr)Persons2::ConvertPtrUID((UniqueID)acDead->lasthitter.count);
				if (lasthitter && (lasthitter->Status.size == AIRSTRUCSIZE))
					OtherSideBlewUp((AirStrucPtr)lasthitter,acDead,migdead);
			}
		}
	}

	if (!acDead->uniqueID.commsmove)								  //AMM 07/07/99
		acDead->ai.radiosilent = TRUE;			//RJS 09Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayerSidePiledIn
//Author		R. Hyde 
//Date			Thu 29 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::PlayerSidePiledIn(AirStrucPtr	ac)
{
	if (ac)
	{
		if (Math_Lib.rnd() < VOX_RAND)							//RJS 01Jul99
		{
			if (ac->AcIsPlayer())
			{
				buddy = ac->FindBuddy();
				if (buddy)
				{
					if (Math_Lib.rnd() > 32767)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEPILEDINREP,MSG_BLOWUPREPORT, buddy, ac, ac));
					else
 					{
 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PILEDIN,MSG_BLOWUPREPORT, buddy, ac, ac));
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PILEDINREP,MSG_BLOWUPREPORTREPLY, buddy, ac, ac));
 					}
				}
			}
			else
			{
				if (ac->PlayerInGroup())
				{
					buddy = Manual_Pilot.ControlledAC2->FindBuddy();
					if (buddy && (buddy != ac))
					{
						if (Math_Lib.rnd() > 32767)
	 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PILEDIN,MSG_BLOWUPREPORT,buddy,ac,Manual_Pilot.ControlledAC2));
						else
						{
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WHEREIS,MSG_BLOWUPREPORT,Manual_Pilot.ControlledAC2,ac,buddy));
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEPILEDINREP,MSG_BLOWUPREPORTREPLY, buddy, ac, Manual_Pilot.ControlledAC2));
						}
					}
				}
			}
		}
	}

	if (!ac->uniqueID.commsmove)									  //AMM 07/07/99
		ac->ai.radiosilent = TRUE;			//RJS 09Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SayWeapon
//Author		Robert Slater
//Date			Thu 13 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::SayWeapon(SLong	index)
{
	SLong	theScript = PHRASE_NOTHING;

	switch (index & LT_MASK)
	{
	case LT_BULLET:
		theScript = PHRASE_GUNS;
	break;
	case LT_BOMB:
	{
		if (index == LT_NAPALM)
			theScript = PHRASE_NAPALM;
		else
			theScript = PHRASE_BOMBS;
	}
	break;
	case LT_ROCKET:
		theScript = PHRASE_ROCKETS;
	break;
	}

	_Radio.TriggerMsg(MESSAGE_STRUC(theScript,MSG_HIPRIORITY,Manual_Pilot.ControlledAC2,NULL,NULL));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AlertGoHome
//Author		Robert Slater
//Date			Mon 24 May 1999
//
//Description	Tell everyone to bugger off if there are no bandits left to kill.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DamageChat::AlertGoHome(AirStrucPtr	killer)
{
	int	bandcnt = 0;

	killer->FindBandit(bandcnt);
	if (!bandcnt)
	{
		AirStrucPtr	theLeader = killer->GroupLeader();
		if (theLeader)
		{
			AirStrucPtr	buddy = theLeader->FindABuddyWithPlayerGivenPriority();
			if (buddy)
			{
				int	theScript;
				if (Math_Lib.rnd() > 32767)
					theScript = SCRIPT_ALLDISENGAGE;
				else
					theScript = SCRIPT_ALLGOHOME;

				_Radio.TriggerMsg(MESSAGE_STRUC(theScript,MSG_NOBANDITCALL_X,theLeader,buddy,buddy));
			}
		}
	}
}
