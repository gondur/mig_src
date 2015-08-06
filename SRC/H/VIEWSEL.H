//------------------------------------------------------------------------------
//Filename       viewsel.h
//System         
//Author         Paul.   
//Date           Mon 19 Feb 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	VIEWSEL_Included
#define	VIEWSEL_Included

#define	DEFAULT_VIEWSEL 0

	#include	"DOSDefs.h"
	#include	"EnumBits.m"
	#include	"KeyTest.h"
	#include	"Worldinc.h"
	#include	"myMath.h"
	#include	"palette.h"

#define	VIEW_SPECIAL_NULL	0									//AMM 20Oct98
#define	VIEW_SPECIAL_MAP	1									//AMM 20Oct98
#define	VIEW_SPECIAL_REPLAY	2									//AMM 20Oct98

#ifndef	NDEBUG

#define AFX_CDECL __cdecl
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR LPCTSTR;
void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);

#endif

const	SLong	DIRECTOR_VIEW_DELAY = 5*100; //five seconds

const	SLong	MaxVisibleRange = 2500000;	//25km away//PD 14Nov96
const	SLong	CommsVisibleRange = 0x07FFFFFFF;				//PD 07Dec96

enum	DeathViewType											//RJS 02Sep98
{																//RJS 02Sep98
	DEATH_NULL = 0,												//RJS 02Sep98
	DEATH_SKID,													//RJS 02Sep98
	DEATH_WATER,												//RJS 02Sep98
	DEATH_NORMAL,												//RJS 03Sep98
	DEATH_AIRTOAIR,												//RJS 03Sep98
	DEATH_AIRTOGROUND											//RJS 11Dec98
};																//RJS 03Sep98

enum	QuickView	{QV_NULL=0,									//PD 28Jan97
					 QV_NorthEast,		QV_East,
					 QV_SouthEast,		QV_South,
					 QV_SouthWest,		QV_West,
					 QV_NorthWest,		QV_North,
					 QV_NorthEastUp,	QV_EastUp,
					 QV_SouthEastUp,	QV_SouthUp,
					 QV_SouthWestUp,	QV_WestUp,
					 QV_NorthWestUp,	QV_NorthUp,
					 QV_UpDownTog,								//PD 18Aug97
					 QV_PanLeft,								//PD 18Aug97
					 QV_PanRight,								//RDH 15Sep97
					 QV_Up,										//RDH 15Sep97
					 QV_Instruments
					};

enum	DeathZoom	{DZ_Slow = 2,
					DZ_Medium = 1,
					DZ_Fast	= 0};								//RJS 05Nov96

enum	ViewTarg	{VT_Player = 0,								//PD 14Jun96
					VT_Unlocked = VT_Player,					//PD 14Jun96
					VT_Enemy,	  VT_Friendly,
					VT_GroundTarg,VT_WayPoint,
					VT_Message,VT_AIUnfriendly,
					VT_Escortee};								//PD 02Sep96

enum	ViewMode	{VM_InPadlock = 0,
					VM_Inside,
					VM_OutPadlock,
					VM_Track,
/**/#ifndef NDEBUG
					VM_OutRevPadlock,
/**/#endif
					VM_Satellite,
					VM_NrSatellite,
					VM_FlyBy,
					VM_Chase,
					VM_InsideCheat,
					VM_ZoomedMap,								//RJS 08Sep98
					VM_Map,
					VM_Prefs};									//PD 19Nov98

enum	ViewSpec	{VS_Null = 0x00,VS_Impact = 0x01,VS_Missile = 0x02};//PD 26Jun96

enum	ZmRtFlags	{ZR_NULL=0,
					ZR_ZoomIn = 0x01,	ZR_ZoomOut = 0x02,
					ZR_RotUp = 0x04,	ZR_RotDn = 0x08,
					ZR_RotLft = 0x10,	ZR_RotRght = 0x20,
					ZR_BIG=0x80};

enum	VisFlags	{	VF_DontCare = 0,						//PD 27Jun96
						VF_CheckDeadArea,
						VF_CheckVisibleArea};

