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
//Filename	missinit.cpp
//System
//Author	 R. Hyde
//Date		Thu 7 Dec 1995
//Description
//------------------------------------------------------------------------------
#include	"dosdefs.h"											//DAW 29Feb96
#define F_SOUNDS												//DAW 05Aug96
#define F_COMMON
#include	"files.g"		//NON-GRAPHICS FILES				//JIM 14May96
//DeadCode JIM 30Apr96 #include	"miss_man.h"										//DAW 17Jan96
//#include	"ui.h"
#include	"uniqueid.h"
#include	"text.h"												//JIM 30Apr96
#include	"briefing.h"												//JIM 30Apr96

#include	"missman2.h"	//special double-include
#undef	MISSMAN2_Included	//special double-include
#include	"missman2.h"	//special double-include
#include	"mytime.h"
#include	"mymath.h"											//RDH 04Jan96
#include	"ranges.h"											//RDH 04Jan96
#include	"node.h"
#include	"ENUMBITS.M"
#include "savegame.h"
#include "persons2.h"
Bool	beentomap;												//RDH 29Nov96
MATHABLE	(Debrief::Types);
MATHABLE	(SquadSelect);

//enum repeated here because one in missman2.h wasn't accessed by this file?
enum					{MAX_FLIGHT_NUM = 4,MAX_AC_IN_FLIGHT_NUM = 4};

enum	InternalSkillType
//steps of 13
//DEADCODE JIM 14/07/99 {	/* 0==>  0*/	ISKILL_NOVICE = 49,	ISKILL_NOVICE1=62,	ISKILL_NOVICE2=71,
//DEADCODE JIM 14/07/99 	/* 3==> 48*/	ISKILL_POOR = 84,	ISKILL_POOR1 = 97,	ISKILL_POOR2 = 110,
//DEADCODE JIM 14/07/99 	/* 6==> 96*/	ISKILL_REGULAR=123,	ISKILL_REGULAR1=136,	ISKILL_REGULAR2=149,
//DEADCODE JIM 14/07/99 	/* 9==>144*/	ISKILL_VETERAN=162,	ISKILL_VETERAN1=175,	ISKILL_VETERAN2=188,
//DEADCODE JIM 14/07/99 	/*12==>192*/	ISKILL_ACE=201,		ISKILL_ACE1=214,	ISKILL_ACE2=227,
//DEADCODE JIM 14/07/99 	/*15==>240*/	ISKILL_HERO=240,	ISKILL_MAX=255,		ISKILL_align=255};
//DeadCode DAW 15Jul99 //steps of 12
//DeadCode DAW 15Jul99 {	/* 0==>  0*/	ISKILL_NOVICE = 64,	ISKILL_NOVICE1=72,	ISKILL_NOVICE2=84,
//DeadCode DAW 15Jul99 	/* 3==> 48*/	ISKILL_POOR = 96,	ISKILL_POOR1 = 108,	ISKILL_POOR2 = 120,
//DeadCode DAW 15Jul99 	/* 6==> 96*/	ISKILL_REGULAR=132,	ISKILL_REGULAR1=144,	ISKILL_REGULAR2=156,
//DeadCode DAW 15Jul99 	/* 9==>144*/	ISKILL_VETERAN=168,	ISKILL_VETERAN1=180,	ISKILL_VETERAN2=192,
//DeadCode DAW 15Jul99 	/*12==>192*/	ISKILL_ACE=204,		ISKILL_ACE1=216,	ISKILL_ACE2=228,
//DeadCode DAW 15Jul99 	/*15==>240*/	ISKILL_HERO=240,	ISKILL_MAX=255,		ISKILL_align=255};

//steps of 11
{	/* 0==>  0*/	ISKILL_NOVICE = 75,	ISKILL_NOVICE1=86,	ISKILL_NOVICE2=97,
	/* 3==> 48*/	ISKILL_POOR = 108,	ISKILL_POOR1 = 119,	ISKILL_POOR2 = 130,
	/* 6==> 96*/	ISKILL_REGULAR=141,	ISKILL_REGULAR1=152,	ISKILL_REGULAR2=163,
	/* 9==>144*/	ISKILL_VETERAN=174,	ISKILL_VETERAN1=185,	ISKILL_VETERAN2=196,
	/*12==>192*/	ISKILL_ACE=207,		ISKILL_ACE1=218,	ISKILL_ACE2=229,
	/*15==>240*/	ISKILL_HERO=240,	ISKILL_MAX=255,		ISKILL_align=255};


//steps of 10
//DEADCODE JIM 14/07/99 {	/* 0==>  0*/	ISKILL_NOVICE = 90,	ISKILL_NOVICE1=100,	ISKILL_NOVICE2=110,
//DEADCODE JIM 14/07/99 	/* 3==> 48*/	ISKILL_POOR = 120,	ISKILL_POOR1 = 130,	ISKILL_POOR2 = 140,
//DEADCODE JIM 14/07/99 	/* 6==> 96*/	ISKILL_REGULAR=150,	ISKILL_REGULAR1=160,	ISKILL_REGULAR2=170,
//DEADCODE JIM 14/07/99 	/* 9==>144*/	ISKILL_VETERAN=180,	ISKILL_VETERAN1=190,	ISKILL_VETERAN2=200,
//DEADCODE JIM 14/07/99 	/*12==>192*/	ISKILL_ACE=210,		ISKILL_ACE1=220,	ISKILL_ACE2=230,
//DEADCODE JIM 14/07/99 	/*15==>240*/	ISKILL_HERO=240,	ISKILL_MAX=255,		ISKILL_align=255};

#define DO_SKILL(flyskill,combskill,flypot,combpot) \
	flyskill##combskill##flypot##combpot=\
	(I##flyskill<<HSflyingskill)			\
	+(I##combskill<<HScombatskill)			\
	+(flypot<<(HSflyingpotential+HStoskill))		\
	+(combpot<<(HScombatpotential+HStoskill))


enum	HidSkills
{
	DO_SKILL(SKILL_REGULAR1,		SKILL_POOR2,		POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_VETERAN2,	SKILL_REGULAR1,		POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_NOVICE2,		SKILL_NOVICE,		POTENTIAL_GOOD,		POTENTIAL_POOR),
	DO_SKILL(SKILL_POOR1,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYPOOR),
	DO_SKILL(SKILL_REGULAR,	SKILL_POOR,		POTENTIAL_VERYGOOD,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_ACE,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_EXCELLENT),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_MAX,		POTENTIAL_GOOD,		POTENTIAL_MAX),
	DO_SKILL(SKILL_VETERAN,		SKILL_POOR,	POTENTIAL_MAX,		POTENTIAL_REGULAR),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_POOR,	SKILL_POOR,		POTENTIAL_GOOD,		POTENTIAL_POOR),
	DO_SKILL(SKILL_POOR,	SKILL_ACE,		POTENTIAL_REGULAR,		POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_POOR,		SKILL_NOVICE2,	POTENTIAL_POOR,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_POOR2,	SKILL_POOR,		POTENTIAL_REGULAR,	POTENTIAL_EXCELLENT),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,	POTENTIAL_EXCELLENT),
//TEMPCODE MS 28/04/99 	DO_SKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_NOVICE,	SKILL_POOR,		POTENTIAL_VERYPOOR,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,	POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR2,		SKILL_POOR1,	POTENTIAL_VERYGOOD,	POTENTIAL_REGULAR),
	DO_SKILL(SKILL_REGULAR,	SKILL_NOVICE,	POTENTIAL_GOOD,		POTENTIAL_POOR),
	DO_SKILL(SKILL_ACE,		SKILL_VETERAN,		POTENTIAL_MAX,		POTENTIAL_EXCELLENT),
	DO_SKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR2,		SKILL_POOR,		POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_ACE,	SKILL_POOR1,		POTENTIAL_MAX,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_VETERAN1,		POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_POOR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_NOVICE,	SKILL_REGULAR,	POTENTIAL_VERYPOOR,	POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_GOOD,		POTENTIAL_MAX),
	DO_SKILL(SKILL_ACE,		SKILL_NOVICE,	POTENTIAL_EXCELLENT,	POTENTIAL_POOR),
	DO_SKILL(SKILL_REGULAR,	SKILL_NOVICE,	POTENTIAL_EXCELLENT,POTENTIAL_POOR),
	DO_SKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_REGULAR,		POTENTIAL_EXCELLENT),
	DO_SKILL(SKILL_NOVICE,	SKILL_POOR2,		POTENTIAL_VERYPOOR,	POTENTIAL_REGULAR),
	DO_SKILL(SKILL_ACE,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
//TEMPCODE MS 28/04/99 	DO_SKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_GOOD,	POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR1,	POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_POOR,		POTENTIAL_VERYGOOD,		POTENTIAL_REGULAR),
	DO_SKILL(SKILL_ACE,		SKILL_POOR,		POTENTIAL_MAX,	POTENTIAL_VERYGOOD),
//TEMPCODE MS 28/04/99 	DO_SKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_MAX,		SKILL_POOR2,		POTENTIAL_MAX,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_POOR,	POTENTIAL_EXCELLENT,POTENTIAL_REGULAR),
	DO_SKILL(SKILL_ACE,		SKILL_REGULAR,	POTENTIAL_EXCELLENT,	POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_POOR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_VETERAN,		POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_POOR,		POTENTIAL_GOOD,	POTENTIAL_POOR),
	DO_SKILL(SKILL_REGULAR2,		SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_ACE,		SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
//TEMPCODE MS 28/04/99 	DO_SKILL(SKILL_REGULAR,	SKILL_POOR,		POTENTIAL_EXCELLENT,POTENTIAL_REGULAR),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_MAX,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_NOVICE,		SKILL_POOR1,	POTENTIAL_VERYPOOR,	POTENTIAL_REGULAR),
	DO_SKILL(SKILL_ACE1,	SKILL_NOVICE,		POTENTIAL_MAX,	POTENTIAL_VERYPOOR),
	DO_SKILL(SKILL_VETERAN,		SKILL_POOR,	POTENTIAL_VERYGOOD,		POTENTIAL_POOR),
	DO_SKILL(SKILL_POOR2,	SKILL_REGULAR,	POTENTIAL_VERYPOOR,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_ACE,		SKILL_ACE,		POTENTIAL_MAX,		POTENTIAL_EXCELLENT),
//TEMPCODE MS 28/04/99 	DO_SKILL(SKILL_REGULAR2,		SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR2,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_POOR2,		POTENTIAL_VERYGOOD,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_EXCELLENT,POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_VERYGOOD,	POTENTIAL_EXCELLENT),
//TEMPCODE MS 28/04/99 	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_NOVICE1,		SKILL_POOR,		POTENTIAL_POOR,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_VERYGOOD,	POTENTIAL_MAX),
//TEMPCODE MS 28/04/99 	DO_SKILL(SKILL_NOVICE,		SKILL_POOR1,	POTENTIAL_VERYPOOR,	POTENTIAL_REGULAR),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_GOOD),
//TEMPCODE MS 28/04/99 	DO_SKILL(SKILL_REGULAR,	SKILL_POOR,		POTENTIAL_VERYGOOD,	POTENTIAL_REGULAR),
	DO_SKILL(SKILL_POOR,		SKILL_POOR1,		POTENTIAL_POOR,	POTENTIAL_REGULAR),
	DO_SKILL(SKILL_POOR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_MAX),
	DO_SKILL(SKILL_NOVICE1,		SKILL_REGULAR,	POTENTIAL_POOR,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_NOVICE,		SKILL_REGULAR,	POTENTIAL_POOR,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_POOR1,		SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
//TEMPCODE MS 28/04/99 	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_EXCELLENT),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR1,	POTENTIAL_EXCELLENT,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,	SKILL_NOVICE2,		POTENTIAL_VERYGOOD,	POTENTIAL_REGULAR),
	DO_SKILL(SKILL_NOVICE,	SKILL_VETERAN,		POTENTIAL_VERYPOOR,	POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_POOR,		SKILL_REGULAR,	POTENTIAL_POOR,		POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_REGULAR,		POTENTIAL_MAX),
	DO_SKILL(SKILL_ACE,		SKILL_VETERAN,	POTENTIAL_EXCELLENT,	POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_REGULAR),
	DO_SKILL(SKILL_NOVICE,	SKILL_POOR2,		POTENTIAL_MAX,	POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR,	SKILL_POOR,		POTENTIAL_VERYGOOD,		POTENTIAL_MAX),
	DO_SKILL(SKILL_MAX,		SKILL_POOR,		POTENTIAL_MAX,		POTENTIAL_GOOD),
	DO_SKILL(SKILL_NOVICE,		SKILL_POOR1,	POTENTIAL_MAX,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_ACE1,	SKILL_REGULAR,		POTENTIAL_MAX,	POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_POOR,		SKILL_REGULAR,		POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_REGULAR,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR,	SKILL_VETERAN,		POTENTIAL_REGULAR,	POTENTIAL_VERYGOOD),
	DO_SKILL(SKILL_NOVICE2,		SKILL_NOVICE,		POTENTIAL_GOOD,		POTENTIAL_MAX),
	DO_SKILL(SKILL_ACE1,	SKILL_ACE,		POTENTIAL_MAX,	POTENTIAL_MAX),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYPOOR),
	DO_SKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_REGULAR),
	DO_SKILL(SKILL_ACE,		SKILL_NOVICE,	POTENTIAL_EXCELLENT,	POTENTIAL_GOOD),
	DO_SKILL(SKILL_REGULAR,SKILL_REGULAR,POTENTIAL_VERYGOOD,POTENTIAL_REGULAR),
	DO_SKILL(SKILL_HERO,		SKILL_HERO,		POTENTIAL_MAX,	POTENTIAL_MAX),
	DO_SKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_VERYPOOR),
	DO_SKILL(SKILL_VETERAN,		SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_REGULAR),
	DO_SKILL(SKILL_ACE,		SKILL_HERO,		POTENTIAL_MAX,	POTENTIAL_MAX),
	DO_SKILL(SKILL_HERO,		SKILL_ACE2,	POTENTIAL_MAX,	POTENTIAL_MAX),
	DO_SKILL(SKILL_HERO,	SKILL_VETERAN,	POTENTIAL_MAX,	POTENTIAL_MAX),
	DO_SKILL(SKILL_MAX,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_REGULAR)
};

