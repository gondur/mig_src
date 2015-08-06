#if !defined(AFX_AC_VIEW_H__C75E68C6_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_AC_VIEW_H__C75E68C6_CF0E_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AC_view.h : header file
//
#include "Debrief.h"


/////////////////////////////////////////////////////////////////////////////
// CAC_view dialog

class CAC_view : public RowanDialog
{
// Construction
public:
	CAC_view(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CAC_view)
	enum { IDD = IDD_AC_OVERVIEW };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLIST_UNLOSSES;
	CRListBox	m_IDC_RLIST_UNCLAIMS;
	CRRadio	m_IDC_RRADIO_FILTER;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_RSTATICCTRL4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAC_view)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void	ReDrawPanel();
	void	ReDrawHeadings();
	void	RedrawTables(Debrief::SquadKills period);
	void	ReDrawRadioButtons();

	// Generated message map functions
	//{{AFX_MSG(CAC_view)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectedRradioFilter(long ButtonNum);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AC_VIEW_H__C75E68C6_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
