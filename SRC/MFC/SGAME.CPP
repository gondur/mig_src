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

// SGame.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SGame.h"
#include "rcombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSGame dialog
#define OPTIONS	\
	SETFIELD(BIT(gamedifficulty,GD_UNLIMITEDARM),				IDC_CBO_WEAPONS,RESCOMBO(REALISTICARMS,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_VULNERABLE),					IDC_CBO_VULNERABLETOFIRE,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_GROUNDCOLLISIONS),			IDC_CBO_GROUNDCOLLISIONS,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_COLLISIONS),					IDC_CBO_MIDAIRCOLLISIONS,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_AIPILOTSALLTIME),			IDC_CBO_AIPILOTALLTIME,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_TACTICALRANGE),				IDC_CBO_ACCELOFF,RESCOMBO(RANGE_TACTICAL,2),		NOLEVEL)	\
	SETFIELD(TYPE(targetsize,TargetSize),								IDC_CBO_TARGETSIZE,RESCOMBO(LMH_LOW,3),				NOLEVEL)	\
	SETFIELD(CHAR(autopilotskillUN,0,1),						IDC_CBO_SKILL_UN,RESCOMBO(BLMHT_BOT,5),				NOLEVEL)	\
	SETFIELD(CHAR(autopilotskillRED,0,1),						IDC_CBO_SKILL_REDS,RESCOMBO(BLMHT_BOT,5),			NOLEVEL)	\
	SETFIELD(ADDBIT(gamedifficulty,GD_PERFECTRADARASSISTEDGUNSIGHT,GD_REALISTICRADARASSISTEDGUNSIGHT),		IDC_CBO_GUNSIGHTRANGING,RESCOMBO(MANUAL,3),		NOLEVEL)	\


CSGame::CSGame(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSGame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSGame)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL5,m_IDC_RSTATICCTRL5);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_RSTATICCTRL12,m_IDC_RSTATICCTRL12);
	DDX_Control(pDX,IDC_RSTATICCTRL14,m_IDC_RSTATICCTRL14);
	DDX_Control(pDX,IDC_RSTATICCTRL16,m_IDC_RSTATICCTRL16);
	DDX_Control(pDX,IDC_CBO_WEAPONS,m_IDC_CBO_WEAPONS);
	DDX_Control(pDX,IDC_CBO_VULNERABLETOFIRE,m_IDC_CBO_VULNERABLETOFIRE);
	DDX_Control(pDX,IDC_CBO_GROUNDCOLLISIONS,m_IDC_CBO_GROUNDCOLLISIONS);
	DDX_Control(pDX,IDC_CBO_MIDAIRCOLLISIONS,m_IDC_CBO_MIDAIRCOLLISIONS);
	DDX_Control(pDX,IDC_CBO_AIPILOTALLTIME,m_IDC_CBO_AIPILOTALLTIME);
	DDX_Control(pDX,IDC_CBO_ACCELOFF,m_IDC_CBO_ACCELOFF);
	DDX_Control(pDX,IDC_CBO_TARGETSIZE,m_IDC_CBO_TARGETSIZE);
	DDX_Control(pDX,IDC_CBO_SKILL_UN,m_IDC_CBO_SKILL_UN);
	DDX_Control(pDX,IDC_CBO_SKILL_REDS,m_IDC_CBO_SKILL_REDS);
	DDX_Control(pDX,IDC_CBO_GUNSIGHTRANGING,m_IDC_CBO_GUNSIGHTRANGING);
	//}}AFX_DATA_MAP
#define	SG2C_DISPLAY setlevel
#include "sg2combo.h"
	OPTIONS	
	m_IDC_CBO_WEAPONS.SetCircularStyle(TRUE);
	m_IDC_CBO_VULNERABLETOFIRE.SetCircularStyle(TRUE);
	m_IDC_CBO_GROUNDCOLLISIONS.SetCircularStyle(TRUE);
	m_IDC_CBO_MIDAIRCOLLISIONS.SetCircularStyle(TRUE);
	m_IDC_CBO_AIPILOTALLTIME.SetCircularStyle(TRUE);
	m_IDC_CBO_ACCELOFF.SetCircularStyle(TRUE);
	m_IDC_CBO_TARGETSIZE.SetCircularStyle(TRUE);
	m_IDC_CBO_SKILL_UN.SetCircularStyle(TRUE);
	m_IDC_CBO_SKILL_REDS.SetCircularStyle(TRUE);
	m_IDC_CBO_GUNSIGHTRANGING.SetCircularStyle(TRUE);
}


BEGIN_MESSAGE_MAP(CSGame, CDialog)
	//{{AFX_MSG_MAP(CSGame)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSGame message handlers

