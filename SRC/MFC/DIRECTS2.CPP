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

// Directs2.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Comit_e.h"
#include "Directs2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CDirects2 dialog


CDirects2::CDirects2(int line,CWnd* pParent /*=NULL*/)
	: RowanDialog(CDirects2::IDD, pParent)
{
	linenum=line;
	CComit_e::This->directivelines[linenum] = this;

	//{{AFX_DATA_INIT(CDirects2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDirects2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirects2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_TARGETS,m_IDC_TARGETS);
	DDX_Control(pDX,IDC_MISSIONS,m_IDC_MISSIONS);
	DDX_Control(pDX,IDC_COMBO_STRIKEAC,m_IDC_COMBO_STRIKEAC);
	DDX_Control(pDX,IDC_COMBO_FIGHTERAC,m_IDC_COMBO_FIGHTERAC);
	DDX_Control(pDX,IDC_DIRECTIVEBUTTON,m_IDC_DIRECTIVEBUTTON);
	DDX_Control(pDX,IDC_BLANK2,m_IDC_BLANK2);
	DDX_Control(pDX,IDC_RESTING,m_IDC_RESTING);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirects2, CDialog)
	//{{AFX_MSG_MAP(CDirects2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//CComit_e::Directive	CComit_e::directives[MAXDIRECTIVES];
//WHEN YOU DECLARE A STATIC YOU HAVE TO DECLARE AN INSTANCE!!!!


/////////////////////////////////////////////////////////////////////////////
// CDirects2 message handlers

