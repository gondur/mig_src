#if !defined(AFX_RCOMBOC_H__737CB0D6_B42B_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RCOMBOC_H__737CB0D6_B42B_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RComboC.h : Declaration of the CRComboCtrl ActiveX Control class.
#include "dosdefs.h"
#include "ListBx.h"
class CRListBox;
#include "files.g"
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl : See RComboC.cpp for implementation.

class CRComboCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRComboCtrl)

// Constructor
public:
	CRComboCtrl();
	HICON m_hIcon;
	HICON m_hDisabledIcon;
	static BOOL m_bDrawing;
	static Bool m_bDrawOffscreen;
	BOOL m_bInit;
	Bool m_FirstSweep;
	long m_ListboxLength;
	long m_FontNum;
	long m_index;
	BOOL m_bCircularStyle;
	OLE_COLOR m_ShadowColor;
	long m_FileNum;
	long m_EndFileNum;
	CList<char*,char*> m_list;
	void DrawBitmap(FileNum filenum,CDC* pdc,int x,int y);
	void DrawBitmap(FileNum filenum,CDC* pdc,int x,int y,int maxx);
	void DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y);
	void DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y,int maxx);
bool	blocktextchanged;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRComboCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnTextChanged();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CRComboCtrl();

	BEGIN_OLEFACTORY(CRComboCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRComboCtrl)

	DECLARE_OLETYPELIB(CRComboCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRComboCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRComboCtrl)		// Type name and misc status


// Message maps
	//{{AFX_MSG(CRComboCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRComboCtrl)
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	afx_msg long GetListboxLength();
	afx_msg void SetListboxLength(long nNewValue);
	afx_msg BOOL GetCircularStyle();
	afx_msg void SetCircularStyle(BOOL bNewValue);
	afx_msg OLE_COLOR GetShadowColor();
	afx_msg void SetShadowColor(OLE_COLOR nNewValue);
	afx_msg long GetEndFileNum();
	afx_msg void SetEndFileNum(long nNewValue);
	afx_msg long GetFileNumMain();
	afx_msg void SetFileNumMain(long nNewValue);
	afx_msg void AddString(LPCTSTR text);
	afx_msg long GetListbox();
	afx_msg void SetIndex(long row);
	afx_msg long GetIndex();
	afx_msg void Clear();
	afx_msg void DeleteString(long index);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRComboCtrl)
	void FireTextChanged(LPCTSTR text)
		{FireEvent(eventidTextChanged,EVENT_PARAM(VTS_BSTR), text);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CRComboCtrl)
	dispidFontNum = 1L,
	dispidListboxLength = 2L,
	dispidCircularStyle = 3L,
	dispidShadowColor = 4L,
	dispidEndFileNum = 5L,
	dispidFileNumMain = 6L,
	dispidAddString = 7L,
	dispidGetListbox = 8L,
	dispidSetIndex = 9L,
	dispidGetIndex = 10L,
	dispidClear = 11L,
	dispidDeleteString = 12L,
	eventidTextChanged = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCOMBOC_H__737CB0D6_B42B_11D1_A1F0_444553540000__INCLUDED)
