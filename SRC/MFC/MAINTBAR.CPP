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

// MainTbar.cpp : implementation file
//

#include "stdafx.h"
#include "MainTbar.h"
#include "MIGView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainToolbar dialog


CMainToolbar::CMainToolbar(CWnd* pParent /*=NULL*/)
	: CRToolBar(pParent)
{
	//{{AFX_DATA_INIT(CMainToolbar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainToolbar::DoDataExchange(CDataExchange* pDX)
{
	CRToolBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainToolbar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
			DDX_Control(pDX,IDC_FRAG2,m_IDC_FRAG2);

	//}}AFX_DATA_MAP
	for (int id=0;id<MAX_ID;id++)
		if (dialids[id])
		{
			DDX_Control(pDX,	dialids[id],	m_dialids[id]);		
		}

}


BEGIN_MESSAGE_MAP(CMainToolbar, CRToolBar)
	//{{AFX_MSG_MAP(CMainToolbar)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainToolbar message handlers

BEGIN_EVENTSINK_MAP(CMainToolbar, CRToolBar)
    //{{AFX_EVENTSINK_MAP(CMainToolbar)
	ON_EVENT(CMainToolbar, IDC_CHANGE_TO_TITLE, 1 /* Clicked */, OnClickedChangeToTitle, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_AUTHORISE, 1 /* Clicked */, OnClickedAuthorise, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_BASES, 1 /* Clicked */, OnClickedBases, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_DIRECTIVES, 1 /* Clicked */, OnClickedDirectives, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_MISSIONRESULTS, 1 /* Clicked */, OnClickedMissionresults, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_OVERVIEW, 1 /* Clicked */, OnClickedOverview, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_PLAYERLOG, 1 /* Clicked */, OnClickedPlayerlog, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_SQUADS, 1 /* Clicked */, OnClickedSquads, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_WEATHER, 1 /* Clicked */, OnClickedWeather, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_DIS, 1 /* Clicked */, OnClickedDis, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_MISSION_FOLDER, 1 /* Clicked */, OnClickedMissionFolder, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_AUTHORISE11, 1 /* Clicked */, OnClickedAuthorise11, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_FRAG2, 1 /* Clicked */, OnClickedFrag2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
int CMainToolbar::dialids[]={
		IDC_AUTHORISE,IDC_BASES,IDC_DIRECTIVES,IDC_MISSIONRESULTS,IDC_OVERVIEW,
		IDC_PLAYERLOG,IDC_SQUADS,IDC_WEATHER,IDC_DIS,IDC_MISSION_FOLDER, //RDH 03/04/99
		NULL/*DOSSIER*/,NULL/*LOADPROF*/,NULL/*ARMY*/};



void CMainToolbar::OnClickedChangeToTitle() 
{
	m_pView->m_currentpage=1;
	m_pFrame->HideToolbars();
	m_pView->m_mapdlg.ShowWindow(SW_HIDE);
	m_pView->OnChangeToTitle();
}

void CMainToolbar::OnClickedAuthorise() 
{
	typedef	HideEdgeControl	EDGE; 
	if (!LoggedChild(AUTHORISE))
		LogChild(AUTHORISE,
			RDialog::MakeTopDialog(Place(POSN_CENTRE,POSN_CENTRE),
								DialList(DialBox(FIL_NULL,new CAuthorise,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									HTabBox(FIL_NULL,IdList(IDS_SUPPLY,IDS_CHOKE,IDS_TRAFFIC,IDS_AIRFIELDS,IDS_ARMY),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
		  								DialBox(FIL_MAP_SUPPLY,new CSupply(SupplyTree::I_SUPPLY)),
		  								DialBox(FIL_MAP_CHOKEPOINTS,new CSupply(SupplyTree::I_CHOKE)), //CChoke
		  								DialBox(FIL_MAP_TRAFFIC,new CSupply(SupplyTree::I_TRAFFIC)),	//CTraffic
										DialBox(FIL_MAP_AIRFIELD,new CSupply(SupplyTree::I_AIRFIELDS)),	//CAFields
		  								DialList(DialBox(FIL_MAP_ARMY,new CArmy(SupplyTree::I_ARMY)),	//CArmy
												DialBox(FIL_NULL,new CArmyDetails(SupplyTree::WestRoute.frontline->associated_item, UID_Null, 0))
		  								)
				)				)	)	);
	else
		CloseLoggedChild(AUTHORISE);
}

void CMainToolbar::OnClickedBases() 
{
	typedef	HideEdgeControl	EDGE;
	if (!LoggedChild(BASES))
		LogChild(BASES,
			RDialog::MakeTopDialog(
			//CRect(20,20,0,0),
			Place(POSN_MIN,POSN_MIN),
						DialList(	DialBox(FIL_MAP_RESOURCE,new BasesTitle),
									//DialBox(FIL_MAP_RESOURCE,new CBases)//,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX  ))
									DialBox(FIL_MAP_RESOURCE,new CBases,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX  ))
				)				)	);
	else
		CloseLoggedChild(BASES);
}
void CMainToolbar::OpenDirectives() 
{
	if (!LoggedChild(DIRECTIVES))
	{
		OnClickedDirectives();
		GETDLGITEM(dialids[DIRECTIVES])->SetPressed(TRUE);
	}else
		LoggedChild(DIRECTIVES)->BringWindowToTop();
}
void CMainToolbar::OnClickedDirectives() 
{
	if (!LoggedChild(DIRECTIVES))
	{
		CloseAllDialogs();
		LogChild(DIRECTIVES,
			RDialog::MakeTopDialog(
			//CRect(120,120,0,0),
			Place(POSN_CENTRE,POSN_CENTRE),
								DialList(DialBox(FIL_MAP_DIRECTIVES,new CComit_e),
									DialBox(FIL_NULL,new CDirects2(0)),
									DialBox(FIL_NULL,new CDirects2(1)),
									DialBox(FIL_NULL,new CDirects2(2)),
									DialBox(FIL_NULL,new CDirects2(3)),
									DialBox(FIL_NULL,new CDirects2(4)),
									DialBox(FIL_NULL,new CDirects2(5)),
									DialBox(FIL_NULL,new CDirects2(6)),
									DialBox(FIL_NULL,new CDirects2(7))
				)				)		);
	}
	else
		CloseLoggedChild(DIRECTIVES);
}

void CMainToolbar::OnClickedMissionresults() 
{
	if (!LoggedChild(RESULTS))
		LogChild(RESULTS,
			RDialog::MakeTopDialog(Place(POSN_MAX,POSN_MAX),
								DialBox(FIL_MAP_MISSIONRESULTS/*IDB_GENERALS*/,new CMResult)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
				)					);	
	else
		CloseLoggedChild(RESULTS);
	
}
void CMainToolbar::LaunchOverview(PosnControl x, PosnControl y) 
{
	typedef	HideEdgeControl	EDGE; 
	if (!LoggedChild(OVERVIEW))
		LogChild(OVERVIEW,
			RDialog::MakeTopDialog(Place(x,y),
								DialList(DialBox(FIL_NULL/*IDB_BBC3*/,new COverview,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									HTabBox(FIL_NULL,IdList(IDS_ACSTATS,IDS_GROUNDSTATS),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
										DialBox(FIL_MAP_OVERVIEW/*IDB_BBC3*/,new CAC_view),
										DialBox(FIL_MAP_OVERVIEW/*IDB_BBC3*/,new CGrndview)//,
		//								DialBox(FIL_MAP_OVERVIEW/*IDB_BBC3*/,new CCmbtview)
				)					)	)	);
	else
		CloseLoggedChild(OVERVIEW);
}
void CMainToolbar::OnClickedOverview() 
{
 	PosnControl x = POSN_CENTRE;
	PosnControl y = POSN_CENTRE;
	LaunchOverview(x, y);


}
void CMainToolbar::OpenPlayerlog() 
{
	if (!LoggedChild(PLAYERLOG))
	{
		OnClickedPlayerlog();
		GETDLGITEM(dialids[PLAYERLOG])->SetPressed(TRUE);
	}else
		LoggedChild(PLAYERLOG)->BringWindowToTop();

}

void CMainToolbar::DialoguesVisible( bool vis)
{
		MakeChildrenVisible(vis);

}

void CMainToolbar::OnClickedMissionlog() 
{
//	static char count=0;
//	if (count++&1)
//		MakeChildrenVisible(bool(count&2));
	PosnControl x = POSN_CENTRE;
	PosnControl y = POSN_CENTRE;
	LaunchPlayerLog(x, y);
	CRTabs* tab=(CRTabs*)LoggedChild(CMainToolbar::PLAYERLOG)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
	tab->SelectTab(2);

}
void CMainToolbar::OnClickedPlayerlog() 
{
//	static char count=0;
//	if (count++&1)
//		MakeChildrenVisible(bool(count&2));
	PosnControl x = POSN_CENTRE;
	PosnControl y = POSN_CENTRE;
	LaunchPlayerLog(x, y);

}
void CMainToolbar::LaunchPlayerLog(PosnControl x, PosnControl y)
{
	typedef	HideEdgeControl	EDGE; 
	if (!LoggedChild(PLAYERLOG))
		LogChild(PLAYERLOG,
			RDialog::MakeTopDialog(Place(x,y),
								DialList(DialBox(FIL_NULL/*IDB_BBC3*/,new CPlyr_log,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)), //rdh
									HTabBox(FIL_NULL,IdList(IDS_CAREER,IDS_MISSIONLOG, IDS_LASTMISSION),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
			  							DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CCareer),
			  							DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CMisn_log),
										DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CLastMissionLog)
//rdh		  								DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CMisntext)
				)					)	)	);
	else
	{
		CloseLoggedChild(PLAYERLOG);
		if  (MMC.firsttime)
		{
			if  (Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
			{
				if  (MMC.directives.autodisplay)
					MainToolBar().OpenDirectives();
			}else
			{
				MainToolBar().OpenDis();
				int pack = 0;
				m_pView->ZoomToUID(Todays_Packages[pack].packagetarget,m_pView->m_zoom);
				m_pView->m_mapdlg.ResetIcon(Todays_Packages[pack].packagetarget);
			}
			MMC.firsttime = false;
		}
	}
}

