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

// MResult.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "MResult.h"
#include "rlistbox.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CMResult dialog


CMResult::CMResult(CWnd* pParent /*=NULL*/)
	: RowanDialog(CMResult::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMResult)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMResult)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_PROFILE,m_IDC_PROFILE);
	DDX_Control(pDX,IDC_DEBRIEF,m_IDC_DEBRIEF);
	DDX_Control(pDX,IDC_REPEAT,m_IDC_REPEAT);
	DDX_Control(pDX,IDC_NEXTPERIOD,m_IDC_NEXTPERIOD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMResult, CDialog)
	//{{AFX_MSG_MAP(CMResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////
//
// Function:    GetMissionSuccess
// Date:		 27/05/99
// Author:		rdh
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	Campaign::GetMissionSuccess(int packnum)
{
  	bool missionsuccess = false;
	int		prevlevel=0;
	int		currlevel=0;
	int		badlevel=0;
	switch (Todays_Packages[packnum].duty)
	{
	case 	DC_BOMB:
	{
		prevlevel=MMC.packageprevscores[packnum];
		SupplyTree::Supply2UID rel;
		SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(Todays_Packages.pack[packnum].packagetarget,&rel);
		switch (rel)
		{
		case SupplyTree::S2U_MAIN:
			currlevel=node->attackstats.damagelevel;
		break;
		case SupplyTree::S2U_AF0:
		case SupplyTree::S2U_AF1:
		case SupplyTree::S2U_AF2:
			currlevel=SupplyTree::FindAirfieldForItem(Todays_Packages.pack[packnum].packagetarget)->attackstats.damagelevel;
		break;
		case SupplyTree::S2U_ROUTE0:
		case SupplyTree::S2U_ROUTE1:
		case SupplyTree::S2U_ROUTE2:
			currlevel=node->route[rel-SupplyTree::S2U_ROUTE0]->attackstats.damagelevel;
		break;
		}
		if (		(currlevel>(prevlevel+40))
				||	 (		(currlevel >= 100)
						&&	(prevlevel < 100)
					 )
			)
			missionsuccess=true;
	}
	break;
	case	DC_CAS:
	{
		//success= (enemieskilled - 2*friendlieskilled)>10
		SupplyTree::Supply2UID rel;
		SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(Todays_Packages.pack[packnum].packagetarget,&rel);
		SupplyLine* line=node->supplyline;
		BattleStruct* battle=&line->groundbattle;
		TeamDef::Team redteam=TeamDef::HOME;
		if (line->initiative==REDATTACKING)
			redteam=TeamDef::AWAY;
		for (int i=0;i<battle->usedteams;i++)
			if (battle->teamlist[i].team==redteam)
				currlevel+=battle->teamlist[i].lastlosses;
			else
				badlevel+=battle->teamlist[i].lastlosses;			  //JIM 18/05/99
		if (currlevel-badlevel*2>18)
			missionsuccess=true;
	}
	break;
	case	DC_WW:	
		//never happens!
	case	DC_AR:
	{
		//success= over 10 trucks killed on section
		SupplyTree::Supply2UID rel;
		SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(Todays_Packages.pack[packnum].packagetarget,&rel);
		SupplyRoute*  road=SupplyTree::FindBridge(Todays_Packages.pack[packnum].packagetarget,node->route[rel-SupplyTree::S2U_ROUTE0]);
		currlevel=road->stores_destroyed;
		if (currlevel>20)
			missionsuccess=true;
	}
	break;
	case	DUTYESCORT:
	case	DUTYBARCAP:
	case	DUTYMIGCAP:
	{
		//success= (enemieskilled - 2*friendlieskilled)>10
		Debrief* debrief=&MMC.debrief;
		currlevel=debrief->barcapkills;
		badlevel=debrief->barcaplost;	
		if (currlevel-badlevel*2>5)
			missionsuccess=true;
	}
	break;
	}
	return(missionsuccess);

}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetOldpackScore
// Date:		03/05/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	Campaign::SetOldPackScore(int packnum)
{	//called prior to entering 3d to back up score of packages
	int		currlevel=0;
	if (Todays_Packages.pack[packnum].packagetarget)
	switch (Todays_Packages[packnum].duty)
	{
	case 	DC_BOMB:
	{
		SupplyTree::Supply2UID rel;
		SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(Todays_Packages.pack[packnum].packagetarget,&rel);
		switch (rel)
		{
		case SupplyTree::S2U_MAIN:
			currlevel=node->attackstats.damagelevel;
//DEADCODE RDH 06/05/99 			node->attackstats.daylasthit = 
		break;
		case SupplyTree::S2U_AF0:
		case SupplyTree::S2U_AF1:
		case SupplyTree::S2U_AF2:
		{
			AirFieldInfo* af = SupplyTree::FindAirfieldForItem(Todays_Packages.pack[packnum].packagetarget);
			currlevel=af->attackstats.damagelevel;
//DEADCODE RDH 06/05/99 			af->attackstats.daylasthit = ;
			break;
		}
		case SupplyTree::S2U_ROUTE0:
		case SupplyTree::S2U_ROUTE1:
		case SupplyTree::S2U_ROUTE2:
			currlevel=node->route[rel-SupplyTree::S2U_ROUTE0]->attackstats.damagelevel;
//DEADCODE RDH 06/05/99 			node->route[rel-SupplyTree::S2U_ROUTE0]->attackstats.daylasthit
		break;
		}
		MMC.packageprevscores[packnum]=currlevel;
	}
	break;
	case	DC_AR:
	{
		SupplyTree::Supply2UID rel;
		SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(Todays_Packages.pack[packnum].packagetarget,&rel);
		SupplyRoute*	s2;
		for (s2=node->route[rel-SupplyTree::S2U_ROUTE0];s2;s2=s2->alternateroute)
			if (s2->redsupplyUID==Todays_Packages.pack[packnum].packagetarget)
			{
				MMC.packageprevscores[packnum]=s2->SetSupplySizeGR(); //JIM 21/05/99
//DEADCODE JIM 21/05/99 					s2->storeslaunched;
//DEADCODE RDH 06/05/99 				s2->attackstats.daylasthit = ;
			}
	}
	break;
	case	DC_WW:	
		//never happens!
	case	DC_CAS:													  //JIM 05/05/99
	{

	}
	break;
	case	DUTYESCORT:
	case	DUTYBARCAP:
	case	DUTYMIGCAP:
	{
	}
	break;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CMResult message handlers


void	CMResult::FillProfileRow(CRListBox* rlistbox,int i)
{
//	rlistbox->AddString(Todays_Packages.pack[i].packname,0);

	if (Todays_Packages.pack[i].packagetarget != UID_NULL)

		rlistbox->AddString(GetTargName(Todays_Packages.pack[i].packagetarget),0);
	else
		rlistbox->AddString("",0);
	info_airgrp* g=
		*Persons2::ConvertPtrUID(Todays_Packages[i][0][0].uid);
	rlistbox->AddString(RESLIST(DUTY_BOMB,Todays_Packages[i].duty/ACTIONSUBCODEMAX),1);

	bool missionsuccess = MMC.GetMissionSuccess(i);
	if (missionsuccess)
		rlistbox->AddString(RESSTRING(SUCCESS),2);
	else
		rlistbox->AddString(RESSTRING(L_FAILURE),2);
		
//DeadCode RDH 30Mar99 	rlistbox->AddString(RESSTRING(OPT_YES),3);
	if (Todays_Packages.pack[i].redo)
		rlistbox->AddString(RESSTRING(OPT_YES),3);
	else
		rlistbox->AddString(RESSTRING(OPT_NO),3);

}
void	CMResult::FillListBox(CRListBox* rlistbox)
{
	int i=0;
	while	(		(Todays_Packages.pack[i][0][0].uid)
				&&	(i<Profile::MAX_PACKS)
			)
	{
		FillProfileRow(rlistbox,i);
		i++;
	}

}

void CMResult::Redraw()
{
	RDialog* parent=(RDialog*)GetParent();
//	parent->SetMaxSize(CRect(0,0,450,350));
	
	CRListBox* rlistbox;
	CString string;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(160);
	rlistbox->AddColumn(66);
	rlistbox->AddColumn(66);
	rlistbox->AddColumn(25);


	string.LoadString(IDS_OBJECTIVE);
	rlistbox->AddString(string,0);

	string.LoadString(IDS_TASK);
	rlistbox->AddString(string,1);

	string.LoadString(IDS_RESULT);
	rlistbox->AddString(string,2);

	string.LoadString(IDS_REDO);
	rlistbox->AddString(string,3);

	FillListBox(rlistbox);
	

}
BOOL CMResult::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRButton*	but = GETDLGITEM(IDC_REPEAT);
	if  (	(		(RFullPanelDial::incomms)
				&&	(_DPlay.UIPlayerType!=PLAYER_HOST)
			)
			||
			((Miss_Man.currcampaignnum != MissMan::SO51_CAMPAIGN))
		)
	{
		but->SetForeColor(RGB(80,80,80));
		but->SetDisabled(true);
	}else
	{
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
	}
		

	Redraw();
	if (Todays_Packages.pack[0][0][0].uid)
		currhilight = 0;
	else
		currhilight = -1;

	ResetHiLight();
	OnClickedDebrief(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CMResult, CDialog)
    //{{AFX_EVENTSINK_MAP(CMResult)
	ON_EVENT(CMResult, IDC_NEXTPERIOD, 1 /* Clicked */, OnClickedNextperiod, VTS_NONE)
	ON_EVENT(CMResult, IDC_REPEAT, 1 /* Clicked */, OnClickedRepeat, VTS_NONE)
	ON_EVENT(CMResult, IDC_PROFILE, 1 /* Clicked */, OnClickedProfile, VTS_NONE)
	ON_EVENT(CMResult, IDC_DEBRIEF, 1 /* Clicked */, OnClickedDebrief, VTS_NONE)
	ON_EVENT(CMResult, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMResult::OnClickedNextperiod() 
{
#ifndef	MIG_DEMO_VER
	CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
	pmainwnd->m_toolbar5.OnClickedNextPeriod(); 
#endif
}

void CMResult::OnClickedRepeat() 
{
	if (Todays_Packages.pack[currhilight].redo)
		Todays_Packages.pack[currhilight].redo = false;
	else
		Todays_Packages.pack[currhilight].redo = true;
	Redraw();
	ResetHiLight();
	
}

void CMResult::OnClickedProfile() 
{
#ifndef	MIG_DEMO_VER
	if (currhilight>=0)
	{
		int row = currhilight;
		if (!LoggedChild(row+1))		//1 is for debrief
		{
	
			CProfile* p;
			LogChild(row+1,
			MakeTopDialog(CRect(50+65*row,450-40*row,0,0),
					DialBox(FIL_MAP_PROFILE,p=new CProfile(false, row))//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
						));
		}
		else
			LoggedChild(row+1)->BringWindowToTop();
	}
#endif
}	


void CMResult::OnClickedDebrief() 
{
#ifndef	MIG_DEMO_VER
	if (LoggedChild(0))
	{
		CloseLoggedChildren();
	}
	RDialog* d =MakeTopDialog(
		//CRect(50,50,0,0),
		Place(POSN_CENTRE,POSN_CENTRE,0,0),
								DialBox(FIL_MAP_PROFILE/*IDB_GENERALS*/,new CDeBrief(currhilight))//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							);	
	LogChild(0,d);
#endif
}
void CMResult::ResetHiLight()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);

	if (currhilight >= 0)
		rlistbox->SetHilightRow(currhilight+1);


}
void CMResult::OnSelectRlistboxctrl1(long row, long column) 
{
	currhilight = row-1;
	ResetHiLight();
	
}
void CMResult::EndDialog(int v)
{
	CloseLoggedChildren();
	CDialog::EndDialog(v);


}
