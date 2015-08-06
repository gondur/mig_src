#if !defined(AFX_PLYR_LOG_H__C75E68C1_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_PLYR_LOG_H__C75E68C1_CF0E_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Plyr_log.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlyr_log dialog

class CPlyr_log : public RowanDialog
{
// Construction
public:
	CPlyr_log(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlyr_log)
	enum { IDD = IDD_PLAYERLOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlyr_log)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnOK();

	// Generated message map functions
	//{{AFX_MSG(CPlyr_log)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLYR_LOG_H__C75E68C1_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
