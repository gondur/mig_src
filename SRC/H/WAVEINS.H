#if !defined(AFX_WAVEINS_H__357542A0_7EC5_11D2_9684_0000476073D8__INCLUDED_)
#define AFX_WAVEINS_H__357542A0_7EC5_11D2_9684_0000476073D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WaveIns.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWaveInsert dialog

class CWaveInsert : public RowanDialog
{
// Construction
public:
	CWaveInsert(int pack,int wave, int d, int t, CWnd* pParent = NULL);   // standard constructor
	int time;
	int duty;
// Dialog Data
	//{{AFX_DATA(CWaveInsert)
	enum { IDD = IDD_WAVEINSERT };
	CEdit	m_IDCX_TIME;
	CRRadio	m_IDC_MAINDUTY;
	CREdit	m_IDC_TIME;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveInsert)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWaveInsert)
	afx_msg void OnOKTitle();
	afx_msg void OnSelectedMainduty(long ButtonNum);
	afx_msg void OnTextChangedTime(LPTSTR text);
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateTime();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEINS_H__357542A0_7EC5_11D2_9684_0000476073D8__INCLUDED_)
