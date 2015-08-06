#if !defined(AFX_FULLPANE_H__F4F91440_EF0E_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_FULLPANE_H__F4F91440_EF0E_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FullPane.h : header file
//
#include "fileman.h"
class RFullPanelDial;
struct	FullScreen;
typedef Bool (RFullPanelDial::*Proc)();
typedef Bool (RFullPanelDial::*SelProc)(FullScreen*&fs);
// Jims full screen panel structure...
struct FullScreen
{
	struct Resolutions
	{
		FileNum artwork; // a resource ID for now until we convert
		enum {DIAL0=0,SMACK,DIAL2};
		struct Dial
		{
			int X;
			int Y;
			enum {X1=0,CENTRE,X2} flags; //default topleft,x1
			FileNum PanelArt;
		} dials[3];
		
		int ListX,ListY;
	} resolutions [6];
	enum Align
	{	
		LEFT=0,RIGHT,CENTRE,ONSPACE,
		VERT=0,HORIZ=4,
		TOP=0,BOT=8,MID=16
	} listalign;
	struct ListSpec
	{
		UINT text;
		FullScreen* nextscreen;
		SelProc onselect;
	} textlists[10];
	typedef	Resolutions::Dial	Dial;
	Proc	InitProc;
	SelProc	OkProc,
			CancelProc;
};

inline FullScreen::Align operator | 
(FullScreen::Align a,FullScreen::Align b)
{return FullScreen::Align(int(a)|int(b));}
inline FullScreen::Align operator + 
(FullScreen::Align a,FullScreen::Align b)
{return (a|b);}

/////////////////////////////////////////////////////////////////////////////
// RFullPanelDial dialog
class	RFullPanelDial;
typedef	bool	(RFullPanelDial::*InterSheetProcZ)(RDialog*,int);
class RFullPanelDial : public RowanDialog
{
// Construction
	bool	enablepanelselfdrawstate;
public:
	static	bool	incomms,in3d,specialevent;
	enum	GameStates	{TITLE,QUICK,HOT,CAMP,WAR,MATCH,REPLAYLOAD};
	static	GameStates	gamestate;
	RFullPanelDial(CWnd* pParent = NULL);   // standard constructor
	RFullPanelDial::~RFullPanelDial();
	FullScreen* m_pStartScreen;	
	void PositionRListBox();
	CRect GetDialPosition(RDialog* dial, UINT dialID);
	void UpdateSize();
	void LaunchScreen(FullScreen* pfullscreen);
	int GetCurrentRes();
	void LaunchSmacker(int dialID,FileNum smackerID);
	void LaunchDial(RDialog* dial, UINT dialID);
	void LaunchDial(UINT dialID,RDialog* dial)
		{LaunchDial(dial,dialID);}
	void LaunchDial(UINT dialID,const DialBox* dial);
	void LaunchMain(FullScreen* startscreen);

	static int resolutions[6];
	UINT m_timerID;
	FullScreen* m_currentscreen;
	RDialog* pdial[3];
	int m_currentres;

	static void	SetTitleText(bool clear=false);
	Bool Launch3d(FullScreen*&fs);
	Bool LaunchMap(FullScreen*&fs, bool firsttime);
	InterSheetProcZ	localnote;
	void ChildDialClosed(int,RDialog*,int);
	CString selectedfile;
// *********** sheet declarations go here:


	static FullScreen 
		demotitle,
		quickmissionflight,
		introsmack,
		Blank,
		title,
		replayload,
		replaysave,
		singleplayer,
		campaignselect,
		quickmission,
		quickmissiondebrief,
		quickmissiondebriefgrnd,
		options3d,
		gameoptions,
		options3d2,
		vieweroptions,
		soundoptions,
		controloptions,
		multiplayer,
		flightoptions,
		selectservice,
		selectsession,
		visitorsbook,
		singlefrag,
		commsfrag,
		radio,
		campstart,
		commsquick,
		campover,
		credits,
		variants,
		mapspecials,
		endcamp,
		deadpilot,
		specialdebrief,												  //RDH 26/06/99
		warendcamp,
		addvisitorsbook,
		paintshop,
//		readyroom,
		readyroomhostmatch,
		readyroomguestmatch,
		readyroomhostmatchred,
		readyroomguestmatchred,										  //RDH 25/03/99
		readyroomhostqmission,
		readyroomguestqmission,
		readyroomhostcampaign,
		readyroomguestcampaign,
		readyroomhostqmissionred,
		readyroomguestqmissionred,
		readyroomhostcampaignred,
		readyroomguestcampaignred,
		quickview,
		loadgame,
		loadcommsgame;

// *********** method declarations go here:
	int	whichcamp;
	void	ChangeCamp(int campnum);
	bool	OnFlyingClosed(RDialog*,int);
	Bool RFullPanelDial::QuickMissionBlue();
	Bool RFullPanelDial::QuickMissionRed();
	Bool RFullPanelDial::QuickMissionDesc();
	Bool RFullPanelDial::PaintShopDesc();



	Bool IntroSmackInit();
	Bool IntroSmackInitForCredits();								  //DAW 30/03/99
	Bool TitleInit();
	Bool Options3dInit();
	Bool GameOptionsInit();
	Bool Options3d2Init();
	Bool ViewerOptionsInit();
	Bool SoundOptionsInit();
	Bool FlightOptionsInit();
	Bool ControlOptionsInit();
	Bool QuickMissionInit();
	Bool QuickViewInit();


