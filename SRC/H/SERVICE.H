#if !defined(AFX_SERVICE_H__7F632941_0F49_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_SERVICE_H__7F632941_0F49_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// service.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectService dialog

class CSelectService : public RowanDialog
{
// Construction
public:
	CSelectService(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectService)
	enum { IDD = IDD_SELECTSERVICE };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLIST_SELECTSERVICE;
	CRStatic	m_IDC_RSTATICCTRL24;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectService)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectService)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistSelectservice(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICE_H__7F632941_0F49_11D2_A5A3_0040052179B6__INCLUDED_)
