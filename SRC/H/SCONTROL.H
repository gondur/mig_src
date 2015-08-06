#if !defined(AFX_SCONTROL_H__5F830781_4036_11D2_83A5_00004760763D__INCLUDED_)
#define AFX_SCONTROL_H__5F830781_4036_11D2_83A5_00004760763D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SControl.h : header file
//
#ifndef AXIS_USES
#define	AXIS_USES
enum	AxisUses		{	AU_UNASSIGNED=-1,
							AU_AILERON=0,AU_ELEVATOR,AU_RUDDER,AU_THROTTLE,
							AU_UI_X=4,AU_UI_Y,
							AU_COLLECTIVE=6,AU_COOLIEHAT=7,
							AU_VIEWH=8,AU_VIEWP,AU_VIEWR,AU_VIEWZ,
							AU_GUNH=12,AU_GUNP,
						  	AU_WALKSPEED=14,AU_WALKTURN,
							AU_FLAPS=16,AU_BRAKE,AU_TRIM_ELEV,AU_ABSTEPS,
							AU_MIN=0,AU_MAX=31,AU_ILLEGAL=127,
							MAXFORCEAXES=10	//list of FF actuator GUIDs
						};
#endif

/////////////////////////////////////////////////////////////////////////////
// SController dialog

class SController
#ifdef __AFXWIN_H__
	:public RowanDialog
#endif
{
// Construction
public:
	UINT ControlsPref_Timer;

//enum	AssignedTasks {AT_UNASSIGNED=-1,AT_AILERON,AT_ELEVATOR,AT_RUDDER,AT_THROTTLE,AT_PAN,AT_PITCH,AT_ZOOM,AT_MOUSELR,AT_MOUSEUD};
#ifdef __AFXWIN_H__
	SController(CWnd* pParent = NULL);   // standard constructor
	void PreDestroyPanel();
	void	SetEnabled(int newaxis);
// Dialog Data
	//{{AFX_DATA(SController)
	enum { IDD = IDD_SCONTROLLER };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_RSTATICCTRL6;
	CRStatic	m_IDC_RSTATICCTRL9;
	CRStatic	m_IDC_RSTATICCTRL12;
	CRStatic	m_IDC_RSTATICCTRL14;
	CRStatic	m_IDC_RSTATICCTRL16;
	CRCombo	m_IDC_DEVLIST;
	CRCombo	m_IDC_STICKDEV;
	CRCombo	m_IDC_THROTDEV;
	CRCombo	m_IDC_RUDDEV;
	CRCombo	m_IDC_PANDEV;
	CRStatic	m_IDC_RSTATICCTRL17;
	CRStatic	m_IDC_RSTATICCTRL18;
	CRStatic	m_IDC_RSTATICCTRL19;
	CRCombo	m_IDC_PITCHDEV;
	CRCombo	m_IDC_ZOOMDEV;
	CRCombo	m_IDC_MOUSEDEV;
	CRStatic	m_IDC_DEVDESC;
	CREdtBt	m_IDC_CALIB;
	CRStatic	m_IDC_SUPPFF;
	CRButton	m_IDC_SELFF;
	CRStatic	m_IDC_SUPPFF2;
	CRButton	m_IDC_SELPOLL;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_RSTATICCTRL8;
	CRStatic	m_IDC_RSTATICCTRL46;
	CRCombo	m_IDC_CBO_FF_GUNRATTLE;
	CRCombo	m_IDC_CBO_FF_STALL;
	CRCombo	m_IDC_CBO_FF_HIGHSPEED;
	CRCombo	m_IDC_CBO_FF_AIRFRAME;
	CRCombo	m_IDC_CBO_CONTROLCOLDEADZONE;
	CRCombo	m_IDC_CBO_RUDDERDEADZONE;
	//}}AFX_DATA

	bool	SetAxesCombo(CRCombo& ID,AxisUses task,bool xonly,bool analogonly,bool paironly);
	int		ChangedAxesCombo(CRCombo& ID,AxisUses task,bool xonly,bool analogonly,bool paironly);
	void	ChangedAxesValue(int newind,AxisUses task);
	void	ChangedAxesSecondValue(int newind,AxisUses task);
	void	RemakeAxes();
	void	RemakeDisplay();				  //GetExtFuel
#endif


	static void	GetAxisConfig(bool setff=false);
	static void	SetAxisConfig();
	static void BuildEnumerationTables();
#ifdef __AFXWIN_H__
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SController)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SController)
	afx_msg void OnClickedCalib();
	afx_msg void OnTextChangedDevlist(LPCTSTR text);
	afx_msg void OnTextChangedMousedev(LPCTSTR text);
	afx_msg void OnTextChangedPandev(LPCTSTR text);
	afx_msg void OnTextChangedPitchdev(LPCTSTR text);
	afx_msg void OnTextChangedRuddev(LPCTSTR text);
	afx_msg void OnClickedSelff();
	afx_msg void OnClickedSelpoll();
	afx_msg void OnTextChangedStickdev(LPCTSTR text);
	afx_msg void OnTextChangedThrotdev(LPCTSTR text);
	afx_msg void OnTextChangedZoomdev(LPCTSTR text);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnTextChangedCboControlcoldeadzone(LPCTSTR text);
	afx_msg void OnTextChangedCboRudderdeadzone(LPCTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
#endif	//def __AFXWIN_H__
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCONTROL_H__5F830781_4036_11D2_83A5_00004760763D__INCLUDED_)
