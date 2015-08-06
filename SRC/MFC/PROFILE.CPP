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

// Profile.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "migview.h"
#include "Profile.h"
#include "rlistbox.h"
#include	"bfnumber.h"
#include	"persons2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

CWaveTabs	*CProfile::wavetabs=NULL;
CTaskTabs	*CProfile::tasktabs=NULL;
int			CProfile::wavepack=-1;
int			CProfile::wavegroup=-1;
/////////////////////////////////////////////////////////////////////////////
// CProfile dialog


CProfile::CProfile(bool enable, int package,CWnd* pParent /*=NULL*/)
	: RowanDialog(CProfile::IDD, pParent)
{
	SetProjSpecific(package);
	enableinput = enable;

	//{{AFX_DATA_INIT(CProfile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProfile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfile)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_INSERTWAVENEW,m_IDC_INSERTWAVENEW);
	DDX_Control(pDX,IDC_DELETEWAVENEW,m_IDC_DELETEWAVENEW);
	DDX_Control(pDX,IDC_TASK,m_IDC_TASK);
	DDX_Control(pDX,IDC_ROUTE,m_IDC_ROUTE);
	DDX_Control(pDX,IDC_SAVE,m_IDC_SAVE);
	DDX_Control(pDX,IDJ_TITLE,m_IDJ_TITLE);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfile, CDialog)
	//{{AFX_MSG_MAP(CProfile)
//	ON_WM_DESTROY()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfile message handlers

BEGIN_EVENTSINK_MAP(CProfile, CDialog)
    //{{AFX_EVENTSINK_MAP(CProfile)
	ON_EVENT(CProfile, IDC_PROFILE, 1 /* Clicked */, OnClickedProfile, VTS_NONE)
	ON_EVENT(CProfile, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(CProfile, IDC_INSERTWAVE, 1 /* Clicked */, OnClickedInsertwave, VTS_NONE)
	ON_EVENT(CProfile, IDC_DELETEWAVE, 3 /* OK */, OnOKDeletewave, VTS_NONE)
	ON_EVENT(CProfile, IDC_DELETEWAVE, 1 /* Clicked */, OnClickedDeletewave, VTS_NONE)
	ON_EVENT(CProfile, IDC_DELETEWAVENEW, 1 /* Clicked */, OnClickedDeletewavenew, VTS_NONE)
	ON_EVENT(CProfile, IDC_INSERTWAVENEW, 1 /* Clicked */, OnClickedInsertwavenew, VTS_NONE)
	ON_EVENT(CProfile, IDC_OBJECTIVE, 1 /* Clicked */, OnClickedObjective, VTS_NONE)
	ON_EVENT(CProfile, IDC_CENTRE, 1 /* Clicked */, OnClickedCentre, VTS_NONE)
	ON_EVENT(CProfile, IDC_SAVE, 1 /* Clicked */, OnClickedSave, VTS_NONE)
	ON_EVENT(CProfile, IDC_TASK, 1 /* Clicked */, OnClickedTask, VTS_NONE)
	ON_EVENT(CProfile, IDC_ROUTE, 1 /* Clicked */, OnClickedRoute, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CProfile::OnClickedProfile() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CProfile::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	InDialAncestor()->ModifyStyle(InDialAncestor()->GetStyle(),NULL);
	currrow=1;
	currcol = 1;
   	RDialog* parent=(RDialog*)GetParent();
//	parent->SetMaxSize(CRect(0,0,450,450));

//	wavetabs=NULL;
//	tabswave=-1;
//	m_statics[0].SubclassDlgItem(IDC_STATIC2,this);
//	m_statics[0].SetColour(RGB(0,255,0));
//	m_statics[1].SubclassDlgItem(IDC_STATIC3,this);
//	m_statics[1].SetColour(RGB(0,255,0));
//	m_statics[2].SubclassDlgItem(IDC_STATIC4,this);
//	m_statics[2].SetColour(RGB(0,255,0));

	CRButton* title;
	title = GETDLGITEM(IDJ_TITLE);
	title->SetString(GetTargName(Todays_Packages[packnum].packagetarget));



//	CREdit* e=GetDlgItem(IDC_EDITID);
//	CREdtBt* b;
//	e->SetCaption(Todays_Packages[packnum].packname);
//	b= GetDlgItem(IDC_OBJECTIVE);
//	b->SetCaption(GetTargName(Todays_Packages[packnum].packagetarget));
//	e=(CREdit*)GetDlgItem(IDC_TASK);
//	info_airgrp* a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][0][0].uid);
//	e->SetCaption(RESLIST(DUTY_BOMB,a->duty.Evaluate()));

	CRListBox* rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);

	rlistbox->Clear();
	rlistbox->AddColumn(80);		//Wave
	rlistbox->AddColumn(45);		//Time
	rlistbox->AddColumn(80);		//Attack
	rlistbox->AddString(RESSTRING(WAVE),0);
	rlistbox->AddString(RESSTRING(TIMEOVERTARGET),1);
	rlistbox->AddString(RESSTRING(DUTY),2);
	rlistbox->AddColumn(80);		//AAA cover
	rlistbox->AddColumn(68);		//Air cover

	
	info_airgrp* a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][0][0].uid);
	if (!(a->duty &DA_CAP)) //UI has simple duties
	{
		rlistbox->AddString(RESSTRING(GRNDESCORT),3);
		rlistbox->AddString(RESSTRING(AIRESCORT),4);
	}else
	{
		rlistbox->AddString("",3);
		rlistbox->AddString("",4);

	}


	ReDraw();


