//------------------------------------------------------------------------------
//Filename       replay.h
//System         
//Author         Andy McMaster
//Date           Wed 29 Apr 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	REPLAY_Included
#define	REPLAY_Included

#define	DEFAULT_REPLAY 0

#include	"DOSDefs.h"	
#include	"stdio.h"
#include	"fileman.h"
#include	"winmove.h"
#include	"worldinc.h"
#include	"modvec.h"											
#include	"model.h"											
#include	"savegame.h"
#include	"cbuffer.h"

//DeadCode AMM 26Nov98 #define	FRAMESINBLOCK 1000
#define	REPLAYHEADBEGINID 0x12345678
#define	REPLAYHEADENDID 0x12345679
#define	REPLAYSUPERHEADBEGINID 0x72345678
#define	REPLAYSUPERHEADENDID 0x72345679

// bullets and missiles get 10 secs, bombs 1 min

#define MISSILEDELAY	500
#define	BULLETDELAY		500
#define BOMBDELAY		3000
#define	POSBSIZE		5

typedef struct _basic_packet REPLAYPACKET;
typedef struct _basic_packet* LPREPLAYPACKET;

typedef struct _miss_conds MISSIONCONDS;
typedef struct _miss_conds* LPMISSIONCONDS;

struct _miss_conds {

	FP	TempVar;			//K variation in temp last time
	FP	Temp0;				//K	temp at seal level
	FP	Press0;				//millibar
	FP  Density0;			//kg/m3 @ SL	//CSB 27/10/98
	FP	wind0;				//mph
	FP	dir0;				//direction in degrees
	FP	windalt;			//mph
	FP	diralt;				//direction in degrees
	FCRD Wind0;				// wind at zero height
	FCRD WindAlt;			// wind at altitude
	SLong WindAltHeight;		// height of above		//RJS 02Nov98
	SWord MinDuration;		// csecs
	SWord MaxDuration;		// csecs
	FP MinMagnitude;		// 1 = 1 m/s
	FP MaxMagnitude;		// 1 = 1 m/s
	UWord Frequency;		// 0 = always, 65535 = very infrequent
	//contrails
	FP	ContrailBandCentre;
	FP	ContrailBandWidth;

	FP	Visibility;			// in cm
	FP	Conditions;			//CLEAR, RAIN, SNOW
	FP	CloudLayer;			// bottom layer in cm
	bool	MistInValley;

};



typedef struct _grentry REPGRENTRY;
typedef struct _grentry* LPREPGRENTRY;

struct _grentry {
	int	val;
	LPREPGRENTRY next;
};

typedef struct _grlist GRLIST;
typedef struct _grlist* LPGRLIST;

struct _grlist {
	FileNum			file;
	ULong			bfctrl;
	LPREPGRENTRY	list;
	UWord			ordernum;									//AMM 10Feb00
	LPGRLIST		next;
};

typedef struct _miprim_values MIPRIMARYVALUES;
typedef struct _miprim_values* LPMIPRIMARYVALUES;

struct _miprim_values
{
// ItemBase
 
	COORDS3D	pos;
	ITEM_STATUS	Status;

// item

	ShapeNum	shape;

// hdgitem

	ANGLES		hdg;

// hpitem

	ANGLES		pitch;

// rotitem

	ANGLES		roll;

// moving item

	SWord		vel;

//mobile item

//DeadCode AMM 07Apr99 	UniqueID	waypoint;
	ONLYFIELD(UWord,UniqueID,waypoint)
	AutoMoveCodeTypeSelect movecode;
	ONLYFIELD(UWord,UniqueID,leader)							//AMM 05Jul99
	ONLYFIELD(UWord,UniqueID,follower)							//AMM 05Jul99
};

typedef struct _asprim_values ASPRIMARYVALUES;
typedef struct _asprim_values* LPASPRIMARYVALUES;

struct _asprim_values
{

// airstruc

// pack bools into a byte

