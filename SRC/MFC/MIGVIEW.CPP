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

// MIGView.cpp : implementation of the CMIGView class
//

#include "stdafx.h"
#include "MIG.h"
#include "MIGDoc.h"
#include "CntrItem.h"
#include "MIGView.h"
#include "MissFldr.h"
#include "Bases.h"
#include "Author.h"
#include "Supply.h"
#include "Choke.h"
//#include "Traffic.h"
//#include "AFields.h"
#include "Army.h"
#include "Comit_e.h"
#include "DIS.h"
#include "Weather.h"
#include "Squads.h"
#include "Sqdnlist.h"
#include "Plyr_log.h"
#include "Career.h"
#include "Misn_log.h"
#include "Misntext.h"
#include "Overview.h"
#include "AC_view.h"
#include "Grndview.h"
#include "Cmbtview.h"
#include "MResult.h"
#include	"mymath.h"
#include <afxodlgs.h>
#include "MainFrm.h"
//#include "stitle.h"
#include "fullpane.h"
#include "text.h"
#include "bfnumber.h"
#include	"persons2.h"
#include "MapDlg.h"
#include "Thumnail.h"
//#include "JoyConfg.h"
#include "RCstmBtn.h"
#include "ScaleBar.h"
#include	"savegame.h"
#include	"node.h"
MAKEFIELD(UniqueID,UID_NULL,IllegalSepID);
#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

const FileNum CMIGView::m_MapFiles[32][20]=
//{{FIL_NULL}};
#include "frontmap.h"
;



// the zoom thresholds where the map uses different bitmaps
// they are floats



CThumbnail* CMIGView::m_thumbnail=NULL;
/////////////////////////////////////////////////////////////////////////////
// CMIGView
extern CFont* g_AllFonts[][4];
extern CDC g_OffScreenDC;

//IMPLEMENT_DYNCREATE(CMIGView, CView)

	CObject* PASCAL CMIGView::CreateObject() \
		{ return new CMIGView; } \
	IMPLEMENT_RUNTIMECLASS(CMIGView, CView, 0xFFFF, \
		CMIGView::CreateObject)


BEGIN_MESSAGE_MAP(CMIGView, CView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CMIGView)
	ON_COMMAND(ID_SHOW_AIR_STRIPS, OnShowAirStrips)
	ON_COMMAND(ID_SHOW_BRIDGES, OnShowBridges)
	ON_COMMAND(ID_POPUP_ZOOM_IN, OnPopupZoomIn)
	ON_COMMAND(ID_POPUP_ZOOM_OUT, OnPopupZoomOut)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_MESSAGE( WM_GETFILE, OnGetFile)
	ON_MESSAGE( WM_RELEASELASTFILE, OnReleaseLastFile)
	ON_MESSAGE( WM_GETOFFSCREENDC, OnGetOffScreenDC)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CMIGView, CView)
    //{{AFX_EVENTSINK_MAP(CMIGView)
//	ON_EVENT(CMIGView, IDC_CHANGE_TO_TITLE, 1 /* Clicked */, OnChangeToTitle, VTS_NONE)
//	ON_EVENT(CMIGView, IDC_AUTHORISE, 1 /* Clicked */, OnIntelligence, VTS_NONE)
	ON_EVENT(CMIGView, 1001, 1 /* Scroll */, OnScrollHorzScrollbar, VTS_I4)
	ON_EVENT(CMIGView, 1000, 1 /* Scroll */, OnScrollVertScrollbar, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMIGView construction/destruction
//CCustomBitmapButton* CMIGView::m_pAllButtons[]={{0}};

CMIGView::CMIGView()
{
	// Initialise map arrays
	// remember to change AIRSTRIPS etc. constants in .h file if this is modified
	// (AIRSTRIPS tells you the total number of airstrips)
	// this code is probably obsolete now...

// AIRSTRIPS

//	m_airstripCoords[0] = CPoint(520,1050);
//	m_airstripCoords[1] = CPoint(700,1200);
//	m_airstripCoords[2] = CPoint(620,1340);
//	m_airstripCoords[3] = CPoint(580,1090);
//	m_airstripsChecked = FALSE;

// BRIDGES

//	m_bridgeCoords[0] = CPoint(540,1080);
//	m_bridgeCoords[1] = CPoint(740,1300);
//	m_bridgesChecked = FALSE;

	m_doIexist=0;
	m_zoom = 1.001;	//1.02320;//1.11625; // initial zoom position
	m_size.cx=256*4*m_zoom-5;
	m_size.cy=256*7*m_zoom-5;
	m_oldzoom=m_zoom;
	m_LButtonDown=FALSE;
//	m_scrollpoint=CPoint(m_size.cx/2,m_size.cy/2);
	m_scrollpoint=CPoint(111,380);//(111,452); // initial map position in pixels from the top left
	RDialog::m_pView=this;
	m_pfullpane=NULL;
//	m_bDontUpdateBitmaps=FALSE;
	m_drawing=FALSE;
	m_pfileblock=NULL;
	m_iconradius=12;
}

CMIGView::~CMIGView()
{
	Persons4::ShutDownMapWorld();
}

BOOL CMIGView::PreCreateWindow(CREATESTRUCT& cs)
{

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMIGView drawing

void CMIGView::OnDraw(CDC* pDC)
{
	CMIGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_currentpage==0)
		m_mapdlg.ShowWindow(SW_SHOW);	// ensures window is always shown even if
//									// closed with escape key
//	else if (!m_pfullpane)
//	{
//		LaunchFullPane(&RFullPanelDial::introsmack);
//	}
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect.right-16,rect.bottom-16,16,16,RGB(0,0,0));
}

/////////////////////////////////////////////////////////////////////////////
// CMIGView printing

BOOL CMIGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMIGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMIGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMIGView diagnostics

#ifdef _DEBUG
void CMIGView::AssertValid() const
{
	CView::AssertValid();
}

void CMIGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMIGDoc* CMIGView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMIGDoc)));
	return (CMIGDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMIGView message handlers

void CMIGView::OnInitialUpdate()
{
	m_currentpage=1;
	CRect rect;
	GetClientRect(rect);
	// note that mapdlg is a child window instead of a pop-up window
	m_mapdlg.Create(CMapDlg::IDD,this);
//	m_mapdlg.ShowWindow(SW_SHOW);
	m_mapdlg.MoveWindow(0,0,30000,30000);
	m_rVertScrollBar.Create(NULL, WS_VISIBLE | WS_CHILD, CRect(-1,-1,-1,-1), this, 1000);
	m_rHorzScrollBar.Create(NULL, WS_VISIBLE | WS_CHILD, CRect(-1,-1,-1,-1), this, 1001);
	m_rVertScrollBar.SetParentPointer((long)this);
	m_rHorzScrollBar.SetParentPointer((long)this);
	m_rHorzScrollBar.SetHorzAlign(TRUE);

//	WINDOWPLACEMENT lpwndpl;
//	m_mapdlg.GetWindowPlacement(&lpwndpl);
//	lpwndpl.rcNormalPosition = CRect(0,0,30000,30000); // Dialog box as large as possible
//	m_mapdlg.SetWindowPlacement(&lpwndpl);
//	LOGBRUSH log;
//	log.lbStyle=BS_NULL;
//	CBrush brush;
//	brush.CreateBrushIndirect(&log);
//	brush.CreateSolidBrush(RGB(50,100,200));
//	CDC* pdc;
//	pdc=m_mapdlg.GetDC();
//	pdc->SelectObject(brush);
//	m_mapdlg.ReleaseDC(pdc);
//	pdc=this->GetDC();
//	pdc->SelectObject(brush);
//	this->ReleaseDC(pdc);
	//FAR TOO EARLY!! NO FILE SYSTEM YET!!! // moved to launchmap:
//	Persons4::StartUpMapWorld();		//do whenever we go to the map screen
//	Persons4::ShutDownMapWorld();		//do whenever we come off the map screen
//	UpdateBitmaps();
// 	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
//	main->HideToolbars();
	ModifyStyleEx(GetExStyle(),NULL); // Bye bye annoying border!
}

void CMIGView::UpdateAll()
{
	return;
/*	CRect rect;
	GetClientRect(rect);
	int px,py;
	ItemBasePtr p;
//	m_bDontUpdateBitmaps=TRUE;
	for (int i=UID_Null;i<IllegalSepID;i++)
	{
		p=Persons2::ConvertPtrUID(UniqueID(i));
		if (p)
		{
			px=((p->World.X*m_zoom)/65536)-(512*m_zoom);
			py=(1792*m_zoom)-((p->World.Z*m_zoom)/65536);
// first check if button is in display area, if it isnt we dont want to do anything to it.
			if (rect.PtInRect(CPoint(px-m_scrollpoint.x-10,
							 py-m_scrollpoint.y-10)))
			{
// if it is then create it if it doesnt exist else just move it.
				if (m_pAllButtons[i] == NULL)
				{
					m_pAllButtons[i]=new CCustomBitmapButton;
					m_pAllButtons[i]->Create("",
						BS_PUSHBUTTON | BS_OWNERDRAW | WS_VISIBLE | WS_CHILD | WS_TABSTOP,// | WS_EX_TOPMOST,
						CRect(px-m_scrollpoint.x-10,py-m_scrollpoint.y-10,
							  px-m_scrollpoint.x+10,py-m_scrollpoint.y+10),
						&m_mapdlg, IDC_BUTTON1);
					m_pAllButtons[i]->m_ID=i;
					m_pAllButtons[i]->LoadBitmaps("AIRSTRIPUP","AIRSTRIPDOWN","AIRSTRIPFOCUS");
//					m_pAllButtons[i]=new CRCustomButton;
//					m_pAllButtons[i]->Create(NULL,WS_VISIBLE,
//						CRect(px-m_scrollpoint.x-10,py-m_scrollpoint.y-10,
//							  px-m_scrollpoint.x+10,py-m_scrollpoint.y+10),
//							  this,IDC_BUTTON1);
//					m_pAllButtons[i]->SetNormalFileNum((long)FIL_ICON_R_CIVILIAN_ON);
//					m_pAllButtons[i]->m_ID=i;
				}
				else // buttons exist and checkbox pressed so just move them
				{	
					m_pAllButtons[i]->MoveWindow(px-m_scrollpoint.x-10,py-m_scrollpoint.y-10,20,20);
				}
			}
			else // if its off screen and exists then delete it
			{
				if (m_pAllButtons[i])
				{
					m_pAllButtons[i]->DestroyWindow();
					delete m_pAllButtons[i];
					m_pAllButtons[i]=NULL;
				}
			}
		}
	}
//	m_bDontUpdateBitmaps=FALSE;
//	m_mapdlg.Invalidate();
//	m_bDontUpdateBitmaps=TRUE;
*/}

void CMIGView::OnShowAirStrips() 
{
	m_airstripsChecked=!m_airstripsChecked;
	UpdateAirStrips();
}

void CMIGView::UpdateAirStrips()
{
	
//DEAD	CRect rect;
//DEAD	GetClientRect(rect);
//DEAD	for (short i=0;i<AIRSTRIPS;i++)
//DEAD	{
//DEAD		if (m_airstripsChecked)
//DEAD		{
//DEAD// first check if button is in display area, if it isnt we dont want to do anything to it.
//DEAD			if (rect.PtInRect(CPoint(m_airstripCoords[i].x*m_zoom-m_scrollpoint.x-9,
//DEAD							 m_airstripCoords[i].y*m_zoom-m_scrollpoint.y-9)))
//DEAD			{
//DEAD// if it is then create it if it doesnt exist else just move it.
//DEAD				if (m_airstripButtons[i].m_hWnd == NULL)
//DEAD				{
//DEAD					m_airstripButtons[i].Create("",
//DEAD						BS_PUSHBUTTON | BS_OWNERDRAW | WS_VISIBLE | WS_CHILD | WS_TABSTOP,// | WS_EX_TOPMOST,
//DEAD						CRect(m_airstripCoords[i].x*m_zoom-m_scrollpoint.x-9,m_airstripCoords[i].y*m_zoom-m_scrollpoint.y-9,
//DEAD							  m_airstripCoords[i].x*m_zoom-m_scrollpoint.x+9,m_airstripCoords[i].y*m_zoom-m_scrollpoint.y+9),
//DEAD						&m_mapdlg, IDC_BUTTON1);
//DEAD					m_airstripButtons[i].m_ID=i;
//DEAD					m_airstripButtons[i].LoadBitmaps("AIRSTRIPUP","AIRSTRIPDOWN","AIRSTRIPFOCUS");
//DEAD				}
//DEAD				else // buttons exist and checkbox pressed so just move them
//DEAD				{// if you force them to the bottom they always remain on top (yes its windoze)
//DEAD//					m_airstripButtons[i].MoveWindow(
//DEAD//					m_airstripCoords[i].x*m_zoom-m_scrollpoint.x-9,m_airstripCoords[i].y*m_zoom-m_scrollpoint.y-9,18,18);
//DEAD					m_airstripButtons[i].SetWindowPos(&wndBottom,
//DEAD						m_airstripCoords[i].x*m_zoom-m_scrollpoint.x-9,m_airstripCoords[i].y*m_zoom-m_scrollpoint.y-9,18,18,
//DEAD					NULL);
//DEAD				}
//DEAD			}
//DEAD			else // if its off screen and exists then move it out of the way
//DEAD			{
//DEAD				if (m_airstripButtons[i].m_hWnd != NULL)
//DEAD					m_airstripButtons[i].MoveWindow(
//DEAD					m_airstripCoords[i].x*m_zoom-m_scrollpoint.x-9,m_airstripCoords[i].y*m_zoom-m_scrollpoint.y-9,18,18);
//DEAD			}
//DEAD		}
//DEAD		else
//DEAD		{
//DEAD			if (m_airstripButtons[i].m_hWnd != NULL)
//DEAD				m_airstripButtons[i].DestroyWindow();
//DEAD		}// if buttons don't exist and are not supposed to be there do nothing
//DEAD	}
	
}

void CMIGView::OnShowBridges() 
{
//	m_bridgesChecked=!m_bridgesChecked;
//	UpdateBridges();
}

void CMIGView::UpdateBridges()
{
//DEAD	CRect rect;
//DEAD	GetClientRect(rect);
//DEAD	for (short i=0;i<BRIDGES;i++)
//DEAD	{
//DEAD		if (m_bridgesChecked)
//DEAD		{
//DEAD// first check if button is in display area, if it isnt we dont want to do anything to it.
//DEAD			if (rect.PtInRect(CPoint(m_bridgeCoords[i].x*m_zoom-m_scrollpoint.x-9,
//DEAD							 m_bridgeCoords[i].y*m_zoom-m_scrollpoint.y-9)))
//DEAD			{
//DEAD// if it is then create it if it doesnt exist else just move it.
//DEAD				if (m_bridgeButtons[i].m_hWnd == NULL)
//DEAD				{
//DEAD					m_bridgeButtons[i].Create("",
//DEAD						BS_PUSHBUTTON | BS_OWNERDRAW | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_EX_TOPMOST,
//DEAD						CRect(m_bridgeCoords[i].x*m_zoom-m_scrollpoint.x-9,m_bridgeCoords[i].y*m_zoom-m_scrollpoint.y-9,
//DEAD							  m_bridgeCoords[i].x*m_zoom-m_scrollpoint.x+9,m_bridgeCoords[i].y*m_zoom-m_scrollpoint.y+9),
//DEAD						&m_mapdlg, IDC_BUTTON2);
//DEAD					m_bridgeButtons[i].m_ID=i;
//DEAD					m_bridgeButtons[i].LoadBitmaps("BRIDGEUP","BRIDGEDOWN","BRIDGEFOCUS");
//DEAD				}
//DEAD				else // buttons exist and checkbox pressed so just move them
//DEAD				{
//DEAD//					m_bridgeButtons[i].MoveWindow(
//DEAD//					m_bridgeCoords[i].x*m_zoom-m_scrollpoint.x-9,m_bridgeCoords[i].y*m_zoom-m_scrollpoint.y-9,18,18);
//DEAD					m_bridgeButtons[i].SetWindowPos(&wndBottom,
//DEAD						m_bridgeCoords[i].x*m_zoom-m_scrollpoint.x-9,m_bridgeCoords[i].y*m_zoom-m_scrollpoint.y-9,18,18,
//DEAD					NULL);
//DEAD				}
//DEAD			}
//DEAD			else // if its off screen and exists then move it out of the way
//DEAD			{
//DEAD				if (m_bridgeButtons[i].m_hWnd != NULL)
//DEAD					m_bridgeButtons[i].MoveWindow(
//DEAD					m_bridgeCoords[i].x*m_zoom-m_scrollpoint.x-9,m_bridgeCoords[i].y*m_zoom-m_scrollpoint.y-9,18,18);
//DEAD			}
//DEAD		}
//DEAD		else
//DEAD		{
//DEAD			if (m_bridgeButtons[i].m_hWnd != NULL)
//DEAD				m_bridgeButtons[i].DestroyWindow();
//DEAD		}// if buttons don't exist and are not supposed to be there do nothing
//DEAD	}
}

void CMIGView::OnZoomIn() 
{
	CRect rect;
	GetClientRect(rect);
	// Zoom to centre of client window if toolbar used
	m_zoom=m_zoom*2;
	Zoom(CPoint(rect.right/2,rect.bottom/2));
}

void CMIGView::OnZoomOut() 
{
	CRect rect;
	GetClientRect(rect);
	m_zoom=m_zoom/2;
	Zoom(CPoint(rect.right/2,rect.bottom/2));
}

void CMIGView::OnContextMenu(CWnd*, CPoint point)
{
	if (m_currentpage) return; // dont allow popup on frontend screens
	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_MIG_ALLEY_MFCVIEW));
		CMenu* pPopup = menu.GetSubMenu(0);
		if (m_zoom >= ZOOMMAX)