//	MakeWaveTabs(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void	CProfile::ReDraw()
{
	maxrows=0;
	for (int row=0;row<Profile::MAX_WAVES;row++)
		if (Todays_Packages[packnum][row][0].uid)
			maxrows++;

	for (row=0;row<maxrows;row++)
		if	(Todays_Packages[packnum][row][0].uid)
			FillWaveRow(row);

//DeadCode RDH 23Dec98 	currrow=row;

	CRListBox* rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->SetHilightRow(currrow);
	rlistbox->SetHilightCol(currcol);



	CRButton*	but = GETDLGITEM(IDC_INSERTWAVENEW);
	if  (		(enableinput)
			&&	(Todays_Packages.FindSquad(Todays_Packages[packnum].duty) >= 0)
		)
	{
		but->SetDisabled(false);
		but->SetForeColor(RGB(255,255,0));
	}
	else
	{
		but->SetDisabled(true);
		but->SetForeColor(RGB(80,80,80));
	}

	but = GETDLGITEM(IDC_DELETEWAVENEW);
	if  (		(enableinput)									//RDH 23Dec98
			&&	(currrow != 1)									//RDH 23Dec98
		)														//RDH 23Dec98
	{
		but->SetDisabled(false);
		but->SetForeColor(RGB(255,255,0));
	}else
	{
		but->SetDisabled(true);
		but->SetForeColor(RGB(80,80,80));
	}

	but = GETDLGITEM(IDC_ROUTE);
	if (enableinput)
	{
		but->SetDisabled(false);
		but->SetForeColor(RGB(255,255,0));
	}else
	{
		but->SetDisabled(true);
		but->SetForeColor(RGB(80,80,80));
	}
	but = GETDLGITEM(IDC_TASK);
	if (enableinput)
	{
		but->SetDisabled(false);
		but->SetForeColor(RGB(255,255,0));
	}else
	{
		but->SetDisabled(true);
		but->SetForeColor(RGB(80,80,80));
	}
//TEMPCODE JIM 31/05/99 	but = GETDLGITEM(IDC_SAVE);
//TEMPCODE JIM 31/05/99 	if (enableinput)
//TEMPCODE JIM 31/05/99 	{
//TEMPCODE JIM 31/05/99 		but->SetDisabled(false);
//TEMPCODE JIM 31/05/99 		but->SetForeColor(RGB(255,255,0));
//TEMPCODE JIM 31/05/99 	}else
//TEMPCODE JIM 31/05/99 	{
//TEMPCODE JIM 31/05/99 		but->SetDisabled(true);
//TEMPCODE JIM 31/05/99 		but->SetForeColor(RGB(80,80,80));
//TEMPCODE JIM 31/05/99 	}

}
void	CProfile::MakeTaskTabs(int wave,int x,int y)
{	
	wavegroup=wave;
	wavepack=packnum;
	info_airgrp* a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wave][0].uid);
