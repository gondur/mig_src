/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       meglobals.cpp
//System
//Author         Jim Taylor
//Date           //RDH 04Jun97
//
//				A version of Globrefs.cpp for the mission editor
//
//
//
//
//
//
//Description    Main program interface to global refs table
//				There are 2 types of global reference - internal and external
//				Internal references simply communicate information from the
//				battlefield header into the battlefield body.
//				Internal references can also communicate between battlefields,
//				either by generous luck, or in the events system.
//				External references are when the battlefield has access to a
//				variable in the main program. It may be setting the value as a
//				flag to the program, or reading a value set by the main program.
//				Internal references are declared in this file
//				External references are fixed up in this file using #define
//				or reference variables to fix the globref name to the real name.
//				I need a mechanism which allows this to be controlled.
//				I think this definitely means using #defines.
//------------------------------------------------------------------------------
#include	"DosDefs.h"
#include	"iostream.h"
#include	"text.h"
#include	"files.g"
#include	"Makebf.h"
#include	"textref.h"
#include	"Persons2.h"
#include	"viewsel.h"
#include	"transite.h"										//PD 29Apr96
#include	"Miles.h"

#include "globals.h"
#include "strings.h"
//------------------------------------------------------------------------------
//declare your internal variables and global #defines here:
//Intenal variables that are hidden:
//

static	EventProcessor
IntProcess =
{
	ENUM_RealInt,
	P_INT,
	0,
	100
},
AltProcess =
{
	ENUM_RealInt,
	P_ALT,
	100000,
	-300000
},


HideProcess =
{
	ENUM_RealInt,
	P_INT,
	0,
	100,
	-1
},
UIDProcess =
{
	ENUM_UniqueID,
	P_TARGET,
	-1,
	-1
},
HBProcess =
{
	ENUM_UniqueID,
	P_HOMEBASE,
	-1,
	-1
},
TargetProcess =
{
	ENUM_UniqueID,
	P_TARGET,
	-1,
	-1
},
//SpinProcess =
//{
//	ENUM_RealInt,
//	P_SPIN,
//	0,
//	16
//},
FlightSizeProcess =
{
	ENUM_RealInt,
	P_SPIN,
	1,
	6
},
//SquadSizeProcess =
//{
//	ENUM_RealInt,
//	P_SPIN,
//	1,
//	3
//},

//EventProcessor	SquadronProcess =
//{
//	ENUM_hide,
//	P_INT,
//	1,
//	10
//};
AnglesProcess =
{
	ENUM_Angle,
	P_INT,
	0,
	65535
},

ActionProcess =
{
	ENUM_Action,
	P_INT,
	0,
	65535
},
PaintProcess =
{
	ENUM_PaintScheme,
	P_PAINT,
	0,
	7
},
CharProcess =
{
	ENUM_Character,
	P_COMBOBOX,
	IDS_TACTICIAN,
	IDS_CAVALIER,
   1

},
EncounterSizeProcess =
{
	ENUM_RealInt,
	P_COMBOBOX,
	TEXT_0,
	TEXT_8,
   1

},
AcTypeProcess =
{
	ENUM_Type,
	P_COMBOBOX,
	IDS_PLANE_TYPE_CAMEL,
	IDS_PLANE_TYPE_SE5,
   1

},
SkillProcess =
{
	ENUM_Skill,
	P_COMBOBOX,
	IDS_TEXT_NOVICE,
	IDS_TEXT_HERO,
   SKILL_STAGE
},
MoraleProcess =
{
	ENUM_Morale,
	P_COMBOBOX,
	IDS_TEXT_ROCKBOTTOM,
	IDS_TEXT_EXCELLENT,
   MORALE_STAGE
},
NatProcess =
{
	ENUM_Side,
	P_COMBOBOX,
	IDS_NEUTRAL,
	IDS_ALLIES,
   1

};
EventProcessor
ShapeProcess =
{
 	ENUM_Shape,
    P_COMBOBOX,
	IDS_TEXT_NOVICE,
	IDS_TEXT_HERO,
};


typedef	GlobalsInfo& GlobalsInfoRef;

static	GlobalsInfo
GR_Pack_Takeoff={"FirstObject",
									IDS_CLOUDBASE,
									IDS_HELP_CLOUDBASE,
									&HideProcess,
									5000
								};

ULong&	GR_TakeOffTime=(ULong&)GR_Pack_Takeoff.value;
#define	GR_TakeOffTime	GR_TakeOffTimeInst
static GlobalsInfoRef

GR_Pack_Target=GR_Pack_Takeoff,
GR_Pack_Regroup=GR_Pack_Takeoff,
GR_AAALevel64K=GR_Pack_Takeoff,
GR_Pack_Targ_F0_E0=GR_Pack_Takeoff,GR_Pack_Targ_F0_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F1_E0=GR_Pack_Takeoff,GR_Pack_Targ_F1_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F2_E0=GR_Pack_Takeoff,GR_Pack_Targ_F2_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F3_E0=GR_Pack_Takeoff,GR_Pack_Targ_F3_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F4_E0=GR_Pack_Takeoff,GR_Pack_Targ_F4_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F5_E0=GR_Pack_Takeoff,GR_Pack_Targ_F5_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F6_E0=GR_Pack_Takeoff,GR_Pack_Targ_F6_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F7_E0=GR_Pack_Takeoff,GR_Pack_Targ_F7_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F8_E0=GR_Pack_Takeoff,GR_Pack_Targ_F8_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F9_E0=GR_Pack_Takeoff,GR_Pack_Targ_F9_E1=GR_Pack_Takeoff,

