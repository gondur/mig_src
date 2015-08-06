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

//
// Battlefield code to do with mig alley map screen
// Sort of global stuff I can't hide anywhere else.
//
//
//
#include	"dosdefs.h"	
#define		F_COMMON  
#include	"text.h"
#include	"uniqueID.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"world.h"
#include	"NODE.H"
#include	"fileman.h"
#include	"missman2.h"
#include	"mytime.h"
#include	"sky.h"
#include	"bstream.h"
#include	"CString.h"


///////////////////////////////////////////////
ItemBasePtr	WorldStuff::pItem[WorldStuff::PITEMTABLESIZE];
ItemBasePtr WorldStuff::pMapItemHead;
///////////////////////////////////////////////
#include "stdarg.h"
extern CString		CSprintf(const char* format,...);
inline	CString	LoadResString(int resnum)
{
	CString s;
	s.LoadString(resnum);
	return s;
};


void	Persons4::StartUpMapWorld()
{		//do whenever we go to the map screen
	pItem=WorldStuff::pItem;
	{	for (int i=0;i<PITEMTABLESIZE;i++)
		{	delete(pItem[i]);
			pItem[i]=NULL;
		}
	}
	{
		Persons4	Persons_4;
		Persons_4.InitTables();
		Persons_4.LoadSubPiece(NULL,FIL_1_mainmig,0,LOAD);
		Persons_4.LoadSubPiece(NULL,FIL_1_convoy,0,LOAD);

	}
	for (int front=0;front<3;front++)		//JIM EDIT HERE		//JIM 18Feb99
//DeadCode DAW 27Jun99 		if (SupplyTree::supplylines[front]->frontline->status==FRONTLINE)
		{
			FileNum	bf=FIL_NULL;
			FileNum	bn=FIL_NULL;
			if (	SupplyTree::supplylines[front]->initiative==REDATTACKING
				||	SupplyTree::supplylines[front]->initiative==REDINITIATIVE
				)
			{
				bf=SupplyTree::supplylines[front]->frontline->bluefrontBF->bf;
				bn=SupplyTree::supplylines[front]->frontline->bluefrontBF->nodetree;
			}
			else
			if (SupplyTree::supplylines[front]->initiative==BLUEATTACKING
				||	SupplyTree::supplylines[front]->initiative==BLUEINITIATIVE
				)
			{
				bf=SupplyTree::supplylines[front]->frontline->redfrontBF->bf;
				bn=SupplyTree::supplylines[front]->frontline->redfrontBF->nodetree;
			}
			if (bf)
			{
				Persons4	Persons_4;
				Persons_4.LoadSubPiece(NULL,bf,front+1,LOAD);
				SupplyTree::supplylines[front]->groundbattle.LoadBattleNodes(bn);
				SupplyTree::supplylines[front]->groundbattle.LinkBattleNodes();

#ifndef NDEBUG
				CString missingnodes="";
				for(int node=0;node<SupplyTree::supplylines[front]->groundbattle.usednodes;node++)
				{
					SuperBattleNode* bn=&SupplyTree::supplylines[front]->groundbattle.nodelist[node];	
					CString onenode="";
					if (bn->in.uid && Persons2::ConvertPtrUID(bn->in.uid)==NULL)
						onenode+=CSprintf(" I:%04x",bn->in.uid);
					if (bn->out.uid && Persons2::ConvertPtrUID(bn->out.uid)==NULL)
						onenode+=CSprintf(" O:%04x",bn->out.uid);
					if (bn->mainuid && Persons2::ConvertPtrUID(bn->mainuid)==NULL)
						onenode+=CSprintf(" M:%04x",bn->mainuid);
					if (onenode!="")
						missingnodes+=LoadResString(bn->mainids)+onenode+"\n";
				}
				if (missingnodes!="")
					_Error.EmitSysErr(CString("The following nodes are not in the file %s:\n")+missingnodes,File_Man.namenumberedfile(bf));
#endif

			}
		}			   //END OF JIM EDIT						//JIM 18Feb99
	for (int i=0;i<Profile::MAX_PACKS;i++)
	{
		if (Todays_Packages.PreLoad(i))
			Todays_Packages.Load(i);
	}
//	Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
//	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];

//	SupplyTree::NodeReview ();
//init and test code
//	MMC.currtime = HR11;
	
//	MMC.Sky.SetMissionConditions ();

}


void	Persons4::ShutDownMapWorld()
{		//do whenever we come off the map screen
	if (pItem)
		for (int i=0;i<PITEMTABLESIZE;i++)
			if (pItem[i])
			{
				delete pItem[i];
				pItem[i]=NULL;
			}
	pItem=WorldStuff::pItem;
}


bool	PackageList::PreLoad(int packnum,FileNum fil,const char* name,bool copyprimary,bool copysecondaries)
{	//need to pre-read package header..
	if (copyprimary || copysecondaries)
	{
		if (!fil)
			fil=FileNum(FIL_RUNTIMEPACK0+packnum);
		if (name)
		{
			fil = File_Man.fakefile(fil,name);
		}
		fileblock f(fil);
		pack[packnum].DecodePackage((string)f.getdata(),copyprimary);
		return true;
	}
	else
		return (pack[packnum][0][0].uid!=UID_NULL);
}
void	PackageList::Load(int packnum,FileNum fil,const char* name)
{
		Persons4	Persons_4;
		if (!fil)
			fil=FileNum(FIL_RUNTIMEPACK0+packnum);
		if (name)
		{
			fil = File_Man.fakefile(fil,name);
		}
		pack[packnum].SetTargetUIDs();
		Persons_4.LoadSubPiece(NULL,fil,Persons4::LOADEDBFS+packnum,Persons4::LOAD);
		FixupAircraft(packnum);
		pack[packnum].CountWaypoints();
}

