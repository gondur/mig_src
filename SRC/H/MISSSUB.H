//------------------------------------------------------------------------------
//Filename       misssub.h
//System         
//Author         Jim Taylor
//Date           Thu 22 Aug 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	MISSSUB_Included
#define	MISSSUB_Included

#define	DEFAULT_MISSSUB 0

#include	"text.h"
#include	"ranges.h"
//#include	"node.h"

enum	{	
				MAXTNKWPINROUTE = 2

			};

//DeadCode MS 27Nov96 enum					{LOWCLOUD = 0,CLOUDAT10000FT,CLEARWEATHER,BADWEATHER, MAXWEATHERNUM = 4};
enum					{LOWCLOUD = 0,CLOUDAT10000FT,BADWEATHER,BADWEATHER10000FT, MAXWEATHERNUM = 4};

enum	SpecialEventBit {SpecialEventMIN = 0,HOMEBASEDESTROYED = 0,
						PLAYERKILLED, RESERVEEXHAUSTED,
//above this you are dead
						PLAYERWOUNDED,RESERVES_2LEFT,RESERVES_6LEFT,
						ACEKILLED,NEARTARGET,
						FATALITYINSQUAD,WOUNDEDINSQUAD,
						MORALEEXCELLENT,MORALEGOOD,MORALEPOOR,MORALEROCKBOTTOM,
//DeadCode RDH 13Mar97 						BESTDAY,SUGGESTEASIERAREA,SUGGESTDIFFICULTAREA,
						BESTDAY,
//
						LIEUTENANTPROMOTION,CAPTAINPROMOTION,

//Spring Offensive training
//DeadCode RDH 13Mar97 						CRASHLAND,BENTGEAR,GOODLANDING,LANDEDONSQUARE,
//DeadCode RDH 13Mar97 						STAYEDVCLOSETOCO,STAYEDCLOSETOCO,STAYEDINVICINITYOFCO,MILESFROMCO,
//DeadCode RDH 13Mar97 						SEENBYCO,NOTSEENBYCO,HITSNEARCO,
						CRASHLAND,BENTGEAR,GOODLANDING,
						QUITTOOSOON,QUITTOOSOONSO_1,
//DeadCode RDH 13Mar97 //SO debriefs
//DeadCode RDH 13Mar97 						LASTMISSIONSTRONG,LASTMISSIONWEAK,
//DeadCode RDH 13Mar97 						SO_WON,SO_LOST,
//DeadCode RDH 25Aug96 //tank debriefs
//DeadCode RDH 25Aug96 						HITTANKANIM,
//DeadCode RDH 13Mar97 
//DeadCode RDH 13Mar97 						EVACUATEFAILED,EVACUATESUCCESSFUL,
//DeadCode RDH 13Mar97 						SO_EVACUATEFAILED,SO_EVACUATESUCCESSFUL,//RDH 18Dec96
//DeadCode RDH 13Mar97 
//DeadCode RDH 13Mar97 //tank lost
//DeadCode RDH 13Mar97 						TANKCAMPAIGNLOST,TANK_BUILDPONTOONBRIDGE,TANKNEARBRIDGES,

						CAMPAIGNLOSTTAEJONOVERRUN,
						CAMPAIGNWONENTEREDPYONGYANG,
						CAMPAIGNLOST,
//awarded medals
						AWARDED_MEDALOFHONOUR,
//DeadCode RDH 13Mar97 //player decisions in combat
//DeadCode RDH 13Mar97 						PLAYER_ENGAGES_SHOULD,PLAYER_ENGAGES_SHOULDNOT,
//DeadCode RDH 13Mar97 						PLAYER_NOTENGAGE_SHOULD,PLAYER_NOTENGAGE_SHOULDNOT,
//landing
						PLAYERLANDEDINCOUNTRY,PLAYERCAPTURED,	//RDH 29Nov96
//target hit
						ATTACKEDAIRFRIENDLY,KILLEDAIRFRIENDLY,KILLEDGROUNDFRIENDLY,
						ENEMYDESTROYEDTARGET,FRIENDLYDESTROYEDTARGET,
//DeadCode RDH 25Aug96 					  HOMEBASEDAMAGED,SpecialEventMAX};
					  SpecialEventMAX};
//			In 3d Temp_Pilots morale

MAKEFIELD (SpecialEventBit,SpecialEventMIN,SpecialEventMAX);


