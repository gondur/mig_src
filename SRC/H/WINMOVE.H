//------------------------------------------------------------------------------
//Filename       winmove.h
//System         
//Author         Andrew McRae
//Date           Fri 9 Aug 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	WINMOVE_Included
#define	WINMOVE_Included

//RDH 15May97
//#ifdef	MAXPLAYERS
//#if MAXPLAYERS != 8
//#error	Value for maxplayers not 8
//#endif
//#else
//#define	MAXPLAYERS	8
//#endif
//RDH 15May97

#define	DEFAULT_WINMOVE 0

#include	"DOSDefs.h"	
#include	"WorldInc.h"
#include	"UniqueID.h"
#include	"transite.h"
#include	"savegame.h"
#include	"misssub.h"
#include	"3dinstr.h"
//#include	"comms.h"		//YOU CAN'T INCLUDE THESE HERE!!!!
#include	"cbuffer.h"		//Winmove is included in everything else, so now
//#include	"dplay.h"		//operating system is included throughout the project!!!
//#include	"dplobby.h"

// directX stuff

typedef struct IDirectPlay4			*LPDIRECTPLAY4A;  // directX 6.0
typedef struct IDirectPlayLobby3	*LPDIRECTPLAYLOBBY3A; // directX 6.0

// some goodies

//DeadCode AMM 10Mar99 #define MAXSERVICES 20
//DeadCode AMM 10Mar99 #define SERVICETEXTSIZE 50
//DeadCode AMM 10Mar99 #define MAXNUMSERVICENAMECHAR 50

//DeadCode AMM 10Mar99 #define MAXSESSIONS 50
//DeadCode AMM 10Mar99 #define SESSIONTEXTSIZE 20

//DeadCode AMM 12May99 #define	MAXCOMMSPACKETSIZE 2048

#define	RNDPACKETSIZE 57 // random list size + 2

//DeadCode AMM 02Jul99 #define BULTABLESIZE 16
//DeadCode AMM 02Jul99 #define COLLTABLESIZE 32
//DeadCode AMM 10Mar99 #define DAMTABLESIZE 32
#define BUFFERLENGTH		128
#define HISTBUFFERLENGTH	BUFFERLENGTH*2
//DeadCode AMM 10Mar99 #define	POSBUFFERLEN	50

#define AIPOS_SHIFT 5
#define	NUMRADIOMESSAGES 8

// actual number displayed is this-1 because need spare entry for new chat
#define NUMBUFFEREDMESSAGES 11

//DeadCode AMM 18Mar99 #define	COMMSTIMEOUT 20000
//DeadCode AMM 23Mar99 #define	COMMSTIMEOUT 10000

// packet to send control messages to aggregator
// initially based on wireplay packet
// can be modified/updated 

typedef struct _controlpacket CONTROLPACKET;
typedef struct _controlpacket* LPCONTROLPACKET;

struct _controlpacket {

	UByte opcode;
	UByte controlcode;
	UByte seqstart;
};

// packet returned from wireplay aggregator indicating position
// of players in aggregated packet

typedef struct _aggreplypacket AGGREPLYPACKET;
typedef struct _aggreplypacket* LPAGGREPLYPACKET;

struct _aggreplypacket {
	UByte opcode;
	UByte controlcode;
	UWord Address[MAXPLAYERS];
};

// packet required for resynch phase, need abs position
// damage state and score

typedef struct _acstatepacket ACSTATEPACKET;
typedef struct _acstatepacket* LPACSTATEPACKET;

struct _acstatepacket {

	ULong		PacketID;

	COORDS3D	Pos;
	ANGLES		Pitch;
	ANGLES		Heading;
	ANGLES		Roll;

	SWord		Velocity;

	UByte		MyKills;
	UByte		MyDeaths;
//DeadCode AMM 17May99 	UByte		MyFFkills;
//DeadCode AMM 17May99 	UByte		MySuicides;

	Bool		alive;
	bool		resurrect;
	bool		joining;
};


// new comms ac packet, designed for prediction purposes and wireplay.
// x, y, z, heading, pitch, roll and velocity are deltas from previous
// values.

// first section used for replay as well, dont need any frame or ack info

typedef struct	_basic_packet BASICPACKET;
typedef struct	_basic_packet* LPBASICPACKET;

struct _basic_packet {

	UByte	Shift:4;		// 4bits + overflow bits
	SByte	Velocity:4;
	UByte	X;
	UByte	Y;
	UByte	Z;
	UByte	Heading;
	UByte	Pitch;
	UByte	Roll;
	UByte	IDCode;		// 2bits for additional packet type, 6 bits info
	UByte	byte1;		// extra stuff
	UByte	byte2;		// extra stuff
	UByte	byte3;		// extra stuff
};

// for comms need frame and ack info

typedef struct _ac_packet ACPACKET;
typedef struct _ac_packet* LPACPACKET;

struct _ac_packet : public _basic_packet
{

	UByte	Count;		// increments every frame
	UByte	Ack1;		//:4;				   
	UByte	Ack2;		//:4;

};

// aggregated packet

typedef struct agg_send_packet AGGSENDPACKET;
typedef struct agg_send_packet* LPAGGSENDPACKET;

struct agg_send_packet {

// bit field represents that player is in this packet

	ULong	PlayersInPacket;
	UByte	Count;
	ACPACKET	player[MAXPLAYERS];
};

// packets sent by player to aggregator
// Done indicates packet has been received back OK and processed

typedef struct send_packet_buff SENDPACKETBUFF;
typedef struct send_packet_buff* LPSENDPACKETBUFF;

struct send_packet_buff {
	ACPACKET	packet;
	Bool		Done;
};

// aggregated packet sent by aggregator with list of 
// who has acked the packet

typedef struct aggsendpackbuff AGGBUFF;
typedef struct aggsendpackbuff* LPAGGBUFF;

struct aggsendpackbuff {

	UByte			NumPlayersInPacket;
	AGGSENDPACKET aggpack;
	Bool	Acks[MAXPLAYERS];
};

// stores ac positions, used with ACPOSENTRY to keep a
// historical record of ac positions for last 50 frames
// this is used in determining AI and AAA actions

