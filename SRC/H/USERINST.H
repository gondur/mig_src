#if !defined(AFX_USERINST_H__597F62E1_78B5_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_USERINST_H__597F62E1_78B5_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UserInst.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserInst dialog

class CUserInst : public RowanDialog
{
// Construction
public:
	CUserInst(int* returnvalfillin=NULL,int requestmsg=IDS_SELECTTARGET,CWnd* pParent = NULL);   // standard constructor
	int*	seltargretval;
	int msg;
// Dialog Data
	//{{AFX_DATA(CUserInst)
	enum { IDD = IDD_SELECTTARGET };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_RSTATICCTRL3;
	CRButton	m_IDC_RESET;
	CRButton	m_IDC_CANCEL;
	//}}AFX_DATA
	void	OnOK();
	void	OnCancel();
	void	RefreshData(int targetid);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInst)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserInst)
	afx_msg void OnClickedSave();
	afx_msg void OnClickedReset();
	afx_msg void OnClickedCancel();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERINST_H__597F62E1_78B5_11D2_9FD5_D0EC00C10000__INCLUDED_)