GR_Pack_Targ_F10_E0=GR_Pack_Takeoff,GR_Pack_Targ_F10_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F11_E0=GR_Pack_Takeoff,GR_Pack_Targ_F11_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F12_E0=GR_Pack_Takeoff,GR_Pack_Targ_F12_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F13_E0=GR_Pack_Takeoff,GR_Pack_Targ_F13_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F14_E0=GR_Pack_Takeoff,GR_Pack_Targ_F14_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F15_E0=GR_Pack_Takeoff,GR_Pack_Targ_F15_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F16_E0=GR_Pack_Takeoff,GR_Pack_Targ_F16_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F17_E0=GR_Pack_Takeoff,GR_Pack_Targ_F17_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F18_E0=GR_Pack_Takeoff,GR_Pack_Targ_F18_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F19_E0=GR_Pack_Takeoff,GR_Pack_Targ_F19_E1=GR_Pack_Takeoff,

GR_Pack_Targ_F20_E0=GR_Pack_Takeoff,GR_Pack_Targ_F20_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F21_E0=GR_Pack_Takeoff,GR_Pack_Targ_F21_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F22_E0=GR_Pack_Takeoff,GR_Pack_Targ_F22_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F23_E0=GR_Pack_Takeoff,GR_Pack_Targ_F23_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F24_E0=GR_Pack_Takeoff,GR_Pack_Targ_F24_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F25_E0=GR_Pack_Takeoff,GR_Pack_Targ_F25_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F26_E0=GR_Pack_Takeoff,GR_Pack_Targ_F26_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F27_E0=GR_Pack_Takeoff,GR_Pack_Targ_F27_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F28_E0=GR_Pack_Takeoff,GR_Pack_Targ_F28_E1=GR_Pack_Takeoff,
GR_Pack_Targ_F29_E0=GR_Pack_Takeoff,GR_Pack_Targ_F29_E1=GR_Pack_Takeoff,
GR_WaveNum=GR_Pack_Takeoff,
GR_TakeOffTime=GR_Pack_Takeoff,
GR_Pack_TakeTime_W0G0=GR_Pack_Takeoff,
GR_Pack_TakeTime_W0G1=GR_Pack_Takeoff,
GR_Pack_TakeTime_W0G2=GR_Pack_Takeoff,
GR_Pack_TakeTime_W1G0=GR_Pack_Takeoff,
GR_Pack_TakeTime_W1G1=GR_Pack_Takeoff,
GR_Pack_TakeTime_W1G2=GR_Pack_Takeoff,
GR_Pack_TakeTime_W2G0=GR_Pack_Takeoff,
GR_Pack_TakeTime_W2G1=GR_Pack_Takeoff,
GR_Pack_TakeTime_W2G2=GR_Pack_Takeoff,
GR_Pack_TakeTime_W3G0=GR_Pack_Takeoff,
GR_Pack_TakeTime_W3G1=GR_Pack_Takeoff,
GR_Pack_TakeTime_W3G2=GR_Pack_Takeoff,
GR_Pack_TakeTime_W4G0=GR_Pack_Takeoff,
GR_Pack_TakeTime_W4G1=GR_Pack_Takeoff,
GR_Pack_TakeTime_W4G2=GR_Pack_Takeoff,
GR_Pack_TakeTime_W5G0=GR_Pack_Takeoff,
GR_Pack_TakeTime_W5G1=GR_Pack_Takeoff,
GR_Pack_TakeTime_W5G2=GR_Pack_Takeoff,
GR_Pack_TakeTime_W6G0=GR_Pack_Takeoff,
GR_Pack_TakeTime_W6G1=GR_Pack_Takeoff,
GR_Pack_TakeTime_W6G2=GR_Pack_Takeoff,
GR_Pack_TakeTime_W7G0=GR_Pack_Takeoff,
GR_Pack_TakeTime_W7G1=GR_Pack_Takeoff,
GR_Pack_TakeTime_W7G2=GR_Pack_Takeoff,
GR_GroundForceType=GR_Pack_Takeoff,
GR_Pack_BlankZero=GR_Pack_Takeoff,
GR_Pack_Sq0_Used=GR_Pack_Takeoff,
GR_Pack_Sq1_Used=GR_Pack_Takeoff,
GR_Pack_Sq2_Used=GR_Pack_Takeoff,
GR_Pack_Sq3_Used=GR_Pack_Takeoff,
GR_Pack_Sq4_Used=GR_Pack_Takeoff,
GR_Pack_PlayerSquad=GR_Pack_Takeoff,
GR_Pack_PlayerPos=GR_Pack_Takeoff,

GR_Scram_G0_Alt=GR_Pack_Takeoff,
GR_Scram_G1_Alt=GR_Pack_Takeoff,
GR_Scram_G2_Alt=GR_Pack_Takeoff,
GR_Scram_G3_Alt=GR_Pack_Takeoff,
GR_Scram_G4_Alt=GR_Pack_Takeoff,
GR_Scram_G5_Alt=GR_Pack_Takeoff,
GR_Scram_G6_Alt=GR_Pack_Takeoff,
GR_Scram_G7_Alt=GR_Pack_Takeoff,

GR_Scram_G0_AC=GR_Pack_Takeoff,
GR_Scram_G1_AC=GR_Pack_Takeoff,
GR_Scram_G2_AC=GR_Pack_Takeoff,
GR_Scram_G3_AC=GR_Pack_Takeoff,
GR_Scram_G4_AC=GR_Pack_Takeoff,
GR_Scram_G5_AC=GR_Pack_Takeoff,
GR_Scram_G6_AC=GR_Pack_Takeoff,
GR_Scram_G7_AC=GR_Pack_Takeoff,