typedef struct acposition ACPOSITION;
typedef struct acposition* LPACPOSITION;

struct acposition {

//DeadCode AMM 07Apr99 	UniqueID	ID;
	ONLYFIELD(UWord,UniqueID,ID);
	COORDS3D	Pos;
	ANGLES		Pitch;
	ANGLES		Heading;
	ANGLES		Roll;
	SWord		Velocity;
	UByte		Frame;

};

typedef struct acposentry ACPOSENTRY;
typedef struct acposentry* LPACPOSENTRY;

struct acposentry : public acposition
{
// used for various things, including indicating that 1st AIACposition packet has been sent
// and next one should be 2nd half
	UByte	extrainfo;
//DeadCode AMM 07Apr99 	UniqueID	Unfriendly;
	ONLYFIELD(UWord,UniqueID,Unfriendly);
	LPACPOSENTRY next;
};

// list of who has acked which frames, used to determine which is the
// last frame that all players have received and can therefor be used
// for AI and AAA actions

typedef struct ackbuff ACKBUFF;
typedef struct ackbuff* LPACKBUFF;

struct ackbuff {

	UByte	Frame;
	Bool	Acks[MAXPLAYERS];
};

enum CollisionCodes {

// 00 top 2 bits indicate 1st part of bullet packet

		PIDC_BULLET=0,

// 01 top 2 bits indicate coll effect
// 2 uids, next 2 top bits= type of packet
// last 4 bits = part of uid

//DeadCode AMM 11Mar99 		PIDC_KILLLAUNCHER=64,									//AMM 08Jan99
		PIDC_UIDPACKET=64,
		PIDC_SCORECLAIM=64,		// 01000000
		PIDC_WINGMANCOMMAND=80, // 01010000
		PIDC_NEXT=96,			// 01100000
//DeadCode DAW 25Jun99 		PID_LASTONE=112,		// 01110000
		PIDC_LASTONE=112,		// 01110000						//AMM 24Jun99

// 10 top 2 bits indicate collision packet

		PIDC_COLLISION=128,

// 11 top 2 bits indicate collision/special packet

//DeadCode DAW 25Jun99 		PIDC_SPECIAL=192,
//DeadCode DAW 25Jun99 		PIDC_RESURRECTEND,
		PIDC_RESURRECTEND=192,										 //AMM 24Jun99
		PIDC_RESURRECT,
		PIDC_PACKETERROR,
		PIDC_INITPACK,
//DeadCode DAW 25Jun99 		PIDC_CHEATED,
		PIDC_DUMMYPACKET,
		PIDC_PLAYERGONE,
//DeadCode AMM 18Mar99 		PIDC_WINGMANCOMMAND,
		PIDC_NEARMISS,
		PIDC_LANDEDEFFECT,
		PIDC_AERODEVICE,
		PIDC_GEAR,
		PIDC_KILLTRANS,
//DeadCode AMM 10Jun99 		PIDC_STARTACCELSELECT,
//DeadCode AMM 10Jun99 		PIDC_ACCELDESELECT,
//DeadCode AMM 10Jun99 		PIDC_STOPACCELSELECT,
		PIDC_STARTACCEL,
		PIDC_DESELECTACCEL,
//DeadCode AMM 10Jun99 		PIDC_QUITACCEL,
		PIDC_DEATHMOVEEFFECT,									//RJS 28Oct98
		PIDC_OWNERCHANGE,
		PIDC_EMPTY,
		PIDC_KILLLAUNCHER,
//DeadCode AMM 10Jun99 		PIDC_MAPACCELSELECTION,
		PIDC_PLAYERMESSAGE,
		PIDC_EXPANDMIGS,
		PIDC_EJECT,
		PIDC_SHAPECHANGE,
		PIDC_ACCELGEARUP,
		PIDC_NEWWP,
		PIDC_PLAYERMOVING,
		PIDC_PLAYERNOTMOVINGHELDAC,
// have these last for checking purposes in StorePacket
		PIDC_AIACPOSITION1,
		PIDC_AIACPOSITION2,
//DeadCode DAW 25Jun99 		PIDC_AIACPOSITION3
};

//DeadCode AMM 10Mar99 enum ACTIONTYPES
//DeadCode AMM 10Mar99 {
//DeadCode AMM 10Mar99 	ACTION_GEAR=0,
//DeadCode AMM 10Mar99 	ACTION_CHEAT
//DeadCode AMM 10Mar99 };

enum PacketType {

	PT_BULLET=0,
//DeadCode AMM 11Mar99 	PT_EFFECT=1,											//AMM 08Jan99
	PT_UIDS,
	PT_COLLISION=2,												//AMM 08Jan99
	PT_SPECIAL=3,												//AMM 08Jan99
};

enum GameTypes {
	DEATHMATCH=0,
	TEAMPLAY, 
	COMMSQUICKMISSION,
	COMMSCAMPAIGN
};

enum	TeamSides {
	TS_NONE=0,
	TS_UN,
	TS_MIGS_R_US,
	TS_COMMIE,
	TS_UNASSIGNED
};

enum CommsTimerIDS {

	TIMER_PAINTSHOP=2364,
	TIMER_ACSELECT,
	TIMER_PREFSGAME,
	TIMER_PREFSFLIGHT,
	TIMER_PREFS3D,
	TIMER_PREFS3D2,
	TIMER_PREFSVIEWS,
	TIMER_PREFSCONTROLS,
	TIMER_PREFSOTHERS,
	TIMER_READYROOM,
	TIMER_VISITORS,
	TIMER_MISSIONBRIEF,
	TIMER_FRAG,
	TIMER_RADIO,
	TIMER_MAP,
	TIMER_VARIANTS,
	TIMER_DEBRIEF

};

enum CommsPlayerStatus {

	CPS_NONE=0,
	CPS_PAINTSHOP,
	CPS_PREFS,
	CPS_READYROOM,
	CPS_3D,
	CPS_GAMESTARTUP,	// when host has selected fly
	CPS_MAP,
	CPS_VISITORBOOK,
	CPS_MISSIONBRIEF,
	CPS_FRAG,
	CPS_RADIO,
	CPS_JOINING,		// when a player attempts to join 3d
	CPS_RESYNCING,
	CPS_DEBRIEF,
	CPS_VARIANTS

};

