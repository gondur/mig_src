	Duty	DUTY_DiveSingle = (Select DA_DIVE,DA_SINGLEFILE),//MS 07Jun99
	Duty	DUTY_DiveIndividual = (Select DA_DIVE,DA_INDIVIDUAL),//MS 07Jun99
	Duty	DUTY_HighWide = (Select DA_HIGH,DA_WIDE),	//MS 07Jun99

	Shape	SHAPE_TroopDefend	=	TRAM,		//MS 27Apr99
	Shape	SHAPE_TroopMove		=	CHINFT,		//MS 27Apr99
	Shape	SHAPE_TroopAttack	=	UNINFT,

	Int	VEL_MoveTroop		=	75,		//MS 10Jun99
	Int	VEL_MoveMortar		=	75,		//MS 10Jun99
	Int	VEL_MoveVehicle		=	150,		//MS 10Jun99
	Int	VEL_MoveTank		=	125,		//MS 10Jun99
	Int	VEL_MoveArtillery	=	100,		//MS 10Jun99

//TempCode MS 23Jun99 	Int	VEL_AttackTroop		=	15,		//MS 10Jun99
//TempCode MS 23Jun99 	Int	VEL_AttackMortar	=	0,		//MS 10Jun99
//TempCode MS 23Jun99 	Int	VEL_AttackVehicle	=	15,		//MS 10Jun99
//TempCode MS 23Jun99 	Int	VEL_AttackTank		=	15,		//MS 10Jun99
//TempCode MS 23Jun99 	Int	VEL_AttackArtillery	=	0,		//MS 10Jun99

	Int	VEL_AttackTroop		=	25,		//MS 10Jun99
	Int	VEL_AttackMortar	=	99,		//MS 10Jun99
	Int	VEL_AttackVehicle	=	99,		//MS 10Jun99
	Int	VEL_AttackTank		=	50,		//MS 10Jun99
	Int	VEL_AttackArtillery	=	99,		//MS 10Jun99

	Int	Weap_Basic	= 0,				
	Int	Weap_Rocket	= 1,
	Int	Weap_RockFuel	= 2,
	Int	Weap_BombFuel	= 3,
	Int	Weap_NapmFuel	= 4,
	Int	Weap_BombRock	= 5,
	Int	Weap_NapmRock	= 6,
	

	Y	FT_TakeOff	=	-50,			//MS 30Sep96

	Int	Encounter00Mod	= 0,				//MS 28Aug96
	Int	EncounterHFMod	= 1,				//MS 28Aug96
	Int	Encounter01Mod	= 2,				//MS 28Aug96
	Int	Encounter01HFMod= 3,				//MS 28Aug96
	Int	Encounter02Mod	= 4,				//MS 28Aug96
	Int	Encounter02HFMod= 5,				//MS 28Aug96
	Int	Encounter03Mod	= 6,				//MS 28Aug96
	Int	Encounter03HFMod= 7,				//MS 28Aug96
	Int	Encounter04Mod	= 8,				//MS 28Aug96

 	Int EncounterList01 = {List	EncounterSize,1,1,1,2,2,3,3,4,4},//MS 28Aug96
 	Int EncounterList02 = {List	EncounterSize,1,1,2,3,4,5,6,7,8},//MS 28Aug96
 	Int EncounterList03 = {List	EncounterSize,1,2,3,5,6,7,9,10,12},//MS 28Aug96
 	Int EncounterList04 = {List	EncounterSize,1,2,4,6,8,10,12,14,16},//MS 28Aug96
 	Int EncounterList05 = {List	EncounterSize,1,3,5,7,10,13,15,17,18},//MS 28Aug96
 	Int EncounterList06 = {List	EncounterSize,1,3,6,9,12,14,18,18,18},//MS 28Aug96
 	Int EncounterList08 = {List	EncounterSize,1,4,8,12,16,18,18,18,18},//MS 28Aug96
 	Int EncounterList10 = {List	EncounterSize,1,5,10,15,18,18,18,18,18},//MS 28Aug96
 	Int EncounterList12 = {List	EncounterSize,1,6,12,18,18,18,18,18,18},//MS 28Aug96

	PaintScheme	COL_E0	=0x00000000;		//from specific image map set
	PaintScheme	COL_E1	=0x00000001;
	PaintScheme	COL_E2	=0x00000002;
	PaintScheme	COL_E3	=0x00000003;
	PaintScheme	COL_E4	=0x00000004;
	PaintScheme	COL_E5	=0x00000005;
	PaintScheme	COL_E6	=0x00000006;
	PaintScheme	COL_E7	=0x00000007;

	PaintScheme	COL_SAME=0x00000010;		//from random set, but all same set
	PaintScheme	COL_VARY=0x00000011;		//each part set randomly

	PaintScheme	COL_BOD	=0x10000000;		//specific body parts
	PaintScheme	COL_TAIL=0x01000000;
	PaintScheme	COL_ELEV=0x00100000;
	PaintScheme	COL_WTOP=0x00010000;
	PaintScheme	COL_WBOT=0x00001000;
	PaintScheme	COL_SIG	=0x00000100;

	PaintScheme	COL_ALL	=0x11111100;

	PaintScheme	COL_BOD_TAIL = {Select	COL_BOD,COL_TAIL};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_BOD_TAIL_SIG = {Select COL_BOD,COL_TAIL,COL_SIG};	//grouped body parts	//MS 30Sep96
	PaintScheme	COL_TAIL_ELEV = {Select	COL_TAIL,COL_ELEV};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_WTOP_WBOT = {Select	COL_WTOP,COL_WBOT};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_BOD_WBOT = {Select	COL_BOD,COL_WBOT};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_WBOT_WTOP = {Select	COL_WBOT,COL_WTOP};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_WTOP_TAIL = {Select	COL_WTOP,COL_TAIL};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_SIG_TAIL = {Select	COL_SIG,COL_TAIL};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_ELEV_WBOT = {Select	COL_ELEV,COL_WBOT};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_SIG_ELEV = {Select	COL_SIG,COL_ELEV};	//grouped body parts//MS 30Sep96

	Int	myval=0x12345678;


	Y NEGFT_0 = 0;
	Y NEGFT_20 = FT_20;					//MS 03Jul96
	Y NEGFT_50 = 0;
	Y NEGFT_100 = FT_100;					//MS 02Jul96
	Y NEGFT_200 = 0;
	Y NEGFT_500 = 0;
	Y NEGFT_1000 = FT_1000;					//MS 02Jul96
	Y NEGFT_1800 = 0;
	Y NEGFT_2000 = FT_2000;	
	Y NEGFT_2500 = 0;	

	Y FT_GRND = FT_10;					//MS 02Jul96

	Y FT_EnterLandingPattern = FT_1000;			//MS 11Nov96

	Y FT_CLOUDBASE = FT_5000;				//MS 21Aug96

	Y FT_SpotAlt = FT_4000;					//MS 02Jul96

	Y FT_ReconAlt = FT_4000;				//MS 02Jul96

	Y FT_BombAlt = FT_4000;

	Y FT_BustAlt = FT_4000;					//MS 04Jul96

	Y FT_BombStraffe = FT_4000;				//MS 04Jul96

	Y FT_Straffe = FT_4000;					//MS 12Dec96

	Y FT_InterceptAlt = FT_8000;
