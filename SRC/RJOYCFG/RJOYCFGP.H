#if !defined(AFX_RJOYCFGP_H__1B499F7A_C31E_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RJOYCFGP_H__1B499F7A_C31E_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RJoyCfgP.h : Declaration of the CRJoyCfgPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRJoyCfgPropPage : See RJoyCfgP.cpp.cpp for implementation.

class CRJoyCfgPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRJoyCfgPropPage)
	DECLARE_OLECREATE_EX(CRJoyCfgPropPage)

// Constructor
public:
	CRJoyCfgPropPage();

// Dialog Data
	//{{AFX_DATA(CRJoyCfgPropPage)
	enum { IDD = IDD_PROPPAGE_RJOYCFG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRJoyCfgPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RJOYCFGP_H__1B499F7A_C31E_11D1_A1F0_444553540000__INCLUDED)
