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

// MsnDeBrf.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "MsnDeBrf.h"

#include	"bfnumber.h"
#include	"persons2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef	  THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeBrief dialog


CDeBrief::CDeBrief(int package, CWnd* pParent /*=NULL*/)
	: RowanDialog(CDeBrief::IDD, pParent)
{
	packnum = package;
	//{{AFX_DATA_INIT(CDeBrief)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDeBrief::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeBrief)
		// NOTE: the ClassWizard will add DDX and DDV calls here
		DDX_Control(pDX,IDC_OBJECTIVE,m_IDC_OBJECTIVE);
		DDX_Control(pDX,IDC_RATING,m_IDC_RATING);
		DDX_Control(pDX,IDC_STATUS, m_IDC_STATUS);

		DDX_Control(pDX,IDC_RSTATICSOFT0,m_IDC_RSTATICSOFT0);
		DDX_Control(pDX,IDC_RSTATICSOFT1,m_IDC_RSTATICSOFT1);
		DDX_Control(pDX,IDC_RSTATICSOFT2,m_IDC_RSTATICSOFT2);
		DDX_Control(pDX,IDC_RSTATICSOFT3,m_IDC_RSTATICSOFT3);
		DDX_Control(pDX,IDC_INFOSOFT0,m_IDC_INFOSOFT0);
		DDX_Control(pDX,IDC_INFOSOFT1,m_IDC_INFOSOFT1);
		DDX_Control(pDX,IDC_INFOSOFT2,m_IDC_INFOSOFT2);
		DDX_Control(pDX,IDC_INFOSOFT3,m_IDC_INFOSOFT3);

		DDX_Control(pDX,IDC_RSTATIC3,m_IDC_RSTATIC3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeBrief, CDialog)
	//{{AFX_MSG_MAP(CDeBrief)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeBrief message handlers

BOOL CDeBrief::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 	SupplyTree::Supply2UID	relation;
 	SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(
	 					Todays_Packages.pack[packnum].packagetarget,&relation);



	CRStatic*   s=GETDLGITEM(IDC_OBJECTIVE);
	s->SetString(RESLIST(CLEAR,MMC.Sky.Conditions));

	if (Todays_Packages.pack[packnum].packagetarget != UID_NULL)

		s->SetString(GetTargName(Todays_Packages.pack[packnum].packagetarget));
	else
		s->SetString("");


	info_airgrp* g= *Persons2::ConvertPtrUID(Todays_Packages[packnum][0][0].uid);
	DutyType duty = (DutyType)g->duty.Evaluate();
	SupplyNode*	battlenode = node->supplyline->frontline->forward->suppliee;
//DEADCODE RDH 25/06/99 	if (node == battlenode)
//DEADCODE RDH 25/06/99 		duty = DC_CAS;		

	s=GETDLGITEM(IDC_RATING);
	bool missionsuccess = MMC.GetMissionSuccess(packnum);
	s=GETDLGITEM(IDC_RATING);
	if (missionsuccess)
		s->SetString(RESSTRING(SUCCESS));
	else
		s->SetString(RESSTRING(L_FAILURE));



	switch	(duty)
	{
		case	DC_BOMB:
		{

		 	s=GETDLGITEM(IDC_RSTATIC3);
			s->ShowWindow(SW_SHOW);
			
			

	    	s=GETDLGITEM(IDC_RSTATICSOFT0);
		 	s->SetString(RESSTRING(DAMAGETHISMSN));
	    	s=GETDLGITEM(IDC_RSTATICSOFT1);
			s->SetString(RESSTRING(DAMAGETOTAL));
	    	s=GETDLGITEM(IDC_RSTATICSOFT2);
			s->SetString(RESSTRING(SUPPLIESDESTROYED));
	    	s=GETDLGITEM(IDC_RSTATICSOFT3);
			s->ShowWindow(SW_SHOW);
	 		s->SetString(RESSTRING(SUPPLIESREMAINING));

//DeadCode RDH 01Jul99 		 	s=GETDLGITEM(IDC_STATUS);
//DeadCode RDH 01Jul99 			s->ShowWindow(SW_SHOW);
//DeadCode RDH 01Jul99 		 	if (node->attackstats.damagelevel == 0)
//DeadCode RDH 01Jul99 		 		s->SetString(RESSTRING(OPERATIONAL));
//DeadCode RDH 01Jul99 		 	else if (node->attackstats.damagelevel < 100)
//DeadCode RDH 01Jul99 		 		s->SetString(RESSTRING(DAMAGED));
//DeadCode RDH 01Jul99 		 	else 
//DeadCode RDH 01Jul99 		 		s->SetString(RESSTRING(DESTROYED));

		   	s=GETDLGITEM(IDC_INFOSOFT0);

			int damage, damage_this_mission;
			SupplyTree::Supply2UID rel;
			SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(Todays_Packages.pack[packnum].packagetarget,&rel);
			switch (rel)
			{
				case SupplyTree::S2U_MAIN:
					damage=node->attackstats.damagelevel;
				break;
				case SupplyTree::S2U_AF0:
				case SupplyTree::S2U_AF1:
				case SupplyTree::S2U_AF2:
					damage=SupplyTree::FindAirfieldForItem(Todays_Packages.pack[packnum].packagetarget)->attackstats.damagelevel;
				break;
				case SupplyTree::S2U_ROUTE0:
				case SupplyTree::S2U_ROUTE1:
				case SupplyTree::S2U_ROUTE2:
					damage=node->route[rel-SupplyTree::S2U_ROUTE0]->attackstats.damagelevel;
			}
			damage_this_mission = damage - MMC.packageprevscores[packnum];
			if (damage_this_mission > 100)
				damage_this_mission = 100;
			if (damage_this_mission < 0)							  //RDH 09/06/99
				damage_this_mission = 0;							  //RDH 09/06/99
		  	s->SetString(CSprintf("%i%%", damage_this_mission));
		   	s=GETDLGITEM(IDC_INFOSOFT1);
//DEADCODE RDH 07/06/99 			damage = node->attackstats.damagelevel;
			if (damage > 100)
				damage = 100;
			if (damage < 0)											  //RDH 09/06/99
				damage = 0;											  //RDH 09/06/99
		  	s->SetString(CSprintf("%i%%", damage));

		   	
											

		   	SWord i = 0;
			SupplyRoute*  currroute;
			int stores_destroyed = 0;


		 	s=GETDLGITEM(IDC_STATUS);
			s->ShowWindow(SW_SHOW);
		 	if (damage == 0)
		 		s->SetString(RESSTRING(OPERATIONAL));
		 	else if (damage < 100)
		 		s->SetString(RESSTRING(DAMAGED));
		 	else 
		 		s->SetString(RESSTRING(DESTROYED));

			
//DEADCODE RDH 27/05/99 			while   (	(i < NUM_OF_SUPPLYROUTES)
//DEADCODE RDH 27/05/99 					)
//DEADCODE RDH 27/05/99 			{
//DEADCODE RDH 27/05/99 				currroute =  node->route[i];
//DEADCODE RDH 27/05/99 				while (currroute)
//DEADCODE RDH 27/05/99 				{
//DEADCODE RDH 27/05/99 					stores_destroyed += currroute->stores_destroyed;
//DEADCODE RDH 27/05/99 					currroute = currroute->alternateroute;  
//DEADCODE RDH 27/05/99 				}
//DEADCODE RDH 27/05/99 				i++;
//DEADCODE RDH 27/05/99 			}			


			if (	 	(rel == SupplyTree::S2U_AF0)
					||	(rel == SupplyTree::S2U_AF1)
					||	(rel == SupplyTree::S2U_AF2)
					||	(rel == SupplyTree::S2U_ROUTE0)
					||	(rel == SupplyTree::S2U_ROUTE1)
					||	(rel == SupplyTree::S2U_ROUTE2)


			   )
			{
		    	s=GETDLGITEM(IDC_RSTATICSOFT2);
				s->ShowWindow(SW_HIDE);
		    	s=GETDLGITEM(IDC_RSTATICSOFT3);
				s->ShowWindow(SW_HIDE);
			   	s=GETDLGITEM(IDC_INFOSOFT2);
				s->ShowWindow(SW_HIDE);
				s=GETDLGITEM(IDC_INFOSOFT3);
				s->ShowWindow(SW_HIDE);

			}else
			{
				//The complication here is that currentstores includes
				//the removal of the destoyed stores
				//	destroyed = (current + destroyed)*damage tokens/tokens

				int tokens = node->attackstats.tokensinmw + node->attackstats.tokensinbf
										- node->attackstats.damagedtokens;
				if (tokens <= 0)
					stores_destroyed = 0;
				else
					stores_destroyed = node->currentstores * node->attackstats.damagedtokens/tokens;

		  		s=GETDLGITEM(IDC_INFOSOFT2);
				s->ShowWindow(SW_SHOW);
				s->SetString(CSprintf("%i", stores_destroyed));
		   		s=GETDLGITEM(IDC_INFOSOFT3);
				s->ShowWindow(SW_SHOW);
		  		s->SetString(CSprintf("%i", node->currentstores));
			}
			break;
		}
		case	DUTYBARCAP:
		{
		 	s=GETDLGITEM(IDC_STATUS);
			s->ShowWindow(SW_HIDE);
			
		 	s=GETDLGITEM(IDC_RSTATIC3);
			s->ShowWindow(SW_HIDE);

//MIGSREPORTED removed 
	    	s=GETDLGITEM(IDC_RSTATICSOFT0);
		 	s->SetString(RESSTRING(MIGSDESTROYED));
	    	s=GETDLGITEM(IDC_RSTATICSOFT1);
			s->SetString(RESSTRING(UNACLOST));
	    	s=GETDLGITEM(IDC_RSTATICSOFT2);
			s->ShowWindow(SW_HIDE);
//DEADCODE RDH 14/05/99 			s->SetString(RESSTRING(UNACLOST));
	    	s=GETDLGITEM(IDC_RSTATICSOFT3);
			s->ShowWindow(SW_HIDE);


		   	s=GETDLGITEM(IDC_INFOSOFT0);
		  	s->SetString(CSprintf("%i", MMC.debrief.barcapkills));
		   	s=GETDLGITEM(IDC_INFOSOFT1);
		  	s->SetString(CSprintf("%i", MMC.debrief.barcaplost));

		   	s=GETDLGITEM(IDC_INFOSOFT2);
			s->ShowWindow(SW_HIDE);


			
			s=GETDLGITEM(IDC_INFOSOFT3);
			s->ShowWindow(SW_HIDE);

			break;
		}
		case	DC_AR:
		{//reccy along supply lines
		 	s=GETDLGITEM(IDC_STATUS);
			s->ShowWindow(SW_HIDE);
			
		 	s=GETDLGITEM(IDC_RSTATIC3);
			s->ShowWindow(SW_HIDE);


	    	s=GETDLGITEM(IDC_RSTATICSOFT0);
		 	s->SetString(RESSTRING(VEHICLESREPORTED));
	    	s=GETDLGITEM(IDC_RSTATICSOFT1);
			s->SetString(RESSTRING(VEHICLESDESTROYED));

	    	s=GETDLGITEM(IDC_RSTATICSOFT2);
			s->SetString(RESSTRING(SUPPLIESDESTROYED));
//DEADCODE RDH 23/06/99 	    	s=GETDLGITEM(IDC_RSTATICSOFT3);
//DEADCODE RDH 23/06/99 			s->ShowWindow(SW_SHOW);
//DEADCODE RDH 23/06/99 	 		s->SetString(RESSTRING(SUPPLIESREMAINING));
	    	s=GETDLGITEM(IDC_RSTATICSOFT3);
			s->ShowWindow(SW_HIDE);



			
		   	s=GETDLGITEM(IDC_INFOSOFT0);
			//should not be devided.
		  	s->SetString(CSprintf("%i", MMC.packageprevscores[packnum])); //JIM 21/05/99



		 	SupplyRoute*	currroute;
			SupplyTree::Supply2UID rel;

			SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(Todays_Packages.pack[packnum].packagetarget,&rel);
			switch (rel)
			{
				case SupplyTree::S2U_ROUTE0:
					currroute = node->route[0];
					break;
				case SupplyTree::S2U_ROUTE1:
					currroute = node->route[1];
					break;
				case SupplyTree::S2U_ROUTE2:
					currroute = node->route[2];
					break;
			}
			currroute = SupplyTree::FindBridge(Todays_Packages.pack[packnum].packagetarget, currroute);
		   	s=GETDLGITEM(IDC_INFOSOFT1);
		  	s->SetString(CSprintf("%i", currroute->stores_destroyed/currroute->storespermobile));


//DEADCODE RDH 30/06/99 
//DEADCODE RDH 30/06/99 			stores_destroyed = MMC.StoresDestroyedForNodeRoute(node);
//DEADCODE RDH 30/06/99 
//DEADCODE RDH 30/06/99 		   	s=GETDLGITEM(IDC_INFOSOFT1);
//DEADCODE RDH 30/06/99 			//this is a simplification because the stored_destroyed may not be 
//DEADCODE RDH 30/06/99 			//transported in the route 0 type						  //RDH 27/05/99
//DEADCODE RDH 30/06/99 		  	s->SetString(CSprintf("%i", stores_destroyed/node->route[0]->storespermobile));


//DEADCODE RDH 24/03/99 			while   (	(i < NUM_OF_SUPPLYROUTES)
//DEADCODE RDH 24/03/99 					)
//DEADCODE RDH 24/03/99 			{
//DEADCODE RDH 24/03/99 				currroute =  node->route[i];
//DEADCODE RDH 24/03/99 				while (currroute)
//DEADCODE RDH 24/03/99 				{
//DEADCODE RDH 24/03/99 					stores_destroyed = currroute->stores_destroyed;
//DEADCODE RDH 24/03/99 					currroute = currroute->alternateroute;  
//DEADCODE RDH 24/03/99 				}
//DEADCODE RDH 24/03/99 				i++;
//DEADCODE RDH 24/03/99 			}			
			s=GETDLGITEM(IDC_INFOSOFT2);
		  	s->SetString(CSprintf("%i", currroute->stores_destroyed));

			s=GETDLGITEM(IDC_INFOSOFT3);
			s->ShowWindow(SW_HIDE);
//DEADCODE RDH 23/06/99 		  	s->SetString(CSprintf("%i", node->currentstores));


			break;
		}
		case	DC_CAS:
		{//reccy along supply lines
		 	s=GETDLGITEM(IDC_STATUS);
			s->ShowWindow(SW_HIDE);
			
		 	s=GETDLGITEM(IDC_RSTATIC3);
			s->ShowWindow(SW_HIDE);


	    	s=GETDLGITEM(IDC_RSTATICSOFT0);
		 	s->SetString(RESSTRING(ARMOURDESTROYED));
	    	s=GETDLGITEM(IDC_RSTATICSOFT1);
			s->SetString(RESSTRING(ARTILLERYDESTROYED));

	    	s=GETDLGITEM(IDC_RSTATICSOFT2);
			s->SetString(RESSTRING(PLATOONSNEUT));
	    	s=GETDLGITEM(IDC_RSTATICSOFT3);
			s->ShowWindow(SW_HIDE);

			int troops = 0, tanks = 0, artillery = 0;
			TeamDef::Team blueforce;

			if	(		(node->supplyline->initiative==REDATTACKING)
//DEADCODE RDH 28/02/99 				&&	(tabside == 0)
			)
				blueforce = TeamDef::HOME;
			else
				blueforce = TeamDef::AWAY;

			for (int i=0;i<node->supplyline->groundbattle.usedteams;i++)
			{
				if (node->supplyline->groundbattle.teamlist[i].team!=blueforce)
				{
					switch(node->supplyline->groundbattle.teamlist[i].forcetype)
					{
						case	TeamDef::TROOPSONLY:
						case	TeamDef::MORTAR:					  //JIM 29/06/99
						{
							troops += node->supplyline->groundbattle.teamlist[i].lastlostforces;
							break;
						}
						case	TeamDef::TANKS:
						case	TeamDef::MORTARTRUCK:				  //JIM 29/06/99
						{
							tanks += node->supplyline->groundbattle.teamlist[i].lastlostforces; //JIM 13/06/99;
							break;
						}
						case	TeamDef::ARTILLARY:
						case	TeamDef::MAXFORCETYPES:
						{
							artillery += node->supplyline->groundbattle.teamlist[i].lastlostforces;
							break;
						}
					}

				}
			}
			if (troops)
				if (troops>50)
					troops/=50;
				else
					troops=1;
			if (tanks)
				if (tanks>50)
					tanks/=50;
				else
					tanks=1;
			if (artillery)
				if (artillery>50)
					artillery/=50;
				else
					artillery=1;

		   	s=GETDLGITEM(IDC_INFOSOFT0);
		  	s->SetString(CSprintf("%i", tanks));
		   	s=GETDLGITEM(IDC_INFOSOFT1);
		  	s->SetString(CSprintf("%i", artillery));


			s=GETDLGITEM(IDC_INFOSOFT2);
		  	s->SetString(CSprintf("%i", troops));
		   	s=GETDLGITEM(IDC_INFOSOFT3);
			s->ShowWindow(SW_HIDE);


			break;
		}


	}

	  






	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void	CDeBrief::ParentDialClosed(RDialog*,int rv)
{
 	OnCancel();
}
