#if !defined(AFX_PROFILE_H__353A40A3_C003_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_PROFILE_H__353A40A3_C003_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000	   m
// Profile.h : header file
//
//#include "TStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CProfile dialog
class	CWaveTabs;
class	CTaskTabs;
class CProfile : public RowanDialog
{
// Construction
public:
	CProfile(bool enable, int	package,CWnd* pParent = NULL);   // standard constructor
//	CTransparentStatic m_statics[3];
	int	currrow;
	int currcol;
	int maxrows;
	int insertedwav;	//remember the wave that we offer to insert for the user 
	bool enableinput;
static 	CWaveTabs*	wavetabs;
// Dialog Data
	//{{AFX_DATA(CProfile)
	enum { IDD = IDD_PROFILE };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRButton	m_IDC_INSERTWAVENEW;
	CRButton	m_IDC_DELETEWAVENEW;
	CRButton	m_IDC_TASK;
	CRButton	m_IDC_ROUTE;
	CRButton	m_IDC_SAVE;	
	CRButton	m_IDJ_TITLE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void EndDialog( int nResult );
	// Generated message map functions
	//{{AFX_MSG(CProfile)
	afx_msg void OnClickedProfile();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnClickedInsertwave();
	afx_msg void OnOKDeletewave();
	afx_msg void OnClickedDeletewave();
	afx_msg void OnClickedDeletewavenew();
	afx_msg void OnClickedInsertwavenew();
	afx_msg void OnClickedObjective();
	afx_msg void OnClickedCentre();
	afx_msg void OnClickedSave();
	afx_msg void OnClickedTask();
	afx_msg void OnClickedRoute();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void	FillWaveRow(int wave);
	void	ClearWaveRow(int wave);
static 	CTaskTabs*	tasktabs;
static	int	wavepack,wavegroup;
	int		tabswave;
	void	ChildDialClosed(int,RDialog* r,int code);
	void	RefreshData(int);
	void	MakeWaveTabs(int wave,int group,int x=500,int y=100);
	void	MakeTaskTabs(int wave,int x=500,int y=100);

public:
	void	SetWaveTabs(int wave,int group=-1);
	void	SetTaskTabs(int wave,int group);
	void	ReDraw();


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILE_H__353A40A3_C003_11D1_A5A3_0040052179B6__INCLUDED_)
