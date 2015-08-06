#if !defined(AFX_RTITLEPPG_H__008F23F8_9243_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RTITLEPPG_H__008F23F8_9243_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RTitlePpg.h : Declaration of the CRTitlePropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRTitlePropPage : See RTitlePpg.cpp.cpp for implementation.

class CRTitlePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRTitlePropPage)
	DECLARE_OLECREATE_EX(CRTitlePropPage)

// Constructor
public:
	CRTitlePropPage();

// Dialog Data
	//{{AFX_DATA(CRTitlePropPage)
	enum { IDD = IDD_PROPPAGE_RTITLE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRTitlePropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTITLEPPG_H__008F23F8_9243_11D1_A1F0_444553540000__INCLUDED)
