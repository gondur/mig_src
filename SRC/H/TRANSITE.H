//------------------------------------------------------------------------------
//Filename       transite.h
//System         
//Author         Martin Alderton
//Date           Mon 4 Mar 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	TRANSITE_Included
#define	TRANSITE_Included

#include "worldinc.h"
#include	"AnimData.h"									//RJS 10Feb97

#include "display.h"						//PD 19Apr96
#include "myvector.h"					
#include "3dinstr.h"												//RJS 06Aug96

#define	DEFAULT_TRANSITE 0

const	int	MaxTransients = 256;								//RJS 06Apr99
const	int	MaxTrails = 128;									//RJS 06Apr99
const	int	RealMaxTransients = 128;							//DAW 06Apr99

const SWord	BOMBWEIGHT = 80;	//Newtons
enum	DeathType	{	DT_BigGround=0,							//PD 07May96
						DT_GroundSmoke,							//PD 07May96
						DT_AirDelay,							//PD 07May96
						DT_AirInstant							//PD 07May96
					};											//PD 07May96

//PD 29Apr96
const	SLong	MUZZELVEL = 6000; //about 1200 mph	//mach 2			//RDH 23Jul96
const	SLong	LIFETIME_BULLET = 100;			//Bullet life in csecs = 1/2sec//RDH 09May99
const	SLong	LIFETIME_MINIEX = 1*100;			//Mini explo life in csecs = 1sec
const	SLong	LIFETIME_BIGEXP = 5*100;			//Big explo life in csecs = 10sec//RJS 06Aug96
const	SLong	LIFETIME_ACPART = 1*30*100;						//RJS 03Dec96
const	SLong	LIFETIME_SMOKETRAIL=1*60*100;//Smoke trail life in csec
const	SLong	LIFETIME_SMOKE = 1*100;				//Smoke particle life in csecs
const	SLong	LIFETIME_GROUNDEXP = 1*45*100;//Ground explosion life in csec//RJS 22Nov96
const	SLong	LIFETIME_DEBRISLNCHR = 5*100;	//Debris chunk//RJS 21Jun96
const	SLong	LIFETIME_SMALLFIRE = 30*100;	//Small fire	//RJS 20Nov96
const	SLong	LIFETIME_TROOP = 60*100;			//Troop chap//RJS 20Nov96
const	SLong	LIFETIME_FLAK  = 100;			//Flak			//RJS 02Jul96
const	SLong	LIFETIME_PARACHUTE = 10000;		//Parachute		//RJS 02Jul96
const	SLong	LIFETIME_RICOCHET = 20;			//Ricochet		//RJS 05Jul96
const	SLong	LIFETIME_BOMB = 10000;			//Bomb			//RJS 16Aug96
const	SLong	LIFETIME_VAPOUR = 60*100;						//RJS 27May97
const	SLong	LIFETIME_ROCKET = 3000;

