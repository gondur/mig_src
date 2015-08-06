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

//
//WinMode:	stub3d.cpp
//
//TASK:		manages the 3d thread
//
//ROUTINES:	presently about 5 routines:
//
//	MakeInteractive(WinMode,Coords)
//	MakePassive(WinMode,Coords)
//	MakeResize(WinMode,Coords)
//	ToggleInteractive(bool)
//	TogglePaused(bool)
//	ToggleAccel(bool)
//	DeleteWorld()
//	
//	WinMode:	
//		FullScreen/Windowed/DualScreen 
//							0x0000,0x1000,0x2000
//		Accelerated			0x000=no,0x100=yes,
//							0x10n=specific card									
//							0x1m0=specific mode


#include	"stdafx.h"
#include	<afxmt.h>
#include	<dinput.h>
#include	<mmsystem.h>
#include	"dosdefs.h"

#include	"stub3d.h"
#include	"keytest.h"


#include	"hardpasm.h"
#include	"worldinc.h"
#include	"aaa.h"
#include	"flymodel.h"
#include	"mytime.h"
#include	"ai.h"
#include	"persons2.h"
#include	"collided.h"
#include	"3dcode.h"
#include	"world.h"
#include	"shapes.h"
//#include	"lstream.h"
#include	"3dinstr.h"
#include	"savegame.h"
#include	"winmove.h"
#include	"miles.h"
#undef LPDDCAPS
#include	"win3d.h"
#include	"polygon.h"
#include	"Analogue.h"
#include	"transite.h"
#include	"ViewSel.h"
#include	"rchatter.h"										//RJS 11Jun98
#include	"replay.h"
#include	"globrefs.h"
#include	"replay.h"
#include	"aggrgtor.h"
#include	"OverLay.h"
#include	"messengn.h"										//RJS 27Jan99
#include	"3dcom.h"											//RJS 08Apr99

enum	{BUFFERED_KEYS=100};

//extern ULong 
//		GR_FriendlyScoutType00,									//JIM 09Apr96
//		GR_Quit3DNow,
//		GR_OkToQuit3DNow;
static	volatile Bool	insidetimer = FALSE;

//inline	int	LockExchange(int* loc,int newval=0)
//{
//	int rv;
//	_asm	{	mov		eax,newval
//				mov		ebx,loc
//				xchg	ds:[ebx],eax
//				mov		rv,eax
//			}
//	return	rv;
//}
extern Replay _Replay;
extern UByte videoBuffer;
extern bool mono3d;
LogStack	Log_Stack={{{0}}};
///////////////////////////////////////////////////////////////////////

//HANDLE	View3d::htable[NUM_EVENTS];
//LPDIRECTINPUT  Inst3d::Master_3d.g_lpDI=NULL;
//LPDIRECTINPUTDEVICE  Inst3d::Master_3d.g_lpDIDevice=NULL;
//HINSTANCE	View3d::hinst=NULL;
//HWND		View3d::hwind=NULL;
///View3d*		Inst3d::viewedwin=NULL;
//char		Inst3d::lastkeys[256]={0};
//Inst3d*		Inst3d::Master_3d.currinst=NULL;
KeyMap3d*	Inst3d::commonkeymaps=NULL;
extern	KeyMapping	*Debug3dMapTable;

Mast3d	Master_3d;
///////////////////////////////////////////////////////////////////////
Mast3d::Mast3d()
{
	TIMECAPS tcaps;
	timeGetDevCaps ( &tcaps, sizeof (TIMECAPS));
//DEADCODE DAW 10/02/00 	int wTimerRes = min(max(tcaps.wPeriodMin,1),tcaps.wPeriodMax);
//DEADCODE DAW 10/02/00 //DEADCODE DAW 10/02/00 	if (wTimerRes<20)	//milisecs
	wTimerRes=max(tcaps.wPeriodMin,1);
	timeBeginPeriod (wTimerRes);
	uTimerID = timeSetEvent (20, wTimerRes, Master_3d.StaticTimeProc, (int)&Master_3d, TIME_PERIODIC);
	currinst=NULL;
	int mv=0;
	ticknum=0;
}

void Mast3d::Init(HINSTANCE			Hinst,HWND				Hwind)
{

	winst=Hwind;
	hinst=Hinst;
	MainInit();
	if (FAILED(DirectInputCreate(hinst, DIRECTINPUT_VERSION, &g_lpDI, NULL)))
		_Error.EmitSysErr("Can't access DirectInput!");
			;;;;;//ERROR 

}

void	Mast3d::BigWin()
{
	_DirectDraw::lpDirectDD->SetSmackerMode(false,Master_3d.winst);
	AfxGetMainWnd()->ModifyStyle(WS_THICKFRAME,NULL); // Bye bye border!
//	SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,FALSE,NULL,NULL);
	AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
}
void	Mast3d::SmallWin()
{
	_DirectDraw::lpDirectDD->SetSmackerMode(true,Master_3d.winst);
	AfxGetMainWnd()->ModifyStyle(WS_THICKFRAME,NULL); // Bye bye border!
//	SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,FALSE,NULL,NULL);
	AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
}

void	Mast3d::MainInit(void)
{
	FILEMAN.InitFileSystem(); // moved to a place where it will happen sooner (Mainfrm.cpp) DBM

	Image_Map.InitImageMaps();									//DAW 27Oct98

	_DPlay.Implemented = FALSE;

 	_Miles.Init((ULong)winst);											//RJS 02Nov98
	Display* Whole_Screen;
//	if (DDrawInitialised==FALSE)
//	{
//		_Main.DDrawInitialised = TRUE;

		_DirectDraw::lpDirectDD=new DirectDD;
//		_DirectDraw::lpDirectDD->SetSmackerMode(true,Master_3d.winst);
//		_DirectDraw::lpDirectDD->SetSmackerMode(false,Master_3d.winst);
		///_Analogue.Test();

//		if((Whole_Screen = new Display) == NULL)
//			_Error.EmitSysErr(__FILE__":Failed to create screen record\n");
//		Whole_Screen->InitDirectDraw ();
//		delete Whole_Screen;

//		Whole_Screen->DD.hWnd = hwind;
 //		if(	Whole_Screen->Init(NULL) == FALSE)	
  //			_Error.EmitSysErr(__FILE__":Failed to initialise screen record\n");
//	}
}
	
//////////////////////////////////////////////////////////////////////
Mast3d::~Mast3d()
{
	Inst3d*	ilist=currinst;
	while (ilist)
	{
		currinst=ilist->nextinst;
		delete ilist;
		ilist=currinst;
	}
	if (uTimerID)
		timeKillEvent(uTimerID); 
	uTimerID=0;
	if (wTimerRes)
		timeEndPeriod (wTimerRes);
	wTimerRes=0;
	if (Master_3d.g_lpDI)
	{
		Master_3d.g_lpDI->Release();
		Master_3d.g_lpDI=NULL;
	}
	delete _DirectDraw::lpDirectDD;


}
//MakeInteractive
void	Mast3d::Stop()
{
	if (uTimerID)
		timeKillEvent(uTimerID); 
	uTimerID=0;
}

///////////////////////////////////////////////////////////////////////
Inst3d::Inst3d(bool flag)
{
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[0]='i';
	Log_Stack.Log(LogStack::MESSAGELOOP);
//DEADCODE DAW 9/22/99 This increases main thread priority. That is not our problem, it seems.
//DEADCODE DAW 9/22/99 	CWinThread* mainthread=AfxGetThread();
//DEADCODE DAW 9/22/99 	mainthread->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
	
//DeadCode AMM 13Jan00 	movethread=AfxBeginThread(moveloop,this,THREAD_PRIORITY_ABOVE_NORMAL,50000,CREATE_SUSPENDED); 
// set up semaphore and mutex objects

	ULong maxcount;

	if (_DPlay.Implemented)
		maxcount=1000;
	else
		maxcount=200;

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='s';
	semaphore=CreateSemaphore(
		NULL,		// security attribs are default
		0,			// initial count
		maxcount,	// max count
		NULL		// name 
		);			

	if (!semaphore)
		_Error.EmitSysErr("Semaphore creation failed");


//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='m';
	mutex=CreateMutex(
		NULL,		// security attribs are default
		FALSE,		// owner?
		NULL		// name 
		);

	if (!mutex)
		_Error.EmitSysErr("Mutex creation failed");

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='t';
	movethread=AfxBeginThread(moveloop,this,THREAD_PRIORITY_ABOVE_NORMAL,50000,0); 
	mapview=flag;
	mono3d=false;
//DEADCODE JIM 29/03/99 	FILEMAN.flushcachedfiles();
 	paused=TRUE;
	accel=FALSE;
	interactive=FALSE;
	nextinst=Master_3d.currinst;
	Master_3d.currinst=this;	  //at this point the thread starts receiving timer messages.

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='k';
	commonkeymaps=(KeyMap3d*) Key_Tests.reftable3d.flat;
	world=new WorldStuff;
	(&world)->SetViewpoint(NULL);
//DEADCODE DAW 17/02/00 	blocktick=blockticks=TRUE;	//no movecodes
	viewedwin=NULL;
	livelist=NULL;
	Manual_Pilot.ControlledAC2=NULL;
	GR_Quit3DNow=0;
	GR_OkToQuit3DNow=0;
//DEADCODE DAW 28/03/99 	Timer_Code.Quit3DTimer=500;

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='r';
	_Replay.DeleteReplayLog(); // want new log every time we enter non-playback 3D//AMM 07Oct98
	_Replay.SuperHeaderStored=false;
	_Miles.ResetSoundFlags();
	Three_Dee.InitialiseCache();
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='l';
	Land_Scape.Init();
	Three_Dee.current_world=&world;
	//Load in the shape files requested by the battle field file loads
	SHAPESTUFF.LoadRequiredShapes();
	Three_Dee.livelist=livelist;
	_Collide.tdalt=TRUE;
//DEADCODE DAW 28/03/99 	Timer_Code.accel=FALSE;
	Trans_Obj.View_Point=NULL;
	Key_Tests.Reg3dConv(FIL_3D_KEYBOARD_TABLE);
	timeofday=11*60*60*100;
	OverLay.SetToMapViewScreen();
	Dead_Stream.GetWorldDead(&world);				//RDH 02Oct96	  //JIM 03/06/99

//do this as very last thing!!!
	Log_Stack.UnLog(LogStack::MESSAGELOOP);
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='=';

}

