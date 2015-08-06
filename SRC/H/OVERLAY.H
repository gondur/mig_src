//------------------------------------------------------------------------------
//Filename       overlay.h
//System         
//Author         Paul    
//Date           Thu 4 Jun 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	OVERLAY_Included
#define	OVERLAY_Included

#define	DEFAULT_OVERLAY 0

struct ICON;
class MESSAGE_STRUC;

#define INFOLINESMAX 4

struct GameSettings;

struct MapScr;

enum Key {	SEL_1,		SEL_2,	SEL_3,	SEL_4,		
			SEL_5,		SEL_6,	SEL_7,	SEL_8,		
			SEL_9,		SEL_0,	SEL_PLUS,
			SEL_MINUS,	SEL_ENTER,	SEL_ESC,
			SEL_UP,		SEL_DN,		SEL_LFT,	
			SEL_RGT,	SEL_PAUSE,	SEL_QUIT,
			SEL_BLANK,	SEL_EOL,
			SEL_NONE};

enum KeyFlags {	KF_NULL=0,
				KF_PAUSEON=1<<4,
				KF_PAUSEOFF=2<<4,
				KF_ACCELON=4<<4,
				KF_ACCELOFF=8<<4,
				KF_SLOWACCEL=1,
				KF_FASTACCEL=12,
				KF_BESTACCEL=15,
				KF_FLAGMASK=KF_PAUSEON+KF_PAUSEOFF+KF_ACCELON+KF_ACCELOFF,
				KF_ACCELFRAMESMASK=~KF_FLAGMASK
			};

struct IconEntry
{
	UWord imageMapNo;
	UWord x,y,w,h;
};

struct FRect
{
	Float top,bottom,left,right;
};

struct MapScr
{
	//these are bit flags
	enum {	SCALE_NULL=0,  			// 	no scaling performed on the grid other
									//	than the x2 when the screen resolution
									//	is over 640x480

			SCALE_GRIDORIGIN=1,		//	grid origin position is scaled so that
									//	it always apears at the same position
									//	regardless of the current screen resolution

			SCALE_GRIDELEMENTS=2,	//	elements of the grid are scaled so that
									//	they always cover the same percentage of the
									//	screen area regardless of the screen resolution

			JUSTIFY_CENTRE_SX=4,	//	center the grid horizontally on the screen

			JUSTIFY_CENTRE_SY=8,	//	centre the grid vertically on the screen

			SCALE_GRIDWH=16,		//	scale the wipe area for the grid as the screen
									//	resolution changes

			SCALE_GRIDOFFSETS=32,

			SCALE_DOUBLEIFGT800=64,

			SCALE_DYNAMICSIZE=128,

			FLAG_MOUSEOVERHI=256
		};

	typedef Key (__cdecl MapScr::*InitRtnPtr) (void);
	typedef MapScr* (__cdecl MapScr::*SelRtnPtr) (UByte&,Key);
	typedef void (__cdecl MapScr::*ExtraRtnPtr) (void);
	typedef Key InitRtn (void);
	typedef MapScr* SelRtn (UByte&,Key);
	typedef void ExtraRtn (void);

	UWord 	gridFlags;		//general flags to specify how the screen is to be
							//displayed
	UWord 	windowLeft,		//screen(X,Y) coordinates of the top left corner of the
			windowTop;		//screen defined in PIXELS640

	UWord 	windowWidth,	//screen(W,H) values for the screen area 
			windowHeight;	//to be wiped defined in PIXELS640

	UWord 	gridXOffset,	//(X,Y) offset from the screen(X,Y) coordinates to
			gridYOffset;	//the grid start position

	ULong 	wipeColour,		//background wipe colour (NO_BACKGROUND_WIPE disables)
			textColour,		//colour for displayed text
			hilightColour;	//hilight colour for displayed text

	UWord 	columnWidth,	//Width & height of a single grid element
			rowHeight;		//

	UByte 	numColumns,		//Number of columns of grid elements
			numRows;		//Number of rows of grid elements

	UWord 	highTimer;		//hilight timer for icon based screens. 0==do nothing
							//x=remove hilight from selected option after 'x' frames

	InitRtnPtr initRtn;		//ptr to screen initialisation routine

	ExtraRtnPtr extraRtn;	//ptr to routine called at the end of each draw cycle

	struct OptionList
	{
		UWord resID;
		UByte resIDOffset;
		UByte key;
		SelRtnPtr selRtn;
	}
	optionList[32];

	InitRtn FirstMapInit,
			AccelMapInit,
			WaypointMapInit,
			RadioMapInit,
			CommsMsgMapInit,
			CommsRecipientMapInit,
			CommsMsgOrdersInit,
			CommsRecipientOrdersInit,
			ReplayScreenInit,
			CommsDialogInit,
			Orders3DInit,
			UserMsgInit,
			UserOptionsInit,
			MapViewScreenInit,
			UserOptsMapInit;

