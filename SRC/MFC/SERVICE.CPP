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

// service.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "service.h"
#include	"winmove.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectService dialog


CSelectService::CSelectService(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSelectService::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectService)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectService::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectService)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLIST_SELECTSERVICE,m_IDC_RLIST_SELECTSERVICE);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectService, CDialog)
	//{{AFX_MSG_MAP(CSelectService)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectService message handlers

BOOL CSelectService::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	CString string;

	rlistbox=GETDLGITEM(IDC_RLIST_SELECTSERVICE);
	rlistbox->Clear();
	rlistbox->AddColumn(200);


	LPENUMSERVICE temp;

	temp=_DPlay.ServiceList;
	while (temp)
	{
		rlistbox->AddString(temp->sname,0);
		temp=temp->Next;
	}

	temp=_DPlay.ServiceList;
	int row  = 0;
	while	(	(temp)
			&&	(strcmp(temp->sname,_DPlay.ServiceName))
			)
	{
		temp=temp->Next;
		row++;
	}
	if (!temp)
	{
		row = 0;
		temp=_DPlay.ServiceList;
		if (temp)
		{
			strcpy(_DPlay.ServiceName,temp->sname);
		}
	}
	rlistbox->SetHilightRow(row);

// OK, a new session a new chance to process some messages...cool eh?

	_DPlay.LeaveCommsFlag=FALSE;
	_DPlay.HostQuitFlag=FALSE;
//	_DPlay.GameType=DEATHMATCH;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CSelectService, CDialog)
    //{{AFX_EVENTSINK_MAP(CSelectService)
	ON_EVENT(CSelectService, IDC_RLIST_SELECTSERVICE, 1 /* Select */, OnSelectRlistSelectservice, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSelectService::OnSelectRlistSelectservice(long row, long column) 
{
	LPENUMSERVICE temp;

	temp=_DPlay.ServiceList;
	while (row-- && temp)
	{
		temp=temp->Next;
	}
	if (temp)
	{
		if (strcmp(temp->sname,_DPlay.ServiceName))
		{
			strcpy(&_DPlay.ServiceName[0],temp->sname);

		}else
		{
//			RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
  //			FullScreen* fs;
			FullPanel()->OnSelectRlistbox(1,1);					//JIM 12Jan99
		}
	}		


}
