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

//////////////////////////////////////////////////////////////////////
//
// Module:      Flt_task.cpp
//
// Created:     01/04/99 by JIM
//
// Description: 
//
//////////////////////////////////////////////////////////////////////
// Flt_Task.cpp : implementation file
//

#include	"stdafx.h"
#include	"mig.h"
#include	"Flt_Task.h"
#include	"RCombo.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"Weapons.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlt_Task dialog
CFlt_Task::Act	CFlt_Task::lastaction=REFRESHNONE;


CFlt_Task::CFlt_Task(int pack,int wave,int group,CWnd* pParent /*=NULL*/)
	: RowanDialog(CFlt_Task::IDD, pParent)
{
	SetProjSpecific(pack,wave,group);
	displayedflights=-1;
	escortishigh=EscortGoHigh()	;
	attackislimit=AttackGoLimit();
	CheckAttackAgainstRules();
	//{{AFX_DATA_INIT(CFlt_Task)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

bool	CFlt_Task::EscortGoHigh()
{
	if (groupnum==0) 
		return false;
	if (!Todays_Packages[packnum][wavenum][groupnum].uid)
		return false;
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	info_airgrp* ag0=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][0].uid);
	return (ag0->type.Evaluate() != ag->type.Evaluate());
}

CFlt_Task::AttackRules	CFlt_Task::AttackGoLimit()
{
	if (groupnum==2 || !Todays_Packages[packnum][wavenum][groupnum].uid)
		return	RULE_HIDDEN;
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag->type.Evaluate()==SQ_B29)
		return	RULE_HIGH;
	if (ag->type.Evaluate()==SQ_B26)
		return	RULE_WIDE;
	for (int i=0;i<4;i++)
		if (ag->bombs.Evaluate(i)<3)
			return RULE_DIVE;
	return RULE_ALL;
}

bool	CFlt_Task::CheckAttackAgainstRules()
{
	if (!Todays_Packages[packnum][wavenum][groupnum].uid)
		return false;
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	bool		rv=false;	//no changes make
	currattackmethod=(AttackType)ag->attmethod.Evaluate();
	currattackpattern=ag->attpattern.Evaluate();
//validate attack method rules
	switch (attackislimit)
	{
	case	RULE_HIDDEN:	//never happens
	case	RULE_DIVE:
		if (currattackmethod!=ATT_DIVE)
		{
			currattackmethod=ATT_DIVE;
			rv=true;
		}
	break;
	case	RULE_ALL:	//no limits
	break;	
	case	RULE_WIDE:
		if (currattackmethod==ATT_DIVE)
		{
			currattackmethod=ATT_LOW;
			rv=true;
		}
		if (currattackpattern!=0)	//wide
		{
			currattackpattern=0;
			rv=true;
		}
	break;
	case	RULE_HIGH:
		if (currattackmethod!=ATT_HIGH)
		{
			currattackmethod=ATT_HIGH;
			rv=true;
		}
		if (currattackpattern!=0)	//wide
		{
			currattackpattern=0;
			rv=true;
		}
	break;
	}
//validate pattern against method
	switch (currattackmethod)
	{
	case ATT_DIVE:
		if (currattackpattern==0)
		{
			currattackpattern=1;
			rv=true;
		}
	break;
	case ATT_HIGH:
		if (currattackpattern!=0)
		{
			currattackpattern=0;
			rv=true;
		}
	break;
	case ATT_LOW:		//no limits not already applied
	break;
	}
	if (rv)
	{
		ag->attpattern=	currattackpattern;
		ag->attmethod=	currattackmethod;
	}
	return rv;
}

