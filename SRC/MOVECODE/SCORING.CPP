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
//Filename       scoring.cpp
//System         
//Author         R. Hyde 
//Date           Mon 9 Sep 1996
//Description    
//------------------------------------------------------------------------------
#include	"dosdefs.h"
#include	"world.h"
#include	"worldinc.h"
#include	"flymodel.h"
#include 	"ui.h"
#include	"transite.h"
#include	"mymath.h"
#include	"mytime.h"
#include	"maps.h"
#include	"ai.h"
#include "persons2.h"											//RDH 24Jul96

MATHABLE	(SkillType);
MATHABLE	(MoraleType);


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IncSkill
//Author		R. Hyde 
//Date			Mon 9 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SkillType AirStruc::IncSkill (AirStrucPtr ac,SWord aircraft_no)
{
	return ((SkillType)
		(Math_Lib.rnd((SKILL_HERO - MMC.Temp_Pilots[aircraft_no].skill) * ac->ai.morale)/MORALE_TOPMORALE));//RDH 04Dec96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModIfyPilotMorale
//Author		R. Hyde 
//Date			Mon 9 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::ModifyPilotMorale(SWord i, MoraleType moralestep)
{
	if (	(MMC.Temp_Pilots[i].morale + moralestep) > MORALE_TOPMORALE)
	{
		MMC.Temp_Pilots[i].morale = MORALE_TOPMORALE;
	}elseif	(	(MMC.Temp_Pilots[i].morale + moralestep) < MORALE_ROCKBOTTOM)
	{
		MMC.Temp_Pilots[i].morale = MORALE_ROCKBOTTOM;
	}else
	{
		MMC.Temp_Pilots[i].morale += moralestep;
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModIfyPlayerMerit
//Author		R. Hyde 
//Date			Mon 9 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::ModifyPlayerMerit(DeltaMeritType meritstep)
{
//DeadCode RDH 17Feb97 	if (	((SLong) (Miss_Man.camp.playermerit + (MeritType) meritstep))
//DeadCode RDH 17Feb97 				> ((SLong) MERIT_IMPOSSIBLE))
//DeadCode RDH 17Feb97 	{
//DeadCode RDH 17Feb97 		Miss_Man.camp.playermerit = MERIT_TOP;
//DeadCode RDH 17Feb97 	}elseif	(	(Miss_Man.camp.playermerit + (MeritType) meritstep)
//DeadCode RDH 17Feb97 					< MERIT_ROCKBOTTOM)
//DeadCode RDH 17Feb97 	{
//DeadCode RDH 17Feb97 		Miss_Man.camp.playermerit = MERIT_ROCKBOTTOM;
//DeadCode RDH 17Feb97 	}else
//DeadCode RDH 17Feb97 	{
//DeadCode RDH 17Feb97 		Miss_Man.camp.playermerit = Miss_Man.camp.playermerit + (MeritType) meritstep;
//DeadCode RDH 17Feb97 	}

}

//DeadCode RDH 19Mar97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 19Mar97 //Procedure		ModIfySquadronMorale
//DeadCode RDH 19Mar97 //Author		R. Hyde 
//DeadCode RDH 19Mar97 //Date			Mon 9 Sep 1996
//DeadCode RDH 19Mar97 //
//DeadCode RDH 19Mar97 //Description	
//DeadCode RDH 19Mar97 //
//DeadCode RDH 19Mar97 //Inputs		
//DeadCode RDH 19Mar97 //
//DeadCode RDH 19Mar97 //Returns	
//DeadCode RDH 19Mar97 //
//DeadCode RDH 19Mar97 //------------------------------------------------------------------------------
//DeadCode RDH 19Mar97 static	void AirStruc::ModifySquadronMorale(MoraleType moralestep)
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 {
//DeadCode RDH 17Feb97 	for (SWord i =0;i < MMC.Temp_Squadron.pilotsperflight;i++)
//DeadCode RDH 17Feb97 	{
//DeadCode RDH 17Feb97 		for (SWord j =0;j <Miss_Man.camp.squad.flightnum[i];j++)
//DeadCode RDH 17Feb97 			ModifyPilotMorale(j+MMC.Temp_Squadron.pilotsperflight * i,moralestep);
//DeadCode RDH 17Feb97 	}
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 }
//DeadCode RDH 13Mar97 
//DeadCode RDH 13Mar97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 13Mar97 //Procedure		PlayerDecision
//DeadCode RDH 13Mar97 //Author		R. Hyde 
//DeadCode RDH 13Mar97 //Date			Mon 9 Sep 1996
//DeadCode RDH 13Mar97 //
//DeadCode RDH 13Mar97 //Description	
//DeadCode RDH 13Mar97 //
//DeadCode RDH 13Mar97 //Inputs		
//DeadCode RDH 13Mar97 //
//DeadCode RDH 13Mar97 //Returns	
//DeadCode RDH 13Mar97 //
//DeadCode RDH 13Mar97 //------------------------------------------------------------------------------
//DeadCode RDH 13Mar97 static	void AirStruc::PlayerDecision ()
//DeadCode RDH 13Mar97 {
//DeadCode RDH 13Mar97 	if (MMC.specialeventbits[PLAYER_ENGAGES_SHOULD])
//DeadCode RDH 13Mar97 		ModifySquadronMorale(MORALE_HALFSTAGE);
//DeadCode RDH 13Mar97 	if (MMC.specialeventbits[PLAYER_ENGAGES_SHOULDNOT])
//DeadCode RDH 13Mar97 		ModifySquadronMorale(MORALE_MINUSHALFSTAGE);
//DeadCode RDH 13Mar97 	if (MMC.specialeventbits[PLAYER_NOTENGAGE_SHOULD])
//DeadCode RDH 13Mar97 		ModifySquadronMorale(MORALE_MINUSHALFSTAGE);
//DeadCode RDH 13Mar97 	if (MMC.specialeventbits[PLAYER_NOTENGAGE_SHOULDNOT])
//DeadCode RDH 13Mar97 		ModifySquadronMorale(MORALE_HALFSTAGE);
//DeadCode RDH 13Mar97 }
//DeadCode RDH 13Mar97 
//DeadCode RDH 19Mar97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 19Mar97 //Procedure		PrelimACtivePilotChk
//DeadCode RDH 19Mar97 //Author		R. Hyde 
//DeadCode RDH 19Mar97 //Date			Mon 29 Jan 1996
//DeadCode RDH 19Mar97 //
//DeadCode RDH 19Mar97 //Description	
//DeadCode RDH 19Mar97 //
//DeadCode RDH 19Mar97 //Inputs		
//DeadCode RDH 19Mar97 //
//DeadCode RDH 19Mar97 //Returns	
//DeadCode RDH 19Mar97 //
//DeadCode RDH 19Mar97 //------------------------------------------------------------------------------
//DeadCode RDH 19Mar97 static	void AirStruc::PrelimActivePilotChk ()
//DeadCode RDH 19Mar97 {
//DeadCode RDH 19Mar97 	SWord	notactive =0,i;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 	for (i=0;i<PILOTS_PER_SQUADRON;i++)
//DeadCode RDH 19Mar97 	{
//DeadCode RDH 19Mar97 		if (i != Miss_Man.camp.currentplayerslot)
//DeadCode RDH 19Mar97 		{
//DeadCode RDH 19Mar97 			if (MMC.Temp_Pilots [i].daystorecover != 0)
//DeadCode RDH 19Mar97 			{
//DeadCode RDH 19Mar97 				notactive++;
//DeadCode RDH 19Mar97 			}
//DeadCode RDH 19Mar97 		}
//DeadCode RDH 19Mar97 	}
//DeadCode RDH 19Mar97 	if (notactive > Miss_Man.camp.reservesavail)
//DeadCode RDH 19Mar97 	{
//DeadCode RDH 19Mar97 		MMC.specialeventbits |= RESERVEEXHAUSTED;
//DeadCode RDH 19Mar97 	}
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 }
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EndGameScoring
//Author		R. Hyde 
//Date			Sun 8 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//Other Factors:	death of leader or buddy
//
//
//
//
//------------------------------------------------------------------------------
void	AirStruc::EndGameScoring()
{
//DeadCode RDH 19Mar97 	SWord	blueacdead;
//DeadCode RDH 19Mar97 	UniqueID	tmpUID;
//DeadCode RDH 19Mar97 	UniqueID	EndBand;
//DeadCode RDH 19Mar97 	ItemBasePtr		tmpitem;
//DeadCode RDH 19Mar97 	Bool	tankalive = FALSE;
//DeadCode RDH 19Mar97 	AirStrucPtr		hitter;
//DeadCode RDH 19Mar97 	SWord	i;
//DeadCode RDH 19Mar97 	AirStrucPtr	currac;
//DeadCode RDH 19Mar97 	Bool	enemyhit = FALSE;
//DeadCode RDH 19Mar97 	SWord	aircraft_no,hitter_no;
//DeadCode RDH 19Mar97 	currac = (AirStrucPtr) ACList;
//DeadCode RDH 19Mar97 	AircraftAnimData*	adptr;
//DeadCode RDH 19Mar97 //DeadCode RDH 09Sep96 	adptr = (AircraftAnimData *)Anim;
//DeadCode RDH 19Mar97 //DeadCode RDH 13Oct96 	Bool	tmp = FALSE;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 //code required for
//DeadCode RDH 19Mar97 //				MMC.specialeventbits |= FRIENDLYDESTROYEDTARGET;//JIM 05Dec96
//DeadCode RDH 19Mar97 //				MMC.specialeventbits |= ENEMYDESTROYEDTARGET;	//JIM 05Dec96
//DeadCode RDH 19Mar97 //				MMC.specialeventbits |= HOMEBASEDESTROYED;		//JIM 05Dec96
//DeadCode RDH 19Mar97 //DUMPING THESE
//DeadCode RDH 19Mar97 //				MMC.specialeventbits[PLAYER_ENGAGES_SHOULD])
//DeadCode RDH 19Mar97 //				MMC.specialeventbits[PLAYER_ENGAGES_SHOULDNOT])
//DeadCode RDH 19Mar97 //				MMC.specialeventbits[PLAYER_NOTENGAGE_SHOULD])
//DeadCode RDH 19Mar97 //				MMC.specialeventbits[PLAYER_NOTENGAGE_SHOULDNOT])
//DeadCode RDH 19Mar97 //
//DeadCode RDH 19Mar97 //merit for killing ground items, used in SO for increasing merit on last mission
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 //DeadCode RDH 01Dec96 	MMC.specialeventbits = 0;									//RDH 23Nov96
//DeadCode RDH 19Mar97 //DeadCode RDH 01Dec96 	MMC.newsevent = 0;											//RDH 23Nov96
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 	if (	(Miss_Man.currcampaignnum == Miss_Man.INTROCAMPAIGN)	//RDH 08Dec96
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 		&&	(Miss_Man.camp.currmission->missiondate == APR25th1918)//RDH 08Dec96
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 		)
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 	{
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 		tmpUID = RedSAMBAND;
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 		EndBand = BlueSAMBAND;
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 		while (tmpUID < EndBand)
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 		{
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 			tmpitem=Persons_2.ConvertPtrUID(tmpUID);
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 			if 	(tmpitem!=NULL)
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 			{
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 				if (Persons_2.ItemStatus(tmpUID).deadtime == 0)
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 						tankalive = TRUE;
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 			}
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 			tmpUID++;
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 		}
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 		if (tankalive == FALSE)
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 			MMC.specialeventbits |= SO_WON;
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 		else
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 			MMC.specialeventbits |= SO_LOST;
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 	}															//RDH 08Dec96
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 	if (Miss_Man.currcampaignnum == Miss_Man.SO51_CAMPAIGN)	//RDH 27Sep96
//DeadCode RDH 19Mar97 	{
//DeadCode RDH 19Mar97 		//if aaa site dead then associated gun goes back to being dead
//DeadCode RDH 19Mar97 		//clear blueaaa list entry
//DeadCode RDH 19Mar97 		for (i =0;i<MAXGUNS;i++)
//DeadCode RDH 19Mar97 		{
//DeadCode RDH 19Mar97 			if (Persons_2.ItemStatus(Miss_Man.camp.blueaaa[i]).deadtime != 0)
//DeadCode RDH 19Mar97 			{	
//DeadCode RDH 19Mar97 				Miss_Man.camp.blueguns[i] = UID_Null;
//DeadCode RDH 19Mar97 			}
//DeadCode RDH 19Mar97 			Miss_Man.camp.blueaaa[i] = UID_Null;	
//DeadCode RDH 19Mar97 		}
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 		//deal with blue ac
//DeadCode RDH 19Mar97 		if (Persons_2.ItemStatus(UID_AlAfHermies).deadtime != 0)	//JIM 11Oct96
//DeadCode RDH 19Mar97 			MMC.blueacflying = -1;
//DeadCode RDH 19Mar97 		if (MMC.blueacflying < 4)								//JIM 13Dec96
//DeadCode RDH 19Mar97 			MMC.blueacflying++;									//JIM 13Dec96
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 		MMC.blueacflying++;
//DeadCode RDH 19Mar97 		if (MMC.blueacflying > 8)
//DeadCode RDH 19Mar97 			MMC.blueacflying = 8;
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 		//null wp that were no dead tanks
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 		for (i=0;i<(MAXTNKWPINROUTE);i++)
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 		{
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 			if (Persons_2.ItemStatus(MMC.tankcampwp[i].target_uid).deadtime != 0)
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 			{
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 				MMC.tankcampwp[i].target_uid = UID_Null;
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 				MMC.tankcampwp[i].mapx = WPICONW/2;
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 				MMC.tankcampwp[i].mapy = WPICONH/2-MAPICONSIZE;
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 			}
//DeadCode RDH 19Mar97 //DeadCode RDH 15Oct96 		}
//DeadCode RDH 19Mar97 		//generaltidy that is also done on exitting map
//DeadCode RDH 19Mar97 		Persons_2.TankEndMission ();
//DeadCode RDH 19Mar97 		Persons_2.LaunchTankConvoy();
//DeadCode RDH 19Mar97 		Persons_2.LaunchTruckConvoyTest();
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 	}
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 	if (Manual_Pilot.ControlledAC2->ai.homebase->Status.deadtime)
//DeadCode RDH 19Mar97 		MMC.specialeventbits |= HOMEBASEDESTROYED;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 //DeadCode RDH 13Mar97 	PlayerDecision ();
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 	if ( MMC.specialeventbits[FRIENDLYDESTROYEDTARGET])
//DeadCode RDH 19Mar97 	{															//RDH 08Dec96
//DeadCode RDH 19Mar97 		if (Miss_Man.camp.currmission->missiontext == TEXT_HATBEATUPFIELD)//RDH 08Dec96
//DeadCode RDH 19Mar97 		{														//RDH 08Dec96
//DeadCode RDH 19Mar97 			ModifyPlayerMerit(MERIT_VIS_MSN_SUCCESS);			//RDH 08Dec96
//DeadCode RDH 19Mar97 			ModifySquadronMorale(MORALE_STAGE);						//MS 13Dec96
//DeadCode RDH 19Mar97 		}else													//RDH 08Dec96
//DeadCode RDH 19Mar97 		{														//RDH 08Dec96
//DeadCode RDH 19Mar97 			ModifyPlayerMerit(MERIT_TARGET_DESTROYED);			//RDH 08Dec96
//DeadCode RDH 19Mar97 		}														//RDH 08Dec96
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 	}
//DeadCode RDH 19Mar97 	if ( MMC.specialeventbits[ENEMYDESTROYEDTARGET])
//DeadCode RDH 19Mar97 	{
//DeadCode RDH 19Mar97 		ModifyPlayerMerit((DeltaMeritType)-MERIT_TARGET_DESTROYED);
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 		if (Miss_Man.camp.currmission->missiontext == TEXT_CRCSINTERCEPTUNESCORTED_B)//MS 13Dec96
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 			ModifySquadronMorale(MORALE_MINUSHALFSTAGE);
//DeadCode RDH 19Mar97 	}
//DeadCode RDH 19Mar97 	if  (	(!(MMC.specialeventbits[ENEMYDESTROYEDTARGET]))		//MS 13Dec96
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 		&& (Miss_Man.camp.currmission->missiontext == TEXT_CRCSINTERCEPTUNESCORTED_B)//MS 13Dec96
//DeadCode RDH 19Mar97 		)														//MS 13Dec96
//DeadCode RDH 19Mar97 		{														//MS 13Dec96
//DeadCode RDH 19Mar97 			ModifyPlayerMerit(MERIT_VIS_MSN_SUCCESS);			//MS 13Dec96
//DeadCode RDH 19Mar97 			ModifySquadronMorale(MORALE_STAGE);					//MS 13Dec96
//DeadCode RDH 19Mar97 		}														//MS 13Dec96
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96   while (currac)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96   {
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 	adptr = (AircraftAnimData *)currac->Anim;
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96  	if ( Art_Int.SameFlight(currac,Manual_Pilot.ControlledAC2)) 			//(aircraft in player squadron)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 	{
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 		aircraft_no = (currac->formpos&InWingMAX) +
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				(currac->formpos&InFormMAX) * Miss_Man.camp.squad.pilotsperflight;
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 		MMC.Temp_Pilots[aircraft_no].skill += IncSkill (currac);
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 		MMC.Temp_Pilots[aircraft_no].morale = (MoraleType) currac->ai.morale;
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 
//DeadCode RDH 19Mar97 //TempCode RDH 11Oct96 		if (tmp)	
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 		if (adptr->lasthitter.count != UID_Null)			//(aircraft hit)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 		{
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				if (currac->Status.deadtime != 0)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				{
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 					if (aircraft_no == Miss_Man.camp.currentplayerslot)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						MMC.specialeventbits |= PLAYERKILLED;
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 					else
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						MMC.Temp_Pilots [aircraft_no].daystorecover = -1;
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				}elseif  (	(adptr->dammageflags && 0xaaaa)		//binary 1010 1010 1010 1010
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						||	(adptr->damageflags2 && 0xaaaa)		//binary 1010 1010 1010 1010
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				{
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						MMC.Temp_Pilots [aircraft_no].daystorecover = Math_Lib.rnd(6);
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						ModifyPilotMorale(aircraft_no, -MORALE_STAGE);
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						if (aircraft_no == Miss_Man.camp.currentplayerslot)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 							MMC.specialeventbits |= PLAYERWOUNDED;
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				}elseif  (	(adptr->dammageflags && 0x5555)		
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						||	(adptr->damageflags2 && 0x5555)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				{
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						MMC.Temp_Pilots [aircraft_no].daystorecover = Math_Lib.rnd(3);
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						ModifyPilotMorale(aircraft_no, (MoraleType)-(MORALE_STAGE/2));
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				}else
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				{
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						ModifyPilotMorale(aircraft_no, (MoraleType)-(MORALE_STAGE/4));
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				}
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				hitter = (AirStrucPtr) (Persons_2.ConvertPtrUID(adptr->lasthitter.count));
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				if (hitter->nationality == currac->nationality)
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				{
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 						ModifyPilotMorale(hitter_no, (MoraleType) (-(hitter->ai.skill * 2)));
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 				}
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 		}else
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 		{
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 		 		ModifyPilotMorale(aircraft_no, MORALE_STAGE);
//DeadCode RDH 19Mar97 //DeadCode RDH 24Oct96 		}
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97   while (currac)												//RDH 11Dec96
//DeadCode RDH 19Mar97   {
//DeadCode RDH 19Mar97 	adptr = (AircraftAnimData *)currac->Anim;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 //DeadCode RJS 11Feb97 	if (adptr->lasthitter.count != UID_Null)			//(aircraft hit)
//DeadCode RDH 19Mar97 	if (currac->lasthitter.count != UID_Null)	//(Aircraft Hit)//RJS 11Feb97
//DeadCode RDH 19Mar97 	{
//DeadCode RDH 19Mar97 //DeadCode RJS 11Feb97 		hitter = (AirStrucPtr)(Persons_2.ConvertPtrUID(adptr->lasthitter.count));
//DeadCode RDH 19Mar97 		hitter = (AirStrucPtr)(Persons_2.ConvertPtrUID(currac->lasthitter.count));//RJS 11Feb97
//DeadCode RDH 19Mar97 		if ( Art_Int.SameFlight(hitter,Manual_Pilot.ControlledAC2))
//DeadCode RDH 19Mar97 		{
//DeadCode RDH 19Mar97 			if (	(currac->Status.deadtime != 0)
//DeadCode RDH 19Mar97 				||	(adptr->dammageflags & 0x5555)
//DeadCode RDH 19Mar97 				||	(adptr->damageflags2 & 0x5555)
//DeadCode RDH 19Mar97 				)
//DeadCode RDH 19Mar97 			{
//DeadCode RDH 19Mar97 				enemyhit = TRUE;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 			}
//DeadCode RDH 19Mar97 		}
//DeadCode RDH 19Mar97   	}
//DeadCode RDH 19Mar97 	currac = (AirStrucPtr) currac->nextmobile;
//DeadCode RDH 19Mar97  }																//RDH 11Dec96
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97   currac = (AirStrucPtr) ACList;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97   blueacdead = 0;												//JIM 13Dec96
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97   while (currac)
//DeadCode RDH 19Mar97   {
//DeadCode RDH 19Mar97 	adptr = (AircraftAnimData *)currac->Anim;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97  	if ( Art_Int.SameFlight(currac,Manual_Pilot.ControlledAC2)) 			//(aircraft in player squadron)
//DeadCode RDH 19Mar97 	{
//DeadCode RDH 19Mar97 //DeadCode RDH 12Dec96 		aircraft_no = (currac->formpos&InWingMAX) +
//DeadCode RDH 19Mar97 //DeadCode RDH 12Dec96  				(currac->formpos&InFormMAX) * Miss_Man.camp.squad.pilotsperflight;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 		aircraft_no = (currac->fly.originalformpos&InWingMAX) +	//RDH 12Dec96
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97  				(currac->fly.originalformpos&InFormMAX) * Miss_Man.camp.squad[0].pilotsperflight;//RDH 17Feb97
//DeadCode RDH 19Mar97  				(currac->fly.originalformpos&InFormMAX) * 4;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 		MMC.Temp_Pilots[aircraft_no].skill += IncSkill (currac,aircraft_no);
//DeadCode RDH 19Mar97 		if (MMC.Temp_Pilots[aircraft_no].skill > SKILL_HERO)	//RDH 29Nov96
//DeadCode RDH 19Mar97 			MMC.Temp_Pilots[aircraft_no].skill = SKILL_HERO;	//RDH 29Nov96
//DeadCode RDH 19Mar97 		MMC.Temp_Pilots[aircraft_no].morale = (MoraleType) currac->ai.morale;
//DeadCode RDH 19Mar97 		if (MMC.Temp_Pilots[aircraft_no].morale > MORALE_TOPMORALE)//RDH 29Nov96
//DeadCode RDH 19Mar97 			MMC.Temp_Pilots[aircraft_no].morale = MORALE_TOPMORALE;//RDH 29Nov96
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 		if (currac->Status.deadtime != 0)
//DeadCode RDH 19Mar97 		{
//DeadCode RDH 19Mar97 			if (aircraft_no == Miss_Man.camp.currentplayerslot)
//DeadCode RDH 19Mar97 			{
//DeadCode RDH 19Mar97 				assert(Manual_Pilot.ControlledAC2 == currac);	//RDH 12Dec96
//DeadCode RDH 19Mar97 				MMC.specialeventbits |= PLAYERKILLED;
//DeadCode RDH 19Mar97 			}
//DeadCode RDH 19Mar97 			else
//DeadCode RDH 19Mar97 				MMC.Temp_Pilots [aircraft_no].daystorecover = -1;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 		}elseif  (	(adptr->dammageflags & 0xaaaa)		//binary 1010 1010 1010 1010//RDH 14Nov96
//DeadCode RDH 19Mar97 				||	(adptr->damageflags2 & 0xaaaa)		//binary 1010 1010 1010 1010//RDH 14Nov96
//DeadCode RDH 19Mar97 				)
//DeadCode RDH 19Mar97 		{
//DeadCode RDH 19Mar97 //DeadCode RDH 19Nov96 			MMC.Temp_Pilots [aircraft_no].daystorecover = Math_Lib.rnd(6);
//DeadCode RDH 19Mar97 			ModifyPilotMorale(aircraft_no, -MORALE_STAGE);
//DeadCode RDH 19Mar97 			if (aircraft_no == Miss_Man.camp.currentplayerslot)
//DeadCode RDH 19Mar97 				MMC.specialeventbits |= PLAYERWOUNDED;
//DeadCode RDH 19Mar97 			else
//DeadCode RDH 19Mar97 				MMC.Temp_Pilots [aircraft_no].daystorecover = 2 + Math_Lib.rnd(4);//RDH 20Nov96
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 		}elseif  (	(adptr->dammageflags & 0x5555)				//RDH 14Nov96
//DeadCode RDH 19Mar97 				||	(adptr->damageflags2 & 0x5555)				//RDH 14Nov96
//DeadCode RDH 19Mar97 				)
//DeadCode RDH 19Mar97 		{
//DeadCode RDH 19Mar97 			if (aircraft_no != Miss_Man.camp.currentplayerslot)	//RDH 19Nov96
//DeadCode RDH 19Mar97 				MMC.Temp_Pilots [aircraft_no].daystorecover = 2 + Math_Lib.rnd(2);
//DeadCode RDH 19Mar97 			ModifyPilotMorale(aircraft_no, (MoraleType)-(MORALE_STAGE/2));
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 		}elseif (currac->lasthitter.count != UID_Null)			//(aircraft hit)//RJS 11Feb97
//DeadCode RDH 19Mar97 		{
//DeadCode RDH 19Mar97 			ModifyPilotMorale(aircraft_no, (MoraleType)-(MORALE_STAGE/4));
//DeadCode RDH 19Mar97 			hitter = (AirStrucPtr) (Persons_2.ConvertPtrUID(currac->lasthitter.count));//RJS 11Feb97
//DeadCode RDH 19Mar97 			if (hitter->nationality == currac->nationality)
//DeadCode RDH 19Mar97 			{
//DeadCode RDH 19Mar97 				hitter_no = (hitter->fly.originalformpos&InWingMAX) +//RDH 19Dec96
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 						(hitter->fly.originalformpos&InFormMAX) * Miss_Man.camp.squad.pilotsperflight;//RDH 19Dec96
//DeadCode RDH 19Mar97 						(hitter->fly.originalformpos&InFormMAX) * 4;
//DeadCode RDH 19Mar97 				ModifyPilotMorale(hitter_no, (MoraleType) (-(hitter->ai.skill * 2)));
//DeadCode RDH 19Mar97 			}
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 		}else
//DeadCode RDH 19Mar97 		{
//DeadCode RDH 19Mar97 			if (enemyhit == TRUE)							//RDH 11Dec96
//DeadCode RDH 19Mar97 		 		ModifyPilotMorale(aircraft_no, MORALE_STAGE);
//DeadCode RDH 19Mar97 		}
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 		if (Miss_Man.camp.currmission->missiontext == TEXT_SOINTRO1)
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 		{
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 			if (adptr->lasthitter.count != UID_Null)
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 			{
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 				if 	(aircraft_no == 0)
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 				   	MMC.specialeventbits |= ATTACKEDAIRFRIENDLY;
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 			}
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 		}
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 	}else
//DeadCode RDH 19Mar97 	{
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 		if (Miss_Man.camp.currmission->missiontext == TEXT_SOINTRO1)
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 		{
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 			if (currac->Status.deadtime != 0)
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 				   	MMC.specialeventbits |= KILLEDAIRFRIENDLY;
//DeadCode RDH 19Mar97 //DeadCode RDH 15Jan97 		}
//DeadCode RDH 19Mar97 		if (currac->lasthitter.count != UID_Null)			//(aircraft hit)//RJS 11Feb97
//DeadCode RDH 19Mar97 		{
//DeadCode RDH 19Mar97 			hitter = (AirStrucPtr)(Persons_2.ConvertPtrUID(currac->lasthitter.count));//RJS 11Feb97
//DeadCode RDH 19Mar97 			if ( Art_Int.SameFlight(hitter,Manual_Pilot.ControlledAC2))
//DeadCode RDH 19Mar97 			{
//DeadCode RDH 19Mar97 //DeadCode RDH 12Dec96 				hitter_no = (hitter->formpos&InWingMAX) +
//DeadCode RDH 19Mar97 //DeadCode RDH 12Dec96 						(hitter->formpos&InFormMAX) * Miss_Man.camp.squad.pilotsperflight;
//DeadCode RDH 19Mar97 				hitter_no = (hitter->fly.originalformpos&InWingMAX) +
//DeadCode RDH 19Mar97 //DeadCode RDH 17Feb97 						(hitter->fly.originalformpos&InFormMAX) * Miss_Man.camp.squad.pilotsperflight;
//DeadCode RDH 19Mar97 						(hitter->fly.originalformpos&InFormMAX) * 4;
//DeadCode RDH 19Mar97 				if (currac->Status.deadtime != 0)
//DeadCode RDH 19Mar97 				{
//DeadCode RDH 19Mar97 					MMC.Temp_Pilots[hitter_no].kills ++;
//DeadCode RDH 19Mar97 //DeadCode JIM 13Dec96 					MMC.blueacflying--;
//DeadCode RDH 19Mar97 					blueacdead++;
//DeadCode RDH 19Mar97 //DeadCode JIM 13Dec96 					if (MMC.blueacflying < 0)
//DeadCode RDH 19Mar97 //DeadCode JIM 13Dec96 						MMC.blueacflying = 0;
//DeadCode RDH 19Mar97 					ModifyPilotMorale(hitter_no, (MoraleType) (hitter->ai.skill * 2));
//DeadCode RDH 19Mar97 					if (hitter_no == Miss_Man.camp.currentplayerslot)
//DeadCode RDH 19Mar97 							ModifyPlayerMerit(MERIT_KILL);
//DeadCode RDH 19Mar97 	
//DeadCode RDH 19Mar97 	
//DeadCode RDH 19Mar97 				}elseif  (	(adptr->dammageflags && 0xaaaa)		//binary 1010 1010 1010 1010
//DeadCode RDH 19Mar97 						||	(adptr->damageflags2 && 0xaaaa)		//binary 1010 1010 1010 1010
//DeadCode RDH 19Mar97 						)
//DeadCode RDH 19Mar97 				{
//DeadCode RDH 19Mar97 						ModifyPilotMorale(hitter_no, (MoraleType)hitter->ai.skill);
//DeadCode RDH 19Mar97 				}elseif  (	(adptr->dammageflags && 0x5555)		
//DeadCode RDH 19Mar97 							||	(adptr->damageflags2 && 0x5555)
//DeadCode RDH 19Mar97 							 )
//DeadCode RDH 19Mar97 				{
//DeadCode RDH 19Mar97 						ModifyPilotMorale(hitter_no, (MoraleType)(hitter->ai.skill/2));
//DeadCode RDH 19Mar97 				}else
//DeadCode RDH 19Mar97 				{
//DeadCode RDH 19Mar97 						ModifyPilotMorale(hitter_no, (MoraleType)(hitter->ai.skill/4));
//DeadCode RDH 19Mar97 				}
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 			}	
//DeadCode RDH 19Mar97 		}
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97   	}
//DeadCode RDH 19Mar97 	currac = (AirStrucPtr) currac->nextmobile;
//DeadCode RDH 19Mar97   }
//DeadCode RDH 19Mar97 	MMC.blueacflying -= blueacdead /2;
//DeadCode RDH 19Mar97 	if (MMC.blueacflying < 4)
//DeadCode RDH 19Mar97 			MMC.blueacflying = 4;
//DeadCode RDH 19Mar97 
//DeadCode RDH 19Mar97 //decide whether to bypass recording the hits during the mission
//DeadCode RDH 19Mar97 //if campaign lost don't record
//DeadCode RDH 19Mar97  	PrelimActivePilotChk ();
//DeadCode RDH 19Mar97 	if ((MMC.specialeventbits[HOMEBASEDESTROYED]) ||
//DeadCode RDH 19Mar97 		(MMC.specialeventbits[PLAYERKILLED]) ||
//DeadCode RDH 19Mar97 //DeadCode RDH 13Mar97 		(MMC.specialeventbits[TANKCAMPAIGNLOST]) ||
//DeadCode RDH 19Mar97 		(MMC.specialeventbits[RESERVEEXHAUSTED]) ||
//DeadCode RDH 19Mar97 		(MMC.specialeventbits[KILLEDAIRFRIENDLY]) ||
//DeadCode RDH 19Mar97 		(MMC.specialeventbits[PLAYERCAPTURED]) ||
//DeadCode RDH 19Mar97 		(MMC.specialeventbits[ATTACKEDAIRFRIENDLY])
//DeadCode RDH 19Mar97 		
//DeadCode RDH 19Mar97 		)
//DeadCode RDH 19Mar97 	{
//DeadCode RDH 19Mar97 		MMC.specialeventbits |= CAMPAIGNLOST;
//DeadCode RDH 19Mar97 	}
//DeadCode RDH 19Mar97 
}
