//------------------------------------------------------------------------------
//Filename       persons2.h
//System         
//Author         Jim Taylor				 
//Date           Tue 5 Dec 1995
//Description    New 'persons' to process new battlefield format.
//------------------------------------------------------------------------------
#ifndef	PERSONS2_Included
#define	PERSONS2_Included

	#include	"FlyInit.h"
	#include	"enumbits.m"
	#include	"WorldInc.h"
	#include	"UniqueID.h"
	#include	"world.h"
#include	"text.h"
#include	"files.g"
//TempCode JIM 19Jul96 	#include	"text.g"
#define	DEFAULT_PERSONS2 0

typedef	class	ShapeNumField *ShapeNumFieldPtr;
struct EventVar;
#ifndef	MAKEBF_Included
enum	TokenCode	{};
#endif
//------------------------------------------------------------------------------
//DEADCODE JIM 17/03/99 typedef	struct	EventRec*	EventRecPtr;
//DEADCODE JIM 17/03/99 struct	EventSet
//DEADCODE JIM 17/03/99 {
//DEADCODE JIM 17/03/99 enum	fixedgvars	{GV_EVENT_START=-1,GV_EVENT_WINDOW=-2,GV_EVENT_EVENT=-3,GV_EVENT_NEST=-4};
//DEADCODE JIM 17/03/99 	int	Index;
//DEADCODE JIM 17/03/99 	union	{int	Value;EventRec* Nesting;};
//DEADCODE JIM 17/03/99 };
//DEADCODE JIM 17/03/99 struct	EventRec
//DEADCODE JIM 17/03/99 {
//DEADCODE JIM 17/03/99 	static	EventRec*	eventbase;
//DEADCODE JIM 17/03/99 	EventRec*	eventlink;
//DEADCODE JIM 17/03/99 	int			eventlistsize;
//DEADCODE JIM 17/03/99 	ItemBasePtr	attitem;
//DEADCODE JIM 17/03/99 	EventSet*	eventlist;
//DEADCODE JIM 17/03/99 	ULong		eventwstart;
//DEADCODE JIM 17/03/99 	ULong		eventwend;
//DEADCODE JIM 17/03/99 	EventRec(ItemBasePtr i,int count)
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 	 	eventlink=eventbase;
//DEADCODE JIM 17/03/99 		eventbase=this;
//DEADCODE JIM 17/03/99 		attitem=i;
//DEADCODE JIM 17/03/99 		eventlistsize=count;
//DEADCODE JIM 17/03/99 		eventlist=new EventSet [count];
//DEADCODE JIM 17/03/99 		eventwstart=0;
//DEADCODE JIM 17/03/99 		eventwend=0;
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 	~EventRec()
//DEADCODE JIM 17/03/99 	{	delete [] eventlist;			//delete list array
//DEADCODE JIM 17/03/99 		EventRec**	ev2=&eventbase;		//find this record in static list
//DEADCODE JIM 17/03/99 		while (*ev2!=this)	ev2=&ev2[0]->eventlink;
//DEADCODE JIM 17/03/99 		*ev2=eventlink;					//remove
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 };
//DEADCODE JIM 17/03/99 
//------------------------------------------------------------------------------
struct	PosCtrl
{
	COORDS3D	pos;
	UNIQUE_ID	refUID;
	ItemBasePtr		refptr;
	enum	AbsAxes	{ABS_REL=0,ABS_X=1,ABS_Y=2,ABS_Z=4,ABS_ABS=7}
				absaxes;
	PosCtrl()	{	pos.X=0;pos.Y=0;pos.Z=00;absaxes=ABS_REL;
					refUID.count=IllegalSepID;refptr=NULL;
				};
};
BITABLE(PosCtrl::AbsAxes);

//------------------------------------------------------------------------------
enum	UILogType
{
    ptrcopy         = 1,
    worldcopy,
    addworldcopy,
    anglesaccopy,
    anglesmobcopy,
    followaccopy,
    followmobcopy,
};

struct  NodeData
#ifdef  BFNUMBER_Included
{
    UILogType       request;

    union
    {
        ItemBasePtr *attackerptr;
        ItemBasePtr posptr;
    };
        EventVal    posexpr;
}
#endif
;


struct  UidNode
#ifdef  BFNUMBER_Included
    :public NodeData
{
    UniqueID    uidattack;
    UidNode     *less;
    UidNode     *more;
}
#endif
;

