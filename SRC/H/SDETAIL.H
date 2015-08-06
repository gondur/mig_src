#if !defined(AFX_SDETAIL_H__21F9B521_F983_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SDETAIL_H__21F9B521_F983_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SDetail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSDetail dialog

struct SDrvrModes;

class CSDetail : public RowanDialog
{
// Construction
public:
	CSDetail(CWnd* pParent = NULL);   // standard constructor
	void PreDestroyPanel();
	UINT	ThreeDeePref_Timer;
	bool fNoPrimaryDisplay;

// Dialog Data
	//{{AFX_DATA(CSDetail)
	enum { IDD = IDD_SDETAIL };
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
	CRCombo m_IDC_CBO_DISPLAYDRIVERS;
	CRCombo m_IDC_CBO_RESOLUTIONS;
	CRCombo	m_IDC_CBO_AUTOFRAMERATE;
	CRCombo	m_IDC_CBO_LOWESTFRAMERATE;
	CRCombo	m_IDC_CBO_GAMMACORRECTION;
	CRCombo	m_IDC_CBO_GROUNDSHADING;
	CRCombo	m_IDC_CBO_ITEMSHADING;
//DEADCODE RDH 15/02/99 	CRCombo	m_IDC_CBO_SHOWIRONWORK;
	CRCombo	m_IDC_CBO_REFLECTIONS;
	CRStatic	m_IDC_RSTATICCTRL48;
	CRCombo	m_IDC_CBO_WEATHER;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDetail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSDetail)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTextChangedCboDisplaydrivers(LPCTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void CheckForPrimaryDisplay(int,SDrvrModes*);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDETAIL_H__21F9B521_F983_11D1_A5A3_0040052179B6__INCLUDED_)
