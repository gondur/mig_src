#if !defined(AFX_CURREMBL_H__79CD4BA1_59D1_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_CURREMBL_H__79CD4BA1_59D1_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurrEmbl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCurrEmblem dialog

class CCurrEmblem : public RowanDialog
{
// Construction
public:
	CCurrEmblem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCurrEmblem)
	enum { IDD = IDD_CURREMBLEM };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_NOSEART0;
	CRStatic	m_IDC_RSTATICCTRL24;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurrEmblem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCurrEmblem)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURREMBL_H__79CD4BA1_59D1_11D2_9FD5_D0EC00C10000__INCLUDED_)
