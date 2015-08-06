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

// Supply.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Supply.h"
#include "RCombo.h"
#include "rlistbox.h"
#include "dossier.h"
#include "general.h"
#include "damage.h"
#include "notes.h"
#include "Author.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSupply dialog


CSupply::CSupply(int index, CWnd* pParent /*=NULL*/)
	: RowanDialog(CSupply::IDD, pParent)
{

	sortindex = 0;
	currrow = -1;	
	panel = index;
	//{{AFX_DATA_INIT(CSupply)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSupply::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSupply)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_SORTCOMBO,m_IDC_SORTCOMBO);
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_AUTHORISE,m_IDC_AUTHORISE);
	DDX_Control(pDX,IDC_DOSSIER,m_IDC_DOSSIER);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSupply, CDialog)
	//{{AFX_MSG_MAP(CSupply)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSupply::AddSupplyMission(int j, SupplyNode*  currnode)
{
	for (int i = (MAX_TARGETS - 1); i > j ; i--)
	{
		target[i] = target[i - 1];
	}	
	target[i].activity = currnode->currentstores;
	target[i].capacity = currnode->maxstorestonnes;
	target[i].target = currnode->associated_item;
	target[i].status = 0;
	target[i].supplyline = currnode->supplyline;
	num_targets++;
	if (num_targets >= MAX_TARGETS)
		num_targets = MAX_TARGETS  - 1;
}

void CSupply::SortSupplyNodes()
{
	SupplyNode* currnode;
	currnode = SupplyTree::FirstNode;
	while (currnode->type != LASTONE)
	{
		{
			for (int j = 0; j <= num_targets; j++)
				if 	(		(	(sortindex == 0) &&	(target[j].supplyline != &SupplyTree::EastRoute) &&	(currnode->supplyline == &SupplyTree::EastRoute))
					||	(	(sortindex == 1) &&	(target[j].supplyline != &SupplyTree::CentralRoute)&&	(currnode->supplyline == &SupplyTree::CentralRoute))
					||	(	(sortindex == 2) &&	(target[j].supplyline != &SupplyTree::WestRoute)&&	(currnode->supplyline == &SupplyTree::WestRoute))
					||	(	(sortindex == 3) &&	(currnode->currentstores > target[j].status))
					||	(	(sortindex == 4) &&	(currnode->currentstores   > target[j].activity))
					||	(	(sortindex == 5) &&	(currnode->maxstorestonnes > target[j].capacity))

				)
			{
				int uidband=Persons2::getbandfromUID(currnode->associated_item);
				if  (		(uidband != BlueBoatBAND)
						&&	(uidband != BlueMilitaryBAND)
					)
					AddSupplyMission(j,currnode);
				break;
			}
		}
			
		currnode = currnode->next;
	};

}
void CSupply::AddChokeMission(int j, SupplyRoute*  currroute)
{
	for (char i = (MAX_TARGETS - 1); i > j ; i--)
	{
		target[i] = target[i - 1];
	}
	target[i].activity = currroute->storeslaunched;
	target[i].capacity = currroute->maxcapacitysummer;
	target[i].target = currroute->associated_brdg;
	target[i].status = 0;
	target[i].supplyline = currroute->supplier->supplyline;

	num_targets++;
	if (num_targets >= MAX_TARGETS)
		num_targets = MAX_TARGETS  - 1;

}

