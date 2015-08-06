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

// FullPane.cpp : implementation file
//
//not needed ever now #define	PROT80			//80min protection stuff defined if you want in on
#define F_SOUNDS
#define F_BATTLE
#define F_COMMON
#include "stdafx.h"
#include "mig.h"
#include "stdlib.h"
#include "FullPane.h"
#include "messages.h"
#include "MIGView.h"
#include "replay.h"
#include "winmove.h"
#include "aggrgtor.h"
#include "campback.h"
#include "sairclms.h"
#include "globrefs.h"
#include "persons2.h"
#include "load.h"
#include	"miles.h"
#include	"bstream.h"
#include "overlay.h"
#include	"credits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
int	introsmk=0;
bool	RFullPanelDial::incomms=false,RFullPanelDial::in3d=false,RFullPanelDial::specialevent=false;
RFullPanelDial::GameStates	RFullPanelDial::gamestate=RFullPanelDial::TITLE;

/////////////////////////////////////////////////////////////////////////////
// RFullPanelDial dialog
int RFullPanelDial::resolutions[]={640,800,1024,1280};

// Initialise sheets here.  This means they are initialised at
// compile time instead of run time.
typedef FullScreen::Resolutions::Dial DIAL;
typedef FullScreen::Align ALIGN;

FullScreen RFullPanelDial::introsmack=
{
	{
		{
			FIL_NULL,
//DEADCODE DAW 21/03/99 			{{320,74}},
			{{0,70}},
			0,0
		},
		{
			FIL_NULL,
//DEADCODE DAW 21/03/99 			{{80,234}},
			{{0,70}},
			0,0
		},
		{
			FIL_NULL,
//DEADCODE DAW 21/03/99 			{{192,218}},
			{{0,70}},
			0,0
		},
		{
			FIL_NULL,
//DEADCODE DAW 21/03/99 			{{320,346}},
			{{0,70}},
			0,0
		},
	},
	FullScreen::Align::CENTRE,
			{{0,&title,CheckLobby}},
	IntroSmackInit
};

FullScreen RFullPanelDial::Blank={	{	{	FIL_NULL	}	}	};

FullScreen RFullPanelDial::credits=
{
	{
		{
			FIL_NULL,
//DEADCODE DAW 30/03/99 			{{0,0},{0,350}},
 			{{0,0},{100,50}},
			0,200
		},
		{
			FIL_NULL,
//DEADCODE DAW 30/03/99 			{{0,0},{0,450}},
			{{80,250},{80,10}},									  //JIM 15/06/99
			0,200
		},
		{
			FIL_NULL,
//DEADCODE DAW 30/03/99 			{{0,0},{0,550}},
			{{192,350},{200,100}},									  //JIM 15/06/99
			0,200
		},
		{
			FIL_NULL,
//DEADCODE DAW 30/03/99 			{{0,0},{0,750}},
			{{320,350},{300,100}},									  //JIM 15/06/99
			0,300
		},
	},
// for lobbied games need to goto locker room instead of main menu
	FullScreen::Align::CENTRE,
	{{0,&title,CheckForDemo}},
	IntroSmackInitForCredits
};

FullScreen RFullPanelDial::demotitle=
{
	{
		{	//Not got any 640 artwork, but need a backdrop for error box!
			FIL_TITLE_800,	
			{{100,100}},	// no dialogs
			425,170
		},
		{
			FIL_TITLE_800,
			{{200,180}},	// no dialogs
			530,210
		},
		{
			FIL_TITLE_1024,
			{{100,100,FullScreen::Resolutions::Dial::X2}},	// no dialogs
			675,260
		},
		{
			FIL_TITLE_1280,
			{{200,200,FullScreen::Resolutions::Dial::X2}},	// no dialogs
			810,370
		},
	},
	FullScreen::Align::CENTRE,
	{
		{IDS_TITLE1,&options3d},
		{IDS_SINGLEPLAYER1,&quickmissionflight,SetUpHotShot},
//DEADCODE JIM 11/07/99 		{IDS_TITLE2,&singleplayer},
//DeadCode AMM 12Jul98 		{IDS_TITLE3,&selectservice},
//DEADCODE JIM 11/07/99 		{IDS_TITLE3,&selectservice,StartComms},
//DEADCODE JIM 11/07/99 		{IDS_LOADGAME,&loadgame},
		{IDS_TITLE5,&replayload,InitReplay},
//DeadCode AMM 04Jan99 		{IDS_TITLE5,&replaysave,InitReplay},
		{IDS_TITLE6,&credits},
		{IDS_TITLE7,NULL,ConfirmExit}
	},
	TitleInit
};

FullScreen RFullPanelDial::title=
{
	{
		{	//Not got any 640 artwork, but need a backdrop for error box!
			FIL_TITLE_800,	
			{{100,100}},	// no dialogs
			425,170
		},
		{
			FIL_TITLE_800,
			{{200,180}},	// no dialogs
			530,210
		},
		{
			FIL_TITLE_1024,
			{{100,100,FullScreen::Resolutions::Dial::X2}},	// no dialogs
			675,260
		},
		{
			FIL_TITLE_1280,
			{{200,200,FullScreen::Resolutions::Dial::X2}},	// no dialogs
			810,370
		},
	},
	FullScreen::Align::CENTRE,
	{
#ifndef	 MIG_DEMO_VER
		{IDS_TITLE1,&options3d},
		{IDS_TITLE2,&singleplayer},
//DeadCode AMM 12Jul98 		{IDS_TITLE3,&selectservice},
		{IDS_TITLE3,&selectservice,StartComms},
		{IDS_LOADGAME,&loadgame},
		{IDS_TITLE5,&replayload,InitReplay},
//DeadCode AMM 04Jan99 		{IDS_TITLE5,&replaysave,InitReplay},
		{IDS_TITLE6,&credits},
#endif
		{IDS_TITLE7,NULL,ConfirmExit}
	},
	TitleInit
};

