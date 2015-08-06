#if !defined(AFX_VWQLIST_H__4CD00AA1_57B7_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_VWQLIST_H__4CD00AA1_57B7_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VwQList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewQList dialog

class CViewQList : public RowanDialog
{
// Construction
public:
	CViewQList(int side,int wave,int group,CWnd* pParent = NULL);   // standard constructor

	QuickFields*	fields;

// Dialog Data
	//{{AFX_DATA(CViewQList)
	enum { IDD = IDD_VIEWQLIST };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_GRPDESC;
	CRStatic	m_IDC_TYPE;
	CRStatic	m_IDC_FLIGHTS;
	CRStatic	m_IDC_ALT;
	CRStatic	m_IDC_SKILL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewQList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewQList)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VWQLIST_H__4CD00AA1_57B7_11D2_9FD5_D0EC00C10000__INCLUDED_)