	FIRSTFIELD (UByte, Bool,simpleacm,0)
		BITFIELD(Bool,flatturn,1,1)
		BITFIELD(Bool,information,2,2)
		BITFIELD(Bool,slowdownleader,3,3)
		BITFIELD(Bool,advantage,4,4)
		BITFIELD(Bool,disadvantage,5,5)
		BITFIELD(Bool,UseIntFuel,6,6)
		LASTFIELD(Bool,FuelDumped,7,7)

	FIRSTFIELD (UByte, Bool, StoresDumped,0)
		BITFIELD(Bool,Ejected,1,1)
		BITFIELD(Bool,Spare0,2,2)
		BITFIELD(Bool,Spare1,3,3)
		BITFIELD(Bool,Spare2,4,4)
		BITFIELD(Bool,Spare3,5,5)
		BITFIELD(Bool,Spare4,6,6)
		LASTFIELD(Bool,Spare5,7,7)

	bool	playermoving;

	// ai

	ONLYFIELD(UWord,UniqueID,homebase)							//AMM 02Jun99
	ONLYFIELD(UWord,UniqueID,unfriendly)
	ONLYFIELD(UWord,UniqueID,attacker)
	ONLYFIELD(UByte,MANOEUVRE,manoeuvre)
	UByte		ManStep;
	UByte		morale;
	SByte		moraleinc;
	SLong		lastdelta;
	ANGLES		desiredroll;
	ANGLES		desiredpitch;
//DEADCODE JIM 28/04/99 	ANGLES		lastdeltaroll;
	ANGLES		desiredaoa;

	ANGLES		desiredhdg;
	Float		desiredturn;
	Float		desiredpitchrate;
	ULong		desiredrange;
	ULong		desiredalt;
	SLong		deltapitchsum;

	//weap

	UWord	rreloadmass;
	UWord	creloadmass;
	UWord	lreloadmass;

	UWord	rreloaddrag;
	UWord	creloaddrag;
	UWord	lreloaddrag;

	UWord	rmass;
	UWord	cmass;
	UWord	lmass;

	UWord	rdrag;
	UWord	cdrag;
	UWord	ldrag;

//DeadCode AMM 13Jul99 	int	int_fuel;
	int	rint_fuel;												//AMM 13Jul99
	int	cint_fuel;												//AMM 13Jul99
	int	lint_fuel;												//AMM 13Jul99

	int	rext_fuel;
	int	cext_fuel;
	int	lext_fuel;

//DeadCode AMM 13Jul99 	SWord	int_fuel_leakage;
	SWord	rint_fuel_leakage;									//AMM 13Jul99
	SWord	cint_fuel_leakage;									//AMM 13Jul99
	SWord	lint_fuel_leakage;									//AMM 13Jul99

	SWord	rext_fuel_leakage;
	SWord	cext_fuel_leakage;
	SWord	lext_fuel_leakage;

	UWord	shpweapindex;
	SWord	ShootDelay;
	SWord	weapforce;

	//flight_ctl

	ONLYFIELD(UByte,FormationIndex,originalformpos);			//AMM 02Jun99
	ONLYFIELD(UWord,UniqueID,nextflight)
	ONLYFIELD(UWord,UniqueID,leadflight)
	SWord		rpm;
	SWord		thrustpercent;
//DeadCode AMM 29Jun99 	ANGLES		cpitch;
	ONLYFIELD(UWord,UniqueID,backupWP)
	SLong		gforce;
	SWord		aileron;
	SWord		elevator;
	SWord		rudder;
	Float		dhdg;

	//	misc

	UNIQUE_ID	lasthitter;

	UByte		Weapons;

// formationitem

	ONLYFIELD(UWord,FormationIndex,formpos)
// moved into MI stuff because convoys need leader and follower as well as AC
//DeadCode AMM 05Jul99 	ONLYFIELD(UWord,UniqueID,leader)
//DeadCode AMM 05Jul99 	ONLYFIELD(UWord,UniqueID,follower)
	ONLYFIELD(UByte,FORMATIONDESC,formation)
	ONLYFIELD(UByte,DutyType,duty)
	UWord		manoeuvretime;
};

