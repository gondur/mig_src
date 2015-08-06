#if !defined(AFX_DBRFTLBR_H__D5BD95A1_4D5B_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_DBRFTLBR_H__D5BD95A1_4D5B_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DbrfTlbr.h : header file
//
#include "rtoolbar.h"

/////////////////////////////////////////////////////////////////////////////
// CDebriefToolbar dialog

class CDebriefToolbar : public CRToolBar
{
// Construction
public:
	CDebriefToolbar(CWnd* pParent = NULL);   // standard constructor
	void OpenMissionresults();
	void ChildDialClosed(int dialnum,RDialog*,int rv);

// Dialog Data
	//{{AFX_DATA(CDebriefToolbar)
	enum { IDD = IDD_DEBRIEFTOOLBAR };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_DIS;
	CRButton	m_IDC_PLAYERLOG;
	CRButton	m_IDC_OVERVIEW;
	CRButton	m_IDC_MISSIONRESULTS;
	CRButton	m_IDC_BORDER3;
	CRButton	m_IDC_NEXT_PERIOD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDebriefToolbar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
//protected:
public:

	// Generated message map functions
	//{{AFX_MSG(CDebriefToolbar)
	afx_msg void OnClickedMissionresults();
	afx_msg void OnClickedPlayerlog();
	afx_msg void OnClickedDis();
	afx_msg void OnClickedNextPeriod();
	afx_msg void OnClickedOverview();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBRFTLBR_H__D5BD95A1_4D5B_11D2_9FD5_D0EC00C10000__INCLUDED_)
