#if !defined(AFX_MISNTEXT_H__C75E68C5_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_MISNTEXT_H__C75E68C5_CF0E_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Misntext.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMisntext dialog

class CMisntext : public RowanDialog
{
// Construction
public:
	CMisntext(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMisntext)
	enum { IDD = IDD_MISSIONTEXT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMisntext)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMisntext)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MISNTEXT_H__C75E68C5_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
