#if !defined(AFX_RSCRLBARCTL_H__505AEE53_6A66_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RSCRLBARCTL_H__505AEE53_6A66_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RScrlBarCtl.h : Declaration of the CRScrlBarCtrl ActiveX Control class.
#include "dosdefs.h"
#include "files.g"

/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl : See RScrlBarCtl.cpp for implementation.

class CRScrlBarCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRScrlBarCtrl)

// Constructor
public:
	static BOOL m_bDrawing;
	CRScrlBarCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRScrlBarCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CRScrlBarCtrl();

	BEGIN_OLEFACTORY(CRScrlBarCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRScrlBarCtrl)

	DECLARE_OLETYPELIB(CRScrlBarCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRScrlBarCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRScrlBarCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRScrlBarCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRScrlBarCtrl)
	afx_msg long GetMinValue();
	afx_msg void SetMinValue(long nNewValue);
	afx_msg long GetMaxValue();
	afx_msg void SetMaxValue(long nNewValue);
	afx_msg long GetStepSize();
	afx_msg void SetStepSize(long nNewValue);
	afx_msg BOOL GetHorzAlign();
	afx_msg void SetHorzAlign(BOOL bNewValue);
	afx_msg long GetParentPointer();
	afx_msg void SetParentPointer(long nNewValue);
	afx_msg long GetPageSize();
	afx_msg void SetPageSize(long nNewValue);
	afx_msg long GetScrollPos();
	afx_msg void SetScrollPos(long nNewValue);
	afx_msg BOOL GetUseMessagesInsteadOfEvents();
	afx_msg void SetUseMessagesInsteadOfEvents(BOOL bNewValue);
	afx_msg long GetFileNumOffset();
	afx_msg void SetFileNumOffset(long nNewValue);
	afx_msg void Move(long left, long top, long right, long bottom);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRScrlBarCtrl)
	void FireScroll(long nPos)
		{FireEvent(eventidScroll,EVENT_PARAM(VTS_I4), nPos);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	void DoFireScroll();
	int m_button;
	BOOL m_bHorzAlign;
	long m_FileNumOffset;
	long m_lStepSize;
	long m_lMaxValue;
	long m_lMinValue;
	long m_iScrollPos;
	int m_timerID;
	CPoint m_point;
	long m_offset;
	long m_pagesize;
	CWnd* m_parent;
	BOOL m_bUseMessagesInsteadOfEvents;
	void DrawBitmap(FileNum filenum,CDC* pdc,int x,int y);
	void DrawTransparentBitmap(FileNum filenum,CDC * pDC,int x, int y);
	void DrawTiledBitmap(FileNum filenum,CDC* pdc,int x,int y,int length);
	void MergeDCs(CDC* sourceDC, CDC* destDC);

	enum {
	//{{AFX_DISP_ID(CRScrlBarCtrl)
	dispidMinValue = 1L,
	dispidMaxValue = 2L,
	dispidStepSize = 3L,
	dispidHorzAlign = 4L,
	dispidParentPointer = 5L,
	dispidPageSize = 6L,
	dispidScrollPos = 7L,
	dispidUseMessagesInsteadOfEvents = 8L,
	dispidFileNumOffset = 9L,
	dispidMove = 10L,
	eventidScroll = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSCRLBARCTL_H__505AEE53_6A66_11D1_A1F0_444553540000__INCLUDED)
