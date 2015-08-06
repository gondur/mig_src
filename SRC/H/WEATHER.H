#if !defined(AFX_WEATHER_H__48476DC2_CE19_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_WEATHER_H__48476DC2_CE19_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Weather.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWeather dialog

class CWeather : public RowanDialog
{
// Construction
public:
	CWeather(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWeather)
	enum { IDD = IDD_WEATHER };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_RSTATICCTRL2;
	CRStatic	m_IDC_CONDITIONS;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_CONTRAIL_BASE;
	CRStatic	m_IDC_VISIBILITY;
	CRStatic	m_IDC_CONTRAIL_TOP;
	CRStatic	m_IDC_WINDSPEED0;
	CRStatic	m_IDC_WINDDIRECTION0;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRStatic	m_IDC_RSTATICCTRL11;
	CRStatic	m_IDC_RSTATICCTRL12;
	CRStatic	m_IDC_RSTATICCTRL25;
	CRStatic	m_IDC_RSTATICCTRL26;
	CRStatic	m_IDC_TEMP;
	CRStatic	m_IDC_TEMPERATURE;
	CRStatic	m_IDC_RSTATICCTRL24;
	CRStatic	m_IDC_PRESSURE;
	CRStatic	m_IDC_RSTATICCTRL47;
	CRStatic	m_IDC_CLOUDLAYER;
	CRStatic	m_IDC_RSTATICCTRL48;
	CRStatic	m_IDC_WINDSPEED1;
	CRStatic	m_IDC_WINDDIRECTION1;
	CRStatic	m_IDC_RSTATICCTRL49;
	CRStatic	m_IDC_RSTATICCTRL50;
	CRStatic	m_IDC_RSTATICCTRL51;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_GUSTS;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_SPECIALNOTES;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeather)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWeather)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEATHER_H__48476DC2_CE19_11D1_A5A3_0040052179B6__INCLUDED_)
