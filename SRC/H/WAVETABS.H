#if !defined(AFX_WAVETABS_H__AA4722E1_A786_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_WAVETABS_H__AA4722E1_A786_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WaveTabs.h : header file
//
class WaypointButtons;
class CWPShare;
class CWPGround;

/////////////////////////////////////////////////////////////////////////////
// CWaveTabs dialog

class CWaveTabs : public RowanDialog
{
// Construction
public:
	CWaveTabs(int pack,int wave,CWnd* pParent = NULL);   // standard constructor
	static bool m_launched;
	WaypointButtons* m_wpBut1;
	WaypointButtons* m_wpBut2;
	WaypointButtons* m_wpBut3;
	WaypointButtons* m_wpBut4;
	CWPShare* m_wp1;
	CWPGround* m_wp2;
	CWPGround* m_wp3;
	CWPGround* m_wp4;
	void	OnOK();
// Dialog Data
	//{{AFX_DATA(CWaveTabs)
	enum { IDD = IDD_WAVETABS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveTabs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWaveTabs)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClickedTitle();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnSelectTab(RDialog* tab);

	MSG2(OnSelectTab)	{OnSelectTab((RDialog*) a);return 0;}
	DECLARE_MESSAGE_MAP()

public:
	void	SelectTab(int group=-1);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVETABS_H__AA4722E1_A786_11D1_A1F0_444553540000__INCLUDED_)
