#if !defined(AFX_RMDLDLG_H__8ADE6461_6818_11D2_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RMDLDLG_H__8ADE6461_6818_11D2_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RMdlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RMdlDlg dialog

#include "globdefs.h"
#include "files.g"
class fileblock;

class RMdlDlg : public CDialog
{
// Construction
public:
	RMdlDlg(CWnd* pParent = NULL);   // standard constructor
	FileNum m_artnum;
	fileblock* m_pfileblock;
	UINT m_TitleID;
	UINT m_MessageID;
	UINT m_Button0ID;
	UINT m_Button1ID;
	UINT m_Button2ID;
	CPoint m_point;
	BOOL m_lbuttondown;

// Dialog Data
	//{{AFX_DATA(RMdlDlg)
	enum { IDD = IDD_MODAL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDJ_TITLE;
	CRButton	m_IDC_OK;
	CRButton	m_IDC_CANCEL;
	CRButton	m_IDC_RETRY;
	CRStatic	m_IDC_MESSAGE_TEXT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RMdlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RMdlDlg)
	afx_msg void OnClickedOk();
	afx_msg void OnClickedRetry();
	afx_msg void OnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg FileNum OnGetArt();
	afx_msg long OnGetXYOffset();
	afx_msg CFont* OnGetGlobalFont(int fontnum);
	afx_msg BYTE* OnGetFile(int filenum);
	afx_msg void OnReleaseLastFile();
	afx_msg CDC* OnGetOffScreenDC();
	afx_msg CHintBox* OnGetHintBox();
	MSG2_0(OnGetArt);
	MSG2_0(OnGetXYOffset);
	MSG2_1(OnGetGlobalFont);
	MSG2_1(OnGetFile);
	MSG2_0v(OnReleaseLastFile);
	MSG2_0(OnGetOffScreenDC);
	MSG2_0(OnGetHintBox);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMDLDLG_H__8ADE6461_6818_11D2_A1F0_0080C8582DE4__INCLUDED_)