// information needed to cause a collision

typedef struct _comms_collision COMMSCOLLISION;
typedef struct _comms_collision* LPCOMMSCOLLISION;

struct _comms_collision {

	UWord		id;
	UByte		offset;
	UByte		type;
	UByte		str;
//DeadCode AMM 07Apr99 	UniqueID hitterscorer;
	ONLYFIELD(UWord,UniqueID,hitterscorer);
};

typedef struct _scoreclaim CLAIMER;
typedef struct _scoreclaim* LPCLAIMER;

struct _scoreclaim : _comms_collision {

	LPCLAIMER	next;
	UByte	pnum;
};


typedef ULong myDPID;
typedef ULong* myLPDPID;

enum MessageCodes {
	PKILLEDBYP=0,YOUCRASHED,YOUCOLLIDEDWITHP,PCRASHED,PCOLLIDEDWITHP,
	KILLEDBYP,KILLEDP,PLEFTGAME,YOUDIED,PDIED,PCHEATED

};

// UIPlayerType Codes
#define	PLAYER_HOST 1
#define	PLAYER_GUEST 3

// record of packets sent to aggregator

typedef struct _delta_record DELTARECORD;
typedef struct _delta_record* LPDELTARECORD;

struct _delta_record {

	COORDS3D	lastpos; // SLongs

	ANGLES		Pitch;
	ANGLES		Heading; // (yaw)
	ANGLES		Roll;

	SLong		Velocity;

	UByte		SpecCode;	// as well as deltas need make sure dont lose
							// any kill or resurrect messages etc...
	UByte		byte1;
	UByte		byte2;
	UByte		byte3;

	UByte		Count;
	Bool		Done;
} ;

// received packets

typedef struct _buffer_pack BUFFPACK;
typedef struct _buffer_pack* LPBUFFPACK;

struct _buffer_pack
{
	UByte	Count;

	ACPACKET	PlayerData[MAXPLAYERS];
	Bool 	Received[MAXPLAYERS];

};

typedef struct _hist_buff	HISTBUFF;
typedef struct _hist_buff*	LPHISTBUFF;

struct _hist_buff 
{
// this position has been received ok

	bool		OK;

// historical position

	COORDS3D	Pos;
	ANGLES		Pitch;
	ANGLES		Heading;
	ANGLES		Roll;
	SWord		Velocity;
	UByte		Frame;

// deltas for recalculating position

	ACPACKET	deltas;
};

// list of packets received, used to ack packets

typedef struct _reclist RECLIST;
typedef struct _reclist* LPRECLIST;

struct _reclist
{
	UByte	packet;
};

// stores bullet/missile/fuel etc launches

typedef struct _bul_entry BULENTRY;
typedef struct _bul_entry* LPBULENTRY;

struct _bul_entry
{
	ULong num;
	ULong index;
	ULong framelaunched;
};

// dplat service provider list

typedef struct _enum_service ENUMSERVICE;
typedef struct _enum_service* LPENUMSERVICE;

struct _enum_service
{
	GUID	sid; 	//service ID
	char*	sname;	//service name
	UByte*	connection;	//connection info buffer
	ULong	connsize;	//connection info buffer size


	LPENUMSERVICE Next;
};

// dplay session list

typedef struct _enum_session ENUMSESSION;
typedef struct _enum_session* LPENUMSESSION;

struct _enum_session
{
	char*	sname;	//service name

	LPENUMSESSION Next;
};

// visitor book information

typedef struct _visitor_info VISITORINFO;
typedef struct _visitor_info* LPVISITORINFO;

struct _visitor_info
{
	char*	vis_name;	// visitors name
	Bool	vis_status;	// set TRUE if visitor can join game
	LPVISITORINFO	next; // next visitor
};

// any other effect that needs transmitting

typedef struct _special_packet SPECPACKET;
typedef struct _special_packet* LPSPECPACKET;

struct _special_packet
{
	ULong	ID;

	UByte	spec1;
	UByte	spec2;
	UByte	spec3;
};

typedef struct	uidpacket UIDPACKET;
typedef struct	uidpacket* LPUIDPACKET;

struct uidpacket
{
	UByte	 IDCode;
//DeadCode AMM 07Apr99 	UniqueID uid1;
//DeadCode AMM 07Apr99 	UniqueID uid2;
	ONLYFIELD(UWord,UniqueID, uid1);
	ONLYFIELD(UWord,UniqueID, uid2);
};

typedef struct _chatmessage CHATMESSAGE;
typedef struct _chatmessage* LPCHATMESSAGE;

struct _chatmessage
{
	char	chat[128];
	char	name[32];
};

//DeadCode AMM 10Mar99 typedef struct _id_node IDNODE;
//DeadCode AMM 10Mar99 typedef struct _id_node* LPIDNODE;
//DeadCode AMM 10Mar99 
//DeadCode AMM 10Mar99 struct _id_node
//DeadCode AMM 10Mar99 {
//DeadCode AMM 10Mar99 	LPIDNODE	next;
//DeadCode AMM 10Mar99 	UniqueID id;
//DeadCode AMM 10Mar99 };


struct	H2HPlayerInfo;
struct	H2HPlayer;
class DPlay {

public:
	DPlay::DPlay ();
	DPlay::~DPlay ();

// direct play specific vars

	LPENUMSERVICE	ServiceList; // list of dplay services with names and ids
	LPENUMSESSION	SessionList; // list of dplay session names
	LPDIRECTPLAY4A lpDP4;				// oo look DirectX 6
	LPGUID	lpAppGuid;					// Global GUID Number

	char* tempdpsessdesc2;

	LPDIRECTPLAYLOBBY3A	lpDPL;		//DirectPlay Lobby

	char* templpDPC;

// direct play specific funcs

	Bool	InitDirectPlay ();
	void	ExitDirectPlay();
	Bool UIMultiPlayInit ();	// Main Menu
	Bool UISelectServiceProvider(char* servicename);
	bool UIGetSessionListUpdate ();
	void UIAssignServices();
	void DeleteServiceList();
	void DeleteSessionList();

// this players data vars

