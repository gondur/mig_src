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

//DeadCode JIM 17Mar99 // Save.cpp : implementation file
//DeadCode JIM 17Mar99 //
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 #include "stdafx.h"
//DeadCode JIM 17Mar99 #include "mig.h"
//DeadCode JIM 17Mar99 #include "Save.h"
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 #ifdef _DEBUG
//DeadCode JIM 17Mar99 #define new DEBUG_NEW
//DeadCode JIM 17Mar99 #undef THIS_FILE
//DeadCode JIM 17Mar99 static char THIS_FILE[] = __FILE__;
//DeadCode JIM 17Mar99 #endif
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 /////////////////////////////////////////////////////////////////////////////
//DeadCode JIM 17Mar99 // CSave dialog
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 CSave::CSave(CWnd* pParent /*=NULL*/)
//DeadCode JIM 17Mar99 	: RowanDialog(CSave::IDD, pParent)
//DeadCode JIM 17Mar99 {
//DeadCode JIM 17Mar99 	filename = "";
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 	//{{AFX_DATA_INIT(CSave)
//DeadCode JIM 17Mar99 		// NOTE: the ClassWizard will add member initialization here
//DeadCode JIM 17Mar99 	//}}AFX_DATA_INIT
//DeadCode JIM 17Mar99 }
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 void CSave::DoDataExchange(CDataExchange* pDX)
//DeadCode JIM 17Mar99 {
//DeadCode JIM 17Mar99 	CDialog::DoDataExchange(pDX);
//DeadCode JIM 17Mar99 	//{{AFX_DATA_MAP(CSave)
//DeadCode JIM 17Mar99 		// NOTE: the ClassWizard will add DDX and DDV calls here
//DeadCode JIM 17Mar99 	DDX_Control(pDX,IDC_FILEOK,m_IDC_FILEOK);
//DeadCode JIM 17Mar99 	DDX_Control(pDX,IDC_RLISTBOXFILE,m_IDC_RLISTBOXFILE);
//DeadCode JIM 17Mar99 	DDX_Control(pDX,IDC_SAVENAME,m_IDC_SAVENAME);
//DeadCode JIM 17Mar99 	//}}AFX_DATA_MAP
//DeadCode JIM 17Mar99 }
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 BEGIN_MESSAGE_MAP(CSave, CDialog)
//DeadCode JIM 17Mar99 	//{{AFX_MSG_MAP(CSave)
//DeadCode JIM 17Mar99 	//}}AFX_MSG_MAP
//DeadCode JIM 17Mar99 END_MESSAGE_MAP()
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 /////////////////////////////////////////////////////////////////////////////
//DeadCode JIM 17Mar99 // CSave message handlers
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 BEGIN_EVENTSINK_MAP(CSave, CDialog)
//DeadCode JIM 17Mar99     //{{AFX_EVENTSINK_MAP(CSave)
//DeadCode JIM 17Mar99 	ON_EVENT(CSave, IDC_SAVE, 1 /* Clicked */, OnClickedSave, VTS_NONE)
//DeadCode JIM 17Mar99 	ON_EVENT(CSave, IDC_SAVENAME, 2 /* TextChanged */, OnTextChangedSavename, VTS_I4)
//DeadCode JIM 17Mar99 	ON_EVENT(CSave, IDC_RLISTBOXFILE, 1 /* Select */, OnSelectRlistboxfile, VTS_I4 VTS_I4)
//DeadCode JIM 17Mar99 	ON_EVENT(CSave, IDC_SAVENAME, 3 /* ReturnPressed */, OnReturnPressedSavename, VTS_BSTR)
//DeadCode JIM 17Mar99 	//}}AFX_EVENTSINK_MAP
//DeadCode JIM 17Mar99 END_EVENTSINK_MAP()
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 void CSave::OnClickedSave() 
//DeadCode JIM 17Mar99 {
//DeadCode JIM 17Mar99 	// TODO: Add your control notification handler code here
//DeadCode JIM 17Mar99 	
//DeadCode JIM 17Mar99 }
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 void CSave::OnTextChangedSavename(LPCTSTR text) 
//DeadCode JIM 17Mar99 {
//DeadCode JIM 17Mar99 	currrow = -1;
//DeadCode JIM 17Mar99 	CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);
//DeadCode JIM 17Mar99 	l->SetHilightRow(currrow);
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 }
//DeadCode JIM 17Mar99 void CSave::PrintFileName()
//DeadCode JIM 17Mar99 {
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 	CREdit* e;
//DeadCode JIM 17Mar99 	e=GETDLGITEM(IDC_SAVENAME);
//DeadCode JIM 17Mar99 	e->SetCaption(filename);
//DeadCode JIM 17Mar99 }
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 void CSave::OnSelectRlistboxfile(long row, long column) 
//DeadCode JIM 17Mar99 {
//DeadCode JIM 17Mar99 	// TODO: Add your control notification handler code here
//DeadCode JIM 17Mar99 	if (currrow == row)
//DeadCode JIM 17Mar99 	{
//DeadCode JIM 17Mar99 		OnOK();
//DeadCode JIM 17Mar99 	}else
//DeadCode JIM 17Mar99 	{
//DeadCode JIM 17Mar99 		CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);
//DeadCode JIM 17Mar99 		filename = (char*)l->GetString(row, column);
//DeadCode JIM 17Mar99 		PrintFileName();
//DeadCode JIM 17Mar99 		currrow = row;
//DeadCode JIM 17Mar99 	}
//DeadCode JIM 17Mar99 	
//DeadCode JIM 17Mar99 }
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 BOOL CSave::OnInitDialog() 
//DeadCode JIM 17Mar99 {
//DeadCode JIM 17Mar99 	CDialog::OnInitDialog();
//DeadCode JIM 17Mar99 	
//DeadCode JIM 17Mar99 	CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);
//DeadCode JIM 17Mar99 	l->Clear();
//DeadCode JIM 17Mar99 	
//DeadCode JIM 17Mar99 	l->AddColumn(200);
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 	l->AddString("file0",0);
//DeadCode JIM 17Mar99 	l->AddString("file1",0);
//DeadCode JIM 17Mar99 	l->AddString("file2",0);
//DeadCode JIM 17Mar99 	l->AddString("file3",0);
//DeadCode JIM 17Mar99 	l->AddString("file4",0);
//DeadCode JIM 17Mar99 	l->AddString("file5",0);
//DeadCode JIM 17Mar99 	l->AddString("file6",0);
//DeadCode JIM 17Mar99 	l->AddString("file7",0);
//DeadCode JIM 17Mar99 	l->AddString("file8",0);
//DeadCode JIM 17Mar99 	l->AddString("file9",0);
//DeadCode JIM 17Mar99 	l->AddString("file10",0);
//DeadCode JIM 17Mar99 	l->AddString("file11",0);
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 	//find the file in directory that = input filename
//DeadCode JIM 17Mar99 	//if found set currrow
//DeadCode JIM 17Mar99 	//else
//DeadCode JIM 17Mar99 	//		currrow = 0; filename = first in list
//DeadCode JIM 17Mar99 					currrow = 0;
//DeadCode JIM 17Mar99 					filename = "file0";
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 	l->SetHilightRow(currrow);
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 	PrintFileName();
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 	return TRUE;  // return TRUE unless you set the focus to a control
//DeadCode JIM 17Mar99 	              // EXCEPTION: OCX Property Pages should return FALSE
//DeadCode JIM 17Mar99 }
//DeadCode JIM 17Mar99 
//DeadCode JIM 17Mar99 void CSave::OnReturnPressedSavename(LPCTSTR text) 
//DeadCode JIM 17Mar99 {
//DeadCode JIM 17Mar99 	OnOK();
//DeadCode JIM 17Mar99 	
//DeadCode JIM 17Mar99 }
//DeadCode DAW 26Mar99 	ON_EVENT(CSave, IDC_SAVENAME, 2 /* TextChanged */, OnTextChangedSavename, VTS_I4)
//DeadCode DAW 26Mar99 	ON_EVENT(CSave, IDC_RLISTBOXFILE, 1 /* Select */, OnSelectRlistboxfile, VTS_I4 VTS_I4)
//DeadCode DAW 26Mar99 	ON_EVENT(CSave, IDC_SAVENAME, 3 /* ReturnPressed */, OnReturnPressedSavename, VTS_BSTR)
//DeadCode DAW 26Mar99 	//}}AFX_EVENTSINK_MAP
//DeadCode DAW 26Mar99 END_EVENTSINK_MAP()
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 void CSave::OnClickedSave() 
//DeadCode DAW 26Mar99 {
//DeadCode DAW 26Mar99 	// TODO: Add your control notification handler code here
//DeadCode DAW 26Mar99 	
//DeadCode DAW 26Mar99 }
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 void CSave::OnTextChangedSavename(LPTSTR text) 
//DeadCode DAW 26Mar99 {
//DeadCode DAW 26Mar99 	currrow = -1;
//DeadCode DAW 26Mar99 	CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);
//DeadCode DAW 26Mar99 	l->SetHilightRow(currrow);
//DeadCode DAW 26Mar99 		trunc(text,20);
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 }
//DeadCode DAW 26Mar99 void CSave::PrintFileName()
//DeadCode DAW 26Mar99 {
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	CREdit* e;
//DeadCode DAW 26Mar99 	e=GETDLGITEM(IDC_SAVENAME);
//DeadCode DAW 26Mar99 	e->SetCaption(filename);
//DeadCode DAW 26Mar99 }
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 void CSave::OnSelectRlistboxfile(long row, long column) 
//DeadCode DAW 26Mar99 {
//DeadCode DAW 26Mar99 	// TODO: Add your control notification handler code here
//DeadCode DAW 26Mar99 	if (currrow == row)
//DeadCode DAW 26Mar99 	{
//DeadCode DAW 26Mar99 		OnOK();
//DeadCode DAW 26Mar99 	}else
//DeadCode DAW 26Mar99 	{
//DeadCode DAW 26Mar99 		CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);
//DeadCode DAW 26Mar99 		filename = (char*)l->GetString(row, column);
//DeadCode DAW 26Mar99 		PrintFileName();
//DeadCode DAW 26Mar99 		currrow = row;
//DeadCode DAW 26Mar99 	}
//DeadCode DAW 26Mar99 	
//DeadCode DAW 26Mar99 }
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 BOOL CSave::OnInitDialog() 
//DeadCode DAW 26Mar99 {
//DeadCode DAW 26Mar99 	CDialog::OnInitDialog();
//DeadCode DAW 26Mar99 	
//DeadCode DAW 26Mar99 	CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);
//DeadCode DAW 26Mar99 	l->Clear();
//DeadCode DAW 26Mar99 	
//DeadCode DAW 26Mar99 	l->AddColumn(200);
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	l->AddString("file0",0);
//DeadCode DAW 26Mar99 	l->AddString("file1",0);
//DeadCode DAW 26Mar99 	l->AddString("file2",0);
//DeadCode DAW 26Mar99 	l->AddString("file3",0);
//DeadCode DAW 26Mar99 	l->AddString("file4",0);
//DeadCode DAW 26Mar99 	l->AddString("file5",0);
//DeadCode DAW 26Mar99 	l->AddString("file6",0);
//DeadCode DAW 26Mar99 	l->AddString("file7",0);
//DeadCode DAW 26Mar99 	l->AddString("file8",0);
//DeadCode DAW 26Mar99 	l->AddString("file9",0);
//DeadCode DAW 26Mar99 	l->AddString("file10",0);
//DeadCode DAW 26Mar99 	l->AddString("file11",0);
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	//find the file in directory that = input filename
//DeadCode DAW 26Mar99 	//if found set currrow
//DeadCode DAW 26Mar99 	//else
//DeadCode DAW 26Mar99 	//		currrow = 0; filename = first in list
//DeadCode DAW 26Mar99 					currrow = 0;
//DeadCode DAW 26Mar99 					filename = "file0";
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	l->SetHilightRow(currrow);
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	PrintFileName();
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	return TRUE;  // return TRUE unless you set the focus to a control
//DeadCode DAW 26Mar99 	              // EXCEPTION: OCX Property Pages should return FALSE
//DeadCode DAW 26Mar99 }
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 void CSave::OnReturnPressedSavename(LPCTSTR text) 
//DeadCode DAW 26Mar99 {
//DeadCode DAW 26Mar99 	OnOK();
//DeadCode DAW 26Mar99 	
//DeadCode DAW 26Mar99 }
//DeadCode DAW 26Mar99 ==========
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 
