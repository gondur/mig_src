//------------------------------------------------------------------------------
//Filename       node.h
//System         
//Author         R. Hyde 
//Date           Wed 19 Feb 1997
//Description    
//
// IF YOU ADD ANY FIELDS TO THESE DATA STRUCTURES, YOU NEED TO CHECK THE << and >>
// IN SAVEGAME.CPP FOR THE STRUCTURE
// MOST FIELDS ARE MARKED "C" for Constant or "S" for Saved
// UNMARKED FIELDS ARE EITHER IN STRUCTURES THAT AREN'T SAVED, OR ARE LOOPHOLES!!!
//------------------------------------------------------------------------------
#ifndef	NODE_Included
#define	NODE_Included

#define	DEFAULT_NODE 0
#include	"UniqueID.h"
#include	"movement.h"
#include	"flyinit.h"

class CString;
#include "batnode.h"
#include "package.h"
//TempCode JIM 17Mar99 #include "debrief.h"

enum	SupplyPriority	{SP_NONE = 0,SP_HIGH = 1000,SP_ALIGN = 65535};

enum	{NUM_OF_SUPPLYROUTES = 3};

enum	LandStores
	{//1 unit = 10 tonnes
		STORES_NIL							= 0,
		//MAXMOBILESONDOUBLETRACK				= 10,
		//MAXMOBILESONSINGLETRACK				= 5,
		//MAXMOBILESONSINGLEROAD				= 20,
		MIN_TRAINSPERDAY					= 8,	//single track
		STD_TRAINSPERDAY					= 16,	//single track
		MAJ_TRAINSPERDAY					= 32,	//double track
		MIN_TRUCKSPERDAY					= 10,	//minor tracks
		STD_TRUCKSPERDAY					= 20,	//single roads
		MAJ_TRUCKSPERDAY					= 30,	//major dual highways
		STORES_TOSUPPORTASSAULT				= 200,
		STORES_TOSUPPORTDEFENSE				= 70,
		STORES_STANDARDSUPPLY				= 10,
		STORES_TOPREPAREASSAULT				= 350,
		STORES_TOINITIATEASSAULT			= 400,
		STORES_TORETRENCH					= 200,
		STORES_TODISCOURAGEBLUEATTACK		= 150,
		STORES_BLUEPREPAREATTACK			= 240,
		STORES_BLUEATTACKSTRENGTH			= 750,	//140,
		STORES_INITALVERYBIGSETTLEMENT		= 2000,
		STORES_INITALBIGSETTLEMENT			= 1500,				//MS 20Jan99
		STORES_INITALMEDIUMSETTLEMENT		= 1000,
		STORES_INITALSMALLSETTLEMENT		= 500,
		STORES_INITALVERYSMALLSETTLEMENT	= 150,
		STORES_TRUCK						= 4,
		STORES_TRAIN						= 10,//16,	//per carriage!
		STORES_MAXSUPPLY					= 2000,
		STORES_NO_TO_DESTROY_TO_REST_ROUTE	= 500					  //RDH 06/06/99
	};


enum	Initiative	{	REDINITIATIVE,BLUEINITIATIVE,
						REDATTACKING,BLUEATTACKING,
						REDWON,BLUEWON,
						REDLOST,BLUELOST
					};

//--------------------------------------------
//Ongoing ground battle structures
//
//
//

//------------------------------------------------------------------------------
//SupplyLines structure
//There are 5 supply lines.
//
//Each "SupplyLine" will consist of about 20-30 "nodes" each connected by a
//number of "Supply Routes".
//
//Each supply line has a set of properties:
struct	SupplyNode;
struct	SupplyRoute;
enum	SupplyLineNum	{SLN_EAST,SLN_CENTRAL,SLN_WEST};

struct	SupplyLine
{									//SEE SAVEGAME.CPP
	UniqueID	AssociatedDepot[2];	//C			//Marshalling yard, truck park
	SupplyNode*	firstnode;			//C			//the first node for this line
//rdh 6/1/99	SupplyNode*	splitAB;			//C
//rdh 6/1/99	SupplyNode*	splitBC;			//C
	SWord		MaxMobiles;			//S
	SWord		TodaysMobiles;		//S
	SWord		CurrMobiles;		//S
	SupplyNode*	frontline;			//S!			//the front line position for this line
	SWord		attackpotential;	//S				// 0 = retreat, 1 = defend,
	CallNames	TACcallname;
	CallNames	FACcallname;
	bool		FACActive;
												//else the higher the number the 
												// the greater the attack potential
	Initiative	initiative;			//S			//who has initiative on this line
	BattleStruct	groundbattle;	//s
	void	InitiateBf();
	void	NextAttackReports();
	void	PostAttackReports();
	void	ExitBf();
	void	DiagnosticOutput(int type,char* intro);
};
//------------------------------------------------------------------------------
//Node Structure