//DeadCode RJS 20Nov98 const	ShapeNum	MiniExplosionShape	=	SMOKE;				//RJS 06Aug96
//DeadCode RJS 20Nov98 const	ShapeNum	BigExplosionShape	=	EXPLO;				//PD 01May96
//DeadCode RJS 20Nov98 const	ShapeNum	GunfireShape		=	BULLET;				//PD 29Apr96
//DeadCode RJS 20Nov98 const	ShapeNum	SmokinShape			=	SMOKE;				//PD 30Apr96
//DeadCode RJS 20Nov98 const	ShapeNum	BigSmokeShape		=	BSMKE;				//PD 09May96
//DeadCode RJS 20Nov98 const	ShapeNum	InvisibleLauncher	=	EMPTY;				//PD 30Apr96
//DeadCode RJS 20Nov98 const	ShapeNum	GroundExplosionShape=	EXPLO;				//PD 01May96
//DeadCode RJS 20Nov98 const	ShapeNum	CraterShape			=	CRATER;				//RJS 02Jul96
//DeadCode RJS 20Nov98 const	ShapeNum	SmallFireShape		=	SMLFIR;				//RJS 09Oct96
//DeadCode RJS 20Nov98 const	ShapeNum	LargeFireShape		=	FIRE;				//RJS 09Oct96
//DeadCode RJS 20Nov98 const	ShapeNum	FlakShape			=	SMOKE;				//RJS 02Jul96
//DeadCode RJS 20Nov98 const	ShapeNum	SmallCraterShape	=	HOLE;				//RJS 10Jul96
//DeadCode RJS 20Nov98 const	ShapeNum	HugeExplosionShape	=	BEXP;				//RJS 13Aug96
//DeadCode RJS 20Nov98 const	ShapeNum	RicochetSmokeShape	=	RSMOKE;				//RJS 09Sep96
//DeadCode RJS 20Nov98 const	ShapeNum	ShockwaveShape		=	EMPTY2;				//RJS 16Oct96
//DeadCode RJS 20Nov98 const	ShapeNum	BoxShape			=	EMPTY;				//RJS 17Oct96
//DeadCode RJS 20Nov98 const	ShapeNum	BirdShape			=	EMPTY;				//RJS 17Oct96
//DeadCode RJS 20Nov98 const	ShapeNum	ChickenShape		=	EMPTY;				//RJS 17Oct96
//DeadCode RJS 20Nov98 const	ShapeNum	DustShape			=	SDUST;				//RJS 31Oct96
//DeadCode RJS 20Nov98 const	ShapeNum	GermFlakShape		=	EMPTY;				//RJS 06Nov96
//DeadCode RJS 20Nov98 const	ShapeNum	BritFlakShape		=	EMPTY;				//RJS 06Nov96
//DeadCode RJS 20Nov98 const	ShapeNum	TrenchShapeBrit		=	EMPTY;				//RJS 15Dec96
//DeadCode RJS 20Nov98 const	ShapeNum	TroopLauncherShape	=	EMPTY;				//RJS 08Nov96
//DeadCode RJS 20Nov98 const	ShapeNum	FuelBarrelShape		=	EMPTY;				//RJS 22Nov96
//DeadCode RJS 20Nov98 const	ShapeNum	TinyFireShape		=	EMPTY;				//RJS 06Dec96
//DeadCode RJS 20Nov98 const	ShapeNum	TrenchShapeGerm		=	EMPTY;				//RJS 15Dec96
//DeadCode RJS 20Nov98 const	ShapeNum	VapourShape			=	VAPSHP;				//RJS 27May97
//DeadCode RJS 20Nov98 const	ShapeNum	VapourStreamShape	=	HOLE;				//RJS 27May97
//DeadCode RJS 20Nov98 const	ShapeNum	CloneShape			=	GCLONE;				//RJS 01Oct97
//DeadCode RJS 20Nov98 const	ShapeNum	MigPuffShape		=	DUMMY2;				//RJS 09Jan98
//DeadCode RJS 20Nov98 const	ShapeNum	NapalmShape			=	DUMY10;				//RJS 22Jan98

const	SWord		TenMetresPerSec		=	103;

const	SWord		OrdinaryDrag		=	1;
const	SWord		RetardedDrag		=	5;

const	SWord		TerminalVelocity	=	0x07FFF;

const	SWord		SmokeBaseVel			=	400;			//PD 01May96
const	SWord		SmokeVariableVertVel	=	100;			//PD 01May96
const	SWord		SmokeVariableHorzVel	=	50;				//PD 01May96

const	SWord		DefaultShootDelay	=	6;//8;//15;			//25 0.25 secs//RDH 03Oct96

const	SWord		SmokeLaunchDelay	=	10;			//0.10 secs//PD 30Apr96

const	Angles		DeathAngleStep		=	ANGLES_2Deg;		//PD 02May96

//DeadCode AMM 24Jul98 typedef struct _bul_packet BULPACKET;							//ARM 12Sep96
//DeadCode AMM 24Jul98 typedef struct _bul_packet* LPBULPACKET;						//ARM 12Sep96
//DeadCode AMM 24Jul98 struct _bul_packet {											//ARM 12Sep96
//DeadCode AMM 24Jul98 					
//DeadCode AMM 24Jul98 //DeadCode AMM 08Jun98 	Bool		got1sthalf;
//DeadCode AMM 24Jul98 //DeadCode AMM 08Jun98 	UWord		PosX,PosY,PosZ;									//ARM 12Sep96
//DeadCode AMM 24Jul98 //DeadCode AMM 08Jun98 	SWord		HorzVel;										//ARM 12Sep96
//DeadCode AMM 24Jul98 //DeadCode AMM 08Jun98 	SWord		VertVel;										//ARM 12Sep96
//DeadCode AMM 24Jul98 //DeadCode AMM 08Jun98 	SWord		Head;											//ARM 12Sep96
//DeadCode AMM 24Jul98 //DeadCode AMM 08Jun98 	SLong		LaunchTime;										//ARM 12Sep96
//DeadCode AMM 24Jul98 //DeadCode AMM 08Jun98 	ShapeNum	Shape;											//ARM 12Sep96
//DeadCode AMM 24Jul98 	Bool		got1sthalf;
//DeadCode AMM 24Jul98 	SLong		PosX,PosY,PosZ;									
//DeadCode AMM 24Jul98 	SWord		HorzVel;										
//DeadCode AMM 24Jul98 	SWord		VertVel;										
//DeadCode AMM 24Jul98 	ANGLES		Head;											
//DeadCode AMM 24Jul98 	SLong		LaunchTime;										
//DeadCode AMM 24Jul98 	ShapeNum	Shape;											
//DeadCode AMM 24Jul98 };																

