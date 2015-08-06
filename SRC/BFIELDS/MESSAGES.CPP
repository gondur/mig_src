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
//Filename       messages.cpp		debugfile
//System         
//Author         Jim Taylor
//Date           Thu 3 Oct 1996
//Description    Message creation in persons class
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#include	"worldinc.h"
#include	"myerror.h"
#include	"text.h"
#include	"persons2.h"
#include	"flymodel.h"
//#include	"Mytime.h"
#include	"stub3d.h"
#include	"rchatter.h"

//------------------------------------------------------------------------------
//DeadCode RJS 27Jan99 void	Persons2::AddMessageIfPlayerSq(AirStrucPtr eye,UserMsg::Reason r,TextSnip0 t,ItemBasePtr cp)
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	if (eye->ai.eventlog->stage==EventLog::TAKEOFF)
//DeadCode RJS 27Jan99 		AddMessage(r,t,cp);
//DeadCode RJS 27Jan99 }
//DeadCode RJS 27Jan99 void	Persons2::AddMessageIfPlayer(ItemBasePtr eye,UserMsg::Reason r,TextSnip0 t,ItemBasePtr cp)
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	if (eye==Manual_Pilot.ControlledAC2)
//DeadCode RJS 27Jan99 		AddMessage(r,t,cp);
//DeadCode RJS 27Jan99 }
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 void	Persons2::AddMessage(UserMsg::Reason r,TextSnip0 t,Coords3D&  cp)
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	if (r!=UserMsg::COURSE)
//DeadCode RJS 27Jan99 		ClrMessage(UserMsg::COURSE);
//DeadCode RJS 27Jan99 	int c=0;
//DeadCode RJS 27Jan99 	for (c=0;c<UserMessages::MAX-1;c++)
//DeadCode RJS 27Jan99 		breakif (usermessages.line[c].reason==r);
//DeadCode RJS 27Jan99 	if (usermessages.line[c].reason!=r)
//DeadCode RJS 27Jan99 	{
//DeadCode RJS 27Jan99 		usermessages.newmessages=TRUE;
//DeadCode RJS 27Jan99 	}
//DeadCode RJS 27Jan99 	for (c=c;c>0;c--)
//DeadCode RJS 27Jan99 		usermessages.line[c]=usermessages.line[c-1];
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 	UserMsg& umlz=usermessages.line[0];
//DeadCode RJS 27Jan99 	umlz.reason=r;
//DeadCode RJS 27Jan99 	umlz.trgname=t;
//DeadCode RJS 27Jan99 	if (&cp==&umlz.despos)
//DeadCode RJS 27Jan99 	{
//DeadCode RJS 27Jan99 		umlz.World=cp;
//DeadCode RJS 27Jan99 	 	umlz.trgplace=&umlz;
//DeadCode RJS 27Jan99 	}
//DeadCode RJS 27Jan99 	else  // should not get here!
//DeadCode RJS 27Jan99 #ifdef __WATCOMC__
//DeadCode RJS 27Jan99 		INT3();													//JIM 19Jun97
//DeadCode RJS 27Jan99 #endif
//DeadCode RJS 27Jan99 #ifdef __MSVC__
//DeadCode RJS 27Jan99 		INT3;
//DeadCode RJS 27Jan99 #endif
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 //DeadCode JIM 14Nov96 		umlz.trgplace=&cp;
//DeadCode RJS 27Jan99 }
//DeadCode RJS 27Jan99 void	Persons2::AddMessage(UserMsg::Reason r,TextSnip0 t,ItemBasePtr cp)
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	if (r!=UserMsg::COURSE)
//DeadCode RJS 27Jan99 		ClrMessage(UserMsg::COURSE);
//DeadCode RJS 27Jan99 //DeadCode JIM 25Jul96 	if (t!=TextRef_MIN)
//DeadCode RJS 27Jan99 //DeadCode JIM 25Jul96 		t=_Text.Conv(t,permtextpage);
//DeadCode RJS 27Jan99 	int c=0;
//DeadCode RJS 27Jan99 	//look for existing entry
//DeadCode RJS 27Jan99 	for (c=0;c<UserMessages::MAX-1;c++)		
//DeadCode RJS 27Jan99 		breakif (usermessages.line[c].reason==r);		//don't check last one
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 	if (usermessages.line[c].reason!=r)					//because checked here anyway
//DeadCode RJS 27Jan99 	{
//DeadCode RJS 27Jan99 		usermessages.newmessages=TRUE;
//DeadCode RJS 27Jan99 	}
//DeadCode RJS 27Jan99 	//bump earlier entries up over existing entry or over end
//DeadCode RJS 27Jan99 	for (c=c;c>0;c--)
//DeadCode RJS 27Jan99 		usermessages.line[c]=usermessages.line[c-1];
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 	UserMsg& umlz=usermessages.line[0];
//DeadCode RJS 27Jan99 	umlz.reason=r;
//DeadCode RJS 27Jan99 	umlz.trgname=t;
//DeadCode RJS 27Jan99 //DeadCode RDH 15Oct96 	if (cp)
//DeadCode RJS 27Jan99 //TempCode RDH 15Oct96 		if (cp==&AirStruc::despos)
//DeadCode RJS 27Jan99 //TempCode RDH 15Oct96 		{
//DeadCode RJS 27Jan99 //TempCode RDH 15Oct96 			umlz.placefields=cp;
//DeadCode RJS 27Jan99 //TempCode RDH 15Oct96 			umlz.trgplace=&umlz.placefields;
//DeadCode RJS 27Jan99 //TempCode RDH 15Oct96 		}
//DeadCode RJS 27Jan99 //TempCode RDH 15Oct96 		else
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 	umlz.trgplace=cp;
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 //DeadCode RDH 15Oct96 	else
//DeadCode RJS 27Jan99 //DeadCode RDH 15Oct96 	{
//DeadCode RJS 27Jan99 //DeadCode RDH 15Oct96 		umlz.placefields.X=
//DeadCode RJS 27Jan99 //DeadCode RDH 15Oct96 			umlz.placefields.Y=
//DeadCode RJS 27Jan99 //DeadCode RDH 15Oct96 				umlz.placefields.Z=0;
//DeadCode RJS 27Jan99 //DeadCode RDH 15Oct96 		umlz.trgplace=NULL;
//DeadCode RJS 27Jan99 //DeadCode RDH 15Oct96 	}
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 }
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 void	Persons2::ClrMessage(UserMsg::Reason r)
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	int c=0;
//DeadCode RJS 27Jan99 	if (r==UserMsg::NOMSG)
//DeadCode RJS 27Jan99 	{
//DeadCode RJS 27Jan99 		for (c=0;c<UserMessages::MAX;c++)
//DeadCode RJS 27Jan99 			usermessages.line[c].reason=UserMsg::NOMSG;
//DeadCode RJS 27Jan99 	}
//DeadCode RJS 27Jan99 	else
//DeadCode RJS 27Jan99 	{
//DeadCode RJS 27Jan99 		for (c=0;c<UserMessages::MAX;c++)
//DeadCode RJS 27Jan99 		{
//DeadCode RJS 27Jan99 			if (usermessages.line[c].reason==r)
//DeadCode RJS 27Jan99 				break;
//DeadCode RJS 27Jan99 		}
//DeadCode RJS 27Jan99 		if (c<UserMessages::MAX)
//DeadCode RJS 27Jan99 		{
//DeadCode RJS 27Jan99 			while (++c<UserMessages::MAX)
//DeadCode RJS 27Jan99 			{
//DeadCode RJS 27Jan99 				usermessages.line[c-1]=usermessages.line[c];
//DeadCode RJS 27Jan99 			}
//DeadCode RJS 27Jan99 	 		usermessages.line[UserMessages::MAX-1].reason=UserMsg::NOMSG;
//DeadCode RJS 27Jan99 		}
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 	}
//DeadCode RJS 27Jan99 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateLog
//Author		Jim Taylor
//Date			Thu 5 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
struct EventLog *  Persons2::eventloglist;
struct EventLog *  Persons2::TruckLog;
struct EventLog *  Persons2::TargLog;
struct EventLog *  Persons2::PlayerLog;

