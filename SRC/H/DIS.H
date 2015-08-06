#if !defined(AFX_DIS_H__48476DC1_CE19_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_DIS_H__48476DC1_CE19_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DIS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDIS dialog

class CDIS : public RowanDialog
{
// Construction
public:
	CDIS(CWnd* pParent = NULL);   // standard constructor

	static char intelltime;
	enum	{DAY, ALL};
	char intelltype;
	enum	{TARGET, GENERAL};
	static SByte	currhilight;
	int currindex;;



SupplyTree::DisSmacker	dissmackers[MAXDIRECTIVES];


// Dialog Data
	//{{AFX_DATA(CDIS)
	enum { IDD = IDD_DIS };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRButton	m_IDC_VIEWNOTES;
	CRButton	m_IDC_VIEWFOOTAGE;
	CRRadio	m_IDC_RRADIO_INTELLTYPE;
	CRRadio	m_IDC_RRADIO_INTELLTIME;
	CRButton	m_IDC_INTELLIGENCE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	Redraw();
	void	RedrawList(Debrief::DisLog* dislog, int size);
	int		FindText();
	FileNum	FindSmacker();
	void	ResetHiLight();
	void	ReCalcHiLight();
	void	HiLightLast(Debrief::DisLog* dislog, int size);






	// Generated message map functions
	//{{AFX_MSG(CDIS)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedViewnotes();
	afx_msg void OnSelectedRradioIntelltime(long ButtonNum);
	afx_msg void OnSelectedRradioIntelltype(long ButtonNum);
	afx_msg void OnClickedViewfootage();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnClickedIntelligence();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIS_H__48476DC1_CE19_11D1_A5A3_0040052179B6__INCLUDED_)
