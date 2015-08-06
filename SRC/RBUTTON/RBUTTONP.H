#if !defined(AFX_RBUTTONPPG_H__78918655_A917_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RBUTTONPPG_H__78918655_A917_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RButtonPpg.h : Declaration of the CRButtonPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRButtonPropPage : See RButtonPpg.cpp.cpp for implementation.

class CRButtonPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRButtonPropPage)
	DECLARE_OLECREATE_EX(CRButtonPropPage)

// Constructor
public:
	CRButtonPropPage();

// Dialog Data
	//{{AFX_DATA(CRButtonPropPage)
	enum { IDD = IDD_PROPPAGE_RBUTTON };
	BOOL	m_bMovesParent;
	long	m_FontNum;
	BOOL	m_bCloseButton;
	BOOL	m_bTickButton;
	BOOL	m_bToggle;
	BOOL	m_bShowShadow;
	CString	m_NormalFileNumString;
	CString	m_PressedFileNumString;
	BOOL	m_UpdateCaption;
	CString	m_hintStringID;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRButtonPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RBUTTONPPG_H__78918655_A917_11D1_A1F0_444553540000__INCLUDED)
