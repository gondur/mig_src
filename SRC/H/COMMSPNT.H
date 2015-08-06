#if !defined(AFX_COMMSPNT_H__0239C701_584E_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_COMMSPNT_H__0239C701_584E_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CommsPnt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommsPaint dialog

class CCommsPaint : public RowanDialog
{
// Construction
public:
	CCommsPaint(CWnd* pParent = NULL);   // standard constructor
	UINT	paintshop_timer;

// Dialog Data
	//{{AFX_DATA(CCommsPaint)
	enum { IDD = IDD_COMMSPAINT };
	CRButton	m_IDC_NOSEART0;
	CRButton	m_IDC_NOSEART1;
	CRButton	m_IDC_NOSEART2;
	CRButton	m_IDC_NOSEART3;
	CRButton	m_IDC_NOSEART4;
	CRButton	m_IDC_NOSEART5;
	CRButton	m_IDC_NOSEART6;
	CRButton	m_IDC_NOSEART7;
	CRButton	m_IDC_NOSEART8;
	CRButton	m_IDC_NOSEART9;
	CRButton	m_IDC_NOSEART10;
	CRButton	m_IDC_NOSEART11;
	CRButton	m_IDC_NOSEART12;
	CRButton	m_IDC_NOSEART13;
	CRButton	m_IDC_NOSEART14;
	CRButton	m_IDC_NOSEART15;
	CRButton	m_IDC_NOSEART16;
	CRButton	m_IDC_NOSEART17;
	CRButton	m_IDC_NOSEART18;
	CRButton	m_IDC_NOSEART19;
	CRButton	m_IDC_NOSEART20;
	CRButton	m_IDC_NOSEART21;
	CRButton	m_IDC_NOSEART22;
	CRButton	m_IDC_NOSEART23;
	CRButton	m_IDC_NOSEART24;
	CRButton	m_IDC_NOSEART25;
	CRButton	m_IDC_NOSEART26;
	CRButton	m_IDC_NOSEART27;
	CRButton	m_IDC_NOSEART28;
	CRButton	m_IDC_NOSEART29;
	CRButton	m_IDC_NOSEART30;
	CRButton	m_IDC_NOSEART31;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommsPaint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommsPaint)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnClickedButtonID(int ID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSPNT_H__0239C701_584E_11D2_9FD5_D0EC00C10000__INCLUDED_)
