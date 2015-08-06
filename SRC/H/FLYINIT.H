//------------------------------------------------------------------------------
//Filename       flyinit.h
//System         
//Author         R. Hyde 
//Date           Mon 4 Dec 1995
//Description    project specific list of planeytpes
//------------------------------------------------------------------------------
#ifndef	FLYINIT_Included
#define	FLYINIT_Included

#define	DEFAULT_FLYINIT 0

enum	QuitGameConditions {ALT_X = 0,STANDARDQUIT,SEENBYLEADER , COMECLOSETOLEADER, LEADERREACHEDDESTINATION,ACMTRAININGTIMEUP,
							CRASHED_DEAD,CRASHED_ALIVE,CRASHED_BENTWING,CRASH_TOOFAST,LANDED_OK,LANDED_ONSQUARE,
							SPRINGOFFENSIVELOST,SPRINGOFFENSIVEWON,
							EVACUATESUCCESS,EVACUATEFAILURE, COMMSQUIT
							
							
							};

enum	PlaneTypeSelect											//RDH 06Aug96
		{PT_F86A,PT_F86E ,PT_F86F, PT_F84,PT_F80,PT_F51,PT_F82,
			PT_B26,
			PT_B29,
			PT_T6,PT_4U,
			PT_MIG15,PT_MIG15BIS,		//RDH 17Feb97
			PT_YAK,
			PT_VEHICLES,
			PT_ATruck=PT_VEHICLES,
			PT_ATank,
			PT_BADMAX,
	
			PT_F86WEAPPAK=PT_F86F,
			PT_MIGWEAPPAK=PT_T6,

		};

enum	SquadSelect	 		
//The five fully populated flyable blue squadrons must come first in this list,
//then non-flyable blues, then flyable reds, then non-flyable reds
	{	SQ_B_FLYABLE=0,
			SQ_F86A=0,SQ_F86B,SQ_F80,SQ_F84,SQ_F51,
		SQ_B_NONFLYABLE=5,
			SQ_B26=5,SQ_B29,
		SQ_B_NONFLYSPOT=7,	
			SQ_T6=7,SQ_4U,
		SQ_R_FLYABLE=9,			SQ_MIG15=9,//alias
			SQ_M15=9,SQ_M15B,
		SQ_R_NONFLYABLE=11,
			SQ_YAK=11,
		SQ_R_MOREMIGSQUADS=12,
		SQ_M15_0=12,SQ_M15_1,SQ_M15_2,SQ_M15_3,
		SQ_M15_4,SQ_M15_5,SQ_M15_6,SQ_M15_7,
		SQ_VEHICLES=20,
			SQ_ATruck=20,SQ_ATank

	};
//
//Translation between squad and planetype takes place in Persons3::Squad2Type()
//

//DEADCODE RDH 03/03/99 enum	AcPosition{ FLIGHTLEADER, ELEMENTLEADER, WINGMAN, LONER };
enum	tThreatLevel	{
		BANDITNEVER,						//never engage, used if damaged
		BANDITINENGAGERANGEOFFRIENDLY,		//used for bait
		BANDITFIRING,
		BANDITINWEAPONSRANGE,
		BANDITINDANGERRANGE,
		BANDITINENGAGERANGE,
		BANDITINCOMBATRANGE,
		BANDITANYWHERE
		};
enum	tAggressionLevel	{
		AL_STOODDOWN,			//don't launch
		AL_MIN = AL_STOODDOWN,
		AL_TRAINING,			//launch but will not engage
		AL_DEFENSIVE,			//attack bombers if with weapons
		AL_ATTACKBOMBERSONLY,	//never attack fighters
		AL_SPLITFORCE,			//attack fighters only if they are 
								//escorting bombers
		AL_ATTACKWEAKNESSES,	//attack fighters if low on fuel, 
								//damaged etc.
		AL_ATTACKANYTHING,		//aggressive behaviour
		AL_MAX=AL_ATTACKANYTHING,
		AL_STAGE = 1
				};