void CFlt_Task::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlt_Task)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_ATTACKMETHOD,m_IDC_ATTACKMETHOD);
	DDX_Control(pDX,IDC_GROUPFORM,m_IDC_GROUPFORM);
	DDX_Control(pDX,IDC_FLIGHTFORM,m_IDC_FLIGHTFORM);
	DDX_Control(pDX,IDC_ATTACKPATTERN,m_IDC_ATTACKPATTERN);
	DDX_Control(pDX,IDC_F0WEAPONS,m_IDC_F0WEAPONS);
	DDX_Control(pDX,IDC_TSQUAD,m_IDC_TSQUAD);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_RSTATICCTRL8,m_IDC_RSTATICCTRL8);
	DDX_Control(pDX,IDC_RSTATICCTRL9,m_IDC_RSTATICCTRL9);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_TF0W,m_IDC_TF0W);
	DDX_Control(pDX,IDC_TF0T0,m_IDC_TF0T0);
	DDX_Control(pDX,IDC_F0TARG0,m_IDC_F0TARG0);
	DDX_Control(pDX,IDC_F0TARG1,m_IDC_F0TARG1);
	DDX_Control(pDX,IDC_ACTYPE,m_IDC_ACTYPE);
	DDX_Control(pDX,IDC_F1WEAPONS,m_IDC_F1WEAPONS);
	DDX_Control(pDX,IDC_TF1W,m_IDC_TF1W);
	DDX_Control(pDX,IDC_TF1T0,m_IDC_TF1T0);
	DDX_Control(pDX,IDC_F1TARG0,m_IDC_F1TARG0);
	DDX_Control(pDX,IDC_F1TARG1,m_IDC_F1TARG1);
	DDX_Control(pDX,IDC_F2WEAPONS,m_IDC_F2WEAPONS);
	DDX_Control(pDX,IDC_TF2W,m_IDC_TF2W);
	DDX_Control(pDX,IDC_TF2T0,m_IDC_TF2T0);
	DDX_Control(pDX,IDC_F2TARG0,m_IDC_F2TARG0);
	DDX_Control(pDX,IDC_F2TARG1,m_IDC_F2TARG1);
	DDX_Control(pDX,IDC_F3WEAPONS,m_IDC_F3WEAPONS);
	DDX_Control(pDX,IDC_TF3W,m_IDC_TF3W);
	DDX_Control(pDX,IDC_TF3T0,m_IDC_TF3T0);
	DDX_Control(pDX,IDC_F3TARG0,m_IDC_F3TARG0);
	DDX_Control(pDX,IDC_F3TARG1,m_IDC_F3TARG1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFlt_Task, CDialog)
	//{{AFX_MSG_MAP(CFlt_Task)
//DEADCODE JIM 18/05/99 	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_SELECTTAB, OnSelectTab)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlt_Task message handlers

