#if !defined(AFX_SGAME_H__CB7A5323_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SGAME_H__CB7A5323_FA0F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SGame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSGame dialog

class CSGame : public RowanDialog
{
// Construction
public:
	CSGame(CWnd* pParent = NULL);   // standard constructor
	void PreDestroyPanel();
	UINT GamePref_Timer;

// Dialog Data
	//{{AFX_DATA(CSGame)
	enum { IDD = IDD_SGAME };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	CRStatic	m_IDC_RSTATICCTRL2;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_RSTATICCTRL5;
	CRStatic	m_IDC_RSTATICCTRL6;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRStatic	m_IDC_RSTATICCTRL12;
	CRStatic	m_IDC_RSTATICCTRL14;
	CRStatic	m_IDC_RSTATICCTRL16;
	CRCombo	m_IDC_CBO_WEAPONS;
	CRCombo	m_IDC_CBO_VULNERABLETOFIRE;
	CRCombo	m_IDC_CBO_GROUNDCOLLISIONS;
	CRCombo	m_IDC_CBO_MIDAIRCOLLISIONS;
	CRCombo	m_IDC_CBO_AIPILOTALLTIME;
	CRCombo	m_IDC_CBO_ACCELOFF;
	CRCombo	m_IDC_CBO_TARGETSIZE;
	CRCombo	m_IDC_CBO_SKILL_UN;
	CRCombo	m_IDC_CBO_SKILL_REDS;
	CRCombo	m_IDC_CBO_GUNSIGHTRANGING;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSGame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSGame)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SGAME_H__CB7A5323_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
