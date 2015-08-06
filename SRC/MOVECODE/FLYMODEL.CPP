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

//Filename       flymodel.cpp
//System         
//Author         R. Hyde 
//Date           Mon 11 Sep 1995
//Description    
//------------------------------------------------------------------------------

//#define		_NOFLIGHTMODEL_

#include	"dosdefs.h"
#define F_GRAFIX
#define F_COMMON
#include	"files.g"
#include	"worldinc.h"
#include	"planetyp.h"
#include	"myangles.h"
#include	"enumbits.m"
#include	"mytime.h"											//RDH 25Apr96
//MATHABLE	(ANGLES)
#include	"flymodel.h"
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
#include "persons2.h"											//RDH 24Jul96
#include	"ranges.h"
#include	"winmove.h"											//ARM 10Oct96
#include	"modvec.h"											//ARM 08Jan97
#include	"model.h"											//ARM 07Jan97
#include	"shapes.h"
#include	"replay.h"
//extern	ULong	GR_Quit3DNow;
extern DPlay _DPlay;

										//ARM 06Nov96
//DeadCode RDH 26Mar98 //DeadCode RDH 23Feb96 extern	PlaneType&	camel;
//DeadCode RDH 26Mar98 //-----------------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //	Special Notes:
//DeadCode RDH 26Mar98 //		take care of vel_cms for fast aircraft	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //-----------------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	Remaining jobs
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	1	exit for dead aircraft +++
//DeadCode RDH 26Mar98 //	2	easier model to fly
//DeadCode RDH 26Mar98 //	3	Wind
//DeadCode RDH 26Mar98 //	4	Ground handling
//DeadCode RDH 26Mar98 //		on ground turn a/c with aileron (s&r 185)
//DeadCode RDH 26Mar98 //		ground loop
//DeadCode RDH 26Mar98 //		ground effect
//DeadCode RDH 26Mar98 //	5	Fuel
//DeadCode RDH 26Mar98 //	6	Waypoint update	
//DeadCode RDH 26Mar98 //	7	Damage
//DeadCode RDH 26Mar98 //	8	Tidy up thrust patch
//DeadCode RDH 26Mar98 //	9	Pre stall buffet and buffet in general
//DeadCode RDH 26Mar98 //	10	Trim needs checking
//DeadCode RDH 26Mar98 //	11	check duplication in InitManualPilot and persons
//DeadCode RDH 26Mar98 //-----------------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	Concerns
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	1	Introducing the correct aoa for drag calculations gave unstable aircraft
//DeadCode RDH 26Mar98 //			effect is excluded-> no adverse yaw		
//DeadCode RDH 26Mar98 //	2	Calculation of croll looks dubious and so is excluded
//DeadCode RDH 26Mar98 //	3	Some warning light code not needed for Flying Corps is included
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //-----------------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	Factors not included
//DeadCode RDH 26Mar98 //	
//DeadCode RDH 26Mar98 //	1	P effect
//DeadCode RDH 26Mar98 //	2	reduced lift on wing in shadow of body
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //-----------------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //The notes section here consists of the following parts:
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		1	Permanent notes on the flight model	
//DeadCode RDH 26Mar98 //		2	Notes on relationship with rest of code
//DeadCode RDH 26Mar98 //		3	notes for me during development of flight model
//DeadCode RDH 26Mar98 //
//-----------------------------------------------------------------------------------------
//1	Permanent notes on the flight model	
//
//
//	1	Units
//			 	vel,i_a_s			10 cm/s
//				vel_cm  			cm/s
//				vel_mm  			cm/s
//				WorldX,Y,Z			cm
//				forces				N
//				airdensity			g/m^3
//				sos					m/s
//				angles				all use full word
//				trig functions		signed word, 7fff = 1.0, 8000 = -1	
//
//	2	In the model, y is reversed:
//
//			cposy = -ControlledAC->World.Y; 		world y postion of ac
//			
//	3	Angles 					
//			    roll right wing down = +ve
//				hdg change to right  = +ve
//				pitch up			 = +ve
//				
//		When the ac is pointing above the velocity vector, then aoa = +ve
//		When the ac has a bigger heading than velocity vector, then slip = -ve
//
//
//
//DeadCode RDH 26Mar98 //	4	Defining an aircraft
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		See separate notes
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	5	Use of Rudder:
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			Oppose torque of engine
//DeadCode RDH 26Mar98 //			to produce side slip
//DeadCode RDH 26Mar98 //			keep level near stall (ailerons use lead to spin?)
//DeadCode RDH 26Mar98 //			balance adverse drag
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			In old model 1,3,4 absent 
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			When rudder is applied, aircraft skids. Side slip angle
//DeadCode RDH 26Mar98 //			angle and dihedral work to produce roll
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			When aircraft is rolled with ailerons, slip is produced
//DeadCode RDH 26Mar98 //			Slip and weathercocking effect of tail give heading change of
//DeadCode RDH 26Mar98 //			aircraft.Dihedral also has effect of unrolling
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	7	Aileron effects
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			On applying aileron, drag on wings in changed in opposite 
//DeadCode RDH 26Mar98 //			directions. This can produce an adverse yaw
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	8	Moments
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	8.1	Pitch
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	8.2	Roll
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		+ve slip gives -roll
//DeadCode RDH 26Mar98 //				effect increased by dihedral
//DeadCode RDH 26Mar98 //				effect caused by dihedral gving bigger aoa for one wing
//DeadCode RDH 26Mar98 //				and reduced lift on wing in shadow of body		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		torque on prop (and rotary engines)
//DeadCode RDH 26Mar98 //					opposite and equal, is it rate of change of torque or magnitude
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		ailerons
//DeadCode RDH 26Mar98 //				increase aoa on upper wing	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		roll of aircraft (lateral damping)
//DeadCode RDH 26Mar98 //				relative wind on down wing produce higher aoa, hence increases lift
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		overbanking tendency
//DeadCode RDH 26Mar98 //				slip gives yaw which means one wing is travelling faster
//DeadCode RDH 26Mar98 //				which gives roll
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	8.3 Yaw
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		rudder
//DeadCode RDH 26Mar98 //		slipstream
//DeadCode RDH 26Mar98 //		precedence
//DeadCode RDH 26Mar98 //			prop turning clockwise from pilot seat
//DeadCode RDH 26Mar98 //			right turn gives downward force
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		p effect
//DeadCode RDH 26Mar98 //		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		adverse yaw
//DeadCode RDH 26Mar98 //			rolling wing means lift difference which means drag difference	
//DeadCode RDH 26Mar98 //		weather cocking
//DeadCode RDH 26Mar98 //			tail moves ac into relative wind
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	9	Forces
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		For lift, consider effect on body lift (important for knife-edge)
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //


//-----------------------------------------------------------------------------------------
//2	Notes on relationship with rest of code
//
//
//	1	We calculate the position of a point on the aircraft. There are a number of
//		significant points:
//					pilot eye
//					centre around which aircraft turns
//					centre of drawn shape
//		At present we don't distinguish between two
//
//	2	Changing from auto to manual has changed, I will probably need to know
//		so that trim can be allowed
//
//	3	
// 
//DeadCode RDH 26Mar98 //	4	SetFlags, WayPointUpdate and FuelLeft is commented out	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	5	The thrust routine needs to be accessed indirectly
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	6	damage lights needed for effect on thrust, aileron and elevator
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//	8	
//	 	if (ControlledAC2 == ControlledAC)
//				true for manual pilot
//
//DeadCode RDH 26Mar98 //	9	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	10	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	12	I've introduced a 1cm/sec velocty field for the flight model, vel_cms.
//DeadCode RDH 26Mar98 //		ControlledAC->vel is still in 10cm/s units. vel_cms in not used
//DeadCode RDH 26Mar98 //		in other equations
//DeadCode RDH 26Mar98 //		Also introduced mm/s to reduce rounding error
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //-----------------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //Static data
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //elevator deflection constant,  see taillift and Theory of Flight p502
//DeadCode RDH 26Mar98 //increments in 5 deg deviation steps
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 static UWord 	ElevatorDeflection_Data[] =
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  			{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  						0,20,40,65,
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  						90,120,
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  //30
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  					155,
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  					190,225,
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  //45
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  					280
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  			};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 static UWord 	ElevatorDeflection_Data[] =
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  						0,15,30,50,
//DeadCode RDH 26Mar98  						80,100,
//DeadCode RDH 26Mar98  //30
//DeadCode RDH 26Mar98  					120,
//DeadCode RDH 26Mar98  					140,160,
//DeadCode RDH 26Mar98  //45
//DeadCode RDH 26Mar98  //DeadCode RDH 07Dec96 					175
//DeadCode RDH 26Mar98  					190											//RDH 07Dec96
//DeadCode RDH 26Mar98  			};
 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //increments in 1000m steps