BOOL CDirects2::OnInitDialog() 
{
	Redraw();	
	CREdtBt* b;

	b=GETDLGITEM(IDC_DIRECTIVEBUTTON);
	if (CComit_e::This->dir_ctrl.directives[linenum].type != SupplyTree::D_RESTING)
		b->SetDragAndDropID(linenum+1);
	else
	{
		ResetStrikeAc();
		ResetFighterAc();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CDirects2, CDialog)

    //{{AFX_EVENTSINK_MAP(CDirects2)
	ON_EVENT(CDirects2, IDC_COMBO_STRIKEAC, 1 /* TextChanged */, OnTextChangedComboStrikeac, VTS_BSTR)
	ON_EVENT(CDirects2, IDC_COMBO_FIGHTERAC, 1 /* TextChanged */, OnTextChangedComboFighterac, VTS_BSTR)
	ON_EVENT(CDirects2, IDC_DIRECTIVEBUTTON, 1 /* Clicked */, OnClickedDirectivebutton, VTS_NONE)
	ON_EVENT(CDirects2, IDC_DIRECTIVEBUTTON, 2 /* CanAcceptDrop */, OnCanAcceptDropDirectivebutton, VTS_I4 VTS_PBOOL)
	ON_EVENT(CDirects2, IDC_DIRECTIVEBUTTON, 3 /* DroppedOn */, OnDroppedOnDirectivebutton, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDirects2::Redraw()
{
		char buffer[10];

	CDialog::OnInitDialog();
	CRCombo* combo;
	CREdtBt* b;
	b=GETDLGITEM(IDC_DIRECTIVEBUTTON);
	CRStatic*   s=GETDLGITEM(IDC_RESTING);

	
	int index;
	int string = IDS_L_AIRSUP + CComit_e::This->dir_ctrl.directives[linenum].type;
	if (CComit_e::This->dir_ctrl.directives[linenum].type != SupplyTree::D_RESTING)
	{
		b->ShowWindow(SW_SHOW);
		s->ShowWindow(SW_HIDE);
		b->SetCaption(LoadResString(string));
	}else
	{
		b->ShowWindow(SW_HIDE);
		s->ShowWindow(SW_SHOW);
		s->SetString(LoadResString(string));
	}
	int combosteps;
	combo=GETDLGITEM(IDC_COMBO_STRIKEAC);
	s=GETDLGITEM(IDC_BLANK2);
	if (CComit_e::This->dir_ctrl.directives[linenum].type == SupplyTree::D_AIRSUPERIORITY)
	{
		s->ShowWindow(SW_SHOW);
		combo->ShowWindow(SW_HIDE);
	}else
	{
		combo->ShowWindow(SW_SHOW);
		s->ShowWindow(SW_HIDE);
		combosteps = (CComit_e::This->dir_ctrl.TotalStrikeAc/4)+1;
		if ((combosteps*4-1) < CComit_e::This->dir_ctrl.directives[linenum].strikeac)
			index = combosteps-1;
		else
			index = CComit_e::This->dir_ctrl.directives[linenum].strikeac/4;
		combo->Clear()->MakeNumList(combosteps,0,4)->SetIndex(index);
	}
	combo=GETDLGITEM(IDC_COMBO_FIGHTERAC);
	combosteps = (CComit_e::This->dir_ctrl.TotalFighterAC/4)+1;
	if ((combosteps*4-1) < CComit_e::This->dir_ctrl.directives[linenum].fighterac)
		index = combosteps-1;
	else
		index = CComit_e::This->dir_ctrl.directives[linenum].fighterac/4;
 	combo->Clear()->MakeNumList(combosteps,0,4)->SetIndex(index);


	if (CComit_e::This->dir_ctrl.directives[linenum].type != SupplyTree::D_RESTING)
	{
	 	int x = CComit_e::This->dir_ctrl.directives[linenum].targets;
		_itoa(x,buffer,10);
		CRStatic*   s=GETDLGITEM(IDC_TARGETS);
		s->SetString(buffer);
		x = CComit_e::This->dir_ctrl.directives[linenum].missionsset;
		_itoa(x,buffer,10);
		s=GETDLGITEM(IDC_MISSIONS);
		s->SetString(buffer);
	}else
	{
		CRStatic*   s=GETDLGITEM(IDC_TARGETS);
		s->ShowWindow(SW_HIDE);
		s=GETDLGITEM(IDC_MISSIONS);
		s->ShowWindow(SW_HIDE);

	}

}
void CDirects2::ResetStrikeAc()
{
	SByte i,r;
	int resting = 0;

	int onduty = 0;
	for (i = 0; i < MAXDIRECTIVES; i++)
		if (CComit_e::This->dir_ctrl.directives[i].type == SupplyTree::D_RESTING)
			r = i;
		else
			onduty += CComit_e::This->dir_ctrl.directives[i].strikeac;

	if (onduty <= CComit_e::This->dir_ctrl.TotalStrikeAc )
		CComit_e::This->dir_ctrl.directives[r].strikeac = CComit_e::This->dir_ctrl.TotalStrikeAc  - onduty;
	else
	{
		int striketoalloc = CComit_e::This->dir_ctrl.TotalStrikeAc; 
		CComit_e::This->dir_ctrl.directives[r].strikeac = 0;
		for (i = (MAXDIRECTIVES - 1); ((i > -1) && (onduty > striketoalloc)); i--)
		{
			onduty -= CComit_e::This->dir_ctrl.directives[i].strikeac;
			CComit_e::This->dir_ctrl.directives[i].strikeac = 0;
			if (onduty < striketoalloc )
			{
				CComit_e::This->dir_ctrl.directives[i].strikeac = striketoalloc  - onduty;
				striketoalloc -= CComit_e::This->dir_ctrl.directives[i].strikeac;
//				onduty = CComit_e::This->dir_ctrl.TotalStrikeAc ;
			}
		}
	}
}
void CDirects2::OnTextChangedComboStrikeac(LPCTSTR text) 
{
  	CRCombo* combo;
	combo=GETDLGITEM(IDC_COMBO_STRIKEAC);
	CComit_e::This->dir_ctrl.directives[linenum].strikeac = 4 * combo->GetIndex();	

	ResetStrikeAc();
	CComit_e::This->RedrawAll();
	
}
void CDirects2::ResetFighterAc()
{
	SByte i,r;
	int resting = 0;
	int onduty = 0;

		for (i = 0; i < MAXDIRECTIVES; i++)
		if (CComit_e::This->dir_ctrl.directives[i].type == SupplyTree::D_RESTING)
			r = i;
		else
			onduty += CComit_e::This->dir_ctrl.directives[i].fighterac;

	if (onduty <= CComit_e::This->dir_ctrl.TotalFighterAC)
		CComit_e::This->dir_ctrl.directives[r].fighterac = CComit_e::This->dir_ctrl.TotalFighterAC - onduty;
	else
	{
		int fightertoalloc = CComit_e::This->dir_ctrl.TotalFighterAC; 

		CComit_e::This->dir_ctrl.directives[r].fighterac = 0;
		for (i = (MAXDIRECTIVES - 1); ((i > -1) && (onduty > fightertoalloc)); i--)
		{
			onduty -= CComit_e::This->dir_ctrl.directives[i].fighterac;
			CComit_e::This->dir_ctrl.directives[i].fighterac = 0;
			if (onduty < fightertoalloc)
			{
				CComit_e::This->dir_ctrl.directives[i].fighterac = fightertoalloc - onduty;
				fightertoalloc -= CComit_e::This->dir_ctrl.directives[i].fighterac;
//				onduty = CComit_e::This->dir_ctrl.TotalFighterAC;
			}
		}
	}

}
void CDirects2::OnTextChangedComboFighterac(LPCTSTR text) 
{
	CRCombo* combo;
	combo=GETDLGITEM(IDC_COMBO_FIGHTERAC);
	CComit_e::This->dir_ctrl.directives[linenum].fighterac = 4 * combo->GetIndex();	

	ResetFighterAc();
  	CComit_e::This->RedrawAll();
		
}

void CDirects2::OnClickedDirectivebutton() 
{
	if (CComit_e::This->dir_ctrl.directives[linenum].type != SupplyTree::D_RESTING)
	{
		if (LoggedChild(0))
		{
 			CRTabs* tab=(CRTabs*)LoggedChild(0)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
			tab->SelectTab(CComit_e::This->dir_ctrl.directives[linenum].type);
			//delete tab;
		
		}else
		{
			typedef	HideEdgeControl	EDGE; 
			RDialog* d=MakeTopDialog(CRect(500,450,0,0),
				DialList(DialBox(FIL_NULL,new CCamplist,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									HTabBox(FIL_NULL,IdList(IDS_AIRSUP,IDS_CHOKE_L, IDS_SUPPLY,IDS_AIRFIELDS,IDS_RAIL, IDS_ROAD,IDS_ARMY),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
		  								DialBox(FIL_MAP_MIGCAP,new CSelectionResults(SupplyTree::D_AIRSUPERIORITY)),
		  								DialBox(FIL_MAP_CHOKEPOINTS,new CSelectionResults(SupplyTree::D_CHOKE)), 
										DialBox(FIL_MAP_SUPPLY,new CSelectionResults(SupplyTree::D_SUPPLY)),
										DialBox(FIL_MAP_AIRFIELD,new CSelectionResults(SupplyTree::D_AIRFIELDS)),
		  								DialBox(FIL_MAP_TRAFFIC,new CSelectionResults( SupplyTree::D_RAIL)),
										DialBox(FIL_MAP_TRAFFIC,new CSelectionResults(SupplyTree::D_ROAD)),
		  								DialBox(FIL_MAP_ARMY,new CSelectionResults(SupplyTree::D_ARMY))
		  								
		  								
									)														  							

					  			)
							 );	
			LogChild(0,d);
			CRTabs* tab=(CRTabs*)d->fchild->GetDlgItem(IDJ_TABCTRL);
			tab->SelectTab(CComit_e::This->dir_ctrl.directives[linenum].type);
			//delete tab;
		}
	}	
}

void CDirects2::OnCanAcceptDropDirectivebutton(long sourcedropID, BOOL FAR* pReply) 
{
	sourcedropID--;
	if (		(CComit_e::This->dir_ctrl.directives[linenum].type != SupplyTree::D_RESTING)
			&&	(sourcedropID != linenum)
		)
		*pReply= true;
	else
		*pReply= false;
	
}

void CDirects2::OnDroppedOnDirectivebutton(long sourcedropID) 
{
	Directive tempd;
	sourcedropID--;
	char i ;
	
	tempd = CComit_e::This->dir_ctrl.directives[sourcedropID];
	if (sourcedropID > linenum)
	{
		for (i = sourcedropID; i > (linenum); i--)
			CComit_e::This->dir_ctrl.directives[i] = CComit_e::This->dir_ctrl.directives[i-1];
		CComit_e::This->dir_ctrl.directives[linenum] = tempd;
	}else
	{
		for (i = sourcedropID; i < (linenum); i++)
			CComit_e::This->dir_ctrl.directives[i] = CComit_e::This->dir_ctrl.directives[i+1];
		CComit_e::This->dir_ctrl.directives[linenum] = tempd;
	}
	CComit_e::This->RedrawAll();

	
}
