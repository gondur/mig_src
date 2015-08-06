#if !defined(AFX_SQDNLBUT_H__025E4542_2F99_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_SQDNLBUT_H__025E4542_2F99_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SqdnLBut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSqdnlistBut dialog

class CSqdnlistBut : public RowanDialog
{
// Construction
public:
	CSqdnlistBut(int squad,CWnd* pParent = NULL);   // standard constructor
	void CSqdnlistBut::MakeNewPilot(int pilot);
	void CSqdnlistBut::KillPilot(int pilot, pilotstatus status);

// Dialog Data
	//{{AFX_DATA(CSqdnlistBut)
	enum { IDD = IDD_SQDNLIST_BUT };
	CEdit	m_IDCX_BINGOFUEL;
	CRStatic	m_IDC_RSTATICCTRL38;
	CRButton	m_IDC_PILOTLOSSES;
	CRCombo	m_IDC_ROTATEFREQ;
	CRStatic	m_IDC_RSTATICCTRL39;
	CRStatic	m_IDC_RSTATICCTRL60;
	CRStatic	m_IDC_AVAILACNUM;
	CREdit	m_IDC_BINGOFUEL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSqdnlistBut)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSqdnlistBut)
	afx_msg void OnClickedPilotlosses();
	afx_msg void OnTextChangedRotatefreq(LPCTSTR text);
	afx_msg void OnTextChangedFlighttactics(LPCTSTR text);
	afx_msg void OnTextChangedElementtactics(LPCTSTR text);
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedBingofuel(LPTSTR text);
	afx_msg void OnUpdateBingofuel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQDNLBUT_H__025E4542_2F99_11D2_9FD5_D0EC00C10000__INCLUDED_)