#include	"infoitem.h"
//------------------------------------------------------------------------------
//struct	RouteHdr
//{
//	RouteHdr	*next;
//	UniqueID	waypoint;
//	int			numusers;
//};

//------------------------------------------------------------------------------

	struct	EventLog:EventEntry
{
	EventLog*	next;
	UniqueID	targetuid;	//can distinguish friend/enemy a/c or ground

	Nationality	nat;
//	Had famekill and fameloss in old engine

	EventLog(EventLog* last)	{	next=last;stage=EMPTY;encsize=losses=hits=0;
									nat=NAT_AMBER;place=-1;homebase=UID_NULL;
									encounteredtype=PT_VEHICLES;escorttype=PT_BADMAX;	}
};


// Message enums moved to rchatter.h							//RJS 27Jan99

//DeadCode RJS 27Jan99 class	UserMsg:public ItemBase
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 public:
//DeadCode RJS 27Jan99 	enum		Reason
//DeadCode RJS 27Jan99 				{	NOMSG,
//DeadCode RJS 27Jan99 					COURSE,			//come to xxx
//DeadCode RJS 27Jan99 					PASSEDWP,		//passed WP: name/action
//DeadCode RJS 27Jan99 					ATTACK,			//ASSIGNEDAC
//DeadCode RJS 27Jan99 					ATTACKED,		//Being attacked by/bounced/taking hits
//DeadCode RJS 27Jan99 					CLOSE,			//Enemy a/c Close/Reconn/Spotter/Bomber/Balloon/ground
//DeadCode RJS 27Jan99 					TIME,			//acccel/takeover/paused/auto/regroup/regroup initiated
//DeadCode RJS 27Jan99 									//sensitivity
//DeadCode RJS 27Jan99 					SIGHTED,		//Unknown/Dogfight/Unfriend/Friendly/Vehicle/flak(e/f)
//DeadCode RJS 27Jan99 					GOHOME,			//Going Home/Killed/Assume Lead/Low/no fuel/ammo / too damaged
//DeadCode RJS 27Jan99 					FRIENDLY,		//Shooting a friendly
//DeadCode RJS 27Jan99 					OBJECTIVE,		//sighted/destroyed/balloonflamed
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 					COMMSKILL1,		//killed in comms 1 - 8
//DeadCode RJS 27Jan99 					COMMSKILL2,		//killed in comms 1 - 8
//DeadCode RJS 27Jan99 					COMMSKILL3,		//killed in comms 1 - 8
//DeadCode RJS 27Jan99 					COMMSKILL4,		//killed in comms 1 - 8
//DeadCode RJS 27Jan99 					COMMSKILL5,		//killed in comms 1 - 8
//DeadCode RJS 27Jan99 					COMMSKILL6,		//killed in comms 1 - 8
//DeadCode RJS 27Jan99 					COMMSKILL7,		//killed in comms 1 - 8
//DeadCode RJS 27Jan99 					COMMSKILL8,		//killed in comms 1 - 8
//DeadCode RJS 27Jan99 					COMMSKILLU,		//unfriendly
//DeadCode RJS 27Jan99 					COMMSKILLF,		//friendly
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 					LEFTGAME,		// comms player has left game //AMM 18Jun97
//DeadCode RJS 27Jan99 				}
//DeadCode RJS 27Jan99 				reason;
//DeadCode RJS 27Jan99 	ItemBasePtr	trgplace;	//for angle and range do intercept to trgplace
//DeadCode RJS 27Jan99 	TextSnip0	trgname;
//DeadCode RJS 27Jan99 	UserMsg& operator = (UserMsg& s)
//DeadCode RJS 27Jan99 		{	
//DeadCode RJS 27Jan99 			reason=s.reason;
//DeadCode RJS 27Jan99 			if (s.trgplace==&s)
//DeadCode RJS 27Jan99 			{
//DeadCode RJS 27Jan99 				trgplace=this;
//DeadCode RJS 27Jan99 				World=s.World;
//DeadCode RJS 27Jan99 			}
//DeadCode RJS 27Jan99 			else
//DeadCode RJS 27Jan99 				trgplace=s.trgplace;
//DeadCode RJS 27Jan99 			trgname=s.trgname;
//DeadCode RJS 27Jan99 			return	(*this);
//DeadCode RJS 27Jan99 		}
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 };
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 struct	UserMessages
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	enum	{MAX=5};
//DeadCode RJS 27Jan99 	UserMsg	line[MAX];
//DeadCode RJS 27Jan99 	Bool	newmessages;
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 };
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 struct	LastMsg
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	UserMsg::Reason		reason;
//DeadCode RJS 27Jan99 	TextSnip0	trgname;
//DeadCode RJS 27Jan99 };