BOOL CFlt_Task::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (Todays_Packages[packnum][wavenum][groupnum].numflights==0)
		actypebackup=-1;
	else
		actypebackup=Todays_Packages[packnum][wavenum][groupnum].squadron;

	RefreshAll();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CFlt_Task::RefreshAll() 
{
	RefreshParent();
	char buffer[10];
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	SetFlightCount();
	CRCombo* combo;
	CRStatic*   s;
	if (ag)
	{
		s=GETDLGITEM(IDC_RSTATICCTRL9);
		s->ShowWindow(SW_SHOW);
		s=GETDLGITEM(IDC_RSTATICCTRL10);
		s->ShowWindow(SW_SHOW);
		combo=GETDLGITEM(IDC_GROUPFORM);
		combo->ShowWindow(SW_SHOW);
		int currform=(ag->form.Evaluate()-SQUAD_FLATV);
		if (currform<0)
		{
			currform=0;
			ag->form=SQUAD_FLATV;
		}
		combo->
			Clear()->
				RESCOMBO(GROUPFORM_VFORM,8)->
					SetIndex((currform)/4);
		combo=GETDLGITEM(IDC_FLIGHTFORM);
		combo->ShowWindow(SW_SHOW);									  //MS 07/04/99
		if (groupnum==0)
			combo->
				Clear()->
					RESCOMBO(ORIENTATE_ALONE,1)->
						SetIndex(0); //MS 07/04/99
		else
		{
//DEADCODE JIM 28/05/99 			info_airgrp* ag0;
//DEADCODE JIM 28/05/99 			ag0=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][0].uid);

			if (!escortishigh)
			{
				combo->
					Clear()->
						RESCOMBO(ORIENTATE_CLOSE,4)->
							SetIndex((currform)%4); //MS 07/04/99
			}
			else
			{
				combo->
					Clear()->
						RESCOMBO(ESCORTHIGH0,4)->
							SetIndex((currform)%4); //MS 07/04/99
			}

			
		}

		if (!(ag->duty.Evaluate()&DA_CAP))
		{
			combo=GETDLGITEM(IDC_ATTACKMETHOD);
			combo->ShowWindow(SW_SHOW);
			int methodbase=0,methodopts=3;
			switch (attackislimit)
			{
			case	RULE_HIDDEN:							break;
			case	RULE_DIVE:	methodbase=0;methodopts=1;	break;
			case	RULE_ALL:	methodbase=0;methodopts=3;	break;
			case	RULE_WIDE:	methodbase=1;methodopts=2;	break;
			case	RULE_HIGH:	methodbase=2;methodopts=1;	break;
			}
			if (ag->attmethod.Evaluate()!=ENABLE_COMPLEX_VAL)
				combo->Clear()->RESCOMBO(ATTACKMETHOD_DIVE+methodbase,methodopts)->SetIndex(ag->attmethod.Evaluate()-methodbase);
			else
				combo->Clear()->RESCOMBO(NOTIMPOSED,2)->SetIndex(ag->radiosilence);

			combo=GETDLGITEM(IDC_ATTACKPATTERN);
			combo->ShowWindow(SW_SHOW);
			if (ag->attpattern.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				switch (currattackmethod)
				{
				case ATT_DIVE:	{methodbase=1,methodopts=6;		break;	}
				case ATT_LOW: if (attackislimit!=RULE_WIDE)
								{methodbase=0,methodopts=7;		break;	}
				case ATT_HIGH:
								{methodbase=0,methodopts=1;		break;	}
				}
				combo->Clear()->RESCOMBO(ATTACKPATTERN_WIDE+methodbase,methodopts)->SetIndex(currattackpattern-methodbase);
			}
			else
				combo->ShowWindow(SW_HIDE);
			s=GETDLGITEM(IDC_RSTATICCTRL7);
			s->SetString(RESSTRING(ATTACKMETHOD));
			s=GETDLGITEM(IDC_RSTATICCTRL8);
			s->ShowWindow(SW_SHOW);

		}
		else
		{
			combo=GETDLGITEM(IDC_ATTACKMETHOD);
			combo->Clear()->Clear()->RESCOMBO(NOTIMPOSED,2)->SetIndex(ag->radiosilence);
			combo->ShowWindow(SW_SHOW);
			combo=GETDLGITEM(IDC_ATTACKPATTERN);
			combo->ShowWindow(SW_HIDE);

			s=GETDLGITEM(IDC_RSTATICCTRL7);
			s->SetString(RESSTRING(RADIOSILENCE));
			s=GETDLGITEM(IDC_RSTATICCTRL8);
			s->ShowWindow(SW_HIDE);

		}

	}else
	{
			combo=GETDLGITEM(IDC_ATTACKMETHOD);
			combo->ShowWindow(SW_HIDE);
			combo=GETDLGITEM(IDC_ATTACKPATTERN);
			combo->ShowWindow(SW_HIDE);
			combo=GETDLGITEM(IDC_GROUPFORM);
			combo->ShowWindow(SW_HIDE);
			combo=GETDLGITEM(IDC_FLIGHTFORM);
			combo->ShowWindow(SW_HIDE);
			s=GETDLGITEM(IDC_RSTATICCTRL7);
			s->ShowWindow(SW_HIDE);
			s=GETDLGITEM(IDC_RSTATICCTRL8);
			s->ShowWindow(SW_HIDE);
			s=GETDLGITEM(IDC_RSTATICCTRL9);
			s->ShowWindow(SW_HIDE);
			s=GETDLGITEM(IDC_RSTATICCTRL10);
			s->ShowWindow(SW_HIDE);

	}
	FillRow(0,m_IDC_F0WEAPONS,m_IDC_F0TARG0,m_IDC_F0TARG1);
	FillRow(1,m_IDC_F1WEAPONS,m_IDC_F1TARG0,m_IDC_F1TARG1);
	FillRow(2,m_IDC_F2WEAPONS,m_IDC_F2TARG0,m_IDC_F2TARG1);
	FillRow(3,m_IDC_F3WEAPONS,m_IDC_F3TARG0,m_IDC_F3TARG1);
}

void CFlt_Task::OnSelectTab(RDialog* tab)
{
	if (groupnum!=0)
	{
		info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
		info_airgrp* ag0=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][0].uid);

		if (!ag || !ag0)
			return;
		bool	egh=EscortGoHigh();
		if (escortishigh!=egh)
		{
			escortishigh=egh;
			CRCombo* combo;
			combo=GETDLGITEM(IDC_FLIGHTFORM);
			int currform=(ag->form.Evaluate()-SQUAD_FLATV);
			if (currform<0)
				currform=0;
			if (!escortishigh)
			{
				combo->
					Clear()->
						RESCOMBO(ORIENTATE_CLOSE,4)->
							SetIndex((currform)%4); //MS 07/04/99
			}else
			{
				combo->
					Clear()->
						RESCOMBO(ESCORTHIGH0,4)->
							SetIndex((currform)%4); //MS 07/04/99
			}

		}
		
	}


}