GR_Scram_G0_Skill=GR_Pack_Takeoff,
GR_Scram_G1_Skill=GR_Pack_Takeoff,
GR_Scram_G2_Skill=GR_Pack_Takeoff,
GR_Scram_G3_Skill=GR_Pack_Takeoff,
GR_Scram_G4_Skill=GR_Pack_Takeoff,
GR_Scram_G5_Skill=GR_Pack_Takeoff,
GR_Scram_G6_Skill=GR_Pack_Takeoff,
GR_Scram_G7_Skill=GR_Pack_Takeoff,

GR_Scram_G0_Squad=GR_Pack_Takeoff,
GR_Scram_G1_Squad=GR_Pack_Takeoff,
GR_Scram_G2_Squad=GR_Pack_Takeoff,
GR_Scram_G3_Squad=GR_Pack_Takeoff,
GR_Scram_G4_Squad=GR_Pack_Takeoff,
GR_Scram_G5_Squad=GR_Pack_Takeoff,
GR_Scram_G6_Squad=GR_Pack_Takeoff,
GR_Scram_G7_Squad=GR_Pack_Takeoff,

GR_Pack_Sq0_Home=GR_Pack_Takeoff,
GR_Pack_Sq1_Home=GR_Pack_Takeoff,
GR_Pack_Sq2_Home=GR_Pack_Takeoff,
GR_Pack_Sq3_Home=GR_Pack_Takeoff,
GR_Pack_Sq4_Home=GR_Pack_Takeoff,
GR_Pack_Sq5_Home=GR_Pack_Takeoff,
GR_Pack_Sq6_Home=GR_Pack_Takeoff,
GR_Pack_Sq7_Home=GR_Pack_Takeoff,
GR_BLUESKILLCONFIG=GR_Pack_Takeoff,
GR_REDSKILLCONFIG=GR_Pack_Takeoff,
GR_WPP_Rendevous=GR_Pack_Takeoff,
GR_WPP_Ingress=GR_Pack_Takeoff,
GR_WPP_Target=GR_Pack_Takeoff,
GR_WPP_Regroup=GR_Pack_Takeoff,
GR_WPP_Egress=GR_Pack_Takeoff,
GR_WPP_Disperse=GR_Pack_Takeoff,
GR_WPC_Rendevous=GR_Pack_Takeoff,
GR_WPC_Ingress=GR_Pack_Takeoff,
GR_WPC_Target=GR_Pack_Takeoff,
GR_WPC_Regroup=GR_Pack_Takeoff,
GR_WPC_Egress=GR_Pack_Takeoff,
GR_movecode=GR_Pack_Takeoff,
GR_FormType00=GR_Pack_Takeoff,
GR_FormType01=GR_Pack_Takeoff,
GR_FormType02=GR_Pack_Takeoff,
GR_TruckMoveCode=GR_Pack_Takeoff,
GR_WPC_Disperse=GR_Pack_Takeoff;



static	GlobalsInfo
GR_bluestrength = 	{"bluestrength" ,
						IDS_BLUESTRENGTH,	IDS_HELP_BLUESTRENGTH,
						&FlightSizeProcess},
GR_bluefighters = 	{"bluefighters",
									IDS_BLUEFIGHTERS,
									IDS_HELP_BLUEFIGHTERS,
									&FlightSizeProcess,
								},
GR_bluebombers = 	{"bluebombers",
									IDS_BLUEBOMBERS,
									IDS_HELP_BLUEBOMBERS,
									&FlightSizeProcess,
								},
GR_redstrength = 	{"redstrength",
									IDS_REDSTRENGTH,
									IDS_HELP_REDSTRENGTH,
									&FlightSizeProcess,
								},
GR_redfighters =    {"redfighters",
									IDS_REDFIGHTERS,
									IDS_HELP_REDFIGHTERS,
									&FlightSizeProcess,
								},
GR_redbombers =     {"redbombers",
									IDS_REDBOMBERS,
									IDS_HELP_REDBOMBERS,
									&FlightSizeProcess,
								},
GR_greenstrength =	{"greenstrength",
									IDS_GREENSTRENGTH,
									IDS_HELP_GREENSTRENGTH,
									&FlightSizeProcess,
								},
GR_PlyrFormSize =	{"PlyrFormSize",
									IDS_PLYRFORMSIZE,
									IDS_HELP_PLYRFORMSIZE,
									&FlightSizeProcess,
								},
GR_rndbluescouts =	{"rndbluescouts",
									IDS_RNDBLUESCOUTS,
									IDS_HELP_RNDBLUESCOUTS,
									&FlightSizeProcess,
								},
GR_PlyrWingSize =	{"PlyrWingSize",
									IDS_PLYRWINGSIZE,
									IDS_HELP_PLYRWINGSIZE,
									&FlightSizeProcess,
								},
