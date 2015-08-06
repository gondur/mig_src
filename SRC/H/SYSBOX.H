#if !defined(AFX_SYSTEMBOX_H__72355DC1_3997_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_SYSTEMBOX_H__72355DC1_3997_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SystemBox.h : header file
//
class CMainFrame;
/////////////////////////////////////////////////////////////////////////////
// CSystemBox dialog

class CSystemBox : public RowanDialog
{
// Construction
public:
	bool	once;
	void Init(UINT nIDTemplate, CWnd * pParentWnd);
	CSystemBox(CMainFrame* mainf,CWnd* pParent = NULL);   // standard constructor
	CMainFrame* m_pParent;
// Dialog Data
	//{{AFX_DATA(CSystemBox)
	enum { IDD = IDD_SYSTEM };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_THUMBNAIL;
	CRButton	m_IDC_ZOOMIN;
	CRButton	m_IDC_FILES;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemBox)
	afx_msg void OnClickedFiles();
	afx_msg void OnClickedThumbnail();
	afx_msg void OnClickedZoomin();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMBOX_H__72355DC1_3997_11D1_A1F0_444553540000__INCLUDED_)
