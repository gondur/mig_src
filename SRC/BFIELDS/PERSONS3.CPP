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
//	Persons3.cpp
//	This converts the complex info_ objects into simpler
//	item and airstruc elements
//
//
	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
	#include	"dosdefs.h"
	#include	"myerror.h"						   
	#include	"worldinc.h"
	#include	"bfnumber.h"
	#include	"bfcommon.h"
	#include	"bfnumber.h"	//intensional double include
	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
	#include	"3dcode.h"
	#include	"flyinit.h"
	#include	"viewsel.h"
	#include	"comms.h"
	#include	"replay.h"
#include "contlist.h"
#include	"globrefs.h"
//DeadCode JIM 28Mar96 extern	PlaneType&	camel;										//RDH 23Feb96
//Old_Code PD 27Aug96  	MAKEFIELD	(ShapeNum,ShapeNumMIN,ShapeNumMAX);
//	extern	ULong	GR_FriendlyScoutType00;
//	extern	ULong	GR_GlobalSkillMin;
//	extern	ULong	GR_GlobalSkillMax;
//	extern	ULong	GR_CWP,GR_CPP;
//	extern	ULong	GR_EnemyScoutSquad,
//					GR_FriendlyScoutSquad,
//					GR_EnemyChargeSquad,
//					GR_FriendlyChargeSquad,
//					GR_Pack_PlayerSquad,
//					GR_Pack_PlayerPos

					
	extern	ULong	GR_Pack_Sq_Used[SQ_R_NONFLYABLE+1];	//inc Yak
	AirStrucPtr	Persons3::migsq[2];
//Nationality		defaultside=NAT_GREEN;

//ItemBasePtr		*Persons2::pItem;

//DEADCODE JIM 25/03/99 char	CustomMissionDesc[300];
//DEADCODE JIM 25/03/99 char	CustomMissionNews[300];
//DEADCODE JIM 25/03/99 char	CustomMissionTitle[100];
//DEADCODE JIM 25/03/99 MissionType	CustomMission;
//DEADCODE JIM 25/03/99 

#define EvalOrDefault(field,type,expr,defaultv)				\
		{													\
			int v1;											\
			if ((v1=I.expr.Evaluate())==ENABLE_COMPLEX_VAL)	\
				field=defaultv;								\
			else			   								\
				field=type(v1);								\
		}
