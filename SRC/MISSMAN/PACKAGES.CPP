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
// Module:      Packages.cpp
//
// Created:     15/12/98 by JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////
// Managing the package list.
//
//	 IDB_TOOLBAR_HORZ
//
//

#include	"dosdefs.h"
#include	"files.g"
#include	"text.h"
#include	"Worldinc.h"
#include	"node.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"mymath.h"
#include	"ranges.h"
#include "winmove.h"
#include "comms.h"
#include "planetyp.h"
#include "..\mfc\resource.h"
#include	"globrefs.h"
#include "myerror.h"


MAKEFIELD(UniqueID,UID_NULL,IllegalSepID);
struct PackageList  Todays_Packages={UID_Null};

void	PackageList::UpDatePackageTimes()
{
	int targettime;
	int laststartperiodtime=0;
	int p=0;
	while (p<Profile::MAX_PACKS && Todays_Packages[p][0].firstwp)
	{
		if (MMC.debrief.currperiod == 0)
			laststartperiodtime = AFTERNOONPERIODSTART;
		if (MMC.debrief.currperiod == 1)
			laststartperiodtime = MORNINGPERIODSTART;
		if (MMC.debrief.currperiod == 2)
			laststartperiodtime = MIDDAYPERIODSTART;
		for (int i=0;i<Profile::MAX_WAVES;i++)
		if (Todays_Packages[p][i].firstwp)
		{
			targettime = Todays_Packages[p][i].targettime - laststartperiodtime + MMC.currtime;
			if	(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
			{
				if (targettime >	HR16MIN20)							  //RDH 11/06/99
					//don't want it too dark in winter
					targettime =	HR16MIN20;							  //RDH 11/06/99
				if (targettime <	HR08)
					//don't want it too dark in winter
					targettime =	HR08;							  //RDH 11/06/99
			}
			SetWaveTimes(p, i, targettime);
		}

		p++;
	}
}
void	PackageList::SetWaveTimes(int p, int w, int targettime)
{
	Todays_Packages[p][w].targettime = targettime;
	Todays_Packages[p].CalcWPTimes(w);

}

#ifndef	MIG_DEMO_VER
void	PackageList::DeleteNonRedoPackages()
{
	int row=0, shunt =0;
	while  ((shunt+row)<Profile::MAX_PACKS)
	{
		DirControl	dir_ctrl;
		bool redo_ok = dir_ctrl.ModifyRedoIfNecessary(row);
		if (		(!pack[row].redo)
				||	(!redo_ok)
			)
		{
			//delete contents of package
			ClearPack(row);
			//tidy list
			ShuntPack(row);
			shunt++;

		}else
			row++;
	}

}
#endif #ifndef	MIG_DEMO_VER

bool	PackageList::PackageHasBeenEdited()
{
	int p=0;
	while (p<Profile::MAX_PACKS && pack[p][0].firstwp)
	{
		if (pack[p].edited) 
			return (true);
		p++;
	}
	return(false);
}
void PackageList::ProfileFlightsRequired(int packnum, int& mb, int& f80, 
	 int& f84,int& f51,int& fb,int& f, int& f86a, int& f86b, int& b26, int& b29)
{
	mb = 0; f80 = 0; f84 = 0; f51 = 0; fb = 0, f = 0, f86a = 0, f86b = 0, b26 = 0, b29 = 0;

	for (int wave=0;wave<Profile::MAX_WAVES;wave++)
		for (int group=0;group<Profile::MAX_GROUPS;group++)
		{
			{
				int squadnum = pack[packnum].wave[wave].group[group].squadron;
				int numflights = pack[packnum].wave[wave].group[group].numflights;
				switch (squadnum)
				{
					case SQ_F86A:
					{
						f86a += numflights;
						f += numflights;
						break;
					}
					case SQ_F86B:
					{
						f86b += numflights;
						f += numflights;
						break;
					}
					case SQ_F80:
					{
						fb += numflights;
						f80 += numflights;

						break;
					}
					case SQ_F84:
					{
						fb += numflights;
						f84 += numflights;

						break;
					}
					case SQ_F51:
					{
						fb += numflights;
						f51 += numflights;
						break;
					}
					case SQ_B26:
					{
						b26 += numflights;
						mb += numflights;
						break;
					}
					case SQ_B29:
					{
						b29 += numflights;
						mb += numflights;
						break;
					}

				}
			}
		}
			

}
void PackageList::FlightsAvailable(int pack, int& a_mb, int& a_f80,int& a_f84,int& a_f51,int& a_fb,int& a_f, int& a_f86a, int& a_f86b, int& a_b26, int& a_b29)
{
	//if pack is ever used make sure that -1 means we don't have a current pack //RDH 06/06/99
	int mbindex = SQ_B26;
	if (MMC.directives.B29avail)
		mbindex = SQ_B29;
	a_mb = (SquadACAvail(mbindex) - SquadACUsed(mbindex))/4; 
	if (mbindex == SQ_B26)
	{
		a_b26 = a_mb;
		a_b29 = 0;
	}else
	{
		a_b29 = a_mb;
		a_b26 = 0;
	}

	a_f80 = (SquadACAvail(SQ_F80) - SquadACUsed(SQ_F80))/4;
	a_f84 = (SquadACAvail(SQ_F84) - SquadACUsed(SQ_F84))/4;
	a_f51 = (SquadACAvail(SQ_F51) - SquadACUsed(SQ_F51))/4;
	a_fb = a_f80 + a_f84 + a_f51;


	a_f86a = (SquadACAvail(SQ_F86A) - SquadACUsed(SQ_F86A))/4;
	a_f86b = (SquadACAvail(SQ_F86B) - SquadACUsed(SQ_F86B))/4;
	a_f = a_f86a + a_f86b;

}
int PackageList::FindSquad(int duty)
{
	int sq;
	char	choice[4];
	choice[0] = SQ_B26;
	choice[1] = SQ_F84;
	choice[2] = SQ_F80;
	choice[3] = SQ_F51;
	if (MMC.directives.B29avail)
		choice[0] = SQ_B29;
	if (		(duty == DUTYMIGCAP)											  //RDH 16/03/99 //RDH 26/04/99
			||	(duty == DUTYBARCAP)								  //RDH 26/04/99
		)
	{																  //RDH 16/03/99

		choice [0] = SQ_F86A;										  //RDH 16/03/99
		choice [3] = SQ_F86B;										  //RDH 16/03/99
	}
///	Persons2::InitTables();		//TEMP!!!! Should only be done once!!!
	for (sq=0;sq<4;sq++)
		breakif (SquadACAvail(choice[sq])>=SquadACUsed(choice[sq])+4);
	if (sq == 4)
	{
		return( -2);
	}
	sq = choice[sq];
	return sq;
}
int PackageList::FindSquadExlMedBombers()
{
	int sq;
	char	choice[3];
	choice[0] = SQ_F84;
	choice[1] = SQ_F80;
	choice[2] = SQ_F51;
	for (sq=0;sq<3;sq++)
		breakif (SquadACAvail(choice[sq])>=SquadACUsed(choice[sq])+4);
	if (sq == 3)
	{
		return( -2);
	}
	sq = choice[sq];
	return sq;
}
int PackageList::CAPAircraftcnt()
{
	int cnt =  SquadACAvail(SQ_F86A) - SquadACUsed(SQ_F86A);
	cnt	= cnt+  SquadACAvail(SQ_F86B) - SquadACUsed(SQ_F86B);
	return cnt;
}
int PackageList::FindPackage()
{

	int p=0;
	while (p<Profile::MAX_PACKS && pack[p][0].firstwp)
		p++;
	if (p==Profile::MAX_PACKS)
		return -1;
	return p;
}
int PackageList::NewPackage(UniqueID targ, int duty)
{

	int sq;
	int p;
	sq = FindSquad(duty);
	if (sq < 0)
		return sq;
	p = FindPackage();
	if (p < 0)
		return p;
	
	pack[p].redo = false;
	pack[p].edited = false;
	pack[p].duty=(DutyType)duty;
	pack[p].packname[0]='M';
	pack[p].packname[1]=' ';
	if (p==9)
		pack[p].packname[2]='0';
	else
		pack[p].packname[2]=p+'1';
	pack[p].packname[3]=0;
	pack[p].packname[4]=0;
	char pl='A'-1;
	forever
	{
		int pn=*(int*)pack[p].packname;
		int p2;
		for (p2=0;p2<Profile::MAX_PACKS;p2++)
			breakif (p2!=p && *(int*)pack[p2].packname==pn);
		breakif (p2==Profile::MAX_PACKS);
		pl++;
		pack[p].packname[3]=pl;
	};
	info_airgrp* a=new info_airgrp;
	a->uniqueID.count=Persons2::assignuid(BlueAcBAND);
	pack[p][0].group[0].uid=a->uniqueID.count;
	Persons2::tabulateUID(a);
	pack[p][0][0].SetFlights(1);
	for (int i = 0; i <3;i++)			//rdh
		pack[p][0][i].callname = -1;

//	a->inform=4;
	a->inwing=2;
//	a->type=sq;
	pack[p][0][0].SetSquad(sq);
	a->duty=duty;
	a->attmethod=0;
	a->attpattern=0;
	a->radiosilence = 0;
	a->form=SQUAD_FLATV;//ListFormExpr(2);								  //JIM 19/05/99//CSB 19May99
//	a->form[0]=SQUAD_FLATV;a->form[1]=SQUAD_FLATV;				//CSB 19May99
	a->bombs=new ListFormExpr(4);
	a->bombs[0]=0;a->bombs[1]=0;a->bombs[2]=0;a->bombs[3]=0;		  //JIM 24/03/99

	pack[p].packagetarget=targ;				//TEMP FIX!!!! No target info available
	pack[p].egressloc= FindEgressPoint(targ);
	pack[p].packagetakeoff=
		pack[p][0][0].takeoffAF;//=
			//SupplyTree::airfieldinfo[MMC.squad[sq].airfieldindex].airfield;//SquadronInfo							//TEMP
	if (		(a->duty == DUTYMIGCAP)											  //RDH 16/03/99 //RDH 26/04/99
			||	(a->duty == DUTYBARCAP)								  //RDH 26/04/99
		)
		pack[p][0].firstwp=pack[p].MakePrimaryRoute(FT_30000);
	else
		pack[p][0].firstwp=pack[p].MakePrimaryRoute(FT_10000);



//	UniqueID wt,waf,wal,wpf,wpl,wr;
//	Todays_Packages[p][0].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
//	Todays_Packages[p][0].InsertWpBetween(waf,wal,pack[p].packagetarget,wpbombno,0);
	Todays_Packages[p][0][0][0].globrefind=Todays_Packages[p].FindSpareGlobref();
	Todays_Packages[p][0].MakeWayPoints(true, 0, a->duty,targ);

	Todays_Packages[p][0].targettime = MMC.currtime + (int)HR02; 
//	Todays_Packages[p][0].starttime = MMC.currtime; 

	return	p;
}
UniqueID PackageList::FindEgressPoint(UniqueID targ)
{
	UniqueID	egresslist[6] = {UID_FCSinmiDo,
								 UID_ChoDo,
								 UID_RescueShip1,
								 UID_TokchokKundo,
								 UID_RescueShip2,
								 UID_KogunsanKundo
								};		
		
//		UID_BrRdYalu,UID_BrRlPyongyang,UID_MyBlSeoul,UID_StKusong,UID_AfBlTaegu,UID_AfBlTaejon};

	info_itemS* t = *Persons2::ConvertPtrUID(targ);
	info_itemS* e = *Persons2::ConvertPtrUID(UID_StAndong);		//southern most point
	UniqueID	egress = UID_StAndong;

	int		delta = e->World.Z - t->World.Z;    
	int		delta2;

	for (int i = 0; i < 6; i++)
	{
		UniqueID	uid = egresslist[i];
		e = *Persons2::ConvertPtrUID(uid);
		delta2 = e->World.Z - t->World.Z;  
		if (delta2 < 0)
			if (delta2 > delta)
			{
				egress= uid;
				delta = delta2;
			}
	}
	return(egress);

}
bool	PackageList::GetSquadEntry(int p, int w, int g, int& squad, int& flight)
{
	int	squadron[SQ_R_NONFLYABLE+1];			//include Yak
	for (int i=0;i<=SQ_R_NONFLYABLE;i++)
		squadron[i] = 0;

 	for (i=0;i<Profile::MAX_PACKS;i++)
//DeadCode RDH 07Jul99 	if (Todays_Packages.pack[i][0][0].uid)
//DeadCode RDH 07Jul99 	{
	for (int wave=0;wave<Profile::MAX_WAVES;wave++)
		if (Todays_Packages.pack[i][wave][0].uid)
		{

			for (int group=0;group<Profile::MAX_GROUPS;group++)
			{
//				UniqueID u=Todays_Packages.pack[i].wave[wave].group[group].uid;	   //10/1/99rdh
				if (Todays_Packages.pack[i].wave[wave].group[group].numflights)	   //10/1/99rdh
				{
					int squadnum = Todays_Packages.pack[i].wave[wave].group[group].squadron;
					int numflights = Todays_Packages.pack[i].wave[wave].group[group].numflights;
					if  ((p == i) && (w == wave) && (g == group ))
					{
						squad = squadnum;
						flight = squadron[squadnum];
						return(true);
					}
					else
					{
//						if (squadnum < PILOTABLE_SQUADRONS)
//							//only record the piloted squads
							squadron[squadnum] += numflights;
					}
				}
			}
	}

	return(false);


}

bool	PackageList::FlyableAircraftAvailable()
{
	bool	avail = false;


 	for (int i=0;i<Profile::MAX_PACKS;i++)
	if (Todays_Packages.pack[i][0][0].uid)
	{
		for (int wave=0;wave<Profile::MAX_WAVES;wave++)
			for (int group=0;group<Profile::MAX_GROUPS;group++)
			{
				if (Todays_Packages.pack[i].wave[wave].group[group].numflights)	   //10/1/99rdh
				{
					if (Todays_Packages.pack[i].wave[wave].group[group].squadron <SQ_B_NONFLYABLE)
						avail = true;
				}
			}
	}
	return(avail);


}

bool	PackageList::GetPackage(int& i, int& wave, int& group, int squad, int flight)
{
// Find the package, wave, group that is using squad, flight
	int	squadron[SQ_R_NONFLYABLE+1];			//include Yak
	for (i=0;i<=SQ_R_NONFLYABLE;i++)
		squadron[i] = 0;

	int imax;
//	if  (		(_DPlay.CurrPlayers != 0)
//DeadCode AMM 25Feb99 	if  (		(_DPlay.PlayerCreated)
//DeadCode AMM 25Feb99 		&&	(_DPlay.GameType == COMMSCAMPAIGN)
//DeadCode AMM 25Feb99 		&&	(_DPlay.Side == FALSE)
//DeadCode AMM 25Feb99 		)
//DeadCode AMM 25Feb99 	{
//DeadCode AMM 25Feb99 		i = Profile::MAX_PACKS;
//DeadCode AMM 25Feb99 		imax = i + 1;
//DeadCode AMM 25Feb99 	}else
	{
		i = 0;
		imax = Profile::MAX_PACKS;
	}

 	for (i;i< imax;i++)
//DeadCode RDH 07Jul99 	if (Todays_Packages.pack[i][0][0].uid)
//DeadCode RDH 07Jul99 	{
	for (wave=0;wave<Profile::MAX_WAVES;wave++)
		if (Todays_Packages.pack[i][wave][0].uid)
		{
			for (group=0;group<Profile::MAX_GROUPS;group++)
			{
				UniqueID u=Todays_Packages.pack[i].wave[wave].group[group].uid;
				if (u)
				{
					int squadnum = Todays_Packages.pack[i].wave[wave].group[group].squadron;
					int numflights = Todays_Packages.pack[i].wave[wave].group[group].numflights;
					if  (	(squad == squadnum) &&  (		(flight >= squadron[squadnum])
														&&	(flight < (squadron[squadnum] + numflights))
													)
						)
					{
						return(true);
					}
					else
//						if (squadnum < PILOTABLE_SQUADRONS)
//							//only record the piloted squads
							squadron[squadnum] += numflights;
				}
			}
		}
	return(false);


}


void	Profile::Wave::MakeWayPoints(bool wave0, int grnum, int duty,UniqueID targ)
{	//
	//What am I trying to do?
	//For most patrol missions I want to set up a pair of 
	//waypoints based on the InitialPoint waypoint.
	//	If it is the main route, that is SGR_WPP_Target
	//	If it is not the main route it is SGR_WPC_Target
	//For bombing missions, the target should be SGR_Pack_Target
	//For the armed recon patrol, we want a second target.
	//This comes from the flight specific target information.
	//Before calling this routine, the previous one will have allocated 
	//a UID for the flight specific data.
	//If we don't need it after all, this routine can clear it.

 	UniqueID wt,waf,wal,wpf,wpl,wr;
	GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
	UniqueID targ2=UID_NULL;
	UniqueID patrolbeginitem=UID_NULL;
	Coords3D wp0;
	Coords3D wp1;
	SavedGlobrefs patrolzone=SGR_WPP_Target;
	if (!wave0)
		patrolzone=SGR_WPC_Target;
	if (!Persons2::GetLoc(patrolzone)|| !Persons2::ConvertPtrUID(UniqueID(Persons2::GetLoc(patrolzone))))
		Persons2::SetLoc(patrolzone,targ);

	Coords3D patrolzonepos=Persons2::ConvertPtrUID(UniqueID(Persons2::GetLoc(patrolzone)))->World;

	switch (duty)
	{
		case	DC_WW:	
		{
			wp0.X = 500000;		wp0.Y = FT_5000;		wp0.Z =	1000000; //RDH 12/07/99
			wp1.X = -500000;	wp1.Y = FT_5000;		wp1.Z =	3000000; //RDH 12/07/99
			break;
		}
		case	DUTYESCORT:
		{
			wp0.X = 1000000;	wp0.Y = FT_20000;	wp0.Z =	2000000;
			wp1.X = -1000000;	wp1.Y = FT_20000;	wp1.Z =	2000000;
			break;

		}
		case	DUTYBARCAP:
		case	DUTYMIGCAP:
		{
			wp0.X = 2000000;	wp0.Y = FT_30000;	wp0.Z =	2500000;
			wp1.X = -2000000;	wp1.Y = FT_30000;	wp1.Z =	2500000;
			break;

		}
		case	DC_CAS:
		{
			wp0.X = 400000;		wp0.Y = FT_8000;		wp0.Z =	2000000;
			wp1.X = -400000;	wp1.Y = FT_8000;		wp1.Z =	2000000;
			break;

		}
		case	DC_AR:	
		{
//DEADCODE RDH 25/03/99 			SupplyNode* node;
//DEADCODE RDH 25/03/99 			SupplyTree::Supply2UID	reftype;
//DEADCODE RDH 25/03/99 			node = SupplyTree::FindSupplyNodeForItem(targ,&reftype);
//DEADCODE RDH 25/03/99 			if (node)
//DEADCODE RDH 25/03/99 			{
//DEADCODE RDH 25/03/99 				if (reftype==SupplyTree::S2U_MAIN
//DEADCODE RDH 25/03/99 					&&	(node->forward)					
//DEADCODE RDH 25/03/99 					&&	(node->forward->suppliee)					
//DEADCODE RDH 25/03/99 					&&	(node->forward->suppliee->associated_item)					
//DEADCODE RDH 25/03/99 				)
//DEADCODE RDH 25/03/99 				targ2 = node->forward->suppliee->associated_item;
//DEADCODE RDH 25/03/99 				else
//DEADCODE RDH 25/03/99 				{
//DEADCODE RDH 25/03/99 					int index=reftype-SupplyTree::S2U_ROUTE0;
//DEADCODE RDH 25/03/99 					if (index>=0 && index<3)
//DEADCODE RDH 25/03/99 						targ2=node->route[index]->supplier->associated_item;
//DEADCODE RDH 25/03/99 					else
//DEADCODE RDH 25/03/99 						targ2=node->route[0]->supplier->associated_item;
//DEADCODE RDH 25/03/99 				}
//DEADCODE RDH 25/03/99 			}
//DEADCODE RDH 25/03/99 			else
//DEADCODE RDH 25/03/99 			{	// put in a rel wp if no item to go to 
//DEADCODE RDH 25/03/99 				//targ2 = UID_NULL;
//DEADCODE RDH 25/03/99 				wp1.X = -400000;
//DEADCODE RDH 25/03/99 				wp1.Y = 100000;
//DEADCODE RDH 25/03/99 				wp1.Z =	100000;
//DEADCODE RDH 25/03/99 			}
			SupplyNode* node;
			SupplyTree::Supply2UID	reftype;
			node = SupplyTree::FindSupplyNodeForItem(targ,&reftype);
			if (node)
			{
					patrolbeginitem = node->associated_item;
					int index=reftype-SupplyTree::S2U_ROUTE0;
					if (index>=0 && index<3)
						targ2=node->route[index]->supplier->associated_item;
					else
						targ2=node->route[0]->supplier->associated_item;
				
			}
			else
			{	// put in a rel wp if no item to go to 
				//targ2 = UID_NULL;
				wp1.X = -400000;
				wp1.Y = 100000;
				wp1.Z =	100000;
			}

			break;
		}
	}
	if (targ2)
	{
		group[grnum][0].primary.SGT=
			group[grnum][0].primary.ID=
				patrolbeginitem;
		group[grnum][0].primary.SGbandindex=
			 group[grnum][0].primary.groupindex=0;

	
		group[grnum][0].secondary.SGT=
			group[grnum][0].secondary.ID=
				targ2;
		group[grnum][0].secondary.SGbandindex=
			group[grnum][0].secondary.groupindex=0;
	}
	else
	{
		group[grnum][0].primary.SGT=
			group[grnum][0].primary.ID=
				UID_NULL;
		group[grnum][0].primary.SGbandindex=
			group[grnum][0].primary.groupindex=0;

		group[grnum][0].secondary.SGT=
			group[grnum][0].secondary.ID=
				UID_NULL;
		group[grnum][0].secondary.SGbandindex=
			group[grnum][0].secondary.groupindex=0;
	}
	switch (duty)
	{
		case	DC_AR:	
		{
//DeadCode RDH 30Mar99 			InsertWpBetween(waf,wal,patrolzone,wpstartloopno,grnum);
//DeadCode RDH 30Mar99 			GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
//DeadCode RDH 30Mar99 			if (targ2)
//DeadCode RDH 30Mar99 				InsertWpBetween(waf,wal,SavedGlobrefs(group[grnum][0].globrefind+1),wpstoploopchkno,grnum);
//DeadCode RDH 30Mar99 			else
//DeadCode RDH 30Mar99 			{
//DeadCode RDH 30Mar99 				UniqueID newwp=InsertWpBetween(wpf,wpl,patrolzone,wpstoploopchkno,grnum);
//DeadCode RDH 30Mar99 				info_waypoint* w=*Persons2::ConvertPtrUID(newwp);
//DeadCode RDH 30Mar99 				w->position.RecalcDeltasToMatch(wp1);
//DeadCode RDH 30Mar99 			}
			if (targ2)
			{
				UniqueID newwp=InsertWpBetween(waf,wal,SavedGlobrefs(group[grnum][0].globrefind),wpstartloopno,grnum);
				info_waypoint* w=*Persons2::ConvertPtrUID(newwp);
				wp1=w->World;
				wp1.Y=FT_5000;
				w->position.RecalcDeltasToMatch(wp1);
				GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				newwp=InsertWpBetween(waf,wal,SavedGlobrefs(group[grnum][0].globrefind+1),wpstoploopchkno,grnum);
				w=*Persons2::ConvertPtrUID(newwp);
				wp1=w->World;
				wp1.Y=FT_5000;
				w->position.RecalcDeltasToMatch(wp1);
			}else
			{
				InsertWpBetween(waf,wal,patrolzone,wpstartloopno,grnum);
				GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID newwp=InsertWpBetween(wpf,wpl,patrolzone,wpstoploopchkno,grnum);
				info_waypoint* w=*Persons2::ConvertPtrUID(newwp);
				w->position.RecalcDeltasToMatch(wp1);
			}

		}
		break;
		case	DC_BOMB:
//		case	DUTYDIVEBOMB:
		{
			UniqueID newwp=InsertWpBetween(waf,wal,SGR_Pack_Target,wpbombno,grnum);
			info_waypoint*	w=*Persons2::ConvertPtrUID(newwp);
			w->range=METRES7000;
			group[grnum][0].globrefind=0;
		}
		break;
		case	DC_CAS:	
		{
			UniqueID newwp=InsertWpBetween(waf,wal,SGR_Pack_Target,wpstartloopno,grnum);
			info_waypoint*	w=*Persons2::ConvertPtrUID(newwp);
			w->position.RecalcDeltasToMatch(wp0);

			GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
			newwp=InsertWpBetween(wpf,wpl,SGR_Pack_Target,wpstoploopchkno,grnum);
			w=*Persons2::ConvertPtrUID(newwp);
			w->position.RecalcDeltasToMatch(wp1);
			group[grnum][0].globrefind=0;
		}
		break;
		case	DC_WW:	
		case	DUTYESCORT:
		case	DUTYMIGCAP:	
		case	DUTYBARCAP:	
		{
			UniqueID newwp=InsertWpBetween(waf,wal,patrolzone,wpstartloopno,grnum);
			info_waypoint*	w=*Persons2::ConvertPtrUID(newwp);
			wp0.X+=patrolzonepos.X;
			wp0.Z+=patrolzonepos.Z;
			w->position.RecalcDeltasToMatch(wp0);

			GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
			newwp=InsertWpBetween(wpf,wpl,patrolzone,wpstoploopchkno,grnum);
			w=*Persons2::ConvertPtrUID(newwp);
			wp1.X+=patrolzonepos.X;
			wp1.Z+=patrolzonepos.Z;
			w->position.RecalcDeltasToMatch(wp1);
			group[grnum][0].globrefind=0;
		}
	}
}

UniqueID	Profile::Wave::MakeGroup(bool iswave0,bool AAA)
{
	for (int sq=0;sq<5;sq++)
		breakif (Todays_Packages.SquadACAvail(sq)>=Todays_Packages.SquadACUsed(sq)+4);
	UniqueID rv = UID_NULL;
	if (sq < 5)
	{
		int grnum=AAA?1:2;
		Group& newgrp=group[grnum];
		info_airgrp* a=new info_airgrp;
		newgrp.uid=
			a->uniqueID.count=
				rv=Persons2::assignuid(BlueAcBAND);
		Persons2::tabulateUID(a);
		newgrp.SetFlights(1);
	//	a->inform=4;
		a->inwing=2;
	//	a->type=sq;
		newgrp.SetSquad(sq);
	//	newgrp.takeoffAF=
	//			SupplyTree::airfieldinfo[MMC.squad[sq].airfieldindex].airfield;//SquadronInfo							//TEMP
	//		UID_AfRdSinuiju;							//TEMP

		a->duty= AAA?DC_WW:DUTYESCORT;
		a->attmethod=0;
		a->attpattern=0;
		a->radiosilence = 0;

		a->form=SQUAD_FLATV;//new ListFormExpr(2);							//CSB 19May99
	//	a->form[0]=SQUAD_FLATV;a->form[1]=SQUAD_FLATV;				//CSB 19May99
		a->bombs=new ListFormExpr(4);
		a->bombs[0]=0;a->bombs[1]=0;a->bombs[2]=0;a->bombs[3]=0;
		a->leader=0;
		MakeWayPoints(iswave0, grnum, a->duty.Evaluate(),UID_NULL);
	}
	return rv;
}

UniqueID	Profile::MakeWave(int wavenum,int duty)
{
	for (int sq=0;sq<5;sq++)
		breakif (Todays_Packages.SquadACAvail(sq)>=Todays_Packages.SquadACUsed(sq)+4);
	UniqueID rv = UID_NULL;
	if (sq < 5)
	{
		info_airgrp* a=new info_airgrp;
		wave[wavenum][0].uid=
			a->uniqueID.count=
				rv=Persons2::assignuid(BlueAcBAND);
		int uid = wave[wavenum][0].uid;
		Persons2::tabulateUID(a);
		wave[wavenum][0].SetFlights(1);
		wave[wavenum][0].SetSquad(sq);

		for (int i = 0; i <3;i++)			//rdh
			wave[wavenum][i].callname = -1;
	//	a->inform=4;
		a->inwing=2;
	//	a->type=sq;
	//	group[0].SetSquad(sq);
	//	group[0].takeoffAF=
	//			SupplyTree::airfieldinfo[MMC.squad[sq].airfieldindex].airfield;//SquadronInfo							//TEMP
	//		UID_AfRdSinuiju;							//TEMP
	//	Persons2::tabulateUID(a);
		a->duty=duty;
		a->attmethod=0;
		a->attpattern=0;
		a->radiosilence = 0;

		a->form=SQUAD_FLATV;//new ListFormExpr(2);							//CSB 19May99
	//	a->form[0]=SQUAD_FLATV;a->form[1]=SQUAD_FLATV;				//CSB 19May99
		a->bombs=new ListFormExpr(4);
		a->bombs[0]=0;a->bombs[1]=0;a->bombs[2]=0;a->bombs[3]=0;		  //JIM 24/03/99
		wave[wavenum][0][0].globrefind=FindSpareGlobref();
		wave[wavenum].firstwp=Profile::MakeSecondaryRoute((DutyType)duty);
		
 		wave[wavenum].MakeWayPoints(false, 0, a->duty.Evaluate(),packagetarget);
	}
	return rv;

}
UniqueID	Profile::MakePrimaryRoute(int Y)
{	//Build a route which links key points in package
	//points are:
	//	H:	primary home-base
	//	T:	target
	//	E:	egress
	//These are the globrefs 
		//Pack_Takeoff
		//Pack_Target
		//Pack_Regroup

	//route contains
	//	Rendevous	(H..T*.2)	- Wave forms up here
	//	Ingress		(H..T*.5)	- Cross front line
	//	Target		(H..T*.9)	- Approaching target - all do different roles
	//	Regroup		(T..E*.1)	- Finished bombing - all form up again
	//	Egress		(T..E*.9)	- exit over sea - B52s go home from here
	//	Disperse	(E..H*.7)	- break formation and fly to home airfields
	UniqueID rv=UID_Null;

	rv=MakeInterceptWP(SGR_Pack_Regroup,SGR_Pack_Takeoff,	70,rv,SGR_WPP_Disperse,Y,wpalandingno);
	rv=MakeInterceptWP(SGR_Pack_Target,SGR_Pack_Regroup,	90,rv,SGR_WPP_Egress,Y);
	rv=MakeInterceptWP(SGR_Pack_Target,SGR_Pack_Regroup,	10,rv,SGR_WPP_Regroup,Y);
	if (duty==DC_CAS)
		rv=MakeInterceptWP(SGR_Pack_Takeoff,SGR_Pack_Target,	90,rv,SGR_WPP_Target,Y,wp_start_cas);
	else
		rv=MakeInterceptWP(SGR_Pack_Takeoff,SGR_Pack_Target,	90,rv,SGR_WPP_Target,Y);
	rv=MakeInterceptWP(SGR_Pack_Takeoff,SGR_Pack_Target,	50,rv,SGR_WPP_Ingress,Y);
	rv=MakeInterceptWP(SGR_Pack_Takeoff,SGR_Pack_Target,	20,rv,SGR_WPP_Rendevous,Y);
	
	return	rv;
}
UniqueID	Profile::MakeSecondaryRoute(DutyType duty)
{	//Build a route which links key points in package
	//route contains
	//	Rendevous		- Wave forms up here
	//	Ingress			- Cross front line
	//	Target			- Approaching target - all do different roles
	//	Regroup			- Finished bombing - all form up again
	//	Egress			- exit over sea - B52s go home from here
	//	Disperse		- break formation and fly to home airfields
	//
	//Each of these is made as a angle relative waypoint from the main route.
	//Rendevous uses 
	UniqueID rv=UID_Null;
	rv=MakeInterceptWP(SGR_WPP_Disperse,SGR_Pack_Takeoff,	0,rv,SGR_WPC_Disperse,0,wpalandingno);	//FT_10000);
	rv=MakeInterceptWP(SGR_WPP_Regroup,SGR_WPP_Disperse,	0,rv,SGR_WPC_Egress,0);	//FT_10000);
	rv=MakeInterceptWP(SGR_WPP_Regroup,SGR_WPP_Egress,		0,rv,SGR_WPC_Regroup,0);	//FT_10000);
	if (duty==DC_CAS)
		rv=MakeInterceptWP(SGR_WPP_Target,SGR_WPP_Regroup,		0,rv,SGR_WPC_Target,0,wp_start_cas);	//FT_10000);
	else
		rv=MakeInterceptWP(SGR_WPP_Target,SGR_WPP_Regroup,		0,rv,SGR_WPC_Target,0);	//FT_10000);
	rv=MakeInterceptWP(SGR_WPP_Ingress,SGR_WPP_Target,		0,rv,SGR_WPC_Ingress,0);	//FT_10000);
	rv=MakeInterceptWP(SGR_WPP_Rendevous,SGR_WPP_Ingress,	0,rv,SGR_WPC_Rendevous,0);//FT_10000);
	return	rv;
}

UniqueID	Profile::MakeInterceptWP(SavedGlobrefs a,SavedGlobrefs b,int percent,UniqueID next,SavedGlobrefs as,int deltaalt,BFieldWaypointActions action/*=wpacnoactionno*/)
{
	UniqueID rv;
	info_waypoint* wp0=new info_waypoint;
	wp0->range=10000;
	wp0->position.MakeIcptGRExpr(a,b);
	wp0->position[1][1]=deltaalt;
	wp0->position[2][1]=percent;
	wp0->position[2][2]=0;
//DEADCODE JIM 24/03/99 	wp0->position[2][3]=0;		  //pitch mod!
	wp0->nextwp=next;
	wp0->uniqueID.count=
		rv=Persons2::assignuid(WayPointBAND);
	info_waypoint *wp;
//DEADCODE JIM 03/03/99 	if (rv == 355)	//debug
//DEADCODE JIM 03/03/99 	{
//DEADCODE JIM 03/03/99   		wp = *Persons2::ConvertPtrUID(rv);
//DEADCODE JIM 03/03/99 	}
	if (action!=wpacnoactionno)
		wp0->wpact=action;
	Persons2::tabulateUID(wp0);
	if (as!=SGR_BLANK)
		wp0->uid=-as;
	if (next)
	{
		wp0=*Persons2::ConvertPtrUID(next);
		wp0->prevwp=rv;
	}
	return rv;
}

bool	Profile::Wave::GetKeyTargetWPs(UniqueID& targetarea,UniqueID& firststartpatrolbomb,UniqueID& laststartpatrolbomb,UniqueID& firstendpatrol,UniqueID& lastendpatrol,UniqueID& regrouparea)
{	//if there are no target waypoints then sets TARGET as all 4 and returns false
	firststartpatrolbomb=
		laststartpatrolbomb=
			firstendpatrol=
				lastendpatrol=
					UID_Null;
	UniqueID u=firstwp;
	info_waypoint* w=*Persons2::ConvertPtrUID(u);
	while(w->uid.Evaluate()!=-SGR_WPP_Target &&	w->uid.Evaluate()!=-SGR_WPC_Target)
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	targetarea=u;
	while(w->uid.Evaluate()!=-SGR_WPP_Regroup && w->uid.Evaluate()!=-SGR_WPC_Regroup)
	{
		if (w->wpact.Evaluate()!=GOT_UNDEFINED_VAL)
			if(		w->wpact.Evaluate()==wpstoploopchkno 
				||	w->wpact.Evaluate()==wpsecondaryno)
				if (firstendpatrol)
					lastendpatrol=u;
				else
					firstendpatrol=u;
			else
				if (firststartpatrolbomb)
					laststartpatrolbomb=u;
				else
					firststartpatrolbomb=u;
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	}
	regrouparea=u;
	if (!firststartpatrolbomb)
		firststartpatrolbomb=targetarea;
	if (!laststartpatrolbomb)
		laststartpatrolbomb=firststartpatrolbomb;
	if (!firstendpatrol)
		firstendpatrol=laststartpatrolbomb;
	if (!lastendpatrol)
		lastendpatrol=firstendpatrol;
	return (lastendpatrol!=targetarea);
}

//wpacnoactionno
UniqueID	Profile::Wave::FindWpBetween(UniqueID wp1,UniqueID wp2,int group,int flight,int elt)
{
	UniqueID u=wp1;
	info_waypoint *w=*Persons2::ConvertPtrUID(u);

	forever
	{
		if (group==w->applygroup.Evaluate())
			if (	flight==-1	||	w->applyflight.Evaluate()==GOT_UNDEFINED_VAL
				||	w->applyflight.Evaluate()==flight)
				if (elt==-1 || w->applyelt.Evaluate()==GOT_UNDEFINED_VAL
					||	elt==w->applyelt.Evaluate())
					return(u);
		if (u==wp2)	
			return(UID_Null);
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	}
//	return UID_Null;
}
UniqueID	Profile::Wave::FindWpAfter(UniqueID wp1,UniqueID wp2,int group,int flight,int elt)
{
	UniqueID u=wp1;
	if (!u || u==wp2)
		return UID_Null;
	info_waypoint *w=*Persons2::ConvertPtrUID(u);
	w=*Persons2::ConvertPtrUID(u=w->nextwp);
	forever
	{
		if (group==w->applygroup.Evaluate())
			if (	flight==-1	||	w->applyflight.Evaluate()==GOT_UNDEFINED_VAL
				||	w->applyflight.Evaluate()==flight)
				if (elt==-1 || w->applyelt.Evaluate()==GOT_UNDEFINED_VAL
					||	elt==w->applyelt.Evaluate())
					return(u);
		if (u==wp2)	
			return(UID_Null);
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	}
//	return UID_Null;
}

void	Profile::Wave::RemoveWpBetween(UniqueID&wp1,UniqueID&wp2,UniqueID wptoremove)
{
	if (!wptoremove)
		return;
	info_waypoint *w=*Persons2::ConvertPtrUID(wptoremove);
	info_waypoint *wn=*Persons2::ConvertPtrUID(w->nextwp);
	info_waypoint *wp=*Persons2::ConvertPtrUID(w->prevwp);
	wn->prevwp=w->prevwp;
	wp->nextwp=w->nextwp;
	if (wp1==wptoremove)
		if (wp2==wp1)
			wp2=wp1=w->prevwp;
		else
			wp1=w->nextwp;
	else
		if (wp2==wptoremove)
			wp2=w->prevwp;
	delete(w);
	Persons2::delUID(wptoremove);
}

UniqueID	Profile::Wave::InsertWpBetween(UniqueID&wp1,UniqueID&wp2,SavedGlobrefs targetref,BFieldWaypointActions a,int group,int flight,int elt)
{
	info_waypoint *w=new info_waypoint;
	UniqueID rv=
		w->uniqueID.count=Persons2::assignuid(WayPointBAND);
	Persons2::tabulateUID(w);

	UniqueID	pu;
	if (a)
	{
		w->wpact=a;
	}
	pu=wp1;
	if (targetref)
		if (targetref==SGR_WPP_Target || targetref==SGR_WPC_Target)
		{

			w->position.MakeAngWorldPos(targetref,100000);
//DEADCODE JIM 28/06/99 			w->target=new GlobRefExpr(targetref);
		}
		else
		{

			w->position.MakeAbsWorldPos(100000);
			w->target=new GlobRefExpr(targetref);
		}
	else
	{
		w->position.MakeAbsWorldPos(100000);
		w->target=new GlobRefExpr(SGR_Pack_Target);
	}
	info_waypoint *wp=*Persons2::ConvertPtrUID(pu);
	w->range=METRES100;												  //JIM 08/04/99
	w->nextwp=wp->nextwp;
	wp->nextwp=rv;
	w->prevwp=pu;
	info_waypoint *wn=*Persons2::ConvertPtrUID(w->nextwp);
	if (wn)
		wn->prevwp=rv;

	w->applygroup=group;
	if (flight!=-1)		w->applyflight=flight;
	if (elt!=-1)   		w->applyelt=elt;

	if (a && wp1==wp2)
	{	//fix route list delimiters
		if (wp->wpact.Evaluate()==0 || wp->wpact.Evaluate()==GOT_UNDEFINED_VAL)
			wp1=rv;
		wp2=rv;
	}
	return rv;
}
void	Profile::ResetPatrolItems()
{
	UniqueID oldprimarySGT = wave[0][0][0].primary.SGT;
	UniqueID oldsecondarySGT = wave[0][0][0].secondary.SGT;
	UniqueID newprimarySGT;
	UniqueID newsecondarySGT; 

	SupplyNode* node;
	SupplyTree::Supply2UID	reftype;

	node = SupplyTree::FindSupplyNodeForItem(packagetarget,&reftype);
	if (node)
	{
		newprimarySGT = node->associated_item;
		int index=reftype-SupplyTree::S2U_ROUTE0;
		if (index>=0 && index<3)
			newsecondarySGT=node->route[index]->supplier->associated_item;
		else
			newsecondarySGT=node->route[0]->supplier->associated_item;
	
	   for(int wav=0;wav<Profile::MAX_WAVES;wav++)
			for (int grp=0;grp<Profile::MAX_GROUPS;grp++)
				for (int f=0;f<Profile::MAX_FLIGHTS;f++)
				{
					if 	(wave[wav][grp][f].primary.SGT == oldprimarySGT)
							wave[wav][grp][f].primary.SGT = wave[wav][grp][0].primary.ID= newprimarySGT;
					if 	(wave[wav][grp][f].secondary.SGT == oldsecondarySGT)
							wave[wav][grp][f].secondary.SGT = wave[wav][grp][0].secondary.ID= newsecondarySGT;
				}
	}
}
void	Profile::RecalcRoutePositions()
{
	SetTargetGlobrefs();
	RecalcPrimaryPositions();
	CalcWPTimes(0);

	for (int i=1;i<MAX_WAVES;i++)
		if (wave[i].firstwp)
		{
			RecalcSecondaryPositions(i);
			CalcWPTimes(i);
		}

}

void	Profile::SetTargetGlobrefs(bool fixconvoys)
{
	packagetakeoff=wave[0][0].takeoffAF;
	UniqueID targ=packagetarget;
	if (Persons2::getbandfromUID(targ)==RedRoadBAND || Persons2::getbandfromUID(targ)==RedRailBand	)				  //JIM 12/04/99
	{
		SupplyNode* node= SupplyTree::FindSupplyNodeForNodeItem(targ);
		targ=node->associated_item;
	}

	Persons2::SetLoc(SGR_Pack_Target,targ);
	Persons2::SetLoc(SGR_Pack_Regroup,egressloc);
	Persons2::SetLoc(SGR_Pack_Takeoff,packagetakeoff);
	for (int gr=SGR_Pack_Targ_F0_E0;gr<=SGR_Pack_Targ_Fmax_E1;gr++)
		Persons2::SetLoc(gr,0);

	for(int wav=0;wav<Profile::MAX_WAVES;wav++)
		for (int grp=0;grp<Profile::MAX_GROUPS;grp++)
			for (int fl=0,ft=wave[wav][grp].numflights;fl<ft;fl++)
				if ((gr=wave[wav][grp][fl].globrefind)!=0)
					if (wave[wav][grp][fl].primary.ID || wave[wav][grp][fl].secondary.ID)
					{
						Persons2::SetLoc(gr,wave[wav][grp][fl].primary.ID);
						Persons2::SetLoc(gr+1,wave[wav][grp][fl].secondary.ID);
					}
}

void	Profile::RecalcPrimaryPositions()
{
	packagetakeoff=wave[0][0].takeoffAF;
	SetGlobRefsForRoute(wave[0].firstwp);
	RepositionSubWaypoints(wave[0].firstwp);
}
void	Profile::RecalcSecondaryPositions(int w)
{
	SetGlobRefsForRoute(wave[w].firstwp);
	RepositionSubWaypoints(wave[w].firstwp);
}

void	Profile::SetGlobRefsForRoute(UniqueID wpuid)
{
	while (wpuid)
	{
		info_waypoint* w=*Persons2::ConvertPtrUID(wpuid);
		if (w->uid!=GOT_UNDEFINED_VAL)
		{
			w->World.X=w->World.Y=w->World.Z=0;
			w->position.EvalW(w->World);
			if (w->target.Evaluate()!=GOT_UNDEFINED_VAL)
			{
				COORDS3D& base=
					Persons2::ConvertPtrUID(UniqueID(w->target.Evaluate()))->World;
				w->World.X+=base.X;
				w->World.Y+=base.Y;
				w->World.Z+=base.Z;
			}
			Persons2::SetLoc(-w->uid,w->uniqueID.count);
		}
		wpuid=w->nextwp;
	}

}

void	Profile::RepositionSubWaypoints(UniqueID wpuid)
{
	while (wpuid)
	{
		info_waypoint* w=*Persons2::ConvertPtrUID(wpuid);
		if (w->uid==GOT_UNDEFINED_VAL)
		{
			w->World.X=w->World.Y=w->World.Z=0;
			w->position.EvalW(w->World);
			if (w->target.Evaluate()!=GOT_UNDEFINED_VAL && w->target.Evaluate()!=UID_NULL)
			{
				COORDS3D& base=
					Persons2::ConvertPtrUID(UniqueID(w->target.Evaluate()))->World;
				w->World.X+=base.X;
				w->World.Y+=base.Y;
				w->World.Z+=base.Z;
			}
		}
		wpuid=w->nextwp;
	}
}
int	PackageList::SquadACAvail(int sqnum)
{//must not return more than 16
	if (		(		(Miss_Man.currcampaignnum != MissMan::F86_CAMPAIGN) //rdh 29/04/99
					&&	(Miss_Man.currcampaignnum != MissMan::SO51_CAMPAIGN) //rdh 29/04/99
				)													  //rdh 29/04/99
			&&	(	(sqnum == SQ_B29) || (sqnum == SQ_B26)			  //rdh 29/04/99
				)													  //rdh 29/04/99
		)															  //rdh 29/04/99
	{																  //rdh 29/04/99
		return (0);													  //rdh 29/04/99
	}																  //rdh 29/04/99
	if (sqnum < PILOTABLE_SQUADRONS)
	{
		if (MMC.squad[sqnum].ac_total_avail > 16)
			return(16);
		else
			return(MMC.squad[sqnum].ac_total_avail);
	}
	else
	{
		if  (		(MMC.squad[SQ_F86A].ac_total_avail >=4)
				||	(MMC.squad[SQ_F86B].ac_total_avail >=4)			
				||	(MMC.squad[SQ_F80].ac_total_avail>=4)			
				||	(MMC.squad[SQ_F84].ac_total_avail >=4)			
			)
	  		return(MAXACPERSQUAD);
		else
			return(0);
	}
//Old_Code DAW 12Nov98 	if (sqnum<SQ_B_NONFLYABLE)
//Old_Code DAW 12Nov98 		return(MMC.squad[sqnum].ac_total_avail);
//Old_Code DAW 12Nov98 	else
//Old_Code DAW 12Nov98 		return 16;
}
int	PackageList::SquadACUsed(int sqnum)
{
	int retv=0;
	for (int pack=0;pack<Profile::MAX_PACKS;pack++)
		for (int wave=0;wave<Profile::MAX_WAVES;wave++)
			for (int group=0;group<Profile::MAX_GROUPS;group++)
				if (this[0][pack][wave][group].uid && this[0][pack][wave][group].squadron==sqnum)
				{
					info_airgrp* a=*Persons2::ConvertPtrUID(this[0][pack][wave][group].uid);
					retv+=a->inform.Evaluate();
				}
	return(retv);

//	int retv=0;
//	for (int pack=0;pack<Profile::MAX_PACKS;pack++)
//		for (int wave=0;wave<Profile::MAX_WAVES;wave++)
//			for (int group=0;group<Profile::MAX_GROUPS;group++)
//			{
//				info_airgrp* a=*Persons2::ConvertPtrUID(this[0][pack][wave][group].uid);
//				if ((a) &&	(a->type == sqnum))
//				{
//					
//					retv+=a->inform.Evaluate();
//				}
//			}
//	return(retv);

}
Float Profile::RelDensity(SLong alt)
{
	Float reldensity;
	reldensity = 1 - 8.9117e-7* alt + 2.2625e-13 * alt * alt;

	return(reldensity);
}

int Profile::CalcFuel(struct COORDS3D * last,struct COORDS3D * wp,int leadtype,int esctype, SWord StoresDrag)	//CSB 18/06/99
{
	//use the leadtype to find the time of travel (use its velocities)
	//use the escort type to find the fuel rates
	SLong horitime, climbtime;
	CalcHoriAndClimbTime(last, wp, horitime, climbtime, leadtype, esctype, StoresDrag);					//CSB 18/06/99
	int lastY = last->Y;
	int wpY= wp->Y;
 	if (leadtype != esctype)
 	{
 		if (lastY != 0)
 			lastY =  MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_1000;
 		if (wpY != 0)
 			wpY =  MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_1000;
 	}

	SLong deltaY = wpY - lastY;

	Float FuelUsageRate;
	Float reldensity;
	FuelUsageRate = 0.9;
	
	int type=Persons3::Squad2Type(esctype);
	ClassPtr actype;
	actype = Plane_Type_Translate[type][0];

	SLong alt = lastY;
	if (deltaY > 10000)
		//climb first for fuel economy
		alt = wpY;
	reldensity = RelDensity(alt);
	Float usage = FuelUsageRate * horitime * actype->fuelaboff * reldensity	;//s * cg/cs
	usage = usage * 100;	//cg

	if (deltaY > 10000)
		  FuelUsageRate = 1.0;
	else if (deltaY < -10000)
		  FuelUsageRate = 0.5;
	else
		FuelUsageRate = 0.9; 
	reldensity = RelDensity((wpY+lastY)/2);
 	Float climbusage = FuelUsageRate * climbtime * actype->fuelaboff * reldensity;//s * cg/cs
	climbusage = climbusage* 100;	//cg


	return	(usage + climbusage);

}
void Profile::CalcHoriAndClimbTime(struct COORDS3D * last,struct COORDS3D * wp,SLong& horitime,SLong& climbtime,int type, int esctype, SWord StoresDrag)	//CSB 18/06/99
{
	//workout the horizontal distance
	//split into horidist and climbdist
	//use horivel and climb vel to work out time
	int lastY = last->Y;
	int wpY= wp->Y;

 	if (type != esctype)
 	{
 		if (lastY != 0)
 			lastY =  MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_1000;
 		if (wpY != 0)
 			wpY =  MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_1000;
 	}

	SLong x = wp->X - last->X;
	SLong y = wpY - lastY;
	SLong z = wp->Z - last->Z;
	SLong dist = Math_Lib.Distance2d(x,z);
//bestclimbpitch
	type=Persons3::Squad2Type(type);
	ClassPtr actype;
	actype = Plane_Type_Translate[type][0];

	UWord p = (UWord) (actype->bestclimbpitch.a);
	
	p *= (9000 - StoresDrag) / 9000;
	p -= StoresDrag / 10;

	Float pitch = ((Float)p);
	pitch = pitch / 10430.37835047;
	Float sinpitch = FSin (pitch);
	Float cospitch = FCos (pitch);
	Float climbdist = y / sinpitch;
	Float  hclimbdist;
	Float  horidist;

	if (climbdist < 0)
		climbdist = - climbdist;

	if (climbdist < dist)
	{
		hclimbdist = (climbdist *  cospitch);
		horidist = dist - hclimbdist;
	}else
	{
		climbdist = dist;
		horidist = 0;
	}
	
	//assume descent time is same as for climb
	climbtime = climbdist / (actype->bestclimbvel * 10);

//DeadCode CSB 16/06/99		horitime = horidist / (actype->cruisevel * 10);		//  cm and mm/cs
	
	SWord ResCruiseVel = actype->cruisevel;

	if((actype->visible == F51) || (actype->visible == YAK9))
	{
		FP VelFraction = 1.0 - FP(StoresDrag) * 0.00006;
		FP fMaxVel	   = FP(ResCruiseVel) * VelFraction;
		ResCruiseVel = fMaxVel;
	}
	else
	{
		SLong DeltaVel	 = (175 * StoresDrag) / 1000;
		if(DeltaVel > 0)
			ResCruiseVel -= DeltaVel;
	}
//DeadCode CSB 18/06/99		ResCruiseVel -= (715 * StoresDrag) / 1000;

	SLong MaxAlt = wp->Y;
	if(last->Y > wp->Y) MaxAlt = last->Y;

	if((Save_Data.flightdifficulty [FD_WINDEFFECTS]) && (MaxAlt > 1036333))		// 34,000 ft
	{
		SLong wx, wy, wz;
		MMC.Sky.GetWind(MaxAlt, wx, wy, wz);
		
		FP WindComp = 0;
		if(dist)
			WindComp = ((FP)x * (FP)wx + (FP)z * (FP)wz) / (FP)dist;
		ResCruiseVel += WindComp;
	}


	horitime = horidist / (ResCruiseVel * 10);		//  cm and mm/cs



}
int Profile::ValidateTime(CString* buffer, int packnum, int wavenum)
{
	
	int time = 0;
		if  (	(buffer->GetLength() > 0 )
			&&				(buffer->GetLength() < 6 )			)
		{
			char	buff[5];
			strcpy(buff,*buffer);
			char*	hr = buff;
			char*	cnt = hr;
			char*	min;

			while ( (*cnt >= 48) && (*cnt <= 57))
				*cnt++;
			*cnt++ = 0;
			min = cnt;
			while ( (*cnt >= 48) && (*cnt <= 57))
				*cnt++;
			*cnt++ = 0;
			time = atoi(min) + 60 * atoi(hr);

			int currtime;
			if (Miss_Man.currcampaignnum==Miss_Man.SO51_CAMPAIGN)
			{
				if (MMC.debrief.currperiod == 0)
					currtime = MORNINGPERIODSTART/60;
				if (MMC.debrief.currperiod == 1)
					currtime = MIDDAYPERIODSTART/60;
				if (MMC.debrief.currperiod == 2)
					currtime = AFTERNOONPERIODSTART/60;
			}
			else
			{														  //JIM 02/09/99
				currtime=Todays_Packages[0][0].targettime/60;
				if (currtime>AFTERNOONPERIODSTART/60)
					currtime=AFTERNOONPERIODSTART/60;
				else
				if (currtime>MIDDAYPERIODSTART/60)
					currtime=MIDDAYPERIODSTART/60;
				else
					currtime=MORNINGPERIODSTART/60;
			}
			if (time < currtime)
				time = currtime;
			if (time > (currtime + (HR02 + MIN30+ MIN5)/60))
				 time = (currtime + (HR02 + MIN30+ MIN5)/60);

		}
		return(time);

}
int Profile::CalcTime(struct COORDS3D * last,struct COORDS3D * wp,int type, int esctype, SWord StoresDrag)	//CSB 18/06/99	

{
	//if not patrol then add 5 minutes around target
	//patrol is handled retrospectively when fuel at end is known 
	SLong horitime, climbtime;
	CalcHoriAndClimbTime(last, wp, horitime, climbtime, type, esctype, StoresDrag);					//CSB 18/06/99	


	int time = horitime+climbtime;
	return	(time);
//	return	(1800);

}


void	Profile::ClearWave(int w)
{	//Delete route and aircraft in wave slot 
	UniqueID u=wave[w].firstwp;
	wave[w].firstwp=UID_NULL;
	while (u)
	{
		info_waypoint *w=*Persons2::ConvertPtrUID(u);
		if ( u == Todays_Packages.hiwp)
				Todays_Packages.hiwp = UID_NULL;
		Persons2::delUID(u);
		u=w->nextwp;
		delete w;
	}
	ClearGroup(w,0);
	ClearGroup(w,1);
	ClearGroup(w,2);
}

void	Profile::ClearGroup(int w,int g)
{
	
	if (wave[w][g].uid)
	{
//DEADCODE RDH 05/07/99 		wave[w][g].SetFlights(0);									  //RDH 14/06/99
		UniqueID* u=&wave[w].firstwp;
		while (*u)
		{
			info_waypoint *w=*Persons2::ConvertPtrUID(*u);
			if (w->applygroup.Evaluate()==g)
			{
				Persons2::delUID(*u);
				*u=w->nextwp;
				delete w;
			}
			else
				u=&w->nextwp;
		}
		info_airgrp *a=*Persons2::ConvertPtrUID(wave[w][g].uid);
		Persons2::delUID(wave[w][g].uid);
		delete a;
	}
	wave[w][g].uid=UID_NULL;
	wave[w][g].takeoffAF = UID_NULL;
	wave[w][g].SetFlights(0);									  //RDH 14/06/99 //RDH 05/07/99

}

void	PackageList::ClearPack(int p)
{
	for (int w=0;w<Profile::MAX_WAVES;w++)
		pack[p].ClearWave(w);
//	pack[p].packname[0]=0;
//	pack[p].packagetakeoff=	pack[p].packagetarget	=pack[p].regrouploc=UID_NULL;

	pack[p].packname[0] = 0;
	pack[p].redo = false;
	pack[p].edited = false;
	pack[p].packagetakeoff = UID_NULL;							
	pack[p].packagetarget = UID_NULL;
	pack[p].egressloc = UID_NULL;
	pack[p].wpsused=0;



}

void	PackageList::WipeAll()
{
	for (int p=0;p<Profile::MAX_PACKS;p++)
	{
		pack[p].packagetarget=UID_NULL;
		pack[p].redo = false;
		pack[p].edited = false;

		for (int w=0;w<Profile::MAX_WAVES;w++)
		{
			pack[p][w].firstwp=UID_NULL;
			for (int g=0;g<Profile::MAX_GROUPS;g++)
				pack[p][w][g].uid=UID_NULL;
		}
	}
}

void	PackageList::ShuntPack(int p)
{	
	if 	(pack[p][0].firstwp)
	{	//shunt up
		//I assume it fits!!!
		Profile tmp=pack[Profile::MAX_PACKS-1];
		for (int i=Profile::MAX_PACKS-1;i>p;i--)
			pack[i]=pack[i-1];
		pack[p]=tmp;
	}
	else
	{	//shunt down
		Profile tmp=pack[p];
		for (int i=p+1;i<Profile::MAX_PACKS;i++)
			pack[i-1]=pack[i];
		pack[Profile::MAX_PACKS-1]=tmp;
	}
}

void	Profile::ShuntWave(int w)
{
	if (wave[w].firstwp)
	{	//shunt up - I assume it fits!
		Profile::Wave tmp=wave[MAX_WAVES-1];
		for (int i=MAX_WAVES-1;i>w;i--)
			wave[i]=wave[i-1];
		wave[w]=tmp;
	}
	else
	{	//shunt down
		Profile::Wave tmp=wave[w];
		for (int i=w+1;i<MAX_WAVES;i++)
			wave[i-1]=wave[i];
		wave[MAX_WAVES-1]=tmp;
	}
}

///////////////////////////////////////////////////
//
// Low level supplytree routines
//
//
AirFieldInfo*	SupplyTree::FindAirfieldForItem(UniqueID u)
{
	for (int i=0;airfieldinfo[i].nationality!=NAT_ALIGN;i++)
		if (airfieldinfo[i].airfield==u)
			return airfieldinfo+i;
	return NULL;
}

SupplyTree::Supply2UID	SupplyTree::NodeHoldsUID(UniqueID u,SupplyNode* search)
{
	if (search)
	{
		if(search->associated_item==u) return  S2U_MAIN;
//TEMPCODE DAW 09/06/99 		if(search->airfield[0]==u) return S2U_AF0;
//TEMPCODE DAW 09/06/99 		if(search->airfield[1]==u) return S2U_AF1;
//TEMPCODE DAW 09/06/99 		if(search->airfield[2]==u) return S2U_AF2;
		SupplyRoute*	s2;
		for (s2=search->route[0];s2;s2=s2->alternateroute)
		{
			if (s2->redsupplyUID==u)	return S2U_ROUTE0;
			if (s2->associated_brdg==u)	return S2U_ROUTE0;
		}
		for (s2=search->route[1];s2;s2=s2->alternateroute)
		{
			if (s2->redsupplyUID==u)	return S2U_ROUTE1;
			if (s2->associated_brdg==u)	return S2U_ROUTE1;
		}
		for (s2=search->route[2];s2;s2=s2->alternateroute)
		{
			if (s2->redsupplyUID==u)	return S2U_ROUTE2;
			if (s2->associated_brdg==u)	return S2U_ROUTE2;
		}
	}
	return S2U_NOTHERE;
}


void	SupplyTree::FillNatForUID(UniqueIDField& f)
{
	f=0;	//clears all bits
	SupplyNode* search;
	for (search=FirstNode;search->next!=search;search=search->next)
	{
//DEADCODE RDH 14/05/99 		if (search->status==BEHINDREDLINES)
		if (search->status!=BEHINDBLUELINES)
		{
			if (search->status!=BEHINDBLUELINES)
			{
				f|=search->associated_item;
				f|=search->associated_town;
			}
			if (search->attackstats.damagelevel>90)
			{
				ItemPtr p=*Persons2::ConvertPtrUID(search->associated_item);
				p->Status.deaded=TRUE;
			}
			if (search->attackstown.damagelevel>90)
			{
				ItemPtr p=*Persons2::ConvertPtrUID(search->associated_town);
				p->Status.deaded=TRUE;
			}
//DeadCode JIM 19Feb99 			f|=search->airfield[0];
//DeadCode JIM 19Feb99 			f|=search->airfield[1];
//DeadCode JIM 19Feb99 			f|=search->airfield[2];
			SupplyRoute*	s2;
			for (s2=search->route[0];s2;s2=s2->alternateroute)
			{
				if (search->status!=BEHINDBLUELINES)
				{
					f|=s2->associated_brdg;
					f|=s2->redsupplyUID;
				}
				if (s2->attackstats.damagelevel>90)
				{
					ItemPtr p=*Persons2::ConvertPtrUID(s2->associated_brdg);
					if (p)
						p->Status.deaded=TRUE;
				}
			}
			for (s2=search->route[1];s2;s2=s2->alternateroute)
			{
				if (search->status!=BEHINDBLUELINES)
				{
					f|=s2->associated_brdg;
					f|=s2->redsupplyUID;
				}
				if (s2->attackstats.damagelevel>90)
				{
					ItemPtr p=*Persons2::ConvertPtrUID(s2->associated_brdg);
					if (p)
						p->Status.deaded=TRUE;
				}
			}
			for (s2=search->route[2];s2;s2=s2->alternateroute)
			{
				if (search->status!=BEHINDBLUELINES)
				{
					f|=s2->associated_brdg;
					f|=s2->redsupplyUID;
				}
				if (s2->attackstats.damagelevel>90)
				{
					ItemPtr p=*Persons2::ConvertPtrUID(s2->associated_brdg);
					if (p)
						p->Status.deaded=TRUE;
				}
			}
		}
	}
	for (int af=0;airfieldinfo[af].nationality!=NAT_ALIGN;af++)
	{
		if (		(airfieldinfo[af].nationality==NAT_RED)
				||	(airfieldinfo[af].nationality==NAT_AMBER)		  //RDH 25/05/99
		   )
			f|=airfieldinfo[af].airfield;
			if (airfieldinfo[af].attackstats.damagelevel>90)
			{
				ItemPtr p=*Persons2::ConvertPtrUID(airfieldinfo[af].airfield);
				if (p)
					p->Status.deaded=TRUE;
			}
	}
}
void	SupplyTree::FillFL_Icons(SupplyLine* SL, FileNum* FL_Icon)
{
	for (int i=0;i<SL->groundbattle.usedteams;i++)
	{
		bool teamisblue = true;
		if	(SL->initiative==REDATTACKING)
		{
			if (SL->groundbattle.teamlist[i].team == TeamDef::AWAY)
				teamisblue = false;
		}else
		{
			if (SL->groundbattle.teamlist[i].team == TeamDef::HOME)
				teamisblue = false;
		}

		if (		(SL->groundbattle.teamlist[i].location > AmberBattleNodeBAND)
				&&	(SL->groundbattle.teamlist[i].location < AmberBattleNodeBANDEND)
		   )
		{
			if (teamisblue)
			{
				switch (SL->groundbattle.teamlist[i].forcetype)
				{
					case  TeamDef::TROOPSONLY:
					case  TeamDef::MORTAR:
					{
						FL_Icon[SL->groundbattle.teamlist[i].location - AmberBattleNodeBAND] = FIL_ICON_B_TROOP_OFF2;
						break;
					}
					case  TeamDef::MORTARTRUCK:
					{
						FL_Icon[SL->groundbattle.teamlist[i].location - AmberBattleNodeBAND] = FIL_ICON_B_TRUCK_OFF2;
						break;
					}
					case  TeamDef::TANKS:
					{
						FL_Icon[SL->groundbattle.teamlist[i].location - AmberBattleNodeBAND] = FIL_ICON_B_TANK_OFF2;
						break;
					}
					case  TeamDef::ARTILLARY:
					{
						FL_Icon[SL->groundbattle.teamlist[i].location - AmberBattleNodeBAND] = FIL_ICON_B_ARTILLERY_OFF2;
						break;
					}
				}
			}else
			{
				switch (SL->groundbattle.teamlist[i].forcetype)
				{
					case  TeamDef::TROOPSONLY:
					case  TeamDef::MORTAR:
					{
						FL_Icon[SL->groundbattle.teamlist[i].location - AmberBattleNodeBAND] = FIL_ICON_R_TROOP_OFF2;
						break;
					}
					case  TeamDef::MORTARTRUCK:
					{
						FL_Icon[SL->groundbattle.teamlist[i].location - AmberBattleNodeBAND] = FIL_ICON_R_TRUCK_OFF2;
						break;
					}
					case  TeamDef::TANKS:
					{
						FL_Icon[SL->groundbattle.teamlist[i].location - AmberBattleNodeBAND] = FIL_ICON_R_TANK_OFF2;
						break;
					}
					case  TeamDef::ARTILLARY:
					{
						FL_Icon[SL->groundbattle.teamlist[i].location - AmberBattleNodeBAND] = FIL_ICON_R_ARTILLERY_OFF2;
						break;
					}
				}
			}
		}
	}
}
void	SupplyTree::FillFLS_Icons(FileNum* FL_Icon)
{
	for (int i =0; i < (AmberBattleNodeBANDEND-AmberBattleNodeBAND) ;i++)
		FL_Icon[i] = FIL_NULL;
	FillFL_Icons(&WestRoute, FL_Icon);
	FillFL_Icons(&CentralRoute, FL_Icon);
	FillFL_Icons(&EastRoute, FL_Icon);


}


Nationality	SupplyTree::GetNatForUID(UniqueID u,UniqueIDField& f)
{
	if (NodeHoldsUID(u,WestRoute.frontline)) return NAT_AMBER;
	if (NodeHoldsUID(u,EastRoute.frontline)) return NAT_AMBER;
	if (NodeHoldsUID(u,CentralRoute.frontline)) return NAT_AMBER;
	if (f[u]) 
		return NAT_RED;
	else
	{
		ItemPtr p=*Persons2::ConvertPtrUID(u);
		if (p)
			if (p->SGT)
				if (f[p->SGT])
				{
					f|=u;
					return NAT_RED;
				}
		return NAT_BLUE;
	}
}


SupplyNode*	SupplyTree::FindSupplyNodeForItem(UniqueID u,Supply2UID* relation)
{
	info_itemS *i=*Persons2::ConvertPtrUID(u);
	if (i && i->SGT)
		u=i->SGT;
	return	FindSupplyNodeForNodeItem(u,relation);
}
SupplyRoute*	SupplyTree::FindBridge(UniqueID u,SupplyRoute* route)
{
	for(int debugcount=10;route;route=route->alternateroute)
	{
		if (route->associated_brdg==u)			return route;
		if (route->redsupplyUID==u)	  			return route;
		if (!debugcount--)			  			return NULL;
	}
	return NULL;
}
SupplyNode*	SupplyTree::FindSupplyNodeForNodeItem(UniqueID u,Supply2UID* relation)
{
	SupplyNode* search;
	Supply2UID rel=S2U_MAIN;
	for (search=FirstNode;search->next!=search;search=search->next)
	{
		rel=S2U_MAIN;
		breakif(search->associated_item==u);
		breakif(search->associated_town==u);
		rel=S2U_AF0;
		breakif(search->airfield[0]==u);
		rel=S2U_AF1;
		breakif(search->airfield[1]==u);
		rel=S2U_AF2;
		breakif(search->airfield[2]==u);
		rel=S2U_ROUTE0;
		breakif(FindBridge(u,search->route[0]));
		rel=S2U_ROUTE1;
		breakif(FindBridge(u,search->route[1]));
		rel=S2U_ROUTE2;
		breakif(FindBridge(u,search->route[2]));
	}
	if (relation)
		*relation=rel;
	if (search->next!=search)
		return search;
	if (relation)
		*relation=S2U_NOTHERE;
	return NULL;
}

int	 SupplyRoute::SetSupplySizeGR()
{
	int trucks=storeslaunched/storespermobile;	//trucks per period
	trucks-=5;
	if (trucks<5)										//too few to see
		if (trucks>-2)//trucks at night
			if (Math_Lib.rnd(3))
				trucks=0;
			else
					trucks=trucks+5;							//make more visible
		else
			trucks=0;
	return trucks;
//DEADCODE DAW 10/05/99 ///					GR_WP1=playernode->forward->associated_brdg;
//DEADCODE DAW 10/05/99 						if (trucks>0)
//DEADCODE DAW 10/05/99 						rv=s->populateBF;


}

bool	SupplyRoute::SetSupplySizeGR(ULong& GR_FormSize00,ULong& GR_FormSize01,ULong& GR_FormSize02)
{
	int trucks=SetSupplySizeGR();
	GR_FormSize00=trucks;
	GR_FormSize01=trucks/2;
	GR_FormSize02=trucks/3;
	return (trucks>0);
}


FileNum SupplyTree::TargetToBf(UniqueID targ,UByte* convoysflagandaaalevelreturn)
{
	UByte aaalevelreturn;
	if (	!convoysflagandaaalevelreturn 
		&& (Persons2::getbandfromUID(targ)==RedRoadBAND || Persons2::getbandfromUID(targ)==RedRailBand)
		)
		return FIL_NULL;
	SupplyNode* search;
	Supply2UID rel;
	search=FindSupplyNodeForNodeItem(targ,&rel);
	FileNum	bf=FIL_NULL;
	if (search)
	{
		switch (rel)
		{	//S2U_NOTHERE=0,S2U_MAIN,S2U_AF0,S2U_AF1,S2U_AF2,S2U_ROUTE0,S2U_ROUTE1,S2U_ROUTE2
		case S2U_MAIN:		
			bf=search->populateBF;
			aaalevelreturn=search->attackstats.aaalevel;			  //JIM 01/06/99
		break;
		case S2U_AF0:
		case S2U_AF1:
		case S2U_AF2:
		{
			AirFieldInfo* af=FindAirfieldForItem(targ);
//			if (af->nationality==NAT_BLUE)
			bf = af->EmptyPopulateBF;
			aaalevelreturn=af->attackstats.aaalevel;
//			else
//				bf = FindAirfieldForItem(targ)->RedPopulateBF;

//DeadCode DAW 08Mar99 			if (af)
//DeadCode DAW 08Mar99 			{
//DeadCode DAW 08Mar99 				if (af->nationality==NAT_BLUE)
//DeadCode DAW 08Mar99 					bf = FindAirfieldForItem(targ)->BluePopulateBF;
//DeadCode DAW 08Mar99 				else
//DeadCode DAW 08Mar99 					bf = FindAirfieldForItem(targ)->RedPopulateBF;
//DeadCode DAW 08Mar99 			}
			break;
		}
		case S2U_ROUTE0:
		case S2U_ROUTE1:
		case S2U_ROUTE2:
			if (	convoysflagandaaalevelreturn 
				&& (Persons2::getbandfromUID(targ)==RedRoadBAND || Persons2::getbandfromUID(targ)==RedRailBand)
				)
			{
				SupplyRoute*	s2;
				for (s2=search->route[rel-S2U_ROUTE0];s2;s2=s2->alternateroute)
					if (s2->redsupplyUID==targ)
					{
						aaalevelreturn=s2->attackstats.aaalevel;
						if (s2->SetSupplySizeGR(GR_FormSize00,GR_FormSize01,GR_FormSize02))
							bf=s2->populateBF;
						else
							bf=FIL_NULL;
					}
			}
			else
			{
				bf=search->route[rel-S2U_ROUTE0]->populateBF;
				aaalevelreturn=search->route[rel-S2U_ROUTE0]->attackstats.aaalevel;
			}
		break;
		}
		if (convoysflagandaaalevelreturn)
			*convoysflagandaaalevelreturn=aaalevelreturn;
		if (bf)
			if (Persons2::BFLoaded(bf))
				return FIL_NULL;
	}
	return bf;

}


void	SupplyTree::CheckTargetLoaded(UniqueID targ)
{
	FileNum bf=TargetToBf(targ);
	if (bf)
	{
		if (Persons2::loadedBF[0]!=FIL_1_convoy)
			_Error.EmitSysErr("Failed to load subworld file %04x. Fell back to map code!",bf);
		Persons4	persons;	
		int slot=0;
		if 	(!persons.GetSpareBFNumber(slot))
			slot=persons.DeleteOldestBF();
		persons.LoadSubPiece(NULL,bf,slot,Persons4::LOAD);
	}

}


//////////////////////////////////////
//
// Back to packages
//

bool Profile::NonLeadElementSet(int applyflight, int applyelt)
{
	if (		(applyflight != ENABLE_COMPLEX_VAL)
			&&	(		(applyflight > 0)
					||	(		(applyelt != ENABLE_COMPLEX_VAL)
							&&	(applyelt > 0)
						 )
				 )
		)
		return true;
	else
		return false;
}
/*
void Profile::CalcWPTimes(int wavenum)
{
	//calculate start time, patrol time

//	int times[30];
//	int* addtime=times;
	UniqueID u=wave[wavenum].firstwp;
	info_airgrp* ag[3];
	ag[0]=*Persons2::ConvertPtrUID(wave[wavenum][0].uid);
	ag[1]=*Persons2::ConvertPtrUID(wave[wavenum][1].uid);
	ag[2]=*Persons2::ConvertPtrUID(wave[wavenum][2].uid);


	int targettime = 0;
	int	currmainwp=1;char currsubwp='A';

	int lastapplygroup = ENABLE_COMPLEX_VAL;
	int lastapplyflight = ENABLE_COMPLEX_VAL;
	int lastapplyelt = ENABLE_COMPLEX_VAL;

	COORDS3D* last;
	COORDS3D* lastwp[3];
	COORDS3D* home;
	info_waypoint* wp;
	int lasttime[3];
	lasttime[0] = lasttime[1] = lasttime[2] = 0;

	while (u)
	{
		wp=*Persons2::ConvertPtrUID(u);

		if (currmainwp ==1)
		{
			last=&Persons2::ConvertPtrUID(wave[wavenum][0].takeoffAF)->World;
			home=last;
		}else if (NonLeadElementSet(lastapplyflight, lastapplyelt))
		{
				 last = lastwp[wp->applygroup];
		}else if (			(wp->applygroup!=ENABLE_COMPLEX_VAL)
					&&		(lastapplygroup != wp->applygroup)
				 )
		{
				
			last = lastwp[wp->applygroup];
			if (!NonLeadElementSet(wp->applyflight, wp->applyelt))
				 lastwp[wp->applygroup] = &wp->World;
		}else if (			(wp->applygroup!=ENABLE_COMPLEX_VAL)
					&&		(lastapplygroup == wp->applygroup)
				 )
		{
			if (!NonLeadElementSet(wp->applyflight, wp->applyelt))
				 lastwp[wp->applygroup] = &wp->World;
		}else if (			(wp->applygroup == ENABLE_COMPLEX_VAL)
					&&		(lastapplygroup != ENABLE_COMPLEX_VAL)
				 )
		{
			last = lastwp[0];
		}
		
		if (wp->uid!=GOT_UNDEFINED_VAL)
		{
			currmainwp+=1;currsubwp='A';
		}
		else
		{
			currsubwp++;		//say which groups processed by this sub-waypoint
		}

		int dtime;
		int g;
		if 	(wp->applygroup==ENABLE_COMPLEX_VAL)
			g = 0;
		else
			g = wp->applygroup;

		dtime=Profile::CalcTime(last,&wp->World,ag[g]->type);			
		wp->etas = lasttime[g] + dtime;
		if (!NonLeadElementSet(wp->applyflight, wp->applyelt))
			lasttime[g] = wp->etas;

		if (currmainwp==4 && currsubwp=='A')
			targettime = wp->etas;				//backstop
//		if (	(currmainwp==4)
//			&&	(currsubwp!='A')
//			&&	(wp->target != GOT_UNDEFINED_VAL)
//			)
//			targettime = wp->etas;				//better

		if (currmainwp==4 && currsubwp=='A')
		{
			for (int j = 0; j < 3; j++)
			{
				lastwp[j] = &wp->World;
				lasttime[j] = wp->etas;
			}
		}
		last=&wp->World;
		lastapplygroup = wp->applygroup;
		lastapplyflight = wp->applyflight;
		lastapplyelt = wp->applyelt;
		u=wp->nextwp;
	}

	wave[wavenum][0].takeofftime = wave[wavenum].targettime - targettime;
	//temporary edits by JIM
	wave[wavenum][1].takeofftime = wave[wavenum].targettime - targettime; //JIM 19/01/99
	wave[wavenum][2].takeofftime = wave[wavenum].targettime - targettime; //JIM 19/01/99
	u=wave[wavenum].firstwp;
	while (u)
	{
		wp=*Persons2::ConvertPtrUID(u);
		int etas = wp->etas.Evaluate(); 
		etas =	etas + wave[wavenum][0].takeofftime;
		wp->etas = etas;
 		u=wp->nextwp;
	}

*/
void Profile::CalcWPTimes(int wavenum)
{
//given the wave's targettime, calcualte all wp ets ans takeofftime
	info_airgrp* ag[3];
	UniqueID u;
	info_waypoint* wp;
//DEADCODE RDH 15/04/99 	int lastgroupcalculated = 0;	

	int groups = 3;
	while (groups >= 0)
	{
		for (int g=0;g<groups;g++)
		{//do all groups first then go back  and do first group again to fill in wp->etas
			u=wave[wavenum].firstwp;
			ag[g]=*Persons2::ConvertPtrUID(wave[wavenum][g].uid);
			if (ag[g])
			{
//DEADCODE RDH 15/04/99 				lastgroupcalculated  = g;
				int targettime = 0;
				int	currmainwp=1;char currsubwp='A';

				COORDS3D* last;
				COORDS3D* home;
			
				int lasttime=0;
				int	regrouptime;
	//##temp fix														  //RDH 14/03/99
				if (wave[wavenum][g].takeoffAF)
					last=&Persons2::ConvertPtrUID(wave[wavenum][g].takeoffAF)->World;
				else
					last=&Persons2::ConvertPtrUID(wave[0][0].takeoffAF)->World;
				home=last;
											
				wp=*Persons2::ConvertPtrUID(u);
				while (u)
				{
					if (wp->uid != GOT_UNDEFINED_VAL)
					{
						currmainwp+=1;currsubwp='A';
					}else
						currsubwp++;		//say which groups processed by this sub-waypoint

					int dtime;
					int leadgroup;

					//leadgroup is used to determine cruise vel and bestclimb data
					//leadgroup is 0 for most of the time, but there are exceptions:
					//	to rendez-vous
					//	from dispersal
					//	whenever the group is specified
					if  (		(wp->applygroup != ENABLE_COMPLEX_VAL)
							||	(currmainwp==2 && currsubwp=='A')
						)
					{
						leadgroup = g;
					}
					else
						leadgroup = 0;
					
					SWord StoresDrag = 0;														//CSB 17/06/99	
					if  (		(currmainwp <= 4)
							&&	(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])							
						)
					{// on way in and we want to account for stores drag
							StoresDrag = wave[wavenum][leadgroup].GetStoresDrag(0);
					}
					dtime=Profile::CalcTime(last,&wp->World,ag[leadgroup]->type, ag[g]->type,StoresDrag);			//CSB 18/06/99	

					wp->etas = lasttime + dtime;
					
					if (currmainwp==5 && currsubwp=='A')
					{//regroup, ensure that all groups have the same regroup time
						if (g == 0)
							regrouptime = wp->etas;
						else
						{
							//we want to bring al groups together here
							//group one sets the time
							int abs_rvtime = regrouptime + wave[wavenum][0].takeofftime;
							int reltoToT = abs_rvtime - wave[wavenum].targettime;
							int etas = wp->etas.Evaluate(); 

	//DEADCODE RDH 15/04/99 						etas = etas - dtime;		//get back to target time
							etas = targettime;
							//the difficulty is that during this loop the etas is in
							//seconds from launch, different groups have different takeofftime
							etas += reltoToT;
							wp->etas = etas;
 			
						}
					}
					lasttime = wp->etas;

					if (currmainwp==4 && currsubwp=='A')
						targettime = wp->etas;				//backstop

					last=&wp->World;
					u=wp->nextwp;
					if (u)
					{
						//bypass all the waypoints we are not interested in for this group
						wp=*Persons2::ConvertPtrUID(u);
						while	(	(		(NonLeadElementSet(wp->applyflight, wp->applyelt))
										||	(		(wp->applygroup!= ENABLE_COMPLEX_VAL)
												&&	(wp->applygroup != g)
											)
									)
									&&	(u)
								)
						{
							u=wp->nextwp;
							if (u)
								wp=*Persons2::ConvertPtrUID(u);
							
						}
					}
				}
				wave[wavenum][g].takeofftime = wave[wavenum].targettime - targettime;
			}
		}
		groups = groups - 2;
	}
	u=wave[wavenum].firstwp;
	while (u)
	{
		wp=*Persons2::ConvertPtrUID(u);
		int etas = wp->etas.Evaluate(); 
		etas =	etas + wave[wavenum][0].takeofftime;
		wp->etas = etas;
 		u=wp->nextwp;
	}
}