//DEADCODE JIM 10/04/99 	int duty = IDS_L_DUTY_BOMB + a->duty.Evaluate()/8;
	int duty = IDS_L_DUTY_BOMB + a->duty.Evaluate()/ACTIONSUBCODEMAX;

	LogChild
	(0,
	MakeTopDialog
//		(CRect(50,400,0,0),
		(Place(POSN_CENTRE,POSN_MIN, 0, 0),

			DialList
			(DialBox
				(FIL_NULL/*IDB_BBC3*/,
					tasktabs = new CTaskTabs,	//CWaveTabs(packnum,wave),
					Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)
				),
				HTabBox
//				(FIL_NULL,IdList(IDS_ATTACK,IDS_GRNDESCORT,IDS_AIRESCORT),
				(FIL_NULL,IdList(duty,IDS_GRNDESCORT,IDS_AIRESCORT),
					Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE),
					DialBox(FIL_MAP_STRIKE/*IDB_STRIKE*/,new CFlt_Task(packnum,wave,0)),
					DialBox(FIL_MAP_AAA/*IDB_BLUE*/,new CFlt_Task(packnum,wave,1)),
					DialBox(FIL_MAP_MIGCAP/*IDB_ESCORT*/,new CFlt_Task(packnum,wave,2))
				
				)
			)
		)
	);
}

void	CProfile::MakeWaveTabs(int wave, int group, int x,int y)
{	
//	typedef	HideEdgeControl	EDGE;
//	tabswave=wave;
	wavegroup=wave;
	wavepack=packnum;
	info_airgrp* a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wave][0].uid);
	int duty = IDS_L_DUTY_BOMB + a->duty.Evaluate()/ACTIONSUBCODEMAX;


	LogChild(1,
	MakeTopDialog
//		(Place(POSN_MAX,POSN_MIN, -40, 40),
			(Place(POSN_MAX,POSN_MAX),
		DialList(DialBox(FIL_NULL/*IDB_BBC3*/,
					wavetabs=new CWaveTabs(packnum,wave),
					Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
			HTabBox(FIL_NULL,IdList(IDS_MAINROUTE,IDS_TARGETAREA1),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE), 
				DialList(DialBox(FIL_MAP_ROUTE,new CRoute(wave,IDD_ROUTEMAIN),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									DialBox(FIL_NULL,new WPDetail(packnum,wave,-1,UID_NULL,IDD_WPMAINDETAIL),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)),
									DialBox(FIL_NULL,new CWPShare(packnum,wave, group),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							),

				HTabBox(FIL_MAP_PAYLOAD,IdList(duty,IDS_GRNDESCORT,IDS_AIRESCORT),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE),
							DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									DialBox(FIL_NULL,new WPDetail(packnum,wave,-1,UID_NULL),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)),
									DialBox(FIL_NULL,new CWPGround(packnum,wave,0),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							),
							DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									DialBox(FIL_NULL,new WPDetail(packnum,wave,-1,UID_NULL),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)),
									DialBox(FIL_NULL,new CWPGround(packnum,wave,1),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							),
							DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									DialBox(FIL_NULL,new WPDetail(packnum,wave,-1,UID_NULL),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)),
									DialBox(FIL_NULL,new CWPGround(packnum,wave,2),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							)
						)
					)
				)
			)
		);


//	wavegroup=wave;
//	wavepack=packnum;
//	LogChild(wave,
//	MakeTopDialog
//		(CRect(550,250,0,0),
//		DialList(DialBox(FIL_NULL/*IDB_BBC3*/,
//					wavetabs=new CWaveTabs(packnum,wave),
//					Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//			HTabBox(FIL_NULL,IdList(IDS_TASK,IDS_SHAREDWPS,IDS_GROUPWP),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE), 
//				HTabBox(FIL_NULL,IdList(IDS_ATTACK,IDS_GRNDESCORT,IDS_AIRESCORT),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE),
//					DialBox(FIL_MAP_STRIKE/*IDB_STRIKE*/,new CFlt_Task(packnum,wave,0)),
//					DialBox(FIL_MAP_AAA/*IDB_BLUE*/,new CFlt_Task(packnum,wave,1)),
//					DialBox(FIL_MAP_MIGCAP/*IDB_ESCORT*/,new CFlt_Task(packnum,wave,2))
//						),
//				DialList(DialBox(FIL_MAP_ROUTE,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new CWPShare(packnum,wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX))	
//							),
//
//				HTabBox(FIL_MAP_ROUTE,IdList(IDS_ATTACK,IDS_GRNDESCORT,IDS_AIRESCORT),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE),
//					DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new CWPGround(packnum,wave,0),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX))	
//							),
//					DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new CWPGround(packnum,wave,1),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX))	
//							),
//					DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new CWPGround(packnum,wave,2),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX))	
//							)
//						)
//					)
//				)
//			)
//		);