enum	NodeType{NOCONTEST, BATTLEFIELD,LASTONE					//either a battlefield or not
			};

enum	Status{	BEHINDREDLINES,
				FRONTLINE,
				BEHINDBLUELINES 
			};
enum	AirFieldType	{AFT_PROPONLY,AFT_LIGHTBOMBER,AFT_JET, AFT_LOADEDJET};

struct	Attacks		//Saved
{	//Frequencies are in units of 0.1
//rdh6/1/99	char	freq7;			//frequency of attacks reduced by 1/7 per day = week ave
//rdh6/1/99	char	freq31;			//frequency of attacks reduced by 1/31 per day = month ave



	UWord	actypelasthit:4,	//type of AC used for that attack
			LBaaalevel:6,	 
			LBaaaavail:6;

	UWord	damagedtokens:6,
			tokensinmw:5,
			tokensinbf:5;

	UByte	aaalevel;		//proportional factor

	UByte	daylasthit;		//day number from start of last attack

	UWord	damagelevel;	//100 is dead, but could get higher than 256!

	UWord	totalinbf;				//NEED TO SAVE!
	UWord	damageinbf;

	UWord	totalinmw;
	UWord	damageinmw;
};

struct	SupplyFightFiles
{	
	int			frontnum;
	FileNum		bf;
	FileNum		nodetree;
	int			startdis;
	int			advancedis;
	int			altitude;
/////			Debrief::DisEntry	startdis;	//leg bone connected to the ancle bone!!!
};

struct	SupplyNode
{

		SupplyNode*		next;		//C-followed
		SupplyLine*		supplyline;	//C//every node belongs to one of 5 supplylines
		NodeType		type;		//C
		Status			status;		//S
		UniqueID	airfield[3];	//C//Up to 3 red airfield that could defend node
		UniqueID	associated_item;//C//"health" of this item determines chance
		UniqueID	associated_town;
		int			associated_itemtext;
										//of supply down the line
										//Could be a supply dump marshalling
										//yard etc
//		char		associtemprofile;	//mission profile against this item
		SWord			currentstores;	//S//just a number. See above equates
		SWord			maxstorestonnes;//S//just a number. Max stores that can be held
		SupplyRoute* 	route[3];		//C//each node can be supplied by a max of 3 nodes
											//record here the routes that connect to
											//these nodes
											//when deciding on retreat start at [0] and 
											//find node on red side, other wise surrender
		struct	FightFiles
		{	
			FileNum		bfdummy;	//this field is garbage. Just to stop VC problems
			SupplyFightFiles* fightfiles;
//DEADCODE JIM 13/05/99 			FileNum		nodetree;
//DEADCODE JIM 13/05/99 			int			startdis;
			SupplyFightFiles* operator->();
/////			Debrief::DisEntry	startdis;	//leg bone connected to the ancle bone!!!
		};

		FightFiles		redfrontBF;		//C //battlefield that determines the placement
		FightFiles		bluefrontBF;	//battlefield that determines the placement
//DeadCode DAW 28Oct98 		FileNum		redfrontBF;		//C //battlefield that determines the placement
//DeadCode DAW 28Oct98 										//of items if reds are attacking from this 
//DeadCode DAW 28Oct98 										//node:
//DeadCode DAW 28Oct98 										//		tanks attacking line
//DeadCode DAW 28Oct98 										//		artillery
//DeadCode DAW 28Oct98 										//		roadblock
//DeadCode DAW 28Oct98 										//		supply dumps
//DeadCode DAW 28Oct98 										//		field HQ
//DeadCode DAW 28Oct98 										//
//DeadCode DAW 28Oct98 		FileNum		bluefrontBF;	//battlefield that determines the placement
									//of items if blues are attacking from this
									//node
		SupplyRoute*	forward;	//C		//route down which the advance should progress
		SupplyPriority	priority;	//S
		bool			serviced;	//cleared in load/save
		FileNum			populateBF;	//C	//Battlefield to make town look good when overflown
//rdh29/1/99		char			damagelevel;//S
//rdh6/1/99		char			aaalevel;	//S
		char			repairrate;	//S

