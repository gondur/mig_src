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

// WaveTabs.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "WaveTabs.h"
#include "WPBut.h"
#include "WPGround.h"
#include "WPShare.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaveTabs dialog

bool CWaveTabs::m_launched=FALSE;
CWaveTabs::CWaveTabs(int pack,int wave,CWnd* pParent /*=NULL*/)
	: RowanDialog(CWaveTabs::IDD, pParent)
{
	SetProjSpecific(pack,wave);
	//{{AFX_DATA_INIT(CWaveTabs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWaveTabs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveTabs)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaveTabs, CDialog)
	//{{AFX_MSG_MAP(CWaveTabs)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_MESSAGE( WM_SELECTTAB, OnSelectTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveTabs message handlers

int CWaveTabs::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (m_launched)
	{
		BringWindowToTop();
		return -1;
	}
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_launched=TRUE;
	RDialog* parent=(RDialog*)this->GetParent();
	return 0;
}

BEGIN_EVENTSINK_MAP(CWaveTabs, CDialog)
    //{{AFX_EVENTSINK_MAP(CWaveTabs)
	ON_EVENT(CWaveTabs, IDJ_TITLE, 1 /* Clicked */, OnClickedTitle, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CWaveTabs::OnClickedTitle() 
{
	// TODO: Add your control notification handler code here
	
}


void CWaveTabs::OnOK() 
{
	CDialog::OnOK();
}

void CWaveTabs::OnDestroy() 
{
	CDialog::OnDestroy();
	if (m_ReallyDestroyed) m_launched=FALSE;
}

void	CWaveTabs::SelectTab(int group)
{		//if false show flights main tab and group second tab
		//if true show route main tab, and group+1 second tab

	// get pointer to the tab controls and invoke SelectTab
//	CRTabs* tab=(CRTabs*)fchild->GetDlgItem(IDJ_TABCTRL);
//	CWnd* currentWindow;
//	if (seewp) currentWindow=(CWnd*)tab->SelectTab(1);
//	else currentWindow=(CWnd*)tab->SelectTab(0);
//	tab=(CRTabs*)currentWindow->GetDlgItem(IDJ_TABCTRL);
//	if (seewp) tab->SelectTab(group+1);
//	else tab->SelectTab(group);

	//new version , 12/10/98
	// get pointer to the tab controls and invoke SelectTab
//		CRTabs* tab=(CRTabs*)fchild->GetDlgItem(IDJ_TABCTRL);
//		CWnd* currentWindow;
//		if (seewp) 
//		{	
//			if	(group == -1) 
//				currentWindow=(CWnd*)tab->SelectTab(1);
//			else
//				currentWindow=(CWnd*)tab->SelectTab(2);
//			 
//		}
//		else 
//			currentWindow=(CWnd*)tab->SelectTab(0);
  //
//		tab=(CRTabs*)currentWindow->GetDlgItem(IDJ_TABCTRL);
//
//		
//		if (seewp) 
//		{
//			if (group != -1)
//				tab->SelectTab(group);
//		}
//		else 
//			tab->SelectTab(group);

 		CRTabs* tab=(CRTabs*)fchild->GetDlgItem(IDJ_TABCTRL);
		CWnd* currentWindow;
		if	(group == -1) 
			currentWindow=(CWnd*)tab->SelectTab(0);
		else
			currentWindow=(CWnd*)tab->SelectTab(1);
		//delete tab;

		tab=(CRTabs*)currentWindow->GetDlgItem(IDJ_TABCTRL);
		if (group != -1)
			tab->SelectTab(group);
		//delete tab;


}

void CWaveTabs::OnSelectTab(RDialog* tab)
{
//	INT3;
}

void CWaveTabs::OnSize(UINT nType, int cx, int cy) 
{
	RDialog::OnSize(nType, cx, cy);
//DEAD	if (m_wpBut1->m_hWnd)
//DEAD	{
//DEAD		CRect rect;
//DEAD		CWnd* parent=m_wpBut1->GetParent();
//DEAD		parent->GetClientRect(rect);
//DEAD		CRect rect2;
//DEAD		m_wpBut1->GetClientRect(rect2);
//DEAD		CRect rect3;
//DEAD/*		rect3=CRect(0,rect.bottom-rect2.bottom,rect.right,rect.bottom);
//DEAD		m_wpBut1->MoveWindow(rect3);
//DEAD		m_wpBut2->MoveWindow(rect3);
//DEAD		m_wpBut3->MoveWindow(rect3);
//DEAD		m_wpBut4->MoveWindow(rect3);
//DEAD		rect3=CRect(0,0,rect.right,rect.bottom-rect2.bottom);
//DEAD		m_wp1->MoveWindow(rect3);
//DEAD		m_wp2->MoveWindow(rect3);
//DEAD		m_wp3->MoveWindow(rect3);
//DEAD		m_wp4->MoveWindow(rect3);*/
//DEAD		m_wp1->GetClientRect(rect3);
//DEAD		CRListBox* rlistbox;
//DEAD		rlistbox=m_wp1->GetDlgItem(IDC_WAYPOINTLIST);
//DEAD		rlistbox->MoveWindow(rect3);
//DEAD		rlistbox=m_wp2->GetDlgItem(IDC_WAYPOINTLIST);
//DEAD		rlistbox->MoveWindow(rect3);
//DEAD		rlistbox=m_wp3->GetDlgItem(IDC_WAYPOINTLIST);
//DEAD		rlistbox->MoveWindow(rect3);
//DEAD		rlistbox=m_wp4->GetDlgItem(IDC_WAYPOINTLIST);
//DEAD		rlistbox->MoveWindow(rect3);
//DEAD	}
}

BOOL CWaveTabs::OnInitDialog() 
{
	CDialog::OnInitDialog();
	parent->SetMaxSize(CRect(0,0,300,450));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
