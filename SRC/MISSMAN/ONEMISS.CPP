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

//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 //Filename       onemiss.cpp
//DEADCODE JIM 25/03/99 //System         
//DEADCODE JIM 25/03/99 //Author         R. Hyde 
//DEADCODE JIM 25/03/99 //Date           Fri 2 Aug 1996
//DEADCODE JIM 25/03/99 //Description    
//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 #include	"dosdefs.h"											//DAW 29Feb96
//DEADCODE JIM 25/03/99 //DeadCode JIM 22Aug96 //DeadCode JIM 22Aug96 #define	F_GRAFIX
//DEADCODE JIM 25/03/99 #define	F_BFIELD
//DEADCODE JIM 25/03/99 #define	F_SOUNDS
//DEADCODE JIM 25/03/99 #define	F_COMMON												//JIM 22Aug96
//DEADCODE JIM 25/03/99 #include	"files.g"	//NON-GRAPHICS FILES
//DEADCODE JIM 25/03/99 #include	"missman2.h"										//DAW 17Jan96
//DEADCODE JIM 25/03/99 //DeadCode JIM 14May96 #include	"ui.h"												//JIM 30Apr96
//DEADCODE JIM 25/03/99 #include	"uniqueid.h"
//DEADCODE JIM 25/03/99 #include	"mytime.h"											//RDH 26Jan96
//DEADCODE JIM 25/03/99 //DeadCode JIM 22Apr97 #include	"UID.G"
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99  WpSetType ScrambleWpSet =
//DEADCODE JIM 25/03/99  {
//DEADCODE JIM 25/03/99  	/*MainObjective*/	UID_Null,
//DEADCODE JIM 25/03/99  	/*SubObjective*/	UID_Null,
//DEADCODE JIM 25/03/99  	/*WP1*/				UID_Null,
//DEADCODE JIM 25/03/99  	/*WP2*/				UID_Null,
//DEADCODE JIM 25/03/99  	/*WP3*/				UID_Null
//DEADCODE JIM 25/03/99  };
//DEADCODE JIM 25/03/99  
//DEADCODE JIM 25/03/99  
//DEADCODE JIM 25/03/99  WpListType ScrambleList =
//DEADCODE JIM 25/03/99  {	/*NoOfEntries*/	1,
//DEADCODE JIM 25/03/99  			{&ScrambleWpSet} 
//DEADCODE JIM 25/03/99  };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 //NEW SCRAMBLE MISSIONS BY MARK									//MS 05Sep96
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 WpSetType ScrambleWpSetGerm =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*MainObjective*/	UID_NODE_AnTung,
//DEADCODE JIM 25/03/99 	/*SubObjective*/	UID_Null,
//DEADCODE JIM 25/03/99 	/*WP1*/				UID_NODE_AnTung,
//DEADCODE JIM 25/03/99 	/*WP2*/				UID_NODE_AnTung,
//DEADCODE JIM 25/03/99 	/*WP3*/				UID_NODE_AnTung
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 WpListType ScrambleListGerm =
//DEADCODE JIM 25/03/99 {	/*NoOfEntries*/	1,
//DEADCODE JIM 25/03/99 			{&ScrambleWpSetGerm} 
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_FirstFlightGerm =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTFIRSTFLIGHTTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTFIRSTFLIGHTTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_FirstFlightGerm,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	1,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	1,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_FollowLdrGerm =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTFOLLOWTHELEADERTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTFOLLOWTHELEADERTEXT,
//DEADCODE JIM 25/03/99 ///	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_FollowLdrGerm,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	2,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	2,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_LOOSE,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_TurkeyShootGerm =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTTURKEYSHOOTTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTTURKEYSHOOTTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_TurkeyShootGerm,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	1,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	1,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_GroundAttackGerm =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTGROUNDATTACKTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTGROUNDATTACKTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_GroundAttackGerm,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	1,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	1,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_OneOnOneGerm =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTONEONONETITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTONEONONETEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_OneOnOneGerm,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	1,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	1,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_SquadEncounterGerm =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTSQUADRONENCOUNTERTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTSQUADRONENCOUNTERTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_SquadEncounterGerm,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	12,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	4,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_StalkingPreyGerm =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTSTALKINGPREYTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTSTALKINGPREYTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_StalkingPreyGerm,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	4,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	4,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_FirstPatrolGerm =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTFIRSTPATROLTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTFIRSTPATROLTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_FirstPatrolGerm,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	3,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	6,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		CLOUDAT10000FT,							//MS 27Nov96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 //Allied															//MS 05Sep96
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 WpSetType ScrambleWpSetBrit =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*MainObjective*/	UID_NODE_AnTung,
//DEADCODE JIM 25/03/99 	/*SubObjective*/	UID_Null,
//DEADCODE JIM 25/03/99 	/*WP1*/				UID_NODE_AnTung,
//DEADCODE JIM 25/03/99 	/*WP2*/				UID_NODE_AnTung,
//DEADCODE JIM 25/03/99 	/*WP3*/				UID_NODE_AnTung
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 WpListType ScrambleListBrit =
//DEADCODE JIM 25/03/99 {	/*NoOfEntries*/	1,
//DEADCODE JIM 25/03/99 			{&ScrambleWpSetBrit} 
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_FirstFlightBrit =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTFIRSTFLIGHTTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTFIRSTFLIGHTTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListBrit,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_FirstFlightBrit,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	1,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	1,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_90Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_FollowLdrBrit =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTFOLLOWTHELEADERTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTFOLLOWTHELEADERTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListBrit,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_FollowLdrBrit,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	2,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	2,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_LOOSE,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		CLOUDAT10000FT,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_TurkeyShootBrit =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTTURKEYSHOOTTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTTURKEYSHOOTTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		HR17,		//STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListBrit,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_TurkeyShootBrit,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	1,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	1,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		CLOUDAT10000FT,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_GroundAttackBrit =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTGROUNDATTACKTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTGROUNDATTACKTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListBrit,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_GroundAttackBrit,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	1,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	1,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_OneOnOneBrit =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXTONEONONETITLE,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXTONEONONETEXT,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 	/*wplist*/			&ScrambleListBrit,	
//DEADCODE JIM 25/03/99 	/*playerbf*/		FIL_OneOnOneBrit,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	1,
//DEADCODE JIM 25/03/99 	/*numofflightac*/	1,
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_SquadEncounterBrit =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTSQUADRONENCOUNTERTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTSQUADRONENCOUNTERTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListBrit,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_SquadEncounterBrit,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	12,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	4,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_StalkingPreyBrit =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTSTALKINGPREYTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTSTALKINGPREYTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListBrit,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_StalkingPreyBrit,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	4,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	4,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_FirstPatrolBrit =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO
//DEADCODE JIM 25/03/99 //	/*NewsBrf*/			(TextRef)TEXTFIRSTPATROLTITLE,
//DEADCODE JIM 25/03/99 //	/*MissionBrf*/		(TextRef)TEXTFIRSTPATROLTEXT,
//DEADCODE JIM 25/03/99 //	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 //	/*TimeOfDay*/		STANDARDMORNING,
//DEADCODE JIM 25/03/99 //	/*wplist*/			&ScrambleListBrit,	
//DEADCODE JIM 25/03/99 //	/*playerbf*/		FIL_FirstPatrolBrit,
//DEADCODE JIM 25/03/99 //	/*numofsquadronac*/	3,
//DEADCODE JIM 25/03/99 //	/*numofflightac*/	6,
//DEADCODE JIM 25/03/99 //	/*FormationType*/	FORM_STACKEDV,
//DEADCODE JIM 25/03/99 //	/*weathernum*/		CLOUDAT10000FT,							//MS 27Nov96
//DEADCODE JIM 25/03/99 //	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 //	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 //	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_H2HRandom =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXTFIRSTFLIGHTTITLE,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXTFIRSTFLIGHTTEXT,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR12MIN10,
//DEADCODE JIM 25/03/99 	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 	/*playerbf*/		FIL_NULL,//FIL_H2HRandom,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	12,
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,	//FORM_RANDOM,
//DEADCODE JIM 25/03/99 	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_H2HImplode =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXTFIRSTFLIGHTTITLE,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXTFIRSTFLIGHTTEXT,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR12MIN10,
//DEADCODE JIM 25/03/99 	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 	/*playerbf*/		FIL_NULL,	//FIL_H2HImplode,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	12,
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,	//FORM_IMPLODE,
//DEADCODE JIM 25/03/99 	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 MissionType Msn_H2HExplode =
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	/*introsmack*/		FIL_SMACK_DEMO,
//DEADCODE JIM 25/03/99 	/*NewsBrf*/			(TextRef)TEXTFIRSTFLIGHTTITLE,
//DEADCODE JIM 25/03/99 	/*MissionBrf*/		(TextRef)TEXTFIRSTFLIGHTTEXT,
//DEADCODE JIM 25/03/99 	/*missiondate*/		DEC25th1950,
//DEADCODE JIM 25/03/99 	/*TimeOfDay*/		HR12MIN10,
//DEADCODE JIM 25/03/99 	/*wplist*/			&ScrambleListGerm,	
//DEADCODE JIM 25/03/99 	/*playerbf*/		FIL_NULL,	//FIL_H2HExplode,
//DEADCODE JIM 25/03/99 	/*numofsquadronac*/	12,
//DEADCODE JIM 25/03/99 	/*numofflightac*/	4,
//DEADCODE JIM 25/03/99 	/*FormationType*/	SQUAD_STACKEDV,	//SQUAD_STACKEDV,
//DEADCODE JIM 25/03/99 	/*weathernum*/		LOWCLOUD,									//RDH 02Oct96
//DEADCODE JIM 25/03/99 	/*windspeed*/		0,
//DEADCODE JIM 25/03/99 	/*winddirection*/	ANGLES_270Deg,
//DEADCODE JIM 25/03/99 	/*backdropart*/		FIL_NULL
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 SingleMission	H2H_Missions [] =
//DEADCODE JIM 25/03/99 	{
//DEADCODE JIM 25/03/99 		{&Msn_H2HRandom},
//DEADCODE JIM 25/03/99 		{&Msn_H2HImplode},
//DEADCODE JIM 25/03/99 		{&Msn_H2HExplode}
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 	};
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 SingleMission	Scramble_Missions [] =
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 	{
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 		{&Msn_FirstFlightBrit},									//RDH 12Sep96
//DEADCODE JIM 25/03/99 		{&Msn_FollowLdrBrit},									//RDH 12Sep96
//DEADCODE JIM 25/03/99 		{&Msn_TurkeyShootBrit},									//RDH 12Sep96
//DEADCODE JIM 25/03/99 		{&Msn_OneOnOneBrit},									//RDH 12Sep96
//DEADCODE JIM 25/03/99 		{&Msn_GroundAttackBrit},								//RDH 12Sep96
//DEADCODE JIM 25/03/99 		{&Msn_SquadEncounterBrit},								//RDH 12Sep96
//DEADCODE JIM 25/03/99 		{&Msn_StalkingPreyBrit},								//RDH 12Sep96
//DEADCODE JIM 25/03/99 		{&Msn_FirstPatrolBrit},									//RDH 12Sep96
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 		{&Msn_FirstFlightGerm},									//MS 05Sep96
//DEADCODE JIM 25/03/99 		{&Msn_FollowLdrGerm},									//MS 05Sep96
//DEADCODE JIM 25/03/99 		{&Msn_TurkeyShootGerm},									//MS 05Sep96
//DEADCODE JIM 25/03/99 		{&Msn_OneOnOneGerm},									//MS 05Sep96
//DEADCODE JIM 25/03/99 		{&Msn_GroundAttackGerm},								//MS 05Sep96
//DEADCODE JIM 25/03/99 		{&Msn_SquadEncounterGerm},								//MS 05Sep96
//DEADCODE JIM 25/03/99 		{&Msn_StalkingPreyGerm},								//MS 05Sep96
//DEADCODE JIM 25/03/99 		{&Msn_FirstPatrolGerm},									//MS 05Sep96
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 //DeadCode MS 05Sep96 		{&Msn_FirstFlight},
//DEADCODE JIM 25/03/99 //DeadCode MS 05Sep96 		{&Msn_FirstPatrol},
//DEADCODE JIM 25/03/99 //DeadCode MS 05Sep96 		{&Msn_OneOnOneII},
//DEADCODE JIM 25/03/99 //DeadCode MS 05Sep96 		{&Msn_TurkeyShoot},
//DEADCODE JIM 25/03/99 //DeadCode MS 05Sep96 		{&Msn_StalkingPrey},
//DEADCODE JIM 25/03/99 //DeadCode MS 05Sep96 		{&Msn_GroundAttack},
//DEADCODE JIM 25/03/99 //DeadCode MS 05Sep96 		{&Msn_FollowLdr},
//DEADCODE JIM 25/03/99 //DeadCode MS 05Sep96 		{&Msn_SquadEncounterII},
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 //		{&Msn_OneOnOne},
//DEADCODE JIM 25/03/99 //DeadCode JIM 21Oct96 	{&Msn_H2HExplode},
//DEADCODE JIM 25/03/99 //		{&Msn_OverRoucourt},
//DEADCODE JIM 25/03/99 //		{&Msn_surprise},
//DEADCODE JIM 25/03/99 //		{&Msn_OverHavrincourt},
//DEADCODE JIM 25/03/99 //		{&Msn_SquadronEncounter},
//DEADCODE JIM 25/03/99 //		{&Msn_OverRoucourt},
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 	};