/*
bool Profile::CalcFuel(int wavenum, int group, UniqueID wpuid, int& reqfuel)	
{
	int fuel = 0;
	reqfuel = 0;
	int bingo;
	UniqueID u=wave[wavenum].firstwp;
	info_airgrp* ag[3];
	ag[0]=*Persons2::ConvertPtrUID(wave[wavenum][0].uid);
	ag[1]=*Persons2::ConvertPtrUID(wave[wavenum][1].uid);
	ag[2]=*Persons2::ConvertPtrUID(wave[wavenum][2].uid);


	int targettime = 0;
	int	currmainwp=1;char currsubwp='A';

	int lastapplygroup = ENABLE_COMPLEX_VAL;
	int lastapplyflight = ENABLE_COMPLEX_VAL;
	int lastapplyelt = ENABLE_COMPLEX_VAL;


	COORDS3D* last;
	COORDS3D* lastwp[3];
	COORDS3D* home;
	info_waypoint* wp;
	
	int type;
	ClassPtr actype;
	int intfuel;

	fuel = wave[wavenum][group].GetExtFuel(0);
	type=Persons3::Squad2Type(ag[group]->type);
	actype = Plane_Type_Translate[type][0];
	intfuel = actype->maxintfuel*1000;   //0.01kg->g
	fuel += intfuel;


	while (u)
	{
		wp=*Persons2::ConvertPtrUID(u);

		if (currmainwp ==1)
		{
			last=&Persons2::ConvertPtrUID(wave[wavenum][0].takeoffAF)->World;
			home=last;
		}else if (NonLeadElementSet(lastapplyflight, lastapplyelt))
		{
				 last = lastwp[wp->applygroup];
		}else if (			(wp->applygroup!=ENABLE_COMPLEX_VAL)
					&&		(lastapplygroup != wp->applygroup)
				 )
		{
				 last = lastwp[wp->applygroup];
				 if (!NonLeadElementSet(wp->applyflight, wp->applyelt))
					lastwp[wp->applygroup] = &wp->World;
		}else if (			(wp->applygroup!=ENABLE_COMPLEX_VAL)
					&&		(lastapplygroup == wp->applygroup)
				 )
		{
				 if (!NonLeadElementSet(wp->applyflight, wp->applyelt))
					 lastwp[wp->applygroup] = &wp->World;
		}else if (			(wp->applygroup == ENABLE_COMPLEX_VAL)
					&&		(lastapplygroup != ENABLE_COMPLEX_VAL)
				 )
		{
			last = lastwp[group];
		}
		
		if (wp->uid!=GOT_UNDEFINED_VAL)
		{
			currmainwp+=1;currsubwp='A';
		}
		else
		{
			currsubwp++;		//say which groups processed by this sub-waypoint
		}

		int dtime;

		if  (	(		(wp->applygroup == group)
					&&	(!NonLeadElementSet(wp->applyflight, wp->applyelt))
				)
				||	(wp->applygroup==ENABLE_COMPLEX_VAL)
			)
			fuel -=Profile::CalcFuel(last,&wp->World,ag[0]->type,ag[group]->type);			

		if ( wpuid == u)
			reqfuel = fuel;

		if (currmainwp==4 && currsubwp=='A')
		{
			lastwp[0] = &wp->World;
			lastwp[1] = &wp->World;
			lastwp[2] = &wp->World;
		}
		last=&wp->World;
		lastapplygroup = wp->applygroup;
		lastapplyflight = wp->applyflight;
		lastapplyelt = wp->applyelt;
		u=wp->nextwp;
	}

	for (int k = 0; k < 3; k++)
	{
		if (wave[wavenum].group[k].squadron < SQ_B_NONFLYABLE)
		{
			bingo = MMC.squad[wave[wavenum].group[k].squadron].bingofuel;
			if (fuel < bingo)
				return false;
		}
	}
	return true;

}
*/
bool Profile::CalcFuel(int wavenum, int group, UniqueID wpuid, int& reqfuel)	
{
	int fuel = 0;
	reqfuel = 0;
	int bingo;
	UniqueID u=wave[wavenum].firstwp;

	info_airgrp* ag[3];
	ag[group]=*Persons2::ConvertPtrUID(wave[wavenum][group].uid);
	ag[0]=*Persons2::ConvertPtrUID(wave[wavenum][0].uid);
	
	int targettime = 0;
	int	currmainwp=1;char currsubwp='A';

	
	COORDS3D* last;
	COORDS3D* home;
	info_waypoint* wp;
	
	int type;
	ClassPtr actype;
	int intfuel;

	fuel = wave[wavenum][group].GetExtFuel(0);
	type=Persons3::Squad2Type(ag[group]->type);
	actype = Plane_Type_Translate[type][0];
	intfuel = actype->maxintfuel*1000;   //0.01kg->g
	fuel += intfuel;

	fuel = fuel - 10000000;//allowance for take-off and landing			   //15000000 //CSB 18/06/99
	//##temp fix														  //RDH 14/03/99
	if (wave[wavenum][group].takeoffAF)
		last=&Persons2::ConvertPtrUID(wave[wavenum][group].takeoffAF)->World;
	else
		last=&Persons2::ConvertPtrUID(wave[0][0].takeoffAF)->World;

	home=last;

	int regroupfuel;

	while (u)
	{
		wp=*Persons2::ConvertPtrUID(u);

		
		if (wp->uid!=GOT_UNDEFINED_VAL)
		{
			currmainwp+=1;currsubwp='A';
		}else
			currsubwp++;		//say which groups processed by this sub-waypoint
		
		int dtime;

		int leadgrp = 0;
		if (		
			)
			//not escorting
			leadgrp = group;
		//leadgroup is used to determine cruise vel and bestclimb data
		//leadgroup is 0 for most of the time, but there are exceptions:
		//	whenever the group is specified
		//	to rendez-vous
		//	in target area
		//	from dispersal (done out of loop)
		if  (		(wp->applygroup != ENABLE_COMPLEX_VAL)
				||	(currmainwp==2 && currsubwp=='A')
				||	(		(currmainwp == 4 )
						&&	(currsubwp != 'A')
					)

				)
			{
				leadgrp = group;
			}
			else
				leadgrp = 0;

		SWord StoresDrag = 0;														//CSB 17/06/99	
		if  (		(currmainwp <= 4)
				&&	(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])							
			)
		{// on way in and we want to account for stores drag
				StoresDrag = wave[wavenum][leadgrp].GetStoresDrag(0);
		}
		fuel -=Profile::CalcFuel(last,&wp->World,ag[leadgrp]->type,ag[group]->type,StoresDrag);			//CSB 18/06/99			

		if (		(currmainwp == 5 )
				&&	(currsubwp == 'A')
			)
			regroupfuel = fuel;



		if (wpuid == u)
			reqfuel = fuel;
		last=&wp->World;
		u=wp->nextwp;
		if (u)
		{
			wp=*Persons2::ConvertPtrUID(u);
			while	(	(		(NonLeadElementSet(wp->applyflight, wp->applyelt))
							||	(		(wp->applygroup!= ENABLE_COMPLEX_VAL)
									&&	(wp->applygroup != group)
								)
						)
						&&	(u)
					)
			{
				u=wp->nextwp;
				if (u)
					wp=*Persons2::ConvertPtrUID(u);
				
			}
		}
	}
	//come to field
	//no longer a possibility of escorting and no stores drag
	fuel -=Profile::CalcFuel(&wp->World,home,ag[group]->type,ag[group]->type,0);	//CSB 18/06/99		


	if (wave[wavenum].group[group].squadron < SQ_B_NONFLYABLE)
	{
		bingo = MMC.squad[wave[wavenum].group[group].squadron].bingofuel;
		if (		(regroupfuel < bingo)
				||	(fuel < 0)
			)	
			return false;
	}
	return true;
}