	Bool	PlayerCreated;		// Ok to send messages (Player Created)
	Bool	Implemented;		// DirectPlay/Session/Player Flag
	Bool	Host;				// True if this machine is host, else guest
	Bool	ServedGame;
	ULong	UIPlayerType;		// Host or Guest, for UI Only
	ULong	MyTeamKills;		
	ULong	MyTeamDeaths;
//DeadCode AMM 17May99 	ULong	MyTeamFFKills;
	ULong	EnemyTeamKills;		
	ULong	EnemyTeamDeaths;
//DeadCode AMM 17May99 	ULong	EnemyTeamFFKills;
	myDPID	aggID;					// aggregator ID
	myDPID	myDPlayID;				//dplay id/wplay id
	ULong	mySlot;	// players position in h2h_player struc, alloc packet
					// aggregated packet etc (everything in fact)
	myDPID	playergroupID;

// make acks buffer bigger to cope with resent packets

//DeadCode AMM 07Jul99 	CBuffer<RECLIST,BUFFERLENGTH> RecPackBuffer;
	CBuffer<RECLIST,BUFFERLENGTH*2> RecPackBuffer;
	CBuffer<SENDPACKETBUFF,BUFFERLENGTH> SendPackBuffer;

	Bool		SentStopResetMess;

// game data

// circular buffer to store ac packets. 

	CBuffer<BUFFPACK,BUFFERLENGTH> PacketBuffer;

// historical buffer for AAA

//DeadCode AMM 23Mar99 	CBuffer<ACPOSITION, HISTBUFFERLENGTH> HistPosBuffer[MAXPLAYERS];
	CBuffer<HISTBUFF, HISTBUFFERLENGTH> HistPosBuffer[MAXPLAYERS];

	void	UpdateHistBuffer(LPACPACKET Packet,ULong slot);
	void	AddPacketToHistBuffer(LPACPACKET Packet,ULong slot);

// this frames deltas

	DELTARECORD	Deltas;

// collision stuff

//DeadCode AMM 02Jul99 	CBuffer<COMMSCOLLISION,COLLTABLESIZE> CollBuffer;
	CBuffer<COMMSCOLLISION,BUFFERLENGTH> CollBuffer;			//AMM 02Jul99
	LPCLAIMER HSB;// hitterscorerbuffer

	void	NewCollision2 (UWord id, UByte offset, UByte hitbox, UByte typeandstr, UniqueID hitterscorer);
	Bool TestForCollision (LPCOMMSCOLLISION);

// special packet

//DeadCode AMM 02Jul99 	CBuffer<SPECPACKET,COLLTABLESIZE> SpecBuffer;
	CBuffer<SPECPACKET,BUFFERLENGTH> SpecBuffer;				//AMM 02Jul99

	Bool TestForSpecial(LPSPECPACKET);
	void NewSpecial(ULong id,UByte byte1, UByte byte2, UByte byte3);

// bullet stuff

	void	NewBullet (ULong num, ULong index);
	Bool TestForBullet (LPBULENTRY);
//DeadCode AMM 02Jul99 	CBuffer<BULENTRY,BULTABLESIZE> BulletBuffer;
	CBuffer<BULENTRY,BUFFERLENGTH> BulletBuffer;				//AMM 02Jul99

// for collision effects (killlauncher calls)

//DeadCode AMM 11Mar99 	CBuffer<UniqueID,COLLTABLESIZE> EffectBuffer;
//DeadCode AMM 11Mar99 	Bool	TestForEffect(LPSPECPACKET);
	void	NewKillLauncher(UniqueID id);
	void	ProcessKillLauncher(LPBASICPACKET p);

//DeadCode AMM 02Jul99 	CBuffer<UIDPACKET,COLLTABLESIZE> UIDSBuffer;
	CBuffer<UIDPACKET,BUFFERLENGTH> UIDSBuffer;					//AMM 02Jul99

// UI vars

	Bool 	FlyNowFlag;

	CBuffer<CHATMESSAGE,NUMBUFFEREDMESSAGES> ChatBuffer;

// UI funcs

	Bool UINetworkSelectFly ();
	Bool UINewPlayer (char*,char*);

//DeadCode AMM 15Apr99  	Bool SendMessageToAll (char* Data, ULong Length);
//DeadCode AMM 15Apr99 	Bool SendMessageToPlayers (char* Data, ULong Length);
	bool SendGMessageToPlayers (char* Data, ULong Length);
	bool SendGMessageToPlayersTimeout (char* Data, ULong Length);
//DeadCode AMM 15Apr99 	Bool SendMessage(char* data, ULong len, ULong to);

 	Bool SendMessageToAll (void* Data, ULong Length);
	Bool SendMessageToPlayers (void* Data, ULong Length);
	Bool SendMessage(void* data, ULong len, ULong to);

		#ifdef	MISSSUB_Included
		void UILeavingMainSheet ();
		void UISendInPaintShopMessage ();
		void UISendInPrefsMessage ();
		void SendInFragMessage();
		void SendInMapMessage();
		void SendInMissionBriefMessage();
		void SendInRadioMessage();
		void SendInReadyRoomMessage();
		void SendInVisitorsBookMessage();
		void SendInDebriefMessage();
		void UISendDialogue (const char*);
		#ifdef	SAVEGAME_Included
		void UIUpdateMainSheet ();
		Bool UISendPrefs (bool request); //Bool final); //SaveData* Save_Data, SWord, SLong, Bool);
		#endif
		#endif
	Bool GetMySlot();
	Bool SendSlot(myDPID playerid, ULong slot);
	SLong GetNextAvailableSlot();
//DeadCode AMM 16Jun99 	void 	AddStatusBar(Bool reset,ULong playerid);
	void	InitH2HPArray();

// general stuff

