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
//Filename       flyinit.cpp
//System         
//Author         Jim Taylor
//Date           Tue 31 Oct 1995
//Description    Instances of planetypes and dumb planetypes
//------------------------------------------------------------------------------

#define F_GRAFIX												//DAW 05Aug96
#define F_COMMON
#define F_BATTLE
#include "dosdefs.h"
#include "myANGLES.h"
#include "ranges.h"

#include "worldinc.h"											//ARM 29Jan97
#include "modvec.h"												//ARM 29Jan97
#include "model.h"												//ARM 29Jan97

#include "planetyp.h"
#include	"radio.g"											//RJS 10Feb99

#undef	PLANETYP_Included
#include	"planetyp.h"
SLong const ROTATION_CLOCKWISE = 1; 
SLong const ROTATION_ANTICLOCKWISE = -1;


startinst(PlaneType,Plane_Type_F86A)
	(WeightEmpty)		498000,	//correct		//0.01kg
	(FuelLoad)			126400,	//correct		//0.01kg
/*shad shp*/			F86SHD,									//RJS 12May97
/*(TextRef)*/			0,//	TEXT_F86E,
/*vis shp*/				F86,							//JIM 28Mar96
	(FuelABoff)			650,	//correct		//cg/cs
//DeadCode CSB 18/11/98		(FuelCruise)		145,//check		//CSB	270,		//cg/cs

	(MaxVel)			2700,
	(MinVel)			165,							//RDH 24Nov96
	(CruiseVel)			2480,
	(BestClimbVel)		2422,
	(Angles)			1154,	//ANGLES_13Deg,
	(MaxDiveVel)		3000,						//RDH 04Dec96
	(MaxAccel)			12082,	//CSB 28/05/99	
/*pit1 shp*/			DUMMY8,									//RJS 21Jan98
/*pit2 shp*/			DUMMY8,							//PD 25Sep96
/*msk1 shp*/			EMPTY2,							//PD 25Sep96
/*msk2 shp*/			EMPTY2,							//PD 25Sep96
/*cockpit scale*/		0.07743,								//RJS 20Apr99
/*phrase name*/			PHRASE_F86S,							//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_FIGHTER,
	(ANGLES)			ANGLES_0Deg,		//deck angle
	(MaxRollRate)		ANGLES_180Deg,
//DeadCode CSB 22/02/99		(MaxTurnRate)		ANGLES_22Deg,
	(MaxPitchRate)		ANGLES_15Deg,
	(LandingSpeed)		600,
	(MaxDiveRpm)		1400,				//max dive rpm
	(FreeRpm)			400,					//freewheel rpm
	(MaxRpm)			1150,
	(MinRpm)			800,
//DeadCode CSB 19/11/98		(MaxSafeVel)		820,
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
//DeadCode CSB 19/11/98		(MaxCeilingGoodW)	600000,
//DeadCode CSB 19/11/98		(MaxCeilingBadW)	500000,
//DeadCode CSB 19/11/98		(OpCeiling)			FT_14000,
	(FightCeiling)		FT_12000,