void CSupply::SortChokes()
{
	SupplyRoute* currroute;
	currroute = SupplyTree::FirstRoute;
	while (currroute->status != SR_LASTONE)
	{
		if (currroute->associated_brdg != NULL)
		{
			for (char j = 0; j <= num_targets; j++)
				if 	(		(	(sortindex == 0) &&	(target[j].supplyline != &SupplyTree::EastRoute) &&	(currroute->supplier->supplyline == &SupplyTree::EastRoute))
					||	(	(sortindex == 1) &&	(target[j].supplyline != &SupplyTree::CentralRoute)&&	(currroute->supplier->supplyline == &SupplyTree::CentralRoute))
					||	(	(sortindex == 2) &&	(target[j].supplyline != &SupplyTree::WestRoute)&&	(currroute->supplier->supplyline == &SupplyTree::WestRoute))
					||	(	(sortindex == 3) &&	(currroute->storeslaunched  > target[j].status))
					||	(	(sortindex == 4) &&	(currroute->storeslaunched   > target[j].activity))
					||	(	(sortindex == 5) &&	(currroute->maxcapacitysummer > target[j].capacity))

				)
				{
					AddChokeMission(j,currroute);
					break;
				}
		}
		currroute = currroute->next;
	};

}
void CSupply::AddTrafficMission(int j, SupplyRoute*  currroute)
{
	for (char i = (MAX_TARGETS - 1); i > j ; i--)
	{
		target[i] = target[i - 1];
	}
	target[i].activity = currroute->storeslaunched;
	target[i].capacity = currroute->maxcapacitysummer;
	target[i].target = currroute->redsupplyUID;						  //RDH 17/03/99
	target[i].status = 0;
	target[i].supplyline = currroute->supplier->supplyline;

	num_targets++;
	if (num_targets >= MAX_TARGETS)
		num_targets = MAX_TARGETS  - 1;

}

