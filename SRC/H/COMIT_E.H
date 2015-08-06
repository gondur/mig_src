#if !defined(AFX_COMIT_E_H__3697AD42_CD76_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_COMIT_E_H__3697AD42_CD76_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Comit_e.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComit_e dialog
class	CDirects2;
class	CSelectionResults;

class CComit_e : public RowanDialog
{
// Construction
public:

	CComit_e(CWnd* pParent = NULL);   // standard constructor







	static	CDirects2*  directivelines[MAXDIRECTIVES];
	static	CSelectionResults*  directivedetails[MAXDIRECTIVES];
	static	CComit_e*	This;

//	bool	B29Avail;


DirControl	dir_ctrl;


//char	tot_acresource[7];

//enum	{AIRSUPERIORITY = 0, CHOKE, SUPPLY, AIRFIELDS, RAIL, ROAD, ARMY};



// Dialog Data
	//{{AFX_DATA(CComit_e)
	enum { IDD = IDD_COMIT_E };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_TSQUAD;
	CRStatic	m_IDC_TSQUAD2;
	CRStatic	m_IDC_TSQUAD3;
	CRStatic	m_IDC_TSQUAD4;
	CRStatic	m_IDC_TSQUAD5;
	CRButton	m_IDC_AUTOGENERATE;
	CRButton	m_IDC_AUTODISPLAY;
	CRStatic	m_IDC_TSQUAD6;
	CRStatic	m_IDC_TSQUAD7;
	CRButton	m_IDCALPHAALLOWED;
	CRStatic	m_IDC_TSQUAD8;
	CRStatic	m_IDC_TSQUAD9;
	CRStatic	m_IDC_STRIKEINUSE;
	CRStatic	m_IDC_FIGHTERSINUSE;
	CRStatic	m_IDC_TARGETSINUSE;
	CRStatic	m_IDC_MISSIONSINUSE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComit_e)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void RedrawAll();


protected:



	// Generated message map functions
	//{{AFX_MSG(CComit_e)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedCamplist();
	afx_msg void OnOKTitle();
	afx_msg void OnOKAutogenerate();
	afx_msg void OnOKAutodisplay();
	afx_msg void OnClickedAutogenerate();
	afx_msg void OnClickedAutodisplay();
	afx_msg void OnClickedCalphaallowed();
	afx_msg void OnClickedTitle();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMIT_E_H__3697AD42_CD76_11D1_A5A3_0040052179B6__INCLUDED_)
