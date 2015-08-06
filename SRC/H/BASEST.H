#if !defined(AFX_BASEST_H__E22BAFC1_2DDA_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_BASEST_H__E22BAFC1_2DDA_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BasesT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BasesTitle dialog

class BasesTitle : public RowanDialog
{
// Construction
public:
	BasesTitle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BasesTitle)
	enum { IDD = IDD_BASES_TITLE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BasesTitle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BasesTitle)
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEST_H__E22BAFC1_2DDA_11D2_9FD5_D0EC00C10000__INCLUDED_)
