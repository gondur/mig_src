#if !defined(AFX_RSPINBUTP_H__7EBC74F3_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RSPINBUTP_H__7EBC74F3_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RSpinButP.h : Declaration of the CRSpinButPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRSpinButPropPage : See RSpinButP.cpp.cpp for implementation.

class CRSpinButPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRSpinButPropPage)
	DECLARE_OLECREATE_EX(CRSpinButPropPage)

// Constructor
public:
	CRSpinButPropPage();
	long m_lRepeatDelay;

// Dialog Data
	//{{AFX_DATA(CRSpinButPropPage)
	enum { IDD = IDD_PROPPAGE_RSPINBUT };
	long	m_FontNum;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRSpinButPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSPINBUTP_H__7EBC74F3_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED)
