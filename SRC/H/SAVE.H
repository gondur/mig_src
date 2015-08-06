#if !defined(AFX_SAVE_H__11348501_787F_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_SAVE_H__11348501_787F_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Save.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSave dialog

class CSave : public RowanDialog
{
// Construction
public:
	CSave(CWnd* pParent = NULL);   // standard constructor

	CString	filename;
	int currrow;


// Dialog Data
	//{{AFX_DATA(CSave)
	enum { IDD = IDD_SAVE };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_FILEOK;
	CRListBox	m_IDC_RLISTBOXFILE;
	CREdit	m_IDC_SAVENAME;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
 	void PrintFileName();

	// Generated message map functions
	//{{AFX_MSG(CSave)
	afx_msg void OnClickedSave();
	afx_msg void OnTextChangedSavename(LPCTSTR text);
	afx_msg void OnSelectRlistboxfile(long row, long column);
	virtual BOOL OnInitDialog();
	afx_msg void OnReturnPressedSavename(LPCTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVE_H__11348501_787F_11D2_9FD5_D0EC00C10000__INCLUDED_)
