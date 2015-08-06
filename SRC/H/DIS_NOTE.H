#if !defined(AFX_DIS_NOTE_H__D5E07E81_0C42_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_DIS_NOTE_H__D5E07E81_0C42_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dis_Note.h : header file	  DebugLineStats
//

/////////////////////////////////////////////////////////////////////////////
// CDis_Note dialog

class CDis_Note : public RowanDialog
{
// Construction
public:
	CDis_Note(int text,CWnd* pParent = NULL);   // standard constructor
 	int idtext;
	void  ParentDialClosed(RDialog*,int rv);

// Dialog Data
	//{{AFX_DATA(CDis_Note)
	enum { IDD = IDD_DISNOTES };
	CRStatic	m_IDC_DISNOTES;
	CRStatic	m_IDC_DISNOTES2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDis_Note)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDis_Note)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIS_NOTE_H__D5E07E81_0C42_11D2_A5A3_0040052179B6__INCLUDED_)
