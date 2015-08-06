#if !defined(AFX_TASK_H__DAE85E21_CD59_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_TASK_H__DAE85E21_CD59_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Task.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTask dialog

class CTask : public RowanDialog
{
// Construction
public:
	CTask(int pack,int wave,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTask)
	enum { IDD = IDD_TASK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTask)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASK_H__DAE85E21_CD59_11D1_A5A3_0040052179B6__INCLUDED_)
