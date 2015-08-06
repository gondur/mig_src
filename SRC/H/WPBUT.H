#if !defined(AFX_WPBUT_H__E395BAA1_118C_11D2_9FD6_D0EC00C10000__INCLUDED_)
#define AFX_WPBUT_H__E395BAA1_118C_11D2_9FD6_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WPBut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WaypointButtons dialog

class WaypointButtons : public RowanDialog
{
// Construction
public:
	WaypointButtons(CWnd* pParent = NULL);   // standard constructor
	void	RefreshData(int);
// Dialog Data
	//{{AFX_DATA(WaypointButtons)
	enum { IDD = IDD_WPBUTTONS };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_INSERT;
	CRButton	m_IDC_DELETE;
	CRButton	m_IDC_MOVE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WaypointButtons)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
void FireMessageToSibling(int buttonID,int eventid);
protected:

	// Generated message map functions
	//{{AFX_MSG(WaypointButtons)
	afx_msg void OnClickedMove();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnClicked(int);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPBUT_H__E395BAA1_118C_11D2_9FD6_D0EC00C10000__INCLUDED_)
