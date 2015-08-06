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

// Results.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Results.h"
#include "rlistbox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResults dialog


CResults::CResults(CWnd* pParent /*=NULL*/)
	: RowanDialog(CResults::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResults)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResults)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResults, CDialog)
	//{{AFX_MSG_MAP(CResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResults message handlers

BOOL CResults::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->AddColumn(125);
	rlistbox->AddColumn(50);
	rlistbox->AddColumn(50);
	rlistbox->AddColumn(25);
	rlistbox->AddString("I.D",0);
	rlistbox->AddString("St 1",0);
	rlistbox->AddString("Ar 1",0);
	rlistbox->AddString("Cp 1",0);
	rlistbox->AddString("Objective",1);
	rlistbox->AddString("Sinuiju Twin Bridges",1);
	rlistbox->AddString("Sunchon Highway",1);
	rlistbox->AddString("Yalu River",1);
	rlistbox->AddString("Task",2);
	rlistbox->AddString("Strike",2);
	rlistbox->AddString("Recon",2);
	rlistbox->AddString("MiGCAP",2);
	rlistbox->AddString("Result",3);
	rlistbox->AddString("50 (80)",3);
	rlistbox->AddString("5 Trucks",3);
	rlistbox->AddString("N/A",3);
	rlistbox->AddString("Kills",4);
	rlistbox->AddString("4",4);
	rlistbox->AddString("2",4);
	rlistbox->AddString("4",4);
	rlistbox->AddString("Lost",5);
	rlistbox->AddString("4",5);
	rlistbox->AddString("2",5);
	rlistbox->AddString("4",5);	
	rlistbox->AddString("Rating",6);
	rlistbox->AddString("Poo",6);
	rlistbox->AddString("Good",6);
	rlistbox->AddString("Bad",6);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
