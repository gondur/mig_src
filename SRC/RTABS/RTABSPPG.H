#if !defined(AFX_RTABSPPG_H__4A1E1995_8B31_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RTABSPPG_H__4A1E1995_8B31_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RTabsPpg.h : Declaration of the CRTabsPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRTabsPropPage : See RTabsPpg.cpp.cpp for implementation.

class CRTabsPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRTabsPropPage)
	DECLARE_OLECREATE_EX(CRTabsPropPage)

// Constructor
public:
	CRTabsPropPage();

// Dialog Data
	//{{AFX_DATA(CRTabsPropPage)
	enum { IDD = IDD_PROPPAGE_RTABS };
	long	m_FontNum;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRTabsPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTABSPPG_H__4A1E1995_8B31_11D1_A1F0_444553540000__INCLUDED)