/* */const	Angles		VIEWANGLESTEP = (Angles)(int(ANGLES_180Deg)/50);	//gives 360 deg rotation in 30 sec//RDH 19Mar96

enum	ViewPanRate	{PR_MediumPan = 50, PR_FastPan = 100, PR_SlowPan = 25, PR_SlowMediumPan = 35};
enum	ViewCutType {Instant,Gradual,VSlow,Floating};					//PD 13Nov96

const	SLong		ViewRangeMin  = 0x00a0;
const	SLong		ViewRangeMax  = 0x030000;					//RJS 08Jan97
const	SLong		FlyByRange = 0x01000;						//PD 18Jun96
const	SLong		FlyBySteps = 0x00800;						//PD 18Jun96


//PD 05Jul96 - these 4 constants define the dead area behind
//and below the polygon cockpit when on inside view

const UWord dpitchstrt = (UWord )ANGLES_70Deg;	//ANGLES_90Deg;	//PD 04Sep97
//Old_Code PD 25Sep96 const UWord dpitchend  = (UWord )ANGLES_315Deg;
const UWord dpitchend  = (UWord )((UWord)ANGLES_0Deg-1);

const UWord dhdgstrt = (UWord )ANGLES_135Deg;
const UWord dhdgend  = (UWord )ANGLES_225Deg;
//PD 05Jul96

enum	ViewChange {VC_NotChanged=0,							//PD 18Nov96
					VC_SuccessfulChange,						//PD 18Nov96
					VC_ImpactViewIsOn,							//PD 18Nov96
					VC_ImpactViewIsOff,							//PD 18Nov96
					VC_PadlockNotAvail,							//RDH 28Nov96
					VC_FailedToChange,							//PD 18Nov96
					VC_FailedNoEnemyClose,						//PD 18Nov96
					VC_FailedNoEnemyVisible};					//PD 18Nov96

typedef	struct	ViewFlags
{
	ViewTarg	viewtarg;
	ViewMode	viewmode;
	ViewSpec	viewspec;
	ViewPanRate	viewpanrate;									//PD 01Apr96
	ViewCutType	viewcuttype;									//PD 01Apr96
	ViewChange	viewchanged;									//PD 24Oct96
	Bool		vieweestepped;									//PD 22Nov96
}
View_Flags,*View_FlagsP;

typedef	struct													//PD 22Jul97
tagPeripheralViewList
{
	SLong	sx,sy;
	UByte	intensity;
	UByte	edgeflag;
	Colour	clr;
}
PVList,*PVListP;												//PD 22Jul97

class	View3d;
class	Window;
class	ViewPoint : public mobileitem							//PD 08Mar96
{  
	bool multiplayerViewsRestricted;							//PD 03Mar99
	View3d*	view3dwin;
	Window* currwin;
	friend class	InfoPanelSheet;								//JIM 11Oct96
	friend class	DPlay;										//AMM 16Mar99
	typedef void(__cdecl ViewPoint::*InitRtnP) (void );
	typedef void(ViewPoint::InitRtn) (void );

	typedef void(__cdecl ViewPoint::*ZmRtRtnP) (ZmRtFlags );
	typedef void(ViewPoint::ZmRtRtn) (ZmRtFlags );

	typedef void(__cdecl ViewPoint::*DrawRtnP) (void );
	typedef void(ViewPoint::DrawRtn) (void );

	typedef void(__cdecl ViewPoint::*QVRtnP) (QuickView );		//PD 18Nov97
	typedef void(ViewPoint::QVRtn) (QuickView );				//PD 28Jan97

	typedef struct	ViewRec
	{
		ViewRec() {};
		ViewRec(SLong d,ANGLES h,ANGLES p,ANGLES r,SLong rd,ANGLES rh,ANGLES rp,ANGLES rr)
		{range=d;hdg=h;pitch=p;roll=r;reset_range=rd;reset_hdg=rh;reset_pitch=rp;reset_roll=rr;}

		SLong	range;
		ANGLES	hdg,pitch,roll;
		SLong	reset_range;
		ANGLES	reset_hdg,reset_pitch,reset_roll;
	}
	View_Rec,
	*View_RecP;

