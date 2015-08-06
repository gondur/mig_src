#if !defined(AFX_SSOUND_H__CB7A5321_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SSOUND_H__CB7A5321_FA0F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SSound.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSSound dialog

class CSSound
 : public RowanDialog
{
// Construction
public:
	CSSound(CWnd* pParent = NULL);   // standard constructor
	void PreDestroyPanel();
	UINT OthersPref_Timer;
// Dialog Data
	//{{AFX_DATA(CSSound)
	enum { IDD = IDD_SSOUND };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	CRStatic	m_IDC_RSTATICCTRL2;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRCombo	m_IDC_CBO_MUSIC;
	CRCombo	m_IDC_CBO_SFX;
	CRCombo	m_IDC_CBO_SFX2;
	CRCombo	m_IDC_CBO_SFX3;
	CRCombo	m_IDC_CBO_RADIOCHATTER;
	CRCombo	m_IDC_CBO_ENGINESOUND;
	CRCombo	m_IDC_CBO_GEFFECTS;
	CRCombo	m_IDC_CBO_INJURYEFFECTS;
	CRCombo	m_IDC_CBO_WHITEOUTS;
	CRCombo	m_IDC_CBO_AUTOVECTORING;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSound)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSSound)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSOUND_H__CB7A5321_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
