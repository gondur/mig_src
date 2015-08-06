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
//Filename       intrmiss.cpp
//System         
//Author         R. Hyde 
//Date           Fri 10 Jan 1997
//Description    
//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 #include	"dosdefs.h"											//DAW 29Feb96
//DEADCODE JIM 25/03/99 #define F_SOUNDS												//DAW 05Aug96
//DEADCODE JIM 25/03/99 #define F_COMMON												//DAW 05Aug96
//DEADCODE JIM 25/03/99 #include	"files.g"	//NON-GRAPHICS
//DEADCODE JIM 25/03/99 #include	"missman2.h"										//DAW 17Jan96
//DEADCODE JIM 25/03/99 //DeadCode JIM 14May96 #include	"ui.h"												//JIM 30Apr96
//DEADCODE JIM 25/03/99 #include	"uniqueid.h"
//DEADCODE JIM 25/03/99 #include	"mytime.h"											//RDH 08Jan96
//DEADCODE JIM 25/03/99 //DeadCode JIM 22Apr97 #include	"UID.G"
//DEADCODE JIM 25/03/99 #include	"speed.h"											//MS 20Nov96
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 WpSetType WPNullSet =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*MainObjective*/	UID_Null,
//DEADCODE JIM 25/03/99 	/*SubObjective*/	UID_Null,
//DEADCODE JIM 25/03/99 	/*WP1*/				UID_Null,
//DEADCODE JIM 25/03/99 	/*WP2*/				UID_Null,
//DEADCODE JIM 25/03/99 	/*WP3*/				UID_Null
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 WpListType f51airevacList =
//DEADCODE JIM 25/03/99 {	/*NoOfEntries*/	1,
//DEADCODE JIM 25/03/99 			{&WPNullSet}
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 BfTypeList DefaultList = 
//DEADCODE JIM 25/03/99 {	/*NoOfEntries*/	2,
//DEADCODE JIM 25/03/99 			{BF_F51AIREVAC,BF_F51AIREVAC}
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType F51AirEvac =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_GAMEINTRO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXT_NULL,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXT_F51AIREVAC,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR18,		 
//DEADCODE JIM 25/03/99 	/*wplist*/		&f51airevacList,
//DEADCODE JIM 25/03/99 	/*playerbf*/		BF_F51AIREVAC,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	8,			 
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,			 
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		CLOUDAT10000FT,
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL//TITLELOADGAME
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType F51AttackNKField =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_GAMEINTRO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXT_NULL,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXT_F51ATTACKNKFIELD,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR18,		 
//DEADCODE JIM 25/03/99 	/*wplist*/		&f51airevacList,
//DEADCODE JIM 25/03/99 	/*playerbf*/		BF_F51ATTACKNKFIELD,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	8,			 
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,			 
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		CLOUDAT10000FT,
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL//TITLELOADGAME
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType F51AttackNKColumn =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_GAMEINTRO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXT_NULL,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXT_F51ATTACKNKCOLUMN,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR18,		 
//DEADCODE JIM 25/03/99 	/*wplist*/		&f51airevacList,
//DEADCODE JIM 25/03/99 	/*playerbf*/		BF_F51ATTACKNKCOLUMN,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	8,			 
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,			 
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		CLOUDAT10000FT,
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL//TITLELOADGAME
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType F80AttackNKHQ =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_GAMEINTRO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXT_NULL,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXT_F80ATTACKNKHQ,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR18,		 
//DEADCODE JIM 25/03/99 	/*wplist*/		&f51airevacList,
//DEADCODE JIM 25/03/99 	/*playerbf*/		BF_F80ATTACKNKHQ,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	8,			 
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,			 
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		CLOUDAT10000FT,
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL//TITLELOADGAME
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType F80BowlingAlley =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_GAMEINTRO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXT_NULL,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXT_F80BOWLINGALLEY,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR18,		 
//DEADCODE JIM 25/03/99 	/*wplist*/		&f51airevacList,
//DEADCODE JIM 25/03/99 	/*playerbf*/		BF_F80BOWLINGALLEY,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	8,			 
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,			 
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		CLOUDAT10000FT,
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL//TITLELOADGAME
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType F80PusanBreakout =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_GAMEINTRO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXT_NULL,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXT_F80PUSANBREAKOUT,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR18,		 
//DEADCODE JIM 25/03/99 	/*wplist*/		&f51airevacList,
//DEADCODE JIM 25/03/99 	/*playerbf*/		BF_F80PUSANBREAKOUT,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	8,			 
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,			 
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		CLOUDAT10000FT,
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL//TITLELOADGAME
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType F86BouncedbyMiGs =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_GAMEINTRO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXT_NULL,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXT_F86BOUNCEDBYMIGS,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR18,		 
//DEADCODE JIM 25/03/99 	/*wplist*/		&f51airevacList,
//DEADCODE JIM 25/03/99 	/*playerbf*/		BF_F86BOUNCEDBYMIGS,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	8,			 
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,			 
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		CLOUDAT10000FT,
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL//TITLELOADGAME
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType F86FighterSweep =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_GAMEINTRO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXT_NULL,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXT_F86FIGHTERSWEEP,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR18,		 
//DEADCODE JIM 25/03/99 	/*wplist*/		&f51airevacList,
//DEADCODE JIM 25/03/99 	/*playerbf*/		BF_F86FIGHTERSWEEP,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	8,			 
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,			 
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		CLOUDAT10000FT,
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL//TITLELOADGAME
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType F84YaluBridge =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_GAMEINTRO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXT_NULL,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXT_F84YALUBRIDGE,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR18,		 
//DEADCODE JIM 25/03/99 	/*wplist*/		&f51airevacList,
//DEADCODE JIM 25/03/99 	/*playerbf*/		BF_F84YALUBRIDGE,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	8,			 
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,			 
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		CLOUDAT10000FT,
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL//TITLELOADGAME
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 SingleMission	Intro_Missions [] =
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 	{
//DEADCODE JIM 25/03/99 		{&F51AirEvac},
//DEADCODE JIM 25/03/99 		{&F51AttackNKField},
//DEADCODE JIM 25/03/99 		{&F51AttackNKColumn},
//DEADCODE JIM 25/03/99 		{&F80AttackNKHQ},
//DEADCODE JIM 25/03/99 		{&F80BowlingAlley},
//DEADCODE JIM 25/03/99 		{&F80PusanBreakout},
//DEADCODE JIM 25/03/99 		{&F84YaluBridge},
//DEADCODE JIM 25/03/99 		{&F86BouncedbyMiGs},
//DEADCODE JIM 25/03/99 		{&F86FighterSweep}
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 	};
//DEADCODE JIM 25/03/99 