typedef struct _fm_full_prim_values FMPRIMARYVALUES;
typedef struct _fm_full_prim_values* LPFMPRIMARYVALUES;

struct _fm_full_prim_values 
{
// model.h

	Bool	FirstCycle;											//AMM 29Jun99
	FCRD	RotVel;
//DeadCode AMM 29Jun99 	FP		Mass;
//DeadCode AMM 29Jun99 	FCRD	RotInertia;
	int		Elevator;
//DeadCode AMM 29Jun99 	int		ElevatorTrim;
	int		Aileron;
	int		Rudder;
//DeadCode AMM 29Jun99 	SWord	DesiredRPM;
//DeadCode AMM 29Jun99 	Bool	Gear;
	UWord	CrashTime;

// acmmodel.h

	FP		lastdeltapitch;
	FP		deltapitchsum;						
	FP 		deltarollsum;						
	FP 		deltayawsum;						
	FP 		maxdeltaforclosework;
	FP		OldCtrlRoll;
	FP		OldCtrlTurnRate;
	FP		OldCtrlYawRate;
	FP		desiredRoll;

};

typedef struct _prim_engine_vals PRIMARYENGINEVALUES;
typedef struct _prim_engine_vals* LPPRIMARYENGINEVALUES;

// engine.h

struct _prim_engine_vals {

	FP		Speed;
	FP		SpeedRpm;
	FP		MaxThrust;
	FP		PropInc;
	FP		PropVel;
	FP		SlipVel;
	FP		SlipRot;
	Bool	BlowerHigh;
};

// elmt.h

typedef struct _prim_elmt_vals PRIMARYELMTVALUES;
typedef struct _prim_elmt_vals* LPPRIMARYELMTVALUES;

struct _prim_elmt_vals {

	FP		aoa[2][2];
};

typedef struct _aerodev_vals AERODEVVALUES;
typedef struct _aerodev_vals* LPAERODEVVALUES;

struct _aerodev_vals {

	SWord	Val;
	SWord	Attractor;
	SWord	OldAttractor;
};

enum	RDEATH													//RJS 28Oct98
{																//RJS 28Oct98
	RDEATH_NULL	= 0,											//RJS 28Oct98
	RDEATH_SKID,												//RJS 28Oct98
	RDEATH_ROLL,												//RJS 28Oct98
	RDEATH_DIVE													//RJS 28Oct98
};																//RJS 28Oct98

//DeadCode AMM 29Mar99 enum	RECORDSTATE
//DeadCode AMM 29Mar99 {
//DeadCode AMM 29Mar99 	RS_NOINTERRUPT=0,
//DeadCode AMM 29Mar99 	RS_NOTRECORDED,
//DeadCode AMM 29Mar99 	RS_RECORDING,
//DeadCode AMM 29Mar99 	RS_HAVERECORDED
//DeadCode AMM 29Mar99 };

typedef struct ReplaySmkStruc REPLAYSMOKE;
typedef struct ReplaySmkStruc* LPREPLAYSMOKE;

struct	ReplaySmkStruc											//AMM 04Nov98
{
 	ULong			lifetime;									
	SLong			lastwx,										
					lastwy,										
					lastwz;										
	UByte			nextlist:6,									
					beendrawn:1,
					cloudlaunched:1;								
	SWord			LaunchCountdown;							
	SWord			SampleTime;									
	SByte			smkindex:7,									//RJS 18Feb99
					transient:1;								//RJS 18Feb99
	UByte			nopoints;
	ULong			currTime;									//RJS 16Jun99
};																//AMM 04Nov98