void	CFlt_Task::SetFlightCount()
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	CREdtBt* squad=GETDLGITEM(IDC_ACTYPE);
	if (ag!=NULL)
	{
		ULong flights=ag->inform;
		int maxavail=ULong(	Todays_Packages.SquadACAvail(Todays_Packages[packnum][wavenum][groupnum].squadron)
							-Todays_Packages.SquadACUsed(Todays_Packages[packnum][wavenum][groupnum].squadron)
							+flights)/4;
		flights/=4;
//DeadCode DAW 22Jun99 		if (flights!=displayedflights && displayedflights!=-1)
//DeadCode DAW 22Jun99 			RefreshParent();
		displayedflights=flights;
		char buffer[20];
		sprintf(buffer,"%s (%i/%i)",RESLIST(SQ_BF_F86A,Todays_Packages[packnum][wavenum][groupnum].squadron),flights,maxavail);
		squad->SetCaption(buffer);
	}
	else
		squad->SetCaption(RESSTRING(OFFDUTY));
}

BEGIN_EVENTSINK_MAP(CFlt_Task, CDialog)
    //{{AFX_EVENTSINK_MAP(CFlt_Task)
	ON_EVENT(CFlt_Task, IDC_ACTYPE, 1 /* Clicked */, OnClickedActype, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F0TARG0, 1 /* Clicked */, OnClickedF0targ0, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F0WEAPONS, 1 /* Clicked */, OnClickedF0weapons, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F1TARG0, 1 /* Clicked */, OnClickedF1targ0, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F1TARG1, 1 /* Clicked */, OnClickedF1targ1, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F1WEAPONS, 1 /* Clicked */, OnClickedF1weapons, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F2TARG0, 1 /* Clicked */, OnClickedF2targ0, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F2TARG1, 1 /* Clicked */, OnClickedF2targ1, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F2WEAPONS, 1 /* Clicked */, OnClickedF2weapons, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F3TARG0, 1 /* Clicked */, OnClickedF3targ0, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F3TARG1, 1 /* Clicked */, OnClickedF3targ1, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F3WEAPONS, 1 /* Clicked */, OnClickedF3weapons, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_F0TARG1, 1 /* Clicked */, OnClickedF0targ1, VTS_NONE)
	ON_EVENT(CFlt_Task, IDC_ATTACKMETHOD, 1 /* TextChanged */, OnTextChangedAttackmethod, VTS_BSTR)
	ON_EVENT(CFlt_Task, IDC_ATTACKPATTERN, 1 /* TextChanged */, OnTextChangedAttackpattern, VTS_BSTR)
	ON_EVENT(CFlt_Task, IDC_FLIGHTFORM, 1 /* TextChanged */, OnTextChangedFlightform, VTS_BSTR)
	ON_EVENT(CFlt_Task, IDC_GROUPFORM, 1 /* TextChanged */, OnTextChangedGroupform, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void	CFlt_Task::FillRow(int flight,CREdtBt& m_idweap,CREdtBt& m_idprim,CREdtBt& m_idsec)
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
	{
		int flights=ag->inform;
//		int maxavail=(Todays_Packages.SquadACAvail((int)ag->type)-Todays_Packages.SquadACUsed((int)ag->type)+flights)/4;
		int maxavail=ULong(	Todays_Packages.SquadACAvail(Todays_Packages[packnum][wavenum][groupnum].squadron)
							-Todays_Packages.SquadACUsed(Todays_Packages[packnum][wavenum][groupnum].squadron)
							+flights)/4;

		flights/=4;
		if (flights<=flight)
		{
			CREdtBt* weap=GETDLGITEM(idweap);
			if (flight>=maxavail)	//Some test for max available flights
			{
				weap->SetCaption(RESSTRING(NOTAVAIL));
				weap->EnableWindow(FALSE);
			}
			else
			{
				weap->SetCaption(RESSTRING(OFFDUTY));
				weap->EnableWindow(TRUE);
			}
			CREdtBt*	targ=GETDLGITEM(idprim);
			targ->EnableWindow(FALSE);
			targ->SetCaption("");
			targ=GETDLGITEM(idsec);
			targ->EnableWindow(FALSE);
			targ->SetCaption("");
		}
		else
		{
			CREdtBt* weap=GETDLGITEM(idweap);
			int packstr=CWeapons::GetWeapName(packnum,wavenum,groupnum,flight);
			if (packstr==0)
			{
				((info_airgrp*)*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid))->bombs[flight]=0;
				packstr=CWeapons::GetWeapName(packnum,wavenum,groupnum,flight);
			}
			weap->SetCaption(LoadResString(packstr));
			weap->EnableWindow(TRUE);

			CREdtBt*	targ=GETDLGITEM(idprim);
			targ->EnableWindow(TRUE);
			CString	buffer;
			Profile::TargetDescript* t=&Todays_Packages[packnum][wavenum][groupnum][flight].primary;
			int targuid=t->ID;
			if (targuid)
			{
				if (t->SGT==Todays_Packages[packnum].packagetarget && t->band)
					buffer=GetShapeName(ShapeNum(((info_itemS*)Persons2::ConvertPtrUID(UniqueID(targuid)))->shape.Evaluate()));
				else
					buffer=GetTargName((UniqueID)targuid);
			}
			else
				if (t->SGbandindex)
					if (flight)
						buffer=CSprintf("%s + %i %s, %s",RESSTRING(LEADER),t->groupindex,RESLIST(CARDINAL_NORTH,t->SGbandindex));
					else
						buffer=CSprintf("%i %s, %s",t->groupindex,RESLIST(CARDINAL_NORTH,t->SGbandindex));
				else
					if (flight)
						buffer=RESSTRING(LEADERTARGET);
					else
						buffer=RESSTRING(MAINTARGET);
			targ->SetCaption(buffer);
			targ=GETDLGITEM(idsec);
			targ->EnableWindow(TRUE);
			t=&Todays_Packages[packnum][wavenum][groupnum][flight].secondary;
			targuid=t->ID;
			if (targuid)
			{
				if (t->SGT==Todays_Packages[packnum].packagetarget && t->band)
					buffer=GetShapeName(ShapeNum(((info_itemS*)Persons2::ConvertPtrUID(UniqueID(targuid)))->shape.Evaluate()));
				else
					buffer=GetTargName((UniqueID)targuid);
			}
			else
				if (t->SGbandindex)
					if (flight)
						buffer=CSprintf("%s + %i Miles, %s %s",RESSTRING(LEADER),t->groupindex,RESLIST(CARDINAL_NORTH,t->SGbandindex));
					else
						buffer=CSprintf("%i Miles, %s %s",t->groupindex,RESLIST(CARDINAL_NORTH,t->SGbandindex));
				else
					buffer="";
			targ->SetCaption(buffer);
		}
	}
	else
	{
			CREdtBt* weap=GETDLGITEM(idweap);
			weap->SetCaption("");
			weap->EnableWindow(FALSE);
			CREdtBt*	targ=GETDLGITEM(idprim);
			targ->EnableWindow(FALSE);
			targ->SetCaption("");
			targ=GETDLGITEM(idsec);
			targ->EnableWindow(FALSE);
			targ->SetCaption("");
	}
}


