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

// RListBoxPpg.cpp : Implementation of the CRListBoxPropPage property page class.

#include "stdafx.h"
#include "RListBox.h"
#include "RListBxP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRListBoxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRListBoxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CRListBoxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRListBoxPropPage, "RLISTBOX.RListBoxPropPage.1",
	0x90b5eda8, 0x666f, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CRListBoxPropPage::CRListBoxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CRListBoxPropPage

BOOL CRListBoxPropPage::CRListBoxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_RLISTBOX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxPropPage::CRListBoxPropPage - Constructor

CRListBoxPropPage::CRListBoxPropPage() :
	COlePropertyPage(IDD, IDS_RLISTBOX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CRListBoxPropPage)
	m_bIsStripey = FALSE;
	m_lines = FALSE;
	m_bLockLeftColumn = FALSE;
	m_bLockTopRow = FALSE;
	m_bDragAndDrop = FALSE;
	m_FontNum = 0;
	m_bBlackboard = FALSE;
	m_FontNum2 = 0;
	m_bLines2 = FALSE;
	m_bSelectWholeRows = FALSE;
	m_border = FALSE;
	m_horzSeperation = 0;
	m_vertSeperation = 0;
	m_Centred = FALSE;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxPropPage::DoDataExchange - Moves data between page and properties

void CRListBoxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CRListBoxPropPage)
	DDP_Check(pDX, IDC_IS_STRIPEY, m_bIsStripey, _T("IsStripey") );
	DDX_Check(pDX, IDC_IS_STRIPEY, m_bIsStripey);
	DDP_Check(pDX, IDC_LINES, m_lines, _T("Lines") );
	DDX_Check(pDX, IDC_LINES, m_lines);
	DDP_Check(pDX, IDC_LOCK_LEFT_COLUMN, m_bLockLeftColumn, _T("LockLeftColumn") );
	DDX_Check(pDX, IDC_LOCK_LEFT_COLUMN, m_bLockLeftColumn);
	DDP_Check(pDX, IDC_LOCK_TOP_ROW, m_bLockTopRow, _T("LockTopRow") );
	DDX_Check(pDX, IDC_LOCK_TOP_ROW, m_bLockTopRow);
	DDP_Check(pDX, IDC_DRAG_AND_DROP, m_bDragAndDrop, _T("DragAndDrop") );
	DDX_Check(pDX, IDC_DRAG_AND_DROP, m_bDragAndDrop);
	DDP_Text(pDX, IDC_FONT_NUMBER, m_FontNum, _T("FontNum") );
	DDX_Text(pDX, IDC_FONT_NUMBER, m_FontNum);
	DDP_Check(pDX, IDC_BLACKBOARD, m_bBlackboard, _T("Blackboard") );
	DDX_Check(pDX, IDC_BLACKBOARD, m_bBlackboard);
	DDP_Text(pDX, IDC_FONT_NUMBER2, m_FontNum2, _T("FontNum2") );
	DDX_Text(pDX, IDC_FONT_NUMBER2, m_FontNum2);
	DDP_Check(pDX, IDC_LINES2, m_bLines2, _T("Lines2") );
	DDX_Check(pDX, IDC_LINES2, m_bLines2);
	DDP_Check(pDX, IDC_SELECT_WHOLE_ROWS, m_bSelectWholeRows, _T("SelectWholeRows") );
	DDX_Check(pDX, IDC_SELECT_WHOLE_ROWS, m_bSelectWholeRows);
	DDP_Check(pDX, IDC_SELECT_WHOLE_ROWS2, m_border, _T("Border") );
	DDX_Check(pDX, IDC_SELECT_WHOLE_ROWS2, m_border);
	DDP_Text(pDX, IDC_HORZ_SEPERATION, m_horzSeperation, _T("HorzSeperation") );
	DDX_Text(pDX, IDC_HORZ_SEPERATION, m_horzSeperation);
	DDP_Text(pDX, IDC_VERT_SEPERATION, m_vertSeperation, _T("VertSeperation") );
	DDX_Text(pDX, IDC_VERT_SEPERATION, m_vertSeperation);
	DDP_Check(pDX, IDC_CENTRED, m_Centred, _T("Centred") );
	DDX_Check(pDX, IDC_CENTRED, m_Centred);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxPropPage message handlers