//------------------------------------------------------------------------------



#if  defined(__WATCOMC__) || defined (__MSVC__)
extern	ULong&	GR_firstobject;
#endif
#define	firstobject ((UniqueID&)GR_firstobject)

//------------------------------------------------------------------------------
enum	PaintSchemes	{PS_PLAYER,PS_AUTOPLAYER,PS_PAINTSHOP,PS_RANDOM,PS_DEFINED};
enum	Cols	{COLS_MAP_SIZE=6,COLS_DAMAGE=6,COLS_BOMBS=8,COLS_ALL=10};

struct	ContourList;
struct	BfieldDesc;
//class	ViewPoint;
//#include	"viewsel.h"
class	ViewPoint;
class	Inst3d;
//------------------------------------------------------------------------------
class	Persons2
{
	friend	struct	PackageList;
	friend 	class	SupplyTree;
	friend	class	DPlay;
	friend  class	Replay;										//AMM 26May98
	friend	class	TSquadronDataForm;
	friend	class	TMissionEditor;
	friend	class	TWayPointForm;
	friend	class	TChooseBfForm;
	friend	class	DeadStream;
	friend	class	TCampaignEditDlg;
	friend	class	TFileLoadSave;
	friend	class	TBfieldForm;
public:
	int			selectedsquad;
	int			currbfindex;
	UniqueID	currsupergroup;
///	Bool	loadingmainworld;

	char usedevents[32];
	Bool	UsedFixedUID;
	enum	JustScanning
			{
				LOAD,
				SCANNAMES,
				SCANSQUADS,
				SELECTSQUAD,
				NAMESQUAD
			}
			justscanning;
enum	BattlefieldType	{	MAINWORLDBF = 0,
							BFMAXCOUNTER = 255,BFTYPE = 256,

							BFPHASES=	(int)BFMAXCOUNTER*(int)BFTYPE,
							PLAYERBF =	1*(int)BFTYPE,	//actual package battlefields
								PLAYERBF1,PLAYERBF2,PLAYERBF3,PLAYERBF4,PLAYERBF5,
							ROUTEBF =	2*(int)BFTYPE,	//targets for all packages
							PLAYROUTEBF = 3*(int)BFTYPE,	//extra detail for player's mission
					//additional elements on players route to target
							PREREDTAKEOFFAFBF,
							REDTAKEOFFAFBF,
							REDTAKEOFFREDAFBF,
							PREBLUETAKEOFFAFBF,
							TAKEOFFAFBF,	//player takeoff
							TAKEOFFBLUEAF,
							TAKEOFFHANDBLUEAF,
							TAKEOFF0AF,
							TAKEOFF1AF,
							TAKEOFF2AF,
							TAKEOFF3AF,
							TAKEOFF4AF,
							TARGETBF,		//player's target area
							SECTARGBF,		//neighboring target area
							ROUTE0BF,		//routes to target area
							ROUTE1BF,		//routes to target area
							ROUTE2BF,		
							ROUTE3BF,
							TOWN0BF,
							TOWN1BF,
							TOWN2BF,
							TOWN3BF,
							CHOKE0BF,		//routes to target area
							CHOKE1BF,		//routes to target area
							CHOKE2BF,		
							CHOKE3BF,
							DEFENDAF0BF,
							DEFENDAF1BF,	//neighboring airfields
							DEFENDAF2BF,
							DEFENDAF0RBF,
							DEFENDAF1RBF,	//neighboring airfields
							DEFENDAF2RBF,

							//put any more in before here!
							ENDPLAYTARGBF,

							GROUNDBF =  4*(int)BFTYPE,
							EASTGROUNDBF= (int)GROUNDBF+64,
							CENTGROUNDBF= (int)GROUNDBF+128,
							WESTGROUNDBF= (int)GROUNDBF+192,