enum	NewsEvent {NewsEventMIN = 0, NEWSWOUNEDRECOVERED, NEWSACEIN,
									 NEWSACEOUT,NEWSMISSION,NEWSMERITPROMOTION,
									 NEWSDEADMANPROMOTION,NEWSTHEPROMOTION,
									NEWSWOUNDEDMANPROMOTION,	//DAW 23Aug96
									//Spring Offensive: go operational
									 NEWSOPERATIONALGOOD,NEWSOPERATIONALBAD,
//last mission
						NEWSLASTMISSIONOFCAMPAIGN,
//updates
						NEWSCRCUPDATE,	
						NEWS_HAT_25_GOOD,
						NEWS_HAT_25_BAD,
						NEWS_HAT_50_GOOD,
						NEWS_HAT_50_BAD,
						NEWS_HAT_75_GOOD,
						NEWS_HAT_75_BAD,
						NEWS_SPRING_25_GOOD,
						NEWS_SPRING_25_BAD,
						NEWS_SPRING_50_GOOD,
						NEWS_SPRING_50_BAD,
						NEWS_SPRING_75_GOOD,
						NEWS_SPRING_75_BAD,



									//Spring Offensive: lastday
									NEWSSTRONGPOSITION,NEWSWEAKPOSITION,NEWSAVERAGEPOSITION,
									NEWSBESTDAY,				//DAW 23Aug96
										NewsEventMAX};


MAKEFIELD (NewsEvent,NewsEventMIN,NewsEventMAX);



enum	pilotstatus	{NOTFLYING = 0,FLYING, WOUNDED, MIA, IS_DEAD = MIA, KIA};
//moved to flyinit.h											//RDH 23Sep96
//DeadCode JIM 10Jun96 enum	SkillType
//DeadCode JIM 10Jun96 		{SKILL_NOVICE = 0,SKILL_STAGE = 1,SKILL_POOR,SKILL_REGULAR,SKILL_VETERAN,SKILL_ACE,SKILL_HERO};
//DeadCode RDH 23Sep96 enum	MeritType
//DeadCode RDH 23Sep96 		{MERIT_ROCKBOTTOM = 0,MERIT_INITIAL = 1000,MERIT_2LFTEXPERIENCED =5000,
//DeadCode RDH 23Sep96 		MERIT_LFT = 8000,
//DeadCode RDH 23Sep96 		MERIT_CAPTAIN = 12000,MERIT_MAJOR =18000,MERIT_MAJORHONOUR = 27000,
//DeadCode RDH 23Sep96 		MERIT_MAJORHONOURPLUS = 30000,MERIT_TOP = 65534,MERIT_IMPOSSIBLE = 65535,
//DeadCode RDH 23Sep96 		
//DeadCode RDH 23Sep96 //Spring Offensive merits to get operational		
//DeadCode RDH 23Sep96 		MERIT_OPERATIONAL = 3000
//DeadCode RDH 23Sep96 			
//DeadCode RDH 23Sep96 
//DeadCode RDH 23Sep96 		};
//DeadCode RDH 23Sep96 //aims is to get 30000 merit points by end of campaign			//RDH 23Sep96
//DeadCode RDH 23Sep96 //Circus	36 kills: 2 kills a mission, 20 missions -> 750 merit per kill
//DeadCode RDH 23Sep96 enum	DeltaMeritType
//DeadCode RDH 23Sep96 		{
//DeadCode RDH 23Sep96 		MERIT_TARGET_DESTROYED = 3000,
//DeadCode RDH 23Sep96 		MERIT_KILL = 750,
//DeadCode RDH 23Sep96 		MERIT_VIS_MSN_SUCCESS =4000,
//DeadCode RDH 23Sep96 		MERIT_OP_CRASHLAND = -300,
//DeadCode RDH 23Sep96 		MERIT_OP_BENTGEAR = -100,
//DeadCode RDH 23Sep96 		MERIT_OP_KANGAROO = 300,
//DeadCode RDH 23Sep96 		MERIT_OP_GOODLANDING = 100,
//DeadCode RDH 23Sep96 		MERIT_OP_LANDEDONSQUARE = 500,
//DeadCode RDH 23Sep96 		MERIT_OP_STAYEDVCLOSETOCO = 3000,
//DeadCode RDH 23Sep96 		MERIT_OP_STAYEDCLOSETOCO = 1500,
//DeadCode RDH 23Sep96 		MERIT_OP_STAYEDINVICINITYOFCO = 1000,
//DeadCode RDH 23Sep96 		MERIT_OP_MILESFROMCO = -1000,
//DeadCode RDH 23Sep96 		MERIT_OP_SEENBYCO = -1000,
//DeadCode RDH 23Sep96 		MERIT_OP_NOTSEENBYCO =1000,
//DeadCode RDH 23Sep96 		MERIT_OP_HITSNEARCO = 3000
//DeadCode RDH 23Sep96 
//DeadCode RDH 23Sep96 		};


