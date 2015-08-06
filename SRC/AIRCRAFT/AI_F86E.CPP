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
//Filename       AI_f86e.cpp
//System         
//Author         Split from DT_f86e.cpp
//Date           Thu 10 Dec 1998
//Description    F86E AI settings
//------------------------------------------------------------------------------

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
//DeadCode RJS 02Dec97 #include "3dcom.h"

void F86E_SetupAI (AirStrucPtr const ControlledAC, ULong Version)
{
	ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;

	
	ACM.BrakePower = 14;
	ACM.SteerRatio = 8e-6;

	ACM.MaxAileron = 32767;
	ACM.MaxElevatorForTightTurn	= 32767;

//	ACM.DiffPitchForMaxElevator	= 0.1745;

	ACM.aoamodifier = 1000;//1200;
	ACM.DeltaPitchForMaxElevator = 0.25;//	= 1.0472;

	ACM.pitchmodifier = 0.25;
//DeadCode CSB 08/03/99		ACM.pitchratemodifier = 0;//100000;
	ACM.pitchintmodifier = 0;//1.5;
	ACM.IntPitchForMaxElevator	= 0.1;//1000;

	ACM.rollmodifier = 1.0;//0.5;	
	ACM.rollintmodifier = 0;//2;
	ACM.IntRollForMaxAileron = 100;//80;

	ACM.yawmodifier = 5;//6;
	ACM.yawintmodifier = 0;//3;	

	ACM.turnmodifier = 1;//1.2;
	ACM.turnintmodifier = 0.01;//12;
	ACM.liftmodifier = 1000;//1200;



	ACM.maxdeltaforclosework = 0.1;
	ACM.lastdeltapitch = 0;

	ACM.deltapitchsum = 0;
	ACM.deltarollsum = 0;
	ACM.deltayawsum = 0;

}
//DeadCode CSB 12/03/99		ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;
//DeadCode CSB 12/03/99	
//DeadCode CSB 12/03/99		
//DeadCode CSB 12/03/99	//used for simple ground taxi-ing
//DeadCode CSB 12/03/99		ACM.BrakePower = 14;
//DeadCode CSB 12/03/99		ACM.SteerRatio = 8e-6;
//DeadCode CSB 12/03/99	
//DeadCode CSB 12/03/99		ACM.MaxAileron = 32767;
//DeadCode CSB 12/03/99	
//DeadCode CSB 12/03/99		ACM.DeltaPitchForMaxElevator	= 1.0472;
//DeadCode CSB 12/03/99		ACM.MaxElevatorForTightTurn	= 32767;
//DeadCode CSB 12/03/99		ACM.lastdeltapitch = 0;
//DeadCode CSB 12/03/99		ACM.deltapitchsum = 0;
//DeadCode CSB 12/03/99		ACM.deltayawsum = 0;
//DeadCode CSB 12/03/99		ACM.yawmodifier = 8;		//10;			//0.2
//DeadCode CSB 12/03/99		ACM.yawintmodifier = 3;	//1;		//1;
//DeadCode CSB 12/03/99		ACM.turnmodifier = 1;		//1.1;			//		2;
//DeadCode CSB 12/03/99		ACM.turnintmodifier = 10;		//1.6;		//1.5;
//DeadCode CSB 12/03/99		ACM.rollmodifier = 0.7;	//0.6;
//DeadCode CSB 12/03/99		ACM.pitchratemodifier = 100000;
//DeadCode CSB 12/03/99		ACM.aoamodifier = 1000;
//DeadCode CSB 12/03/99		ACM.pitchmodifier = 1;			//2;
//DeadCode CSB 12/03/99		ACM.pitchintmodifier = 1.5;
//DeadCode CSB 12/03/99		ACM.liftmodifier = 1000; 
//DeadCode CSB 12/03/99	
//DeadCode CSB 12/03/99		ACM.deltarollsum = 0;
//DeadCode CSB 12/03/99		ACM.rollintmodifier = 2;	//1;
//DeadCode CSB 12/03/99		ACM.IntRollForMaxAileron = 80;
//DeadCode CSB 12/03/99		ACM.IntPitchForMaxElevator	= 1000;
//DeadCode CSB 12/03/99		ACM.maxdeltaforclosework = 0;
//DeadCode CSB 12/03/99	}
