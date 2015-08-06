#if !defined(AFX_DIRECTS2_H__6ECCAEA2_3DD2_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_DIRECTS2_H__6ECCAEA2_3DD2_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Directs2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirects2 dialog

class CDirects2 : public RowanDialog
{
// Construction
public:
	CDirects2(int line,CWnd* pParent = NULL);   // standard constructor
	int	linenum;

// Dialog Data
	//{{AFX_DATA(CDirects2)
	enum { IDD = IDD_DIRECTS2 };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_TARGETS;
	CRStatic	m_IDC_MISSIONS;
	CRCombo	m_IDC_COMBO_STRIKEAC;
	CRCombo	m_IDC_COMBO_FIGHTERAC;
	CREdtBt	m_IDC_DIRECTIVEBUTTON;
	CRStatic	m_IDC_BLANK2;
	CRStatic	m_IDC_RESTING;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirects2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
//	void RedrawAll();

// Implementation
public:
	void Redraw();
	
protected:
	void ResetStrikeAc();
	void ResetFighterAc();


	// Generated message map functions
	//{{AFX_MSG(CDirects2)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedComboStrikeac(LPCTSTR text);
	afx_msg void OnTextChangedComboFighterac(LPCTSTR text);
	afx_msg void OnClickedDirectivebutton();
	afx_msg void OnCanAcceptDropDirectivebutton(long sourcedropID, BOOL FAR* pReply);
	afx_msg void OnDroppedOnDirectivebutton(long sourcedropID);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTS2_H__6ECCAEA2_3DD2_11D2_9FD5_D0EC00C10000__INCLUDED_)
