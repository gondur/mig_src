#if !defined(AFX_Credits_H__C6FA28C2_3E98_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_Credits_H__C6FA28C2_3E98_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif
// Credits.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCredits dialog

class CCredits : public RowanDialog
{
// Construction
public:
	CCredits(int thestring,CWnd* pParent = NULL);   // standard constructor
	UINT m_timerID;
	int strnum;
// Dialog Data
	//{{AFX_DATA(CCredits)
	enum { IDD = IDD_CREDITS };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCredits)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		creds;
	int		numcr;

	// Generated message map functions
	//{{AFX_MSG(CCredits)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	MSG2_0(OnGetXYOffset);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Credits_H__C6FA28C2_3E98_11D2_A5A3_0040052179B6__INCLUDED_)

