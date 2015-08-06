#if !defined(AFX_VISITORS_H__B058C5C3_0CFE_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_VISITORS_H__B058C5C3_0CFE_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Visitors.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVisitorsBook dialog

class CVisitorsBook : public RowanDialog
{
// Construction
public:
	UINT vis_timer;

	CVisitorsBook(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVisitorsBook)
	enum { IDD = IDD_VISITORSBOOK };
	CRListBox	m_IDC_RLIST_VISITORS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisitorsBook)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVisitorsBook)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistVisitors(long row, long column);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISITORS_H__B058C5C3_0CFE_11D2_A5A3_0040052179B6__INCLUDED_)
