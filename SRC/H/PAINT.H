#if !defined(AFX_PAINT_H__27646163_0F61_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_PAINT_H__27646163_0F61_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Paint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaint dialog

class CPaint : public RowanDialog
{
// Construction
public:
	CPaint(int squadnum, int pilot,CWnd* pParent = NULL);   // standard constructor
	void ParentDialClosed(RDialog*,int rv);

// Dialog Data
	//{{AFX_DATA(CPaint)
	enum { IDD = IDD_PAINTSHOP };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_NOSEART_DEFAULT1;
	CRButton	m_IDC_NOSEART_DEFAULT2;
	CRButton	m_IDC_NOSEART_DEFAULT3;
	CRButton	m_IDC_NOSEART_DEFAULT4;
	CRButton	m_IDC_NOSEART_DEFAULT5;
	CRButton	m_IDC_NOSEART_DEFAULT6;
	CRButton	m_IDC_NOSEART_DEFAULT7;
	CRButton	m_IDC_NOSEART_DEFAULT8;
	CRButton	m_IDC_NOSEART_DEFAULT9;
	CRButton	m_IDC_NOSEART_DEFAULT10;
	CRButton	m_IDC_NOSEART_DEFAULT11;
	CRButton	m_IDC_NOSEART_DEFAULT12;
	CRButton	m_IDC_NOSEART_DEFAULT13;
	CRButton	m_IDC_NOSEART_DEFAULT14;
	CRButton	m_IDC_NOSEART_DEFAULT15;
	CRButton	m_IDC_NOSEART_DEFAULT16;
	CRRadio	m_IDC_RRADIO_NOSESELECT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int	decalsset;
	void CPaint::DrawDecals();
	void CPaint::SelectNoseArt(int art);


	// Generated message map functions
	//{{AFX_MSG(CPaint)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectedRradioNoseselect(long ButtonNum);
	afx_msg void OnClickedNoseartDefault1();
	afx_msg void OnClickedNoseartDefault10();
	afx_msg void OnClickedNoseartDefault11();
	afx_msg void OnClickedNoseartDefault12();
	afx_msg void OnClickedNoseartDefault13();
	afx_msg void OnClickedNoseartDefault14();
	afx_msg void OnClickedNoseartDefault15();
	afx_msg void OnClickedNoseartDefault16();
	afx_msg void OnClickedNoseartDefault2();
	afx_msg void OnClickedNoseartDefault3();
	afx_msg void OnClickedNoseartDefault4();
	afx_msg void OnClickedNoseartDefault5();
	afx_msg void OnClickedNoseartDefault6();
	afx_msg void OnClickedNoseartDefault7();
	afx_msg void OnClickedNoseartDefault8();
	afx_msg void OnClickedNoseartDefault9();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAINT_H__27646163_0F61_11D2_A5A3_0040052179B6__INCLUDED_)
