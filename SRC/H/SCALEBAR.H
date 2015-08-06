#if !defined(AFX_SCALEBAR_H__E28110A1_DAB5_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_SCALEBAR_H__E28110A1_DAB5_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScaleBar.h : header file
//
#include "RToolBar.h"

/////////////////////////////////////////////////////////////////////////////
// CScaleBar dialog

class CScaleBar : public CRToolBar
{
// Construction
public:
	CScaleBar(CWnd* pParent = NULL);   // standard constructor
	CPoint m_oldPoint;
	float m_oldzoom;
	BOOL m_RButtonDown;

// Dialog Data
	//{{AFX_DATA(CScaleBar)
	enum { IDD = IDD_SCALE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScaleBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScaleBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCALEBAR_H__E28110A1_DAB5_11D1_A1F0_0080C8582DE4__INCLUDED_)