							SCRAMBF =	5*(int)BFTYPE,
							DEFENDERBF =6*(int)BFTYPE,
							MIGSQ0BF,
							MIGSQ1BF,
							MIGSQTO0BF,
							MIGSQTO1BF,
							MIGSQTO2BF,
							MIGSQTO3BF,
							MIGSQTO4BF,
							MIGSQAF0BF,
							MIGSQAF1BF,
							MIGSQAF2BF,
							MIGSQAF3BF,
							MIGSQAF4BF,
							MIGSQAFTO0BF,
							MIGSQAFTO1BF,
							MIGSQAFTO2BF,
							MIGSQAFTO3BF,
							MIGSQAFTO4BF,
							MIGSQPREAIR	=(int)DEFENDERBF+16,
							MIGSQALLEY	=(int)DEFENDERBF+32,
							MIGSQPOSTAIR=(int)DEFENDERBF+48,
							MIGENDINFO=(int)DEFENDERBF+(int)BFMAXCOUNTER,
//							AAABF = 	4*(int)BFTYPE,
//							ENEMYACBF = 5*(int)BFTYPE,
//							CONVOYCOUNT=6*(int)BFTYPE,
//							AAACOUNT =	7*(int)BFTYPE,

							FINISHBF =	(int)BFMAXCOUNTER*(int)BFTYPE,
							};
public:
enum	{UIDTABLESIZE = 64, 	PITEMTABLESIZE = IllegalBAND,
			LOADEDBFS=64,LOADEDBFS2=84,LOADEDSGS=64};