void CSupply::SortTraffic()
{
		SupplyRoute* currroute;
	currroute = SupplyTree::FirstRoute;
	while (currroute->status != SR_LASTONE)
	{
		{
			for (char j = 0; j <= num_targets; j++)
				if 	(		(	(sortindex == 0) &&	(target[j].supplyline != &SupplyTree::EastRoute) &&	(currroute->supplier->supplyline == &SupplyTree::EastRoute) && (currroute->redsupplyUID))
					||	(	(sortindex == 1) &&	(target[j].supplyline != &SupplyTree::CentralRoute)&&	(currroute->supplier->supplyline == &SupplyTree::CentralRoute)&& (currroute->redsupplyUID))
					||	(	(sortindex == 2) &&	(target[j].supplyline != &SupplyTree::WestRoute)&&	(currroute->supplier->supplyline == &SupplyTree::WestRoute)&& (currroute->redsupplyUID))
					||	(	(sortindex == 3) &&	(currroute->storeslaunched  > target[j].status)&& (currroute->redsupplyUID))
					||	(	(sortindex == 4) &&	(currroute->storeslaunched   > target[j].activity)&& (currroute->redsupplyUID))
					||	(	(sortindex == 5) &&	(currroute->maxcapacitysummer > target[j].capacity)&& (currroute->redsupplyUID))

				)
				{
					AddTrafficMission(j,currroute);
					break;
				}
		}
		currroute = currroute->next;
	};

}
void CSupply::AddAirfieldsMission(int j, int af, int score)
{
		for (char i = (MAX_TARGETS - 1); i > j ; i--)
	{
		target[i] = target[i - 1];
	}
		//this is repeating previous work 							  //RDH 19/06/99
	target[i].activity = 0;
	if (SupplyTree::airfieldinfo[af].nationality==NAT_RED)
			target[i].activity = SupplyTree::airfieldinfo[af].activeac;
	target[i].capacity = (1 + (int)(SupplyTree::airfieldinfo[af].type)) *  SupplyTree::airfieldinfo[af].capacity;
	target[i].target = SupplyTree::airfieldinfo[af].airfield;
	target[i].status = 0;
	target[i].supplyline = SupplyTree::airfieldinfo[af].northnodes[0]->supplyline;

	num_targets++;
	if (num_targets >= MAX_TARGETS)
		num_targets = MAX_TARGETS  - 1;

}
void CSupply::SortAirfields()
{
	for (int i = 0; i < SupplyTree::AIRFIELDSINWORLD; i++)
	{
		int score = 0;
		if (sortindex == 4)
		{
			if (SupplyTree::airfieldinfo[i].nationality==NAT_RED)
				score=SupplyTree::airfieldinfo[i].activeac;
		}else
			score =   (1 + (int)(SupplyTree::airfieldinfo[i].type)) *  SupplyTree::airfieldinfo[i].capacity;
		for (char j = 0; j <= num_targets; j++)
		{

			if 	(	(		(	(sortindex == 0) &&	(target[j].supplyline != &SupplyTree::EastRoute) &&	(SupplyTree::airfieldinfo[i].northnodes[0]->supplyline == &SupplyTree::EastRoute))
					||	(	(sortindex == 1) &&	(target[j].supplyline != &SupplyTree::CentralRoute)&&	(SupplyTree::airfieldinfo[i].northnodes[0]->supplyline == &SupplyTree::CentralRoute))
					||	(	(sortindex == 2) &&	(target[j].supplyline != &SupplyTree::WestRoute)&&	(SupplyTree::airfieldinfo[i].northnodes[0]->supplyline == &SupplyTree::WestRoute))
					||	(	(sortindex == 3) &&	(score  > target[j].status))
					||	(	(sortindex == 4) &&	(score   > target[j].activity))
					||	(	(sortindex == 5) &&	(score > target[j].capacity))

					)
					&&	 (SupplyTree::airfieldinfo[i].nationality != NAT_BLUE)
				)
			{
				AddAirfieldsMission(j,i, score);
				break;
			}
		}

	}

}
void CSupply::AddArmyMission(int j, SupplyNode*  currnode)
{
}
void CSupply::SortArmy()
{
}
void CSupply::SortIntell()
{
	for (int j = 0; j < MAX_TARGETS; j++)
	{
		target[j].activity = -1;
		target[j].capacity = -1;
		target[j].status = -1;
		target[j].supplyline = NULL;
		target[j].target = UID_NULL;

	}
	num_targets = 0;

	switch	(panel)
	{
		case SupplyTree::I_SUPPLY:
		{
			SortSupplyNodes();
			break;
		}
		case SupplyTree::I_CHOKE:
		{
			SortChokes();
			break;
		}
		case SupplyTree::I_TRAFFIC:
		{
			SortTraffic();
			break;
		}
		case  SupplyTree::I_AIRFIELDS:
		{
			SortAirfields();
			break;
		}
		case SupplyTree::I_ARMY:
		{
			SortArmy();
			break;
		}
	}
}
void	CSupply::ReDrawButtons()
{
	CRButton*	dosbut = GETDLGITEM(IDC_DOSSIER);
	CRButton*	authbut = GETDLGITEM(IDC_AUTHORISE);
	if (currrow != -1)
	{
		dosbut->SetForeColor(RGB(255,255,0));
		dosbut->SetDisabled(false);
		int	pack=Todays_Packages.FindPackage();
		if (pack>=0)
		{
			authbut->SetForeColor(RGB(255,255,0));
			authbut->SetDisabled(false);
		}else
		{
			authbut->SetForeColor(RGB(80,80,80));
			authbut->SetDisabled(true);
		}

	}
	else
	{
		dosbut->SetForeColor(RGB(80,80,80));
		dosbut->SetDisabled(true);
		authbut->SetForeColor(RGB(80,80,80));
		authbut->SetDisabled(true);
	}

}
void	CSupply::ReDraw()
{
	int capacity[5] = {(STORES_MAXSUPPLY-250), (MAJ_TRAINSPERDAY)*STORES_TRAIN,  
						(MAJ_TRAINSPERDAY)*STORES_TRAIN, 20, 200};


	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(TARGETFIELDWIDTH+56);
//	rlistbox->AddColumn(50);
	rlistbox->AddColumn(64);
	rlistbox->AddColumn(70);
	rlistbox->AddColumn(70);

	rlistbox->AddString(RESSTRING(OBJECTIVE),0);
	rlistbox->AddString(RESSTRING(MSR),1);
//	rlistbox->AddString(RESSTRING(STATUS),2);
	rlistbox->AddString(RESSTRING(ACTIVITY),2);
	rlistbox->AddString(RESSTRING(CAPACITY),3);

	for (int j = 0; j < num_targets; j++)
	{
		if (target[j].target != UID_NULL)
		{//display nothing if there is not a target
				rlistbox->AddString(GetTargName(target[j].target), 0);
			if 	(target[j].supplyline == &SupplyTree::EastRoute)
				rlistbox->AddString(RESSTRING(L_MSR_EAST), 1);
			else if (target[j].supplyline == &SupplyTree::CentralRoute)
				rlistbox->AddString(RESSTRING(MSR_CENTRAL), 1);
			else if (target[j].supplyline == &SupplyTree::WestRoute)
				rlistbox->AddString(RESSTRING(MSR_WEST), 1);

			int step = capacity[panel]/4;
			int mag = target[j].activity/step;
			if (mag > 4)
				mag = 4;
			rlistbox->AddString(RESLIST(VERYLOW,mag),2);

			mag = target[j].capacity/step;
			if (mag > 4)
				mag = 4;
			rlistbox->AddString(RESLIST(VERYLOW,mag),3);
		}
	}


	   
}
/////////////////////////////////////////////////////////////////////////////
// CSupply message handlers

