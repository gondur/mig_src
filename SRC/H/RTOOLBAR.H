#if !defined(AFX_RTOOLBAR_H__95882EC2_D9F5_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RTOOLBAR_H__95882EC2_D9F5_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CRToolBar.h : header file
//
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CRToolBar dialog
class CMainFrame;
class CMIGView;

class CRToolBar : public CDialog
{
	DECLARE_DYNAMIC(CRToolBar);
// Construction
public:
	void Float(); // floats a toolbar
	void Replace(CRToolBar* newtoolbar); // replaces this toolbar with newtoolbar
	DialogLinks	dialoglinks;
	int		LogChild(RDialog*);	//new system for managing intersheet comms
	bool	LogChild(int,RDialog*);	//as Dallas never implemented one!
	int		LoggedChild();
	RDialog*	LoggedChild(int);
	bool	CloseLoggedChild(int);	  //true means still open!!!
	void	CloseLoggedChildren(RDialog* skipthis=NULL);
	void	RefreshChild(int rv);
	virtual void ChildDialClosed(int dialnum,RDialog*,int rv);
	virtual void RefreshData(int childnum);
	void	MakeChildrenVisible(bool);

	void Init();
	int GetDockSide(CPoint point);
	void Init(CMainFrame* parent,int minlength,int length,int width,UINT nDockBarID = AFX_IDW_DOCKBAR_TOP,int priority=0,UINT dockablesides=CBRS_ALIGN_ANY);
	// the length is always the longer of the two
	// keep the width the same in all of the toolbars
	// a priority of 0 means the toolbar will not resize
	virtual void SetHorzAlign(BOOL bHorzAlign);
	CRToolBar(CWnd* pParent = NULL);   // standard constructor
	~CRToolBar()	{DialExitFix();}
	void	DialExitFix(int rv=0);
	BOOL m_bHorzAlign;
	BOOL m_init;
	UINT m_dockablesides;
	int m_priority;
	int m_align;
	int m_length;
	int m_currentlength;
	int m_minlength;
	int m_width;
	int m_row; // what row we are on if docked
	CMainFrame* m_pFrame;
	CMIGView* m_pView;
	int m_LButtonDown;	//0=not down;1=dragging ctool;2=dragging app
	CPoint m_lastdown;
	fileblock* m_pfileblock;
	CList<CRToolBar*,CRToolBar*>* m_pList;
	int m_index;

	
// Dialog Data
	//{{AFX_DATA(CRToolBar)
	enum { IDD = IDD_EMPTYTOOLBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	void	DDX_Control(CDataExchange* pDX,int	dialid,CWnd&	m_dial);
	BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRToolBar)
	public:
	virtual BOOL DestroyWindow();
	virtual int DoModal();
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void OnFinalRelease();
	virtual void OnSetFont(CFont* pFont);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void Serialize(CArchive& ar);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRToolBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCancelMode();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
	afx_msg int OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG
	afx_msg LRESULT OnCommandHelp(WPARAM, LPARAM lParam);
	afx_msg BYTE* OnGetFile(int filenum);
	afx_msg void OnReleaseLastFile();
	afx_msg CHintBox* OnGetHintBox();
	afx_msg void OnPlaySound(int filenum);
	afx_msg int OnGetString(int resourceID,char* workbuffer);
	MSG2(OnGetString)	{return OnGetString(a,(char*)b);}
	MSG2_2(OnCommandHelp);
	MSG2_1(OnGetFile);
	MSG2_0v(OnReleaseLastFile);
	MSG2_0(OnGetHintBox);
	MSG2_1v(OnPlaySound);
	DECLARE_MESSAGE_MAP()
private:
	CRToolBar* FindToolBar(CPoint point); // this is a slightly dodgy function so dont call it
											// unless you KNOW a docked toolbar is inside point
};
#endif
