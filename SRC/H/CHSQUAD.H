#if !defined(AFX_CHSQUAD_H__580D0A83_220B_11D2_9FD6_D0EC00C10000__INCLUDED_)
#define AFX_CHSQUAD_H__580D0A83_220B_11D2_9FD6_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChSquad.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ChooseSquad dialog

class ChooseSquad : public RowanDialog
{
// Construction
public:
	ChooseSquad(int pack,int wave,int group,CWnd* pParent = NULL);   // standard constructor

	int initialsquad;
	int initialac;
	int currrow;

// Dialog Data
	//{{AFX_DATA(ChooseSquad)
	enum { IDD = IDD_CHOOSESQUAD };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_TSQUAD;
//	CRCombo	m_IDC_FLIGHTS;
	CRSpinBut m_IDC_RSPINBUTCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ChooseSquad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillCombo();
	int	 FlightAvail(int squad);
	void	ParentDialClosed(RDialog*,int rv);
	void OnOK( );
	void OnCancel( );
	// Generated message map functions
	//{{AFX_MSG(ChooseSquad)
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnClickedDelete();
	afx_msg void OnTextChangedFlights(LPCTSTR text);
	virtual BOOL OnInitDialog();
//DEADCODE DAW 29/03/99 	afx_msg void OnOKTitle();
//DEADCODE DAW 29/03/99 	afx_msg void OnCancelTitle();
	afx_msg void OnTextChangedRspinbutctrl1(LPCTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHSQUAD_H__580D0A83_220B_11D2_9FD6_D0EC00C10000__INCLUDED_)
