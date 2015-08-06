#if !defined(AFX_SVIEWER_H__CB7A5322_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SVIEWER_H__CB7A5322_FA0F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SViewer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSViewer dialog

class CSViewer : public RowanDialog
{
// Construction
public:
	CSViewer(CWnd* pParent = NULL);   // standard constructor
		void PreDestroyPanel();
		UINT ViewsPref_Timer;


// Dialog Data
	//{{AFX_DATA(CSViewer)
	enum { IDD = IDD_SVIEWER };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	CRStatic	m_IDC_RSTATICCTRL2;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_RSTATICCTRL5;
	CRStatic	m_IDC_RSTATICCTRL6;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_RSTATICCTRL8;
	CRStatic	m_IDC_RSTATICCTRL9;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRStatic	m_IDC_RSTATICCTRL12;
	CRStatic	m_IDC_RSTATICCTRL14;
	CRStatic	m_IDC_RSTATICCTRL16;
	CRCombo m_IDC_CBO_MULTIPLAYER_VIEW;
	CRCombo m_IDC_CBO_PERIPHERAL_VISION;
	CRCombo m_IDC_CBO_AUTO_PADLOCK;
	CRCombo m_IDC_CBO_VIEW_MODE_SELECT;
	CRCombo m_IDC_CBO_PADLOCK;
	CRCombo m_IDC_CBO_CAMERACOLOUR;
	CRCombo m_IDC_CBO_UNITS;
	CRCombo m_IDC_CBO_GUNCAMERAONATSTART;
	CRCombo m_IDC_CBO_HEADSUPDISPLAY;
	CRCombo m_IDC_CBO_INFOLINE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSViewer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSViewer)
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SVIEWER_H__CB7A5322_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
