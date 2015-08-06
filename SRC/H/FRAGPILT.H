#if !defined(AFX_FRAGPILT_H__035ACCE1_100C_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_FRAGPILT_H__035ACCE1_100C_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FragPilt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFragPilot dialog

class CFragPilot : public RowanDialog
{
// Construction
public:
	CFragPilot(int*pack,CWnd* pParent = NULL);   // standard constructor
	int squadnum,squadflight;
	void	PrintPilotNames();									//AMM 17Nov98
// Dialog Data
	//{{AFX_DATA(CFragPilot)
	enum { IDD = IDD_FRAGPILT };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_FRAG_ROLE;
	CRStatic	m_IDC_FRAG_ID;
	CRStatic	m_IDC_FRAG_WAVE;
	CRCombo	m_IDC_FRAG_CALLNAME;
	CREdtBt	m_IDC_PLAYERCHAT;
	CREdtBt	m_IDC_PLAYERCHAT2;
	CREdtBt	m_IDC_PLAYERCHAT3;
	CREdtBt	m_IDC_PLAYERCHAT4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFragPilot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	EndDialog( int nResult );
//	bool	beenselected;
	void	FillComboBox();
	BOOL	UniqueCallNameOrThisGroups(char callname);
	void	FindCallName(char index);
	void	OnClickedPlayer(int acinflight);
//DeadCode AMM 17Nov98 	void	PrintPilotNames();
	bool	CommsPlayer(int pos, int& i);



	// Generated message map functions
	//{{AFX_MSG(CFragPilot)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedFragCallname(LPCTSTR text);
	afx_msg void OnClickedPlayerchat();
	afx_msg void OnClickedPlayerchat3();
	afx_msg void OnClickedPlayerchat2();
	afx_msg void OnClickedPlayerchat4();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAGPILT_H__035ACCE1_100C_11D2_A5A3_0040052179B6__INCLUDED_)
