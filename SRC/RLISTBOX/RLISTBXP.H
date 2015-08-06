#if !defined(AFX_RLISTBOXPPG_H__90B5EDB6_666F_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RLISTBOXPPG_H__90B5EDB6_666F_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RListBoxPpg.h : Declaration of the CRListBoxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRListBoxPropPage : See RListBoxPpg.cpp.cpp for implementation.

class CRListBoxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRListBoxPropPage)
	DECLARE_OLECREATE_EX(CRListBoxPropPage)

// Constructor
public:
	CRListBoxPropPage();

// Dialog Data
	//{{AFX_DATA(CRListBoxPropPage)
	enum { IDD = IDD_PROPPAGE_RLISTBOX };
	BOOL	m_bIsStripey;
	BOOL	m_lines;
	BOOL	m_bLockLeftColumn;
	BOOL	m_bLockTopRow;
	BOOL	m_bDragAndDrop;
	long	m_FontNum;
	BOOL	m_bBlackboard;
	long	m_FontNum2;
	BOOL	m_bLines2;
	BOOL	m_bSelectWholeRows;
	BOOL	m_border;
	long	m_horzSeperation;
	long	m_vertSeperation;
	BOOL	m_Centred;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRListBoxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RLISTBOXPPG_H__90B5EDB6_666F_11D1_A1F0_444553540000__INCLUDED)