	static AirStruc*	PlayerGhostAC;
	static AirStruc*	PlayerSeenAC;
static bool	pItemSet()	{return (pItem!=NULL);}

protected:
	ViewPoint* viewpoint;

static	UniqueIDBand	uidbandbase[UIDTABLESIZE];
static	UniqueID		uidbandmax[UIDTABLESIZE];
static	UniqueID		uidbandmin[UIDTABLESIZE];

static	FileNum			loadedBF[LOADEDBFS];
static	UniqueID		loadedSG[LOADEDSGS];

static	ItemBasePtr		*pItem;	//array now in struct world

//	ContourList	*contourlists;
//	RouteHdr	*routelist;

//DeadCode RDH 22Jul96 	UserMessages	usermessages;
	PaintSchemes	colourrule;
UidNode			*rootuidnode;
	WorldStuff*	myworld;
	ShapeNumFieldPtr	shapefield;
//	UniqueID	firstobject;
	void	AddSGToList(UniqueID newSGT);

void		processbfieldtoplevel(string& bfieldptr);
//virtual Bool		setposition(ItemBasePtr	tmpitem,EventVal& pos,Bool addwhenfilled)=0;
#ifdef	MAKEBF_Included
void		toplevel_string(string	&bfieldptr,TokenCode t);
Bool		toplevel_eventname(string &bfieldptr,info_event& E);
Bool		toplevel_agname(string &bfieldptr,info_airgrp& A);
#endif
void		toplevel_itemgrp(string	&bfieldptr);
void		toplevel_gndgrp(string	&bfieldptr);
void		toplevel_airgrp(string	&bfieldptr);
UniqueID	toplevel_route(string	&bfieldptr);
UniqueID	midlevel_waypoint(string	&bfieldptr,UniqueID);
void		toplevel_itemS(string	&bfieldptr,bool enabled);
void		toplevel_setval(string	&bfieldptr);
SLong		evaluateglobvar(string &bfieldptr,FormationIndex fi=FormationIndexMIN);
#ifdef BFNUMBER_Included
EventVal	constructvalue(string &bfieldptr,Bool isform=FALSE);
EventVal	constructposition(string &bfieldptr);
WorldExpr*	constructposition(string &bfieldptr,WorldExpr*	W);
EventVal	constructangles(string &bfieldptr);
Bool		lowlevel_squadron(	string& bfieldptr,info_airgrp&	I);
void		event_time(string& bfieldptr,EventVal&h,EventVal&m,EventVal&s);
void		event_event(string& bfieldptr,info_event& I);
EventVar	event_setval(string& bfieldptr);
void		midlevel_event(string& bfieldptr,info_event*& I);
void		midlevel_event(string& bfieldptr,info_event& I);
#endif

virtual	int			make_itemgroupcount(EventVal& E)=0;
virtual void		make_itemS(info_itemS& I,bool enabled)=0;
virtual void		make_airgrp(info_airgrp& I)=0;
virtual void		make_gndgrp(info_grndgrp& I)=0;
virtual UniqueID	make_waypoint(info_waypoint& I)=0;
virtual void		make_setval(EventVar& es)=0;
virtual void		make_string(string bfieldptr,int len,TokenCode t)=0;
virtual Bool		make_eventname(string bfieldptr,int len,info_event& E)=0;
virtual Bool		make_agname(string src,int len,info_airgrp& A)=0;
virtual void		make_events(info_event*& I,ItemBasePtr P)=0;
virtual void		used_globref(int index)=0;

void		getrelpos(string &bfieldptr,PosCtrl &position);
void		getposition(string &bfieldptr,PosCtrl &position);
void		pos_icpt(string&bfieldptr,ANGLES&tmpasp,ANGLES&tmpbrg,SLong&tmprange);
WayPoint*	getroute(string& bfieldptr);

void		throwtree(string& bfieldptr);
int			getloopcount(string & bfieldptr);
Bool	lowlevel_squadron(int snequ);

//virtual void		fixupengagements(AirStrucPtr	firstac)=0;
static void	FixupRouteOwner(UniqueID owner,UniqueID route);

Bool		setposition(ItemBasePtr	tmpitem,PosCtrl &position,Bool addwhenfilled);
//virtual COORDS3D*	setfolloweroffset(AirStrucPtr	newac)=0;			//RDH 27Feb96
//COORDS3D*	setfolloweroffset(FormationItemPtr	newac);			//RDH 27Feb96

void		setpointer(ItemBasePtr*,UniqueID);
//virtual void		AddToWorld(ItemPtr	tmpitem)=0;

UidNode**	searchtree(UniqueID srcuid) {return(searchtree(srcuid,&rootuidnode));}
UidNode**	searchtree(UniqueID srcuid,UidNode** nextnode);

//virtual void		adduidrequest(UidNode* newnode,UniqueID srcuid)=0;
virtual Bool		anyoutstanding()=0;

//virtual Bool		useUID(ItemBasePtr	selecteditem)=0;
//virtual Bool		recurseanyoutstanding(UidNode* node)=0;

//void		SetAngles (AirStrucPtr	newac);
//void		SetAngles (FormationItemPtr	newmob);

Inst3d*		inst3d;

public:
void			logUID(ItemBasePtr trgitemptr);
static void		tabulateUID(ItemBasePtr trgitemptr);
static UniqueID	findavailuid(UniqueIDBand	tmpband);
static UniqueID	assignuid(UniqueIDBand	tmpband);
static void		SetLoc(int	locnum,int value);


static int&			GetLoc(int	locnum);
protected:

//virtual FileNum		ActionEvent(EventRecPtr	evind,WorldStuff *worldptr,ItemBasePtr target)=0;

void		LoadSubPiece(WorldStuff *worldptr, string& bfieldptr,int bfindex,JustScanning scanning=LOAD);
void 		LoadSubPiece(WorldStuff *worldptr, FileNum filenumber,int bfindex,JustScanning scanning=LOAD);
private:
//void 		LoadSubPiece(WorldStuff *worldptr, FileNum filenumber,JustScanning scanning=LOAD);
void 		InitSetPiece();
//public:

virtual void		AddRoute(UniqueID)=0;
virtual void 		InitGamePiece()=0;
virtual void		InitSubPiece()=0;
virtual void		EndSubPiece()=0;
virtual void 		FinishSetPiece()=0;
public:
static void	InitTables();
protected:


virtual FileNum FindCommsNextBf (Persons2::BattlefieldType& bfctrl)=0;		//ARM 27Sep96
FileNum	FindNextBf (BattlefieldType &nextbftype);
FileNum	LaunchMigPatrol(SquadSelect squad,int prefsize,UniqueID takeoff,int migdaytype,int migcaptime);
	UniqueID	bluenemigcap;
	UniqueID	blueswmigcap;

Bool	LaunchConvoy(FileNum,SWord);					//RDH 30Sep96
void	SetSecondWP (WayPointPtr	tmpitem);

public:

static	bool	DeleteBFItems(FileNum bfieldtoremove);
static	bool	BFLoaded(FileNum f);
static	bool	GetSpareBFNumber(int& number);
static	int		DeleteOldestBF();

CON	Persons2(WorldStuff* world,ViewPoint* vp);

//virtual	void	PreScanBF(FileNum f)=0;
void	TankEndMission();								//RDH 30Sep96
void	LaunchTankConvoy ();							//RDH 13Oct96
Bool	LaunchTruckConvoy ();							//RDH 16Dec96
void	LaunchTruckConvoyTest ();						//RDH 16Dec96
//DeadRJS27Jan99	UserMessages	usermessages;
static 	BfieldDesc*		bfdesc;

static ItemBasePtr	ConvertPtrUID(UniqueID tmpUID);					//PD 01Apr96
static	ItemBasePtr		SlowConvertPtrUID(UniqueID tmpUID);

static void		delUID(UniqueID u);
static 	UniqueIDBand	getbandfromUID(UniqueID	tmpUID);			//RDH 08Aug96
static 	UniqueIDBand	getbandMAXfromUID(UniqueID	tmpUID);			//RDH 08Aug96
static	int				getbandnumfromUID(UniqueID	tmpUID);
//virtual Bool		PossibleEvent(WorldStuff *worldptr,ItemBasePtr target,ItemBasePtr actor)=0;
void 		LoadSetPiece(WorldStuff *worldptr, FileNum filenumber);
void 		LoadSetPiece(WorldStuff *worldptr);

//virtual void		FreeRoutes()=0;
//virtual void		FreeEvents()=0;
static EventLogPtr	eventloglist,TruckLog,TargLog,PlayerLog;
//DeadCode RJS 27Jan99 void	AddMessageIfPlayerSq(AirStrucPtr eye,UserMsg::Reason r,TextSnip0 t,ItemBasePtr trg);
//DeadCode RJS 27Jan99 void	AddMessageIfPlayer(ItemBasePtr eye,UserMsg::Reason,TextSnip0,ItemBasePtr trg);
//DeadCode RJS 27Jan99 void	AddMessage(UserMsg::Reason,TextSnip0,ItemBasePtr trg);
//DeadCode RJS 27Jan99 void	AddMessage(UserMsg::Reason,TextSnip0,Coords3D& trg);
//DeadCode RJS 27Jan99 void	ClrMessage(UserMsg::Reason);
static void	UpdateLog(AirStrucPtr	eventlogowner,int	credits,EventLog::Stage stage);
static void	UpdateLog(MobileItemPtr	eventlogowner,int	credits,EventLog::Stage stage);
static void	UpdateLog(EventLogPtr	eventlog,int	credits,EventLog::Stage stage,ItemBasePtr place=NULL);
static void	UpdatePlayerLog(AirStrucPtr	eventitem,EventLog::Stage stage);
static void	UpdateLog(ItemPtr	eventlogowner,int	credits,EventLog::Stage stage);



//TEMPCODE JIM 25/03/99 TextPage	permtextpage;

FileNum		lastbfloaded;
ItemBasePtr	lasttarg,lastact;

ITEM_STATUS	ItemStatus(UniqueID uid,ITEM_STATUS s);
ITEM_STATUS	ItemStatus(UniqueID uid);
ITEM_STATUS	ConvoyStatus(UniqueID uid,UniqueID& nextwp,UniqueID& nextwptarg,SLong& livelength);


void	SaveBF(FileNum dirnum,char* fname,char* name,char* comment,bool newfile);

#ifdef BFNUMBER_Included
void	SaveAirGrp(FILE* f,ItemBasePtr B,char* fname,int tabs);
void	SaveGrndGrp(FILE* f,ItemBasePtr B,char* fname,int tabs);
void	SaveItem(FILE* f,ItemBasePtr B,char* fname,int tabs);
void	SaveNumber(FILE* f,EventVal& V,char* fname,int tabs,EnumListNames e=ENUM_RealInt);
void	SavePosition(FILE* f,EventVal& V,char* fname,int tabs,char* namedpos=NULL);
void	SaveRoute(FILE* f,UniqueID U,char* fname,int tabs);
void	PreSaveRoute(FILE* f,UniqueID U,char* fname,int tabs);
Bool	SaveEvents(FILE* f,info_event* E,char* fname,int tabs);
#endif

void	ClearGlobrefPackVars();		//(done)call this BEFORE transmitting globrefs
void	ResetGlobrefPackVars();		//(done)call this AFTER transmitting globrefs
void	ClearGlobrefStaticVars();	//(done)call this in initsetpiece
void	ClearGlobrefGlobalVars();	//(not done)call this somewhere safely inside debrief

Bool	SENT_REQ;
static	UniqueID	GetNthSGTMember(UniqueID SGT,UniqueIDBand base,int index);
static	int			GetNOfSGTMember(UniqueID SGT,UniqueIDBand uidband,UniqueID member);

int	Pack_PlayerSquad,Pack_PlayerPos;
//void	SetReplayPack();
};

