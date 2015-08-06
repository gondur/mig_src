#if !defined(AFX_CAMPLIST_H__3697AD41_CD76_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_CAMPLIST_H__3697AD41_CD76_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Camplist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCamplist dialog

class CCamplist : public RowanDialog
{
// Construction
public:
	CCamplist(CWnd* pParent = NULL);   // standard constructor
 	void ParentDialClosed(RDialog*,int rv);

// Dialog Data
	//{{AFX_DATA(CCamplist)
	enum { IDD = IDD_CAMPLIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamplist)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCamplist)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedProfilelibrary();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMPLIST_H__3697AD41_CD76_11D1_A5A3_0040052179B6__INCLUDED_)
