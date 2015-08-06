#if !defined(AFX_RBUTTONCTL_H__78918653_A917_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RBUTTONCTL_H__78918653_A917_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RButtonCtl.h : Declaration of the CRButtonCtrl ActiveX Control class.
#include "files.g"
#include "hintbox.h"

/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl : See RButtonCtl.cpp for implementation.

class CRButtonCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRButtonCtrl)

// Constructor
public:
	CRButtonCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRButtonCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnTextChanged();
	//}}AFX_VIRTUAL

// Implementation
protected:
//	CPictureHolder    m_picNormal;
//	CPictureHolder    m_picPressed;
	Bool m_FirstSweep;
	BOOL m_bInit;
	static BOOL m_bDrawing;
	BOOL m_bPressed;
	BOOL m_bDisabled;
	long m_NormalFileNum;
	long m_PressedFileNum;
	long m_TransparentInnerFileNum;
	CString m_NormalFileNumString;
	CString m_PressedFileNumString;
	CString m_string;
	long m_ResourceNumber;
	CString m_hintString;
	CString m_hintStringID;
	long m_hintResourceNumber;
	OLE_COLOR m_ShadowColor;
	BOOL m_bShowShadow;
	HICON m_closeUpIcon;
	HICON m_closeDownIcon;
	BOOL m_bCloseButton;
	BOOL m_bClosePressed;
	HICON m_tickUpIcon;
	HICON m_tickDownIcon;
	BOOL m_bTickButton;
	BOOL m_bTickPressed;
	HICON m_helpUpIcon;
	HICON m_helpDownIcon;
	BOOL m_bHelpButton;
	BOOL m_bHelpPressed;
	long m_FontNum;
	BOOL m_LButtonDown;
	BOOL m_bMovesParent;
	BOOL m_BitMapWithTransparencies ;
	CPoint m_point;
	bool	gotparentwnd;
	void	GetParentWndInfo();
	~CRButtonCtrl();

	BEGIN_OLEFACTORY(CRButtonCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRButtonCtrl)

	DECLARE_OLETYPELIB(CRButtonCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRButtonCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRButtonCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRButtonCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRButtonCtrl)
	BOOL m_updateCaption;
	afx_msg void OnUpdateCaptionChanged();
	afx_msg BOOL GetMovesParent();
	afx_msg void SetMovesParent(BOOL bNewValue);
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	afx_msg BOOL GetCloseButton();
	afx_msg void SetCloseButton(BOOL bNewValue);
	afx_msg BOOL GetTickButton();
	afx_msg void SetTickButton(BOOL bNewValue);
	afx_msg BOOL GetShowShadow();
	afx_msg void SetShowShadow(BOOL bNewValue);
	afx_msg OLE_COLOR GetShadowColor();
	afx_msg void SetShadowColor(OLE_COLOR nNewValue);
	afx_msg BSTR GetString();
	afx_msg void SetString(LPCTSTR lpszNewValue);
	afx_msg long GetResourceNumber();
	afx_msg void SetResourceNumber(long nNewValue);
	afx_msg long GetNormalFileNum();
	afx_msg void SetNormalFileNum(long nNewValue);
	afx_msg long GetPressedFileNum();
	afx_msg void SetPressedFileNum(long nNewValue);
	afx_msg BSTR GetNormalFileNumString();
	afx_msg void SetNormalFileNumString(LPCTSTR lpszNewValue);
	afx_msg BSTR GetPressedFileNumString();
	afx_msg void SetPressedFileNumString(LPCTSTR lpszNewValue);
	afx_msg BOOL GetPressed();
	afx_msg void SetPressed(BOOL bNewValue);
	afx_msg BOOL GetDisabled();
	afx_msg void SetDisabled(BOOL bNewValue);
	afx_msg BSTR GetHintStringID();
	afx_msg void SetHintStringID(LPCTSTR lpszNewValue);
	afx_msg long GetHintResourceNumber();
	afx_msg void SetHintResourceNumber(long nNewValue);
	afx_msg BOOL GetTransparency();
	afx_msg void SetTransparency(BOOL bNewValue);
	afx_msg long GetTransparentBitMap();
	afx_msg void SetTransparentBitMap(long nNewValue);
	afx_msg BOOL GetHelpButton();
	afx_msg void SetHelpButton(BOOL bNewValue);
	afx_msg BSTR GetHintString();
	afx_msg void SetHintString(LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRButtonCtrl)
	void FireClicked()
		{FireEvent(eventidClicked,EVENT_PARAM(VTS_NONE));}
	void FireCancel()
		{FireEvent(eventidCancel,EVENT_PARAM(VTS_NONE));}
	void FireOK()
		{FireEvent(eventidOK,EVENT_PARAM(VTS_NONE));}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	void DrawBitmap(FileNum filenum,CDC* pdc);
	void DrawBitmapWithTransparencies(FileNum filenum,CDC* pdc);
	void DrawTransparentBitmap(CDC* pDC, FileNum filenum);
	enum {
	//{{AFX_DISP_ID(CRButtonCtrl)
	dispidMovesParent = 2L,
	dispidFontNum = 3L,
	dispidCloseButton = 4L,
	dispidTickButton = 5L,
	dispidShowShadow = 6L,
	dispidShadowColor = 7L,
	dispidString = 8L,
	dispidResourceNumber = 9L,
	dispidNormalFileNum = 10L,
	dispidPressedFileNum = 11L,
	dispidNormalFileNumString = 12L,
	dispidPressedFileNumString = 13L,
	dispidUpdateCaption = 1L,
	dispidPressed = 14L,
	dispidDisabled = 15L,
	dispidTransparency = 18L,
	dispidTransparentFileNum = 19L,
	dispidHelpButton = 20L,
	dispidHintString = 21L,
	eventidClicked = 1L,
	eventidCancel = 2L,
	eventidOK = 3L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RBUTTONCTL_H__78918653_A917_11D1_A1F0_444553540000__INCLUDED)
