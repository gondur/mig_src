#if !defined(AFX_RJOYCFGC_H__1B499F78_C31E_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RJOYCFGC_H__1B499F78_C31E_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RJoyCfgC.h : Declaration of the CRJoyCfgCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl : See RJoyCfgC.cpp for implementation.

class CRJoyCfgCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRJoyCfgCtrl)

// Constructor
public:
	CRJoyCfgCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRJoyCfgCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPictureHolder    m_pic;
	HICON m_hPlaneIcon;
	long m_x;
	long m_y;
	~CRJoyCfgCtrl();

	BEGIN_OLEFACTORY(CRJoyCfgCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRJoyCfgCtrl)

	DECLARE_OLETYPELIB(CRJoyCfgCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRJoyCfgCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRJoyCfgCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRJoyCfgCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRJoyCfgCtrl)
	afx_msg LPPICTUREDISP GetControlPicture();
	afx_msg void SetControlPicture(LPPICTUREDISP newValue);
	afx_msg long GetX();
	afx_msg void SetX(long nNewValue);
	afx_msg long GetY();
	afx_msg void SetY(long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRJoyCfgCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CRJoyCfgCtrl)
	dispidControlPicture = 1L,
	dispidX = 2L,
	dispidY = 3L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RJOYCFGC_H__1B499F78_C31E_11D1_A1F0_444553540000__INCLUDED)
