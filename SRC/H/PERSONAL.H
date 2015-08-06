#if !defined(AFX_PERSONAL_H__D1105581_0B55_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_PERSONAL_H__D1105581_0B55_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// personal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPilotsPersonalDetails dialog

class CPilotsPersonalDetails : public RowanDialog
{
// Construction
public:
	CPilotsPersonalDetails(int squadnum, int pilot, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPilotsPersonalDetails)
	enum { IDD = IDD_PILOT_PERSONAL_DETAILS };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_NAME_PILOT1;
	CRListBox	m_IDC_RLIST_DETAILS_PILOT1;
	CRStatic	m_IDC_NAME_PILOT2;
	CRListBox	m_IDC_RLIST_DETAILS_PILOT2;
	CRListBox	m_IDC_RLIST_DETAILS_PILOT3;
	CRListBox	m_IDC_RLIST_DETAILS_PILOT4;
	CRStatic	m_IDC_NAME_PILOT3;
	CRStatic	m_IDC_NAME_PILOT4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPilotsPersonalDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	DrawOnePilotDetail(CRStatic&	m_name, CRListBox& m_listbox, int i, int baseac);
	bool	CommsPlayer(int pos, int& i);

	// Generated message map functions
	//{{AFX_MSG(CPilotsPersonalDetails)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONAL_H__D1105581_0B55_11D2_A5A3_0040052179B6__INCLUDED_)
