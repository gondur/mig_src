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

// General.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "General.h"
#include	"node.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneral dialog


CGeneral::CGeneral(int sgt,int uid,CWnd* pParent /*=NULL*/)
	: RowanDialog(CGeneral::IDD, pParent)
{
	SetProjSpecific(-1,sgt,uid);
	//{{AFX_DATA_INIT(CGeneral)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneral)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RSTATICCTRL1,m_IDC_RSTATICCTRL1);
	DDX_Control(pDX,IDC_TARGET_TITLE,m_IDC_TARGET_TITLE);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_MSR,m_IDC_MSR);
	DDX_Control(pDX,IDC_RSTATICCTRL9,m_IDC_RSTATICCTRL9);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_RSTATICCTRL11,m_IDC_RSTATICCTRL11);
	DDX_Control(pDX,IDC_RSTATICCTRL12,m_IDC_RSTATICCTRL12);
	DDX_Control(pDX,IDC_STATUS,m_IDC_STATUS);
	DDX_Control(pDX,IDC_RSTATICCTRL15,m_IDC_RSTATICCTRL15);
	DDX_Control(pDX,IDC_DATE_LAST_SORTIE,m_IDC_DATE_LAST_SORTIE);
	DDX_Control(pDX,IDC_REPAIR_LEVEL,m_IDC_REPAIR_LEVEL);
	DDX_Control(pDX,IDC_RSTATICCTRL21,m_IDC_RSTATICCTRL21);
	DDX_Control(pDX,IDC_THREAT_AAA,m_IDC_THREAT_AAA);
	DDX_Control(pDX,IDC_THREAT_MIG15,m_IDC_THREAT_MIG15);
	//}}AFX_DATA_MAP




}


BEGIN_MESSAGE_MAP(CGeneral, CDialog)
	//{{AFX_MSG_MAP(CGeneral)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneral message handlers

void	CGeneral::PrintDamageLevel(UWord damagelevel)
{
	CRStatic* 	stat=GETDLGITEM(IDC_REPAIR_LEVEL);

	if (damagelevel == 0)
		stat->SetString(RESSTRING(OPERATIONAL));
	else if (damagelevel < 100)
		stat->SetString(RESSTRING(DAMAGED));
	else 
		stat->SetString(RESSTRING(DESTROYED));

}
void	CGeneral::PrintMiGActivity(SupplyNode*	node)
{
	int migact=0;
	for (int reqaf=0;reqaf<3;reqaf++)
		if (node->airfield[reqaf])
		{
			int af=0;			//AirFieldInfo
			while (SupplyTree::airfieldinfo[af].nationality!=NAT_ALIGN)
				if (SupplyTree::airfieldinfo[af].airfield==node->airfield[reqaf])
					break;
				else
					af++;
			if (SupplyTree::airfieldinfo[af].nationality==NAT_RED)
				migact+=SupplyTree::airfieldinfo[af].activeac;
		}
	migact = migact - 6;
	if (migact < 0)
		migact = 0;
	migact/=SupplyTree::STANDARDREDAFCOMPLEMENT;
	if (migact > 4)
		migact = 4;
		CRStatic* stat=GETDLGITEM(IDC_THREAT_MIG15);
	stat->SetString(RESLIST(ENEMYACTIVITY0,migact));
}

void	CGeneral::DisplayRouteInfo(UniqueID uid, SupplyNode*	node, SupplyTree::Supply2UID relation)
{
	
	int route = relation - SupplyTree::S2U_ROUTE0;
	if (route < 0)
		route = 0;
	if (route > 2)
		route = 0;
	SupplyRoute* sr = node->route[route];
		CRStatic* stat=GETDLGITEM(IDC_THREAT_AAA);
	stat->SetString(RESLIST(ENEMYACTIVITY0,sr->attackstats.aaalevel/60));

	sr = SupplyTree::FindBridge(uid, sr);
	PrintLastSortie(sr->attackstats);

	stat=GETDLGITEM(IDC_STATUS);
	if (uid == sr->redsupplyUID)
	{//mobile
		int traffic = (4 * sr->storeslaunched)/sr->maxcapacitysummer;
		if (traffic > 3)
			  traffic = 3;
		stat->SetString(RESLIST(TRAFFIC_QUIET,traffic));
		stat=GETDLGITEM(IDC_RSTATICCTRL11);
		stat->SetString(RESSTRING(ROUTETYPE));
		stat=GETDLGITEM(IDC_REPAIR_LEVEL);
		int  routesize = sr->maxcapacitysummer/sr->storespermobile;	
		if (sr->storespermobile != STORES_TRUCK)
		{
			if (routesize <= MIN_TRAINSPERDAY)
				stat->SetString(RESSTRING(L_MINORRAILLINK));
			else if (routesize <= STD_TRAINSPERDAY)
				stat->SetString(RESSTRING(STD_RAILLINK));
			else 
				stat->SetString(RESSTRING(MAJOR_RAILLINK));
		}else
		{
			if (routesize <= MIN_TRUCKSPERDAY)
				stat->SetString(RESSTRING(L_ROADTRACK));
			else if (routesize <= STD_TRUCKSPERDAY)
				stat->SetString(RESSTRING(SINGLEROAD));
			else 
				stat->SetString(RESSTRING(MAJORROAD));
		}
	}else
	{
		stat=GETDLGITEM(IDC_STATUS);
		stat->SetString(RESLIST(OWNER_RED,node->status));

		PrintDamageLevel(sr->attackstats.damagelevel);

	}
			


}
void	CGeneral::PrintLastSortie(Attacks attackstats)
{
		CRStatic* stat=GETDLGITEM(IDC_DATE_LAST_SORTIE);
	if (attackstats.daylasthit)
	{
		SLong date = MMC.startdate + ((attackstats.daylasthit - 1) * SECSPERDAY);
		stat->SetString(GetDateName(date,DATE_LONG));
	}else
		stat->SetString(RESSTRING(NEVER));
}


