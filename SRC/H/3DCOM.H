//------------------------------------------------------------------------------
//Filename       3dcom.h
//System         
//Author         Paul.   
//Date           Fri 22 Sep 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	D3DCOM_Included
#define	D3DCOM_Included
#include    "dosdefs.h"
#include	"3ddefs.h"
#include	"3dinstr.h"
#include	"animdata.h"
#define	DEFAULT_D3DCOM 0

const	SLong	MAX_DOPOINTS	= 512;							//PD 15Apr96
class	Window;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//				      STRUCTURE/CLASS/TYPE DEFINITIONS
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

#ifndef	NDEBUG

#define AFX_CDECL __cdecl
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR LPCTSTR;
void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);

#endif


//DeadCode PD 15Mar96 const	SWord	shapecodeframetime = 10;						//PD 08Mar96
class	ViewPoint;
class	shape;
struct	DoPointStruc;

#define	MaxColLogs	64											//RJS 07Jul98
const SLong	specMax	=	95;

enum	ContactType	{ CT_Leftwing=0,CT_RightWing,CT_Nose,CT_Tail,CT_Wheel };//PD 11Sep96

enum	AnimFlags												//PD 27Mar96
		{
		MINANIMFLAG = 0,
		ITEMSTATE = MINANIMFLAG,
		IMAGEMAPTAIL,
		IMAGEMAPBTMWING,
		IMAGEMAPFUSELAGE,
		IMAGEMAPOTHER,
		IMAGEMAPTOPWING,
		IMAGEMAPEMBLEM,
		SCARFFLAG,												//PD 15Apr96
		EXPLODEFRAME,											//PD 15Apr96
		MUZZLEFRAME,											//PD 15Apr96
		ACBITSFLAGS,											//PD 17Apr96
		ACBITSFLAGS2,											//PD 17Apr96
		ACAILERON,												//PD 19Apr96
		ACELEVATOR,												//PD 19Apr96
		ACRUDDER,												//PD 19Apr96

		//Cockpit instrumentation animations

		RPMDIAL,												//PD 29Apr96
		VELDIAL,												//PD 29Apr96
		ALTDIAL,												//PD 29Apr96
		COMPASS,												//PD 29Apr96
		LSWITCH,												//PD 29Apr96
		RSWITCH,												//PD 29Apr96

		ACAILERONR,												//RJS 19Jun96
		WINDSOCK,												//RJS 12Aug96
		TROOPFRAME,												//RJS 18Oct96
		MAXANIMFLAG
		};

//PD 15Jan96
struct	bvert
{
	SWord	number,image_x,image_y;
};

typedef struct SPHTREETYPE										//RJS 09Jul98
{																//RJS 09Jul98
	UByte		vertex;											//RJS 09Jul98
	SPHTREETYPE	*left;											//RJS 09Jul98
	SPHTREETYPE	*right;											//RJS 09Jul98
}SphTreeType, *SphTreeTypeP;									//RJS 09Jul98

struct	ColLogStuff												//RJS 07Jul98
{
	ItemPtr	theShooter;												  //JIM 11/03/99
	ItemPtr	item;
	UWord	coloffset;
	UWord	coltype;
	UWord	colstrength;
	SWord	grpel;												//RJS 17Sep98
	UByte	send;												//AMM 31Aug98
	UWord	shapehit;											//AMM 26Nov98
};																//RJS 07Jul98

struct	ReplayAnimOffsets										//RJS 07Jul98
{
	UWord	deltaoffset;
	UByte	newbyte;
};																//RJS 07Jul98

struct	bumpmapdata
{
	ImageMapNumber	image,		//Image map number
					bump;		//bump map data number

	SLong	vertexcount;		//No of vertices used (should always be 4
								//by the time DrawBumpPoly is reached )

	bvert	vertexlist[4];		//image coordinate store
};

typedef	struct bumpmapdata BumpMapData,*BumpMapDataP;

typedef struct	MYGROUNDVECTOR
{
	SLong	gx,gy,gz;
} MyGroundVector, *MyGroundVectorPtr;							//RJS 21Nov96

typedef struct	VAPANIMDAT										//RJS 18Sep97
{																//RJS 18Sep97
	UWord	depth:8,											//RJS 15Apr98
			frameno:7,											//RJS 15Apr98
			drawit:1;											//RJS 15Apr98
} VapAnimDat, *VapAnimDatPtr;									//RJS 30Mar98

struct	Coords3DList											//RJS 21Apr99
{																//RJS 17Sep97
	MyGroundVector	trailpoint;									//RJS 17Sep97
	ULong			lifeleft:18,								//RJS 15Apr98
					radius:14;									//RJS 15Apr98
	ULong			LifeTime:18,								//RJS 24Nov98
					FadeTime:13,								//RJS 17Feb99
					KillMe:1;									//RJS 17Feb99
	SWord			xdelta;										//RJS 17Sep97
	SWord			ydelta;										//RJS 17Sep97
																//RJS 17Sep97
	Coords3DList*	next;										//RJS 21Apr99

public:															//RJS 21Apr99