struct	ReplaySmlSmkStruc											//RJS 18Feb99
{																//RJS 18Feb99
	UWord			uniqueid;									//RJS 18Feb99
 	ULong			lifetime;									//RJS 18Feb99
	SByte			smkindex;									//RJS 18Feb99
	UByte			nopoints;									//RJS 18Feb99
	ULong			currTime;									//RJS 16Jun99
};																//RJS 18Feb99

struct	ReplaySmkPoint											//RJS 17Feb99
{
	SLong	x,y,z;
	ULong	lifeleft:18,								
			radius:14;									
	ULong	LifeTime:18,								
			FadeTime:13,								
			KillMe:1;									
//DeadCode RJS 18Feb99 	SWord	xdelta;										
//DeadCode RJS 18Feb99 	SWord	ydelta;										
};

typedef struct _markinfo MARKINFO;
typedef struct _markinfo* LPMARKINFO;

struct _markinfo 
{
	ULong blocknum;
	UWord framenum;
	UByteP memaddress;
};

enum	ReplayFlags
{
	RF_NONE=0,
	RF_SKIPFRAMES,
	RF_BLOCKFORWARD,
	RF_BLOCKREWIND,
	RF_FRAMEFORWARD,
	RF_FRAMEREWIND,
	RF_SKIPTOPREVIOUSMARK,
	RF_SKIPTONEXTMARK
	
};

struct ArmedTransient
{
	COORDS3D	Pos;
	UWord		shape;
	SWord		velx;
	SWord		vely;
	SWord		velz;
	SWord		velhori;
	UByte		movecode;
	UByte		strength;
	UWord		launcher;
	UWord		lifetime;
	ANGLES		hdg;
	ANGLES		pitch;
	UWord		deadtime:1,
				trailindex:6,
				transrandom:9;
};


class Replay {

public:
	bool	replayskip;											//DAW 18Aug99
	bool	ResetFileFlag;
	Bool	Record;
	Bool	Playback;
	ULong	PlaybackGameState;
//DeadCode AMM 26Feb99 	bool	PlaybackCampDebrief;
	Bool	PlaybackPaused;

	void* 	playbackfilestart;
	UByteP	playbackfilepos;
	UByteP	playbackfileend;
	HANDLE	mappedplaybackfile;
	HANDLE	playbackstorage;

	void*	recordfilestart;
	UByteP	recordfilepos;
	HANDLE	mappedrecordfile;
	HANDLE	recordstorage;
	ULong	recordfilemaxsize;
	ULong	recordfilecurrsize;

	char	rfilename[256];
	char	pfilename[256];
	char	RealFilename[256];
	ULong	replayframecount;

	UWord	thisblockstartframe;
	UWord	thisblockendframe;
	UWord	thisblocknumframes;

	MARKINFO	beginmark;
	MARKINFO	endmark;

	void	DeleteReplayLog();
	
	RDEATH	ReplayDeathMode;									//RJS 28Oct98


	CON Replay();
	CON ~Replay();

	Bool	StoreDeltas();
	Bool	EndRecord();
	Bool	EndPlayback();
	Bool	SaveReplayData(char* name);
	Bool	LoadReplayData(char* name);
	Bool	OpenRecordLog();
	void	CloseRecordLog();
	Bool	OpenPlaybackLog();
	void	ClosePlaybackLog();
	Bool	LoadDeltas();
	Bool	StoreRandomList();
	Bool	LoadRandomList();
	Bool	StoreInitialGlobRefs();
	Bool	LoadInitialGlobRefs();
	Bool	StoreDeadItems();
	Bool	LoadDeadItems();
	void	UpdateGhostAC();
	void	ProcessFirstBulletPacket(AirStrucPtr bul, LPREPLAYPACKET packet);
	void	ProcessSecondBulletPacket(AirStrucPtr bul, LPREPLAYPACKET packet);
	Bool	LoadItemAnims();
	Bool	StoreItemAnims();

	bool	LoadSaveGame();
	Bool	StoreSaveGame();