BOOL CGeneral::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRStatic* stat=GETDLGITEM(IDC_TARGET_TITLE);

	UniqueID	trg=UniqueID(wavenum);
	int uidband=Persons2::getbandfromUID(trg);


	if (uidband == AmberBattleNodeBAND)
	{
		TeamDef		*team=SupplyTree::WestRoute.groundbattle.FindTeamAtLocation(trg);
		if (!team) 
			team=SupplyTree::CentralRoute.groundbattle.FindTeamAtLocation(trg);
		else if (!team) 
			team=SupplyTree::EastRoute.groundbattle.FindTeamAtLocation(trg);
		if (team)
			stat->SetString(LoadResString(team->forcename));
	}else
		stat->SetString(GetTargName(trg));

	stat=GETDLGITEM(IDC_RSTATICCTRL11);
	stat->SetString(RESSTRING(REPAIRS));

	SupplyTree::Supply2UID	relation;
	SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(trg,&relation);
	Attacks* attacks=SupplyTree::GetAttacks(trg,node,relation);
	
	if (!node)
	{
		stat=GETDLGITEM(IDC_MSR);
		stat->SetString("");
	}
	else
	{
//DEADCODE RDH 19/06/99 		PrintMiGActivity(node);
		stat=GETDLGITEM(IDC_MSR);
		if (node->supplyline==&SupplyTree::WestRoute)
			stat->SetString(RESSTRING(WEST));
		elseif (node->supplyline==&SupplyTree::EastRoute)
			stat->SetString(RESSTRING(EAST));
		else
			stat->SetString(RESSTRING(CENTRAL));

		if  (		(relation == SupplyTree::S2U_ROUTE0)
				||	(relation == SupplyTree::S2U_ROUTE1)
				||	(relation == SupplyTree::S2U_ROUTE2)
			)
		{
			PrintMiGActivity(node);
			DisplayRouteInfo(trg, node, relation);
 		}else
		{

//DEADCODE RDH 12/06/99 			stat=GETDLGITEM(IDC_THREAT_AAA);
//DEADCODE RDH 12/06/99 			stat->SetString(RESLIST(ENEMYACTIVITY0,node->attackstats.aaalevel/60));
//DEADCODE RDH 12/06/99 			stat=GETDLGITEM(IDC_STATUS);

			if  (		(relation == SupplyTree::S2U_AF0)
					||	(relation == SupplyTree::S2U_AF1)
					||	(relation == SupplyTree::S2U_AF2)
				)

			{
				AirFieldInfo* af=SupplyTree::FindAirfieldForItem(trg);

				int migact = 0;
				if (af->nationality==NAT_RED)
					migact=af->activeac;
				migact/5;
				if (migact > 4)
					migact = 4;

				CRStatic* stat=GETDLGITEM(IDC_THREAT_MIG15);
				stat->SetString(RESLIST(VERYLOW,migact));

				stat=GETDLGITEM(IDC_THREAT_AAA);					  //RDH 12/06/99
				stat->SetString(RESLIST(ENEMYACTIVITY0,af->attackstats.aaalevel/60)); //RDH 12/06/99
				stat=GETDLGITEM(IDC_STATUS);						  //RDH 12/06/99
				if  (		(af)
						&&	(af->activeac)
					)
					stat->SetString(RESSTRING(ACTIVE));
				else
					stat->SetString(RESLIST(OWNER_RED,node->status));	  //RDH 12/06/99
			}else if (relation == SupplyTree::S2U_MAIN)
			{
				PrintMiGActivity(node);
				stat=GETDLGITEM(IDC_THREAT_AAA);
				stat->SetString(RESLIST(ENEMYACTIVITY0,node->attackstats.aaalevel/60));
				stat=GETDLGITEM(IDC_STATUS);
				int mag = (4 * node->currentstores)/(STORES_MAXSUPPLY-250);
				if (mag > 4)
					mag = 4;
				stat->SetString(RESLIST(VERYLOW,mag));
			}else
			{
				PrintMiGActivity(node);
				stat=GETDLGITEM(IDC_THREAT_AAA);
				stat->SetString(RESLIST(ENEMYACTIVITY0,node->attackstats.aaalevel/60));
				stat=GETDLGITEM(IDC_STATUS);
				stat->SetString(RESLIST(OWNER_RED,node->status));
			}
			
			PrintLastSortie(*attacks);

			PrintDamageLevel(attacks->damagelevel);

			stat = GETDLGITEM(IDC_RSTATICCTRL9);
			if (relation == SupplyTree::S2U_MAIN)
				stat->SetString(RESSTRING(ACTIVITY));
			else			
				stat->SetString(RESSTRING(STATUS));


		}
	}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