	void	Wipe();
//	{
//		Coords3DList*	apoint = this;
//		Coords3DList*	tmpptr;
//		while (apoint)
//		{
//			tmpptr = apoint->next;
//			delete apoint;
//			apoint = tmpptr;
//		}
//	}
};																//RJS 21Apr99

typedef struct	TRAILRECORD										//RJS 17Sep97
{																//RJS 17Sep97
 	Coords3DList*	thelist;									//RJS 17Sep97
	UWord			bitshift:4,									//RJS 17Sep97
					transient:1,								//RJS 22Jan99
					nopoints:11;								//RJS 17Sep97
 	ULong			lifetime;									//RJS 14Apr98
	SLong			lastwx,										//RJS 17Sep97
					lastwy,										//RJS 17Sep97
					lastwz;										//RJS 17Sep97
	UByte			nextlist:7,									//RJS 16Jun99
					beendrawn:1;								//RJS 16Jun99
	SWord			LaunchCountdown;							//RJS 24Nov97
	SWord			SampleTime;									//RJS 08Jan98
	Coords3DList*	FakePointPtr;								//RJS 25Feb98
//DeadCode RJS 06May99 	SWord			InitVelY;
//DeadCode RJS 06May99 	SWord			InitVelH;
//DeadCode RJS 06May99 	SWord			Acceleration;
	UByteP			SmkDescPtr;									//RJS 09Apr98
	Bool			cloudlaunched;								//RJS 03Jul98
	ULong			currTime;									//RJS 16Jun99
} TrailRecord, *TrailRecordPtr;									//RJS 17Sep97

enum	ProbeRequest											//AMM 26Mar99
{																//AMM 26Mar99
	PROBER_KILL = 0,											//AMM 26Mar99
	PROBER_DEGRADE												//AMM 26Mar99
};																//AMM 26Mar99

struct	probeinfo
{
	ProbeRequest	action;
	SWord			index;
	TransientItem*	itm;
};

#define		MAX_VAPOURS	32										//RJS 10Mar98
#define		REAL_MAX_VAPOURS	33								//RJS 21Jan99
class	ViewPoint;
//DeadCode PD 17Oct96 typedef	void (shape::*CMFI)	(UByte *&);

class	shape
{

 			typedef	void InterpProc (UByte*& );					//PD 17Oct96

			friend	class		DeadStream;
			static 	UByteP		animflags;						//PD 17Oct96

			UByteP				shape_ptr,
								draw_data;

			static SLong		fade_start,						//PD 17Oct96
								fade_end,
								object_dist;

//DeadCode PD 10Jan97 			static MATRIX_PTR 	object_matrix;					//PD 17Oct96
			static FPMATRIX_PTR fpobject_matrix;				//PD 08Jan97
			static Obj3DPtr	  	object_obj3d;					//PD 17Oct96
			static FPMATRIX_PTR fprealobject_matrix;			//RJS 15Jan99

			static Window*		current_screen;					//PD 17Oct96
			static Colour		colour;							//PD 17Oct96
			static ColourRange	range;							//PD 17Oct96
			static ImageMapNumber	image;						//PD 17Oct96

			static SWord 		shapescale,
								AnimWeaponPack;					//RJS 11May98
			static Bool			ClearMorph;						//RJS 12Mar98

			//Animation frame time variables

			static struct GlobalAnimTime						//PD 17Oct96
			{
				SLong	centisec,		//Continuous 100th second counter
						tnthssec,		//   "  "     10th second counter
						secs;			//   "  "      1   second counter
			}
			globalanimtime;

			static UWord andedFlags;
			static UWord oredFlags;
			static SWord polyVertCount;
			static DoPointStruc* polyVertIndex[64];
			static bool specularEnabled;
//DeadCode RJS 21Nov96  			struct	myvector
//DeadCode RJS 21Nov96  			{
//DeadCode RJS 21Nov96  				SLong	gx,gy,gz;
//DeadCode RJS 21Nov96  			};

//DeadCode RJS 17Sep97 			typedef	struct	COORDS3DLIST
//DeadCode RJS 17Sep97 			{
//DeadCode RJS 17Sep97 				MyGroundVector	trailpoint;						//RJS 21Nov96
//DeadCode RJS 17Sep97 				SWord			lifetime;						//RJS 16May97
//DeadCode RJS 17Sep97 				ULong			bornat;							//RJS 02Jun97
//DeadCode RJS 17Sep97 				UWord			radius:11,						//RJS 17Sep97
//DeadCode RJS 17Sep97 								frameno:3,						//RJS 17Sep97
//DeadCode RJS 17Sep97 								depth:2;						//RJS 17Sep97
//DeadCode RJS 17Sep97 				COORDS3DLIST*	next;							//RJS 21May97
//DeadCode RJS 17Sep97 			} Coords3DList, *Coords3DListPtr;					//RJS 19Sep96
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97  			typedef struct	TRAILRECORD
//DeadCode RJS 17Sep97  			{
//DeadCode RJS 17Sep97  				Coords3DListPtr	thelist;
//DeadCode RJS 17Sep97 				SWord			addtime;						//RJS 30May97
//DeadCode RJS 17Sep97 				UWord			bitshift:5,						//RJS 30May97
//DeadCode RJS 17Sep97 								nopoints:11;					//RJS 30May97
//DeadCode RJS 17Sep97 				UWord			lifetime;						//RJS 30May97
//DeadCode RJS 17Sep97 				SLong			lastwx,							//RJS 21May97
//DeadCode RJS 17Sep97 								lastwy,							//RJS 21May97
//DeadCode RJS 17Sep97 								lastwz;							//RJS 21May97
//DeadCode RJS 17Sep97 				UByte			nextlist:7,						//RJS 30May97
//DeadCode RJS 17Sep97 								beendrawn:1;					//RJS 30May97
//DeadCode RJS 17Sep97  			} TrailRecord;										//RJS 20Sep96

