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

// ChSquad.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "ChSquad.h"
#include "bfnumber.h"
#include "persons2.h"
#include "missman2.h"
#include "comit_e.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// ChooseSquad dialog


ChooseSquad::ChooseSquad(int pack,int wave,int group,CWnd* pParent /*=NULL*/)
	: RowanDialog(ChooseSquad::IDD, pParent)
{
	SetProjSpecific(pack,wave,group);
	//{{AFX_DATA_INIT(ChooseSquad)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT


}
int	 ChooseSquad::FlightAvail(int squad)
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
	{
		int ac;
		if (squad == Todays_Packages[packnum][wavenum][groupnum].squadron)
			ac = ag->inform;
		else
			ac = 0;

		int flightsavail= Todays_Packages.SquadACAvail(squad) - Todays_Packages.SquadACUsed(squad);
			flightsavail +=	ac;
			flightsavail = flightsavail/4;		
			
		return(flightsavail);
	}else
		return (0);

}
void ChooseSquad::FillCombo()
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
	{
		ULong flights=ag->inform;

		int maxavail=FlightAvail(Todays_Packages[packnum][wavenum][groupnum].squadron);
//		int maxavail=ULong(	Todays_Packages.SquadACAvail(Todays_Packages[packnum][wavenum][groupnum].squadron)
//							-Todays_Packages.SquadACUsed(Todays_Packages[packnum][wavenum][groupnum].squadron)
//							+flights)/4;
		flights/=4;
//		CRCombo* combo;
//		combo=GETDLGITEM(IDC_FLIGHTS);
//		if (groupnum!=0)	
//			combo->Clear()->MakeNumList(maxavail+1,0,1)->SetIndex(flights);
//		else
// 			combo->Clear()->MakeNumList(maxavail,1,1)->SetIndex(flights-1);
		CRSpinBut* spinbut;
		spinbut=GETDLGITEM(IDC_RSPINBUTCTRL1);
		if (groupnum!=0)	
			spinbut->Clear()->MakeNumList(maxavail+1,0,1)->SetIndex(flights);
		else
   			spinbut->Clear()->MakeNumList(maxavail,1,1)->SetIndex(flights-1);
	}
}

void ChooseSquad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ChooseSquad)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_TSQUAD,m_IDC_TSQUAD);
//	DDX_Control(pDX,IDC_FLIGHTS,m_IDC_FLIGHTS);
	DDX_Control(pDX,IDC_RSPINBUTCTRL1,m_IDC_RSPINBUTCTRL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ChooseSquad, CDialog)
	//{{AFX_MSG_MAP(ChooseSquad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ChooseSquad message handlers