//		wavegroup=wave;
//	wavepack=packnum;
//	LogChild(wave,
//	MakeTopDialog
//		(CRect(550,250,0,0),
//		DialList(DialBox(FIL_NULL/*IDB_BBC3*/,
//					wavetabs=new CWaveTabs(packnum,wave),
//					Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//			HTabBox(FIL_NULL,IdList(IDS_TASK,IDS_ROUTE),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE), 
//				HTabBox(FIL_NULL,IdList(IDS_ATTACK,IDS_GRNDESCORT,IDS_AIRESCORT),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE),
//					DialBox(FIL_MAP_STRIKE/*IDB_STRIKE*/,new CFlt_Task(packnum,wave,0)),
//					DialBox(FIL_MAP_AAA/*IDB_BLUE*/,new CFlt_Task(packnum,wave,1)),
//					DialBox(FIL_MAP_MIGCAP/*IDB_ESCORT*/,new CFlt_Task(packnum,wave,2))
//						),
//				HTabBox(FIL_MAP_ROUTE,IdList(IDS_SHAREDWPS,IDS_ATTACK,IDS_GRNDESCORT,IDS_AIRESCORT),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE),
//					DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new CWPShare(packnum,wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX))	
//							),
//					DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new CWPGround(packnum,wave,0),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX))	
//							),
//					DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new CWPGround(packnum,wave,1),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX))	
//							),
//					DialList(DialBox(FIL_NULL,new CRoute(wave),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new CWPGround(packnum,wave,2),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//									DialBox(FIL_NULL,new WaypointButtons(),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX))	
//							)
//						)
//					)
//				)
//			)
//		);


}

void	CProfile::ClearWaveRow(int wave)
{
	CRListBox* rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->ReplaceString("",wave+1,0);
	rlistbox->ReplaceString("",wave+1,1);
	rlistbox->ReplaceString("",wave+1,2);
	rlistbox->ReplaceString("",wave+1,3);
	rlistbox->ReplaceString("",wave+1,4);
}
void	CProfile::FillWaveRow(int wave)
{
	CRListBox* rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->SetNumberOfRows(maxrows+1);
	char buffer[10];
	int uid = (int)Todays_Packages[packnum][wave][0].uid;
	info_airgrp* a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wave][0].uid);
	sprintf(buffer,"%i.%s",wave+1,RESLIST(DUTY_BOMB,a->duty.Evaluate()/ACTIONSUBCODEMAX));
	rlistbox->ReplaceString(buffer,wave+1,0);
	int t=Todays_Packages[packnum][wave].targettime/60;
	sprintf(buffer,"%02i:%02i",t/60,t%60);
	rlistbox->ReplaceString(buffer,wave+1,1);
	int ac = a->inform.Evaluate();
	if (ac)
	{
		sprintf(buffer,"%s (%i)",RESLIST(SQ_BF_F86A,a->type.Evaluate()),a->inform.Evaluate()/4);
		rlistbox->ReplaceString(buffer,wave+1,2);
	}else
		rlistbox->ReplaceString("",wave+1,2);

	a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wave][1].uid);
	if (a)
	{
		sprintf(buffer,"%s (%i)",RESLIST(SQ_BF_F86A,a->type.Evaluate()),a->inform.Evaluate()/4);
		rlistbox->ReplaceString(buffer,wave+1,3);
	}
	else
	{
		rlistbox->ReplaceString("",wave+1,3);
	}
	a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wave][2].uid);
	if (a)
	{
		sprintf(buffer,"%s (%i)",RESLIST(SQ_BF_F86A,a->type.Evaluate()),a->inform.Evaluate()/4);
		rlistbox->ReplaceString(buffer,wave+1,4);
	}
	else
	{
		rlistbox->ReplaceString("",wave+1,4);
	}
}

