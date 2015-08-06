
#if !defined(AFX_RRADIOC_H__7EBC74F1_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RRADIOC_H__7EBC74F1_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RRadioC.h : Declaration of the CRRadioCtrl ActiveX Control class.
#include <afxtempl.h>
#include "dosdefs.h"
#include "files.g"

/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl : See RRadioC.cpp for implementation.

class CRRadioCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRRadioCtrl)

// Constructor
public:
	HICON m_hButtonUp;
	HICON m_hButtonDown;
	Bool m_FirstSweep;
	long m_FontNum;
	long m_Cols;
	CList<char*,char*> m_list;
	static BOOL m_bDrawing;
	long m_CurSel;
	long m_ColumnWidth;
	int m_bitmapheight ;
	CRRadioCtrl();
	void DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRRadioCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CRRadioCtrl();

	BEGIN_OLEFACTORY(CRRadioCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRRadioCtrl)

	DECLARE_OLETYPELIB(CRRadioCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRRadioCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRRadioCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRRadioCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRRadioCtrl)
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	afx_msg long GetCols();
	afx_msg void SetCols(long nNewValue);
	afx_msg long GetCurrentSelection();
	afx_msg void SetCurrentSelection(long nNewValue);
	afx_msg long GetColumnWidth();
	afx_msg void SetColumnWidth(long nNewValue);
	afx_msg void AddButton(LPCTSTR text);
	afx_msg void Clear();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRRadioCtrl)
	void FireSelected(long ButtonNum)
		{FireEvent(eventidSelected,EVENT_PARAM(VTS_I4), ButtonNum);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CRRadioCtrl)
	dispidFontNum = 1L,
	dispidCols = 2L,
	dispidCurrentSelection = 3L,
	dispidColumnWidth = 4L,
	dispidAddButton = 5L,
	dispidClear = 6L,
	eventidSelected = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RRADIOC_H__7EBC74F1_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED)