GR_EnemyWingSize00 ={"EnemyWingSize0",
									IDS_ENEMYWINGSIZE00,
									IDS_HELP_ENEMYWINGSIZE00,
									&FlightSizeProcess,
},
GR_EnemyScoutType00={"EnemyScoutType00",
									IDS_ENEMYSCOUTTYPE00,
									IDS_HELP_ENEMYSCOUTTYPE00,
									&AcTypeProcess,
},
GR_EnemyChargeType00={"EnemyChargeType00",
									IDS_ENEMYCHARGETYPE00,
									IDS_HELP_ENEMYCHARGETYPE00,
									&AcTypeProcess,
},
GR_EnemyScoutType01 ={"EnemyScoutType01",
									IDS_ENEMYSCOUTTYPE01,
									IDS_HELP_ENEMYSCOUTTYPE01,
									&AcTypeProcess,
},
GR_EnemyChargeType01={"EnemyChargeType01",
									IDS_ENEMYCHARGETYPE01,
									IDS_HELP_ENEMYCHARGETYPE01,
									&AcTypeProcess,
},
GR_CampaignEnemyScoutType00 =
					{"CampaignEnemyScoutType00",
									IDS_CAMPAIGNENEMYSCOUTTYPE00,
									IDS_HELP_CAMPAIGNENEMYSCOUTTYPE00,
									&AcTypeProcess,
},
GR_CampaignEnemyChargeType00 =
					{"CampaignEnemyChargeType00",
									IDS_CAMPAIGNENEMYCHARGETYPE00,
									IDS_HELP_CAMPAIGNENEMYCHARGETYPE00,
									&AcTypeProcess,
},
GR_CampaignEnemyScoutType01 =
					{"CampaignEnemyScoutType01",
									IDS_CAMPAIGNENEMYSCOUTTYPE01,
									IDS_HELP_CAMPAIGNENEMYSCOUTTYPE01,
									&AcTypeProcess,
},
GR_CampaignEnemyChargeType01 =
					{"CampaignEnemyChargeType01",
									IDS_CAMPAIGNENEMYCHARGETYPE01,
									IDS_HELP_CAMPAIGNENEMYCHARGETYPE01,
									&AcTypeProcess,
},
GR_FriendlyChargeType00 =
					{"FriendlyChargeType00",
									IDS_FRIENDLYCHARGETYPE00,
									IDS_HELP_FRIENDLYCHARGETYPE00,
									&AcTypeProcess,
},
GR_CampaignFriendlyScoutType00 =
					{"CampaignFriendlyScoutType00",
									IDS_CAMPAIGNFRIENDLYSCOUTTYPE00,
									IDS_HELP_CAMPAIGNFRIENDLYSCOUTTYPE00,
									&AcTypeProcess,
},
GR_CampaignFriendlyChargeType00 =
					{"CampaignFriendlyChargeType00",
									IDS_CAMPAIGNFRIENDLYCHARGETYPE00,
									IDS_HELP_CAMPAIGNFRIENDLYCHARGETYPE00,
									&AcTypeProcess,
},
GR_FormSize00 =     {"FormSize00",
									IDS_FORMSIZE00,
									IDS_HELP_FORMSIZE00,
									&FlightSizeProcess,
},
GR_FormSize01 =     {"FormSize01",
									IDS_FORMSIZE01,
									IDS_HELP_FORMSIZE01,
									&FlightSizeProcess,
},
GR_FormSize02 =     {"FormSize02",
									IDS_FORMSIZE02,
									IDS_HELP_FORMSIZE02,
									&FlightSizeProcess,
},
GR_FormSize03 =     {"FormSize03",
									IDS_FORMSIZE03,
									IDS_HELP_FORMSIZE03,
									&FlightSizeProcess,
},
GR_AngleStepSize =  {"AngleStepSize",
									IDS_ANGLESTEPSIZE,
									IDS_HELP_ANGLESTEPSIZE,
									&IntProcess,
},
GR_HeightStepSize = {"HeightStepSize",
									IDS_HEIGHTSTEPSIZE,
									IDS_HELP_HEIGHTSTEPSIZE,
									&IntProcess,
},
GR_RangeStepSize =  {"RangeStepSize",
									IDS_RANGESTEPSIZE,
									IDS_HELP_RANGESTEPSIZE,
									&IntProcess,
},
GR_EncounterSize =  {"EncounterSize",
									IDS_ENCOUNTERSIZE,
									IDS_HELP_ENCOUNTERSIZE,
									&EncounterSizeProcess,
},
GR_ParentRand =     {"ParentRand",
									IDS_PARENTRAND,
									IDS_HELP_PARENTRAND,
									&IntProcess,
},
//GR_AngleSelect =    {"HeightSize",
//									IDS_HEIGHTSIZE,
//									IDS_HELP_HEIGHTSIZE,
//									&AltProcess,
//},
GR_HeightSize =     {"HeightSize",
									IDS_HEIGHTSIZE,
									IDS_HELP_HEIGHTSIZE,
									&AltProcess,
},
GR_RequiredNationality =
					{"RequiredNationality",
									IDS_REQUIREDNATIONALITY,
									IDS_HELP_REQUIREDNATIONALITY,
									&NatProcess,
},
GR_DesPitch =       {"DesPitch",
									IDS_DESPITCH,
									IDS_HELP_DESPITCH,
									&AnglesProcess,
},
GR_DesHdg =         {"DesHdg",
									IDS_DESHDG,
									IDS_HELP_DESHDG,
									&AnglesProcess,
},
GR_RandAngle =      {"RandAngle",
									IDS_RANDANGLE,
									IDS_HELP_RANDANGLE,
									&AnglesProcess,
},
GR_PS_1 =           {"PS_1",
									IDS_PS_1,
									IDS_HELP_PS_1,
									&PaintProcess,
},
GR_PS_2 =           {"PS_2",
									IDS_PS_2,
									IDS_HELP_PS_2,
									&PaintProcess,
},
GR_PS_3 =           {"PS_3",
									IDS_PS_3,
									IDS_HELP_PS_3,
									&PaintProcess,
},
GR_PS_4 =           {"PS_4",
									IDS_PS_4,
									IDS_HELP_PS_4,
									&PaintProcess,
},
GR_PS_5 =           {"PS_5",
									IDS_PS_5,
									IDS_HELP_PS_5,
									&PaintProcess,
},
GR_PS_6 =           {"PS_6",
									IDS_PS_6,
									IDS_HELP_PS_6,
									&PaintProcess,
},
GR_PS_7 =           {"PS_7",
									IDS_PS_7,
									IDS_HELP_PS_7,
									&PaintProcess,
},
GR_PS_8 =           {"PS_8",
									IDS_PS_8,
									IDS_HELP_PS_8,
									&PaintProcess,
};