bool Profile::GetPackageFromWP(UniqueID req_wpuid,int& pack, int& wave, int& g)
{
	g = 0;
 	for (pack=0;pack<Profile::MAX_PACKS;pack++)
	{
		if (Todays_Packages.pack[pack][0][0].uid)
		{
			for (wave=0;wave<Profile::MAX_WAVES;wave++)
			{
				if (Todays_Packages[pack][wave][0].takeoffAF)
				{
					info_waypoint* wp;
					UniqueID u=Todays_Packages.pack[pack][wave].firstwp;
					while (u)
					{
						wp=*Persons2::ConvertPtrUID(u);
						if ( u == req_wpuid)
						{
							if (wp->applygroup != GOT_UNDEFINED_VAL)
								g = wp->applygroup;
							return (true);
						}
						
						
	   					u=wp->nextwp;
					}
				}
			}
		}
	}
	return (false);
}

void	Profile::Group::SetSquad(int squadnum)
{
	squadron.squadron=squadnum;
	if (uid && uid!=IllegalSepID)
	{
		info_airgrp* a=*Persons2::ConvertPtrUID(uid);
			a->type=squadnum;
	}
	if (squadnum<SQ_B_NONFLYABLE)
		takeoffAF=
			SupplyTree::airfieldinfo[MMC.squad[squadnum].airfieldindex].airfield;
	else
		takeoffAF=
			UID_Japan;
}