			static	TrailRecord		traillist[REAL_MAX_VAPOURS];//RJS 21Jan99

			static	UByte	lastdamage[8];						//RJS 23Feb98
			static	UByte	laststationdamage[8];				//RJS 06Apr98
			static	UByteP	lastdamptr;						//RJS 18Feb97

			static	UWord	HitThisOffset;						//RJS 24Nov98
			static	Bool	CommsDamage;						//RJS 15May97
			static	Bool	VapourCyl;							//RJS 15May97

			static	DoPointStruc	CylPnt1;					//RJS 14May97
			static	DoPointStruc	CylPnt2;					//RJS 14May97

			static	UByte	VapourAnim;							//RJS 20May97
			static	Bool	IsSubShape;							//RJS 03Jun97

//DeadCode RJS 16Apr98 			Bool	SamplePntTime;								//RJS 18Sep97

			static	UByte		RandTable[256];					//RJS 17Nov97

			static	SByte		VapDeadList[REAL_MAX_VAPOURS];	//RJS 21Jan99
			static	int			VapDeadCnt;						//RJS 09Apr98
			static	AirStrucPtr globinitairitem;				//RJS 13May98
			static	SWord		oldAlphaSwitch;					//RJS 04Jun98
			ItemPtr	RadarItemPtr;								//RJS 25Jun98
			static  Bool		DamageNow;						//RJS 07Jul98
			static  SLong		CollisionCnt;					//RJS 07Jul98
			static  SphTreeTypeP	SphereTree;					//RJS 09Jul98
			static  SphTreeTypeP	SphereTreeTable;			//RJS 09Jul98
			static	UByte		SphereList[256];				//RJS 09Jul98
			static	SLong		GlobSphereCnt;					//RJS 09Jul98
			static  Bool		DrawnClouds;					//RJS 16Jul98

			UWord	MaxMuzzles;									//RJS 23Jul98
			static	ItemPtr		pTrailItm;						//RJS 02Sep98

			static	ShapeNum	damage_Shape;					//RJS 17Sep98
			static	UByteP		damage_Sdptr;					//RJS 17Sep98
			static	SLong		damage_GrpElmt;					//RJS 17Sep98
			static	animptr		damage_GrpAnimPrev;				//RJS 21Apr99
			static	animptr		damage_GrpAnimNext;				//RJS 21Apr99
			static	UByteP		damage_GrpPrev;					//RJS 17Sep98
			static	UByteP		damage_GrpNext;					//RJS 17Sep98
			static SWord dotNLineFadeValue;
			static  Float		DistScale;
			static	UByte	staticRed,staticGreen,staticBlue;	//PD 20Jan99
			static	UByte	shadedRed,shadedGreen,shadedBlue;	//PD 20Jan99
			static	animptr		damage_GrpTokenDep;				//RJS 21Apr99
			static	UByte		damage_ItemState;				//AMM 26Apr99
			static	UByte		current_level;
			static	UByte		IsAircraft;
			static	bool		oldMipMapState;					//RJS 24May99
			static	SLong		animlag;						//RJS 30Jun99

			SLong		radarRange;								//RJS 09Nov98
			ItemPtr		radarTmpItm;							//RJS 09Nov98
			SLong		viewer_x,viewer_y,viewer_z;				//RJS 09Nov98
			FPMATRIX	radarMatrix;							//RJS 09Nov98
			SWord		radarTimer;								//RJS 07Apr99

			static animptr		GlobalAdptr;					//RJS 21Apr99
			ItemPtr		globinititem;							//RJS 21Apr99

		public:
			static	bool	fSpecialShade;
			static	bool	fPolyPitShade;
			void	FixUpColLog();								//RJS 07Jul98
			static	Bool		FixUpCollision;					//RJS 07Jul98
			void	AddToCollisionList(	SLong	uniqueid,
									SLong	element,
									SLong	hittype,
									SLong	hitstrength,UByte pnum,bool myscorer	);
			static	ViewPoint*	View_Point;
			void	SetView(ViewPoint* v,Window* w) {View_Point=v;current_screen=w;}//DAW 23Feb98
			static	DoPointStruc	*newco;						//RJS 02Dec97
			static DoPointStruc	shpco[MAX_DOPOINTS];			//RJS 02Dec97

