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

// SSound.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SSound.h"
#include "rcombo.h"
#include "miles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSound dialog
 

CSSound::CSSound(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSSound::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSSound)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
#define OPTIONS	\
	SETFIELD(CHAR(vol.music,0,25),				IDC_CBO_MUSIC,RESCOMBO(OBLMHT_OFF,6),					NOLEVEL)	\
	SETFIELD(CHAR(vol.sfx,0,25),				IDC_CBO_SFX,RESCOMBO(OBLMHT_OFF,6),						NOLEVEL)	\
	SETFIELD(CHAR(vol.uisfx,0,25),				IDC_CBO_SFX2,RESCOMBO(OBLMHT_OFF,6),						NOLEVEL)	\
	SETFIELD(CHAR(vol.anim,0,25),				IDC_CBO_SFX3,RESCOMBO(OBLMHT_OFF,6),						NOLEVEL)	\
	SETFIELD(CHAR(vol.rchat,0,25),				IDC_CBO_RADIOCHATTER,RESCOMBO(OBLMHT_OFF,6),			NOLEVEL)	\
	SETFIELD(CHAR(vol.engine,0,25),				IDC_CBO_ENGINESOUND,RESCOMBO(OBLMHT_OFF,6),				NOLEVEL)	 \
	SETFIELD(BIT(gamedifficulty,GD_GEFFECTS),		IDC_CBO_GEFFECTS,RESCOMBO(OFF,2),		DISABLEDINCOMMS)	\
	SETFIELD(BIT(gamedifficulty,GD_INJURYEFFECTS),		IDC_CBO_INJURYEFFECTS,RESCOMBO(OFF,2),		DISABLEDINCOMMS)	\
	SETFIELD(BIT(gamedifficulty,GD_WHITEOUT),		IDC_CBO_WHITEOUTS,RESCOMBO(OFF,2),		DISABLEDINCOMMS)	\
	SETFIELD(BIT(gamedifficulty,GD_AUTOVECTORING),		IDC_CBO_AUTOVECTORING,RESCOMBO(OFF,2),		DISABLEDINCOMMS)	\


void CSSound::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSSound)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_CBO_MUSIC,m_IDC_CBO_MUSIC);
	DDX_Control(pDX,IDC_CBO_SFX,m_IDC_CBO_SFX);
	DDX_Control(pDX,IDC_CBO_SFX2,m_IDC_CBO_SFX2);
	DDX_Control(pDX,IDC_CBO_SFX3,m_IDC_CBO_SFX3);
	DDX_Control(pDX,IDC_CBO_RADIOCHATTER,m_IDC_CBO_RADIOCHATTER);
	DDX_Control(pDX,IDC_CBO_ENGINESOUND,m_IDC_CBO_ENGINESOUND);
	DDX_Control(pDX,IDC_CBO_GEFFECTS,m_IDC_CBO_GEFFECTS);
	DDX_Control(pDX,IDC_CBO_INJURYEFFECTS,m_IDC_CBO_INJURYEFFECTS);
	DDX_Control(pDX,IDC_CBO_WHITEOUTS,m_IDC_CBO_WHITEOUTS);
	DDX_Control(pDX,IDC_CBO_AUTOVECTORING,m_IDC_CBO_AUTOVECTORING);
	//}}AFX_DATA_MAP
#define	SG2C_DISPLAY setlevel
#include "sg2combo.h"
	OPTIONS	