void CMainToolbar::OpenSquads(int entry)
{
	if (!LoggedChild(SQUADS))
	{
		OnClickedSquads();
		GETDLGITEM(dialids[SQUADS])->SetPressed(TRUE);
	}else
	{
		LoggedChild(SQUADS)->BringWindowToTop();

	}
	CRTabs* tab=(CRTabs*)LoggedChild(SQUADS)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
	tab->SelectTab(entry);
	//delete tab;

}
void CMainToolbar::OnClickedSquads() 
{
	if (!LoggedChild(SQUADS))
	{
		LogChild(SQUADS,CSqdnlist::Make());
		CRTabs* tab=(CRTabs*)LoggedChild(SQUADS)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
		int entry = 0;
		//find the entry squadron with some aircraft available
		while	(		(!MMC.squad[entry].ac_total_avail)
					&&	(entry < 5)			
				)
			entry++;
		if (entry >= 5)
			entry = 0;

		tab->SelectTab(entry);

	}
	else
		CloseLoggedChild(SQUADS);
}

void CMainToolbar::OnClickedWeather() 
{
	int f;
	f = FIL_MAP_CLOUD1 + MMC.Sky.Conditions;
	if (MMC.Sky.MaxMagnitude > 0)
		f++;
	if (!LoggedChild(WEATHER))
		LogChild(WEATHER,
			RDialog::MakeTopDialog(Place(POSN_CENTRE,POSN_CENTRE),
										DialBox((FileNum)f/*IDB_GENERALS*/,new CWeather)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
				)					);	
	else
		CloseLoggedChild(WEATHER);
}