//DeadCode RDH 09Sep96 enum	MoraleType
//DeadCode RDH 09Sep96 		{MORALE_ROCKBOTTOM = 0,MORALE_VERYPOOR = 40,MORALE_STAGE = 40,MORALE_HALFSTAGE = 20,
//DeadCode RDH 09Sep96 			MORALE_MINUSHALFSTAGE = -20,
//DeadCode RDH 09Sep96 		MORALE_POOR =80,MORALE_MEDIUM = 120,MORALE_GOOD =160,MORALE_VERYGOOD = 200,MORALE_EXCELLENT = 240,MORALE_TOPMORALE = 255 };
//DeadCode JIM 10Jun96 enum	CharacterType	- now in flyinit.h
//DeadCode JIM 10Jun96 		{CHAR_TACTICIAN = 0,CHAR_MRAVERAGE,CHAR_CAVALIER,CHAR_align=255};		
enum 	RankType {SECLIEUTENANT= 0,SECLIEUTENANT_EXPERT,LIEUTENANT,CAPTAIN,MAJOR, RANK_INC = 1};
enum					{MAXCONVOYS = 12,MAXTANKCONVOYS = 8,MAXTRUCKCONVOYS = 6,MAXROUTES = 4,MAXGUNS = 16};

enum	HatMissionFamily {HP_VOLUNTEER = 0,
			HP_NOCHOICE = 0, HP_BALLOON,HP_PATROL,HP_ESCORT,HP_ROVING};

enum	SquadPanelSelection {PERSONNEL = 0, CONFIGURE, PREFERENCES, PAINTSHOP,SAVEGAME};
enum	ConfigureSelection	{SAVECONFIGURE,RETURNFROMCONFIGURE,CANCELCONFIGURE,GOTOJOYSTICKCONFIG,
								CANCELSCRNCONFIG,ACCEPTSCREENCONFIG,TRYSELECTEDSCREENCONFIG

								};
enum	CtrlVar	{
								GOTOACCEL,GOTOMAP
				};
enum	FlightInfoSelection { FLYNOW= 0, JUSTRETURN};

enum	{
//		MAXCIRCUSMISSIONS 		= 21,
//		MAXHATMISSIONS 			= 21,
//DeadCode RDH 23Nov96 		MAXSPRINGMISSIONS 		= 24,
//		MAXSPRINGMISSIONS 		= 15,							//RDH 23Nov96
//		MAXTANKMISSIONS 		= 16,

//		CIRCUSPLAYERSLOT 		= 0,
//		HATPLAYERSLOT 			= 11,

//		CIRCUSTARGETKILL 		= 52,
		RADIOMESSAGELEN			= 128,
		PASSWORDNAMELEN			= 11,
		SESSIONNAMELEN			= 128,
		PLAYERNAMELEN			= 21,
		PILOTS_PER_SQUADRON 	= 24,
		PILOTABLE_SQUADRONS		=	5,
		PILOTS_PER_CAMPAIGN 	= (int)PILOTS_PER_SQUADRON* (int)PILOTABLE_SQUADRONS,
		PILOTACTIVE 			= 0,
		PILOTDEAD 				= -1,
		PILOTS_IN_RESERVE 		= 80,
		ACESLIST 				= 0,
		CASUALTYLIST 			= 20,		//(int)ACESLIST + (int)PILOTS_IN_RESERVE,
		FLIGHTSPERSQUADRON	 	= 4,
		FLYINGFLIGHTSPERSQUADRON= 32,//(int)FLIGHTSPERSQUADRON - 1,//Jim 30 jun 98

		WRAPMIGSQUADRONS		=4,
		MAXMIGSQUADRONS			=12,		
//		MAXIMAGEMAPSPERAIRCRAFT = 8,
		};

struct	MissionType;
typedef	MissionType* DayMission [3];
typedef	MissionType* SingleMission;

typedef	MissionType* MissionFamily [6];
typedef MissionFamily MissionArea [5];

