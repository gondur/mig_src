#if !defined(AFX_RSPLTBARCTL_H__0542BF53_88DF_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RSPLTBARCTL_H__0542BF53_88DF_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RSpltBarCtl.h : Declaration of the CRSpltBarCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl : See RSpltBarCtl.cpp for implementation.

class CRSpltBarCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRSpltBarCtrl)

// Constructor
public:
	CRSpltBarCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSpltBarCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CRSpltBarCtrl();

	BEGIN_OLEFACTORY(CRSpltBarCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRSpltBarCtrl)

	DECLARE_OLETYPELIB(CRSpltBarCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRSpltBarCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRSpltBarCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRSpltBarCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRSpltBarCtrl)
	afx_msg long GetTopLeftWindow();
	afx_msg void SetTopLeftWindow(long nNewValue);
	afx_msg long GetBottomRightWindow();
	afx_msg void SetBottomRightWindow(long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRSpltBarCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	CWnd* m_pTopLeftWindow;
	CWnd* m_pBottomRightWindow;
	BOOL m_LButtonDown;
	CPoint m_point;
	enum {
	//{{AFX_DISP_ID(CRSpltBarCtrl)
	dispidTopLeftWindow = 1L,
	dispidBottomRightWindow = 2L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSPLTBARCTL_H__0542BF53_88DF_11D1_A1F0_444553540000__INCLUDED)