#define	NEWSKILL(flyskill,combskill,flypot,combpot)	HideSkills(flyskill##combskill##flypot##combpot)

startinst(CampaignPackages, CampaignF80_Def)
	/*garbage*/		sizeof(CampaignPackages),
	/*introsmack*/		FIL_SMACK_CAMP1INTRO,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_AfBlTaegu,							//MS 06Apr99
	/*playertakeoff*/	UID_AfBlTaegu,							//MS 06Apr99
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	JUN25th1950,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	JUN25th1950,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	JUN25th1950,
	/*lastdate*/								JUL19th1950,

	/*currtime*/		AFTERNOONPERIODSTART,				//can only be the start time
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		MORALE_GOOD,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",
	/*front*/				{UID_SdBlPyongtaek,UID_SdRdWonju,UID_StKangnung},//MS 06Apr99

	/*camp_win_anim*/	 FIL_SMACK_CAMP1GOOD,
	/*camp_lost_anim*/	 FIL_SMACK_CAMP5LOSE,
	{	
//the following order of squadrons is assumed in the ui, rdh 9/8/98
	{/*F86squad*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//0,//TEXT_4FIG,
		/*airfield*/						27,	//TAEGU			//MS 02Jun99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					816,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},
	{/*F86sq B*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//0,//TEXT_4FIG,
		/*airfield*/						25,	//KUNSAN		//MS 02Jun99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					416,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F80squad*/
		/*actype*/							PT_F80,	
		/*name*/							0,//0,//TEXT_27FEG,
		/*airfield*/						27,	//TAEGU			//MS 13Apr99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					716,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JUN25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F84squad*/
		/*actype*/							PT_F84,	
		/*name*/							0,//0,//TEXT_8FBG,
		/*airfield*/						30,	//POHANG		//MS 02Jun99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					616,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F51squad*/
		/*actype*/							PT_F51,	
		/*name*/							0,//0,//TEXT_35FIG,
		/*airfield*/						28,	//TaeguW		//MS 02Jun99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					516,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	}


	},

	{	 //type,colour,text,date				avail,tloss,dloss,MAX skill
		{PT_MIG15,2,0,JUN25th1950,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_BOMBERS1},
		{PT_MIG15,3,0,JUN25th1950,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_BOMBERS1},
		{PT_YAK,0,0,JUL3rd1950,	32,0,0,	SKILL_REGULAR,		MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},//MS 24Jun99
		{PT_YAK,0,0,JUL8th1950,	32,0,0,	SKILL_VETERAN,		MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},//MS 24Jun99
		{PT_MIG15,4,0,JUL19th1950,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_WAITWEAK},
		{PT_MIG15,5,0,JUL19th1950,	0,0,0,	SKILL_REGULAR,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_CUTWEAK},
		{PT_MIG15,6,0,JUL19th1950,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_ENDRUNDECOY},
		{PT_MIG15,7,0,JUL19th1950,	0,0,0,	SKILL_REGULAR,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_ENDRUNDECOY},
		{PT_MIG15,0,0,JUL19th1950,	0,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_WESTTRAIN},
		{PT_MIG15,1,0,JUL19th1950,	0,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_CENTTRAIN},
		{PT_MIG15,2,0,JUL19th1950,	0,0,0,	SKILL_ACE,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_WPOORTRAIN},
		{PT_MIG15,3,0,JUL19th1950,	0,0,0,	SKILL_ACE,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_CONTRAILFOCUS},
	},
	2,		//next squad to copy
	/*score*/		230,											  //MS 19/06/99//MS 28Jun99
	/*dis*/				Debrief::D_MiniText00_H,
	
	{
		{
			/*msn_date*/	JUN30th1950,
			/*msn_time*/	HR05MIN40,									  //MS 18/06/99 //RDH 28/06/99
			/*target*/		UID_RAIL_Munsan2Seoul,
			/*captarget*/	UID_RAIL_Munsan2Seoul,
			/*profile*/		FIL_C1M1								  //DAW 23/06/99

		},
		{
			/*msn_date*/	JUL3rd1950,
			/*msn_time*/	HR12,
			/*target*/		UID_ROAD_Hoensong2Wonju,
			/*captarget*/	UID_ROAD_Hoensong2Wonju,
			/*profile*/		FIL_ARMEDRECONN

		},
		{
			/*msn_date*/	JUL8th1950,
			/*msn_time*/	HR08,
			/*target*/		UID_ROAD_Suwon2Osan,
			/*captarget*/	UID_ROAD_Suwon2Osan,
			/*profile*/		FIL_C1M3								  //RDH 07/07/99

		},
		{
			/*msn_date*/	JUL19th1950,
			/*msn_time*/	HR14MIN30,
			/*target*/		UID_ROAD_Osan2Pyongtaek,
			/*captarget*/	UID_ROAD_Osan2Pyongtaek,
			/*profile*/		FIL_ARMEDRECONN

		}
	}


endinst(CampaignPackages, CampaignF80_Def);
//------------------------------------------------------------------------------
startinst(CampaignPackages, CampaignF51_Def)
	/*garbage*/		sizeof(CampaignPackages),
	/*introsmack*/		FIL_SMACK_CAMP2INTRO,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_NODE_AnTung,							//MS 19Aug96
	/*playertakeoff*/	UID_NODE_AnTung,							//MS 19Aug96
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	AUG2nd1950,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	AUG2nd1950,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	AUG2nd1950,
	/*lastdate*/		AUG20th1950,
	/*currtime*/		MORNINGPERIODSTART,				//can only be the start time
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		MORALE_GOOD,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",
//TempCode MS 06Apr99 	/*front*/				{UID_StKimchon,UID_StAndong,UID_StYonghae},//MS 22Apr99
//DeadCode MS 09Jun99 	/*front*/				{UID_SdBlTaejon,UID_StUisong,UID_StYonghae},//MS 22Apr99
	/*front*/				{UID_StKumi,UID_StAndong,UID_StYonghae},//MS 22Apr99
	/*camp_win_anim*/	 FIL_SMACK_CAMP2GOOD,
	/*camp_lost_anim*/	 FIL_SMACK_CAMP5LOSE,
	{	
//the following order of squadrons is assumed in the ui, rdh 9/8/98
	{/*F86squad*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//0,//TEXT_4FIG,
		/*airfield*/						19,//TEMP 28,					//JIM 25/01/99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					816,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},
	{/*F86sq B*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						25,
		/*movetoairfield*/					-1,
		/*nextacnumber*/					416,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F80squad*/
		/*actype*/							PT_F80,	
		/*name*/							0,//TEXT_27FEG,
		/*airfield*/						30,	//POHANG		//MS 02Jun99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					716,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F84squad*/
		/*actype*/							PT_F84,	
		/*name*/							0,//TEXT_8FBG,
		/*airfield*/						27,
		/*movetoairfield*/					-1,
		/*nextacnumber*/					616,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F51squad*/
		/*actype*/							PT_F51,	
		/*name*/							0,//TEXT_35FIG,
		/*airfield*/						27,	//TAEGU			//MS 13Apr99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					516,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					AUG2nd1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	}


	},

	{	 //type,colour,text,date				avail,tloss,dloss,MAX skill
		{PT_MIG15,0,0,DEC25th1950,/*active slot!!*/	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_SANCPAT},
		{PT_MIG15,1,0,DEC25th1950,/*active slot!!*/	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_SANCPAT},
		{PT_MIG15,2,0,DEC25th1950+SECSPERWEEK*3,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_SAFEPAT},
		{PT_MIG15,3,0,DEC25th1950+SECSPERWEEK*6,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_INTERCEPT1},
		{PT_MIG15,4,0,DEC25th1950+SECSPERWEEK*9,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_WAITWEAK},
		{PT_MIG15,5,0,DEC25th1950+SECSPERWEEK*12,	0,0,0,	SKILL_REGULAR,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_CUTWEAK},
		{PT_MIG15,6,0,DEC25th1950+SECSPERWEEK*15,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_ENDRUNDECOY},
		{PT_MIG15,7,0,DEC25th1950+SECSPERWEEK*18,	0,0,0,	SKILL_REGULAR,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_ENDRUNDECOY},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*21,	0,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_WESTTRAIN},
		{PT_MIG15,1,0,DEC25th1950+SECSPERWEEK*24,	0,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_CENTTRAIN},
		{PT_MIG15,2,0,DEC25th1950+SECSPERWEEK*27,	0,0,0,	SKILL_ACE,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_WPOORTRAIN},
		{PT_MIG15,3,0,DEC25th1950+SECSPERWEEK*30,	0,0,0,	SKILL_ACE,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_CONTRAILFOCUS},
	},
	2,		//next squad to copy
	/*score*/		80,											//MS 28Jun99
	/*dis*/				Debrief::D_MiniText06_H,
	
	{
		{
			/*msn_date*/	AUG15th1950,
			/*msn_time*/	HR09,
			/*target*/		UID_StTaegu,
			/*captarget*/	UID_NULL,
			/*profile*/		FIL_CASPUSAN

		},
		{
			/*msn_date*/	AUG18th1950,
			/*msn_time*/	HR16MIN20,
			/*target*/		UID_StTaegu,
			/*captarget*/	UID_NULL,
			/*profile*/		FIL_CASPUSAN

		},
		{
			/*msn_date*/	AUG19th1950,
			/*msn_time*/	HR10,
			/*target*/		UID_StTaegu,
			/*captarget*/	UID_NULL,
			/*profile*/		FIL_CASPUSAN

		},
		{
			/*msn_date*/	AUG20th1950,
			/*msn_time*/	HR13,
			/*target*/		UID_StTaegu,
			/*captarget*/	UID_NULL,
			/*profile*/		FIL_CASPUSAN

		},
//DeadCode DAW 08Apr99 		{
//DeadCode DAW 08Apr99 			/*msn_date*/	DEC25th1950,
//DeadCode DAW 08Apr99 			/*msn_time*/	HR08MIN50,
//DeadCode DAW 08Apr99 			/*target*/		UID_ROAD_Kanda2Wonsan,
//DeadCode DAW 08Apr99 			/*captarget*/		UID_ROAD_Kanda2Wonsan,
//DeadCode DAW 08Apr99 			/*profile*/		FIL_CAS
//DeadCode DAW 08Apr99 
//DeadCode DAW 08Apr99 		},
//DeadCode DAW 08Apr99 		{
//DeadCode DAW 08Apr99 			/*msn_date*/	DEC25th1950,
//DeadCode DAW 08Apr99 			/*msn_time*/	HR08MIN50,
//DeadCode DAW 08Apr99 			/*target*/		UID_ROAD_Kanda2Wonsan,
//DeadCode DAW 08Apr99 			/*captarget*/		UID_ROAD_Kanda2Wonsan,
//DeadCode DAW 08Apr99 			/*profile*/		FIL_CAS
//DeadCode DAW 08Apr99 
//DeadCode DAW 08Apr99 		},
//DeadCode DAW 08Apr99 		{
//DeadCode DAW 08Apr99 			/*msn_date*/	DEC25th1950,
//DeadCode DAW 08Apr99 			/*msn_time*/	HR08MIN50,
//DeadCode DAW 08Apr99 			/*target*/		UID_ROAD_Kanda2Wonsan,
//DeadCode DAW 08Apr99 			/*captarget*/		UID_ROAD_Kanda2Wonsan,
//DeadCode DAW 08Apr99 			/*profile*/		FIL_CAS
//DeadCode DAW 08Apr99 
//DeadCode DAW 08Apr99 		},
//DeadCode DAW 08Apr99 		{
//DeadCode DAW 08Apr99 			/*msn_date*/	DEC25th1950,
//DeadCode DAW 08Apr99 			/*msn_time*/	HR08MIN50,
//DeadCode DAW 08Apr99 			/*target*/		UID_ROAD_Kanda2Wonsan,
//DeadCode DAW 08Apr99 			/*captarget*/		UID_ROAD_Kanda2Wonsan,
//DeadCode DAW 08Apr99 			/*profile*/		FIL_CAS
//DeadCode DAW 08Apr99 
//DeadCode DAW 08Apr99 		}
	}


endinst(CampaignPackages, CampaignF51_Def);
//------------------------------------------------------------------------------
startinst(CampaignPackages, CampaignF84_Def)
	/*garbage*/		sizeof(CampaignPackages),
	/*introsmack*/		FIL_SMACK_CAMP3INTRO,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_NODE_AnTung,							//MS 19Aug96
	/*playertakeoff*/	UID_NODE_AnTung,							//MS 19Aug96
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	SEP18th1950,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	SEP18th1950,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	SEP18th1950,
	/*lastdate*/		OCT25th1950,
	/*currtime*/		MIDDAYPERIODSTART,
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		MORALE_GOOD,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",
	/*front*/				{UID_MyBlSeoul,UID_StChuncheon,UID_StKansang},//MS 09Jun99
	/*camp_win_anim*/	 FIL_SMACK_CAMP3GOOD,
	/*camp_lost_anim*/	 FIL_SMACK_CAMP3INTRO,

//	/*front*/				{UID_MyBlMunsan,UID_StYonchon,UID_StChongson},
//	/*front*/				{UID_MyBlSeoul,UID_SdRdWonju,UID_SdRdYangyang},
//	/*front*/				{UID_SdBlPyongtaek,UID_SdRdWonju,UID_SdRdYangyang},
	{	
//the following order of squadrons is assumed in the ui, rdh 9/8/98
	{/*F86squad*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						19,//TEMP 28,					//JIM 25/01/99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					816,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},
	{/*F86sq B*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						25,
		/*movetoairfield*/					-1,
		/*nextacnumber*/					416,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F80squad*/
		/*actype*/							PT_F80,	
		/*name*/							0,//TEXT_27FEG,
		/*airfield*/						22,	//Osan			//MS 02Jun99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					716,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F84squad*/
		/*actype*/							PT_F84,	
		/*name*/							0,//TEXT_8FBG,
		/*airfield*/						23,	//SUWON
		/*movetoairfield*/					-1,
		/*nextacnumber*/					616,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					SEP17th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F51squad*/
		/*actype*/							PT_F51,	
		/*name*/							0,//TEXT_35FIG,
		/*airfield*/						26, //Taejon
		/*movetoairfield*/					-1,
		/*nextacnumber*/					516,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	}


	},

	{	 //type,colour,text,date				avail,tloss,dloss,MAX skill
		{PT_MIG15,0,0,DEC25th1950,/*active slot!!*/	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_SANCPAT},
		{PT_MIG15,1,0,DEC25th1950,/*active slot!!*/	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_SANCPAT},
		{PT_MIG15,2,0,DEC25th1950+SECSPERWEEK*3,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_SAFEPAT},
		{PT_MIG15,3,0,DEC25th1950+SECSPERWEEK*6,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_INTERCEPT1},
		{PT_MIG15,4,0,DEC25th1950+SECSPERWEEK*9,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_WAITWEAK},
		{PT_MIG15,5,0,DEC25th1950+SECSPERWEEK*12,	0,0,0,	SKILL_REGULAR,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_CUTWEAK},
		{PT_MIG15,6,0,DEC25th1950+SECSPERWEEK*15,	0,0,0,	SKILL_POOR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_ENDRUNDECOY},
		{PT_MIG15,7,0,DEC25th1950+SECSPERWEEK*18,	0,0,0,	SKILL_REGULAR,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_ENDRUNDECOY},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*21,	0,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_WESTTRAIN},
		{PT_MIG15,1,0,DEC25th1950+SECSPERWEEK*24,	0,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_CENTTRAIN},
		{PT_MIG15,2,0,DEC25th1950+SECSPERWEEK*27,	0,0,0,	SKILL_ACE,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_WPOORTRAIN},
		{PT_MIG15,3,0,DEC25th1950+SECSPERWEEK*30,	0,0,0,	SKILL_ACE,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_CONTRAILFOCUS},
	},
	2,		//next squad to copy
	/*score*/		4,
	/*dis*/				Debrief::D_MiniText12_H,
	
	{
		{
			/*msn_date*/	SEP20th1950,
			/*msn_time*/	HR15,
			/*target*/		UID_SdRdKaesong,
			/*captarget*/	UID_SdRdKaesong,
			/*profile*/		FIL_FBSTRIKE

		},
		{
			/*msn_date*/	SEP25th1950,
			/*msn_time*/	HR13,
			/*target*/		UID_BrRlYesong,
			/*captarget*/	UID_BrRlYesong,
			/*profile*/		FIL_FBSTRIKE

		},
		{
			/*msn_date*/	OCT8th1950,
			/*msn_time*/	HR09,
			/*target*/		UID_SdRdPyonggang,
			/*captarget*/	UID_SdRdPyonggang,
			/*profile*/		FIL_FBSTRIKE

		},
		{
			/*msn_date*/	OCT16th1950,
			/*msn_time*/	HR14MIN50,
			/*target*/		UID_ICMPNampo,
			/*captarget*/	UID_ICMPNampo,
			/*profile*/		FIL_FBSTRIKE
//DeadCode MS 24Jun99 			/*msn_date*/	OCT16th1950,
//DeadCode MS 24Jun99 			/*msn_time*/	HR14MIN50,
//DeadCode MS 24Jun99 			/*target*/		UID_BrRlPyongyang,
//DeadCode MS 24Jun99 			/*captarget*/	UID_BrRlPyongyang,
//DeadCode MS 24Jun99 			/*profile*/		FIL_FBSTRIKE

		},
		{
			/*msn_date*/	OCT25th1950,
			/*msn_time*/	HR12MIN15,
			/*target*/		UID_WhRdSukchon,
			/*captarget*/	UID_WhRdSukchon,
			/*profile*/		FIL_FBSTRIKE

		},
//DeadCode DAW 08Apr99 		{
//DeadCode DAW 08Apr99 			/*msn_date*/	DEC25th1950,
//DeadCode DAW 08Apr99 			/*msn_time*/	HR08MIN50,
//DeadCode DAW 08Apr99 			/*target*/		UID_BrRlImjin,
//DeadCode DAW 08Apr99 			/*captarget*/	UID_BrRlImjin,
//DeadCode DAW 08Apr99 			/*profile*/		FIL_FBSTRIKE
//DeadCode DAW 08Apr99 
//DeadCode DAW 08Apr99 		},
//DeadCode MS 06Apr99 		{
//DeadCode MS 06Apr99 			/*msn_date*/	DEC25th1950,
//DeadCode MS 06Apr99 			/*msn_time*/	HR08MIN50,
//DeadCode MS 06Apr99 			/*target*/		UID_ROAD_Kanda2Wonsan,
//DeadCode MS 06Apr99 			/*captarget*/		UID_ROAD_Kanda2Wonsan,
//DeadCode MS 06Apr99 			/*profile*/		FIL_FBSTRIKE
//DeadCode MS 06Apr99 
//DeadCode MS 06Apr99 		},
//DeadCode MS 06Apr99 		{
//DeadCode MS 06Apr99 			/*msn_date*/	DEC25th1950,
//DeadCode MS 06Apr99 			/*msn_time*/	HR08MIN50,
//DeadCode MS 06Apr99 			/*target*/		UID_ROAD_Kanda2Wonsan,
//DeadCode MS 06Apr99 			/*captarget*/		UID_ROAD_Kanda2Wonsan,
//DeadCode MS 06Apr99 			/*profile*/		FIL_FBSTRIKE
//DeadCode MS 06Apr99 
//DeadCode MS 06Apr99 		}
	},


endinst(CampaignPackages, CampaignF84_Def);
//------------------------------------------------------------------------------
startinst(CampaignPackages, CampaignF86_Def)
	/*garbage*/		sizeof(CampaignPackages),
	/*introsmack*/		FIL_SMACK_CAMP4INTRO,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_NODE_AnTung,							//MS 19Aug96
	/*playertakeoff*/	UID_NODE_AnTung,							//MS 19Aug96
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	NOV2nd1950,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	NOV2nd1950,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	NOV2nd1950,
	/*lastdate*/		DEC25th1950,
	/*currtime*/		MIDDAYPERIODSTART,
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		MORALE_GOOD,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",
	/*front*/				{UID_MyRdPyongyang,UID_StSamdung,UID_MyRlWonsan},//MS 14May99
	/*camp_win_anim*/	 FIL_SMACK_CAMP4GOOD,
	/*camp_lost_anim*/	 FIL_SMACK_CAMP4INTRO,
	{	
//the following order of squadrons is assumed in the ui, rdh 9/8/98
	{/*F86squad*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						19,	//KIMPO
		/*movetoairfield*/					-1,
		/*nextacnumber*/					816,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					NOV2nd1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},
	{/*F86sq B*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						25,	//KUNSAN
		/*movetoairfield*/					-1,
		/*nextacnumber*/					416,
		/*ac_total_avail*/					19,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F80squad*/
		/*actype*/							PT_F80,	
		/*name*/							0,//TEXT_27FEG,
		/*airfield*/						22,//TEMP 27,
		/*movetoairfield*/					-1,
		/*nextacnumber*/					716,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F84squad*/
		/*actype*/							PT_F84,	
		/*name*/							0,//TEXT_8FBG,
		/*airfield*/						27,
		/*movetoairfield*/					-1,
		/*nextacnumber*/					616,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F51squad*/
		/*actype*/							PT_F51,	
		/*name*/							0,//TEXT_35FIG,
		/*airfield*/						26,
		/*movetoairfield*/					-1,
		/*nextacnumber*/					516,
		/*ac_total_avail*/					0,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					DEC25th1950,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	}


	},

	{	 //type,colour,text,date				avail,tloss,dloss,MAX skill
		{PT_MIG15,0,0,DEC25th1950,/*active slot!!*/	40,0,0,	SKILL_VETERAN,	MORALE_EXCELLENT,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},//MS 27Jun99
		{PT_MIG15,0,0,DEC25th1950,/*active slot!!*/	40,0,0,	SKILL_VETERAN,	MORALE_EXCELLENT,	AL_SPLITFORCE,MIGEV_BOMBERS1},//MS 27Jun99
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*3,	40,0,0,	SKILL_VETERAN,	MORALE_EXCELLENT,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},//MS 27Jun99
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*6,	40,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*9,	40,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*12,	40,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*15,	40,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*18,	40,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*21,	40,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*24,	40,0,0, SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*27,	40,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},
		{PT_MIG15,0,0,DEC25th1950+SECSPERWEEK*30,	40,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_BOMBERS1},
	},
	2,		//next squad to copy
	/*score*/		5,
	/*dis*/				Debrief::D_MiniText18_H,
	
	{
		{
			/*msn_date*/	NOV2nd1950,
			/*msn_time*/	HR12MIN20,
			/*target*/		UID_WhRdSinuiju,
			/*captarget*/	UID_NODE_sinuiju,
			/*profile*/		FIL_MEDBSTRIKE

		},
		{
			/*msn_date*/	NOV15th1950,
			/*msn_time*/	HR13,
			/*target*/		UID_BrRlYalu0,
			/*captarget*/	UID_NODE_sinuiju,
			/*profile*/		FIL_MEDBSTRIKE

		},
		{
			/*msn_date*/	NOV25th1950,
			/*msn_time*/	HR14MIN20,
			/*target*/		UID_SCCSakchu,
			/*captarget*/	UID_StNamsanni,
			/*profile*/		FIL_MEDBSTRIKE

		},
		{
			/*msn_date*/	DEC9th1950,
			/*msn_time*/	HR15MIN20,
			/*target*/		UID_SdRdSonchon,
			/*captarget*/	UID_NODE_sinuiju,
			/*profile*/		FIL_MEDBSTRIKE

		},
		{
			/*msn_date*/	DEC16th1950,
			/*msn_time*/	HR11,
			/*target*/		UID_SCCHuichon,
			/*captarget*/	UID_StNamsanni,
			/*profile*/		FIL_MEDBSTRIKE

		},
		{
			/*msn_date*/	DEC25th1950,
			/*msn_time*/	HR13,
			/*target*/		UID_BrRdSinuiju,
			/*captarget*/	UID_NODE_sinuiju,
			/*profile*/		FIL_MEDBSTRIKE

		},
//DeadCode MS 06Apr99 		{
//DeadCode MS 06Apr99 			/*msn_date*/	DEC25th1950,
//DeadCode MS 06Apr99 			/*msn_time*/	HR08MIN50,
//DeadCode MS 06Apr99 			/*target*/		UID_ROAD_Kanda2Wonsan,
//DeadCode MS 06Apr99 			/*captarget*/		UID_ROAD_Kanda2Wonsan,
//DeadCode MS 06Apr99 			/*profile*/		FIL_MEDBSTRIKE
//DeadCode MS 06Apr99 
//DeadCode MS 06Apr99 		},
//DeadCode MS 06Apr99 		{
//DeadCode MS 06Apr99 			/*msn_date*/	DEC25th1950,
//DeadCode MS 06Apr99 			/*msn_time*/	HR08MIN50,
//DeadCode MS 06Apr99 			/*target*/		UID_ROAD_Kanda2Wonsan,
//DeadCode MS 06Apr99 			/*captarget*/		UID_ROAD_Kanda2Wonsan,
//DeadCode MS 06Apr99 			/*profile*/		FIL_MEDBSTRIKE
//DeadCode MS 06Apr99 
//DeadCode MS 06Apr99 		}
	},


