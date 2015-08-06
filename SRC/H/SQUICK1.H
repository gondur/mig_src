#if !defined(AFX_SQUICK1_H__CB7A5325_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SQUICK1_H__CB7A5325_FA0F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SQuick1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSQuick1 dialog
class	CSQuickLine;
class	CSQuick1;

struct	QuickFields
{
	enum QFD {
				QFD_FIGHTER,
				QFD_BOMBER_PLAYER_ONLY,
				QFD_BOMBER_AUTO_ONLY,
				QFD_BOMBER_PLAYER_AUTO,			//these 2 access the same list
				QFD_BOMBER_PLAYER_AUTO_IS_AUTO,	//but flag which is selected
				QFD_MIG_PLAYER_ONLY,
				QFD_MIG_AUTO_ONLY,
				QFD_MIG_PLAYER_AUTO,			//you must slecet appropriately
				QFD_MIG_PLAYER_AUTO_IS_AUTO,
				QFD_FIXED_PLAYER,
				QFD_FIXED_AUTO,
				QFD_FIXED_NUM_PLAYER,
				QFD_FIXED_NUM_AUTO,	//12
//DeadCode AMM 12May99 				QFD_LONE_PLAYER,
//DeadCode AMM 12May99 				QFD_LONE_MIG,		//14
				QFD_SPARE_SLOT_LOOK_SPARE_SLOT_LOOK,
				QFD_LONE_PLAYER,	//14
				QFD_LONE_MIG,		//15
				QFD_MASK=0x0f,
				QFD_LAST=0x0f,
				QFD_FLAGS=0xf0,
				QFD_ALLOW_ZERO_FL=128

	};
				
	char	actype;
	char	flights;
	char	skill;
	int alt;
	int descID;

	char	duty;

	QFD		Duty()	{return (QFD)(duty&QFD_MASK);}
	char	DutyFlags()	{return duty;}
	bool	AllowZero()	{return (duty&QFD_ALLOW_ZERO_FL)!=0;}
	void	SetDuty(QFD v)	{duty=(duty&QFD_FLAGS)|v;}
	CSQuickLine*	dialog;
};
struct	QuickDef
{
   	int		missionname,missiondesc;
	QuickFields
		line[2]	//red/blue
			[8]	//waves
			[4];//groups
	char	plside,plwave,plgrp,plac;
	UWord	currmissnum;
	char	weather,	cloudbaseK;
	int		targtypeIDs[4];
	UniqueID	targets[4][4];
	UniqueID	target;

	CSQuick1*	parent;
	int	SpareFlights(int squad);
	void	FixOtherLines(int squad);
	void	MakeDeathMatchMission(int index);
	void	MakeTeamPlayMission(int index);
	void	UpdateAcType();


};
#ifdef	QUICKQUICKQUICK
class CSQuick1
{
public:
	static	QuickDef	quickdef;
	static	QuickDef	quickmissions[];
	static	int			currquickmiss;


} ;
#else
class	QFDField;

class CSQuick1 : public RowanDialog
{
// Construction
public:
	int	targtype,targentry,plflst;
	CSQuick1(CWnd* pParent = NULL);   // standard constructor
	UINT missbrief_timer;
	UByte	misslistindex[40];
	UByte	misslistbackindex[40];

// Dialog Data
	//{{AFX_DATA(CSQuick1)
	enum { IDD = IDD_SQUICKMISSION };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_SDETAIL1;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_SDETAIL2;
	CRStatic	m_IDC_RSTATICCTRL24;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRCombo	m_IDC_MISSLISTS;
	CRCombo	m_IDC_FLIGHTNUM;
	CRCombo	m_IDC_ELTNUM;
	CRCombo	m_IDC_CLOUD;
	CRCombo	m_IDC_WEATHER;
	CRCombo	m_IDC_TARGTYPE;
	CRCombo	m_IDC_TARGNAME;
	CRRadio	m_IDC_RRADIO;
	//}}AFX_DATA

	static	QuickDef	quickdef;
	static	QuickDef	quickmissions[];
	static	int			currquickmiss;
	static	QFDField	nonplayer;
	void	MakeFlightCombo();
	void	ReinitCombo();
	char	flightlines[10][4];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQuick1)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool	wassingle;

	// Generated message map functions
	//{{AFX_MSG(CSQuick1)
	afx_msg void OnTextChangedMisslists(LPCTSTR text);
	afx_msg void OnTextChangedFlightnum(LPCTSTR text);
	afx_msg void OnTextChangedTargtype(LPCTSTR text);
	afx_msg void OnTextChangedTargname(LPCTSTR text);
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedEltnum(LPCTSTR text);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSelectedRradio(long ButtonNum);
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUICK1_H__CB7A5325_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
