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

// MissFldr.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "MissFldr.h"
#include "Profile.h"
//#include "Targets.h"
#include "WaveTabs.h"
//#include "Wave.h"
#include "Dossier.h"
#include "rlistbox.h"
#include "General.h"
#include "Damage.h"
#include "Notes.h"
#include "Task.h"
#include "Route.h"
#include "WPShare.h"
#include "WPGround.h"
//#include "WPAAA.h"
//#include "WPAir.h"
#include "Flt_Task.h"
//#include "quikmisn.h"
#include	"node.h"
#include	"text.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"migview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CMissionFolder dialog
//RDialog*	CMissionFolder::displayedprofs[Profile::MAX_PACKS]={0};
CMissionFolder*	CMissionFolder::activedial=NULL;

CMissionFolder::CMissionFolder(CWnd* pParent /*=NULL*/)
	: RowanDialog(CMissionFolder::IDD, pParent)
{
	activedial=this;
	currrow=-1;
	//{{AFX_DATA_INIT(CMissionFolder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void	CMissionFolder::Make()
{
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	if (!activedial)
		main->m_toolbar2.OnClickedMissionFolder();



}

RDialog*	CMissionFolder::MakeProper()
{
	if (!activedial)	   
		return MakeTopDialog(::Place(POSN_MIN,POSN_MAX,0,0),
									DialBox(FIL_MAP_MISSIONFOLDER,new CMissionFolder)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
								);	
	else
		return NULL;
}

void CMissionFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMissionFolder)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_INTELLIGENCE,m_IDC_INTELLIGENCE);
	DDX_Control(pDX,IDC_PROFILE3,m_IDC_PROFILE3);
	DDX_Control(pDX,IDC_FRAG,m_IDC_FRAG);
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_DELETEMISSION,m_IDC_DELETEMISSION);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMissionFolder, CDialog)
	//{{AFX_MSG_MAP(CMissionFolder)
	ON_BN_CLICKED(IDC_PROFILE, OnProfile)
	ON_WM_CANCELMODE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CMissionFolder, CDialog)
    //{{AFX_EVENTSINK_MAP(CMissionFolder)
	ON_EVENT(CMissionFolder, IDC_INTELLIGENCE, 1 /* Clicked */, OnClickedIntelligence, VTS_NONE)
	ON_EVENT(CMissionFolder, IDC_FRAG, 1 /* Clicked */, OnClickedFrag, VTS_NONE)
	ON_EVENT(CMissionFolder, IDC_PROFILE3, 1 /* Clicked */, OnClickedProfile, VTS_NONE)
	ON_EVENT(CMissionFolder, IDC_DELETEMISSION, 1 /* Clicked */, OnClickedDeletemission, VTS_NONE)
	ON_EVENT(CMissionFolder, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMissionFolder message handlers

void CMissionFolder::OnProfile() 
{
	// TODO: Add your control notification handler code here
//	RDialog::MakeTopDialog(CRect(50,50,0,0),
//								DialBox(IDB_MUSTY,new CProfile)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
//							);


//	RDialog::MakeTopDialog(CRect(50,350,0,0),
//		DialList(DialBox(IDB_BLUE,new CWaveTabs,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//								HTabBox(NULL,IdList("BarCAP","Strike F80 (2)","AAA F80 (2)","Escort F80 (2)"),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
//		  							DialBox(IDB_ARTWORK2,MakeRtestsh1()),
//									DialList(DialBox(IDB_STRIKE,new CWave),
//			  							DialBox(IDB_STRIKE,ptargets,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN))),
//									DialBox(IDB_MUSTY,MakeRtestsh1()),
//				  					DialBox(IDB_ESCORT,MakeRtestsh1())
//								)
//					  		)
//					     );
}

void CMissionFolder::ResetHiLight()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);

	if (currrow >= 0)
	{
		if (currrow == Todays_Packages.hipack)
		{
			RDialog::m_pView->SetHiLightInfo(currrow, Todays_Packages.hiwave, 
				Todays_Packages.higroup, Todays_Packages.hiwp);

		}else
		{
 			UniqueID trgtuid = UID_NULL;
			UniqueID wpuid = Todays_Packages[currrow].wave[0].firstwp;
			while  (	(wpuid)
					&&	(wpuid != Todays_Packages.hiwp)
					)

			{
				info_waypoint* w=*Persons2::ConvertPtrUID(wpuid);
				if (Todays_Packages[currrow][0].targettime == w->etas)
					trgtuid = wpuid;
				wpuid=w->nextwp;
			}
			if  (		(wpuid != Todays_Packages.hiwp)
				||	(wpuid == UID_NULL)
			)

				wpuid = trgtuid;

			RDialog::m_pView->SetHiLightInfo(currrow, 0, 0, wpuid);
		}
//
		rlistbox->SetHilightRow(currrow+1);
	}


}