void CProfile::OnSelectRlistboxctrl1(long row, long column) 
{
	if 	(enableinput)
	{
		if (column >= 2)
		{
			if (row && row<=Profile::MAX_PACKS)
				if	(Todays_Packages[packnum][row-1][0].uid)
				{
					SetTaskTabs(row-1,column-2);
					RDialog::m_pView->SetHiLightInfo(packnum, row-1, column-2, Todays_Packages.hiwp);
				}

		}else
		{
			if (row && row<=Profile::MAX_PACKS)
				if	(Todays_Packages[packnum][row-1][0].uid)
					if (column==0)
						SetWaveTabs(row-1,-1);
					else
						SetWaveTabs(row-1,-1);
		}
		currrow=row;
		currcol=column;
	}
	ReDraw();
}


void	CProfile::ChildDialClosed(int wave,RDialog* r,int code)
{	//User has closed the tabs sheet!
	if (wave==0)
		tasktabs=NULL;
	else if (wave == 1)
		wavetabs=NULL;
//DeadCode RDH 23Dec98 	FillWaveRow(wavegroup);
}
void	CProfile::RefreshData(int child)
{
//	FillWaveRow(wavegroup);
	if (child ==3)	 //
		SetWaveTabs(insertedwav,-1);

	ReDraw();
	if (child!=0 || (CFlt_Task::lastaction&CFlt_Task::REFRESHPARENT))
		RefreshParent();
	if (child==0 && LoggedChild(1) && wavetabs && (CFlt_Task::lastaction&CFlt_Task::REFRESHWPMASK))
		if ((CFlt_Task::lastaction&CFlt_Task::REFRESHWPMASK)==CFlt_Task::REFRESHWPMAIN)
			wavetabs->SelectTab(-1);
		else
				wavetabs->SelectTab((CFlt_Task::lastaction&CFlt_Task::REFRESHWPMASK)-CFlt_Task::REFRESHLOCALWP0);
}

void	CProfile::SetWaveTabs(int wave,int group)
{
	if (wave != wavegroup)
	{
		currrow = wave+1;
		if (	(group >2)	||	(group < 0)	)
			group = -1;

		currcol = group+2;
		ReDraw();

	}
	
	if  (			(wavetabs)
			&& 		(wave!=wavegroup || packnum!=wavepack)
		)
	{
		wavetabs->OnOK();
		wavetabs=NULL;
	}
	if  (			(tasktabs)
			&& 		(wave!=wavegroup || packnum!=wavepack)
		)
	{
		tasktabs->OnOK();
		tasktabs=NULL;
	}
	if (!wavetabs)
	{
		MakeWaveTabs(wave, group);
	}
	wavetabs->SelectTab(group);
}
void	CProfile::SetTaskTabs(int wave,int group)
{
	if  (			(wavetabs)
			&& 		(wave!=wavegroup || packnum!=wavepack)
		)
	{
		wavetabs->OnOK();
		wavetabs=NULL;
	}
	if  (			(tasktabs)
			&& 		(wave!=wavegroup || packnum!=wavepack)
		)
	{
		tasktabs->OnOK();
		tasktabs=NULL;
	}
	if (!tasktabs)
	{
		MakeTaskTabs(wave);
	}
	tasktabs->SelectTab(group);

}


void CProfile::EndDialog( int nResult )
{
//void CProfile::OnDestroy() 
//{
	CloseLoggedChildren();
	if (packnum==wavepack)
	{
//	if (wavetabs && packnum==wavepack)
//	{
//		wavetabs->OnOK();
		wavetabs=NULL;
//	}
//	if (tasktabs && packnum==wavepack)
//	{
//		tasktabs->OnOK();
		tasktabs=NULL;
	}
//	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CDialog::EndDialog(nResult);
	
}

void CProfile::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}


void CProfile::OnClickedInsertwave() 
{
}

void CProfile::OnOKDeletewave() 
{
	// TODO: Add your control notification handler code here
	
}

