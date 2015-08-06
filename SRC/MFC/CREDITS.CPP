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

// Credits.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Credits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CCredits dialog


CCredits::CCredits(int thestring,CWnd* pParent /*=NULL*/)
	: RowanDialog(CCredits::IDD, pParent)
{
	strnum=thestring;
	//{{AFX_DATA_INIT(CCredits)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCredits::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCredits)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCredits, CDialog)
	//{{AFX_MSG_MAP(CCredits)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE( WM_GETXYOFFSET, OnGetXYOffset)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCredits message handlers

BOOL CCredits::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString doc=__DATE__;
	creds=IDS_CT_DESIGNTEAMTITLE;									  //DAW 21/06/99
	numcr=10;

	CRStatic* text=GETDLGITEM(IDC_SDETAIL1);
	text->SetString(LoadResString(creds));
//	text+=doc;
//	MessageBox (doc,"Warning",MB_OK);
//DEADCODE DAW 21/06/99 	m_timerID=SetTimer(1984,12000,NULL);
	m_timerID=SetTimer(1984,7000,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*long CCredits::OnGetXYOffset()
{ // *CLUDGE* to remove 1 pixel offset on quick mission screen
	long offset=RDialog::OnGetXYOffset();
	short offsetx=offset&0xFFFF;
	short offsety=(offset&0xFFFF0000)>>16;
//	TRACE2("Offset X: %d Offset Y: %d\n",offsetx,offsety);
	if (offsety==-301) offsety=-299;
	return offsetx+(offsety<<16);
}*/
extern	char* compiledate;
void CCredits::OnTimer(UINT nIDEvent) 
{
	CRStatic* text=GETDLGITEM(IDC_SDETAIL1);
	creds++;														  //DAW 21/06/99
	numcr--;
	if (numcr!=-1)
	if (creds<IDS_CT_COPYRIGHT)
		text->SetString(LoadResString(creds));
	else
	{
		void*	memptr;
		int		memsize;
		HGLOBAL	memhandle;
		HRSRC	reshandle;
 
		reshandle=FindResource(NULL,(char*)VS_VERSION_INFO,RT_VERSION); 
		memhandle=LoadResource(NULL,reshandle);
		memsize=GlobalSize(memhandle);
		memptr=LockResource(memhandle);
		ULong* search=(ULong*)memptr;
		while (*search!=0xFEEF04BD)
			search++;
		VS_FIXEDFILEINFO* info=(VS_FIXEDFILEINFO*)search;
		char	version[]="V 0.00@";
		version[2]+=info->dwProductVersionMS>>16;
		version[4]+=info->dwProductVersionMS&255;
		version[5]+=info->dwProductVersionLS>>16;
		version[6]+=info->dwProductVersionMS&255;
		if (version[6]=='@')
			version[6]=0;
		CString cr=LoadResString(IDS_CT_COPYRIGHT);
		int lastword=cr.ReverseFind(' ');
		if (lastword>cr.GetLength()-3)
		{
			cr=cr.Left(lastword);
			lastword=cr.ReverseFind(' ');
		}
		cr=cr.Left(lastword);
		text->SetString(	cr+"\n"+version+"     "+compiledate);

				
	}
//	if (nIDEvent==m_timerID)
//	{
//DeadCode DAW 14Jun99 		if (!DoSmack((int)m_hWnd))
//DeadCode DAW 14Jun99 		{
//DeadCode DAW 14Jun99 			OnOK();
//DeadCode DAW 14Jun99 		}
//	}
//	CDialog::OnTimer(nIDEvent);
}

void CCredits::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);
}

void CCredits::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	FullPanel()->OnLButtonUp(nFlags, point);	
}