enum AcTactics {WELDEDWING, TOPCOVER, SWORDANDSHIELD, LOOSEDEUCE};

#define	MAX_NUM_AC_IN_SQUADRON 19

enum	tFirstEncounterTactics
			{TACTIC_NULL,
			 TACTIC_LINEASTERN,		
			 TACTIC_LINEABREAST,
			 TACTIC_SCATTER,		//go straight in
			 TACTIC_PINCER,		//split force and pincer
			 TACTIC_MULTIWAVE,		//split force and delay some of it
			 TACTIC_DIVEANDZOOM,
//DEADCODE RDH 08/03/99 			 TACTIC_DECOYACTIVE,	//decoy ac do something, ie skip waypoint
//DEADCODE RDH 08/03/99 			 TACTIC_DECOYPASSIVE,	//decoy ac continue unaffected
			 TACTIC_ROUNDABOUT		//go int circles
			};

enum	DutyType
{
	DUTYMASK=0xf0,
	DC_BOMB=0x00,
	DC_TARGPATROLS=0x10,
	DC_CAS=0x10,
	DC_WW=0x20,
	DC_AR=0x30,

	DA_LEVEL=0,
	DA_DIVE=8,
	ACTIONCODE=0x0f,
	ACTIONSUBCODE=0x07,
	ACTIONSUBCODEMAX=0x08,
	DA_HIGH=0,
	DA_WIDE=1,
	DA_SINGLEFILE=2,
	DA_INDIVIDUAL=3,
	DA_ELEMENT=4,
	DA_SPACEDIND=5,
	DA_SPACEDELT=6,
	DA_SPACEDFLT=7,
	DA_CAP=8,

	DD_ILLEGALWIDE=9,
	DD_SINGLEFILE=10,
	DD_INDIVIDUAL=11,
	DD_ELEMENT=12,
	DD_SPACEDIND=13,
	DD_SPACEDELT=14,
	DD_SPACEDFLT=15,

	DUTYESCORT=0x18,
	DUTYBARCAP=0x28,
	DUTYMIGCAP=0x38,

/**/	MAKEDUTYBOMB=(int)DC_BOMB+(int)DA_HIGH,
/**/	MAKEDUTYCAS=(int)DC_CAS+(int)DA_LEVEL+(int)DA_SPACEDELT,
/**/	MAKEDUTYWW=(int)DC_WW+(int)DA_DIVE+(int)DA_SPACEDIND,
/**/	MAKEDUTYAR=(int)DC_AR+(int)DA_DIVE+(int)DA_INDIVIDUAL,
    DUTY_ALIGN=0xffff
};

//DEADCODE JIM 24/03/99 enum	DutyType
//DEADCODE JIM 24/03/99 
//DEADCODE JIM 24/03/99 //there is a list of text strings which uses this set of duties
//DEADCODE JIM 24/03/99 //called IDS_L_
//DEADCODE JIM 24/03/99 		{
//DEADCODE JIM 24/03/99 //17Nov 98 list
//DEADCODE JIM 24/03/99 			DUTYBOMB=0,
//DEADCODE JIM 24/03/99 			DUTYDIVEBOMB=1,
//DEADCODE JIM 24/03/99 			DUTYRECONN=2,
//DEADCODE JIM 24/03/99 			DUTYTARGPATROLS=3,
//DEADCODE JIM 24/03/99 			DUTYFLAKSUPP=3,
//DEADCODE JIM 24/03/99 			DUTYESCORT=4,				//RDH 18Feb97
//DEADCODE JIM 24/03/99 			DUTYCAP=5,
//DEADCODE JIM 24/03/99 			DUTYCAS=6,
//DEADCODE JIM 24/03/99 			DUTYSPOT=7,
//DEADCODE JIM 24/03/99 //			DUTYCAP=0,
//DEADCODE JIM 24/03/99 //			DUTYHEAVYBOMB=1,
//DEADCODE JIM 24/03/99 //			DUTYBOMB=2,
//DEADCODE JIM 24/03/99 //			DUTYCLOSEESCORT=3,				//RDH 18Feb97
//DEADCODE JIM 24/03/99 //			DUTYHIGHESCORT=4,
//DEADCODE JIM 24/03/99 //			DUTYFLAKSUPP=5,
//DEADCODE JIM 24/03/99 //			DUTYRECONN=6,
//DEADCODE JIM 24/03/99 //			DUTYSPOT=7,
//DEADCODE JIM 24/03/99 //			DUTYNAPALM=8,
//DEADCODE JIM 24/03/99 //			DUTYROCKETS=9,
//DEADCODE JIM 24/03/99 //			DUTYSTRAFF=10,
//DEADCODE JIM 24/03/99 //			DUTYCAS=11,
//DEADCODE JIM 24/03/99 			
//DEADCODE JIM 24/03/99 			DUTY_ALIGN=0xffff};		//RDH 18Feb97

