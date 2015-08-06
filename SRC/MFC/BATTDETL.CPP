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

// BattDetl.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "BattDetl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CBattleDetail dialog


CBattleDetail::CBattleDetail(UniqueID uid, UniqueID forceuid, int side,CWnd* pParent /*=NULL*/)
	: RowanDialog(CBattleDetail::IDD, pParent)
{
	u = uid;
	forceu = forceuid;
	tabside = side;
	//{{AFX_DATA_INIT(CBattleDetail)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBattleDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBattleDetail)
		// NOTE: the ClassWizard will add DDX and DDV calls here
		DDX_Control(pDX,IDC_RLISTBOXTOP,m_IDC_RLISTBOXTOP);
		DDX_Control(pDX,IDC_RLISTBOXBTM,m_IDC_RLISTBOXBTM);
		DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
		DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBattleDetail, CDialog)
	//{{AFX_MSG_MAP(CBattleDetail)
		ON_MESSAGE( WM_SELECTTAB, OnSelectTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void CBattleDetail::FillBtmBox()
{
		CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXBTM);
	rlistbox->Clear();
	rlistbox->AddColumn(120);
	rlistbox->AddColumn(40);
	rlistbox->AddColumn(64);
	rlistbox->AddColumn(100);

	rlistbox->AddString(RESSTRING(UNIT),0);
	rlistbox->AddString(RESSTRING(SIZE),1);
	rlistbox->AddString(RESSTRING(STATUS),2);
	rlistbox->AddString(RESSTRING(LOCATION),3);

	TeamDef* topteam = &node->supplyline->groundbattle.teamlist[teams[currrow]];
	if (teams[currrow] != -1)
	{
//DeadCode RDH 14Jun99 		CRListBox* rlistbox;
//DeadCode RDH 14Jun99 		rlistbox=GETDLGITEM(IDC_RLISTBOXBTM);
		for (int i=0;i<node->supplyline->groundbattle.usedteams;i++)
		{
			if (node->supplyline->groundbattle.teamlist[i].team!=blueforce)
			{
				TeamDef* btmteam = &node->supplyline->groundbattle.teamlist[i];
				 
				if	(		(btmteam->nextnode == topteam->node)
						||	(btmteam->node == topteam->nextnode)
						||	(btmteam->node == topteam->node)
						||	(btmteam->nextnode == topteam->nextnode)
					)
					
				{
					rlistbox->AddString(LoadResString(node->supplyline->groundbattle.teamlist[i].forcename),0);
					rlistbox->AddString(CSprintf(" %i",node->supplyline->groundbattle.teamlist[i].strength/100),1);
					rlistbox->AddString(LoadResString(IDS_L_INACTIVE + node->supplyline->groundbattle.teamlist[i].action),2);
					CString string, string2;
					string.LoadString(node->supplyline->groundbattle.teamlist[i].node->mainids);
					if (string.GetLength() > 0)
					{
						string.TrimLeft();
						string2 = string;
						string2.MakeUpper();
						string.SetAt(0, string2.GetAt(0));
	//DEADCODE RDH 03/04/99 					rlistbox->AddString(LoadResString(node->supplyline->groundbattle.teamlist[i].node->mainids),3);
						rlistbox->AddString(string,3);
					}				
				}
			}
		}
		rlistbox=GETDLGITEM(IDC_RLISTBOXTOP);
		rlistbox->SetHilightRow(currrow+1);
	}
}
void CBattleDetail::FillTopBox()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXTOP);


		int cnt = 0;
		for (int i=0;i<node->supplyline->groundbattle.usedteams;i++)
		{
			if (node->supplyline->groundbattle.teamlist[i].team==blueforce)
			{
				if (forceu == node->supplyline->groundbattle.teamlist[i].location)
					currrow = cnt; 
				teams[cnt++] = i;
				rlistbox->AddString(LoadResString(node->supplyline->groundbattle.teamlist[i].forcename),0);
				rlistbox->AddString(CSprintf(" %i",node->supplyline->groundbattle.teamlist[i].strength/100),1);
				rlistbox->AddString(LoadResString(IDS_L_INACTIVE + node->supplyline->groundbattle.teamlist[i].namedaction),2);
				CString string, string2;
				string.LoadString(node->supplyline->groundbattle.teamlist[i].node->mainids);
				if (string.GetLength() > 0)
				{
					string.TrimLeft();
					string2 = string;
					string2.MakeUpper();
					string.SetAt(0, string2.GetAt(0));

					
	//DEADCODE RDH 03/04/99 				rlistbox->AddString(LoadResString(node->supplyline->groundbattle.teamlist[i].node->mainids),3);
					rlistbox->AddString(string,3);
				}
			}


		}
		rlistbox->SetHilightRow(currrow+1);

}