extern	SingleMission Spring51_Missions [];
extern	SingleMission PeaceTalk_Missions [];
extern	SingleMission Intro_Missions [];
extern	SingleMission Scramble_Missions [];						//RDH 02Aug96
extern	SingleMission H2H_Missions [];						//RDH 02Aug96
extern 	MissionArea Hat_Missions [2];

struct FormationPos
{
	SLong	range;
	ANGLESInst	bearing;
	SLong	delta_alt;
	SWord	alt_icon;
};

	enum					{MAXFLIGHT_FORMS_NUM = 8};
	enum					{MAXAC_FORMATIONS_NUM = 16,MAXAC_EXTENDEDFORMATIONS_NUM=11};
struct FormationType
{
	int		numentries;
//	TextRef			name;
	FormationPos	wingpos[MAXAC_FORMATIONS_NUM];
//DeadCode RDH 24Sep96 	FormationPos	wingpos [MAXAC_FORMATIONS_NUM];

};



	enum					{MAXSQUAD_FORMS_NUM = 5};			//RDH 18Aug96
struct SquadronType
{
	int numentries;
//	TextRef			name;
	FormationPos	wingpos [FLYINGFLIGHTSPERSQUADRON];

};

typedef FormationType* SingleFormation;
extern SingleFormation Aircraft_Formations [];

typedef SquadronType* SquadFormation;
extern SquadFormation Squadron_Formations [];

//DEADCODE JIM 25/03/99 struct MapWpSet
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	UniqueID	uid;
//DEADCODE JIM 25/03/99 	SLong		worldx;
//DEADCODE JIM 25/03/99 	SLong		worldy;
//DEADCODE JIM 25/03/99 	SLong		worldz;
//DEADCODE JIM 25/03/99 	BFieldWaypointActions	action;
//DEADCODE JIM 25/03/99 	SLong		mapx;
//DEADCODE JIM 25/03/99 	SLong		mapy;
//DEADCODE JIM 25/03/99 	SWord		flags;
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 struct TnkMapWpSet {										//RDH 08Oct96
//DEADCODE JIM 25/03/99 					UniqueID	target_uid;
//DEADCODE JIM 25/03/99 					SLong		worldx;
//DEADCODE JIM 25/03/99 					SLong		worldy;
//DEADCODE JIM 25/03/99 					SLong		worldz;
//DEADCODE JIM 25/03/99 					SWord		action;
//DEADCODE JIM 25/03/99 					SLong		mapx;
//DEADCODE JIM 25/03/99 					SLong		mapy;
//DEADCODE JIM 25/03/99 					SWord		flags;
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 					};
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 struct PaperMaps
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	SLong		mapx;
//DEADCODE JIM 25/03/99 	SLong		mapy;
//DEADCODE JIM 25/03/99 	SLong		mapw;
//DEADCODE JIM 25/03/99 	SLong		maph;
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//#define MAXPLAYERS 12
#define MAXPLAYERS 8

struct 	PilotName	{ UWord nameref;char initial1,initial2; };

struct PilotHist
{
	typedef PilotName Name;
	Name	name;
	SWord	kills;
	pilotstatus	status;
	RankType	rank;
	SLong		lastdate;
};

