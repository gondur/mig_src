
#if !defined(AFX_WPDETAIL_H__9C1F6041_3383_11D2_83A5_00004760763D__INCLUDED_)
#define AFX_WPDETAIL_H__9C1F6041_3383_11D2_83A5_00004760763D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WPDetail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WPDetail dialog

class WPDetail : public RowanDialog
{
// Construction
public:
	WPDetail(int p,int w,int g,int u,int id=IDD_WPDETAIL,CWnd* pParent = NULL);   // standard constructor
	RowanDialog* wplist;
	enum	{DATA,NEXT,PREV};
	int startperiod;
	int stepsize;
	int steps;
// Dialog Data
	//{{AFX_DATA(WPDetail)
	enum { IDD = IDD_WPDETAIL };
	CRStatic	m_IDC_SDETAIL2;
	CRStatic	m_IDC_SDETAIL4;
	CRStatic	m_IDC_SDETAIL6;
	CRStatic	m_IDC_FUEL;
	CRCombo	m_IDC_ALT;
//DEADCODE RDH 16/02/99 	CREdit	m_IDC_ETA_ABS;
	CREdtBt	m_IDC_NAME;
	CRButton	m_IDC_PREV;
	CRButton	m_IDC_NEXT;
	CRStatic	m_IDC_SDETAIL5;
	CRStatic	m_IDC_ETA_REL;
	CRStatic	m_IDC_ETANONEDIT;
	CRSpinBut m_IDC_RSPINETA;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WPDetail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//void ParentDialClosed(RDialog*,int rv);
	void RefreshData(int childnum);
	void RefreshEtasAndFuel();
	void UpdateEtasAndFuel();
	void FillSpinBut(int t);

	void ValidateEta();



	// Generated message map functions
	//{{AFX_MSG(WPDetail)
	afx_msg void OnTextChangedAlt(LPCTSTR text);
	afx_msg void OnClickedName();
	afx_msg void OnTextChangedVelocity(LPCTSTR text);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClickedInsbefore();
	afx_msg void OnClickedInsafter();
	afx_msg void OnClickedNext();
	afx_msg void OnClickedPrev();
	afx_msg void OnTextChangedRspineta(LPCTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPDETAIL_H__9C1F6041_3383_11D2_83A5_00004760763D__INCLUDED_)