//DEADCODE RDH 02/05/99 			pPopup->ModifyMenu(ID_POPUP_ZOOM_IN,MF_GRAYED | MF_BYCOMMAND | MF_STRING,0,"Zoom In");
			pPopup->EnableMenuItem(ID_POPUP_ZOOM_IN,MF_GRAYED | MF_BYCOMMAND);
		if (m_zoom <= ZOOMMIN)
//DEADCODE RDH 02/05/99 			pPopup->ModifyMenu(ID_POPUP_ZOOM_OUT,MF_GRAYED | MF_BYCOMMAND | MF_STRING,0,"Zoom Out");
			pPopup->EnableMenuItem(ID_POPUP_ZOOM_OUT,MF_GRAYED | MF_BYCOMMAND);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;
		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
//	::AfxTrace("Menu P (%i,%i)\n", point.x, point.y);
		CRect rect;
		GetWindowRect(rect);
		m_popupPoint=point-rect.TopLeft();
	}
}

void CMIGView::ZoomToUID(UniqueID uid, double zoom)
{
	int px,py;
	ItemBasePtr p;
	p=Persons2::ConvertPtrUID(uid);
	ASSERT(p);
	px=((p->World.X*m_zoom)/65536)-(384*m_zoom);
	py=(1792*m_zoom)-((p->World.Z*m_zoom)/65536);
	CRect rect;
	GetClientRect(rect);
	// Zoom to centre of client window if toolbar used
	m_scrollpoint.x=px-rect.right/2;
	m_scrollpoint.y=py-rect.bottom/2;
	m_zoom=zoom;
	Zoom(CPoint(rect.right/2,rect.bottom/2));

//	Zoom(CPoint(px,py));
}

void CMIGView::OnPopupZoomIn() 
{
//	::AfxTrace("Zoom IN (%i,%i)\n", m_popupPoint.x, m_popupPoint.y);
	m_zoom=m_zoom*1.2599;
	Zoom(m_popupPoint);
}

static void	PalTrans(void* &dataarea,ULong& datasize)
{
//	BITMAPINFO* pInfo=(BITMAPINFO*)((char*)dataarea+sizeof(BITMAPFILEHEADER));
//	for (int i=pInfo->bmiHeader.biClrUsed?pInfo->bmiHeader.biClrUsed-1:255;i;i--)
//		(int&)pInfo->bmiColors[i]=((int&)pInfo->bmiColors[i]&0x00f0f0f0)+0x00040404;



}


void CMIGView::OnPopupZoomOut() 
{
//	::AfxTrace("Zoom OUT (%i,%i)\n", m_popupPoint.x, m_popupPoint.y);
	m_zoom=m_zoom*0.7937;
	Zoom(m_popupPoint);		
}
/* The Old way of doing it...
void CMIGView::UpdateBitmaps()
{
	// First of all hide all the old windows if this isnt the first time through.
	// The windows are in fact CStatics which basically give a bitmap the functionality
	// of a window.
	int areax;
	int areay;
	if (m_zoom>=4)
	{
		areax=16;
		areay=32; // area of bitmap array
	}
	else if (m_zoom>=1)
	{
		areax=4;
		areay=8;
	}
	else if (m_zoom>0)
	{
		areax=1;
		areay=1;
	}
	if (m_oldzoom>=4)
	{
		for (int x=m_oldstartx;x<m_oldendx;x++)
		{
			for (int y=m_oldstarty;y<m_oldendy;y++)
			{
				m_pbigstaticArray[x+(y*16)]->ShowWindow(SW_HIDE);
			}
		}
	}
	else if (m_oldzoom>=1)
	{
		for (int x=m_oldstartx;x<m_oldendx;x++)
		{
			for (int y=m_oldstarty;y<m_oldendy;y++)
			{
				m_pstaticArray[x+(y*4)]->ShowWindow(SW_HIDE);
			}
		}
	}
	else if (m_oldzoom>0)
	{
		m_psmallStatic->ShowWindow(SW_HIDE);
	}
	else // if it is first time through initialise array
	{
		int z;
		m_psmallStatic = NULL;
		m_pstaticArray = new CStatic*[4*8];
		for (z=0;z<4*8;z++)
			m_pstaticArray[z]=NULL; // do this in constructor?
		m_pbigstaticArray = new CStatic*[16*32];
		for (z=0;z<16*32;z++)
			m_pbigstaticArray[z]=NULL; // do this in constructor?
	}

	// calculate the range of windows we need to display next

	int zoomsquaresize;
	if (m_zoom>=4)
		zoomsquaresize=64*m_zoom;	// size of one side of bitmap compensated for zoom
	else if (m_zoom>=1)
		zoomsquaresize=256*m_zoom;
	else zoomsquaresize=5000;
	int startx=m_scrollpoint.x/zoomsquaresize;
	int starty=m_scrollpoint.y/zoomsquaresize;
	int squaresize=256; // size of one side of bitmap
	CRect rect;
	this->GetClientRect(&rect);  // top left is always 0,0
	FILE* fp;
	CDC* pDC;
	pDC = m_mapdlg.GetDC();
	HDC hDC;
	hDC = pDC->GetSafeHdc( );  // gets and stores handle of mapdlg DC	

	typedef struct tagBIGBITMAPINFO : public tagBITMAPINFO
	{
		RGBQUAD dummy[255];
	} BIGBITMAPINFO;
	HBITMAP hb;
	BIGBITMAPINFO tmp;
	BITMAPINFO* i=(BITMAPINFO*)&tmp;
	char*	buffer=new char[256*256];
	char filename[50];
	int endx=min(startx+(rect.right/zoomsquaresize)+2,areax);
	int endy=min(starty+(rect.bottom/zoomsquaresize)+2,areay);
		
// now display the windows in the correct positions loading them in if necessary

	if (m_zoom>=4)
	{
		for (int x=startx;x<endx;x++)
		{
			for (int y=starty;y<endy;y++)
			{
				if (m_pbigstaticArray[x+(y*areax)]==NULL)
				{
					// load in relevant bitmap			

					m_pbigstaticArray[x+(y*areax)]=new CStatic;	

					sprintf(filename,"FrontMap\\Map%d_%d.bmp",x,areay-y-1);
					fp=fopen(filename,"rb");
					if (fp==NULL) // does not exist so must be chinese land or sea assume sea
					{
						hb=(HBITMAP)m_sea;
					}
					else
					{
						// skip over file header
						fseek(fp,sizeof(BITMAPFILEHEADER),SEEK_CUR);
						// read in bitmap info header
						fread(i,1,sizeof(BIGBITMAPINFO),fp);
						// read bitmap bit data into buffer
						fread(buffer,1,squaresize*squaresize,fp);
						fclose(fp);
						hb = CreateDIBitmap(hDC,&i->bmiHeader,CBM_INIT,buffer,i,DIB_RGB_COLORS);
						// now draw it.	
					}
					m_pbigstaticArray[x+(y*areax)]->Create("",WS_VISIBLE | WS_CHILD | SS_BITMAP | WS_EX_TRANSPARENT, // bitmaps are always on the bottom,
							  CRect(x*zoomsquaresize,			y*zoomsquaresize,
									x*zoomsquaresize+squaresize,y*zoomsquaresize+squaresize),
							  &m_mapdlg);
					m_pbigstaticArray[x+(y*areax)]->SetBitmap(hb);
				}
				// if it exists we are only interested in moving and showing it.
				m_pbigstaticArray[x+(y*areax)]->MoveWindow(
					((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
					((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
					zoomsquaresize,zoomsquaresize);
				m_pbigstaticArray[x+(y*areax)]->ShowWindow(SW_SHOWNA);
			}
		}
	}
	else if (m_zoom>=1)
	{
		for (int x=startx;x<endx;x++)
		{
			for (int y=starty;y<endy;y++)
			{
				if (m_pstaticArray[x+(y*areax)]==NULL)
				{
					// load in relevant bitmap			

					m_pstaticArray[x+(y*areax)]=new CStatic;	

					sprintf(filename,"FrBigMap\\SMap%d_%d.bmp",x,areay-y-1);
					fp=fopen(filename,"rb");
					if (fp==NULL) // does not exist so must be chinese land or sea assume sea
					{
						hb=(HBITMAP)m_sea;
					}
					else
					{
						// skip over file header
						fseek(fp,sizeof(BITMAPFILEHEADER),SEEK_CUR);
						// read in bitmap info header
						fread(i,1,sizeof(BIGBITMAPINFO),fp);
						// read bitmap bit data into buffer
						fread(buffer,1,squaresize*squaresize,fp);
						fclose(fp);
						hb = CreateDIBitmap(hDC,&i->bmiHeader,CBM_INIT,buffer,i,DIB_RGB_COLORS);
						// now draw it.	
					}
					m_pstaticArray[x+(y*areax)]->Create("",WS_VISIBLE | WS_CHILD | SS_BITMAP | WS_EX_TRANSPARENT, // bitmaps are always on the bottom,
							  CRect(x*zoomsquaresize,			y*zoomsquaresize,
									x*zoomsquaresize+squaresize,y*zoomsquaresize+squaresize),
							  &m_mapdlg);
					m_pstaticArray[x+(y*areax)]->SetBitmap(hb);
				}
				// if it exists we are only interested in moving and showing it.
				m_pstaticArray[x+(y*areax)]->MoveWindow(
					((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
					((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
					zoomsquaresize,zoomsquaresize);
				m_pstaticArray[x+(y*areax)]->ShowWindow(SW_SHOWNA);
			}
		}
	}
	else
	{
		if (m_psmallStatic==NULL)
		{
			// load in relevant bitmap			
			m_psmallStatic=new CStatic;
			hb=(HBITMAP)m_thumbnail;
			m_psmallStatic->Create("",WS_VISIBLE | WS_CHILD | SS_BITMAP | WS_EX_TRANSPARENT, // bitmaps are always on the bottom,
				CRect(0,0,256,512),&m_mapdlg);
			m_psmallStatic->SetBitmap(hb);
		}
		// if it exists we are only interested in moving and showing it.
		m_psmallStatic->MoveWindow(-m_scrollpoint.x,-m_scrollpoint.y,256*4*m_zoom,512*4*m_zoom);
		m_psmallStatic->ShowWindow(SW_SHOWNA);
	}

	// clean up
	if (rect.right>m_size.cx) 
		pDC->FillSolidRect(CRect(m_size.cx,0,rect.right,rect.bottom),
							GetSysColor(COLOR_APPWORKSPACE));
	if (rect.bottom>m_size.cy)
		pDC->FillSolidRect(CRect(0,m_size.cy,rect.right,rect.bottom),
							GetSysColor(COLOR_APPWORKSPACE));
	UpdateAirStrips();
	UpdateBridges();
	UpdateAll();
	m_oldendx=endx;
	m_oldendy=endy;
	m_oldstartx=startx;
	m_oldstarty=starty;
	m_oldzoom=m_zoom;
	delete [] buffer;
	m_mapdlg.PostMessage(WM_PAINT,NULL,NULL);
}
*/
// The New Way...
void	CMIGView::ScreenXY(int wx,int wz,int&px,int&py,int scrollx,int scrolly)
{
	px=((wx*m_zoom)/65536)-(384*m_zoom)+scrollx;
	py=(1792*m_zoom)-((wz*m_zoom)/65536)+scrolly;
}
void	CMIGView::ScreenXY(ItemBasePtr p,int&px,int&py,int scrollx,int scrolly)
{
	ScreenXY(p->World.X,p->World.Z,px,py,scrollx,scrolly);
	if (p->uniqueID.count>=WayPointBAND && p->uniqueID.count<WayPointBANDEND)
	{
		SWord s,c;
		UWord ang=(p->uniqueID.count-WayPointBAND)*ANGLES_50Deg;
		Math_Lib.sin_cos((Angles)ang,s,c);
		px+=s*m_iconradius/32768;
		py+=c*m_iconradius/32768;
	}
}