endinst(CampaignPackages, CampaignF86_Def);
//------------------------------------------------------------------------------
startinst(CampaignSquad, CampaignSpring_Def)
	/*garbage*/		sizeof(CampaignSquad),
	/*introsmack*/		FIL_SMACK_CAMP5INTRO,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_NODE_AnTung,							//MS 19Aug96
	/*playertakeoff*/	UID_NODE_AnTung,							//MS 19Aug96
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	JAN5th1951,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	JAN5th1951,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	JAN5th1951,
	/*lastdate*/		JUN20th1951,
	/*currtime*/		MORNINGPERIODSTART,
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		MORALE_GOOD,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//THIS SECTION WILL BE IN FINAL VERSION, IS COMMENTED OUT WHEN TESTING
#if !defined(NEVER_DEFINED_DOUBLE_EXCLAIM_TO_USE_TESTVALUES) || defined(NDEBUG)	
#pragma warnmsg("release campaign line")

//TempCode MS 01Jun99 //front 1
//TempCode MS 01Jun99	/*front*/				{UID_SdBlPyongtaek,UID_SdRdWonju,UID_StKangnung},
//TempCode MS 02Jun99 //front 2
//TempCode MS 02Jun99 	/*front*/				{UID_SdBlSuwon,UID_StHoensong,UID_SdRdYangyang},
//TempCode MS 02Jun99 //front 3
//TempCode MS 02Jun99 	/*front*/				{UID_MyBlSeoul,UID_StChuncheon,UID_StKansang},
//TempCode MS 03Jun99 //front 4
//TempCode MS 08Jun99 	/*front*/				{UID_SdRdKaesong,UID_StHwachon,UID_StKojin},
//TempCode MS 03Jun99 //front 5
//TempCode MS 03Jun99 	/*front*/				{UID_SdRdSariwon,UID_SdRdPyonggang,UID_StKojo},
//TempCode MS 03Jun99 //front 6
//TempCode MS 03Jun99 	/*front*/				{UID_MyRdPyongyang,UID_StSamdung,UID_MyRlWonsan},

