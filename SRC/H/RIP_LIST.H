#if !defined(AFX_RIP_LIST_H__64D4AFA4_CE2F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_RIP_LIST_H__64D4AFA4_CE2F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RIP_List.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRIP_List dialog

class CRIP_List : public RowanDialog
{
// Construction
public:
	CRIP_List(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRIP_List)
	enum { IDD = IDD_RIP_LIST };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATICCTRL1;
	CRStatic	m_IDC_RIPDATE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRIP_List)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
		void	ParentDialClosed(RDialog*,int rv);

	// Generated message map functions
	//{{AFX_MSG(CRIP_List)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIP_LIST_H__64D4AFA4_CE2F_11D1_A5A3_0040052179B6__INCLUDED_)
