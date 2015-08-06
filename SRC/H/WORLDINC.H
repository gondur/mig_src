//------------------------------------------------------------------------------
//Filename       worldinc.h
//System         
//Author         Paul.   
//Date           Thu 19 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	WORLDINC_Included
#define	WORLDINC_Included
#include	"movement.h"										//RDH 19Feb96
#include	"myangles.h"
#include	"shapenum.g"										//JIM 31Oct95
#include	"uniqueid.h"										//JIM 31Oct95
#include	"flyinit.h"
#include	"bitcount.h"
#include	"modvec.h"
#include	"animptr.h"
#define	DEFAULT_WORLDINC 0

typedef class Model* PMODEL;									//ARM 07Mar97
typedef class AcmModel* PACMMODEL;								//ARM 14May97
typedef class _instruments *PINSTRUMENTS;						//ARM 27Aug97

#ifndef	NDEBUG
void	DbgMemTest2(void*);
#endif

class	MinAnimData;
 
typedef	char	(MinAnimData::*Animfieldref);
typedef	char	(MinAnimData::*AFR);

//FileItem - part of worldload - discarded
//

//DeadCode PD 12Oct95 typedef	UWord	shapeindx;

//DeadCode RJS 21Apr99 typedef	void	*animptr;
//Protected animdata stuff....
class	GrpMinAnimData;
class	SunAnimData;
class	ExplodeAnimData;
class	FireAnimData;
class	BalloonAnimData;
class	BarageAnimData;
class	TroopAnimData;
class	TrainAnimData;
class	BlokesAnimData;					
class	WeapAnimData;
class	MoveGunAnimData;
class	TwoGunAnimData;
class	AircraftAnimData;
class	PolyPitAnimData;
class	LauncherAnimData;
class	WindsocAnimData;
class	CloneAnimData;
class	FlareAnimData;
class	ParachuteAnimData;
class	ThugAnimData;
class	MissileAnimData;
class	DebrisAnimData;
class	SmokeTrailAnimData;
struct	Coords3DList;
//DeadCode AMM 30Jul99 class	animptr
//DeadCode AMM 30Jul99 {
//DeadCode AMM 30Jul99 	//This anim class has been re-written by
//DeadCode AMM 30Jul99 	//RJS .... 30 June 1999
//DeadCode AMM 30Jul99 
//DeadCode AMM 30Jul99 	void*	ptr;
//DeadCode AMM 30Jul99 #ifndef	NDEBUG
//DeadCode AMM 30Jul99 	ULong	size;		//bit 9 = minanim >... (23 anim flags)
//DeadCode AMM 30Jul99 						//1st 9 bits = user anim size
//DeadCode AMM 30Jul99 						//or size of group...
//DeadCode AMM 30Jul99 #endif
//DeadCode AMM 30Jul99 public:
//DeadCode AMM 30Jul99 
//DeadCode AMM 30Jul99 	animptr()	
//DeadCode AMM 30Jul99 	{
//DeadCode AMM 30Jul99 		ptr=NULL;
//DeadCode AMM 30Jul99 #ifndef	NDEBUG
//DeadCode AMM 30Jul99 		size = 0;
//DeadCode AMM 30Jul99 #endif
//DeadCode AMM 30Jul99 	}
//DeadCode AMM 30Jul99 
//DeadCode AMM 30Jul99 	void	operator = (UByteP a){ptr = a;};
//DeadCode AMM 30Jul99 	UByte&	operator[] (int a);
//DeadCode AMM 30Jul99 	UByte&	operator[] (SWord a);
//DeadCode AMM 30Jul99 	UByte&	operator[] (UWord a);
//DeadCode AMM 30Jul99 	UByte&	operator[] (UByte a);
//DeadCode AMM 30Jul99 	Bool	operator == (void* a){if (ptr==a) return TRUE; return FALSE;}
//DeadCode AMM 30Jul99 	int		operator - (animptr& a);
//DeadCode AMM 30Jul99 	Bool	operator != (void* a){if (ptr!=a) return TRUE; return FALSE;}
//DeadCode AMM 30Jul99 	void	operator += (int a);
//DeadCode AMM 30Jul99 	void	operator ++ ();
//DeadCode AMM 30Jul99 	UByteP	operator & ();
//DeadCode AMM 30Jul99 	ULong	Offset(void*	a);
//DeadCode AMM 30Jul99 
//DeadCode AMM 30Jul99 #ifndef	NDEBUG
//DeadCode AMM 30Jul99 void	MemTest();
//DeadCode AMM 30Jul99 void	Delete()	{delete [](char*)ptr; ptr=NULL; size = 0;}
//DeadCode AMM 30Jul99 void	operator = (animptr& a){ptr = a.ptr; size = a.size;};
//DeadCode AMM 30Jul99 void	operator = (int a){size = ULong(a);if (a==0)ptr = NULL;};
//DeadCode AMM 30Jul99 
//DeadCode AMM 30Jul99 operator MinAnimData*();
//DeadCode AMM 30Jul99 operator GrpMinAnimData*();
//DeadCode AMM 30Jul99 operator SunAnimData*();
//DeadCode AMM 30Jul99 operator ExplodeAnimData*();
//DeadCode AMM 30Jul99 operator FireAnimData*();
//DeadCode AMM 30Jul99 operator BalloonAnimData*();
//DeadCode AMM 30Jul99 operator BarageAnimData*();
//DeadCode AMM 30Jul99 operator TroopAnimData*();
//DeadCode AMM 30Jul99 operator TrainAnimData*();
//DeadCode AMM 30Jul99 operator BlokesAnimData*();		
//DeadCode AMM 30Jul99 operator WeapAnimData*();
//DeadCode AMM 30Jul99 operator MoveGunAnimData*();
//DeadCode AMM 30Jul99 operator TwoGunAnimData*();
//DeadCode AMM 30Jul99 operator AircraftAnimData*();
//DeadCode AMM 30Jul99 operator PolyPitAnimData*();
//DeadCode AMM 30Jul99 operator LauncherAnimData*();
//DeadCode AMM 30Jul99 operator WindsocAnimData*();
//DeadCode AMM 30Jul99 operator CloneAnimData*();
//DeadCode AMM 30Jul99 operator FlareAnimData*();
//DeadCode AMM 30Jul99 operator ParachuteAnimData*();
//DeadCode AMM 30Jul99 operator ThugAnimData*();
//DeadCode AMM 30Jul99 operator MissileAnimData*();
//DeadCode AMM 30Jul99 operator DebrisAnimData*();
//DeadCode AMM 30Jul99 operator SmokeTrailAnimData*();
//DeadCode AMM 30Jul99 operator Coords3DList*();
//DeadCode AMM 30Jul99 #else
//DeadCode AMM 30Jul99 void	Delete()	{delete [](char*)ptr; ptr=NULL;}
//DeadCode AMM 30Jul99 void	operator = (animptr& a){ptr = a.ptr;};
//DeadCode AMM 30Jul99 void	operator = (int a){if (a==0)ptr = NULL;};
//DeadCode AMM 30Jul99 
//DeadCode AMM 30Jul99 operator MinAnimData*(){return (MinAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator GrpMinAnimData*(){return (GrpMinAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator SunAnimData*(){return (SunAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator ExplodeAnimData*(){return (ExplodeAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator FireAnimData*(){return (FireAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator BalloonAnimData*(){return (BalloonAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator BarageAnimData*(){return (BarageAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator TroopAnimData*(){return (TroopAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator TrainAnimData*(){return (TrainAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator BlokesAnimData*(){return (BlokesAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator WeapAnimData*(){return (WeapAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator MoveGunAnimData*(){return (MoveGunAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator TwoGunAnimData*(){return (TwoGunAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator AircraftAnimData*(){return (AircraftAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator PolyPitAnimData*(){return (PolyPitAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator LauncherAnimData*(){return (LauncherAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator WindsocAnimData*(){return (WindsocAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator CloneAnimData*(){return (CloneAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator FlareAnimData*(){return (FlareAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator ParachuteAnimData*(){return (ParachuteAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator ThugAnimData*(){return (ThugAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator MissileAnimData*(){return (MissileAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator DebrisAnimData*(){return (DebrisAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator SmokeTrailAnimData*(){return (SmokeTrailAnimData*)ptr;}
//DeadCode AMM 30Jul99 operator Coords3DList*(){return (Coords3DList*)ptr;}
//DeadCode AMM 30Jul99 #endif
//DeadCode AMM 30Jul99 
//DeadCode AMM 30Jul99 
//DeadCode AMM 30Jul99 };


typedef	struct WayPoint	*WayPointPtr;
typedef	FormationTypeIndex	FORMATIONDESC;
typedef	void	*msgptr;
struct	WEAPCLASS
{
	UWord	group,entry;
};
typedef	void	*CALLPTR;
typedef	void	*LIGHTS;
//DeadCode PD 20Feb96 typedef	void	*VIEWDEF;
typedef	void	*animrtnref;
typedef	void	*shpintrpptr;
typedef	void	*weapptr;
//DeadCode RJS 10Feb97 typedef	void	*detectrtnref;
//DeadCode RDH 19Feb96 typedef	ULong	ActionRtnRef;

struct	PlaneType;
typedef	PlaneType	*ClassPtr;

//DeadCode RDH 28Feb96 enum	DUTYDESC	{dummy_duty = 0,DUTY_ALIGN=255};
//moved to h\movement.h											//RDH 19Feb96
//DeadCode RDH 19Feb96 enum	MANOEUVRE	{MANOEUVRE_SELECT=0,MANOEUVRE_IMMELMAN,MANOEUVRE_LOOP,MANOEUVRE_BARREL,MANOEUVRE_STALL};
//
//Blues are aggressive friendly forces (do the killing)
//Reds are aggressive unfriendly forces (get killed)
//green are non-aggressive neutral forces (bugger 'em)
//amber are aggressive neutral forces (bugger me)
//DeadCode RDH 26Oct95 enum	CONTROLMODE	{AUTO = 0,MANUAL};
//MovedTo3ddefs.h DAW 28Nov95 enum	Obj3DType	{STATIC = 0, MOBILE};
//DeadCode PD 07Mar96 enum	SHAPETYPE	{DUMMY_TYPE = 0};
//TempCode DAW 28Nov95 typedef	Obj3DType	OBJ3DTYPE;