void	Profile::Group::SetFlights(int flights)
{
	numflights.numflights=flights;
	if (uid && uid!=IllegalSepID)
	{
		info_airgrp* a=*Persons2::ConvertPtrUID(uid);
		a->inform=flights*4;
	}
	

}
int Profile::WPType(UniqueID u)
{
		int text = IDS_INSERTEDWAYPOINT;
		info_waypoint *wp;
		wp = *Persons2::ConvertPtrUID(u);
		if (wp)
		{
			if (wp->uid == GOT_UNDEFINED_VAL)
			{
				if (wp->applygroup != GOT_UNDEFINED_VAL)
				{
					if (wp->applygroup == 0)
					{
						int action=wp->wpact.Evaluate();
						if (action==ENABLE_COMPLEX_VAL)
							action=wpacnoactionno;
						text = 	IDS_L_WPACTION_NONE + action;
					}else
						text = (int)wp->applygroup + IDS_ATTACK;
				}

			}else
			{
				int uid = -(int)wp->uid;
				switch (uid)
				{
				case SGR_WPP_Rendevous:
				case SGR_WPP_Ingress:
				case SGR_WPP_Target:
				case SGR_WPP_Regroup:
				case SGR_WPP_Egress:
				case SGR_WPP_Disperse:
					{
						text = uid - SGR_WPP_Rendevous + IDS_MAIN_WP_RENDEVOUS;

						break;
					}
				case SGR_WPC_Rendevous:
				case SGR_WPC_Ingress:
				case SGR_WPC_Target:
				case SGR_WPC_Regroup:
				case SGR_WPC_Egress:
				case SGR_WPC_Disperse:
					{
						text = uid - SGR_WPC_Rendevous + IDS_MAIN_WP_RENDEVOUS;

						break;
					}


				}
			}
		}
		return(text);
}


