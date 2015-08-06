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
//Filename       keyfly.cpp
//System         
//Author         R. Hyde && A. McRae from Jan 97
//Date           Mon 30 Oct 1995
//Description    
//------------------------------------------------------------------------------
#define F_GRAFIX												//DAW 05Aug96
#define F_COMMON
#define F_BATTLE
#include	"dosdefs.h"
#include	"worldinc.h"
#include	"planetyp.h"
#include	"flymodel.h"
#include	"keytest.h"
#include	"mymath.h"											//RDH 30Nov95
#include	"analogue.h"										//RDH 17Apr96
#include	"missman2.h"											//RDH 17Jul96
#include	"miles.h"											//RDH 17Jul96
#include	"ranges.h"											//RDH 17Jul96
#include	"winmove.h"											//ARM 29Nov96
#include	"modvec.h"											//ARM 05Feb97
#include	"model.h"											//ARM 05Feb97
#include	"savegame.h"
#include	"replay.h"
#include	"overlay.h"

extern DPlay _DPlay;
//DeadCode JIM 29Oct96 #pragma	dump_object_model	AirStruc

//DeadCode JIM 29Oct96 #pragma	dump_object_model PolyPitAnimData

//	1	devices not coded
//
//
//
//
//
//
//
//
//
	enum	{													//JIM 03Apr96
		 	MAXKEY_COUNT 	=	1,//4,	//CSB 29/01/99
		 	MINSENSITIVITY	=	1,//0,	//CSB 29/01/99
		 	MAXSENSITIVITY	=	4,//3,	//CSB 29/01/99
//DeadCode RDH 19Dec95 ULong const 	MAXRUDDER 		=	64;							//RDH 19Dec95
		 	RUDDER_STEP 		=	5 * RUDDERFACTOR,
		 	NEGATIVE		=	0,
		 	ABRPM	=	2000,
		 	MINRPM	=	1000,
			};