struct PilotType;
class	Persons3:public	Persons2
{
	friend class	ArtInt;
enum	TakeOffState
{TOS_SIMPLE,TOS_SECRET,TOS_MIGTAKEOFF,TOS_INAIR,TOS_TAKENOFF,TOS_TAKINGOFF,TOS_RUNWAY,TOS_NEXTFLIGHTS,TOS_TAXIING,TOS_HOLDING};
	static	AirStrucPtr	migsq[2];

	int	gotgrpflags;int gotgrpnum;
	WPNames	nextwpname;
	int		nextwpnum;
	enum	{MAXCALLNAMES=40};		//1-32 inclusive...
	char	callsignnamecount[MAXCALLNAMES];
void	AddPreLoadFXShapes();									//RJS 02Apr99
void	FixUpWaypointsToGroup(int grpnum,UniqueID route,UniqueID leader,int numinflight);
//static void	ColourRuleAllRandom(AirStrucPtr	newac,FormationIndex formtype,UByte*);
void	ColourRulePlayerSquadron(AirStrucPtr	newac,FormationIndex formtype,UByte*,PilotType* pilot);
//static void	ColourRulePlayerAuto(AirStrucPtr	newac,FormationIndex formtype,UByte*);
//static void	ColourRulePaintShop(AirStrucPtr	newac,FormationIndex formtype,UByte*);
//static void	ColourRuleDefined(AirStrucPtr	newac,FormationIndex formtype,UByte*);
//static void	(*(Colour_Rule_List[]))(AirStrucPtr,FormationIndex,UByte*);
FileNum FindCommsNextBf (Persons2::BattlefieldType& bfctrl);		//ARM 27Sep96
void		SetAngles (AirStrucPtr	newac);
void		SetAngles (FormationItemPtr	newmob);

void		logworldcopy(ItemBasePtr,UniqueID,EventVal& pos,Bool addwhenfilled);
void		logworldcopy(ItemBasePtr,UniqueID,Bool addwhenfilled);
void		logsetangles(AirStrucPtr targitem,UniqueID srcUID);
void		logsetangles(FormationItemPtr targitem,UniqueID srcUID,UILogType=anglesmobcopy);
void		logpointercopy(ItemBasePtr*trgitemptr,UniqueID srcuid);

void		setfollowerposition(AirStrucPtr it);
void		setfollowerposition(FormationItemPtr it);
void		adduidrequest(ItemBasePtr trgitemptr,UniqueID srcuid,UILogType request);
void		adduidrequest(ItemBasePtr trgitemptr,UniqueID srcuid,EventVal& pos,UILogType request);
void		adduidrequest(ItemBasePtr *trgitemptr,UniqueID srcuid);
//Bool		PossibleEvent(ItemBasePtr target,ItemBasePtr actor)
//			{return PossibleEvent(mobileitem::currworld,target,actor);}
void		make_airgrp(info_airgrp& I);
void		fixupengagements(AirStrucPtr	firstac);
UniqueID	make_waypoint(info_waypoint& I);
int			make_itemgroupcount(EventVal& E);
void		make_itemS(info_itemS& I,bool enabled);
void		make_gndgrp(info_grndgrp& I);
void		make_events(info_event*& I,ItemBasePtr P);
void		make_setval(EventVar& es);
void		make_string(string bfieldptr,int len,TokenCode t);
Bool		make_eventname(string bfieldptr,int len,info_event& E);
Bool		make_agname(string src,int len,info_airgrp& A);
void		used_globref(int index);
COORDS3D*	setfolloweroffset(AirStrucPtr	newac);			//RDH 27Feb96
COORDS3D*	setfolloweroffset(FormationItemPtr	newac);			//RDH 27Feb96
Bool		setposition(ItemBasePtr	tmpitem,EventVal& pos,Bool addwhenfilled);
void		setpointer(ItemBasePtr*,UniqueID);
void		logUID(ItemBasePtr trgitemptr);
Bool		useUID(ItemBasePtr	selecteditem);
Bool		useUID(ItemBasePtr	selecteditem,UniqueID theuid);
Bool		recurseanyoutstanding(UidNode* node);
Bool		anyoutstanding();
void 		InitGamePiece();
void		InitSubPiece();
void		EndSubPiece();
void 		FinishSetPiece();
void		AddToWorld(ItemPtr	tmpitem);
//Bool		PossibleEvent(WorldStuff *worldptr,ItemBasePtr target,ItemBasePtr actor);
//FileNum		ActionEvent(EventRecPtr	evind,WorldStuff *worldptr,ItemBasePtr target);
void		AddRoute(UniqueID);
void	PreScanBF(FileNum f);
void		adduidrequest(UidNode* newnode,UniqueID srcuid);
//nonvirtual functions... only a couple!
static PlaneTypeSelect	squad2type[];
public:
static PlaneTypeSelect Squad2Type(int);
private:
	enum	GearState	{GS_INAIR,GS_GEAR,GS_PARKED};
GearState	setpositionMIG(AirStrucPtr currac,EventVal* pos,TakeOffState	takeoffstate,int takeofftimesecs);						//RDH 17Jun96

//void		adduidrequest(ItemBasePtr trgitemptr,UniqueID srcuid,EventVal& pos,UILogType request)
//{Persons2::adduidrequest(trgitemptr,srcuid,pos,request);}
void		fixupengagements(AirStrucPtr	eyeF,AirStrucPtr trg);
public:

CON		Persons3(WorldStuff* world,ViewPoint* vp,Inst3d* inst);//:Persons2(world,vp)	{gotgrpnum=1;inst3d=inst;}//JIM 19Feb99
void	FreeRoutes();
void	FreeEvents();
void	ProcessLogList();
UniqueID	prevflightleader;
int		numprevflights;
};