////////////////////////////////////////////////////////////////////////
//
// Function:    GetRouteSplitting
// Date:        15/12/98
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
Profile::WaveSplitting	Profile::Wave::GetRouteSplitting(int groupnum,int acnum)
{	//return how the route is made up at present
 	UniqueID wt,waf,wal,wpf,wpl,wr;
	GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
	UniqueID  trgu=FindWpBetween(waf,wal,groupnum,acnum/4,0);
	assert(trgu);
	info_waypoint*	trgwp=*Persons2::ConvertPtrUID(trgu);
	if (trgwp->applyflight.Evaluate()!=ENABLE_COMPLEX_VAL)
		if (trgwp->applyelt.Evaluate()!=ENABLE_COMPLEX_VAL)
			return WS_SEP_ELT;
		else
			return WS_SEP_WING;
	else
	{
		//ok.. route not split. Does it use primary target or own subtarget?
		//if it is a patrol then always say primary
		if (trgwp->target.complex && trgwp->target->type==Expr::EXPR_GLOB)
			if (	trgwp->target.UsesGlobRef()>=SGR_Pack_Targ_F0_E0
				&&	trgwp->target.UsesGlobRef()<=SGR_Pack_Targ_Fmax_E1
				)
				return	WS_SINGLE_OWN;
		UniqueID  patu=FindWpBetween(wpf,wpl,groupnum,0,0);
		if (patu && patu!=trgu)
		{
			trgwp=*Persons2::ConvertPtrUID(patu);
			if (trgwp->target.complex && trgwp->target->type==Expr::EXPR_GLOB)
				if (	trgwp->target.UsesGlobRef()>=SGR_Pack_Targ_F0_E0
					&&	trgwp->target.UsesGlobRef()<=SGR_Pack_Targ_Fmax_E1
					)
					return	WS_SINGLE_OWN;
		}
		return	WS_SINGLE_PRIMARY;
	}
}

