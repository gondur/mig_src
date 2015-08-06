#if !defined(AFX_ROUTE_H__DAE85E22_CD59_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_ROUTE_H__DAE85E22_CD59_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Route.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoute dialog

class CRoute : public RowanDialog
{
// Construction
public:
	CRoute(int pack,CWnd* pParent = NULL);   // standard constructor
	CRoute(int pack,int id,CWnd* pParent = NULL);   // standard constructor
	void	RefreshData(int childnum);
	bool	radioenabled;
// Dialog Data
	//{{AFX_DATA(CRoute)
	enum { IDD = IDD_ROUTE };
		// NOTE: the ClassWizard will add data members here
	CRRadio	m_IDC_MODE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoute)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoute)
	afx_msg void OnSelectedMode(long ButtonNum);
	afx_msg void OnEnable(BOOL bEnable);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUTE_H__DAE85E22_CD59_11D1_A5A3_0040052179B6__INCLUDED_)
