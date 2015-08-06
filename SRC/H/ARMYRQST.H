#if !defined(AFX_ARMYRQST_H__E1CC3EC3_D392_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_ARMYRQST_H__E1CC3EC3_D392_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Armyrqst.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArmyRequests dialog
//BLUE
class CArmyRequests : public RowanDialog
{
// Construction
public:
	CArmyRequests(CWnd* pParent = NULL);   // standard constructor
	static	CArmyRequests* MakeSheet(CRect r,UniqueID item,UniqueID  force);
	void  ParentDialClosed(RDialog*,int rv);

	void	TabSelect(int side);

// Dialog Data
	//{{AFX_DATA(CArmyRequests)
	enum { IDD = IDD_ARMYREQUESTS };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRListBox	m_IDC_RLISTBOXCTRL2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArmyRequests)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArmyRequests)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARMYRQST_H__E1CC3EC3_D392_11D1_A5A3_0040052179B6__INCLUDED_)