//structure redefined 11/8/98 rdh
enum	HideSkills
{
	HSflyingskill=0,
	HScombatskill=8,
	HSflyingpotential=16,
	HScombatpotential=24,
	HStoskill=4,
	HSmask=255,
	HSskillmask=15,
	HSallskills=0x01010101
};
struct PilotType
{
	typedef PilotName Name;
	Name		name;
	HideSkills	hideskills;
#ifndef	__BCPLUSPLUS__
	int	BigFlyingSkill()		{return (UByte)((hideskills>>HSflyingskill)&HSmask);}
	int	BigCombatSkill()		{return (UByte)((hideskills>>HScombatskill)&HSmask);}
	int	BigFlyingPotential()	{return (UByte)((hideskills>>HSflyingpotential)&HSmask);}
	int	BigCombatPotential()	{return (UByte)((hideskills>>HScombatpotential)&HSmask);}
	SkillType	FlyingSkill()		{return (SkillType)(UByte)((hideskills>>(HSflyingskill+HStoskill))&HSskillmask);}
	SkillType	CombatSkill()		{return (SkillType)(UByte)((hideskills>>(HScombatskill+HStoskill))&HSskillmask);}
	void	SetFlySkill(SkillType s)	{hideskills=HideSkills((hideskills&~(HSmask<<HSflyingskill))+(s<<(HSflyingskill+HStoskill)));}//DAW 26May99
	void	SetCombSkill(SkillType s)	{hideskills=HideSkills((hideskills&~(HSmask<<HScombatskill))+(s<<(HScombatskill+HStoskill)));}//DAW 26May99
	void	SetBigFlySkill(int s)	{hideskills=HideSkills((hideskills&~(HSmask<<HSflyingskill))+(s<<HSflyingskill));}//DAW 26May99
	void	SetBigCombSkill(int s)	{hideskills=HideSkills((hideskills&~(HSmask<<HScombatskill))+(s<<HScombatskill));}//DAW 26May99
//DeadCode DAW 09Jul99 	void	SetFlySkill(SkillType s)	{hideskills=HideSkills((hideskills&~(HSskillmask<<HSflyingskill))+(s<<(HSflyingskill+HStoskill)));}//DAW 26May99
//DeadCode DAW 09Jul99 	void	SetCombSkill(SkillType s)	{hideskills=HideSkills((hideskills&~(HSskillmask<<HScombatskill))+(s<<(HScombatskill+HStoskill)));}//DAW 26May99
//DeadCode DAW 09Jul99 	void	SetBigFlySkill(int s)	{hideskills=HideSkills((hideskills&~(HSskillmask<<HSflyingskill))+(s<<HSflyingskill));}//DAW 26May99
//DeadCode DAW 09Jul99 	void	SetBigCombSkill(int s)	{hideskills=HideSkills((hideskills&~(HSskillmask<<HScombatskill))+(s<<HScombatskill));}//DAW 26May99
#endif
	pilotstatus	status;
	MoraleType	morale;
	RankType	rank;
	SWord		missionscompleted;
	NextFollAct	nextfollact;
	SWord	dayssincerest; //actually periods.
	SWord	kills;
	SWord	airkillslastmsn;
	SWord	daystorecover;
	SWord	aircraftnum;
	UByte	decal;
//	UByte	airkillslastmiss;
	UByte	grndhitslastmiss;
};



//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 struct	WpSetType
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	UniqueID	mainobjective;
//DEADCODE JIM 25/03/99 	UniqueID	subobjective;
//DEADCODE JIM 25/03/99 	UniqueID	wp1;
//DEADCODE JIM 25/03/99 	UniqueID	wp2;
//DEADCODE JIM 25/03/99 	UniqueID	wp3;
//DEADCODE JIM 25/03/99 	UniqueID	zero;
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 struct	WpListType
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99  	SWord	noofentries;
//DEADCODE JIM 25/03/99 	WpSetType*	wpset[1];
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 struct	MissionType
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	FileNum	introsmack;
//DEADCODE JIM 25/03/99 	TextRef	newstext;
//DEADCODE JIM 25/03/99 	TextRef	missiontext;
//DEADCODE JIM 25/03/99 	SLong	missiondate;
//DEADCODE JIM 25/03/99 	SLong	timeofday;
//DEADCODE JIM 25/03/99 	WpListType* wplist;
//DEADCODE JIM 25/03/99 	FileNum	playerbf;
//DEADCODE JIM 25/03/99 	SWord	numofsquadronac;	
//DEADCODE JIM 25/03/99 	SWord	numofflightac;	
//DEADCODE JIM 25/03/99 	FormationTypeIndex	formationtypeindex;
//DEADCODE JIM 25/03/99 	SWord		weathernum;											//RDH 02Oct96
//DEADCODE JIM 25/03/99 	SWord	windspeed;
//DEADCODE JIM 25/03/99 	ANGLESInst	winddirection;			//direction from which the wind comes
//DEADCODE JIM 25/03/99 	FileNum	backdropart;
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 struct	BfTypeList
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99  	SWord	noofentries;
//DEADCODE JIM 25/03/99 	SWord	bfields[2];
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 



 	enum		{MAX_PACKAGE_NUM = 5,MAX_COMPONENT_NUM = 4};

	enum	FamilyType{PFT_NULL = 4,
					PFT_HEAVYSTRIKE = 0,
					PFT_STRIKE = 1,		
					PFT_PATROL = 2,		
					PFT_CAS = 3,
					PFT_ALIGN = 0xffff
					};
