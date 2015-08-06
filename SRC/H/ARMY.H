#if !defined(AFX_ARMY_H__7CC731A4_CA3D_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_ARMY_H__7CC731A4_CA3D_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Army.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArmy dialog

class CArmy : public RowanDialog
{
// Construction
public:
	CArmy(int index,CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CArmy)
	enum { IDD = IDD_ARMY };
		// NOTE: the ClassWizard will add data members here
	CRRadio	 m_IDC_RRADIO_FRONT;
	CRButton	m_IDC_AUTHORISE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArmy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArmy)
	afx_msg void OnClickedAuthorise();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectedRradioFront(long ButtonNum);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARMY_H__7CC731A4_CA3D_11D1_A5A3_0040052179B6__INCLUDED_)
