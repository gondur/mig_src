#if !defined(AFX_TARGETDOSSIER_H__C378D721_C24A_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_TARGETDOSSIER_H__C378D721_C24A_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TargetDossier.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTargetDossier dialog

class CTargetDossier : public RowanDialog
{
// Construction
public:
	static RDialog* MakeSheet(CRect r,UniqueID item);
	CTargetDossier(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTargetDossier)
	enum { IDD = IDD_TARGETDOSSIER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTargetDossier)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTargetDossier)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TARGETDOSSIER_H__C378D721_C24A_11D1_A5A3_0040052179B6__INCLUDED_)