void CMainToolbar::OpenDis() 
{
	if (!LoggedChild(DIS))
	{
		OnClickedDis();
		GETDLGITEM(dialids[DIS])->SetPressed(TRUE);
	}else
		LoggedChild(DIS)->BringWindowToTop();
}


void CMainToolbar::OnClickedDis() 
{
	if (!LoggedChild(DIS))
		LogChild(DIS,
			RDialog::MakeTopDialog(
			Place(POSN_MIN,POSN_MIN),
									DialBox(FIL_MAP_INTELLIGENCE/*IDB_GENERALS*/,new CDIS)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
				)					);
	else
		CloseLoggedChild(DIS);
}

void CMainToolbar::OnClickedMissionFolder() 
{
	if (!LoggedChild(MISSIONS))
	{
//		CloseAllDialogs();
		LogChild(MISSIONS,CMissionFolder::MakeProper());
	}
	else
		CloseLoggedChild(MISSIONS);

}

void CMainToolbar::OnClickedAuthorise11() 
{
	// TODO: Add your control notification handler code here
///TEMP TEST!!!	RDialog::MakeTopDialog(CRect(50,50,690,530),DialBox(FIL_TITLE_640,MakeRtestsh1()));	
	
}

void CMainToolbar::ChildDialClosed(int dialnum,RDialog*,int rv)
{	if (dialids[dialnum])
		GETDLGITEM(dialids[dialnum])->SetPressed(FALSE);
}

