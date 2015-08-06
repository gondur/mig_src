#if !defined(AFX_CHOKE_H__7CC731A5_CA3D_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_CHOKE_H__7CC731A5_CA3D_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Choke.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChoke dialog

class CChoke : public RowanDialog
{
// Construction
public:
	CChoke(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChoke)
	enum { IDD = IDD_CHOKE };
		// NOTE: the ClassWizard will add data members here
	CRRadio	m_IDC_RRADIOCTRL2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChoke)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChoke)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOKE_H__7CC731A5_CA3D_11D1_A5A3_0040052179B6__INCLUDED_)
