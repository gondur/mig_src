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
//Filename       dosmove.cpp
//System         
//Author         Andrew McRae
//Date           Mon 5 Aug 1996
//Description    Move all things.
//				 Called from ThreeDee::PossMoveCycle in 3d\3dcode
//------------------------------------------------------------------------------

#include	"DOSDefs.h"	
#include	"WorldInc.h"
#include	"UniqueID.h"
//DeadCode DAW 26Nov96 #include	"UniqueID.g"
#include	"flymodel.h"
#include	"ai.h"

#include	"persons2.h"

#define		SPECIAL_KEYMAPS	FALSE
#include	"Keytest.h"
#include	"hotkeys.h"
#include	"mytime.h"
#include	"viewsel.h"
#include	"mymath.h"

#include	"myerror.h"

#include	"transite.h"

//DeadCode RJS 02Dec97 #include	"3dcom.h"
#include	"3dcode.h"
#include	"lstream.h"											//PD 31Oct96

#include	"winmove.h"											//RDH 25Nov96
#include	"aaa.h"

extern void	CheckE3();

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PossMoveCycle
//Author		Jim Taylor
//Date			Mon 3 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 01Sep98 Bool go4it=FALSE;
static void ThreeDee::PossMoveCycle()
{
	if (!(Timer_Code.paused+Timer_Code.accel))					//JIM 15Oct96
		if (Timer_Code.TestMsgTime())	// checks for 3 csec
			mobileitem::DosMove ();
}


char	fnum=0;
void mobileitem::DosMove ()
{
	fnum++;
//DeadCode JIM 06Jan97 	CheckE3();
	if (Timer_Code.accel==FALSE)								//JIM 13Nov96
		LandStream.ProcessSeekRequests();						//PD 18Nov96

	WorldStuff &world = mobileitem::GetWorld();
	
//DeadCode JIM 06Jan97 	CheckE3();
	Art_Int.VisibleCheck();

//DeadCode JIM 06Jan97 	CheckE3();
	mobileitem::MoveAll(world);

//DeadCode JIM 06Jan97 	CheckE3();
	TransientItem::MoveAllTrans(world);
	Three_Dee.livelist->Event();			//JIM 22Sep96 - moved from 3dcode

//DeadCode JIM 06Jan97 	CheckE3();
	Manual_Pilot.MainManualPilot();				//make this last - 3 comms
//DeadCode JIM 06Jan97 	CheckE3();
	Trans_Obj.PilotedACHit();					//make this last - 4 comms
//DeadCode JIM 06Jan97 	CheckE3();
	Trans_Obj.ControlKeybWeap(Manual_Pilot.ControlledAC2,world);//RDH 03Oct96
//DeadCode JIM 06Jan97 	CheckE3();
}


// Comms Stubs

void SendInitPacket ()
{
}

void SendInit2Packet ()
{
}

void DPlay::NewBullet (TransientItem* BulPtr)
{
}

void DPlay::NewCollision (itemptr, itemptr, ULong, SByte)
{
}

void DPlay::NewDamage (AirStrucPtr ac, BitStates oldstate, BitFlags whichbit)
{
}

void DPlay::ExitDirectPlay ()
{
}

void DPlay::UIMultiPlayInit ()
{
}

//DeadCode AMM 01Jun98 Bool DPlay::UISelectH2H ()
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 	return FALSE;
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 Bool DPlay::UISelectNetwork ()
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 	return FALSE;
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 void DPlay::UICreateSession ()
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 void DPlay::UIJoinSession ()
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 void DPlay::UICancelNetwork ()
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }

ULong DPlay::UIUpdateMainSheet (H2HPlayer* H2H_Player, SaveData* Save_Data, ULong& player, SWord& currmission_no, SLong& currdate)
{
	return 0;
}

//DeadCode AMM 01Jun98 void DPlay::SetFlyNow (Bool State)
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 Bool DPlay::FlyNow ()
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 	return FALSE;
//DeadCode AMM 01Jun98 }

void DPlay::UILeavingMainSheet (H2HPlayer* H2H_Player)
{
}

void DPlay::UIPaintShop (Bool Status)
{
}

void DPlay::UIPrefs (Bool Status)
{
}

//DeadCode AMM 01Jun98 void DPlay::UISendMessage (H2HPlayer*, char*)
void DPlay::UISendDialogue (H2HPlayer*, char*)
{
}

void DPlay::UIUpdateMessage (H2HPlayer*, char*)
{
}

ULong DPlay::UINetworkSelectFly (H2HPlayer* H2H_Player, SaveData* Save_Data, PilotType* Active_Pilot, SWord currmission_no, SLong currdate)
{
	return 0;
}

//DeadCode AMM 01Jun98 ULong DPlay::UINewPlayer (char* Name, char* SessionName, H2HPlayer* H2H_Player)
ULong DPlay::UINewPlayer (char* Name, char* SessionName)
{
	return 0;
}

void DPlay::UIGetSessionListUpdate (char ** JoinNames, ULong& Entries, ULong& Changed)
{
}

void DPlay::UIAssignServices(char** JoinServices, ULong& Entries,ULong& Changed)
{
}

