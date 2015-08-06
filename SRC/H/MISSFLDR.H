#if !defined(AFX_MISSFLDR_H__353A40A1_C003_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_MISSFLDR_H__353A40A1_C003_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MissFldr.h : header file
//
class	CProfile;
/////////////////////////////////////////////////////////////////////////////
// CMissionFolder dialog

class CMissionFolder : public RowanDialog
{
// Construction
public:
	CMissionFolder(CWnd* pParent = NULL);   // standard constructor
	static	RDialog*	MakeProper();
	static	void	Make();
	static  void		OpenOneProfile(int row); 
	void	FillFirst3Col(CRListBox* rlistbox,int i);

// Dialog Data
	//{{AFX_DATA(CMissionFolder)
	enum { IDD = IDD_MISSION_FOLDER };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_INTELLIGENCE;
	CRButton	m_IDC_PROFILE3;
	CRButton	m_IDC_FRAG;
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRButton	m_IDC_DELETEMISSION;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMissionFolder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	static RDialog* displayedprofs[Profile::MAX_PACKS];
	static CMissionFolder*	activedial;
	void	ChildDialClosed(int,RDialog*,int);
	void	RefreshData(int);
	void	EndDialog(int rv);
	int currrow;
	// Generated message map functions
	//{{AFX_MSG(CMissionFolder)
	afx_msg void OnProfile();
	afx_msg void OnClickedIntelligence();
	afx_msg void OnClickedFrag();
	afx_msg void OnClickedProfile();
	afx_msg void OnCancelMode();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedDeletemission();
	afx_msg void OnButton1();
	afx_msg void OnDestroy();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void	OpenProfile(int row) ;
	void	FillProfileRow(CRListBox* rlistbox,int i);
	void	ClearProfileRow(CRListBox* rlistbox,int i);
	void	RefreshLoggedChildren();

	void	FillListBox();
	void	ResetHiLight();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MISSFLDR_H__353A40A1_C003_11D1_A5A3_0040052179B6__INCLUDED_)
