#if !defined(AFX_OVERVIEW_H__C75E68C2_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_OVERVIEW_H__C75E68C2_CF0E_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Overview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COverview dialog

class COverview : public RowanDialog
{
// Construction
public:
	COverview(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COverview)
	enum { IDD = IDD_OVERVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COverview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COverview)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OVERVIEW_H__C75E68C2_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