	SelRtn 	SelectFromFirstMap,
			SelectFromAccelMap,
			SelectFromWaypointMap,
			SelectFromRadioMap,
			SelectFromCommsMsgMap,
			SelectFromCommsRecipientMap,
			SelectFromCommsMsgOrders,
			SelectFromCommsRecipientOrders,
			SelectFromReplayScreen,
			SelectFromCommsDialog,
			SelectFrom3DOrders,
			SelectFromUserMsg,
			SelectFromUserOptions,
			SelectFromMapViewScreen,
			SelectFromUserOptsMap;

	ExtraRtn	UpdateMessageDisplay,
				UpdateWaypointDisplay,
				HandleUpDnLftRgtToggleKeys,
				ShowPositionIndicators,
				TimeLimitedDisplay,
//				ShowItemIcons,
				DisplayTargName;

	void	ShowItemIcons(bool);
	void	ShowItemIconsZoomed(bool);

	void	ShowBackgroundMapHiRez();
	void	ShowBackgroundMap(COORDS3D&,SWord*,SWord*);
	void	ShowBackgroundMapHi(COORDS3D&,SWord*,SWord*);
	void	ShowWaypointIcon(SWord,SWord,WayPointPtr);
	void	ShowAircraftRoute(AirStrucPtr,SWord *,SWord *,bool);
	void	ShowAircraftRouteHi(AirStrucPtr,SWord *,SWord *,bool);
	void	ShowAircraftIcon(SWord,SWord,AirStrucPtr);
	void	ShowAircraftIcons(SWord *,SWord *,bool);
	void	ShowAircraftIconsHi(SWord *,SWord *,bool);
	void	ShowTargetLocation(itemptr,SWord *,SWord *);
	void	ShowTargetLocationHi(itemptr,SWord *,SWord *);
	void	ShowTargetIcon(SWord,SWord,itemptr);

	void	ShowAircraftIconsZoomed(SLong *,SLong *,bool);
	void	ShowAircraftRouteZoomed(AirStrucPtr,SLong *,SLong *,bool);

	static float map_scale;
};

#define MSBlankLine {0,0xFF,SEL_BLANK,NULL}
#define MSListEnd {0,0xFF,SEL_EOL,NULL}
#define MSEscapeLine(p1) {0,0xFF,SEL_ESC,(p1)}
#define MSAltXLine(p1) {0,0xFF,SEL_QUIT,(p1)}
#define MSPauseLine(p1) {0,0xFF,SEL_PAUSE,(p1)}
class	DecisionAI;

class CString;
class COverlay
{
	public:
	volatile	int	accelcountdown;
	SWord	viewee_x,viewtype_x,viewrange_x,viewalt_x,viewbrg_x;
	bool	fTwoLines;
	bool fHitZoomLimit;

	struct ScrollyText
	{
		enum State 
		{
			WaitingToScroll=0,
			ScrollingToEnd,
			WaitingToScrollBack,
			ScrollingToFront
		};
		enum TimerValues 
		{
			WaitToScrollTime=10*100,
			ScrollToEndTime=10*100,
			WaitToScrollBackTime=10*100,
			ScrollToFrontTime=ScrollToEndTime
		};

		SWord timer;
		SWord index;
		SWord targetIndex;
		State state;

		ScrollyText(SWord ti=0):timer(WaitToScrollTime),index(0),state(WaitingToScroll),targetIndex(ti) {}
		SWord CharsToShuffle(SWord ft) 
		{
			if (!targetIndex) return 0;
			SLong toGo;
			toGo=(state==ScrollingToEnd)?targetIndex-index:index;
			if (toGo)
			{
				toGo=toGo*SLong(ft)/SLong(timer);
				if (!toGo) toGo=1;
			}
			else toGo=1;
			return SWord(toGo);
		}
		CString Scroll(CString&,SWord);
	}
	*pScrollyText;

		void Kludge();
	WayPointPtr curr_waypoint;
	AirStrucPtr	message_caller;
	AirStrucPtr	message_callee;
	itemptr		message_target;
	itemptr		target_item;

	int GetTime();
	enum MessageType {PAUSEMESS=0,ACCELMESS,CLEARMESS,SENSMESS,IMPACTONMESS,IMPACTOFFMESS,NOVIEWMESS};
	bool TestMessageText();
	void TriggerMessage(MessageType,UWord val=0);
	bool fZoomedMap;
	SWord messageTimer;
	FileNum loader_art;
	ImageMapDesc* pball;

	CString* msgText;
	CString* otherText;

	UByte quit3d;
	void ChopStr(CString&,CString&);
	void MakeDotDotDot(CString&);
	SWord CalcTargIndex(CString&);

	static MapScr 	firstMapScr,
					firstMapScrCOMMS,
					accelMapScr,
					waypointMapScr,
					radioMapScr,
					commsMsgMapScr,
					commsRecipientMapScr,
					commsMsgOrdersScr,
					commsRecipientOrdersScr,
					replayScr,
					replayPlayingScr,
					commsDialog,
					orders3dScr,
					userMsgScrCOMMS,
					userMsgScr,
					userOptionsScr,
					mapViewScr,
					userOptsMapScr;

	MapScr	*pCurScr,*pNewScr;
	Key hilight;
	SWord highTimer;
	UWord commsDialReturn;
	SWord displayTimeLimit;
	char** indirectStringTable;
	CString* targName;
	void DisplayTargName();

