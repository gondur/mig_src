#if !defined(AFX_AUTHOR_H__EF9ACC83_C4D6_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_AUTHOR_H__EF9ACC83_C4D6_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Author.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuthorise dialog

class CAuthorise : public RowanDialog
{
// Construction
public:
	CAuthorise(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAuthorise)
	enum { IDD = IDD_AUTHORISATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuthorise)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAuthorise)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTHOR_H__EF9ACC83_C4D6_11D1_A5A3_0040052179B6__INCLUDED_)
