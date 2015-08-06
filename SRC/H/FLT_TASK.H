#if !defined(AFX_FLT_TASK_H__A17844E1_CD70_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_FLT_TASK_H__A17844E1_CD70_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Flt_Task.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlt_Task dialog

class CFlt_Task : public RowanDialog
{
// Construction
public:
	CFlt_Task(int pack,int wave,int group,CWnd* pParent = NULL);   // standard constructor
	int	displayedflights;
	int	seltargretval;
	static enum	Act {REFRESHNONE=0,REFRESHWPMAIN=1,REFRESHLOCALWP0,REFRESHLOCALWP1,REFRESHLOCALWP2,REFRESHWPMASK=255,REFRESHPARENT=256}	lastaction;
	int	actypebackup;
// Dialog Data
	//{{AFX_DATA(CFlt_Task)
	enum { IDD = IDD_FLT_TASK };
		// NOTE: the ClassWizard will add data members here
	CRCombo	m_IDC_ATTACKMETHOD;
	CRCombo	m_IDC_GROUPFORM;
	CRCombo	m_IDC_FLIGHTFORM;
	CRCombo	m_IDC_ATTACKPATTERN;
	CREdtBt	m_IDC_F0WEAPONS;
	CRStatic	m_IDC_TSQUAD;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_RSTATICCTRL8;
	CRStatic	m_IDC_RSTATICCTRL9;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRStatic	m_IDC_TF0W;
	CRStatic	m_IDC_TF0T0;
	CREdtBt	m_IDC_F0TARG0;
	CREdtBt	m_IDC_F0TARG1;
	CREdtBt	m_IDC_ACTYPE;
	CREdtBt	m_IDC_F1WEAPONS;
	CRStatic	m_IDC_TF1W;
	CRStatic	m_IDC_TF1T0;
	CREdtBt	m_IDC_F1TARG0;
	CREdtBt	m_IDC_F1TARG1;
	CREdtBt	m_IDC_F2WEAPONS;
	CRStatic	m_IDC_TF2W;
	CRStatic	m_IDC_TF2T0;
	CREdtBt	m_IDC_F2TARG0;
	CREdtBt	m_IDC_F2TARG1;
	CREdtBt	m_IDC_F3WEAPONS;
	CRStatic	m_IDC_TF3W;
	CRStatic	m_IDC_TF3T0;
	CREdtBt	m_IDC_F3TARG0;
	CREdtBt	m_IDC_F3TARG1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlt_Task)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
void	OnClickedWeapons(int flight);
void	OnClickedTarg0(int flight);
void	OnClickedTarg1(int flight);
void	FillRow(int flight,CREdtBt& m_idweap,CREdtBt& idprim,CREdtBt& idsec);
void	SetFlightCount();
void	RefreshAll();
void	RefreshData(int datatype);

	bool	escortishigh;

	enum	AttackRules	{RULE_HIDDEN,RULE_DIVE,RULE_ALL,RULE_WIDE,RULE_HIGH}
			attackislimit;
	enum	AttackType	{ATT_DIVE,ATT_LOW,ATT_HIGH}
			currattackmethod;
	int		currattackpattern;	//0=wide
	bool		EscortGoHigh();
	AttackRules	AttackGoLimit();
	bool		CheckAttackAgainstRules();


	// Generated message map functions
	//{{AFX_MSG(CFlt_Task)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedActype();
	afx_msg void OnClickedF0targ0();
	afx_msg void OnClickedF0weapons();
	afx_msg void OnClickedF1targ0();
	afx_msg void OnClickedF1targ1();
	afx_msg void OnClickedF1weapons();
	afx_msg void OnClickedF2targ0();
	afx_msg void OnClickedF2targ1();
	afx_msg void OnClickedF2weapons();
	afx_msg void OnClickedF3targ0();
	afx_msg void OnClickedF3targ1();
	afx_msg void OnClickedF3weapons();
	afx_msg void OnClickedF0targ1();
	afx_msg void OnTextChangedAttackmethod(LPCTSTR text);
	afx_msg void OnTextChangedAttackpattern(LPCTSTR text);
	afx_msg void OnTextChangedFlightform(LPCTSTR text);
	afx_msg void OnTextChangedGroupform(LPCTSTR text);
	afx_msg void OnButton1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnSelectTab(RDialog* tab);
	MSG2(OnSelectTab)	{OnSelectTab((RDialog*) a);return 0;}
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLT_TASK_H__A17844E1_CD70_11D1_A5A3_0040052179B6__INCLUDED_)
