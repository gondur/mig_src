#if !defined(AFX_RSTATICP_H__C42BAC4C_CA3C_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RSTATICP_H__C42BAC4C_CA3C_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RStaticP.h : Declaration of the CRStaticPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRStaticPropPage : See RStaticP.cpp.cpp for implementation.

class CRStaticPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRStaticPropPage)
	DECLARE_OLECREATE_EX(CRStaticPropPage)

// Constructor
public:
	CRStaticPropPage();

// Dialog Data
	//{{AFX_DATA(CRStaticPropPage)
	enum { IDD = IDD_PROPPAGE_RSTATIC };
	long	m_FontNum;
	BOOL	m_UpdateCaption;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRStaticPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSTATICP_H__C42BAC4C_CA3C_11D1_A1F0_444553540000__INCLUDED)