struct	HitEffectRecord;	//RJS 18Jan99

struct	StatTrailItem											//RJS 13May99
{
	TransientItemPtr	item;
	ULong				time;

	StatTrailItem()
	{
		item = NULL;
		time = 0xFFFFFFFF;
	}
};

class	ViewPoint;
class TransObj
{

TransientItemPtr	TransToGoList;

int	transientcounter;											//PD 24Jul96
int	trailcounter;												//RJS 06Apr99

SWord	shootdelay;												//PD 29Apr96
SWord	fakeshootdelay;											//RJS 21Apr98

struct	Area
{
	SLong	botx, botz;
	SLong	topx, topz;
};																//RJS 02Jul96

Area	trooparea;												//RJS 02Jul96

UByte	vapourcount;

enum	WeapSearchType											//RJS 10Jun97
{
	Go_Forward = 0,
	Go_Backward,												//RJS 09Sep98
	Go_Instant													//RJS 09Sep98
};

private:
void KillOldest();												//PD 24Jul96

TransientItemPtr TransObj::DeleteTransientItem(TransientItemPtr );		//MGA 22Feb96
TransientItemPtr TransObj::DeleteTempTransientItem(TransientItemPtr );//MGA 25Mar96
int  TransObj::FindInTransientList(TransientItemPtr);						//MGA 29Feb96
int  TransObj::CountTheTransients(TransientItemPtr );									//MGA 27Feb96
int  TransObj::CountTheDeadTransients(TransientItemPtr );									//MGA 27Feb96
int  TransObj::GetRand(void);

TransientItemPtr TransObj::InitTransientItem(MobileItemPtr,itemptr,itemptr,UNIQUE_ID,int );//MGA 22Feb96
// I don't now see where this procedure will be used			//MGA 29Feb96

	bool	HitTheDeck;											//RDH 09May99


public:	
	MobileItem* View_Point;
	ViewPoint* View_Object;

	SLong	autobulletcount;									//PD 29Apr96
	SLong	uiddeathitem;										//PD 03May96
	SLong	deathtype;											//PD 03May96
	UByte	CloudTotal;											//RJS 09Jul97
	SWord	CloudTimer;											//RJS 09Jul97
	SWord	GScatterCnt;										//RJS 21Oct97
	SWord	GScatterTimer;										//RJS 21Oct97

	StatTrailItem		StaticTrailList[MaxTrails];				//RJS 13May99
	SWord				StaticTrailCnt;							//RJS 18Feb99
	SWord				StaticTrailIndex;						//RJS 18Feb99

	SWord				realFrameTime;							//RJS 27May99

TransObj(void );
~TransObj();

	void	SetViewPoint(MobileItem* vp,ViewPoint* vo);
	void	PilotedACHit();										//PD 02Sep96
//DeadCode AMM 28Apr99 	void	CommsACHit (AirStrucPtr, itemptr);					//AMM 17Mar97
	void	GAndFriction(mobileitem*,SWord dragfactor,SWord dragfacy = 0);				//RJS 04Jul96
	void	ControlKeybWeap(AirStrucPtr, WorldStuff&);			//PD 29Apr96
	void	TestForItem2Kill(WorldStuff& );						//PD 07May96
	void	GAndFrictionFixedPitch(mobileitem*,SWord dragfactor,SWord dragfacy = 0);//RJS 29May98
	void	NoGravityAndFriction(mobileitem*,SWord dragfactor=0);//RJS 18Jun98

	void	LaunchExplosion(mobileitem*, WorldStuff&, int strength = 0);//RJS 22Jan98
void TransObj::LaunchDummyExplosion(mobileitem);									//MGA 29Feb96
void TransObj::LaunchDitchEffect(mobileitem, WorldStuff& );								//MGA 01Mar96
//DeadCode AMM 01Jun98 void TransObj::LaunchCrater(mobileitem*, WorldStuff& );			//RJS 25Jun96
void TransObj::LaunchCrater(mobileitem*, WorldStuff&);									//RJS 19Nov98
//DeadCode PD 26Apr96 void TransObj::LaunchBullet(mobileitem&, WorldStuff& );				//MGA 21Mar96
//Old_Code PD 29Apr96 void TransObj::LaunchDeadACPart(AirStruc&,BitFlags,WorldStuff& );//PD 19Apr96
 	void	LaunchDeadACPart(AirStruc*,BitFlags,WorldStuff&,Bool blowup=FALSE );//RJS 20Feb97

