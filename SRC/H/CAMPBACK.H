#if !defined(AFX_CAMPBACK_H__C6FA28C2_3E98_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_CAMPBACK_H__C6FA28C2_3E98_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CampBack.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCampBack dialog

class CCampBack : public RowanDialog
{
// Construction
public:
	CCampBack(int thestring, int the_idd = IDD, CWnd* pParent = NULL);   // standard constructor
	int strnum;
// Dialog Data
	//{{AFX_DATA(CCampBack)
	enum { IDD = IDD_CAMPAIGNBACKGROUND };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCampBack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCampBack)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg long OnGetXYOffset();
	MSG2_0(OnGetXYOffset);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMPBACK_H__C6FA28C2_3E98_11D2_A5A3_0040052179B6__INCLUDED_)
