#if !defined(AFX_SQUADS_H__64D4AFA1_CE2F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SQUADS_H__64D4AFA1_CE2F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Squads.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSquads dialog

class CSquads : public RowanDialog
{
// Construction
public:
	void OnOK();
	CSquads(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSquads)
	enum { IDD = IDD_SQUADS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSquads)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSquads)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUADS_H__64D4AFA1_CE2F_11D1_A5A3_0040052179B6__INCLUDED_)