	Bool	BlockForward();
	Bool	BlockRewind(Bool onlyone=FALSE);
//DeadCode AMM 12May99 	Bool	LoadPilots();
//DeadCode AMM 12May99 	Bool	StorePilots();
	ULong	LoadHeaderLength();
	Bool	StoreHeaderLength(ULong length);

	Bool	StartRecordFlag;
	ULong	framestoskip;
	ReplayFlags	ReplayFlag;

	int		PlayerSquad;
	int		PlayerPos;
	ULong	headlength[1024];
	UByteP	headmems[2][1024]; // memory address off beginning/end of block
	UWord	numframes[1024];
	UWord	markers[2][1024]; // begin frame, end frame of block
	UByte	numblocks;
	UByte	currblock;
	LPREPGRENTRY initgrlist;
	LPGRLIST	bfgrlist;
	LPGRLIST	currentry;
	void	AddFileAndGlobRefsToList(FileNum file,ULong bfctrl);
	void	DeleteFileAndGlobRefList(LPGRLIST& list);
	void	GetGlobRefs(LPREPGRENTRY& list);
	Bool	StoreGlobRefList(LPREPGRENTRY list);
	Bool	LoadGlobRefList(LPREPGRENTRY& list);

	void	SetGlobRefs(LPREPGRENTRY list);

	Bool	StoreFileAndGlobRefList();
	Bool	LoadFileAndGlobRefList();

//DeadCode AMM 19Mar99 	Bool	ReplayRead(UByte* dest, ULong size);
//DeadCode AMM 21Apr99 	Bool	ReplayRead(void* dest, ULong size);
	Bool	ReplayRead(UByte* dest, ULong size);
//DeadCode AMM 19Mar99 	Bool	ReplayWrite(UByte* src, ULong size);
//DeadCode AMM 21Apr99 	Bool	ReplayWrite(void* src, ULong size);
	Bool	ReplayWrite(UByte* src, ULong size);
	void	GetInitialGlobRefs();
	void	DeleteGRList(LPREPGRENTRY& list);
	Bool	StoreHeaderID();
	Bool	LoadHeaderID();

	FileNum	LoadBFieldNum();
 	Bool	StoreBFieldNum(FileNum bf);

	ULong	LoadBFCtrl();
 	Bool	StoreBFCtrl(ULong a);

	Bool	StoreItemData();
	Bool	LoadItemData();

	void	ResetReplayData();

	void	SkipToBeginning();
	void	SkipToEnd();
	void	FrameForward();
	ULong	FrameRewind();

	Bool	StoreInitFrameCounts();
	Bool	StoreRealFrameCounts(UWord num, UWord start, UWord end);
	Bool	LoadFrameCounts();

	Bool	StorePrimaryASData(AirStrucPtr ac); //, LPASPRIMARYVALUES aspv);
	void	GetPrimaryASData(AirStrucPtr,LPASPRIMARYVALUES aspv);
	Bool	StorePrimaryMIData(MobileItemPtr ac); //, LPMIPRIMARYVALUES mipv);
	void	GetPrimaryMIData(MobileItemPtr item,LPMIPRIMARYVALUES mipv);

	void	RestorePrimaryASValues(AirStrucPtr ac, LPASPRIMARYVALUES aspv);
	void	RestorePrimaryMIValues(MobileItemPtr ac, LPMIPRIMARYVALUES mipv);

	Bool	StorePrimaryFMData(AirStrucPtr ac);
	void	GetPrimaryFMData(AirStrucPtr ac, LPFMPRIMARYVALUES);
	Bool	StorePrimaryEngineData(AirStrucPtr ac);
	void	GetPrimaryEngineData(LPPRIMARYENGINEVALUES,PENGINE );
	Bool	StorePrimaryElmtData(AirStrucPtr ac);
	void	GetPrimaryElmtData(LPPRIMARYELMTVALUES, PMAINPLANE);

