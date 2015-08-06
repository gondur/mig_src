#if !defined(AFX_REDITCTL_H__499E2BF3_AC32_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_REDITCTL_H__499E2BF3_AC32_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// REditCtl.h : Declaration of the CREditCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CREditCtrl : See REditCtl.cpp for implementation.

class CREditCtrl : public COleControl
{
	DECLARE_DYNCREATE(CREditCtrl)

// Constructor
public:
	CREditCtrl();
	int m_curPoint;
	int m_curPos;
	int m_scrollPoint;
	long m_FontNum;
	UINT m_timerID;
	BOOL m_bShowCursor;
	static BOOL m_bDrawing;
	Bool m_FirstSweep;
	BOOL m_bDisabled;
//	CBitmap* partwork;
//	BITMAP	artworkinfo;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREditCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnTextChanged();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CREditCtrl();

	BEGIN_OLEFACTORY(CREditCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CREditCtrl)

	DECLARE_OLETYPELIB(CREditCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CREditCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CREditCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CREditCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CREditCtrl)
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CREditCtrl)
	void FireReturnPressed(LPCTSTR text)
		{FireEvent(eventidReturnPressed,EVENT_PARAM(VTS_BSTR), text);}
	void FireTextChanged(LPCTSTR text)
		{FireEvent(eventidTextChanged,EVENT_PARAM(VTS_I4), text);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CREditCtrl)
	dispidFontNum = 1L,
	eventidTextChanged = 2L,
	eventidReturnPressed = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDITCTL_H__499E2BF3_AC32_11D1_A1F0_444553540000__INCLUDED)