void CMainToolbar::OnClickedFrag2() 
{
	if	(!Todays_Packages.FlyableAircraftAvailable())
	{
		int rv;
		if (!Todays_Packages.pack[0][0][0].uid)
			rv = RDialog::RMessageBox(IDS_NOMISSIONS, IDS_SETMISSIONS,NULL,IDS_NEXT_PERIOD,IDS_CONTINUE);
		else														  //RDH 14/06/99
			rv = RDialog::RMessageBox(IDS_MISSIONINVALID, IDS_NOTCLEARED,NULL,IDS_NEXT_PERIOD,IDS_CONTINUE); //RDH 14/06/99
 		if (rv < 2)	
		{
			
			CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
			main->m_toolbar1.CloseLoggedChildren();
			main->m_toolbar2.CloseLoggedChildren();
			main->m_toolbar3.CloseLoggedChildren();
			main->m_toolbar4.CloseLoggedChildren();
			main->m_toolbar5.CloseLoggedChildren();

			MMC.UpdateAllDis();											  //RDH 19/06/99
		  	MMC.ZeroDisDay();
			MMC.msgwithsmacker = 0;										  //RDH 26/06/99
			MMC.smacker = FIL_NULL;


			MMC.NextMission();
			SupplyTree::ProcessAirFields();
			CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
			pmainwnd->m_toolbar5.OnClickedNextPeriod(); 
 		}
	}
	else
	{
// need to find best place for this
//		_Replay.SaveTempSaveGame("dreplay.dat");

		Todays_Packages.SaveBin();
		RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
		FullScreen* fs;
		fullscreen->SetDefaultPilotPositions();
		CFiling::SaveGame("Auto Save.sav");

		//manage stores_destroyed									  //RDH 25/05/99
		SupplyTree::ProcessStoresDestroyed ();

	//DeadCode AMM 27Nov98 	RDialog::m_pView->LaunchFullPane(&RFullPanelDial::singlefrag);	
//	RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
	RFullPanelDial::SetDefaultPilotPositions();
//DeadCode AMM 27Nov98 	RDialog::m_pView->LaunchFullPane(&RFullPanelDial::singlefrag);	

		if (_DPlay.PlayerCreated && _DPlay.Host)
		{
//DeadCode PD 23May99 			_DPlay.SendSaveGame();
			_DPlay.SendSaveGame(false,false);
		}

		if (!RFullPanelDial::incomms)								//AMM 27Nov98
			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::singlefrag);	//AMM 27Nov98
		else														//AMM 27Nov98
		{
//DEADCODE rdh 23/04/99 			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::commsfrag);	//AMM 27Nov98
			if	(_DPlay.Side)
					if (_DPlay.UIPlayerType == PLAYER_HOST)
						RDialog::m_pView->LaunchFullPane(&RFullPanelDial::readyroomhostcampaign);	
					else
						RDialog::m_pView->LaunchFullPane(&RFullPanelDial::readyroomguestcampaign);	

			else
				RDialog::m_pView->LaunchFullPane(&RFullPanelDial::readyroomguestcampaignred);
		}
	}
}
void CMainToolbar::OpenDossierNotFrontLine(UniqueID item) 
{
	if (LoggedChild(DOSSIER))
		CloseLoggedChild(DOSSIER);

 	LogChild(DOSSIER,CTargetDossier::MakeSheet(
		Place(POSN_MAX,POSN_MIN),
					item));

}