	bool	viewtime;
	ULong	accelselected;		// indicates which players have selected time accel
	ULong	deadplayers;		// indicates whether player is dead or alive
	Bool	ResyncPhase;
	Bool	WorldSyncPhase;
	bool	WorldSyncPhaseReady;
//DeadCode AMM 18Mar99 	ULong	wsrgot;
	Bool	Initiator;
//DeadCode DAW 28Oct99 	char	LobbyIPAddress[128];	//needed for joining a lobbied game over internet
	char 	SessionName [SESSIONNAMELEN];	// Session Name
	char	ServiceName[256];	//serviceprovider
	char	PlayerName[PLAYERNAMELEN];	//players name
	char	Password[PASSWORDNAMELEN];		//password for session
	char	GameName[256];		//name of battlefield
	char	Messages[MAXPLAYERS][NUMRADIOMESSAGES][RADIOMESSAGELEN];		
	UByte	RateDivider;		// data rate divider
	UByte	FrameInc;			// same as data rate divider - number of frames in each send/receive cycle
	Bool	firsttimein;		// used to initialise stuff on entry to 3d
	Bool	realfirsttimein;
	Bool	synched;			// true is all players are synched with aggregator
//DeadCode AMM 16Apr99 	Bool	nojunk;
	bool	csync;	// comms is synched
	GameTypes	GameType;			// co-operative/teamplay/deathmatch
	Bool	Side;				// TRUE if UN, FALSE if red
	bool	SideSelected;
	ULong	CurrPlayers;		// No. of players in the session
	ULong AllocPacket [MAXPLAYERS];	// [n]=UniqueID referenced by mySlot
	ULong	SuicideTime;	// time at which suicide is allowed (5 secs after death)
	Bool	AllowSuicide;
	static H2HPlayerInfo H2H_Player[MAXPLAYERS];	// holds info about players
	UByte	FrameCount;		// Frame count (3 csecs)
//DeadCode AMM 10Mar99 	UByte	PFrameCount;
	ULong ActivePlayers;
	ULong SyncBits;	// bitfield, bit set (1 << players mySlot) when received
	Bool	AllowJoins;

	Bool SendPacketToAggregator(LPACPACKET lpAcPacket);
	void SendGonePacket();
	void CommitSuicide();
	Bool Synchronise ();
	void InitRecBits ();
	void ResurrectMe (AirStrucPtr ac, bool suicide);
	void SetScore (AirStrucPtr victim, ItemPtr killer);			//AMM 01Sep98
	void ResurrectAircraft (AirStrucPtr, Bool);
	void RepairAircraft (AirStrucPtr);
	void InitResurrect (AirStrucPtr);
 	void ProcessPlayerGone(ULong player,Bool in3d); //,ULong& update);
//DeadCode AMM 10Mar99 	void EndGame(); // stops game and returns to main sheet
	void PredictMove(AirStruc* ac);
	void AddDeltas(AirStruc* AC, Bool sign);
	UByte 	MakeShiftValue();
	Bool 	ReceiveFromAggregator(LPAGGSENDPACKET packet);
//DeadCode AMM 10Mar99 	Bool	PlayerIsInMyTeam(myDPID GameID);
	void	SendNeedResyncMessage();
	void	ResetState();
	void	SendResyncMessage();
	void	BeginSyncPhase();
	Bool	ReceiveSyncPackets();
	Bool	CreateDPlayInterface();

	void	CopyBuffer(char* dest, char* src, ULong size);

	void	CalcNewAbsPos();
	void	PredictGoodMovement(UWord slot);

	Bool	InitSyncPhase();
	Bool	SecondSyncPhase();
	void	InitGameVars();
	void	MakeAndSendPacket();
	void	SetRandomList();
	
	Bool	ProcessPlayerMessage(char* message,ULong size,ULong from,UByte ctrl);
	Bool	ProcessSystemMessage(char* message,UByte ctrl);
	
	void ProcessDeltaPacket (LPACPACKET Packet,ULong playerID);
	void ProcessExtraPacket (LPACPACKET Packet,ULong playerID);

	void StorePacket (LPAGGSENDPACKET packet);
	void MakeDeltaPacket (LPBASICPACKET packet);
	void MakeExtraPacket (LPBASICPACKET packet, Bool replay);

	void MakeCollPacket (LPCOMMSCOLLISION, LPBASICPACKET lpAcPacket);
	void UpdateDeltas(LPACPACKET lpAcPacket);
	void UpdatePredictedAC(LPACPACKET lpAcPacket);
	void MakeSpecPacket(LPSPECPACKET, LPBASICPACKET);

	void	CountPlayers();
	Bool	UISendFlyNow();
	Bool	UIUpdatePrefs();
	void	InitMainSheetInfo();
	Bool	ConnectToAggregator(ULong& aggregatorID,char* Name);

	void	ProcessInfoPackets();

	CBuffer<ACKBUFF,BUFFERLENGTH> RecAckBuffer;

	void	UpdateAckBuffer(LPAGGSENDPACKET packet);
	void	SetUpPlayersAC();
	Bool	JoinGame();
	void	AddPlayerToGame(ULong pid,ULong actype,ULong id);
	void	IsGameAvailable();
	void	SendGameAvailableMessage(Bool available);

	Bool	GameAvailable;
	ULong	ResendTime;

	Bool	Joining;
	void	SendEnteringGameMessage();
	Bool	gotfullpacket;

	ULong	sendtowho; // 0-7 player slot, 128=all, 255=my team
//DeadCode AMM 22Feb99 	ULong	oldsendtowho; //  for when player to talk to is deselected

	void	InitBuffers();
	void	BeginAggregation();
	Bool	SendAllocPacket();
	void	ResetDeltas();
	void	ProcessDamagePacket(LPACPACKET packet, ULong player, ItemBasePtr lpOpAc);
	void	ProcessCollisionPacket(LPBASICPACKET packet,ULong fromplayerslot);
	void	ProcessSpecialPacket(LPBASICPACKET packet, AirStrucPtr AC,ULong slot);

//DeadCode AMM 10Mar99 	Bool	junkpacket;
	SLong	GetVal(UByte src,UByte shift);
	Bool	Lobbied;

//DeadCode DAW 29Oct99 	Bool	LaunchedByLobby();
	Bool	LaunchedByLobbyCheck();
	Bool	ConnectToLobby();
	Bool	FinishLobbySetup();

	bool	PossibleLobby;

	void	SetRandomListPos();
	Bool	StartCommsSession();
	Bool	SetUpPlayerInfo(char* name);

