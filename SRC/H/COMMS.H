//------------------------------------------------------------------------------
//Filename       comms.h
//System         
//Author         Andrew McRae
//Date           Mon 23 Sep 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	COMMS_Included
#define	COMMS_Included
class	UIComponent;
typedef	class	UIComponent	*UIComponentPtr;
class	StringWBComp;

#define	DEFAULT_COMMS 0

struct H2HPlayerInfo
{
	ULong	dpid;
	char	name[60];			//name[SaveData::NAMEARRAYSIZE];
	char	squadron;			//0 to 5 of pilotable aircraft, see flyinit.h
	char	position;			//0 to 15 aircraft in flight
	char	dialogue[100];		//dialogue[MAXNUMOFDIALOGUECHARS];
	SWord	status;
	SWord	kills;
	SWord	deaths;
//DeadCode AMM 17May99 	SWord	ffkills;
	ULong	MyTeam;				// team number
	UByte	decal;
};

// Fields common to all data packets

typedef struct CommonData COMMONDATA;
typedef struct CommonData* PCOMMONDATA;

struct CommonData
{
	ULong	PacketID;	
	ULong	PlayerID;
	ULong	Slot;												//AMM 10Feb97
};


// User Interface Player Details
typedef struct _uiplayerdata UIPLAYERDATA;
typedef struct _uiplayerdata* PUIPLAYERDATA;
struct _uiplayerdata : public CommonData
{
	H2HPlayerInfo playerinfo;

};

// id lookup table packet

typedef struct _lookuptable UILOOKUPTABLE;
typedef struct _lookuptable* PUILOOKUPTABLE;

struct _lookuptable : public CommonData
{
// IDLookup table
	ULong	Table[MAXPLAYERS];
};

typedef struct _initinfo INITINFO;
typedef struct _initinfo* PINITINFO;

struct _initinfo : CommonData
{
	char	Name[21];
	ULong	ID;
};

typedef struct	_gameavailable GAMEAVAILABLEPACKET;
typedef struct	_gameavailable* PGAMEAVAILABLEPACKET;

struct _gameavailable : CommonData
{
	Bool	available;
};

typedef struct _password PASSWORDPACK;
typedef struct _password* LPPASSWORDPACK;

struct _password : CommonData
{
	char	name[60];
	char	pword[10];
};

typedef struct _slotpos SLOTPOSPACK;
typedef struct _slotpos* LPSLOTPOSPACK;

struct _slotpos : CommonData
{
	char	squadron;
	char	position;
	UByte	packer;		// so that packet isnt same size as ACPACKET
};

typedef struct _gamedetails GAMEDETAILS;
typedef struct _gamedetails* LPGAMEDETAILS;

struct _gamedetails : CommonData
{
	UByte	DataRate;
	UByte	GameType;
	UByte	GameIndex;
	char	GameName[60];
};

typedef struct _csquickstruc CSQUICKSTRUC;
typedef struct _csquickstruc* LPCSQUICKSTRUC;

struct _csquickstruc : CommonData
{
	ULong	newmissionnum;										//AMM 07Dec98
	char	csquick[500];	// this should be big enough
};

typedef struct _savegamep SAVEGAMEPACKET;
typedef struct _savegamep* LPSAVEGAMEPACKET;

struct _savegamep : CommonData
{
	ULong	index;
	ULong	size;
	char	data[500];
};

typedef struct _csstrucpart CSSTRUCPART;
typedef struct _csstrucpart* LPCSSTRUCPART;

struct _csstrucpart : CommonData
{
	ULong	index;
	ULong	size;
	ULong	newmissionnum;
	char	data[500];
};

typedef struct _messages MESSAGEPACKET;
typedef struct _messages* LPMESSAGEPACKET;

struct _messages : CommonData
{
	char	messages[10][128];	// my messages
};

typedef struct _allocreq ALLOCREQUEST;
typedef struct _allocreq* LPALLOCREQUEST;

struct _allocreq : CommonData
{
	ULong id;
};

// Prefs Data Packet
typedef struct _prefs_data UIPREFSDATA;
typedef struct _prefs_data* PUIPREFSDATA;

struct _prefs_data : CommonData
{
//DeadCode AMM 08Apr99 	ULong DataRate;
	FlightDifficultyField	flightdifficulty;
	GameDifficultyField	gamedifficulty;
	TargetSize targetsize;
	SWord	autopilotskillUN;
	SWord	autopilotskillRED;
};