#define	TDXBASE	0
#define	TDZBASE	0

#define MAXNUMBEROFTRANSIENTS 64								//MGA 27Feb96

struct	UNIQUE_ID
			{
				FIRSTFIELD (UWord,UniqueID,count,13)
				BITFIELD(Bool,changed,14,14)
////				LASTFIELD(Bool,sector,15,15)
//DeadCode AMM 10Jun98 				LASTFIELD(Bool,deaded,	15,15)		//RJS 27Feb98

				LASTFIELD(Bool,commsmove,	15,15)				//AMM 10Jun98

//				UniqueID	count	:14;
//				UWord		changed	:1,
//							sector	:1;
#ifdef	TRACKBADASSIGNMENTS	
			operator=(UNIQUE_ID&);
#endif
			};

//struct	BRIEF_ID
//			{
//			 	short	int	count:12,
//							spare:4;
//			};

enum	ITEM_SIZE	{	ItemBaseSize,WayPointSize,	//this layout is intended
						ItemSize,					//to show the hierachy of
						HdgSize,					//ItemBase derived types.
						HPSize,
						RotatedSize,
						MovingSize,
						MobileSize,TransientSize,VIEWPOINTSIZE2,
						FormationSize,
						ShipSize,
						AirStrucSize,

						ITEMBASESIZE=0,WAYPOINTSIZE,//this layout is intended
						ITEMSIZE,					//to show the hierachy of
						HDGSIZE,					//ItemBase derived types.
						HPSIZE,
						ROTATEDSIZE,
						MOVINGSIZE,
						MOBILESIZE,TRANSIENTSIZE,VIEWPOINTSIZE,
						FORMATIONSIZE,
						SHIPSIZE,
						AIRSTRUCSIZE,


						ITEM_SIZE_ALIGN=255
						};

struct	ITEM_STATUS
{
	FIRSTFIELD	(UWord,	Bool,BlueLaunch,0)
		BITFIELD(Bool,ManLaunch,1,1)
		BITFIELD(Bool,Drawn,2,2)
		BITFIELD(ITEM_SIZE,size,3,7)
		BITFIELD(UByte,deadtime,8,12)
		BITFIELD(UByte,deadscale,13,14)
		LASTFIELD(Bool,deaded,15,15)	 						//AMM 10Jun98
//DeadCode AMM 10Jun98 		SPAREFIELD(15,15)

//	Bool		BlueLaunch:	1,
//				ManLaunch:	1,
//				Drawn:		1;
//	ITEM_SIZE	size:		5;
//	UByte		deadtime:	5,	//max=32
//				deadscale:	2;	//¬hours/2hours/days/weeks
//	ITEM_STATUS() {};

	ITEM_STATUS()
	{
#ifdef	__MSVC__
		overview_BlueLaunch.value=0;
#endif
	}
	ITEM_STATUS(Bool bl,Bool ml=FALSE,Bool d=FALSE,ITEM_SIZE is=ITEMBASESIZE,UByte dt=0,UByte ds=0)
	{
		BlueLaunch=bl;
		ManLaunch=ml;
		Drawn=d;
		size=is;
		deadtime=dt;
		deadscale=ds;
	}
#ifdef	TRACKBADASSIGNMENTS	
			operator=(ITEM_STATUS&);
#endif
};

inline ITEM_STATUS SetStatus(UByte dt,UByte ds) {ITEM_STATUS rv(TRUE,TRUE,TRUE,ITEMBASESIZE,dt,ds);return rv;};

			
//DeadCode JIM 06Nov96 typedef	struct	COORDS3D	{	SLong	X,Y,Z;	} Coords3D;
struct	EventLog;
typedef	EventLog	*EventLogPtr;

typedef Bool	TellLeader;										//DAW 30Jun96
enum	NextLeadAct		{NL_OnCourse,NL_CircleFlights,NL_CircleSingles,NL_Flights,NL_DoubleFlighs,NL_PrevRipple,NL_PrevDouble,NL_align=255};
enum	NextFollAct		{NF_PersonalThreat,NF_CircleSingle,NF_Single,NF_Double,NF_ReDouble,NF_align=255};
class	ItemBase		;
class	item			;
class	hdgitem			;
class	hpitem			;
class	rotitem			;
class	MovingItem		;
class	mobileitem		;
class	TransientItem	;
class	formationitem	;
class	shipitem		;
class	AirStruc		;
struct	info_itemS;
struct	info_base;
struct	info_waypoint;
struct	info_grndgrp;
struct	info_airgrp;
//class	;
//class	;


typedef ItemBase		*ItemBasePtr;							//JIM 14Feb96
typedef item			Item,*ItemPtr,*itemptr;
typedef hdgitem			*HdgItemPtr;
typedef hpitem			*HpItemPtr;
typedef rotitem			*RotItemPtr;
typedef MovingItem		*MovingItemPtr;
typedef mobileitem		MobileItem,*MobileItemPtr;
typedef TransientItem	*TransientItemPtr;
typedef formationitem	FormationItem,*FormationItemPtr;
typedef shipitem		*ShipItemPtr;
typedef	AirStruc		*AirStrucPtr;

class	ItemBase//:public	TextBlockKnown
{
protected:
	ItemBase()	{Status.size=ItemBaseSize;(UWord&)uniqueID=(UWord&)Status=0;}//JIM 12Sep96
public:
	~ItemBase();
static	ULong	desposrange;
static	COORDS3D despos;										//RDH 27Feb96

	void	operator	delete(void*);
	UNIQUE_ID	uniqueID;	//o00s02//access with myitem->uniqueID.count
	ITEM_STATUS	Status;		//o02s02//access with myitem->Status.size
	COORDS3D	World;		//o04s0C//access with myitem->World.X
// Fix against "condition is always true"
#ifdef __WATCOMC__
#pragma warning	690	6
#endif
#ifdef	worldincassert
	#undef	worldincassert
#endif

#ifdef	assert
#ifndef	NDEBUG
#ifdef __MSVC__
	#define	worldincassert
#endif
#endif
#endif

 	operator	ItemBase* ()
		{return(ItemBase*) (this);}

#ifndef	worldincassert
 	operator	item* ()	  	{
	 			return(item*) (this);	}
 	operator	WayPoint* ()  	{
	 			return(WayPoint*) (this);	}
	 
 	operator	hdgitem* ()  	{
	 			return(hdgitem*) (this);	}
	 
 	operator	hpitem* ()  	{
	 			return(hpitem*) (this);	}
	 
 	operator	rotitem* ()  	{
	 			return(rotitem*) (this);	}
	 
 	operator	mobileitem* ()  	{
	 			return(mobileitem*) (this);	}
	 
 	operator	MovingItem* ()  	{
	 			return(MovingItem*) (this);	}
	 
 	operator	TransientItem* ()  	{
	 			return(TransientItem*) (this);	}
	 
 	operator	FormationItemPtr ()  	{
	 			return(FormationItemPtr) (this);	}
	 
 	operator	ShipItemPtr ()  	{
	 			return(ShipItemPtr) (this);	}
	 
 	operator	AirStrucPtr ()  	{
	 			return(AirStrucPtr) (this);	}
 
	operator    info_itemS*	()		{
				return	(info_itemS*)(this);	}

	operator    info_base*	()		{
				return	(info_base*)(this);	}

	operator    info_waypoint*	()		{
				return	(info_waypoint*)(this);	}

	operator    info_grndgrp*	()		{
				return	(info_grndgrp*)(this);	}

	operator    info_airgrp*	()		{
				return	(info_airgrp*)(this);	}
#else
 	operator	item* ()	  	{
			 if (this)
	 		 assert (Status.size>=ItemSize);
	 			return(item*) (this);	}
 	operator	WayPoint* ()  	{
			 if (this)
	 		 assert ( Status.size==WayPointSize);
	 			return(WayPoint*) (this);	}
	 
 	operator	hdgitem* ()  	{
			 if (this)
	 		 assert ( Status.size>=HdgSize);
	 			return(hdgitem*) (this);	}
	 
 	operator	hpitem* ()  	{
			 if (this)
	 		 assert ( Status.size>=HPSize);
	 			return(hpitem*) (this);	}
	 
 	operator	rotitem* ()  	{
			 if (this)
	 		 assert ( Status.size>=RotatedSize);
	 			return(rotitem*) (this);	}
	 
 	operator	MovingItem* ()  	{
			 if (this)
	 		 assert ( Status.size>=MovingSize);
	 			return(MovingItem*) (this);	}
	 
 	operator	mobileitem* ()  	{
			 if (this)
	 		 assert ( Status.size>=MobileSize);
	 			return(mobileitem*) (this);	}
	 
 	operator	TransientItem* ()  	{
			 if (this)
	 		 assert ( Status.size>=TransientSize);
	 			return(TransientItem*) (this);	}
	 
 	operator	FormationItemPtr ()  	{
			 if (this)
	 		 assert ( Status.size>=FormationSize);
	 			return(FormationItemPtr) (this);	}
	 
 	operator	ShipItemPtr ()  	{
			 if (this)
	 		 assert ( Status.size>=ShipSize);
	 			return(ShipItemPtr) (this);	}
	 
 	operator	AirStrucPtr ()  	{
			 if (this)
	 		 assert ( Status.size>=AirStrucSize);
	 			return(AirStrucPtr) (this);	}

	operator    info_itemS*	()		{
				return	(info_itemS*)(this);	}