BEGIN_EVENTSINK_MAP(ChooseSquad, CDialog)
    //{{AFX_EVENTSINK_MAP(ChooseSquad)
	ON_EVENT(ChooseSquad, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(ChooseSquad, IDC_DELETE, 1 /* Clicked */, OnClickedDelete, VTS_NONE)
	ON_EVENT(ChooseSquad, IDC_FLIGHTS, 1 /* TextChanged */, OnTextChangedFlights, VTS_BSTR)
//DEADCODE DAW 29/03/99 	ON_EVENT(ChooseSquad, IDJ_TITLE, 3 /* OK */, OnOKTitle, VTS_NONE)
//DEADCODE DAW 29/03/99 	ON_EVENT(ChooseSquad, IDJ_TITLE, 2 /* Cancel */, OnCancelTitle, VTS_NONE)
	ON_EVENT(ChooseSquad, IDC_RSPINBUTCTRL1, 1 /* TextChanged */, OnTextChangedRspinbutctrl1, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void ChooseSquad::OnSelectRlistboxctrl1(long row, long column) 
{
	// TODO: Add your control notification handler code here

	int i = row;											  //RDH 17/06/99
	i--;													  //RDH 17/06/99
	if (i == 5)
	{
		if(MMC.directives.B29avail)							  //RDH 17/06/99
			i = SQ_B29;											  //RDH 17/06/99
		else													  //RDH 17/06/99
			i = SQ_B26;											  //RDH 17/06/99
	}


	if (		(i != Todays_Packages[packnum][wavenum][groupnum].squadron)
			&&	(i >= 0)
		)
	{
//DEADCODE RDH 17/06/99 		if (row)
		{
//DEADCODE RDH 17/06/99 			row--;

			int numavail=Todays_Packages.SquadACAvail(i)
						-Todays_Packages.SquadACUsed(i);
			if (numavail>=4)
			{
				Todays_Packages[packnum][wavenum][groupnum].SetSquad(i);
				info_airgrp* a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	//			a->type=row;
				if (a->inform.Evaluate()>numavail)
				{
	//				a->inform=numavail&-4;
					Todays_Packages[packnum][wavenum][groupnum].SetFlights(numavail/4);
	//				Todays_Packages[packnum][wavenum][groupnum].numflights=numavail/4;
				}
	//			RefreshParent();

 				currrow = i + 1;
				if (currrow > 6)
					currrow = 6;

				FillCombo();
			}

		}
	}
	CRListBox* rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->SetHilightRow(currrow);

}

void ChooseSquad::OnClickedDelete() 
{
	// TODO: Add your control notification handler code here
	if (groupnum!=0)	
	{
		Todays_Packages[packnum].ClearGroup(wavenum,groupnum);
		OnOK();
	}
}

void ChooseSquad::OnTextChangedFlights(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here

	
}

BOOL ChooseSquad::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	initialsquad = Todays_Packages[packnum][wavenum][groupnum].squadron;
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
			initialac = ag->inform;

	CRListBox* rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(64);
	rlistbox->AddColumn(50);
	rlistbox->AddColumn(120);
	rlistbox->AddColumn(10);
	rlistbox->AddString(RESSTRING(SQUADRON),0);
	rlistbox->AddString(RESSTRING(TYPE),1);
	rlistbox->AddString(RESSTRING(LOCATION),2);
	rlistbox->AddString(RESSTRING(AVAILABLE),3);

	for (int i=0;i<PILOTABLE_SQUADRONS;i++)
	{
		rlistbox->AddString(RESLIST(SQ_BF_F86A,i),0);
		rlistbox->AddString(RESLIST(F86A,Persons3::Squad2Type(i)),1);
		rlistbox->AddString(GetTargName(SupplyTree::airfieldinfo[MMC.squad[i].airfieldindex].airfield),2);
		rlistbox->AddString(CSprintf("%i",FlightAvail(i)),3);
	}
//DEADCODE RDH 27/05/99 	if (Miss_Man.currcampaignnum==MissMan::SO51_CAMPAIGN)					  //JIM 01/04/99
//DEADCODE RDH 27/05/99 	{																  //JIM 01/04/99
		if (MMC.directives.B29avail)
			i = SQ_B29;
		else
			i = SQ_B26;
		rlistbox->AddString(RESLIST(SQ_BF_F86A,i),0);
		rlistbox->AddString(RESLIST(F86A,Persons3::Squad2Type(i)),1);
		rlistbox->AddString(RESSTRING(JAPAN),2);
		rlistbox->AddString(CSprintf("%i",FlightAvail(i)),3);

		if  (		(Todays_Packages[packnum][wavenum][groupnum].squadron == SQ_B26)
				||	(Todays_Packages[packnum][wavenum][groupnum].squadron == SQ_B29)
			)
			currrow = PILOTABLE_SQUADRONS+1;
		else
			currrow = Todays_Packages[packnum][wavenum][groupnum].squadron+1;
//DEADCODE RDH 27/05/99 	}																  //JIM 01/04/99
	rlistbox->SetHilightRow(currrow);
	FillCombo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ChooseSquad::OnOK() 
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
	{
		if (groupnum!=0)	
			if (ag->inform == 0)
				Todays_Packages[packnum].ClearGroup(wavenum,groupnum);
//			else
//				Todays_Packages[packnum][wavenum][groupnum].SetFlights(ag->inform/4);
//DeadCode DAW 12Nov98 				Todays_Packages[packnum][wavenum][groupnum].numflights = ag->inform/4;
	}
	Todays_Packages[packnum].RecalcRoutePositions();
	RefreshParent();
	m_pView->m_mapdlg.Invalidate();									  //RDH 19/06/99

	CDialog::OnOK();
}

void ChooseSquad::OnCancel() 
{
//DeadCode DAW 12Nov98 	Todays_Packages[packnum][wavenum][groupnum].squadron = initialsquad;
	Todays_Packages[packnum][wavenum][groupnum].SetSquad(initialsquad);
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
			//ag->inform = initialac;
			Todays_Packages[packnum][wavenum][groupnum].SetFlights(initialac/4);
	CDialog::OnCancel();
	
}
void	ChooseSquad::ParentDialClosed(RDialog*,int rv)
{
	OnCancel();
}

void ChooseSquad::OnTextChangedRspinbutctrl1(LPCTSTR text) 
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
	{
		CRSpinBut* spinbut;
		spinbut=GETDLGITEM(IDC_RSPINBUTCTRL1);
		int ac = spinbut->GetIndex();
		if (groupnum!=0)	
		{
				Todays_Packages[packnum][wavenum][groupnum].SetFlights(ac);
		}else
		{
				Todays_Packages[packnum][wavenum][groupnum].SetFlights(ac+1) ;
		}
		
	}
	
}