void CMainToolbar::OpenDossier(UniqueID item) 
{
	int uidband=Persons2::getbandfromUID(item);

	if (	(		(SupplyTree::WestRoute.frontline->forward->suppliee->associated_item == item)
				||	(SupplyTree::CentralRoute.frontline->forward->suppliee->associated_item == item)
				||	(SupplyTree::EastRoute.frontline->forward->suppliee->associated_item == item)
			)
			&&
			(Save_Data.mapfilters[FILT_FRONTLINE])
		)
	{//front line
		if (LoggedChild(ARMY))
			CloseLoggedChild(ARMY);

	 	LogChild(ARMY,CArmyDetails::MakeSheet(
			Place(POSN_MAX,POSN_MIN),
					item, UID_Null,0));

	}else if (uidband == AmberBattleNodeBAND)
	{//front line force
		UniqueID forceuid;
		forceuid = item;
		SupplyLine* SL;

		TeamDef		*Team=SupplyTree::WestRoute.groundbattle.FindTeamAtLocation(forceuid);
		if (Team)
		{
			item = SupplyTree::WestRoute.frontline->forward->suppliee->associated_item;
			SL= &SupplyTree::WestRoute;
		}
		else 
		{
			Team=SupplyTree::CentralRoute.groundbattle.FindTeamAtLocation(forceuid);
			if (Team)
			{
				item = SupplyTree::CentralRoute.frontline->forward->suppliee->associated_item;
				SL= &SupplyTree::CentralRoute;
			}
			else
			{
				Team=SupplyTree::EastRoute.groundbattle.FindTeamAtLocation(forceuid);
				if (Team) 
				{
					item = SupplyTree::EastRoute.frontline->forward->suppliee->associated_item;
					SL = &SupplyTree::EastRoute;
				}
				else
					item = UID_Null;
			}
		}
		if (item)
		{
			
			int side = 0;
			if	(SL->initiative==REDATTACKING)
			{
				if (Team->team == TeamDef::AWAY)
					side = 1;
			}else
			{
				if (Team->team == TeamDef::HOME)
					side = 1;
			}




			if (LoggedChild(ARMY))
				CloseLoggedChild(ARMY);

	 		LogChild(ARMY,CArmyDetails::MakeSheet(
				Place(POSN_MAX,POSN_MIN),
						item, forceuid,side));
		}
			
	}else
	{//others
		OpenDossierNotFrontLine(item);
	}
	
}
void CMainToolbar::OpenLoadProfile(int uid) 
{
	if (LoggedChild(LOADPROF))
		CloseLoggedChild(LOADPROF);

 	LogChild(LOADPROF,CLoadProf::MakeSheet(uid));

}

void CMainToolbar::CloseAllDialogs()
{
	for (int i = 0; i < MAX_ID; i++)
	{
		if 	(LoggedChild(i))
			 CloseLoggedChild(i);
	}
}

void CMainToolbar::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CRToolBar::OnShowWindow(bShow, nStatus);

	CRButton*	but = GETDLGITEM(dialids[DIRECTIVES]);
	if  (Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
	{
		but->SetDisabled(false);
		but->SetHintString(RESSTRING(DIRECTIVES));
	}else
	{
		but->SetDisabled(true);
		but->SetHintString(RESSTRING(NOTAVAIL));
	}

	
	but = GETDLGITEM(IDC_FRAG2);

	if (RFullPanelDial::incomms)
		but->SetHintString(RESSTRING(READYROOM));
	else
		but->SetHintString(RESSTRING(FRAG));

}