//------------------------------------------------------------------------------
//	Variables that are declared here, but are modified/read nby the main game
//
GlobalsInfo
GR_TankShape =		{"TankShape",TEXT_TankShape,TEXT_TankShape,
									&ShapeProcess,NAT_RED},
GR_TroopShape =		{"TroopShape",TEXT_TroopShape,TEXT_TroopShape,
									&ShapeProcess,NAT_RED},
GR_GunShape =		{"GunShape",TEXT_GunShape,TEXT_GunShape,
									&ShapeProcess,NAT_RED},
GR_DefendBarageShape =		{"DefendBarageShape",TEXT_DefendBarageShape,TEXT_DefendBarageShape,
									&ShapeProcess,NAT_RED},
GR_Truck1Shape =		{"Truck1Shape",TEXT_Truck1Shape,TEXT_Truck1Shape,
									&ShapeProcess,NAT_RED},
GR_Truck2Shape =		{"Truck2Shape",TEXT_Truck2Shape,TEXT_Truck2Shape,
									&ShapeProcess,NAT_RED},
GR_TentsShape =		{"TentsShape",TEXT_TentsShape,TEXT_TentsShape,
									&ShapeProcess,NAT_RED},
GR_ParkedACShape =		{"ParkedACShape",TEXT_ParkedACShape,TEXT_ParkedACShape,
									&ShapeProcess,NAT_RED},
GR_NAT_ENEMY =		{"NAT_ENEMY",
									IDS_NAT_ENEMY,
									IDS_HELP_NAT_ENEMY,
									&HideProcess,
									NAT_RED,
},
GR_NAT_FRIEND =     {"NAT_FRIEND",
									IDS_NAT_FRIEND,
									IDS_HELP_NAT_FRIEND,
									&HideProcess,
									NAT_BLUE
};
static	GlobalsInfo
GR_amberstrength =	{"amberstrength",
									IDS_AMBERSTRENGTH,
									IDS_HELP_AMBERSTRENGTH,
									&FlightSizeProcess,
								},
GR_FriendlyScoutType00 =
					{"FriendlyScoutType00",
									IDS_FRIENDLYSCOUTTYPE00,
									IDS_HELP_FRIENDLYSCOUTTYPE00,
									&AcTypeProcess,
								},
//GR_Cam_ViewTarg =	{"Cam_ViewTarg",
//									IDS_CAM_VIEWTARG,
//									IDS_HELP_CAM_VIEWTARG,
//									&IntProcess,
//								},
//GR_Cam_ViewMode =	{"Cam_ViewMode",
//									IDS_CAM_VIEWMODE,
//									IDS_HELP_CAM_VIEWMODE,
//									&IntProcess,
//								},
//GR_Cam_CutType =	{"Cam_CutType",
//									IDS_CAM_CUTTYPE,
//									IDS_HELP_CAM_CUTTYPE,
//									&IntProcess,
//								},
//GR_Cam_PanRate =	{"Cam_PanRate",
//									IDS_CAM_PANRATE,
//									IDS_HELP_CAM_PANRATE,
//									&IntProcess,
//								},
//GR_Cam_Zoom =		{"Cam_Zoom",
//									IDS_CAM_ZOOM,
//									IDS_HELP_CAM_ZOOM,
//									&IntProcess,
//								},
//GR_Cam_Heading =	{"Cam_Heading",
//									IDS_CAM_HEADING,
//									IDS_HELP_CAM_HEADING,
//									&AnglesProcess,
//								},
//GR_Cam_Pitch =		{"Cam_Pitch",
//									IDS_CAM_PITCH,
//									IDS_HELP_CAM_PITCH,
//									&AnglesProcess,
//								},
//GR_Cam_RollRate =	{"Cam_RollRate",
//									IDS_CAM_ROLLRATE,
//									IDS_HELP_CAM_ROLLRATE,
//									&IntProcess,
//								},
//GR_Cam_RotateRate =	{"Cam_RotateRate",
//									IDS_CAM_ROLLRATE,
//									IDS_HELP_CAM_ROLLRATE,
//									&IntProcess,
//								},
//GR_AutoBulletCount ={"AutoBulletCount",
//									IDS_AUTOBULLETCOUNT,
//									IDS_HELP_AUTOBULLETCOUNT,
//									&IntProcess,
//								},
//GR_UIDDeathItem =	{"UIDDeathItem",
//									IDS_UIDDEATHITEM,
//									IDS_HELP_UIDDEATHITEM,
//									&UIDProcess,
//								},
//GR_deathtype =		{"deathtype",
//									IDS_DEATHTYPE,
//									IDS_HELP_DEATHTYPE,
//									&IntProcess,
//								},
//GR_Cam_CamItem =	{"Cam_CamItem",
//									IDS_CAM_CAMITEM,
//									IDS_HELP_CAM_CAMITEM,
//									&IntProcess,
//								},
//GR_Cam_TrgtItem =	{"Cam_TrgtItem",
//									IDS_CAM_TRGTITEM,
//									IDS_HELP_CAM_TRGTITEM,
//									&UIDProcess,
//								},
//GR_Cam_PitchRate =	{"Cam_PitchRate",
//									IDS_CAM_PITCHRATE,
//									IDS_HELP_CAM_PITCHRATE,
//									&IntProcess,
//								},
GR_EnemyScoutHomeBase =
					{"EnemyScoutHomeBase",
									IDS_ENEMYSCOUTHOMEBASE,
									IDS_HELP_ENEMYSCOUTHOMEBASE,
									&HBProcess,
								},
GR_EnemyChargeHomeBase =
					{"EnemyChargeHomeBase",
									IDS_FRIENDLYCHARGEHOMEBASE,
									IDS_HELP_FRIENDLYCHARGEHOMEBASE,
									&HBProcess,
								},
