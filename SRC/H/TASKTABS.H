#if !defined(AFX_TASKTABS_H__58AEFAA1_6358_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_TASKTABS_H__58AEFAA1_6358_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TaskTabs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTaskTabs dialog

class CTaskTabs : public RowanDialog
{
// Construction
public:
	CTaskTabs(CWnd* pParent = NULL);   // standard constructor

	void	SelectTab(int group);

// Dialog Data
	//{{AFX_DATA(CTaskTabs)
	enum { IDD = IDD_TASKTABS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaskTabs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTaskTabs)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKTABS_H__58AEFAA1_6358_11D2_9FD5_D0EC00C10000__INCLUDED_)