Inst3d::Inst3d()
{
	Log_Stack.Log(LogStack::MESSAGELOOP);
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[0]='I';
// set up semaphore and mutex objects

	ULong maxcount;

	if (_DPlay.Implemented)
		maxcount=1000;
	else
		maxcount=200;

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='S';
	semaphore=CreateSemaphore(
		NULL,		// security attribs are default
		0,			// initial count
		maxcount,	// max count
		NULL		// name 
		);			

	if (!semaphore)
		_Error.EmitSysErr("Semaphore creation failed");


//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='M';
	mutex=CreateMutex(
		NULL,		// security attribs are default
		FALSE,		// owner?
		NULL		// name 
		);

	if (!mutex)
		_Error.EmitSysErr("Mutex creation failed");

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='P';
	int oldprec=GETPREC();
	SETPREC(3);

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='T';
	CWinThread* mainthread=AfxGetThread();
	mainthread->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);

//DeadCode AMM 13Jan00 	movethread=AfxBeginThread(moveloop,this,THREAD_PRIORITY_ABOVE_NORMAL,50000,CREATE_SUSPENDED); 
	movethread=AfxBeginThread(moveloop,this,THREAD_PRIORITY_ABOVE_NORMAL,50000,0); 

	mapview=false;
	if (_Replay.Playback && !Save_Data.gamedifficulty[GD_GUNCAMERACOLOUR])
		mono3d=true;
	else
		mono3d=false;

 	paused=TRUE;
	accel=FALSE;
	interactive=FALSE;
	nextinst=Master_3d.currinst;
	Master_3d.currinst=this;

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='K';
	commonkeymaps=(KeyMap3d*) Key_Tests.reftable3d.flat;

	world=new WorldStuff;
//DEADCODE DAW 17/02/00 	blocktick=blockticks=0;
	viewedwin=NULL;
	_Replay.inst=this;											//AMM 11May99
	livelist=NULL;
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='B';
	Persons3	Persons_2(world,NULL,this);


	Manual_Pilot.ControlledAC2 = NULL;							//RDH 24Oct96
	GR_Quit3DNow=0;
	GR_OkToQuit3DNow=0;

	_Replay.DeleteFileAndGlobRefList(_Replay.bfgrlist);	//need to reset bfields if new mission

	if (!_Replay.Playback)
	{
		_Replay.badrecord=true;									//AMM 09Mar99
		_Replay.DeleteReplayLog(); // want new log every time we enter non-playback 3D//AMM 07Oct98
	}

	if (Save_Data.gamedifficulty[GD_GUNCAMERAATSTART] && !_DPlay.Implemented && !_Replay.Playback)			//AMM 05Jan99
	{
		_Replay.Record=TRUE;
	}
	_Replay.SuperHeaderStored=false;

	Art_Int.CleanUp();			//A/C recognition list

	timeofday = 11*60*60*100;										//PD 19Jan99

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='A';
	_Miles.ResetSoundFlags();									//DAW 01Sep98
	_Radio.SetUpRandomVoices();										//RJS 08Jun99
 	_Collide.tdalt = FALSE;
	Three_Dee.InitialiseCache();
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='L';
	Land_Scape.Init();
	Persons_2.LoadSetPiece(&world);//RDH 25Mar96
	Dead_Stream.GetWorldDead(&world);				//RDH 02Oct96

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='W';
	Manual_Pilot.SetWorldPtr(&world);							//PD 25Jun96
	_Collide.SetWorld(&world);								//PD 22Mar96
	MobileItem::SetWorld(&world);
	Three_Dee.current_world=&world;
	Trans_Obj.CleanUpTrailList();								//JIM 26Mar99



	//Load in the shape files requested by the battle field file loads
	SHAPESTUFF.LoadRequiredShapes();
 	//Set up animation data...
	(*world).SetLaunchers();										//RJS 21Aug96

	livelist= new LiveList(&world);
	Three_Dee.livelist=livelist;

	Three_Dee.livelist->BackupSleepList();

	//Back-up miles flags first
	SWord	oldsfxvol = Save_Data.vol.sfx;							  //RJS 07/07/99
	SWord	oldsfxmusic = Save_Data.vol.music;						   //RJS 07/07/99
	SWord	oldsfxchat = Save_Data.vol.rchat;						   //RJS 07/07/99
																	  //RJS 07/07/99
	Save_Data.vol.sfx = 0;											   //RJS 07/07/99
	Save_Data.vol.music = 0;										  //RJS 07/07/99
	Save_Data.vol.rchat = 0;										  //RJS 07/07/99
	Log_Stack.DontCheck(LogStack::MOVECODE);
	for (int i=0;i<Art_Int.ACARRAYSIZE*4;i++)	//CSB 06/07/99	
	{	//SFX are disabled here, so it is safe to send SFX messages.
		Art_Int.VisibleCheck();
	}
	Log_Stack.DontCheck();
	//Restore miles flags...
	Save_Data.vol.sfx = oldsfxvol;									  //RJS 07/07/99
	Save_Data.vol.music = oldsfxmusic;								  //RJS 07/07/99
	Save_Data.vol.rchat = oldsfxchat;								  //RJS 07/07/99

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='R';
	if (_Replay.Record)											//AMM 14Jun99
	{															//AMM 14Jun99
		_Replay.InitPosBuffer();								//AMM 14Jun99
		_Replay.StoreFinalRecordData();							//AMM 14Jun99
	}															//AMM 14Jun99
	else if (_Replay.Playback)									//AMM 14Jun99
	{															//AMM 14Jun99
		_Replay.LoadFinalPlaybackData();						//AMM 14Jun99
																//AMM 14Jun99
		if (!_Replay.Playback)									//AMM 14Jun99
			_Error.EmitSysErr("Error reading playback log");	//AMM 14Jun99
	}															//AMM 14Jun99
	else														//AMM 14Jun99
		_Replay.InitPosBuffer();								//AMM 14Jun99

	_Collide.tdalt = TRUE;										//PD 30Sep96

	_MsgBuffer.SetPlayer(Persons2::PlayerGhostAC,Persons2::PlayerSeenAC);			//RJS 27Jan99

	Trans_Obj.View_Point=Manual_Pilot.ControlledAC2;

	SendInit2Packet ();											//ARM 15Aug96

	Key_Tests.Reg3dConv(FIL_3D_KEYBOARD_TABLE);

	if (_Replay.RestorePosition)
	{
		_Replay.RestorePlaybackPosition();
	}



	SETPREC(oldprec);
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[2]='=';

	Log_Stack.UnLog(LogStack::MESSAGELOOP);
}
///////////////////////////////////////////////////////////////////////
Inst3d::~Inst3d()
{
	Log_Stack.Log(LogStack::MESSAGELOOP);
	_Miles.KillAll();

	//FIRST, remove all viewports:
	Paused(TRUE);
	CWinThread*	oldmovethread=movethread;
	movethread=0;
//DeadCode AMM 13Jan00 	oldmovethread->ResumeThread();
	{
		View3d* sptr=viewedwin;
		while (sptr)
		{
			sptr->SetEndDraw(View3d::D_CLOSE);
			sptr=sptr->nextview;
		}
		sptr=viewedwin;
		Interactive(NULL);
		viewedwin=NULL;
		while (sptr)
		{
			View3d* sp2=sptr;
			sptr=sptr->nextview;
			delete sp2;
		}
	}
	//Next, remove instance from list
	if (Master_3d.currinst)
	{
		Inst3d**	sptr=&Master_3d.currinst;
		while (*sptr!=this)
			sptr=&sptr[0]->nextinst;
		*sptr=nextinst;
	}

	//Next, start freeing resources:

	_DPlay.GameRunning=FALSE;

	if (!mapview)
	{
	Persons3 	Persons_3(world,NULL,this);
	if (!_Replay.Playback)
	{
		Art_Int.FakeMissionSuccess();
		Dead_Stream.SetWorldDead(world);				//RDH 02Oct96
		Dead_Stream.ScoreSGKills();
//	Persons_3.EndGameScoring();
#ifndef	MIG_DEMO_VER
		Persons_3.ProcessLogList();
#endif	MIG_DEMO_VER
	}
	Persons_3.FreeRoutes();
	Persons_3.FreeEvents();

//DEADCODE JIM 23/02/99 DON'T DO THIS!!!	Dead_Stream.ClrWorldDead();				//RDH 02Oct96

//	Timer_Code.PauseToggle(FALSE);
//	Timer_Code.AccelToggle(FALSE);
//DeadCode RDH 11Dec96 	Dead_Stream.SetWorldDead();
	// THIS LINE CAN CAUSE A CRASH									//ARM 06Mar97
//TempCode ARM 06Mar97 	AirStruc::EndGameScoring();									//RDH 11Dec96
//TEMP	if (!(MMC.specialeventbits[CAMPAIGNLOST]))					//RDH 11Dec96
//TEMP		Dead_Stream.SetWorldDead();								//RDH 11Dec96
//DeadCode JIM 06Oct96 	Persons_2.TankEndMission();
//	Whole_Screen->SetMouseImage(1);
	}
	else Persons4::ShutDownViewFromMap();

	delete	livelist;
	Three_Dee.livelist=NULL;
	SHAPESTUFF.UnLoadRequiredShapes();
	Three_Dee.Done3D();											//DAW 30Nov95
 	Image_Map.UnLoadImageMaps();								//RJS 14Jun99
	if (!mapview) (*world).ClearWorld();
	delete Persons2::PlayerGhostAC;
	Persons2::PlayerSeenAC=NULL;
	Persons2::PlayerGhostAC=NULL;

	_DPlay.DeleteClaimBuffer();									//AMM 12Mar99

	if (_Replay.Playback)
	{
// want to remove deadlist and restore from save game, otherwise it becomes garbage

		Dead_Stream.ClrWorldDead();								//AMM 29Mar99

		if (_Replay.MapPlayback)									  //AMM 25/06/99
			_Replay.RestoreSaveGame();
//DeadCode DAW 25Jun99 		_Replay.RestoreSaveGame();
		_Replay.ClosePlaybackLog();
		_Replay.RestorePrefs();
		RFullPanelDial::gamestate=(RFullPanelDial::GameStates)_Replay.PlaybackGameState;
//		_Replay.Playback=FALSE;
	}
	else
	{
//	if (_Replay.Record)
		_Replay.CloseRecordLog();
	}
	_Replay.inst=NULL;

//	_Replay.Record=FALSE;
//	_Replay.PlaybackPaused=FALSE;

//	Key_Tests.RegUIConv(INVALIDFILENUM);
//TEMP 	for (int i=0;i<MAX_VAPOURS;i++)	SHAPE.KillVapourStream(i);	//RJS 02Jun97

//TEMP	_Miles.StopAll();
//TEMP	_Miles.DiscardMusic();										//RJS 27Sep96
//TEMP	_Miles.FreeSamples();										//RJS 04Oct96
	_Miles.ResetSoundFlags();									//DAW 01Sep98
	if (!mapview) Art_Int.CleanUp();
	delete world;
	MobileItem::SetWorld(NULL);

	OverLay.pCurScr=OverLay.pNewScr=NULL;

//DEADCODE JIM 29/03/99 	FILEMAN.flushcachedfiles();

//	RDialog::m_pView->ModifyStyleEx(RDialog::m_pView->GetExStyle(),NULL); // Bye bye annoying border!
	AfxGetMainWnd()->ModifyStyle(WS_THICKFRAME,NULL); // Bye bye border!
#if defined(NDEBUG)
	AfxGetMainWnd()->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
#endif
//	SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,FALSE,NULL,NULL);
	AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);