typedef struct _miss_conds_packet CONDITIONSDATA;
typedef struct _miss_conds_packet* LPCONDITIONSDATA;

struct _miss_conds_packet : CommonData
{
	char	conds[512];
};

enum PacketCodes {
	PID_NEWPLAYER=0xf00000d1 ,
	PID_PLAYERUPDATE,		 	//f00000d2
	PID_IMHERE,					//f00000d3
	PID_PLAYERQUIT,				//f00000d4
	PID_MESSAGE,				//f00000d5
	PID_REQUESTSLOT,			//f00000d6
 	PID_DATAREQUEST,			//f00000d7
	PID_INPAINTSHOP,			//f00000d8
	PID_INPREFS,				//f00000d9
	PID_INFRAG,					//f00000da
	PID_INREADYROOM,			//f00000db
	PID_INMAP,					//f00000dc
	PID_INMISSIONBRIEF,			//f00000dd
	PID_INRADIO,				//f00000de
	PID_INVISITORS,				//f00000df
	PID_INDEBRIEF,				//f00000e0
	PID_PREFSDATA,				//f00000e1
	PID_FLYNOW,					//f00000e2
	PID_PLAYERLEAVINGGAME,		//f00000e3
	PID_IAMIN,					//f00000e4
	PID_GAMEAVAILABLE,			//f00000e5
	PID_PASSWORD,				//f00000e6
	PID_VISITORUPDATE,			//f00000e7
	PID_SYNC, 					//f00000e8
	PID_NEEDRESYNC,				//f00000e9
	PID_ISTHEREAGAME,			//f00000ea
	PID_PREFSREQUEST,			//f00000eb
	PID_ALLOCREQUEST,			//f00000ec
	PID_BFIELDREQUEST,			//f00000ed
	PID_SLOTREQUEST,			//f00000ee
	PID_SLOTINFOUPDATE,			//f00000ef
	PID_GAMEDETAILSREQUEST,		//f00000f0
	PID_GAMEDETAILSINFO,		//f00000f1
	PID_PLAYERINFOREQUEST,		//f00000f2
	PID_RESYNC,					//f00000f3
	PID_NEWSLOT,				//f00000f4
	PID_ALLOCPACKET,			//f00000f5
	PID_PASSWORDVALID,			//f00000f6
//DeadCode AMM 15Apr99 	PID_POSITIONDATA,
	PID_HOSTBUSY,				//f00000f7
	PID_CSQUICKREQUEST,			//f00000f8
	PID_CSQUICKINFO,	// used when host changes mission in game			//f00000f9
	PID_CSQUICKINIT,	// used when players joining request			//f00000fa
	PID_ACDATA,				//f00000fb
	PID_ACANIM,				//f00000fc
	PID_MOBDATA,			//f00000fd
	PID_MOBANIM,			//f00000fe
	PID_ITEMDATA,			//f00000ff
	PID_ITEMANIM,			//f0000100
	PID_NUMACANIMS,			//f0000101
	PID_NUMMOBANIMS,		//f0000102
	PID_NUMITEMANIMS,		//f0000103
	PID_MESSAGES,			//f0000104
	PID_MESSAGESREQUEST,	//f0000105
	PID_GOTWORLD,			//f0000106
	PID_BFIELDPACKETIDENT,	//f0000107
	PID_MISSCONDSREQUEST,	//f0000108
	PID_MISSIONCONDITIONS,	//f0000109
	PID_SAVEGAME,			//f000010a
	PID_SAVEGAMEBINARY,		//f000010b
	PID_SAVEGAMESCORE,		//f000010c
	PID_READYWORLD,			//f000010d
	PID_RESTARTWORLDSYNC,	//f000010e
	PID_GUESTLEAVING,		//f000010f
	PID_NUMDEADBLOCKS,		//f0000110
	PID_DEADBLOCKDATA,		//f0000111
	PID_HOSTLEAVING, // party pooper  			//f0000112
	PID_SINGLEPILOTSTATUS,	//f0000113
	PID_ALLPILOTSSTATUS,	//f0000114
	PID_CAMPAIGNSTRUC,		//f0000115
	PID_CAMPAIGNSTRUCBINARY,	//f0000116
	PID_QUITACCEL,			 //f0000117
	PID_RANDREQUEST,			//f0000118
	PID_AAAPACKET,			//f0000119
	PID_RANDOMLIST,			//f000011a
	PID_CSSTRUC,				// 0x34
	PID_CSSTRUCBINARY			// 0x35

};

#endif
