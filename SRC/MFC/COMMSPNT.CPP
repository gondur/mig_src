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

// CommsPnt.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "CommsPnt.h"
#include "winmove.h"
#include "comms.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CCommsPaint dialog


CCommsPaint::CCommsPaint(CWnd* pParent /*=NULL*/)
	: RowanDialog(CCommsPaint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommsPaint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCommsPaint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommsPaint)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_NOSEART0,m_IDC_NOSEART0);
	DDX_Control(pDX,IDC_NOSEART1,m_IDC_NOSEART1);
	DDX_Control(pDX,IDC_NOSEART2,m_IDC_NOSEART2);
	DDX_Control(pDX,IDC_NOSEART3,m_IDC_NOSEART3);
	DDX_Control(pDX,IDC_NOSEART4,m_IDC_NOSEART4);
	DDX_Control(pDX,IDC_NOSEART5,m_IDC_NOSEART5);
	DDX_Control(pDX,IDC_NOSEART6,m_IDC_NOSEART6);
	DDX_Control(pDX,IDC_NOSEART7,m_IDC_NOSEART7);
	DDX_Control(pDX,IDC_NOSEART8,m_IDC_NOSEART8);
	DDX_Control(pDX,IDC_NOSEART9,m_IDC_NOSEART9);
	DDX_Control(pDX,IDC_NOSEART10,m_IDC_NOSEART10);
	DDX_Control(pDX,IDC_NOSEART11,m_IDC_NOSEART11);
	DDX_Control(pDX,IDC_NOSEART12,m_IDC_NOSEART12);
	DDX_Control(pDX,IDC_NOSEART13,m_IDC_NOSEART13);
	DDX_Control(pDX,IDC_NOSEART14,m_IDC_NOSEART14);
	DDX_Control(pDX,IDC_NOSEART15,m_IDC_NOSEART15);
	DDX_Control(pDX,IDC_NOSEART16,m_IDC_NOSEART16);
	DDX_Control(pDX,IDC_NOSEART17,m_IDC_NOSEART17);
	DDX_Control(pDX,IDC_NOSEART18,m_IDC_NOSEART18);
	DDX_Control(pDX,IDC_NOSEART19,m_IDC_NOSEART19);
	DDX_Control(pDX,IDC_NOSEART20,m_IDC_NOSEART20);
	DDX_Control(pDX,IDC_NOSEART21,m_IDC_NOSEART21);
	DDX_Control(pDX,IDC_NOSEART22,m_IDC_NOSEART22);
	DDX_Control(pDX,IDC_NOSEART23,m_IDC_NOSEART23);
	DDX_Control(pDX,IDC_NOSEART24,m_IDC_NOSEART24);
	DDX_Control(pDX,IDC_NOSEART25,m_IDC_NOSEART25);
	DDX_Control(pDX,IDC_NOSEART26,m_IDC_NOSEART26);
	DDX_Control(pDX,IDC_NOSEART27,m_IDC_NOSEART27);
	DDX_Control(pDX,IDC_NOSEART28,m_IDC_NOSEART28);
	DDX_Control(pDX,IDC_NOSEART29,m_IDC_NOSEART29);
	DDX_Control(pDX,IDC_NOSEART30,m_IDC_NOSEART30);
	DDX_Control(pDX,IDC_NOSEART31,m_IDC_NOSEART31);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommsPaint, CDialog)

	//{{AFX_MSG_MAP(CCommsPaint)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommsPaint message handlers
BEGIN_EVENTSINK_MAP(CCommsPaint, CDialog)
	ON_EVENT_RANGE(CCommsPaint, IDC_NOSEART0, IDC_NOSEART31, 1 /* Clicked */, OnClickedButtonID, VTS_I4)
END_EVENTSINK_MAP()


void	CCommsPaint::OnClickedButtonID(int id)
{
	int butnum=id-IDC_NOSEART0;
	assert(butnum>=0 && butnum<32);
  
	DPlay::H2H_Player[_DPlay.mySlot].decal = butnum;
//DeadCode JIM 12Jan99 	RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
	FullPanel()->LaunchDial(new CCurrEmblem,1);

}

BOOL CCommsPaint::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRButton* rbutton;
	int decals;
	for(int i=0;i<32;i++)
	{ 
		rbutton=GETDLGITEM(IDC_NOSEART0+i);
		if (DPlay::H2H_Player[_DPlay.mySlot].squadron < SQ_R_FLYABLE)
		{
			rbutton->ShowWindow(SW_SHOW);

			if (i < 16)
				decals = i + FIL_NOSE_STD_1;
			else
				decals = i - 16 + FIL_NOSE_USER_1;

 			rbutton->SetNormalFileNum(decals);
			rbutton->SetPressedFileNum(1);
		}else
		{
			rbutton->ShowWindow(SW_HIDE);
		}
	}

	paintshop_timer=SetTimer(TIMER_PAINTSHOP,0,NULL); 

	_DPlay.UISendInPaintShopMessage();
	DPlay::H2H_Player[_DPlay.mySlot].status=CPS_PAINTSHOP;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommsPaint::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==paintshop_timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	CDialog::OnTimer(nIDEvent);
}