BOOL CSupply::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRCombo* combo;
	CString string;

	combo=GETDLGITEM(IDC_SORTCOMBO);
	combo->RESCOMBO(MSREAST,5)->SetIndex(sortindex);
	
	SortIntell();
	ReDraw();
	ReDrawButtons();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CSupply, CDialog)
    //{{AFX_EVENTSINK_MAP(CSupply)
	ON_EVENT(CSupply, IDC_DOSSIER, 1 /* Clicked */, OnClickedDossier, VTS_NONE)
	ON_EVENT(CSupply, IDC_SORTCOMBO, 1 /* TextChanged */, OnTextChangedSortcombo, VTS_BSTR)
	ON_EVENT(CSupply, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(CSupply, IDC_AUTHORISE, 1 /* Clicked */, OnClickedAuthorise, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSupply::OnClickedDossier() 
{
	if  (		(currrow != -1)
			&&	(target[currrow].target != UID_NULL)
		)
	{
		m_pView->ZoomToUID(target[currrow].target,m_pView->m_zoom);
		m_pView->m_mapdlg.ResetIcon(target[currrow].target);
		MainToolBar().OpenDossier(target[currrow].target);
//		CTargetDossier::MakeSheet(CRect(180,400,0,0),target[currrow].target);
		OnOK();

	}
}

void CSupply::OnTextChangedSortcombo(LPCTSTR text) 
{

  	CRCombo* combo;
	combo=GETDLGITEM(IDC_SORTCOMBO);
	sortindex = combo->GetIndex();
	if (sortindex > 2)
		sortindex++;
	SortIntell();
	ReDraw();
	ReDrawButtons();
		 
}

void CSupply::OnSelectRlistboxctrl1(long row, long column) 
{
	if (row!=0)
		currrow=row-1;	
	ReDrawButtons();
}

void CSupply::OnClickedAuthorise() 
{
	if  (		(currrow != -1)
			&&	(target[currrow].target != UID_NULL)
		)
	{
		MainToolBar().OpenLoadProfile(target[currrow].target);		  //rdh 29/04/99

//		int	pack=Todays_Packages.NewPackage(target[currrow].target);
//		if (pack>=0)
//		{
//			m_pView->ZoomToUID(target[currrow].target,m_pView->m_zoom);
//			m_pView->m_mapdlg.ResetIcon(target[currrow].target);
//			CMissionFolder::Make();
//			CMissionFolder::OpenOneProfile(pack);
//		}

		OnOK();

	}
	
}

void CSupply::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}