	void	LaunchBitsOffPart(ItemPtr,UByteP,WorldStuff&,UByte,UByteP,UWord blowup=0,Bool noFlash=FALSE);//RJS 15Sep98
	void	LaunchSmokeTrail(mobileitem*, WorldStuff&);			//PD 30Apr96
	void	LaunchGroundExplosion(mobileitem*, WorldStuff&);	//PD 01May96
	void	SeenFlak(TransientItemPtr transit);

void MobilePuffTravel(TransientItemPtr transit,WorldStuff& world);//JIM 24Sep96
void MobileFlare(TransientItemPtr,WorldStuff&);					//RJS 17May99
void MobileExplosion(TransientItemPtr,WorldStuff&);				//PD 26Apr96
void MobileSink(TransientItemPtr,WorldStuff&);					//RJS 13May99
void MobileCarpetStrike(TransientItemPtr,WorldStuff&);			//RJS 31May99
void MobileCrater(TransientItemPtr,WorldStuff&);				//PD 26Apr96
void MobileBullet(TransientItemPtr, WorldStuff&);				//PD 26Apr96
void MobileSmokeTrail(TransientItemPtr, WorldStuff&);			//PD 30Apr96
void MobileDeadACPart(TransientItemPtr,WorldStuff& );			//PD 26Apr96
void MobileGAndF(TransientItemPtr,WorldStuff& );				//PD 30Apr96
void MobileGroundExp(TransientItemPtr,WorldStuff& );			//PD 01May96
void MobileGroundDebris(TransientItemPtr, WorldStuff&);			//RJS 21Jun96
void MobileFire(TransientItemPtr, WorldStuff&);					//RJS 01Jul96
void MobileTroop(TransientItemPtr, WorldStuff&);				//RJS 01Jul96
void MobileParachute(TransientItemPtr, WorldStuff&);			//RJS 02Jul96
void MobileBarage(TransientItemPtr, WorldStuff&);				//RJS 02Jul96
void MobileDelayedExplosion(TransientItemPtr, WorldStuff&);		//RJS 02Jul96
void MobileFlak(TransientItemPtr, WorldStuff&);					//RJS 02Jul96
void MobileRicochet(TransientItemPtr, WorldStuff&);				//RJS 05Jul96
void MobileGuidedExplosion(TransientItemPtr, WorldStuff&);		//RJS 08Jul96
void MobileGuidedBurning(TransientItemPtr, WorldStuff&);		//RJS 08Jul96
void MobileGuidedFire(TransientItemPtr, WorldStuff&);			//RJS 09Jul96
void MobileATeam(TransientItemPtr, WorldStuff&);				//RJS 10Jul96
void MobileBombDrop(TransientItemPtr, WorldStuff&);				//RJS 24Jul96
void MobileDustRing(TransientItemPtr, WorldStuff&);				//RJS 13Oct96
void MobileBigExplosion(TransientItemPtr, WorldStuff&);			//RJS 13Aug96
void MobileMovingSmoke(TransientItemPtr, WorldStuff&);			//RJS 02Sep96
void MobileRicochetSmoke(TransientItemPtr, WorldStuff&);		//RJS 05Sep96
void MobileShockwave(TransientItemPtr, WorldStuff&);			//RJS 16Oct96
void MobileBird(TransientItemPtr, WorldStuff&);					//RJS 17Oct96
void MobileAmmoBoxes(TransientItemPtr, WorldStuff&);			//RJS 17Oct96
void MobileDummyBomb(TransientItemPtr, WorldStuff&);			//RJS 01Apr99
void MobileVapourTransient(TransientItemPtr, WorldStuff&);		//RJS 27May97
void MobileRocket(TransientItemPtr, WorldStuff&);				//RJS 04Jun97
void MobileCloneGun(TransientItemPtr, WorldStuff&);				//RJS 01Oct97
void MobileTimerExplosion(TransientItemPtr, WorldStuff&);		//RJS 22Jan98
void MobileNapalm(TransientItemPtr, WorldStuff&);				//RJS 22Jan98
void MobileDoDamage(TransientItemPtr, WorldStuff&);				//RJS 18Feb98
void MobileThuggery(TransientItemPtr, WorldStuff&);				//RJS 02Mar98
void MobileSmallThug(TransientItemPtr, WorldStuff&);			//RJS 03Dec98
void MobileFuelDrop(TransientItemPtr, WorldStuff&);				//RJS 28May98
void MobileDeadBridge(TransientItemPtr, WorldStuff&);			//RJS 30Oct98
void MobileCollapse(TransientItemPtr, WorldStuff&);				//RJS 18Nov98
void MobileSparkTrail(TransientItemPtr, WorldStuff&);			//RJS 11Dec98
void MobileCanopy(TransientItemPtr, WorldStuff&);				//RJS 23Mar99

void TransObj::RemoveDeadListFromWorld();								//MGA 27Feb96
void TransObj::RemoveDeadListFromWorld(WorldStuff& )			//JIM 11Nov96
		{RemoveDeadListFromWorld();}							//JIM 11Nov96
void TransObj::DeleteAll();										//PD 11May96
void TransObj::AddTransientItemToWorld(TransientItemPtr, WorldStuff& );				//MGA 27Feb96
void TransObj::AddTransientItemToDeadList(TransientItemPtr, bool novapour=false);//DAW 19May99