inline	SWord&	operator *(DutyType& f){return(SWord&) f;}

//MARK, here are the form types for flight and group levels		//RDH 05Mar99

enum	FormationTypeIndex
		{
//DeadCode MS 08Mar99 			FORM_STACKEDV = 0,
//DeadCode MS 08Mar99 		 	FORM_STACKEDBOX,
//DeadCode MS 08Mar99 			FORM_DIAMOND,
//DeadCode MS 08Mar99 			FORM_FLATBOX,
//DeadCode MS 08Mar99 			FORM_V,
//DeadCode MS 08Mar99 			FORM_TWOV,
//DeadCode MS 08Mar99 			FORM_FILLEDV,
//DeadCode MS 08Mar99 			FORM_FINGER4,
//DeadCode MS 08Mar99 //NEW MARKS														//MS 05Mar99
//DeadCode MS 08Mar99 			FORM_STRING,
//DeadCode MS 08Mar99 			FORM_GAGGLE,
//DeadCode MS 08Mar99 			FORM_SHEPHERD,
//DeadCode MS 08Mar99 			FORM_LOOSEFINGER,
//DeadCode MS 08Mar99 			FORM_ECHELONRIGHT,
//DeadCode MS 08Mar99 			FORM_ECHELONLEFT,
//DeadCode MS 08Mar99 			FORM_ABREAST,
//DeadCode MS 08Mar99 			
//DeadCode MS 08Mar99 //NOT ACCESSIBLE BY PLAYER										//MS 05Mar99
//DeadCode MS 08Mar99 			FORM_LOOSE,
//DeadCode MS 08Mar99 			FORM_RANDOM,
//DeadCode MS 08Mar99 			FORM_IMPLODE,
//DeadCode MS 08Mar99 			FORM_EXPLODE,
//DeadCode MS 08Mar99 			FORM_TAKEOFF,
//DeadCode MS 08Mar99 			FORM_SINGLEFILE
//DeadCode MS 08Mar99 
//DeadCode MS 08Mar99 //TempCode MS 05Mar99 			FORM_
//DeadCode MS 08Mar99 //TempCode MS 05Mar99 			FORM_FINGERFOUR,
//DeadCode MS 08Mar99 //TempCode MS 05Mar99 			FORM_LOOSEFINGER,
//DeadCode MS 08Mar99 //TempCode MS 05Mar99 			FORM_ECHELONRIGHT,
//DeadCode MS 08Mar99 //TempCode MS 05Mar99 			FORM_ECHELONLEFT,
//DeadCode MS 08Mar99 //TempCode MS 05Mar99 			FORM_MESS,
//DeadCode MS 08Mar99 
//DeadCode MS 08Mar99 
//DeadCode MS 08Mar99 
//DeadCode MS 08Mar99 		};				
//DeadCode MS 08Mar99 
//DeadCode MS 08Mar99 enum	SquadronTypeIndex
//DeadCode MS 08Mar99 		{
			
			FORM_V =0,				//ground mobiles			//MS 07Apr99
			FORM_SINGLEFILE,		//ground mobiles			//MS 07Apr99
			SQUAD_TAKEOFF,
//UN SQUAD FORMATIONS
			SQUAD_FLATV,	SQUAD_FIRST_UN=SQUAD_FLATV,
			SQUAD_FLATV_Right,
			SQUAD_FLATV_Left,
			SQUAD_FLATV_Ahead,
			SQUAD_STACKEDV,
			SQUAD_STACKEDV_Right,
			SQUAD_STACKEDV_Left,
			SQUAD_STACKEDV_Ahead,
			SQUAD_ECHELONRIGHT,
			SQUAD_ECHELONRIGHT_Right,
			SQUAD_ECHELONRIGHT_Left,	
			SQUAD_ECHELONRIGHT_Ahead,
			SQUAD_ECHELONLEFT,
			SQUAD_ECHELONLEFT_Right,
			SQUAD_ECHELONLEFT_Left,	
			SQUAD_ECHELONLEFT_Ahead,
			SQUAD_STACKEDLINE,
			SQUAD_STACKEDLINE_Right,
			SQUAD_STACKEDLINE_Left,	
			SQUAD_STACKEDLINE_Ahead,
			SQUAD_LINEABREAST,
			SQUAD_LINEABREAST_Right,
			SQUAD_LINEABREAST_Left,	
			SQUAD_LINEABREAST_Ahead,
			SQUAD_BOX,
			SQUAD_BOX_Right,
			SQUAD_BOX_Left,	
			SQUAD_BOX_Ahead,
			SQUAD_DIAMOND,
			SQUAD_DIAMOND_Right,
			SQUAD_DIAMOND_Left,	
			SQUAD_DIAMOND_Ahead,
//UN COMBAT FORMATIONS
			SQUAD_COMBAT_FLATV,
//MIG SQUAD FORMATIONS - NOT ACCESIBLE BY PLAYER				//MS 07Apr99
			SQUAD_DECOY,	SQUAD_FIRST_MIG=SQUAD_DECOY,
			SQUAD_UPPERCUT,										//MS 05Mar99
			SQUAD_STAIRCASE,									//MS 05Mar99
			SQUAD_3LEVELS,										//MS 05Mar99
			SQUAD_STRING,										//MS 05Mar99
			SQUAD_CH_ABREAST,									//MS 07Apr99
			SQUAD_GAGGLE,										//MS 07Apr99
			SQUAD_MIG_LEFT,
			SQUAD_MIG_RIGHT,
			SQUAD_VIC,
//NOT ACCESSIBLE BY PLAYER										//MS 05Mar99
			SQUAD_TRUCKCONVOY,
			SQUAD_TRAINCONVOY,
			SQUAD_BATTLELINE,
			SQUAD_BAIT,
			SQUAD_DUMMY02,										//MS 05Mar99
			SQUAD_DUMMY03,										//MS 05Mar99
			SQUAD_DUMMY04,										//MS 05Mar99
			SQUAD_DUMMY05,										//MS 05Mar99
			SQUAD_DUMMY06,										//MS 05Mar99
			SQUAD_DUMMY07,										//MS 05Mar99
			SQUAD_DUMMY08										//MS 05Mar99
		};
					