	typedef	struct	ViewKey
	{
		KeyVal3D	keynum;
		InitRtnP	viewcode;
	}
	View_Key,
	*View_KeyP;

	typedef	struct	ZoomKey
	{
		KeyVal3D	keynum;
		ZmRtRtnP	viewcode;
		ZmRtFlags	zr_flags;
	}
	Zoom_Key,
	*Zoom_KeyP;

	typedef struct	Quickview
	{
		KeyVal3D	keynum;
		QVRtnP		viewcode;
		QuickView	qv_flags;
	}
	Quick_View,
	*Quick_ViewP;

	typedef	struct	ViewpointDelta
	{
		SLong	amplitude;
		ANGLES	anglevalue;
		SLong	scalefactor;
		SWord	lastdir;
	}
	Viewpoint_Delta,
	*Viewpoint_DeltaP;

	Viewpoint_Delta	xdelta,
					ydelta,
					zdelta;

	SLong	viewrangemin,viewrangemax;							//PD 27Mar96
	SLong	modViewRangeMin;

	SLong	directorcount;

	public:

	itemptr	currentvehicle,
			trackeditem,										//PD 29Feb96
			trackeditem2,
			previousvehicle;

	private:

	itemptr	currentenemyitem,
			currentfriendlyitem,
			currentdirectoritem,
			currentgndtargitem,
			currentmessageitem;									//PD 02Sep96

	WayPointPtr	currentwaypoint;

	View_KeyP	viewee_list,
				viewtype_list,
				viewspec_list;

	View_RecP	globalviewrec,									//PD 27Feb96
				currentviewrec,
				premapviewrec,									//PD 16Feb99
				paintshopviewrec,
				inpadlockviewrec,
				insidefwdviewrec,	insideviewrec, 		insidednviewrec,//PD 20Jun96
				outpadlockviewrec,	trackviewrec,  		
#ifndef NDEBUG
				outrevpadlockviewrec,
#endif
				satelliteviewrec,	nrsatelliteviewrec,
				flybyviewrec,		chaseviewrec,		insidecheatviewrec,
				fixedviewrec,									//PD 27Sep97
				quickviewrec,									//RDH 02Sep98
				deathviewgndrec,								//RJS 02Sep98
				deathviewwatrec,								//RJS 02Sep98
				deathviewrotrec,								//RJS 03Sep98
				deathviewairrec,								//RJS 03Sep98
				maprec,											//PD 19Nov98
				prefsrec,										//RJS 25Mar99
				parachuterec;									//RJS 25Mar99

	Zoom_KeyP	viewrot_list,									//PD 14Aug97
				viewrot2_list;									//PD 14Aug97

	Quick_ViewP	quickview_list,									//PD 14Aug97
				quickview2_list;								//PD 14Aug97

	Quick_ViewP fixedview_list,
				fixedview2_list;								//PD 03Sep97

	Bool		drawpolypit,									//PD 16Feb99
				premapdrawpolypit;								//PD 16Feb99
	Bool		bupdrawpolypit;									//PD 28Jan97
	Bool		enemytoofar;									//PD 14Nov96
	Bool		enemyvisible;									//PD 18Nov96
	Bool		bDoingHW3D;
	Bool		bPadlockOut;

	ZmRtFlags	uiflag;

	Bool		nextentry;										//PD 11Sep96

	SWord		viewcodeframetime;								//PD 29Feb96

	SWord		jhead,jpitch,jroll,jzoom;						//PD 16Sep97

	ANGLES		reqhdg,reqpitch,reqroll;						//PD 05Apr96

	ANGLES		acthdg,actpitch,actroll;

	item		GroundTargItem;									//PD 09Dec96
	item		DirectorItem;									//PD 05Dec96
	int			currentmessage;									//PD 02Sep96
	UWord		quit3dtimer;
	SWord		analview[4];
	enum		{JOY_HEAD=0,JOY_PITCH,JOY_ROLL,JOY_ZOOM};