	void	GeneralAircraftDammage(AirStruc*,WorldStuff&,Bool	blowup=FALSE,itemptr hitter= NULL);//ARM 02Dec96
//TempCode RJS 18Feb97 	void	SetAircraftDammage(AirStruc*,WorldStuff&,UByteP,BitStates,Bool,Bool nomovecode=FALSE,Bool	blowup=FALSE,Bool sendpacket = FALSE);//RJS 13Feb97
	void	SetAircraftDammage(AirStruc*,WorldStuff&,BitFlags,BitStates,Bool,Bool nomovecode=FALSE,Bool	blowup=FALSE,Bool sendpacket = FALSE);//RJS 13Feb97
	void	DirectAircraftDamage(AirStruc*,WorldStuff&,BitStates,BitFlags);//ARM 08Oct96

	TransientItem*	LaunchOneGunBullet(mobileitem* ,SLong,ShapeNum,SLong, SLong, SLong, WorldStuff&,SWord theangle=0);//RJS 26May98
//DeadCode AMM 24Jul98 	TransientItem*	LaunchCommsBullet(AirStrucPtr, struct _bul_packet);//ARM 06Sep96
	TransientItem*	LaunchRearGunBullet(mobileitem* ,ShapeNum,SLong, SLong, SLong, WorldStuff&);//RJS 11Oct96