void Profile::SetACTypesFromGeneric()
{

}


void	PackageList::SaveGame(BOStream& bos)
{
	for (int packs=0;packs<Profile::MAX_PACKS;packs++)
		if (pack[packs][0][0].uid)
			SaveBin(&packs[pack],bos);
}

void	PackageList::FixupAircraft(int packnum)
{
		int wave=-1;
		int group;
		int i;
		UniqueID	baseac=Persons2::assignuid(BlueAcBAND);

		for (i=baseac+1;i!=baseac;i=((BlueAcBANDEND==i)?BlueAcBAND:i+1))
		{
			info_airgrp* a=*Persons2::ConvertPtrUID(UniqueID(i));
			if (a && a->bfieldindex==Persons4::LOADEDBFS+packnum)
			{
				a->bfieldindex=Persons4::LOADEDBFS2+packnum;					  //JIM 20/05/99
				if (a->wpref)
				{
					wave++;
					group=0;
					pack[packnum][wave].firstwp=a->wpref;
				}
				else
					if(!pack[packnum][wave][group].numflights)
						group++;
				pack[packnum][wave][group].uid=UniqueID(i);
	 			pack[packnum][wave][group].SetSquad(pack[packnum][wave][group].squadron);

				group++;
			}

		}
		pack[packnum].egressloc= FindEgressPoint(pack[packnum].packagetarget); //RDH 19/03/99

		for (i=0;i<Profile::MAX_WAVES;i++)
		{
			int targettime;
			int laststartperiodtime;

			if (Todays_Packages[packnum][i].targettime > AFTERNOONPERIODSTART)
				laststartperiodtime = AFTERNOONPERIODSTART;
			else if (Todays_Packages[packnum][i].targettime > MIDDAYPERIODSTART)
				laststartperiodtime = MIDDAYPERIODSTART;
//DEADCODE RDH 01/07/99 			else if (Todays_Packages[packnum][i].targettime > MORNINGPERIODSTART)
			else
				laststartperiodtime = MORNINGPERIODSTART;
			targettime = Todays_Packages[packnum][i].targettime - laststartperiodtime + MMC.currtime;
			if	(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
			{
				if (targettime >	HR16MIN20)
					//don't want it too dark in winter
					targettime =	HR16MIN20;							  //RDH 11/06/99
				if (targettime <	HR08)								  //RDH 27/06/99
					//don't want it too dark in winter
					targettime =	HR08;							  //RDH 11/06/99 //RDH 27/06/99
			}
			SetWaveTimes(packnum, i, targettime);
		}

		if (pack[packnum].duty == DC_AR)
			pack[packnum].ResetPatrolItems();					//RDH 30Mar99

		pack[packnum].RecalcRoutePositions();
}

void	PackageList::LoadGame(BIStream& bis)
{
	for (int p=0;p<Profile::MAX_PACKS;p++)
		ClearPack(p);
	hipack=hiwave=higroup=0;
	hiwp=UID_NULL;

	enum	{SIZ=20000};
	char* buffer=new char[SIZ];
	bis.read(buffer,SIZ);
	int fsize=bis.gcount();
	assert (fsize<SIZ);
	char* ind=buffer;
	char* const last=buffer+fsize;
	int packnum=0;
	Persons4	Persons_4;
	while (ind<last)
	{
		pack[packnum].DecodePackage(ind,true);
		while (*ind++)	
		{}
		pack[packnum].SetTargetUIDs();
		Persons_4.LoadSubPiece(NULL,ind,Persons4::LOADEDBFS+packnum,Persons4::LOAD);
		FixupAircraft(packnum);
		pack[packnum].CountWaypoints();
		packnum++;
	}
	delete buffer;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitViewFromMap
//Author		Paul.   
//Date			Thu 11 Mar 1999
//------------------------------------------------------------------------------
void Persons4::InitViewFromMap(UniqueID trg_uid)
{
	WorldStuff::pMapItemHead=NULL;

	if (pItem)
		for (int i=0;i<PITEMTABLESIZE;i++)
			if (pItem[i]!=NULL && pItem[i]->uniqueID.count==trg_uid)
				WorldStuff::pMapItemHead=pItem[i];

	if (WorldStuff::pMapItemHead)
	{
		((itemptr)WorldStuff::pMapItemHead)->Next=NULL;
		SLong ix=WorldStuff::pMapItemHead->World.X,
				iz=WorldStuff::pMapItemHead->World.Z;

		//find all other items in a 10km radius
		for (int i=0;i<PITEMTABLESIZE;i++)
		{
			SLong d;
			if (pItem[i]!=NULL &&
				pItem[i]->Status.size!=WAYPOINTSIZE &&
				(d=Math_Lib.Distance2d(pItem[i]->World.X-ix,pItem[i]->World.Z-iz))>0 &&
				d<1000000)
			{
				((itemptr)pItem[i])->Next=((itemptr)WorldStuff::pMapItemHead)->Next;
				((itemptr)WorldStuff::pMapItemHead)->Next=(itemptr)pItem[i];
			}
		}
	}
	//pMapItemHead now points to a linked list of items within a 10km range
	//of the selected target. The head of the list is the selected item.

	pItem=WorldStuff::pItem;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShutDownViewFromMap
//Author		Paul.   
//Date			Fri 12 Mar 1999
//------------------------------------------------------------------------------
void Persons4::ShutDownViewFromMap()
{
	itemptr ip=itemptr(WorldStuff::pMapItemHead);
	while (ip)
	{
		itemptr np=ip->Next;
		ip->World.Y=0;
		ip->Next=(itemptr)-1;
		ip=np;
	}
}
