#if !defined(AFX_MAINFRM_H__DB03429D_1B07_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__DB03429D_1B07_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RDlgBar.h"
#include "SysBox.h"	// Added by ClassView
#include "ButonBar.h"
#include <afxtempl.h>
//#include "rtoolbar.h"
#include "scalebar.h"
#include "maintbar.h"
#include "mapfltrs.h"
#include "msctlbr.h"
#include "dbrftlbr.h"

class CMIGView;
class CMIGDoc;


class CMainFrame : public CFrameWnd
{
//protected: // create from serialization only

// Attributes
public:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	bool	havedrawn,havesafe;
	bool	bAppMinimized;
	int		disablehelp;	//1=disabletabs 2=disablepanels
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void	InitialiseSafe();

	void ShowToolbars(bool firsttime);
	void HideToolbars();
	BOOL m_bHideToolbars;
	Bool m_oldindebrief;
	typedef CList<CRToolBar*,CRToolBar*> ToolBarList;
	ToolBarList m_left;
	ToolBarList m_top;
	ToolBarList m_right;
	ToolBarList m_bottom;
	CRect m_borderRect;
#ifndef	MIG_DEMO_VER
	CMapFilters m_toolbar1;
	CMainToolbar m_toolbar2;
	CMiscToolbar m_toolbar3;
	CScaleBar m_toolbar4;
	TitleBar	m_titlebar;
	CDebriefToolbar m_toolbar5;
	CSystemBox* m_wndSystemBox;
#endif
	int m_doIExist;
//DEADCODE DAW 07/05/99 	CResizableDlgBar m_wndDialogBar;
//DeadCode RDH 11Jul99 	CSystemBox* m_wndSystemBox;
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	void	Initialise();
//	CStatusBar  m_wndStatusBar;
//	CButtonBar    m_wndToolBar;

// Generated message map functions
protected:
public:
	void UpdateToolbars();
	void	RePositionLayout(int dx,int dy);
	void	RePositionLayout(int dx,int dy,ToolBarList* toollist);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBye();
	afx_msg void OnGoSmall();
	afx_msg void OnGoBig();
	afx_msg void OnGoNormal();
	afx_msg void OnPaint();
	afx_msg void OnHelp();
	afx_msg void OnHelpFinder();
	afx_msg void OnContextHelp();
	afx_msg void OnSize(UINT,int,int);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	//}}AFX_MSG
	afx_msg LRESULT OnCommandHelp(WPARAM, LPARAM lParam);
	MSG2_2(OnCommandHelp);
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
#ifndef	MIG_DEMO_VER
#ifdef	MAINTBAR_INCLUDED
inline CMainToolbar&	MainToolBar()
{
	CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
	return pmainwnd->m_toolbar2;
}
inline CDebriefToolbar&	DebriefToolBar()
{
	CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
	return pmainwnd->m_toolbar5;
}
inline	CMiscToolbar& MiscToolBar()
{
	CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
	return pmainwnd->m_toolbar3;
}
#endif
#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__DB03429D_1B07_11D1_A1F0_444553540000__INCLUDED_)