inline	SWord&	operator *(FamilyType& f){return(SWord&) f;}
					

	enum	Type{
			HS_BASE = 0,	
			HS_ALPHADIRECT = HS_BASE,	
			HS_ALPHAINDIRECT,	
			HS_BETADIRECT,		
			HS_BETAINDIRECT,	
			HS_UNESCORTED,		
			HS_UNESCORTEDNIGHT,
			S_BASE,	
			S_BOMB = S_BASE,	
			S_ROCKET,	
			S_CRACKBURN,
			S_NAPALM,	
			S_STRAFF,
			PTRL_BASE,		
			PTRL_BARCAP = PTRL_BASE,		
			PTRL_TACTICALINTERDICT,
			PTRL_AGGCAP,
			CAS_BASE,	
			CAS_BOMB = CAS_BASE,	
			CAS_ROCKET,	
			CAS_CRACKBURN,
			CAS_NAPALM,	
			CAS_STRAFF,
			T_NULL,
			T_ALIGN = 0xffff
				};

inline	SWord&	operator *(Type& f){return(SWord&) f;}


enum	Stores	{
				GUNSONLY = 0,	B29_STD = 0,
				LR_BOMB = 1,	B29_TARZON = 1,
				LR_HDBOMB,
				LR_ROCKET,
				LR_NAPALM,
				CAS_NB,
				CAS_RB,
				CAS_NR,
				STORES_ALIGN = 0xffff
			};

inline	SWord&	operator *(Stores& f){return(SWord&) f;}

enum	Squadron{
		F86Squad = 0,
		F84Squad,
		F80Squad,
		F51Squad,
		B29Squad,




		};

inline	SWord&	operator *(Squadron& f){return(SWord&) f;}

//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 enum  	{
//DEADCODE JIM 25/03/99 			PASSIVE,ACTIVE,SIBLING,CONTROL
//DEADCODE JIM 25/03/99 		};	
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 enum	ListControl{LISTINACTIVE,LISTACTIVE};
//DEADCODE JIM 25/03/99 enum	{LISTCONTROLMAX = 16, STORESPERACMAX = 8,CONFIGSTORESAC = 6};

//MARK, this is the list of events in the order of use			//MS 04Mar99

enum	RedEvents
{
	MIGEV_SANCPAT,
	MIGEV_SAFEPAT,
	MIGEV_INTERSOUTH1,
	MIGEV_STRAIGHTRUN,	//straight run down with no diversions - easy to stop
	MIGEV_INTERCEPT1,	
	MIGEV_BOMBERS1,
//-------------------------------------------------------------------
	MIGEV_INTERSOUTH2,
	MIGEV_INTERCEPT2,
	MIGEV_WAITWEAK,
	MIGEV_CUTWEAK,	
//-------------------------------------------------------------------
	MIGEV_CONTRAILFOCUS,
	MIGEV_BOMBERS2,
//-------------------------------------------------------------------
	MIGEV_INTERSOUTH3,
	MIGEV_INTERCEPT3,
//-------------------------------------------------------------------
	MIGEV_THREELEVELS,
	MIGEV_BOMBERS3,
//-------------------------------------------------------------------
	MIGEV_MOVINGROUND,
	MIGEV_STATICROUND,
//-------------------------------------------------------------------
	MIGEV_ENDRUNDECOY,
	MIGEV_LOWSWEEP,
//-------------------------------------------------------------------
	MIGEV_UPPERCUT,
	MIGEV_INTERCEPT4,
//-------------------------------------------------------------------
	MIGEV_STAIRCASE,
	MIGEV_SUPERIOR1,
//-------------------------------------------------------------------
	MIGEV_SLEDGEHAMMER,
	MIGEV_SUPERIOR2,
//-------------------------------------------------------------------
	MIGEV_WESTTRAIN,
	MIGEV_BIGTRAIN1,
//-------------------------------------------------------------------
	MIGEV_BIGTRAIN2,
	MIGEV_BIGTRAIN3,
	MIGEV_BIGTRAIN4,
	MIGEV_BIGTRAIN5,
	MIGEV_BIGTRAIN6,
	MIGEV_EASTCOAST,
	MIGEV_CENTTRAIN,
	MIGEV_WPOORTRAIN,
	MIGEV_CAREFUL,
	MIGEV_CONFRONT,		//migs attack sabres to clear them
	MIGEV_CAREFUL2,
//DeadCode RDH 05Mar99 	MIGEV_TRAIL,
//DeadCode RDH 05Mar99 	MIGEV_STRING,
//DeadCode RDH 05Mar99 	MIGEV_JAWS,
//DeadCode RDH 05Mar99 	MIGEV_ZVENO,
//DeadCode MS 04Mar99 	MIGEV_DECOYACTIVE,
//DeadCode MS 04Mar99 	MIGEV_DECOYPASSIVE,
//DeadCode RDH 05Mar99 	MIGEV_BAIT,
//DeadCode RDH 05Mar99 	MIGEV_SLIGHTHAND,
	MIGEV_MAX
};