BOOL CMissionFolder::OnInitDialog() 
{
	CDialog::OnInitDialog();

	RDialog* parent=(RDialog*)GetParent();
//	parent->SetMaxSize(CRect(0,0,450,350));


	FillListBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void	CMissionFolder::FillListBox()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(TARGETFIELDWIDTH);
	rlistbox->AddColumn(80);										  //RDH 02/06/99
	rlistbox->AddColumn(60);										  //RDH 02/06/99
	rlistbox->AddColumn(15);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(OBJECTIVE),0);
	rlistbox->AddString(RESSTRING(TASK),1);
	rlistbox->AddString(RESSTRING(TIMEOVERTARGET),2);
	rlistbox->AddString(RESSTRING(FLIGHTS),3);

	int count = -1;
//	for (int col=0;col<4;col++)
//		for (int row=0;row<Profile::MAX_PACKS;row++)
//			rlistbox->AddString("",col);
	for (int i=0;i<Profile::MAX_PACKS;i++)
		if (Todays_Packages.pack[i][0][0].uid)
		{
			FillProfileRow(rlistbox,i);
			count++;
		}
//		else
//			ClearProfileRow(rlistbox,i);
	//Add a dummy entry so that bottom of list is not interpreted as a selection
	// of the last entry
	rlistbox->AddString("",0);

	if (currrow == -1)
	{
		if (	(count > -1)
			&&	(count >= Todays_Packages.hipack)
			)
			currrow = Todays_Packages.hipack;
	}else
	{
		if (count < currrow)
		{
			if (count>0)
				currrow = 0;
			else
				currrow = -1;
			Todays_Packages.hipack = currrow;
		}
	}
	ResetHiLight();

}

void	CMissionFolder::ClearProfileRow(CRListBox* rlistbox,int r)
{
//	CRListBox* rlistbox=GetDlgItem(IDC_RLISTBOXCTRL1);
//	for (int i=0;i<4;i++)
//		rlistbox->ReplaceString("",r+1,i);
}
void	CMissionFolder::FillProfileRow(CRListBox* rlistbox,int i)
{
//	rlistbox->ReplaceString(Todays_Packages.pack[i].packname,i+1,0);

	if (Todays_Packages.pack[i].packagetarget != UID_NULL)
		rlistbox->AddString(GetTargName(Todays_Packages.pack[i].packagetarget),0);
	else
		rlistbox->AddString("",0);
//	sprintf(buffer,"%04x",Todays_Packages.pack[i].packagetarget);
//	rlistbox->ReplaceString(buffer,i+1,1);
	info_airgrp* g=
		*Persons2::ConvertPtrUID(Todays_Packages[i][0][0].uid);
//DEADCODE JIM 10/04/99 	rlistbox->AddString(RESLIST(DUTY_BOMB,g->duty.Evaluate()/8),1);
	rlistbox->AddString(RESLIST(DUTY_BOMB,g->duty.Evaluate()/ACTIONSUBCODEMAX),1);

//	CRListBox* rlistbox=(CRListBox*)this->GetDlgItem(IDC_RLISTBOXCTRL1);
	char buffer[30];
	int t=Todays_Packages.pack[i].wave[0].targettime/60;
	sprintf(buffer,"%02i:%02i",t/60,t%60);
	rlistbox->AddString(buffer,2);
	int totalflights=0;
	for (int wave=0;wave<Profile::MAX_WAVES;wave++)
		for (int group=0;group<Profile::MAX_GROUPS;group++)
		{
			UniqueID u=Todays_Packages.pack[i].wave[wave].group[group].uid;
			if (u)
			{
				info_airgrp* g=*Persons2::ConvertPtrUID(u);
				totalflights+=g->inform.Evaluate();
			}
		}

	sprintf(buffer,"%3i",totalflights/4);
	rlistbox->AddString(buffer,3);
}
void CMissionFolder::OnClickedIntelligence() 
{
	if (currrow>=0)
		MainToolBar().OpenDossier(Todays_Packages[currrow].packagetarget);
//		CTargetDossier::MakeSheet(
//		//CRect(180,180,0,0),
//		Place(POSN_MAX,POSN_MIN,-10,10),
//				Todays_Packages[currrow].packagetarget);

}

