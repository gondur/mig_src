#if !defined(AFX_DOSBUT_H__CEB45521_2BB7_11D2_83A5_00004760763D__INCLUDED_)
#define AFX_DOSBUT_H__CEB45521_2BB7_11D2_83A5_00004760763D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DosBut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DossierButtons dialog

class DossierButtons : public RowanDialog
{
// Construction
public:
	DossierButtons(int uid,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DossierButtons)
	enum { IDD = IDD_DOSSBUTTONS };
	CRButton	m_IDC_AUTHORISE; 
	CRButton	m_IDC_CENTRE;    
	CRButton	m_IDC_PHOTO;     
	CRButton	m_IDC_Zoom;      

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DossierButtons)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DossierButtons)
	afx_msg void OnClickedAuthorise();
	afx_msg void OnClickedCentre();
	afx_msg void OnClickedPhoto();
	afx_msg void OnClickedZoom();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSBUT_H__CEB45521_2BB7_11D2_83A5_00004760763D__INCLUDED_)
