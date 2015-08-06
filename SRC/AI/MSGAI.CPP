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
//Filename       msgai.cpp
//System         
//Author         Jim Taylor
//Date           Tue 28 May 1996
//Description    Beginning of a new AI version.
//
//In this version, the aircraft are processed by stepping through a sparse array,
//rather than a packed array so that their moment of action can seem 
//nondeterministic
//
//
//jobs
//1	Consider AddMessage for playerac
//
//
//
//
//
//------------------------------------------------------------------------------

#include	"dosdefs.h"
	#define F_COMMON
	#define F_GRAFIX
	#define F_BATTLE
#include	"files.g"
#include	"worldinc.h"
#include	"ai.h"
#include	"myerror.h"
#include	"mymath.h"
#include	"landscap.h"
#include	"ranges.h"
#include	"planetyp.h"
#include	"mytime.h"
#include	"flymodel.h"
#include	"persons2.h"
#include	"savegame.h"
#include	"miles.h"
#include	"3dinstr.h"
#include	"winmove.h"											//ARM 06Dec96
#include	"textref.h"
#include "rchatter.h"
#include	"replay.h"
#include	"overlay.h"

ArtInt	Art_Int;
AirStrucPtr	ArtInt::ACArray[ACARRAYSIZE]={0};

//rdh	enum	{DANGERRANGE  =METRES500,		//must defend self
//		SPOTRANGE  		=METRES5000,		//is it a bird, is it a plane?
//		RECOGNISERANGE  =METRES3000,		//no, its superman
//		ATTACKRANGE  	=MILES01,		//I guess he's comming for me, so I'll go for him
//		ENGAGERANGE  	=METRES1000};		//I'm going for him.


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckSequenceAudible
//Author		Jim Taylor
//Date			Thu 14 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	FormationItem::PlayerSequenceAudible(FileNum f)
{
	if (	formpos==0	||	Manual_Pilot.ControlledAC2==this)
	{
		_Miles.SequenceAudible(f);
		return(true);
	}
	return(false);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CleanUp
//Author		Jim Taylor
//Date			Tue 18 Jun 1996
//
//Description	reset AI system for next mission.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::CleanUp()
{
	for (int i=0;i<ACARRAYSIZE;i++)
		ACArray[i]=NULL;
	gunstimer=0;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Add
//Author		Jim Taylor
//Date			Tue 28 May 1996
//
//Description	Adds ac to ai ac array
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::Add(AirStrucPtr ac)
{
	if (Remove(ac))
		_Error.EmitSysErr("Added AC already known");
	int	ind=Math_Lib.rnd(ACARRAYSIZE);
	while (ACArray[ind])
		if (--ind<0)
			break;
	if (ind<0)
	{
		ind=ACARRAYSIZE-1;
		while (ACArray[ind])
			if (--ind<0)
				_Error.EmitSysErr("Aircraft array is full!");
	}
	ACArray[ind]=ac;
	return(true);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Remove
//Author		Jim Taylor
//Date			Tue 28 May 1996
//
//Description	Removes ac from ai ac array
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::Remove(AirStrucPtr ac)
{
 	int ind=ACARRAYSIZE-1;
	do
		if (ACArray[ind]==ac)
		{
			ACArray[ind]=NULL;
			return(true);
		}
	while	(ind--);
	return(false);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Visible
//Author		Jim Taylor
//Date			Tue 4 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::Visible(AirStrucPtr eye,AirStrucPtr trg)
{
	Coords3D* eyepos=_DPlay.GetGoodACPosition(eye);
	Coords3D* trgpos=_DPlay.GetGoodACPosition(trg);
	//loads of quick throwouts for target
//DeadCode JIM 22Apr97 	if (trg->uniqueID.deaded)									//JIM 17Oct96
	if (trg->Status.deadtime)
		return(false);											//JIM 17Oct96
	if (trg->leader && trg->information)
		return(false);
	if (trg->nationality==eye->nationality)
		if (eye->movecode==AUTO_COMBAT && eye->ai.unfriendly)
			return(false);
		else;
	else
		if (trg->leader && trg->movecode==AUTO_COMBAT && trg->ai.unfriendly)
			return(false);
	if (trg->ai.attacker && trg->ai.attacker->ai.unfriendly==trg && trg->ai.attacker->movecode>=AUTO_PRECOMBAT)
		return(false);
	int	delta=trgpos->X-eyepos->X;
	int delta2=trgpos->Z-eyepos->Z;
	int	visiblerange=VISIBLERANGE;
	if (eye->nationality==NAT_RED && trg->nationality==NAT_BLUE)
		if (trg->ai.radiosilent)
			visiblerange=METRES30KM;
		else
			visiblerange=METRES100KM;

	if (	delta<visiblerange && delta>-visiblerange
		&&	delta2<visiblerange && delta2>-visiblerange
//DEADCODE JIM 29/03/99 		||	(!!(eye->World.Y<Land_Scape.CloudAlt())!=!!(trg->World.Y<Land_Scape.CloudAlt()))
		)
	{
		Item::InterceptandRange(eyepos,trgpos);
		if (eye->Range<VISIBLERANGE)
			return(true);
	}
	//finally do proper hdg-intercept
	elser
	{
		if (eye->ai.unfriendly==trg)
			eye->ai.unfriendly=NULL;
		return(false);
	}
}

//DeadCode JIM 06Nov96 #define	SUNPITCH 	ANGLES_30Deg
//DeadCode JIM 06Nov96 #define	SUNHDG	ANGLES_135Deg	

bool	ArtInt::Seen(AirStrucPtr eye,AirStrucPtr trg)
{
	if (!Visible(eye,trg))
		return(false);
	else
	{
//DeadCode JIM 10Dec96 		if (trg->nationality!=eye->nationality)
//DeadCode JIM 10Dec96 		{
//DeadCode JIM 10Dec96 			spotcount++;
//DeadCode JIM 10Dec96 			if (Save_Data.gamedifficulty[GD_TACTICALRANGE])			//JIM 22Oct96
//DeadCode JIM 10Dec96 			{														//JIM 22Oct96
//DeadCode JIM 10Dec96 				Timer_Code.AccelToggle(FALSE);						//JIM 22Oct96
//DeadCode JIM 10Dec96 				Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);		//JIM 22Oct96
//DeadCode JIM 10Dec96 			}														//JIM 22Oct96
//DeadCode JIM 10Dec96 		}		
		if (eye->ai.unfriendly!=trg)
		{
			//build up probabilities
			enum	CentWord	{	PCW_1=655,PCW_2=1300,PCW_5=3277,
									PCW_10=6553,PCW_20=13107,
									PCW_25=16384,PCW_50=32768,PCW_75=49100,
									PCW_80=52430,PCW_90=59000,
									PCW_95=62250,PCW_99=64900,PCW_100=65536
									};
			ULong	prob=PCW_100;	//NOTE: ALL MATH IS UNSIGNED!!!!
			ULong	tprob;
			//range														//0.0km: 100
//DEADCODE RDH 23/06/99 			if (item::Range<DANGERRANGE*2)								//0.5km:  98
//DEADCODE RDH 23/06/99 				tprob=PCW_100-item::Range*PCW_5/(DANGERRANGE*2);		//1.0km:  95
//DEADCODE RDH 23/06/99 			elseif (item::Range<RECOGNISERANGE)														//3.0km:	 50
//DEADCODE RDH 23/06/99 				tprob=PCW_95-MULDIVSIN(item::Range,PCW_90,RECOGNISERANGE-(DANGERRANGE*2));  				//5.0km:	  5
//DEADCODE RDH 23/06/99 			else
//DEADCODE RDH 23/06/99 				tprob=PCW_5-MULDIVSIN(item::Range-RECOGNISERANGE,PCW_5,METRES2000);


			int boundary = 	ENGAGERANGE + ((COMBATRANGE - ENGAGERANGE) *(eye->ai.combatskill))/(SKILL_HERO);
			
			if (item::Range<boundary)								//0.5km:  98
				tprob=PCW_100-item::Range*PCW_5/(boundary);		//1.0km:  95
			elseif (item::Range<REDUCEDVISIBILITY)														//3.0km:	 50
				tprob=PCW_95-MULDIVSIN(item::Range-boundary,PCW_90,REDUCEDVISIBILITY-boundary);  				//5.0km:	  5
			else if (item::Range<VISIBLERANGE) 
				tprob=PCW_5;
			else
				tprob = PCW_1;
			prob=(prob*tprob)>>16;
			//sun position
//DeadCode CSB 06/07/99				if (eye->World.Y>Land_Scape.CloudAlt())
//DeadCode CSB 06/07/99				{
//DeadCode CSB 06/07/99					WorldStuff	*worldptr = mobileitem::currworld;
//DeadCode CSB 06/07/99					if (-worldptr->sunrot<ANGLES_180Deg)
//DeadCode CSB 06/07/99					{
//DeadCode CSB 06/07/99						tprob	=Math_Lib.AbsSign((SWord)(item::PitchIntercept-worldptr->sunpitch))				//00deg=  10
//DeadCode CSB 06/07/99								+Math_Lib.AbsSign((SWord)(item::HdgIntercept-worldptr->sunhdg));				//20deg= 100
//DeadCode CSB 06/07/99						ANGLES	tang=(Angles)tprob;
//DeadCode CSB 06/07/99						if (tang<ANGLES_20Deg)										//20+  = 100
//DeadCode CSB 06/07/99						{
//DeadCode CSB 06/07/99							tprob=PCW_10+tprob*PCW_90/ANGLES_20Deg;
//DeadCode CSB 06/07/99							prob=(prob*tprob)>>16;
//DeadCode CSB 06/07/99						}
//DeadCode CSB 06/07/99					}
//DeadCode CSB 06/07/99				}
			//pointing his way?
			tprob=	PCW_100												//000Deg= 100								
					-	Math_Lib.AbsSign((SWord)
						(item::HdgIntercept-eye->hdg))					//090Deg=  60
						*PCW_75/ANGLES_180Deg;							//180Deg=  20
			prob=(prob*tprob)>>16;
			tprob=	PCW_100
					-	Math_Lib.AbsSign((SWord)(item::PitchIntercept	//+90Deg=  50
										-	eye->pitch					//+20Deg= 100
										-	ANGLES_10Deg))				//-50Deg=  50
						*PCW_50/ANGLES_112Deg;							//-90Deg=  25
			prob=(prob*tprob)>>16;

			//side on?
			if (item::Range>REDUCEDVISIBILITY)
			{
			//really need 'viewer transform' here.
				tprob=	PCW_100											 	//-180Deg= 25
						-	Math_Lib.AbsSign((SWord)						// -90Deg=100
									(Math_Lib.AbsSign((SWord)
										(item::HdgIntercept					//   0Deg= 25
										-trg->hdg))							// +90Deg=100
									-ANGLES_90Deg))							//+180Deg= 25
							*PCW_25/ANGLES_90Deg
						-	Math_Lib.AbsSign((SWord)						//-180Deg= 25
									(Math_Lib.AbsSign((SWord)
										(item::PitchIntercept				// -90Deg=100
										-trg->pitch))						//   0Deg= 25
									-ANGLES_90Deg))							// +90Deg=100
							*PCW_25/ANGLES_90Deg;								//+180Deg= 25

				prob=(prob*tprob)>>16;
			}
	//Enemy size:	  (more or bigger dots)
	//A/C spotability:max 200%, min 50%
	//Force size:	1=10%		.. 10=100%
			tprob=GuessFormationSize(eye, trg);
			if (tprob>=8)
				tprob=PCW_90+PCW_1*(tprob-8);
			else
				tprob=PCW_75+PCW_2*tprob;
			prob=(prob*tprob)>>16;
	//Enemy formation:

	if (		(Persons2::PlayerGhostAC == eye)
			&&	(item::Range < COMBATRANGE)
			&&	(!Save_Data.gamedifficulty[GD_AUTOVECTORING])
	   )
  		prob = PCW_100;
	//Skill:	(Friendly force size)
//DEADCODE RDH 23/06/99 			tprob=eye->ai.combatskill			+2;
//DEADCODE RDH 23/06/99 			prob=prob*tprob/(SKILL_HERO	+2);
			

	//So, what are the chances?
			if (Math_Lib.rnd()>prob)								  //RDH 23/06/99
				return(false);
			else													  //RDH 23/06/99
				return(true);
		}															  //RDH 23/06/99
		else
			return(true);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VisibleCheck
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
void	ArtInt::VisibleCheck()
{
	VisibleAcCheck();
	VisibleContrailsCheck();
	VisibleAAACheck();
	
}

void	ArtInt::ExpandMigs(AirStrucPtr placeholder)
{	
	//Comms interface goes here and does this:
//TempCode JIM 13May99 T::F_C7_RED,
//TempCode JIM 13May99 T::F_C7_UN,

// dont need to send a message for replay because expandmigs uses ghost AC position
// to expand Migs. In time accel for replay the Migs could get expanded but upon
// resuming record the block header will record all their positions.
//DeadCode AMM 13Apr99 	placeholder->Status.Drawn=TRUE;
	if (_DPlay.Implemented)										//AMM 12Apr99
		_DPlay.SendExpandMigsMessage(placeholder->uniqueID.count);//AMM 12Apr99
	else														//AMM 12Apr99
		placeholder->Status.Drawn=TRUE;							//AMM 12Apr99
}

void	ArtInt::ReallyExpandMigs(AirStrucPtr placeholder)
{	//GUARANTEED 256/50=5 SECOND DELAY BETWEEN THESE 2 ROUTINES!!!
//	basic setup info in placeholder
//		currac->fly.callname=formac;
//		currac->fly.callnum=wingac;
//		currac->Status.deadscale=I.type.Evaluate(0)-SQ_R_MOREMIGSQUADS;
//	copy from placeholder:
//		formation
//		homebase - can be airfield
//		waypoints
//		position
//
	int squad=placeholder->Status.deadscale;
	AirStrucPtr	mainleader=NULL,flightleader=NULL,prevac=NULL;
	bool geardown = false;	//(placeholder->movecode==AUTO_TAKEOFF);
	AircraftAnimData* adptr = (AircraftAnimData *)placeholder->Anim;	//CSB 31/5/99
	if(adptr->acleglowerl == 0)
		geardown = true;						//CSB 31/5/99
	for (int ac=placeholder->fly.callname,wingsize=placeholder->fly.callnum,flnum=0;ac>0;flnum++)
		for (int wac=0;wac<wingsize;wac++,ac--)
		{
			AirStrucPtr	newac=Persons3::migsq[squad];
			if (newac)
			{
				Persons3::migsq[squad]=newac->fly.nextflight;
				if (!mainleader)
				{
					prevac=mainleader=flightleader=newac;
					newac->fly.leadflight=placeholder->fly.leadflight;
					newac->fly.nextflight=NULL;
					newac->leader=
						newac->follower=NULL;
				}
				else
				if (wac)
				{
					prevac->follower=newac;
					newac->leader=flightleader;
					newac->follower=NULL;
					newac->fly.leadflight=mainleader;
					newac->fly.nextflight=NULL;
					prevac=newac;
				}
				else
				{
					newac->leader=NULL;
					newac->follower=NULL;
					flightleader->fly.nextflight=newac;
					newac->fly.leadflight=mainleader;
					newac->fly.nextflight=NULL;
					flightleader=
						prevac=newac;
				}
				newac->currworld->RemoveFromWorld(newac);
				newac->fly.originalformpos=
					newac->formpos=(FormationIndexMIN+(InForm)flnum)+(InWing)wac;//DAW 26May99
				newac->formation=(FORMATIONDESC)placeholder->formation;
				if (newac->formpos==FormationIndexMIN)
					newac->World=placeholder->World;
				else
					if (placeholder->movecode==AUTO_TAKEOFF)
					{
						newac->World=placeholder->World;
						newac->World.X+=METRES15*(newac->formpos&InWingMAX);
						newac->World.Z+=METRES15*(newac->formpos&InFormMAX);
					}
					else
						newac->World=*newac->PositionWRTLeader();
				newac->currworld->AddToWorld(newac);

				newac->hdg=placeholder->hdg;
				newac->pitch=placeholder->pitch;
				newac->fly.cpitch=placeholder->fly.cpitch;
				newac->roll=placeholder->roll;
				newac->vel=placeholder->vel;
				newac->slowdownleader=FALSE;
				newac->overview_movecode=placeholder->overview_movecode;
				if (geardown)
					newac->fly.pModel->GearDown(newac);
				newac->information=geardown?FALSE:TRUE;
				newac->ai.manoeuvre=(MANOEUVRE)placeholder->ai.manoeuvre;
				newac->manoeuvretime=placeholder->manoeuvretime;
				newac->ai.ManStep=(int)placeholder->ai.ManStep;
				newac->ai.homebase=placeholder->ai.homebase;
				newac->ai.eventlog=placeholder->ai.eventlog;
				newac->waypoint=placeholder->waypoint;

//TEMPCODE RDH 26/05/99 				newac->
			}
		}
//make placeholder disappear
	placeholder->Status.deadtime=1;
	placeholder->World.Y=0;
	placeholder->vel=0;
	placeholder->movecode=AUTO_NOPPILOT;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VisibleAcCheck
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	All aircraft including medium bombrs come through here
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////
//
// Function:    VisibleAcCheck
// Date:        17/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
void	ArtInt::VisibleAcCheck()
{
	spotcount=0;
//DeadCode JIM 10Jun96 	((char*)0xb0000)_++;
	AirStruc* eye=ACArray[ACArrayInd];

	ACArrayInd++;
	if (ACArrayInd>=ACARRAYSIZE)
	{
		ACArrayInd-=ACARRAYSIZE;
		if (gunstimer)
			if (--gunstimer)
				OverLay.DecisionMessage(PreCombatMsg,8,Persons2::PlayerGhostAC,NULL,Persons2::PlayerGhostAC,FALSE);	//RJS 09Jun99

	}
	if (eye && !eye->Status.deadtime)							//JIM 17Oct96
 	if ((eye->formpos == 0) || !eye->information)			//group leader or not in formation //RDH 23/02/99
	if (eye->shape==SUPMIG && eye->nationality==NAT_RED)
	{	//super migs do nothing until 100 miles range of any unfriendly
		//don't need to worry about historical position as a message gets sent.
		if (eye->movecode!=AUTO_NOPPILOT)
			if (eye->Status.Drawn)
				ReallyExpandMigs(eye);
			else
				for (int indloop=0;indloop<ACARRAYSIZE;indloop++)
				{
					AirStruc* trg=ACArray[indloop];
					if (	trg 
						&&	trg->nationality!=eye->nationality
						&&	Math_Lib.DistAbsSum(trg->World.X-eye->World.X,trg->World.Z-eye->World.Z)<METRES200KM)
					{
						ExpandMigs(eye);
						break;
					}
				}
	}
	else
	if (eye->movecode==AUTO_TAKEOFF)
	{
		if (eye->ai.ManStep>=TO_SIMPLEHOLDDELAY)
		{
			bool closebomber=false;
			for (int indloop=0;indloop<ACARRAYSIZE;indloop++)
			{
				AirStruc* trg=ACArray[indloop];
				if (	trg &&	trg->nationality!=eye->nationality)
				{
					Coords3D* trgpos=_DPlay.GetGoodACPosition(trg);
					if ((trg->duty&ACTIONCODE)==DA_CAP)
					{
//DeadCode DAW 02Sep99 						breakif(Math_Lib.DistAbsSum(trgpos->X-eye->World.X,trgpos->Z-eye->World.Z)<METRES10KM)
						if(Math_Lib.DistAbsSum(trgpos->X-eye->World.X,trgpos->Z-eye->World.Z)<METRES50KM) //JIM 16/06/99
							closebomber=true;
					}
					else
						if(Math_Lib.DistAbsSum(trgpos->X-eye->World.X,trgpos->Z-eye->World.Z)<METRES80KM) //JIM 16/06/99
							closebomber=true;
				}
			}
			if (closebomber)
				eye->ai.ManStep=TO_RUNWAYPOWER;
		}
	}
	else
	if (eye->movecode!=AUTO_NOPPILOT)	//spare aircraft
//TEMPCODE JIM 17/03/99 	if (!eye->leader || !eye->information)
//DEADCODE RDH 23/02/99 	if (!eye->leader || !eye->information)
	if (!eye->AircraftDamaged())
//rdh 13/1/99	if (!eye->AircraftDamaged() && eye->classtype->aerobaticfactor!=AEROBATIC_LOW)								//JIM 29Aug96
	if (eye->movecode!=AUTO_COMBAT || eye->ai.unfriendly==NULL)
	{	//we exist and we are not busy
		int	indstart=Math_Lib.rnd(100);
		int indloop=indstart;

//DEADCODE RDH 13/06/99 		if	(	(		eye->leader
//DEADCODE RDH 13/06/99 					&& ((AirStruc*)*eye->leader)->ai.unfriendly
//DEADCODE RDH 13/06/99 					&& ((AirStruc*)*eye->leader)->movecode==AUTO_COMBAT
//DEADCODE RDH 13/06/99 				)
//DEADCODE RDH 13/06/99 				||
//DEADCODE RDH 13/06/99 				(			eye->fly.leadflight
//DEADCODE RDH 13/06/99 					&& ((AirStruc*)*eye->fly.leadflight)->ai.unfriendly
//DEADCODE RDH 13/06/99 					&& ((AirStruc*)*eye->fly.leadflight)->movecode==AUTO_COMBAT
//DEADCODE RDH 13/06/99 				)
//DEADCODE RDH 13/06/99 			)
		if (	(eye->ai.unfriendly==NULL) && (LeadersGroupInCombat(eye)))									  //RDH 13/06/99
		{//if eye has leader and leader has unfriendly and leader is in combat 
			if (AttackSpareInLeadersGroup(eye))	return;
		}
		do
		{
			AirStruc* trg=ACArray[indloop];
//##also quick throw out based on whether msg already sent
			if (	trg 
				&&	trg!=eye 
				&&	trg->movecode!=AUTO_NOPPILOT
				&&	trg->movecode!=AUTO_TAKEOFF
				&&	((trg->formpos == 0) || (!trg->information))		//only see group leaders or a/c not information //RDH 10/05/99
				&& Seen(eye,trg)
				)
			{
				{//ok.. we can see the other guy
				 //can't tell who he is yet..
					if (trg->nationality!=eye->nationality
						&& eye->ai.unfriendly!=trg
						)
					{
						spotcount++;
						if (Save_Data.gamedifficulty[GD_TACTICALRANGE])
						{
//TEMP							Timer_Code.AccelToggle(FALSE);
							OverLay.CancelAccel();
//DEADCODE DAW 10/05/99 							Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);
						}
					}
				if (trg->Range>RECOGNISERANGE)
					breakif (SpottedUnknown(eye,trg))
				else if (eye->nationality==trg->nationality)
					//he's a good guy!
					breakif (DoesFriendNeedHelp(eye,trg))
				else if (trg->nationality==NAT_GREEN || trg->nationality==NAT_AMBER)
					//damn civilians!
					breakif (SpottedNeutral(eye,trg))
				else if (eye->movecode==AUTO_PRECOMBAT)
				{	//If we are already pre-combatting then we only need to
					//consider breaking off if this is a new unfriendly and
					//it is closer.
					SpottedNewUnfriendly(eye,trg);
				}	//logic block
				else
					//die alien scum
					breakif (SpottedUnfriendly(eye,trg))
				}
			}
		if (indloop==0)
			indloop=ACARRAYSIZE;
		indloop--;
		}
		while (indloop!=indstart);
	}
}


//DeadCode RDH 27Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 27Mar98 //Procedure		DoesFriendNeedHelp
//DeadCode RDH 27Mar98 //Author		Jim Taylor
//DeadCode RDH 27Mar98 //Date			Tue 4 Jun 1996
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Description	Assess wether friendly needs helping out
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Inputs		
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Returns	
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 Bool	ArtInt::DoesFriendNeedHelp(AirStruc* eye,AirStruc* trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	if (trg->ai.unfriendly && !((AirStruc*)*trg->ai.unfriendly)->ai.attacker)
//DeadCode RDH 27Mar98 	{
//DeadCode RDH 27Mar98 //TEMP		if (trg->ai.eventlog->stage!=EventLog::TAKEOFF)
//DeadCode RDH 27Mar98 //TEMP			Persons_2.AddMessageIfPlayerSq(eye,UserMsg::SIGHTED,TEXT_DOGFIGHTSIGHTED,trg);
//DeadCode RDH 27Mar98 		if (eye->ai.unfriendly==NULL && eye->movecode<AUTO_PRECOMBAT)
//DeadCode RDH 27Mar98 			eye->ai.unfriendly=trg->ai.unfriendly;
//DeadCode RDH 27Mar98 		if (trg->Range>RECOGNISERANGE)
//DeadCode RDH 27Mar98 		{//decide wether to attack - they may not know about us
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 		else
//DeadCode RDH 27Mar98 		if (trg->Range>ATTACKRANGE)
//DeadCode RDH 27Mar98 		{//decide wether to attack or evade - they can see us
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 		else
//DeadCode RDH 27Mar98 		{//they are very close... really have to go in!
//DeadCode RDH 27Mar98 			//force everyone out of formation so they spot indipendently
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 	else
//DeadCode RDH 27Mar98 		if (trg->Range>RECOGNISERANGE-METRES500)
//DeadCode RDH 27Mar98 			if (eye->ai.eventlog->stage==EventLog::TAKEOFF)
//DeadCode RDH 27Mar98 			if (trg->ai.eventlog->stage!=EventLog::TAKEOFF)
//DeadCode RDH 27Mar98 			{
//DeadCode RDH 27Mar98 //TEMP				Persons_2.UpdateLog(trg->ai.eventlog,0,EventLog::SEENBYPLAYERS);
//DeadCode RDH 27Mar98 //TEMP				Persons_2.AddMessage(UserMsg::SIGHTED,TEXT_FRIENDLYSIGHTED,trg);
//DeadCode RDH 27Mar98 				eye->PlayerSequenceAudible(FIL_MUSIC_FRIENDLY_SEEN);
//DeadCode RDH 27Mar98 			}
//DeadCode RDH 27Mar98 	return(false);
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 27Mar98 //Procedure		SpottedNeutral
//DeadCode RDH 27Mar98 //Author		Jim Taylor
//DeadCode RDH 27Mar98 //Date			Tue 4 Jun 1996
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Description	do we care about neutrals?
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Inputs		
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Returns	
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 Bool	ArtInt::SpottedNeutral(AirStruc* eye,AirStruc* trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	return(false);
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 27Mar98 //Procedure		SpottedNewUnfriendly
//DeadCode RDH 27Mar98 //Author		Jim Taylor
//DeadCode RDH 27Mar98 //Date			Tue 22 Oct 1996
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Description	
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Inputs		
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Returns	
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 Bool	ArtInt::SpottedNewUnfriendly(AirStruc* eye,AirStruc* trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	if (eye->leader==NULL)
//DeadCode RDH 27Mar98 		if (trg->ai.attacker==NULL)
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 			int	newrange=trg->Range;
//DeadCode RDH 27Mar98 			if (newrange<DANGERRANGE)
//DeadCode RDH 27Mar98 				return(SpottedUnfriendly(eye,trg));
//DeadCode RDH 27Mar98 			if (newrange<ENGAGERANGE)
//DeadCode RDH 27Mar98 			{
//DeadCode RDH 27Mar98 				if (eye->ai.unfriendly==NULL)
//DeadCode RDH 27Mar98 					return(SpottedUnfriendly(eye,trg));
//DeadCode RDH 27Mar98 				eye->InterceptandRange(eye->ai.unfriendly);
//DeadCode RDH 27Mar98 				if (eye->Range>ENGAGERANGE)
//DeadCode RDH 27Mar98 					return(SpottedUnfriendly(eye,trg));
//DeadCode RDH 27Mar98 			}
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 	return(false);
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 27Mar98 //Procedure		SpottedUnfriendly
//DeadCode RDH 27Mar98 //Author		Jim Taylor
//DeadCode RDH 27Mar98 //Date			Tue 4 Jun 1996
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Description	Do we want to attack or evade or tell flight/squad leader?
//DeadCode RDH 27Mar98 //				Based on character and rule flags.
//DeadCode RDH 27Mar98 //				First rule flag: go tell the leader.
//DeadCode RDH 27Mar98 //				This works for followers as well, as only out of formation followers get here!
//DeadCode RDH 27Mar98 //				Ok... so we decide to engage...
//DeadCode RDH 27Mar98 //					If range is <danger we just go in. No time to plan.
//DeadCode RDH 27Mar98 //					If the spotter is the leader then the whole flight can go in
//DeadCode RDH 27Mar98 //					Any following flights can go in as well
//DeadCode RDH 27Mar98 //					
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Inputs		
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Returns	TRUE if engaging
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 Bool	ArtInt::SpottedUnfriendly(AirStruc* eye,AirStruc* trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	if (eye->ai.eventlog->stage==EventLog::TAKEOFF)
//DeadCode RDH 27Mar98 		if (trg->ai.unfriendly)
//DeadCode RDH 27Mar98 			eye->PlayerSequenceAudible(FIL_MUSIC_DOGFIGHT_SEEN);
//DeadCode RDH 27Mar98 		else
//DeadCode RDH 27Mar98 		if (trg->classtype->aerobaticfactor!=AEROBATIC_LOW)
//DeadCode RDH 27Mar98 			eye->PlayerSequenceAudible(FIL_MUSIC_IDENTIFY_ENEMY);
//DeadCode RDH 27Mar98 		else
//DeadCode RDH 27Mar98 			eye->PlayerSequenceAudible(FIL_MUSIC_BOMBERS_SEEN);
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 //TEMP	Persons_2.PossibleEvent(eye->currworld,trg,eye);
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	if ( trg->Range>DANGERRANGE && eye->ai.tellleader && eye->formpos )
//DeadCode RDH 27Mar98 	{	//ok.. we are supposed to tell the leader...
//DeadCode RDH 27Mar98 		//BUT only if he is not already engaging.
//DeadCode RDH 27Mar98 		AirStrucPtr	leadac=*eye->leader;
//DeadCode RDH 27Mar98 		if (leadac==NULL)
//DeadCode RDH 27Mar98 			leadac=eye->fly.leadflight;
//DeadCode RDH 27Mar98 		if (leadac && leadac->ai.unfriendly==NULL && leadac->movecode!=AUTO_COMBAT)
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 			eye->movecode=AUTO_TELLLEADER;
//DeadCode RDH 27Mar98 			eye->ai.unfriendly=trg;
//DeadCode RDH 27Mar98 		 	return(true);	//we have decided to run to leader
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 //TEMP		Persons_2.AddMessageIfPlayer(eye,UserMsg::SIGHTED,TEXT_UNFRIENDLYSIGHTED,trg);
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 	//we act indipendently...
//DeadCode RDH 27Mar98 	if (eye->Range>ATTACKRANGE)
//DeadCode RDH 27Mar98 	{	//if range is > attack range we can choose based on character of the pilot
//DeadCode RDH 27Mar98 		//	On spotting the enemy, a tactician will only engage if:
//DeadCode RDH 27Mar98 		// 				outnumbers enemy
//DeadCode RDH 27Mar98 		//			&	has surprise
//DeadCode RDH 27Mar98 		//			&	has altitude advantage & optimum alt range
//DeadCode RDH 27Mar98 		//
//DeadCode RDH 27Mar98 		//	Norman	outnumbers enemy &	has altitude advantage
//DeadCode RDH 27Mar98 		//
//DeadCode RDH 27Mar98 		//	Cavalier only requires altitude advantage.
//DeadCode RDH 27Mar98 		//	Alt advantage includes a check for operating altitude
//DeadCode RDH 27Mar98 		//
//DeadCode RDH 27Mar98 		// However, you should keep an eye on him!
//DeadCode RDH 27Mar98 		if (eye->movecode!=AUTO_COMBAT)							//JIM 27Aug96
//DeadCode RDH 27Mar98 			eye->ai.unfriendly=trg;								//JIM 27Aug96
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 		switch	(eye->ai.character)
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 		case CHAR_CAVALIER:
//DeadCode RDH 27Mar98 			if (	trg->World.Y > eye->classtype->opceiling	)
//DeadCode RDH 27Mar98 			{
//DeadCode RDH 27Mar98 //TEMP				Persons_2.AddMessageIfPlayerSq(eye,UserMsg::SIGHTED,TEXT_UNFRIENDLYSIGHTED,trg);
//DeadCode RDH 27Mar98 				return(false);
//DeadCode RDH 27Mar98 			}
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 		case CHAR_MRAVERAGE:
//DeadCode RDH 27Mar98 			if (	trg->World.Y > eye->classtype->opceiling
//DeadCode RDH 27Mar98 				||	GuessFormationSize(trg)>CountFormationSize(eye)
//DeadCode RDH 27Mar98 				)
//DeadCode RDH 27Mar98 			{
//DeadCode RDH 27Mar98 //TEMP				Persons_2.AddMessageIfPlayerSq(eye,UserMsg::SIGHTED,TEXT_UNFRIENDLYSIGHTED,trg);
//DeadCode RDH 27Mar98 				return(false);
//DeadCode RDH 27Mar98 			}
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 				
//DeadCode RDH 27Mar98 		case CHAR_TACTICIAN:
//DeadCode RDH 27Mar98 			if (	trg->World.Y > eye->classtype->fightceiling
//DeadCode RDH 27Mar98 //DeadCode JIM 24Oct96 				||	trg->World.Y < eye->classtype->fightfloor
//DeadCode RDH 27Mar98 				||	GuessFormationSize(trg)>CountFormationSize(eye)
//DeadCode RDH 27Mar98 //DeadCode RDH 23Jul96 				||	SameFlight(eye,*trg->ai.unfriendly)
//DeadCode RDH 27Mar98 				)
//DeadCode RDH 27Mar98 			{
//DeadCode RDH 27Mar98 //TEMP				Persons_2.AddMessageIfPlayerSq(eye,UserMsg::SIGHTED,TEXT_UNFRIENDLYSIGHTED,trg);
//DeadCode RDH 27Mar98 				return(false);
//DeadCode RDH 27Mar98 			}
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 				
//DeadCode RDH 27Mar98 		case CHAR_TIMID:   	//won't attack unless directly threatened
//DeadCode RDH 27Mar98 			{
//DeadCode RDH 27Mar98 //TEMP				Persons_2.AddMessageIfPlayerSq(eye,UserMsg::SIGHTED,TEXT_UNFRIENDLYSIGHTED,trg);
//DeadCode RDH 27Mar98 				return (FALSE);
//DeadCode RDH 27Mar98 			}
//DeadCode RDH 27Mar98 		}	
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 	if (trg->Range<DANGERRANGE)
//DeadCode RDH 27Mar98 	{	//just go straight in. No time to set up
//DeadCode RDH 27Mar98 		SetEngage(eye,trg);
//DeadCode RDH 27Mar98 		if (eye->movecode<AUTO_PRECOMBAT)
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 //TEMP			Persons_2.AddMessageIfPlayerSq(eye,UserMsg::ATTACKED,TEXT_BOUNCED,trg);
//DeadCode RDH 27Mar98 			eye->PlayerSequenceAudible(FIL_MUSIC_SURPRISED);
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 		ClearFollowerFormation(eye);
//DeadCode RDH 27Mar98 		return(true);
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 	//Go in in formation... try and get advantage if poss!
//DeadCode RDH 27Mar98 	//how to go in...
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	if (eye->leader)
//DeadCode RDH 27Mar98 	{
//DeadCode RDH 27Mar98 		SetPreEngage(eye,trg);
//DeadCode RDH 27Mar98 		return(true);
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	//find the leader to go for
//DeadCode RDH 27Mar98 	//Always go for leader of current flight
//DeadCode RDH 27Mar98 	if (trg->information && trg->leader)
//DeadCode RDH 27Mar98 		trg=*trg->leader;
//DeadCode RDH 27Mar98 	//If we are squad leader consider going for their squad leader
//DeadCode RDH 27Mar98 	if (eye->formpos==0 && trg->fly.leadflight &&trg->information)//JIM 03Oct96
//DeadCode RDH 27Mar98 		trg=trg->fly.leadflight;
//DeadCode RDH 27Mar98 	//attack him!
//DeadCode RDH 27Mar98 		SetPreEngage(eye,trg);
//DeadCode RDH 27Mar98 	//send everyone in our flight against everyone in his flight
//DeadCode RDH 27Mar98 	AirStrucPtr	currtrg=trg;
//DeadCode RDH 27Mar98 	AirStrucPtr	currfol=eye;
//DeadCode RDH 27Mar98 	while ((currfol=*currfol->follower)!=NULL)
//DeadCode RDH 27Mar98 		currtrg=SetFollowerPreEngage(currfol,currtrg);
//DeadCode RDH 27Mar98 	//send each flight in our squad against each of his flights
//DeadCode RDH 27Mar98 	if (eye->formpos==00)
//DeadCode RDH 27Mar98 	{
//DeadCode RDH 27Mar98 		currtrg=trg;
//DeadCode RDH 27Mar98 		currfol=eye;
//DeadCode RDH 27Mar98 		if (currtrg->leader==NULL)
//DeadCode RDH 27Mar98 		while ((currfol=currfol->fly.nextflight)!=NULL)
//DeadCode RDH 27Mar98 			currtrg=SetFlightPreEngage(currfol,currtrg);
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 	return(true);
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 27Mar98 //Procedure		SpottedUnknown
//DeadCode RDH 27Mar98 //Author		Jim Taylor
//DeadCode RDH 27Mar98 //Date			Tue 4 Jun 1996
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Description	Do we want a closer look?
//DeadCode RDH 27Mar98 //				At this range, the only criteria are our strength and enemy force 
//DeadCode RDH 27Mar98 //				size.
//DeadCode RDH 27Mar98 //				Character can be applied to this.
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Inputs		
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Returns	
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 Bool	ArtInt::SpottedUnknown(AirStruc* eye,AirStruc* trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	if (eye->ai.unfriendly==NULL)
//DeadCode RDH 27Mar98 		if (eye->nationality!=trg->nationality)
//DeadCode RDH 27Mar98 			eye->ai.unfriendly=trg;
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	if (	eye->ai.eventlog->stage==EventLog::TAKEOFF
//DeadCode RDH 27Mar98 		&&	trg->ai.eventlog->stage!=EventLog::TAKEOFF
//DeadCode RDH 27Mar98 		)
//DeadCode RDH 27Mar98 //TEMP		Persons_2.AddMessage(UserMsg::SIGHTED,TEXT_UNKNOWNSIGHTED,eye);
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 		if (eye->ai.eventlog->stage==EventLog::TAKEOFF)
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 		 	if(trg->ai.eventlog->stage!=EventLog::TAKEOFF)
//DeadCode RDH 27Mar98 			{
//DeadCode RDH 27Mar98 				eye->PlayerSequenceAudible(FIL_MUSIC_SPOTTED_UNKNOWN);
//DeadCode RDH 27Mar98 //TEMP				Persons_2.UpdateLog(trg->ai.eventlog,0,EventLog::SEENBYPLAYERS);
//DeadCode RDH 27Mar98 			}
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 		elseif(trg->ai.eventlog->stage!=EventLog::TAKEOFF)
//DeadCode RDH 27Mar98 //TEMP			Persons_2.UpdateLog(trg->ai.eventlog,0,EventLog::SEENBYOTHERS);
//DeadCode RDH 27Mar98 		;
//DeadCode RDH 27Mar98 	return(false);
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 

//DEADCODE RDH 13/06/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE RDH 13/06/99 //Procedure		AttackSpareInLeadersFlight
//DEADCODE RDH 13/06/99 //Author		Jim Taylor
//DEADCODE RDH 13/06/99 //Date			Tue 4 Jun 1996
//DEADCODE RDH 13/06/99 //
//DEADCODE RDH 13/06/99 //Description	
//DEADCODE RDH 13/06/99 //
//DEADCODE RDH 13/06/99 //Inputs		
//DEADCODE RDH 13/06/99 //
//DEADCODE RDH 13/06/99 //Returns	
//DEADCODE RDH 13/06/99 //
//DEADCODE RDH 13/06/99 //------------------------------------------------------------------------------
//DEADCODE RDH 13/06/99 bool	ArtInt::AttackSpareInLeadersFlight(AirStruc* eye)
//DEADCODE RDH 13/06/99 {
//DEADCODE RDH 13/06/99 	AirStruc*	unf=(AirStrucPtr)*((AirStrucPtr)*eye->leader)->ai.unfriendly;
//DEADCODE RDH 13/06/99 	if (unf->leader)
//DEADCODE RDH 13/06/99 		unf=(AirStruc*)*unf->leader;
//DEADCODE RDH 13/06/99 	while (unf)
//DEADCODE RDH 13/06/99 	{
//DEADCODE RDH 13/06/99 		if (unf->ai.attacker==NULL)
//DEADCODE RDH 13/06/99 		{
//DEADCODE RDH 13/06/99 			eye->InterceptandRange(&unf->World);
//DEADCODE RDH 13/06/99 			if (unf->Range<RECOGNISERANGE)
//DEADCODE RDH 13/06/99 
//DEADCODE RDH 13/06/99 //	Decisions based on character/rules
//DEADCODE RDH 13/06/99 //	If rules say don't enagage wait until range is 1/2 mile
//DEADCODE RDH 13/06/99 //
//DEADCODE RDH 13/06/99 //
//DEADCODE RDH 13/06/99 //
//DEADCODE RDH 13/06/99 //
//DEADCODE RDH 13/06/99 //
//DEADCODE RDH 13/06/99 			{
//DEADCODE RDH 13/06/99 				SetEngage(eye,unf,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
//DEADCODE RDH 13/06/99 				return(true);
//DEADCODE RDH 13/06/99 			}
//DEADCODE RDH 13/06/99 		}
//DEADCODE RDH 13/06/99 		unf=(AirStrucPtr)*unf->follower;
//DEADCODE RDH 13/06/99 	}
//DEADCODE RDH 13/06/99 	//everybody is engaged
//DEADCODE RDH 13/06/99 	
//DEADCODE RDH 13/06/99 	if (	(unf)	&&	(unf->leader))
//DEADCODE RDH 13/06/99 	{//if there is a leader then go for it
//DEADCODE RDH 13/06/99 		SetEngage(eye,unf->Leader(),MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
//DEADCODE RDH 13/06/99 		return(true);
//DEADCODE RDH 13/06/99 	}
//DEADCODE RDH 13/06/99 	return(false);
//DEADCODE RDH 13/06/99 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AttackSpareInLeadersGroup
//Author		 //RDH 13/06/99
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::LeadersGroupInCombat(AirStruc* eye)
{
	bool incombat = false;
	AirStruc*	ldr = eye;
	if (eye->leader)
		ldr = (AirStruc*)eye->leader;
	if (	(ldr->fly.leadflight)
			&&	(ldr->formpos != 0)
		)
		ldr = ldr->fly.leadflight;

	AirStruc* ldr2;
	//rdh 25/6/99: don't process for player when he is leader
	if  (		(ldr->AcIsPlayer())
			&&	!(Save_Data.gamedifficulty[GD_AUTOVECTORING])
		)
	{
		incombat = false;
	}else
	{
		while (	(ldr)	&&	(!incombat))
		{
			ldr2 = ldr;
			while (ldr2)
			{
				if (		(ldr2->ai.unfriendly!=NULL)
						&&	(ldr2->ai.unfriendly->Status.size==AIRSTRUCSIZE)
						&&	(ldr2->nationality != ((AirStruc*)ldr2->ai.unfriendly)->nationality)
				   )
				{
					incombat = true;
					break;
				}
				ldr2=(AirStruc*)ldr2->follower;
			}
			ldr = ldr->fly.nextflight;
		}
	}
	return (incombat);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AttackSpareInLeadersGroup
//Author		 //RDH 13/06/99
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::AttackSpareInLeadersGroup(AirStruc* eye)
{
	AirStruc*	ldr = eye;
	if (eye->leader)
		ldr = (AirStruc*)eye->leader;
	if (	(ldr->fly.leadflight)
			&&	(ldr->formpos != 0)
		)
		ldr = ldr->fly.leadflight;
	//ldr is the Group Leader

	AirStruc* ldr2;
	AirStruc*	unfldr = NULL;
	//find an unfriendly engaged by this group
	while (	(ldr)	&&	(!unfldr))
	{
		ldr2 = ldr;
		while (ldr2)
		{
			if 	(		(ldr2->ai.unfriendly)
					&&	(ldr2->ai.unfriendly->Status.size==AIRSTRUCSIZE)
				)
				unfldr=(AirStrucPtr)(ldr2->ai.unfriendly);
			if (unfldr)
				break;
			ldr2=(AirStruc*)ldr2->follower;
		}
		ldr = ldr->fly.nextflight;
	}

	if(unfldr)
	{
		if (unfldr->leader)
			unfldr=(AirStruc*)*unfldr->leader;

		if (	(unfldr->fly.leadflight)
				&&	(unfldr->formpos != 0)
			)
			unfldr = unfldr->fly.leadflight;

		//unfldr is a GroupLeader
		AirStruc*	unf = unfldr;
		AirStruc*	unf2;
		AirStruc*	trg = NULL;
		AirStruc*	anytrg = NULL;
		int range = MILES50;
		int anyrange = MILES50;
		while (unf)
		{
			unf2 = unf;
			while (unf2)
			{
				eye->InterceptandRange(&unf2->World);
				if (unf2->ai.attacker==NULL)
				{
					if (unf2->Range<range)
					{
						trg = unf2;
						range = unf2->Range;
					}
				}else
				{
					if (unf2->Range<anyrange)
					{
						anytrg = unf2;
						anyrange = unf2->Range;
					}

				}
				unf2=(AirStruc*)unf2->follower;
			}
			unf = unf->fly.nextflight;
		}
//DeadCode CSB 07/07/99			MANOEUVRE manoeuvre;
//DeadCode CSB 07/07/99			if (range <	BREAKOFFRANGE)
//DeadCode CSB 07/07/99				manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 07/07/99			else
//DeadCode CSB 07/07/99				manoeuvre = MANOEUVRE_GAINHEIGHT;
		if (trg)
		{
//DeadCode CSB 07/07/99				SetEngage(eye,trg,manoeuvre,ANGLES_0Deg,ANGLES_0Deg, FALSE);
			SetEngage(eye,trg,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);	//CSB 07/07/99	
			return(true);
		}else
		{//everybody is engaged
			if (anytrg)
			{
//DeadCode CSB 07/07/99					SetEngage(eye,anytrg,manoeuvre,ANGLES_0Deg,ANGLES_0Deg, FALSE);
				SetEngage(eye,anytrg,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);	//CSB 07/07/99	
				return(true);
			}
		}
	}
	return(false);
}


//DeadCode RDH 27Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 27Mar98 //Procedure		SetEngage
//DeadCode RDH 27Mar98 //Author		Jim Taylor
//DeadCode RDH 27Mar98 //Date			Mon 10 Jun 1996
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Description	
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Inputs		Range should be eye .. trg
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Returns	
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 void	ArtInt::SetEngage(AirStrucPtr eye,AirStrucPtr trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	if (	eye->ai.unfriendly
//DeadCode RDH 27Mar98 		&&	eye->ai.unfriendly->Status.size==AIRSTRUCSIZE
//DeadCode RDH 27Mar98 		&& ((AirStrucPtr)*eye->ai.unfriendly)->ai.attacker==eye
//DeadCode RDH 27Mar98 		)
//DeadCode RDH 27Mar98 		((AirStrucPtr)*eye->ai.unfriendly)->ai.attacker=NULL;
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	if (trg)
//DeadCode RDH 27Mar98 	{
//DeadCode RDH 27Mar98 		if (eye->ai.unfriendly==trg)
//DeadCode RDH 27Mar98 		{	//informational
//DeadCode RDH 27Mar98 //TEMP			if (eye==Manual_Pilot.ControlledAC2)
//DeadCode RDH 27Mar98 //TEMP			{
//DeadCode RDH 27Mar98 //TEMP				if (trg->formpos==0 && trg->ai.eventlog->name)
//DeadCode RDH 27Mar98 //TEMP					eye->PlayerSequenceAudible(FIL_MUSIC_ENEMY_ACE_SEEN);
//DeadCode RDH 27Mar98 //TEMP				if (trg->waypoint)
//DeadCode RDH 27Mar98 //TEMP					switch (trg->waypoint->action)
//DeadCode RDH 27Mar98 //TEMP					{
//DeadCode RDH 27Mar98 //TEMP					case	wpstraffeno:
//DeadCode RDH 27Mar98 //TEMP						Persons_2.AddMessage(UserMsg::CLOSE,TEXT_ENEMYONGROUNDATTK,trg);
//DeadCode RDH 27Mar98 //TEMP					break;
//DeadCode RDH 27Mar98 //TEMP					case	wpballoonbustno:
//DeadCode RDH 27Mar98 //TEMP						Persons_2.AddMessage(UserMsg::CLOSE,TEXT_THREATTOBALLOON,trg);
//DeadCode RDH 27Mar98 //TEMP					break;
//DeadCode RDH 27Mar98 //TEMP					case	wpreccyno:
//DeadCode RDH 27Mar98 //TEMP						Persons_2.AddMessage(UserMsg::CLOSE,TEXT_ENEMYISRECONN,trg);
//DeadCode RDH 27Mar98 //TEMP					break;
//DeadCode RDH 27Mar98 //TEMP					case	wpartspotno:
//DeadCode RDH 27Mar98 //TEMP						Persons_2.AddMessage(UserMsg::CLOSE,TEXT_ENEMYISSPOTTER,trg);
//DeadCode RDH 27Mar98 //TEMP					break;
//DeadCode RDH 27Mar98 //TEMP					default:
//DeadCode RDH 27Mar98 //TEMP						if (trg->classtype->aerobaticfactor==AEROBATIC_LOW)
//DeadCode RDH 27Mar98 //TEMP							Persons_2.AddMessage(UserMsg::CLOSE,TEXT_ENEMYISBOMBER,trg);
//DeadCode RDH 27Mar98 //TEMP						else
//DeadCode RDH 27Mar98 //TEMP							Persons_2.AddMessage(UserMsg::CLOSE,TEXT_GM_ENEMYACCLOSE,trg);
//DeadCode RDH 27Mar98 //TEMP					}
//DeadCode RDH 27Mar98 //TEMP				else
//DeadCode RDH 27Mar98 //TEMP						if (trg->classtype->aerobaticfactor==AEROBATIC_LOW)
//DeadCode RDH 27Mar98 //TEMP							Persons_2.AddMessage(UserMsg::CLOSE,TEXT_ENEMYISBOMBER,trg);
//DeadCode RDH 27Mar98 //TEMP						else
//DeadCode RDH 27Mar98 //TEMP							Persons_2.AddMessage(UserMsg::CLOSE,TEXT_GM_ENEMYACCLOSE,trg);
//DeadCode RDH 27Mar98 //TEMP
//DeadCode RDH 27Mar98 //TEMP			}	
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 		else
//DeadCode RDH 27Mar98 		{	//new engage
//DeadCode RDH 27Mar98 //TEMP			if (eye==Manual_Pilot.ControlledAC2)
//DeadCode RDH 27Mar98 //TEMP				Persons_2.AddMessage(UserMsg::TIME,TEXT_GM_ENEMYACCLOSE,trg);
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	eye->ai.unfriendly=trg;
//DeadCode RDH 27Mar98 	eye->information=FALSE;
//DeadCode RDH 27Mar98 	eye->movecode=AUTO_COMBAT;
//DeadCode RDH 27Mar98 	eye->manoeuvretime=0;
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	if(trg)
//DeadCode RDH 27Mar98 		if (	!trg->ai.attacker
//DeadCode RDH 27Mar98 			||	((AirStrucPtr)*trg->ai.attacker)->ai.unfriendly!=trg
//DeadCode RDH 27Mar98 			)
//DeadCode RDH 27Mar98 			if (eye!=Manual_Pilot.ControlledAC2)				//JIM 01Sep96
//DeadCode RDH 27Mar98 				trg->ai.attacker=eye;
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	//if (trg->Range>MILES02)
//DeadCode RDH 27Mar98 	//	Do approach manoeuvre instead
//DeadCode RDH 27Mar98 	//else
//DeadCode RDH 27Mar98 		
//DeadCode RDH 27Mar98 		eye->ai.manoeuvre=MANOEUVRE_SELECT;
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 //TEMP	Timer_Code.AccelToggle(FALSE);
//DeadCode RDH 27Mar98 	Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	if (trg)
//DeadCode RDH 27Mar98 	{
//DeadCode RDH 27Mar98 		if (eye->ai.eventlog->stage==EventLog::TAKEOFF)
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 //TEMP		 	if(trg->ai.eventlog->stage!=EventLog::TAKEOFF)
//DeadCode RDH 27Mar98 //TEMP				Persons_2.UpdateLog(trg->ai.eventlog,0,EventLog::APPROACHED);
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 		else
//DeadCode RDH 27Mar98 			if  (	(Manual_Pilot.ControlledAC2->nationality !=eye->nationality)//RDH 21Nov96
//DeadCode RDH 27Mar98 				&&	(trg->ai.eventlog->stage==EventLog::TAKEOFF)//RDH 21Nov96
//DeadCode RDH 27Mar98 				)												//RDH 21Nov96
//DeadCode RDH 27Mar98 //TEMP				Persons_2.UpdateLog(eye->ai.eventlog,0,EventLog::HOSTILE);
//DeadCode RDH 27Mar98 				;
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 void	ArtInt::SetPreEngage(AirStrucPtr eye,AirStrucPtr trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	eye->ai.unfriendly=trg;
//DeadCode RDH 27Mar98 	eye->information=FALSE;
//DeadCode RDH 27Mar98 	eye->movecode=AUTO_PRECOMBAT;
//DeadCode RDH 27Mar98 	eye->manoeuvretime=0;
//DeadCode RDH 27Mar98 	if (trg)
//DeadCode RDH 27Mar98 	{
//DeadCode RDH 27Mar98 		if (	!trg->ai.attacker
//DeadCode RDH 27Mar98 			||	((AirStrucPtr)*trg->ai.attacker)->ai.unfriendly!=trg
//DeadCode RDH 27Mar98 			)
//DeadCode RDH 27Mar98 			trg->ai.attacker=eye;
//DeadCode RDH 27Mar98 		if (eye==Manual_Pilot.ControlledAC2)
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 //TEMP			Persons_2.AddMessage(UserMsg::ATTACK,TEXT_GM_ASSIGNEDAC,trg);
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 	//if (trg->Range>MILES02)
//DeadCode RDH 27Mar98 	//	Do approach manoeuvre instead
//DeadCode RDH 27Mar98 	//else
//DeadCode RDH 27Mar98 		eye->ai.manoeuvre=MANOEUVRE_SELECT;
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 AirStrucPtr	ArtInt::SetFollowerWhoEngage(AirStrucPtr eye,AirStrucPtr trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	AirStrucPtr	tmpt=trg;
//DeadCode RDH 27Mar98 	if (tmpt==NULL)	return(tmpt);
//DeadCode RDH 27Mar98 		switch (eye->ai.followeraction)
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 		case	NF_CircleSingle:
//DeadCode RDH 27Mar98 		case	NF_PersonalThreat:
//DeadCode RDH 27Mar98 			tmpt=NULL;
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 		case	NF_Single:
//DeadCode RDH 27Mar98 			tmpt=nextfol(trg,TRUE);
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 		case	NF_Double:
//DeadCode RDH 27Mar98 			tmpt=nextfol(trg,FALSE);
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 		case	NF_ReDouble:
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98 		return	(tmpt);
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 AirStrucPtr	ArtInt::SetFollowerPreEngage(AirStrucPtr eye,AirStrucPtr trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	//Improvement:
//DeadCode RDH 27Mar98 	//	Go for next most skilled rather than next in formation.
//DeadCode RDH 27Mar98 	//  (Assume leader has gone for highest skill, so perform skill comparison
//DeadCode RDH 27Mar98 	eye->information=FALSE;
//DeadCode RDH 27Mar98 	AirStrucPtr	tmpt=trg;
//DeadCode RDH 27Mar98 	if (!eye->AircraftDamaged() && eye->classtype->aerobaticfactor!=AEROBATIC_LOW)								//JIM 29Aug96
//DeadCode RDH 27Mar98 	if (eye->movecode<AUTO_PRECOMBAT)
//DeadCode RDH 27Mar98 	{
//DeadCode RDH 27Mar98 		tmpt = SetFollowerWhoEngage(eye,trg);
//DeadCode RDH 27Mar98 		SetPreEngage(eye,tmpt);
//DeadCode RDH 27Mar98 		if (tmpt)
//DeadCode RDH 27Mar98 			trg=tmpt;
//DeadCode RDH 27Mar98 	}	
//DeadCode RDH 27Mar98 	return(trg);
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 AirStrucPtr	ArtInt::SetFlightWhoEngage(AirStrucPtr eye,AirStrucPtr trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	AirStrucPtr	tmpt=trg;
//DeadCode RDH 27Mar98 	if (tmpt==NULL)	return(tmpt);
//DeadCode RDH 27Mar98 		switch (eye->ai.leaderaction)
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 		case	NL_OnCourse:		//no change in course
//DeadCode RDH 27Mar98 		case	NL_CircleSingles:	//not assigned during approach
//DeadCode RDH 27Mar98 		case	NL_CircleFlights:	//but fly over and assign later
//DeadCode RDH 27Mar98 			tmpt=NULL;		//CAN'T TELL THESE APART FROM HERE!
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 		case	NL_Flights:			//only assign if there are spare flights
//DeadCode RDH 27Mar98 			tmpt=nextfl(trg,FALSE);
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 		case	NL_DoubleFlighs:	//assign to next flight even if already assigned
//DeadCode RDH 27Mar98 			tmpt=nextfl(trg,TRUE);
//DeadCode RDH 27Mar98 			if (tmpt)	trg=tmpt;
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 		case	NL_PrevRipple:		//assign to curr flight, but from unassigned down
//DeadCode RDH 27Mar98 			tmpt=nextfol(trg,FALSE);
//DeadCode RDH 27Mar98 			if (tmpt==NULL)
//DeadCode RDH 27Mar98 				tmpt=nextfl(trg,TRUE);
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 		case	NL_PrevDouble:		//assign to curr flight from leader down
//DeadCode RDH 27Mar98 //DeadCode JIM 19Aug96 			tmpt=nextfol(trg,TRUE);
//DeadCode RDH 27Mar98 			tmpt=trg;
//DeadCode RDH 27Mar98 		break;
//DeadCode RDH 27Mar98 		}
//DeadCode RDH 27Mar98  		return (tmpt);
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 AirStrucPtr	ArtInt::SetFlightPreEngage(AirStrucPtr eye,AirStrucPtr trg)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	eye->information=FALSE;
//DeadCode RDH 27Mar98 	AirStrucPtr	tmpt=trg;
//DeadCode RDH 27Mar98 
//DeadCode RDH 27Mar98 	if (eye->movecode<AUTO_PRECOMBAT)
//DeadCode RDH 27Mar98 	{
//DeadCode RDH 27Mar98 		if (eye->ai.leaderaction==NL_OnCourse)
//DeadCode RDH 27Mar98 			RETURN(trg);
//DeadCode RDH 27Mar98 		else
//DeadCode RDH 27Mar98 			tmpt=SetFlightWhoEngage(eye,trg);
//DeadCode RDH 27Mar98 		if (tmpt)	trg=tmpt;
//DeadCode RDH 27Mar98 		//assign a/c from tmpt to flight
//DeadCode RDH 27Mar98 		if (!eye->AircraftDamaged() && eye->classtype->aerobaticfactor!=AEROBATIC_LOW)								//JIM 29Aug96
//DeadCode RDH 27Mar98 			SetPreEngage(eye,tmpt);
//DeadCode RDH 27Mar98 		AirStrucPtr	currtrg=tmpt;
//DeadCode RDH 27Mar98 		AirStrucPtr	currfol=eye;
//DeadCode RDH 27Mar98 		while ((currfol=*currfol->follower)!=NULL)
//DeadCode RDH 27Mar98 			currtrg=SetFollowerPreEngage(currfol,currtrg);
//DeadCode RDH 27Mar98 	}
//DeadCode RDH 27Mar98 	RETURN	(trg);
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 27Mar98 //Procedure		nextfl
//DeadCode RDH 27Mar98 //Author		Jim Taylor
//DeadCode RDH 27Mar98 //Date			Wed 26 Jun 1996
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Description	
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Inputs		
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //Returns	
//DeadCode RDH 27Mar98 //
//DeadCode RDH 27Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 27Mar98 AirStrucPtr	ArtInt::nextfl(AirStrucPtr trg,Bool unassigned)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	AirStrucPtr	t2=trg;
//DeadCode RDH 27Mar98 	if (trg)
//DeadCode RDH 27Mar98 		repeat
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 			if (trg->fly.nextflight)
//DeadCode RDH 27Mar98 				trg=trg->fly.nextflight;
//DeadCode RDH 27Mar98 			else
//DeadCode RDH 27Mar98 				if (trg->fly.leadflight)
//DeadCode RDH 27Mar98 					trg=trg->fly.leadflight;
//DeadCode RDH 27Mar98 				else
//DeadCode RDH 27Mar98 					return(NULL);
//DeadCode RDH 27Mar98 			if (!!trg->ai.attacker <=!!unassigned)
//DeadCode RDH 27Mar98 				return(trg);
//DeadCode RDH 27Mar98 		}	while (t2!=trg);
//DeadCode RDH 27Mar98 	return(NULL);
//DeadCode RDH 27Mar98 }
//DeadCode RDH 27Mar98 AirStrucPtr	ArtInt::nextfol(AirStrucPtr trg,Bool unassigned)
//DeadCode RDH 27Mar98 {
//DeadCode RDH 27Mar98 	AirStrucPtr	t2=trg;
//DeadCode RDH 27Mar98 	if (trg)
//DeadCode RDH 27Mar98 		repeat
//DeadCode RDH 27Mar98 		{
//DeadCode RDH 27Mar98 			if (trg->follower)
//DeadCode RDH 27Mar98 				trg=*trg->follower;
//DeadCode RDH 27Mar98 			else
//DeadCode RDH 27Mar98 				if (trg->leader)
//DeadCode RDH 27Mar98 					trg=*trg->leader;
//DeadCode RDH 27Mar98 				else
//DeadCode RDH 27Mar98 					return(NULL);
//DeadCode RDH 27Mar98 			if (!!trg->ai.attacker <=!!unassigned)
//DeadCode RDH 27Mar98 				return(trg);
//DeadCode RDH 27Mar98 		}	while (t2!=trg);
//DeadCode RDH 27Mar98 	return(NULL);
//DeadCode RDH 27Mar98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CountFormation
//Author		Jim Taylor
//Date			Mon 10 Jun 1996
//
//Description	If the aircraft is on its own then return a total number of a/c
//				spotted so-far this frame.
//				If the aircraft is in formation then count up number of other
//				a/c in the formation.
//				GuessFormationSize will guess if a singleton is spotted
//				CountFormationSize will say "1"
//
//Inputs		A/C formation member
//
//Returns		Integer count
//
//------------------------------------------------------------------------------
int		ArtInt::GuessFormationSize(AirStrucPtr caller, AirStrucPtr trg)
{
//DEADCODE RDH 23/06/99 	if (!trg->leader || trg->information)
//DEADCODE RDH 23/06/99 	{
		if (trg->leader)
			trg=(AirStrucPtr)*trg->leader;
		if (		(!trg->fly.leadflight)
				||	(trg->information)
				||	(AircraftAreClose(caller, trg->fly.leadflight)) //trg and its leader is close so assume rest is a well //RDH 12/06/99
			)
		{	//count all a/c in formation
			if (trg->fly.leadflight)
				trg=trg->fly.leadflight;
			int	acc=0;
			do
			{
				AirStrucPtr	tf=trg;
				do
				{
					acc++;
					tf=(AirStrucPtr)*tf->follower;
				}
				while (tf && tf->information);
				trg=trg->fly.nextflight;
			}
//DEADCODE RDH 12/06/99 			while (trg && trg->information);
			while (trg);		//we want all ac 
			return acc;
		}
		else
		{	//count all a/c in flight
			int	acc=0;
			AirStrucPtr	tf=trg;
			do
			{
				acc++;
				tf=(AirStrucPtr)*tf->follower;
			}
			while (tf && tf->information);
			return acc;
		}
//DEADCODE RDH 23/06/99 	}
//DEADCODE RDH 23/06/99 	else	//on our own
//DEADCODE RDH 23/06/99 		return (spotcount);
}

int		ArtInt::CountFormationSize(AirStrucPtr trg)
{
	if (!trg->leader || trg->information)
	{
		if (trg->leader)
			trg=(AirStrucPtr)*trg->leader;
		if (!trg->fly.leadflight || trg->information)
		{	//count all a/c in formation
			if (trg->fly.leadflight)
				trg=trg->fly.leadflight;
			int	acc=0;
			do
			{
				AirStrucPtr	tf=trg;
				do
				{
					acc++;
					tf=(AirStrucPtr)*tf->follower;
				}
				while (tf && tf->information);
				trg=trg->fly.nextflight;
			}
			while (trg && trg->information);
			return acc;
		}
		else
		{	//count all a/c in flight
			int	acc=0;
			AirStrucPtr	tf=trg;
			do
			{
				acc++;
				tf=(AirStrucPtr)*tf->follower;
			}
			while (tf && tf->information);
			return acc;
		}
	}
	else	//on our own
		return (1);
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SameFlight
//Author		Jim Taylor
//Date			Tue 25 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::SameFlight(AirStrucPtr a,AirStrucPtr b)
{
	if (a && a->Status.size==AIRSTRUCSIZE)
	{
		if (a->leader)	a=*a->leader;
		if (a->fly.leadflight)	a=a->fly.leadflight;
	}
	if (b && a->Status.size==AIRSTRUCSIZE)
	{
		if (b->leader)	b=*b->leader;
		if (b->fly.leadflight)	b=b->fly.leadflight;
	}
	return  (a==b);
}

void	ArtInt::ClearFollowerFormation(AirStrucPtr ac)
{
	if (ac)
		while (ac)
		{
			AirStrucPtr fol=ac;
			while (fol)
			{
				fol->information=FALSE;
				fol=*fol->follower;
			}
			ac=ac->fly.nextflight;
		}

}


void	ArtInt::AllEngage(AirStrucPtr leadac)
{
	AutoMoveCodeTypeSelect	m=leadac->movecode;
	AirStrucPtr	w=leadac;
	while(w)
	{
		AirStrucPtr	f=w;
		while (f)
		{
			if (f->movecode==m)
			if (!f->AircraftDamaged() && f->classtype->aerobaticfactor!=AEROBATIC_LOW)								//JIM 29Aug96
				Art_Int.SetEngage(f,*f->ai.unfriendly,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
			f=*f->follower;
		}
		w=w->fly.nextflight;
	}
}

void	ArtInt::AllBreakOff(AirStrucPtr leadac)
{
	AutoMoveCodeTypeSelect	m=leadac->movecode;
	AirStrucPtr	w=leadac;
	while(w)
	{
		AirStrucPtr	f=w;
		if (leadac->movecode==AUTO_COMBAT)
		while (f)
		{
			if (f->movecode==AUTO_COMBAT && f->ai.manoeuvre<=MANOEUVRE_TOPCOVER)
				Art_Int.BreakOff(f);
			f=*f->follower;
		}
		else
		while (f)
		{
			if (f->movecode==m)
				Art_Int.BreakOff(f);
			else if (f->movecode==AUTO_COMBAT)
				//25/6/99 rdh when leader is in precombat and rest are in cobat then break is ok
				Art_Int.BreakOff(f);

			f=*f->follower;
		}
		w=w->fly.nextflight;
	}
}

void	ArtInt::BreakOff(AirStrucPtr ac)
{
// ac that break off have no owner until they engage again

	if (_DPlay.Implemented)//AMM 12Mar99
	{
		if (ac->CommsOwner==Persons2::PlayerSeenAC->uniqueID.count)		//AMM 12Mar99
		{
//			_DPlay.OwnerChange(255,ac);									//AMM 12Mar99
			_DPlay.AddAIACToPositionList(ac);			//AMM 12Mar99
		}
	}

	ac->movecode=AUTO_FOLLOWWP;
	if (		(ac->ai.unfriendly)
			&&	(ac->ai.unfriendly->Status.size==AIRSTRUCSIZE)
		)
	{//there is one call where the break off is happening because the
		//pilot has been damaged and is of low morale. He might not be in combat
		AirStrucPtr unf=*ac->ai.unfriendly;
		ac->ai.unfriendly=NULL;
		if (unf && unf->ai.attacker==ac)
			unf->ai.attacker=NULL;
	}
//DeadCode AMM 05Jul99 	if (ac->ai.eventlog->stage==EventLog::TAKEOFF)
//DeadCode AMM 05Jul99 		_Miles.DiscardMusic();
}

bool	ArtInt::OkToAccel()
{
	//need to test for piloted A/C
	AirStrucPtr tmp;
	if (Manual_Pilot.ControlledAC2->waypoint==NULL)
	{
//TEMP	 	Persons_2.AddMessage(UserMsg::TIME,TEXT_ENTERLANDING,Manual_Pilot.ControlledAC2->ai.homebase);//JIM 06Dec96
		return(false);
	}
	if (Manual_Pilot.ControlledAC2->Status.deadtime)
	{
		return(false);
	}
	for (int i=0;i<ACARRAYSIZE;i++)
	{
		if (tmp=ACArray[i],
				tmp!=0
			&&	tmp->movecode==AUTO_COMBAT
			&&	tmp->ai.unfriendly
			&&	Manual_Pilot.ControlledAC2!=tmp
			&&	(Manual_Pilot.ControlledAC2->InterceptandRange (tmp),tmp->Range</*METRES*/4000000)
			)
		{
//DeadCode RDH 23Oct96 			Persons_2.AddMessage(UserMsg::TIME,TEXT_GM_ENEMYACNEAR,ACArray[i]);//JIM 25Jul96
//TEMP			if (tmp->nationality==Manual_Pilot.ControlledAC2->nationality)
//TEMP				Persons_2.AddMessage(UserMsg::TIME,//TEMP,ACArray[i]->ai.unfriendly);//JIM 25Jul96
//TEMP			else
//TEMP				Persons_2.AddMessage(UserMsg::TIME,TEXT_NULL,ACArray[i]);//JIM 25Jul96
			return(false);
		}
	}
	return(true);
}

void	ArtInt::PersonalThreatMsg(AirStrucPtr trg,AirStrucPtr agg)
{
  		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);	


		AirStruc* plyrbuddy = Manual_Pilot.ControlledAC2->FindBuddy();
		AirStruc* buddy = trg->FindBuddy();

		if  (		(trg->leader)
				&&	(trg->ai.elementtactics == WELDEDWING)
				&&	(trg->ai.unfriendly)
				&&	(trg->ai.unfriendly->Status.size==AIRSTRUCSIZE)
				&&	(trg->Leader()->ai.unfriendly)
				&&	(trg->Leader()->ai.unfriendly->Status.size==AIRSTRUCSIZE)
				&&	(trg->ai.Unfriendly() == trg->Leader()->ai.Unfriendly())
			)
		{//can't cover any longer
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTCLEAR, MSG_CLEAR, trg, NULL, trg->Leader())); //RDH 17/06/99
		}else
		 if (		(rndpc <RND10PC)
				&&	(trg->classtype->visible == F86)
				&&	(		(Manual_Pilot.ControlledAC2->World.Y - trg->World.Y) > FT_3000)
				&&	(trg->PlayerInGroup())
				&&	(RangeFromTo(trg, Manual_Pilot.ControlledAC2) < ENGAGERANGE)
				&&	(plyrbuddy)
			)

		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_INTROUBLE, MSG_PERSONALTHREAT, plyrbuddy, agg, Manual_Pilot.ControlledAC2));
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_INTROUBLE_REPLY, MSG_PERSONALTHREAT_REPLY_DELAY, trg, NULL, Manual_Pilot.ControlledAC2));
		}else
		{
			if  (	(rndpc <RND25PC) && (buddy)	 &&	(agg->classtype->phrasename == PHRASE_MIGS)
				)
			{
				if (buddy->AcIsPlayer())//we don't have script for player to say this! //RDH 28/05/99
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLOSEANDFIRING, MSG_PERSONALTHREAT, trg, agg, buddy));
				else
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLOSEANDFIRING, MSG_PERSONALTHREAT, buddy, agg, trg));
			}
			else
			{
				if (buddy)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_THEYARESHOOTING, MSG_PERSONALTHREAT, trg, agg, buddy));
				else
				{
					if  (		(trg->nationality == Manual_Pilot.ControlledAC2->nationality)
							&&	(rndpc <RND10PC)
						)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_THEYARESHOOTING, MSG_PERSONALTHREAT, trg, agg, Manual_Pilot.ControlledAC2));
				}
			}
		}
   
}
bool	ArtInt::PersonalThreat(AirStrucPtr trg,AirStrucPtr agg,bool process)
{
// 	return FALSE;
	
	if (trg->nationality==agg->nationality)		  //MS 11/05/99
		return(false);

	if (	trg && agg
		&&	trg->Status.size==AIRSTRUCSIZE
		&&	agg->Status.size==AIRSTRUCSIZE	)
	{	//It is a valid pairing - now some quick throwouts:
		//If aircraft already committed

		//if trg dead
		if	(trg->Status.deadtime)
			return(false);

		//if trg is bomber
		if	(trg->classtype->aerobaticfactor==AEROBATIC_LOW)		  //RDH 03/03/99
		{
			if (trg->formpos)
				trg = trg->fly.leadflight;
			AirStruc*  escortleader = trg->FindAirEscortLeader();
//DEADCODE RDH 01/07/99 			if (!escortleader)
//DEADCODE RDH 01/07/99 			{
//DEADCODE RDH 01/07/99 				if (trg->nationality == Manual_Pilot.ControlledAC2->nationality)
//DEADCODE RDH 01/07/99 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_AMUNDERATTACK, MSG_PERSONALTHREAT, trg, agg, Manual_Pilot.ControlledAC2));
//DEADCODE RDH 01/07/99 			}else
			if (escortleader)
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_AMUNDERATTACK, MSG_PERSONALTHREAT, trg, trg, escortleader));

			return(false);
		}

		//if trg is in combat and has a trg in standard contact, 1 in 16 chance of reacting
		//and range is short
		int range = 0;
		if (		(trg->ai.unfriendly)
				&&	(trg->ai.unfriendly->Status.size==AIRSTRUCSIZE)
		   )
			range=trg->Distance3D(&(trg->ai.unfriendly)->World);

		if (	trg->movecode==AUTO_COMBAT
			&&	(range 	< INSIDEWEAPONSRANGE)
			&&	trg->ai.unfriendly
			&&	(trg->ai.unfriendly->Status.size==AIRSTRUCSIZE)
			&&	(trg->ai.Unfriendly()->ai.attacker==trg)
			&&	Math_Lib.rnd(16)
			)
			return(false);
		//if trg and agg on same side, 1 in 16 chance of reacting
//DEADCODE DAW 11/05/99 		if (trg->nationality==agg->nationality && Math_Lib.rnd(16))
//DEADCODE DAW 11/05/99 			return(false);

		//if trg is player come out of accel
		if (trg==Manual_Pilot.ControlledAC2)
		{
//TEMP			Persons_2.AddMessage(UserMsg::ATTACKED,TEXT_TAKINGHITS,agg);
//TEMP			Timer_Code.AccelToggle(FALSE);
				OverLay.CancelAccel();
//DEADCODE DAW 10/05/99 			Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);			  //RDH 03/03/99
		}

		if (Manual_Pilot.ControlledAC2 == agg)
			agg = Persons2::PlayerGhostAC;

		//if agg is computer controlled and if trg is not agg unfriendly don't react
		if  (		(agg != Persons2::PlayerGhostAC)
				&&	(agg->ai.unfriendly != trg)
			)
			return(false);

		PersonalThreatMsg(trg, agg);								  //RDH 15/06/99
		MANOEUVRE manoeuvre = MANOEUVRE_SELECT;
		MANOEUVRE goodmanoeuvre = MANOEUVRE_SELECT;
		if 	(trg->ai.combatskill >= SKILL_VETERAN)
			 goodmanoeuvre = MANOEUVRE_SPLITS;

		if((trg->classtype->visible == F86) && (!Math_Lib.rnd(2)))	//CSB 08/07/99	
				goodmanoeuvre = MANOEUVRE_DIVINGSPIN;				//CSB 08/07/99

		if 	(trg->ai.combatskill >= SKILL_REGULAR)
		{
			RndVal	rndnum = Math_Lib.rnd();
			if	(rndnum < RND25PC)
				manoeuvre = MANOEUVRE_SCISSORS;
			else if	(rndnum < RND50PC)
				manoeuvre = MANOEUVRE_BREAKTURN;
			else
				manoeuvre = goodmanoeuvre;						  //RDH 15/06/99 //RDH 20/06/99
		}
		if (		(trg->ai.unfriendly)
				&&	(trg->ai.unfriendly->Status.size==AIRSTRUCSIZE)
			)
		{//target already has an unfriendly ac
			if (trg->ai.unfriendly !=agg)
				SetEngage(trg,agg,manoeuvre,ANGLES_0Deg,ANGLES_0Deg, FALSE);	//agg is different
			else
			{//change manoeuvre in response
				trg->ai.manoeuvre  = manoeuvre;
				trg->ai.ManStep   = 0;
				
			}

		}else
		{//
			SetEngage(trg,agg,manoeuvre,ANGLES_0Deg,ANGLES_0Deg, FALSE);
		}															  //RDH 15/06/99
			
		return(true);
	}
	else
		return(false);
}


void	FormationItem::BreakForm()
{ //This code now protects itself against stopped trucks and getting called twice.

//DeadCode AMM 01Jun98 	if (_DPlay.Implemented)										//ARM 06Dec96
//DeadCode AMM 01Jun98 		return;

//DeadCode DAW 29Jun99 	movecode=AUTO_NOPPILOT;										//JIM 15Oct96
	FormationItemPtr	replacement=NULL;
//DeadCode JIM 15Oct96 	if (follower)
	replacement=follower;
	bool	gottrain=(Persons2::getbandfromUID(uniqueID.count)==RedTrainBAND);//DAW 22Jun99
	FormationItemPtr	user=NULL;
	if (leader)
	{
		user=leader;

		while (user && user->follower!=this)
			user=user->follower;
		if (!user && movecode==AUTO_NOPPILOT)
			return;				//hopefully already dead so don't remove again!
		assert(user&&"not member of leaders convoy!");
		user->follower=replacement;
		if (replacement && gottrain)
			while (replacement)
			{
				replacement->movecode=AUTO_NOPPILOT;
				replacement=replacement->follower;
			}
	}
	else
	{
		if	(replacement)
		{
			replacement->formpos=formpos;
			replacement->leader=NULL;
			leader=replacement;
		}
		user=follower;
		while (user)
		{
			if (user->leader==this)
				user->leader=replacement;
			if (gottrain)
				user->movecode=AUTO_NOPPILOT;
			user=user->follower;
		}
	}
	movecode=AUTO_NOPPILOT;										//JIM 15Oct96
//DeadCode DAW 29Jun99 	leader=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakForm
//Author		Jim Taylor
//Date			Thu 3 Jun 1999
//
//Description	Break aircaft out because he is dead usually.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::BreakForm()
{

//DeadCode AMM 01Jun98 	if (_DPlay.Implemented)										//ARM 06Dec96
//DeadCode AMM 01Jun98 		return;

	if (this==Manual_Pilot.ControlledAC2)
	{
		OverLay.CancelAccel();
		//TEMP		Timer_Code.AccelToggle(FALSE);
//DEADCODE DAW 10/05/99 		Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);
	}

	AirStrucPtr	replacement=NULL;
	if (fly.nextflight)
		replacement=fly.nextflight;
	if (follower)
		replacement=*follower;
	if (	formpos==0
		&&	this!=Manual_Pilot.ControlledAC2
//DeadCode JIM 02Dec96 		&&	ai.eventlog->stage!=EventLog::TAKEOFF
		&&  replacement											//RDH 01Dec96
		)
//TEMP		if (replacement==Manual_Pilot.ControlledAC2)
//TEMP			Persons_2.AddMessage(UserMsg::GOHOME,TEXT_ASSUMELEAD,despos);
//TEMP		else
//TEMP			Persons_2.AddMessage(UserMsg::GOHOME,TEXT_LEADERKILLED,despos);
		 ;
	if (replacement)
	{	//better version										//JIM 02Dec96
//DEADCODE JIM 09/07/99 		replacement->formpos=formpos;
		replacement->information=FALSE;								  //JIM 09/07/99
		if (replacement->leader==this)
			replacement->leader=NULL;
		if (replacement->fly.leadflight==this)
			replacement->fly.leadflight=NULL;
		if (!this->formpos || replacement->position())		  //JIM 09/07/99	//CSB 12/07/99
			replacement->formpos=formpos;							  //JIM 09/07/99
		if (	replacement->fly.nextflight==NULL
			&&	fly.nextflight!=replacement
			)
			replacement->fly.nextflight=fly.nextflight;
	}
	AcArrayItterator	user;
	while (user.Next())
		if (user)
		{
			if (user->leader==this || user->fly.leadflight==this)
			{
				if (user->leader==this)
					user->leader=replacement;
				if (user->fly.leadflight==this)
					user->fly.leadflight=replacement;
				user->information=FALSE;
			}

			if (user->follower==this)
				user->follower=replacement;
			if (user->fly.nextflight==this)
				user->fly.nextflight=replacement;

			if (user->ai.unfriendly==this)
				user->ai.unfriendly=NULL;
			if (user->ai.attacker==this)
				user->ai.attacker=NULL;
		}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayerHitConvoy
//Author		R. Hyde 
//Date			Thu 12 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode DAW 27Jun99 void	ArtInt::PlayerHitConvoy(FormationItemPtr f1)
//DeadCode DAW 27Jun99 {
//DeadCode DAW 27Jun99 	FormationItemPtr f=f1->leader;
//DeadCode DAW 27Jun99 	if (f==NULL)
//DeadCode DAW 27Jun99 		f=f1;
//DeadCode DAW 27Jun99 	AirStrucPtr p=Manual_Pilot.ControlledAC2;
//DeadCode DAW 27Jun99 	if (p->leader==NULL && p->follower!=NULL && p->movecode!=AUTO_STRAFFE)
//DeadCode DAW 27Jun99 		if (p->waypoint && p->waypoint->target!=f)
//DeadCode DAW 27Jun99 		{	//all of players flight will attack convoy...
//DeadCode DAW 27Jun99 			//insert an extra waypoint to that effect
//DeadCode DAW 27Jun99 			WayPointPtr w=new WayPoint;
//DeadCode DAW 27Jun99 			WayPointPtr o=p->waypoint;
//DeadCode DAW 27Jun99 			if (p->waypoint->prev==NULL)
//DeadCode DAW 27Jun99 			{	//no prev, but I have stuff pointing there!
//DeadCode DAW 27Jun99 				*w=*p->waypoint;
//DeadCode DAW 27Jun99 				w->uniqueID.count=UID_Null;
//DeadCode DAW 27Jun99 				w->next=p->waypoint->next;
//DeadCode DAW 27Jun99 				p->waypoint->next=w;
//DeadCode DAW 27Jun99 				w->prev=p->waypoint;
//DeadCode DAW 27Jun99 				if (w->next)
//DeadCode DAW 27Jun99 					w->next->prev=w;
//DeadCode DAW 27Jun99 				w=w->prev;
//DeadCode DAW 27Jun99 			}
//DeadCode DAW 27Jun99 			else
//DeadCode DAW 27Jun99 			{
//DeadCode DAW 27Jun99 				w->next=p->waypoint;
//DeadCode DAW 27Jun99 				w->prev=p->waypoint->prev;
//DeadCode DAW 27Jun99 				p->waypoint->prev=w;
//DeadCode DAW 27Jun99 				w->prev->next=w;
//DeadCode DAW 27Jun99 				w->uniqueID.count=UID_Null;
//DeadCode DAW 27Jun99 			}
//DeadCode DAW 27Jun99 
//DeadCode DAW 27Jun99 //DeadCode AMM 10Jun98 			w->uniqueID.deaded=TRUE;							//RJS 27Feb98
//DeadCode DAW 27Jun99 //DeadCode AMM 30Nov98 			w->uniqueID.commsmove=TRUE;							//AMM 10Jun98
//DeadCode DAW 27Jun99 			w->Status.deaded=TRUE;								//AMM 30Nov98
//DeadCode DAW 27Jun99 			p->movecode=AUTO_STRAFFE;
//DeadCode DAW 27Jun99 			w->World.X=0;
//DeadCode DAW 27Jun99 			w->World.Y=METRES4000;
//DeadCode DAW 27Jun99 			w->World.Z=0;
//DeadCode DAW 27Jun99 			w->range=METRES3000-METRES500;
//DeadCode DAW 27Jun99 			w->vel=0;
//DeadCode DAW 27Jun99 			w->eta=0;
//DeadCode DAW 27Jun99 			w->action=wpdivebombstraffeno;
//DeadCode DAW 27Jun99 			w->target=f;
//DeadCode DAW 27Jun99 			while (p)
//DeadCode DAW 27Jun99 			{
//DeadCode DAW 27Jun99 				if (p->waypoint==o)
//DeadCode DAW 27Jun99 					p->waypoint=w;
//DeadCode DAW 27Jun99 				p=*p->follower;
//DeadCode DAW 27Jun99 			}
//DeadCode DAW 27Jun99 		}
//DeadCode DAW 27Jun99 		else
//DeadCode DAW 27Jun99 			if (p->waypoint && f->follower && f->Status.deadtime)
//DeadCode DAW 27Jun99 			   p->waypoint->target=f->follower;
//DeadCode DAW 27Jun99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessWPEvents
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::ProcessWPEvents()
{
//TempCode RDH 27Mar98 	Blue ac will have events on their waypoints to launch the MiGs
//TempCode RDH 27Mar98 	Decide here which MiGs to launch
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 	if (there hasn't been a launch against group trg is in)
//TempCode RDH 27Mar98 	if (trg == FB)
//TempCode RDH 27Mar98 	{
//TempCode RDH 27Mar98 		if (trg is escorted)
//TempCode RDH 27Mar98 			LaunchMiGs(trg,SPLITFORCE);
//TempCode RDH 27Mar98 		else
//TempCode RDH 27Mar98 			LaunchMiGs(trg,ATTACKBOMBERSONLY);
//TempCode RDH 27Mar98 	}else if (trg is not escorting)
//TempCode RDH 27Mar98 		LaunchMiGs(trg, ATTACKWEAKNESSES);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchMiGs
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::LaunchMiGs(AirStruc* trg,tAggressionLevel al)
{

//TempCode RDH 27Mar98 1	Choose squadron with al == aggressionlevel, if none try > , last resort go for <
//TempCode RDH 27Mar98 		this determines aggressionlevel, morale and ability
//TempCode RDH 27Mar98 2	Choose number of aircraft to launch, 150% of US?
//TempCode RDH 27Mar98 3	Combat ability determines number of wingmen:
//TempCode RDH 27Mar98 		range from three leader to 50% leaders
//TempCode RDH 27Mar98 		determine NumWingMenPerFlight
//TempCode RDH 27Mar98 		We need at  least three leaders. One decoy, and two for split forces
//TempCode RDH 27Mar98 4	After bfield is loaded there is a chance that a threatlevel will be increased to simulate 	hotheads.
//TempCode RDH 27Mar98 5	If no US aircraft near, launch as a ghost squadron
//TempCode RDH 27Mar98 6	Good chance of GCI directing MiG too low
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 	If (spotdefence required)
//TempCode RDH 27Mar98 	{
//TempCode RDH 27Mar98 		BfEventStaticRoundAbout
//TempCode RDH 27Mar98 		BfEventStandardPointDefence
//TempCode RDH 27Mar98 		BfEventPatrolling3Levels
//TempCode RDH 27Mar98 	}	
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 	if (NumWingMenPerFlight <3)
//TempCode RDH 27Mar98 		elementtactics = LOOSEDEUCE or SWORDANDSHIELD
//TempCode RDH 27Mar98 	else
//TempCode RDH 27Mar98 		elementtactics = LINEASTERN or LINEABREAST
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 	switch (aggressionlevel)
//TempCode RDH 27Mar98 	{
//TempCode RDH 27Mar98 		case	TRAINING:
//TempCode RDH 27Mar98 		{
//TempCode RDH 27Mar98 			BFEventSanctuaryPatrol
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 			break;
//TempCode RDH 27Mar98 		}
//TempCode RDH 27Mar98 		case	DEFENSIVE:
//TempCode RDH 27Mar98 		{
//TempCode RDH 27Mar98 			BFEventSanctuaryPatrol
//TempCode RDH 27Mar98 			BFEventSafePatrol
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 			break;
//TempCode RDH 27Mar98 		}
//TempCode RDH 27Mar98 		case	ATTACKBOMBERSONLY:
//TempCode RDH 27Mar98 		{
//TempCode RDH 27Mar98 			//note these are just ways of getting at bombers
//TempCode RDH 27Mar98 			//actual attack is part of acm
//TempCode RDH 27Mar98 			BFEventEndRunDecoy
//TempCode RDH 27Mar98 			BFEventSlightOfHand
//TempCode RDH 27Mar98 			BFEventWestandCentralTrains
//TempCode RDH 27Mar98 			BFEventWestcraptrain
//TempCode RDH 27Mar98 			BFEventContrailFocus
//TempCode RDH 27Mar98 			BFEventEastCoastRaiders
//TempCode RDH 27Mar98 			BFEventLowSweep
//TempCode RDH 27Mar98 			break;
//TempCode RDH 27Mar98 		}
//TempCode RDH 27Mar98 		case	SPLITFORCE:
//TempCode RDH 27Mar98 		{
//TempCode RDH 27Mar98 			BFEventEndRunDecoy
//TempCode RDH 27Mar98 			BFEventSlightOfHand
//TempCode RDH 27Mar98 			BFEventWestandCentralTrains
//TempCode RDH 27Mar98 			BFEventContrailFocus
//TempCode RDH 27Mar98 			break;
//TempCode RDH 27Mar98 		}
//TempCode RDH 27Mar98 		case	ATTACKWEAKNESSES:
//TempCode RDH 27Mar98 		{
//TempCode RDH 27Mar98 			BFEventEndRunDecoy
//TempCode RDH 27Mar98 			BFEventInterceptEnemy
//TempCode RDH 27Mar98 			BFEventSlightOfHand
//TempCode RDH 27Mar98 			BFEventWestandCentralTrains
//TempCode RDH 27Mar98 			BFEventWestCrapTrains
//TempCode RDH 27Mar98 			BFEventAttackAtBingofuel.
//TempCode RDH 27Mar98 			BFEventContrailFocus
//TempCode RDH 27Mar98 			BFEventStaircase
//TempCode RDH 27Mar98 			BFEventJaws
//TempCode RDH 27Mar98 			BFEventPatrollingat3levels
//TempCode RDH 27Mar98 			break;
//TempCode RDH 27Mar98 		}
//TempCode RDH 27Mar98 		case	ATTACKANYTHING:
//TempCode RDH 27Mar98 		{
//TempCode RDH 27Mar98 			BFEventEndRunDecoy
//TempCode RDH 27Mar98 			BFEventInterceptEnemy
//TempCode RDH 27Mar98 			BFEventSlightOfHand
//TempCode RDH 27Mar98 			BFEventWestandCentralTrains
//TempCode RDH 27Mar98 			BFEventWestCrapTrains
//TempCode RDH 27Mar98 			BFEventContrailFocus
//TempCode RDH 27Mar98 			BFEventUppercutDecoy
//TempCode RDH 27Mar98 			BFEventStaircase
//TempCode RDH 27Mar98 			BFEventJaws
//TempCode RDH 27Mar98 			BFEventPatrollingat3levels
//TempCode RDH 27Mar98 			break;
//TempCode RDH 27Mar98 		}
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VisibleContrailsCheck
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::VisibleContrailsCheck()
{
//TempCode RDH 27Mar98 AirStruc* next eye from array
//TempCode RDH 27Mar98 if eye exists, is not dead, is a leader or is not information, is not damaged
//TempCode RDH 27Mar98 if  bomber
//TempCode RDH 27Mar98 {
//TempCode RDH 27Mar98 	AlertFighters(eye,trg,CONTRAILSMG);
//TempCode RDH 27Mar98 }else if not in combat or unfriendly == NULL
//TempCode RDH 27Mar98 {
//TempCode RDH 27Mar98 	set start point to inspect array
//TempCode RDH 27Mar98 	do
//TempCode RDH 27Mar98 	{
//TempCode RDH 27Mar98 		if  range > VISIBLERANGE  andVisibleContrails()
//TempCode RDH 27Mar98 			SpottedOldContrails(eye,trg);
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 	}while all aircraft not inspected
//TempCode RDH 27Mar98 }
//TempCode RDH 27Mar98 
}
void	ArtInt::VisibleAAACheck()
{
	AirStruc* eye=ACArray[ACArrayInd];
	if (eye && !eye->Status.deadtime && eye->waypoint)												//viewer alive
		if (eye->waypoint->wpname==WPNAME_Target || eye->waypoint->wpname==0)									//in patrol area
			if ((eye->duty&ACTIONCODE)!=DA_CAP)
				if (eye->movecode!=AUTO_BOMB)
					if (!eye->formpos || eye->uniqueID.count==eye->waypoint->skipunder)
					{
						ItemPtr	seltrg=NULL;
						if ((eye->duty&DUTYMASK)==DC_WW)
						{
							AaaMainList::AaaSubList* list=Three_Dee.livelist->aaalist;
							AaaMainList::AaaSubList* lstart=list;
							do{
								for (int i=0;i<AaaMainList::SUBLISTSIZE;i++)
								{
									ItemPtr trg=list->aaaitem[i];
									if (trg && trg->Status.size==ITEMSIZE && !trg->Status.deadtime)
									{
										Coords3D		weapoff;
										int				weapnum=0;
										UWord			mvel,mdelay,mburst;						//RDH 31Jul98

										WeapAnimData*	weapanim=SHAPE.GetWeaponLauncher(trg,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
										if (weapanim)
										{
											AaaParams*	aaaparams=&aaaguntypelist[weapanim->LauncherType-LT_MOVEGUN];
											if (aaaparams->guntype==AAA_ANTIAIRCRAFT && aaaparams->nat!=eye->nationality)
											{
												int range=eye->Distance3D(&trg->World);
												if (range<METRES15KM)
													if (range<(METRES2000 + eye->ai.combatskill*METRES350) || !Math_Lib.rnd(20-eye->ai.combatskill))
													{	//spotted a site!
														seltrg=trg;
														break;
													}
											}
										}
									}
								}
								list=list->next;
							}while (list!=lstart);
						}
						else
						if ((eye->duty&DUTYMASK)==DC_AR)
						{
							for (FormationItemPtr truck=*MobileItem::MobileList;truck;truck=*truck->nextmobile)
							{
								if (!truck->leader && truck->nationality!=eye->nationality && !truck->Status.deadtime)
								{
									int range=eye->Distance3D(&truck->World);
									if (range<METRES15KM)
									{
										UniqueIDBand b=Persons2::getbandfromUID(truck->uniqueID.count);
										if (b==RedTrainBAND || b==RedTruckBAND)
											if (range< (METRES2000 + eye->ai.combatskill*METRES350) || !Math_Lib.rnd(20-eye->ai.combatskill))
											{	//spotted a site!
												seltrg=truck;										
												break;
											}
									}
								}
							}
						}
						if (seltrg)	//ok... got a selected target! Now what?
						{
							AirStrucPtr sender,recipient;
							recipient=eye->PlayerInGroup();
//DEADCODE RDH 15/06/99 							if (!recipient)
//DEADCODE RDH 15/06/99 							{
//DEADCODE RDH 15/06/99 								sender=recipient=eye;
//DEADCODE RDH 15/06/99 							}
//DEADCODE RDH 15/06/99 							else
							if (!recipient)
								recipient=eye;
							else									  //JIM 31/08/99
							{
								if (GR_TruckMoveCode==GROUND_TOGLOBREF) //JIM 31/08/99
									OverLay.DecisionMessage(SecretMessages,0,Persons2::PlayerGhostAC,NULL,Persons2::PlayerGhostAC); //JIM 31/08/99
							}
							if (recipient==eye)
							{
								sender=recipient->FindBuddy();
								if (!sender)
									sender=recipient;
							}
							else
							{
								sender=eye;
							}
							if (seltrg->Status.size==ITEMSIZE)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_WWALLOCUS,MSG_MORETARGETS,sender,seltrg,recipient));
							else
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SEETARGET,MSG_MORETARGETS,sender,seltrg,recipient));
							for (AirStrucPtr fl=eye;fl;fl=fl->fly.nextflight)
								for (AirStrucPtr w=fl;w;w=w->Follower())
									if (w->uniqueID.count>=eye->waypoint->skipunder && w->uniqueID.count<=eye->waypoint->skipover) 
									{
										w->movecode=AUTO_BOMB;
										w->ai.ManStep=0;
										w->manoeuvretime=0;
										w->ai.unfriendly=seltrg;
									}
						}
					}
}

//All new:
////////////////////////////////////////////////////////////////////////
//
// Function:    SendMsgAndCall
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
inline const MESSAGE_STRUC& MESSAGE_STRUC::CheckCalleePlayer() const
{
	if (callee==Persons2::PlayerSeenAC)
		callee=Persons2::PlayerGhostAC;
	return *this;
}
inline const MESSAGE_STRUC& MESSAGE_STRUC::CheckCallerPlayer() const
{
	if (caller==Persons2::PlayerSeenAC)
		caller=Persons2::PlayerGhostAC;
	return *this;
}
inline const MESSAGE_STRUC& MESSAGE_STRUC::CheckTargetPlayer() const
{
	if (target==Persons2::PlayerSeenAC)
		target=Persons2::PlayerGhostAC;
	return *this;
}

bool	ArtInt::SendMsgAndCall(const MESSAGE_STRUC& msg,DecisionAI* processor) //JIM 22/01/99
{
//DeadCode DAW 26Mar99 	//if	autodecisions not enabled					//autodecisions does everything...
//DeadCode DAW 26Mar99 	//	and message recient is player interested		//other groups do own thing
//DeadCode DAW 26Mar99 	//	and	sender does not equal player [interested]	//myflight told myself to engage!
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 // COMMS: block messages to other players
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	if (_DPlay.Implemented || _Replay.Record)
//DeadCode DAW 26Mar99 	{
//DeadCode DAW 26Mar99 		UByte decision=0;		// 0-100 = 7 bits
//DeadCode DAW 26Mar99 		UByte option=0;			// 0-9	 = 4 bits
//DeadCode DAW 26Mar99 		UniqueID trg=UID_NULL;	// UID	 = 14 bits				  
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 		if (msg.target)
//DeadCode DAW 26Mar99 			trg=msg.target->uniqueID.count;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 		_DPlay.NewWingmanCommand(decision,option,trg);
//DeadCode DAW 26Mar99 	}
//DeadCode DAW 26Mar99 	else
//DeadCode DAW 26Mar99 	{
//DeadCode DAW 26Mar99 		if (processor.GetMsgOptions()==NULL || 0) //msg.callee.IsPiloted()
//DeadCode DAW 26Mar99 			return processor.AutoMsgDecision(*msg.callee,msg.target,*msg.caller,this);
//DeadCode DAW 26Mar99 		else
//DeadCode DAW 26Mar99 			msg.SetDecision(&processor);
//DeadCode DAW 26Mar99 	}
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 // in replay record still want to hear message, but as there is too much info for voices
//DeadCode DAW 26Mar99 // to store, must say message now and have results when packet processed.
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	if (!_DPlay.Implemented) // && !_Replay.Record)
//DeadCode DAW 26Mar99 		_Radio.TriggerMsg(msg);
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	return true;
	//if	autodecisions not enabled					//autodecisions does everything...
	//	and message recient is player interested		//other groups do own thing
	//	and	sender does not equal player [interested]	//myflight told myself to engage!
	msg.CheckCalleePlayer().CheckCallerPlayer().CheckTargetPlayer();

	if (blocking)
	{
		assert (blocking==DoNothing);
		blocking=processor;
		return true;
	}
	else if (	processor->GetMsgOptions()==NULL
			||	Save_Data.gamedifficulty[GD_AUTOVECTORING]			  //RDH 18/04/99
			)
	{
			_Radio.TriggerMsg(msg);
			return processor->AutoMsgDecision(*msg.callee,msg.target,*msg.caller,this);
	}
	else if (!msg.callee->AcIsPlayer())
	{//automatic decision making
		_Radio.TriggerMsg(msg);

// want to block messages to remote players

		if (msg.callee && !msg.callee->uniqueID.commsmove)				//AMM 20Apr99
			return processor->AutoMsgDecision(*msg.callee,msg.target,*msg.caller,this);
		else
			return true;
	}
	else
	{//decision required from user
		OverLay.CancelAccel();
		_Radio.TriggerMsg(msg.SetDecision(processor));
		return true;
	}
}

bool	DecisionAI::UserMsgDecision(AirStrucPtr callee,ItemBasePtr trg,			  //JIM 22/01/99
		AirStrucPtr caller,ArtInt* artint,MESSAGE_STRUC* PriorityMessage)
{
	if (caller->ai.radiosilent)
	{
		AirStrucPtr respondent=caller->fly.leadflight;
		if (!respondent)
			respondent=caller->FindBuddy();
		if (Math_Lib.rnd(8)==0)
			caller->ai.radiosilent=FALSE;							  //JIM 11/06/99
		if (respondent)
		{
			if (Math_Lib.rnd(8)==0)
				respondent->ai.radiosilent=FALSE;					  //JIM 11/06/99
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SILENCE, MSG_SILENCE, respondent, NULL, caller));

		}


	}
	return AutoMsgDecision(callee,trg,caller,artint,PriorityMessage);
}


PhraseTables DecisionAI::GetDefaultPhrase(AirStrucPtr callee,ItemBasePtr trg)
{
	Art_Int.blocking=DoNothing;
	OptionRef* msgopts=GetMsgOptions();
	assert(msgopts);

	bool tookaction=AutoMsgDecision(callee,trg,callee,&Art_Int);
	DecisionAI* returnedscript=Art_Int.blocking;
	Art_Int.blocking=NULL;
	if (tookaction)
	{
		assert(returnedscript!=DoNothing && returnedscript!=NULL);
		for (;msgopts->optionmsg!=PHRASE_PARTS_S;msgopts++)
			if (*msgopts->airesult == returnedscript)
				return msgopts->optionmsg;
		if (*msgopts->airesult == returnedscript)					  //JIM 21/06/99
			return msgopts->optionmsg;
		msgopts++;
		for (;msgopts->optionmsg!=PHRASE_PARTS_S;msgopts++)
			if (*msgopts->airesult == returnedscript)
				return msgopts->optionmsg;

		assert(!"Default action taken does not match any user action")
		return	PHRASE_CONTINUE;
	}
	else
	{
		assert(returnedscript==DoNothing || returnedscript==NULL);
		for (;msgopts->optionmsg!=PHRASE_PARTS_S;msgopts++)
			if (!msgopts->airesult || msgopts->airesult==&DoNothing)
				return msgopts->optionmsg;
		return	PHRASE_CONTINUE;	//no user phrase to continue...
	}



}

////////////////////////////////////////////////////////////////////////
//
// Function:    AcIsPlayer
// Date:        21/02/99
// Author:      JIM
//
// Description: A variety of routines to find message recipients
//
////////////////////////////////////////////////////////////////////////
AirStrucPtr			AirStruc::AcIsPlayer()
{
	if (this==NULL)	return this;
	if (this==Persons2::PlayerGhostAC)	return this;
	if (this==Persons2::PlayerSeenAC)	return this;
	//for comms to pick up other remote player aircraft:
	//I don't think we want this!
	//if (this->uniqueID.commsmove)		return	true;
	return NULL;
}
AirStrucPtr		AirStruc::InPlayersElement()
{
	if (!this)	
		return this;
	if (AcIsPlayer())				
		return this;
	return	FindBuddy()->AcIsPlayer();
}
AirStrucPtr		AirStruc::FindBuddy()
{
	if (!this)	
		return this;
	if (leader)
		return Leader();
	if (follower)
		return	Follower();
	if (fly.nextflight)
		return fly.nextflight;
	if (fly.leadflight)
		return fly.leadflight;
	return NULL;
}
AirStrucPtr		AirStruc::PlayerInFlight()
{
	AirStrucPtr	rv;
	rv=InPlayersElement();
	if (rv)
		return	rv;
	switch (position())
	{
	case 0:
		if (fly.nextflight)
			rv=fly.nextflight->InPlayersElement();
		break;
	case 1:
		if (leader && !follower && Leader()->fly.nextflight)
			rv=Leader()->fly.nextflight->InPlayersElement();
		break;
	case 2:
		if (!leader)		
			rv=(fly.leadelt()->InPlayersElement());
		break;
	case 3:
		if (leader && leader->follower==this)
		rv=(Leader()->fly.leadelt()->InPlayersElement());
	}
	return rv;
}

AirStrucPtr		AirStruc::PlayerInGroup()
{
	AirStrucPtr	leadac=this;
	if (leader)
		leadac=Leader();
	if (leadac->formpos)			//RDH 24/05/99 edit on Craig's machine as well
		leadac=leadac->fly.leadflight;
	AirStrucPtr rv;
	for(;leadac;leadac=leadac->fly.nextflight)
	{
		rv=leadac->InPlayersElement();
		if (rv)
			return rv;
	}
	return	NULL;
}
AirStrucPtr		AirStruc::FindAirEscortLeader()
{
	AcArrayItterator search;
	while (search.Next())
		if (search)
		{
			if (!search->formpos)
				if (search->fly.leadflight==this)
					if (!search->Status.deadtime)
						if (search->duty==DUTYESCORT)
							return search;
		}
	return search;
}
AirStrucPtr		AirStruc::AcCloseAttackingOneOfGroup(bool& unffound)
{
	SLong range = COMBATRANGE;
	AirStruc*	possiblevictim = NULL;
	AirStruc*	victim = NULL;
	AirStruc*	lead = FindGroupLeader();
	AirStruc*	eye;
	while (lead)
	{
		eye = lead;
		while (eye)
		{
			if (eye->ai.attacker)	
			{
				Art_Int.InterceptRangeFromTo(eye, eye->ai.attacker);
				if (		(Range < COMBATRANGE)	
						&&	(Range < range)
					)
				{
					 unffound = true;
					 possiblevictim = eye;
					if (		(eye != this)
							&&	(Art_Int.TargetFacingCaller(eye, eye->ai.attacker, ANGLES_40Deg))
							&&	(Art_Int.TargetOnCallerTail(eye, eye->ai.attacker, ANGLES_40Deg))
							&&	(Art_Int.AircraftAreClose(eye, this))
						)
					{
						 victim = eye;
	 					 range = Range;
					}
				}
			}
			eye=(AirStruc*)eye->follower;
		}
		lead=lead->fly.nextflight;
	}
	if (unffound)
	{
		if (victim)
			possiblevictim = victim;		//override possiblevictim  with victim if there is one
	}


	return possiblevictim;
}
AirStrucPtr		AirStruc::RemoveElement()
{//elements in MiG are considered to be flights in our system

	AirStruc*	leadf;
//DeadCode DAW 21Jul99 	if (fly.leadflight)
	if (formpos)												  //JIM 21/07/99
		leadf = fly.leadflight;
	else
		leadf = NULL;

	AirStruc*	nextf = this->fly.nextflight;

	AirStruc*	prevf = leadf;

	if (prevf)
	while (prevf->fly.nextflight!=this)
		prevf=prevf->fly.nextflight;


	
	if (prevf)
		prevf->fly.nextflight = nextf;

	if ((nextf)	&&	(position() == 0))
		if (nextf->position())
			nextf->formpos = formpos;
		else if (formpos == 0)
		{
			nextf->formpos = formpos;

			//following flights
			for (AirStruc* nf= nextf;nf;nf= nf->fly.nextflight) //everybody's lead flight is new leader
				for (AirStruc* wing= nf;wing;wing= wing->Follower()) //everybody else's lead flight is new leader
				{//following leaders and their wingmen
					wing->fly.leadflight = nextf;

				}
			nextf->fly.leadflight = leadf;		//overwrite using escortee for the new flight leader

		}

	

//removed element
	fly.leadflight = NULL;
	fly.nextflight = NULL;

	formpos = FormationIndexMIN;
		

	return NULL;
}
AirStrucPtr		AirStruc::FindABuddyWithPlayerGivenPriority()
{
	AirStruc*	callee = FindBuddy();
	if	(		(PlayerInGroup())
			&&	(!AcIsPlayer())
		)			
			callee  = Manual_Pilot.ControlledAC2;

	return callee;
}
AirStrucPtr		AirStruc::FindABuddyNotPlayer()
{
		if (!this)	
		return this;
	if (leader)
		if (!Leader()->AcIsPlayer())
			return Leader();
	if (follower)
		if (!Follower()->AcIsPlayer())
		return	Follower();
	if (fly.nextflight)
		if (!fly.nextflight->AcIsPlayer())
		return fly.nextflight;
	if (fly.leadflight)
		if (!fly.leadflight->AcIsPlayer())
		return fly.leadflight;
	return NULL;

}
AirStrucPtr		AirStruc::FindAcInGroup()
{
	AirStruc*	buddy = FindBuddy();
	if (!buddy)
	{
		if (leader)//RJS 01Apr99
		{
			if (((AirStruc*) leader)->fly.nextflight)
				buddy = ((AirStruc*) leader)->fly.nextflight;
			else if (((AirStruc*) leader)->fly.leadflight)
				buddy = ((AirStruc*) leader)->fly.leadflight;
		}
	}
	return (buddy);
}
//DEADCODE RDH 05/07/99 AirStrucPtr		AirStruc::FindBandit(int& count)
//DEADCODE RDH 05/07/99 {//find bandit in visible range
//DEADCODE RDH 05/07/99 	AcArrayItterator bogey;
//DEADCODE RDH 05/07/99 	AirStruc*	bandit = NULL;
//DEADCODE RDH 05/07/99 	SLong range =  VISIBLERANGE;
//DEADCODE RDH 05/07/99 	count = 0;
//DEADCODE RDH 05/07/99 	while (bogey.Next())
//DEADCODE RDH 05/07/99 		if (bogey)
//DEADCODE RDH 05/07/99 		{
//DEADCODE RDH 05/07/99 			if (bogey->nationality != nationality)
//DEADCODE RDH 05/07/99 			{
//DEADCODE RDH 05/07/99 				if (	(!bogey->leader)
//DEADCODE RDH 05/07/99 					||	(!bogey->information)
//DEADCODE RDH 05/07/99 					)
//DEADCODE RDH 05/07/99 				{
//DEADCODE RDH 05/07/99 					if  (		(!bogey->leader)
//DEADCODE RDH 05/07/99 							&&	(bogey->movecode != AUTO_NOPPILOT)						
//DEADCODE RDH 05/07/99 						)
//DEADCODE RDH 05/07/99 						//count all leaders that active
//DEADCODE RDH 05/07/99 						count++;
//DEADCODE RDH 05/07/99 					Art_Int.InterceptRangeFromTo(this, bogey);
//DEADCODE RDH 05/07/99 					if (		(Range < VISIBLERANGE)
//DEADCODE RDH 05/07/99 							&&	(Range < range)
//DEADCODE RDH 05/07/99 							&&	(!Status.deadtime) 
//DEADCODE RDH 05/07/99 						)
//DEADCODE RDH 05/07/99 					{
//DEADCODE RDH 05/07/99 						range = Range;
//DEADCODE RDH 05/07/99 						bandit = bogey;
//DEADCODE RDH 05/07/99 					}
//DEADCODE RDH 05/07/99 				}
//DEADCODE RDH 05/07/99 			}
//DEADCODE RDH 05/07/99 		}
//DEADCODE RDH 05/07/99 	Range = range;		//range of bandit   
//DEADCODE RDH 05/07/99 	return (bandit);
//DEADCODE RDH 05/07/99 }
AirStrucPtr		AirStruc::FindBandit(int& count)
{//find bandit in visible range, return count of leader. THis may be 0 even if bandit found
	AcArrayItterator bogey;
	AirStruc*	bandit = NULL;
	SLong range =  VISIBLERANGE;
	count = 0;
	while (bogey.Next())
		if (bogey)
		{
			if  (		(		(!bogey->leader)
							||	(!bogey->information)
						)
						&&	(bogey->movecode != AUTO_NOPPILOT)
						&&	(bogey->nationality != nationality)
						&&	(!Status.deadtime)
				)	
			{
				Art_Int.InterceptRangeFromTo(this, bogey);
				if 	(Range < VISIBLERANGE)
				{
					if 	(!bogey->leader)
						//count all leaders that active
						count++;
					if (Range < range)
					{
						range = Range;
						bandit = bogey;
					}
				}
			}
		}
	Range = range;		//range of bandit   
	return (bandit);
}





//DEADCODE RDH 05/07/99 AirStrucPtr		AirStruc::FindAnyBandit(SLong& range)
//DEADCODE RDH 05/07/99 {
//DEADCODE RDH 05/07/99 	AcArrayItterator bogey;
//DEADCODE RDH 05/07/99 	AirStruc*	bandit = NULL;
//DEADCODE RDH 05/07/99 	range =  MILES2000;
//DEADCODE RDH 05/07/99 
//DEADCODE RDH 05/07/99 	while (bogey.Next())
//DEADCODE RDH 05/07/99 		if (bogey)
//DEADCODE RDH 05/07/99 		{
//DEADCODE RDH 05/07/99 			if (bogey->nationality != nationality)
//DEADCODE RDH 05/07/99 			{
//DEADCODE RDH 05/07/99 				if (	(!bogey->leader)
//DEADCODE RDH 05/07/99 					||	(!bogey->information)
//DEADCODE RDH 05/07/99 					)
//DEADCODE RDH 05/07/99 				{
//DEADCODE RDH 05/07/99 					
//DEADCODE RDH 05/07/99 					Art_Int.InterceptRangeFromTo(this, bogey);
//DEADCODE RDH 05/07/99 					if (		(Range < MILES2000)
//DEADCODE RDH 05/07/99 							&&	(Range < range)
//DEADCODE RDH 05/07/99 							&&	(!Status.deadtime) 
//DEADCODE RDH 05/07/99 						)
//DEADCODE RDH 05/07/99 					{
//DEADCODE RDH 05/07/99 						range = Range;
//DEADCODE RDH 05/07/99 						bandit = bogey;
//DEADCODE RDH 05/07/99 					}
//DEADCODE RDH 05/07/99 				}
//DEADCODE RDH 05/07/99 			}
//DEADCODE RDH 05/07/99 		}
//DEADCODE RDH 05/07/99 	return (bandit);
//DEADCODE RDH 05/07/99 }
AirStrucPtr		AirStruc::FindAnyBandit(SLong& range, int& count)
{
	AcArrayItterator bogey;
	AirStruc*	bandit = NULL;
	range =  MILES2000;

	while (bogey.Next())
	if (bogey)
		{
			if  (		(		(!bogey->leader)
							||	(!bogey->information)
						)
						&&	(bogey->movecode != AUTO_NOPPILOT)
						&&	(bogey->nationality != nationality)
						&&	(!Status.deadtime)
				)	
			{
				Art_Int.InterceptRangeFromTo(this, bogey);
				if 	(Range < MILES2000)
				{
					if 	(!bogey->leader)
						//count all leaders that active
						count++;
					if (Range < range)
					{
						range = Range;
						bandit = bogey;
					}
				}
			}
		}
	return (bandit);





}
AirStrucPtr		AirStruc::FindBanditOnTail()
{
	AcArrayItterator bogey;
	AirStruc*	bandit = NULL;
	
	while (bogey.Next())
		if (bogey)
		{
			if (bogey->nationality != nationality)
			{
				if (bogey->movecode == AUTO_COMBAT)
				{
					Art_Int.InterceptRangeFromTo(this, bogey);
					if (		(Range < ENGAGERANGE)
							&&	(Art_Int.TargetOnCallerTail(this, bogey, ANGLES_30Deg))
						)
					{
		
						bandit = bogey;
					}
				}
			}
		}
	return (bandit);
}
bool AirStruc::InSameWave(AirStruc* trg)
{
	AirStruc* caller = FindGroupLeader();
	trg = trg->FindGroupLeader();
	if	(	(		(trg)
				&&	(trg->fly.leadflight == caller)
			)
			||
			(		(caller)
				&&	(caller->fly.leadflight == trg)
			)
		)
		return (true);
	else
		return (false);
}
void	ArtInt::AllChangeMovecode(AirStrucPtr leadac, AirStrucPtr trg, AutoMoveCodeTypeSelect movecode)
{
	AirStrucPtr	w=leadac;
	while(w)
	{
		AirStrucPtr	f=w;
		while (f)
		{
			f->ai.unfriendly = trg;
			f->movecode = movecode;
			f=*f->follower;
		}
		w=w->fly.nextflight;
	}
}