Bool DPlay::UISelectServiceProvider(char* servicename)
{
	return FALSE;
}

Bool DPlay::UISendMessageToAll (char* Data, ULong Length)
{
	return FALSE;
}

Bool DPlay::UISendMessageToPlayers (char* Data, ULong Length)
{
	return FALSE;
}

Bool DPlay::UIGetMyNonSysMessage (char* Data, ULong& Length)
{
	return FALSE;
}

//DeadCode AMM 01Jun98 void DPlay::UIModemWait ()
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 void DPlay::UIModemDial ()
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 void DPlay::InitCommFlags ()
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 	Modem = FALSE;
//DeadCode AMM 01Jun98 	Network = FALSE;
//DeadCode AMM 01Jun98 }

//DeadCode AMM 01Jun98 void DPlay::UISendPrefs (SaveData* Save_Data, SWord currmission_no, SLong currdate, Bool Final)
Bool DPlay::UISendPrefs (SaveData* Save_Data, SWord currmission_no, SLong currdate, Bool Final)
{
	return FALSE;
}

Bool DPlay::UISendPaintScheme (PilotType* Active_Pilot)
{
	return FALSE;
}

//DeadCode AMM 01Jun98 void DPlay::RecordKill (AirStrucPtr ac)
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 void DPlay::FlushMessageQueue (myDPID PlayerID)
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 void DPlay::LogEntry (char* Entry)
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }
//DeadCode AMM 01Jun98 
//DeadCode AMM 01Jun98 void DPlay::LogPos (ULong x, ULong y, ULong z)
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }

void DPlay::ResurrectMe (AirStrucPtr ac, Bool Send)
{
}

void DPlay::SetScore (AirStrucPtr victim,UniqueID killer,ULong deathtype)//AMM 19Feb97
{
}

void DPlay::PredictMove(AirStruc* ac)
{
}

void DPlay::ResurrectKilledAircraft (AirStrucPtr)
{
}

void DPlay::ResurrectAircraft (AirStrucPtr ControlledAC, Bool Forced)
{
}

void DPlay::InitResurrect (AirStrucPtr ac)
{
}

Bool DPlay::PermitKeys ()
{
	return TRUE;
}

void DPlay::AddDeltas(AirStruc* AC, Bool sign)
{
}

void DPlay::SendGonePacket()
{
}

void DPlay::CommitSuicide()
{
}

Bool DPlay::Synchronise()
{
	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DPlay
//Author		R. Hyde 
//Date			Tue 3 Dec 1996
//
//Description	Moved constructor & destructor from winmove.h
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON		DPlay::DPlay ()
{
	SelectedService = NULL;
//DeadCode AMM 01Jun98 	Modem = FALSE;
//DeadCode AMM 01Jun98 	Network = FALSE;
}

CON		DPlay::~DPlay ()
{
}

void DPlay::UIGetMyPlayerName (H2HPlayer* H2H_Player, char* strg)
{
}


void DPlay::RepairAircraft (AirStrucPtr ac)
{
}
//DeadCode AMM 01Jun98 void DPlay::StoreKill (AirStrucPtr ac, AirStrucPtr kac, Bool Send)
//DeadCode AMM 01Jun98 {
//DeadCode AMM 01Jun98 }

void DPlay::SendKill (AirStrucPtr ac, ULong QuitNow,ULong deathtype, AirStrucPtr achit,SByte gindex)
{
}
void DPlay::TimeoutInSynch()
{
}

void DPlay::BeginSyncPhase()
{
}

ULong DPlay::JoinGame()
{
	return 0;
}
Bool	DPlay::UIGetMessage(char* Data, ULong& Length, ULong& from)
{
	return FALSE;
}

void DPlay::BeginAggregation()
{
}

void DPlay::SetRandomListPos(){};
void DPlay::InitBuffers(){};
void DPlay::ResetDeltas(){};

CON	Replay::Replay(){};
CON	Replay::~Replay(){};
Bool Replay::StoreHeader(){return FALSE;};
Bool Replay::StoreDeltas(){return FALSE;};
Bool Replay::OpenRecordLog(){return FALSE;};
void Replay::CloseRecordLog(){};
Bool Replay::OpenPlaybackLog(){return FALSE;};
void Replay::ClosePlaybackLog(){};
Bool Replay::StoreACDetails(){return FALSE;};
Bool Replay::LoadACDetails(){return FALSE;};
Bool Replay::LoadHeader(){return FALSE;};
Bool Replay::LoadDeltas(){return FALSE;};
Bool Replay::StoreRandomList(){return FALSE;};
Bool Replay::LoadRandomList(){return FALSE;};
Bool Replay::LoadGlobalRefs(){return FALSE;};
Bool Replay::StoreGlobalRefs(){return FALSE;};
Bool Replay::BeginRecord(){return FALSE;};
Bool Replay::LoadDeadItems(){return FALSE;};
Bool Replay::LoadMobPositions(){return FALSE;};
void Replay::UpdateGhostAC(){};



//TempCode ARM 07Dec96 void DPlay::AircraftDead (AirStrucPtr ac, Bool logdeath)
//TempCode ARM 07Dec96 {
//TempCode ARM 07Dec96 }
