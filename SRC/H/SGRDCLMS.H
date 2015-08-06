#if !defined(AFX_SGRDCLMS_H__A63CF8A2_FEE3_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SGRDCLMS_H__A63CF8A2_FEE3_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SGrdClms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSQuickGroundClaims dialog

class CSQuickGroundClaims : public RowanDialog
{
// Construction
public:
	CSQuickGroundClaims(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSQuickGroundClaims)
	enum { IDD = IDD_SQUICKMISSIONDEBRIEF_GROUNDCLAIMS };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	CRStatic	m_IDC_RSTATICCTRL2;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_RSTATICCTRL5;
	CRStatic	m_IDC_SDETAIL2;
	CRStatic	m_IDC_RSTATICCTRL24;
	CRStatic	m_IDC_RSTATICCTRL6;
	CRStatic	m_IDC_SDETAIL4;
	CRStatic	m_IDC_SCLAIMS_PLAYER_SUPPLYVEHICLE;
	CRStatic	m_IDC_SCLAIMS_PLAYER_SUPPLYPOINT;
	CRStatic	m_IDC_SCLAIMS_PLAYER_SUPPLYTRAIN;
	CRStatic	m_IDC_SCLAIMS_PLAYER_MARSHALLINGYARD;
	CRStatic	m_IDC_SCLAIMS_PLAYER_BRIDGE;
	CRStatic	m_IDC_SCLAIMS_PLAYER_AIRFIELDS;
	CRStatic	m_IDC_SCLAIMS_PLAYER_ARTILLERYPOSITION;
	CRStatic	m_IDC_SCLAIMS_PLAYER_TROOPCONCENTRATION;
	CRStatic	m_IDC_SCLAIMS_PLAYER_TANK;
	CRStatic	m_IDC_SDETAIL16;
	CRStatic	m_IDC_SDETAIL20;
	CRStatic	m_IDC_SCLAIMS_UN_SUPPLYVEHICLE;
	CRStatic	m_IDC_SCLAIMS_UN_SUPPLYPOINT;
	CRStatic	m_IDC_SCLAIMS_UN_SUPPLYTRAIN;
	CRStatic	m_IDC_SCLAIMS_UN_MARSHALLINGYARD;
	CRStatic	m_IDC_SCLAIMS_UN_BRIDGE;
	CRStatic	m_IDC_SCLAIMS_UN_AIRFIELDS;
	CRStatic	m_IDC_SCLAIMS_UN_ARTILLERYPOSITION;
	CRStatic	m_IDC_SCLAIMS_UN_TROOPCONCENTRATION;
	CRStatic	m_IDC_SCLAIMS_UN_TANK;
	CRStatic	m_IDC_SCLAIMS_RED_SUPPLYVEHICLE;
	CRStatic	m_IDC_SCLAIMS_RED_SUPPLYPOINT;
	CRStatic	m_IDC_SCLAIMS_RED_SUPPLYTRAIN;
	CRStatic	m_IDC_SCLAIMS_RED_MARSHALLINGYARD;
	CRStatic	m_IDC_SCLAIMS_RED_BRIDGE;
	CRStatic	m_IDC_SCLAIMS_RED_AIRFIELDS;
	CRStatic	m_IDC_SCLAIMS_RED_ARTILLERYPOSITION;
	CRStatic	m_IDC_SCLAIMS_RED_TROOPCONCENTRATION;
	CRStatic	m_IDC_SCLAIMS_RED_TANK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQuickGroundClaims)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSQuickGroundClaims)
	afx_msg void OnPaint();
	afx_msg void OnCancelMode();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SGRDCLMS_H__A63CF8A2_FEE3_11D1_A5A3_0040052179B6__INCLUDED_)