//		m_IDC_CBO_MUSIC.SetCircularStyle(TRUE);
//		m_IDC_CBO_SFX.SetCircularStyle(TRUE);
//		m_IDC_CBO_RADIOCHATTER.SetCircularStyle(TRUE);
//		m_IDC_CBO_ENGINESOUND.SetCircularStyle(TRUE);
//		m_IDC_CBO_GEFFECTS.SetCircularStyle(TRUE);
//		m_IDC_CBO_INJURYEFFECTS.SetCircularStyle(TRUE);
//		m_IDC_CBO_WHITEOUTS.SetCircularStyle(TRUE);
//		m_IDC_CBO_AUTOVECTORING.SetCircularStyle(TRUE);


		m_IDC_CBO_MUSIC.SetCircularStyle(TRUE);						  //RDH 03/04/99
		m_IDC_CBO_SFX.SetCircularStyle(TRUE);
		m_IDC_CBO_SFX2.SetCircularStyle(TRUE);
		m_IDC_CBO_SFX3.SetCircularStyle(TRUE);
		m_IDC_CBO_RADIOCHATTER.SetCircularStyle(TRUE);
		m_IDC_CBO_ENGINESOUND.SetCircularStyle(TRUE);
		m_IDC_CBO_GEFFECTS.SetCircularStyle(TRUE);
		m_IDC_CBO_INJURYEFFECTS.SetCircularStyle(TRUE);
		m_IDC_CBO_WHITEOUTS.SetCircularStyle(TRUE);
		m_IDC_CBO_AUTOVECTORING.SetCircularStyle(TRUE);				  //RDH 03/04/99
		
		if (!_Miles.IsEnabled(SOUND_DIGITAL))
		{
			GETDLGITEM(IDC_CBO_SFX)->Clear();
			GETDLGITEM(IDC_CBO_SFX)->AddString(RESSTRING(NOTAVAILABLE));
			GETDLGITEM(IDC_CBO_SFX)->SetIndex(0);
			GETDLGITEM(IDC_CBO_SFX)->Clear();
			if (	_Miles.digerror
				&&	ULongP(_Miles.digerror)[0]==*(int*)"Dire"
				&&	ULongP(_Miles.digerror)[1]==*(int*)"ctSo"
				)
				GETDLGITEM(IDC_CBO_SFX)->AddString(CString("DS:")+(_Miles.digerror+11));
			else
				GETDLGITEM(IDC_CBO_SFX)->AddString(_Miles.digerror);
		}
		if (!_Miles.IsEnabled(SOUND_MIDI))
		{
			GETDLGITEM(IDC_CBO_MUSIC)->Clear();
			GETDLGITEM(IDC_CBO_MUSIC)->AddString(RESSTRING(NOTAVAILABLE));
			GETDLGITEM(IDC_CBO_MUSIC)->SetIndex(0);
		}
		if (!_Miles.IsEnabled(SOUND_RADIO))						//DAW 18Aug99
		{
			GETDLGITEM(IDC_CBO_RADIOCHATTER)->Clear();
			GETDLGITEM(IDC_CBO_RADIOCHATTER)->AddString(RESSTRING(NOTAVAILABLE));
			GETDLGITEM(IDC_CBO_RADIOCHATTER)->SetIndex(0);
		}


//	calib=GetDlgItem(IDC_CALIB2);
//	calib->SetCaption(RESSTRING(CONFIG));

}



BEGIN_MESSAGE_MAP(CSSound, CDialog)
	//{{AFX_MSG_MAP(CSSound)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSound message handlers

void CSSound::OnDestroy() 
{
	KillTimer(OthersPref_Timer);

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}
void CSSound::PreDestroyPanel()
{
#define	SG2C_WRITEBACK setlevel
#include "sg2combo.h"

	OPTIONS

	_Miles.SetVolumes(FALSE);									//RJS 12Mar99
}
#define SG2C_CLEANUP
#include "sg2combo.h"

BEGIN_EVENTSINK_MAP(CSSound, CDialog)
    //{{AFX_EVENTSINK_MAP(CSSound)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


BOOL CSSound::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (_DPlay.PlayerCreated)									//AMM 12Jul99
	{															//AMM 12Jul99
		_DPlay.UISendInPrefsMessage();							//AMM 12Jul99
		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_PREFS;		//AMM 12Jul99
	}															//AMM 12Jul99

	OthersPref_Timer=SetTimer(TIMER_PREFSOTHERS,0,NULL);

	CRCombo* combo;
	if	(		(RFullPanelDial::incomms)
			&&	(_DPlay.UIPlayerType==PLAYER_GUEST)
		)
	{
		combo=GETDLGITEM(IDC_CBO_GEFFECTS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_INJURYEFFECTS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_WHITEOUTS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_AUTOVECTORING);
		combo->SetEnabled(false);
	}else
	{
		combo=GETDLGITEM(IDC_CBO_GEFFECTS);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_INJURYEFFECTS);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_WHITEOUTS);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_AUTOVECTORING);
		combo->SetEnabled(true);
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSSound::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==OthersPref_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	
	CDialog::OnTimer(nIDEvent);
}