struct	MigEvent
{
	FileNum					eventbf,alteventbf;			//2 versions: 50-50 chance
	tAggressionLevel		minlevel;
	int						takeofftime;
	SWord					minformsize,maxformsize;	//both 0 = no limit
	enum					{	TARGET=1,		//goes for a target
								DIRECT=2,		//goes direct - no decoy element
								BARCAP=4,		//goes for barcaps
								LOCAL=8,		//stays in Yalu region
								STARTSOUTH=16,	//starts south of MA
								BIGTRAIN=32,	//Is a bigtrain. If selected first then all missions that day will be that train.
								DECOY=64,		//Has a decoy aspect
								TRAIN_TARGET=33,//Its a big train with a target!
								SOUTH_TARGET=17,//starts south with a target
								DIRECT_TARGET=3,//direct run to a target
								LOCAL_TARGET=9,	//local with a target
								DECOY_TARGET=65,//local with a target
								DECLOC_TARGET=73,
							};	//this enum could be more compact...
	int						eventdoes;		
	tFirstEncounterTactics	firsttactics;
	tThreatLevel			mainthreat, secthreat;
};


//DeadCode JIM 19Feb99 struct AcComponent
//DeadCode JIM 19Feb99 {
//DeadCode JIM 19Feb99 	DutyType	duty;
//DeadCode JIM 19Feb99 	Squadron	squadron;
//DeadCode JIM 19Feb99 	SWord		numofflights;
//DeadCode JIM 19Feb99 	Stores		stores;
//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 };
//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 struct WeaponSets
//DeadCode JIM 19Feb99 {
//DeadCode JIM 19Feb99 	ranges		range;
//DeadCode JIM 19Feb99 	TextSnip0	text;
//DeadCode JIM 19Feb99 };
//DeadCode JIM 19Feb99 struct	Package
//DeadCode JIM 19Feb99 {
//DeadCode JIM 19Feb99 	FamilyType	familytype;
//DeadCode JIM 19Feb99 	Type		type;
//DeadCode JIM 19Feb99 	UniqueID	target_uid;
//DeadCode JIM 19Feb99 	SLong		target_eta;
//DeadCode JIM 19Feb99 	WayPoint*	maintroute;
//DeadCode JIM 19Feb99 	AcComponent component[MAX_COMPONENT_NUM];
//DeadCode JIM 19Feb99 	char		name[30];
//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 };

//DeadCode RDH 11Mar97 struct	AirFieldInfo
//DeadCode RDH 11Mar97 {
//DeadCode RDH 11Mar97 	Nationality		nationality;
//DeadCode RDH 11Mar97 	UniqueIDDummy		airfield;	
//DeadCode RDH 11Mar97 	SupplyNode*			northnodes[2];		//used to decide when airfield changes hands
//DeadCode RDH 11Mar97 	SupplyNode*			southnodes[2];		//
//DeadCode RDH 11Mar97 
//DeadCode RDH 11Mar97 };


//extern Package	Predefined_Package[];
//extern WeaponSets Predefined_WeapSet [CONFIGSTORESAC][STORESPERACMAX];
//extern ListControl listcontrol [LISTCONTROLMAX];
//extern AirFieldInfo	airfieldinfo[];
//DEADCODE JIM 25/03/99 extern void SendMsg(UniqueID uid,SWord topfilter,SWord sender,SWord priority,TextRef msg);//RDH 10Mar97
struct	SupplyNode;
struct	SupplyRoute;
struct	SupplyLine;

enum	{MAXMISSIONS = 20, MAXDIRECTIVES = 8,  MAXACPERSQUAD = 16, MAX_DIRGROUPS = 5,
				WAVE2_FLAK=3, WAVE2_ESCORT=4};
struct	DirGroup
{
	char		squadron;
	char		numflights;
};

struct	Mission
{
	int			score;
	FileNum		profile;
	char		note;
	UniqueID	target;
	UniqueID	suppliee;
	DirGroup	group[MAX_DIRGROUPS];		//MAX_GROUPS];
//	char		acresource[7];
//	char		squadron[3];
	bool		escort;
	bool		missionset;
	SupplyNode*	node;
};

