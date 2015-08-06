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

// WPDetail.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "WPDetail.h"
#include "bfnumber.h"
#include "persons2.h"
#include "ranges.h"
#include "savegame.h"
#include "migview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// WPDetail dialog


WPDetail::WPDetail(int p,int w,int g,int u,int id,CWnd* pParent /*=NULL*/)
	: RowanDialog(id, pParent)
{
	SetProjSpecific(p,w,-1,u);
	wplist=NULL;
	//{{AFX_DATA_INIT(WPDetail)
	//}}AFX_DATA_INIT
}


void WPDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WPDetail)
	DDX_Control(pDX,IDC_SDETAIL2,m_IDC_SDETAIL2);
	DDX_Control(pDX,IDC_SDETAIL4,m_IDC_SDETAIL4);
	DDX_Control(pDX,IDC_SDETAIL6,m_IDC_SDETAIL6);
	DDX_Control(pDX,IDC_FUEL,m_IDC_FUEL);
	DDX_Control(pDX,IDC_ALT,m_IDC_ALT);
//DEADCODE RDH 16/02/99 	DDX_Control(pDX,IDC_ETA_ABS,m_IDC_ETA_ABS);
	DDX_Control(pDX,IDC_NAME,m_IDC_NAME);
	DDX_Control(pDX,IDC_PREV,m_IDC_PREV);
	DDX_Control(pDX,IDC_NEXT,m_IDC_NEXT);
	DDX_Control(pDX,IDC_SDETAIL5,m_IDC_SDETAIL5);
	DDX_Control(pDX,IDC_ETA_REL,m_IDC_ETA_REL);
	DDX_Control(pDX,IDC_ETANONEDIT,m_IDC_ETANONEDIT);
	DDX_Control(pDX,IDC_RSPINETA,m_IDC_RSPINETA);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WPDetail, CDialog)
	//{{AFX_MSG_MAP(WPDetail)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WPDetail message handlers
//void WPDetail::ParentDialClosed(RDialog*,int rv)
//{
//	OnOK();
//}
void WPDetail::ValidateEta()
{
	if (acnum)
	{
//		CREdit* edit;
//		CString	buffer;

//DEADCODE RDH 17/02/99 		edit=GETDLGITEM(IDC_ETA_ABS);
//DEADCODE RDH 17/02/99 		buffer = edit->GetCaption();
//DEADCODE RDH 17/02/99 
//DEADCODE RDH 17/02/99 		Profile::ValidateTime(&buffer, packnum, wavenum);
	}
}
void WPDetail::UpdateEtasAndFuel()
{
	if (acnum)
	{
		info_waypoint* w=*Persons2::ConvertPtrUID(UniqueID(acnum));
		if (w)	//has been 0 in the past so more protectionDAW 12/11/1998
			if (Todays_Packages[packnum][wavenum].targettime == w->etas)
				ValidateEta();
	}

}
void WPDetail::FillSpinBut(int t)
{
	CRSpinBut* spinbut;
	spinbut=GETDLGITEM(IDC_RSPINETA);
	
	
	spinbut->Clear();
	int h =  startperiod;
	int m = 0;
	m = h % 60;
	h = h/60;
	int steps = 32;
	int index = (t - startperiod )/stepsize;
	if (index < 0)
		index = 0;
	if (index >= steps)
		index = steps-1;
	
	while(steps--)
		{
		char buffer[10];
		spinbut->AddString(CSprintf("%02i.%02i",h,m));
		m+=stepsize;
		if (m == 60)
		{
			m = 0;
			h++;
		}
	}
	spinbut->SetIndex(index);


}