#ifdef	 MIG_DEMO_VER
FullScreen RFullPanelDial::singleplayer={	{	{	FIL_NULL	}	}	};
#endif
#ifndef	 MIG_DEMO_VER
FullScreen RFullPanelDial::loadcommsgame=
{
	{
		{
			FIL_LOADSAVE_640,
			{{100,100}},	// no dialogs
			425,170
		},
		{
			FIL_LOADSAVE_800,
			{{30,200}},
			20,560
		},
		{
			FIL_LOADSAVE_1024,
			{{40,260}},
			35,720
		},
		{
			FIL_LOADSAVE_1280,
			{{30,520}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&multiplayer},
		{IDS_LOAD,&readyroomhostcampaign,DoLoadCommsGame}
	},
	SetUpLoadGame
};

FullScreen RFullPanelDial::loadgame=
{
	{
		{
			FIL_LOADSAVE_640,
			{{100,100}},	// no dialogs
			425,170
		},
		{
			FIL_LOADSAVE_800,
			{{30,180}},
			20,560
		},
		{
			FIL_LOADSAVE_1024,
			{{40,260}},
			35,720
		},
		{
			FIL_LOADSAVE_1280,
			{{30,520}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&title},
		{IDS_LOAD,NULL,DoLoadGame}
	},
	SetUpLoadGame
};

#endif	//#ifndef	 MIG_DEMO_VER

FullScreen RFullPanelDial::replayload=
{
	{
		{
			FIL_REPLAY_640,
			{{15,15}},
			15,440
		},
		{
			FIL_REPLAY_800,
			{{4,150}},
			20,560
		},
		{
			FIL_REPLAY_1024,
			{{40,260}},
			50,700
		},
		{
			FIL_REPLAY_1280,
			{{40,325}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&title,ReplayLoadBack},
//DeadCode AMM 17Feb99 		{IDS_LOAD,NULL,ReplayLoad},
		{IDS_LOAD,&quickmissionflight,ReplayLoad},			//AMM 17Feb99
//		{IDS_SAVE,NULL,ReplaySave},
//		{IDS_VIEW,NULL,ReplayView},
//DeadCode AMM 17Feb99 		{IDS_VIEW,&quickmissionflight,ReplayView},
	},
	ReplayLoadInit
};

#ifndef	 MIG_DEMO_VER

FullScreen RFullPanelDial::replaysave=
{
	{
		{
			FIL_REPLAY_640,
			{{15,15}},
			15,440
		},
		{
			FIL_REPLAY_800,
			{{4,150}},
			20,560
		},
		{
			FIL_REPLAY_1024,
			{{40,260}},
			50,700
		},
		{
			FIL_REPLAY_1280,
			{{40,325}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
//		{IDS_TITLE7,&title},
		{IDS_QUICKMISSION1,NULL,ReplaySaveBack},
//		{IDS_LOAD,NULL,ReplayLoad},
		{IDS_SAVE,&replaysave,ReplaySave},
//		{IDS_VIEW,NULL,ReplayView},
		{IDS_VIEW,&quickmissionflight,ReplayView},
	},
	ReplaySaveInit
};

FullScreen RFullPanelDial::singleplayer=
{
	{
		{
			FIL_TITLE_640,
			{{0}},	// no dialogs
			425,170
		},
		{
			FIL_TITLE_800,
			{{0}},	// no dialogs
			530,210
		},
		{
			FIL_TITLE_1024,
			{{0}},	// no dialogs
			675,260
		},
		{
			FIL_TITLE_1280,
			{{0}},	// no dialogs
			810,370
		},
	},
	FullScreen::Align::CENTRE,
	{
		{IDS_SINGLEPLAYER1,&quickmissionflight,SetUpHotShot},
		{IDS_SINGLEPLAYER2,&quickmission,SetQuickState},
		{IDS_SINGLEPLAYER3,&campaignselect,SetCampState},
		{IDS_SINGLEPLAYER4,&campstart,SetUpFullWar},
		{IDS_BACK,&title},
	},
};

FullScreen RFullPanelDial::selectservice=
{
	{
		{
			FIL_LOCKERROOM_640,
			{
				{15,180}
			},
			15,440
		},
		{
			FIL_LOCKERROOM_800,
			{
				{20,280}
			},
			20,560
		},
		{
			FIL_LOCKERROOM_1024,
			{
				{25,450}//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_LOCKERROOM_1280,
			{
				{40,680}//,FullScreen::Resolutions::Dial::X2}
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&title,CleanUpComms},
//DeadCode AMM 12Jul98 		{IDS_SELECT,&selectsession},
//DeadCode AMM 20Jan99 		{IDS_SELECT,&selectsession,GetSessions},
		{IDS_CREATEGAME,&multiplayer,CreateCommsGame},
		{IDS_JOINGAME,&selectsession,GetSessions},

	},
	SelectServiceInit
};

FullScreen RFullPanelDial::selectsession=
{
	{
		{
			FIL_LOCKERROOM_640,
			{
				{15,180}
			},
			15,440
		},
		{
			FIL_LOCKERROOM_800,
			{
				{20,280}
			},
			20,560
		},
		{
			FIL_LOCKERROOM_1024,
			{
				{25,450}//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_LOCKERROOM_1280,
			{
				{40,680}//,FullScreen::Resolutions::Dial::X2}
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&selectservice,ReInitCommsInterface},
//DeadCode AMM 20Jan99 		{IDS_CREATEGAME,&multiplayer,CreateCommsGame},
//DeadCode AMM 20Jan99 		{IDS_JOINGAME,&multiplayer,JoinCommsGame},
//DeadCode AMM 20Jan99 //		{IDS_PREFERENCES9,&selectsession,RefreshSessions},
		{IDS_SELECT,&multiplayer,JoinCommsGame},
	},
	SelectSessionInit
};
#endif

FullScreen RFullPanelDial::multiplayer=
{
	{
		{
			FIL_LOCKERROOM_640,
			{{15,180}},
			15,440
		},
		{
			FIL_LOCKERROOM_800,
			{{20,240}},
			20,560
		},
		{
			FIL_LOCKERROOM_1024,
			{{25,400}},//,FullScreen::Resolutions::Dial::X2}},
			25,720
		},
		{
			FIL_LOCKERROOM_1280,
			{{40,620}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
#ifndef	 MIG_DEMO_VER
		{IDS_QUICKMISSION1,&selectsession,LobbyCheck},
		{IDS_CONTINUE,&readyroomhostmatch,CreatePlayer},
		{IDS_LOADGAME,&loadcommsgame, LoadCampaign},
#else
		{IDS_QUICKMISSION1,NULL,LobbyCheck},
		{IDS_CONTINUE,&readyroomhostmatch,CreatePlayer},
#endif
//		{IDS_VISITORS,&visitorsbook,VisitorsBook},
	},
	LockerRoomInit
};

FullScreen RFullPanelDial::visitorsbook=
{
	{
		{
			FIL_PAINTSHOP_640,
			{{15,180}},
			15,440
		},
		{
			FIL_PAINTSHOP_800,
			{{20,250}},
			20,560
		},
		{
			FIL_PAINTSHOP_1024,
			{{86,330}},//,FullScreen::Resolutions::Dial::X2}},
			25,720
		},
		{
			FIL_PAINTSHOP_1280,
			{{40,450}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&readyroomhostmatch, SelectReadyRoom},
//		{IDS_CONTINUE,&visitorsbook},
	},
	VisitorsBookInit
};

#ifndef	 MIG_DEMO_VER
FullScreen RFullPanelDial::singlefrag=
{
	{
		{
			FIL_READYROOM_640,
			{{70,50}},
			15,440
		},
		{
			FIL_READYROOM_800,
			{{60,16}},
			20,560
		},
		{
			FIL_READYROOM_1024,
			{
				{20,20},//,FullScreen::Resolutions::Dial::X2},
				{25,150}//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_READYROOM_1280,
			{{100,24}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_MAP,&readyroomhostmatch,ReturnToMap},
		{IDS_FLY,&quickmissionflight, FragFly},
		{IDS_TITLE1,&options3d}
		#ifndef NDEBUG 
			,{IDS_P3D,NULL,Pseudo3D}
		#endif
	},
	FragInit
};

FullScreen RFullPanelDial::commsfrag=
{
	{
		{
			FIL_READYROOM_640,
			{{70,50}},
			15,440
		},
		{
			FIL_READYROOM_800,
			{	{60,16},
				{16,117},
			},
			20,560
		},
		{
			FIL_READYROOM_1024,
			{
				{20,20},//,FullScreen::Resolutions::Dial::X2},
				{25,150},//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_READYROOM_1280,
			{{100,24},//,FullScreen::Resolutions::Dial::X2},
			{25,188},
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&readyroomhostmatch, SelectReadyRoom},
		{IDS_FLY,&quickmissionflight, FragFly}
	},
	FragInit
};

#endif
FullScreen RFullPanelDial::radio=
{
	{
		{
			FIL_PAINTSHOP_640,
			{{15,180}},
			15,440
		},
		{
			FIL_PAINTSHOP_800,
			{{20,230}},
			20,570
		},
		{
			FIL_PAINTSHOP_1024,
			{{86,330}},//,FullScreen::Resolutions::Dial::X2}},
			25,720
		},
		{
			FIL_PAINTSHOP_1280,
			{{40,400}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_CONTINUE,&readyroomhostmatch, SelectReadyRoomFromRadio},
		{IDS_RESETMSG,&radio, ResetMessages},
//DeadCode AMM 17Nov98 		{IDS_QUICKMISSION1,&selectsession},
//DeadCode AMM 17Nov98 		{IDS_LOADGAME,&quickmission},
//DeadCode AMM 17Nov98 		{IDS_SCAMPAIGNSELECT7,&campaignselect},
//DeadCode AMM 17Nov98 		{IDS_VISITORS,&visitorsbook},
	},
	RadioInit
};

FullScreen RFullPanelDial::paintshop=
{
	{
		{
			FIL_PAINTSHOP_640,
			{{15,180},
			{25,354},//FullScreen::Resolutions::Dial::X2},
			{320,374}},//,FullScreen::Resolutions::Dial::X2}},
			15,440
		},
		{
			FIL_PAINTSHOP_800,
			{{32,200},
			{32,464},//FullScreen::Resolutions::Dial::X2},
			{32,544}},//,FullScreen::Resolutions::Dial::X2}},
			20,570
		},
		{
			FIL_PAINTSHOP_1024,
//			{{25,280},
//			{25,560},//,FullScreen::Resolutions::Dial::X2},
//			{480,560}},//,FullScreen::Resolutions::Dial::X2}},
			{{86,330},
			{86,600},
			{86,680}},
			25,720
		},
		{
			FIL_PAINTSHOP_1280,
			{{40,450},
			{40,800},//FullScreen::Resolutions::Dial::X2},
			{40,910}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_CONTINUE,&readyroomhostmatch, SelectReadyRoom},
		{IDS_VARIANTS,&variants,SelectRRVariants},
//DeadCode DAW 27Jun99 		{IDS_VARIANTS,&variants},
	},
	PaintShopInit
};

//FullScreen RFullPanelDial::readyroom=
//{
//	{
//		{
//			FIL_READYROOM_640,
//			{{70,50}},
//			15,440
//		},
//		{
//			FIL_READYROOM_800,
//			{{130,100}},
//			20,550
//		},
//		{
//			FIL_READYROOM_1024,
//			{{15,15,FullScreen::Resolutions::Dial::X2}},
//			25,720
//		},
//		{
//			FIL_READYROOM_1280,
//			{{130,150,FullScreen::Resolutions::Dial::X2}},
//			40,960
//		},
//	},
//	FullScreen::Align::HORIZ,
//	{
////DeadCode AMM 05Aug98 		{IDS_BACK,&multiplayer},
//		{IDS_QUICKMISSION1,&title,CleanUpComms},
//		{IDS_FRAG,&singlefrag, PrepareForFrag},
//		{IDS_FLY,&quickmission,CommsSelectFly},
//		{IDS_VISITORS,&visitorsbook},
//		{IDS_RADIO,&radio},
//		{IDS_PAINTSHOP,&paintshop},
//		{IDS_MAP,&paintshop},
//	},
//	ReadyRoomInit
//};

#define READYROOMLAYOUT										\
	{														 \
		{													  \
			FIL_READYROOM_640,								\
			{{70,50}},										 \
			15,440											  \
		},													   \
		{														\
			FIL_READYROOM_800,									 \
			{{60,15}},										  \
			20,560												   \
		},															\
		{															 \
			FIL_READYROOM_1024,										  \
			{{15,15}},			   \
			25,720														\
		},																 \
		{																  \
			FIL_READYROOM_1280,											   \
			{{100,20}},					\
			40,960															 \
		},																	  \
	}																		   

FullScreen RFullPanelDial::readyroomhostmatch=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
//		{IDS_FRAG,&commsfrag},
		{IDS_FLY,&quickmissionflight,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_RADIO,&radio},
		{IDS_PAINTSHOP,&paintshop},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestmatch=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
//		{IDS_FRAG,&commsfrag},
		{IDS_FLY,&quickmissionflight,CanGuestJoin},	// to simulate selecting fly
		{IDS_RADIO,&radio},
		{IDS_PAINTSHOP,&paintshop},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomhostmatchred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
//		{IDS_FRAG,&commsfrag},
		{IDS_FLY,&quickmissionflight,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_RADIO,&radio},
		{IDS_PAINTSHOP,&paintshop},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestmatchred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
//		{IDS_FRAG,&commsfrag},
		{IDS_FLY,&quickmissionflight,CanGuestJoin},				//DAW 27Jun99
		{IDS_RADIO,&radio},
		{IDS_PAINTSHOP,&paintshop},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
#ifndef	 MIG_DEMO_VER

FullScreen RFullPanelDial::readyroomhostqmission=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
//		{IDS_FLY,&quickmission,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_RADIO,&radio},
		{IDS_PAINTSHOP,&paintshop},
		{IDS_EDITMISSION,&commsquick},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestqmission=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_RADIO,&radio},
		{IDS_PAINTSHOP,&paintshop},
		{IDS_VIEWMISSION,&quickview},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomhostqmissionred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
//		{IDS_FLY,&quickmission,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_RADIO,&radio},
		{IDS_EDITMISSION,&commsquick},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestqmissionred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_RADIO,&radio},
		{IDS_VIEWMISSION,&quickview},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};


FullScreen RFullPanelDial::readyroomhostcampaign=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
//		{IDS_FLY,&quickmission,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_RADIO,&radio},
//DeadCode AMM 04Jan99 		{IDS_MAP,&paintshop},
		{IDS_MAP,&paintshop,ReturnToMap},
		{IDS_CPS_PREFS,&options3d},

	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestcampaign=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_RADIO,&radio},
//DeadCode AMM 04Jan99 		{IDS_MAP,&paintshop},
//DeadCode AMM 18Feb99 		{IDS_MAP,&paintshop,ReturnToMap},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};

FullScreen RFullPanelDial::readyroomhostcampaignred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_VISITORS,&visitorsbook},
		{IDS_RADIO,&radio},
		{IDS_CPS_PREFS,&options3d},

	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestcampaignred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_RADIO,&radio},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};


FullScreen RFullPanelDial::campaignselect=
{
	{
		{
			FIL_CAMPAIGNSELECT_640,
			{{5,370},
			{50,30},
			{0,0}
			},
			540,10
		},
		{
			FIL_CAMPAIGNSELECT_800,
			{{7,380},
			{30,60},
			{30,20}
			},
			20,560
		},
		{
			FIL_CAMPAIGNSELECT_1024,
			{{10,500},//,FullScreen::Resolutions::Dial::X2},
			{80,80},
			{80,80}
			},
			35,720
		},
		{
			FIL_CAMPAIGNSELECT_1280,
			{{40,800},	
			{120,150},		//smacker
			{60,150}		//text
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&singleplayer},
		{IDS_FILM,NULL,StartCampSmacker},
		{IDS_BACKGROUND,NULL,StartCampBackground},
		{IDS_OBJECTIVES,NULL,StartCampObjectives},
		{IDS_BEGIN,NULL,LaunchMapFirstTime},
	},
	CampaignSelectInit
};
FullScreen RFullPanelDial::campover=
{
	{
		{
			FIL_CAMPAIGNSELECT_640,
			{{5,370},
			{5,5},
			{5,5}
			},
			20,560
		},
		{
			FIL_CAMPAIGNSELECT_800,
			{{7,500},
			{5,5},
			{5,5}
			},
			20,560
		},
		{
			FIL_CAMPAIGNSELECT_1024,
			{{10,550},//,FullScreen::Resolutions::Dial::X2},
			{100,50},
			{5,5}//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_CAMPAIGNSELECT_1280,
			{{40,800},//FullScreen::Resolutions::Dial::X2},
			{5,5},
			{5,5}//,FullScreen::Resolutions::Dial::X2}
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&title},
		{IDS_BEGIN,&campstart,},
//		{IDS_SCAMPAIGNSELECT6,&singleplayer},
//		{IDS_SCAMPAIGNSELECT7,NULL,LaunchMap},
//		{IDS_QUICKMISSION1,&singleplayer},
	},
	CampaignOverInit
};
FullScreen RFullPanelDial::campstart=
{
	{
		{
			FIL_CAMPAIGNSELECT_640,
			{{5,370},
			{5,5},
			{5,5}
			},
			540,10
		},
		{
			FIL_CAMPAIGNSELECT_800,
			{{7,500},
			{10,24},
			{10,320}
			},
			20,564
		},
		{
			FIL_CAMPAIGNSELECT_1024,
			{{10,500},//,FullScreen::Resolutions::Dial::X2},
			{80,40},
			{80,360}//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_CAMPAIGNSELECT_1280,
			{{40,800},//FullScreen::Resolutions::Dial::X2},
			{100,50},
			{100,450}//,FullScreen::Resolutions::Dial::X2}
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&singleplayer},
		{IDS_BACKGROUND,NULL,StartCampBackground2},
		{IDS_OBJECTIVES,NULL,StartCampObjectives2},
		{IDS_BEGIN,NULL,LaunchMapFirstTime},
	},
	CampaignStartInit
};
#define  MAPSPECIALLAYOUT									   \
	{															\
		{														 \
			FIL_CAMPAIGNSELECT_640,								  \
			{{5,370},											   \
			{5,5},													\
			{5,5}													 \
			},														  \
			540,10													   \
		},																\
		{																 \
			FIL_CAMPAIGNSELECT_800,										  \
			{{7,500},													   \
			{10,24},															\
			{10,320}															 \
			},																  \
			20,560															   \
		},																		\
		{																		 \
			FIL_CAMPAIGNSELECT_1024,											  \
			{{10,500},						   \
			{80,40},																\
			{80,360}							 \
			},																		  \
			25,720																	   \
		},																				\
		{														\
			FIL_CAMPAIGNSELECT_1280,							 \
			{{40,800},		  \
			{100,50},												   \
			{100,450}				\
			},														 \
			40,960													  \
		},															   \
	}

FullScreen RFullPanelDial::mapspecials=
{
	MAPSPECIALLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_CONTINUE,NULL,LaunchMapIfAlive},
	},
	MapSpecialsInit
};

FullScreen RFullPanelDial::endcamp=
{
	MAPSPECIALLAYOUT,
	FullScreen::Align::HORIZ,
	{
//DEADCODE AMM 16/05/99 		{IDS_TITLE7,&singleplayer},
		{IDS_TITLE7,&singleplayer,CleanUpComms}, //AMM 16/05/99
	},
	EndCampInit
};
FullScreen RFullPanelDial::deadpilot=
{
	MAPSPECIALLAYOUT,
	FullScreen::Align::HORIZ,
	{
//DEADCODE AMM 16/05/99 		{IDS_TITLE7,&singleplayer},
		{IDS_TITLE7,&singleplayer,CleanUpComms},  //AMM 16/05/99
		{IDS_CONTINUE,NULL,ContinueAlthoughDead},
		{IDS_LOADGAME,NULL,ReloadBecauseDead},
	},
	DeadPilotInit
};
FullScreen RFullPanelDial::specialdebrief=
{
	MAPSPECIALLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_CONTINUE,NULL,ContinueAfterSpecialDebrief},
	},
	SpecialsInit
};
FullScreen RFullPanelDial::warendcamp=
{
	MAPSPECIALLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&singleplayer},
		{IDS_CONTINUE,NULL,StartNextCampaign},
	},
	EndCampInit
};


FullScreen RFullPanelDial::quickview=
{
	{
		{
			FIL_QUICKMISSION_640,
			{{15,15}},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{{20,20}},
			20,560
		},
		{
			FIL_QUICKMISSION_1024,
			{
				{25,20},//, FullScreen::Dial::X2},
			},
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{{40,100}},//,FullScreen::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_READYROOM,&readyroomhostmatch, SelectReadyRoom}
	},
	QuickViewInit
};


FullScreen RFullPanelDial::commsquick=
{
	{
		{
			FIL_QUICKMISSION_640,
			{{15,15}},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{{20,20},{20,234}},
			20,560
		},
		{
			FIL_QUICKMISSION_1024,
			
			{{25,20},{25,300}},//, FullScreen::Dial::X2},},
			
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{{40,100},{40,375}},//,FullScreen::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
//		{IDS_QUICKMISSION1,&multiplayer},
		{IDS_VARIANTS,&variants},
		{IDS_READYROOM,&readyroomhostmatch, SelectReadyRoom}
	},
	QuickMissionInit
};

#endif	//MIG_DEMO_VER

FullScreen RFullPanelDial::quickmission=
{
	{
		{
			FIL_QUICKMISSION_640,
			{{15,15},{15,200}},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{{20,20},{20,234}},
			20,560
		},
		{
			FIL_QUICKMISSION_1024,
			{{25,20},{25,300}},//, FullScreen::Dial::X2},},
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{{40,100},{40,375}},//,FullScreen::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&singleplayer,CheckForDemo},
		{IDS_VARIANTS,&variants},
//DeadCode DAW 09Jul99 		{IDS_QUICKMISSION2,&quickmissiondebrief},
		{IDS_QUICKMISSION3,&quickmissionflight}
	},
	QuickMissionInit
};
FullScreen RFullPanelDial::quickmissionflight=
{

	{	{FIL_NULL,{0,0},50,400},
		{FIL_NULL,{0,0},50,600},
		{FIL_NULL,{0,0},50,700},
		{FIL_NULL,{0,0},50,1000}
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION2,NULL,QuitFlying}
	},
	StartFlying
};

FullScreen RFullPanelDial::quickmissiondebrief=
{
	{
		{
			FIL_QUICKMISSION_640,
			{
				{15,15},
				{15,190}
			},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{
				{20,20},
				{20,234}
			},
			20,560
		},
		{
			FIL_QUICKMISSION_1024,
			{
				{25,25},//FullScreen::Resolutions::Dial::X2},
				{25,300},//FullScreen::Resolutions::Dial::X2},
			},
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{
				{40,100},//FullScreen::Resolutions::Dial::X2},
				{40,380},//FullScreen::Resolutions::Dial::X2},
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&quickmission,IfCommsToReadyRoom},
		{IDS_ACSTATS,NULL},
		{IDS_GROUNDSTATS,&quickmissiondebriefgrnd},
#ifndef	 MIG_DEMO_VER
		{IDS_TITLE5,&replaysave,DebriefReplayCheck}								//AMM 10Feb99
#endif
	},
	QuickMissionDebriefInit
};
	
FullScreen RFullPanelDial::quickmissiondebriefgrnd=
{
	{
		{
			FIL_QUICKMISSION_640,
			{
				{15,15},
				{15,190}
			},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{
				{20,20},
				{20,234}
			},
			20,560
		},
		{
			FIL_QUICKMISSION_1024,
			{
				{25,25},//FullScreen::Resolutions::Dial::X2},
				{25,300},//FullScreen::Resolutions::Dial::X2},
			},
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{
				{40,100},//FullScreen::Resolutions::Dial::X2},
				{40,380},//FullScreen::Resolutions::Dial::X2},
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&quickmission,IfCommsToReadyRoom},
		{IDS_ACSTATS,&quickmissiondebrief},
		{IDS_GROUNDSTATS,NULL},
#ifndef	 MIG_DEMO_VER
		{IDS_TITLE5,&replaysave,DebriefReplayCheck}								//AMM 10Feb 99
#endif
	},
	QuickMissionDebriefGrndInit
};


FullScreen RFullPanelDial::variants=
{
	{
		{
			FIL_QUICKMISSION_640,
			{{15,15}},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{{20,20}},
			20,560
		},
		{
			FIL_QUICKMISSION_1024,
			{
				{40,40},// FullScreen::Dial::X2},
			},
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{{40,100}},//,FullScreen::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&quickmission, ExitVariant}
	},
	VariantsInit
};

#define	OPTIONSTITLE\
	{											\
		{IDS_PREFERENCES5,&options3d},				\
		{IDS_PREFERENCES1,&options3d2},	 \
		{IDS_PREFERENCES2,&flightoptions},		  \
		{IDS_PREFERENCES3,&gameoptions},		   \
		{IDS_PREFERENCES6,&vieweroptions},			 \
		{IDS_CONTROLLER,&controloptions},			   \
		{IDS_PREFERENCES8,&soundoptions},			  \
		{IDS_PREFERENCES9,NULL,PreferencesExitPath}						\
	}

#define	OPTIONSXY640	15,5
#define	OPTIONSXY800	10,10
#define	OPTIONSXY1024	10,10
#define	OPTIONSXY1280	20,10

#define	PANELXY640	15,50											  //RDH 11/06/99
#define	PANELXY800	50,70											  //RDH 11/06/99
#define	PANELXY1024	60,110
#define	PANELXY1280	90,150


FullScreen RFullPanelDial::options3d=
{
	{
		{
			FIL_3DDISPLAY_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_3DDISPLAY_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_3DDISPLAY_1024,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_3DDISPLAY_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	Options3dInit
};
//#define	OPTIONSXY640	15,5
//#define	OPTIONSXY800	10,10
//#define	OPTIONSXY1024	10,10
//#define	OPTIONSXY1280	20,10


FullScreen RFullPanelDial::gameoptions=
{
	{
		{
			FIL_GAMESETUP_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_GAMESETUP_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_GAMESETUP_1024,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_GAMESETUP_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	GameOptionsInit
};

FullScreen RFullPanelDial::options3d2=
{
	{
		{
			FIL_3DDISPLAY_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_3DDISPLAY_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_3DDISPLAY_1024,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_3DDISPLAY_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	Options3d2Init
};

FullScreen RFullPanelDial::vieweroptions=
{
	{
		{
			FIL_VIEWOPTIONS_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_VIEWOPTIONS_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_VIEWOPTIONS_1024,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_VIEWOPTIONS_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	ViewerOptionsInit
};

FullScreen RFullPanelDial::soundoptions=
{
	{
		{
			FIL_SOUNDSETUP_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_SOUNDSETUP_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_SOUNDSETUP_1024,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_SOUNDSETUP_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	SoundOptionsInit
};

FullScreen RFullPanelDial::flightoptions=
{
	{
		{
			FIL_FLIGHTCONFIG_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_FLIGHTCONFIG_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_FLIGHTCONFIG_1024,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_FLIGHTCONFIG_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	FlightOptionsInit
};

FullScreen RFullPanelDial::controloptions=
{
	{
		{
			FIL_FLIGHTCONFIG_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_FLIGHTCONFIG_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_FLIGHTCONFIG_1024,
			{{60,100}},												  //RDH 14/05/99
			OPTIONSXY1024
		},
		{
			FIL_FLIGHTCONFIG_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	ControlOptionsInit
};

RFullPanelDial::RFullPanelDial(CWnd* pParent /*=NULL*/)
	: RowanDialog(RFullPanelDial::IDD, pParent)
{
	//{{AFX_DATA_INIT(RFullPanelDial)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_currentscreen=NULL;
	whichcamp=0;
	pdial[0]=NULL;
	pdial[1]=NULL;
	pdial[2]=NULL;
	m_timerID=NULL;
	m_currentres=-1;
}

RFullPanelDial::~RFullPanelDial()
{
	m_pView->m_pfullpane=NULL;

}



void RFullPanelDial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RFullPanelDial)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOX,m_IDC_RLISTBOX);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RFullPanelDial, CDialog)
	//{{AFX_MSG_MAP(RFullPanelDial)
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ENABLE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE_CLASS( WM_GETGLOBALFONT,RFullPanelDial,OnGetGlobalFont)
	ON_MESSAGE_CLASS( WM_GETARTWORK,RFullPanelDial, OnGetArt)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// RFullPanelDial message handlers


void RFullPanelDial::LaunchMain(FullScreen* startscreen)
{ // launches the main dialog window
	CRect rect;
//DeadCode DAW 18Jun99 	if (GetCurrentRes()==0)
//DeadCode DAW 18Jun99 		MessageBox("Resolution is too small to run Mig Alley - this message to be removed","Warning",MB_OK);
//DeadCode DAW 18Jun99 	else
	{

	m_pView->GetClientRect(rect);
	RDialog* dial=RDialog::MakeTopDialog(rect,
								DialBox(FIL_NULL,this,EDGES_NOSCROLLBARS_NODRAGGING)
							);
	// launch the first sheet...
//	CWnd* parent=GetParent()->GetParent();
//	ASSERT(parent==m_pView);
	GetParent()->BringWindowToTop();
	m_pStartScreen=startscreen;
	LaunchScreen(startscreen);
	UpdateSize();
	}
}

void RFullPanelDial::LaunchDial(RDialog* dial, UINT dialID) // typically pass new CSoundDialog for example
{
	if (pdial[dialID]) 
	{
		pdial[dialID]->PreDestroyPanel();
		pdial[dialID]->DestroyPanel();
	}
//	dial->Create(dial->MY_IID,this);
	// scale the dialog if necessary due to font size change
//	dial->m_scalingfactor=(float)fontdpi/96;
//	dial->ScaleDialog(1);
	pdial[dialID]=AddPanel(dial,
		m_currentscreen->resolutions[m_currentres].dials[dialID].flags & FullScreen::Dial::X2, 
		CRect(	m_currentscreen->resolutions[m_currentres].dials[dialID].X,
				m_currentscreen->resolutions[m_currentres].dials[dialID].Y,
				0,
				m_currentscreen->resolutions[m_currentres].dials[dialID].flags  & FullScreen::Dial::CENTRE
			),
		m_currentscreen->resolutions[m_currentres].artwork,
		EDGES_NOSCROLLBARS_NODRAGGING);
	pdial[dialID]->m_bDrawBackground=pdial[dialID]->m_bDrawBackground||enablepanelselfdrawstate;
//	dial->ShowWindow(SW_SHOW);
}
void RFullPanelDial::LaunchDial(UINT dialID,const DialBox* d) // typically pass new CSoundDialog for example
{
	if (pdial[dialID]) 
	{
		pdial[dialID]->PreDestroyPanel();
		pdial[dialID]->DestroyPanel();
	}
//	dial->Create(dial->MY_IID,this);
	// scale the dialog if necessary due to font size change
//	dial->m_scalingfactor=(float)fontdpi/96;
	pdial[dialID]=AddPanel(d,
				m_currentscreen->resolutions[m_currentres].dials[dialID].flags & FullScreen::Dial::X2, 
				CRect(	m_currentscreen->resolutions[m_currentres].dials[dialID].X,
						m_currentscreen->resolutions[m_currentres].dials[dialID].Y,
						0,
						m_currentscreen->resolutions[m_currentres].dials[dialID].flags  & FullScreen::Dial::CENTRE
					)
				);
	pdial[dialID]->m_bDrawBackground=pdial[dialID]->m_bDrawBackground||enablepanelselfdrawstate;
//	dial->ShowWindow(SW_SHOW);
}


extern	Smack*	OpenSmack(FileNum filenumber,int win,int X,int Y,int w,int h);
extern	cdecl	UWord	DoSmack(int poo);
extern	cdecl	void	CloseSmack();


void RFullPanelDial::LaunchSmacker(int dialID,FileNum smackerID)
{
	int	X=	m_currentscreen->resolutions[m_currentres].dials[dialID].X;
	int	Y=	m_currentscreen->resolutions[m_currentres].dials[dialID].Y;
	if (smackerID)
	{
		File_Man.DiscardDirList(smackerID);
		File_Man.ExistNumberedFile(smackerID);

#ifdef PROT80
#ifndef MIG_DEMO_VER
		{
			DWORD spc,bps,freec,totc;
			char buffer[80];
			File_Man.NameNumberedFile(smackerID,buffer);
			buffer[3]=0;
			GetDiskFreeSpace(buffer,&spc,&bps,&freec,&totc);
			spc=((spc*bps)/1024)*totc;
			while (spc<1024*650 || spc>1024*700)
			{
				if (MessageBox(RESSTRING(INSERTCD),buffer,MB_RETRYCANCEL+MB_ICONEXCLAMATION)==IDCANCEL)
					_Error.ReallyEmitSysErr(RESSTRING(FILENOTEXIST),smackerID,buffer);
				buffer[3]=0;
				GetDiskFreeSpace(buffer,&spc,&bps,&freec,&totc);
				spc=((spc*bps)/1024)*totc;
			}
		}
#endif
#endif
 

	}
//DeadCode DAW 02Nov99 	if (!smackerID || File_Man.ExistNumberedFile(smackerID))
	if ((!smackerID || File_Man.ExistNumberedFile(smackerID)) || _DPlay.PossibleLobby)
	{
#ifdef MIG_DEMO_VER
		if (!_DPlay.PossibleLobby)
#endif
			OpenSmack(smackerID,(int)m_hWnd,X,Y,0,0);					//DAW 09Jul99


//Old_Code DAW 04Dec98 	m_timerID=SetTimer(2398,1000/12,NULL);
		m_timerID=SetTimer(2398,1,NULL);
	}
}

void RFullPanelDial::OnTimer(UINT nIDEvent) 
{
	// Nick the Enum loop thing
	if (nIDEvent==m_timerID)
	{
//DeadCode DAW 29Oct99 		if (!DoSmack((int)m_hWnd))
		if (!DoSmack((int)m_hWnd) || _DPlay.ConnectToLobby())
		{
//			Master_3d.BigWin();
//			Invalidate();
			if (_DPlay.PossibleLobby)
			{
				_DPlay.FinishLobbySetup();
				_DPlay.PossibleLobby=false;
			}

#ifdef MIG_DEMO_VER
			if (!_DPlay.PossibleLobby)
#endif
				CloseSmack();


			OnLButtonUp(0, CPoint (0,0)) ;
			//KillTimer(m_timerID);
			//m_timerID=0;
		}
	}
}

void RFullPanelDial::OnLButtonUp(UINT nFlags, CPoint point) 
{
//DeadCode DAW 29Oct99 	if (m_currentscreen->textlists[0].text==NULL) 
	if (m_currentscreen->textlists[0].text==NULL && !_DPlay.PossibleLobby) 
	{
		OnSelectRlistbox(0,0);
//DEADCODE DAW 15/06/99 		UpdateSize();
//DEADCODE DAW 15/06/99 
//DEADCODE DAW 15/06/99 		_Miles.InitSoundFonts();		//RJS 24Nov98
	}
//	{
//		LaunchScreen();
//		UpdateSize();
//	}
}

int RFullPanelDial::GetCurrentRes()
{ // the screen height is assumed to be 3/4 the screen width...
	CRect rect;
//	m_pView->GetClientRect(rect);
	AfxGetMainWnd()->GetWindowRect(rect); // a slightly more accurate representation
	int bestresX=0;
	int res;
	for (res=0;res<6;res++)
	{
		if (resolutions[res] &&
			rect.Width()>=resolutions[res] && 
			rect.Width()-resolutions[res]<=rect.Width()-resolutions[bestresX])
			bestresX=res;
	}
	int bestresY=0;
	for (res=0;res<6;res++)
	{
		if (resolutions[res] &&
			rect.Height()*4>=resolutions[res]*3 && 
			rect.Height()-resolutions[res]<=rect.Width()-resolutions[bestresY])
			bestresY=res;
	}
//	if (resolutions[bestresX]<=resolutions[bestresY]) return bestresX;
//	return bestresY;
	if (resolutions[bestresX]<=resolutions[bestresY]) res = bestresX;
	else res=bestresY;
	// now check if the artwork for this resolution is available, if not
	// search downwards until you find one that is there (Note there must be
	// one at the lowest resolution...
//	if (!m_currentscreen->resolutions[res].artwork)
//		return res;
	if (m_currentscreen)
		if (!m_currentscreen->resolutions[res].artwork)
			return res;
		else{}
	else
		return res;


	if (m_currentscreen)
	{
		if (!m_currentscreen->resolutions[res].artwork) return res;
		while (!m_currentscreen->resolutions[res].artwork || !FILEMAN.existnumberedfile(m_currentscreen->resolutions[res].artwork))
		{
			// find the next lowest resolution...
			int currentres=resolutions[res];
			int closestres=0;
			for (int newres=0;newres<6;newres++)
			{
				if (resolutions[newres]<currentres && resolutions[newres]>closestres)
				{
					closestres=resolutions[newres];
					res=newres;
				}
			}
			if (closestres==0)
			{
//				ASSERT(FALSE); // cannot find artwork for this sheet make sure there
								// is one at the lowest resolution...
				return 0;
			}
		}
	}
	return res;
}

void RFullPanelDial::LaunchScreen(FullScreen * pfullscreen)
{
	bool	closedsmack=false;
	if (m_timerID) 
	{
		CloseSmack();
		Master_3d.BigWin();
		KillTimer(m_timerID);
		m_timerID=0;
		closedsmack=true;
	}
	pdial[0]=pdial[1]=pdial[2]=NULL;
	Invalidate();
	m_currentscreen=pfullscreen;
	artnum=pfullscreen->resolutions[m_currentres].artwork;
	PositionRListBox();
	localnote=NULL;
	enablepanelselfdrawstate=false;
	if (m_currentscreen->InitProc) (this->*m_currentscreen->InitProc)();
	enablepanelselfdrawstate=false;
	if (closedsmack) 
	{
		int	failed=0;
		UpdateSize();
		failed=GetCurrentRes();

		PAINTSTRUCT paintstruct;
		CDC* pDC;
		pDC=BeginPaint(&paintstruct);
		if (GetDeviceCaps(pDC->m_hDC,BITSPIXEL)<15)
			failed=0;
		if (failed==0)
		{
			//attempt to improve 256 colour palette match?
		}
		EndPaint(&paintstruct);
		Invalidate();

		if (failed==0)
		{
			GETDLGITEM(IDC_RLISTBOX)->Clear();
			MessageBox(RESSTRING(RESWARNING), RESSTRING(MIGALLEY));
			ConfirmExit(pfullscreen);
		}
	}
}

BEGIN_EVENTSINK_MAP(RFullPanelDial, CDialog)
    //{{AFX_EVENTSINK_MAP(RFullPanelDial)
	ON_EVENT(RFullPanelDial, IDC_RLISTBOX, 1 /* Select */, OnSelectRlistbox, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RFullPanelDial::OnSelectRlistbox(long row, long column) 
{
	int x=max(row,column);
	Bool retval=TRUE;

	//Nuke any running smacker
//	CloseSmack();

	FullScreen* nextscreen=m_currentscreen->textlists[x].nextscreen;
	if (m_currentscreen->textlists[x].onselect) 
		retval=(this->*m_currentscreen->textlists[x].onselect)(nextscreen);
	if (retval && nextscreen)
	{
		// Nuke all panels then launch relevant sheet.
		RDialog* nextchild;

		for (int dialID=0;dialID<3;dialID++)
			if (pdial[dialID])
			{
				pdial[dialID]->PreDestroyPanel();
				pdial[dialID]->DestroyPanel();
				pdial[dialID]=NULL;
			}
		fchild=NULL;
		LaunchScreen(nextscreen);
	}
}

void RFullPanelDial::UpdateSize()
{
	// first move this so that it fits one of the resolutions
	m_currentres=GetCurrentRes();
	int width=resolutions[m_currentres];
	int height=(resolutions[m_currentres]*3)/4;
	if (resolutions[m_currentres]==1280)
		height=1024;
	artnum=m_currentscreen->resolutions[m_currentres].artwork;
	CRect rect;
	AfxGetMainWnd()->GetClientRect(rect);
	if (m_currentscreen->textlists[0].text==NULL)
	{
		MoveWindow(rect);
	}
	else
	{
		MoveWindow((rect.Width()-width)/2,(rect.Height()-height)/2,
				width,height);
	}
	PositionRListBox();
	for (int x=0;x<3;x++)
	{
		if (pdial[x])
		{
			pdial[x]->artnum=artnum;
			pdial[x]->MoveWindow(GetDialPosition(pdial[x],x));
			if (m_currentscreen->resolutions[m_currentres].dials[x].flags & FullScreen::Resolutions::Dial::X2) pdial[x]->ScaleDialog(2);
			else pdial[x]->ScaleDialog(1);
		}
	}
}

CRect RFullPanelDial::GetDialPosition(RDialog * dial, UINT dialID)
{
	CRect rect;
	dial->GetClientRect(rect);
	CPoint bottomright=rect.BottomRight();
	rect+=CPoint(m_currentscreen->resolutions[m_currentres].dials[dialID].X,
					 m_currentscreen->resolutions[m_currentres].dials[dialID].Y);
	if (m_currentscreen->resolutions[m_currentres].dials[dialID].flags & FullScreen::Resolutions::Dial::CENTRE)
	{
		bottomright.x/=2;
		bottomright.y/=2;
		rect-=bottomright;
	}
	return rect;
}

void RFullPanelDial::PositionRListBox()
{
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetBorder(FALSE);
	prlistbox->Clear();
	int seperation=100;

	if (m_currentscreen->listalign & FullScreen::Align::HORIZ)
	{	// a horizontal listbox...
		// spacing depends on resolution...
		for (int x=0;x<10;x++)
		{
			if (m_currentscreen->textlists[x].text==NULL) break;
			prlistbox->AddColumn(seperation);
			CString string;
			string.LoadString(m_currentscreen->textlists[x].text);
			prlistbox->AddString(string,x);
		}
	}
	else // a vertical one
	{
		prlistbox->AddColumn(100);
		for (int x=0;x<10;x++)
		{
			if (m_currentscreen->textlists[x].text==NULL) break;
			CString string;
			string.LoadString(m_currentscreen->textlists[x].text);
			prlistbox->AddString(string,0);
		}
	}
	// move to correct position.
	prlistbox->Shrink();
	prlistbox->ResizeToFit();
	CRect rect;
	prlistbox->GetClientRect(rect);
	CPoint bottomright=rect.BottomRight();
	CPoint topleft(m_currentscreen->resolutions[m_currentres].ListX,m_currentscreen->resolutions[m_currentres].ListY);
	switch (m_currentscreen->listalign&0xF8)
	{
		case FullScreen::Align::TOP:
			break;
		case FullScreen::Align::BOT:
			bottomright.x/=2;
			bottomright.y/=2;
			rect-=bottomright;
			break;
		case FullScreen::Align::MID:
			rect-=bottomright;
			break;
	}
	switch (m_currentscreen->listalign&0x3)
	{
		case FullScreen::Align::LEFT:
			prlistbox->SetCentred(FALSE);
			break;
		case FullScreen::Align::RIGHT:
			prlistbox->SetCentred(FALSE);
			break;
		case FullScreen::Align::CENTRE:
			prlistbox->SetCentred(TRUE);
			break;
		case FullScreen::Align::ONSPACE:
			prlistbox->SetCentred(FALSE);
			break;
	}
	prlistbox->MoveWindow(topleft.x,topleft.y,bottomright.x,bottomright.y);
}

// some utility procedures for launching map or 3d
#ifndef	MIG_DEMO_VER

Bool RFullPanelDial::LaunchMap(FullScreen*&fs, bool firsttime)
{
	CloseSmack();

	m_pView->LaunchMap(firsttime);

	return FALSE;
}
#endif

Bool RFullPanelDial::Launch3d(FullScreen*&fs)
{
	CloseSmack();
	return TRUE;
}

//************************************** YOUR PROCEDURES HERE


Bool RFullPanelDial::ConfirmExit(FullScreen*&fs)
{	
	CMainFrame* mainframe = ((CMainFrame*)AfxGetMainWnd());
	Save_Data.SavePreferences();
	mainframe->m_doIExist=0;
	mainframe->DestroyWindow();

//	((CMainFrame*)AfxGetMainWnd())->OnBye();
	return FALSE;
}

Bool RFullPanelDial::IntroSmackInitForCredits()
{
	LaunchSmacker(0,FIL_SMACK_GAMEINTRO);
	LaunchDial(new 	CCredits(IDS_CT_PROGRAMMINGTEAMTITLE),1);
	return TRUE;
}
Bool RFullPanelDial::IntroSmackInit()
{
//DeadCode DAW 02Nov99 	_DPlay.LaunchedByLobbyCheck();
	UpdateSize();
	Save_Data.InitPreferences((int)Master_3d.winst);
	_Replay.TruncateTempFiles();
 	char buffer[80];
 	File_Man.NameNumberedFile(FIL_SMACK_GAMEINTRO,buffer);
//DeadCode DAW 02Nov99 	if (!File_Man.ExistNumberedFile(FIL_SMACK_GAMEINTRO))
	if (!File_Man.ExistNumberedFile(FIL_SMACK_GAMEINTRO) && !_DPlay.PossibleLobby)
		_Error.ReallyEmitSysErr(RESSTRING(FILENOTEXIST),FIL_SMACK_GAMEINTRO,buffer);
#ifdef PROT80
#ifndef MIG_DEMO_VER
 		{
 			DWORD spc,bps,freec,totc;
 			char buffer[80];
 			File_Man.NameNumberedFile(FIL_SMACK_GAMEINTRO,buffer);
 			buffer[3]=0;
 			GetDiskFreeSpace(buffer,&spc,&bps,&freec,&totc);
 			spc=((spc*bps)/1024)*totc;
 			while (spc<1024*650 || spc>1024*700)
 			{
 				if (MessageBox(RESSTRING(INSERTCD),buffer,MB_RETRYCANCEL+MB_ICONEXCLAMATION)==IDCANCEL)
 					_Error.ReallyEmitSysErr(RESSTRING(FILENOTEXIST),FIL_SMACK_GAMEINTRO,buffer);
 				buffer[3]=0;
 				GetDiskFreeSpace(buffer,&spc,&bps,&freec,&totc);
 				spc=((spc*bps)/1024)*totc;
 			}
 		}
#endif
#endif
	if (introsmk==0)
		Master_3d.SmallWin();
	SetCursorPos(10,10);
	LaunchSmacker(0,FIL_SMACK_GAMEINTRO);
	return TRUE;
}
void RFullPanelDial::ResetLoadGameOption()
{
#ifndef MIG_DEMO_VER
 	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	if  (		(_DPlay.GameType == COMMSCAMPAIGN) 
			&&	(_DPlay.UIPlayerType == PLAYER_HOST)
		)
		prlistbox->ReplaceString(RESSTRING(LOADGAME),0,2);
	else
		prlistbox->ReplaceString("",0,2);
#endif
}

Bool RFullPanelDial::Options3dInit()
{
	LaunchDial(new CSDetail,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(0);
	prlistbox->SetHilightRow(0);
	return TRUE;
}

Bool RFullPanelDial::GameOptionsInit()
{
	LaunchDial(new CSGame,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(3);
	prlistbox->SetHilightRow(0);
	return TRUE;
}

Bool RFullPanelDial::Options3d2Init()
{
	LaunchDial(new CAutoPilot,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(1);
	prlistbox->SetHilightRow(0);
	return TRUE;
}

Bool RFullPanelDial::ViewerOptionsInit()
{
	LaunchDial(new CSViewer,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(4);
	prlistbox->SetHilightRow(0);
	return TRUE;
}

Bool RFullPanelDial::SoundOptionsInit()
{
	LaunchDial(new CSSound,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(6);
	prlistbox->SetHilightRow(0);
	return TRUE;
}

Bool RFullPanelDial::FlightOptionsInit()
{

	LaunchDial(new CSFlight,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(2);
	prlistbox->SetHilightRow(0);
	return TRUE;
}

Bool RFullPanelDial::ControlOptionsInit()
{
	LaunchDial(new SController,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(5);
	prlistbox->SetHilightRow(0);
	return TRUE;
}


Bool RFullPanelDial::QuickMissionDesc()
{ //CCampBack
  	LaunchDial(new CCampBack(CSQuick1::quickdef.missiondesc, IDD_QUICKTEXT),1);
	return TRUE;
}

Bool RFullPanelDial::QuickMissionBlue()
{
	int	ilun[8][2]={{0}};
	int initind=0;
	for (int wave=0;wave<8;wave++)
		for (int grp=0;grp<3;grp++)
			if (CSQuick1::quickdef.line[0][wave][grp].flights||CSQuick1::quickdef.line[0][wave][grp].DutyFlags())
			{
				ilun[initind][0]=wave;
				ilun[initind][1]=grp;
				initind++;
			}
	const DialBox&	ND=*(DialBox*)NULL;

	LaunchDial(1,
		&DialList(DialBox(FIL_NULL,new QuickMissionPanel),			
			DialList ( DialBox(FIL_NULL,new EmptyChildWindow, EDGES_NOSCROLLBARS_NODRAGGING),
				(initind>0)?DialBox(FIL_NULL,new CSQuickLine(0,ilun[0][0],ilun[0][1]),EDGES_NOSCROLLBARS_NODRAGGING):ND,
				(initind>1)?DialBox(FIL_NULL,new CSQuickLine(0,ilun[1][0],ilun[1][1]),EDGES_NOSCROLLBARS_NODRAGGING):ND,
				(initind>2)?DialBox(FIL_NULL,new CSQuickLine(0,ilun[2][0],ilun[2][1]),EDGES_NOSCROLLBARS_NODRAGGING):ND,
				(initind>3)?DialBox(FIL_NULL,new CSQuickLine(0,ilun[3][0],ilun[3][1]),EDGES_NOSCROLLBARS_NODRAGGING):ND,
				(initind>4)?DialBox(FIL_NULL,new CSQuickLine(0,ilun[4][0],ilun[4][1]),EDGES_NOSCROLLBARS_NODRAGGING):ND,
				(initind>5)?DialBox(FIL_NULL,new CSQuickLine(0,ilun[5][0],ilun[5][1]),EDGES_NOSCROLLBARS_NODRAGGING):ND,
				(initind>6)?DialBox(FIL_NULL,new CSQuickLine(0,ilun[6][0],ilun[6][1]),EDGES_NOSCROLLBARS_NODRAGGING):ND//,
//				(initind>7)?DialBox(FIL_NULL,new CSQuickLine(0,ilun[7][0],ilun[7][1]),EDGES_NOSCROLLBARS_NODRAGGING):ND

			)));
			
	return TRUE;


}
Bool RFullPanelDial::QuickMissionRed()
{

	int	ilch[8][2]={{0}};
	int initindch=0;
	for (int wave=0;wave<8;wave++)
		for (int grp=0;grp<3;grp++)
			if (CSQuick1::quickdef.line[1][wave][grp].flights||CSQuick1::quickdef.line[1][wave][grp].DutyFlags())
			{
				ilch[initindch][0]=wave;
				ilch[initindch][1]=grp;
				initindch++;
			}
	DialBox*	ND=NULL;

	LaunchDial(1,
		&DialList(DialBox(FIL_NULL,new QuickMissionPanel),			
			DialList ( DialBox(FIL_NULL,new EmptyChildWindow, EDGES_NOSCROLLBARS_NODRAGGING),
				(initindch>0)?DialBox(FIL_NULL,new CSQuickLine(1,ilch[0][0],ilch[0][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>1)?DialBox(FIL_NULL,new CSQuickLine(1,ilch[1][0],ilch[1][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>2)?DialBox(FIL_NULL,new CSQuickLine(1,ilch[2][0],ilch[2][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>3)?DialBox(FIL_NULL,new CSQuickLine(1,ilch[3][0],ilch[3][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>4)?DialBox(FIL_NULL,new CSQuickLine(1,ilch[4][0],ilch[4][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>5)?DialBox(FIL_NULL,new CSQuickLine(1,ilch[5][0],ilch[5][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>6)?DialBox(FIL_NULL,new CSQuickLine(1,ilch[6][0],ilch[6][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND//,
//				(initindch>7)?DialBox(FIL_NULL,new CSQuickLine(1,ilch[7][0],ilch[7][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND
			  )));
			
	return TRUE;
}

Bool RFullPanelDial::QuickMissionInit()
{
	LaunchDial(0,new CSQuick1);

	return QuickMissionDesc();
		
	return TRUE;
}

#ifndef	MIG_DEMO_VER

Bool RFullPanelDial::QuickViewInit()
{
	DialBox    Top(FIL_NULL,new CQuickView);
	int	ilun[8][2]={{0}};
	int initind=0;



	for (int wave=0;wave<8;wave++)
		for (int grp=0;grp<3;grp++)
			if (CSQuick1::quickdef.line[0][wave][grp].flights)
			{
				ilun[initind][0]=wave;
				ilun[initind][1]=grp;
				initind++;
			}


	int	ilch[8][2]={{0}};
	int initindch=0;
	for (wave=0;wave<8;wave++)
		for (int grp=0;grp<3;grp++)
			if (CSQuick1::quickdef.line[1][wave][grp].flights)
			{
				ilch[initindch][0]=wave;
				ilch[initindch][1]=grp;
				initindch++;
			}
	DialBox*	ND=NULL;

	LaunchDial(0,
		&DialList(Top,			
			DialList ( DialBox(FIL_NULL,new EmptyChildWindow, EDGES_NOSCROLLBARS_NODRAGGING),
				(initind>0)?DialBox(FIL_NULL,new CViewQList(0,ilun[0][0],ilun[0][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initind>1)?DialBox(FIL_NULL,new CViewQList(0,ilun[1][0],ilun[1][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initind>2)?DialBox(FIL_NULL,new CViewQList(0,ilun[2][0],ilun[2][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initind>3)?DialBox(FIL_NULL,new CViewQList(0,ilun[3][0],ilun[3][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initind>4)?DialBox(FIL_NULL,new CViewQList(0,ilun[4][0],ilun[4][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initind>5)?DialBox(FIL_NULL,new CViewQList(0,ilun[5][0],ilun[5][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initind>6)?DialBox(FIL_NULL,new CViewQList(0,ilun[6][0],ilun[6][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initind>7)?DialBox(FIL_NULL,new CViewQList(0,ilun[7][0],ilun[7][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND
				),
			DialList ( DialBox(FIL_NULL,new EmptyChildWindow,EDGES_NOSCROLLBARS_NODRAGGING),
				(initindch>0)?DialBox(FIL_NULL,new CViewQList(1,ilch[0][0],ilch[0][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>1)?DialBox(FIL_NULL,new CViewQList(1,ilch[1][0],ilch[1][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>2)?DialBox(FIL_NULL,new CViewQList(1,ilch[2][0],ilch[2][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>3)?DialBox(FIL_NULL,new CViewQList(1,ilch[3][0],ilch[3][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>4)?DialBox(FIL_NULL,new CViewQList(1,ilch[4][0],ilch[4][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>5)?DialBox(FIL_NULL,new CViewQList(1,ilch[5][0],ilch[5][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>6)?DialBox(FIL_NULL,new CViewQList(1,ilch[6][0],ilch[6][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(initindch>7)?DialBox(FIL_NULL,new CViewQList(1,ilch[7][0],ilch[7][1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND
			)));
			
	return TRUE;
}

#endif	//MIG_DEMO_VER

//extern	ULong	GR_Scram_Alt[],GR_Scram_Squad[],
//				GR_Scram_Skill[],GR_Scram_AC[],GR_Pack_Sq_Used[];
//				GR_Pack_Target,GR_Pack_PlayerSquad,GR_Pack_PlayerPos;
static RDialog* flybox;


void	RFullPanelDial::ChildDialClosed(int,RDialog* d,int l)
{
	if (localnote)
		(this->*localnote)(d,l);
	

}
Bool RFullPanelDial::StartFlying()
{	 //First copy over all the info from the CSQuick1::quickdef to globrefs
	//Now need the code in scramble...
	bool fIsRunning=in3d;
	in3d=true;
//	Todays_Packages[0][0][0].uid=UID_NULL;
#ifndef NDEBUG
//#define PLACEMENT	CRect(0,0,400,300)
//#define PLACEMENT	CRect(0,0,512,384)
//#define PLACEMENT	CRect(0,0,640,480)
#define PLACEMENT	CRect(0,0,800,600)
#else
#define	PLACEMENT	Place(POSN_CENTRE,POSN_CENTRE, 0, 0)
#endif
//DEADCODE DAW 16/03/99 Dont take from craig - this is correct
//dont do it twice.
//////////////////////////////////////////////////////////////////////
//
// Function:    FIL_PHOTOART
// Date:		07/07/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
	OverLay.loader_art=FIL_PHOTOART;
	LogChild(0,
		flybox=MakeTopDialog(PLACEMENT,DialBox(OverLay.loader_art,new Rtestsh1(NULL,fIsRunning),EDGES_NOSCROLLBARS)));

#undef PLACEMENT
	localnote=(OnFlyingClosed);
	return TRUE;
}

bool RFullPanelDial::OnFlyingClosed(RDialog*,int rv)
{
	FullScreen* s=NULL;

	if (rv==IDCANCEL)
	{
//		if (!Inst3d::fTaskSwitched)
	 		LaunchScreen(&options3d);
//		_Replay.MenuViewPlayback=false;
	}
	else
	{
		if (!_Replay.RestorePosition)							//AMM 18Feb99
		{														//AMM 18Feb99
			strcpy(_Replay.pfilename,Save_Data.lastreplayname);	//AMM 18Feb99
		}														//AMM 18Feb99

		in3d=false;
//DeadCode AMM 26Feb99 		if (_Replay.PlaybackCampDebrief)
//DeadCode AMM 26Feb99 		{
//DeadCode AMM 26Feb99 			MMC.indebrief = true;
//DeadCode AMM 26Feb99 		}
//DeadCode AMM 26Feb99 		else
//DeadCode AMM 26Feb99 		{
//DeadCode AMM 26Feb99 			MMC.indebrief=false;
//DeadCode AMM 26Feb99 		}

#ifndef	MIG_DEMO_VER
		CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
		main->m_titlebar.Redraw();

		if (_Replay.RestorePosition)
		{
			LaunchScreen(&replaysave);
		}
		else 
#endif
		if (_Replay.MenuViewPlayback)
		{
//DeadCode AMM 17Feb99 			_Replay.MenuViewPlayback=false;
			LaunchScreen(&replayload);
		}
		else
		if (gamestate==HOT || gamestate==QUICK)	   //PlaybackGameState
		{
			if (_Replay.PlaybackGameState)
			{
				_Replay.PlaybackGameState=0;
				FullScreen* fs=&singleplayer;
				if (gamestate==HOT)
					CheckForDemo(fs);
				else
					fs=&quickmission;
				LaunchScreen(fs);
			}
			else
				LaunchScreen(&quickmissiondebrief);
		}
//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER
		else
		if (gamestate==MATCH)
		{
			FullScreen* fs;
			SelectReadyRoom(fs);
			LaunchScreen(fs);
		}
#ifndef	MIG_DEMO_VER
		else
		{
			if (!_Replay.MapPlayback)
			{
				MMC.indebrief = TRUE;
				CMainFrame* main=(CMainFrame*)AfxGetMainWnd();

				if (_DPlay.PlayerCreated) //AMM 17/05/99
				{ //AMM 17/05/99
					if (_DPlay.Host) //AMM 17/05/99
						_DPlay.SendInMapMessage(); //AMM 17/05/99
					else //AMM 17/05/99
					{
						_DPlay.SendInDebriefMessage(); //AMM 17/05/99
					}
				} //AMM 17/05/99

				Save_Data.mapfilters%= FILT_MAINWP;
				Save_Data.mapfilters%= FILT_SUBWP;
				main->m_toolbar1.SetFiltersFromSaveGame();
				m_pView->m_mapdlg.Invalidate();

				main->m_titlebar.Redraw();

				MMC.NextMission();
				Persons4::StartUpMapWorld();
				SupplyTree::ProcessAirFields();

				FileNum f;
				for (f=FIL_MIDMAP;f<FIL_MIDMAP+(6*4);f=(FileNum)(f+1))
					delete new fileblock(f);
				for (f=FIL_MAP_BUTTON1;f<FIL_ICON_NEXT_PERIOD;f=(FileNum)(f+1))
					delete new fileblock(f);

//DEADCODE DAW 18/06/99 // if game has quit because host exited then wait for save game
//DEADCODE DAW 18/06/99 				if (_DPlay.HostQuit)
//DEADCODE DAW 18/06/99 				{
//DEADCODE DAW 18/06/99 					Persons4::ShutDownMapWorld();
//DEADCODE DAW 18/06/99 					_DPlay.ReceiveStartupSaveGame(false);
//DEADCODE DAW 18/06/99 					Persons4::StartUpMapWorld();
//DEADCODE DAW 18/06/99 				}

				if (_DPlay.PlayerCreated && _DPlay.GameType==COMMSCAMPAIGN)//DAW 22Jun99
				{
					if (_DPlay.Host)
					{
						_DPlay.SendEndGameScore();
					}
					else if (_DPlay.HostQuit)
					{
						_DPlay.ReceiveStartupSaveGame(false);
						_DPlay.HostQuit=false;
					}
				}

//DEADCODE RDH 26/06/99 				if (MMC.smacker)
//DEADCODE RDH 26/06/99 				{
//DEADCODE RDH 26/06/99 					LaunchScreen(&mapspecials);
//DEADCODE RDH 26/06/99 				}
//DEADCODE RDH 26/06/99 				else	
				{
					if (MMC.Active_Pilots[MMC.playersquadron*24+MMC.playeracnum].status >= IS_DEAD)
						MainToolBar().OnClickedMissionlog();
					else
						DebriefToolBar().OpenMissionresults();
					LaunchMap(s, true);
				}
			}
			else
			{
				_Replay.MapPlayback=false;
				Persons4::StartUpMapWorld();
				LaunchMap(s, true);
			}
		}
#endif 
	}
	return true;
}

#ifndef	MIG_DEMO_VER

Bool	RFullPanelDial::Pseudo3D(FullScreen*&fs)
{
	FragFly(fs);

//	INT3;	//SET UP YOUR RETURN VALUES NOW!!!!

//##test data begins
	MMC.debrief.lastperiod.count[SQ_F86B].count[Debrief::MIG] = 3;
	MMC.debrief.lastperiod.count[SQ_F84].count[Debrief::AAA] = 2;

	MMC.debrief.lastperiod.count[SQ_F84].count[Debrief::TRAIN] = 4;
	MMC.debrief.playerlog[MMC.debrief.currlogday][MMC.debrief.currperiod].target1 = UID_BrRdYalu;

	MMC.debrief.playertotals[SQ_F84][Debrief::SORTIES]++;
	MMC.debrief.playertotals[SQ_F84][Debrief::COMBATS]++;
	MMC.debrief.playertotals[SQ_F84][Debrief::KILLS]++;

//	MMC.DisDayEntry(Debrief::TARGUID, UID_BrRlYalu0, Debrief::T_AttackWest03_H);
// 	MMC.DisDayEntry(Debrief::DISCARDTARGUID, UID_BrRdYalu, Debrief::T_DeceptionFound00_H);

//	MMC.DisDayEntry(Debrief::NAME, UID_BrRdYalu, Debrief::T_ByPassBuilt_H);





//##test data ends

	//Drag the following to a watch window:
	//  gamestate specialevent incomms
	//	SAVE_DATA
	//	MMC Miss_Man.camp
	//	Supply_Tree				  fileblock
	OnFlyingClosed(this,0);
	return FALSE;
}
Bool	RFullPanelDial::FragFly(FullScreen*&fs)
{
	if (_DPlay.PlayerCreated)
	{
		if (_DPlay.Host)
		{
			if (_DPlay.GameType==COMMSCAMPAIGN)
				_Replay.SaveTempSaveGame("dcomms.dat",true); //AMM 26/05/99
// send fly now message to guests
			if (!_DPlay.UINetworkSelectFly())
				return FALSE;
		}
		else 
		{
// if game in progress then join, otherwise dont do anything
			if (!_DPlay.FlyNowFlag)
			{
				if (_DPlay.GameAvailable)
				{
					if (!_DPlay.JoinGame())
					{
						DPlay::H2H_Player[_DPlay.mySlot].status=CPS_FRAG;
						_DPlay.SendInFragMessage();
						return FALSE;			   
					}
//DeadCode DAW 27Jun99 						return FALSE;
				}
				else
				{
					return FALSE;
				}
			}
		}
	}
		MMC.UpdateAllDis();											  //RDH 19/06/99
	  	MMC.ZeroDisDay();
		MMC.msgwithsmacker = 0;										  //RDH 26/06/99
		MMC.smacker = FIL_NULL;

///CANT DO THIS HERE!!		PrepareForFrag(fs);										//AMM 17Nov98 //JIM 21/12/98
///This stomps quickmission into Todays_Packages, 
///but from campaign I already have Todays_Packages set up.
///Also, we are about to enter the 3d. This is far too late!

//		if (incomms && _DPlay.GameType!=COMMSCAMPAIGN)
//			PrepareForFrag(fs);


// this saves out binary bfield from map. needs transmitting to other players before
// they arrive at the frag screen so that ac are set up correct
// put somewhere else
//
//		if (!incomms											//AMM 17Nov98
//		|| (_DPlay.Host && _DPlay.GameType==COMMSCAMPAIGN)		//AMM 17Nov98
//		)														//AMM 17Nov98
//		{														//AMM 17Nov98
//			Todays_Packages.SaveBin();							
//		}														//AMM 17Nov98
//CANT DO IT HERE... You have just stuffed illegals into UID ptrs!!!

// need to save out a dummy save game here in case record is started
// in middle of mission


		if (!_DPlay.PlayerCreated && _Replay.IsCampState(gamestate))
		{
			_Replay.SaveTempSaveGame("dreplay.dat",false);						//AMM 26Feb99
		}

		return(TRUE);

}
Bool	RFullPanelDial::ReturnToMap(FullScreen*&fs)
{
	if (gamestate==QUICK)
		return TRUE;
	_DPlay.SendInMapMessage();
	LaunchMap(fs, false);
	return FALSE;
}
bool RFullPanelDial::CommsPlayer(int pos, int& i, int squadnum)
{
	if (!RFullPanelDial::incomms)									  //JIM 19/05/99
		return false;												  //JIM 19/05/99
	i = 0;
	while	(		(i < MAXPLAYERS)							//AMM 04Nov98
//DeadCode AMM 17Nov98 	while	(		(i < _DPlay.CurrPlayers)
			)
	{
		if  (		(DPlay::H2H_Player[i].squadron == squadnum)
			&&		(DPlay::H2H_Player[i].position == pos)
			&&		(DPlay::H2H_Player[i].status!=CPS_NONE)		//AMM 04Nov98

			)
			return (true);
		i++;
	}
	return (false);
}
bool RFullPanelDial::DuplicateCommsPlayer(int pos, int player, int squadnum)
{
	int i = 0;
	while	(		(i < player)
			)
	{
		if  (		(DPlay::H2H_Player[i].squadron == squadnum)
			&&		(DPlay::H2H_Player[i].position == pos)

			)
			return (true);
		i++;
	}
	return (false);
}

void RFullPanelDial::SetDefaultPilotPositions()
{
	enum	{MaxFlights=24};


	CFrag::OneFragDef params[MaxFlights];		 //max used below
	int numopts = 0;

	for (int pack=0;pack<Profile::MAX_PACKS;pack++)
	{
		for (int wave=0;wave<Profile::MAX_WAVES;wave++)
		{
			for (int group=0;group<Profile::MAX_GROUPS;group++)
			{
				UniqueID u=Todays_Packages.pack[pack].wave[wave].group[group].uid;
				if (		(u)
						&&	(numopts < MaxFlights)
					)
				{
					numopts = CFrag::MakeFlights(numopts, pack, wave, group, params);
				}
			}
		}
	}


//DeadCode AMM 17Nov98 	int commsplayer;

	if (incomms)
//DeadCode AMM 17Nov98 	if ( _DPlay.CurrPlayers > 0)
	{
// cant do anything here as host is not set up, dont know how many players there are

//DeadCode AMM 17Nov98 		for (char j=0 ; j < _DPlay.CurrPlayers; j++)
//DeadCode AMM 17Nov98 		{
//DeadCode AMM 17Nov98 		  if	(		(!CFrag::PositionValid(j, params, numopts))
//DeadCode AMM 17Nov98 					||	(DuplicateCommsPlayer(DPlay::H2H_Player[j].position, j, DPlay::H2H_Player[j].squadron))
//DeadCode AMM 17Nov98 				)
//DeadCode AMM 17Nov98 		  {
//DeadCode AMM 17Nov98 			bool	acplaced = false;
//DeadCode AMM 17Nov98 			char i=0;
//DeadCode AMM 17Nov98 			while	(		(i < numopts)
//DeadCode AMM 17Nov98 					&&	(!acplaced)
//DeadCode AMM 17Nov98 				)
//DeadCode AMM 17Nov98 			{
//DeadCode AMM 17Nov98 				int squadnum = params[i][3];
//DeadCode AMM 17Nov98 				int squadflight = params[i][4];
//DeadCode AMM 17Nov98 				char k = 0;
//DeadCode AMM 17Nov98 				while  (	(k < 4)
//DeadCode AMM 17Nov98 						&&	(!acplaced)
//DeadCode AMM 17Nov98 						)
//DeadCode AMM 17Nov98 				{
//DeadCode AMM 17Nov98 					int pos = squadflight * 4 + k;
//DeadCode AMM 17Nov98 					 if (		(		(		(squadnum < SQ_B_NONFLYABLE)
//DeadCode AMM 17Nov98 										&&	(_DPlay.Side)
//DeadCode AMM 17Nov98 									)
//DeadCode AMM 17Nov98 								||	(	(		(squadnum == SQ_M15)
//DeadCode AMM 17Nov98 											||	(squadnum == SQ_M15B)
//DeadCode AMM 17Nov98 										)
//DeadCode AMM 17Nov98 										&&	(!_DPlay.Side)
//DeadCode AMM 17Nov98 									)
//DeadCode AMM 17Nov98 							)
//DeadCode AMM 17Nov98 							&&	 (!CommsPlayer(pos, commsplayer, squadnum))
//DeadCode AMM 17Nov98 							&&	(_DPlay.SlotFree(pos,squadnum))
//DeadCode AMM 17Nov98 						)		
//DeadCode AMM 17Nov98 					 {
//DeadCode AMM 17Nov98 						 acplaced = true;
//DeadCode AMM 17Nov98 						DPlay::H2H_Player[j].squadron = squadnum;
//DeadCode AMM 17Nov98 						DPlay::H2H_Player[j].position = pos;
//DeadCode AMM 17Nov98 						if (j == (_DPlay.mySlot))
//DeadCode AMM 17Nov98 						{
//DeadCode AMM 17Nov98 				 			MMC.playersquadron = squadnum;
//DeadCode AMM 17Nov98 							MMC.playeracnum = squadflight*4;
//DeadCode AMM 17Nov98 						}
//DeadCode AMM 17Nov98 					 }
//DeadCode AMM 17Nov98 					  k++;
//DeadCode AMM 17Nov98 				}
//DeadCode AMM 17Nov98 				i++;
//DeadCode AMM 17Nov98 			}
//DeadCode AMM 17Nov98 			if (!acplaced)
//DeadCode AMM 17Nov98 			{
//DeadCode AMM 17Nov98 				DPlay::H2H_Player[j].squadron = -1;
//DeadCode AMM 17Nov98 				DPlay::H2H_Player[j].position = -1;
//DeadCode AMM 17Nov98 			}
//DeadCode AMM 17Nov98 		  }
//DeadCode AMM 17Nov98 		}
	}else
	{
	  if	(!CFrag::PositionValid(0, params, numopts))
	  {
		bool	acplaced = false;
		char i=0;
		while	(		(i < numopts)
				&&	(!acplaced)
			)
		{
			int squadnum = params[i][3];
			int squadflight = params[i][4];
			char k = 0;
			while  (	(k < 4)
					&&	(!acplaced)
					)
			{
				int pos = squadflight * 4 + k;
				if (squadnum < SQ_B_NONFLYABLE)
				{
					acplaced = true;
		 			MMC.playersquadron = squadnum;
					MMC.playeracnum = squadflight*4;
				}
				k++;
			}
			i++;
		}
	  }
	}
//	for (char i=0 ; i < numopts; i++)
//	{
//		int squadnum = params[i][3];
//		int squadflight = params[i][4];
//		 if (		(squadnum < SQ_B_NONFLYABLE)
//				&&	(squadflight == 0)
//				&&	(GR_Pack_PlayerSquad == -1)
//			)		
//		 {
//	 		GR_Pack_PlayerSquad = squadnum;
//			GR_Pack_PlayerPos = squadflight*4;
//		 }
//	}


}
#endif	//MIG_DEMO_VER
Bool RFullPanelDial::PrepareForFrag(FullScreen*&fs)
{
	//we are using the frag to allow player to choose positions
	//we are doing the minimum set up to get result

	Todays_Packages.PackagePrepareForFrag();					//AMM 17Nov98

//DeadCode AMM 17Nov98 	switch (_DPlay.GameType)
//DeadCode AMM 17Nov98 	{
//DeadCode AMM 17Nov98 		case TEAMPLAY:
//DeadCode AMM 17Nov98 		case DEATHMATCH:
//DeadCode AMM 17Nov98 		case COMMSQUICKMISSION:
//DeadCode AMM 17Nov98 		{
//DeadCode AMM 17Nov98 			int side;
//DeadCode AMM 17Nov98 			if (_DPlay.Side)
//DeadCode AMM 17Nov98 				side = 0;
//DeadCode AMM 17Nov98 			else
//DeadCode AMM 17Nov98 				side = 1;
//DeadCode AMM 17Nov98 //			for (int side = 0; side < 2; side++)
//DeadCode AMM 17Nov98 			{
//DeadCode AMM 17Nov98 				 for (int wave=0;wave<8;wave++)
//DeadCode AMM 17Nov98 				 {
//DeadCode AMM 17Nov98 					for (int grp=0;grp<3;grp++)
//DeadCode AMM 17Nov98 					{
//DeadCode AMM 17Nov98 						if (CSQuick1::quickdef.line[side][wave][grp].flights != 0)
//DeadCode AMM 17Nov98 						{
//DeadCode AMM 17Nov98 							Todays_Packages.pack[side].wave[wave].group[grp].uid = UID_StChosan;
//DeadCode AMM 17Nov98 							Todays_Packages.pack[side].wave[wave].group[grp].SetFlights( 
//DeadCode AMM 17Nov98 										CSQuick1::quickdef.line[side][wave][grp].flights);
//DeadCode AMM 17Nov98 							Todays_Packages.pack[side].wave[wave].group[grp].SetSquad( 
//DeadCode AMM 17Nov98 									CSQuick1::quickdef.line[side][wave][grp].actype);
//DeadCode AMM 17Nov98 						Todays_Packages.pack[side].wave[wave].group[grp].callname = -1;
//DeadCode AMM 17Nov98 						}			
//DeadCode AMM 17Nov98 					}
//DeadCode AMM 17Nov98 				 }
//DeadCode AMM 17Nov98 			}
//DeadCode AMM 17Nov98 			break;
//DeadCode AMM 17Nov98 		}
//DeadCode AMM 17Nov98 		case COMMSCAMPAIGN:
//DeadCode AMM 17Nov98 		{
//DeadCode AMM 17Nov98 			//temp to fill mig is for testing purposes
//DeadCode AMM 17Nov98 			int side = 1;
//DeadCode AMM 17Nov98 				 for (int wave=0;wave<8;wave++)
//DeadCode AMM 17Nov98 				 {
//DeadCode AMM 17Nov98 					for (int grp=0;grp<3;grp++)
//DeadCode AMM 17Nov98 					{
//DeadCode AMM 17Nov98 						if (CSQuick1::quickdef.line[side][wave][grp].flights != 0)
//DeadCode AMM 17Nov98 						{
//DeadCode AMM 17Nov98 							Todays_Packages.pack[Profile::MAX_PACKS ].wave[wave].group[grp].uid = UID_StChosan;
//DeadCode AMM 17Nov98 							Todays_Packages.pack[Profile::MAX_PACKS ].wave[wave].group[grp].SetFlights( 
//DeadCode AMM 17Nov98 										CSQuick1::quickdef.line[side][wave][grp].flights);
//DeadCode AMM 17Nov98 							Todays_Packages.pack[Profile::MAX_PACKS ].wave[wave].group[grp].SetSquad( 
//DeadCode AMM 17Nov98 									CSQuick1::quickdef.line[side][wave][grp].actype);
//DeadCode AMM 17Nov98 						Todays_Packages.pack[Profile::MAX_PACKS ].wave[wave].group[grp].callname = -1;
//DeadCode AMM 17Nov98 						}			
//DeadCode AMM 17Nov98 					}
//DeadCode AMM 17Nov98 				 }
//DeadCode AMM 17Nov98 			
//DeadCode AMM 17Nov98 			break;
//DeadCode AMM 17Nov98 		}
//DeadCode AMM 17Nov98 
//DeadCode AMM 17Nov98 	}

#ifndef	MIG_DEMO_VER
	if (!incomms)
		SetDefaultPilotPositions();
#endif
	return TRUE;

}

//DeadCode DAW 01Nov99 #endif	//MIG_DEMO_VER

Bool RFullPanelDial::QuitFlying(FullScreen*&fs)
{
	flybox->PostMessage(WM_COMMAND,IDOK,NULL);
	return FALSE;
}


Bool RFullPanelDial::QuickMissionDebriefInit()
{
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
#ifndef	MIG_DEMO_VER
	if (incomms)
		prlistbox->ReplaceString("",0,3);
	else
		prlistbox->ReplaceString(RESSTRING(REPLAY),0,3);
#endif

//	CRListBox* prlistbox;
//	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(1);
	prlistbox->SetHilightRow(0);

	LaunchDial(new CSQuick2,0);
	LaunchDial(new CSQuickAirClaims,1);

	return TRUE;
}
Bool RFullPanelDial::QuickMissionDebriefGrndInit()
{
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
#ifndef	MIG_DEMO_VER
	if (incomms)
		prlistbox->ReplaceString("",0,3);
	else
		prlistbox->ReplaceString(RESSTRING(REPLAY),0,3);
#endif

//	CRListBox* prlistbox;
//	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(2);
	prlistbox->SetHilightRow(0);
	LaunchDial(new CSQuick2,0);
	LaunchDial(new CSQuickGroundClaims,1);

	return TRUE;
}

Bool RFullPanelDial::ReplayLoadInit()
{
	if (_Replay.IsCampState(gamestate))
	{
		_Replay.BackupSaveGame();
//DeadCode AMM 26Feb99 		_Replay.PlaybackCampDebrief=MMC.indebrief;
	}
//DeadCode AMM 26Feb99 	else
//DeadCode AMM 26Feb99 	{
//DeadCode AMM 26Feb99 		_Replay.PlaybackCampDebrief=false;
//DeadCode AMM 26Feb99 	}

	CString	wildcard="*.cam";
	selectedfile=Save_Data.lastreplayname;
	strcpy(_Replay.pfilename,selectedfile);

	LaunchDial(new	CLoad(IDD_SREPLAY,LSD_LOAD,	FIL_VIDEOS_START_DIR,wildcard,selectedfile),0);

//	LaunchDial(new CSReplay,0);
	return TRUE;
}
Bool RFullPanelDial::ReplaySaveInit()
{
	if (_Replay.IsCampState(gamestate))
	{
		_Replay.BackupSaveGame();
	}

	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	if (_Replay.RestorePosition)
		prlistbox->ReplaceString("",0,2);
	else
		prlistbox->ReplaceString(RESSTRING(VIEW),0,2);

	CString	wildcard="*.cam";
	selectedfile=Save_Data.lastreplayname;

	if (!_Replay.RestorePosition)
	{
//		strcpy(_Replay.pfilename,selectedfile);
		strcpy(_Replay.pfilename,"replay.dat");
	}

//DeadCode AMM 15Feb99 	strcpy(_Replay.pfilename,"replay.dat");

	LaunchDial(new	CLoad(IDD_SAVEREPLAY,LSD_SAVE,	FIL_VIDEOS_START_DIR,wildcard,selectedfile),0);

//	LaunchDial(new CSReplay,0);
	return TRUE;
}

#ifndef	MIG_DEMO_VER
Bool RFullPanelDial::CampaignSelectInit()
{
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightRow(0);									  //RDH 19/05/99
	prlistbox->SetHilightCol(1);									  //RDH 19/05/99

	LaunchDial(new CSCampaign,0);
	LaunchSmacker(1,FIL_NULL);
	ChangeCamp(0);
	return TRUE;
}

Bool RFullPanelDial::CampaignOverInit()
{
//	Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
//	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];

//	LaunchDial(new CSCampaign,0);
	LaunchSmacker(1,FileNum(FIL_SMACK_CAMP1INTRO+(whichcamp&0x0f)));
	LaunchDial(new CCampBack(IDS_CAMPOBJ0+(whichcamp&0x0f)),2);
	return TRUE;
}

Bool RFullPanelDial::CampaignStartInit()
{
	LaunchSmacker(1,FIL_SMACK_CAMP1INTRO);
//	LaunchDial(new CCampBackEntireWar(IDS_CAMPDESC0),2);
	return TRUE;
}
#endif
Bool RFullPanelDial::LockerRoomInit()
{
	LaunchDial(new CLockerRoom,0);
	return TRUE;
}
#ifndef	MIG_DEMO_VER
Bool RFullPanelDial::LoadCampaign(FullScreen*&fs)
{
	if  (		(_DPlay.GameType == COMMSCAMPAIGN) 
			&&	(_DPlay.UIPlayerType == PLAYER_HOST)
		)
	{
		return TRUE;
//		if (!LoadCampaignData())
//		{
//	//		_Error.EmitSysErr("Error: Could not load campaign file");
//			return FALSE;
//		}else
//			return TRUE;
	}else
			return FALSE;

}
bool RFullPanelDial::LoadCampaignData()
{
	return TRUE;
//DeadCode RDH 11Jan99 	char	loadfile[40];
//DeadCode RDH 11Jan99 
//DeadCode RDH 11Jan99 	strcpy(loadfile,"c:\\mig\\game\\camp0.sav");
//DeadCode RDH 11Jan99 
//DeadCode RDH 11Jan99 	char* newfile=new char[256];
//DeadCode RDH 11Jan99 	char* buffer=new char[256];
//DeadCode RDH 11Jan99 	OPENFILENAME openfilename;
//DeadCode RDH 11Jan99 
//DeadCode RDH 11Jan99 	strcpy (newfile,"*.sav");
//DeadCode RDH 11Jan99 	strcpy(buffer,"Saved Files *.dat All Files *.*");
//DeadCode RDH 11Jan99  	buffer[11]=NULL;
//DeadCode RDH 11Jan99 	buffer[17]=NULL;
//DeadCode RDH 11Jan99 	buffer[27]=NULL;
//DeadCode RDH 11Jan99 	buffer[31]=NULL;
//DeadCode RDH 11Jan99 	buffer[32]=NULL;
//DeadCode RDH 11Jan99 
//DeadCode RDH 11Jan99     openfilename.lStructSize = sizeof OPENFILENAME; 
//DeadCode RDH 11Jan99     openfilename.hwndOwner=NULL;
//DeadCode RDH 11Jan99     openfilename.hInstance=NULL;
//DeadCode RDH 11Jan99     openfilename.lpstrFilter=buffer; 
//DeadCode RDH 11Jan99     openfilename.lpstrCustomFilter=NULL; 
//DeadCode RDH 11Jan99     openfilename.nMaxCustFilter=NULL; 
//DeadCode RDH 11Jan99     openfilename.nFilterIndex=1; 
//DeadCode RDH 11Jan99     openfilename.lpstrFile=newfile; 
//DeadCode RDH 11Jan99     openfilename.nMaxFile=256; 
//DeadCode RDH 11Jan99     openfilename.lpstrFileTitle=NULL; 
//DeadCode RDH 11Jan99     openfilename.nMaxFileTitle=NULL; 
//DeadCode RDH 11Jan99     openfilename.lpstrInitialDir="\\mig\\game"; 
//DeadCode RDH 11Jan99     openfilename.lpstrTitle="Load Saved Game";
//DeadCode RDH 11Jan99     openfilename.Flags=OFN_NOCHANGEDIR | OFN_HIDEREADONLY; 
//DeadCode RDH 11Jan99     openfilename.nFileOffset=NULL; 
//DeadCode RDH 11Jan99     openfilename.nFileExtension=NULL; 
//DeadCode RDH 11Jan99     openfilename.lpstrDefExt=".sav";
//DeadCode RDH 11Jan99     openfilename.lCustData=NULL; 
//DeadCode RDH 11Jan99     openfilename.lpfnHook=NULL; 
//DeadCode RDH 11Jan99     openfilename.lpTemplateName=NULL;
//DeadCode RDH 11Jan99 
//DeadCode RDH 11Jan99 //   	(GetOpenFileName(&openfilename));
//DeadCode RDH 11Jan99 
//DeadCode RDH 11Jan99 	if (GetOpenFileName(&openfilename))
//DeadCode RDH 11Jan99 	{
//DeadCode RDH 11Jan99 // do something with load file
//DeadCode RDH 11Jan99 	}
//DeadCode RDH 11Jan99 	else
//DeadCode RDH 11Jan99 	{
//DeadCode RDH 11Jan99 //DeadCode AMM 14Dec98 		MessageBox("Could not load file","Load Camp",MB_OK);
//DeadCode RDH 11Jan99 		RMessageBox(IDS_MIGALLEY,IDS_NOTLOAD,NULL,IDS_L_CLEAR);
//DeadCode RDH 11Jan99 		return FALSE;
//DeadCode RDH 11Jan99 	}
//DeadCode RDH 11Jan99 
//DeadCode RDH 11Jan99 	delete [] buffer;
//DeadCode RDH 11Jan99 	delete [] newfile;
//DeadCode RDH 11Jan99 
//DeadCode RDH 11Jan99 	return TRUE;
}

Bool RFullPanelDial::SetUpLoadGame()
{
	CString	wildcard="*.sav";
	selectedfile=Save_Data.lastsavegame;

	LaunchDial(new	CLoad(IDD_LOADFULL,LSD_LOAD,			FIL_SAVEGAMEDIR,wildcard,selectedfile),0);

	return TRUE;

}
Bool RFullPanelDial::SelectServiceInit()
{
	LaunchDial(new CSelectService,0);
	return TRUE;
}

Bool RFullPanelDial::SelectSessionInit()
{
	LaunchDial(new CSelectSession,0);
	return TRUE;
}
#endif
Bool RFullPanelDial::VisitorsBookInit()
{
	LaunchDial(new CVisitorsBook,0);
	return TRUE;
}

Bool RFullPanelDial::ReadyRoomInit()
{
	LaunchDial(new CReadyRoom,0);
	return TRUE;
}
#ifndef	 MIG_DEMO_VER

Bool RFullPanelDial::FragInit()
{
	CFrag::OneFragDef params[CFrag::MaxFragLines];

	CFrag::FragInit();

//DeadCode AMM 14Oct98 	if  (		(_DPlay.CurrPlayers != 0)
	if  (		(incomms)										//AMM 14Oct98
		&&	(_DPlay.GameType == COMMSCAMPAIGN)
		&&	(_DPlay.Side == FALSE)
		)
		CFrag::packmode = false;

	
	DialBox topbit(FIL_NULL,
			incomms ? (CFrag*)new CFragComms:(CFrag*)new CFragSingle, 
				EDGES_NOSCROLLBARS_NODRAGGING);
	int numopts=0;
	if (CFrag::packmode)
	{//pack mode
		numopts = CFrag::FillFlightParams(CFrag::comboindex, params);
//		params[0][0] = 0;
//		params[0][1] = 0;
//		params[0][2] = 0;
//		numopts++;
	}
	else
	{//squad  mode
		numopts = CFrag::FillFlightParamswithSquads(CFrag::comboparams[CFrag::comboindex].pack, params);
		if (numopts == 0)											  //RDH 10/06/99
		{
			CFrag::comboindex = 0;
			numopts = CFrag::FillFlightParamswithSquads(CFrag::comboparams[CFrag::comboindex].pack, params);
		}															  //RDH 10/06/99
	}
	DialBox* ND=NULL;
	LaunchDial(0,
		   &DialList(	topbit,
				DialList(	DialBox(FIL_NULL,new EmptyChildWindow, EDGES_NOSCROLLBARS_NODRAGGING),
				(numopts>0)?DialBox(FIL_NULL,CFrag::pilotlines[0]=new CFragPilot(params[0]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(numopts>1)?DialBox(FIL_NULL,CFrag::pilotlines[1]=new CFragPilot(params[1]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(numopts>2)?DialBox(FIL_NULL,CFrag::pilotlines[2]=new CFragPilot(params[2]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(numopts>3)?DialBox(FIL_NULL,CFrag::pilotlines[3]=new CFragPilot(params[3]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(numopts>4)?DialBox(FIL_NULL,CFrag::pilotlines[4]=new CFragPilot(params[4]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(numopts>5)?DialBox(FIL_NULL,CFrag::pilotlines[5]=new CFragPilot(params[5]),EDGES_NOSCROLLBARS_NODRAGGING):*ND,
				(numopts>6)?DialBox(FIL_NULL,CFrag::pilotlines[6]=new CFragPilot(params[6]),EDGES_NOSCROLLBARS_NODRAGGING):*ND
//DEADCODE JIM 26/03/99 				(numopts>7)?DialBox(FIL_NULL,CFrag::pilotlines[7]=new CFragPilot(params[7])):*ND
				)	)	);
	if (numopts==0)
		m_IDC_RLISTBOX.ReplaceString("",0,1);

	return TRUE;
}

#endif //MIG_DEMO_VER
Bool RFullPanelDial::RadioInit()
{
	LaunchDial(new CRadio,0);
	return TRUE;
}

//DeadCode DAW 01Nov99 #endif //MIG_DEMO_VER

Bool RFullPanelDial::VariantsInit()
{
	LaunchDial(new CVariants,0);
	return TRUE;
}					
void RFullPanelDial::ResetVariantOption()
{
 	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	if  (		(_DPlay.GameType <= TEAMPLAY) 
			&&	(_DPlay.UIPlayerType == PLAYER_HOST)
		)
		prlistbox->ReplaceString(RESSTRING(VARIANTS),0,1);
	else
		prlistbox->ReplaceString("",0,1);
}

//DeadCode DAW 01Nov99 #ifndef MIG_DEMO_VER

Bool RFullPanelDial::PaintShopDesc()
{
	if (pdial[0])
	{
		pdial[0]->PreDestroyPanel();
		pdial[0]->DestroyPanel();
		pdial[0]=NULL;
	}
	if (pdial[1])
	{
		pdial[1]->PreDestroyPanel();
		pdial[1]->DestroyPanel();
		pdial[1]=NULL;
	}
//TEMPCODE JIM 17/05/99 	if (pdial[2])
//TEMPCODE JIM 17/05/99 	{
//TEMPCODE JIM 17/05/99 		pdial[2]->PreDestroyPanel();
//TEMPCODE JIM 17/05/99 		pdial[2]->DestroyPanel();
//TEMPCODE JIM 17/05/99 		pdial[2]=NULL;
//TEMPCODE JIM 17/05/99 	}

	if (DPlay::H2H_Player[_DPlay.mySlot].squadron  < SQ_R_FLYABLE)
	{
		LaunchDial(new CCommsPaint,0);
 		LaunchDial(new CCurrEmblem,1);
	}
	return TRUE;
}
	
Bool RFullPanelDial::PaintShopInit()
{
//	LaunchDial(new CPaint(0,0),0);
	if  (_DPlay.GameType <= TEAMPLAY) 
		LaunchDial(new CCommsDeathMatchAc,2);


	return PaintShopDesc();
//	DialBox    Top(FIL_NULL,new CCommsPaint);
//
//	LaunchDial(0,
//		&DialList(Top,			
//			DialList ( DialBox(FIL_NULL,new EmptyChildWindow, EDGES_NOSCROLLBARS_NODRAGGING),
//				DialBox(FIL_NULL,new CCurrEmblem,EDGES_NOSCROLLBARS_NODRAGGING)
//					)));
	
	return TRUE;
}

//DeadCode DAW 01Nov99 #endif	#ifndef MIG_DEMO_VER

CFont* RFullPanelDial::OnGetGlobalFont(int fontnum)
{
	if (m_currentres==-1) m_currentres=GetCurrentRes();
	if (g_AllFonts[fontnum][1])
	{
		int currentres=resolutions[m_currentres];
		if (currentres>=1280) return g_AllFonts[fontnum][3];
		else if (currentres>=1024) return g_AllFonts[fontnum][2];
		else if (currentres>=800) return g_AllFonts[fontnum][1];
		else return g_AllFonts[fontnum][0];	
	}
	else if (m_scalingfactor==2) return g_AllFonts[fontnum][3];
	else return g_AllFonts[fontnum][0];
}
Bool RFullPanelDial::ReplayLoad(FullScreen*&fs)
{

//	pdial[0]->DestroyPanel();
//	pdial[0]=NULL;

//	if (!_Replay.LoadReplayData())
//		_Error.EmitSysErr("Error: Could not load replay file");

	//this is the file to load
	//use CFiling::LoadGame to see how to code the load
	CString file =selectedfile;
	Save_Data.lastreplayname=selectedfile;

	char* temp;
	temp=file.GetBuffer(0);

	_Replay.LoadReplayData(temp);

// load also views now....

	if (!_Replay.ValidReplayFile())
	{
		RMessageBox(IDS_MIGALLEY,IDS_INVALIDREPLAYFILE,NULL,IDS_CONTINUE);	//RJS 03Sep99
		return FALSE;
	}

	_Replay.Playback=TRUE;
	_Replay.Record=FALSE;

// need to initialise some sort of miss_man structure for now

	Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];
	SetTitleText(true);

	return TRUE;
}
void	RFullPanelDial::SetTitleText(bool clear)
{	
	if (clear)
		AfxGetMainWnd()->SetWindowText(RESSTRING(MIGALLEY));
	else
	if (Miss_Man.currcampaignnum!=Miss_Man.SCRAMBLECAMPAIGN)
		AfxGetMainWnd()->SetWindowText(RESSTRING(MIGALLEY)+": "+LoadResString(IDS_L_SCAMPAIGNSELECT1+Miss_Man.currcampaignnum));
	else
		AfxGetMainWnd()->SetWindowText(RESSTRING(MIGALLEY)+": "+LoadResString(CSQuick1::quickmissions[CSQuick1::currquickmiss].missionname));
}
Bool RFullPanelDial::ReplaySave(FullScreen*&fs)
{
//	if (!_Replay.SaveReplayData())
//		_Error.EmitSysErr("Error: Could not save replay file");

	//this is the file to load
	CString file =selectedfile;

	Save_Data.lastreplayname=selectedfile;

	char* temp;
	temp=file.GetBuffer(0);
	
	_Replay.SaveReplayData(temp);

	return TRUE;
}

Bool RFullPanelDial::ReplayView(FullScreen*&fs)
{
	if (_Replay.RestorePosition)
		return FALSE;

	if (!_Replay.MenuViewPlayback)
	{
		strcpy(_Replay.pfilename,"replay.dat");
	}

	if (!_Replay.ValidReplayFile())
	{
//DeadCode AMM 14Dec98 		MessageBox("Invalid replay file","Error",MB_OK);
		RMessageBox(IDS_MIGALLEY,IDS_INVALIDREPLAYFILE,NULL,IDS_CONTINUE);
		return FALSE;
	}

	_Replay.Playback=TRUE;
	_Replay.Record=FALSE;

// need to initialise some sort of miss_man structure for now

	Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];
	SetTitleText(true);

//	gamestate=QUICK;
//	flybox=MakeTopDialog(CRect(50,50,690,530),DialBox(FIL_TITLE_640,new Rtestsh1()));
//	LogChild(0,flybox);
//	localnote=(OnFlyingClosed);
	
	return TRUE;
}

Bool RFullPanelDial::ExitVariant(FullScreen*&fs)
{
//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER
	if (incomms)
	{
#ifndef	MIG_DEMO_VER
		if (gamestate==QUICK)
			fs=&commsquick;
		else
#endif
			fs = &paintshop;

	}else
//DeadCode DAW 01Nov99 #endif
	{
		fs=&quickmission;
	}
	return TRUE;

}

#ifndef	MIG_DEMO_VER

Bool RFullPanelDial::StartComms(FullScreen*&fs)
{
	_Replay.Record=FALSE;
	_Replay.Playback=FALSE;

	_Replay.BackupPrefs();										//AMM 25May99

 	Save_Data.gamedifficulty|=GD_VULNERABLE;
 	Save_Data.gamedifficulty|=GD_GROUNDCOLLISIONS;			
 	Save_Data.gamedifficulty|=GD_COLLISIONS;			

	Save_Data.flightdifficulty%=FD_AUTOTHROTTLE;				//AMM 25May99

	if (_DPlay.StartCommsSession())
		return TRUE;
	RMessageBox(IDS_MIGALLEY,IDS_NOTCONNECTED,NULL,IDS_CONTINUE);

	return FALSE;
}

Bool RFullPanelDial::GetSessions(FullScreen*&fs)
{
//	if (strcmp("Empire Lobby",&_DPlay.ServiceName[0]))
	{
		_DPlay.UISelectServiceProvider(&_DPlay.ServiceName[0]);
//		_DPlay.UIGetSessionListUpdate();
		if (!_DPlay.UIGetSessionListUpdate())
		{
// problem initialising connection, exit to main menu

			_DPlay.CommsMessage(IDS_BADSESSIONS2);
			_DPlay.ExitDirectPlay();
//DeadCode AMM 12May99 			fs=&title;

			if (_DPlay.StartCommsSession())
			{
				fs=&selectservice;
			}
			else
			{
				fs=&title;
			}
		}
		if (_DPlay.singlesession)
		{
			if (_DPlay.FindGoodSession())
			{
				if (_DPlay.JoinComms())
				{
					fs=&multiplayer;
					return TRUE;
				}
			}

			_DPlay.CommsMessage(IDS_BADSESSIONS2);
			return FALSE;

		}
	}
	return TRUE;
}

Bool RFullPanelDial::CreateCommsGame(FullScreen*&fs)
{
	_DPlay.UISelectServiceProvider(&_DPlay.ServiceName[0]);
	_DPlay.UIPlayerType = PLAYER_HOST;
	return TRUE;
}

Bool RFullPanelDial::JoinCommsGame(FullScreen*&fs)
{
//	Bool res;

	return (_DPlay.JoinComms());

//DeadCode AMM 20Jan99 	_DPlay.UIPlayerType = PLAYER_GUEST;
//DeadCode AMM 20Jan99 
//DeadCode AMM 20Jan99 // need a temp name to be able to create a player with
//DeadCode AMM 20Jan99 
//DeadCode AMM 20Jan99 	strcpy(_DPlay.PlayerName,"temp name");
//DeadCode AMM 20Jan99 
//DeadCode AMM 20Jan99 // need to get game details before going to locker room so that info can be filled
//DeadCode AMM 20Jan99 // in correctly....
//DeadCode AMM 20Jan99 
//DeadCode AMM 20Jan99 	if (_DPlay.UINewPlayer(_DPlay.PlayerName,_DPlay.SessionName))
//DeadCode AMM 20Jan99 	{
//DeadCode AMM 20Jan99 // null temp player name
//DeadCode AMM 20Jan99 
//DeadCode AMM 20Jan99 		strcpy (_DPlay.PlayerName,"");
//DeadCode AMM 20Jan99 
//DeadCode AMM 20Jan99 		if (_DPlay.GetGameDetails())
//DeadCode AMM 20Jan99 		{
//DeadCode AMM 20Jan99 			return TRUE;
//DeadCode AMM 20Jan99 		}
//DeadCode AMM 20Jan99 //DeadCode AMM 14Dec98 		MessageBox("Host Busy","",MB_OK);
//DeadCode AMM 20Jan99 		RMessageBox(IDS_MIGALLEY,IDS_HOSTBUSY,NULL,IDS_L_CLEAR);
//DeadCode AMM 20Jan99 	}
//DeadCode AMM 20Jan99 
//DeadCode AMM 20Jan99 	strcpy(_DPlay.PlayerName,"");
//DeadCode AMM 20Jan99 
//DeadCode AMM 20Jan99 	_DPlay.lpDP4->DestroyPlayer(_DPlay.myDPlayID);
//DeadCode AMM 20Jan99 	_DPlay.lpDP4->Close();
//DeadCode AMM 20Jan99 
//DeadCode AMM 20Jan99 	return FALSE;
//DeadCode AMM 20Jan99 //DeadCode AMM 13Oct98 	return TRUE;
}

//Bool RFullPanelDial::VisitorsBook(FullScreen*&fs)
//{
//	pdial[0]->DestroyPanel();
//	pdial[0]=NULL;
//
//	Bool res;
//
//	if (_DPlay.UIPlayerType==PLAYER_GUEST)
//	{	 
//		res=_DPlay.UINewPlayer(&_DPlay.PlayerName[0],&_DPlay.SessionName[0]);
//		
//		if (res)
//		{
//			_DPlay.SendUpdateToVisitorsBook(&_DPlay.PlayerName[0],FALSE);
//		}
//		else
//		{
//			MessageBox("Could not create session or player","Whoops",MB_OK);
//		}
//
//		_DPlay.DestroyAndClose(_DPlay.myDPlayID);
//	}
//
//	LaunchDial(new CLockerRoom,0);
//	return FALSE;
//}
#endif
Bool RFullPanelDial::ResetMessages(FullScreen*&fs)
{
	_DPlay.InitMessages();
	fs = &radio;
	return TRUE;

}
Bool RFullPanelDial::SelectReadyRoomFromRadio(FullScreen*&fs)
{
	pdial[0]->OnOK();
	return(SelectReadyRoom(fs));
}
Bool RFullPanelDial::SelectReadyRoom(FullScreen*&fs)
{
	return SelectReadyRoomStatic(fs);
}
Bool RFullPanelDial::SelectReadyRoomStatic(FullScreen*&fs)
{
	PrepareForFrag(fs);

//DeadCode AMM 08Jan99 	if (_DPlay.UpdateMission)
//DeadCode AMM 08Jan99 	{
//DeadCode AMM 08Jan99 		_DPlay.SendCSQuickStrucToPlayers(FALSE);
//DeadCode AMM 08Jan99 		_DPlay.UpdateMission=FALSE;
//DeadCode AMM 08Jan99 	}

	switch (_DPlay.GameType)
	{
		case TEAMPLAY:
		case DEATHMATCH:
		{
			if	(_DPlay.Side)
			{
				if  (_DPlay.UIPlayerType==PLAYER_HOST)
					fs=&readyroomhostmatch;
				else
					fs=&readyroomguestmatch;
			}else
			{
				if  (_DPlay.UIPlayerType==PLAYER_HOST)
					fs=&readyroomhostmatchred;
				else
					fs=&readyroomguestmatchred;
			}
			break;
		}
#ifndef	MIG_DEMO_VER
		case COMMSQUICKMISSION:
		{
			if	(_DPlay.Side)
			{
				if  (_DPlay.UIPlayerType==PLAYER_HOST)
					fs=&readyroomhostqmission;
				else
					fs=&readyroomguestqmission;
			}else
			{
				if  (_DPlay.UIPlayerType==PLAYER_HOST)
					fs=&readyroomhostqmissionred;
				else
					fs=&readyroomguestqmissionred;

			}
			break;
		}
		case COMMSCAMPAIGN:
		{
			if	(_DPlay.Side)
			{
				if  (_DPlay.UIPlayerType==PLAYER_HOST)
					fs=&readyroomhostcampaign;
				else
					fs=&readyroomguestcampaign;
			}else
			{
				if  (_DPlay.UIPlayerType==PLAYER_HOST)
					fs=&readyroomhostcampaignred;
				else
					fs=&readyroomguestcampaignred;
			}
			break;
		}
#endif
	}
	return TRUE;
}
Bool RFullPanelDial::CreatePlayer(FullScreen*&fs)
{
	incomms=true;
//??rdh	gamestate=QUICK;	//need to set QUICK, MATCH, or CAMP
						//need to get mission description from host to slaves
	switch (_DPlay.GameType)
	{
		case TEAMPLAY:
		{
			gamestate = MATCH;
			break;
		}
		case DEATHMATCH:
		{
			gamestate = MATCH;
			break;
		}
		case COMMSQUICKMISSION:
		{
			gamestate = QUICK;
			break;
		}
		case COMMSCAMPAIGN:
		{
			gamestate = CAMP;
			break;
		}
	}

	pdial[0]->DestroyPanel();
	pdial[0]=NULL;

	Bool res;
	if (_DPlay.UIPlayerType==PLAYER_HOST)
	{
// host now creates session at start of ready room

		res=TRUE;

//DeadCode AMM 12Oct98 		res=_DPlay.UINewPlayer(&_DPlay.PlayerName[0],&_DPlay.SessionName[0]);
//DeadCode AMM 12Oct98 
//DeadCode AMM 12Oct98 		if (res)
//DeadCode AMM 12Oct98 		{
//DeadCode AMM 12Oct98 			res=_DPlay.SetUpPlayerInfo(&_DPlay.PlayerName[0]);
//DeadCode AMM 12Oct98 
//DeadCode AMM 12Oct98 			if (!res)
//DeadCode AMM 12Oct98 			{
//DeadCode AMM 12Oct98 				MessageBox("Could set up player","Whoops",MB_OK);
//DeadCode AMM 12Oct98 			}
//DeadCode AMM 12Oct98 		}
//DeadCode AMM 12Oct98 		else
//DeadCode AMM 12Oct98 		{
//DeadCode AMM 12Oct98 			MessageBox("Could not create session or player","Whoops",MB_OK);
//DeadCode AMM 12Oct98 		}
	}
	else
	{
// already in session

//		res=_DPlay.UINewPlayer(&_DPlay.PlayerName[0],&_DPlay.SessionName[0]);

//		if (res)
		{
// password check

			res=_DPlay.AttemptToJoin();

			if (res)
			{
				res=_DPlay.SetUpPlayerInfo(&_DPlay.PlayerName[0]);

				if (!res)
				{
//DeadCode AMM 14Dec98 					MessageBox("Could not contact host","Warning",MB_OK);
					RMessageBox(IDS_MIGALLEY,IDS_NOTCONTACTHOST,NULL,IDS_CONTINUE);
				}
			}
			else
			{
//DeadCode AMM 14Dec98 				MessageBox("Incorrect password","Warning",MB_OK);
				RMessageBox(IDS_MIGALLEY,IDS_INCORRECTPASSWORD,NULL,IDS_CONTINUE);
			}
		}
//		else
//		{
//			MessageBox("Could not create session or player","Whoops",MB_OK);
//		}
	}

		//temp for comms testing
//DeadCode AMM 12Oct98 	if (incomms)
//DeadCode AMM 12Oct98 	{
//DeadCode AMM 12Oct98 		_DPlay.CurrPlayers = 2;
//DeadCode AMM 12Oct98 		char buffer[10]; 
//DeadCode AMM 12Oct98 		strcpy(buffer, "Macca");
//DeadCode AMM 12Oct98 		strcpy(DPlay::H2H_Player[1].name,buffer);
//DeadCode AMM 12Oct98 	}

	if (res)
	{
		if (_DPlay.GameType!=COMMSCAMPAIGN)
		{
			PrepareForFrag(fs); 									//AMM 13Oct98
			Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
			Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];
			SetTitleText();
		}

		_DPlay.ApplyBackupPilots();

// should be unassigned initially

		MMC.playeracnum=-1;
		MMC.playersquadron=-1;

#ifndef	MIG_DEMO_VER
		if  (	(_DPlay.GameType == COMMSQUICKMISSION)
			&&	(_DPlay.UIPlayerType==PLAYER_HOST)
			)
		{
//			Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
//			Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];
			fs=&commsquick;
		}else if  (	(_DPlay.GameType == COMMSCAMPAIGN)
			&&	(_DPlay.UIPlayerType==PLAYER_HOST)
			)
		{
			if (!_DPlay.campaignloaded)
			{
				whichcamp=_DPlay.GameIndex; //AMM 10/06/99
				SetCampState(fs);
				LaunchMapFirstTime(fs);

// launch map first time sets these up so nobble again

				MMC.playersquadron=-1;
				MMC.playeracnum=-1;
				return FALSE;
			}
		}else
#endif
		{
			SelectReadyRoom(fs);
		}
		if  (	(_DPlay.GameType == TEAMPLAY)
			||		(_DPlay.GameType == DEATHMATCH)
			)
		{
			CSQuick1::quickdef.UpdateAcType();
		}

		return TRUE;
	}
	else
	{
//		_DPlay.DestroyAndClose(_DPlay.myDPlayID);
		LaunchDial(new CLockerRoom,0);
		return FALSE;
	}
}

//DeadCode AMM 06Aug98 Bool RFullPanelDial::RefreshSessions()
//DeadCode AMM 06Aug98 {
//DeadCode AMM 06Aug98  	_DPlay.UIGetSessionListUpdate();
//DeadCode AMM 06Aug98 	return TRUE;
//DeadCode AMM 06Aug98 }

Bool RFullPanelDial::CommsSelectFly(FullScreen*&fs)
{
//DeadCode AMM 18Aug98 	if (_DPlay.Host)											//AMM 15Jul98
//DeadCode AMM 18Aug98 		_Agg.StopResetAggregator();								//AMM 15Jul98

	if (!_DPlay.UINetworkSelectFly())
		return FALSE;

	return TRUE;
}

//DeadCode DAW 01Nov99 #endif	MIG_DEMO_VER

Bool RFullPanelDial::InitReplay(FullScreen*&fs)
{
	_Replay.MenuViewPlayback=true;

	strcpy(_Replay.pfilename,"replay.dat");
//	_Replay.GetReplayFilename(_Replay.filename);

//	_Replay.Record=TRUE;
	return TRUE;
}

//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER

Bool RFullPanelDial::CleanUpComms(FullScreen*&fs)
{
	_DPlay.campaignloaded=false;
	CSQuick1::currquickmiss=-1;

//	_Replay.RestorePrefs();

	_DPlay.ClearPackages();

//DeadCode AMM 14May99 // clear packages 
//DeadCode AMM 14May99 
//DeadCode AMM 14May99 	for (int side = 0; side < 2; side++)
//DeadCode AMM 14May99 	{
//DeadCode AMM 14May99 		for (int wave=0;wave<8;wave++)
//DeadCode AMM 14May99 		{
//DeadCode AMM 14May99 			for (int grp=0;grp<3;grp++)
//DeadCode AMM 14May99 			{
//DeadCode AMM 14May99 				Todays_Packages.pack[side].wave[wave].group[grp].uid = UID_NULL;
//DeadCode AMM 14May99 			}
//DeadCode AMM 14May99 		}
//DeadCode AMM 14May99 	}

	_DPlay.UILeavingMainSheet();
//	_DPlay.DestroyAndClose(_DPlay.myDPlayID);
	_DPlay.ExitDirectPlay();

	if (_DPlay.Lobbied)
	{
		_DPlay.Lobbied=FALSE;
// quit game

		ConfirmExit(fs);
		return FALSE;
	}
	return TRUE;
}

//DeadCode DAW 01Nov99 #endif	MIG_DEMO_VER

LRESULT RFullPanelDial::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL RFullPanelDial::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreCreateWindow(cs);
}

int RFullPanelDial::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

BOOL RFullPanelDial::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void RFullPanelDial::OnEnable(BOOL bEnable) 
{
	CDialog::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	
}

#ifndef	MIG_DEMO_VER

void	RFullPanelDial::ChangeCamp(int campnum)
{
	if (pdial[2]) 
	{
		pdial[2]->PreDestroyPanel();
		pdial[2]->DestroyPanel();
		pdial[2]=NULL;
	}
	if (whichcamp&0x10)
	{
		whichcamp=campnum+0x10;
		LaunchDial(new CCampBack(IDS_CAMPDESC0+campnum),2);
	}
	else
	if (whichcamp&0x20)
	{
		whichcamp=campnum+0x20;
		LaunchDial(new CCampBack(IDS_CAMPOBJ0+campnum),2);
	}
	else
	{
		whichcamp=campnum;
	File_Man.DiscardDirList(FileNum(FIL_SMACK_CAMP1INTRO+whichcamp));
	File_Man.ExistNumberedFile(FileNum(FIL_SMACK_CAMP1INTRO+whichcamp));
#ifdef PROT80
#ifndef MIG_DEMO_VER
		{
			DWORD spc,bps,freec,totc;
			char buffer[80];
			File_Man.NameNumberedFile(FileNum(FIL_SMACK_CAMP1INTRO+whichcamp),buffer);
			buffer[3]=0;
			GetDiskFreeSpace(buffer,&spc,&bps,&freec,&totc);
			spc=((spc*bps)/1024)*totc;
			while (spc<1024*650 || spc>1024*700)
			{
				if (MessageBox(RESSTRING(INSERTCD),buffer,MB_RETRYCANCEL+MB_ICONEXCLAMATION)==IDCANCEL)
					_Error.ReallyEmitSysErr(RESSTRING(FILENOTEXIST),FIL_SMACK_CAMP1INTRO+whichcamp,buffer);
				buffer[3]=0;
				GetDiskFreeSpace(buffer,&spc,&bps,&freec,&totc);
				spc=((spc*bps)/1024)*totc;
			}
		}
#endif
#endif

		OpenSmack(FileNum(FIL_SMACK_CAMP1INTRO+whichcamp),(int)m_hWnd,-1,-1,0,0);
//		OpenSmack(FileNum(FIL_SMACK_CAMP1INTRO+whichcamp),(int)m_hWnd,0,0,640,480);
	}
}										  
Bool	RFullPanelDial::StartCampSmacker(FullScreen*&fs)
{
	if (pdial[2]) 
	{
		pdial[2]->PreDestroyPanel();
		pdial[2]->DestroyPanel();
		pdial[2]=NULL;
	}
	whichcamp=(whichcamp&0x0f);
	File_Man.DiscardDirList(FileNum(FIL_SMACK_CAMP1INTRO+whichcamp));
	File_Man.ExistNumberedFile(FileNum(FIL_SMACK_CAMP1INTRO+whichcamp));
#ifdef PROT80
#ifndef	 MIG_DEMO_VER
		{
			DWORD spc,bps,freec,totc;
			char buffer[80];
			File_Man.NameNumberedFile(FileNum(FIL_SMACK_CAMP1INTRO+whichcamp),buffer);
			buffer[3]=0;
			GetDiskFreeSpace(buffer,&spc,&bps,&freec,&totc);
			spc=((spc*bps)/1024)*totc;
			while (spc<1024*650 || spc>1024*700)
			{
				if (MessageBox(RESSTRING(INSERTCD),buffer,MB_RETRYCANCEL+MB_ICONEXCLAMATION)==IDCANCEL)
					_Error.ReallyEmitSysErr(RESSTRING(FILENOTEXIST),(FIL_SMACK_CAMP1INTRO+whichcamp),buffer);
				buffer[3]=0;
				GetDiskFreeSpace(buffer,&spc,&bps,&freec,&totc);
				spc=((spc*bps)/1024)*totc;
			}
		}
#endif
#endif
	OpenSmack(FileNum(FIL_SMACK_CAMP1INTRO+whichcamp),(int)m_hWnd,-1,-1,0,0);
	return FALSE;
}
Bool	RFullPanelDial::StartCampBackground(FullScreen*&fs)
{
	CloseSmack();
	if (pdial[2]) 
	{
		pdial[2]->PreDestroyPanel();
		pdial[2]->DestroyPanel();
		pdial[2]=NULL;
	}
	whichcamp=(whichcamp&0x0f)+0x10;
	LaunchDial(new CCampBack(IDS_CAMPDESC0+(whichcamp&0x0f)),2);
	return FALSE;
}
Bool	RFullPanelDial::StartCampObjectives(FullScreen*&fs)
{
	CloseSmack();
	if (pdial[2]) 
	{
		pdial[2]->PreDestroyPanel();
		pdial[2]->DestroyPanel();
		pdial[2]=NULL;
	}
	whichcamp=(whichcamp&0x0f)+0x20;
	LaunchDial(new CCampBack(IDS_CAMPOBJ0+(whichcamp&0x0f)),2);
	return FALSE;
}
Bool	RFullPanelDial::StartCampBackground2(FullScreen*&fs)
{
 	if (pdial[2]) 
 	{
 		pdial[2]->PreDestroyPanel();
 		pdial[2]->DestroyPanel();
 		pdial[2]=NULL;
 	}
	whichcamp=(whichcamp&0x0f)+0x10;
	LaunchDial(new CCampBackEntireWar(IDS_CAMPDESC0+(whichcamp&0x0f)),2);
	return FALSE;
}
Bool	RFullPanelDial::StartCampObjectives2(FullScreen*&fs)
{
	if (pdial[2]) 
	{
		pdial[2]->PreDestroyPanel();
		pdial[2]->DestroyPanel();
		pdial[2]=NULL;
	}
	whichcamp=(whichcamp&0x0f)+0x20;
	LaunchDial(new CCampBackEntireWar(IDS_CAMPOBJ0+(whichcamp&0x0f)),2);
	return FALSE;
}

#endif	//MIG_DEMO_VER

Bool	RFullPanelDial::TitleInit()
{
	_Replay.TruncateTempFiles();	//AMM13Jul99
	_Replay.MenuViewPlayback=false;
	incomms=in3d=false;
	gamestate=TITLE;
	SetTitleText(true);

	return	TRUE;
}

Bool	RFullPanelDial::SetUpHotShot(FullScreen*&fs)
{
	CSQuick1::currquickmiss=9;
	CSQuick1::quickdef=CSQuick1::quickmissions[9]; //FB strike
	Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];
	SetTitleText();
	CSQuick1::currquickmiss=-1;

	gamestate=HOT;
	return TRUE;
}

Bool	RFullPanelDial::SetQuickState(FullScreen*&fs)
{
//DeadCode AMM 14Oct98 	_DPlay.CurrPlayers = 0;		//##

	Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];
	Miss_Man.camp.Sky.Conditions = 0; //always clear for quick missions
	Miss_Man.camp.currtime =  HR12;		//always midday
	gamestate=QUICK;
	SetTitleText();

	return TRUE;
}
Bool	RFullPanelDial::SetCampState(FullScreen*&fs)
{
//DEADCODE RDH 15/02/99 	Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
//DEADCODE RDH 15/02/99 	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];
	gamestate=CAMP;
	return TRUE;
}

Bool	RFullPanelDial::SetUpFullWar(FullScreen*&fs)
{
//DEADCODE RDH 15/02/99 	Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
//DEADCODE RDH 15/02/99 	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];
	gamestate=WAR;
	return TRUE;
}

Bool	RFullPanelDial::IfCommsToReadyRoom(FullScreen*&fs)
{
	//CLEAN UP CAMPAIGN RECORD FOR NEXT TIME. Should really do it before going in, but Macca is nesh :-) //JIM 30/06/99	//CSB 02/07/99	

// ta for breaking the code, guests should NOT clear campaign structure as they
// can choose a new ac and reenter game.	. // AMM29/09/99

	if ((!_DPlay.PlayerCreated) || (_DPlay.PlayerCreated && _DPlay.Host))	//AMM29/09/99
		Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];	//CSB 02/07/99	

#ifndef	MIG_DEMO_VER
	if (incomms)
	{

//		fs=&readyroom;
		SelectReadyRoom(fs);
// after setting up campaign nullify hosts
// position so that in frag slot is initially free
		if (_DPlay.GameType>TEAMPLAY)
		{
			MMC.playersquadron=-1;
		}
	}
#endif	//MIG_DEMO_VER
	if (gamestate==HOT)
		fs=&singleplayer;
	return CheckForDemo(fs);
}
Bool	RFullPanelDial::PreferencesExitPath(FullScreen*&fs)
{
	if (in3d)
	{
		fs=&quickmissionflight;
		return TRUE;
	}
	else
		if (gamestate==TITLE)
			fs=&title;
//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER
		else if (incomms)
				SelectReadyRoom(fs);
#ifndef	MIG_DEMO_VER
			else 
				fs = &singlefrag;
#endif

	return CheckForDemo(fs);
}

#ifndef	MIG_DEMO_VER

Bool	RFullPanelDial::MapSpecialsInit()
{
//DEADCODE RDH 26/06/99 	LaunchSmacker(1, MMC.smacker);
//DEADCODE RDH 26/06/99 	for (int i=0; i < Debrief::DISISITFORTODAY; i++)
//DEADCODE RDH 26/06/99 		if 	(MMC.smacker == SupplyTree::dissmackers[i].file)
//DEADCODE RDH 26/06/99 			break;
//DEADCODE RDH 26/06/99 	int text = 0;
//DEADCODE RDH 26/06/99 	if (i != Debrief::DISISITFORTODAY)			
//DEADCODE RDH 26/06/99 		text = MMC.debrief.disday[i].msgtextid; 
//DEADCODE RDH 26/06/99 
//DEADCODE RDH 26/06/99 	if (text)
//DEADCODE RDH 26/06/99 		LaunchDial(new CCampBack(RESTABLESUM(2,DISPARA_0,text)),2);
//DEADCODE RDH 26/06/99 
	return TRUE;
}
Bool	RFullPanelDial::EndCampInit()								  //RDH 29/06/99
{
	if (Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
	{
		int index;
		index =  SupplyTree::FindBattleIndex();
					
		if (index < 6)
			LaunchSmacker(1, MMC.camp_win_anim);
		else
		{
			if (index > 6)
				index = 6;
			LaunchSmacker(1, MMC.camp_lost_anim);
		}
		LaunchDial(new CCampBack(IDS_CAMP5_END00 + index),2);

	}else
	{
		if (MMC.wincamp)
		{
			LaunchSmacker(1, MMC.camp_win_anim);
			LaunchDial(new CCampBack(IDS_CAMP1ENDGOOD + Miss_Man.currcampaignnum),2);
		}else
		{
			LaunchSmacker(1,MMC.camp_lost_anim);
			LaunchDial(new CCampBack(IDS_CAMP1ENDBAD + Miss_Man.currcampaignnum),2);
		}
	}
	return TRUE;
}

Bool	RFullPanelDial::DeadPilotInit()
{
		LaunchSmacker(1, MMC.introsmack);
		LaunchDial(new CCampBack(IDS_PLAYERDIED),2);
	return TRUE;
}
Bool	RFullPanelDial::SpecialsInit()
{
		LaunchSmacker(1, MMC.smacker);
		LaunchDial(new CCampBack(RESTABLESUM(2,DISPARA_0,MMC.msgwithsmacker)),2);
	return TRUE;
}
Bool	RFullPanelDial::ContinueAlthoughDead(FullScreen*&fs)
{
 
	MMC.Active_Pilots[MMC.playersquadron*24+MMC.playeracnum].status = NOTFLYING;
//DEADCODE RDH 31/05/99 	if (incomms || true)	//test for alive...
//DEADCODE RDH 31/05/99 	{
		if  (		(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
			)
		{
			if	(MMC.directives.autodisplay)
				MainToolBar().OpenDirectives();	
		}else
			MainToolBar().OpenDis();

		return LaunchMap(fs, true);
//DEADCODE RDH 31/05/99 	}
//DEADCODE RDH 31/05/99 	else
//DEADCODE RDH 31/05/99 		fs=&title;

	return TRUE;
}
Bool	RFullPanelDial::ContinueAfterSpecialDebrief(FullScreen*&fs)
{
 	MMC.msgwithsmacker = 0;

	if  (		(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
		)
	{
		if	(MMC.directives.autodisplay)
			MainToolBar().OpenDirectives();	
	}else
		MainToolBar().OpenDis();

	return LaunchMap(fs, true);

	return TRUE;
}
Bool	RFullPanelDial::ReloadBecauseDead(FullScreen*&fs)
{
	char buffer[150];
//DEADCODE RDH 31/05/99 	if (incomms || true)	//test for alive...
//DEADCODE RDH 31/05/99 	{
		BIStream bis(File_Man.namenumberedfile(
			File_Man.fakefile(FIL_SAVEGAMEDIR,"Auto Save.sav"),buffer));
		if (bis.is_open())
			bis>>Miss_Man;

		if  (		(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
			)
		{
			if	(MMC.directives.autodisplay)
				MainToolBar().OpenDirectives();	
		}else
			MainToolBar().OpenDis();
		return LaunchMap(fs, true);
//DEADCODE RDH 31/05/99 	}
//DEADCODE RDH 31/05/99 	else
//DEADCODE RDH 31/05/99 		fs=&title;

	return TRUE;
}

Bool	RFullPanelDial::StartNextCampaign(FullScreen*&fs)
{
	Miss_Man.currcampaignnum = MissMan::CampaignName((int)Miss_Man.currcampaignnum + 1);
	whichcamp = -1;

	char	PlayerName[PLAYERNAMELEN];
	memcpy(PlayerName,MMC.PlayerName,PLAYERNAMELEN);
	Miss_Man.camp = Miss_Man.campaigntable[Miss_Man.currcampaignnum];	//RDH 15/02/99	
	memcpy(MMC.PlayerName,PlayerName,PLAYERNAMELEN);

	LaunchMapFirstTime(fs);

	return TRUE;
}

Bool	RFullPanelDial::LaunchMapIfAlive(FullScreen*&fs)
{
	if (incomms || true)	//test for alive...
	{
		if (MMC.Active_Pilots[MMC.playersquadron*24+MMC.playeracnum].status >= IS_DEAD)
			MainToolBar().OnClickedMissionlog();
		else
			DebriefToolBar().OpenMissionresults();
		return LaunchMap(fs, true);
	}
	else
		fs=&title;

	return TRUE;
}

Bool	RFullPanelDial::LaunchMapFirstTime(FullScreen*&fs)
{
	FileNum f;
//	m_pView->GetDocument()->SetTitle(LoadResString(IDS_L_SCAMPAIGNSELECT1+(whichcamp&0x0f)));
	for (f=FIL_MIDMAP;f<FIL_MIDMAP+(6*4);f=(FileNum)(f+1))
		delete new fileblock(f);
	for (f=FIL_MAP_BUTTON1;f<FIL_ICON_NEXT_PERIOD;f=(FileNum)(f+1))
		delete new fileblock(f);
	Todays_Packages.WipeAll();
	if (whichcamp>=0)
	{
		Miss_Man.currcampaignnum = MissMan::CampaignName(whichcamp&0x0f);							//RDH 19/03/99
		Miss_Man.camp = Miss_Man.campaigntable[Miss_Man.currcampaignnum];	//RDH 15/02/99	
		Miss_Man.camp.inentirewar=(gamestate==WAR);
	}
	SetTitleText();

//DEADCODE RDH 19/03/99 	Miss_Man.currcampaignnum = MissMan::SO51_CAMPAIGN;				//RDH 15/02/99
//DEADCODE RDH 19/03/99 	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SO51_CAMPAIGN]; //RDH 15/02/99	
	Persons4::StartUpMapWorld();
	
	SupplyTree::ProcessAirFields();
	DirControl	dir_ctrl;
	Miss_Man.camp.directives.B29avail = true;						  //RDH 14/06/99
	if  (Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
	{
		dir_ctrl.LoadDirectiveChanges();
		dir_ctrl.AllocateAc();
		dir_ctrl.SetPackagesFromDirectives();
		dir_ctrl.SaveDirectiveChanges();
	}else
	{
		dir_ctrl.MakeMiniCampaignMission();
	}
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	main->m_titlebar.Redraw();
	CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
	MainToolBar().OpenPlayerlog();	
//	pmainwnd->m_toolbar2.OnClickedPlayerlog();	
	return LaunchMap(fs, true);
}
Bool	RFullPanelDial::DoLoadCommsGame(FullScreen*&fs)
{
	CFiling::LoadGame(selectedfile);
	if (selectedfile=="" || selectedfile==".sav")
		return FALSE;
	Save_Data.lastsavegame = selectedfile;
//DEADCODE RDH 28/05/99 	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
//DEADCODE RDH 28/05/99 	main->m_titlebar.Redraw();

//	strcpy(_DPlay.Password,MMC.CommsPassword);
//	strcpy(_DPlay.Password,Save_Data.CommsPassword);
	_DPlay.campaignloaded=true;
	if (CreatePlayer(fs))
	{
		SetCampState(fs);
		LaunchMap(fs, true);										//AMM 22Jan99
	}

	return FALSE;												//AMM 22Jan99

//DeadCode AMM 22Jan99 	return TRUE;
}
Bool	RFullPanelDial::DoLoadGame(FullScreen*&fs)
{
	if (selectedfile=="" || selectedfile==".sav")
		return FALSE;
	if (!CFiling::LoadGame(selectedfile))
		return FALSE;
	Save_Data.lastsavegame = selectedfile;
//DEADCODE RDH 28/05/99 	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
//DEADCODE RDH 28/05/99 	main->m_titlebar.Redraw();
//DeadCode DAW 27Jun99 	Persons4::StartUpMapWorld();
	return LaunchMap(fs, false);
}

#endif	//#ifndef	MIG_DEMO_VER

void RFullPanelDial::OnPaint() 
{
	if (artnum)
		CDialog::OnPaint();
	else
	{
		PAINTSTRUCT paintstruct;
		CDC* pDC;
		pDC=BeginPaint(&paintstruct);
		Rtestsh1::Setup3dStatuses state=Rtestsh1::Start3d(Rtestsh1::S3D_DONEBACK);
		if (state==Rtestsh1::S3D_STOPPED)
		{
			paintstruct.fErase=TRUE;
			CRect rect;
			GetClientRect(rect);
			pDC->FillSolidRect(rect,RGB(0,0,0));
		}
		else
		if (state==Rtestsh1::S3D_STARTSETUP)
		{
			paintstruct.fErase=TRUE;
			CRect rect;
			GetClientRect(rect);
			pDC->FillSolidRect(rect,RGB(0,0,0));	//RGB(160,184,208));
		}
		EndPaint(&paintstruct);
		
	}

}

////////////////////////////////////////////////////////////////////////
//
// Function:    OnGetArt
// Date:        18/01/99
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
FileNum RFullPanelDial::OnGetArt()
{
	return artnum;
}


Bool	RFullPanelDial::CheckForDemo(FullScreen*&fs)	
{
	if (!_DPlay.Lobbied)
	{
		if (	!File_Man.ExistNumberedFile(FIL_SMACK_CAMP1INTRO)
			||	!File_Man.ExistNumberedFile(DIR_FRONTMAP)
			||	!File_Man.ExistNumberedFile(FIL_M_WET)
		
			)
			fs=&demotitle;
	}
	return	TRUE;
}

void	DPlay::FillCSQuickStruc()
{
	ULong n;

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (DPlay::H2H_Player[n].squadron==-1)					//AMM 08Nov98
		{														//AMM 08Nov98
			DPlay::H2H_Player[n].squadron=0;					//AMM 08Nov98
		}														//AMM 08Nov98

		if (DPlay::H2H_Player[n].status!=CPS_NONE)
		{
// for now use just blue field to store AC. 
// actype=playersquadron
// flight=1
// only 1st grouyp gets filled in for deathmatch

			CSQuick1::quickdef.line[0][n][0].actype=DPlay::H2H_Player[n].squadron;
			CSQuick1::quickdef.line[0][n][0].flights=1;

		}
		else
		{
			CSQuick1::quickdef.line[0][n][0].actype=0; // empty slots use default actype0(f86a)
			CSQuick1::quickdef.line[0][n][0].flights=1;
		}
	}
}

Bool RFullPanelDial::CheckLobby(FullScreen*&fs)
{
//		UpdateSize();												  //DAW 15/06/99
																	  //DAW 15/06/99
		_Miles.InitSoundFonts();		//RJS 24Nov98				  //DAW 15/06/99

	
//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER
//DeadCode DAW 29Oct99 	if (_DPlay.LaunchedByLobby())
	if (_DPlay.Lobbied)
	{
		fs=&multiplayer;
	}else
//DeadCode DAW 01Nov99 #endif
		_DPlay.lpDPL=NULL;;
	return CheckForDemo(fs);
}

//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER

Bool RFullPanelDial::CanGuestJoin(FullScreen*&fs)
{
// wowa - only go in here if we are joining..............
	if (!_DPlay.FlyNowFlag)
	{
		if (_DPlay.GameAvailable)
		{
			if (!_DPlay.JoinGame())
			{
				DPlay::H2H_Player[_DPlay.mySlot].status=CPS_READYROOM;
				_DPlay.SendInReadyRoomMessage();
				return FALSE;
			}
//DeadCode DAW 27Jun99 				return FALSE;

			return TRUE;
		}
	}
	else 
		return TRUE;

	return FALSE;
}

//DeadCode DAW 01Nov99 #endif	//#ifndef	MIG_DEMO_VER

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendCSQuickStrucToPlayers
//Author		Andy McMaster
//Date			Sun 8 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DPlay::SendCSQuickStrucToPlayers(Bool init)
{
//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER
	if (GameType==COMMSQUICKMISSION)
	{
		GameIndex=CSQuick1::currquickmiss;
	}
	SendCS((UByte*)&CSQuick1::quickdef,sizeof(QuickDef),init);
//DeadCode DAW 01Nov99 #endif	//#ifndef	MIG_DEMO_VER
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateCSQuick
//Author		Andy McMaster
//Date			Sun 8 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DPlay::UpdateCSQuick(UByte* pack,ULong num)
{
//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER
	memcpy(&CSQuick1::quickdef,pack,sizeof(QuickDef));
	CSQuick1::currquickmiss=num;

// need to call PrepareForFrag

	Todays_Packages.PackagePrepareForFrag();
//DeadCode DAW 01Nov99 #endif	//#ifndef	MIG_DEMO_VER
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PackagePrepareForFrag
//Author		Andy McMaster
//Date			9 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	PackageList::PackagePrepareForFrag()
{
//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER
	int side,wave,grp;

	switch (_DPlay.GameType)
	{
		case TEAMPLAY:
		case DEATHMATCH:
			side=0;
			for (wave=0;wave<8;wave++)
			{
				for (grp=0;grp<3;grp++)
				{
					if (CSQuick1::quickdef.line[side][wave][grp].flights != 0)
					{
						Todays_Packages.pack[side].wave[wave].group[grp].uid = IllegalSepID; //UID_StChosan;
						Todays_Packages.pack[side].wave[wave].group[grp].SetFlights( 
									CSQuick1::quickdef.line[side][wave][grp].flights);
						Todays_Packages.pack[side].wave[wave].group[grp].SetSquad( 
								CSQuick1::quickdef.line[side][wave][grp].actype);
					Todays_Packages.pack[side].wave[wave].group[grp].callname = -1;
					}			
				}
			}
			break;

#ifndef	MIG_DEMO_VER
		case COMMSQUICKMISSION:
		{
//DeadCode AMM 04May99 			int side;
//DeadCode AMM 04May99 
//DeadCode AMM 04May99 			if (_DPlay.GameType==COMMSQUICKMISSION)
//DeadCode AMM 04May99 			{
//DeadCode AMM 04May99 				if (_DPlay.Side)
//DeadCode AMM 04May99 					side = 0;
//DeadCode AMM 04May99 				else
//DeadCode AMM 04May99 					side = 1;
//DeadCode AMM 04May99 			}
//DeadCode AMM 04May99 			else
//DeadCode AMM 04May99 			{
//DeadCode AMM 04May99 // for now put all players in same side even for teamplay
//DeadCode AMM 04May99 				side=0; 
//DeadCode AMM 04May99 			}	
//DeadCode AMM 04May99 
//DeadCode AMM 04May99 //			for (int side = 0; side < 2; side++)
			for (side = 0; side < 2; side++)
			{
				 for (wave=0;wave<8;wave++)
				 {
					for (grp=0;grp<3;grp++)
					{
						if (CSQuick1::quickdef.line[side][wave][grp].flights != 0)
						{
// package side is different to dplay side
							if (side!=_DPlay.Side && _DPlay.SideSelected)
								Todays_Packages.pack[side].wave[wave].group[grp].uid = IllegalSepID; //UID_StChosan;
							Todays_Packages.pack[side].wave[wave].group[grp].SetFlights( 
										CSQuick1::quickdef.line[side][wave][grp].flights);
							Todays_Packages.pack[side].wave[wave].group[grp].SetSquad( 
									CSQuick1::quickdef.line[side][wave][grp].actype);
						Todays_Packages.pack[side].wave[wave].group[grp].callname = -1;
						}else										  //RDH 08/06/99
							Todays_Packages.pack[side].wave[wave].group[grp].uid = UID_NULL; //RDH 08/06/99
					}
				 }
			}
			break;
		}
		case COMMSCAMPAIGN:
		{
			//temp to fill mig is for testing purposes
//			int side = 1;
//			int side=0;
			for (side = 0; side < 2; side++)
			{
				 for (int wave=0;wave<8;wave++)
				 {
					for (int grp=0;grp<3;grp++)
					{
						if (CSQuick1::quickdef.line[side][wave][grp].flights != 0)
						{
							Todays_Packages.pack[Profile::MAX_PACKS ].wave[wave].group[grp].uid = IllegalSepID; //UID_StChosan;
							Todays_Packages.pack[Profile::MAX_PACKS ].wave[wave].group[grp].SetFlights( 
										CSQuick1::quickdef.line[side][wave][grp].flights);
							Todays_Packages.pack[Profile::MAX_PACKS ].wave[wave].group[grp].SetSquad( 
									CSQuick1::quickdef.line[side][wave][grp].actype);
						Todays_Packages.pack[Profile::MAX_PACKS ].wave[wave].group[grp].callname = -1;
						}			
					}
				 }
			}
			
			break;
		}
#endif	//#ifndef	MIG_DEMO_VER

	}
//DeadCode DAW 01Nov99 #endif	//#ifndef	MIG_DEMO_VER
}

Bool RFullPanelDial::ReInitCommsInterface(FullScreen*&fs)
{
#ifndef	MIG_DEMO_VER
	_DPlay.lpDP4->Release();

	if (!_DPlay.CreateDPlayInterface())
	{
// if cant get a new dplay interface then go back to main menu

		fs=&title;
	}

#endif	//#ifndef	MIG_DEMO_VER
	return TRUE;
}

Bool	RFullPanelDial::LobbyCheck(FullScreen*&fs)
{
//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER

	_DPlay.campaignloaded=false;
	CSQuick1::currquickmiss=-1;
	_DPlay.ClearPackages();

	if (_DPlay.Lobbied)
	{
		_DPlay.ExitDirectPlay();
		_DPlay.Lobbied=FALSE;

		ConfirmExit(fs);
		return FALSE;
	}
#ifndef	MIG_DEMO_VER
	else if (_DPlay.UIPlayerType==PLAYER_HOST || _DPlay.singlesession)
	{
		_DPlay.ExitDirectPlay();
		_DPlay.StartCommsSession();
		fs=&selectservice;
	}
	else
	{
		if (!_DPlay.UIGetSessionListUpdate())
		{
// problem initialising connection, exit to main menu

			_DPlay.CommsMessage(IDS_BADSESSIONS2);
			_DPlay.ExitDirectPlay();
			fs=&title;
		}
	}
#endif	//#ifndef	MIG_DEMO_VER
	return TRUE;
}

void	DPlay::CommsMessage(UINT mess)
{
	RDialog::RMessageBox(IDS_MIGALLEY,mess,NULL,IDS_OK);
}

//DeadCode DAW 01Nov99 #ifndef	MIG_DEMO_VER
Bool	DPlay::LoadRadioMessages()
{
	char buffer[150];
 	ULong n;

//	BIStream bis			//rdh 10/2/99
	File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,"radio.txt"),buffer);//rdh 10/2/99

//DeadCode AMM 17Feb99 	FILE* fp=fopen(buffer,"rt");

	HANDLE messfile;
//	int ch,index;
	bool ok;
	DWORD numread;
//	char rmess[128];

	messfile=CreateFile(
		buffer,
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

//DeadCode AMM 17Feb99 	if (!fp)
	if (messfile==INVALID_HANDLE_VALUE || !GetFileSize(messfile,NULL))
	{
//DeadCode AMM 24Feb99 		InitMessages();
		InitMessages();		//rdh 10/2/99
		return FALSE;
	}
	else
	{
		for (n=0;n<NUMRADIOMESSAGES;n++)
		{
//DeadCode AMM 18Feb99 			index=0;
//DeadCode AMM 18Feb99 			do
//DeadCode AMM 18Feb99 			{
//DeadCode AMM 18Feb99 //DeadCode AMM 17Feb99 				ch=fgetc(fp);
//DeadCode AMM 18Feb99 
//DeadCode AMM 18Feb99 				ok=ReadFile(
//DeadCode AMM 18Feb99 					messfile,
//DeadCode AMM 18Feb99 					&ch,
//DeadCode AMM 18Feb99 					1,
//DeadCode AMM 18Feb99 					&numread,
//DeadCode AMM 18Feb99 					NULL);
//DeadCode AMM 18Feb99 
//DeadCode AMM 18Feb99 				if (ok)
//DeadCode AMM 18Feb99 				{
//DeadCode AMM 18Feb99 					if (ch!='\0' && ch!='\n')
//DeadCode AMM 18Feb99 						Messages[mySlot][n][index++]=ch;
//DeadCode AMM 18Feb99 
//DeadCode AMM 18Feb99 				}
//DeadCode AMM 18Feb99 			} while (ch!='\0' && ch!='\n' && ok && index<127);
//DeadCode AMM 18Feb99 //DeadCode AMM 17Feb99 			} while (ch!='\0' && ch!='\n' && feof(fp)==0 && index<127);
//DeadCode AMM 18Feb99 
//DeadCode AMM 18Feb99 			Messages[mySlot][n][index]='\0';

//				ok=
					ReadFile(
					messfile,
					Messages[mySlot][n],
					128,
					&numread,
					NULL);										  //DAW 09/03/99
		}
//DeadCode AMM 17Feb99 		fclose(fp);
		CloseHandle(messfile);
	}
	return TRUE;
}

void	DPlay::SaveRadioMessages()
{
	char buffer[150];
//	char nl='\n';
	ULong n,numwrote;
//	char rmess[128];

//	BIStream bis(File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,"radio.txt"),buffer));
	File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,"radio.txt"),buffer);

//DeadCode AMM 17Feb99 	FILE* fp=fopen(buffer,"wt");
	HANDLE	messfile;

	messfile=CreateFile(
		buffer,
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		0,
		NULL);

	for (n=0;n<NUMRADIOMESSAGES;n++)
	{
//DeadCode AMM 18Feb99 		len=strlen(Messages[mySlot][n]);
//DeadCode AMM 17Feb99 		fprintf(fp,"%s\n",Messages[mySlot][n]);

//		len=strlen(Messages[mySlot][n]);
//		strncpy(rmess,Messages[mySlot][n],127);
//		rmess[127]='\n';

		WriteFile(
			messfile,
			Messages[mySlot][n],
			128,
			&numwrote,
			NULL);
	}

	CloseHandle(messfile);
//DeadCode AMM 17Feb99 	fclose(fp);
}
//DeadCode DAW 01Nov99 #endif	//#ifndef	MIG_DEMO_VER

void	Replay::GetReplayFilename(char* buff)
{
	char buffer[50];

	strcpy(buffer,buff);

//	BIStream bis(File_Man.namenumberedfile(File_Man.fakefile(FIL_VIDEOS_START_DIR,buffer),buff));
	File_Man.namenumberedfile(File_Man.fakefile(FIL_VIDEOS_START_DIR,buffer),buff);

}

void	DPlay::GetCommsSavename(char* buff)
{
	char buffer[50];

	strcpy(buffer,buff);

//	BIStream bis(File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,buffer),buff));
	File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,buffer),buff);
}

void	DPlay::GetLastSaveName(char* buff)
{
	strcpy(buff,Save_Data.lastsavegame);
}

#ifndef	MIG_DEMO_VER
Bool	RFullPanelDial::ReplaySaveBack(FullScreen*&fs)
{
	if (_Replay.RestorePosition)
	{
		_Replay.Playback=TRUE;
//DeadCode AMM 30Mar99 #pragma warnmsg("Is pause still needed here (replay)?")
//DEADCODE DAW 28/03/99 		Timer_Code.paused=TRUE;
		fs=&quickmissionflight;
	}
	else if (_Replay.IsCampState(gamestate))
	{
// launch map debrief

//DEADCODE RDH 22/03/99 		MMC.indebrief = true;
//DEADCODE RDH 22/03/99 		if (specialevent)
//DEADCODE RDH 22/03/99 			if (gamestate == WAR)
//DEADCODE RDH 22/03/99 				LaunchScreen(&warmapspecials);
//DEADCODE RDH 22/03/99 			else
//DEADCODE RDH 22/03/99 				LaunchScreen(&mapspecials);
//DEADCODE RDH 22/03/99 		else	
//DEADCODE RDH 22/03/99 		{
		LaunchMap(fs, false);
//DEADCODE RDH 22/03/99 		}
		return FALSE;
	}
	else
		if (gamestate==HOT)
		{
			fs=&singleplayer;
			return CheckForDemo(fs);
		}
		else
			fs=&quickmission;

// else back to quickmissiondebrief

	return TRUE;
}
#endif	//#ifndef	MIG_DEMO_VER

Bool	RFullPanelDial::ReplayLoadBack(FullScreen*&fs)
{
#ifndef	MIG_DEMO_VER
	if (_Replay.IsCampState(gamestate))
	{
		LaunchMap(fs, false);
		return FALSE;
	}
#endif	//#ifndef	MIG_DEMO_VER
	return CheckForDemo(fs);
}

bool	DPlay::LoadDummySavegame(char* name)
{
//DeadCode AMM 17Mar99 	bool retval;
//DeadCode AMM 22Jan99 	CString	temp="dcomms.sav";
	CString	temp=name;

	bool retval;

	retval=CFiling::LoadGame(temp);

	if (retval)
		Todays_Packages.SaveBin(); 

	return retval;

//DeadCode AMM 16Jun99 	return (CFiling::LoadGame(temp));
//DeadCode AMM 17Mar99 	retval=(CFiling::LoadGame(temp));
//DeadCode AMM 17Mar99 
//DeadCode AMM 17Mar99 	if (retval && RFullPanelDial::incomms)
//DeadCode AMM 17Mar99 		Todays_Packages.PackagePrepareForFrag();
//DeadCode AMM 17Mar99 
//DeadCode AMM 17Mar99 	return retval;
}

ULong	Replay::GetState()
{
	return RFullPanelDial::gamestate;
}

void	Replay::SetState(ULong state)							//AMM 31Mar99
{																//AMM 31Mar99
	RFullPanelDial::gamestate=(RFullPanelDial::GameStates)state;							//AMM 31Mar99
}																//AMM 31Mar99

bool	Replay::IsCampState(ULong state)
{
	if (state==RFullPanelDial::CAMP
	||  state==RFullPanelDial::WAR)
		return true;

	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveTempSaveGame
//Author		Andy McMaster
//Date			Fri 22 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	Replay::SaveTempSaveGame(char* name, bool pack)
{
// save game as dreplay.sav for writing to header

	CString	temp=name;

	Todays_Packages.SaveBin();

	return (CFiling::SaveGame(temp));
}

Bool	RFullPanelDial::DebriefReplayCheck(FullScreen*&fs)
{
//CLEAN UP CAMPAIGN RECORD FOR NEXT TIME. Should really do it before going in, but Macca is nesh :-) //JIM 30/06/99
//DeadCode DAW 09Jul99 	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];

	if (incomms)
		return FALSE;

	if (_Replay.badrecord)
	{

		RMessageBox(IDS_MIGALLEY,IDS_BADREPLAY,NULL,IDS_CONTINUE);
		return FALSE;
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TruncateTempFiles
//Author		Andy McMaster
//Date			Thu 13 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Replay::TruncateTempFiles()
{
	char buffer[128];

	File_Man.namenumberedfile(File_Man.fakefile(FIL_VIDEOS_START_DIR,"replay.dat"),buffer);
	TruncateFile(buffer);

	File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,"dreplay.dat"),buffer);
	TruncateFile(buffer);

	File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,"dcomms.dat"),buffer);
	TruncateFile(buffer);

	File_Man.namenumberedfile(File_Man.fakefile(FIL_VIDEOS_START_DIR,"tblock.dat"),buffer);
	TruncateFile(buffer);

	File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,"rbackup.dat"),buffer);
	TruncateFile(buffer);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearPackages
//Author		Andy McMaster
//Date			Fri 14 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DPlay::ClearPackages()
{
	for (int side = 0; side < 2; side++)
	{
		for (int wave=0;wave<8;wave++)
		{
			for (int grp=0;grp<3;grp++)
			{
				Todays_Packages.pack[side].wave[wave].group[grp].uid = UID_NULL;
			}
		}
	}

	if (GameType<COMMSQUICKMISSION)
	{
		for (int s = 0; s < 2; s++)
		{
			for (int w=0;w<8;w++)
			{
				for (int g=0;g<3;g++)
				{
					CSQuick1::quickdef.line[s][w][g].flights=0;
					CSQuick1::quickdef.line[s][w][g].actype=-1;
				}
			}
		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectRRVariants
//Author		Dave Whiteside
//Date			Sun 27 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	RFullPanelDial::SelectRRVariants(FullScreen*&fs)
{
	if (_DPlay.Host)
		return TRUE;

	return FALSE;
}
