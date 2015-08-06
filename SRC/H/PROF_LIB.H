#if !defined(AFX_PROF_LIB_H__4944BE41_DAB6_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_PROF_LIB_H__4944BE41_DAB6_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Prof_lib.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProfile_Library dialog

class CProfile_Library : public RowanDialog
{
// Construction
public:
	CProfile_Library(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProfile_Library)
	enum { IDD = IDD_PROFILE_LIBRARY };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLIST_DETAILS_PILOT1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfile_Library)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProfile_Library)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROF_LIB_H__4944BE41_DAB6_11D1_A5A3_0040052179B6__INCLUDED_)
