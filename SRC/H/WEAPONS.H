#if !defined(AFX_WEAPONS_H__337EE8A1_11DF_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_WEAPONS_H__337EE8A1_11DF_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Weapons.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWeapons dialog
struct	lchpak;
class CWeapons : public RowanDialog
{
// Construction
	static lchpak*	CWeapons::GetWeapList(int pack,int wave,int grp,int flight);
	static int		CWeapons::GetWeapIndex(int pack,int wave,int grp,int flight);

public:
	CWeapons(int pack,int wave,int grp,int flight,CWnd* pParent = NULL);   // standard constructor
	lchpak*	thisacweaps;
	bool		currgotfuel;
	static int		CWeapons::GetWeapName(int pack,int wave,int grp,int flight);
 	static	int		CWeapons::GetExtFuel(int pack,int wave,int grp,int flight);



// Dialog Data
	//{{AFX_DATA(CWeapons)
	enum { IDD = IDD_PAYLOAD };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_WEAPLIST;
	CRStatic	m_IDC_TSQUAD; 
	CRStatic	m_IDC_TSQUAD2;
	CRStatic	m_IDC_TSQUAD3;
 	CRButton	m_IDJ_TITLE;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeapons)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	ParentDialClosed(RDialog*,int rv);

	// Generated message map functions
	//{{AFX_MSG(CWeapons)
	afx_msg void OnSelectWeaplist(long row, long column);
	DECLARE_EVENTSINK_MAP()
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void	OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEAPONS_H__337EE8A1_11DF_11D2_A5A3_0040052179B6__INCLUDED_)
