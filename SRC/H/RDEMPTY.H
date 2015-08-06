#if !defined(AFX_RDEMPTY_H__19CD38F5_A868_11D1_9B68_444553540000__INCLUDED_)
#define AFX_RDEMPTY_H__19CD38F5_A868_11D1_9B68_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RDEmpty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RDEmpty dialog

class RPEmpty : public RowanDialog
{
// Construction
public:
	RPEmpty(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RDEmpty)
	enum { IDD = IDD_EMPTYPAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	enum IDD_IDDs {IDD2=IDD_EMPTYDIAL};
protected:
	RPEmpty(IDD_IDDs IDD,CWnd* pParent);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RDEmpty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RDEmpty)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
class	RDEmpty:public RPEmpty
{
public:
	RDEmpty(CWnd* pParent = NULL)
		:RPEmpty(IDD2,pParent)	{}   // standard constructor
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RDEMPTY_H__19CD38F5_A868_11D1_9B68_444553540000__INCLUDED_)
