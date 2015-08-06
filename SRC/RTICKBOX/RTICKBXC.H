#if !defined(AFX_RTICKBXC_H__840ED4B4_CF9B_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RTICKBXC_H__840ED4B4_CF9B_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RTickBxC.h : Declaration of the CRTickBoxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl : See RTickBxC.cpp for implementation.

class CRTickBoxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRTickBoxCtrl)

// Constructor
public:
	CRTickBoxCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTickBoxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnTextChanged();
	//}}AFX_VIRTUAL

// Implementation
protected:
	static BOOL m_bDrawing;
	int m_curPos;
	long m_FontNum;
//	CBitmap* partwork;
	CBitmap m_yes;
	CBitmap m_no;
	BOOL m_state;
//	BITMAP	artworkinfo;
	~CRTickBoxCtrl();

	BEGIN_OLEFACTORY(CRTickBoxCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRTickBoxCtrl)

	DECLARE_OLETYPELIB(CRTickBoxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRTickBoxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRTickBoxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRTickBoxCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRTickBoxCtrl)
	afx_msg BOOL GetState();
	afx_msg void SetState(BOOL bNewValue);
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRTickBoxCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CRTickBoxCtrl)
	dispidState = 1L,
	dispidFontNum = 2L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTICKBXC_H__840ED4B4_CF9B_11D1_A1F0_0080C8582DE4__INCLUDED)