			Bool	SunInVision;								//PD 24Jun96
			static	Bool	CollisionOn;						//RJS 21Feb97
			static  FPMATRIX	light_matrix;						//RJS 21Jul97
			static  LightVec	TransLightVector;				//RJS 21Jul97
			static  LightVec	TransViewVector;
			static	LightVec	ViewLightVector;

			static	SWord	v_sin_ang;							//RJS 17Mar98
			static	SWord	v_cos_ang;							//RJS 17Mar98
			SWord	DoWhiteFade;								//RJS 31Mar98
			Bool	SamplePntTime;								//RJS 16Apr98
			Coords3D	GunSightPos;							//RJS 20Apr98
			SLong		ClosestGap;								//RJS 20Apr98
			SLong		RequiredRange;							//RJS 20Apr98
			SLong		WingSpan;								//RJS 21Apr98
			SWord		GunSightHdg;							//RJS 21Apr98
			SWord		GunSightPitch;							//RJS 21Apr98
			Bool		ValidGunSight;							//RJS 21Apr98
			SLong		ClosestGap2;							//RJS 09Nov98
			SWord		GunSightRoll;							//RDH 29Nov98

			ReplayAnimOffsets	*AnimDeltaList;						//RJS 06Jul98
			ColLogStuff			ColLog[MaxColLogs];				//RJS 07Jul98
			SLong				ColLogCnt;						//RJS 07Jul98
			SWord	OldWhiteFade;								//RJS 16Jul98

			static	ItemPtr	damage_ItemPtr;						//RJS 25Aug98
			static	animptr	damage_AnimPtr;						//RJS 21Apr99
			static	SLong	damage_Scale;						//RJS 25Aug98

			Float		SphereXScale;							//RJS 02Dec98
			Float		SphereYScale;							//RJS 02Dec98

			probeinfo	MakeProbes[256];						//AMM 26Mar99
			int			newprobecnt;

			Bool		safeTrail;

			static FPMATRIX		subMatrix;						//RJS 07May99
			static FPMATRIX_PTR	subMatrixP;						//RJS 07May99

			static	SLong	gunsightX;							//AMM 25Jun99
			static	SLong	gunsightY;							//AMM 25Jun99
			static	SLong	gunsightZ;							//AMM 25Jun99
			static	UWord	gunsightmvel;						//AMM 25Jun99

			shape::shape(void );
			shape::~shape();									//PD 15Jan96

			void process_shape(Window*,ViewPoint* vp,Obj3DPtr,FPMATRIX_PTR,Bool	subshape=FALSE,FPMATRIX_PTR this_objmatrix=NULL);//RJS 15Jan99

			void UpdateGlobalFlags(int ft);
			void process_shape(Window*,Obj3DPtr,FPMATRIX_PTR,Bool	subshape=FALSE);//RJS 02Dec97

			void UpdateGlobalFlags();
			SLong GetGroupElement(UByte *&, ShapeNum&, SLong&, SLong&, SLong& ,SLong range=0,UByteP *PrevIptr=NULL,SWordP heading=NULL,UByteP* NextIptr=NULL);//RJS 30Jun99
			int GetLiveElementPos(int eltnum, ItemPtr, SLong&, SLong&, SLong&);//JIM 16Oct96
			void	GetGroupDeps(UByteP,SLong&, SLong &);

			SLong SetAnimData(itemptr, SWord bombs=0 );			//RDH 23Sep96
			UByteP CopyAnimData(animptr&, ShapeNum);			//RJS 21Apr99

			void SetPilotedAcAnim(AirStrucPtr );				//PD 16Apr96
			WeapAnimData* GetWeaponLauncher(itemptr, UByte, SLong&,SLong&,SLong&, UWord&, UWord&, UWord&, SByte ltype=-1,UWord *bulletShape=NULL );//RDH 31Jul98
			void	GetContactPoint(itemptr, LnchrType, COORDS3D&,COORDS3D&,COORDS3D&);//RJS 12Aug97
			UByteP GetLauncherPos(ShapeNum, UByte );			//RJS 23Aug96
			void	LauncherToWorld(itemptr,UByteP,UByte,SLong&,SLong&,SLong&,MyGroundVectorPtr,Coords3D* eyePtr=NULL,Bool incock=FALSE);//RJS 08Dec98
			SLong	GetVapourPoint(itemptr,int,int,SLong&,SLong&,SLong&);//RJS 12Jun98
			void	KillVapourStream(int);						//RJS 27May97
			UByteP	GetGroupItemAnim(itemptr, ShapeNum&, SByte, MyGroundVectorPtr );//RJS 21Nov96
			SLong 	GetAnimDataSize(ShapeNum );					//RJS 08Oct96
			SLong 	GetElementAnimOffset(ShapeNum shpno)		//RJS 20Nov97
			{													//RJS 20Nov97
				return (GetAnimDataSize(shpno)+1);				//RJS 20Nov97
			};													//RJS 20Nov97

