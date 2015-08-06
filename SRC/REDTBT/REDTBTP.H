#if !defined(AFX_REDTBTPPG_H__461A1FF2_B81B_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_REDTBTPPG_H__461A1FF2_B81B_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// REdtBtPpg.h : Declaration of the CREdtBtPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CREdtBtPropPage : See REdtBtPpg.cpp.cpp for implementation.

class CREdtBtPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CREdtBtPropPage)
	DECLARE_OLECREATE_EX(CREdtBtPropPage)

// Constructor
public:
	CREdtBtPropPage();

// Dialog Data
	//{{AFX_DATA(CREdtBtPropPage)
	enum { IDD = IDD_PROPPAGE_REDTBT };
	long	m_FontNum;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CREdtBtPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDTBTPPG_H__461A1FF2_B81B_11D1_A1F0_444553540000__INCLUDED)