	operator    info_base*	()		{
				return	(info_base*)(this);	}

	operator    info_waypoint*	()		{
				return	(info_waypoint*)(this);	}

	operator    info_grndgrp*	()		{
				return	(info_grndgrp*)(this);	}

	operator    info_airgrp*	()		{
				return	(info_airgrp*)(this);	}
#endif
#ifdef	worldincassert
	#undef	worldincassert
#endif
// #ifdef __WATCOMC__
// #pragma warning	690	2
// #endif
};

inline	COORDS3D&	operator += (COORDS3D& trg,COORDS3D& src)	{trg.X+=src.X;trg.Y+=src.Y;trg.Z+=src.Z;return(trg);}
inline	COORDS3D&	operator -= (COORDS3D& trg,COORDS3D& src)	{trg.X-=src.X;trg.Y-=src.Y;trg.Z-=src.Z;return(trg);}
inline	COORDS3D&	operator += (COORDS3D& trg,ItemBase* src)	{trg.X+=src->World.X;trg.Y+=src->World.Y;trg.Z+=src->World.Z;return(trg);}
inline	COORDS3D&	operator -= (COORDS3D& trg,ItemBase* src)	{trg.X-=src->World.X;trg.Y-=src->World.Y;trg.Z-=src->World.Z;return(trg);}


//Nasty cludge number 67: This field contains -1 for map items...
struct WPOverlayItem:public ItemBase			//o10s04
{	WayPointPtr	next;	WPOverlayItem()	{next=NULL;}	};
struct ItemOverlayWP:public ItemBase
{	ItemPtr	Next;		ItemOverlayWP()	{Next=NULL;}	};
struct InfoItemFlag:public ItemBase
{	int		Minus1;};
typedef	InfoItemFlag*	InfoItemFlagPtr;

//
//Waypoint structure											//RDH 28Nov95
//Like an item, only different!
//
enum	WPNames
{
	WPNAME_None,
	WPNAME_Rendevous,
	WPNAME_Ingress,
	WPNAME_Target,
	WPNAME_Regroup,
	WPNAME_Egress,
	WPNAME_Disperse,
	WPNAME_Landing
};

struct	WayPoint:public	WPOverlayItem	//o14 //o30	//uniqueid and position	
{
	friend	COORDS3D* FindDesPos(WayPointPtr);
	void	operator delete(void* obj)	{::delete(WayPointPtr) obj;}
//	WayPointPtr		next;
	WayPointPtr		prev;							//o14s04
	SLong			range;							//o18s04
	itemptr			target;							//o1Cs04
	SLong			eta;							//o20s04
	SWord			vel;							//o24s02
	ONLYFIELD(UWord,BFieldWaypointActions,action);	//o26s02
	ONLYFIELD(UByte,WPNames,wpname);				//o28s01//WPNAME_None means no name
	UByte			wpnum;							//o29s01//0 means no number
	//During init I use 1 upper bit of skip UID as forward reference flag.
	ONLYFIELD(UWord,UniqueID,skipunder);			//o2As02
	ONLYFIELD(UWord,UniqueID,skipover);				//o2Cs02
	SWord			DUMMYSPARE;						//o2Es02
	WayPoint*	NextWP(UniqueID uniqueID);

	WayPoint()	{Status.size=WayPointSize;target=NULL;next=prev=NULL;
					skipunder=UID_Null;skipover=IllegalSepID;}
	COORDS3D*	FindDesPos();
	WayPointPtr		FindWP(WPNames name);										  //RDH 08/03/99
//DEADCODE DAW 08/06/99 	#ifdef	TEXT_Included
//DEADCODE DAW 08/06/99 	TextSnip0	GetWpName();
//DEADCODE DAW 08/06/99 	#endif
#ifdef TRACKBADASSIGNMENTS
	operator=(WayPoint&);
#endif

};
COORDS3D* FindDesPos(WayPointPtr w);

//
//	Basic item in world must have shape and world pos + unique ID
//  Do we need briefID?
//
//
class	item:public	ItemOverlayWP				//o14	//o1C
{
//private:
//DeadCode PD 26Mar96 	animptr		Anim;		//This is the new shape element linked data area
public:
	animptr		Anim;						//o14s04//This is the new shape element linked data area//PD 26Mar96
	ONLYFIELD(UWord,ShapeNum,shape);		//o18s02
	ONLYFIELD(UWord,UniqueID,SGT);			//o1As02

static	ANGLES	PitchIntercept;									//RDH 01Dec95
static	ANGLES	HdgIntercept;									//RDH 01Dec95
static	SLong	Range;											//RDH 01Dec95
	void	firstshape(UWord ,animptr );
	void	nextshape(UWord ,animptr );
	void	firstweap(UWord ,animptr );
	void	nextweap(UWord	,animptr );
	int		Distance3D(COORDS3D*);
static int	Distance3D(COORDS3D*, COORDS3D*);	//CSB 26/04/99	
	FP		Distance3DSquared(COORDS3D*);
	void InterceptandRange (COORDS3D*);
static 	void item::InterceptandRange (COORDS3D* subject, COORDS3D* target);
//RDH 01Dec95
	void InterceptandRange (ItemBasePtr i) {InterceptandRange(&i->World);}//JIM 31Jul96
	UByte&	AnimByte(Animfieldref);

//public:							//and also controls weapon launching
//	itemptr		Next;
//DeadCode RDH 04Dec95 	UNIQUE_ID	UniqueID;	//access with myitem->UniqueID.count
//	BRIEF_ID	BriefID;
//DeadCode RDH 04Dec95 	ITEM_STATUS	Status;		
//DeadCode RDH 04Dec95 	ITEM_SIZE	ItemSize;
	item()	{Status.size=ItemSize;Next=NULL;SGT=UID_NULL;}		//RJS 21Apr99
	int	FACReportDamage(bool	waskill);
	static	void	FACReportGround();
	void	ScoreSimpleItemKilled(bool itsdead,AirStrucPtr killer);
#ifdef TRACKBADASSIGNMENTS
	operator=(Item&);
#endif
};

//DeadCode RJS 21Apr99 inline	ItemBase::~ItemBase()	
//DeadCode RJS 21Apr99 {	if ((int)Status.size>=(int)ItemSize) 
//DeadCode RJS 21Apr99 		delete [] (char*) ((ItemPtr) this)->Anim;
//DeadCode RJS 21Apr99 	((ItemPtr) this)->Anim=NULL;
//DeadCode RJS 21Apr99 //DEADCODE JIM 19/01/99 	Status.size=ItemBaseSize;
//DeadCode RJS 21Apr99 }
inline	ItemBase::~ItemBase()									//RJS 21Apr99
{	if ((int)Status.size>=(int)ItemSize) 						//RJS 21Apr99
	{															//RJS 21Apr99
		((ItemPtr) this)->Anim.Delete();						//RJS 21Apr99
	}															//RJS 21Apr99
}																//RJS 21Apr99

//
//	Subdividing rotated item to allow simpler objects
//
//
class	hdgitem:public	item			//o1Cs02
{
public:
	ANGLES		hdg;
	hdgitem()	{Status.size=HdgSize;}
	void	operator delete(void* obj)	{::delete(HdgItemPtr) obj;}
};

//
//
//
//
class	hpitem:public	hdgitem			//o1Es02
{
public:
	ANGLES		pitch;
	hpitem()	{Status.size=HPSize;}
	void	operator delete(void* obj) {::delete(hpitem*) obj;}
};

//
//
//
//
class	rotitem:public	hpitem			//o20s02
{
public:
	ANGLES		roll;
	rotitem()	{Status.size=RotatedSize;}
	void	operator delete(void* obj) {::delete(rotitem*) obj;}
};

//
// Mobile item subdivided into vel movement and controled movement
//
class	MovingItem:public	rotitem		//o22
{
public:

void CalcNewPos(SLong deltax,SLong deltay,SLong deltaz);
    SWord		velx,					//o22s02						//RDH 13Nov95
				vely,					//o24s02						//RDH 30Oct95
				velz,					//o26s02						//RDH 30Oct95
				velhori,				//o28s02						//RDH 30Oct95
				vel;					//o2As02//units mm/cs - max 3276m/s=mach 10		//RDH 30Oct95
	//VelX,VelY is not equivalent to VelHori,Hdg when sliding.
	//no longer want deltas inside moving item - calc. as local longs
	//they are useful for collision, of course
	//Delta was Vel * cs /10 -> cm. Max cs=33
	//Vel*4 is a good overestimator throwout before recalc.

	MovingItem()	{Status.size=MovingSize;}
};

//DeadCode AMM 27Aug98 typedef struct _packet PACKET;
//DeadCode AMM 27Aug98 typedef struct _packet* LPPACKET;
//
// MobileItem allows a movecode and a waypoint
//
//
class WorldStuff;
class	shape;
typedef shape Shape;
class	mobileitem:public	MovingItem	//o2C
{
	friend class item;
	friend class ManualPilot;									//AMM 01Jun98
	friend class Replay;										//AMM 01Jun98
	friend class DPlay;											//AMM 01Jun98
	friend class Persons2;	friend class Persons3;
	friend class TransObj;										//PD 01May96
	friend	void SendInit2Packet ();							//ARM 17Sep96
//DeadCode AMM 27Aug98 	friend	void CopyPacket (ItemBasePtr lpItemBase);		//AMM 25Aug98
	friend Shape;											//RJS 05Aug96
	friend class State3dOnGoing;											//RJS 05Aug96
	friend class ArtInt;											//RJS 05Aug96
	friend class TrgListProc;											//RJS 05Aug96
	friend class BoxCol;											//RJS 05Aug96
//LastModified:	JIM 24Sep96

private:
static	void MoveList(MobileItemPtr entry,WorldStuff& world);
static	MobileItemPtr	MobileList;
protected:
static	void MoveItem(MobileItemPtr entry,WorldStuff&);				//PD 02May96
static	MobileItemPtr	ACList;
public:
static  WorldStuff*		currworld;								//DAW 02Apr96
static	UByte	timerseed;
static int	timeofday;
static	void SetWorld(WorldStuff* w)	{currworld=w;}					//JIM 25Jul96
static	WorldStuff& GetWorld() {return *currworld;}				//ARM 25Jul96
	void	operator delete(void* obj)	{::delete(MovingItemPtr) obj;}
static	void MoveAll(WorldStuff& world);

