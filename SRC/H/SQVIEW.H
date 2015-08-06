#if !defined(AFX_SQVIEW_H__9F450AC1_56E4_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_SQVIEW_H__9F450AC1_56E4_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SQView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuickView dialog

class CQuickView : public RowanDialog
{
// Construction
public:
	CQuickView(CWnd* pParent = NULL);   // standard constructor
	int	targtype,targentry;
// Dialog Data
	//{{AFX_DATA(CQuickView)
	enum { IDD = IDD_QUICKVIEW };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	CRStatic	m_IDC_SDETAIL2;
	CRStatic	m_IDC_RSTATICCTRL24;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_RSTATICCTRL26;
	CRStatic	m_IDC_RSTATICCTRL36;
	CRStatic	m_IDC_RSTATICCTRL38;
	CRStatic	m_IDC_RSTATICCTRL39;
	CRStatic	m_IDC_RSTATICCTRL41;
	CRStatic	m_IDC_RSTATICCTRL42;
	CRStatic	m_IDC_RSTATICCTRL40;
	CRStatic	m_IDC_RSTATICCTRL43;
	CRStatic	m_IDC_RSTATICCTRL44;
	CRStatic	m_IDC_RSTATICCTRL45;
	CRStatic	m_IDC_CURRMISS;
	CRStatic	m_IDC_CLOUD;
	CRStatic	m_IDC_WEATHER;
	CRStatic	m_IDC_TARGTYPE;
	CRStatic	m_IDC_TARGNAME;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuickView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQuickView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQVIEW_H__9F450AC1_56E4_11D2_9FD5_D0EC00C10000__INCLUDED_)