			SByte	GetElementYDelta(ShapeNum,animptr&,Coords3D&,SLong);//RJS 09Jun99
			UByte	GetGroupDeathToll(itemptr);					//RJS 16Oct96
			Bool	GetNearestTrench(itemptr, SLong&,SLong&,SLong&,SWord& );//RJS 07Nov96
			void	RechargeWeapons(itemptr );					//RJS 19Nov96
			void	ForceDamage(ItemPtr,ItemPtr,UByteP,BitStates,UByte HitterStrength = 4,Bool commsdamage=FALSE);//JIM 11Mar99
			Bool	TestHitBoxes(ItemPtr,ShapeNum,animptr&,UByteP);//RJS 21Apr99
			void animate_shape(Obj3DPtr );						//RJS 20May97
			SLong	DetatchVapourStream(int,int,bool novapour=false);//RJS 19May99
			SLong	DetatchAllVapourStreams(itemptr,int	LifeTime=0,bool novapour=false);//RJS 19May99
			UByte	NextFreeVapour(SWord,SWord,SWord,UByteP);	//RJS 09Apr98
			void	UpdateVapourCoords(itemptr,animptr&);		//DAW 23Apr99
			SLong	ReduceLauncherLoad(AirStrucPtr,SWord,SWord count=1);//RJS 16Sep98
			SLong	WeapUnitWeight(LnchrType);
			void	UpdateSmokeDriftCoords(itemptr,animptr&);	//DAW 23Apr99
			void	HandleVapourCoords(UByteP, itemptr);		//RJS 06Apr99
			void 	dummy_animate_shape(itemptr,UByteP);		//RJS 06Apr99

			SLong	Noise(SLong,SLong,SLong);					//RJS 17Nov97
			UByteP	GetLightDataPtr(ShapeNum,int);					//RJS 18Dec97
			void	InitTrailFields(UByteP,int,int,LnchrType);		//RJS 12Jan98
			UByteP	GetWeaponPack(ShapeNum,int);				//RJS 11May98
			void	KillVapourStreamDeadList();					//RJS 09Apr98
			void	WingSpanUp();								//RJS 20Apr98
			void	WingSpanDown();								//RJS 20Apr98
			void	GunRangeUp();								//RJS 20Apr98
			void	GunRangeDown();								//RJS 20Apr98
			void 	sfx_shape(ItemPtr,IFShare,IFShare,IFShare);	//RJS 20Apr98
			void	RipStores(AirStrucPtr);						//RJS 03Jun98
			Bool	AnimMap(animptr&,SWord,SWord,SWord,SWord&,SWord&,SWord,SWord);//RJS 21Apr99
			void	CalcRadarRange(AirStrucPtr);				//RDH 29Nov98
			void	GetRadarItem(ItemPtr,SLong);				//RJS 09Nov98
			void	ClearRadar();								//RJS 25Jun98
			int		ScanAnimData(itemptr);						//RJS 06Jul98
			void	DefaultAnimData(itemptr,animptr&,Bool isReplay=FALSE);//RJS 21Apr99
			void	PatchAnimData(itemptr,int);					//RJS 06Jul98
			void	CollisionPlayback();						//RJS 07Jul98
			void	InitCloudFade();							//RJS 16Jul98
			void	SetCloudFade();								//RJS 16Jul98
			WeapAnimData* DirectWeaponLauncher(itemptr,UByte,UWord&,SLong&,SLong&,SLong&,UWord&,UWord&,UByte&); //MACCA98
			Bool	ResetAnimData_NewShape(ItemPtr,ShapeNum,UByte weappack=0,bool sendPacket=false);//RJS 21Apr99
			void	KillGear(ItemPtr);							//RJS 07Sep98
			void	FixUpGroupCol();							//RJS 17Sep98
			void	SetGroupDamage(SLong,UByteP,UByteP,animptr&,animptr&,animptr&);//RJS 21Apr99
			SLong	GetAnimDataSizeAndCheck(ShapeNum,AnimSizes,Bool&);//RJS 30Oct98
			void	SetDistScale();								//RJS 02Nov98
			Bool	SampleTrailList();							//AMM 17Nov98
			Bool	GetSmokeTrailList(Bool dummy);				//AMM 17Nov98
			void	DeleteAllSmokeTrails();						//AMM 17Nov98
			void	ResetRadar(AirStrucPtr,SLong,SLong,SLong);	//RJS 09Nov98
			void	SetRadar();									//RJS 06Nov98
			UByteP	GetGroupItemAnimHdg(itemptr, ShapeNum&, SByte, MyGroundVectorPtr, UWord& );//RJS 18Nov98
			void	LogFuelDamage(ItemPtr,UByteP,ItemPtr);		//RJS 18Jan99
			void	ProbeStaticTrail(UByteP,itemptr,animptr&);	//RJS 21Apr99
			void	ReloadMassAndDrag(AirStrucPtr);				//RJS 25Jan99
			void	SetGrpTokenVisibility(UByteP,animptr&,animptr&);//RJS 21Apr99
			SLong	GetGroupElementToken(UByte*&,ShapeNum&,SLong&,SLong&,SLong&,SLong,UByteP*,SWordP,ULong&,UByteP&);//RJS 30Jun99
			void	InitGlobalItem();							//RJS 15Feb99
			SWord  InitItemAnim(animptr&, ShapeNum);			//RJS 21Apr99
			void	NavigationLightsActive(ItemPtr,Bool);		//DAW 17Feb99
			void	ActivateBombBays(ItemPtr);					//DAW 17Feb99
			void replay_animate_shape(ItemPtr	itm);			//AMM 25Feb99
			void	GenerateProbeTrails();						//AMM 26Mar99
			void	SetAnimDataFlags(ShapeNum,animptr&,SLong&);	//RJS 21Apr99
			void	ReplayAnimData_NewShape(UWord,UWord);		//RJS 21Apr99
			void	BombBayDoors(AirStrucPtr,SLong);			//RJS 28Jun99


