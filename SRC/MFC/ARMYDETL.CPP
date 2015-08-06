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

// ArmyDetl.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "ArmyDetl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CArmyDetails dialog


CArmyDetails::CArmyDetails(UniqueID uid, UniqueID forceuid, int side, CWnd* pParent /*=NULL*/)
	: RowanDialog(CArmyDetails::IDD, pParent)
{
	u = uid;
	s= side;
	forceu = forceuid;
	//{{AFX_DATA_INIT(CArmyDetails)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CArmyDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArmyDetails)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL5,m_IDC_RSTATICCTRL5);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_RSTATICCTRL8,m_IDC_RSTATICCTRL8);
	DDX_Control(pDX,IDC_RSTATICCTRL9,m_IDC_RSTATICCTRL9);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_RSTATICCTRL11,m_IDC_RSTATICCTRL11);
	DDX_Control(pDX,IDC_UN_INIT_SIZE,m_IDC_UN_INIT_SIZE);
	DDX_Control(pDX,IDC_UN_CURR_SIZE,m_IDC_UN_CURR_SIZE);
	DDX_Control(pDX,IDC_UN_MORALE,m_IDC_UN_MORALE);
	DDX_Control(pDX,IDC_RED_INIT_SIZE,m_IDC_RED_INIT_SIZE);
	DDX_Control(pDX,IDC_RED_CURR_SIZE,m_IDC_RED_CURR_SIZE);
	DDX_Control(pDX,IDC_RED_MORALE,m_IDC_RED_MORALE);
	DDX_Control(pDX,IDC_FRONTLINE,m_IDC_FRONTLINE);
	DDX_Control(pDX,IDC_BATTLEAREA,m_IDC_BATTLEAREA);
	DDX_Control(pDX,IDC_SITUATION,m_IDC_SITUATION);
	DDX_Control(pDX,IDC_FAC_CALLSIGN,m_IDC_FAC_CALLSIGN);
	DDX_Control(pDX,IDC_TAC_CALLSIGN,m_IDC_TAC_CALLSIGN);
	DDX_Control(pDX,IDC_RSTATICCTRL23,m_IDC_RSTATICCTRL23);
	DDX_Control(pDX,IDC_AUTHORISE	,m_IDC_AUTHORISE);
	DDX_Control(pDX,IDC_DETAILS	,m_IDC_DETAILS);
	DDX_Control(pDX,IDJ_TITLE,m_IDJ_TITLE);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArmyDetails, CDialog)
	//{{AFX_MSG_MAP(CArmyDetails)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

RDialog* CArmyDetails::MakeSheet(CRect r,UniqueID item, UniqueID force, int side)
{
return
	MakeTopDialog(r,
					DialList(DialBox(FIL_MAP_ARMY,new CArmy_dos),	//CArmy
							 DialBox(FIL_NULL,new CArmyDetails(item, force, side))
		  								)
			     );
}

/////////////////////////////////////////////////////////////////////////////
// CArmyDetails message handlers

