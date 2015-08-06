#if !defined(AFX_MSNDEBRF_H__8C2D94E2_CCDA_11D2_8ADB_004005247C35__INCLUDED_)
#define AFX_MSNDEBRF_H__8C2D94E2_CCDA_11D2_8ADB_004005247C35__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MsnDeBrf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeBrief dialog

class CDeBrief : public RowanDialog
{
// Construction
public:
	CDeBrief(int package, CWnd* pParent = NULL);   // standard constructor

	int packnum;
// Dialog Data
	//{{AFX_DATA(CDeBrief)
	enum { IDD = IDD_DEBRIEF };
		// NOTE: the ClassWizard will add data members here
		CRStatic	m_IDC_OBJECTIVE;
		CRStatic	m_IDC_RATING;
		CRStatic	m_IDC_STATUS;
		CRStatic	m_IDC_RSTATICSOFT0;
		CRStatic	m_IDC_RSTATICSOFT1;
		CRStatic	m_IDC_RSTATICSOFT2;
		CRStatic	m_IDC_RSTATICSOFT3;
		CRStatic	m_IDC_INFOSOFT0;
		CRStatic	m_IDC_INFOSOFT1;
		CRStatic	m_IDC_INFOSOFT2;
		CRStatic	m_IDC_INFOSOFT3;
		CRStatic	m_IDC_RSTATIC3;




	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeBrief)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   		void	ParentDialClosed(RDialog*,int rv);


	// Generated message map functions
	//{{AFX_MSG(CDeBrief)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSNDEBRF_H__8C2D94E2_CCDA_11D2_8ADB_004005247C35__INCLUDED_)
