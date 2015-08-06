#if !defined(AFX_FOOTAGE_H__A5A382A1_4E12_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_FOOTAGE_H__A5A382A1_4E12_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Footage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFootage dialog

class CFootage : public RowanDialog
{
// Construction
public:
	CFootage(CWnd* pParent = NULL);   // standard constructor

	void	ParentDialClosed(RDialog*,int rv);

// Dialog Data
	//{{AFX_DATA(CFootage)
	enum { IDD = IDD_FOOTAGE };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDJ_TITLE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFootage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFootage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOOTAGE_H__A5A382A1_4E12_11D2_9FD5_D0EC00C10000__INCLUDED_)
