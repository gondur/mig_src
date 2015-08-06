//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_THUMBNAIL_H__35FD12E1_34C3_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_THUMBNAIL_H__35FD12E1_34C3_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Thumbnail.h : header file
//
#include "files.g"

/////////////////////////////////////////////////////////////////////////////
// CThumbnail dialog

class CThumbnail : public RowanDialog
{
// Construction
public:
	void UpdateView();
	void InvalidateMapOnly();
	void DrawScaledBitmap(CDC* pDC, FileNum filenum, int left, int top, int width, int height);
	CSize m_boxSize;
	CPoint m_point;
	BOOL m_LButtonDown;
	FileNum filenum;
	CThumbnail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CThumbnail)
	enum { IDD = IDD_THUMBNAIL };
	CRButton	m_IDJ_TITLE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbnail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThumbnail)
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBNAIL_H__35FD12E1_34C3_11D1_A1F0_444553540000__INCLUDED_)
