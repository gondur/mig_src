#if !defined(AFX_SQUICKP_H__DF9A48A1_69F5_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_SQUICKP_H__DF9A48A1_69F5_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// sQuickP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// QuickMissionPanel dialog

class QuickMissionPanel : public RowanDialog
{
// Construction
public:
	QuickMissionPanel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(QuickMissionPanel)
	enum { IDD = IDD_SQUICKBACK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(QuickMissionPanel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(QuickMissionPanel)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUICKP_H__DF9A48A1_69F5_11D2_A5A3_0040052179B6__INCLUDED_)
