#if !defined(AFX_RSTATICC_H__C42BAC4A_CA3C_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RSTATICC_H__C42BAC4A_CA3C_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RStaticC.h : Declaration of the CRStaticCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl : See RStaticC.cpp for implementation.
#include "dosdefs.h"
#include "files.g"

class CRStaticCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRStaticCtrl)

// Constructor
public:
	CRStaticCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRStaticCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnTextChanged();
	//}}AFX_VIRTUAL

// Implementation
protected:
	static BOOL m_bDrawing;
//	int m_curPos;
	long m_FontNum;
	CString m_string;
	long m_ResourceNumber;
	OLE_COLOR m_ShadowColor;
	FileNum m_PictureFileNum;
	void DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x=0, int y=0);
	BOOL m_bCentral;
	Bool m_FirstSweep;
	bool	gotparentwnd;	
	void	GetParentWndInfo();

	~CRStaticCtrl();

	BEGIN_OLEFACTORY(CRStaticCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRStaticCtrl)

	DECLARE_OLETYPELIB(CRStaticCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRStaticCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRStaticCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRStaticCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRStaticCtrl)
	BOOL m_updateCaption;
	afx_msg void OnUpdateCaptionChanged();
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	afx_msg BSTR GetString();
	afx_msg void SetString(LPCTSTR lpszNewValue);
	afx_msg long GetResourceNumber();
	afx_msg void SetResourceNumber(long nNewValue);
	afx_msg long GetPictureFileNum();
	afx_msg void SetPictureFileNum(long nNewValue);
	afx_msg BOOL GetCentral();
	afx_msg void SetCentral(BOOL bNewValue);
	afx_msg OLE_COLOR GetShadowColor();
	afx_msg void SetShadowColor(OLE_COLOR nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRStaticCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CRStaticCtrl)
	dispidUpdateCaption = 1L,
	dispidFontNum = 2L,
	dispidString = 3L,
	dispidResourceNumber = 4L,
	dispidPictureFileNum = 5L,
	dispidCentral = 6L,
	dispidShadowColor = 7L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSTATICC_H__C42BAC4A_CA3C_11D1_A1F0_444553540000__INCLUDED)
