#if !defined(AFX_SMKDLG_H__A5A382A3_4E12_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_SMKDLG_H__A5A382A3_4E12_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SmkDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSmackerDialog dialog

class CSmackerDialog : public RowanDialog
{
// Construction
public:
	CSmackerDialog(FileNum fil,CWnd* pParent = NULL);   // standard constructor
	UINT m_timerID;

	FileNum  file;
// Dialog Data
	//{{AFX_DATA(CSmackerDialog)
	enum { IDD = IDD_SMACKER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmackerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	FileNum FindSmacker();

	// Generated message map functions
	//{{AFX_MSG(CSmackerDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMKDLG_H__A5A382A3_4E12_11D2_9FD5_D0EC00C10000__INCLUDED_)