	Bool	LoadFMData(AirStrucPtr ac);
	void	RestorePrimaryFMData(AirStrucPtr ac,LPFMPRIMARYVALUES);
	void	RestorePrimaryEngineData(LPPRIMARYENGINEVALUES,PENGINE);
	void	RestorePrimaryElmtData(LPPRIMARYELMTVALUES,PMAINPLANE);
	void	ResetSecondaryFMValues(AirStrucPtr ac);

	Bool	StoreAeroDevData(AirStrucPtr ac);
	void	GetAeroDevData(LPAERODEVVALUES ,PAERODEVICE);
	void	RestoreAeroDevData(LPAERODEVVALUES,PAERODEVICE);

	Bool	StoreSuspensionData(AirStrucPtr ac);
	FP		GetSuspensionData(PGEAR);
	void	RestoreSuspensionData(FP legpos,PGEAR);

	Bool	LoadGamePrefs();
	Bool	StoreGamePrefs();

	void	StoreFinalRecordData();
	void	LoadFinalPlaybackData();

	void	ResetAICount();
	void	RemoveAllTransients(Bool	totalremove=FALSE);				 //RJS 21Jun99
	void	StopRecord();
	void	GetReplayFileName();

// Dummy death movecodes that go through the motions, but don't actually move...

	void	DummyCrashSkid();									//RJS 28Oct98
	void	DummyCrashRoll();									//RJS 28Oct98
	void	DummyCrashDive();									//RJS 28Oct98

	Bool	StoreDeathMoveState();								//RJS 29Oct98
	Bool	LoadDeathMoveState();								//RJS 29Oct98

	Bool	LoadSmlSmkData(ReplaySmlSmkStruc*,Bool,UByteP&,Coords3D&);//RJS 18Feb99
	Bool	StoreSmlSmkData(ReplaySmlSmkStruc*,UByteP);			//RJS 18Feb99
	Bool	StoreSmkData(LPREPLAYSMOKE,UByteP);					//RJS 17Feb99
	Bool	LoadSmkData(LPREPLAYSMOKE smokey,Bool,UByteP&);		//RJS 18Feb99
	Bool	StoreSmkIndexData(ULong index);
	Bool	LoadSmkIndexData(ULong& index);

	Bool	DoSmokeTrailStuff;

	void	MarkBlockBeginning();
	void	MarkBlockEnd();
	void	RemoveMarks();
	Bool	SaveBlock();
	void	SkipToBeginningMark();
	void	SkipToEndMark();
	void	RemoveBeginningMark();
	void	RemoveEndMark();
	void	SkipToPreviousMark();
	void	SkipToNextMark();

	void	ResetFlags();
	void	ResetRecord();
	void	ToggleRecord();
	bool	ValidReplayFile();

//DeadCode AMM 12May99 	bool	StoreMissionConditions();
//DeadCode AMM 12May99 	bool	LoadMissionConditions();

	bool	numrecordedblocks;

	void	UpdateSeenAIData();
	void	BeginNewBlock();
	void	GetReplayFilename(char* buff);

	ULong	guncameradelay;
	ULong	SuperHeaderSize;
	Bool	LoadSuperHeader();
	Bool	LoadSuperHeaderBeginning();
	Bool	LoadSuperHeaderEnd();

	Bool	StoreSuperHeader();
	Bool	StoreSuperHeaderBeginning();
	Bool	StoreSuperHeaderEnd();

	Bool	LoadSuperHeaderID();
	Bool	StoreSuperHeaderID();

	bool	SuperHeaderStored;
	Bool	StoreBlockHeader();
	Bool	LoadBlockHeader();

	void	BackupPlaybackPosition();
	ULong	backupblock;
	ULong	backupframe;
	UWord	backupstate;
	bool	RestorePosition;
	void	RestorePlaybackPosition();
	bool	MenuViewPlayback;
//DeadCode AMM 26Feb99 	bool	MapDebriefPlayback;
	bool	MapPlayback;