	MobileItemPtr			nextmobile;			//o2Cs04
	WayPointPtr	waypoint;						//o30s04

	FIRSTFIELD( UByte,	AutoMoveCodeTypeSelect,movecode,	5)		//o34s01
	LASTFIELD(			Nationality,nationality,			6,7)
//	AutoMoveCodeTypeSelect	movecode:6;
//	Nationality				nationality:2;

	mobileitem()	{Status.size=MobileSize;waypoint=NULL;}
	void AddToList();

void	ExecuteWayPointAction ();								//RDH 19Feb96
void	DoWayPointAction (AutoMoveCodeTypeSelect	oldmove,WayPointPtr	oldwp,BFieldWaypointActions wpa);

void	NextWayPoint ();										//RDH 19Feb96
void	TeleportWayPoint ();										//RDH 19Feb96
BFieldWaypointActions
		EndLoopWayPoint ();										//RDH 19Feb96
BFieldWaypointActions
		MidLoopWayPoint ();										//RDH 19Feb96
bool	EscorteePastWP(WayPointPtr);
void	ForceBreakLoopWayPoint();		
//DeadCode DAW 19Nov96 void	MidLoopWayPoint ();										//RDH 19Feb96
void	WaitDeadWayPoint ();										//RDH 19Feb96
void	StartBombing ();										//RDH 19Feb96
void	StartStraffe ();										//RDH 19Feb96
void	LandingWayPoint ();
void	KillItNow ();
COORDS3D*	FindDesPos();
void	CalcXYZVel ();
void	NewPosition ();
static	void	WinMove (int timeofday,WorldStuff* worldref);							//ARM 16Sep96
static	void DosMove (int timeofday,WorldStuff* worldref);										//ARM 09Oct96
WorldStuff* GetCurrWorld () { return currworld; }				//ARM 06Sep96

static	void	ResetACGears();									//RJS 01Jun99

};

//
//transient item has targets and timers
//
class	TransientItem:public	mobileitem		//o35	//o50
{
public:
	static int transcount;
	void	operator delete(void* obj)	{::delete(TransientItemPtr) obj;}
	TransientItem()
	{
		Status.size=TransientSize;														//RJS 15Jun99
//DeadCode RJS 15Jun99 		Status.deadtime = 0;															//RJS 15Jun99
//DeadCode RJS 15Jun99 		Status.deadscale = 0;															//RJS 15Jun99
//DeadCode RJS 15Jun99 		Status.deaded = FALSE;															//RJS 15Jun99
		transcount++;
		isDeleted=0;
		isArmed=0;
	}																					//RJS 15Jun99
	void AddToList();
static	TransientItemPtr	TransientList;						//MGA 13Mar96
static	void MoveTransList(TransientItemPtr entry, WorldStuff& world);//DAW 12Mar96
static	void MoveTransItem(TransientItemPtr entry,WorldStuff&);		//PD 26Apr96
static	void MoveAllTrans(WorldStuff& world);						//MGA 20Mar96


	UByte	CollTestEnabled		:1,				//o35s01				//RJS 21Jul98
			CollSuccessTrans	:1,								//RJS 21Jul98
			isOwned				:1,								//RJS 29Mar99
			isDeleted			:1,								//DAW 19May99
			isArmed				:1;								//DAW 19May99

	UWord	DrawOffset;							//o36s02				//RJS 27Nov98
	itemptr	Launcher;							//o38s04				//MGA 22Feb96
	itemptr Target;								//o3Cs04				//MGA 22Feb96
//TempCode MGA 29Feb96 	ShapeNum shape; //already have a shape in item definition
	SLong	LaunchTime;							//o40s04

	TransientItemPtr	nexttrans;				//o44s04			//MGA 28Feb96
	TransientItemPtr	nexttogo;				//o48s04

	UWord	TransRandom;						//o4Cs02				//PD 29Apr96
	UWord	TmpLaunchTime;							//o4Es02	//DAW 19May99
	ULong	TimeOfLaunch;										//DAW 19May99

};												//o50


//
// FormationItem allows mobiles to link together
//
//
inline DutyType	BasicDuty(DutyType duty)
{
	if ((int)duty&(int)ACTIONSUBCODE)
		return DutyType((int)duty&(int)DUTYMASK);
	else
		return duty;
}

struct	ContourList;
class	formationitem:public	mobileitem		//o35	//o4A
{
public:
	ONLYFIELD(UByte,FormationIndex,formpos);	//o35s01//alignment optimisation			//JIM 20Aug96

	FIRSTFIELD(UWord,	FORMATIONDESC,formation,	5)		//o36s02
		BITFIELD(		Bool,slowdownleader,		6,6)
		BITFIELD(		Bool,information,			7,7)
		BITFIELD(		DutyType,duty,				8,13)
		BITFIELD(		Bool,advantage,				14,14)
	LASTFIELD(		Bool,disadvantage,			15,15)


	FormationItemPtr
				leader,							//o38s04
				follower;						//o3Cs04

FormationItemPtr&	Leader()	{return (leader);}
FormationItemPtr&	Follower()	{return (follower);}
	ClassPtr	classtype;					   //o40s04

	ContourList*	contourlist;				//o44s04
	
	UWord		manoeuvretime;					//o48s02//max 655sec=11min								//JIM 20/01/99

	DutyType	BasicDuty()
	{
		if ((int)duty&(int)ACTIONSUBCODE)
			return DutyType((int)duty&(int)DUTYMASK);
		else
			return duty;
	}

	formationitem()
	{	Status.size=FormationSize;
		leader=NULL;follower=NULL;contourlist=NULL;
	}

	void	operator delete(void* obj)	{::delete(FormationItemPtr) obj;}
	SWord TimeLeft();
	void SetManoeuvreTime (UWord time=6000);
	void	AutoTaxi ();
	void	WaitToTaxi();
	SLong CalcReqVel ();
	Bool CalcVel ();
	Bool CalcVelSub (SLong reqvel);			//RDH 28Feb96
//DeadCode CSB 12/02/99		SWord CalcAccel (SWord, SWord);
//DeadCode CSB 12/02/99		void AddAccel2Vel(SWord);
	Bool CalcHdgRollFlat ();
	Bool AutoCalcPitch ();
	void MoveRollToZero(SWord	reqdeltahdg);	
	void GetFollower_xyz (FormationTypeIndex formationtype, FormationItemPtr leader = NULL);			//RDH 27Feb96	//CSB 25/05/99	
	void BreakForm();
	void RemoveDeadMember();
#ifdef	FILE_Included
bool	PlayerSequenceAudible(FileNum f); //msgai
#endif

	ItemPtr				SelectTarget(ItemPtr currtarget,int* selectedelt=NULL,int counter=0);
	int					SelectElement(ItemPtr currtarget,int counter=0);
	FormationItemPtr	SelectConvoyMember(FormationItemPtr curr,int count);
	bool				EnoughDamage3D(ItemPtr currtarget);
//	Coords3D*			FormationItem::SelectedElement(ItemPtr currtarget,int counter=0,Coords3D* coords=&despos);
	bool				FormationItem::SelectedElement(ItemPtr currtarget,int counter=0,Coords3D* coords=&despos); //alive flag

	Bool CheckForWeapon(UByte ltype);							//CSB 26/03/99	

};

class	shipitem:public	formationitem
{
public:
	shipitem()	{Status.size=ShipSize;}
};

struct	ai_info						//contains floats	//o??s60
{

	itemptr		unfriendly,											//o00s04//save
				homebase;											//o04s04//unchanged
	AirStrucPtr	Unfriendly()	{return *unfriendly;}
	AirStrucPtr	attacker;											//o08s04//save

																//o0Cs04
		FIRSTFIELD(ULong,	SkillType,combatskill,			3)	//4	//unchanged
		BITFIELD(		SkillType,flyingskill,			4,7)	//4	//unchanged
		BITFIELD(		UByte,ManStep,				8,11)		//4	//save
		BITFIELD(		CharacterType,character,	12,13)		//2	//notused
		BITFIELD(		MANOEUVRE,manoeuvre,		14,20)		//7	//save
		BITFIELD(		Bool,radiosilent,			21,21)		//1	//unchanged
		BITFIELD(		Bool,simpleacm,				22,22)		//1	//save	
		BITFIELD(		Bool,flatturn,				23,23)		//1	//save
		LASTFIELD(		int,pilotnum,				24,31)	//8 //only need 6*16=7 bits #6 => not pilot
	UByte	morale;												//o10s01	//save
	SByte				moraleinc;								//o11s01	//save

//		BITFIELD(		NextLeadAct,leaderaction,	8,10)		//3	//unchanged
//		BITFIELD(		NextFollAct,followeraction,	27,29)		//3	//unchanged

