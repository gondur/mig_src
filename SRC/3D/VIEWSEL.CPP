/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       viewsel.cpp
//System         
//Author         Paul.   
//Date           Mon 19 Feb 1996
//Description    
//------------------------------------------------------------------------------
	#include	"dosdefs.h"
#define	F_BATTLE
#include "files.g"
	#include	"display.h"
	#include	"vertex.h"
	#include	"viewsel.h"
	#include	"matrix.h"										//PD 28Feb96
	#include	"shapes.h"										//PD 12Mar96
	#include	"myerror.h"										//PD 23Feb96
	#include	"Mytime.h"										//PD 15Mar96
	#include	"landscap.h"									//PD 15Mar96
	#include	"textref.h"										//JIM 19Jul96
	#include	"persons2.h"									//JIM 19Jul96
	#include	"3dcode.h"										//DAW 30Jul96
	#include	"savegame.h"									//PD 02Sep96
	#include	"world.h"										//RJS 18Sep96
	#include	"lstream.h"										//PD 22Nov96
	#include	"3dcom.h"
	#include	"misssub.h"
	#include	"winmove.h"										//ARM 05Dec96
	#include	"analogue.h"									//PD 16Sep97
	#include	"ranges.h"										//PD 30Sep97
	#include	"flymodel.h"
	#include	"OverLay.h"
	#include	"miles.h"
	#include	"rchatter.h"
	#include	"replay.h"
	#include	"cstring.h"
	#include	"MESSENGN.h"

//	MATHABLE(ANGLES)
	MATHABLE(ViewTarg);
	MATHABLE(ViewMode);
	BITABLE(ViewSpec);
	BITABLE(ZmRtFlags);
	NOTABLE(ZmRtFlags,-1);

//	class	ViewPoint	View_Point;

	UWord	supercheatuid = 0x0C64;

	Bool	straightback=FALSE;									//PD 28Jan97
//extern	ULong	GR_Quit3DNow;									//AMM 21Aug97

Bool	bAllowInstantUpdate;									//PD 14Oct97
bool fLastWasNormal,fLastWasAlternate;

const SLong SAFECAMERAHEIGHT=400;	//10m

const SLong MaxFlybyZoom	=50000;		//.5 km
const SLong MinFlybyZoom	=4000;		//40m
const SLong FlyByDuration	=10*100;	//10s
const SLong FlyByToChaseSwitchTime =2*100;	//2s

