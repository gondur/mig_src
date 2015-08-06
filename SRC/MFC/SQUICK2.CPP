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

// SQuick2.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SQuick2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQuick2 dialog


CSQuick2::CSQuick2(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSQuick2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSQuick2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSQuick2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQuick2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_SMISSIONTITLE,m_IDC_SMISSIONTITLE);
	DDX_Control(pDX,IDC_SOBJECTIVETITLE,m_IDC_SOBJECTIVETITLE);
	DDX_Control(pDX,IDC_SOBJECTIVESTATUS,m_IDC_SOBJECTIVESTATUS);
	DDX_Control(pDX,IDC_SMISSIONRATING,m_IDC_SMISSIONRATING);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSQuick2, CDialog)
	//{{AFX_MSG_MAP(CSQuick2)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQuick2 message handlers

BOOL CSQuick2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (_DPlay.PlayerCreated)
	{
		_DPlay.SendInDebriefMessage();
		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_DEBRIEF;
	}
	Debrief_Timer=SetTimer(TIMER_DEBRIEF,0,NULL);

	
	CRStatic*   s=GETDLGITEM(IDC_SMISSIONTITLE);
	if (CSQuick1::currquickmiss==-1)
		s->SetString(RESSTRING(SINGLEPLAYER1));
	else
		s->SetString(LoadResString(CSQuick1::quickmissions[CSQuick1::currquickmiss].missionname));
	s=GETDLGITEM(IDC_SOBJECTIVETITLE);
	s->SetString(GetTargName(CSQuick1::quickdef.target));

	//clear them out, not used										  //RDH 15/06/99
 	s=GETDLGITEM(IDC_SMISSIONRATING);
	s->SetString("");
	s=GETDLGITEM(IDC_RSTATICCTRL4);
	s->SetString("");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSQuick2::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(Debrief_Timer);
	
}

void CSQuick2::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==Debrief_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	
	CDialog::OnTimer(nIDEvent);
}