// release semaphore and mutex handles
	if (semaphore==0 || mutex==0)
		_Error.EmitSysErr("Thread management resources null on release");
	CloseHandle(semaphore);
	CloseHandle(mutex);

	Log_Stack.UnLog(LogStack::MESSAGELOOP);
}
///////////////////////////////////////////////////////////////////////

bool	Inst3d::InThe3D()
{
	
	for (Inst3d*	t=Master_3d.currinst;t;t=t->nextinst)	
	{	 
		for (View3d*	v=t->viewedwin;v;v=v->nextview)
			if (v->drawing)	// &&  v->mode!=NONE)
				return TRUE;
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseDirectX
//Author		Paul.   
//Date			Mon 25 Jan 1999
//------------------------------------------------------------------------------
void Inst3d::ReleaseDirectX()
{
	//remove all viewports...
	for (Inst3d* t=Master_3d.currinst;t;t=t->nextinst)
	{
		t->Paused(TRUE);
		View3d *v=t->viewedwin;
		while (v)
		{
			v->WaitEndDraw(View3d::D_CLOSE);
			v->MakeResize(WinMode::NONE);
			v->CloseWindow(IDCANCEL);
			v=v->nextview;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestoreDirectX
//Author		Paul.   
//Date			Mon 25 Jan 1999
//------------------------------------------------------------------------------
void Inst3d::RestoreDirectX()
{
}

///////////////////////////////////////////////////////////////////////
View3d::View3d(Inst3d* ofinst,HWND newwin,CWnd* d):
	coords(0,0,0,0),E(NULL)

{
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[4]='V';
	Log_Stack.Log(LogStack::MESSAGELOOP);
//DeadCode RJS 18May98 	_Miles.Init((ULong)newwin);									//RJS 03Apr98
	mfcwin=d;
	window=newwin;
	inst=ofinst;
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[6]='i';
	if (ofinst->Interactive())
	{
		nextview=ofinst->Interactive()->nextview;
		ofinst->Interactive()->nextview=this;
	}
	else
	{
		nextview=ofinst->viewedwin;
		ofinst->viewedwin=this;
	}
 	lastrealframetime=5;			//should be in for photo rotation //DAW 19/6/99
	View_Point=NULL;
	Whole_Screen=NULL;
	mode=WinMode::NONE;
	drawing=D_NO;

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[6]='d';
	_Miles.SetDelayed(false);

//DeadCode AMM 13Jan00 	AfxBeginThread( drawloop, this, THREAD_PRIORITY_NORMAL, 50000);
	AfxBeginThread( drawloop, this, THREAD_PRIORITY_NORMAL, 0);
	//THREAD_PRIORITY_ABOVE_NORMAL	    //AFX_THREADPROC

//	oldmessagelines=Save_Data.messagelines;
//	currmessagelines=Save_Data.messagelines;
//	msgtimer =0;												//RDH 24Oct96
//	viewmsgtimer =0;

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[6]='l';
  	Image_Map.LoadImageMapPtrs();								//PD 29Nov95
	doneframe=TRUE;
	Log_Stack.UnLog(LogStack::MESSAGELOOP);
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[6]='=';
}
///////////////////////////////////////////////////////////////////////
View3d::~View3d()
{

	Three_Dee.ClearCurrentDisplay();
	Log_Stack.Log(LogStack::MESSAGELOOP);
	_Miles.DisableAll();

	Interactive(false);
	//free thread

	if (drawing!=D_NO)
	{
		WaitEndDraw(D_CLOSE);
	}
	if (mode!=WinMode::NONE)
	{	//screen is allocated - free resources
	}
	View3d**	sptr=&inst->viewedwin;
	while (*sptr!=this)
		sptr=&sptr[0]->nextview;
	*sptr=nextview;


//	if (View_Point)
//		View_Point->deathview = FALSE;								//RJS 01Nov96
//	ScreenRez	srez;
//	srez.width = 640;
//	srez.colourdepth = 8;
//	srez.driver =-1;
//
//	if (	(Save_Data.screenresolution != srez.width
//		&&	Save_Data.screenresolution != -srez.width)
//		||	Save_Data.colourdepth != srez.colourdepth
//		||	Save_Data.dddriver != srez.driver)
//		{
//			Whole_Screen->ChangeRes(srez);
//			LandStream.RezChanged(srez);						//PD 06Jun97
//		}
//
	MakeResize(WinMode::NONE);

	_Miles.InitUI((int)window);									//DAW 06Apr99
	Log_Stack.UnLog(LogStack::MESSAGELOOP);
}
void	View3d::CloseWindow(const ULong id)
{
	if (mfcwin)
//		mfcwin->PostMessage(WM_COMMAND,IDOK,NULL);
		mfcwin->PostMessage(WM_COMMAND,id,NULL);
}
///////////////////////////////////////////////////////////////////////
int	View3d::MakeInteractive(WinMode	v,const CRect& pos,bool flag,bool flag2)
{
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[12]='I';

	Log_Stack.Log(LogStack::MESSAGELOOP);

	ASSERT(mode==WinMode::NONE);
	if (!MakePassive(v,pos,flag,flag2))
		return (0);
	Interactive(true);
	return 1;
}
///////////////////////////////////////////////////////////////////////
int	View3d::MakePassive(WinMode	v,const CRect& pos,bool flag,bool flag2)
{
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='@';
	Log_Stack.Log(LogStack::MESSAGELOOP);
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[8]='P';

	ASSERT(mode==WinMode::NONE);
	Interactive(false);
	if (&pos)
		coords=pos;
	else
	{

	}
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[10]='p';
	HDC	dcTmp = GetDC(window);
	SetSystemPaletteUse(dcTmp,SYSPAL_NOSTATIC);		 //SYSPAL_ERROR
	ReleaseDC(window,dcTmp);

	//make sure loaderart is cached
	fileblockptr fbp=new fileblock(FIL_LOADERART);
	delete fbp;

	//handle resolution change
	delete _DirectDraw::lpDirectDD;
	_DirectDraw::lpDirectDD=new DirectDD;
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='A';
	Whole_Screen=new Display(this);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='B';
	Whole_Screen->DD.hWnd = window;
	Whole_Screen->DD.hWndApp = Master_3d.winst;
	_Miles.SetDirectSoundWindow((ULong)Master_3d.winst);

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[10]='d';
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='C';
	Whole_Screen->InitDirectDraw ();
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='D';
	Whole_Screen->Init(v,coords.left,coords.top,coords.right,coords.bottom);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='E';
	
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[10]='v';
	View_Point=new ViewPoint(Whole_Screen,this);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='F';

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[10]='o';
	OverLay.SetScreen(Whole_Screen);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='G';

	OverLay.SetViewpoint(View_Point);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='H';

	OverLay.LoaderScreen(0);									//PD 02Mar99
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='I';

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[10]='m';
	_Miles.Init3D();											//RJS 06Apr99
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='J';

	_Miles.SetDirectSoundWindow((ULong)Master_3d.winst);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='K';

//	_Miles.SetVolumes(TRUE);									//RJS 12Mar99
	OverLay.LoaderScreen(0+32);									//PD 02Mar99
//DEADCODE DAW 13/04/99 	_Miles.SetVolumes(TRUE);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='L';

	if (!flag)
	{
		_Miles.SetVolumes(TRUE);								//RJS 13Apr99
		View_Point->SetToPiloted(Manual_Pilot.ControlledAC2);
		View_Point->SetReplayView(_Replay.Playback);//RJS 20Oct98
	}
	else View_Point->SetToMapItem(NULL);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='M';

	OverLay.LoaderScreen(0+48);									//PD 02Mar99
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='N';
	Trans_Obj.View_Point=View_Point;
	Trans_Obj.View_Object=View_Point;							//RJS 21Apr98
	Land_Scape.View_Point=View_Point;
	Land_Scape.currscreen=Whole_Screen;
	OverLay.LoaderScreen(0+64);									//PD 02Mar99
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='O';

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[10]='3';
	Three_Dee.Init3D(Whole_Screen,View_Point);					//RJS 19Nov98
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='P';

	if (flag2) 
		Land_Scape.RefreshLandscape();
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='Q';

	Three_Dee.ResetPalette();									//RJS 24Oct96
	doneframe=TRUE;		//forces frametime to zero
	Drawing(true);
	mode=v;
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='R';

	if (_DPlay.Implemented)										//DAW 22Jun99
	{															//DAW 22Jun99
		_DPlay.csync=true;										//DAW 22Jun99
	}															//DAW 22Jun99
	WaitEndDraw(D_YES);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='S';

	WaitEndDraw(D_YES);
//DEADCODE JIM 20/07/99 	UByteP(0xB0000)[0]='T';

	if (_DPlay.Implemented)										//DAW 22Jun99
	{															//DAW 22Jun99
		_DPlay.csync=false;										//DAW 22Jun99
	}															//DAW 22Jun99
	_Replay.skipOK=true;
//DeadCode AMM 19Apr99 #ifndef NDEBUG
//DeadCode AMM 19Apr99 	if (_DPlay.Implemented)
//DeadCode AMM 19Apr99 		Paused(FALSE);
//DeadCode AMM 19Apr99 #endif
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[10]='=';
	return 1;
}
///////////////////////////////////////////////////////////////////////
int	View3d::MakeResize(WinMode	v,const CRect& pos)
{
	Log_Stack.Log(LogStack::MESSAGELOOP);
	if ((&pos && pos!=coords) || v!=mode)
	{
		//delete old surface...
		if (&pos)
			coords=pos;

		//some legality check before we start screwing things up 10 ways

		if (v!=mode)
		{	//delete windowing object
			v=WinMode::NONE;
			//WaitEndDraw(D_CLOSE);
			drawing=D_CLOSE;
//DEAD			POLYGON.DeleteYList();
//CRASHED CRAIGS M/C
				delete Whole_Screen;
				Whole_Screen=NULL;
			Trans_Obj.View_Point=Manual_Pilot.ControlledAC2;
			delete View_Point;
			View_Point=NULL;
			HDC	dcTmp = GetDC(window);
			SetSystemPaletteUse(dcTmp,SYSPAL_STATIC);
			ReleaseDC(window,dcTmp);
		}
		//make or convert to new diasplay 


		v=mode;
	}
	//else no change
	Log_Stack.UnLog(LogStack::MESSAGELOOP);

	return 1;
}
///////////////////////////////////////////////////////////////////////
View3d* Inst3d::Interactive(View3d* newwin)
{
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[16]='I';
	Log_Stack.Log(LogStack::MESSAGELOOP);
	TRACE("Interactive entry\n");
	View3d* rv=interactive?viewedwin:NULL;
	interactive=(newwin!=NULL);
	if (newwin)	
	{
		View3d** vw=&viewedwin;
		while (*vw!=newwin)
			vw=&vw[0]->nextview;
		*vw=newwin->nextview;				//unhooks newwin
		newwin->nextview=viewedwin;
		viewedwin=newwin;				//reinserts at front
	}
	if (newwin!=rv)
		if (newwin)
		{
			_Analogue.Initialise((int)Master_3d.winst,(int)Master_3d.hinst);
			TRACE("Interactive setup success1\n");
			if (Master_3d.g_lpDI)
			if (!Master_3d.g_lpDIDevice)
			{
//			TRACE("Interactive setup success2\n");
				if (!FAILED(Master_3d.g_lpDI->CreateDevice(GUID_SysKeyboard, &Master_3d.g_lpDIDevice, NULL)))
				{
//			TRACE("Interactive setup success3\n");

					if (!FAILED(Master_3d.g_lpDIDevice->SetDataFormat(&c_dfDIKeyboard)))
						if (!FAILED(Master_3d.g_lpDIDevice->SetCooperativeLevel(Master_3d.winst,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
						{	//E_INVALIDARG	//DIERR_NOTINITIALIZED
//			TRACE("Interactive setup success4\n");
							DIPROPDWORD	buffsize={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},BUFFERED_KEYS};
							DIDEVCAPS DIDevCaps={sizeof(DIDEVCAPS)};
							Master_3d.g_lpDIDevice->GetCapabilities(&DIDevCaps); 
							//DIDC_ATTACHED   DIERR_INVALIDPARAM 
							Master_3d.g_lpDIDevice->SetProperty(DIPROP_BUFFERSIZE,&buffsize.diph);
							if (!FAILED(Master_3d.g_lpDIDevice->SetEventNotification(Master_3d.htable[Master_3d.EVENT_KEYS])))
							{

//			TRACE("Interactive setup success5\n");


								if (!FAILED(Master_3d.g_lpDIDevice->Acquire()))
								{
									TRACE("Interactive setup success\n");
//									*(char*)0xb0000='1';
									return	rv;
								}
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[18]='k';
							}
						}
					Master_3d.g_lpDIDevice->Release();
					Master_3d.g_lpDIDevice=NULL;
				}
				TRACE("Interactive setup fail\n");
				_Error.EmitSysErr("Couldn't access keyboard with directinput?");
				//syserr??
			}
		}
		else
		{
			_Analogue.CloseDown();
			if (Master_3d.g_lpDIDevice)
			{
//				TRACE("Interactive removal\n");

				Master_3d.g_lpDIDevice->Unacquire();
				Master_3d.g_lpDIDevice->SetEventNotification(NULL);
				Master_3d.g_lpDIDevice->Release();
				Master_3d.g_lpDIDevice=NULL;
//				*(char*)0xb0000='0';
									
//				TRACE("Interactive removal exit\n");
			}
		}	 
	Log_Stack.UnLog(LogStack::MESSAGELOOP);
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[18]='=';
	return rv;
}
///////////////////////////////////////////////////////////////////////
bool Inst3d::Paused(bool newmode)
{
	bool rv=paused;
	paused=newmode;
	if (newmode!=rv)
		if (newmode)
		{
			_Miles.StopAll();				//RJS 07Jun99
			_Miles.SequenceMute(500);		//RJS 07Jun99
			_Miles.SetEngine();				//RJS 07Jun99
			accel=false;
		}
		else
		{
		}
	return rv;
}
///////////////////////////////////////////////////////////////////////
bool Inst3d::Accel(bool newmode)
{
	bool rv=accel;
	accel=newmode;
	if (newmode!=rv)
		if (newmode)
		{
			if (_Replay.Record)									//AMM 26May99
			{													//AMM 26May99
				if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER]
				&& !Save_Data.gamedifficulty[GD_GUNCAMERAATSTART])
				{
					_Replay.guncameradelay=0;
//DeadCode AMM 08Jul99 					_Replay.clearreplaybuffers=true;
					_Replay.stopforaccel=false;
				}
				else
				{
					_Replay.stopforaccel=true;						//AMM 26May99
				}
				_Replay.StopRecord();							//AMM 26May99
			}													//AMM 26May99

			_Miles.StopAll();				//RJS 11May99
			_Miles.SequenceMute(500);		//RJS 11May99
			_Miles.SetEngine();									//RJS 01Jun99
			paused=false;
		}
		else
		{
			_Radio.ClearMessages(MSG_TAKEOFFROLLING);			//RJS 14Jun99
			_Radio.ClearMessages(PRI_LOW);						//RJS 03Jun99
			mobileitem::ResetACGears();							//RJS 01Jun99
//DeadCode AMM 10Jun99 			_DPlay.SendAccelDeselectedMessage();				//AMM 26May99

			if (_Replay.stopforaccel)							//AMM 26May99
			{													//AMM 26May99
				_Replay.stopforaccel=false;						//AMM 26May99
				_Replay.StartRecordFlag=TRUE;					//AMM 26May99
				_Replay.DelayedGearUp=true;
			}													//AMM 26May99
		}

	Persons2::PlayerSeenAC->fly.pModel->Blood = 1;
	return rv;
}
///////////////////////////////////////////////////////////////////////
View3d* Inst3d::Interactive()
{
	return interactive?viewedwin:NULL;
}
///////////////////////////////////////////////////////////////////////
bool Inst3d::Paused()
{
	if (this==NULL)
		return	false;
	return paused;
}
///////////////////////////////////////////////////////////////////////
bool Inst3d::Accel()
{
	return accel;
}
///////////////////////////////////////////////////////////////////////
bool	View3d::Drawing(bool newval)
{
	bool rv=(drawing==D_YES);
	if (drawing<=D_YES)
	{
		drawing=newval?D_YES:D_NO;
		if (newval)
		{
		}
		else
		{
		}
	}
	return rv;
}
///////////////////////////////////////////////////////////////////////
void Inst3d::OnKeyInput()
{
	Log_Stack.Log(LogStack::MESSAGELOOP);
	if (!Master_3d.g_lpDIDevice)
		return;
	DIDEVICEOBJECTDATA	keys[BUFFERED_KEYS];
	DWORD	dwItems=BUFFERED_KEYS;
	int		rv= 
		IDirectInputDevice_GetDeviceData( 
			Master_3d.g_lpDIDevice,sizeof(DIDEVICEOBJECTDATA), 
			keys,&dwItems,0);
	if (!FAILED(rv))
		for(DIDEVICEOBJECTDATA*	key=keys;dwItems;dwItems--,key++)
		{
			int keynum=key->dwOfs;
//DAW 15/09/1999		Mono_Text.Print(keynum,UByteP("Key OK "));
			char keyval=key->dwData;
			if (keyval<0)
				OnKeyDown(keynum);
			else
				OnKeyUp(keynum);
		}						   
	Log_Stack.UnLog(LogStack::MESSAGELOOP);
}
void	Inst3d::OnKeyDown(int keynum)
{
	int	index=commonkeymaps->mappings[keynum][commonkeymaps->currshifts];
	if (index)
	{
		if (index<16)
		{	//it's a shift key!
			commonkeymaps->currshifts=index>>1;
		}
		else
		{
			if (!BITSET(commonkeymaps->bitflags,index+1))
				BITSET(commonkeymaps->bitflags,index);
		}
	}
}
void	Inst3d::OnKeyUp(int keynum)
{	//release	
	UWord*	indtable=commonkeymaps->mappings[keynum];
	for (int ent=8;ent;ent--)
	{
		int index=*indtable++;
		if (index)
		{
			if (index<16)
			{	//it's a shift key!
				if (commonkeymaps->currshifts==(index>>1))
					commonkeymaps->currshifts=0;
			}
			else
			{
				BITRESET(commonkeymaps->bitflags,index);
			}
		}
	}
}

UINT AFX_CDECL View3d::drawloop(LPVOID THISTHIS)
{	//can get hwnd etcetera no problem!
	Log_Stack.Log(LogStack::THREEDEE,40000);
	View3d* This=(View3d*) THISTHIS;
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[160]='D';
	forever
	{
		if (This->drawing==D_YES)
		{
			//actual draw code here!
//			while (++(((char*)0xb0000)[160*10])&7)
//				for (((char*)0xb0000)[160*10+2]=0;++(((char*)0xb0000)[160*10+2]);)
//					for (((char*)0xb0000)[160*10+4]=0;++(((char*)0xb0000)[160*10+4]);)
//					{}
			if (This->mode!=WinMode::NONE)
			{
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[162]='d';
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[164]++;
				Window	window3d(*This->Whole_Screen,WINSH_MID,WINSH_MID);

//DeadCode RJS 27Aug98 				_Miles.SetVP(This->View_Point);					//RJS 26Feb98
//Dead 				_Miles.ProcessSpot(This->View_Point);			//RJS 25May99
//Dead				_Radio.ProcessMessages(This->View_Point->FrameTime());			//RJS 01Apr99
 
				static UWord doit=0;							//AMM 07Jul99
				static UWord stage=0;							//AMM 07Jul99

//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[162]='r';
				if (!_DPlay.Implemented || _DPlay.csync)		//DAW 22Jun99
					Three_Dee.render(&window3d,This->View_Point,This->inst->world);
//DeadCode AMM 08Jul99 				else if (doit&0x40)								//AMM 07Jul99
				else if (doit&0x1000)							//AMM 08Jul99
				{												//AMM 07Jul99
// dont want resyncing message at all, but keep waiting message
					if (!_DPlay.resyncbar)						//AMM 28Sep99
						OverLay.CommsWaitingScreen(stage++);		//AMM 07Jul99
				}												//AMM 07Jul99
				doit++;											//AMM 07Jul99
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[162]='b';
				This->BlockTick(TRUE);
				//Transients must always go last...
				if (!_DPlay.Implemented || _DPlay.csync)		//DAW 22Jun99
				{												//DAW 22Jun99
//TEMPCODE JIM 13.08.99 					_Miles.ProcessSpot(This->View_Point);							//RJS 25May99
//TEMPCODE JIM 13.08.99 					_Radio.ProcessMessages(This->View_Point->FrameTime());			//RJS 25May99
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[162]='r';
					SHAPE.GenerateProbeTrails();								//RJS 08Apr99
					SHAPE.KillVapourStreamDeadList();							//RJS 08Apr99
					Trans_Obj.RemoveDeadListFromWorld(This->inst->world);

					if (_Replay.Playback && _Replay.processsmokes)
						_Replay.UpdateSmokeInfo();
				}												//DAW 22Jun99
				else
				{
					if (_DPlay.Implemented && !_DPlay.csync)
					{
						if (_DPlay.CommsGameSync())
							This->Paused(FALSE);
					}
				}

				This->BlockTick(FALSE);
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[162]='s';

// to stop screen strobe in comms sync phase!
				if (!_DPlay.Implemented || _DPlay.csync)		//AMM 09Jun99
					This->Whole_Screen->ScreenSwap();

				if (Key_Tests.KeyPress3d(SCREENSHOT)){
					if (!videoBuffer) This->Whole_Screen->ScreenShot();
					else
					{
						This->Whole_Screen->DoSaveVideoBuffer();
//DEADCODE JIM 29/03/99 						FILEMAN.flushcachedfiles();
					}
				}
				Three_Dee.ClearCurrentScreen();
			}
//DeadCode AMM 01Apr99 			if (_Replay.ReadBlock)
//DeadCode AMM 01Apr99 			{
//DeadCode AMM 01Apr99 				if (!_Replay.LoadBlockHeader())
//DeadCode AMM 01Apr99 					_Replay.PlaybackPaused=TRUE;
//DeadCode AMM 01Apr99 				_Replay.ReadBlock=false;
//DeadCode AMM 01Apr99 			}
		}
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[162]='e';
		if (This->E)
			This->E->SetEvent();
		if (This->drawing==D_CLOSE)
			return 0;
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[162]='f';
		This->DoneFrame();

//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[162]='o';
		if ((Manual_Pilot.ControlledAC2==NULL || !Manual_Pilot.ControlledAC2->Status.deadtime)
			&& !This->Accel() && OverLay.pCurScr==NULL && Key_Tests.KeyPress3d(KEY_CONFIGMENU))
		{
//DeadCode AMM 14Apr99 			if (_DPlay.Implemented || _Replay.Playback)
//DeadCode AMM 14Apr99 				return 0;

			if (!(_DPlay.Implemented || _Replay.Playback))		//AMM 14Apr99
			{													//AMM 14Apr99
// need to store state of record so that when we come back to 3d, I know
// where to start recording from again

//DeadCode AMM 29Mar99 			if (_Replay.Record)
//DeadCode AMM 29Mar99 				_Replay.PrefsInterrupt=RS_RECORDING;
//DeadCode AMM 29Mar99 			else if (_Replay.SuperHeaderStored)
//DeadCode AMM 29Mar99 				_Replay.PrefsInterrupt=RS_HAVERECORDED;
//DeadCode AMM 29Mar99 			else
//DeadCode AMM 29Mar99 				_Replay.PrefsInterrupt=RS_NOTRECORDED; 

//DeadCode AMM 29Mar99 			_DPlay.ExitCommsAndReplay3D();						//AMM 24Feb99

				_Replay.prefscheck=true;

				This->inst->Paused(TRUE); //AMM 21/05/99
				This->MakeResize(WinMode::NONE);
				This->CloseWindow(IDCANCEL);
			}													//AMM 14Apr99
		}
		else if ((Manual_Pilot.ControlledAC2!=NULL && 
				((!_Replay.Playback && Key_Tests.KeyPress3d(EXITKEY)) || 
				_DPlay.SimulateExitKey)) || OverLay.quit3d)
		{
			OverLay.quit3d=0;
//			if (!_DPlay.SimulateExitKey && _DPlay.Implemented)
//DeadCode AMM 11Dec98 			if (_DPlay.Implemented)
//DeadCode AMM 11Dec98 			{
//DeadCode AMM 11Dec98 // real exit
//DeadCode AMM 11Dec98 				_DPlay.SendGonePacket();
//DeadCode AMM 11Dec98 				_DPlay.ResetCommsGame();
//DeadCode AMM 11Dec98 			}
//DeadCode AMM 11Dec98 			else if (_Replay.Record)
//DeadCode AMM 11Dec98 			{
//DeadCode AMM 11Dec98 				_Replay.StopRecord();
//DeadCode AMM 11Dec98 			}

//			if (_Replay.ReplayFlag==RF_SAVEBLOCK)
//			{
//				_Replay.BackupPlaybackPosition();
//				_DPlay.ExitCommsAndReplay3D();
//			}
//			else
			{
				This->inst->Paused(TRUE); //AMM 21/05/99
				_DPlay.ExitCommsAndReplay3D();						//AMM 11Dec98
			}

			This->MakeResize(WinMode::NONE);
			This->CloseWindow();
		}

//DeadCode AMM 16Apr99 		if (Key_Tests.KeyPress3d(SUICIDE))
//DeadCode AMM 16Apr99 		{
//DeadCode AMM 16Apr99 //			if (!_DPlay.ResyncPhase)
//DeadCode AMM 16Apr99 //			{
//DeadCode AMM 16Apr99 //				_DPlay.Initiator=TRUE;
//DeadCode AMM 16Apr99 //				_DPlay.BeginSyncPhase();
//DeadCode AMM 16Apr99 //			}
//DeadCode AMM 16Apr99 //			if (_DPlay.Implemented)
//DeadCode AMM 16Apr99 //				_DPlay.CommitSuicide();
//DeadCode AMM 16Apr99 //			_DPlay.ToggleAC();
//DeadCode AMM 16Apr99 			_DPlay.ForceAIACPosResync();
//DeadCode AMM 16Apr99 		}
//DEADCODE RDH 16/04/99  		if (Key_Tests.KeyPress3d(MAGICK1))
//DEADCODE RDH 16/04/99 		{
//DEADCODE RDH 16/04/99 //			_DPlay.DisplayResyncingMessage();
//DEADCODE RDH 16/04/99 			_DPlay.dodgytime=true;
//DEADCODE RDH 16/04/99 		}
//DEADCODE RDH 16/04/99 		if (Key_Tests.KeyPress3d(MAGICK2))
//DEADCODE RDH 16/04/99 		{
//DEADCODE RDH 16/04/99 			if (!_DPlay.ResyncPhase)
//DEADCODE RDH 16/04/99 			{
//DEADCODE RDH 16/04/99 				_DPlay.Initiator=TRUE;
//DEADCODE RDH 16/04/99 				_DPlay.BeginSyncPhase();
//DEADCODE RDH 16/04/99 			}
//DEADCODE RDH 16/04/99 		}
//DeadCode AMM 16Apr99 		if (Key_Tests.KeyPress3d(RECORDTOGGLE))
//DeadCode AMM 16Apr99 		{
//DeadCode AMM 16Apr99 			_Replay.ToggleRecord();
//DeadCode AMM 16Apr99 		}
//DeadCode AMM 16Apr99 		if (Key_Tests.KeyPress3d(RESETRECORD))
//DeadCode AMM 16Apr99 		{
//DeadCode AMM 16Apr99 			_Replay.ResetRecord();
//DeadCode AMM 16Apr99 		}
	}
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[162]='=';
	Log_Stack.UnLog(LogStack::THREEDEE);
	return 0;
}

void	View3d::SetEndDraw(DrawState d)
{
	if (drawing==D_YES)
		if (!E)
			E=new CEvent();
	drawing=d;	
}
int	View3d::WaitEndDraw(DrawState d,int timeoutmilisec)
{
	if (drawing==D_YES)
		if (!E)
			E=new CEvent();
	drawing=d;	
	if (E)
		if (!E->Lock(timeoutmilisec))
			return false;
	CEvent* t=E;
	E=NULL;
	delete t;
	return true;
}

void	Mast3d::QuitGame(void )
{
//TEMP	_DPlay.ExitDirectPlay();
//TEMP
//TEMP	if (_Main.DDrawInitialised==TRUE)
//TEMP	{
//TEMP		_Main.DDrawInitialised=FALSE;
//TEMP
//TEMP		Whole_Screen->ExitDirectDraw ();	// put in Display::Exit
//TEMP
//TEMP		Whole_Screen->SetTextMode();
//TEMP	}
//TEMP
//TEMP	delete	Whole_Screen;
//TEMP
//TEMP	Whole_Screen=NULL;
//TEMP
//TEMP	if (debugfile!=NULL) fclose (debugfile);
//TEMP
}

//DEADCODE DAW 17/02/00 static int	howcamehere;
void CALLBACK Mast3d::StaticTimeProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2 )
{
	Log_Stack.Log(LogStack::INTERRUPT,0);
	ULong t=0;
	if (_DPlay.Implemented)
	{
		if (_DPlay.Host && _DPlay.GameRunning)
		{
			if (!_DPlay.ResyncPhase && !_DPlay.ServedGame)
			{
//				TRACE0("want timer lock\n");
//DeadCode AMM 15Apr99 				while (LockExchange(&Aggregator::inaggregator,1)) 
//DeadCode AMM 15Apr99 				{
//DeadCode AMM 15Apr99 					Sleep(0);
//DeadCode AMM 15Apr99 					if (t++>1000000)
//DeadCode AMM 15Apr99 						_Error.SayAndQuit("timercall exceeds 1000000");
//DeadCode AMM 15Apr99 				};
//				TRACE0("got lock for timer\n");
				_Agg.AggregatorGetPackets(FALSE,TRUE);
//DeadCode AMM 15Apr99 				LockExchange(&Aggregator::inaggregator,0);
//				TRACE0("released lock for timer\n");
			}
		}
	}

//DeadCode AMM 16Apr99 	if (_DPlay.Implemented && !_DPlay.csync)
//DeadCode AMM 16Apr99 	{
//DeadCode AMM 16Apr99 		_DPlay.CommsGameSync();
//DeadCode AMM 16Apr99 	}
//DeadCode AMM 16Apr99 	else
//DeadCode AMM 16Apr99 	{
		if (!_DPlay.Implemented || (_DPlay.Implemented && _DPlay.csync))//AMM 19Apr99
			((Mast3d*)dwUser)->TimeProc(uID,uMsg,dw1,dw2);
//DeadCode AMM 16Apr99 	}
	Log_Stack.UnLog(LogStack::INTERRUPT);
	if (!Rtestsh1::tempblockkeys)
		Inst3d::OnKeyInput();

}

void Mast3d::TimeProc(UINT uID, UINT uMsg, DWORD dw1, DWORD dw2 )
{
//DeadCode DAW 14Jan00 	static ULong ltim=0;
//DeadCode DAW 14Jan00 	LARGE_INTEGER count;
//DeadCode DAW 14Jan00 	ULong freq;
//DeadCode DAW 14Jan00 
//DeadCode DAW 14Jan00  	if(_DPlay.Implemented && _DPlay.csync)
//DeadCode DAW 14Jan00  	{
//DeadCode DAW 14Jan00  		QueryPerformanceFrequency((LARGE_INTEGER*)(&freq));
//DeadCode DAW 14Jan00  		QueryPerformanceCounter(&count);
//DeadCode DAW 14Jan00  
//DeadCode DAW 14Jan00  		ULong smlcount=count.LowPart;
//DeadCode DAW 14Jan00  		ULong Rtime=((smlcount-ltim)*1000)/freq;
//DeadCode DAW 14Jan00  
//DeadCode DAW 14Jan00  		FILE* fp=fopen("toptim.txt","at");
//DeadCode DAW 14Jan00  		fprintf(fp,"%d %d\n",_DPlay.FrameCount,Rtime);
//DeadCode DAW 14Jan00  		fclose(fp);
//DeadCode DAW 14Jan00  
//DeadCode DAW 14Jan00  		ltim=smlcount;
//DeadCode DAW 14Jan00  	}

//#pragma message("Stub3D.cpp - don't forget to take this out")	//RJS 25Nov98
//	if (currinst && currinst->blocktick) return;				//RJS 25Nov98
//	if (currinst &&												//RJS 25Nov98
//		currinst->viewedwin && 									//RJS 25Nov98
//		!currinst->viewedwin->doneframe &&						//RJS 25Nov98
//		currinst->viewedwin->frametime>10) return;				//RJS 25Nov98
	ticknum++;
	for (Inst3d* inst=currinst;inst;inst=inst->nextinst)
	{
		LONG prev;
		if (!inst->semaphore)	_Error.EmitSysErr("Semaphore null");
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[170]='T';	UByteP(0xB0000)[172]++;
		ReleaseSemaphore(inst->semaphore,1,&prev);							//AMM 12Jan00

//DeadCode AMM 13Jan00 		if (inst->movethread)
//DeadCode AMM 13Jan00 			inst->movethread->ResumeThread();
	}
}
UINT AFX_CDECL Inst3d::moveloop(LPVOID x)
{
	Inst3d* inst=(Inst3d*)x;
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[180]='M';
	forever
	{
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[182]='s';
		if (!inst->semaphore)	_Error.EmitSysErr("Semaphore null");
		WaitForSingleObject(inst->semaphore,INFINITE);			//AMM 13Jan00
		if (!inst->mutex)	_Error.EmitSysErr("mutex null");
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[182]='m';
		WaitForSingleObject(inst->mutex,INFINITE);				//AMM 13Jan00
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[184]++;
//DEADCODE DAW 17/02/00 		if (inst->blocktick)
//DEADCODE DAW 17/02/00 		{
//DEADCODE DAW 17/02/00 			if (inst && inst->viewedwin && !inst->paused)
//DEADCODE DAW 17/02/00 				inst->viewedwin->timeSinceLastMove+=2;
//DEADCODE DAW 17/02/00 			int bt=1;
//DEADCODE DAW 17/02/00 			bt+=LockExchange(&inst->blockticks);
//DEADCODE DAW 17/02/00 			bt=LockExchange(&inst->blockticks,bt);
//DEADCODE DAW 17/02/00 			while (bt)
//DEADCODE DAW 17/02/00 			{
//DEADCODE DAW 17/02/00 				bt+=LockExchange(&inst->blockticks);
//DEADCODE DAW 17/02/00 				bt=LockExchange(&inst->blockticks,bt);
//DEADCODE DAW 17/02/00 			}
//DEADCODE DAW 17/02/00 		}	
//DEADCODE DAW 17/02/00 		else
		{
	//DeadCode AMM 26Aug98 			TRACE0("time proc call\n");
			if (inst && inst->viewedwin)
				inst->viewedwin->timeSinceLastMove=0;
//DEADCODE DAW 17/02/00 			howcamehere=0xf00;
			inst->insidetimer = TRUE;
			Log_Stack.Log(LogStack::MOVECODE,40000);
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[182]='c';
			inst->DoMoveCycle();
			Log_Stack.UnLog(LogStack::MOVECODE);
			inst->insidetimer = FALSE;
			inst->framecount++;
		}
//DeadCode AMM 13Jan00 		if (inst->movethread)
//DeadCode AMM 13Jan00 			inst->movethread->SuspendThread();
		if (!inst->movethread)	//immediately after resume...
			return 0;

		if (!inst->mutex)	_Error.EmitSysErr("mutex null");
		ReleaseMutex(inst->mutex);								//AMM 13Jan00
	}
}
 

WINBASEAPI
BOOL
WINAPI
QueryPerformanceCounter(
    LARGE_INTEGER *lpPerformanceCount
    );

WINBASEAPI
BOOL
WINAPI
QueryPerformanceFrequency(
    LARGE_INTEGER *lpFrequency
    );

void	Inst3d::DoMoveCycle()
{
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[200]='C';
	bool	timeout=false;
//DEADCODE RDH 12/07/99 	ULong num=1;
	OverLay.accelcountdown=1;
	for (View3d* view=viewedwin;view;view=view->nextview)
	{
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[202]='v';
		if (view->doneframe)
		{
			if (view->View_Point)
			{
//DEADCODE DAW 18/02/00 				UByteP(0xB0000)[204]='s';
				_Miles.ProcessSpot(view->View_Point);							//RJS 25May99
//DEADCODE DAW 18/02/00 				UByteP(0xB0000)[204]='m';
				_Radio.ProcessMessages(view->View_Point->FrameTime());			//RJS 25May99
//DEADCODE DAW 18/02/00 				UByteP(0xB0000)[204]='-';
			}
			if (!Paused())
				view->lastframetime=view->frametime;
			else
				view->lastframetime=0;
			view->lastrealframetime=view->frametime;
			view->frametime=0;
			view->realframetime=0;
			view->doneframe=FALSE;
//DEADCODE DAW 18/02/00 			UByteP(0xB0000)[204]='a';
			if (Accel())
				if (accelframes>0)
					if (view->lastrealframetime<MAX_ACCEL_FRAME)
					{
						accelframes++;
						if (	accelframes>10 
							&& (OverLay.keyFlags&KF_ACCELFRAMESMASK)!=KF_SLOWACCEL
							&& (OverLay.keyFlags&KF_ACCELFRAMESMASK)<KF_BESTACCEL)
						{
							accelframes=0;
							OverLay.keyFlags++;
						}
					}
					else
						accelframes=0;
				else
					if (view->lastrealframetime>=MAX_ACCEL_FRAME)
					{
						accelframes--;
						if (accelframes<-10 && (OverLay.keyFlags&KF_ACCELFRAMESMASK)>KF_SLOWACCEL+1)
						{
							accelframes=0;
							OverLay.keyFlags--;
						}
					}
					else
						accelframes=1;
		}
		
		UWord framemax=Accel()?MAX_ACCEL_FRAME:MAX_NORMAL_FRAME;


// for comms we want a higher number, because throwing away frames means that
// a machine will begin to lag behind other machines.

		if (_DPlay.Implemented)									//AMM 12Jan00
			framemax=500;										//AMM 12Jan00
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[202]='f';

		if (view->frametime<framemax)		//max buffer up of 2 seconds of action.
//		if (view->frametime<200)		//max buffer up of 2 seconds of action.
		{								//reduce this to 20 for profiling @ 5 fps
			view->frametime+=2;
			//Pause key && accel key must not be pressed on any 3D UI screens!
			if (OverLay.pCurScr!=NULL) 	//UNKLUDGE					  //JIM 08/06/99
			{
//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[204]='o';
				Key_Tests.KeyPress3d(PAUSEKEY);
				Key_Tests.KeyPress3d(ACCELKEY);
			}
			else
			{
				if (!Accel())
				{
				if (!Paused())
				{
		//			view->frametime+=2;
					if (Key_Tests.KeyPress3d(PAUSEKEY)
						&& !_DPlay.Implemented)							//AMM 23Nov98
					{
						Paused(TRUE);
						OverLay.TriggerMessage(COverlay::PAUSEMESS);
						if (_Replay.Playback)
						{
							_Replay.PlaybackPaused=TRUE;
							OverLay.pCurScr=OverLay.pNewScr=&OverLay.replayScr;
						}
					}
				}
				else
				{
//DEADCODE DAW 18/02/00 				UByteP(0xB0000)[204]='j';
					_Analogue.PollPosition();
					if (Key_Tests.KeyPress3d(PAUSEKEY))
					{
						if (!_DPlay.Implemented)
						{
							Paused(FALSE);
							OverLay.TriggerMessage(COverlay::CLEARMESS);
							if (_Replay.Playback)
							{
								_Replay.PlaybackPaused=FALSE;
								OverLay.pCurScr=OverLay.pNewScr=&OverLay.replayPlayingScr;
							}
						}
					}
				}
				}
				if (!Paused() && Key_Tests.KeyPress3d(ACCELKEY))
				{
					if (!_DPlay.Implemented)
					{
						if (!Accel())		
						{
	//DeadCode DAW 26May99 						if (_Replay.Record)
	//DeadCode DAW 26May99 						{
	//DeadCode DAW 26May99 							_Replay.stopforaccel=true;
	//DeadCode DAW 26May99 							_Replay.StopRecord();
	//DeadCode DAW 26May99 						}

							Accel(TRUE);
							OverLay.TriggerMessage(COverlay::ACCELMESS);
							Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_WAYPT);
							UByte okey=(OverLay.keyFlags&~KF_ACCELFRAMESMASK)+KF_SLOWACCEL;
							OverLay.keyFlags=okey;
						}	
						else
						{
	//DeadCode DAW 26May99 						if (_Replay.stopforaccel)
	//DeadCode DAW 26May99 						{
	//DeadCode DAW 26May99 							_Replay.stopforaccel=false;
	//DeadCode DAW 26May99 							_Replay.StartRecordFlag=TRUE;
	//DeadCode DAW 26May99 						}

							Accel(FALSE);
							OverLay.TriggerMessage(COverlay::CLEARMESS);
							Manual_Pilot.AutoToggle(ManualPilot::MANUAL);
							OverLay.keyFlags&=~KF_ACCELFRAMESMASK;
						}
					}
				}
			}
			if (Key_Tests.KeyPress3d(RECORDTOGGLE))				//AMM 16Apr99
			{													//AMM 16Apr99
				_Replay.ToggleRecord();							//AMM 16Apr99
			}													//AMM 16Apr99
			if (Key_Tests.KeyPress3d(RESETRECORD))				//AMM 16Apr99
			{													//AMM 16Apr99
//				_DPlay.beginsyncflag=true;
				_Replay.ResetRecord();							//AMM 16Apr99
			}													//AMM 16Apr99
//			if (_DPlay.Implemented && Key_Tests.KeyPress3d(SUICIDE))					//AMM 16Apr99
			if (Key_Tests.KeyPress3d(SUICIDE))					//AMM 16Apr99
			{													//AMM 16Apr99
//DeadCode AMM 28Apr99 				if (!_DPlay.ResyncPhase)
//DeadCode AMM 28Apr99 				{
//DeadCode AMM 28Apr99 					_DPlay.Initiator=TRUE;
//DeadCode AMM 28Apr99 					_DPlay.BeginSyncPhase();
//DeadCode AMM 28Apr99 				}

				if (_DPlay.Implemented)							//AMM 16Apr99
					_DPlay.CommitSuicide();						//AMM 16Apr99
			}													//AMM 16Apr99

// pause/unpause now done in overlay for replay playback
/*			if (_Replay.Playback)
			{
				if (_Replay.ppchanged)
				{
					_Replay.ppchanged=false;
					if (Paused())
						Paused(FALSE);
					else
						Paused(TRUE);
				}
//				if (_Replay.PlaybackPaused)
//				{
//					Paused(TRUE);
//				}
//				else
//				{
//					Paused(FALSE);
//				}
			}*/

//DEADCODE DAW 18/02/00 		UByteP(0xB0000)[204]='p';
			if (_Replay.Playback)
			{
				if (_Replay.PlaybackPaused)
				{
// stops animations from continuing when playback reaches end of file and pauses

					Paused(TRUE);
				}
			}

			UByte okey=OverLay.keyFlags;
			OverLay.keyFlags&=KF_ACCELFRAMESMASK;
			
			if (!_DPlay.Implemented)
			{
				if (okey&KF_PAUSEOFF)		Paused(FALSE);
				else if (okey&KF_PAUSEON)	Paused(TRUE);
			}

//DeadCode AMM 10Jun99 			if (okey&KF_ACCELOFF)		Accel(FALSE);
			if (okey&KF_ACCELOFF)
			{
				if (_DPlay.Implemented)
				{
					if (Accel())
						_DPlay.SendQuitAccelMessage();
				}
				else
				{
					Accel(FALSE);
				}
			}
			else if (okey&KF_ACCELON)	Accel(TRUE);

			if (Accel()) 
				OverLay.accelcountdown=(okey&KF_ACCELFRAMESMASK)<<2;	//Max value is 60 moves/timer call
		}
		else
		{
			timeout=true;
		}
///		((char*)0xb0000+160)[view->frametime]++;
	}
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[202]='t';
	if (!timeout)
	{
//DeadCode AMM 10Jun99 		if (num>1)
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			_DPlay.commsaccel=true;
//DeadCode AMM 10Jun99 			_DPlay.commsaccelpsend=true;
//DeadCode AMM 10Jun99 		}
#ifndef NDEBUG
		static LARGE_INTEGER	pc,pc2;
		QueryPerformanceCounter(&pc);
		int cycles=OverLay.accelcountdown;
#endif
		while (OverLay.accelcountdown--)
		{
//DeadCode AMM 12May99 			if (!Paused())
//DeadCode AMM 12May99 				timeofday+=2;
//DeadCode AMM 12May99 			MoveCycle(timeofday,world);
//DEADCODE DAW 18/02/00 			UByteP(0xB0000)[204]='m';
			MoveCycle(world);									//AMM 11May99
			if (OverLay.accelcountdown)
				if (	Key_Tests.KeyPress3d(RPM_00) 
					||	Key_Tests.KeyPress3d(RESETVIEW)
					||	Key_Tests.KeyPress3d(PADLOCKTOG)
					||	Key_Tests.KeyPress3d(SHOOT)
					||	Key_Tests.KeyPress3d(MENUSELECT)
					)
					OverLay.CancelAccel();
		}
//DeadCode CSB 15/06/99	#ifndef NDEBUG
//DeadCode CSB 15/06/99			int prevdif=pc.LowPart-pc2.LowPart;
//DeadCode CSB 15/06/99			QueryPerformanceCounter(&pc2);
//DeadCode CSB 15/06/99			int nextdif=pc2.LowPart-pc.LowPart;
//DeadCode CSB 15/06/99			static int monopos=0;
//DeadCode CSB 15/06/99			Mono_Text.PrintHexAt(monopos,0,cycles+howcamehere,3);
//DeadCode CSB 15/06/99			Mono_Text.PrintHexAt(monopos+4,0,prevdif/16,4);
//DeadCode CSB 15/06/99			Mono_Text.PrintHexAt(monopos+9,0,nextdif/16,4);
//DeadCode CSB 15/06/99			monopos+=16;
//DeadCode CSB 15/06/99			Mono_Text.PrintAt(monopos,0,UByteP("                  "));
//DeadCode CSB 15/06/99			if (monopos>=24*80)
//DeadCode CSB 15/06/99				monopos=0;
//DeadCode CSB 15/06/99	#endif


//DEADCODE AMM 11/06/99 		_DPlay.commsaccel=false;
	}
}



//DeadCode AMM 12May99 void	Inst3d::MoveCycle(int timeofday,WorldStuff* worldref)
void	Inst3d::MoveCycle(WorldStuff* worldref)					//AMM 11May99
{
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[210]='U';
	ULong num=1;
	_Replay.replayskip=false;									//DAW 18Aug99

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[212]='m';
	_Miles.ProcessPercussion();									//DAW 18Aug99

//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[212]='p';
	if (_Replay.Playback)										//AMM 08Feb99
	{
//DeadCode AMM 22Apr99 		if (_Replay.setpaused)									//AMM 14Apr99
		if (_Replay.setpaused==1)								//AMM 22Apr99
		{														//AMM 14Apr99
//DeadCode AMM 22Apr99 			_Replay.setpaused=false;							//AMM 14Apr99
			Paused(TRUE);										//AMM 14Apr99
			_Replay.setpaused=0;									//AMM 22Apr99
		}														//AMM 14Apr99
		else if (_Replay.setpaused==-1)							//AMM 22Apr99
		{														//AMM 22Apr99
			Paused(FALSE);										//AMM 22Apr99
			_Replay.setpaused=0;									//AMM 22Apr99
		}														//AMM 22Apr99

		switch (_Replay.ReplayFlag)									//AMM 14Jan99
		{
		case RF_NONE:
			break;

		case RF_SKIPFRAMES:
		case RF_BLOCKREWIND:
		case RF_SKIPTOPREVIOUSMARK:
		case RF_SKIPTONEXTMARK:
			_Replay.CalcCurrPos();									  //JIM 19/05/99
//DeadCode AMM 01Apr99 
//DeadCode AMM 01Apr99 			switch (_Replay.ReplayFlag)
//DeadCode AMM 01Apr99 			{
//DeadCode AMM 01Apr99 			case RF_SKIPFRAMES:
//DeadCode AMM 01Apr99 				break;
//DeadCode AMM 01Apr99 			case RF_BLOCKREWIND:
//DeadCode AMM 01Apr99 				_Replay.BlockRewind();
//DeadCode AMM 01Apr99 				_Replay.CalcCurrPos();
//DeadCode AMM 01Apr99 				break;
//DeadCode AMM 01Apr99 			case RF_SKIPTOPREVIOUSMARK:
//DeadCode AMM 01Apr99 				_Replay.SkipToPreviousMark();
//DeadCode AMM 01Apr99 				_Replay.CalcCurrPos();
//DeadCode AMM 01Apr99 				break;
//DeadCode AMM 01Apr99 			case RF_SKIPTONEXTMARK:
//DeadCode AMM 01Apr99 				_Replay.SkipToNextMark();
//DeadCode AMM 01Apr99 				_Replay.CalcCurrPos();
//DeadCode AMM 01Apr99 				break;
//DeadCode AMM 01Apr99 			}
			if (_Replay.skipOK)
			{
				num=_Replay.framestoskip;//+1;
 				_Replay.ResetFlags();
				_Replay.replayskip=true;
			}
			break;

		case RF_BLOCKFORWARD:
 			_Replay.ResetFlags();
//DeadCode AMM 14Apr99 			_Replay.BlockForward();
			break;

		case RF_FRAMEFORWARD:
			if (Paused())
				_Replay.FrameForward();
			else
				_Replay.ResetFlags();
			break;

		case RF_FRAMEREWIND:
//DeadCode AMM 22Apr99 			if (Paused())
//DeadCode AMM 22Apr99 			{
//DeadCode AMM 22Apr99 				_Replay.PlaybackPaused=TRUE;
//DeadCode AMM 22Apr99 				num=_Replay.FrameRewind();
//DeadCode AMM 22Apr99 				replayskip=true;
//DeadCode AMM 22Apr99 			}
			if (!Paused())
			{
				Paused(TRUE);
				_Replay.PlaybackPaused=TRUE;
				OverLay.pCurScr=OverLay.pNewScr=&OverLay.replayScr;
			}
			num=_Replay.FrameRewind();
			_Replay.replayskip=true;

			break;
		}
	}
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[212]='p';

	if (!Paused()												//AMM 14Jan99
	|| _Replay.ReplayFlag==RF_FRAMEFORWARD						//AMM 14Jan99
	|| _Replay.ReplayFlag==RF_FRAMEREWIND						//AMM 14Jan99
	|| _Replay.replayskip)												//AMM 25Feb99
//DeadCode AMM 25Feb99 	|| num>1)													//AMM 14Jan99
	{
		int oldprec=GETPREC();
		SETPREC(3);
#ifndef NDEBUG
//DeadCode CSB 13/07/99			if (GETPREC()!=3)
//DeadCode CSB 13/07/99				INT3;
#endif
		
		while (num--)											//AMM 06Oct98
		{
//DeadCode AMM 12May99 			if (Paused())
//DeadCode AMM 12May99 			{
//DeadCode AMM 12May99 // must have got in here because of replay, update time
//DeadCode AMM 12May99 
//DeadCode AMM 12May99 				this->timeofday+=2;
//DeadCode AMM 12May99 			}

//DEADCODE DAW 11/05/99 			timeofday=0;
//DeadCode CSB 05/05/99				timeofday=0;

// done after dosmove
//DeadCode AMM 30Jun99 			timeofday+=2;										//AMM 11May99
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[212]='w';
			MobileItem::WinMove(timeofday,worldref);
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[212]='s';

			if (_Replay.replayskip)
			{	
				if (viewedwin)
				{
					View3d* view=viewedwin;

					view->frametime=2;
					_Replay.UpdateSmokes();
				}
			}
		}

		if (_DPlay.Implemented)
		{
			if (_DPlay.ResyncPhase)
			{
				Paused(TRUE);
				_DPlay.csync=false;
			}
		}

#pragma message(__HERE__"GETPREC()!=3  !!!!")
#ifndef NDEBUG
//DeadCode CSB 13/07/99			if (GETPREC()!=3)
//DeadCode CSB 13/07/99				INT3;
#endif
		SETPREC(oldprec);

		if (_Replay.Playback)
			_Replay.CalcCurrPos();
	}

	if (_Replay.Playback)
	{
		if (_Replay.ReplayFlag==RF_FRAMEREWIND || _Replay.ReplayFlag==RF_FRAMEFORWARD)						//AMM 14Jan99
		{															//AMM 14Jan99
			_Replay.ResetFlags();										//AMM 18Feb99
//DeadCode AMM 16Apr99 			blockticks=0;											//AMM 14Jan99
		}															//AMM 14Jan99
	}
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[212]='=';
}

void	View3d::BlockTick(Bool setit)
{
	if (setit==BOOL_Align) 											  //DAW 10/02/00
	{	//Special flag to say that timer should be aligned
		while (	inst->framecount==waitforframecount)
		{
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[190]='B';	UByteP(0xB0000)[192]++;
			Sleep(0);
		}
		if (Save_Data.detail_3d[DETAIL3D_FASTFRAME])
		{
			while (	inst->framecount==waitforframecount)
				Sleep(0);
			while (inst->framecount==waitforframecount+1)
			{
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[190]='b';	UByteP(0xB0000)[192]++;
				Sleep(0);
			}
		}
		waitforframecount=inst->framecount;
	}
	inst->BlockTick(setit);
}

void	ViewPoint::BlockTick(Bool q)
{
//DEADCODE DAW 18/02/00 	UByteP(0xB0000)[194]='=';
	view3dwin->BlockTick(q);
}

void	Inst3d::BlockTick(Bool setit)
{
	static int nestingcheck=0;
	while (insidetimer == TRUE)
	{Sleep(0);}

 //		insidetimer = insidetimer;

	if (!mapview)
	{
		if (setit)
		{
		if (nestingcheck++)	_Error.EmitSysErr("blocktick nesting error!");
		if (!mutex)	_Error.EmitSysErr("mutex null");
			WaitForSingleObject(mutex,INFINITE);				//AMM 13Jan00

//DEADCODE DAW 17/02/00 			int bt=LockExchange(&blocktick,1);
//DEADCODE DAW 17/02/00 			while (bt==1)
//DEADCODE DAW 17/02/00 			{	//some other process is also setting the ticker. Wait for it to finish
//DEADCODE DAW 17/02/00 				Sleep(0);												  //JIM 21/12/98
//DEADCODE DAW 17/02/00 				;;//cope with simultanious accesses by releasing timeslice? //JIM 21/12/98
//DEADCODE DAW 17/02/00 				bt=LockExchange(&blocktick,1);							  //JIM 21/12/98
//DEADCODE DAW 17/02/00 			}
		}
		else
		{
		if (--nestingcheck)	_Error.EmitSysErr("blocktick nesting error!");
//DEADCODE DAW 17/02/00 			howcamehere=0;
//DeadCode AMM 13Jan00 			LockExchange(&blocktick,0);
//DEADCODE DAW 17/02/00 			int bt=LockExchange(&blockticks,0);
//DeadCode AMM 13Jan00 			while (bt--)
//DeadCode AMM 13Jan00 				if (movethread)
//DeadCode AMM 13Jan00 					movethread->ResumeThread();	//relaunch thread this many times

//DEADCODE DAW 17/02/00 			do{
//DEADCODE DAW 17/02/00 				while (bt--)
//DEADCODE DAW 17/02/00 				{
//DEADCODE DAW 17/02/00 					howcamehere+=0x100;
//DEADCODE DAW 17/02/00 					if (!_DPlay.Implemented || (_DPlay.Implemented && _DPlay.csync)) //AMM 09/07/99
//DEADCODE DAW 17/02/00 						DoMoveCycle();
//DEADCODE DAW 17/02/00 				}
//DEADCODE DAW 17/02/00 				bt=LockExchange(&blockticks,0);
//DEADCODE DAW 17/02/00 			} while (bt);
			//there's always a chance one will slip through, but we will pick it up later!
//DEADCODE DAW 17/02/00 			bt=LockExchange(&blocktick,0);
//DEADCODE DAW 17/02/00 			if (bt!=1)
//DEADCODE DAW 17/02/00 				_Error.EmitSysErr("Something wrong in semaphore logic!");

		if (!mutex)	_Error.EmitSysErr("mutex null");
			ReleaseMutex(mutex);
		}
	}
}

int	View3d::PeekFrameTime()
{
	if (doneframe)
		return 0;
	else
		return frametime;
}
int	View3d::LastFrameTime()
{
//	*(char*)0xb0000='0'+lastframetime;
	return lastframetime;
}
int View3d::TimeSinceLastMove()
{
	return timeSinceLastMove;
}
int	Display::FrameTime()
{
	if (view3dwin)
		return	view3dwin->LastFrameTime();
	else
		return 0;
}

int	ViewPoint::FrameTime()
{
	return	view3dwin->LastFrameTime();
}

int ViewPoint::TimeSinceLastMove()
{
	return view3dwin->TimeSinceLastMove();
}

int	ViewPoint::RealFrameTime()
{
//	*(char*)0xb0002='0'+view3dwin->RealFrameTime();
	return	view3dwin->RealFrameTime();
}

int	ViewPoint::TimeOfDay()
{
//	*(char*)0xb0002='0'+view3dwin->RealFrameTime();
	if (!this)														  //AMM 25/06/99
		return 0;													  //AMM 25/06/99
	return	view3dwin->TimeOfDay();
}

void	View3d::DoneFrame()
{
	doneframe=TRUE;
}

void	AggTracer(char* str)
{
//	TRACE0(str);
}

bool ViewPoint::Accel()
{
	if (!this) return false;
	if (!view3dwin) return false;
	return view3dwin->Accel();
}
int COverlay::GetTime()
{
	return 0;	//Master_3d.currinst->timeofday;
}