//
  //	Abs	BASELOCATION = {PosAfCpRoucourt};		//JIM 02Jul96

//this Position will be supplied by a 3ds ascii file 



	Posn	POS_1QTR		=	{Abs	{Y 1}},
	Posn	POS_3QTR		=	{Abs	{Y 3}},
	Posn	POS_HALF		=	{Abs	{Y 2}},
	


	Int	NEGMETRES800	=	-80000,


	Int	DistEnterLandingPattern = METRES1000,
	Int	NearEnterLandingPattern = METRES100,

//Keep hold of these 
	Int	IDENTRANGE=	METRES1000,	//METRES2500,	//MS 12Aug96
	Int	TWICEIDENTRANGE=METRES2000,	//METRES5000,	//MS 12Aug96
	Int	HALFIDENTRANGE=	METRES500,	//METRES1000,	//MS 12Aug96
	Int	HALFVISINEDGE=	METRES2000,			//MS 11Oct96
	Int	VISINEDGE=	METRES4000,	//METRES5000,	//MS 12Aug96
	Int	VISINEDGE2=	METRES4500,	//METRES6000,	//MS 12Aug96
	Int	VISOUTEDGE=	METRES5000,	//METRES8000,	//MS 12Aug96
//DeadCode RDH 25Oct96 	Int	VISBOUNDARYSIZE=	1000,	//3000,		//MS 12Aug96
	Int	VISBOUNDARYSIZE=	0,	//MSH 25Oct96 Will make AC appear close as pos
	Int	STANDARDTRIGGER=	METRES4000,	//METRES5000,	//METRES5000,//JIM 07Oct96
	Int	HALFSTANDARDTRIGGER=	METRES2000,	//METRES2500,//JIM 07Oct96
	Int	QTRSTANDARDTRIGGER=	METRES1000,		//MS 04Jul96
	Int	MARGIN=	METRES100,
	Int	MARGIN2=	METRES400,
	Int	CAMERATRIGGER=	METRES20,//10
	Int	CAMERATRIGGER2=	METRES40,//20

	Int	ATTACKBALLOONRANGE = METRES2000,
	Int	BEGINRECONRANGE = METRES2000,
	Int	BEGINSPOTRANGE = METRES2000,
	Int	BEGINBOMBRANGE = METRES2000,	
	Int	BEGINSTRAFFERANGE = METRES2000,
	Int	BEGINBOMBSTRAFFERANGE = METRES2000,		//MS 05Jul96
	Int	BEGINEYEBALLRANGE = METRES4000,			//MS 10Dec96
		
