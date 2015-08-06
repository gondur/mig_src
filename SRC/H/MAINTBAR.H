#if !defined(AFX_MAINTBAR_H__C13BD762_E594_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_MAINTBAR_H__C13BD762_E594_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MainTbar.h : header file
//
#include "RToolbar.h"

/////////////////////////////////////////////////////////////////////////////
// CMainToolbar dialog

class CMainToolbar : public CRToolBar
{
// Construction
public:
	CMainToolbar(CWnd* pParent = NULL);   // standard constructor
	enum	{	AUTHORISE,BASES,DIRECTIVES,RESULTS,OVERVIEW,
				PLAYERLOG,SQUADS,WEATHER,DIS,MISSIONS,
				DOSSIER,LOADPROF, ARMY, MAX_ID
			};

	void ChildDialClosed(int dialnum,RDialog*,int rv);
	static int dialids[MAX_ID];
	CRButton	m_dialids[MAX_ID];
	void CloseAllDialogs();

// Dialog Data
	//{{AFX_DATA(CMainToolbar)
	enum { IDD = IDD_MAINTOOLBAR };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_FRAG2;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainToolbar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
   void OpenDirectives(); 
   void OpenPlayerlog(); 
   void OpenSquads(int entry);
   void OpenDossier(UniqueID item);
   void OpenDossierNotFrontLine(UniqueID item); 
   void	OpenDis();
   void DialoguesVisible( bool vis);
   void OpenLoadProfile(int uid); 
   void LaunchPlayerLog(PosnControl x, PosnControl y);
   void LaunchOverview(PosnControl x, PosnControl y); 
	void OnClickedMissionlog();




	// Generated message map functions
	//{{AFX_MSG(CMainToolbar)
	afx_msg void OnClickedChangeToTitle();
	afx_msg void OnClickedAuthorise();
	afx_msg void OnClickedBases();
	afx_msg void OnClickedDirectives();
	afx_msg void OnClickedMissionresults();
	afx_msg void OnClickedOverview();
	afx_msg void OnClickedPlayerlog();
	afx_msg void OnClickedSquads();
	afx_msg void OnClickedWeather();
	afx_msg void OnClickedDis();
	afx_msg void OnClickedMissionFolder();
	afx_msg void OnClickedAuthorise11();
	afx_msg void OnClickedFrag2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
		  
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTBAR_H__C13BD762_E594_11D1_A1F0_0080C8582DE4__INCLUDED_)