enum	SquadronTypeIndex	{STI_DUMMY};
MINMAX(FormationIndex,0,255);
MINMAX(InWing,0,15);		//high field
MINMAX(InForm,0,15);	//low field
inline	FormationIndex	operator	+	(InWing W,InForm F)
	{return (FormationIndex) (((int)W<<5)+(int)F);}
inline	FormationIndex	operator	+	(InForm	F)	{return (FormationIndex)(F);}

inline	FormationIndex	operator	+=	(FormationIndex& I,InForm F)
	{return (  I=(FormationIndex)  ( ((int)I&15) + (int)F )  );}
inline	FormationIndex	operator	+=	(FormationIndex& I,InWing W)
	{return (  I=(FormationIndex)  ( (int)I + ((int)W<<4) )  );}
inline	FormationIndex	operator	+	(FormationIndex I,InWing W)
	{return (  (FormationIndex)  ( (int)I + ((int)W<<4) )  );}
inline	FormationIndex	operator	+	(FormationIndex I,InForm F)
	{return (  (FormationIndex)  ( ((int)I&15) + (int)F )  );}

inline	FormationIndex	operator	&	(FormationIndex I,InWing W)
	{return   (FormationIndex)  ( ((int)I>>4) & (int)W  );}	//RDH 13May96
