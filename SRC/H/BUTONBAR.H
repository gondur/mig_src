#if !defined(AFX_BUTONBAR_H__CCAF2862_CEC7_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_BUTONBAR_H__CCAF2862_CEC7_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ButonBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonBar window

class CButtonBar : public CToolBar
{
// Construction
public:
	CButtonBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CButtonBar();
	CBitmap m_artwork;
	BITMAP m_artworkinfo;

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTONBAR_H__CCAF2862_CEC7_11D1_A1F0_0080C8582DE4__INCLUDED_)