	SWord		flybytimeleft;
	bool		playingflyby;									//RJS 02Jun99
	void		ClipToWorldLimits();
	inline void CheckPadlock(ItemBasePtr);

	bool		viewNotAvailable;
	public:
		void Quit3D(UWord);
		bool Accel();
		void GetThreatData(SWord&,COORDS3D*,UByte*,const SLong);

		void ExecuteMapViewCommand(UByte);
		COORDS3D	trackedItemWorld,							//PD 18Sep97
					trackedItem2World;							//PD 18Sep97

		ItemBase*	itemTalkedAbout;							//RJS 09Jul99

		int		timerFudgeFactor;								//PD 18Sep97
		Bool	StopDeadView;
		UByte	viewmodeselect;		//0 = standard viewing
									//		system
									//1 = fixed viewing system
		Bool	isMagic;										//RJS 05Aug97
		UByte	MagicCode;										//RJS 05Aug97
		Bool	isLightShaded;									//RJS 24Jul97
		UByte	deathspeed;										//RJS 05Nov96
//dead		UByte	enemydirection;									//RJS 11Nov96
		Bool	deathview;										//RJS 09Jan98
		ItemPtr	supercheatitem;									//RJS 18Sep96
		UByte	flakwobble:3;									//RJS 19Nov96
		UByte	stallwobble:3;									//RJS 19Nov96

		SLong	visiblerange;									//PD 27Aug96

		View_Flags	viewnum,
					bupviewnum,									//PD 19Sep97
					dirviewnum,									//PD 16Feb99
					premapviewnum;								//PD 16Feb99

		SLong	viewitemrange;
//DEAD		ANGLES	viewitemhdg;									//PD 05Jul96

		SLong	messagetime;									//RDH 20May96

		short int	mach;
		SWord		right_aoa,									//RDH 15Jul96
					left_aoa;									//RDH 15Jul96

		SLong	bfviewtarg,
				bfviewmode,
				bfcuttype,	
				bfpanrate,	
				bfzoom,		
				bfheading,	
				bfpitch,		
				bfrollrate,
				bfrotaterate,
				bfcamitem,
				bftrgtitem,
				bfpitchrate;

		SLong	currentenemyrange,								//PD 27Jun96
				currentfriendlyrange,
				currentgroundtrgrange;

		DeathViewType	setDeath;								//RJS 02Sep98
		ANGLES	ViewAngleStep;
		SLong	KeySteps;										//JIM 19Aug96
		Bool	drawmap;										//RJS 10Sep98
		ULong	drawSpecialFlags;								//AMM 20Oct98
//////////////////////////////
		CON		ViewPoint(Window* win,View3d* v);
 		DES		~ViewPoint();

		void ReturnFromMap();									//PD 16Feb99

		int	FrameTime();
		int TimeSinceLastMove();
		int	RealFrameTime(); 
		int	TimeOfDay();
		void	BlockTick(Bool q);
		void ViewFudge();										//PD 18Sep97
		void ViewUnFudge();										//PD 18Sep97

		SLong BuildPeripheralVisionList(Window*,PVList*,SLong);		//PD 22Jul97
		SLong CockpitOrientation(Window*,PVList*,SLong);		//PD 03Sep97

		void SetViewRangeMinMax(SLong, SLong);					//PD 27Mar96

		void SetVisibleRange(SLong vrng) {visiblerange=vrng;};	//PD 27Aug96

		void UISetViewItemShape(ShapeNum );						//PD 28Mar96
		itemptr UIGetViewedItem();								//PD 28Mar96
		void SetToPaintShop();									//PD 21Feb96
		void UISelectView();									//PD 21Feb96
		void SetUIFlag(ZmRtFlags);								//PD 22Feb96
		void ClearUIFlag(ZmRtFlags);							//RDH 22Feb96
		void UIResetView();										//PD 21Feb96

		void SelectView();
		void SetToPiloted(itemptr,bool replayreset=false);
		void SetToMapItem(itemptr);								//PD 11Mar99

