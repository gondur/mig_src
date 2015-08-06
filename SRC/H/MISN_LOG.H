#if !defined(AFX_MISN_LOG_H__C75E68C4_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_MISN_LOG_H__C75E68C4_CF0E_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Misn_log.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMisn_log dialog

class CMisn_log : public RowanDialog
{
// Construction
public:
	CMisn_log(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMisn_log)
	enum { IDD = IDD_MISSIONLOG };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMisn_log)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMisn_log)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MISN_LOG_H__C75E68C4_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
