#if !defined(AFX_REDTBTCTL_H__461A1FF0_B81B_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_REDTBTCTL_H__461A1FF0_B81B_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// REdtBtCtl.h : Declaration of the CREdtBtCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl : See REdtBtCtl.cpp for implementation.

#include "globdefs.h"
#include "files.g"

class CREdtBtCtrl : public COleControl
{
	DECLARE_DYNCREATE(CREdtBtCtrl)

// Constructor
public:
	static BOOL m_bDrawing;
	static Bool m_bDrawOffscreen;
	CREdtBtCtrl();
	Bool m_FirstSweep ;
	BOOL m_Init;
	BOOL m_bDrawBitmap;
	long m_FontNum;
	CPoint m_point;
	BOOL m_LButtonDown;
	BOOL m_bDragging;
	long m_DragAndDropID;
	BOOL m_bCanAcceptDrop;
	FileNum m_TransparentPicture ;									//RDH 23Dec98
	void DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREdtBtCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnTextChanged();
	//}}AFX_VIRTUAL

// Implementation
	CString		captiontext;
protected:
	~CREdtBtCtrl();

	BEGIN_OLEFACTORY(CREdtBtCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CREdtBtCtrl)

	DECLARE_OLETYPELIB(CREdtBtCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CREdtBtCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CREdtBtCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CREdtBtCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnCanAcceptDrop(long dropID);
	afx_msg void OnDroppedOn(long dropID);
	MSG2_1(OnCanAcceptDrop);
	MSG2_1v(OnDroppedOn);

// Dispatch maps
	//{{AFX_DISPATCH(CREdtBtCtrl)
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	afx_msg long GetDragAndDropID();
	afx_msg void SetDragAndDropID(long nNewValue);
	afx_msg void SetPictureFileNum(long picture);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CREdtBtCtrl)
	void FireClicked()
		{FireEvent(eventidClicked,EVENT_PARAM(VTS_NONE));}
	void FireCanAcceptDrop(long sourcedropID, BOOL FAR* pReply)
		{FireEvent(eventidCanAcceptDrop,EVENT_PARAM(VTS_I4  VTS_PBOOL), sourcedropID, pReply);}
	void FireDroppedOn(long sourcedropID)
		{FireEvent(eventidDroppedOn,EVENT_PARAM(VTS_I4), sourcedropID);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CREdtBtCtrl)
	dispidFontNum = 1L,
	dispidDragAndDropID = 2L,
	dispidSetPictureFileNum = 3L,
	eventidClicked = 1L,
	eventidCanAcceptDrop = 2L,
	eventidDroppedOn = 3L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDTBTCTL_H__461A1FF0_B81B_11D1_A1F0_444553540000__INCLUDED)
