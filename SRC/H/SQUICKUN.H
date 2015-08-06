#if !defined(AFX_SQUICKUN_H__C77A1F61_FB06_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SQUICKUN_H__C77A1F61_FB06_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SQuickUN.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSQuickLine dialog
struct	QuickFields;
class CSQuickLine : public RowanDialog
{
// Construction
public:
	CSQuickLine(int side,int wave,int group,CWnd* pParent = NULL);   // standard constructor
	void	SetIconPressed(bool turnon);
	QuickFields*	fields;
	void	RecalcFlightsCombo(int spares);
	void SetVariableBits(bool Icanbeplayer=true);

	int aclines[10];
// Dialog Data
	//{{AFX_DATA(CSQuickLine)
	enum { IDD = IDD_SQUICKSET };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_GRPDESC;
	CRCombo	m_IDC_FLIGHTS;
	CRCombo	m_IDC_TYPE;
	CRCombo	m_IDC_ALT;
	CRCombo	m_IDC_SKILL;
	CRButton	m_IDC_PILOTEDFLAG;
	CRStatic	m_IDC_RSTATICCTRL41;
	CRStatic	m_IDC_RSTATICCTRL42;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQuickLine)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSQuickLine)
	afx_msg void OnTextChangedType(LPCTSTR text);
	afx_msg void OnTextChangedSkill(LPCTSTR text);
	afx_msg void OnTextChangedFlights(LPCTSTR text);
	afx_msg void OnTextChangedAlt(LPCTSTR text);
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnClickedPilotedflag();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUICKUN_H__C77A1F61_FB06_11D1_A5A3_0040052179B6__INCLUDED_)