class	Persons4:public	Persons2
{
FileNum FindCommsNextBf (Persons2::BattlefieldType& bfctrl);		//ARM 27Sep96
void		SquadAddDesc(string bfieldptr,int len,TokenCode t);
void		make_airgrp(info_airgrp& I);
//void		fixupengagements(AirStrucPtr	firstac);
UniqueID	make_waypoint(info_waypoint& I);

int			make_itemgroupcount(EventVal& E);
void		make_itemS(info_itemS& I,bool enabled);
void		make_gndgrp(info_grndgrp& I);
void		make_events(info_event*& I,ItemBasePtr P);
void		make_setval(EventVar& es);
void		make_string(string bfieldptr,int len,TokenCode t);
Bool		make_eventname(string bfieldptr,int len,info_event& E);
Bool		make_agname(string src,int len,info_airgrp& A);
void		used_globref(int index);
//COORDS3D*	::setfolloweroffset(AirStrucPtr	newac);			//RDH 27Feb96
//Bool		::setposition(ItemBasePtr	tmpitem,EventVal& pos,Bool addwhenfilled);
//void		::setpointer(ItemBasePtr*,UniqueID);
void		logUID(ItemBasePtr trgitemptr);
//Bool		useUID(ItemBasePtr	selecteditem);
Bool		recurseanyoutstanding(UidNode* node);
Bool		anyoutstanding();
void 		InitGamePiece();
void		InitSubPiece();
void		EndSubPiece();
void 		FinishSetPiece();
//void		::AddToWorld(ItemPtr	tmpitem);
//Bool		::PossibleEvent(WorldStuff *worldptr,ItemBasePtr target,ItemBasePtr actor);
//FileNum		::ActionEvent(EventRecPtr	evind,WorldStuff *worldptr,ItemBasePtr target);
void		AddRoute(UniqueID);
//void	::PreScanBF(FileNum f);
//void		::adduidrequest(UidNode* newnode,UniqueID srcuid);
//nonvbirtual ::functions... only a couple!
//void		adduidrequest(ItemBasePtr trgitemptr,UniqueID srcuid,EventVal& pos,UILogType request)
//{Persons2::adduidrequest(trgitemptr,srcuid,pos,request);}

//void		fixupengagements(AirStrucPtr	eyeF,AirStrucPtr trg);
public:
CON		Persons4():Persons2(NULL,NULL)	{}
static void	StartUpMapWorld();
static void	ShutDownMapWorld();
static void InitViewFromMap(UniqueID);
static void ShutDownViewFromMap();
//void	FreeRoutes();
//void	FreeEvents();
	union
	{
		info_event*	keptevent;
		char*		keptstr;
	};

};

//extern	Persons2	Persons_2;
//------------------------------------------------------------------------------

#endif