	static IconEntry replayIconTable[];
	static IconEntry mapViewIconTable[];
	IconEntry* currIcons;

	void SendMessageAndCall(MESSAGE_STRUC*,DecisionAI*);
	void SetToMapScreen();
	void SetToRadioScreen();
	void SetToMapAccelScreen();
	void SetToReplayScreen();
	void SetToMapViewScreen();
	void SetToOrdersScreen();
	void HotKeyTriggerMenu(SWord sel);
	void HotKeyTriggerMessage(SWord sel1,SWord sel2);
	void DecisionMessage(DecisionAI* dec,SWord option,AirStrucPtr caller,ItemBasePtr callee,AirStrucPtr target,Bool sayvox=TRUE);//RJS 09Jun99
	void AccelSelection(UByte hilight,ULong acceltype); //AMM 10/06/99
	UWord DisplayCommsQuitDialog();
	bool SetToUIScreen(MapScr*);
	void ProcessUIScreen();
	void SetGridDimensions(MapScr *);
	void CancelAccel();
	void MsgOptionSelected(MESSAGE_STRUC*,SLong);
	void SetTargName(char*);
	void ClippedPutC(DoPointStruc*,ImageMapDescPtr,FRect&);

	UByte startMarker,endMarker,curPos;

	UByte keyFlags;	//uses kf_ enums

	SWord mouseX,mouseY;
	SWord lastMouseX,lastMouseY;

	bool fIsWide;
	SLong physicalWidth,physicalHeight;
	ViewPoint* pvp;
	Window* pw;
	SWord fontSize;
	char* messageText;
	SLong speed;
	Float mach;
	SLong altitude;
	SLong thrust;
	SLong heading;
	SLong targRange;
	SLong targRelBrg;
	SLong targRelAlt;
	bool hard3D;
	GameSettings* pBackupSettings;

	void DoThreat();
	void DoArtHoriz();
	void DoCheatBox();
	void DrawLine(SWord,SWord,SWord,SWord,Colour);
	void DoClippedLine(SWord,SWord,SWord,SWord,Colour,SWord,SWord,SWord,SWord);
public:
//DEAD	bool isMetric;
	char *shortDistUnitStr,*longDistUnitStr,*heightUnitStr,*speedUnitStr;
	bool fDonePrefs;
	SLong averageFrameRate;

public:
	void DrawWholeScreen();
	void DrawInfoBar();
	void DrawReplayBar();
	void DrawReplayIcons(bool pauseFlag=false);
	void RenderIcon(ICON&,bool clicked=false);
	//SWord ReplayIconHitTest(SWord,SWord);
	void PutC(SWord&,SWord&,unsigned char);
	void PrintIcon(SLong,SLong,SLong,SLong,UWord);
	void PrintAt(SWord,SWord,char*);
	void PrintAt2(SWord&,SWord&,char*);
	void DrawTopText();
	void DrawMessageText();
	void DrawViewText();
	void DrawWaypointText();
	void PreFormatViewText();
	void SetFontSize(SWord fs) {fontSize=fs;}
	void DrawMapPad();
	void InitInfoTexts();
	void ReleaseInfoTexts();
	char* LdStr(SLong);
	SLong StrPixelLen(char*);
	SLong StrPixelLen2(char*);

	void InitMousePos();
	bool UpdateMousePos();
	void DisplayMouseCursor();

	void PutC3(SWord&,SWord&,int);							//RJS 1Dec00
	void PutC3Clipped(SWord&,SWord&,int);							//RJS 1Dec00

public:
	COverlay() 
	{	msgText=NULL;
		otherText=NULL;
		quit3d=0;
		averageFrameRate=0;
		fontSize=16;
		messageText=NULL;
		pvp=NULL;
		pw=NULL;
		hard3D=false;
		pCurScr=pNewScr=NULL;
		pball=NULL;
		messageTimer=0;
		fZoomedMap=false;
		pScrollyText=NULL;
//		loader_art=FIL_LOADERART_800;
	};
	~COverlay() 
	{
		if (pball)
			delete[](UByte*)pball;
		if (pScrollyText)
			delete pScrollyText;
		pScrollyText=NULL;
	};
	void SetViewpoint(ViewPoint* vp) {pvp=vp;}
	void SetScreen(Window* w) {pw=w;hard3D=w->DoingHardware3D()?true:false;}
	void SetInfoLines(SWord l);
	void RenderInfoPanel();
	void StepInfoBarUp();
	void SetMessageText(char* msg) {messageText=msg;}
	void SetInfoLineVals(SLong s,Float m,SLong a, SLong h,SLong t);
	void RenderMapPad();										//RJS 11Sep98
	void DisplayProfileData(bool );
	void InitPrefs3D();
	void Prefs3D();
	void UpdateSelections();
	void UpdateSelections2();
	void SetViewVals(SLong rng,SLong relB,SLong relA);
	void LoaderScreen(int );
	void CommsWaitingScreen(int);
	void ActionMessage(MESSAGE_STRUC*);
	void CrossHair();
};


extern class COverlay OverLay;

#endif