		Bool PolyPitEnabled();
		Bool UseIdentityMatrix();
		Bool QuickViewing();									//PD 28Jan97
		void GetPolyPitAngles(ANGLES& , ANGLES& , ANGLES& );	//PD 28Feb96
		void GetViewRecAngles(ANGLES& , ANGLES& , ANGLES& );	//PD 05Sep97

		void AllOutsideAnglesReset();							//PD 23Feb96

		AirStrucPtr	GetViewedAc();								//PD 19Aug96
		void SetToDeathView(DeathViewType dtype=DEATH_NORMAL,DeathZoom	slowzoom=DZ_Fast,Bool	haltview=FALSE);//RJS 12Sep97
		void SetToResurrectView();								//ARM 05Dec96
		void PossDirectorAction(Coords3D&);						//RJS 24May99
		void SetToParachuteView(mobileitem*);					//RJS 27Jan98
		void SetReplayView(Bool);								//AMM 20Oct98
		void SetCheatItem(ItemPtr);								//RJS 09Nov98

	private:
		void	ReadJoystick(SWord&,SWord&,SWord&,SWord&);		//PD 16Sep97
		void	GetRoll4HdgAndPitch(ANGLES&,ANGLES&,ANGLES&);	//PD 26Nov96
		UByte 	WhichWay(itemptr);								//PD 07Dec96
		void	RelativeIntercept(itemptr src,itemptr trg,
									ANGLES& rhdg,ANGLES& rpitch);
		void ControlDirectorView();
		void ControlAircraftSelect();
		void ControlViewSelect();
//dead		void CommsStuff();										//PD 18Sep97
		void ControlViewDraw();
		void BFViewSelect();									//PD 01Apr96
		void SetViewFromNum(View_Flags);						//PD 01Apr96
		itemptr GetItemPtrFromUID(SLong );						//PD 01Apr96
		void UpdateGlobalViewRec();								//PD 04Apr96
		void UpdateGlobalHPR();									//PD 05Apr96
	protected:

		void CopyPosition(itemptr, itemptr);
		void CopyPositionHP(itemptr, itemptr);					//PD 27Feb96
		void CopyPositionHPR(itemptr, itemptr);
		void CopyPositionHPVel(itemptr, itemptr);				//PD 24Apr96
		void CopyPositionHPRVel(itemptr, itemptr);				//PD 26Apr96
		void GetHPIntercept(itemptr, ANGLES&, ANGLES& );		//PD 27Feb96
		void AddViewRec(bool addjoy=true);
		void AddViewRecInside(bool dojoy=true);								//PD 14Jun96
		void ClipInsideAngles();								//PD 17Jun96
		void AddZoom();
		void AddCameraWobble();									//PD 29Feb96
		void NewCameraDelta(Viewpoint_Delta&);					//PD 29Feb96
		SLong GetCameraDisplacement(Viewpoint_DeltaP,ANGLES);	//PD 29Feb96
		void GetDeltaAxis(SWord, SWord, SLong, SLong, SLong&, SWord&);//PD 01Mar96

		public:

		itemptr GetFirstAC();
		itemptr GetNextAC(itemptr);

		itemptr GetFirstItem(	MobileItemPtr,	//List ptr
								Nationality,	//Side
								SLong&			//Current range	
							);

		itemptr GetLastItem(	MobileItemPtr,	//List ptr
								Nationality,	//Side
								SLong&			//Current range	
							);

		itemptr	GetFirstMessage();								//PD 02Sep96
//DEAD		itemptr GetNextMessage();								//PD 02Sep96
//DEAD		itemptr	GetLastMessage();								//PD 08Oct97
//DEAD		itemptr GetPrevMessage();								//PD 08Oct97

		itemptr GetNextItem	(	MobileItemPtr,	//List ptr
								MobileItemPtr,	//Current ptr
								Nationality,	//Side
								SLong&			//Current range
							);

		itemptr GetPrevItem	(	MobileItemPtr,	//List ptr
								MobileItemPtr,	//Current ptr
								Nationality,	//Side
								SLong&			//Current range
							);
protected:
		//Viewee setup routines

