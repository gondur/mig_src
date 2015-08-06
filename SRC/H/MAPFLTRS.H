#if !defined(AFX_MAPFLTRS_H__52EE4561_0AAE_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_MAPFLTRS_H__52EE4561_0AAE_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MapFltrs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapFilters dialog

class CMapFilters : public CRToolBar
{
// Construction
public:
	CMapFilters(CWnd* pParent = NULL);   // standard constructor
	void	SetFiltersFromSaveGame();
// Dialog Data
	//{{AFX_DATA(CMapFilters)
	enum { IDD = IDD_MAPFILTERS };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_FILTER_BLUE_AIRFIELDS;
	CRButton	m_IDC_FILTER_BLUE_CIVILIAN;
	CRButton	m_IDC_FILTER_BLUE_SUPPLY;
	CRButton	m_IDC_FILTER_BLUE_MYARD;
	CRButton	m_IDC_FILTER_BLUE_BRIDGE;
	CRButton	m_IDC_FILTER_BLUE_ROADLINK;
	CRButton	m_IDC_FILTER_BLUE_TRUCK;
	CRButton	m_IDC_FILTER_BLUE_TRAIN;
	CRButton	m_IDC_FILTER_BLUE_ARTIE;
	CRButton	m_IDC_FILTER_BLUE_TROOP;
	CRButton	m_IDC_FILTER_BLUE_TANK;
	CRButton	m_IDC_FILTER_BLUE_ALL;
	CRButton	m_IDC_FILTER_RED_AIRFIELDS;
	CRButton	m_IDC_FILTER_RED_CIVILIAN;
	CRButton	m_IDC_FILTER_RED_SUPPLY;
	CRButton	m_IDC_FILTER_RED_MYARD;
	CRButton	m_IDC_FILTER_RED_BRIDGE;
	CRButton	m_IDC_FILTER_RED_ROADLINK;
	CRButton	m_IDC_FILTER_RED_TRUCK;
	CRButton	m_IDC_FILTER_RED_TRAIN;
	CRButton	m_IDC_FILTER_RED_ARTIE;
	CRButton	m_IDC_FILTER_RED_TROOP;
	CRButton	m_IDC_FILTER_RED_TANK;
	CRButton	m_IDC_FILTER_RED_ALL;
	CRButton	m_IDC_FILTER_BLUE_RAILLINK;
	CRButton	m_IDC_FILTER_RED_RAILLINK;
	CRButton	m_IDC_FILTER_MAINWP;
	CRButton	m_IDC_FILTER_SUBWP;
	CRButton	m_IDC_BORDER;
	CRButton	m_IDC_FILTER_ROUTES;
	CRButton	m_IDC_FILTER_FRONTLINE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapFilters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	CRButton	m_filterbuttons[MAPFILTERSMAX+2];
	static	int filterbuttons[MAPFILTERSMAX+2];
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapFilters)
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnClickedFilter(int id);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPFLTRS_H__52EE4561_0AAE_11D2_A5A3_0040052179B6__INCLUDED_)
