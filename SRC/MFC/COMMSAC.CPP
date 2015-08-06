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

// CommsAc.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "CommsAc.h"
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
// CCommsDeathMatchAc dialog


CCommsDeathMatchAc::CCommsDeathMatchAc(CWnd* pParent /*=NULL*/)
	: RowanDialog(CCommsDeathMatchAc::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommsDeathMatchAc)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCommsDeathMatchAc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommsDeathMatchAc)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_CURRENTAC,m_IDC_CURRENTAC);
	DDX_Control(pDX,IDC_CURRENTAIRCRAFT,m_IDC_CURRENTAIRCRAFT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommsDeathMatchAc, CDialog)
	//{{AFX_MSG_MAP(CCommsDeathMatchAc)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommsDeathMatchAc message handlers

BOOL CCommsDeathMatchAc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int index;
	CRCombo* combo=GETDLGITEM(IDC_CURRENTAC);
	
	combo->SetCircularStyle(TRUE);

	int maxindex = 0;
	
	if	(_DPlay.GameType == DEATHMATCH)
	{
#ifndef	MIG_DEMO_VER
		for (char i = 0; i < SQ_B_NONFLYABLE;i++)
			combo->AddString(RESLIST(SQ_BF_F86A,i));
		for (i = SQ_R_FLYABLE; i < SQ_R_NONFLYABLE;i++)
			combo->AddString(RESLIST(SQ_BF_F86A,i));

		maxindex = SQ_B_NONFLYABLE + SQ_R_NONFLYABLE - SQ_R_FLYABLE - 1;

		index = DPlay::H2H_Player[_DPlay.mySlot].squadron;
		if (index >= SQ_B_NONFLYABLE)
			index -=  (SQ_R_FLYABLE-SQ_B_NONFLYABLE);
		if (index > maxindex)
			index = 0;
#else
		for (char i = 0; i <= SQ_B_FLYABLE+1;i++)
			combo->AddString(RESLIST(SQ_BF_F86A,i));

		maxindex = SQ_B_FLYABLE;

		index = DPlay::H2H_Player[_DPlay.mySlot].squadron;
		if (index >= SQ_B_FLYABLE+1)
			index =0;
		if (index > maxindex)
			index = 0;
#endif

	}else if(_DPlay.Side)
	{
		for (char i = 0; i < SQ_B_NONFLYABLE;i++)
			combo->AddString(RESLIST(SQ_BF_F86A,i));
		index = DPlay::H2H_Player[_DPlay.mySlot].squadron;
		if (index >= SQ_B_NONFLYABLE)
			index =  0;
	}else
	{
		for (char i = SQ_R_FLYABLE; i < SQ_R_NONFLYABLE;i++)
			combo->AddString(RESLIST(SQ_BF_F86A,i));
		index = DPlay::H2H_Player[_DPlay.mySlot].squadron;
		if (index >= SQ_R_FLYABLE)
			index -=  (SQ_R_FLYABLE); //-SQ_B_NONFLYABLE);
		else 
			index = 0;
		if (index >=  (SQ_R_NONFLYABLE - SQ_R_FLYABLE))
			index = 0;

	}

	combo->SetIndex(index);

	(DPlay::H2H_Player+_DPlay.mySlot)->status=CPS_FRAG;

	acselect_timer=SetTimer(TIMER_ACSELECT,0,NULL); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CCommsDeathMatchAc, CDialog)
    //{{AFX_EVENTSINK_MAP(CCommsDeathMatchAc)
	ON_EVENT(CCommsDeathMatchAc, IDC_CURRENTAC, 1 /* TextChanged */, OnTextChangedCurrentac, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCommsDeathMatchAc::OnTextChangedCurrentac(LPCTSTR text) 
{
  	CRCombo* combo;
	combo=GETDLGITEM(IDC_CURRENTAC);
	int index = combo->GetIndex();	
	if	(_DPlay.GameType == DEATHMATCH)
	{
		if (index >= SQ_B_NONFLYABLE)
			index +=  (SQ_R_FLYABLE-SQ_B_NONFLYABLE);
		DPlay::H2H_Player[_DPlay.mySlot].squadron = index;	
	}else if (_DPlay.Side)
		DPlay::H2H_Player[_DPlay.mySlot].squadron = index;	
	else
		DPlay::H2H_Player[_DPlay.mySlot].squadron = index + SQ_R_FLYABLE;	

	CSQuick1::quickdef.UpdateAcType();
//DeadCode JIM 12Jan99 	RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
//DEADCODE RDH 25/03/99 	FullPanel()->LaunchDial(new CCurrEmblem,1);
	FullPanel()->PaintShopDesc();


}


void CCommsDeathMatchAc::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==acselect_timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	CDialog::OnTimer(nIDEvent);	
}