//DEADCODE RDH 06/06/99  	/*front*/				{UID_SdRdKaesong,UID_StHwachon,UID_StKojin},
/*front*/				{UID_SdBlPyongtaek,UID_SdRdWonju,UID_StKangnung},

	/*camp_win_anim*/	 FIL_SMACK_CAMP5PEACE,
	/*camp_lost_anim*/	 FIL_SMACK_CAMP5LOSE,

	{	
//the following order of squadrons is assumed in the ui, rdh 9/8/98
	{/*F86squad*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						27,	//TAEGU			//MS 13Apr99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					816,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},
	{/*F86sq B*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						25,	//KUNSAN
		/*movetoairfield*/					-1,
		/*nextacnumber*/					416,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F80squad*/
		/*actype*/							PT_F80,	
		/*name*/							0,//TEXT_27FEG,
		/*airfield*/						30,	//POHANG		//MS 02Jun99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					716,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F84squad*/
		/*actype*/							PT_F84,	
		/*name*/							0,//TEXT_8FBG,
		/*airfield*/						27, //TAEGU			//MS 13Apr99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					616,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F51squad*/
		/*actype*/							PT_F51,	
		/*name*/							0,//TEXT_35FIG,
		/*airfield*/						26,	//TAEJON		//MS 13Apr99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					516,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#else
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//THIS SECTION IS USED FOR TESTING, WILL NOT BE IN FINAL VERSION
#pragma warnmsg("debug campaign line!!!!!!!!!!!!!!!!!!")

//TempCode MS 01Jun99 //front 1
//TempCode MS 01Jun99 ///*front*/				{UID_SdBlPyongtaek,UID_SdRdWonju,UID_StKangnung},
//TempCode MS 02Jun99 //front 2
//TempCode MS 02Jun99 	/*front*/				{UID_SdBlSuwon,UID_StHoensong,UID_StKangnung},
//TempCode MS 02Jun99 //front 3
//TempCode MS 02Jun99 /*front*/				{UID_MyBlSeoul,UID_StChuncheon,UID_StKansang},
//TempCode MS 03Jun99 //front 4
//TempCode MS 03Jun99 	/*front*/				{UID_SdRdKaesong,UID_StHwachon,UID_StKojin},
//TempCode MS 03Jun99 //front 5
//TempCode MS 03Jun99 	/*front*/				{UID_SdRdSariwon,UID_SdRdPyonggang,UID_StKojin},
//TempCode MS 03Jun99 //front 6
//TempCode MS 03Jun99 	/*front*/				{UID_MyRdPyongyang,UID_StSamdung,UID_MyRlWonsan},

//TempCode MS 03Jun99 //front 4
	/*front*/				{UID_SdRdKaesong,UID_StHwachon,UID_StKojin},

	/*camp_win_anim*/	 FIL_SMACK_CAMP5PEACE,
	/*camp_lost_anim*/	 FIL_SMACK_CAMP5LOSE,

	{	
//the following order of squadrons is assumed in the ui, rdh 9/8/98
	{/*F86squad*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						27,	//TAEGU			//MS 13Apr99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					816,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},
	{/*F86sq B*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						25,	//KUNSAN
		/*movetoairfield*/					-1,
		/*nextacnumber*/					416,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F80squad*/
		/*actype*/							PT_F80,	
		/*name*/							0,//TEXT_27FEG,
		/*airfield*/						30,	//POHANG	//MS 13Apr99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					716,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F84squad*/
		/*actype*/							PT_F84,	
		/*name*/							0,//TEXT_8FBG,
		/*airfield*/						19, //TAEGU			//MS 13Apr99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					616,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F51squad*/
		/*actype*/							PT_F51,	
		/*name*/							0,//TEXT_35FIG,
		/*airfield*/						20,	//SEOUL		//MS 13Apr99
		/*movetoairfield*/					-1,
		/*nextacnumber*/					516,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	}
//END OF TEST SETUP												//MS 20Apr99
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#endif
	},
	{	 //type,colour,text,date				avail,tloss,dloss,MAX skill
		{PT_MIG15,0,0,DEC25th1950,/*active slot!!*/	60,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_CUTWEAK},
		{PT_MIG15,1,0,DEC25th1950,/*active slot!!*/	60,0,0,	SKILL_VETERAN,	MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_CUTWEAK},
		{PT_MIG15,2,0,JAN5th1951+SECSPERWEEK*3,	60,0,0,	SKILL_REGULAR,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_BOMBERS2},//MS 18May99
		{PT_MIG15,3,0,JAN5th1951+SECSPERWEEK*5,	40,0,0,	SKILL_ACE,		MORALE_MEDIUM,	AL_DEFENSIVE,MIGEV_INTERCEPT3},//MS 18May99
		{PT_MIG15,4,0,JAN5th1951+SECSPERWEEK*7,	60,0,0,	SKILL_VETERAN,		MORALE_EXCELLENT,AL_DEFENSIVE,MIGEV_BOMBERS3},
		{PT_MIG15,5,0,JAN5th1951+SECSPERWEEK*9,	60,0,0,	SKILL_REGULAR,	MORALE_GOOD,	AL_DEFENSIVE,MIGEV_STATICROUND},
		{PT_MIG15,6,0,JAN5th1951+SECSPERWEEK*11,	40,0,0,	SKILL_ACE,		MORALE_EXCELLENT,AL_DEFENSIVE,MIGEV_LOWSWEEP},
		{PT_MIG15,7,0,JAN5th1951+SECSPERWEEK*13,	60,0,0,	SKILL_REGULAR,	MORALE_MEDIUM,	AL_DEFENSIVE,MIGEV_INTERCEPT4},
		{PT_MIG15,0,0,JAN5th1951+SECSPERWEEK*15,	40,0,0,	SKILL_ACE,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_SUPERIOR1},
		{PT_MIG15,1,0,JAN5th1951+SECSPERWEEK*17,	60,0,0,	SKILL_VETERAN,		MORALE_GOOD,	AL_ATTACKANYTHING,MIGEV_SUPERIOR2},
		{PT_MIG15,2,0,JAN5th1951+SECSPERWEEK*19,	60,0,0,	SKILL_REGULAR,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_BIGTRAIN1},
		{PT_MIG15,3,0,JAN5th1951+SECSPERWEEK*21,	60,0,0,	SKILL_ACE,		MORALE_GOOD,	AL_DEFENSIVE,MIGEV_BIGTRAIN1},
	},
	2		//next squad to copy
endinst(CampaignSquad, CampaignSpring_Def);

#ifdef	MIG_DEMO_VER		//sinmak
#define	SCRAMBLEAF	0
#else						//kimpo
#define	SCRAMBLEAF	19
#endif
startinst(CampaignBlueSquad, CampaignScramble_Def)
	/*garbage*/		sizeof(CampaignBlueSquad),
	/*introsmack*/		FIL_SMACK_CAMP5INTRO,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_NODE_AnTung,							//MS 19Aug96
	/*playertakeoff*/	UID_NODE_AnTung,							//MS 19Aug96
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	JAN5th1951,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	JAN5th1951,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	JAN5th1951,
	/*lastdate*/		APR1st1951,
	/*currtime*/		MORNINGPERIODSTART,
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		MORALE_GOOD,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",

	/*front*/				{UID_SdBlPyongtaek,UID_SdRdWonju,UID_SdRdYangyang},
	/*camp_win_anim*/	 FIL_SMACK_CAMP5PEACE,
	/*camp_lost_anim*/	 FIL_SMACK_CAMP5LOSE,

	{	
//the following order of squadrons is assumed in the ui, rdh 9/8/98
	{/*F86squad*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						SCRAMBLEAF,	//KIMPO
		/*movetoairfield*/					-1,
		/*nextacnumber*/					816,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},
	{/*F86sq B*/
		/*actype*/							PT_F86E,	
		/*name*/							0,//TEXT_4FIG,
		/*airfield*/						SCRAMBLEAF,	//KIMPO
		/*movetoairfield*/					-1,
		/*nextacnumber*/					416,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F80squad*/
		/*actype*/							PT_F80,	
		/*name*/							0,//TEXT_27FEG,
		/*airfield*/						SCRAMBLEAF,	//KIMPO
		/*movetoairfield*/					-1,
		/*nextacnumber*/					716,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F84squad*/
		/*actype*/							PT_F84,	
		/*name*/							0,//TEXT_8FBG,
		/*airfield*/						SCRAMBLEAF,	//KIMPO
		/*movetoairfield*/					-1,
		/*nextacnumber*/					616,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	},

	{/*F51squad*/
		/*actype*/							PT_F51,	
		/*name*/							0,//TEXT_35FIG,
		/*airfield*/						SCRAMBLEAF,	//KIMPO
		/*movetoairfield*/					-1,
		/*nextacnumber*/					516,
		/*ac_total_avail*/					MAX_NUM_AC_IN_SQUADRON,
		/*rotatefreq*/						2,
		/*lastrotatedate*/					JAN5th1951,
		/*flt_used*/						0,
		/*bingofuel*/						68027000,
		/*elementtactics*/					WELDEDWING,
		/*flighttactics*/					SWORDANDSHIELD
	}

	},
endinst(CampaignBlueSquad, CampaignScramble_Def);


PilotType	Campaign::Active_Pilots_Init[] =

//	4th FIW
	{/*active pilots*/
		{	//F86 SQUAD 0
			/*name*/			{00},
			//Zane S. Hankey
			NEWSKILL(SKILL_HERO,		SKILL_HERO,		POTENTIAL_MAX,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			3,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0

		},
		{
			/*name*/			{01},
			//B. S. Wilcox
			NEWSKILL(SKILL_VETERAN2,	SKILL_REGULAR1,		POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			5,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			1
		},
		{
			/*name*/			{02},
			//John W. Wurster
			NEWSKILL(SKILL_ACE,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			1,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			2
		},
		{
			/*name*/			{03},
			//Harlod L. Visscher
			NEWSKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_VERYPOOR),
			/*status*/			FLYING,
			/*morale*/			MORALE_VERYGOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			3
		},
		{
			/*name*/			{04},
			//Walker M. Slaughter
			NEWSKILL(SKILL_REGULAR,	SKILL_MAX,		POTENTIAL_GOOD,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			1,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			4
		},
		{
			/*name*/			{05},
			//Van E. Skeen
			NEWSKILL(SKILL_ACE,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			1,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			5
		},
		{
			/*name*/			{06},
			//Earnest A. Simmonds
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			4,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			6
		},
		{
			/*name*/			{07},
			//Russell J. Lindsay
			NEWSKILL(SKILL_REGULAR,	SKILL_MAX,		POTENTIAL_GOOD,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_VERYGOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			1,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			7
		},
		{
			/*name*/			{8},
			//William T. Van Grundy
			NEWSKILL(SKILL_VETERAN,		SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			1,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			8
		},
		{
			/*name*/			{9},
			//Albert S. Norris
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			9
		},
		{
			/*name*/			{10},
			//Lowell K. Sandlin
			NEWSKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_GOOD,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			10
		},
		{
			/*name*/			{11},
			//Claude A. Chandler
			NEWSKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_REGULAR,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			1,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			11
		},
		{
			/*name*/			{12},
			//Orrin R. McKay
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			3,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			12
		},
		{
			/*name*/			{13},
			//James B. Plog
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			1,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			13
		},
		{
			/*name*/			{14},
			//Jacob Mchale
			NEWSKILL(SKILL_ACE,		SKILL_REGULAR,	POTENTIAL_EXCELLENT,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			14
		},
		{
			/*name*/			{15},
			//Richard J. Levesque
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR1,	POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			15
		},
		{
			/*name*/			{16},
			//R. T. F. Kinsey
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,	POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{17},
			//Jack R. Long
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{18},
			//Glenn T. Mullins
			NEWSKILL(SKILL_ACE,		SKILL_ACE,		POTENTIAL_MAX,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_TOPMORALE,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{19},
			//Kenneth D. La France
			NEWSKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{20},
			//James W. Bertram
			NEWSKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_GOOD,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{21},
			//Phillip E. Young
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR2,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{22},
			//Carrol B. McGuire
			NEWSKILL(SKILL_ACE,		SKILL_VETERAN,		POTENTIAL_MAX,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			1,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{23},
			//P. Lamb
			NEWSKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			1,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{	//F86 SQUAD 1
			/*name*/			{24},
			//Bruce Hinton
			NEWSKILL(SKILL_ACE,		SKILL_HERO,		POTENTIAL_MAX,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{25},
			//John W. Lovell
			NEWSKILL(SKILL_ACE,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{26},
			//J. H. J. Andre
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN1,		POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{27},
			//Ben L. Hovde
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{28},
			//Bruce H. Gogerly
			NEWSKILL(SKILL_VETERAN2,	SKILL_REGULAR1,		POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{29},
			//Kenneth L. Arnell
			NEWSKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_GOOD,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{30},
			//Conrad E. Goldberg
			NEWSKILL(SKILL_ACE,		SKILL_VETERAN,	POTENTIAL_EXCELLENT,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{31},
			//Graham S. Hoster
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{32},
			//Robert H. Keyes
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_REGULAR,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{33},
			//Benjamin H. Hudson
			NEWSKILL(SKILL_VETERAN,		SKILL_POOR,	POTENTIAL_MAX,		POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{34},
			//Sam R. Hockerey
			NEWSKILL(SKILL_ACE,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{35},
			//William W. Mahurin
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{36},
			//Ralph E. Dewald
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_GOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_VERYGOOD,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{37},
			//J.B. Harrison
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR1,	POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{38},
			//I. L. Mattson
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{39},
			//Robert E. Martin
			NEWSKILL(SKILL_ACE,		SKILL_REGULAR,		POTENTIAL_MAX,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{40},
			//J. A. O. Burns
			NEWSKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{41},
			//William G. Emmert
			NEWSKILL(SKILL_MAX,		SKILL_POOR,		POTENTIAL_MAX,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{42},
			//Roy W. Meyer
			NEWSKILL(SKILL_REGULAR,	SKILL_POOR,	POTENTIAL_EXCELLENT,POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{43},
			//Edwin L. Thomas
			NEWSKILL(SKILL_ACE,		SKILL_REGULAR,	POTENTIAL_EXCELLENT,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{44},
			//Samuel Hulse
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{45},
			//William E. Charmichael
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,		POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{46},
			//Maurice L. Wayne
			NEWSKILL(SKILL_REGULAR,	SKILL_POOR,		POTENTIAL_GOOD,	POTENTIAL_POOR),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{47},
			//Whiteside
			NEWSKILL(SKILL_REGULAR2,		SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{	//F80 SQUAD
			/*name*/			{48},
			//Elmer W. Schillereff
			NEWSKILL(SKILL_ACE,		SKILL_ACE,		POTENTIAL_MAX,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{49},
			//E. B. Best
			NEWSKILL(SKILL_ACE,		SKILL_ACE,		POTENTIAL_MAX,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{50},
			//John Fox
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{51},
			//Arnold EagleSton
			NEWSKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{52},
			//John C. Marsh
			NEWSKILL(SKILL_MAX,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{53},
			//Stanton G. Preston
			NEWSKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_GOOD,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{54},
			//Robert V. Kratt
			NEWSKILL(SKILL_ACE1,	SKILL_ACE,		POTENTIAL_MAX,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{55},
			//Allen McElroy
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{56},
			//Harry T. Raebel
			NEWSKILL(SKILL_ACE,		SKILL_ACE,		POTENTIAL_MAX,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{57},
			//Sam P. Colman
			NEWSKILL(SKILL_REGULAR2,		SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{58},
			//Charles A. Mitchell
			NEWSKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{59},
			//James D. Brown
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR2,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{60},
			//L. H. Kelly
			NEWSKILL(SKILL_ACE,		SKILL_REGULAR,	POTENTIAL_EXCELLENT,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{61},
			//William E. Little
			NEWSKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_EXCELLENT,POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{62},
			//Raymond E. Harris
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_VERYGOOD,	POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{63},
			//W. Glover
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{64},
			//Herman W. Price
			NEWSKILL(SKILL_POOR,		SKILL_REGULAR,		POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{65},
			//Jones
			NEWSKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_VERYGOOD,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{66},
			//E. A. Samways
			NEWSKILL(SKILL_REGULAR,		SKILL_REGULAR,	POTENTIAL_GOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{67},
			//William J. Fithian
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{68},
			//Hyde
			NEWSKILL(SKILL_REGULAR,	SKILL_POOR,		POTENTIAL_VERYGOOD,	POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{69},
			//Shaw
			NEWSKILL(SKILL_REGULAR,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{70},
			//John J. Lyons
			NEWSKILL(SKILL_POOR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{71},
			//Richard Granville
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{	//F84 SQUAD
			/*name*/			{72},
			//Amen
			NEWSKILL(SKILL_HERO,		SKILL_ACE2,	POTENTIAL_MAX,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{73},
			//Raymond J. Dickinson
			NEWSKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{74},
			//John H. Heyman
			NEWSKILL(SKILL_ACE,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{75},
			//William T. Brueland
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{76},
			//John B. Heller
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{77},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR1,	POTENTIAL_EXCELLENT,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{78},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_REGULAR,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{79},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,		POTENTIAL_REGULAR,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{80},
			//NAME
			NEWSKILL(SKILL_REGULAR,		SKILL_REGULAR,	POTENTIAL_GOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{81},
			//NAME
			NEWSKILL(SKILL_VETERAN2,	SKILL_REGULAR1,		POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{82},
			//NAME
			NEWSKILL(SKILL_MAX,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_VERYGOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{83},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYPOOR),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{84},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,		POTENTIAL_VERYGOOD,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{85},
			//NAME
			NEWSKILL(SKILL_ACE,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{86},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_MAX,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{87},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_MAX,		POTENTIAL_GOOD,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{88},
			//NAME
			NEWSKILL(SKILL_VETERAN,		SKILL_POOR,	POTENTIAL_MAX,		POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{89},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{90},
			//NAME
			NEWSKILL(SKILL_POOR,	SKILL_POOR,		POTENTIAL_GOOD,		POTENTIAL_POOR),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{91},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_REGULAR,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{92},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{93},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{94},
			//NAME
			NEWSKILL(SKILL_REGULAR,		SKILL_REGULAR,	POTENTIAL_GOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{95},
			//NAME
			NEWSKILL(SKILL_POOR2,	SKILL_POOR,		POTENTIAL_REGULAR,	POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{	//F51 SQUAD
			/*name*/			{96},
			//NAME
			NEWSKILL(SKILL_HERO,	SKILL_VETERAN,	POTENTIAL_MAX,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_EXCELLENT,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{97},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_GOOD,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{98},
			//NAME
			NEWSKILL(SKILL_MAX,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{99},
			//NAME
			NEWSKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{100},
			//NAME
			NEWSKILL(SKILL_ACE,		SKILL_ACE,		POTENTIAL_MAX,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{101},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{102},
			//NAME
			NEWSKILL(SKILL_ACE,		SKILL_VETERAN,		POTENTIAL_MAX,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{103},
			//NAME
			NEWSKILL(SKILL_VETERAN,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{104},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR2,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			CAPTAIN,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{105},
			//NAME
			NEWSKILL(SKILL_ACE,	SKILL_REGULAR,		POTENTIAL_MAX,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{106},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN1,		POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{107},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_GOOD,		POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{108},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			MAJOR,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{109},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_ACE,		POTENTIAL_GOOD,		POTENTIAL_MAX),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{110},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_VERYGOOD,	POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{111},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_EXCELLENT,POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{112},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_REGULAR,		POTENTIAL_EXCELLENT),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{113},
			//NAME
			NEWSKILL(SKILL_REGULAR,		SKILL_REGULAR,	POTENTIAL_GOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{114},
			//NAME
			NEWSKILL(SKILL_ACE,		SKILL_REGULAR,	POTENTIAL_MAX,	POTENTIAL_GOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{115},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR,	POTENTIAL_VERYGOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{116},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_VETERAN,	POTENTIAL_GOOD,	POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{117},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_REGULAR1,	POTENTIAL_MAX,		POTENTIAL_VERYGOOD),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{118},
			//NAME
			NEWSKILL(SKILL_REGULAR,	SKILL_POOR,		POTENTIAL_VERYGOOD,		POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_MEDIUM,
			/*rank*/			LIEUTENANT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
		{
			/*name*/			{119},
			//NAME
			NEWSKILL(SKILL_REGULAR,SKILL_REGULAR,POTENTIAL_VERYGOOD,POTENTIAL_REGULAR),
			/*status*/			FLYING,
			/*morale*/			MORALE_GOOD,
			/*rank*/			SECLIEUTENANT_EXPERT,
			/*missionscompleted*/	0,							//MS 07Jun99
			/*NextFollAct*/			NF_Single,
			/*dayssincerest*/	0,
			/*kills*/			0,
			/*killslastmsn*/	0,
			/*daystorecover*/	0,
			/*aircraftnum*/		-1,
			/*decals*/			0
		},
	};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//nasty global!!!!!!!!!!!!!!!!!!!!!!!!!!!
//DeadCode JIM 22Aug96 SpecialEventBitField	specialeventbits;
//DeadCode JIM 22Aug96 NewsEventField			newsevent;

//MARK, this is the list of events structures					//MS 04Mar99

//MARK, this is the list of events structures					//MS 04Mar99

#define FIL(f1,f2)		FIL_##f1,FIL_##f2
#define FIL2(f1)		FIL_##f1,FIL_##f1
#define FILTO(f1)		FIL_##f1,FIL_##f1##_TO

#define BAN(f1,f2)		BANDIT##f1,BANDIT##f2
typedef	MigEvent ME;
//	enum	{	TARGET=1,		//goes for a target
//				DIRECT=2,		//goes direct - no decoy element - can't use immediately if barcap
//				BARCAP=4,		//goes for barcaps
//				LOCAL=8,		//stays in Yalu region
//				STARTSOUTH=16,	//starts south of MA
//				BIGTRAIN=32,	//Is a bigtrain. If selected first then all missions that day will be that train.
//				TRAIN_TARGET=33,//Big train with a target
//				SOUTH_TARGET=17,//starts south with a target
//				DIRECT_TARGET=3,//direct run to a target - cant get past CAP
//				LOCAL_TARGET=9	//local with a target
//				DECOY_TARGET=65	//run to target with decoy for CAP
//				DECLOC_TARGET=73//fly past CAP and ignore (decoy or local)
//			};

//Timing 0, don't hold, -1 hold until their predicted arrival time, 
//N*SECS100 hold for 'N' seconds after barcap arrives at target. -N*SECS100 for taking off before.
//PUT NUMBER OF SECONDS IN DIRECTLY

MigEvent	CampaignZero::migevents[]=
{//equate									//filea,fileb,			minaggr,detat,	formsize,	flags,			tactics,			threatlevels
/*SANCPAT*/			{FIL2(Sanctuary_Patrol),AL_TRAINING,-1,	8,16, 		ME::LOCAL,	TACTIC_SCATTER,		BAN(FIRING,FIRING)},
/*SAFEPAT*/			{FIL2(Safe_Patrol),		AL_TRAINING,120,	8,16, 		ME::LOCAL_TARGET,	TACTIC_SCATTER,		BAN(FIRING,FIRING)},
/*INTERSOUTH1*/		{FIL2(Intercept_Enemy1),	AL_DEFENSIVE,-1,4,16, 		ME::SOUTH_TARGET,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*STRAIGHTRUN*/		{FIL2(Intercept_Enemy1),	AL_ATTACKWEAKNESSES,-660,	6,12, 	ME::BARCAP,			TACTIC_SCATTER,	BAN(INDANGERRANGE,INDANGERRANGE)},
/*INTERCEPT1*/		{FIL2(Intercept_Enemy1),	AL_ATTACKWEAKNESSES,-660,	6,12, 	ME::BARCAP,			TACTIC_DIVEANDZOOM,	BAN(INDANGERRANGE,INDANGERRANGE)},
/*BOMBERS1*/		{FIL2(BigBomber1),			AL_DEFENSIVE,-660,	8,16, 	ME::DECLOC_TARGET,		TACTIC_DIVEANDZOOM,	BAN(INDANGERRANGE,INDANGERRANGE)},
//-----------------------------------------------------------------------------------------------------
/*INTERSOUTH2*/		{FIL2(Intercept_Enemy2),AL_DEFENSIVE,0,	8,32, 	ME::DIRECT_TARGET,	TACTIC_LINEASTERN,	BAN(INDANGERRANGE,INDANGERRANGE)},
/*INTERCEPT2*/		{FIL2(Intercept_Enemy2),AL_DEFENSIVE,-1,	8,32, 	ME::DECLOC_TARGET,	TACTIC_LINEASTERN,	BAN(INDANGERRANGE,INDANGERRANGE)},
/*WAITWEAK*/		{FIL2(Attack_At_Bingo_Fuel), AL_ATTACKWEAKNESSES,300,	4,32, 	ME::BARCAP,	TACTIC_DIVEANDZOOM,		BAN(ANYWHERE,ANYWHERE)},
/*CUTWEAK*/			{FIL2(Cut_Off_At_Bingo_Fuel),AL_ATTACKWEAKNESSES,-1,	4,32,	ME::BARCAP,	TACTIC_PINCER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
//-----------------------------------------------------------------------------------------------------
/*CONTRAILFOCUS*/	{FIL2(Contrail_Focus),	AL_DEFENSIVE,-120,8,32,		ME::DECLOC_TARGET,	TACTIC_PINCER,	BAN(INWEAPONSRANGE,FIRING)},
/*BOMBERS2*/		{FIL2(BigBomber2),		AL_DEFENSIVE,-240,	8,32, 	ME::DECLOC_TARGET,	TACTIC_LINEASTERN,		BAN(INDANGERRANGE,INDANGERRANGE)},
//-----------------------------------------------------------------------------------------------------
/*INTERSOUTH3*/		{FIL2(Intercept_Enemy3),AL_DEFENSIVE,-1,	8,32, 		ME::SOUTH_TARGET,	TACTIC_PINCER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*INTERCEPT3*/		{FIL2(Intercept_Enemy3),AL_DEFENSIVE,-1,	8,32, 		ME::DECLOC_TARGET,	TACTIC_PINCER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
//-----------------------------------------------------------------------------------------------------
/*THREELEVELS*/		{FIL2(Patrol3Levels),	AL_SPLITFORCE,-600,24,24,	ME::BARCAP,	TACTIC_DIVEANDZOOM,		BAN(ANYWHERE,ANYWHERE)},
/*BOMBERS3*/		{FIL2(BigBomber3),		AL_DEFENSIVE,-1,	16,32, 		ME::DECLOC_TARGET,	TACTIC_LINEABREAST,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
//-----------------------------------------------------------------------------------------------------
/*MOVINGROUND*/		{FIL2(Moving_Roundabout),	AL_DEFENSIVE,-1,	16,32, 		ME::BARCAP,	TACTIC_ROUNDABOUT,		BAN(ANYWHERE,ANYWHERE)},
/*STATICROUND*/		{FIL2(Static_Roundabout),AL_DEFENSIVE,-1,	16,32, 		ME::DIRECT_TARGET,	TACTIC_ROUNDABOUT,		BAN(ANYWHERE,ANYWHERE)},
//-----------------------------------------------------------------------------------------------------
/*ENDRUNDECOY*/		{FIL2(EndRunDecoy),		AL_DEFENSIVE,-1,8,32,	ME::DECLOC_TARGET,	TACTIC_DIVEANDZOOM,	BAN(INWEAPONSRANGE,INCOMBATRANGE)},
/*LOWSWEEP*/		{FIL2(Low_Sweep),		AL_DEFENSIVE,-200,8,16,ME::DECLOC_TARGET,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
//-----------------------------------------------------------------------------------------------------
/*MIGEV_UPPERCUT*/	{FIL2(Uppercut_Decoy),	AL_SPLITFORCE,-1,16,24, 		ME::BARCAP,			TACTIC_MULTIWAVE,	BAN(INDANGERRANGE,INDANGERRANGE)},
/*MIGEV_INTERCEPT4*/{FIL2(Intercept_Enemy4),AL_DEFENSIVE,-1,8,30, 	ME::DECLOC_TARGET,	TACTIC_MULTIWAVE,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
//-----------------------------------------------------------------------------------------------------
/*STAIRCASE*/		{FIL2(Staircase),		AL_SPLITFORCE,-1,8,16,	ME::BARCAP,	TACTIC_LINEASTERN,	BAN(INDANGERRANGE,INDANGERRANGE)},
/*SUPERIOR1*/		{FIL2(Intercept_Enemy3),AL_ATTACKWEAKNESSES,-1,32,60,	ME::DIRECT_TARGET,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
//-----------------------------------------------------------------------------------------------------
/*SLEDGEHAMMER*/	{FIL2(Intercept_Enemy1),AL_ATTACKWEAKNESSES,-1,	2,32, 		ME::BARCAP,	TACTIC_SCATTER,		BAN(FIRING,INENGAGERANGEOFFRIENDLY)},
/*SUPERIOR2*/		{FIL2(Intercept_Enemy4),AL_ATTACKWEAKNESSES,-1,	32,60, 		ME::DIRECT_TARGET,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
//-----------------------------------------------------------------------------------------------------
/*WESTTRAIN*/		{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*BIGTRAIN1*/		{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
//-----------------------------------------------------------------------------------------------------
/*BIGTRAIN2*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*BIGTRAIN3*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*BIGTRAIN4*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*BIGTRAIN5*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*BIGTRAIN6*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*EASTCOAST*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*CENTTRAIN*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*WPOORTRAIN*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*CAREFUL*/		{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*CAREFUL2*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)},
/*CONFRONT*/	{FIL2(BigTrain1),		AL_DEFENSIVE,-1,	56,56, 		ME::BIGTRAIN,	TACTIC_SCATTER,		BAN(INWEAPONSRANGE,INWEAPONSRANGE)}
};						 

//MissMan	Miss_Man ;
MissMan::CampaignName	MissMan::currcampaignnum	= MissMan::INTROCAMPAIGN;
CampaignBase			*MissMan::campaigntable[MAXCAMPAIGNNUM]
						={
							&CampaignF80_Def,							//RDH 19/03/99
							&CampaignF51_Def,							//RDH 19/03/99
							&CampaignF84_Def,							//RDH 19/03/99
							&CampaignF86_Def,							//RDH 19/03/99
							&CampaignSpring_Def,							//RDH 05Sep96 //RDH 19/03/99
							&CampaignScramble_Def		//scramble
						 };


Campaign&	Campaign::operator=(CampaignBase*	b)
{
	char	*s=(char*)b,
			*t=(char*)this;

	for (int i=b->garbage;i--;)
		*t++=*s++;
	for (i=sizeof(Campaign)-b->garbage;i--;)
		*t++=0;
	garbage=sizeof(Campaign);
	CampaignInit();
	return *this;
}

Campaign&	Campaign::operator=(CampaignZero&	b)
	{
		return operator=(&b);
	}

void	Campaign::CampaignInit()
{
	HidSkills s=SKILL_REGULARSKILL_VETERANPOTENTIAL_GOODPOTENTIAL_VERYGOOD;
	directives.ResetForNewCampaign();
	SupplyTree::ResetForNewCampaign();
	Dead_Stream.ClrWorldDead();
	Todays_Packages.WipeAll();

	for (int j = 0; j < PILOTS_PER_CAMPAIGN; j++)
	{
			Active_Pilots[j] = Active_Pilots_Init[j];
	}
	for (int sq=0;sq<PILOTABLE_SQUADRONS;sq++)						  //JIM 02/04/99
		for (int p=0;p<PILOTS_PER_SQUADRON;p++)
		{
			int pn=Math_Lib.rnd(PILOTS_PER_SQUADRON);
			while (Active_Pilots[sq*PILOTS_PER_SQUADRON+pn].aircraftnum!=-1)
				if (pn)
					pn--;
				else
					pn=PILOTS_PER_SQUADRON-1;
			Active_Pilots[sq*PILOTS_PER_SQUADRON+pn].aircraftnum=squad[sq].nextacnumber;
			squad[sq].nextacnumber+=1+((Math_Lib.rnd()+3000)>>(3+16));
		}

	/**/Sky.SetMissionConditions ();

	SupplyTree::SetNodeNationalities(InitialFront[2],InitialFront[1],InitialFront[0],frontdeltastrength);
	if (Miss_Man.currcampaignnum != MissMan::SCRAMBLECAMPAIGN)
		SupplyTree::NodeReview ();


	playeracnum = 0;
	switch (Miss_Man.currcampaignnum)
	{
		case MissMan::F80_CAMPAIGN:
		{
			playersquadron = SQ_F80;
			break;
		}
		case MissMan::F51_CAMPAIGN:
		{
			playersquadron = SQ_F51;
			break;
		}
		case MissMan::F84_CAMPAIGN:
		{
			playersquadron = SQ_F84;
			break;
		}
		case MissMan::F86_CAMPAIGN:
		{
			playersquadron = SQ_F86A;
			break;
		}
		case MissMan::SO51_CAMPAIGN:
		{
			playersquadron = SQ_F86A;
			break;
		}
	}
}
void	SupplyTree::ResetForNewCampaign()
{
	LoadCleanNodeTree();
}

void	SG_DirControl::ResetForNewCampaign()
{
	for (int i =0; i < MAXDIRECTIVES; i++)
	{
		directives[i].type = i;
	}
	directives[1].strikeac = 64;
	directives[0].fighterac = 32;
	autogen = true;
	autodisplay = true;
}

void Campaign::AddDebriefData(Debrief::SquadKills& src, Debrief::SquadKills& dest)
{
	for (Debrief::Types i = Debrief::REDAC; i < Debrief::TARG_MAX; i++)
		for (SquadSelect j = SQ_F86A; j < (SQ_B_NONFLYSPOT); j++)
			dest[j][i] += src[j][i];
}
void Campaign::ZeroDebriefData(Debrief::SquadKills& dest)
{
	for (Debrief::Types i = Debrief::REDAC; i < Debrief::TARG_MAX; i++)
		for (SquadSelect j = SQ_F86A; j < (SQ_B_NONFLYSPOT); j++)
			dest[j][i] = 0;
}

int Campaign::StoresDestroyedForNodeRoute(SupplyNode* node)
{
	int stores_destroyed=0;
	int i = 0;
	SupplyRoute* currroute=node->forward;
	while	(	(i <= NUM_OF_SUPPLYROUTES)
			)
	{
		while (currroute)
		{
			stores_destroyed += currroute->stores_destroyed;
			currroute = currroute->alternateroute;
		}
		currroute =	node->route[i];	  //accesses the non-existant route[3],but then quits
		i++;
	}
	return (stores_destroyed);
}

void Campaign::BattleLossesForNode(SupplyNode* node, int& redlosses, int& bluelosses)
{
	redlosses = 0;
	bluelosses = 0;
	TeamDef::Team blueforce;

	if	(node->supplyline->initiative==REDATTACKING)
		blueforce = TeamDef::HOME;
	else
		blueforce = TeamDef::AWAY;

	for (int i=0;i<node->supplyline->groundbattle.usedteams;i++)
	{
		if (node->supplyline->groundbattle.teamlist[i].team==blueforce)
			bluelosses += node->supplyline->groundbattle.teamlist[i].lastlosses;
		else
			redlosses += node->supplyline->groundbattle.teamlist[i].lastlosses;
	}
}

bool	Campaign::ChkEndCampaign()
{
	bool retval = false;
	wincamp = false;

	if (currdate > lastdate)
	{
		retval = true;
	}


	{
		int msn = curr_msn;
		if (currdate <= lastdate)
			msn = curr_msn - 1; //look at last mission except for last mission
		if (msn < 0)
			msn = 0;
//DEADCODE DAW 18/06/99 		SupplyNode* node = SupplyTree::FindSupplyNodeForNodeItem(missions[msn].target);
		SupplyTree::Supply2UID rel;
		SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(missions[msn].target,&rel);

		switch (Miss_Man.currcampaignnum)
		{
			case MissMan::F80_CAMPAIGN:
			{//truck interdiction
				curr_score += StoresDestroyedForNodeRoute(node);
				if (curr_score >= winscore)
				{
					/**/wincamp = true;
					retval = true;
				}

				break;
			}
			case MissMan::F51_CAMPAIGN:
			{
				int	redlosses;
				int bluelosses;
				BattleLossesForNode(node, redlosses, bluelosses);
				curr_score += redlosses;
				if (curr_score >= winscore)
				{
					/**/wincamp = true;
					retval = true;
				}

				break;
			}
			case MissMan::F84_CAMPAIGN:
			case MissMan::F86_CAMPAIGN:
			{
				int		currlevel=0;
				switch (rel)
				{
					case SupplyTree::S2U_MAIN:
						currlevel=node->attackstats.damagelevel;
					break;
					case SupplyTree::S2U_AF0:
					case SupplyTree::S2U_AF1:
					case SupplyTree::S2U_AF2:
						currlevel=SupplyTree::FindAirfieldForItem(missions[msn].target)->attackstats.damagelevel;
					break;
					case SupplyTree::S2U_ROUTE0:
					case SupplyTree::S2U_ROUTE1:
					case SupplyTree::S2U_ROUTE2:
						currlevel=node->route[rel-SupplyTree::S2U_ROUTE0]->attackstats.damagelevel;
					break;
				}	
				if (currlevel >= 40)							
					curr_score ++; 
				if (curr_score >= winscore)
				{
					/**/wincamp = true;
					retval = true;
				}
				break;
			}
			case MissMan::SO51_CAMPAIGN:
			{
				if	(		(SupplyTree::ChkSpringOffensiveOver())
						||	(currdate > lastdate)
					)
					retval = true;
				else
					retval = false;

				//decided later
				break;
			}
		}
	}

	return(retval);
}

void	Campaign::NextMission()
{
//init and test code
//DEADCODE RDH 24/03/99		/**/DisDayEntry(Debrief::NAME, UID_Null, Debrief::D_BritsArrive_H);


//DEADCODE RDH 12/02/99	currtime = HR11;

	Sky.SetMissionConditions ();
//DEADCODE RDH 19/06/99 	UpdateAllDis();
	UpdatePlayerLog();
	SupplyTree::UpDateAttacksStructure();
	SupplyTree::RemoveDestroyedStores();
	


//handle debrief counters and data
	AddDebriefData(debrief.lastperiod, debrief.cumulative);
	AddDebriefData(debrief.lastperiod, debrief.total);
//moved to EndBebrief to avoid date being wrong in debrief		  //RDH 12/06/99
//DEADCODE RDH 12/06/99 	if (debrief.currperiod == 2)
//DEADCODE RDH 12/06/99 	{
//DEADCODE RDH 12/06/99 		debrief.lastday = debrief.cumulative;
//DEADCODE RDH 12/06/99 		ZeroDebriefData(debrief.cumulative);
//DEADCODE RDH 12/06/99 	}
//DEADCODE RDH 12/06/99 	debrief.currperiod++;

	if (	SupplyTree::WestRoute.initiative==REDATTACKING
		||	SupplyTree::WestRoute.initiative==BLUEATTACKING)
		if (SupplyTree::WestRoute.groundbattle.usednodes)
		{
			SupplyTree::WestRoute.groundbattle.PostAttackDecisions();
			SupplyTree::WestRoute.PostAttackReports();
//DEADCODE DAW 18/06/99 			SupplyTree::WestRoute.groundbattle.NextAttackDecisions();
//DEADCODE DAW 18/06/99 			SupplyTree::WestRoute.NextAttackReports();
		}
	if (	SupplyTree::CentralRoute.initiative==REDATTACKING
		||	SupplyTree::CentralRoute.initiative==BLUEATTACKING)
		if (SupplyTree::CentralRoute.groundbattle.usednodes)
		{
			SupplyTree::CentralRoute.groundbattle.PostAttackDecisions();
			SupplyTree::CentralRoute.PostAttackReports();
//DEADCODE DAW 18/06/99 			SupplyTree::CentralRoute.groundbattle.NextAttackDecisions();
//DEADCODE DAW 18/06/99 			SupplyTree::CentralRoute.NextAttackReports();
		}
	if (	SupplyTree::EastRoute.initiative==REDATTACKING
		||	SupplyTree::EastRoute.initiative==BLUEATTACKING)
		if (SupplyTree::EastRoute.groundbattle.usednodes)
		{
			SupplyTree::EastRoute.groundbattle.PostAttackDecisions();
			SupplyTree::EastRoute.PostAttackReports();
//DEADCODE DAW 18/06/99 			SupplyTree::EastRoute.groundbattle.NextAttackDecisions();
//DEADCODE DAW 18/06/99 			SupplyTree::EastRoute.NextAttackReports();
		}

//moved to EndBebrief to avoid date being wrong in debrief		  //RDH 12/06/99
//DEADCODE RDH 12/06/99 	if	(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
//DEADCODE RDH 12/06/99 	{
//DEADCODE RDH 12/06/99 		if (debrief.currperiod >=3)
//DEADCODE RDH 12/06/99 		{
//DEADCODE RDH 12/06/99 			NextDay();
//DEADCODE RDH 12/06/99 			debrief.currperiod = 0;
//DEADCODE RDH 12/06/99 			debrief.currlogday++;
//DEADCODE RDH 12/06/99 		}
//DEADCODE RDH 12/06/99 	}else
//DEADCODE RDH 12/06/99 	{
//DEADCODE RDH 12/06/99 		NextDay();
//DEADCODE RDH 12/06/99 		debrief.currperiod = 0;
//DEADCODE RDH 12/06/99 		debrief.currlogday++;
//DEADCODE RDH 12/06/99 		currdate -= SECSPERDAY;
//DEADCODE RDH 12/06/99 		if (currdate < lastdate)
//DEADCODE RDH 12/06/99 		{
//DEADCODE RDH 12/06/99 			curr_msn++;
//DEADCODE RDH 12/06/99 			currdate =	 missions[curr_msn].msn_date;
//DEADCODE RDH 12/06/99 
//DEADCODE RDH 12/06/99 		}else
//DEADCODE RDH 12/06/99 			currdate += SECSPERDAY;
//DEADCODE RDH 12/06/99 
//DEADCODE RDH 12/06/99 	}




}
void Campaign::SwapPilot(int groupnum, int src,int dest)
{
	PilotType tmppilot;
	tmppilot = /**/Active_Pilots[24*groupnum+src];
	/**/Active_Pilots[24*groupnum+src] = /**/Active_Pilots[24*groupnum+dest];
	/**/Active_Pilots[24*groupnum+dest] = tmppilot;
}
void Campaign::SwapElement(int groupnum, int src, int dest)
{
	for (int i = 0;i < 2; i++)
		SwapPilot(groupnum, src+i, dest+i);

}
void Campaign::SwapFlight(int groupnum, int src, int dest)
{
	for (int i = 0;i < 4; i +=2)
		SwapElement(groupnum, src+i, dest+i);

}
void	Campaign::ModifySkill(int groupnum, int daysonduty)
{
	for (int i = 0;i < 4; i ++)
	{
		int maxchange = (12 - daysonduty)/4;
		if (maxchange < 0)
			maxchange = 0;
		if (maxchange > 0)
		{
			PilotType& pilot=/**/Active_Pilots[24*groupnum+i];
			FP change = pilot.BigFlyingPotential() - pilot.BigFlyingSkill();
			if (change > 0)
			{
				change = 0.5 + change * pilot.morale/MORALE_TOPMORALE;
				pilot.SetBigFlySkill(((int)pilot.BigFlyingSkill() + (int)change));
				
			}
			change = pilot.BigCombatPotential() - pilot.BigCombatSkill();
			if (change > 0)
			{
				change = 0.5 + change * pilot.morale/MORALE_TOPMORALE;
				pilot.SetBigCombSkill(pilot.BigCombatSkill() +(int)change);
			}

		}
	}

}
void	Campaign::RotateFlightsCheck()
{
	int daysincelastrotate;
	for (SquadSelect j = SQ_F86A; j < (SQ_B_NONFLYABLE); j++)
	{
		daysincelastrotate = currdate - /**/squad[j].lastrotatedate;
		daysincelastrotate = daysincelastrotate/SECSPERDAY;
		int freq = /**/squad[j].rotatefreq;
		if	(		(freq)
				&&	(daysincelastrotate >= freq)
			)
		{
			ModifySkill(j, daysincelastrotate*4);
			SwapFlight(j, 0, 4);
			SwapFlight(j, 4, 8);
			SwapFlight(j, 8, 12);
			SwapFlight(j, 12, 16);
			SwapFlight(j, 16, 20);
//DEADCODE JIM 13/07/99 			for (int k=0; k <16;k++)
//DEADCODE JIM 13/07/99 				/**/Active_Pilots[24*j+k].dayssincerest++;
			for (int k=16; k <23;k++)
				/**/Active_Pilots[24*j+k].dayssincerest = 0;

			/**/squad[j].lastrotatedate = currdate;

		}

	}
}
void	Campaign::ReplenishAcStock()
{
	int min = 20;
	int minsquad;
	for (int squad = 0; squad < 5; squad++)
	{
		if (/**/this->squad[squad].ac_total_avail < min)
		{
			minsquad = squad;
			min = /**/this->squad[squad].ac_total_avail;
		}
	}
	int acrequired = MAX_NUM_AC_IN_SQUADRON - /**/this->squad[minsquad].ac_total_avail;
	if (acrequired > 4)
		acrequired = 4;
	if (acrequired > 0)
	{
		/**/this->squad[minsquad].ac_total_avail += acrequired;
		DisDayEntry(Debrief::NAME, UID_BrRdYalu, Debrief::T_Replenish_H);

	}

}
void	Campaign::RotateMiGSquadron(int squad)
{
	/**/migsquad[squad] = /**/migsquad[/**/nextsquadtocopy];
	/**/nextsquadtocopy++;
	if	(/**/nextsquadtocopy >= MAXMIGSQUADRONS)
	{
		/**/nextsquadtocopy = WRAPMIGSQUADRONS;
		//update startdates
		//first 3 weeks hence to allow last squadron its fulltime
		//then all 2 weeks so they come around a bit faster
		/**/migsquad[WRAPMIGSQUADRONS].startdate = currdate + SECSPERDAY *21;
		for (int i = (WRAPMIGSQUADRONS+1); i < MAXMIGSQUADRONS;i++)
			/**/migsquad[i].startdate = currdate + SECSPERDAY *21 +
									(WRAPMIGSQUADRONS+2 - i) * SECSPERDAY * 14;

	}
//DEADCODE RDH 21/06/99 		if	(/**/migsquad[squad].agglevel == AL_TRAINING)
			/**/DisDayEntry(Debrief::NAME, UID_Null, Debrief::T_SquadRotate_H);
}
void	Campaign::ChkRotateMiGSquadrons()
{
	if (/**/migsquad[0].aclosses > (/**/migsquad[0].ac_total_avail*2))//DAW 02Sep99
		RotateMiGSquadron(0);
	if (/**/migsquad[1].aclosses > (/**/migsquad[1].ac_total_avail*2))//DAW 02Sep99
		RotateMiGSquadron(1);
	if	(/**/migsquad[/**/nextsquadtocopy].startdate <= currdate)
	{
		if (/**/migsquad[0].aclosses > /**/migsquad[1].aclosses)
			RotateMiGSquadron(0);
		else
			RotateMiGSquadron(1);

	}

}
void	Campaign::ModifyMiGAggressionLevel(int squad)
{
	if	(/**/migsquad[squad].agglevel < AL_MAX)
	{
		int cycleday = (currdate - migsquad[squad].startdate)%(SECSPERDAY*4);
		if (	(!cycleday) && (Math_Lib.rnd(2)))
			migsquad[squad].agglevel = (tAggressionLevel)((int)migsquad[squad].agglevel + (int)AL_STAGE);
	}else if	(		(migsquad[squad].aclosseslast >= 10)
			&&	(migsquad[squad].agglevel >	AL_MIN)
		 )
	{
		migsquad[squad].agglevel = (tAggressionLevel)((int)migsquad[squad].agglevel - (int)AL_STAGE);
		if	(migsquad[squad].agglevel == AL_TRAINING)
			DisDayEntry(Debrief::NAME, UID_Null, Debrief::T_StoodDown_H);
	}
}
void	Campaign::NextDay()
{
	currdate += SECSPERDAY;
	if (currdate == MAR5th1951)
		/**/DisDayEntry(Debrief::NAME, UID_Null, Debrief::D_BritsArrive_H);
	if (currdate == (OCT8th1950 + SECSPERDAY))						  //RDH 14/06/99
		/**/DisDayEntry(Debrief::NAME, UID_Null, Debrief::D_AlJolson_H);

	int i;
	ChkRotateMiGSquadrons();
	for (i = 0; i < 2; i++)
		ModifyMiGAggressionLevel(i);
//rdh 9/7 edit to replenish according to campaign
	if (Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
	{
		int currday = currdate%(SECSPERDAY*2);							  //RDH 21/06/99
		if (currday == 0)
			ReplenishAcStock();
		else
		{
			bool noaircraft = true;
			for (int squad = 0; squad < 5; squad++)
			{
				if (/**/this->squad[squad].ac_total_avail >= 4)
					noaircraft = false;
			}
			if (noaircraft)
				this->squad[SQ_F51].ac_total_avail = 4;		//give them 4 mustangs as minimum
		}
	}else
	{
		int squad;
		switch (Miss_Man.currcampaignnum)
		{
			case MissMan::F80_CAMPAIGN:
			{//truck interdiction
				squad = SQ_F80;
				break;
			}
			case MissMan::F51_CAMPAIGN:
			{
				squad = SQ_F51;
				break;
			}
			case MissMan::F84_CAMPAIGN:
			{
				squad = SQ_F84;
				break;
			}
			case MissMan::F86_CAMPAIGN:
			{
				squad = SQ_F86A;
				if (this->squad[SQ_F86B].ac_total_avail < 16)	
					this->squad[SQ_F86B].ac_total_avail = 16;	
				break;
			}
		}
		if (this->squad[squad].ac_total_avail < 16)	
			this->squad[squad].ac_total_avail = 16;	
	}

	RotateFlightsCheck();
	SupplyTree::NodeReview (); 
	Dead_Stream.ReviveWorld();

	if (Miss_Man.currcampaignnum == Miss_Man.F86_CAMPAIGN)							  //RDH 14/06/99
	{																  //RDH 14/06/99
		directives.B29avail = true;									  //RDH 14/06/99 //RDH 14/06/99
	}else															  //RDH 14/06/99
	{																  //RDH 14/06/99
		int B29casualties=debrief.total[SQ_B29].TotalLosses();		  //RDH 14/06/99
		if (B29casualties-10>debrief.currlogday)	//stop the B29s
		{
			if (directives.dayssinceB29>=0)
				DisDayEntry(Debrief::NAME, 0, Debrief::T_Bombers00_H);
			directives.dayssinceB29=-4;
		}
		if (directives.B29avail)
			directives.dayssinceB29 = 0;
		else
		{
			directives.dayssinceB29++;
			if (directives.dayssinceB29==0)
			{
				directives.dayssinceB29=4;
				DisDayEntry(Debrief::NAME, 0, Debrief::T_Bombers01_H);
			}
		}
		if (directives.dayssinceB29>4)
			directives.B29avail = true;
		else
			directives.B29avail = false;
	}
//DEADCODE RDH 01/06/99 	for (i=0;i<PILOTABLE_SQUADRONS;i++)
//DEADCODE RDH 01/06/99 	{
//DEADCODE RDH 01/06/99 		if	(squad[i].movetoairfieldindex != -1)
//DEADCODE RDH 01/06/99 		{
//DEADCODE RDH 01/06/99 			squad[i].airfieldindex = /**/squad[i].movetoairfieldindex;
//DEADCODE RDH 01/06/99 			squad[i].movetoairfieldindex = -1;
//DEADCODE RDH 01/06/99 		}
//DEADCODE RDH 01/06/99 	}

//should be later
//	EndDebrief();


}
void	Campaign::ZeroDisDay()
{
	int j = 0;
	while	(j < Debrief::DISISITFORTODAY)

	{
		debrief.disday[j].typeflag = 0;
		debrief.disday[j].msgowner = 0;
		debrief.disday[j].msgtextid = 0;
		j++;
	}
	int pack,wave,group;
	bool found=	Todays_Packages.GetPackage(pack,wave,group,MMC.playersquadron,MMC.playeracnum/4);
	if (found)
	{
		int day = MMC.debrief.currlogday;
		int period = MMC.debrief.currperiod;
		switch (group)
		{
		case 0:
			debrief.playerlog[day][period].role=Todays_Packages[pack].duty;
		break;
		case 1:
			debrief.playerlog[day][period].role=DC_WW;
		break;
		case 2:
			debrief.playerlog[day][period].role=DUTYESCORT;
		break;
		}

		debrief.playerlog[day][period].target1=Todays_Packages[pack].packagetarget;
		debrief.playerlog[day][period].pilotsquad=SquadSelect(MMC.playersquadron);

		ZeroDebriefData(debrief.lastperiod);

		debrief.barcapkills=0;
		debrief.barcaplost=0;

		for (int i=SQ_MIG15;i<SQ_VEHICLES;i++)
		{
			debrief.playerqmcounts[SquadSelect(i)]=0;
		}	
		debrief.playertotals[(SquadSelect)MMC.playersquadron][Debrief::SORTIES]++;	  //JIM 13/07/99
//		UByte		role;
//		UByte		dummy;
//		UByte		kills;	//fill in later....
//		ONLYFIELD(UByte,	SquadSelect,pilotsquad);
//		ONLYFIELD(UWord,	UniqueID, 	target1);
//		ONLYFIELD(UWord,	UniqueID,	target2);
	}

}
void	Campaign::UpdateAllDis()
{
	{
		int i = 0;
		while	(		(i < Debrief::DISISALLTOOMUCH)
					&&	(debrief.alldis[i].msgtextid != 0)
				)
				i++;
		if (i >= Debrief::DISISALLTOOMUCH)
			i = 0;
		
		if (debrief.currperiod == 0)
		{//don't keep adding date heading if no message is added 
			int previ = i;
			previ--;
			if (previ < 0)
				previ = Debrief::DISISALLTOOMUCH-1;
			if (debrief.alldis[previ].typeflag == Debrief::DATE)
				i = previ;
			debrief.alldis[i].typeflag = Debrief::DATE;
			debrief.alldis[i].msgowner = debrief.currlogday;
			debrief.alldis[i].msgtextid = -1;
			i++;
			if (i >= Debrief::DISISALLTOOMUCH)
				i = 0;
		}

		int j = 0;
		while	(		(j < Debrief::DISISITFORTODAY)
					&&	(debrief.disday[j].msgtextid != 0)
				)
		{
			if (debrief.disday[j].typeflag != Debrief::DISCARDTARGUID)
			{
				debrief.alldis[i] = debrief.disday[j];
				i++;
				if (i >= Debrief::DISISALLTOOMUCH)
					i = 0;
			}
			j++;
		}
	}
}
void	Campaign::UpdatePlayerLog()
{

	{
		int day = MMC.debrief.currlogday;
		int period = MMC.debrief.currperiod;
		for (int i=SQ_MIG15;i<SQ_VEHICLES;i++)
		{
			debrief.playerlog[day][period].kills+=
				debrief.playerqmcounts[SquadSelect(i)];
		}
		if (debrief.playerlog[day][period].kills > 0)				  //JIM 13/07/99
			 debrief.playertotals[(SquadSelect)playersquadron][Debrief::COMBATS]++; //JIM 13/07/99
	}
}

FileNum	Campaign::FindSmacker(int index)
{
	for (int i=0; i < SupplyTree::MAX_DISSMACKERS; i++)
	{
		if (debrief.disday[index].msgtextid == SupplyTree::dissmackers[i].idtext)
			return (SupplyTree::dissmackers[i].file);
	}
	return (FIL_NULL);

}

void	Campaign::DisDayEntry(Debrief::TypeFlag type, int msgowner, int msgtextid)
{
	int i = 0;
	while	(		(i < Debrief::DISISITFORTODAY)
				&&	(debrief.disday[i].msgtextid != 0)
			)
	{
		if (	debrief.disday[i].msgtextid==msgtextid 
			&&	debrief.disday[i].typeflag == type
			&&	debrief.disday[i].msgowner == msgowner)
			return;
		i++;
	}
	//make sure we get last one requested							  //RDH 28/05/99
	if (i >= Debrief::DISISITFORTODAY)
		i = Debrief::DISISITFORTODAY - 1;
//DEADCODE RDH 28/05/99 	if (i < Debrief::DISISITFORTODAY)
//DEADCODE RDH 28/05/99 	{
		debrief.disday[i].typeflag = type;
		debrief.disday[i].msgowner = msgowner;
		debrief.disday[i].msgtextid = msgtextid;
		FileNum smack = FindSmacker(i);
		if (smack)
		{
			msgwithsmacker =  (int)msgtextid;
			smacker = smack;
		}
}
void Campaign::MakeNewPilot(int pilot)
{	//5*24=120
	Active_Pilots[pilot] = Active_Pilots_Init[Math_Lib.rnd(120)];
	Active_Pilots[pilot].name.nameref = Math_Lib.rnd(150);
	Active_Pilots[pilot].name.initial1= Math_Lib.rnd(20)+'A';
	Active_Pilots[pilot].name.initial2= Math_Lib.rnd(20)+'A';
	Active_Pilots[pilot].status = NOTFLYING;
}

void Campaign::KillPilot(int pilot, pilotstatus status)
{
	
	if (dead_pilots[nextdeadpilot].lastdate != 0)
		 ripdate = dead_pilots[nextdeadpilot].lastdate;
	dead_pilots[nextdeadpilot].name = Active_Pilots[pilot].name;
	dead_pilots[nextdeadpilot].kills = Active_Pilots[pilot].kills;
	dead_pilots[nextdeadpilot].rank = Active_Pilots[pilot].rank;
	dead_pilots[nextdeadpilot].lastdate = currdate;

	dead_pilots[nextdeadpilot].status =  status;

	MakeNewPilot(pilot);

	nextdeadpilot++;
	if	(nextdeadpilot >= CASUALTYLIST)
		nextdeadpilot = 0;
}

void	Campaign::MoveDeadPilots()
{
		for(int pilot=0;pilot<119;pilot++)
		{  	
			if (Active_Pilots[pilot].status >= IS_DEAD)
			{
				int groupnum = pilot/24;
				if (groupnum < 5)
					MMC.squad[groupnum].ac_total_avail--;
				if (MMC.squad[groupnum].ac_total_avail < 0)
					MMC.squad[groupnum].ac_total_avail = 0;
				if (pilot != (playersquadron*24+playeracnum))
					//don't move the player, picked up later and means an end campaign
						 KillPilot(pilot, Active_Pilots[pilot].status);
			}
		}

}
void	Campaign::EndDebrief()
{
#ifndef	MIG_DEMO_VER
//moved from NextMission to avoid date being wrong in debrief		  //RDH 12/06/99
	for (int migsq=0;migsq<2;migsq++)									  //JIM 06/07/99
	{
		migsquad[migsq].aclosses+=migsquad[migsq].aclosseslast;
		if (migsquad[migsq].aclosseslast<=8)
		{
			if (migsquad[migsq].morale<MORALE_TOPMORALE)
				migsquad[migsq].morale=MoraleType(migsquad[migsq].morale+1);
		}
		else
			if (migsquad[migsq].ac_total_avail>10)
				migsquad[migsq].ac_total_avail-=(migsquad[migsq].aclosseslast-8)/3;//11==>1 14==>2
		migsquad[migsq].aclosseslast=0;								  //JIM 01/09/99
		if (migsquad[migsq].maxevent<MIGEV_MAX-1)
			if (Math_Lib.rnd(15)==0) //ave 7
				migsquad[migsq].maxevent=RedEvents(migsquad[migsq].maxevent+1);
	}


	if (	SupplyTree::WestRoute.initiative==REDATTACKING			  //JIM 18/06/99
		||	SupplyTree::WestRoute.initiative==BLUEATTACKING)
		if (SupplyTree::WestRoute.groundbattle.usednodes)
		{
//			SupplyTree::WestRoute.PostAttackReports();
//			SupplyTree::WestRoute.groundbattle.PostAttackDecisions();
			SupplyTree::WestRoute.groundbattle.NextAttackDecisions();
			SupplyTree::WestRoute.NextAttackReports();
		}
	if (	SupplyTree::CentralRoute.initiative==REDATTACKING
		||	SupplyTree::CentralRoute.initiative==BLUEATTACKING)
		if (SupplyTree::CentralRoute.groundbattle.usednodes)
		{
//			SupplyTree::CentralRoute.PostAttackReports();
//			SupplyTree::CentralRoute.groundbattle.PostAttackDecisions();
			SupplyTree::CentralRoute.groundbattle.NextAttackDecisions();
			SupplyTree::CentralRoute.NextAttackReports();
		}
	if (	SupplyTree::EastRoute.initiative==REDATTACKING
		||	SupplyTree::EastRoute.initiative==BLUEATTACKING)
		if (SupplyTree::EastRoute.groundbattle.usednodes)
		{
//			SupplyTree::EastRoute.PostAttackReports();
//			SupplyTree::EastRoute.groundbattle.PostAttackDecisions();
			SupplyTree::EastRoute.groundbattle.NextAttackDecisions();
			SupplyTree::EastRoute.NextAttackReports();
		}

	MoveDeadPilots();			//rdh 12/7
	
	if (debrief.currperiod == 2)
	{
		debrief.lastday = debrief.cumulative;
		ZeroDebriefData(debrief.cumulative);
	}
	debrief.currperiod++;
 	if	(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
	{
		if (debrief.currperiod >=3)
		{
			NextDay();
			debrief.currperiod = 0;
			debrief.currlogday++;
		}
	}else
	{
		NextDay();
		debrief.currperiod = 0;
		debrief.currlogday++;
		currdate -= SECSPERDAY;
		if (currdate < lastdate)
		{
			curr_msn++;
			currdate =	 missions[curr_msn].msn_date;

		}else
			currdate += SECSPERDAY;

	}
//above moved from NextMission to avoid date being wrong in debrief		  //RDH 12/06/99

	Persons4::StartUpMapWorld();									  //RDH 28/06/99

	for (int i=0;i<PILOTABLE_SQUADRONS;i++)
	{
		if	(squad[i].movetoairfieldindex != -1)
		{
			squad[i].airfieldindex = /**/squad[i].movetoairfieldindex;
			squad[i].movetoairfieldindex = -1;
		}
	}

	Todays_Packages.hipack = 0;
	Todays_Packages.hiwave = 0;
	Todays_Packages.higroup = 0;
	Todays_Packages.hiwp = UID_Null;

	Todays_Packages.DeleteNonRedoPackages();
	if	(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
	{

		if (debrief.currperiod == 0)
			currtime = MORNINGPERIODSTART;
		if (debrief.currperiod == 1)
			currtime = MIDDAYPERIODSTART;
		if (debrief.currperiod == 2)
			currtime = AFTERNOONPERIODSTART;
		Todays_Packages.UpDatePackageTimes();

		if (directives.autogen)
		{
			DirControl	dir_ctrl;
			dir_ctrl.LoadDirectiveChanges();
			dir_ctrl.AllocateAc();
			dir_ctrl.SetPackagesFromDirectives();
			dir_ctrl.SaveDirectiveChanges();
		}
	}else
	{
//DEADCODE RDH 01/07/99 		if (MMC.missions[MMC.curr_msn].msn_time> AFTERNOONPERIODSTART)
//DEADCODE RDH 01/07/99 			MMC.currtime = AFTERNOONPERIODSTART;
//DEADCODE RDH 01/07/99 		else if (MMC.missions[MMC.curr_msn].msn_time > MIDDAYPERIODSTART)
//DEADCODE RDH 01/07/99 			MMC.currtime = MIDDAYPERIODSTART;
//DEADCODE RDH 01/07/99 		else if (MMC.missions[MMC.curr_msn].msn_time > MORNINGPERIODSTART)
//DEADCODE RDH 01/07/99 			MMC.currtime = MORNINGPERIODSTART;
	


		DirControl	dir_ctrl;
		dir_ctrl.MakeMiniCampaignMission();
	}
//DEADCODE RDH 12/02/99	if (debrief.currperiod == 0)
//DEADCODE RDH 12/02/99		currtime = MORNINGPERIODSTART;
//DEADCODE RDH 12/02/99	if (debrief.currperiod == 1)
//DEADCODE RDH 12/02/99		currtime = MIDDAYPERIODSTART;
//DEADCODE RDH 12/02/99	if (debrief.currperiod == 2)
//DEADCODE RDH 12/02/99		currtime = AFTERNOONPERIODSTART;

//DeadCode RDH 12Jul99 	MoveDeadPilots();
	SupplyTree::SetNodeNationalities(
		SupplyTree::EastRoute.frontline->associated_item,
		SupplyTree::CentralRoute.frontline->associated_item,
		SupplyTree::WestRoute.frontline->associated_item,0);
#endif
}

void	Campaign::SetCurrMission (MissionType* newmission)
{

//	PilotType	temppilot;
//	SWord i,j;
//	currmission = newmission;
 //	SWord	sinwind,coswind;
//rdh	weathernum =	currmission->weathernum;
//	wind.speed =	currmission->windspeed;
//	wind.direction =	currmission->winddirection;
//	Math_Lib.high_sin_cos((ANGLES)(wind.direction + ANGLES_180Deg),sinwind,coswind);
//	wind.velx = wind.speed * sinwind/ ANGLES_FRACT;
//	wind.velz = wind.speed * coswind/ ANGLES_FRACT;

//	currdate = currmission->missiondate;
//	currtime = currmission->timeofday;

//	switch (Miss_Man.currcampaignnum)
//	{
//		case MissMan::PEACETALKCAMPAIGN:
//			{
//DeadCode RDH 17Feb97				{
//DeadCode RDH 17Feb97 //DeadCode JIM 06Nov96					dawntime = MAYDAWNTIME;
//DeadCode RDH 17Feb97 //DeadCode JIM 06Nov96					dusktime = MAYDUSKTIME;
//DeadCode RDH 17Feb97				}else
//DeadCode RDH 17Feb97				{
//					dawntime = OCTOBERDAWNTIME;
//					dusktime = OCTOBERDUSKTIME;
//DeadCode RDH 17Feb97				}
//				break;
//			}
//		case MissMan::INTROCAMPAIGN:
//			{
//DeadCode JIM 06Nov96				dawntime = MARCHDAWNTIME;
//DeadCode JIM 06Nov96				dusktime = MARCHDUSKTIME;
//				break;
//			}
//		case MissMan::SO51_CAMPAIGN:
//			{
//killed 24/6/98
//				for (i=0;i<MAX_PACKAGE_NUM;i++)
//					 package[i].familytype = PFT_NULL;


//DeadCode JIM 06Nov96				dawntime = NOVEMBERDAWNTIME;
//DeadCode JIM 06Nov96				dusktime = NOVEMBERDUSKTIME;
//				break;
//			}
//	}
//DEAD	playerbfield =	newmission->playerbf;


//killed 24/6/98
//	if (	(Miss_Man.currcampaignnum != MissMan::SO51_CAMPAIGN)//RDH 02Apr97
//		)														//RDH 02Apr97
//	{															//RDH 02Apr97
//		SLong acleft =	newmission->numofsquadronac;
//		for (j=0;j<MAXPLAYERWINGS;j++)							//RDH 02Apr97
//		{
//			for (i=0;i<MAX_FLIGHT_NUM;i++)							//RDH 02Apr97
//			{														//RDH 02Apr97
//				if (acleft >= newmission->numofflightac)
//				{
//					squad[j].flightnum [i] = newmission->numofflightac;//RDH 02Apr97
//					acleft -= newmission->numofflightac;
//				}else
//				{
//					squad[j].flightnum [i] = acleft;
//					acleft = 0;
//				}
//
//				squad[j].formationnum [i] = newmission->formationtypeindex;//RDH 02Apr97
//			}
//			 squad[j].squadronform = newmission->formationtypeindex;//RDH 02Apr97
//		}
//	}															//RDH 02Apr97
}