	ONLYFIELD(UByte,tThreatLevel,			threatlevel);		//o12s01						//unchanged
	ONLYFIELD(UByte,tAggressionLevel,		aggressionlevel);	//o13s01						//unchanged
	ONLYFIELD(UByte,tFirstEncounterTactics,	firsttactic);		//o14s01					//unchanged
	ONLYFIELD(UByte,AcTactics,		elementtactics);			//o15s01						//unchanged	
	ONLYFIELD(UByte,AcTactics,		flighttactics);				//o16s01					//unchanged
	ONLYFIELD(UByte,AcTactics,		squadrontactics);			//o17s01					//unchanged	
//##not
//word aligned:
//DeadCode RDH 10Aug98 	UWord		JinkTime;										//DAW 12Jun96
	SLong		lastdelta;										//o18s04	//save, //delta from ideal shooting position
//DeadCode CSB 29/03/99		SLong		oldufposx, oldoldufposx, oldoldoldufposx,
//DeadCode CSB 29/03/99					oldufposy, oldoldufposy, oldoldoldufposy,
//DeadCode CSB 29/03/99					oldufposz, oldoldufposz, oldoldoldufposz;
	ANGLES		desiredroll,									//o1Cs02	//save
				desiredpitch,									//o1Es02	//save
//DEADCODE JIM 28/04/99 				lastdeltaroll,									//o20s02	//save
 				desiredaoa,										//o20s02	//save
				oldpitchI,										//o22s02	//save
				oldoldpitchI,									//o24s02	//save
				oldoldoldpitchI,								//o26s02	//save
				oldhdgI,										//o28s02	//save
				oldoldhdgI,										//o2As02	//save
				oldoldoldhdgI,									//o2Cs02	//save
				desiredhdg;										//o3Es02	//save

	Float		desiredturn,									//o40s08	//save
				desiredpitchrate;								//o48s08	//save
	ULong		desiredrange,									//o50s04	//save
				desiredalt;										//o54s04	//save
//there is also a deltapitchsum in acm. The acm one controls the 
//elevator integral control. This one is at a higher level
	SLong		deltapitchsum;									//o58s04	//save
//DeadCode RDH 20Sep98 	SWord		currentbuffet;									//RDH 06Jun96
	EventLogPtr	eventlog;										//o5Cs04	//ask jim
//DeadCode JIM 10Jun96 	msgptr		MessageList;	//this is it.. use msg->flags to say done/read
	 							//Use fixed speed looping to process times.
	ai_info()	{unfriendly=homebase=NULL;attacker=NULL;eventlog=NULL;}//JIM 08Aug96
	enum	{PROPER_PILOT_MAX=200};
	int	squadnum()	{if (pilotnum<(int)PROPER_PILOT_MAX) return (pilotnum*11)>>8; else return pilotnum-(int)PROPER_PILOT_MAX;	}
};
struct	weap_info					   //o??s20
{
	int		reloadmass;			//o00s04//0.01 g includes all weapons and weight of fuel tank but not weight of fuel
	int		reloaddrag;			//o04s04//N
	int		mass;				//o08s04//0.01 g includes all weapons and weight of fuel tank but not weight of fuel
	int		drag;				//o0Cs04//N
	int		int_fuel;			//o10s04//0.01 g
	int		ext_fuel;			//o14s04//0.01 g
	SWord	int_fuel_leakage;	//o18s02//g/s
	SWord	ext_fuel_leakage;	//o1As02//g/s
	SByte	int_launcher;		//o1Cs01									//RJS 25Mar99
	SByte	ext_launcher;		//o1Ds01									//RJS 25Mar99
	UWord	DUMMYWASTAGE;		//o1Es02
};
struct	weap_ctl			//o??s6C
{
	weap_info	right;			//o00s20
	weap_info	centre;			//o20s20
	weap_info	left;			//o40s20
	
	SWord		ShootDelay;		//o60s02									//save
	FIRSTFIELD(UWord,Bool,UseIntFuel,0)		//o62s02
	BITFIELD(		Bool,FuelDumped,1,1)
	BITFIELD(		Bool,StoresDumped,2,2)
	BITFIELD(		Bool,Ejected,3,3)
	BITFIELD(		Bool,reportedbingo,4,4)
	BITFIELD(		Bool,reportedbingohurting,5,5)
//
//	Spare bits 6-10
//
//need to store AnimWeaponPack for ac to reset rockets etc
	LASTFIELD(		int,Weapons,11,15)					//AMM 07Apr99
	UByte	weapontype;						//o64s01		//LT_ byte
	UByte	shpweapindex;					//o65s01		//Index is basically aircraft type...
	SWord		weapforce;					//o66s02					//RJS 16Sep98
	TransientItem*	currentbullet;			//o68s04					//RJS 29Mar99
};

struct	flight_ctl						//o??s40
{
										//save //RDH 03/03/99
	AirStrucPtr	nextflight,				//o00s04							//save
				leadflight;				//o04s04							//save
	AirStrucPtr	leadelt();
	SWord		rpm,					//o08s02							//save
				thrustpercent,			//o0As02							//save
				afterburner;			//o0Cs02							//not used
//				LastRoll;
	ANGLES		cpitch;					//o0Es02							//calc
	WayPointPtr	backupWP;				//o10s04							//save
	SLong		//cposy,
				gforce;					//o14s04							//save
	SLong		groundlevel;			//o18s04							//calc _Collide.LowestSafeAlt(this,					//JIM 29Oct96
																	//			pitch,				//JIM 29Oct96
																	//		roll);	
	ONLYFIELD(UByte,FormationIndex,originalformpos);	//o1Cs01

	FIRSTFIELD(UByte,	UByte,comefrommap,		6)		//o1Ds01			//ask jim
	LASTFIELD(			Bool,inRadarSight,		7,7)	//RJS 13May99
	SByte		redeffect;								//o1Es01	//ask Paul
	UByte		callname;								//o1Fs01		//ask Jim
	UByte		callnum;								//o20s01		//sak Jim
//TEMPCODE JIM 28/04/99 	UByte		callvoice;
	UByte		AeroDeviceCnt;							//o21s01		//RJS 18Sep98

	SWord		i_a_s,									//o22s02		//calc from SetInstruments
				vel_cms;								//o24s02		//calc from setFlightParams, questio need
																
	SWord		aileron,								//o26s02		//save
				elevator,								//o28s02		//save
				rudder;									//o2As02		//save


	PMODEL		pModel;									//02Cs04		//model.h	
	PACMMODEL	pAcmModel;								//030s04		//acmmodel.h
	PINSTRUMENTS	pInst;								//034s04		//ask Robert

	Float		dhdg;									//038s08		//save


	flight_ctl()	{backupWP=NULL;nextflight=leadflight=NULL;}

};

//DEADCODE JIM 28/04/99 struct	instrum_ctl
//DEADCODE JIM 28/04/99 {
//DEADCODE JIM 28/04/99 //LIGHTS		InstrumLights;	//most flags are in animation data
//DEADCODE JIM 28/04/99 
//DEADCODE JIM 28/04/99 };

//

struct RequiredBankDataElement									//RDH 18Dec95
	{															//RDH 18Dec95
//Old_Code PD 10Nov97 		ANGLES hdg; ANGLES roll;								//RDH 18Dec95
		ANGLESInst hdg; ANGLESInst roll;								//RDH 18Dec95
	};															//RDH 18Dec95

// Don't want to include "model.h"								//ARM 01May97
Bool NewModel (AirStrucPtr const);								//ARM 01May97
void DeleteModel (AirStrucPtr const);							//ARM 01May97


//variables commented to indicate action required for replay, rdh
//				save			need to savethe variable in the replay file
//				set by ***		use the function *** to set the variable
//				unchanged		the variable, once set is never changed
//				zero			the variable should be zeroed on replaying 


class	AirStruc:public shipitem		//o4A
{							//0					1							2							3
public:
// used in coop multiplayer games to decide which player transmits an AI ACs collisions
// with players
	UNIQUE_ID	lasthitter;					//o4As02					//save

public:		
	ai_info		ai;							//o4Cs60
	weap_ctl	weap;						//oACs6C	//ask Rob
	flight_ctl	fly;						//o118s40
//DEADCODE JIM 28/04/99   	instrum_ctl	inst;						//o158s	//ask Robert

	ONLYFIELD(UWord,UniqueID,CommsOwner);	//o158s02



static	bool		playermoving;
static	AirStrucPtr	playernotmovingheldac;
static	bool		PlayerStartedMoving();

static UWord airdensityratiosquareroot[];

static UWord vel_to_aoa[];

//constructors

	AirStruc()													//ARM 01May97
	{															//ARM 01May97
		Status.size = AirStrucSize;								//ARM 01May97
		NewModel (this);										//ARM 01May97
	}															//ARM 01May97
	~AirStruc()													//ARM 01May97
	{															//ARM 01May97
		DeleteModel (this);										//ARM 01May97
	}															//ARM 01May97
#ifdef TRACKBADASSIGNMENTS
	operator=(AirStruc&);
#endif

	void AddToList();
	void	operator delete(void* obj)	{::delete(AirStrucPtr) obj;}

//movecodes
	void	AutoCommsAccel();
	void	MoveMissionDiceThrow();
	void AutoTaxi();											//RDH 28Feb96
	void AutoFollowWp ();
//DeadCode RDH 05Jan99 	void AutoTrainingACM ();
	void AutoCrashSkid();
	void AutoAccelerate();
	void AutoCrashRoll();
//DeadCode RDH 05Jan99 	void AutoTrainingPreMerge ();
//DeadCode RDH 05Jan99 	void SelectNextTrainingManoeuvre();
	void AutoFollowWpWing (AirStrucPtr MyLeader = NULL);		//RDH 27Feb96	//CSB 20/04/99	
	void	AutoTakeOff ();										//RDH 17Jun96
	void
 	AutoLanding ();
	void	HeldACCheck();

	void	AutoTakeOffWing ();									//RDH 17Jun96
	void	AirStruc::TrackBogey();
	void	AirStruc::TrackBandit();

	void	FirstTimeInCombatMsg();						  //RDH 04/03/99
	bool	OutNumbered(AirStruc* trg);								  //RDH 04/03/99

