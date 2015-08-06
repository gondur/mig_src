#if !defined(AFX_SQDNLB_H__025E4541_2F99_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_SQDNLB_H__025E4541_2F99_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SqdnLB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSqdnListBack dialog

class CSqdnListBack : public RowanDialog
{
// Construction
public:
	CSqdnListBack(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSqdnListBack)
	enum { IDD = IDD_SQDNLIST_BACK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSqdnListBack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSqdnListBack)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQDNLB_H__025E4541_2F99_11D2_9FD5_D0EC00C10000__INCLUDED_)
