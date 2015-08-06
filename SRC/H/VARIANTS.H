#if !defined(AFX_VARIANTS_H__35AAB1E1_5A23_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_VARIANTS_H__35AAB1E1_5A23_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Variants.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVariants dialog

class CVariants : public RowanDialog
{
// Construction
public:
	CVariants(CWnd* pParent = NULL);   // standard constructor
	UINT	Variants_Timer;

// Dialog Data
	//{{AFX_DATA(CVariants)
	enum { IDD = IDD_VARIANTS };
		// NOTE: the ClassWizard will add data members here
	CRRadio	m_IDC_RRADIO_F86VARIANTS0;
	CRRadio	m_IDC_RRADIO_MUSTANGVARIANTS;
	CRRadio	m_IDC_RRADIO_F86VARIANTS1;
	CRStatic	m_IDC_RSTATICCTRL43;
	CRStatic	m_IDC_RSTATICCTRL53;
	CRStatic	m_IDC_RSTATICCTRL54;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVariants)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVariants)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectedRradioF86variants0(long ButtonNum);
	afx_msg void OnSelectedRradioF86variants1(long ButtonNum);
	afx_msg void OnSelectedRradioMustangvariants(long ButtonNum);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARIANTS_H__35AAB1E1_5A23_11D2_9FD5_D0EC00C10000__INCLUDED_)
