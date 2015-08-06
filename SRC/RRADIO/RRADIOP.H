#if !defined(AFX_RRADIOP_H__7EBC74F3_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RRADIOP_H__7EBC74F3_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RRadioP.h : Declaration of the CRRadioPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRRadioPropPage : See RRadioP.cpp.cpp for implementation.

class CRRadioPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRRadioPropPage)
	DECLARE_OLECREATE_EX(CRRadioPropPage)

// Constructor
public:
	CRRadioPropPage();

// Dialog Data
	//{{AFX_DATA(CRRadioPropPage)
	enum { IDD = IDD_PROPPAGE_RRADIO };
	long	m_cols;
	long	m_FontNum;
	long	m_ColumnWidth;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRRadioPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RRADIOP_H__7EBC74F3_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED)
