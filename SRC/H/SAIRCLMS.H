#if !defined(AFX_SAIRCLMS_H__A63CF8A1_FEE3_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SAIRCLMS_H__A63CF8A1_FEE3_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SAirClms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSQuickAirClaims dialog

class CSQuickAirClaims : public RowanDialog
{
// Construction
public:
	CSQuickAirClaims(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSQuickAirClaims)
	enum { IDD = IDD_SQUICKMISSIONDEBRIEF_AIRCLAIMS };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_RSTATICCTRL25;
	CRStatic	m_IDC_SDETAIL3;
	CRStatic	m_IDC_RSTATICCTRL26;
	CRStatic	m_IDC_RSTATICCTRL27;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRStatic	m_IDC_RSTATICCTRL28;
	CRStatic	m_IDC_RSTATICCTRL29;
	CRStatic	m_IDC_SCLAIMS_PLAYER_F80;
	CRStatic	m_IDC_SCLAIMS_PLAYER_F51;
	CRStatic	m_IDC_SCLAIMS_PLAYER_F84;
	CRStatic	m_IDC_SCLAIMS_PLAYER_F86;
	CRStatic	m_IDC_SCLAIMS_PLAYER_B26;
	CRStatic	m_IDC_SCLAIMS_PLAYER_B29;
	CRStatic	m_IDC_SCLAIMS_PLAYER_MIG15;
	CRStatic	m_IDC_SCLAIMS_PLAYER_YAK;
	CRStatic	m_IDC_SDETAIL4;
	CRStatic	m_IDC_SDETAIL16;
	CRStatic	m_IDC_SDETAIL20;
	CRStatic	m_IDC_SCLAIMS_UN_F80;
	CRStatic	m_IDC_SCLAIMS_UN_F51;
	CRStatic	m_IDC_SCLAIMS_UN_F84;
	CRStatic	m_IDC_SCLAIMS_UN_F86;
	CRStatic	m_IDC_SCLAIMS_UN_B26;
	CRStatic	m_IDC_SCLAIMS_UN_B29;
	CRStatic	m_IDC_SCLAIMS_UN_MIG15;
	CRStatic	m_IDC_SCLAIMS_UN_YAK;
	CRStatic	m_IDC_SCLAIMS_RED_F80;
	CRStatic	m_IDC_SCLAIMS_RED_F51;
	CRStatic	m_IDC_SCLAIMS_RED_F84;
	CRStatic	m_IDC_SCLAIMS_RED_F86;
	CRStatic	m_IDC_SCLAIMS_RED_B26;
	CRStatic	m_IDC_SCLAIMS_RED_B29;
	CRStatic	m_IDC_SCLAIMS_RED_MIG15;
	CRStatic	m_IDC_SCLAIMS_RED_YAK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQuickAirClaims)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSQuickAirClaims)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAIRCLMS_H__A63CF8A1_FEE3_11D1_A5A3_0040052179B6__INCLUDED_)
