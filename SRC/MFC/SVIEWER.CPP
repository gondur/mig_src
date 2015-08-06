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

// SViewer.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SViewer.h"
#include "replay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSViewer dialog
#define OPTIONS	\
	SETFIELD(BIT(gamedifficulty,GC_MULTIPLAYERVIEWRESTRICTED),		IDC_CBO_MULTIPLAYER_VIEW,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_PERIPHERALVISION),				IDC_CBO_PERIPHERAL_VISION,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_AUTOPADLOCKTOG),					IDC_CBO_AUTO_PADLOCK,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_VIEWMODESELECT),					IDC_CBO_VIEW_MODE_SELECT,RESCOMBO(PANNING,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_PADLOCKONLYWHENVIS),				IDC_CBO_PADLOCK,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_GUNCAMERACOLOUR),				IDC_CBO_CAMERACOLOUR,RESCOMBO(BLACKWHITE,2),		NOLEVEL)	\
	SETFIELD(CHAR(infoLineCount,0,1),								IDC_CBO_INFOLINE,RESCOMBO(INFOLINEOFF,4),NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_UNITS),							IDC_CBO_UNITS,RESCOMBO(IMPERIAL,2),		NOLEVEL)	\
	SETFIELD(ADDBIT(gamedifficulty,GD_GUNCAMERAONTRIGGER,GD_GUNCAMERAATSTART),				IDC_CBO_GUNCAMERAONATSTART,RESCOMBO(CAMERAOFF,3),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_HUDINSTACTIVE),					IDC_CBO_HEADSUPDISPLAY,RESCOMBO(OFF,2),		NOLEVEL)	\


//##need to change heads up save game variable
//DEADCODE RDH 02/04/99 	SETFIELD(BIT(gamedifficulty,GD_GUNCAMERAATSTART),				IDC_CBO_GUNCAMERAONATSTART,RESCOMBO(OFF,2),		NOLEVEL)	\
//DEADCODE RDH 02/04/99 	SETFIELD(BIT(gamedifficulty,GD_GUNCAMERAONTRIGGER),				IDC_CBO_CAMERAONTRIGGER,RESCOMBO(OFF,2),		NOLEVEL)	\


CSViewer::CSViewer(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSViewer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSViewer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

		//{{AFX_DATA_MAP(CSViewer)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL5,m_IDC_RSTATICCTRL5);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_RSTATICCTRL8,m_IDC_RSTATICCTRL8);
	DDX_Control(pDX,IDC_RSTATICCTRL9,m_IDC_RSTATICCTRL9);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_RSTATICCTRL12,m_IDC_RSTATICCTRL12);
	DDX_Control(pDX,IDC_RSTATICCTRL14,m_IDC_RSTATICCTRL14);
	DDX_Control(pDX,IDC_RSTATICCTRL16,m_IDC_RSTATICCTRL16);
	DDX_Control(pDX,IDC_CBO_MULTIPLAYER_VIEW,m_IDC_CBO_MULTIPLAYER_VIEW);
	DDX_Control(pDX,IDC_CBO_PERIPHERAL_VISION,m_IDC_CBO_PERIPHERAL_VISION);
	DDX_Control(pDX,IDC_CBO_AUTO_PADLOCK,m_IDC_CBO_AUTO_PADLOCK);
	DDX_Control(pDX,IDC_CBO_VIEW_MODE_SELECT,m_IDC_CBO_VIEW_MODE_SELECT);
	DDX_Control(pDX,IDC_CBO_PADLOCK,m_IDC_CBO_PADLOCK);
	DDX_Control(pDX,IDC_CBO_CAMERACOLOUR,m_IDC_CBO_CAMERACOLOUR);
	DDX_Control(pDX,IDC_CBO_UNITS,m_IDC_CBO_UNITS);
	DDX_Control(pDX,IDC_CBO_GUNCAMERAONATSTART,m_IDC_CBO_GUNCAMERAONATSTART);
	DDX_Control(pDX,IDC_CBO_HEADSUPDISPLAY,m_IDC_CBO_HEADSUPDISPLAY);
	DDX_Control(pDX,IDC_CBO_INFOLINE,m_IDC_CBO_INFOLINE);
//	DDX_Control(pDX,IDC_RCOMBOCTRL11,m_IDC_RCOMBOCTRL11);
//	DDX_Control(pDX,IDC_RCOMBOCTRL13,m_IDC_RCOMBOCTRL13);
//	DDX_Control(pDX,IDC_RCOMBOCTRL22,m_IDC_RCOMBOCTRL22);
	//}}AFX_DATA_MAP