	SWord	DropOneBomb(mobileitem*,WorldStuff&);							//RDH 23Sep96
	void	PlayGunSound(mobileitem* ,WorldStuff&);				//RDH 18Jul96
	void	LaunchMiniExplosion(mobileitem*, WorldStuff&);		//PD 29Apr96
	void	LaunchDebris(mobileitem*,ShapeNum,SLong,SLong,WorldStuff&,Bool nospin=FALSE);//RJS 20Nov98
	void	LaunchFire(mobileitem*, WorldStuff&);				//RJS 01Jul96
	void	LaunchTroops(item*, ShapeNum,Coords3D, WorldStuff&,SByte	maxtroops=-1);//RJS 07Dec98
	void	LaunchParachute(mobileitem*, WorldStuff&);			//RJS 02Jul96
	void	LaunchBarage(mobileitem*, SLong);					//RJS 05Oct98
	void	LaunchDelayedExplosion(mobileitem*, WorldStuff&);	//RJS 02Jul96
	void	LaunchFlak(mobileitem*, WorldStuff&);				//RJS 02Jul96
	void	LaunchRicochet(mobileitem*, WorldStuff&);			//RJS 05Jul96
	void	LaunchGuidedExplosion(mobileitem*, WorldStuff&);	//RJS 08Jul96
	void	LaunchGuidedBurning(mobileitem*, WorldStuff&);		//RJS 08Jul96
	void	LaunchGuidedFire(mobileitem*,WorldStuff&);			//RJS 09Jul96
	void	LaunchSpark(mobileitem*,WorldStuff&);				//RJS 24Jul96
	void	LaunchBombDrop(mobileitem*,ShapeNum,SLong, SLong, SLong,WorldStuff&,Bool	duff=FALSE);//RJS 11Jun97
	UWord	LaunchVapourStream(UByteP,ShapeNum,SWord velh=0,SWord vely=0,SWord resistance=100,UByteP smkptr=NULL);//RJS 09Apr98
	void	GeneralItemDamage(mobileitem*,mobileitem*,WorldStuff&,SByte,Bool accollision=FALSE);//RJS 10Oct96
	void	AcDamageEffects(AirStruc*,BitFlags,BitStates,WorldStuff&);	//RJS 02Aug96
	void	LaunchBigExplosion(mobileitem*,WorldStuff&,ShapeNum	groundshape=(ShapeNum)0);//RJS 08Nov96
	void	LaunchSparkDebris(mobileitem*, WorldStuff&);			//RJS 13Aug96
	void	LaunchSkinDebris(mobileitem*, WorldStuff&);//RJS 14Aug96
	void	LaunchRealShockwave(mobileitem*,UByte,WorldStuff&);	//RJS 30Nov98
	void	LaunchRicochetSmoke(mobileitem*,ShapeNum,WorldStuff&);		//RJS 26Apr99
	void	LaunchDustRing(mobileitem*, WorldStuff&);			//RJS 13Oct96
	void	LaunchShockwave(mobileitem*, WorldStuff&);			//RJS 16Oct96
	void	LaunchBirds(mobileitem*, ShapeNum, WorldStuff&);	//RJS 17Oct96
	void	LaunchIgniteAmmoBoxes(mobileitem*,UByte, WorldStuff&);//RJS 20Nov98
	void	LaunchDustTrail(mobileitem*, WorldStuff&, SByte distance=-1);//RJS 13Nov96
	void	LaunchMushroomCloud(mobileitem*,SLong,WorldStuff&);	//RJS 07Dec98
	void	LaunchSmokePuff(mobileitem*,ShapeNum,SLong, SLong, SLong, WorldStuff&);//RJS 12Jun98
	void	LaunchSmoulder(mobileitem*, WorldStuff&, Bool	uselch=FALSE);//RJS 09Dec96
	void	LaunchFuelBarrels(mobileitem*, WorldStuff&);		//RJS 22Nov96
	void	DropAllStores(mobileitem*,WorldStuff&);				//RJS 27May98
	void	LaunchScatteredFire(mobileitem*, ShapeNum, WorldStuff&);//RJS 06Dec96
	void	AddWindDrift(item* );								//RJS 07Jan97
	void	ExecuteAnimation(ItemPtr,ItemPtr,UWord,Coords3D,WorldStuff&,SLong,SLong,UByteP,Coords3D,Coords3D,SLong,SByte groupindex=0);//JIM 11Mar99
	Bool	LaunchVapourTransient(mobileitem*,SLong,SLong,SLong,int,int,WorldStuff&,ShapeNum);//RJS 03Dec97
	TransientItem* LaunchRocket(mobileitem*,ShapeNum,SLong, SLong, SLong, WorldStuff&);//RJS 03Jun97
	TransientItem* LaunchFuelDrop(mobileitem*,ShapeNum,WeapAnimData*,SLong,SLong,SLong,WorldStuff&);//RJS 11Jun97
//DeadCode AMM 09Apr99 	void	LaunchWeapon(AirStrucPtr,WeapAnimData*,SLong,SLong,SLong,WorldStuff&,SLong,SLong,Bool unarmed=FALSE);//RJS 23Jul98
	SLong	LaunchWeapon(bool received,AirStrucPtr,WeapAnimData*,SLong,SLong,SLong,WorldStuff&,SLong,SLong,Bool unarmed=FALSE);//RJS 11Jun99
	SLong	ActivateStation(AirStrucPtr,UWord&,UWord&,WorldStuff&);//RJS 17Jun99
	void	WeaponSearch(AirStrucPtr, WeapSearchType direction=Go_Instant, Bool wrap = FALSE);//RJS 13May99
	Bool	DumpFuel(AirStrucPtr, WorldStuff&,Bool byaccident=FALSE);//RJS 03Jun99
	void	DumpWeapons(AirStrucPtr, WorldStuff&);				//RJS 11Jun97
	void	ReloadWeapons(AirStrucPtr);							//RJS 11Jun97
	void	LaunchTrailTail(mobileitem*,SLong,SLong,SLong,ShapeNum,WorldStuff&);//RJS 16Jun97
	void	LaunchClouds();										//RJS 09Jul97
	void	LaunchCloneGun(mobileitem*,mobileitem*,Nationality,SWord,SWord,SWord,SWord,SWord,WorldStuff&);//RJS 08Sep98
//DeadCode RJS 19Feb98 	void	LaunchGroundScatter();								//RJS 21Oct97
	void	LaunchGunPuff(mobileitem*,SLong,SLong,SLong,WorldStuff&);//RJS 05Jan98
	void	LaunchDustTrail2(mobileitem*, WorldStuff&);			//RJS 08Jan98
	void	LaunchNapalmStrike(mobileitem*, WorldStuff&);		//RJS 22Jan98
	void	LaunchCanopyEject(mobileitem*, WorldStuff&);		//RJS 19Feb98
//DeadCode AMM 05Jul99 	void	LaunchGroupThug(item*,ShapeNum,int,int,int,Coords3D,Coords3D,UWord,UWord);//RJS 17Nov98
	void	LaunchGroupThug(item*,ShapeNum,int,int,int,Coords3D,Coords3D,UWord,UWord,ItemPtr);//AMM 05Jul99
//DeadCode RJS 03Dec98 	void	LaunchTrackedBullet(mobileitem*, WorldStuff&);		//RJS 21Apr98
	void	LaunchSmokeCloud(mobileitem*,ShapeNum,Coords3D,WorldStuff&);//RJS 03Jul98
	TransientItem*	LaunchManyGunBullets(mobileitem*,SLong,SWord,SWord,SWord,SWord,ShapeNum,SLong,SLong,SLong,WorldStuff&,SWord,SLong,Bool isArmed=TRUE);//RJS 27May99
	void	LaunchDirtSmall(mobileitem*, WorldStuff&,bool dosound=true);//RJS 21Aug98
	void	LaunchDirtMedium(mobileitem*, WorldStuff&);			//RJS 21Aug98
	void	LaunchDirtLarge(mobileitem*, WorldStuff&);			//RJS 21Aug98
	void	LaunchSplashSmall(mobileitem*, WorldStuff&);		//RJS 21Aug98
	void	LaunchSplashMedium(mobileitem*, WorldStuff&);		//RJS 21Aug98
	void	LaunchSplashLarge(mobileitem*, WorldStuff&);		//RJS 21Aug98
	void	LaunchDustRingBig(mobileitem*, WorldStuff&);		//RJS 21Aug98
	void	DoImpactGround(ItemPtr,Coords3D,UByte);				//MS 30Nov98
	void	LandedEffect(AirStrucPtr,SLong,Bool send=TRUE,Bool musthit=FALSE);//RJS 15Jan99
	void	LaunchBubbles(mobileitem*,SLong,WorldStuff&);		//RJS 24Aug98
	void	LaunchWaterTrail(mobileitem*,WorldStuff&);			//RJS 24Aug98
	void	LaunchFingers(mobileitem*,WorldStuff&);				//DAW 03Sep98
	void	LaunchSmokePuff2(mobileitem*,Coords3D*,ShapeNum,UWord,SLong,SLong,SWord,SLong,SLong,WorldStuff&);//RJS 12Nov98
	SLong	ReActivateStation(AirStrucPtr,UWord&,UWord&,UWord&,WorldStuff&,Bool isUnarmed=FALSE);//RJS 01Apr99
	void	LaunchBridgeElement(ItemPtr,Coords3D&,SWord,WorldStuff&);//RJS 26Feb99
	void	LaunchDirtyFingers(mobileitem*, WorldStuff&);		//RJS 05Nov98
	void	LaunchFlash(mobileitem*,UByte, WorldStuff&);		//RJS 10Nov98
	void	LaunchFingersFire(mobileitem*,WorldStuff&);			//RJS 12Nov98
	void	LaunchTossedShape(mobileitem*,SByte,Coords3D,SLong,WorldStuff&);//RJS 07Dec98
	void	LaunchDirtyBuildingFingers(mobileitem*,UWord,WorldStuff&);//RJS 30Nov98
	void	LaunchSmallThug(item*,item*,ShapeNum,SLong,SLong);	//RJS 03Dec98
	void	LaunchGunDot(mobileitem*,WorldStuff&);				//RJS 07Dec98
	void	LaunchSmallFlash(mobileitem*,WorldStuff&,Bool heightfix=TRUE);//RJS 05May99
	void	LaunchTransientTrail(mobileitem*,ShapeNum,SLong,Bool,WorldStuff&,SLong,Bool onGround=FALSE);//RJS 16May99
	void	LaunchJunk(mobileitem*,ShapeNum,Coords3D&,WorldStuff&);//RJS 15Jan99
	void	ExecuteAnimation(ItemPtr,UWord,ItemPtr,HitEffectRecord&,WorldStuff&);//RJS 18Jan99
	void	LaunchTimeBomb(ItemPtr,ULong,WorldStuff&);
	void	MobileScaleFist(TransientItemPtr,WorldStuff&);
	void	LaunchNapalmImpacted(mobileitem*,WorldStuff&);		//RJS 19Feb99
	void	LaunchCollapse(ItemPtr,Coords3D&,SWord,WorldStuff&);//RJS 25Mar99
	void	LaunchAmmoBoxes(mobileitem*,UByte gindex,Coords3D&,SLong,WorldStuff&);//RJS 26Apr99
	void	LaunchBoatSink(ItemPtr,Coords3D&,SWord,WorldStuff&);//RJS 13May99
	void	LaunchFakeDelayedExplosion(mobileitem*,WorldStuff&);//RJS 16May99
	void	LaunchCarpetStrike(mobileitem*,WorldStuff&);		//RJS 31May99
	void	PointBlokes(ItemPtr,ShapeNum,Coords3D&,SLong,Coords3D*,SLong);//RJS 01Jun99
	void	ReduceBulkStores(AirStrucPtr,UByteP);				//RJS 17Jun99
	void	LaunchReplayWeapon(UByteP);							//AMM 23Jun99
	void	LaunchSnapFlash(mobileitem*,WorldStuff&);			//RJS 29Jun99
	void	LaunchDirtSpark(mobileitem*,WorldStuff&,bool dosound=true);			//RJS 06Jul99



