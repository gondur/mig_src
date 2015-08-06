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

// SmkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SmkDlg.h"
#include "smack.h"
#undef LPDDCAPS
#include	"win3d.h"
#include	"globrefs.h"
#include	"stub3d.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
extern	Smack*	OpenSmack(FileNum filenumber,int win,int X,int Y,int w,int h);
extern	cdecl	UWord	DoSmack(int poo);
extern	cdecl	void	CloseSmack();

/////////////////////////////////////////////////////////////////////////////
// CSmackerDialog dialog


CSmackerDialog::CSmackerDialog(FileNum fil, CWnd* pParent /*=NULL*/)
	: RowanDialog(CSmackerDialog::IDD, pParent)
{
	file = fil;
	//{{AFX_DATA_INIT(CSmackerDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSmackerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmackerDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSmackerDialog, CDialog)
	//{{AFX_MSG_MAP(CSmackerDialog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmackerDialog message handlers

BOOL CSmackerDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rect;
	GetClientRect(rect);
//	OpenSmack(FindSmacker(),(int)m_hWnd,0,0,0,0);
	File_Man.DiscardDirList(file);
	File_Man.ExistNumberedFile(file);
	OpenSmack(file,(int)m_hWnd,0,0,0,0);
	m_timerID=SetTimer(1984,1,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSmackerDialog::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==m_timerID)
	{
		if (!DoSmack((int)m_hWnd))
		{
			OnOK();
		}
	}
//	CDialog::OnTimer(nIDEvent);
}

void CSmackerDialog::OnDestroy() 
{
	CloseSmack();
	CDialog::OnDestroy();
//	Master_3d.BigWin();
}

//FileNum	CSmackerDialog::FindSmacker()
//{
//	Debrief::DisLog* dislog;
//
//	if (CDIS::intelltime == CDIS::ALL)
//		dislog = MMC.debrief.alldis;
//	else
//		dislog = MMC.debrief.disday;
//	dislog[CDIS::currhilight].msgtextid;
//
//	for (int i=0; i < SupplyTree::MAX_DISSMACKERS; i++)
//	{
//		if (dislog[CDIS::currhilight].msgtextid == SupplyTree::dissmackers[i].idtext)
//			return (SupplyTree::dissmackers[i].file);
//	}
//	return (FIL_NULL);
//}

void CSmackerDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect);

	CloseSmack();
	File_Man.DiscardDirList(file);
	File_Man.ExistNumberedFile(file);
//	OpenSmack(FindSmacker(),(int)m_hWnd,0,0,rect.right,rect.bottom);
	OpenSmack(file,(int)m_hWnd,0,0,rect.right,rect.bottom);
}


