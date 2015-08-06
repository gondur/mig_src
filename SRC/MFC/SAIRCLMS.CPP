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

// SAirClms.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SAirClms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CSQuickAirClaims dialog


CSQuickAirClaims::CSQuickAirClaims(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSQuickAirClaims::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSQuickAirClaims)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSQuickAirClaims::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQuickAirClaims)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_RSTATICCTRL25,m_IDC_RSTATICCTRL25);
	DDX_Control(pDX,IDC_SDETAIL3,m_IDC_SDETAIL3);
	DDX_Control(pDX,IDC_RSTATICCTRL26,m_IDC_RSTATICCTRL26);
	DDX_Control(pDX,IDC_RSTATICCTRL27,m_IDC_RSTATICCTRL27);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_RSTATICCTRL28,m_IDC_RSTATICCTRL28);
	DDX_Control(pDX,IDC_RSTATICCTRL29,m_IDC_RSTATICCTRL29);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_F80,m_IDC_SCLAIMS_PLAYER_F80);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_F51,m_IDC_SCLAIMS_PLAYER_F51);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_F84,m_IDC_SCLAIMS_PLAYER_F84);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_F86,m_IDC_SCLAIMS_PLAYER_F86);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_B26,m_IDC_SCLAIMS_PLAYER_B26);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_B29,m_IDC_SCLAIMS_PLAYER_B29);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_MIG15,m_IDC_SCLAIMS_PLAYER_MIG15);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_YAK,m_IDC_SCLAIMS_PLAYER_YAK);
	DDX_Control(pDX,IDC_SDETAIL4,m_IDC_SDETAIL4);
	DDX_Control(pDX,IDC_SDETAIL16,m_IDC_SDETAIL16);
	DDX_Control(pDX,IDC_SDETAIL20,m_IDC_SDETAIL20);
	DDX_Control(pDX,IDC_SCLAIMS_UN_F80,m_IDC_SCLAIMS_UN_F80);
	DDX_Control(pDX,IDC_SCLAIMS_UN_F51,m_IDC_SCLAIMS_UN_F51);
	DDX_Control(pDX,IDC_SCLAIMS_UN_F84,m_IDC_SCLAIMS_UN_F84);
	DDX_Control(pDX,IDC_SCLAIMS_UN_F86,m_IDC_SCLAIMS_UN_F86);
	DDX_Control(pDX,IDC_SCLAIMS_UN_B26,m_IDC_SCLAIMS_UN_B26);
	DDX_Control(pDX,IDC_SCLAIMS_UN_B29,m_IDC_SCLAIMS_UN_B29);
	DDX_Control(pDX,IDC_SCLAIMS_UN_MIG15,m_IDC_SCLAIMS_UN_MIG15);
	DDX_Control(pDX,IDC_SCLAIMS_UN_YAK,m_IDC_SCLAIMS_UN_YAK);
	DDX_Control(pDX,IDC_SCLAIMS_RED_F80,m_IDC_SCLAIMS_RED_F80);
	DDX_Control(pDX,IDC_SCLAIMS_RED_F51,m_IDC_SCLAIMS_RED_F51);
	DDX_Control(pDX,IDC_SCLAIMS_RED_F84,m_IDC_SCLAIMS_RED_F84);
	DDX_Control(pDX,IDC_SCLAIMS_RED_F86,m_IDC_SCLAIMS_RED_F86);
	DDX_Control(pDX,IDC_SCLAIMS_RED_B26,m_IDC_SCLAIMS_RED_B26);
	DDX_Control(pDX,IDC_SCLAIMS_RED_B29,m_IDC_SCLAIMS_RED_B29);
	DDX_Control(pDX,IDC_SCLAIMS_RED_MIG15,m_IDC_SCLAIMS_RED_MIG15);
	DDX_Control(pDX,IDC_SCLAIMS_RED_YAK,m_IDC_SCLAIMS_RED_YAK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSQuickAirClaims, CDialog)
	//{{AFX_MSG_MAP(CSQuickAirClaims)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQuickAirClaims message handlers

BOOL CSQuickAirClaims::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRStatic* s;
	(s=GETDLGITEM(IDC_SCLAIMS_PLAYER_F80))->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[SQ_F80]));
	(s=GETDLGITEM(IDC_SCLAIMS_PLAYER_F51))->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[SQ_F51]));
	(s=GETDLGITEM(IDC_SCLAIMS_PLAYER_F84))->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[SQ_F84]));
	(s=GETDLGITEM(IDC_SCLAIMS_PLAYER_F86))->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[SQ_F86A]+MMC.debrief.playerqmcounts[SQ_F86B]));
	(s=GETDLGITEM(IDC_SCLAIMS_PLAYER_B26))->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[SQ_B26]));
	(s=GETDLGITEM(IDC_SCLAIMS_PLAYER_B29))->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[SQ_B29]));
	(s=GETDLGITEM(IDC_SCLAIMS_PLAYER_MIG15))->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[SQ_MIG15]+MMC.debrief.playerqmcounts[SQ_M15B]));
	(s=GETDLGITEM(IDC_SCLAIMS_PLAYER_YAK))->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[SQ_YAK]));

	(s=GETDLGITEM(IDC_SCLAIMS_UN_F80	))->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[SQ_F80]));
	(s=GETDLGITEM(IDC_SCLAIMS_UN_F51	))->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[SQ_F51]));
	(s=GETDLGITEM(IDC_SCLAIMS_UN_F84	))->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[SQ_F84]));
	(s=GETDLGITEM(IDC_SCLAIMS_UN_F86	))->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[SQ_F86A]+MMC.debrief.unqmcounts[SQ_F86B]));
	(s=GETDLGITEM(IDC_SCLAIMS_UN_B26	))->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[SQ_B26]));
	(s=GETDLGITEM(IDC_SCLAIMS_UN_B29	))->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[SQ_B29]));
	(s=GETDLGITEM(IDC_SCLAIMS_UN_MIG15	))->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[SQ_MIG15]+MMC.debrief.unqmcounts[SQ_M15B]));
	(s=GETDLGITEM(IDC_SCLAIMS_UN_YAK	))->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[SQ_YAK]));

	(s=GETDLGITEM(IDC_SCLAIMS_RED_F80	))->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[SQ_F80]));
	(s=GETDLGITEM(IDC_SCLAIMS_RED_F51	))->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[SQ_F51]));
	(s=GETDLGITEM(IDC_SCLAIMS_RED_F84	))->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[SQ_F84]));
	(s=GETDLGITEM(IDC_SCLAIMS_RED_F86	))->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[SQ_F86A]+MMC.debrief.redqmcounts[SQ_F86B]));
	(s=GETDLGITEM(IDC_SCLAIMS_RED_B26	))->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[SQ_B26]));
	(s=GETDLGITEM(IDC_SCLAIMS_RED_B29	))->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[SQ_B29]));
	(s=GETDLGITEM(IDC_SCLAIMS_RED_MIG15	))->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[SQ_MIG15]+MMC.debrief.unqmcounts[SQ_M15B]));
	(s=GETDLGITEM(IDC_SCLAIMS_RED_YAK	))->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[SQ_YAK]));








	return TRUE;  // return TRUE unless you set the focus to a control
}
