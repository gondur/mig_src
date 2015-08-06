#if !defined(AFX_RTREEPPG_H__E8CBAEBD_85C1_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RTREEPPG_H__E8CBAEBD_85C1_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RTreePpg.h : Declaration of the CRTreePropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRTreePropPage : See RTreePpg.cpp.cpp for implementation.

class CRTreePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRTreePropPage)
	DECLARE_OLECREATE_EX(CRTreePropPage)

// Constructor
public:
	CRTreePropPage();

// Dialog Data
	//{{AFX_DATA(CRTreePropPage)
	enum { IDD = IDD_PROPPAGE_RTREE };
	long	m_lBoxWidth;
	long	m_lBoxHeight;
	long	m_lDepth;
	long	m_lGapWidth;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRTreePropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTREEPPG_H__E8CBAEBD_85C1_11D1_A1F0_444553540000__INCLUDED)
