#if !defined(AFX_WPSHARE_H__ED6BD581_CD50_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_WPSHARE_H__ED6BD581_CD50_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WPShare.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWPShare dialog

class CWPShare : public RowanDialog
{  
	enum	{widecol=150,thincol=3};
	enum	{L_POSITION,L_ALTITUDE,L_ETAREL,L_ETA,FUELLEFT, AAAFUEL, ESCORTFUEL};
	int comboindex;
// Construction
public:
	CWPShare(int pack,int wave,int group,CWnd* pParent = NULL);   // standard constructor
	RowanDialog	*wpdetail,*wpbuttons;
	void	RefreshDetail(UniqueID u);
	void	OnSelectTab(RDialog* tab);
	MSG2(OnSelectTab)	{OnSelectTab((RDialog*) a);return 0;}
	void FillComboBox();
	enum	{INSONDELON,INSONDELOFF,INSOFFDELOFF,INSOFFDELON};
	enum	{RADIOLIST,RADIODETAIL, RADIOENABLE, RADIODISABLE};
	void	RefreshButtons(int effect);
	void	SetButtons(long row);


// Dialog Data
	//{{AFX_DATA(CWPShare)
	enum { IDD = IDD_WPSHARED };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_WAYPOINTLIST;
	CRCombo	m_IDC_TYPE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWPShare)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	int	currrow,currcol;
	enum	{LISTMAXSIZE=33};
	UniqueID	listentries[LISTMAXSIZE+2];
	bool		listfull;
// Implementation
protected:
	void	DisplayData();
//	void	AddRoute();
	void	RefreshData(int childnum);
	// Generated message map functions
	//{{AFX_MSG(CWPShare)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelectWaypointlist(long row, long column);
	afx_msg void OnDestroy();
	afx_msg void OnTextChangedType(LPCTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnDelete();
	afx_msg void OnDetail();
	afx_msg void OnInsert();
	afx_msg void OnMove();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPSHARE_H__ED6BD581_CD50_11D1_A5A3_0040052179B6__INCLUDED_)
