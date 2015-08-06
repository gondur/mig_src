#if !defined(AFX_RTABSCTL_H__4A1E1993_8B31_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RTABSCTL_H__4A1E1993_8B31_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
// RTabsCtl.h : Declaration of the CRTabsCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl : See RTabsCtl.cpp for implementation.

class CRTabsCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRTabsCtrl)

// Constructor
public:
	CRTabsCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTabsCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	long m_FontNum;
	~CRTabsCtrl();

	BEGIN_OLEFACTORY(CRTabsCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRTabsCtrl)

	DECLARE_OLETYPELIB(CRTabsCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRTabsCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRTabsCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRTabsCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRTabsCtrl)
	afx_msg long GetFirstTab();
	afx_msg void SetFirstTab(long nNewValue);
	afx_msg BOOL GetHorzAlign();
	afx_msg void SetHorzAlign(BOOL bNewValue);
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	afx_msg void AddTab(LPCTSTR text, long pWnd);
	afx_msg void Clear();
	afx_msg long CalculateHeight(long totalWidth);
	afx_msg long CalcWidestWord();
	afx_msg long SelectTab(long tab);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	afx_msg	long SelectTabInternal(long tab);
	CWnd* SelectTabBody(long tab);

// Event maps
	//{{AFX_EVENT(CRTabsCtrl)
	void FireSelectTab(long tab)
		{FireEvent(eventidSelectTab,EVENT_PARAM(VTS_I4), tab);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	void DrawRow(float seperation,int start,int finish,CDC* pDC,int row,int rowWidth,BOOL lastrow);
	BOOL m_bHorzAlign;
	CWnd* m_firstTab;
	int m_iCurrentSelection;
	CBitmap m_TabUp;
	CBitmap m_TabDown;
	CDC m_TabUpDC;
	CDC m_TabDownDC;
	int m_TabUpWidth,m_TabDownWidth,m_TabUpHeight,m_TabDownHeight;
	BOOL m_bInit;
	HICON m_hLowTabIcon;
	HICON m_hHighTabIcon;
	HICON m_hLowContinueIcon;
	HICON m_hHighContinueIcon;
	CList<char*,char*> m_textList;
	CList<CWnd*,CWnd*> m_windowList;
	CList<CRect,CRect> m_rectList;
	CList<int,int> m_tabList;
	enum {
	//{{AFX_DISP_ID(CRTabsCtrl)
	dispidFirstTab = 1L,
	dispidHorzAlign = 2L,
	dispidFontNum = 3L,
	dispidAddTab = 4L,
	dispidClear = 5L,
	dispidCalculateHeight = 6L,
	dispidCalcWidestWord = 7L,
	dispidSelectTab = 8L,
	eventidSelectTab = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTABSCTL_H__4A1E1993_8B31_11D1_A1F0_444553540000__INCLUDED)
