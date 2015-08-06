#if !defined(AFX_NOTES_H__FF688EC3_CA28_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_NOTES_H__FF688EC3_CA28_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Notes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNotes dialog

class CNotes : public RowanDialog
{
// Construction
public:
	CNotes(int sgt,int uid,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNotes)
	enum { IDD = IDD_NOTES };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_RSTATICCTRL1;
	CRStatic	m_IDC_TARGET_TITLE;
	CRStatic	m_IDC_NOTES;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNotes)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTES_H__FF688EC3_CA28_11D1_A5A3_0040052179B6__INCLUDED_)
