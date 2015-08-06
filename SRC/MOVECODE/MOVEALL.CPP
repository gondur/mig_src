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
//Filename       moveall.cpp
//System         
//Author         Jim Taylor
//Date           Thu 15 Feb 1996
//Description    The code which moves all the items in the world
//				 This module also manages the lists which move the objects
//------------------------------------------------------------------------------
//DeadCode DAW 03Jun99 #define		DBGMEMTEST

#include	"dosdefs.h"											//JIM 17Nov96
	#define F_COMMON
	#define F_GRAFIX
	#define F_BATTLE
#include	"files.g"  
#include	"textref.h"
#include	"world.h"
#include	"worldinc.h"
#include	"flymodel.h"
#include	"transite.h"
#include	"Files.g"
#include	"persons2.h"
#include	"ai.h"
#include	"ranges.h"
#include	"mymath.h"
#include	"miles.h"
#include	"winmove.h"											//ARM 06Dec96
#include	"replay.h"
#include	"files.g"
#include	"worldinc.h"
#include	"planetyp.h"
#include	"myangles.h"
#include	"enumbits.m"
#include	"mytime.h"											//RDH 25Apr96
//MATHABLE	(ANGLES)
#include	"mymath.h"
#include	"vertex.h"
#include	"matrix.h"											//RDH 23May96
#include	"textref.h"
#include	"viewsel.h"											//PD 19Feb96
#include	"hardpasm.h"										//RDH 14Mar96
#include	"3dcom.h"											//PD 16Apr96
#include	"landscap.h"									//PD 15Mar96
#include	"missman2.h"										//JIM 22Aug96
#include	"savegame.h"
#include	"miles.h"											//DAW 04Jul96
#include	"world.h"											//DAW 04Jul96
#include	"transite.h"										//RDH 26Jul96
#include	"collided.h"										//PD 06Sep96
#include	"speed.h"
#include	"ranges.h"
#include	"modvec.h"											//ARM 08Jan97
#include	"model.h"											//ARM 07Jan97
#include	"shapes.h"

#include	"monotxt.h"

//#define DEBUGMOVE

MobileItemPtr	mobileitem::ACList=NULL;
MobileItemPtr	mobileitem::MobileList=NULL;
TransientItemPtr	TransientItem::TransientList=NULL;
WorldStuff*		mobileitem::currworld=NULL;
UByte	mobileitem::timerseed=0;
int		mobileitem::timeofday=0;

