#if !defined(AFX_SESSION_H__7F632942_0F49_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_SESSION_H__7F632942_0F49_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// session.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectSession dialog

class CSelectSession : public RowanDialog
{
// Construction
public:
	UINT	m_timer;
	int		currsessrow;
	CSelectSession(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectSession)
	enum { IDD = IDD_SELECTSESSION };
	CRListBox	m_IDC_RLIST_SELECTSESSION;
	CRStatic	m_IDC_RSTATICCTRL24;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectSession)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectSession)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistSelectsession(long row, long column);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SESSION_H__7F632942_0F49_11D2_A5A3_0040052179B6__INCLUDED_)
