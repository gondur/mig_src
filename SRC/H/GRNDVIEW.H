#if !defined(AFX_GRNDVIEW_H__C75E68C7_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_GRNDVIEW_H__C75E68C7_CF0E_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Grndview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrndview dialog

class CGrndview : public RowanDialog
{
// Construction
public:
	CGrndview(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrndview)
	enum { IDD = IDD_GROUNDVIEW };
		// NOTE: the ClassWizard will add data members here
	CRRadio	m_IDC_RRADIO_FILTER;
	CRListBox	m_IDC_RLIST_GRNDKILL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrndview)
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
	//{{AFX_MSG(CGrndview)
	afx_msg void OnCancelMode();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectedRradioFilter(long ButtonNum);
	afx_msg void OnSelectRlistGrndkills(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRNDVIEW_H__C75E68C7_CF0E_11D1_A5A3_0040052179B6__INCLUDED_)
