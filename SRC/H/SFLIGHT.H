#if !defined(AFX_SFLIGHT_H__692F5BC0_F0A0_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_SFLIGHT_H__692F5BC0_F0A0_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SFlight.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSFlight dialog

class CSFlight : public RowanDialog
{
// Construction
public:
	CSFlight(CWnd* pParent = NULL);   // standard constructor
	void PreDestroyPanel();
	UINT	FlightPref_Timer;

// Dialog Data
	//{{AFX_DATA(CSFlight)
	enum { IDD = IDD_SFLIGHT };
		// NOTE: the ClassWizard will add data members here
	CRCombo	m_IDC_CBO_ALL;
	CRStatic	m_IDC_RSTATICCTRL1;
	CRCombo	m_IDC_CBO_FLAMEOUTS;
	CRStatic	m_IDC_RSTATICCTRL2;
	CRCombo	m_IDC_CBO_POWERBOOST;
	CRCombo	m_IDC_CBO_AUTOTHROTTLE;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRCombo	m_IDC_CBO_RUDDER;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRCombo	m_IDC_CBO_WINDGUSTS;
	CRStatic	m_IDC_RSTATICCTRL5;
	CRCombo	m_IDC_CBO_SPINS;
	CRStatic	m_IDC_RSTATICCTRL6;
	CRCombo	m_IDC_CBO_AIRFRAME;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRCombo	m_IDC_CBO_STORES;
	CRStatic	m_IDC_RSTATICCTRL8;
	CRCombo	m_IDC_CBO_TORQUE;
	CRStatic	m_IDC_RSTATICCTRL9;
	CRCombo	m_IDC_CBO_ENGINE;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRCombo	m_IDC_CBO_WIND0;
	CRStatic	m_IDC_RSTATICCTRL52;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFlight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSFlight)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTextChangedCboAll(LPCTSTR text);
	afx_msg void OnTextChangedCboAirframe(LPCTSTR text);
	afx_msg void OnTextChangedCboEngine(LPCTSTR text);
	afx_msg void OnTextChangedCboFlameouts(LPCTSTR text);
	afx_msg void OnTextChangedCboPowerboost(LPCTSTR text);
	afx_msg void OnTextChangedCboRudder(LPCTSTR text);
	afx_msg void OnTextChangedCboSpins(LPCTSTR text);
	afx_msg void OnTextChangedCboStores(LPCTSTR text);
	afx_msg void OnTextChangedCboTorque(LPCTSTR text);
	afx_msg void OnTextChangedCboWind(LPCTSTR text);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTextChangedCboWind0(LPCTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFLIGHT_H__692F5BC0_F0A0_11D1_A1F0_0080C8582DE4__INCLUDED_)
