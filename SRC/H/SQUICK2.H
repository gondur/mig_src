#if !defined(AFX_SQUICK2_H__CB7A5326_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SQUICK2_H__CB7A5326_FA0F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SQuick2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSQuick2 dialog

class CSQuick2 : public RowanDialog
{
// Construction
public:
	CSQuick2(CWnd* pParent = NULL);   // standard constructor
	UINT	Debrief_Timer;

// Dialog Data
	//{{AFX_DATA(CSQuick2)
	enum { IDD = IDD_SQUICKMISSIONDEBRIEF };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	CRStatic	m_IDC_RSTATICCTRL2;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_SMISSIONTITLE;
	CRStatic	m_IDC_SOBJECTIVETITLE;
	CRStatic	m_IDC_SOBJECTIVESTATUS;
	CRStatic	m_IDC_SMISSIONRATING;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQuick2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSQuick2)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUICK2_H__CB7A5326_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