inline	FormationIndex	operator	&	(FormationIndex I,InForm F)
	{return (  (FormationIndex)  ( (int)I & (int)F )  );}

enum	CharacterType
		{CHAR_TACTICIAN = 0,CHAR_MRAVERAGE,CHAR_CAVALIER,CHAR_TIMID,CHAR_align=255};		
enum	SkillType
		{	SKILL_NOVICE = 0,	SKILL_NOVICE1=1,SKILL_NOVICE2=2,
			SKILL_POOR = 3,		SKILL_POOR1 = 4,SKILL_POOR2 = 5,
			SKILL_REGULAR=6,	SKILL_REGULAR1=7,SKILL_REGULAR2=8,
			SKILL_VETERAN=9,	SKILL_VETERAN1=10,SKILL_VETERAN2=11,
			SKILL_ACE=12,		SKILL_ACE1=13,SKILL_ACE2=14,
			SKILL_HERO=15,
			SKILL_STAGE=3,		SKILL_MAX=15, SKILL_align=255};

enum	Potential
		{
			POTENTIAL_MAX		=15,
			POTENTIAL_EXCELLENT	=13,
			POTENTIAL_VERYGOOD	=11,
			POTENTIAL_GOOD		=9,
			POTENTIAL_REGULAR	=7,
			POTENTIAL_POOR		=5,
			POTENTIAL_VERYPOOR	=3,
			POTENTIAL_NONE		=0
		};
enum	MoraleType
		{MORALE_ROCKBOTTOM = 0,MORALE_VERYPOOR = 40,MORALE_STAGE = 40,MORALE_HALFSTAGE = 20,
//DeadCode RDH 27Mar98 			MORALE_MINUSHALFSTAGE = -20,
		MORALEINC_STEP = 120,
		MORALE_POOR =80,MORALE_MEDIUM = 120,MORALE_GOOD =160,MORALE_VERYGOOD = 200,MORALE_EXCELLENT = 240,MORALE_TOPMORALE = 255 };
#define			MORALE_MINUSHALFSTAGE (-MORALE_HALFSTAGE)

//DeadCode RDH 27Mar98 enum	DispositionType
//DeadCode RDH 27Mar98 		{	PESSIMISTIC = 0, REALISTIC,OPTIMISTIC
//DeadCode RDH 27Mar98 			};
enum	MeritType
		{MERIT_ROCKBOTTOM = 0,MERIT_INITIAL = 1000,MERIT_2LFTEXPERIENCED =5000,
		MERIT_LFT = 8000,
		MERIT_CAPTAIN = 12000,MERIT_MAJOR =18000,MERIT_MAJORHONOUR = 27000,
		MERIT_MAJORHONOURPLUS = 30000,MERIT_TOP = 65534,MERIT_IMPOSSIBLE = 65535,
		
//Spring Offensive merits to get operational		
		MERIT_OPERATIONAL = 3000
			

		};
