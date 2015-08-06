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

// Variants.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Variants.h"
#include "RRadio.h"
#include "winmove.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CVariants dialog


CVariants::CVariants(CWnd* pParent /*=NULL*/)
	: RowanDialog(CVariants::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVariants)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVariants::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVariants)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RRADIO_F86VARIANTS0,m_IDC_RRADIO_F86VARIANTS0);
	DDX_Control(pDX,IDC_RRADIO_MUSTANGVARIANTS,m_IDC_RRADIO_MUSTANGVARIANTS);
	DDX_Control(pDX,IDC_RRADIO_F86VARIANTS1,m_IDC_RRADIO_F86VARIANTS1);
	DDX_Control(pDX,IDC_RSTATICCTRL43,m_IDC_RSTATICCTRL43);
	DDX_Control(pDX,IDC_RSTATICCTRL53,m_IDC_RSTATICCTRL53);
	DDX_Control(pDX,IDC_RSTATICCTRL54,m_IDC_RSTATICCTRL54);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVariants, CDialog)
	//{{AFX_MSG_MAP(CVariants)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVariants message handlers

BOOL CVariants::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRRadio* pradio;
	CString string;
	CREdit*	editbox;

	pradio=GETDLGITEM(IDC_RRADIO_F86VARIANTS0);
	string.LoadString(IDS_F86a);
	pradio->AddButton(string);
	string.LoadString(IDS_F86e);
	pradio->AddButton(string);
	string.LoadString(IDS_F86f);
	pradio->AddButton(string);
	pradio->SetCurrentSelection(MMC.squad[0].actype);


	pradio=GETDLGITEM(IDC_RRADIO_F86VARIANTS1);
	string.LoadString(IDS_F86a);
	pradio->AddButton(string);
	string.LoadString(IDS_F86e);
	pradio->AddButton(string);
	string.LoadString(IDS_F86f);
	pradio->AddButton(string);
	pradio->SetCurrentSelection(MMC.squad[1].actype);

//rdh 10/1/99	pradio=GETDLGITEM(IDC_RRADIO_MUSTANGVARIANTS);
//	string.LoadString(IDS_MUSTANG);
//	pradio->AddButton(string);
//	string.LoadString(IDS_TWINMUSTANG);
//	pradio->AddButton(string);
//	if (MMC.squad[4].actype == PT_F51)
//		pradio->SetCurrentSelection(0);
//	else
//		pradio->SetCurrentSelection(1);

// if we are in variants then treat as if we are in mission brief for
// status purposes

	Variants_Timer=SetTimer(TIMER_VARIANTS,0,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CVariants, CDialog)
    //{{AFX_EVENTSINK_MAP(CVariants)
	ON_EVENT(CVariants, IDC_RRADIO_F86VARIANTS0, 1 /* Selected */, OnSelectedRradioF86variants0, VTS_I4)
	ON_EVENT(CVariants, IDC_RRADIO_F86VARIANTS1, 1 /* Selected */, OnSelectedRradioF86variants1, VTS_I4)
	ON_EVENT(CVariants, IDC_RRADIO_MUSTANGVARIANTS, 1 /* Selected */, OnSelectedRradioMustangvariants, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CVariants::OnSelectedRradioF86variants0(long ButtonNum) 
{
	MMC.squad[0].actype = (PlaneTypeSelect)ButtonNum;
}

void CVariants::OnSelectedRradioF86variants1(long ButtonNum) 
{
	MMC.squad[1].actype = (PlaneTypeSelect)ButtonNum;
	
}

void CVariants::OnSelectedRradioMustangvariants(long ButtonNum) 
{
//rdh 10/1/99	if (ButtonNum == 0)
//		MMC.squad[4].actype = PT_F51;
//	else
//		MMC.squad[4].actype = PT_F82;

}

void CVariants::OnDestroy() 
{
	CDialog::OnDestroy();

	KillTimer(Variants_Timer);
}

void CVariants::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==Variants_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	
	CDialog::OnTimer(nIDEvent);
}
