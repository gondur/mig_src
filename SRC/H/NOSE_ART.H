#if !defined(AFX_NOSE_ART_H__52EE4561_0AAE_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_NOSE_ART_H__52EE4561_0AAE_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPilotsAircraftDetails dialog
class CPilotAircraftDetails : public RowanDialog
{
// Construction
public:
	CPilotAircraftDetails(int squadnum, int pilot,CWnd* pParent = NULL);   // standard constructor
	void RefreshData();
	void ChildDialClosed(int dialnum,RDialog* child,int rv);
	void  ParentDialClosed(RDialog*,int rv);

// Dialog Data
	//{{AFX_DATA(CPilotAircraftDetails)
	enum { IDD = IDD_PILOTS_AIRCRAFT_DETAILS };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_NAME_PILOT1;
	CRStatic	m_IDC_NAME_PILOT2;
	CRStatic	m_IDC_NAME_PILOT3;
	CRStatic	m_IDC_NAME_PILOT4;
	CRButton	m_IDC_NOSEART_1;
	CRButton	m_IDC_NOSEART_2;
	CRButton	m_IDC_NOSEART_3;
	CRButton	m_IDC_NOSEART_4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPilotAircraftDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void CPilotAircraftDetails::PickNoseArt(int ac);
	  bool CommsPlayer(int pos, int& i);

	// Generated message map functions
	//{{AFX_MSG(CPilotAircraftDetails)
	afx_msg void OnClickedNoseart1();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedNoseart2();
	afx_msg void OnClickedNoseart3();
	afx_msg void OnClickedNoseart4();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOSE_ART_H__52EE4561_0AAE_11D2_A5A3_0040052179B6__INCLUDED_)