	LPVISITORINFO	VisitorsBook;
	void	AddNameToVisitorsBook(char* name);
	void	RemoveNameFromVisitorsBook(char* name);
	void	ToggleVisitorStatus(char* name);
	void	SendUpdateToVisitorsBook(char* name,Bool status);

//DeadCode AMM 16Jun99 	void	LaunchEmpireLobby();
	Bool	PossTransmitColl(ItemPtr item,ItemPtr target,SLong&);//AMM 08Jan99

	void	DeleteLobbyInfo();
//DeadCode AMM 16Jun99 	void	RegisterApp();

	Bool	GameRunning;
	void	RunAggregatorFromReadyRoom();

	void	DeleteVisitorBook();

	void	NewNearMiss(AirStrucPtr trg, AirStrucPtr hitter);
	void	ProcessNearMiss(LPBASICPACKET,AirStrucPtr);
	void	MakeBulletPacket(LPBULENTRY bulpack, LPBASICPACKET packet);
	void	ProcessBulletPacket(LPBASICPACKET pack, AirStrucPtr AC);

	void	CheckPassword(char* pword,char* name,ULong player);
	Bool	SetUpPlayer();
	Bool	AttemptToJoin();

	Bool	SlotFree(int pos,int squadron);
	Bool	AllPlayersHaveSlots();

	void	DisplayReadyDialogue(char* name, char* text);
	void	DisplayFragDialogue(char* name, char* text);
	void	DisplayPlayerInfo();

	Bool	MainSheetCount;
//DeadCode AMM 12May99 	Bool	ReceiveNextMessage(char* Data, ULong& Length, ULong& from);
	Bool	ReceiveNextMessage(char*&Data, ULong& Length, ULong& from,ULong& to,ULong flags);
	void	ProcessAggregatedPacket(char* packet);

	UByte	SyncPacks[MAXPLAYERS];
//DeadCode AMM 13May99 	void	CheckSystemMessageQ();
	void	CopyPacket (ItemBasePtr lpItemBase, LPACPACKET lpAcPacket);

	COORDS3D* GetGoodACPosition(ItemBasePtr ac);
//DeadCode AMM 16Jun99 	COORDS3D* GetGoodACPosition(UniqueID id);
//DeadCode AMM 16Jun99 	COORDS3D* GetACPositionForAAA(AirStrucPtr ac);
//DeadCode AMM 16Jun99 	COORDS3D* GetACPositionForAAA(UniqueID id);

	ItemPtr GetScoreHitter(ItemPtr thingy);

	void	NewGearThingy(SWord val);
	void	ProcessGearThingy(LPBASICPACKET packet, AirStrucPtr ac);

	void	NewAeroDevAction(UByte devID,UWord);
	void	ProcessAeroDevAction(LPBASICPACKET packet, AirStrucPtr ac);

//DeadCode AMM 13Apr99 	void	SendKillTransientsMessage(ULong frame);
//DeadCode AMM 13Apr99 	void	KillPlayersTransients(LPBASICPACKET p, AirStrucPtr ac);
	void	SendKillTransientsMessage();
	void	KillPlayersTransients(AirStrucPtr ac);

	void	ProcessPlayerSlotRequest(char* message,ULong from,UByte ctrl);
	Bool	SendSlotRequest(int, int);
	Bool	ReceiveSlotRequestOK();
	void	ProcessSlotInfoUpdate(char* pack);
	Bool	GetGameDetails();
	void	SendGameDetailsRequest();
	Bool	ReceiveGameDetails();
	void	SendGameDetails();

	UByte	GameIndex;

	void	FillCSQuickStruc();
	Bool	UpdatePlayerInfo();
//DeadCode AMM 13May99 	void	SendMyPlayerInfo();
	bool	SendMyPlayerInfo(bool request);
	void	QuitFromReadyRoom();

	void	ResetDeadPlayers(AirStrucPtr ac);
//DeadCode AMM 10Jun99 	void	SendStartAccelSelectedMessage();
//DeadCode AMM 10Jun99 	void	ProcessStartAccelSelectedMessage(LPBASICPACKET p,ULong slot);
//DeadCode AMM 10Jun99 	void	ProcessStopAccelSelectedMessage(LPBASICPACKET p,ULong slot);
//DeadCode AMM 10Jun99 	void	SendAccelDeselectedMessage();
//DeadCode AMM 10Jun99 	void	ProcessAccelDeselectedMessage(LPBASICPACKET p,ULong slot);

	void	SendStartAccelMessage();
	void	ProcessStartAccelMessage(ULong slot);
	void	SendQuitAccelMessage();
	void	ProcessQuitAccelMessage(ULong slot);

	void	ProcessPrefsPacket(char* pack);

	void	CheckPacketSizes();
	void	GetBattlePosition(UByte slot);
//DeadCode DAW 27Jun99 	void	GetBattlePosition();
	Bool	JustJoined;
	Bool	LeaveCommsFlag;
	Bool	HostQuitFlag;

	Bool	SwitchPlayerACToAIAC(AirStrucPtr AC);
	Bool	SwitchAIACToPlayerAC(AirStrucPtr AC, ULong slot);
	void	FillHistBuffer(AirStrucPtr ac, ULong slot);
	Bool	SimulateExitKey;

//DeadCode AMM 18Mar99 	void	NewWingmanCommand(ULong messnum, UByte command);
	void	NewWingmanCommand(UByte decision, UByte command, UniqueID trg);
//DeadCode AMM 18Mar99 	void	ProcessWingmanCommand(LPBASICPACKET packet);
	void	ProcessWingmanCommand(UniqueID id1, UniqueID id2, ULong slot);

	void	Process1stAIACPositionPacket(LPBASICPACKET p,UByte slot);
	void	Process2ndAIACPositionPacket(LPBASICPACKET p,UByte slot);
	void	Process3rdAIACPositionPacket(LPBASICPACKET p,UByte slot);
	void	Make1stAIACPositionPacket(LPACPACKET p);
	void	Make2ndAIACPositionPacket(LPACPACKET p);
	void	Make3rdAIACPositionPacket(LPACPACKET p);
	void	AddAIACToPositionList(AirStrucPtr AC);
	void	DeleteMyAIACPositionToSendList();
	void	UpdateACFromPositionList(LPACPOSENTRY p);
	void	PutAIACInReadyState(UniqueID id);

// used when AI AC has finished combat and a position update is being sent to other players. 
// Possibly more than one AC per player - but only one will be sent at a time (but there could
// be bloody packet loss!!)
	LPACPOSENTRY	AIACPositions[MAXPLAYERS];
	void	DeleteAIACPositionsList();
	void	DeleteEntryFromAIACPositionsList(LPACPOSENTRY p,UByte slot);

// list of AI AC that I need to send positions for.
	LPACPOSENTRY	MyAIACPositionsToSend;

