#if !defined(AFX_REDITPPG_H__499E2BF5_AC32_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_REDITPPG_H__499E2BF5_AC32_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// REditPpg.h : Declaration of the CREditPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CREditPropPage : See REditPpg.cpp.cpp for implementation.

class CREditPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CREditPropPage)
	DECLARE_OLECREATE_EX(CREditPropPage)

// Constructor
public:
	CREditPropPage();

// Dialog Data
	//{{AFX_DATA(CREditPropPage)
	enum { IDD = IDD_PROPPAGE_REDIT };
	long	m_FontNum;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CREditPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDITPPG_H__499E2BF5_AC32_11D1_A1F0_444553540000__INCLUDED)