//These are test values

//DeadCode MS 04Oct96 	Int	IDENTRANGE=	METRES500,	//METRES1000,	//METRES2500,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	TWICEIDENTRANGE=METRES1000,	//METRES2000,	//METRES5000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	HALFIDENTRANGE= METRES250,	//METRES500,	//METRES1000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	VISINEDGE=	METRES2500,	//METRES5000,	//METRES5000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	VISINEDGE2=	METRES2500,	//METRES5500,	//METRES6000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	VISOUTEDGE=	METRES3000,	//METRES6000,	//METRES8000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	VISBOUNDARYSIZE=	1000,	//3000,		//MS 12Aug96
//DeadCode MS 04Oct96 	Int	STANDARDTRIGGER=	METRES2500,	//METRES5000,	//METRES5000,//MS 12Aug96
//DeadCode MS 04Oct96 	Int	HALFSTANDARDTRIGGER=	METRES1000,	//METRES2500,//MS 12Aug96
//DeadCode MS 04Oct96 	Int	QTRSTANDARDTRIGGER=	METRES250,	//METRES1000		//MS 04Jul96
//DeadCode MS 04Oct96 	Int	MARGIN=	METRES50,
//DeadCode MS 04Oct96 	Int	MARGIN2=	METRES100,
//DeadCode MS 04Oct96 	Int	CAMERATRIGGER=	METRES20,//10
//DeadCode MS 04Oct96 	Int	CAMERATRIGGER2=	METRES40,//20
//DeadCode MS 04Oct96 
//DeadCode MS 04Oct96 	Int	ATTACKBALLOONRANGE = METRES500,
//DeadCode MS 04Oct96 	Int	BEGINRECONRANGE = METRES500,
//DeadCode MS 04Oct96 	Int	BEGINSPOTRANGE = METRES500,
//DeadCode MS 04Oct96 	Int	BEGINBOMBRANGE = METRES500,	
//DeadCode MS 04Oct96 	Int	BEGINSTRAFFERANGE = METRES500,
//DeadCode MS 04Oct96 	Int	BEGINBOMBSTRAFFERANGE = METRES500,		//MS 05Jul96


	Int	JUMPINBAND=	METRES1000,

	Int	CLOSETRIGGER	=	100000,

	Skill	SKILL_MEDIUMTOHIGHMIX=	SKILL_VETERAN,

	Morale	MORALE_HIGH	= MORALE_EXCELLENT,
	Morale	MORALE_LOW	= MORALE_VERYPOOR,

//SPRING OFFENSIVE

//DeadCode MS 20Nov96 	Posn	SO14ROUTE_A =
//DeadCode MS 20Nov96 		{Abs	BASELOCATION, 
//DeadCode MS 20Nov96 		 Rel	{X -100000,  Z -100000}
//DeadCode MS 20Nov96 		},