void CFlt_Task::OnClickedActype() 
{
	bool oktoopensquadsel = false;
	if (!Todays_Packages[packnum][wavenum][groupnum].uid)
	{	//need to create new group
		if (Todays_Packages[packnum][wavenum].MakeGroup((wavenum==0),groupnum==1) != UID_NULL)
		{
			Todays_Packages[packnum].RecalcSecondaryPositions(wavenum);
			attackislimit=AttackGoLimit();							  //JIM 01/06/99
			CheckAttackAgainstRules();								  //JIM 01/06/99
			RefreshAll();
			oktoopensquadsel = true;
		}
		else
			oktoopensquadsel = false;
	}
	else
		oktoopensquadsel = true;
	if (oktoopensquadsel)
	{
		if (LoggedChild()!=-1)
			CloseLoggedChildren();
		//Open squadron selection screen
		LogChild(0,
		RDialog::MakeTopDialog(
	//	CRect(700,450,0,0),
		Place(POSN_CALLER,POSN_CALLER,100,24),
				DialBox(FIL_MAP_PAYLOAD,new ChooseSquad(packnum,wavenum,groupnum))//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
			));
	}

}

void CFlt_Task::OnClickedF0targ0() 
{
	// TODO: Add your control notification handler code here
	OnClickedTarg0(0);
	
}

