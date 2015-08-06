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

// VwQList.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "VwQList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CViewQList dialog


CViewQList::CViewQList(int side,int wave,int group,CWnd* pParent /*=NULL*/)
	: RowanDialog(CViewQList::IDD, pParent)
{
	SetProjSpecific(side,wave,group);
	fields=&CSQuick1::quickdef.line[side][wave][group];

	//{{AFX_DATA_INIT(CViewQList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CViewQList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewQList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_GRPDESC,m_IDC_GRPDESC);
	DDX_Control(pDX,IDC_TYPE,m_IDC_TYPE);
	DDX_Control(pDX,IDC_FLIGHTS,m_IDC_FLIGHTS);
	DDX_Control(pDX,IDC_ALT,m_IDC_ALT);
	DDX_Control(pDX,IDC_SKILL,m_IDC_SKILL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewQList, CDialog)
	//{{AFX_MSG_MAP(CViewQList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewQList message handlers

BOOL CViewQList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRStatic*   s;

	s=GETDLGITEM(IDC_GRPDESC);
	s->SetString(LoadResString(fields->descID));

	s=GETDLGITEM(IDC_TYPE);
	s->SetString(RESLIST(SQ_BF_F86A,fields->actype));

	s=GETDLGITEM(IDC_FLIGHTS);
	if (	fields->Duty()==QuickFields::QFD_FIXED_NUM_PLAYER 
		||	fields->Duty()==QuickFields::QFD_FIXED_NUM_AUTO
		)
		s->SetString(CSprintf("%i", fields->flights));
	else
		if (fields->AllowZero()) 
			s->SetString(CSprintf("%i", fields->flights));
		else
			s->SetString(CSprintf("%i", fields->flights-1));


	s=GETDLGITEM(IDC_ALT);
	s->SetString(CSprintf("%i", fields->alt*10/Save_Data.alt.mediummm));
	s=GETDLGITEM(IDC_SKILL);
	s->SetString(RESLIST(SKILL_NOVICE,fields->skill/3));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