	TransientItemPtr	LaunchUnguidedMissile(mobileitem*,ShapeNum,SLong,AutoMoveCodeTypeSelect,Bool inheritanimdata=FALSE);//RJS 13Jul98
	TransientItemPtr	LaunchUnguidedMissile
								(	item* launcher,
									ShapeNum shape,
									SLong lifetime,
									AutoMoveCodeTypeSelect	movecode,
									Coords3D	&xyz,
									ANGLES		hdg, ANGLES		pitch,
									SWord		velx,SWord		vely,SWord		velz,
									SWord		velh,SWord		vel,
									Nationality nat
									);
	TransientItemPtr	LaunchSuperLauncher
								(	item*,
									ShapeNum,
									SLong,
									AutoMoveCodeTypeSelect,
									Coords3D&,
									ANGLES, ANGLES,
									SWord,SWord,SWord,
									SWord,SWord,
									Nationality,
									SWord,SWord,SWord,SWord,SWord,	//RJS 08Sep98
									WorldStuff&,				//RJS 27May99
									Bool	isArmed = TRUE		//RJS 27May99
									);

	void	ChooseMusic(AirStrucPtr	ac);					  //RDH 02/03/99
	void	KillLauncher(itemptr,ItemPtr,WorldStuff&,SByte	gindex=-1,Coords3D*	hitvector=NULL,Bool	airtoair=FALSE);//JIM 11Mar99
	void	DummyLandedEffect(AirStrucPtr,SLong,UByte atype);
	void	TwatWithWeapon(ItemPtr,ShapeNum,SByte,WorldStuff&);	//RJS 09Nov98
	void	ExplodeAC(AirStrucPtr,ItemPtr,WorldStuff&,Bool setdamage=TRUE);//JIM 11Mar99
	void	KillLauncherComms(AirStrucPtr);						//AMM 08Jan99
	void	ScanTrailListAndSave();								//RJS 18Feb99
	void	RemoveTransientItemFromTrailList(TransientItemPtr);	//RJS 18Feb99
	void	CleanUpTrailList();									//RJS 18Feb99
	void	AddTransientItemToTrailList(TransientItemPtr);		//RJS 18Feb99
	void	LaunchReplayTrail(Coords3D&,UByteP,UByteP);//RJS 18Feb99
	SLong	GetGroundLevel(ItemBase*);							//RJS 14Apr99
	SLong	GetGroundLevel(ItemBase*,UByte&);					//RJS 28Apr99
	Bool	WithinVisibleRange(Coords3D&,SLong);				//RJS 30Apr99

	Bool	KillOldestTrail(ItemPtr);							//RJS 13May99

private:
	TransientItemPtr	LaunchGuidedMissile(mobileitem*,itemptr,ShapeNum,SLong,AutoMoveCodeTypeSelect);//PD 29Apr96
	TransientItemPtr	SimplifiedSpriteLaunch(Item*,ShapeNum,SLong,AutoMoveCodeTypeSelect);//PD 29Apr96
	TransientItemPtr	RelativeSpriteLaunch(Item*,ShapeNum,ShapeNum,SLong,AutoMoveCodeTypeSelect);//RJS 27Nov98

	void	MissileHitSomething(itemptr,TransientItemPtr,WorldStuff&,SByte);//RJS 02Oct96

	void	ApplyVelocities(mobileitem* );						//PD 29Apr96
};

extern TransObj Trans_Obj;

#endif