BOOL CSGame::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (_DPlay.PlayerCreated)									//AMM 12Jul99
	{															//AMM 12Jul99
		_DPlay.UISendInPrefsMessage();							//AMM 12Jul99
		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_PREFS;		//AMM 12Jul99
	}															//AMM 12Jul99

	GamePref_Timer=SetTimer(TIMER_PREFSGAME,0,NULL);

//DEAD	
//DEAD	CRCombo* combo;
//DEAD	CString string;
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_WEAPONS);
//DEAD	string.LoadString(IDS_OPT_UNLIMITED);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_REALISTIC);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_STEAL);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_VULNERABLETOFIRE);
//DEAD	string.LoadString(IDS_OPT_YES);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_NO);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_GROUNDCOLLISIONS);
//DEAD	string.LoadString(IDS_OPT_YES);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_NO);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_MIDAIRCOLLISIONS);
//DEAD	string.LoadString(IDS_OPT_YES);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_NO);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_AIPILOTALLTIME);
//DEAD	string.LoadString(IDS_OPT_YES);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_NO);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_ACCELOFF);
//DEAD	string.LoadString(IDS_OPT_TACTICAL);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_COMBAT);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_FF_GUNRATTLE);
//DEAD	string.LoadString(IDS_OPT_YES);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_NO);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_FF_STALL);
//DEAD	string.LoadString(IDS_OPT_YES);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_NO);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_FF_HIGHSPEED);
//DEAD	string.LoadString(IDS_OPT_YES);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_OPT_NO);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_TARGETSIZE);
//DEAD	string.LoadString(IDS_LARGE);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_MEDIUM);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_SMALL);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_SKILL_UN);
//DEAD	string.LoadString(IDS_SKILL_HIGH);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_SKILL_MEDIUM);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_SKILL_LOW);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_SKILL_REDS);
//DEAD	string.LoadString(IDS_SKILL_HIGH);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_SKILL_MEDIUM);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_SKILL_LOW);
//DEAD	combo->AddString(string);
//DEAD
//DEAD	combo=(CRCombo*)GetDlgItem(IDC_CBO_GUNSIGHTRANGING);
//DEAD	string.LoadString(IDS_MANUAL);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_PERFECT);
//DEAD	combo->AddString(string);
//DEAD	string.LoadString(IDS_REALISTIC);
//DEAD	combo->AddString(string);
//DEAD

	CRCombo* combo;
	if	(		(RFullPanelDial::incomms)
			&&	(_DPlay.UIPlayerType==PLAYER_GUEST)
		)
	{
		combo=GETDLGITEM(IDC_CBO_WEAPONS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_VULNERABLETOFIRE);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_GROUNDCOLLISIONS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_MIDAIRCOLLISIONS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_AIPILOTALLTIME);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_ACCELOFF);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_TARGETSIZE);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_SKILL_UN);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_SKILL_REDS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_GUNSIGHTRANGING);
		combo->SetEnabled(false);
	}else
	{
		combo=GETDLGITEM(IDC_CBO_WEAPONS);
		combo->SetEnabled(true);
		if (RFullPanelDial::incomms && _DPlay.GameType<COMMSQUICKMISSION)
		{
			combo=GETDLGITEM(IDC_CBO_VULNERABLETOFIRE);
			combo->SetEnabled(false);
			combo=GETDLGITEM(IDC_CBO_GROUNDCOLLISIONS);
			combo->SetEnabled(false);
			combo=GETDLGITEM(IDC_CBO_MIDAIRCOLLISIONS);
			combo->SetEnabled(false);
		}
		else
		{
			combo=GETDLGITEM(IDC_CBO_VULNERABLETOFIRE);
			combo->SetEnabled(true);
			combo=GETDLGITEM(IDC_CBO_GROUNDCOLLISIONS);
			combo->SetEnabled(true);
			combo=GETDLGITEM(IDC_CBO_MIDAIRCOLLISIONS);
			combo->SetEnabled(true);
		}
		combo=GETDLGITEM(IDC_CBO_AIPILOTALLTIME);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_ACCELOFF);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_TARGETSIZE);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_SKILL_UN);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_SKILL_REDS);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_GUNSIGHTRANGING);
		combo->SetEnabled(true);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSGame::OnDestroy() 
{
	KillTimer(GamePref_Timer);

//#define	SG2C_WRITEBACK setlevel
//#include "sg2combo.h"
//	OPTIONS	
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
void CSGame::PreDestroyPanel()
{
#define	SG2C_WRITEBACK setlevel
#include "sg2combo.h"
	OPTIONS	
}
#define SG2C_CLEANUP
#include "sg2combo.h"

void CSGame::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==GamePref_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}

	CDialog::OnTimer(nIDEvent);
}