void ViewPoint::CheckPadlock(ItemBasePtr ip)
{
	if(!ip)	InitFlyingView();
	else
	{
		trackeditem2=(itemptr)ip;
		if (!ModifyView()) InitFlyingView();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ViewPoint
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	View point constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DES	ViewPoint::~ViewPoint()
{
	if (currworld) currworld->vp=NULL;
	shape::View_Point=NULL;
	Trans_Obj.View_Point=NULL;	//Manual_Pilot.ControlledAC2;
	Trans_Obj.View_Object=NULL;
	_Miles.SetVP(NULL);					//RJS 26Feb98
	Three_Dee.SetVP(NULL);										//RJS 19Nov98
	_Radio.View_Point = NULL;									//RJS 11May99
	OverLay.pvp=NULL;
}
CON	ViewPoint::ViewPoint(Window* win,View3d* v)
{
	waypoint=NULL;
	quit3dtimer=0xFFFF;
	Trans_Obj.View_Point=this;
	Trans_Obj.View_Object=this;
	if (currworld) currworld->vp=this;
	shape::View_Point=this;
	_Miles.SetVP(this);					//RJS 26Feb98
	Three_Dee.SetVP(this);										//RJS 19Nov98
	_Radio.View_Point = this;									//RJS 11May99
	OverLay.pvp=this;
	itemTalkedAbout = NULL;										//RJS 09Jul99

	currwin=win;
	view3dwin=v;
	static	View_Key	VieweeList[] =
	{
		{RESETVIEW,InitFlyingView},								//PD 03Sep96
		{ENEMYVIEW,InitEnemy},
		{FRNDVIEW,InitFriendly},
		{GRNDTVIEW,InitGroundTarget},
		{WAYPTVIEW,InitWayPoint},
		{MSGVIEW,InitMessage},									//PD 02Sep96

		{PREVENEMYVIEW,PInitEnemy},								//PD 08Oct97
		{PREVFRNDVIEW,PInitFriendly},							//PD 08Oct97
		{PREVGRNDTVIEW,PInitGroundTarget},						//PD 08Oct97
		{PREVWAYPTVIEW,PInitWayPoint},							//PD 08Oct97

		{RESETENEMYVIEW,ResetEnemy},
		{RESETFRNDVIEW,ResetFriendly},
		{RESETGRNDTVIEW,ResetGroundTarget},
		{RESETWAYPTVIEW,RSetWP},
		{PADLOCKTOG,ToggleEnemy},								//PD 26Sep96
		{AIUNFRIENDLYVIEW,InitAIUnfriendly},
		{ESCORTEEVIEW,InitEscortee},
		{(KeyVal3D )NULL,(InitRtnP )NULL}
	};

	static	View_Key	ViewTypeList[] =
	{
		{INSIDETOG,		List1Toggle},
		{OUTSIDETOG,	List2Toggle},
		{SATELLITOG,	List3Toggle},
		{CHASETOG,		List4Toggle},
		{CHEATTOG,		List5Toggle},							//PD 17Jun96
#ifndef	NDEBUG													//RDH 13Dec96
		{OUTREVLOCKTOG,	List6Toggle},							//PD 27Jun96
#endif															//RDH 13Dec96
		{INOUTTOG,		List7Toggle},							//PD 26Sep96
		{GOTOMAPKEY,	List8Toggle},							//rjs 09Sep98
		{ACCELKEY2,		List9Toggle},
		{(KeyVal3D )NULL,(InitRtnP )NULL}
	};

	static	View_Key	ViewSpecList[] =
	{
		{IMPACTTOG,ImpactToggle},
		{(KeyVal3D )NULL,(InitRtnP )NULL}
	};

	//use this list when view mode select is 0

	static	Zoom_Key	ViewRotList[] =
	{
		{ROTRESET,		ResetZoomRotat2,ZR_NULL},
		{ZOOMIN,		HandleZoom,		ZR_ZoomIn},
		{ZOOMOUT,		HandleZoom,		ZR_ZoomOut},
		{ROTDOWN,		HandleRotate,	ZR_RotDn},
		{ROTUP,			HandleRotate,	ZR_RotUp},
		{ROTRIGHT,		HandleRotate,	ZR_RotRght},
		{ROTLEFT,		HandleRotate,	ZR_RotLft},
		{ROTDNLEFT,		HandleRotate,	ZR_RotDn|ZR_RotLft},
		{ROTDNRIGHT,	HandleRotate,	ZR_RotDn|ZR_RotRght},
		{ROTUPLEFT,		HandleRotate,	ZR_RotUp|ZR_RotLft},
		{ROTUPRIGHT,	HandleRotate,	ZR_RotUp|ZR_RotRght},

		{BIGZOOMIN,		HandleZoom,		ZR_BIG|ZR_ZoomIn},
		{BIGZOOMOUT,	HandleZoom,		ZR_BIG|ZR_ZoomOut},
		{BIGROTDOWN,	HandleRotate,	ZR_BIG|ZR_RotDn},
		{BIGROTUP,		HandleRotate,	ZR_BIG|ZR_RotUp},
		{BIGROTRIGHT,	HandleRotate,	ZR_BIG|ZR_RotRght},
		{BIGROTLEFT,	HandleRotate,	ZR_BIG|ZR_RotLft},
		{BIGROTDNLEFT,	HandleRotate,	ZR_BIG|ZR_RotDn|ZR_RotLft},
		{BIGROTDNRIGHT,	HandleRotate,	ZR_BIG|ZR_RotDn|ZR_RotRght},
		{BIGROTUPLEFT,	HandleRotate,	ZR_BIG|ZR_RotUp|ZR_RotLft},
		{BIGROTUPRIGHT,	HandleRotate,	ZR_BIG|ZR_RotUp|ZR_RotRght},

		//add alt-keyboard number keys to this list
		{AROTRESET,		ResetZoomRotat2,ZR_NULL},
		{AROTDOWN,		HandleRotate,	ZR_RotDn},
		{AROTUP,		HandleRotate,	ZR_RotUp},
		{AROTRIGHT,		HandleRotate,	ZR_RotRght},
		{AROTLEFT,		HandleRotate,	ZR_RotLft},
		{AROTDNLEFT,	HandleRotate,	ZR_RotDn|ZR_RotLft},
		{AROTDNRIGHT,	HandleRotate,	ZR_RotDn|ZR_RotRght},
		{AROTUPLEFT,	HandleRotate,	ZR_RotUp|ZR_RotLft},
		{AROTUPRIGHT,	HandleRotate,	ZR_RotUp|ZR_RotRght},

		{(KeyVal3D )NULL,(ZmRtRtnP )NULL,ZR_NULL}
	};

	//use this list when view mode select is 1

	static	Zoom_Key AlternateViewRotList[] =									//PD 14Aug97
	{
		//add alt-keyboard number keys to this list
		{AROTRESET,		ResetZoomRotat2,ZR_NULL},
		{AROTDOWN,		HandleRotate,	ZR_RotDn},
		{AROTUP,		HandleRotate,	ZR_RotUp},
		{AROTRIGHT,		HandleRotate,	ZR_RotRght},
		{AROTLEFT,		HandleRotate,	ZR_RotLft},
		{AROTDNLEFT,	HandleRotate,	ZR_RotDn|ZR_RotLft},
		{AROTDNRIGHT,	HandleRotate,	ZR_RotDn|ZR_RotRght},
		{AROTUPLEFT,	HandleRotate,	ZR_RotUp|ZR_RotLft},
		{AROTUPRIGHT,	HandleRotate,	ZR_RotUp|ZR_RotRght},

		{(KeyVal3D )NULL,	(ZmRtRtnP )NULL,ZR_NULL}
	};															//PD 14Aug97

	static	Quick_View	QuickViewList[]=
	{
		{LOOKNE,	HandleQuickView,	QV_NorthEast},
		{LOOKE,		HandleQuickView,	QV_East}, 
		{LOOKSE,	HandleQuickView,	QV_SouthEast},
		{LOOKS, 	HandleQuickView,	QV_South},
		{LOOKSW,	HandleQuickView,	QV_SouthWest},
		{LOOKW, 	HandleQuickView,	QV_West},
		{LOOKNW,	HandleQuickView,	QV_NorthWest},
		{LOOKN,		HandleQuickView,	QV_North}, 
		{LOOKUPNE,	HandleQuickView,	QV_NorthEastUp},
		{LOOKUPE, 	HandleQuickView,	QV_EastUp}, 
		{LOOKUPSE,	HandleQuickView,	QV_SouthEastUp},
		{LOOKUPS, 	HandleQuickView,	QV_SouthUp},
		{LOOKUPSW,	HandleQuickView,	QV_SouthWestUp},
		{LOOKUPW, 	HandleQuickView,	QV_WestUp},
		{LOOKUPNW,	HandleQuickView,	QV_NorthWestUp},
		{LOOKUPN, 	HandleQuickView,	QV_NorthUp}, 
		{INSTVIEW,	HandleQuickView,	QV_Instruments},
		{INSTVIEW2,	HandleQuickView,	QV_Instruments},
		{(KeyVal3D )NULL,(QVRtnP )NULL,	QV_NULL}
	};

	static Quick_View	FixedViewList[]=
	{
		{ROTRESET,		HandleFixedView,	QV_Up},
		{ROTUPRIGHT,	HandleFixedView,	QV_NorthEast},
		{ROTRIGHT,		HandleFixedView,	QV_East}, 
		{ROTDNRIGHT,	HandleFixedView,	QV_SouthEast},
		{ROTDOWN, 		HandleFixedView,	QV_South},
		{ROTDNLEFT,		HandleFixedView,	QV_SouthWest},
		{ROTLEFT, 		HandleFixedView,	QV_West},
		{ROTUPLEFT,		HandleFixedView,	QV_NorthWest},
		{ROTUP,			HandleFixedView,	QV_North}, 
		{PANLEFT,		HandleFixedView,	QV_PanLeft},
		{PANRIGHT,		HandleFixedView,	QV_PanRight},

		{ALOOKUP,		HandleFixedView,	QV_Up},
		{ALOOKNE,		HandleFixedView,	QV_NorthEast},
		{ALOOKE,		HandleFixedView,	QV_East}, 
		{ALOOKSE,		HandleFixedView,	QV_SouthEast},
		{ALOOKS, 		HandleFixedView,	QV_South},
		{ALOOKSW,		HandleFixedView,	QV_SouthWest},
		{ALOOKW,	 	HandleFixedView,	QV_West},
		{ALOOKNW,		HandleFixedView,	QV_NorthWest},
		{ALOOKN,		HandleFixedView,	QV_North}, 
		{APANLEFT,		HandleFixedView,	QV_PanLeft},
		{APANRIGHT,		HandleFixedView,	QV_PanRight},
		{(KeyVal3D )NULL,(QVRtnP )NULL,	QV_NULL}
	};

	static Quick_View	AlternateFixedViewList[]=
	{
		{ALOOKUP,		HandleFixedView,	QV_Up},
		{ALOOKNE,		HandleFixedView,	QV_NorthEast},
		{ALOOKE,		HandleFixedView,	QV_East}, 
		{ALOOKSE,		HandleFixedView,	QV_SouthEast},
		{ALOOKS, 		HandleFixedView,	QV_South},
		{ALOOKSW,		HandleFixedView,	QV_SouthWest},
		{ALOOKW,	 	HandleFixedView,	QV_West},
		{ALOOKNW,		HandleFixedView,	QV_NorthWest},
		{ALOOKN,		HandleFixedView,	QV_North}, 
		{APANLEFT,		HandleFixedView,	QV_PanLeft},
		{APANRIGHT,		HandleFixedView,	QV_PanRight},
		{(KeyVal3D )NULL,(QVRtnP )NULL,	QV_NULL}
	};

	static	View_Rec	PaintShopViewRec(0x2800,ANGLES_225Deg,ANGLES_45Deg,ANGLES_0Deg,0x2800,ANGLES_225Deg,ANGLES_45Deg,ANGLES_0Deg);
	static	View_Rec	InPadlockViewRec(0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg);
	static	View_Rec	InsideFwdViewRec(0x0100,ANGLES_0Deg,(Angles)0xE74,ANGLES_0Deg,0x0100,ANGLES_0Deg,(Angles)0xE74,ANGLES_0Deg);
	static	View_Rec	InsideViewRec(0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg);
	static	View_Rec	InsideCheatViewRec(0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg);
	static	View_Rec	InsideDnViewRec(0x0100,ANGLES_0Deg,ANGLES_6Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_6Deg,ANGLES_0Deg);
	static	View_Rec	OutPadlockViewRec(0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg);
	static	View_Rec	TrackViewRec(0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg);
#ifndef NDEBUG
	static	View_Rec	OutRevPadlockViewRec(0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg);
#endif
	static	View_Rec	SatelliteViewRec(0x01000,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg,0x01000,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg);
	static	View_Rec	NrSatelliteViewRec(0x0100,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg);
	static	View_Rec	FlyByViewRec(0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg);
	static	View_Rec	ChaseViewRec(0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_10Deg,ANGLES_0Deg);
	static	View_Rec	GlobalViewRec;
	static	View_Rec	DeathViewGndRec(10000,ANGLES_0Deg,ANGLES_45Deg,ANGLES_0Deg,10000,ANGLES_0Deg,ANGLES_45Deg,ANGLES_0Deg);
	static	View_Rec	DeathViewWatRec(1000,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg,1000,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg);
	static	View_Rec	DeathViewRotRec(2000,ANGLES_0Deg,ANGLES_45Deg,ANGLES_0Deg,2000,ANGLES_0Deg,ANGLES_45Deg,ANGLES_0Deg);
	static	View_Rec	DeathViewAirRec(10000,ANGLES_0Deg,ANGLES_315Deg,ANGLES_0Deg,10000,ANGLES_0Deg,ANGLES_315Deg,ANGLES_0Deg);
	static	View_Rec	MapRec(0,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg,0,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg);//RJS 08Sep98
	static	View_Rec	PrefsViewRec(0x0200,ANGLES_0Deg,ANGLES_20Deg,ANGLES_0Deg,0x0200,ANGLES_0Deg,ANGLES_20Deg,ANGLES_0Deg);
	static	View_Rec	ParachuteRec(2000,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg,2000,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg);

	static	rotitem		FlyBySrc,
						FlyByDelta;
	bfpanrate=bfzoom=bfheading=bfpitch=bfrollrate=bfrotaterate=bfpitchrate=0;



	bftrgtitem=bfcamitem=UID_Null;

	currentvehicle = NULL;
	trackeditem = NULL;
	trackeditem2 = NULL;

	viewee_list 	= VieweeList;
	viewtype_list 	= ViewTypeList;
	viewspec_list 	= ViewSpecList;

	viewrot_list 	= ViewRotList;				//standard view rotate keys on the numeric keypad
	viewrot2_list 	= AlternateViewRotList;		//normal numeric keypad keys become fixed view keys

	quickview_list 	= QuickViewList;							//PD 14Aug97
//dead	quickview2_list	= AlternateQuickViewList;					//PD 14Aug97

	fixedview_list 	= FixedViewList;							//PD 14Aug97
	fixedview2_list	= AlternateFixedViewList;					//PD 03Sep97

	paintshopviewrec = &PaintShopViewRec;

	inpadlockviewrec = &InPadlockViewRec;
	insidefwdviewrec = &InsideFwdViewRec;						//PD 20Jun96
	currentviewrec = insideviewrec = &InsideViewRec;			//ARM 02Oct96
	insidecheatviewrec = &InsideCheatViewRec;					//PD 17Jun96
	insidednviewrec = &InsideDnViewRec;

	outpadlockviewrec = &OutPadlockViewRec;
	trackviewrec = &TrackViewRec;
#ifndef NDEBUG
	outrevpadlockviewrec = &OutRevPadlockViewRec;
#endif

	satelliteviewrec = &SatelliteViewRec;
	nrsatelliteviewrec = &NrSatelliteViewRec;

	flybyviewrec = &FlyByViewRec;
	chaseviewrec = &ChaseViewRec;

	globalviewrec = &GlobalViewRec;								//PD 27Feb96

	viewdrawrtn = InvalidDraw;									//PD 23Feb96
	bupviewdrawrtn = NULL;										//PD 28Jan97

	this->hdg =
		this->pitch =
		this->roll = ANGLES_0Deg;								//PD 27Feb96

	this->acthdg =												//PD 02May96
		this->actpitch =										//PD 02May96
		this->actroll = ANGLES_0Deg;							//PD 02May96

	flybysrc = &FlyBySrc;
	flybydelta = &FlyByDelta;

	viewnum.viewchanged=VC_SuccessfulChange;					//PD 24Oct96
	messagetime=FIVESECS100;									//RDH 20May96
	Status.size=VIEWPOINTSIZE;

	SetVisibleRange(MaxVisibleRange);							//PD 27Aug96

//DEAD	visiblerange=0x7FFFFFFF;

	supercheatitem = NULL;										//RJS 18Sep96

	deathviewgndrec = &DeathViewGndRec;//RJS 02Sep98
	deathviewwatrec = &DeathViewWatRec;//RJS 02Sep98
	deathviewrotrec = &DeathViewRotRec;//RJS 02Sep98
	deathviewairrec = &DeathViewAirRec;//RJS 03Sep98
	maprec = &MapRec;											//RJS 08Sep98
	prefsrec=&PrefsViewRec;										//PD 19Nov98
	drawmap = FALSE;											//RJS 10Sep98
	drawSpecialFlags = VIEW_SPECIAL_NULL;
	parachuterec=&ParachuteRec;									//RJS 25Mar99

	deathview = FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ViewPoint
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::SetToMapItem(itemptr trg)
{
	if (this)
	{
		jhead=jpitch=jroll=ANGLES_0Deg;
		deathspeed=0;
		flakwobble=0;
		stallwobble=0;
		StopDeadView=FALSE;
		setDeath=DEATH_NULL;
		viewcodeframetime=RealFrameTime();	//10;	//dummy value just to make the code work
		trg=(itemptr)WorldStuff::pMapItemHead;
		trg->World.Y=Land_Scape.GetGroundLevel(trg,NULL,true);
		deathview=FALSE;
//dead		enemydirection=0;
		AllOutsideAnglesReset();
		trackviewrec->pitch=ANGLES_45Deg;
		currentvehicle=trg;
		trackeditem2=NULL;
		previousvehicle=NULL;
		InitTrack();
		CopyPosition(trackeditem,this);
		UpdateGlobalViewRec();
		AddViewRec();
		UpdateGlobalHPR();
		AddZoom();
		viewnum.viewtarg=VT_Unlocked;
		viewnum.viewmode=VM_Track;
		viewnum.viewspec=VS_Null;
		viewnum.viewchanged=VC_SuccessfulChange;
		messagetime=FIVESECS100;
		viewnum.viewcuttype=Instant;
		ControlViewDraw();
		viewnum.viewcuttype=Gradual;
		trg->World.Y=0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToPiloted
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	Initialises the view system to front inside view
//				of piloted aircraft.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 19Feb99 void ViewPoint::SetToPiloted(itemptr pilotedac)
void ViewPoint::SetToPiloted(itemptr pilotedac,bool replayreset)//AMM 19Feb99
{
	if (this)
	{
		deathview = FALSE;												//RJS 11Jun99


		if (!_Replay.Playback)								//RJS 11Jan99
		{
			natfriend=AirStrucPtr(*pilotedac)->nationality;
			if (_DPlay.PlayerCreated && _DPlay.GameType==DEATHMATCH)
				natenemy=natfriend;
			else
			if (natfriend==NAT_BLUE)
				natenemy=NAT_RED;
			else
				natenemy=NAT_BLUE;
			jhead=jpitch=jroll=ANGLES_0Deg;
			deathspeed=0;
			flakwobble=0;
			stallwobble=0;
			StopDeadView=FALSE;
			setDeath=DEATH_NULL;
			viewcodeframetime=RealFrameTime();	//10;	//dummy value just to make the code work
			deathview=FALSE;
//dead			enemydirection = 0;										//RDH 11Nov96
			AllOutsideAnglesReset();
 			currentvehicle = pilotedac;
			trackeditem2 = NULL;
			previousvehicle = NULL;
			InitInside();
			CopyPositionHPR(trackeditem,this);						//DAW 21Feb96
			ClipInsideAngles();											//PD 17Jun96
			UpdateGlobalViewRec();										//PD 04Apr96
			AddViewRecInside();											//PD 14Jun96

			viewnum.viewtarg=VT_Unlocked;								//PD 26Jun96
			viewnum.viewmode=VM_Inside;									//PD 26Jun96
			viewnum.viewspec=VS_Null;
			viewnum.viewchanged=VC_SuccessfulChange;					//PD 24Oct96
			messagetime=FIVESECS100;									//RDH 20May96
		}
		else
		{
			natfriend=AirStrucPtr(*pilotedac)->nationality;
			if (natfriend==NAT_BLUE)
				natenemy=NAT_RED;
			else
				natenemy=NAT_BLUE;
			jhead=jpitch=jroll=ANGLES_0Deg;
			deathspeed=0;
			flakwobble=0;
			stallwobble=0;
			StopDeadView=FALSE;
			setDeath=DEATH_NULL;
			viewcodeframetime=RealFrameTime();	//10;	//dummy value just to make the code work
			deathview=FALSE;
//dead			enemydirection = 0;										//RDH 11Nov96
			if (!replayreset) //AMM20May
				AllOutsideAnglesReset();
 			currentvehicle = pilotedac;
			trackeditem2 = NULL;
			trackeditem=currentvehicle;	//AMM 19Jan99
			previousvehicle = NULL;
			CopyPositionHPR(trackeditem,this);						//DAW 21Feb96
			ClipInsideAngles();											//PD 17Jun96
			UpdateGlobalViewRec();										//PD 04Apr96
			AddViewRecInside();											//PD 14Jun96

			viewnum.viewtarg=VT_Unlocked;								//PD 26Jun96

			if (!replayreset)									//AMM 19Feb99
				viewnum.viewmode=VM_InsideCheat;									//PD 26Jun96

			viewnum.viewspec=VS_Null;
			viewnum.viewchanged=VC_SuccessfulChange;					//PD 24Oct96
			messagetime=FIVESECS100;									//RDH 20May96

			trackeditem = currentvehicle;

			if (!replayreset)									//AMM 19Feb99
				currentviewrec = insidecheatviewrec;

			bupviewdrawrtn = NULL;										//PD 28Jan97

			if (!replayreset)									//AMM 19Feb99
				viewdrawrtn = DrawInsideCheat;

			drawpolypit = FALSE;
			drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
			drawmap = FALSE;//RJS 10Sep98
			OverLay.SetToReplayScreen();
		}
	}

//Macca comment the next line in to come into 3d on padlock view
//#define FIRSTVIEWISOUTPADLOCKFRIENDLY
#ifdef FIRSTVIEWISOUTPADLOCKFRIENDLY
	InitTrack();
	CopyPosition(trackeditem,this);
	UpdateGlobalViewRec();
	AddViewRec();
	UpdateGlobalHPR();
	AddZoom();
	viewnum.viewtarg=VT_Unlocked;
	viewnum.viewmode=VM_Track;
	viewnum.viewspec=VS_Null;
	viewnum.viewchanged=VC_SuccessfulChange;
	messagetime=FIVESECS100;
	viewnum.viewcuttype=Instant;
	ControlViewDraw();
	viewnum.viewcuttype=Gradual;
	InitFriendly();
	viewnum.viewcuttype=Instant;
	ControlViewDraw();
	viewnum.viewcuttype=Gradual;
#endif

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawPiloted
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ViewPoint::PolyPitEnabled()
{
	if (this)
	{
		return(drawpolypit);
	}
	else
		return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		QuickViewing
//Author		Paul.   
//Date			Tue 28 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ViewPoint::QuickViewing()
{
	if (bupviewdrawrtn!=NULL)
		return(TRUE);

	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPolyPitAngles
//Author		Paul.   
//Date			Wed 21 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::GetPolyPitAngles(ANGLES& pithdg, ANGLES& pitpitch, ANGLES& pitroll)
{
	pithdg = (ANGLES )((hpitem* )trackeditem)->hdg;
	pitpitch = (ANGLES )((hpitem* )trackeditem)->pitch;
	pitroll = (ANGLES )((rotitem* )trackeditem)->roll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetViewRecAngles
//Author		Paul.   
//Date			Fri 5 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::GetViewRecAngles(ANGLES& vrhdg, ANGLES& vrpitch, ANGLES& vrroll)
{
	if (bupviewdrawrtn==NULL && viewdrawrtn!=DrawQuick && viewdrawrtn!=DrawFixed)
	{
 		vrhdg = -currentviewrec->hdg;
		vrpitch = -currentviewrec->pitch;
	}
	else if (viewdrawrtn==DrawQuick)
	{
 		vrhdg = -quickviewrec->hdg;
		vrpitch = -quickviewrec->pitch;
	}
	else
	{
 		vrhdg = -fixedviewrec->hdg;
		vrpitch = -fixedviewrec->pitch;
	}
	vrroll = ANGLES_0Deg;

	vrhdg-=(Angles)jhead;
	vrpitch-=(Angles)jpitch;
	vrroll-=(Angles)jroll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllOutsideAnglesReset				   		
//Author		Paul.   
//Date			Fri 23 Feb 1996
//
//Description	Resets the view system
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::AllOutsideAnglesReset()
{

	View_RecP	temp;

	temp = currentviewrec;
	currentviewrec = inpadlockviewrec; 	ResetZoomRotate((ZmRtFlags )NULL);
	currentviewrec = insidefwdviewrec;	ResetZoomRotate((ZmRtFlags )NULL);//PD 20Jun96
	currentviewrec = insideviewrec;		ResetZoomRotate((ZmRtFlags )NULL);
	currentviewrec = insidecheatviewrec;ResetZoomRotate((ZmRtFlags )NULL);//PD 17Jun96
	currentviewrec = insidednviewrec;	ResetZoomRotate((ZmRtFlags )NULL);
	currentviewrec = outpadlockviewrec;	ResetZoomRotate((ZmRtFlags )NULL);
	currentviewrec = trackviewrec;		ResetZoomRotate((ZmRtFlags )NULL);
#ifndef NDEBUG
	currentviewrec = outrevpadlockviewrec;ResetZoomRotate((ZmRtFlags )NULL);
#endif
	currentviewrec = satelliteviewrec;	ResetZoomRotate((ZmRtFlags )NULL);
	currentviewrec = nrsatelliteviewrec;ResetZoomRotate((ZmRtFlags )NULL);
	currentviewrec = flybyviewrec;		ResetZoomRotate((ZmRtFlags )NULL);
	currentviewrec = chaseviewrec;		ResetZoomRotate((ZmRtFlags )NULL);
	currentviewrec = deathviewrotrec;	ResetZoomRotate((ZmRtFlags )NULL);//RDH 02Sep98
	currentviewrec = deathviewgndrec;	ResetZoomRotate((ZmRtFlags )NULL);//RDH 02Sep98
	currentviewrec = deathviewwatrec;	ResetZoomRotate((ZmRtFlags )NULL);//RDH 02Sep98
	currentviewrec = deathviewairrec;	ResetZoomRotate((ZmRtFlags )NULL);//DAW 03Sep98
	currentviewrec = temp;

	currentenemyitem =
		currentfriendlyitem =
		currentdirectoritem =
		currentgndtargitem =
		currentmessageitem = (itemptr )NULL;					//PD 02Sep96

	currentmessage=0;											//PD 02Sep96

	currentenemyrange =											//PD 27Jun96
		currentfriendlyrange =
		currentgroundtrgrange = 0;

	currentwaypoint = (WayPointPtr	)NULL;

	xdelta.amplitude =
		xdelta.amplitude =
		zdelta.amplitude = 0;

	xdelta.anglevalue =
		ydelta.anglevalue =
		zdelta.anglevalue = (Angles)(ANGLES_180Deg + 1);		//PD 13Mar96

	xdelta.lastdir =
		ydelta.lastdir =
		zdelta.lastdir = 1;										//PD 30Sep97

	viewrangemin = ViewRangeMin;								//PD 27Mar96

//DeadCode RJS 04Jun98 	viewrangemax = ViewRangeMax;								//PD 27Mar96
	viewrangemax = 1920000;										//RJS 04Jun98

	viewnum.viewcuttype = Gradual;								//PD 04Apr96

	viewnum.viewpanrate = PR_MediumPan;							//PD 04Apr96

	directorcount = 0;											//PD 10Sep96

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectView
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::SelectView()
{
	if (quit3dtimer!=0xFFFF)
	{
		UWord newTime=quit3dtimer-RealFrameTime();
		if (newTime>quit3dtimer)
		{
			quit3dtimer=0xFFFF;
			OverLay.quit3d=1;
		}
		else quit3dtimer=newTime;
	}
//Dead	else if (Manual_Pilot.ControlledAC2 &&
//Dead			Manual_Pilot.ControlledAC2->Status.deadtime) 
//Dead			Quit3D(10*100);		//10 seconds to go


	if (setDeath == DEATH_NULL)			//RJS 11Jun99
		AnalogRead();

		if (_DPlay.Implemented &&
			_DPlay.GameRunning &&
			Save_Data.gamedifficulty[GC_MULTIPLAYERVIEWRESTRICTED])
			multiplayerViewsRestricted=true;
		else
			multiplayerViewsRestricted=false;

		ANGLES	lViewAngleStep=VIEWANGLESTEP;

		bAllowInstantUpdate=FALSE;									//PD 14Oct97

		SLong dx,dz;

		bDoingHW3D = currwin->DoingHardware3D();				//PD 19Nov97

//		if (bDoingHW3D)	modViewRangeMin = viewrangemin>>1;
/*		else		*/	modViewRangeMin = viewrangemin;

		SetVisibleRange(MaxVisibleRange);

	//DEAD	visiblerange=0x7FFFFFFF;
		
		viewcodeframetime = RealFrameTime();	//Timer_Code.realframetime;				//PD 15Mar96

//Dead		viewcodeframetime=5;

		ViewAngleStep = (Angles)((lViewAngleStep * viewnum.viewpanrate)/PR_MediumPan);//PD 05Apr96

	if (setDeath == DEATH_NULL)			//RJS 11Jun99
	{
		if (_Replay.Playback && 
			(drawpolypit==TRUE || viewnum.viewmode==VM_InsideCheat) &&
			Land_Scape.GetGroundLevel(*this)<=SAFECAMERAHEIGHT)
		{
			InitTrack();
			CopyPosition(trackeditem,this);
			UpdateGlobalViewRec();
			AddViewRec();
			UpdateGlobalHPR();
			AddZoom();
			viewnum.viewtarg=VT_Unlocked;
			viewnum.viewmode=VM_Track;
			viewnum.viewspec=VS_Null;
			viewnum.viewchanged=VC_SuccessfulChange;
			messagetime=FIVESECS100;
			viewnum.viewcuttype=Instant;
			ControlViewDraw();
			viewnum.viewcuttype=Gradual;
		}

		if (Manual_Pilot.ControlledAC2!=NULL && OverLay.pCurScr==NULL)
		{
			ControlDirectorView();										//PD 10Sep96
			ControlAircraftSelect();
		}
	}

	if (!drawmap && !multiplayerViewsRestricted && Manual_Pilot.ControlledAC2!=NULL)
	{
		ControlViewSelect();
		BFViewSelect();
	}

	ViewFudge();												//PD 18Sep97
	ControlViewDraw();
	ClipToWorldLimits();
	ViewUnFudge();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ViewFudge
//Author		Paul.   
//Date			Thu 18 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ViewFudge()
{
/*	if (Three_Dee.IsPaused())	timerFudgeFactor=0;
	else						timerFudgeFactor=TimeSinceLastMove();

	timerFudgeFactor=0;

	MovingItem*	mip;

	if (trackeditem!=NULL)
	{
		trackedItemWorld = trackeditem->World;

		if (trackeditem->Status.size>=MovingSize)
		{
			mip = (MovingItem*)trackeditem;

			mip->World.X += (timerFudgeFactor * mip->velx)/100;
			mip->World.Y += (timerFudgeFactor * mip->vely)/100;
			mip->World.Z += (timerFudgeFactor * mip->velz)/100;
		}
	}
	if (trackeditem2!=NULL)
	{
	 	trackedItem2World = trackeditem2->World;

		if (trackeditem2->Status.size>=MovingSize)
		{
			mip = (MovingItem*)trackeditem2;

			mip->World.X += (timerFudgeFactor * mip->velx)/100;
			mip->World.Y += (timerFudgeFactor * mip->vely)/100;
			mip->World.Z += (timerFudgeFactor * mip->velz)/100;
		}
	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ViewUnFudge
//Author		Paul.   
//Date			Thu 18 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ViewUnFudge()
{
/*	if (trackeditem!=NULL)	trackeditem->World = trackedItemWorld;
	if (trackeditem2!=NULL)	trackeditem2->World = trackedItem2World;
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BFViewSelect
//Author		Paul.   
//Date			Mon 1 Apr 1996
//
//Description	Sets view depending on the current values of battlefield
//				file variables
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::BFViewSelect()
{
	if (!bfcamitem)
		return;

	View_Flags	newviewnum;

	newviewnum.viewtarg = (ViewTarg )bfviewtarg;
	newviewnum.viewmode = (ViewMode )bfviewmode;
	newviewnum.viewspec = (ViewSpec )NULL;

	newviewnum.viewpanrate=(ViewPanRate )bfpanrate;
	newviewnum.viewcuttype=(ViewCutType )bfcuttype;

	SetViewFromNum(newviewnum);

	bfcamitem=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetViewFromNum
//Author		Paul.   
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::SetViewFromNum(ViewFlags vno)
{
	viewnum = vno;

	switch (viewnum.viewtarg)
	{
		case VT_Player:
			break;

		case VT_Enemy:
			InitEnemy();
			break;

		case VT_Friendly:
			InitFriendly();
			break;

		case VT_GroundTarg:
			InitGroundTarget();
			break;

		case VT_WayPoint:
			InitWayPoint();
			break;

		case VT_Message:										//PD 02Sep96
			InitMessage();										//PD 02Sep96
			break;												//PD 02Sep96

		case VT_AIUnfriendly:
			InitAIUnfriendly();
			break;

		case VT_Escortee:
			InitEscortee();
			break;

		default:
			_Error.EmitSysErr(__FILE__":Illegal ViewTarg number");
			break;
	}

	switch (viewnum.viewmode)
	{
		case VM_InPadlock:
			viewsetuprtn = InitInPadlock;
			break;

		case VM_Inside:
			viewsetuprtn = InitInside;
			break;

		case VM_OutPadlock:
			viewsetuprtn = InitOutPadlock;
			break;

		case VM_Track:
			viewsetuprtn = InitTrack;
			break;
#ifndef NDEBUG
		case VM_OutRevPadlock:
			viewsetuprtn = InitOutRevPadlock;
			break;
#endif
		case VM_Satellite:
			viewsetuprtn = InitSatellite;
			break;

		case VM_NrSatellite:
			viewsetuprtn = InitNrSatellite;
			break;

		case VM_FlyBy:
			viewsetuprtn = InitFlyBy;
			break;

		case VM_Chase:
			viewsetuprtn = InitChase;
			break;

		case VM_InsideCheat:									//PD 03Sep96
			viewsetuprtn = InitInsideCheat;						//PD 03Sep96
			break;												//PD 03Sep96

		case VM_ZoomedMap:										//RJS 08Sep98
		case VM_Map:											//RJS 08Sep98
			viewsetuprtn = InitMap;								//RJS 08Sep98
			break;												//RJS 08Sep98

//DeadCode PD 16Feb99 		case VM_Prefs:											//PD 19Nov98
//DeadCode PD 16Feb99 			viewsetuprtn=InitPrefs;								//PD 19Nov98
//DeadCode PD 16Feb99 			break;												//PD 19Nov98

		default:
			_Error.EmitSysErr(__FILE__":Illegal ViewMode number");
			break;
	}
	(this->*viewsetuprtn) ();									//PD 04Apr96

	SLong	csaverange;										//MS 09May96
	SLong	gsaverange;										//MS 09May96

	csaverange = currentviewrec->range;						//MS 09May96
	gsaverange = globalviewrec->range;						//MS 09May96

	ResetZoomRotate((ZmRtFlags )NULL);						//PD 12Apr96

	currentviewrec->range = csaverange;						//MS 09May96
	globalviewrec->range = gsaverange;						//MS 09May96

	if (bfcamitem)
		if ((trackeditem = GetItemPtrFromUID(bfcamitem))==0)	//JIM 04Apr96
			_Error.EmitSysErr(__FILE__": New tracked item is NULL");				//JIM 04Apr96

	if (bftrgtitem)
		if ((trackeditem2 = GetItemPtrFromUID(bftrgtitem))==0)	//JIM 04Apr96
			_Error.EmitSysErr(__FILE__": New tracked target is NULL");			//JIM 04Apr96

	currentviewrec->hdg += (Angles)bfheading;				//PD 05Apr96

	currentviewrec->pitch += (Angles)bfpitch;				//PD 05Apr96

	ShapeDescPtr	sdptr =
		SHAPESTUFF.GetShapePtr(trackeditem->shape);

	SLong	min_zoom_shape;		//Shape size to get min zoom range

	min_zoom_shape = sdptr->Size<<5;							//PD 05Jul96
	
	if (bfzoom<min_zoom_shape)
		bfzoom = min_zoom_shape;

	currentviewrec->range = bfzoom;								//PD 04Apr96

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetItemPtrFromUID
//Author		Paul.   
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
itemptr ViewPoint::GetItemPtrFromUID(SLong inuid)
{
 	UniqueID	tmpuid = (UniqueID )inuid;

	return	(itemptr )MobileItem::currworld->ConvertPtrUID(tmpuid);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetViewRangeMinMax
//Author		Paul.   
//Date			Wed 27 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::SetViewRangeMinMax(SLong min, SLong max)
{
 	viewrangemin = min;
	viewrangemax = max;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToPaintShop
//Author		Paul.   
//Date			Wed 21 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::SetToPaintShop()
{
	SWord	oldColorDepth;										//PD 07Jun97
	oldColorDepth=Save_Data.colourdepth;
	Save_Data.colourdepth=8;
	ViewCutType	temp;											//PD 10Apr96

	AllOutsideAnglesReset();

	temp = viewnum.viewcuttype;									//PD 10Apr96
	viewnum.viewcuttype = Instant;								//PD 10Apr96

	currentviewrec = paintshopviewrec;
	viewdrawrtn = DrawOutside;
	bupviewdrawrtn = NULL;										//PD 28Jan97
	drawpolypit = FALSE;
	CopyPosition(trackeditem,this);
	UpdateGlobalViewRec();										//PD 04Apr96
	AddViewRec();
	AddZoom();													//PD 10Apr96
	UpdateGlobalHPR();											//PD 10Apr96
	UIResetView();

	viewnum.viewcuttype=temp;									//PD 10Apr96

	bfrotaterate=												//PD 12Apr96
		bfpitchrate=											//PD 12Apr96
		bfrollrate=0;											//PD 12Apr96
	Save_Data.colourdepth=oldColorDepth;						//PD 07Jun97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToDeathView
//Author		Robert Slater
//Date			Fri 1 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::SetToDeathView(DeathViewType	dtype, DeathZoom	slowzoom,Bool	haltview)
{
// if in playback still want to be able to look around
	if (_Replay.Playback)
		return;

//DeadCode RDH 02Sep98 	ViewCutType	temp;
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 	if (_DPlay.Implemented)										//AMM 03Jul97
//DeadCode RDH 02Sep98 		slowzoom=DZ_Medium;										//AMM 03Jul97
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 	if (deathspeed == 0)										//RJS 13Nov96
//DeadCode RDH 02Sep98 	{
//DeadCode RDH 02Sep98 		StopDeadView = haltview;								//RJS 12Sep97
//DeadCode RDH 02Sep98 		deathview = TRUE;
//DeadCode RDH 02Sep98 		
//DeadCode RDH 02Sep98 		if (drawpolypit || (viewnum.viewmode == VM_InsideCheat))//RJS 07Nov96
//DeadCode RDH 02Sep98 		{
//DeadCode RDH 02Sep98 			AllOutsideAnglesReset();
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 			temp = viewnum.viewcuttype;									
//DeadCode RDH 02Sep98 			viewnum.viewcuttype = Instant;								
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 			currentviewrec = paintshopviewrec;
//DeadCode RDH 02Sep98 			bupviewdrawrtn = NULL;								//PD 28Jan97
//DeadCode RDH 02Sep98 			viewdrawrtn = DrawOutside;
//DeadCode RDH 02Sep98 			viewnum.viewmode = VM_Track;
//DeadCode RDH 02Sep98 			drawpolypit = FALSE;
//DeadCode RDH 02Sep98 			CopyPosition(trackeditem,this);
//DeadCode RDH 02Sep98 			UpdateGlobalViewRec();										
//DeadCode RDH 02Sep98 			AddViewRec();
//DeadCode RDH 02Sep98 			AddZoom();													
//DeadCode RDH 02Sep98 			UpdateGlobalHPR();											
//DeadCode RDH 02Sep98 			UIResetView();
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 			viewnum.viewcuttype=temp;									
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 			bfrotaterate=												
//DeadCode RDH 02Sep98 				bfpitchrate=											
//DeadCode RDH 02Sep98 				bfrollrate=0;
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 			switch (slowzoom)									//RJS 05Nov96
//DeadCode RDH 02Sep98 			{
//DeadCode RDH 02Sep98 			 	case DZ_Fast:
//DeadCode RDH 02Sep98 					deathspeed = 2;
//DeadCode RDH 02Sep98 					break;
//DeadCode RDH 02Sep98 				case DZ_Medium:
//DeadCode RDH 02Sep98 					deathspeed = 4;
//DeadCode RDH 02Sep98 					break;
//DeadCode RDH 02Sep98 				case DZ_Slow:
//DeadCode RDH 02Sep98 					deathspeed = 8;
//DeadCode RDH 02Sep98 					break;
//DeadCode RDH 02Sep98 			}
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 			SelectView();											//RJS 05Nov96
//DeadCode RDH 02Sep98 		}
//DeadCode RDH 02Sep98 		else
//DeadCode RDH 02Sep98 		{
//DeadCode RDH 02Sep98 			if (currentviewrec->range < 6500)
//DeadCode RDH 02Sep98 			{
//DeadCode RDH 02Sep98 				viewnum.viewmode = VM_Track;					//RJS 14Nov96
//DeadCode RDH 02Sep98 				switch (slowzoom)									//RJS 05Nov96
//DeadCode RDH 02Sep98 				{
//DeadCode RDH 02Sep98 			 		case DZ_Fast:
//DeadCode RDH 02Sep98 						deathspeed = 3;
//DeadCode RDH 02Sep98 						currentviewrec->reset_range = paintshopviewrec->reset_range;
//DeadCode RDH 02Sep98 						ResetZoomRotate((ZmRtFlags )NULL);			//RJS 05Nov96
//DeadCode RDH 02Sep98 						viewrangemin = ViewRangeMin;				//RJS 05Nov96
//DeadCode RDH 02Sep98 						viewrangemax = ViewRangeMax;				//RJS 05Nov96
//DeadCode RDH 02Sep98 						directorcount = 0;							//RJS 05Nov96
//DeadCode RDH 02Sep98 						break;
//DeadCode RDH 02Sep98 					case DZ_Medium:
//DeadCode RDH 02Sep98 						deathspeed = 4;
//DeadCode RDH 02Sep98 						currentviewrec->reset_range = paintshopviewrec->reset_range;
//DeadCode RDH 02Sep98 						ResetZoomRotate((ZmRtFlags )NULL);			//RJS 05Nov96
//DeadCode RDH 02Sep98 						viewrangemin = ViewRangeMin;				//RJS 05Nov96
//DeadCode RDH 02Sep98 						viewrangemax = ViewRangeMax;				//RJS 05Nov96
//DeadCode RDH 02Sep98 						directorcount = 0;							//RJS 05Nov96
//DeadCode RDH 02Sep98 						break;
//DeadCode RDH 02Sep98 					case DZ_Slow:
//DeadCode RDH 02Sep98 						deathspeed = 0;							//RJS 13Nov96
//DeadCode RDH 02Sep98 						break;
//DeadCode RDH 02Sep98 				}
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 				SelectView();									//RJS 07Nov96
//DeadCode RDH 02Sep98 			}
//DeadCode RDH 02Sep98 			else
//DeadCode RDH 02Sep98 				deathspeed = 0;									//RJS 07Nov96
//DeadCode RDH 02Sep98 		}
//DeadCode RDH 02Sep98 
//DeadCode RDH 02Sep98 	}

	if (!deathview)
	{
		if (setDeath != dtype)
		{
			ViewCutType	temp;
			View_Rec*	deadrec;

			switch (dtype)
			{
			case DEATH_SKID:
			case DEATH_AIRTOGROUND:									//RJS 11Dec98
				deadrec = deathviewgndrec;
				Quit3D(1000);										//RJS 11May99
				break;
			case DEATH_WATER:
				deadrec = deathviewwatrec;
				Quit3D(1500);										//RJS 11May99
				break;
			case DEATH_AIRTOAIR:									//DAW 03Sep98
				deadrec = deathviewairrec;							//DAW 03Sep98
				Quit3D(1500);										//RJS 11May99
				break;												//DAW 03Sep98
			default:												//DAW 03Sep98
				deadrec = deathviewrotrec;							//DAW 03Sep98
				Quit3D(1500);										//RJS 11May99
				break;												//DAW 03Sep98
			}														//DAW 03Sep98

//Dead			setDeath = dtype;

	//		if (_DPlay.Implemented)										//AMM 03Jul97
				slowzoom=DZ_Medium;										//AMM 03Jul97

			currentviewrec = deadrec;

			StopDeadView = haltview;								//RJS 12Sep97
			deathview = TRUE;

			temp = viewnum.viewcuttype;									
			if (!deathspeed)
			{
				AllOutsideAnglesReset();
				UIResetView();
				viewnum.viewcuttype = Instant;								
			}
			else
				viewnum.viewcuttype = Gradual;

			viewrangemin = currentviewrec->range;
			viewrangemax = ViewRangeMax;

			bupviewdrawrtn = NULL;								//PD 28Jan97
			viewdrawrtn = DrawOutside;
			viewnum.viewmode = VM_Track;
			drawpolypit = FALSE;
			CopyPosition(trackeditem,this);


			if (dtype == DEATH_AIRTOAIR)			//RJS 11Jun99
			{
				// Set view to infront of dead item...

				currentviewrec->hdg = (ANGLES)(((mobileitem*)trackeditem)->hdg + ANGLES_45Deg);
			}

			UpdateGlobalViewRec();										
			AddViewRec();
			AddZoom();													
			UpdateGlobalHPR();											

			viewnum.viewcuttype=temp;									

			bfrotaterate=												
				bfpitchrate=											
				bfrollrate=0;

			switch (slowzoom)									//RJS 05Nov96
			{
				case DZ_Fast:
					deathspeed = 2;
					break;
				case DZ_Medium:
					deathspeed = 4;
					break;
				case DZ_Slow:
					deathspeed = 8;
					break;
			}

			SelectView();											//RJS 05Nov96

			setDeath = dtype;										//RJS 11Jun99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToParachuteView
//Author		Robert Slater
//Date			Tue 27 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::SetToParachuteView(mobileitem*	pshapetrans)
{
	bfrotaterate=bfpitchrate=bfrollrate=0;
	if (!pshapetrans)
	{
		viewnum.viewmode=VM_Track;
		InitTrack();
	}
	else
	{
		viewnum.viewmode=VM_OutPadlock;
		InitOutPadlock();
		trackeditem2=trackeditem;
		trackeditem=pshapetrans;
	}
	currentviewrec=parachuterec;
	ResetZoomRotate((ZmRtFlags )NULL);
	ViewCutType	temp;
	temp=viewnum.viewcuttype;
	viewnum.viewcuttype=Instant;
	(this->*viewdrawrtn)();
	viewnum.viewcuttype=temp;
	deathview=TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToResurrectView
//Author		Andrew McRae
//Date			Thu 5 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::SetToResurrectView()
{
	_Error.SayAndQuit("settoresurrectvuew");

	ViewCutType	temp;

	deathview = TRUE;
	
	if (drawpolypit || (viewnum.viewmode == VM_InsideCheat))//RJS 07Nov96
	{
		AllOutsideAnglesReset();

		temp = viewnum.viewcuttype;									
		viewnum.viewcuttype = Instant;								

		currentviewrec = paintshopviewrec;

		bupviewdrawrtn = NULL;									//PD 28Jan97
		viewdrawrtn = DrawOutside;
		viewnum.viewmode = VM_Track;
		drawpolypit = FALSE;
		CopyPosition(trackeditem,this);
		UpdateGlobalViewRec();										
		AddViewRec();
		AddZoom();													
		UpdateGlobalHPR();											
		UIResetView();

		viewnum.viewcuttype=temp;									

		bfrotaterate= ANGLES_30Deg;
			bfpitchrate=0;
			bfrollrate=0;

			deathspeed = 0;

		SelectView();											//RJS 05Nov96
	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UISelectView
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::UISelectView()
{
	bDoingHW3D = FALSE;											//RDH 15Oct97

	bAllowInstantUpdate=FALSE;									//PD 14Oct97

	ANGLES lViewAngleStep = VIEWANGLESTEP;
	viewcodeframetime =	RealFrameTime();// Timer_Code.realframetime;				//PD 27Mar96

	ViewAngleStep = (Angles)((lViewAngleStep * viewnum.viewpanrate)/PR_MediumPan);//PD 09Apr96

	HandleZoom(uiflag);
	HandleRotate(uiflag);
	ControlViewDraw();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UIResetView
//Author		Paul.   
//Date			Wed 21 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::UIResetView()
{
	uiflag = (ZmRtFlags )NULL;
	ResetZoomRotate(uiflag);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearUIFlag
//Author		Paul.   
//Date			Wed 21 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline ZmRtFlags operator &= (ZmRtFlags z,int i) {return z=ZmRtFlags(z&i);}
void ViewPoint::ClearUIFlag(ZmRtFlags inp)
{
	uiflag &= ~int(inp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUIFlag
//Author		Paul.   
//Date			Wed 21 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::SetUIFlag(ZmRtFlags inp)
{
	uiflag |= inp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ControlAircraftSelect
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	Dummy routine not used for Flying Corps
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ControlAircraftSelect()
{

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsStuff
//Author		Paul.   
//Date			Thu 18 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//deadvoid ViewPoint::CommsStuff()
//dead{
//TempCode PD 18Nov97 	if (!isMagic)
//TempCode PD 18Nov97 	{
//TempCode PD 18Nov97 		if (Key_Tests.KeyPress3d(MAGICK1))
//TempCode PD 18Nov97  		{
//TempCode PD 18Nov97  			if (!MagicCode)
//TempCode PD 18Nov97  				MagicCode += 1;
//TempCode PD 18Nov97  		}
//TempCode PD 18Nov97  		else
//TempCode PD 18Nov97  		{
//TempCode PD 18Nov97  			if (Key_Tests.KeyPress3d(MAGICK2))
//TempCode PD 18Nov97  			{
//TempCode PD 18Nov97  				if (MagicCode == 3)
//TempCode PD 18Nov97  				{
//TempCode PD 18Nov97  					MagicCode += 4;
//TempCode PD 18Nov97  					isMagic = TRUE;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 					if (_DPlay.Implemented)						//AMM 21Aug97
//TempCode PD 18Nov97 					{											//AMM 21Aug97
//TempCode PD 18Nov97 						_DPlay.SendKill(NULL,GR_Quit3DNow,CP_CHEATED,NULL);//AMM 21Aug97
//TempCode PD 18Nov97 					}											//AMM 21Aug97
//TempCode PD 18Nov97  				}
//TempCode PD 18Nov97  			}
//TempCode PD 18Nov97  		}
//TempCode PD 18Nov97 	}
//TempCode PD 18Nov97 	else
//TempCode PD 18Nov97 	{
//TempCode PD 18Nov97  		if (Key_Tests.KeyPress3d(MAGICK1))
//TempCode PD 18Nov97  		{
//TempCode PD 18Nov97  			if (MagicCode == 1)
//TempCode PD 18Nov97  			{
//TempCode PD 18Nov97  				MagicCode -= 1;
//TempCode PD 18Nov97  				isMagic = FALSE;
//TempCode PD 18Nov97  			}
//TempCode PD 18Nov97  		}
//TempCode PD 18Nov97  		else
//TempCode PD 18Nov97  		{
//TempCode PD 18Nov97  			if (Key_Tests.KeyPress3d(MAGICK2))
//TempCode PD 18Nov97  			{
//TempCode PD 18Nov97  				if (MagicCode == 7)
//TempCode PD 18Nov97  					MagicCode -= 4;
//TempCode PD 18Nov97  			}
//TempCode PD 18Nov97  		}
//TempCode PD 18Nov97 	}
//dead}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ControlViewSelect
//LastModified:	PD 18Sep97
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	Main view control loop - tests various keys and updates the
//				view position as appropriate
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ControlViewSelect()
{
	bool viewkeysallowed=true;

	if (Manual_Pilot.ControlledAC2 && 
		(Manual_Pilot.ControlledAC2->weap.Ejected ||
		Manual_Pilot.ControlledAC2->Status.deadtime))
		viewkeysallowed=false;

	viewNotAvailable=false;

	if (viewnum.viewmode==VM_Map) return;

	ReadJoystick(jhead,jpitch,jroll,jzoom);					//PD 16Sep97

	//PD 16Jul97 - additional view keys put in for FC Gold

	// (1) View key mode selection

	Bool bViewModeToggled = FALSE;

	if (viewkeysallowed && Key_Tests.KeyPress3d(VIEWMODETOG))
	{
		if (Save_Data.gamedifficulty[GD_VIEWMODESELECT])	Save_Data.gamedifficulty %= GD_VIEWMODESELECT;
		else												Save_Data.gamedifficulty |= GD_VIEWMODESELECT;

		bViewModeToggled=TRUE;
	}

	if (viewkeysallowed && Key_Tests.KeyPress3d(BOXTARGET))
	{
		if (Save_Data.detail_3d[DETAIL3D_PADLOCKCHEAT])	Save_Data.detail_3d %= DETAIL3D_PADLOCKCHEAT;
		else											Save_Data.detail_3d |= DETAIL3D_PADLOCKCHEAT;
	}

	viewmodeselect = Save_Data.gamedifficulty[GD_VIEWMODESELECT]?1:0;//PD 22Aug97

	if (bViewModeToggled && viewmodeselect==0 &&
		(viewdrawrtn==DrawQuick || viewdrawrtn==DrawFixed))		//PD 27Sep97
		InitInside();											//PD 16Sep97

	enemytoofar = FALSE;										//PD 18Nov96
	enemyvisible = TRUE;										//PD 18Nov96
	viewnum.vieweestepped = FALSE;								//PD 22Nov96
	nextentry = FALSE;											//RDH 05Dec96

	View_KeyP	ptr;

	Zoom_KeyP	ptr2;

	View_Flags	lastviewnum;									//RDH 20May96

	lastviewnum = viewnum;										//RDH 20May96

	//Scan for keyboard input

	//Test for view target item change first

	Bool	bPadlockNotPossible=FALSE;							//PD 13Oct97

	if (viewnum.viewmode==VM_Satellite ||						//PD 13Oct97
		viewnum.viewmode==VM_NrSatellite ||
		viewnum.viewmode==VM_FlyBy ||
		viewnum.viewmode==VM_Chase ||
		viewnum.viewmode==VM_InsideCheat)
			bPadlockNotPossible=TRUE;

	if (setDeath == DEATH_NULL && viewkeysallowed)
	{
		bool donereset=false;

		for(ptr = viewee_list;	ptr->viewcode; 	ptr++)
		{
			if(Key_Tests.KeyPress3d(ptr->keynum))
			{
				nextentry=TRUE;
				if (!donereset)
				{
					donereset=true;
					(this->*(ptr->viewcode))();
				}
				else if (bPadlockNotPossible)
				{
					viewNotAvailable=true;
				}
				else
				{
					(this->*(ptr->viewcode))();
				}
				nextentry=TRUE;
			}
		}
	}

	//Test for view type change

	viewsetuprtn = NULL;

	if (setDeath == DEATH_NULL && viewkeysallowed)
	{
		for(ptr = viewtype_list; ptr->viewcode; ptr++)
		{
			if(Key_Tests.KeyPress3d(ptr->keynum))
			{
				nextentry=FALSE;									//PD 28Jan97
				(this->*(ptr->viewcode))();
			}
		}
	}

	//If the view has changed then call the init code

	if(viewsetuprtn)
	{
		(this->*viewsetuprtn) ();
		UpdateGlobalViewRec();									//PD 18Jun96
		currwin->DoReleaseTextures();
	}

	//Test for special case view keys - Impact, missile etc.

	if (setDeath == DEATH_NULL && viewkeysallowed)
	{
		for(ptr = viewspec_list; ptr->viewcode; ptr++)
			if(Key_Tests.KeyPress3d(ptr->keynum))
			{
				(this->*(ptr->viewcode))();
			}

		Quick_ViewP	qvp;

		if (drawpolypit==TRUE && viewmodeselect==1)	qvp = fixedview_list;
		else										qvp = fixedview2_list;

		for (;qvp->viewcode;qvp++)
		{
			if(Key_Tests.KeyPress3d(qvp->keynum))
			{
				(this->*(qvp->viewcode))(qvp->qv_flags);
				break;
			}
		}
	}															//PD 14Aug97

	//Test for zoom/rotate keys

	Bool	zooming = FALSE;
	KeySteps=0;

	if ((setDeath != DEATH_NULL) && !Three_Dee.IsPaused())			//RDH 02Sep98
	{
		if ((setDeath != DEATH_SKID) && (setDeath != DEATH_AIRTOAIR))//DAW 03Sep98
		{														//RDH 02Sep98
			HandleZoom(ZR_ZoomIn);								//RDH 02Sep98
			zooming = TRUE;										//RDH 02Sep98
		}														//RDH 02Sep98

		HandleRotate(ZR_RotRght);
	}
 	else if (viewkeysallowed)
 	{
		//Now, selects a list of keys to scan based on the
		//value of 'viewmodeselect'
		if (viewmodeselect==1 && drawpolypit==TRUE)	ptr2 = viewrot2_list;
	 	else										ptr2 = viewrot_list;

		for(;ptr2->viewcode;ptr2++)
			if(Key_Tests.KeyHeld3d(ptr2->keynum))
			{
				(this->*(ptr2->viewcode)) (ptr2->zr_flags);
				zooming = TRUE;
			}
 	}

	if (viewNotAvailable)
		OverLay.TriggerMessage(COverlay::NOVIEWMESS);

	Bool quickviewselected=FALSE;

	if (!deathview && viewkeysallowed)
	{
		for (Quick_ViewP ptr3=quickview_list;ptr3->viewcode;ptr3++)
		{
			if(Key_Tests.KeyHeld3d(ptr3->keynum))
			{
				(this->*(ptr3->viewcode))(ptr3->qv_flags);
				quickviewselected=TRUE;
				break;
			}
		}
	}

	//Switch back to original view when keys are
	//released

	if (!quickviewselected && bupviewdrawrtn!=NULL)
	{
		viewdrawrtn=bupviewdrawrtn;
		viewnum=bupviewnum;										//PD 19Sep97
		viewnum.viewchanged=VC_SuccessfulChange;				//PD 22Sep97
		messagetime=FIVESECS100;								//PD 22Sep97
		drawpolypit=bupdrawpolypit;
		bupviewdrawrtn=NULL;
		straightback=TRUE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ControlViewDraw
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ControlViewDraw()
{
	//waypoint view shuffle
	if (Manual_Pilot.ControlledAC2)
	{
		WayPointPtr wpp=Manual_Pilot.ControlledAC2->waypoint;
		if (wpp!=waypoint && wpp)
		{
			if (trackeditem && trackeditem==(itemptr)wpp->prev)
				trackeditem=(itemptr)wpp;
			if (trackeditem2 && trackeditem2==(itemptr)wpp->prev)
				trackeditem2=(itemptr)wpp;
			waypoint=wpp;
		}
	}
	OverLay.SetViewVals(0,0,0);
	(this->*viewdrawrtn) ();
}

//-------------------------------------------------------------------------------
//						VIEW INITIALISATION ROUTINES
//-------------------------------------------------------------------------------

void ViewPoint::InitAIUnfriendly()
{
	drawSpecialFlags-=(drawSpecialFlags&VIEW_SPECIAL_MAP);
	drawmap = FALSE;
	viewnum.viewtarg=VT_AIUnfriendly;
	currentenemyitem=NULL;

	if (Manual_Pilot.ControlledAC2 && 
		Manual_Pilot.ControlledAC2->ai.unfriendly &&
		!Manual_Pilot.ControlledAC2->ai.unfriendly->Status.deadtime)
		currentenemyitem=Manual_Pilot.ControlledAC2->ai.unfriendly;

	if(!currentenemyitem) InitFlyingView();
	else
	{
		trackeditem2=currentenemyitem;
		if (!ModifyView()) InitFlyingView();
	}
}
void ViewPoint::InitEscortee()
{
	drawSpecialFlags-=(drawSpecialFlags&VIEW_SPECIAL_MAP);
	drawmap = FALSE;
	viewnum.viewtarg=VT_Escortee;
	currentfriendlyitem=NULL;

	if (Manual_Pilot.ControlledAC2 && !Manual_Pilot.ControlledAC2->Status.deadtime)
	{
		//ROD I need to find a pointer to the item that you want to track here!!

//		alt f2 view:
//		if Leader()
//				point to Leader()
//		else if fly.leadflight
//				point to fly.leadflight
//		else
//				Not available msg

		AirStrucPtr targ=Manual_Pilot.ControlledAC2->Leader();

		if (targ!=NULL)
		{
			if (!targ->Status.deadtime)	
				currentfriendlyitem=(itemptr)targ;
		}
		else 
		{
			targ=Manual_Pilot.ControlledAC2->fly.leadflight;
			if (targ!=NULL &&
				!targ->Status.deadtime)
				currentfriendlyitem=(itemptr)targ;
		}
	}

	if(!currentfriendlyitem) InitFlyingView();
	else
	{
		trackeditem2=currentfriendlyitem;
		if (!ModifyView()) InitFlyingView();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitFlyingView
//Author		Paul.   
//Date			Tue 3 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitFlyingView()
{
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
	viewnum.viewtarg = VT_Player;
	trackeditem2 = NULL;										//PD 14Nov96

	switch (viewnum.viewmode)
	{
		case VM_InPadlock:
		case VM_Inside:
			viewnum.viewmode = VM_Inside;
			break;
		case VM_OutPadlock:
		case VM_Track:
#ifndef NDEBUG
		case VM_OutRevPadlock:
#endif
			viewnum.viewmode = VM_Track;
			break;
		case VM_Satellite:
		case VM_NrSatellite:
		case VM_FlyBy:
		case VM_Chase:
		case VM_InsideCheat:
			break;
	}
	SetViewFromNum(viewnum);
	ResetZoomRotate(ZR_NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitPiloted
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitPiloted()
{
	viewnum.viewmode = VM_Inside;								//PD 19Jun96
	viewnum.viewtarg = VT_Player;								//PD 27Jun96
	trackeditem2 = NULL;
	previousvehicle = NULL;
	bupviewdrawrtn = NULL;										//PD 28Jan97
	viewdrawrtn = DrawInside;
	drawpolypit = TRUE;
	InitInside();												//PD 19Jun96
	CopyPositionHPR(trackeditem,this);						//DAW 21Feb96
	ClipInsideAngles();											//PD 17Jun96
	UpdateGlobalViewRec();										//PD 04Apr96
	AddViewRecInside();											//PD 14Jun96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstAC
//Author		Paul.   
//Date			Tue 2 Mar 1999
//------------------------------------------------------------------------------
itemptr ViewPoint::GetFirstAC()
{
	return itemptr(ACList);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNextAC
//Author		Paul.   
//Date			Tue 2 Mar 1999
//------------------------------------------------------------------------------
itemptr ViewPoint::GetNextAC(itemptr itemPtr)
{
	itemPtr=((MobileItem*)itemPtr)->nextmobile;
//	if (itemPtr==NULL)	itemPtr=ACList;
	return itemPtr;
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitEnemy
//LastModified:	PD 27Jun96
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitEnemy()
{
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98

	viewnum.viewtarg = VT_Enemy;								//PD 27Jun96

	Nationality	their_side=natenemy;;

	FormationItemPtr us;

	us = (FormationItemPtr )trackeditem;

//DEADCODE DAW 17/02/00 	switch(us->nationality)
//DEADCODE DAW 17/02/00 	{
//DEADCODE DAW 17/02/00 		case NAT_RED:
//DEADCODE DAW 17/02/00 			their_side = NAT_BLUE;
//DEADCODE DAW 17/02/00 			break;
//DEADCODE DAW 17/02/00 
//DEADCODE DAW 17/02/00 		case NAT_BLUE:
//DEADCODE DAW 17/02/00 			their_side = NAT_RED;
//DEADCODE DAW 17/02/00 			break;
//DEADCODE DAW 17/02/00 	}

	if(!currentenemyitem)
	{
		currentenemyrange=0;									//JIM 05Aug96
		currentenemyitem = GetFirstItem(ACList,
										their_side,
										currentenemyrange);
	}
	else
	{
		MobileItemPtr tempitem = (MobileItemPtr )currentenemyitem;

		if (nextentry || currentenemyitem->Status.deadtime)
		{
			currentenemyitem = GetNextItem(	ACList,
											tempitem,
											their_side,
											currentenemyrange);
			if (!currentenemyitem)
				currentenemyitem = GetFirstItem(ACList,
												their_side,
												currentenemyrange);
			viewnum.vieweestepped=TRUE;							//PD 22Nov96
		}
	}
	
	if(!currentenemyitem)
	{
		//Failed to locate an enemy aircraft
		InitFlyingView();
		viewNotAvailable=true;
	}
	else
	{
		trackeditem2 = currentenemyitem;

		//Select locked view if available

		if (!ModifyView())
			InitFlyingView();									//PD 03Sep96
	}
	nextentry=FALSE;											//PD 11Sep96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PInitEnemy
//Author		Paul.   
//Date			Wed 8 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::PInitEnemy()
{
//DeadCode AMM 01Jun98 	if (_DPlay.Implemented)	{ PInitFriendly(); return; }															//ARM 06Dec96

	viewnum.viewtarg = VT_Enemy;

	Nationality	their_side=natenemy;

	FormationItemPtr us;

	us = (FormationItemPtr )trackeditem;

//DEADCODE DAW 17/02/00 	their_side=us->nationality==NAT_BLUE?NAT_RED:NAT_BLUE;

	if(!currentenemyitem)
	{
		currentenemyrange=0;
		currentenemyitem = GetLastItem(	ACList,
										their_side,
										currentenemyrange);
	}
	else
	{
		MobileItemPtr tempitem = (MobileItemPtr )currentenemyitem;

		if (nextentry || currentenemyitem->Status.deadtime)
		{
			currentenemyitem = GetPrevItem(	ACList,
											tempitem,
											their_side,
											currentenemyrange);
			if (!currentenemyitem)
				currentenemyitem = GetLastItem(	ACList,
												their_side,
												currentenemyrange);
			viewnum.vieweestepped=TRUE;							//PD 22Nov96
		}
	}
	
	if(!currentenemyitem)
	{
		//Failed to locate an enemy aircraft
		InitFlyingView();										//PD 03Sep96
	}
	else
	{
		trackeditem2 = currentenemyitem;

		//Select locked view if available

		if (!ModifyView())
			InitFlyingView();									//PD 03Sep96
	}
	nextentry=FALSE;											//PD 11Sep96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitFriendly
//LastModified:	PD 27Jun96
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitFriendly()
{
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98

	FormationItemPtr us;

	viewnum.viewtarg = VT_Friendly;								//PD 27Jun96

	us = (FormationItemPtr )trackeditem;

	if(!currentfriendlyitem)
	{
		currentfriendlyitem = GetFirstItem(	ACList,
											us->nationality,
											currentfriendlyrange);
	}
	else
	{
		MobileItemPtr tempitem = (MobileItemPtr )currentfriendlyitem;

		if (nextentry || currentfriendlyitem->Status.deadtime)
		{
			currentfriendlyitem = GetNextItem(	ACList,
												tempitem,
												us->nationality,
												currentfriendlyrange);
			if (!currentfriendlyitem)
				currentfriendlyitem = GetFirstItem(	ACList,
													us->nationality,
													currentfriendlyrange);

			viewnum.vieweestepped=TRUE;							//PD 22Nov96
		}
	}

	if(!currentfriendlyitem)
	{
		//Failed to locate an enemy aircraft
		InitFlyingView();										//PD 03Sep96
		viewNotAvailable=true;
	}
	else
	{
		trackeditem2 = currentfriendlyitem;

		//Select locked view if available

		if(!ModifyView())
			InitFlyingView();									//PD 03Sep96
	}
	nextentry=FALSE;											//PD 11Sep96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PInitFriendly
//Author		Paul.   
//Date			Wed 8 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::PInitFriendly()
{
	FormationItemPtr us;

	viewnum.viewtarg = VT_Friendly;

	us = (FormationItemPtr )trackeditem;

	if(!currentfriendlyitem)
	{
		currentfriendlyitem = GetLastItem(	ACList,
											us->nationality,
											currentfriendlyrange);
	}
	else
	{
		MobileItemPtr tempitem = (MobileItemPtr )currentfriendlyitem;

		if (nextentry || currentfriendlyitem->Status.deadtime)
		{
			currentfriendlyitem = GetPrevItem(	ACList,
												tempitem,
												us->nationality,
												currentfriendlyrange);
			if (!currentfriendlyitem)
				currentfriendlyitem = GetLastItem(	ACList,
													us->nationality,
													currentfriendlyrange);

			viewnum.vieweestepped=TRUE;
		}
	}

	if(!currentfriendlyitem)
	{
		//Failed to locate an enemy aircraft
		InitFlyingView();
		viewNotAvailable=true;
	}
	else
	{
		trackeditem2 = currentfriendlyitem;

		//Select locked view if available

		if(!ModifyView())
			InitFlyingView();
	}
	nextentry=FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitGroundTarget
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//Version Notes:	DAW 23Oct96 - taken pauls version - lastver is deadcoded 
//
//------------------------------------------------------------------------------
void ViewPoint::InitGroundTarget()
{
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98

	//Waypoint target view code
 
	viewnum.viewtarg = VT_GroundTarg;
 
	if (!currentgndtargitem) ResetGroundTarget();

	if(!currentgndtargitem)
	{
			//Signal view not available
		viewNotAvailable=true;
	}
	else
	{
		if(trackeditem2!=currentgndtargitem)
 			trackeditem2 = currentgndtargitem;
 		else
		{
 			//Must want next waypoint in list
 			NextGroundTarget();
 			viewnum.vieweestepped=TRUE;						//PD 22Nov96
 			trackeditem2 = (itemptr )currentgndtargitem;
		}
		//Select locked view if available
		ModifyView();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PInitGroundTarget
//Author		Paul.   
//Date			Wed 8 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::PInitGroundTarget()
{
	//Waypoint target view code

	viewnum.viewtarg = VT_GroundTarg;

	if (!currentgndtargitem)	ResetGroundTarget();

	if(!currentgndtargitem)
	{
		//Signal view not available
	}
	else
	{
		if(trackeditem2!=currentgndtargitem)
			trackeditem2 = currentgndtargitem;
		else
		{
			//Must want next waypoint in list

			PrevGroundTarget();

			viewnum.vieweestepped=TRUE;						//PD 22Nov96
			trackeditem2 = (itemptr )currentgndtargitem;
		}

		//Select locked view if available
		
		ModifyView();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitWayPoint
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::RSetWP()
{
	if (viewnum.viewtarg==VT_WayPoint)
	{
		ResetWayPoint();
		if(currentwaypoint==NULL)
			trackeditem2=((AirStrucPtr)trackeditem)->ai.homebase;
		else
			trackeditem2=(itemptr )currentwaypoint;
	}
}

inline WayPointPtr getfirst(AirStrucPtr ac)
{
	WayPointPtr nwp=ac->waypoint;
	UNIQUE_ID uid=ac->uniqueID;

	if (nwp==NULL) return nwp;

	while (nwp->prev!=NULL) 
		nwp=nwp->prev;
	while(nwp!=ac->waypoint && (uid.count<nwp->skipunder || uid.count>nwp->skipover))
		nwp=nwp->next;
	return nwp;
}

inline WayPointPtr getnext(AirStrucPtr ac,WayPointPtr wp)
{
	UNIQUE_ID uid=ac->uniqueID;
	WayPointPtr nwp=wp;

	if (nwp==NULL) return getfirst(ac);

	nwp=nwp->next;
	while (nwp!=NULL && (uid.count<nwp->skipunder || uid.count>nwp->skipover))
		nwp=nwp->next;
	return nwp;
}

void ViewPoint::InitWayPoint()
{
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
	//if the waypoint info hasn't been set yet then do it now

	viewnum.viewtarg = VT_WayPoint;								//PD 27Jun96

	if(currentwaypoint==NULL)
		ResetWayPoint();

	//if the waypoint info still hasn't been set then this view must be invalid;

	if(currentwaypoint==NULL)
	{
		//Set for view of home base

		trackeditem2=((AirStrucPtr)trackeditem)->ai.homebase;
	}
	else
	{
		if((ItemBasePtr)*trackeditem2!=currentwaypoint && nextentry==FALSE)
			trackeditem2 = (itemptr )currentwaypoint;//dirty  //JIM 23/02/99
		else
		{
			currentwaypoint=getnext((AirStrucPtr)trackeditem,currentwaypoint);
			if (!currentwaypoint)
				trackeditem2=((AirStrucPtr)trackeditem)->ai.homebase;
			else
			{
				trackeditem2 = (itemptr )currentwaypoint;			//PD 25Nov96
				viewnum.vieweestepped=TRUE;							//PD 22Nov96
			}
		}
	}
	//Select locked view if available							//PD 09Dec96

	ModifyView();												//PD 09Dec96

	nextentry=FALSE;											//PD 11Sep96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PInitWayPoint
//Author		Paul.   
//Date			Wed 8 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::PInitWayPoint()
{
	//if the waypoint info hasn't been set yet then do it now

	viewnum.viewtarg = VT_WayPoint;

	if(currentwaypoint==NULL)	ResetWayPoint();

	//if the waypoint info still hasn't been set then this view must be invalid;

	if(currentwaypoint==NULL)
	{
		//Set for view of home base

		trackeditem2=((AirStrucPtr)trackeditem)->ai.homebase;
	}
	else
	{
		if((ItemBasePtr)*trackeditem2!=currentwaypoint && nextentry==FALSE)
			trackeditem2 = (itemptr )currentwaypoint;
		else
		{
			//Must want previous waypoint in list
			if(!currentwaypoint->prev)
			{
				//Go back to the real first waypoint?

				while (currentwaypoint->next)
					currentwaypoint=currentwaypoint->next;
			}
			else
			{
				currentwaypoint = currentwaypoint->prev;
			}
			trackeditem2 = (itemptr )currentwaypoint;
			viewnum.vieweestepped=TRUE;
		}
	}
	//Select locked view if available

	ModifyView();

	nextentry=FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitMessage
//Author		Paul.   
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitMessage()
{
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
	viewnum.viewtarg = VT_Message;
	currentmessageitem = GetFirstMessage();
	if (currentmessageitem==NULL) 
	{
		InitFlyingView();
		viewNotAvailable=true;
	}
	else
	{
		viewnum.vieweestepped=TRUE;
		trackeditem2 = currentmessageitem;
		if (!ModifyView())	InitFlyingView();
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ToggleEnemy
//Author		Paul.   
//Date			Thu 26 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ToggleEnemy()
{
 	if (viewnum.viewtarg==VT_Enemy)
	{
		InitFlyingView();
	}
	else
	{
		nextentry=FALSE;										//PD 28Jan97
		InitEnemy();
	}
}

//-------------------------------------------------------------------------------
//						VIEW RE-INITIALISATION ROUTINES
//-------------------------------------------------------------------------------

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetEnemy
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ResetEnemy()
{
//DeadCode AMM 01Jun98 	if (_DPlay.Implemented)										//PD 17Dec96
//DeadCode AMM 01Jun98 	{															//PD 17Dec96
//DeadCode AMM 01Jun98 		ResetFriendly();										//PD 17Dec96
//DeadCode AMM 01Jun98 		return;													//PD 17Dec96
//DeadCode AMM 01Jun98 	}															//PD 17Dec96

	Nationality	their_side=natenemy;

	FormationItemPtr us;

	us = (FormationItemPtr )trackeditem;

//DEADCODE DAW 17/02/00 	switch(us->nationality)
//DEADCODE DAW 17/02/00 	{
//DEADCODE DAW 17/02/00 		case NAT_RED:
//DEADCODE DAW 17/02/00 			their_side = NAT_BLUE;
//DEADCODE DAW 17/02/00 			break;
//DEADCODE DAW 17/02/00 
//DEADCODE DAW 17/02/00 		case NAT_BLUE:
//DEADCODE DAW 17/02/00 			their_side = NAT_RED;
//DEADCODE DAW 17/02/00 			break;
//DEADCODE DAW 17/02/00 	}
	currentenemyitem = GetFirstItem(ACList,
									their_side,
									currentenemyrange);

	if(!currentenemyitem)
	{
		//Failed to locate an enemy aircraft
		InitFlyingView();										//PD 03Sep96
		viewNotAvailable=true;
	}
	else
	{
		viewnum.vieweestepped=TRUE;								//PD 22Nov96
		trackeditem2 = currentenemyitem;

		if(viewnum.viewtarg!=VT_Enemy)							//PD 27Jan97
		{
			viewnum.viewtarg=VT_Enemy;
			if (!ModifyView())
				InitFlyingView();
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetFriendly
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ResetFriendly()
{
	FormationItemPtr us;

	us = (FormationItemPtr )trackeditem;

	currentfriendlyitem = GetFirstItem(	ACList,
										us->nationality,
										currentfriendlyrange);

	if(!currentfriendlyitem)
	{
		//Failed to locate an enemy aircraft
		InitFlyingView();										//PD 03Sep96
		viewNotAvailable=true;
	}
	else
	{
		viewnum.vieweestepped=TRUE;								//PD 22Nov96
		trackeditem2 = currentfriendlyitem;

		if (viewnum.viewtarg!=VT_Friendly)						//PD 27Jan97
		{
			viewnum.viewtarg = VT_Friendly;
			if (!ModifyView())
				InitFlyingView();
		}	
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ResetGroundTarget
// Date:		10/05/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void ViewPoint::ResetGroundTarget()
{
	ItemBasePtr		SGtarget=NULL;
	if (trackeditem->Status.size==AIRSTRUCSIZE)
	{
		SGtarget=AirStrucPtr(*trackeditem)->ai.unfriendly;
//DEADCODE DAW 12/05/99 #pragma warnmsg("TEMP fix: needs unfriendly copied up to seen AC in winmove")
//DEADCODE DAW 12/05/99 		SGtarget=Persons2::PlayerGhostAC->ai.unfriendly;

		if (SGtarget)
			if (SGtarget->Status.size==AIRSTRUCSIZE)
				SGtarget=NULL;
			else
				if (SGtarget->Status.size<ITEMSIZE)
					SGtarget=NULL;
	}
	if (!SGtarget && trackeditem->Status.size>=MOBILESIZE)
	{
		WayPointPtr w=MobileItemPtr(*trackeditem)->waypoint;		  //JIM 02/07/99
		if (w)
			if (w->wpname==0 || w->action==wpbombno)
				SGtarget=MobileItemPtr(*trackeditem)->waypoint->target;
//		while (SGtarget && SGtarget->Status.size==WAYPOINTSIZE)
//			SGtarget=WayPointPtr(*SGtarget)->target;
	}

//OK... got an SGT to trace.
//Now, the question is, what do you want to reset to?

//I am going for the prescribed target, here...

//DEADCODE DAW 11/05/99 	if (!SGtarget)
//DEADCODE DAW 11/05/99 		enemytoofar=TRUE;
//DEADCODE DAW 11/05/99 	else
	{
//DEADCODE DAW 11/05/99 		UniqueID SGT=ItemPtr(*SGtarget)->SGT;
//DEADCODE DAW 11/05/99 		if (!SGT)
//DEADCODE DAW 11/05/99 		{
//DEADCODE DAW 11/05/99 			SGT=SGtarget->uniqueID.count;
//DEADCODE DAW 11/05/99 		}
//DEADCODE DAW 11/05/99 		else
//DEADCODE DAW 11/05/99 		{
//DEADCODE DAW 11/05/99 			SGtarget=MobileItem::currworld->ConvertPtrUID(SGT);
//DEADCODE DAW 11/05/99 		}
//DEADCODE DAW 11/05/99 
//DEADCODE DAW 11/05/99 		//this if makes the SGT item be chosen first...
//DEADCODE DAW 11/05/99 		if (!SGtarget || ItemPtr(*SGtarget)->shape==EMPTY)
//DEADCODE DAW 11/05/99 		{	//scan for nearest item
//DEADCODE DAW 11/05/99 			Float skiprangeunder=-1.0;	//can't be returned by rangesquared
//DEADCODE DAW 11/05/99 			Float skiprangeover=Float(METRES50KM)*Float(METRES50KM);
//DEADCODE DAW 11/05/99 			SGtarget=NULL;
//DEADCODE DAW 11/05/99 			for (int uid=0;uid<IllegalSepID;uid++)
//DEADCODE DAW 11/05/99 			{
//DEADCODE DAW 11/05/99 				ItemBasePtr b=MobileItem::currworld->ConvertPtrUID(UniqueID(uid));
//DEADCODE DAW 11/05/99 				if (b && b->Status.size>=ITEMSIZE)
//DEADCODE DAW 11/05/99 				{
//DEADCODE DAW 11/05/99 					ItemPtr i=*b;
//DEADCODE DAW 11/05/99 					if (i->SGT==SGT && i->shape!=EMPTY && !i->Status.deadtime)
//DEADCODE DAW 11/05/99 					{
//DEADCODE DAW 11/05/99 						Float range=trackeditem->Distance3DSquared(&i->World);
//DEADCODE DAW 11/05/99 						if (range<skiprangeover && range>skiprangeunder)
//DEADCODE DAW 11/05/99 						{
//DEADCODE DAW 11/05/99 							SGtarget=i;
//DEADCODE DAW 11/05/99 							skiprangeover=range;
//DEADCODE DAW 11/05/99 						}
//DEADCODE DAW 11/05/99 					}
//DEADCODE DAW 11/05/99 				}
//DEADCODE DAW 11/05/99 			}
//DEADCODE DAW 11/05/99 		}
		if (!SGtarget)
			enemytoofar=TRUE;
		else
		{
			viewnum.vieweestepped=TRUE;								//PD 22Nov96
			currentgndtargitem = *SGtarget;
			GroundTargItem.Next= currentgndtargitem;
			if (currentgndtargitem->Status.size<=MOBILESIZE)
			{
				SLong gdx,gdy,gdz;
				int	livegroupelement=SHAPE.GetLiveElementPos(0,currentgndtargitem,gdx,gdy,gdz);
				if (livegroupelement && (gdx || gdy || gdz))
				{
					GroundTargItem.World=currentgndtargitem->World;
					GroundTargItem.World.X += gdx;
					GroundTargItem.World.Y += gdy;
					GroundTargItem.World.Z += gdz;

					currentgndtargitem = &GroundTargItem;
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////
//
// Function:    NextGroundTarget
// Date:		10/05/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void ViewPoint::NextGroundTarget()
{
	ItemBasePtr		SGtarget=NULL;
	if (trackeditem->Status.size==AIRSTRUCSIZE)
	{
		SGtarget=AirStrucPtr(*trackeditem)->ai.unfriendly;
//DEADCODE DAW 12/05/99 #pragma warnmsg("TEMP fix: needs unfriendly copied up to seen AC in winmove")
//DEADCODE DAW 12/05/99 		SGtarget=Persons2::PlayerGhostAC->ai.unfriendly;

		if (SGtarget)
			if (SGtarget->Status.size==AIRSTRUCSIZE)
				SGtarget=NULL;
			else
				if (SGtarget->Status.size<ITEMSIZE)
					SGtarget=NULL;
	}
	if (!SGtarget && trackeditem->Status.size>=MOBILESIZE)
	{
		WayPointPtr w=MobileItemPtr(*trackeditem)->waypoint;		  //JIM 02/07/99
		if (w)
			if (w->wpname==0 || w->action==wpbombno)
				SGtarget=MobileItemPtr(*trackeditem)->waypoint->target;
//		while (SGtarget && SGtarget->Status.size==WAYPOINTSIZE)
//			SGtarget=WayPointPtr(*SGtarget)->target;
	}

//OK... got an SGT to trace.
//As a reset has been requested, first I will try to access the SGT host
//Otherwise it will be the nearest member of the SGT

	if (!SGtarget)
	{
		if (currentgndtargitem == &GroundTargItem)
			SGtarget=currentgndtargitem->Next;
		else
			SGtarget=currentgndtargitem;
	}

	if (!SGtarget)
		enemytoofar=TRUE;
	else
	{
		Float skiprangeunder=-1.0;	//can't be returned by rangesquared
		Float skiprangeover=Float(METRES50KM)*Float(METRES50KM);

		UniqueID SGT=ItemPtr(*SGtarget)->SGT;
		if (!SGT)
		{
			SGT=SGtarget->uniqueID.count;
		}
		else
		{
			SGtarget=MobileItem::currworld->ConvertPtrUID(SGT);
		}

		//GET THE PREVIOUS RANGE - THAT IS THE MINIMUM RANGE
		{
			ItemBasePtr lasttarg=currentgndtargitem;
			if (currentgndtargitem == &GroundTargItem)
				lasttarg=currentgndtargitem->Next;				//DAW 20Jun99
			if (lasttarg)
				skiprangeunder=trackeditem->Distance3DSquared(&lasttarg->World);
		}

		forever
		{
			//GET THE SGT ITEM RANGE. THAT MAY BE THE MAX RANGE
			if (SGtarget && !(ItemPtr(*SGtarget)->shape==EMPTY))
			{
				int SGTrange=trackeditem->Distance3DSquared(&SGtarget->World);
				if (SGTrange>skiprangeunder && SGTrange<skiprangeover)
					skiprangeover=SGTrange;
				else
					SGtarget=NULL;
			}
			else
				SGtarget=NULL;

			//SCAN FOR NEAREST ITEM
			{
				for (int uid=0;uid<IllegalSepID;uid++)
				{
					ItemBasePtr b=MobileItem::currworld->ConvertPtrUID(UniqueID(uid));
					if (b && b->Status.size>=ITEMSIZE)
					{
						ItemPtr i=*b;
						if (i->SGT==SGT && i->shape!=EMPTY && !i->Status.deadtime)
						{
							Float range=trackeditem->Distance3DSquared(&i->World);
							if (range<skiprangeover && range>skiprangeunder)
							{
								SGtarget=i;
								skiprangeover=range;
							}
						}
					}
				}
			}
		breakif(SGtarget);
		breakif(skiprangeunder<0.0)
			//GO ROUND AGAIN WITH RANGE OF ZERO!
			{
				skiprangeover=skiprangeunder+1.0;
				skiprangeunder=-1.0;
				SGtarget=MobileItem::currworld->ConvertPtrUID(SGT);

			}
		}
		if (!SGtarget)
			enemytoofar=TRUE;
		else
		{
			viewnum.vieweestepped=TRUE;								//PD 22Nov96
			currentgndtargitem = *SGtarget;
			GroundTargItem.Next= currentgndtargitem;
			if (currentgndtargitem->Status.size<=MOBILESIZE)
			{
				SLong gdx,gdy,gdz;
				int	livegroupelement=SHAPE.GetLiveElementPos(0,currentgndtargitem,gdx,gdy,gdz);
				if (livegroupelement && (gdx || gdy || gdz))
				{
					GroundTargItem.World=currentgndtargitem->World;
					GroundTargItem.World.X += gdx;
					GroundTargItem.World.Y += gdy;
					GroundTargItem.World.Z += gdz;
					currentgndtargitem = &GroundTargItem;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    PrevGroundTarget
// Date:		10/05/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void ViewPoint::PrevGroundTarget()
{
	ItemBasePtr		SGtarget=NULL;
	if (trackeditem->Status.size==AIRSTRUCSIZE)
	{
		SGtarget=AirStrucPtr(*trackeditem)->ai.unfriendly;
//DEADCODE DAW 12/05/99 #pragma warnmsg("TEMP fix: needs unfriendly copied up to seen AC in winmove")
//DEADCODE DAW 12/05/99 		SGtarget=Persons2::PlayerGhostAC->ai.unfriendly;

		if (SGtarget)
			if (SGtarget->Status.size==AIRSTRUCSIZE)
				SGtarget=NULL;
			else
				if (SGtarget->Status.size<ITEMSIZE)
					SGtarget=NULL;
	}
	if (!SGtarget && trackeditem->Status.size>=MOBILESIZE)
	{
		WayPointPtr w=MobileItemPtr(*trackeditem)->waypoint;		  //JIM 02/07/99
		if (w)
			if (w->wpname==0 || w->action==wpbombno)
				SGtarget=MobileItemPtr(*trackeditem)->waypoint->target;
//		while (SGtarget && SGtarget->Status.size==WAYPOINTSIZE)
//			SGtarget=WayPointPtr(*SGtarget)->target;
	}

//OK... got an SGT to trace.
//As a reset has been requested, first I will try to access the SGT host
//Otherwise it will be the nearest member of the SGT

	if (!SGtarget)
	{
		if (currentgndtargitem == &GroundTargItem)
			SGtarget=currentgndtargitem->Next;
		else
			SGtarget=currentgndtargitem;
	}

	if (!SGtarget)
		enemytoofar=TRUE;
	else
	{
		Float skiprangeunder=-1.0;	//can't be returned by rangesquared
		Float skiprangeover=Float(METRES50KM)*Float(METRES50KM);

		UniqueID SGT=ItemPtr(*SGtarget)->SGT ;
		if (!SGT)
		{
			SGT=SGtarget->uniqueID.count;
		}
		else
		{
			SGtarget=MobileItem::currworld->ConvertPtrUID(SGT);
		}

		//GET THE PREVIOUS RANGE - THAT IS THE MAXIMUM RANGE
		{
			ItemBasePtr lasttarg=currentgndtargitem;
			if (currentgndtargitem == &GroundTargItem)
				lasttarg==currentgndtargitem->Next;
			if (lasttarg)
				skiprangeover=trackeditem->Distance3DSquared(&lasttarg->World);
		}

		forever
		{
			//GET THE SGT ITEM RANGE. THAT MAY BE THE MAX RANGE
			if (SGtarget && !(ItemPtr(*SGtarget)->shape==EMPTY))
			{
				int SGTrange=trackeditem->Distance3DSquared(&SGtarget->World);
				if (SGTrange>skiprangeunder && SGTrange<skiprangeover)
					skiprangeunder=SGTrange;
				else
					SGtarget=NULL;
			}
			else
				SGtarget=NULL;

			//SCAN FOR NEAREST ITEM
			{
				for (int uid=0;uid<IllegalSepID;uid++)
				{
					ItemBasePtr b=MobileItem::currworld->ConvertPtrUID(UniqueID(uid));
					if (b && b->Status.size>=ITEMSIZE)
					{
						ItemPtr i=*b;
						if (i->SGT==SGT && i->shape!=EMPTY && !i->Status.deadtime)
						{
							Float range=trackeditem->Distance3DSquared(&i->World);
							if (range<skiprangeover && range>skiprangeunder)
							{
								SGtarget=i;
								skiprangeover=range;
							}
						}
					}
				}
			}
		breakif(SGtarget);
		breakif(skiprangeover>=Float(METRES50KM)*Float(METRES50KM))
			//GO ROUND AGAIN WITH RANGE OF ZERO!
			{
				skiprangeunder=skiprangeover+1.0;
				skiprangeover=Float(METRES50KM)*Float(METRES50KM)+1.0;
				SGtarget=MobileItem::currworld->ConvertPtrUID(SGT);
			}
		}
		if (!SGtarget)
			enemytoofar=TRUE;
		else
		{
			viewnum.vieweestepped=TRUE;								//PD 22Nov96
			currentgndtargitem = *SGtarget;
			GroundTargItem.Next= currentgndtargitem;
			if (currentgndtargitem->Status.size<=MOBILESIZE)
			{
				SLong gdx,gdy,gdz;
				int	livegroupelement=SHAPE.GetLiveElementPos(0,currentgndtargitem,gdx,gdy,gdz);
				if (livegroupelement && (gdx || gdy || gdz))
				{
					GroundTargItem.World=currentgndtargitem->World;
					GroundTargItem.World.X += gdx;
					GroundTargItem.World.Y += gdy;
					GroundTargItem.World.Z += gdz;
					currentgndtargitem = &GroundTargItem;
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NextGroundTarget
//Author		Paul.   
//Date			Mon 14 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE DAW 10/05/99 void ViewPoint::NextGroundTarget()
//DEADCODE DAW 10/05/99 {
//DEADCODE DAW 10/05/99 	SLong		matchrange = visiblerange;
//DEADCODE DAW 10/05/99 	SLong		range;
//DEADCODE DAW 10/05/99 	SLong		deltax,deltay,deltaz;
//DEADCODE DAW 10/05/99 	SLong		gdx,gdy,gdz;
//DEADCODE DAW 10/05/99 	itemptr		selected = NULL;
//DEADCODE DAW 10/05/99 	ANGLES		dummy1,dummy2;
//DEADCODE DAW 10/05/99 	ANGLES		matchhdg;
//DEADCODE DAW 10/05/99 	SLong		crange = 0;
//DEADCODE DAW 10/05/99 	Bool		livegroupelement;

//DEADCODE DAW 10/05/99 	WayPointPtr	wpp;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	//Set crange to the distance to the currently viewed target
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	if (currentgndtargitem!=NULL)
//DEADCODE DAW 10/05/99 	{
//DEADCODE DAW 10/05/99 		deltax = trackeditem->World.X - currentgndtargitem->World.X;
//DEADCODE DAW 10/05/99 		deltay = trackeditem->World.Y - currentgndtargitem->World.Y;
//DEADCODE DAW 10/05/99 		deltaz = trackeditem->World.Z - currentgndtargitem->World.Z;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		Math_Lib.Intercept(	deltax,deltay,deltaz,
//DEADCODE DAW 10/05/99 							crange,
//DEADCODE DAW 10/05/99 							dummy1,dummy2);
//DEADCODE DAW 10/05/99 	}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	//Get the first waypoint for the current view item (if available)
//DEADCODE DAW 10/05/99 	switch(trackeditem->Status.size)
//DEADCODE DAW 10/05/99 	{
//DEADCODE DAW 10/05/99 		//Item types that don't posses waypoint information
//DEADCODE DAW 10/05/99 		default:
//DEADCODE DAW 10/05/99 		case RotatedSize:
//DEADCODE DAW 10/05/99 		case MovingSize:
//DEADCODE DAW 10/05/99 		case HPSize:
//DEADCODE DAW 10/05/99 		case HdgSize:
//DEADCODE DAW 10/05/99 		case ItemSize:
//DEADCODE DAW 10/05/99 			wpp = (WayPointPtr )NULL;
//DEADCODE DAW 10/05/99 			break;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		case MobileSize:
//DEADCODE DAW 10/05/99 		case TransientSize:
//DEADCODE DAW 10/05/99 		case FormationSize:
//DEADCODE DAW 10/05/99 		case ShipSize:
//DEADCODE DAW 10/05/99 		case AirStrucSize:
//DEADCODE DAW 10/05/99 			wpp = ((MobileItemPtr )trackeditem)->waypoint;
//DEADCODE DAW 10/05/99 			break;
//DEADCODE DAW 10/05/99 	}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	while (wpp)
//DEADCODE DAW 10/05/99 	{
//DEADCODE DAW 10/05/99 		if (wpp->target!=NULL)
//DEADCODE DAW 10/05/99 		{
//DEADCODE DAW 10/05/99 			itemptr	ibp;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 			ibp = (itemptr)wpp->target;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 			if (ibp!=currentgndtargitem
//DEADCODE DAW 10/05/99 				&&
//DEADCODE DAW 10/05/99 				ibp->shape!=EMPTY)
//DEADCODE DAW 10/05/99 			{
//DEADCODE DAW 10/05/99 				livegroupelement=FALSE;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 				if (ibp->Status.size==FORMATIONSIZE)
//DEADCODE DAW 10/05/99 				{
//DEADCODE DAW 10/05/99 					while (ibp->Status.deadtime)
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						formationitem* tmpip=*ibp;
//DEADCODE DAW 10/05/99 						tmpip=tmpip->follower;
//DEADCODE DAW 10/05/99 						ibp=(itemptr)tmpip;
//DEADCODE DAW 10/05/99 						if (ibp==NULL)							//PD 19Dec96
//DEADCODE DAW 10/05/99 							break;								//PD 19Dec96
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 					gdx=gdy=gdz=0;
//DEADCODE DAW 10/05/99 				}
//DEADCODE DAW 10/05/99 				else
//DEADCODE DAW 10/05/99 				{
//DEADCODE DAW 10/05/99 					livegroupelement=
//DEADCODE DAW 10/05/99 						SHAPE.GetLiveElementPos(0,ibp,gdx,gdy,gdz);
//DEADCODE DAW 10/05/99 					if (!livegroupelement)
//DEADCODE DAW 10/05/99 						ibp=NULL;
//DEADCODE DAW 10/05/99 				}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 				if (ibp)
//DEADCODE DAW 10/05/99 				{
//DEADCODE DAW 10/05/99 					deltax = gdx + trackeditem->World.X - ibp->World.X;
//DEADCODE DAW 10/05/99 					deltay = gdy + trackeditem->World.Y - ibp->World.Y;
//DEADCODE DAW 10/05/99 					deltaz = gdz + trackeditem->World.Z - ibp->World.Z;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 					Math_Lib.Intercept(	deltax,deltay,deltaz,
//DEADCODE DAW 10/05/99 										range,
//DEADCODE DAW 10/05/99 										dummy1,dummy2);
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 					if (range<matchrange)
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						matchrange = range;
//DEADCODE DAW 10/05/99 						matchhdg = dummy1;
//DEADCODE DAW 10/05/99 						crange = range;
//DEADCODE DAW 10/05/99 						if (!livegroupelement)
//DEADCODE DAW 10/05/99 							selected = (itemptr )ibp;
//DEADCODE DAW 10/05/99 						else
//DEADCODE DAW 10/05/99 						{
//DEADCODE DAW 10/05/99 							if ((gdx | gdy | gdz)==0)
//DEADCODE DAW 10/05/99 								selected=ibp;
//DEADCODE DAW 10/05/99 							else
//DEADCODE DAW 10/05/99 							{
//DEADCODE DAW 10/05/99 							 	GroundTargItem.World=ibp->World;	//PD 14Dec96
//DEADCODE DAW 10/05/99 								GroundTargItem.World.X += gdx;
//DEADCODE DAW 10/05/99 								GroundTargItem.World.Y += gdy;
//DEADCODE DAW 10/05/99 								GroundTargItem.World.Z += gdz;
//DEADCODE DAW 10/05/99 								selected = &GroundTargItem;			//PD 14Dec96
//DEADCODE DAW 10/05/99 							}
//DEADCODE DAW 10/05/99 						}
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 				}
//DEADCODE DAW 10/05/99 			}
//DEADCODE DAW 10/05/99 		}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		wpp = wpp->next;
//DEADCODE DAW 10/05/99 	}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	if (selected==NULL)
//DEADCODE DAW 10/05/99 	{
//DEADCODE DAW 10/05/99 		//Get the first waypoint for the current view item (if available)
//DEADCODE DAW 10/05/99 		switch(trackeditem->Status.size)
//DEADCODE DAW 10/05/99 		{
//DEADCODE DAW 10/05/99 			//Item types that don't posses waypoint information
//DEADCODE DAW 10/05/99 			default:
//DEADCODE DAW 10/05/99 			case RotatedSize:
//DEADCODE DAW 10/05/99 			case MovingSize:
//DEADCODE DAW 10/05/99 			case HPSize:
//DEADCODE DAW 10/05/99 			case HdgSize:
//DEADCODE DAW 10/05/99 			case ItemSize:
//DEADCODE DAW 10/05/99 				wpp = (WayPointPtr )NULL;
//DEADCODE DAW 10/05/99 				break;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 			case MobileSize:
//DEADCODE DAW 10/05/99 			case TransientSize:
//DEADCODE DAW 10/05/99 			case FormationSize:
//DEADCODE DAW 10/05/99 			case ShipSize:
//DEADCODE DAW 10/05/99 			case AirStrucSize:
//DEADCODE DAW 10/05/99 				wpp = ((MobileItemPtr )trackeditem)->waypoint;
//DEADCODE DAW 10/05/99 				break;
//DEADCODE DAW 10/05/99 		}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		if (wpp) while (wpp->prev) {wpp=wpp->prev;}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		while (wpp)
//DEADCODE DAW 10/05/99 		{
//DEADCODE DAW 10/05/99 			if (wpp->target!=NULL)
//DEADCODE DAW 10/05/99 			{
//DEADCODE DAW 10/05/99 				itemptr	ibp;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 				ibp = (itemptr)wpp->target;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 				if (ibp!=currentgndtargitem
//DEADCODE DAW 10/05/99 					&&
//DEADCODE DAW 10/05/99 					ibp->shape!=EMPTY)
//DEADCODE DAW 10/05/99 				{
//DEADCODE DAW 10/05/99 					livegroupelement=FALSE;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 					if (ibp->Status.size==FORMATIONSIZE)
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						while (ibp->Status.deadtime)
//DEADCODE DAW 10/05/99 						{
//DEADCODE DAW 10/05/99 							formationitem* tmpip=*ibp;
//DEADCODE DAW 10/05/99 							tmpip=tmpip->follower;
//DEADCODE DAW 10/05/99 							ibp=(itemptr)tmpip;
//DEADCODE DAW 10/05/99 							if (ibp==NULL)							//PD 19Dec96
//DEADCODE DAW 10/05/99 								break;								//PD 19Dec96
//DEADCODE DAW 10/05/99 						}
//DEADCODE DAW 10/05/99 						gdx=gdy=gdz=0;
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 					else
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						livegroupelement=
//DEADCODE DAW 10/05/99 							SHAPE.GetLiveElementPos(0,ibp,gdx,gdy,gdz);
//DEADCODE DAW 10/05/99 						if (!livegroupelement)
//DEADCODE DAW 10/05/99 							ibp=NULL;
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 					if (ibp)
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						deltax = gdx + trackeditem->World.X - ibp->World.X;
//DEADCODE DAW 10/05/99 						deltay = gdy + trackeditem->World.Y - ibp->World.Y;
//DEADCODE DAW 10/05/99 						deltaz = gdz + trackeditem->World.Z - ibp->World.Z;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 						Math_Lib.Intercept(	deltax,deltay,deltaz,
//DEADCODE DAW 10/05/99 											range,
//DEADCODE DAW 10/05/99 											dummy1,dummy2);
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 						if (range<matchrange)
//DEADCODE DAW 10/05/99 						{
//DEADCODE DAW 10/05/99 							matchrange = range;
//DEADCODE DAW 10/05/99 							matchhdg = dummy1;
//DEADCODE DAW 10/05/99 							crange = range;
//DEADCODE DAW 10/05/99 							if (!livegroupelement)
//DEADCODE DAW 10/05/99 								selected = (itemptr )ibp;
//DEADCODE DAW 10/05/99 							else
//DEADCODE DAW 10/05/99 							{
//DEADCODE DAW 10/05/99 								if ((gdx | gdy | gdz)==0)
//DEADCODE DAW 10/05/99 									selected=ibp;
//DEADCODE DAW 10/05/99 								else
//DEADCODE DAW 10/05/99 								{
//DEADCODE DAW 10/05/99 							 		GroundTargItem.World=ibp->World;//PD 14Dec96
//DEADCODE DAW 10/05/99 									GroundTargItem.World.X += gdx;
//DEADCODE DAW 10/05/99 									GroundTargItem.World.Y += gdy;
//DEADCODE DAW 10/05/99 									GroundTargItem.World.Z += gdz;
//DEADCODE DAW 10/05/99 									selected = &GroundTargItem;		//PD 14Dec96
//DEADCODE DAW 10/05/99 								}
//DEADCODE DAW 10/05/99 							}
//DEADCODE DAW 10/05/99 						}
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 				}
//DEADCODE DAW 10/05/99 			}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 			wpp = wpp->next;
//DEADCODE DAW 10/05/99 		}
//DEADCODE DAW 10/05/99 	}

//DEADCODE DAW 10/05/99 	if (selected==NULL)
//DEADCODE DAW 10/05/99 		ResetGroundTarget();
//DEADCODE DAW 10/05/99 	else
//DEADCODE DAW 10/05/99 		currentgndtargitem = selected;
//DEADCODE DAW 10/05/99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrevGroundTarget
//Author		Paul.   
//Date			Wed 8 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE DAW 10/05/99 void ViewPoint::PrevGroundTarget()
//DEADCODE DAW 10/05/99 {
//DEADCODE DAW 10/05/99 	SLong		matchrange = 0;
//DEADCODE DAW 10/05/99 	SLong		range;
//DEADCODE DAW 10/05/99 	SLong		deltax,deltay,deltaz;
//DEADCODE DAW 10/05/99 	SLong		gdx,gdy,gdz;
//DEADCODE DAW 10/05/99 	itemptr		selected = NULL;
//DEADCODE DAW 10/05/99 	ANGLES		dummy1,dummy2;
//DEADCODE DAW 10/05/99 	ANGLES		matchhdg;
//DEADCODE DAW 10/05/99 	SLong		crange = 0;
//DEADCODE DAW 10/05/99 	Bool		livegroupelement;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	WayPointPtr	wpp;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	//Set crange to the distance to the currently viewed target
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	if (currentgndtargitem!=NULL)
//DEADCODE DAW 10/05/99 	{
//DEADCODE DAW 10/05/99 		deltax = trackeditem->World.X - currentgndtargitem->World.X;
//DEADCODE DAW 10/05/99 		deltay = trackeditem->World.Y - currentgndtargitem->World.Y;
//DEADCODE DAW 10/05/99 		deltaz = trackeditem->World.Z - currentgndtargitem->World.Z;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		Math_Lib.Intercept(	deltax,deltay,deltaz,
//DEADCODE DAW 10/05/99 							crange,
//DEADCODE DAW 10/05/99 							dummy1,dummy2);
//DEADCODE DAW 10/05/99 	}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	//Get the first waypoint for the current view item (if available)
//DEADCODE DAW 10/05/99 	switch(trackeditem->Status.size)
//DEADCODE DAW 10/05/99 	{
//DEADCODE DAW 10/05/99 		//Item types that don't posses waypoint information
//DEADCODE DAW 10/05/99 		default:
//DEADCODE DAW 10/05/99 		case RotatedSize:
//DEADCODE DAW 10/05/99 		case MovingSize:
//DEADCODE DAW 10/05/99 		case HPSize:
//DEADCODE DAW 10/05/99 		case HdgSize:
//DEADCODE DAW 10/05/99 		case ItemSize:
//DEADCODE DAW 10/05/99 			wpp = (WayPointPtr )NULL;
//DEADCODE DAW 10/05/99 			break;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		case MobileSize:
//DEADCODE DAW 10/05/99 		case TransientSize:
//DEADCODE DAW 10/05/99 		case FormationSize:
//DEADCODE DAW 10/05/99 		case ShipSize:
//DEADCODE DAW 10/05/99 		case AirStrucSize:
//DEADCODE DAW 10/05/99 			wpp = ((MobileItemPtr )trackeditem)->waypoint;
//DEADCODE DAW 10/05/99 			break;
//DEADCODE DAW 10/05/99 	}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	while (wpp)
//DEADCODE DAW 10/05/99 	{
//DEADCODE DAW 10/05/99 		if (wpp->target!=NULL)
//DEADCODE DAW 10/05/99 		{
//DEADCODE DAW 10/05/99 			itemptr	ibp;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 			ibp = (itemptr)wpp->target;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 			if (ibp!=currentgndtargitem
//DEADCODE DAW 10/05/99 				&&
//DEADCODE DAW 10/05/99 				ibp->shape!=EMPTY)
//DEADCODE DAW 10/05/99 			{
//DEADCODE DAW 10/05/99 				livegroupelement=FALSE;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 				if (ibp->Status.size==FORMATIONSIZE)
//DEADCODE DAW 10/05/99 				{
//DEADCODE DAW 10/05/99 					while (ibp->Status.deadtime)
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						formationitem* tmpip=*ibp;
//DEADCODE DAW 10/05/99 						tmpip=tmpip->follower;
//DEADCODE DAW 10/05/99 						ibp=(itemptr)tmpip;
//DEADCODE DAW 10/05/99 						if (ibp==NULL)							//PD 19Dec96
//DEADCODE DAW 10/05/99 							break;								//PD 19Dec96
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 					gdx=gdy=gdz=0;
//DEADCODE DAW 10/05/99 				}
//DEADCODE DAW 10/05/99 				else
//DEADCODE DAW 10/05/99 				{
//DEADCODE DAW 10/05/99 					livegroupelement=
//DEADCODE DAW 10/05/99 						SHAPE.GetLiveElementPos(0,ibp,gdx,gdy,gdz);
//DEADCODE DAW 10/05/99 					if (!livegroupelement)
//DEADCODE DAW 10/05/99 						ibp=NULL;
//DEADCODE DAW 10/05/99 				}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 				if (ibp)
//DEADCODE DAW 10/05/99 				{
//DEADCODE DAW 10/05/99 					deltax = gdx + trackeditem->World.X - ibp->World.X;
//DEADCODE DAW 10/05/99 					deltay = gdy + trackeditem->World.Y - ibp->World.Y;
//DEADCODE DAW 10/05/99 					deltaz = gdz + trackeditem->World.Z - ibp->World.Z;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 					Math_Lib.Intercept(	deltax,deltay,deltaz,
//DEADCODE DAW 10/05/99 										range,
//DEADCODE DAW 10/05/99 										dummy1,dummy2);
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 					if (range>matchrange)
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						matchrange = range;
//DEADCODE DAW 10/05/99 						matchhdg = dummy1;
//DEADCODE DAW 10/05/99 						crange = range;
//DEADCODE DAW 10/05/99 						if (!livegroupelement)
//DEADCODE DAW 10/05/99 							selected = (itemptr )ibp;
//DEADCODE DAW 10/05/99 						else
//DEADCODE DAW 10/05/99 						{
//DEADCODE DAW 10/05/99 							if ((gdx | gdy | gdz)==0)
//DEADCODE DAW 10/05/99 								selected=ibp;
//DEADCODE DAW 10/05/99 							else
//DEADCODE DAW 10/05/99 							{
//DEADCODE DAW 10/05/99 							 	GroundTargItem.World=ibp->World;	//PD 14Dec96
//DEADCODE DAW 10/05/99 								GroundTargItem.World.X += gdx;
//DEADCODE DAW 10/05/99 								GroundTargItem.World.Y += gdy;
//DEADCODE DAW 10/05/99 								GroundTargItem.World.Z += gdz;
//DEADCODE DAW 10/05/99 								selected = &GroundTargItem;			//PD 14Dec96
//DEADCODE DAW 10/05/99 							}
//DEADCODE DAW 10/05/99 						}
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 				}
//DEADCODE DAW 10/05/99 			}
//DEADCODE DAW 10/05/99 		}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		wpp = wpp->next;
//DEADCODE DAW 10/05/99 	}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	if (selected==NULL)
//DEADCODE DAW 10/05/99 	{
//DEADCODE DAW 10/05/99 		//Get the first waypoint for the current view item (if available)
//DEADCODE DAW 10/05/99 		switch(trackeditem->Status.size)
//DEADCODE DAW 10/05/99 		{
//DEADCODE DAW 10/05/99 			//Item types that don't posses waypoint information
//DEADCODE DAW 10/05/99 			default:
//DEADCODE DAW 10/05/99 			case RotatedSize:
//DEADCODE DAW 10/05/99 			case MovingSize:
//DEADCODE DAW 10/05/99 			case HPSize:
//DEADCODE DAW 10/05/99 			case HdgSize:
//DEADCODE DAW 10/05/99 			case ItemSize:
//DEADCODE DAW 10/05/99 				wpp = (WayPointPtr )NULL;
//DEADCODE DAW 10/05/99 				break;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 			case MobileSize:
//DEADCODE DAW 10/05/99 			case TransientSize:
//DEADCODE DAW 10/05/99 			case FormationSize:
//DEADCODE DAW 10/05/99 			case ShipSize:
//DEADCODE DAW 10/05/99 			case AirStrucSize:
//DEADCODE DAW 10/05/99 				wpp = ((MobileItemPtr )trackeditem)->waypoint;
//DEADCODE DAW 10/05/99 				break;
//DEADCODE DAW 10/05/99 		}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		if (wpp) while (wpp->prev) {wpp=wpp->prev;}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 		while (wpp)
//DEADCODE DAW 10/05/99 		{
//DEADCODE DAW 10/05/99 			if (wpp->target!=NULL)
//DEADCODE DAW 10/05/99 			{
//DEADCODE DAW 10/05/99 				itemptr	ibp;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 				ibp = (itemptr)wpp->target;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 				if (ibp!=currentgndtargitem
//DEADCODE DAW 10/05/99 					&&
//DEADCODE DAW 10/05/99 					ibp->shape!=EMPTY)
//DEADCODE DAW 10/05/99 				{
//DEADCODE DAW 10/05/99 					livegroupelement=FALSE;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 					if (ibp->Status.size==FORMATIONSIZE)
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						while (ibp->Status.deadtime)
//DEADCODE DAW 10/05/99 						{
//DEADCODE DAW 10/05/99 							formationitem* tmpip=*ibp;
//DEADCODE DAW 10/05/99 							tmpip=tmpip->follower;
//DEADCODE DAW 10/05/99 							ibp=(itemptr)tmpip;
//DEADCODE DAW 10/05/99 							if (ibp==NULL)							//PD 19Dec96
//DEADCODE DAW 10/05/99 								break;								//PD 19Dec96
//DEADCODE DAW 10/05/99 						}
//DEADCODE DAW 10/05/99 						gdx=gdy=gdz=0;
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 					else
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						livegroupelement=
//DEADCODE DAW 10/05/99 							SHAPE.GetLiveElementPos(0,ibp,gdx,gdy,gdz);
//DEADCODE DAW 10/05/99 						if (!livegroupelement)
//DEADCODE DAW 10/05/99 							ibp=NULL;
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 					if (ibp)
//DEADCODE DAW 10/05/99 					{
//DEADCODE DAW 10/05/99 						deltax = gdx + trackeditem->World.X - ibp->World.X;
//DEADCODE DAW 10/05/99 						deltay = gdy + trackeditem->World.Y - ibp->World.Y;
//DEADCODE DAW 10/05/99 						deltaz = gdz + trackeditem->World.Z - ibp->World.Z;
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 						Math_Lib.Intercept(	deltax,deltay,deltaz,
//DEADCODE DAW 10/05/99 											range,
//DEADCODE DAW 10/05/99 											dummy1,dummy2);
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 						if (range>matchrange)
//DEADCODE DAW 10/05/99 						{
//DEADCODE DAW 10/05/99 							matchrange = range;
//DEADCODE DAW 10/05/99 							matchhdg = dummy1;
//DEADCODE DAW 10/05/99 							crange = range;
//DEADCODE DAW 10/05/99 							if (!livegroupelement)
//DEADCODE DAW 10/05/99 								selected = (itemptr )ibp;
//DEADCODE DAW 10/05/99 							else
//DEADCODE DAW 10/05/99 							{
//DEADCODE DAW 10/05/99 								if ((gdx | gdy | gdz)==0)
//DEADCODE DAW 10/05/99 									selected=ibp;
//DEADCODE DAW 10/05/99 								else
//DEADCODE DAW 10/05/99 								{
//DEADCODE DAW 10/05/99 							 		GroundTargItem.World=ibp->World;//PD 14Dec96
//DEADCODE DAW 10/05/99 									GroundTargItem.World.X += gdx;
//DEADCODE DAW 10/05/99 									GroundTargItem.World.Y += gdy;
//DEADCODE DAW 10/05/99 									GroundTargItem.World.Z += gdz;
//DEADCODE DAW 10/05/99 									selected = &GroundTargItem;		//PD 14Dec96
//DEADCODE DAW 10/05/99 								}
//DEADCODE DAW 10/05/99 							}
//DEADCODE DAW 10/05/99 						}
//DEADCODE DAW 10/05/99 					}
//DEADCODE DAW 10/05/99 				}
//DEADCODE DAW 10/05/99 			}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 			wpp = wpp->next;
//DEADCODE DAW 10/05/99 		}
//DEADCODE DAW 10/05/99 	}
//DEADCODE DAW 10/05/99 
//DEADCODE DAW 10/05/99 	if (selected==NULL)
//DEADCODE DAW 10/05/99 		ResetGroundTarget();
//DEADCODE DAW 10/05/99 	else
//DEADCODE DAW 10/05/99 		currentgndtargitem = selected;
//DEADCODE DAW 10/05/99 }
//DEADCODE DAW 10/05/99 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetWayPoint
//Author		Paul.   
//Date			Mon 19 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ResetWayPoint()
{
	//Get the first waypoint for the current view item (if available)
	switch(trackeditem->Status.size)
	{
		//Item types that don't posses waypoint information
		default:
		case RotatedSize:
		case MovingSize:
		case HPSize:
		case HdgSize:
		case ItemSize:
			currentwaypoint = (WayPointPtr )NULL;
			break;

		case MobileSize:
		case TransientSize:
		case FormationSize:
		case ShipSize:
		case AirStrucSize:
			currentwaypoint = ((MobileItemPtr )trackeditem)->waypoint;
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetMessage
//Author		Paul.   
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ResetMessage()
{

}

//-------------------------------------------------------------------------------
//						VIEW UPDATE ROUTINES
//-------------------------------------------------------------------------------

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawInside
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawInside()
{
	CopyPositionHPR(trackeditem,this);						//DAW 21Feb96
	UpdatePosWRTEye();
	this->reqhdg = -this->reqhdg;								//PD 05Apr96
	this->reqpitch = -this->reqpitch;							//PD 05Apr96
	this->reqroll = -this->reqroll;								//PD 05Apr96
	ClipInsideAngles();											//PD 17Jun96
	UpdateGlobalViewRec();										//PD 04Apr96
	AddViewRecInside();											//PD 14Jun96

	ViewCutType	oldviewcuttype = viewnum.viewcuttype;			//PD 02May96
	viewnum.viewcuttype = Instant;								//PD 02May96

	UpdateGlobalHPR();											//PD 12Apr96

	viewnum.viewcuttype = oldviewcuttype;						//PD 02May96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawQuick
//Author		Paul.   
//Date			Tue 28 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawQuick()
{
	View_RecP	temp;
	temp = currentviewrec;
	currentviewrec = quickviewrec;

	CopyPositionHPR(trackeditem,this);
	this->reqhdg = -this->reqhdg;
	this->reqpitch = -this->reqpitch;
	this->reqroll = -this->reqroll;
	UpdateGlobalViewRec();
	AddViewRecInside(false);									//DAW 02Sep99
	ViewCutType	oldviewcuttype = viewnum.viewcuttype;
	viewnum.viewcuttype = Instant;
	UpdateGlobalHPR();
	viewnum.viewcuttype = oldviewcuttype;

	currentviewrec = temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawQuick
//Author		Paul.   
//Date			Tue 28 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawFixed()
{
	View_RecP	temp;
	temp = currentviewrec;
	currentviewrec = fixedviewrec;

	CopyPositionHPR(trackeditem,this);
	this->reqhdg = -this->reqhdg;
	this->reqpitch = -this->reqpitch;
	this->reqroll = -this->reqroll;
	UpdateGlobalViewRec();
	AddViewRecInside();
	ViewCutType	oldviewcuttype = viewnum.viewcuttype;
	viewnum.viewcuttype = Instant;
	UpdateGlobalHPR();
	viewnum.viewcuttype = oldviewcuttype;

	currentviewrec = temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawInsideLostLock
//Author		Paul.   
//Date			Wed 23 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawInsideLostLock()
{
	ViewCutType	oldvctype;

	oldvctype = viewnum.viewcuttype;
	viewnum.viewcuttype = VSlow;

	CopyPositionHPR(trackeditem,this);
	this->reqhdg = -this->reqhdg;
	this->reqpitch = -this->reqpitch;
	this->reqroll = -this->reqroll;
	ClipInsideAngles();
	UpdateGlobalViewRec();
	AddViewRecInside();
	UpdateGlobalHPR();

	viewnum.viewcuttype=oldvctype;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawInsideFwd
//Author		Paul.   
//Date			Thu 20 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawInsideFwd()
{
	CopyPositionHPR(trackeditem,this);
	this->reqhdg = -this->reqhdg;
	this->reqpitch = -this->reqpitch;
	this->reqroll = -this->reqroll;
	ResetZoomRotate((ZmRtFlags)NULL);							//PD 25Aug96
	ClipInsideAngles();
	UpdateGlobalViewRec();
	AddViewRecInside();
	ViewCutType	oldviewcuttype = viewnum.viewcuttype;
	viewnum.viewcuttype = Instant;
	UpdateGlobalHPR();
	viewnum.viewcuttype = oldviewcuttype;						//PD 25Aug96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawInsideCheat
//Author		Paul.   
//Date			Mon 17 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawInsideCheat()
{
	CopyPositionHPR(trackeditem,this);
	//this->World.Y;
	this->reqhdg = -this->reqhdg;
	this->reqpitch = -this->reqpitch;
	this->reqroll = -this->reqroll;
	ViewCutType	oldviewcuttype = viewnum.viewcuttype;
	viewnum.viewcuttype = Instant;
	UpdateGlobalHPR();
	viewnum.viewcuttype = oldviewcuttype;
}

ANGLES	lastthdg,lasttpitch,lasttroll;
Bool	viewislocked=FALSE;

bool 	padlockisoutside;
ANGLES	lasthdg=ANGLES_0Deg,lastpitch=ANGLES_0Deg;
ANGLES	currinterceptpitch,currintercepthdg;		//current values when moving from one view to another
ANGLES	targetinterceptpitch,targetintercepthdg;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawInPadlock
//LastModified:	PD 05Jul96
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//#define NEW_PADLOCK

//#ifdef NEW_PADLOCK
void ViewPoint::DrawInPadlock()
{
	//Angle limits
	const ANGLES PITCH_UNDER_AC=ANGLES_330Deg;
	const ANGLES PITCH_BELOW_RIM_CLIP=ANGLES_350Deg;
//DeadCode CSB 09/07/99		const ANGLES PITCH_ZONE_PITCH=(Angles)(UWord(ANGLES_90Deg)-UWord(ANGLES_20Deg)-UWord(ANGLES_1Deg));
	const ANGLES PITCH_ZONE_PITCH=(Angles)(UWord(ANGLES_90Deg)-UWord(ANGLES_25Deg));	//CSB 09/07/99	
	const ANGLES HEADING_ZONE_HDG_CLIP_LO=ANGLES_160Deg;
	const ANGLES HEADING_ZONE_HDG_CLIP_HI=(Angles)(int(ANGLES_190Deg)+int(ANGLES_10Deg));
	const SWord TRACKING_TIME=1*100;	//1 second switch

	//View flags
	const bool autopadlockenabled=Save_Data.gamedifficulty[GD_AUTOPADLOCKTOG]?true:false;
	const bool padlockonlyifvisible=Save_Data.gamedifficulty[GD_PADLOCKONLYWHENVIS]?true:false;

	if (autopadlockenabled)
	{
		DrawInPadlockB();
		return;
	}

	drawpolypit=TRUE;

	//Abort the view if tracked item is NULL
	if (!trackeditem2)
	{
		trackeditem2=NULL;
		viewnum.viewmode = VM_Inside;
		InitInside();
		OverLay.SetViewVals(0,0,0);
		return;
	}

	//Update the view position to match the piloted a/c
	CopyPosition(trackeditem,this);
	UpdatePosWRTEye();

	//Get delta world x,y & z coordinates from viewpoint to tracked item
	SLong deltax,deltay,deltaz;

	if (trackeditem2->Status.size==WAYPOINTSIZE)
	{
		Coords3D* tp=::FindDesPos(*trackeditem2);
		deltax=tp->X;
		deltay=tp->Y;
		deltaz=tp->Z;
	}
	else
	{
		deltax=trackeditem2->World.X;
		deltay=trackeditem2->World.Y;
		deltaz=trackeditem2->World.Z;
	}
	deltax-=World.X;
	deltay-=World.Y;
	deltaz-=World.Z;

	//Set up view display information
	{
	SLong viewitemrange;
	ANGLES temp1,temp2;
	Math_Lib.HighIntercept(deltax,deltay,deltaz,viewitemrange,temp1,temp2);
	OverLay.SetViewVals(viewitemrange,temp1-MobileItemPtr(trackeditem)->hdg,deltay);
	}

	ANGLES intercepthdg,interceptpitch,interceptroll(ANGLES_0Deg);

		//Get intercept hdg & pitch in piloted a/c coordinate system
	RelativeIntercept(trackeditem,trackeditem2,intercepthdg,interceptpitch);

	//Decide whether the target is visible & how best to look at it
	//Step (1) is the target below the players aircraft
	if (interceptpitch>>ANGLES_90Deg && interceptpitch<<PITCH_UNDER_AC)
	{
		if (autopadlockenabled)
		{
			//Use outside padlock view instead
			padlockisoutside=true;
			drawpolypit=FALSE;
			DrawOutPadlock();
			targetintercepthdg=
				targetinterceptpitch=ANGLES_0Deg;
			return;
		}
		else if (padlockonlyifvisible)
		{
			//Cancel padlock 'cos the traced item is not visible anymore
			trackeditem2=NULL;
			viewnum.viewmode=VM_Inside;
			InitInside();
			targetintercepthdg=
				targetinterceptpitch=ANGLES_0Deg;
			return;
		}
	}

	//Step (2) check whether the pitch is low enough to require clipping
	if (interceptpitch>>ANGLES_90Deg && interceptpitch<<PITCH_BELOW_RIM_CLIP)
		interceptpitch=PITCH_BELOW_RIM_CLIP;

	//Step (3) check whether the target is in the head up zone
	bool isincentralarea;
	if (intercepthdg<<ANGLES_270Deg && intercepthdg>>ANGLES_90Deg)
		isincentralarea=(interceptpitch>>PITCH_ZONE_PITCH && interceptpitch<<ANGLES_90Deg)?true:false;
	else 
		isincentralarea=false;

	if (isincentralarea)
	{
		//we want the pilot to be looking forwards but
		//with his head tilted back until the target is 
		//in view
		ANGLES newhdg,newpitch;
//		newhdg=intercepthdg+ANGLES_180Deg;
//		newpitch=ANGLES_180Deg-interceptpitch;

		newhdg=ANGLES_0Deg;
		SWord sh,ch;
		Math_Lib.high_sin_cos(intercepthdg,sh,ch);							//PD 23Feb96
		newpitch=(Angles)(ANGLES_90Deg - ((ANGLES_90Deg - interceptpitch)*ch)/ANGLES_FRACT);

		intercepthdg=newhdg;
		interceptpitch=newpitch;
	}
	else
	{
		//standard clipping for intercept heading
		if (intercepthdg>>ANGLES_180Deg && intercepthdg<<HEADING_ZONE_HDG_CLIP_HI)
			intercepthdg=HEADING_ZONE_HDG_CLIP_HI;
		else if (!(intercepthdg>>ANGLES_180Deg) && intercepthdg>>HEADING_ZONE_HDG_CLIP_LO)
			intercepthdg=HEADING_ZONE_HDG_CLIP_LO;
	}

	SWord	deltaangle,deltaanglesign;
	ANGLES	targethdg=intercepthdg;
	ANGLES	targetpitch=interceptpitch;

	deltaangle=targethdg-targetintercepthdg;

	if (deltaangle>=0)	
		deltaanglesign=1;
	else
	{
		deltaanglesign=-1; deltaangle=-deltaangle;
	}
//DEADCODE CSB 09/03/00		if (deltaangle>ANGLES_1Deg && deltaangle>viewcodeframetime)
//DEADCODE CSB 09/03/00			deltaangle=2+((deltaangle*viewcodeframetime)/25);
	if(deltaangle > 256 * viewcodeframetime)
		deltaangle = 256 * viewcodeframetime;

	targethdg=(Angles)(targetintercepthdg+deltaanglesign*deltaangle);

	deltaangle=targetpitch-targetinterceptpitch;
	if (deltaangle>=0)
		deltaanglesign=1;
	else
	{
		deltaanglesign=-1; deltaangle=-deltaangle;
	}

//DEADCODE CSB 09/03/00		if (deltaangle>ANGLES_1Deg && deltaangle>viewcodeframetime)
//DEADCODE CSB 09/03/00			deltaangle=2+((deltaangle*viewcodeframetime)/25);
	if(deltaangle > 512 * viewcodeframetime)
		deltaangle = 512 * viewcodeframetime;

	targetpitch=(Angles)(targetinterceptpitch+deltaanglesign*deltaangle);

	intercepthdg=targetintercepthdg=targethdg;
	interceptpitch=targetinterceptpitch=targetpitch;

	_matrix.TransformAngles(((MobileItemPtr )trackeditem)->hdg,
							((MobileItemPtr )trackeditem)->pitch,
							((MobileItemPtr )trackeditem)->roll,
							intercepthdg,
							interceptpitch,
							interceptroll);

	reqhdg=(ANGLES)-intercepthdg;
	reqpitch=(ANGLES)-interceptpitch;
	reqroll=(ANGLES)-interceptroll;

	ViewCutType	oldviewcuttype=viewnum.viewcuttype;
	viewnum.viewcuttype=Instant;
	UpdateGlobalHPR();
	viewnum.viewcuttype=oldviewcuttype;
}
//#else
void ViewPoint::DrawInPadlockB()
{
	#define	HICOLORANGLE	ANGLES_15Deg

	SLong	deltax, deltay, deltaz;

	ANGLES	hdgint, pitchint, rollint;

	ANGLES	relhdg, relpitch;

	ANGLES	intercepthdg, interceptpitch, interceptroll;

	ANGLES	usehdg, usepitch, useroll;

	ANGLES	targethdg, targetpitch;

	ANGLES 	temp1,temp2;

	ViewCutType	oldviewcuttype;
	
	Bool	pitchvisible,hdgvisible,special;
	
	Bool	targetisvisible;//=TRUE;

	drawpolypit = TRUE;											//PD 08Jul97

	//Test to see if the target aircraft is visible

	if	(trackeditem2)
	{
		CopyPosition(trackeditem,this);
		UpdatePosWRTEye();

		//Delta world x,y & z coordinates from a/c to tracked item
		if (trackeditem2->Status.size==WAYPOINTSIZE)
		{
			Coords3D*	tp=::FindDesPos(*trackeditem2);
			deltax = tp->X - this->World.X;
			deltay = tp->Y - this->World.Y;
			deltaz = tp->Z - this->World.Z;
		}
		else
		{
			deltax = trackeditem2->World.X - this->World.X;
			deltay = trackeditem2->World.Y - this->World.Y;
			deltaz = trackeditem2->World.Z - this->World.Z;
		}

		//Find the heading and pitch to the target
		RelativeIntercept(trackeditem,trackeditem2,intercepthdg,interceptpitch);
		interceptroll = ANGLES_0Deg;

		temp1=intercepthdg;
		temp2=interceptpitch;

		//Get the heading and pitch of the viewer

		hdgint = ((MobileItemPtr )trackeditem)->hdg;
		pitchint = ((MobileItemPtr )trackeditem)->pitch;
		rollint = ((MobileItemPtr )trackeditem)->roll;

		relpitch = interceptpitch;
		relhdg = intercepthdg;

		//hdgint,pitchint,rollint are now the angles required to 
		//look directly at the tracked item.

		//Modified so that if either the heding or pitch is in range
		//then the lock continues to remain active

		UWord	rhdg,rpitch;
		UWord	hdg_lo,hdg_hi;
		UWord	pitch_lo,pitch_hi;
		UWord	pitch_hi_clip;
		UWord	hdg_special_lo,hdg_special_hi;

		rhdg = (UWord)relhdg;
		rpitch = (UWord)relpitch;

		hdg_special_lo=UWord(ANGLES_180Deg)-UWord(ANGLES_10Deg);
		hdg_special_hi=UWord(ANGLES_180Deg)+UWord(ANGLES_10Deg);

		//Set lower and upper limits for the
		//visible cone

		if (bPadlockOut==FALSE)
		{
			if (Save_Data.gamedifficulty[GD_AUTOPADLOCKTOG])
			{
				hdg_hi = dhdgstrt;
				hdg_lo = dhdgend;
			}
			else
			{
				hdg_hi = (UWord)ANGLES_170Deg;
				hdg_lo = (UWord)ANGLES_180Deg+(UWord)ANGLES_10Deg;
			}

			pitch_lo = dpitchstrt;
			pitch_hi = dpitchend;
		}
		else
		{
			hdg_hi = (UWord)ANGLES_30Deg;
			hdg_lo = (UWord)ANGLES_330Deg;

			pitch_lo = (UWord)ANGLES_30Deg;
			pitch_hi = (UWord)ANGLES_330Deg;
		}

		pitch_hi_clip = (UWord)ANGLES_350Deg;//PD 19Nov97

		//Do visibility tests and angle clipping
		
		targetisvisible = FALSE;
		pitchvisible = FALSE;
		hdgvisible = FALSE;
		special=FALSE;
		//check for special case hdg & pitch stuff

		if (rhdg>=hdg_special_lo && rhdg<=hdg_special_hi)
		{
			special=hdgvisible=TRUE;
			rhdg+=ANGLES_180Deg;
			bool checked=false;
			if (rpitch>0x8000)
			{
				checked=true;
				pitchvisible=FALSE;
			}
			rpitch+=ANGLES_90Deg;
			pitch_lo=ANGLES_90Deg;

			//pitch is more complicated...
			//if rpitch is between pitch_lo and pitch_hi then set the pitch visible flag to TRUE
			//if rpitch is outside the range pitch_lo to pitch_hi_clip then clip it to this range
			if (!checked)
			{
				if (rpitch<=pitch_lo || rpitch>=pitch_hi)	pitchvisible=TRUE;
				if (!(rpitch<=pitch_lo || rpitch>=pitch_hi_clip))
				{
					if (rpitch<UWord(ANGLES_180Deg))	rpitch=pitch_lo;
					else								rpitch=pitch_hi_clip;
				}
			}
		}
		else
		{
			//clip heading and pitch angles

			if (rhdg<=hdg_hi || rhdg>=hdg_lo)	hdgvisible=TRUE;	//no clip so flag heading is visible
			else if (rhdg<UWord(ANGLES_180Deg))	rhdg=hdg_hi;
			else								rhdg=hdg_lo;

			//pitch is more complicated...
			//if rpitch is between pitch_lo and pitch_hi then set the pitch visible flag to TRUE
			//if rpitch is outside the range pitch_lo to pitch_hi_clip then clip it to this range
			if (rpitch<=pitch_lo || rpitch>=pitch_hi)	pitchvisible=TRUE;
			if (!(rpitch<=pitch_lo || rpitch>=pitch_hi_clip))
			{
				if (rpitch<UWord(ANGLES_180Deg))	rpitch=pitch_lo;
				else								rpitch=pitch_hi_clip;
			}
		}


		if (bPadlockOut==TRUE)
		{
			if (pitchvisible && hdgvisible)	targetisvisible = TRUE;
		}
		else
		{
			if (!special)
			{
				if (pitchvisible || hdgvisible)	targetisvisible = TRUE;
			}
			else
			{
				if (pitchvisible && hdgvisible)	targetisvisible = TRUE;
			}
		}

		relpitch = (Angles)rpitch;
		relhdg = (Angles)rhdg;

		targetpitch = interceptpitch = relpitch;
		targethdg = intercepthdg = relhdg;

		_matrix.TransformAngles(hdgint,pitchint,rollint,
								intercepthdg,interceptpitch,interceptroll);

		//Now we know if the target is potentially visible and the
		//view angles required to look directly at the item are
		//contained in ...
		//
		//	intercepthdg, interceptpitch and interceptroll
		//
		if (Save_Data.gamedifficulty[GD_PADLOCKONLYWHENVIS] && WhichWay(trackeditem2)!=0)
		{
			trackeditem2=NULL;
			viewnum.viewmode = VM_Inside;
			InitInside();
			lastthdg = lasttpitch = ANGLES_0Deg;
		}
		else
		{
			viewislocked = FALSE;

			if (Save_Data.gamedifficulty[GD_AUTOPADLOCKTOG])	//Auto toggle ON
			{
				if (targetisvisible==FALSE)
				{
					bPadlockOut = TRUE;
					drawpolypit = FALSE;
					DrawOutPadlock();
					return;
				}
				else
				{
					if (bPadlockOut==TRUE)	bAllowInstantUpdate=TRUE;//PD 14Oct97

					bPadlockOut = FALSE;
				}
			}

			if (viewnum.viewcuttype!=Instant && viewislocked==FALSE && bAllowInstantUpdate==FALSE)
			{
				SWord	deltaangle,deltaanglesign;

				deltaangle = targethdg - lastthdg;

				if (deltaangle>=0)
					deltaanglesign=1;
				else
				{
					deltaanglesign=-1; deltaangle=-deltaangle;
				}

				if (deltaangle>ANGLES_1Deg && deltaangle>viewcodeframetime)
					deltaangle = 2 + ((deltaangle*viewcodeframetime)/25);//PD 27Jan97

				targethdg = (Angles)(lastthdg + deltaanglesign*deltaangle);

				deltaangle = targetpitch - lasttpitch;

				if (deltaangle>=0)
					deltaanglesign=1;
				else
				{
					deltaanglesign=-1; deltaangle=-deltaangle;
				}

				if (deltaangle>ANGLES_1Deg && deltaangle>viewcodeframetime)
					deltaangle = 2 + ((deltaangle*viewcodeframetime)/25);//PD 27Jan97

				targetpitch = (Angles)(lasttpitch + deltaanglesign*deltaangle);
			}

			lastthdg=targethdg;
			lasttpitch=targetpitch;

			intercepthdg = targethdg;
			interceptpitch = targetpitch;
			interceptroll = ANGLES_0Deg;

			//Get the heading and pitch of the viewer

			hdgint = ((MobileItemPtr )trackeditem)->hdg;
			pitchint = ((MobileItemPtr )trackeditem)->pitch;
			rollint = ((MobileItemPtr )trackeditem)->roll;

			_matrix.TransformAngles(hdgint,pitchint,rollint,
									intercepthdg,interceptpitch,interceptroll);

			usehdg = intercepthdg;
			usepitch = interceptpitch;
			useroll = interceptroll;

			this->reqhdg = (ANGLES)-usehdg;
			this->reqpitch = (ANGLES)-usepitch;
			this->reqroll = (ANGLES)-useroll;

			oldviewcuttype=viewnum.viewcuttype;
			viewnum.viewcuttype=Instant;

			UpdateGlobalHPR();

			viewnum.viewcuttype=oldviewcuttype;
		}
	}
	else
	{
//dead		enemydirection=0;
		trackeditem2=NULL;
		viewnum.viewmode = VM_Inside;
		InitInside();
	}

	if (trackeditem2!=NULL && trackeditem!=NULL)
	{
		SLong	dx=trackeditem2->World.X-trackeditem->World.X,
				dy=trackeditem2->World.Y-trackeditem->World.Y,
				dz=trackeditem2->World.Z-trackeditem->World.Z;

		if (trackeditem2->Status.size==WAYPOINTSIZE)			//RDH 07Oct96
		{														//RDH 07Oct96
			Coords3D*	tp=::FindDesPos(*trackeditem2);			//RDH 07Oct96
			dx = tp->X - trackeditem->World.X;						//RDH 07Oct96
			dy = tp->Y - trackeditem->World.Y;						//RDH 07Oct96
			dz = tp->Z - trackeditem->World.Z;						//RDH 07Oct96
		}														//RDH 07Oct96
		Math_Lib.HighIntercept(dx,dy,dz,viewitemrange,temp1,temp2);
		OverLay.SetViewVals(viewitemrange,temp1-MobileItemPtr(trackeditem)->hdg,dy);
	}
	else OverLay.SetViewVals(0,0,0);
}
//#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WhichWay
//Author		Paul.   
//Date			Tue 26 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte ViewPoint::WhichWay(itemptr targetitemp)
{
	UByte	retval;

	const SWord	phdg 	= (SWord )ANGLES_35Deg;
	const SWord	nhdg 	= ANGLES_0Deg-(SWord )ANGLES_35Deg;
	const SWord ppitch	= (SWord )ANGLES_30Deg;
	const SWord npitch	= ANGLES_0Deg-(SWord )ANGLES_30Deg;

	MATRIX		tmat;
	MATRIX_PTR	tmatp = &tmat;

	_matrix.generate(this->hdg,this->pitch,this->roll,tmatp);

	SLong	dx,dy,dz;

	dx = trackeditem2->World.X - this->World.X;
	dy = trackeditem2->World.Y - this->World.Y;
	dz = trackeditem2->World.Z - this->World.Z;

	(void )_matrix.transform(tmatp,dx,dy,dz);

	SWord	hdgi,pitchi;

	SLong	range;

	Math_Lib.HighIntercept(dx,-dy,dz,range,hdgi,pitchi);

	if (hdgi>phdg)
	{
		if (pitchi>ppitch)
			retval=4;
		else
		{
			if (pitchi<npitch)
				retval=2;
			else
				retval=3;
		}
	}
	else
	{
		if (hdgi<nhdg)
		{
			if (pitchi>ppitch)
				retval=6;
			else
			{
				if (pitchi<npitch)
					retval=8;
				else
					retval=7;
			}
		}
		else
		{
			if (pitchi>ppitch)
				retval=5;
			else
			{
				if (pitchi<npitch)
					retval=1;
				else
					retval=0;
			}
		}
	}

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RelativeIntercept
//Author		Paul.   
//Date			Sat 7 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::RelativeIntercept(itemptr srcp,itemptr trgp,
									ANGLES& inthdg,ANGLES& intptch)
{
	MobileItemPtr	msrcp,mtrgp;
	FPMATRIX			tmat;
	FPMATRIX_PTR		tmatp = &tmat;

	msrcp = (MobileItemPtr )srcp;
	mtrgp = (MobileItemPtr )trgp;

	_matrix.generate(ANGLES_0Deg-(msrcp->hdg),ANGLES_0Deg-(msrcp->pitch),ANGLES_0Deg-(msrcp->roll),tmatp);

	IFShare	dx,dy,dz;

	dx.i = (mtrgp->World.X - msrcp->World.X);//>>8;//PD 9/12/98
	dy.i = (mtrgp->World.Y - msrcp->World.Y);//>>8;//PD 9/12/98
	dz.i = (mtrgp->World.Z - msrcp->World.Z);//>>8;//PD 9/12/98

	_matrix.transform(tmatp,dx,dy,dz);

	dx.i=dx.f;
	dy.i=dy.f;
	dz.i=dz.f;

	ANGLES	hdgi,pitchi;

	SLong	range;

	Math_Lib.HighIntercept(dx.i,dy.i,dz.i,range,hdgi,pitchi);

	inthdg = hdgi;
	intptch = pitchi;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawTrack
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawTrack()
{
 	CopyPositionHP(trackeditem,this);							//RDH 03Jun96
//keep next line, good for side slip landings					//RDH 03Jun96
//	CopyPositionHPVel(trackeditem,this);						//RDH 03Jun96
	this->reqhdg = -this->reqhdg;								//PD 05Apr96
	this->reqpitch = -this->reqpitch;							//PD 05Apr96
	this->reqroll = -this->reqroll;								//PD 05Apr96
	UpdateGlobalViewRec();										//PD 04Apr96
	AddViewRec();
	UpdateGlobalHPR();											//PD 12Apr96
	AddZoom();
	AddCameraWobble();											//PD 29Feb96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawOutside
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawOutside()
{
	CopyPosition(trackeditem,this);
	UpdateGlobalViewRec();										//PD 04Apr96
	AddViewRec();
	UpdateGlobalHPR();											//PD 12Apr96
	AddZoom();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawOutPadlock
//Author		Paul.   
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawOutPadlock()
{
	if (deathview && currentviewrec==parachuterec)
		ResetZoomRotate((ZmRtFlags )NULL);

	if (trackeditem2)
	{
		ANGLES	deltahdg,deltapitch;

		CopyPosition(trackeditem,this);

		GetHPIntercept(trackeditem2,deltahdg,deltapitch);
		this->reqhdg = -deltahdg;								//PD 05Apr96
		this->reqpitch = -deltapitch;							//PD 05Apr96
	}
	if(!trackeditem2)
	{
		viewnum.viewmode = VM_Track;
		InitTrack();
	}
	UpdateGlobalViewRec();										//PD 05Jul96
	AddViewRec();												//PD 05Jul96
	UpdateGlobalHPR();											//PD 05Jul96
	AddZoom();													//PD 05Jul96

	if (trackeditem2!=NULL && trackeditem!=NULL)
	{
		ANGLES temp1,temp2;
		SLong	dx=trackeditem2->World.X-trackeditem->World.X,
				dy=trackeditem2->World.Y-trackeditem->World.Y,
				dz=trackeditem2->World.Z-trackeditem->World.Z;

		if (trackeditem2->Status.size==WAYPOINTSIZE)			//RDH 07Oct96
		{														//RDH 07Oct96
			Coords3D*	tp=::FindDesPos(*trackeditem2);			//RDH 07Oct96
			dx = tp->X - trackeditem->World.X;						//RDH 07Oct96
			dy = tp->Y - trackeditem->World.Y;						//RDH 07Oct96
			dz = tp->Z - trackeditem->World.Z;						//RDH 07Oct96
		}														//RDH 07Oct96
		Math_Lib.HighIntercept(dx,dy,dz,viewitemrange,temp1,temp2);
		OverLay.SetViewVals(viewitemrange,temp1-MobileItemPtr(trackeditem)->hdg,dy);
	}
	else OverLay.SetViewVals(0,0,0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawOutRevPadlock
//Author		Paul.   
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#ifndef NDEBUG
void ViewPoint::DrawOutRevPadlock()
{
	if(!trackeditem2)
	{
		viewnum.viewmode = VM_Track;
		InitTrack();
	}
	else
	{
		itemptr	temp;

		temp = trackeditem;
		trackeditem = trackeditem2;
		trackeditem2 = temp;

		ANGLES	deltahdg,deltapitch;

		CopyPosition(trackeditem,this);

		GetHPIntercept(trackeditem2,deltahdg,deltapitch);
		this->reqhdg = -deltahdg;								//PD 05Apr96
		this->reqpitch = -deltapitch;							//PD 05Apr96

		temp = trackeditem;
		trackeditem = trackeditem2;
		trackeditem2 = temp;

		UpdateGlobalViewRec();										//PD 04Apr96
		AddViewRec();
		UpdateGlobalHPR();										//PD 12Apr96
		AddZoom();
	}
}
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawChase
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawChase()
{
	if (flybytimeleft!=0)
	{
		SWord ft=RealFrameTime();
		SLong cur=currentviewrec->range;
		SLong toGo=((cur-currentviewrec->reset_range)*ft)/flybytimeleft;
		if (toGo<ft) toGo=ft;
		cur-=toGo;
		if (cur<SLong(currentviewrec->reset_range)) cur=currentviewrec->reset_range;
		currentviewrec->range=cur;

		cur=SLong(SWord(currentviewrec->hdg));
		toGo=((cur-SLong(SWord(currentviewrec->reset_hdg)))*ft)/flybytimeleft;
		if (toGo<0 && toGo>-ft) toGo=-ft;
		if (toGo>0 && toGo<ft) toGo=ft;
		cur-=toGo;
		currentviewrec->hdg=(Angles)UWord(cur);

		cur=SLong(SWord(currentviewrec->pitch));
		toGo=((cur-SLong(SWord(currentviewrec->reset_pitch)))*ft)/flybytimeleft;
		if (toGo<0 && toGo>-ft) toGo=-ft;
		if (toGo>0 && toGo<ft) toGo=ft;
		cur-=toGo;
		currentviewrec->pitch=(Angles)UWord(cur);

		flybytimeleft-=ft;
		if (flybytimeleft<0) flybytimeleft=0;
	}
	CopyPositionHPRVel(trackeditem,this);						//PD 24Apr96
	this->reqhdg = -this->reqhdg;								//PD 05Apr96
	this->reqpitch = -this->reqpitch;							//PD 05Apr96
	this->reqroll = -this->reqroll;								//PD 05Apr96
	UpdateGlobalViewRec();										//PD 04Apr96
	AddViewRec();
	UpdateGlobalHPR();											//PD 12Apr96
	AddZoom();
	AddCameraWobble();											//PD 29Feb96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawFlyBy
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawFlyBy()
{
	ANGLES tester=Math_Lib.HighArcTan(3,4);

	ViewRec bupViewRec=*currentviewrec;
	viewnum.viewcuttype=Instant;
	DrawTrack();
	*currentviewrec=bupViewRec;
	SWord ft=RealFrameTime();
	flybytimeleft-=ft;
	if (flybytimeleft<=0)
	{
		//swap to chase view
		flybytimeleft=0;
		trackeditem2 = (itemptr )NULL;
		viewnum.viewmode = VM_Chase;
		flybytimeleft=FlyByToChaseSwitchTime;
		InitChase();
	}
	else
	{
		SLong distToGo=((MaxFlybyZoom-currentviewrec->reset_range)*ft)/flybytimeleft;
		currentviewrec->reset_range+=distToGo;
		if (currentviewrec->reset_range>MaxFlybyZoom)
			currentviewrec->reset_range=MaxFlybyZoom;

		double dist=double(currentviewrec->reset_range)*double(currentviewrec->reset_range)+
					double(MinFlybyZoom)*double(MinFlybyZoom);
		_asm
		{
			fld dist;
			fsqrt;
			fstp dist;
		}
		currentviewrec->range=SLong(dist);
		currentviewrec->hdg=Math_Lib.HighArcTan(MinFlybyZoom,currentviewrec->reset_range);

/*		MobileItemPtr mip=MobileItemPtr(trackeditem);
		chaseviewrec->pitch=-mip->pitch;
		//zoom in if timeleft>.5*FlyByDuration
		if (flybytimeleft>(FlyByDuration>>1))
		{
			SLong curRange=currentviewrec->range;
			SLong distToGo=((curRange-MinFlybyZoom)*ft)/(flybytimeleft-(FlyByDuration>>1));
			if (distToGo<ft) distToGo=ft;
			curRange-=distToGo;
			if (curRange<MinFlybyZoom) curRange=MinFlybyZoom;
			currentviewrec->range=curRange;
		}
		else
		{
			SLong curRange=currentviewrec->range;
			SLong distToGo=((MaxFlybyZoom-curRange)*ft)/(flybytimeleft);
			if (distToGo<ft) distToGo=ft;
			curRange+=distToGo;
			if (curRange>MaxFlybyZoom) curRange=MaxFlybyZoom;
			currentviewrec->range=curRange;
		}
		//pan round using the heading field of the viewrec
		SLong curH=SLong(currentviewrec->hdg)&0xFFFF;
		SLong angToGo=((curH-(SLong(chaseviewrec->hdg)&0xFFFF))*ft)/flybytimeleft;
		if (angToGo<ft) angToGo=ft;
		curH-=angToGo;
		currentviewrec->hdg=(Angles)UWord(curH);

		SLong curP=SLong(SWord(currentviewrec->pitch));
		angToGo=((curP-SLong(SWord(chaseviewrec->pitch)))*ft)/flybytimeleft;
		if (angToGo<0 && angToGo>ft) angToGo=-ft;
		if (angToGo>0 && angToGo<ft) angToGo=ft;
		curP-=angToGo;
		currentviewrec->pitch=(Angles)UWord(curP);
*/
		if (	(flybytimeleft<((FlyByDuration*3)>>2))				//RJS 02Jun99
			&&	(playingflyby == false)					)
		{
			if (trackeditem->Status.size == AIRSTRUCSIZE)
			{
				playingflyby = true;
				AirStrucPtr	ac = (AirStrucPtr) trackeditem;
				if (ac->fly.pModel->EngineList->Type == ET_PISTON)
					_Miles.PlayDelayed(FIL_SFX_P51_FLYBY_SLOW,ac);//PD 13Aug99
				else
					_Miles.PlayDelayed(FIL_SFX_JET_FLYBY_SLOW,ac);//PD 13Aug99
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InvalidDraw
//Author		Paul.   
//Date			Fri 23 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InvalidDraw()
{
 	_Error.EmitSysErr(__FILE__"Invalid view draw routine");
}

//-------------------------------------------------------------------------------
//						OTHER VIEW ROUTINES
//-------------------------------------------------------------------------------

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ImpactToggle
//LastModified:	PD 17Jun96
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ImpactToggle()
{
	//Currently goes ALL OFF -> MISSILE ON/IMPACT OFF -> MISSILE ON/IMPACT ON

	if (viewnum.viewspec & VS_Impact)
	{
		OverLay.TriggerMessage(COverlay::IMPACTOFFMESS);
		viewnum.viewspec = VS_Null;								//JIM 16Jul96
		return;
	}
	else if (Manual_Pilot.ControlledAC2 &&
			!Manual_Pilot.ControlledAC2->Status.deadtime &&
			!Manual_Pilot.ControlledAC2->weap.Ejected)
	{
		OverLay.TriggerMessage(COverlay::IMPACTONMESS);
		viewnum.viewspec |= VS_Impact;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandleZoom
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::HandleZoom(ZmRtFlags flags)
{
	SLong	viewrangestep;

	//set zoom step based on the current zoom - larger steps
	//when further away.

	viewrangestep = (currentviewrec->range - modViewRangeMin);	//PD 30Apr97

	if (flags&ZR_BIG)											//JIM 10Aug96
		viewrangestep<<=3;										//JIM 10Aug96

	if(viewrangestep <= 20)	viewrangestep = 20;
	else					viewrangestep = 2 + ((viewrangestep * viewcodeframetime)>>5);//JIM 10Aug96
	if(viewrangestep <= 20) viewrangestep = 20;

	if (deathspeed)												//RJS 05Nov96
		viewrangestep /= deathspeed;							//RJS 05Nov96

	if (Three_Dee.shapecheat)
	{
		if(flags & ZR_ZoomIn)
			currentviewrec->range += 1000;					//RJS 25Jul96

		if(flags & ZR_ZoomOut)
			currentviewrec->range -= 1000;			//RJS 25Jul96
	}
	else
	{
		if(flags & ZR_ZoomIn)
			currentviewrec->range += viewrangestep;					//PD 29Feb96

		if(flags & ZR_ZoomOut)
			currentviewrec->range -= viewrangestep>>1;				//PD 29Feb96
	}
	if(currentviewrec->range > viewrangemax)					//PD 27Mar96
		currentviewrec->range = viewrangemax;					//PD 27Mar96
	else
		if(currentviewrec->range < modViewRangeMin)				//PD 30Apr97
			currentviewrec->range = modViewRangeMin;			//PD 30Apr97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopZoom
//Author		Paul.   
//Date			Thu 2 May 1996
//
//Description	Key has been released so copy
//				the current zoom from the global
//				viewrec structure into the 
//				current viewrec structure
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::StopZoom()
{
 	currentviewrec->range = globalviewrec->range;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopRotate
//Author		Paul.   
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::StopRotate()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandleFixedView
//Author		Paul.   
//Date			Tue 22 Jul 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::HandleFixedView(QuickView quickviewflag)
{
	View_RecP nextViewRec;

	static View_Rec VRNorthEast(0x0100,ANGLES_45Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_45Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VREast(0x0100,ANGLES_90Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_90Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRSouthEast(0x0100,ANGLES_135Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_135Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRSouth(0x0100,ANGLES_180Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_180Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRSouthWest(0x0100,ANGLES_225Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_225Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRWest(0x0100,ANGLES_270Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_270Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRNorthWest(0x0100,ANGLES_315Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_315Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRNorth(0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRUp(0x0100,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_90Deg,ANGLES_0Deg);

	if (viewdrawrtn!=DrawFixed)	InitPiloted();					//PD 27Sep97

	if (quickviewflag==QV_UpDownTog)
	{
		if (fixedviewrec==NULL)	return;

		if (fixedviewrec->pitch==ANGLES_0Deg)
		{
			VRNorthEast.pitch	= VRNorthEast.reset_pitch+ANGLES_45Deg;
			VREast.pitch		= VREast.reset_pitch+ANGLES_45Deg;
			VRSouthEast.pitch	= VRSouthEast.reset_pitch+ANGLES_45Deg;
			VRSouth.pitch		= VRSouth.reset_pitch+ANGLES_45Deg;
			VRSouthWest.pitch	= VRSouthWest.reset_pitch+ANGLES_45Deg;
			VRWest.pitch		= VRWest.reset_pitch+ANGLES_45Deg;
			VRNorthWest.pitch	= VRNorthWest.reset_pitch+ANGLES_45Deg;
			VRNorth.pitch		= VRNorth.reset_pitch+ANGLES_45Deg;
		}
		else
		{
			VRNorthEast.pitch	= VRNorthEast.reset_pitch;
			VREast.pitch		= VREast.reset_pitch;
			VRSouthEast.pitch	= VRSouthEast.reset_pitch;
			VRSouth.pitch		= VRSouth.reset_pitch;
			VRSouthWest.pitch	= VRSouthWest.reset_pitch;
			VRWest.pitch		= VRWest.reset_pitch;
			VRNorthWest.pitch	= VRNorthWest.reset_pitch;
			VRNorth.pitch		= VRNorth.reset_pitch;
		}
		return;
	}
	else if (quickviewflag==QV_PanRight)
	{
		if (fixedviewrec==NULL)
			nextViewRec=&VRNorth;
		else
		{
			if 		(fixedviewrec==&VRNorthEast)	nextViewRec=&VREast;
			else if (fixedviewrec==&VREast)			nextViewRec=&VRSouthEast;
			else if (fixedviewrec==&VRSouthEast)	nextViewRec=&VRSouth;
			else if (fixedviewrec==&VRSouth)		nextViewRec=&VRSouthWest;
			else if (fixedviewrec==&VRSouthWest)	nextViewRec=&VRWest;
			else if (fixedviewrec==&VRWest)			nextViewRec=&VRNorthWest;
			else if (fixedviewrec==&VRNorthWest)	nextViewRec=&VRNorth;
			else if (fixedviewrec==&VRNorth)		nextViewRec=&VRNorthEast;
			else return;

			if (fixedviewrec->pitch!=fixedviewrec->reset_pitch)
				nextViewRec->pitch=nextViewRec->reset_pitch+ANGLES_45Deg;

			fixedviewrec=nextViewRec;

			return;
		}
	}
	else if (quickviewflag==QV_PanLeft)
	{
		if (fixedviewrec==NULL)
			nextViewRec=&VRNorth;
		else
		{
			if 		(fixedviewrec==&VRNorthEast)	nextViewRec=&VRNorth;
			else if (fixedviewrec==&VREast)			nextViewRec=&VRNorthEast;
			else if (fixedviewrec==&VRSouthEast)	nextViewRec=&VREast;
			else if (fixedviewrec==&VRSouth)		nextViewRec=&VRSouthEast;
			else if (fixedviewrec==&VRSouthWest)	nextViewRec=&VRSouth;
			else if (fixedviewrec==&VRWest)			nextViewRec=&VRSouthWest;
			else if (fixedviewrec==&VRNorthWest)	nextViewRec=&VRWest;
			else if (fixedviewrec==&VRNorth)		nextViewRec=&VRNorthWest;
			else return;

			if (fixedviewrec->pitch!=fixedviewrec->reset_pitch)
				nextViewRec->pitch=nextViewRec->reset_pitch+ANGLES_45Deg;

			fixedviewrec=nextViewRec;

			return;
		}
	}

	switch (quickviewflag)
	{
		case QV_NorthEast:	nextViewRec=&VRNorthEast;	break;
		case QV_East:		nextViewRec=&VREast;		break;
		case QV_SouthEast:	nextViewRec=&VRSouthEast;	break;
		case QV_South:		nextViewRec=&VRSouth;		break;
		case QV_SouthWest:	nextViewRec=&VRSouthWest;	break;
		case QV_West:		nextViewRec=&VRWest;		break;
		case QV_NorthWest:	nextViewRec=&VRNorthWest;	break;	
		case QV_North:		nextViewRec=&VRNorth;		break;
		case QV_Up:			nextViewRec=&VRUp;			break;
	}

	if (fixedviewrec!=NULL && Save_Data.gamedifficulty[GD_UPTOGGLESTICKS]
		&& quickviewflag!=QV_Up)
	{
		if (fixedviewrec->pitch!=fixedviewrec->reset_pitch)
			nextViewRec->pitch=nextViewRec->reset_pitch+ANGLES_45Deg;
	}

	fixedviewrec=nextViewRec;

	//fixedviewrec = ptr to viewrec for required quick view

	viewdrawrtn=DrawFixed;
	drawpolypit=TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandleQuickView
//Author		Paul.   
//Date			Tue 28 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::HandleQuickView(QuickView quickviewflag)
{
	static View_Rec	VRNorthEast(0x0100,ANGLES_45Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_45Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VREast(0x0100,ANGLES_90Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_90Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRSouthEast(0x0100,ANGLES_135Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_135Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRSouth(0x0100,ANGLES_180Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_180Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRSouthWest(0x0100,ANGLES_225Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_225Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRWest(0x0100,ANGLES_270Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_270Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRNorthWest(0x0100,ANGLES_315Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_315Deg,ANGLES_0Deg,ANGLES_0Deg);
	static View_Rec	VRNorth(0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg,0x0100,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg);

	Bool	shifted = FALSE;

	if (Key_Tests.KeyHeld3d(LOOKUPTOG))	shifted=TRUE;

	if (bupviewdrawrtn==NULL)
	{
		bupviewnum=viewnum;										//PD 22Sep97
		viewnum.viewchanged=VC_SuccessfulChange;				//PD 22Sep97
		messagetime=FIVESECS100;								//PD 22Sep97
	}

	viewnum.viewmode = VM_Inside;

	ANGLES	pitchfiddle;

	if (quickviewflag==QV_Instruments)
	{
		quickviewrec=&VRNorth;
		pitchfiddle=(Angles)-ANGLES_30Deg;
	}
	else
	{
		//Apply the shift if required

		if (shifted)
		{
			if (quickviewflag>QV_North)
				quickviewflag=(QuickView)(quickviewflag-QV_North);
			else
				quickviewflag=(QuickView)(quickviewflag+QV_North);
		}

		switch (quickviewflag)
		{
			case QV_NorthEast:
				quickviewrec=&VRNorthEast;
				pitchfiddle=ANGLES_0Deg;
			break;
			case QV_East:
				quickviewrec=&VREast;
				pitchfiddle=ANGLES_0Deg;
			break;
			case QV_SouthEast:
				quickviewrec=&VRSouthEast;
				pitchfiddle=ANGLES_0Deg;
			break;
			case QV_South:
				quickviewrec=&VRSouth;
				pitchfiddle=ANGLES_0Deg;
			break;
			case QV_SouthWest:
				quickviewrec=&VRSouthWest;
				pitchfiddle=ANGLES_0Deg;
			break;
			case QV_West:
				quickviewrec=&VRWest;
				pitchfiddle=ANGLES_0Deg;
			break;
			case QV_NorthWest:
				quickviewrec=&VRNorthWest;
				pitchfiddle=ANGLES_0Deg;
			break;
			case QV_North:
				quickviewrec=&VRNorth;
				pitchfiddle=ANGLES_0Deg;
			break;

			case QV_NorthEastUp:
				quickviewrec=&VRNorthEast;
				pitchfiddle=ANGLES_45Deg;
			break;
			case QV_EastUp:
				quickviewrec=&VREast;
				pitchfiddle=ANGLES_45Deg;
			break;
			case QV_SouthEastUp:
				quickviewrec=&VRSouthEast;
				pitchfiddle=ANGLES_45Deg;
			break;
			case QV_SouthUp:
				quickviewrec=&VRSouth;
				pitchfiddle=ANGLES_45Deg;
			break;
			case QV_SouthWestUp:
				quickviewrec=&VRSouthWest;
				pitchfiddle=ANGLES_45Deg;
			break;
			case QV_WestUp:
				quickviewrec=&VRWest;
				pitchfiddle=ANGLES_45Deg;
			break;
			case QV_NorthWestUp:
				quickviewrec=&VRNorthWest;
				pitchfiddle=ANGLES_45Deg;
			break;
			case QV_NorthUp:
				quickviewrec=&VRNorth;
				pitchfiddle=ANGLES_45Deg;
			break;
		}
	}
	quickviewrec->pitch=(ANGLES)(quickviewrec->reset_pitch+pitchfiddle);

	//quickviewrec = ptr to viewrec for required quick view

	if (bupviewdrawrtn==NULL)
	{
		bupviewdrawrtn=viewdrawrtn;
		viewdrawrtn=DrawQuick;
		bupdrawpolypit=drawpolypit;
		drawpolypit=TRUE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipInsideAngles
//LastModified:	PD 06Jun97
//Author		Paul.   
//Date			Fri 14 Jun 1996
//
//Description	Keep inside view angles clipped to values that prevent
//				the pilots head from falling off
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ClipInsideAngles()
{
	SWord	temp;

	SWord	angles135,angles225,angles45,angles330;

 	angles135=(SWord)ANGLES_160Deg;
	angles225=(SWord)(UWord(ANGLES_240Deg)-UWord(ANGLES_20Deg)-UWord(ANGLES_20Deg));
	angles45 =(SWord)ANGLES_90Deg;
	angles330=(SWord)ANGLES_320Deg;

	temp = currentviewrec->hdg;

	if (temp > angles135)		temp = angles135;
	else if (temp< angles225)	temp = angles225;

	currentviewrec->hdg = (Angles)temp;

	temp = currentviewrec->pitch;

	if (temp > angles45)		temp = angles45;
	else if (temp< angles330)	temp = angles330;

	currentviewrec->pitch = (Angles)temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandleRotate
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::HandleRotate(ZmRtFlags flags)
{
	ANGLES	viewanglestep = (Angles)((int)ViewAngleStep * viewcodeframetime/5);//PD 05Apr96

	if (!(int)viewanglestep)											//PD 05Apr96
		viewanglestep = ANGLES_FifthDeg;							//PD 05Apr96
	KeySteps++;
	if(flags & ZR_BIG)											//JIM 10Aug96
	{
		viewanglestep=Angles((SWord)viewanglestep<<1);	//2);										//PD 07Dec96
		KeySteps+=7;											//PD 07Dec96
	}

	if (setDeath == DEATH_AIRTOAIR)								//DAW 03Sep98
		viewanglestep = (Angles) (viewanglestep / 6);			//DAW 03Sep98

	switch	(viewnum.viewmode)									//PD 25Aug96
	{
		case VM_InPadlock:
		case VM_Inside:
		case VM_InsideCheat:
			break;

		default:
			viewanglestep = -viewanglestep;
	}															//PD 25Aug96

	if(flags & ZR_RotUp)
		currentviewrec->pitch += viewanglestep;					//PD 29Feb96
	if(flags & ZR_RotDn)
		currentviewrec->pitch -= viewanglestep;					//PD 29Feb96
	if(flags & ZR_RotLft)
		currentviewrec->hdg -= viewanglestep;					//PD 29Feb96
	if(flags & ZR_RotRght)
		currentviewrec->hdg += viewanglestep;					//PD 29Feb96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetZoomRotate
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ResetZoomRotat2(ZmRtFlags flags)
{
	Save_Data.fieldOfView=ANGLES_45Deg;
	ResetZoomRotate(flags);
}
void ViewPoint::ResetZoomRotate(ZmRtFlags flags)
{
	currentviewrec->range = currentviewrec->reset_range;
	globalviewrec->range = currentviewrec->range;				//PD 02May96
	currentviewrec->hdg = currentviewrec->reset_hdg;
	currentviewrec->pitch = currentviewrec->reset_pitch;
	currentviewrec->roll = currentviewrec->reset_roll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyPosition
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::CopyPosition(itemptr source,itemptr dest)
{
	switch(source->Status.size)
	{
		case RotatedSize:
		case MovingSize:
		case MobileSize:
		case TransientSize:
		case FormationSize:
		case ShipSize:
		case AirStrucSize:
			if (dest==this)										//PD 18Jun96
			((ViewPoint* )dest)->reqroll = ANGLES_0Deg;			//PD 18Jun96
			else												//PD 18Jun96
			((rotitem* )dest)->roll = ANGLES_0Deg;				//PD 18Jun96


		case HPSize:
			if (dest==this)										//PD 18Jun96
			((ViewPoint* )dest)->reqpitch = ANGLES_0Deg;		//PD 18Jun96
			else												//PD 18Jun96
			((hpitem* )dest)->pitch = ANGLES_0Deg;				//PD 18Jun96


		case HdgSize:
			if (dest==this)										//PD 18Jun96
			((ViewPoint* )dest)->reqhdg = ANGLES_0Deg;			//PD 18Jun96
			else												//PD 18Jun96
			((hdgitem* )dest)->hdg = ANGLES_0Deg;				//PD 18Jun96


		default:
		case ItemSize:
			dest->World.X = source->World.X;
			dest->World.Y = source->World.Y;
			dest->World.Z = source->World.Z;
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyPositionHP
//Author		Paul.   
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::CopyPositionHP(itemptr source,itemptr dest)
{
	((ViewPoint* )dest)->reqroll = ANGLES_0Deg;
	((ViewPoint* )dest)->reqpitch = ANGLES_20Deg;
	((ViewPoint* )dest)->reqhdg = ANGLES_0Deg;

	switch(source->Status.size)
	{
		case RotatedSize:
		case MovingSize:
		case MobileSize:
		case TransientSize:
		case FormationSize:
		case ShipSize:
		case AirStrucSize:
			((ViewPoint* )dest)->reqroll = ANGLES_0Deg;			//PD 05Apr96

		case HPSize:
			if (!StopDeadView)									//RJS 12Sep97
	 			((ViewPoint* )dest)->reqpitch = ((hpitem* )source)->pitch;//RJS 12Sep97
			else												//RJS 12Sep97
				((ViewPoint* )dest)->reqpitch = -(ANGLES)ANGLES_20Deg;	//RJS 12Sep97

		case HdgSize:
			((ViewPoint* )dest)->reqhdg = ((hdgitem* )source)->hdg;//PD 05Apr96

		default:
		case ItemSize:
			dest->World.X = source->World.X;
			dest->World.Y = source->World.Y;
			dest->World.Z = source->World.Z;
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyPositionHPR
//LastModified:	DAW 23Feb96
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	The '-' signs are temporary						//DAW 23Feb96
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::CopyPositionHPR(itemptr source,itemptr dest)
{
	switch(source->Status.size)
	{
		case RotatedSize:
		case MovingSize:
		case MobileSize:
		case TransientSize:
		case FormationSize:
		case ShipSize:
		case AirStrucSize:
			((ViewPoint* )dest)->reqroll = ((rotitem *)source)->roll;//PD 05Apr96

		case HPSize:
			((ViewPoint* )dest)->reqpitch = ((hpitem *)source)->pitch;//PD 27Feb96

		case HdgSize:
			((ViewPoint* )dest)->reqhdg = ((hdgitem *)source)->hdg;//PD 05Apr96

		default:
		case ItemSize:
			dest->World.X = source->World.X;
			dest->World.Y = source->World.Y;
			dest->World.Z = source->World.Z;
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyPositionHPVel
//Author		Paul.   
//Date			Wed 24 Apr 1996
//
//Description	Set view direction based on the tracked items velocity
//				vectors (if avaliable).
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::CopyPositionHPVel(itemptr source,itemptr dest)
{
	ANGLES	vhdg,vptch,vroll;

	MovingItem*	sptr = (MovingItem* )source;

	switch(source->Status.size)
	{
		case MovingSize:
		case MobileSize:
		case TransientSize:
		case FormationSize:
		case ShipSize:
		case AirStrucSize:

 			vhdg = Math_Lib.HighArcTan(sptr->velx,sptr->velz);

			vptch= Math_Lib.HighArcTan(sptr->vely,sptr->velhori);
 
 			vroll= ANGLES_0Deg;
 
 			((ViewPoint* )dest)->reqhdg = vhdg;
 			((ViewPoint* )dest)->reqpitch = vptch;
 			((ViewPoint* )dest)->reqroll = vroll;
 			break;

		case RotatedSize:
			((ViewPoint* )dest)->reqroll = ANGLES_0Deg;

		case HPSize:
			((ViewPoint* )dest)->reqpitch = ((hpitem* )source)->pitch;//PD 05Apr96

		case HdgSize:
			((ViewPoint* )dest)->reqhdg = ((hdgitem* )source)->hdg;//PD 05Apr96

		default:
		case ItemSize:
			break;
	}
	dest->World.X = source->World.X;
	dest->World.Y = source->World.Y;
	dest->World.Z = source->World.Z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyPositionHPRVel
//Author		Paul.   
//Date			Wed 24 Apr 1996
//
//Description	Set view direction based on the tracked items velocity
//				vectors (if avaliable).
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::CopyPositionHPRVel(itemptr source,itemptr dest)
{
	ANGLES	vhdg,vptch,vroll;

	MovingItem*	sptr = (MovingItem* )source;

	SLong temp =
	Land_Scape.GetGroundLevel(*sptr)+SAFECAMERAHEIGHT;

	Bool bLowDown = sptr->World.Y<=temp?TRUE:FALSE;

	switch(source->Status.size)
	{
		case MovingSize:
		case MobileSize:
		case TransientSize:
		case FormationSize:
		case ShipSize:
		case AirStrucSize:

			if ((sptr->velx==0 && sptr->velz==0) || bLowDown)
				vhdg = sptr->hdg;
			else
 				vhdg = Math_Lib.HighArcTan(sptr->velx,sptr->velz);

			if ((sptr->vely==0 && sptr->velhori==0) || bLowDown)
				vptch = sptr->pitch;
			else
				vptch= Math_Lib.HighArcTan(sptr->vely,sptr->velhori);
 
 			vroll= sptr->roll;
 
 			((ViewPoint* )dest)->reqhdg = vhdg;
 			((ViewPoint* )dest)->reqpitch = vptch;
 			((ViewPoint* )dest)->reqroll = vroll;
 			break;

		case RotatedSize:
			((ViewPoint* )dest)->reqroll = ANGLES_0Deg;

		case HPSize:
			((ViewPoint* )dest)->reqpitch = ((hpitem* )source)->pitch;//PD 05Apr96

		case HdgSize:
			((ViewPoint* )dest)->reqhdg = ((hdgitem* )source)->hdg;//PD 05Apr96

		default:
		case ItemSize:
			break;
	}
	dest->World.X = source->World.X;
	dest->World.Y = source->World.Y;
	dest->World.Z = source->World.Z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddViewRec
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::AddViewRec(bool addjoy)							//DAW 02Sep99
{
	if (addjoy)
	{
		this->reqhdg += (Angles)jhead;								//PD 16Sep97
		this->reqpitch += (Angles)jpitch;							//PD 16Sep97
		this->reqroll += (Angles)jroll;								//PD 16Sep97
	}

	this->reqhdg += globalviewrec->hdg;							//PD 05Apr96
	this->reqpitch += globalviewrec->pitch;						//PD 05Apr96
	this->reqroll += globalviewrec->roll;						//PD 05Apr96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddViewRecInside
//Author		Paul.   
//Date			Fri 14 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::AddViewRecInside(bool dojoy)					//DAW 02Sep99
{
	ANGLES	ac_pitch,ac_hdg,ac_roll;
	ANGLES	vr_pitch,vr_hdg,vr_roll;

	ac_pitch = 	-this->reqpitch;
	ac_hdg = 	-this->reqhdg;
	ac_roll = 	-this->reqroll;

	vr_pitch = globalviewrec->pitch;
	vr_hdg = globalviewrec->hdg;
	vr_roll = globalviewrec->roll;

	SWord	ho,po,ro,zo;

	if (dojoy)
	{
		vr_hdg += (Angles)jhead;
		vr_pitch += (Angles)jpitch;
		vr_roll += (Angles)jroll;
	}

	_matrix.TransformAngles(ac_hdg,ac_pitch,ac_roll,
							vr_hdg,vr_pitch,vr_roll);

	this->reqpitch = -vr_pitch;
	this->reqhdg = -vr_hdg;
	this->reqroll = -vr_roll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddZoom
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::AddZoom()
{
	SLong	min_zoom_shape;		//Shape size to get min zoom range
	SLong	max_zoom_shape;

	if (trackeditem->shape!=EMPTY)
	{
		ShapeDescPtr sdptr=SHAPESTUFF.GetShapePtr(trackeditem->shape);
		Float mzs=Float(sdptr->Size<<4)/_matrix.FoV;
		min_zoom_shape=SLong(mzs);
		max_zoom_shape=min_zoom_shape*50;
	}
	else
	{
		min_zoom_shape=5000;
		max_zoom_shape=min_zoom_shape*50;
	}
	if (min_zoom_shape>(globalviewrec->range+jzoom)) 
	{
		if (!jzoom)
			globalviewrec->range=
				currentviewrec->range=min_zoom_shape;
	}
	else if (max_zoom_shape<(globalviewrec->range+jzoom))
	{
		globalviewrec->range=
			currentviewrec->range=max_zoom_shape;
		min_zoom_shape+=globalviewrec->range;
	}
	else
	{
		min_zoom_shape=globalviewrec->range+jzoom;
	}

	SLong	deltax,deltay,deltaz;

	SLong	temp;

	SWord	sp,cp;	//sine pitch, cosine pitch

	SWord	sh,ch;	//sine heading, cosine heading

	Math_Lib.high_sin_cos(-pitch,sp,cp);							//PD 23Feb96

	Math_Lib.high_sin_cos(-hdg,sh,ch);							//PD 27Feb96

	deltay = -MULSHSIN(min_zoom_shape,sp,15);						//PD 12Mar96

	temp = -MULSHSIN(min_zoom_shape,cp,15);						//PD 12Mar96

	deltax = MULSHSIN(temp,sh,15);						//PD 12Mar96

	deltaz = MULSHSIN(temp,ch,15);						//PD 12Mar96

	COORDS3D last=World,save=last;

	World.X += deltax;
	World.Y += deltay;
	World.Z += deltaz;

	//on map view make sure that the viewer isn't allowed to get
	//above the cloud layer...

	if (OverLay.pCurScr==&OverLay.mapViewScr)
	{
		SLong cloudAlt=Land_Scape.CloudAlt()-FT_1000;
		if (World.Y>cloudAlt)
		{
			double frac=Float(cloudAlt-last.Y)/Float(World.Y-last.Y);
			World.Y=cloudAlt;
			World.X=last.X+SLong(frac*Float(World.X-last.X));
			World.Z=last.Z+SLong(frac*Float(World.Z-last.Z));
			last.X-=World.X;
			last.Y-=World.Y;
			last.Z-=World.Z;
			frac=double(last.X)*double(last.X)+
				double(last.Y)*double(last.Y)+
				double(last.Z)*double(last.Z);
			_asm{
				fld frac;
				fsqrt;
				fstp frac;
			}
			min_zoom_shape=globalviewrec->range=currentviewrec->range=SLong(frac)-5000;
			deltay=-MULSHSIN(min_zoom_shape,sp,15);
			temp=-MULSHSIN(min_zoom_shape,cp,15);
			deltax=MULSHSIN(temp,sh,15);
			deltaz=MULSHSIN(temp,ch,15);
			World=save;
			World.X+=deltax;
			World.Y+=deltay;
			World.Z+=deltaz;
			OverLay.fHitZoomLimit=true;
		}
	}
	//Set camera height to at least 5m above ground level

	temp = Land_Scape.GetGroundLevel(*this)+SAFECAMERAHEIGHT;

	if(World.Y<temp)
		World.Y = temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitInside
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitInside()
{
	if (deathview)
		return;
	if (_Replay.Playback)
	{
		InitInsideCheat();
		return;
	}
	Three_Dee.ResetCompass();									//RJS 21Nov96
	trackeditem = currentvehicle;
	currentviewrec = insideviewrec;
	bupviewdrawrtn = NULL;										//PD 28Jan97
	viewdrawrtn = DrawInside;
	drawpolypit = TRUE;
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitInsideCheat
//Author		Paul.   
//Date			Mon 17 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitInsideCheat()
{
	if (deathview)												//RDH 16Dec96
		return;													//RDH 16Dec96

	trackeditem = currentvehicle;
	currentviewrec = insidecheatviewrec;
	bupviewdrawrtn = NULL;										//PD 28Jan97
	viewdrawrtn = DrawInsideCheat;
	drawpolypit = FALSE;
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitInPadlock
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitInPadlock()
{
	if (deathview)												//RDH 16Dec96
		return;													//RDH 16Dec96

	fLastWasNormal=false;										//PD 04Jan99
	fLastWasAlternate=false;									//PD 04Jan99

	bPadlockOut = FALSE;

	trackeditem = currentvehicle;

	//Default to inside view if no object to follow

	if(!trackeditem2)
	{
		currentviewrec = insideviewrec;
		bupviewdrawrtn = NULL;									//PD 28Jan97
		viewdrawrtn = DrawInside;
	}
	else
	{
		currentviewrec = inpadlockviewrec;
		bupviewdrawrtn = NULL;									//PD 28Jan97
		viewdrawrtn = DrawInPadlock;
	}
	drawpolypit = TRUE;											//PD 14Jun96
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitTrack
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitTrack()
{
	trackeditem = currentvehicle;
	currentviewrec = trackviewrec;
	UpdateGlobalViewRec();
	bupviewdrawrtn = NULL;										//PD 28Jan97
	viewdrawrtn = DrawTrack;
	drawpolypit = FALSE;
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitOutPadlock
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitOutPadlock()
{
//TEMP	if (Save_Data.gamedifficulty[GD_AUTOPADLOCKTOG])
//TEMP		InitInPadlock();
//TEMP	else
	{
		trackeditem = currentvehicle;
		currentviewrec = outpadlockviewrec;
		bupviewdrawrtn = NULL;										//PD 28Jan97
		viewdrawrtn = DrawOutPadlock;
		drawpolypit = FALSE;
		drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
		drawmap = FALSE;//RJS 10Sep98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitOutRevPadlock
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#ifndef NDEBUG
void ViewPoint::InitOutRevPadlock()
{
	trackeditem = currentvehicle;
	currentviewrec = outrevpadlockviewrec;
	bupviewdrawrtn = NULL;										//PD 28Jan97
	viewdrawrtn = DrawOutRevPadlock;
	drawpolypit = FALSE;
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
}
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitNrSatellite
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitNrSatellite()
{
	trackeditem = currentvehicle;
	currentviewrec = nrsatelliteviewrec;
	bupviewdrawrtn = NULL;										//PD 28Jan97
	viewdrawrtn = DrawOutside;
	drawpolypit = FALSE;
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSatellite
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitSatellite()
{
	trackeditem = currentvehicle;
	currentviewrec = satelliteviewrec;
	bupviewdrawrtn = NULL;										//PD 28Jan97
	viewdrawrtn = DrawOutside;
	drawpolypit = FALSE;
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitChase
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitChase()
{
	trackeditem = currentvehicle;
	currentviewrec = chaseviewrec;
	bupviewdrawrtn = NULL;										//PD 28Jan97
	viewdrawrtn = DrawChase;
	drawpolypit = FALSE;
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98

	//Set the initial velocities for the viewpoint to match a/c being tracked

	SWord	st,ct,vh;

	SLong	req_vel = ((MovingItemPtr )trackeditem)->vel;

	this->vel = req_vel;

	Math_Lib.high_sin_cos(this->pitch,st,ct);

	this->vely = (SWord )((req_vel * st)/ANGLES_FRACT);

	vh = (SWord )((req_vel * ct)/ANGLES_FRACT);

	Math_Lib.high_sin_cos(this->hdg,st,ct);

	this->velx = (SWord )((vh * st)/ANGLES_FRACT);
	this->velz = (SWord )((vh * ct)/ANGLES_FRACT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitFlyBy
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitFlyBy()
{
//dead	SLong	flybysteps;

	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
	drawmap = FALSE;//RJS 10Sep98
	if (Three_Dee.shapecheat)
	{
		if (deathview)
			deathview = FALSE;
		else
			deathview = TRUE;
	}
	else
	{
		trackeditem=currentvehicle;
		currentviewrec=flybyviewrec;
		bupviewdrawrtn=NULL;
		viewdrawrtn=DrawFlyBy;
		drawpolypit=FALSE;
		MobileItemPtr mip=(MobileItemPtr)trackeditem;
		currentviewrec->reset_range=MaxFlybyZoom;
		currentviewrec->pitch=mip->pitch;
		currentviewrec->roll=ANGLES_0Deg;
		currentviewrec->reset_range=-MaxFlybyZoom;
		double dist=double(currentviewrec->reset_range)*double(currentviewrec->reset_range)+
					double(MinFlybyZoom)*double(MinFlybyZoom);
		_asm
		{
			fld dist;
			fsqrt;
			fstp dist;
		}
		currentviewrec->range=SLong(dist);
		currentviewrec->hdg=Math_Lib.HighArcTan(MinFlybyZoom,currentviewrec->reset_range);

		chaseviewrec->range=MaxFlybyZoom;
		chaseviewrec->hdg=ANGLES_0Deg;
		chaseviewrec->pitch=ANGLES_0Deg;
		chaseviewrec->roll=ANGLES_0Deg;
		flybytimeleft=FlyByDuration;

		playingflyby = false;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		List1Toggle
//LastModified:	PD 03Sep96
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	Steps between Inside padlock, inside look up and
//				inside look down views
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::List1Toggle()
{
	viewnum.viewmode = VM_Inside;

	switch (viewnum.viewtarg)
	{
		case VT_Player:
			viewsetuprtn = InitInside;
			break;
		case VT_Enemy:
			InitInside();
			CheckPadlock(currentenemyitem);
//dead			viewsetuprtn = InitEnemy;
			break;
		case VT_Friendly:
			InitInside();
			CheckPadlock(currentfriendlyitem);
//dead			viewsetuprtn = InitFriendly;	//DEAD Enemy;
			break;
		case VT_GroundTarg:
			InitInside();
			CheckPadlock(currentgndtargitem);
//dead			viewsetuprtn = InitGroundTarget;
			break;
		case VT_WayPoint:
			InitInside();
			CheckPadlock(currentwaypoint);
//dead			viewsetuprtn = InitWayPoint;
			break;
		case VT_Message:
			InitInside();
			CheckPadlock(currentmessageitem);
//dead			viewsetuprtn = InitMessage;
			break;
		case VT_AIUnfriendly:
			InitInside();
			CheckPadlock(currentenemyitem);
//dead			viewsetuprtn = InitAIUnfriendly;
			break;
		case VT_Escortee:
			InitInside();
			CheckPadlock(currentfriendlyitem);
//dead			viewsetuprtn = InitEscortee;
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		List2Toggle
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::List2Toggle()
{
	viewnum.viewmode = VM_Track;

	switch (viewnum.viewtarg)
	{
		case VT_Player:
			viewsetuprtn = InitTrack;
			break;
		case VT_Enemy:
			InitTrack();
			CheckPadlock(currentenemyitem);
//dead			viewsetuprtn = InitEnemy;
			break;
		case VT_Friendly:
			InitTrack();
			CheckPadlock(currentfriendlyitem);
//dead			viewsetuprtn = InitFriendly;	//DEAD Enemy;
			break;
		case VT_GroundTarg:
			InitTrack();
			CheckPadlock(currentgndtargitem);
//dead			viewsetuprtn = InitGroundTarget;
			break;
		case VT_WayPoint:
			InitTrack();
			CheckPadlock(currentwaypoint);
//dead			viewsetuprtn = InitWayPoint;
			break;
		case VT_Message:
			InitTrack();
			CheckPadlock(currentmessageitem);
//dead			viewsetuprtn = InitMessage;
			break;
		case VT_AIUnfriendly:
			InitTrack();
			CheckPadlock(currentenemyitem);
//dead			viewsetuprtn = InitAIUnfriendly;
			break;
		case VT_Escortee:
			InitTrack();
			CheckPadlock(currentfriendlyitem);
//dead			viewsetuprtn = InitEscortee;
			break;
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		List3Toggle
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::List3Toggle()
{
	if(viewnum.viewmode<VM_Satellite || viewnum.viewmode>VM_NrSatellite)
	{
		viewnum.viewmode = VM_Satellite;
	}
	else
	{
		viewnum.viewmode++;
		if(viewnum.viewmode>VM_NrSatellite)
			viewnum.viewmode = VM_Satellite;
	}

	switch(viewnum.viewmode)
	{
		case VM_Satellite:
			viewsetuprtn = InitSatellite;
			break;
		case VM_NrSatellite:
			viewsetuprtn = InitNrSatellite;
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		List4Toggle
//Author		Paul.   
//Date			Tue 20 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::List4Toggle()
{
	if(viewnum.viewmode<VM_FlyBy || viewnum.viewmode>VM_Chase)
	{
		viewnum.viewmode = VM_FlyBy;
	}
	else
	{
		viewnum.viewmode++;
		if(viewnum.viewmode>VM_Chase)
			viewnum.viewmode = VM_FlyBy;
	}

	switch(viewnum.viewmode)
	{
		case VM_Chase:
			viewsetuprtn = InitChase;
			break;
		case VM_FlyBy:
			viewsetuprtn = InitFlyBy;
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		List5Toggle
//Author		Paul.   
//Date			Mon 17 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::List5Toggle()
{
	if (viewnum.viewmode != VM_InsideCheat)
	{
		viewnum.viewmode = VM_InsideCheat;
		viewsetuprtn = InitInsideCheat;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		List7Toggle
//Author		Paul.   
//Date			Thu 26 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::List7Toggle()
{
	ViewMode	newmode = VM_Inside;

	if (viewnum.viewmode==VM_Inside)
		newmode = VM_Track;
	if (viewnum.viewmode==VM_InPadlock)
		newmode = VM_OutPadlock;
	if (viewnum.viewmode==VM_Track)
		newmode = VM_Inside;
	if (viewnum.viewmode==VM_OutPadlock)
		newmode = VM_InPadlock;

	viewnum.viewmode=newmode;

	switch (newmode)
	{
		case VM_Track:
			viewsetuprtn = InitTrack;
			break;
		case VM_OutPadlock:
			viewsetuprtn = InitOutPadlock;
			break;
		case VM_Inside:
			viewsetuprtn = InitInside;
			break;
		case VM_InPadlock:
			viewsetuprtn = InitInPadlock;
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		List6Toggle
//Author		Paul.   
//Date			Thu 27 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#ifndef NDEBUG
void ViewPoint::List6Toggle()
{
	if (viewnum.viewmode!=VM_OutRevPadlock)
	{
		viewnum.viewmode = VM_OutRevPadlock;
		viewsetuprtn = InitOutRevPadlock;
	}
}
#endif															//RDH 13Dec96

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetHPIntercept
//Author		Paul.   
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::GetHPIntercept(itemptr ip,ANGLES& out_hdg, ANGLES& out_pitch)
{
	SLong	deltax,deltay,deltaz,dummy;

	SWord	hdg_word,pitch_word;

	deltax = ip->World.X - this->World.X;
	deltay = ip->World.Y - this->World.Y;
	deltaz = ip->World.Z - this->World.Z;
	if (trackeditem2->Status.size==WAYPOINTSIZE)			//RDH 07Oct96
	{														//RDH 07Oct96
		Coords3D*	tp=::FindDesPos(*trackeditem2);			//RDH 07Oct96
		deltax = tp->X - this->World.X;						//RDH 07Oct96
		deltay = tp->Y - this->World.Y;						//RDH 07Oct96
		deltaz = tp->Z - this->World.Z;						//RDH 07Oct96
	}														//RDH 07Oct96


	Math_Lib.HighIntercept(deltax,deltay,deltaz,dummy,hdg_word,pitch_word);
	viewitemrange = dummy;										//PD 05Jul96
//DEAD	viewitemhdg = (Angles )hdg_word;							//PD 05Jul96

	out_hdg = (Angles )hdg_word;
	out_pitch = (Angles )pitch_word;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddCameraWobble
//Author		Paul.   
//Date			Thu 29 Feb 1996
//
//Description	Moves the cameraposition vertically and horizontally to
//				add to the views realism (probably!)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::AddCameraWobble()
{
	if (Key_Tests.KeyPress3d(TOGGLEWOBBLEVIEW))
		Save_Data.viewwobble^=0xFF;

	if (Save_Data.viewwobble==0x00)	return;

	ANGLES	viewanglestep =										//PD 08Oct97
	(Angles)((ViewAngleStep * viewcodeframetime)/20);				//PD 08Oct97

	if (!viewanglestep)											//PD 05Apr96
		viewanglestep = ANGLES_1Deg;							//PD 05Apr96

	if(xdelta.anglevalue < ANGLES_0Deg)	NewCameraDelta(xdelta);	//RDH 24Jul96

	if(ydelta.anglevalue < ANGLES_0Deg)	NewCameraDelta(ydelta);	//RDH 24Jul96

	if(zdelta.anglevalue < ANGLES_0Deg)	NewCameraDelta(zdelta);	//RDH 24Jul96

	this->World.X += GetCameraDisplacement(&xdelta,viewanglestep);
	this->World.Y += GetCameraDisplacement(&ydelta,viewanglestep);
	this->World.Z += GetCameraDisplacement(&zdelta,viewanglestep);

	//Don't let the camera go below 5m above ground level

	SLong temp = Land_Scape.GetGroundLevel(*this)+SAFECAMERAHEIGHT;//PD 15Mar96

	if (World.Y<temp)											//PD 15Mar96
		World.Y = temp;											//PD 15Mar96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetCameraDisplacement
//Author		Paul.   
//Date			Thu 29 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong ViewPoint::GetCameraDisplacement(Viewpoint_DeltaP vdp,ANGLES viewanglestep)
{
	SWord	sin_ang,cos_ang;

	SLong	retval;

	ANGLES	anglevalue = vdp->anglevalue+vdp->anglevalue;

	anglevalue -= ANGLES_90Deg;

	Math_Lib.high_sin_cos(anglevalue,sin_ang,cos_ang);

	if (!Three_Dee.IsPaused())
	{
		SLong	modAngleStep = viewanglestep;
		modAngleStep *= vdp->scalefactor;
		modAngleStep >>= 2;
		ANGLES	newAngleStep = (Angles)((modAngleStep!=0)?modAngleStep:1);
		vdp->anglevalue += newAngleStep;
	}

	retval = sin_ang+32767;

	retval = (retval*vdp->amplitude)>>15;

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewCameraDelta
//Author		Paul.   
//Date			Thu 29 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::NewCameraDelta(Viewpoint_Delta& viewdelta)
{
	SLong	random1,random2,temp;

	random1 = Math_Lib.rnd();
	temp 	= Math_Lib.rnd();
	random1 ^= temp;
	random2 = Math_Lib.rnd();
	temp 	= Math_Lib.rnd();
	random2 ^= temp;

	viewdelta.amplitude = random1*60/32768;

	viewdelta.scalefactor = 1 + (random2 & 0x03);

	//Always move in the opposite direction to last time

	if (viewdelta.lastdir>=0)
	{
		viewdelta.lastdir=-1;
		viewdelta.amplitude=-viewdelta.amplitude;
	}
	else viewdelta.lastdir=1;

	viewdelta.anglevalue = ANGLES_0Deg;

	SLong tmp = Land_Scape.GetGroundLevel(*this)+FT_50;

	if (World.Y<tmp)	viewdelta.amplitude=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDeltaAxis
//Author		Paul.   
//Date			Thu 29 Feb 1996
//
//Description	
//
//Maths:		For each of X,Y,Z we know:
//				D = distance in CM between viewer and viewee (long)
//				S = Start vel - viewers velocity in 0.1 cm/cs units 
//				E = End vel - viewees velocity in 0.1 cm/cs units
//				R = Time to traverse whole distance in 100ths of sec
//
//		We solve 	dD/dt 	= 3att+2bt+c
//		and			D 		= attt+btt+ct+d
//		for a,b,c,d
//		The solutions are:
//			d	=	0
//			c	=	S
//			b	=	3D/RR -E/R - 2S/R
//			a	=	E/RR + S/RR - 2D/RRR
//
//			find	dD/dt and D at t=frametime
//
//			E&S are in units of cm/cs	- range +/- 32K
//							- no bits spare
//			R	in units of 1 cs	- range 50 - 32K
//							- 1 bit spare
//			D	in units of 1 cm	- range 0 - 250M
//					  		- 4 bits spare
//		To return
//			dD/dt in units 0.1 cm/cs
//			D  in units of 0.1 cm
//
//			b	=	3D/RR -(E+2S)/10R
//		range:	min		0 	-96
//			max		300K	+96
//					WB.B	00B.B
//
//			a	=	(E+S)/10RR - 2D/RRR	
//		range:	min		-32		0
//			max		+32	2*2^28/2^18=4K
//					00B.B		0BB.B
//
//			c	=	S   	;;-32K .. 32K
//					0BB.B
//
//		[frametime] = t		t	tt	ttt
//			Min	=	4	16 	64
//			Max	=	32	1024	32K
//
//		sol'n	dD/dt 	= 	3att	+2bt	+c
//			|Max|		4M	20M	32K
//
//		sol'n	D 	= 	attt	+btt	+ct
//			|Max|		128M	300M	1M
//
//
//		2D/RRR:		max RRR = 32K^3=32x10^12=32x2^40
//				max RR  = 32K^2=1G
//				min RR  = 2500 2.5K
//				max 2D	= 500M		*256 128G=Ls*64
//				max 2.256.D/RR  = 200M
//			so code as 2D / RR / R
//
//
//Inputs		end_vel      = E
//				start_vel    = S
//				dist         = D	Distance at time R
//				time_to_dist = R	time to Distance 
//				
//				viewcodeframetime	time for specific answer return
//
//Returns	req_dist=D		Distance at time [frametime]
//			req_vel =V		vel at time [frametime]
//------------------------------------------------------------------------------
void ViewPoint::GetDeltaAxis(SWord end_vel,SWord start_vel,SLong dist,SLong time_to_dist,
							SLong& req_dist, SWord& req_vel)
{
	SLong	c,b,a;
	SLong	t,t_squared,t_cubed;
	SLong	temp;

	t = time_to_dist;

	t_squared = t * t;

	c = (start_vel/10);

	b = 3*(dist/t);

	b -= ((end_vel + start_vel + start_vel)/10);

	b /= t;

	a = ((end_vel + start_vel)/10) - (20*(dist/t));

	a /= t_squared;

	t = viewcodeframetime;

	t_squared = t * t;

	t_cubed = t_squared * t;

	req_dist = (a*t_cubed) + (b*t_squared) + (c*t);

	temp = (3*a*t_squared) + (2*b*t) + c;

	req_vel = (SWord )temp*10;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstItem
//LastModified:	PD 27Jun96
//Author		Paul.   
//Date			Thu 27 Jun 1996
//
//Description	Gets the item in a list nearest the viewer
//
//Inputs		ptr to list of items,
//				nationality
//
//Returns		ptr to selected item or NULL
//
//------------------------------------------------------------------------------
itemptr ViewPoint::GetFirstItem(MobileItemPtr 	entry,
								Nationality 	side,
								SLong&			crange)
{
	SLong	deltax,deltay,deltaz;

	ANGLES	matchhdg;											//PD 05Jul96

	SLong	range;

	ANGLES	dummy1,dummy2;										//PD 05Jul96

	SLong	matchrange = visiblerange; 

	itemptr	selected = (itemptr )NULL;

	crange = 0;

	while(entry)
	{
		if(entry!=(MobileItemPtr )trackeditem)	//Not US!
		{
			if(((FormationItemPtr )entry)->nationality==side &&
				!entry->Status.deadtime)						//PD 10Sep96
			{
				deltax = trackeditem->World.X - entry->World.X;
				deltay = trackeditem->World.Y - entry->World.Y;
				deltaz = trackeditem->World.Z - entry->World.Z;

				Math_Lib.HighIntercept(	deltax,deltay,deltaz,
									range,
									dummy1,dummy2);				//PD 05Jul96

				if (Save_Data.gamedifficulty[GD_PADLOCKONLYWHENVIS])
				{
					if (VisibleTest(entry,VF_CheckVisibleArea)==TRUE && range<matchrange)
					{
							matchrange = range;
							matchhdg = dummy1;
							crange = range;
							selected = (itemptr )entry;
					}
				}
				else
				{
					if (range<matchrange)
					{
						matchrange = range;
						matchhdg = dummy1;
						crange = range;
						selected = (itemptr )entry;
					}
				}
			}
		}

		entry = entry->nextmobile;
	}

	viewitemrange=selected?matchrange:0;
//DEAD	viewitemhdg=selected?matchhdg:ANGLES_0Deg;					//PD 05Jul96

	enemyvisible = TRUE;

	if (selected!=NULL)
	{
		if (Save_Data.gamedifficulty[GD_PADLOCKONLYWHENVIS])
		{
		 	enemyvisible=VisibleTest(selected,VF_CheckVisibleArea);
		}
	}
	else
		enemytoofar=TRUE;

	return(selected);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLastItem
//Author		Paul.   
//Date			Wed 8 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
itemptr ViewPoint::GetLastItem(	MobileItemPtr 	entry,
								Nationality 	side,
								SLong&			crange)
{
	SLong	deltax,deltay,deltaz;

	ANGLES	matchhdg;

	SLong	range;

	ANGLES	dummy1,dummy2;

	SLong	matchrange = 0;

	itemptr	selected = (itemptr )NULL;

	crange = 0;

	while(entry)
	{
		if(entry!=(MobileItemPtr )trackeditem)	//Not US!
		{
			if(((FormationItemPtr )entry)->nationality==side &&
				!entry->Status.deadtime)
			{
				deltax = trackeditem->World.X - entry->World.X;
				deltay = trackeditem->World.Y - entry->World.Y;
				deltaz = trackeditem->World.Z - entry->World.Z;

				Math_Lib.HighIntercept(	deltax,deltay,deltaz,
									range,
									dummy1,dummy2);

				if (Save_Data.gamedifficulty[GD_PADLOCKONLYWHENVIS])
				{
					if (VisibleTest(entry,VF_CheckVisibleArea)==TRUE && range>matchrange)
					{
							matchrange = range;
							matchhdg = dummy1;
							crange = range;
							selected = (itemptr )entry;
					}
				}
				else
				{
					if (range>matchrange)
					{
						matchrange = range;
						matchhdg = dummy1;
						crange = range;
						selected = (itemptr )entry;
					}
				}
			}
		}

		entry = entry->nextmobile;
	}

	viewitemrange=selected?matchrange:0;
//DEAD	viewitemhdg=selected?matchhdg:ANGLES_0Deg;					//PD 05Jul96

	enemyvisible = TRUE;

	if (selected!=NULL)
	{
		if (Save_Data.gamedifficulty[GD_PADLOCKONLYWHENVIS])
		{
		 	enemyvisible=VisibleTest(selected,VF_CheckVisibleArea);
		}
	}
	else
		enemytoofar=TRUE;

	return(selected);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNextItem
//LastModified:	PD 27Jun96
//Author		Paul.   
//Date			Thu 27 Jun 1996
//
//Description	Gets the item in a list nearest the viewer further
//				away than the last one
//
//Inputs		ptr to list of items,
//				ptr to currently selected item,
//				nationality, 
//				current selected item range
//
//Returns		ptr to selected item or NULL
//
//------------------------------------------------------------------------------
itemptr ViewPoint::GetNextItem(	MobileItemPtr 	list,
								MobileItemPtr 	entry,
								Nationality 	side,
								SLong&			crange)
{
	SLong	deltax,deltay,deltaz;

	SLong	range;

	ANGLES	dummy1,dummy2,matchhdg;								//PD 05Jul96

	SLong	matchrange = visiblerange;							//PD 27Aug96

	deltax = trackeditem->World.X - entry->World.X;				//PD 20Aug96
	deltay = trackeditem->World.Y - entry->World.Y;				//PD 20Aug96
	deltaz = trackeditem->World.Z - entry->World.Z;				//PD 20Aug96

	Math_Lib.HighIntercept(	deltax,deltay,deltaz,					//PD 20Aug96
						crange,									//PD 20Aug96
						dummy1,dummy2);							//PD 20Aug96

	itemptr	selected = (itemptr )NULL;

	while(list)
	{
		if(list!=(MobileItemPtr )trackeditem && list!=entry && !list->Status.deadtime)//PD 14Nov96
			//Not us OR last OR dead							//PD 14Nov96
		{
			if(((FormationItemPtr )list)->nationality==side)	//RDH 21Aug96
			{
				deltax = trackeditem->World.X - list->World.X;
				deltay = trackeditem->World.Y - list->World.Y;
				deltaz = trackeditem->World.Z - list->World.Z;

				Math_Lib.HighIntercept(	deltax,deltay,deltaz,
									range,
									dummy1,dummy2);				//PD 05Jul96

				if (range<matchrange && range>crange)
				{
					matchrange = range;
					matchhdg = dummy1;
					selected = (itemptr )list;
				}
			}
		}
		list = list->nextmobile;
	}

	//Reset current range to 0 if none selected

	crange = selected?matchrange:0;

	viewitemrange=crange;
//DEAD	viewitemhdg = selected?matchhdg:ANGLES_0Deg;				//PD 05Jul96

	return(selected);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPrevItem
//Author		Paul.   
//Date			Wed 8 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
itemptr ViewPoint::GetPrevItem(	MobileItemPtr 	list,
								MobileItemPtr 	entry,
								Nationality 	side,
								SLong&			crange)
{
	SLong	deltax,deltay,deltaz;

	SLong	range;

	ANGLES	dummy1,dummy2,matchhdg;

	SLong	matchrange = 0;

	deltax = trackeditem->World.X - entry->World.X;
	deltay = trackeditem->World.Y - entry->World.Y;
	deltaz = trackeditem->World.Z - entry->World.Z;

	Math_Lib.HighIntercept(	deltax,deltay,deltaz,
						crange,
						dummy1,dummy2);

	itemptr	selected = (itemptr )NULL;

	while(list)
	{
		if(list!=(MobileItemPtr )trackeditem && list!=entry && !list->Status.deadtime)//PD 14Nov96
			//Not us OR last OR dead
		{
			if(((FormationItemPtr )list)->nationality==side)
			{
				deltax = trackeditem->World.X - list->World.X;
				deltay = trackeditem->World.Y - list->World.Y;
				deltaz = trackeditem->World.Z - list->World.Z;

				Math_Lib.HighIntercept(	deltax,deltay,deltaz,
									range,
									dummy1,dummy2);

				if (range>matchrange && range<crange)
				{
					matchrange = range;
					matchhdg = dummy1;
					selected = (itemptr )list;
				}
			}
		}
		list = list->nextmobile;
	}

	//Reset current range to 0 if none selected

	crange = selected?matchrange:0;

	viewitemrange=crange;
//DEAD	viewitemhdg = selected?matchhdg:ANGLES_0Deg;

	return(selected);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstMessage
//Author		Paul.   
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
itemptr	ViewPoint::GetFirstMessage()
{
//	_MsgBuffer.InitMessageWindow();
//	if (_MsgBuffer.Callsign(1)!="" || _MsgBuffer.MessageBody(1)!="")
//	{
//		AirStrucPtr dummy;
//		itemptr itemPtr;
//		_MsgBuffer.MessageParticipants(1,dummy,dummy,itemPtr);
		if (itemTalkedAbout==Persons2::PlayerGhostAC || itemTalkedAbout==Persons2::PlayerSeenAC)
			return NULL;
//		else
		return (itemptr)itemTalkedAbout;
//	}
//	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UISetViewItemShape
//Author		Paul.   
//Date			Thu 28 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::UISetViewItemShape(ShapeNum shpno)
{
	if (trackeditem)
		trackeditem->shape = shpno;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetViewedItem
//Author		Paul.   
//Date			Thu 28 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
itemptr ViewPoint::UIGetViewedItem()
{
	return	currentvehicle;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateGlobalViewRec
//Author		Paul.   
//Date			Thu 4 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::UpdateGlobalViewRec()
{
	currentviewrec->hdg += (Angles )((bfrotaterate * viewcodeframetime)/10);//PD 04Apr96
	currentviewrec->pitch += (Angles )((bfpitchrate * viewcodeframetime)/10);//PD 04Apr96
	currentviewrec->roll += (Angles )((bfrollrate * viewcodeframetime)/10);//PD 04Apr96

	//Just copy the current viewrec to the global viewrec
	//Smooth changes handled in UpdateGlobalHPR()				//PD 14Jun96

	globalviewrec->range = currentviewrec->range;
	globalviewrec->hdg = currentviewrec->hdg;
	globalviewrec->pitch = currentviewrec->pitch;
	globalviewrec->roll = currentviewrec->roll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateGlobalHPR
//Author		Paul.   
//Date			Fri 5 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::UpdateGlobalHPR()
{
	ViewCutType	oldvct;

	oldvct = viewnum.viewcuttype;

	if (straightback)
	{
		straightback=FALSE;
		viewnum.viewcuttype=Instant;
	}

	switch (viewnum.viewcuttype)
	{
		case VSlow:
		{
			ANGLES	tempangle;
			UWord	tempangle_pos;
			SWord	tempangle_sign;

			//Smooth PITCH
		
			tempangle = this->actpitch - this->reqpitch;
		
			Math_Lib.Pos ((SWord) tempangle,tempangle_pos,tempangle_sign);
		
			//Modify step size based on the size of change required

			if (tempangle_pos>viewcodeframetime)
				tempangle_pos = 2 + ((tempangle_pos * viewcodeframetime)>>5);

			if (tempangle_sign==MathLib::NEGATIVE)
				actpitch += (Angles) tempangle_pos;
			else
				actpitch -= (Angles) tempangle_pos;

			//Smooth HEADING

			tempangle = this->acthdg - this->reqhdg;
			
			Math_Lib.Pos ((SWord) tempangle,tempangle_pos,tempangle_sign);
		
			//Modify step size based on the size of change required

			if (tempangle_pos>viewcodeframetime)
				tempangle_pos = 2 + ((tempangle_pos * viewcodeframetime)>>5);

			if (tempangle_sign==MathLib::NEGATIVE)
				acthdg += (Angles) tempangle_pos;
			else
				acthdg -= (Angles) tempangle_pos;

			//no lag for roll

			actroll=reqroll;
		}
		break;

		case Gradual:
/*		{
			ANGLES	tempangle;
			UWord	tempangle_pos;								//DAW 03May96
			SWord	tempangle_sign;								//DAW 03May96

			//Smooth PITCH
		
			tempangle = this->actpitch - this->reqpitch;
		
			Math_Lib.Pos ((SWord) tempangle,tempangle_pos,tempangle_sign);
		
			//Modify step size based on the size of change required

			if (tempangle_pos>viewcodeframetime)				//PD 02Sep96
				tempangle_pos = 2 + (tempangle_pos * viewcodeframetime)>>5;//PD 06Sep96

			if (tempangle_sign==MathLib::NEGATIVE)
				actpitch += (Angles) tempangle_pos;
			else
				actpitch -= (Angles) tempangle_pos;

			//Smooth HEADING

			tempangle = this->acthdg - this->reqhdg;
			
			Math_Lib.Pos ((SWord) tempangle,tempangle_pos,tempangle_sign);
		
			//Modify step size based on the size of change required

			if (tempangle_pos>viewcodeframetime)				//PD 02Sep96
				tempangle_pos = 2 + (tempangle_pos * viewcodeframetime)>>5;//PD 06Sep96

			if (tempangle_sign==MathLib::NEGATIVE)
				acthdg += (Angles) tempangle_pos;
			else
				acthdg -= (Angles) tempangle_pos;
		
			actroll = reqroll;									//PD 25Sep96
		}
		break;
*/
		case Instant:
		{
			this->acthdg = this->reqhdg;
			this->actpitch = this->reqpitch;
			this->actroll = this->reqroll;
		}
		break;
	}

	this->pitch = this->actpitch;								//PD 02May96
	this->hdg = this->acthdg;
	this->roll = this->actroll;

	if (flakwobble)
	{
		this->pitch += (Angles)(Math_Lib.rnd(ANGLES_2Deg) - ANGLES_1Deg);	//JIM 28Nov96
		this->roll += (Angles)(Math_Lib.rnd(ANGLES_2Deg) - ANGLES_1Deg);	//JIM 28Nov96

		flakwobble--;
	}

	if (stallwobble)
	{
		this->pitch += (Angles)(Math_Lib.rnd(ANGLES_1Deg)-ANGLES_HalfDeg);//JIM 28Nov96
		this->roll += (Angles)(Math_Lib.rnd(ANGLES_1Deg)-ANGLES_HalfDeg);	//JIM 28Nov96

		stallwobble--;
	}

	if (pitch > ANGLES_90Deg || pitch < ANGLES_270Deg)			//RDH 24Jul96
	{
		pitch = -pitch;
		pitch += ANGLES_180Deg;
		hdg += ANGLES_180Deg;
		roll += ANGLES_180Deg;
	}
	viewnum.viewcuttype=oldvct;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModifyView
//Author		Paul.   
//Date			Wed 26 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ViewPoint::ModifyView()
{
	Bool retval = TRUE;

	ViewCutType	oldvct=viewnum.viewcuttype;
	viewnum.viewcuttype=Instant;

	if (viewnum.viewmode==VM_Inside)
	{
		viewnum.viewmode=VM_InPadlock;
		InitInPadlock();
		DrawInPadlock();

		if (!trackeditem2)	retval = FALSE;
	}
	else
	{
		if (viewnum.viewmode==VM_Track)
		{
			viewnum.viewmode=VM_OutPadlock;
			InitOutPadlock();
			DrawOutPadlock();

			if (!trackeditem2)	retval = FALSE;
		}
	}
	viewnum.viewcuttype=oldvct;
	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VisibleTest
//LastModified:	PD 05Jul96
//Author		Paul.   
//Date			Thu 27 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ViewPoint::VisibleTest(itemptr itmp,VisFlags vf)
{
	if (vf==VF_DontCare) return (TRUE);

	Bool	retval;

	SLong	deltax,deltay,deltaz;

	ANGLES	tihdg,tipitch,tiroll;

	MATRIX	tmat;												//PD 25Jul96

	MATRIX_PTR	tmatrix = &tmat;								//PD 25Jul96

	_matrix.generate(this->hdg,this->pitch,this->roll,tmatrix);

	deltax = itmp->World.X - this->World.X;
	deltay = itmp->World.Y - this->World.Y;
	deltaz = itmp->World.Z - this->World.Z;

	(void )_matrix.transform(tmatrix,deltax,deltay,deltaz);

	if (deltaz<=0)	return(FALSE);

	deltax=(deltax<0)?-deltax:deltax;
	deltay=(deltay<0)?-deltay:deltay;

	if (deltax>deltaz)	return(FALSE);

	if (deltay>deltaz)	return(FALSE);

	return(TRUE);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ItemInDeadZone
//Author		Paul.   
//Date			Thu 27 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ViewPoint::ItemInDeadZone(itemptr itmp)
{
	Bool	retval;

	SLong	deltax,deltay,deltaz;

	ANGLES	tihdg,tipitch,tiroll;

	MATRIX	tmat;												//PD 25Jul96

	MATRIX_PTR	tmatrix = &tmat;								//PD 25Jul96

	tihdg = ((MobileItemPtr )itmp)->hdg;
	tipitch = ((MobileItemPtr )itmp)->pitch;
	tiroll = ((MobileItemPtr )itmp)->roll;

	deltax = itmp->World.X - trackeditem->World.X;
	deltay = itmp->World.Y - trackeditem->World.Y;
	deltaz = itmp->World.Z - trackeditem->World.Z;

	deltax >>= 6; deltay >>= 6; deltaz >>= 6;	//Down to 64cm units

	_matrix.generate(	tihdg,									//PD 25Jul96
						tipitch,tiroll,
						tmatrix
					);
			
	_matrix.rotate(	tmatrix,
					deltax,deltay,deltaz
					);

	retval = FALSE;

	//Hdg in a/c coordinate space ie North is to the
	//front of the viewitem

	tihdg = Math_Lib.HighArcTan((SWord )deltax,(SWord )deltaz);

	tipitch=Math_Lib.HighArcTan((SWord )deltay,(SWord )deltax);

	const UWord dpitchstrt = (UWord )ANGLES_90Deg;
	const UWord dpitchend  = (UWord )ANGLES_315Deg;

	const UWord dhdgstrt = (UWord )ANGLES_135Deg;
	const UWord dhdgend  = (UWord )ANGLES_225Deg;

	if (dhdgstrt<(UWord )tihdg && dhdgend>(UWord )tihdg)
		retval = TRUE;

	if (dpitchstrt<(UWord )tipitch && dpitchend>(UWord )tipitch)
		retval = TRUE;

	return (retval);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetViewedAc
//Author		Paul.   
//Date			Mon 19 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStrucPtr	ViewPoint::GetViewedAc()
{
	ItemPtr		itm;

	if (trackeditem2!=NULL)
		itm = trackeditem2;
	else
		itm = trackeditem;

	if (itm==NULL)
		return((AirStrucPtr)NULL);

	if (itm->Status.size!=AirStrucSize)
		return((AirStrucPtr)NULL);

	return ((AirStrucPtr)itm);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PossDirectAction
//Author		Paul.   
//Date			Tue 10 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::PossDirectorAction(Coords3D&	dirworld)		//RJS 24May99
{
	if (directorcount==0)
	{
		DirectorItem.World=dirworld;	//diritem->World;
		currentdirectoritem = &DirectorItem;
		DirectorItem.shape=EMPTY;
		directorcount = DIRECTOR_VIEW_DELAY;

		View_RecP	temp;
		temp = currentviewrec;
		currentviewrec=paintshopviewrec;
		ResetZoomRotate((ZmRtFlags )NULL);
		currentviewrec->range=25000;		//125m
		currentviewrec=temp;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ControlDirectorView
//Author		Paul.   
//Date			Tue 10 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ControlDirectorView()
{
	ViewCutType oldvctype;

	oldvctype = viewnum.viewcuttype;

	if (Manual_Pilot.ControlledAC2 &&
		Manual_Pilot.ControlledAC2->Status.deadtime &&
		Manual_Pilot.ControlledAC2->weap.Ejected)
	{
		directorcount=0;
		viewnum.viewspec |= VS_Impact;
	}

	if (viewnum.viewspec & VS_Impact)
	{
		switch (directorcount)
		{
			case 0:				//No director item to view

				return;

			case DIRECTOR_VIEW_DELAY:	//New director item to view
				dirviewnum = viewnum;
				viewnum.viewmode = VM_Track;
				trackeditem = currentdirectoritem;
				currentviewrec = paintshopviewrec;
				bupviewdrawrtn = NULL;							//PD 28Jan97
				viewdrawrtn = DrawTrack;
				drawpolypit = FALSE;
				viewnum.viewcuttype=Instant;
				DrawTrack();
				directorcount -= viewcodeframetime;
				break;

			default:			//Current director item to view
				directorcount -= viewcodeframetime;
				if (directorcount <= 0)
				{
					viewnum = dirviewnum;
					currentdirectoritem = NULL;
					viewnum.viewcuttype=Instant;
					SetViewFromNum(viewnum);
					directorcount = 0;
				}
				break;
		}
	}
	viewnum.viewcuttype=oldvctype;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRoll4HdgAndPitch
//Author		Paul.   
//Date			Tue 26 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::GetRoll4HdgAndPitch(ANGLES& rhdg,ANGLES& rpitch,ANGLES& rroll)
{
	ANGLES		hdgint,
				pitchint,
				rollint,
				intercepthdg,
				interceptpitch,
				interceptroll;

	intercepthdg 	= -rhdg;
	interceptpitch	= -rpitch;
	interceptroll 	= ANGLES_0Deg;

	hdgint = ((MobileItemPtr )trackeditem)->hdg;
	pitchint = ((MobileItemPtr )trackeditem)->pitch;
	rollint = ((MobileItemPtr )trackeditem)->roll;

	intercepthdg -= hdgint;
	interceptpitch -= pitchint;

	_matrix.TransformAngles(hdgint,pitchint,rollint,
							intercepthdg,interceptpitch,interceptroll);

	rhdg = intercepthdg;
	rpitch = interceptpitch;
	rroll= interceptroll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CockpitOrientation
//Author		Paul.   
//Date			Wed 3 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong ViewPoint::CockpitOrientation(Window* win,PVList* pvlp,SLong)
{
//TempCode PD 18Nov97 	MobileItemPtr	mip;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	MATRIX	fakeViewerMatrix;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	SLong	dx,dy,dz;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	SLong	wvMinX,wvMaxX,wvMinY,wvMaxY;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	SLong	sX,sY;

	SLong	howMany = 0;

//TempCode PD 18Nov97 	SWord	sgnBz;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	if (!Save_Data.gamedifficulty[GD_PERIPHERALVISION] ||
//TempCode PD 18Nov97 		viewnum.viewmode!=VM_InPadlock)
//TempCode PD 18Nov97 		return (howMany);
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	mip = (MobileItemPtr)currentvehicle;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	_matrix.generate(-mip->hdg,-mip->pitch,-mip->roll,&fakeViewerMatrix);
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	dx = trackeditem2->World.X - mip->World.X;
//TempCode PD 18Nov97 	dy = trackeditem2->World.Y - mip->World.Y;
//TempCode PD 18Nov97 	dz = trackeditem2->World.Z - mip->World.Z;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	SWord scaleFactor = _matrix.transform(&fakeViewerMatrix,dx,dy,dz);
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	sgnBz = dz<0?-1:1;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	dz = dz<0?-dz:dz;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	VERTEX	v;
//TempCode PD 18Nov97 	v.scalefactor=scaleFactor;
//TempCode PD 18Nov97 	v.bx = dx;
//TempCode PD 18Nov97 	v.by = dy;
//TempCode PD 18Nov97 	v.bz = dz;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	if (Save_Data.colourdepth!=8)
//TempCode PD 18Nov97 	{
//TempCode PD 18Nov97 		currwin->Body2Screen(FULLW_2,FULLW_2,v);
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 		sX = v.sx; sY = v.sy;
//TempCode PD 18Nov97 	}
//TempCode PD 18Nov97 	else
//TempCode PD 18Nov97 	{
//TempCode PD 18Nov97 		_matrix.body2screen(v);
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 		sX = v.sx * win->virtualXscale;
//TempCode PD 18Nov97 		sY = v.sy * win->virtualYscale;
//TempCode PD 18Nov97 	}
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	wvMinX = win->VirtualMinX;
//TempCode PD 18Nov97 	wvMinY = win->VirtualMinY;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	wvMaxX = wvMinX+win->VirtualWidth-PIXEL640;
//TempCode PD 18Nov97 	wvMaxY = wvMinY+win->VirtualHeight-PIXEL640;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	if (sgnBz==1 &&
//TempCode PD 18Nov97 		sX>=wvMinX && sX<=wvMaxX &&
//TempCode PD 18Nov97 		sY>=wvMinY && sY<=wvMaxY)	return (howMany);
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	UByte	flag = 0;
//TempCode PD 18Nov97 	
//TempCode PD 18Nov97 	if (sX<wvMinX)			{sX = wvMinX;flag|=0x02;}
//TempCode PD 18Nov97 	else if (sX>wvMaxX)		{sX = wvMaxX;flag|=0x01;}
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	if (sY<wvMinY)			{sY = wvMinY;flag|=0x08;}
//TempCode PD 18Nov97 	else if (sY>wvMaxY)		{sY = wvMaxY;flag|=0x04;}
//TempCode PD 18Nov97 			
//TempCode PD 18Nov97 	pvlp->sx = sX;
//TempCode PD 18Nov97 	pvlp->sy = sY;
//TempCode PD 18Nov97 	pvlp->edgeflag = flag;
//TempCode PD 18Nov97 	pvlp->intensity = 0xFF;
//TempCode PD 18Nov97 	pvlp++;
//TempCode PD 18Nov97 	howMany++;

	return (howMany);
}

//TempCode PD 13Mar98 ANGLES GetRequiredRoll(rotitem& srcItem,rotitem& trgItem)
//TempCode PD 13Mar98 {
//TempCode PD 13Mar98 	const Float _PI=22/7;
//TempCode PD 13Mar98  	FPMATRIX fpmMatrix;
//TempCode PD 13Mar98 	_matrix.generate(srcItem.hdg,srcItem.pitch,srcItem.roll,&fpmMatrix);
//TempCode PD 13Mar98 	IFShare	x,y,z;
//TempCode PD 13Mar98 	x.i=srcItem.World.X-trgItem.World.X;
//TempCode PD 13Mar98 	y.i=srcItem.World.Y-trgItem.World.Y;
//TempCode PD 13Mar98 	z.i=srcItem.World.Z-trgItem.World.Z;
//TempCode PD 13Mar98 	_matrix.transform(&fpmMatrix,x,y,z);
//TempCode PD 13Mar98 	if (z.f<0.) z.f=-z.f;
//TempCode PD 13Mar98 	x.f/=z.f;
//TempCode PD 13Mar98 	y.f/=z.f;
//TempCode PD 13Mar98 	_asm {
//TempCode PD 13Mar98 		fld x.f;
//TempCode PD 13Mar98 		fld y.f;
//TempCode PD 13Mar98 		fpatan;
//TempCode PD 13Mar98 		fstp x.f;
//TempCode PD 13Mar98 	}
//TempCode PD 13Mar98 	//x.f is required angle in radians
//TempCode PD 13Mar98 	x.f=Float(32768)*x.f/_PI;
//TempCode PD 13Mar98 	return (Angles)(UWord)x.f;
//TempCode PD 13Mar98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildPeripheralVisionList
//Author		Paul.   
//Date			Tue 22 Jul 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong ViewPoint::BuildPeripheralVisionList(Window* win,PVList* pvlp,SLong maxEntries)
{
	SLong		howMany = 0;

 	if (!Manual_Pilot.ControlledAC2 || !Save_Data.gamedifficulty[GD_PERIPHERALVISION])	
		return (howMany);//PD 21Aug97
	FPMATRIX tmat,*tmatp=&tmat;
	FormationItemPtr us=(FormationItemPtr)trackeditem;
	Nationality their_side=natenemy;//(Manual_Pilot.ControlledAC2->nationality==NAT_BLUE)?NAT_RED:NAT_BLUE;
	MobileItemPtr listp=ACList;

	_matrix.Generate(this->hdg,this->pitch,this->roll,tmatp);

	while (listp!=NULL && howMany<maxEntries)
	{
		if (listp!=(MobileItemPtr)trackeditem &&
			!listp->Status.deadtime)
		{
			//Check position for this item

			IFShare dx,dy,dz;

			dx.i=listp->World.X-this->World.X;
			dy.i=listp->World.Y-this->World.Y;
			dz.i=listp->World.Z-this->World.Z;

			_matrix.transform(tmatp,dx,dy,dz);

			if (dz.f>=Float(1))	// don't display a/c behind the viewer
			{
				SLong	irange;
				SWord	ihdg,ipitch;

				SLong	hi,pi;

				Math_Lib.HighIntercept(SLong(dx.f),SLong(dy.f),SLong(dz.f),irange,ihdg,ipitch);

				UByte col=((FormationItemPtr)listp)->nationality==their_side?UByte(RED):UByte(197);

				if (irange<viewrangemax)
					currwin->DoPeripheralBlob(&dx.f,&dy.f,&dz.f,col,0);
			}
		}
		listp=listp->nextmobile;
	}
	return (0);
}

void ViewPoint::GetThreatData(SWord& count,COORDS3D* pCoords,UByte* pColour,const SLong MAX_RANGE)
{
	MobileItemPtr ac=(MobileItemPtr)Manual_Pilot.ControlledAC2;

	if (!ac)
	{
		count=-1;
		return;
	}
	FPMATRIX tmat,*tmatp=&tmat;

	FormationItemPtr us=(FormationItemPtr)trackeditem;

	Nationality their_side=natenemy;//(ac->nationality==NAT_BLUE)?NAT_RED:NAT_BLUE;

	MobileItemPtr listp=ACList;

	_matrix.GenerateV(-ac->hdg,-ac->pitch,-ac->roll,tmatp);
//	_matrix.GenerateV(ac->hdg,ac->pitch,ac->roll,tmatp);

	SWord max_blobs=count-1;

	count=-1;

	while (listp!=NULL && count<max_blobs)
	{
		if (listp!=(MobileItemPtr)trackeditem && !listp->Status.deadtime)
		{
			//Check position for this item

			IFShare dx,dy,dz;

			dx.i=listp->World.X-ac->World.X;
			dy.i=listp->World.Y-ac->World.Y;
			dz.i=listp->World.Z-ac->World.Z;

			_matrix.transform(tmatp,dx,dy,dz);

			SLong	irange;
			SWord	ihdg,ipitch;

			Math_Lib.HighIntercept(SLong(dx.f),SLong(dy.f),SLong(dz.f),irange,ihdg,ipitch);

			if (irange<MAX_RANGE)
			{
				++count;
				pCoords[count].X=SLong(dx.f);
				pCoords[count].Y=SLong(dy.f);
				pCoords[count].Z=SLong(dz.f);
				pColour[count]=((FormationItemPtr)listp)->nationality==their_side?1:0;
			}
		}
		listp=listp->nextmobile;
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadJoystick
//Author		Paul.   
//Date			Tue 16 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::ReadJoystick(	SWord& swHdg,
								SWord& swPitch,
								SWord& swRoll,
								SWord& swZoom)
{
//TempCode PD 18Nov97 	SWord			xy[4];
//TempCode PD 18Nov97 	AxisUsesField	auf;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	auf|=AU_VIEWH;
//TempCode PD 18Nov97 	auf|=AU_VIEWP;
//TempCode PD 18Nov97 	auf|=AU_VIEWR;
//TempCode PD 18Nov97 	auf|=AU_VIEWZ;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	_Analogue.ReadPosition(auf,xy);
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	for (int i=0;i<4;i++) if (xy[i]==-0x8000) xy[i]=0;
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	swHdg = xy[0]; swPitch = xy[1]; swRoll = xy[2]; swZoom = xy[3];
//TempCode PD 18Nov97 
//TempCode PD 18Nov97 	swZoom = (swZoom<0)?-swZoom:swZoom;							//PD 16Sep97

//	swHdg=swPitch=swRoll=swZoom=0;
	swHdg=analview[JOY_HEAD];
	swPitch=analview[JOY_PITCH];
	swRoll=analview[JOY_ROLL];
	swZoom=analview[JOY_ZOOM];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UseIdentityMatrix
//Author		Paul.   
//Date			Fri 9 Oct 1998
//------------------------------------------------------------------------------
Bool ViewPoint::UseIdentityMatrix()
{
	if (viewdrawrtn==DrawInside &&
		currentviewrec==insideviewrec &&
		currentviewrec->hdg==ANGLES_0Deg &&
		currentviewrec->pitch==ANGLES_0Deg &&
		currentviewrec->roll==ANGLES_0Deg)
		return TRUE;

	return FALSE;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitMap
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::InitMap()
{
	trackeditem = currentvehicle;
	currentviewrec = maprec;
	bupviewdrawrtn = NULL;				
	viewdrawrtn = DrawMap;										
	drawpolypit = FALSE;
	drawmap = TRUE;

	drawSpecialFlags |= VIEW_SPECIAL_MAP;
	OverLay.SetToMapScreen();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitMapAccel
//Author		Paul.   
//Date			Wed 3 Mar 1999
//------------------------------------------------------------------------------
void ViewPoint::InitMapAccel()
{
	trackeditem = currentvehicle;
	currentviewrec = maprec;
	bupviewdrawrtn = NULL;				
	viewdrawrtn = DrawMap;										
	drawpolypit = FALSE;
	drawmap = TRUE;

	drawSpecialFlags |= VIEW_SPECIAL_MAP;
	OverLay.SetToMapAccelScreen();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawMap
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::DrawMap()
{
	ViewCutType	temp = viewnum.viewcuttype;
	viewnum.viewcuttype = Instant;

	CopyPosition(trackeditem,this);

//	World.Y = FT_20000;
//	World.X += (FT_20000 >> 1);
	World.Y = FT_40000;
//	World.X += (FT_40000 >> 1);

	UpdateGlobalViewRec();										
	AddViewRec(false);												  //JIM 01/09/99//DAW 02Sep99
	UpdateGlobalHPR();											

	viewnum.viewcuttype = temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitPrefs
//Author		Paul.   
//Date			Thu 19 Nov 1998
//------------------------------------------------------------------------------
void ViewPoint::InitPrefs()
{
//DeadCode PD 20Nov98 	assert(false&&"Write me!");
//DeadCode PD 16Feb99 	ViewCutType	temp=viewnum.viewcuttype;
//DeadCode PD 16Feb99 	viewnum.viewcuttype=Instant;
//DeadCode PD 16Feb99 
//DeadCode PD 16Feb99 	trackeditem = currentvehicle;
//DeadCode PD 16Feb99 	currentviewrec = prefsrec;
//DeadCode PD 16Feb99 	ResetZoomRotate((ZmRtFlags )NULL);
//DeadCode PD 16Feb99 	UpdateGlobalViewRec();
//DeadCode PD 16Feb99 	bupviewdrawrtn = NULL;										//PD 28Jan97
//DeadCode PD 16Feb99 	viewdrawrtn = DrawPrefs;
//DeadCode PD 16Feb99 	drawpolypit = FALSE;
//DeadCode PD 16Feb99 	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);	//RJS 20Oct98
//DeadCode PD 16Feb99 	drawmap = FALSE;
//DeadCode PD 16Feb99 	OverLay.fPausedForPrefs=true;
//DeadCode PD 16Feb99 	OverLay.InitPrefs3D();
//DeadCode PD 16Feb99 
//DeadCode PD 16Feb99 	viewnum.viewcuttype=temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawPrefs
//Author		Paul.   
//Date			Thu 19 Nov 1998
//------------------------------------------------------------------------------
void ViewPoint::DrawPrefs()
{
//DeadCode PD 16Feb99 	ViewCutType	temp=viewnum.viewcuttype;
//DeadCode PD 16Feb99 	viewnum.viewcuttype=Instant;
//DeadCode PD 16Feb99 
//DeadCode PD 16Feb99  	CopyPositionHP(trackeditem,this);
//DeadCode PD 16Feb99 	this->reqhdg = -this->reqhdg;
//DeadCode PD 16Feb99 	this->reqpitch = -this->reqpitch;
//DeadCode PD 16Feb99 	this->reqroll = -this->reqroll;
//DeadCode PD 16Feb99 	currentviewrec->hdg+=(Angles )((SWord(ANGLES_2Deg)*viewcodeframetime)/10);
//DeadCode PD 16Feb99 //	currentviewrec->hdg+=(Angles )((SWord(ANGLES_2Deg)*10)/10);
//DeadCode PD 16Feb99 	UpdateGlobalViewRec();
//DeadCode PD 16Feb99 	AddViewRec();
//DeadCode PD 16Feb99 	UpdateGlobalHPR();
//DeadCode PD 16Feb99 	AddZoom();
//DeadCode PD 16Feb99 //	viewnum.viewcuttype = temp;
//DeadCode PD 16Feb99 
//DeadCode PD 16Feb99 	viewnum.viewcuttype=temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		List8Toggle
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ViewPoint::List8Toggle()
{
//DeadCode DAW 13Jul99 	if (viewnum.viewmode!=VM_Map && !Accel())
	if (viewnum.viewmode!=VM_Map && !Accel() && !_DPlay.Implemented)//DAW 13Jul99
	{
		if (OverLay.pCurScr==NULL)
		{
			premapviewnum=viewnum;
			premapviewdrawrtn=viewdrawrtn;
			premapdrawpolypit=drawpolypit;
			premapviewrec=currentviewrec;

			viewnum.viewmode = VM_Map;
			viewsetuprtn = InitMap;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		List9Toggle
//Author		Paul.   
//Date			Wed 3 Mar 1999
//------------------------------------------------------------------------------
void ViewPoint::List9Toggle()
{
//DeadCode AMM 10Jun99 	if (_DPlay.Implemented && _DPlay.accelselected!=_DPlay.ActivePlayers)
//DeadCode AMM 10Jun99 	{
//DeadCode AMM 10Jun99 		_DPlay.SendStartAccelSelectedMessage();
//DeadCode AMM 10Jun99 	}
//DeadCode AMM 10Jun99 	else if (viewnum.viewmode!=VM_Map && !Accel())
//DeadCode AMM 10Jun99 	{
//DeadCode DAW 13Jul99 	if (viewnum.viewmode!=VM_Map && !Accel())
	if (viewnum.viewmode!=VM_Map && !Accel() && !_DPlay.Implemented)//DAW 13Jul99
	{
		if (OverLay.pCurScr==NULL)
		{
			//backup some variables so the view can be restored later...
			premapviewnum=viewnum;
			premapviewdrawrtn=viewdrawrtn;
			premapdrawpolypit=drawpolypit;
			premapviewrec=currentviewrec;

			viewnum.viewmode = VM_Map;
			viewsetuprtn = InitMapAccel;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetReplay
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ViewPoint::SetReplayView(Bool	active)
{
	if (this)
	{
		drawSpecialFlags = VIEW_SPECIAL_NULL;

		if (active)
			drawSpecialFlags |= VIEW_SPECIAL_REPLAY;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCheatItem
//Author		Robert Slater
//Date			Mon 9 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ViewPoint::SetCheatItem(ItemPtr	itm)
{
	trackeditem2 = itm;

	trackeditem = itm;
	currentviewrec = outpadlockviewrec;
	bupviewdrawrtn = NULL;						
	viewdrawrtn = DrawOutPadlock;
	drawpolypit = FALSE;
	drawSpecialFlags -= (drawSpecialFlags & VIEW_SPECIAL_MAP);
	drawmap = FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReturnFromMap
//Author		Paul.   
//Date			Tue 16 Feb 1999
//------------------------------------------------------------------------------
void ViewPoint::ReturnFromMap()
{
//DeadCode AMM 10Jun99 	_DPlay.SendAccelDeselectedMessage();

	viewnum=premapviewnum;
	viewdrawrtn=premapviewdrawrtn;
	drawpolypit=premapdrawpolypit;
	currentviewrec=premapviewrec;
	straightback=TRUE;
	drawmap=FALSE;
	drawSpecialFlags-=(drawSpecialFlags&VIEW_SPECIAL_MAP);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExecuteMapViewCommand
//Author		Paul.   
//Date			Fri 12 Mar 1999
//------------------------------------------------------------------------------
void ViewPoint::ExecuteMapViewCommand(UByte k)
{
	viewcodeframetime=RealFrameTime();
	switch (k)
	{
	case SEL_1:	//rotate left
		HandleRotate(ZR_RotRght);
		break;
	case SEL_2:	//rotate right
		HandleRotate(ZR_RotLft);
		break;
	case SEL_3:	//zoom out
		HandleZoom(ZR_ZoomOut);
		break;
	case SEL_4:	//zoom in
		HandleZoom(ZR_ZoomIn);
		break;
	case SEL_5:	//reset view
		ResetZoomRotate((ZmRtFlags)NULL);
		trackviewrec->pitch=ANGLES_45Deg;
		break;
	default:
		break;
	}
}

void ViewPoint::UpdatePosWRTEye()
{
	if (trackeditem && trackeditem->Status.size>=MobileSize)
	{
		COORDS3D dummy,eye;
		MobileItemPtr mip=(MobileItemPtr)trackeditem;
		MobileItemPtr ip=new MobileItem;
		ip->shape=mip->shape;
		ip->World=mip->World;
		ip->hdg=mip->hdg;
		ip->pitch=mip->pitch;
		ip->roll=mip->roll;
		SHAPE.GetContactPoint(ip,CT_EYE,eye,dummy,dummy);
		ip->Anim=NULL;
		delete ip;
		this->World.X=eye.X;
		this->World.Y=eye.Y;
		this->World.Z=eye.Z;
	}
}
void ViewPoint::Quit3D(UWord delay)
{
	if (	((quit3dtimer==0xFFFF) || (delay < quit3dtimer))		//RJS 02Jun99
		&& !_Replay.Playback && !_DPlay.Implemented			)		//RJS 02Jun99
		quit3dtimer=delay;
}

void ViewPoint::AnalogRead()
{
	analview[JOY_HEAD]=_Analogue.ReadPosition(AU_VIEWH);
	analview[JOY_PITCH]=_Analogue.ReadPosition(AU_VIEWP);
	analview[JOY_ROLL]=_Analogue.ReadPosition(AU_VIEWR);
	analview[JOY_ZOOM]=_Analogue.ReadPosition(AU_VIEWZ);
	for (int i=JOY_ZOOM;i>=JOY_HEAD;i--)
	{
		if (analview[i]==-0x8000) analview[i]=0;
//DEADCODE JIM 06/05/99 		else analview[i]<<=4;
	}
}

void ViewPoint::ClipToWorldLimits()
{
	if (World.X<25120262)		World.X=25120262;
	else if (World.X>94178669)	World.X=94178669;
	if (World.Z<5047962)		World.Z=5047962;
	else if (World.Z>129677255)	World.Z=129677255;
}