	void	InformOfDanger(AirStruc* caller, AirStruc* callee);													  //RDH 04/03/99
	void AutoPreCombat ();
	void AirCombat();
	void FrightenBogie();						//rdh 17/12/98
	void SelectNextTwoSeaterManoeuvre ();				//RDH 19Nov96
	void TwoSeaterDefence();										//RDH 19Nov96
	void SimpleACM();	
	void ManualACM();
	void BreakCallandReaction(AirStrucPtr buddy,AirStrucPtr currac,AirStrucPtr unf); //RDH 13/06/99
	void BreakCallReaction(AirStrucPtr currac,AirStrucPtr unf);		  //RDH 27/06/99


	void SetDesiredVel();			//rdh9/12/98
	void SelectNextEngageManoeuvre();									//RDH 12Mar96
	void	SetACMType();											  //RDH 26/03/99
	void	ChooseRadioMessage();							  //RDH 04/03/99
	void SelectNextEvadeManoeuvre();									//RDH 12Mar96
	void AutoSpiral2Ground(WorldStuff&);							
//DeadCode RDH 10Sep96 static	void AutoDeathSequence(MobileItemPtr);							//RJS 08Aug96
	void AutoDeathSequence();									//RDH 10Sep96
	void AutoResurrect(AirStrucPtr);							//ARM 05Dec96
	void AutoToGrndPitchRoll(ANGLES grndroll,ANGLES grndpitch);	//RJS 03Oct96
	void AutoStraffe();											//MS 18Oct96
	void	CheckBombingStatus();
	void	AutoBomb();											//MS 18Oct96
	void	AutoFAC ();
	int		GetFACStage();

	void	AutoCAS();
	AirStrucPtr	FindMyFAC();
	void	SetToCAS(bool firsttime=true);


	void AutoBombHigh();										//CSB 25/03/99	
	void AutoBombLow();											//CSB 25/03/99	
	void AutoBombDive();										//CSB 25/03/99	
	void AutoBombFollow();										//CSB 11/05/99	
	void AutoOrbit(COORDS3D centre, int radius);				//CSB 31/03/99	
//DeadCode DAW 27Jun99 	Bool CheckForWeapon(UByte ltype);							//CSB 26/03/99	
	Bool CheckForAnyWeapon();									//CSB 26/03/99	
	Bool ChooseAWeapon();										//CSB 02/04/99	
	Bool CarryingNapalm();										//CSB 29/04/99	
	Bool SelectBombTarget(Bool NewTarg);						//CSB 03/04/99	
	Bool AnyoneInPhaseN(char PhaseNum);							//CSB 03/04/99
	Bool IsThisBombLeader();									//CSB 23/04/99	
	bool IsLocalLeader();									//CSB 11/05/99	
	UWord CountGroup();											//CSB 23/04/99	
	COORDS3D* RotateToHdg(COORDS3D GlobDelta, COORDS3D& LocalDelta, ANGLES Heading);	//CSB 23/04/99	
	UniqueID FindLeadUID();	//CSB 07/06/99
	void WindTrackCorrection(SWord, SWord, SWord, SWord&, SWord&, SWord&);	//CSB 10/06/99	
	void WindBulletDrift    (SWord, SWord, SWord, SWord&, SWord&, SWord&);	//CSB 10/06/99	
	void CalcBulletVel(SWord MuzVel, SWord &Hdg, SWord &Pitch, SWord &BullVel);	//CSB 11/06/99	

	ItemPtr	CheckFACTarget(ItemBasePtr targ);
	void	LogAutoCASKill();

	void SendFACMessage(PhaseFAC phase);
	Bool	HasSmoked();										//RJS 12Mar99	
	AirStrucPtr	FlyEscortTo();	//returns null if independent
	AirStrucPtr	FindLeadCandidate();	//CSB 20/04/99	
	void	ChainBingoMessage(bool atbingohurting);

//secondary stuff
public:
AirStrucPtr&	Leader()	{return *(AirStrucPtr*)(&leader);}
AirStrucPtr&	Follower()	{return *(AirStrucPtr*)(&follower);}
//	UByte	AirStruc::FightingFactor();
	UByte	AirStruc::CombatFactor();
	UByte	AirStruc::FlyingFactor();

//DeadCode JIM 15Oct96 	void RemoveDeadMember();
	void BreakForm();

	Bool	IsUsingPilotedAcLog();
	COORDS3D* FindDesPos ();
	COORDS3D* FindCombatPos ();
	COORDS3D* PositionWRTLeader (AirStrucPtr lf = NULL);										//RDH 27Feb96	//CSB 25/05/99	
	COORDS3D* PositionTakeOffWRTLeader ();						//RDH 17Jun96
	void SetManualFlightParams ();								//RDH 22Apr96
//DEADCODE RDH 30/04/99 	void SendEveryOneHome ();									//RDH 24Sep96
	void LeaderBreakOff ();									//RDH 24Sep96
//DEADCODE RDH 30/04/99 	void SetWaypointForEveryBody(AirStrucPtr,WayPointPtr);									//RDH 24Sep96
	SWord RequiredDRoll (SWord);
	SWord RequiredDRollSub (SWord);								//RDH 11Oct96
	void AirStruc::RemoveFuelLeakage(weap_info weapinfo, SWord Xpos, UWord NFrames);

	void FuelLeft (FP FuelRate);								//RDH 03Jun96	//CSB 15/09/98
//DeadCode CSB 12/02/99		Bool CalcVelSub (SLong reqvel);								//RDH 15Nov96
	Bool CalcVel ();											//RDH 22Nov96
	Bool AutoCalcPitch ();
	void NewPosition ();
	void NewDeadPosition ();									//RJS 23Feb98
	void CalcNewPosWithWind(SLong deltax,SLong deltay,SLong deltaz,SLong groundlevel);
	void	CalcXYZVel ();
	void	CheckManualCourse();
	Bool	FuelShort(int excesstime,int* avail=NULL,int* safety=NULL );
	Bool	AirStruc::AircraftDamaged();
//DEADCODE JIM 25/04/99 static	void EndGameScoring();								//RDH 09Sep96
static	void PrelimActivePilotChk ();					//RDH 11Dec96
static	SkillType IncSkill (AirStrucPtr,SWord aircraft_no);			//RDH 04Dec96
static	void PlayerDecision ();						//RDH 09Sep96
static	void ModifySquadronMorale(MoraleType);		//RDH 09Sep96
static	void ModifyPilotMorale(SWord, MoraleType);				//RDH 09Sep96
static	void ModifyPlayerMerit(DeltaMeritType);				//RDH 09Sep96
	ANGLES AirStruc::BestClimbAngle();
	Bool	IsHealthyMovecode(ULong&);//RJS 28Aug98

	SLong  CalcBestClimbSpeed();	//CSB 28/09/98
	SWord  CalcBestClimbPitch();	//CSB 28/09/98
	SLong  CalcMaxVelSL ();			//CSB 28/09/98
	SLong  CalcMaxVelDive ();		//CSB 28/09/98
	SWord  CalcAccel(SWord);	//CSB 02/02/99
	void   AddAccel2Vel(SWord Accel);	//CSB 12/02/99
	Bool CalcVelAlt ();				//CSB 29/09/98
	Bool CalcVelAlt (SLong	reqvel);								  //JIM 01/02/99
	Bool CalcHdgRollLimited ();		//CSB 29/09/98
	Bool CalcHdgRollLimited (SWord reqdeltahdg);		//CSB 29/09/98
	void	SetWeaponForce(SLong mass=0,SLong velocity=0,SLong delay=1);//RJS 16Sep98
	void SetFlightParams (bool dotimestuff=true);									//AMM 24Sep98
	void	SetMaccaVels();										//AMM 20Oct98

	Coords3D*	GetTakeOffPos(UniqueID takeoffID,Coords3D& postofill=despos);
	Bool	AmISmoking();										//RJS 18Feb99

																	  
	AirStrucPtr	GroupLeader()
	{	AirStrucPtr	rv=this;
		if (leader)			rv=Leader();
		if (rv->formpos)	rv=rv->fly.leadflight;
		return	rv;
	}
	Bool	TargetOnSubjectTail(ANGLES);
	Bool	SubjectOnTargetTail(ANGLES);
	Bool	TargetFacingSubject(ANGLES);
	Bool	SubjectFacingTarget(ANGLES);
	void	SetFollowersTactic(int);	//CSB 05/07/99	



private:
//DeadCode JIM 15Oct96 	void BreakForm();
	void CopyLeader (AirStrucPtr lf);											//RDH 27Feb96
	Bool CopyLeaderSub (AirStrucPtr lf);											//RDH 27Feb96
	void GetFlightLeader_xyz (SquadronTypeIndex 	formationtype);//RDH 17Jun96
//DeadCode JIM 30Apr96 	void GetFollower_xyz ();			//RDH 27Feb96
//DeadCode JIM 29Apr96 	SLong CalcReqVel ();
//DeadCode JIM 29Apr96 	Bool CalcVel ();
//DeadCode JIM 29Apr96 	Bool CalcVelSub (SLong reqvel);								//RDH 28Feb96
//DeadCode JIM 29Apr96 	Bool CalcHdgRollFlat ();
//DeadCode JIM 29Apr96 	Bool AutoCalcPitch ();
//DeadCode JIM 29Apr96 	void CalcXYZVel ();
//DeadCode JIM 29Apr96 	void SetManoeuvreTime (UWord time=2000);
	SWord ReachedDesPos ();
//DeadCode JIM 01May96 	void NewPosition ();
	void SetRpm ();
//DeadCode JIM 29Apr96 	SWord TimeLeft();
//DeadCode AMM 24Sep98 	void SetFlightParams ();									//DAW 04Jul96
	Bool RollLevel (int delta);
	Bool CalcVelWing (AirStrucPtr lf, SLong Dist);										//JIM 29Oct96
	Bool CalcHdgRoll ();									//RDH 28Feb96
	Bool CalcHdgRoll (SWord delta);									//RDH 28Feb96
	SLong CalcHdg ();											//RDH 11Oct96
	void WindCorrection();
	Bool SideSlip (AirStrucPtr);											//RDH 28Feb96
	Bool SideSlide(AirStrucPtr);											//CSB 20/04/99	
	SWord FindRequiredRoll (SWord, RequiredBankDataElement*);
	void	SetControlSurfaces (); //RDH 25Mar96
//	void	SetInstruments (); //RDH 25Mar96

//ACM member functions
//DEADCODE RDH 21/02/99 	void	MoveToHdg (ANGLES);
	void	MoveToHdg (ANGLES desiredhdg, ANGLES desiredpitch);		  //RDH 21/02/99
 