//DeadCode RDH 26Mar98 //mach in m/s
//DeadCode RDH 26Mar98 static UWord 	Mach_Data[] =
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				340,
//DeadCode RDH 26Mar98 				337,
//DeadCode RDH 26Mar98 				333,
//DeadCode RDH 26Mar98 				329,
//DeadCode RDH 26Mar98 				325,
//DeadCode RDH 26Mar98 				321,
//DeadCode RDH 26Mar98 				317,
//DeadCode RDH 26Mar98 				313,
//DeadCode RDH 26Mar98 				308,
//DeadCode RDH 26Mar98 				304,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				297,
//DeadCode RDH 26Mar98 				298,
//DeadCode RDH 26Mar98 				299
//DeadCode RDH 26Mar98 			};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //increments in 1000m steps
//DeadCode RDH 26Mar98 //density in g/m^3
//DeadCode RDH 26Mar98 static UWord AirDensity_Data[] = 
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				1225,
//DeadCode RDH 26Mar98 				1112,
//DeadCode RDH 26Mar98 				1007,
//DeadCode RDH 26Mar98 				909,
//DeadCode RDH 26Mar98 				819,
//DeadCode RDH 26Mar98 				736,
//DeadCode RDH 26Mar98 				660,
//DeadCode RDH 26Mar98 				590,
//DeadCode RDH 26Mar98 				526,
//DeadCode RDH 26Mar98 				467,
//DeadCode RDH 26Mar98 				414,
//DeadCode RDH 26Mar98 				365,
//DeadCode RDH 26Mar98 				312,
//DeadCode RDH 26Mar98 				267,
//DeadCode RDH 26Mar98 				228,
//DeadCode RDH 26Mar98 				195,
//DeadCode RDH 26Mar98 				195,
//DeadCode RDH 26Mar98 				166,
//DeadCode RDH 26Mar98 				142,
//DeadCode RDH 26Mar98 				122,
//DeadCode RDH 26Mar98 				104,
//DeadCode RDH 26Mar98 				89,
//DeadCode RDH 26Mar98 				76,
//DeadCode RDH 26Mar98 				65
//DeadCode RDH 26Mar98 			};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //Table of SQR(DensityRatio) * 65536
//DeadCode RDH 26Mar98 //DensityRatio is ratio of air density at altitude to air density at sea level 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 static UWord AirDensity_Ratio[] =
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				65535,
//DeadCode RDH 26Mar98 				63250,
//DeadCode RDH 26Mar98 				61250,
//DeadCode RDH 26Mar98 				59375,
//DeadCode RDH 26Mar98 				57500,
//DeadCode RDH 26Mar98 				55625,
//DeadCode RDH 26Mar98 				53625,
//DeadCode RDH 26Mar98 				51750,
//DeadCode RDH 26Mar98 				49875,
//DeadCode RDH 26Mar98 				48250,
//DeadCode RDH 26Mar98 				46500,
//DeadCode RDH 26Mar98 				44875,
//DeadCode RDH 26Mar98 				43250,
//DeadCode RDH 26Mar98 				41625,
//DeadCode RDH 26Mar98 				40000,
//DeadCode RDH 26Mar98 				38500,
//DeadCode RDH 26Mar98 				37000,
//DeadCode RDH 26Mar98 				35375,
//DeadCode RDH 26Mar98 				33625,
//DeadCode RDH 26Mar98 				31875,
//DeadCode RDH 26Mar98 				30250,
//DeadCode RDH 26Mar98 				28500,
//DeadCode RDH 26Mar98 				27125,
//DeadCode RDH 26Mar98 				25750
//DeadCode RDH 26Mar98 	};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 static UWord ManualPilot::airdensityratiosquareroot[] =
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				65535,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				64383,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				63357,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				62280,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				61387,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				60377,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				59282,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				58236,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				57172,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				56233,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				55203,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				54230,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				53239,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				52230,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				51200,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				50231,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				49243,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				48149,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				46943,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				45705,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				44525,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				43218,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				42162,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				41080
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 	};
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 static UWord Shok_Data[] = 
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		0,
//DeadCode RDH 26Mar98 		0,
//DeadCode RDH 26Mar98 	     0,
//DeadCode RDH 26Mar98 	     0,
//DeadCode RDH 26Mar98 	     1,
//DeadCode RDH 26Mar98 	     5,
//DeadCode RDH 26Mar98 	     10,
//DeadCode RDH 26Mar98 	     120,
//DeadCode RDH 26Mar98 		600,
//DeadCode RDH 26Mar98 		1000,
//DeadCode RDH 26Mar98 		1000,
//DeadCode RDH 26Mar98 		1000,
//DeadCode RDH 26Mar98 		1000,
//DeadCode RDH 26Mar98 		1130,
//DeadCode RDH 26Mar98 		1190,
//DeadCode RDH 26Mar98 		1250,
//DeadCode RDH 26Mar98 		1300,
//DeadCode RDH 26Mar98 		1350,
//DeadCode RDH 26Mar98 		1400,
//DeadCode RDH 26Mar98 		1470,
//DeadCode RDH 26Mar98 		1490,
//DeadCode RDH 26Mar98 		1500
//DeadCode RDH 26Mar98 	};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //flight model equates
//DeadCode RDH 26Mar98 SLong const 	SHORTGRASSCOEFF 	=	30;						//RDH 22Oct96
//DeadCode RDH 26Mar98 SLong const 	LONGGRASSCOEFF 		=	40;
//DeadCode RDH 26Mar98 SLong const 	ANGLE2DIV 	=	2 * 65536/360;
//DeadCode RDH 26Mar98 SLong const 	ROT_X_DAMP 	=	80;
//DeadCode RDH 26Mar98 SLong const 	ROT_Y_DAMP 	=	80;
//DeadCode RDH 26Mar98 SLong const 	ROT_Z_DAMP 	=	80;
//DeadCode RDH 26Mar98 SLong const 	MAXALTITUDE_CM 	=	2200000;
//DeadCode RDH 26Mar98 SLong const 	WORD_FRACT   	=	65536;
//DeadCode RDH 26Mar98 SLong const 	LIFTCONST   	=	100 * 65536 / 360;
//DeadCode RDH 26Mar98 SLong const 	ROWANS_PER_RAD  =	10430;		//65536 / 2PI;
//DeadCode RDH 26Mar98 SLong const 	PITCHCOEFF   	=	104;		//PITCHCOEFF = 	WORD_FRACT / TWOPI100			
//DeadCode RDH 26Mar98 SLong const 	GROUNDEFFECT 	=	1000;		//cms
//DeadCode RDH 26Mar98 SLong const 	K_MACH  	 	=	21500;
//DeadCode RDH 26Mar98 SLong const 	LIMOLDPITCH     =	0x1200;
//DeadCode RDH 26Mar98 SLong const 	FLAP_A_SHIFT 	=	28;
//DeadCode RDH 26Mar98 SLong const 	GEFF_CL_ADJUST  =	15;
//DeadCode RDH 26Mar98 SLong const 	FLAP_CL_ADJUST  =	44;            // (2*FLAP_A_SHIFT) * 80 /100
//DeadCode RDH 26Mar98 SLong const 	FLAP_CMO_ADJUST =	13;
//DeadCode RDH 26Mar98 SLong const 	FLAP_CMO_2 		=	2;
//DeadCode RDH 26Mar98 SLong const 	FLAP_DRAG 		=	3;
//DeadCode RDH 26Mar98 SLong const 	RUDDERVEL		=	1250;
//DeadCode RDH 26Mar98 SLong const 	RUDDERVELP2		=	(RUDDERVEL * RUDDERVEL) / 256;
//DeadCode RDH 26Mar98 SLong const 	ELEVPLUS1		=	1;
//DeadCode RDH 26Mar98 SLong const 	HALFPI100		=	157;
//DeadCode RDH 26Mar98 SLong const 	PI100			=	314;
//DeadCode RDH 26Mar98 SLong const 	TWOPI100		=	628;
//DeadCode RDH 26Mar98 SLong const		ROLLEDCLIMBFACTOR = 4000;
//DeadCode RDH 26Mar98 //DeadCode RDH 29Aug96 SLong const		MINVELO			=	20;
//DeadCode RDH 26Mar98 SLong const		MINVELO			=	4;							//RDH 29Aug96
//DeadCode RDH 26Mar98 SLong const		KRITVEL			=	100;						//RDH 23May96
//DeadCode RDH 26Mar98 SLong const		VELMIN 			= 700;
//DeadCode RDH 26Mar98 SLong const		VELMAX 			= 2400;
//DeadCode RDH 26Mar98 SLong const		VELRANGE 		= 3*(VELMAX-VELMIN)/2;
//DeadCode RDH 26Mar98 SLong const		VEL_MAXSLIPSTREAM = 1790;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 SLong const		POWER_MAXSLIPSTREAM = 65000;
//DeadCode RDH 26Mar98 SLong const		POWER_MAXSLIPSTREAM = 100;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 SLong const		AOA_MAXSLIPSTREAM = 2000;
//DeadCode RDH 26Mar98 SLong const		AOA_MAXSLIPSTREAM = 600;
//DeadCode RDH 26Mar98 //DeadCode RDH 23Jul96 SLong const		FLIGHTMODEL_TIMEFRAME = 2;						//RDH 25Apr96
//DeadCode RDH 26Mar98 SLong const		FLIGHTMODEL_TIMEFRAME = TimerCode::FIXEDFRAMETIME;						//RDH 25Apr96
//DeadCode RDH 26Mar98 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//INSTANCE		Manual_Pilot
//Author		Jim Taylor
//Date			Tue 31 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ManualPilot	Manual_Pilot;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ManualPilot	CONSTRUCTOR
//Author		R. Hyde 
//Date			Thu 26 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	ManualPilot::ManualPilot()
{
	View_Point=NULL;
//DeadCode RDH 26Mar98 	elevatordeflectiondata = ElevatorDeflection_Data;
// 	machdata=Mach_Data;
//	airdensitydata=AirDensity_Data;
//	airdensityratio=AirDensity_Ratio;
//DeadCode RDH 03Jun96 	airdensityratiosquareroot=AirDensity_Ratio_SquareRoot;
//	shokdata=Shok_Data;
	ControlledAC2=NULL;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Associate
//Author		Jim Taylor
//Date			Tue 31 Oct 1995
//
//Description	Associates specific 3d item to manual movecode.
//				May also be used to flag auto/manual switch,
//				so put any trim init code here!
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::Associate	(
			AirStruc*	manualas,				//item to move
			CONTROLMODE		inmanual)		//TRUE	//flag for man/auto/auto accel
{
	if  (inmanual!=controlmode || ControlledAC2!=manualas)
	{
		controlmode=inmanual?MANUAL:AUTO;
		ControlledAC2=manualas;
		InitManualPilot(ControlledAC2);
	}
}
//JIM 15Oct96

void	ManualPilot::AutoToggle(CONTROLMODE dead)
{
	if (dead==PILOTDEAD)
		controlmode=PILOTDEAD;
	else
		if (controlmode!=PILOTDEAD)								//JIM 11Oct96
		{														//JIM 11Oct96
			ControlledAC2->information=FALSE;
			ControlledAC2->slowdownleader=FALSE;
			if (dead==TOGGLE)									//JIM 11Oct96
			{
				dead=controlmode==AUTO?MANUAL:AUTO;
				Associate(ControlledAC2,dead);
			}
			else AutoToggleAircraft(ControlledAC2,dead);					//rdh 6/4/98
		}														//JIM 11Oct96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Author		R. Hyde 
//Date		Wed 30 Aug 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::MainManualPilot()
{
//TempCode PD 3Nov97 
//	return;
//TempCode PD 3Nov97 

//Add timing thing here	//CSB 02/03/99
	
	if (ControlledAC2)
	{
		WorldStuff &world = mobileitem::GetWorld();
		UWord	oldsector=	world.GetSector(ControlledAC2);

///////////////////////////////////////////
//tmp fix should not be running acm on player ac in final version//RDH 20Aug96
		if (controlmode == MANUAL)								//RDH 20Aug96
		{
			if (Persons2::PlayerGhostAC->slowdownleader)			  //JIM 22/03/99
			{														  //JIM 22/03/99
				Persons2::PlayerGhostAC->slowdownleader=FALSE;		  //JIM 22/03/99
				if (ControlledAC2->fly.thrustpercent>=90 && ControlledAC2->vel>1200)
					if (!ControlledAC2->TimeLeft())
					{
						AirStrucPtr found=NULL;
						for (AirStrucPtr l=Persons2::PlayerGhostAC;l;l=l->fly.nextflight)
						{
							for (AirStrucPtr w=l;w;w=w->Follower())
								if (!w->information)
									if (w!=Persons2::PlayerGhostAC)
										found=w;
						}
						if (found)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TOOFAST, MSG_FORMATIONFLYING,found, NULL, ControlledAC2));
						ControlledAC2->SetManoeuvreTime();
					}
			}
			GetKeyCommon (ControlledAC2);				//RDH 15Dec95

//DeadCode AMM 01Dec98 		}
//DeadCode AMM 01Dec98 //DeadCode CSB 15/09/98		 	ControlledAC2->FuelLeft ();								//RDH 03Jun96
//DeadCode AMM 01Dec98 
//DeadCode AMM 01Dec98 		if (controlmode == MANUAL)
//DeadCode AMM 01Dec98 		{
			if (!_Replay.Playback)
			{
				_DPlay.AddDeltas(Persons2::PlayerSeenAC,FALSE); 				
#ifndef	_NOFLIGHTMODEL_
 				FlightModelFixedTime(Persons2::PlayerSeenAC);
#endif
 				Persons2::PlayerSeenAC->SetManualFlightParams ();

				_DPlay.AddDeltas(Persons2::PlayerSeenAC,TRUE);				
			}


			SHAPE.RipStores(ControlledAC2);						//RJS 03Jun98

//			ControlledAC2->CheckManualCourse();					//JIM 03Dec96
//being done by macca.
//DEADCODE JIM 22/03/99 			Persons2::PlayerGhostAC->CheckManualCourse();
		}
		else if (controlmode==AUTOACCEL_WAYPT || controlmode==AUTOACCEL_FWD ||
				controlmode==AUTOACCEL_MSG || controlmode==AUTOACCEL_MISS ||
				controlmode==AUTOACCEL_HOME)
		{
			_DPlay.AddDeltas(Persons2::PlayerSeenAC,FALSE); 				//AMM 10Mar99
			AutoMoveCodeTypeSelect bupMoveCode=ControlledAC2->movecode;
			ControlledAC2->movecode=AUTO_ACCELERATE;
			mobileitem::MoveItem((MobileItemPtr)ControlledAC2,world);
			ControlledAC2->movecode=bupMoveCode;
			_DPlay.AddDeltas(Persons2::PlayerSeenAC,TRUE);				//AMM 10Mar99
		}
		else
		{
//			if (controlmode == MANUAL)								//RDH 20Aug96
//				GetStickKeys(ControlledAC2);

//DeadCode AMM 16Jun98 			if(_DPlay.Implemented)								//AMM 15Apr97
			if (!_Replay.Playback)
			{													
// this moves players ac if player is not in control i.e autospiral, autores etc
																
//				WorldStuff &world = mobileitem::GetWorld();		
																
				_DPlay.AddDeltas(ControlledAC2,FALSE);			
				mobileitem::MoveItem((MobileItemPtr)(ControlledAC2),world);
				_DPlay.AddDeltas(ControlledAC2,TRUE);
			}
			else												//AMM 31Aug98
			{													//AMM 31Aug98
// shouldnt ever get in here?
				INT3;
//DeadCode AMM 07Oct98 				_DPlay.PredictMove(Persons2::PlayerSeenAC);		//AMM 31Aug98
//DeadCode AMM 07Oct98 				Persons2::PlayerSeenAC->fly.pModel->Base (Persons2::PlayerSeenAC);

 			}													//AMM 31Aug98


//			View_Object->right_aoa = ControlledAC2->fly.aoa;
//			View_Object->left_aoa = ControlledAC2->fly.aoa;
		}

///////////////////////////////////////////

		if (ControlledAC2->uniqueID.changed)
		{
			UWord	newsector=	world.GetSector(ControlledAC2);
			if (newsector!=oldsector)
			{
				world.RemoveFromSector(ControlledAC2,oldsector);
				world.AddToWorld(ControlledAC2);
			}
			ControlledAC2->uniqueID.changed = FALSE;						//RDH 26Jun96
		}
 	}
//Add timing thing here	//CSB 02/03/99

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeathSequenceOverride
//Author		Robert Slater
//Date			Wed 15 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 26Jan99 Bool	ManualPilot::DeathSequenceOverride(ItemPtr	itm, int	newmovecode)//DAW 03Sep98
Bool	ManualPilot::DeathSequenceOverride(ItemPtr	itm, int	newmovecode,bool commscalled)//AMM 26Jan99
{
//DeadCode AMM 24Mar99 	if (_Replay.Playback && !commscalled)
//DeadCode AMM 24Mar99 		return FALSE;
//DeadCode AMM 24Mar99 
//DeadCode AMM 24Mar99 	if (_DPlay.Implemented || _Replay.Record)
//DeadCode AMM 24Mar99 	{
//DeadCode AMM 24Mar99 		if (!commscalled)
//DeadCode AMM 24Mar99 			return FALSE;
//DeadCode AMM 24Mar99 		if (!commscalled)
//DeadCode AMM 24Mar99 		{
//DeadCode AMM 24Mar99 			if (_DPlay.firstdeathcall)
//DeadCode AMM 24Mar99 			{
//DeadCode AMM 24Mar99 				_DPlay.firstdeathcall=false;
//DeadCode AMM 24Mar99 				return TRUE;
//DeadCode AMM 24Mar99 			}
//DeadCode AMM 24Mar99 			else
//DeadCode AMM 24Mar99 			{
//DeadCode AMM 24Mar99 				return FALSE;
//DeadCode AMM 24Mar99 			}
//DeadCode AMM 24Mar99 		}
//DeadCode AMM 24Mar99 		else
//DeadCode AMM 24Mar99 		{
//DeadCode AMM 24Mar99 			_DPlay.firstdeathcall=true;
//DeadCode AMM 24Mar99 		}
//DeadCode AMM 24Mar99 	}

	Bool	wasset = FALSE;										//DAW 03Sep98
	if (itm->Status.size >= AIRSTRUCSIZE)
	{
		AirStrucPtr		acptr = (AirStrucPtr) itm;
		MinAnimData*	mad = (MinAnimData*) acptr->Anim;

//DeadCode AMM 24Mar99 		if (!_Replay.Playback || (itm != Persons2::PlayerSeenAC))		//RJS 30Oct98
		{
			if (	(acptr->movecode != newmovecode)
				&&	(acptr->movecode != AUTO_NOPPILOT)					//RJS 27Aug98
				&&	(acptr->movecode != AUTO_HITWATER)					//RJS 27Aug98
				&&	(acptr->movecode != AUTO_CRASHSKID)					//RJS 27Aug98
				&&	(acptr->movecode != AUTO_CRASHROLL)					//RJS 27Aug98
				&&	(acptr->movecode != AUTO_SPIRAL2GROUND)	)		//DAW 03Sep98
//DEADCODE DAW 07/05/99 				&&	(acptr->movecode != AUTO_DEATHSEQUENCE)	)			//RJS 27Aug98
			{
//DeadCode RJS 23May99 				mad->itemstate = DEAD;

				if (itm == Persons2::PlayerSeenAC)						//RJS 30Oct98
				{
					controlmode=PILOTDEAD;
//Dead					acptr->Status.deadtime = 1000;//Just to make sure...

					if (_Replay.Record)									//RJS 30Oct98
					{
						UByte	effect = RDEATH_NULL;

						switch (newmovecode)
						{
							case AUTO_HITWATER:
							case AUTO_CRASHSKID:
								effect = RDEATH_SKID;
								break;
							case AUTO_CRASHROLL:
								effect = RDEATH_ROLL;
								break;
							case AUTO_SPIRAL2GROUND:
							case AUTO_DEATHSEQUENCE:
								effect = RDEATH_DIVE;
								break;
						}

		 				_DPlay.NewSpecial(PIDC_DEATHMOVEEFFECT,effect,0,0);
					}
				}

				acptr->movecode = (AutoMoveCodeTypeSelect) newmovecode;
				wasset = TRUE;										//DAW 03Sep98

				if (!acptr->Status.deadtime)						//RJS 17May99
				{
					ItemPtr	lasthitter = acptr;
					if (acptr->lasthitter.count)
					{
						lasthitter = (ItemPtr)Persons2::ConvertPtrUID((UniqueID)acptr->lasthitter.count);
						if (!lasthitter)  		//checks to see if it's an airstruc within ScoreSimpleItemKilled
							lasthitter = acptr;
					}

					if (_DPlay.Implemented)						//RJS 03Jun99
					{											//RJS 03Jun99
						if (_DPlay.GameType<COMMSQUICKMISSION)	//RJS 03Jun99
							_DPlay.SetScore(acptr,lasthitter);	//RJS 03Jun99
						else
						{
							if (_DPlay.GameType>TEAMPLAY)
								_DPlay.NewScoreClaim(lasthitter,acptr->uniqueID.count);
						}
					}
					else
					{
						if (lasthitter->Status.size == AIRSTRUCSIZE)	//RJS 03Jun99
							itm->ScoreSimpleItemKilled(true,(AirStrucPtr)lasthitter);//RJS 25May99
					}

					acptr->BreakForm();								//RJS 17May99
				}
			}
			else
			{
				//It's ok to say you can't move anymore,
				//but not ok to say you can...
				if (newmovecode == AUTO_NOPPILOT)
					acptr->movecode = (AutoMoveCodeTypeSelect) newmovecode;
			}

			//Make sure it is dead!								
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(acptr->shape);	//RJS 17May99
			acptr->Status.deadtime = sdptr->DeadTime;						//RJS 17May99
			acptr->Status.deadscale = sdptr->DeadScale;						//RJS 17May99
	 		acptr->Status.deaded = TRUE;									//RJS 17May99
			if (acptr == Persons2::PlayerSeenAC)				//RJS 09Jul99
			{
				Persons2::PlayerGhostAC->Status.deadtime = sdptr->DeadTime;
				Persons2::PlayerGhostAC->Status.deadscale = sdptr->DeadScale;
				Persons2::PlayerGhostAC->Status.deaded = TRUE;
				Persons2::PlayerGhostAC->overview_movecode=acptr->overview_movecode;
			}
			
			mad->itemstate = DEAD;								//RJS 23May99

			AircraftAnimData* adptr = (AircraftAnimData*)acptr->Anim;//DAW 09Jun99
			adptr->shooting = 0;								//DAW 09Jun99
		}
//DeadCode AMM 24Mar99 		else
//DeadCode AMM 24Mar99 		{
//DeadCode AMM 24Mar99 			// Simulate death movecode set response for replay...
//DeadCode AMM 24Mar99 			if (_Replay.ReplayDeathMode == RDEATH_NULL)
//DeadCode AMM 24Mar99 			{
//DeadCode AMM 24Mar99 				mad->itemstate = DEAD;
//DeadCode AMM 24Mar99 				acptr->Status.deadtime = 1000;//Just to make sure...
//DeadCode AMM 24Mar99 
//DeadCode AMM 24Mar99 				wasset = TRUE;						
//DeadCode AMM 24Mar99 			}
//DeadCode AMM 24Mar99 		}
	}
	return(wasset);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlightModelFixedTime
//Author		R. Hyde 
//Date			Sun 7 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::FlightModelFixedTime(AirStrucPtr const ControlledAC2)
{
	UWord	loopcount;
	ANGLES	test;

//Old_Code RDH 21Oct96 	groundlevel = Land_Scape.GetGroundLevel(ControlledAC2);
	groundlevel = _Collide.LowestSafeAlt(ControlledAC2,
											ControlledAC2->pitch,
											ControlledAC2->roll);//RDH 21Oct96
//DeadCode RDH 25Nov96 //to allow for small changes in ground level add 2 cm
//DeadCode RDH 25Nov96 	groundlevel +=2;											//RDH 23Nov96

//to allow for small changes in ground level add 2 cm			//RDH 29Nov96
	groundlevel +=2;											//RDH 29Nov96

		ControlledAC2->fly.pModel->Base (ControlledAC2);							//ARM 07Jan97

//DeadCode RDH 07Oct96 	//groundlevel for manual pilot
//DeadCode RDH 07Oct96 	if (ControlledAC2 == ControlledAC)							//RDH 07Oct96
//DeadCode RDH 07Oct96 				 groundlevel_mp = groundlevel;					//RDH 07Oct96

//DeadCode RDH 26Mar98 	loopcount = (UWord) (Timer_Code.FRAMETIME+ cycletimeres);	//DAW 31Jul96

//DeadCode RDH 26Mar98 	cycletimeres = (UWord) (loopcount%FLIGHTMODEL_TIMEFRAME);


//DeadCode RDH 26Mar98 	loopcount = (UWord) (loopcount/FLIGHTMODEL_TIMEFRAME);
//need a test here for dead aircraft +++
//DeadCode RDH 26Mar98 	while (loopcount > 0)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 	  		SubManualPilot (ControlledAC2);
//DeadCode RDH 26Mar98 			loopcount--;
//DeadCode RDH 26Mar98 		}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Author		R. Hyde 
//Date		Wed 30 Aug 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::ACMManualPilot(AirStrucPtr const ControlledAC2)
{
	if (ControlledAC2)
	{
		keyboardcontrol = FALSE;
//DeadCode RDH 31Jul98   		ModifyControlInput (ControlledAC2);		//RDH 31Jul98

// All of the next bit is done in the flight model
//DeadCode CSB 15/09/98			if(!(ControlledAC2->fly.pModel->FrameCount & EVERY256cs))	//This will do the following commands for each aircraft
//DeadCode CSB 15/09/98			{											//once every n operations.
//DeadCode CSB 15/09/98				MMC.Sky.Ambient (ControlledAC2->fly.pModel->Pos.y, 
//DeadCode CSB 15/09/98				 				 ControlledAC2->fly.pModel->AmbDensity,
//DeadCode CSB 15/09/98								 ControlledAC2->fly.pModel->AmbTemp,
//DeadCode CSB 15/09/98								 ControlledAC2->fly.pModel->AmbPres);
//DeadCode CSB 15/09/98				ControlledAC->FuelLeft(CalcFuelRate(ControlledAC));	
//DeadCode CSB 15/09/98			}
//DeadCode CSB 15/09/98			ControlledAC2->fly.pModel->FrameCount++;
//DeadCode CSB 15/09/98		 	ControlledAC2->FuelLeft ();								//RDH 03Jun96

//DeadCode RDH 31Jul98  			ControlledAC2->ai.currentbuffet = 0;				//RDH 14Jun96
//DeadCode RDH 31Jul98  			ControlledAC2->ai.JinkTime = 0;						//RDH 14Jun96
		//Calculating the fuel used will now be done within the flight model	CSB
		FlightModelFixedTime(ControlledAC2);
		ControlledAC2->SetManualFlightParams ();				//DAW 04Jul96
 	}
}

//DeadCode RDH 31Jul98//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 31Jul98//Procedure		ModifyControlInput
//DeadCode RDH 31Jul98//Author		R. Hyde 
//DeadCode RDH 31Jul98//Date			Mon 1 Apr 1996
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//Description	The control input is modified by the velocity.
//DeadCode RDH 31Jul98//				In reality the pilot can feel more "pressure" on the stick
//DeadCode RDH 31Jul98//				at high velocity. At some stage the pilot is not strong enough
//DeadCode RDH 31Jul98//				to pull full deflection on the stick
//DeadCode RDH 31Jul98//				Also at high velocity, smaller stick deflection are required
//DeadCode RDH 31Jul98//				for the same effect
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//				We don't have feedback and so we have introduced this empirical
//DeadCode RDH 31Jul98//				routine.
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//				Similar effects at high g were tried but were not successful
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//Inputs		
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//Returns	
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//------------------------------------------------------------------------------
//DeadCode RDH 31Jul98void	ManualPilot::ModifyControlInput(AirStrucPtr const ControlledAC)
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98{
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98	SLong	elevator,aileron,rudder;
//DeadCode RDH 31Jul98	SWord	sinroll,cosroll;
//DeadCode RDH 31Jul98//Old_Code PD 24Jun96 	SWord	elevator_pos,elevator_sign,maxelevator_pos;
//DeadCode RDH 31Jul98	SWord	elevator_sign,maxelevator_pos;						//PD 24Jun96
//DeadCode RDH 31Jul98	UWord	elevator_pos;										//PD 24Jun96
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98	AircraftAnimData*	adptr;
//DeadCode RDH 31Jul98	adptr = (AircraftAnimData *)ControlledAC->Anim;
//DeadCode RDH 31Jul98 	ULong	damflagstate;										//RJS 29Oct96
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	ULong	*dflagptr;											//RJS 29Oct96
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	dflagptr = (ULong*) &(adptr->dammageflags);
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = (*dflagptr)>>BF_Pilot;						//RJS 29Oct96
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = damflagstate & BS_DEAD;
//DeadCode RDH 31Jul98	damflagstate = adptr->PILOTLEFT;								//RJS 21Feb97
//DeadCode RDH 31Jul98	if (damflagstate == BS_DEAD)								//RJS 21Feb97
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98//TempCode ARM 09Jan97 			ControlledAC->fly.elevator = 0;
//DeadCode RDH 31Jul98//TempCode ARM 09Jan97 			ControlledAC->fly.aileron = 0;
//DeadCode RDH 31Jul98//TempCode ARM 09Jan97 			ControlledAC->fly.rudder = 0;
//DeadCode RDH 31Jul98	}
//DeadCode RDH 31Jul98//these reductions in control are annoying in game play			//RDH 05Dec96
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 	}elseif ((damflagstate) != BS_ALIVE)
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 	{
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 			if (damflagstate > 2)
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 				damflagstate = 2;
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 			if (!(keyboardcontrol))
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 			{
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 				ControlledAC->fly.elevator = ControlledAC->fly.elevator * ((4- (SWord)damflagstate))/4;
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 				ControlledAC->fly.aileron = ControlledAC->fly.aileron * ((4 - (SWord)damflagstate))/4;
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 				ControlledAC->fly.rudder = ControlledAC->fly.rudder * ((4 - (SWord)damflagstate))/4;
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 			}
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 		
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 	}
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = (*dflagptr)>>BF_Engine;
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = damflagstate & BS_DEAD;
//DeadCode RDH 31Jul98	damflagstate = adptr->ENGINELEFTIN;								//RJS 21Feb97
//DeadCode RDH 31Jul98	if (damflagstate == BS_DEAD)								//RJS 21Feb97
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98			ControlledAC->fly.thrustpercent = 0;
//DeadCode RDH 31Jul98	}else
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98		// Scale to 80% max thrust loss....
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98		damflagstate *= 5;										//RJS 21Feb97
//DeadCode RDH 31Jul98		damflagstate >>= 4;										//RJS 21Feb97
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98		if (ControlledAC->fly.thrustpercent > (100 - damflagstate))//RJS 21Feb97
//DeadCode RDH 31Jul98		{
//DeadCode RDH 31Jul98			ControlledAC->fly.thrustpercent = 100 - damflagstate;//RJS 21Feb97
//DeadCode RDH 31Jul98		}
//DeadCode RDH 31Jul98	}
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = (*dflagptr)>>BF_Nose;						//RJS 31Oct96
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = damflagstate & BS_DEAD;
//DeadCode RDH 31Jul98	damflagstate = adptr->PROPLEFTIN;									//RJS 21Feb97
//DeadCode RDH 31Jul98	if (damflagstate == BS_DEAD)								//RJS 21Feb97
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98//TempCode ARM 09Jan97 			ControlledAC->fly.thrustpercent = 0;
//DeadCode RDH 31Jul98	}else
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98		// Scale to 50% max thrust loss....
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98		damflagstate *= 3;										//RJS 21Feb97
//DeadCode RDH 31Jul98		damflagstate /= 15;										//RJS 21Feb97
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98		if (ControlledAC->fly.thrustpercent > (100 - damflagstate))//RJS 21Feb97
//DeadCode RDH 31Jul98		{
//DeadCode RDH 31Jul98			ControlledAC->fly.thrustpercent = 100 - damflagstate;//RJS 21Feb97
//DeadCode RDH 31Jul98		}
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98	}
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Author		R. Hyde 
//Date		Wed 30 Aug 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::SubManualPilot(AirStrucPtr const ControlledAC)
{
//DeadCode RDH 26Mar98     	ControlledAC->fly.cposy = -ControlledAC->World.Y;			//RDH 28Feb96
    
//DeadCode RDH 26Mar98     	MachDensity (ControlledAC);
//DeadCode RDH 26Mar98    //TempCode RDH 26Oct95 	classtype->ModelPatch_Thrust ();
//DeadCode RDH 26Mar98     	WW2Thrust(ControlledAC);
//DeadCode RDH 26Mar98     	CalcLift (ControlledAC);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		AircraftAnimData*	adptr;
//DeadCode RDH 26Mar98 		adptr = (AircraftAnimData *)ControlledAC->Anim;
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 		UWord	lcldamflag;
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 		lcldamflag = adptr->dammageflags;
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 		if (((lcldamflag>>BF_Tail) & BS_DEAD) != BS_DEAD)
//DeadCode RDH 26Mar98 		if (adptr->TAIL != BS_DEAD)								//RJS 21Feb97
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 	    	CalcTailLift (ControlledAC);
//DeadCode RDH 26Mar98     		CalcTailDrag (ControlledAC);
//DeadCode RDH 26Mar98 	    	CalcRudderLift (ControlledAC);
//DeadCode RDH 26Mar98 	    	CalcRudderDrag (ControlledAC);
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98     	CalcSideForce (ControlledAC);
//DeadCode RDH 26Mar98     	CalcDrag (ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96    		if (keyboardcontrol)
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96    		{
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96    	 		CalcTrim (ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96    		}else
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 			trim =0;
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 		}
//DeadCode RDH 26Mar98    		if (keyboardcontrol)
//DeadCode RDH 26Mar98    		{
//DeadCode RDH 26Mar98    	 		CalcTrim (ControlledAC);
//DeadCode RDH 26Mar98    		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			trim =0;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 //TempCode ARM 09Jan97     	CalcRotas (ControlledAC);
//DeadCode RDH 26Mar98 //TempCode ARM 07Jan97     	CalcDeltas (ControlledAC);	// does angles
//DeadCode RDH 26Mar98 //TempCode ARM 09Jan97     	CalcVel (ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode DAW 06Jun96 		ControlledAC->fly.acroll = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //DeadCode DAW 06Jun96 		ControlledAC->fly.croll = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //TempCode ARM 07Jan97     	VcoAlfaBeta (ControlledAC);	// does velx,y,z
//DeadCode RDH 26Mar98 //TempCode ARM 07Jan97     	DataTrans (ControlledAC);	// vely & roll only
//DeadCode RDH 26Mar98 //TempCode ARM 07Jan97     	CalcPosition (ControlledAC); // does position
//DeadCode RDH 26Mar98    //**  	SetFlags (ControlledAC);

//DeadCode RDH 26Mar98 		ControlledAC->fly.pModel->Base ();							//ARM 07Jan97

//TempCode ARM 27Aug97 		ANGLES a,b;
//TempCode ARM 27Aug97 		ControlledAC->fly.pModel->HaveWeLanded (ControlledAC, a,b);

}


//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Thu 24 Aug 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	Description:   calculates Mach and airdensity at altitude of currac
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			    
//DeadCode RDH 26Mar98 //	SoS, m/s    = d1 +(altitude_cm - altitude_1000m*100000) * (d2-d1) /100000 
//DeadCode RDH 26Mar98 //	                  
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	AirDensity, g/m^3 = d1 +(altitude_cm - altitude_1000m*100000) * (d2-d1) /100000 
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	indicated airspeed, cm/s = SQR(DensityRatio) * True speed/65535                   
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::MachDensity(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong		altitude_cm;
//DeadCode RDH 26Mar98 	UWord		d1,d2,altitude_1000m,densityratio;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	altitude_cm = ControlledAC->World.Y;
//DeadCode RDH 26Mar98 	if (altitude_cm < 0)
//DeadCode RDH 26Mar98 		altitude_cm = 0;
//DeadCode RDH 26Mar98 	if (altitude_cm >MAXALTITUDE_CM)
//DeadCode RDH 26Mar98 		altitude_cm = MAXALTITUDE_CM;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	altitude_1000m =	(UWord) (altitude_cm/100000);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	d1 =	machdata[altitude_1000m];
//DeadCode RDH 26Mar98 	d2 =	machdata[altitude_1000m+1];
//DeadCode RDH 26Mar98 	sos = (SWord) (d1+ (d2-d1) * (altitude_cm - altitude_1000m*100000)/100000);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	d1 =	airdensitydata[altitude_1000m];
//DeadCode RDH 26Mar98 	d2 =	airdensitydata[altitude_1000m+1];
//DeadCode RDH 26Mar98 	airdensity  = (SWord) (d1+ (d2-d1) * (altitude_cm - altitude_1000m*100000)/100000);
//DeadCode RDH 26Mar98 	dynamicpressure =  (ControlledAC->vel * ControlledAC->vel)/100;
//DeadCode RDH 26Mar98 	dynamicpressure = dynamicpressure * airdensity/2000;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 	d1 =	airdensityratiosquareroot[altitude_1000m];
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 	d2 =	airdensityratiosquareroot[altitude_1000m+1];
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 	densityratio = (UWord) (d1+ (d2-d1) * (altitude_cm - altitude_1000m*100000)/100000); 
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 	View_Point.i_a_s = (SWord) ((SLong) ControlledAC->vel * densityratio /WORD_FRACT);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		WW2Thrust
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 27 Oct 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 // 			max thrust = f (vel, height)
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::WW2Thrust (AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 //DeadCode RDH 24May96 	SLong	maxrpm;
//DeadCode RDH 26Mar98 	SLong 	altfactor;
//DeadCode RDH 26Mar98 	SLong	d1,d2,vel_10m_s;
//DeadCode RDH 26Mar98 	SWord	thrustpercent;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	vel_10m_s = ControlledAC->vel/100;
//DeadCode RDH 26Mar98 	if (vel_10m_s > 9)
//DeadCode RDH 26Mar98 		vel_10m_s = 9;
//DeadCode RDH 26Mar98 	if (vel_10m_s < 0)
//DeadCode RDH 26Mar98 		vel_10m_s = 0;
//DeadCode RDH 26Mar98 	d1 = ControlledAC->classtype->thrustcurve[vel_10m_s];
//DeadCode RDH 26Mar98 	d2 = ControlledAC->classtype->thrustcurve[vel_10m_s + 1];
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	thrust = d1+ (d2-d1) * (ControlledAC->vel - vel_10m_s * 100)/100;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	thrustpercent =	ControlledAC->fly.thrustpercent;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if	(Save_Data.flightdifficulty [FD_POWERBOOST])
//DeadCode RDH 26Mar98 			thrustpercent = thrustpercent * 2;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (	(thrustpercent > 10)
//DeadCode RDH 26Mar98 			&&	(ControlledAC->ai.manoeuvre==MANOEUVRE_TURNINGFIGHT)//RDH 18Nov96
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 			thrustpercent = thrustpercent + ControlledAC->ai.skill * 3;		//give good ai pilots an advantage
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	thrust = thrust * thrustpercent / 100;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	altfactor = 1176 * airdensity  / airdensitydata[0] - 176;
//DeadCode RDH 26Mar98 	thrust = thrust * altfactor / 1000;
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcK2
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 20 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	See CalcTailLift
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 SWord	ManualPilot::CalcK2(AirStrucPtr const ControlledAC,SWord elevator)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	deflection,d2,d1,k2;	
//DeadCode RDH 26Mar98 	UWord	elevator_pos;
//DeadCode RDH 26Mar98 	SWord	elevator_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (elevator,elevator_pos,elevator_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (elevator <0)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		deflection = (45 * elevator_pos) / (MAXELEVATOR);
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		deflection = (17 * elevator_pos) / (MAXELEVATOR);
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96  	if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96  	{
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	 	deflection = (deflection * elevator_pos) / (MAXELEVATOR);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96  		deflection = (deflection * elevator_pos) / (MAXELEVATOR);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	}	
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	d1 = elevatordeflectiondata[(deflection / 5)];
//DeadCode RDH 26Mar98 	d2 = elevatordeflectiondata[(deflection / 5) + 1];
//DeadCode RDH 26Mar98 	k2 = (SWord) (d1+ ((d2-d1) * (deflection - (deflection / 5)* 5) ) /5);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (elevator_sign == MathLib::NEGATIVE)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		k2 = -k2;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	//to impose tail heaviness									//RDH 11Dec96
//DeadCode RDH 26Mar98 	k2 = k2 - 8;												//RDH 12Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	return ((SWord) k2);	
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcK2Rudder
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 20 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 SWord	ManualPilot::CalcK2Rudder(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	deflection,d2,d1,k2;	
//DeadCode RDH 26Mar98 	UWord	rudder_pos;
//DeadCode RDH 26Mar98 	SWord	rudder_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (ControlledAC->fly.rudder,rudder_pos,rudder_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 07Jun96 	deflection = (45 * rudder_pos) / (MAXRUDDER);
//DeadCode RDH 26Mar98 	deflection = (45 * rudder_pos) / (MAXRUDDER);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96  	if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96  	{
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96  	deflection = (deflection * rudder_pos) / (MAXRUDDER);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	deflection = (deflection * rudder_pos) / (MAXRUDDER);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	}	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	d1 = elevatordeflectiondata[(deflection / 5)];
//DeadCode RDH 26Mar98 	d2 = elevatordeflectiondata[(deflection / 5) + 1];
//DeadCode RDH 26Mar98 	k2 = (SWord) (d1+ ((d2-d1) * (deflection - (deflection / 5)* 5) ) /5);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (rudder_sign == MathLib::NEGATIVE)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		k2 = -k2;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	return ((SWord) k2);	
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Thu 24 Aug 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	Theory of Flight pp502-504
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			lift = dynamic press . tailarea . (k1 . AoA + k2 + k3)
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			k1. AoA = 	2.Pi.AoA	AR - 2	 ie taileffect * wingeffect 
//DeadCode RDH 26Mar98 //						-----    .  ------
//DeadCode RDH 26Mar98 //						1 + 2/AR'	AR + 2
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			k2 = f(deflection) see fig 352
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			k3 constant associated with incidence difference (called const in ToF)
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			k3 = -2.Pi. (wing -tail incidence)  *   1
//DeadCode RDH 26Mar98 //												-----    
//DeadCode RDH 26Mar98 //												1 + 2/AR'
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			cl_tail = k1. AoA + k2
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //			max taileffect is +/- 1.4
//DeadCode RDH 26Mar98 //			above 10deg AoA need another function for taileffect
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			For Aspect ratio we use span^2 / area
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcTailLift(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	cl_tail;
//DeadCode RDH 26Mar98 	SWord	aoa;
//DeadCode RDH 26Mar98 	cl_tail = CalcTailLiftSub (ControlledAC,ControlledAC->fly.elevator,aoa);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	Math_Lib.high_sin_cos(ControlledAC->fly.slip,sinslip,cosslip); 
//DeadCode RDH 26Mar98 	SLong dp = ControlledAC->vel;		// * cosslip/ ANGLES_FRACT;//RDH 03Jul96
//DeadCode RDH 26Mar98 	if (	(dp <MPH40)
//DeadCode RDH 26Mar98 		&&	(ControlledAC->World.Y > groundlevel)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 		dp = MPH40;
//DeadCode RDH 26Mar98 	dp =  MULDIVSIN(dp,dp,100);
//DeadCode RDH 26Mar98 	dp = dp * airdensity/2000;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	taillift = dp * ControlledAC->classtype->tailarea/10000;
//DeadCode RDH 26Mar98 	taillift = taillift * ControlledAC->classtype->tailliftmodifier/100;
//DeadCode RDH 26Mar98 //DeadCode RDH 10Jul96 //going down
//DeadCode RDH 26Mar98 //DeadCode RDH 10Jul96 	if (ControlledAC->fly.elevator > 0)
//DeadCode RDH 26Mar98 //DeadCode RDH 10Jul96 		taillift = taillift/4;
//DeadCode RDH 26Mar98 	taillift = taillift * cl_tail /100;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcTailLiftSub
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Tue 16 Apr 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	cl_tail
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 SLong	ManualPilot::CalcTailLiftSub (AirStrucPtr const ControlledAC,SWord elevator,SWord aoa)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SLong	k2,k3,taileffect,wingeffect,cl_tail;
//DeadCode RDH 26Mar98 	UWord	aoa_pos;
//DeadCode RDH 26Mar98 	SWord	aoa_sign,cl_tail_tmp;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98     k2 =	(SLong) CalcK2 (ControlledAC,elevator);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	wingeffect = 100 * (ControlledAC->classtype->wing_ar - 20)
//DeadCode RDH 26Mar98 					/ (ControlledAC->classtype->wing_ar + 20);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	vel_from_pitch = (ControlledAC->classtype->lt * ControlledAC->fly.pitchrate)/
//DeadCode RDH 26Mar98 							(ROWANS_PER_RAD);
//DeadCode RDH 26Mar98 	if (ControlledAC->fly.vel_cms <1)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa_from_pitch =	 vel_from_pitch * ROWANS_PER_RAD;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa_from_pitch =	 MULDIVSIN (vel_from_pitch,ROWANS_PER_RAD,ControlledAC->fly.vel_cms);
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ((ControlledAC->fly.aoa > ANGLES_90Deg)
//DeadCode RDH 26Mar98 		|| (ControlledAC->fly.aoa < ANGLES_270Deg))				//RDH 24Jul96
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	aoa = ANGLES_180Deg - ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	aoa =  ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98    	if (ControlledAC->fly.rotr_xbl < 0)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98   		aoa = aoa + aoa_from_pitch;
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98 	 	aoa = aoa + aoa_from_pitch/2;
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //16 * 4096 = 65536 which is needed to convert AoA to radians	
//DeadCode RDH 26Mar98 	taileffect = aoa;
//DeadCode RDH 26Mar98 	taileffect = taileffect * (TWOPI100 * TWOPI100 / 16) / 4096;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	taileffect = taileffect/ (100 + 2000 / ControlledAC->classtype->tail_ar);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	cl_tail = (wingeffect * (k2 + taileffect)) / 100;
//DeadCode RDH 26Mar98 	k3	=	 ControlledAC->classtype->wing_incidence - ControlledAC->classtype->tail_incidence;
//DeadCode RDH 26Mar98 	k3	=	k3  * (TWOPI100 * TWOPI100 / 16) / 4096;
//DeadCode RDH 26Mar98 	k3 = k3/ (100 + 2000 / ControlledAC->classtype->tail_ar);
//DeadCode RDH 26Mar98 	cl_tail = cl_tail - k3;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (aoa,aoa_pos,aoa_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	if (aoa_sign == MathLib::POSITIVE)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98 		if (aoa_pos > ANGLES_90Deg)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			aoa_pos = ANGLES_180Deg -aoa_pos;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		if (aoa_pos > ANGLES_30Deg)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			cl_tail_tmp = 80 - 80 * (aoa_pos - ANGLES_30Deg)/
//DeadCode RDH 26Mar98  										ANGLES_60Deg;
//DeadCode RDH 26Mar98 			if (cl_tail > cl_tail_tmp)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				cl_tail = cl_tail_tmp;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}elseif (aoa_pos > ANGLES_10Deg)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			taileffect = (SWord) ANGLES_10Deg;
//DeadCode RDH 26Mar98 			taileffect = taileffect * (TWOPI100 * TWOPI100 / 16) / 4096;
//DeadCode RDH 26Mar98 			taileffect = taileffect/ (100 + 2000 / ControlledAC->classtype->tail_ar);
//DeadCode RDH 26Mar98 			cl_tail_tmp = -k3 + (wingeffect * (k2 + taileffect)) / 100;
//DeadCode RDH 26Mar98 			//reduce cl_tail_tmp at 10deg to .8 wrt to aoa_pos
//DeadCode RDH 26Mar98 			cl_tail_tmp =  cl_tail_tmp - (cl_tail_tmp - 80) * (aoa_pos - ANGLES_10Deg) /
//DeadCode RDH 26Mar98 											ANGLES_20Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (cl_tail > cl_tail_tmp)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				cl_tail = cl_tail_tmp;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		if (aoa < - (SWord) ANGLES_90Deg)
//DeadCode RDH 26Mar98  		{
//DeadCode RDH 26Mar98  			aoa = - (SWord) ANGLES_180Deg - aoa;
//DeadCode RDH 26Mar98  		}
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  		if (aoa < - (SWord) ANGLES_30Deg)
//DeadCode RDH 26Mar98  		{
//DeadCode RDH 26Mar98   		cl_tail = -80 +  80 * ( aoa + (SWord) ANGLES_30Deg)/
//DeadCode RDH 26Mar98   										ANGLES_60Deg;
//DeadCode RDH 26Mar98  		}elseif (aoa < - (SWord) ANGLES_10Deg)
//DeadCode RDH 26Mar98  		{
//DeadCode RDH 26Mar98  			taileffect = (SWord)(0 - ANGLES_10Deg);
//DeadCode RDH 26Mar98  			taileffect = taileffect * (TWOPI100 * TWOPI100 / 16) / 4096;
//DeadCode RDH 26Mar98  			taileffect = taileffect/ (100 + 2000 / ControlledAC->classtype->tail_ar);
//DeadCode RDH 26Mar98  			cl_tail = -k3 + (wingeffect * (k2 + taileffect)) / 100;
//DeadCode RDH 26Mar98  			//reduce cl_tail at 10deg to .5 wrt to aoa
//DeadCode RDH 26Mar98  			cl_tail =  cl_tail + (cl_tail - -80) * (aoa + (SWord) ANGLES_10Deg) /
//DeadCode RDH 26Mar98  											ANGLES_20Deg;
//DeadCode RDH 26Mar98  		}
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98 	if (cl_tail >140)
//DeadCode RDH 26Mar98 		cl_tail = 140;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	if (cl_tail <-140)
//DeadCode RDH 26Mar98  		cl_tail = -140;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	return (cl_tail);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcTailDrag
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Sun 23 Jun 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcTailDrag(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	aoa;
//DeadCode RDH 26Mar98    	if (ControlledAC->fly.rotr_xbl < 0)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98   		aoa = aoa + aoa_from_pitch;
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98 	 	aoa = aoa + aoa_from_pitch/2;
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98 //DeadCode RDH 06Aug96  	aoa =  ControlledAC->fly.aoa + aoa_from_pitch;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	taildrag  =	CalcDragSub(ControlledAC,aoa,ControlledAC->fly.vel_cms);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	taildrag = MULDIVSIN (taildrag,ControlledAC->classtype->tailarea,1000);
//DeadCode RDH 26Mar98 	taildrag = taildrag/ControlledAC->classtype->wingarea;
//DeadCode RDH 26Mar98 	taildrag = taildrag * ControlledAC->classtype->taildragmodifier/100;
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcRudderDrag
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Sun 23 Jun 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcRudderDrag(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	aoa;
//DeadCode RDH 26Mar98  	aoa =  ControlledAC->fly.slip - aoa_from_turn;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	rudderdrag  =	CalcDragSub(ControlledAC,aoa,ControlledAC->fly.vel_cms);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	rudderdrag = MULDIVSIN (rudderdrag,ControlledAC->classtype->finarea,1000);
//DeadCode RDH 26Mar98 	rudderdrag = rudderdrag/ControlledAC->classtype->wingarea;
//DeadCode RDH 26Mar98 	rudderdrag = rudderdrag * ControlledAC->classtype->rudderdragmodifier/100;
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Thu 24 Aug 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	Theory of Flight pp502-504
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			lift = dynamic press . rudderarea . (k1 . AoA + k2)
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			k1. AoA = 	2.Pi.AoA
//DeadCode RDH 26Mar98 //						-----   
//DeadCode RDH 26Mar98 //						1 + 2/AR'
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			k2 = f(deflection) see fig 352
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			cl_tail = k1. AoA + k2
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //			max ruddereffect is +/- 1.4
//DeadCode RDH 26Mar98 //			above 10deg AoA need another function for taileffect
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			For Aspect ratio we use span^2 / area
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcRudderLift(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	k2,k3,ruddereffect,cl_rudder,k2_factor;
//DeadCode RDH 26Mar98 	SWord	slip_sign,vel,sinslip,cosslip;
//DeadCode RDH 26Mar98 	SLong	aoa_from_slipstream;
//DeadCode RDH 26Mar98 	UWord	slip_pos;
//DeadCode RDH 26Mar98 	SWord	cl_rudder_tmp,slip;
//DeadCode RDH 26Mar98   	UWord	aoa_from_turn_pos;
//DeadCode RDH 26Mar98   	SWord	aoa_from_turn_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98     k2 =	(SLong) CalcK2Rudder (ControlledAC);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	vel_from_turn = (ControlledAC->classtype->lt * ControlledAC->fly.yawrate)/
//DeadCode RDH 26Mar98 							(ROWANS_PER_RAD);
//DeadCode RDH 26Mar98 	if (ControlledAC->fly.vel_cms <1)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa_from_turn =	 vel_from_turn * ROWANS_PER_RAD;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa_from_turn =	 MULDIVSIN (vel_from_turn,ROWANS_PER_RAD,ControlledAC->fly.vel_cms);
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ((ControlledAC->fly.slip > ANGLES_90Deg)
//DeadCode RDH 26Mar98 		|| (ControlledAC->fly.slip < ANGLES_270Deg))			//RDH 24Jul96
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	slip = ANGLES_180Deg - ControlledAC->fly.slip;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	slip =  ControlledAC->fly.slip;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 06Aug96 	if ((ControlledAC->fly.acroll > ANGLES_90Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 06Aug96 		|| (ControlledAC->fly.acroll < ANGLES_270Deg))			//RDH 24Jul96
//DeadCode RDH 26Mar98 //DeadCode RDH 06Aug96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 06Aug96 			aoa_from_turn =	-aoa_from_turn;
//DeadCode RDH 26Mar98 //DeadCode RDH 06Aug96 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	Math_Lib.Pos ((SWord) aoa_from_turn,aoa_from_turn_pos,aoa_from_turn_sign);
//DeadCode RDH 26Mar98   
//DeadCode RDH 26Mar98  	if (aoa_from_turn_pos > ANGLES_3Deg)
//DeadCode RDH 26Mar98   	{
//DeadCode RDH 26Mar98   		aoa_from_turn_pos = (ANGLES_2Deg + ANGLES_HalfDeg/2)
//DeadCode RDH 26Mar98   								+ aoa_from_turn_pos/4;
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98   	if (aoa_from_turn_pos > ANGLES_10Deg)
//DeadCode RDH 26Mar98   		aoa_from_turn_pos = ANGLES_10Deg;
//DeadCode RDH 26Mar98   	aoa_from_turn = Math_Lib.UseSign (aoa_from_turn_pos,aoa_from_turn_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	totalslip = slip - aoa_from_turn;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ((Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS])		//RDH 03Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 	if ((Save_Data.flightdifficulty [FD_TORQUEEFFECTS])
//DeadCode RDH 26Mar98 		&&  (ControlledAC2 == ControlledAC))
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (ControlledAC->fly.vel_cms < VEL_MAXSLIPSTREAM)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			vel = VEL_MAXSLIPSTREAM;
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			vel = ControlledAC->fly.vel_cms;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 		aoa_from_slipstream = VEL_MAXSLIPSTREAM * thrust * (ControlledAC->fly.vel_cms /100)
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 										   / vel;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 	
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96  		aoa_from_slipstream = aoa_from_slipstream * VEL_MAXSLIPSTREAM /
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96  											 vel;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 		aoa_from_slipstream = AOA_MAXSLIPSTREAM * aoa_from_slipstream / POWER_MAXSLIPSTREAM;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		aoa_from_slipstream = VEL_MAXSLIPSTREAM * ControlledAC->fly.thrustpercent / vel;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 		aoa_from_slipstream = AOA_MAXSLIPSTREAM * aoa_from_slipstream / POWER_MAXSLIPSTREAM;
//DeadCode RDH 26Mar98  		aoa_from_slipstream = aoa_from_slipstream * VEL_MAXSLIPSTREAM / vel;
//DeadCode RDH 26Mar98  		aoa_from_slipstream = aoa_from_slipstream * VEL_MAXSLIPSTREAM / vel;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 		//16 * 4096 = 65536 which is needed to convert slip to radians	
//DeadCode RDH 26Mar98 	 	totalslip -= (SWord) aoa_from_slipstream * ControlledAC->classtype->rotdirection;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 				
//DeadCode RDH 26Mar98 	//16 * 4096 = 65536 which is needed to convert slip to radians	
//DeadCode RDH 26Mar98 	ruddereffect = totalslip * (TWOPI100 * TWOPI100 / 16) / 4096;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ruddereffect = ruddereffect/ (100 + 2000 / ControlledAC->classtype->tail_ar);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	cl_rudder = k2 + ruddereffect;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (totalslip,slip_pos,slip_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (slip_sign == MathLib::POSITIVE)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (slip_pos > ANGLES_90Deg)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			slip_pos = ANGLES_180Deg -slip_pos;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	 	Math_Lib.high_sin_cos((Angles)slip_pos,sinslip,cosslip); 
//DeadCode RDH 26Mar98 		k2_factor = 40 + k2/4;
//DeadCode RDH 26Mar98 		if (slip_pos > ANGLES_30Deg)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			cl_rudder_tmp = k2_factor - k2_factor * (slip_pos - ANGLES_30Deg)/
//DeadCode RDH 26Mar98  										ANGLES_60Deg;
//DeadCode RDH 26Mar98 			if (cl_rudder > cl_rudder_tmp)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				cl_rudder = cl_rudder_tmp;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}elseif (slip_pos > ANGLES_10Deg)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			ruddereffect = (SWord) ANGLES_10Deg;
//DeadCode RDH 26Mar98 			ruddereffect = ruddereffect * (TWOPI100 * TWOPI100 / 16) / 4096;
//DeadCode RDH 26Mar98 			ruddereffect = ruddereffect/ (100 + 2000 / ControlledAC->classtype->tail_ar);
//DeadCode RDH 26Mar98 			cl_rudder_tmp = ruddereffect;
//DeadCode RDH 26Mar98 			//reduce cl_rudder at 10deg to .5 wrt to slip
//DeadCode RDH 26Mar98 			cl_rudder_tmp =  cl_rudder_tmp - (cl_rudder_tmp - k2_factor) * (totalslip - ANGLES_10Deg) /
//DeadCode RDH 26Mar98 											ANGLES_20Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			if (cl_rudder > cl_rudder_tmp)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				cl_rudder = cl_rudder_tmp;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98  		if (totalslip < - (SWord) ANGLES_90Deg)
//DeadCode RDH 26Mar98  		{
//DeadCode RDH 26Mar98  			totalslip = - (SWord) ANGLES_180Deg - totalslip;
//DeadCode RDH 26Mar98  		}
//DeadCode RDH 26Mar98 	 	Math_Lib.high_sin_cos((Angles)totalslip,sinslip,cosslip); 
//DeadCode RDH 26Mar98 		k2_factor = 40 + k2/4;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  		if (totalslip < - (SWord) ANGLES_30Deg)
//DeadCode RDH 26Mar98  		{
//DeadCode RDH 26Mar98   		cl_rudder_tmp = -k2_factor +  k2_factor * (totalslip + (SWord) ANGLES_30Deg)/
//DeadCode RDH 26Mar98   										ANGLES_60Deg;
//DeadCode RDH 26Mar98 			if (cl_rudder < cl_rudder_tmp)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				cl_rudder = cl_rudder_tmp;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98  		}elseif (totalslip < - (SWord) ANGLES_10Deg)
//DeadCode RDH 26Mar98  		
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			ruddereffect = (SWord) ANGLES_350Deg;
//DeadCode RDH 26Mar98 			ruddereffect = ruddereffect * (TWOPI100 * TWOPI100 / 16) / 4096;
//DeadCode RDH 26Mar98 			ruddereffect = ruddereffect/ (100 + 2000 / ControlledAC->classtype->tail_ar);
//DeadCode RDH 26Mar98 			cl_rudder_tmp = ruddereffect;
//DeadCode RDH 26Mar98 			//reduce cl_rudder at 10deg to .5 wrt to slip
//DeadCode RDH 26Mar98 			cl_rudder_tmp =  cl_rudder_tmp + (cl_rudder - -k2_factor) * ((SWord)totalslip - (SWord) ANGLES_350Deg) /
//DeadCode RDH 26Mar98 											ANGLES_20Deg;
//DeadCode RDH 26Mar98 			if (cl_rudder > cl_rudder_tmp)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				cl_rudder = cl_rudder_tmp;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if (cl_rudder >140)
//DeadCode RDH 26Mar98 		cl_rudder = 140;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (cl_rudder <-140)
//DeadCode RDH 26Mar98 		cl_rudder = -140;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	rudderlift = dynamicpressure * ControlledAC->classtype->finarea/10000;
//DeadCode RDH 26Mar98 	rudderlift = rudderlift * cl_rudder /100;
//DeadCode RDH 26Mar98 	rudderlift = rudderlift * ControlledAC->classtype->rudderliftmodifier/100;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	UWord	rudderlift_pos;
//DeadCode RDH 26Mar98 	rudderlift_pos = rudderlift;
//DeadCode RDH 26Mar98 	if (rudderlift < 0)
//DeadCode RDH 26Mar98 		rudderlift_pos = -rudderlift;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	rudderlift -= rudderlift_pos * ControlledAC->fly.yawrate /ANGLES_90Deg;
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcSideForce
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 22 Mar 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	Theory of FLight p537
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //				side force = wingarea*dynamicpressure * 0.4 *(2*Pi*slip/65535)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //				0.4*2*Pi/65535 = 0.0000383 = 1/26075
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcSideForce(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	UWord	slip_pos;
//DeadCode RDH 26Mar98 	SWord	slip_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (totalslip,slip_pos,slip_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (slip_pos >ANGLES_18Deg)
//DeadCode RDH 26Mar98 			slip_pos = ANGLES_18Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	slip_sign = Math_Lib.UseSign (slip_pos,slip_sign);		
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	sideforce = slip_sign * ControlledAC->classtype->wingarea/10;
//DeadCode RDH 26Mar98 	sideforce = - MULDIVSIN (sideforce,dynamicpressure,26075);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Thu 24 Aug 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //	CL calculation  (in 100 u)
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	see p386 of Theory of Flight
//DeadCode RDH 26Mar98 //	lift curve can be made up of up to five straight lines, minimum is 2
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		classtype->stallangle is stall angle
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		general equation, L = 0.5 * CL * v * v *rho *wingarea
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			L in Newtons
//DeadCode RDH 26Mar98 //			v in m/s
//DeadCode RDH 26Mar98 //			rho in kg/m^3
//DeadCode RDH 26Mar98 //			wingarea in m^2
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	 Calculates WingLift (in N)
//DeadCode RDH 26Mar98 //	  Lift = CL * (v * v /10000) * rho /1000 * Wing /200
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcLift(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	aoa_corr;										//RDH 12Dec96
//DeadCode RDH 26Mar98 	SWord	aoa,slip,vel;
//DeadCode RDH 26Mar98 	SLong	innerrightwinglift,innerleftwinglift;
//DeadCode RDH 26Mar98 	SLong	temprightwinglift,templeftwinglift;
//DeadCode RDH 26Mar98 	SWord	aileron_sign;
//DeadCode RDH 26Mar98 	UWord	aileron_pos,maxaileron_pos;
//DeadCode RDH 26Mar98 	SLong	aoa_from_roll_right,aoa_from_roll_left;
//DeadCode RDH 26Mar98 	SWord	aoa_correction;
//DeadCode RDH 26Mar98 	SWord	cosaoa,sinaoa;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //velocity on wings  =  f(yaw)
//DeadCode RDH 26Mar98 //	use wingspan/4
//DeadCode RDH 26Mar98 //		delta vel = yawrate * wingspan  /4
//DeadCode RDH 26Mar98 //			m/s		rads		m
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		delta vel = 10 * yawrate * wingspan  /400
//DeadCode RDH 26Mar98 //			10cm/s					cm
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	vel_from_yaw = (ControlledAC->classtype->wingspan *	 ControlledAC->fly.yawrate)/
//DeadCode RDH 26Mar98 							(4 * ROWANS_PER_RAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 01Jul96  	UWord	vel_from_yaw_pos;
//DeadCode RDH 26Mar98 //DeadCode RDH 01Jul96  	SWord	vel_from_yaw_sign;
//DeadCode RDH 26Mar98 //DeadCode RDH 01Jul96  	Math_Lib.Pos ((SWord) vel_from_yaw,vel_from_yaw_pos,vel_from_yaw_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 01Jul96 
//DeadCode RDH 26Mar98 //DeadCode RDH 01Jul96 
//DeadCode RDH 26Mar98 //TempCode RDH 29Jun96 	if (vel_from_yaw_pos > ControlledAC->fly.vel_cms/16)
//DeadCode RDH 26Mar98 //TempCode RDH 29Jun96 	{
//DeadCode RDH 26Mar98 //TempCode RDH 29Jun96 		vel_from_yaw_pos = ControlledAC->fly.vel_cms/16;
//DeadCode RDH 26Mar98 //TempCode RDH 29Jun96 	}	
//DeadCode RDH 26Mar98 //DeadCode RDH 01Jul96  	vel_from_yaw = Math_Lib.UseSign (vel_from_yaw_pos,vel_from_yaw_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	vel_from_roll = (ControlledAC->classtype->wingspan * ControlledAC->fly.rollrate)/
//DeadCode RDH 26Mar98 							(4 * ROWANS_PER_RAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.high_sin_cos(ControlledAC->fly.aoa,sinaoa,cosaoa); 
//DeadCode RDH 26Mar98 	hori_vel_right = vel_from_yaw * cosaoa/ANGLES_FRACT - vel_from_roll * sinaoa/ANGLES_FRACT;
//DeadCode RDH 26Mar98 	vert_vel_right = vel_from_yaw * sinaoa/ANGLES_FRACT + vel_from_roll * cosaoa/ANGLES_FRACT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	hori_vel_left = vel_from_yaw * cosaoa/ANGLES_FRACT - vel_from_roll * sinaoa/ANGLES_FRACT;
//DeadCode RDH 26Mar98 	vert_vel_left = vel_from_yaw * sinaoa/ANGLES_FRACT + vel_from_roll * cosaoa/ANGLES_FRACT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ((ControlledAC->fly.vel_cms - hori_vel_right) <1)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa_from_roll_right =	 vert_vel_right * ROWANS_PER_RAD;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa_from_roll_right =	 MULDIVSIN (vert_vel_right,ROWANS_PER_RAD,(ControlledAC->fly.vel_cms - hori_vel_right));
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if ((ControlledAC->fly.vel_cms + hori_vel_left) <1)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa_from_roll_left  =	 vert_vel_left * ROWANS_PER_RAD;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa_from_roll_left =	 MULDIVSIN (vert_vel_left,ROWANS_PER_RAD,(ControlledAC->fly.vel_cms + hori_vel_left));
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	UWord	aoa_from_roll_pos;
//DeadCode RDH 26Mar98   	SWord	aoa_from_roll_sign;
//DeadCode RDH 26Mar98   	Math_Lib.Pos ((SWord) aoa_from_roll_right,aoa_from_roll_pos,aoa_from_roll_sign);
//DeadCode RDH 26Mar98   
//DeadCode RDH 26Mar98  	if (aoa_from_roll_pos > ANGLES_3Deg)
//DeadCode RDH 26Mar98   	{
//DeadCode RDH 26Mar98   		aoa_from_roll_pos = (ANGLES_2Deg + ANGLES_HalfDeg/2)
//DeadCode RDH 26Mar98   								+ aoa_from_roll_pos/4;
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98   	if (aoa_from_roll_pos > ANGLES_10Deg)
//DeadCode RDH 26Mar98   		aoa_from_roll_pos = ANGLES_10Deg;
//DeadCode RDH 26Mar98   	aoa_from_roll_right = Math_Lib.UseSign (aoa_from_roll_pos,aoa_from_roll_sign);
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98   	Math_Lib.Pos ((SWord) aoa_from_roll_left,aoa_from_roll_pos,aoa_from_roll_sign);
//DeadCode RDH 26Mar98   
//DeadCode RDH 26Mar98  	if (aoa_from_roll_pos > ANGLES_3Deg)
//DeadCode RDH 26Mar98   	{
//DeadCode RDH 26Mar98   		aoa_from_roll_pos = (ANGLES_2Deg + ANGLES_HalfDeg/2)
//DeadCode RDH 26Mar98   								+ aoa_from_roll_pos/4;
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98   	if (aoa_from_roll_pos > ANGLES_10Deg)
//DeadCode RDH 26Mar98   		aoa_from_roll_pos = ANGLES_10Deg;
//DeadCode RDH 26Mar98   	aoa_from_roll_left = Math_Lib.UseSign (aoa_from_roll_pos,aoa_from_roll_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	slip = (SWord) ControlledAC->fly.slip;
//DeadCode RDH 26Mar98 	aoa_from_dihedral = MULDIVSIN ((ANGLES)ControlledAC->classtype->wing_dihedral,
//DeadCode RDH 26Mar98 								  (SLong) slip,
//DeadCode RDH 26Mar98 								  ROWANS_PER_RAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //effect of aileron
//DeadCode RDH 26Mar98 	aoa_from_aileron =	(ControlledAC->classtype->maxaildeflect *
//DeadCode RDH 26Mar98 							ControlledAC->fly.aileron) / (MAXAILERON);
//DeadCode RDH 26Mar98  	if (!(Save_Data.flightdifficulty [FD_COORDINATEDRUDDER]))		//RDH 12Dec96
//DeadCode RDH 26Mar98 		aoa_from_aileron =	aoa_from_aileron  /2;				//RDH 12Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (ControlledAC->fly.aileron,aileron_pos,aileron_sign);	//RDH 14Jun96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96  	{
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 		aoa_from_aileron =	( aoa_from_aileron *
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 							aileron_pos) / (MAXAILERON);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 			aoa_from_aileron =	( aoa_from_aileron *
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 							aileron_pos) / (MAXAILERON);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 		aoa_from_aileron =	( aoa_from_aileron *
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 							aileron_pos) / (MAXAILERON);
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 20Aug96 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	vel = ControlledAC->fly.vel_cms - hori_vel_right;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	UWord	aoa_correction_pos;
//DeadCode RDH 26Mar98 	SWord	aoa_correction_sign;
//DeadCode RDH 26Mar98 	UWord	aoa_pos;
//DeadCode RDH 26Mar98 	SWord	aoa_sign;
//DeadCode RDH 26Mar98 	Math_Lib.Pos (ControlledAC->fly.aoa,aoa_pos,aoa_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	aoa_correction_right = aoa_from_roll_right + (SWord) aoa_from_dihedral;
//DeadCode RDH 26Mar98 	aoa_correction_left = aoa_from_roll_left + (SWord) aoa_from_dihedral;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (aoa_correction_right,aoa_correction_pos,aoa_correction_sign);
//DeadCode RDH 26Mar98 	if (aoa_pos <ANGLES_90Deg)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if  ((aoa_pos +  aoa_correction_pos) > ANGLES_90Deg)
//DeadCode RDH 26Mar98 			aoa_correction_pos = ANGLES_90Deg- aoa_pos;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if  ((aoa_pos -  aoa_correction_pos) < ANGLES_90Deg)
//DeadCode RDH 26Mar98 			aoa_correction_pos = aoa_pos - ANGLES_90Deg;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	if (aoa_pos >= (SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 		if  ((aoa_pos -  aoa_correction_right) <  (SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 			aoa_correction_pos = aoa_pos - (SWord) ControlledAC2->classtype->stallangle;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	aoa_correction = Math_Lib.UseSign (aoa_correction_pos,aoa_correction_sign);		
//DeadCode RDH 26Mar98 	aoa_correction_right = aoa_correction;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if  (	(ControlledAC->fly.aoa >ANGLES_90Deg)
//DeadCode RDH 26Mar98 		||	(ControlledAC->fly.aoa <ANGLES_270Deg)				//RDH 24Jul96
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa = ControlledAC->fly.aoa - aoa_correction;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa = ControlledAC->fly.aoa + aoa_correction;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	ControlledAC->fly.highest_aoa = (Angles) aoa;
//DeadCode RDH 26Mar98 	rightwinglift  =	CalcLiftSub(ControlledAC,aoa,vel);
//DeadCode RDH 26Mar98 	innerrightwinglift	=	rightwinglift *
//DeadCode RDH 26Mar98 						(ControlledAC->classtype->wingspan/2
//DeadCode RDH 26Mar98 						  - ControlledAC->classtype->aileronspan)/
//DeadCode RDH 26Mar98 							(ControlledAC->classtype->wingspan / 2);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	aoa = aoa - (SWord) aoa_from_aileron;
//DeadCode RDH 26Mar98 	if ((SWord) aoa > (SWord) ControlledAC->fly.highest_aoa)
//DeadCode RDH 26Mar98 		ControlledAC->fly.highest_aoa = (Angles) aoa;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		right_aoa = aoa;				//used for instrumentation
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	ControlledAC->fly.right_aoa = (Angles) aoa;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	rightwinglift  =	CalcLiftSub(ControlledAC,aoa,vel);
//DeadCode RDH 26Mar98 	rightwinglift  =	rightwinglift *
//DeadCode RDH 26Mar98 						(ControlledAC->classtype->aileronspan)/
//DeadCode RDH 26Mar98 							(ControlledAC->classtype->wingspan / 2);
//DeadCode RDH 26Mar98 	rightwinglift	+= innerrightwinglift;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	if ( (SWord) ControlledAC->fly.slip < 0)
//DeadCode RDH 26Mar98   	{
//DeadCode RDH 26Mar98   		SLong temp = 0 -  ControlledAC->fly.slip;
//DeadCode RDH 26Mar98   		if (temp > ANGLES_90Deg)
//DeadCode RDH 26Mar98   			temp = ANGLES_180Deg - temp;
//DeadCode RDH 26Mar98   		if (temp > ANGLES_30Deg)
//DeadCode RDH 26Mar98   			temp = ANGLES_30Deg;
//DeadCode RDH 26Mar98   		temp = rightwinglift * temp/ ANGLES_30Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		aoa_corr =  (SWord) ControlledAC->fly.right_aoa;		//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		if (aoa_corr < 0)										//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			aoa_corr = 0;										//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		if (aoa_corr > (SWord) ANGLES_15Deg)					//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			aoa_corr = (SWord) ANGLES_15Deg;					//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96  	if (!(Save_Data.flightdifficulty [FD_COORDINATEDRUDDER]))		//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			temp = temp * aoa_corr/ANGLES_15Deg;					//RDH 12Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   		rightwinglift = rightwinglift - temp;
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	vel = ControlledAC->fly.vel_cms + hori_vel_left;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (aoa_correction_left,aoa_correction_pos,aoa_correction_sign);
//DeadCode RDH 26Mar98 	if (aoa_pos <ANGLES_90Deg)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if  ((aoa_pos +  aoa_correction_pos) > ANGLES_90Deg)
//DeadCode RDH 26Mar98 			aoa_correction_pos = ANGLES_90Deg- aoa_pos;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if  ((aoa_pos -  aoa_correction_pos) < ANGLES_90Deg)
//DeadCode RDH 26Mar98 			aoa_correction_pos = aoa_pos - ANGLES_90Deg;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	if (aoa_pos >= (SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 		if  ((aoa_pos +  aoa_correction_left) <  (SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 			aoa_correction_pos = aoa_pos - (SWord) ControlledAC2->classtype->stallangle;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	aoa_correction = Math_Lib.UseSign (aoa_correction_pos,aoa_correction_sign);
//DeadCode RDH 26Mar98 	aoa_correction_left = aoa_correction;
//DeadCode RDH 26Mar98 	if  (	(ControlledAC->fly.aoa >ANGLES_90Deg)
//DeadCode RDH 26Mar98 		||	(ControlledAC->fly.aoa <ANGLES_270Deg)				//RDH 24Jul96
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa = ControlledAC->fly.aoa + aoa_correction;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa = ControlledAC->fly.aoa - aoa_correction;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if ((SWord) aoa > (SWord) ControlledAC->fly.highest_aoa)
//DeadCode RDH 26Mar98 		ControlledAC->fly.highest_aoa = (Angles) aoa;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	leftwinglift  =	CalcLiftSub(ControlledAC,aoa,vel);
//DeadCode RDH 26Mar98 	innerleftwinglift	=	leftwinglift *
//DeadCode RDH 26Mar98 						(ControlledAC->classtype->wingspan/2
//DeadCode RDH 26Mar98 						  - ControlledAC->classtype->aileronspan)/
//DeadCode RDH 26Mar98 							(ControlledAC->classtype->wingspan / 2);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	aoa = aoa + (SWord) aoa_from_aileron;
//DeadCode RDH 26Mar98 	if ((SWord) aoa > (SWord) ControlledAC->fly.highest_aoa)
//DeadCode RDH 26Mar98 		ControlledAC->fly.highest_aoa = (Angles) aoa;
//DeadCode RDH 26Mar98 	leftwinglift  =	CalcLiftSub(ControlledAC,aoa,vel);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		left_aoa = aoa;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	ControlledAC->fly.left_aoa = (Angles) aoa;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	leftwinglift  =	leftwinglift *
//DeadCode RDH 26Mar98 						(ControlledAC->classtype->aileronspan)/
//DeadCode RDH 26Mar98 							(ControlledAC->classtype->wingspan / 2);
//DeadCode RDH 26Mar98 	leftwinglift	+= innerleftwinglift;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	if ( (SWord) ControlledAC->fly.slip > 0)
//DeadCode RDH 26Mar98   	{
//DeadCode RDH 26Mar98   		SLong temp =  ControlledAC->fly.slip;
//DeadCode RDH 26Mar98   		if (temp > ANGLES_90Deg)
//DeadCode RDH 26Mar98   			temp = ANGLES_180Deg - temp;
//DeadCode RDH 26Mar98   		if (temp > ANGLES_30Deg)
//DeadCode RDH 26Mar98   			temp = ANGLES_30Deg;
//DeadCode RDH 26Mar98   		temp = leftwinglift * temp/ ANGLES_30Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		aoa_corr =  (SWord) ControlledAC->fly.left_aoa;			//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		if (aoa_corr < 0)										//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			aoa_corr = 0;										//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		if (aoa_corr > (SWord) ANGLES_15Deg)					//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			aoa_corr = (SWord) ANGLES_15Deg;					//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96  	if (!(Save_Data.flightdifficulty [FD_COORDINATEDRUDDER]))		//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			temp = temp * aoa_corr/ANGLES_15Deg;					//RDH 12Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   		leftwinglift = leftwinglift - temp;
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	SLong temp;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96    	if ( ControlledAC->fly.slip < 0)
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96    	{
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96    		temp = -  ControlledAC->fly.slip;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	}else
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 		temp =   ControlledAC->fly.slip;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	if (temp > ANGLES_30Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 		temp = ANGLES_30Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	temp = lift * temp/ ANGLES_30Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	lift = lift - temp;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 	AircraftAnimData*	adptr;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	adptr = (AircraftAnimData *)ControlledAC->Anim;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 	UWord	lcldamflag;
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 	lcldamflag = adptr->dammageflags;
//DeadCode RDH 26Mar98 	templeftwinglift = leftwinglift;
//DeadCode RDH 26Mar98 	temprightwinglift = rightwinglift;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	if (adptr->BOTLEFTWING == BS_DEAD)							//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	{	//No bottom left wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 		leftwinglift = leftwinglift - 3*templeftwinglift/4;
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	}
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	if (adptr->BOTRIGHTWING == BS_DEAD)							//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	{	//No bottom right wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 		rightwinglift = rightwinglift - 3*temprightwinglift/4;
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	}
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	if (adptr->TOPLEFTWING == BS_DEAD)							//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	{	//No top left wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 		leftwinglift = leftwinglift - 3*templeftwinglift/4;
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	}
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	if (adptr->TOPRIGHTWING == BS_DEAD)							//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	{	//No top right wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 		rightwinglift = rightwinglift - 3*temprightwinglift/4;
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (rightwinglift < 0)
//DeadCode RDH 26Mar98 		rightwinglift = 0;										//RJS 13Nov96
//DeadCode RDH 26Mar98 	if (leftwinglift < 0)
//DeadCode RDH 26Mar98 		leftwinglift = 0;										//RJS 13Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	lift = leftwinglift + rightwinglift;
//DeadCode RDH 26Mar98 //DeadCode RJS 09Oct96 	if (lift == 0)
//DeadCode RDH 26Mar98 //DeadCode RJS 09Oct96 	{
//DeadCode RDH 26Mar98 //DeadCode RJS 09Oct96 		if (ControlledAC2 == ControlledAC)		//RDH 12Sep96
//DeadCode RDH 26Mar98 //DeadCode RJS 09Oct96 				controlmode=PILOTDEAD;				//RDH 12Sep96
//DeadCode RDH 26Mar98 //DeadCode RJS 09Oct96 		ControlledAC->movecode = AUTO_CRASHSKID;
//DeadCode RDH 26Mar98 //DeadCode RJS 09Oct96 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcLiftSub
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Sun 7 Apr 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	lift for half a wing
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 SLong	ManualPilot::CalcLiftSub(AirStrucPtr const ControlledAC,SWord aoa,SLong vel)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SWord	cl_slope,cloffset;
//DeadCode RDH 26Mar98 	SLong	retval;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	if (	(!(Save_Data.flightdifficulty [FD_SPINS]))
//DeadCode RDH 26Mar98 //DeadCode RDH 12Jul96 		||	(ControlledAC2 != ControlledAC)
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (aoa > (SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98 				aoa = (SWord) ControlledAC2->classtype->stallangle;
//DeadCode RDH 26Mar98 		if ( ControlledAC->fly.aoa >
//DeadCode RDH 26Mar98 			(SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98 				aoa = (SWord) ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	if	((ANGLES) aoa < ControlledAC->classtype->liftangle[0])
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_slope = ControlledAC->classtype->liftcurve[0];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cloffset = ControlledAC->classtype->liftbase[0];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	elseif	((ANGLES) aoa < ControlledAC->classtype->liftangle[1])
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_slope = ControlledAC->classtype->liftcurve[1];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cloffset = ControlledAC->classtype->liftbase[1];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	else if	((ANGLES) aoa < ControlledAC->classtype->liftangle[2])
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_slope = ControlledAC->classtype->liftcurve[2];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cloffset = ControlledAC->classtype->liftbase[2];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	else if	((ANGLES) aoa < ControlledAC->classtype->liftangle[3])
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_slope = ControlledAC->classtype->liftcurve[3];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cloffset = ControlledAC->classtype->liftbase[3];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	else if	((ANGLES) aoa < ControlledAC->classtype->liftangle[4])
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_slope = ControlledAC->classtype->liftcurve[4];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cloffset = ControlledAC->classtype->liftbase[4];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	elseif	((ANGLES) aoa < ControlledAC->classtype->liftangle[5])
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_slope = ControlledAC->classtype->liftcurve[5];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cloffset = ControlledAC->classtype->liftbase[5];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	elseif	((ANGLES) aoa < ControlledAC->classtype->liftangle[6])
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_slope = ControlledAC->classtype->liftcurve[6];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cloffset = ControlledAC->classtype->liftbase[6];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	else
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_slope = ControlledAC->classtype->liftcurve[7];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cloffset = ControlledAC->classtype->liftbase[7];
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_coeff = cloffset;
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 		cl_coeff +=	(cl_slope * ((SWord)aoa)) / LIFTCONST;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	UWord		d1,d2;
//DeadCode RDH 26Mar98 	SLong	cl;
//DeadCode RDH 26Mar98 	UWord	aoa_pos;
//DeadCode RDH 26Mar98 	SWord	aoa_sign,aoa_5deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (aoa,aoa_pos,aoa_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		aoa_5deg = aoa_pos /ANGLES_5Deg;
//DeadCode RDH 26Mar98 		d1 = ControlledAC->classtype->liftcurve[aoa_5deg];
//DeadCode RDH 26Mar98 		d2 = ControlledAC->classtype->liftcurve[aoa_5deg + 1];
//DeadCode RDH 26Mar98 		cl = d1+ (d2-d1) * (aoa_pos - ANGLES_5Deg * aoa_5deg) / ANGLES_5Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (aoa_sign == MathLib::NEGATIVE)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		cl_coeff = (SLong) -cl/10;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		cl_coeff = (SLong) cl/10;
//DeadCode RDH 26Mar98 	}	
//DeadCode RDH 26Mar98  	 	Math_Lib.high_sin_cos(ControlledAC->fly.slip,sinslip,cosslip); 
//DeadCode RDH 26Mar98  		vel = vel * cosslip/ ANGLES_FRACT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		retval = MULDIVSIN(vel,vel,100);
//DeadCode RDH 26Mar98 		retval = MULDIVSIN(retval,(SLong)cl_coeff,100); 
//DeadCode RDH 26Mar98 		retval = MULDIVSIN (retval,airdensity,1000);
//DeadCode RDH 26Mar98 		retval = MULDIVSIN (retval,ControlledAC->classtype->wingarea,4000);
//DeadCode RDH 26Mar98 		return (retval);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Thu 24 Aug 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //                Total Drag = Shokdrag + Parasitedrag + Induceddrag 
//DeadCode RDH 26Mar98 //                              ( +landing_gear + wheelbrakes + groundfriction)
//DeadCode RDH 26Mar98 //                              in N
//DeadCode RDH 26Mar98 //          
//DeadCode RDH 26Mar98 //		               			(Machth - M1*K) * (d2-d1)      
//DeadCode RDH 26Mar98 //                ShokDrag = [ -------------------------- + d1 ] * Rho / Rho at sea level  
//DeadCode RDH 26Mar98 //                                K * (M2 - M1)
//DeadCode RDH 26Mar98 //                                      \______/--> 1
//DeadCode RDH 26Mar98 //                                         
//DeadCode RDH 26Mar98 //						v in 1 cm/s
//DeadCode RDH 26Mar98 //						SoS in m/s
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //                            with MachTh = V * 1024/ SoS;
//DeadCode RDH 26Mar98 //                            M2 = M1 + 1  in tenths of machs;
//DeadCode RDH 26Mar98 //                            d2, d1       ,shokdrags at M2, M1
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //                Induced  =  CL*CL * (v*v/100*Rho/2000*S) /10000  ;;bob 33
//DeadCode RDH 26Mar98 //                             --------------------------------------
//DeadCode RDH 26Mar98 //                                   (Pi*Ar*Eff)       
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //                Parasite =  (v*v/100*Rho/2000*S) /1000
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		                  			(Machth - M1*K) * (cDo2-cDo1)      
//DeadCode RDH 26Mar98 //                             * [ ------------------------------ + cDo1 ]  
//DeadCode RDH 26Mar98 //                                      K 
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //                landing_gear   = fraction of Induced + Para
//DeadCode RDH 26Mar98 //                groundfriction = fraction of (Weight - Lift)
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //									0.05 short grass
//DeadCode RDH 26Mar98 //									0.10 long grass
//DeadCode RDH 26Mar98 //									0.20 soft ground (camel stuck T/W = .18)
//DeadCode RDH 26Mar98 //					
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //                wheelbrakes    = const val (100) 
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcDrag(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	aoa_corr;										//RDH 12Dec96
//DeadCode RDH 26Mar98 	SLong	groundfriction,innerrightwingdrag,innerleftwingdrag;
//DeadCode RDH 26Mar98 	SLong	temprightwingdrag,templeftwingdrag;
//DeadCode RDH 26Mar98 	SLong	vel,sidedrag;
//DeadCode RDH 26Mar98 	SWord	aoa,slip;
//DeadCode RDH 26Mar98 	SWord	aoa_rollpos,aoa_dihedralpos,aoa_sign,d_aoa = 0;
//DeadCode RDH 26Mar98 	Bool	rightwingdragpos = TRUE;
//DeadCode RDH 26Mar98 	Bool	leftwingdragpos = TRUE;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	groundfriction = 0;											//RDH 29Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	vel =  ControlledAC->fly.vel_cms - hori_vel_right;
//DeadCode RDH 26Mar98 	if (vel > (2*ControlledAC->fly.vel_cms))
//DeadCode RDH 26Mar98 		vel = 2*ControlledAC->fly.vel_cms;
//DeadCode RDH 26Mar98 	if (vel <0)
//DeadCode RDH 26Mar98 	    rightwingdragpos = FALSE;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //effect of aoa change on drag was not good:
//DeadCode RDH 26Mar98 //snap roll impossible and adverse yaw masked	
//DeadCode RDH 26Mar98 //DeadCode RDH 04Jul96   	aoa = ControlledAC->fly.aoa + aoa_from_roll + (SWord) aoa_from_dihedral;
//DeadCode RDH 26Mar98  	if  (	(ControlledAC->fly.aoa >ANGLES_90Deg)
//DeadCode RDH 26Mar98  		||	(ControlledAC->fly.aoa <ANGLES_270Deg)				//RDH 24Jul96
//DeadCode RDH 26Mar98  		)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		aoa = ControlledAC->fly.aoa - aoa_correction_right;
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		aoa = ControlledAC->fly.aoa + aoa_correction_right;
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98     	aoa = ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 //put in some drag for disturbance								//RDH 03May96
//DeadCode RDH 26Mar98 //DeadCode RDH 03May96  	Math_Lib.Pos (aoa_from_roll,aoa_rollpos,aoa_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 03May96  	d_aoa = aoa_rollpos;
//DeadCode RDH 26Mar98 //DeadCode RDH 03May96  	Math_Lib.Pos (aoa_from_dihedral,aoa_dihedralpos,aoa_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 03May96  	d_aoa += aoa_from_dihedral;
//DeadCode RDH 26Mar98 //DeadCode RDH 23May96 	
//DeadCode RDH 26Mar98 //DeadCode RDH 23May96 	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	rightwingdrag  =	CalcDragSub(ControlledAC,aoa,vel);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	innerrightwingdrag	=	rightwingdrag *
//DeadCode RDH 26Mar98 						(ControlledAC->classtype->wingspan/2
//DeadCode RDH 26Mar98 						  - ControlledAC->classtype->aileronspan)/
//DeadCode RDH 26Mar98 							(ControlledAC->classtype->wingspan / 2);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	if (!(Save_Data.flightdifficulty [FD_COORDINATEDRUDDER]))
//DeadCode RDH 26Mar98 		aoa = aoa - ControlledAC->classtype->adverseyaweffect * (SWord)( aoa_from_aileron)/100;
//DeadCode RDH 26Mar98 	rightwingdrag  =	CalcDragSub(ControlledAC,aoa,vel);
//DeadCode RDH 26Mar98 	rightwingdrag  =	rightwingdrag *
//DeadCode RDH 26Mar98 						(ControlledAC->classtype->aileronspan)/
//DeadCode RDH 26Mar98 							(ControlledAC->classtype->wingspan / 2);
//DeadCode RDH 26Mar98 	rightwingdrag	+= innerrightwingdrag;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	if ( (SWord) ControlledAC->fly.slip < 0)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		SLong temp = 0 -  ControlledAC->fly.slip;
//DeadCode RDH 26Mar98   		if (temp > ANGLES_90Deg)
//DeadCode RDH 26Mar98   			temp = ANGLES_180Deg - temp;
//DeadCode RDH 26Mar98  		if (temp > ANGLES_30Deg)
//DeadCode RDH 26Mar98  			temp = ANGLES_30Deg;
//DeadCode RDH 26Mar98  		temp = rightwingdrag * temp/ ANGLES_30Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		aoa_corr =  (SWord) ControlledAC->fly.right_aoa;			//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		if (aoa_corr < 0)										//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			aoa_corr = 0;										//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		if (aoa_corr > (SWord) ANGLES_15Deg)					//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			aoa_corr = (SWord) ANGLES_15Deg;					//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96  	if (!(Save_Data.flightdifficulty [FD_COORDINATEDRUDDER]))		//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			temp = temp * aoa_corr/ANGLES_15Deg;					//RDH 12Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  		rightwingdrag = rightwingdrag - temp;
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	vel = ControlledAC->fly.vel_cms + hori_vel_left;
//DeadCode RDH 26Mar98 	if (vel > (2*ControlledAC->fly.vel_cms))
//DeadCode RDH 26Mar98 		vel = 2*ControlledAC->fly.vel_cms;
//DeadCode RDH 26Mar98 	if (vel <0)
//DeadCode RDH 26Mar98 	    leftwingdragpos = FALSE;
//DeadCode RDH 26Mar98 //effect of aoa change on drag was not good:
//DeadCode RDH 26Mar98 //snap roll imposs and adverse yaw masked	
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96   	aoa = ControlledAC->fly.aoa - aoa_from_roll - (SWord) aoa_from_dihedral;//RDH 22May96
//DeadCode RDH 26Mar98   	if  (	(ControlledAC->fly.aoa >ANGLES_90Deg)
//DeadCode RDH 26Mar98   		||	(ControlledAC->fly.aoa <ANGLES_270Deg)				//RDH 24Jul96
//DeadCode RDH 26Mar98   		)
//DeadCode RDH 26Mar98   	{
//DeadCode RDH 26Mar98   		aoa = ControlledAC->fly.aoa + aoa_correction_left;
//DeadCode RDH 26Mar98   	}else
//DeadCode RDH 26Mar98   	{
//DeadCode RDH 26Mar98   		aoa = ControlledAC->fly.aoa - aoa_correction_left;
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98    	aoa = ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 	leftwingdrag  =	CalcDragSub(ControlledAC,aoa,vel);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	innerleftwingdrag	=	leftwingdrag *
//DeadCode RDH 26Mar98 						(ControlledAC->classtype->wingspan/2
//DeadCode RDH 26Mar98 						  - ControlledAC->classtype->aileronspan)/
//DeadCode RDH 26Mar98 							(ControlledAC->classtype->wingspan / 2);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	if (!(Save_Data.flightdifficulty [FD_COORDINATEDRUDDER]))
//DeadCode RDH 26Mar98 		aoa = aoa + ControlledAC->classtype->adverseyaweffect * (SWord)( aoa_from_aileron)/100;
//DeadCode RDH 26Mar98 	leftwingdrag  =	CalcDragSub(ControlledAC,aoa,vel);
//DeadCode RDH 26Mar98 	leftwingdrag  =	leftwingdrag *
//DeadCode RDH 26Mar98 						(ControlledAC->classtype->aileronspan)/
//DeadCode RDH 26Mar98 							(ControlledAC->classtype->wingspan / 2);
//DeadCode RDH 26Mar98 	leftwingdrag	+= innerleftwingdrag;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	if ( (SWord) ControlledAC->fly.slip > 0)
//DeadCode RDH 26Mar98   	{
//DeadCode RDH 26Mar98   		SLong temp =   ControlledAC->fly.slip;
//DeadCode RDH 26Mar98   		if (temp > ANGLES_90Deg)
//DeadCode RDH 26Mar98   			temp = ANGLES_180Deg - temp;
//DeadCode RDH 26Mar98   		if (temp > ANGLES_30Deg)
//DeadCode RDH 26Mar98   			temp = ANGLES_30Deg;
//DeadCode RDH 26Mar98   		temp = leftwingdrag * temp/ ANGLES_30Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		aoa_corr =  (SWord) ControlledAC->fly.left_aoa;			//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		if (aoa_corr < 0)										//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			aoa_corr = 0;										//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		if (aoa_corr > (SWord) ANGLES_15Deg)					//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			aoa_corr = (SWord) ANGLES_15Deg;					//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 		
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96  	if (!(Save_Data.flightdifficulty [FD_COORDINATEDRUDDER]))		//RDH 12Dec96
//DeadCode RDH 26Mar98 //DeadCode RDH 13Dec96 			temp = temp * aoa_corr/ANGLES_15Deg;					//RDH 12Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   		leftwingdrag = leftwingdrag - temp;
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	sidedrag	=		sideforce/4;
//DeadCode RDH 26Mar98 	if (sideforce < 0)
//DeadCode RDH 26Mar98 			sidedrag = -sidedrag;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	CalcParasiteDrag(ControlledAC);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	AircraftAnimData*	adptr;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	adptr = (AircraftAnimData *)ControlledAC->Anim;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 	UWord	lcldamflag;
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 	lcldamflag = adptr->dammageflags;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	templeftwingdrag = leftwingdrag;
//DeadCode RDH 26Mar98 	temprightwingdrag = rightwingdrag;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	if (adptr->BOTLEFTWING == BS_DEAD)							//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	{	//No bottom left wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 		leftwingdrag = leftwingdrag - templeftwingdrag/2;
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	}
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	if (adptr->BOTRIGHTWING == BS_DEAD)							//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	{	//No bottom right wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 		rightwingdrag = rightwingdrag - temprightwingdrag/2;
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	}
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	if (adptr->TOPLEFTWING == BS_DEAD)							//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	{	//No bottom left wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 		leftwingdrag = leftwingdrag - templeftwingdrag/2;
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	}
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	if (adptr->TOPRIGHTWING == BS_DEAD)							//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	{	//No bottom right wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 		rightwingdrag = rightwingdrag - temprightwingdrag/2;
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	templeftwingdrag = leftwingdrag;
//DeadCode RDH 26Mar98 	temprightwingdrag = rightwingdrag;
//DeadCode RDH 26Mar98 	if (rightwingdragpos == FALSE)
//DeadCode RDH 26Mar98 		temprightwingdrag = -temprightwingdrag;	
//DeadCode RDH 26Mar98 	if (leftwingdragpos == FALSE)
//DeadCode RDH 26Mar98 		templeftwingdrag = -templeftwingdrag;	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	totaldrag = templeftwingdrag + temprightwingdrag + parasiticdrag  + sidedrag;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (ControlledAC->World.Y <= groundlevel)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		//effect of tail skid: almost comes to full stop on landing in glide
//DeadCode RDH 26Mar98 		if ( ControlledAC->pitch >= ControlledAC->classtype->deckangle)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			groundfriction =  LONGGRASSCOEFF * (ControlledAC->fly.weight - lift)/100;
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			groundfriction =  SHORTGRASSCOEFF * (ControlledAC->fly.weight - lift)/100;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		if (groundfriction > 0)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 21Oct96 			if (ControlledAC->AnimByte((AFR) &AircraftAnimData::warninglights) && WBRAKEON) 
//DeadCode RDH 26Mar98 //DeadCode RDH 21Oct96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 21Oct96 	 			groundfriction += ControlledAC->fly.weight;
//DeadCode RDH 26Mar98 //DeadCode RDH 21Oct96 			}
//DeadCode RDH 26Mar98 			totaldrag += groundfriction;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if ((totaldrag > thrust)
//DeadCode RDH 26Mar98 		&& ( ControlledAC->vel <= 0))
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		totaldrag = thrust;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcdragSub
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Sun 7 Apr 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	drag for half wing
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 SLong	ManualPilot::CalcDragSub(AirStrucPtr const ControlledAC,SWord aoa,SLong vel)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	retval;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	SLong	mach_10000th;		//mach in 1/10000th's
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 d	SLong	mach_10th;			//mach in 1/10th's of a mach
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	SLong	pi_ar_ef;
//DeadCode RDH 26Mar98 	SLong	cl_fordrag;
//DeadCode RDH 26Mar98 	SLong	groundfriction;
//DeadCode RDH 26Mar98 	SLong	induceddrag,d1,d2,commondragcomp;					//RDH 27Apr96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	if (!(Save_Data.flightdifficulty [FD_SPINS]))
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (aoa > (SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98 				aoa = (SWord) ControlledAC2->classtype->stallangle;
//DeadCode RDH 26Mar98 		if ( ControlledAC->fly.aoa >
//DeadCode RDH 26Mar98 			(SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98 				aoa = (SWord) ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96  	mach_10000th = (1000 * ControlledAC->vel)/sos;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	if (mach_10000th > K_MACH)
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 		mach_10000th = K_MACH;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	mach_10th = mach_10000th/1000	;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	d1 = shokdata[mach_10th];
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	d2 = shokdata[mach_10th+1];
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	shockdrag = d1+ (d2-d1) * (mach_10000th - mach_10th*1000)/10000; 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	UWord	aoa_pos;
//DeadCode RDH 26Mar98 	SWord	aoa_sign;
//DeadCode RDH 26Mar98 	SLong	aoa_5deg,cl_drag,d_p;
//DeadCode RDH 26Mar98 //DeadCode RDH 23May96  	Math_Lib.Pos ((SWord) ControlledAC->fly.aoa,aoa_pos,aoa_sign);
//DeadCode RDH 26Mar98  	Math_Lib.Pos (aoa,aoa_pos,aoa_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (aoa_pos > ANGLES_90Deg)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 01Jul96 		aoa_pos = ANGLES_180Deg - aoa_pos;
//DeadCode RDH 26Mar98 		aoa_pos = ANGLES_90Deg;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	aoa_5deg = aoa_pos/ ANGLES_5Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	d1 = ControlledAC->classtype->dragcurve[aoa_5deg];
//DeadCode RDH 26Mar98 	d2 = ControlledAC->classtype->dragcurve[aoa_5deg + 1];
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	cl_drag = d1+ (d2-d1) * (aoa_pos - aoa_5deg * ANGLES_5Deg)/ANGLES_5Deg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	Math_Lib.high_sin_cos(ControlledAC->fly.slip,sinslip,cosslip); 
//DeadCode RDH 26Mar98  	vel = vel * cosslip/ ANGLES_FRACT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	d_p = MULDIVSIN(vel,vel,100);
//DeadCode RDH 26Mar98 	d_p = MULDIVSIN (d_p,airdensity,1000);
//DeadCode RDH 26Mar98 	induceddrag = MULDIVSIN(d_p,cl_drag,1000); 
//DeadCode RDH 26Mar98 	induceddrag = MULDIVSIN(induceddrag,
//DeadCode RDH 26Mar98 				ControlledAC->classtype->wingarea,4000);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	parasiticdrag = MULDIVSIN(d_p,
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 					ControlledAC->classtype->parasiticdragarea,
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 					2000000);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	retval =  	induceddrag;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	if (ControlledAC->AnimByte((AFR) &AircraftAnimData::warninglights) && BRAKEON)
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 		retval += 8 * parasiticdrag;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Jul96 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		return (retval);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcParasiteDrag
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 3 Jul 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcParasiteDrag(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	d_p,vel_factor;
//DeadCode RDH 26Mar98 	SLong	aoa_factor;
//DeadCode RDH 26Mar98 	UWord	aoa_pos;
//DeadCode RDH 26Mar98 	SWord	aoa_sign;
//DeadCode RDH 26Mar98 	SWord	cosaoa,sinaoa;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	d_p = MULDIVSIN(ControlledAC->fly.vel_cms,ControlledAC->fly.vel_cms,100);
//DeadCode RDH 26Mar98 	parasiticdrag = MULDIVSIN(d_p,
//DeadCode RDH 26Mar98 					ControlledAC->classtype->parasiticdragarea,
//DeadCode RDH 26Mar98 					2000000);
//DeadCode RDH 26Mar98 	if (	(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])//RDH 23Sep96
//DeadCode RDH 26Mar98 		&&	(Save_Data.gamedifficulty [GD_LIMITEDARM])
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			vel_factor = ControlledAC->classtype->maxvel * ControlledAC->classtype->maxvel;
//DeadCode RDH 26Mar98 			vel_factor = ControlledAC->fly.storesweight * d_p /vel_factor;
//DeadCode RDH 26Mar98 			parasiticdrag +=  vel_factor/2;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (ControlledAC->fly.aoa,aoa_pos,aoa_sign);
//DeadCode RDH 26Mar98  	if (aoa_pos > (SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		aoa_pos = (SWord) ControlledAC2->classtype->stallangle;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	aoa_factor =	16384 * aoa_pos/ControlledAC2->classtype->stallangle; 
//DeadCode RDH 26Mar98  	Math_Lib.high_sin_cos((Angles)aoa_factor,sinaoa,cosaoa); 
//DeadCode RDH 26Mar98 	aoa_factor = 32768 - cosaoa;
//DeadCode RDH 26Mar98 	parasiticdrag = parasiticdrag + parasiticdrag * aoa_factor / 4000;
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Thu 24 Aug 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //                if a Keyboard control game
//DeadCode RDH 26Mar98 //		             - calculates Trim (is treated as an elevtor input in Rotas)
//DeadCode RDH 26Mar98 //                No trim if:   Elevator input 
//DeadCode RDH 26Mar98 //                              big Roll 
//DeadCode RDH 26Mar98 //                              rpm changed recently
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcTrim(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	UWord	elevator_pos;
//DeadCode RDH 26Mar98 	SWord	elevator_sign;
//DeadCode RDH 26Mar98 	UWord	aileron_pos;
//DeadCode RDH 26Mar98 	SWord	aileron_sign;
//DeadCode RDH 26Mar98 	UWord	roll_pos;
//DeadCode RDH 26Mar98 	SWord	roll_sign;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		Math_Lib.Pos (ControlledAC->fly.aileron,aileron_pos,aileron_sign);
//DeadCode RDH 26Mar98 		Math_Lib.Pos (ControlledAC->fly.elevator,elevator_pos,elevator_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.Pos (ControlledAC->roll,roll_pos,roll_sign);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 	if (ControlledAC->World.Y <= groundlevel)
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 	{
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 	 	trim = trim;
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 	}
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 	else
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 	{
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 		if (	(elevator_pos <= ELEVPLUS1)	||
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 			((ControlledAC->fly.aoa+ControlledAC2->classtype->stallangle-ANGLES_2Deg)
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 				> (2*(ControlledAC2->classtype->stallangle-ANGLES_2Deg)))
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 			)
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 //DeadCode RDH 24Sep96   			&&	((SWord) ControlledAC->fly.aoa <
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 //DeadCode RDH 24Sep96 						((SWord) ControlledAC2->classtype->stallangle - ANGLES_2Deg))
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 //DeadCode RDH 24Sep96 			)
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 		{
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 			if ((roll_pos <ANGLES_10Deg) ||
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 //**				((device == 0) && (LastStickPress ==0)) ||
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 	  				(ControlledAC->fly.aileron != 0))
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 			{
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 				DoTrim (ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 			}
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 //**			if	(FlightFlags & AUTO_TO_MANUAL)
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 //**				DoTrim ();
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 		
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 // if rpm has changed in last 2 secs then don't apply trim
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 // this is to allow aircraft to pitch automatically on rpm change
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 			if ((ControlledAC->fly.rpm == ControlledAC->fly.rpm_lastcycle)		
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 				&& (ControlledAC->fly.rpmtrimtime == 0))
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 				{
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 					DoTrim (ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 				}
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 			if (ControlledAC->fly.rpm != ControlledAC->fly.rpm_lastcycle)
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 				{
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 			 		ControlledAC->fly.rpmtrimtime = 200;		//2 secs	
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 					ControlledAC->fly.rpm_lastcycle = ControlledAC->fly.rpm;
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 				}else
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 				{
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 					ControlledAC->fly.rpmtrimtime -= FLIGHTMODEL_TIMEFRAME;	
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 				}
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 		}
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 			
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 		
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 	  
//DeadCode RDH 26Mar98 //DeadCode PD 15Nov96 	}	
//DeadCode RDH 26Mar98 	if (ControlledAC->World.Y <= groundlevel)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 	 	trim = trim;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if  (	(elevator_pos <= ELEVPLUS1)	
//DeadCode RDH 26Mar98 			&&	(	(SWord)ControlledAC->fly.right_aoa	<
//DeadCode RDH 26Mar98 					(SWord)(ControlledAC2->classtype->stallangle-ANGLES_2Deg)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			&&	(	(SWord)ControlledAC->fly.left_aoa	<
//DeadCode RDH 26Mar98 					(SWord)(ControlledAC2->classtype->stallangle-ANGLES_2Deg)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			&&	(roll_pos < ANGLES_10Deg)
//DeadCode RDH 26Mar98 			&&	(ControlledAC->fly.aileron == 0)
//DeadCode RDH 26Mar98 			&&	(ControlledAC->fly.rpmtrimtime == 0)
//DeadCode RDH 26Mar98 			&&	(ControlledAC->fly.thrustpercent == ControlledAC->fly.rpm_lastcycle)		
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 				DoTrim (ControlledAC);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		 if (ControlledAC->fly.thrustpercent != ControlledAC->fly.rpm_lastcycle)
//DeadCode RDH 26Mar98 		 {
//DeadCode RDH 26Mar98 		 		ControlledAC->fly.rpmtrimtime = 200;		//2 secs	
//DeadCode RDH 26Mar98 		 		ControlledAC->fly.rpm_lastcycle = ControlledAC->fly.thrustpercent;
//DeadCode RDH 26Mar98 		 }else
//DeadCode RDH 26Mar98 		 {
//DeadCode RDH 26Mar98 		 		ControlledAC->fly.rpmtrimtime -= FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 				if (ControlledAC->fly.rpmtrimtime  < 0)
//DeadCode RDH 26Mar98 					ControlledAC->fly.rpmtrimtime  = 0;
//DeadCode RDH 26Mar98 		 }
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if	(	(SWord)ControlledAC->fly.right_aoa	>=
//DeadCode RDH 26Mar98 					(SWord)(ControlledAC2->classtype->stallangle-ANGLES_2Deg))
//DeadCode RDH 26Mar98 	 	trim = 0;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		Do_trim
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Mon 25 Sep 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::DoTrim(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SLong	cl_tail;
//DeadCode RDH 26Mar98 	SWord	aoa;
//DeadCode RDH 26Mar98  	SLong	moment,maxtrim;
//DeadCode RDH 26Mar98 	UWord	trim_pos;
//DeadCode RDH 26Mar98 	SWord	trim_sign;
//DeadCode RDH 26Mar98 	SWord	sinalfa;
//DeadCode RDH 26Mar98 	SWord	cosalfa;
//DeadCode RDH 26Mar98 	SLong	tailforce;
//DeadCode RDH 26Mar98 	SLong	wingforce;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96  	moment	= ControlledAC->classtype->chord
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96 				* ControlledAC->classtype->wingarea/ 1000; 
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96 	moment  = moment * dynamicpressure; 
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96  	moment	= moment * ControlledAC->classtype->cm_acwb/10000;
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96  
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96  
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96 //DeadCode RDH 03Jun96  	moment += lift * ControlledAC->classtype->cog_neut_init /1000;
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96  	moment += lift * ControlledAC->fly.cog /1000;
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96  
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96  	moment -= taillift * ControlledAC->classtype->lt/100;
//DeadCode RDH 26Mar98 //TempCode RDH 22Jul96 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	moment	= ControlledAC->classtype->wingarea 
//DeadCode RDH 26Mar98   				  *	ControlledAC->classtype->chord/10;
//DeadCode RDH 26Mar98  	moment 	= MULDIVSIN (moment,dynamicpressure,100);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	moment	= MULDIVSIN (moment,ControlledAC->classtype->cm_acwb,10000);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ((ControlledAC->fly.aoa > ANGLES_90Deg)
//DeadCode RDH 26Mar98 		|| (ControlledAC->fly.aoa < ANGLES_270Deg))				//RDH 24Jul96
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	aoa = ANGLES_180Deg - ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	aoa =  ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.high_sin_cos ((Angles)aoa,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 	wingforce =  (lift * cosalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 				 	(totaldrag * sinalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 	moment += wingforce * ControlledAC->fly.cog /1000;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	tailforce =  (taillift * cosalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 				 	(taildrag * sinalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	moment -= tailforce * ControlledAC->classtype->lt/100;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	trim	= -moment;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	moment  = MULDIVSIN (ControlledAC->fly.rotr_xbl,ControlledAC->classtype->moi.x,10);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	moment	=	moment / FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 	trim	-= moment;
//DeadCode RDH 26Mar98 	if (trim > 32767)
//DeadCode RDH 26Mar98 		trim = 32767;
//DeadCode RDH 26Mar98 	if (trim < -32768)
//DeadCode RDH 26Mar98 		trim = -32768;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	cl_tail = CalcTailLiftSub (ControlledAC,MAXELEVATOR,aoa);
//DeadCode RDH 26Mar98 	maxtrim = dynamicpressure * ControlledAC->classtype->tailarea/10000;
//DeadCode RDH 26Mar98 	maxtrim = maxtrim * ControlledAC->classtype->tailliftmodifier/100;
//DeadCode RDH 26Mar98 	maxtrim = maxtrim * cl_tail /100;
//DeadCode RDH 26Mar98 	maxtrim = maxtrim * ControlledAC->classtype->lt/100;
//DeadCode RDH 26Mar98 	Math_Lib.Pos ((SWord) trim,trim_pos,trim_sign);
//DeadCode RDH 26Mar98 	if (trim_pos > maxtrim)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (trim_sign == MathLib::POSITIVE)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			trim = maxtrim;
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			trim = -maxtrim;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 15Nov96 	trim = 0;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Thu 24 Aug 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 // Description:  Calculates the rotation rates rotr_xbl,rotr_ybl, rotr_zbl
//DeadCode RDH 26Mar98 //               in the Ac_body coordinate system 
//DeadCode RDH 26Mar98 //               - uses local velocity to keep control at low v (in 10th m/s)
//DeadCode RDH 26Mar98 //                           2000 < v < 2600   ,[velocity] = v
//DeadCode RDH 26Mar98 //                 @@v_nhig: 800  < v < 2000   ,[velocity] = v + (1000 - v/2)
//DeadCode RDH 26Mar98 //                 @@v_low :        v < 800    ,[velocity] = v + ( 200 + v/2)
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 // 
//DeadCode RDH 26Mar98 //               - ROLLING: rotr_zbl............................
//DeadCode RDH 26Mar98 //                 damping previous rotr_Z t0 50%
//DeadCode RDH 26Mar98 //                 CMtot = Cmalfa*f(Aileron,AoA)  + CMpee*f(Slip)
//DeadCode RDH 26Mar98 //                              [(CMtot * v*v/256)/8 ] * [CycleT*Span*S] *Rho
//DeadCode RDH 26Mar98 //                 delta_RotZ =---------------------------------------------->>4
//DeadCode RDH 26Mar98 //                                                 1600000h * Izz
//DeadCode RDH 26Mar98 //                 final rotr_zbl limited by maxirotz
//DeadCode RDH 26Mar98 //                 straight fiddle: if (Rotr_Z < 20) and (no aileron) -> rotrZ/2
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //                - YAWING: rotr_ybl............................
//DeadCode RDH 26Mar98 //                  damping previous rotr_Y to 75%
//DeadCode RDH 26Mar98 //                  CMtot = CL_FinNom * (f.rudder + Slip) 
//DeadCode RDH 26Mar98 //                              [(CMtot * v*v/128 ] * [CycleT*FinSlope] *Rho
//DeadCode RDH 26Mar98 //                  delta_RotrY =--------------------------------------------
//DeadCode RDH 26Mar98 //                                                 500000h * Iyy
//DeadCode RDH 26Mar98 //			add an effect for gear down at high speeds;;RDH 17Feb94
//DeadCode RDH 26Mar98 //                  final rotr_ybl limited by maxiroty
//DeadCode RDH 26Mar98 //      
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcRotas(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	RotasFixedRate_x(ControlledAC);
//DeadCode RDH 26Mar98 	RotasFixedRate_y(ControlledAC);
//DeadCode RDH 26Mar98 	RotasFixedRate_z(ControlledAC);
//DeadCode RDH 26Mar98 }	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98  //Procedure		ManualPilot::RotasFixedRate_x
//DeadCode RDH 26Mar98  //Author		R. Hyde 
//DeadCode RDH 26Mar98  //Date			Tue 19 Mar 1996
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Description	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				pitching moment = MoIx . pitchrate change wrt time
//DeadCode RDH 26Mar98  //				
//DeadCode RDH 26Mar98  //				pitchrate change wrt time = pitching moment / MoIx
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				pitching moment = Macwb + L. CoG_Neutral - Lt.lt + Mmp
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				MoIx	moment of inertia (x axis)
//DeadCode RDH 26Mar98  //				Macwb	pitching moment of wing-body combination about
//DeadCode RDH 26Mar98  //						mean aerodynamic centre
//DeadCode RDH 26Mar98  //				c		mean aerodynamic chord,cm	
//DeadCode RDH 26Mar98  //				L		total wing lift
//DeadCode RDH 26Mar98  //				CoG_Neutral, mm
//DeadCode RDH 26Mar98  //							CoG position - Neutral Position
//DeadCode RDH 26Mar98  //							distance taken from front of wing
//DeadCode RDH 26Mar98  //								nose up if positive
//DeadCode RDH 26Mar98  //				lt		distance between CoG and tail mean aerodynamic centre,cm
//DeadCode RDH 26Mar98  //				Lt		tail lift
//DeadCode RDH 26Mar98  //				Mmp		pitchmoment coefficient of propulsion unit
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				Cacwb	in 1/10000ths
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Inputs		ControlledAC->fly.rotr_xbl pitchrate	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Returns	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98  void	ManualPilot::RotasFixedRate_x(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  {
//DeadCode RDH 26Mar98 	SWord	elevator_sign;
//DeadCode RDH 26Mar98 	UWord	elevator_pos; 
//DeadCode RDH 26Mar98 	SWord	aileron_sign;
//DeadCode RDH 26Mar98 	UWord	aileron_pos; 
//DeadCode RDH 26Mar98 	SWord	rudder_sign;
//DeadCode RDH 26Mar98 	UWord	rudder_pos; 
//DeadCode RDH 26Mar98  	SLong	drotr_x,tx;
//DeadCode RDH 26Mar98  	SLong	moment=0;
//DeadCode RDH 26Mar98 	SLong	angular_momemtum,pitchrate_gyro,d_moment;
//DeadCode RDH 26Mar98  	UWord	 rotr_x_pos;
//DeadCode RDH 26Mar98  	SWord	rotr_x_sign;
//DeadCode RDH 26Mar98 	SLong	wingforce;
//DeadCode RDH 26Mar98 	SWord	sinalfa;
//DeadCode RDH 26Mar98 	SWord	cosalfa;
//DeadCode RDH 26Mar98  	UWord	 rotr_y_pos;
//DeadCode RDH 26Mar98  	SWord	rotr_y_sign;
//DeadCode RDH 26Mar98  	UWord	 rotr_z_pos;
//DeadCode RDH 26Mar98  	SWord	rotr_z_sign;
//DeadCode RDH 26Mar98 	SWord	sintheta,costheta;
//DeadCode RDH 26Mar98 	SLong	pitchrate_from_spin;
//DeadCode RDH 26Mar98 	SLong	tailforce;
//DeadCode RDH 26Mar98 	UWord	aoa_pos;
//DeadCode RDH 26Mar98 	SWord	aoa_sign;
//DeadCode RDH 26Mar98 	UWord	slip_pos;
//DeadCode RDH 26Mar98 	SLong	aoa_factor;
//DeadCode RDH 26Mar98 	SWord	slip_sign;
//DeadCode RDH 26Mar98 	SWord	aoa;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 	Math_Lib.Pos (ControlledAC->fly.aoa,aoa_pos,aoa_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 	Math_Lib.Pos (ControlledAC->fly.slip,slip_pos,slip_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 	aoa_factor =  aoa_pos + slip_pos - ANGLES_15Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 	if (aoa_factor > ANGLES_90Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 		aoa_factor = ANGLES_90Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 	if (aoa_factor < ANGLES_0Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 		aoa_factor = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 	Math_Lib.high_sin_cos ((ANGLES) aoa_factor,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	moment	= ControlledAC->classtype->wingarea 
//DeadCode RDH 26Mar98   				  *	ControlledAC->classtype->chord/10;
//DeadCode RDH 26Mar98  	moment 	= MULDIVSIN (moment,dynamicpressure,100);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	moment	= MULDIVSIN (moment,ControlledAC->classtype->cm_acwb,10000);
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96  	if (cosalfa < 1000)
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 		cosalfa = 1000;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Jun96 	moment	=	moment * ANGLES_FRACT / cosalfa;  
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ((ControlledAC->fly.aoa > ANGLES_90Deg)
//DeadCode RDH 26Mar98 		|| (ControlledAC->fly.aoa < ANGLES_270Deg))				//RDH 24Jul96
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	aoa = ANGLES_180Deg - ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	aoa =  ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98    		if (keyboardcontrol)
//DeadCode RDH 26Mar98 			ControlledAC->fly.cog = ControlledAC->classtype->cog_neut_final;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.high_sin_cos ((Angles)aoa,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 	wingforce =  (lift * cosalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 				 	(totaldrag * sinalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 	moment += wingforce * ControlledAC->fly.cog /1000;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	tailforce =  (taillift * cosalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 				 	(taildrag * sinalfa / ANGLES_FRACT);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	moment -= tailforce * ControlledAC->classtype->lt/100;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 	moment += trim;												//RDH 15Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 10Oct96 	if (ControlledAC->vel <MPH15)
//DeadCode RDH 26Mar98 //DeadCode RDH 10Oct96 		  moment = moment - 8*(MPH15 - ControlledAC->vel);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	if ((SWord) ControlledAC->fly.aoa > (SWord) ControlledAC2->classtype->stallangle)
//DeadCode RDH 26Mar98   	{
//DeadCode RDH 26Mar98   	 	Math_Lib.Pos (((SWord) ControlledAC->fly.rotr_ybl),rotr_y_pos, rotr_y_sign);
//DeadCode RDH 26Mar98   		Math_Lib.high_sin_cos (ControlledAC->pitch,sintheta,costheta);
//DeadCode RDH 26Mar98   
//DeadCode RDH 26Mar98   		pitchrate_from_spin =  - rotr_y_pos * sintheta / ANGLES_FRACT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		ANGLES roll;
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		SWord	sinroll,cosroll;
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 	  	if ( (SWord) ControlledAC->fly.acroll < 0)
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 	  	{
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 	  		roll = -  ControlledAC->fly.acroll;
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		}else
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96   			roll =   ControlledAC->fly.acroll;
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		}
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		if (roll > ANGLES_90Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 			roll = ANGLES_180Deg - roll;
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96   		Math_Lib.high_sin_cos (roll,sinroll,cosroll);
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96   		roll = sinroll * cosroll/ ANGLES_FRACT;
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96   		roll = roll/ ANGLES_FRACT;
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96   		roll = 47 * roll/16;
//DeadCode RDH 26Mar98 //DeadCode RDH 07Jul96   		moment += pitchrate_from_spin * roll;
//DeadCode RDH 26Mar98   		moment += pitchrate_from_spin /4 ;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98   	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98  	drotr_x = MULDIVSIN (moment, 1000, ControlledAC->classtype->moi.x);
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	drotr_x = drotr_x  * FLIGHTMODEL_TIMEFRAME / 100;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 	//cludge to stop nose going down too soon on take off
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 	if ( (ControlledAC->World.Y <= groundlevel)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 		&&	(drotr_x < 0 )
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 			)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 			tx = 3 * drotr_x/4;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 			drotr_x = drotr_x - tx;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 			drotr_x++;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 			if (ControlledAC->vel <= KRITVEL)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 				  ControlledAC->fly.rotr_xbl = ControlledAC->fly.rotr_xbl/2;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Dec96 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  	if ((Save_Data.flightdifficulty [FD_GYRO_EFFECTS])
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97 		&&  (ControlledAC2 == ControlledAC))
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  	{
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  		pitchrate_gyro = 	ControlledAC->classtype->gyroeffectperthou * ControlledAC->fly.rotr_ybl/1000;
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97 		pitchrate_gyro =	pitchrate_gyro * ControlledAC->fly.rpm /
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97 								ControlledAC->classtype->maxrpm;
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97 		ControlledAC->fly.rotr_xbl = ControlledAC->fly.rotr_xbl
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97    								-	pitchrate_gyro;
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (!(ControlledAC->fly.comefrommap))
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 	 	ControlledAC->fly.rotr_xbl +=  drotr_x;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		Math_Lib.Pos (ControlledAC->fly.elevator,elevator_pos,elevator_sign);
//DeadCode RDH 26Mar98 		Math_Lib.Pos (ControlledAC->fly.rudder,rudder_pos,rudder_sign);
//DeadCode RDH 26Mar98 		Math_Lib.Pos (ControlledAC->fly.aileron,aileron_pos,aileron_sign);
//DeadCode RDH 26Mar98  		if 	(	(elevator_pos > 1000)
//DeadCode RDH 26Mar98 			||		(aileron_pos > 1000)
//DeadCode RDH 26Mar98 			||			(rudder_pos > 1000)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 				ControlledAC->fly.comefrommap = FALSE;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98  	//max out at 360deg/s, 6284 mrads/sec
//DeadCode RDH 26Mar98  	Math_Lib.Pos (((SWord) ControlledAC->fly.rotr_xbl),rotr_x_pos, rotr_x_sign);
//DeadCode RDH 26Mar98  	if (rotr_x_pos > 6284 )
//DeadCode RDH 26Mar98  		rotr_x_pos = 6284;
//DeadCode RDH 26Mar98  	if (rotr_x_sign == MathLib::NEGATIVE)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		ControlledAC->fly.rotr_xbl = -rotr_x_pos;
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		ControlledAC->fly.rotr_xbl = rotr_x_pos;
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  }
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98  //Procedure		ManualPilot::RotasFixedRate_y
//DeadCode RDH 26Mar98  //Author		R. Hyde 
//DeadCode RDH 26Mar98  //Date			//RDH 09Apr96
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Description	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				yawing moment = MoIy . yawrate change wrt time
//DeadCode RDH 26Mar98  //				
//DeadCode RDH 26Mar98  //				yawrate change wrt time = yawing moment / MoIy
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				yawing moment = delta wing drag + rudder + gyro effect + slipstream
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				MoIy	moment of inertia (y axis)
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Inputs		ControlledAC->fly.rotr_ybl yawrate	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Returns	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98  void	ManualPilot::RotasFixedRate_y(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  {
//DeadCode RDH 26Mar98  	SLong	drotr_y;
//DeadCode RDH 26Mar98  	SLong	moment;
//DeadCode RDH 26Mar98 	UWord	rotr_y_pos;
//DeadCode RDH 26Mar98  	SWord	rotr_y_sign;
//DeadCode RDH 26Mar98 	SLong	angular_momemtum,yawrate_gyro,d_moment;
//DeadCode RDH 26Mar98 	SLong	rightwingforce,leftwingforce;
//DeadCode RDH 26Mar98 	SWord	sinalfa;
//DeadCode RDH 26Mar98 	SWord	cosalfa;
//DeadCode RDH 26Mar98 	SWord	sinalfaplus;
//DeadCode RDH 26Mar98 	SWord	cosalfaplus;
//DeadCode RDH 26Mar98 	SWord	aoa,slip;
//DeadCode RDH 26Mar98 	SLong	rudderforce;
//DeadCode RDH 26Mar98 	SLong	tmp_rightwinglift,tmp_leftwinglift;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 	if ((ControlledAC->fly.aoa > ANGLES_90Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		|| (ControlledAC->fly.aoa < ANGLES_270Deg))				//RDH 24Jul96
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 			tmp_rightwinglift = -rightwinglift;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 			tmp_leftwinglift = -leftwinglift;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		}else
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 			tmp_rightwinglift = rightwinglift;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 			tmp_leftwinglift = leftwinglift;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		}
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  	Math_Lib.high_sin_cos (ControlledAC->fly.aoa,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  	Math_Lib.high_sin_cos ((ANGLES) (ANGLES_90Deg + ControlledAC->fly.aoa),
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  								sinalfaplus,cosalfaplus);
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  	rightwingforce =  (tmp_rightwinglift * cosalfaplus / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  				 	(rightwingdrag * cosalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  	leftwingforce =  (tmp_leftwinglift * cosalfaplus / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  				 	(leftwingdrag * cosalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	Math_Lib.high_sin_cos (ControlledAC->fly.aoa,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	rightwingforce =  (rightwinglift * sinalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98  				 	(rightwingdrag * cosalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98  	leftwingforce =  (leftwinglift * sinalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98  				 	(leftwingdrag * cosalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 	if ((ControlledAC->fly.aoa > ANGLES_90Deg)
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 		&& (ControlledAC->fly.aoa < ANGLES_270Deg))
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 		{
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 		 	aoa = ANGLES_180Deg - ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 		}
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 		else
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 		{
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 		 	aoa =  ControlledAC->fly.aoa;
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 		}
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 	Math_Lib.high_sin_cos ((ANGLES)aoa,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 	rightwingforce =  (-rightwinglift * sinalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 				 	(rightwingdrag * cosalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 	leftwingforce =  (-leftwinglift * sinalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 				 	(leftwingdrag * cosalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 
//DeadCode RDH 26Mar98  	moment	= (rightwingforce - leftwingforce) * ControlledAC->classtype->wingspan /400;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	if ((ControlledAC->fly.slip > ANGLES_90Deg)
//DeadCode RDH 26Mar98 		|| (ControlledAC->fly.slip < ANGLES_270Deg))			//RDH 24Jul96
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	slip = ANGLES_180Deg - ControlledAC->fly.slip;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	slip =  ControlledAC->fly.slip;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.high_sin_cos ((Angles)slip,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	rudderforce =  (rudderlift * cosalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 				 	(rudderdrag * sinalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	moment	+=	rudderforce * ControlledAC->classtype->lt/100;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	drotr_y = MULDIVSIN (moment, 1000, ControlledAC->classtype->moi.y); 
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	drotr_y = drotr_y  * FLIGHTMODEL_TIMEFRAME / 100;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  	if ((Save_Data.flightdifficulty [FD_GYRO_EFFECTS])
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97 		&&  (ControlledAC2 == ControlledAC))
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  	{
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  	yawrate_gyro = 	ControlledAC->classtype->gyroeffectperthou * ControlledAC->fly.rotr_xbl/1000;
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97 	yawrate_gyro =	yawrate_gyro * ControlledAC->fly.rpm /
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97 								ControlledAC->classtype->maxrpm;
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97    	ControlledAC->fly.rotr_ybl = ControlledAC->fly.rotr_ybl
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97    									+ yawrate_gyro;
//DeadCode RDH 26Mar98 //DeadCode RDH 24Mar97  	}
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	ControlledAC->fly.rotr_ybl +=  drotr_y;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ( (ControlledAC->World.Y <= groundlevel)
//DeadCode RDH 26Mar98 		&& (ControlledAC->vel <= 50)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 		  ControlledAC->fly.rotr_ybl = ControlledAC->fly.rotr_ybl/2;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	//max out at 360deg/s, 6284 mrads/sec
//DeadCode RDH 26Mar98  	Math_Lib.Pos (((SWord) ControlledAC->fly.rotr_ybl),rotr_y_pos, rotr_y_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 07Jul96  	if (rotr_y_pos > 6284 )
//DeadCode RDH 26Mar98 //DeadCode RDH 07Jul96  		rotr_y_pos = 6284;
//DeadCode RDH 26Mar98  	if (rotr_y_pos > 6284 )
//DeadCode RDH 26Mar98  		rotr_y_pos = 6284;
//DeadCode RDH 26Mar98  	if (rotr_y_pos > 4000 )
//DeadCode RDH 26Mar98  		rotr_y_pos = 4000;
//DeadCode RDH 26Mar98  	if (rotr_y_sign == MathLib::NEGATIVE)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		ControlledAC->fly.rotr_ybl = -rotr_y_pos;
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		ControlledAC->fly.rotr_ybl = rotr_y_pos;
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  }
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98  //Procedure		ManualPilot::RotasFixedRate_z
//DeadCode RDH 26Mar98  //Author		R. Hyde 
//DeadCode RDH 26Mar98  //Date			//RDH 09Apr96
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Description	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				rolling moment = MoIz . rollrate change wrt time
//DeadCode RDH 26Mar98  //				
//DeadCode RDH 26Mar98  //				rollrate change wrt time = rolling moment / MoIz
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				rolling moment =  delta winglift 8 span/4 + torque
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //				MoIz	moment of inertia (z axis)
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Inputs		ControlledAC->fly.rotr_zbl rollrate	
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //Returns		//rotr_zbl on millirads/s
//DeadCode RDH 26Mar98  //
//DeadCode RDH 26Mar98  //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98  void	ManualPilot::RotasFixedRate_z(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  {
//DeadCode RDH 26Mar98  	SLong	drotr_z;
//DeadCode RDH 26Mar98  	SLong	moment,torque;
//DeadCode RDH 26Mar98 	UWord	rotr_z_pos;
//DeadCode RDH 26Mar98  	SWord	rotr_z_sign;
//DeadCode RDH 26Mar98 	SLong	rightwingforce,leftwingforce;
//DeadCode RDH 26Mar98 	SWord	sinalfa;
//DeadCode RDH 26Mar98 	SWord	sinalfaplus;
//DeadCode RDH 26Mar98 	SWord	cosalfaplus;
//DeadCode RDH 26Mar98 	SWord	cosalfa;
//DeadCode RDH 26Mar98 	SWord	neutraltorquevel;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 	SLong	tmp_rightwinglift,tmp_leftwinglift;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98  	Math_Lib.high_sin_cos (ControlledAC->fly.aoa,sinalfa,cosalfa);
//DeadCode RDH 26Mar98  	rightwingforce =  (rightwinglift * cosalfa / ANGLES_FRACT) -
//DeadCode RDH 26Mar98  				 	(rightwingdrag * sinalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98  	leftwingforce =  (leftwinglift * cosalfa / ANGLES_FRACT) -
//DeadCode RDH 26Mar98  				 	(leftwingdrag * sinalfa / ANGLES_FRACT);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 	if ((ControlledAC->fly.aoa > ANGLES_90Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		|| (ControlledAC->fly.aoa < ANGLES_270Deg))				//RDH 24Jul96
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 			tmp_rightwinglift = -rightwinglift;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 			tmp_leftwinglift = -leftwinglift;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		}else
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 			tmp_rightwinglift = rightwinglift;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 			tmp_leftwinglift = leftwinglift;
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		}
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 		
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  	Math_Lib.high_sin_cos (ControlledAC->fly.aoa,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  	Math_Lib.high_sin_cos ((ANGLES) (ANGLES_90Deg + ControlledAC->fly.aoa),
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  								sinalfaplus,cosalfaplus);
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  	rightwingforce =  (tmp_rightwinglift * sinalfaplus / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  				 	(rightwingdrag * sinalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  	leftwingforce =  (tmp_leftwinglift * sinalfaplus / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96  				 	(leftwingdrag * sinalfa / ANGLES_FRACT);
//DeadCode RDH 26Mar98 //DeadCode RDH 27Aug96 
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 	Math_Lib.high_sin_cos (ControlledAC->fly.aoa,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 	rightwingforce =  (rightwinglift * cosalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 				 	(rightwingdrag * sinalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 	leftwingforce =  (leftwinglift * cosalfa / ANGLES_FRACT) +
//DeadCode RDH 26Mar98 //TempCode RDH 07Jul96 				 	(leftwingdrag * sinalfa / ANGLES_FRACT); 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	moment	= (leftwingforce - rightwingforce) * ControlledAC->classtype->wingspan /400;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 	if ((Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS])
//DeadCode RDH 26Mar98 	if ((Save_Data.flightdifficulty [FD_TORQUEEFFECTS])
//DeadCode RDH 26Mar98 		&&  (ControlledAC2 == ControlledAC))
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		//torque = thrust * vel * 60 / 2pi * engine rpm
//DeadCode RDH 26Mar98 		torque = thrust * ControlledAC->vel;
//DeadCode RDH 26Mar98 		torque = torque * 95/100;
//DeadCode RDH 26Mar98 		torque = torque/ControlledAC->classtype->maxrpm;
//DeadCode RDH 26Mar98 		moment = moment - torque;
//DeadCode RDH 26Mar98 		//torque compensation due to rigging
//DeadCode RDH 26Mar98 		//	max torque * (v/vmax)^2		
//DeadCode RDH 26Mar98 		neutraltorquevel = (ControlledAC->classtype->cruisevel +
//DeadCode RDH 26Mar98 								ControlledAC->classtype->maxvel)/2;//RDH 03Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		torque =	(ControlledAC->vel * ControlledAC->vel)/
//DeadCode RDH 26Mar98 						neutraltorquevel;
//DeadCode RDH 26Mar98 		torque = torque *ControlledAC->classtype->maxtorque
//DeadCode RDH 26Mar98 					/neutraltorquevel;							//RDH 03Dec96
//DeadCode RDH 26Mar98 		torque = torque * airdensity / 1225;		//1225 = ground level air density//RDH 12Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		moment = moment + torque;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98  	drotr_z = MULDIVSIN (moment, 1000, ControlledAC->classtype->moi.z); 
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	drotr_z = drotr_z  * FLIGHTMODEL_TIMEFRAME / 100;
//DeadCode RDH 26Mar98  	
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 //don't roll if on ground										//RDH 27Aug96
//DeadCode RDH 26Mar98 	if ((ControlledAC->World.Y - groundlevel) > 20)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 	 	ControlledAC->fly.rotr_zbl +=  drotr_z;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 	 	ControlledAC->fly.rotr_zbl = 0;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 	if ((ControlledAC->fly.aoa > ANGLES_30Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 		&& (ControlledAC->fly.aoa < ANGLES_330Deg))
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 		ControlledAC->fly.rotr_zbl = ControlledAC->fly.rotr_zbl/2;
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 	}
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	//max out at 360deg/s, 6284 mrads/sec
//DeadCode RDH 26Mar98  	Math_Lib.Pos (((SWord) ControlledAC->fly.rotr_zbl),rotr_z_pos, rotr_z_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 07Jul96  	if (rotr_z_pos > 6284 )
//DeadCode RDH 26Mar98 //DeadCode RDH 07Jul96  		rotr_z_pos = 6284;
//DeadCode RDH 26Mar98  	if (rotr_z_pos > 6284 )
//DeadCode RDH 26Mar98  		rotr_z_pos = 6284;
//DeadCode RDH 26Mar98  	if (rotr_z_sign == MathLib::NEGATIVE)
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		ControlledAC->fly.rotr_zbl = -rotr_z_pos;
//DeadCode RDH 26Mar98  	}else
//DeadCode RDH 26Mar98  	{
//DeadCode RDH 26Mar98  		ControlledAC->fly.rotr_zbl = rotr_z_pos;
//DeadCode RDH 26Mar98  	}
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  }
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		RDH & Paul
//DeadCode RDH 26Mar98 //Date			14Jun96
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Modified		PD 03Jul96
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcDeltas(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	txrotxb16;
//DeadCode RDH 26Mar98 	SLong	txrotyb16;
//DeadCode RDH 26Mar98 	SLong	txrotzb16;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign;
//DeadCode RDH 26Mar98 	ANGLES	newpitch,
//DeadCode RDH 26Mar98 			newhdg,
//DeadCode RDH 26Mar98 			newroll;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98  	Math_Lib.high_sin_cos(ControlledAC->pitch,sinoldacpitch,cosoldacpitch); 
//DeadCode RDH 26Mar98  	Math_Lib.high_sin_cos(ControlledAC->hdg,sinoldachdg,cosoldachdg);
//DeadCode RDH 26Mar98  	Math_Lib.high_sin_cos(ControlledAC->fly.acroll,sinoldacroll,cosoldacroll);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				//rotr_xbl on millirads/s
//DeadCode RDH 26Mar98 				//0.104 = 64k/200000Pi	
//DeadCode RDH 26Mar98  	txrotxb16	= (ControlledAC->fly.rotr_xbl + ControlledAC->ai.currentbuffet * 4)
//DeadCode RDH 26Mar98 						* FLIGHTMODEL_TIMEFRAME * 104/1000;
//DeadCode RDH 26Mar98  
//DeadCode RDH 26Mar98  	txrotyb16	= (ControlledAC->fly.rotr_ybl + ControlledAC->ai.currentbuffet/4)
//DeadCode RDH 26Mar98 						* FLIGHTMODEL_TIMEFRAME * 104/1000;
//DeadCode RDH 26Mar98 	txrotzb16 	= ControlledAC->fly.rotr_zbl * FLIGHTMODEL_TIMEFRAME * 104/1000;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //pitchrate is required in ac axis
//DeadCode RDH 26Mar98 	ControlledAC->fly.pitchrate = (ControlledAC->fly.pitchrate +
//DeadCode RDH 26Mar98 								(txrotxb16 * 100) / FLIGHTMODEL_TIMEFRAME)/2;
//DeadCode RDH 26Mar98 	ControlledAC->fly.yawrate = (ControlledAC->fly.yawrate +
//DeadCode RDH 26Mar98 								(txrotyb16 * 100) / FLIGHTMODEL_TIMEFRAME)/2;
//DeadCode RDH 26Mar98 	ControlledAC->fly.rollrate = ( ControlledAC->fly.rollrate +
//DeadCode RDH 26Mar98 									(txrotzb16 * 100) / FLIGHTMODEL_TIMEFRAME)/2;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SLong	a,b,c;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	a = txrotxb16; b = txrotyb16; c = txrotzb16;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	TransformAngles(ControlledAC->hdg,
//DeadCode RDH 26Mar98 					ControlledAC->pitch,
//DeadCode RDH 26Mar98 					ControlledAC->fly.acroll,
//DeadCode RDH 26Mar98 					a, b, c);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	newpitch 	= (Angles )a;
//DeadCode RDH 26Mar98 	newhdg 		= (Angles )b;
//DeadCode RDH 26Mar98 	newroll 	= (Angles )c;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	newroll +=  (Angles) (ControlledAC->ai.currentbuffet 
//DeadCode RDH 26Mar98 						* FLIGHTMODEL_TIMEFRAME * 104/1000);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jun96 	Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jun96 	if (deltaroll_pos >ANGLES_90Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jun96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jun96 	 	ControlledAC->fly.croll  = ANGLES (deltaroll + ControlledAC->fly.croll);
//DeadCode RDH 26Mar98 //DeadCode RDH 14Jun96 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ControlledAC->fly.acroll = newroll;
//DeadCode RDH 26Mar98  	ControlledAC->fly.croll  = ANGLES (ControlledAC->fly.croll + (newroll-ControlledAC->fly.acroll));
//DeadCode RDH 26Mar98 //DeadCode RDH 27Oct96 	ControlledAC->fly.turnrate = (ControlledAC->fly.turnrate +
//DeadCode RDH 26Mar98 //DeadCode RDH 27Oct96 								(SLong)(((newhdg-ControlledAC->hdg) * 100) / FLIGHTMODEL_TIMEFRAME))/2;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SLong deltaturn = (SWord)newhdg-(SWord)ControlledAC->hdg; 	//RDH 27Oct96
//DeadCode RDH 26Mar98 	deltaturn = deltaturn * 100 / FLIGHTMODEL_TIMEFRAME;		//RDH 27Oct96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ControlledAC->fly.turnrate = (ControlledAC->fly.turnrate + deltaturn)/2;//RDH 27Oct96
//DeadCode RDH 26Mar98  	ControlledAC->pitch = newpitch;
//DeadCode RDH 26Mar98   	ControlledAC->hdg   = newhdg;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //flip checks
//DeadCode RDH 26Mar98 	if (ControlledAC->pitch == ANGLES_90Deg)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		ControlledAC->pitch += ANGLES_BitDeg;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (ControlledAC->pitch == ANGLES_270Deg)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			ControlledAC->pitch -= ANGLES_BitDeg;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (	(ControlledAC->pitch > ANGLES_90Deg)				//RDH 24Jul96
//DeadCode RDH 26Mar98 		|| (ControlledAC->pitch < ANGLES_270Deg))				//RDH 24Jul96
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 			ControlledAC->pitch  = ANGLES_0Deg-ControlledAC->pitch;
//DeadCode RDH 26Mar98 			ControlledAC->pitch += ANGLES_180Deg;
//DeadCode RDH 26Mar98 			ControlledAC->hdg += ANGLES_180Deg;
//DeadCode RDH 26Mar98 			ControlledAC->fly.acroll += ANGLES_180Deg;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 #ifndef	PUBLICVERSION
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcDeltasDebug
//DeadCode RDH 26Mar98 //Author		Paul.   
//DeadCode RDH 26Mar98 //Date			Mon 1 Jul 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	code to soak test 'TransformAngles'
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void ManualPilot::CalcDeltasDebug()
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	FILE* debugfo;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	ANGLES	achdg,acroll,acpitch;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	ANGLES	thdg,tpitch,troll;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	SLong	tx,ty,tz;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	SLong	a,b,c;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	SLong	j;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	SWord	temp;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	debugfo = fopen("\\fly\\src\\trnsang.err","wt");
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	if (debugfo!=NULL)
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	{
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 		fprintf(debugfo,
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 				"AIRCRAFT                     |REQ. DELTAS              |TRANSFORMED DELTAS           \n");
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 		fprintf(debugfo,
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 				"-----------------------------+-------------------------+-----------------------------\n");
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 		for (j=(UWord )0;j<0x010000;j+=ANGLES_1Deg)
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 		{
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			achdg = (ANGLES)50489;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			acpitch = (ANGLES)73;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			acroll = (ANGLES)65240;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			temp = (SWord)-7;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			tx = (SLong)temp;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			temp = (SWord)-62;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			ty = (SLong)temp;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			temp = (SWord)-22;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			tz = (SLong)temp;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			a = tx; b = ty; c = tz;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			TransformAngles(achdg,acpitch,acroll,
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 							a,b,c);
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			thdg = (ANGLES )b;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			tpitch = (ANGLES )a;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			troll = (ANGLES )c;
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 			fprintf(debugfo,
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 					"HDG %4x PTCH %4x ROLL %4x | TX %4x TY %4x TZ %4x | HDG %4x PTCH %4x ROLL %4x\n",
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 					achdg, acpitch,acroll,
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 					tx, ty, tz,
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 					thdg, tpitch, troll);
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 		}
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 		fclose(debugfo);	
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	}
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 
//DeadCode RDH 26Mar98 //DeadCode JIM 12Jul96 	_Error.EmitSysErr(__FILE__":Created '\\FLY\\SRC\\TRNSANG.ERR'");
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 #endif
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		TransformAngles
//DeadCode RDH 26Mar98 //Author		Paul.   
//DeadCode RDH 26Mar98 //Date			Mon 1 Jul 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void ManualPilot::TransformAngles(	ANGLES thdg, ANGLES tpitch, ANGLES troll,
//DeadCode RDH 26Mar98 									SLong& a, SLong& b, SLong& c)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	MATRIX		tma,tmb,tmc;									//PD 25Jul96
//DeadCode RDH 26Mar98 	MATRIX_PTR	mDelta 	= &tma;									//PD 25Jul96
//DeadCode RDH 26Mar98 	MATRIX_PTR	mNegHdg = &tmb;									//PD 25Jul96
//DeadCode RDH 26Mar98 	MATRIX_PTR	mTemp	= &tmc;									//PD 25Jul96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ANGLES	cdhdg,cdpitch,cdroll;
//DeadCode RDH 26Mar98 	SLong	x, y, z;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	_matrix.generate2((Angles )b,(Angles)a,(Angles)c,mDelta);	//PD 25Jul96
//DeadCode RDH 26Mar98 	_matrix.generate2(thdg,tpitch,troll,mTemp);					//PD 25Jul96
//DeadCode RDH 26Mar98 	_matrix.multiply(mDelta,mTemp);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	x = 0; y = 0; z = 0x7FFF;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	_matrix.rotate(mDelta,x,y,z);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	cdhdg = Math_Lib.HighArcTan((SWord )x,(SWord )z);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	_matrix.generateh(ANGLES_0Deg-cdhdg, mNegHdg);
//DeadCode RDH 26Mar98 	_matrix.rotate(mNegHdg,x,y,z);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	cdpitch = Math_Lib.HighArcTan((SWord )y,(SWord )z);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	x = 0; y = 0x7FFF; z = 0;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	_matrix.rotate(mDelta,x,y,z);
//DeadCode RDH 26Mar98 	_matrix.rotate(mNegHdg,x,y,z);
//DeadCode RDH 26Mar98 	_matrix.generatep(ANGLES_0Deg-cdpitch, mTemp);
//DeadCode RDH 26Mar98 	_matrix.rotate(mTemp,x,y,z);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	cdroll = Math_Lib.HighArcTan((SWord )x,(SWord )y);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode PD 25Jul96 	delete (mDelta); delete (mNegHdg); delete (mTemp);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	a = cdpitch; b = cdhdg; c = cdroll;
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Wed 30 Aug 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //	   Calculates delta (v)Pitch, delta vel, delta (v)Heading
//DeadCode RDH 26Mar98 //               PITCH:
//DeadCode RDH 26Mar98 //               Force = (Thrust*SinAoA + Lift)*CosOldRoll - Weight*CosOldPitch
//DeadCode RDH 26Mar98 //               delta Pitch = [Force * CycleT] / (vel * Mass)
//DeadCode RDH 26Mar98 //                             ( * QU2/PI100 for Rowan units)
//DeadCode RDH 26Mar98 //                             if on ground only pos delta Pitch
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //               VELOCITY:
//DeadCode RDH 26Mar98 //               Force = Thrust*CosAoA - Drag - Weight*SinPitch
//DeadCode RDH 26Mar98 //               delta vel = (Force * CycleT) / Mass
//DeadCode RDH 26Mar98 //                             ( / 10 to adapt units)
//DeadCode RDH 26Mar98 //                             if on ground only pos delta Vel
//DeadCode RDH 26Mar98 //               HEADING:
//DeadCode RDH 26Mar98 //               Force = (Thrust*SinAoA + Lift)*SinOldRoll /CosPitch
//DeadCode RDH 26Mar98 //               delta Hdg = (Force * CycleT)/ (vel * Mass)
//DeadCode RDH 26Mar98 //                             ( * QU2/PI100*100 for Rowan units)         
//DeadCode RDH 26Mar98 //                             if on ground no delta Hdg
//DeadCode RDH 26Mar98 //                VFLIP check: Heading and Roll adapted if the V_vector flipped
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcVel(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SWord	velocity;
//DeadCode RDH 26Mar98 	SWord	sinalfa;
//DeadCode RDH 26Mar98 	SWord	cosalfa;
//DeadCode RDH 26Mar98 	SWord	sinoldpitch;
//DeadCode RDH 26Mar98 	SWord	cosoldpitch;
//DeadCode RDH 26Mar98 	SWord	sinoldroll;	
//DeadCode RDH 26Mar98 	SWord	cosoldroll;	
//DeadCode RDH 26Mar98 	SLong	thr_sinalfa;	
//DeadCode RDH 26Mar98 	SLong	netvertforce;	
//DeadCode RDH 26Mar98 	SLong	deltaforce;
//DeadCode RDH 26Mar98 	SLong	deltapitch,deltahdg,deltaroll;			
//DeadCode RDH 26Mar98 	ANGLES	newpitch;
//DeadCode RDH 26Mar98 	SLong	nethoriforce,netweight;	
//DeadCode RDH 26Mar98 	ANGLES	newhdg;	
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign,deltacroll;
//DeadCode RDH 26Mar98 	AircraftAnimData*	adptr;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	deltacroll = ControlledAC->fly.acroll - ControlledAC->fly.croll;	
//DeadCode RDH 26Mar98 	Math_Lib.Pos ((SWord) deltacroll,deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 	if (deltaroll_pos > 50)
//DeadCode RDH 26Mar98 			deltaroll_pos = 50;
//DeadCode RDH 26Mar98 	deltacroll = Math_Lib.UseSign (deltaroll_pos,deltaroll_sign);
//DeadCode RDH 26Mar98 	ControlledAC->fly.croll += (Angles)deltacroll;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	mass = ControlledAC->fly.weight / 10;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ControlledAC->fly.oldvelx = ControlledAC->velx;
//DeadCode RDH 26Mar98 	ControlledAC->fly.oldvely = ControlledAC->vely;
//DeadCode RDH 26Mar98 	ControlledAC->fly.oldvelz = ControlledAC->velz;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	velocity = ControlledAC->vel;
//DeadCode RDH 26Mar98 	if (velocity < 40)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		velocity = 40;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //don't put max on lift
//DeadCode RDH 26Mar98 //**	if (lift > 0x7fff)
//DeadCode RDH 26Mar98 //**	{
//DeadCode RDH 26Mar98 //**		lift = 0x7fff;
//DeadCode RDH 26Mar98 //**	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.high_sin_cos (ControlledAC->fly.aoa,sinalfa,cosalfa);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.high_sin_cos (ControlledAC->fly.cpitch,sinoldpitch,cosoldpitch);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	Math_Lib.high_sin_cos (ControlledAC->fly.croll,sinoldroll,cosoldroll);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	SWord	temp_gforce =  	ControlledAC->fly.gforce;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	ControlledAC->fly.gforce = lift - (cosoldroll * ControlledAC->fly.weight / ANGLES_FRACT);
//DeadCode RDH 26Mar98  	ControlledAC->fly.gforce = 10 + ControlledAC->fly.gforce * 10 / ControlledAC->fly.weight;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  	if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (	(ControlledAC->fly.gforce >=40)
//DeadCode RDH 26Mar98 			&&	(temp_gforce <40)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				adptr = (AircraftAnimData *)ControlledAC->Anim;
//DeadCode RDH 26Mar98 				UWord	lcldamflag;
//DeadCode RDH 26Mar98 //DeadCode RJS 09Jun97 				lcldamflag = adptr->dammageflags;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 14Nov96 				if  (	(adptr->dammageflags & 0xaaaa)		//binary 1010 1010 1010 1010
//DeadCode RDH 26Mar98 //DeadCode RDH 14Nov96 					||	(adptr->damageflags2 & 0xaaaa)		//binary 1010 1010 1010 1010
//DeadCode RDH 26Mar98 //DeadCode RDH 14Nov96 					)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 				if (	(((lcldamflag>>BF_LBWing) & BS_DEAD) > BS_DAMLV2)//RDH 05Dec96
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 					||	(((lcldamflag>>BF_RBWing) & BS_DEAD) > BS_DAMLV2)//RDH 05Dec96
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 						)
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 				if (	(adptr->BOTLEFTWING >= BS_DAMLV2)		//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 					||	(adptr->BOTRIGHTWING >= BS_DAMLV2)	)	//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 				{
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 					SHAPE.ForceDamage(ControlledAC,&adptr->TOPRIGHTWING,BS_DEAD);
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 					SHAPE.ForceDamage(ControlledAC,&adptr->TOPLEFTWING,BS_DEAD);
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 					SHAPE.ForceDamage(ControlledAC,&adptr->BOTRIGHTWING,BS_DEAD);
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 					SHAPE.ForceDamage(ControlledAC,&adptr->BOTLEFTWING,BS_DEAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 					Trans_Obj.SetAircraftDammage(ControlledAC,*myworld,BF_RTWing,BS_DEAD,FALSE);//RJS 13Aug96
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 					Trans_Obj.SetAircraftDammage(ControlledAC,*myworld,BF_LTWing,BS_DEAD,FALSE);//RJS 13Aug96
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 					Trans_Obj.SetAircraftDammage(ControlledAC,*myworld,BF_RBWing,BS_DEAD,FALSE);//RJS 13Aug96
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 					Trans_Obj.SetAircraftDammage(ControlledAC,*myworld,BF_LBWing,BS_DEAD,FALSE);//RJS 13Aug96
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 					_DPlay.NewCollision (ControlledAC, NULL, CP_PILOTDAMAGE, 0);	//ARM 11Oct96
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 23Sep96 			if ( ControlledAC->movecode == AUTO_DEATHSEQUENCE )
//DeadCode RDH 26Mar98 //DeadCode RDH 23Sep96 			{
//DeadCode RDH 26Mar98 //TempCode RDH 14Aug96 				Trans_Obj.LaunchDeadACPart(ControlledAC,
//DeadCode RDH 26Mar98 //TempCode RDH 14Aug96 					BF_RBTWing,*myworld);
//DeadCode RDH 26Mar98 //TempCode RDH 14Aug96 				Trans_Obj.LaunchDeadACPart(ControlledAC,
//DeadCode RDH 26Mar98 //TempCode RDH 14Aug96 					BF_LBWing,*myworld);
//DeadCode RDH 26Mar98 //DeadCode RDH 23Sep96 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		if (	(ControlledAC->fly.gforce >=50)
//DeadCode RDH 26Mar98 			&&	(temp_gforce <50)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 				_Miles.PlayOnce (FIL_SFX_CREAK7,NULL);			//RJS 27Nov96
//DeadCode RDH 26Mar98 		if (	(ControlledAC->fly.gforce >=80)
//DeadCode RDH 26Mar98 			&&	(temp_gforce <80)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				SWord rand = Math_Lib.rnd(2);  
//DeadCode RDH 26Mar98 				if (rand ==0) 
//DeadCode RDH 26Mar98 					_Miles.PlayOnce (FIL_SFX_OUT_OF_BREATH1,NULL);//RJS 22Nov96
//DeadCode RDH 26Mar98 				else
//DeadCode RDH 26Mar98 					_Miles.PlayOnce (FIL_SFX_OUT_OF_BREATH2,NULL);//RJS 22Nov96
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	thr_sinalfa = sinalfa * thrust / ANGLES_FRACT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	deltaforce = (thrust * cosalfa / ANGLES_FRACT)
//DeadCode RDH 26Mar98 						- (sinoldpitch * ControlledAC->fly.weight / ANGLES_FRACT);
//DeadCode RDH 26Mar98 	if	(	(Save_Data.flightdifficulty [FD_POWERBOOST])		//RDH 07Dec96
//DeadCode RDH 26Mar98 		&& 	(ControlledAC->fly.thrustpercent < 20)				//RDH 07Dec96
//DeadCode RDH 26Mar98 		)														//RDH 07Dec96
//DeadCode RDH 26Mar98 		totaldrag = totaldrag * 2;								//RDH 07Dec96
//DeadCode RDH 26Mar98 	deltaforce -=  totaldrag;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //to account for the braking effect of the prop we introduce a cludge//RDH 24May96
//DeadCode RDH 26Mar98 	if  (	(deltaforce > 0)
//DeadCode RDH 26Mar98 		&&	(ControlledAC->vel > ControlledAC->classtype->maxvel)
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (ControlledAC->vel > ControlledAC->classtype->maxdivevel)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			deltaforce = 0;
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			deltaforce = deltaforce *
//DeadCode RDH 26Mar98 					( 100 - 
//DeadCode RDH 26Mar98 //DeadCode RDH 04Dec96 					(ControlledAC->fly.vel_mms - ControlledAC->classtype->minvel * 100)/
//DeadCode RDH 26Mar98 //DeadCode RDH 04Dec96 					(ControlledAC->classtype->maxdivevel - ControlledAC->classtype->minvel)
//DeadCode RDH 26Mar98 //DeadCode RDH 04Dec96 					)/100;
//DeadCode RDH 26Mar98 					(ControlledAC->fly.vel_mms - ControlledAC->classtype->maxvel * 100)/
//DeadCode RDH 26Mar98 					(ControlledAC->classtype->maxdivevel - ControlledAC->classtype->maxvel)
//DeadCode RDH 26Mar98 					)/100;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		if (	(ControlledAC->vel >	 ControlledAC->classtype->maxsafevel)
//DeadCode RDH 26Mar98 				&&  (!(Save_Data.flightdifficulty [FD_POWERBOOST]))
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			AircraftAnimData*	adptr;							//RJS 21Feb97
//DeadCode RDH 26Mar98  			adptr = (AircraftAnimData *)ControlledAC->Anim;		//RJS 21Feb97
//DeadCode RDH 26Mar98 //Old_Code RDH 26Jul96 			UWord	lcldamflag;
//DeadCode RDH 26Mar98 //Old_Code RDH 26Jul96 			lcldamflag = adptr->dammageflags;
//DeadCode RDH 26Mar98 //Old_Code RDH 26Jul96 			lcldamflag	|= BS_DEAD<<BF_RTWing;
//DeadCode RDH 26Mar98 //Old_Code RDH 26Jul96 			lcldamflag	|= BS_DEAD<<BF_LTWing;
//DeadCode RDH 26Mar98 //Old_Code RDH 26Jul96 			adptr->dammageflags = lcldamflag;					//RDH 26Jul96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 			SHAPE.ForceDamage(ControlledAC,&adptr->TOPRIGHTWING,BS_DEAD);
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 			SHAPE.ForceDamage(ControlledAC,&adptr->TOPLEFTWING,BS_DEAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 			Trans_Obj.SetAircraftDammage(ControlledAC,*myworld,BF_RTWing,BS_DEAD,FALSE);//RJS 13Aug96
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 			Trans_Obj.SetAircraftDammage(ControlledAC,*myworld,BF_LTWing,BS_DEAD,FALSE);//RJS 13Aug96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			_DPlay.NewCollision (ControlledAC, NULL, CP_PILOTDAMAGE,0);	//ARM 11Oct96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //TempCode RDH 14Aug96 			Trans_Obj.LaunchDeadACPart(ControlledAC,
//DeadCode RDH 26Mar98 //TempCode RDH 14Aug96 				BF_LTWing,*myworld);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}									
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //in the following equation (m/s to cm/s over cs to s)100/100 cancels out
//DeadCode RDH 26Mar98 //DeadCode RJS 03Dec96 	if (deltaforce < 32)										//RDH 29Nov96
//DeadCode RDH 26Mar98 //DeadCode RJS 03Dec96 		deltaforce = 32;										//RJS 03Dec96
//DeadCode RDH 26Mar98 	ControlledAC->fly.vel_mms += (10 * deltaforce * FLIGHTMODEL_TIMEFRAME) / ( mass );
//DeadCode RDH 26Mar98 	if (ControlledAC->fly.vel_mms < 0)
//DeadCode RDH 26Mar98 		ControlledAC->fly.vel_mms = 0;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	netvertforce =	thr_sinalfa + lift;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	netweight =	MULSHSIN ( ControlledAC->fly.weight, cosoldpitch, 15);//RDH 14Mar96
//DeadCode RDH 26Mar98 	netvertforce -= MULSHSIN (netweight,cosoldroll,15);
//DeadCode RDH 26Mar98 //PITCHCOEFF = 	WORD_FRACT / TWOPI100			
//DeadCode RDH 26Mar98 	deltapitch = netvertforce * FLIGHTMODEL_TIMEFRAME * PITCHCOEFF;
//DeadCode RDH 26Mar98 	deltapitch = deltapitch /( velocity * mass /10);
//DeadCode RDH 26Mar98 	if (	(ControlledAC->World.Y <= groundlevel)
//DeadCode RDH 26Mar98 		&&	(deltapitch < 0 )
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 			deltapitch = 0;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	nethoriforce = MULSHSIN (netweight,sinoldroll,15);
//DeadCode RDH 26Mar98 	nethoriforce += sideforce;
//DeadCode RDH 26Mar98 	deltahdg =  nethoriforce * FLIGHTMODEL_TIMEFRAME * PITCHCOEFF;
//DeadCode RDH 26Mar98  	deltahdg = deltahdg / (velocity * mass/10);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	deltaroll 	= ControlledAC->fly.rotr_zbl * FLIGHTMODEL_TIMEFRAME * 104/1000;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	TransformAngles(ControlledAC->fly.chdg,
//DeadCode RDH 26Mar98 					ControlledAC->fly.cpitch,
//DeadCode RDH 26Mar98 					ControlledAC->fly.croll,
//DeadCode RDH 26Mar98 					deltapitch, deltahdg, deltaroll);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ControlledAC->fly.chdg = (Angles) deltahdg;
//DeadCode RDH 26Mar98 	ControlledAC->fly.cpitch = (Angles) deltapitch;
//DeadCode RDH 26Mar98 	ControlledAC->fly.croll = (Angles)deltaroll;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98  }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Fri 8 Sep 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //   Calculates
//DeadCode RDH 26Mar98 //               - MobileItem VelX, VelY, VelZ, VelHori
//DeadCode RDH 26Mar98 //               - Cheat for making almost straight_and_level completely level
//DeadCode RDH 26Mar98 //               - (v)Roll, this is the roll of an imaginary velocity ac.
//DeadCode RDH 26Mar98 //               - AoA : angle between ac longit.axis and Vproj on symm plane
//DeadCode RDH 26Mar98 //               - Slip: angle between V_vector and symm plane 
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::VcoAlfaBeta(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 		SWord	velocity;
//DeadCode RDH 26Mar98 	SLong	c_vx,c_vy,c_vz;
//DeadCode RDH 26Mar98 	SWord	sintheta,costheta;
//DeadCode RDH 26Mar98 	SWord	sinphi,cosphi;
//DeadCode RDH 26Mar98 	SWord	sinpsi,cospsi;
//DeadCode RDH 26Mar98 	SWord	deltahdg;
//DeadCode RDH 26Mar98 	SWord	sin_deltahdg;
//DeadCode RDH 26Mar98 	SWord	cos_deltahdg;
//DeadCode RDH 26Mar98 	SWord	slip;
//DeadCode RDH 26Mar98 	SWord	sinv_hdg,cosv_hdg;
//DeadCode RDH 26Mar98 	SLong	cosphi_sintheta;
//DeadCode RDH 26Mar98 	SWord	cosaoa,sinaoa;
//DeadCode RDH 26Mar98 	SLong	sinphi_sintheta;
//DeadCode RDH 26Mar98 	SWord	sinv_theta,cosv_theta;
//DeadCode RDH 26Mar98 	SLong	localt1,localt2,localt6,localt8;
//DeadCode RDH 26Mar98 	SLong	sinphi_costheta;
//DeadCode RDH 26Mar98 	SLong	temp1;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if ((ControlledAC->World.Y <= groundlevel) && (ControlledAC->vel < MINVELO))
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		ControlledAC->velx = 0;	
//DeadCode RDH 26Mar98 		ControlledAC->vely = 0;	
//DeadCode RDH 26Mar98 		ControlledAC->fly.cvely = 0;							//RDH 04Oct96
//DeadCode RDH 26Mar98 		ControlledAC->velz = 0;	
//DeadCode RDH 26Mar98 		ControlledAC->velhori = 0;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		velocity = ControlledAC->vel;
//DeadCode RDH 26Mar98 		Math_Lib.high_sin_cos (ControlledAC->fly.cpitch,sinv_theta,cosv_theta);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		c_vy =  - (velocity * sinv_theta) / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		ControlledAC->velhori = (SWord) ((velocity * cosv_theta)/ ANGLES_FRACT);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		Math_Lib.high_sin_cos (ControlledAC->fly.chdg, sinv_hdg, cosv_hdg);
//DeadCode RDH 26Mar98 		c_vx =  ControlledAC->velhori * sinv_hdg / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		c_vz =  ControlledAC->velhori * cosv_hdg / ANGLES_FRACT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //no ground cheats introduced as in old model
//DeadCode RDH 26Mar98 		ControlledAC->velx = (SWord) c_vx;
//DeadCode RDH 26Mar98 		ControlledAC->fly.cvely = (SWord) c_vy;
//DeadCode RDH 26Mar98 		ControlledAC->vely = (SWord) -ControlledAC->fly.cvely;
//DeadCode RDH 26Mar98 		ControlledAC->velz = (SWord) c_vz;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		Math_Lib.high_sin_cos (ControlledAC->pitch,sintheta,costheta);
//DeadCode RDH 26Mar98  		Math_Lib.high_sin_cos (ControlledAC->fly.acroll, sinphi, cosphi);
//DeadCode RDH 26Mar98 		Math_Lib.high_sin_cos (ControlledAC->hdg,sinpsi,cospsi);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		deltahdg = ControlledAC->fly.chdg - ControlledAC->hdg;
//DeadCode RDH 26Mar98 		Math_Lib.high_sin_cos((Angles) deltahdg,sin_deltahdg,cos_deltahdg);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		sinphi_sintheta = sinphi * sintheta / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		localt1 = (cos_deltahdg * sinphi_sintheta) / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		localt1 = localt1 * sinv_theta / ANGLES_FRACT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		temp1 =  (cosphi * sin_deltahdg) / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		temp1 =  (temp1 * sinv_theta) / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		localt1 += temp1;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		sinphi_costheta =  (sinphi * costheta) / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		temp1 =  (sinphi_costheta * cosv_theta) / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		localt1 += temp1;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		if (localt1 <=0)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			localt1 += 1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		localt8 =  (cosphi * cos_deltahdg) / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		temp1 =    (sin_deltahdg * sinphi_sintheta) / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		localt8 -= temp1;										//RDH 18May96
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 //The calculation for croll is dubious
//DeadCode RDH 26Mar98 //Sometimes positive acrolls give negative crolls which produce the wrong
//DeadCode RDH 26Mar98 //effects in flight. The above needs checking, in the meantime
//DeadCode RDH 26Mar98 //use the cheats marked %%%										//RDH 19May96
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		if ((localt1 == 0) && (localt8 == 0))
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 			ControlledAC->fly.croll =ControlledAC->fly.croll;
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		}else
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 			ControlledAC->fly.croll = (ANGLES) Math_Lib.arctan (localt1,localt8);
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 		}
//DeadCode RDH 26Mar98 //DeadCode RDH 08Jul96 
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 //TransVtoBody
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //z
//DeadCode RDH 26Mar98 		localt1 =  costheta * cospsi / ANGLES_FRACT;
//DeadCode RDH 26Mar98 		localt1 *= c_vz;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		temp1 = (costheta * sinpsi / ANGLES_FRACT);
//DeadCode RDH 26Mar98 		temp1 *= c_vx;
//DeadCode RDH 26Mar98 		localt1 += temp1;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 07Jun96 		temp1 -= sintheta  * c_vy;
//DeadCode RDH 26Mar98 		temp1 = - sintheta  * c_vy;
//DeadCode RDH 26Mar98 		localt1 += temp1;
//DeadCode RDH 26Mar98 		localt2 = localt1 / ANGLES_FRACT; 
//DeadCode RDH 26Mar98 //x
//DeadCode RDH 26Mar98 		localt6  =  (sinphi_sintheta * cospsi / ANGLES_FRACT) * c_vz;
//DeadCode RDH 26Mar98 		localt6 -=  (cosphi * sinpsi / ANGLES_FRACT) * c_vz;
//DeadCode RDH 26Mar98 		localt6 +=  (sinphi_sintheta * sinpsi /ANGLES_FRACT) * c_vx;
//DeadCode RDH 26Mar98 		localt6 +=  ((cosphi * cospsi / ANGLES_FRACT) * c_vx);
//DeadCode RDH 26Mar98 		localt6 += sinphi_costheta * c_vy;
//DeadCode RDH 26Mar98 		localt1  = localt6 / ANGLES_FRACT;				//RDH 03Nov95
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		cosphi_sintheta  =  (cosphi * sintheta / ANGLES_FRACT);
//DeadCode RDH 26Mar98 //y
//DeadCode RDH 26Mar98 		localt6  = ((cosphi_sintheta * cospsi)/ ANGLES_FRACT) * c_vz;
//DeadCode RDH 26Mar98 		localt6 += (sinphi * sinpsi / ANGLES_FRACT) * c_vz;
//DeadCode RDH 26Mar98 		localt6 += (cosphi_sintheta * sinpsi / ANGLES_FRACT) * c_vx;
//DeadCode RDH 26Mar98 		localt6 -= (sinphi * cospsi / ANGLES_FRACT) * c_vx;
//DeadCode RDH 26Mar98 		localt6 += (cosphi * costheta / ANGLES_FRACT) * c_vy;
//DeadCode RDH 26Mar98 		localt6  = localt6 / ANGLES_FRACT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //aoa = tan-1 y/z
//DeadCode RDH 26Mar98 			ControlledAC->fly.aoa = (Angles) (Math_Lib.arctan (localt6,localt2)
//DeadCode RDH 26Mar98 						  				+ ControlledAC->classtype->wing_incidence);//JIM 02Apr96
//DeadCode RDH 26Mar98 		Math_Lib.high_sin_cos (ControlledAC->fly.aoa,sinaoa,cosaoa);
//DeadCode RDH 26Mar98 //slip = tan-1 x/z
//DeadCode RDH 26Mar98 		localt6  =  localt1 * cosaoa /ANGLES_FRACT;
//DeadCode RDH 26Mar98 		if ((localt6 == 0) && (localt2 == 0))
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			slip = 0;
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		 	slip = Math_Lib.arctan (localt6,localt2);
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //not convinced by these boundary conditions					//RDH 19May96
//DeadCode RDH 26Mar98 //**		if (slip > ANGLES_90Deg)
//DeadCode RDH 26Mar98 //**		{
//DeadCode RDH 26Mar98 //**			slip -= ANGLES_180Deg;
//DeadCode RDH 26Mar98 //**		}
//DeadCode RDH 26Mar98 //**
//DeadCode RDH 26Mar98 //**		if (slip < ANGLES_270Deg)
//DeadCode RDH 26Mar98 //**		{
//DeadCode RDH 26Mar98 //**			slip += ANGLES_180Deg;
//DeadCode RDH 26Mar98 //**		}
//DeadCode RDH 26Mar98 //**
//DeadCode RDH 26Mar98 //**		if ((slip == ANGLES_90Deg) || (slip == -ANGLES_90Deg))
//DeadCode RDH 26Mar98 //**		{
//DeadCode RDH 26Mar98 //**			slip = 0;
//DeadCode RDH 26Mar98 //**		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		ControlledAC->fly.slip =(Angles)slip;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		MoveToGrndPitchRoll
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Thu 12 Sep 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::MoveToGrndPitchRoll(AirStrucPtr const ControlledAC,ANGLES grndroll,ANGLES grndpitch)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	if (((UWord) ControlledAC->fly.cpitch) > ANGLES_180Deg)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		ControlledAC->fly.cpitch = grndpitch;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if (((UWord) ControlledAC->pitch) > ANGLES_180Deg)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		ControlledAC->pitch = grndpitch;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if (((UWord) ControlledAC->pitch) > (ControlledAC->classtype->deckangle + grndpitch))
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			ControlledAC->pitch = ControlledAC->classtype->deckangle+ grndpitch;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Oct96 		}else
//DeadCode RDH 26Mar98 //DeadCode RDH 20Oct96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 20Oct96 			ControlledAC->pitch = grndpitch;
//DeadCode RDH 26Mar98 //DeadCode RDH 20Oct96 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if ((ControlledAC->roll- grndroll) > 0)
//DeadCode RDH 26Mar98 		ControlledAC->roll -= (Angles)FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 	else
//DeadCode RDH 26Mar98 		ControlledAC->roll += (Angles)FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		CalcGrndHdg
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Wed 5 Jun 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	works out slip on ground	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcGrndInfo(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98  	SWord	sinwind,coswind,dummy,ghdg;
//DeadCode RDH 26Mar98 	SLong	gvel;
//DeadCode RDH 26Mar98 	SLong deltax;
//DeadCode RDH 26Mar98  	SLong deltay;
//DeadCode RDH 26Mar98 	SLong deltaz;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	  	Math_Lib.high_sin_cos(Save_Data.wind.direction,sinwind,coswind); 
//DeadCode RDH 26Mar98 //DeadCode RDH 24Oct96 	 	deltax = ControlledAC->velx + Save_Data.wind.velx;
//DeadCode RDH 26Mar98 //DeadCode RDH 24Oct96 	 	deltaz = ControlledAC->velz + Save_Data.wind.velz;
//DeadCode RDH 26Mar98 	 	deltax = ControlledAC->velx + MMC.wind.velx;
//DeadCode RDH 26Mar98 	 	deltaz = ControlledAC->velz + MMC.wind.velz;
//DeadCode RDH 26Mar98 	 	deltay = ControlledAC->vely;
//DeadCode RDH 26Mar98 		Math_Lib.Intercept (deltax,deltay,deltaz,gvel,ghdg,dummy);
//DeadCode RDH 26Mar98 		grndvel = (SWord) gvel;
//DeadCode RDH 26Mar98 		grndhdg = (Angles) ghdg;
//DeadCode RDH 26Mar98 		if (ControlledAC->manoeuvretime != 0) 
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if (Save_Data.flightdifficulty [FD_WINDEFFECTS])
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 			 	ControlledAC->fly.slip = (Angles)((SWord) (grndhdg - ControlledAC->hdg)/4);
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 //can't put 0 in here, when aircraft to pointing high, it stops it yawing down
//DeadCode RDH 26Mar98 //TempCode RDH 10Jul96 			 	ControlledAC->fly.slip = ANGLES_0Deg;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Procedure		ChkLandedLocation
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date			Fri 29 Nov 1996
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void operator ++ (UniqueID& i,int) {i=UniqueID(i+1);}
//DeadCode RDH 26Mar98 void	ManualPilot::ChkLandedLocation(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	UniqueID	tmpUID,StartBand,EndBand;
//DeadCode RDH 26Mar98 	SLong	reddist,bluedist,reddistx,bluedistx,reddistz,bluedistz;
//DeadCode RDH 26Mar98 	SLong	homedist,enemydist;
//DeadCode RDH 26Mar98 	tmpUID = (UniqueID) RedAirfieldBAND;
//DeadCode RDH 26Mar98 	EndBand =  (UniqueID) BlueAirfieldBAND;
//DeadCode RDH 26Mar98 	ItemBasePtr		tmpitem;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	reddist = 0x7fffffff;
//DeadCode RDH 26Mar98 	while 	(tmpUID < EndBand)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		tmpitem=MobileItem::currworld->ConvertPtrUID(tmpUID);
//DeadCode RDH 26Mar98 		if 	(tmpitem!=NULL)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98 			reddistx = tmpitem->World.X - ControlledAC->World.X;
//DeadCode RDH 26Mar98 			if (reddistx < 0)
//DeadCode RDH 26Mar98 				reddistx = -reddistx;
//DeadCode RDH 26Mar98 			reddistz = tmpitem->World.Z - ControlledAC->World.Z;
//DeadCode RDH 26Mar98 			if (reddistz < 0)
//DeadCode RDH 26Mar98 				reddistz = -reddistz;
//DeadCode RDH 26Mar98 			if (reddist > (reddistx+reddistz))	
//DeadCode RDH 26Mar98 				reddist = reddistx+reddistz;	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		tmpUID++;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	tmpUID = (UniqueID) BlueAirfieldBAND;
//DeadCode RDH 26Mar98 	EndBand =  (UniqueID) RedPortBAND;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	bluedist = 0x7fffffff;
//DeadCode RDH 26Mar98 	while 	(tmpUID < EndBand)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		tmpitem=MobileItem::currworld->ConvertPtrUID(tmpUID);
//DeadCode RDH 26Mar98 		if 	(tmpitem!=NULL)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 		
//DeadCode RDH 26Mar98 			bluedistx = tmpitem->World.X - ControlledAC->World.X;
//DeadCode RDH 26Mar98 			if (bluedistx < 0)
//DeadCode RDH 26Mar98 				bluedistx = -bluedistx;
//DeadCode RDH 26Mar98 			bluedistz = tmpitem->World.Z - ControlledAC->World.Z;
//DeadCode RDH 26Mar98 			if (bluedistz < 0)
//DeadCode RDH 26Mar98 				bluedistz = -bluedistz;
//DeadCode RDH 26Mar98 			if (bluedist > (bluedistx+bluedistz))	
//DeadCode RDH 26Mar98 				bluedist = bluedistx+bluedistz;	
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		tmpUID++;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if (ControlledAC->nationality==NAT_RED)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		homedist=reddist;
//DeadCode RDH 26Mar98 		enemydist=bluedist;
//DeadCode RDH 26Mar98 	}else
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		homedist=bluedist;
//DeadCode RDH 26Mar98 		enemydist=reddist;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 	if (homedist > KM1)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		if ((homedist < enemydist)
//DeadCode RDH 26Mar98 			||	(enemydist > KM10)
//DeadCode RDH 26Mar98 			)
//DeadCode RDH 26Mar98 			MMC.specialeventbits |= PLAYERLANDEDINCOUNTRY;
//DeadCode RDH 26Mar98 		else
//DeadCode RDH 26Mar98 			MMC.specialeventbits |= PLAYERCAPTURED;
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Fri 8 Sep 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //		  calculates position deltas in cm
//DeadCode RDH 26Mar98 //				- delta = (Vnew + Vold)/2 * CycleTime / 10
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //               	- calls XcalcNewpos (flight2) to update pos
//DeadCode RDH 26Mar98 //                 		(with hitgroundcheck at first hit)
//DeadCode RDH 26Mar98 //               	- makes ground checks and corrections
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::CalcPosition(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 	SLong	deltax,deltay,deltaz;								//RDH 02Aug96
//DeadCode RDH 26Mar98 	Collide::Pos	landed;
//DeadCode RDH 26Mar98 	ANGLES	grndpitch,grndroll;
//DeadCode RDH 26Mar98 	SLong	tmp;
//DeadCode RDH 26Mar98 	SWord	roll_sign,deltaroll;
//DeadCode RDH 26Mar98 	UWord	roll_pos;
//DeadCode RDH 26Mar98 	AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //velocity in 10cm/s units, and time in cs -> 10/100 ->/10
//DeadCode RDH 26Mar98 	deltax =  ((ControlledAC->fly.oldvelx + ControlledAC->velx) / 2)
//DeadCode RDH 26Mar98 				* FLIGHTMODEL_TIMEFRAME /10;
//DeadCode RDH 26Mar98 	deltay =  ((ControlledAC->fly.oldvely + ControlledAC->vely) / 2)
//DeadCode RDH 26Mar98 				* FLIGHTMODEL_TIMEFRAME /10;
//DeadCode RDH 26Mar98 	if ((deltay == 0)
//DeadCode RDH 26Mar98 		&& (ControlledAC->vely > 0)								//RDH 23Nov96
//DeadCode RDH 26Mar98 		&& (ControlledAC->World.Y <= groundlevel)
//DeadCode RDH 26Mar98 		)
//DeadCode RDH 26Mar98 			deltay++;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	deltaz =  ((ControlledAC->fly.oldvelz + ControlledAC->velz) / 2)
//DeadCode RDH 26Mar98 				* FLIGHTMODEL_TIMEFRAME /10;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	CalcGrndInfo (ControlledAC);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ControlledAC->CalcNewPosWithWind (deltax,deltay,deltaz,groundlevel);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	if (!(_DPlay.Implemented && ControlledAC->movecode == AUTO_RESURRECT))//ARM 09Dec96
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		if (ControlledAC->fly.alreadylanded)					//RDH 27Nov96
//DeadCode RDH 26Mar98 		{														//RDH 27Nov96
//DeadCode RDH 26Mar98 			_Collide.StillLanded(ControlledAC,grndpitch,grndroll);//RDH 27Nov96
//DeadCode RDH 26Mar98 			if (deltay > 0)										//RDH 27Nov96
//DeadCode RDH 26Mar98 			{													//RDH 27Nov96
//DeadCode RDH 26Mar98 				ControlledAC->fly.alreadylanded = FALSE;		//RDH 27Nov96
//DeadCode RDH 26Mar98 				landed = _Collide.NOTTOUCHED;					//RDH 27Nov96
//DeadCode RDH 26Mar98 			}else												//RDH 27Nov96
//DeadCode RDH 26Mar98 			{													//RDH 27Nov96
//DeadCode RDH 26Mar98 				landed = _Collide.LANDED_OK;					//RDH 27Nov96
//DeadCode RDH 26Mar98 			}													//RDH 27Nov96
//DeadCode RDH 26Mar98 		}else													//RDH 27Nov96
//DeadCode RDH 26Mar98 		{														//RDH 27Nov96
//DeadCode RDH 26Mar98 			landed = _Collide.HaveWeLanded(ControlledAC,grndpitch,grndroll);//RDH 27Nov96
//DeadCode RDH 26Mar98 		}														//RDH 27Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		if ( landed != _Collide.NOTTOUCHED)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			ControlledAC->fly.alreadylanded = TRUE;				//RDH 29Nov96
//DeadCode RDH 26Mar98 			if (!(Save_Data.gamedifficulty [GD_GROUNDCOLLISIONS]))//RDH 21Mar97
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				landed = _Collide.LANDED_OK;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			if (	(ControlledAC->manoeuvretime == 0)
//DeadCode RDH 26Mar98 					// auto aircraft already use manoeuvretime	//RDH 19Dec96
//DeadCode RDH 26Mar98 					// force entry here and crash				//RDH 19Dec96
//DeadCode RDH 26Mar98 				||	(ControlledAC2 != ControlledAC)				//RDH 19Dec96
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				switch	(landed)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					case _Collide.LANDED_OK:
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 							_Miles.PlayLanded(FIL_SFX_LANDING_GRASS_LOOP,NULL,ControlledAC->vel);//RJS 22Nov96
//DeadCode RDH 26Mar98 					  	else									//RDH 19Dec96
//DeadCode RDH 26Mar98 							ControlledAC->vel = MPH100;			//RDH 19Dec96
//DeadCode RDH 26Mar98 						if (	(ControlledAC->vel >MPH80)			//RDH 22Oct96
//DeadCode RDH 26Mar98 							&& (Save_Data.gamedifficulty [GD_COLLISIONS])//RDH 24Mar97
//DeadCode RDH 26Mar98 								)
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							//loose prop and gear
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 							SHAPE.ForceDamage(	ControlledAC,
//DeadCode RDH 26Mar98 												&adptr->PROPLEFTIN,
//DeadCode RDH 26Mar98 												BS_DEAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 							SHAPE.ForceDamage(	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												&adptr->GEAR,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												BS_DEAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 							Trans_Obj.SetAircraftDammage (	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															*myworld,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BF_Nose,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BS_DEAD,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															FALSE,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															TRUE);
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 							Trans_Obj.SetAircraftDammage (	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															*myworld,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BF_Gear,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BS_DEAD,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															FALSE,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															TRUE);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 								ControlledAC->movecode = AUTO_CRASHSKID;//RJS 11Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 							if (ControlledAC2 == ControlledAC)		//RJS 11Nov96
//DeadCode RDH 26Mar98 							{										//RJS 11Nov96
//DeadCode RDH 26Mar98 								controlmode=PILOTDEAD;				//RJS 11Nov96
//DeadCode RDH 26Mar98 //DeadCode JIM 22Apr97 								ControlledAC->uniqueID.deaded = FALSE;//RJS 11Nov96
//DeadCode RDH 26Mar98 								ControlledAC->Status.deadtime = 0;	//RJS 11Nov96
//DeadCode RDH 26Mar98 								if (View_Point)
//DeadCode RDH 26Mar98 									View_Point->SetToDeathView(DZ_Slow);	//RJS 11Nov96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RJS 11Nov96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::CRASHLANDTOOFAST);//RJS 11Nov96
//DeadCode RDH 26Mar98 								ChkLandedLocation(ControlledAC);		//RDH 29Nov96
//DeadCode RDH 26Mar98 							}
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 							Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 							Persons_2.eventloglist->launchtime=Timer_Code.realtime;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 							Persons_2.eventloglist->stage=Persons_2.eventloglist->CRASHLANDTOOFAST;
//DeadCode RDH 26Mar98 						}else
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							if (ControlledAC2 == ControlledAC)		//RJS 11Nov96
//DeadCode RDH 26Mar98 							{
//DeadCode RDH 26Mar98 								ControlledAC->manoeuvretime = FIVESECS100;
//DeadCode RDH 26Mar98 //DeadCode JIM 22Apr97 								ControlledAC->uniqueID.deaded = FALSE;	//JIM 23Oct96
//DeadCode RDH 26Mar98 								ControlledAC->Status.deadtime = 0;	//JIM 23Oct96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 								//just landed so give a kick
//DeadCode RDH 26Mar98 								CalcGrndInfo (ControlledAC);
//DeadCode RDH 26Mar98 								tmp =  -((SWord) ControlledAC->fly.slip);
//DeadCode RDH 26Mar98 								tmp = (tmp * tmp /512) * tmp /512;
//DeadCode RDH 26Mar98 								ControlledAC->fly.rotr_ybl +=  tmp;
//DeadCode RDH 26Mar98 								MoveToGrndPitchRoll(ControlledAC,grndroll,grndpitch);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 							}
//DeadCode RDH 26Mar98 							else
//DeadCode RDH 26Mar98 							{
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 								SHAPE.ForceDamage(	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 													&adptr->GEAR,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 													BS_DEAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 								Trans_Obj.SetAircraftDammage (	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 																*myworld,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 																BF_Gear,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 																BS_DEAD,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 																FALSE,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 																TRUE);//RJS 11Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 									ControlledAC->movecode = AUTO_CRASHSKID;//RJS 11Nov96
//DeadCode RDH 26Mar98 							}
//DeadCode RDH 26Mar98 						}
//DeadCode RDH 26Mar98 						break;
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 					case _Collide.LEFT_WING_TOUCH:
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						if (ControlledAC2 == ControlledAC)		//DAW 20Dec96
//DeadCode RDH 26Mar98 							deltaroll = ControlledAC->roll - grndroll;
//DeadCode RDH 26Mar98 						else									//DAW 20Dec96
//DeadCode RDH 26Mar98 							deltaroll = ANGLES_90Deg;			//DAW 20Dec96
//DeadCode RDH 26Mar98 						Math_Lib.Pos (deltaroll,
//DeadCode RDH 26Mar98 							roll_pos,roll_sign);
//DeadCode RDH 26Mar98 				 		if (roll_pos < ANGLES_20Deg)
//DeadCode RDH 26Mar98 				 		{//bend wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 							SHAPE.ForceDamage(	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												&adptr->BOTLEFTWING,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												BS_DAMLV2);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 							Trans_Obj.SetAircraftDammage (	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															*myworld,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BF_LBWing,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BS_DAMLV2,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															FALSE,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															TRUE);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	 			 			ControlledAC->fly.rotr_ybl -=  (roll_pos/ANGLES_FifthDeg);
//DeadCode RDH 26Mar98 				 			MoveToGrndPitchRoll(ControlledAC,grndroll,grndpitch);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 							if (ControlledAC2 == ControlledAC)		//RJS 11Nov96
//DeadCode RDH 26Mar98 							{
//DeadCode RDH 26Mar98 //TEMP								Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RDH 02Oct96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::BENTWING);//RDH 02Oct96
//DeadCode RDH 26Mar98 							}
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 							Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 							Persons_2.eventloglist->launchtime=Timer_Code.realtime;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 							Persons_2.eventloglist->stage=Persons_2.eventloglist->BENTWING;
//DeadCode RDH 26Mar98 				 		}else
//DeadCode RDH 26Mar98 				 		{
//DeadCode RDH 26Mar98 						//remove wing
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 							SHAPE.ForceDamage(	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												&adptr->BOTLEFTWING,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												BS_DEAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 							Trans_Obj.SetAircraftDammage (	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														*myworld,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														BF_LBWing,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														BS_DEAD,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														FALSE,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														TRUE);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						 		ControlledAC->movecode = AUTO_CRASHROLL;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 							if (ControlledAC2 == ControlledAC)		//RDH 12Sep96
//DeadCode RDH 26Mar98 							{
//DeadCode RDH 26Mar98 								controlmode=PILOTDEAD;				//RDH 12Sep96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RJS 11Nov96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::FATALCRASH);//RJS 11Nov96
//DeadCode RDH 26Mar98 								if (View_Point)
//DeadCode RDH 26Mar98 									View_Point->SetToDeathView(DZ_Medium);//RJS 11Nov96
//DeadCode RDH 26Mar98 								ChkLandedLocation(ControlledAC);		//RDH 29Nov96
//DeadCode RDH 26Mar98 							}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						}	
//DeadCode RDH 26Mar98 						break;
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 					case _Collide.RIGHT_WING_TOUCH:
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 //DeadCode RJS 05Nov96 						View_Point.SetToDeathView();				//RJS 01Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						if (ControlledAC2 == ControlledAC)		//DAW 20Dec96
//DeadCode RDH 26Mar98 							deltaroll = ControlledAC->roll - grndroll;		   	
//DeadCode RDH 26Mar98 						else									//DAW 20Dec96
//DeadCode RDH 26Mar98 							deltaroll = ANGLES_90Deg;			//DAW 20Dec96
//DeadCode RDH 26Mar98 						Math_Lib.Pos (deltaroll,
//DeadCode RDH 26Mar98 							roll_pos,roll_sign);
//DeadCode RDH 26Mar98 						if (roll_pos < ANGLES_20Deg)
//DeadCode RDH 26Mar98 						{//bend wing
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 							SHAPE.ForceDamage(	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												&adptr->BOTRIGHTWING,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												BS_DAMLV2);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 							Trans_Obj.SetAircraftDammage (	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															*myworld,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BF_RBWing,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BS_DAMLV2,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															FALSE,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															TRUE);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98  							ControlledAC->fly.rotr_ybl +=  (roll_pos/ANGLES_FifthDeg);
//DeadCode RDH 26Mar98 							MoveToGrndPitchRoll(ControlledAC,grndroll,grndpitch);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 							if (ControlledAC == ControlledAC2)		//RJS 11Nov96
//DeadCode RDH 26Mar98 							{
//DeadCode RDH 26Mar98 //TEMP								Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RDH 02Oct96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::BENTWING);//RDH 02Oct96
//DeadCode RDH 26Mar98 							}
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 							Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 							Persons_2.eventloglist->launchtime=Timer_Code.realtime;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 							Persons_2.eventloglist->stage=Persons_2.eventloglist->BENTWING;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						}else
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							//remove wing
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 							SHAPE.ForceDamage(	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												&adptr->BOTRIGHTWING,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 												BS_DEAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 							Trans_Obj.SetAircraftDammage (	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															*myworld,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BF_RBWing,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															BS_DEAD,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															FALSE,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 															TRUE);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 							ControlledAC->movecode = AUTO_CRASHROLL;//RJS 11Nov96
//DeadCode RDH 26Mar98 							if (ControlledAC2 == ControlledAC)		//RJS 11Nov96
//DeadCode RDH 26Mar98 							{
//DeadCode RDH 26Mar98 								controlmode=PILOTDEAD;				//RJS 11Nov96
//DeadCode RDH 26Mar98 //DeadCode RJS 11Nov96 								GR_Quit3DNow=CRASHED_DEAD;			//RJS 11Nov96
//DeadCode RDH 26Mar98 								if (View_Point)
//DeadCode RDH 26Mar98 									View_Point->SetToDeathView(DZ_Medium);//RJS 11Nov96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RJS 11Nov96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::FATALCRASH);//RJS 11Nov96
//DeadCode RDH 26Mar98 								ChkLandedLocation(ControlledAC);		//RDH 29Nov96
//DeadCode RDH 26Mar98 							}										//RJS 11Nov96
//DeadCode RDH 26Mar98 						}	
//DeadCode RDH 26Mar98 						break;
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 					case _Collide.NOSE_TOUCH:
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 				 	//explode
//DeadCode RDH 26Mar98 //DeadCode RJS 11Nov96 						View_Point.SetToDeathView();			//RJS 01Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(ControlledAC->shape);//JIM 17Oct96
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 						AircraftAnimData* adptr;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						if (ControlledAC->Status.deadtime == FALSE)	//JIM 17Oct96
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							ControlledAC->Status.deadtime = sdptr->DeadTime;//JIM 17Oct96
//DeadCode RDH 26Mar98 							ControlledAC->Status.deadscale = sdptr->DeadScale;//JIM 17Oct96
//DeadCode RDH 26Mar98 //DeadCode JIM 22Apr97 							ControlledAC->uniqueID.deaded=TRUE;			//JIM 17Oct96
//DeadCode RDH 26Mar98 							ControlledAC->BreakForm();					//JIM 17Oct96
//DeadCode RDH 26Mar98 						}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //						_DPlay.InitResurrect ((AirStrucPtr)ControlledAC);//ARM 05Dec96
//DeadCode RDH 26Mar98 //						break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 						adptr = (AircraftAnimData*)ControlledAC->Anim;
//DeadCode RDH 26Mar98 //DeadCode RJS 09Jun97 						adptr->dammageflags=0x0FFFF;
//DeadCode RDH 26Mar98 //DeadCode RJS 09Jun97 						adptr->damageflags2=0x0FFFF;
//DeadCode RDH 26Mar98 						adptr->itemstate = DEAD;				//RJS 02Oct96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						SHAPE.DetatchAllVapourStreams(ControlledAC);//RJS 27May97
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						SLong	glevel = Land_Scape.GetGroundLevel((itemptr)ControlledAC);//RJS 21Oct96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						if (ControlledAC2 == ControlledAC)		//RJS 11Nov96
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							if (View_Point)
//DeadCode RDH 26Mar98 									View_Point->SetToDeathView();		//RJS 11Nov96
//DeadCode RDH 26Mar98 							controlmode=PILOTDEAD;				//RJS 11Nov96
//DeadCode RDH 26Mar98 							_Miles.StopEngine();				//RJS 11Nov96
//DeadCode RDH 26Mar98 								GR_Quit3DNow=CRASHED_DEAD;			//RJS 11Nov96
//DeadCode RDH 26Mar98 //TEMP							Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RJS 11Nov96
//DeadCode RDH 26Mar98 //TEMP							Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::FATALCRASH);//RJS 11Nov96
//DeadCode RDH 26Mar98 							ChkLandedLocation(ControlledAC);		//RDH 29Nov96
//DeadCode RDH 26Mar98 						}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						if (ControlledAC->shape != WRECK)			//RJS 09Oct96
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(4)), (ItemBasePtr) ControlledAC);//RJS 22Nov96
//DeadCode RDH 26Mar98 							Trans_Obj.LaunchBigExplosion(ControlledAC,*myworld);//RJS 02Oct96
//DeadCode RDH 26Mar98 							ControlledAC->shape=PDEATH;
//DeadCode RDH 26Mar98 							ControlledAC->pitch = grndpitch;
//DeadCode RDH 26Mar98 							ControlledAC->roll = grndroll;
//DeadCode RDH 26Mar98 							ControlledAC->World.Y = glevel;			//RJS 21Oct96
//DeadCode RDH 26Mar98 //DeadCode RJS 06Nov96 							Trans_Obj.LaunchFire(ControlledAC,*myworld);//RJS 06Nov96
//DeadCode RDH 26Mar98 						}
//DeadCode RDH 26Mar98 						else
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							ControlledAC->shape=CRATER;
//DeadCode RDH 26Mar98 							ControlledAC->pitch = grndpitch;
//DeadCode RDH 26Mar98 							ControlledAC->roll = grndroll;
//DeadCode RDH 26Mar98 							ControlledAC->World.Y = glevel;			//RJS 21Oct96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 11Nov96 							if (ControlledAC2 == ControlledAC)		//RDH 12Sep96
//DeadCode RDH 26Mar98 //DeadCode RJS 11Nov96 								controlmode=PILOTDEAD;				//RDH 12Sep96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 							Trans_Obj.LaunchFire(ControlledAC,*myworld);
//DeadCode RDH 26Mar98 						}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 							ControlledAC->movecode = AUTO_NOPPILOT;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 11Nov96 		 					GR_Quit3DNow=CRASHED_DEAD;					//RDH 22Sep96
//DeadCode RDH 26Mar98 //DeadCode RJS 11Nov96 
//DeadCode RDH 26Mar98 //DeadCode RJS 11Nov96 							Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RDH 02Oct96
//DeadCode RDH 26Mar98 //DeadCode RJS 11Nov96 							Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::FATALCRASH);//RDH 02Oct96
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist->launchtime=Timer_Code.realtime;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist->stage=Persons_2.eventloglist->FATALCRASH;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						if (ControlledAC->Status.deadtime)		//ARM 07Dec96
//DeadCode RDH 26Mar98 							_DPlay.StoreKill (ControlledAC2, NULL, TRUE);//ARM 07Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				 	break;
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 					case _Collide.PROP_TOUCH:
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						//loose prop and gear
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						SHAPE.ForceDamage(	ControlledAC,	
//DeadCode RDH 26Mar98 											&adptr->PROPLEFTIN,
//DeadCode RDH 26Mar98 											BS_DEAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 						SHAPE.ForceDamage(	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 											&adptr->GEAR,
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 											BS_DEAD);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 						Trans_Obj.SetAircraftDammage (	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														*myworld,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														BF_Nose,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														BS_DEAD,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														FALSE,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														TRUE);
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 						Trans_Obj.SetAircraftDammage (	ControlledAC,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														*myworld,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														BF_Gear,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														BS_DEAD,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														FALSE,
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 														TRUE);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						ControlledAC->movecode = AUTO_CRASHSKID;	//RJS 11Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						if (ControlledAC2 == ControlledAC)			//RJS 11Nov96
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 							controlmode=PILOTDEAD;					//RJS 11Nov96
//DeadCode RDH 26Mar98 //TEMP							Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RJS 11Nov96
//DeadCode RDH 26Mar98 //TEMP							Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::CRASHLAND);//RJS 11Nov96
//DeadCode RDH 26Mar98 							if (View_Point)
//DeadCode RDH 26Mar98 									View_Point->SetToDeathView(DZ_Slow);	//RJS 11Nov96
//DeadCode RDH 26Mar98 							ChkLandedLocation(ControlledAC);		//RDH 29Nov96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 						}
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 					 	Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 					 	Persons_2.eventloglist->launchtime=Timer_Code.realtime;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist->stage=Persons_2.eventloglist->CRASHLAND;
//DeadCode RDH 26Mar98 				 		break;
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //TempCode ARM 10Dec96 				// only used to send killed message
//DeadCode RDH 26Mar98 //TempCode ARM 10Dec96 				if (ControlledAC->uniqueID.deaded == TRUE)
//DeadCode RDH 26Mar98 //TempCode ARM 10Dec96 					_DPlay.NewCollision (ControlledAC, NULL, CP_GROUND, 0);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{//landed previously
//DeadCode RDH 26Mar98 				if (	(ControlledAC->vel == 0)
//DeadCode RDH 26Mar98 					&&	(Timer_Code.msgcounttime > THIRTYSECS100)//RDH 22Nov96
//DeadCode RDH 26Mar98 					&&	((Timer_Code.msgcounttime - lastmsgtime) > THIRTYSECS100)//RDH 24Nov96
//DeadCode RDH 26Mar98 					)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					lastmsgtime = Timer_Code.msgcounttime;		//RDH 24Nov96
//DeadCode RDH 26Mar98 					ControlledAC2->InterceptandRange (
//DeadCode RDH 26Mar98 								&ControlledAC2->ai.homebase->World);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 					if (ControlledAC2 == ControlledAC)			//RDH 28Nov96
//DeadCode RDH 26Mar98 					{											//RDH 28Nov96
//DeadCode RDH 26Mar98 						if (ControlledAC2->Range < METRES400)		//RDH 23Nov96
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 								GR_Quit3DNow=LANDED_ONSQUARE;					//RDH 22Sep96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RDH 02Oct96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::LANDOKATHOME);//RDH 02Oct96
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist->launchtime=Timer_Code.realtime;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist->stage=Persons_2.eventloglist->LANDOKATHOME;
//DeadCode RDH 26Mar98 						}else
//DeadCode RDH 26Mar98 						{
//DeadCode RDH 26Mar98 								GR_Quit3DNow=LANDED_OK;					//RDH 22Sep96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);//RDH 02Oct96
//DeadCode RDH 26Mar98 //TEMP								Persons_2.UpdateLog(Persons_2.eventloglist,0,EventLog::LANDOK);//RDH 02Oct96
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist->launchtime=Timer_Code.realtime;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Oct96 						Persons_2.eventloglist->stage=Persons_2.eventloglist->LANDOK;
//DeadCode RDH 26Mar98 						}
//DeadCode RDH 26Mar98 						ChkLandedLocation(ControlledAC);		//RDH 29Nov96
//DeadCode RDH 26Mar98 					}											//RDH 28Nov96
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 				AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;//RJS 03Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				if (adptr)										//RJS 03Dec96
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 					if ((BitStates)(((adptr->dammageflags)>>BF_Gear) & BS_DEAD) == BS_DEAD)//RJS 03Dec96
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 					if (adptr->GEAR == BS_DEAD)					//RJS 21Feb97
//DeadCode RDH 26Mar98 //DeadCode RJS 13Mar97 						Trans_Obj.LaunchDustTrail(ControlledAC,*myworld);	//RJS 03Dec96
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 			 			_Miles.PlayLanded(FIL_SFX_LANDING_GRASS_LOOP,NULL,ControlledAC->vel);//RJS 22Nov96
//DeadCode RDH 26Mar98 				ControlledAC->manoeuvretime = 50; 
//DeadCode RDH 26Mar98 				ControlledAC->fly.chdg = ControlledAC->hdg;
//DeadCode RDH 26Mar98 				ControlledAC->fly.acroll = grndroll;
//DeadCode RDH 26Mar98 				ControlledAC->fly.croll = grndroll;
//DeadCode RDH 26Mar98 		 		ControlledAC->fly.rollrate = 0;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				if (ControlledAC->vel >KRITVEL)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					MoveToGrndPitchRoll(ControlledAC,grndroll,grndpitch);
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 					if (ControlledAC->fly.rotr_zbl < 0)
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						ControlledAC->fly.rotr_zbl += FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 					}else
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						ControlledAC->fly.rotr_zbl -= FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 					if (ControlledAC->fly.rotr_ybl < 0)
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						ControlledAC->fly.rotr_ybl += FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 					}else
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						ControlledAC->fly.rotr_ybl -= FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 					if (ControlledAC->fly.rotr_xbl < 0)
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						ControlledAC->fly.rotr_xbl += FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 					}else
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						ControlledAC->fly.rotr_xbl -= FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 					if ((SWord) ControlledAC->pitch >
//DeadCode RDH 26Mar98 						((SWord) (ControlledAC->classtype->deckangle+ grndpitch)))
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						ControlledAC->pitch = ControlledAC->classtype->deckangle + grndpitch;	
//DeadCode RDH 26Mar98 					}else
//DeadCode RDH 26Mar98 					{
//DeadCode RDH 26Mar98 						//counteract tendency to nose down
//DeadCode RDH 26Mar98 						ControlledAC->pitch = (Angles)(ControlledAC->pitch + FLIGHTMODEL_TIMEFRAME * 8);	//RDH 14Nov96
//DeadCode RDH 26Mar98 					}
//DeadCode RDH 26Mar98 					ControlledAC->fly.cpitch =  grndpitch;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 	 		if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				_Miles.StopLanded();
//DeadCode RDH 26Mar98 				tmp = ControlledAC->manoeuvretime - FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 				if (tmp < 0)
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					ControlledAC->manoeuvretime = 0;
//DeadCode RDH 26Mar98 				}else
//DeadCode RDH 26Mar98 				{
//DeadCode RDH 26Mar98 					ControlledAC->manoeuvretime = tmp;
//DeadCode RDH 26Mar98 				}
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}															//ARM 18Nov96
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	groundlevel = Land_Scape.GetGroundLevel(ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	if (ControlledAC->World.Y > groundlevel)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	 	if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			_Miles.StopLanded();
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			SLong tmp = ControlledAC->manoeuvretime - FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			if (tmp < 0)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				ControlledAC->manoeuvretime = 0;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			}else
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				ControlledAC->manoeuvretime = tmp;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	}else
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	 	if (ControlledAC2 == ControlledAC)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		_Miles.PlayLanded(FIL_SFX_LANDING_GRASS_LOOP,NULL,ControlledAC->vel);//RJS 22Nov96
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		ControlledAC->fly.acroll = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		ControlledAC->fly.croll = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	 	ControlledAC->fly.rollrate = 0;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		ControlledAC->World.Y = groundlevel;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		if (ControlledAC->manoeuvretime == 0)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		{//just landed so give a kick
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			ControlledAC->manoeuvretime = FIVESECS100; 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			CalcGrndInfo (ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96  			SLong tmp =  -((SWord) ControlledAC->fly.slip);
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			tmp = (tmp * tmp /512) * tmp /512;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96  			ControlledAC->fly.rotr_ybl +=  tmp;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 //DeadCode RJS 24Jul96 			_Miles.PlayOnce (FIL_SFX_LANDING_CRASH,(rotitem) View_Point,NULL,28000);//RJS 24Jul96
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		ControlledAC->manoeuvretime = 50; 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		ControlledAC->fly.chdg = ControlledAC->hdg;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		if (ControlledAC->vel >KRITVEL)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			if (((UWord) ControlledAC->fly.cpitch) > ANGLES_180Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				ControlledAC->fly.cpitch = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			if (((UWord) ControlledAC->pitch) > ANGLES_180Deg)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				ControlledAC->pitch = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			}else
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				if (((UWord) ControlledAC->pitch) > ControlledAC->classtype->deckangle)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 					ControlledAC->pitch = ControlledAC->classtype->deckangle;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 			}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		}else
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				if (ControlledAC->fly.rotr_zbl < 0)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 					ControlledAC->fly.rotr_zbl += FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				}else
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 					ControlledAC->fly.rotr_zbl -= FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				if (ControlledAC->fly.rotr_ybl < 0)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 					ControlledAC->fly.rotr_ybl += FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				}else
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 					ControlledAC->fly.rotr_ybl -= FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				if (ControlledAC->fly.rotr_xbl < 0)
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 					ControlledAC->fly.rotr_xbl += FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				}else
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 					ControlledAC->fly.rotr_xbl -= FLIGHTMODEL_TIMEFRAME;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				if ((SWord) ControlledAC->pitch > ((SWord) ControlledAC->classtype->deckangle))
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 					ControlledAC->pitch = ControlledAC->classtype->deckangle;	
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				}else
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				{
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 					ControlledAC->pitch = (ANGLES)(ControlledAC->pitch + FLIGHTMODEL_TIMEFRAME);	
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 				ControlledAC->fly.cpitch = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 		}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 	}
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 }
//DeadCode RDH 26Mar98 //DeadCode RDH 12Sep96 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //////////////////////////////////////////////////////////////////////////////////
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 // CLUDGE CORNER...
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 extern	SLong ViewX;
//DeadCode RDH 26Mar98 extern	SLong ViewY;
//DeadCode RDH 26Mar98 extern	SLong ViewZ;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 26Mar98 //Author		R. Hyde 
//DeadCode RDH 26Mar98 //Date		Fri 8 Sep 1995
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Description	
//DeadCode RDH 26Mar98 //		Transfers newly calculated C_model aircraft_angles 
//DeadCode RDH 26Mar98 //               to MobileItem_angles for display
//DeadCode RDH 26Mar98 //               MobileItem: Hdg     <--  Airstruc AcHdg
//DeadCode RDH 26Mar98 //                         : Pitch   <--           AcPitch     (if outside view)
//DeadCode RDH 26Mar98 //                                                 CPitch + 1/2(AoA) (if inside)
//DeadCode RDH 26Mar98 //                         : Roll    <--           360deg - AcRoll
//DeadCode RDH 26Mar98 //                         : VelY    <--           -cvely         
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Inputs		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //Returns	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 void	ManualPilot::DataTrans(AirStrucPtr const ControlledAC)
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 {
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 24May96 	ControlledAC->SetManualFlightParams ();
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //old model reversed these, not explored problem yet			//RDH 15Dec95
//DeadCode RDH 26Mar98 	ControlledAC->roll   = ControlledAC->fly.acroll;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	ControlledAC->vely = (SWord)-ControlledAC->fly.cvely;
//DeadCode RDH 26Mar98 	ControlledAC->fly.vel_cms  = (SWord)(ControlledAC->fly.vel_mms /10);
//DeadCode RDH 26Mar98 	ControlledAC->vel = (SWord)(ControlledAC->fly.vel_cms /10);
//DeadCode RDH 26Mar98 }
//DeadCode RDH 26Mar98 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitManualPilot
//Author		Paul.   
//Date			Thu 2 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::InitManualPilot(AirStrucPtr const ControlledAC)

{

	InitManualPilotSub(ControlledAC);


	//Do this whenever you switch auto/man/auto

	ControlledAC->ai.ManStep = PHASE0;							//RDH 10Sep96
	ControlledAC->ai.manoeuvre = MANOEUVRE_SELECT;				//JIM 05Aug96
	ControlledAC->manoeuvretime = 0;							//JIM 05Aug96
//	ControlledAC->ai.JinkTime = 0;							//JIM 05Aug96

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitManualPilot
//Author		Paul.   
//Date			Thu 2 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::InitManualPilotSub(AirStrucPtr const ControlledAC)

{

		InitSimpleAc(ControlledAC);
///		Save_Data.keysensitivity = 2;											//RDH 12Mar96
		trim =0;													//RDH 15Nov96
		lastmsgtime = 0;

//this does a big initialise									//rdh
		if (ControlledAC2 == ControlledAC)							//ARM 01May97
		{// Player's Aircraft
			ControlledAC->fly.pModel->Initialise (ControlledAC,TRUE);			//ARM 01May97
		}else														//ARM 01May97
		{// ACM Aircraft
			ControlledAC->fly.pModel->Initialise (ControlledAC,FALSE);			//ARM 01May97
		}
}

void ManualPilot::InitSimpleAc(AirStrucPtr const ControlledAC)
{
//	ControlledAC->fly.rpm_lastcycle = ControlledAC->fly.thrustpercent;
//	ControlledAC->fly.rpmtrimtime = 0;
//DeadCode RDH 20Nov96 	ControlledAC->fly.comefrommap = FALSE;
//DEADCODE RDH 13/05/99 	ControlledAC->fly.alreadylanded = FALSE;					//RDH 25Nov96

//the following need to be set on moving to manual
	if (ControlledAC->vel > 0)
		ControlledAC->fly.cpitch = ControlledAC->pitch;			//RDH 10Apr96
	ControlledAC->fly.i_a_s = ControlledAC->vel;				//RDH 19Oct96
	ControlledAC->fly.vel_cms = 	ControlledAC->vel * 10;			//RDH 19Oct96
//	ControlledAC->fly.turnrate = ANGLES_0Deg;					//RDH 19Oct96
	ControlledAC->fly.redeffect = 0;							//RJS 13Nov96
	ControlledAC->ai.moraleinc = 0;
	ControlledAC->ai.deltapitchsum = 0;		//rdh
}
void ManualPilot::AutoToggleAircraft(AirStrucPtr const ControlledAC, CONTROLMODE mode)
{
//DeadCode PD 03Mar99 	if  (	((mode) && (controlmode == AUTO))			//rdh 6/4/98
//DeadCode PD 03Mar99 	  ||	((!(mode)) && (controlmode == MANUAL))
//DeadCode PD 03Mar99 		)
	if (mode!=controlmode)
	{
		if (mode==MANUAL)	ControlledAC->fly.pModel->Controlled = TRUE;
		else				ControlledAC->fly.pModel->Controlled = FALSE;
		controlmode=mode;
		InitFlightModelPos(ControlledAC);
		ControlledAC->ai.ManStep = PHASE0;							//RDH 10Sep96
		ControlledAC->ai.manoeuvre = MANOEUVRE_SELECT;				//JIM 05Aug96
		ControlledAC->manoeuvretime = 0;							//JIM 05Aug96
		ControlledAC->information=FALSE;							  //JIM 16/04/99
//		ControlledAC->ai.JinkTime = 0;							//JIM 05Aug96
	}
//DeadCode AMM 19Jan00 	if((ControlledAC == Persons2::PlayerSeenAC) || (ControlledAC == Persons2::PlayerGhostAC))
//DeadCode AMM 19Jan00 	{
//DeadCode AMM 19Jan00 		ControlledAC->fly.elevator = 0;
//DeadCode AMM 19Jan00 		ControlledAC->fly.aileron  = 0;
//DeadCode AMM 19Jan00 		ControlledAC->fly.rudder   = 0;
//DeadCode AMM 19Jan00 		ControlledAC->fly.pModel->Elevator = 0;
//DeadCode AMM 19Jan00 		ControlledAC->fly.pModel->Aileron  = 0;
//DeadCode AMM 19Jan00 		ControlledAC->fly.pModel->Rudder   = 0;
//DeadCode AMM 19Jan00 	}
}

void ManualPilot::InitFlightModelPos(AirStrucPtr const ControlledAC)
{
	InitSimpleAc(ControlledAC);
//init aoa for first frame where it may be used before it is set

	ControlledAC->fly.elevator = 0;								//AMM 19Jan00
	ControlledAC->fly.aileron  = 0;								//AMM 19Jan00
	ControlledAC->fly.rudder   = 0;								//AMM 19Jan00
	ControlledAC->fly.pModel->Elevator = 0;						//AMM 19Jan00
	ControlledAC->fly.pModel->Aileron  = 0;						//AMM 19Jan00
	ControlledAC->fly.pModel->Rudder   = 0;						//AMM 19Jan00

	PMAINPLANE pMainPlane = ControlledAC->fly.pModel->MainPlaneList;
	while(pMainPlane)
	{
		pMainPlane->aoa[0][0] = 0;
		pMainPlane->aoa[0][1] = 0;
		pMainPlane->aoa[1][0] = 0;
		pMainPlane->aoa[1][1] = 0;
		pMainPlane = pMainPlane->List.NextItem();
	}

	ControlledAC->fly.pModel->InitialiseEngines(ControlledAC);
//DeadCode CSB 10/11/98		ControlledAC->fly.pModel->MainPlaneList->BuffTime[0][0] = 0;
//DeadCode CSB 10/11/98		ControlledAC->fly.pModel->MainPlaneList->BuffTime[0][1] = 0;
//DeadCode CSB 10/11/98		ControlledAC->fly.pModel->MainPlaneList->BuffTime[1][0] = 0;
//DeadCode CSB 10/11/98		ControlledAC->fly.pModel->MainPlaneList->BuffTime[1][1] = 0;
	ControlledAC->fly.pModel->UpdateModel (ControlledAC);
}

UByte	DUMMY;
UByte&	item::AnimByte(Animfieldref)
{
	return(DUMMY=0);
}

//DeadCode PD 19Feb96 ViewPoint	View_Point;


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrintStatistics
//Author		R. Hyde 
//Date			Thu 16 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::PrintStatistics(Window* Whole_Screen)
{

//DeadCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(0000,1000),ScreenWH(0,0),PF_VAlignCenter,
//DeadCode RDH 10Apr96 		_Text.Conv("AC"));

//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(6500,1000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->hdg,5,OFORM_LZ));
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(13000,1000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->pitch,5,OFORM_LZ));	  
//DeadCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(0,5000),ScreenWH(0,0),PF_VAlignCenter,
//DeadCode RDH 10Apr96 		_Text.Conv(ControlledAC2->roll,5,OFORM_LZ));


//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(0000,2000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv("VEL"));
//TempCode RDH 10Apr96 
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(6500,2000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->fly.chdg,5,OFORM_LZ));
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(13000,2000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->fly.cpitch,5,OFORM_LZ));
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(19500,2000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->fly.croll,5,OFORM_LZ));
//TempCode RDH 10Apr96 
//TempCode RDH 10Apr96 
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(0000,3000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv("VAS"));
//TempCode RDH 10Apr96 
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(6500,3000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->vel,5,OFORM_LZ));
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(13000,3000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->fly.aoa,5,OFORM_LZ));
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(19500,3000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->fly.slip,5,OFORM_SIGN));
//TempCode RDH 10Apr96 
//TempCode RDH 10Apr96 
//TempCode RDH 10Apr96 
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(0000,4000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv("Inputs"));
//TempCode RDH 10Apr96 
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(6500,4000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->fly.aileron,5,OFORM_LZ));
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(13000,4000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->fly.elevator,5,OFORM_LZ));
//TempCode RDH 10Apr96 	_Text.Print(Whole_Screen,ScreenXY(19500,4000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96 		_Text.Conv(ControlledAC2->fly.rudder,5,OFORM_LZ));

 
//TempCode RDH 10Apr96  	_Text.Print(Whole_Screen,ScreenXY(0000,5000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96  		_Text.Conv("Pos"));
//TempCode RDH 10Apr96  
//TempCode RDH 10Apr96  	_Text.Print(Whole_Screen,ScreenXY(6500,5000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96  		_Text.Conv(ControlledAC2->World.X,5,OFORM_LZ));
//TempCode RDH 10Apr96  	_Text.Print(Whole_Screen,ScreenXY(13000,5000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96  		_Text.Conv(ControlledAC2->World.Y,5,OFORM_LZ));
//TempCode RDH 10Apr96  	_Text.Print(Whole_Screen,ScreenXY(19500,5000),ScreenWH(0,0),PF_VAlignCenter,
//TempCode RDH 10Apr96  		_Text.Conv(ControlledAC2->World.Z,5,OFORM_LZ));
 
//TempCode JIM 19Jan98  	_Text.Print(Whole_Screen,ScreenXY(6000,5000),ScreenWH(7000,1200),PF_VAlignCenter,
//TempCode JIM 19Jan98  		_Text.Conv(ControlledAC2->fly.acroll,5,OFORM_LZ));
//TempCode JIM 19Jan98  	_Text.Print(Whole_Screen,ScreenXY(13000,5000),ScreenWH(6000,1200),PF_VAlignCenter,
//TempCode JIM 19Jan98  		_Text.Conv(ControlledAC2->fly.rollrate,5,OFORM_LZ));

//	_Text.Print(ScreenXY(0000,14000),ScreenWH(0,0),PF_VAlignCenter,
//		_Text.Conv("TLD"));
//
//	_Text.Print(ScreenXY(6500,14000),ScreenWH(0,0),PF_VAlignCenter,
//		_Text.Conv(thrust,5,OFORM_LZ));
//	_Text.Print(ScreenXY(13000,14000),ScreenWH(0,0),PF_VAlignCenter,
//		_Text.Conv(lift,5,OFORM_LZ));
//	_Text.Print(ScreenXY(19500,14000),ScreenWH(0,0),PF_VAlignCenter,
//		_Text.Conv(totaldrag,5,OFORM_LZ));
//





}

//
// ACM - moved and reclassed...
//
//