struct	SG_Directive
{
	char		type;
	char		strikeac;
	char		fighterac;
};
struct	Directive:SG_Directive
{
	int			targets;
	int			missionsset;
	Mission 	missions[MAXMISSIONS];
};
struct	DirControlData
{
	bool		autogen;
	bool		autodisplay;
	bool		B29avail;
	bool		alphastrikesallowed;
	char		dayssinceB29;

};
struct	SG_DirControl:DirControlData
{
	SG_Directive	directives[MAXDIRECTIVES];
	void	ResetForNewCampaign();
};
struct	DirControl:DirControlData
{
	Directive	directives[MAXDIRECTIVES];

	CON	DirControl();
		void	AllocateAc();

   enum	{ALPHASTRIKE, MEDIUMBOMBERSTRIKE, FBSTRIKE, UNDECIDEDSTRIKE};

UniqueID targetsalloc[10];		//Profile::MAX_PACKS];
int TotalStrikeAc;
int TotalFighterAC; 

int TotalStrikeAcInUse;
int TotalFighterACInUse; 
int	MissionsAlreadyDefined;
int	TargetsAlreadyDefined;
enum {FBTYPES = 3, ACTYPES = 7};
enum	{ACT_NOTSET = 0,ACT_PROP, ACT_JET};
char	acresource[ACTYPES];
char	acalreadyinuse[ACTYPES];

int firsttype;
DirGroup	tmpgroup[MAX_DIRGROUPS];				//MAX_GROUPS];

//char	tempacused[ACTYPES];
int maxscore[7];			//number of directives - resting

char	jetfirst[SQ_B_NONFLYABLE]; 
char	propfirst[SQ_B_NONFLYABLE];


	void	FindScoresAndProfile(int pack, UniqueID uid, SupplyNode* node, int& score, int& maxscore, FileNum& profile, int& type);
	FileNum	FindProfile();
	void	AllocateAcToOneTarget(int pack, UniqueID uid, bool countall);
	void	MakeMiniCampaignMission();								  //RDH 21/03/99
	bool	ModifyRedoIfNecessary(int currpack);			  //RDH 21/06/99

	void AddMission(int d,int j,SupplyNode*  currnode);
	void AddAfMission(int d, int j, int af, int score);
	void ListAirfields(int d);

	void ListSupplyNodes(int d);
	void AddChokeMission(int d, int j, SupplyRoute*  currroute);
	void ListChokes(int d);
	void ListRoutes(int d, SWord type);
	void AddRouteMission(int d, int j, SupplyRoute*  currroute, SWord type);
	void ListFrontLines(int d);

	void	ProcessFrontLine(int d, SupplyLine* sl);
	void	AddCASMission(int d, int j, int score, SupplyLine* sl);


	void	FindTargets(int directive);
	void	AllocateStrike(int d, int i, char& note, int profile);
	void	AllocateFighters(int fightersrequired, int d, int i);
//DEADCODE JIM 11/04/99    	void	AllocateTargets(int d, char striketype);
	bool	AllocateTargets(int d, char striketype, bool escortreq);

	void	AircraftAlreadyUsed(int excludedpack, bool countall);
	void	InitAc();

	int 	MedBomberStrikeRequired(int d, int i, UniqueID target);
	bool 	AllocMedBomberStrike(int strike,  int type);
	int 	FBStrikeRequired(int d, int i, UniqueID target);
	int 	EscortRequired(SupplyNode*  node);
	bool	AllocAc(int grptype,int ac, int type, int d);
	void	AllocateAlphaStrike(int d, int i);
	int		StrikeTypeRequired(int d, int i);
	bool	CloseToChina(int node_num, SupplyNode*  node);
	int 	FlakRequired(UniqueID target, SupplyNode*  node);
	void	UpdatePackageAircraft(int packnum, int d, int i);
	void	SetPackagesFromDirectives();
	int		DirControl::CategoryAvailable(int d, int squad);

	void AutoGenerate();
	int		CalcAcUsedofType(int squad);
	bool	TargetAlreadyAlloc(UniqueID target);
	void	SaveDirectiveChanges();
	void	LoadDirectiveChanges();
	void	InitDirectivesStruct();
	void	ModifyAcInGrp(int packnum, int wavenum, int groupnum, int squad, int numflights);
	int		MakePackage(int d, int i);




};



#endif