////////////////////////////////////////////////////////////////////////
//
// Function:    Independent
// Date:        15/12/98
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
bool	Profile::TargetDescript::Independent()
{
	return (ID || SGbandindex);
}

////////////////////////////////////////////////////////////////////////
//
// Function:    GetTargSplitting
// Date:        15/12/98
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
Profile::WaveSplitting	Profile::Group::GetTargSplitting(int acnum,bool allowelt)
{	//return how the targets need the route set up now
	//If this ac's secondary is set flag elt mode
	if (allowelt && flight[acnum/4].secondary.Independent())
		return WS_SEP_ELT;
	for (int f=1;f<numflights;f++)
		if (	flight[f].primary.Independent()
			||	flight[f].secondary.Independent()
			)
			return	WS_SEP_WING;
	if (	flight[0].primary.Independent()
		||	flight[0].secondary.Independent()
		)
		return	WS_SINGLE_OWN;
	else
		return	WS_SINGLE_PRIMARY;
}
////////////////////////////////////////////////////////////////////////
//
// Function:    FindSpareGlobref
// Date:        15/12/98
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
int	Profile::FindSpareGlobref()
{
	int	usedglobrefs=0;
	for (int w=0;w<Profile::MAX_WAVES;w++)
		for (int g=0;g<Profile::MAX_GROUPS;g++)
			for (int f=0;f<Profile::MAX_FLIGHTS;f++)
				if (wave[w][g][f].globrefind)
					usedglobrefs|=1<<((wave[w][g][f].globrefind-SGR_Pack_Targ_F0_E0)/2);
	for (int i=1,j=0;i;i+=i,j++)
		if (!(usedglobrefs&i))
			return j+SGR_Pack_Targ_F0_E0;
	INT3;
	return 0;
}