void CFlt_Task::OnClickedF0targ1() 
{
	// TODO: Add your control notification handler code here
	OnClickedTarg1(0);
	
}

void CFlt_Task::OnClickedF0weapons() 
{
	// TODO: Add your control notification handler code here
	OnClickedWeapons(0);
}

void CFlt_Task::OnClickedF1targ0() 
{
	// TODO: Add your control notification handler code here
	OnClickedTarg0(1);
	
}

void CFlt_Task::OnClickedF1targ1() 
{
	// TODO: Add your control notification handler code here
	OnClickedTarg1(1);
	
}

void CFlt_Task::OnClickedF1weapons() 
{
	// TODO: Add your control notification handler code here
	OnClickedWeapons(1);
	
}

void CFlt_Task::OnClickedF2targ0() 
{
	// TODO: Add your control notification handler code here
	OnClickedTarg0(2);
	
}

void CFlt_Task::OnClickedF2targ1() 
{
	// TODO: Add your control notification handler code here
	OnClickedTarg1(2);
	
}

void CFlt_Task::OnClickedF2weapons() 
{
	// TODO: Add your control notification handler code here
	OnClickedWeapons(2);
	
}

void CFlt_Task::OnClickedF3targ0() 
{
	// TODO: Add your control notification handler code here
	OnClickedTarg0(3);

}

void CFlt_Task::OnClickedF3targ1() 
{
	// TODO: Add your control notification handler code here
	OnClickedTarg1(3);
	
}

void CFlt_Task::OnClickedF3weapons() 
{
	// TODO: Add your control notification handler code here
	OnClickedWeapons(3);
	
}

void	CFlt_Task::OnClickedWeapons(int flight)
{
	if (LoggedChild()!=-1)
		CloseLoggedChildren();
	acnum=flight*4;
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
	{
		int flights=ag->inform;
		int maxavail=ULong(	Todays_Packages.SquadACAvail(Todays_Packages[packnum][wavenum][groupnum].squadron)
							-Todays_Packages.SquadACUsed(Todays_Packages[packnum][wavenum][groupnum].squadron)
							+flights)/4;
		flights/=4;
		if (flight<maxavail)
		{
			if (flight>=flights)
			{
				//increase all the relevent stats to enable 'flights'
//				ag->inform=ag->inform.Evaluate()+4;
				Todays_Packages[packnum][wavenum][groupnum].SetFlights(flights+1);
				RefreshParent();
				SetFlightCount();
				flight=flights;
				switch (flight)
				{
				case 0:		FillRow(0,m_IDC_F0WEAPONS,m_IDC_F0TARG0,m_IDC_F0TARG1);break;
				case 1:		FillRow(1,m_IDC_F1WEAPONS,m_IDC_F1TARG0,m_IDC_F1TARG1);break;
				case 2:		FillRow(2,m_IDC_F2WEAPONS,m_IDC_F2TARG0,m_IDC_F2TARG1);break;
				case 3:		FillRow(3,m_IDC_F3WEAPONS,m_IDC_F3TARG0,m_IDC_F3TARG1);break;
				}
				lastaction=REFRESHPARENT;
				RefreshParent();
			}
			//do the weapons select screen
			LogChild(1,
				RDialog::MakeTopDialog(
//				CRect(650,400,0,0),
				Place(POSN_CALLER,POSN_CALLER,200,32),

								DialBox(FIL_MAP_PAYLOAD,new CWeapons(packnum,wavenum,groupnum,flight))//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
					)		);		
		}
	}
	//else do nowt
}

void	CFlt_Task::OnClickedTarg0(int flight)
{
	if (LoggedChild()!=-1)
		CloseLoggedChildren();
	acnum=flight*4;
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
	{
		Save_Data.mapfilters%= FILT_MAINWP;
		Save_Data.mapfilters%= FILT_SUBWP;
		CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
		main->m_toolbar1.SetFiltersFromSaveGame();
		m_pView->m_mapdlg.Invalidate();

		int flights=ag->inform;
		flights/=4;
		if (flight<flights)
		{
			//do the target select screen for 'flight primary'
			//LogChild(2,
			//)
			MainToolBar().DialoguesVisible(false);
			LogChild(2,
				RDialog::MakeTopDialog(Place(POSN_CENTRE,POSN_CENTRE),
									DialBox(FIL_MAP_INTELLIGENCE/*IDB_GENERALS*/,new CUserInst(&seltargretval,IDS_SELECTTARGET))
									//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
				)					);




		}
	}
	//else do nowt
}

