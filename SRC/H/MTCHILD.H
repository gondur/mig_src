#if !defined(AFX_MTCHILD_H__485C68C1_09D7_11D2_9FD6_D0EC00C10000__INCLUDED_)
#define AFX_MTCHILD_H__485C68C1_09D7_11D2_9FD6_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MTChild.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EmptyChildWindow dialog

class EmptyChildWindow : public RowanDialog
{
// Construction
public:
	EmptyChildWindow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EmptyChildWindow)
	enum { IDD = IDD_EMPTYCHILD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EmptyChildWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EmptyChildWindow)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MTCHILD_H__485C68C1_09D7_11D2_9FD6_D0EC00C10000__INCLUDED_)