////////////////////////////////////////////////////////////////////////
//
// Function:    ModifyPatrolRoute
// Date:        15/12/98
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
void	Profile::ModifyPatrolRoute(int wavenum,int groupnum,int acnum)
{	//OK... patrol routes are easy!
	//If all routes are undefined or same as leader then only have 1 route
	//If any are different have multiple routes
	//If Elt mode patrol and secondary then have elt seperated route...

	//All inserted sections use same waypoint targets as leader

	bool	canhaveseperateelt=false;	//proper test based on duty required...

	WaveSplitting oldsplit=wave[wavenum].GetRouteSplitting(groupnum,acnum);
	WaveSplitting newsplit=wave[wavenum][groupnum].GetTargSplitting(acnum,canhaveseperateelt);
	//Can be one of:
	//WS_SINGLE_PRIMARY
	//WS_SEP_ELT
	//WS_SEP_WING
	if (oldsplit!=newsplit)
	{
		if (newsplit==WS_SINGLE_PRIMARY)
		{	//must delete existing splits
 				//kill all old sub flight stuff & extend lead flight to cover group 
			UniqueID wt,waf,wal,wpf,wpl,wr;
			wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
			UniqueID t;
			for (int fl=1;fl<4;fl++)
				for(int elt=0;elt<2;elt++)
					if ((t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,elt))!=UID_NULL)
						wave[wavenum].RemoveWpBetween(waf,wal,t);
			wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
			for (fl=1;fl<4;fl++)
				for(int elt=0;elt<2;elt++)
					if ((t=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,fl,elt))!=UID_NULL)
						wave[wavenum].RemoveWpBetween(wpf,wpl,t);
			for (fl=1;fl<4;fl++)
				wave[wavenum][groupnum][fl].globrefind=0;
			t=wave[wavenum].FindWpBetween(waf,wal,groupnum,0,0);
			assert(t);
			info_waypoint* wp=*Persons2::ConvertPtrUID(t);
			wp->applyflight=ENABLE_COMPLEX_VAL;
			wp->applyelt=ENABLE_COMPLEX_VAL;
			t=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,0,0);
			if (t)
			{
				info_waypoint* wp=*Persons2::ConvertPtrUID(t);
				wp->applyflight=ENABLE_COMPLEX_VAL;
				wp->applyelt=ENABLE_COMPLEX_VAL;
			}
		}
		else
		{
			if (oldsplit<WS_SEPERATE)
			{	//allocate 1 targ block per flight & create alias waypoints as required
		
				wave[wavenum][groupnum][0].globrefind=0;	//patrols without targets get confused here...
			 	UniqueID wt,waf,wal,wpf,wpl,wr;
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID t=wave[wavenum].FindWpBetween(waf,wal,groupnum,0,0);
				assert(t);
				UniqueID p=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,0,0);
				info_waypoint* wpt=*Persons2::ConvertPtrUID(t);
				info_waypoint* wpp=NULL;
				if (p)	
					wpp=*Persons2::ConvertPtrUID(p);
				int p_gri=0,t_gri=wpt->target.UsesGlobRef();
				BFieldWaypointActions	p_act,t_act=(BFieldWaypointActions)wpt->wpact.Evaluate();
				Coords3D p_delta,t_delta;
				wpt->position.EvalW(t_delta);
				if (p)
				{
					p_gri=wpp->target.UsesGlobRef();
					p_act=(BFieldWaypointActions)wpp->wpact.Evaluate();
					wpp->position.EvalW(p_delta);
				}
				wpt->applyflight=0;
				if (p)
					wpp->applyflight=0;
				for (int i=1;i<Profile::MAX_FLIGHTS;i++)
				{
					if (	!wave[wavenum][groupnum][i].primary.Independent())
						wave[wavenum][groupnum][i].primary=wave[wavenum][groupnum][0].primary;
					if (	!wave[wavenum][groupnum][i].secondary.Independent())
						wave[wavenum][groupnum][i].primary=wave[wavenum][groupnum][0].secondary;
 					UniqueID ft=wave[wavenum].InsertWpBetween(waf,wal,(SavedGlobrefs)t_gri,t_act,groupnum,i);
					info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
					wpft->position.RecalcDeltasToMatch(t_delta);
					if (p)
					{
 						UniqueID ft=wave[wavenum].InsertWpBetween(wpf,wpl,(SavedGlobrefs)p_gri,p_act,groupnum,i);
						info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
						wpft->position.RecalcDeltasToMatch(p_delta);
					}
				}
			}
 			if (newsplit==WS_SEP_ELT)
			{	//create extra copy for current flights's second element

 				int fl=acnum/4;
			 	UniqueID wt,waf,wal,wpf,wpl,wr;
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,0);
				assert(t);
				UniqueID p=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,fl,0);
				info_waypoint* wpt=*Persons2::ConvertPtrUID(t);
				info_waypoint* wpp=NULL;
				if (p)	
					wpp=*Persons2::ConvertPtrUID(p);
				if (!wave[wavenum][groupnum][fl].globrefind)
					wave[wavenum][groupnum][fl].globrefind=FindSpareGlobref();
				int gri=wpt->target.UsesGlobRef();
//never				if (	gri==wave[wavenum][groupnum][fl].globrefind
//will					||	gri==SGR_Pack_Target	)
//be					gri=wave[wavenum][groupnum][fl].globrefind+1;
				int p_gri=0,t_gri=wpt->target.UsesGlobRef();
				BFieldWaypointActions	p_act,t_act=(BFieldWaypointActions)wpt->wpact.Evaluate();
				Coords3D p_delta,t_delta;
				wpt->position.EvalW(t_delta);

				UniqueID ft=wave[wavenum].InsertWpBetween(waf,wal,(SavedGlobrefs)gri,t_act,groupnum,fl,1);
				info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
				wpft->position.RecalcDeltasToMatch(t_delta);
				wpt->applyelt=0;
				if (p)
				{
					p_gri=wpp->target.UsesGlobRef();
					p_act=(BFieldWaypointActions)wpp->wpact.Evaluate();
					wpp->position.EvalW(p_delta);
					int gri=wpp->target.UsesGlobRef();
//never					if (	gri==wave[wavenum][groupnum][fl].globrefind
//will						||	gri==SGR_Pack_Target	)
//be						gri=wave[wavenum][groupnum][fl].globrefind+1;

					UniqueID ft=wave[wavenum].InsertWpBetween(wpf,wpl,(SavedGlobrefs)gri,p_act,groupnum,fl,1);
					info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
					wpft->position.RecalcDeltasToMatch(p_delta);
					wpp->applyelt=0;
				}

			}
			else
			if (oldsplit==WS_SEP_ELT)
			{	//delete old second element copy & extend first element to cover both
				//identical to main modifyroute version
				int fl=acnum/4;
			 	UniqueID wt,waf,wal,wpf,wpl,wr;
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID t=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,fl,1);
				if (t)
				{
					wave[wavenum].RemoveWpBetween(waf,wal,t);
					t=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,fl,0);
					assert(t);
					info_waypoint* wp=*Persons2::ConvertPtrUID(t);
					wp->applyelt=ENABLE_COMPLEX_VAL;
				}
				t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,1);
				assert(t);
				wave[wavenum].RemoveWpBetween(waf,wal,t);
				t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,0);
				assert(t);
				info_waypoint* wp=*Persons2::ConvertPtrUID(t);
				wp->applyelt=ENABLE_COMPLEX_VAL;

			}

		}
	}
}

////////////////////////////////////////////////////////////////////////
//
// Function:    SetPositionDescription
// Date:        15/12/98
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
void	Profile::Wave::SetPositionDescription(int grp,UniqueID wpid)
{	//Ok... I need to get the flight and element info from the WP
	bool	canhaveseperateelt=false;	//proper test based on duty required...
	info_waypoint* wp=*Persons2::ConvertPtrUID(wpid);
	int fl=wp->applyflight.Evaluate();
	if (fl==ENABLE_COMPLEX_VAL)
		fl=0;
	TargetDescript* targdesc=NULL;
	if (canhaveseperateelt)
		if (wp->wpact.Evaluate()==wpstartloopno)
			if (wp->applyelt!=1)
				targdesc=&group[grp][fl].primary;
			else
				targdesc=&group[grp][fl].secondary;
		else
			targdesc=NULL;
	else
		if (wp->wpact.Evaluate()==wpstartloopno)
			targdesc=&group[grp][fl].primary;
		else
		if (wp->wpact.Evaluate()==wpstoploopchkno)
			targdesc=&group[grp][fl].secondary;
		else
			targdesc=NULL;
	if (targdesc)
	{
		Coords3D delta;
		wp->position.EvalW(delta);
		int direction=(Math_Lib.arctan(delta.X,delta.Y)+ANGLES_22Deg)/ANGLES_45Deg; //0..7,8=0
		int range=Math_Lib.Distance2d(delta.X/1000,delta.Y/1000);
		if (range>32000)
			range=32000;
		targdesc->ID=UID_NULL;
		targdesc->SGT=UID_NULL;
		targdesc->groupindex=direction;
		targdesc->SGbandindex=range;
	}
}