BOOL CArmyDetails::OnInitDialog() 
{
	CDialog::OnInitDialog();

	Refresh();

	SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(u);
	if (	(	node->supplyline->initiative!=REDATTACKING
			&&	node->supplyline->initiative!=BLUEATTACKING
			)
		||	node->supplyline==&SupplyTree::EastRoute
		)
	{
		GETDLGITEM(IDC_AUTHORISE)->SetDisabled(true);
		GETDLGITEM(IDC_DETAILS)->SetDisabled(true);
	}
	else
		if (forceu)
			OnClickedDetails();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CArmyDetails, CDialog)
    //{{AFX_EVENTSINK_MAP(CArmyDetails)
	ON_EVENT(CArmyDetails, IDC_AUTHORISE, 1 /* Clicked */, OnClickedAuthorise, VTS_NONE)
	ON_EVENT(CArmyDetails, IDC_DETAILS, 1 /* Clicked */, OnClickedDetails, VTS_NONE)
	ON_EVENT(CArmyDetails, IDC_DOSSIER, 1 /* Clicked */, OnClickedDossier, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CArmyDetails::OnClickedAuthorise() 
{
		MainToolBar().OpenLoadProfile(u);
}

void CArmyDetails::OnClickedDetails() 
{
	CArmyRequests*	armysheet;
	if (LoggedChild(0))
		CloseLoggedChild(0);
 	LogChild(0,armysheet = CArmyRequests::MakeSheet(
		Place(POSN_MAX,POSN_MAX),
					u, forceu));

	armysheet->TabSelect(s);
}

void CArmyDetails::OnClickedDossier() 
{
	MainToolBar().OpenDossierNotFrontLine(u);

}

static CString	TranslateInitiative(Initiative i,NodeType type,bool iseast)
{
	if (type!=BATTLEFIELD)
	{
		if (i==REDINITIATIVE)
			return(RESSTRING(T_Retreat01_H));
		else
			return(RESSTRING(T_Advance01_H));
	}
	else
		switch (i)
		{
		case REDINITIATIVE:
		case REDATTACKING:
			if (iseast)		return(RESSTRING(L_REDINITIATIVE));
			//fall through
		case BLUEINITIATIVE:
		case BLUEATTACKING:
			if (iseast)		return(RESSTRING(BLUEINITIATIVE));	
			//fall through
			if (SupplyTree::AllFrontOnBattleNodes())
				return RESLIST(REDINITIATIVE,i);
			else
				return RESLIST(REDINITIATIVE,i) + " ("+RESSTRING(CONSOLIDATING)+")";
		break;
		case REDWON:
			return RESSTRING(T_Army01_H);
		case BLUEWON:
			return RESSTRING(T_Army06_H);
		case REDLOST:
			return RESSTRING(T_Army02_H);
		case BLUELOST:
			return RESSTRING(T_Army07_H);
		}
	return "";
}

void CArmyDetails::Refresh() 
{
	CRStatic* stat=GETDLGITEM(IDC_BATTLEAREA);
	stat->SetString(GetTargName(u));
	SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(u);
	if (!node)
	{
		stat=GETDLGITEM(IDC_FRONTLINE);
		stat->SetString("");
	}
	else
	{
		stat=GETDLGITEM(IDC_SITUATION);
		stat->SetString(TranslateInitiative(node->supplyline->initiative,node->route[0]->supplier->type,node->supplyline==&SupplyTree::EastRoute));
		stat=GETDLGITEM(IDC_FRONTLINE);
		if (node->supplyline==&SupplyTree::WestRoute)
			stat->SetString(RESSTRING(WEST));
		elseif (node->supplyline==&SupplyTree::EastRoute)
			stat->SetString(RESSTRING(EAST));
		else
			stat->SetString(RESSTRING(CENTRAL));
		stat=GETDLGITEM(IDC_FAC_CALLSIGN);
		CRStatic* stat2;
		stat2=GETDLGITEM(IDC_RSTATICCTRL5);
		if (node->supplyline->FACActive )
		{
			stat2->SetString(RESSTRING(FAC));
			stat->SetString(LoadResString(IDS_PHRASE_NL_CALLER0 -1+ node->supplyline->FACcallname));
		}
		else
		{
			stat2->SetString(RESSTRING(TAC));
			stat->SetString(LoadResString(IDS_PHRASE_NL_CALLER0 -1+ node->supplyline->TACcallname));
		}
	}
	CRButton*	but = GETDLGITEM(IDC_AUTHORISE);
	if (MMC.indebrief)												  //DAW 6/15/99
	{																  //DAW 6/15/99
		but->SetForeColor(RGB(80,80,80));							  //DAW 6/15/99
		but->SetDisabled(true);										  //DAW 6/15/99
	}																  //DAW 6/15/99
	else															  //DAW 6/15/99
	{																  //DAW 6/15/99
		int a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29;
		Todays_Packages.FlightsAvailable(-1, a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29);
		if  (a_fb <=0)
		{
			but->SetForeColor(RGB(80,80,80));
			but->SetDisabled(true);
		}
		else
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetDisabled(false);
		}
	}

}
void	CArmyDetails::RefreshData(int uid)
{
	u = (UniqueID)uid;
	Refresh();
}