		private:
			void DrawHitBox(Window*,Obj3DPtr,MATRIX_PTR);		//PD 23Oct96
//DeadCode RJS 20May97 			void animate_shape(Obj3DPtr );						//PD 13Mar96
			void draw_shape(Obj3DPtr );							//PD 13Mar96

			void  InitAnimData(itemptr );
//Dead			SWord  InitItemAnim(UByteP&, ShapeNum);				//RJS 23Aug96
			SWord  InitLauncherAnim(animptr&, ShapeNum,int packno=0);//RJS 21Apr99
			UByte GetNumberOfLaunchers(ShapeNum );				//RJS 23Aug96
			void	InitUndercarriageAnim(AirStrucPtr);			//RJS 28May98

			void  drawsphere(int,int,int,int,int,int,Bool,int,int,int);//RJS 21Jan98
			void  imapsphere(UWord,UWord,ImageMapNumber,SWord,SWord,SWord,SWord,bool ispivoted=false);//RJS 26Nov98
//DeadCode RJS 16Dec97 			void  omapsphere(UWord,SLong,ImageMapNumber,SWord,SWord,SWord,SWord,SWord,SWord,UByte,UByte);//RJS 19Feb97
			void  RealImapSphere(int,int,int,int,int,int,int,int,int);//RJS 16Dec97
			void  imapcylinder(UWord,UWord,SLong,ImageMapNumber,UWord,UWord,UWord,UWord,UWord,UWord);//RJS 20Nov98
			void  omapcylinder(UWord,UWord,SLong,ImageMapNumber,UWord,UWord,UWord,UWord,UWord,UWord,UByte,UByte);//RJS 19Feb97
//DeadCode RJS 06Feb98 			void  imapsphere2(UWord,SLong,ImageMapNumber,SWord,SWord,SWord,SWord,SWord,SWord,UWord);//RJS 05Feb98
//DeadCode PD 24Oct96 			void  DrawCheatBox(ShapeDescPtr );					//RJS 23Oct96
			void  imaptrailcyl(UWord,UWord,ImageMapNumber,SWord,SWord,SWord,SWord,UWord,UWord,UByte,UByte,SWord,SWord,SWord,SWord);//RJS 18Sep97
			void  plaincylinder(UWord,UWord,UWord);				//RJS 04Nov97
			void  ParticleCylinderPlain(UWord,UWord,SWord,SWord,SWord,SWord,UWord,SWord,MyGroundVectorPtr,MyGroundVectorPtr,SWord,SWord);//RJS 04Dec97
			void  ParticleCylinderImapd(UWord,UWord,SWord,SWord,SWord,SWord,UWord,SWord,MyGroundVectorPtr,MyGroundVectorPtr,SWord,SWord,SWord,SWord,SWord,SWord);//RJS 11Mar98
			void  ParticleStreamPlain(UWord,UWord,SWord,SWord,SWord,SWord,UWord,SWord,SWord,MyGroundVectorPtr,MyGroundVectorPtr,SWord,SWord);//RJS 04Dec97
			void  ParticleStreamImapd(UWord,UWord,SWord,SWord,SWord,SWord,UWord,SWord,SWord,MyGroundVectorPtr,MyGroundVectorPtr,SWord,SWord,SWord,SWord,SWord,SWord);//RJS 11Mar98
			void  ParticleBoxPlain(UWord,UWord,UWord,UWord,UWord,MyGroundVectorPtr,SWord,SWord,SWord,Bool);//RJS 04Dec97
			void  ParticleBoxImapd(UWord,UWord,SWord,SWord,SWord,SWord,UWord,SWord,MyGroundVectorPtr,MyGroundVectorPtr,SWord,SWord,SWord,SWord);//RJS 04Dec97
			void  PlainBlobLine(UWord,UWord,UWord);					//RJS 11Dec97
			void  ParticleStreamEdgedPlain(UWord,UWord,SWord,SWord,SWord,SWord,UWord,SWord,SWord,MyGroundVectorPtr,MyGroundVectorPtr,SWord,SWord);//RJS 12Dec97
			void  LineStream(UWord,UWord,SWord,SWord,SWord,SWord,UWord,SWord,SWord,MyGroundVectorPtr,MyGroundVectorPtr,SWord,SWord);//RJS 05Jan98
			void  plaintrailcyl(UWord,UWord,SWord,SWord,SWord,SWord,SWord,SWord);//RJS 09Jan98
			void  DrawHeatHaze(int,int,int);					//RJS 30Jan98
			void  imapsphereQuad(UWord,UWord,ImageMapNumber,SWord,SWord,SWord,SWord);	//RJS 20Feb98
			void  ParticleStreamStaggeredImapd(UWord,UWord,SWord,SWord,SWord,SWord,SLong,SLong,SWord,SWord,MyGroundVectorPtr,MyGroundVectorPtr,SWord,SWord,SWord,SWord,SWord,SWord,SWord);//RJS 31Mar98
			Bool  ClipSphere(DoPointStruc&,DoPointStruc&,DoPointStruc&,DoPointStruc&,SLong);//RJS 21Aug98
			Bool  ClipCylinder(DoPointStruc&,DoPointStruc&,DoPointStruc&,DoPointStruc&,SLong,SLong);//RJS 21Aug98
			void  imaptrailcylWrapped(UWord,UWord,ImageMapNumber,SWord,ImageMapNumber,SWord,SWord,SWord,SWord,SWord,SWord,SWord,SWord,SWord,SWord,Bool);//RJS 25Nov98
			Bool  ClipSphereSpin(DoPointStruc&,DoPointStruc&,DoPointStruc&,DoPointStruc&,SLong,SWord);//RJS 19Nov98
			void  imapspherespin(UWord,UWord,ImageMapNumber,SWord,SWord,SWord,SWord,SWord);//RJS 19Nov98
			Bool  ClipSphereRatio(DoPointStruc&,DoPointStruc&,DoPointStruc&,DoPointStruc&,SLong,SWord,SWord,bool);//RJS 26Nov98
			void  FixedPolyOnFloor(Coords3DList*,Coords3DList*,SWord,SWord,SWord,SWord,ImageMapNumber,SWord,SWord,SWord,SWord);//RJS 21Apr99

