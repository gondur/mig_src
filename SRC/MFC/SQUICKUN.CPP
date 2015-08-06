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

// SQuickUN.cpp : implementation file
//

#include "stdafx.h"
//#include "mig.h"
//#include "SQuickUN.h"
#include	"bitfield.h"
typedef	 QuickFields	Q;

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
typedef	 QuickFields::QFD	QFD;
#ifndef QFDFIELD
#define QFDFIELD
MAKEFIELD(QFD,0,Q::QFD_LAST);
#endif
/////////////////////////////////////////////////////////////////////////////
// CSQuickLine dialog


CSQuickLine::CSQuickLine(int side,int wave,int group,CWnd* pParent /*=NULL*/)
	: RowanDialog(CSQuickLine::IDD, pParent)
{
	SetProjSpecific(side,wave,group);
	fields=&CSQuick1::quickdef.line[side][wave][group];
	//{{AFX_DATA_INIT(CSQuickLine)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSQuickLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQuickLine)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_GRPDESC,m_IDC_GRPDESC);
	DDX_Control(pDX,IDC_FLIGHTS,m_IDC_FLIGHTS);
	DDX_Control(pDX,IDC_TYPE,m_IDC_TYPE);
	DDX_Control(pDX,IDC_ALT,m_IDC_ALT);
	DDX_Control(pDX,IDC_SKILL,m_IDC_SKILL);
	DDX_Control(pDX,IDC_PILOTEDFLAG,m_IDC_PILOTEDFLAG);
	DDX_Control(pDX,IDC_RSTATICCTRL41,m_IDC_RSTATICCTRL41);
	DDX_Control(pDX,IDC_RSTATICCTRL42,m_IDC_RSTATICCTRL42);
	//}}AFX_DATA_MAP
}

