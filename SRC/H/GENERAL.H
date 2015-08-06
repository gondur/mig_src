#if !defined(AFX_GENERAL_H__FF688EC1_CA28_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_GENERAL_H__FF688EC1_CA28_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// General.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGeneral dialog

class CGeneral : public RowanDialog
{
// Construction
public:
	CGeneral(int sgt,int suid,CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CGeneral)
	enum { IDD = IDD_GENERAL };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_RSTATICCTRL1;
	CRStatic	m_IDC_TARGET_TITLE;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_MSR;
	CRStatic	m_IDC_RSTATICCTRL9;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRStatic	m_IDC_RSTATICCTRL11;
	CRStatic	m_IDC_RSTATICCTRL12;
	CRStatic	m_IDC_STATUS;
	CRStatic	m_IDC_RSTATICCTRL15;
	CRStatic	m_IDC_DATE_LAST_SORTIE;
	CRStatic	m_IDC_REPAIR_LEVEL;
	CRStatic	m_IDC_RSTATICCTRL21;
	CRStatic	m_IDC_THREAT_AAA;
	CRStatic	m_IDC_THREAT_MIG15;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	PrintDamageLevel(UWord damagelevel);
	void	PrintMiGActivity(SupplyNode*	node);
	void	DisplayRouteInfo(UniqueID uid, SupplyNode*	node, SupplyTree::Supply2UID relation);
	void	PrintLastSortie(Attacks attackstats);

	// Generated message map functions
	//{{AFX_MSG(CGeneral)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERAL_H__FF688EC1_CA28_11D1_A5A3_0040052179B6__INCLUDED_)
