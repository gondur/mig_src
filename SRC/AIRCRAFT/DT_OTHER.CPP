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
//Filename       Dt_other.cpp
//System         
//Author         Craig Beeston
//Date           Tue 20 Apr 1999
//Description    B26 B29 T6 Generic flight model
//------------------------------------------------------------------------------

#include "dosdefs.h"
#include "worldinc.h"
#include "3DCom.h"
#include "modvec.h"
#include "model.h"

void B26_Setup (AirStrucPtr const ControlledAC, ULong Version)
{
	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
	Model.Type = AT_B26;
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);//RJS 14May98

	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &ControlledAC->fly.rpm, &adptr->acrpm, 0, 65536);

//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pNose, &adptr->aclegsuspf, 0, 255);
//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
//DeadCode CSB 20/04/99	 	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);
	PENGINE pEngine = new ENGINE (pModel, ET_PISTON);
}

void B29_Setup (AirStrucPtr const ControlledAC, ULong Version)
{
	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
	Model.Type = AT_B29;
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);//RJS 14May98

	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &ControlledAC->fly.rpm, &adptr->acrpm, 0, 65536);
//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pNose, &adptr->aclegsuspf, 0, 255);
//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
//DeadCode CSB 20/04/99	 	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);
	PENGINE pEngine = new ENGINE (pModel, ET_PISTON);
}

void T6_Setup (AirStrucPtr const ControlledAC, ULong Version)
{
	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
	Model.Type = AT_T6;
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);//RJS 14May98

	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &ControlledAC->fly.rpm, &adptr->acrpm, 0, 65536);
//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pNose, &adptr->aclegsuspf, 0, 255);
//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
//DeadCode CSB 20/04/99	 	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);
	PENGINE pEngine = new ENGINE (pModel, ET_PISTON);
	pEngine->T100 = 1000000;	//Power in watts
	PMAINPLANE pMainPlane = new MAINPLANE (pModel, 75250, 230, 345, 33000, 165, 215);
}

void F4U5_Setup (AirStrucPtr const ControlledAC, ULong Version)
{
	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
	Model.Type = AT_F4U5;
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);//RJS 14May98

	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &ControlledAC->fly.rpm, &adptr->acrpm, 0, 65536);
//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pNose, &adptr->aclegsuspf, 0, 255);
//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
//DeadCode CSB 20/04/99	 	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);
	PENGINE pEngine = new ENGINE (pModel, ET_PISTON);
	pEngine->T100 = 1000000;	//Power in watts
	PMAINPLANE pMainPlane = new MAINPLANE (pModel, 75250, 230, 345, 33000, 165, 215);
}

//DeadCode CSB 05/05/99	#pragma message ("YAK9_SETUP - already defined ?")
/*
void YAK9_Setup (AirStrucPtr const ControlledAC, ULong Version)
{
	ClassPtr data = ControlledAC->classtype;
	PMODEL pModel = ControlledAC->fly.pModel;
	Model& Model = *ControlledAC->fly.pModel;
	AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
	Model.Type = AT_YAK9;
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator, 32767, -32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);//RJS 14May98
//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pNose, &adptr->aclegsuspf, 0, 255);
//DeadCode CSB 20/04/99		new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
//DeadCode CSB 20/04/99	 	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);
	PENGINE pEngine = new ENGINE (pModel, ET_PISTON);
	pEngine->T100 = 1000000;	//Power in watts
	PMAINPLANE pMainPlane = new MAINPLANE (pModel, 75250, 230, 345, 33000, 165, 215);
}
*/