int	CMIGView::WorldXY(int& wx,int& wz,int sx,int sy)
{	if (sx+m_scrollpoint.x>32000)
		wx=65536*384 +256*(((sx+m_scrollpoint.x)*256)/m_zoom);
	else
		wx=65536*384 +((sx+m_scrollpoint.x)*65536)/m_zoom;
	if (sy+m_scrollpoint.y>32000)
		wz=65536*1792-256*(((sy+m_scrollpoint.y)*256)/m_zoom);
	else
		wz=65536*1792-((sy+m_scrollpoint.y)*65536)/m_zoom;
	return m_iconradius*65536/m_zoom;
}

int	CMIGView::WorldXY(Coords3D& w,int sx,int sy)
{
	return WorldXY((int&)w.X,(int&)w.Z,sx,sy);
}

//DeadCode JIM 19Feb99 BOOL CMIGView::IsIconVisible(ItemBasePtr p, int&px, int&py)
//DeadCode JIM 19Feb99 {
//DeadCode JIM 19Feb99 	ScreenXY(p,px,py,m_scrollpoint.x,m_scrollpoint.y);
//DeadCode JIM 19Feb99 	CRect rect;
//DeadCode JIM 19Feb99 	GetClientRect(rect);
//DeadCode JIM 19Feb99 	if (rect.IntersectRect(rect,CRect(px,py,px+m_iconradius*2,py+m_iconradius*2)))
//DeadCode JIM 19Feb99 		return TRUE;
//DeadCode JIM 19Feb99 	else
//DeadCode JIM 19Feb99 		return FALSE;
//DeadCode JIM 19Feb99 }

void	CMIGView::DrawIcon(HDC hDC,int px,int py,BYTE* pData,BITMAPINFO* pInfo)
{
	SetDIBitsToDevice(hDC,px-m_scrollpoint.x-m_iconradius,py-m_scrollpoint.y-m_iconradius+1,m_iconradius*2,m_iconradius*2,
		0,0,0,m_iconradius*2,pData,pInfo,DIB_RGB_COLORS);
}
void	CMIGView::DrawIcon(HDC hDC,int px,int py,FileNum f)
{
		fileblock	block(f);
		BYTE*				pData=(BYTE*)getdata(block);
		BITMAPFILEHEADER*	pFile=(BITMAPFILEHEADER*)pData;
		BITMAPINFO*			pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
		pData+=pFile->bfOffBits;
		DrawIcon(hDC,px,py,pData,pInfo);
}
void	CMIGView::DrawIconText(CDC* pDC,int px,int py,CString name)
{
	pDC->TextOut(px-m_scrollpoint.x+m_iconradius,py-m_scrollpoint.y-m_iconradius+2,name);
}


void CMIGView::Zoom(CPoint screenpoint,bool redrawscalebar)
{
	if (m_zoom<ZOOMMIN) m_zoom=ZOOMMIN;
	if (m_zoom>ZOOMMAX) m_zoom=ZOOMMAX;
	if	(m_zoom>ZOOMTHRESHOLD2)
		m_iconradius=12;
	else 
		m_iconradius=3;
//DeadCode RDH 30Mar99 	m_scrollpoint += screenpoint;
//DeadCode RDH 30Mar99 	m_scrollpoint = CPoint(m_scrollpoint.x*(m_zoom/m_oldzoom),m_scrollpoint.y*(m_zoom/m_oldzoom));
//DeadCode RDH 30Mar99 	m_scrollpoint -= screenpoint;
//DeadCode RDH 30Mar99 	m_size.cx=m_size.cx*(m_zoom/m_oldzoom);
//DeadCode RDH 30Mar99 	m_size.cy=m_size.cy*(m_zoom/m_oldzoom);


	CRect rect;
	GetClientRect(rect);

	float oldsizecy = m_size.cy;
//TEMPCODE JIM 29/05/99 	float oldsizecx = m_size.cx;
////TEMPCODE DAW 08/05/99 	m_size.cx=m_size.cx*(m_zoom/m_oldzoom);
////TEMPCODE DAW 08/05/99 	m_size.cy=m_size.cy*(m_zoom/m_oldzoom);
	m_size.cx=256*4*m_zoom-5;
	m_size.cy=256*7*m_zoom-5;

	if (rect.bottom>m_size.cy)
	{//min zoom for full screen map
		m_zoom = m_oldzoom * rect.bottom/oldsizecy;
////TEMPCODE DAW 08/05/99 		m_size.cx= oldsizecx*(m_zoom/m_oldzoom);
////TEMPCODE DAW 08/05/99 		m_size.cy= oldsizecy*(m_zoom/m_oldzoom);
		m_size.cx=256*4*m_zoom-5;
		m_size.cy=256*7*m_zoom-5;

	}

	m_scrollpoint += screenpoint;
	m_scrollpoint = CPoint(m_scrollpoint.x*(m_zoom/m_oldzoom),m_scrollpoint.y*(m_zoom/m_oldzoom));
	m_scrollpoint -= screenpoint;

	m_oldzoom=m_zoom;												  //JIM 29/05/99

	m_mapdlg.Invalidate();
	UpdateScrollbars();
	if (redrawscalebar)				//deafult true
		m_pScaleBar->RedrawWindow();
}

