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

// SQView.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SQView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CQuickView dialog


CQuickView::CQuickView(CWnd* pParent /*=NULL*/)
	: RowanDialog(CQuickView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuickView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQuickView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuickView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_SDETAIL2,m_IDC_SDETAIL2);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_RSTATICCTRL26,m_IDC_RSTATICCTRL26);
	DDX_Control(pDX,IDC_RSTATICCTRL36,m_IDC_RSTATICCTRL36);
	DDX_Control(pDX,IDC_RSTATICCTRL38,m_IDC_RSTATICCTRL38);
	DDX_Control(pDX,IDC_RSTATICCTRL39,m_IDC_RSTATICCTRL39);
	DDX_Control(pDX,IDC_RSTATICCTRL41,m_IDC_RSTATICCTRL41);
	DDX_Control(pDX,IDC_RSTATICCTRL42,m_IDC_RSTATICCTRL42);
	DDX_Control(pDX,IDC_RSTATICCTRL40,m_IDC_RSTATICCTRL40);
	DDX_Control(pDX,IDC_RSTATICCTRL43,m_IDC_RSTATICCTRL43);
	DDX_Control(pDX,IDC_RSTATICCTRL44,m_IDC_RSTATICCTRL44);
	DDX_Control(pDX,IDC_RSTATICCTRL45,m_IDC_RSTATICCTRL45);
	DDX_Control(pDX,IDC_CURRMISS,m_IDC_CURRMISS);
	DDX_Control(pDX,IDC_CLOUD,m_IDC_CLOUD);
	DDX_Control(pDX,IDC_WEATHER,m_IDC_WEATHER);
	DDX_Control(pDX,IDC_TARGTYPE,m_IDC_TARGTYPE);
	DDX_Control(pDX,IDC_TARGNAME,m_IDC_TARGNAME);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuickView, CDialog)
	//{{AFX_MSG_MAP(CQuickView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuickView message handlers

BOOL CQuickView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRStatic*   s=GETDLGITEM(IDC_CURRMISS);
	s->SetString(RESLIST(QUICK_1, CSQuick1::currquickmiss));


		targtype=0,targentry=0;
	for (int t=0;t<4;t++)
		for (int e=0;e<4;e++)
			if(CSQuick1::quickdef.targets[t][e]==CSQuick1::quickdef.target)
				targtype=t,targentry=e;
	s=GETDLGITEM(IDC_TARGTYPE);
	s->SetString(LoadResString(CSQuick1::quickdef.targtypeIDs[targtype]));

	s=GETDLGITEM(IDC_TARGNAME);
	s->SetString(GetTargName(CSQuick1::quickdef.targets[targtype][targentry]));

	s=GETDLGITEM(IDC_WEATHER);
	s->SetString(RESLIST(WEATHER_CLEAR, CSQuick1::quickdef.weather));
	s=GETDLGITEM(IDC_CLOUD);
	s->SetString(CSprintf("%i", 5000 + 1000 * CSQuick1::quickdef.cloudbaseK));
	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