void WPDetail::RefreshEtasAndFuel()
{
	info_waypoint* w=*Persons2::ConvertPtrUID(UniqueID(acnum));
	if (		(w->applyflight != ENABLE_COMPLEX_VAL)
			&&	(		(w->applyflight > 0)
					||	(		(w->applyelt != ENABLE_COMPLEX_VAL)
							&&	(w->applyelt > 0)
						 )
				 )
	   )
	{

			CRStatic* s;
			s=GETDLGITEM(IDC_FUEL);
			s->SetString(RESSTRING(NA));
			s=GETDLGITEM(IDC_ETANONEDIT);
			s->SetString(RESSTRING(NA));
			s=GETDLGITEM(IDC_ETA_REL);
			s->SetString(RESSTRING(NA));

	}else
	{
		int t = w->etas/60;
		char buffer[30];
		char bufferrel[30];

		sprintf(buffer,"%02i:%02i",t/60,t%60);

		t-=Todays_Packages[packnum][wavenum].targettime/60;
		if (t>=0)
			sprintf(bufferrel,"+%02i:%02i",t/60,t%60);
		else
			sprintf(bufferrel,"-%02i:%02i",-t/60,-t%60);

		CRStatic*   seta=GETDLGITEM(IDC_ETANONEDIT);
//DEADCODE RDH 16/02/99 		CREdit* edit=GETDLGITEM(IDC_ETA_ABS);
		CRSpinBut* spinbut;
		spinbut=GETDLGITEM(IDC_RSPINETA);

		//prep spin but


		if (Todays_Packages[packnum][wavenum].targettime == w->etas)
		{
//DEADCODE RDH 16/02/99 			edit->ShowWindow(SW_SHOW);
			spinbut->ShowWindow(SW_SHOW);
			seta->ShowWindow(SW_HIDE);
//DEADCODE RDH 16/02/99 			edit->SetWindowText(buffer);
		}else
		{
//DEADCODE RDH 16/02/99 			edit->ShowWindow(SW_HIDE);
			spinbut->ShowWindow(SW_HIDE);
			seta->ShowWindow(SW_SHOW);
			seta->SetString(buffer);
		}
		CRStatic*   s=GETDLGITEM(IDC_ETA_REL);
		s->SetString(bufferrel);
		FillSpinBut(w->etas/60);

		if (w->applygroup == GOT_UNDEFINED_VAL)
		{
			int fuel;
			CRStatic* sfuel=GETDLGITEM(IDC_FUEL);
			if (Todays_Packages[packnum][wavenum].group[0].squadron < SQ_B_NONFLYABLE)
			{
				Todays_Packages[packnum].CalcFuel(wavenum,0,UniqueID(acnum), fuel);
				sfuel->SetString(CSprintf("%5i%s",fuel/ (100*Save_Data.mass.gm), LoadResString(Save_Data.mass.abbrtype)));
			}else
			{
				sfuel->SetString(RESSTRING(NA));
			}

			info_airgrp* ag1=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][1].uid);
			sfuel=GetDlgItem(IDC_FUEL2);
			if (sfuel)
			{
				if ((ag1) && (Todays_Packages[packnum][wavenum].group[1].squadron < SQ_B_NONFLYABLE))
				{
					Todays_Packages[packnum].CalcFuel(wavenum,1,UniqueID(acnum), fuel);
					sfuel->SetString(CSprintf("%5i%s",fuel/ (100*Save_Data.mass.gm), LoadResString(Save_Data.mass.abbrtype)));
				}else
				{
					sfuel->SetString(RESSTRING(NA));
				}
			}  
			info_airgrp* ag2=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][2].uid);
			sfuel=GetDlgItem(IDC_FUEL3);
  
			if (sfuel)
			{
				if ((ag2) && (Todays_Packages[packnum][wavenum].group[2].squadron < SQ_B_NONFLYABLE))
				{
					Todays_Packages[packnum].CalcFuel(wavenum,2,UniqueID(acnum), fuel);
					sfuel->SetString(CSprintf("%5i%s",fuel/ (100*Save_Data.mass.gm), LoadResString(Save_Data.mass.abbrtype)));
				}else
				{
					sfuel->SetString(RESSTRING(NA));
				}
			}
		}else
		{
			int fuel;
			CRStatic* sfuel;
			sfuel=GETDLGITEM(IDC_SDETAIL6);
			sfuel->SetString(LoadResString((int)IDS_FUELLEFT+(int)w->applygroup));
			
			sfuel=GETDLGITEM(IDC_FUEL);
			if (	(Todays_Packages[packnum][wavenum].group[w->applygroup].squadron >= SQ_B_NONFLYABLE)

				)
			{
				sfuel->SetString(RESSTRING(NA));
			}else
			{
				Todays_Packages[packnum].CalcFuel(wavenum,w->applygroup,UniqueID(acnum), fuel);
				sfuel->SetString(CSprintf("%5i%s",fuel/ (100*Save_Data.mass.gm), LoadResString(Save_Data.mass.abbrtype)));
			}

		}
	}
}
void WPDetail::RefreshData(int sender)
{
		//CRSpinBut* spinbut;
		//spinbut=GETDLGITEM(IDC_RSPINBUTETA);
		//spinbut->Clear();  //->MakeNumList(24,0,1)->SetIndex(2);

	if (wplist==NULL)
		for (wplist=(RowanDialog*)parent->fchild;wplist;wplist=(RowanDialog*)wplist->sibling)
			breakif(wplist->packnum!=-1 && wplist!=this);

	if (sender==0)
	{	//sender is list
		if (acnum)
		{
			info_waypoint* w=*Persons2::ConvertPtrUID(UniqueID(acnum));
			CREdtBt* b;
			b=GETDLGITEM(IDC_NAME);
			b->SetCaption(GetAreaName(w));
			CRStatic*   alt=GETDLGITEM(IDC_SDETAIL2);
			CRCombo* combo=GETDLGITEM(IDC_ALT);
			combo->Clear();
			int altind=(w->World.Y*10+ (Save_Data.alt.mediummm*Save_Data.alt.mediumstepsize)/2)/(Save_Data.alt.mediummm*Save_Data.alt.mediumstepsize)-Save_Data.alt.minstepcount;
			if (altind <0)
				altind = 0;
			if (altind >= (Save_Data.alt.maxstepcount - Save_Data.alt.minstepcount))
				altind = Save_Data.alt.maxstepcount - Save_Data.alt.minstepcount - 1;
			combo->MakeNumList(Save_Data.alt.maxstepcount-Save_Data.alt.minstepcount,
						Save_Data.alt.minstepcount*Save_Data.alt.mediumstepsize,
						Save_Data.alt.mediumstepsize
					)->SetIndex(altind);

//DEADCODE RDH 25/04/99 			combo->AddString(RESSTRING(GROUND));
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 			if (LoadResString(IDS_SHORT_ALT_ABBR)[0]==LoadResString(IDS_M_SH)[0])
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 			{
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 				combo->MakeNumList(80,200,200);						  //RDH 19/03/99
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 				combo->SetIndex(w->World.Y/METRES200);
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 			}else
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 			{
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 				combo->MakeNumList(100,500,500);					  //RDH 19/03/99
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 				if (w->World.Y/FT_500 < 100)
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 					combo->SetIndex(w->World.Y/FT_500);
//DEADCODE RDH 25/04/99 //DEADCODE DAW 25/04/99 			}
			alt->SetString(CSprintf("%s, %s", RESSTRING(ALTITUDE), LoadResString(Save_Data.alt.mediumabbr)));

			
			
//			combo=GetDlgItem(IDC_VELOCITY);
//			combo->Clear();
//			combo->AddString(RESSTRING(CRUISE));
//			combo->MakeNumList(14,100,50);
//			if (w->vel.Evaluate()<=0)
//				combo->SetIndex(0);
//			else
//				combo->SetIndex(w->vel/250-1);
			RefreshEtasAndFuel();
		}
	}
	else
	{	//sender is radio button so equivalent to close!
		UpdateEtasAndFuel();
	}
}

BEGIN_EVENTSINK_MAP(WPDetail, CDialog)
    //{{AFX_EVENTSINK_MAP(WPDetail)
	ON_EVENT(WPDetail, IDC_ALT, 1 /* TextChanged */, OnTextChangedAlt, VTS_BSTR)
	ON_EVENT(WPDetail, IDC_NAME, 1 /* Clicked */, OnClickedName, VTS_NONE)
	ON_EVENT(WPDetail, IDC_NEXT, 1 /* Clicked */, OnClickedNext, VTS_NONE)
	ON_EVENT(WPDetail, IDC_PREV, 1 /* Clicked */, OnClickedPrev, VTS_NONE)
	ON_EVENT(WPDetail, IDC_RSPINETA, 1 /* TextChanged */, OnTextChangedRspineta, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void WPDetail::OnTextChangedAlt(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	info_waypoint* w=*Persons2::ConvertPtrUID(UniqueID(acnum));
	CRCombo* combo=GETDLGITEM(IDC_ALT);
	w->World.Y=(combo->GetIndex()+Save_Data.alt.minstepcount)*Save_Data.alt.mediumstepsize
	*Save_Data.alt.mediummm/10+1;

//DEADCODE rdh 25/04/99 	if (LoadResString(IDS_SHORT_ALT_ABBR)[0]==LoadResString(IDS_M_SH)[0])
//DEADCODE rdh 25/04/99 		w->World.Y=combo->GetIndex()*METRES200;
//DEADCODE rdh 25/04/99 	else
//DEADCODE rdh 25/04/99 		w->World.Y=combo->GetIndex()*FT_500;

	Coords3D c=w->World;
	if (w->target.Evaluate()!=ENABLE_COMPLEX_VAL)
		c-=Persons2::ConvertPtrUID(UniqueID(w->target.Evaluate()));
	w->position.RecalcDeltasToMatch(c);
//DEADCODE DAW 17/06/99 	wplist->RefreshData(DATA);
	Todays_Packages[packnum].CalcWPTimes(wavenum);
	wplist->RefreshData(DATA);										  //DAW 17/06/99


}

void WPDetail::OnClickedName() 
{
	// TODO: Add your control notification handler code here
	RDialog::m_pView->ZoomToUID(UniqueID(acnum),RDialog::m_pView->m_zoom);


}

//void WPDetail::OnTextChangedVelocity(LPCTSTR text) 
//{
//	// TODO: Add your control notification handler code here
//	info_waypoint* w=*Persons2::ConvertPtrUID(UniqueID(acnum));
//	CRCombo* combo=GETDLGITEM(IDC_VELOCITY);
//	int ind=combo->GetIndex();
//	if (ind)
//		w->vel=ind*250;
//	else
//		w->vel=ENABLE_COMPLEX_VAL;
//	wplist->RefreshData(DATA);
//}


BOOL WPDetail::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//set up the spin button data
	if	(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
	{
		if (MMC.debrief.currperiod == 0)
			startperiod = MORNINGPERIODSTART;
		if (MMC.debrief.currperiod == 1)
			startperiod = MIDDAYPERIODSTART;
		if (MMC.debrief.currperiod == 2)
			startperiod = AFTERNOONPERIODSTART;
	}else
	{
		startperiod =  Todays_Packages[packnum][wavenum].targettime - (80*SECSPERMIN);
	}
 	startperiod = startperiod/SECSPERMIN;
	stepsize = 5;
	steps = 32;


	RefreshData(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void WPDetail::OnDestroy() 
{
	UpdateEtasAndFuel();
	CDialog::OnDestroy();
	
}

void WPDetail::OnClickedPrev() 
{
	// TODO: Add your control notification handler code here
	UpdateEtasAndFuel();
	wplist->RefreshData(PREV);	
}

void WPDetail::OnClickedNext() 
{
	// TODO: Add your control notification handler code here
	UpdateEtasAndFuel();
	wplist->RefreshData(NEXT);	
	
}

void WPDetail::OnTextChangedRspineta(LPCTSTR text) 
{
		CRSpinBut* spinbut;
		spinbut=GETDLGITEM(IDC_RSPINETA);
		int index = spinbut->GetIndex();
		
		Todays_Packages[packnum][wavenum].targettime 
			= (stepsize * index + startperiod) * 60;
		Todays_Packages[packnum].CalcWPTimes(wavenum);
		wplist->RefreshData(DATA);									  //RDH 17/06/99
		RefreshParent();
}