void	CFlt_Task::OnClickedTarg1(int flight)
{
	if (LoggedChild()!=-1)
		CloseLoggedChildren();
	acnum=flight*4;
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	if (ag!=NULL)
	{
		Save_Data.mapfilters%= FILT_MAINWP;
		Save_Data.mapfilters%= FILT_SUBWP;
		CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
		main->m_toolbar1.SetFiltersFromSaveGame();
		m_pView->m_mapdlg.Invalidate();

		int flights=ag->inform;
		flights/=4;
		if (flight<flights)
		{
			//do the target select screen for 'flight secondary'
			MainToolBar().DialoguesVisible(false);
			LogChild(3,
				RDialog::MakeTopDialog(Place(POSN_CENTRE,POSN_CENTRE),
									DialBox(FIL_MAP_INTELLIGENCE/*IDB_GENERALS*/,new CUserInst(&seltargretval,IDS_SELECTTARGET))//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
				)					);

		}
	}
	//else do nowt
}

void CFlt_Task::OnTextChangedAttackmethod(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	CRCombo* combo;
	combo=GETDLGITEM(IDC_ATTACKMETHOD);
//	FillCombo(combo,IDS_L_ATTACKMETHOD_DIVE,5);
	if (ag!=NULL)
	{
		if (ag->duty.Evaluate()&DA_CAP)
		{
			ag->radiosilence=combo->GetIndex()==1;
		}
		else
		{

			int base=0;
			switch (attackislimit)
			{
			case RULE_HIDDEN:	
			case RULE_DIVE:
			case RULE_ALL:		base=0;			break;
			case RULE_WIDE:		base=1;			break;
			case RULE_HIGH:		base=2;			break;
			}
			ag->attmethod=combo->GetIndex()+base;
			CheckAttackAgainstRules();
			CRCombo* combo=GETDLGITEM(IDC_ATTACKPATTERN);

			switch (currattackmethod)
			{
			case ATT_LOW:	//low level
				if  (Todays_Packages[packnum][wavenum][groupnum].squadron != SQ_B26)
					combo->Clear()->RESCOMBO(ATTACKPATTERN_WIDE,7)->SetIndex(ag->attpattern.Evaluate());
			break;
			case ATT_DIVE:	//dive
				if (ag->attpattern==0)
					ag->attpattern=1;
				combo->Clear()->RESCOMBO(ATTACKPATTERN_SINGLEFILE,6)->SetIndex(ag->attpattern.Evaluate()-1);
			break;
			case ATT_HIGH:	//high level
				combo->Clear()->RESCOMBO(ATTACKPATTERN_WIDE,1)->SetIndex(0);
			break;
			}

		}
	}
	else
		combo->SetCaption("");
}

void CFlt_Task::OnTextChangedAttackpattern(LPCTSTR text) 
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	CRCombo* combo;
	combo=GETDLGITEM(IDC_ATTACKPATTERN);
//	FillCombo(combo,IDS_L_ATTACKMETHOD_DIVE,5);
	if (ag!=NULL)
	{
		if (!ag->attmethod.Evaluate())								  //DAW 12/05/99
			ag->attpattern=combo->GetIndex()+1;
		else
			ag->attpattern=combo->GetIndex();
	}
	else
		combo->SetCaption("");
}

void CFlt_Task::OnTextChangedFlightform(LPCTSTR text) 
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	CRCombo* combo;
	combo=GETDLGITEM(IDC_FLIGHTFORM);
//	FillCombo(combo,IDS_L_ATTACKMETHOD_DIVE,5);
	if (ag!=NULL)
	{
		int currform=ag->form.Evaluate()-SQUAD_FLATV;
		currform &=-4;
		currform+=combo->GetIndex();
		currform+=SQUAD_FLATV;
		ag->form=currform;											  //JIM 26/05/99
	}
	else
		combo->SetCaption("");
	
}

void CFlt_Task::OnTextChangedGroupform(LPCTSTR text) 
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	CRCombo* combo;
	combo=GETDLGITEM(IDC_GROUPFORM);
//	FillCombo(combo,IDS_L_ATTACKMETHOD_DIVE,5);
	if (ag!=NULL)
	{
		int currform=ag->form.Evaluate()-SQUAD_FLATV;
		currform &=3;
		currform+=combo->GetIndex()*4;
		currform+=SQUAD_FLATV;
		ag->form=currform;
	}
	else
		combo->SetCaption("");
}