	Bool QuickMissionDebriefInit();
	Bool QuickMissionDebriefGrndInit();
	Bool CampaignSelectInit();
	Bool CampaignOverInit();
	Bool CampaignStartInit();
	Bool ReplayLoadInit();
	Bool ReplaySaveInit();
	Bool LockerRoomInit();
	Bool SelectServiceInit();
	Bool SetUpLoadGame();

	Bool SelectSessionInit();
	Bool VisitorsBookInit();
	Bool FragInit();
	Bool RadioInit();
	Bool PaintShopInit();
	Bool ReadyRoomInit();
	Bool	MapSpecialsInit();
	Bool	EndCampInit();
	Bool	DeadPilotInit();
	Bool	SpecialsInit();

	Bool StartFlying();
	bool LoadCampaignData();
	static void SetDefaultPilotPositions();
	bool DuplicateCommsPlayer(int pos, int player, int squadnum);


	bool CommsPlayer(int pos, int& i, int squadnum);

	Bool VariantsInit();


	Bool	StartCampSmacker();
	Bool	StartCampBackground();
	Bool	StartCampObjectives();
	Bool	CheckForDemo(FullScreen*&fs);
	Bool	DoLoadGame(FullScreen*&fs);
	Bool	DoLoadCommsGame(FullScreen*&fs);
	Bool ConfirmExit(FullScreen*&fs);
	Bool QuitFlying(FullScreen*&fs);
	Bool LaunchMapFirstTime(FullScreen*&fs);
	Bool LoadCampaign(FullScreen*&fs);
	Bool ReplayLoad(FullScreen*&fs);
	Bool ReplaySave(FullScreen*&fs);
	Bool ReplayView(FullScreen*&fs);
	Bool StartComms(FullScreen*&fs);
	Bool GetSessions(FullScreen*&fs);
	Bool CreateCommsGame(FullScreen*&fs);
	Bool JoinCommsGame(FullScreen*&fs);
//	Bool VisitorsBook(FullScreen*&fs);
	Bool CreatePlayer(FullScreen*&fs);
	Bool SelectReadyRoom(FullScreen*&fs);
	static	Bool SelectReadyRoomStatic(FullScreen*&fs);
	Bool SelectReadyRoomFromRadio(FullScreen*&fs);
	Bool ResetMessages(FullScreen*&fs);
	Bool SelectRRVariants(FullScreen*&fs);									//AMM 27Jun99

//DeadCode AMM 06Aug98 	Bool RefreshSessions();
	Bool CommsSelectFly(FullScreen*&fs);
	Bool InitReplay(FullScreen*&fs);
	Bool CleanUpComms(FullScreen*&fs);
	Bool	StartCampSmacker(FullScreen*&fs);
	Bool	FragFly(FullScreen*&fs);
	Bool	ReturnToMap(FullScreen*&fs);
	Bool	Pseudo3D(FullScreen*&fs);
	Bool	StartCampBackground(FullScreen*&fs);
	Bool	StartCampObjectives(FullScreen*&fs);
	Bool	StartCampBackground2(FullScreen*&fs);
	Bool	StartCampObjectives2(FullScreen*&fs);
	Bool	SetUpHotShot(FullScreen*&fs);
	Bool	SetQuickState(FullScreen*&fs);
	Bool	SetCampState(FullScreen*&fs);
	Bool	SetUpFullWar(FullScreen*&fs);
	Bool	IfCommsToReadyRoom(FullScreen*&fs);
	Bool	ContinueAfterSpecialDebrief(FullScreen*&fs);			  //RDH 26/06/99

	Bool	PreferencesExitPath(FullScreen*&fs);
	Bool	LaunchMapIfAlive(FullScreen*&fs);
	Bool	StartNextCampaign(FullScreen*&fs);
	Bool	ContinueAlthoughDead(FullScreen*&fs);
	Bool	ReloadBecauseDead(FullScreen*&fs);
	void	ResetLoadGameOption();
	static	Bool	PrepareForFrag(FullScreen*&fs);
	void	ResetVariantOption();
	Bool	ExitVariant(FullScreen*&fs);
	Bool 	CheckLobby(FullScreen*&fs);
	Bool	CanGuestJoin(FullScreen*&fs);
	Bool	ReInitCommsInterface(FullScreen*&fs);
	Bool	LobbyCheck(FullScreen*&fs);
	Bool	ReplayLoadBack(FullScreen*&fs);
	Bool	ReplaySaveBack(FullScreen*&fs);
	Bool	DebriefReplayCheck(FullScreen*&fs);



	// Dialog Data
	//{{AFX_DATA(RFullPanelDial)
	enum { IDD = IDD_FULLPANE };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOX;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RFullPanelDial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:


	// Generated message map functions
	//{{AFX_MSG(RFullPanelDial)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSelectRlistbox(long row, long column);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnPaint();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg CFont* OnGetGlobalFont(int fontnum);
	afx_msg FileNum OnGetArt();
	MSG2_0(OnGetArt);
	MSG2_1(OnGetGlobalFont);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLPANE_H__F4F91440_EF0E_11D1_A1F0_0080C8582DE4__INCLUDED_)