GR_FriendlyScoutHomeBase =
					{"FriendlyScoutHomeBase",
									IDS_FRIENDLYSCOUTHOMEBASE,
									IDS_HELP_FRIENDLYSCOUTHOMEBASE,
									&HBProcess,
								},
GR_FriendlyChargeHomeBase =
					{"FriendlyChargeHomeBase",
									IDS_FRIENDLYCHARGEHOMEBASE,
									IDS_HELP_FRIENDLYCHARGEHOMEBASE,
									&HBProcess,
								},
GR_FriendlyObjective =
					{"FriendlyObjective",
									IDS_FRIENDLYOBJECTIVE,
									IDS_HELP_FRIENDLYOBJECTIVE,
									&TargetProcess,
								},
GR_EnemyObjective =	{"EnemyObjective",
									IDS_ENEMYOBJECTIVE,
									IDS_HELP_ENEMYOBJECTIVE,
									&TargetProcess,
								},
GR_EnemyScoutMorale={"EnemyScoutMorale",
									IDS_ENEMYSCOUTMORALE,
									IDS_HELP_ENEMYSCOUTMORALE,
									&MoraleProcess,
								},
GR_FriendlyScoutMorale =
					{"FriendlyScoutMorale",
									IDS_FRIENDLYSCOUTMORALE,
									IDS_HELP_FRIENDLYSCOUTMORALE,
									&MoraleProcess,
								},
GR_EnemyScoutCharacter =
					{"EnemyScoutCharacter",
									IDS_ENEMYSCOUTCHARACTER,
									IDS_HELP_ENEMYSCOUTCHARACTER,
									&CharProcess,
								},
GR_EnemyScoutTactician =
					{"EnemyScoutTactician",
									IDS_ENEMYSCOUTTACTICIAN,
									IDS_HELP_ENEMYSCOUTTACTICIAN,
									&CharProcess,
								},
GR_EnemyScoutMrAverage =
					{"EnemyScoutMrAverage",
									IDS_ENEMYSCOUTMRAVERAGE,
									IDS_HELP_ENEMYSCOUTMRAVERAGE,
									&CharProcess,
								},
GR_EnemyScoutCavalier =
					{"EnemyScoutCavalier",
									IDS_ENEMYSCOUTCAVALIER,
									IDS_HELP_ENEMYSCOUTCAVALIER,
									&CharProcess,
								},
GR_FriendlyScoutCharacter =
					{"FriendlyScoutCharacter",
									IDS_FRIENDLYSCOUTCHARACTER,
									IDS_HELP_FRIENDLYSCOUTCHARACTER,
									&CharProcess,
								},
GR_FriendlyScoutTactician =
					{"FriendlyScoutTactician",
									IDS_FRIENDLYSCOUTTACTICIAN,
									IDS_HELP_FRIENDLYSCOUTTACTICIAN,
									&CharProcess,
								},
GR_FriendlyScoutMrAverage =
					{"FriendlyScoutMrAverage",
									IDS_FRIENDLYSCOUTMRAVERAGE,
									IDS_HELP_FRIENDLYSCOUTMRAVERAGE,
									&CharProcess,
								},
GR_FriendlyScoutCavalier =
					{"FriendlyScoutCavalier",
									IDS_FRIENDLYSCOUTCAVALIER,
									IDS_HELP_FRIENDLYSCOUTCAVALIER,
									&CharProcess,
								},
GR_FriendlyChargeCharacter =
					{"FriendlyChargeCharacter",
									IDS_FRIENDLYCHARGECHARACTER,
									IDS_HELP_FRIENDLYCHARGECHARACTER,
									&CharProcess,
								},
GR_FriendlyChargeMorale =
					{"FriendlyChargeMorale",
									IDS_FRIENDLYCHARGEMORALE,
									IDS_HELP_FRIENDLYCHARGEMORALE,
									&MoraleProcess,
								},
GR_EnemyChargeCharacter =
					{"EnemyChargeCharacter",
									IDS_ENEMYCHARGECHARACTER,
									IDS_HELP_ENEMYCHARGECHARACTER,
									&CharProcess,
								},
GR_EnemyChargeMorale =
					{"EnemyChargeMorale",
									IDS_ENEMYCHARGEMORALE,
									IDS_HELP_ENEMYCHARGEMORALE,
									&MoraleProcess,
								},
GR_FriendlyScoutSkillMin =
					{"FriendlyScoutSkillMin",
									IDS_FRIENDLYSCOUTSKILLMIN,
									IDS_HELP_FRIENDLYSCOUTSKILLMIN,
									&SkillProcess,
								},
GR_FriendlyChargeSkillMin =
					{"FriendlyChargeSkillMin",
									IDS_FRIENDLYCHARGESKILLMIN,
									IDS_HELP_FRIENDLYCHARGESKILLMIN,
									&SkillProcess,
								},
GR_EnemyScoutSkillMin =
					{"EnemyScoutSkillMin",
									IDS_ENEMYSCOUTSKILLMIN,
									IDS_HELP_ENEMYSCOUTSKILLMIN,
									&SkillProcess,
								},
GR_EnemyChargeSkillMin =
					{"EnemyChargeSkillMin",
									IDS_ENEMYCHARGESKILLMIN,
									IDS_HELP_ENEMYCHARGESKILLMIN,
									&SkillProcess,
								},
GR_FriendlyScoutSkillMax =
					{"FriendlyScoutSkillMax",
									IDS_FRIENDLYSCOUTSKILLMAX,
									IDS_HELP_FRIENDLYSCOUTSKILLMAX,
									&SkillProcess,
								},
