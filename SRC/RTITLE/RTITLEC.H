#if !defined(AFX_RTITLECTL_H__008F23F6_9243_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RTITLECTL_H__008F23F6_9243_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RTitleCtl.h : Declaration of the CRTitleCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CRTitleCtrl : See RTitleCtl.cpp for implementation.

class CRTitleCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRTitleCtrl)

// Constructor
public:
	CRTitleCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTitleCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CRTitleCtrl();

	BEGIN_OLEFACTORY(CRTitleCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRTitleCtrl)

	DECLARE_OLETYPELIB(CRTitleCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRTitleCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRTitleCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRTitleCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRTitleCtrl)
	afx_msg long SelStockFont(long pDC);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRTitleCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CRTitleCtrl)
	dispidSelStockFont = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTITLECTL_H__008F23F6_9243_11D1_A1F0_444553540000__INCLUDED)
