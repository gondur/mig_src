#if !defined(AFX_LISTBX_H__F27EF061_C95A_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_LISTBX_H__F27EF061_C95A_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListBx.h : header file
//
class CRComboCtrl;

/////////////////////////////////////////////////////////////////////////////
// CListBx dialog

class CListBx : public CDialog
{
// Construction
public:
	CListBx(CWnd* pParent = NULL);   // standard constructor
	CRComboCtrl* m_pCombo;

// Dialog Data
	//{{AFX_DATA(CListBx)
	enum { IDD = IDD_LISTBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListBx)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBX_H__F27EF061_C95A_11D1_A1F0_444553540000__INCLUDED_)