GR_FriendlyChargeSkillMax =
					{"FriendlyChargeSkillMax",
									IDS_FRIENDLYCHARGESKILLMAX,
									IDS_HELP_FRIENDLYCHARGESKILLMAX,
									&SkillProcess,
								},
GR_EnemyScoutSkillMax =
					{"EnemyScoutSkillMax",
									IDS_ENEMYSCOUTSKILLMAX,
									IDS_HELP_ENEMYSCOUTSKILLMAX,
									&SkillProcess,
								},
GR_EnemyChargeSkillMax =
					{"EnemyChargeSkillMax",
									IDS_ENEMYCHARGESKILLMAX,
									IDS_HELP_ENEMYCHARGESKILLMAX,
									&SkillProcess,
								},
GR_GlobalSkillMin =	{"GlobalSkillMin",
									IDS_GLOBALSKILLMIN,
									IDS_HELP_GLOBALSKILLMIN,
									&SkillProcess,
								},
GR_GlobalSkillMax =	{"GlobalSkillMax",
									IDS_GLOBALSKILLMAX,
									IDS_HELP_GLOBALSKILLMAX,
									&SkillProcess,
								},
GR_EnemyScoutSquad ={"EnemyScoutSquad",
									IDS_ENEMYSCOUTSQUAD,
									IDS_HELP_ENEMYSCOUTSQUAD,
									&HideProcess,
									0
								},
GR_FriendlyScoutSquad =
					{"FriendlyScoutSquad",
									IDS_FRIENDLYSCOUTSQUAD,
									IDS_HELP_FRIENDLYSCOUTSQUAD,
									&HideProcess,
									0
								},
GR_EnemyChargeSquad =
					{"EnemyChargeSquad",
									IDS_ENEMYCHARGESQUAD,
									IDS_HELP_ENEMYCHARGESQUAD,
									&HideProcess,
									0
								},
GR_FriendlyChargeSquad =
					{"FriendlyChargeSquad",
									IDS_FRIENDLYCHARGESQUAD,
									IDS_HELP_FRIENDLYCHARGESQUAD,
									&HideProcess,
									0
								};
GlobalsInfo
GR_MainObjective =	{"MainObjective",
									IDS_MAINOBJECTIVE,
									IDS_HELP_MAINOBJECTIVE,
									&HideProcess,
									0
								},
GR_SubObjective =	{"SubObjective",
									IDS_SUBOBJECTIVE,
									IDS_HELP_SUBOBJECTIVE,
									&HideProcess,
									0
								},
GR_WP1 =			{"WP1",
									IDS_WP1,
									IDS_HELP_WP1,
									&HideProcess,
									0
								},
GR_WP2 =			{"WP2",
									IDS_WP2,
									IDS_HELP_WP2,
									&HideProcess,
									0
								},
GR_WP3 =			{"WP3",
									IDS_WP3,
									IDS_HELP_WP3,
									&HideProcess,
									0
								};
static GlobalsInfo
GR_EnemyHomeBase =	{"EnemyHomeBase",
									IDS_ENEMYHOMEBASE,
									IDS_HELP_ENEMYHOMEBASE,
									&HBProcess,
								},
GR_FriendHomeBase =	{"FriendHomeBase",
									IDS_FRIENDHOMEBASE,
									IDS_HELP_FRIENDHOMEBASE,
									&HideProcess,
									0
								},
GR_CPP =			{"CPP",
									IDS_CPP,
									IDS_HELP_CPP,
									&HideProcess,
									0
								},
GR_CWP =			{"CWP",
									IDS_CWP,
									IDS_HELP_CWP,
									&HideProcess,
									0
								},
GR_ConvoyCount =	{"ConvoyCount",
									IDS_CONVOYCOUNT,
									IDS_HELP_CONVOYCOUNT,
									&IntProcess,
								},
//GlobalsInfo		GR_ConvoyUid =
//								{
//									IDS_BLUESTRENGTH,
//									IDS_HELP_BLUESTRENGTH,
//									&IntProcess,
//								};
//GlobalsInfo		GR_GunSite =
//								{
//									IDS_BLUESTRENGTH,
//									IDS_HELP_BLUESTRENGTH,
//									&IntProcess,
//								};
//GlobalsInfo		GR_AAASite =
//								{
//									IDS_BLUEFIGHTERS,
//									IDS_HELP_BLUEFIGHTERS,
//									&IntProcess,
//								},
GR_MainPosX =		{"MainPosX",
									IDS_MAINPOSX,
									IDS_HELP_MAINPOSX,
									&IntProcess,
								},
GR_MainPosY =		{"MainPosY",
									IDS_MAINPOSY,
									IDS_HELP_MAINPOSY,
									&IntProcess,
								},
GR_MainPosZ =		{"MainPosZ",
									IDS_MAINPOSZ,
									IDS_HELP_MAINPOSZ,
									&IntProcess,
								},
GR_SubPosX =		{"SubPosX",
									IDS_SUBPOSX,
									IDS_HELP_SUBPOSX,
									&IntProcess,
								},
GR_SubPosY =		{"SubPosY",
									IDS_SUBPOSY,
									IDS_HELP_SUBPOSY,
									&IntProcess,
								},
GR_SubPosZ =		{"SubPos",
									IDS_SUBPOSZ,
									IDS_HELP_SUBPOSZ,
									&IntProcess,
								},
GR_CloudBase =		{"CloudBase",
									IDS_CLOUDBASE,
									IDS_HELP_CLOUDBASE,
									&HideProcess,
									5000
								},