		SWord			maxstorestokens;//S	//number of stores tokens in supergroup
											//filled in first time drawn
		Attacks			attackstats,attackstown;	//s
};
//External and global modifiers:
//
//
//OppositionModifier		The reds can be up against different forces, eg
//								SK forces and Marines
//						This modifer effects the CurrentStores so that, for instance,
//						a bigger number is required before attacking Marines.
//
//						When deciding which way to proceed with the attack, the reds will
//						choose the line of least resistance
//
//						OppositionModifier will be used to display blue forces on map
//
//
//TerrainModifer		The high ground will be more difficult take
//PennisulaModifer		The further south that the reds go the harder it will be. Blues
//						are closer to their supply lines etc.
//
//------------------------------------------------------------------------------
//We don't want to have any bi-directional routes
//
//
//

enum	SR_Status	{SR_RESTING,SR_ACTIVE,SR_LASTONE};				
struct	SupplyRoute
{
		SupplyRoute*	next;				//C-followed
		SupplyRoute*	alternateroute;		//C
		SupplyNode*		supplier;			//C
		SupplyNode*		suppliee;			//C
		SR_Status		status;				//S
		SLong			recommision_time;	//S
		UniqueID		redsupplyUID;		//C//battle field to load if this internode
												//is to be active in 3d for red supply
		SWord			storespermobile;	//C	//eg STORES_TRUCK orSTORES_TRAIN
		SWord			maxcapacitywinterX;	//C		
		SWord			maxcapacitysummer;	//C		
		UniqueID		associated_brdg;	//C		//could be tunnel or cutings
		int				associated_brdgtext;
		FileNum			populateBF;
//		char			associtemprofile;			//profile against this associated item
		SWord			storeslaunched;		//S	
		SWord			stores_destroyed;	//S
		SWord			stores_destroyed_today;	//S

		SWord			totalstores_destroyed;//S	//This is used to determine whether
										//or not to rest route
//rdh6/1/99		SWord			consecutive_days_attacked;//S 	//This determine the AAA activity.
		Attacks			attackstats;			//s

		bool	SetSupplySizeGR(ULong& GR_FormSize00,ULong& GR_FormSize01,ULong& GR_FormSize02);
		int		SetSupplySizeGR();
};

//struct	DirectivesProfile
//{
//	char	acused[7];
//	int		filenum;
//};
struct	DirectivesProfile
{	//constant - not saved
	char	acused[7];
	int		filenum;
};

struct	AirFieldInfo
{	
	Nationality		nationality;		//S
	UniqueID		airfield;			//C
	int				airfieldtext;
//	char			profile;			//missile profiel against this airfield
	SupplyNode*			northnodes[2];	//C	//used to decide when airfield changes hands
	SupplyNode*			southnodes[2];	//C	//
	AirFieldType	type;				//C
	SWord			capacity;			//S
	FileNum			BluePopulateBF;
	FileNum			RedPopulateBF;
	FileNum			EmptyPopulateBF;
	FileNum			HandBlueBF;
	SByte			hangarfactor,		//C
					rivetfactor,		//C
					supplyfactor,		//C
					otherfactor;		//C
	SWord			days;				//S//since status change
	int				activeac;			//S
	Attacks			attackstats;		//s
};


class	BIStream;class	BOStream;
class	UniqueIDField;

