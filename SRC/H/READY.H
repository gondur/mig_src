#if !defined(AFX_READY_H__B058C5C1_0CFE_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_READY_H__B058C5C1_0CFE_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Ready.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReadyRoom dialog

class CReadyRoom : public RowanDialog
{
// Construction
public:
	UINT rroom_timer;
	CReadyRoom(CWnd* pParent = NULL);   // standard constructor
	void	OnOK();
// Dialog Data
	//{{AFX_DATA(CReadyRoom)
	enum { IDD = IDD_READYROOM };
	CEdit	m_IDCX_PLAYERCHAT;
	CRListBox	m_IDC_RLIST_UN_PLAYER;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRListBox	m_IDC_RLIST_INCOMING_CHAT;
	CREdit	m_IDC_PLAYERCHAT;
	CRRadio	m_IDC_RRADIO_DETAILS;
	CRStatic	m_IDC_GAMENAME;
	CRStatic	m_IDC_RSTATICCTRL24;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadyRoom)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RedrawRadioButtons();


	// Generated message map functions
	//{{AFX_MSG(CReadyRoom)
	virtual BOOL OnInitDialog();
	afx_msg void OnReturnPressedPlayerchat(LPCTSTR text);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSelectedRradioDetails(long ButtonNum);
	afx_msg void OnSelectRlistUnPlayer(long row, long column);
	afx_msg void OnTextChangedPlayerchat(LPTSTR text);
	afx_msg void OnUpdatePlayerchat();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READY_H__B058C5C1_0CFE_11D2_A5A3_0040052179B6__INCLUDED_)