void CMIGView::PlotFrontLine(CDC* pDC)
{
	ItemBasePtr pt;
	int px,py;
	
	CPen pen (PS_SOLID,4,RGB(252,156,12));
	CPen* oldpen=pDC->SelectObject(&pen);

	pt=Persons2::ConvertPtrUID(UniqueID(SupplyTree::WestRoute.frontline->forward->suppliee->associated_item));
	if (pt)
	{
		ScreenXY(pt->World.X,pt->World.Z,px,py,-m_scrollpoint.x,-m_scrollpoint.y);
		pDC->MoveTo(px,py);
		pt=Persons2::ConvertPtrUID(UniqueID(SupplyTree::CentralRoute.frontline->forward->suppliee->associated_item));
		if (pt)
		{
			ScreenXY(pt->World.X,pt->World.Z,px,py,-m_scrollpoint.x,-m_scrollpoint.y);
			pDC->LineTo(px,py);
			pt=Persons2::ConvertPtrUID(UniqueID(SupplyTree::EastRoute.frontline->forward->suppliee->associated_item));
			if (pt)
			{
				ScreenXY(pt->World.X,pt->World.Z,px,py,-m_scrollpoint.x,-m_scrollpoint.y);
				pDC->LineTo(px,py);
			}
		}

	}

	pDC->SelectObject(oldpen);
}
void CMIGView::PlotRoute(CDC* pDC, int pack, int wave, int group, bool drawhilight,UniqueID onlythrough)
{

//	if (!pDC && !onlythrough)
//		INT3;
	// a NULL pDC indicates that we are invalidating rather than drawing
	bool	seesubwp = true;
	bool	afjapan = false;
	UniqueID start=Todays_Packages[pack][wave][group].takeoffAF;
	if (start == UID_Japan)
		afjapan = true;
	if (start)
	{
		CPen hilight (PS_SOLID,2,RGB(255,255,255));
		CPen hilightthin (PS_SOLID,1,RGB(255,255,255));
		CPen dehilight (PS_SOLID,2,RGB(160,160,0));
		CPen dehilightthin (PS_SOLID,1,RGB(160,160,0));
		CPen* oldpen;
		UniqueID nextwp=Todays_Packages[pack][wave].firstwp;
		if (pDC)
		{
			oldpen=pDC->SelectObject(&dehilight);
			if  (drawhilight)
				pDC->SelectObject(&hilight);
			else
				pDC->SelectObject(&dehilight);
		}
		if (!onlythrough || start==onlythrough || nextwp==onlythrough)
			PlotLine(pDC,start,nextwp);
		info_waypoint* wp=*Persons2::ConvertPtrUID(nextwp);
		UniqueID oldwp = nextwp;
		info_waypoint* lastwp=wp;
		if (wp)
		while ((wp->nextwp)!=NULL)
		{
			nextwp=wp->nextwp;
			wp=*Persons2::ConvertPtrUID(nextwp);
			if  (		
					(wp->uid !=ENABLE_COMPLEX_VAL) ||
					(wp->applygroup==ENABLE_COMPLEX_VAL) ||
					(		
						(seesubwp) &&
						(wp->applygroup == Todays_Packages.higroup)
					)
				)
			{
				if  (pDC)
					if 	(
							(wp->applygroup!=ENABLE_COMPLEX_VAL) ||
							(lastwp->applygroup!=ENABLE_COMPLEX_VAL)
						)
					{
						if  (drawhilight)
							pDC->SelectObject(&hilightthin);
						else
							pDC->SelectObject(&dehilightthin);
					}
					else
					{
						if  (drawhilight)
							pDC->SelectObject(&hilight);
						else
							pDC->SelectObject(&dehilight);
					}
				//don't display wp for flights that don't exist
				if  (		(wp->applyflight ==ENABLE_COMPLEX_VAL)
						||	(	(wp->applyflight < Todays_Packages[pack][wave][group].numflights)
							)
					)
					if (!onlythrough || oldwp==onlythrough || nextwp==onlythrough)
						PlotLine(pDC,oldwp,nextwp);
				//display non-lead wps as spurs
				if  (		(wp->applyflight==ENABLE_COMPLEX_VAL)
						||	(		(wp->applyflight== 0)
								&&	(		(wp->applyelt == 0)
										||	(wp->applyelt == ENABLE_COMPLEX_VAL)
									)
							)
					)
						
				{
					lastwp=wp;
					oldwp=nextwp;
				}
			}
		}
		if (!onlythrough || nextwp==onlythrough || start==onlythrough)
			if (afjapan)
				PlotLine(pDC,nextwp,start,TRUE);
			else
				PlotLine(pDC,nextwp,start);
		if (pDC) 
			pDC->SelectObject(oldpen);
	}
/*
	bool	seesubwp = true;
	bool	afjapan = false;
	CPoint linestart;
	UniqueID linestartID;

	UniqueID start=Todays_Packages[pack][wave][group].takeoffAF;
	if (start == UID_Japan)
		afjapan = true;
	if (start)
	{
		CPen hilight (PS_SOLID,2,RGB(255,255,255));
		CPen hilightthin (PS_SOLID,1,RGB(255,255,255));
		CPen dehilight (PS_SOLID,2,RGB(160,160,0));
		CPen dehilightthin (PS_SOLID,1,RGB(160,160,0));
		CPen* oldpen;
		if (pDC) 
			oldpen=pDC->SelectObject(&dehilight);

		UniqueID nextwp=Todays_Packages[pack][wave].firstwp;
		ItemBasePtr pt1,pt2,ptjapan;
		COORDS3D japan;

		int px1,py1,px2,py2, oldpx, oldpy;
			pt1=Persons2::ConvertPtrUID(UniqueID(start));

		japan.X = pt1->World.X + 40000000;
		japan.Z = pt1->World.Z - 20000000;
		pt2=Persons2::ConvertPtrUID(UniqueID(nextwp));
		ScreenXY(pt1->World.X,pt1->World.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
		if (pDC)
		{
			ASSERT(px1<1000);
			pDC->MoveTo(px1,py1);
			if  (drawhilight)
				pDC->SelectObject(&hilight);
			else
				pDC->SelectObject(&dehilight);
		}
		else
		{
			linestart=CPoint(px1,py1);
			linestartID=start;
		}
		ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
		ASSERT(px2<1000);
		pDC->LineTo(px2,py2);
		info_waypoint* wp=*Persons2::ConvertPtrUID(nextwp);
		info_waypoint* oldwp = wp;
		while ((nextwp=wp->nextwp)!=NULL)
		{
			wp=*Persons2::ConvertPtrUID(nextwp);
			if  (		
					(wp->uid !=ENABLE_COMPLEX_VAL) ||
					(wp->applygroup==ENABLE_COMPLEX_VAL) ||
					(		
						(seesubwp) &&
						(wp->applygroup == Todays_Packages.higroup)
					)
				)
			{
				ScreenXY(wp->World.X,wp->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
				if  (pDC && 
						(
							(wp->applygroup!=ENABLE_COMPLEX_VAL) ||
							(oldwp->applygroup!=ENABLE_COMPLEX_VAL)
						)
					)
				{
					if  (drawhilight)
						pDC->SelectObject(&hilightthin);
					else
						pDC->SelectObject(&dehilightthin);
				}
				else if (pDC)
				{
					if  (drawhilight)
						pDC->SelectObject(&hilight);
					else
						pDC->SelectObject(&dehilight);
				}
				if (pDC)
				{
					ASSERT(px2<1000);
					pDC->LineTo(px2,py2);
				}
				else 
				{
					if (linestartID==m_mapdlg.m_buttonid || nextwp==m_mapdlg.m_buttonid)
						m_mapdlg.InvalidateLine(linestart,CPoint(px2,py2));
				}
	
				//display subgroup wps as spurs
				if  (wp->applyflight==ENABLE_COMPLEX_VAL)
				{
					oldwp = wp;
					oldpx = px2;
					oldpy = py2;
				}
				else
				{
					ASSERT(oldpx<1000);
					if (pDC)
						pDC->MoveTo(oldpx,oldpy);
					else
					{
						linestartID=nextwp;
						linestart=CPoint(oldpx,oldpy);
					}
				}
			}
		}

		if (afjapan)
		{
			ScreenXY(japan.X,japan.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
		}
		ASSERT(px1<1000);
		if (pDC)
			pDC->LineTo(px1,py1);
		else
			if (linestartID==m_mapdlg.m_buttonid || start==m_mapdlg.m_buttonid)
				m_mapdlg.InvalidateLine(linestart,CPoint(px1,py1));

		if (pDC)
			pDC->SelectObject(oldpen);
	}
*/	
}

void CMIGView::PlotLine(CDC* pDC, UniqueID thiswp,UniqueID nextwp,BOOL japanwp)
{
	if (!pDC) 
//rdh: Dallas got this wrong		m_mapdlg.InvalidateMovedLine(thiswp,nextwp,japanwp);
//not figured out what is needed
		m_mapdlg.InvalidateLine(thiswp,nextwp);
	else
	{
		int px1,py1,px2,py2;
		ItemBasePtr pt1,pt2;
		pt1=Persons2::ConvertPtrUID(UniqueID(thiswp));
		pt2=Persons2::ConvertPtrUID(UniqueID(nextwp));
		if (!pt1 || !pt2) return;
//DEADCODE RDH 18/04/99 		if (japanwp)
//DEADCODE RDH 18/04/99 			ScreenXY(pt1->World.X + 40000000,pt1->World.Z - 20000000,
//DEADCODE RDH 18/04/99 						px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE RDH 18/04/99 		else
		ScreenXY(pt1,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
//rdh		if (japanwp)
//			ScreenXY(pt2->World.X + 40000000,pt2->World.Z - 20000000,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
//		else
			ScreenXY(pt2,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
		pDC->MoveTo(CPoint(px1,py1));
		pDC->LineTo(CPoint(px2,py2));
		if (japanwp)
		{							
			ScreenXY(pt2->World.X + METRES500KM,pt2->World.Z - METRES150KM,
						px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
			pDC->MoveTo(CPoint(px1,py1));
			pDC->LineTo(CPoint(px2,py2));
		}

	}
}
void CMIGView::InvalidateJapan()
{
		int px1,py1,px2,py2;
		ItemBasePtr pt1;
		pt1=Persons2::ConvertPtrUID(UID_Japan);
		ScreenXY(pt1,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
		ScreenXY(pt1->World.X + METRES500KM,pt1->World.Z - METRES150KM,
				px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
		m_mapdlg.InvalidateLine(CPoint(px1,py1),CPoint(px2,py2));
}


#ifndef	NDEBUG
void CMIGView::PlotMainRoute(CDC* pDC, SupplyLine* SL, int red, int green, int blue)
{
	CPen pen (PS_SOLID,8,RGB(red,green,blue));

	CPen  pen00(PS_SOLID,1,RGB(255,255,255)),
		  pen01(PS_SOLID,1,RGB(255,100,100)),
		  pen02(PS_SOLID,2,RGB(255,100,100)),
		  pen03(PS_SOLID,3,RGB(255,100,100)),
		  pen04(PS_SOLID,4,RGB(255,100,100)),
		  pen05(PS_SOLID,5,RGB(255,100,100)),
		  pen06(PS_SOLID,6,RGB(255,100,100)),
		  pen07(PS_SOLID,7,RGB(255,100,100)),

		  pen11(PS_SOLID,1,RGB(100,255,100)),
		  pen12(PS_SOLID,2,RGB(100,255,100)),
		  pen13(PS_SOLID,3,RGB(100,255,100)),
		  pen14(PS_SOLID,4,RGB(100,255,100)),
		  pen15(PS_SOLID,5,RGB(100,255,100)),
		  pen16(PS_SOLID,6,RGB(100,255,100)),
		  pen17(PS_SOLID,7,RGB(100,255,100)),

		  pen21(PS_SOLID,1,RGB(100,100,255)),
		  pen22(PS_SOLID,2,RGB(100,100,255)),
		  pen23(PS_SOLID,3,RGB(100,100,255)),
		  pen24(PS_SOLID,4,RGB(100,100,255)),
		  pen25(PS_SOLID,5,RGB(100,100,255)),
		  pen26(PS_SOLID,6,RGB(100,100,255)),
		  pen27(PS_SOLID,7,RGB(100,100,255));
		  CPen* penlist[3][7]=
			{
				{&pen01,&pen02,&pen03,&pen04,&pen05,&pen06,&pen07},
				{&pen11,&pen12,&pen13,&pen14,&pen15,&pen16,&pen17},
				{&pen21,&pen22,&pen23,&pen24,&pen25,&pen26,&pen27},
			};
	CPen* oldpen=pDC->SelectObject(&pen);

	SupplyNode*  currnode = SL->firstnode;
	SupplyRoute*  currroute;
	ItemBasePtr pt1,pt2;
	int px1,py1,px2,py2,px3,py3;
	pt1=Persons2::ConvertPtrUID(UniqueID(SL->firstnode->associated_item));
	ScreenXY(pt1->World.X,pt1->World.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
	pDC->MoveTo(px1,py1);

	int count = 0;
	while (			(count < 80)
				&&	(currnode->forward != NULL)
			)
//or should this be new ?
// no comments so I cannot tell
// commented out version crashes on entry to the map
//Old_Code DAW 26Nov98 	while (			(count < 80)
//Old_Code DAW 26Nov98 				&&	(currnode->forward->suppliee != NULL)
//Old_Code DAW 26Nov98 			)
	{
		currroute = currnode->forward;
		pt2=Persons2::ConvertPtrUID(UniqueID(currroute->suppliee->associated_item));
		ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
		pDC->LineTo(px2,py2);
		for (int i=0;i<3;i++)
			if (currnode->forward->suppliee->route[i])
			{
				int proper=0,good=0,bad=0;
				for (SupplyRoute* sr=currnode->forward->suppliee->route[i];sr;sr=sr->alternateroute)
				{
					if (currnode->associated_item==UID_MyBlSeoul)
						currnode=currnode;
					if (sr->populateBF || (proper&&sr->associated_brdg))
						proper+=sr->maxcapacitysummer;
					else
						if (sr->maxcapacitysummer>80)
							bad+=sr->maxcapacitysummer;
						else
							if (sr->maxcapacitysummer!=0)
								good+=1;
				}
				bad/=80;
				proper/=80;
				pt2=Persons2::ConvertPtrUID(UniqueID(currnode->forward->suppliee->route[i]->supplier->associated_item));
				ScreenXY(pt2->World.X,pt2->World.Z,px3,py3,-m_scrollpoint.x,-m_scrollpoint.y);
				if (bad)
					if (proper)
						pDC->SelectObject(penlist[0][bad+good-1]);
					else
						pDC->SelectObject(penlist[1][bad+good-1]);
				else
					if (good)
						pDC->SelectObject(penlist[2][good-1]);
					else
						pDC->SelectObject(&pen00);
				pDC->LineTo(px3,py3);
				pDC->MoveTo(px2,py2);
				pDC->SelectObject(&pen);
			}
//TEMPCODE JIM 28/06/99 		if (currroute->suppliee->route[0]!=currroute)
//TEMPCODE JIM 28/06/99 		{
//TEMPCODE JIM 28/06/99 			pt2=Persons2::ConvertPtrUID(UniqueID(currroute->suppliee->route[0]->supplier->associated_item));
//TEMPCODE JIM 28/06/99 			ScreenXY(pt2->World.X,pt2->World.Z,px3,py3,-m_scrollpoint.x,-m_scrollpoint.y);
//TEMPCODE JIM 28/06/99 			pDC->LineTo(px3,py3);
//TEMPCODE JIM 28/06/99 			pDC->MoveTo(px2,py2);
//TEMPCODE JIM 28/06/99 		}
		currnode = currroute->suppliee;		
		count++;
	}
	pDC->SelectObject(oldpen);


}
#endif
/*
void CMIGView::PlotAirfields(CDC* pDC)
{
	CPen pen (PS_SOLID,1,RGB(255,255,255));
	CPen* oldpen=pDC->SelectObject(&pen);

	ItemBasePtr pt1,pt2;
	int px1,py1,px2,py2;

	SupplyNode* currnode;
	currnode = SupplyTree::FirstNode;
	while (currnode->type != LASTONE)
	{
		pt1=Persons2::ConvertPtrUID(UniqueID(currnode->associated_item));
		ScreenXY(pt1->World.X,pt1->World.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
		for (int i = 0; i< 3; i++)
		{
 			if (m_mapdlg.m_buttonid == currnode->airfield[i])
 			{
 				pDC->MoveTo(px1,py1);
				if (currnode->airfield[i])
 				{
 					pt2=Persons2::ConvertPtrUID(UniqueID(currnode->airfield[i]));
 					ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
					pDC->LineTo(px2,py2);
 				}
 			}

		
		currnode = currnode->next;
	};



	pDC->SelectObject(oldpen);


}

*/
#ifndef	NDEBUG
void CMIGView::PlotAirfields(CDC* pDC)
{

	ItemBasePtr pt1,pt2;
	int px1,py1,px2,py2;

		SWord i = 0;

	while (SupplyTree::airfieldinfo[i].nationality != NAT_ALIGN)
	{
 			if (m_mapdlg.m_buttonid == SupplyTree::airfieldinfo[i].airfield)
 			{


				CPen pen (PS_SOLID,3,RGB(0,0,255));
				CPen* oldpen=pDC->SelectObject(&pen);
				
				pt1=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].airfield));
				ScreenXY(pt1->World.X,pt1->World.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
	
				pDC->MoveTo(px1,py1);
				pt2=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].northnodes[0]->associated_item));
				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
				pDC->LineTo(px2,py2);

				pDC->MoveTo(px1,py1);
				pt2=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].northnodes[1]->associated_item));
				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
				pDC->LineTo(px2,py2);

				CPen pen2 (PS_SOLID,3,RGB(255,0,0));
				pDC->SelectObject(&pen2);

				pDC->MoveTo(px1,py1);
				pt2=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].southnodes[0]->associated_item));
				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
				pDC->LineTo(px2,py2);

				pDC->MoveTo(px1,py1);
				pt2=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].southnodes[1]->associated_item));
				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
				pDC->LineTo(px2,py2);
				pDC->SelectObject(oldpen);
			}
			i++;
			
	};

	

}


