#ifndef SREPLAY_INCLUDED
#pragma once
#define SREPLAY_INCLUDED
//#include "..\h\SREPLAY.H"

/////////////////////////////////////////////////////////////////////////////
// CReplay dialog

class CSReplay : public RowanDialog
{
// Construction
public:
	CSReplay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReplay)
	enum { IDD = IDD_SREPLAY };
		// NOTE: the ClassWizard will add data members here
	CREdit	m_IDC_REDITCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReplay)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif