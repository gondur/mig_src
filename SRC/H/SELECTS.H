#if !defined(AFX_SELECTS_H__6ECCAEA3_3DD2_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_SELECTS_H__6ECCAEA3_3DD2_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Selects.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectionResults dialog

class CSelectionResults : public RowanDialog
{
// Construction
public:
	CSelectionResults(int d, CWnd* pParent = NULL);   // standard constructor

	int tab;
	void CSelectionResults::Redraw();

// Dialog Data
	//{{AFX_DATA(CSelectionResults)
	enum { IDD = IDD_SELECTIONRESULTS };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectionResults)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectionResults)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTS_H__6ECCAEA3_3DD2_11D2_9FD5_D0EC00C10000__INCLUDED_)
