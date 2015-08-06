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
//Filename       noderev.cpp
//System         
//Author         R. Hyde 
//Date           Thu 6 Mar 1997
//Description    
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//
//In 3d/debrief:
//
//On killing mobiles allocate storesdestroyed to launching SupplyRoutes
//
//		Need:		BlueAcAtAirfield(UniqueID af)
//						RedAcAtAirfield(UniqueID af)
//	
//
//Logic to handle salients:
//		one route front cannot be radically different from the others
//Need to be able to distiguish if something is dead
//
//Use:
//		consecutive_days_attacked
//		stores_destroyed
//		totalstores_destroyed
//		recommision_time				(Implement code ProcessStoresArrival)
//
//What needs to be done about campaign win/loss?
//		Same for every campaign?
//What should we do about first node. at present we just max stores everyday 
//
//Routines that need discussion:
//	FindModifiedSupplies()		
//		called for frontline only
//		used when?
//	ProcessAirFields()
//		test may have to change in light of frontline change
//		do we loose a/c: RemoveLostAc();
//		and kill it on transfer to other side: KillItem ();
//	WithDrawSupplies(SupplyNode* node)
//		launch some battle fields to indicate withdrawal
//		messages to player

//
//Not Used:
//	UpdateBf()
//
//Traffic along a whole route should be modified by attacks on big marshalling yards
//	Use TodaysMobiles and Currmobiles
//	Whatabout splitAB splitBC
//for each supply line
//determine TodaysTrains using MaxTrains and status of
//	AssociatedMarshallingYard[2]

//Battle Field launches
//Each InterNode structure has the potential to launch mobiles. These will only
//be seen in the game when an individual field exceeds the normal maximum. 
//This is to indicate movement during the day. 
//Normal movements occurred at night.
//
//We should generally see movement then just behind the lines.
//
//In addition:
//	we will place aircraft on the active airfields
//	front line activity will be launched for FRONTLINE node
//

//Other things to consider:
//
//	Activity on nodes and supplyroutes should generate messages
//
//
//	If Player selects close support mission, he will be directed to battlefield
//	targets by radio and FAC. When out of ammo he returns and may be told he
//	needs to go out immediately to finish the job.
//
//MiG model
//	how many MiGs are launched each day and where
//
//
//Messages:
//
//		Ground forces say they need an attack on something to help them.
//		Red artillery needs to be taken out
//			to help defence
//			to help attack
//
#include	"dosdefs.h"											//RJS 30Aug96
//#include	"stdafx.h"
#include	"myerror.h"												  //DAW 26/04/99
#define F_BATTLE												//RJS 30Aug96
#include	"files.g"											//RJS 30Aug96

