#if !defined(AFX_RADIO_H__27646162_0F61_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_RADIO_H__27646162_0F61_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Radio.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRadio dialog

class CRadio : public RowanDialog
{
// Construction
public:
	CRadio(CWnd* pParent = NULL);   // standard constructor
	UINT	radio_timer;

// Dialog Data
	//{{AFX_DATA(CRadio)
	enum { IDD = IDD_RADIO };
	CEdit	m_IDCX_PLAYERMESSAGE8;
	CEdit	m_IDCX_PLAYERMESSAGE7;
	CEdit	m_IDCX_PLAYERMESSAGE6;
	CEdit	m_IDCX_PLAYERMESSAGE5;
	CEdit	m_IDCX_PLAYERMESSAGE4;
	CEdit	m_IDCX_PLAYERMESSAGE3;
	CEdit	m_IDCX_PLAYERMESSAGE2;
	CEdit	m_IDCX_PLAYERMESSAGE1;
	CREdit	m_IDC_PLAYERMESSAGE1;
	CREdit	m_IDC_PLAYERMESSAGE2;
	CREdit	m_IDC_PLAYERMESSAGE3;
	CREdit	m_IDC_PLAYERMESSAGE4;
	CREdit	m_IDC_PLAYERMESSAGE5;
	CREdit	m_IDC_PLAYERMESSAGE6;
	CREdit	m_IDC_PLAYERMESSAGE7;
	CREdit	m_IDC_PLAYERMESSAGE8;
	CREdit	m_IDC_PLAYERMESSAGE9;
	CREdit	m_IDC_PLAYERMESSAGE10;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadio)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadio)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTextChangedPlayermessage10(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage1(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage2(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage3(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage4(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage5(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage6(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage7(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage8(LPTSTR text);
	afx_msg void OnUpdatePlayermessage1();
	afx_msg void OnUpdatePlayermessage2();
	afx_msg void OnUpdatePlayermessage3();
	afx_msg void OnUpdatePlayermessage4();
	afx_msg void OnUpdatePlayermessage5();
	afx_msg void OnUpdatePlayermessage6();
	afx_msg void OnUpdatePlayermessage7();
	afx_msg void OnUpdatePlayermessage8();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADIO_H__27646162_0F61_11D2_A5A3_0040052179B6__INCLUDED_)
