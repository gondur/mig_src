#if !defined(AFX_DIRECTS1_H__6ECCAEA1_3DD2_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_DIRECTS1_H__6ECCAEA1_3DD2_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Directs1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirects1 dialog

class CDirects1 : public RowanDialog
{
// Construction
public:
	CDirects1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirects1)
	enum { IDD = IDD_DIRECTS_1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirects1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirects1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTS1_H__6ECCAEA1_3DD2_11D2_9FD5_D0EC00C10000__INCLUDED_)