			//Animation code

			void	ResetAnimFlags();							//PD 27Mar96
//DeadCode RJS 05Jun97 			void	SimpleItemAnim(MinAnimData* );				//PD 27Mar96
			void	AircraftAnim(AircraftAnimData*,Bool pitset=FALSE );//RJS 12Feb98
			void	BlokesItemAnim(BlokesAnimData* );			//RJS 01Jun99
			void	WeapItemAnim(WeapAnimData* );				//PD 01Apr96
//DeadCode RJS 05Jun97 			void	ExplodeItemAnim(ExplodeAnimData* );			//PD 15Apr96
			void	PolyPitItemAnim(PolyPitAnimData* );			//PD 15Apr96
			void	SunItemAnim(SunAnimData* );						//PD 24Jun96
			void	SetLauncherData(WeapAnimData* ,ShapeNum );	//PD 01Apr96
			void	FlameItemAnim(FireAnimData* );				//RJS 10Jul96
			void	BalloonItemAnim(BalloonAnimData*, Obj3DPtr );//RJS 12Aug96
			void	WindsockItemAnim(WindsocAnimData* );		//RJS 05Jun97
			void	BarageItemAnim(BarageAnimData* );			//RJS 24Sep96
			void	FireballItemAnim(ExplodeAnimData* );		//RJS 07Oct96
			void	MoveGunItemAnim(MoveGunAnimData* );			//RJS 15Oct96
			void	TankItemAnim(MoveGunAnimData* );			//RJS 17Oct96
			void	TruckItemAnim(MinAnimData*,UByteP);			//RJS 18May99
			void	TrainItemAnim(TrainAnimData* );			//RJS 09Dec96
			void	TroopItemAnim(TroopAnimData*,TroopAnimData* );//RJS 06Dec96
			void	BridgeItemAnim(ExplodeAnimData* );			//RJS 20Nov96
			
			void	AddNewVapourPoint(TrailRecord*,SLong,SLong,SLong,ULong,ULong );//RJS 24Nov98
			Float	DoTrailPoint(UWord, SLong, SLong, SLong);	//RJS 19May97
			void*	FindWeapRecord(ShapeNum,SLong&);			//RJS 03Aug98
			void	AddWeapToAnim(void*,MoveGunAnimData*,LnchrType,int,int&,int&,int&);//RJS 21Apr99

			Bool	SampleSmokePnt(UByteP,SWord&,UByteP,SWord&,UWord);			//RJS 07May98
			SLong	DrawSmokeTrail(SWord,UByteP,ULong,SWord,SWord,SWord,Bool);//RJS 12Mar99
			UWord	CalcTrailDeltas(UByteP,UByteP,UWord,SWord&,SWord&);//RJS 15Apr98
			void	AddVapourStreamToDeadList(int,ItemPtr);			//RJS 22Apr99
			Bool	SampleDustPnt(UByteP,SWord&,UByteP,UWord,SLong,SWord);			//RJS 07May98
			void	AddMassAndDrag(UByteP,int,int,int,int,SLong,SWord);//RJS 25Mar99
			void	AddSmokeCloud(TrailRecord*,ShapeNum,int);	//RJS 03Jul98
			void	LogCollision(ItemPtr,ItemPtr,ShapeNum,UByteP,SLong,int,int,UByte);//JIM 11/03/99
			void	AddToTree(int);								//RJS 09Jul98
			void	RecurseTree(SphTreeTypeP);					//RJS 09Jul98
			SLong	EmptyTree();								//RJS 09Jul98
			UWord	GetMuzzleIndex(LnchrType);					//RJS 23Jul98
			void	DrawDirtTrail(SWord,UByteP,ULong,Bool);		//MS 10Dec98
			UWord	CalcDirtDeltas(Coords3DList*,Coords3DList*,UWord,SWord&,SWord&);//RJS 21Apr99