class	SupplyTree
{
	friend struct	SupplyNode::FightFiles;
static SupplyFightFiles	 DummyBlank, 
		F_W1_RED,F_W1_UN,F_C1_RED,F_C1_UN,
		F_W2_RED,F_W2_UN,F_C2_RED,F_C2_UN,
		F_W3_RED,F_W3_UN,F_C3_RED,F_C3_UN,
		F_W4_RED,F_W4_UN,F_C4_RED,F_C4_UN,
		F_W5_RED,F_W5_UN,F_C5_RED,F_C5_UN,
		F_W6_RED,F_W6_UN,F_C6_RED,F_C6_UN,
		F_W7_RED,F_W7_UN,F_C7_RED,F_C7_UN;


static SupplyNode	N0_0_Dangdong,
					N0_1_Sinuiju,
					N0_2_Yomju,
					N0_3_Sonchon,
					N0_4_Chongju,
					N0_57_Suiho,
					N0_46_Chongsongup,
					N0_48_Kusong,
					N0_44_Namsanni,
					N0_45_Sakchu,
					N0_60_Chosan,
					N0_59_Chosin,
					N0_51_Pungsan,
					N0_33_Kapsan,
					N0_32_Hyesan,
					N0_5_Sinaju,
					N0_16_Chongjin,
					N0_56_Kyongsong,
					N0_17_Kilchu,
					N0_18_Kimchaek,
					N0_50_Tanchon,
					N0_37_Pukchong,
					N0_19_Hamhung,
					N0_8_Manpo,
					N0_9_Kangye,
					N0_58_SinmiDo,
					N0_10_Huichon,
					N0_11_Kujang,
					N0_31_Tokchon,
					N0_4b_Maenjungdong,
					N1_6_Sukchon,
					N1_29_Kangdong,
					N1_54_YulLi,
					N1_7_Pyongyang,
					N1_30_Nampo,
					N1_49_Hwangju,
					N1_41_Ichon,
					N1_22_Sariwon,
					N1_25_Pyongsan,
					N1_26_Kumchon,
					N1_62_Chaeryong,
					N1_24_Haeju,
					N1_61_Yonan,
					N1_69_Kalmal,
					N1_27_Kaesong,
					N1_75_Panmunjom,
					N1_34_Yonghung,
					N1_12_Sunchon,
					N1_20_Kowon,
					N1_21_Wonsan,
					N1_52_Kojo,
					N1_35_Kojin ,
					N1_64_Sangwon ,
					N1_65_Nuang ,
					N1_63_Suan ,
					N1_66_Singye ,
					N1_42_Kansang,
					N1_70_Hwachon,
//					N1_50_Yongpyong,
					N1_68_Changdo,
					N1_53_Koksan,
					N1_40_Hoeyang,
					N1_38_Kumhwa,
					N1_36_Yangyang,
					N1_13_Samdung,
//					N1_23_Changyon,
					N1_14_WaDong ,
					N1_15_Yangdok ,
					N1_39_Kosan ,
					N1_67_Sepo ,
					N1_71_Inje ,
					N1_28_Pyonggang ,
					N1_43_Chorwon ,
					N1_55_Kanda ,
					N1_56_Yonchon ,
					N2_40_Munsan,
					N2_10_Seoul,
					N2_7_Suwon,
					N2_14_Osan,
					N2_29_Kangnung,
					N2_28_Samchok,
					N2_49_Pochon,
					N2_12_Chuncheon,
					N2_48_Kuri,
					N2_35_Hongchon,
					N2_23_Hoensong,
					N2_34_Yulchon,
					N2_43_Pyongchang,
					N2_57_Sangnam,
					N2_42_Chongson,
					N2_9_Inchon,
//					N2_39_Kimpo,
					N2_8_Songnam,
					N2_41_Ichon,
					N2_11_Uijongbu,
					N2_58_Yangpyong,
					N2_6_Wonju,
					N3_19_Pyongtaek,
					N3_3_Chonan,
					N3_36_Mokkye,
					N3_44_Taepaek,
					N3_62_Noktong,
					N3_20_Yechon,
					N3_24_Chomchon,
					N3_21_Sangju,
					N3_2_Chongju,
					N3_8_Songnam,
//DeadCode MS 02May99 					N3_64_Hongsong,
//DeadCode MS 02May99 					N3_65_Hannae,
					N3_51_Maesan,
					N3_52_Kwangheywan,
					N3_53_Chinchon,
					N3_54_Chungpyong,
					N3_60_Mungyong,
					N3_61_Tanyang,
					N3_55_Uisong,
					N3_XX_Taegu,									  //MS 22/04/99
//DeadCode MS 02May99 					N3_66_Taechon,
//DeadCode MS 02May99 					N3_45_Nonsan,
					N3_63_Kunsan,
//DeadCode MS 02May99 					N3_15_Kongju,
					N3_4_Chungju,
					N3_59_Koesan,
					N3_26_Changhowon,
					N3_17_Chochiwon,
					N3_1_Taejon,
					N3_46_Yongdong,
					N3_22_Kimchon,
					N3_37_Kumi,
					N3_30_Ulhin,
					N3_31_Yonghae,
					N3_32_Yongdok,
					N3_25_Pohang,
					N3_5_Chechon,
					N3_47_Punggi,
					N3_16_Yongju,
					N3_18_Andong,
					China_C,
					China_E,
					Last_Node;


static SupplyRoute	
					WestMainSupply,																					
					R0_1_2Rail0,		//ST
					R0_1_2Rail1,		//DT
					R0_0_1Rail0,		//DT
					R0_0_1Rail1,		//DT
					R0_0_1Road,			//MAJ
					R0_1_2Road,			//MAJ
					R0_2_3Rail,			//DT
					R0_2_3Road,			//MAJ
					R0_3_4Road,			//MAJ
					R0_3_4Rail,			//DT
//					R0_4_5Rail,			//DT
					R0_4_5Road,			//MAJ
					R0_5_6Road,			//MAJ
					R0_5_6Rail,			//DT
	   				R0_16_56Road,		//MAJ
					R0_16_56Rail,		//ST
					R0_56_17Rail,		//ST
					R0_56_17Road,		//MAJ
					R0_17_18Rail,		//ST
					R0_17_18Road,		//MAJ
					R0_18_50Rail,		//ST
					R0_18_50Road,		//MAJ
					R0_50_37Rail,		//ST
					R0_50_37Road0,		//MAJ
					R0_50_37Road1,		//SEC
//					R0_4_5Rail,			//DT
//					R0_4_5Road,			//MAJ
//					R0_5_6Road,			//MAJ
//					R0_5_6Rail,			//DT
					R0_37_19Rail,		//ST
					R0_37_19Road,		//MAJ
					R0_19_34Rail,		//ST
					R0_19_34Road,		//MAJ
					R0_8_9Rail,			//ST
					R0_8_9Road,			//MAJ
					R0_9_10Rail,		//ST
					R0_9_10Road,		//MAJ
					R0_10_11Rail,		//ST
					R0_10_11Road,		//MAJ
					R0_11_31Rail,		//ST
					R0_31_13Rail,		//ST
					R0_44_45Rail,		//ST
					R0_45_48Rail,		//ST
					R0_60_11Road,		//MAJ
					R0_11_5Rail,		//ST
					R0_11_5Road,		//MAJ
					R0_48_4Rail,		//ST
					R0_57_46Road,		//MAJ
					R0_4_48Road,		//MAJ
					R0_32_17Rail,		//ST
					R0_32_33Road,		//MAJ
					R0_33_51Road,		//MAJ
					R0_51_37Road,		//MAJ
					R0_9_51Road,		//SEC
//					R0_9_19Road,		//SEC
					R0_11_19Road,		//SEC
					R0_51_50Rail,		//ST
					R0_9_59Road,		//MIN
					R0_3_58Road,		//SEC
					R0_59_19Road,		//MIN
					R0_11_12Rail,		//ST
					R0_46_48Road,		//MAJ
					R0_48_4Road,		//ST
//					R0_4_4bRail,
//					R0_4_4bRoad,
//					R0_4b_5Rail0,
//					R0_4b_5Rail1,
//					R0_4b_5Rail2,
//					R0_4b_5Rail3,
//					R0_4b_5Rail4,
//					R0_4b_5Road,
					R1_71_12Road0,		//MAJ
					R1_71_12Road1,		//SEC
					R1_25_41Road,		//MAJ
					R1_39_40Road,		//MAJ
					R1_40_68Road,		//MAJ
					R1_25_63Road,		//MIN
					R1_71_36Road,		//MAJ
					R1_38_70Road,		//SEC
//					R1_38_70Rail,
//					R1_38_50Road,		//SEC
//					R1_50_12Road,		//SEC
					R1_70_12Road,		//SEC
//					R1_70_12Rail,
					R1_68_38Road,		//MAJ
					R1_62_23Rail,		//
					R1_38_69Road,
					R1_69_49Road,
					R1_41_28Road,
					R1_28_38Rail,
					R1_28_38Road,
					R1_6_7Rail,
					R1_6_7Road,
					R1_15_53Road,
					R1_7_64Road,
					R1_64_54Road,
					R1_22_65Road,
					R1_65_54Road,
					R1_63_54Road,
					R1_25_66Road,
					R1_66_53Road,
					R1_53_55Road,
					R1_15_55Road,
					R1_55_21Road,
					R1_7_30Rail,
					R1_62_23Road,
					R1_42_68Road,
//					R1_13_29Rail,
//					R1_13_29Road,
					R1_7_30Road,
//					R1_30_7Rail,
					R1_30_7Road,
					R1_12_7Road,
//					R1_12_13Rail,
					R1_7_49Rail,
					R1_7_49Road0,
					R1_7_49Road1,
					R1_49_22Road,
					R1_49_22Rail,
					R1_22_25Rail,
					R1_22_25Road,
					R1_25_26Rail,
					R1_25_26Road,
					R1_26_27Road,
					R1_26_27Rail,
					R1_27_75Road,
					R1_27_75Rail,
					R1_29_54Rail,
					R1_75_40Rail,
					R1_75_40Road,
					R1_34_20Rail,
					R1_34_20Road,
					R1_15_20Rail,
					R1_20_21Rail,
					R1_20_21Road,
					R1_21_52Rail,
					R1_21_39Rail,
					R1_21_39Road,
					R1_39_67Rail,
					R1_52_35Road,
					R1_12_7Rail,
//					R1_12_13Rail,
//					R1_30_7Rail,
//					R1_30_7Road,
					R1_52_35Rail,
					R1_35_42Road,
					R1_35_42Rail,
					R1_42_36Rail,
				 	R1_36_29Road,
					R1_13_14Road,
//					R1_13_14Rail,					
					R1_14_15Rail,
					R1_14_15Road,
					R1_67_28Rail,
					R1_28_43Rail,
					R1_22_62Rail,
					R1_62_24Rail,
					R1_24_61Rail,
					R1_61_27Rail,
					R1_71_57Road,
					R1_42_71Road,
					R1_43_56Rail,
					R1_56_11Rail,
					R2_49_11Road,
					R2_40_10Rail,
					R2_40_10Road0,
					R2_40_10Road1,
					R2_40_10Road2,
					R2_7_8Road,
					R2_10_7Rail,
					R2_10_7Road0,
					R2_10_7Road1,
					R2_10_7Road2,
					R2_10_7Road3,
					R2_10_7Road4, 
					R2_10_7Road5,
					R2_12_35Road,
					R2_18_20Road,
					R2_10_8Road,
					R2_35_23Road,
//					R2_35_23Rail,
					R2_23_6Road,
					R2_23_6Rail,
					R2_23_34Road,
					R2_57_34Road,
//					R2_12_35Road,
//					R2_12_35Rail,
					R2_43_42Road,
					R2_42_28Road,
					R2_28_44Road,
					R2_43_5Road,
					R2_6_36Road,
					R2_6_26Road,
					R2_8_41Road,
					R2_9_7Road,
					R2_41_26Road,
					R2_41_14Road,
					R2_10_9Road,
					R2_11_48Road,
					R2_14_41Road,
					R2_41_51Road,
					R2_7_14Road,			
					R2_7_14Rail,
					R2_14_19Rail,
					R2_14_19Road,
					R2_29_28Road,
					R2_28_30Road,
					R2_11_10Rail,
					R2_11_10Road,
					R2_10_58Rail,
//					R2_40_11Road,
					R2_58_6Rail,
					R2_6_5Rail,
					R2_34_29Road,
					R2_6_43Road,
					R2_48_10Road,
					R2_34_43Road,
					R2_12_48Road0,
					R2_12_48Road1,
					R2_12_48Rail,
					R3_24_21Road,
					R3_62_16Road,
					R3_55_37Road,
					R3_59_2Rail,
					R3_41_51Road,
					R3_51_52Road,
					R3_4_61Road,
					R3_18_55Road,
					R3_19_3Rail,
					R3_19_57Road,
					R3_57_26Road,
					R3_57_52Road,
					R3_52_53Road,
					R3_53_54Road,
					R3_54_2Road,
					R3_26_4Road,
					R3_4_60Road,
					R3_60_24Road,
					R3_24_21Rail,
//					R3_24_21Road,
					R3_21_22Road,
					R3_21_22Rail,
					R3_2_24Rail,
					R3_2_1Rail,
					R3_2_17Rail,
//DeadCode MS 02May99 					R3_3_64Rail,
					R3_64_65Rail,
//DeadCode MS 02May99 					R3_65_66Rail,
//DeadCode MS 02May99 					R3_66_63Rail,
//DeadCode MS 02May99 					R3_63_45Rail,
//DeadCode MS 02May99 					R3_45_1Rail,
					R3_3_15Road,
					R3_15_45Road,
					R3_15_1Road,
					R3_17_2Rail,
					R3_4_59Rail,
					R3_2_59Rail,
					R3_59_4Rail,
//					R3_2_24Rail,
					R3_36_4Road,
//					R3_4_60Road,
					R3_62_30Road,
					R3_19_3Road,
					R3_44_62Road,
					R3_3_17Rail,
					R3_3_17Road,
					R3_17_1Rail,
					R3_17_1Road,	
					R3_1_46Rail,
					R3_1_46Road,
					R3_46_22Rail,	
					R3_46_22Road,
					R3_22_37Road,
					R3_30_31Road,
					R3_20_24Road,
					R3_31_32Road,													
					R3_32_25Road,
					R3_5_47Rail,						
//					R3_4_59Rail,
//					R3_59_2Rail,
//					R3_5_47Rail,
					R3_47_16Rail,
					R3_47_16Road,
					R3_16_18Rail,
					R3_16_18Road,
					R3_61_16Road,
					R3_18_20Road,
					R3_18_25Rail,
					R1_63_66Road,
					R1_66_41Road,
					R1_38_12Road,
					R0_4_4bRail,
					R0_4_4bRoad,
					R0_4b_5Rail0,
					R0_4b_5Rail1,
					R0_4b_5Rail2,
					R0_4b_5Rail3,
					R0_4b_5Rail4,
					R0_4b_5Road,
					R1_30_62Road,
					R2_8_7Road,
//					R1_40_39Road,									  //MS 02/05/99
//					R1_39_10Road,
					R2_26_4Road,
					R0_0_57Rail,
					R0_0_44Rail,
					R0_8_60Rail,
					R0_16_32Rail,
					R1_12_29Rail,
					R1_12_29Road,
					R1_29_13Rail,
					R1_29_13Road,
					R1_29_14Rail,
					R1_29_14Road,
					R1_13_54Rail,
					R0_31_29Rail,
					R1_54_65Road,
					R1_65_22Road,
					R2_48_10Rail,
					R1_38_43Rail,
					R2_29_34Road,
					R2_62_30Road,
					R3_62_16Rail,
					R2_34_23Road,
					R2_5_36Road,
					R0_C_16Rail,
					R0_C_8Rail,
					R_Fake00,										  //MS 14/05/99
					R_Fake01,										  //MS 14/05/99
					R_Fake02,										  //MS 14/05/99//MS 02Jun99
					R_Fake03,										  //MS 14/05/99//MS 08Jun99
					R_Fake04,										  //MS 14/05/99//MS 08Jun99
					R_Fake05,										  //MS 14/05/99//MS 09Jun99
					R_Fake06,										  //MS 14/05/99//MS 09Jun99
					R_Fake07,										  //MS 14/05/99//MS 09Jun99
					LastRoute;


public:
static AirFieldInfo	airfieldinfo[];			//S
	enum	Supply2UID	{S2U_NOTHERE=0,S2U_MAIN,S2U_AF0,S2U_AF1,S2U_AF2,S2U_ROUTE0,S2U_ROUTE1,S2U_ROUTE2};
static SupplyNode*	FindSupplyNodeForItem(UniqueID,Supply2UID* rel=NULL);
static	SupplyRoute*	SupplyTree::FindBridge(UniqueID u,SupplyRoute* route);
static SupplyNode*	FindSupplyNodeForNodeItem(UniqueID,Supply2UID* rel=NULL);
static	void FillNatForUID(UniqueIDField& f);
static	AirFieldInfo*	FindAirfieldForItem(UniqueID);
static	Nationality	GetNatForUID(UniqueID u,UniqueIDField& f);
static	Supply2UID	NodeHoldsUID(UniqueID u,SupplyNode* s);
static	FileNum SupplyTree::TargetToBf(UniqueID targ,UByte* getconvoysandreturnaaalevel=NULL);
static	void	SupplyTree::CheckTargetLoaded(UniqueID targ);
static	void	ClearAllStatuses();
static	void	SetStatus(UniqueID u,Attacks& a);
static	SupplyLine*	GetLineFromCallName(int callname);
static	void	LoadCleanNodeTree();
static	void	FillFLS_Icons(FileNum* FL_Icon);
static  void	FillFL_Icons(SupplyLine* SL, FileNum* FL_Icon);
static	void	ResetForNewCampaign();
static	Attacks*	GetAttacks(UniqueID uid);
static	Attacks*	GetAttacks(UniqueID uid,SupplyNode* node,SupplyTree::Supply2UID rel);
static	bool	AllFrontOnBattleNodes(int frontnum=0);//0 means don't check!

static	void	Save(BOStream& bos);
static	void	Load(BIStream& bis);

static SupplyLine	WestRoute,				//S
					CentralRoute,			//S
					EastRoute;				//S
static	SupplyLine*	supplylines	[4];
static SupplyNode *const	FirstNode;		//S
static	SupplyRoute*const	FirstRoute;		//S
static	SupplyNode*	CurrDisNode;							  //RDH 09/03/99

enum	{AIRFIELDSINWORLD = 31};
enum	{STANDARDREDAFCOMPLEMENT = 16};

//enum	{	P_ALPHASTRIKE = 0,
//			P_MEDSTRIKE,
//			P_FBSTRIKE,
//			P_B29CARPETBOMB,		
//			P_B29PRECISIONBOMB,	
//			P_B26RAID,			
//			P_DEEPFBSTRIKE,		
//			P_NORMALFBSTRIKE,		
//			P_LOWRISKFBSTRIKE,		
//			P_HITANDRUN,		
//			P_MIXEDRAID,		
//			P_ARMEDRECONN,		
//			P_SABRESCREEN,		
//			P_RAPIDRESPONSE,		
//			MAXPROFILELIBS = 14
//			};
///static DirectivesProfile	profilelib[MAXPROFILELIBS];
//static WeaponSets Predefined_WeapSet [CONFIGSTORESAC][STORESPERACMAX];
//static ListControl listcontrol [LISTCONTROLMAX];
//	enum	{MAXMISSIONS = 20, MAXDIRECTIVES = 8, MAXACPERSQUAD = 16};
	enum	{M_NOACALLOC = 0, M_NOTOPCOVER, M_NOFIGHTERS, 
				M_NOMEDIUMBOMBERS, M_ALPHANOTPOSSIBLE, M_INSUFFAC, 
				M_ALPHASDISABLED, M_TARGETALREADYALLOC };	
								

