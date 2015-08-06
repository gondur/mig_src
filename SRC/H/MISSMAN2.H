//------------------------------------------------------------------------------
//Filename       missman2.h
//System         
//Author         Jim Taylor
//Date           Thu 22 Aug 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	MISSMAN2_Included
#define	MISSMAN2_Included

#define	DEFAULT_MISSMAN2 0

//this means that I dont want any common files
#define	f_common

#include	"textref.h"
#define		F_SOUNDS
#define		F_COMMON
#include	"Files.g"
#include	"myangles.h"											//RDH 20Dec95
#include	"flyinit.h"											//RDH 20Dec95
#include	"worldinc.h"										//RDH 11Aug96
#include	"debrief.h"
#include	"sky.h"
#ifdef	DEFAULT_MISS_MAN
//
// If the module is declared a second time, then this alternate construction 
// is made to allow instances to occur.
//
	#define	basestruct(subname)							\
	struct	II_##subname			{

	#define	substruct(subname,parentname)				\
	struct	II_##subname			{					\
		II_##parentname	parentinst;

	#define	endstruct(subname)		};					\
	union	I_##subname									\
		{	II_##subname II;subname I;}

	#define	startinst(strucname,instname)	 			\
		II_##strucname	I_##instname	=	{

	#define	endinst(strucname,instname)	 	};			\
		strucname&	instname=*(strucname*)&I_##instname;

#else
//
// This definition defines substructures by simple inheritance
// That will not allow initialisation.
//
	#define	basestruct(subname)							\
	struct	subname					{

	#define	substruct(subname,parentname)				\
	struct	subname : parentname	{

	#define	endstruct(subname)		}

#endif

#define	DEFAULT_MISS_MAN 0
struct	MissionType;
struct	PilotType;
																//DAW 23Aug96
#ifndef	MISS_MAN_Included2										//DAW 23Aug96

#include "bitfield.h"											//DAW 23Aug96
#include	"misssub.h"

#endif
//////////////////////////
//
// This is a far better subdivision of fields
// in order to manage a copy of the active campaign
//
//////////////////////////
basestruct	(CampaignBase)
	int	garbage;
	FileNum	introsmack;
	FileNum	introquarterart;
endstruct(CampaignBase);
//////////////////////////
substruct	(CampaignPtrs,CampaignBase)
//	MissionType*	currmission;
//	MissionType*	dfltmission;

endstruct(CampaignPtrs);
//////////////////////////
substruct	(CampaignStatic,CampaignPtrs)
	UniqueID		playerhomebase;
	UniqueID		playertakeoff;
	bool			firsttime;
	SLong			startdate;
	SLong			ripdate;
	SLong			currdate;
	SLong			lastdate;
	SLong			currtime;
	SLong			dawntime;
	SLong			dusktime;
	SLong			sunsouth;
//	SWord			weathernum;											//RDH 02Oct96
//	struct			Wind {
//						SWord	speed;
//						SWord	velx;
//						SWord	velz;
//						ANGLESInst	direction;			//direction from which the wind comes
//						}	wind;

	RankType		playerrank;
	MoraleType		squadronmorale;
	SWord			frontdeltastrength,
					reservesavail;
	SWord			currentplayerslot;
//DeadCode RDH 25Mar97 	SWord			correctplayerslot;
	char	PlayerName[PLAYERNAMELEN];
	char	aircraftname[20];
	UniqueID	InitialFront[3];
//	FileNum	mainbfield;
	FileNum			camp_win_anim;
	FileNum			camp_lost_anim;
endstruct(CampaignStatic);
//////////////////////////
substruct	(CampaignBlueSquad,CampaignStatic)
 	enum					{MAX_AC_NUM = 19};
struct	SquadronInfo
{
	PlaneTypeSelect	actype;										//RDH 07Apr96
	int				name;	//TextSnip0	 		name;
	SWord			airfieldindex;
	SWord			movetoairfieldindex;
	SWord			nextacnumber;
	SWord			ac_total_avail;
	SWord			rotatefreq;
	SLong			lastrotatedate;
	SWord			flt_used;		//not used!
	int				bingofuel;					//0.01kg
	AcTactics		elementtactics;
	AcTactics		flighttactics;

//	SWord			flt_pilots_avail;
//	SWord			lastflightform,lastgrpform;
//	SWord			flightnum [MAX_FLIGHT_NUM];
//	SWord			formationnum [MAX_FLIGHT_NUM];
//	SWord			squadronform;
//	NextLeadAct		nextleadact [MAX_FLIGHT_NUM];
};
	SquadronInfo	squad[PILOTABLE_SQUADRONS];

endstruct(CampaignBlueSquad);
//////////////////////////
substruct	(CampaignSquad,CampaignBlueSquad)

struct	MigSquadronInfo
{
	PlaneTypeSelect	actype;				//15 or 15bis 
	SWord			colourscheme;		//0..7			
	int				squadnameindex;		//name and desc index
	int				startdate;			//earliest date this squad can be used
	SWord			ac_total_avail;		//red squad size
	SWord			aclosses;			//total since squad launched
	SWord			aclosseslast;		//last 3d session
	SkillType		generalskill;		//ONE FIELD improve over time
	MoraleType		morale;				//squadron variable
	tAggressionLevel	agglevel;		//squad - improve slowly
	RedEvents		maxevent;			//improve very slowly - every 16 days?

};
	MigSquadronInfo	migsquad[MAXMIGSQUADRONS];	//first 2 are active squadrons
	int	nextsquadtocopy;						//copy to 1 of first 2

endstruct(CampaignSquad);
//////////////////////////
substruct	(CampaignPackages,CampaignSquad)
//	Package package[MAX_PACKAGE_NUM];
enum					{MAX_MISSIONPERCAMPAIGN = 8};
struct CampMissionDef
{
	SLong			msn_date;
	SLong			msn_time;
	UniqueID		target;
	UniqueID		captarget;
	FileNum			profile;
};
	int				winscore;
	Debrief::DisEntry		dis;
	CampMissionDef		missions[MAX_MISSIONPERCAMPAIGN];


endstruct(CampaignPackages);
//////////////////////////
substruct	(CampaignPilots,CampaignPackages)
	PilotType	Active_Pilots[PILOTS_PER_CAMPAIGN];
endstruct(CampaignPilots);
//////////////////////////
//DEADsubstruct	(CampaignFiles,CampaignPilotsOnly)
//DEAD//DeadCode RDH 18Feb97 
//DEAD//DeadCode RDH 18Feb97 	FileNum	introsheetart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	intropadart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	introiconart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	cr_iconart;
//DEAD//DeadCode RDH 18Feb97  	FileNum	lc_iconart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	historyart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	personnelart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	junctionart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	squadart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	saveart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	savedialogue;
//DEAD//DeadCode RDH 18Feb97 	FileNum	quitart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	padart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	mainiconart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	flightart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	newstextart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	newsgraphicart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	flightgraphicart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	acsmallart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	acmedart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	aclargeart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	paintshopart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	introtextart;
//DEAD
//DEAD	TextSnip0	objecttext;
//DEAD	TextSnip0	introtext;
//DEAD	TextSnip0	editnametext;
//DEAD	TextSnip0	editnametitle;
//DEAD
//DEADendstruct(CampaignFiles);
//////////////////////////
//DEADsubstruct	(CampaignPilots,CampaignFiles)
//DEAD	PilotType	Reserve_Pilots[PILOTS_IN_RESERVE];
//DEAD//DeadCode RDH 27Mar97 	PilotType	aces[ACESLIST];
//DEADendstruct(CampaignPilots);
//DEAD//////////////////////////
//DEADsubstruct	(CampaignTank,CampaignPilots)
//DEAD	SLong		Tank_timer;
//DEAD	SLong		Truck_timer;
//DEAD//DeadCode RDH 24Feb97 	UniqueID	routesstartuids[MAXROUTES];
//DEAD//DeadCode RDH 24Feb97 	UniqueID	routesenduids[MAXROUTES];
//DEADendstruct(CampaignTank);
//DEAD//////////////////////////
//DEADsubstruct	(CampaignTankZero,CampaignTank)
//DEAD	int			blueacflying;
//DEAD	UniqueID	blueguns[MAXGUNS];
//DEAD	UniqueID	blueaaa[MAXGUNS];
//DEAD	TnkMapWpSet	tankcampwp[MAXTNKWPINROUTE];							//RDH 08Oct96
//DEAD	struct Convoy {
//DEAD		UniqueID	uid;
//DEAD 		FileNum		bfield;
//DEAD		SWord		size;
//DEAD
//DEAD		};	Convoy convoys[MAXCONVOYS];
//DEAD
//DEADendstruct(CampaignTankZero);
//////////////////////////
#undef	basestruct
#undef	substruct
#undef	endstruct

#ifndef	MISS_MAN_Included2
#define	MISS_MAN_Included2

struct	CampaignZPilots:CampaignPilots
{
//DEAD	PilotType		Wounded_Pilots[CASUALTYLIST],
//DEAD					Dead_Pilots[CASUALTYLIST];
//DEAD	SquadronInfo	Temp_Squadron;
//DEAD	PilotType		Temp_Pilots[PILOTS_PER_CAMPAIGN];
  PilotHist		dead_pilots[CASUALTYLIST];
};

struct	CampaignZero:CampaignZPilots
{
//DeadCode RDH 02Oct96 	enum					{MAXWEATHERNUM = 4};
//Dead	WpSetType		players_wpset;
//Dead	SLong			TrainingCount;
//Dead	SLong			TrainingRange;
//DeadCode RDH 02Oct96 	SWord 			currweathernum;
//DeadCode RDH 02Oct96 	SWord 			currwindnum;
//Dead	SWord			currmission_no;
//Dead	SWord			missionwpset;
	SWord			missionarea;
	MeritType		playermerit;
	SWord			killsonbestday;
	SWord			currmissionfamily;
	SWord			dayssincetransfer;
	SWord			nextdeadpilot;
	SWord			playersquadron,playeracnum;
	int				curr_score;				//used in mission scoring //RDH 19/03/99
	int				curr_msn;				//used in mission scoring //RDH 19/03/99
	bool			wincamp;	
	FileNum			smacker;				//a smacker generated by last mission
	int				msgwithsmacker;				//a smacker generated by last mission //RDH 26/06/99
//Dead	SWord			lastrecoveredpilot;
//Dead	TextSnip0		lasttransferee;
//Dead	TextSnip0		lastdeadsuperior;
//Dead	TextSnip0		specialeventtext;							//RDH 06Sep96
//Dead	FileNum		playerbfield;
//Dead	TextPerm	playernameref;
	SpecialEventBitField	specialeventbits;
	NewsEventField			newsevent;
	Bool		indebrief;
	Debrief		debrief;
	ATMOSPHERE		Sky;
	SG_DirControl	directives;
 	char	CommsPassword[11];
	SWord	packageprevscores[10];

	void	SetCurrMission (MissionType*);
	bool	ChkEndCampaign();
	int		StoresDestroyedForNodeRoute(SupplyNode* node);
	void	BattleLossesForNode(SupplyNode* node, int& redlosses, int& bluelosses);


	void	NextMission();
	void	NextDay();
	void	ReplenishAcStock(); //RDH 15/02/99
	void	RotateMiGSquadron(int squad);							  //RDH 09/03/99
	void	ChkRotateMiGSquadrons();								  //RDH 09/03/99
	void	ModifyMiGAggressionLevel(int squad);					  //RDH 09/03/99 //RDH 09/03/99
	void	SwapPilot(int groupnum, int src,int dest);	
	void	SwapElement(int groupnum, int src, int dest);
	void	SwapFlight(int groupnum, int src, int dest);
	void	RotateFlightsCheck();
	void	ModifySkill(int groupnum, int daysonduty);

	void	EndDebrief();
	void	CampaignInit();
	void	AddDebriefData(Debrief::SquadKills& src, Debrief::SquadKills& dest);
	void	ZeroDebriefData(Debrief::SquadKills& dest);
	void	DisDayEntry(Debrief::TypeFlag type, int msgowner, int msgtextid);
	void	UpdateAllDis();
	void	UpdatePlayerLog();										  //RDH 19/06/99
	void	ZeroDisDay();
	FileNum	FindSmacker(int index);
	void	MakeNewPilot(int pilot);
	void	KillPilot(int pilot, pilotstatus status);
	void	MoveDeadPilots();
	void	SetOldPackScore(int packnum);
	bool	GetMissionSuccess(int packnum);


	bool	inentirewar;

	CampaignZero& operator = (CampaignBase	*);
	CampaignZero& operator = (CampaignZero&	);

	static	 MigEvent	migevents[MIGEV_MAX];
	static	PilotType	Active_Pilots_Init[PILOTS_PER_CAMPAIGN];

};
typedef	CampaignZero	Campaign;


//------------------------------------------------------------------------------
//DeadCode RDH 13Jun96 #include	"uid.g"												//RDH 21Dec95
class	 MissMan
{
public:
	static enum	CampaignName {
		INTROCAMPAIGN = 0,
		F80_CAMPAIGN = 0,
		F51_CAMPAIGN,
		F84_CAMPAIGN,
		F86_CAMPAIGN,
		SO51_CAMPAIGN,
//DEADCODE RDH 19/03/99 		PEACETALKCAMPAIGN,
//DEADCODE RDH 19/03/99 		RUNDEMOCAMPAIGN,
 		SCRAMBLECAMPAIGN,
//DEADCODE RDH 19/03/99 		H2HCAMPAIGN,											//RDH 05Sep96
		MINCAMPAIGNNUM = 0,
 		MAXCAMPAIGNNUM = 6,										//RDH 05Sep96
//DEADCODE RDH 19/03/99 		MAXACTUALCAMPAIGNNUM = 3
		} 	currcampaignnum;

	static CampaignBase	*campaigntable[MAXCAMPAIGNNUM];
	Campaign	camp;
	Campaign	backup;


};
extern	MissMan Miss_Man;
#define	MMC	Miss_Man.camp
#endif

#endif