////////////////////////////////////////////////////////////////////////
//
// Function:    ModifyRoute
// Date:        15/12/98
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
void	Profile::ModifyRoute(int wavenum,int groupnum,int acnum)
{
//useful: UniqueID	Profile::Wave::FindWpBetween(UniqueID wp1,UniqueID wp2,int group,int flight,int elt)
//useful: bool	Profile::Wave::GetKeyTargetWPs(UniqueID& targetarea,UniqueID& firststartpatrolbomb,UniqueID& laststartpatrolbomb,UniqueID& firstendpatrol,UniqueID& lastendpatrol,UniqueID& regrouparea)
	
	//I want to make mods to the route at wave level for the selected element.
	//However, I need to embed globref info at the package level.

	//I assume all other groups are already clean, but I need to assign target globref slots
	//I assume other lead/wing are sorted for all flights except current as well.

	//Version 2:
	//I am no longer going to try and handle basic patrols with this system.
	//It is just too different.
	//Instead, this routine is only going to handle lead groups, and I will always allocate 
	//either 0, 1 or 4 flights.
	//
	//The routine ModifyPatrolRoute sorts out the other patrols.
	//

	//If any member of the group except the first flight leader has a separate target then 
	//the whole route gets expanded into flight specific sections.
	//If the role allows the wingman to be separate, then any flight that has a secondary target field 
	//filled then that flight will get separated into elements.
	//If it is all simple, then	I will delete any existing complex route.
	//Special cases:
	//armed recon uses secondary target to denote end of road

	//All patrols over the target area go through here.
	//
	//
	if (wavenum || duty>=DC_TARGPATROLS)
	{
		ModifyPatrolRoute(wavenum,groupnum,acnum);
		return;
	}
	bool	canhaveseperateelt=false;	//proper test based on duty required...
	
	if (duty==DC_BOMB && groupnum==0)
	{
		info_airgrp* a=*Persons2::ConvertPtrUID(wave[wavenum][0].uid);
		if (a->duty.Evaluate()==DC_BOMB)
			canhaveseperateelt=true;
	}

	WaveSplitting oldsplit=wave[wavenum].GetRouteSplitting(groupnum,acnum);
	WaveSplitting newsplit=wave[wavenum][groupnum].GetTargSplitting(acnum,canhaveseperateelt);
	if (oldsplit!=newsplit)
		if (newsplit==WS_SINGLE_PRIMARY||newsplit==WS_SINGLE_OWN)
		{	
			if (oldsplit>WS_SEPERATE)
			{
				//kill all old sub flight stuff & extend lead flight to cover group 
			 	UniqueID wt,waf,wal,wpf,wpl,wr;
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID t,p;
				for (int fl=1;fl<4;fl++)
					for(int elt=0;elt<2;elt++)
						if ((t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,elt))!=UID_NULL)
							wave[wavenum].RemoveWpBetween(waf,wal,t);
				if ((t=wave[wavenum].FindWpBetween(waf,wal,groupnum,0,1))!=UID_NULL)
					wave[wavenum].RemoveWpBetween(waf,wal,t);
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				for (fl=1;fl<4;fl++)
					for(int elt=0;elt<2;elt++)
						if ((p=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,fl,elt))!=UID_NULL && p!=t)
							wave[wavenum].RemoveWpBetween(wpf,wpl,p);
				if ((t=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,0,1))!=UID_NULL)
					wave[wavenum].RemoveWpBetween(wpf,wpl,t);
				for (fl=1;fl<4;fl++)
					wave[wavenum][groupnum][fl].globrefind=0;
				t=wave[wavenum].FindWpBetween(waf,wal,groupnum,0,0);
				assert(t);
				info_waypoint* wp=*Persons2::ConvertPtrUID(t);
				wp->applyflight=ENABLE_COMPLEX_VAL;
				wp->applyelt=ENABLE_COMPLEX_VAL;
				p=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,0,0);
				if (p==t)
					p=UID_NULL;
				if (p)
				{
					info_waypoint* wp=*Persons2::ConvertPtrUID(p);
					wp->applyflight=ENABLE_COMPLEX_VAL;
					wp->applyelt=ENABLE_COMPLEX_VAL;
				}
			}
			if (newsplit==WS_SINGLE_PRIMARY)
			{	//make WP reference the main target
			 	UniqueID wt,waf,wal,wpf,wpl,wr;
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID t=wave[wavenum].FindWpBetween(waf,wal,groupnum,0,0);
				assert(t);
				info_waypoint* wp=*Persons2::ConvertPtrUID(t);
				if (wp->target.complex && wp->target->type==Expr::EXPR_GLOB)
					if (	wp->target.UsesGlobRef()>=SGR_Pack_Targ_F0_E0
						&&	wp->target.UsesGlobRef()<=SGR_Pack_Targ_Fmax_E1
						)
						wp->target.UsesGlobRef()=SGR_Pack_Target;
				t=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,0,0);
				if(t)
				{
					info_waypoint* wp=*Persons2::ConvertPtrUID(t);
					if (wp->target.complex && wp->target->type==Expr::EXPR_GLOB)
						if (	wp->target.UsesGlobRef()>=SGR_Pack_Targ_F0_E0
							&&	wp->target.UsesGlobRef()<=SGR_Pack_Targ_Fmax_E1
							)
							wp->target.UsesGlobRef()=SGR_Pack_Target;
				}
			}
			else
			{	//allocate 1 targ block & set main to point to it.
			 	UniqueID wt,waf,wal,wpf,wpl,wr;
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID t=wave[wavenum].FindWpBetween(waf,wal,groupnum,0,0);
				assert(t);
				info_waypoint* wp=*Persons2::ConvertPtrUID(t);
				wave[wavenum][groupnum][0].globrefind=0;	//patrols without targets get confused here...
				int assglobref=FindSpareGlobref();
				wave[wavenum][groupnum][0].globrefind=assglobref;
				if (wave[wavenum][groupnum][0].primary.Independent())
					if (wp->target.complex && wp->target->type==Expr::EXPR_GLOB)
						if (wp->target.UsesGlobRef()==SGR_Pack_Target)
							wp->target.UsesGlobRef()=assglobref;
				UniqueID p=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,0,0);
				if (p==t)
					p=UID_NULL;
				if (p)
					if (!canhaveseperateelt)
						if (wave[wavenum][groupnum][0].secondary.Independent())
						{
							info_waypoint* wp=*Persons2::ConvertPtrUID(p);
							if (wp->target.complex && wp->target->type==Expr::EXPR_GLOB)
								if (wp->target.UsesGlobRef()==SGR_Pack_Target)
									wp->target.UsesGlobRef()=assglobref+1;
						}
						else
						{}
					else
						if (wave[wavenum][groupnum][0].primary.Independent())
						{
							info_waypoint* wp=*Persons2::ConvertPtrUID(p);
							if (wp->target.complex && wp->target->type==Expr::EXPR_GLOB)
								if (wp->target.UsesGlobRef()==SGR_Pack_Target)
									wp->target.UsesGlobRef()=assglobref;
						}
			}
		}
		else
		{
			if (oldsplit<WS_SEPERATE)
			{	//allocate 1 targ block per flight & create alias waypoints as required
				//hello Mr Wooly Words... 
			 	UniqueID wt,waf,wal,wpf,wpl,wr;
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID t=wave[wavenum].FindWpBetween(waf,wal,groupnum,0,0);
				assert(t);
				UniqueID p=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,0,0);
				if (p==t)
					p=UID_NULL;
				info_waypoint* wpt=*Persons2::ConvertPtrUID(t);
				info_waypoint* wpp=NULL;
				if (p)	
					wpp=*Persons2::ConvertPtrUID(p);
				int p_gri=0,t_gri=wpt->target.UsesGlobRef();
				BFieldWaypointActions	p_act,t_act=(BFieldWaypointActions)wpt->wpact.Evaluate();
				Coords3D p_delta,t_delta;
				wpt->position.EvalW(t_delta);
				if (p)
				{
					p_gri=wpp->target.UsesGlobRef();
					p_act=(BFieldWaypointActions)wpp->wpact.Evaluate();
					wpp->position.EvalW(p_delta);
				}

				enum	GriMode	{GRI_MAIN,GRI_PRI,GRI_SEC,GRI_OTHER};
				GriMode	t_grimode,p_grimode;
				if (t_gri==SGR_Pack_Target)
					t_grimode=GRI_MAIN;
				else 
				if (t_gri==wave[wavenum][groupnum][0].globrefind)
					t_grimode=GRI_PRI;
				else 
				if (t_gri==wave[wavenum][groupnum][0].globrefind+1)
					t_grimode=GRI_SEC;
				else
					t_grimode=GRI_OTHER;

				if (p_gri==SGR_Pack_Target)
					p_grimode=GRI_MAIN;
				else 
				if (p_gri==wave[wavenum][groupnum][0].globrefind)
					p_grimode=GRI_PRI;
				else 
				if (p_gri==wave[wavenum][groupnum][0].globrefind+1)
					p_grimode=GRI_SEC;
				else
					p_grimode=GRI_OTHER;

				if (wave[wavenum][groupnum][0].globrefind)
				{
					wpt->applyflight=0;
					if (p)
						wpp->applyflight=0;
					wave[wavenum][groupnum][1].globrefind=FindSpareGlobref();
					wave[wavenum][groupnum][2].globrefind=FindSpareGlobref();
					wave[wavenum][groupnum][3].globrefind=FindSpareGlobref();
					for (int i=1;i<Profile::MAX_FLIGHTS;i++)
					{
						if (	!wave[wavenum][groupnum][i].primary.Independent())
							wave[wavenum][groupnum][i].primary=wave[wavenum][groupnum][0].primary;
						if (	!wave[wavenum][groupnum][i].secondary.Independent() && canhaveseperateelt)
							wave[wavenum][groupnum][i].secondary=wave[wavenum][groupnum][0].secondary;

						int gri;
						switch (t_grimode)
						{
						case GRI_MAIN:	gri=wave[wavenum][groupnum][i].globrefind;	break;
						case GRI_PRI:	gri=wave[wavenum][groupnum][i].globrefind;	break;
						case GRI_SEC:	gri=wave[wavenum][groupnum][i].globrefind+1;break;
						case GRI_OTHER:	gri=t_gri;									break;
						}
						UniqueID ft=wave[wavenum].InsertWpBetween(waf,wal,(SavedGlobrefs)gri,t_act,groupnum,i);
						info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
						wpft->position.RecalcDeltasToMatch(t_delta);
						if (p)
						{
							switch (p_grimode)
							{
							case GRI_MAIN:	gri=wave[wavenum][groupnum][i].globrefind;	break;
							case GRI_PRI:	gri=wave[wavenum][groupnum][i].globrefind;	break;
							case GRI_SEC:	gri=wave[wavenum][groupnum][i].globrefind+1;break;
							case GRI_OTHER:	gri=p_gri;									break;
							}
							UniqueID ft=wave[wavenum].InsertWpBetween(wpf,wpl,(SavedGlobrefs)gri,p_act,groupnum,i);
							info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
							wpft->position.RecalcDeltasToMatch(p_delta);
						}
					}
				}
				else
				{
					wave[wavenum][groupnum][0].globrefind=FindSpareGlobref();
					wave[wavenum][groupnum][1].globrefind=FindSpareGlobref();
					wave[wavenum][groupnum][2].globrefind=FindSpareGlobref();
					wave[wavenum][groupnum][3].globrefind=FindSpareGlobref();
					for (int i=0;i<Profile::MAX_FLIGHTS;i++)
					{
						int gri=t_gri;
						if (wave[wavenum][groupnum][i].primary.Independent())
							gri=wave[wavenum][groupnum][0].globrefind;
						UniqueID ft=wave[wavenum].InsertWpBetween(waf,wal,(SavedGlobrefs)gri,t_act,groupnum,i);
						info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
						wpft->position.RecalcDeltasToMatch(t_delta);
						if (p)
						{
							int gri;
							if (canhaveseperateelt)
								if (wave[wavenum][groupnum][i].primary.Independent())
									gri=wave[wavenum][groupnum][0].globrefind;
								else
									gri=p_gri;
							else
								if (wave[wavenum][groupnum][i].secondary.Independent())
									gri=wave[wavenum][groupnum][0].globrefind;
								else
									gri=p_gri;
							UniqueID ft=wave[wavenum].InsertWpBetween(wpf,wpl,(SavedGlobrefs)gri,t_act,groupnum,i);
							info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
							wpft->position.RecalcDeltasToMatch(p_delta);
						}
					}
					if (p)
						wave[wavenum].RemoveWpBetween(wpf,wpl,p);
					wave[wavenum].RemoveWpBetween(waf,wal,t);
				}
			}
			if (newsplit==WS_SEP_ELT)
			{	//create extra copy for current flights's second element
				int fl=acnum/4;
			 	UniqueID wt,waf,wal,wpf,wpl,wr;
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,0);
				assert(t);
				UniqueID p=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,fl,0);
				if (p==t)
					p=UID_NULL;
				info_waypoint* wpt=*Persons2::ConvertPtrUID(t);
				info_waypoint* wpp=NULL;
				if (p)	
					wpp=*Persons2::ConvertPtrUID(p);
				if (!wave[wavenum][groupnum][fl].globrefind)
					wave[wavenum][groupnum][fl].globrefind=FindSpareGlobref();
				int gri=wpt->target.UsesGlobRef();
				if (	gri==wave[wavenum][groupnum][fl].globrefind
					||	gri==SGR_Pack_Target	)
					gri=wave[wavenum][groupnum][fl].globrefind+1;
				int p_gri=0,t_gri=wpt->target.UsesGlobRef();
				BFieldWaypointActions	p_act,t_act=(BFieldWaypointActions)wpt->wpact.Evaluate();
				Coords3D p_delta,t_delta;
				wpt->position.EvalW(t_delta);

				UniqueID ft=wave[wavenum].InsertWpBetween(waf,wal,(SavedGlobrefs)gri,t_act,groupnum,fl,1);
				info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
				wpft->position.RecalcDeltasToMatch(t_delta);
				wpt->applyelt=0;
				if (p)
				{
					p_gri=wpp->target.UsesGlobRef();
					p_act=(BFieldWaypointActions)wpp->wpact.Evaluate();
					wpp->position.EvalW(p_delta);
					int gri=wpp->target.UsesGlobRef();
					if (	gri==wave[wavenum][groupnum][fl].globrefind
						||	gri==SGR_Pack_Target	)
						gri=wave[wavenum][groupnum][fl].globrefind+1;

					UniqueID ft=wave[wavenum].InsertWpBetween(wpf,wpl,(SavedGlobrefs)gri,p_act,groupnum,fl,1);
					info_waypoint* wpft=*Persons2::ConvertPtrUID(ft);
					wpft->position.RecalcDeltasToMatch(p_delta);
					wpp->applyelt=0;
				}
			}
			else
			if (oldsplit==WS_SEP_ELT)
			{	//delete old second element copy & extend first element to cover both
				int fl=acnum/4;
			 	UniqueID wt,waf,wal,wpf,wpl,wr;
				wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
				UniqueID t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,1);
				if (t)
				{
					wave[wavenum].RemoveWpBetween(waf,wal,t);
					UniqueID p=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,fl,0);
					if (p==t)
						p=UID_NULL;
					assert(p);
					info_waypoint* wp=*Persons2::ConvertPtrUID(p);
					wp->applyelt=ENABLE_COMPLEX_VAL;
				}
				t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,1);
				assert(t);
				wave[wavenum].RemoveWpBetween(waf,wal,t);
				UniqueID p=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,0);
				if (p==t)
					p=UID_NULL;
				assert(p);
				info_waypoint* wp=*Persons2::ConvertPtrUID(p);
				wp->applyelt=ENABLE_COMPLEX_VAL;
			}
		}
	else
	if (newsplit==WS_SEP_WING)
	{	//same settings for whole group, but this element may have switched
		int fl=acnum/4;
		int maxelt=1;
		UniqueID wt,waf,wal,wpf,wpl,wr;
		wave[wavenum].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
		{	//if split do both elements...
			UniqueID t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,0);
			info_waypoint* wp=*Persons2::ConvertPtrUID(t);
			if (wp->applyelt.Evaluate()!=ENABLE_COMPLEX_VAL)
				maxelt=2;
		}
		for (int elt=0;elt<maxelt;elt++)
		{
			UniqueID t=wave[wavenum].FindWpBetween(waf,wal,groupnum,fl,elt);
			assert(t);
			info_waypoint* wp=*Persons2::ConvertPtrUID(t);
			if (	wp->target.UsesGlobRef()==SGR_Pack_Target
				&&	wave[wavenum][groupnum][fl].primary.Independent()	)
				wp->target.UsesGlobRef()=wave[wavenum][groupnum][fl].globrefind+elt;
			else
			if (	wp->target.UsesGlobRef()!=SGR_Pack_Target
				&&	!wave[wavenum][groupnum][fl].primary.Independent()	)
				wp->target.UsesGlobRef()=SGR_Pack_Target;

			UniqueID p=wave[wavenum].FindWpBetween(wpf,wpl,groupnum,fl,elt);
			if (p==t)
				p=UID_NULL;
			if (p)
			{
				info_waypoint* wp=*Persons2::ConvertPtrUID(p);
				if (canhaveseperateelt)
					if (	wp->target.UsesGlobRef()==SGR_Pack_Target
						&&	wave[wavenum][groupnum][fl].primary.Independent()	)
						wp->target.UsesGlobRef()=wave[wavenum][groupnum][fl].globrefind+elt;
					else
					if (	wp->target.UsesGlobRef()!=SGR_Pack_Target
						&&	!wave[wavenum][groupnum][fl].primary.Independent()	)
						wp->target.UsesGlobRef()=SGR_Pack_Target;
					else{}
				else
					if (	wp->target.UsesGlobRef()==SGR_Pack_Target
						&&	wave[wavenum][groupnum][fl].primary.Independent()	)
						wp->target.UsesGlobRef()=wave[wavenum][groupnum][fl].globrefind+1;
					else
					if (	wp->target.UsesGlobRef()!=SGR_Pack_Target
						&&	!wave[wavenum][groupnum][fl].primary.Independent()	)
						wp->target.UsesGlobRef()=SGR_Pack_Target;
					else{}
			}
		}

	}
}

SupplyLine*	SupplyTree::GetLineFromCallName(int callname)
{
	if (callname==WestRoute.FACcallname)	return &WestRoute;
	if (callname==WestRoute.TACcallname)	return &WestRoute;
	if (callname==CentralRoute.FACcallname)	return &CentralRoute;
	if (callname==CentralRoute.TACcallname)	return &CentralRoute;
	if (callname==EastRoute.FACcallname)	return &EastRoute;
	if (callname==EastRoute.TACcallname)	return &EastRoute;
	return NULL;
}


int	Profile::CountWaypoints()
{
	int wpcount=0;
	for (int wavenum=0;wavenum<MAX_WAVES;wavenum++)
		wpcount+=CountWaypoints(wavenum);
	wpsused=wpcount;
	return	wpsused;
}

int	Profile::CountWaypoints(int wavenum)
{
	if (!wave[wavenum].firstwp)
		return 0;
	int	rv=1;
	for (info_waypoint* wp=*Persons2::ConvertPtrUID(wave[wavenum].firstwp);
			wp->nextwp;wp=*Persons2::ConvertPtrUID(wp->nextwp))
		rv++;
	return rv;
}

int	 PackageList::UsedWaypoints()
{
	int	rv=0;
	for (int packnum=0;packnum<Profile::MAX_PACKS;packnum++)
		rv+=pack[packnum].wpsused;
	return rv;
} 

bool	PackageList::CanAddMoreWaypoints(int	packnum)
{
	if (pack[packnum].wpsused>180)
		return false;
	else
	if (UsedWaypoints()>350)
		return false;
	else
		return true;
}