//extern Replay	_Replay;
//extern DPlay _DPlay;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveAll
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void mobileitem::MoveAll(WorldStuff& world)
{
//#pragma message("AC move code temporarily disabled...")
//#pragma message("....cos there was 0 frame rate!!!")

  		MoveList(ACList, world);
		MoveList(MobileList, world);	

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveAllTrans
//Author		Martin Alderton
//Date			Wed 20 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransientItem::MoveAllTrans(WorldStuff& world)
{
	MoveTransList(TransientList, world);
}

static UByte dontmove=0;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveList
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void mobileitem::MoveList(MobileItemPtr entry,WorldStuff& world)
{
//	static x=0;
	currworld=&world;											//PD 12Jul96

#ifdef DEBUGMOVE
//DeadCode AMM 24Nov98 	static x=0;
//DeadCode AMM 24Nov98 	if (_Replay.FCReset)
//DeadCode AMM 24Nov98 	{
//DeadCode AMM 24Nov98 		x=0;
//DeadCode AMM 24Nov98 		_Replay.FCReset=FALSE;
//DeadCode AMM 24Nov98 	}

	FILE* fp;
	if (_Replay.Record)
	{
//DeadCode AMM 28Apr99 		fp=fopen("enemy.txt","at");
		fp=fopen("record.txt","at");
	}
	else if (_Replay.Playback)
	{
//DeadCode AMM 28Apr99 		fp=fopen("enemy2.txt","at");
		fp=fopen("playback.txt","at");
	}
	else if (_DPlay.Implemented)
	{
		fp=fopen("commsac.txt","at");
	}
#endif

	while (entry)
	{
		MobileItemPtr	next=entry->nextmobile;
		UWord	oldsector=-1;										  //JIM 17/02/99
		if (entry->movecode!=AUTO_NOPPILOT)								  //JIM 17/02/99
			oldsector=	world.GetSector(*entry);					  //JIM 17/02/99
		else
			oldsector=-1;

		if (entry==Persons2::PlayerGhostAC)				
		{
			INT3;
		}
		else if (entry==Persons2::PlayerSeenAC)
		{
// should go in here to keep ghostac upto date 

#ifdef DEBUGMOVE
			if (_Replay.Record || _Replay.Playback || _DPlay.Implemented)
			{
				UWord uid=entry->uniqueID.count;
//DeadCode AMM 12May99 				fprintf(fp,"%d X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d (ghost)\n",
				fprintf(fp,"%d ID=%x X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d (ghost)\n",
					_Replay.replayframecount,
					uid,
					Persons2::PlayerGhostAC->World.X,
					Persons2::PlayerGhostAC->World.Y,
					Persons2::PlayerGhostAC->World.Z,
					Persons2::PlayerGhostAC->hdg.a,
					Persons2::PlayerGhostAC->pitch.a,
					Persons2::PlayerGhostAC->roll.a,
					Persons2::PlayerGhostAC->vel
					);
//DeadCode AMM 24Nov98 				AirStrucPtr p=(AirStrucPtr)entry;
//DeadCode AMM 24Nov98 				if (p->waypoint)
//DeadCode AMM 24Nov98 				{
//DeadCode AMM 24Nov98 					fprintf(fp,"WP X=%d Y=%d Z=%d\n",
//DeadCode AMM 24Nov98 						p->waypoint->World.X,
//DeadCode AMM 24Nov98 						p->waypoint->World.Y,
//DeadCode AMM 24Nov98 						p->waypoint->World.Z
//DeadCode AMM 24Nov98 						);
//DeadCode AMM 24Nov98 				}
//DeadCode AMM 24Nov98 				else
//DeadCode AMM 24Nov98 					fprintf(fp,"NO WP\n");
//DeadCode AMM 24Nov98 
//DeadCode AMM 24Nov98 				if (p->fly.leadflight)
//DeadCode AMM 24Nov98 				{
//DeadCode AMM 24Nov98 					if (p->fly.leadflight->waypoint)
//DeadCode AMM 24Nov98 					{
//DeadCode AMM 24Nov98 						fprintf(fp,"LWP X=%d Y=%d Z=%d\n",
//DeadCode AMM 24Nov98 							p->fly.leadflight->waypoint->World.X,
//DeadCode AMM 24Nov98 							p->fly.leadflight->waypoint->World.Y,
//DeadCode AMM 24Nov98 							p->fly.leadflight->waypoint->World.Z
//DeadCode AMM 24Nov98 							);
//DeadCode AMM 24Nov98 					}
//DeadCode AMM 24Nov98 					else
//DeadCode AMM 24Nov98 						fprintf(fp,"NO LWP\n");
//DeadCode AMM 24Nov98 				}
//DeadCode AMM 24Nov98 				else
//DeadCode AMM 24Nov98 					fprintf(fp,"NO LWP\n");
			}
#endif

// want to update GoodAbsPos with predicted movement

//DeadCode AMM 24Mar99 			AirStrucPtr gac=Persons2::PlayerGhostAC;
//DeadCode AMM 24Mar99 	FILE* fp=fopen("pred.txt","at");
//DeadCode AMM 24Mar99 	fprintf(fp,"movecode predict\n");
//DeadCode AMM 24Mar99 	fprintf(fp,"b4: X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d cp=%d\n",gac->World.X,gac->World.Y,gac->World.Z,
//DeadCode AMM 24Mar99 		gac->hdg.a,gac->pitch.a,gac->roll.a,gac->vel,gac->fly.cpitch.a);
//DeadCode AMM 25Mar99 	FILE* fp=fopen("prednum.txt","at");
//DeadCode AMM 25Mar99 	fprintf(fp,"%d: MovePred\n",_DPlay.FrameCount);
//DeadCode AMM 25Mar99 	fclose(fp);
			_DPlay.AddDeltas(Persons2::PlayerGhostAC,TRUE);
			_DPlay.PredictMove(Persons2::PlayerGhostAC);
			_DPlay.AddDeltas(Persons2::PlayerGhostAC,FALSE);
//DeadCode AMM 24Mar99 	fprintf(fp,"AF: X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d cp=%d\n",gac->World.X,gac->World.Y,gac->World.Z,
//DeadCode AMM 24Mar99 		gac->hdg.a,gac->pitch.a,gac->roll.a,gac->vel,gac->fly.cpitch.a);
//DeadCode AMM 24Mar99 	fclose(fp);

		}
		else
		{
#ifdef DEBUGMOVE
				if ((_Replay.Record || _Replay.Playback || _DPlay.Implemented) && entry->Status.size==AIRSTRUCSIZE )
				{
					ULong m=entry->movecode;
					ULong man=((AirStrucPtr)entry)->ai.manoeuvre;
					UWord uid=entry->uniqueID.count;
					UByte inform=((AirStrucPtr)entry)->information;

//DeadCode AMM 12May99 					fprintf(fp,"ID=%d inform=%d move=%d man=%d X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d\n",
					fprintf(fp,"ID=%x X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d inform=%d move=%d man=%d\n",
							uid,
//DeadCode AMM 12May99 							inform,
//DeadCode AMM 12May99 							m,
//DeadCode AMM 12May99 							man,
							entry->World.X,
							entry->World.Y,
							entry->World.Z,
							entry->hdg.a,
							entry->pitch.a,
							entry->roll.a,
//DeadCode AMM 12May99 							entry->vel
							entry->vel,
							inform,
							m,
							man
							);


//DeadCode AMM 24Nov98 				AirStrucPtr p=(AirStrucPtr)entry;
//DeadCode AMM 24Nov98 				if (p->waypoint)
//DeadCode AMM 24Nov98 				{
//DeadCode AMM 24Nov98 					fprintf(fp,"WP X=%d Y=%d Z=%d\n",
//DeadCode AMM 24Nov98 						p->waypoint->World.X,
//DeadCode AMM 24Nov98 						p->waypoint->World.Y,
//DeadCode AMM 24Nov98 						p->waypoint->World.Z
//DeadCode AMM 24Nov98 						);
//DeadCode AMM 24Nov98 				}
//DeadCode AMM 24Nov98 				else
//DeadCode AMM 24Nov98 					fprintf(fp,"NO WP\n");
//DeadCode AMM 24Nov98 
//DeadCode AMM 24Nov98 				if (p->fly.leadflight)
//DeadCode AMM 24Nov98 				{
//DeadCode AMM 24Nov98 					if (p->fly.leadflight->waypoint)
//DeadCode AMM 24Nov98 					{
//DeadCode AMM 24Nov98 						fprintf(fp,"LWP X=%d Y=%d Z=%d\n",
//DeadCode AMM 24Nov98 							p->fly.leadflight->waypoint->World.X,
//DeadCode AMM 24Nov98 							p->fly.leadflight->waypoint->World.Y,
//DeadCode AMM 24Nov98 							p->fly.leadflight->waypoint->World.Z
//DeadCode AMM 24Nov98 							);
//DeadCode AMM 24Nov98 					}
//DeadCode AMM 24Nov98 					else
//DeadCode AMM 24Nov98 						fprintf(fp,"NO LWP\n");
//DeadCode AMM 24Nov98 				}
//DeadCode AMM 24Nov98 				else
//DeadCode AMM 24Nov98 					fprintf(fp,"NO LWP\n");
			}

#endif
  			if (entry->uniqueID.commsmove)
 			{
				if (entry->shape!=EMPTY)
				{
// AC with empty shape are not in world, so dont move them

					if (!mobileitem::currworld->vp->Accel())
					{
// not in accel predict 

						_DPlay.PredictMove((AirStrucPtr)entry);
					}
					else
					{
// in accel need to move as no delta packets will arrive

						entry->movecode=AUTO_COMMSACCEL;
						MoveItem(entry,world);
					}

// update model pos.Y so that ac leaves behind contrails?

					if (((AirStrucPtr)entry)->fly.pModel)
						((AirStrucPtr)entry)->fly.pModel->Pos.y=((AirStrucPtr)entry)->World.Y;
				}
			}
			else
			{
				ANGLES currhdg=entry->hdg;						//AMM 31Jul98

				MoveItem(entry,world);

				if (entry->uniqueID.changed)					//AMM 31Jul98
				{												//AMM 31Jul98
					if (entry->Status.size==AirStrucSize)		//AMM 31Jul98
					{											//AMM 31Jul98
						((AirStrucPtr)(entry))->fly.dhdg= (SWord)(entry->hdg - currhdg);			//AMM 31Jul98
					}											//AMM 31Jul98
				}												//AMM 31Jul98
			}
		}
#ifndef	NDEBUG
		if (!(entry->uniqueID.changed)						//AMM 31Jul98
			&& oldsector!=0xffff
			&& (oldsector!=world.GetSector(*entry)))				//AMM 31Jul98

		{
#ifdef __WATCOMC__
				INT3();
#endif
#ifdef __MSVC__
				INT3;
#endif
		}
#endif
		if (entry->uniqueID.changed && oldsector!=0xFFFF)				  //JIM 17/02/99
		{
			UWord	newsector=	world.GetSector(*entry);
			if (newsector!=oldsector)
			{
				world.RemoveFromSector(entry,oldsector);
				world.AddToWorld(entry);
			}
			entry->uniqueID.changed = FALSE;						//RDH 26Jun96
		}
		else
			oldsector=oldsector;
		entry=next;												//RDH 23Feb96
	}
#ifdef DEBUGMOVE
	if (_Replay.Record || _Replay.Playback || _DPlay.Implemented)
	{
		fprintf(fp,"\n");
		fclose(fp);
	}
#endif
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveList
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#ifndef	NDEBUG
	  int	Count_SetFlightParams=0;
#endif
void mobileitem::MoveItem(MobileItemPtr entry,WorldStuff& world)
{
//DEADCODE DAW 14/06/99 #ifndef	NDEBUG
//DEADCODE DAW 14/06/99 	Count_SetFlightParams=0;
//DEADCODE DAW 14/06/99 #endif
/*

	#ifndef NDEBUG
	if (entry->Status.size==AIRSTRUCSIZE)
	{
		AirStrucPtr currac = (AirStrucPtr)entry;
		MODEL& MOD = *currac->fly.pModel;

		if((!currworld->vp) || (!currworld->vp->Accel()))
			if(!(MOD.FrameCount & EVERY256cs) && (!currac->Status.deadtime) && (currac->fly.callnum <= 25))
			{
				if(currac->PlayerInGroup())
					PrintVar(0, currac->fly.callnum, "%.0f ", FP(currac->ai.combatskill));
				else if(currac->vel)
				{
					if(currac->classtype->visible == F86)
						PrintVar(10, currac->fly.callnum, "F86 %.0f ", FP(currac->ai.combatskill));

					if(currac->classtype->visible == F84)
						PrintVar(20, currac->fly.callnum, "F84 %.0f ", FP(currac->ai.combatskill));

					if(currac->classtype->visible == F80)
						PrintVar(30, currac->fly.callnum, "F80 %.0f ", FP(currac->ai.combatskill));

					if(currac->classtype->visible == F51)
						PrintVar(40, currac->fly.callnum, "F51 %.0f ", FP(currac->ai.combatskill));

					if(currac->classtype->visible == B26)
						PrintVar(50, currac->fly.callnum, "B26 %.0f ", FP(currac->ai.combatskill));

					if(currac->classtype->visible == B29)
						PrintVar(60, currac->fly.callnum, "B29 %.0f ", FP(currac->ai.combatskill));

					if(currac->classtype->visible == MIG15)
						PrintVar(70, currac->fly.callnum, "M15 %.0f ", FP(currac->ai.combatskill));

					if(currac->classtype->visible == CMIG15)
						PrintVar(70, currac->fly.callnum, "M15 %.0f ", FP(currac->ai.combatskill));
				}
			}

		}
*/
/*		if( ((!currworld->vp) || (!currworld->vp->Accel())) && (currac->fly.callnum <= 8))
			if(!(MOD.FrameCount & EVERY8cs) || (currac->Status.deadtime))
				if((currac->PlayerInGroup()) || (	(currac->ai.unfriendly)
												 && (currac->ai.unfriendly->Status.size == AIRSTRUCSIZE)
												 && (AirStrucPtr(currac->ai.unfriendly)->PlayerInGroup())) )
//DEADCODE RDH 23/06/99 		if  (		(		(currac->fly.callname == 3)		//hot shot f86 = 3
//DEADCODE RDH 23/06/99 						||	(currac->fly.callname == 5)		//hot shot mig		
//DEADCODE RDH 23/06/99 					)
//DEADCODE RDH 23/06/99 					&&	(currac->fly.callnum <= 8)
//DEADCODE RDH 23/06/99 			)
		{

			if (currac->ai.unfriendly)
				currac->InterceptandRange (&currac->ai.unfriendly->World);						  //RDH 13/06/99
			else
				Range = 0;
			int grouppos = currac->fly.callnum;
			int line = grouppos + 1;
			if((MOD.Type == AT_MIG15) || (MOD.Type == AT_MIG15BIS) || (MOD.Type == AT_YAK9))
				line += 9;

			if((MOD.Type == AT_MIG15) || (MOD.Type == AT_MIG15BIS) || (MOD.Type == AT_YAK9))
				PrintVar(0, line, "RED %.0f      ", FP(grouppos));
			else
				PrintVar(0, line, "BLU %.0f      ", FP(grouppos));

			if (currac->Status.deadtime )
			{
				PrintString(32, line, "DEAD");

			}else
			{

				if(currac->ai.unfriendly) PrintVar(77, line, "v%.0f", FP(AirStrucPtr(currac->ai.unfriendly)->fly.callnum));
				if(currac->ai.attacker) 
					PrintVar(73, line, "a%.0f", FP(AirStrucPtr(currac->ai.attacker)->fly.callnum));
				else
					PrintVar(73, line, "a%.0f", FP(0));

				PrintVar(10, line, "Vel %.1f      ", FP(currac->vel / 10.0));
				PrintVar(20, line, "Range %.0f      ", FP(currac->Range / 100.0));
				
				if(currac->ai.simpleacm) PrintString(32, line, "simple    ");
				else			 PrintString(32, line, "COMPLEX   ");

				switch (currac->movecode)
				{
					case AUTO_TRACKINGBOGIE:	{ PrintString(40, line, "Track Bogie						");    break; }
					case AUTO_PRECOMBAT:	{ PrintString(40, line, "Precombat						");    break; }
					case AUTO_COMBAT:
					{
						switch (currac->ai.manoeuvre)
						{
							case MANOEUVRE_SELECT:						{ PrintString(40, line, "SELECT						");    break; }
							case MANOEUVRE_LOOKROUND:					{ PrintString(40, line, "LOOKROUND					");    break; }
							case MANOEUVRE_WELDEDWINGMAN:				{ PrintString(40, line, "WELDEDWINGMAN				");    break; }
							case MANOEUVRE_BAILOUT:						{ PrintString(40, line, "BAILOUT					");    break; }
							case MANOEUVRE_TOPCOVER:					{ PrintString(40, line, "TOPCOVER					");    break; }
							case MANOEUVRE_LINEABREAST:					{ PrintString(40, line, "LINEABREAST				");    break; }
							case MANOEUVRE_SCATTER:						{ PrintString(40, line, "SCATTER					");    break; }
							case MANOEUVRE_PINCER:						{ PrintString(40, line, "PINCER						");    break; }
							case MANOEUVRE_MULTIWAVE:					{ PrintString(40, line, "MULTIWAVE					");    break; }
							case MANOEUVRE_DIVEANDZOOM:					{ PrintString(40, line, "DIVEANDZOOM				");    break; }
							case MANOEUVRE_LEADPURSUIT:					{ PrintString(40, line, "LEADPURSUIT				");    break; }
							case MANOEUVRE_LAGPURSUIT:					{ PrintString(40, line, "LAGPURSUIT					");    break; }
							case MANOEUVRE_CIRCUMVENT:					{ PrintString(40, line, "CIRCUMVENT					");    break; }
							case MANOEUVRE_ROUNDABOUT:					{ PrintString(40, line, "ROUNDABOUT					");    break; }
							case MANOEUVRE_SPLITMANOEUVRE:				{ PrintString(40, line, "SPLITMANOEUVRE				");    break; }
							case MANOEUVRE_HEADON:						{ PrintString(40, line, "HEADON						");    break; }
							case MANOEUVRE_LINEASTERN:					{ PrintString(40, line, "LINEASTERN					");    break; }
							case MANOEUVRE_BARRELROLLATTACK:			{ PrintString(40, line, "BARRELROLLATTACK			");    break; }
							case MANOEUVRE_SCISSORS:					{ PrintString(40, line, "SCISSORS					");    break; }
							case MANOEUVRE_MILDSCISSORS:				{ PrintString(40, line, "MILDSCISSORS				");    break; }
							case MANOEUVRE_TURNINGFIGHT:				{ PrintString(40, line, "TURNINGFIGHT				");    break; }
							case MANOEUVRE_SPLITS:						{ PrintString(40, line, "SPLITS						");    break; }
							case MANOEUVRE_ZOOMANDDROP:					{ PrintString(40, line, "ZOOMANDDROP				");    break; }
							case MANOEUVRE_STRAIGHTANDLEVEL:			{ PrintString(40, line, "STRAIGHTANDLEVEL			");    break; }
							case MANOEUVRE_SPINOUT:						{ PrintString(40, line, "SPINOUT					");    break; }
							case MANOEUVRE_DIVEFORHOME:					{ PrintString(40, line, "DIVEFORHOME				");    break; }
							case MANOEUVRE_GOHOME:						{ PrintString(40, line, "GOHOME						");    break; }
							case MANOEUVRE_MAKEFORFRIENDLY:				{ PrintString(40, line, "MAKEFORFRIENDLY			");    break; }
							case MANOEUVRE_MOVEAWAY:					{ PrintString(40, line, "MOVEAWAY					");    break; }
							case MANOEUVRE_ACCIDENTALSPINOUT:			{ PrintString(40, line, "ACCIDENTALSPINOUT			");    break; }
							case MANOEUVRE_VERTICALLOOP:				{ PrintString(40, line, "VERTICALLOOP				");    break; }
							case MANOEUVRE_IMMELMANNTURN:				{ PrintString(40, line, "IMMELMANNTURN				");    break; }
							case MANOEUVRE_HEADONOFFSET:				{ PrintString(40, line, "HEADONOFFSET				");    break; }
							case MANOEUVRE_IMMELMANN:					{ PrintString(40, line, "IMMELMANN					");    break; }
							case MANOEUVRE_STAYWITHPREY:				{ PrintString(40, line, "STAYWITHPREY				");    break; }
							case MANOEUVRE_CLIMBFORHOME:				{ PrintString(40, line, "CLIMBFORHOME				");    break; }
							case MANOEUVRE_STRAIGHTDIVE:				{ PrintString(40, line, "STRAIGHTDIVE				");    break; }
							case MANOEUVRE_STANDONTAIL:					{ PrintString(40, line, "STANDONTAIL				");    break; }
							case MANOEUVRE_SHOOTTOFRIGHTEN:				{ PrintString(40, line, "SHOOTTOFRIGHTEN			");    break; }
							case MANOEUVRE_SHOOTTOOEARLY:				{ PrintString(40, line, "SHOOTTOOEARLY				");    break; }
							case MANOEUVRE_GAINHEIGHT:					{ PrintString(40, line, "GAINHEIGHT					");    break; }
							case MANOEUVRE_LAGROLL:						{ PrintString(40, line, "LAGROLL					");    break; }
							case MANOEUVRE_EXTENSION:					{ PrintString(40, line, "EXTENSION					");    break; }
							case MANOEUVRE_DIVINGSPIN:					{ PrintString(40, line, "DIVINGSPIN					");    break; }
							case MANOEUVRE_REVERSETURN:					{ PrintString(40, line, "REVERSETURN				");    break; }
							case MANOEUVRE_SELFASBAIT:					{ PrintString(40, line, "SELFASBAIT					");    break; }
							case MANOEUVRE_JINK:						{ PrintString(40, line, "JINK						");    break; }
							case MANOEUVRE_BREAKTURN:					{ PrintString(40, line, "BREAKTURN					");    break; }
							case MANOEUVRE_LAZYTURN:					{ PrintString(40, line, "LAZYTURN					");    break; }
							case MANOEUVRE_BREAK180:					{ PrintString(40, line, "BREAK180					");    break; }
							case MANOEUVRE_BREAKLOW:					{ PrintString(40, line, "BREAKLOW					");    break; }
							case MANOEUVRE_BREAKHIGH:					{ PrintString(40, line, "BREAKHIGH					");    break; }
							case MANOEUVRE_BREAK90:						{ PrintString(40, line, "BREAK90					");    break; }
							case MANOEUVRE_HIGBARRELROLL:				{ PrintString(40, line, "HIGBARRELROLL				");    break; }
							case MANOEUVRE_PANICTURN:					{ PrintString(40, line, "PANICTURN					");    break; }
							case MANOEUVRE_UNBALANCEDFLIGHT:			{ PrintString(40, line, "UNBALANCEDFLIGHT			");    break; }
							case MANOEUVRE_LOWALT:						{ PrintString(40, line, "LOWALT						");    break; }
							case MANOEUVRE_SNAPSHOT:					{ PrintString(40, line, "SNAPSHOT					");    break; }
							case MANOEUVRE_STAYONTAIL:					{ PrintString(40, line, "STAYONTAIL					");    break; }
							case MANOEUVRE_TURNTOHDGANDPITCH:			{ PrintString(40, line, "TURNTOHDGANDPITCH			");    break; }
							case MANOEUVRE_HOTSIDELAGPURSUITFIGHT:		{ PrintString(40, line, "HOTSIDELAGPURSUITFIGHT		");    break; }
							case MANOEUVRE_SANDWICHMANOEUVRES:			{ PrintString(40, line, "SANDWICHMANOEUVRES			");    break; }
							case MANOEUVRE_SUSTAINEDTURN:				{ PrintString(40, line, "SUSTAINEDTURN				");    break; }
							case MANOEUVRE_HIGHYOYO:					{ PrintString(40, line, "HIGHYOYO					");    break; }
							case MANOEUVRE_ZOOM:						{ PrintString(40, line, "ZOOM						");    break; }
							case MANOEUVRE_LOWYOYO:						{ PrintString(40, line, "LOWYOYO					");    break; }
							case MANOEUVRE_INTERCEPTHIGH:				{ PrintString(40, line, "INTERCEPTHIGH				");    break; }
							case MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED:	{ PrintString(40, line, "CLIMBATSUSTAINEDTURNSPEED	");    break; }
							case MANOEUVRE_GAINSPEED:					{ PrintString(40, line, "GAINSPEED					");    break; }
							case MANOEUVRE_SPINRECOVERY:				{ PrintString(40, line, "SPINRECOVERY				");    break; }
						}
					}
				}

				if (currac->ai.unfriendly)
				{
					COORDS3D trg = currac->ai.unfriendly->World;
					COORDS3D my  = currac->World;
					FP fAttack = (trg.X - my.X) * currac->velx + (trg.Y - my.Y) * currac->vely + (trg.Z - my.Z) * currac->velz;
					fAttack *= 100.0 / FP(currac->vel * Range);

					PrintVar(59, line, "*%.0f ", fAttack);  
				}

				PrintVar(64, line, "f%.0f ", FP(currac->ai.combatskill));
				PrintVar(68, line, "m%.0f ", FP(currac->ai.morale));  
			}
		}
	}
#endif
*/
/* TEST CODE CSB 01/06/99 */
/* TEST CODE CSB 01/06/99 */
/* TEST CODE CSB 01/06/99 */

#ifndef	NDEBUG
	//Someone has set the movecode for a dead ac!!!
//DeadCode CSB 13/07/99		if (	(entry->movecode != AUTO_NOPPILOT)				//RJS 27Jun99
//DeadCode CSB 13/07/99			&&	(entry->shape == PDEATH)			)
//DeadCode CSB 13/07/99			INT3;
#endif



	switch (entry->movecode)
	{
	case AUTO_TRACKINGBOGIE:
		((AirStrucPtr) *entry)->TrackBogey();
		break;
	case AUTO_TRACKINGBANDIT:
		((AirStrucPtr) *entry)->TrackBandit();
		break;
	case AUTO_PRECOMBAT:
		((AirStrucPtr) *entry)->AutoPreCombat();
		break;
	case AUTO_FOLLOWWP:												  //RDH 13/06/99
	case AUTO_TELLLEADER:										//JIM 03Oct96
		((AirStrucPtr) *entry)->AutoFollowWp();
		break;
	case AUTO_FAC:
		((AirStrucPtr) *entry)->AutoFAC();
		break;
	case AUTO_CAS:
		((AirStrucPtr) *entry)->AutoCAS();
		break;
//rdh 5/1/99	case AUTO_TRAININGPREMERGE:									//RDH 09Sep96
//rdh 5/1/99		((AirStrucPtr) *entry)->AutoTrainingPreMerge();			//RDH 09Sep96
//rdh 5/1/99		break;
//rdh 5/1/99	case AUTO_TRAININGACM:										//RDH 09Sep96
//rdh 5/1/99		((AirStrucPtr) *entry)->AutoTrainingACM();				//RDH 09Sep96
//rdh 5/1/99		break;													//RDH 09Sep96
	case AUTO_CRASHROLL:										//RDH 12Sep96
		((AirStrucPtr) *entry)->AutoCrashRoll();						//RDH 12Sep96
		break;
	case AUTO_CRASHSKID:										//RDH 12Sep96
		((AirStrucPtr) *entry)->AutoCrashSkid();				//RDH 12Sep96
		break;
	case AUTO_TAKEOFF:
		((AirStrucPtr) *entry)->AutoTakeOff();
		break;
	case AUTO_COMBAT:
		((AirStrucPtr) *entry)->AirCombat();
		break;
	case AUTO_NOPPILOT:
//DeadCode AMM 01Dec98 		if (entry=Persons2::PlayerSeenAC)

		
//DEADCODE RDH 28/04/99 		if (entry->uniqueID.count>RedAcBAND && entry->uniqueID.count<BlueAcBANDEND)
//DEADCODE RDH 28/04/99 			UByteP(0xB0000)[2*entry->uniqueID.count&0xfff]='N';
//DeadCode JIM 28Apr99 			UByteP(0xB0000)[2*entry->uniqueID.count&0xfff]='N';

		if (entry==Persons2::PlayerSeenAC)						//AMM 01Dec98
		{
			_DPlay.ResurrectMe(Persons2::PlayerSeenAC,false);
		}
		break;
	case AUTO_WAIT4TIME:
		break;
	case GROUND_TAXI:
		((FormationItemPtr) *entry)->AutoTaxi();
//DEADCODE DAW 14/06/99 #ifndef	NDEBUG
//DEADCODE DAW 14/06/99 	Count_SetFlightParams++;
//DEADCODE DAW 14/06/99 #endif
		break;
	case GROUND_TOGLOBREF:
		((FormationItemPtr) *entry)->WaitToTaxi();
		break;
//	case AUTO_TAXI:
//		((AirStrucPtr) *entry)->AutoTaxi();
//		break;
	case AUTO_SPIRAL2GROUND:
		((AirStrucPtr) *entry)->AutoSpiral2Ground(world);		//PD 01May96
		break;
	case AUTO_RESURRECT:
		((AirStrucPtr) *entry)->AutoResurrect((AirStrucPtr)entry);			//ARM 05Dec96
		break;
	case AUTO_DEATHSEQUENCE:
		((AirStrucPtr) *entry)->AutoDeathSequence();			//RDH 10Sep96
		break;
	case AUTO_LANDING:											//JIM 02Aug96
		((AirStrucPtr) *entry)->AutoLanding();				//JIM 02Aug96
		break;													//JIM 02Aug96
	case AUTO_STRAFFE:
		((AirStrucPtr) *entry)->AutoStraffe();				//JIM 02Aug96
		break;													//JIM 02Aug96
	case AUTO_BOMB:
		((AirStrucPtr) *entry)->AutoBomb();				//JIM 02Aug96
		break;													//JIM 02Aug96
	case AUTO_HITWATER:											//RJS 24Aug98
		((AirStrucPtr) *entry)->AutoCrashSkid();				//RJS 24Aug98
		break;													//RJS 24Aug98
	case AUTO_ACCELERATE:
		((AirStrucPtr) *entry)->AutoAccelerate();
		break;
	case AUTO_MISSIONDICETHROW:
		((AirStrucPtr) *entry)->MoveMissionDiceThrow();
		break;
	case AUTO_COMMSACCEL:
		((AirStrucPtr) *entry)->AutoCommsAccel();
		break;
	}
//DEADCODE DAW 14/06/99 #ifndef	NDEBUG
//DEADCODE DAW 14/06/99 	if(!Count_SetFlightParams)
//DEADCODE DAW 14/06/99 		int breakpoint = 0;//INT3;
//DEADCODE DAW 14/06/99 	Count_SetFlightParams=0;
//DEADCODE DAW 14/06/99 #endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveList
//LastModified:	PD 26Apr96
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
extern void	CheckE3();
void TransientItem::MoveTransList(TransientItemPtr entry,WorldStuff& world)
{
	currworld=&world;
	while (entry)
	{
		TransientItemPtr	next= entry->nexttrans;
		if (entry->movecode != MOBILE_NOPPILOT)						//RJS 09Dec98
		{
			UWord	oldsector=	world.GetSector(*entry);			//PD 25Jun96
	
			MoveTransItem(entry,world);
	
			if (oldsector!=world.GetSector(*entry))					//PD 25Jun96
			{
				world.RemoveFromSector((TransientItemPtr)entry,oldsector);
				world.AddToWorld((TransientItemPtr)entry);
			}
		}

		entry=next;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveList
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransientItem::MoveTransItem(TransientItemPtr entry,WorldStuff& world)//PD 26Apr96
{
#ifdef	DBGMEMTEST
#ifndef	NDEBUG
	TransientItem*	tmpentry = TransientList;
	while (tmpentry)
	{
		DbgMemTest2(tmpentry);
		tmpentry->Anim.MemTest();
		tmpentry = tmpentry->nexttrans;
	}
#endif
#endif
	switch (entry->movecode)// & AutoMoveCodeMask)					//RJS 24Nov97
	{
  	case	MOBILE_BURNIT:			Trans_Obj.MobileExplosion(entry,world);	break;//PD 26Apr96
 	case	MOBILE_CRATER:			Trans_Obj.MobileCrater(entry,world);	break;//PD 26Apr96
	case	MOBILE_BULLET:			Trans_Obj.MobileBullet(entry,world); 	break;//PD 26Apr96
	case    MOBILE_DEADACPART:		Trans_Obj.MobileDeadACPart(entry,world);break;//PD 26Apr96
	case 	MOBILE_SMOKETRAIL:		Trans_Obj.MobileSmokeTrail(entry,world);break;//PD 30Apr96
	case 	MOBILE_GANDF:			Trans_Obj.MobileGAndF(entry,world);		break;//PD 30Apr96
	case 	MOBILE_GROUNDEXP:		Trans_Obj.MobileGroundExp(entry,world);	break;//PD 01May96
	case 	MOBILE_DEBRIS:			Trans_Obj.MobileGroundDebris(entry,world);	break;//RJS 21Jun96
	case 	MOBILE_FIRE:			Trans_Obj.MobileFire(entry,world);	break;//RJS 01Jul96
	case 	MOBILE_TROOP:			Trans_Obj.MobileTroop(entry,world);	break;//RJS 01Jul96
	case 	MOBILE_PARACHUTE:		Trans_Obj.MobileParachute(entry,world);	break;//RJS 02Jul96
	case 	MOBILE_BARAGE:			Trans_Obj.MobileBarage(entry,world);	break;//RJS 02Jul96
	case 	MOBILE_DELEXP:			Trans_Obj.MobileDelayedExplosion(entry,world);	break;//RJS 02Jul96
	case 	MOBILE_FLAK:			Trans_Obj.MobileFlak(entry,world);	break;//RJS 02Jul96
	case 	MOBILE_RICOCHET:		Trans_Obj.MobileSparkTrail(entry,world);	break;//RJS 11Dec98
	case 	MOBILE_ATEAM:			Trans_Obj.MobileATeam(entry,world);	break;//RJS 10Jul96
	case 	MOBILE_BOMBDROP:		Trans_Obj.MobileBombDrop(entry,world);	break;//RJS 24Jul96
	case 	MOBILE_BIGEXP:			Trans_Obj.MobileBigExplosion(entry,world);	break;//RJS 12Aug96
	case 	MOBILE_MOVSMK:			Trans_Obj.MobileMovingSmoke(entry,world);	break;//RJS 02Sep96
	case 	MOBILE_STATIONARY:		Trans_Obj.MobileRicochetSmoke(entry,world);	break;//RJS 05Sep96
	case 	MOBILE_PUFFTRAVEL:		Trans_Obj.MobilePuffTravel(entry,world);	break;//RJS 13Oct96
	case 	MOBILE_BIRD:			Trans_Obj.MobileBird(entry,world);	break;//RJS 01Oct97
	case 	MOBILE_AMMODEATH:		Trans_Obj.MobileAmmoBoxes(entry,world);	break;//RJS 17Oct96
	case 	MOBILE_MUSHROOM:		Trans_Obj.MobileDummyBomb(entry,world);	break;//RJS 01Apr99
	case 	MOBILE_ROCKET:			Trans_Obj.MobileRocket(entry,world);	break;//RJS 04Jun97
	case 	MOBILE_CLONEGUN:		Trans_Obj.MobileCloneGun(entry,world);	break;//RJS 01Oct97
	case 	MOBILE_TIMEREXPLOSION:	Trans_Obj.MobileTimerExplosion(entry,world);	break;//RJS 22Jan98
	case 	MOBILE_NAPALM:			Trans_Obj.MobileNapalm(entry,world);	break;//RJS 22Jan98
	case 	MOBILE_DODAMAGE:		Trans_Obj.MobileDoDamage(entry,world);	break;//RJS 18Feb98
	case 	MOBILE_THUG:			Trans_Obj.MobileThuggery(entry,world);	break;//RJS 02Mar98
	case 	MOBILE_SMALLTHUG:		Trans_Obj.MobileSmallThug(entry,world);	break;//RJS 03Dec98
	case 	MOBILE_FUELDROP:		Trans_Obj.MobileFuelDrop(entry,world);	break;//RJS 28May98
	case 	MOBILE_DEADBRIDGE:		Trans_Obj.MobileDeadBridge(entry,world);	break;//RJS 30Oct98
	case 	MOBILE_COLLAPSE:		Trans_Obj.MobileCollapse(entry,world);	break;//RJS 18Nov98
	case 	MOBILE_CARPETBOMB:		Trans_Obj.MobileCarpetStrike(entry,world);	break;//RJS 31May99
	case 	MOBILE_SCALEFIST:		Trans_Obj.MobileScaleFist(entry,world);	break;//RJS 10Feb99
	case 	MOBILE_CANOPY:			Trans_Obj.MobileCanopy(entry,world);	break;//RJS 23Mar99
	case 	MOBILE_SINK:			Trans_Obj.MobileSink(entry,world);	break;//RJS 13May99
	case 	MOBILE_FLARE:			Trans_Obj.MobileFlare(entry,world);	break;//RJS 17May99

	}
#ifdef	DBGMEMTEST
#ifndef	NDEBUG
	tmpentry = TransientList;
	while (tmpentry)
	{
		DbgMemTest2(tmpentry);
		tmpentry->Anim.MemTest();
		tmpentry = tmpentry->nexttrans;
	}
#endif
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToList
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AddToList()
{
	nextmobile=ACList;
	ACList=*this;
	Art_Int.Add(this);
}

void mobileitem::AddToList()
{
	nextmobile=MobileList;
	MobileList=*this;
}

void TransientItem::AddToList()
{
	nexttrans=TransientList;
	TransientList=this;

// transients have ID equal to frame when launched. When a collision occurs the player 
// who processes the collision (owner of transient) send a message indicating that all
// transients with that frame number launched by him should be removed from the world

	this->uniqueID.count=(UniqueID)_DPlay.FrameCount;

// if this was launched by a transient then it inherits its parents flags

	if (Launcher->Status.size==TRANSIENTSIZE)
	{
		this->CollTestEnabled=((TransientItemPtr)Launcher)->CollTestEnabled;
		this->CollSuccessTrans=((TransientItemPtr)Launcher)->CollSuccessTrans;
	}
	else
	if ((Launcher==Persons2::PlayerSeenAC && !_Replay.Playback)
	|| (!_DPlay.Implemented && !_Replay.Record && !_Replay.Playback))
	{
// comms/replay off or player launched 
// if replay is turned on then these bullets will cause collisions to be recorded
// even though bullets are not seen on replay

		this->CollTestEnabled=TRUE;
		this->CollSuccessTrans=TRUE;
	}
	else if (!Launcher->uniqueID.commsmove && Launcher!=Persons2::PlayerSeenAC)
	{
// AI launched - want to test all AI bullets against all other AI planes and against player
// unless in playback, which is dealt with in PossTransmitColl

		this->CollTestEnabled=TRUE;

// if this hits player then collision will be sent if in record or comms. Other collisions do
// not need to be sent as they are AI against AI, or AI against comms player in which case
// that player will send his own collision info packets. 

// if this hits a player then check CommsOwner ID. If it is me then trasmit, otherwise ignore.

		this->CollSuccessTrans=FALSE;
	}
	else
	{
// comms received - dont test for anything just show them. All player collisions are dealt with
// via separate packet info

		this->CollTestEnabled=FALSE;
		this->CollSuccessTrans=FALSE;
	}

//DeadCode JIM 07Oct96  	TransientItemPtr temp = new TransientItem;
//DeadCode JIM 07Oct96   	if (TransientList==NULL)
//DeadCode JIM 07Oct96   	{
//DeadCode JIM 07Oct96   		TransientList=*this;
//DeadCode JIM 07Oct96   	}
//DeadCode JIM 07Oct96   	else
//DeadCode JIM 07Oct96   	{
//DeadCode JIM 07Oct96  		temp=TransientList;
//DeadCode JIM 07Oct96  		TransientList=*this;
//DeadCode JIM 07Oct96  
//DeadCode JIM 07Oct96  		TransientList->nexttrans=temp;
//DeadCode JIM 07Oct96   	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWpName
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
//TextSnip0	WayPoint::GetWpName()
//{
//	TextSnip0	retval=TEXT_NULL;
//	if (action!=wpacnoactionno)// && action<16)
//		retval=(_Text.ConvSnip0((TextList)LIST_WPACTIONS0,action));
//	elseif (target)
//		retval=(_Text.ConvSnip0(target->uniqueID.count));
//	if (retval==TEXT_NULL)
//		retval=(TEXT_WPACNOACTIONNO);
//	return(retval);
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExecuteWayPointAction
//Author		R. Hyde 
//Date			Mon 19 Feb 1996
//
//Description	Now pseudo recursive. Compiler should optimise to itteration.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	mobileitem::ExecuteWayPointAction ()

{
//TEMP	Persons_2.PossibleEvent(currworld,waypoint,this);
	AutoMoveCodeTypeSelect	oldmove=movecode;
	WayPointPtr	oldwp=waypoint;
//DeadCode JIM 18Oct96 	if (oldwp)
	//NULL WP MEANS START TO LAND...
	if (waypoint)
		DoWayPointAction(oldmove,oldwp,waypoint->action);
	else
		DoWayPointAction(oldmove,oldwp,wpforcelanding);
	if (Status.size==AIRSTRUCSIZE)
	{
		AirStrucPtr a=*this;
		if (	a->ai.eventlog->stage==EventLog::TAKEOFF
			&&	waypoint && waypoint->target
			)
		{
			if	(	waypoint->action==wpbombno
				||	waypoint->action==wpengagetargetno
				||	waypoint->action==wpdivebombstraffeno
//				||	waypoint->action==wpstraffeno
				||	waypoint->action==wpballoonbustno
				)
			{
//TEMP				Persons_2.AddMessage(UserMsg::SIGHTED,TEXT_OBJECTIVESIGHTED,waypoint->target);
				_Miles.SequenceAudible(FIL_MUSIC_OBJECTIVE_SIGHTED);
			}
		}
	}
}

void	mobileitem::DoWayPointAction (AutoMoveCodeTypeSelect	oldmove,WayPointPtr	oldwp,BFieldWaypointActions action)
{

	if (movecode==oldmove && waypoint==oldwp)
	{
		if (waypoint)
		{
			if (!waypoint->Status.deadtime && this==Manual_Pilot.ControlledAC2)
			{
//				UserMsg::Reason	r=UserMsg::PASSEDWP;
//DEADCODE JIM 25/03/99 				TextSnip0	t=TEXT_NULL;
//				t=waypoint->GetWpName();
//TEMP				Persons_2.AddMessage(r,t,*FindDesPos ());
//DeadCode RDH 15Oct96 				Persons_2.ClrMessage(UserMsg::COURSE);
			}
		}


		switch (action)
		{
		case	wpatakeoffno:
		case	wpacircleno:
		case	wptruckbridge:
		case	wptruckescort:
				NextWayPoint ();
		break;
//
//	PROPER WAYPOINT ACTIONS START HERE:
//	the ones above fall through to noaction
//
		case	wpacnoactionno:
				NextWayPoint ();
		break;

		case	wpdmbtrknoactno:
				NextWayPoint ();
				action=wpretrywp;
		break;

		case	wpballoonbustno:											//MS 18Jul96
		case	wpdivebombstraffeno:										//MS 18Jul96
//		case	wpstraffeno:												//MS 18Jul96
			StartStraffe();
		break;

		case	wpbombno:													//MS 18Jul96
		case	wpengagetargetno:
		case	wpattackconvoyno:
			StartBombing();
		break;

		case	wpreccyno:										//JIM 17Dec96
 		case	wpartspotno:									//JIM 17Dec96
				KillItNow();
		break;

		case	wpteleportnext:
			TeleportWayPoint();
		break;

		case	wpstoploopchkno :							//JIM 30Jul96
			action=EndLoopWayPoint();								//JIM 30Jul96
		break;												//JIM 30Jul96

		case	wpbreakloop :							//JIM 30Jul96 //JIM 19/03/99
		case	wpstartloopno:										  //JIM 19/03/99
			action=MidLoopWayPoint();								//JIM 30Jul96
		break;												//JIM 30Jul96
		
		case	wpforcebreakloop:
			ForceBreakLoopWayPoint();
		break;

		case	wpwaituntildeadno :							//JIM 30Jul96
			WaitDeadWayPoint();								//JIM 30Jul96
		break;												//JIM 02Aug96
		case	wpalandingno:								//JIM 02Aug96
			LandingWayPoint();								//JIM 02Aug96
		break;												//JIM 02Aug96
		case	wpdmbtrkstopno:
		case	wpstopno:									//RDH 17Oct96
			velx=vely=velz=0;
			movecode=AUTO_NOPPILOT;
		break;
		case wpforcelanding:
		{
			movecode = AUTO_LANDING;
			if (Anim!=NULL)
				SHAPE.NavigationLightsActive(this, TRUE);
			AirStrucPtr AC = *this;
			AC->ai.ManStep = 0;
			AC->SetManoeuvreTime(0);
			
			if(AC->formpos == 0)
			{
				AirStrucPtr ThePlayer = AC->PlayerInGroup();
				if((ThePlayer) && (AC != ThePlayer))
				{
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_STEER_RANGE, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER,
										AC->ai.homebase, AC));

			 		if(Save_Data.flightdifficulty [FD_WINDGUSTS])
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED_GUSTS, MSG_STATUSRESPONSE_DELAY_LP_RPT,
										VOICE_TOWER, NULL, AC));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED, MSG_STATUSRESPONSE_DELAY_LP_RPT,
										VOICE_TOWER, NULL, AC));
				}
			}
			break;
		}

		case	wp_start_cas:
			NextWayPoint();
			if (	(AirStrucPtr(*this)->duty&DUTYMASK)==DC_CAS 
				&& (AirStrucPtr(*this)->duty&ACTIONCODE)!=DA_CAP
				)
				AirStrucPtr(*this)->SetToCAS(true);
		break;

		case	wp_threat_combfriendly:
		case	wp_threat_engfriendly:
		case	wp_threat_firing:
		case	wp_threat_weapon:
		case	wp_threat_danger:
		case	wp_threat_engage:
		case	wp_threat_any:
			assert (Status.size==AIRSTRUCSIZE);
			AirStrucPtr(*this)->ai.threatlevel=tThreatLevel(action-wp_threat_combfriendly);
			NextWayPoint();
		break;


		case	wpretrywp:
		break;												//RDH 17Oct96
		}
	}

		if (Status.size>=FormationSize)							//JIM 04Aug96
		{	//find a child and recurse down it					//JIM 04Aug96
			FormationItemPtr	f=*this;						//JIM 04Aug96
			if (f->follower)									//JIM 04Aug96
			f->follower											//JIM 04Aug96
				->DoWayPointAction(oldmove,oldwp,action);				//JIM 04Aug96
			elseif (Status.size==AirStrucSize)					//JIM 04Aug96
				if (	f->leader								//JIM 04Aug96
					&& ((AirStrucPtr)*f->leader)->fly.nextflight)//JIM 04Aug96
					((AirStrucPtr)*f->leader)->fly.nextflight	//JIM 04Aug96
						->DoWayPointAction(oldmove,oldwp,action);		//JIM 04Aug96
				elseif (((AirStrucPtr)*this)->fly.nextflight)	//JIM 04Aug96
					((AirStrucPtr)*this)->fly.nextflight		//JIM 04Aug96
						->DoWayPointAction(oldmove,oldwp,action);		//JIM 04Aug96
		}														//JIM 04Aug96
		//else finished											//JIM 04Aug96

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckManualCourse
//Author		Jim Taylor
//Date			Sun 21 Jul 1996
//
//Description	
//				Basically does equivalents to auto movecode for player
//
//				Checks if manual is on course and has reached waypoints
//				Checks for all break off
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::CheckManualCourse()
{
	ANGLES	currintercept,originalintercept;
	SLong	range,dprange;
//DEADCODE MS 06/05/99 	//This code is called on Ghost, but need s to copy back any effects to Seen:
//DEADCODE MS 06/05/99 	Persons2::PlayerSeenAC->waypoint=waypoint;
//DEADCODE MS 06/05/99 	Persons2::PlayerSeenAC->leader=leader;
//DEADCODE MS 06/05/99 	Persons2::PlayerSeenAC->follower=follower;
//DEADCODE MS 06/05/99 	Persons2::PlayerSeenAC->fly.nextflight=fly.nextflight;
//DEADCODE MS 06/05/99 	Persons2::PlayerSeenAC->fly.leadflight=fly.leadflight;
//DEADCODE MS 06/05/99 


	COORDS3D* dp;
	if (Manual_Pilot.controlmode==Manual_Pilot.PILOTDEAD)
		return;
	if (movecode==AUTO_PRECOMBAT)
		if (ai.unfriendly==NULL)
			if (formpos)
			{
				InterceptandRange (dp=PositionWRTLeader ());
				range=Range;
				currintercept=originalintercept=HdgIntercept;
				dprange=0;
			}
			else
				movecode=AUTO_FOLLOWWP;
		else
		{

			dp=&ai.unfriendly->World;

			dprange=METRES500;
			InterceptandRange (dp);
			if (Range>dprange)
				InterceptandRange (dp=FindCombatPos());
			else
				currintercept=originalintercept=HdgIntercept;
			currintercept=originalintercept=HdgIntercept;
			range=Range;
		}
	elseif (movecode==AUTO_COMBAT)
	{
		if (formpos)
			if (fly.leadflight->movecode!=AUTO_COMBAT)
			{
				movecode=(AutoMoveCodeTypeSelect)fly.leadflight->movecode;
			}
			elseif (	fly.leadflight->ai.manoeuvre==MANOEUVRE_TOPCOVER
					&&	ai.manoeuvre!=MANOEUVRE_TOPCOVER
					)
			{
//TEMP			 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_LEADERGOINGHOME,fly.leadflight);
				ai.manoeuvre=MANOEUVRE_TOPCOVER;
				if (	ai.unfriendly
					&&	ai.unfriendly->Status.size==AIRSTRUCSIZE
					&&	((AirStrucPtr)ai.unfriendly)->ai.attacker==this
					)
					((AirStrucPtr)ai.unfriendly)->ai.attacker=NULL;
				ai.unfriendly=NULL;
			}

		if (ai.unfriendly)
		{
			InterceptandRange (dp=&ai.unfriendly->World);
			range=Range;
			currintercept=originalintercept=HdgIntercept;
			dprange=METRES100;
		}
		else
		{
			if (	//ai.manoeuvre==MANOEUVRE_TOPCOVER &&			//JIM 03Dec96
				formpos==0)
				if (AllOnTopCover())
				{
					Art_Int.AllBreakOff(this);									//JIM 16Jul96
//TEMP				 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_SQUADRONREGROUPED,NULL);
				}
				elseif (AllButLdrNotOnCombat ())
				{
					ai.manoeuvre=MANOEUVRE_TOPCOVER;
				}

			return;
		}
	}
	elseif (movecode==AUTO_BOMB || movecode==AUTO_CAS)
	{
		if (!ai.unfriendly)
		{
			if (movecode==AUTO_BOMB)
				movecode=AUTO_FOLLOWWP;
		}
		else
		{
			if (!SelectedElement(ai.unfriendly,ai.manoeuvre.value))
			{
				int newelt;
				ItemPtr trg=SelectTarget(ai.unfriendly,&newelt);
				if (!SelectedElement(trg,newelt))
					trg=NULL;
				OverLay.DecisionMessage(FACMsg,FAC_BombsAway,this,trg,this,FALSE);	//RJS 09Jun99
			}
		}
		OverLay.CancelAccel();
		range = 1;		//CSB 13/07/99	Force it to fail later test
		dprange = 0;	//CSB 13/07/99	
	}
	elseif (!FlyEscortTo())
	{	//followwp
		InterceptandRange (dp=FindDesPos ());
		dprange=desposrange+MILES01;	//make it easy for player
		if (PitchIntercept>ANGLES_85Deg)
			Range=0;
		if (waypoint && !formpos && fly.leadflight && fly.leadflight->waypoint==waypoint->next)
			dprange+=METRES10KM;			//escortee just gone through. See AutoFollowWP
		originalintercept=currintercept=HdgIntercept;
		range=Range;
		WayPointPtr	wp=fly.backupWP;
		if (wp==NULL)
			wp=waypoint;
		if (movecode==AUTO_TAXI && vel>5*60)					//RDH 11Dec96
			movecode=AUTO_FOLLOWWP;								//RDH 11Dec96
//TempCode JIM 14Nov96 		if (wp && wp->prev)
//TempCode JIM 14Nov96 		{
//TempCode JIM 14Nov96 			InterceptandRange(wp->prev->FindDesPos());
//TempCode JIM 14Nov96 			originalintercept=(ANGLES)(HdgIntercept+ANGLES_180Deg);	//still have old intercept
//TempCode JIM 14Nov96 		}
//TempCode JIM 14Nov96 //complicates dp calculation

	}
	else if(!Status.deadtime)	//CSB 09/06/99	
	{	//followwp wing
		InterceptandRange (dp=PositionWRTLeader ());
		range=Range;
		currintercept=originalintercept=HdgIntercept;
		dprange=0;
		if (range>METRES100)
		{
			information=FALSE;
			AirStrucPtr leadac=Leader();
			if (!leadac)
				leadac=fly.leadflight;
			leadac->slowdownleader=TRUE;
			if (fly.leadflight)
				fly.leadflight->slowdownleader=TRUE;
//DeadCode CSB 07/06/99				int r=range/METRES250;	  //7 bits=12800 metres
			int r = (int)FSqrt(range/METRES500);				//CSB 07/06/99	
			if (ai.desiredrange)									  //JIM 18/05/99
				if (r>ai.desiredrange)								  //JIM 18/05/99
					if (r<8)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLOSER, (MsgType)(MSG_FORMATIONFLYING+MSG_REPEAT), leadac, NULL, this));		//CSB 26/05/99	
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GETBACK, (MsgType)(MSG_FORMATIONFLYING+MSG_REPEAT), leadac, NULL, this));		//CSB 26/05/99	
			ai.desiredrange=r;										  //JIM 18/05/99

		}
		else
			information=TRUE;

	}

	//now what?
	if (range<dprange)											//JIM 20Aug96
	{	//reached waypoint near enough							//JIM 20Aug96
//DeadCode JIM 03Dec96 		if (waypoint && movecode<AUTO_PRECOMBAT)				//JIM 20Aug96
		if (movecode<AUTO_PRECOMBAT)				//JIM 20Aug96
		{														//JIM 20Aug96
//			UserMsg::Reason	r=UserMsg::PASSEDWP;
			//tests for special waypoints
//DeadCode AMM 10Jun98 			if (!waypoint || waypoint->uniqueID.deaded)			//RJS 27Feb98
//DeadCode AMM 30Nov98 			if (!waypoint || waypoint->uniqueID.commsmove)		//AMM 10Jun98
			if (!waypoint || waypoint->Status.deaded)			//AMM 30Nov98
			{
				ExecuteWayPointAction();
			}
			else
			{
//DeadCode JIM 06Dec96 				TextSnip0	t=waypoint->GetWpName();
				ExecuteWayPointAction();
//DeadCode JIM 06Dec96 				Persons_2.AddMessage(r,t,*FindDesPos ());
//DeadCode RDH 15Oct96 				Persons_2.ClrMessage(UserMsg::COURSE);
			}
		}
		elseif (movecode==AUTO_PRECOMBAT)
		{	//switch to engage
			Art_Int.AllEngage(this);
		}
	}
	elseif (range>METRES500+dprange)
	{
		despos=*dp;
		if (Math_Lib.AbsSign((SWord)(currintercept-hdg))>ANGLES_30Deg)
//hard:   if (Math_lib.AbsSign(currintercept-originalintercept)>ANGLES_30Deg)
//TEMP			Persons_2.AddMessage(UserMsg::COURSE,TEXT_NULL,despos);
			;
	}
	if (movecode != AUTO_COMBAT)
	{//don't want this message when in combat						  //RDH 30/04/99
		ItemBasePtr corner=Persons2::ConvertPtrUID(UID_StNamsanni);
		if (corner->World.X>World.X)
		{	//sinuiju corner
			if ((corner->World.X-World.X)>(corner->World.Z-World.Z))
			{
				AirStrucPtr buddy=FindBuddy();
				if (buddy)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CROSSRIVER, MSG_CROSSRIVER, buddy, NULL, this));
			}
		}
		else
		{	//north korea
			if (corner->World.Z<World.Z)
			{
				AirStrucPtr buddy=FindBuddy();
				if (buddy)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CROSSRIVER, MSG_CROSSRIVER, buddy, NULL, this));
			}
		}
	}
}

