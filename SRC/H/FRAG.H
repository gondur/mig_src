#if !defined(AFX_FRAG_H__27646161_0F61_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_FRAG_H__27646161_0F61_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Frag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrag dialog
class CFragPilot;

class CFrag : public RowanDialog
{
// Construction
public:
///	CFrag(CWnd* pParent = NULL);   // standard constructor
protected:
	CFrag(int fragid,CWnd* pParent);   // standard constructor
	void	CFragCon();
public:
	UINT frag_timer;
	bool	fragfirsttime;

	enum	{MaxFragLines=6};

	typedef	int OneFragDef[6];


	static	void CFrag::FragInit();
	static	void CFrag::FillComboParams(int& comboentry, int type, int pack, int wave, int group);
	static	int CFrag::FillFlightParams(int i, OneFragDef* params);
	static	int CFrag::MakeFlights(int numopts, int p, int w, int g, OneFragDef* params);
	static	int CFrag::FillFlightParamswithSquads(int squad, OneFragDef* params);
	static	char CFrag::FindUniqueCallName(char callname);
	static	bool CFrag::SquadFlying(int squad);
	static	bool PositionValid(int pilot,CFrag::OneFragDef* params, int numopts);


	static  CFragPilot* pilotlines[MaxFragLines+1];


	static int disppack,dispgrp,dispsquad, comboindex;
	static bool packmode;
enum	{MAXCOMBOENTRIES  = 12};
enum	FillType	{NOTUSED = 0,ALLFLIGHTS, PACKAGE, WAVE, GROUP};
struct	ComboParams
{
	FillType	type;
	int			pack;
	int			wave;
	int			group;
};

static	ComboParams	comboparams[MAXCOMBOENTRIES];

// Dialog Data
	//{{AFX_DATA(CFrag)
	enum { IDD = IDD_FRAGCOMMS };
	CEdit	m_IDCX_PLAYERCHAT;
	CRStatic	m_IDC_RSTATICCTRL24;
	CRStatic	m_IDC_RSTATICCTRL35;
	CRStatic	m_IDC_RSTATICCTRL37;
	CRRadio	m_IDC_RRADIO_DETAILS;
	CRCombo	m_IDC_ATTACKMETHOD2;
	CRStatic	m_IDC_GRPDESC;
	CRButton	m_IDC_PILOTEDFLAG;
	CRStatic	m_IDC_UNASSIGN;
	CRButton	m_IDC_UNASSIGNFLAG;
	CRListBox	m_IDC_RLIST_INCOMING_CHAT;
	CREdit	m_IDC_PLAYERCHAT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CFrag::RedrawScreen();


	// Generated message map functions
	//{{AFX_MSG(CFrag)
	virtual BOOL OnInitDialog();
	afx_msg void OnReturnPressedPlayerchat(LPCTSTR text);
	afx_msg void OnSelectedRradioDetails(long ButtonNum);
	afx_msg void OnTextChangedAttackmethod2(LPCTSTR text);
	afx_msg void OnClickedPilotedflag();
	afx_msg void OnClickedUnassignflag();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnTextChangedPlayerchat(LPTSTR text);
	afx_msg void OnUpdatePlayerchat();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnReturnPressed();
	DECLARE_MESSAGE_MAP()
};

class	CFragComms:public	CFrag
{
public:
	enum	{ IDD = IDD_FRAGCOMMS};
	CFragComms(CWnd* parent=NULL):	CFrag(IDD,parent)	{}
	void	OnOK()	{OnReturnPressed();}
};
class	CFragSingle:public	CFrag
{
public:
	enum	{ IDD = IDD_FRAG};
	CFragSingle(CWnd* parent=NULL):	CFrag(IDD,parent)	{}
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAG_H__27646161_0F61_11D2_A5A3_0040052179B6__INCLUDED_)