//GR_firstobject =		{"FirstObject",
//									IDS_CLOUDBASE,
//									IDS_HELP_CLOUDBASE,
//									&HideProcess,
//									5000
//								},
GR_Quit3DNow =		{"OkToQuit3DNow",
									IDS_OKTOQUIT3DNOW,
									IDS_HELP_OKTOQUIT3DNOW,
									&IntProcess,
								},
GR_OkToQuit3DNow =	{"Quit3DNow",
									IDS_QUIT3DNOW,
									IDS_HELP_QUIT3DNOW,
									&IntProcess,
								},
GR_MainAction =		{"MainAction",
									IDS_MAINACTION,
									IDS_HELP_MAINACTION,
									&ActionProcess,
								},
GR_SubAction =		{"SubAction",
									IDS_SubAction,
									IDS_HELP_SubAction,
									&ActionProcess,
								}
//,
//GR_H2H_PT1 =		{"H2H_PT1",
//									IDS_H2H_PT1,
//									IDS_HELP_H2H_PT1,
//									&AcTypeProcess,
//								},
//GR_H2H_PT2 =		{"H2H_PT2",
//									IDS_H2H_PT2,
//									IDS_HELP_H2H_PT2,
//									&AcTypeProcess,
//								},
//GR_H2H_PT3 =		{"H2H_PT3",
//									IDS_H2H_PT3,
//									IDS_HELP_H2H_PT3,
//									&AcTypeProcess,
//								},
//GR_H2H_PT4 =		{"H2H_PT4",
//									IDS_H2H_PT4,
//									IDS_HELP_H2H_PT4,
//									&AcTypeProcess,
//								},
//GR_H2H_PT5 =		{"H2H_PT5",
//									IDS_H2H_PT5,
//									IDS_HELP_H2H_PT5,
//									&AcTypeProcess,
//								},
//GR_H2H_PT6 =		{"H2H_PT6",
//									IDS_H2H_PT6,
//									IDS_HELP_H2H_PT6,
//									&AcTypeProcess,
//								},
//GR_H2H_PT7 =		{"H2H_PT7",
//									IDS_H2H_PT7,
//									IDS_HELP_H2H_PT7,
//									&AcTypeProcess,
//								},
//GR_H2H_PT8 =		{"H2H_PT8",
//									IDS_H2H_PT8,
//									IDS_HELP_H2H_PT8,
//									&AcTypeProcess,
//								};
;

//------------------------------------------------------------------------------
//	Variables that are declared here, but are modified/read nby the main game
//	Much rteduced list. Mark has been adding to wrong one!
//////ULong
//////		GR_amberstrength=1,			//comms
//////		GR_NAT_FRIEND=0,			//set in uigen
//////		GR_FriendlyScoutType00=0,	//Xset in state3d							//JIM 09Apr96
//////		GR_CPP=0,					//set in events					//MS 21Jun96
//////		GR_CWP=0,					//set in events					//MS 21Jun96
//////		GR_NAT_ENEMY=0,             //set in uigen
//////		GR_MainObjective=0,			//set in uigen							//MS 21Jun96
//////		GR_SubObjective=0,			//set in uigen							//MS 21Jun96
//////		GR_WP1=0,					//set in uigen					//MS 21Jun96
//////		GR_WP2=0,					//set in uigen					//MS 21Jun96
//////		GR_WP3=0,					//set in uigen					//MS 21Jun96
//////		GR_MainPosX,                //Xset in tank
//////		GR_MainPosY,				//Xset in tank
//////		GR_MainPosZ,                //Xset in tank
//////		GR_SubPosX,                 //Xset in tank
//////		GR_SubPosY,                 //Xset in tank
//////		GR_SubPosZ,                 //Xset in tank
//////		GR_MainAction,		//Xset in tank//RDH 05Dec96
//////		GR_SubAction,		//Xset in tank//RDH 05Dec96
//////		GR_ConvoyCount,		//Xset in tank									//RDH 09Aug96
//////		GR_CloudBase,				 //set in UIGEN							//MS 21Nov96

//////		GR_Quit3DNow=0,				//read in scramble
//////		GR_OkToQuit3DNow=0,			//read in scramble
//////		GR_FriendHomeBase=0,		 //set in UIGEN - SHOULD BE OVERRIDABLE!										//MS 21Jun96
//////		GR_GlobalSkillMin=0,		 //defaulted in UIGEN							//MS 30Aug96
//////		GR_GlobalSkillMax=0,									//MS 30Aug96
//////		GR_H2H_PT1,GR_H2H_PT2,GR_H2H_PT3,GR_H2H_PT4,     	//comms
//////		GR_H2H_PT5,GR_H2H_PT6,GR_H2H_PT7,GR_H2H_PT8		;

//------------------------------------------------------------------------------
//  References to variables in the main game
//
//#define	myname	yourname,bits,shift

static GlobalsInfo
GR_Sample_Play =	{"Sample_Play",
									IDS_SAMPLE_PLAY,
									IDS_HELP_SAMPLE_PLAY,
									&IntProcess,
								},
GR_Sample_Volume =	{"Sample_Volume",
									IDS_SAMPLE_VOLUME,
									IDS_HELP_SAMPLE_VOLUME,
									&IntProcess,
								},
GR_Sample_Pan =		{"Sample_Pan",
									IDS_SAMPLE_PAN,
									IDS_HELP_SAMPLE_PAN,
									&IntProcess,
								};

//------------------------------------------------------------------------------
//Make the actual list:
//
#include	"bfrefs.g"


//------------------------------------------------------------------------------
//Code to access
//

void	Persons2::SetLoc(int	locnum,int value)
{
	((GlobalsInfo*)BFieldGlobalTable[locnum].reference)->value=value;

}
int&	Persons2::GetLoc(int	locnum)
{
	return	((GlobalsInfo*)BFieldGlobalTable[locnum].reference)->value;
}




