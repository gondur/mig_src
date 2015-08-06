#if !defined(AFX_FILING_H__11348502_787F_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_FILING_H__11348502_787F_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Filing.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFiling dialog

class CFiling : public RowanDialog
{
// Construction
public:
	CFiling(bool quitonok=false,CWnd* pParent = NULL);   // standard constructor
	static CString selectedfile;
	static	bool	LoadGame(CString);
	static	bool	SaveGame(CString);
	bool quitonok;
// Dialog Data
	//{{AFX_DATA(CFiling)
	enum { IDD = IDD_FILING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFiling)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnOK(); 

	// Generated message map functions
	//{{AFX_MSG(CFiling)
	afx_msg void OnCancelTitle();
	afx_msg void OnOKTitle();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILING_H__11348502_787F_11D2_9FD5_D0EC00C10000__INCLUDED_)