BOOL CSQuickLine::OnInitDialog() 		//FP
{
	CDialog::OnInitDialog();
	fields->dialog=this;

	m_IDC_FLIGHTS.SetCircularStyle(TRUE);
	m_IDC_TYPE.SetCircularStyle(TRUE);
	m_IDC_ALT.SetCircularStyle(TRUE);
	m_IDC_SKILL.SetCircularStyle(TRUE);


	CRButton* currfl=GETDLGITEM(IDC_PILOTEDFLAG);
//DeadCode AMM 14Oct98 	if (_DPlay.CurrPlayers == 0)
	if (!RFullPanelDial::incomms)								//AMM 14Oct98
	{
		currfl->ShowWindow(SW_SHOW);
		if(CSQuick1::quickdef.plside==packnum && CSQuick1::quickdef.plwave==wavenum && CSQuick1::quickdef.plgrp==groupnum)
			currfl->SetPressed(true);
	}else
	{
		currfl->ShowWindow(SW_HIDE);
	}
	CRStatic* desc=GETDLGITEM(IDC_GRPDESC);
	desc->SetString(LoadResString(fields->descID));
	CRCombo* combo=GETDLGITEM(IDC_ALT);
	int altind=fields->alt*10/(Save_Data.alt.mediummm*Save_Data.alt.mediumstepsize)-Save_Data.alt.minstepcount;
	if (altind<0)
		altind=0;													  //JIM 14/05/99
	else
		if (altind>=Save_Data.alt.maxstepcount-Save_Data.alt.minstepcount)
			altind=Save_Data.alt.maxstepcount-Save_Data.alt.minstepcount-1; //JIM 14/05/99
	combo->MakeNumList(Save_Data.alt.maxstepcount-Save_Data.alt.minstepcount,
						Save_Data.alt.minstepcount*Save_Data.alt.mediumstepsize,
						Save_Data.alt.mediumstepsize
					)->SetIndex(altind);
	combo=GETDLGITEM(IDC_SKILL);
	combo->RESCOMBO(SKILL_NOVICE,6)->SetIndex(fields->skill/3);

	SetVariableBits();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSQuickLine::SetVariableBits(bool Icanbeplayer)
{	//the input flag set false forces redrawing with player deselected rather than selected
	CRCombo* combo=GETDLGITEM(IDC_TYPE);
	combo->Clear();
	int sqstart,sqcount;
	bool Iamplayer=(	Icanbeplayer 
		&&	packnum==CSQuick1::quickdef.plside
		&&	wavenum==CSQuick1::quickdef.plwave
		&&	groupnum==CSQuick1::quickdef.plgrp	);
	switch (fields->Duty())
	{
	case	Q::QFD_FIGHTER:
	case	Q::QFD_LONE_PLAYER:
		sqstart=SQ_B_FLYABLE;sqcount=5;	break;
	case	Q::QFD_BOMBER_PLAYER_ONLY:
		sqstart=SQ_F80;sqcount=3;	break;
	case	Q::QFD_BOMBER_AUTO_ONLY:
		sqstart=SQ_B_NONFLYABLE;sqcount=2;	break;
	case	Q::QFD_BOMBER_PLAYER_AUTO:
	case	Q::QFD_BOMBER_PLAYER_AUTO_IS_AUTO:
		sqstart=SQ_F80;sqcount=5;	
		if (Iamplayer)	sqcount=3;
		break;
	case	Q::QFD_MIG_PLAYER_ONLY:
	case	Q::QFD_LONE_MIG:
		sqstart=SQ_R_FLYABLE;sqcount=2;	break;
	case	Q::QFD_MIG_PLAYER_AUTO:
	case	Q::QFD_MIG_PLAYER_AUTO_IS_AUTO:
		sqstart=SQ_R_FLYABLE;sqcount=3;	
		if (Iamplayer || RFullPanelDial::incomms)	sqcount=2;
		break;
	case	Q::QFD_MIG_AUTO_ONLY:
	case	Q::QFD_FIXED_PLAYER:
	case	Q::QFD_FIXED_AUTO:
	case	Q::QFD_FIXED_NUM_PLAYER:
	case	Q::QFD_FIXED_NUM_AUTO:
		sqstart=fields->actype;sqcount=1;	break;
	}
	int line=0;
	int min=0;
	if (Iamplayer)
		min=1;
	if (!fields->AllowZero())
		min=1;
	for (int sq=sqstart;sqcount;sq++,sqcount--)
	{
		int avail=CSQuick1::quickdef.SpareFlights(sq);
		if (sq==fields->actype)
			avail+=fields->flights;
		if (avail>=min)
		{
			combo->AddString(RESLIST(SQ_BF_F86A,sq)); 
			aclines[line++]=sq;
		}
	}
	int l;
	for (l=0;l<line;l++)
		breakif (aclines[l]==fields->actype);
	if (l==line)
		assert (l!=line);
	combo->SetIndex(l);


	combo=GETDLGITEM(IDC_FLIGHTS);
	combo->Clear();
	if (	fields->Duty()==Q::QFD_FIXED_NUM_PLAYER 
		||	fields->Duty()==Q::QFD_FIXED_NUM_AUTO
		||	fields->Duty()==Q::QFD_LONE_PLAYER
		||	fields->Duty()==Q::QFD_LONE_MIG
		)
	{
		combo->MakeNumList(1,fields->flights);
		combo->SetIndex(0);
	}
	else
		if (min==0) 
			combo->MakeNumList(CSQuick1::quickdef.SpareFlights(fields->actype)+fields->flights+1,0)
				->SetIndex(fields->flights);
		else
			combo->MakeNumList(CSQuick1::quickdef.SpareFlights(fields->actype)+fields->flights,1)
				->SetIndex(fields->flights-1);
	CRButton* currfl=GETDLGITEM(IDC_PILOTEDFLAG);
	if (Iamplayer)
	{
		currfl->SetPressed(true);
		currfl->SetDisabled(false);
	}
	else
	{
		currfl->SetPressed(false);
		if (CSQuick1::nonplayer[fields->Duty()] || fields->flights==0)
			currfl->SetDisabled(true);
		else
			currfl->SetDisabled(false);
	}
}


BEGIN_MESSAGE_MAP(CSQuickLine, CDialog)
	//{{AFX_MSG_MAP(CSQuickLine)
	ON_WM_CANCELMODE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQuickLine message handlers

BEGIN_EVENTSINK_MAP(CSQuickLine, CDialog)
    //{{AFX_EVENTSINK_MAP(CSQuickLine)
	ON_EVENT(CSQuickLine, IDC_TYPE, 1 /* TextChanged */, OnTextChangedType, VTS_BSTR)
	ON_EVENT(CSQuickLine, IDC_SKILL, 1 /* TextChanged */, OnTextChangedSkill, VTS_BSTR)
	ON_EVENT(CSQuickLine, IDC_FLIGHTS, 1 /* TextChanged */, OnTextChangedFlights, VTS_BSTR)
	ON_EVENT(CSQuickLine, IDC_ALT, 1 /* TextChanged */, OnTextChangedAlt, VTS_BSTR)
	ON_EVENT(CSQuickLine, IDC_PILOTEDFLAG, 1 /* Clicked */, OnClickedPilotedflag, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSQuickLine::OnTextChangedType(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	CRCombo* combo=GETDLGITEM(IDC_TYPE);
	CRButton* but=GETDLGITEM(IDC_PILOTEDFLAG);
	int newtype=aclines[combo->GetIndex()];
	switch (fields->Duty())
	{
	case	Q::QFD_FIGHTER:
	case	Q::QFD_BOMBER_PLAYER_ONLY:
	case	Q::QFD_BOMBER_AUTO_ONLY:
	case	Q::QFD_MIG_PLAYER_ONLY:
	case	Q::QFD_LONE_PLAYER:
	case	Q::QFD_LONE_MIG:
	break;
	case	Q::QFD_BOMBER_PLAYER_AUTO:
	case	Q::QFD_BOMBER_PLAYER_AUTO_IS_AUTO:
		if (newtype>=5)
			fields->SetDuty(Q::QFD_BOMBER_PLAYER_AUTO_IS_AUTO);
		else
			fields->SetDuty(Q::QFD_BOMBER_PLAYER_AUTO);
		break;
	case	Q::QFD_MIG_PLAYER_AUTO:
	case	Q::QFD_MIG_PLAYER_AUTO_IS_AUTO:
		if (newtype>=11)
			fields->SetDuty(Q::QFD_MIG_PLAYER_AUTO_IS_AUTO);
		else
			fields->SetDuty(Q::QFD_MIG_PLAYER_AUTO);
		break;
	case	Q::QFD_MIG_AUTO_ONLY:
	case	Q::QFD_FIXED_PLAYER:
	case	Q::QFD_FIXED_AUTO:
	case	Q::QFD_FIXED_NUM_PLAYER:
	case	Q::QFD_FIXED_NUM_AUTO:
		return;		//should not happen!!!
	}
	//should always be legal, now!
	if (newtype!=fields->actype)
	{
		int availcount=CSQuick1::quickdef.SpareFlights(newtype);
		int oldtype=fields->actype;
		fields->actype=newtype;
		int oldcount=fields->flights;
		fields->flights=0;
		if (oldcount>availcount)
			oldcount=availcount;
		fields->flights=oldcount;
		CSQuick1::quickdef.FixOtherLines(newtype);
		CSQuick1::quickdef.parent->MakeFlightCombo();
	}
	SetVariableBits();
}

void CSQuickLine::OnTextChangedSkill(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	CRCombo* combo=GETDLGITEM(IDC_SKILL);
	fields->skill=combo->GetIndex()*3;
}

void CSQuickLine::OnTextChangedFlights(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	CRCombo* combo=GETDLGITEM(IDC_FLIGHTS);
	bool oldcount=(fields->flights==0);
	if (fields->AllowZero()											  //RDH 03/03/99
		&&	(	packnum!=CSQuick1::quickdef.plside
			||	wavenum!=CSQuick1::quickdef.plwave
			||	groupnum!=CSQuick1::quickdef.plgrp
		)	)
		fields->flights=combo->GetIndex();
	else
		fields->flights=combo->GetIndex()+1;
	CSQuick1::quickdef.FixOtherLines(fields->actype);
	CSQuick1::quickdef.parent->MakeFlightCombo();
	SetVariableBits();
}

void CSQuickLine::OnTextChangedAlt(LPCTSTR text) 
{
	//this is the setup code that needs to be reversed
//	int altind=fields->alt*10/(Save_Data.alt.mediummm*Save_Data.alt.mediumstepsize)-Save_Data.alt.minstepcount;
//	combo->MakeNumList(Save_Data.alt.maxstepcount-Save_Data.alt.minstepcount,
//						Save_Data.alt.mediumstepsize,
//						Save_Data.alt.minstepcount*Save_Data.alt.mediumstepsize
//					)->SetIndex(altind);
	CRCombo* combo=GETDLGITEM(IDC_ALT);
	fields->alt=(combo->GetIndex()+Save_Data.alt.minstepcount)*Save_Data.alt.mediumstepsize
		*Save_Data.alt.mediummm/10+1;
}

void CSQuickLine::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void	CSQuickLine::SetIconPressed(bool turnon)
{
	if (!this)
		return;
	SetVariableBits(turnon);
}
void CSQuickLine::RecalcFlightsCombo(int spares) 
{
	if (!this)
		return;
	SetVariableBits();
}

void CSQuickLine::OnClickedPilotedflag() 
{
	// TODO: Add your control notification handler code here
	if	(!(CSQuick1::quickdef.plside==packnum && CSQuick1::quickdef.plwave==wavenum && CSQuick1::quickdef.plgrp==groupnum))
	{
		CSQuick1::quickdef.line[CSQuick1::quickdef.plside][CSQuick1::quickdef.plwave][CSQuick1::quickdef.plgrp].dialog->SetIconPressed(false);
		CSQuick1::quickdef.plside=packnum;
		CSQuick1::quickdef.plwave=wavenum;
		CSQuick1::quickdef.plgrp=groupnum;
		SetVariableBits();
		CSQuick1::quickdef.parent->MakeFlightCombo();

	}
	else
	{	//turn it back on!
		CRButton* currfl=GETDLGITEM(IDC_PILOTEDFLAG);
		currfl->SetPressed(true);
	}
}

void CSQuickLine::OnDestroy() 
{
	CDialog::OnDestroy();
	fields->dialog=NULL;
	// TODO: Add your message handler code here
	
}
