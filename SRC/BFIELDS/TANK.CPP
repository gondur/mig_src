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
//Filename       tank.cpp
//System         
//Author         R. Hyde 
//Date           Fri 9 Aug 1996
//Description    
//------------------------------------------------------------------------------
//Questions
//
//	Jobs
//		
//	In load	
//		
//	In endgame		
//		
//	if bfield is truck	
//		if trgt dead
//	 	 	remove truck convoy from Convoy array
//  		add gun to Miss_Man.currcamp->blueguns
//			
//		
//---------------------------------------------------------------------
//The first mission is a special so the first point where the campaign
//code is relevant is in the endgame
//------------------------------------------------------------------------------
//
//Special treatment for loading battlefields:
//
//D Routes:	they have no items but still need to be loaded
//
//D Convoys:	On map the convoy.uid field contains the uid of the waypoint that
//			convoy should start at.
//			On loading return the uid of the convoy leader to convoy.uid
//
//
//AAA:		For each entry in the bluegunlist make a blueaaasite (small bore)
//			return uid of aaa created to blueaaalist
//  			
//
//  ------------------------------------------------------------------------------
//  Jobs in 3d
//
//  When a tank kills a gun
//  	add truck entry to Miss_Man.currcamp->convoy array
//
//  When a truck reaches a waypoint with a dead gun
//  	remove truck convoy from Convoy array
//  	add gun to Miss_Man.currcamp->blueguns
//
//
//  logic for tanks:
//  	don't progress until enemy guns dead
//  	don't progress if bridge dead
//
//
//  ------------------------------------------------------------------------------
//  UIDs
//  	
//  airfields
//  ac
//  military for guns
//  ccc for hq/chat
//
//  sams tanks
//  GroundMobile for truck
//  red civ for bridges
//  gic	balloons
//  greenciv  towns
//
//
//  blue civ  - winch sites for balloons
//  port for tank site, rail heads 
//  port dumps
//  aaasite
//  redvetoed inconsequentials
//	bluevetoed	redcross
//  ------------------------------------------------------------------------------
//  Shapes/groups
//
//  GFLAK1GN	one flak truck
//  GARTILL		german artillery group 3 guns none on centre
//	tankdromes
//
//
//
//  ------------------------------------------------------------------------------
//	Extensions
//
//	Scout cars 
//	Blue artillery
//
//
//
#define F_GRAFIX
#define F_SOUNDS
#define F_COMMON

//DeadCode JIM 19Aug96 	#include	"bfcommon.h"
			#include	"dosdefs.h"
			#include	"text.h"
			#include	"persons2.h"
			#include	"savegame.h"
			#include	"missman2.h"
			#include	"enumbits.m"
			#include	"mymath.h"
			#include	"Mytime.h"			//CFont
			#include	"myerror.h"	
			#include	"node.h"
#define	QUICKQUICKQUICK
			#include	"squick1.h"