//aims is to get 30000 merit points by end of campaign			//RDH 23Sep96
//Circus	36 kills: 2 kills a mission, 20 missions -> 750 merit per kill
enum	DeltaMeritType
		{
//DeadCode RDH 08Dec96 		MERIT_TARGET_DESTROYED = 3000,
		MERIT_TARGET_DESTROYED = 2000,							//RDH 08Dec96
		MERIT_KILL = 750,
		MERIT_VIS_MSN_SUCCESS =4000,
		MERIT_OP_CRASHLAND = -300,
		MERIT_OP_BENTGEAR = -100,
//DeadCode RDH 11Dec96 		MERIT_OP_KANGAROO = 300,
		MERIT_OP_GOODLANDING = 100,
		MERIT_OP_LANDEDONSQUARE = 500,
		MERIT_OP_STAYEDVCLOSETOCO = 3000,
		MERIT_OP_STAYEDCLOSETOCO = 1500,
		MERIT_OP_STAYEDINVICINITYOFCO = 1000,
		MERIT_OP_MILESFROMCO = -1000,
		MERIT_OP_SEENBYCO = -1000,
		MERIT_OP_NOTSEENBYCO =1000,
		MERIT_OP_HITSNEARCO = 3000

		};


//DeadCode RDH 27Mar98 enum 	AerobaticFactor {AEROBATIC_LOW,AEROBATIC_MEDIUM,AEROBATIC_HIGH};
//		Aerobaticfactor is used to determine type of aircraft	//RDH 03Mar98
//		perhaps it should be combat ability						//RDH 03Mar98
enum 	AerobaticFactor {AEROBATIC_LOW,			//medium bomber
						AEROBATIC_MEDIUM,		//prop
						AEROBATIC_HIGH,	 		//fighterbomber
						AEROBATIC_FIGHTER,		//sabre or mig
//						AEROBATIC_MIG,
//						AEROBATIC_SABRE,
						AEROBATIC_HIGHEST
						};
 
enum	CallNames	{	Call_Pilot0=1,Call_Pilot29=30,
						Call_FAC0,Call_FAC1,Call_FAC2,
						Call_TAC0,Call_TAC1,Call_TAC2,
						Call_Dentist,Call_Tower,
					};

//DEADCODE JIM 04/03/99 enum	SquadNames
//DEADCODE JIM 04/03/99 		{
//DEADCODE JIM 04/03/99 
//DEADCODE JIM 04/03/99 			MySquadAce,TheirSquadAce,AnotherSquadAce,SqdnAce48,
//DEADCODE JIM 04/03/99 			SqdnAce56,Jasta11Ace,OttoKonnecke,FritzRumey,
//DEADCODE JIM 04/03/99 				SNEQU_LASTACE,
//DEADCODE JIM 04/03/99  			Jasta02,Jasta03,Jasta04,Jasta05,
//DEADCODE JIM 04/03/99 			Jasta06,Jasta07,Jasta08,Jasta10,
//DEADCODE JIM 04/03/99 			Jasta11,Jasta12,Jasta19,Jasta23,
//DEADCODE JIM 04/03/99 			Jasta32,Jasta64,Jasta65,JastaAnon,
//DEADCODE JIM 04/03/99 				SNEQU_SECONDSET,
//DEADCODE JIM 04/03/99 			Pursuit27,Pursuit95,Group02,Frog,
//DEADCODE JIM 04/03/99 			SquadAnon,SquadBIAF,Squad11,Squad29,
//DEADCODE JIM 04/03/99 			Squad40,Squad43,Squad48,Squad54,
//DEADCODE JIM 04/03/99 			Squad56,Squad60,Squad66,Squad70
//DEADCODE JIM 04/03/99 		};
//DEADCODE JIM 04/03/99 
//Blues are aggressive friendly forces (do the killing)
//Reds are aggressive unfriendly forces (get killed)
//green are non-aggressive neutral forces (bugger 'em)
//amber are aggressive neutral forces (bugger me)
//	 moved from worldinc 7/8/98
enum	Nationality	{NAT_RED=1,NAT_BLUE=2,NAT_GREEN=0,NAT_AMBER=3,NAT_ALIGN=255};
#endif


