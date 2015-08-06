#if !defined(AFX_LOADPROF_H__6FFB8421_7AFB_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_LOADPROF_H__6FFB8421_7AFB_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LoadProf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoadProf dialog

class CLoadProf : public RowanDialog
{
// Construction
public:
	CLoadProf(int uid, CWnd* pParent = NULL);   // standard constructor
	static CString selectedfile;
	static	RDialog* MakeSheet(int uid);

	int		trguid;
	void	OnOK(); 
	void	OnCancel(); 


// Dialog Data
	//{{AFX_DATA(CLoadProf)
	enum { IDD = IDD_LOADPROFILE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadProf)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SwopFighterIfNecessary(int packnum, int wave, int group,int& Org_left, int& Opt_left, int Opt_Squad);
	void EnsureAvailMedBmbAndFighterUsed(int packnum, int f86a_left, int f86b_left);

	// Generated message map functions
	//{{AFX_MSG(CLoadProf)
//	afx_msg void OnOKTitle();
//	afx_msg void OnCancelTitle();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADPROF_H__6FFB8421_7AFB_11D2_9FD5_D0EC00C10000__INCLUDED_)