SLong	const BIGTHRUSTSTEP =10;
SLong	const SMALLTHRUSTSTEP =1;
//DeadCode CSB 29/01/99	struct	flightkey_sensitivity
//DeadCode CSB 29/01/99	{
//DeadCode CSB 29/01/99		SWord	keypress [MAXKEY_COUNT];
//DeadCode CSB 29/01/99	};
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99	//CSB - PAUL - Change these values to affect keyboard control sensitivity
//DeadCode CSB 29/01/99	//#define TEMPSENS {15000, 15000, 15000, 15000}//{3580,7160,14320,28640}				//ARM 15Apr97
//DeadCode CSB 29/01/99	//DeadCode CSB 07/01/99	#define TEMPSENS {968, 1936, 3872, 7744}//{3580,7160,14320,28640}				//ARM 15Apr97
//DeadCode CSB 29/01/99	#define TEMPSENS {8192, 16384, 24576, 32767}
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99	flightkey_sensitivity
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99		// RUDDER													//ARM 25Feb97
//DeadCode CSB 29/01/99		ruddersens	=	TEMPSENS,
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99		// ELEVATOR_BACK											//ARM 25Feb97
//DeadCode CSB 29/01/99	//TempCode ARM 07Apr97 	elevsens	=	{20*ELEVATORFACTOR,30*ELEVATORFACTOR,35*ELEVATORFACTOR,40*ELEVATORFACTOR},
//DeadCode CSB 29/01/99		elevsens	=	TEMPSENS,
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99		// ELEVATOR_FWD												//ARM 25Feb97
//DeadCode CSB 29/01/99	//TempCode ARM 07Apr97 	elevsensf	=	{20*ELEVATORFACTOR,30*ELEVATORFACTOR,40*ELEVATORFACTOR,48*ELEVATORFACTOR},
//DeadCode CSB 29/01/99		elevsensf	=	TEMPSENS,
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99		// AILERON													//ARM 25Feb97
//DeadCode CSB 29/01/99	//TempCode ARM 07Apr97 	rollsens	=	{4*AILERONFACTOR,4*AILERONFACTOR,24*AILERONFACTOR,30*AILERONFACTOR},
//DeadCode CSB 29/01/99		rollsens	=	TEMPSENS,
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99		// ELEVATOR CURVES FOR DIFFERENT SENSITIVITIES				//ARM 25Feb97
//DeadCode CSB 29/01/99		elevsrc [5] =	{	{15*ELEVATORFACTOR,20*ELEVATORFACTOR,25*ELEVATORFACTOR,30*ELEVATORFACTOR},
//DeadCode CSB 29/01/99					  		{15*ELEVATORFACTOR,20*ELEVATORFACTOR,30*ELEVATORFACTOR,38*ELEVATORFACTOR},
//DeadCode CSB 29/01/99							{20*ELEVATORFACTOR,30*ELEVATORFACTOR,35*ELEVATORFACTOR,40*ELEVATORFACTOR},
//DeadCode CSB 29/01/99							{20*ELEVATORFACTOR,30*ELEVATORFACTOR,40*ELEVATORFACTOR,48*ELEVATORFACTOR},					//RDH 15Dec95
//DeadCode CSB 29/01/99	//allow forward action to be one greater in sensitivity			//RDH 01Oct96
//DeadCode CSB 29/01/99							{20*ELEVATORFACTOR,30*ELEVATORFACTOR,40*ELEVATORFACTOR,48*ELEVATORFACTOR}	//RDH 01Oct96
//DeadCode CSB 29/01/99						},
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99		// RUDDER CURVES FOR DIFFERENT SENSITIVITIES				//ARM 25Feb97
//DeadCode CSB 29/01/99		rollsrc [4] = 	{	{10*AILERONFACTOR,20*AILERONFACTOR,20*AILERONFACTOR,20*AILERONFACTOR},//RDH 04Dec96
//DeadCode CSB 29/01/99							{10*AILERONFACTOR,20*AILERONFACTOR,20*AILERONFACTOR,25*AILERONFACTOR},//RDH 04Dec96
//DeadCode CSB 29/01/99							{10*AILERONFACTOR,20*AILERONFACTOR,24*AILERONFACTOR,30*AILERONFACTOR},//RDH 04Dec96
//DeadCode CSB 29/01/99							{10*AILERONFACTOR,20*AILERONFACTOR,24*AILERONFACTOR,MAXAILERON}//RDH 04Dec96
//DeadCode CSB 29/01/99						};




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetKeyCommon
//Author		R. Hyde 
//Date			Tue 31 Oct 1995
//
//Description	f
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::GetKeyCommon(AirStrucPtr const ControlledAC)
{
	PMODEL pModel = ControlledAC->fly.pModel;
//DeadCode CSB 28/06/99		flight_ctl* Fly = &ControlledAC->fly;
//DeadCode CSB 28/06/99		SLong OldEle = Fly->elevator;
//DeadCode CSB 28/06/99		SLong OldAil = Fly->aileron;
//DeadCode CSB 28/06/99		SLong OldRud = Fly->rudder;
//DeadCode CSB 28/06/99		SLong OldThr = Fly->thrustpercent;

	GetStickKeys (ControlledAC2);							//RDH 04Mar96

//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */	static FILE* file = NULL;
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */	static Bool record = TRUE;
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */	if(pModel->FrameCount == 0) 
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */		record = TRUE;
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */	if(record)
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */	{
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */		if(pModel->FrameCount == 0) 
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */			file = fopen ("Joystic1.txt", "wt");
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */	
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */		fprintf (file, "Time %.2f Ail_0 %.0f Ail_1 %.0f Ail_2 %.0f Ele_0 %.0f Ele_1 %.0f Ele_2 %.0f Rud_0 %.0f \n",
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */					(FP)pModel->FrameCount / 50.0, (FP)Fly->aileron,  (FP)OldAil, (FP)pModel->Aileron, 
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */												   (FP)Fly->elevator, (FP)OldEle, (FP)pModel->Elevator, (FP)Fly->rudder);
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */		if(pModel->FrameCount == 6000)
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */		{
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */			fclose (file);
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */			record = FALSE;
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */			PrintString(10, 22, "**** STOPPED ****");
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */		}
//DeadCode CSB 10/06/99	/* TEST CODE CSB 10/06/99 */	}
//DeadCode CSB 14/06/99		const SWord fSmooth = 8;
//DeadCode CSB 14/06/99		Fly->elevator		= ((fSmooth - 1) * OldEle + Fly->elevator) / fSmooth;
//DeadCode CSB 14/06/99		Fly->aileron		= ((fSmooth - 1) * OldAil + Fly->aileron ) / fSmooth;
//DeadCode CSB 14/06/99		Fly->rudder			= ((fSmooth - 1) * OldRud + Fly->rudder  ) / fSmooth;

//Set control values in Model including Central deadzone and end clipping

	SWord EleDeadZone = _Analogue.deadzones[AU_ELEVATOR];
	SWord AilDeadZone = _Analogue.deadzones[AU_AILERON];
	SWord RudDeadZone = _Analogue.deadzones[AU_RUDDER];

	pModel->Elevator -= pModel->ElevatorTrim;

//#define PRINT_INPUT_DATA
#ifdef PRINT_INPUT_DATA
PrintVar(40, 15, "Raw Elev %.0f  ", (FP)ControlledAC->fly.elevator);
PrintVar(40, 16, "Raw Ailn %.0f  ", (FP)ControlledAC->fly.aileron);
PrintVar(40, 17, "Raw Rudd %.0f  ", (FP)ControlledAC->fly.rudder);
#endif


//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	FP Val0 = 0;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	FP Val1 = 0;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	Val0 = ControlledAC->fly.elevator;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	{
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		FP Val0s, Val0a;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		if(Val0 >= 0)	{Val0a =  Val0;	Val0s =  1;}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		else			{Val0a = -Val0;	Val0s = -1;}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		FP Val2 = Val0a / 2;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		if(Val0a > 21845)
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		{
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			FP frac = (Val0a - 21845) / 10923;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			frac = frac * frac;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			Val1 = (1 - frac) * Val2 + frac * Val0a;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		else
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			Val1 = Val2;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		Val1 *= Val0s;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	pModel->Elevator = Val1;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	Val0 = ControlledAC->fly.aileron;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	{
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		FP Val0s, Val0a;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		if(Val0 >= 0)	{Val0a =  Val0;	Val0s =  1;}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		else			{Val0a = -Val0;	Val0s = -1;}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		FP Val2 = Val0a / 2;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		if(Val0a > 21845)
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		{
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			FP frac = (Val0a - 21845) / 10923;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			frac = frac * frac;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			Val1 = (1 - frac) * Val2 + frac * Val0a;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		else
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			Val1 = Val2;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		Val1 *= Val0s;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	pModel->Aileron = Val1;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	Val0 = ControlledAC->fly.rudder;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	{
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		FP Val0s, Val0a;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		if(Val0 >= 0)	{Val0a =  Val0;	Val0s =  1;}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		else			{Val0a = -Val0;	Val0s = -1;}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		FP Val2 = Val0a / 2;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		if(Val0a > 21845)
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		{
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			FP frac = (Val0a - 21845) / 10923;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			frac = frac * frac;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			Val1 = (1 - frac) * Val2 + frac * Val0a;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		else
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */			Val1 = Val2;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */		Val1 *= Val0s;
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	}
//DeadCode CSB 20/05/99	/* TEST CODE CSB 19/05/99 */	pModel->Rudder = Val1;


//DeadCode CSB 06/04/99		ApplyDeadZone(ControlledAC, ControlledAC->fly.elevator, pModel->Elevator, EleDeadZone);
//DeadCode CSB 06/04/99		ApplyDeadZone(ControlledAC, ControlledAC->fly.aileron , pModel->Aileron , AilDeadZone);
//DeadCode CSB 06/04/99		ApplyDeadZone(ControlledAC, ControlledAC->fly.rudder  , pModel->Rudder  , RudDeadZone);
	
//DeadCode CSB 19/05/99		ApplyDeadZone2(ControlledAC, ControlledAC->fly.elevator, pModel->Elevator, EleDeadZone);
//DeadCode CSB 19/05/99		ApplyDeadZone2(ControlledAC, ControlledAC->fly.aileron , pModel->Aileron , AilDeadZone);
//DeadCode CSB 19/05/99		ApplyDeadZone2(ControlledAC, ControlledAC->fly.rudder  , pModel->Rudder  , RudDeadZone);
	
	ApplyDeadZone3(ControlledAC, ControlledAC->fly.elevator, pModel->Elevator, EleDeadZone);
	ApplyDeadZone3(ControlledAC, ControlledAC->fly.aileron , pModel->Aileron , AilDeadZone);
	ApplyDeadZone3(ControlledAC, ControlledAC->fly.rudder  , pModel->Rudder  , RudDeadZone);

	MODLIMIT(pModel->Elevator, 32767);
	MODLIMIT(pModel->Aileron,  32767);
	MODLIMIT(pModel->Rudder,   32767);

#ifdef PRINT_INPUT_DATA
PrintVar(60, 15, "Mod Elev %.0f  ", (FP)pModel->Elevator);
PrintVar(60, 16, "Mod Ailn %.0f  ", (FP)pModel->Aileron);
PrintVar(60, 17, "Mod Rudd %.0f  ", (FP)pModel->Rudder);
#endif
	

	SecondaryControls (ControlledAC2);

	// Elevator Trim

	//Automatic trim
//DeadCode CSB 09/07/99		if( (0==1) )	//fix this !!!!
//DeadCode CSB 09/07/99		{
//DeadCode CSB 09/07/99			bool ElevKeys = FALSE;
//DeadCode CSB 09/07/99			if( (Key_Tests.KeyHeld3d (ELEVATOR_BACK)) || 
//DeadCode CSB 09/07/99				(Key_Tests.KeyHeld3d (ELEVATOR_FORWARD)) ) ElevKeys = TRUE;
//DeadCode CSB 09/07/99	
//DeadCode CSB 09/07/99	
//DeadCode CSB 09/07/99			FP DeltaTrim = (FP)(pModel->Elevator * pModel->MODEL_DT);
//DeadCode CSB 09/07/99			if(ElevKeys)
//DeadCode CSB 09/07/99			{
//DeadCode CSB 09/07/99				DeltaTrim *= 0.05;
//DeadCode CSB 09/07/99	//DeadCode CSB 02/12/98				MODLIMIT(DeltaTrim, 100 * pModel->MODEL_DT);
//DeadCode CSB 09/07/99				pModel->ElevatorTrim += (SWord)DeltaTrim;
//DeadCode CSB 09/07/99			}
//DeadCode CSB 09/07/99			else
//DeadCode CSB 09/07/99			{
//DeadCode CSB 09/07/99				DeltaTrim *= 0.001;
//DeadCode CSB 09/07/99				MODLIMIT(DeltaTrim, 4 * pModel->MODEL_DT);
//DeadCode CSB 09/07/99				pModel->ElevatorTrim += (SWord)DeltaTrim;
//DeadCode CSB 09/07/99			}
//DeadCode CSB 09/07/99			MODLIMIT(pModel->ElevatorTrim, 16384);
//DeadCode CSB 09/07/99		}

	SLong TempElevator = (SLong)pModel->Elevator + (SLong)pModel->ElevatorTrim;
	MODLIMIT (TempElevator, 32767);
	pModel->Elevator = (SWord)TempElevator;



	MODLIMIT (pModel->Elevator, 32767);
	MODLIMIT (pModel->Aileron , 32767);
	MODLIMIT (pModel->Rudder  , 32767);


//done via radio comms	
//DEADCODE RDH 24/03/99 	if (Key_Tests.KeyPress3d (GOHOME))
//DEADCODE RDH 24/03/99 		ControlledAC2->SendEveryOneHome ();
//DEADCODE RDH 24/03/99 
//DEADCODE RDH 24/03/99 	if (Key_Tests.KeyPress3d (REFORMATION))
//DEADCODE RDH 24/03/99 	{
//DEADCODE RDH 24/03/99 		ControlledAC2->LeaderBreakOff ();
//DEADCODE RDH 24/03/99 //TEMP	 	Persons_2.AddMessage(UserMsg::TIME,TEXT_ATTEMPTINGTOREGROUP,NULL);//RDH 03Dec96
//DEADCODE RDH 24/03/99 	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyDeadZone
//Author		Craig Beeston
//Date			Wed 16 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::ApplyDeadZone(AirStrucPtr const ControlledAC, SWord SrcVal, int& DstVal, SWord DeadZone)
{
//DeadCode AMM 29Jun99 	FP MidZone_EndZone = 2;	//Deadzone at extremes is twice as wide as central deadzone on one side of centre
//DeadCode AMM 29Jun99 	SWord TopLimit = 32767 - MidZone_EndZone*DeadZone;
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 	SWord OldVal = DstVal;
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 	SLong TempVal = SrcVal;
//DeadCode AMM 29Jun99 	SWord SignVal = 1;
//DeadCode AMM 29Jun99 	if(TempVal < 0) 
//DeadCode AMM 29Jun99 	{
//DeadCode AMM 29Jun99 		SignVal =  -1;
//DeadCode AMM 29Jun99 		TempVal *= -1;
//DeadCode AMM 29Jun99 	}
//DeadCode AMM 29Jun99 	
//DeadCode AMM 29Jun99 	for(;;)		//See  "\CSB\DeadZone.xls"
//DeadCode AMM 29Jun99 	{
//DeadCode AMM 29Jun99 		if(TempVal <= DeadZone)	//Inside DeadZone
//DeadCode AMM 29Jun99 		{
//DeadCode AMM 29Jun99 			TempVal = 0;
//DeadCode AMM 29Jun99 			break;
//DeadCode AMM 29Jun99 		}
//DeadCode AMM 29Jun99 		
//DeadCode AMM 29Jun99 		if(TempVal >= TopLimit ) //Clip top and bottom of range
//DeadCode AMM 29Jun99 		{
//DeadCode AMM 29Jun99 			TempVal = 32767;
//DeadCode AMM 29Jun99 			break;
//DeadCode AMM 29Jun99 		}
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 		if( (TempVal > 2*DeadZone) && (TempVal <= TopLimit) )	//Main Linear Bit
//DeadCode AMM 29Jun99 		{
//DeadCode AMM 29Jun99 			FP MinVal = 1.5 * DeadZone;
//DeadCode AMM 29Jun99 			FP MaxVal = TopLimit;
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 			TempVal = (int)(32767 * ( (float)TempVal - MinVal) / (MaxVal - MinVal) );
//DeadCode AMM 29Jun99 			break;
//DeadCode AMM 29Jun99 		}
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 		if( (TempVal > DeadZone) && (TempVal < 2*DeadZone) )	//Curve between deadzone and linear region
//DeadCode AMM 29Jun99 		{
//DeadCode AMM 29Jun99 			FP MinVal = 1.5 * DeadZone;		//Where linear region hits zero
//DeadCode AMM 29Jun99 			FP MaxVal = TopLimit;	//Top of linear region
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 			FP Val1 = (int)(32767 * (2 * (float)DeadZone - MinVal) / (MaxVal - MinVal) );	//Value where curve meets line
//DeadCode AMM 29Jun99 			MinVal = DeadZone;		//Start of curve
//DeadCode AMM 29Jun99 			MaxVal = 2 * DeadZone;	//End of curve
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 			FP Fraction = ( (float)TempVal - MinVal) / (MaxVal - MinVal);
//DeadCode AMM 29Jun99 			TempVal = (int)(Val1 * Fraction * Fraction);
//DeadCode AMM 29Jun99 			break;
//DeadCode AMM 29Jun99 		}
//DeadCode AMM 29Jun99 		break;	//To stop it getting locked in this loop - Should never get this far!!
//DeadCode AMM 29Jun99 	}
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 	TempVal *= SignVal;
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		PMODEL pModel = ControlledAC->fly.pModel;
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		FP MaxDif = 32767 * 0.01 * pModel->MODEL_DT / pModel->MaxDefTime;
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98	
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		SLong Dif = TempVal - OldVal;
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		SWord SignDif = 1;
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		if(Dif < 0) 
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		{
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98			SignDif = -1;
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98			Dif    *= -1;
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		}
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98	
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		if(Dif > MaxDif)
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		{
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98			if(SignDif == 1) TempVal = OldVal + (int)MaxDif;
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98			else			 TempVal = OldVal - (int)MaxDif;
//DeadCode AMM 29Jun99 //DeadCode CSB 23/12/98		}
//DeadCode AMM 29Jun99 	
//DeadCode AMM 29Jun99 	PMODEL pModel = ControlledAC->fly.pModel;
//DeadCode AMM 29Jun99 	
//DeadCode AMM 29Jun99 	FP Rate =  ( (float)TempVal - (float)OldVal ) * pModel->ControlPower;
//DeadCode AMM 29Jun99 	Rate    -= (float)OldVal * pModel->ControlResistance * pModel->AmbDensity * pModel->Inst.MachNo * pModel->Inst.MachNo;
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 	TempVal = OldVal + (int)(Rate * pModel->MODEL_DT);
//DeadCode AMM 29Jun99 
//DeadCode AMM 29Jun99 	MODLIMIT(TempVal, 32767);
//DeadCode AMM 29Jun99 	DstVal = TempVal;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyDeadZone2
//Author		Craig Beeston
//Date			Tue 6 Apr 1999
//
//Description	Just Like the one above but to give extra control using a digital stick
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::ApplyDeadZone2(AirStrucPtr const ControlledAC, SWord SrcVal, int& DstVal, SWord DeadZone)
{
	UWord DeadRegion  = DeadZone;
	UWord LinearStart = 3 * DeadZone;
	UWord CurveEnd    = 5 * DeadZone;
	UWord MaxVal	  = 32767 - DeadZone; 

	SWord SrcSign = 1;
	if(SrcVal < 0) SrcSign = -1;

	SWord SrcAbs = SrcVal * SrcSign;	//Gives positive value
	if(SrcAbs < DeadRegion) 
	{
		DstVal = 0;
		return;
	}
	if(SrcAbs > CurveEnd)
	{
		DstVal =  32768 * (SrcAbs - LinearStart) / (MaxVal - LinearStart);
		DstVal *= SrcSign;
		MODLIMIT(DstVal, 32767);
		return;
	}
	FP TempVal = ((FP)SrcAbs - (FP)DeadRegion) / ((FP)CurveEnd - (FP)DeadRegion);
	TempVal = TempVal * TempVal;
	TempVal = TempVal * 32768.0 * ((FP)CurveEnd - (FP)LinearStart) / ((FP)MaxVal - (FP)LinearStart);
	DstVal = TempVal * SrcSign;
	MODLIMIT(DstVal, 32767);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyDeadZone3
//Author		Craig Beeston
//Date			Wed 19 May 1999
//
//Description	Central deadzone, Then linear for bottom 2/3 giving 1/3 output, then steep curve towards limits
//				See "Craig\\C:\CSB\Joystick_Filter.xls"
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::ApplyDeadZone3(AirStrucPtr const ControlledAC, SWord SrcVal, int& DstVal, SWord DeadZone)
{
	UWord StartCurve1 = DeadZone;
	UWord StartLinear = 5 * DeadZone;
	UWord LinearBase  = 3 * DeadZone;
	UWord StartCurve2 = 21845;	//	2/3 * 32768
	UWord EndCurve2	  = 32767 - DeadZone; 

	SWord SrcSign, SrcAbs;
	if(SrcVal >= 0)	{SrcAbs =  SrcVal;	SrcSign =  1;}
	else			{SrcAbs = -SrcVal;	SrcSign = -1;}

	if(SrcAbs < StartCurve1)	//Centre Dead Region
	{
		DstVal = 0;
		return;
	}

	if(SrcAbs >= EndCurve2)		//Top End Dead Region
	{	
		DstVal = 32767 * SrcSign;
		return;
	}

	if(SrcAbs > StartLinear)	//Linear Section
	{
		DstVal = (32767 / 2 * (SrcAbs - LinearBase)) / (EndCurve2 - LinearBase);
		if(SrcAbs <= StartCurve2)
		{
			DstVal *= SrcSign;
			return;
		}
		else					//Steep curve
		{
			FP temp = ((FP)SrcAbs - (FP)StartCurve2) / ((FP)EndCurve2 - (FP)StartCurve2);
			temp = temp * temp;
			temp = (FP)DstVal * (1 - temp) + 32767.0 * temp;
			DstVal = temp * SrcSign;
			return;
		}
	}

	FP temp = ((FP)SrcAbs - (FP)StartCurve1) / ((FP)StartLinear - (FP)StartCurve1);
	DstVal = (32767 / 2 * (StartLinear - LinearBase)) / (EndCurve2 - LinearBase);
	DstVal = temp * temp * (FP)DstVal * (FP)SrcSign;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRPMABKeys
//Author		R. Hyde 
//Date			Tue 31 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::GetRPMABKeys(AirStrucPtr const ControlledAC)

{

// Called from GetStickKeys, at end						//ARM 11Apr97

//rdh needed to know whether on internal or external here
 	if	(ControlledAC->weap.centre.int_fuel >0)
 	{
//DeadCode CSB 13/01/99	 		if (Key_Tests.KeyPress3d (RPM_MIL))
//DeadCode CSB 13/01/99	 		{
//DeadCode CSB 13/01/99	 			ControlledAC->fly.afterburner = 0;
//DeadCode CSB 13/01/99	 			ControlledAC->fly.thrustpercent = 100;
//DeadCode CSB 13/01/99	 		}
 
//DeadCode CSB 13/01/99	 		if (Key_Tests.KeyPress3d (RPM_MIN))
//DeadCode CSB 13/01/99	 		{
//DeadCode CSB 13/01/99	 			ControlledAC->fly.afterburner = 0;
//DeadCode CSB 13/01/99	 			ControlledAC->fly.thrustpercent = 0;
//DeadCode CSB 13/01/99	 		}

		if (Key_Tests.KeyPress3d (RPM_BIG_UP))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent += BIGTHRUSTSTEP;
 			if (ControlledAC->fly.thrustpercent >100)
 			{
 				ControlledAC->fly.thrustpercent = 100;
 			}
 		}

		if (Key_Tests.KeyPress3d (RPM_BIG_DOWN))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent -= BIGTHRUSTSTEP;
 			if (ControlledAC->fly.thrustpercent <0)
 			{
 				ControlledAC->fly.thrustpercent = 0;
 			}
 		}
 
 		if (Key_Tests.KeyPress3d (RPM_UP))
 		{
 			{
 				ControlledAC->fly.afterburner = 0;
 				ControlledAC->fly.thrustpercent += SMALLTHRUSTSTEP;
 			if (ControlledAC->fly.thrustpercent >100)
 			{
 				ControlledAC->fly.thrustpercent = 100;
 			}
 			}
 		}
 		if (Key_Tests.KeyPress3d (RPM_DOWN))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent -= SMALLTHRUSTSTEP;
 			if (ControlledAC->fly.thrustpercent <0)
 			{
 				ControlledAC->fly.thrustpercent = 0;
 			}
 		}
 		if (ControlledAC->fly.thrustpercent <0)
 		{
 			ControlledAC->fly.thrustpercent = 0;
 		}

		if (!OverLay.pCurScr)
		{
		if (Key_Tests.KeyPress3d (RPM_OFF))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent = 0;
	 	}
		if (Key_Tests.KeyPress3d (RPM_10))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent = 10;
	 	}
		if (Key_Tests.KeyPress3d (RPM_20))
 		{
 			ControlledAC->fly.afterburner = 0;
	 		ControlledAC->fly.thrustpercent = 20;
 		}
 
		if (Key_Tests.KeyPress3d (RPM_30))
	 	{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent = 30;
	 	}
 
		if (Key_Tests.KeyPress3d (RPM_40))
 		{
 			ControlledAC->fly.afterburner = 0;
	 		ControlledAC->fly.thrustpercent = 40;
 		}
 
		if (Key_Tests.KeyPress3d (RPM_50))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent = 50;
 		}
 
		if (Key_Tests.KeyPress3d (RPM_60))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent = 60;
 		}
 
		if (Key_Tests.KeyPress3d (RPM_70))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent = 70;
 		}
 
		if (Key_Tests.KeyPress3d (RPM_80))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent = 80;
 		}
		if (Key_Tests.KeyPress3d (RPM_90))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent = 90;
 		}
 
		if (Key_Tests.KeyPress3d (RPM_00))
 		{
 			ControlledAC->fly.afterburner = 0;
 			ControlledAC->fly.thrustpercent = 100;
 		}
		}
 
 
 
 	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindMaxRPM
//Author		R. Hyde 
//Date			Tue 31 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void ManualPilot::FindMaxRPM(AirStrucPtr const ControlledAC)
//
//{
//		if (ControlledAC->fly.rpm >MAXRPM)
//		/{
//			ControlledAC->fly.rpm = MAXRPM;
//		}
//
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SensitivityMsg
//Author		R. Hyde 
//Date			Tue 3 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::SensitivityMsg(AirStrucPtr const ControlledAC)
{
		switch (Save_Data.keysensitivity)
		{
			case	0:
			{
//TEMP			 	Persons_2.AddMessage(UserMsg::TIME,TEXT_SENSITIVITY0,NULL);//RDH 03Dec96
				break;
			}
			case	1:
			{
//TEMP			 	Persons_2.AddMessage(UserMsg::TIME,TEXT_SENSITIVITY1,NULL);//RDH 03Dec96
				break;
			}
			case	2:
			{
//TEMP			 	Persons_2.AddMessage(UserMsg::TIME,TEXT_SENSITIVITY2,NULL);//RDH 03Dec96
				break;
			}
			case	3:
			{
//TEMP			 	Persons_2.AddMessage(UserMsg::TIME,TEXT_SENSITIVITY3,NULL);//RDH 03Dec96
				break;
			}
		}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetStickKeys
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
void	ManualPilot::GetStickKeys (AirStrucPtr const ControlledAC)

{
//	UWord	rudder_pos;
//	SWord	rudder_sign,cntstick_rudder;

//	if (_DPlay.PermitKeys())									//ARM 29Nov96
	{
		if (Key_Tests.KeyPress3d (CHEATLIFTKEY))					//RDH 21Jul96
		{															//RDH 21Jul96
			if (!_DPlay.Implemented || (_DPlay.Implemented && _DPlay.liftcheat))
			{
				if (ControlledAC->World.Y <(FT_60000-FT_10000))			//DAW 12May99
					if (ControlledAC->fly.pModel->Controlled)			//ARM 15May97
					{
						ControlledAC->fly.pModel->ResetDeltaPos (ControlledAC,0,FT_1000,0);//DAW 15Jun98

	// this gets done in delta application
	//DeadCode AMM 25Mar99 					Persons2::PlayerGhostAC->World.Y+=FT_1000;

	//DeadCode AMM 25Mar99 					if (_DPlay.Implemented || _Replay.Record)
						if (!_Replay.Playback)
						{
							_DPlay.Deltas.lastpos.Y+=FT_1000;
						}
	//					_DPlay.NewCollision (ControlledAC, NULL, PIDC_ACTION,ACTION_CHEAT);//DAW 15Jun98
					}
			}
		}															//RDH 21Jul96
	}

 	if (Key_Tests.KeyPress3d (RPMTOGGLE))
 		if(ControlledAC->fly.pModel->DesiredRPM == 1800)
			ControlledAC->fly.pModel->DesiredRPM = 3000;
		else 
			ControlledAC->fly.pModel->DesiredRPM = 1800;
	
	if (Key_Tests.KeyPress3d (RESTARTENGINE))	//CSB 25/11/98
		if(ControlledAC->weap.centre.int_fuel > 0)
			ControlledAC->fly.pModel->RestartEngine = TRUE;

	if (Key_Tests.KeyPress3d (SENS_UP))
	{
		if (Save_Data.keysensitivity < MAXSENSITIVITY)
		{
			_Miles.PlaySample (FIL_SFX_GUN_RELOADING4,5120);	//RJS 24Jul96
			Save_Data.keysensitivity++;
//DeadCode CSB 29/01/99				elevsens = elevsrc [sensitivity];
//DeadCode CSB 29/01/99				elevsensf = elevsrc [sensitivity+1];
//DeadCode CSB 29/01/99				rollsens = rollsrc [sensitivity];
			SensitivityMsg(ControlledAC);										//RDH 03Dec96

		}else
		{
			_Miles.PlaySample (FIL_SFX_GUN_CLICK1,5120);			//RJS 24Jul96

		}
		OverLay.TriggerMessage(COverlay::SENSMESS,Save_Data.keysensitivity);
	}
	if (Key_Tests.KeyPress3d (SENS_DOWN))
	{
		if (Save_Data.keysensitivity > MINSENSITIVITY)
		{
			_Miles.PlaySample (FIL_SFX_GUN_RELOADING4,5120);	//RJS 24Jul96
			Save_Data.keysensitivity--;
//DeadCode CSB 29/01/99				elevsens = elevsrc [sensitivity];
//DeadCode CSB 29/01/99				elevsensf = elevsrc [sensitivity+1];
//DeadCode CSB 29/01/99				rollsens = rollsrc [sensitivity];
			SensitivityMsg(ControlledAC);										//RDH 03Dec96
		}else
		{
			_Miles.PlaySample (FIL_SFX_GUN_CLICK1,5120);			//RJS 24Jul96

		}
		OverLay.TriggerMessage(COverlay::SENSMESS,Save_Data.keysensitivity);
	}
//**	if (analog joy)
//**	{
//**	}else
//**	{
//DeadCode CSB 29/01/99			FP fDelta = 32767 * sensitivity / MAXSENSITIVITY * ControlledAC->fly.pModel->MODEL_DT / 100;
//DeadCode CSB 29/01/99			SWord Delta = (int)fDelta;
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99			if (Key_Tests.KeyHeld3d (ELEVATOR_BACK))
//DeadCode CSB 29/01/99			{
//DeadCode CSB 29/01/99				if (cntstick_b <(MAXKEY_COUNT - 1))
//DeadCode CSB 29/01/99				{
//DeadCode CSB 29/01/99					cntstick_b++;
//DeadCode CSB 29/01/99				}
//DeadCode CSB 29/01/99	//DeadCode CSB 29/01/99				ControlledAC->fly.elevator = (SWord) -elevsens.keypress[cntstick_b];
//DeadCode CSB 29/01/99				if(ControlledAC->fly.elevator > -32767 + Delta)
//DeadCode CSB 29/01/99					ControlledAC->fly.elevator -= Delta;	//CSB 29/01/99
//DeadCode CSB 29/01/99			}else
//DeadCode CSB 29/01/99			{
//DeadCode CSB 29/01/99	//DeadCode CSB 29/01/99				cntstick_b =0;
//DeadCode CSB 29/01/99				if (Key_Tests.KeyHeld3d (ELEVATOR_FORWARD))
//DeadCode CSB 29/01/99				{
//DeadCode CSB 29/01/99					if (cntstick_f <(MAXKEY_COUNT - 1))
//DeadCode CSB 29/01/99					{
//DeadCode CSB 29/01/99						cntstick_f++;
//DeadCode CSB 29/01/99					}
//DeadCode CSB 29/01/99	//DeadCode CSB 29/01/99						ControlledAC->fly.elevator = elevsensf.keypress[cntstick_f];
//DeadCode CSB 29/01/99				if(ControlledAC->fly.elevator < 32767 - Delta)
//DeadCode CSB 29/01/99					ControlledAC->fly.elevator += Delta;	//CSB 29/01/99
//DeadCode CSB 29/01/99				}elseif( (cntstick_b != 0) || (cntstick_f != 0) )	//No key pressed but still effects of previous key press
//DeadCode CSB 29/01/99				{
//DeadCode CSB 29/01/99	//DeadCode CSB 29/01/99					cntstick_f =0;
//DeadCode CSB 29/01/99	//DeadCode CSB 29/01/99					ControlledAC->fly.elevator = 0;
//DeadCode CSB 29/01/99					if( (ControlledAC->fly.elevator >= -Delta) && (ControlledAC->fly.elevator <= Delta) )
//DeadCode CSB 29/01/99					{
//DeadCode CSB 29/01/99						ControlledAC->fly.elevator = 0;
//DeadCode CSB 29/01/99						cntstick_f = 0;
//DeadCode CSB 29/01/99						cntstick_b = 0;
//DeadCode CSB 29/01/99					}
//DeadCode CSB 29/01/99					elseif (ControlledAC->fly.elevator < -Delta) 
//DeadCode CSB 29/01/99						ControlledAC->fly.elevator += Delta;
//DeadCode CSB 29/01/99	
//DeadCode CSB 29/01/99					elseif(ControlledAC->fly.elevator > Delta)
//DeadCode CSB 29/01/99						ControlledAC->fly.elevator -= Delta; 
//DeadCode CSB 29/01/99				}
//DeadCode CSB 29/01/99			}
//DeadCode CSB 29/01/99			MODLIMIT(ControlledAC->fly.elevator, 32767 * (sensitivity + 1) / (MAXSENSITIVITY + 1) );

		FP fDelta = 32767 * Save_Data.keysensitivity / MAXSENSITIVITY * ControlledAC->fly.pModel->MODEL_DT / 100;
		SWord Delta1 = (int)fDelta;
		SWord Delta2 = (int)(2 * fDelta);
		UWord LimitVal = 32767 * Save_Data.keysensitivity / MAXSENSITIVITY;
		Bool KeyPressed = FALSE;

		if (Key_Tests.KeyHeld3d (ELEVATOR_BACK))
		{
			cntstick_b = 1;
			if(ControlledAC->fly.elevator > 0)
				ControlledAC->fly.elevator = 0;
			if(ControlledAC->fly.elevator > -32767 + Delta1)
				ControlledAC->fly.elevator -= Delta1;	//CSB 29/01/99
			KeyPressed = TRUE;
		}
		else
		{
			if (Key_Tests.KeyHeld3d (ELEVATOR_FORWARD))
			{
				cntstick_f = 1;
				if(ControlledAC->fly.elevator < 0)
					ControlledAC->fly.elevator = 0;
				if(ControlledAC->fly.elevator < 32767 - Delta1)
					ControlledAC->fly.elevator += Delta1;	//CSB 29/01/99
				KeyPressed = TRUE;
			}
			elseif( (cntstick_b != 0) || (cntstick_f != 0) )	//No key pressed but still effects of previous key press
			{
				if( (ControlledAC->fly.elevator >= -Delta1) && (ControlledAC->fly.elevator <= Delta1) )
				{
					ControlledAC->fly.elevator = 0;
					cntstick_f = 0;
					cntstick_b = 0;
				}
				elseif (ControlledAC->fly.elevator < -Delta1) 
					ControlledAC->fly.elevator += Delta1;

				elseif(ControlledAC->fly.elevator > Delta1)
					ControlledAC->fly.elevator -= Delta1; 
			}
		}
		if(KeyPressed)
			MODLIMIT(ControlledAC->fly.elevator, LimitVal);

//////////////////////////////////////////////
		KeyPressed = FALSE;

		if (Key_Tests.KeyHeld3d (AILERON_LEFT))
		{
			cntstick_l = 1;
			if(ControlledAC->fly.aileron > 0)
				ControlledAC->fly.aileron = 0;
			if(ControlledAC->fly.aileron > -32767 + Delta2)
				ControlledAC->fly.aileron -= Delta2;	//CSB 29/01/99
			KeyPressed = TRUE;
		}
		else
		{
			if (Key_Tests.KeyHeld3d (AILERON_RIGHT))
			{
				cntstick_r = 1;
				if(ControlledAC->fly.aileron < 0)
					ControlledAC->fly.aileron = 0;
				if(ControlledAC->fly.aileron < 32767 - Delta2)
					ControlledAC->fly.aileron += Delta2;	//CSB 29/01/99
				KeyPressed = TRUE;
			}
			elseif( (cntstick_l != 0) || (cntstick_r != 0) )	//No key pressed but still effects of previous key press
			{
				if( (ControlledAC->fly.aileron >= -Delta2) && (ControlledAC->fly.aileron <= Delta2) )
				{
					ControlledAC->fly.aileron = 0;
					cntstick_l = 0;
					cntstick_r = 0;
				}
				elseif (ControlledAC->fly.aileron < -Delta2) 
					ControlledAC->fly.aileron += Delta2;

				elseif(ControlledAC->fly.aileron > Delta2)
					ControlledAC->fly.aileron -= Delta2; 
			}
		}
		if(KeyPressed)
			MODLIMIT(ControlledAC->fly.aileron, LimitVal);

//////////////////////////////////////////////
		KeyPressed = FALSE;

		if (Key_Tests.KeyHeld3d (RUDDER_LEFT))
		{
			cntrudder_l = 1;
			if(ControlledAC->fly.rudder > 0)
				ControlledAC->fly.rudder = 0;
			if(ControlledAC->fly.rudder > -32767 + Delta2)
				ControlledAC->fly.rudder -= Delta2;	//CSB 29/01/99
			KeyPressed = TRUE;
		}
		else
		{
			if (Key_Tests.KeyHeld3d (RUDDER_RIGHT))
			{
				cntrudder_r = 1;
				if(ControlledAC->fly.rudder < 0)
					ControlledAC->fly.rudder = 0;
				if(ControlledAC->fly.rudder < 32767 - Delta2)
					ControlledAC->fly.rudder += Delta2;	//CSB 29/01/99
				KeyPressed = TRUE;
			}
			elseif( (cntrudder_l != 0) || (cntrudder_r != 0) )	//No key pressed but still effects of previous key press
			{
				if( (ControlledAC->fly.rudder >= -Delta2) && (ControlledAC->fly.rudder <= Delta2) )
				{
					ControlledAC->fly.rudder = 0;
					cntrudder_l = 0;
					cntrudder_r = 0;
				}
				elseif (ControlledAC->fly.rudder < -Delta2) 
					ControlledAC->fly.rudder += Delta2;

				elseif(ControlledAC->fly.rudder > Delta2)
					ControlledAC->fly.rudder -= Delta2; 
			}
		}
		if(KeyPressed)
			MODLIMIT(ControlledAC->fly.rudder, LimitVal);

//////////////////////////////////////////////
/*		if (Key_Tests.KeyHeld3d (AILERON_LEFT))	/*	//CSB 29/01/99
		{
			if (cntstick_l <(MAXKEY_COUNT - 1))
			{
				cntstick_l++;
			}
			ControlledAC->fly.aileron = (SWord) -rollsens.keypress[cntstick_l];
		}else
		{
			cntstick_l =0;
			if (Key_Tests.KeyHeld3d (AILERON_RIGHT))
			{
				if (cntstick_r <(MAXKEY_COUNT - 1))
				{
					cntstick_r++;
				}
				ControlledAC->fly.aileron = rollsens.keypress[cntstick_r];
			}else
			{
				cntstick_r =0;
				ControlledAC->fly.aileron = 0;
			}
		}


//make rudder like elevator and aileron
		cntstick_rudder = 1;
		if (Key_Tests.KeyHeld3d (RUDDER_LEFT))
		{
			if (cntrudder_l <(MAXKEY_COUNT - 1))
			{
				cntrudder_l++;
			}
			ControlledAC->fly.rudder = (SWord) -ruddersens.keypress[cntrudder_l];
		}else
		{
			cntrudder_l =0;
			if (Key_Tests.KeyHeld3d (RUDDER_RIGHT))
			{
				if (cntrudder_r <(MAXKEY_COUNT - 1))
				{
					cntrudder_r++;
				}
				ControlledAC->fly.rudder = ruddersens.keypress[cntrudder_r];
			}else
			{
				cntrudder_r =0;
				cntstick_rudder = 0;
				ControlledAC->fly.rudder = 0;
			}
		}
*/	//CSB 29/01/99

//joystick control

		keyboardcontrol = TRUE;
		_Analogue.PollPosition();
		SWord	ail=_Analogue.ReadPosition(AU_AILERON);
		SWord	elev=_Analogue.ReadPosition(AU_ELEVATOR);
		SWord	rudd=_Analogue.ReadPosition(AU_RUDDER);
		SWord	thro=_Analogue.ReadPosition(AU_THROTTLE);
		UWord	xy3_pos;
		SWord	xy3_sign;
		SLong	aileron,elevator,rudder;

//DeadCode CSB 12/11/98			Mono_Text.PrintHexAt(30,0,ail,4);
//DeadCode CSB 12/11/98			Mono_Text.PrintHexAt(30,1,elev,4);
//DeadCode CSB 12/11/98			Mono_Text.PrintHexAt(30,2,rudd,4);
//DeadCode CSB 12/11/98			Mono_Text.PrintHexAt(30,3,thro,4);

		flight_ctl* Fly = &ControlledAC->fly;
		SLong delta, fsmooth;

		const dEle  = 1000;		const sEle1	= 16;		const sEle2	= 4;
		const dAil  = 100;		const sAil1 = 16;		const sAil2	= 4;
		const dRud  = 1000;		const sRud1	= 16;		const sRud2	= 4;
	

		if ((ail!=-0x8000) && (cntstick_r == 0)&& (cntstick_l == 0))
		{
			keyboardcontrol = FALSE;
			aileron = MAXAILERON * ail/ 32768;
			delta = aileron - Fly->aileron;
			if((delta > -dAil) && (delta < dAil))	fsmooth = sAil1;
			else								 	fsmooth = sAil2;
			Fly->aileron = ((fsmooth - 1) * Fly->aileron + aileron) / fsmooth;
		}
		if ((elev!=-0x8000) && (cntstick_f == 0)&& (cntstick_b == 0))
		{
			keyboardcontrol = FALSE;
			elevator = - MAXELEVATOR * elev/ 32768;
			delta = elevator - Fly->elevator;
			if((delta > -dEle) && (delta < dEle))	fsmooth = sEle1;
			else								 	fsmooth = sEle2;
			Fly->elevator = ((fsmooth - 1) * Fly->elevator + elevator) / fsmooth;
		}
		if ((rudd!=-0x8000) && (cntrudder_l == 0) && (cntrudder_r == 0) )
		{
			rudder = MAXRUDDER * rudd/ 32768;
			ControlledAC->fly.rudder = (SWord) rudder;
			delta = rudder - Fly->rudder;
			if((delta > -dRud) && (delta < dRud))	fsmooth = sRud1;
			else								 	fsmooth = sRud2;
			Fly->rudder = ((fsmooth - 1) * Fly->rudder + rudder) / fsmooth;
		}

		if (thro!=-0x8000)
		{
			Math_Lib.Pos (thro,xy3_pos,xy3_sign);
			SLong TempThrust = xy3_pos;

const int DeadZone = 2048;//1024;
			if(TempThrust < 2048) TempThrust = 0;
			else if(TempThrust >= 32768 - DeadZone) TempThrust = 100;
			else TempThrust = (100 * (TempThrust - DeadZone)) / (32768 - 2 * DeadZone);

			ControlledAC->fly.thrustpercent = TempThrust;
		}else
			GetRPMABKeys(ControlledAC);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SecondaryControls
//Author		Andrew McRae
//Date			Tue 12 Aug 1997
//
//Description	Flaps, slats, gear etc.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::SecondaryControls (AirStrucPtr const ControlledAC2)
{

	PMODEL pModel = ControlledAC2->fly.pModel;
	MODEL& Mod = *ControlledAC2->fly.pModel;

	// Wheel Brakes

	if (Key_Tests.KeyHeld3d (LEFTWHEELBRAKE))
		pModel->LeftWheelBrake = 0x4000;
	else
		pModel->LeftWheelBrake = 0x0000;

	if (Key_Tests.KeyHeld3d (RIGHTWHEELBRAKE))
		pModel->RightWheelBrake = 0x4000;
	else
		pModel->RightWheelBrake = 0x0000;


	// Flaps, Speed Brakes, Slats, Gear up/down

	PAERODEVICE pAeroDevice = pModel->DeviceList;
	while (pAeroDevice != NULL)
	{
		pAeroDevice->Action (ControlledAC2, AeroDevice::CT_KEYS);
		if(pAeroDevice->Type == AeroDevice::DT_FLAPS)					//CSB 24/08/99	
		{																//CSB 24/08/99	
			if(Key_Tests.KeyPress3d(NEWFLAPSUP) )						//CSB 24/08/99	
				pAeroDevice->Attractor = 0x0000;						//CSB 24/08/99	
																		//CSB 24/08/99	
			if(Key_Tests.KeyPress3d(NEWFLAPSMID) )						//CSB 24/08/99	
				pAeroDevice->Attractor = 0x1555;						//CSB 24/08/99	
																		//CSB 24/08/99	
			if(Key_Tests.KeyPress3d(NEWFLAPSDOWN) )						//CSB 24/08/99	
				pAeroDevice->Attractor = 0x4000;						//CSB 24/08/99	
																		//CSB 24/08/99	
//DeadCode CSB 24/08/99				PrintVar(10, 10, "Flaps = %.d ", pAeroDevice->Attractor);	//CSB 24/08/99	
		}																//CSB 24/08/99	

		pAeroDevice = pAeroDevice->List.NextItem ();
	}


	// Elevator Trim
	if (Key_Tests.KeyHeld3d (ELEVTRIMFWD))
		if (pModel->ElevatorTrim < 16352)
			pModel->ElevatorTrim += 16;

	if (Key_Tests.KeyHeld3d (ELEVTRIMAFT))
		if (pModel->ElevatorTrim > -16352)
			pModel->ElevatorTrim -= 16;

	if (Key_Tests.KeyPress3d (ELEVTRIMNEU))
		pModel->ElevatorTrim = 0;



	// Prop Pitch
//TempCode ARM 29Jul97 	if (ControlledAC2->fly.pModel->Type == AT_F51D)
//TempCode ARM 29Jul97 	{
//TempCode ARM 29Jul97 		if (ControlledAC2->fly.pModel->EngineList != NULL)
//TempCode ARM 29Jul97 		{
//TempCode ARM 29Jul97 			if (Key_Tests.KeyPress3d (PROPLOWPITCH))
//TempCode ARM 29Jul97 				ControlledAC2->fly.pModel->EngineList->PropPitch = PP_LOW;
//TempCode ARM 29Jul97 			if (Key_Tests.KeyPress3d (PROPHIGHPITCH))
//TempCode ARM 29Jul97 				ControlledAC2->fly.pModel->EngineList->PropPitch = PP_HIGH;
//TempCode ARM 29Jul97 			if (Key_Tests.KeyPress3d (PROPFEATHER))
//TempCode ARM 29Jul97 				ControlledAC2->fly.pModel->EngineList->PropPitch = PP_FEATHER;
//TempCode ARM 29Jul97 		}
//TempCode ARM 29Jul97 	}

}

