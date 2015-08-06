//Old_Code JW 09Mar99 //{{AFX_INCLUDES()
//Old_Code JW 09Mar99 #include "redit.h"
//Old_Code JW 09Mar99 //}}AFX_INCLUDES
#if !defined(AFX_CAREER_H__C75E68C3_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_CAREER_H__C75E68C3_CF0E_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Career.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCareer dialog

class CCareer : public RowanDialog
{
// Construction
public:
	CCareer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCareer)
	enum { IDD = IDD_CAREER };
	CEdit	m_IDCX_NAME;
	CREdit	m_IDC_NAME;
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATICCTRL3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCareer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnOK();
	// Generated message map functions
	//{{AFX_MSG(CCareer)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTextChangedName(LPTSTR text);
	afx_msg void OnUpdateName();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAREER_H__C75E68C3_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
