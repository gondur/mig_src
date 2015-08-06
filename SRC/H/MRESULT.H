#if !defined(AFX_MRESULT_H__44ED4981_CFCA_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_MRESULT_H__44ED4981_CFCA_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MResult.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMResult dialog

class CMResult : public RowanDialog
{
// Construction
public:
	CMResult(CWnd* pParent = NULL);   // standard constructor

	int currhilight;
// Dialog Data
	//{{AFX_DATA(CMResult)
	enum { IDD = IDD_RESULTS };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRButton	m_IDC_PROFILE;
	CRButton	m_IDC_DEBRIEF;
	CRButton	m_IDC_REPEAT;
	CRButton	m_IDC_NEXTPERIOD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMResult)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Redraw();
	void FillProfileRow(CRListBox* rlistbox,int i);
	void FillListBox(CRListBox* rlistbox);
	void ResetHiLight();


	// Generated message map functions
	//{{AFX_MSG(CMResult)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedNextperiod();
	afx_msg void OnClickedRepeat();
	afx_msg void OnClickedProfile();
	afx_msg void OnClickedDebrief();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void EndDialog(int v);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRESULT_H__44ED4981_CFCA_11D1_A5A3_0040052179B6__INCLUDED_)