#define FormOrDefault(field,type,expr,defaultv)				\
		{													\
			int v1;											\
			if ((v1=I.expr.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)	\
				field=defaultv;								\
			else			   								\
				field=type(v1);								\
		}


CON	Persons3::Persons3(WorldStuff* world,ViewPoint* vp,Inst3d* inst):
	Persons2(world,vp)
{
	inst3d=inst;
	gotgrpnum=1;
	migsq[0]=migsq[1]=NULL;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	THESE make_ routines make the actual items in the world
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//Pseudocode time:
//
//Switch (takeoffstate)
//TOS_SIMPLE:
//Simple scenario - works as before
//TOS_INAIR:
//{		//place in approximate location
//		if (can't make ETA to first waypoint + 1 min for takeoff seq)
//			place proportionally on route to first waypoint 
//		else
//		if (is wave leader)
//			try each waypoint in turn until time used up
//			if past engage waypoint
//				dice roll encounter with target
//			if past last waypoint, 
//				place 1 mile north of last waypoint
//			else
//				place proportionally between waypoints
//		else
//			place in formation with leader
//}
//TOS_HOLDING:
//{		//place as far back as possible
//		calc position as TAXI2..TAXI1 * 40m *(20-timemod/15)
//		place on pause until modulo time		(PHASE 0 then PHASE 2, turn, PHASE 5)
//}
//TOS_TAXIING:
//{		//place closer
//		calc position as TAXI1..TAXI2 * 40m *((time-GR)/15)
//		place on "immediate" pause - delayed until player ready	(PHASE 1 then PHASE 2, turn, PHASE 5)
//}
//TOS_TAKENOFF:
//{		//place close to airfield
//		place in formation at altitude between RUNWAY1..RUNWAY0 *100m*(GR-time)/15)
//			pointing towards first waypoint	
//}
//TOS_TAKINGOFF:
//{		//place some just in front 
//		place (GR-time)/15 flights in formation at altitude on RUNWAY1
//			pointing towards first waypoint
//		place 1 flight on TAKEOFFL/TAKEOFFW - should be player's flight
//		place other flights at TAXI0..TAXI1 * 40m *(time-GR)/15 - delay UPR (PHASE 3, PHASE 4 then move to position PHASE 6 common)
//}

//Phases:
//TOS_HOLDING
//0		Hold until time
//TOS_TAXIING
//1		Hold until player gone
//2		Move towards TAXI1 at 40m every 15 seconds On reaching TAXI1, phase 5
//TOS_NEXTFLIGHTS
//3		Hold until player gone
//4		Move towards TAXI0 at 40m every 15 seconds. On reaching TAXI0, phase 6 
//
//5		Move all way to TAXI0 over ?15? seconds. On time up, phase 6
//
//6		Hold for 5 seconds
//		Within 5 seconds
//			1st Elt moves forward to LAUNCHL
//			2nd Elt moves forward to LAUNCHW
//7		Within 5 seconds
//			Both turn and move forward until leader at RUNWAY0 then PHASE 9
//TOS_RUNWAY
//8		Hold until player gone
//9		Take off acceleration up runway towards RUNWAY1
//
//10	Climb straight forward for fixed time
//
//11	Slow turn in formation
////////////////////////////////////////////////////////////////////////
//
// Function:    setpositionMIG
// Date:        21/01/99
// Author:      JIM
//
// Description: LIMITED TO RANGES LESS THAN 640M
//
////////////////////////////////////////////////////////////////////////
inline void	ModifyPosn(Coords3D& c,int range,ANGLES h,ANGLES p)
{
 		SWord	sin_theta,cos_theta;
		SWord	sin_hdg, cos_hdg;

		Math_Lib.high_sin_cos (p,sin_theta,cos_theta);

		int vely = MULSHSIN(range,sin_theta,ANGLES_SHIFT);

		int velhori = MULSHSIN(range,cos_theta,ANGLES_SHIFT);


		Math_Lib.high_sin_cos (h, sin_hdg, cos_hdg);
		int velx =  MULSHSIN(velhori,sin_hdg,ANGLES_SHIFT);
		int velz =   MULSHSIN(velhori,cos_hdg,ANGLES_SHIFT);
		c.X+=velx;
		c.Y+=vely;
		c.Z+=velz;


}

inline ANGLES GetTakeOffOffset(AirStrucPtr currac,Coords3D& startpos,Coords3D& run0)
{
	int position=currac->position();
	Coords3D	posn1,posn2;
	if (!currac->GetTakeOffPos(UniqueID(RunwayEBAND),posn1))
	{	//JAPAN CLUDGE!!!
		run0=currac->ai.homebase->World;
		run0.Y=METRES1000;
		startpos.Z=startpos.Y=0;
		startpos.X=-METRES30*position;
		return ANGLES_0Deg;			
	}
	else
	{
		ANGLES h,p;
		SLong range,range2;
		startpos.X=startpos.Y=startpos.Z=0;
		currac->GetTakeOffPos(UniqueID(RunwaySBAND),run0);

		if (position>=2)
		{
			ItemBasePtr E=Persons2::ConvertPtrUID(UID_TAXIE),
						L=Persons2::ConvertPtrUID(UID_TAXIL);
			if (E&&L)
			{
				startpos.X=E->World.X-L->World.X;
				startpos.Y=0;
				startpos.Z=E->World.Z-L->World.Z;
			}
			else
			{
				startpos.X=startpos.Y=0;
				startpos.Z=-position*METRES30;
			}
		}
		Math_Lib.Intercept(posn1.X-run0.X,posn1.Y-run0.Y,posn1.Z-run0.Z,range,h,p);
		if (position&1)
		{
			ModifyPosn(startpos,METRES20,h-ANGLES_90Deg,ANGLES_0Deg);
		}
		return h;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    setpositionMIG
// Date:		09/03/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
Persons3::GearState	Persons3::setpositionMIG(AirStrucPtr currac,EventVal* pos,TakeOffState	takeoffstate,int takeofftimesecs)						//RDH 17Jun96
{
//	const	UniqueID	UID_TAXI1=(UniqueID)-1;
//	const	UniqueID	UID_TAXI0=(UniqueID)-2;
//	const	UniqueID	UID_TAXIL=(UniqueID)-3;
//	const	UniqueID	UID_TAXIW=(UniqueID)-4;
//	const	UniqueID	UID_RUNWAY0=(UniqueID)-5;
//	const	UniqueID	UID_RUNWAY1=(UniqueID)-6;
//	const	UniqueID	UID_TAXI2=(UniqueID)-7;

	const int	ACSTEP=METRES20;
	const int	FLSTEP=ACSTEP+ACSTEP;
	const int	BUDDYSTEP=METRES15;
 	const int	TAXIVEL=80;	//mm/cs = 18mph

	Coords3D	posn0,posn1;

	int takeofftime=takeofftimesecs*SECS100;
	int actiontime=inst3d->timeofday;
	if (takeoffstate>=TOS_RUNWAY)
	{
		if (ItemPtr(*ConvertPtrUID(UID_TAXI0))->SGT!=currac->ai.homebase->uniqueID.count)
		{	//other airfield
			//just place in rows of 4 .
			//need to get distance back and time delay to place this flight.
			//factors include:
			//takeoffstate,time delay,flight num
			//TOS_RUNWAY,			//no offset
			//TOS_NEXTFLIGHTS,		//offset based on time	- phase = go immediately
			//TOS_TAXIING,			//offset based on time	- phase = go immediately
			//TOS_HOLDING			//offset based on time modulo - phase = wait

			if (currac->position())
			{
				AirStrucPtr	leader;
				switch (currac->position())
				{
				case 3:
				case 1:		leader=currac->Leader();					break;
				case 2:		leader=currac->fly.leadelt()->Follower();	break;
				}
				ANGLES h=leader->hdg;
				currac->hdg=h;
				h-=ANGLES_90Deg;
				currac->World=leader->World;
				ModifyPosn(currac->World,METRES20,h,ANGLES_0Deg);
				currac->ai.manoeuvre.value=leader->ai.manoeuvre.value;
				currac->manoeuvretime=leader->manoeuvretime;
				currac->ai.ManStep.value=leader->ai.ManStep.value;
			}
			else
			{
				int positiontime=((takeofftime-actiontime)%(TIME_TAKEOFF_ROUNDING*100))%(60*SECS100);
				int holdingtime=(takeofftime-actiontime)-positiontime;
				currac->ai.manoeuvre.value=holdingtime>>16;
				currac->SetManoeuvreTime(holdingtime&0xffff);
				currac->GetTakeOffPos(UniqueID(RunwaySBAND),posn0);
				currac->GetTakeOffPos(UniqueID(RunwayEBAND),posn1);
				
				ANGLES h,p;
				SLong range;
				Math_Lib.Intercept(posn1.X-posn0.X,posn1.Y-posn0.Y,posn1.Z-posn0.Z,range,h,p);
				positiontime=-positiontime*TAXIVEL/100;
				currac->World=posn0;
				ModifyPosn(currac->World,positiontime,h,p);
				currac->hdg=h;
				currac->pitch=p;
				if (holdingtime)
					currac->ai.ManStep=TO_SIMPLEHOLDDELAY;
				else
					currac->ai.ManStep=TO_RUNWAYTAXI;
			}
			currac->movecode=AUTO_TAKEOFF;
			AddToWorld(currac);
			return GS_PARKED;
		}
	}

	switch (takeoffstate)
	{
	case TOS_SECRET:
	{
		currac->vel=0;
		if (pos)
		{
//ptr not set yet!			currac->ai.eventlog->stage=eventloglist->EMPTY;
//DeadCode CSB 12/07/99				return setposition(currac,*pos,TRUE)==TRUE;
			setposition(currac,*pos,TRUE);	//CSB 12/07/99	
		}
		else
		{
			currac->World=currac->fly.leadflight->World;
			currac->fly.leadflight->World.Y+=METRES10;
			AddToWorld(currac);
		}
	}
	return GS_INAIR;
	case TOS_SIMPLE:
	{	//USE UP HALF THE FUEL!!!
		currac->vel=currac->classtype->cruisevel;
		if (pos && pos->complex)
//DeadCode CSB 12/07/99				return setposition(currac,*pos,TRUE)==TRUE;
		{
			if(setposition(currac,*pos,TRUE)==TRUE)	//CSB 12/07/99	
				return GS_PARKED;					//CSB 12/07/99	
			else									//CSB 12/07/99	
				return GS_INAIR;					//CSB 12/07/99	
		}
		else
		{
			currac->information = TRUE;								  //RDH 27/04/99
			setfollowerposition(currac);
			return GS_INAIR;
		}
	}
	//addtoworld already performed
	return GS_INAIR;//false;	//CSB 12/07/99	
	case	TOS_MIGTAKEOFF:
	{	//place on homebase=packagetakeoff or on runway if not china1/2/3
		Coords3D	start,end;
		currac->movecode=AUTO_TAKEOFF;
		currac->ai.ManStep=TO_SIMPLEHOLDDELAY;
		if 	(currac->GetTakeOffPos(UniqueID(RunwaySBAND),start))
		{	//proper runway
			currac->GetTakeOffPos(UniqueID(RunwayEBAND),end);
			if (!GR_Pack_TakeTime[0][0])
				currac->ai.ManStep=TO_SIMPLEHOLDINDEFINITE;
		}
		else
		{	//fake item
			start=currac->ai.homebase->World;
			start.Y+=METRES1000;
			end=*currac->FindDesPos();
			if (!GR_Pack_TakeTime[0][0])
				currac->movecode=AUTO_FOLLOWWP;
		}
		int time=(GR_Pack_TakeTime[0][0]-GR_TakeOffTime)*SECS100;
		if (time<0)
			time=0;
		currac->ai.manoeuvre.value=time>>16;
		currac->SetManoeuvreTime(time&0xffff);
		currac->World=start;
		ANGLES h,p;
		SLong range;
		Math_Lib.Intercept(end.X-start.X,end.Y-start.Y,end.Z-start.Z,range,h,p);
		currac->pitch=p;
		currac->hdg=h;
		currac->roll=ANGLES_0Deg;
		AddToWorld(currac);

	}
	return GS_PARKED;//true;
	case TOS_INAIR:
	{		
		int	fuelused=10000000;	//take off cost = 99kg in cg 
		if (!currac->formpos)	//group leader
		{
			WayPointPtr wp=currac->waypoint;
			posn0=currac->ai.homebase->World;	//approx takeoff position
			posn0.Y+=METRES500;
			posn1=*wp->FindDesPos();
			int eta=wp->eta;
			int vel;
			int range=Math_Lib.Distance2d(posn0.X-posn1.X,posn0.Z-posn1.Z);
			if (!eta)
			{
				vel=wp->vel;
				if (!vel)
					vel=currac->classtype->cruisevel;
				eta=range*10/vel+takeofftime;
			}
			else
			{
				if (eta-takeofftime)
					vel=(range*10)/(eta-takeofftime);
				else
					vel=0;
				if (vel<200)
					vel=currac->classtype->cruisevel;
			}
			takeofftime+=1*60*SECS100;	//time taken to fly takeoff pattern
			if (eta<actiontime)
				if (currac->fly.leadflight)
				{	//place in formation with lead group
					//how to estimate fuel? Assume straight line at cruise?
					setfollowerposition(currac);
					fuelused+=(actiontime-takeofftime)*((currac->classtype->fuelaboff/4));
					currac->waypoint=currac->fly.leadflight->waypoint;
					currac->movecode=currac->fly.leadflight->movecode;
				}
				else
				{	//rattle through the waypoints...
					do{
						fuelused+=(eta-takeofftime)*((vel*currac->classtype->fuelaboff/4)/currac->classtype->cruisevel);
						posn0=posn1;			//reached prev waypoint
						takeofftime=eta;
						
						eta=wp->eta;
						posn1=*wp->FindDesPos();
						int range=Math_Lib.Distance2d(posn0.X-posn1.X,posn0.Z-posn1.Z);
						if (!eta)
						{
							vel=wp->vel;
							if (!vel)
								vel=currac->classtype->cruisevel;
							eta=range*10/vel+takeofftime;
						}
						else
						{
							if (eta-takeofftime)
								vel=(range*10)/(eta-takeofftime);
							else
								vel=0;
							if (vel<200)
								vel=currac->classtype->cruisevel;
						}

					breakif(eta>actiontime);

						if (wp->next->skipunder)
						{	//if within 10 mins of target then do the target
							if (eta+10*60*SECS100>actiontime)
							{
								posn0.Z-=METRES500;	//start 500m south of target area
								eta=eta+10*60*SECS100;
								break; //breakif has been satisfied!!!
							}
							else
							{
								//dice throw mission success!
								currac->movecode= AUTO_MISSIONDICETHROW;
								do
									wp=wp->next;
								while (wp->skipunder);
							}
						}
						else
							wp=wp->next;
					}while(wp->next);
					if (!wp->next)
					{	//run out of waypoints - prepare to split up
						posn0=posn1;
						posn0.Z+=METRES500;	//start 500m north of 'break formation'
						eta=actiontime+10;
						takeofftime=actiontime;
					}
				}	//else
			if (eta>actiontime)
			{	//set it up between posn0 and posn1
				//account for fuel loss
				//always ensure we have at least minsafefuel
				Float ratio=Float(actiontime-takeofftime)/Float(eta-takeofftime);
				if (ratio<-0.1)										  //DAW 18/06/99
					ratio=-0.1;										  //DAW 18/06/99
				currac->hdg=Math_Lib.arctan(posn1.X-posn0.X,posn1.Z-posn0.Z);
				posn0.X+=(posn1.X-posn0.X)*ratio;
				if (ratio>0.0)										  //DAW 18/06/99
					posn0.Y+=(posn1.Y-posn0.Y)*ratio;					  //DAW 23/03/99 //DAW 18/06/99
				posn0.Z+=(posn1.Z-posn0.Z)*ratio;					  //DAW 23/03/99
				currac->World=posn0;
				AddToWorld(currac);
				currac->vel=vel;
			}
			currac->waypoint=wp;
		}
		else
		{	//place in formation with leader.
			//how to estimate fuel? copy leader?
			setfollowerposition(currac);
			fuelused+=(actiontime-takeofftime)*((currac->classtype->fuelaboff/4));
			currac->waypoint=currac->fly.leadflight->waypoint;
			currac->movecode=currac->fly.leadflight->movecode;
		}
	}
	//addtoworld already preformed
	return GS_INAIR;//false;
	case  TOS_TAKENOFF:
	{	//place in air in a group formation pointing away from the runway
		int	fuelused=10000000;	//take off cost = 99kg in cg 
		if (!currac->formpos)
		{
			posn1=*currac->FindDesPos();
			currac->GetTakeOffPos(UniqueID(RunwaySBAND),posn0);
			posn0.Y+=METRES500;
			ANGLES h,p;
			SLong range;
			Math_Lib.Intercept(posn1.X-posn0.X,posn1.Y-posn0.Y,posn1.Z-posn0.Z,range,h,p);
			if (range>METRES2500)
				range=METRES2500;
			range=((actiontime-takeofftime)/TIME_TAKEOFF_FLIGHT+2)*range/25;
			ModifyPosn(posn0,range,h,p);
			currac->World=posn0;
			currac->hdg=h;
			currac->pitch=p;
			currac->fly.cpitch=p+ANGLES_5Deg;
			currac->vel=currac->classtype->cruisevel;
			AddToWorld(currac);
		}
		else
		{	//place in formation with leader.
			//how to estimate fuel? copy leader?
			setfollowerposition(currac);
		}
		currac->movecode=AUTO_TAKEOFF;
	}
	//addtoworld already preformed
	return GS_INAIR;//false;
	case  TOS_TAKINGOFF:
	{
		Coords3D offset;
		ANGLES h=GetTakeOffOffset(currac,offset,posn1);
		int fuelused=0;

		ANGLES p=ANGLES_0Deg;
		SLong range;
		ModifyPosn(posn1,METRES500,h,p);
		p=ANGLES_5Deg;			
		int flight=((actiontime-takeofftime)/(TIME_TAKEOFF_FLIGHT*100))-1;
		ModifyPosn(posn1,METRES400*flight*flight,h,p);
		posn1+=offset;
		currac->World=posn1;
		currac->hdg=h;
		currac->pitch=p;
		currac->fly.cpitch=p+ANGLES_5Deg;
		currac->vel=600+flight*50;
		currac->movecode=AUTO_TAKEOFF;
		currac->ai.ManStep=10;
		currac->SetManoeuvreTime(TO_MINCLIMBTIME+10*SECS100*(2-flight));
		AddToWorld(currac);
	}
	//addtoworld already preformed
	return GS_GEAR;//false;//true;//	//CSB 12/07/99	
	case TOS_RUNWAY:
	{
//DEADCODE DAW 04/06/99 		int FPOS = currac->position();	//Fix This !!!!
		int fuelused=0;
		ANGLES h=GetTakeOffOffset(currac,posn1,posn0);
		currac->hdg=h;
		posn0+=posn1;
		currac->World=posn0;
		currac->movecode=AUTO_TAKEOFF;
		currac->ai.ManStep=TO_PLAYERPLAYER;
	}
	AddToWorld(currac);
	return	GS_PARKED;//true;
	case TOS_NEXTFLIGHTS:
	{
		if (currac->leader)
		{	//place alongside my leader
			ANGLES h,p;
			ULong range=BUDDYSTEP;
			p=ANGLES_0Deg;
			h=currac->leader->hdg+ANGLES_90Deg;
			currac->World=currac->leader->World;
			ModifyPosn(currac->World,range,h,p);
			currac->movecode=AUTO_TAKEOFF;
			currac->ai.ManStep=TO_LATERFLIGHTPLAYER;
			currac->hdg=currac->leader->hdg;

		}
		else
		{
			currac->GetTakeOffPos(UID_TAXI0,posn0);
			currac->GetTakeOffPos(UID_TAXI1,posn1);
			ANGLES h,p;
			SLong range;
			Math_Lib.Intercept(posn1.X-posn0.X,posn1.Y-posn0.Y,posn1.Z-posn0.Z,range,h,p);
			currac->hdg=h+ANGLES_180Deg;
			range=METRES01+(FLSTEP/4)*(currac->position()+(takeofftime-actiontime)/(100*TIME_TAKEOFF_FLIGHT/4))-FLSTEP;
			ModifyPosn(posn0,range,h,p);
			currac->World=posn0;
			currac->movecode=AUTO_TAKEOFF;
			currac->ai.ManStep=TO_LATERFLIGHTPLAYER;
		}
	}
	AddToWorld(currac);
	return GS_PARKED;//true;
	case TOS_TAXIING:
	{
		if (currac->leader)
		{	//place alongside my leader
			ANGLES h,p;

			p=ANGLES_0Deg;
			h=currac->leader->hdg+ANGLES_90Deg;
			ULong range=BUDDYSTEP;
			currac->World=currac->leader->World;
			ModifyPosn(currac->World,range,h,p);

			currac->movecode=AUTO_TAKEOFF;
			currac->ai.ManStep=TO_LATERGROUPPLAYER;
			currac->hdg=currac->leader->hdg;

		}
		else
		{
			currac->GetTakeOffPos(UID_TAXI1,posn0);
			currac->GetTakeOffPos(UID_TAXI2,posn1);
			ANGLES h,p;
			SLong range;
			Math_Lib.Intercept(posn1.X-posn0.X,posn1.Y-posn0.Y,posn1.Z-posn0.Z,range,h,p);
			currac->hdg=h+ANGLES_180Deg;
			range=METRES01+(FLSTEP/4)*(currac->position()+(takeofftime-actiontime)/(100*TIME_TAKEOFF_FLIGHT/4))-FLSTEP;
			ModifyPosn(posn0,range,h,p);
			currac->World=posn0;
			currac->movecode=AUTO_TAKEOFF;
			currac->ai.ManStep=TO_LATERGROUPPLAYER;
		}


	}
	AddToWorld(currac);
	return GS_PARKED;//true;
	case TOS_HOLDING:
	{
		if (currac->leader)
		{	//place alongside my leader
			ANGLES h,p;

			p=ANGLES_0Deg;
			h=currac->leader->hdg+ANGLES_90Deg;
			ULong range=BUDDYSTEP;
			currac->World=currac->leader->World;
			ModifyPosn(currac->World,range,h,p);

			currac->movecode=AUTO_TAKEOFF;
			currac->ai.ManStep=TO_LATERGROUPTIMER;
			currac->hdg=currac->leader->hdg;
			int positiontime=(takeofftime-actiontime)%(TIME_TAKEOFF_ROUNDING*100);
			int holdingtime=(takeofftime-actiontime)-positiontime;
			currac->ai.manoeuvre.value=holdingtime>>16;
			currac->SetManoeuvreTime(holdingtime&0xffff);

		}
		else
		{
			currac->GetTakeOffPos(UID_TAXI1,posn0);
			currac->GetTakeOffPos(UID_TAXI2,posn1);
			ANGLES h,p;
			SLong range;
			Math_Lib.Intercept(posn1.X-posn0.X,posn1.Y-posn0.Y,posn1.Z-posn0.Z,range,h,p);
			currac->hdg=h+ANGLES_180Deg;
			int positiontime=(takeofftime-actiontime)%(TIME_TAKEOFF_ROUNDING*100);
			int holdingtime=(takeofftime-actiontime)-positiontime;
			range=METRES01+(FLSTEP/4)*(currac->position()+(positiontime)/(100*TIME_TAKEOFF_FLIGHT/4))-FLSTEP;
			ModifyPosn(posn0,range,h,p);
			currac->World=posn0;
			currac->movecode=AUTO_TAKEOFF;
			currac->ai.ManStep=TO_LATERGROUPTIMER;
			currac->ai.manoeuvre.value=holdingtime>>16;
			currac->SetManoeuvreTime(holdingtime&0xffff);

		}
	}
	AddToWorld(currac);
	return GS_PARKED;//true;
	}
	return GS_PARKED;//true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_airgrp
//LastModified:	JIM 29Jul97
//Author		Jim Taylor
//Date			Mon 16 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	SByte	Skill_Per_Period[]=
//		day0	day1	day2	day3	day4	day5	day6	day7	day8	
{22,	0,1,2,	2,3,3,	4,4,4,	5,5,5,	5,4,4,	3,3,2,	2,1,1,	0,0,0};

void	Persons3::make_airgrp(info_airgrp& I)
{

	if (justscanning)
	{
		if (I.uid.Evaluate()>=0)
			 UsedFixedUID=TRUE;
		return;
	}
	UByte		cols[COLS_ALL]={0};
	AirStruc	*firstac=NULL;
	AirStruc	*flleadac=NULL;
	AirStruc	*fllastac=NULL;
	int& GR_WaveNum=(int&)::GR_WaveNum;
	bool	supermig=false;
	int		offsetinformationleaderflights;

	int sqnum=I.squadname.Evaluate();

	if (sqnum==ENABLE_COMPLEX_VAL)
	{
		if (I.shape.Evaluate()==ENABLE_COMPLEX_VAL)
			if (GR_WaveNum<0)
			{
				sqnum=-int(GR_WaveNum--);
			}
			else
			{
				int grpnum=gotgrpnum;
				sqnum=(GR_Scram_Squad[GR_WaveNum-1]>>(grpnum*8))&255;
				if (sqnum==0)
					sqnum=(GR_Scram_Squad[GR_WaveNum-1])&255;
				sqnum++;
				sqnum&=127;
			}
		else
			sqnum=0;
	}


	FormationIndex estformpos=FormationIndexMIN;
	int	wingcount=0;
	int wingac=I.inwing.Evaluate();
	int	formac=ENABLE_COMPLEX_VAL;
	if (wingac==ENABLE_COMPLEX_VAL)
	{
		_Error.EmitSysErr("Old system for denoting piloted A/C has been binned");
	}
	else
	{
		formac=I.inform.Evaluate();
	}

	int	takeofftime=GR_TakeOffTime;
	TakeOffState	takeoffstate=TOS_SIMPLE;
	if (GR_WaveNum>0)
	{
		takeofftime=GR_Pack_TakeTime[GR_WaveNum-1][gotgrpnum];
		int roundedtakeofftime=GR_TakeOffTime-(GR_TakeOffTime%TIME_TAKEOFF_ROUNDING);
		if (takeofftime<roundedtakeofftime)
			takeoffstate=TOS_INAIR;		//Take off time well before player time
		else
		if (takeofftime>=roundedtakeofftime+TIME_TAKEOFF_ROUNDING)
			takeoffstate=TOS_HOLDING;	//Take off time well after player time
		else
		if (takeofftime>GR_TakeOffTime)
			takeoffstate=TOS_TAXIING;	//Take off time just behind player time
		else
		if (GR_TakeOffTime>takeofftime+(formac/wingac)*TIME_TAKEOFF_FLIGHT)
			takeoffstate=TOS_TAKENOFF;	//Take off time just in front of player time
		else
		if (GR_TakeOffTime==takeofftime)	//these two are pushed forward to 
			takeoffstate=TOS_RUNWAY;		//NEXTFLIGHTS
		else
			takeoffstate=TOS_TAKINGOFF;	//Take off time includes player.
	}





	if (I.usedpaintrules)
	{
		int	instr;;
		if (I.usedpaintrules==1 && (instr=I.paintrules[0].Evaluate())<16)
			colourrule=(PaintSchemes)instr;
		else
		{
			colourrule=PS_DEFINED;
			for (int j=0;j<I.usedpaintrules;j++)
			{
				instr=I.paintrules[j].Evaluate();
				int	code=instr&0x001f;
				if (code==16)
					code=Math_Lib.rnd(8);
				for (int i=0;i<6;i++)
				{
					if (instr&0xf0000000)
						if (code<16)
							cols[i]=code;
						else
							cols[i]=Math_Lib.rnd(8);
					instr<<=4;
				}
			}
		}
	}
	else
		if (formac==ENABLE_COMPLEX_VAL)
			colourrule=PS_PLAYER;
		else
			colourrule=PS_RANDOM;




	int	inwingcount=wingac;

	if (!formac)
	{	//No aircraft launched. Communication between waypoints and aircraft distracted
		gotgrpnum=-1;

	}
	else
	{
		do
		{

			int v1,v2,v3;
			AirStruc*	currac=new AirStruc;


			currac->follower=
				currac->fly.nextflight=NULL;
			if ((v1=I.nat.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)//AMM 30Jul98
				currac->nationality=NAT_RED;					//AMM 30Jul98
			else												//AMM 30Jul98
				currac->nationality=Nationality(v1);			//AMM 30Jul98


			if (	(v1=I.uid.Evaluate(estformpos))<0)
				if ((v2=I.band.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
					if (currac->nationality==NAT_RED)
						currac->uniqueID.count=assignuid(RedAcBAND);
					else
						currac->uniqueID.count=assignuid(BlueAcBAND);
				else
					currac->uniqueID.count=assignuid((UniqueIDBand)v2);
			else
				if (ConvertPtrUID(UniqueID(v1)))
					currac->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
				else
					currac->uniqueID.count=UniqueID(v1);


			if (estformpos==0)
			{
				offsetinformationleaderflights=0;	//CSB 14/05/99	

				//quick fix for mig squadron dummies!!!!
				if (I.type.Evaluate(0)>=SQ_R_MOREMIGSQUADS)
				{
					int sq=I.type.Evaluate(0)-SQ_R_MOREMIGSQUADS;
					if (formac==1 || wingac>1)
					{
						currac->fly.callname=formac;
						currac->fly.callnum=wingac;
						currac->Status.deadscale=sq;
						supermig=true;
						formac=wingac=inwingcount=1;
						if (!I.position.complex || I.movecode.Evaluate()==AUTO_TAKEOFF)
							takeoffstate=TOS_MIGTAKEOFF;
						if (GR_Pack_TakeTime[0][0])
							takeofftime=GR_Pack_TakeTime[0][0];
					}
					else
					{
						takeoffstate=TOS_SECRET;
						migsq[sq]=currac;
					}
					sqnum=MAXCALLNAMES-1-sq;
				}

				int grpnum=gotgrpnum;
				while (gotgrpnum<32)	//wind up to next active group num...
					breakif(gotgrpflags&(1<<++gotgrpnum));
				//waypoints use this a/c as group leader
				if (I.leader.Evaluate()!=ENABLE_COMPLEX_VAL)
				{	
					if (I.leader.Evaluate()==0)
					{
						//flleadac=NULL;		//already is...
						firstac=*ConvertPtrUID(prevflightleader);
					}
					else
						flleadac=
							firstac=*ConvertPtrUID((UniqueID)I.leader.Evaluate());
					if (firstac==NULL)
						_Error.EmitSysErr("Leader not loaded before used");
//DEADCODE JIM 01/03/99 					while (flleadac->fly.nextflight)
//DEADCODE JIM 01/03/99 						flleadac=flleadac->fly.nextflight;

					//cludge to set escort flights that are 
					//same type and formation as leader to
					//fly in formation with him instead of 
					//flying at escort position.
					if ((v1=I.type.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
						v1=GR_FriendlyScoutType00;
					v2=Squad2Type(v1);	  //TextRef
					if (Plane_Type_Translate[v2][0]==firstac->classtype)
						if (I.form.Evaluate()==firstac->formation)
						{
							offsetinformationleaderflights=numprevflights;
							if (wingac==2)
								numprevflights+=(formac+3)/4;
							else
								numprevflights+=(formac+wingac-1)/4;
						}

					if (!I.wpref)
					{
						I.wpref=firstac->waypoint->uniqueID.count;
					}
				}
				else
				{
					if (wingac==2)
						numprevflights=(formac+3)/4;
					else
						numprevflights=(formac+wingac-1)/wingac;
				 	prevflightleader=currac->uniqueID.count;
				}
				FixUpWaypointsToGroup(grpnum,I.wpref,currac->uniqueID.count,formac);
			}
			if (I.wpref)
				setpointer((ItemBasePtr*)&currac->waypoint,I.wpref);		//JIM 05Aug96
			else
			{
				assert	(takeoffstate==TOS_SECRET);
				currac->waypoint=NULL;
			}
//			currac->fly.storesweight = 0;
			currac->information = FALSE;		
			currac->velx =0;					
			currac->vely =0;					
			currac->velz =0;					
//			currac->fly.aoa = ANGLES_2Deg;
//			currac->fly.slip = ANGLES_0Deg;
			currac->fly.cpitch = ANGLES_0Deg;		
//			currac->ai.lastdeltapitch = ANGLES_0Deg;
//DEADCODE JIM 28/04/99 			currac->ai.lastdeltaroll = ANGLES_0Deg;		
			currac->fly.aileron = 0;						
			currac->fly.elevator = 0;					
			currac->fly.rudder = 0;						
//			currac->fly.weight = 1000;
			currac->weap.ShootDelay=0;


			if (flleadac==NULL)
			{
				currac->fly.leadflight=firstac;						  //JIM 01/03/99
				currac->formpos=FormationIndexMIN;
				currac->fly.originalformpos=currac->formpos+(InForm)offsetinformationleaderflights;
				firstac=
					flleadac=
						fllastac=currac;

			}
			else
			{
				currac->fly.leadflight=firstac;
				if (fllastac==NULL)
				{
					flleadac->fly.nextflight=currac;
					currac->leader=NULL;
					if (wingac==2 && (flleadac->formpos&InWingMAX)==0)
					{
						currac->formpos=flleadac->formpos+(InWing)2;
						currac->fly.originalformpos=flleadac->fly.originalformpos+(InWing)2;
					}
					else
					{
						currac->formpos=flleadac->formpos+(InForm)1;
						currac->fly.originalformpos=flleadac->fly.originalformpos+(InForm)1;
					}
					flleadac=
						fllastac=currac;
				}
				else
				{
					currac->leader=flleadac;
					fllastac->follower=currac;

					currac->formpos=fllastac->formpos+(InWing)1;
					currac->fly.originalformpos=fllastac->fly.originalformpos+(InWing)1;
					fllastac=currac;
				}
			}

			currac->follower=
				currac->fly.nextflight=NULL;

			if ((v1=I.nat.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				currac->nationality=NAT_RED;
			else
				currac->nationality=Nationality(v1);

			if (!supermig)
			{
				currac->fly.callname=sqnum;
				if (sqnum)
					currac->fly.callnum=callsignnamecount[sqnum]++;
				else
					currac->fly.callnum=0;
			}

			if ((v1=I.type.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				v1=GR_FriendlyScoutType00;
			int squadnum=v1;

			v2=Squad2Type(squadnum);	  //TextRef
			PilotType	dummypilot={{0},
									HideSkills(SKILL_REGULAR*HSallskills),
									NOTFLYING,
									MORALE_VERYGOOD};
			PilotType	*pilotskillinfoptr;

// check to see if AC are players

			SLong tempdecal=-1;									//AMM 08Dec98

			if (_DPlay.Implemented)
			{
				for (ULong n=0;n<MAXPLAYERS;n++)
				{
					if (_DPlay.GameType>TEAMPLAY)
					{
//DeadCode AMM 17Nov98 						if (DPlay::H2H_Player[n].position==v1
//DeadCode AMM 17Nov98 						&& DPlay::H2H_Player[n].squadron==GR_Pack_Sq_Used[v1])
						if (DPlay::H2H_Player[n].position==GR_Pack_Sq_Used[v1]//AMM 17Nov98
						&& DPlay::H2H_Player[n].squadron==v1)	//AMM 17Nov98
						{
							_DPlay.AllocPacket[n]=currac->uniqueID.count;
							currac->uniqueID.commsmove=TRUE;
							tempdecal=DPlay::H2H_Player[n].decal;//AMM 08Dec98
							break;
						}
					}
					else
					{
						if (!_DPlay.AllocPacket[n])
						{
							_DPlay.AllocPacket[n]=currac->uniqueID.count;
							currac->uniqueID.commsmove=TRUE;
							tempdecal=DPlay::H2H_Player[n].decal;//AMM 08Dec98
							break;
						}
					}
				}
			}
				
			if (v1<SQ_B_NONFLYABLE)
			{	//get record and increment index.
				currac->ai.pilotnum=v1*PILOTS_PER_SQUADRON+GR_Pack_Sq_Used[v1]; //DAW 13/04/99
				pilotskillinfoptr=&Miss_Man.camp.Active_Pilots[v1*PILOTS_PER_SQUADRON+GR_Pack_Sq_Used[v1]++]; //DAW 13/04/99
			}
			else
			{
				currac->ai.pilotnum=ai_info::PROPER_PILOT_MAX+v1;
				if (v1<=SQ_R_NONFLYABLE)
					GR_Pack_Sq_Used[v1]++;
				if (v1>=SQ_R_MOREMIGSQUADS)
				{	//copy data from squad description
					v1-=SQ_R_MOREMIGSQUADS;
					dummypilot.SetFlySkill(SkillType(Miss_Man.camp.migsquad[v1].generalskill-Math_Lib.rnd(6)));
					if (dummypilot.FlyingSkill()<SKILL_REGULAR)
						if (dummypilot.FlyingSkill()&1)
							dummypilot.SetFlySkill(SKILL_REGULAR);
					dummypilot.SetCombSkill(SkillType(Miss_Man.camp.migsquad[v1].generalskill-Math_Lib.rnd(6)));
					if (dummypilot.CombatSkill()<SKILL_REGULAR)
						if (dummypilot.CombatSkill()&1)
							dummypilot.SetCombSkill(SKILL_REGULAR);
					dummypilot.morale=Miss_Man.camp.migsquad[v1].morale;
					dummypilot.decal=Miss_Man.camp.migsquad[v1].colourscheme;
//DeadCode DAW 09Jul99 					dummypilot.SetCombSkill(SkillType(Miss_Man.camp.migsquad[v1].generalskill-Math_Lib.rnd(6)));
//DeadCode DAW 09Jul99 					dummypilot.morale=Miss_Man.camp.migsquad[v1].morale;
//DeadCode DAW 09Jul99 					dummypilot.decal=Miss_Man.camp.migsquad[v1].colourscheme;
				}
				pilotskillinfoptr=&dummypilot;
			}
			pilotskillinfoptr->dayssincerest++;
			pilotskillinfoptr->missionscompleted++;
			if (tempdecal!=-1)									//AMM 08Dec98
			{													//AMM 08Dec98
				pilotskillinfoptr->decal=tempdecal;				//AMM 08Dec98
				tempdecal=-1;									//AMM 08Dec98
			}													//AMM 08Dec98

			currac->classtype=Plane_Type_Translate[v2][0];
			if (v1==Pack_PlayerSquad)
				Pack_PlayerPos--;

			if ((v1=I.shape.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				if (!supermig)
					currac->shape=currac->classtype->visible;
				else
					currac->shape=SUPMIG;
			else
				currac->shape=(ShapeNum)v1;
			HP	hp;
			if (!I.attitude.EvalA(hp))
			{
				currac->hdg=hp.H;
				currac->pitch=hp.P;
			}
			else
				currac->pitch=ANGLES_180Deg;

			currac->roll=ANGLES_0Deg;										//JIM 21Oct96
  			currac->fly.rpm = 1150;									//JIM 21Oct96
			currac->fly.thrustpercent = 100;							//JIM 21Oct96


			currac->ai.manoeuvre=MANOEUVRE_SELECT;
			currac->manoeuvretime=0;									//JIM 11Sep96
			currac->ai.ManStep=PHASE0;								//JIM 11Sep96
			currac->slowdownleader=FALSE;
			currac->information=FALSE;

			currac->CommsOwner=UID_NULL;							//AMM 27Nov98

			if ((v1=I.movecode.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				currac->movecode=AUTO_FOLLOWWP;
			else
				if (v1>AUTO_COMBAT)
				{
					currac->movecode=AUTO_COMBAT;
					currac->ai.manoeuvre=MANOEUVRE(v1-AUTO_COMBAT);
				}
				else
					currac->movecode=AutoMoveCodeTypeSelect(v1);

			FormOrDefault(currac->ai.morale,MoraleType,morale,pilotskillinfoptr->morale);
			FormOrDefault(currac->ai.radiosilent,Bool,radiosilence,FALSE);
//temp for flight model tuning, rdh
//auto ac
//rdh 25nov			currac->ai.morale = MORALE_GOOD;		//MORALE_POOR;
//			currac->ai.morale 	= MORALE_TOPMORALE;		
			
//RDH 18/02/99
			if (currac->nationality == NAT_RED)
			{
				currac->ai.elementtactics = LOOSEDEUCE;
			}else
			{
				currac->ai.elementtactics = WELDEDWING;
			}
			currac->ai.squadrontactics = LOOSEDEUCE;
			currac->ai.flighttactics = LOOSEDEUCE;
			
			int combskill,flyskill;
			FormOrDefault(combskill,int,skill,pilotskillinfoptr->CombatSkill());
			FormOrDefault(flyskill,int,skill,pilotskillinfoptr->FlyingSkill());
			if (pilotskillinfoptr->dayssincerest>Skill_Per_Period[0])
			{
				combskill=combskill-(pilotskillinfoptr->dayssincerest-Skill_Per_Period[0]);
				flyskill=flyskill-(pilotskillinfoptr->dayssincerest-Skill_Per_Period[0]);
				if (combskill<0)
					combskill=0;
				if (flyskill<0)
					flyskill=0;
			}
			else
			{
				combskill=combskill+(Skill_Per_Period[pilotskillinfoptr->dayssincerest]);
				flyskill=flyskill+(Skill_Per_Period[pilotskillinfoptr->dayssincerest]);
				if (combskill>SKILL_MAX)
					combskill=SKILL_MAX;
				if (flyskill>SKILL_MAX)
					flyskill=SKILL_MAX;
			}

			currac->ai.flyingskill=SkillType(	((GR_GlobalSkillMax-GR_GlobalSkillMin)*flyskill)/SKILL_HERO
												+GR_GlobalSkillMin
											);
			currac->ai.combatskill=SkillType(	((GR_GlobalSkillMax-GR_GlobalSkillMin)*combskill)/SKILL_HERO
												+GR_GlobalSkillMin
											);

			FormOrDefault(currac->ai.character,CharacterType,character,CHAR_MRAVERAGE);

			FormOrDefault((UWord&)cols[COLS_DAMAGE],int,damage,0);
			FormOrDefault((UWord&)cols[COLS_BOMBS],int,bombs,0);


			if ((v1=I.target.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				currac->ai.unfriendly=NULL;
			else
				setpointer((ItemBase**)&currac->ai.unfriendly,UniqueID(v1));

			if ((v1=I.attacker.Evaluate(estformpos))==ENABLE_COMPLEX_VAL || estformpos==0)
				currac->ai.attacker=NULL;
			else
				setpointer((ItemBase**)&currac->ai.attacker,UniqueID(v1));


			if ((v1=I.homebase.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
			{
				if (firstac!=currac)
					currac->ai.homebase=firstac->ai.homebase;
				else
					if (squadnum<SQ_B_NONFLYABLE)
						setpointer((ItemBase**)&currac->ai.homebase,UniqueID(GR_Pack_Home[squadnum]));
					else
					if (squadnum<SQ_R_FLYABLE)
						setpointer((ItemBase**)&currac->ai.homebase,UID_Japan);
					

	//DeadCode AMM 20Aug97 			else
	//DeadCode AMM 20Aug97 				_Error.EmitSysErr("No homebase defined???");
			}
			else
				setpointer((ItemBase**)&currac->ai.homebase,UniqueID(v1));

			if (Three_Dee.livelist)
			{
				DOLAUNCHER_PTR d=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos(currac->shape,0);
				if ( d && (d->lnchrtype & LT_MASK) == LT_MOVEGUN )
					*Three_Dee.livelist+=currac;
			}

			if (firstobject==IllegalSepID)
				firstobject=currac->uniqueID.count;

			int dutyval=0,dvplus1=0,dvplus2=0;						  //JIM 25/03/99
			EvalOrDefault(dutyval,int,duty,DUTYMIGCAP);				  //JIM 25/03/99
			EvalOrDefault(dvplus1,int,attmethod,0);					  //JIM 25/03/99
			EvalOrDefault(dvplus2,int,attpattern,0);				  //JIM 25/03/99
			if ((dutyval&ACTIONSUBCODE)==0)							  //RDH 23/05/99
			switch (dvplus1)
			{
			case 0:	//dive											  //RDH 23/05/99
				if ((dutyval&ACTIONCODE)!=DA_CAP)
				{
					if (dvplus2)
						dvplus1=dvplus2+9;
					else
						if (squadnum<SQ_B_NONFLYABLE)
							dvplus1=10;
						else
							dvplus1=0;	//high level default!
				}
				break;
			case 1:	//low level
				dvplus1+=dvplus2;
				break;
			case 2:	//high level
				dvplus1=0;	dvplus2=0;	break;
			}
			currac->duty=DutyType(dutyval+dvplus1);					  //RDH 23/05/99

			EvalOrDefault(currac->formation,FormationTypeIndex,form,SQUAD_STACKEDV);

			FormOrDefault(currac->vel,int,vel,currac->classtype->cruisevel);		//rdh
			GearState	onground;
			if (estformpos==0)
			{
				EventVal* pos=&I.position;

				if ((onground=setpositionMIG(currac,pos,takeoffstate,takeofftime))==GS_PARKED)//true)						//RDH 17Jun96	//CSB 12/07/99	
				{
					currac->vel=0;
					currac->pitch = currac->classtype->deckangle;
					currac->roll = ANGLES_0Deg;
					currac->fly.vel_cms = 	0;					
				}
				make_events(I.events,currac);
			}
			else
			{
				if (firstac->movecode==AUTO_TAKEOFF)
				{
					currac->vel=0;
					currac->movecode=AUTO_TAKEOFF;
//rdh					currac->hdg = MMC.wind.direction;				//RDH 15Sep97
					currac->pitch = currac->classtype->deckangle;
					currac->roll = ANGLES_0Deg;
					currac->fly.vel_cms = 	0;					
//					currac->fly.vel_mms = 	0;					
				}
			}

			currac->fly.comefrommap = FALSE;								//RDH 20Nov96

 			if (currac->pitch == ANGLES_180Deg)						//RDH 16Apr96
 				SetAngles (currac);									//RDH 16Apr96

			currac->ai.eventlog=eventloglist;
			if (estformpos)
			{
				if ((onground=setpositionMIG(currac,NULL,takeoffstate,takeofftime))==GS_PARKED)						//RDH 17Jun96
				{														//CSB 19/02/99
					currac->vel=0;										//CSB 19/02/99
					currac->pitch = currac->classtype->deckangle;		//CSB 19/02/99
					currac->roll = ANGLES_0Deg;							//CSB 19/02/99
					currac->fly.vel_cms = 	0;							//CSB 19/02/99
				}														//CSB 19/02/99

			}
			else
			{
				if (eventloglist->nat!=NAT_AMBER)
					if (I.follower.Evaluate()==ENABLE_COMPLEX_VAL
					&&	I.leader.Evaluate()==ENABLE_COMPLEX_VAL)
						currac->ai.eventlog=
							eventloglist=
								new EventLog (eventloglist);
				
				eventloglist->nat=currac->nationality;			//JIM 30Sep96
				if (I.leader.Evaluate()==ENABLE_COMPLEX_VAL)
				{
					eventloglist->targetuid=currac->uniqueID.count;
					if (eventloglist->stage!=EventLog::TAKEOFF)
					{
						eventloglist->encounteredtype=PlaneTypeSelect(v2);
						eventloglist->launchtime=takeofftime*SECS100;
						if (eventloglist->homebase==UID_Japan)
							eventloglist->launchtime-=30*60*SECS100;
					}
				}
				else
					if (eventloglist->stage!=EventLog::TAKEOFF)
						eventloglist->escorttype=PlaneTypeSelect(v2);


//				if (formac==ENABLE_COMPLEX_VAL)
//				{
//					UpdateLog(eventloglist,0,EventLog::TAKEOFF);//RDH 02Oct96
//				}
//				else
				{
					if (takeoffstate!=TOS_SECRET)
					{
						if (supermig)
							eventloglist->encsize += currac->fly.callname;			//RDH 02Oct96
						else
							eventloglist->encsize += formac;			//RDH 02Oct96
						if (/*currac->nationality==NAT_RED &&*/ eventloglist->stage!=EventLog::TAKEOFF)
						{
							UpdateLog(eventloglist,0,EventLog::UNSEEN);//RDH 02Oct96
							eventloglist->launchtime=takeofftime*SECS100;
							if (eventloglist->homebase==UID_Japan)
								eventloglist->launchtime-=30*60*SECS100;
						}
					}
				}

				if (	eventloglist->homebase==UID_NULL
					&& currac->ai.homebase
					&& (int)currac->ai.homebase!=-1
//					&& (currac->movecode==AUTO_TAKEOFF)		//RDH 13Nov96
					)
				{
					eventloglist->homebase=currac->ai.homebase->uniqueID.count;
					if (eventloglist->homebase==UID_Japan)
						eventloglist->launchtime-=30*60*SECS100;
				}
			}

			//Everybody goes through colourruleplayersquadron now!!!!!
			ColourRulePlayerSquadron(currac,currac->formpos,cols,pilotskillinfoptr);			//RDH 16Apr96
//DeadCode DAW 09Jul99 			if (takeoffstate>TOS_TAKENOFF)
			if(onground != GS_INAIR)
			{
				currac->fly.pModel->GearDown(currac);
				SHAPE.NavigationLightsActive(currac, TRUE);
			}


			logUID(currac);
			if (I.uid.Evaluate() !=ENABLE_COMPLEX_VAL && I.uid.Evaluate()<0)
			{
					SetLoc(-I.uid.Evaluate(),currac->uniqueID.count); //also need to fix references
					useUID(currac,UniqueID(I.uid.Evaluate()));
			}
			currac->AddToList();

			//set up for next in squadron

			--formac;
			if (--inwingcount==0)
			{
		 		inwingcount=wingac;
		 		fllastac=NULL;
				if (wingac==2 && (formac&2))
					estformpos+=(InWing)1;
				else
				{
			 		estformpos+=(InForm)1;
					if (takeoffstate>TOS_TAKENOFF)
						takeofftime+=TIME_TAKEOFF_FLIGHT;
					if (takeoffstate==TOS_RUNWAY)
						takeoffstate=TOS_NEXTFLIGHTS;
					else
					if (takeoffstate==TOS_TAKINGOFF)
						if (takeofftime>=GR_TakeOffTime)
							takeoffstate=TOS_RUNWAY;	//next flight is player!!
				}
			}
			else
				estformpos+=(InWing)1;

		} while (formac);

		if (I.follower.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			AirStrucPtr f=*ConvertPtrUID((UniqueID)I.follower.Evaluate());
			if (f==NULL)
				_Error.EmitSysErr("Follower not yet defined!");
			f->fly.leadflight=firstac;
		}
		fixupengagements(firstac);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		fixupengagements
//Author		Jim Taylor
//Date			Mon 19 Aug 1996
//
//Description	Fixes to squadron engagement logic for forward references
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::fixupengagements(AirStrucPtr	firstac)
{
	AirStrucPtr attacker=firstac->ai.attacker;
	if (	firstac->ai.unfriendly
		&&	(int) firstac->ai.unfriendly !=-1
		&& 	firstac->ai.unfriendly->Status.size==AIRSTRUCSIZE	)
	{
		AirStrucPtr	eye=firstac;
		AirStrucPtr trg=*firstac->ai.unfriendly;
		fixupengagements(eye,trg);
		if (	trg->ai.unfriendly==eye
			&&	attacker!=trg	)
		{
			AirStrucPtr	eye=trg;
			AirStrucPtr trg=firstac;
			fixupengagements(eye,trg);
		}
	}
	if (	attacker
		&&	(int)attacker!=-1	)
	{
			AirStrucPtr	eye=attacker;
			AirStrucPtr trg=firstac;
			fixupengagements(eye,trg);
	}
}

void	Persons3::fixupengagements(AirStrucPtr	eyeF,AirStrucPtr trg)
{
	//movecodes and manoeuvres already done
	//leader goes for leader... already done
	trg->ai.attacker=eyeF;
	AirStrucPtr	trgF=trg;
	forever
	{
		AirStrucPtr eye=*eyeF->follower;
		while (eye)
		{
			AirStrucPtr trgE=Art_Int.SetFollowerWhoCanEngage(eye,trgF);
			if (trg)
				trgF=trgE;
			eye->ai.unfriendly=trgE;

// set up commsowner if this ac is attacking a player initially

			if (trgE->uniqueID.commsmove)						//AMM 27Nov98
				eye->CommsOwner=trgE->uniqueID.count;			//AMM 27Nov98

			if (trgE && trgE->ai.attacker!=NULL)
				trgE->ai.attacker=eye;
			eye=*eye->follower;
		}

		eyeF=eyeF->fly.nextflight;
		breakif (eyeF==NULL);
		AirStrucPtr trgF=Art_Int.SetFlightWhoCanEngage(eyeF,trg);
		if (trgF)
			trg=trgF;
		eyeF->ai.unfriendly=trgF;

// set up commsowner if this ac is attacking a player initially

		if (trgF->uniqueID.commsmove)							//AMM 27Nov98
			eyeF->CommsOwner=trgF->uniqueID.count;				//AMM 27Nov98

		if (trgF && trgF->ai.attacker!=NULL)
			trgF->ai.attacker=eyeF;
	};
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_waypoint
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		if I.useexistingWP then evaluate that to get UID to link in!
//				no other vars will be filled in.
//
//Returns	
//
//------------------------------------------------------------------------------
enum	{WP_SKIP_BASE=IllegalSepID+1,WP_SKIP_GROUP=64};
UniqueID	Persons3::make_waypoint(info_waypoint& I)
{
	if(gotgrpnum)
	{
		gotgrpnum=0;
		gotgrpflags=0xffff0000;
		if ((int)GR_WaveNum>=0)
			GR_WaveNum++;
		nextwpname=WPNAME_None;
		nextwpnum=1;
	}

	if (justscanning)
	{

		if (I.uid.Evaluate()>=0)
			 UsedFixedUID=TRUE;
		return (UID_Null);
	}
	int v1;
	if ((v1=I.useexistingWP.Evaluate())!=ENABLE_COMPLEX_VAL)
	{
		if (I.prevwp!=IllegalSepID)
		{
			WayPointPtr p,n;
			p=*ConvertPtrUID(I.prevwp);
			n=*ConvertPtrUID(UniqueID(v1));
			if (p==NULL || n==NULL)
				_Error.EmitSysErr("Can't link together unloaded waypoints");
			p->next=n;
			n->prev=p;
		}
		return UniqueID(v1);
	}
	else
	{
		WayPointPtr	newwaypoint=new WayPoint;
		if (I.events!=NULL)
		{
//DeadCode AMM 10Jun98 			newwaypoint->uniqueID.deaded=TRUE;
//DeadCode AMM 30Nov98 			newwaypoint->uniqueID.commsmove=TRUE;				//AMM 10Jun98
			newwaypoint->Status.deaded=TRUE;					//AMM 30Nov98
			make_events(I.events,newwaypoint);
		}
//DeadCode AMM 10Jun98  		newwaypoint->uniqueID.deaded=FALSE;
//DeadCode AMM 30Nov98  		newwaypoint->uniqueID.commsmove=FALSE;					//AMM 10Jun98
 		newwaypoint->Status.deaded=FALSE;						//AMM 30Nov98
 ////		newwaypoint->bfieldindex=1;
		newwaypoint->eta = 0;										//RDH 19Feb96
		if ((v1=I.etas.Evaluate())!=ENABLE_COMPLEX_VAL)
			newwaypoint->eta += v1*100;										//RDH 19Feb96
		if ((v1=I.etam.Evaluate())!=ENABLE_COMPLEX_VAL)
			newwaypoint->eta += v1*60*100;										//RDH 19Feb96
		if ((v1=I.etah.Evaluate())!=ENABLE_COMPLEX_VAL)
			newwaypoint->eta += v1*60*60*100;										//RDH 19Feb96
		if ((v1=I.uid.Evaluate())<0)
		{
			newwaypoint->uniqueID.count=assignuid(WayPointBAND);
			if (-v1>=SGR_WPP_Rendevous && -v1<=SGR_WPP_Disperse)
			{
				nextwpname=WPNames(-v1-SGR_WPP_Rendevous+WPNAME_Rendevous);
				nextwpnum=0;
			}
			elseif (-v1>=SGR_WPC_Rendevous && -v1<=SGR_WPC_Disperse)
			{
				nextwpname=WPNames(-v1-SGR_WPC_Rendevous+WPNAME_Rendevous);
				nextwpnum=0;
			}
		}
		else
		{
			newwaypoint->uniqueID.count=UniqueID(v1);
		}
		newwaypoint->wpname=nextwpname;
		newwaypoint->wpnum=nextwpnum++;
		EvalOrDefault(newwaypoint->vel,int,vel,0);

		if (I.position.complex)
			setposition(newwaypoint,I.position,FALSE);
		else
			newwaypoint->World.X=
				newwaypoint->World.Y=
					newwaypoint->World.Z=
						0;

		if ((v1=I.target.Evaluate())==ENABLE_COMPLEX_VAL)
			newwaypoint->target=NULL;
		else
			setpointer((ItemBase**)&newwaypoint->target,UniqueID(v1));

		WayPointPtr	tmpwp=NULL;
		if (I.prevwp!=IllegalSepID)
		{
			tmpwp=(WayPointPtr)ConvertPtrUID(I.prevwp);
			assert((tmpwp)&&("nested route must exist"));
		}

		if ((v1=I.range.Evaluate())!=ENABLE_COMPLEX_VAL)
			if (I.rangeispercent)
			{
				assert(tmpwp&&"RangePC but no prev");
				SLong r;
				ANGLES b,a;
				Math_Lib.HighIntercept(	tmpwp->World.X-newwaypoint->World.X,
									tmpwp->World.Y-newwaypoint->World.Y,
									tmpwp->World.Z-newwaypoint->World.Z,
									r,b,a);
				if (r>1000000)
					r=(r/100)*v1;
				else
					r=(r*v1)/100;
				newwaypoint->range=r;
			}
			else
				newwaypoint->range=v1;
		else
			newwaypoint->range=0;

		if (I.applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			gotgrpflags|=1<<I.applygroup.Evaluate();
			//I put dummy values into skipunder and skipover which later get fixed up.
			newwaypoint->skipunder=UniqueID((WP_SKIP_BASE)+(I.applygroup.Evaluate()*WP_SKIP_GROUP));
			newwaypoint->skipover=UniqueID(newwaypoint->skipunder+63);	//this will get trimmed when fixed up
			if (I.applyflight.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				newwaypoint->skipunder=UniqueID(newwaypoint->skipunder+I.applyflight.Evaluate()*4);
				newwaypoint->skipover=UniqueID(newwaypoint->skipunder+3);
			}
			if (I.applyelt.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				newwaypoint->skipunder=UniqueID(newwaypoint->skipunder+I.applyelt.Evaluate()*2);
				newwaypoint->skipover=UniqueID(newwaypoint->skipunder+1);
			}
			if (I.applyac.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				newwaypoint->skipunder=UniqueID(newwaypoint->skipunder+I.applyac.Evaluate());
				newwaypoint->skipover=UniqueID(newwaypoint->skipunder);
			}
		}


		EvalOrDefault(newwaypoint->action,BFieldWaypointActions,wpact,wpacnoactionno);
		logUID(newwaypoint);
		if (I.uid.Evaluate() !=ENABLE_COMPLEX_VAL && I.uid.Evaluate()<0)
		{
				SetLoc(-I.uid.Evaluate(),newwaypoint->uniqueID.count); //also need to fix references
				useUID(newwaypoint,UniqueID(I.uid.Evaluate()));
		}
		if (tmpwp)
		{
			tmpwp->next=newwaypoint;
			newwaypoint->prev=tmpwp;
		}
		else
			newwaypoint->prev=NULL;
		newwaypoint->next=NULL;
		return(newwaypoint->uniqueID.count);
	}
}

void	Persons3::FixUpWaypointsToGroup(int grpnum,UniqueID route,UniqueID leader,int numinflight)
{		//tromp down the route. Any waypoint keyed to this group gets a UID based on leader uid.
	grpnum=(WP_SKIP_BASE)+(grpnum*WP_SKIP_GROUP);
	int grpnumupper=grpnum+numinflight-1;
	int grpnummax=grpnum+WP_SKIP_GROUP-1;
	
	for(WayPointPtr w=*ConvertPtrUID(route);w;w=w->next)
		if (	w->skipunder>=grpnum		//this is bottom of current grp range
			&&	w->skipunder<=grpnummax)	//this is a debug helper-max possible value
			if (w->skipunder<=grpnumupper)	//this is real top of current grp range
			{
				w->skipunder=UniqueID(w->skipunder-grpnum+leader);
				if (w->skipover<=grpnumupper)	//if range goes over clip
					w->skipover=UniqueID(w->skipover-grpnum+leader);
				else
					w->skipover=UniqueID(leader+numinflight-1);
			}
			//else range starts too high - ignore it!
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_itemS
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	Persons3::make_itemgroupcount(EventVal& E)
{
	return E.Evaluate();
}

void	Persons3::make_itemS(info_itemS& I,bool enabled)
{
	if (!enabled)
		return;
	if (justscanning)
	{
		if (I.uid.Evaluate()>=0)
			 UsedFixedUID=TRUE;
		return;
	}
	if (I.band.Evaluate()==RedAAASiteBAND && Math_Lib.rnd()>GR_AAALevel64K)
		return;	//Discard some AAA sites if low activity!!!!

	if (I.band.Evaluate()==RedAAALargeBAND)
	{	//this may be quite painful!
		assert (I.SGT);
		if (SupplyTree::FindSupplyNodeForNodeItem(I.SGT)->status!=BEHINDREDLINES)
			return;
	}

	itemptr	tmpitem = new item;
	tmpitem->SGT=I.SGT;
	make_events(I.events,tmpitem);
	if (I.uid.Evaluate()<0)
		if (I.band.Evaluate()==ENABLE_COMPLEX_VAL)
			tmpitem->uniqueID.count=assignuid(GreenMiscBAND);
		else
			tmpitem->uniqueID.count=assignuid(UniqueIDBand(I.band.Evaluate()));
	else
		tmpitem->uniqueID.count=UniqueID(I.uid.Evaluate());
	int sh=I.shape.Evaluate();
	if (sh==ENABLE_COMPLEX_VAL)
		_Error.EmitSysErr("Shape not set in item");
	*shapefield|=
		(tmpitem->shape=(ShapeNum)I.shape.Evaluate());
	if (I.attitude.Evaluate() != ENABLE_COMPLEX_VAL)
	{
		// Set anim for bridge shape....
		// ... and fill it in for animation

		if (SHAPE.SetAnimData(tmpitem,0) == sizeof(ExplodeAnimData))
		{
			ExplodeAnimData*	adptr = (ExplodeAnimData*) tmpitem->Anim;
			adptr->frameno = I.attitude.Evaluate();
		}
	}

	setposition(tmpitem,I.position,TRUE);
	logUID(tmpitem);
	if (I.uid.Evaluate() !=ENABLE_COMPLEX_VAL && I.uid.Evaluate()<0)
	{
		SetLoc(-I.uid.Evaluate(),tmpitem->uniqueID.count); //also need to fix references
		useUID(tmpitem,UniqueID(I.uid.Evaluate()));
	}
	if (firstobject==IllegalSepID)
		firstobject=tmpitem->uniqueID.count;

//DeadCode JIM 08Jan96 		AddToWorld(tmpitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_gndgrp
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::make_gndgrp(info_grndgrp& I)
{
	if (justscanning)
	{

		if (I.uid.Evaluate()>=0)
			 UsedFixedUID=TRUE;

		return;
	}
	int inform=I.inform.Evaluate();
	if (inform==ENABLE_COMPLEX_VAL)
		inform=1;
	if (inform<=-1)
	{
		inform=GR_FormSize00/-inform;
		if (inform<4)
		{
			inform=8;
			if (inform>GR_FormSize00)
				inform=GR_FormSize00;
			GR_FormSize00-=inform;
			if (GR_FormSize00!=0 && GR_FormSize00<inform)
			{
				GR_FormSize00+=inform;
				inform=GR_FormSize00/2;
				GR_FormSize00-=inform;
			}
		}
	}

	gotgrpnum=-1;
	if (inform)
	{
FormationItemPtr
		leadtruck=NULL,
		prevtruck=NULL,
		currtruck=NULL;
		FormationIndex	estformpos=FormationIndexMIN;
		int v1,v2;
		if ((v1=I.leader.Evaluate())!=ENABLE_COMPLEX_VAL)
		{
			prevtruck=
				leadtruck=*ConvertPtrUID((UniqueID)v1);
			if (leadtruck==NULL)
				_Error.EmitSysErr("Specified Lead truck not yet defined.");
		}
		
		while (inform--)
		{
			currtruck=new	FormationItem;
			currtruck->SGT=I.SGT;
			if (leadtruck==NULL)
			{
				leadtruck=currtruck;
				currtruck->leader=NULL;
				currtruck->formpos=FormationIndexMIN;
			}
			else
			{
				currtruck->leader=leadtruck;
				prevtruck->follower=currtruck;
				currtruck->formpos=prevtruck->formpos+(InWing)1;
			}
			currtruck->follower=NULL;


			FormOrDefault(currtruck->nationality,Nationality,nat,NAT_RED);	//defaultside);
			EvalOrDefault(currtruck->formation,FormationTypeIndex,form,FORM_V);

			if ((v1=I.uid.Evaluate(estformpos))<0)
				if ((v2=I.band.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
//					if (currtruck->nationality==NAT_RED)
//						currtruck->uniqueID.count=assignuid(RedCombatVehicleBAND);
//					else
						currtruck->uniqueID.count=assignuid(BlueCombatVehicleBAND);
				else
					currtruck->uniqueID.count=assignuid((UniqueIDBand)v2);
			else
				if (ConvertPtrUID(UniqueID(v1)))
					currtruck->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
				else
				{
					currtruck->uniqueID.count=UniqueID(v1);
				}

			if ((v1=I.type.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				currtruck->classtype=Plane_Type_Translate[PT_ATruck]_;
			else
				currtruck->classtype=Plane_Type_Translate[Squad2Type(v1)]_;

			if ((v1=I.shape.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				currtruck->shape=currtruck->classtype->visible;
			else
				currtruck->shape=(ShapeNum)v1;


			EvalOrDefault(currtruck->movecode,AutoMoveCodeTypeSelect,movecode,AutoMoveCodeTypeSelect(GR_TruckMoveCode));
			currtruck->manoeuvretime=0;
			currtruck->slowdownleader=FALSE;					//JIM 18Jun97
			currtruck->information=FALSE;							//JIM 18Jun97
			currtruck->velx =0;												//RDH 26Feb96
			currtruck->vely =0;												//RDH 26Feb96
			currtruck->velz =0;												//RDH 26Feb96
			currtruck->velhori =0;												//RDH 26Feb96

			FormOrDefault(currtruck->vel,int,vel,50);//5 m/s or 10mph
			
			setpointer((ItemBasePtr*)&currtruck->waypoint,I.wpref);

			if (currtruck->formpos==0)
				setposition(currtruck,I.position,TRUE);			
			else
				setfollowerposition(currtruck);
			HP	hp;
			currtruck->roll=ANGLES_0Deg;										//JIM 21Oct96
			currtruck->pitch=ANGLES_180Deg;										//JIM 21Oct96
			if (!I.attitude.EvalA(hp))
			{
				currtruck->hdg=hp.H;
				currtruck->pitch=hp.P;
			}
			else
				SetAngles (currtruck);						
			logUID(currtruck);
			if (I.uid.Evaluate() !=ENABLE_COMPLEX_VAL && I.uid.Evaluate()<0)
			{
					SetLoc(I.uid.Evaluate(),currtruck->uniqueID.count); //also need to fix references
					useUID(currtruck,UniqueID(I.uid.Evaluate()));
			}
			currtruck->AddToList();
				
			estformpos+=(InForm)1;
			prevtruck=currtruck;
		}
		make_events(I.events,leadtruck);
		if (firstobject==IllegalSepID)
			firstobject=leadtruck->uniqueID.count;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_events
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::make_events(info_event_ptr&	I,ItemBasePtr P)
{
//DEADCODE JIM 17/03/99 	if (justscanning)
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 		return;
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 	info_event_ptr J=I;
//DEADCODE JIM 17/03/99 	I=NULL;
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 		info_event_ptr I=J;
//DEADCODE JIM 17/03/99 	while (I)
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		EventRecPtr	newevent;
//DEADCODE JIM 17/03/99 		int count=10;
//DEADCODE JIM 17/03/99 		int bfnum;
//DEADCODE JIM 17/03/99 		do
//DEADCODE JIM 17/03/99 		{
//DEADCODE JIM 17/03/99 			bfnum=I->bfields.Evaluate();
//DEADCODE JIM 17/03/99 			breakif (bfnum==ENABLE_COMPLEX_VAL);
//DEADCODE JIM 17/03/99 			if (BITTEST(usedevents,bfnum&255))
//DEADCODE JIM 17/03/99 				bfnum=ENABLE_COMPLEX_VAL;
//DEADCODE JIM 17/03/99 			else
//DEADCODE JIM 17/03/99 			{	//more complex: load the battlefield and
//DEADCODE JIM 17/03/99 				//test for used fixed UID flag
//DEADCODE JIM 17/03/99 				UsedFixedUID=FALSE;
//DEADCODE JIM 17/03/99 				{
//DEADCODE JIM 17/03/99 					WorldStuff* wpbackup=myworld;
//DEADCODE JIM 17/03/99 ////					justscanning=SCANNAMES;
//DEADCODE JIM 17/03/99 					{
//DEADCODE JIM 17/03/99 						LoadSubPiece(NULL,(FileNum)bfnum,(int)Persons2::LOADEDBFS-1,SCANNAMES);
//DEADCODE JIM 17/03/99 					}
//DEADCODE JIM 17/03/99 					myworld=wpbackup;
//DEADCODE JIM 17/03/99 	////				justscanning=LOAD;
//DEADCODE JIM 17/03/99 				}
//DEADCODE JIM 17/03/99 				if (UsedFixedUID)
//DEADCODE JIM 17/03/99 					BITSET(usedevents,bfnum&255);
//DEADCODE JIM 17/03/99 			}
//DEADCODE JIM 17/03/99 		} while (bfnum==ENABLE_COMPLEX_VAL && count--);
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		int i=I->usedsetvals;
//DEADCODE JIM 17/03/99 		if (bfnum!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 		{
//DEADCODE JIM 17/03/99 			newevent=new EventRec (P,i+1);
//DEADCODE JIM 17/03/99 			newevent->eventlist[i].Index=EventSet::GV_EVENT_EVENT;
//DEADCODE JIM 17/03/99 			newevent->eventlist[i].Value=bfnum;
//DEADCODE JIM 17/03/99 		}
//DEADCODE JIM 17/03/99 		else
//DEADCODE JIM 17/03/99 			newevent=new EventRec (P,i);
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		int v1;
//DEADCODE JIM 17/03/99 		newevent->eventwstart=
//DEADCODE JIM 17/03/99 			newevent->eventwend=0;
//DEADCODE JIM 17/03/99 		if ((v1=I->starts.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwstart+=v1*100;
//DEADCODE JIM 17/03/99 		if ((v1=I->startm.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwstart+=v1*60*100;
//DEADCODE JIM 17/03/99 		if ((v1=I->starth.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwstart+=v1*60*60*100;
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		if ((v1=I->wins.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwend+=v1*100;
//DEADCODE JIM 17/03/99 		if ((v1=I->winm.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwend+=v1*60*100;
//DEADCODE JIM 17/03/99 		if ((v1=I->winh.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwend+=v1*60*60*100;
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 	
//DEADCODE JIM 17/03/99 		while (--i>=0)
//DEADCODE JIM 17/03/99 		{
//DEADCODE JIM 17/03/99 			newevent->eventlist[i].Index=I->setvals[i].index;
//DEADCODE JIM 17/03/99 			newevent->eventlist[i].Value=I->setvals[i].Evaluate();
//DEADCODE JIM 17/03/99 		}
//DEADCODE JIM 17/03/99 		if (newevent->eventwend)								//JIM 04Nov96
//DEADCODE JIM 17/03/99 			newevent->eventwend+=newevent->eventwstart+Timer_Code.realtime;
//DEADCODE JIM 17/03/99 		if (newevent->eventwstart)								//JIM 14Aug96
//DEADCODE JIM 17/03/99 			newevent->eventwstart+=Timer_Code.realtime;
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		I=(info_event_ptr)I->next;
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_setval
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::make_setval(EventVar& es)
{
	if (justscanning)
	{
		return;
	}
	SetLoc(es.index,es.Evaluate());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_string
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		t is one of:
//						T_comment	
//						T_name
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 extern	MissionType CustomMission;
//DEADCODE JIM 25/03/99 extern	char	CustomMissionDesc[];
//DEADCODE JIM 25/03/99 extern	char	CustomMissionNews[];
//DEADCODE JIM 25/03/99 extern	char	CustomMissionTitle[];


void	Persons3::make_string(string src,int len,TokenCode t)
{
//DEADCODE JIM 25/03/99 	MissionType*	M=&CustomMission;

	if (justscanning)
	{
		switch (t)
		{
			case T_comment:
//DEADCODE JIM 25/03/99 				if ((UWord&)CustomMissionDesc[0])
//DEADCODE JIM 25/03/99 				{
//DEADCODE JIM 25/03/99 					if (!(UWord&)CustomMissionNews[0])
//DEADCODE JIM 25/03/99 					{
//DEADCODE JIM 25/03/99 						CustomMissionNews[1]=1;
//DEADCODE JIM 25/03/99 						strncpy(CustomMissionNews,src,len);
//DEADCODE JIM 25/03/99 						CustomMissionNews[len]=0;
//DEADCODE JIM 25/03/99 					}
//DEADCODE JIM 25/03/99 				}
//DEADCODE JIM 25/03/99 				else
//DEADCODE JIM 25/03/99 				{
//DEADCODE JIM 25/03/99 					CustomMissionDesc[1]=1;
//DEADCODE JIM 25/03/99 					strncpy(CustomMissionDesc,src,len);
//DEADCODE JIM 25/03/99 					CustomMissionDesc[len]=0;
//DEADCODE JIM 25/03/99 				}
			break;
			case T_name:
//DEADCODE JIM 25/03/99 				strncpy(CustomMissionTitle,src,len);
//DEADCODE JIM 25/03/99 				CustomMissionTitle[len]=0;
			break;
			case T_family:
			{
//DEADCODE JIM 25/03/99 				char dummyc;
//DEADCODE JIM 25/03/99 				int	dummyi;
//DEADCODE JIM 25/03/99 				sscanf(src,
//DEADCODE JIM 25/03/99 					"%i %i "
//DEADCODE JIM 25/03/99 					"%hi %hi "
//DEADCODE JIM 25/03/99 					"%c %c "
//DEADCODE JIM 25/03/99 					"%hi %hi %hi "
//DEADCODE JIM 25/03/99 					"%hi %hi %hi "
//DEADCODE JIM 25/03/99 					"%hi %hi "
//DEADCODE JIM 25/03/99 					"%hi %hi "
//DEADCODE JIM 25/03/99 					"%hi %hi %hi"
//DEADCODE JIM 25/03/99 					,
//DEADCODE JIM 25/03/99 					&M->missiondate,&M->timeofday,
//DEADCODE JIM 25/03/99 					&M->numofsquadronac,&M->numofflightac,
//DEADCODE JIM 25/03/99 					&dummyc/*M->PlayerNationality*/,&M->formationtypeindex,
//DEADCODE JIM 25/03/99 					&M->weathernum,&M->windspeed,&M->winddirection,
//DEADCODE JIM 25/03/99 					&dummyi,&dummyi,&dummyi,	//&M->era,&M->region,&M->PlayerAcType,
//DEADCODE JIM 25/03/99 					&dummyi,&dummyi,			//&M->PlayerHomeBase,&M->EnemyHomeBase,
//DEADCODE JIM 25/03/99 					&M->wplist->wpset[0]->mainobjective,&M->wplist->wpset[0]->subobjective,
//DEADCODE JIM 25/03/99 					&M->wplist->wpset[0]->wp1,&M->wplist->wpset[0]->wp2,&M->wplist->wpset[0]->wp3
//DEADCODE JIM 25/03/99 					);
//DEADCODE JIM 25/03/99 				//M->PlayerNationality&=31;
//DEADCODE JIM 25/03/99 				M->formationtypeindex=FormationTypeIndex(M->formationtypeindex&31);
			}
			break;
		}
	}
}
Bool	Persons3::make_eventname(string src,int len,info_event&)
{
	return TRUE;
}
Bool	Persons3::make_agname(string src,int len,info_airgrp&)
{
	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		used_globref
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::used_globref(int index)
{

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	EXTRA ROUTINES ONLY USED BY make_ routines
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Position modifiers
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setangles
//Author		R. Hyde 
//Date			Mon 26 Feb 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons3::SetAngles (FormationItemPtr	newmob)
{

	if (newmob->formpos == 0)
		if ((int)newmob->waypoint!=-1)
			if ((int)newmob->waypoint->target!=-1 && !(newmob->waypoint->World.Y&0x40000000))
			{
				newmob->InterceptandRange (newmob->FindDesPos ());
				newmob->pitch= newmob->PitchIntercept;
				newmob->hdg	= newmob->HdgIntercept;
				if (newmob->roll == ANGLES_180Deg)
					newmob->roll = ANGLES_0Deg;
			}
			else
				logsetangles(newmob,newmob->waypoint->uniqueID.count);
		else
			logsetangles(newmob,newmob->uniqueID.count);
	else
		if (newmob->leader->pitch!=ANGLES_180Deg)
		{
			newmob->pitch = newmob->leader->pitch;
			newmob->hdg = newmob->leader->hdg;
			if (newmob->roll == ANGLES_180Deg)
				newmob->roll = ANGLES_0Deg;
		}
		else
			logsetangles(newmob,newmob->leader->uniqueID.count);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setangles
//Author		R. Hyde 
//Date			Mon 26 Feb 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons3::SetAngles (AirStrucPtr	newac)
{

	if (newac->formpos == 0)
		if ((int)newac->waypoint!=-1)
			if ((int)newac->waypoint->target!=-1 && !(newac->waypoint->World.Y&0x40000000))
			{
				newac->InterceptandRange (newac->FindDesPos ());
				newac->pitch= newac->PitchIntercept;
				newac->hdg	= newac->HdgIntercept;
				if (newac->roll == ANGLES_180Deg)
					newac->roll = ANGLES_0Deg;
			}
			else
				logsetangles(newac,newac->waypoint->uniqueID.count);
		else
			logsetangles(newac,newac->uniqueID.count);
	else
		if (newac->fly.leadflight->roll!=ANGLES_180Deg)
		{
			newac->pitch = newac->fly.leadflight->pitch;
			newac->hdg = newac->fly.leadflight->hdg;
			if (newac->roll == ANGLES_180Deg)
				newac->roll = ANGLES_0Deg;
		}
		else
			logsetangles(newac,newac->fly.leadflight->uniqueID.count);

	if (newac->vel == 0)											//RDH 04Sep96
	{															//RDH 04Sep96
		newac->fly.cpitch = ANGLES_0Deg;						//RDH 04Sep96
	}else
	{															//RDH 04Sep96
		newac->fly.cpitch = newac->pitch;
	}															//RDH 04Sep96
//	newac->fly.chdg = newac->hdg;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setfolloweroffset
//Author		Jim Taylor
//Date			Mon 22 Jan 1996
//
//Description	Set the offset position for a follower.
//
//Inputs		newac->formpos
//				If wing pos is non-zero then realive to leader
//				If wing pos is zero then relative to leadflight
//				newac->formation
//
//
//Returns		newac->world modified
//
//------------------------------------------------------------------------------
COORDS3D*	Persons3::setfolloweroffset(FormationItemPtr	newmob)
{
	newmob->HdgIntercept=newmob->hdg;							//AMM 19Aug97

	if (newmob->formpos != 0)
	{
		newmob->GetFollower_xyz ( newmob->formation);					//RDH 17Jun96

//		if (newmob->formation==FORM_EXPLODE					//AMM 19Aug97
//		|| newmob->formation==FORM_IMPLODE					//AMM 19Aug97
//		|| newmob->formation==FORM_RANDOM)					//AMM 19Aug97
			if (newmob->HdgIntercept!=newmob->hdg)					//AMM 19Aug97
			{													//AMM 19Aug97
			 	newmob->pitch=ANGLES_0Deg;						//AMM 19Aug97
				newmob->hdg=newmob->HdgIntercept;					//AMM 19Aug97
			}													//AMM 19Aug97

		return (&newmob->despos);
	}elser
	{
		return (NULL);
	}


}

COORDS3D*	Persons3::setfolloweroffset(AirStrucPtr	newac)
{
	COORDS3D	*despos;

//DeadCode RDH 27Feb96 	if (newac->pitch == ANGLES_180Deg)
//DeadCode RDH 27Feb96 		SetAngles (newac);
	newac->HdgIntercept=newac->hdg;
	if (newac->formpos != 0)
	{
		if (	(newac->leader && newac->leader->movecode == AUTO_TAKEOFF)
			||	(newac->fly.leadflight && newac->fly.leadflight->movecode == AUTO_TAKEOFF)	)
		{
			newac->pitch = newac->classtype->deckangle;			//JIM 04Dec96
//DeadCode JIM 27Nov96 			newac->pitch=ANGLES_5Deg;
			newac->movecode=AUTO_TAKEOFF;
			newac->vel = 0;										//RDH 30Sep96
			newac->fly.vel_cms = 	0;							//RDH 30Sep96
//			newac->fly.vel_mms = 	0;							//RDH 30Sep96
			return (newac->PositionTakeOffWRTLeader ());
		}else
		{
			despos=newac->PositionWRTLeader();					//AMM 19Aug97

//			if (newac->formation==FORM_EXPLODE					//AMM 19Aug97
//			|| newac->formation==FORM_IMPLODE					//AMM 19Aug97
//			|| newac->formation==FORM_RANDOM)					//AMM 19Aug97
				if (newac->hdg!=newac->HdgIntercept)
				{
					newac->hdg=newac->HdgIntercept;
					newac->pitch=ANGLES_0Deg;
				}
			return despos;										//AMM 19Aug97
//DeadCode AMM 20Aug97 			return (newac->PositionWRTLeader ());
		}
	}elser
	{
		if (newac->movecode==AUTO_TAKEOFF)
		{
//rdh			newac->hdg = MMC.wind.direction;				//RDH 02Aug96
			newac->pitch = newac->classtype->deckangle;			//JIM 04Dec96
			newac->roll = ANGLES_0Deg;
			newac->vel = 0;										//RDH 30Sep96
			newac->fly.vel_cms = 	0;							//RDH 30Sep96
//			newac->fly.vel_mms = 	0;							//RDH 30Sep96
			return NULL;
		}	
		else
		if (newac->fly.leadflight)
			return	newac->PositionWRTLeader();
		else
			return (NULL);											//RDH 17Jun96
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	UID forward reference fixup 
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setposition
//Author		Jim Taylor
//Date			Tue 17 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Persons3::setfollowerposition(AirStrucPtr it)
{
	if (it->fly.leadflight && it->fly.leadflight->pitch==ANGLES_180Deg)
	{
	 	logsetangles(it,it->fly.leadflight->uniqueID.count,followaccopy);
		return;
	}
	Coords3D* dp=setfolloweroffset(it);
	assert (dp);
	it->World=*dp;	//*setfolloweroffset(it);						  //JIM 25/04/99
	assert(it->fly.leadflight);
	if (it->fly.leadflight->World.Y&0x40000000)
		logworldcopy(it,it->fly.leadflight->uniqueID.count,TRUE);
	else
	 	AddToWorld(*it);
}
void Persons3::setfollowerposition(FormationItemPtr it)
{
	if (it->leader && it->leader->pitch==ANGLES_180Deg)
	{
	 	logsetangles(it,it->leader->uniqueID.count,followmobcopy);
		return;
	}
	it->World=*setfolloweroffset(it);
	assert(it->leader);
	if (it->leader->World.Y&0x40000000)
		logworldcopy(it,it->leader->uniqueID.count,TRUE);
	else
	 	AddToWorld(*it);
}

Bool Persons3::setposition( ItemBase* it, EventVal& pos, Bool addtoworld)
{
	UniqueID	rv=pos.EvalW(it->World);
	if ((rv) && (rv != IllegalSepID))
		logworldcopy(it,rv,pos,addtoworld);
	else
	{
		if (addtoworld)
			if (it->Status.size!=WayPointSize)
	 			AddToWorld(*it);
		int dy;
		if ((dy=it->World.Y) < 0)								//RDH 17Jun96
		{														//RDH 17Jun96
			it->World.Y =  Land_Scape.GetGroundLevel(it)	//RDH 17Jun96
										- it->World.Y;		//RDH 17Jun96
		//PAUL'S NEW ROUTINE RETURNS DELTA TO GROUND
		//	This is delta from given alt to ground level
		//  given is N below sea level
		//	I want abs above sea = ground + |given| = ground -given
		// this is paul's returned value!!! (Ok, so I'm lazy! :-)
		//	position.pos.Y =
		//		tmpitem->World.Y = -Land_Scape.GetGroundDelta(tmpitem);
			if (dy<-600)
				return(FALSE);
			else
				return(TRUE);
		}
	}
	return (FALSE);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setpointer
//Author		Jim Taylor
//Date			Fri 12 Jan 1996
//
//Description	Set the pointer to the item with the uid.
//				If the item does not yet exist then the 
//				pointer is noted until the UID is available.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void		Persons3::setpointer(ItemBasePtr	*targitemptr,UniqueID	srcuid)
{
	if ((*targitemptr=ConvertPtrUID(srcuid))==0)
		logpointercopy(targitemptr,srcuid);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		searchtree
//Author		Robert Slater
//Date			Tue 13 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UidNode**	Persons2::searchtree(UniqueID srcuid,UidNode **nextnode)
{
	UidNode		*currentnode,
				**currnodeptr=nextnode;

		while(*nextnode)
		{
			currnodeptr=nextnode;
			currentnode = *nextnode;

			if (srcuid == currentnode->uidattack)
				return(nextnode);

			if (srcuid < currentnode->uidattack)
				nextnode = &currentnode->less;
			else
				nextnode = &currentnode->more;

		}

		return(currnodeptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		adduidrequest
//Author		Robert Slater
//Date			Tue 13 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::adduidrequest(ItemBasePtr *trgitemptr,UniqueID srcuid)
{
	UidNode		*newnode = new UidNode;

	newnode->uidattack = srcuid;
	newnode->attackerptr = trgitemptr;
	newnode->request = ptrcopy;
	newnode->less = NULL;
	newnode->more = NULL;
	adduidrequest(newnode,srcuid);

}
void	Persons3::adduidrequest(ItemBasePtr trgitemptr,UniqueID srcuid,EventVal& pos,UILogType request)
{
	UidNode		*newnode = new UidNode;
	newnode->posexpr = pos;
	newnode->uidattack = srcuid;
	newnode->posptr = trgitemptr;
	newnode->request = request;
	newnode->less = NULL;
	newnode->more = NULL;
	adduidrequest(newnode,srcuid);


}
void	Persons3::adduidrequest(ItemBasePtr trgitemptr,UniqueID srcuid,UILogType request)
{
	UidNode		*newnode = new UidNode;

	newnode->uidattack = srcuid;
	newnode->posptr = trgitemptr;
	newnode->request = request;
	newnode->less = NULL;
	newnode->more = NULL;
	adduidrequest(newnode,srcuid);
}

void	Persons3::adduidrequest(UidNode *newnode,UniqueID srcuid)
{
	UidNode	  **foundnode, *thenode;
	assert (srcuid);
	assert (srcuid==newnode->uidattack);
	if (rootuidnode == NULL)
	{
		rootuidnode = newnode;
	}
	else
	{
		// Search down the tree to correct node...

		foundnode = searchtree(srcuid);
		thenode = *foundnode;

		// Select branch...

		if (srcuid == thenode->uidattack)
		{
			//add to end of similar requests
			while (thenode->more && thenode->more->uidattack==srcuid)
				thenode=thenode->more;
			// Add to the greater node, and shuffle if it is occupied
			newnode->more = thenode->more;
			thenode->more = newnode;
			
		}
		else
		{
			// Must be less than or greater than, so no problem

			if (srcuid < thenode->uidattack)
				thenode->less = newnode;
			else
				thenode->more = newnode;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		logpointercopy
//Author		Jim Taylor
//Date			Fri 12 Jan 1996
//
//Description	Logs that the given item pointer needs fixing up when the
//				given unique id item is loaded.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::logpointercopy(ItemBasePtr *trgitemptr,UniqueID srcuid)
{
	UILogType	request = ptrcopy;
   
	adduidrequest(trgitemptr,srcuid);

	*trgitemptr=(ItemBasePtr)-1;

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		logworldcopy
//Author		Jim Taylor
//Date			Mon 8 Jan 1996
//
//Description	Logs data transfer to happen when source item is loaded
//				If 'addwhenfilled' is set then item is added to world when data
//				transfer is complete.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::logworldcopy(ItemBasePtr targitem,UniqueID srcUID,Bool	addwhenfilled)
{
	targitem->World.Y|=0x40000000;
	EventVal	tmp;
	UILogType	request = worldcopy;

	if (addwhenfilled)
		request = addworldcopy;
	if (srcUID==0)
		_Error.EmitSysErr("Asked for zero UID source");
	adduidrequest(targitem,srcUID,request);
}
void	Persons3::logworldcopy(ItemBasePtr targitem,UniqueID srcUID,EventVal& pos,Bool	addwhenfilled)
{
	targitem->World.Y|=0x40000000;
	UILogType	request = worldcopy;

	if (addwhenfilled)
		request = addworldcopy;
	if (srcUID==0)
		_Error.EmitSysErr("Asked for zero UID source");

	adduidrequest(targitem,srcUID,pos,request);
}

void	Persons3::logsetangles(AirStrucPtr targitem,UniqueID srcUID)
{
	logsetangles(targitem,srcUID,anglesaccopy);
}

void	Persons3::logsetangles(FormationItemPtr targitem,UniqueID srcUID,UILogType request)
{
	adduidrequest(targitem,srcUID,request);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		logUID
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	puts item in uid lookup and sets pointers
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::logUID(ItemBasePtr	selecteditem)
{
	UniqueID		theuid;

	theuid = selecteditem->uniqueID.count;

	assert(pItem[theuid]==NULL&&"UID already used!");
	assert(pItem[theuid]==0&&"Reused!");
	pItem[theuid] = selecteditem;
}

Bool	Persons3::useUID(ItemBasePtr	selecteditem)
{
	return useUID(selecteditem,selecteditem->uniqueID.count);
}

Bool	Persons3::useUID(ItemBasePtr	selecteditem,UniqueID theuid)
{

	UidNode			*swapnode, **foundnode, *thenode, *nextnode, **rightmostnode;
	Bool			finished = FALSE;
	ItemBasePtr		*attackerptr;
	UILogType	 	request;
	Bool	retval=FALSE;

	while(!finished)
	{
		finished = TRUE;
		foundnode = searchtree(theuid);

		thenode = *foundnode;
		Bool	skippedone;
		do{
			skippedone=FALSE;
			if (	thenode	&&	thenode->uidattack==theuid	)
			{
				if ( 	(	thenode->request==worldcopy
						||	thenode->request==addworldcopy
						)
					&&	(	selecteditem->World.Y&0x40000000
						||	(	selecteditem->Status.size==WAYPOINTSIZE
							&&	(int)((WayPoint*)*selecteditem)->target==-1
					)	)	)
				{
					foundnode=&foundnode[0]->more;
					thenode = *foundnode;
					skippedone=TRUE;
				}
				else											//JIM 22Oct97
				if	(	thenode->request==anglesaccopy
					||	thenode->request==anglesmobcopy
					||	thenode->request==followaccopy
					||	thenode->request==followmobcopy
					)
					if (	(	selecteditem==thenode->posptr
							&&	(int)((FormationItem*)*selecteditem)->waypoint==-1
							)
						|| 	(	selecteditem!=thenode->posptr
							&&	(	(	selecteditem->Status.size==WAYPOINTSIZE
									&& 	(	(selecteditem->World.Y&0x40000000)
										||	(int)(((WayPoint*)*selecteditem)->target)==-1
									)	)
								||	(	(selecteditem->Status.size==ITEMSIZE)
									&&	(selecteditem->World.Y&0x40000000)
									)
								||	(	(selecteditem->Status.size>=MOBILESIZE)
									&& (((MobileItem*)*selecteditem)->pitch==ANGLES_180Deg)
						)	)	)	)
					{
						foundnode=&foundnode[0]->more;
						thenode = *foundnode;
						skippedone=TRUE;
					}
			}
		}while (skippedone);

		if (thenode)
			if (thenode->uidattack == theuid)
			{
				finished = FALSE;

				// Extract data...

				retval=TRUE;
				request = thenode->request;

				switch (request)
				{
				case ptrcopy :
				{
					attackerptr = thenode->attackerptr;
					*attackerptr = selecteditem;
				}
				break;
				case followaccopy:
				{
					setfollowerposition((AirStrucPtr)*thenode->posptr);
				}
				break;
				case followmobcopy:
				{
					setfollowerposition((FormationItemPtr)*thenode->posptr);
				}
				break;
				case anglesaccopy:
				{
					SetAngles((AirStrucPtr)*thenode->posptr);
				}
				break;
				case anglesmobcopy:
				{
					SetAngles((FormationItem*)*thenode->posptr);
				}
				break;
				case worldcopy :
				case addworldcopy :
				{
					Coords3D	t;

					UniqueID rv=UID_Null;
					if (thenode->posexpr.complex)
						rv=thenode->posexpr.EvalW(t);
					else
						t=selecteditem->World;
					if (rv)
					{	//need to put this expression back into to-do list!
						//but can take old one out...
						if (rv==thenode->uidattack)
							_Error.EmitSysErr("Forward reference fixup gone recursive!");

						adduidrequest(thenode->posptr,rv,thenode->posexpr,request);
					}
					else
					{
						thenode->posptr->World.Y &=~0x40000000;
						thenode->posptr->World.X =
							thenode->posptr->World.X + t.X;
						thenode->posptr->World.Y =
							thenode->posptr->World.Y + t.Y;
						thenode->posptr->World.Z =
							thenode->posptr->World.Z + t.Z;

						if (request == addworldcopy)
							AddToWorld(*thenode->posptr);
					}
				}
				break;
				}

			
				// Tidy tree...

				nextnode = thenode->more;

				if (thenode->less)
				{
					swapnode = thenode->less;

					rightmostnode = searchtree(theuid,&swapnode);

					(*rightmostnode)->more = nextnode;
				}
				else
				{
					swapnode = thenode->more;
				}

				*foundnode = swapnode;

				delete thenode;

			}
	}
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		anyoutstanding
//Author		Robert Slater
//Date			Thu 15 Feb 1996
//
//Description	Checks if any outstanding UIDs on the tree.
//				If there are, we try to fix them up properly.
//
//				If there are still some left the return TRUE so the caller can raise an error code
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------

Bool	Persons3::recurseanyoutstanding(UidNode* node)
{
	UniqueID	nextatt=node->uidattack;
	ItemBasePtr	B=ConvertPtrUID(nextatt);
	if (!B)
		return FALSE;
	if (useUID(B))
		return TRUE;
	if (node->less)
		if (recurseanyoutstanding(node->less))
			return TRUE;
	if (node->more)
		if (recurseanyoutstanding(node->more))
			return TRUE;
	return FALSE;
}

Bool	Persons3::anyoutstanding()
{
	while (rootuidnode!=NULL)
		if (!recurseanyoutstanding(rootuidnode))
			return TRUE;										//JIM 10Sep97
	return FALSE;												//JIM 10Sep97
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	UID/World interface
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

void Persons3::InitGamePiece()
{
//DEADCODE DAW 12/05/99 	File_Man.DiscardDirList(FIL_RUNTIMEPACK0);
	for (int i=0;i<LOADEDBFS;i++)
		loadedBF[i]=FIL_NULL;

	if (_Replay.Playback)
	{
		Pack_PlayerSquad=_Replay.PlayerSquad;
		Pack_PlayerPos=_Replay.PlayerPos;
		MMC.playersquadron=_Replay.PlayerSquad;					//AMM 17Nov98
		MMC.playeracnum=_Replay.PlayerPos;						//AMM 17Nov98
	}
	else
	{
		Pack_PlayerSquad=MMC.playersquadron;
		Pack_PlayerPos=MMC.playeracnum;
	}

	for (i=0;i<MAXCALLNAMES;i++)
		callsignnamecount[i]=1;
    ClearGlobrefStaticVars();
	while (eventloglist)
	{
		EventLogPtr	tmp=eventloglist;
		eventloglist=tmp->next;
		delete tmp;
	}

//	ClrMessage(UserMsg::NOMSG);									//JIM 23Oct96

	for (i=0;i<32;i++)
		usedevents[i]=0;
	mobileitem::MobileList=NULL;
	mobileitem::ACList=NULL;
	TransientItem::TransientList=NULL;							//PD 11May96
	Art_Int.CleanUp();
	Manual_Pilot.ControlledAC2=NULL;							//JIM 04Sep97
//	GR_EnemyScoutSquad=											//RDH 15Sep97
//		GR_FriendlyScoutSquad=
//			GR_EnemyChargeSquad=
//				GR_FriendlyChargeSquad=JastaAnon;
			
}
void	Persons3::InitSubPiece()
{
	if (!justscanning)
	{
		firstobject=IllegalSepID;
		eventloglist=new EventLog(eventloglist);
	   if (inst3d)
		eventloglist->launchtime=inst3d->timeofday;
///		eventloglist->launchtime=Timer_Code.realtime;
		shapefield=new ShapeNumField;
	}
}
void Persons3::EndSubPiece()
{
	if (!justscanning)
	{
		AddPreLoadFXShapes();									//RJS 02Apr99

		SHAPESTUFF.AddShapesToGlobList(shapefield);
		delete shapefield;
		shapefield=NULL;
	}
}
  
void Persons3::FinishSetPiece()
{
	GR_TruckMoveCode=GROUND_TOGLOBREF;


	SLong len;
	UWord oldsector;

	//get airfield altitudes loaded. This causes too much grief otherwise
	for (int afnum=0;SupplyTree::airfieldinfo[afnum].nationality!=NAT_ALIGN;afnum++)
	{
		ItemPtr I=*ConvertPtrUID(SupplyTree::airfieldinfo[afnum].airfield);
		if (I->World.Y==0)
			I->World.Y=Land_Scape.GetGroundLevel(I,NULL,true);
	}


	if (_DPlay.Implemented)
	{
		_DPlay.SendBFieldsToPlayers(false);
	}

//DeadCode AMM 17Nov98 //	if (_Replay.Record)
//DeadCode AMM 17Nov98 		_Replay.AddFileAndGlobRefsToList(FIL_NULL);

	if (!_Replay.Playback)
		SENT_REQ=FALSE;
	if (anyoutstanding())
		_Error.EmitSysErr("Unresolved UIDS! One is: %x",rootuidnode->uidattack);

//	if(Miss_Man.camp.playerbfield!=FIL_NULL)
//	{
		if (!Manual_Pilot.ControlledAC2)							//JIM 04Sep97
			_Error.EmitSysErr("No player A/C set up on entering 3d!");//JIM 04Sep97
//	}

// create extra instance of Airstruc, if one does not already exist.

// GhostAC is one used by AI. 
// SeenAC is one seen and moved by player.

// Deltas sent are difference between predictor and actual movement

//	WorldStuff &world = mobileitem::GetWorld();

	if(Persons2::PlayerGhostAC==Persons2::PlayerSeenAC)								//JIM 12Sep97
	{
		AirStrucPtr newac=new AirStruc;

		if (newac==NULL)
			_Error.SayAndQuit("could not create newac");

		DeleteModel(newac);				//newac->fly.pModel;
		newac->fly.pModel=NULL;				   // DeleteModel

		Persons2::PlayerSeenAC=newac;
		newac=NULL;
		
	}

//DeadCode AMM 23Jul98 	if (_Replay.Playback)
//DeadCode AMM 23Jul98 	{
//DeadCode AMM 23Jul98 		Manual_Pilot.controlmode==ManualPilot::AUTO;
//DeadCode AMM 23Jul98 	}

	Persons2::PlayerGhostAC=Manual_Pilot.ControlledAC2;

// both AC start off the same

	_DPlay.CopyBuffer((char*)Persons2::PlayerSeenAC,(char*)Persons2::PlayerGhostAC,sizeof(AirStruc));

	Manual_Pilot.ControlledAC2=Persons2::PlayerSeenAC;

	Persons2::PlayerGhostAC->fly.pModel=NULL;
	Persons2::PlayerGhostAC->Anim=NULL;

	Persons2::PlayerSeenAC->AddToList();
	
	if (!Art_Int.Remove(Persons2::PlayerSeenAC))
		_Error.SayAndQuit("Cant remove seenac");

// remove ghost from sectorlist and add seen

	myworld->RemoveFromWorld(Persons2::PlayerGhostAC);
	myworld->AddToWorld(Persons2::PlayerSeenAC);

// need to remove ghostac from aclist 

	AirStrucPtr Me = *AirStruc::ACList;

	if (Me==Persons2::PlayerGhostAC)
	{
		AirStruc::ACList=*Me->nextmobile;
	}
	else
	{
		while (Me && Me->nextmobile!=Persons2::PlayerGhostAC)
		{
			Me=*Me->nextmobile;
		}

		if (Me)
		{
			Me->nextmobile=Me->nextmobile->nextmobile;
		}
		else
			_Error.SayAndQuit("cant remove ac from aclist");
	}
	
// nobble UID pointer!							 

	pItem[Persons2::PlayerGhostAC->uniqueID.count]=NULL;

	logUID(Persons2::PlayerSeenAC);

/// move to after mobileitem::world has been set up

//DeadCode AMM 19Nov98 // record or playback from beginning?	
//DeadCode AMM 19Nov98 																	 
//DeadCode AMM 19Nov98 	if (_Replay.Record)
//DeadCode AMM 19Nov98 	{
//DeadCode AMM 19Nov98 		_Replay.StoreFinalRecordData();
//DeadCode AMM 19Nov98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 		_Replay.Record=FALSE;
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 		Timer_Code.msgcounttime=0; // reset rounding
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 		if (_Replay.StoreFileAndGlobRefList())
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 			if (_Replay.StorePilots())
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 				if (_Replay.StoreItemAnims())
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 					if (_Replay.StoreItemData())
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 						if (_Replay.StoreInitFrameCounts())
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 						{
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 // in this case beginning of file is 0, so current pos is length of header
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 	
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 							if (_Replay.StoreHeaderLength(0))
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 								_Replay.Record=TRUE;
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 						}
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 		if (!_Replay.Record)
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 			_Error.EmitSysErr("Error writing to record log");
//DeadCode AMM 19Nov98 	}
//DeadCode AMM 19Nov98 	else
//DeadCode AMM 19Nov98 	if (_Replay.Playback)
//DeadCode AMM 19Nov98 	{
//DeadCode AMM 19Nov98 		_Replay.LoadFinalPlaybackData();
//DeadCode AMM 19Nov98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 		_Replay.Playback=FALSE;
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 		Timer_Code.msgcounttime=0; // reset rounding
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 		if (_Replay.LoadPilots())
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 			if (_Replay.LoadItemAnims())
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 				if (_Replay.LoadItemData())
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 					if (_Replay.LoadFrameCounts())
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 					{
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 						ULong n;
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 						n=_Replay.LoadHeaderLength();
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98  						if (n!=0)
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98  						{
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98  							_Replay.headlength[_Replay.numblocks++]=n;
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98  							_Replay.currblock++;
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98  							_Replay.Playback=TRUE;
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98  						}
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98  					}
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 		if (!_Replay.Playback)
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 			_Error.EmitSysErr("Error reading playback log");
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 
//DeadCode AMM 19Nov98 //DeadCode AMM 01Oct98 		Manual_Pilot.controlmode=ManualPilot::AUTO;
//DeadCode AMM 19Nov98 
//DeadCode AMM 19Nov98 		if (!_Replay.Playback)
//DeadCode AMM 19Nov98 			_Error.EmitSysErr("Error reading playback log");
//DeadCode AMM 19Nov98	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToWorld
//Author		Jim Taylor
//Date			Mon 8 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void		Persons3::AddToWorld(ItemPtr	tmpitem)
{
 //	#pragma message("Persons3::AddToWorld - Don't forget to take this out!")
 //	if ((tmpitem->Status.size==AirStrucSize) || (tmpitem->shape == KIMPO))
 //	{	//1M=10km	- .5m=5km
//TempCode RDH 20Apr98  		tmpitem->World.X=(tmpitem->World.X&0x3ffff)+0x5000000;
//TempCode RDH 20Apr98  		tmpitem->World.Z=(tmpitem->World.Z&0x3ffff)+0x3000000;
//DeadCode DAW 28Apr98  		tmpitem->World.X=(tmpitem->World.X&0x3ffff)+0x2600000;
//DeadCode DAW 28Apr98  		tmpitem->World.Z=(tmpitem->World.Z&0x3ffff)+0x5400000;
//TempCode MS 11May98  		tmpitem->World.X=(tmpitem->World.X&0x3ffff)+0x2600000;
//TempCode MS 11May98  		tmpitem->World.Z=(tmpitem->World.Z&0x3ffff)+0x5400000-0x200000-0x40000;

 //	}
	myworld->AddToWorld(tmpitem);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Event run-time stuff
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PossibleEvent
//Author		Jim Taylor
//Date			Wed 20 Mar 1996
//
//Description	Execute any event associated with this item
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//extern	ULong	GR_CWP,GR_CPP;
//DEADCODE JIM 17/03/99 Bool		Persons3::PossibleEvent(WorldStuff *worldptr,ItemBasePtr target,ItemBasePtr actor)
//DEADCODE JIM 17/03/99 {
//DEADCODE JIM 17/03/99 	if (target)
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 		FileNum	eventbf=INVALIDFILENUM;
//DEADCODE JIM 17/03/99 		EventRecPtr	evind=EventRec::eventbase;
//DEADCODE JIM 17/03/99 		while (evind)
//DEADCODE JIM 17/03/99 		{
//DEADCODE JIM 17/03/99 			if (evind->attitem==target && Timer_Code.realtime>=evind->eventwstart)
//DEADCODE JIM 17/03/99 			{
//DEADCODE JIM 17/03/99 				EventRecPtr	tmpnext=evind->eventlink;
//DEADCODE JIM 17/03/99 				//need start/window tests here!
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 				//need to set GR_CPP,GR_CWP
//DEADCODE JIM 17/03/99 				GR_CWP=target->uniqueID.count;
//DEADCODE JIM 17/03/99 				GR_CPP=actor->uniqueID.count;
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 				eventbf=ActionEvent(evind,mobileitem::currworld,target);
//DEADCODE JIM 17/03/99 				if (eventbf!=INVALIDFILENUM)
//DEADCODE JIM 17/03/99 				{
//DEADCODE JIM 17/03/99 					lastbfloaded=eventbf;
//DEADCODE JIM 17/03/99 					lasttarg=target;
//DEADCODE JIM 17/03/99 					lastact=actor;
//DEADCODE JIM 17/03/99 //DeadCode JIM 12Aug96 					LoadSubPiece(worldptr,eventbf);
//DEADCODE JIM 17/03/99 //DeadCode JIM 12Aug96 					assert(!anyoutstanding()&&"Sub event not complete!");
//DEADCODE JIM 17/03/99 //DeadCode RDH 11Oct96 					if (Save_Data.gamedifficulty[GD_TACTICALRANGE])
//DEADCODE JIM 17/03/99 //DeadCode RDH 11Oct96 					{
//DEADCODE JIM 17/03/99 //DeadCode RDH 11Oct96 						Timer_Code.AccelToggle(FALSE);
//DEADCODE JIM 17/03/99 //DeadCode RDH 11Oct96 						Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);
//DEADCODE JIM 17/03/99 //DeadCode RDH 11Oct96 					}
//DEADCODE JIM 17/03/99 					return TRUE;
//DEADCODE JIM 17/03/99 				}
//DEADCODE JIM 17/03/99 				evind=tmpnext;
//DEADCODE JIM 17/03/99 			}
//DEADCODE JIM 17/03/99 			else
//DEADCODE JIM 17/03/99 				evind=evind->eventlink;
//DEADCODE JIM 17/03/99 		}
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 	else
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 		if (lastbfloaded)
//DEADCODE JIM 17/03/99 		{
//DEADCODE JIM 17/03/99 		 	LoadSubPiece(mobileitem::currworld,lastbfloaded,currbfindex+1);
//DEADCODE JIM 17/03/99 //			if (	lasttarg->Status.size==WayPointSize
//DEADCODE JIM 17/03/99 //				&&	((WayPointPtr)*lasttarg)->target
//DEADCODE JIM 17/03/99 //				)
//DEADCODE JIM 17/03/99 //				eventloglist->area=_Text.ConvSnip0(((WayPointPtr)*lasttarg)->target->uniqueID.count);
//DEADCODE JIM 17/03/99 			lastbfloaded=FIL_NULL;
//DEADCODE JIM 17/03/99 			if (anyoutstanding())
//DEADCODE JIM 17/03/99 				_Error.EmitSysErr("Unresolved UIDS! One is: %x",rootuidnode->uidattack);
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 //DeadCode JIM 22Oct96 NEVER WANT TO QUIT ACCEL HERE
//DEADCODE JIM 17/03/99 //DeadCode JIM 22Oct96 
//DEADCODE JIM 17/03/99 //DeadCode JIM 22Oct96 			if (Save_Data.gamedifficulty[GD_TACTICALRANGE])		//RDH 11Oct96
//DEADCODE JIM 17/03/99 //DeadCode JIM 22Oct96 			{
//DEADCODE JIM 17/03/99 //DeadCode JIM 22Oct96 				Timer_Code.AccelToggle(FALSE);
//DEADCODE JIM 17/03/99 //DeadCode JIM 22Oct96 				Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);
//DEADCODE JIM 17/03/99 //DeadCode JIM 22Oct96 			}
//DEADCODE JIM 17/03/99 //DeadCode JIM 30Nov96 			AddMessage(UserMsg::TIME,TextSnip0MIN,
//DEADCODE JIM 17/03/99 //DeadCode JIM 30Nov96 				ConvertPtrUID(eventloglist->targetuid));
//DEADCODE JIM 17/03/99 			if (lasttarg)
//DEADCODE JIM 17/03/99 			{
//DEADCODE JIM 17/03/99 				target=lasttarg;
//DEADCODE JIM 17/03/99 				lasttarg=NULL;
//DEADCODE JIM 17/03/99 				PossibleEvent(mobileitem::currworld,target,lastact);
//DEADCODE JIM 17/03/99 				return TRUE;
//DEADCODE JIM 17/03/99 			}
//DEADCODE JIM 17/03/99 		}
//DEADCODE JIM 17/03/99 		else
//DEADCODE JIM 17/03/99 		{	//Look for timed out events on player's waypoint	//JIM 14Aug96
//DEADCODE JIM 17/03/99 			MobileItemPtr a=*actor;
//DEADCODE JIM 17/03/99 			target=a->waypoint;
//DEADCODE JIM 17/03/99 			FileNum	eventbf=INVALIDFILENUM;
//DEADCODE JIM 17/03/99 			EventRecPtr	evind=EventRec::eventbase;
//DEADCODE JIM 17/03/99 			while (evind)
//DEADCODE JIM 17/03/99 			{
//DEADCODE JIM 17/03/99 				if (evind->eventwend && evind->attitem==target && Timer_Code.realtime>=evind->eventwend)
//DEADCODE JIM 17/03/99 				{
//DEADCODE JIM 17/03/99 					EventRecPtr	tmpnext=evind->eventlink;
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 					//need to set GR_CPP,GR_CWP
//DEADCODE JIM 17/03/99 					GR_CWP=target->uniqueID.count;
//DEADCODE JIM 17/03/99 					GR_CPP=actor->uniqueID.count;
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 					eventbf=ActionEvent(evind,mobileitem::currworld,target);
//DEADCODE JIM 17/03/99 					if (eventbf!=INVALIDFILENUM)
//DEADCODE JIM 17/03/99 					{
//DEADCODE JIM 17/03/99 						lastbfloaded=eventbf;
//DEADCODE JIM 17/03/99 						lasttarg=target;
//DEADCODE JIM 17/03/99 						lastact=actor;
//DEADCODE JIM 17/03/99 //DeadCode JIM 12Aug96 					LoadSubPiece(worldptr,eventbf);
//DEADCODE JIM 17/03/99 //DeadCode JIM 12Aug96 					assert(!anyoutstanding()&&"Sub event not complete!");
//DEADCODE JIM 17/03/99 //DeadCode RDH 11Oct96 						Timer_Code.AccelToggle(FALSE);
//DEADCODE JIM 17/03/99 //DeadCode RDH 11Oct96 						Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);
//DEADCODE JIM 17/03/99 						return TRUE;
//DEADCODE JIM 17/03/99 					}
//DEADCODE JIM 17/03/99 					evind=tmpnext;
//DEADCODE JIM 17/03/99 				}
//DEADCODE JIM 17/03/99 				else
//DEADCODE JIM 17/03/99 					evind=evind->eventlink;
//DEADCODE JIM 17/03/99 			}
//DEADCODE JIM 17/03/99 		}
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 	return FALSE;
//DEADCODE JIM 17/03/99 }
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JIM 17/03/99 //Procedure		ActionEvent
//DEADCODE JIM 17/03/99 //Author		Jim Taylor
//DEADCODE JIM 17/03/99 //Date			Fri 29 Mar 1996
//DEADCODE JIM 17/03/99 //
//DEADCODE JIM 17/03/99 //Description	
//DEADCODE JIM 17/03/99 //
//DEADCODE JIM 17/03/99 //Inputs		
//DEADCODE JIM 17/03/99 //
//DEADCODE JIM 17/03/99 //Returns	
//DEADCODE JIM 17/03/99 //
//DEADCODE JIM 17/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 17/03/99 FileNum		Persons3::ActionEvent(EventRecPtr	evind,WorldStuff *worldptr,ItemBasePtr target)
//DEADCODE JIM 17/03/99 {
//DEADCODE JIM 17/03/99 	FileNum	eventbf=INVALIDFILENUM;
//DEADCODE JIM 17/03/99 	int	els=evind->eventlistsize;
//DEADCODE JIM 17/03/99 	while (els--)
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 		if (evind->eventlist[els].Index>=0)
//DEADCODE JIM 17/03/99 			SetLoc(evind->eventlist[els].Index,evind->eventlist[els].Value);
//DEADCODE JIM 17/03/99 		elseif (evind->eventlist[els].Index==evind->eventlist[els].GV_EVENT_EVENT)
//DEADCODE JIM 17/03/99 			eventbf=(FileNum)evind->eventlist[els].Value;
//DEADCODE JIM 17/03/99 		elseif (evind->eventlist[els].Index==evind->eventlist[els].GV_EVENT_NEST)
//DEADCODE JIM 17/03/99 			if (eventbf!=INVALIDFILENUM)
//DEADCODE JIM 17/03/99 				ActionEvent(evind->eventlist[els].Nesting,mobileitem::currworld,target);
//DEADCODE JIM 17/03/99 			else
//DEADCODE JIM 17/03/99 				eventbf=ActionEvent(evind->eventlist[els].Nesting,mobileitem::currworld,target);
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 	delete evind;
//DEADCODE JIM 17/03/99 	return(eventbf);
//DEADCODE JIM 17/03/99 }



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Colour schemes: also sets up piloted A/C
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//typedef void (*ha)(AirStrucPtr,FormationIndex,UByte* colours);
//ha	Persons3::Colour_Rule_List[]
//		={
//			&Persons3::ColourRulePlayerSquadron,
//			&Persons3::ColourRulePlayerAuto,
//			&Persons3::ColourRulePaintShop,
//			&Persons3::ColourRuleAllRandom,
//			&Persons3::ColourRuleDefined,
//		};
  //
	//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ColourRules
//Author		Jim
//Date			Sun 7 Apr 1996
//
//Description	Various coded methods for colouring squadrons.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void	Persons3::ColourRuleAllRandom(AirStrucPtr	newac,FormationIndex formtype,UByte* s)
//{
//	if (SHAPE.SetAnimData(newac,0)!=sizeof(AircraftAnimData))	//DAW 12May98... 0 is weapon pack
//		_Error.EmitSysErr("Animation not aircraft");
//	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
//	anim->imagemaptail=Math_Lib.rnd(8);
//	anim->imagemapbtmwing=Math_Lib.rnd(8);
//	anim->imagemapfuselage=Math_Lib.rnd(8);
//	anim->imagemapother=Math_Lib.rnd(8);
//	anim->imagemaptopwing=Math_Lib.rnd(8);
//	anim->imagemapemblem=Math_Lib.rnd(8);
//	Manual_Pilot.InitManualPilotSub(newac);			//rdh 9/6

//	anim->dammageflags=*(UWord*)&s[COLS_DAMAGE];
//}
//void	Persons3::ColourRuleDefined(AirStrucPtr	newac,FormationIndex formpos,UByte* selection)
//{
//	if (SHAPE.SetAnimData(newac,0)!=sizeof(AircraftAnimData))	//DAW 12May98... 0 is weapon pack
//		_Error.EmitSysErr("Animation not aircraft");
//	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
//	anim->imagemaptail=selection[1];
//	anim->imagemapbtmwing=selection[4];
//	anim->imagemapfuselage=selection[0];
//	anim->imagemapother=selection[2];
//	anim->imagemaptopwing=selection[3];
//	anim->imagemapemblem=selection[5];
//	Manual_Pilot.InitManualPilotSub(newac);			//rdh 9/6
//	anim->dammageflags=*(UWord*)&selection[COLS_DAMAGE];
//}

void	Persons3::ColourRulePlayerSquadron(AirStrucPtr	newac,FormationIndex formpos,UByte* s,PilotType* pilot)
{	//EVERYTHING COMES HERE NOW!!!!!
//DeadCode RDH 23Sep96 	if (SHAPE.SetAnimData(newac)!=sizeof(AircraftAnimData))
	if (SHAPE.SetAnimData(newac,s[COLS_BOMBS])!=sizeof(AircraftAnimData))	//DAW 12May98... 0 is weapon pack
		_Error.EmitSysErr("Animation not aircraft");
	newac->weap.Weapons=s[COLS_BOMBS];									//AMM 07Apr99
	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
	int inwingpos,outwingpos;
//	inwingpos=formpos&InWingMAX;
//	outwingpos=formpos&InFormMAX;

//	newac->ai.leaderaction = Miss_Man.camp.squad[0].nextleadact	//RDH 17Feb97
//							[outwingpos];						//RDH 18Aug96

//	if (inwingpos == 0)
//	{//flight leader get squadron formation
//		newac->formation = (FormationTypeIndex)Miss_Man.camp.squad[0].squadronform;
//	}else
//	{
//		newac->formation = (FormationTypeIndex)Miss_Man.camp.squad[0].formationnum [outwingpos];//RDH 17Feb97
//	}

 //	outwingpos*=Miss_Man.camp.squad[0].pilotsperflight;			//RDH 17Feb97
//	outwingpos*=4;			//RDH 17Feb97
//	inwingpos+=outwingpos;


//DEADCODE JIM 25/02/99 	newac->ai.followeraction = 	pilot->nextfollact;//RDH 18Aug96
//	newac->ai.combatskill 	= 	pilot->combatskill;		//RDH 18Aug96
//	newac->ai.combatskill 	= 	pilot->flyingskill;		//RDH 11Aug98
//	newac->ai.character = 		pilot->character;	//RDH 11Aug98
//DeadCode CSB 05/07/99		newac->ai.morale 	= 		pilot->morale;		//RDH 18Aug96



//fight tuning temp, rdh
//rdh 25nov98	newac->ai.morale 	= MORALE_TOPMORALE;		
//	newac->ai.combatskill 	= SKILL_HERO;
//	newac->ai.morale = MORALE_GOOD;		//MORALE_POOR;
//	newac->ai.combatskill 	= SKILL_VETERAN;

//	newac->ai.followeraction = 	MMC.Active_Pilots[inwingpos].nextfollact;//RDH 18Aug96

//	newac->ai.morale 	= MORALE_EXCELLENT;		
//	newac->ai.combatskill 	= SKILL_ACE;		
//	newac->ai.followeraction = 	MMC.Active_Pilots[inwingpos].nextfollact;//RDH 18Aug96
//	anim->imagemaptail		=	MMC.Active_Pilots[inwingpos].imagemaps.tail;
//	anim->imagemapbtmwing	=	MMC.Active_Pilots[inwingpos].imagemaps.btmwing;
//	anim->imagemapfuselage	=	MMC.Active_Pilots[inwingpos].imagemaps.fuselage;
//	anim->imagemapother		=	MMC.Active_Pilots[inwingpos].imagemaps.other;
//	anim->imagemaptopwing	=	MMC.Active_Pilots[inwingpos].imagemaps.topwing;
	anim->imagemapemblem	=	pilot->decal;

	// Set up 3-digit aircraft number...
	int	digits[16];												//RJS 11Mar99
	int	digcnt = 0;												//RJS 11Mar99
	int	tmpnum = pilot->aircraftnum;							//RJS 11Mar99
	int	pootmpnum = tmpnum;										//RJS 11Mar99
																//RJS 11Mar99
	while (digcnt < 3)											//RJS 11Mar99
	{															//RJS 11Mar99
		pootmpnum /= 10;										//RJS 11Mar99
		tmpnum -= (pootmpnum*10);								//RJS 30Apr99
		if (tmpnum < 0)											//RJS 30Apr99
			tmpnum = 0;											//RJS 30Apr99
		if (tmpnum > 9)											//RJS 30Apr99
			tmpnum = 9;											//RJS 30Apr99
																//RJS 30Apr99
		digits[digcnt++] = tmpnum;								//RJS 30Apr99
		tmpnum = pootmpnum;										//RJS 11Mar99
	}															//RJS 11Mar99
	anim->imagemapacid1 = digits[2];							//RJS 11Mar99
	anim->imagemapacid2 = digits[1];							//RJS 11Mar99
	anim->imagemapacid3 = digits[0];							//RJS 11Mar99

//	anim->dammageflags=*(UWord*)&s[COLS_DAMAGE];
	if ((int)Pack_PlayerPos==-1)			//RDH 27Aug96
	{															//PD 26Jun96
		Manual_Pilot.Associate(newac,ManualPilot::MANUAL);						//RDH 17Jun96
//		viewpoint->SetToPiloted(newac);							//PD 26Jun96
		SHAPE.SetPilotedAcAnim(newac);							//PD 26Jun96
		Pack_PlayerPos--;
		if (newac->movecode==AUTO_TAKEOFF)
		{
			newac->movecode=AUTO_FOLLOWWP;
			newac->playermoving=false;
		}
		else
			newac->playermoving=true;
		newac->playernotmovingheldac=NULL;
		UpdateLog(newac,0,EventLog::TAKEOFF);
		newac->ai.eventlog->homebase=newac->ai.homebase->uniqueID.count;
	}
	else	  //EmitSysErr
		Manual_Pilot.InitManualPilotSub(newac);			//rdh 9/6
}
//void	Persons3::ColourRulePlayerAuto(AirStrucPtr	newac,FormationIndex formpos,UByte* s)
//{
//DeadCode RDH 23Sep96 	if (SHAPE.SetAnimData(newac)!=sizeof(AircraftAnimData))
//	if (SHAPE.SetAnimData(newac,0)!=sizeof(AircraftAnimData))	//DAW 12May98... 0 is weapon pack
//		_Error.EmitSysErr("Animation not aircraft");
//	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
//	int inwingpos,outwingpos;
//	inwingpos=formpos&InWingMAX;
//	outwingpos=formpos&InFormMAX;
//DeadCode RDH 17Feb97 	outwingpos*=Miss_Man.camp.squad[0].pilotsperflight;			//RDH 17Feb97
//	outwingpos*=4;												//RDH 17Feb97
//	inwingpos+=outwingpos;
//	anim->imagemaptail		=MMC.Active_Pilots[inwingpos].imagemaps.tail;
//	anim->imagemapbtmwing	=MMC.Active_Pilots[inwingpos].imagemaps.btmwing;
//	anim->imagemapfuselage	=MMC.Active_Pilots[inwingpos].imagemaps.fuselage;
//	anim->imagemapother		=MMC.Active_Pilots[inwingpos].imagemaps.other;
//	anim->imagemaptopwing	=MMC.Active_Pilots[inwingpos].imagemaps.topwing;
//	anim->imagemapemblem	=MMC.Active_Pilots[inwingpos].imagemaps.emblem;
//	anim->dammageflags=*(UWord*)&s[COLS_DAMAGE];
//	if (Miss_Man.camp.currentplayerslot == inwingpos)				//PD 26Jun96
//
//	{															//PD 26Jun96
//		Manual_Pilot.Associate(newac,TRUE);						//RDH 17Jun96
//		viewpoint->SetToPiloted(newac);							//PD 26Jun96
//		SHAPE.SetPilotedAcAnim(newac);							//PD 26Jun96
//	}															//PD 26Jun96
//}

//void	Persons3::ColourRulePaintShop(AirStrucPtr	newac,FormationIndex formpos,UByte* s)
//{
//DeadCode RDH 23Sep96 	if (SHAPE.SetAnimData(newac)!=sizeof(AircraftAnimData))
//	if (SHAPE.SetAnimData(newac,0)!=sizeof(AircraftAnimData))	//DAW 12May98... 0 is weapon pack
//		_Error.EmitSysErr("Animation not aircraft");
//	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
//	int inwingpos,outwingpos;
//	inwingpos=formpos&InWingMAX;
//	outwingpos=formpos&InFormMAX;
//DeadCode RDH 17Feb97 	outwingpos*=Miss_Man.camp.squad[0].pilotsperflight;			//RDH 17Feb97
//	outwingpos*= 4;												//RDH 17Feb97
//	inwingpos+=outwingpos;
//	anim->imagemaptail		=MMC.Active_Pilots[inwingpos].imagemaps.tail;
//	anim->imagemapbtmwing	=MMC.Active_Pilots[inwingpos].imagemaps.btmwing;
//	anim->imagemapfuselage	=MMC.Active_Pilots[inwingpos].imagemaps.fuselage;
//	anim->imagemapother		=MMC.Active_Pilots[inwingpos].imagemaps.other;
//	anim->imagemaptopwing	=MMC.Active_Pilots[inwingpos].imagemaps.topwing;
//	anim->imagemapemblem	=MMC.Active_Pilots[inwingpos].imagemaps.emblem;
//	Manual_Pilot.Associate(newac,FALSE);
//	viewpoint->SetToPiloted(newac);							//PD 26Jun96
//	SHAPE.SetPilotedAcAnim(newac);							//PD 26Jun96
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Maintaining lists of allocated waypoints so they can be freed in the endgame
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


void	Persons3::AddRoute(UniqueID	firstwp)
{
	RouteHdr	*tmp=new RouteHdr;
	tmp->next=myworld->routelist;
	myworld->routelist=tmp;
	tmp->waypoint=firstwp;
	tmp->numusers=0;
}


void	Persons3::FreeRoutes()
{
	RouteHdr*	tmphdr=myworld->routelist;
	myworld->routelist=NULL;
	while(tmphdr)
	{
		WayPointPtr	tmpwp=*ConvertPtrUID(tmphdr->waypoint);
		while(tmpwp)
		{
		 	WayPointPtr	tmpwp2=tmpwp->next;
			delete(tmpwp);
			tmpwp=tmpwp2;
		}
		RouteHdr*	tmphdr2=tmphdr->next;
		delete tmphdr;
		tmphdr=tmphdr2;
	}	
	ContourList::FreeList();

}


void	Persons3::FreeEvents()
{
//DEADCODE JIM 17/03/99 	while (EventRec::eventbase)	delete EventRec::eventbase;

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Runtime/endgame routines to getting info on items
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ItemStatus
//Author		Jim Taylor
//Date			Mon 30 Sep 1996
//
//Description	get and put statuses of items. Use in State3d destructor.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//ITEM_STATUS	Persons2::ItemStatus(UniqueID u,ITEM_STATUS s)
//{
//
//	ItemBasePtr	i=ConvertPtrUID(u);
//	if (i)
//	{
//		ITEM_STATUS	rv=i->Status;
//		i->Status.deadtime=s.deadtime;
//		i->Status.deadscale=s.deadscale;
//		return (rv);
//	}
//	else
//	{
//		ITEM_STATUS	rv;//={FALSE};
//		rv.BlueLaunch=FALSE;
//		return rv;
//	}
//}

//ITEM_STATUS	Persons2::ItemStatus(UniqueID u)
//{
//	ItemBasePtr	i=ConvertPtrUID(u);
//	if (i)
//		return (i->Status);
//	else
//	{
//		ITEM_STATUS	rv;
//		return rv;
//	}
//}

//ITEM_STATUS	Persons2::ConvoyStatus(UniqueID uid,UniqueID& nextwp,UniqueID& nextwptarg,SLong& livelength)
//{
//	FormationItemPtr	f=*ConvertPtrUID(uid);
//	if (f)
//	{
//		livelength=0;
//		WayPointPtr w=f->waypoint;
//
//		nextwp=w->uniqueID.count;
//		ItemBasePtr	i=w->target;
//		if (i)
//			nextwptarg=i->uniqueID.count;
//		else
//			nextwptarg=IllegalSepID;
//		while (f)
//		{
//			if (f->Status.deadtime==0)
//			  	livelength++;
//			f=f->follower;
//		}
//		if (i)
//			return (i->Status);
//		else
//			return (w->Status);
//	}
//	else
//	{
//		ITEM_STATUS	rv;
//		return rv;
//	}
//}


 //
 //
 //
 //


//
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreScanBF
//Author		R. Hyde 
//Date			Tue 12 Aug 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::PreScanBF(FileNum f)
{
//DEADCODE JIM 25/03/99 	(UWord&)CustomMissionDesc[0]=0;
//DEADCODE JIM 25/03/99 	(UWord&)CustomMissionNews[0]=0;
//	justscanning=SCANNAMES;
	LoadSubPiece(NULL,f,(int)LOADEDBFS-1,SCANNAMES);
//DEADCODE JIM 25/03/99 	CustomMission.playerbf=f;
  //	justscanning=LOAD;
}
//
//

PlaneTypeSelect	Persons3::squad2type[]=					//some entries are bypassed:
	{	PT_F86A,PT_F86A,PT_F80,PT_F84,PT_F51,			//MMC.squad
		PT_B26,PT_B29,		PT_T6,PT_4U,				//used
		PT_MIG15,PT_MIG15BIS,							//used
		PT_YAK,											//used
		PT_MIG15,PT_MIG15,PT_MIG15,PT_MIG15,			//MMC.migsquad
		PT_MIG15BIS,PT_MIG15BIS,PT_MIG15BIS,PT_MIG15BIS,//MMC.migsquad
		PT_ATruck,PT_ATank								//used
	};
PlaneTypeSelect Persons3::Squad2Type(int s)
{
	if (s < SQ_B_NONFLYABLE)
		return (MMC.squad[s].actype);
	else
		if (s > SQ_R_MOREMIGSQUADS)
			return (MMC.migsquad[s-SQ_R_MOREMIGSQUADS].actype);
		else
			return squad2type[s];	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPreLoadFXShapes
//Author		Robert Slater
//Date			Fri 2 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::AddPreLoadFXShapes()
{
 	*shapefield|=SMOKE;
 	*shapefield|=EXPLO;
 	*shapefield|=BULLET;		//bullet
 	*shapefield|=BSMKE;
 	*shapefield|=SMLFIR;
 	*shapefield|=FIRE;
 	*shapefield|=BEXP;
 	*shapefield|=RSMOKE;
 	*shapefield|=SDUST;
 	*shapefield|=BDUST;
 	*shapefield|=DUMMY1;		//mig cannon blob
 	*shapefield|=DUMMY2;		//mig cannon smoke
 	*shapefield|=DUMY10;
 	*shapefield|=CTWR2;			//explosion shockwave
 	*shapefield|=DUMMY9;
 	*shapefield|=PLUME1;
 	*shapefield|=BULGND;
 	*shapefield|=BULWAT;
 	*shapefield|=DRTYX;
 	*shapefield|=MUSHY;
 	*shapefield|=SPLASH;
 	*shapefield|=GNDEXP;
 	*shapefield|=FIREB;
 	*shapefield|=PLUME2;
 	*shapefield|=FLASH;
 	*shapefield|=SMKSHP;
}
