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

// Notes.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Notes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotes dialog


CNotes::CNotes(int sgt,int uid,CWnd* pParent /*=NULL*/)
	: RowanDialog(CNotes::IDD, pParent)
{
	SetProjSpecific(-1,sgt,uid);
	//{{AFX_DATA_INIT(CNotes)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNotes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNotes)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RSTATICCTRL1,m_IDC_RSTATICCTRL1);
	DDX_Control(pDX,IDC_TARGET_TITLE,m_IDC_TARGET_TITLE);
	DDX_Control(pDX,IDC_NOTES,m_IDC_NOTES);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNotes, CDialog)
	//{{AFX_MSG_MAP(CNotes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotes message handlers

BOOL CNotes::OnInitDialog() 
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

	SupplyTree::Supply2UID	nodetype;
	SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(trg,&nodetype);
	int text = IDS_NOINFO;

	stat=GETDLGITEM(IDC_NOTES);
	if (node)
	{
		switch (nodetype)
		{
			case	SupplyTree::S2U_MAIN:	
			{
				text = node->associated_itemtext;
				break;
			}
			case	SupplyTree::S2U_AF0:
			case	SupplyTree::S2U_AF1:
			case	SupplyTree::S2U_AF2:
			{
				AirFieldInfo* af=SupplyTree::FindAirfieldForItem(trg);
				if (af)
				{
					text = af->airfieldtext;
				}
			}
			break;
			case	SupplyTree::S2U_ROUTE0:
			case	SupplyTree::S2U_ROUTE1:
			case	SupplyTree::S2U_ROUTE2:
			{
				text=node->route[nodetype-SupplyTree::S2U_ROUTE0]->associated_brdgtext;	
				break;
			}
		}
		stat->SetString(LoadResString(text));
	
	}
	else
		stat->SetString(RESSTRING(NOINFO));
//	stat=GetDlgItem(IDC_NOTES);
//	stat->SetString(RESSTRING(node->notes));

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