		InitRtn InitPiloted,
				InitEnemy,
				InitFriendly,
				InitGroundTarget,
				InitWayPoint,
				InitMessage,									//PD 03Sep96

				PInitEnemy,										//PD 08Oct97
				PInitFriendly,									//PD 08Oct97
				PInitGroundTarget,								//PD 08Oct97
				PInitWayPoint,									//PD 08Oct97
//DEAD				PInitMessage,									//PD 08Oct97

				InitFlyingView,									//PD 03Sep96
				ResetEnemy,
				ResetFriendly,
				ResetGroundTarget,
				NextGroundTarget,
				PrevGroundTarget,								//PD 08Oct97
				ResetWayPoint,
				RSetWP,
				ResetMessage,
				InitAIUnfriendly,
				InitEscortee,
				ToggleEnemy;									//PD 26Sep96

		//View type selection routines

		InitRtn	List1Toggle,	//Inside padlock -> inside look up -> inside look down
				List2Toggle,	//Outside padlock -> track -> outside padlock reverse
				List3Toggle,	//Satellite -> near satellite
				List4Toggle,	//Fly by -> chase				//PD 17Jun96
				List5Toggle,	//Cheat view (no cockpit just crosshairs)//PD 17Jun96
				List7Toggle,	//Inside<->outside padlock toggle//PD 26Sep96
				List8Toggle,	//Map toggle
				List9Toggle;									//PD 19Nov98

#ifndef	NDEBUG
		InitRtn	List6Toggle;									//PD 27Jun96
#endif															//PD 27Jun96

		//View type setup routines

		InitRtnP viewsetuprtn;

		InitRtn	InitInPadlock,
				InitInside,										//PD 03Sep96
				InitOutPadlock,	InitTrack,	
#ifndef NDEBUG
				InitOutRevPadlock,
#endif
				InitSatellite,	InitNrSatellite,
				InitFlyBy,		InitChase,	InitInsideCheat,	//RJS 08Sep98
				InitMap,		InitPrefs,	InitMapAccel;		//PD 03Mar99

		//View type update routines

		InitRtnP viewdrawrtn,
				 bupviewdrawrtn,								//PD 16Feb99
				 premapviewdrawrtn;								//PD 16Feb99

		InitRtn	DrawInside,
				DrawInsideLostLock,								//PD 23Oct96
				DrawInPadlock,									//PD 27Feb96
				DrawInPadlockB,									//PD 27Feb96
				DrawInsideFwd,									//PD 20Jun96
				DrawOutPadlock,									//PD 27Feb96
#ifndef NDEBUG
				DrawOutRevPadlock,								//PD 28Feb96
#endif
				DrawTrack,
				DrawOutside,
				DrawChase,
				DrawFlyBy,
				DrawInsideCheat,								//PD 17Jun96
				DrawQuick,										//PD 28Jan97
				DrawFixed,										//PD 27Sep97
				InvalidDraw,									//RJS 08Sep98
				DrawMap,										//PD 19Nov98
				DrawPrefs;										//PD 19Nov98

		//Special case routines

		InitRtn	ImpactToggle;									//PD 17Jun96

		//View zoom and rotation handlers

		ZmRtRtn	HandleZoom,
				HandleRotate,
				ResetZoomRotate,
				ResetZoomRotat2;

		//Quick view control routine

		QVRtn	HandleQuickView,
				HandleFixedView;								//PD 22Jul97

		item	*flybysrc,*flybydelta;

		void	StopZoom();										//PD 02May96
		void	StopRotate();									//PD 02Sep96

		Bool	ModifyView();									//PD 05Jul96

		Bool	VisibleTest(itemptr ,VisFlags );				//DAW 30Jun96

		Bool	ItemInDeadZone(itemptr );						//DAW 30Jun96
		void	UpdatePosWRTEye();
		void	AnalogRead();
		Nationality	natfriend,natenemy;

};

//extern class ViewPoint View_Point;

#endif
