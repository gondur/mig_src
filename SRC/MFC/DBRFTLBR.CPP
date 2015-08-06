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

// DbrfTlbr.cpp : implementation file
//
#include "stdafx.h"
#include "mig.h"
#include "DbrfTlbr.h"
#include "Maintbar.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CDebriefToolbar dialog


CDebriefToolbar::CDebriefToolbar(CWnd* pParent /*=NULL*/)
	: CRToolBar(pParent)
{
	//{{AFX_DATA_INIT(CDebriefToolbar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDebriefToolbar::DoDataExchange(CDataExchange* pDX)
{
	CRToolBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebriefToolbar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_DIS,m_IDC_DIS);
	DDX_Control(pDX,IDC_PLAYERLOG,m_IDC_PLAYERLOG);
	DDX_Control(pDX,IDC_OVERVIEW,m_IDC_OVERVIEW);
	DDX_Control(pDX,IDC_MISSIONRESULTS,m_IDC_MISSIONRESULTS);
	DDX_Control(pDX,IDC_BORDER3,m_IDC_BORDER3);
	DDX_Control(pDX,IDC_NEXT_PERIOD,m_IDC_NEXT_PERIOD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebriefToolbar, CRToolBar)
	//{{AFX_MSG_MAP(CDebriefToolbar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebriefToolbar message handlers

BEGIN_EVENTSINK_MAP(CDebriefToolbar, CRToolBar)
    //{{AFX_EVENTSINK_MAP(CDebriefToolbar)
	ON_EVENT(CDebriefToolbar, IDC_MISSIONRESULTS, 1 /* Clicked */, OnClickedMissionresults, VTS_NONE)
	ON_EVENT(CDebriefToolbar, IDC_PLAYERLOG, 1 /* Clicked */, OnClickedPlayerlog, VTS_NONE)
	ON_EVENT(CDebriefToolbar, IDC_DIS, 1 /* Clicked */, OnClickedDis, VTS_NONE)
	ON_EVENT(CDebriefToolbar, IDC_NEXT_PERIOD, 1 /* Clicked */, OnClickedNextPeriod, VTS_NONE)
	ON_EVENT(CDebriefToolbar, IDC_OVERVIEW, 1 /* Clicked */, OnClickedOverview, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDebriefToolbar::OpenMissionresults() 
{
	if (!LoggedChild(CMainToolbar::RESULTS))
	{
		OnClickedMissionresults();
		((CRButton*)GetDlgItem(CMainToolbar::dialids[CMainToolbar::RESULTS]))->SetPressed(TRUE);
	}else
		LoggedChild(CMainToolbar::RESULTS)->BringWindowToTop();
}



void CDebriefToolbar::OnClickedMissionresults() 
{
	if (!LoggedChild(CMainToolbar::RESULTS))
		LogChild(CMainToolbar::RESULTS,
			RDialog::MakeTopDialog(
//			CRect(140,140,0,0),
			Place(POSN_MAX,POSN_MAX, -10, -10),
								DialBox(FIL_MAP_MISSIONRESULTS,new CMResult)
				)					);	
	else
		CloseLoggedChild(CMainToolbar::RESULTS);
}

void CDebriefToolbar::OnClickedPlayerlog() 
{

	typedef	HideEdgeControl	EDGE; 
	if (!LoggedChild(CMainToolbar::PLAYERLOG))
	{
		LogChild(CMainToolbar::PLAYERLOG,
			RDialog::MakeTopDialog(Place(POSN_MAX,POSN_MIN,-10,10),
								DialList(DialBox(FIL_NULL/*IDB_BBC3*/,new CPlyr_log,EDGES_NOSCROLLBARS), //rdh
									HTabBox(FIL_NULL,IdList(IDS_CAREER,IDS_MISSIONLOG, IDS_LASTMISSION),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
			  							DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CCareer),
			  							DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CMisn_log),
										DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CLastMissionLog)
										
//rdh		  								DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CMisntext)
				)					)	)	);
	}else
		CloseLoggedChild(CMainToolbar::PLAYERLOG);



}