#define	SG2C_DISPLAY setlevel
#include "sg2combo.h"
	OPTIONS	
	m_IDC_CBO_MULTIPLAYER_VIEW.SetCircularStyle(TRUE);
	m_IDC_CBO_PERIPHERAL_VISION.SetCircularStyle(TRUE);
	m_IDC_CBO_AUTO_PADLOCK.SetCircularStyle(TRUE);
	m_IDC_CBO_VIEW_MODE_SELECT.SetCircularStyle(TRUE);
	m_IDC_CBO_PADLOCK.SetCircularStyle(TRUE);
	m_IDC_CBO_CAMERACOLOUR.SetCircularStyle(TRUE);
	m_IDC_CBO_UNITS.SetCircularStyle(TRUE);
	m_IDC_CBO_GUNCAMERAONATSTART.SetCircularStyle(TRUE);
	m_IDC_CBO_HEADSUPDISPLAY.SetCircularStyle(TRUE);
	m_IDC_CBO_INFOLINE.SetCircularStyle(TRUE);
//

}


BEGIN_MESSAGE_MAP(CSViewer, CDialog)
	//{{AFX_MSG_MAP(CSViewer)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSViewer message handlers

void CSViewer::OnDestroy() 
{
	KillTimer(ViewsPref_Timer); 

	CDialog::OnDestroy();
	Save_Data.SetUnits();
	
}
void CSViewer::PreDestroyPanel()
{
#define	SG2C_WRITEBACK setlevel
#include "sg2combo.h"
	OPTIONS	
}
#define SG2C_CLEANUP
#include "sg2combo.h"

void CSViewer::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==ViewsPref_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CSViewer::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (_DPlay.PlayerCreated)									//AMM 12Jul99
	{															//AMM 12Jul99
		_DPlay.UISendInPrefsMessage();							//AMM 12Jul99
		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_PREFS;		//AMM 12Jul99
	}															//AMM 12Jul99

//DeadCode AMM 31Mar99 	if (RFullPanelDial::gamestate!=RFullPanelDial::TITLE)						//AMM 31Mar99
//DeadCode AMM 31Mar99 		_Replay.prefscheck=true;								//AMM 31Mar99
	
	ViewsPref_Timer=SetTimer(TIMER_PREFSVIEWS,0,NULL);

	CRCombo* combo;
	if	(		(RFullPanelDial::incomms)
			&&	(_DPlay.UIPlayerType==PLAYER_GUEST)
		)
	{
		combo=GETDLGITEM(IDC_CBO_MULTIPLAYER_VIEW);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_PERIPHERAL_VISION);
		combo->SetEnabled(false);
//DeadCode AMM 12Jul99 		combo=GETDLGITEM(IDC_CBO_AUTO_PADLOCK);
//DeadCode AMM 12Jul99 		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_VIEW_MODE_SELECT);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_PADLOCK);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_INFOLINE);
		combo->SetEnabled(false);
	}
	else
	{
		combo=GETDLGITEM(IDC_CBO_MULTIPLAYER_VIEW);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_PERIPHERAL_VISION);
		combo->SetEnabled(true);
//DeadCode AMM 12Jul99 		combo=GETDLGITEM(IDC_CBO_AUTO_PADLOCK);
//DeadCode AMM 12Jul99 		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_VIEW_MODE_SELECT);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_PADLOCK);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_INFOLINE);
		combo->SetEnabled(true);
	}

	if (RFullPanelDial::incomms)
	{
		combo=GETDLGITEM(IDC_CBO_CAMERACOLOUR);
		combo->SetEnabled(false);
//DeadCode AMM 25May99 		combo=GETDLGITEM(IDC_CBO_UNITS);
//DeadCode AMM 25May99 		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_GUNCAMERAONATSTART);
		combo->SetEnabled(false);
	}
	GETDLGITEM(IDC_CBO_INFOLINE)
		->Clear();
	GETDLGITEM(IDC_CBO_INFOLINE)
		->RESCOMBO(INFOLINEOFF,3)
		->AddString(RESSTRING(MAP_WAYPOINTS));
	GETDLGITEM(IDC_CBO_INFOLINE)
		->SetIndex(Save_Data.infoLineCount);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