void CMissionFolder::OnClickedFrag() 
{
//	m_pView->m_currentpage=1;
//	m_pFrame->HideToolbars();
//	m_pView->m_mapdlg.ShowWindow(SW_HIDE);
//	m_pView->OnChangeToTitle();
	/*
	RDialog* d=
		MakeTopDialog(CRect(50,50,0,0),
				DialList(DialBox(FIL_GAMESETUP_640,new MapFragList),
					DialList(	DialBox(FIL_NULL,new CFrag),
						DialList(	DialBox(FIL_NULL,new EmptyChildWindow),
							DialBox(FIL_NULL,new CFragPilot(0,0,0,0)),
							DialBox(FIL_NULL,new CFragPilot(0,0,0,4)),
							DialBox(FIL_NULL,new CFragPilot(0,0,0,8)),
							DialBox(FIL_NULL,new CFragPilot(0,0,0,12)),
							DialBox(FIL_NULL,new CFragPilot(0,0,1,0)),
							DialBox(FIL_NULL,new CFragPilot(0,0,1,4))
					)	)	)	);
	*/
	RFullPanelDial::SetDefaultPilotPositions();

//rdh 10/1/99	RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
//	FullScreen* fs;
//	fullscreen->SetDefaultPilotPositions();

//	RDialog::m_pView->LaunchFullPane(&RFullPanelDial::singlefrag);
	MainToolBar().OnClickedFrag2();
}

void CMissionFolder::OnClickedProfile() 
{
	if (currrow>=0)
		OpenProfile(currrow);
}

void		CMissionFolder::OpenOneProfile(int row)
{
	if (activedial)
	{
		activedial->OpenProfile(row);

		activedial->currrow = row;
		activedial->FillListBox();			//to update dialog


//		CRListBox* rlistbox;
//		rlistbox=(CRListBox*)activedial->GetDlgItem(IDC_RLISTBOXCTRL1);
//		activedial->FillProfileRow(rlistbox,row);
	}
}
	
