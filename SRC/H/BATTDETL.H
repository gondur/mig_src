#if !defined(AFX_BATTDETL_H__22E8D6E1_8B8D_11D2_9684_0000476073D8__INCLUDED_)
#define AFX_BATTDETL_H__22E8D6E1_8B8D_11D2_9684_0000476073D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BattDetl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBattleDetail dialog

class CBattleDetail : public RowanDialog
{
// Construction
public:
	CBattleDetail(UniqueID uid,UniqueID forceuid,int side,CWnd* pParent = NULL);   // standard constructor
	int u, forceu;
	int tabside;
	void ParentDialClosed(RDialog*,int rv);
	int	teams[BattleStruct::MAXTEAMS];
	int currrow;
	TeamDef::Team blueforce;
	SupplyNode*	node;
// Dialog Data
	//{{AFX_DATA(CBattleDetail)
	CRListBox  m_IDC_RLISTBOXTOP;
	CRListBox  m_IDC_RLISTBOXBTM;
	CRStatic	m_IDC_RSTATICCTRL2;
	CRStatic	m_IDC_RSTATICCTRL3;

	enum { IDD = IDD_BATTLEDETAIL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBattleDetail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillTopBox();
	void FillBtmBox();

	// Generated message map functions
	//{{AFX_MSG(CBattleDetail)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxtop(long row, long column);
	afx_msg void OnSelectRlistboxbtm(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG

	afx_msg	void	OnSelectTab();
	MSG2(OnSelectTab)	{OnSelectTab();return 0;}


	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATTDETL_H__22E8D6E1_8B8D_11D2_9684_0000476073D8__INCLUDED_)