			static void SetLineAndDotShade(itemptr,ViewPoint*);		//PD 02Nov98
			void UpdateReplayVapourCoords(UByteP	rsdptr, itemptr	itm,animptr&	aptr);//RJS 21Apr99
			Bool ReplaySampleSmokePnt(	UByteP		smkinfo,
										SWord		&listindex,
										UByteP		instr_ptr,
										SWord		&Stores,
										UWord		LifeTime,
										SWord		&hdg,
										SWord		&pitch,
										SWord		&roll
										);						//AMM 25Feb99

			void	AddFuelLauncher(UByteP, int, int);
			void	FakeDustTrail(Coords3D&,SLong,SWord,UByteP);//RJS 18May99
			void	DrawTempBlobTrail(SLong,UByteP,SLong,Bool);	//RJS 07Jun99
	

	static	void	InterpLoop(UByteP);					//RJS 19Mar97

		protected:

			static	void shape::makeViewLightVec();
			static	SWord shape::plainPolyLight(DoPointStruc**);
			static	bool doingHW3D;

 			static	InterpProc
 					dopoint,		dopolygon,		dosetlc,		dosetcolour,
 					doline,			doret,			doifcross,		dogosub,
 					doifeq,			doifne,			donop,			dogroup,
 					dogoto,			doend,			dowindowdial,	doattitude,//RJS 07Apr98
 					dodot,			doscalesize,	dogunsight,		dowheelspray,//RJS 16Mar98
 					doifbright,		doquikpoly,		dofadeenvelope,	dowhiteout,//RJS 31Mar98
 					donpoints,		don4cmpnts,		do4cmpnt,		dondupvec,//RJS 29May98
 					dondeltapoints,	dodrawsun,	dosetcolour256,	doswitch,//RJS 22Jun98
 					dosetcolourall,	dopoint2x,		do4cmpt2x,		doifcase,
 					donincpnts,		dotransparenton,dotransparentoff,dosphere,
 					dosmokedon,		dosmokedoff,	donormal,		dosmoothpoly,
 					dovector,		dotransformlight,dolshadeon,	dorelpoly,//RJS 30Apr98
 					donspheres,		donspheresimapd,doweaponoff,	dodrawreflectpoly,//RJS 26Aug98
 					doresetanim,	dospin,			dosetcolourh,	doquiksmoothpoly,//RJS 19Nov98
 					dorepos,		dodepthcolour,	dodepthpoly,	doimagemap,
 					docreateipoly,	docreateivert,	dodrawipoly,	docopyivert,
 					dosmthrelpoly,	doquikrelpoly,	donsubs,		dobitsofffx,//RJS 15Jan99
 					doondamaged,	dosetmipmap,	donvec,			donextvec,//RJS 18Jan99
 					donpoint2x,		docallshape,	dosmokepnt,		dobitsoff,
 					doplumepnt,		doisphere,		dorealisphere,	docreaterpoly,//RJS 16Dec97
 					dodrawipolys,	domappoly,		dosetmapmap,	do3dbreak,
 					docylinder,		dontpoints,		dosetmapoff,	dosetmappingplaner,
 					dosetmappingtan,dosmktrail,		dooffsetpnt,	doicylinder,
 					docreatebpoly,	docopybvert,	dodrawbpoly,	dodrawrpoly,
 					dodrawopoly,	dolauncher,		dodial,			docompass,
 					doiswitch,		doincln,		dosetglassrange,drawbetween,
 					doanimation,	dodamage,		doeffect,		docollision,
 					dodrawstation,	docaserange,	doifpiloted,	doniverts,
 					dotrifan,		dotrizag,		dotrifanflat,	dotrizagflat,
 					dostretchpoint,	dostretchmap,	doflipvector,	doflipnvec,
					domorphpoint,	domorphnpoints,	douserealtime,	dotimerphase,
					doblobline,		dowheeldamage,	dolight,		dolighttimer,
					dodigitdial,	donianimverts,	dosetluminosity, dobitsoffcock,
					domorphsphere,	domorphsphereimapd, doheathaze,	doifhard3d,
					domorphnsphrs,	domorphnsphrsimapd;			//RJS 04Feb98

//DeadCode RJS 01Dec97 			static	InterpProc*	InterpTable[dosetglassrangeno+1];		//PD 17Oct96
//DeadCode RJS 01Dec97 			static	void		DrawSubShape(DOCALLSHAPE_PTR);	//RJS 03Mar97
			static	InterpProc*	*InterpTable;					//RJS 01Dec97
			static	void		DrawSubShape(UByteP);			//RJS 01Dec97
		};

	extern	class	shape	SHAPE;

#endif
