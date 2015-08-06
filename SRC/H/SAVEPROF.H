//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#if !defined(AFX_SAVEPROF_H__6FFB8422_7AFB_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_SAVEPROF_H__6FFB8422_7AFB_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SaveProf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveProf dialog

class CSaveProf : public RowanDialog
{
// Construction
public:
	CSaveProf(int packnum,CWnd* pParent = NULL);   // standard constructor

	static CString selectedfile;
	void OnOK(); 

// Dialog Data
	//{{AFX_DATA(CSaveProf)
	enum { IDD = IDD_SAVEPROFILE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveProf)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveProf)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEPROF_H__6FFB8422_7AFB_11D2_9FD5_D0EC00C10000__INCLUDED_)
