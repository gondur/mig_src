#if !defined(AFX_RSCRLBARPPG_H__505AEE55_6A66_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RSCRLBARPPG_H__505AEE55_6A66_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RScrlBarPpg.h : Declaration of the CRScrlBarPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRScrlBarPropPage : See RScrlBarPpg.cpp.cpp for implementation.

class CRScrlBarPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRScrlBarPropPage)
	DECLARE_OLECREATE_EX(CRScrlBarPropPage)

// Constructor
public:
	CRScrlBarPropPage();

// Dialog Data
	//{{AFX_DATA(CRScrlBarPropPage)
	enum { IDD = IDD_PROPPAGE_RSCRLBAR };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRScrlBarPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSCRLBARPPG_H__505AEE55_6A66_11D1_A1F0_444553540000__INCLUDED)