/////////////////////////////////////////////////////////////////////////////
// CBattleDetail message handlers

BOOL CBattleDetail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXTOP);
	rlistbox->Clear();
	rlistbox->AddColumn(120);
	rlistbox->AddColumn(40);
	rlistbox->AddColumn(64);
	rlistbox->AddColumn(100);

	rlistbox->AddString(RESSTRING(UNIT),0);
	rlistbox->AddString(RESSTRING(SIZE),1);
	rlistbox->AddString(RESSTRING(STATUS),2);
	rlistbox->AddString(RESSTRING(LOCATION),3);


//DeadCode RDH 14Jun99 	rlistbox=GETDLGITEM(IDC_RLISTBOXBTM);
//DeadCode RDH 14Jun99 	rlistbox->Clear();
//DeadCode RDH 14Jun99 	rlistbox->AddColumn(120);
//DeadCode RDH 14Jun99 	rlistbox->AddColumn(40);
//DeadCode RDH 14Jun99 	rlistbox->AddColumn(64);
//DeadCode RDH 14Jun99 	rlistbox->AddColumn(100);
//DeadCode RDH 14Jun99 
//DeadCode RDH 14Jun99 	rlistbox->AddString(RESSTRING(UNIT),0);
//DeadCode RDH 14Jun99 	rlistbox->AddString(RESSTRING(SIZE),1);
//DeadCode RDH 14Jun99 	rlistbox->AddString(RESSTRING(STATUS),2);
//DeadCode RDH 14Jun99 	rlistbox->AddString(RESSTRING(LOCATION),3);

	
	CRStatic*   s0=GETDLGITEM(IDC_RSTATICCTRL2);
	CRStatic*   s1=GETDLGITEM(IDC_RSTATICCTRL3);
	if (tabside == 0)
	{
		s0->SetString(RESSTRING(UNFORCES));
		s1->SetString(RESSTRING(REDFORCES));
	}else
	{
		s1->SetString(RESSTRING(UNFORCES));
		s0->SetString(RESSTRING(REDFORCES));
	}
	
	for (int i=0;i<BattleStruct::MAXTEAMS;i++)
		teams[i] = -1;

	node=SupplyTree::FindSupplyNodeForItem((UniqueID)u);
	if (node)
	{
		if	(		(node->supplyline->initiative==REDATTACKING)
				==	(tabside == 0)
			)
			blueforce = TeamDef::HOME;
		else
			blueforce = TeamDef::AWAY;
		currrow = 0;
		FillTopBox();
		FillBtmBox();
	}else
		currrow = -1;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void  CBattleDetail::ParentDialClosed(RDialog*,int rv)
{
	OnOK();
}

BEGIN_EVENTSINK_MAP(CBattleDetail, CDialog)
    //{{AFX_EVENTSINK_MAP(CBattleDetail)
	ON_EVENT(CBattleDetail, IDC_RLISTBOXTOP, 1 /* Select */, OnSelectRlistboxtop, VTS_I4 VTS_I4)
	ON_EVENT(CBattleDetail, IDC_RLISTBOXBTM, 1 /* Select */, OnSelectRlistboxbtm, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CBattleDetail::OnSelectRlistboxtop(long row, long column) 
{
	// TODO: Add your control notification handler code here
	currrow = row-1;
	m_pView->m_mapdlg.ResetIcon(node->supplyline->groundbattle.teamlist[teams[currrow]].location);
	FillBtmBox();

	
}

void CBattleDetail::OnSelectRlistboxbtm(long row, long column) 
{
	CRListBox* rlistbox;

	rlistbox=GETDLGITEM(IDC_RLISTBOXBTM);
	rlistbox->SetHilightRow(-1);
	
}
void CBattleDetail::OnSelectTab()
{
  	m_pView->m_mapdlg.ResetIcon(node->supplyline->groundbattle.teamlist[teams[currrow]].location);

}