void CMissionFolder::OpenProfile(int row) 
{
		Todays_Packages.pack[row].edited = true;

	if (!LoggedChild(row))
	{
		CProfile* p;
		// TODO: Add your control notification handler code here
//		MakeTopDialog(CRect(50+32*(1+row),100+32*(1+row),0,0),
		MakeTopDialog(
//			Place(POSN_CALLER,POSN_CALLER,32*(1+row),-32*(1+row)),
			Place(POSN_CALLER,POSN_CALLER,200,24),

				DialBox(FIL_MAP_PROFILE,p=new CProfile(true, row))//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
					);
		//if this is current package then open current wave and correct tab for curr wp 
		if (Todays_Packages.hiwp)
		{
			info_waypoint* wp;
			int wave, g;
			Profile::GetPackageFromWP(Todays_Packages.hiwp, row, wave, g);
			wp=*Persons2::ConvertPtrUID(Todays_Packages.hiwp);
			if (wp)
				if (wp->applygroup==ENABLE_COMPLEX_VAL)
					p->SetWaveTabs(wave,-1);
				else
					p->SetWaveTabs(wave,wp->applygroup);
			else
			{
				p->SetWaveTabs(0,-1);
				Todays_Packages.hiwp=UID_NULL;
			}

		}else
			p->SetWaveTabs(0,-1);

	LogChild(row,p);
//		displayedprofs[row]=p;
	}
	else	
	{
		LoggedChild(row)->BringWindowToTop();

		CProfile* p = (CProfile*) LoggedChild(row)->fchild;

		if (Todays_Packages.hiwp)
		{
			info_waypoint* wp;
			int wave, g;
			Profile::GetPackageFromWP(Todays_Packages.hiwp, row, wave, g);
			wp=*Persons2::ConvertPtrUID(Todays_Packages.hiwp);
			if (wp->applygroup==ENABLE_COMPLEX_VAL)
				p->SetWaveTabs(wave,-1);
			else
				p->SetWaveTabs(wave,wp->applygroup);

		}else
			p->SetWaveTabs(0,-1);

	}


}	
void	CMissionFolder::ChildDialClosed(int pack,RDialog* dial,int why)
{
		FillListBox();			//to update dialog


//	CRListBox* rlistbox;
//	rlistbox=(CRListBox*)this->GetDlgItem(IDC_RLISTBOXCTRL1);
//
//	FillProfileRow(rlistbox, pack);
}

void	CMissionFolder::RefreshData(int pack)
{
	FillListBox();			//to update dialog

//	CRListBox* rlistbox;
//	rlistbox=(CRListBox*)this->GetDlgItem(IDC_RLISTBOXCTRL1);
  

//	FillProfileRow(rlistbox, pack);
}

void CMissionFolder::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}
void CMissionFolder::RefreshLoggedChildren()
{
	for (int row=0;row<Profile::MAX_PACKS;row++)
		if (LoggedChild(row))
					RefreshChild(row);

}
void CMissionFolder::OnClickedDeletemission() 
{	
	if (currrow>=0)
	{	
		
		int rv = RDialog::RMessageBox(IDS_DELETEMISSION, IDS_AREYOUSURE,NULL,IDS_L_YESNO_YES,IDS_CANCEL);
		if (rv == 1)
		{
			//close windows pointing to current package
			//also close higher numbered packages as this is 
			//the easiest way to handle compacting list
			for (int row=currrow;row<Profile::MAX_PACKS;row++)
				if (LoggedChild(row))
					CloseLoggedChild(row);
			//delete contents of package
			Todays_Packages.ClearPack(currrow);
			//tidy list
			Todays_Packages.ShuntPack(currrow);
			FillListBox();			//to update dialog

		}
		RefreshLoggedChildren();
		m_pView->m_mapdlg.Invalidate();
	}
}

void CMissionFolder::OnButton1() 
{
//	//Create new package instance with primary action
//	int	pack=Todays_Packages.NewPackage();
//	if (pack>=0)
//	{
//		FillProfileRow(pack);
//		//Open dialogs to describe this package
//		OpenProfile(pack);
//	}
}

void CMissionFolder::EndDialog(int v)
{
	CloseLoggedChildren();
	CDialog::EndDialog(v);

	activedial=NULL;
}

void CMissionFolder::OnDestroy() 
{
//	CloseLoggedChildren();
	CDialog::OnDestroy();
	activedial=NULL;
		
}

void CMissionFolder::OnSelectRlistboxctrl1(long row, long column) 
{
	if (row!=0)
		if (Todays_Packages[row-1].wave[0].firstwp)
		{
			if (currrow == (row -1))
			{
				OpenOneProfile(currrow);
			}else
			{
				currrow=row-1;
			}
			ResetHiLight();
		}
		else
		{
			CRListBox* rlistbox;
			rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
			rlistbox->SetHilightRow(currrow+1);
		}
}