	DeadStream Replay_Dead_Stream;
	ULong	GetState();
	void	SetState(ULong state);
	bool	IsCampState(ULong state);
	bool	BackupSaveGame();
	bool	RestoreSaveGame();
	bool	SaveTempSaveGame(char* name,bool pack);
	void	ResetReplayView();
	void	SetVelsAndOldVals(AirStrucPtr ac);
//DeadCode AMM 17Feb99 	bool	firstblock;
	  
	void	PreScanReplayFile();
	bool	prescan;
	ULong	TotalFrames;
	ULong	EndBlockNum;
	UWord	EndFrameNum;
	UWord	BeginBlockFrame;

	UByte	CurrPos;
	UByte	BeginMarkPos;
	UByte	EndMarkPos;

	void	CalcBeginMarkPos();
	void	CalcEndMarkPos();
	void	CalcCurrPos();

	void	UpdateSmokes();
	bool	StoreFMMass(AirStrucPtr ac);
	bool	LoadFMMass(AirStrucPtr ac);
	bool	badrecord;

	bool	prefscheck;
//DeadCode AMM 29Mar99 	UByte	PrefsInterrupt;// if prefs are selected during record then fun and games occur
//DeadCode AMM 29Mar99 	//  0=no prefs interrupt
//DeadCode AMM 29Mar99 	//	1=prefs interrupt record
//DeadCode AMM 29Mar99 	//	2=prefs interrupted non record game (i.e. we will need a super header if record begins)
//DeadCode AMM 29Mar99 	//	3=prefs interrupted a game that has recorded something but is not recording now!

//DeadCode AMM 08Jul99 	bool	clearreplaybuffers;
	void	ClearReplayBuffers();

	bool	StorePrevPosBuffer();
	bool	LoadPrevPosBuffer();
	void	InitPosBuffer();
	void	UpdatePosBuffer();

	CBuffer<COORDS3D,POSBSIZE>	PosBuffer;

	bool	ppchanged;
	bool	skipOK;

	bool	StoreHeaderEndID();
	bool	LoadHeaderEndID();
	bool	StoreSuperHeaderEndID();
	bool	LoadSuperHeaderEndID();

	bool	ReadBlock;
	bool	stopforaccel;
//DeadCode AMM 22Apr99 	bool	setpaused;
	SByte	setpaused; // 0=do nothing, 1=pause, -1 = unpause
	bool	emptyblock;

	bool	processsmokes;
	void	UpdateSmokeInfo();
	bool	BackupSmokeInfo();
	UByteP	backupsmoke;
	UByteP	tempbackupsmoke;
	ULong	smokesize;
	bool	SmokeRead(void* dest,ULong size);
	bool	StoreSmokeSize(ULong size);

	SByte	DelayedWeapon;
	void	BackupPrefs();
	void	RestorePrefs();

	struct	REPLAYPREFS
	{
		FlightDifficultyField	flightdifficulty;
		GameDifficultyField	gamedifficulty;
		SWord	autopilotskillUN;
		SWord	autopilotskillRED;
		TargetSize targetsize;
	};

	REPLAYPREFS	ReplayPrefs;

	bool	StoreTimeOfDay();
	bool	LoadTimeOfDay();

	Inst3d*	inst;

	bool	StoreCampaignStruc();
	bool	LoadCampaignStruc();

	void	TruncateTempFiles();
	void	TruncateFile(char* name);

	void	BackupGRRandomList();
	bool	LoadGRRandomList();
	bool	StoreGRRandomList();
	UWord 	BackupRndPacket [RNDPACKETSIZE];
	bool	UpdateLandscape;
	bool	DelayedGearUp;

	bool	StoreAAAList();
	bool	LoadAAAList();

	void	ResetItemAnim();

	bool	StoreArmedTransients();
	bool	LoadArmedTransients();

	bool	LoadHeader;
	bool	StoreHeader;
	void	SetTimeOfDay(int time);								//AMM 30Jun99
	bool	StopRecordFlag;										//DAW 02Jul99

	bool	FakeCollisionOn;									//AMM 12Jul99
};	

extern Replay _Replay;

#endif
