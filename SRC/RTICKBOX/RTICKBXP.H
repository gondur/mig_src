#if !defined(AFX_RTICKBXP_H__840ED4B6_CF9B_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RTICKBXP_H__840ED4B6_CF9B_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RTickBxP.h : Declaration of the CRTickBoxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRTickBoxPropPage : See RTickBxP.cpp.cpp for implementation.

class CRTickBoxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRTickBoxPropPage)
	DECLARE_OLECREATE_EX(CRTickBoxPropPage)

// Constructor
public:
	CRTickBoxPropPage();

// Dialog Data
	//{{AFX_DATA(CRTickBoxPropPage)
	enum { IDD = IDD_PROPPAGE_RTICKBOX };
	long	m_FontNum;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRTickBoxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTICKBXP_H__840ED4B6_CF9B_11D1_A1F0_0080C8582DE4__INCLUDED)
