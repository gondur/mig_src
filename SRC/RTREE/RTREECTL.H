#if !defined(AFX_RTREECTL_H__E8CBAEBB_85C1_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RTREECTL_H__E8CBAEBB_85C1_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RTreeCtl.h : Declaration of the CRTreeCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl : See RTreeCtl.cpp for implementation.

class CRTreeCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRTreeCtrl)

// Constructor
public:
	CRTreeCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTreeCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPictureHolder    m_pic;
	~CRTreeCtrl();

	BEGIN_OLEFACTORY(CRTreeCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRTreeCtrl)

	DECLARE_OLETYPELIB(CRTreeCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRTreeCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRTreeCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRTreeCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRTreeCtrl)
	afx_msg LPPICTUREDISP GetControlPicture();
	afx_msg void SetControlPicture(LPPICTUREDISP newValue);
	afx_msg long GetDepth();
	afx_msg void SetDepth(long nNewValue);
	afx_msg long GetBoxWidth();
	afx_msg void SetBoxWidth(long nNewValue);
	afx_msg long GetBoxHeight();
	afx_msg void SetBoxHeight(long nNewValue);
	afx_msg long GetGapWidth();
	afx_msg void SetGapWidth(long nNewValue);
	afx_msg long GetText(short index);
	afx_msg void Clear();
	afx_msg void SetText(LPCTSTR text, short index);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRTreeCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	long m_lBoxWidth;
	long m_lBoxHeight;
	long m_lDepth;
	long m_lGapWidth;
	char** m_list;

	enum {
	//{{AFX_DISP_ID(CRTreeCtrl)
	dispidControlPicture = 1L,
	dispidDepth = 2L,
	dispidBoxWidth = 3L,
	dispidBoxHeight = 4L,
	dispidGapWidth = 5L,
	dispidGetText = 6L,
	dispidClear = 7L,
	dispidSetText = 8L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTREECTL_H__E8CBAEBB_85C1_11D1_A1F0_444553540000__INCLUDED)
