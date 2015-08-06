#if !defined(AFX_PILOTS_H__64D4AFA3_CE2F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_PILOTS_H__64D4AFA3_CE2F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Pilots.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPilots dialog

class CPilots : public RowanDialog
{
// Construction
public:
	CPilots(CWnd* pParent = NULL);   // standard constructor
	void	ParentDialClosed(RDialog*,int rv);

// Dialog Data
	//{{AFX_DATA(CPilots)
	enum { IDD = IDD_PILOTS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPilots)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPilots)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PILOTS_H__64D4AFA3_CE2F_11D1_A5A3_0040052179B6__INCLUDED_)