#include	"globrefs.h"
MissMan	Miss_Man;
//DeadCode JIM 19Aug96 	enum	BattlefieldType	{MAINWORLDBF = 0, BFMAXCOUNTER = 255,BFTYPE = 256,PLAYERBF = BFTYPE,
//DeadCode JIM 19Aug96 							ROUTEBF = 2*BFTYPE,CONVOYBF = 3*BFTYPE,
//DeadCode JIM 19Aug96 							AAABF =  4*BFTYPE,ENEMYACBF = 5*BFTYPE,
//DeadCode JIM 19Aug96 							CONVOYCOUNT = 6*BFTYPE, AAACOUNT = 7*BFTYPE,
//DeadCode JIM 19Aug96 							FINISHBF = 8*BFTYPE
//DeadCode JIM 19Aug96 							};
//DeadCode JIM 19Aug96 
//extern	ULong GR_WP1;
//extern	ULong GR_WP2;
//extern	ULong GR_ConvoyCount;
//extern	ULong GR_ConvoyUid;
//DeadCode RDH 02Dec96 extern	ULong GR_GunSite;
//extern	ULong GR_AAASite;
//extern	ULong
//
////DeadCode RDH 08Oct96 					GR_bluestrength,
//					GR_MainPosX,
//					GR_MainPosY,
//					GR_MainPosZ,
//					GR_SubPosX,
//					GR_SubPosY,
//					GR_SubPosZ,
//					GR_MainAction,		//RDH 05Dec96
//					GR_SubAction,		//RDH 05Dec96
//					GR_MainObjective,										//MS 21Jun96
//					GR_SubObjective;										//MS 21Jun96
BITABLE(Persons2::BattlefieldType);
MATHABLE(Persons2::BattlefieldType);


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSecondWP
//Author		R. Hyde 
//Date			Thu 17 Oct 1996
//
//Description		Miss_Man.camp.playerbfield==FIL_NULL when entering map
//						When entering map we don't want to increment wps
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADvoid	Persons2::SetSecondWP (WayPointPtr	tmpitem)
//DEAD{
//DEAD	UniqueIDBand	uidband;
//DEAD
//DEAD	if (tmpitem)
//DEAD	{
//DEAD		uidband = getbandfromUID((UniqueID)tmpitem->target->uniqueID.count);
//DEAD		if (uidband == RedMilitaryBAND)
//DEAD		{
//DEAD//DeadCode RDH 22Oct96 			if (tmpitem->target->Status.deadtime != 0)
//DEAD//DeadCode RDH 22Oct96 			{
//DEAD				if (Miss_Man.camp.playerbfield==FIL_NULL)
//DEAD				{
//DEAD					GR_WP2 = GR_WP1;
//DEAD				}else
//DEAD				{
//DEAD//DeadCode RDH 05Dec96 					if (tmpitem->next==NULL)
//DEAD//DeadCode RDH 05Dec96 						_Error.EmitSysErr("second waypoint null");
//DEAD//DeadCode RDH 05Dec96 					GR_WP2 = tmpitem->next->uniqueID.count;
//DEAD					if (tmpitem->next==NULL)					//RDH 05Dec96
//DEAD						GR_WP2 = GR_WP1;						//RDH 05Dec96
//DEAD					else										//RDH 05Dec96
//DEAD						GR_WP2 = tmpitem->next->uniqueID.count;	//RDH 05Dec96
//DEAD				}
//DEAD
//DEAD//DeadCode RDH 22Oct96 			}else
//DEAD//DeadCode RDH 22Oct96 			{
//DEAD//DeadCode RDH 22Oct96 				GR_WP2 = GR_WP1;
//DEAD//DeadCode RDH 22Oct96 			}
//DEAD		}else
//DEAD		{
//DEAD			if (tmpitem->target->Status.deadtime != 0)
//DEAD			{
//DEAD				GR_WP2 = GR_WP1;
//DEAD			}else
//DEAD			{
//DEAD				if (Miss_Man.camp.playerbfield==FIL_NULL)
//DEAD				{
//DEAD					GR_WP2 = GR_WP1;
//DEAD				}else
//DEAD				{
//DEAD//DeadCode RDH 05Dec96 					if (tmpitem->next==NULL)
//DEAD//DeadCode RDH 05Dec96 						_Error.EmitSysErr("second waypoint null");
//DEAD//DeadCode RDH 05Dec96 					GR_WP2 = tmpitem->next->uniqueID.count;
//DEAD					if (tmpitem->next==NULL)					//RDH 05Dec96
//DEAD						GR_WP2 = GR_WP1;						//RDH 05Dec96
//DEAD					else										//RDH 05Dec96
//DEAD						GR_WP2 = tmpitem->next->uniqueID.count;	//RDH 05Dec96
//DEAD				}
//DEAD			}
//DEAD		}
//DEAD	}else
//DEAD	{
//DEAD		GR_WP2 = GR_WP1;
//DEAD	}
//DEAD
//DEAD}
//DEAD
inline UniqueID operator--(UniqueID& u,int) {return u=UniqueID(u-1);}
inline Persons2::BattlefieldType operator +=(Persons2::BattlefieldType& u,int i){return u=Persons2::BattlefieldType(u+i);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindNextBf
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs	nextbftype	- state control variable
//
//Returns	filenumber, or null to skip this one
//			nextbftype updated - set to FINISHBF to quit
//			some globrefs updated
//------------------------------------------------------------------------------
UByte RndSq256()
{
	UWord rv=Math_Lib.rnd();
	rv=rv|(rv>>8);
	return (UByte)rv;
}

int	RndSq256(int v)
{
	return (v*RndSq256())>>8;
}
enum	{MIGDAYSOUTH,MIGDAYDIRECT,MIGDAYLATEBARCAP,MIGDAYALLBARCAP,MIGDAYBIGTRAIN};

#define	KeepIfNotLoaded(rv)	(BFLoaded(rv)?FIL_NULL:rv)
FileNum	Persons2::FindNextBf (BattlefieldType &nextbftype)
{
	static	UniqueID	playertarget;
	static	SupplyNode*	playernode;
	static	int			flighttakeoffstep;
	static	int			leftval,rightval;
	static	int			migdaytype;
	static	int		migcapstrength;
	static	int		migcaptime;
	GR_movecode=AUTO_FOLLOWWP;
	SupplyNode*	playernode2=playernode;
	UniqueIDBand	uidband;								//RDH 05Dec96
	BattlefieldType	n;
	WayPointPtr	tmpitem;
	if (Todays_Packages[0].packagetarget)
		GR_TruckMoveCode=GROUND_TOGLOBREF;
	else
		GR_TruckMoveCode=GROUND_TAXI;
	GR_GlobalSkillMin = SKILL_NOVICE;						//RDH 01Oct96
	GR_GlobalSkillMax = SKILL_HERO;							//RDH 01Oct96

	switch (nextbftype & BFPHASES)
	{
		case	MAINWORLDBF:
		{
			GR_BLUESKILLCONFIG=Save_Data.autopilotskillUN;
			GR_REDSKILLCONFIG=Save_Data.autopilotskillUN;
//				if (Todays_Packages[0][0][0].uid)
//				if (Todays_Packages[0].packagetarget)
//					nextbftype = ROUTEBF;
//				else
//					nextbftype = SCRAMBF;
//
			migcaptime=0;
			nextbftype = ROUTEBF;	//REMOVE MACCAS  IF STATEMENT EDITS HERE!
//You will find you have fewer bugs
//if you only have one return statment in a method. DAW
//
			return(FIL_1_mainmig);

		}

		case	ROUTEBF:	//populate the route!
		{	//populate other packages routes
			if (nextbftype==ROUTEBF)
			{	//set everything up... 
				//need to get UID and then get node record describing that item
				//Then, for each package not attacking that node 
				//launch it's target battlefield.
				//set everything up... 
				//need to get UID and then get node record describing that item
				//Then, for each package not attacking that node 
				//launch it's target battlefield.
				if (!Todays_Packages[0].packagetarget)
				{
					nextbftype=PLAYROUTEBF;
					return FIL_NULL;
				}
			}
			//Even means load package target
			//Odd means load next sub-target
			enum	{PACK_PHASES=2};
			int packnum=(nextbftype-ROUTEBF)/PACK_PHASES;
			int packphase=nextbftype-ROUTEBF-packnum*PACK_PHASES;
			
			UniqueID targ=Todays_Packages[packnum].packagetarget;
			FileNum rv=FIL_NULL;
			if (packphase==0)
			{
				UByte	aaalevel;
				if (targ)
					rv=SupplyTree::TargetToBf(targ,&aaalevel);
				GR_AAALevel64K=aaalevel<<8;
				nextbftype=BattlefieldType(int(nextbftype)+1);
				return	KeepIfNotLoaded(rv);
			}
			else
			{
				for (int wave=0;wave<Profile::MAX_WAVES;wave++)
					for (int grp=0;grp<Profile::MAX_GROUPS;grp++)
						for (int fl=0;fl<Todays_Packages[packnum][wave][grp].numflights;fl++)
								if (Todays_Packages[packnum][wave][grp][fl].globrefind)
								{
									if (	Todays_Packages[packnum][wave][grp][fl].primary.SGT
										&&	Todays_Packages[packnum][wave][grp][fl].primary.SGT!=targ
										)
									{	//do allow convoys
										UByte	aaalevel;
										rv=SupplyTree::TargetToBf(Todays_Packages[packnum][wave][grp][fl].primary.SGT,&aaalevel);
										GR_AAALevel64K=aaalevel<<8;
										if (rv)
											return KeepIfNotLoaded(rv);
									}
									if (	Todays_Packages[packnum][wave][grp][fl].secondary.SGT
										&&	Todays_Packages[packnum][wave][grp][fl].secondary.SGT!=targ
										)
									{
										UByte	aaalevel;
										rv=SupplyTree::TargetToBf(Todays_Packages[packnum][wave][grp][fl].secondary.SGT,&aaalevel);
										GR_AAALevel64K=aaalevel<<8;
										if (rv)
											return KeepIfNotLoaded(rv);
									}
								}
				nextbftype=BattlefieldType(int(nextbftype)+1);
				if (nextbftype>=ROUTEBF+Profile::MAX_PACKS*PACK_PHASES)
					nextbftype=PLAYROUTEBF;
				return FIL_NULL;
			}
		}
		case	PLAYROUTEBF:
		{	//for the player's target area, launch all neighboring battlefields
			FileNum rv=FIL_NULL;
			switch (nextbftype)
			{
			case	PLAYROUTEBF:
				rv=FIL_NULL;
				if (Todays_Packages[0].packagetarget)
				{
					int playpack=-1;
					int totalflights=0;
					int account=MMC.playeracnum;
					for (int pack=0;pack<Profile::MAX_PACKS;pack++)
					{
						MMC.SetOldPackScore(pack);
						for (int wave=0;wave<Profile::MAX_WAVES;wave++)
							for (int grp=0;grp<Profile::MAX_GROUPS;grp++)
							{
								totalflights+=Todays_Packages[pack][wave][grp].numflights;
								if (MMC.playersquadron==Todays_Packages[pack][wave][grp].squadron)
									if (account>=0)
										if ((account-=Todays_Packages[pack][wave][grp].numflights*4)<0)
										{
											playpack=pack;
											//5min = 5 * 60 * 100 cs = 30,000 cs, say 32K
											//15 sec= 1500
											GR_TakeOffTime=(Todays_Packages[pack][wave][grp].takeofftime)-(Todays_Packages[pack][wave][grp].takeofftime%TIME_TAKEOFF_ROUNDING);
											GR_TakeOffTime+=(totalflights+((account-3)/4))*TIME_TAKEOFF_FLIGHT;
										}
							}
					}
					playertarget=Todays_Packages[playpack].packagetarget;
					flighttakeoffstep=0;

					{
						GR_WaveNum=-1;	//not a package wave!!!
						rv=FIL_RVBUZZ00;
						GR_MainObjective=Todays_Packages[playpack].egressloc;
					}
					nextbftype=PREBLUETAKEOFFAFBF;
				}
				else
				{
					playertarget=CSQuick1::quickdef.target;
					GR_TakeOffTime=9*60*60;
					nextbftype=PREREDTAKEOFFAFBF;
				}
				playernode=playernode2=SupplyTree::FindSupplyNodeForItem(playertarget);

			break;
			case	REDTAKEOFFAFBF:
			{
				int afindex=5;//UID_AfRdAntung
				rv=SupplyTree.airfieldinfo[afindex].EmptyPopulateBF;
				GR_MainObjective=SupplyTree.airfieldinfo[afindex].airfield;
				GR_AAALevel64K=0;
			}
			break;
			case	REDTAKEOFFREDAFBF:
			{
				int afindex=5;//UID_AfRdAntung
				rv=SupplyTree.airfieldinfo[afindex].RedPopulateBF;
				GR_MainObjective=SupplyTree.airfieldinfo[afindex].airfield;
				GR_AAALevel64K=0;
			}


			case	TAKEOFFAFBF:
			{
				GR_TruckMoveCode=GROUND_TAXI;

				int afindex=0;
				if (MMC.playersquadron<SQ_B_NONFLYABLE)
					afindex=MMC.squad[MMC.playersquadron].airfieldindex;
				else
					afindex=25;//UID_Kunsan
				rv=SupplyTree.airfieldinfo[afindex].EmptyPopulateBF;
				GR_MainObjective=SupplyTree.airfieldinfo[afindex].airfield;
				GR_AAALevel64K=0;
			}

//DeadCode DAW 05Feb99 					rv=SupplyTree.airfieldinfo[MMC.squad[MMC.playersquadron].airfieldindex].BluePopulateBF;
//DeadCode DAW 05Feb99 					GR_MainObjective=SupplyTree.airfieldinfo[MMC.squad[MMC.playersquadron].airfieldindex].airfield;
			break;
			case    TAKEOFFBLUEAF:
			{
				GR_TruckMoveCode=GROUND_TAXI;

				int afindex=0;
				if (MMC.playersquadron<SQ_B_NONFLYABLE)
					afindex=MMC.squad[MMC.playersquadron].airfieldindex;
				else
					afindex=25;//UID_Kunsan
				rv=SupplyTree.airfieldinfo[afindex].BluePopulateBF;
				GR_MainObjective=SupplyTree.airfieldinfo[afindex].airfield;
				if (!playernode)
					nextbftype=ENDPLAYTARGBF;						  //JIM 02/06/99
				GR_AAALevel64K=0;
			}
			break;
			case    TAKEOFFHANDBLUEAF:
			{
				GR_TruckMoveCode=GROUND_TAXI;
	
				GR_WaveNum=-1;	//not a package wave!!!
				int afindex=0;
				if (MMC.playersquadron<SQ_B_NONFLYABLE)
					afindex=MMC.squad[MMC.playersquadron].airfieldindex;
				else
					afindex==25;//UID_Kunsan
//DeadCode AMM 28Apr99 				rv=SupplyTree.airfieldinfo[afindex].HandBlueBF;
				GR_MainObjective=SupplyTree.airfieldinfo[afindex].airfield;
				GR_AAALevel64K=0;

// only want to return a value if in campaign

				if (Todays_Packages[0].packagetarget)			//AMM 27Apr99
					rv=SupplyTree.airfieldinfo[afindex].HandBlueBF;//AMM 27Apr99

			}
			break;

			case	TAKEOFF0AF:
			case	TAKEOFF1AF:
			case	TAKEOFF2AF:
			case	TAKEOFF3AF:
			case	TAKEOFF4AF:
			{
				int afindex=MMC.squad[nextbftype-TAKEOFF0AF].airfieldindex;
				rv=SupplyTree.airfieldinfo[afindex].EmptyPopulateBF;
				GR_MainObjective=SupplyTree.airfieldinfo[afindex].airfield;
				GR_AAALevel64K=0;
			}
			break;


			case	TARGETBF:
				GR_MainObjective=playernode->associated_item;
				GR_AAALevel64K=playernode->attackstats.aaalevel<<8;
				rv=playernode->populateBF;
			break;
			case	SECTARGBF:
				GR_MainObjective=playernode->associated_item;
				rv=FIL_NULL;
			break;
			case	ROUTE0BF:
				{
			//the question is... How do I know the convoy is active today?
				for (SupplyRoute* s=playernode->forward;s;s=s->alternateroute)
					if (s->redsupplyUID) //extra test to see if high pop.
					{
						GR_MainObjective=s->supplier->associated_item;
						GR_SubObjective=s->suppliee->associated_item;
						GR_WP1=s->redsupplyUID;
						if (s->SetSupplySizeGR(GR_FormSize00,GR_FormSize01,GR_FormSize02))
							rv=s->populateBF;
						break;
					}
					if (rv)											  //JIM 22/04/99
						GR_AAALevel64K=playernode->forward->attackstats.aaalevel<<8;
				}
			break;
			case	ROUTE1BF:
			case	ROUTE2BF:
			case	ROUTE3BF:
			//the question is... How do I know the convoy is active today?
				{
				for (SupplyRoute* s=playernode->route[nextbftype-ROUTE1BF];s;s=s->alternateroute)
					if (s->redsupplyUID) //extra test to see if high pop.
					{
						GR_MainObjective=s->supplier->associated_item;
						GR_SubObjective=s->suppliee->associated_item;
						GR_WP1=s->redsupplyUID;
						if (s->SetSupplySizeGR(GR_FormSize00,GR_FormSize01,GR_FormSize02))
							rv=s->populateBF;
//DEADCODE DAW 10/05/99 						int trucks=s->storeslaunched/s->storespermobile;	//trucks per period
//DEADCODE DAW 10/05/99 						trucks-=10;
//DEADCODE DAW 10/05/99 						if (trucks)//trucks at night
//DEADCODE DAW 10/05/99 							if (trucks<10)										//too few to see
//DEADCODE DAW 10/05/99 								if (Math_Lib.rnd(3))
//DEADCODE DAW 10/05/99 									trucks=0;
//DEADCODE DAW 10/05/99 								else
//DEADCODE DAW 10/05/99 									trucks=trucks+5;							//make more visible
//DEADCODE DAW 10/05/99 						GR_FormSize00=trucks;
//DEADCODE DAW 10/05/99 						GR_FormSize01=trucks/2;
//DEADCODE DAW 10/05/99 						GR_FormSize02=trucks/3;
//DEADCODE DAW 10/05/99 ///					GR_WP1=playernode->forward->associated_brdg;
//DEADCODE DAW 10/05/99 						if (trucks>0)
//DEADCODE DAW 10/05/99 						rv=s->populateBF;
						break;
					}
				}
			break;
			case	CHOKE0BF:
				if (playernode->forward)
				{
					GR_WP1=playernode->forward->associated_brdg;
					if (GR_WP1)
					{
						GR_MainObjective=playernode->associated_item;
						GR_SubObjective=playernode->forward->suppliee->associated_item;

						GR_AAALevel64K=playernode->forward->attackstats.aaalevel<<8;
						rv=playernode->forward->populateBF;
				
					}
				}
			break;
			case	CHOKE1BF:
			case	CHOKE2BF:
			case	CHOKE3BF:
				if (playernode->route[nextbftype-CHOKE1BF])
				{
					GR_WP1=playernode->route[nextbftype-CHOKE1BF]->associated_brdg;
					if (GR_WP1)
					{
						GR_SubObjective=playernode->associated_item;
						GR_MainObjective=playernode->route[nextbftype-CHOKE1BF]->supplier->associated_item;					
						GR_AAALevel64K=playernode->route[nextbftype-CHOKE1BF]->attackstats.aaalevel<<8;
						rv=playernode->route[nextbftype-CHOKE1BF]->populateBF;
					}
				}
				break;

			case	TOWN0BF:
				if (playernode->forward && playernode->forward->suppliee)
				{
					GR_MainObjective=playernode->forward->suppliee->associated_item;
					GR_AAALevel64K=playernode->forward->suppliee->attackstats.aaalevel<<8;
					rv=playernode->forward->suppliee->populateBF;
				}
			break;
			case	TOWN1BF:
			case	TOWN2BF:
			case	TOWN3BF:
				if (playernode->route[nextbftype-TOWN1BF] && playernode->route[nextbftype-TOWN1BF]->supplier)
				{
					GR_MainObjective=playernode->route[nextbftype-TOWN1BF]->supplier->associated_item;
					GR_AAALevel64K=playernode->route[nextbftype-TOWN1BF]->supplier->attackstats.aaalevel<<8;
					rv=playernode->route[nextbftype-TOWN1BF]->supplier->populateBF;
				}
				break;

			case	DEFENDAF0BF:
			case	DEFENDAF1BF:
			case	DEFENDAF2BF:
				if ((GR_MainObjective=playernode->airfield[nextbftype-DEFENDAF0BF])!=UID_NULL)
				{
					AirFieldInfo*	af=SupplyTree::FindAirfieldForItem(UniqueID(GR_MainObjective));
					GR_AAALevel64K=af->attackstats.aaalevel<<8;
					rv=af->EmptyPopulateBF;
				}
			break;
			case	DEFENDAF0RBF:
			case	DEFENDAF1RBF:
			case	DEFENDAF2RBF:
				if ((GR_MainObjective=playernode->airfield[nextbftype-DEFENDAF0RBF])!=UID_NULL)
				{
					AirFieldInfo*	af=SupplyTree::FindAirfieldForItem(UniqueID(GR_MainObjective));
					GR_AAALevel64K=af->attackstats.aaalevel<<8;
					if (af->nationality==NAT_RED)
					rv=af->RedPopulateBF;
				}
			break;
			//PUT ANY EXTRA PLAYER STUFF HERE!!!

			case	ENDPLAYTARGBF:
			default:
				break;
			}
			if (nextbftype!=ENDPLAYTARGBF)
				nextbftype=BattlefieldType(int(nextbftype)+1);
			else
			{

				if (Todays_Packages[0].packagetarget)
					nextbftype=GROUNDBF;
				else
					nextbftype = SCRAMBF;

			}
			return KeepIfNotLoaded(rv);
//TempCode RDH 14Jul99 			if (rv && BFLoaded(rv))
//TempCode RDH 14Jul99 				return FIL_NULL;
//TempCode RDH 14Jul99 			else
//TempCode RDH 14Jul99 				return (rv);
		}
		break;
		case	GROUNDBF:
		{	//if the player's target area is an ongoing battle then launch the battle itself
			//we may decide we can afford to launch all 3 battles simultaniously
			//and perhaps even if not attacking them.
 			//			EASTGROUNDBF= (int)GROUNDBF+64,
			//			CENTGROUNDBF= (int)GROUNDBF+128,
			//			WESTGROUNDBF= (int)GROUNDBF+192,
			GR_AAALevel64K=65535;
			static BattleStruct* bs;
			BattleStruct* bsdebug=bs;
			if (nextbftype==GROUNDBF)
			{
				int sl;
				SupplyNode* supplier=NULL;
				for (sl=0;sl<3;sl++)
				{
					if (	SupplyTree::supplylines[sl]->frontline
						&&	SupplyTree::supplylines[sl]->frontline->forward
						&&	SupplyTree::supplylines[sl]->frontline->forward->suppliee==playernode
						)
						supplier=SupplyTree::supplylines[sl]->frontline;
				}
				if (	supplier 
					&&	supplier->status==FRONTLINE && supplier->type==BATTLEFIELD
					&&	(	supplier->supplyline->initiative==REDATTACKING
						||	supplier->supplyline->initiative==BLUEATTACKING
					)	)
				{
					playernode=supplier;
					if (supplier->supplyline==&SupplyTree::WestRoute)
						nextbftype=WESTGROUNDBF;
					else
					if (supplier->supplyline==&SupplyTree::EastRoute)
						nextbftype=EASTGROUNDBF;
					else
						nextbftype=CENTGROUNDBF;
				}
				else
					nextbftype=PLAYERBF;
				return FIL_NULL;
			}
			if (nextbftype==GROUNDBF+1)
			{	//air or ground controller
				//assume 3 targets
				enum	{NUMTARGETS=3};
				int targpriorities[NUMTARGETS]={0};
				int lowprislot=0;
				int found=0;
				BattleStruct* bs2=bs;
				for (int teamnum=0;teamnum<BattleStruct::MAXTEAMS;teamnum++)
				{
					if (bs->teamlist[teamnum].strength)
						if (	(playernode->supplyline->initiative==REDATTACKING)
							==	(bs->teamlist[teamnum].team==TeamDef::AWAY)
							)
						{
							if (bs->teamlist[teamnum].advantagepriority>targpriorities[lowprislot])
							{	//;
								found++;
								targpriorities[lowprislot]=bs->teamlist[teamnum].advantagepriority;
								GR_Pack_Targ[lowprislot][0]=bs->teamlist[teamnum].nextlocation;
								GR_Pack_Targ[lowprislot][1]=bs->teamlist[teamnum].location;
								if (!GR_Pack_Targ[lowprislot][0])
									GR_Pack_Targ[lowprislot][0]=GR_Pack_Targ[lowprislot][1];
								for (int slot=0,lps=targpriorities[lowprislot];slot<NUMTARGETS;slot++)
									if (targpriorities[slot]<lps)
										lps=targpriorities[lowprislot=slot];
							}
						}
				}
				if (found>NUMTARGETS)
					found=NUMTARGETS;
//DEADCODE DAW 15/06/99 				if (playernode->supplyline==&SupplyTree::WestRoute)
//DEADCODE DAW 15/06/99 				{
//DEADCODE DAW 15/06/99 					GR_MainObjective=UID_BNW_3a;
//DEADCODE DAW 15/06/99 				}
//DEADCODE DAW 15/06/99 				else
//DEADCODE DAW 15/06/99 				if (playernode->supplyline==&SupplyTree::EastRoute)
//DEADCODE DAW 15/06/99 					GR_MainObjective=UID_NULL;//UID_BNE_3a;
//DEADCODE DAW 15/06/99 				else
//DEADCODE DAW 15/06/99 					GR_MainObjective=UID_BNC_3a;
//DEADCODE DAW 15/06/99 				if (!ConvertPtrUID(UniqueID(GR_MainObjective)))
				GR_MainObjective=playernode->forward->suppliee->associated_item;

				nextbftype=PLAYERBF;
				GR_WaveNum=-1;	//not a package wave!!!
				if (found)
					if (playernode->supplyline->FACActive)			  //JIM 20/05/99
					{
						GR_FriendlyScoutSquad=playernode->supplyline->FACcallname;
						if (playernode->supplyline->initiative==REDATTACKING)
							GR_CloudBase=playernode->supplyline->frontline->redfrontBF->altitude;
						else
							GR_CloudBase=playernode->supplyline->frontline->bluefrontBF->altitude;
						return FileNum(FIL_FAC_1TARGET+found-1);
					}
					else
					{
						GR_FriendlyScoutSquad=playernode->supplyline->TACcallname;
						return FileNum(FIL_TAC_1TARGET+found-1);
					}
				else
					return FIL_NULL;
			}


			FileNum	rv=FIL_NULL;;
			if (nextbftype==WESTGROUNDBF || nextbftype==EASTGROUNDBF || nextbftype==CENTGROUNDBF)
			{	//grouped together for ease of use...
				if (nextbftype==WESTGROUNDBF)
					playernode=SupplyTree::WestRoute.frontline;
				else
				if (nextbftype==EASTGROUNDBF)
					playernode=SupplyTree::EastRoute.frontline;
				else
					playernode=SupplyTree::CentralRoute.frontline;
				bs=&playernode->supplyline->groundbattle;
				bsdebug=bs;
				if (playernode->supplyline->initiative==REDATTACKING)
				{
					bs->LoadBattleNodes(playernode->bluefrontBF->nodetree);
					rv=playernode->bluefrontBF->bf;
				}
				else
				{
					bs->LoadBattleNodes(playernode->redfrontBF->nodetree);
					rv=playernode->redfrontBF->bf;
				}
				bs->LinkBattleNodes();
				bs->LinkTeams();
				nextbftype=BattlefieldType(int(nextbftype)+1);
			}
			else
			{
				int teamnum=((nextbftype&63)-1);
				if (teamnum<BattleStruct::MAXTEAMS)
				{

					bs->BattleField(teamnum,
						rv,(UniqueID&)GR_MainObjective ,(UniqueID&)GR_SubObjective,
						(int&) GR_FormSize00,(int&) GR_FormSize01);
					if (	(playernode->supplyline->initiative==REDATTACKING)
						==	(bs->teamlist[teamnum].team==TeamDef::AWAY)
						)
						GR_RequiredNationality=NAT_RED;
					else
						GR_RequiredNationality=NAT_BLUE;
					GR_GroundForceType=bs->teamlist[teamnum].forcetype;
					GR_movecode=GROUND_TAXI;
					BattleStruct* bs2=bs;
					UniqueID starthere=(UniqueID&)GR_MainObjective,endhere=(UniqueID&)GR_SubObjective;
					if (rv)
						bs2=bs2;
					nextbftype=BattlefieldType(int(nextbftype)+1);
				}
				else
					nextbftype=BattlefieldType(int(GROUNDBF)+1);   //modify this to load all 3 or other tricks...
//DeadCode DAW 23Dec98 						nextbftype=PLAYERBF;  //SayAndQuit
			}
			return rv;	//can repeat safely
		}
		break;
		case	SCRAMBF:
		{	//set up to load the scramble battlefield
			int glind=0;
			for(int s=0;s<2;s++)
				for(int w=0;w<8;w++)
					for(int g=0;g<3;g++)
						if(CSQuick1::quickdef.line[s][w][g].flights || CSQuick1::quickdef.line[s][w][g].AllowZero())
						{
							GR_Scram_Alt[glind]=CSQuick1::quickdef.line[s][w][g].alt;
							GR_Scram_AC[glind]=CSQuick1::quickdef.line[s][w][g].flights*4;
							GR_Scram_Skill[glind]=CSQuick1::quickdef.line[s][w][g].skill;
							GR_Scram_Squad[glind]=CSQuick1::quickdef.line[s][w][g].actype;
							glind++;
						}
						else
							GR_Scram_AC[glind]=0;
			for(int w=0;w<8;w++)
				GR_Pack_TakeTime[w][0]=GR_Pack_TakeTime[w][1]=GR_Pack_TakeTime[w][2]=0;
//DeadCode AMM 02Jun99 			for(int sq=0;sq<5;sq++)
			for (int sq=0;sq<=SQ_R_NONFLYABLE;sq++)				//AMM 02Jun99
				GR_Pack_Sq_Used[sq]=0;
			for (int squads=0;squads<SQ_B_NONFLYABLE;squads++)
				GR_Pack_Home[squads]=SupplyTree.airfieldinfo[MMC.squad[squads].airfieldindex].airfield;
			for (squads=SQ_B_NONFLYABLE;squads<8;squads++)
				GR_Pack_Home[squads]=UID_Japan;


			GR_Pack_Target=CSQuick1::quickdef.target;
//DeadCode AMM 17Nov98 				Pack_PlayerSquad=MMC.playersquadron;
//DeadCode AMM 17Nov98 				Pack_PlayerPos=MMC.playeracnum;
			nextbftype = FINISHBF;
			GR_WaveNum=-1;	
			return (FileNum)CSQuick1::quickdef.currmissnum;

		}
		case	PLAYERBF:
		{	//The aircraft for each package...
			if (GR_BLUESKILLCONFIG>=2)
				GR_GlobalSkillMin = 3*(GR_BLUESKILLCONFIG-2);						//RDH 01Oct96
			else
				GR_GlobalSkillMax = SKILL_HERO-(2-GR_BLUESKILLCONFIG)*2;							//RDH 01Oct96

			FileNum rv=FIL_NULL;
			int packnum=(nextbftype&BFMAXCOUNTER);
			if (packnum==0)
			{
//					Pack_PlayerSquad=MMC.playersquadron;
//					Pack_PlayerPos=MMC.playeracnum;
//DEADCODE DAW 03/06/99 				Dead_Stream.GetWorldDead(myworld);				//RDH 02Oct96
//DeadCode AMM 02Jun99 				for(int sq=0;sq<5;sq++)
			for (int sq=0;sq<=SQ_R_NONFLYABLE;sq++)				//AMM 02Jun99
					GR_Pack_Sq_Used[sq]=0;
				int ac=0;

			}
			if (!packnum)
			{
				leftval=migcapstrength=0;

			}
			else
				if (Todays_Packages[packnum-1][0][0].uid)
					if ((Todays_Packages[packnum-1].duty&ACTIONCODE)==DA_CAP)
					{	//potential barcap patrol
						AirStrucPtr as=*ConvertPtrUID(UniqueID(GR_firstobject));
						assert(as);
						for (WayPoint* wp=as->waypoint;wp;wp=wp->next)
							if (wp->wpname==WPNAME_Target)
							{
								Coords3D* c=wp->FindDesPos();
								int posnweight=c->X+c->Z;
								if (!leftval)
								{
									bluenemigcap=blueswmigcap=wp->uniqueID.count;
									leftval=rightval=posnweight;
								}
								elseif (leftval>posnweight)
								{
									leftval=posnweight;
									blueswmigcap=wp->uniqueID.count;
								}
								elseif (rightval<posnweight)
								{
									rightval=posnweight;
									bluenemigcap=wp->uniqueID.count;
								}
							}
						for (int wave=0;wave<Profile::MAX_WAVES;wave++)
							for (int group=0;group<Profile::MAX_GROUPS;group++)
								migcapstrength+=Todays_Packages[packnum-1][wave][group].numflights;
						migcaptime=Todays_Packages[packnum-1][0].targettime;


					}
			if (packnum<Profile::MAX_PACKS)
			if (Todays_Packages[packnum][0][0].uid)
			{	//build 3 squad targets
				Todays_Packages[packnum].SetTargetUIDs(true);
				Todays_Packages[packnum].SetTargetGlobrefs(true);

				for (int squads=0;squads<SQ_B_NONFLYABLE;squads++)
					GR_Pack_Home[squads]=SupplyTree.airfieldinfo[MMC.squad[squads].airfieldindex].airfield;
				for (squads=SQ_B_NONFLYABLE;squads<8;squads++)
					GR_Pack_Home[squads]=UID_Japan;

				for (int wave=0;wave<Profile::MAX_WAVES;wave++)
					if (Todays_Packages[packnum][wave][0].numflights)
					{
						GR_Scram_Squad[wave]=0x808080+
							1*			Todays_Packages[packnum][wave][0].callname
							+256*		Todays_Packages[packnum][wave][1].callname
							+256*256*	Todays_Packages[packnum][wave][2].callname;

						int time;
						time=Todays_Packages[packnum][wave][0].takeofftime;
						time=(time-(time%TIME_TAKEOFF_ROUNDING))+flighttakeoffstep*TIME_TAKEOFF_FLIGHT;
						GR_Pack_TakeTime[wave][0]=time;
						flighttakeoffstep+=Todays_Packages[packnum][wave][0].numflights;

						time=Todays_Packages[packnum][wave][1].takeofftime;
						time=(time-(time%TIME_TAKEOFF_ROUNDING))+flighttakeoffstep*TIME_TAKEOFF_FLIGHT;
						GR_Pack_TakeTime[wave][1]=time;
						flighttakeoffstep+=Todays_Packages[packnum][wave][1].numflights;

						time=Todays_Packages[packnum][wave][2].takeofftime;
						time=(time-(time%TIME_TAKEOFF_ROUNDING))+flighttakeoffstep*TIME_TAKEOFF_FLIGHT;
						GR_Pack_TakeTime[wave][2]=time;
						flighttakeoffstep+=Todays_Packages[packnum][wave][2].numflights;
					}
				GR_WaveNum=0;	
				rv=FileNum(FIL_RUNTIMEPACK0+packnum);
			}
			if (packnum<Profile::MAX_PACKS)
			{
				nextbftype = BattlefieldType(PLAYERBF+1+packnum);
			}
			else
				nextbftype = DEFENDERBF;
			return(rv);
		}
		case DEFENDERBF:
		{
			if (GR_REDSKILLCONFIG>=2)
				GR_GlobalSkillMin = 3*(GR_BLUESKILLCONFIG-2);						//RDH 01Oct96
			else
				GR_GlobalSkillMax = SKILL_HERO-(2-GR_BLUESKILLCONFIG)*2;							//RDH 01Oct96
			FileNum rv=FIL_NULL;
#if	defined(IF_THIS_LINE_ENABLED_GOT_MIGS)
//#if	!defined(NDEBUG) && !defined(IF_THIS_LINE_ENABLED_NO_MIGS)
			for (int sq=0;sq<PILOTABLE_SQUADRONS;sq++)		
				GR_Scram_Squad[sq]=	MMC.squad[sq].bingofuel;
			nextbftype=MIGENDINFO;
#else
			switch	(nextbftype)
			{
			case DEFENDERBF:
			{
				//reusing scram_squad as blue bingo level. All blues now set up.
				for (int sq=0;sq<PILOTABLE_SQUADRONS;sq++)		
					GR_Scram_Squad[sq]=	MMC.squad[sq].bingofuel;
				//I need to decide:
				//1) Whether there is a blue migcap - must get a pointer to them...
				//2) Whether it is strong enough
				//3) Where it is
				//4) When it will arrive
				//5) Big train day?
				if (migcapstrength==0)
				{
					migdaytype=MIGDAYDIRECT;			//Everyone goes direct to targets!
					bluenemigcap=UID_AfRdUiju;
					blueswmigcap=UID_AfRdSinuiju;
				}
				elseif (migcapstrength<2)
					migdaytype=MIGDAYLATEBARCAP;		//Early attacks south can take place
				else						
					if (!(	(MMC.migevents[migdaytype=RndSq256(MMC.migsquad[0].maxevent+1)].eventdoes&MigEvent::BIGTRAIN)
						&&	MMC.migevents[migdaytype].minlevel<MMC.migsquad[0].agglevel
						) )	//If big train day then migdaytype=selected big train - set in this if
						migdaytype=MIGDAYALLBARCAP;		//else migdaytype=barcap only.
			}	//migdaysouth is set when a southern airfield wants to launch
			break;
			case MIGSQ0BF:
			{
				GR_FormSize00=MMC.migsquad[0].ac_total_avail*2/3;
				GR_FormSize03=GR_FormSize00*2	;
				GR_Scram_Squad[0]=SQ_M15_0;
				rv=FIL_MIG_HOLDING;
			}
			break;
			case MIGSQ1BF:
			{
				GR_FormSize00=MMC.migsquad[1].ac_total_avail*2/3;
				GR_Scram_Squad[0]=SQ_M15_1;
				rv=FIL_MIG_HOLDING;
			}
			break;
			case MIGSQTO0BF:
			case MIGSQTO1BF:
			case MIGSQTO2BF:
			case MIGSQTO3BF:
			case MIGSQTO4BF:
			{
				int numskip=nextbftype-MIGSQTO0BF;
				for (int afnum=0;SupplyTree::airfieldinfo[afnum].nationality!=NAT_ALIGN;afnum++)
					if (	SupplyTree::airfieldinfo[afnum].nationality==NAT_RED
						&&	SupplyTree::airfieldinfo[afnum].activeac	
						)
						breakif(--numskip<0);
				if (SupplyTree::airfieldinfo[afnum].nationality==NAT_RED)
				{
					ItemPtr af=*Persons2::ConvertPtrUID(SupplyTree::airfieldinfo[afnum].airfield);
					if (af->World.Z>Persons2::ConvertPtrUID(UID_AfRdSinanju)->World.Z & Math_Lib.rnd(3))
					{	//launch a mig alley type mission
						rv=LaunchMigPatrol(SQ_M15_1,SupplyTree::airfieldinfo[afnum].activeac,SupplyTree::airfieldinfo[afnum].airfield,migdaytype,migcaptime);
					}
					else
					{	//launch a southern airfield type mission
						GR_WaveNum=-1;	//not a package wave!!!
						GR_Pack_Takeoff=SupplyTree::airfieldinfo[afnum].airfield;
						GR_Scram_Squad[0]=SQ_M15_1;
						GR_Pack_TakeTime[0][0]=0;
						GR_Pack_Target=GR_Pack_Takeoff;
						GR_FormSize00=SupplyTree::airfieldinfo[afnum].activeac;
						GR_FormSize01=SupplyTree::airfieldinfo[afnum].activeac/2;
						GR_FormSize02=SupplyTree::airfieldinfo[afnum].activeac/3;
						rv=FIL_MIG_SOUTHAF;
					}
				}
			}
			break;
			case MIGSQAF0BF:
			case MIGSQAF1BF:
			case MIGSQAF2BF:
			case MIGSQAF3BF:
			case MIGSQAF4BF:
			{
				int numskip=nextbftype-MIGSQAF0BF;
				for (int afnum=0;SupplyTree::airfieldinfo[afnum].nationality!=NAT_ALIGN;afnum++)
					if (	SupplyTree::airfieldinfo[afnum].nationality==NAT_RED
						&&	SupplyTree::airfieldinfo[afnum].activeac	
						)
						breakif(--numskip<0);
				if (SupplyTree::airfieldinfo[afnum].nationality==NAT_RED)
				{
 					GR_AAALevel64K=SupplyTree::airfieldinfo[afnum].attackstats.aaalevel<<8;
					rv=SupplyTree::airfieldinfo[afnum].EmptyPopulateBF;
					rv=KeepIfNotLoaded(rv);
				}
			}
			break;
			case MIGSQAFTO0BF:
			case MIGSQAFTO1BF:
			case MIGSQAFTO2BF:
			case MIGSQAFTO3BF:
			case MIGSQAFTO4BF:
			{
				int numskip=nextbftype-MIGSQAFTO0BF;
				for (int afnum=0;SupplyTree::airfieldinfo[afnum].nationality!=NAT_ALIGN;afnum++)
					if (	SupplyTree::airfieldinfo[afnum].nationality==NAT_RED
						&&	SupplyTree::airfieldinfo[afnum].activeac	
						)
						breakif(--numskip<0);
				if (SupplyTree::airfieldinfo[afnum].nationality==NAT_RED)
				{
 					GR_AAALevel64K=SupplyTree::airfieldinfo[afnum].attackstats.aaalevel<<8;
					rv=SupplyTree::airfieldinfo[afnum].RedPopulateBF;
					rv=KeepIfNotLoaded(rv);
				}
			}
			break;

			default:
				if (nextbftype>=MIGSQPREAIR)
				{
					UniqueID migaf=UID_NULL;
					while (!migaf)
						switch (Math_Lib.rnd(4))
						{
						case 1:	migaf=UID_MIG_CHINA1;break;
						case 2:	migaf=UID_MIG_CHINA2;break;
						case 3:	migaf=UID_MIG_CHINA3;break;
						case 4:	if (SupplyTree::airfieldinfo[5].activeac==0)
									migaf=UID_AfRdAntung;break;
						}
					rv=LaunchMigPatrol(SQ_M15_0,0,migaf,migdaytype,migcaptime);
					if (!GR_FormSize03)
						nextbftype=MIGENDINFO;
				}
			}
#endif
			if (nextbftype!=MIGENDINFO)
				nextbftype=BattlefieldType(int(nextbftype)+1);
			else
				nextbftype=FINISHBF;
			return rv;
		}

	}
	return(FIL_NULL);
}

FileNum	Persons2::LaunchMigPatrol(SquadSelect squad,int prefsize,UniqueID takeoff,int migdaytype,int migcaptime)
{
	FileNum rv=FIL_NULL;
	int	packnum=Math_Lib.rnd(Profile::MAX_PACKS);
	while	(Todays_Packages[packnum][0][0].uid==UID_NULL)
		packnum=Math_Lib.rnd(packnum);
	UniqueID packtarg=Todays_Packages[packnum].packagetarget;
	//pick a good profile for the day



	int criteria=-1;
	int profilenum=-1;
	int	range=0;
	if (migdaytype>MIGDAYBIGTRAIN)
	{
	   profilenum=migdaytype;
	   criteria=MigEvent::TRAIN_TARGET;
	}
	else
	{

		ItemBasePtr	targitem=ConvertPtrUID(packtarg);
		ItemBasePtr takeoffitem=ConvertPtrUID(takeoff);
		if (targitem==NULL)											  //JIM 12/04/99
		{
			SupplyTree::Supply2UID relation;
			SupplyNode* node=SupplyTree::FindSupplyNodeForItem(packtarg,&relation);
			assert(node);
			assert(UWord(relation-SupplyTree::S2U_ROUTE0)<3);
			packtarg=node->route[relation-SupplyTree::S2U_ROUTE0]->supplier->associated_item;
			targitem=ConvertPtrUID(packtarg);
		}															  //JIM 12/04/99
		range=Math_Lib.Distance2d(takeoffitem->World.X-targitem->World.X,takeoffitem->World.Z-targitem->World.Z);
		//time in seconds... speed 250m/s plus allowance for getting there first 
		int	arrivaltime=Todays_Packages[packnum][0].targettime-300-GR_TakeOffTime;
		range-=arrivaltime*METRES240;	//actually, migs are doing 241.0
		//negative range means delay takeoff

		if (Todays_Packages[packnum].duty&DA_CAP)
				criteria=MigEvent::BARCAP;
		elseif (migdaytype==MIGDAYSOUTH)
			criteria=MigEvent::SOUTH_TARGET;
		elseif (targitem->World.Z>Persons2::ConvertPtrUID(UID_AfRdSinanju)->World.Z)
			criteria=MigEvent::LOCAL_TARGET;
		elseif (migdaytype==MIGDAYDIRECT)
			criteria=MigEvent::DIRECT_TARGET;
		elseif (migdaytype==MIGDAYALLBARCAP)
			criteria=MigEvent::DECOY_TARGET;
		else
		{	//where do we need to be now to intercept the bombers?
			if (range>METRES50KM)
				criteria=MigEvent::DIRECT_TARGET;
			else
				criteria=MigEvent::DECOY_TARGET;
		}
		profilenum=RndSq256(MMC.migsquad[squad-SQ_M15_0].maxevent+1);
		int profdelta=0;
		while(	(	(profilenum+profdelta>=0 && profilenum+profdelta<=MMC.migsquad[squad-SQ_M15_0].maxevent)
				||	(profilenum-profdelta>=0 && profilenum-profdelta<=MMC.migsquad[squad-SQ_M15_0].maxevent)
				)
			&&	(	MMC.migevents[profilenum+profdelta].minlevel>=MMC.migsquad[squad-SQ_M15_0].agglevel
				||	(MMC.migevents[profilenum+profdelta].eventdoes&criteria)!=criteria
			)	)
			if (profdelta>=0)
				profdelta=-profdelta-1;
			else
				profdelta=-profdelta;
				
		if (profilenum+profdelta>=0 && profilenum+profdelta<=MMC.migsquad[squad-SQ_M15_0].maxevent)
			profilenum=profilenum+profdelta;
		else
			profilenum=-1;
	}
	if (profilenum==-1)
	{
		profilenum=MIGEV_SANCPAT;
		criteria=MigEvent::LOCAL;
	}

	GR_WaveNum=-1;								//flag not a package
	if (prefsize)
		if (MMC.migevents[profilenum].maxformsize>prefsize)
			GR_FormSize00=MMC.migevents[profilenum].maxformsize;
		elseif (MMC.migevents[profilenum].minformsize>prefsize)
			GR_FormSize00=MMC.migevents[profilenum].minformsize;
		else
			GR_FormSize00=prefsize;
	else
	{
		GR_FormSize00=MMC.migevents[profilenum].minformsize
						+Math_Lib.rnd(MMC.migevents[profilenum].maxformsize-MMC.migevents[profilenum].minformsize);
		if (GR_FormSize00>GR_FormSize03)
			GR_FormSize00=GR_FormSize03;
		GR_FormSize03-=GR_FormSize00;
	}
	GR_FormSize01=MMC.migevents[profilenum].minformsize;
	GR_FormSize02=GR_FormSize00-GR_FormSize01;
	GR_Scram_Squad[0]=squad;
	Persons2::SetLoc(SGR_Pack_Takeoff,takeoff);
	Persons2::SetLoc(SGR_Pack_Target,packtarg);						  //DAW 13/04/99

	//also need to set:
	//		Wp0,Wp1			=patrol area			for Decoy and MigCap
	GR_WP1=blueswmigcap;
	GR_WP2=bluenemigcap;
	//		RangeStepSize 	=distance from takeoff	for Direct
	//		Pack_TakeTime	=time to takeoff		for MigCap 	
	//
	GR_Pack_TakeTime[0][0]=0;
	GR_RangeStepSize=0;
	if (MMC.migevents[profilenum].takeofftime && migcaptime)
	{
		int	rnddeltatime=Math_Lib.rnd(5)*30-60;
		GR_Pack_TakeTime[0][0]=migcaptime+MMC.migevents[profilenum].takeofftime+rnddeltatime;
	}
	else
	if (range<0)
	{
		GR_Pack_TakeTime[0][0]=-range/METRES240;
		GR_movecode=AUTO_TAKEOFF;
	}
	else
		GR_RangeStepSize=range;
	rv=MMC.migevents[profilenum].eventbf;



	return rv;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchConvoy
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Persons2::LaunchConvoy(FileNum bfield,SWord size)


{
//DeadCode RDH 24Feb97 	SWord i = 0,j,k=0;
	Bool	repeatuid,retval = FALSE;
//DeadCode RDH 24Feb97 	SWord	uidcount;
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97 //TempCode RDH 09Aug96 if (hq and relevant tanksite not dead) *****
//DeadCode RDH 24Feb97 //TempCode RDH 09Aug96 {	
//DeadCode RDH 24Feb97 	while (i < MAXCONVOYS)
//DeadCode RDH 24Feb97 	{
//DeadCode RDH 24Feb97 		breakif ( Miss_Man.camp.convoys[i].size == 0);
//DeadCode RDH 24Feb97 		i++;
//DeadCode RDH 24Feb97 	}
//DeadCode RDH 24Feb97 	if (i != MAXCONVOYS)
//DeadCode RDH 24Feb97 	{//set uid to first wp of a route
//DeadCode RDH 24Feb97 			uidcount = 	Math_Lib.rnd(MAXROUTES);
//DeadCode RDH 24Feb97 			uidcount--;
//DeadCode RDH 24Feb97 			// avoid two convoys on same start	
//DeadCode RDH 24Feb97 			do
//DeadCode RDH 24Feb97 			{
//DeadCode RDH 24Feb97 				repeatuid = FALSE;
//DeadCode RDH 24Feb97 				uidcount++;
//DeadCode RDH 24Feb97 				k++;
//DeadCode RDH 24Feb97 				if (uidcount >= MAXROUTES)
//DeadCode RDH 24Feb97 					uidcount =0;
//DeadCode RDH 24Feb97 				j = 0;
//DeadCode RDH 24Feb97 				while ((j < MAXCONVOYS) && (repeatuid == FALSE))
//DeadCode RDH 24Feb97 				{
//DeadCode RDH 24Feb97 					if ( Miss_Man.camp.routesstartuids[uidcount]
//DeadCode RDH 24Feb97 							==	Miss_Man.camp.convoys[j].uid)
//DeadCode RDH 24Feb97 						repeatuid = TRUE;
//DeadCode RDH 24Feb97 					j++;
//DeadCode RDH 24Feb97 				}
//DeadCode RDH 24Feb97 			}while ((repeatuid == TRUE) && k <= MAXROUTES);
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97 			if (k <= MAXROUTES)
//DeadCode RDH 24Feb97 			{
//DeadCode RDH 24Feb97 				Miss_Man.camp.convoys[i].uid = Miss_Man.camp.routesstartuids[uidcount];
//DeadCode RDH 24Feb97 				Miss_Man.camp.convoys[i].bfield = bfield;
//DeadCode RDH 24Feb97 				Miss_Man.camp.convoys[i].size = size;
//DeadCode RDH 24Feb97 				retval = TRUE;
//DeadCode RDH 24Feb97 			}		
//DeadCode RDH 24Feb97 	}
	return (retval);
//DeadCode RDH 24Feb97 //TempCode RDH 09Aug96 }
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTankConvoy
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons2::LaunchTankConvoy ()
{
//DeadCode RDH 14Jan97 	SWord i = 0,j=0,k;
//DeadCode RDH 14Jan97 	while (	(Miss_Man.camp.Tank_timer > 0)
//DeadCode RDH 14Jan97 		&&	(j < MAXTANKCONVOYS)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 	{
//DeadCode RDH 14Jan97 		i = 0;
//DeadCode RDH 14Jan97 		while (i < MAXCONVOYS)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			if (	( Miss_Man.camp.convoys[i].size != 0)
//DeadCode RDH 14Jan97 			&&	(Miss_Man.camp.convoys[i].bfield == BFTANKSET)
//DeadCode RDH 14Jan97 				)
//DeadCode RDH 14Jan97 				j++;
//DeadCode RDH 14Jan97 			i++;
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		if (j < MAXTANKCONVOYS)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			k=0;
//DeadCode RDH 14Jan97 			if (Persons_2.ItemStatus(UID_AlTdHavrincourtWd).deadtime == 0)
//DeadCode RDH 14Jan97 				k+=4;
//DeadCode RDH 14Jan97 			if (Persons_2.ItemStatus(UID_AlTdTrescault).deadtime == 0)
//DeadCode RDH 14Jan97 				k+=4;
//DeadCode RDH 14Jan97 			if (	(k == 8)
//DeadCode RDH 14Jan97 				||  (Math_Lib.rnd(k) > 2)
//DeadCode RDH 14Jan97 				)
//DeadCode RDH 14Jan97 			{
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 				if (LaunchConvoy(BFTANKSET,4))
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 				{
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 					Miss_Man.camp.Tank_timer -= INTERVAL_BETWEEN_TANK_LAUNCHES;
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 					Miss_Man.camp.Tank_timer -= Math_Lib.rnd(SECSPERHR/2);
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 				}
//DeadCode RDH 14Jan97 				LaunchConvoy(BFTANKSET,4);						//RDH 11Dec96
//DeadCode RDH 14Jan97 			}													//RDH 11Dec96
//DeadCode RDH 14Jan97 			Miss_Man.camp.Tank_timer -= INTERVAL_BETWEEN_TANK_LAUNCHES;//RDH 11Dec96
//DeadCode RDH 14Jan97 			Miss_Man.camp.Tank_timer -= Math_Lib.rnd(SECSPERHR/2);//RDH 11Dec96
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 	}
//DeadCode RDH 14Jan97 
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTruckConvoyTest
//Author		Jim Taylor
//Date			Thu 17 Oct 1996
//
//Description	
//if gun killed this time launch a truck
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons2::LaunchTruckConvoyTest ()
{

//DeadCode RDH 24Feb97 	UniqueID	tmpUID,EndBand;
//DeadCode RDH 24Feb97 	tmpUID  = RedMilitaryBAND;
//DeadCode RDH 24Feb97 	ItemBasePtr		tmpitem;
//DeadCode RDH 24Feb97 	EndBand = BlueMilitaryBAND;
//DeadCode RDH 24Feb97 	Bool	Launchtruck = TRUE;
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97  while (	(Miss_Man.camp.Tank_timer > 0)
//DeadCode RDH 24Feb97 			&& (Launchtruck == TRUE)
//DeadCode RDH 24Feb97 		)
//DeadCode RDH 24Feb97  { 
//DeadCode RDH 24Feb97 	Launchtruck = FALSE;
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97 	while (	(tmpUID < EndBand)
//DeadCode RDH 24Feb97 			&&	(Launchtruck == FALSE)
//DeadCode RDH 24Feb97 				)
//DeadCode RDH 24Feb97 	{
//DeadCode RDH 24Feb97 		tmpitem=Persons_2.ConvertPtrUID(tmpUID);
//DeadCode RDH 24Feb97 		if (	(tmpitem)
//DeadCode RDH 24Feb97 			&&	(tmpitem->Status.deadtime >= 7)		//temp
//DeadCode RDH 24Feb97 			)
//DeadCode RDH 24Feb97 			Launchtruck = TRUE;
//DeadCode RDH 24Feb97 		tmpUID++;
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97 	}
//DeadCode RDH 24Feb97 	if (	(Launchtruck)
//DeadCode RDH 24Feb97 		&&(tmpUID < EndBand)									//RDH 16Dec96
//DeadCode RDH 24Feb97 		)														//RDH 16Dec96
//DeadCode RDH 24Feb97 			Launchtruck = Persons_2.LaunchTruckConvoy();		//RDH 16Dec96
//DeadCode RDH 24Feb97  }
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTruckConvoy
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Persons2::LaunchTruckConvoy ()
{
	SWord i = 0,j=0,k;
	Bool	retval = FALSE;
//DeadCode RDH 14Jan97 	if (Miss_Man.camp.Truck_timer > 0)
//DeadCode RDH 14Jan97 	{
//DeadCode RDH 14Jan97 		i = 0;
//DeadCode RDH 14Jan97 		while (i < MAXCONVOYS)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			if (	( Miss_Man.camp.convoys[i].size != 0)
//DeadCode RDH 14Jan97 			&&	(Miss_Man.camp.convoys[i].bfield == BFTRUCKSET)
//DeadCode RDH 14Jan97 				)
//DeadCode RDH 14Jan97 				j++;
//DeadCode RDH 14Jan97 			i++;
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		if (j < MAXTRUCKCONVOYS)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			k=0;
//DeadCode RDH 14Jan97 			if (Persons_2.ItemStatus(UID_AlTdHavrincourtWd).deadtime == 0)
//DeadCode RDH 14Jan97 				k+=4;
//DeadCode RDH 14Jan97 			if (Persons_2.ItemStatus(UID_AlTdTrescault).deadtime == 0)
//DeadCode RDH 14Jan97 				k+=4;
//DeadCode RDH 14Jan97 			if (	(k == 8)
//DeadCode RDH 14Jan97 				||  (Math_Lib.rnd(k) > 2)
//DeadCode RDH 14Jan97 				)
//DeadCode RDH 14Jan97 			{
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 				if (LaunchConvoy(BFTRUCKSET,1))
//DeadCode RDH 14Jan97 				{
//DeadCode RDH 14Jan97 					Miss_Man.camp.Truck_timer -= INTERVAL_BETWEEN_TRUCK_LAUNCHES;
//DeadCode RDH 14Jan97 					Miss_Man.camp.Truck_timer -= Math_Lib.rnd(SECSPERHR);
//DeadCode RDH 14Jan97 					retval = TRUE;
//DeadCode RDH 14Jan97 				}
//DeadCode RDH 14Jan97 			}
//DeadCode RDH 14Jan97 	}	}
	return (retval);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TankEndMission
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons2::TankEndMission()
{
//DeadCode RDH 14Jan97 	SWord	i,j;
//DeadCode RDH 14Jan97 	ItemBasePtr		tmpitem;
//DeadCode RDH 14Jan97 	Bool	finishuid;
//DeadCode RDH 14Jan97 		ITEM_STATUS trgstat;
//DeadCode RDH 14Jan97 		UniqueIDBand	uidband;
//DeadCode RDH 14Jan97 		UniqueID	nwptrg;
//DeadCode RDH 14Jan97 		SLong		size=0;
//DeadCode RDH 14Jan97 		Bool	inlist = FALSE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //moved to scoring.cpp											//RDH 13Oct96
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 //deal with blue ac
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 //DeadCode JIM 11Oct96 	tmpitem=Persons_2.ConvertPtrUID(UID_AlAfHermies);
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 	if (Persons_2.ItemStatus(UID_AlAfHermies).deadtime != 0)	//JIM 11Oct96
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 		MMC.blueacflying = -1;
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 	MMC.blueacflying++;
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 	if (MMC.blueacflying > 4)
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 		MMC.blueacflying = 4;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //get info about convoys back from 3d
//DeadCode RDH 14Jan97 	for (i=0;i<MAXCONVOYS;i++)
//DeadCode RDH 14Jan97 	{
//DeadCode RDH 14Jan97 		size=0;
//DeadCode RDH 14Jan97 		inlist = FALSE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		if (MMC.convoys[i].size)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			trgstat=ConvoyStatus(MMC.convoys[i].uid,MMC.convoys[i].uid,nwptrg,size);
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 			//put gun into bluegun list when truck arrives
//DeadCode RDH 14Jan97 			if (Miss_Man.camp.convoys[i].bfield == BFTRUCKSET)
//DeadCode RDH 14Jan97 			{
//DeadCode RDH 14Jan97 				if (	(trgstat.deadtime != 0)					//JIM 13Dec96
//DeadCode RDH 14Jan97 				 	&&	(Miss_Man.camp.playerbfield != FIL_NULL)	//JIM 13Dec96
//DeadCode RDH 14Jan97 					)											//JIM 13Dec96
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 				{
//DeadCode RDH 14Jan97 					size = 0;
//DeadCode RDH 14Jan97 					j = 0;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 					while 	(j < MAXGUNS)
//DeadCode RDH 14Jan97 					{
//DeadCode RDH 14Jan97 						if (Miss_Man.camp.blueguns[j] == nwptrg)
//DeadCode RDH 14Jan97 							   inlist = TRUE;
//DeadCode RDH 14Jan97 						j++;
//DeadCode RDH 14Jan97 					}
//DeadCode RDH 14Jan97 					if (!(inlist))
//DeadCode RDH 14Jan97 					{
//DeadCode RDH 14Jan97 						j = 0;
//DeadCode RDH 14Jan97 						while (((Miss_Man.camp.blueguns[j]) !=UID_Null)
//DeadCode RDH 14Jan97 							 &&	(j < MAXGUNS)
//DeadCode RDH 14Jan97 							)
//DeadCode RDH 14Jan97 							j++;
//DeadCode RDH 14Jan97 						if (j < MAXGUNS)
//DeadCode RDH 14Jan97 							Miss_Man.camp.blueguns[j] = nwptrg;
//DeadCode RDH 14Jan97 					}
//DeadCode RDH 14Jan97 				}
//DeadCode RDH 14Jan97 			}
//DeadCode RDH 14Jan97 			uidband = Persons_2.getbandfromUID((UniqueID) nwptrg);
//DeadCode RDH 14Jan97 			if (uidband == RedCivilianBAND)
//DeadCode RDH 14Jan97 			{
//DeadCode RDH 14Jan97  				if (trgstat.deadtime == 0 )
//DeadCode RDH 14Jan97 					MMC.specialeventbits |= TANKNEARBRIDGES;
//DeadCode RDH 14Jan97 			}
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 			}else
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 			{
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 				if (Miss_Man.camp.convoys[i].bfield != BFTRUCKSET)
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 				{//kill gun that has been passed by tanks, 6 hrs	//RDH 06Dec96
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 					ItemStatus(nwptrg,SetStatus(24,0));				//RDH 06Dec96
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 																//RDH 06Dec96
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 				}
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 			}
//DeadCode RDH 14Jan97 			MMC.convoys[i].size=size;
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 	}
//DeadCode RDH 14Jan97 //repairing bridges
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtNoyelles);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtCantaing);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtFontaine);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtMarcoing);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtMasnieres);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //is campaign lost
//DeadCode RDH 14Jan97 //if convoy.uid (waypoint at this stage == routesend wp
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 	finishuid = FALSE;
//DeadCode RDH 14Jan97 	i = 0;
//DeadCode RDH 14Jan97 	do
//DeadCode RDH 14Jan97 	{
//DeadCode RDH 14Jan97 		j = 0;
//DeadCode RDH 14Jan97 		while ((j < MAXCONVOYS) && (finishuid == FALSE))
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			if ( Miss_Man.camp.routesenduids[i]
//DeadCode RDH 14Jan97 						==	Miss_Man.camp.convoys[j].uid)
//DeadCode RDH 14Jan97 					finishuid = TRUE;
//DeadCode RDH 14Jan97 			j++;
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 		i++;
//DeadCode RDH 14Jan97 	}while ((finishuid == FALSE) && (i < MAXROUTES));
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 	if (finishuid == TRUE)
//DeadCode RDH 14Jan97 		MMC.specialeventbits |= TANKCAMPAIGNLOST;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 //if aaa site dead then associated gun goes back to being dead
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 //clear blueaaa list entry
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 	for (i =0;i<MAXGUNS;i++)
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 	{
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 		if (Miss_Man.camp.blueaaa[i] ==UID_Null)
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 		{	
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 			Miss_Man.camp.blueguns[i] = UID_Null;
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 		}
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 		Miss_Man.camp.blueaaa[i] = UID_Null;	
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 	
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 	}
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //moved to scoring.cpp											//RDH 13Oct96
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 	LaunchTankConvoy();
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		lowlevel_squadron
//Author		Jim Taylor
//Date			Wed 25 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Persons2::lowlevel_squadron(int snequ)
{
//		if (snequ>SNEQU_LASTACE)
//			if (snequ>SNEQU_SECONDSET)
//				eventloglist->home=_Text.ConvSnip0((TextList)LIST_SQUADS2,snequ-SNEQU_SECONDSET-1);
//			else
//				eventloglist->home=_Text.ConvSnip0((TextList)LIST_SQUADS,snequ-SNEQU_LASTACE-1);
//		else
//		{
//			eventloglist->home=_Text.ConvSnip0((TextList)LIST_ACESQUADS,snequ);
//			eventloglist->name=_Text.ConvSnip0((TextList)LIST_ACES,snequ);
//		}	
		return(FALSE);
}
