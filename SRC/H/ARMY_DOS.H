#if !defined(AFX_ARMY_DOS_H__E1CC3EC1_D392_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_ARMY_DOS_H__E1CC3EC1_D392_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Army_dos.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArmy_dos dialog

class CArmy_dos : public RowanDialog
{
// Construction
public:
	CArmy_dos(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CArmy_dos)
	enum { IDD = IDD_ARMYDOSSIER };
		// NOTE: the ClassWizard will add data members here
		CRButton	m_IDJ_TITLE;
//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArmy_dos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArmy_dos)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARMY_DOS_H__E1CC3EC1_D392_11D1_A5A3_0040052179B6__INCLUDED_)
