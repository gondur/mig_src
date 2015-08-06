#if !defined(AFX_SCAMP_H__CB7A5327_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SCAMP_H__CB7A5327_FA0F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SCamp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSCampaign dialog

class CSCampaign : public RowanDialog
{
// Construction
public:
	static int	SelCamp;
	CSCampaign(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSCampaign)
	enum { IDD = IDD_SCAMPAIGNSELECT };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLIST_CAMPAIGNS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCampaign)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSCampaign)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedPlayermessage1();
	afx_msg void OnClickedPlayermessage2();
	afx_msg void OnClickedPlayermessage3();
	afx_msg void OnClickedPlayermessage4();
	afx_msg void OnClickedPlayermessage5();
	afx_msg void OnSelectRlistCampaigns(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCAMP_H__CB7A5327_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