void CDebriefToolbar::OnClickedDis() 
{
	if (!LoggedChild(CMainToolbar::DIS))
	{
		CloseLoggedChildren();
		LogChild(CMainToolbar::DIS,
			RDialog::MakeTopDialog(
			//CRect(80,80,0,0),
			Place(POSN_MIN,POSN_MIN),
									DialBox(FIL_MAP_INTELLIGENCE/*IDB_GENERALS*/,new CDIS)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
				)					);
	}
	else
		CloseLoggedChild(CMainToolbar::DIS);
//	MainToolBar().OnClickedDis(); 

}
//CloseLoggedChildren

void CDebriefToolbar::OnClickedOverview() 
{
	typedef	HideEdgeControl	EDGE; 
	if (!LoggedChild(CMainToolbar::OVERVIEW))
		LogChild(CMainToolbar::OVERVIEW,
			RDialog::MakeTopDialog(
			//CRect(180,180,0,0),
			Place(POSN_MIN,POSN_MIN),
								DialList(DialBox(FIL_NULL/*IDB_BBC3*/,new COverview,EDGES_NOSCROLLBARS),
									HTabBox(FIL_NULL,IdList(IDS_ACSTATS,IDS_GROUNDSTATS),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
										DialBox(FIL_MAP_OVERVIEW/*IDB_BBC3*/,new CAC_view),
										DialBox(FIL_MAP_OVERVIEW/*IDB_BBC3*/,new CGrndview)//,
		//								DialBox(FIL_MAP_OVERVIEW/*IDB_BBC3*/,new CCmbtview)
				)					)	)	);
	else
		CloseLoggedChild(CMainToolbar::OVERVIEW);
  
//	PosnControl x = POSN_MIN;
//	PosnControl y = POSN_MIN;
//	MainToolBar().LaunchOverview(x, y);
}

void CDebriefToolbar::OnClickedNextPeriod() 
{
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();

	CRButton*	but = GETDLGITEM(IDC_NEXT_PERIOD);
	but->SetPressed(FALSE);		//always lift next period, might have been pressed

	MMC.indebrief = FALSE;

	if  (		(RFullPanelDial::incomms)
			&&	(_DPlay.UIPlayerType!=PLAYER_HOST)
		)
	{
		if	(_DPlay.Side)
			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::readyroomguestcampaign);	 //RDH 03/04/99
		else
			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::readyroomguestcampaignred);	 //RDH 03/04/99
	}else
	{
	 	Save_Data.mapfilters |= FILT_MAINWP;
		Save_Data.mapfilters |= FILT_SUBWP;
		main->m_toolbar1.SetFiltersFromSaveGame();
		m_pView->m_mapdlg.Invalidate();

//DEADCODE RDH 12/06/99 		main->m_titlebar.Redraw();

		MMC.EndDebrief();
		main->m_titlebar.Redraw();									  //RDH 12/06/99
		bool  campend = MMC.ChkEndCampaign();
//DEADCODE RDH 28/06/99 		Persons4::StartUpMapWorld();
		if (MMC.Active_Pilots[MMC.playersquadron*24+MMC.playeracnum].status >= IS_DEAD)
			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::deadpilot);
		else if (campend)
		{
			if	(		(RFullPanelDial::gamestate != RFullPanelDial::WAR)
					||	(!MMC.wincamp)
					||	(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
				)
				RDialog::m_pView->LaunchFullPane(&RFullPanelDial::endcamp);
			else
				RDialog::m_pView->LaunchFullPane(&RFullPanelDial::warendcamp);
		}
		else if (MMC.msgwithsmacker)
		{
			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::specialdebrief);

		}else
		{
	 		CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
			pmainwnd->UpdateToolbars();
			CloseLoggedChildren();
			if  (		(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
					
				)
			{
		//		CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
		//		pmainwnd->m_toolbar2.OnClickedDirectives();
				if	(MMC.directives.autodisplay)
					MainToolBar().OpenDirectives();	

			}else
				MainToolBar().OpenDis();
		}
	}
}
void CDebriefToolbar::ChildDialClosed(int dialnum,RDialog*,int rv)
{
	CRButton* b=(CRButton*)GetDlgItem(CMainToolbar::dialids[dialnum]);
	b->SetPressed(FALSE);
	//delete b;
}
