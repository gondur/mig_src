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

// ListBx.cpp : implementation file
//
// THIS IS THE COMBO BOX LIST BOX!!!
//

#include "stdafx.h"
#include "RCombo.h"
#include "ListBx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CListBx dialog


CListBx::CListBx(CWnd* pParent /*=NULL*/)
	: CDialog(CListBx::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListBx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CListBx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListBx)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListBx, CDialog)
	//{{AFX_MSG_MAP(CListBx)
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_PLAYSOUND, OnPlaySound)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBx message handlers

void CListBx::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
//	this->ShowWindow(SW_HIDE);	
}

BOOL CListBx::OnEraseBkgnd(CDC* pDC) 
{	
	return TRUE;
}

void CListBx::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	if (nState==WA_INACTIVE)
		ShowWindow(SW_HIDE);
	CDialog::OnActivate(nState, pWndOther, bMinimized);
}

BEGIN_EVENTSINK_MAP(CListBx, CDialog)
    //{{AFX_EVENTSINK_MAP(CListBx)
	ON_EVENT(CListBx, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CListBx::OnSelectRlistboxctrl1(long row, long column) 
{
	CRListBox* rlistbox=(CRListBox*)GetDlgItem(IDC_RLISTBOXCTRL1);
	char* pstring;
	pstring=(char*)rlistbox->GetString(row,column);
	ShowWindow(SW_HIDE);
	m_pCombo->SetWindowText(pstring);
	rlistbox->SelectRecentlyFired();								  //JIM 15/06/99
}
afx_msg void CListBx::OnPlaySound(int filenum)
{
	RDialog::OnPlaySound(FIL_SFX_OFFICE_BOOKCLOSE3);	//DRAW_CLOSE!! //RDH 13/04/99
	
}
