#if !defined(AFX_TITLEBAR_H__891B54A3_4D5E_11D2_83A5_00004760763D__INCLUDED_)
#define AFX_TITLEBAR_H__891B54A3_4D5E_11D2_83A5_00004760763D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TitleBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TitleBar dialog

class TitleBar : public CRToolBar
{
// Construction
public:
	TitleBar(CWnd* pParent = NULL);   // standard constructor
	void Redraw();
	int m_xoffset;
	int m_yoffset;

// Dialog Data
	//{{AFX_DATA(TitleBar)
	enum { IDD = IDD_TITLEBAR };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_TITLE;
	CRButton	m_IDC_DATE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TitleBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TitleBar)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg FileNum OnGetArt();
	afx_msg long OnGetXYOffset();
	afx_msg CFont* OnGetGlobalFont(int fontnum);
	afx_msg BYTE* OnGetFile(int filenum);
	afx_msg void OnReleaseLastFile();
	afx_msg BOOL OnGetX2Flag();
	MSG2_0(OnGetArt);
	MSG2_0(OnGetXYOffset);
	MSG2_1(OnGetGlobalFont);
//	MSG2_1(OnGetFile);
//	MSG2_0v(OnReleaseLastFile);
//	MSG2_0(OnGetX2Flag);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITLEBAR_H__891B54A3_4D5E_11D2_83A5_00004760763D__INCLUDED_)