void CMIGView::PlotSupplyingRoutes(CDC* pDC)
{

	ItemBasePtr pt1,pt2;
	int px1,py1,px2,py2;

	CPen	pen (PS_SOLID,1,RGB(255,0,0));
	CPen* oldpen;
	;
	oldpen=pDC->SelectObject(&pen);

	SupplyNode* currnode;
	currnode = SupplyTree::FirstNode;
	while (currnode->type != LASTONE)
	{
		pt1=Persons2::ConvertPtrUID(UniqueID(currnode->associated_item));
		ScreenXY(pt1->World.X,pt1->World.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
		for (int i = 0; i< 3; i++)
		{
			
//DEADCODE DAW 14/05/99 			if (currnode->supplyline == &SupplyTree::WestRoute)
//DEADCODE DAW 14/05/99 			{
//DEADCODE DAW 14/05/99 				CPen pen (PS_SOLID,1,RGB(255,0,0));
//DEADCODE DAW 14/05/99 				oldpen=pDC->SelectObject(&pen);
//DEADCODE DAW 14/05/99 			}
//DEADCODE DAW 14/05/99 			if (currnode->supplyline == &SupplyTree::CentralRoute)
//DEADCODE DAW 14/05/99 			{
//DEADCODE DAW 14/05/99 				CPen pen (PS_SOLID,1,RGB(0,255,0));
//DEADCODE DAW 14/05/99 				oldpen=pDC->SelectObject(&pen);
//DEADCODE DAW 14/05/99 			}
//DEADCODE DAW 14/05/99 			if (currnode->supplyline == &SupplyTree::EastRoute)
//DEADCODE DAW 14/05/99 			{
//DEADCODE DAW 14/05/99 				CPen pen (PS_SOLID,1,RGB(0,0,255));
//DEADCODE DAW 14/05/99 				oldpen=pDC->SelectObject(&pen);
//DEADCODE DAW 14/05/99 			}

			pDC->MoveTo(px1,py1);
			if (currnode->route[i])
			{
				pt2=Persons2::ConvertPtrUID(UniqueID(currnode->route[i]->supplier->associated_item));
				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
			}
			if (currnode->supplyline == &SupplyTree::WestRoute)
				pDC->LineTo(px2,py2);

		}

		
		
		currnode = currnode->next;
	};


   pDC->SelectObject(oldpen);

 

}
#endif
#ifndef NDEBUG
void	PlotInvalidateBoxes(CDC*	pDC)
{
	for (int pennum=0;pennum<debugboxmem.lastline;pennum++)
	{
		CPen pen(PS_SOLID,1,COLORREF(debugboxmem.debuglineRGB[pennum&7]));
		bool	gotone=false;
		debugboxmem.debuglineRGB[pennum&7]+=0x1000;
		CPen* oldpen=pDC->SelectObject(&pen);
		for (int box=0;box<debugboxmem.lastbox;box++)
			if (debugboxmem.boxmem[box].linenum==pennum)
			{
				pDC->MoveTo(debugboxmem.boxmem[box].sx,debugboxmem.boxmem[box].sy);
				pDC->LineTo(debugboxmem.boxmem[box].ex,debugboxmem.boxmem[box].ey);
				pDC->LineTo(debugboxmem.boxmem[box].ex,debugboxmem.boxmem[box].sy);
				pDC->LineTo(debugboxmem.boxmem[box].sx,debugboxmem.boxmem[box].sy);
				pDC->LineTo(debugboxmem.boxmem[box].sx,debugboxmem.boxmem[box].ey);
				pDC->LineTo(debugboxmem.boxmem[box].ex,debugboxmem.boxmem[box].ey);
			}
		pDC->SelectObject(oldpen);
	}
	debugboxmem.lastline=0;
	debugboxmem.lastbox=0;
}
#endif

void CMIGView::PlotDebugInfo(CDC* pDC)
{
#ifndef NDEBUG
//TempCode DAW 22Jun99 	PlotMainRoute(pDC, &SupplyTree::WestRoute,255,0,0);
//TempCode DAW 22Jun99 	PlotMainRoute(pDC, &SupplyTree::CentralRoute,0,255,0);
//TempCode DAW 22Jun99 	PlotMainRoute(pDC, &SupplyTree::EastRoute,0,0,255);
//TEMPCODE JIM 16/03/99 	PlotAirfields(pDC);
//	PlotSupplyingRoutes(pDC);
// 	PlotInvalidateBoxes(pDC);
#endif
}



void CMIGView::PlotRoutes(CDC* pDC,UniqueID onlythrough)
{

//	bool	hilighton = false;
//	int higroup = 2;
	if  (Save_Data.mapfilters[FILT_ROUTES])
	{
		for (int pack=0;pack<Profile::MAX_PACKS;pack++)
		{
			for (int wave=0;wave<Profile::MAX_WAVES;wave++)
			{
				for (int group=0;group<Profile::MAX_GROUPS;group++)
				{
					if  (		(Todays_Packages.hiwave != wave)
							||	(Todays_Packages.hipack != pack)
							)
						PlotRoute(pDC, pack, wave, group, false,onlythrough);
				}
			}
		}
	}
	for (int group=0;group<Profile::MAX_GROUPS;group++)
		PlotRoute(pDC, Todays_Packages.hipack, Todays_Packages.hiwave, group, true,onlythrough);


}
FileNum  CMIGView::DrawIconTest(ItemBasePtr p, UniqueID i, bool hilight,UniqueIDField& redUIDs, FileNum* FL_Icon) 
{
	FileNum	filenum = FIL_NULL;
	FileNum	hifilenum = FIL_NULL;
	bool dodrawonsize=true;
	if (p==NULL)
		dodrawonsize=false;
	else
	{
//DeadCode DAW 22Jun99 		if (p->Status.deaded)
//DeadCode DAW 22Jun99 		{
//DeadCode DAW 22Jun99 			if (hilight)
//DeadCode DAW 22Jun99 				filenum =FIL_ICON_DEAD_ON;
//DeadCode DAW 22Jun99 			else
//DeadCode DAW 22Jun99 				filenum =FIL_ICON_DEAD_OFF;
//DeadCode DAW 22Jun99 			dodrawonsize=false;
//DeadCode DAW 22Jun99 		}
//DeadCode DAW 22Jun99 		else

		if (((info_base*)p)->SGT != UID_Null)
			if (((Item*)p)->shape == EMPTY)
				dodrawonsize=false;
			else
				if (m_zoom < ZOOMTHRESHOLDDETAIL)
					dodrawonsize=false;
	}
	if (dodrawonsize)
	{
		int uidband;
		if (((info_base*)p)->SGT != UID_Null)
			uidband=Persons2::getbandfromUID(((info_base*)p)->SGT);	
		else	
			uidband=Persons2::getbandfromUID(i);

	

//DEADCODE RDH 13/02/99 	if (	 ( 	(SupplyTree::WestRoute.frontline->associated_item == i)
//DEADCODE RDH 13/02/99 				||	(SupplyTree::CentralRoute.frontline->associated_item == i)
//DEADCODE RDH 13/02/99 				||	(SupplyTree::EastRoute.frontline->associated_item == i)
//DEADCODE RDH 13/02/99 			 )
//DEADCODE RDH 13/02/99 		  &&	(		(Save_Data.mapfilters[FILT_FRONTLINE])
//DEADCODE RDH 13/02/99 				||	(hilight)
//DEADCODE RDH 13/02/99 					)
//DEADCODE RDH 13/02/99 		)
	if (	 ( 	(SupplyTree::WestRoute.frontline->forward->suppliee->associated_item == i)
				||	(SupplyTree::CentralRoute.frontline->forward->suppliee->associated_item == i)
				||	(SupplyTree::EastRoute.frontline->forward->suppliee->associated_item == i)
			 )
		  &&	(		(Save_Data.mapfilters[FILT_FRONTLINE])
				||	(hilight)
					)
		)
	{
		if	(m_zoom>ZOOMTHRESHOLD2)	
		{	
			filenum =FIL_ICON_FRONTLINE;
			hifilenum =FIL_ICON_FRONTLINE_OFF2;
		}else
		{
			filenum =FIL_ICON_SMALL_FRONTLINE;
			hifilenum =FIL_ICON_SMALL_FRONTLINE_OFF2;
		}

	}else
	{
		//note all the big icons are named incorrectly: on is off!!!
		switch (uidband)
		{
			case		WayPointBAND:
			{
				int pack, wave, g;
				Profile::GetPackageFromWP(i, pack, wave, g);

				if  (		(		(Todays_Packages.hiwave == wave)
								&&	(Todays_Packages.hipack == pack)
							)
							||
							(		(Save_Data.mapfilters[FILT_ROUTES])
								||	(hilight)
							)
					)
				{
					info_waypoint* wp=*Persons2::ConvertPtrUID(i);
					if  (		(		(Save_Data.mapfilters[FILT_MAINWP])
									||	(hilight)
								)
							&&	((wp->applygroup==ENABLE_COMPLEX_VAL))
						)
					{
						filenum =FIL_ICON_MAINWP;
						hifilenum =FIL_ICON_MAINWP_OFF2;
					}
					if  (		(		(Save_Data.mapfilters[FILT_SUBWP])
									||	(hilight)
								)
							&&	((wp->applygroup!=ENABLE_COMPLEX_VAL))
							&&	(//don't display wp for flights that don't exist //RDH 15/02/99
										(wp->applyflight ==ENABLE_COMPLEX_VAL)
									||	(	(wp->applyflight < Todays_Packages[pack][wave][g].numflights)
										)
								)
						)

					{
						filenum =FIL_ICON_SUBWP;
						hifilenum =FIL_ICON_SUBOFF2;
					}
				}
				break;
			}
			case		RedRailBand:
			{
				SupplyNode* node;
				SupplyTree::Supply2UID	reftype;
				node = SupplyTree::FindSupplyNodeForItem(i,&reftype);
				if (		(node->status == BEHINDREDLINES)
						||	(node->status == FRONTLINE)
				   )
				{
					if (		(Save_Data.mapfilters[FILT_RED_TRAIN])
							||	(hilight)
						)
					{
						filenum =FIL_ICON_R_TRAIN_ON;
						hifilenum =FIL_ICON_R_TRAIN_OFF2;
					}
					break;
				}
			}
			case		RedRoadBAND:
			{
				SupplyNode* node;
				SupplyTree::Supply2UID	reftype;
				node = SupplyTree::FindSupplyNodeForItem(i,&reftype);
				if (		(node->status == BEHINDREDLINES)
						||	(node->status == FRONTLINE)
					)
				{
					if (		(Save_Data.mapfilters[FILT_RED_TRUCK])
							||	(hilight)
						)
					{
						filenum =FIL_ICON_R_TRUCK_ON;
						hifilenum =FIL_ICON_R_TRUCK_OFF2;
					}
				}
				break;
			}
			case		AmberAirfieldBAND:
			{
				Nationality nat=SupplyTree::GetNatForUID(i,redUIDs);
				if (nat==NAT_BLUE)
				{
					if (		(Save_Data.mapfilters[FILT_BLUE_AIRFIELDS])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_B_AIRFIELD_ON;
						hifilenum =FIL_ICON_B_AIRFIELD_OFF2;
					}
				}
				else
				{
					if (		(Save_Data.mapfilters[FILT_RED_AIRFIELDS])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_R_AIRFIELD_ON;
						hifilenum =FIL_ICON_R_AIRFIELD_OFF2;
					}
				}

				break;
			}
			case		AmberBattleNodeBAND:
			{
				if (m_zoom > ZOOMTHRESHOLDFRONTLINE)
				{
					hifilenum = FL_Icon[i - AmberBattleNodeBAND];
					if (hifilenum)
					{
						if (!hilight)
							filenum = (FileNum)((int)hifilenum - 2);

						if (		(!hilight)
								&&	(		(		(!Save_Data.mapfilters[FILT_RED_TROOP])
												&&	(hifilenum == FIL_ICON_R_TROOP_OFF2)
											)
										||	(		(!Save_Data.mapfilters[FILT_RED_TRUCK])
												&&	(hifilenum == FIL_ICON_R_TRUCK_OFF2)
											)
										||	(		(!Save_Data.mapfilters[FILT_RED_TANK])
												&&	(hifilenum == FIL_ICON_R_TANK_OFF2)
											)
										||	(		(!Save_Data.mapfilters[FILT_RED_ARTIE])
												&&	(hifilenum == FIL_ICON_R_ARTILLERY_OFF2)
											)
										||	(		(!Save_Data.mapfilters[FILT_BLUE_TROOP])
												&&	(hifilenum == FIL_ICON_B_TROOP_OFF2)
											)
										||	(		(!Save_Data.mapfilters[FILT_BLUE_TRUCK])
												&&	(hifilenum == FIL_ICON_B_TRUCK_OFF2)
											)
										||	(		(!Save_Data.mapfilters[FILT_BLUE_TANK])
												&&	(hifilenum == FIL_ICON_B_TANK_OFF2)
											)
										||	(		(!Save_Data.mapfilters[FILT_BLUE_ARTIE])
												&&	(hifilenum == FIL_ICON_B_ARTILLERY_OFF2)
											)


									)
							)
						{
							filenum = FIL_NULL;
							hifilenum = FIL_NULL;
						}
					}
				}
				break;
			}

			case		RedAAASiteBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		BlueAAASiteBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		RedAAALargeBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case  		AmberCivilianBAND:
			{
				Nationality nat=SupplyTree::GetNatForUID(i,redUIDs);
				if (nat==NAT_BLUE)
				{
					if (		(Save_Data.mapfilters[FILT_BLUE_CIVILIAN])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_B_CIVILIAN_ON;
						hifilenum =FIL_ICON_B_CIVILIAN_OFF2;
					}
				}else
				{
					if (		(Save_Data.mapfilters[FILT_RED_CIVILIAN])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_R_CIVILIAN_ON;
						hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
					}
				}
				break;
			}
			case		AmberSupplyBAND:
			{
				Nationality nat=SupplyTree::GetNatForUID(i,redUIDs);
				if (nat==NAT_BLUE)
				{
					if (		(Save_Data.mapfilters[FILT_BLUE_SUPPLY])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_B_SUPPLY_ON;
						hifilenum =FIL_ICON_B_SUPPLY_OFF2;
					}
				}else
				{
					if (		(Save_Data.mapfilters[FILT_RED_SUPPLY])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_R_SUPPLY_ON;
						hifilenum =FIL_ICON_R_SUPPLY_OFF2;
					}
				}
				break;
			}
			case		AmberBridgeBAND:
			{
				Nationality nat=SupplyTree::GetNatForUID(i,redUIDs);
				if (nat==NAT_BLUE)
				{
					if (		(Save_Data.mapfilters[FILT_BLUE_BRIDGE])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_B_BRIDGE_ON;
						hifilenum =FIL_ICON_B_BRIDGE_OFF2;
					}
				}else
				{
					if (		(Save_Data.mapfilters[FILT_RED_BRIDGE])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_R_BRIDGE_ON;
						hifilenum =FIL_ICON_R_BRIDGE_OFF2;
					}
				}
				break;
			}
			case		AmberMYardBAND:
			{
				Nationality nat=SupplyTree::GetNatForUID(i,redUIDs);
				if (nat==NAT_BLUE)
				{
					if (		(Save_Data.mapfilters[FILT_BLUE_MYARD])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_B_MARSHALLINGYARD_ON;
						hifilenum =FIL_ICON_B_MARSHALLINGYARD_OFF2;
					}
				}else
				{
					if (		(Save_Data.mapfilters[FILT_RED_MYARD])
							||	(hilight)
					)
					{
						filenum =FIL_ICON_R_MARSHALLINGYARD_ON;
						hifilenum =FIL_ICON_R_MARSHALLINGYARD_OFF2;
					}
				}
				break;

			}
			case		RedTrainBAND:
			{
				if (		(Save_Data.mapfilters[FILT_RED_TRAIN])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		RedTruckBAND:
			{
				if (		(Save_Data.mapfilters[FILT_RED_TRUCK])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		RedTruckParkBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
//DEADCODE RDH 22/06/99 			case		RedTroopBAND:
//DEADCODE RDH 22/06/99 			{
//DEADCODE RDH 22/06/99 				if (		(Save_Data.mapfilters[FILT_RED_TROOP])
//DEADCODE RDH 22/06/99 						||	(hilight)
//DEADCODE RDH 22/06/99 					)
//DEADCODE RDH 22/06/99 				{
//DEADCODE RDH 22/06/99 					filenum =FIL_ICON_R_CIVILIAN_ON;
//DEADCODE RDH 22/06/99 					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
//DEADCODE RDH 22/06/99 				}
//DEADCODE RDH 22/06/99 				break;
//DEADCODE RDH 22/06/99 			}
			case		BlueTroopBAND:
			{
				if (		(Save_Data.mapfilters[FILT_BLUE_TROOP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		RedArmourBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		BlueArmourBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		RedArtilleryBAND:
			{
				if (		(Save_Data.mapfilters[FILT_RED_ARTIE])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		BlueArtilleryBAND:
			{
				if (		(Save_Data.mapfilters[FILT_BLUE_ARTIE])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		RedCombatVehicleBAND :
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		BlueCombatVehicleBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		GreenVetoedBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		GreenMobileBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case	  	GreenMiscBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		RedHQBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		BlueHQBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		RedBoatBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		BlueBoatBAND:
			case	BlueMilitaryBAND:
			{
				//empty band
				//No icon required
				//used for egress points, 
				//from Japan, china airspace, supply starting points
				break;
			}
			case		GreenBoatBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		RedStaticAcBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			case		BlueStaticACBAND:
			{
				if (		(Save_Data.mapfilters[FILT_MAINWP])
						||	(hilight)
					)
				{
					filenum =FIL_ICON_R_CIVILIAN_ON;
					hifilenum =FIL_ICON_R_CIVILIAN_OFF2;
				}
				break;
			}
			default:
			{
				filenum =FIL_ICON_R_AIRCRAFT_ON;
				break;
			}
		}
		if	(filenum != FIL_NULL)								//DAW 20Jun99
			if (p->Status.deaded)
			{
					filenum =FIL_ICON_DEAD_ON;
					hifilenum =FIL_ICON_DEAD_OFF;
			}

		if (hilight)
			filenum=hifilenum;										  //JIM 29/05/99


		if	(		(filenum != FIL_NULL)
				&&	(m_zoom<=ZOOMTHRESHOLD2)	
			)
		{
			switch (filenum)
			{
				case	FIL_ICON_FRONTLINE:
				{
					filenum = FIL_ICON_SMALL_FRONTLINE;
					break;
				}
				case	FIL_ICON_FRONTLINE_OFF2:
				{
					filenum = FIL_ICON_SMALL_FRONTLINE_OFF2;
					break;
				}
				case	   FIL_ICON_MAINWP:
				case	   FIL_ICON_SUBWP:
				{
					filenum =FIL_ICON_GREEN_OFF;
					break;

				}
				case	   FIL_ICON_MAINWP_OFF2:
				case	   FIL_ICON_SUBOFF2:
				{
			 		filenum =FIL_ICON_GREEN_ON;
			 		break;
				}
				case	   FIL_ICON_R_CIVILIAN_ON:
				case		FIL_ICON_R_AIRCRAFT_ON:
				case		FIL_ICON_R_AIRFIELD_ON:
				case		FIL_ICON_R_ARTILLERY_ON:
				case		FIL_ICON_R_BRIDGE_ON:
				case		FIL_ICON_R_MARSHALLINGYARD_ON:
				case		FIL_ICON_R_RAILLINK_ON:
				case		FIL_ICON_R_ROADLINK_ON:
				case		FIL_ICON_R_SUPPLY_ON:
				case		FIL_ICON_R_TANK_ON:
				case		FIL_ICON_R_TRAIN_ON:
				case		FIL_ICON_R_TROOP_ON:
				case		FIL_ICON_R_TRUCK_ON:

				{
			 		filenum =FIL_ICON_RED_OFF2;
			 		break;
				}
				case	   FIL_ICON_R_CIVILIAN_OFF2:
				case		FIL_ICON_R_AIRCRAFT_OFF2:
				case		FIL_ICON_R_AIRFIELD_OFF2:
				case		FIL_ICON_R_ARTILLERY_OFF2:
				case		FIL_ICON_R_BRIDGE_OFF2:
				case		FIL_ICON_R_MARSHALLINGYARD_OFF1:
				case		FIL_ICON_R_ROADLINK_OFF2:
				case		FIL_ICON_R_SUPPLY_OFF2:
				case		FIL_ICON_R_RAILLINK_OFF2:
				case		FIL_ICON_R_TANK_OFF2:
				case		FIL_ICON_R_TRAIN_OFF2:
				case		FIL_ICON_R_TROOP_OFF2:
				case		FIL_ICON_R_TRUCK_OFF2:

				{
			 		filenum =FIL_ICON_RED_ON;
			 		break;
				}
				case	   FIL_ICON_B_CIVILIAN_ON:
				case	   FIL_ICON_B_AIRFIELD_ON:
				case		FIL_ICON_B_AIRCRAFT_ON:
				case		FIL_ICON_B_ARTILLERY_ON:
				case		FIL_ICON_B_BRIDGE_ON:
				case		FIL_ICON_B_MARSHALLINGYARD_ON:
				case		FIL_ICON_B_RAILLINK_ON:
				case		FIL_ICON_B_ROADLINK_ON:
				case		FIL_ICON_B_SUPPLY_ON:
				case		FIL_ICON_B_TANK_ON:
				case		FIL_ICON_B_TRAIN_ON:
				case		FIL_ICON_B_TROOP_ON:
				case		FIL_ICON_B_TRUCK_ON:
				{
			 		filenum =FIL_ICON_BLUE_OFF2;
			 		break;
				}
				case	   FIL_ICON_B_CIVILIAN_OFF2:
				case	   FIL_ICON_B_AIRFIELD_OFF2:
				case		FIL_ICON_B_AIRCRAFT_OFF2:
				case		FIL_ICON_B_ARTILLERY_OFF2:
				case		FIL_ICON_B_BRIDGE_OFF2:
				case		FIL_ICON_B_MARSHALLINGYARD_OFF2:
				case		FIL_ICON_B_RAILLINK_OFF2:
				case		FIL_ICON_B_ROADLINK_OFF2:
				case		FIL_ICON_B_SUPPLY_OFF2:
				case		FIL_ICON_B_TANK_OFF2:
				case		FIL_ICON_B_TRAIN_OFF2:
				case		FIL_ICON_B_TROOP_OFF2:
				case		FIL_ICON_B_TRUCK_OFF2:
				{
			 		filenum =FIL_ICON_BLUE_ON;
			 		break;
				}
				default:
				{
					filenum =FIL_ICON_YELLOW_ON;
					break;
				}

			}

		}
	}
  }
  return (filenum);
}
//



//• DCB_ACCUMULATE Bounding rectangle accumulation is occurring.
//• DCB_RESET Bounding rectangle is empty.
//• DCB_SET Bounding rectangle is not empty.
//• DCB_ENABLE Bounding accumulation is on.
//• DCB_DISABLE
void CMIGView::DrawIcons(HDC hDC, CDC* pDC,UniqueIDField& redUIDs, FileNum* FL_Icon)
{
	ItemBasePtr p;
	int px,py;
	FileNum  f;
	RECT	bounds;
	int rv;
	if ((rv=pDC->GetBoundsRect(&bounds,0))==DCB_RESET)
			GetClientRect(&bounds);  // top left is always 0,0
	else
		if (rv!=DCB_SET)
			assert(0);
	int	Wx1,Wx2,Wz1,Wz2;
	int radius=
		WorldXY(Wx1,Wz1,bounds.left,bounds.bottom);
		WorldXY(Wx2,Wz2,bounds.right,bounds.top);
	Wx1-=radius;
	Wx2+=radius;
	Wz1-=radius;
	Wz2+=radius;
//	m_bDontUpdateBitmaps=TRUE;
	// should work out what the worldrect is here for quicker referencing...
	for (int i=UID_Null;i<IllegalSepID;i++)
	{
		p=Persons2::ConvertPtrUID(UniqueID(i));
		if (	p 
			&&	i!=m_mapdlg.m_buttonid
			&&	p->World.X<Wx2 && p->World.X>Wx1
			&&	p->World.Z<Wz2 && p->World.Z>Wz1
			)

		{
			f = DrawIconTest( p, UniqueID(i), false,redUIDs,FL_Icon);
		  	if ((f))
			{
				ScreenXY(p,px,py);
				DrawIcon(hDC,px,py, f);
			}
				
		}
	}
	p=Persons2::ConvertPtrUID(UniqueID(m_mapdlg.m_buttonid));
	if (p)
	{
		f = DrawIconTest(p, UniqueID(m_mapdlg.m_buttonid), true,redUIDs,FL_Icon);
	  	if ((f))
		{
		 	ScreenXY(p,px,py);
			DrawIcon(hDC,px,py, f);
		}
	}

}


void CMIGView::UpdateBitmaps(CDC* pDC)
{
//	if (m_bDontUpdateBitmaps) return;
	int areax;
	int areay;
	if (m_zoom>=ZOOMTHRESHOLD3)
	{
		areax=16;
		areay=28; // area of bitmap array
	}
	else if (m_zoom>=ZOOMTHRESHOLD2)
	{
		areax=4;
		areay=8;
	}
	else if (m_zoom>ZOOMTHRESHOLD1)
	{
		areax=1;
		areay=1;
	}
	int zoomsquaresize;
	if (m_zoom>=ZOOMTHRESHOLD3)
		zoomsquaresize=64*m_zoom;	// size of one side of bitmap compensated for zoom
	else if (m_zoom>=ZOOMTHRESHOLD2)
		zoomsquaresize=256*m_zoom;
	else zoomsquaresize=1024*m_zoom;
	int startx=m_scrollpoint.x/zoomsquaresize;
	int starty=m_scrollpoint.y/zoomsquaresize;
	const int squaresize=256; // size of one side of bitmap
	CRect rect;
	GetClientRect(rect);  // top left is always 0,0
//	CDC* pDC;
//	pDC = m_mapdlg.GetDC();
	HDC hDC;
	hDC = pDC->GetSafeHdc( );  // gets and stores handle of mapdlg DC	
	assert(areax==1 || startx<areax)
	assert(areay==1 || starty<areay)
	int endx=min(startx+(rect.right/zoomsquaresize)+2,areax);
	int endy=min(starty+(rect.bottom/zoomsquaresize)+2,areay);
	BYTE* pData;

	if (m_zoom>=ZOOMTHRESHOLD3)
	{
		//make sure all portions are loaded before starting to draw
		{for (int x=startx;x<endx;x++)
			for (int y=starty;y<endy;y++)
				fileblock(m_MapFiles[27-y][x],PalTrans);
		}
		for (int x=startx;x<endx;x++)
		{
			for (int y=starty;y<endy;y++)
			{
				pData=(BYTE*)getdata(fileblock(m_MapFiles[27-y][x],PalTrans));
				if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
				{
					// now render it...
					BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
					BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
					pData+=pFile->bfOffBits;
					if (m_zoom>25)
					{
						int X=((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
							Y=((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
							SQS=zoomsquaresize/2+1,
							sqsp1o2=(squaresize+1)/2;
						StretchDIBits(hDC,X,Y+SQS,
							SQS,SQS,
							0,0,sqsp1o2,sqsp1o2,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
						StretchDIBits(hDC,X+SQS,Y+SQS,
							SQS,SQS,
							squaresize/2,0,sqsp1o2,sqsp1o2,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
						StretchDIBits(hDC,X,Y,
							SQS,SQS,
							0,squaresize/2,sqsp1o2,sqsp1o2,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
						StretchDIBits(hDC,X+SQS,Y,
							SQS,SQS,
							squaresize/2,squaresize/2,sqsp1o2,sqsp1o2,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
					}
					else
					{
						StretchDIBits(hDC,					
							((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
							((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
							zoomsquaresize,zoomsquaresize,
							0,0,squaresize,squaresize,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
					}
				}
			}
		}
	}			
	else if (m_zoom>=ZOOMTHRESHOLD2)
	{
		//make sure all portions are loaded before starting to draw
		{for (int x=startx;x<endx;x++)
			for (int y=starty;y<endy;y++)
				fileblock(FileNum(FIL_MIDMAP+x+(6*4)-(4*y)));
		}
		for (int x=startx;x<endx;x++)
		{
			for (int y=starty;y<endy;y++)
			{
				pData=(BYTE*)getdata(fileblock(FileNum(FIL_MIDMAP+x+(6*4)-(4*y))));
				if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
				{
					// now render it...
					BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
					BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
					pData+=pFile->bfOffBits;
					StretchDIBits(hDC,					
						((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
						((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
						zoomsquaresize,zoomsquaresize,
						0,0,squaresize,squaresize,
						pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
				}
			}
		}
	}
	else
	{
		// Draw thumbnail...
		for (int y=0;y<2;y++)
		{
			pData=(BYTE*)getdata(fileblock(FileNum(FIL_THUMBTOP+y)));
			if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
			{
				// now render it...
				BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
				BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
				pData+=pFile->bfOffBits;
				StretchDIBits(hDC,					
					-m_scrollpoint.x,
					-m_scrollpoint.y+(y*zoomsquaresize)-(zoomsquaresize/4),
					zoomsquaresize,zoomsquaresize,
					0,0,squaresize,squaresize,
					pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
			}
		}
	}
//	if (rect.right>m_size.cx) 
//		pDC->FillSolidRect(CRect(m_size.cx,0,rect.right,rect.bottom),
//							RGB(63,80,111));
//	if (rect.bottom>m_size.cy)
//		pDC->FillSolidRect(CRect(0,m_size.cy,rect.right,rect.bottom),
//							RGB(63,80,111));
	if (rect.right>m_size.cx) 
		pDC->FillSolidRect(CRect(m_size.cx,0,rect.right,rect.bottom),
							RGB(58,72,143));
	if (rect.bottom>m_size.cy)
		pDC->FillSolidRect(CRect(0,m_size.cy,rect.right,rect.bottom),
							RGB(58,72,143));
	// now draw the icons...
	UniqueIDField redUIDs;
	SupplyTree::FillNatForUID(redUIDs);

	FileNum  FL_Icon[AmberBattleNodeBANDEND-AmberBattleNodeBAND];
	if (m_zoom > ZOOMTHRESHOLDFRONTLINE)
		SupplyTree::FillFLS_Icons(FL_Icon);

	if (Save_Data.mapfilters[FILT_FRONTLINE])
		PlotFrontLine(pDC);

	DrawIcons(hDC, pDC,redUIDs, FL_Icon);
	// now plot the routes...
	PlotRoutes(pDC);
	//now the hint
	ItemBasePtr p;
	int px,py;
	p=Persons2::ConvertPtrUID(UniqueID(m_mapdlg.m_hintid));
	FileNum  f;
	f = DrawIconTest(p, UniqueID(m_mapdlg.m_hintid), false,redUIDs,FL_Icon);
	if (	(p)	&& (f))
	{
		ScreenXY(p,px,py);
		pDC->SetBkColor(RGB(255,255,255));
		pDC->SetTextColor(RGB(0,0,0));
		int uidband=Persons2::getbandfromUID(UniqueID(m_mapdlg.m_hintid));

		if (uidband == AmberBattleNodeBAND)
		{
			TeamDef		*team=SupplyTree::WestRoute.groundbattle.FindTeamAtLocation(UniqueID(m_mapdlg.m_hintid));
			if (!team) 
				team=SupplyTree::CentralRoute.groundbattle.FindTeamAtLocation(UniqueID(m_mapdlg.m_hintid));
			else if (!team) 
				team=SupplyTree::EastRoute.groundbattle.FindTeamAtLocation(UniqueID(m_mapdlg.m_hintid));
			if (team)
				DrawIconText(pDC,px,py,LoadResString(team->forcename));

			
		}else
			DrawIconText(pDC,px,py,GetTargName(UniqueID(m_mapdlg.m_hintid)));
	}

	PlotDebugInfo(pDC);
//DEADCODE JIM 29/05/99 	m_oldzoom=m_zoom;
	m_drawing=FALSE;
}
/*
void CMIGView::DrawLine(CDC * pDC, int uid1, int uid2)
{
	ItemBasePtr pt1,pt2;
	int px,py;
	pt1=Persons2::ConvertPtrUID(UniqueID(uid1);
	pt2=Persons2::ConvertPtrUID(UniqueID(uid2);
	if (pt1 && pt2)
	{
		px=((p->World.X*m_zoom)/65536)
		py=(1792*m_zoom)-((p->World.Z*m_zoom)/65536);
		pDC->


	}
}
*/
void CMIGView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
/*
	CPoint oldscrollpoint=m_scrollpoint;
	if (nSBCode == SB_LINEDOWN) m_scrollpoint.y +=40;
	if (nSBCode == SB_LINEUP) m_scrollpoint.y -=40;
	if (nSBCode == SB_PAGEDOWN) m_scrollpoint.y += 400;
	if (nSBCode == SB_PAGEUP) m_scrollpoint.y -= 400;
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) 
	{
		if (m_drawing) return;
		if (m_scrollpoint.y!=nPos)
		{
			m_drawing=TRUE;
			m_scrollpoint.y=nPos;
		}
	}
//	if (nSBCode != SB_THUMBPOSITION && nSBCode != SB_THUMBTRACK) m_mapdlg.Invalidate();
	UpdateScrollbars();
	m_mapdlg.ScrollWindow(oldscrollpoint.x-m_scrollpoint.x,oldscrollpoint.y-m_scrollpoint.y);
*/
}


void CMIGView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
/*	CPoint oldscrollpoint=m_scrollpoint;
	if (nSBCode == SB_LINERIGHT) m_scrollpoint.x +=40;
	if (nSBCode == SB_LINELEFT) m_scrollpoint.x -=40;
	if (nSBCode == SB_PAGERIGHT) m_scrollpoint.x += 400;
	if (nSBCode == SB_PAGELEFT) m_scrollpoint.x -= 400;
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
	{
		if (m_drawing) return;
		if (m_scrollpoint.x!=nPos)
		{
			m_drawing=TRUE;
			m_scrollpoint.x=nPos;
		}
	}
//	if (nSBCode != SB_THUMBPOSITION && nSBCode != SB_THUMBTRACK) m_mapdlg.Invalidate();
	UpdateScrollbars();
	m_mapdlg.ScrollWindow(oldscrollpoint.x-m_scrollpoint.x,oldscrollpoint.y-m_scrollpoint.y);
*/
}

void CMIGView::UpdateScrollbars()
{

	if (!m_mapdlg.m_hWnd) return;
	if (m_currentpage!=0)
	{
		m_rHorzScrollBar.ShowWindow(SW_HIDE);
		m_rVertScrollBar.ShowWindow(SW_HIDE);
/*		SCROLLINFO scrollinfo;
		scrollinfo.cbSize=sizeof(SCROLLINFO);
		scrollinfo.fMask=SIF_ALL;// | SIF_DISABLENOSCROLL; 
		scrollinfo.nMin=0;
		scrollinfo.nMax=0;
		scrollinfo.nPage=0;
		scrollinfo.nPos=0; 
		scrollinfo.nTrackPos=0; 
		SetScrollInfo(SB_HORZ,&scrollinfo,TRUE);
		scrollinfo.nMax=0;
		scrollinfo.nPage=0;
		scrollinfo.nPos=0;
		SetScrollInfo(SB_VERT,&scrollinfo,TRUE);
	*/
	}
	else
	{
		CRect rect;
		GetClientRect(rect);
		m_scrollpoint.x=min(m_scrollpoint.x,m_size.cx-rect.right);
		m_scrollpoint.x=max(m_scrollpoint.x,0);
		m_scrollpoint.y=min(m_scrollpoint.y,m_size.cy-rect.bottom);
		m_scrollpoint.y=max(m_scrollpoint.y,0);
		int vert=0;
		int horz=0;
		if (rect.right<(int)m_size.cx)
		{
			m_rHorzScrollBar.SetMinValue(0);
			m_rHorzScrollBar.SetMaxValue(m_size.cx-rect.right);
			m_rHorzScrollBar.SetPageSize(rect.right);
			m_rHorzScrollBar.SetScrollPos(m_scrollpoint.x);
			horz=16;
			m_rHorzScrollBar.ShowWindow(SW_SHOW);
			m_rHorzScrollBar.BringWindowToTop();
		}
		else
			m_rHorzScrollBar.ShowWindow(SW_HIDE);
		if (rect.bottom<(int)m_size.cy)
		{
			m_rVertScrollBar.SetMinValue(0);
			m_rVertScrollBar.SetMaxValue(m_size.cy-rect.bottom);
			m_rVertScrollBar.SetPageSize(rect.bottom);
			m_rVertScrollBar.SetScrollPos(m_scrollpoint.y);
			vert=16;
			m_rVertScrollBar.ShowWindow(SW_SHOW);
			m_rVertScrollBar.BringWindowToTop();
		}
		else
			m_rVertScrollBar.ShowWindow(SW_HIDE);
		m_mapdlg.MoveWindow(0,0,rect.right-vert,rect.bottom-horz);
		m_rVertScrollBar.MoveWindow(rect.right-16,0,16,rect.bottom-horz);
		m_rHorzScrollBar.MoveWindow(0,rect.bottom-16,rect.right-vert,16);
/*		SCROLLINFO scrollinfo;
		scrollinfo.cbSize=sizeof(SCROLLINFO);
		scrollinfo.fMask=SIF_ALL;// | SIF_DISABLENOSCROLL; 
		scrollinfo.nMin=0;
		scrollinfo.nMax=m_size.cx;
		scrollinfo.nPage=rect.right;
		scrollinfo.nPos=m_scrollpoint.x; 
		scrollinfo.nTrackPos=0; 
		SetScrollInfo(SB_HORZ,&scrollinfo,TRUE);
		scrollinfo.nMax=m_size.cy;
		scrollinfo.nPage=rect.bottom;
		scrollinfo.nPos=m_scrollpoint.y;
		SetScrollInfo(SB_VERT,&scrollinfo,TRUE);
*/
#ifndef	MIG_DEMO_VER
		if (m_thumbnail)
			m_thumbnail->InvalidateMapOnly();
#endif
	}
}

void CMIGView::OnMove(int x, int y) 
{
	CView::OnMove(x, y);
	
//DEADCODE DAW 07/05/99 	// TODO: Add your message handler code here
//DEADCODE DAW 07/05/99 	if (m_doIexist>2)
//DEADCODE DAW 07/05/99 	{
//DEADCODE DAW 07/05/99 		if (m_pfullpane) m_pfullpane->UpdateSize();
//DEADCODE DAW 07/05/99 		if (m_currentpage==0) m_mapdlg.Invalidate();
//DEADCODE DAW 07/05/99 //DeadCode JIM 15Jul98 		UpdateBitmaps();
//DEADCODE DAW 07/05/99 //DeadCode JIM 15Jul98 		if (m_pfullpane) m_pfullpane->UpdateSize();
//DEADCODE DAW 07/05/99 		RecalcLayout();
//DEADCODE DAW 07/05/99 	}
//DEADCODE DAW 07/05/99 //	UpdateScrollbars();
	
}

void CMIGView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if (m_doIexist>2)
	{
		if (m_pfullpane) m_pfullpane->UpdateSize();
		if (m_currentpage==0) m_mapdlg.Invalidate();
//DeadCode JIM 15Jul98 		UpdateBitmaps();
//DeadCode JIM 15Jul98 		if (m_pfullpane) m_pfullpane->UpdateSize();
	}
	UpdateScrollbars();
	m_doIexist++; // window only exists after it has been initially sized twice.
}

BOOL CMIGView::OnEraseBkgnd(CDC* pDC) 
{
	if (m_currentpage!=0)
//DEADCODE JIM 19/06/99 		if (Rtestsh1::Start3d(Rtestsh1::S3D_DONEBACK))
		{
			CRect rect;
			GetClientRect(rect);
			pDC->FillRect(rect, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
		}
	return TRUE;
}

void CMIGView::OnChangeToTitle() 
{
	LaunchFullPane(&RFullPanelDial::introsmack);
}

void CMIGView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnLButtonDown(nFlags, point);

}

void CMIGView::OnMouseMove(UINT nFlags, CPoint point) 
{
		CRect rect;
		GetWindowRect(rect);
		m_popupPoint=point-rect.TopLeft();

	CView::OnMouseMove(nFlags, point);
}

void CMIGView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CView::OnLButtonUp(nFlags, point);
}

#ifndef	MIG_DEMO_VER

void CMIGView::LaunchMap(bool firsttime)
{
///	Persons4::StartUpMapWorld();		//do whenever we go to the map screen
	m_pfullpane->DestroyWindow();
	m_currentpage=0;
	m_pfullpane=NULL;
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	main->ShowToolbars(firsttime);
	main->m_titlebar.Redraw();
	m_mapdlg.ShowWindow(SW_SHOW);
	m_mapdlg.BringWindowToTop();
	m_mapdlg.Invalidate();
	UpdateScrollbars();

//DeadCode JIM 15Jul98 	Persons4::StartUpMapWorld();		//do whenever we go to the map screen
//	Persons4::ShutDownMapWorld();		//do whenever we come off the map screen
}

#endif

void CMIGView::LaunchFullPane(FullScreen * startscreen)
{
//	Persons4::ShutDownMapWorld();		//do whenever we come off the map screen
	m_currentpage=1;					//no.. only if going somewhere nasty.
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
#ifndef	MIG_DEMO_VER
	if (!main->m_bHideToolbars)
		main->HideToolbars();
	else
		main->m_wndSystemBox->InDialAncestor()->ShowWindow(SW_HIDE);		  //JIM 14/06/99
	main->m_toolbar1.CloseLoggedChildren();
	main->m_toolbar2.CloseLoggedChildren();
	main->m_toolbar3.CloseLoggedChildren();
	main->m_toolbar4.CloseLoggedChildren();
	main->m_toolbar5.CloseLoggedChildren();
	m_mapdlg.ShowWindow(SW_HIDE);
#endif
	UpdateScrollbars();
	main->OnGoBig();	//ShowWindow(SW_SHOWMAXIMIZED);
	m_pfullpane=new RFullPanelDial; // must create it on the heap
	m_pfullpane->LaunchMain(startscreen);
}

void CMIGView::OnScrollHorzScrollbar(long nPos) 
{
	if (m_drawing) return;
	CPoint oldscrollpoint=m_scrollpoint;
	if (m_scrollpoint.x!=nPos)
	{
		m_drawing=TRUE;
		m_scrollpoint.x=nPos;
	}
	UpdateScrollbars();
	m_mapdlg.ScrollWindow(oldscrollpoint.x-m_scrollpoint.x,oldscrollpoint.y-m_scrollpoint.y);
}

void CMIGView::OnScrollVertScrollbar(long nPos) 
{
	if (m_drawing) return;
	CPoint oldscrollpoint=m_scrollpoint;
	if (m_scrollpoint.y!=nPos)
	{
		m_drawing=TRUE;
		m_scrollpoint.y=nPos;
	}
	UpdateScrollbars();
	m_mapdlg.ScrollWindow(oldscrollpoint.x-m_scrollpoint.x,oldscrollpoint.y-m_scrollpoint.y);
}

BYTE* CMIGView::OnGetFile(int filenum)
{
	if (m_pfileblock)
	{
		delete m_pfileblock;
		m_pfileblock=NULL;
	}
	if (!(filenum>0x6800 && filenum<0x7100))  //only directories 104..113
		return NULL;
	m_pfileblock=new fileblock((FileNum)filenum);
	return (BYTE*)getdata(m_pfileblock);
}

void CMIGView::OnReleaseLastFile()
{
	delete m_pfileblock;
	m_pfileblock=NULL;
}

CDC* CMIGView::OnGetOffScreenDC()
{
	return &g_OffScreenDC;
}

void	CMIGView::SetHiLightInfo(int	pack, int wave, int	group,
						UniqueID	wp,bool fullgroup)

{
	fullgroup|=(Todays_Packages.hipack!=pack || Todays_Packages.hiwave!=wave);
	if (Todays_Packages.hipack!=-1)
		if (fullgroup)
		{
			PlotRoute(NULL, Todays_Packages.hipack, Todays_Packages.hiwave, 0, false);
			PlotRoute(NULL, Todays_Packages.hipack, Todays_Packages.hiwave, 1, false);
			PlotRoute(NULL, Todays_Packages.hipack, Todays_Packages.hiwave, 2, false);
		}
		else
			PlotRoute(NULL, Todays_Packages.hipack, Todays_Packages.hiwave, Todays_Packages.higroup, false);
	Todays_Packages.hipack = pack;
	Todays_Packages.hiwave = wave;
	Todays_Packages.higroup = group;
	Todays_Packages.hiwp = wp;
	RDialog::m_pView->m_mapdlg.ResetIcon(Todays_Packages.hiwp);

	if (fullgroup)
	{
		PlotRoute(NULL, pack, wave, 0, group==0);
		PlotRoute(NULL, pack, wave, 1, group==1);
		PlotRoute(NULL, pack, wave, 2, group==2);
		InvalidateJapan();
	}
	else
		PlotRoute(NULL, pack, wave, group,true);

//	CDC* pdc;
//	pdc=m_mapdlg.GetDC();
//	PlotRoutes(pdc);
//	ReleaseDC(pdc);
}			  



CScrollBar* CMIGView::GetScrollBarCtrl(int nBar) const
{
	// TODO: Add your specialized code here and/or call the base class
	//CWnd::OnRegisteredMouseWheel
	return CView::GetScrollBarCtrl(nBar);
}

BOOL CMIGView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if (Rtestsh1::Start3d(Rtestsh1::S3D_STOPPED)==Rtestsh1::S3D_GOING)
		return false;
	if (!m_currentpage)
	{
	// TODO: Add your message handler code here and/or call default
//	::AfxTrace("Zoom WHLP(%i,%i)\n", pt.x, pt.y);
//		CRect rect;
//		GetWindowRect(rect);
//		m_popupPoint=pt-rect.TopLeft();
		if (zDelta)
			if (zDelta<0)
				if (zDelta<-600)
					m_zoom=m_zoom*0.5;
				else
					m_zoom=m_zoom*(1.0+zDelta/1200.0);
			else
				if (m_zoom<ZOOMMAX)
					if (zDelta>600)
						m_zoom=m_zoom*1.625;
					else
						m_zoom=m_zoom*(1.0+zDelta/960.0);
				else
					return CView::OnMouseWheel(nFlags, zDelta, pt);
//	::AfxTrace("Zoom WHL (%i,%i)\n", m_popupPoint.x, m_popupPoint.y);
		Zoom(m_popupPoint);
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