//DeadCode CSB 19/11/98		(FightFloor)		FT_8000,
	(Abs_Ceiling)		1524000,	//cm - 50,000ft
						0.2723,		//15.6deg
	(MuzzleVel)			9500,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	6,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

	{			
		(BestClimbAng)	2136	,
		(BestClimbAng)	1928	,
		(BestClimbAng)	1738	,
		(BestClimbAng)	1554	,
		(BestClimbAng)	1282	,
		(BestClimbAng)	1154	,
		(BestClimbAng)	1035	,
		(BestClimbAng)	919	,
		(BestClimbAng)	805	,
		(BestClimbAng)	691	,
		(BestClimbAng)	575	,
		(BestClimbAng)	451	,
		(BestClimbAng)	327	,
		(BestClimbAng)	209	,
		(BestClimbAng)	95	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	2204	,
		(BestClimbSpeed)	2219	,
		(BestClimbSpeed)	2226	,
		(BestClimbSpeed)	2240	,
		(BestClimbSpeed)	2435	,
		(BestClimbSpeed)	2422	,
		(BestClimbSpeed)	2394	,
		(BestClimbSpeed)	2363	,
		(BestClimbSpeed)	2331	,
		(BestClimbSpeed)	2299	,
		(BestClimbSpeed)	2268	,
		(BestClimbSpeed)	2279	,
		(BestClimbSpeed)	2308	,
		(BestClimbSpeed)	2339	,
		(BestClimbSpeed)	2380	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		3022	,
	(MaxVelSL_11km)		2697	,
	(MaxVelSL_20km)		2100	,
				
	(MaxVelDive_0km)	3600	,	
	(MaxVelDive_11km)	3100	,	
	(MaxVelDive_20km)	3100	,	
	
/*version*/			1,

	&F86E_Setup,											//ARM 28Jan97

endinst(PlaneType,Plane_Type_F86A);

/////////////////////////////////////////////////////////////////////////////////////////

startinst(PlaneType,Plane_Type_F86E)
	(WeightEmpty)		511900,	//correct		//0.01kg
	(FuelLoad)			124600,	//correct		//0.01kg
/*shad shp*/			F86SHD,									//RJS 12May97
/*(TextRef)*/			0,//TEXT_F86E,
/*vis shp*/				F86,							//JIM 28Mar96
	(FuelABoff)			650,	//correct		//cg/cs
//DeadCode CSB 18/11/98		(FuelCruise)		145,		//CSB	270,		//cg/cs

	(MaxVel)			3000,	//679 mph
	(MinVel)			450,	//100 mph	
	(CruiseVel)			2600,	//450 mph
	(BestClimbVel)		2050,	//450 mph
	(Angles)			975,	//ANGLES_10Deg,
	(MaxDiveVel)		3250,	//M 0.96			
	(MaxAccel)			11294,	//CSB 28/05/99	
/*pit1 shp*/			DUMMY8,									//RJS 21Jan98
/*pit2 shp*/			DUMMY8,							//PD 25Sep96
/*msk1 shp*/			EMPTY2,							//PD 25Sep96
/*msk2 shp*/			EMPTY2,							//PD 25Sep96
/*cockpit scale*/		0.07743,								//RJS 20Apr99
/*phrase name*/			PHRASE_F86S,							//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_FIGHTER,
	(ANGLES)			ANGLES_0Deg,		//deck angle
	(MaxRollRate)		ANGLES_180Deg,
//DeadCode CSB 22/02/99		(MaxTurnRate)		ANGLES_22Deg,
	(MaxPitchRate)		ANGLES_15Deg,
	(LandingSpeed)		600,
	(MaxDiveRpm)		7950,	//max rpm
	(FreeRpm)			500,	//min freewheel rpm
	(MaxRpm)			7950,
	(MinRpm)			500,
//DeadCode CSB 19/11/98		(MaxSafeVel)		3400,	//M 1.0
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
//DeadCode CSB 19/11/98		(MaxCeilingGoodW)	1615000,//53000 ft
//DeadCode CSB 19/11/98		(MaxCeilingBadW)	1372000,//45000 ft
//DeadCode CSB 19/11/98		(OpCeiling)			1615000,//53000 ft
	(FightCeiling)		1500000,//49000 ft
//DeadCode CSB 19/11/98		(FightFloor)		 300000,// 9800 ft
	(Abs_Ceiling)		1623000,//53250 ft
		0.2723,		//15.6deg
	(MuzzleVel)			9143,//9500,	//fix this !!!!

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	6,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

	{			
		(BestClimbAng)	2143	,
		(BestClimbAng)	1934	,
		(BestClimbAng)	1742	,
		(BestClimbAng)	1559	,
		(BestClimbAng)	1287	,
		(BestClimbAng)	1158	,
		(BestClimbAng)	1039	,
		(BestClimbAng)	923	,
		(BestClimbAng)	808	,
		(BestClimbAng)	694	,
		(BestClimbAng)	579	,
		(BestClimbAng)	454	,
		(BestClimbAng)	330	,
		(BestClimbAng)	212	,
		(BestClimbAng)	97	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	2204	,
		(BestClimbSpeed)	2219	,
		(BestClimbSpeed)	2228	,
		(BestClimbSpeed)	2242	,
		(BestClimbSpeed)	2435	,
		(BestClimbSpeed)	2422	,
		(BestClimbSpeed)	2394	,
		(BestClimbSpeed)	2363	,
		(BestClimbSpeed)	2331	,
		(BestClimbSpeed)	2299	,
		(BestClimbSpeed)	2268	,
		(BestClimbSpeed)	2279	,
		(BestClimbSpeed)	2308	,
		(BestClimbSpeed)	2337	,
		(BestClimbSpeed)	2382	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	,
		(BestClimbSpeed)	2414	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		3022	,
	(MaxVelSL_11km)		2697	,
	(MaxVelSL_20km)		2100	,
				
	(MaxVelDive_0km)	3600	,	
	(MaxVelDive_11km)	3100	,	
	(MaxVelDive_20km)	3100	,	

/*version*/			2,

		&F86E_Setup,											//ARM 28Jan97

endinst(PlaneType,Plane_Type_F86E);

/////////////////////////////////////////////////////////////////////////////////////////

startinst(PlaneType,Plane_Type_F86F)
	(WeightEmpty)		524600,//correct		//0.01kg
	(FuelLoad)			126400,					//0.01kg
/*shad shp*/			F86SHD,									//RJS 12May97
/*(TextRef)*/			0,//TEXT_F86E,
/*vis shp*/				F86,							//JIM 28Mar96
	(FuelABoff)			650,		//cg/cs
//DeadCode CSB 18/11/98		(FuelCruise)		270,		//cg/cs

	(MaxVel)			3050,
	(MinVel)			165,							//RDH 24Nov96
	(CruiseVel)			2557,
	(BestClimbVel)		2428,
	(Angles)			1405,	//ANGLES_13Deg,
	(MaxDiveVel)		3000,						//RDH 04Dec96
	(MaxAccel)			12718,		//CSB 28/05/99	
/*pit1 shp*/			DUMMY8,									//RJS 21Jan98
/*pit2 shp*/			DUMMY8,							//PD 25Sep96
/*msk1 shp*/			EMPTY2,							//PD 25Sep96
/*msk2 shp*/			EMPTY2,							//PD 25Sep96
/*cockpit scale*/		0.07743,								//RJS 20Apr99
/*phrase name*/			PHRASE_F86S,							//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_FIGHTER,
	(ANGLES)		ANGLES_14Deg,		//deck angle
	(MaxRollRate)		ANGLES_180Deg,
//DeadCode CSB 22/02/99		(MaxTurnRate)		ANGLES_22Deg,
	(MaxPitchRate)		ANGLES_15Deg,
	(LandingSpeed)		600,
	(MaxDiveRpm)		1400,				//max dive rpm
	(FreeRpm)		400,					//freewheel rpm
	(MaxRpm)		1150,
	(MinRpm)		800,
//DeadCode CSB 19/11/98		(MaxSafeVel)			820,
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
//DeadCode CSB 19/11/98		(MaxCeilingGoodW)	600000,
//DeadCode CSB 19/11/98		(MaxCeilingBadW)	500000,
//DeadCode CSB 19/11/98		(OpCeiling)			FT_14000,
	(FightCeiling)		FT_12000,
//DeadCode CSB 19/11/98		(FightFloor)		 FT_8000,
	(Abs_Ceiling)		1524000,	//cm - 50,000ft
		0.2723,		//15.6deg
	(MuzzleVel)		9500,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	6,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

	{			
		(BestClimbAng)	2198	,
		(BestClimbAng)	2028	,
		(BestClimbAng)	1864	,
		(BestClimbAng)	1706	,
		(BestClimbAng)	1554	,
		(BestClimbAng)	1405	,
		(BestClimbAng)	1259	,
		(BestClimbAng)	1117	,
		(BestClimbAng)	970	,
		(BestClimbAng)	821	,
		(BestClimbAng)	682	,
		(BestClimbAng)	546	,
		(BestClimbAng)	413	,
		(BestClimbAng)	288	,
		(BestClimbAng)	167	,
		(BestClimbAng)	45	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	2569	,
		(BestClimbSpeed)	2545	,
		(BestClimbSpeed)	2519	,
		(BestClimbSpeed)	2490	,
		(BestClimbSpeed)	2459	,
		(BestClimbSpeed)	2428	,
		(BestClimbSpeed)	2397	,
		(BestClimbSpeed)	2368	,
		(BestClimbSpeed)	2357	,
		(BestClimbSpeed)	2370	,
		(BestClimbSpeed)	2377	,
		(BestClimbSpeed)	2396	,
		(BestClimbSpeed)	2421	,
		(BestClimbSpeed)	2430	,
		(BestClimbSpeed)	2437	,
		(BestClimbSpeed)	2438	,
		(BestClimbSpeed)	2439	,
		(BestClimbSpeed)	2439	,
		(BestClimbSpeed)	2439	,
		(BestClimbSpeed)	2439	,
		(BestClimbSpeed)	2439	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		3105	,
	(MaxVelSL_11km)		2784	,
	(MaxVelSL_20km)		2150	,
				
	(MaxVelDive_0km)	3600	,	
	(MaxVelDive_11km)	3100	,	
	(MaxVelDive_20km)	3100	,	

/*version*/			3,

		&F86E_Setup,											//ARM 28Jan97

endinst(PlaneType,Plane_Type_F86F);

/////////////////////////////////////////////////////////////////////////////////////////
		
startinst(PlaneType,Plane_Type_F84)							//RDH 07Apr96
			(WeightEmpty)	523300,//correct
			(FuelLoad)		135000,			//With tip tanks//69200 W/O tip tanks	//	126400,
			/*shad shp*/		F84SHD,							//RJS 10Jun97
			/*(TextRef)*/		0,//TEXT_F84,
			/*vis shp*/			F84,							//AM 21Jan97
			(FuelABoff)		725,			//CSB	300,			//cg/cs
//DeadCode CSB 18/11/98				(FuelCruise)	150,			//CSB	270,			//cg/cs

	(MaxVel)			2750,
	(MinVel)			165,							//RDH 24Nov96
	(CruiseVel)			2300,//1975,//
	(BestClimbVel)		1500,
	(Angles)			 900,	//ANGLES_13Deg,
			(MaxDiveVel)		3000,						//RDH 04Dec96
			(MaxAccel)			10704,		//CSB 28/05/99	
			/*pit1 shp*/		CPTF84,							//PD 20Jun96
			/*pit2 shp*/		CPTF84,							//RJS 26Apr99
			/*msk1 shp*/		EMPTY2,							//PD 20Jun96
			/*msk2 shp*/		EMPTY2,							//PD 20Jun96
		/*cockpit scale*/		0.09794,						//RJS 20Apr99
		/*phrase name*/			PHRASE_F84S,					//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_HIGH,
	(ANGLES)		ANGLES_0Deg,		//deck angle
			(MaxRollRate)		ANGLES_60Deg,
//DeadCode CSB 22/02/99				(MaxTurnRate)		ANGLES_22Deg,
			(MaxPitchRate)		ANGLES_15Deg,
			(LandingSpeed)		600,
			(MaxDiveRpm)		2200,				//max dive rpm
			(FreeRpm)		400,					//freewheel rpm
			(MaxRpm)		2000,
			(MinRpm)		800,
//DeadCode CSB 19/11/98				(MaxSafeVel)			1340,						//RDH 04Dec96
			(MovableFireZoneType)	-1,
			(Damage)			0x2222,
//DeadCode CSB 19/11/98				(MaxCeilingGoodW)	600000,
//DeadCode CSB 19/11/98				(MaxCeilingBadW)	500000,
//DeadCode CSB 19/11/98				(OpCeiling)			FT_20000,
			(FightCeiling)		FT_18000,
//DeadCode CSB 19/11/98				(FightFloor)		FT_10000,
			(Abs_Ceiling)		1524000,	//cm - 50,000ft
		0.2723,		//15.6deg
				(MuzzleVel)		9500,

		(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
		(FileNum)			INVALIDFILENUM,
		(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	6,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

		(InstType)			lightinstrumtypes,
		(ACFlags)			HUDINACTIVE,

	{			
		(BestClimbAng)	2148	,
		(BestClimbAng)	1923	,
		(BestClimbAng)	1709	,
		(BestClimbAng)	1506	,
		(BestClimbAng)	1313	,
		(BestClimbAng)	1131	,
		(BestClimbAng)	958	,
		(BestClimbAng)	795	,
		(BestClimbAng)	640	,
		(BestClimbAng)	495	,
		(BestClimbAng)	330	,
		(BestClimbAng)	220	,
		(BestClimbAng)	112	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	1567	,
		(BestClimbSpeed)	1572	,
		(BestClimbSpeed)	1579	,
		(BestClimbSpeed)	1588	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1613	,
		(BestClimbSpeed)	1630	,
		(BestClimbSpeed)	1649	,
		(BestClimbSpeed)	1673	,
		(BestClimbSpeed)	1701	,
		(BestClimbSpeed)	1894	,
		(BestClimbSpeed)	1939	,
		(BestClimbSpeed)	1986	,
		(BestClimbSpeed)	2035	,
		(BestClimbSpeed)	2035	,
		(BestClimbSpeed)	2035	,
		(BestClimbSpeed)	2035	,
		(BestClimbSpeed)	2035	,
		(BestClimbSpeed)	2035	,
		(BestClimbSpeed)	2035	,
		(BestClimbSpeed)	2035	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		2725	,
	(MaxVelSL_11km)		2454	,
	(MaxVelSL_20km)		500	,
				
	(MaxVelDive_0km)	3400	,	
	(MaxVelDive_11km)	2950	,	
	(MaxVelDive_20km)	2950	,	

		/*version*/			1,

		&F84E_Setup,											//ARM 28Jan97

endinst(PlaneType,Plane_Type_F84);

/////////////////////////////////////////////////////////////////////////////////////////

startinst(PlaneType,Plane_Type_F80)							//RDH 07Apr96
	(WeightEmpty)	374100,//correct
	(FuelLoad)		126400,
	/*shad shp*/		F80SHD,							//RJS 10Jun97
	/*(TextRef)*/		0,//TEXT_F80,					//RDH 20Dec96
	/*vis shp*/			F80,							//RDH 07Apr96
	(FuelABoff)			560,
//DeadCode CSB 18/11/98				(FuelCruise)	270,			//cg/cs

	(MaxVel)			2650,
	(MinVel)			165,							//RDH 24Nov96
	(CruiseVel)			2300,
	(BestClimbVel)		1250,	//2102,
	(Angles)			1325,	//ANGLES_13Deg,
	(MaxDiveVel)		3000,						//RDH 04Dec96
	(MaxAccel)			12885,	//CSB 28/05/99	
			/*pit1 shp*/		CPTF80,							//PD 20Jun96
			/*pit2 shp*/		CPTF80,							//RJS 26Apr99
			/*msk1 shp*/		EMPTY2,							//PD 20Jun96
			/*msk2 shp*/		EMPTY2,							//PD 20Jun96
		/*cockpit scale*/		0.064901,						//RJS 20Apr99
		/*phrase name*/			PHRASE_F80S,					//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_HIGH,
	(ANGLES)		ANGLES_0Deg,		//deck angle
			(MaxRollRate)		ANGLES_60Deg,
//DeadCode CSB 22/02/99				(MaxTurnRate)		ANGLES_22Deg,
			(MaxPitchRate)		ANGLES_15Deg,
			(LandingSpeed)		600,
			(MaxDiveRpm)		2200,				//max dive rpm
			(FreeRpm)		400,					//freewheel rpm
			(MaxRpm)		2000,
			(MinRpm)		800,
//DeadCode CSB 19/11/98				(MaxSafeVel)			1160,
			(MovableFireZoneType)	-1,
			(Damage)			0x2222,
//DeadCode CSB 19/11/98				(MaxCeilingGoodW)	600000,
//DeadCode CSB 19/11/98				(MaxCeilingBadW)	500000,
//DeadCode CSB 19/11/98				(OpCeiling)			FT_20000,
			(FightCeiling)		FT_18000,
//DeadCode CSB 19/11/98				(FightFloor)		FT_10000,
			(Abs_Ceiling)		1524000,	//cm - 50,000ft
		0.2723,		//15.6deg
				(MuzzleVel)		9500,

		(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
		(FileNum)			INVALIDFILENUM,
		(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	6,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

		(InstType)			lightinstrumtypes,
		(ACFlags)			HUDINACTIVE,

	{			
		(BestClimbAng)	2434	,
		(BestClimbAng)	2189	,
		(BestClimbAng)	1961	,
		(BestClimbAng)	1743	,
		(BestClimbAng)	1536	,
		(BestClimbAng)	1340	,
		(BestClimbAng)	1157	,
		(BestClimbAng)	984	,
		(BestClimbAng)	819	,
		(BestClimbAng)	664	,
		(BestClimbAng)	519	,
		(BestClimbAng)	381	,
		(BestClimbAng)	252	,
		(BestClimbAng)	126	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	1500	,
		(BestClimbSpeed)	1506	,
		(BestClimbSpeed)	1509	,
		(BestClimbSpeed)	1515	,
		(BestClimbSpeed)	1524	,
		(BestClimbSpeed)	1534	,
		(BestClimbSpeed)	1546	,
		(BestClimbSpeed)	1559	,
		(BestClimbSpeed)	1578	,
		(BestClimbSpeed)	1602	,
		(BestClimbSpeed)	1626	,
		(BestClimbSpeed)	1659	,
		(BestClimbSpeed)	1698	,
		(BestClimbSpeed)	1887	,
		(BestClimbSpeed)	1939	,
		(BestClimbSpeed)	1939	,
		(BestClimbSpeed)	1939	,
		(BestClimbSpeed)	1939	,
		(BestClimbSpeed)	1939	,
		(BestClimbSpeed)	1939	,
		(BestClimbSpeed)	1939	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		2640	,
	(MaxVelSL_11km)		2450	,
	(MaxVelSL_20km)		900	,
				
	(MaxVelDive_0km)	3400	,	
	(MaxVelDive_11km)	2950	,	
	(MaxVelDive_20km)	2950	,	

		/*version*/			1,

		&F80C_Setup,											//ARM 28Jan97

endinst(PlaneType,Plane_Type_F80);

startinst(PlaneType,Plane_Type_P51)						//RDH 07Apr96
	(WeightEmpty)		366600,	 //correct
	(FuelLoad)			103000,	 //Internal,
	/*shad shp*/		F51SHD,							//RJS 12May97
	/*(TextRef)*/		0,//TEXT_P51,
	/*vis shp*/			F51,					//JIM 28Mar96
	(FuelABoff)			215,
	(MaxVel)			2250,
	(MinVel)			600,			
	(CruiseVel)			1750,
	(BestClimbVel)		1100,	//935,
	(Angles)			900,	//ANGLES_10Deg,
	(MaxDiveVel)		2500,			
	(MaxAccel)			16000,		//CSB 31/05/99	
	/*pit1 shp*/		CPTF51,							//RDH 22Aug96
	/*pit2 shp*/		CPTF51,									//RJS 26Apr99
	/*msk1 shp*/		EMPTY2,							//RDH 22Aug96
	/*msk2 shp*/		EMPTY2,							//RDH 22Aug96
	/*cockpit scale*/	0.214395,								//RJS 20Apr99
	/*phrase name*/			PHRASE_F51S,						//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_HIGH,
	(Angles)			ANGLES_13Deg,		//deck angle
	(MaxRollRate)		ANGLES_60Deg,
//DeadCode CSB 22/02/99				(MaxTurnRate)		ANGLES_22Deg,
	(MaxPitchRate)		ANGLES_15Deg,
	(LandingSpeed)		600,
	(MaxDiveRpm)		4000,				//max dive rpm
	(FreeRpm)			500,					//freewheel rpm
	(MaxRpm)			3000,
	(MinRpm)			500,
//DeadCode CSB 19/11/98				(MaxSafeVel)			735,						//RDH 24Nov96
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
//DeadCode CSB 19/11/98				(MaxCeilingGoodW)	600000,
//DeadCode CSB 19/11/98				(MaxCeilingBadW)	500000,
//DeadCode CSB 19/11/98				(OpCeiling)			FT_16000,
	(FightCeiling)		FT_14000,
//DeadCode CSB 19/11/98				(FightFloor)		FT_10000,
	(Abs_Ceiling)		1250000,
						0.2723,		//15.6deg
	(MuzzleVel)			9500,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_P51_INT_LOOP,				//RJS 16Sep98
/* number of guns */	6,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

	{			
		(BestClimbAng)	1112	,
		(BestClimbAng)	1209	,
		(BestClimbAng)	1296	,
		(BestClimbAng)	1254	,
		(BestClimbAng)	1064	,
		(BestClimbAng)	1030	,
		(BestClimbAng)	1091	,
		(BestClimbAng)	1013	,
		(BestClimbAng)	788	,
		(BestClimbAng)	550	,
		(BestClimbAng)	344	,
		(BestClimbAng)	137	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
//DeadCode CSB 31/05/99			(BestClimbAng)	2240	,
//DeadCode CSB 31/05/99			(BestClimbAng)	2230	,
//DeadCode CSB 31/05/99			(BestClimbAng)	2190	,
//DeadCode CSB 31/05/99			(BestClimbAng)	2110	,
//DeadCode CSB 31/05/99			(BestClimbAng)	2000	,
//DeadCode CSB 31/05/99			(BestClimbAng)	1850	,
//DeadCode CSB 31/05/99			(BestClimbAng)	1675	,
//DeadCode CSB 31/05/99			(BestClimbAng)	1475	,
//DeadCode CSB 31/05/99			(BestClimbAng)	1225	,
//DeadCode CSB 31/05/99			(BestClimbAng)	925	,
//DeadCode CSB 31/05/99			(BestClimbAng)	625	,
//DeadCode CSB 31/05/99			(BestClimbAng)	275	,
//DeadCode CSB 31/05/99			(BestClimbAng)	0	,
//DeadCode CSB 31/05/99			(BestClimbAng)	0	,
//DeadCode CSB 31/05/99			(BestClimbAng)	0	,
//DeadCode CSB 31/05/99			(BestClimbAng)	0	,
//DeadCode CSB 31/05/99			(BestClimbAng)	0	,
//DeadCode CSB 31/05/99			(BestClimbAng)	0	,
//DeadCode CSB 31/05/99			(BestClimbAng)	0	,
//DeadCode CSB 31/05/99			(BestClimbAng)	0	,
//DeadCode CSB 31/05/99			(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1200	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	711	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	760	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	809	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	858	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	907	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	956	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1006	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1055	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1104	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1153	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1202	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1251	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1300	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1300	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1300	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1300	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1300	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1300	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1300	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1300	,
//DeadCode CSB 31/05/99			(BestClimbSpeed)	1300	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		1700	,
	(MaxVelSL_11km)		1900	,
	(MaxVelSL_20km)		0	,
				
	(MaxVelDive_0km)	3050	,	
	(MaxVelDive_11km)	2650	,	
	(MaxVelDive_20km)	2650	,	

		/*version*/			1,

	&F51D_Setup,											//ARM 04Feb97

endinst(PlaneType,Plane_Type_P51);							//RDH 07Apr96



startinst(PlaneType,Plane_Type_P82)						//RDH 07Apr96
//
			(WeightEmpty)	490300,	  
			(FuelLoad)		103000,//Internal, //182000 Max 73210,								//CSB	126400,
			/*shad shp*/		F82SHD,							//RJS 29Jun99
			/*(TextRef)*/		0,//TEXT_P51,
			/*vis shp*/			F82,							//RJS 29Jun99
			(FuelABoff)		215,						//CSB
//DeadCode CSB 18/11/98				(FuelCruise)	125,	//CSB	270,				//cg/cs
	(MaxVel)			2500,
	(MinVel)			165,							//RDH 24Nov96
	(CruiseVel)			1678,
	(BestClimbVel)		1840,	//935,
	(Angles)			1558,	//ANGLES_13Deg,
	(MaxDiveVel)		3000,						//RDH 04Dec96
	(MaxAccel)			12000,							//PD 17Oct96
			/*pit1 shp*/		CPTF51,							//RDH 22Aug96
			/*pit2 shp*/		CPTF51,							//RJS 26Apr99
			/*msk1 shp*/		EMPTY2,							//RDH 22Aug96
			/*msk2 shp*/		EMPTY2,							//RDH 22Aug96
		/*cockpit scale*/		1,								//RJS 19Jan99
		/*phrase name*/			PHRASE_F82S,					//RJS 18Mar99
			(AerobaticFactor)	AEROBATIC_MEDIUM,
			(Angles)		ANGLES_14Deg,		//deck angle
			(MaxRollRate)		ANGLES_60Deg,
//DeadCode CSB 22/02/99				(MaxTurnRate)		ANGLES_22Deg,
			(MaxPitchRate)		ANGLES_15Deg,
			(LandingSpeed)		600,
			(MaxDiveRpm)		1400,				//max dive rpm
			(FreeRpm)		400,					//freewheel rpm
			(MaxRpm)		1150,
			(MinRpm)		800,
//DeadCode CSB 19/11/98				(MaxSafeVel)			735,						//RDH 24Nov96
			(MovableFireZoneType)	-1,
			(Damage)			0x2222,
//DeadCode CSB 19/11/98				(MaxCeilingGoodW)	600000,
//DeadCode CSB 19/11/98				(MaxCeilingBadW)	500000,
//DeadCode CSB 19/11/98				(OpCeiling)			FT_16000,
			(FightCeiling)		FT_14000,
//DeadCode CSB 19/11/98				(FightFloor)		FT_10000,
			(Abs_Ceiling)		1524000,	//cm - 50,000ft		//DAW 07Oct98
		0.2723,		//15.6deg
				(MuzzleVel)		9500,

		(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
		(FileNum)			INVALIDFILENUM,
		(FileNum)			FIL_SFX_P51_INT_LOOP,				//RJS 16Sep98
/* number of guns */	6,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

		(InstType)			lightinstrumtypes,
		(ACFlags)			HUDINACTIVE,
//DeadCode CSB 16/11/98					{	(ThrustCurve)		1000,							
//DeadCode CSB 16/11/98				(ThrustCurve)		968,							
//DeadCode CSB 16/11/98				(ThrustCurve)		947,							
//DeadCode CSB 16/11/98				(ThrustCurve)		934,							
//DeadCode CSB 16/11/98				(ThrustCurve)		929,							
//DeadCode CSB 16/11/98				(ThrustCurve)		934,							
//DeadCode CSB 16/11/98				(ThrustCurve)		960,							
//DeadCode CSB 16/11/98				(ThrustCurve)		1033,							
//DeadCode CSB 16/11/98				(ThrustCurve)		1124,							
//DeadCode CSB 16/11/98				(ThrustCurve)		1210,							
//DeadCode CSB 16/11/98				(ThrustCurve)		1288,
//DeadCode CSB 16/11/98				(ThrustCurve)		1366,
//DeadCode CSB 16/11/98				(ThrustCurve)		1448,
//DeadCode CSB 16/11/98				(ThrustCurve)		1513
//DeadCode CSB 16/11/98			},
//DeadCode CSB 16/11/98	//thrustaltcurve: default is the air density ratio
//DeadCode CSB 16/11/98			{			1.0,							//SL
//DeadCode CSB 16/11/98						0.9074,							//1000m
//DeadCode CSB 16/11/98						0.8215,							//2000m
//DeadCode CSB 16/11/98						0.7420,							//3000m
//DeadCode CSB 16/11/98						0.6685,							//4000m
//DeadCode CSB 16/11/98						0.6007,							//5000m
//DeadCode CSB 16/11/98						0.5383,							//6000m
//DeadCode CSB 16/11/98						0.4810,							//7000m
//DeadCode CSB 16/11/98						0.4285,							//8000m
//DeadCode CSB 16/11/98						0.3805,							//9000m
//DeadCode CSB 16/11/98						0.3367,							//10000m
//DeadCode CSB 16/11/98						0.2968,							//11000m
//DeadCode CSB 16/11/98						0.2535,							//12000m
//DeadCode CSB 16/11/98						0.2166,							//13000m
//DeadCode CSB 16/11/98						0.1850,							//14000m
//DeadCode CSB 16/11/98						0.1580,							//15000m
//DeadCode CSB 16/11/98						0.1349,							//16000m
//DeadCode CSB 16/11/98						0.1153,							//17000m
//DeadCode CSB 16/11/98						0.0984,							//18000m
//DeadCode CSB 16/11/98						0.0841,							//19000m
//DeadCode CSB 16/11/98						0.0718							//20000m
//DeadCode CSB 16/11/98						
//DeadCode CSB 16/11/98			},
	{
		(BestClimbAng)	3024	,	//CSB 28/09/98
		(BestClimbAng)	2665	,
		(BestClimbAng)	2342	,
		(BestClimbAng)	2051	,
		(BestClimbAng)	1790	,
		(BestClimbAng)	1558	,
		(BestClimbAng)	1352	,
		(BestClimbAng)	1169	,
		(BestClimbAng)	1009	,
		(BestClimbAng)	869	,
		(BestClimbAng)	747	,
		(BestClimbAng)	641	,
		(BestClimbAng)	546	,
		(BestClimbAng)	462	,
		(BestClimbAng)	381	,
		(BestClimbAng)	300	,
		(BestClimbAng)	208	,
		(BestClimbAng)	94	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},

	{			
		(BestClimbSpeed)	1882	,
		(BestClimbSpeed)	1867	,
		(BestClimbSpeed)	1853	,
		(BestClimbSpeed)	1844	,
		(BestClimbSpeed)	1839	,
		(BestClimbSpeed)	1840	,
		(BestClimbSpeed)	1847	,
		(BestClimbSpeed)	1862	,
		(BestClimbSpeed)	1887	,
		(BestClimbSpeed)	1922	,
		(BestClimbSpeed)	1970	,
		(BestClimbSpeed)	2031	,
		(BestClimbSpeed)	2104	,
		(BestClimbSpeed)	2193	,
		(BestClimbSpeed)	2288	,
		(BestClimbSpeed)	2388	,
		(BestClimbSpeed)	2488	,
		(BestClimbSpeed)	2585	,
		(BestClimbSpeed)	2684	,
		(BestClimbSpeed)	0	,
		(BestClimbSpeed)	0
	},			

	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},	
	
	(MaxVelSL_0km)		3016,	//CSB 28/09/98
	(MaxVelSL_11km)		2613,	//CSB 28/09/98
	(MaxVelSL_20km)		2000,	//CSB 28/09/98

	(MaxVelDive_0km)	3050	,	
	(MaxVelDive_11km)	2650	,	
	(MaxVelDive_20km)	2650	,	

		/*version*/			1,

		&F51D_Setup,											//ARM 04Feb97

endinst(PlaneType,Plane_Type_P82);							//RDH 07Apr96




startinst(PlaneType,Plane_Type_MIG15)						//RDH 07Apr96
	(WeightEmpty)		372300,//correct
	(FuelLoad)			 98700,//correct
	/*shad shp*/		M15SHD,							//RJS 10Jun97
	/*(TextRef)*/		0,//TEXT_MIG15,
	/*vis shp*/			CMIG15,							//JIM 28Mar96
	(FuelABoff)			560,//correct
//DeadCode CSB 18/11/98				(FuelCruise)	150,			//CSB	270,			//cg/cs

	(MaxVel)			2900,//652 mph
	(MinVel)			450, //100 mph
	(CruiseVel)			2250,//450 mph
	(BestClimbVel)		1750,//450 mph
	(Angles)			1500,	//ANGLES_10Deg,
	(MaxDiveVel)		3100,//700 mph						//RDH 04Dec96
	(MaxAccel)			14799,		//CSB 28/05/99	
	/*pit1 shp*/		CPTM15,							//RDH 22Aug96
	/*pit2 shp*/		CPTM15,									//RJS 26Apr99
	/*msk1 shp*/		EMPTY2,							//RDH 22Aug96
	/*msk2 shp*/		EMPTY2,							//RDH 22Aug96
	/*cockpit scale*/	0.117647,								//RJS 20Apr99
	/*phrase name*/		PHRASE_MIGS,							//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_FIGHTER,
	(Angles)			ANGLES_0Deg,		//deck angle
	(MaxRollRate)		ANGLES_60Deg,
//DeadCode CSB 22/02/99		(MaxTurnRate)		ANGLES_22Deg,
	(MaxPitchRate)		ANGLES_15Deg,
	(LandingSpeed)		600, 
	(MaxDiveRpm)		4640,				//max dive rpm
	(FreeRpm)			500,					//freewheel rpm
	(MaxRpm)			4640,
	(MinRpm)			500,
//DeadCode CSB 19/11/98		(MaxSafeVel)		3100,
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
//DeadCode CSB 19/11/98				(MaxCeilingGoodW)	600000,
//DeadCode CSB 19/11/98				(MaxCeilingBadW)	500000,
//DeadCode CSB 19/11/98				(OpCeiling)			FT_16000,
	(FightCeiling)		1450000, //47000 ft
//DeadCode CSB 19/11/98				(FightFloor)		FT_10000,
	(Abs_Ceiling)		1560000,	//cm - 51250ft
		0.26,		//15deg		sustained aoa
	(MuzzleVel)			6900,//Cannon	9143,//Machine Gun	//

	(FileNum)			FIL_SFX_MIG_CANNON_LOOP1,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	4,										//RJS 29Mar99
/* gun sfx delay */		32,										//RJS 12Apr99
/* gun FF freq */		40,										//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

		{			
		(BestClimbAng)	3037	,
		(BestClimbAng)	2741	,
		(BestClimbAng)	2463	,
		(BestClimbAng)	2201	,
		(BestClimbAng)	1946	,
		(BestClimbAng)	1707	,
		(BestClimbAng)	1482	,
		(BestClimbAng)	1150	,
		(BestClimbAng)	977	,
		(BestClimbAng)	818	,
		(BestClimbAng)	626	,
		(BestClimbAng)	513	,
		(BestClimbAng)	383	,
		(BestClimbAng)	260	,
		(BestClimbAng)	138	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	1744	,
		(BestClimbSpeed)	1750	,
		(BestClimbSpeed)	1754	,
		(BestClimbSpeed)	1758	,
		(BestClimbSpeed)	1769	,
		(BestClimbSpeed)	1779	,
		(BestClimbSpeed)	1791	,
		(BestClimbSpeed)	2015	,
		(BestClimbSpeed)	2045	,
		(BestClimbSpeed)	2068	,
		(BestClimbSpeed)	2246	,
		(BestClimbSpeed)	2228	,
		(BestClimbSpeed)	2237	,
		(BestClimbSpeed)	2237	,
		(BestClimbSpeed)	2238	,
		(BestClimbSpeed)	2239	,
		(BestClimbSpeed)	2239	,
		(BestClimbSpeed)	2239	,
		(BestClimbSpeed)	2239	,
		(BestClimbSpeed)	2239	,
		(BestClimbSpeed)	2239	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		2894	,
	(MaxVelSL_11km)		2590	,
	(MaxVelSL_20km)		1800	,
				
	(MaxVelDive_0km)	3400	,	
	(MaxVelDive_11km)	2950	,	
	(MaxVelDive_20km)	2950	,	

	/*version*/			1,

	&MIG15_Setup,											//ARM 06Feb97

endinst(PlaneType,Plane_Type_MIG15);							//RDH 07Apr96

/////////////////////////////////////////////////////////////////////////////////////////

startinst(PlaneType,Plane_Type_MIG15BIS)						//RDH 07Apr96
			(WeightEmpty)	388100,//correct
			(FuelLoad)		115500,//correct
			/*shad shp*/		M15SHD,							//RJS 10Jun97
			/*(TextRef)*/	0,//	TEXT_MIG15,
			/*vis shp*/			CMIG15,						//RDH 10/05/99
			(FuelABoff)		560,	//correct
//DeadCode CSB 18/11/98				(FuelCruise)	270,			//cg/cs

			(MaxVel)			3000,
			(MinVel)			147,
	(CruiseVel)			2476,
	(BestClimbVel)		2194,
	(Angles)			1810,	//ANGLES_10Deg,
	(MaxDiveVel)		3000,						//RDH 04Dec96
	(MaxAccel)			16917,		//CSB 28/05/99	
			/*pit1 shp*/		CPTM15,							//RDH 22Aug96
			/*pit2 shp*/		CPTM15,							//RJS 26Apr99
			/*msk1 shp*/		EMPTY2,							//RDH 22Aug96
			/*msk2 shp*/		EMPTY2,							//RDH 22Aug96
		/*cockpit scale*/	0.117647,							//RJS 21May99
		/*phrase name*/			PHRASE_MIGS,					//RJS 18Mar99
			(AerobaticFactor)	AEROBATIC_FIGHTER,
			(Angles)		ANGLES_14Deg,		//deck angle
			(MaxRollRate)		ANGLES_90Deg,
//DeadCode CSB 22/02/99				(MaxTurnRate)		ANGLES_22Deg,
			(MaxPitchRate)		ANGLES_15Deg,
			(LandingSpeed)		600,
			(MaxDiveRpm)		1400,				//max dive rpm
			(FreeRpm)		400,					//freewheel rpm
			(MaxRpm)		1150,
			(MinRpm)		800,
//DeadCode CSB 19/11/98				(MaxSafeVel)			700,
			(MovableFireZoneType)	-1,
			(Damage)			0x2222,
//DeadCode CSB 19/11/98				(MaxCeilingGoodW)	600000,
//DeadCode CSB 19/11/98				(MaxCeilingBadW)	500000,
//DeadCode CSB 19/11/98				(OpCeiling)			FT_16000,
			(FightCeiling)		FT_14000,
//DeadCode CSB 19/11/98				(FightFloor)		FT_10000,
			(Abs_Ceiling)		1524000,	//cm - 50,000ft
		0.26,		//15deg		sustained aoa
				(MuzzleVel)		6900,

		(FileNum)			FIL_SFX_MIG_CANNON_LOOP1,
		(FileNum)			INVALIDFILENUM,
		(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	4,										//RJS 29Mar99
/* gun sfx delay */		32,										//RJS 12Apr99
/* gun FF freq */		40,										//RJS 31May99

		(InstType)			lightinstrumtypes,
		(ACFlags)			HUDINACTIVE,

			{			
		(BestClimbAng)	3462	,
		(BestClimbAng)	3138	,
		(BestClimbAng)	2534	,
		(BestClimbAng)	2280	,
		(BestClimbAng)	2039	,
		(BestClimbAng)	1810	,
		(BestClimbAng)	1491	,
		(BestClimbAng)	1335	,
		(BestClimbAng)	1186	,
		(BestClimbAng)	1041	,
		(BestClimbAng)	896	,
		(BestClimbAng)	751	,
		(BestClimbAng)	590	,
		(BestClimbAng)	436	,
		(BestClimbAng)	285	,
		(BestClimbAng)	138	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	1896	,
		(BestClimbSpeed)	1900	,
		(BestClimbSpeed)	2151	,
		(BestClimbSpeed)	2163	,
		(BestClimbSpeed)	2177	,
		(BestClimbSpeed)	2194	,
		(BestClimbSpeed)	2377	,
		(BestClimbSpeed)	2358	,
		(BestClimbSpeed)	2330	,
		(BestClimbSpeed)	2297	,
		(BestClimbSpeed)	2265	,
		(BestClimbSpeed)	2231	,
		(BestClimbSpeed)	2241	,
		(BestClimbSpeed)	2249	,
		(BestClimbSpeed)	2281	,
		(BestClimbSpeed)	2328	,
		(BestClimbSpeed)	2369	,
		(BestClimbSpeed)	2369	,
		(BestClimbSpeed)	2369	,
		(BestClimbSpeed)	2369	,
		(BestClimbSpeed)	2369	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		2994	,
	(MaxVelSL_11km)		2698	,
	(MaxVelSL_20km)		2100	,
				
	(MaxVelDive_0km)	3400	,	
	(MaxVelDive_11km)	2950	,	
	(MaxVelDive_20km)	2950	,	

		/*version*/			2,

		&MIG15_Setup,											//ARM 06Feb97

endinst(PlaneType,Plane_Type_MIG15BIS);							//RDH 07Apr96

/////////////////////////////////////////////////////////////////////////////////////////

startinst(PlaneType,Plane_Type_B26)
	(WeightEmpty)		1136000,//correct
	(FuelLoad)			 400000,//correct
	/*shad shp*/		B26SHD,	
	/*(TextRef)*/		0,//TEXT_B29,
	/*vis shp*/			B26,	
	(FuelABoff)			1000,	//cg/cs

	(MaxVel)			1260,//282 mph
	(MinVel)			 500,//112 mph
	(CruiseVel)			1125,//1184,//212 mph
	(BestClimbVel)		750,//190 mph
	(Angles)			750,	//ANGLES_5Deg,
	(MaxDiveVel)		2250,
	(MaxAccel)			5000,//Guess
	/*pit1 shp*/		EMPTY2,
	/*pit2 shp*/		EMPTY2,
	/*msk1 shp*/		EMPTY2,
	/*msk2 shp*/		EMPTY2,
	/*cockpit scale*/		1,								//RJS 19Jan99
	/*phrase name*/		PHRASE_B26S,							//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_LOW,
	(Angles)			ANGLES_0Deg,		//deck angle
	(MaxRollRate)		ANGLES_40Deg,
//DeadCode CSB 22/02/99		(MaxTurnRate)		ANGLES_10Deg,
	(MaxPitchRate)		ANGLES_10Deg,
	(LandingSpeed)		500,//112 mph
	(MaxDiveRpm)		3000,//guess				//max dive rpm
	(FreeRpm)			500,					//freewheel rpm
	(MaxRpm)			2750,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
	(FightCeiling)		500000,//16400 ft
	(Abs_Ceiling)		610000,//20000 ft
		0.2723,		//15.6deg
	(MuzzleVel)			6000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	4,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

	{			
		(BestClimbAng)	1000	,
		(BestClimbAng)	975	,
		(BestClimbAng)	900	,
		(BestClimbAng)	750	,
		(BestClimbAng)	500	,
		(BestClimbAng)	200	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	750	,
		(BestClimbSpeed)	850	,
		(BestClimbSpeed)	950	,
		(BestClimbSpeed)	1050	,
		(BestClimbSpeed)	1150	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	,
		(BestClimbSpeed)	1250	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		1250	,
	(MaxVelSL_11km)		1250	,
	(MaxVelSL_20km)		1250	,
				
	(MaxVelDive_0km)	3050	,	
	(MaxVelDive_11km)	2650	,	
	(MaxVelDive_20km)	2650	,	

		/*version*/			1,

		&B26_Setup,

endinst(PlaneType,Plane_Type_B26);

/////////////////////////////////////////////////////////////////////////////////////////

startinst(PlaneType,Plane_Type_B29)						//RDH 07Apr96
	(WeightEmpty)		3336900,//correct
	(FuelLoad)			2000000,//correct
	/*shad shp*/		B29SHD,							//RJS 12May97
	/*(TextRef)*/	0,//	TEXT_B29,
	/*vis shp*/			B29,//MIG15,							//JIM 28Mar96
	(FuelABoff)			2000,	//cg/cs
//DeadCode CSB 18/11/98				(FuelCruise)	144,				//cg/cs

	(MaxVel)			1600,//358 mph
	(MinVel)			 500,//112 mph
	(CruiseVel)			1400,//270 mph
	(BestClimbVel)		 950,	//1019,//236 mph
	(Angles)			 775,	//ANGLES_5Deg,
	(MaxDiveVel)		2250,						
	(MaxAccel)			5000,//Guess							//PD 17Oct96
	/*pit1 shp*/		EMPTY2,							//RDH 22Aug96
	/*pit2 shp*/		EMPTY2,						//RDH 22Aug96
	/*msk1 shp*/		EMPTY2,							//RDH 22Aug96
	/*msk2 shp*/		EMPTY2,							//RDH 22Aug96
	/*cockpit scale*/	1,								//RJS 19Jan99
	/*phrase name*/		PHRASE_B29S,							//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_LOW,
	(Angles)			ANGLES_0Deg,		//deck angle
	(MaxRollRate)		ANGLES_20Deg,
//DeadCode CSB 22/02/99		(MaxTurnRate)		ANGLES_5Deg,
	(MaxPitchRate)		ANGLES_10Deg,
	(LandingSpeed)		500,//112 mph
	(MaxDiveRpm)		3000,//guess				//max dive rpm
	(FreeRpm)			500,					//freewheel rpm
	(MaxRpm)			2750,
	(MinRpm)			500,
//DeadCode CSB 19/11/98		(MaxSafeVel)		20000,
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
//DeadCode CSB 19/11/98				(MaxCeilingGoodW)	600000,
//DeadCode CSB 19/11/98				(MaxCeilingBadW)	500000,
//DeadCode CSB 19/11/98				(OpCeiling)			FT_16000,
	(FightCeiling)		945000,//31000 ft
//DeadCode CSB 19/11/98				(FightFloor)		FT_10000,
	(Abs_Ceiling)		990000,//32500 ft
		0.2723,		//15.6deg
	(MuzzleVel)			6000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	1,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

		{			
		(BestClimbAng)	1500	,
		(BestClimbAng)	1500	,
		(BestClimbAng)	1475	,
		(BestClimbAng)	1425	,
		(BestClimbAng)	1350	,
		(BestClimbAng)	1200	,
		(BestClimbAng)	1000	,
		(BestClimbAng)	750	,
		(BestClimbAng)	500	,
		(BestClimbAng)	250	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	1000	,
		(BestClimbSpeed)	1000	,
		(BestClimbSpeed)	1000	,
		(BestClimbSpeed)	1000	,
		(BestClimbSpeed)	1010	,
		(BestClimbSpeed)	1025	,
		(BestClimbSpeed)	1050	,
		(BestClimbSpeed)	1100	,
		(BestClimbSpeed)	1200	,
		(BestClimbSpeed)	1400	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	,
		(BestClimbSpeed)	1600	
	},			
				
	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			
				
	(MaxVelSL_0km)		1600	,
	(MaxVelSL_11km)		1600	,
	(MaxVelSL_20km)		1600	,
				
	(MaxVelDive_0km)	3050	,	
	(MaxVelDive_11km)	2650	,	
	(MaxVelDive_20km)	2650	,	

		/*version*/			1,

		&B29_Setup,											//ARM 28Jan97

endinst(PlaneType,Plane_Type_B29);								//RDH 17Feb97

/////////////////////////////////////////////////////////////////////////////////////////

startinst(PlaneType,Plane_Type_T6)	
	(WeightEmpty)		188600,
	(FuelLoad)			50000,
	/*shad shp*/		T6SHD,									//RJS 29Jun99
	/*(TextRef)*/		0,//TEXT_B29,
	/*vis shp*/			T6,//MIG15,							//JIM 28Mar96
	(FuelABoff)			1,

	(MaxVel)			 910,//205 mph
	(MinVel)			 444,//100 mph
	(CruiseVel)			 820,//175 mph
	(BestClimbVel)		 736,//150 mph
	(Angles)			ANGLES_10Deg,
	(MaxDiveVel)		1111,//250 mph						
	(MaxAccel)			10000,//Guess
	/*pit1 shp*/		EMPTY2,		
	/*pit2 shp*/		EMPTY2,		
	/*msk1 shp*/		EMPTY2,		
	/*msk2 shp*/		EMPTY2,		
	/*cockpit scale*/	1,								//RJS 19Jan99
	/*phrase name*/		PHRASE_F86S,							//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_LOW,
	(Angles)			ANGLES_5Deg,		//deck angle
	(MaxRollRate)		ANGLES_90Deg,
//DeadCode CSB 22/02/99		(MaxTurnRate)		ANGLES_8Deg,
	(MaxPitchRate)		ANGLES_15Deg,
	(LandingSpeed)		444,//100 mph
	(MaxDiveRpm)		3000,//guess				//max dive rpm
	(FreeRpm)			500,					//freewheel rpm
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
	(FightCeiling)		650000,
	(Abs_Ceiling)		700000,
						0.3491,		//20 deg
	(MuzzleVel)			6000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	1,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

	{
		(BestClimbAng)	3024	,
		(BestClimbAng)	2665	,
		(BestClimbAng)	2342	,
		(BestClimbAng)	2051	,
		(BestClimbAng)	1790	,
		(BestClimbAng)	1558	,
		(BestClimbAng)	1352	,
		(BestClimbAng)	1169	,
		(BestClimbAng)	1009	,
		(BestClimbAng)	869	,
		(BestClimbAng)	747	,
		(BestClimbAng)	641	,
		(BestClimbAng)	546	,
		(BestClimbAng)	462	,
		(BestClimbAng)	381	,
		(BestClimbAng)	300	,
		(BestClimbAng)	208	,
		(BestClimbAng)	94	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},

	{			
		(BestClimbSpeed)	753	,
		(BestClimbSpeed)	747 ,
		(BestClimbSpeed)	741	,
		(BestClimbSpeed)	738	,
		(BestClimbSpeed)	736	,
		(BestClimbSpeed)	736	,
		(BestClimbSpeed)	739	,
		(BestClimbSpeed)	745	,
		(BestClimbSpeed)	755	,
		(BestClimbSpeed)	769 ,
		(BestClimbSpeed)	788	,
		(BestClimbSpeed)	812	,
		(BestClimbSpeed)	842	,
		(BestClimbSpeed)	877	,
		(BestClimbSpeed)	915	,
		(BestClimbSpeed)	955	,
		(BestClimbSpeed)	995	,
		(BestClimbSpeed)	1034,
		(BestClimbSpeed)	1074,
		(BestClimbSpeed)	1074,
		(BestClimbSpeed)	1074	
	},

	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},	
	
	(MaxVelSL_0km)		911,
	(MaxVelSL_11km)		911,
	(MaxVelSL_20km)		778,

	(MaxVelDive_0km)	3050,
	(MaxVelDive_11km)	2650,
	(MaxVelDive_20km)	2650,

		/*version*/			1,

		&T6_Setup,

endinst(PlaneType,Plane_Type_T6);

/////////////////////////////////////////////////////////////////////////////////////////

startinst(PlaneType,Plane_Type_F4U)
	(WeightEmpty)		407400,
	(FuelLoad)			120000,
	/*shad shp*/		CORSHD,									//RJS 29Jun99
	/*(TextRef)*/		0,//TEXT_B29,
	/*vis shp*/			CORS,//MIG15,							//JIM 28Mar96
	(FuelABoff)			1,
	(MaxVel)			1600,
	(MinVel)			 500,
	(CruiseVel)			1637,
	(BestClimbVel)		1389,
	(Angles)			ANGLES_10Deg,
	(MaxDiveVel)		2250,						
	(MaxAccel)			10000,
	/*pit1 shp*/		EMPTY2,							//RDH 22Aug96
	/*pit2 shp*/		EMPTY2,						//RDH 22Aug96
	/*msk1 shp*/		EMPTY2,							//RDH 22Aug96
	/*msk2 shp*/		EMPTY2,							//RDH 22Aug96
	/*cockpit scale*/	1,								//RJS 19Jan99
	/*phrase name*/		PHRASE_CORSS,							//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_LOW,
	(Angles)			ANGLES_5Deg,		//deck angle
	(MaxRollRate)		ANGLES_90Deg,
//DeadCode CSB 22/02/99		(MaxTurnRate)		ANGLES_10Deg,
	(MaxPitchRate)		ANGLES_15Deg,
	(LandingSpeed)		 500,
	(MaxDiveRpm)		3000,//guess				//max dive rpm
	(FreeRpm)			500,					//freewheel rpm
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
	(FightCeiling)		650000,
	(Abs_Ceiling)		1124700,
						0.3491,		//20 deg
	(MuzzleVel)			6000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_JET_INTERNAL_LOOP,
/* number of guns */	1,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

	{			
		(BestClimbAng)	1820	,
		(BestClimbAng)	1295	,
		(BestClimbAng)	1077	,
		(BestClimbAng)	910	,
		(BestClimbAng)	769	,
		(BestClimbAng)	645	,
		(BestClimbAng)	533	,
		(BestClimbAng)	430	,
		(BestClimbAng)	334	,
		(BestClimbAng)	244	,
		(BestClimbAng)	159	,
		(BestClimbAng)	77	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			

	{			
		(BestClimbSpeed)	1353	,
		(BestClimbSpeed)	1355	,
		(BestClimbSpeed)	1360	,
		(BestClimbSpeed)	1368	,
		(BestClimbSpeed)	1380	,
		(BestClimbSpeed)	1395	,
		(BestClimbSpeed)	1414	,
		(BestClimbSpeed)	1436	,
		(BestClimbSpeed)	1461	,
		(BestClimbSpeed)	1489	,
		(BestClimbSpeed)	1521	,
		(BestClimbSpeed)	1557	,
		(BestClimbSpeed)	1596	,
		(BestClimbSpeed)	1596	,
		(BestClimbSpeed)	1596	,
		(BestClimbSpeed)	1596	,
		(BestClimbSpeed)	1596	,
		(BestClimbSpeed)	1596	,
		(BestClimbSpeed)	1596	,
		(BestClimbSpeed)	1596	,
		(BestClimbSpeed)	1596	
	},			

	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			

	(MaxVelSL_0km)		2127	,
	(MaxVelSL_11km)		1752	,
	(MaxVelSL_20km)		1596	,

	(MaxVelDive_0km)	3050,
	(MaxVelDive_11km)	2650,
	(MaxVelDive_20km)	2650,

		/*version*/			1,

	&F4U5_Setup,						

endinst(PlaneType,Plane_Type_F4U);	

/////////////////////////////////////////////////////////////////////////////////////////

startinst(PlaneType,Plane_Type_YAK9)	
//
	(WeightEmpty)		277000,	 //correct
	(FuelLoad)			 67900,
	/*shad shp*/		YAKSHD,									//RJS 29Jun99
	/*(TextRef)*/	  0,//TEXT_P51,
	/*vis shp*/			  YAK9,	
	(FuelABoff)			    215,	
	(MaxVel)			  1850,
	(MinVel)			   500,	
	(CruiseVel)			  1905,
	(BestClimbVel)		  1288,
	(Angles)	  ANGLES_10Deg,
	(MaxDiveVel)		  3000,
	(MaxAccel)			 10000,	
	/*pit1 shp*/		CPTF51,							//RDH 22Aug96
	/*pit2 shp*/		CPTF51,									//RJS 26Apr99
	/*msk1 shp*/		EMPTY2,							//RDH 22Aug96
	/*msk2 shp*/		EMPTY2,							//RDH 22Aug96
	/*cockpit scale*/ 	0.214395,								//RJS 20Apr99
/*phrase name*/			PHRASE_YAK9S,							//RJS 18Mar99
	(AerobaticFactor)	AEROBATIC_HIGH,
	(Angles)			ANGLES_11Deg,		//deck angle
	(MaxRollRate)		ANGLES_60Deg,
//DeadCode CSB 22/02/99		(MaxTurnRate)		ANGLES_10Deg,
	(MaxPitchRate)		ANGLES_15Deg,
	(LandingSpeed)		600,
	(MaxDiveRpm)		3000,				//max dive rpm
	(FreeRpm)			500,					//freewheel rpm
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,
	(Damage)			0x2222,
	(FightCeiling)		FT_14000,
	(Abs_Ceiling)		1060000,
						0.2723,		//15.6deg
	(MuzzleVel)			6000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,
	(FileNum)			INVALIDFILENUM,
	(FileNum)			FIL_SFX_P51_INT_LOOP,				//RJS 16Sep98
/* number of guns */	4,										//RJS 29Mar99
/* gun sfx delay */		24,										//RJS 12Apr99
/* gun FF freq */		120,									//RJS 31May99

	(InstType)			lightinstrumtypes,
	(ACFlags)			HUDINACTIVE,

	{			
		(BestClimbAng)	1820	,
		(BestClimbAng)	1244	,
		(BestClimbAng)	1006	,
		(BestClimbAng)	823	,
		(BestClimbAng)	669	,
		(BestClimbAng)	533	,
		(BestClimbAng)	410	,
		(BestClimbAng)	297	,
		(BestClimbAng)	192	,
		(BestClimbAng)	93	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			

	{			
		(BestClimbSpeed)	1037	,
		(BestClimbSpeed)	1049	,
		(BestClimbSpeed)	1085	,
		(BestClimbSpeed)	1144	,
		(BestClimbSpeed)	1227	,
		(BestClimbSpeed)	1334	,
		(BestClimbSpeed)	1464	,
		(BestClimbSpeed)	1618	,
		(BestClimbSpeed)	1796	,
		(BestClimbSpeed)	1997	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	,
		(BestClimbSpeed)	2222	
	},			

	{	(DiveVelFactor)	0	,
		(DiveVelFactor)	429	,
		(DiveVelFactor)	626	,
		(DiveVelFactor)	750	,
		(DiveVelFactor)	842	,
		(DiveVelFactor)	917	,
		(DiveVelFactor)	967	,
		(DiveVelFactor)	990	,
		(DiveVelFactor)	1000	
	},			

	(MaxVelSL_0km)		1631	,
	(MaxVelSL_11km)		2222	,
	(MaxVelSL_20km)		2222	,

	(MaxVelDive_0km)	3050,
	(MaxVelDive_11km)	2650,
	(MaxVelDive_20km)	2650,

	/*version*/			1,

//DEADCODE CSB 27/04/99 	&YAK9_Setup,
	&YAK9_Setup,

endinst(PlaneType,Plane_Type_YAK9);	

/////////////////////////////////////////////////////////////////////////////////////////


startinst(WheeledType,ATruck)
			(WeightEmpty)	5539,
			(FuelLoad)		130000000,
			/*shad shp*/		EMPTY2,
			/*(TextRef)*/		0,//TEXT_DAY,
			/*vis shp*/			EMPTY2,							//JIM 28Mar96
			(FuelABoff)		180,
//DeadCode CSB 18/11/98				(FuelCruise)	144,				//mg/cs

			(MaxVel)			50,
			(MinVel)			1,
			(CruiseVel)			40,
			(BestClimbVel)		30,
			(Angles)			ANGLES_45Deg,
			(MaxDiveVel)		60,
			(MaxAccel)			12000,
endinst(WheeledType,ATruck);


startinst(WheeledType,ATank)
			(WeightEmpty)	5539,
			(FuelLoad)		130000000,
			/*shad shp*/		EMPTY2,
			/*(TextRef)*/		0,//TEXT_DAY,
			/*vis shp*/			EMPTY2,							//JIM 28Mar96
			(FuelABoff)		180,
//DeadCode CSB 18/11/98				(FuelCruise)	144,				//mg/cs

			(MaxVel)			18,	//4 mph
			(MinVel)			1,	//this is the lowest you can push
			(CruiseVel)			8,	//the vel to generate a delta
			(BestClimbVel)		6,
			(Angles)			ANGLES_45Deg,
			(MaxDiveVel)		20,
			(MaxAccel)			12000,
endinst(WheeledType,ATank);


PlaneInit*	Plane_Type_Translate[]	=
			{	&Plane_Type_F86A,
				&Plane_Type_F86E,
				&Plane_Type_F86F,
				&Plane_Type_F84,
				&Plane_Type_F80,
				&Plane_Type_P51,
				&Plane_Type_P82,
				&Plane_Type_B26,		//B26
				&Plane_Type_B29,
				&Plane_Type_T6,		//Mozzie
				&Plane_Type_F4U,		//Corsair
				&Plane_Type_MIG15,
				&Plane_Type_MIG15BIS,
				&Plane_Type_YAK9,									  //rdh 23/04/99
				&ATruck,
				&ATank
			};
