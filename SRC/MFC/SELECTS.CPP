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

// Selects.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Selects.h"
#include "rlistbox.h"
#include "comit_e.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CSelectionResults dialog


CSelectionResults::CSelectionResults(int d, CWnd* pParent /*=NULL*/)
	: RowanDialog(CSelectionResults::IDD, pParent)
{

	tab = d;
	CComit_e::This->directivedetails[d] = this;

	//{{AFX_DATA_INIT(CSelectionResults)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectionResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectionResults)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectionResults, CDialog)
	//{{AFX_MSG_MAP(CSelectionResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectionResults message handlers

BOOL CSelectionResults::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Redraw();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CSelectionResults::Redraw()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();

//input: tab = tab displayed	
//this is = to type we want
//find current directive with this type
	int directive = 0;
	while	(		(directive < MAXDIRECTIVES)
				&&	(CComit_e::This->dir_ctrl.directives[directive].type != tab)
			)
	{
		directive++;
	}
	if (directive == MAXDIRECTIVES)
		//error condition
		directive = 0;
	if (CComit_e::This->dir_ctrl.directives[directive].type == SupplyTree::D_AIRSUPERIORITY)
	{
		rlistbox->AddColumn(300);
		if (CComit_e::This->dir_ctrl.directives[directive].missions[0].note == SupplyTree::M_NOFIGHTERS)
		{
			rlistbox->AddString(RESSTRING(NOFIGHTERS),0);
		}else
		{
			rlistbox->AddString(RESSTRING(CAPAC),0);
		}
	}else if 	(		(CComit_e::This->dir_ctrl.directives[directive].missions[0].note == SupplyTree::M_NOACALLOC)
				)
	{
		rlistbox->AddColumn(300);
		rlistbox->AddString(LoadResString(IDS_L_NOALLOC),0);

	}else
	{
		if  (		(CComit_e::This->dir_ctrl.directives[directive].type == SupplyTree::D_ROAD)
				||		(CComit_e::This->dir_ctrl.directives[directive].type == SupplyTree::D_RAIL)
			)
		{
			rlistbox->AddColumn(180);
//DEADCODE RDH 26/04/99 			rlistbox->AddColumn(180);
			rlistbox->AddColumn(100);
			rlistbox->AddString(RESSTRING(DIRECTIVETARGET),0);
//DEADCODE RDH 26/04/99 			rlistbox->AddString(RESSTRING(FROM),0);
//DEADCODE RDH 26/04/99 			rlistbox->AddString(RESSTRING(TO),1);
			rlistbox->AddString(RESSTRING(NOTES),1);
 			for (char i = 0; i < CComit_e::This->dir_ctrl.directives[directive].targets ;i++)	
			{
				if (CComit_e::This->dir_ctrl.directives[directive].missions[i].target != UID_NULL)
		  			rlistbox->AddString(GetTargName(CComit_e::This->dir_ctrl.directives[directive].missions[i].target), 0);
//DEADCODE RDH 26/04/99 				if (CComit_e::This->dir_ctrl.directives[directive].missions[i].suppliee != UID_NULL)
//DEADCODE RDH 26/04/99 		  			rlistbox->AddString(GetTargName(CComit_e::This->dir_ctrl.directives[directive].missions[i].suppliee), 1);
				if (CComit_e::This->dir_ctrl.directives[directive].missions[i].missionset)
					rlistbox->AddString(LoadResString(IDS_L_ALPHASTRIKE + CComit_e::This->dir_ctrl.directives[directive].missions[i].profile),1);
				else
					rlistbox->AddString(LoadResString(IDS_L_NOALLOC + CComit_e::This->dir_ctrl.directives[directive].missions[i].note),1);
			}



		}else
		{
			rlistbox->AddColumn(180);
			rlistbox->AddColumn(100);
			rlistbox->AddString(RESSTRING(DIRECTIVETARGET),0);
			rlistbox->AddString(RESSTRING(NOTES),1);

			for (char i = 0; i < CComit_e::This->dir_ctrl.directives[directive].targets ;i++)	
			{
				if (CComit_e::This->dir_ctrl.directives[directive].missions[i].target != UID_NULL)
		  			rlistbox->AddString(GetTargName(CComit_e::This->dir_ctrl.directives[directive].missions[i].target), 0);
				if (CComit_e::This->dir_ctrl.directives[directive].missions[i].missionset)
					rlistbox->AddString(LoadResString(IDS_L_ALPHASTRIKE + CComit_e::This->dir_ctrl.directives[directive].missions[i].profile),1);
				else
					rlistbox->AddString(LoadResString(IDS_L_NOALLOC + CComit_e::This->dir_ctrl.directives[directive].missions[i].note),1);
			}
		}
	}

}
