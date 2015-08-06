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

// RRadioP.cpp : Implementation of the CRRadioPropPage property page class.

#include "stdafx.h"
#include "RRadio.h"
#include "RRadioP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRRadioPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRRadioPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CRRadioPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRRadioPropPage, "RRADIO.RRadioPropPage.1",
	0x7ebc74e5, 0xf3c, 0x11d2, 0xa1, 0xf0, 0, 0x80, 0xc8, 0x58, 0x2d, 0xe4)


/////////////////////////////////////////////////////////////////////////////
// CRRadioPropPage::CRRadioPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CRRadioPropPage

BOOL CRRadioPropPage::CRRadioPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_RRADIO_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRRadioPropPage::CRRadioPropPage - Constructor

CRRadioPropPage::CRRadioPropPage() :
	COlePropertyPage(IDD, IDS_RRADIO_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CRRadioPropPage)
	m_cols = 0;
	m_FontNum = 0;
	m_ColumnWidth = 0;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CRRadioPropPage::DoDataExchange - Moves data between page and properties

void CRRadioPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CRRadioPropPage)
	DDP_Text(pDX, IDC_COLS, m_cols, _T("Cols") );
	DDX_Text(pDX, IDC_COLS, m_cols);
	DDP_Text(pDX, IDC_FONTNUM, m_FontNum, _T("FontNum") );
	DDX_Text(pDX, IDC_FONTNUM, m_FontNum);
	DDP_Text(pDX, IDC_COLUMNWIDTH, m_ColumnWidth, _T("ColumnWidth") );
	DDX_Text(pDX, IDC_COLUMNWIDTH, m_ColumnWidth);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CRRadioPropPage message handlers