	void	MoveToHdgOnThisRoll (ANGLES,ANGLES);
	void	MoveToAoA (ANGLES);
	void	MoveToRudder (SWord);
	void	MoveToSlip (ANGLES);
	void	MoveToPitch (ANGLES,SWord);
	void	MoveToAcPitch (ANGLES);
	SWord	MoveToDesiredPitch (ANGLES,ANGLES);
	SWord	DesiredPitchChk (ANGLES,ANGLES);
	SWord	DesiredAcPitchChk (ANGLES,ANGLES);					//RDH 01Nov96
//DEADCODE RDH 21/02/99 	Bool	MoveToDesiredHdg (ANGLES,ANGLES);
	Bool	MoveToDesiredHdg (ANGLES desiredhdg,ANGLES desiredpitch,ANGLES target);

	Bool	ChkAtDesiredHdg (ANGLES,ANGLES);						//RDH 01Apr96
	Bool	ChkAtDesiredAcHdg (ANGLES,ANGLES);					//RDH 01Nov96
	Bool	AirStruc::ChkAtDesiredRoll (ANGLES desiredroll,ANGLES target);

	SWord	MoveToDesiredHdgOnThisRoll (ANGLES,ANGLES,ANGLES);
	void	ClimbAtBestSpeed ();
	void	MoveToRoll (SWord,SWord);
//DeadCode RDH 05Jan99 	void	TightClimbingTurn (ANGLES);
	void	MoveToThrust (SWord);
	void	SimpleMoveToThrust (SWord);							//RDH 11Oct96
	void	SimpleCalcVel ();
	SWord 	ManoeuvreTimeLeft ();
	bool	WeldedWingSixOK();
	bool	BreakCallNecessary(AirStrucPtr currac,AirStrucPtr unf, int range);

//DeadCode RDH 05Jan99  	void	TightTurn (SLong recovery_alt);					//RDH 12Jul96
 	void	AutoShoot (Bool manual);							//RDH 22Oct96
	void	FireABullet(SWord delaybetweenbursts,Bool isArmed=TRUE); //RJS 27May99
	void	FireARocket(SWord delaybetweenbursts,Bool isArmed=TRUE); //RJS 27May99
	void	SplitS ();
	void	ZoomandDrop ();
	void	StandOnTail ( );
	void	GainHeight ( );
	void	ShootToFrighten ( );
	void	DiveAndZoom ( );
	void	FlatTurn ();										//RDH 28Mar96
	void 	GainSpeed();										//RDH 27Apr98
	void 	LookAround ();										//RDH 19Aug96
	void	AirStruc::WeldedWingMan();
	void	AirStruc::BailOut();
	void 	TopCover ();										//RDH 19Aug96
	void	AirStruc::LineAbreast();
	void	AirStruc::Scatter();
	void	AirStruc::Pincer();
	void	AirStruc::MultiWave();

//rdh	void	AirStruc::DiveAndZoom ();
	void	AirStruc::LeadPursuit();
	void	AirStruc::LagPursuit();
	void	AirStruc::Circumvent();
//	void	AirStruc::DecoyActive();
//	void	AirStruc::DecoyPassive();
	void	AirStruc::RoundAbout();
	void	AirStruc::SplitManoeuvre();
	void	AirStruc::ResetUnfriendly();
	void	AirStruc::HeadOn ( );
	void	AirStruc::LineAstern();
	void AirStruc::ShootTooEarly();

	void	AirStruc::LagRoll();
	void	AirStruc::ExtensionManoeuvre();
	void	DivingSpin();
	void	AirStruc::ReverseTurn();
	void	AirStruc::SelfAsBait();
	void	AirStruc::Jink();
	void	AirStruc::BreakTurn();
	void	AirStruc::LazyTurn();
	void	AirStruc::Break180();
	void	AirStruc::BreakLow();
	void	AirStruc::BreakHigh();
	void	AirStruc::Break90();
	void	AirStruc::HiGBarrelRoll();
	void	AirStruc::PanicTurn();
	void	AirStruc::UnBalancedFlight();
//	void	AirStruc::TrackingShot();
	void	AirStruc::LowAlt();
	void	AirStruc::SnapShot();
	void	AirStruc::StayOnTail();
	Bool	AirStruc::TurnToHdgAndPitch();
//DeadCode RDH 07Jan99 	void	AirStruc::HotSideLagPursuitFight();
//DeadCode RDH 07Jan99 	Bool	AirStruc::SandwichManoeuvres();
//	SWord	AirStruc::RollforTurn(SWord reqdeltapitch,SWord deltahdg, Float& desiredturn);
	SWord	AirStruc::RollforTurn(SWord reqdeltapitch,SWord deltahdg, Float& desiredturn,COORDS3D	target);
	void		AirStruc::CalcDesiredPitchRate(SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos);
	FP		AirStruc::CoarseRollAdjust(FP rroll, FP fpitch);
	FP		AirStruc::FineRollAdjust(SWord reqdeltapitch,SWord deltahdg,FP rroll, FP fpitch, FP fhdg);
	Bool	AirStruc::UnfriendlyOnSameRoll();


//DeadCode RDH 07Jan99 	void	AirStruc::SustainedTurn();
	void	AirStruc::TurningFight();
//	void	AirStruc::CalcLead(SWord& velx,SWord& vely,SWord& velz);
//	void	AirStruc::CalcLead(AirStrucPtr  subject, AirStrucPtr target, SWord& velx,SWord& vely,SWord& velz);
	void	AirStruc::CalcLead(AirStrucPtr  subject, AirStrucPtr target, SLong& velx,SLong& vely,SLong& velz, Bool cutcorner);

//	void	AirStruc::TurnFightSub(ANGLES	HdgIntercept);
//	void	AirStruc::TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch);
	void	AirStruc::TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target);
	void	AirStruc::TurnFightPhase1(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target);

//	void	AirStruc::TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget);
	void	AirStruc::SlowDownCheck(UWord reqdeltahdg_pos);
	void	AirStruc::SlowDown(FP velc);
	void	AirStruc::SpeedUp(FP velc);

	SWord	AirStruc::ThrustfromFF();


//	void	AirStruc::TurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget);
	void	AirStruc::TurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget,COORDS3D	target);

	void	AirStruc::HighYoYo();
	void	AirStruc::Zoom();
	void	AirStruc::LowYoYo ( );
	void	AirStruc::TurnFightTargetNotOnNose(SWord	reqdeltahdg, SWord	reqdeltapitch, SWord	reqdeltapitch_sign,UWord	reqdeltapitch_pos, ANGLES	deltapitch);
	void	AirStruc::RollAndPull(SWord	reqdeltahdg, SWord dpitch);

	void	AirStruc::InterceptHigh();
	void	AirStruc::ClimbAtSustainedTurnSpeed();
	
	Bool	AirStruc::BanditOnColdSide();
	Bool	AirStruc::BanditHasLead();

	Bool 	AllOnTopCover ();										//RDH 19Aug96
	Bool	AllButLdrNotOnCombat ();								//RDH 11Nov96
	void	BarrelRollAttack ( );
	void	Scissors ( );
	void	MildScissors ( );
	void	StraightandLevel ( );
//DeadCode RDH 30Mar98 	void	AcmSideSlip ( );
	void	SpinOut ( );
	void	DiveforHome ( );
	void	ClimbforHome ( );
	void	StraightDive ( );
	void	GoHome ( );
	void	MakeForFriendly ( );
	void	MoveAway ( );
//DeadCode RDH 06Jan99 	void	AccidentalSpinOut ( );
	void	SpinRecovery ( );								//RDH 21Aug96
//rdh	void	TurningFight ( );
	void	LowGYoYo ( );
	void	RollAway ( );
//DeadCode RDH 07Jan99 	void	VerticalLoop ( );
//DeadCode RDH 07Jan99 	void	ImmelmannTurn ( );
	void	HeadOnOffset ( );
	void	Immelmann ( );
	void	StayWithPrey ( );
//DeadCode RDH 05Jan99 	void	GatherSpeed ();
	void	LeadUnFriendly ();


	Float	CalcSimpleAccel ();
	UWord	CalcMaxPitchRate();	//CSB 01/06/99	

	void	SimpleLowAlt();											  //RDH 25/05/99

	void	AirStruc::SimpleTurningFight();
	void	AirStruc::SimpleTurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget,COORDS3D	target);
	void	AirStruc::SimpleTurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target);
	void	AirStruc::SimpleTurnFightTargetNotOnNose(SWord	reqdeltahdg, SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos, ANGLES	deltapitch);

	void	SimpleWeldedWingMan();
	void	SimpleBailOut();
	void	SimpleLineAbreast();
	void	SimpleScatter();
	void	SimplePincer();
	void	SimpleMultiWave();
	void	SimpleDiveAndZoom ();
	void	SimpleLeadPursuit();
	void	SimpleLagPursuit();
	void	SimpleCircumvent();
