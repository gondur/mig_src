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

// session.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "session.h"
#include "winmove.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectSession dialog


CSelectSession::CSelectSession(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSelectSession::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectSession)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectSession::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectSession)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLIST_SELECTSESSION,m_IDC_RLIST_SELECTSESSION);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectSession, CDialog)
	//{{AFX_MSG_MAP(CSelectSession)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectSession message handlers

BOOL CSelectSession::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_timer=SetTimer(2365,0,NULL);

	CRListBox* rlistbox;
	CString string;

	rlistbox=GETDLGITEM(IDC_RLIST_SELECTSESSION);
	rlistbox->Clear();
	rlistbox->AddColumn(200);

//DeadCode AMM 13Jul98 	ULong temp=_DPlay.JoinNameCount;
//DeadCode AMM 13Jul98 	char** Name=_DPlay.JoinNames;
//DeadCode AMM 13Jul98 
//DeadCode AMM 13Jul98 	while (temp--)
//DeadCode AMM 13Jul98 	{
//DeadCode AMM 13Jul98 		rlistbox->AddString(*Name,0);
//DeadCode AMM 13Jul98 		*Name++;
//DeadCode AMM 13Jul98 	}
//DeadCode AMM 13Jul98 
//DeadCode AMM 13Jul98 	rlistbox->AddString("Dont forget to get some real sessions",0);
//DeadCode AMM 13Jul98 	rlistbox->AddString("and fill in names structure",0);
//DeadCode AMM 13Jul98 	rlistbox->AddString("...",0);
//DeadCode AMM 13Jul98 	rlistbox->AddString("or people wont be able to join!",0);
//DeadCode AMM 13Jul98 	rlistbox->AddString("and that would be a shame",0);
//DeadCode AMM 13Jul98 	rlistbox->AddString("...",0);
//DeadCode AMM 13Jul98 	rlistbox->AddString("wouldnt it?",0);
//DeadCode AMM 13Jul98 	rlistbox->AddString("...",0);
//DeadCode AMM 13Jul98 	rlistbox->AddString("...",0);
//DeadCode AMM 13Jul98 	rlistbox->AddString("how many lines can these things take?",0);

	LPENUMSESSION temp;

	temp=_DPlay.SessionList;
	while (temp)
	{
		rlistbox->AddString(temp->sname,0);
		temp=temp->Next;
	}
	currsessrow=-1;
//DeadCode AMM 12Jul98 	string.LoadString(IDS_SESSION);
//DeadCode AMM 12Jul98 	rlistbox->AddString(string,0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CSelectSession, CDialog)
    //{{AFX_EVENTSINK_MAP(CSelectSession)
	ON_EVENT(CSelectSession, IDC_RLIST_SELECTSESSION, 1 /* Select */, OnSelectRlistSelectsession, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSelectSession::OnSelectRlistSelectsession(long row, long column) 
{
	// TODO: Add your control notification handler code here

//DeadCode AMM 13Jul98 	char** Name=_DPlay.JoinNames;
//DeadCode AMM 13Jul98 	while (row--)
//DeadCode AMM 13Jul98 	{
//DeadCode AMM 13Jul98 		*Name++;
//DeadCode AMM 13Jul98 	}
//DeadCode AMM 13Jul98 	
//DeadCode AMM 13Jul98 	strcpy(&_DPlay.SessionName[0],*Name);

	LPENUMSESSION temp;

	currsessrow=row;

	temp=_DPlay.SessionList;
	while (row-- && temp)
	{
		temp=temp->Next;
	}

	if (temp)
	{
		if (strcmp(temp->sname,_DPlay.SessionName))					  //RDH 03/04/99
		{
			strncpy(&_DPlay.SessionName[0],temp->sname,59);
				_DPlay.SessionName[59]=NULL;
		}else
		{
//DEADCODE AMM 10/07/99 			FullPanel()->OnSelectRlistbox(1,1);						  //RDH 03/04/99
		}
	}
}

void CSelectSession::OnTimer(UINT nIDEvent) 
{
 	if (nIDEvent==m_timer)
	{
		ULong c1=0,c2=0;
		LPENUMSESSION temp;
		CRListBox* rlistbox;

		temp=_DPlay.SessionList;
		while (temp)
		{
			c1++;
			temp=temp->Next;
		}

		_DPlay.UIGetSessionListUpdate();

		temp=_DPlay.SessionList;
		while (temp)
		{
			c2++;
			temp=temp->Next;
		}

		if (c1!=c2)
		{
			rlistbox=GETDLGITEM(IDC_RLIST_SELECTSESSION);
			rlistbox->Clear();
			rlistbox->AddColumn(200);

			temp=_DPlay.SessionList;
			while (temp)
			{
				if (_DPlay.singlesession)
				{
					strncpy(_DPlay.SessionName,_DPlay.SessionList->sname,59);
					_DPlay.SessionName[59]=NULL;

					KillTimer(m_timer);

					FullPanel()->OnSelectRlistbox(1,1);
					return;

				}
				rlistbox->AddString(temp->sname,0);
				temp=temp->Next;
			}
			currsessrow=-1;
		}

//		if (currsessrow>=0)
//		{
//			rlistbox->SetHilightRow(currsessrow);
//		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CSelectSession::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(m_timer);
}