void	Persons2::UpdateLog(AirStrucPtr	eventitem,int	credits,EventLog::Stage stage)
{
	UpdateLog(eventitem->ai.eventlog,credits,stage,eventitem);
}

void	Persons2::UpdatePlayerLog(AirStrucPtr	eventitem,EventLog::Stage stage)
{
	if (!PlayerLog)
	{
		PlayerLog=new EventLog(eventloglist);
		UpdateLog(PlayerLog,0,stage,eventitem);
		PlayerLog->homebase=eventitem->ai.eventlog->homebase;
		PlayerLog->encounteredtype=eventitem->ai.eventlog->encounteredtype;
		PlayerLog->escorttype=eventitem->ai.eventlog->escorttype;
		PlayerLog->encsize=1;
	}
	else
	{
		UpdateLog(PlayerLog,0,stage);
	}


}

void	Persons2::UpdateLog(ItemPtr	eventitem,int	credits,EventLog::Stage stage)
{
	if (!TargLog)
	{
		TargLog=new EventLog(eventloglist);
		UpdateLog(TargLog,0,stage,eventitem);
		TargLog->encsize=1;
	}
	else
	{
		UpdateLog(TargLog,0,stage);
	}

}
void	Persons2::UpdateLog(MobileItemPtr	eventitem,int	credits,EventLog::Stage stage)
{
	if (!TruckLog)
	{
		TruckLog=new EventLog(eventloglist);
		UpdateLog(TruckLog,credits,stage,eventitem);
		TruckLog->encounteredtype=PT_VEHICLES;
		TruckLog->encsize=10;
	}
	else
	{
		UpdateLog(TruckLog,credits,stage);
	}
}

void	Persons2::UpdateLog(EventLogPtr	eventlog,int	credits,EventLog::Stage stage,ItemBasePtr place)
{
	if (eventlog->stage==EventEntry::TAKEOFF)
		INT3;
//	assert(eventlog&&"AC with no event!");
	if (stage>=eventlog->stage)
	{
		if (stage>eventlog->stage)
		{
			eventlog->stage=stage;
			eventlog->launchtime=Master_3d.currinst->timeofday;
			eventlog->hits=0;
			eventlog->losses=0;
			if (place)
				eventlog->place=RadioChatter::GetPlaceNum(&place->World);
			//return true;
		}
		if (credits>0)
			eventlog->hits+=credits;
		else
			eventlog->losses-=credits;
	}
	//return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsUsingPilotedAcLog
//Author		rdh
//Date			13/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::IsUsingPilotedAcLog()								  //JIM 17/03/99
	{
		if (ai.eventlog->stage==EventLog::TAKEOFF)					  //JIM 17/03/99
			return (TRUE);											  //JIM 17/03/99
		else														  //JIM 17/03/99
			return (FALSE);
	}
