#if !defined(AFX_CAMPWAR_H__D3363401_633F_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_CAMPWAR_H__D3363401_633F_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// campwar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCampBackEntireWar dialog

class CCampBackEntireWar : public RowanDialog
{
// Construction
public:
	CCampBackEntireWar(int thestring,CWnd* pParent = NULL);   // standard constructor
	int strnum;

// Dialog Data
	//{{AFX_DATA(CCampBackEntireWar)
	enum { IDD = IDD_CAMPAIGNBACKENTIREWAR };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCampBackEntireWar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCampBackEntireWar)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMPWAR_H__D3363401_633F_11D2_9FD5_D0EC00C10000__INCLUDED_)
