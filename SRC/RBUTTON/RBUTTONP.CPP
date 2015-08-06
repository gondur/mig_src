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

// RButtonPpg.cpp : Implementation of the CRButtonPropPage property page class.

#include "stdafx.h"
#include "RButton.h"
#include "RButtonP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
#ifndef THIS_FILE_DEFINED
static char THIS_FILE[] = __FILE__;
#endif
#endif


IMPLEMENT_DYNCREATE(CRButtonPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRButtonPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CRButtonPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRButtonPropPage, "RBUTTON.RButtonPropPage.1",
	0x78918647, 0xa917, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CRButtonPropPage::CRButtonPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CRButtonPropPage

BOOL CRButtonPropPage::CRButtonPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_RBUTTON_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonPropPage::CRButtonPropPage - Constructor

CRButtonPropPage::CRButtonPropPage() :
	COlePropertyPage(IDD, IDS_RBUTTON_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CRButtonPropPage)
	m_bMovesParent = FALSE;
	m_FontNum = 0;
	m_bCloseButton = FALSE;
	m_bTickButton = FALSE;
	m_bToggle = FALSE;
	m_bShowShadow = FALSE;
	m_NormalFileNumString = _T("");
	m_PressedFileNumString = _T("");
	m_UpdateCaption = FALSE;
	m_hintStringID = _T("");
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonPropPage::DoDataExchange - Moves data between page and properties

void CRButtonPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CRButtonPropPage)
	DDP_Check(pDX, IDC_MOVES_PARENT, m_bMovesParent, _T("MovesParent") );
	DDX_Check(pDX, IDC_MOVES_PARENT, m_bMovesParent);
	DDP_Text(pDX, IDC_FONT_NUMBER, m_FontNum, _T("FontNum") );
	DDX_Text(pDX, IDC_FONT_NUMBER, m_FontNum);
	DDP_Check(pDX, IDC_CLOSE, m_bCloseButton, _T("CloseButton") );
	DDX_Check(pDX, IDC_CLOSE, m_bCloseButton);
	DDP_Check(pDX, IDC_TICK, m_bTickButton, _T("TickButton") );
	DDX_Check(pDX, IDC_TICK, m_bTickButton);
	DDP_Check(pDX, IDC_DROP_SHADOWS, m_bShowShadow, _T("ShowShadow") );
	DDX_Check(pDX, IDC_DROP_SHADOWS, m_bShowShadow);
	DDP_Text(pDX, IDC_NORMAL_PICTURE_FILE_NUM, m_NormalFileNumString, _T("NormalFileNumString") );
	DDX_Text(pDX, IDC_NORMAL_PICTURE_FILE_NUM, m_NormalFileNumString);
	DDP_Text(pDX, IDC_PRESSED_PICTURE_FILE_NUM, m_PressedFileNumString, _T("PressedFileNumString") );
	DDX_Text(pDX, IDC_PRESSED_PICTURE_FILE_NUM, m_PressedFileNumString);
	DDP_Check(pDX, IDC_UPDATE_CAPTION, m_UpdateCaption, _T("UpdateCaption") );
	DDX_Check(pDX, IDC_UPDATE_CAPTION, m_UpdateCaption);
	DDP_Text(pDX, IDC_PRESSED_PICTURE_FILE_NUM2, m_hintStringID, _T("HintStringID") );
	DDX_Text(pDX, IDC_PRESSED_PICTURE_FILE_NUM2, m_hintStringID);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonPropPage message handlers