//	void	SimpleDecoyActive();
//	void	SimpleDecoyPassive();
	void	SimpleRoundAbout();
	void	SimpleSplitManoeuvre();
	void	SimpleHeadOn ( );
	void	SimpleLineAstern();
	void SimpleShootTooEarly();
	void	SimpleLagRoll();
	void	SimpleExtensionManoeuvre();
	void	SimpleDivingSpin();
	void	SimpleReverseTurn();
	void	SimpleSelfAsBait();
	void	SimpleJink();
	void	SimpleBreakTurn();
	void	SimpleLazyTurn();
	void	SimpleBreak180();
	void	SimpleBreakLow();
	void	SimpleBreakHigh();
	void	SimpleBreak90();
	void	SimpleHiGBarrelRoll();
	void	SimplePanicTurn();
	void	SimpleUnBalancedFlight();
	void	SimpleTrackingShot();
	void	SimpleSnapShot();
	void	SimpleStayOnTail();
	Bool	SimpleTurnToHdgAndPitch();
	void	SimpleHotSideLagPursuitFight();
	Bool	SimpleSandwichManoeuvres();
	void	SimpleSustainedTurn();
	void	SimpleHighYoYo();
	void	SimpleZoom();
	void	SimpleLowYoYo ( );
	void	SimpleInterceptHigh();
	void	SimpleClimbAtSustainedTurnSpeed();
	void	SimpleMakeForFriendly();
	void	SimpleImmelmann();
	void	SimpleGainSpeed();									//RDH 27Apr98

	void	SimpleGatherSpeed ();
	void	SimpleLeadUnFriendly ();
	void	SimpleSplitS ();
	void	SimpleZoomandDrop ();
//rdh	void	SimpleDiveAndZoom ( );
	void	SimpleGainHeight ( );
	void 	SimpleTopCover ();
	void 	SimpleLookAround ();
	void 	SimpleBarrelRollAttack ( );
	void 	SimpleScissors ( );
	void 	SimpleMildScissors ( );
	void 	SimpleStraightandLevel ( );
	void 	SimpleAcmSideSlip ( );
	void 	SimpleSpinRecovery ();
	void 	SimpleSpinOut ( );
	void 	SimpleDiveforHome ( );
	void 	SimpleClimbforHome ( );
	void 	SimpleStraightDive ( );
	void 	SimpleStandOnTail ( );
	void 	SimpleShootToFrighten ( );
	void 	SimpleGoHome ( );
	void 	SimpleMoveAway ( );
	void 	SimpleAccidentalSpinOut ( );
//rdh	void 	SimpleTurningFight ();
//	void	AirStruc::SimpleTurningFight();
//	void	AirStruc::SimpleTurnFightSub(ANGLES	HdgIntercept);

	void 	SimpleLowGYoYo ( );
	void 	SimpleVerticalLoop ( );
	void	SimpleImmelmannTurn ( );
	void 	SimpleHeadOnOffset ( );
	void 	SimpleStayWithPrey ( );
	void 	SimpleTightTurn (SLong recovery_alt);
	void 	SimpleTightTurnSub (SLong recovery_alt,COORDS3D	target);
 	void	SimpleTightTurnSubSub (SWord	deltapitch);									//RDH 13Oct96
 	void	SimpleTightClimbingTurn (ANGLES);
	Bool	SimpleMoveToDesiredHdg (ANGLES,ANGLES);
	void	SimpleMoveToHdg (ANGLES);
	void	SimpleMoveToRoll (SWord);
	SWord	SimpleMoveToDesiredPitch (ANGLES,ANGLES);



//DeadCode RDH 30Mar98 	void	SelectDefendManoeuvre();
//DeadCode RDH 30Mar98 	void	SelectAttackManoeuvre();
//DeadCode RDH 30Mar98 	Bool	SelectDefendManoeuvreSub(DEFENDMANOEUVRE);
//DeadCode RDH 30Mar98 	Bool	SelectAttackManoeuvreSub(ATTACKMANOEUVRE);
	Bool	TimeToChangeToEvade ();
	Bool	WeHaveNumbersAdvantage ();
//DeadCode RDH 30Mar98 	Bool	WeHaveNumbersAndACMAdvantage ();
	Bool	DisengageAppropriate ();
	Bool	AirStruc::NoseToTail (ANGLES angle);
	void	AirStruc::SelectNextDisengageManoeuvre ();
	void	AirStruc::PanicManoeuvres();
	void	AirStruc::BanditHighManoeuvre();
	void	AirStruc::BanditLowManoeuvre();
	void	AirStruc::LowAltManoeuvre();
	Bool	AirStruc::TooLow();

	void	AirStruc::MoraleMod();

//rdh	void	AirStruc::SelectNextEngageManoeuvre ();
	Bool	AirStruc::LooseDeuceSituation();
	void	AirStruc::TakeLooseDeuceOption();
	Bool	AirStruc::TimeToChangeToDisengage ();
	SLong AirStruc::SubjectClosure();
	Bool AirStruc::SubjectClosureGreaterThan(SLong dvel);
	Bool	AirStruc::SubjectLeadingTarget();
	Bool AirStruc::TargetClosureGreaterThan(SLong dvel);
	Bool AirStruc::ClosureLessThan(SLong dvel);
	Bool AirStruc::M_LagRoll();
	Bool 	AirStruc::M_FlightSeparation();
	bool AirStruc::AboveGround(SLong height);
	void	AirStruc::ManoeuvreBasedOnClosure();
	Bool 	AirStruc::M_BarrelRoll();
	Bool 	AirStruc::M_ZoomAndDrop();
	Bool 	AirStruc::M_SpinOut();
//DeadCode RDH 07Jan99 	Bool 	AirStruc::M_SideSlip();
	Bool 	AirStruc::M_SelfAsBait();
	Bool	AirStruc::TargetHasCorrectLead(ANGLES lead, ANGLES maxlead);
	ANGLES AirStruc::ActualLead(AirStrucPtr  subjt, AirStrucPtr trgt);
	MANOEUVRE	AirStruc::ManoeuvreBasedOnSkill(SkillType skill, MANOEUVRE goodman, MANOEUVRE badman);
	Bool	AirStruc::SubjectHasEnergyAdvantage();
	Bool 	AirStruc::M_GunDefence(ANGLES lead);
	Bool 	AirStruc::M_UnSighted();
	Bool 	AirStruc::M_DiveForHome();
	Bool 	AirStruc::M_SplitS();
	Bool 	AirStruc::M_Scissors(ANGLES lead);
	Bool	AirStruc::M_ShootTooEarly();
	void	AirStruc::DefenceManoeuvre();
	Bool	AirStruc::M_ShootToFrighten();
	SLong		AirStruc::DeltaAltitude();
	void	AirStruc::AggressivePassManoeuvre();
	void	AirStruc::DefensivePassManoeuvre();
	void	AirStruc::SelectNoseToNoseManoeuvre();
	void	AirStruc::SelectNoseToTailManoeuvre();
	void AirStruc::SelectNoseToBeamManoeuvre();
	void	AirStruc::SelectBeamToNoseManoeuvre();
	void	AirStruc::SelectBeamToTailManoeuvre();
	void	AirStruc::SelectBeamToBeamManoeuvre();
	void	AirStruc::SelectTailToTailManoeuvre();
	void	AirStruc::SelectTailToBeamManoeuvre();
	void	AirStruc::SelectTailToNoseManoeuvre();
	SWord AirStruc::CornerSpeed();
	SWord AirStruc::SustainedTurnSpeed();


	Float	Model_InstTurnRate(AirStrucPtr subject);
//rdh	FP	Model_MachNo(){return 0.0;}
//	FP	Model_Speed(){return 0.0;}
public:
//DeadCode DAW 09Mar99 	bool		AcIsFlightLeader()	{return	(fly.position()==0);}
//DeadCode DAW 09Mar99 	bool		AcIsGroupLeader()	{return	(formpos==0);}
	bool		AcIsFlightLeader()	{return	((int)position()==0);}
	bool		AcIsGroupLeader()	{return	((int)formpos==0);}
	AirStrucPtr		AcIsPlayer();
	AirStrucPtr		InPlayersElement();
 	AirStrucPtr		FindBuddy();
 	AirStrucPtr		PlayerInGroup();
 	AirStrucPtr		PlayerInFlight();
 	AirStrucPtr		FindAirEscortLeader();
 	AirStrucPtr		AcCloseAttackingOneOfGroup(bool& victimfound);	  //RDH 27/06/99
 	AirStrucPtr		RemoveElement();								  //RDH 03/03/99
	AirStruc*		FindGroupLeaderInFormation();
	AirStruc*		FindGroupLeaderClose();						  //RDH 23/06/99
	AirStruc*		FindGroupLeader();								  //RDH 03/03/99
	AirStrucPtr		FindABuddyWithPlayerGivenPriority();			  //RDH 04/03/99
	AirStrucPtr		FindABuddyNotPlayer();							  //RDH 20/05/99

	AirStrucPtr		FindBandit(int& count);									  //RDH 05/03/99
	AirStrucPtr		FindAnyBandit(SLong& range, int& count);			  //RDH 08/03/99
	AirStrucPtr		FindAcInGroup();						  //RDH 05/03/99
	bool			InSameWave(AirStruc* trg);	  //RDH 04/05/99

	AirStrucPtr		FindBanditOnTail();
	void			SetGroupWP(WayPoint*	newwp);					  //RDH 09/03/99
	AirStruc*	AcShouldGoHome();									  //RDH 09/03/99
	void	AiLeaderBingoInstructions();
	void	SayEndPatrolFuel();
	void	PublicFireABullet(SWord delaybetweenbursts,Bool isArmed=TRUE); //RJS 27May99
	int	position() {return (formpos&InWingMAX);}
	void	MissionDiceThrow(WayPointPtr targetwp=NULL);



//	Existing in chat.cpp	AirStruc* FindGroupLeader(AirStruc* ac)


};

//SLong const 	MAXRPM			=	8192;



//
// Shapes: Now 2 parts to each shape... the shape data and the anim data
// There is only 1 instance of the shape data which all items share.
// There is 1 copy of the anim data for each item.
// This anim data may include weaponry records.
//

enum	ScaleType {SHP_1CM=0,SHP_4CM,SHP_16CM,SHP_GRP};			//PD 06Mar96


#endif


