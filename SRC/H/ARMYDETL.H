#if !defined(AFX_ARMYDETL_H__E1CC3EC2_D392_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_ARMYDETL_H__E1CC3EC2_D392_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArmyDetl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArmyDetails dialog

class CArmyDetails : public RowanDialog
{
// Construction
public:
	CArmyDetails(UniqueID uid,UniqueID forceuid, int side, CWnd* pParent = NULL);   // standard constructor
	static RDialog* MakeSheet(CRect r,UniqueID item, UniqueID force, int side );
	void	RefreshData(int uid);
	void	Refresh(); 

	UniqueID u, forceu;
	int s;
// Dialog Data
	//{{AFX_DATA(CArmyDetails)
	enum { IDD = IDD_ARMYDETAILS };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDJ_TITLE;
	CRStatic	m_IDC_RSTATICCTRL2;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_RSTATICCTRL5;
	CRStatic	m_IDC_RSTATICCTRL6;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_RSTATICCTRL8;
	CRStatic	m_IDC_RSTATICCTRL9;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRStatic	m_IDC_RSTATICCTRL11;
	CRStatic	m_IDC_UN_INIT_SIZE;
	CRStatic	m_IDC_UN_CURR_SIZE;
	CRStatic	m_IDC_UN_MORALE;
	CRStatic	m_IDC_RED_INIT_SIZE;
	CRStatic	m_IDC_RED_CURR_SIZE;
	CRStatic	m_IDC_RED_MORALE;
	CRStatic	m_IDC_FRONTLINE;
	CRStatic	m_IDC_BATTLEAREA;
	CRStatic	m_IDC_SITUATION;
	CRStatic	m_IDC_FAC_CALLSIGN;
	CRStatic	m_IDC_TAC_CALLSIGN;
	CRStatic	m_IDC_RSTATICCTRL23;
	CRButton	m_IDC_AUTHORISE; 
	CRButton	m_IDC_DETAILS;


	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArmyDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArmyDetails)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedAuthorise();
	afx_msg void OnClickedDetails();
	afx_msg void OnClickedDossier();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARMYDETL_H__E1CC3EC2_D392_11D1_A5A3_0040052179B6__INCLUDED_)
