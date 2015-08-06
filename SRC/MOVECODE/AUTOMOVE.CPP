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

////////////////////////////////////////////////////////////////////// //DAW 04/06/99
//
// Module:      Automove.cpp
//
// Created:     22/03/99 by DAW
//
// Description: 			  TowerMsg
//
//////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
//Filename       automove.cpp
//System         
//Author         R. Hyde 
//Date           Tue 28 Nov 1995
//Description    
//------------------------------------------------------------------------------
//THe aoa calc is only good for camels###

#define F_GRAFIX												//RDH 24Sep96
	 
#include	"dosdefs.h"
#include	"worldinc.h"

#include	"planetyp.h"
#include	"myangles.h"
#include	"enumbits.m"
#include	"flymodel.h"
//MATHABLE	(ANGLES);
BITABLE		(Bool);
//DELTABLE	(ANGLES,int);
#include	"mymath.h"
#include	"miles.h"
#include	"missman2.h"										//JIM 22Aug96
#include	"ranges.h"											//RDH 28Feb96
#include	"speed.h"											//RDH 28Feb96
#include	"mytime.h"											//PD 15Mar96
#include	"3dcom.h"											//PD 19Apr96
#include	"landscap.h"									//PD 15Mar96
#include	"viewsel.h"											//RDH 25Jun96
#include	"ai.h"
#include	"flyinit.h"
#include	"savegame.h"
#include	"collided.h"										//RDH 12Sep96
#include	"transite.h"										//RDH 12Sep96
#include	"contlist.h"										//RDH 12Sep96
#include	"persons2.h"										//RDH 12Sep96
#include	"winmove.h"											//ARM 06Dec96
#include	"monotxt.h"											//ARM 08Dec96
#include	"modvec.h"
#include	"model.h"											//RJS 24Feb98
#include	"globrefs.h"
#include	"areatype.h"										//RJS 24Aug98
#include	"3dcode.h"											//RJS 24Aug98
#include	"SHAPES.H"
#include	"movement.h"
#include	"replay.h"
#include	"node.h"
#include	"overlay.h"
#include	"rchatter.h"
#include	"..\mfc\resource.h"
//DeadCode PD 15Mar96 int	frametime = 10;
//extern	ULong	GR_Quit3DNow;
extern DPlay _DPlay;

#define TRACEMOVE

//DeadCode RDH 28Feb96 SLong const 	FIVEMILESIN_CMS = 1200000;
//DeadCode RDH 14Mar96 ANGLES const 	MAXROLL = ANGLES_70Deg;

//check finddespos
//rollrate modifier
//SetManoeuvreTime

//autocalcpitch used to use cpitch
//GROUNDLEVEL defined in flymodel.cpp


//autoavoid code
//wpaction code


//RequiredDrollData dw 0, 6		;;For given input angle (lhs)
//                  dw ANGLES_1Deg, 5		;;roll will be the power 
//                  dw ANGLES_2Deg, 4		;;of 2 on rhs
//                  dw ANGLES_3Deg, 3
//                  dw ANGLES_10Deg, 2
//                  dw ANGLES_180Deg, 0				;;JIM 16Aug93
//
//;following is needed for interploate				;;RDH 02Apr94
//		  dw ANGLES_fifthDeg, ANGLES_0Deg		;;RDH 02Apr94
//;this table was not symmetric					;;RDH 02Apr94
//RequiredBankData  dw ANGLES_fifthDeg, ANGLES_0Deg
//                  dw ANGLES_halfDeg, ANGLES_3Deg
//                  dw ANGLES_1Deg, ANGLES_4Deg
//                  dw ANGLES_2Deg, ANGLES_5Deg
//                  dw ANGLES_3Deg, ANGLES_7Deg
//                  dw ANGLES_4Deg, ANGLES_9Deg			
//                  dw ANGLES_5Deg, ANGLES_11Deg
//                  dw ANGLES_6Deg, ANGLES_16Deg			
//                  dw ANGLES_10Deg, ANGLES_45Deg			
//                  dw ANGLES_22Deg, ANGLES_60Deg
//                  dw ANGLES_180Deg, MAXROLL 

//DeadCode RDH 18Dec95 struct RequiredBankDataElement
//DeadCode RDH 18Dec95 	{
//DeadCode RDH 18Dec95 		ANGLES hdg; ANGLES roll;
//DeadCode RDH 18Dec95 	};

UWord AirStruc::airdensityratiosquareroot[] =
			{
				65535,
				64383,
				63357,
				62280,
				61387,
				60377,
				59282,
				58236,
				57172,
				56233,
				55203,
				54230,
				53239,
				52230,
				51200,
				50231,
				49243,
				48149,
				46943,
				45705,
				44525,
				43218,
				42162,
				41080
	};


static RequiredBankDataElement 	RequiredBankData[] =
			{
//DeadCode CSB 23/03/99					{ANGLES_FifthDeg, ANGLES_0Deg},
//DeadCode CSB 23/03/99					{ANGLES_HalfDeg, ANGLES_3Deg},
//DeadCode CSB 23/03/99					{ANGLES_1Deg, ANGLES_4Deg},
//DeadCode CSB 23/03/99					{ANGLES_2Deg, ANGLES_5Deg},
//DeadCode CSB 23/03/99					{ANGLES_3Deg, ANGLES_7Deg},
//DeadCode CSB 23/03/99					{ANGLES_4Deg, ANGLES_9Deg},
//DeadCode CSB 23/03/99					{ANGLES_5Deg, ANGLES_11Deg},
//DeadCode CSB 23/03/99					{ANGLES_6Deg, ANGLES_16Deg},
//DeadCode CSB 23/03/99					{ANGLES_10Deg, ANGLES_45Deg},
//DeadCode CSB 23/03/99					{ANGLES_22Deg, ANGLES_60Deg},
//DeadCode CSB 23/03/99					{ANGLES_180BareDeg, MAXROLL}
				{ANGLES_0Deg, ANGLES_0Deg},
				{ANGLES_FifthDeg, ANGLES_10Deg},
				{ANGLES_2Deg, ANGLES_20Deg},
				{ANGLES_10Deg, ANGLES_45Deg},
				{ANGLES_45Deg, MAXROLL},
				{ANGLES_180BareDeg, MAXROLL}
			};

UWord AirStruc::vel_to_aoa[] =

			{
				ANGLES_40Deg,
				ANGLES_34Deg,
//DeadCode RDH 06Jun96 				ANGLES_27Deg,
				ANGLES_25Deg,
				ANGLES_18Deg,
				ANGLES_10Deg,
				ANGLES_6Deg,
				ANGLES_4Deg,
				ANGLES_3Deg,
				ANGLES_2_5Deg,
				ANGLES_2Deg,
				ANGLES_1_67Deg,
				ANGLES_1_33Deg,
				ANGLES_1Deg,
				ANGLES_0Deg,
				ANGLES_0Deg,
				ANGLES_0Deg,
				ANGLES_0Deg,
				ANGLES_0Deg,
				ANGLES_0Deg

			};
SLong const 	MAXALTITUDE_CM 	=	2200000;
SLong const 	WORD_FRACT   	=	65536;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFollower_xyz
//Author		R. Hyde 
//Date			Mon 26 Feb 1996
//
//Description	Fills despos with desired location
//				THIS MUST BE BASED ON WING LEADER, NOT SQUAD LEADER//JIM 02Aug96
//				Otherwise, in 2 wings that are trying to come 
//				together the followers will stay loose.
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	//Want no effect to F86 which has 52 in this shape size field.
	//These sizes are too big for bigger bombers. Want to keep F86 the same
	//Was: 32K*52/ShpSize	- where shpsize for f86 is 52
	//The smaller the value, the wider spaced
	//Putting a minimum value of 32K/5 means a max spread of *5 ==> 250ft becomes 1200ft
#define SIZEDIV32K(who)	((ANGLES_FRACT/5)+(ANGLES_FRACT*4*52/5)/SHAPESTUFF.GetShapePtr( who )->Size)

void	formationitem::GetFollower_xyz (FormationTypeIndex	formationtype, FormationItemPtr leader)
{
	int acsizediv= SIZEDIV32K(shape);
	ANGLES	brg;
	SWord	sinbearing,cosbearing;
	SLong	range;
//DeadCode RDH 17Jun96 	SWord	formationtype;
	SWord	formationpos;

//DeadCode RDH 17Jun96 	formationtype = formation; 
	formationpos = (formpos&InWingMAX) - 1; 

	if(leader == NULL)
	{
		leader=*this->leader;
		if (!leader)
			leader=AirStrucPtr(*this)->fly.leadelt();
	}

//DEADCODE AMM 18/05/99 	if (!leader)
//DEADCODE AMM 18/05/99 	{
//DEADCODE AMM 18/05/99 		leader=AirStrucPtr(*this)->fly.leadelt();
//DEADCODE AMM 18/05/99 	}
	
	brg = leader->hdg + Aircraft_Formations [formationtype]->wingpos [formationpos].bearing;
	range = Aircraft_Formations [formationtype]->wingpos [formationpos].range;

	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);

	despos = leader->World; 									//JIM 02Aug96
	{
//DeadCode DAW 09Mar99 		despos.X += sinbearing	* range / ANGLES_FRACT;
//DeadCode DAW 09Mar99 		despos.Y += Aircraft_Formations [formationtype]->wingpos [formationpos].delta_alt;	
//DeadCode DAW 09Mar99 		despos.Z += cosbearing	* range / ANGLES_FRACT;

		despos.X += MULDIVSIN (sinbearing,range,acsizediv);		//RDH 14Dec96
		despos.Z += MULDIVSIN (cosbearing,range,acsizediv);		//RDH 14Dec96

		despos.Y += Aircraft_Formations [formationtype]->wingpos [formationpos].delta_alt;
	}


//DeadCode RDH 21May99 	if(range == 0)	//CSB 14/05/99	
//DeadCode RDH 21May99 		int Breakpoint = 1;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFlightLeader_xyz
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
void AirStruc::GetFlightLeader_xyz (SquadronTypeIndex	formationtype)

{
	//Want no effect to F86 which has 52 in this field.
	int acsizediv= SIZEDIV32K(fly.leadflight->shape);
	ANGLES	brg;
	SWord	sinbearing,cosbearing;
	SLong	range;
//DeadCode RDH 17Jun96 	SWord	formationtype;
	SWord	formationpos;

//DeadCode RDH 17Jun96 	formationtype = 0; 
	formationpos = (fly.originalformpos&InFormMAX);
//DeadCode RDH 13May96 	formationpos = (formpos&InWingMAX); 
//need to add one to bypass escortee data						//RDH 05Aug96
//DeadCode RDH 05Aug96 	formationpos = (formationpos) - 1; 

	brg = fly.leadflight->hdg + Squadron_Formations [formationtype]->wingpos [formationpos].bearing;
	range = Squadron_Formations [formationtype]->wingpos [formationpos].range;
	//time for a cludge... WW escort is closer!
	if (duty!=DUTYESCORT)											  //JIM 21/04/99
		acsizediv+=acsizediv>>1;


	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);

	despos = fly.leadflight->World; 							//JIM 02Aug96
//DeadCode RDH 14Dec96 	despos.X += sinbearing	* range / ANGLES_FRACT;
//DeadCode RDH 14Dec96 	despos.Z += cosbearing	* range / ANGLES_FRACT;
	despos.X += MULDIVSIN (sinbearing,range,acsizediv);		//RDH 14Dec96
	despos.Z += MULDIVSIN (cosbearing,range,acsizediv);		//RDH 14Dec96

	if (fly.leadflight->shape!=shape && 
			despos.Y <  (MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_2000))
		despos.Y =  MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_1000;		 //DAW 05/05/99
//DEADCODE DAW 05/05/99 		despos.Y=METRES10KM;										  //DAW 05/05/99
	else
		despos.Y+=Squadron_Formations [formationtype]->wingpos [formationpos].delta_alt;	

//DeadCode RDH 21May99 	if(range == 0)
//DeadCode RDH 21May99 		int Breakpoint = 2;	//CSB 14/05/99	
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveWithLeader
//Author		R. Hyde 
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
COORDS3D* AirStruc::PositionWRTLeader (AirStrucPtr lf)

{
//DeadCode JIM 02Aug96 	assert (formpos != 0 && "Moving leader wrt leader!");
 	SLong	x,y,z;
//DeadCode JIM 02Aug96 	despos = fly.leadflight->World; 


	if (formpos==0)
	{
		assert	(fly.leadflight && "Moving main leader wrt self!");
		GetFlightLeader_xyz ((SquadronTypeIndex) (FormationTypeIndex)formation);
//DeadCode JIM 19Feb99 		despos = fly.leadflight->World;
//DeadCode JIM 19Feb99 		despos.Y +=2000;	//20m
	}
	else
	if (formpos&InWingMAX)	
	{	
		GetFollower_xyz ( formation, lf);
//DeadCode RDH 09May96 		GetFlightLeader_xyz ();
	}
	else
	if (formpos&InFormMAX)	
	{
//DeadCode RDH 09May96 		GetFollower_xyz ();
//DeadCode RDH 18Aug96 		GetFlightLeader_xyz (SQUAD_STACKEDV);
		GetFlightLeader_xyz ((SquadronTypeIndex) (FormationTypeIndex)formation);
	}
	return (&despos);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PositionTakeOffWRTLeader
//Author		R. Hyde 
//Date			Mon 17 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
COORDS3D* AirStruc::PositionTakeOffWRTLeader ()
{
//DeadCode JIM 02Aug96 	assert (formpos != 0 && "Moving leader wrt leader!");
 	SLong	x,y,z;
//DeadCode JIM 02Aug96 	despos = fly.leadflight->World;


	if (formpos==0)
	{
		assert	(fly.leadflight && "Moving main leader wrt leader!");
		despos = fly.leadflight->World;
		despos.X +=1000;	//10m
	}
	else
	if (formpos&InWingMAX)	
	{	
		GetFollower_xyz (SQUAD_TAKEOFF);
	}
	else
	if (formpos&InFormMAX)	
	{
		GetFlightLeader_xyz (SquadronTypeIndex(SQUAD_TAKEOFF));
	}
	return (&despos);	

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyLeaderSub
//Author		R. Hyde 
//Date			Mon 17 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::CopyLeaderSub (AirStrucPtr lf)									//RDH 11Jul96
{
//DeadCode RDH 24Sep96 	AirStrucPtr lf=*leader;
//DeadCode RDH 24Sep96 	if (lf==NULL)
//DeadCode RDH 24Sep96 		lf=fly.leadflight;

	assert(lf&&"No leader in copy");
	pitch 	= lf->pitch;
	hdg 	= lf->hdg;
	roll 	= lf->roll;
	fly.cpitch 	= lf->fly.cpitch;	
//	fly.aoa 	= lf->fly.aoa;		

	velx =lf->velx;						
	vely =lf->vely;						
	velz =lf->velz;						
	velhori =lf->velhori;						
	vel 	=lf->vel;

//DeadCode RDH 02Jul96 	fly.anim_rudder = fly.leadflight->fly.anim_rudder;
//DeadCode RDH 02Jul96 	fly.anim_aileron = fly.leadflight->fly.anim_aileron;
//DeadCode RDH 02Jul96 	fly.anim_elevator = fly.leadflight->fly.anim_elevator;
	if((this != Persons2::PlayerSeenAC) && (this != Persons2::PlayerGhostAC))
	{
		fly.rudder = lf->fly.rudder;
		fly.aileron = lf->fly.aileron;
		fly.elevator = lf->fly.elevator;
	}

	if (roll==ANGLES_0Deg)										//RDH 11Jul96
		return TRUE;											//RDH 11Jul96
	else														//RDH 11Jul96
		return FALSE;											//RDH 11Jul96
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyLeader
//Author		R. Hyde 
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::CopyLeader (AirStrucPtr lf)

{
//DeadCode RDH 17Jun96 	pitch 	= fly.leadflight->pitch;
//DeadCode RDH 17Jun96 	hdg 	= fly.leadflight->hdg;
//DeadCode RDH 17Jun96 	roll 	= fly.leadflight->roll;
//DeadCode RDH 17Jun96 	fly.cpitch 	= fly.leadflight->fly.cpitch;	
//DeadCode RDH 17Jun96 	fly.aoa 	= fly.leadflight->fly.aoa;		
//DeadCode RDH 17Jun96 
//DeadCode RDH 17Jun96 	velx =fly.leadflight->velx;						
//DeadCode RDH 17Jun96 	vely =fly.leadflight->vely;						
//DeadCode RDH 17Jun96 	velz =fly.leadflight->velz;						
//DeadCode RDH 17Jun96 	velhori =fly.leadflight->velhori;						
//DeadCode RDH 17Jun96 	vel 	=fly.leadflight->vel;
//DeadCode RDH 17Jun96 
	if (CopyLeaderSub (lf))		//if leader horizontal			//RDH 11Jul96
		NewPosition();			//then even faster!				//RDH 11Jul96
	else														//RDH 11Jul96
	{															//RDH 11Jul96
	 	World = *PositionWRTLeader (lf);						//RDH 01Jun99
		uniqueID.changed = TRUE;								//RDH 11Jul96
	}															//RDH 11Jul96
//DeadCode RDH 17Jun96 
//DeadCode RDH 17Jun96 	fly.anim_rudder = fly.leadflight->fly.anim_rudder;
//DeadCode RDH 17Jun96 	fly.anim_aileron = fly.leadflight->fly.anim_aileron;
//DeadCode RDH 17Jun96 	fly.anim_elevator = fly.leadflight->fly.anim_elevator;
//DeadCode RDH 17Jun96 	fly.rudder = fly.leadflight->fly.rudder;
//DeadCode RDH 17Jun96 	fly.aileron = fly.leadflight->fly.aileron;
//DeadCode RDH 17Jun96 	fly.elevator = fly.leadflight->fly.elevator;
		SetFlightParams ();
	//temp fix...												//JIM 12Jul96
	uniqueID.changed = TRUE;									//JIM 12Jul96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoToGrndPitchRoll
//Author		Robert Slater
//Date			Thu 3 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoToGrndPitchRoll(ANGLES grndroll,ANGLES grndpitch)
{
	if (((UWord) fly.cpitch) > ANGLES_180Deg)
		fly.cpitch = grndpitch;

	if (((UWord) pitch) > ANGLES_180Deg)
	{
		pitch = grndpitch;
	}
	else
	{
		if (((UWord) pitch) > (classtype->deckangle + grndpitch))
			pitch = classtype->deckangle+ grndpitch;
		else
			pitch = grndpitch;
	}

	if ((roll- grndroll) > 0)
		roll -= (Angles)Timer_Code.FRAMETIME;
	else
		roll += (Angles)Timer_Code.FRAMETIME;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		void
//Author		R. Hyde 
//Date			Tue 10 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoDeathSequence()
{
	AircraftAnimData*	adptr = (AircraftAnimData *)Anim;

	PitchIntercept = ANGLES_300Deg;
	SWord DesRoll  = ANGLES_45Deg;
	for(;;)
	{

		if( (adptr->LEFTWINGIN > BS_DAMLV2) && (adptr->RIGHTWINGIN > BS_DAMLV2) && (adptr->TAIL > BS_DAMLV2) )
		{	
			PitchIntercept = ANGLES_270Deg;
			DesRoll = ANGLES_80Deg;
			if(roll < ANGLES_0Deg) DesRoll = -DesRoll;
			break;
		}

		if( (adptr->LEFTWINGIN > BS_DAMLV2) && (adptr->RIGHTWINGIN > BS_DAMLV2) )
		{
			PitchIntercept = ANGLES_285Deg;
			DesRoll = ANGLES_85Deg;
			if(roll < ANGLES_0Deg) DesRoll = -DesRoll;
			break;
		}
		
		if( (adptr->LEFTWINGIN > BS_DAMLV2) && (adptr->RIGHTWINGIN < BS_DAMLV2) )
		{
			PitchIntercept = ANGLES_300Deg;
			DesRoll =  ANGLES_90Deg;
			DesRoll -= ANGLES_1Deg;
			DesRoll = -DesRoll;
			break;
		}

		if( (adptr->LEFTWINGIN < BS_DAMLV2) && (adptr->RIGHTWINGIN > BS_DAMLV2) )
	 	{
			PitchIntercept = ANGLES_300Deg;
			DesRoll =  ANGLES_90Deg;
			DesRoll -= ANGLES_1Deg;
			break;
		}
 
		if(adptr->TAIL > BS_DAMLV2)
		{
			PitchIntercept = ANGLES_270Deg;
			DesRoll = ANGLES_45Deg;
			if(roll < ANGLES_0Deg) DesRoll = -DesRoll;
			break;
		}

		if(adptr->PILOTLEFT == BS_DEAD)
		{
			PitchIntercept = ANGLES_330Deg;
			DesRoll = ANGLES_45Deg;
			if(roll < ANGLES_0Deg) DesRoll = -DesRoll;
			break;
		}

		if(classtype->aerobaticfactor != AEROBATIC_LOW)
		{
			SLong totfuel;
			totfuel =  weap.left.int_fuel + weap.centre.int_fuel + weap.right.int_fuel;
			totfuel += weap.left.ext_fuel + weap.centre.ext_fuel + weap.right.ext_fuel;

			if(totfuel == 0)
			{
				PitchIntercept = ANGLES_350Deg;
				DesRoll = ANGLES_0Deg;
				if(World.Y < 100000)
				{
					Trans_Obj.LaunchCanopyEject(this,*mobileitem::currworld);
					weap.centre.int_fuel = 100000;  //1 kg	-> Should force a NO PILOT death move
				}
				break;
			}
		}

		break;
	}

//DeadCode CSB 07/05/99		AutoCalcPitch();
	if(PitchIntercept < pitch) pitch -= Timer_Code.FRAMETIME * 20;
	if(PitchIntercept > pitch) pitch += Timer_Code.FRAMETIME * 20;
	fly.cpitch = pitch;

	SimpleMoveToRoll(DesRoll);
	FP DeltaHdg = (SWord)roll * -(SWord)pitch * 2.0 * Timer_Code.FRAMETIME / (ANGLES_90Deg * 100.0);
	hdg += (SWord)DeltaHdg;

	if(vel != classtype->minvel)
	{
		SWord Accel = CalcAccel(classtype->minvel);
		AddAccel2Vel(Accel);
	}

	CalcXYZVel();
 	NewDeadPosition ();											//RJS 15Jan99
	SLong	groundheight = Trans_Obj.GetGroundLevel(*this);		//RJS 14Apr99
																//RJS 14Apr99
	if (World.Y <= groundheight)								//RJS 14Apr99
	{															//RJS 14Apr99
		World.Y = groundheight;									//RJS 14Apr99
		Trans_Obj.LandedEffect(*this,_Collide.NOSE_TOUCH);		//RJS 14Apr99
	}															//RJS 14Apr99
																//RJS 14Apr99
	SetFlightParams ();
}
/*	SWord	currroll,tanroll,deltaroll,deltahdg;
		UWord	deltahdg_pos;
		SWord	deltahdg_sign;
	
	
	adptr = (AircraftAnimData *)Anim;

/*	HdgIntercept = (Angles) (Math_Lib.rnd(2) *	(SWord) ANGLES_4Deg)  + (ANGLES)ANGLES_4Deg;
	PitchIntercept = ANGLES_345Deg;



 	if (adptr->LEFTWINGIN == BS_DEAD)							//RDH 31Jul98
 	{
 		HdgIntercept	-=	ANGLES_40Deg; 
 		PitchIntercept  -=	ANGLES_15Deg;
 	}
 	if (adptr->LEFTWINGOUT == BS_DEAD)							//RDH 31Jul98
 	{
 		HdgIntercept	-=	ANGLES_5Deg; 
 		PitchIntercept  -=	ANGLES_5Deg;
 	}
 	if (adptr->RIGHTWINGIN == BS_DEAD)							//RDH 31Jul98
 	{
 		HdgIntercept	+=	ANGLES_40Deg; 
 		PitchIntercept  -=	ANGLES_15Deg;
 	}
 	if (adptr->RIGHTWINGOUT == BS_DEAD)							//RDH 31Jul98
 	{
 		HdgIntercept	+=	ANGLES_5Deg; 
 		PitchIntercept  -=	ANGLES_5Deg;
 	}


	if  (	(adptr->TAIL == BS_DEAD)									//RJS 21Feb97
		||	(adptr->FIN == BS_DEAD)
		)
		PitchIntercept  -=	ANGLES_85Deg;


	if (	(HdgIntercept >>  ANGLES_20Deg)
		&&	(HdgIntercept <<  ANGLES_340Deg)
		)
	{
		CalcVelSub (classtype->maxdivevel);
		deltaroll = (SWord) ((SWord)(HdgIntercept)*Timer_Code.FRAMETIME/16);//RDH 19Nov96
		roll += (Angles) deltaroll;								//RDH 19Nov96
	}
	else
	{
		CalcVelSub (classtype->cruisevel);						//RDH 19Nov96
		SimpleMoveToRoll ((Angles) (2 * (SWord)HdgIntercept));	//RDH 20Nov96
//DeadCode RDH 20Nov96 		roll = (Angles) (2 * (SWord)HdgIntercept);				//RDH 19Nov96
	}

	AutoCalcPitch ();
	//use HdgIntercept to define rollrate
	// divide by 100 for strict frametime use, 32 gives a 3 times multiplier//RDH 01Oct96
//DeadCode RDH 19Nov96 	deltaroll = (SWord) ((SWord)(HdgIntercept)*Timer_Code.FRAMETIME/16);	//RDH 01Oct96
//DeadCode RDH 19Nov96 	roll += (Angles) deltaroll;
//DeadCode RDH 24Oct96 	if (	(roll > ANGLES_90Deg)							//RDH 24Jul96
//DeadCode RDH 24Oct96 		||	(roll < ANGLES_270Deg))							//RDH 24Jul96
//DeadCode RDH 24Oct96 	{
//DeadCode RDH 24Oct96 		currroll = -roll;
//DeadCode RDH 24Oct96 	}else
//DeadCode RDH 24Oct96 	{
//DeadCode RDH 24Oct96 		currroll = roll;
//DeadCode RDH 24Oct96 	}
//DeadCode RDH 24Oct96 	tanroll = Math_Lib.tan ((Angles) currroll);
//DeadCode RDH 24Oct96 	if (vel==0)												
//DeadCode RDH 24Oct96 		vel=1;
//DeadCode RDH 24Oct96 	hdg += (Angles) (40 * tanroll * Timer_Code.FRAMETIME/ vel);	
//DeadCode RDH 24Oct96 
	deltahdg = CalcHdg();
	Math_Lib.Pos ((SWord) deltahdg, deltahdg_pos,deltahdg_sign);
	if (deltahdg_pos > ANGLES_1Deg)
	{
		deltahdg = ANGLES_1Deg;
		if (deltahdg_sign == MathLib::NEGATIVE)
			deltahdg = -deltahdg;
	}
	hdg += (Angles)deltahdg;
*/
/*	SWord RollRate, PitchRate, YawRate, TargetPitch, TargetCPitch;
	RollRate  = 0;
	PitchRate = 0;
	YawRate   = 0;
	TargetPitch  = ANGLES_270Deg;	//Pitch of aircraft vector
	TargetCPitch = ANGLES_270Deg;	//Pitch of velocity vector

	
	for(;;)
	{
		if( (adptr->LEFTWINGIN == BS_DEAD) && (adptr->RIGHTWINGIN == BS_DEAD) && (adptr->TAIL == BS_DEAD) )
		{	
			TargetCPitch = ANGLES_270Deg;
			pitch -= ANGLES_1Deg;
			roll  += ANGLES_10Deg;
			hdg	  += ANGLES_1Deg;
	
			TargetPitch = pitch;
			break;
		}

		if( (adptr->LEFTWINGIN == BS_DEAD) && (adptr->RIGHTWINGIN == BS_DEAD) )
		{
			if(roll >= ANGLES_0Deg)
			{
				YawRate		=  ANGLES_5Deg;
//DeadCode CSB 01/02/99				RollRate	= -ANGLES_5Deg;
			}
			else
			{
				YawRate		= -ANGLES_5Deg;
//DeadCode CSB 01/02/99				RollRate	=  ANGLES_5Deg;
			}
			TargetPitch  =  ANGLES_275Deg;
			TargetCPitch =  ANGLES_275Deg;
			break;
		}
		
		if( (adptr->LEFTWINGIN == BS_DEAD) && (adptr->RIGHTWINGIN != BS_DEAD) )
		{
			RollRate	 =  ANGLES_2Deg; 
			YawRate		 = -ANGLES_8Deg;
			TargetPitch  =  ANGLES_300Deg;
			TargetCPitch =  ANGLES_300Deg;
			break;
		}

		if( (adptr->LEFTWINGIN != BS_DEAD) && (adptr->RIGHTWINGIN == BS_DEAD) )
	 	{
	 		RollRate	 = -ANGLES_2Deg; 
			YawRate		 =  ANGLES_8Deg;
			TargetPitch  =  ANGLES_300Deg;
			TargetCPitch =  ANGLES_300Deg;
			break;
		}
 
		if(adptr->TAIL == BS_DEAD)
		{
			TargetCPitch = ANGLES_270Deg;

			if(roll >= ANGLES_0Deg) YawRate	=  ANGLES_1Deg;
			else					YawRate	= -ANGLES_1Deg;
	
			if( (roll > ANGLES_350Deg) && (roll < ANGLES_10Deg) )
				TargetPitch = ANGLES_270Deg;
			else
				TargetPitch =  ANGLES_330Deg;
			break;
		}

		if(adptr->PILOTLEFT == BS_DEAD)
		{
			TargetCPitch = ANGLES_315Deg;
			TargetPitch  = ANGLES_315Deg;
			FP yawrate = (FP)roll * 0.01;
			YawRate = (Angles)(int)yawrate;
			FP NewRoll = (FP)roll * 0.995;
			roll = (Angles)(int)NewRoll;

			break;
		}

		break;
	}

	roll  += RollRate;
	hdg   += YawRate;
	if(fly.cpitch > (Angles)TargetCPitch) fly.cpitch -= ANGLES_FifthDeg;
	if(fly.cpitch < (Angles)TargetCPitch) fly.cpitch += ANGLES_FifthDeg;

	if(pitch > (Angles)TargetPitch) pitch -= ANGLES_FifthDeg;
	if(pitch < (Angles)TargetPitch) pitch += ANGLES_FifthDeg;

	CalcVelAlt (classtype->cruisevel);


	CalcXYZVel();
 	NewDeadPosition ();											//RJS 15Jan99
	SLong	groundheight = Trans_Obj.GetGroundLevel(*this);		//RJS 14Apr99
																//RJS 14Apr99
	if (World.Y <= groundheight)								//RJS 14Apr99
	{															//RJS 14Apr99
		World.Y = groundheight;									//RJS 14Apr99
		Trans_Obj.LandedEffect(*this,_Collide.NOSE_TOUCH);		//RJS 14Apr99
	}															//RJS 14Apr99
																//RJS 14Apr99
	SetFlightParams ();
}
*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoResurrect
//Author		Andrew McRae
//Date			Thu 5 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoResurrect (AirStrucPtr ac)
{
	static bool firstframe=true;
	Bool Owner;
	ULong n;
	ULong MaxHeight;

	if (ac == Manual_Pilot.ControlledAC2)
	{
		if (firstframe)
		{
// this aircraft belongs to this machine

			_DPlay.RepairAircraft (ac);
			_DPlay.AllowSuicide=FALSE;
			ac->Status.deaded=FALSE;							//DAW 22Jun99

// set aircraft orientation

			Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;

			Manual_Pilot.ControlledAC2->roll = ANGLES_0Deg;
			Manual_Pilot.ControlledAC2->pitch = ANGLES_0Deg;
//		Manual_Pilot.ControlledAC2->hdg = ac->hdg;
//		Manual_Pilot.ControlledAC2->vel = MPH100;
//		Manual_Pilot.ControlledAC2->vel = MPH200;

			if (ac->fly.pModel->EngineList)
			{
				if (ac->fly.pModel->EngineList->Type==ET_JET)
				{
// jets go a bit quicker than biplanes then?

					Manual_Pilot.ControlledAC2->vel = (MPH400+MPH100);
				}
				else
				{
// mustangs a bit slower than jet?

					Manual_Pilot.ControlledAC2->vel = (MPH200+MPH100);
				}
			}
			else
			{
// what are you, a balloon or something????
				
				Manual_Pilot.ControlledAC2->vel=0;
			}

// save sensitivity setting

//		UWord OldSensitivity;
	
//		OldSensitivity = Manual_Pilot.GetSensitivity();
//		Manual_Pilot.SetSensitivity (OldSensitivity);
			firstframe=false;
		}

// move the aircraft
// a bit faster for jets!

		ac->World.Y+=FT_20;
//		ac->World.Y += FT_5;
		ac->hdg += ANGLES_4Deg;

// needed to update flight model which is still being processed even though its ignored at this stage

		Manual_Pilot.InitManualPilot (Manual_Pilot.ControlledAC2);

// calc max height

		MaxHeight = 0;
		for (n=0; n<MAXPLAYERS; n++)
		{
			if (_DPlay.ActivePlayers&(1<<n))
			{
				AirStrucPtr ac2;
				ac2 = (AirStrucPtr)MobileItem::currworld->ConvertPtrUID ((UniqueID)_DPlay.AllocPacket [n]);
				if (ac2)
				{
					if (ac != ac2)
					{
						if (ac2->World.Y > MaxHeight)
							MaxHeight = ac2->World.Y;
					}
				}
			}
		}

// need MaxHeight a bit bigger than for biplanes!

		if (MaxHeight == 0)	// just in case no aircraft found
			MaxHeight = FT_30000;
//			MaxHeight = FT_10000;

		MaxHeight += FT_2000;

//		if (MaxHeight > FT_10000)
//			MaxHeight = FT_10000;

		if (MaxHeight > FT_30000)
			MaxHeight = FT_30000;

 		if (Key_Tests.KeyPress3d(RESURRECTKEY) || (ac->World.Y >= MaxHeight))
		{
			firstframe=true;

//			Manual_Pilot.ControlledAC2->vel = MPH100;
			Manual_Pilot.InitManualPilotSub(ac);
			ac->movecode = AUTO_FOLLOWWP;	//0;					//JIM 10Dec96
			Manual_Pilot.controlmode=ManualPilot::MANUAL;	// PILOTDEAD

// enable its death - not yet
//			for (n=0; n<MAXPLAYERS; n++)
//			{
//				if (_DPlay.AllocPacket [n] == (ac->uniqueID.count))
//					ac->Status.deaded=FALSE;
//			}

// Send message to tell other machines this aircraft is back online

			_DPlay.RepairAircraft(ac);							//AMM 12Jul99
			_DPlay.ResetCommsSurfaces();// reset gear etc now so that it is up when I resurrect
			_DPlay.NewSpecial(PIDC_RESURRECTEND,0,0,0);			//AMM 01Sep98
			Persons2::PlayerSeenAC->ai.radiosilent=FALSE;
			Persons2::PlayerGhostAC->ai.radiosilent=FALSE;
			_Miles.ResetSoundFlags();
			_DPlay.viewtime=true;
			_DPlay.AllowSuicide=TRUE;
//DeadCode AMM 12Jul99 			_DPlay.RepairAircraft(ac);
			_DPlay.SuicideTime=0;
			_DPlay.resurrectend=true;
			Trans_Obj.View_Object->SetToPiloted((itemptr)Persons2::PlayerSeenAC,false);//AMM 12Jul99
		}
	}
	else
	{
// this aircraft belongs to another player

		_DPlay.RepairAircraft (ac);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoFollowWpWing
//Author		R. Hyde					Craig Beeston
//Date			//RDH 27Feb96			23 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns		//This routine has trouble with the inside aircraft when a big formation is turning.  
//					His target position moves backwards faster thatn he can decellerate
//
//------------------------------------------------------------------------------
void AirStruc::AutoFollowWpWing (AirStrucPtr MyLeader)

{
//DeadCode CSB 13/06/99	/* TEST CODE CSB 11/06/99 */
//DeadCode CSB 13/06/99	/* TEST CODE CSB 11/06/99 */	
//DeadCode CSB 13/06/99	/* TEST CODE CSB 11/06/99 */
//DeadCode CSB 13/06/99		if(fly.pModel->Type == AT_F86E)
//DeadCode CSB 13/06/99		{
//DeadCode CSB 13/06/99			PrintVar((fly.callnum - 1) * 20, 22, "VX %.1f ", FP(velx * 0.1));
//DeadCode CSB 13/06/99			PrintVar((fly.callnum - 1) * 20, 23, "VY %.1f ", FP(vely * 0.1));
//DeadCode CSB 13/06/99			PrintVar((fly.callnum - 1) * 20, 24, "VZ %.1f ", FP(velz * 0.1));
//DeadCode CSB 13/06/99		}
//DeadCode CSB 13/06/99	/* TEST CODE CSB 11/06/99 */
//DeadCode CSB 13/06/99	/* TEST CODE CSB 11/06/99 */
//DeadCode CSB 13/06/99	/* TEST CODE CSB 11/06/99 */
	
	const CanSideSlip = 1;
	const InFront     = 2;
	const Beside      = 3;
	const Behind      = 4;
	char  RelPos = 0;

	AirStrucPtr lf;
	if(MyLeader)  
		lf = MyLeader;
	else														//RDH 21May99
		lf = FindLeadCandidate();

	if (	( ((lf->roll + ANGLES_60Deg) >> (ANGLES_120Deg))	
			||	((lf->pitch + ANGLES_30Deg) >> (ANGLES_60Deg)) 
			|| (lf->vel < 500) )
			&& (!currworld->vp || !currworld->vp->Accel())
		)
			information = FALSE;

	if(information)	
	{	//If we are slowed by a follower, then slow our leader
		//This approach leads to a chain of slowdowns and no false slowdowns:
		//wing->element->flight->group->escortee
		if (slowdownleader)											  //DAW 12/05/99
		{
			Bool DontSlowDown = FALSE;
			if(	   ((lf->classtype->visible == B26) || (lf->classtype->visible == B29))
				&& ((classtype->visible != B26) && (classtype->visible != B29)) )
				DontSlowDown = TRUE;
			
			if(!DontSlowDown)
				lf->slowdownleader=TRUE;								  //DAW 12/05/99 //DAW 12/05/99
		}

		slowdownleader=FALSE;
		CopyLeader (lf);
	}
	else
	{
		if(!TimeLeft())
		{
			Bool GotIntoFormation = FALSE;
			Bool DontSlowDown = FALSE;
			if(	   ((lf->classtype->visible == B26) || (lf->classtype->visible == B29))
				&& ((classtype->visible != B26) && (classtype->visible != B29)) )
				DontSlowDown = TRUE;
			
			if(!DontSlowDown)
				lf->slowdownleader=TRUE;								  //DAW 12/05/99

			slowdownleader=FALSE;
//DEADCODE DAW 12/05/99 			if(leader)												//JIM 17Sep96
//DEADCODE DAW 12/05/99 				leader->slowdownleader=TRUE;						//JIM 17Sep96
//DEADCODE DAW 12/05/99 			if(fly.leadflight)										//JIM 17Sep96
//DEADCODE DAW 12/05/99 				fly.leadflight->slowdownleader=TRUE;				//JIM 17Sep96

			despos = *PositionWRTLeader(lf);
			despos.X -= (lf->velx * Timer_Code.FRAMETIME) / 10;
			despos.Y -= (lf->vely * Timer_Code.FRAMETIME) / 10;
			despos.Z -= (lf->velz * Timer_Code.FRAMETIME) / 10;

			COORDS3D GlobDelta, LocalDelta;
			GlobDelta.X = despos.X - World.X;
			GlobDelta.Y = despos.Y - World.Y;
			GlobDelta.Z = despos.Z - World.Z;
			RotateToHdg(GlobDelta, LocalDelta, lf->hdg);
			
			COORDS3D AbsD;
			AbsD.X = LocalDelta.X;	if(AbsD.X < 0) AbsD.X *= -1;
			AbsD.Y = LocalDelta.Y;	if(AbsD.Y < 0) AbsD.Y *= -1;
			AbsD.Z = LocalDelta.Z;	if(AbsD.Z < 0) AbsD.Z *= -1;

			FP RangeSq = Distance3DSquared(&despos);
			if(RangeSq > FP(METRES100 * METRES100))
				Status.Drawn=FALSE;			

			if(		(RangeSq < FP(METRES50 * METRES50))	//Can we go into sideslip
				&&	(vel > classtype->minvel)
				&&	((lf->hdg - hdg < ANGLES_5Deg) && (hdg - lf->hdg < ANGLES_5Deg)) 
				&&	((lf->roll <= ANGLES_60Deg) && (-lf->roll <= ANGLES_60Deg)) )
				RelPos = CanSideSlip;
			else
			{
				if(AbsD.X > AbsD.Z)			RelPos = Beside;
				else
				{
					if(LocalDelta.Z > 0)	RelPos = Behind;
					else					RelPos = InFront;
				}
			}

			if(RelPos == CanSideSlip)
			{
				Range = Distance3D(&despos);
				CalcVelWing(lf, LocalDelta.Z);
				GotIntoFormation = SideSlip (lf);

				if(	(!currworld->vp) ||	(currworld->vp->Accel()) )						//CSB 10/05/99	
					GotIntoFormation = TRUE;											//CSB 10/05/99	
			}
			else
			{
				Bool level = TRUE;
				FP leadtime = 0;

				COORDS3D GlobVel;
				COORDS3D LocalVel;
				GlobVel.X = velx;
				GlobVel.Y = vely;
				GlobVel.Z = velz;
				RotateToHdg(GlobVel, LocalVel, lf->hdg);
				
				switch(RelPos)
				{
					case Behind:
					{
						if(LocalVel.Z > lf->vel)
							leadtime = (LocalDelta.Z * 20) / (LocalVel.Z - lf->vel);
						else leadtime = 60*SECS100;
						level &= CalcVelWing(lf, LocalDelta.Z);
						break;
					}
				
					case Beside:
					{
						if(LocalDelta.X * LocalVel.X > 0)
						{
							leadtime = (LocalDelta.X * 20) / LocalVel.X;
							FP maxtime = LocalDelta.X / 20;
							if(maxtime < 0) maxtime *= -1;
							if(leadtime > maxtime) leadtime = maxtime;
						}
						level &= CalcVelWing(lf, LocalDelta.Z);
						break;
					}
				
					case InFront:
					{
						if(LocalDelta.Z < -50000)	//more than 500 metres infront	-> Turn back
							level &= CalcVelWing(lf, 100000);
						else
						{
							level &= CalcVelWing(lf, LocalDelta.Z);
							if(LocalVel.Z < lf->vel)
								leadtime = (LocalDelta.Z * 20) / (LocalVel.Z - lf->vel);
							else
								leadtime = 20*SECS100;
						}
						break;
					}
					break;

				}			

				COORDS3D AimPos = despos;					//Position ahead of the target aircraft
				if(lf->vel < 500) 
					AimPos.Y += FT_1000;
				if(leadtime > 0)
				{
					MODMAXMIN(leadtime, 0, 60*SECS100);
					AimPos.X += (leadtime * lf->velx) / 10;
					if(lf->vely > 0)
						AimPos.Y += (leadtime * lf->vely) / 10;
					else
						AimPos.Y += (leadtime * lf->vely) / 20;
					AimPos.Z += (leadtime * lf->velz) / 10;
				}
//DeadCode CSB 24/05/99					SLong groundlevel = Trans_Obj.GetGroundLevel(*this); 
//DeadCode CSB 24/05/99					if(AimPos.Y < groundlevel + 10000)
//DeadCode CSB 24/05/99						AimPos.Y = groundlevel + 10000;
//DeadCode CSB 24/05/99					if( ((SWord) PitchIntercept > ANGLES_90Deg)	&& (World.Y < (groundlevel + FT_1000))	)
//DeadCode CSB 24/05/99						PitchIntercept = ANGLES_0Deg;					//RDH 18Nov96
				InterceptandRange(&AimPos);
				level&=AutoCalcPitch ();
				level&=CalcHdgRoll ();
				CalcXYZVel ();

				if(level)
				{
					if(RangeSq > FP(KM10) * FP(KM10))
						SetManoeuvreTime(THIRTYSECS100);
					else if(RangeSq > FP(KM1) * FP(KM1))
						SetManoeuvreTime(FIVESECS100);
				}

			}
			
//MOVED TO WITHIN SIDE SLIP CALL ^^^
//DeadCode DAW 15Jun99 			if(	(!currworld->vp) ||	(currworld->vp->Accel()) )						//CSB 10/05/99	
//DeadCode DAW 15Jun99 				GotIntoFormation = TRUE;											//CSB 10/05/99	
																					//CSB 10/05/99	
			if(GotIntoFormation)													//CSB 10/05/99	
			{																		//CSB 10/05/99	
				information = TRUE;													//CSB 10/05/99	
				World=despos;		//position correctly							//CSB 10/05/99	
//DeadCode CSB 29/06/99					velx=vely=velz=0;	//don't move this frame!						//CSB 10/05/99	
			}
		}
		NewPosition ();
		SetFlightParams ();
	}
}		
		


//DeadCode CSB 23/04/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 23/04/99	//Procedure		AutoFollowWpWing
//DeadCode CSB 23/04/99	//Author		R. Hyde 
//DeadCode CSB 23/04/99	//Date			//RDH 27Feb96
//DeadCode CSB 23/04/99	//
//DeadCode CSB 23/04/99	//Description	
//DeadCode CSB 23/04/99	//
//DeadCode CSB 23/04/99	//Inputs		
//DeadCode CSB 23/04/99	//
//DeadCode CSB 23/04/99	//Returns	
//DeadCode CSB 23/04/99	//
//DeadCode CSB 23/04/99	//------------------------------------------------------------------------------
//DeadCode CSB 23/04/99	void AirStruc::AutoFollowWpWing (AirStrucPtr MyLeader)
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99	{
//DeadCode CSB 23/04/99		const flightpos = position();
//DeadCode CSB 23/04/99		PrintVar(50, 20+flightpos, "Vel %.1f ", (FP)(vel / 10.0));
//DeadCode CSB 23/04/99	//##if in autoprecombat
//DeadCode CSB 23/04/99	//##if manoeuvre == MANOEUVRE_LINEABREAST
//DeadCode CSB 23/04/99	//##if manoeuvre == MANOEUVRE_LINEASTERN
//DeadCode CSB 23/04/99	//##			use different formation
//DeadCode CSB 23/04/99	//##
//DeadCode CSB 23/04/99	//##Z
//DeadCode CSB 23/04/99	//##
//DeadCode CSB 23/04/99	 	SLong groundlevel;
//DeadCode CSB 23/04/99		AirStrucPtr lf;
//DeadCode CSB 23/04/99		if(MyLeader)  lf = MyLeader;
//DeadCode CSB 23/04/99		else lf = FlyEscortTo();
//DeadCode CSB 23/04/99		if(lf == NULL) lf = FindLeadCandidate();
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99	//DeadCode CSB 20/04/99		if (leader==NULL)	lf=fly.leadflight;
//DeadCode CSB 23/04/99	//DeadCode CSB 20/04/99		else				lf=*leader;
//DeadCode CSB 23/04/99	if(flightpos == 1)
//DeadCode CSB 23/04/99		PrintVar(40, 20, "   Leader Vel %.1f ", (FP)(lf->vel / 10.0));
//DeadCode CSB 23/04/99	//#pragma warnmsg("Paul: need test for accel")
//DeadCode CSB 23/04/99		if (	( ((lf->roll + ANGLES_60Deg) >> (ANGLES_120Deg))	
//DeadCode CSB 23/04/99				||	((lf->pitch + ANGLES_30Deg) >> (ANGLES_60Deg)) )
//DeadCode CSB 23/04/99				&& (!currworld->vp || !currworld->vp->Accel())
//DeadCode CSB 23/04/99	//TEMPCODE DAW 28/03/99 		&&	(Timer_Code.accel == BOOL_FALSE) 
//DeadCode CSB 23/04/99			)
//DeadCode CSB 23/04/99				information = FALSE;
//DeadCode CSB 23/04/99	if(information)
//DeadCode CSB 23/04/99		PrintString(70, 20+flightpos, "WELDED  ");
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99		if(information)	CopyLeader (lf);
//DeadCode CSB 23/04/99		else if(!TimeLeft())
//DeadCode CSB 23/04/99		{
//DeadCode CSB 23/04/99			Bool GotIntoFormation = FALSE;
//DeadCode CSB 23/04/99			if (leader)												//JIM 17Sep96
//DeadCode CSB 23/04/99				leader->slowdownleader=TRUE;						//JIM 17Sep96
//DeadCode CSB 23/04/99			if (fly.leadflight)										//JIM 17Sep96
//DeadCode CSB 23/04/99				fly.leadflight->slowdownleader=TRUE;				//JIM 17Sep96
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99			InterceptandRange(PositionWRTLeader() );
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99			if(Range > METRES100)
//DeadCode CSB 23/04/99				Status.Drawn=FALSE;			
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99			Bool level=(Bool)(Range > METRES500);
//DeadCode CSB 23/04/99			level&=CalcVelWing(lf);
//DeadCode CSB 23/04/99	//DeadCode CSB 12/04/99			level&=AutoCalcPitch ();
//DeadCode CSB 23/04/99			groundlevel = Trans_Obj.GetGroundLevel(*this); 			//RJS 14Apr99
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99			if( ((SWord) PitchIntercept > ANGLES_90Deg)	&& (World.Y < (groundlevel + FT_1000))	)
//DeadCode CSB 23/04/99				PitchIntercept = ANGLES_0Deg;					//RDH 18Nov96
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99	/////////////////////Fix This !!!!!
//DeadCode CSB 23/04/99	//DEADCODE JIM 14/04/99 I JUST WASTED A DAY BECAUSE OF THIS!!!!
//DeadCode CSB 23/04/99	//DEADCODE JIM 14/04/99 if(1==1)
//DeadCode CSB 23/04/99	//DEADCODE JIM 14/04/99 SideSlip (lf);
//DeadCode CSB 23/04/99	//DEADCODE JIM 14/04/99 else
//DeadCode CSB 23/04/99	//DEADCODE JIM 14/04/99 I JUST WASTED A DAY BECAUSE OF THIS!!!!
//DeadCode CSB 23/04/99	{
//DeadCode CSB 23/04/99			if (	(Range > METRES100) 
//DeadCode CSB 23/04/99				||	(vel < classtype->minvel)
//DeadCode CSB 23/04/99				||	((lf->roll > ANGLES_60Deg) || (-lf->roll > ANGLES_60Deg))
//DeadCode CSB 23/04/99				||	((lf->hdg - hdg > ANGLES_5Deg) || (hdg - lf->hdg > ANGLES_5Deg)) )
//DeadCode CSB 23/04/99			{
//DeadCode CSB 23/04/99	PrintVar   (60, 20+flightpos, "Range %.1f ", (FP)(Range / 100.0));
//DeadCode CSB 23/04/99	PrintString(70, 20+flightpos, "INDEPEND");
//DeadCode CSB 23/04/99				if((vel > lf->vel) && (Range > 100000))
//DeadCode CSB 23/04/99				{
//DeadCode CSB 23/04/99					ULong TimeToLead = Range / (vel - lf->vel);	//10 cs
//DeadCode CSB 23/04/99					if(TimeToLead > 60 * 10) TimeToLead = 60 * 10;
//DeadCode CSB 23/04/99					SLong DeltaPosX = lf->velx * TimeToLead;
//DeadCode CSB 23/04/99					SLong DeltaPosY = lf->vely * TimeToLead;
//DeadCode CSB 23/04/99					SLong DeltaPosZ = lf->velz * TimeToLead;
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99					despos.X += DeltaPosX;
//DeadCode CSB 23/04/99					despos.Y += DeltaPosY;
//DeadCode CSB 23/04/99					despos.Z += DeltaPosZ;
//DeadCode CSB 23/04/99					InterceptandRange(&despos);
//DeadCode CSB 23/04/99					InterceptandRange(&despos);	
//DeadCode CSB 23/04/99				}
//DeadCode CSB 23/04/99	
//DeadCode CSB 23/04/99				level&=AutoCalcPitch ();
//DeadCode CSB 23/04/99				level&=CalcHdgRoll ();
//DeadCode CSB 23/04/99				CalcXYZVel ();
//DeadCode CSB 23/04/99			}else
//DeadCode CSB 23/04/99			{
//DeadCode CSB 23/04/99	//DeadCode CSB 23/02/99				if ((Range > METRES10) || ((lf->roll + ANGLES_30Deg) >> (ANGLES_60Deg))	)
//DeadCode CSB 23/04/99	//DeadCode CSB 23/02/99				{
//DeadCode CSB 23/04/99	//DeadCode CSB 23/02/99					CalcHdgRollFlat ();
//DeadCode CSB 23/04/99	//DeadCode CSB 23/02/99					roll 	= lf->roll;								//RDH 30Nov96
//DeadCode CSB 23/04/99	//DeadCode CSB 23/02/99					CalcXYZVel ();
//DeadCode CSB 23/04/99	//DeadCode CSB 23/02/99				}else
//DeadCode CSB 23/04/99	//DeadCode CSB 23/02/99				{
//DeadCode CSB 23/04/99	//DeadCode CSB 12/04/99				SideSlip (lf);
//DeadCode CSB 23/04/99	//DeadCode CSB 23/02/99				}
//DeadCode CSB 23/04/99				if((!Status.Drawn) && (Range < METRES50))	//Only if not visible between 100m..50m
//DeadCode CSB 23/04/99				{
//DeadCode CSB 23/04/99					information = TRUE;									//JIM 29May96
//DeadCode CSB 23/04/99					World=despos;		//position correctly
//DeadCode CSB 23/04/99					velx=vely=velz=0;	//don't move this frame!
//DeadCode CSB 23/04/99				}
//DeadCode CSB 23/04/99				else
//DeadCode CSB 23/04/99				{
//DeadCode CSB 23/04/99					GotIntoFormation = SideSlip (lf);
//DeadCode CSB 23/04/99	PrintVar   (60, 20+flightpos, "Range %.1f ", (FP)(Range / 100.0));
//DeadCode CSB 23/04/99	PrintString(70, 20+flightpos, "SIDESLIP");
//DeadCode CSB 23/04/99				}
//DeadCode CSB 23/04/99			}
//DeadCode CSB 23/04/99			if (level)
//DeadCode CSB 23/04/99				if (Range > MILES01)
//DeadCode CSB 23/04/99					SetManoeuvreTime(THIRTYSECS100);
//DeadCode CSB 23/04/99	//DeadCode CSB 12/04/99				else
//DeadCode CSB 23/04/99	//DeadCode CSB 12/04/99					SetManoeuvreTime(FIVESECS100);
//DeadCode CSB 23/04/99	}/////////////////////Fix This !!!!!
//DeadCode CSB 23/04/99			NewPosition ();
//DeadCode CSB 23/04/99			SetFlightParams ();
//DeadCode CSB 23/04/99			SWord	reqdeltahdg;
//DeadCode CSB 23/04/99			UWord	reqdeltahdg_pos;
//DeadCode CSB 23/04/99			SWord	reqdeltahdg_sign;
//DeadCode CSB 23/04/99	//DeadCode CSB 23/02/99			SWord	roll;										//RDH 05Dec96
//DeadCode CSB 23/04/99			UWord	roll_pos;									//RDH 05Dec96
//DeadCode CSB 23/04/99			SWord	roll_sign;									//RDH 05Dec96
//DeadCode CSB 23/04/99	//DeadCode JIM 21Oct96 		reqdeltahdg = 	(SWord) ((SWord) fly.leadflight->hdg - hdg);
//DeadCode CSB 23/04/99	//DeadCode RDH 05Dec96 		reqdeltahdg = 	(SWord) ((SWord) lf->hdg - hdg);		//JIM 21Oct96
//DeadCode CSB 23/04/99	//DeadCode CSB 20/04/99			reqdeltahdg = 	(SWord) (lf->hdg - hdg);	//RDH 05Dec96
//DeadCode CSB 23/04/99	//DeadCode CSB 20/04/99			Math_Lib.Pos (reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode CSB 23/04/99	//DeadCode RDH 30Nov96 		desposrange = 0;
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99			desposrange = vel - lf->vel;							//RDH 30Nov96
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99			if (desposrange < 50)									//RDH 30Nov96
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99				desposrange = 50;									//RDH 30Nov96
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99			desposrange = 100;	//CSB 15/04/99	
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99			Math_Lib.Pos ((SWord)(roll - lf->roll), roll_pos,roll_sign);	//RDH 05Dec96
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99			if  (	(ReachedDesPos ())
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99				&&		(roll_pos < ANGLES_5Deg)						//RDH 24Jul96
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99	//DeadCode RDH 05Dec96 				&& (roll > ANGLES_355Deg)						//RDH 24Jul96
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99				&&	(reqdeltahdg_pos  < ANGLES_10Deg)
//DeadCode CSB 23/04/99	//DeadCode CSB 15/04/99				)
//DeadCode CSB 23/04/99			if(GotIntoFormation)
//DeadCode CSB 23/04/99			{
//DeadCode CSB 23/04/99				information = TRUE;									//JIM 29May96
//DeadCode CSB 23/04/99				World=despos;
//DeadCode CSB 23/04/99			}
//DeadCode CSB 23/04/99		}
//DeadCode CSB 23/04/99		else
//DeadCode CSB 23/04/99		{
//DeadCode CSB 23/04/99			NewPosition ();
//DeadCode CSB 23/04/99			SetFlightParams ();
//DeadCode CSB 23/04/99		}
//DeadCode CSB 23/04/99	}

//Movement.H
//enum	PhaseFAC	{
//	FAC_WAIT=0,			FAC_WAITRECONNECT,			FAC_WELCOME_LONGRANGE,		FAC_WINGWAGGLE,
//		FAC_WAITCLOSER,	FAC_WELCOME_CLOSE,			FAC_WAITTOUCHING,			
//	FAC_TARGETAREA=16,	FAC_TARGETAREARECONNECT,	FAC_NEXTTARGASBOMBERCLIMBS,	FAC_DESCRIBETARGETS,	
//		FAC_FLYTOAREA,	FAC_HOMEFORCES,				FAC_TARGETBMBCLOSER,		FAC_TARGETTOOCLOSE,
//		FAC_WATCHROCKETS,
//	FAC_ROCKETEER=32,	FAC_ROCKETEERRECONNECT,		FAC_GOINGIN,				FAC_SEEMYSMOKE,	
//		FAC_CLIMBTOOBSERVE,	FAC_ADVISEATTACK,		FAC_OBSERVING,				FAC_MISSTIMEOUT,
//		FAC_ENOUGHHITS,	FAC_HIT,					FAC_DAMAGE,					FAC_HITFRIENDS,
//	FAC_EXTRAS=48,		FAC_REQUEST_LONGRANGE,		FAC_GOINGHOME,				FAC_MORETARGETS,	
//		FAC_NOMORETARGETS,
//	FAC_CAS_SPECIAL=64,80,96,112
//
//
//
//	FAC_STAGEMASK=-16,FAC_SUBSTAGEMASK=15
//					};
//////////////////////////////////////////////////////////////////////
//
// Function:    AutoCAS
// Date:		30/03/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
static int	CASMANSTEP(PhaseFAC p)	
{return p>>4;}

static SupplyLine* FindLine(WayPointPtr trgwp)
{
//	while (trgwp && trgwp->skipunder)
//		trgwp=trgwp->prev;
	ItemBasePtr trg=NULL;
	if (trgwp)
		trg=trgwp->target;
	if (trg)
	{
	//follow to find battle
		SupplyNode* sn=SupplyTree::FindSupplyNodeForItem(trg->uniqueID.count);
		SupplyLine* sl=sn->supplyline;
		if (sl->frontline->forward && sl->frontline->forward->suppliee==sn)
			return sl;
	}
	return NULL;
}
void	AirStruc::LogAutoCASKill()
{
	int forcesize=0;
	for (AirStrucPtr fllead=this;fllead;fllead=fllead->fly.nextflight)
		for (AirStrucPtr follower=fllead;follower;follower=follower->Follower())
			forcesize++;

	if (Math_Lib.rnd(30)>forcesize)
		return;

	SupplyLine* sl=FindLine(waypoint);
	if (sl)
	{
//pick a RED team
		TeamDef::Team	reqteam=(sl->initiative==REDATTACKING)?TeamDef::HOME:TeamDef::AWAY;
			for (int count=sl->groundbattle.usedteams,team=Math_Lib.rnd(count);count;count--,team=(team==0)?(sl->groundbattle.usedteams-1):(team-1))
				breakif(sl->groundbattle.teamlist[team].team==reqteam);
		sl->groundbattle.teamlist[team].lastlosses++;
	}
	else
		assert(!"Expected a ground battle here!");


}

AirStrucPtr	AirStruc::FindMyFAC()	 //SGT
{
	if (ai.unfriendly && ai.unfriendly->Status.size==AIRSTRUCSIZE)	//already set up????
		if (AirStrucPtr(*ai.unfriendly)->movecode==AUTO_FAC)
			return *ai.unfriendly;

	SupplyLine* sl=FindLine(waypoint);
	AirStrucPtr t=NULL;
	if (sl)
	{
		for (t=*MobileItem::ACList;t;t=*t->nextmobile)
			if (t->movecode==AUTO_FAC)
				breakif(t->fly.callname==sl->TACcallname ||	t->fly.callname==sl->FACcallname);
		
	}
	return t;
}

void	AirStruc::SetToCAS(bool firsttime)
{
	movecode=AUTO_CAS;
	AirStrucPtr fac=FindMyFAC();
	if (fac)
	{
		ai.unfriendly=fac;
		ai.ManStep=CASMANSTEP(FAC_TARGETAREA);
		if (!formpos && fac->follower!=this)
		{
			fac->follower=this;
			if (firsttime)
				fac->SendFACMessage(FAC_REQUEST_LONGRANGE);
		}
	}
	else
		ai.ManStep=CASMANSTEP(FAC_WAIT);
}

void	AirStruc::AutoCAS()			   //manstep is 4 bits...
{
	if (!ai.unfriendly || ai.unfriendly->Status.size==AIRSTRUCSIZE)
	{
		switch (ai.ManStep<<4)
		{
		case FAC_WAIT:			//no FAC. Just followwp and occasionally flag a kill
		{						//chance each tome we pass a waypoint, or set longrange flag.
			WayPoint* wp=waypoint;
			AutoFollowWp();		//Will do AFWPW
			if (waypoint->wpname!=WPNAME_Target)
				movecode=AUTO_FOLLOWWP;
			else
			if (!formpos)
				if (wp!=waypoint)
				{
					LogAutoCASKill();
					LogAutoCASKill();
					LogAutoCASKill();
				}
				else
				if (manoeuvretime>29*SECS100)
				{
					manoeuvretime=29*SECS100;
					LogAutoCASKill();
				}
		}
		break;
		case FAC_TARGETAREA:	//travel to FAC's target area
		{	
			if (!formpos)
			{
				//first, find the FAC associated with us...
				//then his current waypoint, and it's target
				ai.unfriendly=FindMyFAC();
				if (ai.unfriendly)
				{
					ItemBasePtr trg=AirStrucPtr(*ai.unfriendly)->waypoint->target;
					assert(trg&&"FAC always has a target!!!");
					despos=trg->World;
					despos.Y+=METRES2500;
					InterceptandRange(&despos);
					if (Range<METRES1400)
						CalcVelAlt(1200);
					else
						CalcVelAlt(1800);
					CalcHdgRollLimited();
					AutoCalcPitch();
					CalcXYZVel();
					NewPosition ();
					SetFlightParams ();
				}
				else
				{	//FAC must be dead... go home
					while (waypoint->action!=wpstoploopchkno)
						NextWayPoint();
					NextWayPoint();
					movecode=AUTO_FOLLOWWP;
					AutoFollowWp();
				}
			}
			else
			{
				AutoFollowWpWing();
				if (fly.leadflight->movecode!=AUTO_CAS)
				{
					movecode=(AutoMoveCodeTypeSelect)fly.leadflight->movecode;
					waypoint=fly.leadflight->waypoint;
				}
			}


		}
		break;
		case FAC_ROCKETEER:		//finished drop some rockets, now need to get group to safe alt
		{
			ai.unfriendly=FindMyFAC();
			if (ai.unfriendly)
			{
				int	keyalt=ai.unfriendly->World.Y;
				if (ai.unfriendly->shape!=T6)	
					keyalt+=waypoint->World.Y;
				if (World.Y<keyalt+METRES100)
				{	//climb like a madman
					CalcVelAlt(1200);
					CalcHdgRollLimited(ANGLES_0Deg);
					PitchIntercept=ANGLES_10Deg;
					AutoCalcPitch();
					CalcXYZVel();
					NewPosition ();
					SetFlightParams ();
				}
				else
				{
					if (leader && leader->World.Y>keyalt)
						AutoFollowWpWing();
					else
					if (!leader && fly.leadflight && fly.leadflight->World.Y>keyalt)
						AutoFollowWpWing();
					else
					{
						CalcVelAlt(1800);
						CalcHdgRollLimited(ANGLES_10Deg);
						PitchIntercept=ANGLES_2Deg;
						AutoCalcPitch();
						CalcXYZVel();
						NewPosition ();
						SetFlightParams ();
					}
					if ((timerseed>>1)==formpos)
					{
						AirStrucPtr follower=FindGroupLeader();
						for (AirStrucPtr fllead=follower;fllead;fllead=fllead->fly.nextflight)
							for (follower=fllead;follower;follower=follower->Follower())
								if (follower->World.Y<keyalt)
									if (!follower->AcIsPlayer() || follower->World.Y<keyalt-METRES500)
										break;
						if (!follower)
						{	//everyone is above altitude!!!
							AirStrucPtr follower=FindGroupLeader();
							for (AirStrucPtr fllead=follower;fllead;fllead=fllead->fly.nextflight)
								for (follower=fllead;follower;follower=follower->Follower())
									follower->ai.ManStep=CASMANSTEP(FAC_TARGETAREA);
						}
					}
				}
			}
			else
			{
				if (World.Y<METRES2000)
				{
					CalcVelAlt(1200);
					CalcHdgRollLimited(ANGLES_0Deg);
					PitchIntercept=ANGLES_10Deg;
					AutoCalcPitch();
					CalcXYZVel();
					NewPosition ();
					SetFlightParams ();
				}
				else
				{
					movecode=AUTO_FOLLOWWP;
					AutoFollowWp();
				}
			}

		}
		break;
		case FAC_EXTRAS:		//whatever...
		{
		}
		break;
		}
#ifndef NDEBUG
		if (!ai.ManStep)
			INT3;
#endif
	}
	else
	{	//drop some rockets
		AutoBomb();
		if (ai.unfriendly==NULL)
			ai.ManStep=CASMANSTEP(FAC_ROCKETEER);
	}
}

////////////////////////////////////////////////////////////////////////
//
// Function:    AutoFAC 
// Date:        18/12/98
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
enum	WEAPONRY
{
WEAP_GUNS=1,
WEAP_ROCK=2,
WEAP_NAP=4,
WEAP_BOMB=8
};

static UByte	Weaplookup[]=
{
	10,1,9,4,
	3,7,8,8,
	2,6,5,5,
	2,6,5,5		//should never happen
};


 const	TargetIndexes& TargetIndexes::SetWeap(AirStruc *trg)  const
{	//phrase to describe all weapons carried...
	UByte	weapflags=0;
	WeapAnimData*	weapon=NULL;										//RJS 29Aug96
	int index=0;
	SLong	xpos,ypos,zpos;
	UWord	mvel,mdelay,mburst;									//RDH 31Jul98
	if (trg->Anim==NULL)
	{
		assert (trg==Persons2::PlayerGhostAC);
		trg=Persons2::PlayerSeenAC;
	}
	while (index<6)
	{
		weapon = SHAPE.GetWeaponLauncher(trg,index++,xpos,ypos,zpos,mvel,mdelay,mburst);//RDH 31Jul98
		if (weapon->LoadedStores)
		if ((weapon->LauncherType&LT_MASK)==LT_BULLET)
			weapflags|=WEAP_GUNS;
		else
		if ((weapon->LauncherType&LT_MASK)==LT_ROCKET)
			weapflags|=WEAP_ROCK;
		else
		if ((weapon->LauncherType&LT_MASK)==LT_BOMB)
			if (weapon->LauncherType==LT_NAPALM)
				weapflags|=WEAP_NAP;
			else
				weapflags|=WEAP_BOMB;
	}
	int rv=PHRASE_WEAPONS+Weaplookup[weapflags];
	return SetWeap(rv);
}
const TargetIndexes& TargetIndexes::SetOneWeap(AirStruc *trg) const
{	//select any 1 weapon that is carried....
	UByte	weapflags=0;
	WeapAnimData*	weapon=NULL;										//RJS 29Aug96
	int index=0;
	SLong	xpos,ypos,zpos;
	UWord	mvel,mdelay,mburst;									//RDH 31Jul98
	if (trg->Anim==NULL)
	{
		assert (trg==Persons2::PlayerGhostAC);
		trg=Persons2::PlayerSeenAC;
	}
	while (index<6)
	{
		weapon = SHAPE.GetWeaponLauncher(trg,index++,xpos,ypos,zpos,mvel,mdelay,mburst);//RDH 31Jul98
		if (weapon->LoadedStores)
		if ((weapon->LauncherType&LT_MASK)==LT_BULLET)
			weapflags|=WEAP_GUNS;
		else
		if ((weapon->LauncherType&LT_MASK)==LT_ROCKET)
			weapflags|=WEAP_ROCK;
		else
		if ((weapon->LauncherType&LT_MASK)==LT_BOMB)
			if (weapon->LauncherType==LT_NAPALM)
				weapflags|=WEAP_NAP;
			else
				weapflags|=WEAP_BOMB;
	}
	for (int i=8;i;i=i>>1)
		breakif (weapflags&i);
	int rv=PHRASE_WEAPONS+Weaplookup[i];
	return SetWeap(rv);
}
const TargetIndexes & TargetIndexes::SetDir(ItemBasePtr from,ItemBasePtr delta) const
{
	int	diffX=delta->World.X-from->World.X;
	int	diffZ=delta->World.Z-from->World.Z;
	int posx=diffX;if(posx<0)posx=-posx;
	int posz=diffZ;if(posz<0)posz=-posz;
	if (posx>2*posz)
		if (diffX<0)
			return SetDir(PHRASE_W);
		else
			return SetDir(PHRASE_E);
	else
	if (posz>2*posx)
		if (diffZ<0)
			return SetDir(PHRASE_S);
		else
			return SetDir(PHRASE_N);
	else
		if (diffX<0)
			if (diffZ<0)
				return SetDir(PHRASE_SW);
			else
				return SetDir(PHRASE_SE);
		else
			if (diffZ<0)
				return SetDir(PHRASE_NW);
			else
				return SetDir(PHRASE_NE);
	
	return SetDir(PHRASE_OVER);
}
////////////////////////////////////////////////////////////////////////
//
// Function:    SendFACMessage
// Date:        04/03/99
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
void	AirStruc::SendFACMessage(PhaseFAC phase)
{
	char* tmpmsgtext="";
	TARGET_INDEXES tindex;
	if (Follower())
	switch	(phase)
	{
	case	FAC_REQUEST_LONGRANGE:
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MAKECONTACTWITHFAC, MSG_FACCONTACT_RPT, Follower(), Follower(), this,tindex.SetWeap(Follower())));
	}
	break;
	case	FAC_WELCOME_LONGRANGE:
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WELCOMELONGRANGE, MSG_FACCONTACT_RPT, Follower(), NULL, this));
	//intended fall through
	case	FAC_WAITRECONNECT:
		if 	(shape==T6)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FACMAKESCONTACT, MSG_FACCONTACT_RPT, this,this,Follower()));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FACMAKESCONTACT_OPT_1, MSG_FACCONTACT_RPT, this,this,Follower()));
	break;
	case	FAC_WELCOME_CLOSE:
	{
		if 	(shape==T6)
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WELCOMECLOSERANGE, MSG_FACCONTACT_RPT, Follower(), Follower(), this));
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WELCOMECLOSERANGEREPLY,MSG_FACCONTACT_RPT, this, this, Follower()));
			if (Follower()->ai.flyingskill&1)
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ROGER, (MsgType)(MSG_FACCONTACT_RPT+MSG_BLOCKCHATTER), Follower(),NULL,this));//RJS 06Jul99
		}
		else
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WELCOMECLOSERANGE_OPT_1, MSG_FACCONTACT_RPT, Follower(), Follower(), this));
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WELCOMECLOSERANGEREPLY_OPT_0,MSG_FACCONTACT_RPT, this, this, Follower()));
			if (Follower()->ai.flyingskill&1)
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ROGER, (MsgType)(MSG_FACCONTACT_RPT+MSG_BLOCKCHATTER), Follower(),NULL,this));//RJS 06Jul99
		}
	}
	break;
	case	FAC_DESCRIBETARGETS:
	{
		SupplyLine		*sl=SupplyTree::GetLineFromCallName(fly.callname);
		TeamDef			*team=sl->groundbattle.FindTeamAtLocation(ai.unfriendly->uniqueID.count);
		SuperBattleNode	*node=team->node;
		//else
		if (team->action==TeamDef::ATTACK)
		{
			tindex.SetType(team->forcetype+PHRASE_TROOPCOMPANY).SetName(node->mainids-IDS_PHRASE_TARGNAM+PHRASE_TARGNAM);
			tindex.SetDir(Persons2::ConvertPtrUID(node->mainuid),ai.unfriendly);
			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_DESCRIBETARGETATTACKING_OPT_0, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower(),tindex));
			//{CALLER, COMMA, CALLEE, STOP, YOURTARGET, TARGTYPE, STOP, ATTACKINGFROM,TARGDIR, TARGNAM)
		}
		else
		if (team->action==TeamDef::RETREAT_UNDER_FIRE)
		{
			tindex.SetMove(PHRASE_RETREATTHROUGH);
			tindex.SetType(team->forcetype+PHRASE_TROOPCOMPANY);
			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_DESCRIBETARGETATTACKING_OPT_1, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower(),tindex));
		}
		else
		if (team->action==TeamDef::MOVE_FORWARD || team->action==TeamDef::RETREAT)
		{
			if (node->in.occupier==team)
			{
				if (node->innerlink.redtransportmethodname)
					tindex.SetMove(node->innerlink.redtransportmethodname-IDS_PHRASE_TARGMOV+PHRASE_TARGMOV);
				else
					tindex.SetMove(PHRASE_ONROAD);	//PHRASE_ONMOVE
			}
			else
			{
				if (team->nextnode->innerlink.redtransportmethodname)
					tindex.SetMove(team->nextnode->innerlink.redtransportmethodname);
				else
					tindex.SetMove(PHRASE_ONROAD);	//PHRASE_ONMOVE
			}
			tindex.SetType(team->forcetype+PHRASE_TROOPCOMPANY);
			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_DESCRIBETARGETATTACKING_OPT_1, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower(),tindex));
			//{CALLER, COMMA, CALLEE, COMMA, YOURTARGET, TARGTYPE, TARGMOVE)
		}
		else
		//if (team->action==STAY_HERE)//default!
		{
			if (node->occupier==team)
			{
				tindex.SetType(team->forcetype+PHRASE_TROOPCOMPANY).SetName(node->mainids-IDS_PHRASE_TARGNAM+PHRASE_TARGNAM);
				//TARGET_INDEXES(type, name)));
				_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_DESCRIBETARGETAT, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower(),tindex));
			}
			else
			{
				tindex.SetType(team->forcetype+PHRASE_TROOPCOMPANY).SetName(node->mainids-IDS_PHRASE_TARGNAM+PHRASE_TARGNAM);
				tindex.SetDir(Persons2::ConvertPtrUID(node->mainuid),ai.unfriendly);
				_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_DESCRIBETARGETHOLD, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower(),tindex));
				//{CALLER, COMMA, CALLEE, STOP, YOURTARGET, TARGTYPE, STOP, MASSING,TARGDIR, TARGANM)
			}
		}	
	}
	break;
	case	FAC_HOMEFORCES:
	{
		SupplyLine		*sl=SupplyTree::GetLineFromCallName(fly.callname);
		TeamDef			*team=sl->groundbattle.FindTeamAtLocation(ai.unfriendly->uniqueID.count);
		SuperBattleNode	*node=team->node;
		TeamDef			*friends=NULL;
		if (node->occupier && node->occupier->team!=team->team)
			friends=node->occupier;
		else
		if (node->in.occupier && node->in.occupier->team!=team->team)
			friends=node->in.occupier;
		else
		if (node->out.occupier && node->out.occupier->team!=team->team)
			friends=node->out.occupier;
		if (friends)
		{
			if (friends->action==TeamDef::ATTACK)
			{
				tindex.SetName(node->mainids-IDS_PHRASE_TARGNAM+PHRASE_TARGNAM).SetDir(Persons2::ConvertPtrUID(node->mainuid),Persons2::ConvertPtrUID(friends->location));
				_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_DESCRIBEFRIENDATTACKING, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower(),tindex));
				//{CALLER, COMMA, CALLEE, STOP, FRIENDATTACKING, TARGDIR, TARGNAM, STOP, CAUTION)
			}
			else
				if (friends->action==TeamDef::RETREAT_UNDER_FIRE)
			{
				_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_DESCRIBEFRIENDRETREATING, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower()));
			}
			else
				if (friends->action==TeamDef::MOVE_FORWARD || friends->action==TeamDef::RETREAT)
			{
				_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_FAC_NOFRIENDS, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower()));
			}
			else
			//if (team->action==STAY_HERE)
			{

				tindex.SetName(node->mainids-IDS_PHRASE_TARGNAM+PHRASE_TARGNAM).SetDir(Persons2::ConvertPtrUID(node->mainuid),Persons2::ConvertPtrUID(friends->location));
				if (node->mainuid==friends->location)
					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_FRIENDLIESAT, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower(),tindex));
				else
					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_DESCRIBEFRIENDMASSING, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower(),tindex));
				//{CALLER, COMMA, CALLEE, STOP, FRIENDMASSING, TARGDIR, TARGNAM, STOP, CAUTION)
			}
		}
		else
		{
			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_FAC_NOFRIENDS, MSG_FACCONTACT_RPT, this, ai.unfriendly, Follower()));
		}

	}
	break;
	case	FAC_WATCHROCKETS:
	{	//need to handle TAC mortars
		if 	(shape==T6)		//FALSE for TAC in a truck. 
			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_WATCHROCKETS, MSG_FACCONTACT_RPT,this, ai.unfriendly, Follower()));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_WATCHMORTORS, MSG_FACCONTACT_RPT,this, ai.unfriendly, Follower()));
	}
	break;
	case	FAC_SEEMYSMOKE:
	{	//need to handle 'missed'
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SEESMOKE, MSG_FACCONTACT_RPT,this, ai.unfriendly, Follower()));
		//only if not player:
		if (!Follower()->AcIsPlayer())
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SEESMOKEREPLY, MSG_FACCONTACT_RPT, Follower(),NULL,this));
	}
	break;
	case	FAC_ADVISEATTACK:
	{	//any advice so long as it is less than current weapons....
		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_ADVISEATTACK, MSG_FACCONTACT_RPT, this,ai.unfriendly,Follower(),tindex.SetOneWeap(Follower())));
		//(CALLEE, STOP, ADVISEATTACK, WEAPONS)
		//only if not player
		if (!Follower()->AcIsPlayer())
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ADVISEATTACKREPLY, MSG_FACCONTACT_RPT, Follower(), NULL, this));
	}	
	break;
	case	FAC_ENOUGHHITS:
	{
		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_ENOUGHHITS, MSG_FACCONTACT_RPT,this,ai.unfriendly,Follower()));
	}
	break;
	case	FAC_MISSTIMEOUT:
	{
		//_Radio.	 this,ai.unfriendly,Follower()));
		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_MISSTIMEOUT, MSG_FACCONTACT_RPT,this,ai.unfriendly,Follower()));
	}
	break;
	case	FAC_HIT:
	{
		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_FAC_SAYS_HIT, MSG_FAC_SAYS_HIT,this,ai.unfriendly,Follower()));
	}
	break;	
	case	FAC_DAMAGE:
	{
		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_FAC_SAYS_DAMAGE, MSG_FAC_SAYS_DAMAGE,this,ai.unfriendly,Follower()));
	}
	break;
	case	FAC_HITFRIENDS:
	{
//DeadCode DAW 17Jun99 		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_FAC_CEASEFIRE, MSG_FAC_CEASEFIRE,this,ai.unfriendly,Follower()));
		_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_FAC_CEASEFIRE, MSG_FACCONTACT_RPT,this,ai.unfriendly,Follower()));
	}
	case	FAC_GOINGHOME:
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FACTOOHOT, MSG_FACCONTACT_RPT, this,ai.unfriendly,Follower()));
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOMORETARGETSREPLY, MSG_FACCONTACT_RPT,Follower(),NULL,this)); 
	}
	break;
	case	FAC_MORETARGETS:
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MORETARGETS, MSG_FACCONTACT_RPT, this,ai.unfriendly,Follower()));
	}
	break;
	case	FAC_NOMORETARGETS:
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOMORETARGETS, MSG_FACCONTACT_RPT, this,ai.unfriendly,Follower()));
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOMORETARGETSREPLY, MSG_FACCONTACT_RPT,Follower(),NULL,this)); 
	}
	break;
	//The following cases don't generate messages:
	//case	FAC_WAITRECONNECT:			
	case	FAC_TARGETAREARECONNECT:
	case	FAC_ROCKETEERRECONNECT:		case	FAC_WAIT:
	case	FAC_TARGETBMBCLOSER:		case	FAC_OBSERVING:
	case	FAC_TARGETAREA:				case	FAC_NEXTTARGASBOMBERCLIMBS:
	case	FAC_FLYTOAREA:				case	FAC_WINGWAGGLE:
	case	FAC_WAITCLOSER:				case	FAC_WAITTOUCHING:
	case	FAC_ROCKETEER:				case	FAC_GOINGIN:		
	case	FAC_CLIMBTOOBSERVE:			case	FAC_TARGETTOOCLOSE:
	INT3;
	break;
	}
//	Mono_Text.Print((UByte*)tmpmsgtext);
}

ItemPtr	AirStruc::CheckFACTarget(ItemBasePtr targ)
{
	ItemPtr unf=*ai.unfriendly;
	if (!unf || unf->SGT!=targ->uniqueID.count || unf->Status.deadtime)
	{
		UniqueID sgt=targ->uniqueID.count;
		for (int i=0;i<IllegalSepID;i++)
		{
			ItemBasePtr u1=Persons2::ConvertPtrUID(UniqueID(i));
			if (u1 && u1->Status.size>=ITEMSIZE && ItemPtr(*u1)->SGT==sgt)
				breakif((unf=*u1)->Status.deadtime!=0); //&& unf alive
		}
		if (unf)
			ai.unfriendly=unf;
	}
	return unf;
}

int	Item::FACReportDamage(bool waskill)
{
	UniqueID	thisSGT=SGT;
//	if (thisSGT)
//		for (t=*MobileItem::ACList;t;t=*t->nextmobile)
//			breakif(t->movecode==AUTO_FAC && t->waypoint->target->uniqueID.count==thisSGT);
//	if (t)
//	{
	TeamDef* team=NULL;
	int		line=0;
	for (line=0;SupplyTree::supplylines[line];line++)
	{
		team=SupplyTree::supplylines[line]->groundbattle.FindTeamAtLocation(thisSGT);
		breakif(team);
	}
//DeadCode CSB 01/07/99		assert(team);
	if (team)
	{
		if (waskill)
			if (team->lastlosses<team->MAX_LOSSES)
				team->lastlosses++;

		AirStrucPtr t=NULL;
		for (t=*MobileItem::ACList;t;t=*t->nextmobile)
			if (t->movecode==AUTO_FAC)
			breakif(	t->fly.callname==SupplyTree::supplylines[line]->TACcallname
					||	t->fly.callname==SupplyTree::supplylines[line]->FACcallname
					);
		if (t)
			if (	(SupplyTree::supplylines[line]->initiative==REDATTACKING)
				==	(team->team==TeamDef::AWAY)		)
				if (waskill)
					t->SendFACMessage(FAC_HIT);
				else
					t->SendFACMessage(FAC_DAMAGE);
			else
				t->SendFACMessage(FAC_HITFRIENDS);
		return team->forcetype;
	}
	else
		return	TeamDef::MAXFORCETYPES;
}

void	Item::FACReportGround()
{
	AirStrucPtr t=NULL;
	for (t=*MobileItem::ACList;t;t=*t->nextmobile)
		breakif(	t->movecode==AUTO_FAC 
		&&	t->ai.ManStep+FAC_ROCKETEER==FAC_OBSERVING
				&&	t->waypoint->action==wpengagetargetno
				)
	if (t && t->GetFACStage()==FAC_OBSERVING)
	{
		t->ai.ManStep=FAC_MISSTIMEOUT;
		t->SetManoeuvreTime(200);
	}
}

int	AirStruc::GetFACStage()
{
	int stage;
	if (waypoint->action==WP_waitfriendly)
		stage=FAC_WAIT;
	else if (waypoint->action==wpacircleno)
		stage=FAC_TARGETAREA;
	else if (waypoint->action==wpengagetargetno)
		stage=FAC_ROCKETEER;
	else
		stage=FAC_EXTRAS;
	stage+=ai.ManStep;
	return stage;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoFAC
//Author		Dave Whiteside
//Date			Tue 29 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AutoFAC ()
{	//what waypoint type are we on?
	//from that we can get the phase base incase it gets cleared accidentally
	//

	bool	airbased=(shape==T6);		//FALSE for TAC in a truck. 

	int stage=GetFACStage();

	//first the movement aspect
	Coords3D*	dp=NULL;
	if (airbased)
		switch	(stage)
		{
//Waiting waypoint
		case	FAC_EXTRAS:
		case	FAC_WAITRECONNECT:
		case	FAC_TARGETAREARECONNECT:
		case	FAC_ROCKETEERRECONNECT:
		case	FAC_WAIT:
		case	FAC_WELCOME_LONGRANGE:
		case	FAC_HOMEFORCES:
		case	FAC_TARGETBMBCLOSER:
		case	FAC_WATCHROCKETS:
		case	FAC_ADVISEATTACK:
		case	FAC_OBSERVING:
		case	FAC_MISSTIMEOUT:
		case	FAC_ENOUGHHITS:			//all these do the same circling manoeuvre
		{
			TimeLeft();	//decrement any timer that is going...
			InterceptandRange (dp=FindDesPos ());
			if (hdg-HdgIntercept+ANGLES_30Deg<<ANGLES_60Deg)
			{
				SWord LocalBestClimbPitch = CalcBestClimbPitch();
				if (Range>METRES3000 || PitchIntercept > (Angles)LocalBestClimbPitch) //JIM 30/06/99
				 	PitchIntercept = (Angles)LocalBestClimbPitch;
			}
			else
			{
				if (Range>METRES2000 && PitchIntercept>ANGLES_330Deg)
				 	PitchIntercept = ANGLES_2Deg;					  //JIM 30/06/99
				else
					PitchIntercept=ANGLES_0Deg;									//go for a flatish turn
			}
			CalcVelAlt();	//fly to circle target

			AutoOrbit(*dp,METRES1200);

			AutoCalcPitch ();
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();
		}
		break;
//Target area waypoint												  //DAW 01/07/99
		case	FAC_TARGETAREA:
		case	FAC_NEXTTARGASBOMBERCLIMBS:
		case	FAC_NOMORETARGETS:
		case	FAC_DESCRIBETARGETS:
		case	FAC_FLYTOAREA:
		{
			TimeLeft();	//decrement any timer that is going...
			InterceptandRange (dp=FindDesPos ());
			if (hdg-HdgIntercept+ANGLES_30Deg<<ANGLES_60Deg)
			{
				SWord LocalBestClimbPitch = CalcBestClimbPitch();
				if (World.Y-dp->Y>METRES1000)
					if (Range>METRES4000 || PitchIntercept > (Angles)LocalBestClimbPitch) //JIM 30/06/99
				 		PitchIntercept = (Angles)LocalBestClimbPitch;
			}
			else
			{
				if (Range>METRES4000 && PitchIntercept>ANGLES_330Deg)
				 	PitchIntercept = ANGLES_2Deg;					  //JIM 30/06/99
//DeadCode AMM 05Jul99 				else
//DeadCode AMM 05Jul99 					PitchIntercept=ANGLES_0Deg;									//go for a flatish turn
			}
			CalcVelAlt();
			CalcHdgRollLimited();	//note: fly straight to target!

			AutoCalcPitch ();
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();
		}
		break;
		case	FAC_WINGWAGGLE:			//fly towards friendlies and waggle wings

		case	FAC_WAITCLOSER:
		case	FAC_WELCOME_CLOSE:
		case	FAC_WAITTOUCHING:		//all these fly towards the friendlies - held in 'unfriendly'
		{
			InterceptandRange (dp=&follower->World);
			SWord reqdeltahdg = 	(SWord) (hdg - HdgIntercept);
			if (stage==FAC_WINGWAGGLE)
			{
				if (TimeLeft()&64)
				   reqdeltahdg+=ANGLES_20Deg;
				else
				   reqdeltahdg-=ANGLES_20Deg;
			}
			else
				TimeLeft();
			if (Range>METRES2000 && PitchIntercept>ANGLES_330Deg)
				PitchIntercept = ANGLES_10Deg;					  //JIM 30/06/99
			else
				PitchIntercept=ANGLES_0Deg;									//go for a flatish turn
			CalcVelAlt();	//CSB 29/09/98	//This takes altitude into account
			CalcHdgRollLimited(reqdeltahdg);	//but try harder if too far away!
			AutoCalcPitch ();	//speed is not significantly affected by the roll angle
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();
		}

		break;

		case	FAC_TARGETTOOCLOSE:
		{
			TimeLeft();
			ItemPtr	unf=CheckFACTarget(waypoint->next->target);
			if (!unf)
			{
				assert(unf);
				//move on to next target...
				NextWayPoint();
				NextWayPoint();
				stage=FAC_DESCRIBETARGETS;
			}
			else
				InterceptandRange (dp=&unf->World);
			Angles reqdeltahdg=ANGLES_0Deg;
			if (HdgIntercept-hdg+ANGLES_90Deg<<ANGLES_180Deg)
				reqdeltahdg=ANGLES_15Deg;
			else
				reqdeltahdg=reqdeltahdg;
			PitchIntercept=ANGLES_1Deg;									//go for a flatish turn
			CalcVelAlt();	//CSB 29/09/98	//This takes altitude into account
			CalcHdgRollLimited(reqdeltahdg);	//but try harder if too far away!
			AutoCalcPitch ();	//speed is not significantly affected by the roll angle
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();
		}
		break;
//Target waypoint
		case	FAC_ROCKETEER:
		case	FAC_GOINGIN:
		case	FAC_SEEMYSMOKE:			//diving attack
		{
			ItemPtr	unf=CheckFACTarget(waypoint->target);
			if (!unf)
			{
				assert(unf);
				//move on to next target...
				NextWayPoint();
				stage=FAC_DESCRIBETARGETS;
			}
			else
				InterceptandRange (dp=&unf->World);
			if (PitchIntercept>ANGLES_315Deg)
				if (PitchIntercept<ANGLES_0Deg)
					PitchIntercept=ANGLES_5Deg;
				else
					PitchIntercept=PitchIntercept+ANGLES_30Deg;
			else
			if (Range>METRES800)
			{
				if (Range<METRES3000)
					if (Range<METRES1000)
						PitchIntercept=PitchIntercept+ANGLES_2Deg;
					else
						PitchIntercept=PitchIntercept+ANGLES_10Deg;
				else
					if (PitchIntercept<ANGLES_0Deg)
						PitchIntercept=ANGLES_5Deg;
					else
						PitchIntercept=PitchIntercept+ANGLES_30Deg;
			}
			else
				PitchIntercept=PitchIntercept;
			TimeLeft();
			CalcVelAlt();	//CSB 29/09/98	//This takes altitude into account
			CalcHdgRollLimited();	//but try harder if too far away!
			AutoCalcPitch ();	//speed is not significantly affected by the roll angle
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();
		}
		break;
		case	FAC_CLIMBTOOBSERVE:		//pull up and out
			if (pitch<ANGLES_0Deg)
				HdgIntercept=ANGLES_0Deg;
			else
			{
				HdgIntercept=Angles(ANGLES_10Deg+Range/METRES200);
				InterceptandRange (dp=FindDesPos ());
			}
			PitchIntercept=ANGLES_20Deg;									//go for a flatish turn
			CalcVelAlt();	//CSB 29/09/98	//This takes altitude into account
			CalcHdgRollLimited(HdgIntercept);	//but try harder if too far away!
			AutoCalcPitch ();	//speed is not significantly affected by the roll angle
			AutoCalcPitch ();	//speed is not significantly affected by the roll angle
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();
		break;
		}
	else
	{	/*TAC doesn't actually animate, just teleports*/ 
		if (!TimeLeft())
		{
			Range=0;
			uniqueID.changed=TRUE;

			switch	(stage)
			{
			case	FAC_WAITRECONNECT:
			case	FAC_TARGETAREARECONNECT:
	
			case	FAC_WAIT:
			case	FAC_WELCOME_LONGRANGE:

			case	FAC_HOMEFORCES:

			case	FAC_TARGETBMBCLOSER:
			case	FAC_WATCHROCKETS:
			{
				dp=FindDesPos ();
				World=*dp;
			}
			break;
			case	FAC_TARGETAREA:
			case	FAC_NEXTTARGASBOMBERCLIMBS:
			case	FAC_DESCRIBETARGETS:
			case	FAC_FLYTOAREA:
			{
				dp=FindDesPos ();
				World=*dp;
			}
			break;
			case	FAC_WINGWAGGLE:			//fly towards friendlies and waggle wings

			case	FAC_WAITCLOSER:
			case	FAC_WELCOME_CLOSE:
			case	FAC_WAITTOUCHING:		//all these fly towards the friendlies - held in 'unfriendly'
			{
				dp=FindDesPos ();
				Range=0;
				World=*dp;
			}
			break;
			case	FAC_TARGETTOOCLOSE:
			{
				dp=FindDesPos ();
				World=*dp;
			}
			break;
			case	FAC_ROCKETEER:
			case	FAC_ROCKETEERRECONNECT:
			case	FAC_GOINGIN:
			case	FAC_SEEMYSMOKE:			//diving attack
			case	FAC_CLIMBTOOBSERVE:		//pull up and out
			case	FAC_ADVISEATTACK:
			case	FAC_OBSERVING:
			case	FAC_MISSTIMEOUT:
			case	FAC_ENOUGHHITS:			//all these do the same circling manoeuvre
			{	//do nothing!!
				dp=FindDesPos ();
//DeadCode AMM 05Jul99 				World=*dp;
			}
			break;
			}
		}
	}
	
	//decision making
	if (manoeuvretime==0)
		switch	(stage)
		{
//Waiting waypoint
		case	FAC_WAITRECONNECT:
		case	FAC_TARGETAREARECONNECT:
		case	FAC_ROCKETEERRECONNECT:
		case	FAC_WAIT:
		//find nearby friendly...
		{
			int x=World.X,y=World.Y;							//DAW 04May99
			AirStrucPtr t=Follower();
//TEMPCODE MS 04/05/99 //FAC can only handlde CAS going through CAS waypoint!
//DeadCode DAW 04May99 			if (!t)
//DeadCode DAW 04May99 			for (t=*ACList;t;t=*t->nextmobile)
//DeadCode DAW 04May99 				if (t->nationality==nationality && t!=this && !t->leader)
//DeadCode DAW 04May99 					if (Math_Lib.DistAbsSum(x-t->World.X,y-t->World.Y)<MILES05)
//DeadCode DAW 04May99 						if (!Math_Lib.rnd(4))
//DeadCode DAW 04May99 							break;
			if (t)	//clear t if we decide not to go for it!
			{
				if (t->leader)
					t=*t->leader;
				while (t->fly.leadflight)
					t=t->fly.leadflight;
				InterceptandRange (dp=&t->World);
				if (Range>MILES05)
				{
					t->InterceptandRange (dp=FindDesPos ());
					if (Range<MILES03)
					{
						follower=t;
						if (stage==FAC_WAIT)
							stage=FAC_WINGWAGGLE;
					}
					else
						if (stage==FAC_WAIT)
							stage=FAC_WAITCLOSER;
						
					SendFACMessage(FAC_WELCOME_LONGRANGE);
					SetManoeuvreTime(500);
				}
				else
				{
					follower=t;
					SendFACMessage(FAC_WELCOME_CLOSE);
					switch (stage)
					{
					case	FAC_TARGETAREARECONNECT:	stage=FAC_TARGETAREA;	break;
					case	FAC_ROCKETEERRECONNECT:		stage=FAC_WATCHROCKETS; break;
					case	FAC_WAITRECONNECT:
					case	FAC_WAIT:					stage=FAC_WAITTOUCHING;	break;
					}
				   SetManoeuvreTime(1000);

				}
			}

			if (!t)
			   SetManoeuvreTime(500);
		}
		break;

		case	FAC_WELCOME_LONGRANGE:
		case	FAC_WINGWAGGLE:
			stage=FAC_WAITCLOSER;
		   SetManoeuvreTime(100);
		break;

		case	FAC_WAITCLOSER:
		{
			AirStrucPtr	t=*follower;
			InterceptandRange (dp=&t->World);
			if (Range<MILES03)
			{
				stage=FAC_WAITTOUCHING;
				SendFACMessage(FAC_WELCOME_CLOSE);
			   SetManoeuvreTime(500);
			}
			else
			   SetManoeuvreTime(300);
		}
		break;
		case	FAC_WELCOME_CLOSE:				//shouldn't happen...

		case	FAC_WAITTOUCHING:
		{
			NextWayPoint();
			NextWayPoint();
			ai.unfriendly=waypoint->next->target;
			stage=FAC_TARGETAREA;
		}
		break;
//target area waypoint
		case	FAC_TARGETAREA:					//shouldn't happen...

		case	FAC_NEXTTARGASBOMBERCLIMBS:
		{
////TEMPCODE JIM 30/03/99 			AirStrucPtr	t;
////TEMPCODE JIM 30/03/99 			bool	allready=true;	
////TEMPCODE JIM 30/03/99 			for (t=*follower;t;t=t->fly.nextflight)
////TEMPCODE JIM 30/03/99 				for (AirStrucPtr w=t;w;w=*w->follower)
////TEMPCODE JIM 30/03/99 					if (w->movecode!=AUTO_FOLLOWWP)
////TEMPCODE JIM 30/03/99 						allready=false;
////TEMPCODE JIM 30/03/99 
////TEMPCODE JIM 30/03/99 			if (allready)
			if (!Follower()->ai.unfriendly || Follower()->ai.unfriendly==this)
			{
				//Only set player's unfriendly here...
				stage=FAC_DESCRIBETARGETS;
//DeadCode RDH 06Jul99 				ItemPtr trg=CheckFACTarget(waypoint->next->target);
//DeadCode RDH 06Jul99 				if (trg)
//DeadCode RDH 06Jul99 				{
//DeadCode RDH 06Jul99 					UniqueID SGT=trg->SGT;
//DeadCode RDH 06Jul99 					for (AirStrucPtr fllead=Follower();fllead;fllead=fllead->fly.nextflight)
//DeadCode RDH 06Jul99 						for (AirStrucPtr follower=fllead;follower;follower=follower->Follower())
//DeadCode RDH 06Jul99 							if (follower==Persons2::PlayerGhostAC)
//DeadCode RDH 06Jul99 							{
//DeadCode RDH 06Jul99 								if (!follower->ai.unfriendly || follower->ai.unfriendly->SGT!=SGT)
//DeadCode RDH 06Jul99 									follower->ai.unfriendly=trg;
//DeadCode RDH 06Jul99 							}
//DeadCode RDH 06Jul99 				}
//DeadCode RDH 06Jul99 				ai.unfriendly=waypoint->next->target;
			}
			else
				SetManoeuvreTime(100);
		}
		break;
		case	FAC_DESCRIBETARGETS:
		{
			ItemPtr trg=CheckFACTarget(waypoint->next->target);
			if (trg)
			{
				UniqueID SGT=trg->SGT;
				for (AirStrucPtr fllead=Follower();fllead;fllead=fllead->fly.nextflight)
					for (AirStrucPtr follower=fllead;follower;follower=follower->Follower())
						if (follower==Persons2::PlayerGhostAC)
						{
							if (!follower->ai.unfriendly || follower->ai.unfriendly->SGT!=SGT)
								follower->ai.unfriendly=trg;
						}
			}
			ai.unfriendly=waypoint->next->target;
			SendFACMessage(FAC_DESCRIBETARGETS);
			SetManoeuvreTime(20*SECS100);
			stage=FAC_FLYTOAREA;
		}
		break;
		case	FAC_FLYTOAREA:
			if (Range<METRES3000)
			{
				SendFACMessage(FAC_HOMEFORCES);
				stage=FAC_TARGETBMBCLOSER;
				SetManoeuvreTime(8*SECS100);
			}
			else
				if (Range>METRES4000)
					SetManoeuvreTime(100);
		break;

		case	FAC_HOMEFORCES:			//shouldn't happen...

		case	FAC_TARGETTOOCLOSE:
		{
				ItemPtr	unf=CheckFACTarget(waypoint->next->target);
				if (!unf)
				{
					assert(unf);
					//move on to next target...
					NextWayPoint();
					NextWayPoint();
					stage=FAC_DESCRIBETARGETS;
				}
				else
				{
					InterceptandRange (dp=&unf->World);
					int	dhdg_a=Math_Lib.AbsSign(hdg-HdgIntercept)&0x3fff;
					dhdg_a*=6;	//2000m in 180deg

					if (	Range>METRES3000
						||	Range>METRES2000+dhdg_a
						)
					{
						SendFACMessage(FAC_WATCHROCKETS);
						NextWayPoint();
						stage=FAC_ROCKETEER;
					}
					else
						SetManoeuvreTime(100);
				}
		}
		break;														  //JIM 08/07/99

		case	FAC_TARGETBMBCLOSER:
		{
			AirStrucPtr	t=*follower;
			InterceptandRange (dp=&t->World);
			if (Range<METRES2000 || PitchIntercept>ANGLES_45Deg)
			{
				ItemPtr	unf=CheckFACTarget(waypoint->next->target);
				if (!unf)
				{
					assert(unf);
					//move on to next target...	SayAndQuit
					NextWayPoint();
					NextWayPoint();
					stage=FAC_DESCRIBETARGETS;
				}
				else
				{
					InterceptandRange (dp=&unf->World);
					int	dhdg_a=Math_Lib.AbsSign(hdg-HdgIntercept);
					dhdg_a*=6;	//2000m in 180deg

					if (!airbased
						|| 	Range>METRES3000 ||	Range>METRES2000+dhdg_a
						)
					{
						SendFACMessage(FAC_WATCHROCKETS);
						NextWayPoint();
						stage=FAC_ROCKETEER;
						SetManoeuvreTime(500);
					}
					else
						stage=FAC_TARGETTOOCLOSE;
				}
			}
			else
				if (Range>METRES3000)
					SetManoeuvreTime(50);
		}
		break;
		case	FAC_WATCHROCKETS:			//shouldn't happen...
//target waypoint
		case	FAC_ROCKETEER:
		case	FAC_GOINGIN:
		{

			ItemPtr	unf=CheckFACTarget(waypoint->target);
			if (!unf)
			{
				assert(unf);
				//move on to next target...	SayAndQuit
				NextWayPoint();
				NextWayPoint();
				stage=FAC_DESCRIBETARGETS;
			}
			else
			{
				InterceptandRange (dp=&unf->World);
			}
			int muzzelvel=3000;	//200m/s

			if (!airbased)
			{
				PitchIntercept=ANGLES_45Deg;	//shoot upwards
				SWord velh=muzzelvel/4;
				int time10=Range/velh;
				Coords3D	world=this->World;
				world.Y+=METRES05;
				int deltah=unf->World.Y-world.Y;
				SWord vely=(deltah/time10+5*time10);
				SWord	sh,ch;
				Math_Lib.high_sin_cos(HdgIntercept,sh,ch);
				SWord	vx=(sh*velh)>>ANGLES_SHIFT,
						vz=(ch*velh)>>ANGLES_SHIFT;

				Trans_Obj.LaunchUnguidedMissile
						(	this,
							SPARK,
							100*SECS100,
							MOBILE_FLARE,
							world,
							HdgIntercept,
							PitchIntercept,
							vx,vely,vz,velh,muzzelvel,NAT_BLUE	);

				SendFACMessage(FAC_SEEMYSMOKE);
				stage=FAC_CLIMBTOOBSERVE;
				SetManoeuvreTime(10*SECS100);
			}
			else
			if (Range<METRES300)
			{	//fire a rocket!
				SendFACMessage(FAC_SEEMYSMOKE);
				stage=FAC_CLIMBTOOBSERVE;
				SWord	sp,cp;
				Math_Lib.high_sin_cos(PitchIntercept,sp,cp);
				SWord	sh,ch;
				Math_Lib.high_sin_cos(HdgIntercept,sh,ch);

				SWord	vy=(sp*muzzelvel)>>ANGLES_SHIFT,
						vh=(cp*muzzelvel)>>ANGLES_SHIFT,
						vx=(sh*vh)>>ANGLES_SHIFT,
						vz=(ch*vh)>>ANGLES_SHIFT;
					
				Trans_Obj.LaunchUnguidedMissile
						(	this,
							SPARK,
							10*SECS100,
							MOBILE_FLARE,
							this->World,
							HdgIntercept,
							PitchIntercept,
							vx,vy,vz,vh,muzzelvel,NAT_BLUE	);
			}
		}
		break;
		case	FAC_SEEMYSMOKE:			//shouldn't happen...

		case	FAC_CLIMBTOOBSERVE:
		{
			if (dp)
			{
				if (!airbased || World.Y-dp->Y>-METRES100)
				{
					SendFACMessage(FAC_ADVISEATTACK);
					stage=FAC_OBSERVING;
					//Start auto aircraft attacks
					ItemPtr	trg=CheckFACTarget(waypoint->target);
					UniqueID SGT=trg->SGT;
					assert(SGT&&"No SGT in FAC target");
					for (AirStrucPtr fllead=Follower();fllead;fllead=fllead->fly.nextflight)
						for (AirStrucPtr follower=fllead;follower;follower=follower->Follower())
						{
							if (!follower->ai.unfriendly || follower->ai.unfriendly->SGT!=SGT)
							{
								follower->ai.unfriendly=trg;
								follower->ai.ManStep=0;
							}
							else
								if (follower->ai.ManStep==15)
									follower->ai.ManStep=0;
						}

					if (!airbased)
						SetManoeuvreTime(40*SECS100);
				}
			}

		}
		break;
		case	FAC_ADVISEATTACK:			//shouldn't happen...
		case	FAC_OBSERVING:
		{
			ItemPtr	unf=CheckFACTarget(waypoint->target);
			if (unf)
			{
				UniqueID targSGT=unf->SGT;
				TeamDef* team=NULL;
				for (int line=0;SupplyTree::supplylines[line];line++)
				{
					team=SupplyTree::supplylines[line]->groundbattle.FindTeamAtLocation(targSGT);
					breakif(team);
				}
				assert(team);
				int numkills=team->lastlosses;
				int maxkills=team->strength/50;
				if (numkills>=maxkills || numkills*8>team->MAX_LOSSES*3+Math_Lib.rnd(150))
					unf=NULL;
			}
			if (!unf)
			{
				SendFACMessage(FAC_ENOUGHHITS);
				NextWayPoint();
				for (AirStrucPtr fllead=Follower();fllead;fllead=fllead->fly.nextflight)
					for (AirStrucPtr follower=fllead;follower;follower=follower->Follower())
						if (follower->ai.unfriendly!=this)
						{
							follower->ai.ManStep=CASMANSTEP(FAC_ROCKETEER);
							follower->ai.unfriendly=NULL;
						}
				Follower()->ai.unfriendly=this;
				if (waypoint->action==wpstoploopchkno)
					stage=FAC_NOMORETARGETS;
				else
					stage=FAC_NEXTTARGASBOMBERCLIMBS;
			}
			else
				SetManoeuvreTime(500);
		}
		break;
		case	FAC_NOMORETARGETS:
		{
////TEMPCODE JIM 30/03/99 			AirStrucPtr	t;
////TEMPCODE JIM 30/03/99 			bool	allready=true;	
////TEMPCODE JIM 30/03/99 			for (t=*follower;t;t=t->fly.nextflight)
////TEMPCODE JIM 30/03/99 				for (AirStrucPtr w=t;w;w=*w->follower)
////TEMPCODE JIM 30/03/99 					if (w->movecode!=AUTO_FOLLOWWP)
////TEMPCODE JIM 30/03/99 						allready=false;
////TEMPCODE JIM 30/03/99 
////TEMPCODE JIM 30/03/99 			if (allready)
			if (!Follower()->ai.unfriendly || Follower()->ai.unfriendly==this)
			{
				SendFACMessage(FAC_NOMORETARGETS);
				stage=FAC_EXTRAS;
			}
			else
				SetManoeuvreTime(100);
		}
		break;
		case	FAC_MISSTIMEOUT:
		{
			SendFACMessage(FAC_MISSTIMEOUT);
			stage=FAC_OBSERVING;
		}
		case	FAC_ENOUGHHITS:			//shouldn't happen...
			;
		}
	ai.ManStep=stage&FAC_SUBSTAGEMASK;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlyEscortTo
//Author		Jim 
//Date			Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStrucPtr	AirStruc::FlyEscortTo()
{
///	if (	(fly.leadflight || formpos) &&	//don't remember why...

//DeadCode CSB 20/04/99		AirStrucPtr candidate=NULL;
//DeadCode CSB 20/04/99		if (leader)
//DeadCode CSB 20/04/99			candidate=Leader();
//DeadCode CSB 20/04/99		else
//DeadCode CSB 20/04/99		if (position()==2)
//DeadCode CSB 20/04/99			candidate=fly.leadelt();
//DeadCode CSB 20/04/99		else if (fly.leadflight)
//DeadCode CSB 20/04/99		{
//DeadCode CSB 20/04/99			candidate=fly.leadflight;
//DeadCode CSB 20/04/99			if (formpos==0)
//DeadCode CSB 20/04/99			{	//flying as escorter. Get range to escortee and waypoint.
//DeadCode CSB 20/04/99				//If waypoint within 30 miles or escortee within 50 miles fly to escortee.
//DeadCode CSB 20/04/99				if (Distance3D (FindDesPos())>MILES30+desposrange)
//DeadCode CSB 20/04/99					if (Distance3D(&candidate->World)>MILES30)
//DeadCode CSB 20/04/99						candidate=NULL;
//DeadCode CSB 20/04/99			}
//DeadCode CSB 20/04/99		}

	AirStrucPtr candidate=NULL;
	candidate = FindLeadCandidate();

	if (candidate)
		if (candidate->waypoint==waypoint)
			if (movecode==AUTO_TELLLEADER || movecode==candidate->movecode)
				return candidate;
	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindLeadCandidate
//Author		Craig Beeston 
//Date			20 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStrucPtr	AirStruc::FindLeadCandidate()
{
///	if (	(fly.leadflight || formpos) &&	//don't remember why...
	AirStrucPtr candidate=NULL;
	if (leader)
		candidate=Leader();
	else
	if (position()==2)
		candidate=fly.leadelt();
	else if (fly.leadflight)
	{
		candidate=fly.leadflight;
		if (formpos==0)
		{	//flying as escorter. Get range to escortee and waypoint.
			//If waypoint within 30 miles or escortee within 50 miles fly to escortee.
			if (Distance3D (FindDesPos())>MILES30+desposrange)
				if (Distance3D(&candidate->World)>MILES30)
					candidate=NULL;
		}
	}

	return candidate;
}



//////////////////////////////////////////////////////////////////////
//
// Function:    AutoFollowWp
// Date:		18/04/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void AirStruc::AutoFollowWp ()

{
	SWord flightpos = position();
	if (!waypoint)
	{
		ItemBasePtr trg=ai.homebase;
		if (World.Z-trg->World.Z<METRES20KM && trg->uniqueID.count!=UID_Japan)
		{	//each pilot is 0.2 m/s slower over 18000m at 250m/s = 72 seconds= 14.4 metres
//DEADCODE DAW 27/04/99 		UByteP(0xB0000)[2*uniqueID.count&0xfff]=manoeuvretime?'f':'F';
			if (!TimeLeft())
			{
				despos=trg->World;
				despos.Y+=METRES800;
				InterceptandRange (&despos);
				SWord dVel, dHdg, dPitch;
				WindTrackCorrection(vel, HdgIntercept, PitchIntercept, dVel, dHdg, dPitch);
				HdgIntercept   += dHdg;
				PitchIntercept += dPitch;
				Bool	level=(Bool)(Range>MILES01);
				SWord LocalBestClimbPitch = CalcBestClimbPitch();
				if (PitchIntercept > (Angles)LocalBestClimbPitch)
				{
			 		PitchIntercept = (Angles)LocalBestClimbPitch;
				}
				if (nationality==NAT_RED)
					level&=CalcVelAlt(classtype->cruisevel+50-(formpos&InFormMAX)*10-(formpos&InWingMAX));
				else
					level&=CalcVelAlt(classtype->cruisevel+50-ai.pilotnum*2);
				level&=CalcHdgRollLimited ();
				level&=AutoCalcPitch ();
				CalcXYZVel();
				if (level && Range>METRES4000)
				{	//1000 metres at 300m/s = 3 seconds!!!!
					SetManoeuvreTime(6*SECS100);
				}
				else
					if (Range<METRES2000)
						ExecuteWayPointAction ();						//JIM 03Jul96
			}													//JIM 03Jul96
			NewPosition ();
			SetFlightParams ();
			return;													  //JIM 05/03/99
		}
	}
	AirStrucPtr MyLeader;
	if(MyLeader = FlyEscortTo())
	{
//DEADCODE DAW 27/04/99 		UByteP(0xB0000)[2*uniqueID.count&0xfff]=information?roll?'r':'i':manoeuvretime?'t':'c';
		AutoFollowWpWing (MyLeader);
	}
	else
	{

//DeadCode CSB 01/06/99			if(	   (fly.pModel->Type == AT_F86E) || (fly.pModel->Type == AT_F80C) 
//DeadCode CSB 01/06/99				|| (fly.pModel->Type == AT_F84E) || (fly.pModel->Type == AT_F51D) )
//DeadCode CSB 01/06/99			{
//DeadCode CSB 01/06/99				PrintVar(0, 5, "Pitch   %.1f ", FP(pitch / 182.0));
//DeadCode CSB 01/06/99				PrintVar(0, 6, "Vel     %.1f ", FP(vel / 10.0));
//DeadCode CSB 01/06/99				PrintVar(0, 7, "ROC     %.1f ", FP(vely / 10.0));
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99				if(slowdownleader)
//DeadCode CSB 01/06/99					PrintString(0, 9, "SLOW DOWN");
//DeadCode CSB 01/06/99				else
//DeadCode CSB 01/06/99					PrintString(0, 9, "         ");
//DeadCode CSB 01/06/99				PrintVar(0, 12, "Frame   %.0f ", FP(fly.pModel->FrameCount));
//DeadCode CSB 01/06/99			}



//DEADCODE DAW 27/04/99 		UByteP(0xB0000)[2*uniqueID.count&0xfff]=information?'I':manoeuvretime?'T':'C';
		if	(!TimeLeft())
		{

//DeadCode CSB 18/06/99	/* TEST CODE CSB 14/06/99 */	PrintVar( 0, 23, "Time %.0f ", FP(int(timeofday / (100 * 60 * 60))));
//DeadCode CSB 18/06/99	/* TEST CODE CSB 14/06/99 */	PrintVar( 8, 23, ":%.0f ", FP(int(timeofday / (100 * 60)) - 60 * int(timeofday / (100 * 60 * 60))));
//DeadCode CSB 18/06/99	/* TEST CODE CSB 14/06/99 */	PrintVar(11, 23, ":%.0f ", FP(int(timeofday / (100)) - 60 * int(timeofday / (100 * 60))));

//DeadCode DAW 06Nov96 			((char*)0xB0000)[20]++;
			Coords3D*	dp;
			InterceptandRange (dp=FindDesPos ());
			SWord dVel, dHdg, dPitch;
			WindTrackCorrection(vel, HdgIntercept, PitchIntercept, dVel, dHdg, dPitch);
			HdgIntercept   += dHdg;
			PitchIntercept += dPitch;

			Bool	level=FALSE;//(Bool)(Range>MILES01);				//JIM 21Oct96
//DeadCode DAW 26Mar99 			Bool	level=(Bool)(Range>MILES01);				//JIM 21Oct96


//DeadCode CSB 06/04/99	if((classtype->visible == B26) || (classtype->visible == B29))
//DeadCode CSB 06/04/99	{
//DeadCode CSB 06/04/99	PrintString(30, 5, "HEAVY BOMBERS");
//DeadCode CSB 06/04/99	PrintVar(30,  7, "WayPoint Number  %.0f ", (FP)(waypoint->wpname));
//DeadCode CSB 06/04/99	PrintVar(30,  8, "WayPoint Height  %.0f ", (FP)(waypoint->World.Y / 100));
//DeadCode CSB 06/04/99	PrintVar(30,  9, "WayPoint Action  %.0f ", (FP)(waypoint->action));
//DeadCode CSB 06/04/99	PrintVar(30, 10, "WayPoint Bearing %.1f ", (FP)((HdgIntercept - hdg) / 182.04));
//DeadCode CSB 06/04/99	PrintVar(30, 11, "WayPoint Range   %.0fm ", (FP)(Range / 100));
//DeadCode CSB 06/04/99	}
//DeadCode CSB 06/04/99	else if(classtype->visible != MIG15) 
//DeadCode CSB 06/04/99	{
//DeadCode CSB 06/04/99	PrintVar(0,  7, "WayPoint Number  %.0f ", (FP)(waypoint->wpname));
//DeadCode CSB 06/04/99	PrintVar(0,  8, "WayPoint Height  %.0f ", (FP)(waypoint->World.Y / 100));
//DeadCode CSB 06/04/99	PrintVar(0,  9, "WayPoint Action  %.0f ", (FP)(waypoint->action));
//DeadCode CSB 06/04/99	PrintVar(0, 10, "WayPoint Bearing %.1f ", (FP)((HdgIntercept - hdg) / 182.04));
//DeadCode CSB 06/04/99	PrintVar(0, 11, "WayPoint Range   %.0fm ", (FP)(Range / 100));
//DeadCode CSB 06/04/99	}

			
			SWord LocalBestClimbPitch = CalcBestClimbPitch();	//CSB 28/09/98
//DeadCode CSB 28/09/98				SLong	LocalBestClimbVel   = CalcBestClimbSpeed(World.Y);		//CSB 28/09/98
			
			
//best climb is at classtype->bestclimbpitch and classtype->bestclimbvel//RDH 26Jul96
//DeadCode CSB 28/09/98				if (PitchIntercept>classtype->bestclimbpitch)//RDH 26Jul96
			if (PitchIntercept > (Angles)LocalBestClimbPitch)	//CSB 28/09/98
			{													//JIM 05Jul96
			 	PitchIntercept = (Angles)LocalBestClimbPitch;		//RDH 26Jul96
				Range-=dp->Y-World.Y;						//JIM 05Jul96
			}													//JIM 05Jul96


			if (Range > MILES01)
			{
				level=TRUE;
//DeadCode CSB 28/09/98					if ( PitchIntercept << classtype->bestclimbpitch)//RDH 26Jul96
				if ( PitchIntercept << (Angles)LocalBestClimbPitch)//CSB 28/09/98
				{
					UWord MinVel = CalcBestClimbSpeed();
					if(slowdownleader) MinVel -= 250;
					if(vel >= MinVel)
						PitchIntercept = (Angles)LocalBestClimbPitch;	//RDH 26Jul96

//DeadCode CSB 02/06/99						if(	   (fly.pModel->Type == AT_F86E) || (fly.pModel->Type == AT_F80C) 
//DeadCode CSB 02/06/99							|| (fly.pModel->Type == AT_F84E) || (fly.pModel->Type == AT_F51D) )
//DeadCode CSB 02/06/99							if(vel >= MinVel)
//DeadCode CSB 02/06/99								PrintString(0, 10, "Best Pitch");
//DeadCode CSB 02/06/99							else
//DeadCode CSB 02/06/99								PrintString(0, 10, "          ");

				}
			}		
			else
			{	//travelling away from WP and within 1 mile
				//level out and hopefully get a despos push
				if (((hdg-HdgIntercept)-ANGLES_90Deg)<<ANGLES_180Deg)
				{
					HdgIntercept=hdg;
					PitchIntercept=ANGLES_0Deg;
					level=TRUE;
					if (desposrange<Range)
						Range=desposrange+MILES05;
				}

			}


//DeadCode CSB 29/09/98				level&=CalcVel ();							//JIM 21Oct96
//DeadCode CSB 29/09/98				level&=CalcHdgRoll ();
			level&=CalcVelAlt();	//CSB 29/09/98	//This takes altitude into account

/* TEST CODE CSB 08/06/99 */			
/* TEST CODE CSB 08/06/99 */			
/* TEST CODE CSB 08/06/99 */
/*
			FP DistX  = World.X - ai.homebase->World.X;
			FP DistZ  = World.Z - ai.homebase->World.Z;
			FP Dist2D = FSqrt(DistX * DistX + DistZ * DistZ);

			switch(classtype->visible)
			{
				case F86:
					PrintVar( 0,  5, "F86  Pitch %.1f ", FP(pitch / 182.04));
					PrintVar(20,  5, "Vel %.1f ", FP(vel * 0.1));
					PrintVar(35,  5, "Dist %.0f ", FP(Dist2D * 0.01));
					PrintVar(50,  5, "X %.0f ", FP(World.X));
					PrintVar(65,  5, "Z %.0f ", FP(World.Z));

					{
						FP DeltaY = World.Y - dp->Y;
						if(DeltaY < 0) DeltaY *= -1;
						if(DeltaY < 10000)
							int breakpoint = 0;

						FP Pitch = pitch;
						if(Pitch < 0) Pitch *= -1;
						if(Pitch < ANGLES_1Deg)
							int breakpoint = 0;
					}
					break;
				case F84:
					PrintVar( 0,  6, "F84  Pitch %.1f ", FP(pitch / 182.04));
					PrintVar(20,  6, "Vel %.1f ", FP(vel * 0.1));
					PrintVar(50,  6, "X %.0f ", FP(World.X));
					PrintVar(60,  6, "Z %.0f ", FP(World.Z));
					{
						FP DeltaY = World.Y - dp->Y;
						if(DeltaY < 0) DeltaY *= -1;
						if(DeltaY < 10000)
							int breakpoint = 0;

						FP Pitch = pitch;
						if(Pitch < 0) Pitch *= -1;
						if(Pitch < ANGLES_1Deg)
							int breakpoint = 0;
					}
					break;
				case F80:
					PrintVar( 0,  7, "F80  Pitch %.1f ", FP(pitch / 182.04));
					PrintVar(20,  7, "Vel %.1f ", FP(vel * 0.1));
					PrintVar(50,  7, "X %.0f ", FP(World.X));
					PrintVar(60,  7, "Z %.0f ", FP(World.Z));
					{
						FP DeltaY = World.Y - dp->Y;
						if(DeltaY < 0) DeltaY *= -1;
						if(DeltaY < 10000)
							int breakpoint = 0;

						FP Pitch = pitch;
						if(Pitch < 0) Pitch *= -1;
						if(Pitch < ANGLES_1Deg)
							int breakpoint = 0;
					}
					break;
				case F51:
					PrintVar( 0,  8, "P51  Pitch %.1f ", FP(pitch / 182.04));
					PrintVar(20,  8, "Vel %.1f ", FP(vel * 0.1));
					PrintVar(50,  8, "X %.0f ", FP(World.X));
					PrintVar(60,  8, "Z %.0f ", FP(World.Z));
					{
						FP DeltaY = World.Y - dp->Y;
						if(DeltaY < 0) DeltaY *= -1;
						if(DeltaY < 10000)
							int breakpoint = 0;

						FP Pitch = pitch;
						if(Pitch < 0) Pitch *= -1;
						if(Pitch < ANGLES_1Deg)
							int breakpoint = 0;
					}
					break;
				case B26:
					PrintVar( 0,  9, "B26  Pitch %.1f ", FP(pitch / 182.04));
					PrintVar(20,  9, "Vel %.1f ", FP(vel * 0.1));
					PrintVar(50,  9, "X %.0f ", FP(World.X));
					PrintVar(60,  9, "Z %.0f ", FP(World.Z));
					{
						FP DeltaY = World.Y - dp->Y;
						if(DeltaY < 0) DeltaY *= -1;
						if(DeltaY < 10000)
							int breakpoint = 0;

						FP Pitch = pitch;
						if(Pitch < 0) Pitch *= -1;
						if(Pitch < ANGLES_1Deg)
							int breakpoint = 0;
					}
					break;
				case B29:
					PrintVar( 0, 10, "B29  Pitch %.1f ", FP(pitch / 182.04));
					PrintVar(20, 10, "Vel %.1f ", FP(vel * 0.1));
					PrintVar(50, 10, "X %.0f ", FP(World.X));
					PrintVar(60, 10, "Z %.0f ", FP(World.Z));
					{
						FP DeltaY = World.Y - dp->Y;
						if(DeltaY < 0) DeltaY *= -1;
						if(DeltaY < 10000)
							int breakpoint = 0;

						FP Pitch = pitch;
						if(Pitch < 0) Pitch *= -1;
						if(Pitch < ANGLES_1Deg)
							int breakpoint = 0;
					}
					break;
				break;
			}
*/
/* TEST CODE CSB 08/06/99 */			
/* TEST CODE CSB 08/06/99 */			
/* TEST CODE CSB 08/06/99 */			
			

			level&=CalcHdgRollLimited ();	//CSB 29/09/98 //This limits the Roll such that the
			if(Range > MILES20)
			{
				if( roll > ANGLES_45Deg) roll = ANGLES_45Deg;
				if(-roll > ANGLES_45Deg) {roll = ANGLES_45Deg;	roll = -roll;}
			}
			//speed is not significantly affected by the roll angle
			level&=AutoCalcPitch ();

			CalcXYZVel();
			if (waypoint && !formpos && fly.leadflight && fly.leadflight->waypoint==waypoint->next) //JIM 18/04/99
			{
				if (information)
					desposrange+=METRES10KM;
				else
					desposrange+=MILES01; //escortee gone through WP so allow increased range!
			}
			information=FALSE;
			if (level && Range>desposrange+MILES02)											//JIM 21Oct96
			{
				Range-=desposrange;

				if (desposrange>MILES10)						//JIM 19Jun99
					if (pitch)									//JIM 19Jun99
						SetManoeuvreTime (10*SECS100);			//JIM 19Jun99
					else										//JIM 19Jun99
						SetManoeuvreTime (30*SECS100);			//JIM 19Jun99
				else	//Use float multiply as it is faster than int divide//JIM 19Jun99
					SetManoeuvreTime (desposrange*((30.0*SECS100)/MILES10));//JIM 19Jun99
//DeadCode DAW 20Jun99 				if((pitch != ANGLES_0Deg) || (PitchIntercept != ANGLES_0Deg))
//DeadCode DAW 20Jun99 					SetManoeuvreTime(1000);	//CSB 15/06/99	10 secs
//DeadCode DAW 20Jun99 				else
//DeadCode DAW 20Jun99 				{	//Straight and Level flight
//DeadCode DAW 20Jun99 					if (Range>MILES10)
//DeadCode DAW 20Jun99 						SetManoeuvreTime (THIRTYSECS100);//50 secs @ 600mph=10miles
//DeadCode DAW 20Jun99 					else if (Range>MILES05)
//DeadCode DAW 20Jun99 						SetManoeuvreTime (15*SECS100); //50 secs @ 600mph=10miles
//DeadCode DAW 20Jun99 					else
//DeadCode DAW 20Jun99 						SetManoeuvreTime (FIVESECS100);
//DeadCode DAW 20Jun99 				}
			}
			else   //readyroomhostcampaign
				if (ReachedDesPos ())								//JIM 03Jul96
				{													//JIM 03Jul96
					ExecuteWayPointAction ();						//JIM 03Jul96
				}
		}														//JIM 03Jul96
															//JIM 03Jul96
		NewPosition ();
		SetFlightParams ();
	}
}
//////////////////////////////////////////////////////////////////////
//
// Function:    MoveMissionDiceThrow
// Date:		08/06/99
// Author:		Jim
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	AirStruc::MoveMissionDiceThrow()
{
	MissionDiceThrow(waypoint->FindWP(WPNAME_Target));
	movecode=AUTO_FOLLOWWP;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoCommsAccel
//Author		Andy McMaster
//Date			Fri 11 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoCommsAccel()
{
// simulate AUTOACCEL_FWD

	Coords3D	*dpflyto;

	SWord sinHdg,cosHdg;
	Range=METRES5000;
	Math_Lib.high_sin_cos(hdg,sinHdg,cosHdg);
	dpflyto=&despos;
	dpflyto->X=World.X+MULSHSIN(sinHdg,Range,ANGLES_SHIFT);
	dpflyto->Z=World.Z+MULSHSIN(cosHdg,Range,ANGLES_SHIFT);
	dpflyto->Y=World.Y;

	InterceptandRange (dpflyto);

	CalcXYZVel();
	NewPosition ();
}

//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		AutoTrainingPreMerge
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Tue 28 Nov 1995
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void AirStruc::AutoTrainingPreMerge ()
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 }

//////////////////////////////////////////////////////////////////////
//
// Function:    AutoAccelerate
// Date:		19/04/99
// Author:		Paul/JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void AirStruc::AutoAccelerate()
{
	long velval;
	assert(ULong(this)==ULong(Manual_Pilot.ControlledAC2)&&"AutoAccelerate is for the piloted ac only");
	AirStrucPtr	canwpwing=NULL;
//DEADCODE DAW 27/04/99 	UByteP(0xB0000)[2*uniqueID.count&0xfff]=information?roll?'R':'I':manoeuvretime?'T':'C';
//DEADCODE DAW 27/04/99 	if (!UByteP(0xB0000)[160]++)	UByteP(0xB0000)[162]++;
	if	(information || !TimeLeft())
	{
		Coords3D dp1,dp2;
		Coords3D	*dparrived,*dpflyto;
		Angles		pitch,roll;
		int alt = Land_Scape.GetGroundLevel(World);
		if (World.Y-alt<METRES500)
		{	//1 in 10 gradient climb to 500m
			dp1.X=dp1.Y=dp1.Z=0;
			dparrived=&dp1;
			dpflyto=&dp2;
			Range=METRES1000;
			SWord sinHdg,cosHdg;
			Math_Lib.high_sin_cos(hdg,sinHdg,cosHdg);
			dpflyto->X=World.X+MULSHSIN(sinHdg,Range,ANGLES_SHIFT);
			dpflyto->Z=World.Z+MULSHSIN(cosHdg,Range,ANGLES_SHIFT);
			dpflyto->Y=World.Y+METRES100;
			fly.pModel->SetPlayerMoving(this);
			if (World.Y-alt>METRES100)
			{
				fly.pModel->GearUp(this);
				dpflyto->Y=World.Y+METRES50;	//CSB 08/07/99	
				if(!formpos)					//CSB 08/07/99	
					if(vel > 900) vel = 900;	//CSB 08/07/99	
			}

//DeadCode DAW 01Jul99 			playermoving=true;
		}
		else
		switch (Manual_Pilot.controlmode)
		{
		//Jim's new system:
		// AUTOACCEL_WAYPT:	Continue until the waypoint changes from what it was recorded as
		//					Then quit to normal time
		// AUTOACCEL_MISS:	Continue until the waypoint changes to the recorded setting
		//					Then switch to _WAYPT mode to wait for next action!
		case ManualPilot::AUTOACCEL_MISS:
		case ManualPilot::AUTOACCEL_WAYPT:
			dp1=*FindDesPos();
			dparrived=dpflyto=&dp1;
			if (Manual_Pilot.controlmode==ManualPilot::AUTOACCEL_WAYPT)
				if (Manual_Pilot.acceltochanged)
					if (waypoint!=Manual_Pilot.acceltochanged)
						OverLay.CancelAccel();
			if (Manual_Pilot.controlmode==ManualPilot::AUTOACCEL_MISS)
				if (Manual_Pilot.acceltochanged)
					if (waypoint==Manual_Pilot.acceltochanged)
						Manual_Pilot.controlmode=ManualPilot::AUTOACCEL_WAYPT;	//come out on next!!


			if (leader && leader->movecode!=AUTO_COMBAT && leader->waypoint==waypoint)
			{
				canwpwing=Persons2::PlayerGhostAC->FindLeadCandidate();
				dpflyto=PositionWRTLeader(canwpwing);
			}
			else if (fly.leadflight && fly.leadflight->movecode!=AUTO_COMBAT && fly.leadflight->waypoint==waypoint)
			{
				canwpwing=Persons2::PlayerGhostAC->FindLeadCandidate();
				dpflyto=PositionWRTLeader(canwpwing);
			}
			break;
//		case ManualPilot::AUTOACCEL_HOME:
//			despos=ai.homebase->World;
//			despos.Y+=METRES1000;
//			dparrived=dpflyto=&despos;
//			//find the position of the landing waypoint
//			break;
		case ManualPilot::AUTOACCEL_FWD:
			//move to a position ahead of the aircraft
			SWord sinHdg,cosHdg;
			Range=METRES5000;
			Math_Lib.high_sin_cos(hdg,sinHdg,cosHdg);
			dparrived=dpflyto=&despos;
			dpflyto->X=World.X+MULSHSIN(sinHdg,Range,ANGLES_SHIFT);
			dpflyto->Z=World.Z+MULSHSIN(cosHdg,Range,ANGLES_SHIFT);
			dpflyto->Y=World.Y;
			break;
		case ManualPilot::AUTOACCEL_MSG:
			if (OverLay.message_target)
			{
				dparrived=
					dpflyto=&dp1;
				dp1=OverLay.message_target->World;
			}
			else OverLay.CancelAccel();
			break;
		default:
			assert(false&&"Illegal control mode in AutoAccelerate");
			break;
		}



		desposrange=MILES01;	 //SEE CheckManualCourse
		if (Save_Data.gamedifficulty[GD_TACTICALRANGE])
			desposrange=MILES05;

		SLong DeltaRange = World.Y - dpflyto->Y;	//CSB 30/06/99	
		if(DeltaRange < 0) DeltaRange *= -1;		//CSB 30/06/99	
		desposrange += DeltaRange;					//CSB 30/06/99


		InterceptandRange (dpflyto);

		Bool level=(Bool)(Range>MILES01);
		if (!Manual_Pilot.acceltochanged)
		if (dpflyto!=dparrived)										  //JIM 14/04/99
		{
			if (Range<desposrange && Math_Lib.distance3d(World.X-dparrived->X,World.Y-dparrived->Y,World.Z-dparrived->Z)<desposrange)
			{
//DEADCODE JIM 16/04/99 				ExecuteWayPointAction ();
				OverLay.CancelAccel();
			}
		}
		else
			if (Range<desposrange)
			{
//DEADCODE JIM 16/04/99 				ExecuteWayPointAction ();
				OverLay.CancelAccel();
			}

		if (canwpwing && Range<desposrange*2)
		{
			if (Range>desposrange)
				information=FALSE;
			AutoFollowWpWing(canwpwing);	
		}
		else
		{
			information=FALSE;

			SWord dVel, dHdg, dPitch;
			WindTrackCorrection(vel, HdgIntercept, PitchIntercept, dVel, dHdg, dPitch);
			HdgIntercept   += dHdg;
			PitchIntercept += dPitch;

			if(Manual_Pilot.controlmode == ManualPilot::AUTOACCEL_FWD)	//CSB 18Jun99
				HdgIntercept = hdg;										//CSB 18Jun99

			SWord LocalBestClimbPitch=CalcBestClimbPitch();

			if (PitchIntercept>(Angles)LocalBestClimbPitch)
			{
	 			PitchIntercept=(Angles)LocalBestClimbPitch;
	//TEMPCODE JIM 14/04/99 			Range-=dp->Y-World.Y;
			}
			if (Range>MILES01 && PitchIntercept<<(Angles)LocalBestClimbPitch)
				PitchIntercept=(Angles)LocalBestClimbPitch;

			level&=CalcVelAlt();
			level&=CalcHdgRollLimited ();
			level&=AutoCalcPitch ();
			CalcXYZVel();


			if (level && Range>desposrange*2)
			{
				if (Range-desposrange>MILES10)		SetManoeuvreTime();
				else if (Range-desposrange>MILES05)	SetManoeuvreTime(THIRTYSECS100);
				else if (Range-desposrange>MILES02)	SetManoeuvreTime(10*SECS100);
				else								SetManoeuvreTime(FIVESECS100);
			}

		NewPosition ();
		SetFlightParams ();

		}
	}
	else
	{
		NewPosition ();
		SetFlightParams ();
	}
}
//%%			if (level && Range>desposrange)
//%%			{
//%%				if (Range-desposrange>MILES10)		SetManoeuvreTime();
//%%				if (Range-desposrange>MILES05)		SetManoeuvreTime(THIRTYSECS100);
//%%				else if (Range-desposrange>MILES02)	SetManoeuvreTime(10*SECS100);
//%%				else								SetManoeuvreTime(FIVESECS100);
//%%			}
//%%	//		else
//%%		}
//%%	}
//%%	NewPosition ();
//%%	SetFlightParams ();
//%%}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Procedure
//Author		R. Hyde 
//Date			Thu 12 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AutoCrashSkid()
{
	SLong	groundlevel;										//RJS 02Jul98
	ANGLES	grndroll;											//RJS 02Jul98
	ANGLES	grndpitch;											//RJS 02Jul98
//DeadCode RJS 10May99 	ANGLES	grndhdg = fly.pModel->grndhdg;
	Bool	onWater = FALSE;
	AreaType	theArea;
	UByte	slowshift = 3;										//RJS 06Dec98
	AircraftAnimData	*adptr = (AircraftAnimData*) Anim;

//	if (_Collide.HaveWeLanded(*this,grndpitch,grndroll,TRUE) == Collide::NOTTOUCHED)
//		movecode = AUTO_SPIRAL2GROUND;
	_Collide.HaveWeLanded(*this,grndpitch,grndroll,TRUE);

	groundlevel = fly.pModel->GroundHeight;

	theArea = (AreaType)Three_Dee.GetLandType();
	if ((theArea == AT_sea) || (theArea == AT_river) || (theArea == AT_washShore))
	{
		onWater = TRUE;
		slowshift = 4;											//RJS 06Dec98
	}

//Dead	if (fly.thrustpercent >0)						
	fly.thrustpercent = 0;										//RJS 17May99

	// Set new thrust in flight model...

	if (vel <= 0)
	{
		if (this == Manual_Pilot.ControlledAC2)					//RJS 08Sep98
			_Miles.StopEngine();								//RJS 08Sep98

		SHAPE.DetatchAllVapourStreams(*this,0);					//RJS 14Jul98
		adptr->hasdust = FALSE;

		if (onWater)
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shape);
			SLong			size = sdptr->Size << 4;
			SLong			dist = World.Y - groundlevel;

			if (Trans_Obj.View_Object && (this==Manual_Pilot.ControlledAC2))
				Trans_Obj.View_Object->SetToDeathView(DEATH_WATER);

			//Sink...
			if (dist > -size)
			{
				if (dist < 0)
				{
					dist = size + dist;
				}
				else
					dist = size;

				Trans_Obj.LaunchBubbles(*this,dist,*currworld);

				if (pitch < ANGLES_45Deg)
					pitch += (Angles)(Timer_Code.FRAMETIME<<2);

				if (roll < ANGLES_45Deg)
					roll += (Angles)(Timer_Code.FRAMETIME<<2);

				World.Y -= Timer_Code.FRAMETIME;
			}
			else
			{
				//Kill shadows & stuff...
				MinAnimData*	mad = (MinAnimData*)Anim;			//RJS 18Jun99
				mad->itemstate = DEAD;
				mad->IsInvisible = 1;

				movecode = AUTO_NOPPILOT;
			}
		}
		else
		{
			Trans_Obj.LaunchDustRingBig(*this,*currworld);

			// The end...
			movecode = AUTO_NOPPILOT;
			if (Trans_Obj.View_Object && (this==Manual_Pilot.ControlledAC2))
				Trans_Obj.View_Object->SetToDeathView(DEATH_NORMAL);
		}

//DeadCode RJS 10May99 /*		if (shape == WRECK)
//DeadCode RJS 10May99 		{
//DeadCode RJS 10May99 			shape = CRATER;
//DeadCode RJS 10May99 			if (this == Manual_Pilot.ControlledAC2)
//DeadCode RJS 10May99 			{
//DeadCode RJS 10May99 					GR_Quit3DNow=CRASHED_DEAD;		
//DeadCode RJS 10May99 				_Miles.StopEngine();
//DeadCode RJS 10May99 			}
//DeadCode RJS 10May99 			Trans_Obj.LaunchFire(*this,*currworld);
//DeadCode RJS 10May99 			if (_DPlay.Implemented)								//AMM 17Jun97
//DeadCode RJS 10May99 			{													//AMM 17Jun97
//DeadCode RJS 10May99 				Trans_Obj.LaunchCrater(*this,*currworld);				//AMM 04Jul97
//DeadCode RJS 10May99 				_DPlay.SendKill(*this,GR_Quit3DNow,PIDC_FIRECRATER,NULL);//AMM 17Jun97
//DeadCode RJS 10May99 			}													//AMM 17Jun97
//DeadCode RJS 10May99 		}
//DeadCode RJS 10May99 		else*/
//DeadCode RJS 10May99 		{
//DeadCode RJS 10May99 			SLong	anggap = (grndhdg - hdg)*3;
//DeadCode RJS 10May99 
//DeadCode RJS 10May99 			anggap >>= 2;
//DeadCode RJS 10May99 
//DeadCode RJS 10May99 			hdg += (Angles) anggap;
//DeadCode RJS 10May99 
//DeadCode RJS 10May99 			if (this == Manual_Pilot.ControlledAC2)
//DeadCode RJS 10May99 					GR_Quit3DNow=CRASHED_ALIVE;					//RDH 22Sep96
//DeadCode RJS 10May99 		}
	}
	else
	{
		World.Y = groundlevel;
		if (onWater)
		{
			// Give it 4 seconds to knacker totally...
			UWord	damage = (BS_DEAD * fly.pModel->CrashTime)/400;

			if (damage > BS_DEAD) damage = BS_DEAD;

			if (Math_Lib.rnd() > 32767)
			{
				if ((adptr->LEFTWINGIN < BS_DAMLV1) && (damage >= BS_DAMLV1))
					SHAPE.ForceDamage(*this,*this,&adptr->LEFTWINGIN,BS_DAMLV1);
				else
				{
					if ((adptr->LEFTWINGIN < BS_DAMLV2) && (damage >= BS_DAMLV2))
						SHAPE.ForceDamage(*this,*this,&adptr->LEFTWINGIN,BS_DAMLV2);
					else
					{
						if ((adptr->LEFTWINGIN < BS_DEAD) && (damage >= BS_DEAD))
							SHAPE.ForceDamage(*this,*this,&adptr->LEFTWINGIN,BS_DEAD);
					}
				}
			}
			else
			{
				if ((adptr->RIGHTWINGIN < BS_DAMLV1) && (damage >= BS_DAMLV1))
					SHAPE.ForceDamage(*this,*this,&adptr->RIGHTWINGIN,BS_DAMLV1);
				else
				{
					if ((adptr->RIGHTWINGIN < BS_DAMLV2) && (damage >= BS_DAMLV2))
						SHAPE.ForceDamage(*this,*this,&adptr->RIGHTWINGIN,BS_DAMLV2);
					else
					{
						if ((adptr->RIGHTWINGIN < BS_DEAD) && (damage >= BS_DEAD))
							SHAPE.ForceDamage(*this,*this,&adptr->RIGHTWINGIN,BS_DEAD);
					}
				}
			}

			_Miles.PlayLooped(FIL_SFX_WATER_LOOP,*this);
		}

		vel -= (Timer_Code.FRAMETIME << slowshift);						//RJS 24Aug98

		CalcXYZVel();
 		NewDeadPosition ();	

		if (roll > grndroll)
			roll -= (Angles)Timer_Code.FRAMETIME;
		if (roll < grndroll)
			roll += (Angles)Timer_Code.FRAMETIME;
		if (pitch > grndpitch)
			pitch -= (Angles)Timer_Code.FRAMETIME;
		if (pitch < grndpitch)
			pitch += (Angles)Timer_Code.FRAMETIME;

//DeadCode RJS 23Feb98 		groundlevel = Land_Scape.GetGroundLevel(*this);			//RJS 01Nov96
//DeadCode RJS 23Feb98 		if ((World.Y - groundlevel) < 300)						//RJS 01Nov96
//DeadCode RJS 23Feb98 			Trans_Obj.LaunchDustTrail(*this,*currworld);		//RJS 01Nov96

		if (this == Manual_Pilot.ControlledAC2)
		{
//			if (hdg < 0)
//				fly.pModel->grndhdg = hdg - ANGLES_50Deg;
//			else
//				fly.pModel->grndhdg = hdg + ANGLES_50Deg;

			_Miles.PlayLanded(*this,vel,FALSE);//RJS 22Nov96
//			_Miles.PlayEngine(classtype,fly.rpm,vel);			//RJS 03Dec96
		}
	}

	fly.pModel->CrashTime += Timer_Code.FRAMETIME;//RJS 25Aug98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoCrashRoll
//Author		R. Hyde 
//Date			Thu 12 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AutoCrashRoll()
{
//DeadCode RJS 26Aug98 	AircraftAnimData* adptr;
//DeadCode RJS 26Aug98 	Bool	rolldone, pitchdone;
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 	adptr = (AircraftAnimData*)Anim;
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 	ANGLES	anglestep = (Angles)(Timer_Code.FRAMETIME * ANGLES_2Deg);//RJS 09Oct96
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 	if (shape == WRECK)
//DeadCode RJS 26Aug98 	{
//DeadCode RJS 26Aug98 	 	shape = CRATER;
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 		if (this == Manual_Pilot.ControlledAC2)
//DeadCode RJS 26Aug98 			_Miles.StopEngine();						
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 		Trans_Obj.LaunchFire(*this,*currworld);
//DeadCode RJS 26Aug98 		if (_DPlay.Implemented)									//AMM 17Jun97
//DeadCode RJS 26Aug98 		{														//AMM 17Jun97
//DeadCode RJS 26Aug98 			Trans_Obj.LaunchCrater(*this,*currworld);				//AMM 04Jul97
//DeadCode RJS 26Aug98 			_DPlay.SendKill(*this,GR_Quit3DNow,PIDC_FIRECRATER,NULL);//AMM 17Jun97
//DeadCode RJS 26Aug98 		}														//AMM 17Jun97
//DeadCode RJS 26Aug98 	}
//DeadCode RJS 26Aug98 	else
//DeadCode RJS 26Aug98 	{
//DeadCode RJS 26Aug98 		if (adptr->RIGHTWINGIN == BS_DEAD)						//RJS 13Mar97
//DeadCode RJS 26Aug98 		{
//DeadCode RJS 26Aug98 			//right wing is missing
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 			if ((roll >> ANGLES_10Deg) && (roll << ANGLES_170Deg))
//DeadCode RJS 26Aug98 			{
//DeadCode RJS 26Aug98 				roll += anglestep;
//DeadCode RJS 26Aug98 				rolldone = FALSE;
//DeadCode RJS 26Aug98 			}
//DeadCode RJS 26Aug98 			else
//DeadCode RJS 26Aug98 				rolldone = TRUE;
//DeadCode RJS 26Aug98 		}
//DeadCode RJS 26Aug98 		else
//DeadCode RJS 26Aug98 		{
//DeadCode RJS 26Aug98 			if (adptr->LEFTWINGIN == BS_DEAD)					//RJS 13Mar97
//DeadCode RJS 26Aug98 			{
//DeadCode RJS 26Aug98 				//left wing is missing
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 				if ((roll >> ANGLES_170Deg) && (roll << ANGLES_350Deg))
//DeadCode RJS 26Aug98 				{
//DeadCode RJS 26Aug98 					roll -= anglestep;
//DeadCode RJS 26Aug98 					rolldone = FALSE;
//DeadCode RJS 26Aug98 				}
//DeadCode RJS 26Aug98 				else
//DeadCode RJS 26Aug98 					rolldone = TRUE;
//DeadCode RJS 26Aug98 			}
//DeadCode RJS 26Aug98 		}
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 		if ((pitch >> ANGLES_20Deg) && (pitch << ANGLES_340Deg))
//DeadCode RJS 26Aug98 		{
//DeadCode RJS 26Aug98 			pitch += anglestep;
//DeadCode RJS 26Aug98 			pitchdone = FALSE;
//DeadCode RJS 26Aug98 		}
//DeadCode RJS 26Aug98 		else
//DeadCode RJS 26Aug98 			pitchdone = TRUE;
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 		if (pitchdone && rolldone)									//RJS 07Oct96
//DeadCode RJS 26Aug98 		{
//DeadCode RJS 26Aug98 			//burn		
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 			if (adptr->itemstate!=DEAD)
//DeadCode RJS 26Aug98 			{
//DeadCode RJS 26Aug98 				adptr->itemstate=DEAD;
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 				if (this == Manual_Pilot.ControlledAC2)
//DeadCode RJS 26Aug98 				{
//DeadCode RJS 26Aug98 					_Miles.StopEngine();							//RJS 04Oct96
//DeadCode RJS 26Aug98 						GR_Quit3DNow=CRASHED_DEAD;					//RJS 21Oct96
//DeadCode RJS 26Aug98 				}
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 				Trans_Obj.LaunchFire(*this,*currworld);				//RJS 09Oct96
//DeadCode RJS 26Aug98 				movecode=AUTO_NOPPILOT;
//DeadCode RJS 26Aug98 				if (_DPlay.Implemented)							//AMM 17Jun97
//DeadCode RJS 26Aug98 				{												//AMM 17Jun97
//DeadCode RJS 26Aug98 					Trans_Obj.LaunchCrater(*this,*currworld);				//AMM 04Jul97
//DeadCode RJS 26Aug98 					_DPlay.SendKill(*this,GR_Quit3DNow,PIDC_FIRECRATER,NULL);//AMM 17Jun97
//DeadCode RJS 26Aug98 				}												//AMM 17Jun97
//DeadCode RJS 26Aug98 			}
//DeadCode RJS 26Aug98 		}
//DeadCode RJS 26Aug98 		else
//DeadCode RJS 26Aug98 		{
//DeadCode RJS 26Aug98 //			Trans_Obj.LaunchDustTrail(*this,*currworld);		//RJS 13Nov96
//DeadCode RJS 26Aug98 			CalcXYZVel ();
//DeadCode RJS 26Aug98 			NewPosition ();
//DeadCode RJS 26Aug98 		}
//DeadCode RJS 26Aug98 	}
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98  	//after a few secs
//DeadCode RJS 26Aug98 //DeadCode RJS 21Oct96 	GR_Quit3DNow=CRASHED_DEAD;					//RDH 22Sep96
//DeadCode RJS 26Aug98 
//DeadCode RJS 26Aug98 	SetFlightParams ();

	SLong	groundlevel;										
	ANGLES	grndroll;											
	ANGLES	grndpitch;											
//DeadCode AMM 29Jun99 	ANGLES	grndhdg = fly.pModel->grndhdg;
	Bool	onWater = FALSE;
	AreaType	theArea;
	UByte	slowshift;
	ANGLES	anglestep = (Angles)(Timer_Code.FRAMETIME * ANGLES_2Deg);//RJS 26Aug98
	AircraftAnimData	*adptr = (AircraftAnimData*) Anim;
	Bool	rolldone, pitchdone;


	_Collide.HaveWeLanded(*this,grndpitch,grndroll,TRUE);		//RJS 24Aug98
	groundlevel = fly.pModel->GroundHeight;

	slowshift = 4;
	theArea = (AreaType)Three_Dee.GetLandType();
	if ((theArea == AT_sea) || (theArea == AT_river) || (theArea == AT_washShore))
	{
		onWater = TRUE;
		slowshift += 6;
	}

	SWord	tmproll, tmppitch;
	SLong	crashtime = fly.pModel->CrashTime;

	World.Y = groundlevel;

	if (vel > 0)
	{
		ANGLES	oldhdg = hdg;

		vel -= (Timer_Code.FRAMETIME << slowshift);						//RJS 24Aug98

		anglestep += ((anglestep * vel) / 500);

		if (adptr->RIGHTWINGIN == BS_DEAD)						
		{
			hdg += ANGLES_45Deg;
			roll += anglestep;

			tmproll = roll;
			if (tmproll < -ANGLES_90Deg)
				SHAPE.ForceDamage(*this,*this,&adptr->LEFTWINGOUT,BS_DEAD);
		}
		else
		{
			if (adptr->LEFTWINGIN == BS_DEAD)						
			{
				hdg -= ANGLES_45Deg;
				roll -= anglestep;

				tmproll = roll;
				if (tmproll > ANGLES_90Deg)
					SHAPE.ForceDamage(*this,*this,&adptr->RIGHTWINGOUT,BS_DEAD);
			}
		}

		CalcXYZVel();
 		NewDeadPosition ();	

		hdg = oldhdg;
	}
	else
	{
		SWord	maxangle = ANGLES_170Deg;
		bool	tipleft = false;

		if (Trans_Obj.View_Object && (this==Manual_Pilot.ControlledAC2))//RDH 02Sep98
			Trans_Obj.View_Object->SetToDeathView(DEATH_NORMAL);//RDH 02Sep98

		if (this == Manual_Pilot.ControlledAC2)					//RJS 08Sep98
			_Miles.StopEngine();								//RJS 08Sep98

		SHAPE.DetatchAllVapourStreams(*this,0);			
		adptr->hasdust = FALSE;

		tmproll = roll;
		tmppitch = pitch;

		//Feeble gravity effect...
		//The bigger the angle, the slower it tips...

		if ((adptr->RIGHTWINGIN == BS_DEAD) && (tmproll < ANGLES_45Deg))
		{
			maxangle = ANGLES_0Deg;
			tipleft = true;
		}
		else
		{
			if ((adptr->LEFTWINGIN == BS_DEAD) && (tmproll > -ANGLES_45Deg))
				maxangle = ANGLES_0Deg;
			else
				tipleft = true;
		}

		if (tipleft == false)
		{
			if (tmproll >= maxangle)
				rolldone = TRUE;
			else
			{
				anglestep = (Angles) (ANGLES_1Deg * crashtime);

				roll+=anglestep;
				rolldone = FALSE;
			}
		}
		else
		{
			if (tmproll <= -maxangle)
				rolldone = TRUE;
			else
			{
				anglestep = (Angles) (ANGLES_1Deg * crashtime);

				roll-=anglestep;
				rolldone = FALSE;
			}
		}

		if (tmppitch < ANGLES_170Deg)
		{
			anglestep = (Angles) (ANGLES_1Deg * crashtime);

			tmppitch += anglestep;
			pitchdone = FALSE;
		}
		else
			pitchdone = TRUE;

		if (rolldone && pitchdone)
		{
			Trans_Obj.LaunchDirtMedium(*this,*currworld);
			movecode = AUTO_NOPPILOT;

			if (this == Manual_Pilot.ControlledAC2)
				GR_Quit3DNow=CRASHED_ALIVE;					//RDH 22Sep96
		}
		else
			fly.pModel->CrashTime += Timer_Code.FRAMETIME;
	}
}

//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		AutoTrainingACM
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Tue 28 Nov 1995
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void AirStruc::AutoTrainingACM ()
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99   
//DeadCode RDH 05Jan99 	ai.unfriendly = follower;									//JIM 26Nov96
//DeadCode RDH 05Jan99 	if (!(follower))
//DeadCode RDH 05Jan99 	{
//DeadCode RDH 05Jan99 		AutoFollowWp ();
//DeadCode RDH 05Jan99 	}else
//DeadCode RDH 05Jan99 	{
//DeadCode RDH 05Jan99 		InterceptandRange (&follower->World);
//DeadCode RDH 05Jan99 //DEAD		if (this != Manual_Pilot.ControlledAC2)						//RDH 10Nov96
//DeadCode RDH 05Jan99 //DEAD		{															//RDH 10Nov96
//DeadCode RDH 05Jan99 //DEAD			Miss_Man.camp.TrainingRange += Range/256; 
//DeadCode RDH 05Jan99 //DEAD			Miss_Man.camp.TrainingCount ++;
//DeadCode RDH 05Jan99 //DEAD		}															//RDH 10Nov96
//DeadCode RDH 05Jan99 		if (ai.manoeuvre == MANOEUVRE_SELECT)
//DeadCode RDH 05Jan99 		{	//first time in
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 			static Bool pooed = FALSE;
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 			if (!pooed)
//DeadCode RDH 05Jan99 				Manual_Pilot.InitManualPilot(this);
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 			pooed = TRUE;
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 //DeadCode RDH 27Nov96 			ai.ManStep = PHASE0;
//DeadCode RDH 05Jan99 	//DeadCode RDH 19Nov96 		ai.manoeuvre= MANOEUVRE_GAINHEIGHT;
//DeadCode RDH 05Jan99 //rdh 26march98	 			MoveToThrust (80);
//DeadCode RDH 05Jan99 			SetManoeuvreTime (500);
//DeadCode RDH 05Jan99 			ai.ManStep = PHASE1;
//DeadCode RDH 05Jan99 //DeadCode ARM 15Sep97 			// testing only
//DeadCode RDH 05Jan99 			ai.ManStep  = PHASE0;								//ARM 02Jun97
//DeadCode RDH 05Jan99 	 		ai.desiredroll = ANGLES_0Deg;
//DeadCode RDH 05Jan99 			ai.manoeuvre= MANOEUVRE_STRAIGHTANDLEVEL;				//RDH 19Nov96
//DeadCode RDH 05Jan99 		}
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 //DeadCode ARM 15Sep97 		// testing only
//DeadCode RDH 05Jan99 //DeadCode ARM 15Sep97 		ai.manoeuvre= MANOEUVRE_STRAIGHTANDLEVEL;				//ARM 07May97
//DeadCode RDH 05Jan99 //DeadCode ARM 15Sep97 		ai.manoeuvre= MANOEUVRE_GAINHEIGHT;						//ARM 09May97
//DeadCode RDH 05Jan99 //DeadCode ARM 15Sep97 		ai.manoeuvre= MANOEUVRE_MOVEAWAY;						//ARM 15May97
//DeadCode RDH 05Jan99 //DeadCode ARM 15Sep97 		ai.manoeuvre= MANOEUVRE_STANDONTAIL;					//ARM 08Sep97
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 		ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;				//ARM 15Sep97
//DeadCode RDH 05Jan99 //		ai.manoeuvre = MANOEUVRE_BARRELROLL;					//ARM 15Sep97
//DeadCode RDH 05Jan99 		ai.manoeuvre = MANOEUVRE_GAINHEIGHT;						//ARM 16Sep97
//DeadCode RDH 05Jan99 		ai.manoeuvre = MANOEUVRE_ZOOMANDDROP;					//ARM 18Sep97
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 		switch (ai.manoeuvre)
//DeadCode RDH 05Jan99 		{
//DeadCode RDH 05Jan99 				case MANOEUVRE_BOUNCEFOLLOWER:							
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					BounceFollower ();									
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				//case MANOEUVRE_BARRELROLL:							
//DeadCode RDH 05Jan99 				//{													
//DeadCode RDH 05Jan99 				//	BarrelRoll ();									
//DeadCode RDH 05Jan99 				//	break;											
//DeadCode RDH 05Jan99 				//}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_SCISSORS:							
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					Scissors ();									
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_MILDSCISSORS:						
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					MildScissors ();								
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_SPLITS:								
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					SplitS ();										
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_ZOOMANDDROP:							
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					ZoomandDrop ();									
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_STRAIGHTANDLEVEL :					
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					StraightandLevel ( );							
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 //				case MANOEUVRE_SIDESLIP :							
//DeadCode RDH 05Jan99 //				{													
//DeadCode RDH 05Jan99 //					AcmSideSlip ( );								
//DeadCode RDH 05Jan99 //					break;											
//DeadCode RDH 05Jan99 //				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_SPINOUT :							
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					SpinOut ( );									
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_GAINHEIGHT:							
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					GainHeight ( );									
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_DIVEFORHOME :						
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					DiveforHome ( );								
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_VERTICALLOOP :						
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					VerticalLoop ( );								
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_IMMELMANNTURN :						
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					ImmelmannTurn ( );								
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}													
//DeadCode RDH 05Jan99 				case MANOEUVRE_CLIMBFORHOME:						
//DeadCode RDH 05Jan99 				{													
//DeadCode RDH 05Jan99 					ClimbforHome ( );								
//DeadCode RDH 05Jan99 					break;											
//DeadCode RDH 05Jan99 				}
//DeadCode RDH 05Jan99 				case MANOEUVRE_STANDONTAIL:						//ARM 08Sep97
//DeadCode RDH 05Jan99 				{												//ARM 08Sep97
//DeadCode RDH 05Jan99 					StandOnTail ();								//ARM 08Sep97
//DeadCode RDH 05Jan99 				}												//ARM 08Sep97
//DeadCode RDH 05Jan99 	
//DeadCode RDH 05Jan99 		}
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 		Manual_Pilot.ACMManualPilot(this);
//DeadCode RDH 05Jan99 	
//DeadCode RDH 05Jan99 	}
//DeadCode RDH 05Jan99 }

//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		SelectNextTrainingManoeuvre
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Tue 10 Sep 1996
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void AirStruc::SelectNextTrainingManoeuvre()
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 	SWord	manoeuvrerange=0;// = (SWord)(MANOEUVRE_STRAIGHTDIVE - MANOEUVRE_BARRELROLL);
//DeadCode RDH 05Jan99 	SWord	firstmanoeuvre=0;// = MANOEUVRE_BARRELROLL;
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 //DeadCode RDH 27Nov96 	 ai.manoeuvre = (MANOEUVRE)(MANOEUVRE_BARRELROLL +
//DeadCode RDH 05Jan99 //DeadCode RDH 27Nov96 		Math_Lib.rnd(MANOEUVRE_STRAIGHTDIVE - MANOEUVRE_BARRELROLL));
//DeadCode RDH 05Jan99 	ai.manoeuvre = (MANOEUVRE)(firstmanoeuvre + Math_Lib.rnd(manoeuvrerange));
//DeadCode RDH 05Jan99 	if (	(ai.manoeuvre == MANOEUVRE_SPINOUT)					//RDH 27Nov96
//DeadCode RDH 05Jan99 		&&	 (World.Y < FT_2000)								//RDH 22Nov96
//DeadCode RDH 05Jan99 			)													//RDH 22Nov96
//DeadCode RDH 05Jan99 	{															//RDH 22Nov96
//DeadCode RDH 05Jan99 			ai.manoeuvre = MANOEUVRE_SCISSORS;					//RDH 22Nov96
//DeadCode RDH 05Jan99 	}															//RDH 22Nov96
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 	switch (ai.manoeuvre)
//DeadCode RDH 05Jan99 	{
//DeadCode RDH 05Jan99 		case MANOEUVRE_BOUNCEFOLLOWER:
//DeadCode RDH 05Jan99 //		case MANOEUVRE_TURNINGFIGHT:
//DeadCode RDH 05Jan99 		case MANOEUVRE_MAKEFORFRIENDLY:
//DeadCode RDH 05Jan99 		{
//DeadCode RDH 05Jan99 			ai.manoeuvre = MANOEUVRE_SCISSORS;
//DeadCode RDH 05Jan99 			break;
//DeadCode RDH 05Jan99 		}
//DeadCode RDH 05Jan99 		case MANOEUVRE_MOVEAWAY:
//DeadCode RDH 05Jan99 		case MANOEUVRE_ACCIDENTALSPINOUT:
//DeadCode RDH 05Jan99 		{
//DeadCode RDH 05Jan99 			ai.manoeuvre = MANOEUVRE_VERTICALLOOP;
//DeadCode RDH 05Jan99 			break;
//DeadCode RDH 05Jan99 		}
//DeadCode RDH 05Jan99 		case MANOEUVRE_LOWYOYO:
//DeadCode RDH 05Jan99 		case MANOEUVRE_HEADONOFFSET:
//DeadCode RDH 05Jan99 //		{
//DeadCode RDH 05Jan99 //			ai.manoeuvre = MANOEUVRE_SIDESLIP;
//DeadCode RDH 05Jan99 //			break;
//DeadCode RDH 05Jan99 //		}
//DeadCode RDH 05Jan99 		case MANOEUVRE_STAYWITHPREY:
//DeadCode RDH 05Jan99 		case MANOEUVRE_DIVEANDZOOM:
//DeadCode RDH 05Jan99 		case MANOEUVRE_GOHOME:
//DeadCode RDH 05Jan99 	
//DeadCode RDH 05Jan99 		{
//DeadCode RDH 05Jan99 			ai.manoeuvre = MANOEUVRE_IMMELMANNTURN;
//DeadCode RDH 05Jan99 			break;
//DeadCode RDH 05Jan99 		}
//DeadCode RDH 05Jan99 		case MANOEUVRE_IMMELMANN:
//DeadCode RDH 05Jan99 		case MANOEUVRE_STRAIGHTDIVE:
//DeadCode RDH 05Jan99 		{
//DeadCode RDH 05Jan99 //			ai.manoeuvre = MANOEUVRE_BARRELROLL;
//DeadCode RDH 05Jan99 			break;
//DeadCode RDH 05Jan99 		}
//DeadCode RDH 05Jan99 	}
//DeadCode RDH 05Jan99 	if ((ai.manoeuvre == MANOEUVRE_VERTICALLOOP)				//RDH 19Dec96
//DeadCode RDH 05Jan99 		&& (vel < MPH100)										//RDH 19Dec96
//DeadCode RDH 05Jan99 			)													//RDH 19Dec96
//DeadCode RDH 05Jan99 			ai.manoeuvre= MANOEUVRE_STRAIGHTANDLEVEL;			//RDH 19Dec96
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 //	ai.manoeuvre = MANOEUVRE_BARRELROLL;						//ARM 15Sep97
//DeadCode RDH 05Jan99 	ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;					//ARM 15Sep97
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrackBogey
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
void	AirStruc::TrackBogey()
{
	//routine used for AUTO_TRACKING equate
	AutoPreCombat ();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrackBandit
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
void	AirStruc::TrackBandit()
{
	//## not used????
	//routine used for AUTO_TRACKING equate
	AutoPreCombat ();
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoPreCombat
//Author		R. Hyde 
//Date			Thu 11 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AutoPreCombat ()
{
/* TEST CODE CSB 01/06/99 */	
/* TEST CODE CSB 01/06/99 */		
/* TEST CODE CSB 01/06/99 */	
/*	MODEL& MOD = *fly.pModel;
	int flightno = formpos & 0x03;
	int flightpo = (formpos & 0x30) / 16;
	int grouppos = 1 + flightno * 4 + flightpo;
	int line = grouppos + 1;
	if((MOD.Type == AT_MIG15) || (MOD.Type == AT_MIG15BIS))
		line += 9;

	{
		if((MOD.Type == AT_MIG15) || (MOD.Type == AT_MIG15BIS))
			PrintVar(0, line, "MiG %.0f      ", FP(grouppos));
		else
			PrintVar(0, line, "F86 %.0f      ", FP(grouppos));

		PrintVar(10, line, "Vel %.1f      ", FP(vel / 10.0));

		if(ai.unfriendly)
		{	InterceptandRange (&ai.unfriendly->World);
			PrintVar(20, line, "Range %.0f      ", FP(Range / 100.0));
		}
		
		if(ai.simpleacm) PrintString(30, line, "simple    ");
		else			 PrintString(30, line, "COMPLEX   ");

		PrintString(40, line, "** AutoPreCombat **				");
	}

*/
/* TEST CODE CSB 01/06/99 */
/* TEST CODE CSB 01/06/99 */
/* TEST CODE CSB 01/06/99 */

 	SLong groundlevel;

//##switches to combat should only occur if in PRECOMBAT, could be in tracking??
	
	AirStrucPtr candidate=NULL;
	candidate = FindLeadCandidate();
	Float rangeto = RECOGNISERANGE;
	rangeto = rangeto * rangeto;
	Float maxrange = rangeto;
	if (candidate)
	{
		rangeto = Distance3DSquared(&candidate->World);
	}
	if	((rangeto < maxrange) &&	(			((candidate)	&&	(movecode==candidate->movecode))
												||	((candidate  == Persons2::PlayerGhostAC)  && (Persons2::PlayerSeenAC->movecode == AUTO_TRACKINGBOGIE))
										)
		)
//DEADCODE RDH 18/06/99 	if (	((formpos&InWingMAX) && leader && leader->movecode == movecode)	) //RDH 10/05/99
//DEADCODE RDH 10/05/99 	if (	((formpos&InWingMAX) && leader && leader->movecode==AUTO_PRECOMBAT)	)
	{//follower
		if (ai.unfriendly)
		{
			InterceptandRange (&ai.unfriendly->World);
//DeadCode CSB 24/06/99				if (Range<ENGAGERANGE)
			if (Range<COMBATRANGE)	//CSB 24/06/99	
			{	//set for combat next frame
				//opportunity to re-think engagement and change unfriendly	
				//leader should have already told follower to engage
				//as he hasn't try again
				if (	(leader)	&&	(ai.elementtactics == WELDEDWING))
				{//don't give a target: this should lead to weldedwing tactics //RDH 28/04/99
					Art_Int.SetEngage(this,NULL, MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
				}else
					Art_Int.SetEngage(this,*ai.unfriendly, MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
			}
		}
//DeadCode CSB 07/06/99			if (leader->vel<TAKEOFFSPEED)
//DeadCode CSB 07/06/99			{															//JIM 18Dec96
//DeadCode CSB 07/06/99				AutoTakeOff();										//JIM 18Dec96
//DeadCode CSB 07/06/99				return;												//JIM 18Dec96
//DeadCode CSB 07/06/99			}															//JIM 18Dec96
		AutoFollowWpWing (candidate);
	}
	else if (ai.unfriendly==NULL)
	{
		Art_Int.BreakOff(this);
		AutoFollowWp();
	}
	else
	{
		if	(!TimeLeft())
		{
			InterceptandRange (&ai.unfriendly->World);
			Bool	level=(Bool)(Range>MILES01);

			if (		(Range < RECOGNISERANGE)					  //RDH 26/03/99
					&&	(nationality == ((AirStruc*)ai.unfriendly)->nationality)   //RDH 26/03/99
				)													  //RDH 26/03/99
			{														  //RDH 26/03/99
				Art_Int.BreakOff(this);								  //RDH 26/03/99
//DeadCode CSB 28/04/99					AutoFollowWp();										  //RDH 26/03/99
			}else
			{
				if	(		(Range<RECOGNISERANGE)							//RDH 14/7
						&&	(movecode == AUTO_TRACKINGBOGIE)
					)
				{	//set for combat next frame. Tell all followers to break.
					Art_Int.SpottedUnfriendly(this,(AirStruc*)ai.unfriendly);						//rdh 14/7
				}
				if (Range<COMBATRANGE)
				{	//set for combat next frame. Tell all followers to break.
					Art_Int.AllEngage(this);
				}
				Bool	DoEngage=TRUE;

				InterceptandRange (FindCombatPos());
				if (PitchIntercept>classtype->bestclimbpitch)	//max climb rate//RDH 26Jul96
				{	//IF TOO STEEP make shallow and fix 3d range
					//not for tactician.. he wants to get alt.
			 		PitchIntercept=classtype->bestclimbpitch;		//RDH 26Jul96
//DEADCODE rdh 28/04/99 					if (ai.character!=CHAR_TACTICIAN)
//DEADCODE rdh 28/04/99 						Range-=despos.Y-World.Y;						//JIM 05Jul96
				}

				level&=CalcVelAlt (classtype->cruisevel+100);	//20mph above cruise
				level&=CalcHdgRoll ();

	//remove until we know what we want
	//TempCode RDH 24Jun96 			//	fuel conservation
	//TempCode RDH 24Jun96 			if (Range > MILES05)
	//TempCode RDH 24Jun96 			{
	//TempCode RDH 24Jun96 				if (PitchIntercept < ANGLES_10Deg)
	//TempCode RDH 24Jun96 				{
	//TempCode RDH 24Jun96 					PitchIntercept = ANGLES_10Deg;
	//TempCode RDH 24Jun96 				}
	//TempCode RDH 24Jun96 				if (PitchIntercept > ANGLES_350Deg)
	//TempCode RDH 24Jun96 				{
	//TempCode RDH 24Jun96 					PitchIntercept = ANGLES_350Deg;
	//TempCode RDH 24Jun96 				}
	//TempCode RDH 24Jun96 			}		
				level&=AutoCalcPitch ();
				CalcXYZVel ();
				if 	(	level && Range >  ENGAGERANGE)
//DeadCode CSB 23/06/99						if (Range > RECOGNISERANGE)
//DeadCode CSB 23/06/99							SetManoeuvreTime (THIRTYSECS100);
//DeadCode CSB 23/06/99						else
					{
						SetManoeuvreTime (FIVESECS100);
					}
			}
		}
		NewPosition ();
		SetFlightParams ();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindCombatPos
//Author		Jim Taylor
//Date			Thu 21 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
COORDS3D*	AirStruc::FindCombatPos ()
{
	SLong	desrange=Range,desalt;
	ANGLES	deshdg;
	despos	=	ai.unfriendly->World;

//##
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 //##when unfriendly in formation go for blind spot (ie not right behind unfriendly
//TempCode RDH 27Mar98 	if	(	(eye->ai.manoeuvre == MANOEUVRE_CIRCUMVENT)
//TempCode RDH 27Mar98 			||	(eye->ai.manoeuvre == MANOEUVRE_DIVEANDZOOM)
//TempCode RDH 27Mar98 		)
//TempCode RDH 27Mar98 	{
//TempCode RDH 27Mar98 		go high as possible
//TempCode RDH 27Mar98 		either go behind or up sun
//TempCode RDH 27Mar98 	}else if	(	(eye->ai.manoeuvre == MANOEUVRE_SCATTER)
//TempCode RDH 27Mar98 				||	(eye->ai.manoeuvre == MANOEUVRE_MULTIWAVE)
//TempCode RDH 27Mar98 				)
//TempCode RDH 27Mar98 	{
//TempCode RDH 27Mar98 		go straight towards enemy
//TempCode RDH 27Mar98 		retain alt until last 800m
//TempCode RDH 27Mar98 	}else if	(	(eye->ai.manoeuvre == MANOEUVRE_PINCER)
//TempCode RDH 27Mar98 	{
//TempCode RDH 27Mar98 			go to point defined as rel hdg from trg = desiredhdg, 100m
//TempCode RDH 27Mar98 	}else if	(	(eye->ai.manoeuvre == MANOEUVRE_ROUNDABOUT)
//TempCode RDH 27Mar98 	{
//TempCode RDH 27Mar98 		move in circles gradually approaching trg
//TempCode RDH 27Mar98 		threatlevel = BANDITINENGAGERANGEOFFRIENDLY in higher circle
//TempCode RDH 27Mar98 		if (threatlevel = BANDITINENGAGERANGEOFFRIENDLY)
//TempCode RDH 27Mar98 			check whether to go into combat
//TempCode RDH 27Mar98 	}else
//TempCode RDH 27Mar98 	{// include MANOEUVRE_LINEASTERN, MANOEUVRE_LINEABREAST,  + general
//TempCode RDH 27Mar98 		if (ai.morale  high)
//TempCode RDH 27Mar98 		{
//TempCode RDH 27Mar98 			if (ai.combatskill <= SKILL_REGULAR)
//TempCode RDH 27Mar98 			{
//TempCode RDH 27Mar98 				go for unfriendly
//TempCode RDH 27Mar98 				go for target alt
//TempCode RDH 27Mar98 			}elseif (ai.combatskill <= SKILL_ACE)
//TempCode RDH 27Mar98 			{
//TempCode RDH 27Mar98 				go up sun first or behind
//TempCode RDH 27Mar98 				go for target alt
//TempCode RDH 27Mar98 			}else if (MiG and trg = bomber)
//TempCode RDH 27Mar98 					approach low
//TempCode RDH 27Mar98 			else
//TempCode RDH 27Mar98 				go up sun first or behind, go high
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 		}else
//TempCode RDH 27Mar98 		{
//TempCode RDH 27Mar98 			go high as possible
//TempCode RDH 27Mar98 			if (ai.combatskill <= SKILL_REGULAR)
//TempCode RDH 27Mar98 				go straight towards
//TempCode RDH 27Mar98 			else 
//TempCode RDH 27Mar98 				either go behind or up sun
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 	}
//TempCode RDH 27Mar98 
//TempCode RDH 27Mar98 




	if (Save_Data.gamedifficulty[GD_TACTICALRANGE])			//JIM 22Oct96
	{
		switch	(ai.character)
		{
		case CHAR_CAVALIER:
			if (nationality==NAT_RED)	//my nationality
				deshdg=ANGLES_45Deg;
			else
				deshdg=ANGLES_225Deg;
			desalt=METRES1000;
			desrange=METRES500;
		break;
		case CHAR_TACTICIAN:
			deshdg=((AirStrucPtr)*ai.unfriendly)->hdg-ANGLES_180Deg;		 //32K*6=2KM
//Old_Code PD 10Nov97 			desrange=Math_Lib.AbsSign((SWord)((Angles)(int)(HdgIntercept-deshdg)+ANGLES_180Deg))*6+METRES500;
//Old_Code PD 10Nov97 			deshdg=(Angles)((SWord)deshdg+
//Old_Code PD 10Nov97 				(SWord)((Angles)(HdgIntercept-deshdg)+ANGLES_180Deg)/2);
			desrange=Math_Lib.AbsSign((SWord)(int)((HdgIntercept-deshdg)+ANGLES_180Deg))*6+METRES500;
			deshdg+=(Angles)(((HdgIntercept-deshdg)+ANGLES_180Deg)/2);
			desalt=METRES1000;
			if (World.Y+Range/4-ai.unfriendly->World.Y<desalt)
				desrange+=METRES800;
		break;
		case CHAR_MRAVERAGE:
			deshdg=ANGLES_180Deg-HdgIntercept;
			desrange=METRES500;
			desalt=METRES500;
		break;
		}
		SWord	sinbearing,cosbearing;
		Math_Lib.high_sin_cos(deshdg,sinbearing,cosbearing);
		despos.X += MULSHSIN(sinbearing,desrange,ANGLES_SHIFT);
		despos.Z += MULSHSIN(cosbearing,desrange,ANGLES_SHIFT);
		despos.Y += desalt;
	}
	return (&despos);
}

//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 19Feb99 //Procedure		AutoFollowTakeOffWing
//DeadCode JIM 19Feb99 //Author		R. Hyde 
//DeadCode JIM 19Feb99 //Date			//RDH 27Feb96
//DeadCode JIM 19Feb99 //
//DeadCode JIM 19Feb99 //Description	
//DeadCode JIM 19Feb99 //
//DeadCode JIM 19Feb99 //Inputs		
//DeadCode JIM 19Feb99 //
//DeadCode JIM 19Feb99 //Returns	
//DeadCode JIM 19Feb99 //
//DeadCode JIM 19Feb99 //------------------------------------------------------------------------------
//DeadCode JIM 19Feb99 void AirStruc::AutoTakeOffWing ()
//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 {
//DeadCode JIM 19Feb99 //TempCode RDH 19Jun96 	if (information)
//DeadCode JIM 19Feb99 //TempCode RDH 19Jun96 	{
//DeadCode JIM 19Feb99 //DeadCode RDH 21Jun96 		CopyLeaderSub ();
//DeadCode JIM 19Feb99 //DeadCode RDH 21Jun96 		World = *PositionTakeOffWRTLeader ();
//DeadCode JIM 19Feb99 //TempCode RDH 19Jun96 	}else
//DeadCode JIM 19Feb99 //TempCode RDH 19Jun96 	{
//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 	AirStrucPtr lf;
//DeadCode JIM 19Feb99 	SLong reqvel,groundlevel;
//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 	if (leader==NULL)
//DeadCode JIM 19Feb99 	{
//DeadCode JIM 19Feb99 		lf=fly.leadflight;
//DeadCode JIM 19Feb99 	}else
//DeadCode JIM 19Feb99 	{
//DeadCode JIM 19Feb99 		lf=*leader;
//DeadCode JIM 19Feb99 	}
//DeadCode JIM 19Feb99 	
//DeadCode JIM 19Feb99 	despos = lf->World; 
//DeadCode JIM 19Feb99  
//DeadCode JIM 19Feb99 		groundlevel = Land_Scape.GetGroundLevel(*this); 
//DeadCode JIM 19Feb99   		if ( groundlevel > World.Y)								//RDH 04Sep96
//DeadCode JIM 19Feb99   		{
//DeadCode JIM 19Feb99 			World.Y = groundlevel;
//DeadCode JIM 19Feb99  			reqvel = classtype->maxvel;
//DeadCode JIM 19Feb99   			if (vel < MPH45)
//DeadCode JIM 19Feb99   			{
//DeadCode JIM 19Feb99  				PitchIntercept = ANGLES_0Deg;
//DeadCode JIM 19Feb99   			}else
//DeadCode JIM 19Feb99  			{
//DeadCode JIM 19Feb99  				PitchIntercept = ANGLES_6Deg;
//DeadCode JIM 19Feb99  			}
//DeadCode JIM 19Feb99  
//DeadCode JIM 19Feb99   		}else
//DeadCode JIM 19Feb99   		{
//DeadCode JIM 19Feb99  			reqvel = MPH45;
//DeadCode JIM 19Feb99   			if (vel < MPH45)
//DeadCode JIM 19Feb99 			{
//DeadCode JIM 19Feb99  				PitchIntercept = ANGLES_0Deg;
//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 			}else
//DeadCode JIM 19Feb99 			{
//DeadCode JIM 19Feb99 				InterceptandRange (&despos);
//DeadCode JIM 19Feb99 				SWord	reqdeltahdg;
//DeadCode JIM 19Feb99 				UWord	reqdeltahdg_pos;
//DeadCode JIM 19Feb99 				SWord	reqdeltahdg_sign;
//DeadCode JIM 19Feb99 //DeadCode JIM 21Oct96 				reqdeltahdg = 	(SWord) ((SWord) fly.leadflight->hdg - HdgIntercept);
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 				reqdeltahdg = 	(SWord) ((SWord) lf->hdg - HdgIntercept);
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 				Math_Lib.Pos (reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 				if  ( 	(reqdeltahdg_pos  > ANGLES_60Deg)
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 					||	(World.Y < (groundlevel + FT_500))
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 					)
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 	 			{
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 	 				PitchIntercept = ANGLES_13Deg;
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 	 
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 	 			}else
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 	 			{
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 	 				movecode=AUTO_FOLLOWWP;
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 					manoeuvretime=0;
//DeadCode JIM 19Feb99 //DeadCode RDH 22Oct96 	 			}
//DeadCode JIM 19Feb99 				if  (World.Y < (groundlevel + FT_700))
//DeadCode JIM 19Feb99 	 			{
//DeadCode JIM 19Feb99 	 				PitchIntercept = ANGLES_13Deg;
//DeadCode JIM 19Feb99 	 
//DeadCode JIM 19Feb99 	 			}else
//DeadCode JIM 19Feb99 	 			{
//DeadCode JIM 19Feb99 	 				movecode=AUTO_FOLLOWWP;
//DeadCode JIM 19Feb99 					manoeuvretime=0;
//DeadCode JIM 19Feb99 	 			}
//DeadCode JIM 19Feb99 			} 
//DeadCode JIM 19Feb99   		}
//DeadCode JIM 19Feb99   		AutoCalcPitch ();
//DeadCode JIM 19Feb99  		CalcVelSub (reqvel);
//DeadCode JIM 19Feb99  		CalcXYZVel ();
//DeadCode JIM 19Feb99  		NewPosition ();
//DeadCode JIM 19Feb99  		SetFlightParams ();
//DeadCode JIM 19Feb99  
//DeadCode JIM 19Feb99  
//DeadCode JIM 19Feb99 //TempCode RDH 19Jun96 	}
//DeadCode JIM 19Feb99 }
//DeadCode JIM 19Feb99 

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTakeOffPos
//Author		R. Hyde 
//Date			Tue 28 Nov 1995		//JIM 05/03/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Coords3D*	AirStruc::GetTakeOffPos(UniqueID takeoffID,Coords3D& despos)
{
	if (takeoffID==RunwaySBAND || takeoffID==RunwayEBAND)
	{
		UniqueID homeid=ai.homebase->uniqueID.count;
		if (homeid==UID_Japan)
		{
			despos=ai.homebase->World;
			if (takeoffID==RunwayEBAND)
				despos.Z+=METRES2000;
			despos.Y=METRES1000;								//DAW 27Jun99
			return &despos;											  //JIM 21/05/99
		}
		else
		for (int i=RunwaySBAND;i!=RunwayEBAND;i++,takeoffID=UniqueID(takeoffID+1))
		{
			ItemPtr takeoffitem=*Persons2::ConvertPtrUID(takeoffID);
			if (takeoffitem && takeoffitem->SGT==homeid)
			{
				despos=takeoffitem->World;
//				if (despos.Y==0)
//				{
					if (ai.homebase->World.Y==0)
					{
//						ai.homebase->World.X=42384689;
//						ai.homebase->World.Z=90999080;
						ai.homebase->World.Y=Land_Scape.GetGroundLevel(ai.homebase,NULL,true);
					}
					despos.Y=ai.homebase->World.Y;
//				}
				//need fix for gear height....
				Coords3D w,c1,c2;
				SHAPE.GetContactPoint(this,CT_WHLLEFT,w,c1,c2);
				int delta=c1.Y;//(c1.Y+c2.Y)/2;
				if (classtype->deckangle>ANGLES_5Deg)
					delta-=delta>>2;
				despos.Y-=delta;    //classtype->wheellevel;
				return &despos;
			}
		}
		return NULL;
	}
	else
	{

		ItemPtr takeoffitem=*Persons2::ConvertPtrUID(takeoffID);
		assert(takeoffitem&&"NO ITEM");

		despos=takeoffitem->World;
		takeoffitem=*Persons2::ConvertPtrUID(takeoffitem->SGT);
		assert(takeoffitem&&"NO ASSOC");

		despos.X-=takeoffitem->World.X;
		despos.Z-=takeoffitem->World.Z;

		if (ai.homebase->World.Y==0)
			ai.homebase->World.Y=Land_Scape.GetGroundLevel(ai.homebase,NULL,true);
		despos.X+=ai.homebase->World.X;
		despos.Y=ai.homebase->World.Y;
		despos.Z+=ai.homebase->World.Z;
        Coords3D w,c1,c2;
        SHAPE.GetContactPoint(this,CT_WHLLEFT,w,c1,c2);
        int delta=c1.Y;//(c1.Y+c2.Y)/2;
		if (classtype->deckangle>ANGLES_5Deg)
			delta-=delta>>2;
        despos.Y-=delta;    //classtype->wheellevel;
		return &despos;
	}

//	ERROR - stuff from craig and rod and everybody else

//DeadCode CRAIG 26Feb99 		ai.homebase->World.Y=Land_Scape.GetGroundLevel(ai.homebase,true);
//DeadCode CRAIG 26Feb99 	despos.X+=ai.homebase->World.X;
//DeadCode CRAIG 26Feb99 	despos.Y=ai.homebase->World.Y;
//DeadCode CRAIG 26Feb99 	despos.Z+=ai.homebase->World.Z;
//DeadCode CRAIG 26Feb99 	Coords3D w,c1,c2;
//DeadCode CRAIG 26Feb99 	SHAPE.GetContactPoint(this,CT_WHLLEFT,w,c1,c2);
//DeadCode CRAIG 26Feb99 	int delta=(c1.Y+c2.Y)/2;
//DeadCode CRAIG 26Feb99 	despos.Y+=delta;	//classtype->wheellevel;
//DeadCode RDH 26Feb99 
//DeadCode RDH 26Feb99 	despos=takeoffitem->World;
//DeadCode RDH 26Feb99 	takeoffitem=*Persons2::ConvertPtrUID(takeoffitem->SGT);
//DeadCode RDH 26Feb99 	assert(takeoffitem);
//DeadCode RDH 26Feb99 	despos.X-=takeoffitem->World.X;
//DeadCode RDH 26Feb99 	despos.Z-=takeoffitem->World.Z;
//DeadCode RDH 26Feb99 	assert(ai.homebase);
//DeadCode RDH 26Feb99 
//DeadCode RDH 26Feb99 	if (ai.homebase->World.Y==0)
//DeadCode RDH 26Feb99 		ai.homebase->World.Y=Land_Scape.GetGroundLevel(ai.homebase);
//DeadCode RDH 26Feb99 	despos.X+=ai.homebase->World.X;
//DeadCode RDH 26Feb99 	despos.Y=ai.homebase->World.Y;
//DeadCode RDH 26Feb99 	despos.Z+=ai.homebase->World.Z;
//DeadCode RDH 26Feb99 	despos.Y+=200;	//classtype->wheellevel;

}

////////////////////////////////////////////////////////////////////////
//
// Function:    AutoTakeOff 
// Date:        20/01/99
// Author:      JIM
//
// Description: 
//
//Phases:
//0		Hold until time
//1		Hold until player gone
//2		Move towards TAXI1 at 40m every 15 seconds On reaching TAXI1, phase 5
//
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
//
//8		Hold until player gone
//9		Take off acceleration up runway towards RUNWAY1
//
//10	Climb straight forward for fixed time
//
//11	Slow turn in formation
////////////////////////////////////////////////////////////////////////
bool		AirStruc::playermoving=false;
AirStrucPtr	AirStruc::playernotmovingheldac=NULL;
bool		AirStruc::PlayerStartedMoving()
{
	return	playermoving;
}

AirStrucPtr flight_ctl::leadelt()
{
	if ((originalformpos&InWingMAX)!=2)
		assert(AirStrucPtr(int(this)-int(&AirStrucPtr(NULL)->fly))->position()==2);
	AirStrucPtr scan=leadflight;
	while (scan && &scan->fly.nextflight->fly!=this)
		scan=scan->fly.nextflight;
	return scan;
}


void	AirStruc::HeldACCheck()
{
	if (!playernotmovingheldac)
	{

//DeadCode DAW 28Jun99 		if (_DPlay.Implemented || _Replay.Record)				//AMM 22Jun99
//DeadCode DAW 28Jun99 			_DPlay.NewPlayerNotMovingHeldAC(this->uniqueID.count);//AMM 22Jun99
//DeadCode DAW 28Jun99 		else													//AMM 22Jun99
			playernotmovingheldac=this;
		SetManoeuvreTime(5*SECS100+Math_Lib.rnd(20*SECS100));
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOFLY, MSG_STATUS, VOICE_TOWER, Persons2::PlayerGhostAC, Persons2::PlayerGhostAC));
 	
	 	if(Save_Data.flightdifficulty [FD_WINDGUSTS])
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED_GUSTS, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, Persons2::PlayerGhostAC, Persons2::PlayerGhostAC));
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_ALTWIND_BEARINGNO_SPEED_GUSTS, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, Persons2::PlayerGhostAC, Persons2::PlayerGhostAC));
		}
		else
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, Persons2::PlayerGhostAC, Persons2::PlayerGhostAC));
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_ALTWIND_BEARINGNO_SPEED, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, Persons2::PlayerGhostAC, Persons2::PlayerGhostAC));
		}
	}
	if (this==playernotmovingheldac)
	{  
		if (PlayerStartedMoving())
			SetManoeuvreTime(0);
		else
		if (!TimeLeft())
		{
			//silly mesage
			AirStrucPtr pl=Persons2::PlayerGhostAC;
			switch (Math_Lib.rnd(10))
			{
			case 0:
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOFLY, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, pl, pl));
			break;
			case 1:
			case 6:
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARED, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, pl, pl));
			break;
			case 2:
			case 7:
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_HAVEPROBLEM, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, pl, pl));
			break;
			case 3:
			case 8:
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARRUNWAY, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, pl, pl));
			break;
			case 4:
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_GETMOVING, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, pl, pl));
			break;
			case 5:
			case 9:
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_READYFORTAKEOFF, MSG_STATUSRESPONSE_DELAY_LP_RPT, playernotmovingheldac, pl, pl));
			break;
			}

			SetManoeuvreTime(5*SECS100+Math_Lib.rnd(20*SECS100));
		}


	}

}
//////////////////////////////////////////////////////////////////////
//
// Function:    AutoTakeOff 
// Date:		29/03/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////



void AirStruc::AutoTakeOff ()
{
//DeadCode CSB 17/05/99	////////////////////////////////////////////
//DeadCode CSB 17/05/99	//**	TESTCODE	//CSB 21/04/99		**//
//DeadCode CSB 17/05/99	////////////////////////////////////////////	
//DeadCode CSB 24/05/99		if(Key_Tests.KeyHeld3d (RESTARTENGINE))
//DeadCode CSB 24/05/99			if(PlayerInGroup())
//DeadCode CSB 24/05/99			{
//DeadCode CSB 24/05/99				AirStrucPtr grplead = FindGroupLeader();
//DeadCode CSB 24/05/99	
//DeadCode CSB 24/05/99				for (AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
//DeadCode CSB 24/05/99					for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
//DeadCode CSB 24/05/99					{
//DeadCode CSB 24/05/99						foll->movecode = AUTO_LANDING;
//DeadCode CSB 24/05/99						foll->ai.ManStep = 0;
//DeadCode CSB 24/05/99						foll->SetManoeuvreTime(0);
//DeadCode CSB 24/05/99						foll->waypoint = NULL;
//DeadCode CSB 24/05/99					}		
//DeadCode CSB 24/05/99				return;
//DeadCode CSB 24/05/99			}
//DeadCode CSB 17/05/99	////////////////////////////////////////////
//DeadCode CSB 17/05/99	//**	TESTCODE	//CSB 21/04/99		**//
//DeadCode CSB 17/05/99	////////////////////////////////////////////	

		
//	const	UniqueID	UID_TAXI1=(UniqueID)-1;
//	const	UniqueID	UID_TAXI0=(UniqueID)-2;
//	const	UniqueID	UID_TAXIL=(UniqueID)-3;
//	const	UniqueID	UID_TAXIW=(UniqueID)-4;
//	const	UniqueID	UID_RUNWAY0=(UniqueID)-5;
//	const	UniqueID	UID_RUNWAY1=(UniqueID)-6;

	const int flightnum = (formpos&InFormMAX);
	const int flightpos = position();

//DeadCode CSB 22/04/99	PrintVar(20 * flightnum, 3 + flightpos, "%.0f ", (FP)flightpos);
//DeadCode CSB 22/04/99	PrintVar(20 * flightnum, 8 + flightpos, "V %.1f ", (FP)(vel * 0.1));
//DeadCode CSB 22/04/99	PrintVar(22 * flightnum, 3 + flightpos, "T %.2f ", (FP)(manoeuvretime * 0.01));	
//DeadCode CSB 22/04/99	switch(ai.ManStep)
//DeadCode CSB 22/04/99	{
//DeadCode CSB 22/04/99		case TO_LATERGROUPTIMER:	PrintString(10 + 20 * flightnum, 3 + flightpos, "LATERGROUPTIMER ");	break;
//DeadCode CSB 22/04/99		case TO_LATERGROUPPLAYER:	PrintString(10 + 20 * flightnum, 3 + flightpos, "LATERGROUPPLAYER ");	break;
//DeadCode CSB 22/04/99		case TO_LATERGROUPTAXI:		PrintString(10 + 20 * flightnum, 3 + flightpos, "LATERGROUPTAXI ");		break;
//DeadCode CSB 22/04/99		case TO_LATERFLIGHTPLAYER:	PrintString(10 + 20 * flightnum, 3 + flightpos, "LATERFLIGHTPLAYER ");	break;
//DeadCode CSB 22/04/99		case TO_LATERFLIGHTSLIPWAY:	PrintString(10 + 20 * flightnum, 3 + flightpos, "LATERFLIGHTSLIPWAY ");	break;
//DeadCode CSB 22/04/99		case TO_LATERGROUPSLIPWAY:	PrintString(10 + 20 * flightnum, 3 + flightpos, "LATERGROUPSLIPWAY ");	break;
//DeadCode CSB 22/04/99		case TO_RUNWAYTURN:			PrintString(10 + 20 * flightnum, 3 + flightpos, "RUNWAYTURN ");			break;
//DeadCode CSB 22/04/99		case TO_RUNWAYTAXI:			PrintString(10 + 20 * flightnum, 3 + flightpos, "RUNWAYTAXI ");			break;
//DeadCode CSB 22/04/99		case TO_PLAYERPLAYER:		PrintString(10 + 20 * flightnum, 3 + flightpos, "PLAYERPLAYER ");		break;
//DeadCode CSB 22/04/99		case TO_RUNWAYPOWER:		PrintString(10 + 20 * flightnum, 3 + flightpos, "RUNWAYPOWER ");		break;
//DeadCode CSB 22/04/99		case TO_RUNWAYCLIMB:		PrintString(10 + 20 * flightnum, 3 + flightpos, "RUNWAYCLIMB ");		break;
//DeadCode CSB 22/04/99		case TO_CLIMBTURN:			PrintString(10 + 20 * flightnum, 3 + flightpos, "CLIMBTURN ");			break;
//DeadCode CSB 22/04/99		case TO_DIRTYAFWPW:			PrintString(10 + 20 * flightnum, 3 + flightpos, "DIRTYAFWPW ");			break;
//DeadCode CSB 22/04/99	}
	
	const int	ACSTEP=METRES20;
	const int	BUDDYSTEP=METRES15;
	const int	FLSTEP=ACSTEP+ACSTEP;
	const int	TAXIVEL=80;	//mm/cs = 18mph
	const int	MAXPERFRAME=FT_1;
	switch (ai.ManStep)
	{
	case TO_LATERGROUPTIMER:
	{	//aircraft held until programmed time
		if (!TimeLeft())
			if (ai.manoeuvre.value)
			{
				ai.manoeuvre.value--;		//256 lots of 11 mins = 30+ hrs
				SetManoeuvreTime(65535);
			}
			else
				ai.ManStep=TO_LATERGROUPPLAYER;
	}
	break;

	case TO_LATERGROUPPLAYER:
	{	//later groups held until player moves
		if (PlayerStartedMoving())
		{
			ai.ManStep=TO_LATERGROUPTAXI;
			manoeuvretime=0;
		}
		HeldACCheck();

	}
	break;
	
	case TO_LATERGROUPTAXI:	
	{	//main taxiway
		Coords3D* despos=GetTakeOffPos(UID_TAXI1);
		if (!TimeLeft())
		{

			if (flightpos==0 || flightpos==2)	//elt leaders only
				if (Math_Lib.DistAbsSum(World.X-despos->X,World.Z-despos->Z)>METRES02)
				{
					vel=10;	//10 moves before position is checked	//pythag distance=10
					if (Math_Lib.DistAbsSum(World.X-despos->X,World.Z-despos->Z)>(ACSTEP*18/10))
						SetManoeuvreTime(15*SECS100);
					else	//only 20m left to travel, then turn
						SetManoeuvreTime(SECS100*150/100);
				}
				else
				{
					velhori=0;
					vel=10;
					ai.ManStep=TO_LATERGROUPSLIPWAY;
				}
			else
			{
				ai.ManStep=(UByte)AirStrucPtr(leader)->ai.ManStep;
				manoeuvretime=AirStrucPtr(leader)->manoeuvretime;
			}
		}
		else	//want to travel about 40m in 5 secs = 8m/s=20mph=16cm/fr=80mm/cs
			if (flightpos==0 || flightpos==2)	//elt leaders only
				if (vel)
				{
	 				InterceptandRange (despos);
					if (velhori)
					{	//travelling forward
						if (vel>1)		//force a certain number of frames
							vel--;
						else
						if (flightpos==0)
							if ((Range%(FLSTEP))<MAXPERFRAME)	 //2 frames
								vel=0;
							else;
						else
							if (Range<MAXPERFRAME || ((Range+ACSTEP)%FLSTEP)<MAXPERFRAME)
							{
								vel=0;
							}
						hdg=HdgIntercept;
					}
					else
					{
						//4sec for 90 deg = 22.5deg/sec= 0.5 deg per frame
						//turning circle for 8m/s=20.5m - wingman wobbles on spot if 20m away
						if (hdg-HdgIntercept>ANGLES_ThirdDeg)
							hdg-=ANGLES_ThirdDeg;
						else
						if (HdgIntercept-hdg>ANGLES_HalfDeg)
							hdg+=ANGLES_HalfDeg;
						else
						{
							hdg=HdgIntercept;
							velhori=TAXIVEL;
						}
					}
					SWord	sin_hdg, cos_hdg;
					Math_Lib.high_sin_cos (hdg, sin_hdg, cos_hdg);
					{
						int reqvel=TAXIVEL;
						if (manoeuvretime>12*SECS100)
							reqvel>>=1;
						velx = (SWord)  reqvel* sin_hdg / ANGLES_FRACT;
						velz = (SWord)	reqvel* cos_hdg / ANGLES_FRACT;
						vely=0;
					}
					NewPosition();
				}
				else
					;
			else	//wingman
				if (leader->vel)
					if (leader->velhori)	//leader travelling straight, wingman alongside
					{
						velx=leader->velx;
						velz=leader->velz;
						hdg=leader->hdg;
						NewPosition();
					}
					else
					{	//leader turning& moving forward at 16 cm per frame		
						//wingman is placed at 90 deg to vel vector
						//vel = 80, range=2000 - mul by 25
						hdg=leader->hdg;
						World.X=leader->World.X+leader->velz*BUDDYSTEP/TAXIVEL;
						World.Z=leader->World.Z-leader->velx*BUDDYSTEP/TAXIVEL;
						World.Y=leader->World.Y;
						uniqueID.changed=TRUE;
					}
	}
	break;
	
	case TO_LATERFLIGHTPLAYER:
	{	//later flights held until player moves
		if (PlayerStartedMoving())
		{
			manoeuvretime=0;
			ai.ManStep=TO_LATERFLIGHTSLIPWAY;
		}
		HeldACCheck();

	}
	break;
	
	case TO_LATERFLIGHTSLIPWAY:	
	{	//later flights move down slipway
		//identical to phase 2!!!
		Coords3D* despos=GetTakeOffPos(UID_TAXI0);
		if (!TimeLeft())
		{

			if (flightpos==0 || flightpos==2)	//elt leaders only
				if (Math_Lib.DistAbsSum(World.X-despos->X,World.Z-despos->Z)>METRES02)
				{
					vel=10;	//10 moves before position is checked	//pythag distance=10
					if (Math_Lib.DistAbsSum(World.X-despos->X,World.Z-despos->Z)>METRES35)
						SetManoeuvreTime(15*SECS100);
					else	//only 20m left to travel, then turn
						SetManoeuvreTime(SECS100*180/100);
				}
				else
				{
					velhori=0;
					vel=10;
					ai.ManStep=TO_RUNWAYTURN;
					SetManoeuvreTime(0);
					if( (flightpos==0) && (PlayerInGroup()) )	//either says it to himself or specifically to player
					{
						AirStrucPtr buddy = NULL;
						buddy = FindBuddy();
						if(buddy)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MOVETOACTIVE, MSG_MOVETOACTIVE, this, NULL, buddy));
					}
				}
			else
			{						  
				if (ai.ManStep==Leader()->ai.ManStep)
					manoeuvretime=AirStrucPtr(leader)->manoeuvretime;
				else
				{
					ai.ManStep=(UByte)Leader()->ai.ManStep;
					SetManoeuvreTime(SECS100*50/100);

				}
			}
		}
		else	//want to travel about 40m in 5 secs = 8m/s=20mph=16cm/fr=80mm/cs
			if (flightpos==0 || flightpos==2)	//elt leaders only
				if (vel)
				{
	 				InterceptandRange (despos);
					if (velhori)
					{	//travelling forward
						if (vel>1)		//force a certain number of frames
							vel--;
						else
						if (flightpos==0)
							if ((Range%(FLSTEP))<MAXPERFRAME)	 //2 frames
								vel=0;
							else;
						else
							if (Range<MAXPERFRAME || ((Range+ACSTEP)%FLSTEP)<MAXPERFRAME)
							{
								vel=0;
							}
						hdg=HdgIntercept;
					}
					else
					{
						//4sec for 90 deg = 22.5deg/sec= 0.5 deg per frame
						//turning circle for 8m/s=20.5m - wingman wobbles on spot if 20m away
						if (hdg-HdgIntercept>ANGLES_HalfDeg)
							hdg-=ANGLES_HalfDeg;
						else
						if (HdgIntercept-hdg>ANGLES_HalfDeg)
							hdg+=ANGLES_HalfDeg;
						else
						{
							hdg=HdgIntercept;
							velhori=TAXIVEL;
						}
					}
					SWord	sin_hdg, cos_hdg;
					Math_Lib.high_sin_cos (hdg, sin_hdg, cos_hdg);

					{
						int reqvel=TAXIVEL;
						if (manoeuvretime>12*SECS100)
							reqvel>>=1;
						velx = (SWord)  reqvel* sin_hdg / ANGLES_FRACT;
						velz = (SWord)	reqvel* cos_hdg / ANGLES_FRACT;
						vely=0;
					}
					NewPosition();
				}
				else
					;
			else	//wingman
				if (leader->vel)
					if (leader->velhori)	//leader travelling straight, wingman alongside
					{
						velx=leader->velx;
						velz=leader->velz;
						hdg=leader->hdg;
						NewPosition();
					}
					else
					{	//leader turning& moving forward at 16 cm per frame		
						//wingman is placed at 90 deg to vel vector
						//vel = 80, range=2000 - mul by 25
						hdg=leader->hdg;
						World.X=leader->World.X+leader->velz*BUDDYSTEP/TAXIVEL;
						World.Z=leader->World.Z-leader->velx*BUDDYSTEP/TAXIVEL;
						World.Y=leader->World.Y;
						uniqueID.changed=TRUE;
					}
	}
	break;
	
	case TO_LATERGROUPSLIPWAY:	
	{	//later groups travelling down slipway
		if (flightpos==0 || flightpos==2)	//elt leaders only
			if (vel)
			{
				Coords3D* despos=GetTakeOffPos(UID_TAXI0);
	 			InterceptandRange (despos);
				if (velhori)
				{	//travelling forward
					if (flightpos==0)
						if (Range<MAXPERFRAME)	 //2 frames
							vel=0;
						else;
					else
						if (Range<MAXPERFRAME)
						{
							vel=0;
						}
					hdg=HdgIntercept;
				}
				else
				{
					//4sec for 90 deg = 22.5deg/sec= 0.5 deg per frame
					//turning circle for 8m/s=20.5m - wingman wobbles on spot if 20m away
					if (hdg-HdgIntercept>ANGLES_HalfDeg)
						hdg-=ANGLES_HalfDeg;
					else
					if (HdgIntercept-hdg>ANGLES_HalfDeg)
						hdg+=ANGLES_HalfDeg;
					else
					{
						hdg=HdgIntercept;
						velhori=TAXIVEL;
					}
				}
				SWord	sin_hdg, cos_hdg;
				Math_Lib.high_sin_cos (hdg, sin_hdg, cos_hdg);
					{
						int reqvel=TAXIVEL;
						if (manoeuvretime>12*SECS100)
							reqvel>>=1;
						velx = (SWord)  reqvel* sin_hdg / ANGLES_FRACT;
						velz = (SWord)	reqvel* cos_hdg / ANGLES_FRACT;
						vely=0;
					}
				NewPosition();
			}
			else
			{
				ai.ManStep=TO_RUNWAYTURN;	//go to next phase regardless!
				SetManoeuvreTime(SECS100);
			}
		else	//wingman
			if (leader->vel)
				if (leader->velhori)	//leader travelling straight, wingman alongside
				{
					velx=leader->velx;
					velz=leader->velz;
					hdg=leader->hdg;
					NewPosition();
				}
				else
				{	//leader turning& moving forward at 16 cm per frame		
					//wingman is placed at 90 deg to vel vector
					//TAXIVEL = 80, ACSTEP=2000 --> mul by 25
					hdg=leader->hdg;
					World.X=leader->World.X+leader->velz*BUDDYSTEP/TAXIVEL;
					World.Z=leader->World.Z-leader->velx*BUDDYSTEP/TAXIVEL;
					World.Y=leader->World.Y;
					uniqueID.changed=TRUE;
				}
			else
			{
				ai.ManStep=TO_RUNWAYTURN;	//go to next phase regardless!
				SetManoeuvreTime(SECS100);
			}


	}
	break;
	
	case TO_RUNWAYTURN:	//leader moves to leader spot
	{	//setting to position
		if (!TimeLeft())	//DON'T move until time gone!
		{
			Coords3D* despos;

			if (flightpos<2)
				despos=GetTakeOffPos(UID_TAXIL);
			else
				despos=GetTakeOffPos(UID_TAXIE);
			InterceptandRange (despos);
			if (Range<MAXPERFRAME+(flightpos&1)*METRES20)
			{
				velx=0;
				vely=0;
				velz=0;
				ai.ManStep=TO_RUNWAYTAXI;
//DeadCode CSB 17/06/99					if(flightpos == 0)
//DeadCode CSB 17/06/99						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOFLY, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, this, Persons2::PlayerGhostAC));
			}
			else
			{
				//4sec for 90 deg = 22.5deg/sec= 0.5 deg per frame
				//turning circle for 8m/s=20.5m - wingman wobbles on spot if 20m away

				int taxivel=TAXIVEL;
				if (hdg-HdgIntercept>ANGLES_HalfDeg)
					if (leader)
					{
						hdg-=ANGLES_ThirdDeg;
					}
					else
						hdg-=ANGLES_HalfDeg;
				else
				if (HdgIntercept-hdg>ANGLES_HalfDeg)
					if (!leader)
					{
						hdg+=ANGLES_ThirdDeg;
						taxivel+=taxivel;
					}
					else
						hdg+=ANGLES_HalfDeg;
				else
				{
					hdg=HdgIntercept;
					if (!leader)
						taxivel+=taxivel/4;
				}
				SWord	sin_hdg, cos_hdg;
				Math_Lib.high_sin_cos (hdg, sin_hdg, cos_hdg);
				velx = (SWord)  taxivel * sin_hdg / ANGLES_FRACT;
				velz = (SWord)  taxivel * cos_hdg / ANGLES_FRACT;
				vely=0;
				NewPosition();
			}
		}
		else
		{
				SWord	sin_hdg, cos_hdg;
				Math_Lib.high_sin_cos (hdg, sin_hdg, cos_hdg);
				velx = (SWord)  TAXIVEL * sin_hdg / ANGLES_FRACT;
				velz = (SWord)  TAXIVEL * cos_hdg / ANGLES_FRACT;
				vely=0;
				NewPosition();
		}
	}
	break;
	
	case TO_RUNWAYTAXI:		 //roll forward on runway
	{	//setting to position
		if (flightpos==0)
		{
			if (	(!fly.nextflight || fly.nextflight->ai.ManStep==TO_RUNWAYTAXI)
				&&	(!follower || Follower()->ai.ManStep==TO_RUNWAYTAXI)
				&&	(!fly.nextflight || !fly.nextflight->follower || fly.nextflight->Follower()->ai.ManStep==TO_RUNWAYTAXI)
				)
			{
//DeadCode MS 11Apr99 				Coords3D* despos=GetTakeOffPos(UID_RUNWAY0);
				Coords3D*	despos=GetTakeOffPos(UniqueID(RunwaySBAND));
				InterceptandRange (despos);
				if (Range<MAXPERFRAME)
				{
					despos=GetTakeOffPos(UniqueID(RunwayEBAND));//MS 11Apr99
//DeadCode MS 11Apr99 					despos=GetTakeOffPos(UID_RUNWAY1);	//belts and braces!
					InterceptandRange (despos);
					hdg=HdgIntercept;
					ai.ManStep=TO_RUNWAYPOWER;
					SetManoeuvreTime(SECS100/2);	//how long to 'blast'
					if(PlayerInGroup())
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOFLY, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, this, Persons2::PlayerGhostAC));
				}

				//4sec for 90 deg = 22.5deg/sec= 0.5 deg per frame
				//turning circle for 8m/s=20.5m - wingman wobbles on spot if 20m away
				if (hdg-HdgIntercept>ANGLES_HalfDeg)
					hdg-=ANGLES_HalfDeg;
				else
				if (HdgIntercept-hdg>ANGLES_HalfDeg)
					hdg+=ANGLES_HalfDeg;
				else
				{
					hdg=HdgIntercept;
				}
				SWord	sin_hdg, cos_hdg;
				Math_Lib.high_sin_cos (hdg, sin_hdg, cos_hdg);
				velx = (SWord)  TAXIVEL * sin_hdg / ANGLES_FRACT;
				velz = (SWord)  TAXIVEL * cos_hdg / ANGLES_FRACT;
				vely=0;
				NewPosition();
			}
		}
		else
		{
			AirStrucPtr lead=Leader();
			if (!lead && flightpos==2)
				lead=fly.leadelt();
			if (!lead)
			{
				ai.ManStep=TO_RUNWAYPOWER;
				SetManoeuvreTime(SECS100/2);	//how long to 'blast'
			}
			if (lead->ai.ManStep==ai.ManStep)
			{
				hdg=lead->hdg;
				velx=lead->velx;
				vely=lead->vely;
				velz=lead->velz;
			}
			else
			if (lead->ai.ManStep>ai.ManStep)
			{
				ai.ManStep=(UByte)lead->ai.ManStep;
				manoeuvretime=lead->manoeuvretime;
				hdg=lead->hdg;
			}
			NewPosition();
		}
	}
	break;
	
	case TO_PLAYERPLAYER:
	{	//guys in our flight waiting to take off
		if (PlayerStartedMoving())
		{
			SetManoeuvreTime(SECS100/2);
			ai.ManStep=TO_RUNWAYPOWER;
		}
		HeldACCheck();

	}
	break;
	
	case TO_RUNWAYPOWER:
	{	//booring bit just go whooshing forward at ever increasing velocity
		if( (vel > 0) && (vel < 1.4 * classtype->landingspeed) )
		{
			SLong Accel = CalcAccel(1.4 * classtype->landingspeed);
			AddAccel2Vel(Accel);
		}	
		else if(vel == 0)
			if(Math_Lib.rnd() < 32768) vel = 1;
			
		else
			TimeLeft();

		CalcXYZVel ();
 		NewPosition ();
 		SetFlightParams ();
		
		Coords3D* despos;
		despos=GetTakeOffPos(UniqueID(RunwaySBAND));
		InterceptandRange (despos);

		if(Range < METRES600)
		{
//DeadCode CSB 09/06/99				if((Range > METRES100) && (pitch > ANGLES_0Deg))
//DeadCode CSB 09/06/99					pitch -= (Angles)(10 * Timer_Code.FRAMETIME);
//DeadCode CSB 09/06/99				fly.cpitch = ANGLES_0Deg;
		}
		else
		{
			if(pitch < ANGLES_10Deg)
			{
				pitch += (Angles)(10 * Timer_Code.FRAMETIME);
				if(pitch > ANGLES_10Deg)
					pitch = ANGLES_10Deg;
			}

			if(pitch > ANGLES_10Deg)
			{
				pitch -= (Angles)(2 * Timer_Code.FRAMETIME);
				if(pitch < ANGLES_10Deg)
					pitch = ANGLES_10Deg;
			}
			FP fdeckang = (ANGLES)classtype->deckangle;
			FP fpitch   = pitch;
			FP f_10Deg  = ANGLES_10Deg;
			FP fract = (fpitch - fdeckang) / (f_10Deg - fdeckang);
			if(fract > 0.5)
				fly.cpitch = (Angles)((SWord)((2.0 * fract - 1.0) * ANGLES_10Deg));
			else
				fly.cpitch = ANGLES_0Deg;
		
			if(pitch == ANGLES_10Deg)
			{
				ai.ManStep=TO_RUNWAYCLIMB;
				SetManoeuvreTime(TO_NORMCLIMBTIME);
			}
		}

//DEADCODE CSB 13/05/99			if(pitch >= ANGLES_10Deg && Range>METRES600)
//DEADCODE CSB 13/05/99			{
//DEADCODE CSB 13/05/99				ai.ManStep=TO_RUNWAYCLIMB;
//DEADCODE CSB 13/05/99				SetManoeuvreTime(TO_NORMCLIMBTIME);
//DEADCODE CSB 13/05/99			}

	}
	break;
	
	case TO_RUNWAYCLIMB:
	{	//climb
		if(manoeuvretime >= TO_MINCLIMBTIME) 
		{
			 TimeLeft();
			 if (manoeuvretime <TO_MINCLIMBTIME)
			 {
				fly.pModel->SetGearAnimPos(this, ANIM_GEAR_AUTO);
			 }
		}
		else
			if (!TimeLeft())
			{
				if(flightpos == 0)
				{
					ai.ManStep = TO_CLIMBTURN;
					SLong NumFlights = CountGroup() / 4;
					SLong SlowClimbTime = ( (SLong)TO_TURNCLIMBTIME * (NumFlights - 1) ) / 3;
					SetManoeuvreTime(SlowClimbTime);	//If lead flight, should count flights following and set "slow" time 
				}
				else
				{
					ai.ManStep = TO_DIRTYAFWPW;
					SetManoeuvreTime(0);
				}
			}

//DeadCode CSB 12/02/99			PitchIntercept=ANGLES_2Deg;
		if (flightpos==0 || manoeuvretime>TO_WINGCLIMBTIME)
		{
			PitchIntercept = ANGLES_5Deg;

			if(pitch < PitchIntercept)
				pitch += (Angles)(10 * Timer_Code.FRAMETIME);
			if(pitch > PitchIntercept)
				pitch -= (Angles)(10 * Timer_Code.FRAMETIME);
			
			fly.cpitch = pitch;
//DeadCode CSB 22/04/99				AutoCalcPitch ();
//DeadCode CSB 12/02/99	 		CalcVelAlt (2*classtype->minvel+20*4-flightpos*20);
	 		CalcVelAlt (1.5 * classtype->landingspeed);
		 	CalcXYZVel ();
 			NewPosition ();
	 		SetFlightParams ();
		}
		else
		{
			Coords3D*	dp;
			AirStrucPtr lf = FindLeadCandidate();
			if(!lf)
			{
				movecode = AUTO_FOLLOWWP;
				AutoFollowWp();
				SetManoeuvreTime(0);
				fly.pModel->SetGearAnimPos(this, ANIM_GEAR_AUTO);
				SHAPE.NavigationLightsActive(this, FALSE);
				break;
			}

			InterceptandRange (dp=PositionWRTLeader (lf));
			if(dp->Y > ai.homebase->World.Y + METRES10)
			{
				if((hdg - HdgIntercept + ANGLES_45Deg << ANGLES_90Deg) || (Range > 50000))	//CSB 20/04/99	
				{
					if (manoeuvretime >= TO_MINCLIMBTIME) 
						fly.pModel->SetGearAnimPos(this, ANIM_GEAR_AUTO);
					ai.ManStep=TO_DIRTYAFWPW;
					SetManoeuvreTime(0);
					AutoFollowWpWing(lf);
				}
				else
					if(SideSlide(lf))
					{
						if (manoeuvretime >= TO_MINCLIMBTIME) 
							fly.pModel->SetGearAnimPos(this, ANIM_GEAR_AUTO);
						ai.ManStep=TO_DIRTYAFWPW;
						SetManoeuvreTime(0);
					}
			}
			else
			{
				PitchIntercept = ANGLES_5Deg;
				AutoCalcPitch ();
		 		CalcVelAlt (1.4 * classtype->landingspeed);
				CalcXYZVel ();
 				NewPosition ();
		 		SetFlightParams ();
			}
		}
	}
	break;
	
	case TO_CLIMBTURN:
	{	//turn			 //Only Flight leaders should be in this code	//CSB 19/04/99	
		Coords3D*	dp;
		InterceptandRange (dp=FindDesPos ());
		SWord deshdg = HdgIntercept - hdg;
		if((hdg != HdgIntercept) || (roll != ANGLES_0Deg))
		{
			CalcHdgRollLimited(-deshdg);
			if( roll > ANGLES_45Deg) roll = ANGLES_45Deg;
			if(-roll > ANGLES_45Deg) {roll = ANGLES_45Deg;	roll = -roll;}
		}												  
		
		PitchIntercept = ANGLES_5Deg;

		AutoCalcPitch ();
		int flightnum = (formpos&InFormMAX);
		
		if(flightnum == 0)
		{
			CalcVelAlt(1.5 * classtype->landingspeed); 	//group leader slows down to let other flights catch up
			if(!TimeLeft())
			{
				movecode = AUTO_FOLLOWWP;
				SetManoeuvreTime(0);

				if((!formpos) && (nationality==NAT_RED))
				{
					if (World.Z>Persons2::ConvertPtrUID(UID_AfRdSinanju)->World.Z)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MIGSLAUNCHEDANTUNG, MSG_LAUNCHMIGSREPORTED, VOICE_DENTIST, this, Persons2::PlayerGhostAC));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MIGSLAUNCHED, MSG_LAUNCHMIGSREPORTED, VOICE_DENTIST, this, Persons2::PlayerGhostAC));
				}
			}
		}
		else
		{
			CalcVelAlt();	//other flights go at max possible speed to try to catch up
			if((deshdg < ANGLES_1Deg) && (-deshdg < ANGLES_1Deg))
			{
				ai.ManStep = TO_DIRTYAFWPW;
				SetManoeuvreTime(0);
			}
		}

 		CalcXYZVel ();
		NewPosition ();
		SetFlightParams ();
	}
	break;
		
//DeadCode CSB 19/04/99			if (flightpos!=0)
//DeadCode CSB 19/04/99			{
//DeadCode CSB 19/04/99				if (flightpos==2)
//DeadCode CSB 19/04/99				{
//DeadCode CSB 19/04/99					AirStrucPtr l=fly.leadelt();
//DeadCode CSB 19/04/99					if (l->movecode!=AUTO_TAKEOFF)
//DeadCode CSB 19/04/99						movecode=l->movecode;
//DeadCode CSB 19/04/99					if (l->World.Y-l->ai.homebase->World.Y<METRES50)
//DeadCode CSB 19/04/99						aslead=true;
//DeadCode CSB 19/04/99					else
//DeadCode CSB 19/04/99						aslead=false;
//DeadCode CSB 19/04/99				}
//DeadCode CSB 19/04/99				else
//DeadCode CSB 19/04/99				{
//DeadCode CSB 19/04/99					if (Leader()->movecode!=AUTO_TAKEOFF)
//DeadCode CSB 19/04/99						movecode=Leader()->movecode;
//DeadCode CSB 19/04/99					if (Leader()->World.Y-Leader()->ai.homebase->World.Y<METRES50)
//DeadCode CSB 19/04/99						aslead=true;
//DeadCode CSB 19/04/99					else
//DeadCode CSB 19/04/99						aslead=false;
//DeadCode CSB 19/04/99				}
//DeadCode CSB 19/04/99			}
//DeadCode CSB 19/04/99			else
//DeadCode CSB 19/04/99				aslead=true;
//DeadCode CSB 19/04/99			if (aslead)
//DeadCode CSB 19/04/99			{
//DeadCode CSB 19/04/99				Coords3D*	dp;
//DeadCode CSB 19/04/99				InterceptandRange (dp=FindDesPos ());
//DeadCode CSB 19/04/99	
//DeadCode CSB 19/04/99				Angles deshdg = ANGLES_30Deg;
//DeadCode CSB 19/04/99	
//DeadCode CSB 19/04/99				int flightnum=(formpos&InFormMAX);
//DeadCode CSB 19/04/99				//Craig to write and tune:
//DeadCode CSB 19/04/99				//if (alsead)
//DeadCode CSB 19/04/99				//	Turn both ways
//DeadCode CSB 19/04/99				//	If not lead flight 
//DeadCode CSB 19/04/99				//	{	if are on course
//DeadCode CSB 19/04/99				//			try to form up with leader by calling AutoFollowWPWing
//DeadCode CSB 19/04/99				//		if leadflight not on autotakeoff
//DeadCode CSB 19/04/99				//			switch to AFWP
//DeadCode CSB 19/04/99				//else
//DeadCode CSB 19/04/99				//	AFWPW
//DeadCode CSB 19/04/99	//TEMPCODE JIM 11/04/99 			if (flightpos==0)
//DeadCode CSB 19/04/99								
//DeadCode CSB 19/04/99	
//DeadCode CSB 19/04/99	
//DeadCode CSB 19/04/99	
//DeadCode CSB 19/04/99	
//DeadCode CSB 19/04/99					if (hdg-HdgIntercept<<ANGLES_10Deg)	//within 30 degrees of course
//DeadCode CSB 19/04/99					{
//DeadCode CSB 19/04/99						if (nationality==NAT_RED)
//DeadCode CSB 19/04/99						{
//DeadCode CSB 19/04/99							if (World.Z>Persons2::ConvertPtrUID(UID_AfRdSinanju)->World.Z)
//DeadCode CSB 19/04/99								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MIGSLAUNCHEDANTUNG, MSG_LAUNCHMIGSREPORTED, VOICE_DENTIST, this, Persons2::PlayerGhostAC));
//DeadCode CSB 19/04/99							else
//DeadCode CSB 19/04/99								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MIGSLAUNCHED, MSG_LAUNCHMIGSREPORTED, VOICE_DENTIST, this, Persons2::PlayerGhostAC));
//DeadCode CSB 19/04/99						}
//DeadCode CSB 19/04/99						
//DeadCode CSB 19/04/99						deshdg=ANGLES_1Deg;
//DeadCode CSB 19/04/99					}
//DeadCode CSB 19/04/99					
//DeadCode CSB 19/04/99	
//DeadCode CSB 19/04/99					if (!TimeLeft())	//should always be on course before time runs out!
//DeadCode CSB 19/04/99					{
//DeadCode CSB 19/04/99						if(manoeuvretime >= TO_MINCLIMBTIME) 
//DeadCode CSB 19/04/99							fly.pModel->SetGearAnimPos(this, ANIM_GEAR_AUTO);
//DeadCode CSB 19/04/99						
//DeadCode CSB 19/04/99						for (AirStrucPtr fllead=this;fllead;fllead=fllead->fly.nextflight)
//DeadCode CSB 19/04/99							for (AirStrucPtr follower=fllead;follower;follower=follower->Follower())
//DeadCode CSB 19/04/99							{
//DeadCode CSB 19/04/99								follower->movecode=AUTO_FOLLOWWP;
//DeadCode CSB 19/04/99								follower->SetManoeuvreTime(0);
//DeadCode CSB 19/04/99							}
//DeadCode CSB 19/04/99					}
//DeadCode CSB 19/04/99				CalcHdgRollLimited(deshdg);
//DeadCode CSB 19/04/99	
//DeadCode CSB 19/04/99				PitchIntercept = ANGLES_5Deg;
//DeadCode CSB 19/04/99	
//DeadCode CSB 19/04/99	  			AutoCalcPitch ();
//DeadCode CSB 19/04/99	 			CalcVelAlt(2 * classtype->landingspeed + flightnum*300);
//DeadCode CSB 19/04/99		 		CalcXYZVel ();
//DeadCode CSB 19/04/99	 			NewPosition ();
//DeadCode CSB 19/04/99	 			SetFlightParams ();
//DeadCode CSB 19/04/99			}
//DeadCode CSB 19/04/99			else
//DeadCode CSB 19/04/99			{
//DeadCode CSB 19/04/99				AutoFollowWpWing();
//DeadCode CSB 19/04/99			}
//DeadCode CSB 19/04/99		}
//DeadCode CSB 19/04/99		break;
//DeadCode CSB 19/04/99		
	case TO_DIRTYAFWPW:
	{		//Dirty AutoFollowWpWing
		AirStrucPtr lf = FindLeadCandidate();

		if((!lf) || (lf->movecode == AUTO_FOLLOWWP))
		{
			movecode = AUTO_FOLLOWWP;
			AutoFollowWp();
			SetManoeuvreTime(0);
			SHAPE.NavigationLightsActive(this, FALSE);
		}
		else
			AutoFollowWpWing(lf);
		break;
	}

	case TO_SIMPLEHOLDDELAY:
		//MIG COUNTDOWN
		if (!TimeLeft())
			if (ai.manoeuvre.value)
			{
				ai.manoeuvre.value--;		//256 lots of 11 mins = 30+ hrs
				SetManoeuvreTime(65535);
			}
			else
				ai.ManStep=TO_RUNWAYTAXI;
	break;
	
	case TO_SIMPLEHOLDINDEFINITE:
		//NO ACTION WHATSOEVER!!!
	break;


	//end case
	}

}



//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 void AirStruc::AutoTaxi ()
//DeadCode JIM 19Feb99 {
//DeadCode JIM 19Feb99 	if (	roll != ANGLES_0Deg
//DeadCode JIM 19Feb99 		||	!TimeLeft()	
//DeadCode JIM 19Feb99 		)
//DeadCode JIM 19Feb99 	{
//DeadCode JIM 19Feb99 		InterceptandRange (FindDesPos ());
//DeadCode JIM 19Feb99 		roll=ANGLES_0Deg;
//DeadCode JIM 19Feb99 		Bool	level=CalcVel ();
//DeadCode JIM 19Feb99 				level&=CalcHdgRollFlat ();
//DeadCode JIM 19Feb99 				level&=AutoCalcPitch ();
//DeadCode JIM 19Feb99 		CalcXYZVel ();
//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 		if (vel==0)	vel=1;										//DAW 07Dec96
//DeadCode JIM 19Feb99 
//DeadCode JIM 19Feb99 		SLong	rangetime=((Range-1000*100)/vel)/10;
//DeadCode JIM 19Feb99 		if (rangetime>30*100)
//DeadCode JIM 19Feb99 			rangetime=30*100;
//DeadCode JIM 19Feb99 		if (	level
//DeadCode JIM 19Feb99 			&&	rangetime>0	)
//DeadCode JIM 19Feb99 			SetManoeuvreTime(rangetime);
//DeadCode JIM 19Feb99 	}
//DeadCode JIM 19Feb99 	NewPosition ();
//DeadCode JIM 19Feb99 	SetFlightParams ();
//DeadCode JIM 19Feb99 }


void formationitem::WaitToTaxi ()
{
	movecode=AutoMoveCodeTypeSelect(GR_TruckMoveCode);
}
//////////////////////////////////////////////////////////////////////
//
// Function:    AutoTaxi 
// Date:		10/06/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void formationitem::AutoTaxi ()
{
	if (leader && leader->waypoint==waypoint)
	{	//quick and dirty
	 	velx=leader->velx;
	 	vely=leader->vely;
	 	velz=leader->velz;
	 	velhori=leader->velhori;
	 	vel=leader->vel;
		hdg=leader->hdg;
		pitch=leader->pitch;
		roll=leader->roll;
		vely=contourlist->GetVVel(this);
		NewPosition ();
//		World.Y=leader->World.Y;
	}
	else
	{

		if (	roll != ANGLES_0Deg
			||	!TimeLeft()	
			)
		{
			Coords3D p=*FindDesPos ();										//MS 28Nov96
//DeadCode JIM 06Dec96 			if (p.Y<=0)
				p.Y=World.Y;
			InterceptandRange (&p);				//MS 28Nov96

			roll=ANGLES_0Deg;

			SLong	reqvel;
			if (waypoint && waypoint->vel)
		 		reqvel =  waypoint->vel;
			else
				reqvel =  classtype->cruisevel;

			if (Math_Lib.AbsSign(hdg-HdgIntercept)>ANGLES_30Deg)
			{
				reqvel*=ANGLES_180Deg-Math_Lib.AbsSign(hdg-HdgIntercept);
				reqvel/=ANGLES_180Deg;
			}
			Bool	level=CalcVelSub (reqvel);
					level&=CalcHdgRollFlat ();
//DEADCODE JIM 19/06/99 			if (vel==0)
//DEADCODE JIM 19/06/99 				vel=1;
//DEADCODE JIM 19/06/99 
			pitch=ANGLES_0Deg;
//DeadCode RDH 29Oct96 			AutoCalcPitch ();	//never fails...

			CalcXYZVel ();

//DeadCode JIM 06Dec96 			if (p->Y<=0)										//MS 28Nov96
//DeadCode JIM 06Dec96 				Range-=World.Y;									//MS 28Nov96

			if (vel==0)	vel=1;									//DAW 07Dec96

			SLong	rangetime=((Range*100)/vel)/10;
			if (	Range<desposrange
				||	rangetime<=Timer_Code.FRAMETIME*4			//RDH 30Oct96
				)					//DAW 31Jul96
			{
				ExecuteWayPointAction ();
			}
			else
			{
//TempCode DAW 06Nov96 				((char*)0xB0000)[16]++;
				rangetime -=600;
				if (rangetime>30*100)
					rangetime=30*100;
				if (	level
					&&	rangetime>0)
					SetManoeuvreTime(rangetime);
			}
		}
		vely=contourlist->GetVVel(this);
		NewPosition ();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVVel
//Author		R. Hyde 
//Date			Sun 27 Oct 1996
//
//Description	Utilises a table to cache 1 tile of alt data
//				This should allow Paul to optimise his code a little.
//				I will require only 64 bytes per convoy, whereas Paul would 
//				need 65K potentially and would be continually discarding.
//				The file system will also be able to discard up to 4K
//				associated with this tile.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------   
ContourList *  ContourList::allocatedlist=NULL;

void	ContourList::FreeList()
{
	ContourList	*list,*next;
	list=allocatedlist;
	allocatedlist=NULL;
	while(list)
	{
		next=list->allocatednext;
		delete list;
		list=next;
	}
}

SWord	ContourList::GetVVel(FormationItemPtr	it)
{
	if (	(it->velx ==0)
		&&	(it->velz ==0)
		)
			return (it->vely);

	if (this==NULL)
	{
		it->contourlist=new ContourList;

		it->contourlist->velx=0x8000;	//uninitialised
		it->contourlist->velz=-0x8000;
		it->contourlist->currind=0;
		it->contourlist->vely[it->contourlist->currind]=0;
		it->contourlist->vely[it->contourlist->currind+1]=0x80;
		return(it->contourlist->GetVVel(it));
	}
	else
	{
		if (velz==-0x8000)									//JIM 13Nov96
		{	//don't know where the ground is!
			if (	velx!=it->velx
				||	(tilex&-0x1000)!=(it->World.X&-0x1000)
				||	(tilez&-0x1000)!=(it->World.Z&-0x1000)
			   )
			{
				velx=it->velx;
				tilex=it->World.X;
				tilez=it->World.Z;
				int	gl=Land_Scape.GetGroundLevel(it->World);
				if (gl!=0 && gl!=HIGHESTGROUND)
				{	//started to get ground data again! bounce to level.
					it->World.Y=gl;
					velz=0;
					velx=0x8000;
				}
			}
		}
		else
		{
			if (	velx!=it->velx
				||	velz!=it->velz
				||	(tilex&-0x20000)!=(it->World.X&-0x20000)
				||	(tilez&-0x20000)!=(it->World.Z&-0x20000)
				)
			{	//we can work it out again!
				velx=it->velx;
				velz=it->velz;
				tilex=it->World.X;
				tilez=it->World.Z;
				currind=0;
				int	gl=Land_Scape.GetGroundLevel(it->World);		//JIM 13Nov96
				if (gl==0 || gl==HIGHESTGROUND)
				{	//failed to load
					currind=0;
					vely[currind]=0;
					velz=0x8000;
				}
				else												//JIM 13Nov96
					MakeNewTable(it);
			}
			if (	(tilex&-0x1000)!=(it->World.X&-0x1000)
				||	(tilez&-0x1000)!=(it->World.Z&-0x1000)
				)
			{
				tilex=it->World.X;
				tilez=it->World.Z;
		 		currind++;
			}
		}
		//continue
		if (vely[currind]==-0x80)
		{
//DeadCode JIM 26Nov96 			INT3();
			velx=0x8000;
			velz=0x8000;
			return(0);
		}
		return(vely[currind]);
	}
}


void	ContourList::MakeNewTable(FormationItemPtr	it)
{
	//DDA along the line 
	//each time we hit a boundary, get the exact height data
	//and calc the vel to get to that height from the current simulated position

	{
		for (int i=0;i<64;i++)
			vely[i]=0x80;
	}

	int	absvelx=velx,
		absvelz=velz,
		absdistx=tilex&(0x20000-1),
		absdistz=tilez&(0x20000-1);

	if (absvelx<0)
		absvelx=-absvelx;
	else
		absdistx=0x20000-absdistx;

	if (absvelz<0)
		absvelz=-absvelz;
	else
		absdistz=0x20000-absdistz;

	//First, where are we trying to get to?

	//want to compare times for x and z travel to find shorter
	if (absdistz*absvelx<absdistx*absvelz)
	{	//absdistz is closer
		absdistx=absdistz*absvelx/absvelz;
	}
	else
	{	//absdistx is closer
		absdistz=absdistx*absvelz/absvelx;
	}

	SByte* newvely=vely;
	if (absvelx<absvelz)
	{	//do da code!
		int	stepx=absvelx*0x1000/absvelz;
		if (velx<0)
			stepx=-stepx;
		int	stepz;
		Coords3D pos=it->World;
		int	dz0=-(pos.Z&(0x1000-1));
		pos.Z&=-0x1000;
		if (velz<0)
		{
			stepz=-0x1000;
		}
		else
		{
			stepz=0x1000;
			pos.Z+=0x1000;	//this is the starting point
			dz0=0x1000+dz0;
		}
		int oldx=pos.X;
		pos.X+=dz0*velx/velz;

		int	gl=Land_Scape.GetGroundLevel(pos)-pos.Y;
		//OK.. need a correction for the first 40m
		//this may exceed max pitch, so clip it to max/min pitch
		//
		//
		int	vely=0;
		if (dz0)
			vely=(gl*velz+dz0-1)/dz0;	//round up
		pos.Y+=vely*dz0/velz;
		if (vely>120)
			vely=120;
		if (vely<-120)
			vely=-120;
		if ((oldx&-0x1000) != (pos.X&-0x1000))
			if (pos.X&(0x1000-1))
			newvely++[0]=vely;	
		newvely++[0]=vely;
		int steps=absdistz/0x1000;
		while (steps)
		{
			oldx=pos.X;
			pos.X+=stepx;
			pos.Z+=stepz;
			gl=Land_Scape.GetGroundLevel(pos)-pos.Y;
			vely=(gl*absvelz+0xfff)/0x1000;	//round up
			pos.Y+=vely*0x1000/absvelz;
			if ((oldx&-0x1000) != (pos.X&-0x1000))
				if (pos.X&(0x1000-1))
				newvely++[0]=vely;	
			newvely++[0]=vely;
			steps--;
		}
	}
	else
	{
		int	stepz=absvelz*0x1000/absvelx;
		if (velz<0)
			stepz=-stepz;
		int	stepx;
		Coords3D pos=it->World;
		int	dx0=-(pos.X&(0x1000-1));
		pos.X&=-0x1000;
		if (velx<0)
		{
			stepx=-0x1000;
		}
		else
		{
			stepx=0x1000;
			pos.X+=0x1000;	//this is the starting point
			dx0=0x1000+dx0;
		}
		int oldz=pos.Z;
		pos.Z+=dx0*velz/velx;


		int	gl=Land_Scape.GetGroundLevel(pos)-pos.Y;
		//OK.. need a correction for the first 40m
		//this may exceed max pitch, so clip it to max/min pitch
		//
		//
		int	vely=0;
		if (dx0)
			vely=(gl*velx+dx0-1)/dx0;		//round up

		pos.Y+=vely*dx0/velx;
		if (vely>120)
			vely=120;
		if (vely<-120)
			vely=-120;
		if ((oldz&-0x1000) != (pos.Z&-0x1000))
			if (pos.Z&(0x1000-1))
			newvely++[0]=vely;	
		newvely++[0]=vely;

		int steps=absdistx/0x1000;
		while (steps)
		{
			oldz=pos.Z;
			pos.Z+=stepz;
			pos.X+=stepx;
			gl=Land_Scape.GetGroundLevel(pos)-pos.Y;
			vely=(gl*absvelx+0xfff)/0x1000;	//round up
			pos.Y+=vely*0x1000/absvelx;
			if ((oldz&-0x1000) != (pos.Z&-0x1000))
				if (pos.Z&(0x1000-1))
				newvely++[0]=vely;	
			newvely++[0]=vely;
			steps--;
		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoLanding
//Author		Craig Beeston
//Date			Wed 21 Apr 1999
//
//Description	Brings aircraft into orbit around there home airfield, loose height
//				and loose speed, one at a time approach and land along takeoff line
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoLanding()
{
	const int flightpos = position();
	const int ApproachRad = 83333;		//r = R * Sin(ApproachAng) / (1 + Sin(ApproachAng)) * 1.02ish
	const SWord ApproachAng	= (SWord)ANGLES_30Deg;
	const SWord ApproachZone= (SWord)ANGLES_1Deg;
	static UWord LandingNum = 0;
	
	int squadnum = ai.squadnum();
	int pilotnum = ai.pilotnum - 24 * squadnum;
	int OrbitRadius = 250000 + METRES20 * pilotnum;		
	int	OrbitAlt	= 50000  + METRES30 * squadnum;

//#define PRINT_LANDING_DATA
#ifdef PRINT_LANDING_DATA	
	PrintVar(30, 3 + flightpos, "Phase %.0f ", (FP)ai.ManStep);
	PrintVar(40, 3 + flightpos, "Alt %.1f ", (FP)((World.Y - ai.homebase->World.Y) * 0.01));
	PrintVar(50, 3 + flightpos, "Vel %.1f ", (FP)(vel * 0.1));
	PrintVar(60, 3 + flightpos, "Pitch %.1f ", (FP)(pitch / 182.04));
	PrintVar(70, 3 + flightpos, "Hdg %.1f ", (FP)(hdg / 182.04));
#endif

	switch(ai.ManStep)
	{
		case 0:	//orbit, loose height, loose speed
		{
			COORDS3D runway0;
			GetTakeOffPos(UniqueID(RunwaySBAND), runway0);
			despos   = runway0;
			despos.Y = World.Y;
			InterceptandRange(&despos);

			if(Range > 2 * OrbitRadius) AutoFollowWp();
			else
			{
				AutoOrbit(despos, OrbitRadius);
				
				SLong DeltaAlt = World.Y - runway0.Y;
				if(DeltaAlt > OrbitAlt + 1000)		{PitchIntercept = ANGLES_10Deg; PitchIntercept = -PitchIntercept;}
				else if(DeltaAlt < OrbitAlt - 1000)	 PitchIntercept = ANGLES_10Deg;
				else								 PitchIntercept = ANGLES_0Deg;

				AutoCalcPitch();
				SWord OrbitVel = (3 * classtype->landingspeed) / 2;
				if(CalcVelAlt(OrbitVel))
					if((PitchIntercept == ANGLES_0Deg) && (pitch == ANGLES_0Deg))
						ai.ManStep = 1;			//Ready to start landing approach
				
				CalcXYZVel();
				NewPosition ();
				SetFlightParams ();
			}
			break;
		}

		case 1:	//orbit and wait for a gap to land
		{
			COORDS3D runway0, runway1;
			GetTakeOffPos(UniqueID(RunwaySBAND), runway0);
			GetTakeOffPos(UniqueID(RunwayEBAND), runway1);

			despos   = runway0;
			despos.Y = World.Y;

			AutoOrbit(despos, OrbitRadius);
				
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();

			InterceptandRange(&runway0, &runway1);
			SWord RunwayHdg = HdgIntercept;
			InterceptandRange(&runway0);
			SWord HdgError = (SWord)HdgIntercept - RunwayHdg - ApproachAng;
			if((HdgError > -ApproachZone) && (HdgError < ApproachZone))
			{
				Bool CanLand = TRUE;
				if(playernotmovingheldac)
					if(	  (playernotmovingheldac->movecode == AUTO_TAKEOFF)
					   || ((playernotmovingheldac->movecode == AUTO_LANDING) && (playernotmovingheldac->ai.ManStep == 2)) )
					   CanLand = FALSE;
				if(CanLand)
				{
					if(PlayerInGroup())
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOLAND, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, this, Persons2::PlayerGhostAC));//, TRUE));

					if (_DPlay.Implemented || _Replay.Record)				//AMM 22Jun99
//DeadCode DAW 28Jun99 						_DPlay.NewPlayerNotMovingHeldAC(this->uniqueID.count);//AMM 22Jun99
						_DPlay.NewPlayerNotMovingHeldAC(this->uniqueID.count,DPlay::AUTOLANDING1);//AMM 28Jun99
					else													//AMM 22Jun99
					{
						playernotmovingheldac = this;
						ai.ManStep = 2;	//
						SetManoeuvreTime(5*SECS100);
						fly.pModel->SetGearAnimPos(this, ANIM_GEAR_AUTO);
					}
//DeadCode DAW 28Jun99 						playernotmovingheldac = this;
//DeadCode DAW 28Jun99 					ai.ManStep = 2;	//
//DeadCode DAW 28Jun99 					SetManoeuvreTime(5*SECS100);
//DeadCode DAW 28Jun99 					fly.pModel->SetGearAnimPos(this, ANIM_GEAR_AUTO);
				}
			}
			break;
		}

		case 2:	//Tight turn onto runway	//Timed
		case 3:	//Tight turn onto runway 
		{
			if((ai.ManStep == 2) && (!TimeLeft()))
			{
				ai.ManStep = 3;						//Let the next guy into landing approach
				if (_DPlay.Implemented || _Replay.Record)				//AMM 22Jun99
//DeadCode DAW 28Jun99 					_DPlay.NewPlayerNotMovingHeldAC(UID_NULL);//AMM 22Jun99
					_DPlay.NewPlayerNotMovingHeldAC(UID_NULL,DPlay::AUTOLANDING2);	//AMM 28Jun99
				else													//AMM 22Jun99
				{
					playernotmovingheldac = NULL;
					SetManoeuvreTime(5 * SECS100);		//Start putting flaps down
				}
//DeadCode DAW 28Jun99 					playernotmovingheldac = NULL;
//DeadCode DAW 28Jun99 				SetManoeuvreTime(5 * SECS100);		//Start putting flaps down
			}
			if((ai.ManStep == 3) && (TimeLeft()) && (fly.pModel))
				fly.pModel->FlapsDown(this);

			COORDS3D runway0, runway1;
			GetTakeOffPos(UniqueID(RunwaySBAND), runway0);
			GetTakeOffPos(UniqueID(RunwayEBAND), runway1);

			InterceptandRange(&runway0, &runway1);
			SWord RunwayHdg = HdgIntercept;

			InterceptandRange(&runway0);
			AutoCalcPitch();

			SWord desroll = -Math_Lib.arctan(vel * vel, (FP)(100 * GRAVITY * ApproachRad));
			SimpleMoveToRoll(desroll);
			hdg += CalcHdg();

			if(vel > classtype->landingspeed)
				AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();

			SWord HdgError = (SWord)hdg - RunwayHdg;
			if(HdgError < 0) HdgError = -HdgError;
			if(HdgError < ANGLES_HalfDeg)
			{
				hdg = (Angles)RunwayHdg;
				ai.ManStep = 4;
			}
			break;
		}
	
		case 4:	//Straight approach onto runway with sideslide to get on line
		{
			if(vel > classtype->landingspeed)
				AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);

			COORDS3D runway0;
			GetTakeOffPos(UniqueID(RunwaySBAND), runway0);
			InterceptandRange(&runway0);
			AutoCalcPitch();

			COORDS3D GlobDelta, LocDelta;
			
			GlobDelta.X = runway0.X - World.X;
			GlobDelta.Y = runway0.Y - World.Y;
			GlobDelta.Z = runway0.Z - World.Z;

			RotateToHdg(GlobDelta, LocDelta, hdg);

			if((LocDelta.X < 100) && (LocDelta.X > -100))	//Within 1 metre laterally of desired landing spot
			{
				if(roll != ANGLES_0Deg)
					SimpleMoveToRoll(ANGLES_0Deg);
				CalcXYZVel();
			}
			else
			{
				SLong desroll = 4 * LocDelta.X;

				MODLIMIT(desroll, ANGLES_45Deg);
				SimpleMoveToRoll((SWord)desroll);
				SWord VelHdg = (SWord)hdg + (2 * (SWord)roll) / 10;		//Direction of travel - different from aircraft hdg

				SLong despitch = (LocDelta.Y * ANGLES_FRACT) / Range;
				MODLIMIT(despitch, ANGLES_15Deg);
				PitchIntercept = (Angles)despitch;
				AutoCalcPitch();

				SWord SinPitch, CosPitch, SinHdg, CosHdg;;
				Math_Lib.high_sin_cos (pitch,  SinPitch, CosPitch);
				Math_Lib.high_sin_cos ((Angles)VelHdg,  SinHdg, CosHdg);

				vely	= (vel * SinPitch) / ANGLES_FRACT;
				velhori	= (vel * CosPitch) / ANGLES_FRACT;
				velx	= (velhori * SinHdg) / ANGLES_FRACT;
				velz	= (velhori * CosHdg) / ANGLES_FRACT;
				if((this != Persons2::PlayerSeenAC) && (this != Persons2::PlayerGhostAC))
					fly.rudder  = -3 * (SWord)roll;
			}

			NewPosition ();
			SetFlightParams ();

			int TimeToLevelOut = -(SWord)pitch / 10;	//cs
			int HeightLoss = -TimeToLevelOut * vely / 20;	//cm
			HeightLoss = HeightLoss * 11 / 10;		//10% correction for Rounding/integration errors
			
			if(-LocDelta.Y < HeightLoss + 250)	//pull out to level at 2.5 metres
				ai.ManStep = 5;					//Level out, flare and land
		
			break;
		}
	
		case 5:	  //Level Out and flare
		{
			COORDS3D runway0;
			GetTakeOffPos(UniqueID(RunwaySBAND), runway0);

			PitchIntercept = ANGLES_10Deg;
			if(pitch < PitchIntercept)
				pitch += 10 * Timer_Code.FRAMETIME;
			fly.cpitch = pitch;
			if(vel > 3 * classtype->landingspeed / 4)
				AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);
			CalcXYZVel();

			if(pitch > ANGLES_0Deg)	//Stomp vely to force AC onto ground
			{
				if(World.Y > runway0.Y)
					vely = -10;
				else
				{					
					vely = 0;	//Touched Down

					if (ItemPtr(*Persons2::ConvertPtrUID(UID_TAXI0))->SGT != ai.homebase->uniqueID.count)
						ai.ManStep = 12;
					else
						ai.ManStep = 6;		//Nose wheel down and slow down
					SetManoeuvreTime(65535);
				}
			}
			NewPosition ();
			SetFlightParams ();
			break;
		}

		case 6:	 //Straight along runway lowering the nose and slowing down
		{
			if(pitch > classtype->deckangle)
			{
				pitch -= 10 * Timer_Code.FRAMETIME;
				if(pitch < classtype->deckangle) pitch = classtype->deckangle;
			}
			if(pitch < classtype->deckangle)
			{
				pitch += 10 * Timer_Code.FRAMETIME;
				if(pitch > classtype->deckangle) pitch = classtype->deckangle;
			}


			if(vel > 300)
				AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);
			CalcXYZVel();
			vely = 0;

			NewPosition ();
			SetFlightParams ();

			COORDS3D runway1;
			GetTakeOffPos(UniqueID(RunwayEBAND), runway1);
			InterceptandRange(&runway1);
			if(Range < METRES250)
			{
				if(vel > 100)
					AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);
		
				if(manoeuvretime == 65535)
				{
					manoeuvretime = LandingNum;
					LandingNum++;
				}
				if(Range < METRES10)
					ai.ManStep = 7;	//Turn off runway towards AF_PARK0
			}
			break;
		}

		case 7:  //Turn off runway towards parking area
		{
			GetTakeOffPos(UniqueID(UID_PARK0), despos);
			InterceptandRange(&despos);

			SWord deltahdg = HdgIntercept - hdg;
			if( deltahdg > ANGLES_1Deg) hdg += ANGLES_FifthDeg * Timer_Code.FRAMETIME;
			if(-deltahdg > ANGLES_1Deg) hdg -= ANGLES_FifthDeg * Timer_Code.FRAMETIME;

			if(vel > 100)
				AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);

			CalcXYZVel();
			vely = 0;
			NewPosition ();
			SetFlightParams ();

			if(Range < METRES10)
				ai.ManStep = 8;	//Turn towards AF_PARK1
			break;
		}

		case 8:  //Turn back towards parking spot
		{
			UWord ParkNum = manoeuvretime;
			COORDS3D Park1, ParkL;
			GetTakeOffPos(UniqueID(UID_PARK1), Park1);
			GetTakeOffPos(UniqueID(UID_PARKL), ParkL);
			COORDS3D Offset;
			Offset.X = ParkL.X - Park1.X;
			Offset.Y = ParkL.Y - Park1.Y;
			Offset.Z = ParkL.Z - Park1.Z;
			despos = Park1;
			SWord flightnum = ParkNum / 4 + 2;
			despos.X -= flightnum * Offset.X;
			despos.Y -= flightnum * Offset.Y;
			despos.Z -= flightnum * Offset.Z;
			
			InterceptandRange(&despos);

			SWord deltahdg = HdgIntercept - hdg;
			if( deltahdg > ANGLES_1Deg) hdg += ANGLES_FifthDeg * Timer_Code.FRAMETIME;
			if(-deltahdg > ANGLES_1Deg) hdg -= ANGLES_FifthDeg * Timer_Code.FRAMETIME;

			if((Range > METRES100) && (vel < 250))
				AddAccel2Vel(2560 * Timer_Code.FRAMETIME);
			else if((Range < METRES100) && (vel > 100))
				AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);

			CalcXYZVel();
			vely = 0;
			NewPosition ();
			SetFlightParams ();

			if(Range < METRES10)
				ai.ManStep = 9;	//Turn towards Parking Spot
			break;
		}

		case 9:	 //Element leaders go straight on - Wingmen turn around the back of there leader
		{
			UWord ParkNum = manoeuvretime;
			COORDS3D Park1, ParkL;
			GetTakeOffPos(UniqueID(UID_PARK1), Park1);
			GetTakeOffPos(UniqueID(UID_PARKL), ParkL);
			COORDS3D Offset;
			Offset.X = ParkL.X - Park1.X;
			Offset.Y = ParkL.Y - Park1.Y;
			Offset.Z = ParkL.Z - Park1.Z;
	
			if(ParkNum & 0x000002)		//Flight or Element Leader
				GetTakeOffPos(UniqueID(UID_PARKW), despos);
			else
				despos = ParkL;
		
			SWord flightnum = ParkNum / 4 + 1;
			despos.X -= flightnum * Offset.X;
			despos.Y -= flightnum * Offset.Y;
			despos.Z -= flightnum * Offset.Z;

			if(ParkNum & 0x000001)		//Leader or WingMan
			{
				FP OffsetRange = Distance3D(&Park1, &ParkL);
				despos.X += (METRES15 * Offset.Z) / OffsetRange;
				despos.Z -= (METRES15 * Offset.X) / OffsetRange;
			}
			
			InterceptandRange(&despos);

			SWord deltahdg = HdgIntercept - hdg;
			if( deltahdg > ANGLES_1Deg) hdg += ANGLES_FifthDeg * Timer_Code.FRAMETIME;
			if(-deltahdg > ANGLES_1Deg) hdg -= ANGLES_FifthDeg * Timer_Code.FRAMETIME;

			if(vel > 100)
				AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);

			CalcXYZVel();
			vely = 0;
			NewPosition ();
			SetFlightParams ();

			if(Range < METRES10)
				ai.ManStep = 10;	//Turn towards actual Parking Spot
			break;
		}

		case 10:	 //Turn to actual parking spot and stop
		{
			UWord ParkNum = manoeuvretime;
			COORDS3D Park1, ParkL;
			GetTakeOffPos(UniqueID(UID_PARK1), Park1);
			GetTakeOffPos(UniqueID(UID_PARKL), ParkL);
			COORDS3D Offset;
			Offset.X = ParkL.X - Park1.X;
			Offset.Y = ParkL.Y - Park1.Y;
			Offset.Z = ParkL.Z - Park1.Z;
	
			if(ParkNum & 0x000002)		//Flight or Element Leader
				GetTakeOffPos(UniqueID(UID_PARKW), despos);
			else
				despos = ParkL;
		
			SWord flightnum = ParkNum / 4;
			despos.X -= flightnum * Offset.X;
			despos.Y -= flightnum * Offset.Y;
			despos.Z -= flightnum * Offset.Z;

			if(ParkNum & 0x000001)		//Leader or WingMan
			{
				FP OffsetRange = Distance3D(&Park1, &ParkL);
				despos.X += (METRES15 * Offset.Z) / OffsetRange;
				despos.Z -= (METRES15 * Offset.X) / OffsetRange;
			}
			
			InterceptandRange(&despos);

			SWord deltahdg = HdgIntercept - hdg;
			if( deltahdg > ANGLES_1Deg) hdg += ANGLES_FifthDeg * Timer_Code.FRAMETIME;
			if(-deltahdg > ANGLES_1Deg) hdg -= ANGLES_FifthDeg * Timer_Code.FRAMETIME;

//DeadCode CSB 26/04/99				if(vel > 100)
//DeadCode CSB 26/04/99					AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);
			if((Range > 300) && (Range < 1000 * 3))
			vel = Range / 30;

			CalcXYZVel();
			vely = 0;
			NewPosition ();
			SetFlightParams ();

			if(Range < METRES01)
			{
				ai.ManStep = 11;	//Turn towards Parking Spot
				SHAPE.NavigationLightsActive(this, FALSE);
			}

			break;
		}

		case 11:  //Parked
		{
			//NOTHING AT ALL
			break;
		}
		
		case 12:  //Simple Parking
		{
			if(pitch > classtype->deckangle)
			{
				pitch -= 10 * Timer_Code.FRAMETIME;
				if(pitch < classtype->deckangle) pitch = classtype->deckangle;
			}
			if(pitch < classtype->deckangle)
			{
				pitch += 10 * Timer_Code.FRAMETIME;
				if(pitch > classtype->deckangle) pitch = classtype->deckangle;
			}
			
			if(manoeuvretime == 65535)
			{
				manoeuvretime = LandingNum;
				LandingNum++;
			}

			UWord ParkNum = manoeuvretime;
			COORDS3D runway1;
			GetTakeOffPos(UniqueID(RunwayEBAND), runway1);
			InterceptandRange(&runway1);
			Range -= 2000 * ParkNum;

			SWord DesVel;
			if(Range > 25000)
				DesVel = 250;
			else
				DesVel = Range / 100;
			if(vel > DesVel)
				AddAccel2Vel(-2560 * Timer_Code.FRAMETIME);
			if(Range < 1000)
				ai.ManStep = 13;
			
			CalcXYZVel();
			vely = 0;

			NewPosition ();
			SetFlightParams ();
			break;
		}
		
		case 13:  //Parked
		{
			//NOTHING AT ALL
			break;
		}
		
		break;
	}
}

//DeadCode CSB 21/04/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 21/04/99	//Procedure		AutoLanding
//DeadCode CSB 21/04/99	//Author		R. Hyde 
//DeadCode CSB 21/04/99	//Date			Sun 27 Oct 1996
//DeadCode CSB 21/04/99	//
//DeadCode CSB 21/04/99	//Description	
//DeadCode CSB 21/04/99	//
//DeadCode CSB 21/04/99	//Inputs		
//DeadCode CSB 21/04/99	//
//DeadCode CSB 21/04/99	//Returns	
//DeadCode CSB 21/04/99	//
//DeadCode CSB 21/04/99	//------------------------------------------------------------------------------
//DeadCode CSB 21/04/99	void	AirStruc::AutoLanding()
//DeadCode CSB 21/04/99	{
//DeadCode CSB 21/04/99		despos=ai.homebase->World;
//DeadCode CSB 21/04/99		despos.Y-=METRES01;										//JIM 03Dec96
//DeadCode CSB 21/04/99		despos.X+=3200*(formpos&InWingMAX);
//DeadCode CSB 21/04/99		despos.Z+=3200*(formpos&InFormMAX);
//DeadCode CSB 21/04/99		InterceptandRange (&despos);
//DeadCode CSB 21/04/99	
//DeadCode CSB 21/04/99		if (Range>METRES1600)
//DeadCode CSB 21/04/99			AutoFollowWp();
//DeadCode CSB 21/04/99		else
//DeadCode CSB 21/04/99		{
//DeadCode CSB 21/04/99			if (Range>METRES200)
//DeadCode CSB 21/04/99				if (	Range>METRES800
//DeadCode CSB 21/04/99					||	World.Y-ai.homebase->World.Y>METRES100
//DeadCode CSB 21/04/99	//DeadCode RDH 24Oct96 					||	(	Math_Lib.AbsSign((SWord)(HdgIntercept-Save_Data.wind.direction))>ANGLES_10Deg
//DeadCode CSB 21/04/99						||	(	//rdh change to MA wind Math_Lib.AbsSign((SWord)(HdgIntercept-MMC.wind.direction))>ANGLES_30Deg &&
//DeadCode CSB 21/04/99							Range>METRES50)
//DeadCode CSB 21/04/99					)
//DeadCode CSB 21/04/99				{	//head out to fly 90 deg at radius  300metres alt 200metres
//DeadCode CSB 21/04/99					//METRES500 is 50,000. /2=25,000 /4=12000 /8=6000 /16=3000
//DeadCode CSB 21/04/99					//90 deg is 16,000. 45 deg=4,000
//DeadCode CSB 21/04/99					//Inside gives bigger deltang. Outside gives smaller.
//DeadCode CSB 21/04/99					ANGLES	deltang=(Angles)((METRES600-Range)/8);	//metres500=50000
//DeadCode CSB 21/04/99					deltang+=(Angles)(100*(formpos&InWingMAX));	//this is intentionally peanuts, but 
//DeadCode CSB 21/04/99					deltang+=(Angles)(15*(formpos&InFormMAX));	//generates some separation
//DeadCode CSB 21/04/99					deltang+=ANGLES_90Deg;							//sub is -110K..+50K
//DeadCode CSB 21/04/99					HdgIntercept+=deltang;							//over8=  -14K..+6K
//DeadCode CSB 21/04/99					if (World.Y-ai.homebase->World.Y<METRES100)		//		-60deg..+45deg
//DeadCode CSB 21/04/99						if (World.Y-ai.homebase->World.Y<METRES50)	//@700m sub is -20000 /8=2500=90deg-13deg=78deg
//DeadCode CSB 21/04/99							PitchIntercept=-PitchIntercept;			
//DeadCode CSB 21/04/99						else
//DeadCode CSB 21/04/99							PitchIntercept=ANGLES_0Deg;
//DeadCode CSB 21/04/99						else
//DeadCode CSB 21/04/99							if (PitchIntercept<ANGLES_340Deg)
//DeadCode CSB 21/04/99								PitchIntercept=ANGLES_340Deg;
//DeadCode CSB 21/04/99					Bool
//DeadCode CSB 21/04/99						level=CalcVelSub (classtype->cruisevel);	//20mph above cruise
//DeadCode CSB 21/04/99						level&=CalcHdgRoll ();
//DeadCode CSB 21/04/99						level&=AutoCalcPitch ();
//DeadCode CSB 21/04/99				}
//DeadCode CSB 21/04/99				else
//DeadCode CSB 21/04/99				{	//fly to land gracefully on runway
//DeadCode CSB 21/04/99					//in box grid based on formation position
//DeadCode CSB 21/04/99					PitchIntercept=(Angles)(2*PitchIntercept);
//DeadCode CSB 21/04/99					Bool
//DeadCode CSB 21/04/99						level=CalcVelSub (classtype->minvel);	//20mph above cruise
//DeadCode CSB 21/04/99						level&=CalcHdgRoll ();
//DeadCode CSB 21/04/99						level&=AutoCalcPitch ();
//DeadCode CSB 21/04/99				}
//DeadCode CSB 21/04/99			else
//DeadCode CSB 21/04/99			{
//DeadCode CSB 21/04/99	
//DeadCode CSB 21/04/99	 			PitchIntercept=ANGLES_0Deg;
//DeadCode CSB 21/04/99				if (	(HdgIntercept-hdg)<ANGLES_90Deg
//DeadCode CSB 21/04/99					&&	(HdgIntercept-hdg)>ANGLES_270Deg)
//DeadCode CSB 21/04/99					CalcVelSub (classtype->minvel);
//DeadCode CSB 21/04/99				else
//DeadCode CSB 21/04/99				{
//DeadCode CSB 21/04/99					CalcVelSub (0);
//DeadCode CSB 21/04/99					if (Range>METRES150)
//DeadCode CSB 21/04/99						movecode=AUTO_NOPPILOT;
//DeadCode CSB 21/04/99				}
//DeadCode CSB 21/04/99				HdgIntercept=hdg;	//no directional corrections now, please!
//DeadCode CSB 21/04/99				CalcHdgRollFlat ();
//DeadCode CSB 21/04/99				AutoCalcPitch ();
//DeadCode CSB 21/04/99			}
//DeadCode CSB 21/04/99		CalcXYZVel();
//DeadCode CSB 21/04/99		NewPosition ();
//DeadCode CSB 21/04/99		SetFlightParams ();
//DeadCode CSB 21/04/99	
//DeadCode CSB 21/04/99		}
//DeadCode CSB 21/04/99	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoStraffe
//Author		Mark Shaw
//Date			Fri 18 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoStraffe()
{
	UWord	mvel,mdelay,mburst;									//RDH 31Jul98
	if (ai.ManStep==0)
	{
		ai.ManStep=1;
		int	index;
		for (index = 0; index < 6; index++)						//RDH 31Jul98
		{
			WeapAnimData*	weapon;										//RJS 29Aug96
			SLong			xpos, ypos, zpos;							//RJS 29Aug96
			weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BOMB);//RDH 31Jul98
			if (weapon && weapon->LoadedStores > 0)
			{
				ai.ManStep=2;
			}

		}
	}

	if (!TimeLeft())
	{
		if (!SHAPE.GetLiveElementPos(formpos&InWingMAX,waypoint->target,despos.X,despos.Y,despos.Z))
			SHAPE.GetLiveElementPos(0,waypoint->target,despos.X,despos.Y,despos.Z);
		despos.X+=waypoint->target->World.X;
		despos.Y+=waypoint->target->World.Y;
		despos.Z+=waypoint->target->World.Z;
//DeadCode JIM 20Nov96 		despos.Y+=waypoint->World.Y;
		InterceptandRange (&despos);
		if ((HdgIntercept-hdg-ANGLES_90Deg<<ANGLES_180Deg))
		{
			if (Range<METRES1000)
			{	//flying away
				HdgIntercept=hdg;
				PitchIntercept=ANGLES_15Deg;
				if (ai.ManStep==3)
					ai.ManStep=0;
			}
			else
			{
				if (waypoint->target->Status.deadtime)
					if (waypoint->target->Status.size>=FORMATIONSIZE)
					{
						FormationItemPtr f=*waypoint->target;
						if (f->follower)
							waypoint->target=f->follower;
						else
							Art_Int.BreakOff(this);
					}
					else
						Art_Int.BreakOff(this);
				else
					if (roll==ANGLES_0Deg)
						if (Math_Lib.rnd()<RND25PC)
							Art_Int.BreakOff(this);

			}

			Bool
				level=CalcVelSub (classtype->maxvel);
				level&=CalcHdgRoll ();
				level&=AutoCalcPitch ();
			if (level)
	 			SetManoeuvreTime(FIVESECS100);
		}
		else
		{	//flying towards
			//mod pitchintercept based on range
			ANGLES	pdiff=PitchIntercept-pitch;
			if (ai.ManStep==2)
				pdiff=PitchIntercept-fly.cpitch+ANGLES_2Deg;

			if (	Range<METRES350 ////////&& (Timer_Code.msgcounttime &8)==0
				&&	ai.ManStep<3
				&&	pdiff<ANGLES_0Deg
				)
			{
				int	index=4;
				if (ai.ManStep==2)
				for (index = 0; index < 4; index++)
				{
					WeapAnimData*	weapon;										//RJS 29Aug96
					SLong			xpos, ypos, zpos;							//RJS 29Aug96
					weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BOMB);//RDH 31Jul98
					if (weapon && weapon->LoadedStores > 0)
					{
						weapon->LoadedStores--;
						Trans_Obj.LaunchBombDrop(this,BOMB,xpos,ypos,zpos,*currworld);//RJS 28Aug96
						ai.ManStep=3;
						break;
					}

				}
				elseif (ai.ManStep==1)
				{
					int	timeleft = weap.ShootDelay-Timer_Code.FRAMETIME;//DAW 31Jul96
					if (timeleft<=0)
					{
						for (index = 0; index < 4; index++)		//JIM 05Dec96
						{
							WeapAnimData*	weapon;										//RJS 29Aug96
							SLong			xpos, ypos, zpos;							//RJS 29Aug96
							weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BULLET);//RDH 31Jul98
						 	weap.ShootDelay = 10;
							if (   (weapon)						//JIM 05Dec96
								&& (weapon->LoadedStores > 0)
								)
							{
			 						weapon->LoadedStores--;
									Trans_Obj.LaunchOneGunBullet(this,mvel,BULLET,xpos,ypos,zpos,*currworld);
							}
						}
					}
					else
						weap.ShootDelay = timeleft;

			}	}
			if (Range>METRES600)
			{	//1m height diff=1/2 deg
				int delth;
				if (ai.ManStep==2)
					delth=-(World.Y-despos.Y-METRES350);		//JIM 04Dec96
				else
					delth=-(World.Y-despos.Y-METRES450);
				if (delth>ANGLES_60Deg)	delth=ANGLES_60Deg;
				if (0-delth>ANGLES_60Deg)	delth=0-ANGLES_60Deg;
				HdgIntercept+=(Angles)((formpos&InWingMAX)*ANGLES_5Deg);
				PitchIntercept=(Angles)(delth+(formpos&InWingMAX)*ANGLES_HalfDeg);
			}
			elseif (Range<METRES100)
				PitchIntercept=ANGLES_20Deg;
			else
			{
				int	pim=(Range-METRES250)>>5;			//metres200=20K=110deg./16->7 deg
				PitchIntercept-=(Angles)pim;
			}
			Bool
				level=CalcVelSub (classtype->cruisevel);	//20mph above cruise
				level&=CalcHdgRoll ();
				level&=AutoCalcPitch ();
			if (level && Range>MILES01)
	 			SetManoeuvreTime(SECS100);
		}
	 	CalcXYZVel();
	}
	NewPosition ();
	SetFlightParams ();
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckBombingStatus
//Author		Jim
//Date			26 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::CheckBombingStatus()
{
	AirStrucPtr lead=this;
	if (lead->Leader())
		lead=lead->Leader();
	if (lead->formpos)
		lead=lead->fly.leadflight;
	else
	{	//for all aircraft in formation, if any are still bombing then quick quit 
		for (;lead;lead=lead->fly.nextflight)
		{
			for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
				if (foll->movecode==AUTO_BOMB)
					return;
		}
		//ok so nobody is bombing.
		//next job: get status of target.
		if (EnoughDamage3D(ai.unfriendly))
			_Miles.SequenceAudible(FIL_MUSIC_OBJECTIVE_COMPLETED);
		else
			_Miles.SequenceAudible(FIL_MUSIC_OBJECTIVE_FAILED);
	}
}

//DeadCode CSB 29/03/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 29/03/99	//Procedure		AutoBomb
//DeadCode CSB 29/03/99	//Author		
//DeadCode CSB 29/03/99	//Date			Fri 18 Oct 1996
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//Description	
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//Inputs		
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//Returns	
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//------------------------------------------------------------------------------
//DeadCode CSB 29/03/99	void	AirStruc::AutoBomb()
//DeadCode CSB 29/03/99	{
//DeadCode CSB 29/03/99		if(uniqueID.count == waypoint->skipunder)
//DeadCode CSB 29/03/99		{
//DeadCode CSB 29/03/99			PrintVar(60, 5, "Man Time %.0f ", formationitem::manoeuvretime);
//DeadCode CSB 29/03/99			if (!TimeLeft())
//DeadCode CSB 29/03/99				if(ai.ManStep == 1)		   //Stop bombing and move to next waypoint
//DeadCode CSB 29/03/99				{
//DeadCode CSB 29/03/99					waypoint=waypoint->next;
//DeadCode CSB 29/03/99					movecode=AUTO_FOLLOWWP;
//DeadCode CSB 29/03/99					ai.ManStep = 0;
//DeadCode CSB 29/03/99					PrintString(50, 20, "                    ");
//DeadCode CSB 29/03/99				}
//DeadCode CSB 29/03/99				else
//DeadCode CSB 29/03/99				{
//DeadCode CSB 29/03/99					ai.ManStep = 0;
//DeadCode CSB 29/03/99					SHAPE.GetLiveElementPos(0,waypoint->target,despos.X,despos.Y,despos.Z);
//DeadCode CSB 29/03/99					despos.X+=waypoint->target->World.X;
//DeadCode CSB 29/03/99					despos.Y+=waypoint->target->World.Y;
//DeadCode CSB 29/03/99					despos.Z+=waypoint->target->World.Z;
//DeadCode CSB 29/03/99					despos.Y+=waypoint->World.Y;
//DeadCode CSB 29/03/99					InterceptandRange (&despos);
//DeadCode CSB 29/03/99	PrintVar(60,  8, "Target Bearing %.1f ", (FP)((HdgIntercept - hdg) / 182.04));
//DeadCode CSB 29/03/99	PrintVar(60,  9, "Target Pitch   %.1f ", (FP)((PitchIntercept - pitch) / 182.04));
//DeadCode CSB 29/03/99	PrintVar(60, 10, "Target Range   %.0f ", (FP)(Range / 100));
//DeadCode CSB 29/03/99		
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99				if (Range>MILES02)
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99				{
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99					Bool
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99						level=CalcVelSub (classtype->cruisevel);	//20mph above cruise
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99						level&=CalcHdgRoll ();
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99						level&=AutoCalcPitch ();
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99					if (level)
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99			 			SetManoeuvreTime(FIVESECS100);
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99				}
//DeadCode CSB 29/03/99	//DeadCode CSB 24/03/99				else
//DeadCode CSB 29/03/99					{
//DeadCode CSB 29/03/99						SWord DeltaHdg = (SWord)(HdgIntercept - hdg);
//DeadCode CSB 29/03/99						if((DeltaHdg > ANGLES_90Deg) || (DeltaHdg < -ANGLES_90Deg))
//DeadCode CSB 29/03/99						{	//past! go out and try again
//DeadCode CSB 29/03/99							HdgIntercept=hdg;
//DeadCode CSB 29/03/99							CalcVelSub (classtype->cruisevel);	//20mph above cruise
//DeadCode CSB 29/03/99							Bool level = CalcHdgRoll ();
//DeadCode CSB 29/03/99							level&=AutoCalcPitch ();
//DeadCode CSB 29/03/99							if (level)
//DeadCode CSB 29/03/99					 			SetManoeuvreTime(30*SECS100);
//DeadCode CSB 29/03/99						}
//DeadCode CSB 29/03/99						else
//DeadCode CSB 29/03/99						{
//DeadCode CSB 29/03/99							PitchIntercept+=PitchIntercept;
//DeadCode CSB 29/03/99							CalcVelSub (classtype->cruisevel);	//20mph above cruise
//DeadCode CSB 29/03/99							if (CalcHdgRoll ())
//DeadCode CSB 29/03/99							//
//DeadCode CSB 29/03/99							//Calc intercept point:
//DeadCode CSB 29/03/99							//	time comes from horizontal distance. oom 100,000cm/100m/s->1000 cs , 200,000cm->2000cs
//DeadCode CSB 29/03/99							//	s=ut+1/2att							 oom 50,000 cm, 200,000 cm
//DeadCode CSB 29/03/99							//    mm/cs  
//DeadCode CSB 29/03/99							//
//DeadCode CSB 29/03/99							{	
//DeadCode CSB 29/03/99								int NumberOfACs = waypoint->skipover - waypoint->skipunder;
//DeadCode CSB 29/03/99								Range += 1000 * NumberOfACs;
//DeadCode CSB 29/03/99		
//DeadCode CSB 29/03/99								int	t  = Range * 10 / velhori; //t in cs
//DeadCode CSB 29/03/99								int	t2 = t * t / 2;
//DeadCode CSB 29/03/99								int	d  = t * -vely + t2;   //d in mm
//DeadCode CSB 29/03/99								int	h  = World.Y - (despos.Y - waypoint->World.Y);
//DeadCode CSB 29/03/99								if ((ULong)(h * 10 + 20000 - d) < 40000)
//DeadCode CSB 29/03/99								{	//drop bomb now!
//DeadCode CSB 29/03/99									ai.ManStep = 1;
//DeadCode CSB 29/03/99									SetManoeuvreTime(10*SECS100);
//DeadCode CSB 29/03/99									PrintString(50, 20, "**** BOMBS AWAY ****");
//DeadCode CSB 29/03/99								}
//DeadCode CSB 29/03/99								if(h < -20000) 
//DeadCode CSB 29/03/99								{
//DeadCode CSB 29/03/99									PitchIntercept = ANGLES_0Deg;
//DeadCode CSB 29/03/99									if((pitch < ANGLES_5Deg) && (pitch > -ANGLES_5Deg))
//DeadCode CSB 29/03/99										SetManoeuvreTime(3 * t);	//Fly to over the target and then the same distance twice again.
//DeadCode CSB 29/03/99								}
//DeadCode CSB 29/03/99		
//DeadCode CSB 29/03/99							}
//DeadCode CSB 29/03/99							AutoCalcPitch ();
//DeadCode CSB 29/03/99						}
//DeadCode CSB 29/03/99					}
//DeadCode CSB 29/03/99					CalcXYZVel();
//DeadCode CSB 29/03/99				}
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99			if(ai.ManStep == 1) 
//DeadCode CSB 29/03/99				Trans_Obj.DropOneBomb((mobileitem* )this,*currworld);
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99			NewPosition ();
//DeadCode CSB 29/03/99			SetFlightParams ();
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		}
//DeadCode CSB 29/03/99		else
//DeadCode CSB 29/03/99		{
//DeadCode CSB 29/03/99			if(fly.leadflight != NULL)
//DeadCode CSB 29/03/99				if(fly.leadflight->ai.ManStep == 1) 
//DeadCode CSB 29/03/99					Trans_Obj.DropOneBomb((mobileitem* )this,*currworld);
//DeadCode CSB 29/03/99			
//DeadCode CSB 29/03/99			AutoFollowWpWing();
//DeadCode CSB 29/03/99		}
//DeadCode CSB 29/03/99		 
//DeadCode CSB 29/03/99	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoBomb
//Author		Mark Shaw				CSB
//Date			Fri 18 Oct 1996			25 Mar 1999

//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoBomb()
{
	Bool IsLeader = FALSE;
	if(IsThisBombLeader()) IsLeader = TRUE;

	if(ai.unfriendly == NULL)
	{
		if(IsLeader)
		{
			if((waypoint) && (waypoint->target))
				ai.unfriendly = *waypoint->target;
		}
		else
		{
			if((waypoint) && (waypoint->target))
				ai.unfriendly = *waypoint->target;

			if(ai.unfriendly == NULL)
				if((leader) && (Leader()->ai.unfriendly))
					ai.unfriendly = Leader()->ai.unfriendly;

			if(ai.unfriendly == NULL)
				if((fly.leadflight) && (fly.leadflight->ai.unfriendly))
					ai.unfriendly = fly.leadflight->ai.unfriendly;

			if(ai.unfriendly == NULL)
				INT3;
		}
	}

	if((IsLeader) && ((ai.ManStep == 0) || (ai.ManStep == 15)) && (!TimeLeft()))	//Circling - check status every 10 secs
	{
		char localduty = duty & ACTIONCODE;
		if((localduty & DA_DIVE) || (localduty & ACTIONSUBCODE != DA_HIGH))	//Level or Dive
			SetManoeuvreTime(10 * SECS100);

		if (EnoughDamage3D(ai.unfriendly))		//If target is completely destroyed	//Fix This !!!!
		{
			if((duty & DUTYMASK) == DC_CAS)		//FAC - wait around target
			{
				AirStrucPtr lead = *this;								//All aircraft stop bombing ans circle target
				for (;lead;lead=lead->fly.nextflight)
					for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
						foll->ai.ManStep = 15;
			}
			else
			{
				WayPointPtr oldwaypoint = waypoint;
				AirStrucPtr lead = *this;								//All aircraft stop bombing and circle target
				for (;lead;lead=lead->fly.nextflight)
		 			for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
						if((foll->movecode == AUTO_BOMB) && (foll->waypoint = oldwaypoint))
						{
							foll->movecode = AUTO_FOLLOWWP;
							foll->waypoint = foll->waypoint->next;
						}
			}
		}
		else
		{		//Target Not destroyed - check if everyone has run out of ammo
			Bool SomeoneStillGotAmmo = FALSE;
			AirStrucPtr lead = *this;								//All aircraft stop bombing ans circle target
			for (;lead;lead=lead->fly.nextflight)
				for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
//DeadCode AMM 07May99 					if((foll != Persons2::PlayerGhostAC) && (foll->ai.ManStep != 15))
					if((foll != Persons2::PlayerGhostAC && !foll->uniqueID.commsmove) && (foll->ai.ManStep != 15))//AMM 07May99
						SomeoneStillGotAmmo = TRUE;
			
			if(!SomeoneStillGotAmmo)
			{
				AirStrucPtr lead = *this;								//All aircraft stop bombing ans circle target
				for (;lead;lead=lead->fly.nextflight)
					for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
					{
						foll->movecode = AUTO_FOLLOWWP;
						foll->waypoint = foll->waypoint->NextWP(foll->uniqueID.count);
					}
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLEARINGAREA, MSG_CLEARINGAREA, *this, NULL, Follower()));
			}
		}
	}

	if(movecode == AUTO_FOLLOWWP)					
		AutoFollowWp();

	else
	{
		if(ai.ManStep == 15)	//Finish Bombing
		{
			AirStrucPtr MyLeader = NULL;
			if(leader) MyLeader = (AirStruc*)leader;
			if(fly.leadflight) MyLeader = fly.leadflight;
			if((MyLeader) && (MyLeader->ai.ManStep == 15) && (MyLeader->World.Y - ai.unfriendly->World.Y > 240000))
				AutoFollowWpWing();
			else
			{
				AutoOrbit(ai.unfriendly->World, 600000);	//Circle climbing to 10000 ft - outside waiting bombers
				if(World.Y - ai.unfriendly->World.Y < 300000)	PitchIntercept = ANGLES_5Deg;
				else											PitchIntercept = ANGLES_0Deg;
				AutoCalcPitch();
				CalcXYZVel();
				NewPosition ();
				SetFlightParams ();
			}
		}
		else
		{	//Not Finished Bombing
			char localduty = duty & ACTIONCODE;
			if(localduty & DA_DIVE)	//Level or Dive
			{	//Dive Bomb
				AutoBombDive();
			}
			else
			{
				localduty &= ACTIONSUBCODE;
				if(localduty == DA_HIGH)
				{	//High Level Wide Pattern Bombing Run
					AutoBombHigh();
				}
				else
				{	//Low Level Bombing Run
					AutoBombLow();
				}
			}
		}
		weap.ShootDelay = weap.ShootDelay-Timer_Code.FRAMETIME;
		if (weap.ShootDelay < 0)
			weap.ShootDelay = 0;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoBombHigh
//Author		Mark Shaw
//Date			Fri 18 Oct 1996
//
//Description	High Level Bombimg run
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoBombHigh()
{
	if(!IsThisBombLeader())
		AutoBombFollow();
	else
	{
		if(ai.ManStep == 0)
		{
			if((!CheckForWeapon(LT_BOMB)) && (!CheckForWeapon(LT_NAPALM)))
				ai.ManStep = 15;	//Finish bombimg - climbing circle
			else
			{
				SHAPE.BombBayDoors(this,ANIM_GEAR_DOWN);		//RJS 28Jun99
				ai.ManStep = 1;
			}
		}

		if (!TimeLeft())
			if(ai.ManStep == 14)		   //Stop bombing and move to next waypoint
			{
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLEARINGAREA, MSG_CLEARINGAREA, *this, NULL, Follower()));
				waypoint=waypoint->next;
				movecode=AUTO_FOLLOWWP;
				ai.ManStep = 0;

				SHAPE.BombBayDoors(this,ANIM_GEAR_UP);		//RJS 28Jun99
			}
			else
			{
				despos.X = ai.unfriendly->World.X;
				despos.Y = World.Y;
				despos.Z = ai.unfriendly->World.Z;
				InterceptandRange (&despos);
				{
					FP t = FSqrt( (World.Y - ai.unfriendly->World.Y) * 2 * 0.01 / 10);	//time for bomb to fall in secs
					FP ReqRange = t * (FP)velhori * 0.1;
					
//DeadCode CSB 17/06/99						ReqRange -= 10 * CountGroup();
					if(Range < (ReqRange - 10) * 100)	//10 metres too close to drop bombs
					{
						HdgIntercept = hdg;
		 				CalcVelAlt (classtype->cruisevel);
						Bool level = CalcHdgRoll ();
						level&=AutoCalcPitch ();
						if(level)
							SetManoeuvreTime(t * SECS100 * 3);
					}
					else
					{
						AutoCalcPitch ();
						CalcVelAlt (classtype->cruisevel);
						CalcHdgRoll();
						UWord reqdeltahdg_pos;
						SWord reqdeltahdg_sign;
						SWord reqdeltahdg = SWord(HdgIntercept - hdg);
						Math_Lib.Pos(reqdeltahdg, reqdeltahdg_pos, reqdeltahdg_sign);
						if((reqdeltahdg_pos < ANGLES_1Deg) && (Range < (ReqRange + 10) * 100))	//10 metres too far to drop bombs
						{	//drop bomb now!
							ai.ManStep = 14;
							AirStrucPtr AFollower = FindABuddyWithPlayerGivenPriority();
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DROPBOMBS_L, MSG_STARTINGTRGTRUN, *this, NULL, AFollower));
							SetManoeuvreTime(t*SECS100);
//DeadCode CSB 28/04/99								PrintString(50, 20, "**** BOMBS AWAY ****");
						}
					}
				}
				CalcXYZVel();
			}

		if(ai.ManStep == 14) 
//DeadCode CSB 11/05/99				if (Math_Lib.rnd()<10000)
				Trans_Obj.DropOneBomb((mobileitem* )this,*currworld);

		NewPosition ();
		SetFlightParams ();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoBombLow
//Author		Mark Shaw
//Date			Fri 18 Oct 1996
//
//Description	Low Level Bombing Run	eg. Napalm
//				If attack pattern is WIDE only the group leader gets past phase 0
//
//Inputs		
//					
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoBombLow()
{
	const LowLevelRun = 200000;
	const LowLevelAlt = 10000;
	const int flightpos = position();

	char localduty = duty & ACTIONSUBCODE;
	if((localduty == DA_WIDE) && (!IsThisBombLeader()))
		AutoBombFollow();
	else
	switch(ai.ManStep)
	{
		case 0:	//Circle around Target
		case 1: //Circle around Target - Count X seconds		//Delay from last attacker
		{
			int MaxOrbitAlt = ai.unfriendly->World.Y + 150000;
			if((waypoint) && (waypoint->World.Y > MaxOrbitAlt)) MaxOrbitAlt = waypoint->World.Y;

			if(MaxOrbitAlt > 250000) MaxOrbitAlt = 250000;
			MaxOrbitAlt += 10000;
			int MinOrbitAlt = MaxOrbitAlt - 20000;

			AirStrucPtr MyLeader = NULL;
			Bool CanFollow = FALSE;
			if(ai.ManStep == 0)
			{
				if(leader)			MyLeader = (AirStruc*)leader;
				if(fly.leadflight)	MyLeader = fly.leadflight;
//DeadCode CSB 12/05/99					if((MyLeader) && (MyLeader->ai.ManStep == 0) && (MyLeader->World.Y - ai.unfriendly->World.Y > 240000))
				if((MyLeader) && (MyLeader->movecode == AUTO_BOMB) && (MyLeader->ai.ManStep == 0) && (MyLeader->World.Y > MinOrbitAlt))
					CanFollow = TRUE;
			}
			if(CanFollow)
				AutoFollowWpWing(MyLeader);
			else
			{
				AutoOrbit(ai.unfriendly->World, 500000);
				if(World.Y > MaxOrbitAlt)	PitchIntercept = ANGLES_320Deg;
				else 
//DeadCode CSB 12/05/99					if(World.Y - ai.unfriendly->World.Y < 240000)	PitchIntercept = ANGLES_10Deg;
				if(World.Y < MinOrbitAlt)	PitchIntercept = ANGLES_10Deg;
				else						PitchIntercept = ANGLES_0Deg;
				AutoCalcPitch();
				CalcXYZVel();
				NewPosition ();
				SetFlightParams ();
			}

			//Check to see if you can select a target and start a bombing attack
			Bool CanChooseTarget = FALSE;
			if(ai.ManStep == 0)
			{
				if(IsThisBombLeader())
				{
					if(manoeuvretime == Timer_Code.FRAMETIME)
						CanChooseTarget = TRUE;
				}
				else
					if(!TimeLeft()) 
					{
						CanChooseTarget = TRUE;
						SetManoeuvreTime(SECS100 / 2);
					}
			}

			if(CanChooseTarget)
//DeadCode CSB 12/05/99	  				if(	((World.Y - ai.unfriendly->World.Y > 240000) && (World.Y - ai.unfriendly->World.Y < 250000))
				if(	((World.Y > MinOrbitAlt) && (World.Y < MaxOrbitAlt))
					|| ((localduty == DA_SINGLEFILE) && (!IsLocalLeader())) )
				{
					Bool CanStartRun = FALSE;
					if((localduty == DA_WIDE) || ((localduty == DA_SINGLEFILE) && (!IsLocalLeader())))
						CanStartRun = TRUE;
					else
					{
						COORDS3D targetpos = ai.unfriendly->World;
						targetpos.Y = World.Y;
						FP DistSq = Distance3DSquared(&targetpos);
						if(DistSq < 550000.0 * 550000.0)
							CanStartRun = TRUE;
					}
					if(CanStartRun)
					{
//DeadCode CSB 24/05/99							if(CheckForWeapon(LT_BOMB))
						CanStartRun = SelectBombTarget(TRUE);
						if(CanStartRun)
						{
							WorldStuff*	worldptr = mobileitem::currworld;
							Trans_Obj.DumpFuel(this,*worldptr);
							SHAPE.BombBayDoors(this,ANIM_GEAR_DOWN);		//RJS 28Jun99
//DeadCode CSB 24/05/99							else
//DeadCode CSB 24/05/99								ai.ManStep = 15;
							int ElementNumber = (int)ai.manoeuvre;
							if(!SelectedElement(ai.unfriendly, ElementNumber))
							{
								AirStrucPtr buddy = FindBuddy();
								if(buddy)
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TARGETNOTIDENTIFIED, MSG_CLEAR_RPT , *this, NULL, buddy));
								ai.ManStep = 15;
							}
						}
					}
				}
				
			if(ai.ManStep == 1)
				if(!TimeLeft())
					if(CheckForWeapon(LT_BOMB))
					{
						ChooseAWeapon();
						ai.ManStep = 2;
					}
					else
						ai.ManStep = 15;

			break;
		}
		
		case 2:	//Hard Turn - dive for point ahead of target
		{	
			information = FALSE;
			int ElementNumber = (int)ai.manoeuvre;
			COORDS3D targetpos;
			bool targetlive = SelectedElement(ai.unfriendly, ElementNumber, &targetpos);
			if(!targetlive)
			{
				SelectBombTarget(FALSE);
				targetlive = SelectedElement(ai.unfriendly, ElementNumber, &targetpos);
				ai.manoeuvre = (MANOEUVRE)ElementNumber;
			}

			InterceptandRange (&targetpos);
			ANGLES targetHI = HdgIntercept;

			SWord SinHdgInt, CosHdgInt;
			Math_Lib.high_sin_cos(targetHI, SinHdgInt, CosHdgInt);
				
			FP DeltaPosX = -(FP)LowLevelRun * (FP)SinHdgInt / (FP)ANGLES_FRACT;
			FP DeltaPosZ = -(FP)LowLevelRun * (FP)CosHdgInt / (FP)ANGLES_FRACT;

			despos.X = targetpos.X + DeltaPosX;	//Dive for a point 1250m ahead of target 100m above
			despos.Z = targetpos.Z + DeltaPosZ;
			despos.Y = targetpos.Y + LowLevelAlt;
					
			InterceptandRange (&despos);	//End of dive
			CalcVelAlt (classtype->maxdivevel);	
			AutoCalcPitch ();
			
			UWord reqdeltahdg_pos;
			SWord reqdeltahdg_sign;
			SWord reqdeltahdg = SWord(targetHI - hdg);
			Math_Lib.Pos(reqdeltahdg, reqdeltahdg_pos, reqdeltahdg_sign);
//CSB			if(reqdeltahdg_pos > ANGLES_10Deg)
			if(reqdeltahdg_pos > ANGLES_5Deg)
			{
				SWord DesRoll = MAXCOMBATROLL;
				if(reqdeltahdg_sign == -1)
					DesRoll = -DesRoll;
				roll += RequiredDRollSub(DesRoll);
				hdg  += (Angles)(CalcHdg());
			}
			else
				CalcHdgRoll ();

			//Calc Pull out point
			int TimeToLevelOut = -(SWord)pitch * 100 / classtype->maxpitchrate;	//cs
			int HeightLoss = -TimeToLevelOut * vely / 20;	//cm
			HeightLoss = HeightLoss * 11 / 10;		//10% correction for Rounding/integration errors

			if(World.Y - HeightLoss <= despos.Y)
				ai.ManStep = 3;	//Pull Up
					
			if(reqdeltahdg_pos > ANGLES_100Deg)
				ai.ManStep = 5;
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();
			break;
		}

		case 3:	//Pull up to zero deg and do low level run
		{
			int ElementNumber = (int)ai.manoeuvre;
			bool targetlive = SelectedElement(ai.unfriendly, ElementNumber, &despos);
			if(!targetlive)
			{
				SelectBombTarget(FALSE);
				targetlive = SelectedElement(ai.unfriendly, ElementNumber, &despos);
				ai.manoeuvre = (MANOEUVRE)ElementNumber;
			}

			despos.Y = World.Y;
			InterceptandRange (&despos);
			AutoCalcPitch();
			CalcVelAlt (classtype->cruisevel);	
			CalcHdgRoll();

			UWord reqdeltahdg_pos;
			SWord reqdeltahdg_sign;
			SWord reqdeltahdg = SWord(HdgIntercept - hdg);
			Math_Lib.Pos(reqdeltahdg, reqdeltahdg_pos, reqdeltahdg_sign);
			if(reqdeltahdg_pos < ANGLES_5Deg)
			{
				char localduty = duty & ACTIONSUBCODE;
//DeadCode CSB 17/06/99					if(localduty == DA_WIDE)	//Group drops bombs spread over target area
//DeadCode CSB 17/06/99						if(waypoint)
//DeadCode CSB 17/06/99							if(waypoint->skipunder)
//DeadCode CSB 17/06/99								Range -= 10 * (waypoint->skipover - waypoint->skipunder);
				int	t  = Range * 10 / velhori; //t in cs
				int	t2 = t * t / 2;
				int	d  = t * -vely + t2;   //d in mm   ut + 1/2 at2
				int	h  = World.Y - ai.unfriendly->World.Y;
				if ((ULong)(h * 10 + LowLevelAlt - d) < 20000)	  // +- 10 m height
				{
					ai.ManStep = 14;	//Drop Bombs

					if(IsThisBombLeader())
					{
						AirStrucPtr AFollower = NULL;
						if(localduty == DA_WIDE)
							AFollower = FindABuddyWithPlayerGivenPriority();
						else
							if(localduty == DA_SPACEDFLT)
								AFollower = PlayerInFlight();
						if(!AFollower)
							AFollower = FindBuddy();

						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DROPBOMBS_L, MSG_STARTINGTRGTRUN, *this, NULL, AFollower));
					}
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DROPBOMBS_F, MSG_STARTINGTRGTRUN, *this, NULL, GroupLeader()));

					SetManoeuvreTime(10 * SECS100);
				}
			}

			if(reqdeltahdg_pos > ANGLES_30Deg)
				ai.ManStep = 5;
			
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();
			break;
		}

		case 14:	//Drop Some Bombs
		{
			Trans_Obj.DropOneBomb((mobileitem* )this,*currworld);
			NewPosition ();
			SetFlightParams ();

			if(!TimeLeft()) 
			{
				ai.ManStep = 5;
				SHAPE.BombBayDoors(this,ANIM_GEAR_UP);		//RJS 28Jun99
			}
			break;
		}

		case 5:
		{
			HdgIntercept = hdg;
			PitchIntercept = ANGLES_20Deg;
			AutoCalcPitch();
			CalcHdgRoll();
			CalcVelAlt (classtype->cruisevel);	
			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();
			if(World.Y - ai.unfriendly->World.Y > 75000)	//2500 ft
				if(!CheckForWeapon(LT_BOMB))
					ai.ManStep = 15;	//End Bombing - go to climbing orbit
				else
				{
					ai.ManStep = 0;		//Go into orbit ready for next attack
					SetManoeuvreTime(10 * SECS100);

					char localduty = duty & ACTIONSUBCODE;
					switch(localduty)
					{
						case DA_WIDE:
						{
							if(uniqueID.count != FindLeadUID())
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BRINGAROUND, MSG_SECONDRUN, *this, NULL, Follower()));			
							break;
						}
		
						case DA_ELEMENT:
						case DA_SPACEDELT:
						{
							if((flightpos == 0) || (flightpos == 2))
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BRINGAROUND, MSG_SECONDRUN, *this, NULL, Follower()));			
							break;
						}

						case DA_SPACEDFLT:
						{
							if(flightpos == 0)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BRINGAROUND, MSG_SECONDRUN, *this, NULL, Follower()));			
							break;
						}

						case DA_SINGLEFILE:
						case DA_INDIVIDUAL:
						case DA_SPACEDIND:
						{
							break;
						}
						break;
					}
				}
		}
		break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoBombDive
//Author		Mark Shaw
//Date			Fri 18 Oct 1996
//
//Description	Dive Bombing Attack
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AutoBombDive()
{
	const int flightpos = position();

	switch(ai.ManStep)
	{
		case 0:	//Circle around Target
		case 1: //Circle around Target - Count X seconds		//Delay from last attacker
		{
			int MaxOrbitAlt = ai.unfriendly->World.Y + 150000;
			if((waypoint) && (waypoint->World.Y > MaxOrbitAlt)) MaxOrbitAlt = waypoint->World.Y;

			if(MaxOrbitAlt > 250000) MaxOrbitAlt = 250000;
			MaxOrbitAlt += 10000;
			int MinOrbitAlt = MaxOrbitAlt - 20000;

			AirStrucPtr MyLeader = NULL;
			Bool CanFollow = FALSE;
			if(ai.ManStep == 0)
			{
				if(leader)			MyLeader = (AirStruc*)leader;
				if(fly.leadflight)	MyLeader = fly.leadflight;
//DeadCode CSB 12/05/99					if((MyLeader) && (MyLeader->ai.ManStep == 0) && (MyLeader->World.Y - ai.unfriendly->World.Y > 240000))
				if((MyLeader) && (MyLeader->movecode == AUTO_BOMB) && (MyLeader->ai.ManStep == 0) && (MyLeader->World.Y > MinOrbitAlt))
					CanFollow = TRUE;
			}
			if(CanFollow)
				AutoFollowWpWing(MyLeader);
			else
			{
				AutoOrbit(ai.unfriendly->World, 500000);
				if(World.Y > MaxOrbitAlt)	PitchIntercept = ANGLES_320Deg;
				else 
//DeadCode CSB 12/05/99					if(World.Y - ai.unfriendly->World.Y < 240000)	PitchIntercept = ANGLES_10Deg;
				if(World.Y < MinOrbitAlt)	PitchIntercept = ANGLES_10Deg;
				else						PitchIntercept = ANGLES_0Deg;
				AutoCalcPitch();
				CalcXYZVel();
				NewPosition ();
				SetFlightParams ();
			}

			//Check to see if you can select a target and start a bombing attack
			Bool CanChooseTarget = FALSE;
			if(ai.ManStep == 0)
			{
				if(IsThisBombLeader())
				{
					if(manoeuvretime == Timer_Code.FRAMETIME)
						CanChooseTarget = TRUE;
				}
				else
					if(!TimeLeft()) 
						CanChooseTarget = TRUE;
			}

			if(CanChooseTarget)
			{
				char localduty = duty & ACTIONSUBCODE;

				if(	((World.Y > MinOrbitAlt) && (World.Y < MaxOrbitAlt))
					|| ((localduty == DA_SINGLEFILE) && (!IsLocalLeader())) )
				{
					Bool CanStartRun = FALSE;
					if((localduty == DA_WIDE) || ((localduty == DA_SINGLEFILE) && (!IsLocalLeader())))
						CanStartRun = TRUE;
					else
					{
						COORDS3D targetpos = ai.unfriendly->World;
						targetpos.Y = World.Y;
						FP DistSq = Distance3DSquared(&targetpos);
						if(DistSq < 550000.0 * 550000.0)
							CanStartRun = TRUE;
					}
					if(CanStartRun)
					{
//DeadCode CSB 24/05/99							if(CheckForAnyWeapon())
						CanStartRun = SelectBombTarget(TRUE);
						if(CanStartRun)
						{
							WorldStuff*	worldptr = mobileitem::currworld;
							Trans_Obj.DumpFuel(this,*worldptr);
//DeadCode CSB 24/05/99							else
//DeadCode CSB 24/05/99								ai.ManStep = 15;
							int ElementNumber = (int)ai.manoeuvre;
							if(!SelectedElement(ai.unfriendly, ElementNumber))
							{
								AirStrucPtr buddy = FindBuddy();
								if(buddy)
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TARGETNOTIDENTIFIED, MSG_CLEAR_RPT , *this, NULL, buddy));
								ai.ManStep = 15;
							}
						}
					}
				}
			}
			
			if(ai.ManStep == 1)
				if(!TimeLeft())
					if(CheckForAnyWeapon())
					{
						ChooseAWeapon();
						ai.ManStep = 2;
					}
					else
						ai.ManStep = 15;

			break;
		}
		
		case 2:	//Hard Turn - dive for target - don't count
		{	
			information = FALSE;
			int ElementNumber = (int)ai.manoeuvre;
			bool targetlive = SelectedElement(ai.unfriendly, ElementNumber, &despos);
			if(!targetlive)
			{
				SelectBombTarget(FALSE);
				targetlive = SelectedElement(ai.unfriendly, ElementNumber, &despos);
				ai.manoeuvre = (MANOEUVRE)ElementNumber;
			}

			InterceptandRange (&despos);

			CalcVelAlt (classtype->cruisevel);	
			AutoCalcPitch ();

			UWord reqdeltahdg_pos;
			SWord reqdeltahdg_sign;
			SWord reqdeltahdg = SWord(HdgIntercept - hdg);
			Math_Lib.Pos(reqdeltahdg, reqdeltahdg_pos, reqdeltahdg_sign);
//CSB			if(reqdeltahdg_pos > ANGLES_10Deg)
			if(reqdeltahdg_pos > ANGLES_5Deg)
			{
				SWord DesRoll = MAXCOMBATROLL;
				if(reqdeltahdg_sign == -1)
					DesRoll = -DesRoll;
				roll += RequiredDRollSub(DesRoll);
				hdg  += (Angles)(CalcHdg());
			}
			else
				CalcHdgRoll ();

			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();

			//Calc Pull out point
			int TimeToLevelOut = -(SWord)pitch * 100 / classtype->maxpitchrate;	//cs
			int HeightLoss = -TimeToLevelOut * vely / 20;	//cm
			HeightLoss = HeightLoss * 11 / 10;		//10% correction for Rounding/integration errors
			SWord DiveTimeLeft = 1;
			if(vely < 0) 
			{
				FP fDiveTimeLeft = -((FP)World.Y - (FP)despos.Y - (FP)HeightLoss - 10000.0) * 10.0 / (FP)vely;	//cs
				if(fDiveTimeLeft < 32767)
					DiveTimeLeft = fDiveTimeLeft;
			}

			UWord deltahdg_pos	,deltapitch_pos;
			SWord deltahdg_sign	,deltapitch_sign;

			Math_Lib.Pos((SWord)(PitchIntercept - pitch), deltapitch_pos, deltapitch_sign);
			Math_Lib.Pos((SWord)(HdgIntercept   - hdg  ), deltahdg_pos  , deltahdg_sign  );
				
			if((deltapitch_pos < ANGLES_2_5Deg) && (deltahdg_pos < ANGLES_2_5Deg) && (targetlive))
			{
				if(weap.weapontype == LT_BULLET)	//1 second life
					if((Range < 10 * (vel + classtype->muzzlevel)) && (DiveTimeLeft > 150))					
					{
												
						FireABullet(150);
					}
						
				if(weap.weapontype == LT_ROCKET)
					if((DiveTimeLeft < 150) && (DiveTimeLeft > 50))
					{
						FireARocket(0);
						weap.ShootDelay -= Timer_Code.FRAMETIME;
					}
	
			}
			if(DiveTimeLeft < 0)
				ai.ManStep = 3;	//Pull Up

				
//DeadCode CSB 06/04/99	if(uniqueID.count == waypoint->skipunder)
//DeadCode CSB 06/04/99	{
//DeadCode CSB 06/04/99	PrintVar(40,  8, "Pitch %.1f ", (FP)(pitch / 182.04));
//DeadCode CSB 06/04/99	PrintVar(40,  9, "Vel   %.1f ", (FP)(vel / 10));
//DeadCode CSB 06/04/99	PrintVar(40, 10, "Alt   %.0f ", (FP)(World.Y / 100));
//DeadCode CSB 06/04/99	}
			break;
		}

		case 3:	//Pull up to 20 deg
		{
			int ElementNumber = (int)ai.manoeuvre;
			bool targetlive = SelectedElement(ai.unfriendly, ElementNumber, &despos);
			HdgIntercept = hdg;
			PitchIntercept = ANGLES_20Deg;
			AutoCalcPitch();
//DeadCode CSB 06/04/99	if((SLong)pitch * OldPitch <= 0)
//DeadCode CSB 06/04/99		PrintVar(60, 2, "MinAlt %.0f ", (FP)((World.Y - despos.Y) / 100));
			CalcHdgRoll();
			CalcVelAlt (classtype->cruisevel);	

			CalcXYZVel();
			NewPosition ();
			SetFlightParams ();

			if(weap.weapontype == LT_BOMB)
			{
//DeadCode CSB 29/06/99					UWord reqdeltahdg_pos;
//DeadCode CSB 29/06/99					SWord reqdeltahdg_sign;
//DeadCode CSB 29/06/99					SWord reqdeltahdg = SWord(HdgIntercept - hdg);
//DeadCode CSB 29/06/99					Math_Lib.Pos(reqdeltahdg, reqdeltahdg_pos, reqdeltahdg_sign);
//DeadCode CSB 29/06/99					if((reqdeltahdg_pos < ANGLES_5Deg) && (targetlive))
				if(targetlive)
				{
					COORDS3D despos2 = despos;
					despos2.Y = World.Y;

					InterceptandRange (&despos2);	//Only used here for bombing range
					int	t  = Range * 10 / velhori; //t in cs
					int	t2 = t * t / 2;
					int	d  = t * -vely + t2;   //d in mm
					int	h  = World.Y - ai.unfriendly->World.Y;
					if ((ULong)(h * 10 + 20000 - d) < 40000)
					{
						Trans_Obj.DropOneBomb((mobileitem* )this,*currworld);	//drop bomb now!
						Trans_Obj.DropOneBomb((mobileitem* )this,*currworld);	//drop bomb now!

						if(IsThisBombLeader())
						{
							AirStrucPtr callee = NULL;
							char localduty = duty & ACTIONSUBCODE;

							if(localduty == DA_SPACEDFLT)
								callee = PlayerInFlight();
							if(!callee)
								callee = FindBuddy();

							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DROPBOMBS_L, MSG_STARTINGTRGTRUN, *this, NULL, callee));
						}
						else
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DROPBOMBS_F, MSG_STARTINGTRGTRUN, *this, NULL, FindBuddy()));
					}
				}
			}
	
			if(World.Y > despos.Y + 75000)	//2500 ft
				ai.ManStep = 4;	//Go in again or go to next waypoint

			break;
		}

		case 4:
		{
			NewPosition ();
			SetFlightParams ();

			if(!CheckForAnyWeapon())
				ai.ManStep = 15;	//End Bombing - go to climbing orbit
			else
			{
				ai.ManStep = 0;		//Go into orbit ready for next attack
				SetManoeuvreTime(10 * SECS100);

				if(IsThisBombLeader())
				{
					char localduty = duty & ACTIONSUBCODE;
					AirStrucPtr AFollower = NULL;
					if(localduty == DA_SPACEDFLT)
						AFollower = PlayerInFlight();
					if(!AFollower) 
						AFollower = FindBuddy();
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BRINGAROUND, MSG_SECONDRUN_RPT, *this, NULL, AFollower));			
				}

//DeadCode CSB 23/05/99					char localduty = duty & ACTIONSUBCODE;
//DeadCode CSB 23/05/99					switch(localduty)
//DeadCode CSB 23/05/99					{
//DeadCode CSB 05/04/99						case DA_WIDE:
//DeadCode CSB 05/04/99						{
//DeadCode CSB 05/04/99							if(uniqueID.count != waypoint->skipunder)
//DeadCode CSB 05/04/99								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BRINGAROUND, MSG_SECONDRUN, *this, NULL, Follower()));			
//DeadCode CSB 05/04/99							break:
//DeadCode CSB 05/04/99						}
//DeadCode CSB 23/05/99	
//DeadCode CSB 23/05/99						case DA_ELEMENT:
//DeadCode CSB 23/05/99						case DA_SPACEDELT:
//DeadCode CSB 23/05/99						{
//DeadCode CSB 23/05/99							if((flightpos == 0) || (flightpos == 2))
//DeadCode CSB 23/05/99								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BRINGAROUND, MSG_SECONDRUN, *this, NULL, Follower()));			
//DeadCode CSB 23/05/99							break;
//DeadCode CSB 23/05/99						}
//DeadCode CSB 23/05/99	
//DeadCode CSB 23/05/99						case DA_SPACEDFLT:
//DeadCode CSB 23/05/99						{
//DeadCode CSB 23/05/99							if(flightpos == 0)
//DeadCode CSB 23/05/99								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BRINGAROUND, MSG_SECONDRUN, *this, NULL, Follower()));			
//DeadCode CSB 23/05/99							break;
//DeadCode CSB 23/05/99						}
//DeadCode CSB 23/05/99	
//DeadCode CSB 23/05/99						case DA_SINGLEFILE:
//DeadCode CSB 23/05/99						case DA_INDIVIDUAL:
//DeadCode CSB 23/05/99						case DA_SPACEDIND:
//DeadCode CSB 23/05/99						{
//DeadCode CSB 23/05/99							break;
//DeadCode CSB 23/05/99						}
//DeadCode CSB 23/05/99						break;
//DeadCode CSB 23/05/99					}
			}
		}
 
		break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoBombFollow
//Author		Craig Beeston
//Date			Tue 11 May 1999
//
//Description	For high or wide bombing runs.  Aircraft just run AFWPW and drop bomb.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AutoBombFollow()
{
	AirStrucPtr lf = NULL;
	Bool GoToAutoFollowWp = FALSE;

	lf = FindGroupLeader();
	if((!lf) && (leader)) lf = Leader();
	else 
		if((!lf) && (fly.leadflight)) lf = fly.leadflight;

//DeadCode CSB 13/07/99		if(lf == NULL) 
//DeadCode CSB 13/07/99			int breakpoint = 0;


	AutoFollowWpWing();

	switch(ai.ManStep)
	{
		case 0:
		{
			SHAPE.BombBayDoors(this,ANIM_GEAR_DOWN);		//RJS 28Jun99
			if(lf->ai.ManStep >= 14)	
			{
				SetManoeuvreTime(Math_Lib.rnd(256));
				ai.ManStep = 13;
			}
			if(lf->movecode == AUTO_FOLLOWWP)
				GoToAutoFollowWp = TRUE;
			break;
		}

		case 13:
		{
			if(!TimeLeft())
				ai.ManStep = 14;
			break;
		}

		case 14:
		{
			if(Trans_Obj.DropOneBomb((mobileitem* )this,*currworld) == 0)
			{
				SHAPE.BombBayDoors(this,ANIM_GEAR_UP);		//RJS 28Jun99
				ai.ManStep = 5;
			}
			break;
		}

		case 5:
		{
			if(lf->movecode == AUTO_FOLLOWWP)
				GoToAutoFollowWp = TRUE;
			break;
		}
		break;
	}

	if(GoToAutoFollowWp)
	{
		movecode = AUTO_FOLLOWWP;
		waypoint = lf->waypoint;
		SetManoeuvreTime(0);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoOrbit
//Author		Craig Beeston 
//Date			Wed 31 Mar 1999
//
//Description	makes an aircraft orbit a given point with a circle of given radius
//
//Inputs		Centre, Radius
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AutoOrbit(COORDS3D centre, int radius)
{
	centre.Y = World.Y;		//ignore vertical distance
	InterceptandRange(&centre);
	
//DeadCode CSB 06/04/99	PrintVar(60, 15, "Range %.0f ", (FP)(Range / 100));
//DeadCode CSB 06/04/99	PrintVar(60, 16, "Headg %.0f ", (FP)((HdgIntercept - hdg) / 182.04));
//DeadCode CSB 06/04/99	PrintVar(60, 17, "Roll  %.0f ", (FP)(roll / 182.04));

	FP HdgOffset = ANGLES_90Deg;

	FP RadiusCorrector = ((FP)Range - (FP)radius) / 500000.0;
	MODLIMIT(RadiusCorrector, 1);
//DeadCode CSB 06/04/99	PrintVar(60, 18, "HdgCo %.0f ", (FP)(90 * RadiusCorrector));
	HdgOffset -= RadiusCorrector * HdgOffset;
	HdgIntercept += (Angles)((SWord)HdgOffset);
	
	SWord reqdeltahdg = SWord(HdgIntercept - hdg);
	SWord reqdeltahdg_pos;
	if(reqdeltahdg >= 0) reqdeltahdg_pos =  reqdeltahdg;
	else				 reqdeltahdg_pos = -reqdeltahdg;
	if((reqdeltahdg_pos < ANGLES_1Deg) && (RadiusCorrector > -1) && (RadiusCorrector < 1))
	{
		if(reqdeltahdg > 0) HdgIntercept = hdg + ANGLES_1Deg;
		else				HdgIntercept = hdg - ANGLES_1Deg;
	}
	CalcHdgRoll();

//	SWord IdealRoll = (vel * vel) / (GRAVITY * radius);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindDesPos
//Author		R. Hyde 
//Date			Tue 28 Nov 1995									//JIM 01May96
//
//Description	Find position indicated by waypoint
//				by acumulating waypoint and backupwp and waypoint target.
//				SIMILAR CODE ALERT
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
COORDS3D* AirStruc::FindDesPos ()

{
//DeadCode RDH 27Feb96 	static	COORDS3D despos;
	COORDS3D	*base=NULL;

//DeadCode JIM 05Aug96 	assert(waypoint&&"still moving off end of list");			//JIM 28Mar96
	if (waypoint)
	{
		despos=waypoint->World;
		desposrange= waypoint->range;

		if (waypoint->target != NULL)
		{//	relative to WP target
			base = &waypoint->target->World;
		}else
		{
			if (fly.backupWP == NULL)
			{// WP is absolute
				despos=waypoint->World;
			return (&despos);
			}else
			{
				if (fly.backupWP->target != NULL)
				{// relative to backupWP target
					base = &fly.backupWP->target->World;
				}else
				{// Wp is relative to backupWP  
					base = &fly.backupWP->World;
				}
			}

		}

		if (base)
		{
			despos.X += base->X;
			despos.Y += base->Y;
			if (base->Y==0)			//cludge to bypass missing ground popping in!
				despos.Y+=METRES1000;
			despos.Z += base->Z;
		}
	}
	else														//RDH 06Aug96
	{
		assert(ai.homebase && "Null waypoint pointer and no home to go to!");
		despos=ai.homebase->World;
		if (ai.homebase->uniqueID.count==UID_Japan && World.Z-despos.Z<METRES2000)
		{
			despos.X+=500*METRES1000;
			despos.Z-=300*METRES1000;
		}
		despos.Y+=METRES800;									//JIM 02Dec96
		desposrange= METRES1600;								//JIM 02Dec96
	}
	if (despos.Y<=0)
	{
		despos.Y=Land_Scape.GetGroundLevel(despos)-despos.Y;
	}
	return(&despos);

}
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindDesPos
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	Finddespos for simpler items - no backup.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
COORDS3D* mobileitem::FindDesPos ()
{
 	return	waypoint->FindDesPos();
}

COORDS3D* FindDesPos(WayPointPtr w)	{return (w->FindDesPos());}

COORDS3D* WayPoint::FindDesPos ()
{
//DeadCode RDH 27Feb96 	static	COORDS3D despos;
	COORDS3D	*base,*offset;

	if (this==NULL)													//JIM 21Nov96
		_Error.EmitSysErr("still moving off end of list");		//JIM 21Nov96

	desposrange= range;
	if (target != NULL)
	{//	relative to WP target
		if (target->uniqueID.count<WayPointBAND || target->uniqueID.count>=WayPointBANDEND)
			base = &target->World;
		else
			base=::FindDesPos(*target);
		offset = &World;
		if (base->Y==0 && offset->Y<0)
		{
			base->Y=Land_Scape.GetGroundLevel(*base);
			offset->Y=-offset->Y;
		}
		despos.X = base->X + offset->X;
		despos.Y = base->Y + offset->Y;
		despos.Z = base->Z + offset->Z;
	}
	else
	{
		if (World.Y<=0)
		{	
			int	gl=Land_Scape.GetGroundLevel(this);
			if (gl!=0)
			World.Y=gl-World.Y;
		}
		despos=World;
	}
//DeadCode JIM 29Apr96 		else
//DeadCode JIM 29Apr96 		{
//DeadCode JIM 29Apr96 			if (fly.backupWP->target != NULL)
//DeadCode JIM 29Apr96 			{// relative to backupWP target
//DeadCode JIM 29Apr96 				base = &fly.backupWP->target->World;
//DeadCode JIM 29Apr96 				offset = &World;
//DeadCode JIM 29Apr96 				target = &despos;
//DeadCode JIM 29Apr96 
//DeadCode JIM 29Apr96 			}else
//DeadCode JIM 29Apr96 			{// Wp is relative to backupWP  
//DeadCode JIM 29Apr96 				base = &fly.backupWP->World;
//DeadCode JIM 29Apr96 				offset = &World;
//DeadCode JIM 29Apr96 				target = &despos;
//DeadCode JIM 29Apr96 
//DeadCode JIM 29Apr96 			}
//DeadCode JIM 29Apr96 		}

//DeadCode PD 16Oct96 	if (despos.Y<=0)
//DeadCode PD 16Oct96 	{	//cheep tacky cludge alert!!!							//JIM 14Oct96
//DeadCode PD 16Oct96 		Land_Scape.GetGroundLevel(despos)-despos.Y;//JIM 14Oct96
//DeadCode PD 16Oct96 	}
	return (&despos);

}
	
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptandRange
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description		
//
//Inputs		
//
//Returns	"Global" Range, HdgIntercept and PitchIntercept
//
//------------------------------------------------------------------------------
int item::Distance3D (COORDS3D* target)
{
	SLong deltax = target->X - World.X;
	SLong deltay = target->Y - World.Y;
	SLong deltaz = target->Z - World.Z;
	return Math_Lib.distance3d (deltax,deltay,deltaz);
}

int item::Distance3D (COORDS3D* subject, COORDS3D* target)	//CSB 26/04/99	
{															//CSB 26/04/99	
	SLong deltax = target->X - subject->X;					//CSB 26/04/99	
	SLong deltay = target->Y - subject->Y;					//CSB 26/04/99	
	SLong deltaz = target->Z - subject->Z;					//CSB 26/04/99	
	return Math_Lib.distance3d (deltax,deltay,deltaz);		//CSB 26/04/99	
}

FP item::Distance3DSquared (COORDS3D* target)
{
	FP deltax = target->X - World.X;
	FP deltay = target->Y - World.Y;
	FP deltaz = target->Z - World.Z;
	return	deltax*deltax+deltay*deltay+deltaz*deltaz;
}

void item::InterceptandRange (COORDS3D* target)
{
	SLong deltax = target->X - World.X;
	SLong deltay = target->Y - World.Y;
	SLong deltaz = target->Z - World.Z;
	Math_Lib.Intercept (deltax,deltay,deltaz,Range,HdgIntercept,PitchIntercept);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptandRange
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description		
//
//Inputs		
//
//Returns	"Global" Range, HdgIntercept and PitchIntercept
//
//------------------------------------------------------------------------------
void item::InterceptandRange (COORDS3D* subject, COORDS3D* target)

{


	SLong deltax = target->X - subject->X;
	SLong deltay = target->Y - subject->Y;
	SLong deltaz = target->Z - subject->Z;
	Math_Lib.Intercept (deltax,deltay,deltaz,Range,HdgIntercept,PitchIntercept);
	
}

//DeadCode CSB 12/02/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 12/02/99	//Procedure		CalcVelSub
//DeadCode CSB 12/02/99	//LastModified:	RDH 26Jul96
//DeadCode CSB 12/02/99	//Author		R. Hyde 
//DeadCode CSB 12/02/99	//Date			Tue 28 Nov 1995
//DeadCode CSB 12/02/99	//
//DeadCode CSB 12/02/99	//Description	
//DeadCode CSB 12/02/99	//
//DeadCode CSB 12/02/99	//Inputs		
//DeadCode CSB 12/02/99	//
//DeadCode CSB 12/02/99	//Returns	
//DeadCode CSB 12/02/99	//
//DeadCode CSB 12/02/99	//------------------------------------------------------------------------------
//DeadCode CSB 12/02/99	Bool AirStruc::CalcVelSub (SLong reqvel)
//DeadCode CSB 12/02/99	
//DeadCode CSB 12/02/99	{
//DeadCode CSB 12/02/99		ANGLES	temppitch;
//DeadCode CSB 12/02/99		Bool	retval;
//DeadCode CSB 12/02/99	
//DeadCode CSB 12/02/99		temppitch = pitch;
//DeadCode CSB 12/02/99		pitch = fly.cpitch;
//DeadCode CSB 12/02/99		retval = formationitem::CalcVelSub(reqvel);
//DeadCode CSB 12/02/99		pitch = temppitch;
//DeadCode CSB 12/02/99		return(retval);
//DeadCode CSB 12/02/99	
//DeadCode CSB 12/02/99	
//DeadCode CSB 12/02/99	}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVelSub
//LastModified:	RDH 26Jul96
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool formationitem::CalcVelSub (SLong reqvel)

{
	SLong	accel;
	SWord	deltavel,deltavel_sign;	
	UWord	deltavel_pos;
	SLong	climb_vel;

	UWord	roll_pos;											//RDH 28Nov96
	SWord	roll_sign;											//RDH 28Nov96

	WheeledType* classtype=formationitem::classtype;
//reduce vel if climbing
	if (((SWord)pitch) > ANGLES_0Deg)
	{
		climb_vel = (classtype->maxvel - classtype->bestclimbvel) *
									(SWord) (classtype->bestclimbpitch - pitch)/(ANGLES)classtype->bestclimbpitch;
	}else
	{
		climb_vel = (classtype->maxdivevel - 20 - classtype->maxvel) *
									((SWord) pitch)/ANGLES_90Deg;

	//DeadCode RDH 17Dec96 	climb_vel = classtype->maxvel-classtype->bestclimbvel-climb_vel;
		climb_vel = classtype->maxvel - climb_vel;					//RDH 17Dec96
		
	}
//reduce vel if turning and climbing							//RDH 17Dec96

	if (((SWord)pitch) > ANGLES_0Deg)							//RDH 17Dec96
	{															//RDH 17Dec96
		Math_Lib.Pos ((SWord)roll,roll_pos,roll_sign);				//RDH 28Nov96
		climb_vel =   climb_vel * (SWord) (MAXCOMBATROLL - roll_pos)/MAXCOMBATROLL;

		climb_vel = classtype->bestclimbvel + climb_vel;
	}

	if (climb_vel > (classtype->maxdivevel-20))						//RDH 28Nov96
		climb_vel = classtype->maxdivevel-20;						//RDH 28Nov96
//DeadCode RDH 14Nov96 	if (climb_vel < classtype->bestclimbvel)
//DeadCode RDH 14Nov96 		climb_vel = classtype->bestclimbvel;
//something just over stall										//RDH 14Nov96
//really need an entry in planetype								//RDH 14Nov96
	if (climb_vel < MPH40)										//RDH 14Nov96
		climb_vel = MPH40;										//RDH 14Nov96
	if (slowdownleader)											//JIM 17Sep96
		if (formpos&InWingMAX)
			climb_vel-=50;	//10mph	25;		//5mph								//JIM 17Sep96
		else
			climb_vel-=80;	//15mph	25;		//5mph								//JIM 17Sep96
	slowdownleader=FALSE;										//JIM 17Sep96
	if (reqvel > climb_vel)
	 	reqvel = climb_vel;



	deltavel = (SWord) (reqvel - vel);
//maxaccel is a fraction, where 256 = 10 cm/s/s						//RDH 19Feb96
	accel	=  classtype->maxaccel * Timer_Code.FRAMETIME/ 25600;//DAW 31Jul96

//DeadCode CSB 12/02/99		SLong oldvel = vel;
//DeadCode CSB 12/02/99		SLong accel = CalcAccel(reqvel);
//DeadCode CSB 12/02/99		AddAccel2Vel(accel);
//DeadCode CSB 12/02/99		if( (reqvel - vel) * (reqvel - oldvel) <= 0)
//DeadCode CSB 12/02/99		{
//DeadCode CSB 12/02/99			vel = reqvel;
//DeadCode CSB 12/02/99			return(TRUE);
//DeadCode CSB 12/02/99		}
//DeadCode CSB 12/02/99		else return(FALSE);

	Math_Lib.Pos (deltavel,deltavel_pos,deltavel_sign);
	if (accel>deltavel_pos)
	{
		if (deltavel_sign == MathLib::NEGATIVE)
		 vel -= deltavel_pos;
		else
		 vel += deltavel_pos;
		return(TRUE);
	}
	elser
	{
		if (deltavel_sign == MathLib::NEGATIVE)
		 vel -= accel;
		else
		 vel += accel;
		return(FALSE);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVel
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	  
//
//------------------------------------------------------------------------------
Bool AirStruc::CalcVel ()

{
	SLong	reqvel;

	if (waypoint && waypoint->vel)
	 	reqvel =  waypoint->vel;
	else
		reqvel =  classtype->cruisevel;	
//DeadCode CSB 15/02/99		return	CalcVelSub (reqvel);
	return	CalcVelAlt (reqvel);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVel
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	  
//
//------------------------------------------------------------------------------
Bool formationitem::CalcVel ()

{
	SLong	reqvel;

	if (waypoint && waypoint->vel)
	 	reqvel =  waypoint->vel;
	else
		reqvel =  classtype->cruisevel;

	return	CalcVelSub (reqvel);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVelWing
//Author		R. Hyde 
//Date			Wed 28 Feb 1996
//
//Description	Leaders vel + some
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::CalcVelWing (AirStrucPtr lf, SLong Dist)
{
	Bool RetVal;
	if(Dist >= METRES1000)	//17 bits
		RetVal = CalcVelAlt(32000);	//Requesting mach 10. Max Vel clip expected //JIM 22/04/99
	else
	{
		SLong ReqVel = 0;
		if(Dist > 0)
		{
			SWord MaxAcc = -CalcAccel(0);	//Ensure requesting decel not accel
			FP ThingToSqrt = FP(MaxAcc) * (2.0 / 2560.0) * Dist;
			if(ThingToSqrt > 0)
				ReqVel = lf->vel + FSqrt(ThingToSqrt);
			else
				ReqVel = lf->vel;
		}
		else
		{
			SWord MaxAcc = CalcAccel(32000);	//Ensure requesting accel not decel
			FP ThingToSqrt = FP(MaxAcc) * (2.0 / 2560.0) * -Dist;
			if(ThingToSqrt > 0)
				ReqVel = lf->vel - FSqrt(ThingToSqrt);
			else
				ReqVel = lf->vel;
		}

		if(ReqVel < classtype->minvel)
			ReqVel = classtype->minvel;

		Bool RetVal = CalcVelAlt(ReqVel);
		if((Dist > 0) && (vel > ReqVel))
		{
			vel = ReqVel;
			RetVal = FALSE;
		}
		if((Dist < 0) && (vel < ReqVel))
		{
			vel = ReqVel;
			RetVal = FALSE;
		}

	}
	return(RetVal);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SideSlip
//Author		R. Hyde					Craig Beeston
//Date			Wed 28 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns		True if just got into formation
//
//------------------------------------------------------------------------------
Bool AirStruc::SideSlip (AirStrucPtr lf)
{
//DeadCode CSB 09/06/99			if(vel < lf->vel) vel = 2 * lf->vel - vel;		

//DeadCode CSB 10/05/99			COORDS3D Newdespos = despos;
//DeadCode CSB 10/05/99			Newdespos.X -= (velx * Timer_Code.FRAMETIME) / 10;
//DeadCode CSB 10/05/99			Newdespos.Y -= (vely * Timer_Code.FRAMETIME) / 10;
//DeadCode CSB 10/05/99			Newdespos.Z -= (velz * Timer_Code.FRAMETIME) / 10;

		SWord	dvel;

		PitchIntercept = lf->pitch;
		AutoCalcPitch();

		hdg 	= lf->hdg;

		SimpleMoveToRoll(lf->roll);

		dvel = vel - lf->vel;							//RDH 30Nov96
		if(dvel < 0) 
			dvel *= -1;
		
		if (dvel < 5)									//RDH 30Nov96
			dvel = 5;									//RDH 30Nov96
		vel = lf->vel + dvel;

		if(Range)
		{
			velx = lf->velx + (SWord)(dvel * (despos.X - World.X) / Range);
			vely = lf->vely + (SWord)(dvel * (despos.Y - World.Y) / Range);
			velz = lf->velz + (SWord)(dvel * (despos.Z - World.Z) / Range);
		}
		else
		{
			velx = lf->velx;
			vely = lf->vely;
			velz = lf->velz;
		}

		SWord DeltaX = (SWord)(despos.X - World.X);
		SWord DeltaY = (SWord)(despos.Y - World.Y);
		SWord DeltaZ = (SWord)(despos.Z - World.Z);
		if(DeltaX < 0) DeltaX *= -1;
		if(DeltaY < 0) DeltaY *= -1;
		if(DeltaZ < 0) DeltaZ *= -1;

		if((DeltaX < 50) && (DeltaY < 50) && (DeltaZ < 50))
			return TRUE;
		else
			return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SideSlide
//Author		Craig Beeston
//Date			Tue 20 Apr 1999
//
//Description	Gets into formation by rolling and sliding with no change in heading
//
//Inputs		
//
//Returns		True if just got into formation
//
//------------------------------------------------------------------------------
Bool AirStruc::SideSlide (AirStrucPtr lf)
{
	hdg = lf->hdg;

	COORDS3D GlobDelta, LocDelta;
	GlobDelta.X = despos.X - World.X;
	GlobDelta.Y = despos.Y - World.Y;
	GlobDelta.Z = despos.Z - World.Z;

	RotateToHdg(GlobDelta, LocDelta, hdg);

	SLong desroll = 2 * LocDelta.X;
	MODLIMIT(desroll, ANGLES_45Deg);
	SimpleMoveToRoll((SWord)desroll);

	SLong despitch = (LocDelta.Y * ANGLES_FRACT) / Range;
	MODLIMIT(despitch, ANGLES_15Deg);
	PitchIntercept = (Angles)despitch;
	SLong AbsDx = LocDelta.X;
	if(AbsDx < 0) AbsDx *= -1;
	AbsDx /= 2;
	if(AbsDx > ANGLES_20Deg) AbsDx = ANGLES_20Deg;
	PitchIntercept += AbsDx;
	AutoCalcPitch();

	SWord VelHdg = (SWord)hdg + (2 * (SWord)roll) / 10;		//Direction of travel - different from aircraft hdg

	SWord SinHdg, CosHdg, SinPitch, CosPitch;
	Math_Lib.high_sin_cos (pitch,  SinPitch, CosPitch);
	Math_Lib.high_sin_cos ((Angles)VelHdg, SinHdg,   CosHdg);

	if(LocDelta.Z > 100000)
		CalcVelAlt();	//Max Vel
	else
	{
		SLong ReqVel = 0;
		SWord MaxAcc = 0;
		if(LocDelta.Z > 0)
			MaxAcc = CalcAccel(0);		//Ensure requesting decel not accel
		else
			MaxAcc = CalcAccel(10000);	//Ensure requesting accel not decel

		FP ThingToSqrt = (-MaxAcc * LocDelta.Z) * (2.0 / 2560.0);
		if(ThingToSqrt <= 0)
			ReqVel = fly.leadflight->vel;
		else
			if(LocDelta.Z > 0)
				ReqVel = fly.leadflight->vel + FSqrt(ThingToSqrt);
			else
				ReqVel = fly.leadflight->vel - FSqrt(ThingToSqrt);
		
		CalcVelAlt(ReqVel);
	}

	vely	= (vel * SinPitch) / ANGLES_FRACT;
	velhori	= (vel * CosPitch) / ANGLES_FRACT;
	velx	= (velhori * SinHdg) / ANGLES_FRACT;
	velz	= (velhori * CosHdg) / ANGLES_FRACT;

	NewPosition ();
	SetFlightParams ();


	if(GlobDelta.X < 0) GlobDelta.X *= -1;
	if(GlobDelta.Y < 0) GlobDelta.Y *= -1;
	if(GlobDelta.Z < 0) GlobDelta.Z *= -1;

	if((GlobDelta.X < 5000) && (GlobDelta.Y < 5000) && (GlobDelta.Z < 5000))	//All within 50m
		return TRUE;
	else
		return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcHdgRollFlat
//Author		R. Hyde 
//Date			Wed 28 Feb 1996
//
//Description	allows a flat turn using rudder up to 20 deg /sec
//
//Inputs		
//
//Returns		TRUE if made the turn
//
//------------------------------------------------------------------------------
Bool formationitem::CalcHdgRollFlat ()

{
	SWord	reqdeltahdg,deltaroll;
	SLong	allowedturn;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltahdg_sign;

	reqdeltahdg = 	(SWord) (hdg - HdgIntercept);
	if (Status.size==AirStrucSize)
		MoveRollToZero(reqdeltahdg);
	else
		roll = ANGLES_0Deg;

	Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
	allowedturn = ANGLES_30Deg * Timer_Code.FRAMETIME/ 100;		//DAW 31Jul96
	if (reqdeltahdg_pos < allowedturn)
	{
		hdg = HdgIntercept;
		return(TRUE);

	}else
	{
		if (reqdeltahdg_sign==Math_Lib.POSITIVE)
		{
			hdg =  hdg - (Angles) allowedturn; 
		}else
		{
			hdg =  hdg + (Angles) allowedturn;
		}
	}
//TempCode JIM 29Apr96 	deltaroll = RequiredDRoll (0);
//TempCode JIM 29Apr96 	roll	 += (Angles) deltaroll;	
//DeadCode JIM 29Apr96 	fly.rudder = -MAXRUDDER * reqdeltahdg/ANGLES_20Deg;
//DeadCode JIM 29Apr96 	fly.aileron = 0;
	return(FALSE);

}

void	formationitem::MoveRollToZero(SWord	reqdeltahdg)
{
	AirStrucPtr	This=*this;
	roll+=(Angles)This->RequiredDRoll(0);
	if((This != Persons2::PlayerSeenAC) && (This != Persons2::PlayerGhostAC))
	{
		This->fly.rudder = -MAXRUDDER * reqdeltahdg/ANGLES_20Deg;
		This->fly.aileron = 0;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcHdgRoll
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//		 TR in deg per sec  = 360.g.tan RollAngle/(2.Pi.v)
//in Rowan units of 360 deg = 65536, v in 10cm/s units tan 45 = 256 not 1
//		 TR in cs			= 65536.98. tan roll/ 2.Pi.v.100.256 
//							=  40 tan roll /v	
//
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::CalcHdgRoll ()										  //DAW 16/06/99
{
	return AirStruc::CalcHdgRoll ((SWord) (hdg - HdgIntercept));
}
Bool AirStruc::CalcHdgRoll (SWord reqdeltahdg)

{
	SWord	deltaroll,currroll,tanroll;
//	SWord	reqdeltahdg;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltahdg_sign;
	SLong	deltahdg;
	UWord	deltahdg_pos;
	SWord	deltahdg_sign;
	Bool	retval=FALSE;

	if (Save_Data.flightdifficulty [FD_WINDEFFECTS])
				WindCorrection();
//DEADCODE DAW 16/06/99 	reqdeltahdg = 	(SWord) (hdg - HdgIntercept);
	Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode CSB 26/03/99		if ((Angles)reqdeltahdg_pos <(ANGLES)ANGLES_ThirdDeg)				//RDH 03Dec96
	if((reqdeltahdg_pos < ANGLES_ThirdDeg) && (roll != ANGLES_0Deg))
		retval=RollLevel (reqdeltahdg);
	else
	{
		deltaroll = RequiredDRoll (reqdeltahdg);
		roll	 += (Angles) deltaroll;
		deltahdg = CalcHdg();
		Math_Lib.Pos ((SWord) deltahdg, deltahdg_pos,deltahdg_sign);
		if (deltahdg_pos <reqdeltahdg_pos)
		{
			hdg =  hdg + (Angles) deltahdg; 
		}else
		{
			retval=RollLevel (reqdeltahdg);
		}
//DeadCode RDH 19Feb96 		if ((World.Y > 15000) && ((roll < ANGLES_80Deg) || (reqdeltahdg >ANGLES_260Deg)))
//DeadCode RDH 19Feb96 		{
//DeadCode RDH 19Feb96 			PitchIntercept = ANGLES_340Deg;
//DeadCode RDH 19Feb96 		}
//DeadCode RDH 11Oct96 
//DeadCode RDH 11Oct96 		if (	(roll >ANGLES_90Deg)							//RDH 24Jul96
//DeadCode RDH 11Oct96 			||	(roll < ANGLES_270Deg))							//RDH 24Jul96
//DeadCode RDH 11Oct96 		{
//DeadCode RDH 11Oct96 			currroll = -roll;
//DeadCode RDH 11Oct96 		}else
//DeadCode RDH 11Oct96 		{
//DeadCode RDH 11Oct96 			currroll = roll;
//DeadCode RDH 11Oct96 		}
//DeadCode RDH 11Oct96 		tanroll = Math_Lib.tan ((ANGLES) currroll);
//DeadCode RDH 11Oct96 //HACK
//DeadCode RDH 11Oct96 		if (vel==0)												//DAW 12Jul96
//DeadCode RDH 11Oct96 			vel=1;
//DeadCode RDH 11Oct96 //ENDHACK
//DeadCode RDH 11Oct96 		deltahdg = 40 * tanroll * Timer_Code.FRAMETIME/ vel;	//DAW 31Jul96
//DeadCode RDH 11Oct96 		Math_Lib.Pos ((SWord) deltahdg, deltahdg_pos,deltahdg_sign);
//DeadCode RDH 11Oct96 		if (deltahdg_pos <reqdeltahdg_pos)
//DeadCode RDH 11Oct96 		{
//DeadCode RDH 11Oct96 			hdg =  hdg + (ANGLES) deltahdg; 
//DeadCode RDH 11Oct96 		}else
//DeadCode RDH 11Oct96 		{
//DeadCode RDH 11Oct96 			retval=RollLevel ();
//DeadCode RDH 11Oct96 		}
	}
	if((this != Persons2::PlayerSeenAC) && (this != Persons2::PlayerGhostAC))
		fly.aileron = -MAXAILERON * reqdeltahdg/ANGLES_20Deg;
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcHdg
//Author		R. Hyde 
//Date			Fri 11 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong AirStruc::CalcHdg ()
{

	SWord	currroll,tanroll;
	SLong	deltahdg;
	UWord	deltahdg_pos;
	SWord	deltahdg_sign;
	Bool	retval=FALSE;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltahdg_sign;
	MODEL& MOD = *fly.pModel;

		if (	(roll >>ANGLES_90Deg)							//RDH 07Nov96
			&&	(roll << ANGLES_270Deg))						//RDH 07Nov96
		{
			currroll = 0-roll;
		}else
		{
			currroll = roll;
		}
		if (currroll >= 0)
		{
			if (currroll > MAXCOMBATROLL)
				currroll = MAXCOMBATROLL;
		}else
		{
			if (currroll < -((SWord)MAXCOMBATROLL))
				currroll = 0-MAXCOMBATROLL;
		}
		tanroll = Math_Lib.tan ((Angles) currroll);
//HACK
		if (vel==0)												//DAW 12Jul96
			vel=1;
//ENDHACK
//DeadCode CSB 01/04/99			deltahdg = 1+ 40 * tanroll * Timer_Code.FRAMETIME/ vel;	//DAW 31Jul96
		FP fdeltahdg = (40.0 * tanroll * Timer_Code.FRAMETIME) / vel;	//DAW 31Jul96
		if(fdeltahdg >  32767) fdeltahdg =  32767;
		if(fdeltahdg < -32767) fdeltahdg = -32767;
		deltahdg = fdeltahdg;
// I reckon this 40 should be a 38 (.30664) 1000 * g / 256	//CSB 18/09/98
//stop turning on sixpence										//RDH 07Nov96

//DeadCode CSB 01/06/99			if (deltahdg > 100)
//DeadCode CSB 01/06/99				deltahdg = 100 + (deltahdg - 100)/8;

//	Stop the simple aircraft from turning faster than the flight model aircraft can	//CSB 01/06/99	
		int maxdelta = (CalcMaxPitchRate() * Timer_Code.FRAMETIME) / 100;	//CSB 01/06/99	
		if(deltahdg > maxdelta)												//CSB 01/06/99	
			deltahdg = maxdelta;											//CSB 01/06/99	
		if(-deltahdg > maxdelta)											//CSB 03/06/99	
			deltahdg = -maxdelta;											//CSB 03/06/99	

//	fly.turnrate = (fly.turnrate +
//								(SLong)(((deltahdg) * 100) / Timer_Code.FRAMETIME))/2;

//rads per cs
	MOD.Inst.turn = (MOD.Inst.turn + (Rowan2Rads(deltahdg) ) / Timer_Code.FRAMETIME)/2;
	
	return(deltahdg);


}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WindCorrection
//Author		R. Hyde 
//Date			Fri 30 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::WindCorrection()
{
	//rdh change to MA wind
//	SWord	sinhdg,coshdg,temppitch;
//	SLong	time;
//	SLong	deltax,deltay,deltaz;
//
//	time =  Range/vel;	//1/10s
//	Math_Lib.high_sin_cos(HdgIntercept,sinhdg,coshdg); 

////DeadCode RDH 24Oct96 	deltax =  Range * sinhdg/ANGLES_FRACT + Save_Data.wind.velx	* time;
//	deltax =  MULSHSIN(Range,sinhdg,ANGLES_SHIFT) + MMC.wind.velx	* time;
//	deltay = 0;
////DeadCode RDH 24Oct96 	deltaz =  Range * coshdg/ANGLES_FRACT + Save_Data.wind.velz	* time;
//	deltaz =  MULSHSIN(Range,coshdg,ANGLES_SHIFT) + MMC.wind.velz	* time;
//	temppitch = PitchIntercept;
//	Math_Lib.Intercept (deltax,deltay,deltaz,Range,HdgIntercept,PitchIntercept);
//	PitchIntercept = (Angles)temppitch;

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RollLevel
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::RollLevel (int reqdeltahdg)

{
		SWord	deltaroll;

		hdg = Angles(hdg-reqdeltahdg); //not always got hdgintercept filled in!
	 	deltaroll = classtype->maxrollrate * Timer_Code.FRAMETIME/ 100;//DAW 31Jul96
	 	if ( !(roll & ANGLES_180Deg))
		{
			deltaroll = -deltaroll;
		}
		roll =  roll + (Angles) deltaroll;
	
	 	if ( (roll & ANGLES_180Deg) == (deltaroll & ANGLES_180Deg ))
		{
			roll =ANGLES_0Deg;
			return(TRUE);
		}
		return(FALSE);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoCalcPitch
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool formationitem::AutoCalcPitch ()

{
	SWord	reqdeltapitch, deltapitch;
	UWord	reqdeltapitch_pos;
	SWord	reqdeltapitch_sign;
	Bool	retval=FALSE;
 	reqdeltapitch = PitchIntercept - (SWord) pitch;
	Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
	if (reqdeltapitch_pos < ANGLES_FifthDeg)
	{
 		pitch = PitchIntercept;
		retval=TRUE;
	}else
	{
		deltapitch = classtype->maxpitchrate * Timer_Code.FRAMETIME/ 100;//DAW 31Jul96
		if (deltapitch > reqdeltapitch_pos)
		{
 			pitch = PitchIntercept;
			retval=TRUE;
		}else
		{
			if (reqdeltapitch_sign==Math_Lib.POSITIVE)			//JIM 05May96
			{
 				pitch = pitch + (Angles) deltapitch;
			}else
			{
 				pitch = pitch - (Angles) deltapitch;
			}
		}
	}
	if (Status.size==AirStrucSize)
	{
		AirStrucPtr This = (AirStrucPtr) *this;
		if((This != Persons2::PlayerSeenAC) && (This != Persons2::PlayerGhostAC))
			This->fly.elevator = -MAXELEVATOR * reqdeltapitch/ANGLES_20Deg;
	}
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoCalcPitch
//Author		R. Hyde 
//Date			Thu 6 Jun 1996
//
//Description	THe aoa calc is only good for camels###
//				Something need to be done here as in FC in order to correct the	//fix this !!!!
//				drawing of aircraft at high angles of attack 
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool  AirStruc::AutoCalcPitch()
{
	Bool	retval;
	UWord	d1,d2,vel_in_10mph;

	pitch = fly.cpitch;
	retval = formationitem::AutoCalcPitch();
//DEADCODE JIM 13/06/99 	vel_in_10mph = vel/44;
//DEADCODE JIM 13/06/99 	d1 =	vel_to_aoa[vel_in_10mph];		
//DEADCODE JIM 13/06/99 	d2 =	vel_to_aoa[vel_in_10mph+1];
//DEADCODE JIM 13/06/99 	if ((Angles)d1 > classtype->deckangle)
//DEADCODE JIM 13/06/99 	{
//DEADCODE JIM 13/06/99 		d1 = Angles(classtype->deckangle);
//DEADCODE JIM 13/06/99 	}
//DEADCODE JIM 13/06/99 	if ((Angles)d2 > classtype->deckangle)
//DEADCODE JIM 13/06/99 	{
//DEADCODE JIM 13/06/99 		d2 = Angles(classtype->deckangle);
//DEADCODE JIM 13/06/99 	}
//DEADCODE JIM 13/06/99 //	fly.aoa = (Angles) ((UWord) (d1+ (d2-d1) * (vel - vel_in_10mph * 45)/45)); 


	fly.cpitch = pitch;
//	pitch = pitch + fly.aoa;
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcXYZVel
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void mobileitem::CalcXYZVel ()

{
		SWord	sin_theta,cos_theta;
		SWord	sin_hdg, cos_hdg;

		Math_Lib.high_sin_cos (pitch,sin_theta,cos_theta);

		vely = (SWord) ( (vel * sin_theta) / ANGLES_FRACT);

		velhori = (SWord) ((vel * cos_theta)/ ANGLES_FRACT);


		Math_Lib.high_sin_cos (hdg, sin_hdg, cos_hdg);
		velx = (SWord)  velhori * sin_hdg / ANGLES_FRACT;
		velz = (SWord)  velhori * cos_hdg / ANGLES_FRACT;


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcXYZVel
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::CalcXYZVel ()

{
	ANGLES tmppitch,tmpcpitch;

	tmppitch = pitch;
	tmpcpitch = fly.cpitch;

	pitch = fly.cpitch;
	mobileitem::CalcXYZVel ();

	pitch      = tmppitch ;
	fly.cpitch = tmpcpitch;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReachedDesPos
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord AirStruc::ReachedDesPos ()

{
	SLong	desrange;

	if (desposrange ==0)
	{	//trial and error shows 2.5 * distance travelled in frame is about right
		//vel*time=10*dist, so want v*t/4
		//put in /3 'cos frametime is 3 so optimised out????
		if (Range>METRES500)		return (FALSE);
		desrange = velhori * Timer_Code.FRAMETIME/ 3;			//DAW 31Jul96
	}else
		desrange = desposrange;
	if (desrange > Range)
		return(TRUE);
	else
		return(FALSE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewPosition
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	delta = vel*0.3
//				to handle rounding, I have brought in fs = 0..1 over 1200ms
//				if delta should be 1.3, 
//				then for 800ms it will be 1 and	for 400 ms it will be 2
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void mobileitem::NewPosition ()

{
//DeadCode RDH 28Oct96 
//DeadCode RDH 28Oct96 TAKE MINE!!!! IGNORE ANDREW'S!!!!!
//DeadCode RDH 28Oct96 
//DeadCode RDH 28Oct96 	SLong	deltax,deltay,deltaz,fs=(Timer_Code.realtime<<1)&127;
//DeadCode RDH 28Oct96 
																//RDH 28Oct96
	SLong	deltax,deltay,deltaz,								//RDH 28Oct96
		fs=(timerseed<<1)&127;					//RDH 28Oct96		  //DAW 28/03/99
																//RDH 28Oct96

	if (_DPlay.Implemented)										//AMM 16Feb99
		fs=0;													//AMM 16Feb99

//velocity in 10cm/s units, and time in cs -> 10/100 ->/10
						//3*128/10=38.4=38
	deltax =  (velx * (Timer_Code.FRAMETIME*128/10)+fs)>>7;					//DAW 31Jul96
	deltay =  (vely * (Timer_Code.FRAMETIME*128/10)+fs)>>7;					//DAW 31Jul96
	deltaz =  (velz * (Timer_Code.FRAMETIME*128/10)+fs)>>7;					//DAW 31Jul96

	CalcNewPos (deltax,deltay,deltaz);

//TempCode PD 14Oct96 	SLong groundlevel = Land_Scape.GetGroundLevel(*this);
//TempCode PD 14Oct96 	if (World.Y < groundlevel)
//TempCode PD 14Oct96 		World.Y = groundlevel;


//DeadCode RDH 15Jul96 	uniqueID.changed = TRUE;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewPosition
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::NewPosition ()
{
	SLong	deltax,deltay,deltaz;
	ANGLES	grndpitch,grndroll;
	Collide::Pos	landed;
	int fs=(timerseed<<10)&65535;	//timerseed 0..254=2.5sec <<8 is min shift. <<16 = no effect

	if (_DPlay.Implemented)										//AMM 28Apr99
		fs=0;													//AMM 28Apr99

//velocity in 10cm/s units, and time in cs -> 10/100 ->/10
	deltax =  (velx * (Timer_Code.FRAMETIME*65536/10)+fs)>>16;					//DAW 31Jul96
	deltay =  (vely * (Timer_Code.FRAMETIME*65536/10)+fs)>>16;					//DAW 31Jul96
	deltaz =  (velz * (Timer_Code.FRAMETIME*65536/10)+fs)>>16;					//DAW 31Jul96
			  

//DeadCode JIM 29Oct96 	groundlevel = Land_Scape.GetGroundLevel(*this);
//#pragma warnmsg("Paul: need test for accel")
//DEADCODE DAW 28/03/99 	if	(Timer_Code.accel == FALSE)								//RDH 22Nov96
//DeadCode DAW 30Jun99 	if (!currworld->vp || !currworld->vp->Accel())
//DeadCode DAW 30Jun99 	{
//DeadCode DAW 30Jun99 		fly.groundlevel = _Collide.LowestSafeAlt(this,					//JIM 29Oct96
//DeadCode DAW 30Jun99 											pitch,				//JIM 29Oct96
//DeadCode DAW 30Jun99 											roll);				//JIM 29Oct96
//DeadCode DAW 30Jun99 	}else
//DeadCode DAW 30Jun99 	{
//DeadCode DAW 30Jun99 		fly.groundlevel = 0;										//RDH 22Nov96
//DeadCode DAW 30Jun99 	}
	CalcNewPosWithWind (deltax,deltay,deltaz,0);				//RJS 29Jun99
//#pragma warnmsg("Paul: need test for accel")
//DEADCODE DAW 28/03/99 	if	(Timer_Code.accel == FALSE)								//RDH 22Nov96
	if (!currworld->vp || !currworld->vp->Accel())
	{
		landed = _Collide.HaveWeLanded(*this,grndpitch,grndroll);//RJS 14Jan98
		//QUICK CLUDGE COS THINGS ARE SCREWED
//DeadCode DAW 30Jun99 		grndroll=ANGLES_0Deg;
//DeadCode DAW 30Jun99 		grndpitch=ANGLES_0Deg;
	
		if((movecode != AUTO_TAKEOFF) && (movecode != AUTO_LANDING))	//CSB 21/05/99	
			if((landed != _Collide.NOTTOUCHED)
				&&	(	(this == Manual_Pilot.ControlledAC2)		//AMM 01Jun98
					 || !_DPlay.Implemented)	)					//AMM 01Jun98
			{
				if	((landed ==  _Collide.LANDED_OK)
	//DeadCode CSB 21/05/99					 &&	(vel < MPH80)									//JIM 30Oct96
					)
		
				{
		//DeadCode RJS 03Oct96  			World.Y = groundlevel;							
	 				AutoToGrndPitchRoll(grndroll,grndpitch);			//RJS 03Oct96
				}else
				{
	//New or deleted???????
					World.Y = fly.pModel->GroundHeight;					//RJS 29Jun99
					roll = grndroll;
					pitch = grndpitch;

					Trans_Obj.LandedEffect(*this,landed);
					if (this == Manual_Pilot.ControlledAC2)
					{
						GR_Quit3DNow=CRASHED_DEAD;					//RJS 13Nov96
					}
				}													//RDH 14Apr99
			}														//RDH 14Apr99
	}															//RDH 14Apr99
}

void AirStruc::RemoveFuelLeakage(weap_info weapinfo, SWord Xpos, UWord NFrames)
{
	if (weapinfo.int_fuel_leakage > 0)
	{
		int leakage = Timer_Code.FRAMETIME * weapinfo.int_fuel_leakage * NFrames;
		if (leakage < weapinfo.int_fuel)
		{
			weapinfo.int_fuel -= leakage;
//DeadCode CSB 18/06/99				fly.pModel->RemoveMass(leakage * 0.001, Xpos, 0, 0);
		}
		else
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) Anim;

			weapinfo.int_fuel_leakage = 0;
			if (weapinfo.int_launcher > -1)
				adptr->weaponlaunchers[weapinfo.int_launcher].pitch = 0;
		}
	}	
	if (weapinfo.ext_fuel_leakage > 0)
	{
		int leakage = Timer_Code.FRAMETIME * weapinfo.ext_fuel_leakage * NFrames;
		if (leakage < weapinfo.ext_fuel)
		{
			weapinfo.ext_fuel -= leakage;
//DeadCode CSB 18/06/99				if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
//DeadCode CSB 18/06/99					fly.pModel->RemoveMass(leakage * 0.001, Xpos, 0, 0);
		}
		else
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) Anim;

			weapinfo.ext_fuel_leakage = 0;
			if (weapinfo.ext_launcher > -1)
				adptr->weaponlaunchers[weapinfo.ext_launcher].pitch = 0;
		}
	}	
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FuelLeft
//Author		R. Hyde 
//Date			Mon 3 Jun 1996
//
//Description	Assume that internal fuel is only on centre station
//				Calculates the amount of fuel used by the aircraft over the last N frames
//				for aircraft using the simple movecode.
//				
//				The mass of fuel used per frame is calculated in cg as an integer.
//				This is subtracted from Robs weapons data.  The same amount of 
//				fuel (an integer number of cg) is subtracted from the aircraft 
//				total mass (FP) in 0.01 kg.  Therefore, rounding errors should
//				not cause the integer and FP values to get out of step.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::FuelLeft (FP FuelRate)	//[0, 1] per engine
{	//ONLY CALLED EVERY 128 FRAMES (256cs)!!!

//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */	if((this == Persons2::PlayerGhostAC) || (this == Persons2::PlayerSeenAC))
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */	{
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar( 0, 10, "Left %.0f "  , FP(weap.left.drag));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar(30, 10, "Centre %.0f ", FP(weap.centre.drag));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar(60, 10, "Right %.0f " , FP(weap.right.drag));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar( 0, 12, "Left %.0f "  , FP(weap.left.mass * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar(30, 12, "Centre %.0f ", FP(weap.centre.mass * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar(60, 12, "Right %.0f " , FP(weap.right.mass * 0.00001));
//DeadCode CSB 25/06/99	
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar( 0, 15, "Left %.0f "  , FP(weap.left.int_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar(30, 15, "Centre %.0f ", FP(weap.centre.int_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar(60, 15, "Right %.0f " , FP(weap.right.int_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar( 0, 16, "Left %.0f "  , FP(weap.left.ext_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar(30, 16, "Centre %.0f ", FP(weap.centre.ext_fuel * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 24/06/99 */		PrintVar(60, 16, "Right %.0f " , FP(weap.right.ext_fuel * 0.00001));
//DeadCode CSB 25/06/99	
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */		PrintVar( 0, 5, "Vel   %.1f ", FP(vel * 0.1));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */		InterceptandRange(ai.homebase);
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */		PrintVar( 0, 7, "Range %.2f ", FP(Range * 0.00001));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */		PrintVar(20, 5, "FuelRate %.3f ", FuelRate);
//DeadCode CSB 25/06/99	
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */		static Float DistTravelled;
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */		DistTravelled += FP(vel) * 0.256;
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */		PrintVar( 0, 8, "Dist %.2f ", FP(DistTravelled / 1000));
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */		FP usage = (FuelRate * Timer_Code.FRAMETIME * FRAMESPERCALC * classtype->fuelaboff);//cg,cs
//DeadCode CSB 25/06/99										FP kmpkg = FP(vel) * 0.000256 / (usage * 0.00001);
//DeadCode CSB 25/06/99										PrintVar(40, 5, "km/kg %.5f ", kmpkg);
//DeadCode CSB 25/06/99	/* TEST CODE CSB 25/06/99 */	}

	
//DeadCode CSB 15/09/98		int usage;
//DeadCode CSB 15/09/98		FP FuelRate;
//DeadCode CSB 15/09/98		
//DeadCode CSB 15/09/98		if(fly.pModel->EngineList->Type == ET_JET)
//DeadCode CSB 15/09/98		{
//DeadCode CSB 15/09/98			FuelRate = (fly.pModel->EngineList->Thrust * fly.pModel->EngineList->Thrust) 
//DeadCode CSB 15/09/98			           / (fly.pModel->EngineList->p0 * fly.pModel->EngineList->p0);
//DeadCode CSB 15/09/98		}
//DeadCode CSB 15/09/98			else
//DeadCode CSB 15/09/98		{	
//DeadCode CSB 15/09/98			FuelRate = (fly.pModel->EngineList->Power * fly.pModel->EngineList->Power) 
//DeadCode CSB 15/09/98			           / (fly.pModel->EngineList->p0 * fly.pModel->EngineList->p0);
//DeadCode CSB 15/09/98		}
//DeadCode CSB 15/09/98	
//DeadCode CSB 15/09/98		if(FuelRate < 0.05) FuelRate = 0.05;

	int usage = (FuelRate * Timer_Code.FRAMETIME * FRAMESPERCALC * classtype->fuelaboff);//cg,cs
	SWord Xpos = 0;
//DeadCode CSB 18/06/99		if(fly.pModel->MainPlaneList != NULL)
//DeadCode CSB 18/06/99			Xpos = fly.pModel->MainPlaneList->Pos[0][1].x;

	if (weap.UseIntFuel)
	{
		SLong OldTotInt = weap.left.int_fuel + weap.centre.int_fuel + weap.right.int_fuel;
		weap_info *TankToUse = &weap.left;

		if(weap.centre.int_fuel_leakage > TankToUse->int_fuel_leakage) 
			TankToUse = &weap.centre;

		if(weap.right.int_fuel_leakage > TankToUse->int_fuel_leakage) 
			TankToUse = &weap.right;

		if(TankToUse->int_fuel_leakage == 0)
		{
			TankToUse = &weap.left;
		
			if(weap.right.int_fuel > TankToUse->int_fuel) 
				TankToUse = &weap.right;

			if(TankToUse->int_fuel == 0)
				TankToUse = &weap.centre;
		}

		TankToUse->int_fuel -= usage;
		if(TankToUse->int_fuel < 0)
			TankToUse->int_fuel = 0;

		SLong TotInt = weap.left.int_fuel + weap.centre.int_fuel + weap.right.int_fuel;
		if(TotInt <= 0)
		{
			fly.thrustpercent = 0;
			if((this == Persons2::PlayerGhostAC) || (this == Persons2::PlayerSeenAC))
				OverLay.CancelAccel();
			else
				if(movecode != AUTO_LANDING)
				{
					movecode = AUTO_DEATHSEQUENCE;
					Status.deadtime = 1;
					if(OldTotInt != 0)
					{
						AirStrucPtr buddy = FindABuddyWithPlayerGivenPriority();
						if((buddy) && (PlayerInGroup()))
						{
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HURTFUEL, MSG_BINGOFUEL, this, NULL, buddy));
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERKILLED_OPT_4, MSG_DAMAGELEVEL2, this, NULL, buddy));
						}
						SLong DistHome = Distance3D(&ai.homebase->World);
						if(DistHome < 10 * (World.Y - ai.homebase->World.Y))
						{
							movecode = AUTO_LANDING;
							ai.ManStep = 0;
						}
					}
				}
		}
	}
	else
	{
		weap_info *TankToUse = &weap.left;
		
		if(weap.right.ext_fuel > TankToUse->ext_fuel) 
			TankToUse = &weap.right;

		if(TankToUse->ext_fuel == 0)
			TankToUse = &weap.centre;

		TankToUse->ext_fuel -= usage;
		if(TankToUse->ext_fuel < 0)
			TankToUse->ext_fuel = 0;

		if((weap.left.ext_fuel == 0) && (weap.centre.ext_fuel == 0) && (weap.right.ext_fuel == 0))
		{
			weap.UseIntFuel = TRUE;
//DeadCode CSB 02/07/99				if((this != Persons2::PlayerGhostAC) || ((currworld->vp) && (currworld->vp->Accel())))
//DeadCode CSB 02/07/99				{
//DeadCode CSB 02/07/99					WorldStuff*	worldptr = mobileitem::currworld;
//DeadCode CSB 02/07/99					Trans_Obj.DumpFuel(this,*worldptr);
//DeadCode CSB 02/07/99				}
		}
	}

//leakage
	UWord NumFrames = EVERY256cs + 1;

	RemoveFuelLeakage(weap.right,  Xpos, NumFrames);
	RemoveFuelLeakage(weap.centre, 0,     NumFrames);
	RemoveFuelLeakage(weap.left,  -Xpos, NumFrames);




//	fly.mainfuel -= Timer_Code.FRAMETIME* classtype->fuelaboff;	//DAW 31Jul96
//	if (fly.mainfuel < 0)
//	{
//		if (this == Manual_Pilot.ControlledAC2)
//			_Miles.SequenceAudible(FIL_MUSIC_GOING_BADLY);
//		fly.mainfuel = 0;
//		fly.thrustpercent = 0;
//	}
//	//fuel is in mg and needs to be converted to N
//	fly.weight = 	(SWord) classtype->weightempty
//									+ fly.mainfuel/100000;
//	if (	(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])	//RDH 21Mar97
//		&&	(Save_Data.gamedifficulty [GD_LIMITEDARM])
//		)
//		fly.weight +=  fly.storesweight;
//

//	if ((timerseed &0x3E)==(uniqueID.count&0x3E))
	{
		int	avail,safety;
		if (waypoint && FuelShort(0,&avail,&safety)	&& waypoint->wpname<WPNAME_Regroup)
		{
			int	factor=99;
			if (safety)
				factor=MULDIVUNS(100,avail,safety);
			if ((factor&1) && factor<75)
				ChainBingoMessage(true);
			else
			if (factor==99)
			{
				if (AcIsGroupLeader())
					if (AcIsPlayer())
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BINGOFUEL, MSG_BINGOFUEL, this, this, this));
					else
					{
						AiLeaderBingoInstructions();
					}
				else				
				{
					AirStrucPtr glead=FindGroupLeader();
					ChainBingoMessage(false);
					if (!glead->AcIsPlayer())
						glead->AiLeaderBingoInstructions();
				}
			}
		}
	}
}

void	AirStruc::ChainBingoMessage(bool atbingohurting)
{
	AirStrucPtr recipient=NULL;
	switch (position())
	{
	case 0:
		if (formpos)
			recipient=fly.leadflight;
	break;
	case 3:															  //JIM 28/05/99
	case 1:
		recipient=Leader();
	break;
	case 2:															  //RJS 5/28/99
		recipient=fly.leadelt();
	break;
	}
	if (!atbingohurting)
	{
		if (recipient && weap.reportedbingo)
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_IMATBINGOFUEL, MSG_BINGOFUEL, this, this, recipient));
			recipient->ChainBingoMessage(atbingohurting);
		}
		weap.reportedbingo=TRUE;
	}
	else
	{
		if (recipient && weap.reportedbingohurting)
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HURTFUEL, MSG_BINGOFUEL, this, NULL, recipient));
			recipient->ChainBingoMessage(atbingohurting);
		}
		weap.reportedbingohurting=TRUE;
	}
}
void	AirStruc::AiLeaderBingoInstructions()
{
	if (	ai.unfriendly 
		&&	ai.unfriendly->Status.size==AIRSTRUCSIZE 
		&&	AirStrucPtr(*ai.unfriendly)->movecode==AUTO_FAC)
	{
		AirStrucPtr fac=*ai.unfriendly;

		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ADVISEFACBINGO, MSG_ADVISEFACBINGO, this, NULL, fac));
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ADVISEFACFINISHEDREPLY, MSG_STATUSREPORT_REPLY_DELAY, fac, this, this));
	}
	AirStrucPtr buddy=PlayerInGroup();
	if (!buddy)
		buddy=FindBuddy();
	if (buddy)
//TEMPCODE JIM 04/04/99 		if (GroupInCombat())
//TEMPCODE JIM 04/04/99 			Art_Int.SendMsgAndCall(MESSAGE_STRUC(SCRIPT_WEATBINGOFUEL_DISENG, MSG_STATUSREQUEST, this, NULL, buddy), AllDisengage);
//TEMPCODE JIM 04/04/99 		else
		Art_Int.SendMsgAndCall(MESSAGE_STRUC(SCRIPT_WEATBINGOFUEL, MSG_STATUSREQUEST, this, NULL, buddy), Rendezvous);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFlightParams
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	CSB - The frame counter for each aircraft aircraft is incremented and the amount
//				of fuel used and the atmospheric conditions are calculated every N frames
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
extern int	 Count_SetFlightParams;
void AirStruc::SetFlightParams (bool dotimestuff)
{
//DEADCODE DAW 14/06/99 #ifndef	NDEBUG
//DEADCODE DAW 14/06/99 	if (dotimestuff)
//DEADCODE DAW 14/06/99 		if (Count_SetFlightParams++!=0)
//DEADCODE DAW 14/06/99 			INT3;
//DEADCODE DAW 14/06/99 #endif

//DeadCode CSB 15/09/98		if	(Timer_Code.accel == FALSE)								//RDH 22Nov96
//DeadCode CSB 15/09/98		{
	if (dotimestuff)
	{
		ULong targetrpm = classtype->minrpm + ((classtype->maxrpm - classtype->minrpm) * fly.thrustpercent) / 100;
		if(targetrpm > fly.rpm)
		{
			fly.rpm += 10 * Timer_Code.FRAMETIME;
			if(fly.rpm > targetrpm) fly.rpm = targetrpm;
		}
		if(targetrpm < fly.rpm)
		{
			fly.rpm -= 10 * Timer_Code.FRAMETIME;
			if(fly.rpm < targetrpm) fly.rpm = targetrpm;
		}

		AircraftAnimData* adptr = (AircraftAnimData*)Anim;
		if(adptr) adptr->acrpm = fly.rpm;
//DeadCode CSB 05/05/99			fly.pModel->Animations(*this);

		if(!(fly.pModel->FrameCount & EVERY256cs))	//This will do the following commands for each aircraft
		{											//once every n operations.
//			if (!_Replay.Record && !_Replay.Playback)
			{
				MMC.Sky.Ambient (World.Y, 
			 				 	fly.pModel->AmbDensity,
							 	fly.pModel->AmbTemp,
								 fly.pModel->AmbPres);
			}
			//(FP)vel / (10 * FSqrt(1.403 * 287 * fly.pModel->AmbTemp) );
			//0.9 * fly.pModel->AmbDensity / 0.0001225 * (1 + 0.45 * Mach);

//DeadCode CSB 24/06/99				if((classtype->visible == B26) || (classtype->visible == B29))
			if(classtype->aerobaticfactor == AEROBATIC_LOW)
				fly.thrustpercent = 100;
			else
			{
//DeadCode CSB 27/06/99					FP P45Mach			 = (FP)vel * FSqrt ( ( (0.45*0.45)/((10.0*10.0)*(1.403*287.0)) ) / fly.pModel->AmbTemp ); //JIM 15/04/99
//DeadCode CSB 27/06/99					FP FuelUsageRate = (fly.pModel->AmbDensity *(0.9/ 0.0001225)) * (1.0 + P45Mach);// to calculate the fuel rate for a simple flight model
				FP FuelUsageRate = fly.pModel->AmbDensity / 0.0001225;// to calculate the fuel rate for a simple flight model

				SLong LocalMaxVelSL = CalcMaxVelSL();
				if(movecode != AUTO_COMBAT)
				{
					SLong tp = 100;
					if(pitch < ANGLES_2_5Deg)
						tp = (100 * vel * vel) / (LocalMaxVelSL * LocalMaxVelSL);
					MODMAXMIN(tp, 0, 100);
					fly.thrustpercent = tp;
				}
				FuelUsageRate *= fly.thrustpercent * 0.01;
				FuelUsageRate *= 1.2;
				FuelLeft(FuelUsageRate);
			}//Old_Code DAW 22Nov98 			FP FuelUsageRate = fly.thrustpercent * 0.01;
		}
		fly.pModel->FrameCount++;
	}
//DeadCode CSB 15/09/98			FuelLeft();
//DeadCode CSB 15/09/98			SetControlSurfaces();
//DeadCode CSB 15/09/98			SetRpm ();
//DeadCode CSB 15/09/98	//		SetInstruments ();
//DeadCode CSB 15/09/98			fly.vel_cms = vel * 10;
//DeadCode CSB 15/09/98	//rdh		fly.vel_mms = fly.vel_cms  * 10;
//DeadCode CSB 15/09/98	//		fly.rotr_xbl = 0;								//RDH 22Jul96
//DeadCode CSB 15/09/98	//		fly.rotr_ybl = 0;								//RDH 22Jul96
//DeadCode CSB 15/09/98	//		fly.rotr_zbl = 0;								//RDH 22Jul96
//DeadCode CSB 15/09/98	//		fly.acroll = roll;											//RDH 22Jul96
//DeadCode CSB 15/09/98	//		fly.croll = roll;											//RDH 22Jul96
//DeadCode CSB 15/09/98	//		hdg = hdg;												//RDH 22Jul96
//DeadCode CSB 15/09/98		}
}	
//done in usermsg
//DEADCODE RDH 30/04/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE RDH 30/04/99 //Procedure		SetWaypointForEveryBody
//DEADCODE RDH 30/04/99 //Author		R. Hyde 
//DEADCODE RDH 30/04/99 //Date			Tue 24 Sep 1996
//DEADCODE RDH 30/04/99 //
//DEADCODE RDH 30/04/99 //Description	
//DEADCODE RDH 30/04/99 //
//DEADCODE RDH 30/04/99 //Inputs		
//DEADCODE RDH 30/04/99 //
//DEADCODE RDH 30/04/99 //Returns	
//DEADCODE RDH 30/04/99 //
//DEADCODE RDH 30/04/99 //------------------------------------------------------------------------------
//DEADCODE RDH 30/04/99 void AirStruc::SetWaypointForEveryBody(AirStrucPtr ac,WayPointPtr	wp)
//DEADCODE RDH 30/04/99 {
//DEADCODE RDH 30/04/99 	if (ac)
//DEADCODE RDH 30/04/99 		while (ac)
//DEADCODE RDH 30/04/99 		{
//DEADCODE RDH 30/04/99 			AirStrucPtr fol=ac;
//DEADCODE RDH 30/04/99 			while (fol)
//DEADCODE RDH 30/04/99 			{
//DEADCODE RDH 30/04/99 				fol->waypoint=wp;
//DEADCODE RDH 30/04/99 				fol=*fol->follower;
//DEADCODE RDH 30/04/99 			}
//DEADCODE RDH 30/04/99 			ac=ac->fly.nextflight;
//DEADCODE RDH 30/04/99 		}
//DEADCODE RDH 30/04/99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LeaderBreakOff
//Author		Jim Taylor
//Date			Wed 23 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::LeaderBreakOff ()
{
//	done in usermsg.cpp
//DEADCODE RDH 16/05/99 	AirStrucPtr fighterleader;
//DEADCODE RDH 16/05/99 	if (formpos == 0)
//DEADCODE RDH 16/05/99 	{
//DEADCODE RDH 16/05/99 		fighterleader = this;
//DEADCODE RDH 16/05/99 	}else
//DEADCODE RDH 16/05/99 	{
//DEADCODE RDH 16/05/99 		fighterleader = fly.leadflight;
//DEADCODE RDH 16/05/99 	}
//DEADCODE RDH 16/05/99 	if (fighterleader->movecode==AUTO_COMBAT)
//DEADCODE RDH 16/05/99 	{
//DEADCODE RDH 16/05/99 //		_Miles.SequenceAudible(FIL_MUSIC_PLAYER_RUNS);
//DEADCODE RDH 16/05/99 		fighterleader->ai.manoeuvre=MANOEUVRE_TOPCOVER;
//DEADCODE RDH 16/05/99 		if (	fighterleader->ai.unfriendly
//DEADCODE RDH 16/05/99 			&&	fighterleader->ai.unfriendly->Status.size==AIRSTRUCSIZE
//DEADCODE RDH 16/05/99 			&&	((AirStrucPtr)fighterleader->ai.unfriendly)->ai.attacker==fighterleader
//DEADCODE RDH 16/05/99 			)
//DEADCODE RDH 16/05/99 			((AirStrucPtr)fighterleader->ai.unfriendly)->ai.attacker=NULL;
//DEADCODE RDH 16/05/99 		fighterleader->ai.unfriendly=NULL;
//DEADCODE RDH 16/05/99 	}
//DEADCODE RDH 16/05/99 	else
//DEADCODE RDH 16/05/99 	if (fighterleader->movecode==AUTO_PRECOMBAT)
//DEADCODE RDH 16/05/99 	{
//DEADCODE RDH 16/05/99 		Art_Int.AllBreakOff(this);									//JIM 16Jul96
//DEADCODE RDH 16/05/99 	}


}

//done in usermsg
//DEADCODE RDH 30/04/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE RDH 30/04/99 //Procedure		SendEveryOneHome
//DEADCODE RDH 30/04/99 //Author		R. Hyde 										//JIM 23Oct96
//DEADCODE RDH 30/04/99 //Date			Tue 24 Sep 1996
//DEADCODE RDH 30/04/99 //
//DEADCODE RDH 30/04/99 //Description	
//DEADCODE RDH 30/04/99 //
//DEADCODE RDH 30/04/99 //Inputs		
//DEADCODE RDH 30/04/99 //
//DEADCODE RDH 30/04/99 //Returns	
//DEADCODE RDH 30/04/99 //
//DEADCODE RDH 30/04/99 //------------------------------------------------------------------------------
//DEADCODE RDH 30/04/99 void AirStruc::SendEveryOneHome ()
//DEADCODE RDH 30/04/99 {
//DEADCODE RDH 30/04/99 
//DEADCODE RDH 30/04/99 //TEMP	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_LEADERGOINGHOME,NULL);//JIM 05Dec96
//DEADCODE RDH 30/04/99 	AirStrucPtr fighterleader,bomberleader;
//DEADCODE RDH 30/04/99 	WayPointPtr	lastwaypoint;
//DEADCODE RDH 30/04/99 
//DEADCODE RDH 30/04/99 	if (formpos == 0)
//DEADCODE RDH 30/04/99 	{
//DEADCODE RDH 30/04/99 		fighterleader = this;
//DEADCODE RDH 30/04/99 	}else
//DEADCODE RDH 30/04/99 	{
//DEADCODE RDH 30/04/99 		fighterleader = fly.leadflight;
//DEADCODE RDH 30/04/99 	}
//DEADCODE RDH 30/04/99 	{
//DEADCODE RDH 30/04/99 		//fighters go home
//DEADCODE RDH 30/04/99 		//Deadcode does 'fighters break patrol
//DEADCODE RDH 30/04/99 		lastwaypoint = fighterleader->waypoint;
//DEADCODE RDH 30/04/99 
//DEADCODE RDH 30/04/99 		while (		lastwaypoint->action!=wpalandingno
//DEADCODE RDH 30/04/99 				&&	(lastwaypoint->next != NULL)
//DEADCODE RDH 30/04/99 //DeadCode JIM 04Nov96 				&&	lastwaypoint->action!=wpinitlandno
//DEADCODE RDH 30/04/99 //DeadCode JIM 23Oct96 				&&	lastwaypoint->action!=wpstoploopchkno
//DEADCODE RDH 30/04/99 //DeadCode JIM 23Oct96 				&&	lastwaypoint->action!=wpstoploopchkno
//DEADCODE RDH 30/04/99 				)
//DEADCODE RDH 30/04/99 				lastwaypoint = lastwaypoint->next;
//DEADCODE RDH 30/04/99 		if (lastwaypoint->action==wpstoploopchkno)
//DEADCODE RDH 30/04/99 			lastwaypoint = lastwaypoint->next;
//DEADCODE RDH 30/04/99 
//DEADCODE RDH 30/04/99 		SetWaypointForEveryBody(fighterleader,lastwaypoint);
//DEADCODE RDH 30/04/99 //DeadCode JIM 11Oct96 		if (ai.attacker!=NULL)
//DEADCODE RDH 30/04/99 //DeadCode JIM 11Oct96 		_Miles.SequenceAudible(FIL_MUSIC_PLAYER_RUNS);
//DEADCODE RDH 30/04/99 
//DEADCODE RDH 30/04/99 		if (fighterleader->fly.leadflight != NULL)
//DEADCODE RDH 30/04/99 		{//bombers go home
//DEADCODE RDH 30/04/99 			SetWaypointForEveryBody(fighterleader->fly.leadflight,lastwaypoint);
//DEADCODE RDH 30/04/99 		}
//DEADCODE RDH 30/04/99 	}
//DEADCODE RDH 30/04/99 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetManualFlightParams
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SetManualFlightParams ()

{
	SetControlSurfaces();
	SetRpm ();
//	SetInstruments ();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetManoeuvreTime
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	Sets the timer counter. This timer is used for various things
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void formationitem::SetManoeuvreTime (UWord	time)
{
 manoeuvretime=time;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TimeLeft
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord formationitem::TimeLeft ()

{
	SLong tmp=manoeuvretime-Timer_Code.FRAMETIME;				//DAW 31Jul96
	if (tmp <0)
	{
		manoeuvretime = 0;
		return (FALSE);
	}else
	{
		manoeuvretime =tmp; 					//PD 15Mar96
		return (manoeuvretime);
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RequiredDRoll
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description			a roll is chosen from a table for the required delta hdg	
//						the delta roll is then calculated	 
//						
//						
//						
//Inputs				reqdeltahdg
//
//Returns				deltaroll
//
//------------------------------------------------------------------------------
SWord AirStruc::RequiredDRoll (SWord reqdeltahdg)

{
	SWord	reqroll;

	reqroll = FindRequiredRoll (reqdeltahdg, RequiredBankData);

	//fix this !!!! to limit the angle of roll so that it can be assumed that 
	//				the speed is not affected by the roll angle		//CSB 29/09/98
	return (RequiredDRollSub(reqroll));							//RDH 11Oct96
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RequiredDRollSub
//Author		R. Hyde 
//Date			Fri 11 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord AirStruc::RequiredDRollSub (SWord reqroll)
{
	SWord	deltaroll,reqdeltaroll;
	UWord	reqdeltaroll_pos;
	SWord	reqdeltaroll_sign;

	reqdeltaroll = (SWord) ((Angles)reqroll - roll);
	Math_Lib.Pos (reqdeltaroll,reqdeltaroll_pos,reqdeltaroll_sign);

//DeadCode RDH 27Oct96 //rollrateaccel  65536 means 360 deg/s/s
//DeadCode RDH 27Oct96 	fly.rollrate	+=  classtype->rollrateaccel * Timer_Code.FRAMETIME/ 100;//DAW 31Jul96
//DeadCode RDH 27Oct96 	if (fly.rollrate > classtype->maxrollrate)

//gradual move to max may be required							//RDH 27Oct96
//	fly.rollrate = (Angles)classtype->maxrollrate;

//	deltaroll = fly.rollrate * Timer_Code.FRAMETIME/100;		//DAW 31Jul96

	deltaroll = (Angles)classtype->maxrollrate * Timer_Code.FRAMETIME/100;		//rdh

	if (deltaroll > reqdeltaroll_pos)
			deltaroll = reqdeltaroll_pos;

	if (reqdeltaroll_sign == MathLib::NEGATIVE)
	{
		deltaroll = -deltaroll;
	}


	return (deltaroll);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindRequiredRoll
//Author		R. Hyde 
//Date			Fri 15 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord AirStruc::FindRequiredRoll (SWord reqdeltahdg, RequiredBankDataElement* rolldata)

{

	UWord	reqdeltahdg_pos;
	SWord	reqdeltahdg_sign;
	SWord	reqrolllower,reqrollupper;
	SWord	reqhdglower,reqhdgupper;
	SWord	reqroll;

//	RequiredBankDataElement*	rolldata;
//	rolldata = RequiredBankData;

	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

	if (reqdeltahdg_pos == ANGLES_180Deg)
	{
		reqroll = MAXROLL;
	}else
	{
		reqrollupper = 0;
		reqhdgupper = 0;
		reqrolllower = reqrollupper;
		reqhdglower = reqhdgupper;
		while (rolldata->hdg < (Angles)reqdeltahdg_pos)
		{
			reqrolllower = reqrollupper;
			reqhdglower = reqhdgupper;
			rolldata++;
//DeadCode RDH 22Aug96 			reqrollupper = rolldata->roll;
			if (rolldata->roll >> (ANGLES_30Deg))
			{
				if (ai.flyingskill > SKILL_REGULAR)
				{
					reqrollupper = ANGLES(MAXCOMBATROLL) - ANGLES_8Deg + (Angles)(ai.flyingskill * ANGLES_2Deg/SKILL_STAGE);//RDH 19Aug96
				}else
				{
					reqrollupper = ANGLES(ANGLES_60Deg) + (Angles)(ai.flyingskill * ANGLES_10Deg/SKILL_STAGE);//RDH 19Aug96
				}
			}
			else
				reqrollupper = (ANGLES)rolldata->roll;
			reqhdgupper = (ANGLES)rolldata->hdg; 
		}
		if (reqhdgupper - reqhdglower == 0)
		{
			reqroll = reqrolllower;
		}else
		{
			reqroll = reqrolllower + (reqrollupper - reqrolllower)
					* (reqdeltahdg_pos - reqhdglower) / (reqhdgupper - reqhdglower);
		}
//DeadCode CSB 05/07/99			if (	(	(AircraftDamaged())
//DeadCode CSB 05/07/99					||	(classtype->aerobaticfactor==AEROBATIC_LOW)
//DeadCode CSB 05/07/99					)
//DeadCode CSB 05/07/99				&&	(reqroll > ANGLES_30Deg)
//DeadCode CSB 05/07/99				)
//DeadCode CSB 05/07/99				reqroll = ANGLES_30Deg;

		if( ((classtype->visible == B29) || (classtype->visible == B26))	//CSB 05/07/99	
			&& (reqroll > ANGLES_45Deg) )									//CSB 05/07/99
				reqroll = ANGLES_45Deg;											//CSB 05/07/99	
	}
	if	(reqdeltahdg_sign == MathLib::POSITIVE)
	{
		reqroll = -reqroll;
	}
	return (reqroll);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcNewPos
//Author		R. Hyde 
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MovingItem::CalcNewPos(SLong deltax,SLong deltay,SLong deltaz)

{


	World.X += deltax;
  	World.Y += deltay;
	World.Z += deltaz;										//RDH 18Dec95
//DeadCode RDH 30Nov95 	if (World.Y <= GROUNDLEVEL)
//DeadCode RDH 30Nov95 	{
//DeadCode RDH 30Nov95 		World.Y = GROUNDLEVEL;
//DeadCode RDH 30Nov95 	}
	uniqueID.changed = TRUE;									//RDH 15Jul96

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcNewPos
//Author		R. Hyde 
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::CalcNewPosWithWind(SLong deltax,SLong deltay,SLong deltaz,SLong groundlevel)

{

//DeadCode CSB 08/06/99		SWord	sinv_hdg,cosv_hdg;
//DeadCode CSB 08/06/99		SWord	sind_hdg,cosd_hdg;
//DeadCode CSB 08/06/99		ANGLES	dhdg;
//DeadCode CSB 08/06/99		SLong	horivel;

//	if (Save_Data.flightdifficulty [FD_WINDEFFECTS] && !Timer_Code.accel)
//	{
//rdh change to MA wind
//		if (World.Y > groundlevel)
//		{
////DeadCode RDH 24Oct96 			deltax +=  Save_Data.wind.velx	* TimerCode::FIXEDFRAMETIME /10;
////DeadCode RDH 24Oct96 			deltaz +=  Save_Data.wind.velz	* TimerCode::FIXEDFRAMETIME /10;
//			deltax +=  MMC.wind.velx	* TimerCode::FIXEDFRAMETIME /10;
//			deltaz +=  MMC.wind.velz	* TimerCode::FIXEDFRAMETIME /10;
//		}else
//		{
//DeadCode RDH 24Oct96 			dhdg = hdg - Save_Data.wind.direction+ ANGLES_180Deg;
//			dhdg = hdg - MMC.wind.direction+ ANGLES_180Deg;
//			Math_Lib.high_sin_cos (dhdg, sind_hdg, cosd_hdg);
////DeadCode RDH 24Oct96 			horivel =  Save_Data.wind.speed * cosd_hdg / ANGLES_FRACT;
//			horivel =  MMC.wind.speed * cosd_hdg / ANGLES_FRACT;
//			horivel+= velhori;
//			if ((horivel < 0) ||  (velhori ==0))
//			{
//				deltax = 0;
//				deltaz = 0;
//			}else
//			{
//				Math_Lib.high_sin_cos (hdg, sinv_hdg, cosv_hdg);
//				deltax =  (horivel * sinv_hdg / ANGLES_FRACT);
//				deltax = deltax * TimerCode::FIXEDFRAMETIME /10;
//				deltaz =  (horivel * cosv_hdg / ANGLES_FRACT);
//				deltaz = deltaz * TimerCode::FIXEDFRAMETIME /10;
//			}
//
//		}
//
//	}

//DeadCode CSB 08/06/99		if (Save_Data.flightdifficulty [FD_WINDEFFECTS])// && !Timer_Code.accel)
//DeadCode CSB 08/06/99		{
//DeadCode CSB 08/06/99			SLong wx, wy, wz;
//DeadCode CSB 08/06/99			MMC.Sky.GetWind(World.Y, wx, wy, wz);
//DeadCode CSB 08/06/99			if(World.Y < groundlevel + 10000)
//DeadCode CSB 08/06/99			{
//DeadCode CSB 08/06/99				wx = (wx * (World.Y - groundlevel)) / 10000;
//DeadCode CSB 08/06/99				wy = (wy * (World.Y - groundlevel)) / 10000;
//DeadCode CSB 08/06/99				wz = (wz * (World.Y - groundlevel)) / 10000;
//DeadCode CSB 08/06/99			}
//DeadCode CSB 08/06/99			deltax += (wx * Timer_Code.FRAMETIME) / 10;
//DeadCode CSB 08/06/99			deltay += (wy * Timer_Code.FRAMETIME) / 10;
//DeadCode CSB 08/06/99			deltaz += (wz * Timer_Code.FRAMETIME) / 10;
//DeadCode CSB 08/06/99		}
	
	//CSB 10/06/99	
	SLong wx, wy, wz;	
	MMC.Sky.GetWind(World.Y, wx, wy, wz);

	deltax += (wx * Timer_Code.FRAMETIME) / 10;
	deltay += (wy * Timer_Code.FRAMETIME) / 10;
	deltaz += (wz * Timer_Code.FRAMETIME) / 10;

//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */	SLong MaxDelta = 0;
//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */	if(deltax > MaxDelta)	MaxDelta = deltax;
//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */	if(-deltax > MaxDelta)	MaxDelta = -deltax;
//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */	if(deltay > MaxDelta)	MaxDelta = deltay;
//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */	if(-deltay > MaxDelta)	MaxDelta = -deltay;
//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */	if(deltaz > MaxDelta)	MaxDelta = deltaz;
//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */	if(-deltaz > MaxDelta)	MaxDelta = -deltaz;
//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */
//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */	if(MaxDelta > 1000)
//DeadCode DAW 30Jun99 /* TEST CODE CSB 18/06/99 */		int BreakPoint = 0;
	   
	MovingItem::CalcNewPos(deltax, deltay, deltaz);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInstruments
//Author		R. Hyde 
//Date			Tue 25 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void	AirStruc::SetInstruments ()
//{
//	UWord		d1,d2,altitude_1000m,densityratio;
//	SLong		altitude_cm;
//
//	
//	altitude_cm = World.Y;
//	if (altitude_cm < 0)
//		altitude_cm = 0;
//	if (altitude_cm >MAXALTITUDE_CM)
//		altitude_cm = MAXALTITUDE_CM;
//
//	altitude_1000m =	(UWord) (altitude_cm/100000);
//
//	
//	d1 =	airdensityratiosquareroot[altitude_1000m];
//	d2 =	airdensityratiosquareroot[altitude_1000m+1];
//	densityratio = (UWord) (d1+ (d2-d1) * (altitude_cm - altitude_1000m*100000)/100000); 
////DeadCode ARM 27Aug97 	fly.i_a_s = (SWord) ((SLong) vel * densityratio /WORD_FRACT);
////DeadCode ARM 27Aug97 	fly.i_a_s = (SWord)(fly.pModel->IndicatedAirSpeed * 10);	//ARM 26Aug97
//
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetControlSurfaces
//Author		R. Hyde 
//Date			Mon 25 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SetControlSurfaces ()
{
	UWord	elevator_pos;
	SWord	elevator_sign;
	SWord	deltaelevator;
	UWord	aileron_pos;
	SWord	aileron_sign;
	SWord	deltaaileron;
//	UWord	rudder_pos;
//	SWord	rudder_sign;
	SWord	deltarudder;

SLong const ELEVATORSTEPSIZE = MAXELEVATOR/8; 
//Copy to animation data structure							//PD 19Apr96

	AircraftAnimData *adptr = (AircraftAnimData *)Anim;			//PD 19Apr96
	if (adptr)													//PD 19Apr96
	{
//DeadCode ARM 16Jul97 		adptr->acelevator = fly.elevator >> 8;					//RJS 13Jun97
//DeadCode ARM 16Jul97 		adptr->acaileronl = fly.aileron >> 8;					//RJS 13Jun97
//DeadCode ARM 16Jul97 		adptr->acaileronr = fly.aileron >> 8;					//RJS 13Jun97
//DeadCode ARM 16Jul97 		adptr->acrudder = fly.rudder >> 8;						//RJS 13Jun97



//DeadCode RJS 13Jun97 //DeadCode RDH 23Jul96 	if (fly.elevator != 0)
//DeadCode RJS 13Jun97 //DeadCode RDH 23Jul96 	{
//DeadCode RJS 13Jun97 	deltaelevator = fly.elevator - adptr->acelevator;
//DeadCode RJS 13Jun97 	if (deltaelevator != 0)
//DeadCode RJS 13Jun97 	{
//DeadCode RJS 13Jun97 		Math_Lib.Pos (deltaelevator,elevator_pos,elevator_sign);
//DeadCode RJS 13Jun97 		if (elevator_pos > ELEVATORSTEPSIZE)
//DeadCode RJS 13Jun97 		{
//DeadCode RJS 13Jun97 			if (elevator_sign == MathLib::POSITIVE)
//DeadCode RJS 13Jun97 			{
//DeadCode RJS 13Jun97 			adptr->acelevator += ELEVATORSTEPSIZE;
//DeadCode RJS 13Jun97 			}else
//DeadCode RJS 13Jun97 			{
//DeadCode RJS 13Jun97 			adptr->acelevator -= ELEVATORSTEPSIZE;
//DeadCode RJS 13Jun97 			}
//DeadCode RJS 13Jun97 		}else
//DeadCode RJS 13Jun97 		{
//DeadCode RJS 13Jun97 			adptr->acelevator = fly.elevator;
//DeadCode RJS 13Jun97 		}
//DeadCode RJS 13Jun97 	}
//DeadCode RJS 13Jun97 	deltaaileron = fly.aileron - adptr->acaileronl;				//RJS 13Mar97
//DeadCode RJS 13Jun97 //DeadCode RDH 23Jul96 	if (fly.aileron != 0)
//DeadCode RJS 13Jun97 //DeadCode RDH 23Jul96 	{
//DeadCode RJS 13Jun97 	if (deltaaileron != 0)
//DeadCode RJS 13Jun97 	{
//DeadCode RJS 13Jun97 		Math_Lib.Pos (deltaaileron,aileron_pos,aileron_sign);
//DeadCode RJS 13Jun97 		if (aileron_pos > MAXAILERON/8)
//DeadCode RJS 13Jun97 		{
//DeadCode RJS 13Jun97 			if (aileron_sign == MathLib::POSITIVE)
//DeadCode RJS 13Jun97 			{
//DeadCode RJS 13Jun97 			adptr->acaileronl += MAXAILERON/8;					//RJS 13Mar97
//DeadCode RJS 13Jun97 			}else
//DeadCode RJS 13Jun97 			{
//DeadCode RJS 13Jun97 			adptr->acaileronl -= MAXAILERON/8;					//RJS 13Mar97
//DeadCode RJS 13Jun97 			}
//DeadCode RJS 13Jun97 		}else
//DeadCode RJS 13Jun97 		{
//DeadCode RJS 13Jun97 			adptr->acaileronl = fly.aileron;					//RJS 13Mar97
//DeadCode RJS 13Jun97 		}
//DeadCode RJS 13Jun97 	}
//DeadCode RJS 13Jun97 //DeadCode RDH 23Jul96 	if (fly.rudder != 0)
//DeadCode RJS 13Jun97 //DeadCode RDH 23Jul96 	{
//DeadCode RJS 13Jun97 	deltarudder = fly.rudder - adptr->acrudder;
//DeadCode RJS 13Jun97 	if (deltarudder != 0)
//DeadCode RJS 13Jun97 	{
//DeadCode RJS 13Jun97 		Math_Lib.Pos (deltarudder,rudder_pos,rudder_sign);
//DeadCode RJS 13Jun97 		if (rudder_pos > MAXRUDDER/8)
//DeadCode RJS 13Jun97 		{
//DeadCode RJS 13Jun97 			if (rudder_sign == MathLib::POSITIVE)
//DeadCode RJS 13Jun97 			{
//DeadCode RJS 13Jun97 			adptr->acrudder += MAXRUDDER/8;
//DeadCode RJS 13Jun97 			}else
//DeadCode RJS 13Jun97 			{
//DeadCode RJS 13Jun97 			adptr->acrudder -= MAXRUDDER/8;
//DeadCode RJS 13Jun97 			}
//DeadCode RJS 13Jun97 		}else
//DeadCode RJS 13Jun97 		{
//DeadCode RJS 13Jun97 			adptr->acrudder = fly.rudder;
//DeadCode RJS 13Jun97 		}
//DeadCode RJS 13Jun97 	}
//DeadCode RJS 13Jun97 	if  (	(fly.rudder == 0) && (adptr->acaileronl != 0)		//RJS 13Mar97
//DeadCode RJS 13Jun97 		)
//DeadCode RJS 13Jun97 	{
//DeadCode RJS 13Jun97 			adptr->acrudder = (MAXRUDDER * adptr->acaileronl)/(2 * MAXAILERON);//RJS 13Mar97
//DeadCode RJS 13Jun97 	}

//DeadCode RDH 02Jul96 	//Copy to animation data structure							//PD 19Apr96
//DeadCode RDH 02Jul96 
//DeadCode RDH 02Jul96 	AircraftAnimData *adptr = (AircraftAnimData *)Anim;			//PD 19Apr96
//DeadCode RDH 02Jul96 
//DeadCode RDH 02Jul96 	if (adptr)													//PD 19Apr96
//DeadCode RDH 02Jul96 	{
//DeadCode RDH 02Jul96 		adptr->anim_aileron = fly.anim_aileron;
//DeadCode RDH 02Jul96 		adptr->anim_elevator = fly.anim_elevator;
//DeadCode RDH 02Jul96 		adptr->anim_rudder = fly.anim_rudder;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetRpm
//Author		R. Hyde 
//Date			Mon 22 Apr 1996
//
//Description		  produce an rpm as a function of thrust ^ 2
//							
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SetRpm ()
//RDH 24May96 modified
{
//DeadCode RDH 24May96 	SLong	rpm;
//DeadCode RDH 24May96 
//DeadCode RDH 24May96 	rpm = (classtype->maxrpm - classtype->minrpm) *  fly.thrustpercent /100;
//DeadCode RDH 24May96 	rpm = classtype->minrpm +
//DeadCode RDH 24May96 				rpm * rpm / (classtype->maxrpm - classtype->minrpm);
//DeadCode RDH 24May96 
//DeadCode RDH 24May96 
//DeadCode RDH 24May96 	fly.rpm = rpm;
//DeadCode RDH 24May96 

//rpm calc

	SLong	reqrpm;

	if (fly.thrustpercent <2)
	{
		if (vel > 90)
		{
			reqrpm = classtype->freerpm;
		}else
		{
			reqrpm = 0;
		}
	}else
	{
		reqrpm = fly.thrustpercent * (classtype->maxrpm - classtype->minrpm)/100;
		reqrpm = classtype->minrpm + reqrpm * reqrpm /
				(classtype->maxrpm - classtype->minrpm);
		reqrpm = reqrpm
				-  (SWord) pitch *  (classtype->maxdiverpm - classtype->maxrpm)
				/	(ANGLES_60Deg);
	}
	//effect of pitch
//DeadCode RDH 14Aug96 	if (reqrpm > classtype->minrpm)
//DeadCode RDH 14Aug96 	{
//DeadCode RDH 16Aug96 		reqrpm = reqrpm
//DeadCode RDH 16Aug96 				-  (SWord) pitch *  (classtype->maxdiverpm - classtype->maxrpm)
//DeadCode RDH 16Aug96 				/	(ANGLES_60Deg);
//DeadCode RDH 14Aug96 		if (reqrpm < classtype->minrpm)
//DeadCode RDH 14Aug96 				reqrpm = classtype->minrpm;	

//DeadCode RDH 14Aug96 	}
	if (fly.rpm > reqrpm)
	{
		fly.rpm -= Timer_Code.FRAMETIME;						//DAW 31Jul96
	}else
	{
//DeadCode RJS 10Dec96 		if (	(reqrpm > ((classtype->maxrpm + classtype->minrpm)/2))//RDH 05Dec96
//DeadCode RJS 10Dec96 			&&	(fly.rpm < ((classtype->maxrpm + classtype->minrpm)/2))//RDH 05Dec96
//DeadCode RJS 10Dec96 			)													//RDH 05Dec96
//DeadCode RJS 10Dec96 		{														//RDH 05Dec96
//DeadCode RJS 10Dec96 			fly.rpm = 	(classtype->maxrpm + classtype->minrpm)/2;//RDH 05Dec96
																//RDH 05Dec96
//DeadCode RJS 10Dec96 		}else
//DeadCode RJS 10Dec96 		{
			fly.rpm += Timer_Code.FRAMETIME;						//DAW 31Jul96
//DeadCode RJS 10Dec96 		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//RJS 28Aug98
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsHealthyMovecode
//Author		Dave Whiteside
//Date			Fri 28 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::IsHealthyMovecode(ULong&	themovecode)
{
	Bool	retval = FALSE;
	themovecode = 0xFFFFFFFF;

	if (Status.size >= MOBILESIZE)
	{
//DeadCode AMM 28Apr99 		if (!_Replay.Playback)									//RJS 29Oct98
		if (!_Replay.Playback || this!=Persons2::PlayerSeenAC)	//AMM 28Apr99
		{
			themovecode = movecode;
			if (	(movecode != AUTO_NOPPILOT)
				&&	(movecode != AUTO_HITWATER)
				&&	(movecode != AUTO_CRASHROLL)
				&&	(movecode != AUTO_CRASHSKID)
				&&	(movecode != AUTO_SPIRAL2GROUND)				//DAW 03Sep98
				&&	(movecode != AUTO_DEATHSEQUENCE)	)
				retval = TRUE;
		}
		else
		{
			themovecode = _Replay.ReplayDeathMode;
			if (themovecode == RDEATH_NULL)
				retval = TRUE;
		}														//RJS 29Oct98
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetWeaponForce
//Author		Robert Slater
//Date			Wed 16 Sep 1998
//
//Description	
//
//Inputs		  100000cg = 1kg
//					10m/sec
//					csec
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SetWeaponForce(SLong	mass, SLong	velocity, SLong	delay)
{
	if (mass)
	{
		SLong	force = (mass*velocity)/delay;

		force /= 10000;	//CSB 08/01/99

		weap.weapforce = -force;
	}
	else
		weap.weapforce = 0;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcBestClimbSpeed
//Author		Craig Beeston
//Date			Mon 28 Sep 1998
//
//Description	Given an altitude the best climb velocity is calculated for that aircraft
//
//Inputs		Alt
//
//Returns		Vel
//
//------------------------------------------------------------------------------
SLong AirStruc::CalcBestClimbSpeed()
{
	Bool	retval = FALSE;
	
	SLong Height = World.Y;

	if(Height < 0)       Height = 0;
	if(Height > 2000000) Height = 2000000;
	
	SWord h = Height * 0.00001;	//cm -> km
	SWord v1, v2;
	v1 = classtype->bestclimbspeed[h];
	v2 = classtype->bestclimbspeed[h+1];
	SLong ClimbVel = v1 + (Height - 100000 * h) / 100000 * (v2 - v1);

	SLong StoresDrag = weap.left.drag + weap.centre.drag + weap.right.drag;
	
//DeadCode CSB 28/05/99		ClimbVel = (ClimbVel * (10000 - StoresDrag)) / 10000;
//DeadCode CSB 28/05/99		ClimbVel -= StoresDrag / 100;
	ClimbVel = (ClimbVel * 98) / 100;

	return(ClimbVel);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcBestClimbPitch
//Author		Craig Beeston
//Date			Mon 28 Sep 1998
//
//Description	Given an altitude the best climb Pitch is calculated for that aircraft
//
//Inputs		Alt
//
//Returns		pitch
//
//------------------------------------------------------------------------------
SWord AirStruc::CalcBestClimbPitch()
{
	SLong Height = World.Y;

	if(Height < 0)       Height = 0;
	if(Height > 2000000) Height = 2000000;
	
	SWord h = Height * 0.00001;	//cm -> km
	SWord p1, p2;
	p1 = classtype->bestclimbang[h];
	p2 = classtype->bestclimbang[h+1];
	SWord ClimbPitch = p1 + (Height - 100000 * h) * (p2 - p1) / 100000;

	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
	{
		SLong StoresDrag = weap.left.drag + weap.centre.drag + weap.right.drag;

		ClimbPitch =  (ClimbPitch * (9000 - StoresDrag)) / 9000;
		ClimbPitch -= StoresDrag / 10;
	}

	ClimbPitch = (ClimbPitch * 90) / 100;	

	if(ClimbPitch > ANGLES_0Deg)
		return(ClimbPitch);
	else
		return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcMaxVelDive
//Author		Craig Beeston
//Date			Mon 28 Sep 1998
//
//Description	Given an altitude the Maximum Speed in a vertical dive is calculated for that aircraft
//
//Inputs		Alt
//
//Returns		Speed
//
//------------------------------------------------------------------------------
SLong AirStruc::CalcMaxVelDive()
{
	SLong Height = World.Y;

	if(Height < 0) Height = 0;
	if(Height > 2000000) Height = 2000000;

	SLong MaxVelDive;

	if(Height < 1100000)
		MaxVelDive = classtype->maxveldive_0km + Height * 
					(classtype->maxveldive_11km - classtype->maxveldive_0km) / 1100000;
	else
		MaxVelDive = classtype->maxveldive_11km + (Height - 1100000) *
					(classtype->maxveldive_20km - classtype->maxveldive_11km) / 900000;
	
	return(MaxVelDive);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcMaxVelSL
//Author		Craig Beeston
//Date			Mon 28 Sep 1998
//
//Description	Given an altitude the Maximum Straight and Level Speed is calculated for that aircraft
//
//Inputs		Alt
//
//Returns		Speed
//
//------------------------------------------------------------------------------
SLong AirStruc::CalcMaxVelSL()
{
	SLong Height = World.Y;

	if(Height < 0) Height = 0;
	if(Height > 2000000) Height = 2000000;

	SLong MaxVelSL;

	if(Height < 1100000)
		MaxVelSL = classtype->maxvelsl_0km + Height * 
					(classtype->maxvelsl_11km - classtype->maxvelsl_0km) / 1100000;
	else
		MaxVelSL = classtype->maxvelsl_11km + (Height - 1100000) *
					(classtype->maxvelsl_20km - classtype->maxvelsl_11km) / 900000;
	

	//Effect of stores drag
	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
	{
		SLong StoresDrag = weap.left.drag + weap.centre.drag + weap.right.drag;
	
		if(StoresDrag)
		{
			if((classtype->visible == F51) || (classtype->visible == YAK9))
			{
				FP VelFraction = 1.0 - FP(StoresDrag) * 0.00006;
				FP fMaxVel	   = FP(MaxVelSL) * VelFraction;
				MaxVelSL = fMaxVel;
			}
			else
			{
				SLong DeltaVel	 = (175 * StoresDrag) / 1000;
				if(DeltaVel > 0)
 				MaxVelSL -= DeltaVel;
			}
		}
	}


	return(MaxVelSL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVelAlt
//Author		Craig Beeston 
//Date			Tue 29 Sep 1998
//
//Description	Calculates the velocity for AutoFollowWP depending on the altitude of the AC
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::CalcVelAlt ()

{
	SLong	reqvel=0;
	if (waypoint && waypoint->vel)
	 	reqvel =  waypoint->vel;
	return CalcVelAlt (reqvel);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVelAlt
//Author		Craig Beeston 
//Date			Tue 29 Sep 1998
//
//Description	Calculates the velocity for AutoFollowWP depending on the altitude of the AC
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::CalcVelAlt (SLong reqvel)
{
	SWord LocalMaxVelSL = CalcMaxVelSL();
	SWord MaxVel = LocalMaxVelSL;

	if (!reqvel)
		reqvel = LocalMaxVelSL * 0.95;//fix this to represent a cruise velocity

	if((SWord)pitch == 0) 
		MaxVel = LocalMaxVelSL;
	else
	if (((SWord)pitch) > ANGLES_0Deg)
	{
		SWord LocalBestClimbSpeed = CalcBestClimbSpeed();
		SWord LocalBestClimbPitch = CalcBestClimbPitch();

		FP PitchRatio;
		if(LocalBestClimbPitch > 0)
		{
			PitchRatio =  (SWord)pitch;
			PitchRatio /= LocalBestClimbPitch;
			PitchRatio *= PitchRatio;
			if(PitchRatio > 1.0) PitchRatio = 1.0;
			MaxVel = LocalMaxVelSL + PitchRatio * (LocalBestClimbSpeed - LocalMaxVelSL);
		}
		else MaxVel = LocalBestClimbSpeed;
	}
	else
	{
		SWord LocalMaxVelDive = CalcMaxVelDive();

		SWord LocalPitch = -SWord(pitch);		//0 for SL, -16384 for straight down
		SWord p = LocalPitch / 2048;			//11.25 deg sections
		if(p < 0) p = 0;
		if(p > 7) p = 7;

		SWord q = classtype->divevelfactor[p] + (LocalPitch - p * 2048) * 
					(classtype->divevelfactor[p+1] - classtype->divevelfactor[p]) / 2048;

		MaxVel = LocalMaxVelSL + q * (LocalMaxVelDive - LocalMaxVelSL) / 1000;
	}
	if (slowdownleader)											//JIM 17Sep96 //JIM 01/02/99
		if (formpos&InWingMAX)										  //JIM 01/02/99
			MaxVel -= 150;	//10mph	25;		//5mph								//JIM 17Sep96 //JIM 01/02/99
		else														  //JIM 01/02/99
			MaxVel -= 250;	//15mph	25;		//5mph								//JIM 17Sep96 //JIM 01/02/99
	
		
//DeadCode CSB 28/05/99		//Effect of stores drag
//DeadCode CSB 28/05/99		SLong StoresDrag = weap.left.drag + weap.centre.drag + weap.right.drag;
//DeadCode CSB 28/05/99		if(StoresDrag)
//DeadCode CSB 28/05/99		{
//DeadCode CSB 28/05/99			if((classtype->visible == F51) || (classtype->visible == YAK9))
//DeadCode CSB 28/05/99			{
//DeadCode CSB 28/05/99				FP VelFraction = 1.0 - FP(StoresDrag) * 0.00006;
//DeadCode CSB 28/05/99				FP fMaxVel	   = FP(MaxVel) * VelFraction;
//DeadCode CSB 28/05/99				MaxVel = fMaxVel;
//DeadCode CSB 28/05/99			}
//DeadCode CSB 28/05/99			else
//DeadCode CSB 28/05/99			{
//DeadCode CSB 28/05/99				SLong DeltaVel	 = ((SWord)pitch + 4600) * (StoresDrag * 10) / (50 * 4600);
//DeadCode CSB 28/05/99				if(DeltaVel > 0)
//DeadCode CSB 28/05/99	 			MaxVel -= DeltaVel;
//DeadCode CSB 28/05/99			}
//DeadCode CSB 28/05/99		}

	if (reqvel > MaxVel)
	 	reqvel = MaxVel;

	if (reqvel < classtype->minvel)
	 	reqvel = classtype->minvel;


	SWord oldvel = vel;
	SWord accel  = CalcAccel(reqvel);
	AddAccel2Vel(accel);
	slowdownleader = FALSE;										//JIM 17Sep96
	if( (reqvel - vel) * (reqvel - oldvel) <= 0)
	{
		vel = reqvel;
		return(TRUE);
	}
	else return(FALSE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcAccel
//Author		Craig Beeston 
//Date			Tue 2 Feb 1999
//
//Description	Calculates the maximum possible accel or deccel of an AC at current alt and speed
//				Only really right for straight and level flight	
//
//Inputs		Requested velocity
//
//Returns		Possible Acceleration/Decelleration (in dodgy unit (256 = 10 cm/s2) )
//
//------------------------------------------------------------------------------
SWord AirStruc::CalcAccel(SWord reqvel)
{
	SWord retval = 0;	
	if(reqvel < 0) return 0;

	SWord maxvel = CalcMaxVelSL();

	FP reldens = 1 - (FP)World.Y / 3250000;
	reldens = reldens * reldens * reldens;

	FP maxaccel 	= classtype->maxaccel;
	FP weightempty	= classtype->weightempty; 
	FP totalmass = weap.left.int_fuel + weap.centre.int_fuel + weap.right.int_fuel;
	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
		totalmass +=   weap.left.mass     + weap.centre.mass     + weap.right.mass
					 + weap.left.ext_fuel + weap.centre.ext_fuel + weap.right.ext_fuel;

	totalmass = weightempty + totalmass * 0.001;

	
	maxaccel = maxaccel * weightempty / totalmass;

	if(reqvel >= vel)
	{
		FP accel =	(FP)vel / (FP)maxvel;
		if((classtype->visible == F51) || (classtype->visible == YAK9))
			accel =	1 - accel * accel * accel;
		else
			accel =	1 - accel * accel;
		accel *= maxaccel;

		if((pitch != 0) && (vel))
		{
//DeadCode CSB 28/05/99				SWord SinPitch, CosPitch;
//DeadCode CSB 28/05/99				Math_Lib.high_sin_cos(pitch, SinPitch, CosPitch);
//DeadCode CSB 28/05/99	
//DeadCode CSB 28/05/99				accel -= 25105 * SinPitch / 32768;	//Gravity in Dodgy units
			accel -= (25105.0 * vely) / vel;	//Gravity in Dodgy units
		}

		if (slowdownleader)						
		{
			if (formpos&InWingMAX)										  
				accel *= 0.75;
			else			
				accel *= 0.5;
		}
		MODLIMIT(accel, 32767);
		
		if(accel > 0)
			retval = (SWord)accel;
		else
			retval = 0;

	}
	else
	{
		FP deccel = (FP)vel / (FP)maxvel;
//DeadCode CSB 30/06/99			if((classtype->visible == F51) || (classtype->visible == YAK9))
//DeadCode CSB 30/06/99				deccel = deccel * deccel * deccel * maxaccel;
//DeadCode CSB 30/06/99			else
			deccel = deccel * deccel * maxaccel;
		
		if(pitch != 0)
		{
//DeadCode CSB 28/05/99				SWord SinPitch, CosPitch;
//DeadCode CSB 28/05/99				Math_Lib.high_sin_cos(pitch, SinPitch, CosPitch);
//DeadCode CSB 28/05/99	
//DeadCode CSB 28/05/99				deccel +=  25105 * SinPitch / 32768;	//Gravity in Dodgy units
			deccel += (25105.0 * vely) / vel;	//Gravity in Dodgy units
		}
		MODLIMIT(deccel, 32767);

		if(deccel > 0)
			retval = -(SWord)deccel;
		else
			retval = 0;
	}


	retval *= reldens;
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAccel2Vel
//Author		Craig Beeston 
//Date			Fri 12 Feb 1999
//
//Description	Adds a given acceleration to the AC velocity using the clock
//
//Inputs		Acceleration (in dodgy units (256 = 10 m/s2) )
//
//Returns		
//
//------------------------------------------------------------------------------
void AirStruc::AddAccel2Vel(SWord Accel)
{
	FP AbsAccel = Accel;
	if(AbsAccel < 0) AbsAccel *= -1;
//DeadCode CSB 08/07/99		int timer = (timerseed & 0x3f);
	int timer1 = timeofday & 0x01ff;	//5.12 secs
	int timer2 = timeofday & 0x001f;	//0.32 secs

	FP ftimer1 = timer1;
	FP ftimer2 = timer2;
	FP delta_t = Timer_Code.FRAMETIME;

	FP DeltaVel = (ftimer2 + delta_t * ftimer1 / 512.0) / 32.0; 
	DeltaVel += delta_t * (FP)AbsAccel / 25600.0;

	if(Accel > 0)
		vel += int(DeltaVel);
	else	
		vel -= int(DeltaVel);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcHdgRollLimited
//Author		(R. Hyde) Craig Beeston
//Date			(Tue 28 Nov 1995) Tue 29 Sep 1998
//
//Description	
//		 TR in deg per sec  = 360.g.tan RollAngle/(2.Pi.v)
//in Rowan units of 360 deg = 65536, v in 10cm/s units tan 45 = 256 not 1
//		 TR in cs			= 65536.98. tan roll/ 2.Pi.v.100.256 
//							=  40 tan roll /v	
//
//				This does the same as CalcHdgRoll but will limit the angle of roll so that
//				the speed can be calculated based assuming no roll
//			
//				At present this will only be called by AutoFollowWp
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::CalcHdgRollLimited ()
{
	return CalcHdgRoll();
	SWord	reqdeltahdg;

	if (Save_Data.flightdifficulty [FD_WINDEFFECTS])
				WindCorrection();
	reqdeltahdg = 	(SWord) (hdg - HdgIntercept);
	return	 CalcHdgRollLimited(reqdeltahdg);
}

Bool AirStruc::CalcHdgRollLimited (SWord reqdeltahdg)
{
	return CalcHdgRoll(reqdeltahdg);

	SWord	deltaroll,currroll,tanroll;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltahdg_sign;
	SLong	deltahdg;
	UWord	deltahdg_pos;
	SWord	deltahdg_sign;
	Bool	retval=FALSE;
	Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode CSB 31/03/99		if ((Angles)reqdeltahdg_pos <(ANGLES)ANGLES_ThirdDeg)				//RDH 03Dec96
	if ((Angles)reqdeltahdg_pos <(ANGLES)ANGLES_ThirdDeg)					//CSB 31/03/99	
	{
		retval=RollLevel (reqdeltahdg);
	}else
	{
		SWord	reqroll;

		reqroll = FindRequiredRoll (reqdeltahdg, RequiredBankData);
//DeadCode CSB 06/04/99	PrintVar(0, 12, "WayPoint ReqRoll %.1f ", (FP)(reqroll / 182.04));	//CSB 23/03/99	

	//fix this !!!! to limit the angle of roll so that it can be assumed that 
	//				the speed is not affected by the roll angle		//CSB 29/09/98
		if((SWord)pitch > 0)
		{
			SWord RollLimit;
			
			FP n1 = 1 - 0.7857 * World.Y / classtype->abs_ceiling;
			FP BestPitch = CalcBestClimbPitch();
			FP n2 = (SWord)pitch / BestPitch;
			n2 *= n2;
			n2 = 1 - 0.5 * n2;
			RollLimit = 12743 * n1 * n2;
			if(RollLimit < 1365) RollLimit = 1365;	//7.5 deg	at ceiling

			SWord reqroll_sign;
			UWord reqroll_pos;
			Math_Lib.Pos (reqroll, reqroll_pos, reqroll_sign);
		
			if(reqroll_pos > RollLimit)
			{
				if(reqroll_sign == -1) reqroll = -RollLimit;
				if(reqroll_sign ==  1) reqroll =  RollLimit;
			}
		}

		deltaroll = RequiredDRollSub(reqroll);							//RDH 11Oct96

		roll	 += (Angles) deltaroll;
		deltahdg = CalcHdg();
		Math_Lib.Pos ((SWord) deltahdg, deltahdg_pos,deltahdg_sign);
		if (deltahdg_pos <reqdeltahdg_pos)
		{
			hdg =  hdg + (Angles) deltahdg; 
		}else
		{
			retval=RollLevel (reqdeltahdg);
		}
	}
	if((this != Persons2::PlayerSeenAC) && (this != Persons2::PlayerGhostAC))
		fly.aileron = -MAXAILERON * reqdeltahdg/ANGLES_20Deg;
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMaccaVels
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SetMaccaVels()
{
	FPMATRIX	mat;
	SWord		tmphdg = -hdg;
	ANGLES		thePitch = pitch;
	ANGLES		theHdg = (Angles) tmphdg;
	SWord		cosa2,sina2;
	SWord		sin_ang,cos_ang;
	Float		x,y,z;
	Float		mulfrac = 1.0 / 32768.0;
	Float		sina,cosa;
	Float		fvel = Float(vel);

	mat.L11 = 1;	//x.x
	mat.L12	= 0;	//x.y
	mat.L13 = 0;	//x.z
	mat.L21 = 0;	//y.x
	mat.L22 = 1;	//y.y
	mat.L23 = 0;	//y.z
	mat.L31 = 0;	//z.x
	mat.L32 = 0;	//z.y
	mat.L33 = 1;	//z.z

/*	if (thePitch==ANGLES_90Deg)
		thePitch=ANGLES_90BareDeg;
	else
	if (thePitch==ANGLES_270Deg)
		thePitch=ANGLES_270BareDeg;*/

	if (theHdg)
	{
		Math_Lib.high_sin_cos(theHdg,sina2,cosa2);
		sina = sina2;
		cosa = cosa2;

		sina *= mulfrac;
		cosa *= mulfrac;

		x = (mat.L11 * cosa) + (mat.L31 * sina);
		y = (mat.L12 * cosa) + (mat.L32 * sina);
		z = (mat.L13 * cosa) + (mat.L33 * sina);

		mat.L31 = (mat.L31 * cosa) - (mat.L11 * sina);
		mat.L32 = (mat.L32 * cosa) - (mat.L12 * sina);
		mat.L33 = (mat.L33 * cosa) - (mat.L13 * sina);

		mat.L11 = x;
		mat.L12 = y;
		mat.L13 = z;
	}

	Math_Lib.high_sin_cos(thePitch,sin_ang,cos_ang);
	if (thePitch)
	{
		sina = sin_ang;
		cosa = cos_ang;

		sina *= mulfrac;
		cosa *= mulfrac;

		x = (mat.L31 * cosa) + (mat.L21 * sina);
		y = (mat.L32 * cosa) + (mat.L22 * sina);
		z = (mat.L33 * cosa) + (mat.L23 * sina);

		mat.L21 = (mat.L21 * cosa) - (mat.L31 * sina);
		mat.L22 = (mat.L22 * cosa) - (mat.L32 * sina);
		mat.L23 = (mat.L23 * cosa) - (mat.L33 * sina);

		mat.L31 = x;
		mat.L32 = y;
		mat.L33 = z;
	}

	Float	xx = mat.L31;
	Float	yy = mat.L32;
	Float	zz = mat.L33;
	Float	maxpoo;

	maxpoo = xx*xx;
	maxpoo += yy*yy;
	maxpoo += zz*zz;

	double mag = (double) maxpoo;
	_asm
	{
		fld mag;
		fsqrt;
		fstp mag;
	}

	maxpoo = 1.0 / mag;

	xx *= maxpoo;
	yy *= maxpoo;
	zz *= maxpoo;

	xx *= Float(vel);
	yy *= Float(vel);
	zz *= Float(vel);

	// Velocity
	velx = SWord(xx);
	vely = SWord(yy);
	velz = SWord(zz);

	velhori = (vel * cos_ang)>>ANGLES_SHIFT;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckForWeapon
//Author		Robert Slater
//Date			Fri 26 Mar 1999
//
//Description	Check to see if the aircraft is carrying any of the given weapon
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool FormationItem::CheckForWeapon(UByte ltype)//Check for stores...
{
	AircraftAnimData*	adptr = (AircraftAnimData*) Anim;
	WeapAnimData*	weapon;
	int				index;

	for (index=0; index < 8; index++)
	{
		weapon = &adptr->weaponlaunchers[index];
		if (	weapon
			&& ((weapon->LauncherType & LT_MASK) == (ltype & LT_MASK))		  //RJS 01Apr99
			&&	(weapon->LoadedStores > 0))
			return TRUE;
	}

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckForAnyWeapon
//Author		Craig Beeston
//Date			Fri 26 Mar 1999
//
//Description	Check to see if the aircraft is carrying any weapons for ground attack
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::CheckForAnyWeapon()//Check for stores...
{
	AircraftAnimData*	adptr = (AircraftAnimData*) Anim;
	WeapAnimData*	weapon;
	int				index;
	Bool			retval = FALSE;

	for (index=0; index < 8; index++)
	{
		weapon = &adptr->weaponlaunchers[index];
		if ((weapon) && (weapon->LoadedStores > 0))
		{
			switch (weapon->LauncherType & LT_MASK)
			{
			case LT_BULLET:
			case LT_BOMB:
			case LT_ROCKET:
				retval = TRUE;
				break;
			}
		}
	}

	return retval;
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseAWeapon
//Author		Craig Beeston
//Date			Fri 2 Apr 1999
//
//Description	Choose a weapon to use for dive bomb 
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::ChooseAWeapon()
{
	Bool RetVal = FALSE;
	if(CheckForWeapon(LT_BOMB))
	{
		weap.weapontype = LT_BOMB;
		RetVal = TRUE;
	}
	else if(CheckForWeapon(LT_ROCKET))
	{
		weap.weapontype = LT_ROCKET;
		RetVal = TRUE;
	}
	else if(CheckForWeapon(LT_BULLET))
	{
		weap.weapontype = LT_BULLET;
		RetVal = TRUE;
	}
	return(RetVal);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CarryingNapalm
//Author		Craig Beeston
//Date			Thu 29 Apr 1999
//
//Description	Check to see if the aircraft is carrying napalm rather than bombs
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::CarryingNapalm()
{
	AircraftAnimData*	adptr = (AircraftAnimData*) Anim;
	WeapAnimData*	weapon;
	int				index;

	for (index=0; index < 8; index++)
	{
		weapon = &adptr->weaponlaunchers[index];
		if (	weapon
			&& ((weapon->LauncherType & LT_MASK) == (LT_BOMB & LT_MASK))
			&&	(weapon->LoadedStores > 0))
			if(weapon->LauncherType == LT_NAPALM) return TRUE;
	}

	return FALSE;
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectBombTarget
//Author		Craig Beeston
//Date			Sat 3 Apr 1999
//
//Description	Choose a target to bomb depending on duty 
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::SelectBombTarget(Bool NewTarg)
{
	Bool RetVal = FALSE;
	int flightpos = position();
	char localduty = duty & ACTIONSUBCODE;
	switch(localduty)
	{
//*************************************************************************************************
		case DA_WIDE:
		{					//Wide Pattern Low Level Run
			if(!IsLocalLeader())
				return FALSE;
			int ElementNumber;
			ai.unfriendly = SelectTarget(ai.unfriendly, &ElementNumber);
			ai.manoeuvre = (MANOEUVRE)ElementNumber;

			RetVal = TRUE;
//DeadCode CSB 24/05/99				if(!ChooseAWeapon())
//DeadCode CSB 24/05/99					ai.ManStep = 15;
//DeadCode CSB 24/05/99				else
			{
				if(NewTarg)
				{
					ai.ManStep = 1;
					SetManoeuvreTime(1 * SECS100);
					AirStrucPtr callee = FindABuddyWithPlayerGivenPriority();
					if((callee) && (callee->fly.callnum > fly.callnum))
					{
						if(CarryingNapalm())
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_1, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));
						else	
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_0, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));

					}
				}
			}
			break;
		}
//*************************************************************************************************
		case DA_SINGLEFILE:
		{						//Single File Pattern Low Level Run
			AirStrucPtr bomblead = NULL;
			AirStrucPtr grplead = FindGroupLeader();
			Bool Breakout = FALSE;

			for(AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
			{
				for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
				{
					if(foll->ai.ManStep != 15)
					{
						bomblead = foll;
						Breakout = TRUE;
						break;
					}
				}
//DeadCode CSB 30/06/99					if(bomblead == foll) break;
				if(Breakout) break;
			}
//DeadCode CSB 13/07/99				if(bomblead != grplead)
//DeadCode CSB 13/07/99					int breakpoint = 0;

			if(this == bomblead)
			{
				if((!AnyoneInPhaseN(1)) || (!NewTarg))
				{
					int ElementNumber;
					ai.unfriendly = SelectTarget(ai.unfriendly, &ElementNumber);
					ai.manoeuvre = (MANOEUVRE)ElementNumber;

					RetVal = TRUE;
//DeadCode CSB 24/05/99						if(!ChooseAWeapon())
//DeadCode CSB 24/05/99							ai.ManStep = 15;
//DeadCode CSB 24/05/99						else 
					if(NewTarg)
					{
						ai.ManStep = 1;
						SetManoeuvreTime(2 * SECS100);
						ChooseAWeapon();
						
						AirStrucPtr callee = PlayerInGroup();
						if((!callee) && (follower))
							callee = Follower();
							
						if((callee) && (NewTarg) && (callee->fly.callnum > fly.callnum))
						{
							if(weap.weapontype == LT_BOMB)
							{
								if(CarryingNapalm())
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_1, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));
								else
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_0, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));
							}
							else if(weap.weapontype == LT_ROCKET)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_2, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));
							else
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTAPPROACH_L, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));
						}
					}
				}
			}
			else
			{
//CSB				if((bomblead->ai.ManStep == 0) && (bomblead->World.Y > bomblead->waypoint->World.Y - 10000))//- bomblead->ai.unfriendly->World.Y > 240000))
//CSB					break;

				if( ((AnyoneInPhaseN(2)) && (!AnyoneInPhaseN(1))) || (!NewTarg))
//DeadCode CSB 24/05/99						if(!ChooseAWeapon())
//DeadCode CSB 24/05/99							ai.ManStep = 15;
//DeadCode CSB 24/05/99						else
					if(bomblead->ai.unfriendly)
					{
						ai.unfriendly = bomblead->ai.unfriendly;	//CSB 27/05/99	
						ai.manoeuvre = (MANOEUVRE)bomblead->ai.manoeuvre;
						RetVal = TRUE;
//DeadCode DAW 26May99 	ai.manoeuvre = MANOEUVRE(bomblead->ai.manoeuvre);

						int ElementNumber = (int)ai.manoeuvre;
						bool targetlive = SelectedElement(ai.unfriendly, ElementNumber, &despos);
						if(!targetlive)
						{
							ai.unfriendly = SelectTarget(ai.unfriendly, &ElementNumber);
							ai.manoeuvre = (MANOEUVRE)ElementNumber;
						}
						 
						if(NewTarg)
							ai.ManStep = 1;
						SetManoeuvreTime(2 * SECS100);
					}
			}
			break;
		}
//*************************************************************************************************
		case DA_INDIVIDUAL:
		{
			if((!AnyoneInPhaseN(1)) || (!NewTarg))
//DeadCode CSB 24/05/99					if(!ChooseAWeapon())
//DeadCode CSB 24/05/99						ai.ManStep = 15;
//DeadCode CSB 24/05/99					else
				{
					int ElementNumber, ACNumber;
					ACNumber = (int)uniqueID.count - (int)FindLeadUID();

					ai.unfriendly = SelectTarget(ai.unfriendly, &ElementNumber, ACNumber);
					ai.manoeuvre = (MANOEUVRE)ElementNumber;
					RetVal = TRUE;
					if(NewTarg)
					{
						if(NewTarg)
							ai.ManStep = 1;
						SetManoeuvreTime(SECS100 / 2);
					}
				}
			break;
		}
//*************************************************************************************************
		case DA_ELEMENT:
		{
			//Element Pattern Low Level Run
//DeadCode CSB 24/05/99				if(!ChooseAWeapon())
//DeadCode CSB 24/05/99					ai.ManStep = 15;
//DeadCode CSB 24/05/99				else
			if(IsLocalLeader())
			{
				if((!AnyoneInPhaseN(1)) || (!NewTarg))
				{
					int ElementNumber, ACNumber;
					ACNumber = (int)uniqueID.count - (int)FindLeadUID();
					ACNumber /= 2;
					ai.unfriendly = SelectTarget(ai.unfriendly, &ElementNumber, ACNumber);
					ai.manoeuvre = (MANOEUVRE)ElementNumber;
					RetVal = TRUE;
					if(NewTarg)
					{
						ai.ManStep = 1;
						SetManoeuvreTime(SECS100 / 2);
					}

					AirStrucPtr Wingman = Follower();
					if((Wingman) && (Wingman->fly.callnum > fly.callnum))
					{
						if(NewTarg)
						{
							ChooseAWeapon();
							if(weap.weapontype == LT_BOMB)
							{
								if(CarryingNapalm())
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_1, MSG_STARTINGTRGTRUN_RPT, *this, NULL, Wingman));
								else
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_0, MSG_STARTINGTRGTRUN_RPT, *this, NULL, Wingman));
							}
							else if(weap.weapontype == LT_ROCKET)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_2, MSG_STARTINGTRGTRUN_RPT, *this, NULL, Wingman));
							else
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTAPPROACH_L, MSG_STARTINGTRGTRUN_RPT, *this, NULL, Wingman));
						}

						if(Wingman == Persons2::PlayerGhostAC)	// Wingman is player
						{
								
						}
						else
//DeadCode CSB 24/05/99							if(!Wingman->ChooseAWeapon())
//DeadCode CSB 24/05/99								Wingman->ai.ManStep = 15;
//DeadCode CSB 24/05/99							else
						{
							if(NewTarg)
							{
								Wingman->ai.ManStep = 1;
								Wingman->SetManoeuvreTime(SECS100 / 2);
							}
							Wingman->ai.unfriendly = ai.unfriendly;
							Wingman->ai.manoeuvre  = (MANOEUVRE)ai.manoeuvre;
						}
					}
				}
			}
			break;
		}
//*************************************************************************************************
		case DA_SPACEDIND:
		{
			//Spaced Individual Pattern Low Level Run
			if((!AnyoneInPhaseN(1)) || (!NewTarg))
			{
//DeadCode CSB 24/05/99					if(!ChooseAWeapon())
//DeadCode CSB 24/05/99						ai.ManStep = 15;
//DeadCode CSB 24/05/99					else
				{
					int ElementNumber;
					ai.unfriendly = SelectTarget(ai.unfriendly, &ElementNumber);//, ACNumber);
					ai.manoeuvre = (MANOEUVRE)ElementNumber;
					RetVal = TRUE;
					if(NewTarg)
					{
						ai.ManStep = 1;
						SetManoeuvreTime(8 * SECS100);
					}
				}
			}
			break;
		}
//*************************************************************************************************
		case DA_SPACEDELT:
		{
		//Spaced Element Pattern Low Level Run
			if(IsLocalLeader())
			{
				if((!AnyoneInPhaseN(1)) || (!NewTarg))
				{
//DeadCode CSB 24/05/99						if(!ChooseAWeapon())
//DeadCode CSB 24/05/99							ai.ManStep = 15;
//DeadCode CSB 24/05/99						else
					{
						int ElementNumber, ACNumber;
						ai.unfriendly = SelectTarget(ai.unfriendly, &ElementNumber);//, ACNumber);
						ai.manoeuvre = (MANOEUVRE)ElementNumber;
						RetVal = TRUE;
						if(NewTarg)
						{
							ai.ManStep = 1;
							SetManoeuvreTime(8 * SECS100);
						}
								
						AirStrucPtr Wingman = Follower();
						if((Wingman) && (NewTarg) && (Wingman->fly.callnum > fly.callnum))
						{
							ChooseAWeapon();
							if(weap.weapontype == LT_BOMB)
							{
								if(CarryingNapalm())
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_1, MSG_STARTINGTRGTRUN_RPT, *this, NULL, Follower()));
								else
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_0, MSG_STARTINGTRGTRUN_RPT, *this, NULL, Follower()));
							}
							else if(weap.weapontype == LT_ROCKET)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_2, MSG_STARTINGTRGTRUN_RPT, *this, NULL, Follower()));
							else
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTAPPROACH_L, MSG_STARTINGTRGTRUN_RPT, *this, NULL, Follower()));
							
							if(Wingman == Persons2::PlayerGhostAC)	// Wingman is player
							{
					
							}
							else
//DeadCode CSB 24/05/99								if(!Wingman->ChooseAWeapon())
//DeadCode CSB 24/05/99									Wingman->ai.ManStep = 15;
//DeadCode CSB 24/05/99								else
							{
								if(NewTarg)
								{
									Wingman->ai.ManStep = 1;
									Wingman->SetManoeuvreTime(8 * SECS100);
								}
								Wingman->ai.unfriendly = ai.unfriendly;
								Wingman->ai.manoeuvre  = (MANOEUVRE)ai.manoeuvre;
							}
						}
					}
				}
			}
			break;
		}
//*************************************************************************************************
		case DA_SPACEDFLT:
		{
			//Spaced Flight Pattern Low Level Run
			if(IsLocalLeader())
			{
				if((!AnyoneInPhaseN(1)) || (!NewTarg))
				{
//DeadCode CSB 24/05/99						if(!ChooseAWeapon())
//DeadCode CSB 24/05/99							ai.ManStep = 15;
//DeadCode CSB 24/05/99						else
					{
						int ElementNumber, ACNumber;
						ai.unfriendly = SelectTarget(ai.unfriendly, &ElementNumber);//, ACNumber);
						ai.manoeuvre = (MANOEUVRE)ElementNumber;
						RetVal = TRUE;
						if(NewTarg)
						{
							ai.ManStep = 1;
							SetManoeuvreTime(8 * SECS100);
						}

						AirStrucPtr callee = PlayerInFlight();
						if((!callee) && (follower))
							callee = Follower();
						
						if((callee) && (NewTarg) && (callee->fly.callnum > fly.callnum))
						{
							ChooseAWeapon();
							if(weap.weapontype == LT_BOMB)
							{
								if(CarryingNapalm())
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_1, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));
								else
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_0, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));
							}
							else if(weap.weapontype == LT_ROCKET)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTINGTRGTRUN_OPT_2, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));
							else
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STARTAPPROACH_L, MSG_STARTINGTRGTRUN_RPT, *this, NULL, callee));
						}

						AirStrucPtr foll = Follower();
						if(foll)
						{
							if(foll == Persons2::PlayerGhostAC)	// Wingman is player
							{
							
							}
							else
//DeadCode CSB 24/05/99								if(!foll->ChooseAWeapon())
//DeadCode CSB 24/05/99									foll->ai.ManStep = 15;
//DeadCode CSB 24/05/99								else
							{
								if(NewTarg)
								{
									foll->ai.ManStep = 1;
									foll->SetManoeuvreTime(8 * SECS100);
								}

								foll->ai.unfriendly = ai.unfriendly;
								foll->ai.manoeuvre  = (MANOEUVRE)ai.manoeuvre;
							}
						}		
						foll = fly.nextflight;	//second element leader
						if(foll)
						{
							if(foll == Persons2::PlayerGhostAC)	// Wingman is player
							{
							
							}
							else
//DeadCode CSB 24/05/99								if(!foll->ChooseAWeapon())
//DeadCode CSB 24/05/99									foll->ai.ManStep = 15;
//DeadCode CSB 24/05/99								else
							{
								if(NewTarg)
								{
									foll->ai.ManStep = 1;
									foll->SetManoeuvreTime(8 * SECS100);
								}
								foll->ai.unfriendly = ai.unfriendly;
								foll->ai.manoeuvre  = (MANOEUVRE)ai.manoeuvre;
							}
						}		
						if(foll)
							foll = fly.nextflight->Follower();	//second element wingman
						if(foll)
						{
							if(foll == Persons2::PlayerGhostAC)	// Wingman is player
							{
							
							}
							else
//DeadCode CSB 24/05/99								if(!foll->ChooseAWeapon())
//DeadCode CSB 24/05/99									foll->ai.ManStep = 15;
//DeadCode CSB 24/05/99								else
							{
								if(NewTarg)
								{
									foll->ai.ManStep = 1;
									foll->SetManoeuvreTime(8 * SECS100);
								}
								foll->ai.unfriendly = ai.unfriendly;
								foll->ai.manoeuvre  = (MANOEUVRE)ai.manoeuvre;
							}
						}		
					}
				}
			}
			break;
		}
//*************************************************************************************************
	}
	return RetVal;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AnyoneInPhaseN
//Author		Craig Beeston
//Date			Sat 3 Apr 1999
//
//Description	Checks if any member of this group is in manoeuvre pahse N
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::AnyoneInPhaseN(char PhaseNum)
{
 	Bool SomeoneInPhase1 = FALSE;
	AirStrucPtr grplead = FindGroupLeader();

	for (AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
		for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
			if(foll->ai.ManStep == PhaseNum)
			{
				if (foll->AcIsPlayer() && PhaseNum==1)
					foll->ai.ManStep.value=0;
				SomeoneInPhase1 = TRUE;
			}
	return(SomeoneInPhase1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsThisBombLeader
//Author		Craig Beeston
//Date			Fri 23 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool AirStruc::IsThisBombLeader()
{
 	if(formpos == 0)
		return(TRUE);	
	else
	{
		if((waypoint) && (waypoint->skipunder))
			if(uniqueID.count == waypoint->skipunder)
				return(TRUE);
	}
	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsLocalLeader
//Author		Craig Beeston
//Date			Tue 11 May 1999
//
//Description	Decide whether AC is a bombing leader depending on duty 
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool AirStruc::IsLocalLeader()
{
	int flightpos = position();
	char localduty = duty & ACTIONSUBCODE;
	switch(localduty)
	{
		case DA_HIGH:
		case DA_WIDE:
		case DA_SINGLEFILE:
			if(IsThisBombLeader())	return(true);
			else					return(false);

		case DA_INDIVIDUAL:
		case DA_SPACEDIND:
			return(true);

		case DA_ELEMENT:
		case DA_SPACEDELT:
			if((flightpos == 0) || (flightpos == 2))	return(true);
			else										return(false);

		case DA_SPACEDFLT:
			if(flightpos == 0)	return(true);
			else				return(false);
	}
	return(true);	//Shouldn't get this far
}	
	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CountGroup
//Author		Craig Beeston
//Date			Fri 23 Apr 1999
//
//Description	Counts the number of aircraft in this group
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord AirStruc::CountGroup()
{
 	UWord NumAC = 0;
	AirStrucPtr grplead = FindGroupLeader();

	for (AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
		for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
			NumAC++;

	return(NumAC);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotateToHdg
//Author		Craig Beeston
//Date			Fri 23 Apr 1999
//
//Description	Takes a vector and works out its components in a given heading
//
//Inputs		MULSHSIN
//
//Returns	
//
//------------------------------------------------------------------------------
COORDS3D* AirStruc::RotateToHdg(COORDS3D GlobDelta, COORDS3D& LocalDelta, ANGLES Heading)
{
	SWord SinHdg, CosHdg;
	Math_Lib.high_sin_cos (Heading, SinHdg, CosHdg);
	int DX=MULSHSIN(CosHdg,GlobDelta.X,ANGLES_SHIFT)-MULSHSIN(SinHdg,GlobDelta.Z,ANGLES_SHIFT);
	int DZ=MULSHSIN(CosHdg,GlobDelta.Z,ANGLES_SHIFT)+MULSHSIN(SinHdg,GlobDelta.X,ANGLES_SHIFT);

	LocalDelta.X = DX;
	LocalDelta.Y = GlobDelta.Y;
	LocalDelta.Z = DZ;
	return(&LocalDelta);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindLeadUID
//Author		Craig Beeston
//Date			Mon 7 Jun 1999
//
//Description	Finds the bombing leaders UniqueID
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UniqueID AirStruc::FindLeadUID()
{
	if((waypoint) && (waypoint->skipunder))
		return(waypoint->skipunder);

	AirStrucPtr GrpLead = FindGroupLeader();
//DEADCODE DAW 07/06/99 	if(GrpLead) 
		return(GrpLead->uniqueID.count);

//DEADCODE DAW 07/06/99 	return(UID_NULL);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WindTrackCorrection
//Author		Craig Beeston
//Date			Thu 10 Jun 1999
//
//Description	Calculates the change in hdg needed to compensate for the wind
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::WindTrackCorrection(SWord Vel, SWord DesHdg, SWord DesPitch, SWord& dVel, SWord& dHdg, SWord& dPitch)
{
	SWord WindHdg;
	SWord WindVel;
	MMC.Sky.GetWindDirVel(World.Y, WindHdg, WindVel);
	if(!WindVel)
	{
		dHdg   = 0;
		dPitch = 0;
		dVel   = 0;
		return;
	}

	SWord DeltaHdg = DesHdg - WindHdg + ANGLES_180Deg;
	
	SWord sindhdg, cosdhdg;
	Math_Lib.high_sin_cos((Angles)DeltaHdg, sindhdg, cosdhdg);
	
	SWord sinpitch, cospitch;
	Math_Lib.high_sin_cos((Angles)DesPitch, sinpitch, cospitch);

	SLong NewVelHori = ((Vel * cospitch) + (WindVel * cosdhdg)) / ANGLES_FRACT;
	FP HdgCorr = WindVel * sindhdg / (NewVelHori * FPIE);

	FP PitchCorr = 10429.0 * (FP)WindVel * (FP)sinpitch * (FP)cosdhdg / ((FP)Vel * (FP)ANGLES_FRACT * (FP)ANGLES_FRACT);

	FP VelCorr = WindVel * cosdhdg * cospitch / (ANGLES_FRACT * ANGLES_FRACT);

	dHdg   = HdgCorr;
	dPitch = PitchCorr;
	dVel   = VelCorr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WindBulletDrift
//Author		Craig Beeston
//Date			Fri 11 Jun 1999
//
//Description	Calculates the resulting change in velocity, pitch and heading due to the effects of the wind
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::WindBulletDrift(SWord Vel, SWord DesHdg, SWord DesPitch, SWord& dVel, SWord& dHdg, SWord& dPitch)
{
	SWord dhdg, dpitch;
	WindTrackCorrection(Vel, DesHdg, DesPitch, dVel, dhdg, dpitch);

	dHdg   = -dhdg;
	dPitch = -dpitch;
//DeadCode CSB 11/06/99		
//DeadCode CSB 11/06/99		SWord WindHdg;
//DeadCode CSB 11/06/99		SWord WindVel;
//DeadCode CSB 11/06/99		MMC.Sky.GetWindDirVel(World.Y, WindHdg, WindVel);
//DeadCode CSB 11/06/99		if(!WindVel)
//DeadCode CSB 11/06/99		{
//DeadCode CSB 11/06/99			dHdg   = 0;
//DeadCode CSB 11/06/99			dPitch = 0;
//DeadCode CSB 11/06/99			return;
//DeadCode CSB 11/06/99		}
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		SWord DeltaHdg = DesHdg - WindHdg + ANGLES_180Deg;
//DeadCode CSB 11/06/99		SWord sinhdg, coshdg;
//DeadCode CSB 11/06/99		Math_Lib.high_sin_cos((Angles)DeltaHdg, sinhdg, coshdg);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		SWord sinpitch, cospitch;
//DeadCode CSB 11/06/99		Math_Lib.high_sin_cos((Angles)DesPitch, sinpitch, cospitch);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		SLong NewVelHori = ((Vel * cospitch) + (WindVel * cosdhdg)) / ANGLES_FRACT;
//DeadCode CSB 11/06/99		FP HdgCorr = WindVel * sindhdg / (NewVelHori * FPIE);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		FP PitchCorr = 10429 * WindVel * sinpitch * cosdhdg / (Vel * ANGLES_FRACT * ANGLES_FRACT);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		FP VelCorr = WindVel * cosdhdg * cospitch / (ANGLES_FRACT * ANGLES_FRACT);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		dHdg   = HdgCorr;
//DeadCode CSB 11/06/99		dPitch = PitchCorr;
//DeadCode CSB 11/06/99		dVel   = VelCorr;
//DeadCode CSB 11/06/99			
//DeadCode CSB 11/06/99	//////////////
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		SLong TrueVel = Vel + (WindVel * coshdg) / ANGLES_FRACT;
//DeadCode CSB 11/06/99		FP HdgCorr = WindVel * sinhdg / (TrueVel * FPIE);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		TrueVel = 2 * Vel - TrueVel;
//DeadCode CSB 11/06/99		FP PitchCorr = WindVel * sinpitch / (TrueVel * FPIE);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		FP VelCorr = WindVel * coshdg * cospitch / (ANGLES_FRACT * ANGLES_FRACT);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		dHdg   = HdgCorr;
//DeadCode CSB 11/06/99		dPitch = PitchCorr;
//DeadCode CSB 11/06/99		dVel   = VelCorr;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcBulletVel
//Author		Craig Beeston
//Date			Fri 11 Jun 1999
//
//Description	Calculates the velocity, pitch and heading of a bullet including the effects of the wind
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::CalcBulletVel(SWord MuzVel, SWord &Hdg, SWord &Pitch, SWord &BullVel)
{
	SWord dVel, dHdg, dPitch;
	SWord bullvel   = vel + MuzVel;
	SWord bullhdg   = hdg;
	SWord bullpitch = pitch;
	WindBulletDrift(bullvel, hdg, pitch, dVel, dHdg, dPitch);
		
	bullvel   += dVel;
	bullhdg   += dHdg;
	bullpitch += dPitch;

	if(bullpitch > ANGLES_90Deg)
	{
		bullpitch =  ANGLES_180Deg - bullpitch;
		bullhdg   += ANGLES_180Deg;
	}
	if(-bullpitch > ANGLES_90Deg)
	{
		bullpitch = -ANGLES_180Deg - bullpitch;
		bullhdg   += ANGLES_180Deg;
	}

	BullVel = bullvel;
	Hdg     = bullhdg;
	Pitch   = bullpitch;
}

