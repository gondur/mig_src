//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 NOW USE MISSMAN2.H
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 //Filename       miss_man.h
//DeadCode JIM 22Aug96 //System         
//DeadCode JIM 22Aug96 //Author         R. Hyde 
//DeadCode JIM 22Aug96 //Date           Thu 7 Dec 1995
//DeadCode JIM 22Aug96 //Description    
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 #ifndef	MISS_MAN_Included
//DeadCode JIM 22Aug96 #define	MISS_MAN_Included
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 //this means that I dont want any common files
//DeadCode JIM 22Aug96 #define	f_common
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 #include	"textref.h"
//DeadCode JIM 22Aug96 #define		F_SOUNDS
//DeadCode JIM 22Aug96 #define		F_COMMON
//DeadCode JIM 22Aug96 #include	"Files.g"
//DeadCode JIM 22Aug96 #include	"angles.h"											//RDH 20Dec95
//DeadCode JIM 22Aug96 #include	"flyinit.h"											//RDH 20Dec95
//DeadCode JIM 22Aug96 #include	"worldinc.h"										//RDH 11Aug96
//DeadCode JIM 22Aug96 #ifdef	DEFAULT_MISS_MAN
//DeadCode JIM 22Aug96 //
//DeadCode JIM 22Aug96 // If the module is declared a second time, then this alternate construction 
//DeadCode JIM 22Aug96 // is made to allow instances to occur.
//DeadCode JIM 22Aug96 //
//DeadCode JIM 22Aug96 	#define	basestruct(subname)							\
//DeadCode JIM 22Aug96 	struct	II_##subname			{
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	#define	substruct(subname,parentname)				\
//DeadCode JIM 22Aug96 	struct	II_##subname			{					\
//DeadCode JIM 22Aug96 		II_##parentname	parentinst;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	#define	endstruct(subname)		};					\
//DeadCode JIM 22Aug96 	union	I_##subname									\
//DeadCode JIM 22Aug96 		{	II_##subname II;subname I;}
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	#define	startinst(strucname,instname)	 			\
//DeadCode JIM 22Aug96 		I_##strucname	I_##instname	=	{
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	#define	endinst(strucname,instname)	 	};			\
//DeadCode JIM 22Aug96 		strucname&	instname=I_##instname.I;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 #else
//DeadCode JIM 22Aug96 //
//DeadCode JIM 22Aug96 // This definition defines substructures by simple inheritance
//DeadCode JIM 22Aug96 // That will not allow initialisation.
//DeadCode JIM 22Aug96 //
//DeadCode JIM 22Aug96 	#define	basestruct(subname)							\
//DeadCode JIM 22Aug96 	struct	subname					{
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	#define	substruct(subname,parentname)				\
//DeadCode JIM 22Aug96 	struct	subname : parentname	{
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	#define	endstruct(subname)		}
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 #endif
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 #define	DEFAULT_MISS_MAN 0
//DeadCode JIM 22Aug96 struct	MissionType;
//DeadCode JIM 22Aug96 struct	PilotType;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 #include "bitfield.h"
//DeadCode JIM 22Aug96 #ifndef	MISS_MAN_Included2
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 enum	SpecialEventBit {SpecialEventMIN = 0,HOMEBASEDESTROYED = 0,
//DeadCode JIM 22Aug96 									PLAYERKILLED, RESERVEEXHAUSTED,
//DeadCode JIM 22Aug96 //above this you are dead
//DeadCode JIM 22Aug96 						PLAYERWOUNDED,RESERVES_2LEFT,RESERVES_6LEFT,
//DeadCode JIM 22Aug96 						ACEKILLED,NEARTARGET,
//DeadCode JIM 22Aug96 						FATALITYINSQUAD,WOUNDEDINSQUAD,
//DeadCode JIM 22Aug96 						MORALEEXCELLENT,MORALEGOOD,MORALEPOOR,MORALEROCKBOTTOM,
//DeadCode JIM 22Aug96 						BESTDAY,SUGGESTEASIERAREA,SUGGESTDIFFICULTAREA,
//DeadCode JIM 22Aug96 //
//DeadCode JIM 22Aug96 						LIEUTENANTPROMOTION,CAPTAINPROMOTION,
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 //Spring Offensive training
//DeadCode JIM 22Aug96 						CRASHLAND,BENTGEAR,KANGAROO,GOODLANDING,
//DeadCode JIM 22Aug96 						STAYEDVCLOSETOCO,STAYEDCLOSETOCO,STAYEDINVICINITYOFCO,MILESFROMCO,
//DeadCode JIM 22Aug96 						SEENBYCO,NOTSEENBYCO,HITSNEARCO,
//DeadCode JIM 22Aug96 //SO debriefs
//DeadCode JIM 22Aug96 						LASTMISSIONSTRONG,LASTMISSIONWEAK,
//DeadCode JIM 22Aug96 //tank debriefs
//DeadCode JIM 22Aug96 						HITTANKANIM,
//DeadCode JIM 22Aug96 //awarded medals
//DeadCode JIM 22Aug96 						AWARDED_MEDALOFHONOUR,
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 					  HOMEBASEDAMAGED,SpecialEventMAX};
//DeadCode JIM 22Aug96 //			In 3d Temp_Pilots morale
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 MAKEFIELD (SpecialEventBit,SpecialEventMIN,SpecialEventMAX);
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 enum	NewsEvent {NewsEventMIN = 0, NEWSWOUNEDRECOVERED, NEWSACEIN,
//DeadCode JIM 22Aug96 									 NEWSACEOUT,NEWSMISSION,NEWSMERITPROMOTION,
//DeadCode JIM 22Aug96 									 NEWSDEADMANPROMOTION,NEWSTHEPROMOTION,
//DeadCode JIM 22Aug96 									//Spring Offensive: go operational
//DeadCode JIM 22Aug96 									 NEWSOPERATIONALGOOD,NEWSOPERATIONALBAD,
//DeadCode JIM 22Aug96 										NewsEventMAX};
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 MAKEFIELD (NewsEvent,NewsEventMIN,NewsEventMAX);
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 enum	pilotstatus	{NOTFLYING = 0,FLYING};
//DeadCode JIM 22Aug96 //DeadCode JIM 10Jun96 enum	SkillType
//DeadCode JIM 22Aug96 //DeadCode JIM 10Jun96 		{SKILL_NOVICE = 0,SKILL_STAGE = 1,SKILL_POOR,SKILL_REGULAR,SKILL_VETERAN,SKILL_ACE,SKILL_HERO};
//DeadCode JIM 22Aug96 enum	MeritType
//DeadCode JIM 22Aug96 		{MERIT_ROCKBOTTOM = 0,MERIT_INITIAL = 1000,MERIT_2LFTEXPERIENCED =5000,
//DeadCode JIM 22Aug96 		MERIT_LFT = 8000,
//DeadCode JIM 22Aug96 		MERIT_CAPTAIN = 12000,MERIT_MAJOR =18000,MERIT_MAJORHONOUR = 27000,MERIT_IMPOSSIBLE = 65535,
//DeadCode JIM 22Aug96 		
//DeadCode JIM 22Aug96 //Spring Offensive merits to get operational		
//DeadCode JIM 22Aug96 		MERIT_OPERATIONAL = 3000,
//DeadCode JIM 22Aug96 			
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 		};
//DeadCode JIM 22Aug96 enum	DeltaMeritType
//DeadCode JIM 22Aug96 		{
//DeadCode JIM 22Aug96 		MERIT_VIS_MSN_SUCCESS =4000,
//DeadCode JIM 22Aug96 		MERIT_OP_CRASHLAND = -300,
//DeadCode JIM 22Aug96 		MERIT_OP_BENTGEAR = -100,
//DeadCode JIM 22Aug96 		MERIT_OP_KANGAROO = 300,
//DeadCode JIM 22Aug96 		MERIT_OP_GOODLANDING = 500,
//DeadCode JIM 22Aug96 		MERIT_OP_STAYEDVCLOSETOCO = 3000,
//DeadCode JIM 22Aug96 		MERIT_OP_STAYEDCLOSETOCO = 1500,
//DeadCode JIM 22Aug96 		MERIT_OP_STAYEDINVICINITYOFCO = 1000,
//DeadCode JIM 22Aug96 		MERIT_OP_MILESFROMCO = -1000,
//DeadCode JIM 22Aug96 		MERIT_OP_SEENBYCO = -1000,
//DeadCode JIM 22Aug96 		MERIT_OP_NOTSEENBYCO =1000,
//DeadCode JIM 22Aug96 		MERIT_OP_HITSNEARCO = 3000
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 		};
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 enum	MoraleType
//DeadCode JIM 22Aug96 		{MORALE_ROCKBOTTOM = 0,MORALE_VERYPOOR = 40,MORALE_STAGE = 40,MORALE_POOR =80,MORALE_MEDIUM = 120,MORALE_GOOD =160,MORALE_VERYGOOD = 200,MORALE_EXCELLENT = 240,MORALE_TOPMORALE = 255 };
//DeadCode JIM 22Aug96 //DeadCode JIM 10Jun96 enum	CharacterType	- now in flyinit.h
//DeadCode JIM 22Aug96 //DeadCode JIM 10Jun96 		{CHAR_TACTICIAN = 0,CHAR_MRAVERAGE,CHAR_CAVALIER,CHAR_align=255};		
//DeadCode JIM 22Aug96 enum 	PlayerRank {SECLIEUTENANT= 0,SECLIEUTENANT_EXPERT,LIEUTENANT,CAPTAIN,MAJOR, RANK_INC = 1};
//DeadCode JIM 22Aug96 enum					{MAXCONVOYS = 2,MAXROUTES = 5,MAXGUNS = 2};
//DeadCode JIM 22Aug96 #endif
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 enum	AircraftType{	TYPE_CAMEL,										//RDH 07Apr96
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_SE5A,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_NIEUPORT,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_SPAD,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_SNIPE,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_STRUTTER,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_BRISTOL_F2A,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_PUP,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_FE2B,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_BE2C,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_RE8,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_DH9,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_PFALZ,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_ALBATROS_D2,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_ALBATROS_D3,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_FOKKER_D7,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_FOKKER_DR1,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_ALBATROS_CV,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_AEG_C4,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_AVIATIK_C,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_RUMBLER_C,
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 				TYPE_NULL
//DeadCode JIM 22Aug96 //DeadCode RDH 07Apr96 			};
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 struct	WpSetType;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 basestruct	(CampaignInitDef)
//DeadCode JIM 22Aug96  	enum					{MAX_FLIGHT_NUM = 4};
//DeadCode JIM 22Aug96 	enum					{MAXWEATHERNUM = 4};
//DeadCode JIM 22Aug96 	UniqueID		playerhomebase;
//DeadCode JIM 22Aug96 	UniqueID		playertakeoff;
//DeadCode JIM 22Aug96 	SLong			currdate;
//DeadCode JIM 22Aug96 	SLong			currtime;
//DeadCode JIM 22Aug96 	SWord 			currweathernum;
//DeadCode JIM 22Aug96 	SWord 			currwindnum;
//DeadCode JIM 22Aug96 	MissionType*	currmission;
//DeadCode JIM 22Aug96 	SWord			currmission_no;
//DeadCode JIM 22Aug96 	SWord			missionwpset;
//DeadCode JIM 22Aug96 	SWord			missionarea;
//DeadCode JIM 22Aug96 	WpSetType*		players_wpset;
//DeadCode JIM 22Aug96 	MissionType*	dfltmission;
//DeadCode JIM 22Aug96 	PlayerRank		playerrank;
//DeadCode JIM 22Aug96 	MeritType		playermerit;
//DeadCode JIM 22Aug96 	SWord			killsonbestday;
//DeadCode JIM 22Aug96 	SWord			currmissionfamily;
//DeadCode JIM 22Aug96 	SWord			dayssincetransfer;
//DeadCode JIM 22Aug96 	MoraleType		squadronmorale;
//DeadCode JIM 22Aug96 	SWord			lastdeadpilot;
//DeadCode JIM 22Aug96 	SWord			lastrecoveredpilot;
//DeadCode JIM 22Aug96 	TextRef			lasttransferee;
//DeadCode JIM 22Aug96 	TextRef			lastdeadsuperior;
//DeadCode JIM 22Aug96 struct	SquadronInfo
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96 	SLong			ac_available;
//DeadCode JIM 22Aug96 	SLong			ac_used;
//DeadCode JIM 22Aug96 	SWord			flightnum [MAX_FLIGHT_NUM];
//DeadCode JIM 22Aug96 	SWord			formationnum [MAX_FLIGHT_NUM];
//DeadCode JIM 22Aug96 	SWord			squadronform;
//DeadCode JIM 22Aug96 	NextLeadAct		nextleadact [MAX_FLIGHT_NUM];
//DeadCode JIM 22Aug96 	SWord			pilotsperflight;
//DeadCode JIM 22Aug96 	PlaneTypeSelect	actype;										//RDH 07Apr96
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 	SquadronInfo	squad;
//DeadCode JIM 22Aug96 	struct	TkInfo {
//DeadCode JIM 22Aug96 					SWord		timer;
//DeadCode JIM 22Aug96 					SWord		numoftankconvoys;
//DeadCode JIM 22Aug96 					UniqueID	blueguns[MAXGUNS];
//DeadCode JIM 22Aug96 					UniqueID	blueaaa[MAXGUNS];
//DeadCode JIM 22Aug96 				struct Convoy {
//DeadCode JIM 22Aug96 					UniqueID	uid;
//DeadCode JIM 22Aug96  					FileNum		bfield;
//DeadCode JIM 22Aug96 					SWord		size;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 					};	Convoy convoys[MAXCONVOYS];
//DeadCode JIM 22Aug96 			 };		
//DeadCode JIM 22Aug96 		TkInfo	tkinfo;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	SWord		acesavail,
//DeadCode JIM 22Aug96 				reservesavail;
//DeadCode JIM 22Aug96 	FileNum		playerbfield;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 endstruct	(CampaignInitDef);
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 substruct	(CampaignDef,CampaignInitDef)
//DeadCode JIM 22Aug96 //DeadCode RDH 24Jan96 //	PilotType*	currpilotlist;
//DeadCode JIM 22Aug96 	UniqueID	routesstartuids[MAXROUTES];
//DeadCode JIM 22Aug96 	PilotType	*aces,
//DeadCode JIM 22Aug96 				*reserves;
//DeadCode JIM 22Aug96 	SWord	playerslot;
//DeadCode JIM 22Aug96 	FileNum	mainbfield;
//DeadCode JIM 22Aug96 	FileNum	introsheetart;
//DeadCode JIM 22Aug96 	FileNum	intropadart;
//DeadCode JIM 22Aug96 	FileNum	introiconart;
//DeadCode JIM 22Aug96 	FileNum	cr_iconart;
//DeadCode JIM 22Aug96 	FileNum	introsmack;
//DeadCode JIM 22Aug96 	FileNum	introquarterart;
//DeadCode JIM 22Aug96 	FileNum	historyart;
//DeadCode JIM 22Aug96 	FileNum	personnelart;
//DeadCode JIM 22Aug96 	FileNum	junctionart;
//DeadCode JIM 22Aug96 	FileNum	squadart;
//DeadCode JIM 22Aug96 	FileNum	saveart;
//DeadCode JIM 22Aug96 	FileNum	savedialogue;
//DeadCode JIM 22Aug96 	FileNum	quitart;
//DeadCode JIM 22Aug96 	FileNum	padart;
//DeadCode JIM 22Aug96 	FileNum	mainiconart;
//DeadCode JIM 22Aug96 	FileNum	flightart;
//DeadCode JIM 22Aug96 	FileNum	newstextart;
//DeadCode JIM 22Aug96 	FileNum	newsgraphicart;
//DeadCode JIM 22Aug96 	FileNum	flightgraphicart;
//DeadCode JIM 22Aug96 	FileNum	acsmallart;
//DeadCode JIM 22Aug96 	FileNum	acmedart;
//DeadCode JIM 22Aug96 	FileNum	aclargeart;
//DeadCode JIM 22Aug96 	FileNum	paintshopart;
//DeadCode JIM 22Aug96 	FileNum	introtextart;
//DeadCode JIM 22Aug96 	TextRef	objecttext;
//DeadCode JIM 22Aug96 	TextRef	introtext;
//DeadCode JIM 22Aug96 	TextRef	editnametext;
//DeadCode JIM 22Aug96 	TextRef	editnametitle;
//DeadCode JIM 22Aug96 //following must be the last field
//DeadCode JIM 22Aug96 //DeadCode JIM 22Aug96 	CampaignInitDef*	restartdata;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 void	SetCurrMission (MissionType*);
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 endstruct	(CampaignDef);
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 #ifndef	MISS_MAN_Included2
//DeadCode JIM 22Aug96 #define	MISS_MAN_Included2
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 //DeadCode RDH 13Jun96 #include	"uid.g"												//RDH 21Dec95
//DeadCode JIM 22Aug96 struct	 MissMan
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96 //DeadCode DAW 02Apr96 	enum	{MAXCAMPAIGNNUM = 6,MAXACTUALCAMPAIGNNUM = 4};
//DeadCode JIM 22Aug96 	enum	CampaignName {
//DeadCode JIM 22Aug96 		CIRCUSCAMPAIGN = 0,
//DeadCode JIM 22Aug96 		HATRINGCAMPAIGN,
//DeadCode JIM 22Aug96 		SPRINGCAMPAIGN,
//DeadCode JIM 22Aug96 		TANKCAMPAIGN,
//DeadCode JIM 22Aug96 		RUNDEMOCAMPAIGN,
//DeadCode JIM 22Aug96 		SCRAMBLECAMPAIGN,
//DeadCode JIM 22Aug96 		MINCAMPAIGNNUM = 0,
//DeadCode JIM 22Aug96 		MAXCAMPAIGNNUM = 6,
//DeadCode JIM 22Aug96 		MAXACTUALCAMPAIGNNUM = 4
//DeadCode JIM 22Aug96 		};
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	CampaignName 	currcampaignnum;
//DeadCode JIM 22Aug96 	struct	CampaignDef		*currcamp,
//DeadCode JIM 22Aug96 							*campaigntable[MAXCAMPAIGNNUM];
//DeadCode JIM 22Aug96 	TextPerm	playernameref;
//DeadCode JIM 22Aug96 	CampaignInitDef*	restartdata;
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 extern	MissMan Miss_Man;
//DeadCode JIM 22Aug96 extern	SpecialEventBitField	specialeventbits;
//DeadCode JIM 22Aug96 extern	NewsEventField			newsevent;
//DeadCode JIM 22Aug96 struct	WpListType;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 struct	MissionType
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96 	FileNum	introsmack;
//DeadCode JIM 22Aug96 	TextRef	newstext;
//DeadCode JIM 22Aug96 	TextRef	missiontext;
//DeadCode JIM 22Aug96 	SLong	missiondate;
//DeadCode JIM 22Aug96 	SLong	timeofday;
//DeadCode JIM 22Aug96 	WpListType* wplist;
//DeadCode JIM 22Aug96 	FileNum	playerbf;
//DeadCode JIM 22Aug96 	SWord	numofsquadronac;	
//DeadCode JIM 22Aug96 	SWord	numofflightac;	
//DeadCode JIM 22Aug96 	FormationTypeIndex	formationtypeindex;
//DeadCode JIM 22Aug96 	FileNum	backdropart;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 struct	WpSetType
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96 	UniqueID	mainobjective;
//DeadCode JIM 22Aug96 	UniqueID	subobjective;
//DeadCode JIM 22Aug96 	UniqueID	wp1;
//DeadCode JIM 22Aug96 	UniqueID	wp2;
//DeadCode JIM 22Aug96 	UniqueID	wp3;
//DeadCode JIM 22Aug96 	UniqueID	zero;
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 struct	WpListType
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96  	SWord	noofentries;
//DeadCode JIM 22Aug96 	WpSetType*	wpset [4];
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 struct	BfTypeList
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96  	SWord	noofentries;
//DeadCode JIM 22Aug96 	SWord	bfields [24];
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 enum	pilotskill 	{NOVICE = 0,REGULAR,VETERAN,ACE,HERO};
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 enum	pilotmorale {PM_ROCKBOTTOM = 0,PM_VERYPOOR = 6000,PM_POOR = 11000,PM_AVERAGE = 16000,PM_GOOD = 21000,PM_VERYGOOD = 26000,PM_EXCELLENT = 31000,PM_TOPMORALE = 32767};	
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 enum	pilotchar	{TACTICIAN = 0,MRAVERAGE,CAVALIER};
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 enum	pilotstatus	{NOTFLYING = 0,FLYING};
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 enum	SkillType
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 		{SKILL_NOVICE = 0,SKILL_REGULAR,SKILL_VETERAN,SKILL_ACE,SKILL_HERO};
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 enum	MoraleType
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 		{MORALE_ROCKBOTTOM = 0,MORALE_VERYPOOR = 5000,MORALE_STAGE = 5000,MORALE_POOR =10000,MORALE_MEDIUM = 15000,MORALE_GOOD =20000,MORALE_VERYGOOD = 25000,MORALE_EXCELLENT = 30000,MORALE_TOPMORALE = 32767 };
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 enum	CharacterType
//DeadCode JIM 22Aug96 //DeadCode RDH 30Jan96 		{CHAR_TACTICIAN = 0,CHAR_MRAVERAGE,CHAR_CAVALIER};		
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 struct PilotType
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96 	TextRef	name;
//DeadCode JIM 22Aug96 	SkillType	skill;
//DeadCode JIM 22Aug96 	pilotstatus	status;
//DeadCode JIM 22Aug96 	CharacterType	character;
//DeadCode JIM 22Aug96 	MoraleType	morale;
//DeadCode JIM 22Aug96 //DeadCode RDH 11Aug96 	FileNum	photo;
//DeadCode JIM 22Aug96 	NextFollAct	nextfollact;
//DeadCode JIM 22Aug96 	SWord	dayssincerest;
//DeadCode JIM 22Aug96 	SWord	kills;
//DeadCode JIM 22Aug96 //DeadCode MS 18Aug96 	SWord	flyinghours;
//DeadCode JIM 22Aug96 	SWord	daystorecover;
//DeadCode JIM 22Aug96 struct	ImageMaps
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96  	UByte	topwing;
//DeadCode JIM 22Aug96  	UByte	tail;
//DeadCode JIM 22Aug96  	UByte	btmwing;
//DeadCode JIM 22Aug96  	UByte	fuselage;
//DeadCode JIM 22Aug96  	UByte	other;
//DeadCode JIM 22Aug96 	UByte	emblem;
//DeadCode JIM 22Aug96 //DeadCode RDH 20Feb96 	SWord	topwing;
//DeadCode JIM 22Aug96 //DeadCode RDH 20Feb96 	SWord	tail;
//DeadCode JIM 22Aug96 //DeadCode RDH 20Feb96 	SWord	btmwing;
//DeadCode JIM 22Aug96 //DeadCode RDH 20Feb96 	SWord	fuselage;
//DeadCode JIM 22Aug96 //DeadCode RDH 20Feb96 	SWord	other;
//DeadCode JIM 22Aug96 }	imagemaps;
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 SLong const FLIGHTSPERSQUADRON	 = 4;
//DeadCode JIM 22Aug96 SLong const FLYINGFLIGHTSPERSQUADRON	 = FLIGHTSPERSQUADRON - 1;
//DeadCode JIM 22Aug96 SLong const MAXIMAGEMAPSPERAIRCRAFT = 8;
//DeadCode JIM 22Aug96 struct FormationPos
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96 	SLong	range;
//DeadCode JIM 22Aug96 	ANGLES	bearing;
//DeadCode JIM 22Aug96 	SLong	delta_alt;
//DeadCode JIM 22Aug96 	SWord	alt_icon;
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	enum					{MAXFLIGHT_FORMS_NUM = 8};
//DeadCode JIM 22Aug96 	enum					{MAXAC_FORMATIONS_NUM = 5};
//DeadCode JIM 22Aug96 struct FormationType
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96 	TextRef			name;
//DeadCode JIM 22Aug96 	FormationPos	wingpos [MAXAC_FORMATIONS_NUM];
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 	enum					{MAXSQUAD_FORMS_NUM = 5};			//RDH 18Aug96
//DeadCode JIM 22Aug96 struct SquadronType
//DeadCode JIM 22Aug96 {
//DeadCode JIM 22Aug96 	TextRef			name;
//DeadCode JIM 22Aug96 	FormationPos	wingpos [FLYINGFLIGHTSPERSQUADRON];
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 };
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 typedef FormationType* SingleFormation;
//DeadCode JIM 22Aug96 extern SingleFormation Aircraft_Formations [];
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 typedef SquadronType* SquadFormation;
//DeadCode JIM 22Aug96 extern SquadFormation Squadron_Formations [];
//DeadCode JIM 22Aug96 //------------------------------------------------------------------------------
//DeadCode JIM 22Aug96 typedef	MissionType* DayMission [3];
//DeadCode JIM 22Aug96 extern	DayMission Circus_Missions [];
//DeadCode JIM 22Aug96 typedef	MissionType* SingleMission;
//DeadCode JIM 22Aug96 extern	SingleMission Spring_Missions [];
//DeadCode JIM 22Aug96 extern	SingleMission HatDflt_Missions [];
//DeadCode JIM 22Aug96 extern	SingleMission TnkDflt_Missions [];
//DeadCode JIM 22Aug96 extern	SingleMission Scramble_Missions [];						//RDH 02Aug96
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 typedef	MissionType* MissionFamily [6];
//DeadCode JIM 22Aug96 typedef MissionFamily MissionArea [5];
//DeadCode JIM 22Aug96 extern 	MissionArea Hat_Missions [2];
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 const	PILOTS_PER_SQUADRON = 24;
//DeadCode JIM 22Aug96 //DeadCode RDH 24Jan96 typedef	PilotType*	PilotRef;
//DeadCode JIM 22Aug96 //DeadCode RDH 24Jan96 typedef PilotRef	SquadronPilots [PILOTS_PER_SQUADRON];
//DeadCode JIM 22Aug96 //DeadCode RDH 24Jan96 typedef	PilotType*	PilotList;
//DeadCode JIM 22Aug96 //DeadCode RDH 24Jan96 extern	PilotList Crc_Pilot_List [];
//DeadCode JIM 22Aug96 //DeadCode RDH 24Jan96 extern	PilotList Work_Pilot_List [];
//DeadCode JIM 22Aug96 //DeadCode RDH 24Jan96 extern	PilotList Crc_Ace_List [];
//DeadCode JIM 22Aug96 //DeadCode RDH 24Jan96 extern	PilotList Crc_Reserve_List [];
//DeadCode JIM 22Aug96 //DeadCode RDH 24Jan96 extern	PilotList Crc_Wounded_List [];
//DeadCode JIM 22Aug96 extern	PilotType	Crc_Pilots[],Crc_12Reserves[],Crc_8Aces[];
//DeadCode JIM 22Aug96 extern	PilotType	Hat_Pilots[],Hat_12Reserves[],Hat_8Aces[];
//DeadCode JIM 22Aug96 extern	PilotType	SO_Pilots[],SO_12Reserves[],SO_8Aces[];
//DeadCode JIM 22Aug96 extern	PilotType	Tnk_Pilots[],Tnk_12Reserves[],Tnk_8Aces[];
//DeadCode JIM 22Aug96 extern	PilotType	Active_Pilots[],Temp_Pilots[],Wounded_Pilots[],Dead_Pilots[],Reserve_Pilots[];
//DeadCode JIM 22Aug96 extern	CampaignInitDef::SquadronInfo Temp_Squadron;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 enum	HatMissionFamily {HP_VOLUNTEER = 0,
//DeadCode JIM 22Aug96 			HP_NOCHOICE = 0, HP_BALLOON,HP_PATROL,HP_ESCORT,HP_ROVING};
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 enum	SquadPanelSelection {PERSONNEL = 0, CONFIGURE, PREFERENCES, PAINTSHOP,SAVEGAME};
//DeadCode JIM 22Aug96 enum	ConfigureSelection	{SAVECONFIGURE,RETURNFROMCONFIGURE,CANCELCONFIGURE,GOTOJOYSTICKCONFIG};
//DeadCode JIM 22Aug96 enum	FlightInfoSelection { FLYNOW= 0, JUSTRETURN};
//DeadCode JIM 22Aug96 SWord	const	MAXCIRCUSMISSIONS = 21;
//DeadCode JIM 22Aug96 SWord	const	MAXHATMISSIONS = 21;
//DeadCode JIM 22Aug96 SWord	const	MAXSPRINGMISSIONS = 24;
//DeadCode JIM 22Aug96 SWord	const	MAXTANKMISSIONS = 16;
//DeadCode JIM 22Aug96 SWord	const	CIRCUSPLAYERSLOT = 0;
//DeadCode JIM 22Aug96 SWord	const	HATPLAYERSLOT = 7;
//DeadCode JIM 22Aug96 SWord	const	CIRCUSTARGETKILL = 52;
//DeadCode JIM 22Aug96 SWord	const	PILOTACTIVE = 0;
//DeadCode JIM 22Aug96 SWord	const	PILOTDEAD = -1;
//DeadCode JIM 22Aug96 SWord	const	PILOTS_IN_RESERVE = 12;
//DeadCode JIM 22Aug96 SWord	const	ACESLIST = 8;
//DeadCode JIM 22Aug96 SWord	const	CASUALTYLIST = ACESLIST + PILOTS_IN_RESERVE;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 //DeadCode RDH 22Jan96 //SLong const PILOTSPERFLIGHT	 = 6;
//DeadCode JIM 22Aug96 //DeadCode RDH 22Jan96 SLong const FLIGHTSPERSQUADRON	 = 4;
//DeadCode JIM 22Aug96 //DeadCode RDH 22Jan96 SLong const FLYINGFLIGHTSPERSQUADRON	 = FLIGHTSPERSQUADRON - 1;
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 #endif
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 #undef	basestruct
//DeadCode JIM 22Aug96 #undef	substruct
//DeadCode JIM 22Aug96 #undef	endstruct
//DeadCode JIM 22Aug96 
//DeadCode JIM 22Aug96 #endif
//DeadCode DAW 23Aug96 >>>>>>>>>>  miss_man.h  Rev "JIM branch" (1.1.36.0.3.0)
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 <<<<<<<<<<  miss_man.h  Rev "Tip" (1.1.38.0)
//DeadCode DAW 23Aug96 //tank lost
//DeadCode DAW 23Aug96 						TANKCAMPAIGNLOST,
//DeadCode DAW 23Aug96 //awarded medals
//DeadCode DAW 23Aug96 						AWARDED_MEDALOFHONOUR,
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 					  SpecialEventMAX};
//DeadCode DAW 23Aug96 //			In 3d Temp_Pilots morale
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 MAKEFIELD (SpecialEventBit,SpecialEventMIN,SpecialEventMAX);
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 enum	NewsEvent {NewsEventMIN = 0, NEWSWOUNEDRECOVERED, NEWSACEIN,
//DeadCode DAW 23Aug96 									 NEWSACEOUT,NEWSMISSION,NEWSMERITPROMOTION,
//DeadCode DAW 23Aug96 									 NEWSDEADMANPROMOTION,NEWSTHEPROMOTION,
//DeadCode DAW 23Aug96 									NEWSWOUNDEDMANPROMOTION,
//DeadCode DAW 23Aug96 									//Spring Offensive: go operational
//DeadCode DAW 23Aug96 									 NEWSOPERATIONALGOOD,NEWSOPERATIONALBAD,
//DeadCode DAW 23Aug96 									NEWSBESTDAY,
//DeadCode DAW 23Aug96 										NewsEventMAX};
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 MAKEFIELD (NewsEvent,NewsEventMIN,NewsEventMAX);
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 enum	pilotstatus	{NOTFLYING = 0,FLYING};
//DeadCode DAW 23Aug96 //DeadCode JIM 10Jun96 enum	SkillType
//DeadCode DAW 23Aug96 //DeadCode JIM 10Jun96 		{SKILL_NOVICE = 0,SKILL_STAGE = 1,SKILL_POOR,SKILL_REGULAR,SKILL_VETERAN,SKILL_ACE,SKILL_HERO};
//DeadCode DAW 23Aug96 enum	MeritType
//DeadCode DAW 23Aug96 		{MERIT_ROCKBOTTOM = 0,MERIT_INITIAL = 1000,MERIT_2LFTEXPERIENCED =5000,
//DeadCode DAW 23Aug96 		MERIT_LFT = 8000,
//DeadCode DAW 23Aug96 		MERIT_CAPTAIN = 12000,MERIT_MAJOR =18000,MERIT_MAJORHONOUR = 27000,MERIT_IMPOSSIBLE = 65535,
//DeadCode DAW 23Aug96 		
//DeadCode DAW 23Aug96 //Spring Offensive merits to get operational		
//DeadCode DAW 23Aug96 		MERIT_OPERATIONAL = 3000,
//DeadCode DAW 23Aug96 			
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 		};
//DeadCode DAW 23Aug96 enum	DeltaMeritType
//DeadCode DAW 23Aug96 		{
//DeadCode DAW 23Aug96 		MERIT_VIS_MSN_SUCCESS =4000,
//DeadCode DAW 23Aug96 		MERIT_OP_CRASHLAND = -300,
//DeadCode DAW 23Aug96 		MERIT_OP_BENTGEAR = -100,
//DeadCode DAW 23Aug96 		MERIT_OP_KANGAROO = 300,
//DeadCode DAW 23Aug96 		MERIT_OP_GOODLANDING = 500,
//DeadCode DAW 23Aug96 		MERIT_OP_STAYEDVCLOSETOCO = 3000,
//DeadCode DAW 23Aug96 		MERIT_OP_STAYEDCLOSETOCO = 1500,
//DeadCode DAW 23Aug96 		MERIT_OP_STAYEDINVICINITYOFCO = 1000,
//DeadCode DAW 23Aug96 		MERIT_OP_MILESFROMCO = -1000,
//DeadCode DAW 23Aug96 		MERIT_OP_SEENBYCO = -1000,
//DeadCode DAW 23Aug96 		MERIT_OP_NOTSEENBYCO =1000,
//DeadCode DAW 23Aug96 		MERIT_OP_HITSNEARCO = 3000
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 		};
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 enum	MoraleType
//DeadCode DAW 23Aug96 		{MORALE_ROCKBOTTOM = 0,MORALE_STEP = 16,MORALE_VERYPOOR = 40,MORALE_STAGE = 40,MORALE_POOR =80,MORALE_MEDIUM = 120,MORALE_GOOD =160,MORALE_VERYGOOD = 200,MORALE_EXCELLENT = 240,MORALE_TOPMORALE = 255 };
//DeadCode DAW 23Aug96 //DeadCode JIM 10Jun96 enum	CharacterType	- now in flyinit.h
//DeadCode DAW 23Aug96 //DeadCode JIM 10Jun96 		{CHAR_TACTICIAN = 0,CHAR_MRAVERAGE,CHAR_CAVALIER,CHAR_align=255};		
//DeadCode DAW 23Aug96 enum 	PlayerRank {SECLIEUTENANT= 0,SECLIEUTENANT_EXPERT,LIEUTENANT,CAPTAIN,MAJOR, RANK_INC = 1};
//DeadCode DAW 23Aug96 enum					{MAXCONVOYS = 2,MAXROUTES = 5,MAXGUNS = 2};
//DeadCode DAW 23Aug96 #endif
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 enum	AircraftType{	TYPE_CAMEL,										//RDH 07Apr96
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_SE5A,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_NIEUPORT,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_SPAD,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_SNIPE,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_STRUTTER,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_BRISTOL_F2A,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_PUP,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_FE2B,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_BE2C,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_RE8,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_DH9,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_PFALZ,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_ALBATROS_D2,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_ALBATROS_D3,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_FOKKER_D7,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_FOKKER_DR1,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_ALBATROS_CV,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_AEG_C4,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_AVIATIK_C,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_RUMBLER_C,
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 				TYPE_NULL
//DeadCode DAW 23Aug96 //DeadCode RDH 07Apr96 			};
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 struct	WpSetType;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 basestruct	(CampaignInitDef)
//DeadCode DAW 23Aug96  	enum					{MAX_FLIGHT_NUM = 4};
//DeadCode DAW 23Aug96 	enum					{MAXWEATHERNUM = 4};
//DeadCode DAW 23Aug96 	UniqueID		playerhomebase;
//DeadCode DAW 23Aug96 	UniqueID		playertakeoff;
//DeadCode DAW 23Aug96 	SLong			currdate;
//DeadCode DAW 23Aug96 	SLong			currtime;
//DeadCode DAW 23Aug96 	SWord 			currweathernum;
//DeadCode DAW 23Aug96 	SWord 			currwindnum;
//DeadCode DAW 23Aug96 	MissionType*	currmission;
//DeadCode DAW 23Aug96 	SWord			currmission_no;
//DeadCode DAW 23Aug96 	SWord			missionwpset;
//DeadCode DAW 23Aug96 	SWord			missionarea;
//DeadCode DAW 23Aug96 	WpSetType*		players_wpset;
//DeadCode DAW 23Aug96 	MissionType*	dfltmission;
//DeadCode DAW 23Aug96 	PlayerRank		playerrank;
//DeadCode DAW 23Aug96 	MeritType		playermerit;
//DeadCode DAW 23Aug96 	SWord			killsonbestday;
//DeadCode DAW 23Aug96 	SWord			currmissionfamily;
//DeadCode DAW 23Aug96 	SWord			dayssincetransfer;
//DeadCode DAW 23Aug96 	MoraleType		squadronmorale;
//DeadCode DAW 23Aug96 	SWord			lastdeadpilot;
//DeadCode DAW 23Aug96 	SWord			lastrecoveredpilot;
//DeadCode DAW 23Aug96 	TextRef			lasttransferee;
//DeadCode DAW 23Aug96 	TextRef			lastdeadsuperior;
//DeadCode DAW 23Aug96 struct	SquadronInfo
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96 	SLong			ac_available;
//DeadCode DAW 23Aug96 	SLong			ac_used;
//DeadCode DAW 23Aug96 	SWord			flightnum [MAX_FLIGHT_NUM];
//DeadCode DAW 23Aug96 	SWord			formationnum [MAX_FLIGHT_NUM];
//DeadCode DAW 23Aug96 	SWord			squadronform;
//DeadCode DAW 23Aug96 	NextLeadAct		nextleadact [MAX_FLIGHT_NUM];
//DeadCode DAW 23Aug96 	SWord			pilotsperflight;
//DeadCode DAW 23Aug96 	PlaneTypeSelect	actype;										//RDH 07Apr96
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 	SquadronInfo	squad;
//DeadCode DAW 23Aug96 	struct	TkInfo {
//DeadCode DAW 23Aug96 					SWord		timer;
//DeadCode DAW 23Aug96 					SWord		numoftankconvoys;
//DeadCode DAW 23Aug96 					UniqueID	blueguns[MAXGUNS];
//DeadCode DAW 23Aug96 					UniqueID	blueaaa[MAXGUNS];
//DeadCode DAW 23Aug96 				struct Convoy {
//DeadCode DAW 23Aug96 					UniqueID	uid;
//DeadCode DAW 23Aug96  					FileNum		bfield;
//DeadCode DAW 23Aug96 					SWord		size;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 					};	Convoy convoys[MAXCONVOYS];
//DeadCode DAW 23Aug96 			 };		
//DeadCode DAW 23Aug96 		TkInfo	tkinfo;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 	SWord		acesavail,
//DeadCode DAW 23Aug96 				reservesavail;
//DeadCode DAW 23Aug96 	FileNum		playerbfield;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 endstruct	(CampaignInitDef);
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 substruct	(CampaignDef,CampaignInitDef)
//DeadCode DAW 23Aug96 //DeadCode RDH 24Jan96 //	PilotType*	currpilotlist;
//DeadCode DAW 23Aug96 	UniqueID	routesstartuids[MAXROUTES];
//DeadCode DAW 23Aug96 	PilotType	*aces,
//DeadCode DAW 23Aug96 				*reserves;
//DeadCode DAW 23Aug96 	SWord	playerslot;
//DeadCode DAW 23Aug96 	FileNum	mainbfield;
//DeadCode DAW 23Aug96 	FileNum	introsheetart;
//DeadCode DAW 23Aug96 	FileNum	intropadart;
//DeadCode DAW 23Aug96 	FileNum	introiconart;
//DeadCode DAW 23Aug96 	FileNum	cr_iconart;
//DeadCode DAW 23Aug96 	FileNum	lc_iconart;
//DeadCode DAW 23Aug96 	FileNum	introsmack;
//DeadCode DAW 23Aug96 	FileNum	introquarterart;
//DeadCode DAW 23Aug96 	FileNum	historyart;
//DeadCode DAW 23Aug96 	FileNum	personnelart;
//DeadCode DAW 23Aug96 	FileNum	junctionart;
//DeadCode DAW 23Aug96 	FileNum	squadart;
//DeadCode DAW 23Aug96 	FileNum	saveart;
//DeadCode DAW 23Aug96 	FileNum	savedialogue;
//DeadCode DAW 23Aug96 	FileNum	quitart;
//DeadCode DAW 23Aug96 	FileNum	padart;
//DeadCode DAW 23Aug96 	FileNum	mainiconart;
//DeadCode DAW 23Aug96 	FileNum	flightart;
//DeadCode DAW 23Aug96 	FileNum	newstextart;
//DeadCode DAW 23Aug96 	FileNum	newsgraphicart;
//DeadCode DAW 23Aug96 	FileNum	flightgraphicart;
//DeadCode DAW 23Aug96 	FileNum	acsmallart;
//DeadCode DAW 23Aug96 	FileNum	acmedart;
//DeadCode DAW 23Aug96 	FileNum	aclargeart;
//DeadCode DAW 23Aug96 	FileNum	paintshopart;
//DeadCode DAW 23Aug96 	FileNum	introtextart;
//DeadCode DAW 23Aug96 	TextRef	objecttext;
//DeadCode DAW 23Aug96 	TextRef	introtext;
//DeadCode DAW 23Aug96 	TextRef	editnametext;
//DeadCode DAW 23Aug96 	TextRef	editnametitle;
//DeadCode DAW 23Aug96 //following must be the last field
//DeadCode DAW 23Aug96 	CampaignInitDef*	restartdata;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 void	SetCurrMission (MissionType*);
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 endstruct	(CampaignDef);
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 #ifndef	MISS_MAN_Included2
//DeadCode DAW 23Aug96 #define	MISS_MAN_Included2
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 //DeadCode RDH 13Jun96 #include	"uid.g"												//RDH 21Dec95
//DeadCode DAW 23Aug96 struct	 MissMan
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96 //DeadCode DAW 02Apr96 	enum	{MAXCAMPAIGNNUM = 6,MAXACTUALCAMPAIGNNUM = 4};
//DeadCode DAW 23Aug96 	enum	CampaignName {
//DeadCode DAW 23Aug96 		CIRCUSCAMPAIGN = 0,
//DeadCode DAW 23Aug96 		HATRINGCAMPAIGN,
//DeadCode DAW 23Aug96 		SPRINGCAMPAIGN,
//DeadCode DAW 23Aug96 		TANKCAMPAIGN,
//DeadCode DAW 23Aug96 		RUNDEMOCAMPAIGN,
//DeadCode DAW 23Aug96 		SCRAMBLECAMPAIGN,
//DeadCode DAW 23Aug96 		MINCAMPAIGNNUM = 0,
//DeadCode DAW 23Aug96 		MAXCAMPAIGNNUM = 6,
//DeadCode DAW 23Aug96 		MAXACTUALCAMPAIGNNUM = 4
//DeadCode DAW 23Aug96 		};
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 	CampaignName 	currcampaignnum;
//DeadCode DAW 23Aug96 	struct	CampaignDef		*currcamp,
//DeadCode DAW 23Aug96 							*campaigntable[MAXCAMPAIGNNUM];
//DeadCode DAW 23Aug96 	TextPerm	playernameref;
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 extern	MissMan Miss_Man;
//DeadCode DAW 23Aug96 extern	SpecialEventBitField	specialeventbits;
//DeadCode DAW 23Aug96 extern	NewsEventField			newsevent;
//DeadCode DAW 23Aug96 struct	WpListType;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 struct	MissionType
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96 	FileNum	introsmack;
//DeadCode DAW 23Aug96 	TextRef	newstext;
//DeadCode DAW 23Aug96 	TextRef	missiontext;
//DeadCode DAW 23Aug96 	SLong	missiondate;
//DeadCode DAW 23Aug96 	SLong	timeofday;
//DeadCode DAW 23Aug96 	WpListType* wplist;
//DeadCode DAW 23Aug96 	FileNum	playerbf;
//DeadCode DAW 23Aug96 	SWord	numofsquadronac;	
//DeadCode DAW 23Aug96 	SWord	numofflightac;	
//DeadCode DAW 23Aug96 	FormationTypeIndex	formationtypeindex;
//DeadCode DAW 23Aug96 	FileNum	backdropart;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 struct	WpSetType
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96 	UniqueID	mainobjective;
//DeadCode DAW 23Aug96 	UniqueID	subobjective;
//DeadCode DAW 23Aug96 	UniqueID	wp1;
//DeadCode DAW 23Aug96 	UniqueID	wp2;
//DeadCode DAW 23Aug96 	UniqueID	wp3;
//DeadCode DAW 23Aug96 	UniqueID	zero;
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 struct	WpListType
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96  	SWord	noofentries;
//DeadCode DAW 23Aug96 	WpSetType*	wpset [4];
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 struct	BfTypeList
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96  	SWord	noofentries;
//DeadCode DAW 23Aug96 	SWord	bfields [24];
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 enum	pilotskill 	{NOVICE = 0,REGULAR,VETERAN,ACE,HERO};
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 enum	pilotmorale {PM_ROCKBOTTOM = 0,PM_VERYPOOR = 6000,PM_POOR = 11000,PM_AVERAGE = 16000,PM_GOOD = 21000,PM_VERYGOOD = 26000,PM_EXCELLENT = 31000,PM_TOPMORALE = 32767};	
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 enum	pilotchar	{TACTICIAN = 0,MRAVERAGE,CAVALIER};
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 enum	pilotstatus	{NOTFLYING = 0,FLYING};
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 enum	SkillType
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 		{SKILL_NOVICE = 0,SKILL_REGULAR,SKILL_VETERAN,SKILL_ACE,SKILL_HERO};
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 enum	MoraleType
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 		{MORALE_ROCKBOTTOM = 0,MORALE_VERYPOOR = 5000,MORALE_STAGE = 5000,MORALE_POOR =10000,MORALE_MEDIUM = 15000,MORALE_GOOD =20000,MORALE_VERYGOOD = 25000,MORALE_EXCELLENT = 30000,MORALE_TOPMORALE = 32767 };
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 enum	CharacterType
//DeadCode DAW 23Aug96 //DeadCode RDH 30Jan96 		{CHAR_TACTICIAN = 0,CHAR_MRAVERAGE,CHAR_CAVALIER};		
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 struct PilotType
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96 	TextRef	name;
//DeadCode DAW 23Aug96 	SkillType	skill;
//DeadCode DAW 23Aug96 	pilotstatus	status;
//DeadCode DAW 23Aug96 	CharacterType	character;
//DeadCode DAW 23Aug96 	MoraleType	morale;
//DeadCode DAW 23Aug96 //DeadCode RDH 11Aug96 	FileNum	photo;
//DeadCode DAW 23Aug96 	NextFollAct	nextfollact;
//DeadCode DAW 23Aug96 	SWord	dayssincerest;
//DeadCode DAW 23Aug96 	SWord	kills;
//DeadCode DAW 23Aug96 //DeadCode MS 18Aug96 	SWord	flyinghours;
//DeadCode DAW 23Aug96 	SWord	daystorecover;
//DeadCode DAW 23Aug96 struct	ImageMaps
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96  	UByte	topwing;
//DeadCode DAW 23Aug96  	UByte	tail;
//DeadCode DAW 23Aug96  	UByte	btmwing;
//DeadCode DAW 23Aug96  	UByte	fuselage;
//DeadCode DAW 23Aug96  	UByte	other;
//DeadCode DAW 23Aug96 	UByte	emblem;
//DeadCode DAW 23Aug96 //DeadCode RDH 20Feb96 	SWord	topwing;
//DeadCode DAW 23Aug96 //DeadCode RDH 20Feb96 	SWord	tail;
//DeadCode DAW 23Aug96 //DeadCode RDH 20Feb96 	SWord	btmwing;
//DeadCode DAW 23Aug96 //DeadCode RDH 20Feb96 	SWord	fuselage;
//DeadCode DAW 23Aug96 //DeadCode RDH 20Feb96 	SWord	other;
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 	ImageMaps	imagemaps;
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 SLong const FLIGHTSPERSQUADRON	 = 4;
//DeadCode DAW 23Aug96 SLong const FLYINGFLIGHTSPERSQUADRON	 = FLIGHTSPERSQUADRON - 1;
//DeadCode DAW 23Aug96 SLong const MAXIMAGEMAPSPERAIRCRAFT = 8;
//DeadCode DAW 23Aug96 struct FormationPos
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96 	SLong	range;
//DeadCode DAW 23Aug96 	ANGLES	bearing;
//DeadCode DAW 23Aug96 	SLong	delta_alt;
//DeadCode DAW 23Aug96 	SWord	alt_icon;
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 	enum					{MAXFLIGHT_FORMS_NUM = 8};
//DeadCode DAW 23Aug96 	enum					{MAXAC_FORMATIONS_NUM = 5};
//DeadCode DAW 23Aug96 struct FormationType
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96 	TextRef			name;
//DeadCode DAW 23Aug96 	FormationPos	wingpos [MAXAC_FORMATIONS_NUM];
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 	enum					{MAXSQUAD_FORMS_NUM = 5};			//RDH 18Aug96
//DeadCode DAW 23Aug96 struct SquadronType
//DeadCode DAW 23Aug96 {
//DeadCode DAW 23Aug96 	TextRef			name;
//DeadCode DAW 23Aug96 	FormationPos	wingpos [FLYINGFLIGHTSPERSQUADRON];
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 };
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 typedef FormationType* SingleFormation;
//DeadCode DAW 23Aug96 extern SingleFormation Aircraft_Formations [];
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 typedef SquadronType* SquadFormation;
//DeadCode DAW 23Aug96 extern SquadFormation Squadron_Formations [];
//DeadCode DAW 23Aug96 //------------------------------------------------------------------------------
//DeadCode DAW 23Aug96 typedef	MissionType* DayMission [3];
//DeadCode DAW 23Aug96 extern	DayMission Circus_Missions [];
//DeadCode DAW 23Aug96 typedef	MissionType* SingleMission;
//DeadCode DAW 23Aug96 extern	SingleMission Spring_Missions [];
//DeadCode DAW 23Aug96 extern	SingleMission HatDflt_Missions [];
//DeadCode DAW 23Aug96 extern	SingleMission TnkDflt_Missions [];
//DeadCode DAW 23Aug96 extern	SingleMission Scramble_Missions [];						//RDH 02Aug96
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 typedef	MissionType* MissionFamily [6];
//DeadCode DAW 23Aug96 typedef MissionFamily MissionArea [5];
//DeadCode DAW 23Aug96 extern 	MissionArea Hat_Missions [2];
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 const	PILOTS_PER_SQUADRON = 24;
//DeadCode DAW 23Aug96 //DeadCode RDH 24Jan96 typedef	PilotType*	PilotRef;
//DeadCode DAW 23Aug96 //DeadCode RDH 24Jan96 typedef PilotRef	SquadronPilots [PILOTS_PER_SQUADRON];
//DeadCode DAW 23Aug96 //DeadCode RDH 24Jan96 typedef	PilotType*	PilotList;
//DeadCode DAW 23Aug96 //DeadCode RDH 24Jan96 extern	PilotList Crc_Pilot_List [];
//DeadCode DAW 23Aug96 //DeadCode RDH 24Jan96 extern	PilotList Work_Pilot_List [];
//DeadCode DAW 23Aug96 //DeadCode RDH 24Jan96 extern	PilotList Crc_Ace_List [];
//DeadCode DAW 23Aug96 //DeadCode RDH 24Jan96 extern	PilotList Crc_Reserve_List [];
//DeadCode DAW 23Aug96 //DeadCode RDH 24Jan96 extern	PilotList Crc_Wounded_List [];
//DeadCode DAW 23Aug96 extern	PilotType	Crc_Pilots[],Crc_12Reserves[],Crc_8Aces[];
//DeadCode DAW 23Aug96 extern	PilotType	Hat_Pilots[],Hat_12Reserves[],Hat_8Aces[];
//DeadCode DAW 23Aug96 extern	PilotType	SO_Pilots[],SO_12Reserves[],SO_8Aces[];
//DeadCode DAW 23Aug96 extern	PilotType	Tnk_Pilots[],Tnk_12Reserves[],Tnk_8Aces[];
//DeadCode DAW 23Aug96 extern	PilotType	Active_Pilots[],Temp_Pilots[],Wounded_Pilots[],Dead_Pilots[],Reserve_Pilots[];
//DeadCode DAW 23Aug96 extern	CampaignInitDef::SquadronInfo Temp_Squadron;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 enum	HatMissionFamily {HP_VOLUNTEER = 0,
//DeadCode DAW 23Aug96 			HP_NOCHOICE = 0, HP_BALLOON,HP_PATROL,HP_ESCORT,HP_ROVING};
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 enum	SquadPanelSelection {PERSONNEL = 0, CONFIGURE, PREFERENCES, PAINTSHOP,SAVEGAME};
//DeadCode DAW 23Aug96 enum	ConfigureSelection	{SAVECONFIGURE,RETURNFROMCONFIGURE,CANCELCONFIGURE,GOTOJOYSTICKCONFIG};
//DeadCode DAW 23Aug96 enum	FlightInfoSelection { FLYNOW= 0, JUSTRETURN};
//DeadCode DAW 23Aug96 SWord	const	MAXCIRCUSMISSIONS = 21;
//DeadCode DAW 23Aug96 SWord	const	MAXHATMISSIONS = 21;
//DeadCode DAW 23Aug96 SWord	const	MAXSPRINGMISSIONS = 24;
//DeadCode DAW 23Aug96 SWord	const	MAXTANKMISSIONS = 16;
//DeadCode DAW 23Aug96 SWord	const	CIRCUSPLAYERSLOT = 0;
//DeadCode DAW 23Aug96 SWord	const	HATPLAYERSLOT = 7;
//DeadCode DAW 23Aug96 SWord	const	CIRCUSTARGETKILL = 52;
//DeadCode DAW 23Aug96 SWord	const	PILOTACTIVE = 0;
//DeadCode DAW 23Aug96 SWord	const	PILOTDEAD = -1;
//DeadCode DAW 23Aug96 SWord	const	PILOTS_IN_RESERVE = 12;
//DeadCode DAW 23Aug96 SWord	const	ACESLIST = 8;
//DeadCode DAW 23Aug96 SWord	const	CASUALTYLIST = ACESLIST + PILOTS_IN_RESERVE;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 //DeadCode RDH 22Jan96 //SLong const PILOTSPERFLIGHT	 = 6;
//DeadCode DAW 23Aug96 //DeadCode RDH 22Jan96 SLong const FLIGHTSPERSQUADRON	 = 4;
//DeadCode DAW 23Aug96 //DeadCode RDH 22Jan96 SLong const FLYINGFLIGHTSPERSQUADRON	 = FLIGHTSPERSQUADRON - 1;
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 #endif
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 #undef	basestruct
//DeadCode DAW 23Aug96 #undef	substruct
//DeadCode DAW 23Aug96 #undef	endstruct
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 #endif
//DeadCode DAW 23Aug96 
//DeadCode DAW 23Aug96 ==========
