#if !defined(AFX_LOCKER_H__B058C5C2_0CFE_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_LOCKER_H__B058C5C2_0CFE_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Locker.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLockerRoom dialog

class CLockerRoom : public RowanDialog
{
// Construction
public:
	CLockerRoom(CWnd* pParent = NULL);   // standard constructor

	char currquickmiss;

// Dialog Data
	//{{AFX_DATA(CLockerRoom)
	enum { IDD = IDD_LOCKERROOM };
	CEdit	m_IDCX_PLAYERCHAT;
	CEdit	m_IDCX_NAME;
	CEdit	m_IDCX_GAME_TITLE;
	CREdit	m_IDC_NAME;
	CRStatic	m_IDC_RSTATICCTRL3;
	CREdit	m_IDC_GAME_TITLE;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_RSTATICCTRL24;
	CRStatic	m_IDC_RSTATICCTRL6;
	CRRadio	m_IDC_RRADIO_GAMETYPE;
	CRRadio	m_IDC_RRADIO_SELECTSIDE;
	CRStatic	m_IDC_RSTATICCTRL7;
	CREdit	m_IDC_PLAYERCHAT;
	CRStatic	m_IDC_RSTATICCTRL26;
	CRStatic	m_IDC_GRPDESC;
	CRButton	m_IDC_PILOTEDFLAG;
	CRCombo	m_IDC_GAME_TITLECOMBO;
	CRCombo	m_IDC_DATARATE;
	CRStatic	m_IDC_SCENARIO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLockerRoom)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpDateDPlay();
	
	void RedrawSide();
	void RedrawCombo();

	// Generated message map functions
	//{{AFX_MSG(CLockerRoom)
	afx_msg void OnClickedVisitors();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSelectedRradioGametype(long ButtonNum);
	afx_msg void OnClickedPilotedflag();
	afx_msg void OnTextChangedName(LPTSTR text);
	afx_msg void OnTextChangedGameTitle(LPTSTR text);
	afx_msg void OnTextChangedPlayerchat(LPTSTR text);
	afx_msg void OnUpdateGameTitle();
	afx_msg void OnUpdateName();
	afx_msg void OnUpdatePlayerchat();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCKER_H__B058C5C2_0CFE_11D2_A5A3_0040052179B6__INCLUDED_)
