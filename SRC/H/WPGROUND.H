#if !defined(AFX_WPGROUND_H__ED6BD582_CD50_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_WPGROUND_H__ED6BD582_CD50_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WPGround.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWPGround dialog

class CWPGround : public RowanDialog
{
	enum	{widecol=150,thincol=3};

// Construction
public:
	CWPGround(int pack,int wave,int group,CWnd* pParent = NULL);   // standard constructor
	~CWPGround();
	RowanDialog* wpdetail,*wpbuttons;
	void RefreshDetail(UniqueID u);
	int comboindex, levelindex;
 	enum	{L_POSITION,L_ALTITUDE,L_ETAREL,L_ETA,FUELLEFT};

// Dialog Data
	//{{AFX_DATA(CWPGround)
	enum { IDD = IDD_WPGROUND };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_WAYPOINTLIST;
	CRCombo	m_IDC_TYPE;
	CRCombo	m_IDC_LEVEL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWPGround)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	void	AddRoute();
	void	SetButtons(long row);
	void	RefreshButtons(int effect);

	int currrow;
	enum	{LISTFULLSIZE=30,MAXLISTSIZE=40};
	bool	listfull;
	UniqueID*	tablewp;
//DEADCODE JIM 03/06/99 	UniqueID	tablewp[MAXLISTSIZE];
	enum	TableType{MAINROUTE=-3,HEADER=-2,TITLE=-1,BEFORE=0,ATTACK1,BETWEEN,ATTACK2,AFTER,POSTRV};
//DEADCODE JIM 03/06/99 	TableType
//DEADCODE JIM 03/06/99 			tabletype[MAXLISTSIZE];
	TableType*	tabletype;
	UniqueID keys[6];
	void	DescribeTargetRoute();
	void	Describeonewp(CRListBox* listbox,UniqueID u,TableType t,int row,char letter);
	int		groupingmode;
	void	RefreshData(int childnum);
	// Generated message map functions
	//{{AFX_MSG(CWPGround)
	afx_msg void OnSelectWaypointlist(long row, long column);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTextChangedType(LPCTSTR text);
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedLevel(LPCTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnDelete();
	afx_msg void OnDetail();
	afx_msg void OnInsert();
	afx_msg void OnMove();
	afx_msg void OnSelectTab(RDialog* tab);
	MSG2(OnSelectTab)	{OnSelectTab((RDialog*) a);return 0;}
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPGROUND_H__ED6BD582_CD50_11D1_A5A3_0040052179B6__INCLUDED_)
