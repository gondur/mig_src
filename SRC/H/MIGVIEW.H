#if !defined(AFX_MIGVIEW_H__DB0342A1_1B07_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_MIGVIEW_H__DB0342A1_1B07_11D1_A1F0_444553540000__INCLUDED_

#include "Dosdefs.h"
#include "MIGDoc.h"
#include "MapDlg.h"	// Added by ClassView
#include "FullPane.h"
#include "rscrlbar.h"
#include "globdefs.h"

class	ItemBase;
typedef	ItemBase* ItemBasePtr;
class	CScaleBar;

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

const int AIRSTRIPS = 4;
const int BRIDGES = 2;
//#include "CustBB.h"
#define ZOOMMIN 0.25
#define ZOOMMAX	50
//32
#define ZOOMTHRESHOLD1 0
#define ZOOMTHRESHOLD2 1
#define ZOOMTHRESHOLD3 4
#define ZOOMTHRESHOLDFRONTLINE 4
#define ZOOMTHRESHOLDDETAIL 16



#define currsheetname CMIGView

#define CreateWindowWithParams (childname,(paramlist)) \
static void rv1_##childname(int retcode); \
\
void currsheetname::On##childname() \
{ \
	if (##childname.m_hWnd == NULL) \
	/* Checks to see if window does not exist */\
		##childname.Init(C##childname::IDD,this,rv1_##childname,##paramlist); \
	/* if not create it */ \
	else \
		##childname.SetFocus(); \
	/* if it exists set the focus to it */ \
} \
\
static void rv2_##childname(int retcode); \
static void rv1_##childname(int retcode) \
{ \
	rv2_##childname(retcode); \
	##childname->DestroyWindow(); \
} \
static void rv2_##childname(int retcode)

//class CResizableDlgBar;
class RDialog;
class RFullPanelDial;
class CRCustomButton;
class	UniqueIDField;
class CThumbnail;
class CMIGView : public CView
{

protected: // create from serialization only
	CMIGView();
	DECLARE_DYNCREATE(CMIGView)

// Attributes
public:
	CMIGDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIGView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate( );
	//}}AFX_VIRTUAL

// Implementation
public:
	void ScreenXY(ItemBasePtr p,int&px,int&py,int scrollx=0,int scrolly=0);
	void ScreenXY(int wx,int wz,int&px,int&py,int scrollx=0,int scrolly=0);
	int	WorldXY(int& wx,int& wz,int sx,int sy);	//returns icon radius
	int	WorldXY(Coords3D& w,int sx,int sy);	//returns icon radius
	BOOL IsIconVisible(ItemBasePtr id, int&px, int&py);
	void	DrawIcon(HDC hDC,int px,int py,FileNum f);
	void	DrawIcon(HDC hDC,int px,int py,BYTE* pData,BITMAPINFO* pInfo);
	void	DrawIconText(CDC* pDC,int px,int py,CString name);

	void ZoomToUID(UniqueID uid,double zoom);
	void LaunchFullPane(FullScreen* startscreen);
	void UpdateAll();
	void LaunchMap(bool firsttime);
	void OnChangeToTitle();
	CRScrlBar m_rVertScrollBar;
	CRScrlBar m_rHorzScrollBar;
	void SetHiLightInfo(int	pack, int wave = 0, int	group = 0,
						UniqueID	wp=UID_NULL,bool fullredraw=false);
//	void Quit();
//	CBitmap m_title;
/*	int GetOptionNum(CPoint point);
	enum	ViewState {
							MAP,
							TITLE
						};
	enum TextAlign {
						LEFT, // down the left of the page
						RIGHT, // down the right of the page
						CENTRE, // down the centre of the page
						SPACE  // first space in each word is central
					};
	enum ActionType {
						PAGE, // the pagenum to go to
						DIALOG, // the resource ID of the dialog
						PROCEDURE // a pointer to a static procedure
					};
	struct PageText
	{
		char* text; // the text to be displayed
		ActionType actiontype; // the type of action to do when clicked on
		int pagenum; // the pagenum to go to
		void (CMIGView::* procedure)(); // or the procedure to launch
	};
	struct Page
	{
		UINT artwork; // the identifier of the artwork
		int DialogX;
		int DialogY;
		BOOL DialogDouble;
		UINT DialogID; // the ID of the dialog to place
		int SmackerX;
		int SmackerY;
		BOOL SmackerDouble;
		UINT SmackerID; // some way of identifying the smacker
		int FontNum; // the font used to draw the text
		int TitleX;
		int TitleY;
		TextAlign textalign; // the alignment of the text
		PageText pagetext[8];	// Up to 8 lines of text per page (Feel free to increase)
								// Will automatically scale as required
		void (CMIGView::* init)(); // initialisation routine pointer
	};*/
	// will use the appropriate resolution depending on screensize
//	Page m_page640[15]; // 15 pages in the game (Change if you like)
//	Page m_page800[15]; // 15 pages in the game (Change if you like)
//	Page m_page1024[15]; // 15 pages in the game (Change if you like)
//	Page m_page1280[15]; // 15 pages in the game (Change if you like)
//	ViewState m_viewstate;

//	UINT m_currentartwork;
//	int m_optionNum;
//	CResizableDlgBar* m_pDialogBar;
//	RDialog* m_pTitleDialog;
//	int m_CurrentScaleOfDialog;

	CScaleBar* m_pScaleBar;
	int m_currentpage;
	RFullPanelDial* m_pfullpane;
	BOOL m_drawing;
	BOOL m_LButtonDown;
	int m_doIexist;
	void UpdateScrollbars();
	CPoint m_scrollpoint;
//	CBitmap m_chin;
//	CBitmap m_sea;
	int m_oldstarty;
	int m_oldstartx;
	int m_oldendy;
	int m_oldendx;
	int m_iconradius;
	BOOL m_isPaletteCreated;
	HDC m_hDC;
	fileblock* m_pfileblock;
	void UpdateBitmaps(CDC* pDC);
	void PlotRoutes(CDC* pDC,UniqueID onlythrough=UID_NULL);
	FileNum DrawIconTest(ItemBasePtr p, UniqueID i, bool hilight,UniqueIDField& redUIDs, FileNum* FL_Icon); 
protected:
	void InvalidateJapan();
	void PlotRoute(CDC* pDC, int pack, int wave, int group, bool drawhilight,UniqueID onlythrough=UID_NULL);
	void PlotFrontLine(CDC* pDC);
	void PlotLine(CDC* pDC, UniqueID thiswp,UniqueID nextwp, BOOL japanwp=FALSE);
//DeadCode RDH 19Apr99 	FileNum DrawIconTest(ItemBasePtr p, UniqueID i, bool hilight,UniqueIDField& redUIDs); 
//DeadCode RDH 19Apr99 	void DrawIcons(HDC hDC, CDC* pDC,UniqueIDField& redUIDs);
	void DrawIcons(HDC hDC, CDC* pDC,UniqueIDField& redUIDs, FileNum* FL_Icon);
	void PlotMainRoute(CDC* pDC,SupplyLine* SL, int red, int green, int blue);
	void PlotDebugInfo(CDC* pDC);
	void PlotAirfields(CDC* pDC);
	void PlotSupplyingRoutes(CDC* pDC);
	void DrawLine(CDC* pDC, int wx,int wz,int &px1, int &py1,int &px2,int &py2, 
		int scrollx,int scrolly, int red, int green, int blue, int width);
public:
	bool m_bridgesChecked;
	bool m_airstripsChecked;
//	bool m_bDontUpdateBitmaps;
	void UpdateBridges();
	void UpdateAirStrips();
	float m_zoom;
	float m_oldzoom;
	CPoint m_popupPoint;
	void Zoom(CPoint screenpoint,bool redrawscalebar=true);
//	CSize m_sizei;
	struct CSizeF
	{
		float cx,cy;
	}	m_size;
	CMapDlg					m_mapdlg;
	static const FileNum m_MapFiles[32][20];
	static CThumbnail* m_thumbnail;
	virtual ~CMIGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CMIGView)
	afx_msg void OnShowAirStrips();
	afx_msg void OnShowBridges();
	afx_msg void OnPopupZoomIn();
	afx_msg void OnPopupZoomOut();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnScrollHorzScrollbar(long nPos);
	afx_msg void OnScrollVertScrollbar(long nPos);
	afx_msg void OnMove(int x, int y);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg BYTE* OnGetFile(int filenum);
	afx_msg void OnReleaseLastFile();
	afx_msg CDC* OnGetOffScreenDC();
	MSG2_1(OnGetFile);
	MSG2_0v(OnReleaseLastFile);
	MSG2_0(OnGetOffScreenDC);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MIGView.cpp
inline CMIGDoc* CMIGView::GetDocument()
   { return (CMIGDoc*)m_pDocument; }
#endif
inline	RFullPanelDial*	GetFullPanel(CMIGView* view)
{	return	view->m_pfullpane;	}


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIGVIEW_H__DB0342A1_1B07_11D1_A1F0_444553540000__INCLUDED_)