void CFlt_Task::OnButton1() 
{
}

void CFlt_Task::RefreshData(int datatype)
{
	lastaction=REFRESHNONE;
//DeadCode DAW 22Jun99 	SetFlightCount();
	Profile::TargetDescript* t=&Todays_Packages[packnum][wavenum][groupnum][acnum/4].primary;
	switch (datatype)
	{
	case 0:	//squad select
		if (actypebackup==Todays_Packages[packnum][wavenum][groupnum].squadron)
			lastaction=REFRESHPARENT;
		else
		{
			lastaction=Act(REFRESHWPMAIN+REFRESHPARENT);
		}
		if (Todays_Packages[packnum][wavenum][groupnum].numflights==0)
			actypebackup=-1;
		else
			actypebackup=Todays_Packages[packnum][wavenum][groupnum].squadron;
		SetFlightCount();
		if (attackislimit!=AttackGoLimit())
		{
			attackislimit=AttackGoLimit();
			CheckAttackAgainstRules();
		}
		Todays_Packages[packnum].CountWaypoints();
		RefreshAll();
//DEADCODE RDH 19/06/99 		RDialog::m_pView->SetHiLightInfo(Todays_Packages.hipack, Todays_Packages.hiwave, 
//DEADCODE RDH 19/06/99 				Todays_Packages.higroup, Todays_Packages.hiwp,true);

	break;
	case 3: //secondary target
		t=&Todays_Packages[packnum][wavenum][groupnum][acnum/4].secondary;
	//Fall through!!!
	case 2:	//main target
		t->ID=(UniqueID)seltargretval;
		if (seltargretval)
		{
			info_base*	i=*Persons2::ConvertPtrUID(t->ID);
			if (i->SGT)
			{
//				if (i->SGT!=Todays_Packages[packnum].PackageTarget)
				t->SGT=i->SGT; //doesn't matter which... load/save knows difference
				t->band=Persons2::getbandfromUID(t->ID);
			    t->SGbandindex=Persons2::GetNOfSGTMember(t->SGT,t->band,t->ID);
				Todays_Packages[packnum].ModifyRoute(wavenum,groupnum,acnum);
				Todays_Packages[packnum].CountWaypoints();
			}
			else
			{
				if (seltargretval==Todays_Packages[packnum].packagetarget)
				{
					t->SGT=UID_Null;
					t->band=PilotedAcBAND;
					t->SGbandindex=0;
					Todays_Packages[packnum].ModifyRoute(wavenum,groupnum,acnum);
					Todays_Packages[packnum].CountWaypoints();
				}
				else
				{
					t->SGT=t->ID;
					t->band=PilotedAcBAND;
					t->SGbandindex=0;
					Todays_Packages[packnum].ModifyRoute(wavenum,groupnum,acnum);
					Todays_Packages[packnum].CountWaypoints();
				}
			}
		}
		else
		{
			t->SGT=UID_Null;
			t->band=PilotedAcBAND;
			t->SGbandindex=0;
			Todays_Packages[packnum].ModifyRoute(wavenum,groupnum,acnum);
			Todays_Packages[packnum].CountWaypoints();
		}
		Todays_Packages[packnum].RecalcRoutePositions(); //RDH 15/02/99
		CMissionFolder::Make();
		CMissionFolder::OpenOneProfile(packnum);

	//fall through!!!
	case 1:	//stores select
		if (attackislimit!=AttackGoLimit())
		{
			attackislimit=AttackGoLimit();
			CheckAttackAgainstRules();
			RefreshAll();
		}
		else
			switch (acnum)
			{
			case 0:		FillRow(0,m_IDC_F0WEAPONS,m_IDC_F0TARG0,m_IDC_F0TARG1);break;
			case 4:		FillRow(1,m_IDC_F1WEAPONS,m_IDC_F1TARG0,m_IDC_F1TARG1);break;
			case 8:		FillRow(2,m_IDC_F2WEAPONS,m_IDC_F2TARG0,m_IDC_F2TARG1);break;
			case 12:	FillRow(3,m_IDC_F3WEAPONS,m_IDC_F3TARG0,m_IDC_F3TARG1);break;
			}
		lastaction=Act(REFRESHLOCALWP0+groupnum);
		break;
	}
	RefreshParent();
}