	Bool	UpdateFrag;
	Bool	UpdateMission;
	bool	FragChanged;

	void	SendCSQuickStrucToPlayers(Bool init);
	void	GetCSQuickStruc();
	void	UpdateCSQuick(UByte* pack,ULong num);
	void	SendCS(UByte* info, ULong size, Bool init);
	Bool	GetCS();
	void	SendCSRequest();

	void	SendACDetails();
	Bool	GetACDetails();
	void	SendMobDetails();
	Bool	GetMobDetails();
	void	SendItemDetails();
	Bool	GetItemDetails();
	Bool	SyncCommsWorld();
	void	MakeAnimPack(ULong num,UByteP pack,ShapeNum shape);
	void	ProcessAnimPack(UByteP pack,ItemPtr item);
	Bool	GetNumAnims(ULong type,ULong& num);
	Bool	GetAllAnims(ULong type, ULong need, ULong& got);
	void	SendNumAnims(ULong num,ULong type);
	void	SendAnimData(ULong type,ULong num,UniqueID id);
	Bool	GetSyncData(ULong type,ULong num,ULong& got);
	void	ProcessACData(UByteP pack);
	void	ProcessMobData(UByteP pack);

//DeadCode AMM 23May99 	void	SendMyMessages();
	bool	SendMyMessages(bool request);
	void	ReceiveMessages(UByteP p,ULong from);
	void	SendGotWorldMessage();
	void	SaveRadioMessages();
	Bool	LoadRadioMessages();		//rdh 10/1/99
	void	InitMessages();
//rdh10/1/99	void	InitMessages();
	bool	UpdateMessages();

	Bool	DisplayInfo;
	void	DisableJoins();
	void	EnableJoins();

	void	OwnerChange(ULong newownerid, AirStrucPtr AIAC);
	void	ProcessOwnerChange(LPBASICPACKET p);
	void	InitialiseOwners();
//DeadCode AMM 08Jun99 	void	GetOwner(AirStrucPtr AIAC);
	AirStrucPtr NextCommsOwner;
	bool	AmOwner(AirStrucPtr ac);
//DeadCode AMM 08Jun99 	void	UpdateCommsOwner();
	void	OwnerChangeDecision(AirStrucPtr me, AirStrucPtr him);
	void	SelectPlayerToChatTo(ULong player);
	void	SelectPlayerToChatTo(ULong position, ULong squadron);
	void	ResetAllocPacket();

	void	ProcessBFieldInfo(char* info,ULong& bfctrl, FileNum& filelist);
	void	SendBFieldsToPlayers(bool request);

	bool	ReceiveBFieldInfo();

	void	ResetCommsGame();
	void	ExitCommsAndReplay3D();
	void	CommsMessage(unsigned int mess);

//DeadCode AMM 08Jun99 	void	ForceAIACPosResync();

	Bool	UpdateMissionConditions();
	Bool	SendMissionConditions(bool request);
	void	ProcessConditionsPacket(char* message);

	void	DisplayPlayerJoiningMessage(ULong slot);
	void	DisplayResyncingMessage();
	void	DisplayResyncOKMessage();

//DeadCode AMM 12May99 	void	SendSaveGame(bool score=false);
	bool	SendSaveGame(bool score, bool startup);
	bool	ReceiveSaveGame(bool startup,ULong num,ULong size);
	bool	ReceiveStartupSaveGame(bool realstartup);
	void	UpdateSaveGame(UByte* savegamedata,char* data);
	bool	SaveDummyCommsSaveGame(UByte* data,ULong size);

	void	GetCommsSavename(char* b);
	void	GetLastSaveName(char* b);
	bool	LoadDummySavegame(char* name);

	bool	singlesession;// if service provider is serial/modem or tcp
						// then should be only one session to connect to
						// dont bother enumerating sessions
	Bool	JoinComms();
	Bool	FindGoodSession();

	bool	campaignloaded;
	bool	megashootcheat;
	bool	invulnerablecheat;
	bool	liftcheat;
	bool	firstdeathcall;
	char*	GetPlayerMessage(ULong index);
	char*	GetPlayerName(ULong);								//RJS 22Mar99
	ULong	GetPlayerNumber(ULong);								//RJS 22Mar99
	ULong	lasttime;
//DeadCode AMM 07Jul99 	ULong	dodgytime;

//DeadCode AMM 08Jun99 	void	ChangeACType();
//DeadCode AMM 08Jun99 	bool	changeacflag;
//DeadCode AMM 17Jun99 	inline ULong ID2Slot(ULong id);
	inline ULong DPID2Slot(ULong id);
	inline ULong UID2Slot(UWord id);

	void	AddHitterScorer(UByte pnum,LPCOMMSCOLLISION coll);
	ItemPtr	GetHitterScorer(SLong uniqueid,SLong element,SLong hittype,SLong hitstrength,UByte pnum);
	void	NewScoreClaim(ItemPtr hitterscorer,UniqueID trg);
	void	ProcessScoreClaim(UniqueID hitterid,UniqueID trgid);

	bool	TestForUIDSPacket(LPSPECPACKET s);
	void	MakeUIDSPacket(LPSPECPACKET s,LPBASICPACKET p);
	void	ProcessUIDSPacket(LPBASICPACKET p,ULong slot);
	void	NewUIDSPacket(UniqueID id1,UniqueID id2,UByte code);
	void	GetUIDSFromPacket(UniqueID& id1, UniqueID& id2,LPBASICPACKET p);
	void	DeleteClaimBuffer();

	// 0=not resent, 1=resent 1/4 , 2=resent 1/2
	UByte	ResendStatus;
	UByte	ResendPacket;

