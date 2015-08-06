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

// SystemBox.cpp : implementation file
//

#include "stdafx.h"
#include "MIG.h"
#include "SysBox.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemBox dialog


CSystemBox::CSystemBox(CMainFrame* mainf,CWnd* pParent /*=NULL*/)
	: RowanDialog(CSystemBox::IDD, pParent)
{
	m_pParent=mainf;
	once=false;
	//{{AFX_DATA_INIT(CSystemBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CSystemBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_THUMBNAIL,m_IDC_THUMBNAIL);
	DDX_Control(pDX,IDC_ZOOMIN,m_IDC_ZOOMIN);
	DDX_Control(pDX,IDC_FILES,m_IDC_FILES);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSystemBox, CDialog)
	//{{AFX_MSG_MAP(CSystemBox)
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemBox message handlers

//void CSystemBox::Init(UINT nIDTemplate, CWnd * pParentWnd)
//{
//	m_pParent=(CMainFrame*)pParentWnd;
//	Create(nIDTemplate, pParentWnd);
//	CButton* button;
//	HINSTANCE hinstance;
//	hinstance=AfxGetInstanceHandle();
//	button = (CButton*)(this->GetDlgItem(ID_BYE));
//	button->SetIcon(LoadIcon(hinstance,MAKEINTRESOURCE(IDI_BYE)));
//	button = (CButton*)(this->GetDlgItem(ID_GOSMALL));
//	button->SetIcon(LoadIcon(hinstance,MAKEINTRESOURCE(IDI_GOSMALL)));
//	button = (CButton*)(this->GetDlgItem(ID_GOBIG));
//	button->SetIcon(LoadIcon(hinstance,MAKEINTRESOURCE(IDI_GOBIG)));
//	button = (CButton*)(this->GetDlgItem(ID_GONORMAL));
//	button->SetIcon(LoadIcon(hinstance,MAKEINTRESOURCE(IDI_GONORMAL)));
//}

BEGIN_EVENTSINK_MAP(CSystemBox, CDialog)
    //{{AFX_EVENTSINK_MAP(CSystemBox)
	ON_EVENT(CSystemBox, IDC_FILES, 1 /* Clicked */, OnClickedFiles, VTS_NONE)
	ON_EVENT(CSystemBox, IDC_THUMBNAIL, 1 /* Clicked */, OnClickedThumbnail, VTS_NONE)
	ON_EVENT(CSystemBox, IDC_ZOOMIN, 1 /* Clicked */, OnClickedZoomin, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSystemBox::OnClickedFiles() 
{
	// TODO: Add your control notification handler code here
	m_pParent->OnBye();	
}

void CSystemBox::OnClickedThumbnail() 
{
	// TODO: Add your control notification handler code here
	m_pParent->OnGoSmall();
}

void CSystemBox::OnClickedZoomin() 
{
	// TODO: Add your control notification handler code here
	CRButton* z=GETDLGITEM(IDC_ZOOMIN);
	if (m_pParent->IsZoomed())	//z->GetPressed())
		m_pParent->OnGoNormal();
	else
		m_pParent->OnGoBig();

}


BOOL CSystemBox::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnEraseBkgnd(pDC);
}

void CSystemBox::OnEnable(BOOL bEnable) 
{
	CDialog::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	
}
