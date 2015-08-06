#if !defined(AFX_RDEMPTYD_H__505728C2_2797_11D2_83A5_00004760763D__INCLUDED_)
#define AFX_RDEMPTYD_H__505728C2_2797_11D2_83A5_00004760763D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RDEmptyD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RDEmptyD dialog

class RDEmptyD : public RowanDialog
{
// Construction
public:
	RDEmptyD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RDEmptyD)
	enum { IDD = IDD_EMPTYDIAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RDEmptyD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RDEmptyD)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RDEMPTYD_H__505728C2_2797_11D2_83A5_00004760763D__INCLUDED_)