	void	DisplayPlayerSelectedTimeAccelMessage(ULong slot,bool on);
	void	DisplayPlayerDeselectedTimeAccelMessage(ULong slot);

//DeadCode AMM 10Jun99 	void	SendMapAccelSelection(UByte sel);
//DeadCode AMM 10Jun99 	void	SendMapAccelSelection();
//DeadCode AMM 10Jun99 	void	ProcessMapAccelSelection(LPBASICPACKET p);
//DeadCode AMM 15Mar99 	UByte	mapaccelselection;
//DeadCode AMM 10Jun99 	bool	commsaccel;
//DeadCode AMM 10Jun99 	bool	commsaccelpsend;

	struct	SYNCDATA
	{
		bool	resettime;
		bool	sentinfo;
		ULong	wsmneeded;
		ULong	wsmgot;
		UByte	stage;
		ULong	wsrneeded;
		ULong	wsrgot;

		ULong	itemstage;

		ULong	mobstage;

		ULong	acstage;

		ULong	deadstage;
	};

	SYNCDATA	SyncData;
	void	InitSyncData(bool startup);

	void	CalcVels(UByte slot=0,UByte pframes=0);

	UByte	velcounter;

	void	NewPlayerMessage(UByte message);
	void	ProcessPlayerMessage(LPBASICPACKET p, ULong slot);
	void	DisplayPlayerMessage(ItemPtr victim, ItemPtr hitter, UByte script_type,UByte messnum=0);

	enum	Script_Type
	{
		ST_PLAYERKILLEDCOMMS=0,
		ST_PLAYERKILLEDPLAYER,
		ST_PLAYERKILLEDFRIENDLY,
		ST_PLAYERKILLEDENEMY,
		ST_PLAYERLEFTGAME,
		ST_PLAYERJOINEDGAME,
		ST_PLAYERJOINING,
		ST_PLAYERSELACCEL,
		ST_PLAYERDESELACCEL,
		ST_PLAYERMESSAGE
	};

	ULong	CommsTimeoutLength; // in ms

	bool	MsgRecipientAll;

	void	SendEndGameScore();
	void	ReceiveEndGameScore();

	void	SendExpandMigsMessage(UniqueID mig);
	void	ProcessExpandMigsMessage(LPBASICPACKET p);

//DeadCode AMM 19Apr99 	void	CommsGameSync();
	bool	CommsGameSync();

	void	ProcessEjectMessage(AirStrucPtr ac);
	void	ProcessGuestLeavingMessage(ULong from);

	void	NewShapePacket(UWord,UWord);						//RJS 21Apr99
	void	ProcessNewShapePacket(LPBASICPACKET);				//RJS 21Apr99
	UByte	CommsKiller;
	void	ProcessResyncPacket(LPACSTATEPACKET,ULong);
	UByte	resyncsgot;
	bool	RestartWorldSync;
	void	SendRestartWorldSyncMessage();
	void	SendDeadStream();
	bool	GetDeadStream();
	bool	GetNumDeadBlocks(ULong& num,int& dtime);
	bool	GetAllDeadBlocks(ULong need, ULong& got);

	void	SendPilotsStatus(bool single,int pilot=0);
	bool	GetPilotsStatus();
	void	ProcessPilotStatusPacket(bool single,UByteP p);

	UByte	BackupPilots[PILOTS_PER_CAMPAIGN];
	void	ApplyBackupPilots();

	char*	CommsPacketPtr;
	ULong	CommsPacketLength;

	bool	SendCampaignStruc(bool startup);
	bool	ReceiveCampaignStruc();

	void	ClearPackages();
	bool	ResetSync;
	bool	beginsyncflag;
	bool	resetreceivesync;
	void	InitialFlagReset();

	UByte	GetAccelNumber();
	void	SendAccelGearUpMessage();
	void	ProcessAccelGearUpMessage();

	enum AccelTypeComms
	{
		ACCEL_NONE=0,
		ACCEL_FORWARD,
		ACCEL_NEXTWP,
		ACCEL_MESSAGESUBJECT,
		ACCEL_MISSIONIP,
		ACCEL_HOME,
		ACCEL_WP_NEXTWP,
		ACCEL_WP_HIGHLIGHTED_WP
	};

	AccelTypeComms	AccelComms;
	ULong			Accelhilight;

	void	NewWPMessage(UniqueID wp);
	void	ProcessNewWPMessage(LPBASICPACKET p);

	bool	PlayerSync;
	void	SendDeselectAccelMessage();
	void	ProcessDeselectAccelMessage(ULong slot);

	bool	network;

	void	SendAAAList();
	bool	GetAAAList();
	void	ProcessAAAPacket(char* packet);
	void	SendBackupRandomList(bool request);
	void	ProcessRandomList(char* packet);
	bool	GetRandomList();
	bool	HostQuit;

	void	NewPlayerMoving();
	void	ProcessPlayerMoving();

	enum PlayerNotMove
	{
		HELDACCHECK=0,
		AUTOLANDING1,
		AUTOLANDING2

	};

//DeadCode DAW 28Jun99 	void	NewPlayerNotMovingHeldAC(UniqueID ac);
	void	NewPlayerNotMovingHeldAC(UniqueID ac,UByte type);	//DAW 28Jun99
	void	ProcessNewPlayerNotMovingHeldAC(LPBASICPACKET p);
	bool	resurrectend;

	SByte	joiningplayerslot;
	void	ResetCommsSurfaces();								//DAW 28Jun99

	bool	resyncbar;
	void	ExpandAggPacket(LPAGGSENDPACKET, LPAGGSENDPACKET);

	void	AddChatMessageToBuffer(const char*,const char*);
	void	UpdateChatBox();
	Bool 	LobbyConnect();

	DELTARECORD	DeltasToApply[MAXPLAYERS][6];// 6 is max data rate for Mig
	UByte		DeltaIndex;
	void		ApplyPartialDeltas();
	void		AddDeltasToApply(LPACPACKET, ULong);

	UWord	BFieldToProcess;
	void	StoreReceivedBField(char*, ULong);
	bool	ProcessRequiredBFieldPacket(ULong& bfctrl, FileNum& filelist);
	void	Process_PM_CSStruc(char*);
};

extern DPlay _DPlay;

void SendInitPacket ();
void SendInit2Packet ();

#endif