	enum	{	D_AIRSUPERIORITY=0, D_CHOKE, D_SUPPLY, D_AIRFIELDS, D_RAIL,
		D_ROAD, D_ARMY, D_RESTING};
	enum	{	I_SUPPLY = 0, I_CHOKE, I_TRAFFIC, I_AIRFIELDS, I_ARMY}; 


enum {MAX_DISSMACKERS = 50};
struct	DisSmacker
{
	int		idtext;
	FileNum	file;
};
static	DisSmacker	dissmackers[MAX_DISSMACKERS];



static	void	SetNodeNationalities(UniqueID eastfront,UniqueID centralfront,UniqueID westfront,int deltastrength);


static	SWord FindModifiedSupplies(SupplyNode* node);
static	SWord BlueAcAtAirfield(UniqueID af);
static	SWord RedAcAtAirfield(UniqueID af);
static	void	GenerateSupplyDIS();
static	void	FrontLineSupplyDIS(SupplyLine* SL);
static	void ProcessAirFields();
static	void PopulateRedAfs();
static	UniqueID FindRedAfToPopulate(int acnum);
static	void	MoveAnyBlueAc(int curraf);
static	int		FindFreeSlots(int afnum);
static	void	MoveSquadron(int squad);

static	void RetreatOneNode(SupplyLine* SL);
static	void RetreatOneNode();
static	void InitiateBf();
static	void UpdateBf();
static	void WithDrawSupplies(SupplyNode* node);
static	SWord StoreLaunchPossible(SupplyRoute* currroute);
static	void SupplyThisNode(SupplyNode* node,SWord priority,SWord requirement);
static	void AdvanceOneNode(SupplyLine* SL);
static	void AdvanceOneNode();
static	SWord StoresUsage  (SupplyLine* SL,SupplyNode* node);
static	void ProcessFrontLineRequest (SupplyLine* SL);
static	void ProcessFrontLineRequests ();
static	void SupplyHPNodes ();
static	void ProcessStoresDestroyed ();
static	void ResetPriorityAndServicedFlag();
static	void ProcessStoresArrival ();
static	void FrontLineStoresUsage (SupplyLine* SL);
static	void ResetFirstSupplyNode  (SupplyLine* SL);
static	void ProcessPreviousDaysSupplies();
static	void NodeReview ();
static	void UpDateAttacksStructure();
static	bool ChkSpringOffensiveOver();
static	int	FindBattleIndex();
static	void	RemoveDestroyedStores();
static	int		DestroyedStores(SupplyNode* node);



};
inline SupplyFightFiles* SupplyNode::FightFiles::operator->()
	{if (fightfiles) return  fightfiles;else return &SupplyTree::DummyBlank;}


#endif