void CProfile::OnClickedDeletewave() 
{
}

void CProfile::OnClickedDeletewavenew() 
{
	if (currrow)
	{
		int rv = RDialog::RMessageBox(IDS_DELETEWAVE, IDS_AREYOUSURE,NULL,IDS_L_YESNO_YES,IDS_CANCEL);
		if (rv == 1)
		{
			maxrows--;
			if (wavetabs)
				wavetabs->OnOK();
			if (tasktabs)
				tasktabs->OnOK();
			Todays_Packages[packnum].ClearWave(currrow-1);
			Todays_Packages[packnum].ShuntWave(currrow-1);
//DeadCode RDH 23Dec98 			for (int i=currrow;i<maxrows;i++)
//DeadCode RDH 23Dec98 				if	(Todays_Packages[packnum][i][0].uid)
//DeadCode RDH 23Dec98 					FillWaveRow(i);
//DeadCode RDH 23Dec98 			CRListBox* rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 23Dec98 			rlistbox->Invalidate();
			if (currrow>=maxrows)
			{
				currrow=1;										//RDH 23Dec98
//DeadCode RDH 23Dec98 				rlistbox->SetHilightRow(0);
			}
		}
	}
	ReDraw();
}

void CProfile::OnClickedInsertwavenew() 
{
	int wav=0;
	while(wav<Profile::MAX_WAVES && Todays_Packages[packnum][wav].firstwp)
		wav++;
	if (wav==Todays_Packages[packnum][wav].firstwp)
		return;
	info_airgrp* a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][0][0].uid);

	insertedwav = wav;
   	if (a->duty&DA_CAP)
	{
		maxrows++;
		currrow++;
		Todays_Packages[packnum].MakeWave(wav,a->duty);
		Todays_Packages[packnum][wav].targettime = Todays_Packages[packnum][0].targettime; 
//		FillWaveRow(wav);
		ReDraw();
		SetWaveTabs(wav,-1);

	}else
	{
		currrow++;
		typedef	HideEdgeControl	EDGE; 
		if (LoggedChild(3))
			CloseLoggedChild(3);

		LogChild(3,
			RDialog::MakeTopDialog(
				Place(POSN_CALLER,POSN_CALLER,-3,-3),
				DialBox(FIL_MAP_PROFILE,
					new CWaveInsert(packnum,wav,a->duty.Evaluate(),Todays_Packages[packnum][0].targettime) 
		)	)	);		
	}


//	maxrows++;
//	Todays_Packages[packnum][wav].MakeWave(DUTYBOMB);
//	FillWaveRow(wav);
//	SetWaveTabs(wav,-1);
	
}

void CProfile::OnClickedObjective() 
{
	MainToolBar().OpenDossier(Todays_Packages[packnum].packagetarget);
//	CTargetDossier::MakeSheet(CRect(180,180,0,0),Todays_Packages[packnum].packagetarget);
}

void CProfile::OnClickedCentre() 
{
	m_pView->ZoomToUID(UniqueID(Todays_Packages[packnum].packagetarget),m_pView->m_zoom);

}

void CProfile::OnClickedSave() 
{
	typedef	HideEdgeControl	EDGE; 
	CString	wildcard="*.prf";
//	CSaveProf::selectedfile=Save_Data.lastpackname;
	CSaveProf::selectedfile= GetTargName(Todays_Packages[packnum].packagetarget) + ".prf";
	if (LoggedChild(2))
		CloseLoggedChild(2);

	LogChild(2,
			RDialog::MakeTopDialog(Place(POSN_CENTRE,POSN_CENTRE),
								DialList(DialBox(FIL_NULL/*IDB_BBC3*/,new CSaveProf(packnum),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
											DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CLoad(IDD_SAVE,LSD_SAVE,			FIL_USER_PROFILES_DIR,wildcard,CSaveProf::selectedfile))
										)
								  )	
				);
	
}

void CProfile::OnClickedTask() 
{
	// TODO: Add your control notification handler code here
	int col = currcol-2;
	if (col < 0)
		col = 0;
	SetTaskTabs(currrow-1, col);

}

void CProfile::OnClickedRoute() 
{
	SetWaveTabs(currrow-1,-1);
	
}