//Route	ROUTE_BOMBHQ=
//{
//WayPoint	ROUTE_BOMBHQ_A,
//WayPoint	ROUTE_BOMBHQ_B,
//WayPoint	ROUTE_BOMBHQ_C,
//WayPoint	ROUTE_BOMBHQ_D,
//WayPoint	ROUTE_BOMBHQ_E,
//WayPoint	ROUTE_BOMBHQ_F,
//WayPoint	ROUTE_BOMBHQ_G,
//WayPoint	ROUTE_BOMBHQ_H,
//WayPoint	ROUTE_BOMBHQ_I,
//WayPoint	ROUTE_BOMBHQ_J,
//WayPoint	ROUTE_BOMBHQ_K
//};
//									//configured skill           {SKILL_NOVICE,	SKILL_POOR  ,	SKILL_REGULAR,	VETERAN			SKILL_ACE   ,	SKILL_HERO
		   //requested skill
  Skill		GetBlueNoviceSkill=	{List BLUESKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE};
  Skill		GetBluePoorSkill=		{List BLUESKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE1,	SKILL_NOVICE1,	SKILL_NOVICE2,	SKILL_NOVICE2,	SKILL_POOR};
  Skill		GetBlueRegularSkill=	{List BLUESKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE1,	SKILL_NOVICE2,	SKILL_POOR1,	SKILL_POOR2,	SKILL_REGULAR};
  Skill		GetBlueVeteranSkill=	{List BLUESKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR1,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN};
  Skill		GetBlueAceSkill=		{List BLUESKILLCONFIG,SKILL_NOVICE2,SKILL_POOR1,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetBlueHeroSkill=		{List BLUESKILLCONFIG,SKILL_POOR,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE,		SKILL_HERO};

  Skill		GetRedNoviceSkill=	{List REDSKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE};
  Skill		GetRedPoorSkill=		{List REDSKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE1,	SKILL_NOVICE1,	SKILL_NOVICE2,	SKILL_NOVICE2,	SKILL_POOR};
  Skill		GetRedRegularSkill=	{List REDSKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE1,	SKILL_NOVICE2,	SKILL_POOR1,	SKILL_POOR2,	SKILL_REGULAR};
  Skill		GetRedVeteranSkill=	{List REDSKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR1,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN};
  Skill		GetRedAceSkill=		{List REDSKILLCONFIG,SKILL_NOVICE2,	SKILL_POOR1,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetRedHeroSkill=		{List REDSKILLCONFIG,SKILL_POOR,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE,		SKILL_HERO};

  Skill		GetG0SkillMin=			{List Scram_G0_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG1SkillMin=			{List Scram_G1_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG2SkillMin=			{List Scram_G2_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG3SkillMin=			{List Scram_G3_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG4SkillMin=			{List Scram_G4_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG5SkillMin=			{List Scram_G5_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG7SkillMin=			{List Scram_G7_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};

  Skill		GetG0SkillMax=			{List Scram_G0_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG1SkillMax=			{List Scram_G1_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG2SkillMax=			{List Scram_G2_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG3SkillMax=			{List Scram_G3_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG4SkillMax=			{List Scram_G4_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG5SkillMax=			{List Scram_G5_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG6SkillMax=			{List Scram_G6_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG7SkillMax=			{List Scram_G7_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};



//TrainShapeInst1 is actually used as a formpos driven list
  Side		NatG0FST00=	{List FriendlyScoutType00,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG0Squad=	{List Scram_G0_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG1Squad=	{List Scram_G1_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG2Squad=	{List Scram_G2_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG3Squad=	{List Scram_G3_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG4Squad=	{List Scram_G4_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG5Squad=	{List Scram_G5_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG6Squad=	{List Scram_G6_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG7Squad=	{List Scram_G7_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
AirItem dummynameTrainShapeInst1=
{
	Shape	TrainShapeInst1=	
		{	
			List	TPINC,
				TBACK,
			Shape {	Select	
				{	List {Random 3},
					Shape {	List	{Random 6},
							CART1,
							TANKER,
							TCOAL,
							THAUL,
							SUPPLY,
							SUPPLY
					},
					Shape {	List	{Random 6},
							CRANE,
							TWOOD,
							TROOPC,
							TPIPE,
							SUPPLY,
							SUPPLY
					},
					Shape {	List	{Random 6},

							TCABLE,
							TEMPTY,
							TROLL,
							TGOODS,
							SUPPLY,
							SUPPLY
					}
		}	}	}//,

//TempCode MS 08Jun99 AirItem dummynameFlakShapeInst1=
//TempCode MS 08Jun99 {
//TempCode MS 08Jun99 	Shape	FlakShapeInst1=	
//TempCode MS 08Jun99 		{	
//TempCode MS 08Jun99 			List	TPINC,
//TempCode MS 08Jun99 				TBACK,
//TempCode MS 08Jun99 			Shape {	Select	
//TempCode MS 08Jun99 				{	List {Random 3},
//TempCode MS 08Jun99 					Shape {	List	{Random 6},
//TempCode MS 08Jun99 							CART1,
//TempCode MS 08Jun99 							TANKER,
//TempCode MS 08Jun99 							TCOAL,
//TempCode MS 08Jun99 							THAUL,
//TempCode MS 08Jun99 							SUPPLY,
//TempCode MS 08Jun99 							SUPPLY
//TempCode MS 08Jun99 					},
//TempCode MS 08Jun99 					Shape {	List	{Random 6},
//TempCode MS 08Jun99 							CRANE,
//TempCode MS 08Jun99 							TWOOD,
//TempCode MS 08Jun99 							TROOPC,
//TempCode MS 08Jun99 							TPIPE,
//TempCode MS 08Jun99 							SUPPLY,
//TempCode MS 08Jun99 							SUPPLY
//TempCode MS 08Jun99 					},
//TempCode MS 08Jun99 					Shape {	List	{Random 6},
//TempCode MS 08Jun99 
//TempCode MS 08Jun99 							TCABLE,
//TempCode MS 08Jun99 							TEMPTY,
//TempCode MS 08Jun99 							TROLL,
//TempCode MS 08Jun99 							TGOODS,
//TempCode MS 08Jun99 							SUPPLY,
//TempCode MS 08Jun99 							SUPPLY
//TempCode MS 08Jun99 					}
//TempCode MS 08Jun99 		}	}	}
};
