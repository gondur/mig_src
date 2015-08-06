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

#include "stdafx.h"
#include "MIG.h"

#include "MainFrm.h"
#include "afxpriv.h"
#include "migview.h"
#include "fileman.h"
#include "smack.h"
#include "winmove.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
bool	HELPWASLAUNCHEDRECENTLY=false;

extern CFont* g_AllFonts[MAXFONTS][4];
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_BYE, OnBye)
	ON_COMMAND(ID_GOSMALL, OnGoSmall)
	ON_COMMAND(ID_GOBIG, OnGoBig)
	ON_COMMAND(ID_GONORMAL, OnGoNormal)
	ON_WM_PAINT()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_WM_GETMINMAXINFO()
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
	// Global help commands
//	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
//	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, OnHelpFinder)
	ON_MESSAGE( WM_COMMANDHELP,OnCommandHelp)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

//#if !defined (NDEBUG)
#define NOT_TOPMOST
//#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_doIExist=0;
	m_bHideToolbars=TRUE;
/////	FILEMAN.InitFileSystem();
	havedrawn=havesafe=false;
	m_oldindebrief=(Bool)2;
}

CMainFrame::~CMainFrame()
{
	for (int i=0;i<MAXFONTS;i++)
	{
		for (int j=0;j<4;j++)
		{
			if (g_AllFonts[i][j]!=NULL)
			{
				delete g_AllFonts[i][j];
			}
		}
	}
	if (RDialog::m_pMessageBox)
		delete RDialog::m_pMessageBox;
	if (RDialog::m_pHintBox)
		delete RDialog::m_pHintBox;
	if (RDialog::m_pListBox)
		delete RDialog::m_pListBox;
///	SmackSetSystemRes(SMACKRESRESET);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

#if !defined(NOT_TOPMOST)
	cs.dwExStyle|=WS_EX_TOPMOST;
#endif

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnBye() 
{
#ifndef	MIG_DEMO_VER
	int rv = RDialog::RMessageBox(IDS_QUITGAME, IDS_AREYOUSURE,IDS_SAVE,IDS_L_YESNO_YES,IDS_CANCEL);
	if (rv==0)
	{
		MiscToolBar().OpenSaveOnly(true);

///		else
		return;
	}
	else
	if (rv<2)
	{
		if (RFullPanelDial::incomms)
		{
 			_DPlay.ExitDirectPlay();
		}
//DEADCODE AMM 17/05/99 		m_oldindebrief=FALSE;
		RDialog::m_pView->LaunchFullPane(&RFullPanelDial::title);	
	}
#endif
}

void CMainFrame::OnGoSmall() 
{
//	ShowWindow(SW_SHOWMINIMIZED);
	// show/hide toolbars instead...
	if (m_bHideToolbars)
		ShowToolbars(false);
	else
		HideToolbars();
#ifndef	MIG_DEMO_VER
	m_wndSystemBox->InDialAncestor()->ShowWindow(SW_SHOW);
#endif
}

void CMainFrame::OnGoBig() 
{
//TEMPCODE DAW 08/05/99 	if (!IsZoomed())
		ModifyStyle(WS_THICKFRAME,NULL); // Bye bye border
		HELPWASLAUNCHEDRECENTLY=false;
#if !defined(NOT_TOPMOST)
				SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
#endif
//DeadCode DAW 17Jun99 		ModifyStyleEx(0,WS_EX_TOPMOST);

	ShowWindow(SW_SHOWMAXIMIZED);
//	m_wndSystemBox.GetDlgItem(ID_GONORMAL)->ShowWindow(SW_SHOW);
//	m_wndSystemBox.GetDlgItem(ID_GOBIG)->ShowWindow(SW_HIDE);
}

void CMainFrame::OnGoNormal() 
{
//TEMPCODE DAW 08/05/99 	if (IsZoomed())
		ModifyStyle(NULL,WS_THICKFRAME); // Come back border!
//DeadCode DAW 17Jun99 	ModifyStyleEx(WS_EX_TOPMOST,0);
	ShowWindow(SW_SHOWNORMAL);
#if !defined(NOT_TOPMOST)
				SetWindowPos(&wndBottom,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
#endif
//	m_wndSystemBox.GetDlgItem(ID_GONORMAL)->ShowWindow(SW_HIDE);
//	m_wndSystemBox.GetDlgItem(ID_GOBIG)->ShowWindow(SW_SHOW);
}

void CMainFrame::Initialise()
{
	CMIGView* view = (CMIGView*)GetActiveView();
		m_doIExist=2;	
		// Init toolbars
//DeadCode JIM 05Jul98 		m_toolbar1.Create(CMainToolbar::IDD,view);
//DeadCode JIM 05Jul98 		CRect rect;
//DeadCode JIM 05Jul98 		m_toolbar1.GetWindowRect(rect);
//DeadCode JIM 05Jul98 		m_toolbar1.Init(this,rect.Width(),rect.Width(),40,AFX_IDW_DOCKBAR_TOP,0);
//DeadCode JIM 05Jul98 		m_toolbar2.Create(CMainToolbar::IDD,view);
//DeadCode JIM 05Jul98 		m_toolbar2.Init(this,rect.Width(),rect.Width(),40,AFX_IDW_DOCKBAR_TOP,0);
//DeadCode JIM 05Jul98 		m_toolbar4.Create(CScaleBar::IDD,view);
//DeadCode JIM 05Jul98 		m_toolbar4.Init(this,200,400,40,AFX_IDW_DOCKBAR_LEFT,4);

		CRect rect;

#ifndef	MIG_DEMO_VER
		m_titlebar.Create(TitleBar::IDD,view);
		m_titlebar.GetWindowRect(rect);
		m_titlebar.Init(this,rect.Width(),rect.Width(),48,AFX_IDW_DOCKBAR_TOP,0,CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);

		m_toolbar1.Create(CMapFilters::IDD,view);
		m_toolbar1.GetWindowRect(rect);
		m_toolbar1.Init(this,rect.Width(),rect.Width(),48,AFX_IDW_DOCKBAR_TOP,0);

		m_toolbar2.Create(CMainToolbar::IDD,view);
		m_toolbar2.GetWindowRect(rect);
		m_toolbar2.Init(this,rect.Width(),rect.Width(),48,AFX_IDW_DOCKBAR_TOP,0);
		m_toolbar5.Create(CDebriefToolbar::IDD,view);
		m_toolbar5.GetWindowRect(rect);
		m_toolbar5.Init(this,rect.Width(),rect.Width(),48,AFX_IDW_DOCKBAR_TOP,0);
		m_toolbar3.Create(CMiscToolbar::IDD,view);
		m_toolbar3.GetWindowRect(rect);
		m_toolbar3.Init(this,rect.Width(),rect.Width(),48,AFX_IDW_DOCKBAR_TOP,0);
		m_toolbar4.Create(CScaleBar::IDD,view);
		m_toolbar4.Init(this,200,400,48,AFX_IDW_DOCKBAR_LEFT,4);
		view->m_pScaleBar=&m_toolbar4;
		typedef	HideEdgeControl	EDGE;
		RDialog::MakeTopDialog(CRect(850,650,0,0),
			DialBox(FIL_NULL,m_wndSystemBox=new CSystemBox(this),Edges(EDGE::OCCLUDE_EXACT+EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)));
#endif #ifndef	MIG_DEMO_VER

//		m_wndSystemBox-.Init(CSystemBox::IDD,this);
//		m_wndSystemBox.ShowWindow(SW_SHOW);
		HideToolbars();
		_DPlay.LaunchedByLobbyCheck();
#ifdef 	MIG_DEMO_VER
//DeadCode DAW 02Nov99 		if (!File_Man.ExistNumberedFile(FIL_SMACK_GAMEINTRO))
		if (!File_Man.ExistNumberedFile(FIL_SMACK_GAMEINTRO) && !_DPlay.PossibleLobby)
		{
			Save_Data.InitPreferences((int)Master_3d.winst);
			_Replay.TruncateTempFiles();
			view->LaunchFullPane(&RFullPanelDial::demotitle);
		}
		else
#endif
			view->LaunchFullPane(&RFullPanelDial::introsmack);			  //JIM 18/01/99
		m_doIExist=1;	
}

void	CMainFrame::InitialiseSafe()
{
	havesafe=true;
	if (havedrawn)
		Initialise();
}
void CMainFrame::OnPaint() 
{
//	CDC* pDC=GetWindowDC();
//	CRect windrect;
//	GetWindowRect(windrect);
//	pDC->FillSolidRect(0,0,windrect.Width(),windrect.Height(),RGB(0,0,0));
	CMIGView* view = (CMIGView*)GetActiveView();
	havedrawn=true;
	if (m_doIExist==0)
	{
		if (havesafe)
			Initialise();

	}
	if (m_doIExist==1)
	{
		CRect rect;
		GetWindowRect(rect);
		CRect systemrect;
#ifndef	MIG_DEMO_VER
		m_wndSystemBox->InDialAncestor()->GetClientRect(systemrect);
#endif
		CRect viewrect;
		view->GetClientRect(viewrect);
		view->ClientToScreen(viewrect);
		int	bs=(viewrect.top-rect.top)%16;
#ifndef	MIG_DEMO_VER
		if (viewrect.top-rect.top+10>systemrect.bottom || view->m_currentpage!=0) // check if there is room for the system box 
			m_wndSystemBox->InDialAncestor()->MoveWindow(CRect(rect.right-systemrect.right-bs,rect.top+bs,rect.right-bs,rect.top+systemrect.bottom+bs));
		else 
		{
			int scrollwidth=0;
			if (view->m_size.cy>=viewrect.Height())
				scrollwidth=16;
			m_wndSystemBox->InDialAncestor()->MoveWindow(
			CRect(viewrect.right-systemrect.right-scrollwidth,rect.top+bs,viewrect.right-scrollwidth,rect.top+systemrect.bottom+bs));
		}
#endif
	}
	PAINTSTRUCT ps;
	::BeginPaint(m_hWnd, &ps);
//	pDC->FillSolidRect(0,0,windrect.Width(),windrect.Height(),RGB(0,0,0));
}

void CMainFrame::HideToolbars()
{
	m_bHideToolbars=TRUE;
#ifndef	MIG_DEMO_VER
	m_titlebar.ShowWindow(SW_HIDE);
	m_toolbar1.ShowWindow(SW_HIDE);
	m_toolbar2.ShowWindow(SW_HIDE);
	m_toolbar3.ShowWindow(SW_HIDE);
	m_toolbar4.ShowWindow(SW_HIDE);
	m_toolbar5.ShowWindow(SW_HIDE);
	m_wndSystemBox->InDialAncestor()->ShowWindow(SW_HIDE);
#endif #ifndef	MIG_DEMO_VER
	RecalcLayout();
}

void CMainFrame::ShowToolbars(bool firsttime)
{
#ifndef	MIG_DEMO_VER
	m_bHideToolbars=FALSE;
	m_titlebar.ShowWindow(SW_SHOW);
	m_toolbar1.ShowWindow(SW_SHOW);

	m_toolbar2.ShowWindow(SW_SHOW);
	m_toolbar3.ShowWindow(SW_SHOW);
	m_toolbar4.ShowWindow(SW_SHOW);
	m_toolbar5.ShowWindow(SW_SHOW);
	m_wndSystemBox->InDialAncestor()->ShowWindow(SW_SHOW);
	RecalcLayout();
#endif #ifndef	MIG_DEMO_VER
//	if  (firsttime && (RFullPanelDial::incomms && _DPlay.UIPlayerType==PLAYER_GUEST))
//		m_oldindebrief=TRUE;
//DEADCODE JIM 14/05/99  	if (firsttime)
//DEADCODE JIM 14/05/99  	{
//DEADCODE  14/05/99  		//first time in set this flag to opposite of what we want to ensure we
//DEADCODE  14/05/99  		//get a refresh. 
//DEADCODE  14/05/99  		if  (		(RFullPanelDial::incomms)
//DEADCODE  14/05/99  				&&	(_DPlay.UIPlayerType==PLAYER_GUEST)
//DEADCODE  14/05/99  			)
//DEADCODE  14/05/99  			m_oldindebrief=FALSE;
//DEADCODE  14/05/99  		else
//DEADCODE  14/05/99  			if 	(MMC.indebrief)
//DEADCODE  14/05/99  				m_oldindebrief=FALSE;
//DEADCODE  14/05/99  			else
//DEADCODE  14/05/99  				m_oldindebrief=TRUE;
//DEADCODE  14/05/99 	}
//DEADCODE  14/05/99 */
	UpdateToolbars();
}

void CMainFrame::RePositionLayout(int dx,int dy) 
{
	RePositionLayout(dx,dy,&m_left);
	RePositionLayout(dx,dy,&m_top);
	RePositionLayout(dx,dy,&m_right);
	RePositionLayout(dx,dy,&m_bottom);
}
void CMainFrame::RePositionLayout(int dx,int dy,CMainFrame::ToolBarList* toollist)
{
	POSITION position;
	CRToolBar* pToolbar;
	position=toollist->GetHeadPosition();
	int	count=toollist->GetCount();
	for (int y=0;y<count;y++)
	{
		pToolbar=toollist->GetNext(position);
		CRect rect;
 		pToolbar->GetWindowRect(rect);
		pToolbar->MoveWindow(rect+CPoint(dx,dy));
	}
}
void CMainFrame::RecalcLayout(BOOL bNotify) 
{
	// TODO: Add your specialized code here and/or call the base class
	CFrameWnd::RecalcLayout(bNotify); // if this isnt called the frame window doesnt appear at all
	if (!m_hWnd)
		return;
	if (m_doIExist==0) return;
	CMIGView* view = (CMIGView*)GetActiveView();
	if (!view) return; // If the view doesnt exist yet return
	CRect rect2;
	GetClientRect(rect2);
	if (m_bHideToolbars) 
	{
		view->MoveWindow(rect2);
		return;
	}
	// draw the toolbars
	m_borderRect=CRect(0,0,0,0); // keeps track of the width of each edge
	int x;
	int y;
	int count;
	int start;
	int row;
	int total;
	int priority;
	CRToolBar* pToolbar;
	CRToolBar* pPriorityToolbar;
	BOOL foundend;
	POSITION position;
	CRect rect;
	view->GetWindowRect(rect);
	CRect systemrect;
#ifndef	MIG_DEMO_VER
	m_wndSystemBox->GetWindowRect(systemrect);
#endif
	// first row on top row is a bit shorter because of system box
	int totalwidth=rect2.Width()-systemrect.Width()+1;
	int totalheight=rect2.Height();
	ClientToScreen(rect2);
	// Start with the top

	position=m_top.GetHeadPosition();
	count=m_top.GetCount();
	start=0;
	row=0;
	total=0;
	priority=0;
	foundend=FALSE;
	for (y=0;y<count;y++)
	{
		pToolbar=m_top.GetNext(position);
		pToolbar->m_currentlength=pToolbar->m_minlength;
		total+=pToolbar->m_minlength;
		if (total>totalwidth && start!=y)
		{
			y--;
			foundend=TRUE;
			total-=pToolbar->m_minlength;
		}
		else if (pToolbar->m_priority >= priority)
		{
			priority=pToolbar->m_priority;
			pPriorityToolbar=pToolbar;
		}
		// found a row now draw it
		if (foundend || y==count-1)
		{
			pPriorityToolbar->m_currentlength+=totalwidth-total;
			position=m_top.FindIndex(start);
			total=0;
			for (x=start;x<=y;x++)
			{
				pToolbar=m_top.GetNext(position);
				pToolbar->m_index=x+1;
//				pToolbar->MoveWindow(rect2.left+total,rect2.top+(row*pToolbar->m_width),pToolbar->m_currentlength,pToolbar->m_width);
				pToolbar->SetWindowPos(this,rect2.left+total,rect2.top+(row*pToolbar->m_width),pToolbar->m_currentlength,pToolbar->m_width,SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
				pToolbar->m_row=row;
				total+=pToolbar->m_currentlength;
			}
			// initialise the next row if its there
			m_borderRect.top+=pToolbar->m_width; // assumed all of them are the same width for now...
			if (foundend)
			{
				start=y+1;
				row++;
				totalwidth=rect2.Width();
				total=0;
				foundend=FALSE;
				priority=0;
			}
		}
	}
	totalwidth=rect2.Width();
	// repeat for the other edges
	// probably look nicer doing these 4 things as a very complicated
	// loop but whats the point?  its faster and simpler this way
	// plus its easy to have special conditions for a particular edge
	// next the bottom

	position=m_bottom.GetHeadPosition();
	count=m_bottom.GetCount();
	start=0;
	row=0;
	total=0;
	priority=0;
	foundend=FALSE;
	for (y=0;y<count;y++)
	{
		pToolbar=m_bottom.GetNext(position);
		pToolbar->m_currentlength=pToolbar->m_minlength;
		total+=pToolbar->m_minlength;
		if (total>totalwidth && start!=y)
		{
			y--;
			foundend=TRUE;
			total-=pToolbar->m_minlength;
		}
		else if (pToolbar->m_priority >= priority)
		{
			priority=pToolbar->m_priority;
			pPriorityToolbar=pToolbar;
		}
		// found a row now draw it
		if (foundend || y==count-1)
		{
			pPriorityToolbar->m_currentlength+=totalwidth-total;
			position=m_bottom.FindIndex(start);
			total=0;
			for (x=start;x<=y;x++)
			{
				pToolbar=m_bottom.GetNext(position);
				pToolbar->m_index=x+1;
//				pToolbar->MoveWindow(rect2.left+total,rect2.top+(totalheight-pToolbar->m_width)-(row*pToolbar->m_width),pToolbar->m_currentlength,pToolbar->m_width);
				pToolbar->SetWindowPos(this,rect2.left+total,rect2.top+(totalheight-pToolbar->m_width)-(row*pToolbar->m_width),pToolbar->m_currentlength,pToolbar->m_width,SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
				pToolbar->m_row=row;
				total+=pToolbar->m_currentlength;
			}
			// initialise the next row if its there
			m_borderRect.bottom+=pToolbar->m_width; // assumed all of them are the same width for now...
			if (foundend)
			{
				start=y+1;
				row++;
				total=0;
				foundend=FALSE;
				priority=0;
			}
		}
	}
	totalheight-=(m_borderRect.bottom+m_borderRect.top);
	// Next the left

	position=m_left.GetHeadPosition();
	count=m_left.GetCount();
	start=0;
	row=0;
	total=0;
	priority=0;
	foundend=FALSE;
	for (y=0;y<count;y++)
	{
		pToolbar=m_left.GetNext(position);
		pToolbar->m_currentlength=pToolbar->m_minlength;
		total+=pToolbar->m_minlength;
		if (total>totalheight && start!=y)
		{
			y--;
			foundend=TRUE;
			total-=pToolbar->m_minlength;
		}
		else if (pToolbar->m_priority >= priority)
		{
			priority=pToolbar->m_priority;
			pPriorityToolbar=pToolbar;
		}
		// found a row now draw it
		if (foundend || y==count-1)
		{
			pPriorityToolbar->m_currentlength+=totalheight-total;
			position=m_left.FindIndex(start);
			total=0;
			for (x=start;x<=y;x++)
			{
				pToolbar=m_left.GetNext(position);
				pToolbar->m_index=x+1;
				pToolbar->MoveWindow(rect2.left+(row*pToolbar->m_width),rect2.top+(m_borderRect.top+total),pToolbar->m_width,pToolbar->m_currentlength);
				pToolbar->SetWindowPos(this,rect2.left+(row*pToolbar->m_width),rect2.top+(m_borderRect.top+total),pToolbar->m_width,pToolbar->m_currentlength,SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
				pToolbar->m_row=row;
				total+=pToolbar->m_currentlength;
			}
			// initialise the next row if its there
			m_borderRect.left+=pToolbar->m_width; // assumed all of them are the same width for now...
			if (foundend)
			{
				start=y+1;
				row++;
				total=0;
				foundend=FALSE;
				priority=0;
			}
		}
	}
	// Next the right

	position=m_right.GetHeadPosition();
	count=m_right.GetCount();
	start=0;
	row=0;
	total=0;
	priority=0;
	foundend=FALSE;
	for (y=0;y<count;y++)
	{
		pToolbar=m_right.GetNext(position);
		pToolbar->m_currentlength=pToolbar->m_minlength;
		total+=pToolbar->m_minlength;
		if (total>totalheight && start!=y)
		{
			y--;
			foundend=TRUE;
			total-=pToolbar->m_minlength;
		}
		else if (pToolbar->m_priority >= priority)
		{
			priority=pToolbar->m_priority;
			pPriorityToolbar=pToolbar;
		}
		// found a row now draw it
		if (foundend || y==count-1)
		{
			pPriorityToolbar->m_currentlength+=totalheight-total;
			position=m_right.FindIndex(start);
			total=0;
			for (x=start;x<=y;x++)
			{
				pToolbar=m_right.GetNext(position);
				pToolbar->m_index=x+1;
//				pToolbar->MoveWindow(rect2.left+totalwidth-pToolbar->m_width-(row*pToolbar->m_width),rect2.top+m_borderRect.top+total,pToolbar->m_width,pToolbar->m_currentlength);
				pToolbar->SetWindowPos(this,rect2.left+totalwidth-pToolbar->m_width-(row*pToolbar->m_width),rect2.top+m_borderRect.top+total,pToolbar->m_width,pToolbar->m_currentlength,SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
				pToolbar->m_row=row;
				total+=pToolbar->m_currentlength;
			}
			// initialise the next row if its there
			m_borderRect.right+=pToolbar->m_width; // assumed all of them are the same width for now...
			if (foundend)
			{
				start=y+1;
				row++;
				total=0;
				foundend=FALSE;
				priority=0;
			}
		}
	}

	// create the border depending on borderrect
	rect-=rect2.TopLeft();
	view->MoveWindow(CRect(rect.left+m_borderRect.left,rect.top+m_borderRect.top,rect.right-m_borderRect.right,rect.bottom-m_borderRect.bottom));
	// move system box to top
#ifndef	MIG_DEMO_VER
	m_wndSystemBox->InDialAncestor()->SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
#endif
//	Invalidate();
}

//DEADCODE DAW 07/05/99 void CMainFrame::OnNcPaint() 
//DEADCODE DAW 07/05/99 {
//DEADCODE DAW 07/05/99 //	CDC* pDC=GetWindowDC();
//DEADCODE DAW 07/05/99 //	CRect windrect;
//DEADCODE DAW 07/05/99 //	GetWindowRect(windrect);
//DEADCODE DAW 07/05/99 //	pDC->FillSolidRect(0,0,windrect.Width(),windrect.Height(),RGB(0,0,0));
//DEADCODE DAW 07/05/99 	// Do not call CFrameWnd::OnNcPaint() for painting messages
//DEADCODE DAW 07/05/99 }

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
//DEADCODE DAW 07/06/99 	CRect rect;														  //DAW 07/06/99
//DEADCODE DAW 07/06/99 	AfxGetMainWnd()->GetWindowRect(rect);							  //DAW 07/06/99
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::UpdateToolbars()
{
#ifndef	MIG_DEMO_VER
	if (m_oldindebrief==MMC.indebrief) return;
	m_oldindebrief=MMC.indebrief;
	if (MMC.indebrief)// && m_toolbar2.IsWindowVisible())
	{
		m_toolbar5.ShowWindow(SW_SHOW);
		m_toolbar2.Replace(&m_toolbar5);
	}
	else// if (!MMC.indebrief && m_toolbar5.IsWindowVisible())
	{
		m_toolbar2.ShowWindow(SW_SHOW);
		m_toolbar5.Replace(&m_toolbar2);
	}
#endif
	RecalcLayout();
}

void CMainFrame::OnHelp() 
{
	// TODO: Add your command handler code here
	if (!Inst3d::InThe3D())
	{
		HELPWASLAUNCHEDRECENTLY=true;
		HWND upperwnd=HWND_BOTTOM;  
		::SetWindowPos(m_hWnd,upperwnd,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
		CFrameWnd::OnHelp() ;
	}
}

void CMainFrame::OnHelpFinder() 
{
	// TODO: Add your command handler code here
	if (!Inst3d::InThe3D())
		CFrameWnd::OnHelpFinder() ;
	
}

void CMainFrame::OnContextHelp() 
{
	// TODO: Add your command handler code here
	if (!Inst3d::InThe3D())
		CFrameWnd::OnContextHelp() ;
	
}
LRESULT CMainFrame::OnCommandHelp(WPARAM w, LPARAM lParam)
{
	if (!Inst3d::InThe3D())
	{
		CMIGView* view = (CMIGView*)GetActiveView();
		if ((disablehelp&1)==0 || (view && view->m_currentpage==0))
			AfxGetApp()->WinHelp(HID_BASE_RESOURCE+IDD_INTRODUCTION);
	}
	return 1;//CFrameWnd::OnCommandHelp(w,lParam);
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnSize
//Author		Paul.   
//Date			Mon 25 Jan 1999
//------------------------------------------------------------------------------
void CMainFrame::OnMove(int x, int y) 
{
//DEADCODE DAW 07/05/99 	CRect oldpos;
//DEADCODE DAW 07/05/99 	GetWindowRect(oldpos);
//DEADCODE DAW 07/05/99 	CFrameWnd::OnMove(x, y);
//DEADCODE DAW 07/05/99 	x-=oldpos.left;
//DEADCODE DAW 07/05/99 	y-=oldpos.top;
//DEADCODE DAW 07/05/99 	RePositionLayout(x,y);
//	RecalcLayout();
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	if (nType==SIZE_MINIMIZED)
	{
		//window has been minimized
		bAppMinimized=true;
	}
	else if (bAppMinimized)
	{
		//window has been restored
		bAppMinimized=false;
	}
	HELPWASLAUNCHEDRECENTLY=false;
	CFrameWnd::OnSize(nType,cx,cy);
}

void CMainFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMainFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return true;//CFrameWnd::OnEraseBkgnd(pDC);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_doIExist=false;
	CFrameWnd::OnClose();
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
	lpMMI->ptMinTrackSize=CPoint(300,200);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
//DeadCode DAW 22Jun99 		TRACE2("Activate %i ==> %08x\n",nState,::GetWindowThreadProcessId(pWndOther->m_hWnd, NULL) );
//DeadCode DAW 22Jun99 	else
//DeadCode DAW 22Jun99 	{
//DeadCode DAW 22Jun99 		TRACE1("Activate %i xxx\n",nState);
		//If in the 3D && state==0 then discard DD here
#ifdef NDEBUG
 	if (!pWndOther)
		if (Inst3d::InThe3D())
		{
			if (!nState)	Inst3d::ReleaseDirectX();
			else
			{
				Inst3d::RestoreDirectX();
				CMIGView* view=(CMIGView*)GetActiveView();
				RFullPanelDial*	dial=GetFullPanel(view);
				dial->LaunchScreen(&RFullPanelDial::quickmissionflight);
			}
		}
#endif
//DeadCode DAW 22Jun99 	}

	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}
static BOOL CALLBACK EnumThreadWndProc(  HWND hwnd,  LPARAM lParam)
{
	*(int*)lParam=(int)hwnd;
	return	FALSE;
}
   

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CFrameWnd::OnActivateApp(bActive, hTask);
//DeadCode DAW 22Jun99 	TRACE2("Activate Ap %i ==>%08x\n",bActive,hTask);
	
	// TODO: Add your message handler code here
	//BOOL SetWindowPos( const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags );
	//const CWnd* pWndInsertAfter= wndBottom/wndTop/ wndTopMost/wndNoTopMost
//BOOL SetWindowPos(
//  HWND hWnd,             // handle to window
//  HWND hWndInsertAfter,  // placement-order handle
//  int X,                 // horizontal position
//  int Y,                 // vertical position
//  int cx,                // width
//  int cy,                // height
//  UINT uFlags            // window-positioning flags
//);
		if (!bActive)
		{  
			HWND upperwnd=HWND_BOTTOM;  
			::SetWindowPos(m_hWnd,upperwnd,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//DEADCODE DAW 16/06/99 			if (hTask)
//DEADCODE DAW 16/06/99 				EnumThreadWindows((int)hTask,EnumThreadWndProc,(int)&upperwnd);
//DEADCODE DAW 16/06/99  			if (upperwnd!=HWND_BOTTOM)
//DEADCODE DAW 16/06/99 			{
//DEADCODE DAW 16/06/99 				::SetWindowPos(m_hWnd,HWND_TOP,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//DEADCODE DAW 16/06/99 				::SetWindowPos(upperwnd,HWND_TOP,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//DEADCODE DAW 16/06/99 			}
		}
		else
		{
#if !defined(NOT_TOPMOST)
			if (IsZoomed() & HELPWASLAUNCHEDRECENTLY==false)
				SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
#endif
		}
	
}
/* 
pWndInsertAfter젨쟅dentifies the CWnd object that will precede this CWnd object in the Z-order. 
This parameter can be a pointer to a CWnd or a Pointer to one of the following values:

wndBottom젨쟑laces the window at the bottom of the Z-order. 
If this CWnd is a topmost window, the window loses its topmost status; 
the system places the window at the bottom of all other windows.

wndTop젨쟑laces the window at the top of the Z-order.

wndTopMost젨쟑laces the window above all nontopmost windows. 
The window maintains its topmost position even when it is deactivated.

wndNoTopMost젨쟓epositions the window to the top of all nontopmost windows (that is, behind all topmost windows). 
This flag has no effect if the window is already a nontopmost window.


nFlags젨쟔pecifies sizing and positioning options. This parameter can be a combination of the following:

SWP_DRAWFRAME젨잻raws a frame (defined when the window was created) around the window. 

SWP_FRAMECHANGED젨쟔ends a WM_NCCALCSIZE message to the window, even if the window's size is not being changed. If this flag is not specified, WM_NCCALCSIZE is sent only when the window's size is being changed.

SWP_HIDEWINDOW젨쟄ides the window.

SWP_NOACTIVATE젨잻oes not activate the window. If this flag is not set, the window is activated and moved to the top of either the topmost or the nontopmost group (depending on the setting of the pWndInsertAfter parameter).

SWP_NOCOPYBITS젨잻iscards the entire contents of the client area. If this flag is not specified, the valid contents of the client area are saved and copied back into the client area after the window is sized or repositioned.

SWP_NOMOVE젨쟓etains current position (ignores the x and y parameters).

SWP_NOOWNERZORDER젨잻oes not change the owner window's position in the Z-order.

SWP_NOREDRAW젨잻oes not redraw changes. If this flag is set, no repainting of any kind occurs. This applies to the client area, the nonclient area (including the title and scroll bars), and any part of the parent window uncovered as a result of the moved window. When this flag is set, the application must explicitly invalidate or redraw any parts of the window and parent window that must be redrawn.

SWP_NOREPOSITION젨쟔ame as SWP_NOOWNERZORDER. 

SWP_NOSENDCHANGING젨쟑revents the window from receiving the WM_WINDOWPOSCHANGING message.

SWP_NOSIZE젨쟓etains current size (ignores the cx and cy parameters).

SWP_NOZORDER젨쟓etains current ordering (ignores pWndInsertAfter).

SWP_SHOWWINDOW젨잻isplays the window.
*/