#include	"math.h"
#include	"worldinc.h"
#include	"text.h"
#include	"missman2.h"
#include	"node.h"
//#include	"briefing.h"											//PD 15Mar96
#include "mymath.h"
#include "..\mfc\resource.h"
#include "persons2.h"
MATHABLE(SupplyPriority);



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindModifiedSupplies
//Author		R. Hyde 
//Date			Thu 6 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord SupplyTree::FindModifiedSupplies(SupplyNode* node)
{
	 SWord retval;

	retval = node->currentstores;

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BlueAcAtAirfield
//Author		R. Hyde 
//Date			Tue 11 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord SupplyTree::BlueAcAtAirfield(UniqueID af)
{
	SWord	count = 0;
	for (int squad = 0; squad < 5; squad++)
	{
		if (airfieldinfo[MMC.squad[squad].airfieldindex].airfield == af)
			count += MMC.squad[squad].ac_total_avail;
	}

	return (count);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RedAcAtAirfield
//Author		R. Hyde 
//Date			Tue 11 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord SupplyTree::RedAcAtAirfield(UniqueID af)
{

	SWord	count;
	AirFieldInfo* afptr=FindAirfieldForItem(af);
	count = afptr->activeac; 
	return (count);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PopulateRedAfs
//Author		R. Hyde 
//Date			 //RDH 13/02/99
//
//Description		
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::PopulateRedAfs()
{
//DEADCODE RDH 19/06/99 //clr out activeac
//DEADCODE RDH 19/06/99 	SWord i = 0;
//DEADCODE RDH 19/06/99 	while (airfieldinfo[i].nationality != NAT_ALIGN)
//DEADCODE RDH 19/06/99 	{
//DEADCODE RDH 19/06/99 		airfieldinfo[i].activeac = 0;
//DEADCODE RDH 19/06/99 		i++;
//DEADCODE RDH 19/06/99 	}
	UniqueID af;
	SWord i = 0;
	if (Miss_Man.currcampaignnum != MissMan::F86_CAMPAIGN)			  //RDH 14/06/99
	{//don't want MiGs on red airfelds below Yalu in F86 campaign	  //RDH 14/06/99 //RDH 14/06/99

		int afnum = MMC.migsquad[1].ac_total_avail/20;
		int acnum = MMC.migsquad[1].ac_total_avail;
		int popac;
		if (afnum > 2)
			afnum = 2;
		for (i = 0; i <= afnum;i++)
		{
			popac = acnum;
			if (popac > 20)
				popac = 20;
			if (popac > 0)
				af = FindRedAfToPopulate(popac);	//store as a negative number 
			acnum = acnum - popac;

		}
	}
	//clr out old activeac
	i = 0;
	while (airfieldinfo[i].nationality != NAT_ALIGN)
	{
		if (airfieldinfo[i].activeac < 0)
			airfieldinfo[i].activeac = -airfieldinfo[i].activeac; 
		else
			airfieldinfo[i].activeac = 0;
		i++;
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindRedAfToPopulate
//Author		R. Hyde 
//Date			Thu 6 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UniqueID SupplyTree::FindRedAfToPopulate(int acnum)
{
//find a red airfield that fits the bill to populate
//populate it with acnum aircraft
	SupplyNode* currnode;

	currnode =  WestRoute.frontline->route[0]->supplier;
	COORDS3D& frontline=
			Persons2::ConvertPtrUID(WestRoute.frontline->associated_item)->World;

	while (currnode != NULL)
	{
		for (int i=0;i <3;i++)
		{

			AirFieldInfo* af=FindAirfieldForItem(currnode->airfield[i]);
			if (af)
			{
				COORDS3D& afworld=
					Persons2::ConvertPtrUID(af->airfield)->World;

				if	(		(af->attackstats.damagelevel < 90) 
						&&	(af->activeac >= 0)
						&&	((afworld.Z - frontline.Z) > 5000000)	//airfield > 50km north of frontlibe
					)
				{
					if (af->activeac == 0)
						MMC.DisDayEntry(Debrief::TARGUID, af->airfield, Debrief::T_Airfield01_H);
					af->activeac =-acnum;
					return(af->airfield);
				}
			}
		}
		currnode = currnode->route[0]->supplier;
	}	
	return(UID_Null);
}
void SupplyTree::MoveSquadron(int squad)
{
	int af = 0;
	while	(		(airfieldinfo[af].nationality!=NAT_ALIGN)
			)
	{
		if (	(		(		(airfieldinfo[af].type < AFT_JET)
							&&	(squad != SQ_F51)	
						)
					||
						(airfieldinfo[af].type > AFT_JET)
				)
				&&
				(FindFreeSlots(af) >= 1)
				&&
				(airfieldinfo[af].nationality == NAT_BLUE)
			)
		{
			MMC.squad[squad].movetoairfieldindex = -1;
			MMC.DisDayEntry(Debrief::DISCARDTARGUID, 
				airfieldinfo[MMC.squad[squad].airfieldindex].airfield, 
					Debrief::T_Airfield02_H); //RDH 18/04/99

			MMC.squad[squad].airfieldindex = af;
 
			break;
			
		}

		af++;
	}
}
int SupplyTree::FindFreeSlots(int afnum)
{
	int free =0;
 	for (int i=0;i<PILOTABLE_SQUADRONS;i++)
	{
		if  (		(		(MMC.squad[i].airfieldindex == afnum)
						&&	(MMC.squad[i].movetoairfieldindex == -1)
					)
				||	(		(MMC.squad[i].movetoairfieldindex == afnum)
					)
			)
			free++;
	}
	free = SupplyTree::airfieldinfo[afnum].capacity - free;
	return (free);
	
}
void SupplyTree::MoveAnyBlueAc(int curraf)
{
 	for (int i=0;i<PILOTABLE_SQUADRONS;i++)
	{
		if  (		(		(MMC.squad[i].airfieldindex == curraf)
						&&	(MMC.squad[i].movetoairfieldindex == -1)
					)
				||	(		(MMC.squad[i].movetoairfieldindex == curraf)
					)
			)
			MoveSquadron(i);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessAirFields
//Author		R. Hyde 
//Date			Thu 6 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::ProcessAirFields()
{
	SWord i = 0;
	PopulateRedAfs();
	while (airfieldinfo[i].nationality != NAT_ALIGN)
	{
		if (airfieldinfo[i].nationality == NAT_BLUE)
		{
			if  (	(airfieldinfo[i].northnodes[0]->status == BEHINDREDLINES)
				&&	(airfieldinfo[i].northnodes[1]->status == BEHINDREDLINES)
				)
			{
	 			MMC.DisDayEntry(Debrief::DISCARDTARGUID, airfieldinfo[i].airfield, Debrief::T_AF01_H);
				airfieldinfo[i].nationality = NAT_RED;
				airfieldinfo[i].days = 0;
				MoveAnyBlueAc(i);									  //RDH 10/03/99
			}elseif (	(airfieldinfo[i].northnodes[0]->status == BEHINDREDLINES)
					||	(airfieldinfo[i].northnodes[1]->status == BEHINDREDLINES)
					||	(airfieldinfo[i].northnodes[0]->status == FRONTLINE)
					||	(airfieldinfo[i].northnodes[1]->status == FRONTLINE)
					)
			{
				if  (	(airfieldinfo[i].northnodes[0]->supplyline->initiative == REDATTACKING)
					||	(airfieldinfo[i].northnodes[1]->supplyline->initiative == REDATTACKING)
					)
					airfieldinfo[i].days++;
				if (airfieldinfo[i].days == 1)
		 			MMC.DisDayEntry(Debrief::DISCARDTARGUID, airfieldinfo[i].airfield, Debrief::T_AF00_H);
				elseif (BlueAcAtAirfield(airfieldinfo[i].airfield) != 0)
 					MMC.DisDayEntry(Debrief::DISCARDTARGUID, airfieldinfo[i].airfield, Debrief::T_AF00_H);
			}else
			{
				airfieldinfo[i].days = 0;

			}


		}else
		{
			if  (	(airfieldinfo[i].northnodes[0]->status == BEHINDBLUELINES)
					&&	(airfieldinfo[i].northnodes[1]->status == BEHINDBLUELINES)
				) 
			{
				MMC.DisDayEntry(Debrief::DISCARDTARGUID, airfieldinfo[i].airfield, Debrief::T_AF02_H);
				airfieldinfo[i].nationality = NAT_BLUE;
				airfieldinfo[i].days = 0;

			}elseif (	(airfieldinfo[i].southnodes[0]->status == BEHINDBLUELINES)
					||	(airfieldinfo[i].southnodes[1]->status == BEHINDBLUELINES)
					||	(airfieldinfo[i].northnodes[0]->status == FRONTLINE)
					||	(airfieldinfo[i].northnodes[1]->status == FRONTLINE)
					)
			{
				if  (	(airfieldinfo[i].northnodes[0]->supplyline->initiative == BLUEATTACKING)
					||	(airfieldinfo[i].northnodes[1]->supplyline->initiative == BLUEATTACKING)
					)
					airfieldinfo[i].days++;
			if (airfieldinfo[i].days == 1)
				MMC.DisDayEntry(Debrief::DISCARDTARGUID, airfieldinfo[i].airfield, Debrief::T_Airfield04_H);
			elseif (RedAcAtAirfield(airfieldinfo[i].airfield) != 0)
				MMC.DisDayEntry(Debrief::DISCARDTARGUID, airfieldinfo[i].airfield, Debrief::T_Airfield05_H);
			}else
			{
				airfieldinfo[i].days = 0;
			}
		}
		i++;
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RetreatOneNode
//Author		R. Hyde 
//Date			12/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::RetreatOneNode()
{
	for (int front=0;front<3;front++)
		if (supplylines[front]->frontline->type==BATTLEFIELD)
			RetreatOneNode(supplylines[front]);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RetreatOneNode
//Author		R. Hyde 
//Date			Tue 11 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::RetreatOneNode(SupplyLine* SL)
{

//DEADCODE RDH 24/03/99 	if (SL->frontline->route[0]->supplier == &N1_7_Pyongyang)
//DEADCODE RDH 24/03/99 		MMC.specialeventbits |= CAMPAIGNWONENTEREDPYONGYANG;
//DEADCODE RDH 24/03/99 	else
//DEADCODE RDH 24/03/99 		SL->frontline = SL->frontline->route[0]->supplier;

//N1_6_Sukchon is one above
//last battlefield
	SL->ExitBf();
	SL->frontline = SL->frontline->route[0]->supplier;
		SL->initiative=BLUEINITIATIVE;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateSupplyDIS
//Author		R. Hyde 
//Date			//RDH 09/03/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::GenerateSupplyDIS()
{
	SupplyNode* currnode = CurrDisNode;
	do
	{
		NodeType type;
		if (currnode)
			type = currnode->type;
		if (		(currnode->type == LASTONE)
		   )
			currnode = FirstNode;
		else
			currnode = currnode->next;

		if	(		(currnode->associated_town != NULL)
				&&	(currnode->maxstorestonnes > STORES_INITALMEDIUMSETTLEMENT)
				&&	((3 * currnode->currentstores) > (currnode->maxstorestonnes * 4))
			)
		{
			MMC.DisDayEntry(Debrief::DISCARDTARGUID, currnode->associated_town, Debrief::T_Supply00_H);
			break;
		}



	}while (currnode != CurrDisNode);
	CurrDisNode = currnode;

	FrontLineSupplyDIS(&WestRoute);
	FrontLineSupplyDIS(&CentralRoute);
	FrontLineSupplyDIS(&EastRoute);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FrontLineSupplyDIS
//Author		R. Hyde 
//Date			//RDH 09/03/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::FrontLineSupplyDIS(SupplyLine* SL)
{
	if (SL->frontline->currentstores < STORES_TOSUPPORTASSAULT)
		MMC.DisDayEntry(Debrief::DISCARDTARGUID, SL->frontline->associated_item, Debrief::T_Supply01_H);
	 else
		MMC.DisDayEntry(Debrief::DISCARDTARGUID, SL->frontline->associated_item, Debrief::T_Supply02_H);
	 if (SL->frontline->status != FRONTLINE)
	 {
		if (SL->frontline->currentstores > STORES_TOPREPAREASSAULT)
			MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army00_H);
		else if (SL->frontline->currentstores < STORES_BLUEPREPAREATTACK)
			MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army05_H);

	 }
}




static const int forcenames[3][2][TeamDef::MAXFORCETYPES]=
{	//TROOPSONLY,MORTAR,MORTARTRUCK,TANKS,ARTILLARY
	{/*WR*/	{IDS_L_WR_TROOPS,IDS_L_WR_MORTAR,IDS_L_WR_MORTARTRUCK,IDS_WR_TANKS,IDS_WR_ARTILLARY},
	 /*WB*/	{IDS_L_WB_TROOPS,IDS_L_WB_MORTAR,IDS_L_WB_MORTARTRUCK,IDS_WB_TANKS,IDS_WB_ARTILLARY}},
	{/*CR*/	{IDS_L_CR_TROOPS,IDS_L_CR_MORTAR,IDS_L_CR_MORTARTRUCK,IDS_CR_TANKS,IDS_CR_ARTILLARY},
	 /*CB*/	{IDS_L_CB_TROOPS,IDS_L_CB_MORTAR,IDS_L_CB_MORTARTRUCK,IDS_CB_TANKS,IDS_CB_ARTILLARY}},
	{/*ER*/	{IDS_L_ER_TROOPS,IDS_L_ER_MORTAR,IDS_L_ER_MORTARTRUCK,IDS_ER_TANKS,IDS_ER_ARTILLARY},
	 /*EB*/	{IDS_L_EB_TROOPS,IDS_L_EB_MORTAR,IDS_L_EB_MORTARTRUCK,IDS_EB_TANKS,IDS_EB_ARTILLARY}},
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitiateBf
//Author		R. Hyde 
//Date			Thu 6 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyLine::InitiateBf()
{
	int slnum;
	if (this==&SupplyTree::WestRoute)
		slnum=0;
	else
	if (this==&SupplyTree::CentralRoute)
		slnum=1;
	else
////if (this==&SupplyTree::EastRoute)
		slnum=2;
	if (slnum!=2)													  //JIM 10/06/99
		if (initiative==REDATTACKING)
		{
			MMC.DisDayEntry(Debrief::TARGUID,frontline->associated_item,frontline->bluefrontBF->startdis);

			if (groundbattle.LoadBattleNodes(frontline->bluefrontBF->nodetree))
			{
				groundbattle.NewSetupFirstDay(forcenames[slnum][0],forcenames[slnum][1],frontline->maxstorestonnes*0.50,frontline->currentstores);
				groundbattle.NextAttackDecisions();

			}
		}
		else
		{
			MMC.DisDayEntry(Debrief::TARGUID,frontline->associated_item,frontline->redfrontBF->startdis);
			frontline->currentstores+=frontline->maxstorestonnes*0.30;//DAW 02Sep99
			if (groundbattle.LoadBattleNodes(frontline->redfrontBF->nodetree))
			{
				groundbattle.NewSetupFirstDay(forcenames[slnum][1],forcenames[slnum][0],frontline->currentstores,frontline->maxstorestonnes*0.50);
				groundbattle.NextAttackDecisions();

			}
		}
}
void SupplyLine::ExitBf()
{
	for (int t=0;t<groundbattle.MAXTEAMS;t++)
		groundbattle.teamlist[t].strength=0;
	groundbattle.usednodes=0;
	groundbattle.usedteams=0;
}

//DEADCODE JIM 18/05/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JIM 18/05/99 //Procedure		UpdateBf
//DEADCODE JIM 18/05/99 //Author		R. Hyde 
//DEADCODE JIM 18/05/99 //Date			Thu 6 Mar 1997
//DEADCODE JIM 18/05/99 //
//DEADCODE JIM 18/05/99 //Description	
//DEADCODE JIM 18/05/99 //
//DEADCODE JIM 18/05/99 //Inputs		
//DEADCODE JIM 18/05/99 //
//DEADCODE JIM 18/05/99 //Returns	
//DEADCODE JIM 18/05/99 //
//DEADCODE JIM 18/05/99 //------------------------------------------------------------------------------
//DEADCODE JIM 18/05/99 void SupplyTree::UpdateBf()
//DEADCODE JIM 18/05/99 {
//DEADCODE JIM 18/05/99 
//DEADCODE JIM 18/05/99 }
//DEADCODE JIM 18/05/99 


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WithDrawSupplies
//Author		R. Hyde 
//Date			Tue 11 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::WithDrawSupplies(SupplyNode* node)
{
//launch some battle fields to indicate withdrawal
//messages to player
//
	for (int route=0;route<3;route++)
		if (node->route[route] && node->route[route]->suppliee)
			if (node->currentstores/5>node->route[route]->maxcapacitysummer)
				node->route[route]->supplier->currentstores+=node->route[route]->maxcapacitysummer;
			else
				node->route[route]->supplier->currentstores+=node->currentstores/5;
	node->currentstores=0;

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreLaunchPossible
//Author		R. Hyde 
//Date			Tue 11 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord SupplyTree::StoreLaunchPossible(SupplyRoute* currroute)
{
	SWord capacity = currroute->maxcapacitysummer;

	capacity -= currroute->storeslaunched;

	return (capacity);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SupplyNode
//Author		R. Hyde 
//Date			Tue 11 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::SupplyThisNode(SupplyNode* node,SWord priority,SWord requirement)
{
	SWord i = 0,storelaunchrequest;
	SupplyRoute*  currroute;


	while   (	(i < NUM_OF_SUPPLYROUTES)
			&&	(requirement != 0)	
			)
	{
		currroute =  node->route[i];
		while (		(currroute != NULL)
				&&	(requirement != 0)
			  )
		{
			if  (	(currroute->status == SR_ACTIVE)
				&&	(!currroute->associated_brdg || currroute->attackstats.damagelevel<90)
				)
			{
				if	(currroute->supplier->currentstores > 0)		  //RDH 14/05/99
				{
					if (currroute->supplier->currentstores < requirement)
						storelaunchrequest = currroute->supplier->currentstores;
					else
						storelaunchrequest = requirement;

					if ((StoreLaunchPossible(currroute)) < storelaunchrequest)
						storelaunchrequest = StoreLaunchPossible(currroute);

					if (storelaunchrequest < 0)
						storelaunchrequest = 0;
					if (storelaunchrequest == 0)
							 MMC.DisDayEntry(Debrief::DISCARDTARGUID, currroute->supplier->associated_item, Debrief::T_Supply02_H);
					currroute->supplier->priority = 
						(SupplyPriority)(currroute->supplier->priority+
										priority*storelaunchrequest/requirement);
					requirement -= storelaunchrequest;
					currroute->supplier->currentstores -= storelaunchrequest;
			 		currroute->storeslaunched += storelaunchrequest;
				}else
					currroute->supplier->priority = (SupplyPriority)priority;

			}
			currroute = currroute->alternateroute;  
		};
		i++;
	}
//DeadCode DAW 21May99 	if (requirement > 0)
   			

	node->serviced = TRUE;			//perhaps unsuccessfully

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AdvanceOneNode
//Author		R. Hyde 
//Date			12/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::AdvanceOneNode()
{
	for (int front=0;front<3;front++)
		if (supplylines[front]->frontline->type==BATTLEFIELD)
			AdvanceOneNode(supplylines[front]);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AdvanceOneNode
//Author		R. Hyde 
//Date			Tue 11 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::AdvanceOneNode(SupplyLine* SL)
{

//DEADCODE RDH 24/03/99 	if (SL->frontline->route[0]->suppliee == &N3_1_Taejon)
//DEADCODE RDH 24/03/99 		MMC.specialeventbits |= CAMPAIGNLOSTTAEJONOVERRUN;
//DEADCODE RDH 24/03/99 	else
//DEADCODE RDH 24/03/99 		SL->frontline = SL->frontline->forward->suppliee;

//N3_3_Chonan is behind blue's last battlefield
		SL->ExitBf();
		SL->frontline = SL->frontline->forward->suppliee;
		SL->initiative=REDINITIATIVE;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoresUsage
//Author		R. Hyde 
//Date			Mon 17 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord SupplyTree::StoresUsage  (SupplyLine* SL,SupplyNode* node)
{
	SWord retval;
	if (node == SL->frontline)
	{
		return -(30+(node->attackstats.damagelevel*node->maxstorestonnes/400));
	}else
	{
		retval = 0;
	}
	return (retval);
}


//////////////////////////////////////////////////////////////////////
//
// Function:    AllFrontOnBattleNodes
// Date:		29/06/99
// Author:		JIM
//
//Description: Checks all front are on battle nodes.
//				If non-zero checks they are on same battle nodes
//
//////////////////////////////////////////////////////////////////////
bool	SupplyTree::AllFrontOnBattleNodes(int frontnum)
{	
	if (	WestRoute.frontline->type==NOCONTEST 
		||	CentralRoute.frontline->type==NOCONTEST 
		||	EastRoute.frontline->type==NOCONTEST
		)
		return false;
	if (frontnum)
		if (	WestRoute.frontline->redfrontBF->frontnum!=frontnum
			||	CentralRoute.frontline->redfrontBF->frontnum!=frontnum
			||	EastRoute.frontline->redfrontBF->frontnum!=frontnum
			)
			return false;
	return true;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessFrontLineRequest
//Author		R. Hyde 
//Date			Tue 11 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::ProcessFrontLineRequest (SupplyLine* SL)
{
	SWord supplies;
	SWord requirement;

	supplies = FindModifiedSupplies(SL->frontline);

	requirement = SL->frontline->maxstorestonnes - SL->frontline->currentstores
									- StoresUsage (SL,SL->frontline);
	if (Miss_Man.currcampaignnum!=Miss_Man.F51_CAMPAIGN)
		SL->FACActive=(Math_Lib.rnd()>20000);
	else
		SL->FACActive=true;
	switch (SL->initiative)
	{
		case BLUEINITIATIVE:
		{
			switch (SL->frontline->type)
			{
				case NOCONTEST:
				{
					if (supplies  < SL->frontline->maxstorestonnes*0.05)
						RetreatOneNode(SL);
					else
						WithDrawSupplies(SL->frontline);
					break;
				}
				case BATTLEFIELD:
				{
					SupplyThisNode(SL->frontline,SP_HIGH,requirement);
					if (supplies >  (3*SL->frontline->maxstorestonnes/4))
					{
						SL->initiative = REDINITIATIVE;
					}else 
						if (supplies <  (2*SL->frontline->maxstorestonnes/4))
							if (AllFrontOnBattleNodes())
							{
								SL->initiative = BLUEATTACKING;
								SL->InitiateBf();
							}
					break;
				}
			}
			break;
		}
		case REDINITIATIVE:
		{
			switch (SL->frontline->type)
			{
				case NOCONTEST:
				{
					if (supplies  >= SL->frontline->maxstorestonnes*0.2)
						AdvanceOneNode(SL);
					else
					{	//Nasty cheet. I don't want to take all day about the advancement or it will go wrong!
						supplies=SL->frontline->maxstorestonnes*0.21;  //DAW 26/06/99
						SupplyThisNode(SL->frontline,SP_HIGH,requirement);
					}
					break;
				}
				case BATTLEFIELD:
				{
					if (supplies >= SL->frontline->maxstorestonnes*0.95)
					{
						if (AllFrontOnBattleNodes())
						{					
							SL->initiative = REDATTACKING;
							SL->InitiateBf();
						}
					}
					else
						if(supplies < (STORES_TODISCOURAGEBLUEATTACK*0.8+SL->frontline->maxstorestonnes*0.3))
						{
							SL->initiative = BLUEINITIATIVE;
						}
					requirement = STORES_TOSUPPORTASSAULT;
					SupplyThisNode(SL->frontline,SP_HIGH,requirement);
					break;

				}
			}
			break;
		}
		case BLUEATTACKING:
		{
			switch (SL->frontline->type)
			{
				case NOCONTEST:
				{
					SL->initiative = BLUEINITIATIVE;
					break;
				}
				case BATTLEFIELD:
				{
//DEADCODE JIM 19/06/99 ALL THESE CONDITIONS HANDLED INSIDE GROUND BATTLE PROCESSING
//DEADCODE JIM 19/06/99 //					if (supplies > (3*SL->frontline->maxstorestonnes/4))
//DEADCODE JIM 19/06/99 //					{	THIS IS NOW BLUELOST
//DEADCODE JIM 19/06/99 //						SL->initiative = REDATTACKING;
//DEADCODE JIM 19/06/99 //						if (Math_Lib.rnd(2))
//DEADCODE JIM 19/06/99 //							MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army04_H);
//DEADCODE JIM 19/06/99 //						else
//DEADCODE JIM 19/06/99 //							MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army07_H);
//DEADCODE JIM 19/06/99 //					}elseif (supplies <(SL->frontline->maxstorestonnes/4))
//DEADCODE JIM 19/06/99 //					{	THIS IS NOW BLUEWON
//DEADCODE JIM 19/06/99 //						if (SL!=&EastRoute)							  //JIM 10/06/99
//DEADCODE JIM 19/06/99 //						{
//DEADCODE JIM 19/06/99 //		 					MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, SL->frontline->bluefrontBF->advancedis);
//DEADCODE JIM 19/06/99 //							RetreatOneNode();
//DEADCODE JIM 19/06/99 //							SL->initiative = BLUEINITIATIVE;
//DEADCODE JIM 19/06/99 //						}
//DEADCODE JIM 19/06/99 //					}
//DEADCODE JIM 19/06/99 					if (supplies<STORES_TODISCOURAGEBLUEATTACK)
//DEADCODE JIM 19/06/99 					{
//DEADCODE JIM 19/06/99 						if (SL!=&EastRoute)
//DEADCODE JIM 19/06/99 							SL->initiative=BLUEWON;
//DEADCODE JIM 19/06/99 					}
//DEADCODE JIM 19/06/99 					else
					{
						SupplyThisNode(SL->frontline,SP_HIGH,requirement);
					}
					break;
				}
			}
			break;
		}
		case BLUELOST:
		{
			if (Math_Lib.rnd(2))
				MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army04_H);
			else
				MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army07_H);
			SL->ExitBf();
			SL->initiative=REDINITIATIVE;
		}
		break;
		case REDATTACKING:
		{
			switch (SL->frontline->type)
			{
				case NOCONTEST:
				{
					SL->initiative = REDINITIATIVE;
					break;
				}
				case BATTLEFIELD:
				{
//DEADCODE JIM 19/06/99 ALL THESE CONDITIONS HANDLED INSIDE GROUND BATTLE PROCESSING
//DEADCODE JIM 19/06/99 //					if (supplies >= SL->frontline->maxstorestonnes)
//DEADCODE JIM 19/06/99 //					{	THIS IS NOW REDWON
//DEADCODE JIM 19/06/99 //						if (SL!=&EastRoute)							  //JIM 10/06/99
//DEADCODE JIM 19/06/99 //						{
//DEADCODE JIM 19/06/99 //		 					MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, SL->frontline->redfrontBF->advancedis);
//DEADCODE JIM 19/06/99 //							AdvanceOneNode();
//DEADCODE JIM 19/06/99 //							SL->initiative = REDINITIATIVE;
//DEADCODE JIM 19/06/99 //							SupplyThisNode(SL->frontline,SP_HIGH,requirement);
//DEADCODE JIM 19/06/99 //						}
//DEADCODE JIM 19/06/99 //					}
//DEADCODE JIM 19/06/99 //					elseif (supplies > (SL->frontline->maxstorestonnes/4))
//DEADCODE JIM 19/06/99 					if (supplies<STORES_TODISCOURAGEBLUEATTACK)
//DEADCODE JIM 19/06/99 					{
//DEADCODE JIM 19/06/99 						if (SL!=&EastRoute)
//DEADCODE JIM 19/06/99 							SL->initiative = REDLOST; 
//DEADCODE JIM 19/06/99 					}
//DEADCODE JIM 19/06/99 					else
					{
//DEADCODE JIM 18/05/99 						UpdateBf();
						SupplyThisNode(SL->frontline,SP_HIGH,requirement);
					}
//DEADCODE JIM 19/06/99 //					else
//DEADCODE JIM 19/06/99 //					{
//DEADCODE JIM 19/06/99 //						SL->ExitBf();
//DEADCODE JIM 19/06/99 //						SL->initiative = BLUEINITIATIVE; 
//DEADCODE JIM 19/06/99 //						if (Math_Lib.rnd(2))
//DEADCODE JIM 19/06/99 //							MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army02_H);
//DEADCODE JIM 19/06/99 //						else
//DEADCODE JIM 19/06/99 //							MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army03_H);
//DEADCODE JIM 19/06/99 //DEADCODE JIM 18/05/99 						RetreatOneNode();
//DEADCODE JIM 19/06/99 //					}
					break;
				}
			}
			break;
		}
		case REDLOST:
		{
			if (Math_Lib.rnd(2))
				MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army02_H);
			else
				MMC.DisDayEntry(Debrief::TARGUID, SL->frontline->associated_item, Debrief::T_Army03_H);
			SL->ExitBf();
			SL->initiative=BLUEINITIATIVE;
		}
		break;
		case REDWON:
		{	  //not handled here!
		}
		break;
		case BLUEWON:
		{	  //not handled here!
		}
		break;
	}
//DEADCODE JIM 10/06/99 	SL->groundbattle.NextAttackDecisions();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessFrontLineRequests
//Author		R. Hyde 
//Date			Thu 6 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::ProcessFrontLineRequests ()
{

	ProcessFrontLineRequest (&WestRoute);
	ProcessFrontLineRequest (&EastRoute);
	ProcessFrontLineRequest (&CentralRoute);
	if (WestRoute.initiative==REDWON || EastRoute.initiative==REDWON || CentralRoute.initiative==REDWON)
	{
		for (int fr=0;fr<3;fr++)
			if (supplylines[fr]->initiative==REDWON)
		 		MMC.DisDayEntry(Debrief::TARGUID, supplylines[fr]->frontline->associated_item, supplylines[fr]->frontline->bluefrontBF->advancedis);
		AdvanceOneNode();
	}
	else
	if (WestRoute.initiative==BLUEWON || EastRoute.initiative==BLUEWON || CentralRoute.initiative==BLUEWON)
	{
		for (int fr=0;fr<3;fr++)
			if (supplylines[fr]->initiative==BLUEWON)
				MMC.DisDayEntry(Debrief::TARGUID, supplylines[fr]->frontline->associated_item, supplylines[fr]->frontline->redfrontBF->advancedis);
		RetreatOneNode();
	}

}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SupplyHPNodes
//Author		R. Hyde 
//Date			Thu 6 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::SupplyHPNodes ()
{

	SupplyPriority priority;
	SupplyNode* currnode;
	SupplyNode*  hp_node=NULL;
	SWord	requirement;
		

	do
	{
		priority = SP_NONE;
		currnode = &N0_0_Dangdong;
		while (currnode->next->type != LASTONE)
		{
			if  (	(currnode->serviced == FALSE)
				&&  (currnode->status!=BEHINDBLUELINES)	//don't supply blue nodes
				&&	(currnode->priority > priority)
				&&  (	currnode->status!=FRONTLINE		//don't supply blue advance nodes
					||	currnode->type!=NOCONTEST					  //JIM 29/06/99
					||	currnode->supplyline->initiative!=BLUEINITIATIVE
					)
				)
				{
					priority = currnode->priority;
					hp_node = currnode;
				}
			currnode = currnode->next;
		};
		if (priority != SP_NONE)
		{
			requirement = hp_node->maxstorestonnes -
							hp_node->currentstores;
			SupplyThisNode(hp_node,(SWord) priority,requirement);
		}
	}
	while (priority != SP_NONE);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetPriorityAndServicedFlag
//Author		R. Hyde 
//Date			Wed 12 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::ResetPriorityAndServicedFlag()
{
	SupplyNode* currnode;

	currnode = &N0_0_Dangdong;
	while (currnode->next->type != LASTONE)
	{

		if (currnode->currentstores == currnode->maxstorestonnes)
		{
			currnode->priority = SP_NONE;

		}
		currnode->serviced = FALSE;
		currnode = currnode->next;
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessStoresDestroyed
//Author		R. Hyde 
//Date			 //RDH 25/05/99
//
//Description	
//			On starting a mission put last store_destroyed in 
//			stores_destroyed_today and then zero
//
//			store_destroyed can then be used for stores destroyed on mission
//			stores_destroyed_today is used in node review at the end of the day
//			stores_destroyed needs to be retained because it is used in debrief
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::ProcessStoresDestroyed ()
{
	SupplyRoute* currroute;
		
	currroute= &R0_0_1Rail0; 
	while (currroute->next->status != SR_LASTONE)
	{
		currroute->stores_destroyed_today += currroute->stores_destroyed;
		currroute->stores_destroyed = 0;
		currroute = currroute->next;

	}
	for (int front=0;front<3;front++)
		for (int t=0;t<supplylines[front]->groundbattle.usedteams;t++)
		{
			supplylines[front]->groundbattle.teamlist[t].lastlosses=0;
			supplylines[front]->groundbattle.teamlist[t].lastlostforces=0;
		}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessStoresArrival
//Author		R. Hyde 
//Date			Wed 12 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::ProcessStoresArrival ()
{
	SWord	storagespace,availablestores;

	SupplyRoute* currroute;
		
	currroute= &R0_0_1Rail0; 
	while (currroute->next->status != SR_LASTONE)
	{
		if (currroute->suppliee)
		{

			storagespace = currroute->suppliee->maxstorestonnes -
								currroute->suppliee->currentstores;
//DEADCODE DAW 25/06/99 											- StoresUsage (currroute->suppliee->supplyline,currroute->suppliee);
			if (storagespace <= 0)
			{
				currroute->suppliee->currentstores = currroute->suppliee->maxstorestonnes;
//DEADCODE DAW 25/06/99 													- StoresUsage (currroute->suppliee->supplyline,currroute->suppliee);
			}else
			{
				availablestores = (currroute->storeslaunched
												-  currroute->stores_destroyed_today);
				if (availablestores > storagespace)
					availablestores = storagespace;

				currroute->suppliee->priority = (SupplyPriority)
							(currroute->suppliee->priority*(storagespace - availablestores)/
														 storagespace);
				
				//if damagelevel high and stores added then storing in damaged wh
				if  (		(currroute->suppliee->currentstores == 0) 
						&&	(currroute->suppliee->attackstats.damagelevel > 60) //RDH 17/06/99
						&&	(availablestores > 0 )
					)
					MMC.DisDayEntry(Debrief::TARGUID, currroute->suppliee->associated_item, Debrief::T_USE_DAMAGED_WH_H);


				currroute->suppliee->currentstores += availablestores;
				if (currroute->suppliee->currentstores > ((96 * STORES_MAXSUPPLY) / 128))
		 			MMC.DisDayEntry(Debrief::DISCARDTARGUID, currroute->suppliee->associated_item, Debrief::T_Supply00_H);
				

			}
			currroute->totalstores_destroyed +=  currroute->stores_destroyed_today;
//inc aaalevel			if (currroute->stores_destroyed != 0)
//				currroute->consecutive_days_attacked++;
//			else
//				currroute->consecutive_days_attacked = 0;
			currroute->stores_destroyed_today = 
			currroute->storeslaunched = 0;
 		if (currroute->recommision_time <= MMC.debrief.currlogday)
 			currroute->status = SR_ACTIVE;

 		if (currroute->totalstores_destroyed > STORES_NO_TO_DESTROY_TO_REST_ROUTE)
 		{
 			currroute->totalstores_destroyed = 0;
 			currroute->recommision_time = MMC.debrief.currlogday + 5;
 			currroute->status = SR_RESTING;
 		}

	//TempCode RDH 12Mar97 		if (currroute->recommision_time < Time)
	//TempCode RDH 12Mar97 			status = SR_ACTIVE;

	//TempCode RDH 12Mar97 		if (currroute->totalstores_destroyed > STORES_NO_TO_DESTROY_TO_REST_ROUTE)
	//TempCode RDH 12Mar97 		{
	//TempCode RDH 12Mar97 			currroute->totalstores_destroyed = 0;
	//TempCode RDH 12Mar97 			currroute->recommision_time = Time + 5days;
	//TempCode RDH 12Mar97 			currroute->status = SR_RESTING;
	//TempCode RDH 12Mar97 		}
		}
		currroute = currroute->next;

	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FrontLineStoresUsage
//Author		R. Hyde 
//Date			Wed 12 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::FrontLineStoresUsage (SupplyLine* SL)
{
	SL->frontline->currentstores += StoresUsage (SL,SL->frontline);
	if (SL->frontline->currentstores < 0)
		SL->frontline->currentstores = 0;

}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetFirstSupplyNode
//Author		R. Hyde 
//Date			Thu 13 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::ResetFirstSupplyNode  (SupplyLine* SL)
{
	SL->firstnode->currentstores = SL->firstnode->maxstorestonnes;
	SL->firstnode->serviced = TRUE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessPreviousDaysSupplies
//Author		R. Hyde 
//Date			Wed 12 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::ProcessPreviousDaysSupplies()
{
	ResetPriorityAndServicedFlag();
	FrontLineStoresUsage (&WestRoute);
	FrontLineStoresUsage (&CentralRoute);
	FrontLineStoresUsage (&EastRoute);
	ProcessStoresArrival ();
	ResetFirstSupplyNode (&WestRoute);
	ResetFirstSupplyNode (&CentralRoute);
	ResetFirstSupplyNode (&EastRoute);
 	
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpDateAttacksStructure()
//Author		R. Hyde 
//Date			7/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Attacks*	SupplyTree::GetAttacks(UniqueID uid)
{
			SupplyTree::Supply2UID rel;
			SupplyNode*		node=SupplyTree::FindSupplyNodeForItem(uid,&rel);
	return 	GetAttacks(uid,node,rel);
}
Attacks*	SupplyTree::GetAttacks(UniqueID uid,SupplyNode* node,SupplyTree::Supply2UID rel)
{
		Attacks* att=NULL;
		if (node)
			switch (rel)
			{	//S2U_NOTHERE=0,S2U_MAIN,S2U_AF0,S2U_AF1,S2U_AF2,S2U_ROUTE0,S2U_ROUTE1,S2U_ROUTE2
				case S2U_MAIN:
				{
					if (uid==node->associated_item)
						att = &node->attackstats;
					else
						att = &node->attackstown;
					break;
				}
				case S2U_ROUTE0:
				case S2U_ROUTE1:
				case S2U_ROUTE2:
				{
					att = &FindBridge(uid,
							node->route[rel-SupplyTree::S2U_ROUTE0])->attackstats;
					break;
				}
				case S2U_AF0:
				case S2U_AF1:
				case S2U_AF2:
				{
					AirFieldInfo* af = SupplyTree::FindAirfieldForItem(uid);
					att=&af->attackstats;

					break;
				}
			}
		return att;
}

void SupplyTree::UpDateAttacksStructure()
{
 	for (int i=0;i<Profile::MAX_PACKS;i++)
	{
		if (Todays_Packages.pack[i][0][0].uid)
		{
			SupplyTree::Supply2UID rel;
			SupplyNode*		node=SupplyTree::FindSupplyNodeForItem(Todays_Packages.pack[i].packagetarget,&rel);
			Attacks*	att;
			if (node)
			{
				att=GetAttacks(Todays_Packages.pack[i].packagetarget,node,rel);
				//0, 32 92 152 212 255
				enum	{aaalevelcut=100,aaaleveldelta=60};
				if (att->aaalevel < 32)
					att->aaalevel = 32;
				else if (att->aaalevel > 195)
					att->aaalevel = 255;
				else
					if (att->aaalevel > aaalevelcut)
						att->aaalevel += aaaleveldelta;
					else
					{	//if any 1 node goes through 150 then test all nodes to get message
						att->aaalevel += aaaleveldelta;
						if (att->aaalevel > aaalevelcut)
							switch (rel)
							{
							case S2U_MAIN:
							{	//check all nodes
								for (SupplyNode* node=FirstNode;node->next!=node;node=node->next)
									if (node->attackstats.aaalevel<aaalevelcut)
										break;
								if (node->next==node)
									MMC.DisDayEntry(Debrief::TARGUID,Todays_Packages.pack[i].packagetarget,Debrief::D_Flak01_H);	break;
							}
							break;
							case S2U_ROUTE0:
							case S2U_ROUTE1:
							case S2U_ROUTE2:
							{	//routes: check all rail or road as appropriate
								SupplyRoute*	route=FindBridge(Todays_Packages.pack[i].packagetarget,node->route[rel-SupplyTree::S2U_ROUTE0]);
								int wagonsize=0;
								if (route->associated_brdg)
									for (route=FirstRoute;route->next!=route;route=route->next)
									{
										if (route->associated_brdg && route->attackstats.aaalevel<aaalevelcut)
											break;
									}
								else
								{
									wagonsize=route->storespermobile;
									for (route=FirstRoute;route->next!=route;route=route->next)
									{
										if (!route->associated_brdg && route->storespermobile==wagonsize && route->attackstats.aaalevel<aaalevelcut)
											break;
									}
								}
								if (route->next==route)
									switch (wagonsize)
									{
									case 0:				MMC.DisDayEntry(Debrief::TARGUID,Todays_Packages.pack[i].packagetarget,Debrief::D_Flak03_H);	break;
									case STORES_TRUCK:	MMC.DisDayEntry(Debrief::TARGUID,Todays_Packages.pack[i].packagetarget,Debrief::D_Flak02_H);	break;
									case STORES_TRAIN:	MMC.DisDayEntry(Debrief::TARGUID,Todays_Packages.pack[i].packagetarget,Debrief::D_Flak00_H);	break;
									}

							}
							break;
							case S2U_AF0:
							case S2U_AF1:
							case S2U_AF2:
							{	//check all red airfields

								AirFieldInfo* af = SupplyTree::FindAirfieldForItem(Todays_Packages.pack[i].packagetarget);
								att=&af->attackstats;

							}
							break;
							}
				}
				att->daylasthit = MMC.debrief.currlogday+1;		//0 indicates never hit
				att->actypelasthit = Todays_Packages.pack[i][0][0].squadron;

			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DestroyedStores
//Author		R. Hyde 
//Date			 //RDH 27/05/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	SupplyTree::DestroyedStores(SupplyNode* node)
{
	int destroyedstores;
   
	int tokens = node->attackstats.tokensinmw + node->attackstats.tokensinbf;
	
	if (tokens <= 0)
		  destroyedstores = 0;
	else
	{
		destroyedstores =  node->currentstores * node->attackstats.damagedtokens;
		destroyedstores = destroyedstores/tokens;  
	}
	return (destroyedstores);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveDestroyedStores
//Author		R. Hyde 
//Date			 //RDH 27/05/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	SupplyTree::RemoveDestroyedStores()
{
	SupplyNode* currnode;

	currnode = &N0_0_Dangdong;
	while (currnode->next->type != LASTONE)
	{
		currnode->currentstores -= DestroyedStores(currnode);
		if (currnode->currentstores < 0)							  //RDH 22/06/99
			currnode->currentstores = 0;							  //RDH 22/06/99
		currnode = currnode->next;
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NodeReview
//Author		R. Hyde 
//Date			Mon 10 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SupplyTree::NodeReview ()
{
	ProcessPreviousDaysSupplies();
	ProcessFrontLineRequests();
	SupplyHPNodes();

//DEADCODE RDH 23/03/99 	ProcessAirFields();
	GenerateSupplyDIS();
}

//higher value are higher priority. Mul by 10 to give full priority.

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NodeReview
//Author		R. Hyde 
//Date			Mon 10 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool SupplyTree::ChkSpringOffensiveOver()
{
	if 	(		(WestRoute.frontline == &N1_6_Sukchon)
			||	(WestRoute.frontline == &N3_3_Chonan)
			||	(CentralRoute.frontline == &N1_29_Kangdong)
			||	(CentralRoute.frontline == &N3_5_Chechon)
			||	(EastRoute.frontline == &N1_20_Kowon)
			||	(EastRoute.frontline == &N2_28_Samchok)
		)
		return (true);
	else
		return (false);
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NodeReview
//Author		R. Hyde 
//Date			Mon 10 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int SupplyTree::FindBattleIndex()
{
	SupplyRoute*  currroute;

	int index = 1;
	if 	(WestRoute.frontline == &N1_6_Sukchon)
		index = 0;
	else if	(WestRoute.frontline == &N3_3_Chonan)
		index = 7;
	else
	{
		int count = 0;
		SupplyNode*  currnode = WestRoute.firstnode;

		while (			(count < 80)
					&&	(currnode->forward != NULL)
					&&	(WestRoute.frontline != currnode)
				)
		{
			if (currnode->type == BATTLEFIELD)
				index++;
			currroute = currnode->forward;
			currnode = currroute->suppliee;		
			count++;
		}

	}
	return(index);
}



enum	ConflictDecisionPercents
		{
			MAX_DEAD=5,								//force between 0..5% of army faced may as well be wiped
			MAX_ALWAYS_WITHDRAW=20,					//force between 5 and 20% will always withdraw
			EXTRA_HURT_DEFENDERS=25,
			MIN_FORWARD_TO_ATTACK=40,				//won't move forward to attack next occ pos until got 40% their strength or better
			MAX_RND_WITHDRAW_REINFORCE=40,			//force between 20 and 40% will either wait for reinforcements or withdraw
			MAX_ALWAYS_REINFORCE=60,				//force between 40 and 70% of opp strength will always wait
			MAX_RND_REINFORCE_ATTACK=90,			//force between 70 and 90 may wait or go for it
			MAX_SEND_REINFORCE=95,					//won't send extra reinforcements above this fig
			MAX_ATTACK_DONTSPLIT=400,				//force over 4* can send reinforcements to others
///			MAX_ALWAYS_ATTACK=2000					//inverse of 5% - bigger force just goes for it
		};

enum	{	PLAYER_PROPORTION_ATTACKER=45,	//bigger means less player effect			
			PLAYER_PROPORTION_DEFENDER=35,	//Holder gets applied as well.
			PLAYER_PROPORTION_RETREAT=25,
			PLAYER_PROPORTION_CONVOY=35,
			PLAYER_PROPORTION_HOLDER=55,

			ATTACK_PROPORTION_AUTO=20,		//bigger means less ground battle effect

			STORES_TO_TROOPS_INITIAL=8,	//average - info only
			STORES_TO_REDTROOPS_REINFORCE=3,
			MAXSTORES_TO_BLUETROOPS_REINFORCE=8,
			STORES_TROOPS_PER_PERIOD=140,			//bigger means less stores used
			OVERWHELMING_TROOPS_PROPORTION_WIN=20
		};
	
inline bool	SameSide(TeamDef* us,TeamDef* them)		//BOTH MUST BE NON-NULL!
{	return (us->team==them->team);	}	


inline	int	CalcChanceMods(TeamDef* attacker,SuperBattleNode::IntraLink* attackpos,
							 TeamDef* defender,SuperBattleNode* defendpos)
{
	int	advmod=attackpos->TerrainAdvantage();
	if (!(defendpos->flanks.nonlinks&defendpos->flanks.NOT_ML))
		if (defendpos->flanks.leftnode->occupier)
			if (SameSide(defender,defendpos->flanks.leftnode->occupier))
				advmod+=10;
			else
				advmod-=10;
	if (!(defendpos->flanks.nonlinks&defendpos->flanks.NOT_MR))
		if (defendpos->flanks.rightnode->occupier)
			if (SameSide(defender,defendpos->flanks.rightnode->occupier))
				advmod+=10;
			else
				advmod-=10;
	if (attacker->forcetype==attacker->TROOPSONLY)
		advmod+=10;
	if (attacker->forcetype==attacker->ARTILLARY)
		advmod+=10;
	if (defender->forcetype==defender->TROOPSONLY)
		advmod-=10;
	if (defender->forcetype==defender->ARTILLARY)
		advmod-=20;
	//Additional modifiers required for:
	//	distant artillary
	return advmod;

}

inline	int	CalcAttackChance(TeamDef* attacker,SuperBattleNode::IntraLink* attackpos,
							 TeamDef* defender,SuperBattleNode* defendpos)
{
	int advantage=attacker->strength*100/defender->strength;
	int	advmod=CalcChanceMods(attacker,attackpos,defender,defendpos);
	return advantage+advmod;
}
inline	int	CalcDefendChance(TeamDef* attacker,SuperBattleNode::IntraLink* attackpos,
							 TeamDef* defender,SuperBattleNode* defendpos)
{
	int advantage=defender->strength*100/attacker->strength;
	int	advmod=CalcChanceMods(attacker,attackpos,defender,defendpos);
	return advantage-advmod;
}

bool	Better(int h,int l)
{
	if (l==h)
		return (Math_Lib.rnd(2)==0);
	else
		return (h>l);
}

inline	void	MergeForces(TeamDef* benefitters,TeamDef* dissolvers)
{
	if (benefitters->forcetype==TeamDef::TROOPSONLY
		|| (	dissolvers->forcetype!=TeamDef::TROOPSONLY 
			&&	dissolvers->strength>benefitters->strength
		)	)
		benefitters->forcetype=dissolvers->forcetype;
	benefitters->strength+=dissolvers->strength;
	benefitters->lastlosses+=dissolvers->lastlosses;
	benefitters->lastlostforces+=dissolvers->lastlostforces;
	dissolvers->strength=-1;
}

bool	BattleStruct::NextAttackDecision(TeamDef* us)	
{	//returns true if force disbanded!
typedef	TeamDef	T;
T::Action	decision=T::STAY_HERE;
T::Action	nameddecision=T::STAY_HERE;
	int			routenum=0;
	UniqueID	teleloc=us->location;
	UniqueID	nextloc=us->location;
	us->DiagnosticOutput("NextMove a");
	SuperBattleNode* nextnode=us->node;
	//this team is on team->node
	SuperBattleNode* node=us->node;
	TeamDef* them;
	SuperBattleNode::IntraLink	*fwd=&node->in,*back=&node->out;
	us->namedaction=TeamDef::STAY_HERE;					//in case nothing better gets set...
	us->advantagepriority=us->strength/10;
	if (us->team==T::HOME)
	{	fwd=&node->out;back=&node->in;	}

	if (node)
		if (node->occupier==us)		//main node
		{
			if ((them=fwd->occupier)!=NULL)
				if (SameSide(us,them))
				{	//silly case: force in front will have to come back and merge with us
					decision=T::STAY_HERE;
				}
				else
				{	//enemy force ahead. Either defend or pull back	
					int attackadvantage=CalcDefendChance(them,fwd,us,node);
					us->advantagepriority=attackadvantage;
					if (attackadvantage<MAX_DEAD)
						decision=T::LOSE_FORCE;
					else if (attackadvantage<MAX_ALWAYS_WITHDRAW)
						nameddecision=decision=T::RETREAT;
					else if (attackadvantage<MAX_RND_WITHDRAW_REINFORCE && Math_Lib.rnd(2))
						nameddecision=decision=T::RETREAT;
					else if (attackadvantage<MAX_ATTACK_DONTSPLIT)
						decision=T::STAY_HERE,nameddecision=T::DEFEND_ATTACK;
					else
					{	//can send some troops to other locations
						decision=T::STAY_HERE,nameddecision=T::DEFEND_ATTACK;		//NOT HANDLING SPLITS YET!
					}
					if (decision==T::RETREAT)
					{	//may not be able to retreat - then stay here!
						if (back->occupier)
							if (SameSide(us,back->occupier))
							{
								nextloc=teleloc=back->uid;
								decision=T::MERGE_FORCE;
							}
							else
								decision=T::STAY_HERE,nameddecision=T::DEFEND_ATTACK;
						else
							if (us->team==T::HOME)
								if (!node->innode)
									decision=T::STAY_HERE,nameddecision=T::DEFEND_ATTACK;
								else
								{
									SuperBattleNode::IntraLink* back2=&node->innode->out;
									if (back2->occupier && !SameSide(us,back2->occupier))
										decision=T::STAY_HERE,nameddecision=T::DEFEND_ATTACK;
									else
									{
										decision=T::RETREAT;
										teleloc=back->uid;
										nextloc=back2->uid;
										nextnode=node->innode;
									}
								}
							else	//away
								if (!node->firstoutnode)
									decision=T::STAY_HERE,nameddecision=T::DEFEND_ATTACK;
								else
								{
									SuperBattleNode* backnode=node->firstoutnode;
									decision=T::STAY_HERE,nameddecision=T::DEFEND_ATTACK;
									while (backnode && backnode->innode==node)
									{
										SuperBattleNode::IntraLink* back2=&backnode->in;
										if (!back2->occupier || SameSide(us,back2->occupier))
										{
											nameddecision=decision=T::RETREAT;
											teleloc=back->uid;
											nextloc=back2->uid;
											nextnode=backnode;
											break;
										}
										backnode=backnode->flanks.rightnode;
									}
								}
					}
				}	//end of defending against attack
			else
			{	//next node not occupied
				//SPECIAL RULES TO KEEP ARTILLARY BACK1 NODE NOT IMPLEMENTED!
				//need to choose best route to go down
				SuperBattleNode*	fwdnode;
				SuperBattleNode*	fwdnodenotnull;
				SuperBattleNode::IntraLink*			fwd2;
				if (us->team==T::HOME)
				{
					fwdnode=node->firstoutnode;
					fwd2=&fwdnode->in;
				}
				else
				{
					fwdnode=node->innode;
					fwd2=&fwdnode->out;
				}
				int	currroute=0;
				enum	{REENFORCENONEED=50,STAYBAD=100,TAKEEMPTYPRI=150,ATTACKENEMYPRI=300,
							ATTACKENEMYWAITREINFORCEPRI=301,	//want to attack enemy, but can't move forward until ready to attack!
							REINFORCEATT=200,REINFORCEDEFEND=250};
				int bestsofar=0;
				while (fwdnode)
				{
					if (fwd2->occupier)
						if (SameSide(us,fwd2->occupier))
						{	//REINFORCE option

							if (fwdnode->occupier && !SameSide(us,fwdnode->occupier))
							{	//ongoing conflict. Do they need help?
								int attackchance=MAX_SEND_REINFORCE-CalcAttackChance(fwd2->occupier,fwd2,fwdnode->occupier,fwdnode);
								if (attackchance>0)
									attackchance+=REINFORCEATT;
								else
									attackchance=REENFORCENONEED;
								if (Better(attackchance,bestsofar))
								{
									bestsofar=attackchance;
									decision=T::MOVE_FORWARD;
									nameddecision=T::MOVE_REINFORCE;
									routenum=currroute;
								}
							}
						}
						else
						{	//Can't go here- enemy occupied position
							if (Better(STAYBAD,bestsofar))
							{	//but must defend my current spot against them??
								bestsofar=STAYBAD;
								nameddecision=decision=T::STAY_HERE;
								routenum=currroute;
							}
						}
					else if (fwdnode->occupier)
						if (SameSide(us,fwdnode->occupier))
						{	//REINFORCE option
							SuperBattleNode::IntraLink*			fwd2fwd=&fwdnode->out;
							if (fwd2fwd==fwd2)	fwd2fwd=&fwdnode->in;
							if (fwd2fwd->occupier && !SameSide(us,fwd2fwd->occupier))
							{	//ongoing conflict. Do they need help?
								int attackchance=MAX_SEND_REINFORCE-CalcDefendChance(fwd2fwd->occupier,fwd2fwd,fwdnode->occupier,fwdnode);
								if (attackchance>0)
									attackchance+=REINFORCEATT;
								else
									attackchance=REENFORCENONEED;
								if (Better(attackchance,bestsofar))
								{
									bestsofar=attackchance;
									decision=T::MOVE_FORWARD;
									nameddecision=T::MOVE_REINFORCE;
									routenum=currroute;
								}
							}
						}
						else
						{	//Enemy node - consider attacking
							int attackchance=CalcAttackChance(us,fwd2,fwdnode->occupier,fwdnode);
							//check if there is a wait reinforce battlefield... otherwise must wait here!
							if (attackchance>MIN_FORWARD_TO_ATTACK)
								if (	attackchance>MAX_ALWAYS_REINFORCE
									||	(	(us->team==T::HOME && fwdnode->in.waitreinforcehere)
										||	(us->team==T::AWAY && fwdnode->out.waitreinforcehere)
									)	)
								{
									if (Better(ATTACKENEMYPRI,bestsofar))
									{
										bestsofar=ATTACKENEMYPRI;
										decision=T::MOVE_FORWARD;
										nameddecision=T::MOVE_TOATTACK;
										routenum=currroute;
										us->advantagepriority=attackchance;
									}
								}
								else
									if (Better(ATTACKENEMYWAITREINFORCEPRI,bestsofar))
									{
										bestsofar=ATTACKENEMYWAITREINFORCEPRI;
										nameddecision=T::WAIT_REINFORCE;
										decision=T::STAY_HERE;
										us->advantagepriority=attackchance;
									}


						}
					else
					{	//move forward to take vacant node
						if (Better(TAKEEMPTYPRI,bestsofar))
						{
							bestsofar=TAKEEMPTYPRI;
							nameddecision=decision=T::MOVE_FORWARD;
							routenum=currroute;
						}
					}
					currroute++;
					if (us->team==T::AWAY)
						fwdnode=NULL;
					else
					{
						fwdnode=fwdnode->flanks.rightnode;
						if (fwdnode)
							if (fwdnode->innode!=node)
								fwdnode=NULL;
							else
								fwd2=&fwdnode->in;
					}
				}	//end while all alternate routes
				//OK.. so now we know... move forward or stay here?
				if (decision==T::MOVE_FORWARD)
					if (us->team==T::HOME)
					{
						nextnode=node->firstoutnode;
						while (routenum--)
							nextnode=nextnode->flanks.rightnode;
						teleloc=node->out.uid;
						nextloc=nextnode->in.uid;
					}
					else
					{
						teleloc=node->in.uid;
						nextnode=node->innode;
						nextloc=nextnode->out.uid;
					}
			}
		}	//end of cental occupation
		else
		if (fwd->occupier==us)
		{	//IF WE ARE ON FORWARD NODE THEN MUST BE RETREATING
			//What are we retreating into?
			if (node->occupier)
				if (SameSide(us,node->occupier))
				{	//merge into holding force
					nextloc=teleloc=node->mainuid;
					decision=T::MERGE_FORCE;
				}
				else
				{	//fight past holding force
					nextloc=back->uid;
					if (fwd->retreatfromhere)
						nameddecision=decision=T::RETREAT_UNDER_FIRE;
					else
					{
						decision=T::TELEPORT;
						nameddecision=T::STAY_HERE;
						teleloc=back->uid;
					}
				}
			else
			{	//take node for 1 round... should have happened already...
				decision=T::TELEPORT;
				nameddecision=T::STAY_HERE;
				teleloc=node->mainuid;
				nextloc=node->mainuid;
			}
		}
		else
		if (back->occupier==us)
		{	//If we are on back node then we should consider attacking
			//other situation is if we have retreated through last node.
			if (node->occupier)
				if (SameSide(us,node->occupier))
				{	//merge into holding force
					nextloc=teleloc=node->mainuid;
					decision=T::MERGE_FORCE;
				}
				else
				{	//enemy force on main spot. Now what?
					int attackadvantage=CalcAttackChance(us,back,node->occupier,node);
					if (attackadvantage<MAX_DEAD)
						decision=T::LOSE_FORCE;
					else if (attackadvantage<MAX_ALWAYS_WITHDRAW)
						nameddecision=decision=T::RETREAT;
					else if (attackadvantage<MAX_RND_WITHDRAW_REINFORCE && Math_Lib.rnd(2))
						nameddecision=decision=T::RETREAT;
					else if (attackadvantage<MAX_ALWAYS_REINFORCE)
						decision=T::STAY_HERE,nameddecision=T::WAIT_REINFORCE;
					else if (attackadvantage<MAX_RND_REINFORCE_ATTACK && Math_Lib.rnd(2))
						decision=T::STAY_HERE,nameddecision=T::WAIT_REINFORCE;
					else if (attackadvantage<MAX_ATTACK_DONTSPLIT)
						nameddecision=decision=T::ATTACK;
					else
						nameddecision=decision=T::ATTACK;	  
					if (decision==T::STAY_HERE && !back->waitreinforcehere)
						nameddecision=decision=T::RETREAT;	//If can't stay here then go back
					if (decision==T::RETREAT)
					{
						if (us->team==T::HOME)
							if (!node->innode)
								decision=T::STAY_HERE,nameddecision=T::WAIT_REINFORCE;
							else
							{
								SuperBattleNode::IntraLink* back2=&node->innode->out;
								if (back2->occupier && !SameSide(us,back2->occupier))
									decision=T::STAY_HERE,nameddecision=T::WAIT_REINFORCE;
								else
								{
									decision=T::TELEPORT;
									nameddecision=T::STAY_HERE;
									teleloc=back->uid;
									nextloc=back2->uid;
									nextnode=node->innode;
								}
							}
						else	//away
							if (!node->firstoutnode)
								decision=T::STAY_HERE,nameddecision=T::WAIT_REINFORCE;
							else
							{
								SuperBattleNode* backnode=node->firstoutnode;
								decision=T::STAY_HERE,nameddecision=T::WAIT_REINFORCE;
								while (backnode && backnode->innode==node)
								{
									SuperBattleNode::IntraLink* back2=&backnode->in;
									if (!back2->occupier || SameSide(us,back2->occupier))
									{
										decision=T::RETREAT;
										teleloc=back->uid;
										nextloc=back2->uid;
										nextnode=backnode;
										break;
									}
									backnode=backnode->flanks.rightnode;
								}
							}

					}
					if (decision==T::STAY_HERE && !back->waitreinforcehere)
						nameddecision=decision=T::ATTACK;	//if can't go back and can't stay here then attack!
					if (decision==T::ATTACK)
						nextloc=node->mainuid;
				}
			else
			if (fwd->uid)	//not end of tree!!!
				{	//main node empty! Lets take it!
					decision=T::TELEPORT;
					teleloc=node->mainuid;
					nextloc=node->mainuid;
				}
		}
	else
	{	//new force needs injecting...	 CAN'T DO IT HERE!



	}
	//OK that's made some decisions... now need to set in stone.
	//first, the losers	
	if (decision==T::MERGE_FORCE)
	{	//if merge forces, then inherit better weaponry
		TeamDef* targ=node->occupier;
		if (node->in.uid==teleloc)
			targ=node->in.occupier;
		if (node->out.uid==teleloc)
			targ=node->out.occupier;

		MergeForces(targ,us);
		return false;
	}
	if (decision==T::LOSE_FORCE)
	{
		us->strength=-1;
		return false;
	}
	//now the winners.
	//stop others travelling our route
	//by setting us up as occupier
	if (decision==T::TELEPORT)
		decision=T::STAY_HERE;
//DEADCODE DAW 15/06/99 	us->lastlosses=0;
	us->action=decision;
	us->namedaction=nameddecision;
	if (teleloc!=us->location)
	{
		us->location=teleloc;
		if (node->mainuid==teleloc)
			node->occupier=us;
		else
		if (node->in.uid==teleloc)
			node->in.occupier=us;
		else
		if (node->out.uid==teleloc)
			node->out.occupier=us;
	}
	if (nextloc!=teleloc)
	{
		us->nextlocation=nextloc;
		us->nextnode=nextnode;
		if (nextnode->mainuid==nextloc && !node->occupier)
			nextnode->occupier=us;
		else
		if (nextnode->in.uid==nextloc && !node->in.occupier)
			nextnode->in.occupier=us;
		else
		if (nextnode->out.uid==nextloc && !node->out.occupier)
			nextnode->out.occupier=us;
	}
	us->DiagnosticOutput("NextMove b");
	return true;
}

bool	BattleStruct::PostAttackDecision(TeamDef* us)	
{	//THIS ROUTINE RESOLVES CONFLICTS ONLY!!
	//returns true if force disbanded!
	typedef	TeamDef	T;
	SuperBattleNode* node=us->node;
	TeamDef* them;
	SuperBattleNode::IntraLink	*fwd=&node->in,*back=&node->out;
	if (us->team==T::HOME)
	{	fwd=&node->out;back=&node->in;	}

	switch (us->action)
	{
	case	T::ATTACK:				//inner to main
	{	//calc losses due to fighting on both sides
		//did we wipe them out? Did they move out?
	us->DiagnosticOutput("PostAttack a");
		assert (back->occupier==us);
		if ((them=node->occupier)!=NULL)
			if (SameSide(us,them))
			{	//should not happen!!! Merge
				MergeForces(them,us);
				back->occupier=NULL;
				return false;
			}
			else
			{	//ho hum. The enemy are still there.
				//losses due to player
				them->lastlostforces+=them->strength*(them->lastlosses)/PLAYER_PROPORTION_ATTACKER;
				them->strength-=them->strength*(them->lastlosses)/PLAYER_PROPORTION_ATTACKER;
				us->lastlostforces=us->strength*(us->lastlosses)/PLAYER_PROPORTION_DEFENDER;
				us->strength-=us->strength*(us->lastlosses)/PLAYER_PROPORTION_DEFENDER;
				//they are fighting so lose 10% off both forces using opposite strengths
				them->strength-=us->strength/ATTACK_PROPORTION_AUTO;
				us->strength-=them->strength/ATTACK_PROPORTION_AUTO;
				//compare percentages to get extra losses
				int advantage=CalcAttackChance(us,back,them,node)+Math_Lib.rnd(20);
				if (advantage<100)
				{
					if (advantage>0)
						us->strength=us->strength*advantage/100;
					else
						us->strength==1;
					advantage=CalcAttackChance(us,back,them,node)+Math_Lib.rnd(20);
					if (advantage<MAX_DEAD)
					{	//ourforce is removed
						us->strength=-1;
						back->occupier=NULL;
						return false;
					}
				}
				else
				{
					advantage=CalcDefendChance(us,back,them,node)+Math_Lib.rnd(20);
					if (advantage<EXTRA_HURT_DEFENDERS)
					{
						if (advantage>0)
							them->strength=them->strength*advantage/EXTRA_HURT_DEFENDERS;
						else
							them->strength=-1;
						advantage=CalcDefendChance(us,back,them,node)+Math_Lib.rnd(20);
						if (advantage<MAX_DEAD)
						{	//they die. We move onto their hill.
							us->location=node->mainuid;
							us->nextlocation=UID_NULL;
							node->occupier=us;
							back->occupier=NULL;
							them->strength=-1;
							them->action=T::LOSE_FORCE;
						}
					}
					//nothing much else happens if no-one has advantage
				}
		
			}
		else
		{	//they moved out! We get node
			//(note: If they moved out they were teleported to the out point and then transported)
			us->nextnode=NULL;
			us->location=node->mainuid;
			node->occupier=us;
			back->occupier=NULL;
			us->nextlocation=UID_NULL;
		}
//DEADCODE DAW 15/06/99 		us->lastlosses=0;
//DEADCODE JIM 18/06/99 		us->action=T::STAY_HERE;
	}
	us->DiagnosticOutput("PostAttack a");
	break;
	case	T::RETREAT_UNDER_FIRE:	//outer to inner - could merge or take main if empty
	{
	us->DiagnosticOutput("PostAttack a");
		assert (fwd->occupier==us);
		//calc losses due to fighting
		if ((them=node->occupier)!=NULL)
			if (SameSide(us,them))
			{	//retreated past our own troops. Should not happen!
				MergeForces(them,us);
				fwd->occupier=NULL;
				return false;
			}
			else
			{	//did they wipe us out?
				int advantage=CalcAttackChance(us,fwd,them,node);
				us->lastlostforces+=us->strength*(us->lastlosses)/PLAYER_PROPORTION_RETREAT;
				us->strength-=us->strength*(us->lastlosses)/PLAYER_PROPORTION_RETREAT;
				us->strength=us->strength*advantage/200;	//tunable to ensure high losses even if advantage
				advantage=CalcAttackChance(us,fwd,them,node);
				if (advantage<MAX_DEAD)
				{	//ourforce is removed
					us->strength=-1;
					fwd->occupier=NULL;
					return false;
				}
				if ((them=back->occupier)!=NULL)
				{
					assert (SameSide(us,them));	//must be our side - merge for counter //DAW 23/06/99
					MergeForces(them,us);
					fwd->occupier=NULL;
					return false;
				}
				us->nextnode=NULL;			//otherwise we take the inner point with remaining force
				us->location=back->uid;
				us->nextlocation=UID_NULL;
				back->occupier=us;
				fwd->occupier=NULL;
			}
		else
		{	//they moved out! We take node!
			//(note: If they moved out they were teleported to the in point and then transported)
			us->nextnode=NULL;
			us->location=node->mainuid;
			us->nextlocation=UID_NULL;
			node->occupier=us;
			fwd->occupier=NULL;
		}
//DEADCODE DAW 15/06/99 		us->lastlosses=0;
//DEADCODE JIM 18/06/99 		us->action=T::STAY_HERE;
	us->DiagnosticOutput("PostAttack a");
	}
	break;
	default:;
	//	case	RETREAT,			//down road - could merge
	//	case	MOVE_FORWARD:		//up road - could merge
	//	case	TELEPORT:
	//	case	STAY_HERE:			//main or inner
	//		LOSE_FORCE,
	//		MERGE_FORCE,
	}
	return true;
}

bool	BattleStruct::PostMoveDecision(TeamDef* us)
{
	//returns true if force disbanded!
	typedef	TeamDef	T;
	SuperBattleNode* node=us->node;
	assert(node);
	TeamDef* them;

	if (us->action==T::MOVE_FORWARD || us->action==T::RETREAT)
	{
	us->DiagnosticOutput("PostMove a");
//DEADCODE DAW 26/04/99 #pragma warnmsg("Indentation troubles.")
		us->lastlostforces+=us->strength*(us->lastlosses)/PLAYER_PROPORTION_CONVOY;
		us->strength-=us->strength*(us->lastlosses)/PLAYER_PROPORTION_CONVOY;
		assert(node!=us->nextnode);
		if (	(us->team==T::HOME)==(us->action==T::MOVE_FORWARD)	)
		{
			assert(node->out.occupier==us)
			node->out.occupier=NULL;
		}
		else
		{
			assert(node->in.occupier==us);
			node->in.occupier=NULL;
		}
		node=us->nextnode;
		assert(node);
		us->node=us->nextnode;
		us->nextnode=NULL;
		us->location=us->nextlocation;
		us->nextlocation=UID_NULL;
			//need to check if should move to main node or merge here or at main node
		SuperBattleNode::IntraLink	*back=&node->out;
		if (	(us->team==T::HOME)==(us->action==T::MOVE_FORWARD)	)
			back=&node->in;
		assert (back->uid==us->location || node->mainuid==us->location);
		if ((them=back->occupier)!=NULL && them!=us)
		{
			assert (SameSide(us,them))
			MergeForces(them,us);
			return false;
		}
		else
			if ((them=node->occupier)!=NULL)
				if (SameSide(us,them))
				{
					MergeForces(them,us);
					return false;
				}
				else
				{	//set up to attack them
					back->occupier=us;
					us->location=back->uid;
				}
			else
			{
				us->location=node->mainuid;
				node->occupier=us;
			}
		us->DiagnosticOutput("PostMove b");
	}
	else
		if (us->action==T::STAY_HERE)
		{
			us->DiagnosticOutput("PostMove a");
			us->lastlostforces+=us->strength*(us->lastlosses)/PLAYER_PROPORTION_HOLDER;
			us->strength-=us->strength*(us->lastlosses)/PLAYER_PROPORTION_HOLDER;
		}
		//else others already covered.
	return true;
}

bool	BattleStruct::NextAttackDecisions()
{
	assert(usednodes || !usedteams);
	LinkTeams();
	for (int i=0;i<usedteams;i++)
		if (!teamlist[i].location)
		{	//new force needs injecting!
			SuperBattleNode* node=NULL;
			if (teamlist[i].team==TeamDef::HOME)
			{
				node=homenodes; //have to go in here!
			}
			else
			{
				SuperBattleNode* trynode=awaynodes;
				int score=-10000;									  //JIM 01/06/99
				enum {EMPTY=40,OCCSAME=30,OCCDIFF=10,NOTANKS=20};
				while (trynode)
				{
					if (!trynode->occupier)
						if (!(trynode->out.terrain&SuperBattleNode::IntraLink::TANKSLOST))
						{
							if (Better(NOTANKS,score))	//any route flagged no tanks is poor
							{							//as trucks will get stopped too!
								score=NOTANKS;
								node=trynode;
							}
						}
						else
						{
							if (Better(EMPTY,score))	  //usable empty square is best
							{
								score=EMPTY;
								node=trynode;
							}
						}
					else
						if (trynode->occupier->forcetype==teamlist[i].forcetype)
						{							//consider merging with same force type
							if (Better(OCCSAME-trynode->occupier->strength/100,score))
							{
								score=OCCSAME-trynode->occupier->strength/100;
								node=trynode;
							}
						}
						else
						{							//consider merging with diff force type
							if (Better(OCCDIFF-trynode->occupier->strength/100,score))
							{
								score=OCCDIFF-trynode->occupier->strength/100;
								node=trynode;
							}
						}
					trynode=trynode->flanks.rightnode;
				}
			}
			//so teleport new force to selected node...
			if (!node->occupier)
			{	//can teleport there
				teamlist[i].action=TeamDef::STAY_HERE;
				teamlist[i].namedaction=TeamDef::NEW_FORCE;
				teamlist[i].advantagepriority=teamlist[i].strength/10;
				teamlist[i].location=node->mainuid;
				teamlist[i].node=node;
				node->occupier=teamlist+i;
			}
			else
			{
				teamlist[i].action=TeamDef::MERGE_FORCE;
				MergeForces(node->occupier,&teamlist[i]);
				node->occupier->namedaction=TeamDef::NEW_FORCE;
				node->occupier->advantagepriority=node->occupier->strength/10;
			}
			teamlist[i].DiagnosticOutput("NewForce");

		}
		else
			NextAttackDecision(teamlist+i);
	int teamdif=0;					//compaction factor
	for ( i=0;i<usedteams;i++)
		if (teamlist[i].strength<=0)
			teamdif++;
		else
			if (teamdif)
				teamlist[i-teamdif]=teamlist[i];
	usedteams-=teamdif;
	for (i=usedteams;i<MAXTEAMS;i++)
		teamlist[i].strength=0;
	LinkTeams();
	return true;	//probably return false if end of battle
}
bool	BattleStruct::PostAttackDecisions()
{
	assert(usednodes || !usedteams);
	LinkTeams();
	for (int i=0;i<usedteams;i++)
		if (teamlist[i].location)
			PostAttackDecision(teamlist+i);

	int teamdif=0;					//compaction factor
	for ( i=0;i<usedteams;i++)
		if (teamlist[i].strength<=0)
			teamdif++;
		else
			if (teamdif)
				teamlist[i-teamdif]=teamlist[i];
	usedteams-=teamdif;
	for (i=usedteams;i<MAXTEAMS;i++)
		teamlist[i].strength=0;

	LinkTeams();
	for ( i=0;i<usedteams;i++)
		if (teamlist[i].location)
			PostMoveDecision(teamlist+i);

	teamdif=0;					//compaction factor
	for ( i=0;i<usedteams;i++)
		if (teamlist[i].strength<=0)
			teamdif++;
		else
			if (teamdif)
				teamlist[i-teamdif]=teamlist[i];
	usedteams-=teamdif;

	for (i=usedteams;i<MAXTEAMS;i++)
		teamlist[i].strength=0;

	LinkTeams();
	
	return true;	//probably return false if end of battle
}

void	SupplyLine::NextAttackReports()
{
	TeamDef::Team	blueteam=TeamDef::AWAY;
	if (initiative==REDATTACKING)
		blueteam=TeamDef::HOME;
	else
		return;
	for (int i=0;i<groundbattle.usedteams;i++)
		if (groundbattle.teamlist[i].team==blueteam)
		{
			if (groundbattle.teamlist[i].advantagepriority<MAX_RND_WITHDRAW_REINFORCE)
				if (groundbattle.teamlist[i].action==TeamDef::STAY_HERE)
					MMC.DisDayEntry(Debrief::DISCARDTARGUID,frontline->associated_item, Debrief::T_FAC01_H);

			if (	groundbattle.teamlist[i].node 
				&&	groundbattle.teamlist[i].node->flanks.leftnode==NULL
				&&	groundbattle.teamlist[i].node->flanks.rightnode!=NULL
				)
			{
				SuperBattleNode* n;
				bool	someonemovedup=false;
				for (n=groundbattle.teamlist[i].node;n;n=n->flanks.rightnode)
				{
					breakif (!n->occupier || n->occupier->team!=blueteam);	//stop on any gap or red
					if (n->occupier->action!=TeamDef::STAY_HERE)
						someonemovedup=true;
				}
				if (!n && someonemovedup)
					MMC.DisDayEntry(Debrief::DISCARDTARGUID,frontline->associated_item, Debrief::T_FAC03_H);
			}

			if (blueteam==TeamDef::HOME)
			{
				SuperBattleNode* n=NULL;
				for (n=groundbattle.teamlist[i].node->innode;n;n=n->innode)
					breakif(n->occupier &&  n->occupier->team!=blueteam);	//stop on red only
				if (n)
					if (n->occupier->action==TeamDef::STAY_HERE)
						MMC.DisDayEntry(Debrief::DISCARDTARGUID,frontline->associated_item, Debrief::T_FAC04_H);
					else
						MMC.DisDayEntry(Debrief::DISCARDTARGUID,frontline->associated_item, Debrief::T_Army01_H);
			}
		}
		else
		{

		}
}

void	SupplyLine::PostAttackReports()
{
	if (initiative!=REDATTACKING && initiative!=BLUEATTACKING)
		return;
	if (!groundbattle.usednodes)
		return;														  //JIM 11/06/99
	TeamDef::Team	blueteam=TeamDef::AWAY;
	int	bluestoresinuse=0;		//10 troops = 1 stores
	int redstoresinuse=0;
	if (initiative==REDATTACKING)
		blueteam=TeamDef::HOME;
//DeadCode DAW 27Jun99 	else
//DeadCode DAW 27Jun99 		return;
	for (int i=0;i<groundbattle.usedteams;i++)
	{
		if (groundbattle.teamlist[i].team==blueteam)
		{
			bluestoresinuse+=groundbattle.teamlist[i].strength;
			if (groundbattle.teamlist[i].lastlosses>5)
				MMC.DisDayEntry(Debrief::DISCARDTARGUID,frontline->associated_item, Debrief::T_FAC02_H);
		}
		else
		{
			redstoresinuse+=groundbattle.teamlist[i].strength;
			if (groundbattle.teamlist[i].lastlosses>8)
				MMC.DisDayEntry(Debrief::DISCARDTARGUID,frontline->associated_item, Debrief::T_FAC00_H);
		}
		if (	groundbattle.teamlist[i].team==TeamDef::HOME)
		{
			if (!groundbattle.teamlist[i].node->firstoutnode
				&&	groundbattle.teamlist[i].node->occupier==&groundbattle.teamlist[i]
				)
				if (initiative==REDATTACKING)
					initiative=REDLOST;
				else
				if (initiative==BLUEATTACKING)
					initiative=BLUELOST;
		}
		else
		if (	groundbattle.teamlist[i].team==TeamDef::AWAY)
		{
			if (	!groundbattle.teamlist[i].node->innode
				&&	groundbattle.teamlist[i].node->occupier==&groundbattle.teamlist[i]
				)
				if (initiative==REDATTACKING)
					initiative=REDWON;
				else
				if (initiative==BLUEATTACKING)
					initiative=BLUEWON;
		}
	}
	DiagnosticOutput(0,"Supplies");
	if (frontline->currentstores-redstoresinuse/STORES_TROOPS_PER_PERIOD>0)
		frontline->currentstores-=redstoresinuse/STORES_TROOPS_PER_PERIOD;	
	else
	{
		frontline->currentstores=STORES_STANDARDSUPPLY;
		if (initiative==REDATTACKING)
			initiative=REDLOST;
		else
		if (initiative==BLUEATTACKING)
			initiative=BLUEWON;
	}
	if (redstoresinuse>OVERWHELMING_TROOPS_PROPORTION_WIN*bluestoresinuse)
		if (initiative==REDATTACKING)
			initiative=REDWON;
		else
		if (initiative==BLUEATTACKING)
			initiative=BLUELOST;
	if (bluestoresinuse>OVERWHELMING_TROOPS_PROPORTION_WIN*redstoresinuse)
		if (initiative==REDATTACKING)
			initiative=REDLOST;
		else
		if (initiative==BLUEATTACKING)
			initiative=BLUEWON;
	int slnum;

	if (initiative!=REDATTACKING && initiative!=BLUEATTACKING)
		ExitBf();

	if (this==&SupplyTree::WestRoute)
		slnum=0;
	else
	if (this==&SupplyTree::CentralRoute)
		slnum=1;
	else
////if (this==&SupplyTree::EastRoute)
		slnum=2;
	DiagnosticOutput(0,"Remaining");

	if (frontline->currentstores>STORES_TOINITIATEASSAULT)	 //400
		if (Math_Lib.rnd(2))
		{	//inject extra red force
			TeamDef* team=groundbattle.teamlist+groundbattle.usedteams++;
			team->strength=frontline->currentstores/STORES_TO_REDTROOPS_REINFORCE;
			int	forcetype=Math_Lib.rnd(5);
			team->team=(blueteam==TeamDef::AWAY)?TeamDef::HOME:TeamDef::AWAY;
			team->forcename=forcenames[slnum][1][forcetype]+Math_Lib.rnd(5);
			team->forcetype=TeamDef::ForceType(forcetype);
			team->action=TeamDef::STAY_HERE;
			team->namedaction=TeamDef::NEW_FORCE;
			team->location=UID_NULL;
			team->nextlocation=UID_NULL;
			team->lastlosses=0;
			team->lastlostforces=0;
			team->node=NULL;
			team->nextnode=NULL;
		}
	if (Math_Lib.rnd(2)==0)
	{	//inject extra blue force
		TeamDef* team=groundbattle.teamlist+groundbattle.usedteams++;
		team->strength=frontline->maxstorestonnes/MAXSTORES_TO_BLUETROOPS_REINFORCE;
		int	forcetype=Math_Lib.rnd(5);
		team->team=blueteam;
		team->forcename=forcenames[slnum][0][forcetype]+Math_Lib.rnd(5);
		team->forcetype=TeamDef::ForceType(forcetype);
		team->action=TeamDef::STAY_HERE;
		team->namedaction=TeamDef::NEW_FORCE;
		team->location=UID_NULL;
		team->nextlocation=UID_NULL;
		team->lastlosses=0;
		team->lastlostforces=0;
		team->node=NULL;
		team->nextnode=NULL;
	}


}
bool	BattleStruct::BattleField(int teamnum,FileNum& fil,UniqueID& src,UniqueID& trg,int& mainforce,int& extraforce)
{	//return true if outward from src
	fil=FIL_NULL;
	TeamDef* us=teamlist+teamnum;
	if (us->strength==0)
		return false;
	typedef	TeamDef	T;
	SuperBattleNode* node=us->node;
	mainforce=us->strength/80;
	extraforce=0;
	if (mainforce>10)
	{
		extraforce=mainforce-10;
		if (extraforce>6)
			extraforce=6;
		mainforce=10;
	}
	if (us->team==T::HOME)
		switch(us->action)
		{
		case	T::MERGE_FORCE://should never happen
		case	T::LOSE_FORCE:	//should never happen
		case	T::TELEPORT:	//should never happen
		case  	T::STAY_HERE:
			if (node->occupier==us)
			{
				fil=node->out.defendmain;
				src=node->mainuid;
				trg=node->out.uid;
				return	true;
			}
			else
			{	assert (node->in.occupier==us);
				fil=node->in.waitreinforcehere;
				src=node->in.uid;
				trg=node->mainuid;
				return	true;
			}
		case	T::MOVE_FORWARD:
		{
			fil=us->nextnode->innerlink.homeapproach;
			src=node->out.uid;
			trg=us->nextnode->in.uid;
			return	true;
		}
		case	T::ATTACK:
		{
			fil=node->in.attackmain;
			src=node->in.uid;
			trg=node->mainuid;
			//in this case, extraforce represents flanking...
			if (!(	(	(node->flanks.nonlinks&SuperBattleNode::FlankLink::NOT_ML) 
					|| 	(!node->flanks.leftnode->occupier)
					||	SameSide(us,node->flanks.leftnode->occupier)
					)
				&&	(	(node->flanks.nonlinks&SuperBattleNode::FlankLink::NOT_MR) 
					|| 	(!node->flanks.rightnode->occupier)
					||	SameSide(us,node->flanks.rightnode->occupier)
				))	)
				extraforce=0;
			return	true;
		}

		case	T::RETREAT:
		{
			fil=node->innerlink.homeretreat;
			src=node->in.uid;
			trg=us->nextnode->out.uid;
			return	false;
		}

		case	T::RETREAT_UNDER_FIRE:
		{
			fil=node->out.retreatfromhere;
			src=node->out.uid;
			trg=node->in.uid;
			return	false;
		}
		}
	else
		switch(us->action)
		{
		case	T::MERGE_FORCE://should never happen
		case	T::LOSE_FORCE:	//should never happen
		case	T::TELEPORT:	//should never happen
		case  	T::STAY_HERE:
			if (node->occupier==us)
			{
				fil=node->in.defendmain;
				src=node->mainuid;
				trg=node->in.uid;
				return	false;
			}
			else
			{	assert (node->out.occupier==us);
				fil=node->out.waitreinforcehere;
				src=node->out.uid;
				trg=node->mainuid;
				return	false;
			}
		case	T::MOVE_FORWARD:
		{
			fil=node->innerlink.awayapproach;
			src=node->in.uid;
			trg=us->nextnode->out.uid;
			return	false;
		}
		case	T::ATTACK:
		{
			fil=node->out.attackmain;
			src=node->out.uid;
			trg=node->mainuid;
			//in this case, extraforce represents flanking...
			if (!(	(	(node->flanks.nonlinks&SuperBattleNode::FlankLink::NOT_ML) 
					|| 	(!node->flanks.leftnode->occupier)
					||	SameSide(us,node->flanks.leftnode->occupier)
					)
				&&	(	(node->flanks.nonlinks&SuperBattleNode::FlankLink::NOT_MR) 
					|| 	(!node->flanks.rightnode->occupier)
					||	SameSide(us,node->flanks.rightnode->occupier)
				))	)
				extraforce=0;
			return	false;
		}

		case	T::RETREAT:
		{
			fil=us->nextnode->innerlink.awayretreat;
			src=node->out.uid;
			trg=us->nextnode->in.uid;
			return	true;
		}

		case	T::RETREAT_UNDER_FIRE:
		{
			fil=node->in.retreatfromhere;
			src=node->in.uid;
			trg=node->out.uid;
			return	true;
		}
		}

   fil=FIL_NULL;
   return true;
}
//static bool	Sh(UWord& v)	{v>>=1;return ((v&1)!=0);}

bool	BattleStruct::NewSetupFirstDay(const int* hometeamnames,const int* awayteamnames,int homestrength,int awaystrength)
{


	LinkBattleNodes();
	SuperBattleNode* away=awaynodes;

	int awaynodecount=0;
	while (away)
	{
		awaynodecount++;
		away=away->flanks.rightnode;
	}
	int	homenodecount=homestrength/(awaynodecount+1);
	awaynodecount=awaystrength/(awaynodecount+1);
	int homeskip=Math_Lib.rnd(20);	//this node left undefended, but 'cos rnd is high,,,
	away=awaynodes;
	TeamDef *team=teamlist;

	for (away=awaynodes;away;away=away->flanks.rightnode)
	{	//set up attackers:
		int forcetype=away->out.terrain&15;
		if ((away->out.terrain&32768)==0)
			forcetype=Math_Lib.rnd(13)/3;
		team->strength=awaynodecount*4+Math_Lib.rnd(5);		//STORES_TO_TROOPS_INITIAL
		awaystrength-=team->strength/STORES_TO_TROOPS_INITIAL;
		team->team=team->AWAY;
		team->forcename=awayteamnames[forcetype]+Math_Lib.rnd(5);
		team->forcetype=TeamDef::ForceType(forcetype);
		team->action=TeamDef::STAY_HERE;
		team->location=away->mainuid;
		team->nextlocation=UID_NULL;
		team->lastlosses=0;
		team->lastlostforces=0;
		team->node=away;
		team->nextnode=away;
		away->occupier=team;
		team++;

		//set up defenders
		if (homestrength>0)
			if (!away->innode->occupier)				  //DAW 26/04/99
			{
				forcetype=(away->out.terrain>>8)&15;
				if ((away->out.terrain&32768)==0)
					forcetype=Math_Lib.rnd(13)/3;
				team->strength=homenodecount*4+Math_Lib.rnd(5);		//STORES_TO_TROOPS_INITIAL
				homestrength-=team->strength/STORES_TO_TROOPS_INITIAL;
				team->team=team->HOME;
				team->forcename=awayteamnames[forcetype]+Math_Lib.rnd(5);
				team->forcetype=TeamDef::ForceType(forcetype);
				team->action=TeamDef::STAY_HERE;
				team->location=away->innerlink.uid;
				team->nextlocation=UID_NULL;
				team->lastlosses=0;
				team->lastlostforces=0;
				team->node=away->innode;
				team->nextnode=away->innode;
				away->innode->occupier=team;
				team++;
			}
			else
			{	//double team this defensive position!
				away->innode->occupier->strength+=homenodecount*5;
				homestrength-=homenodecount*5/10;
			}

	}
	LinkTeams();

	return true;
}





TeamDef*	BattleStruct::FindTeamAtLocation(UniqueID u)
{
   for (int team=usedteams-1;team>=0;team--)
	   if (teamlist[team].location==u)
		   return teamlist+team;
	return NULL;
}

void	SupplyTree::SetNodeNationalities(UniqueID eastfront,UniqueID centralfront,UniqueID westfront,int deltastrength)
{
	//first set all nodes to Blue
	for (SupplyNode* node=FirstNode;node->next!=node;node=node->next)
	{
		node->status=BEHINDBLUELINES;
//		node->attackstats.aaalevel=0;
	}
	node=FindSupplyNodeForNodeItem(eastfront);
	EastRoute.frontline=node;
	node->status=FRONTLINE;
	if (deltastrength)
	{
		node->currentstores+=deltastrength;
		if (node->currentstores>node->maxstorestonnes)
			node->currentstores=node->maxstorestonnes;
		if (node->currentstores<node->maxstorestonnes/2)
			node->currentstores=node->maxstorestonnes/2;
	}
	node=FindSupplyNodeForNodeItem(centralfront);
	CentralRoute.frontline=node;
	node->status=FRONTLINE;
	if (deltastrength)
	{
		node->currentstores+=deltastrength;
		if (node->currentstores>node->maxstorestonnes)
			node->currentstores=node->maxstorestonnes;
		if (node->currentstores<node->maxstorestonnes/2)
			node->currentstores=node->maxstorestonnes/2;
	}
	node=FindSupplyNodeForNodeItem(westfront);
	WestRoute.frontline=node;
	node->status=FRONTLINE;
	if (deltastrength)
	{
		node->currentstores+=deltastrength;
		if (node->currentstores>node->maxstorestonnes)
			node->currentstores=node->maxstorestonnes;
		if (node->currentstores<node->maxstorestonnes/2)
			node->currentstores=node->maxstorestonnes/2;
	}
	if (deltastrength>0)
	{
		EastRoute.initiative=REDINITIATIVE;
		EastRoute.initiative=BLUEINITIATIVE;
		WestRoute.initiative=REDINITIATIVE;
	}

	if (deltastrength<0)
	{
		WestRoute.initiative=BLUEINITIATIVE;
		CentralRoute.initiative=REDINITIATIVE;
		CentralRoute.initiative=BLUEINITIATIVE;
	}

	SupplyRoute* route;
	int routeind;
	bool	gotone=true;
	while(gotone)
		for (gotone=false,node=FirstNode;node->next!=node;node=node->next)
			if (node->status!=BEHINDBLUELINES)
				for (routeind=0;route=node->route[routeind],routeind<3;routeind++)
					if (route && route->supplier->status==BEHINDBLUELINES)
					{
						gotone=true;
						route->supplier->status=BEHINDREDLINES;
						if (route->supplier->attackstats.aaalevel<80)
							route->supplier->attackstats.aaalevel=80;
						if (route->attackstats.aaalevel<80)
							route->attackstats.aaalevel=80;
					}
	for (route=FirstRoute;route->next!=route;route=route->next)
		if (route->suppliee->status==BEHINDREDLINES)
			if (route->attackstats.aaalevel<60)
				route->attackstats.aaalevel=60;

	for (int af=0;airfieldinfo[af].nationality!=NAT_ALIGN;af++)
		if (	airfieldinfo[af].northnodes[0]->status==BEHINDBLUELINES
			&&	(	!airfieldinfo[af].northnodes[1]
				||	airfieldinfo[af].northnodes[1]->status==BEHINDBLUELINES
			)	)
		{
			airfieldinfo[af].nationality=NAT_BLUE;
			airfieldinfo[af].attackstats.aaalevel=0;
		}
		else
		if (	airfieldinfo[af].southnodes[0]->status==BEHINDREDLINES
			&&	(	!airfieldinfo[af].southnodes[1]
				||	airfieldinfo[af].southnodes[1]->status==BEHINDREDLINES
			)	)
		{
			airfieldinfo[af].nationality=NAT_RED;
			airfieldinfo[af].attackstats.aaalevel=60;
		}
		else
			airfieldinfo[af].nationality=NAT_AMBER;
}

