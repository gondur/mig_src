#if !defined(AFX_PAYLOAD_H__C378D722_C24A_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_PAYLOAD_H__C378D722_C24A_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Payload.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPayload dialog

class CPayload : public RowanDialog
{
// Construction
public:
	CPayload(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPayload)
	enum { IDD = IDD_PAYLOAD };
	CRListBox	m_IDC_WEAPLIST;
	CRStatic	m_IDC_TSQUAD;
	CRStatic	m_IDC_TSQUAD2;
	CRStatic	m_IDC_TSQUAD3;
	CRStatic	m_IDC_TSQUAD4;
	CRStatic	m_IDC_TSQUAD5;
	CRStatic	m_IDC_TSQUAD6;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_RSTATICCTRL4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPayload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPayload)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAYLOAD_H__C378D722_C24A_11D1_A5A3_0040052179B6__INCLUDED_)
