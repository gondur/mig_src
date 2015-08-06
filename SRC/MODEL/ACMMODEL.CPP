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
//Filename       acmmodel.cpp
//System         
//Author         Andrew McRae
//Date           Wed 16 Apr 1997
//Description    Mig Alley Flight Model
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "monotxt.h"
#include "savegame.h"
#include "ranges.h"
#include	<math.h>
#include "planetyp.h"
#include	"replay.h"
#include	"persons2.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Null
//Author		Andrew McRae
//Date			Fri 13 Jun 1997
//
//Description	reset everything
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AcmModel::Null ()
{
	ULong n = sizeof(AcmModel);
	for (UByte* p=(UByte*)this;n;n--,p++) {	*p = 0;	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Calc
//Author		Andrew McRae
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AcmModel::Calc ()
{

//TempCode ARM 10Sep97 	Model& Mod = *pModel;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	// Controls
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	Elevator = ControlAttractor (Elevator, Mod.Elevator, 3);
//TempCode ARM 10Sep97 	Aileron = ControlAttractor (Aileron, Mod.Aileron, 3);
//TempCode ARM 10Sep97 	Rudder = ControlAttractor (Rudder, Mod.Rudder, 3);
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	// Calc Forces
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	pitch = (FP)Elevator * ElevatorCtrl;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	FP ctrldynpress = Mod.DynamicPressure;
//TempCode ARM 10Sep97 	if (ctrldynpress > MAXCTRLDYNPRESS)
//TempCode ARM 10Sep97 		ctrldynpress = MAXCTRLDYNPRESS;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	pitch *= ctrldynpress;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	aoa = pitch + Incidence;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	FP Cl = pClCurve->GetValue (aoa);
//TempCode ARM 10Sep97 	FP Cd = pCdCurve->GetValue (aoa);
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	FP Lift = Cl * Mod.DynamicPressure * Mod.Area;
//TempCode ARM 10Sep97 	FP Drag = Cd * Mod.DynamicPressure * Mod.Area;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	FP sin = FSin (aoa);
//TempCode ARM 10Sep97 	FP cos = FCos (aoa);
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	Mod.NettForce.x = 0;
//TempCode ARM 10Sep97 	Mod.NettForce.y = Lift*cos - Drag*sin;
//TempCode ARM 10Sep97 	Mod.NettForce.z = -Drag*cos - Lift*sin;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	// Set Orientation
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	if (Mod.AirSpeed == 0)
//TempCode ARM 10Sep97 		return;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	FCRD zvec;
//TempCode ARM 10Sep97 	zvec.x = -Mod.AirVel.x;
//TempCode ARM 10Sep97 	zvec.y = -Mod.AirVel.y;
//TempCode ARM 10Sep97 	zvec.z = -Mod.AirVel.z;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	NrmVec (zvec, zvec);
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	FCRD xvec;
//TempCode ARM 10Sep97 	xvec.x = zvec.z;
//TempCode ARM 10Sep97 	xvec.y = 0;
//TempCode ARM 10Sep97 	xvec.z = -zvec.x;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	NrmVec (xvec, xvec);
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	TnsPnt (zvec, zvec, Mod.Ori);
//TempCode ARM 10Sep97 	TnsPnt (xvec, xvec, Mod.Ori);
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	Mod.Ori.x.x = xvec.x;
//TempCode ARM 10Sep97 	Mod.Ori.x.y = xvec.y;
//TempCode ARM 10Sep97 	Mod.Ori.x.z = xvec.z;
//TempCode ARM 10Sep97 	Mod.Ori.z.x = zvec.x;
//TempCode ARM 10Sep97 	Mod.Ori.z.y = zvec.y;
//TempCode ARM 10Sep97 	Mod.Ori.z.z = zvec.z;
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	CPrdY (Mod.Ori);
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	RotOriXVec (Mod.Ori, pitch);
//TempCode ARM 10Sep97 	RotOriZVec (Mod.Ori, (FP)Aileron * AileronCtrl * ctrldynpress);
//TempCode ARM 10Sep97 	RotOriYVec (Mod.Ori, (FP)-Rudder * RudderCtrl * ctrldynpress);
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	// Engines
//TempCode ARM 10Sep97 
//TempCode ARM 10Sep97 	PTHRUSTPOINT pThrust = Mod.ThrustList;
//TempCode ARM 10Sep97 	while (pThrust != NULL)
//TempCode ARM 10Sep97 	{
//TempCode ARM 10Sep97 		pThrust->Process ();
//TempCode ARM 10Sep97 		Mod.NettForce.x += pThrust->Force.x;
//TempCode ARM 10Sep97 		Mod.NettForce.y += pThrust->Force.y;
//TempCode ARM 10Sep97 		Mod.NettForce.z += pThrust->Force.z;
//TempCode ARM 10Sep97 		pThrust = pThrust->List.NextItem ();
//TempCode ARM 10Sep97 	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Pilot
//Author		Andrew McRae
//Date			Mon 12 May 1997
//
//Description	Determine target AcmPoint
//
//Inputs		none
//
//Returns		none
//
//------------------------------------------------------------------------------
void AcmModel::Pilot (AirStrucPtr const ControlledAC)
{
//	FILE* fp=fopen("acmmode.txt","at");

//	LastElevator = pModel->Elevator;
//	LastAileron = pModel->Aileron;
//	LastRudder = pModel->Rudder;
	PMODEL pModel = ControlledAC->fly.pModel;

	SWord OldElevator = pModel->Elevator;	//CSB 08/03/99
	SWord OldAileron  = pModel->Aileron;	//CSB 08/03/99
	SWord OldRudder   = pModel->Rudder;	//CSB 08/03/99
//	fprintf(fp,"%d\n",_Replay.replayframecount);

	if (AcmMode[ACM_CLIMBRATE])
	{
//		fprintf(fp,"climbrate\n");
		ModClimbRate (ControlledAC);
	}

	if (AcmMode[ACM_HEIGHT])
	{
//		fprintf(fp,"height\n");
		ModHeight (ControlledAC);
	}

	if (AcmMode[ACM_MINHEIGHT])
	{
//		fprintf(fp,"minheight\n");
		ModMinHeight (ControlledAC);
	}


	if (AcmMode[ACM_KEEPWINGSLEVEL])
	{
//		fprintf(fp,"keep wings level\n");
		ModKeepWingsLevel (ControlledAC);
	}

	if (AcmMode[ACM_ROLLRATE])
	{
//		fprintf(fp,"roll rate\n");
		ModRollRate (ControlledAC);
	}

	if (AcmMode[ACM_ROLL])
	{
//		fprintf(fp,"roll\n");
		ModRoll (ControlledAC);
	}

	if (AcmMode[ACM_FASTROLL])
	{
//		fprintf(fp,"fastroll\n");
		ModFastRoll (ControlledAC);
	}

//	if (AcmMode[ACM_HEADING]) ModHeading ();

//	if (AcmMode[ACM_FLYDESIREDROLL]) ModFlyDesiredRoll ();

	if (AcmMode[ACM_SETTHRUST])
	{
//		fprintf(fp,"setthrust\n");
		SetThrust (ControlledAC);
	}

	if (AcmMode[ACM_PITCHRATE])
	{
//		fprintf(fp,"pitch rate\n");
		ModPitchRate (ControlledAC);
	}

	if (AcmMode[ACM_PITCH])
	{
//		fprintf(fp,"pitch\n");
		ModPitch (ControlledAC);
	}

	if (AcmMode[ACM_SPEED])
	{
//		fprintf(fp,"speed\n");
		ModSpeed (ControlledAC);
	}

	if (AcmMode[ACM_TURNRATE])
	{
//		fprintf(fp,"turnrate\n");
		ModTurnRate (ControlledAC);
	}

	if (AcmMode[ACM_VECTOR])
	{
//		fprintf(fp,"vector\n");
		ModVector (ControlledAC);
	}


	if (AcmMode[ACM_STAYVERTICAL])
	{
//		fprintf(fp,"stayvertical\n");
		ModStayVertical (FALSE);
	}

	if (AcmMode[ACM_ZEROSPECIFICPOWER])
	{
//		fprintf(fp,"zerospecpow\n");
		ModZeroSpecificPower (ControlledAC);
	}

	if (AcmMode[ACM_YAWRATE])
	{
//		fprintf(fp,"yawrate\n");
		ModYawRate (ControlledAC);
	}

	if (AcmMode[ACM_LIFTLIMIT])
	{
//		fprintf(fp,"liftlimit\n");
		ModLiftLimit (ControlledAC);
	}

	if (AcmMode[ACM_RUDDER])
	{
//		fprintf(fp,"rudder\n");
		ModRudder (ControlledAC);
	}

	if (AcmMode[ACM_ELEVATOR])
	{
//		fprintf(fp,"elevator\n");
		ModElevator (ControlledAC);
	}

	if (AcmMode[ACM_AILERON])
	{
//		fprintf(fp,"aileron\n");
		ModAileron (ControlledAC);
	}

	if (AcmMode[ACM_AOA])
	{
//		fprintf(fp,"aoa\n");
		ModAoA (ControlledAC);
	}

	if (AcmMode[ACM_RELAOA])
	{
//		fprintf(fp,"relaoa\n");
		ModRelAoA (ControlledAC);
	}

//	fclose(fp);

//DeadCode RDH 03Dec98 //rdh	if (AcmMode[ACM_SPEEDWITHELEVATORS]) ModSpeedWithElevators (ControlledAC);
//DeadCode RDH 03Dec98 //	if (AcmMode[ACM_YAWRATE]) ModYawRate (ControlledAC);
//DeadCode RDH 03Dec98 //	if (AcmMode[ACM_LIFTLIMIT]) ModLiftLimit (ControlledAC);
//DeadCode RDH 03Dec98 //	if (AcmMode[ACM_RUDDER]) ModRudder (ControlledAC);
//DeadCode RDH 03Dec98 //	if (AcmMode[ACM_ELEVATOR]) ModElevator (ControlledAC);
//DeadCode RDH 03Dec98 //	if (AcmMode[ACM_AILERON]) ModAileron (ControlledAC);
//DeadCode RDH 03Dec98 //	if (AcmMode[ACM_AOA]) ModAoA (ControlledAC);
//DeadCode RDH 03Dec98 //	if (AcmMode[ACM_RELAOA]) ModRelAoA (ControlledAC);
//DeadCode RDH 03Dec98 
//DeadCode RDH 03Dec98 
//DeadCode RDH 03Dec98 	// ACM_COMBAT / CRUISE modes ??	 - adjust control values
//DeadCode RDH 03Dec98 	// ACM_STAYVERTICAL + STAYVERTICALONHEADING
//DeadCode RDH 03Dec98 
//DeadCode RDH 03Dec98 //	pModel->Throttle = (SWord)((pModel->ThrottleFrac + 128) >> 8);
//DeadCode RDH 03Dec98 		
//DeadCode RDH 03Dec98 //	MODLIMIT (Elevator, 32767);
//DeadCode RDH 03Dec98 //	pModel->Elevator = (SWord)Elevator;
//DeadCode RDH 03Dec98 
//DeadCode RDH 03Dec98 //	MODLIMIT (Aileron, 32767);
//DeadCode RDH 03Dec98 //	pModel->Aileron = (SWord)Aileron;
//DeadCode RDH 03Dec98 //	MODLIMIT (Rudder, 32767);
//DeadCode RDH 03Dec98 //	pModel->Rudder = (SWord)Rudder;

	SLong DeltaElevator = pModel->Elevator - OldElevator;
	SLong DeltaAileron  = pModel->Aileron  - OldAileron;
	SLong DeltaRudder   = pModel->Rudder   - OldRudder;

	SWord MaxDelta = 6553 * pModel->MODEL_DT;
#ifdef PRINT_AI_DATA
PrintString(70, 2, "         ");
PrintString(70, 3, "         ");
PrintString(70, 4, "         ");
	if( (DeltaElevator > MaxDelta) || (DeltaElevator < -MaxDelta) ) PrintString(70, 2, "E Clipped");
	if( (DeltaAileron  > MaxDelta) || (DeltaAileron  < -MaxDelta) ) PrintString(70, 3, "A Clipped");
	if( (DeltaRudder   > MaxDelta) || (DeltaRudder   < -MaxDelta) ) PrintString(70, 4, "R Clipped");
#endif

	MODLIMIT(DeltaElevator, MaxDelta);
	MODLIMIT(DeltaAileron , MaxDelta);
	MODLIMIT(DeltaRudder  , MaxDelta);

	pModel->Elevator = OldElevator + DeltaElevator;
	pModel->Aileron  = OldAileron  + DeltaAileron;
	pModel->Rudder   = OldRudder   + DeltaRudder;

	MODLIMIT (pModel->Elevator, 32767);
	MODLIMIT (pModel->Aileron, 32767);
	MODLIMIT (pModel->Rudder, 32767);

	if((ControlledAC != Persons2::PlayerSeenAC) && (ControlledAC != Persons2::PlayerGhostAC))
	{
		ControlledAC->fly.elevator = pModel->Elevator;
		ControlledAC->fly.aileron  = pModel->Aileron;
		ControlledAC->fly.rudder   = pModel->Rudder;
	}

	OldAoa = 0.5 * (pModel->MainPlaneList->aoa[0][0] + pModel->MainPlaneList->aoa[1][0]);

//DeadCode CSB 08/03/99		int delevator = pModel->Elevator  - (int)ControlledAC->fly.elevator;
//DeadCode CSB 08/03/99		if (delevator > 20000)
//DeadCode CSB 08/03/99			delevator = 20000;
//DeadCode CSB 08/03/99		if (delevator < -20000)
//DeadCode CSB 08/03/99			delevator = -20000;
//DeadCode CSB 08/03/99		ControlledAC->fly.elevator = ControlledAC->fly.elevator + (SWord)delevator * pModel->MODEL_DT/100;
//DeadCode CSB 08/03/99	
//DeadCode CSB 08/03/99		int daileron = pModel->Aileron  - (int)ControlledAC->fly.aileron;
//DeadCode CSB 08/03/99		if (daileron > 20000)
//DeadCode CSB 08/03/99			daileron = 20000;
//DeadCode CSB 08/03/99		if (daileron < -20000)
//DeadCode CSB 08/03/99			daileron = -20000;
//DeadCode CSB 08/03/99		ControlledAC->fly.aileron = ControlledAC->fly.aileron + (SWord)daileron * pModel->MODEL_DT/100;
//DeadCode CSB 08/03/99	
//DeadCode CSB 08/03/99		int drudder = pModel->Rudder  - (int)ControlledAC->fly.rudder;
//DeadCode CSB 08/03/99		if (drudder > 10000)
//DeadCode CSB 08/03/99			drudder = 10000;
//DeadCode CSB 08/03/99		if (drudder < -10000)
//DeadCode CSB 08/03/99			drudder = -10000;
//DeadCode CSB 08/03/99		ControlledAC->fly.rudder = ControlledAC->fly.rudder + (SWord)drudder * pModel->MODEL_DT/100;



//Robert is handling all this
//	// Secondary Controls
//	{
//		// Default controls
//
//this is the version we need to keep rdh 22/4/98
//		if (pModel->Inst.IndicatedAirSpeed > 250) 
//		{
//			if (!Raised)
//			{
//				FlapsUp ();
//				GearUp ();
//				Raised = TRUE;
//			}
//		}
//		else
//			Raised = FALSE;
//	}

	ActionAeroDeviceCommands (ControlledAC);
//	AcmMode %= ACM_ZEROSPECIFICPOWER;
//	AcmMode %= ACM_YAWRATE;
//	AcmMode %= ACM_LIFTLIMIT;
//	AcmMode %= ACM_PITCH;
//	AcmMode %= ACM_TURNRATE;
//	AcmMode %= ACM_ROLL;
	Clear();
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ActionAeroDeviceCommands
//Author		Andrew McRae
//Date			Thu 18 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AcmModel::ActionAeroDeviceCommands (AirStrucPtr const ControlledAC)
{
	// Flaps, Speed Brakes, Slats, Gear up/down
	PMODEL pModel = ControlledAC->fly.pModel;

	PAERODEVICE pAeroDevice = pModel->DeviceList;
	while (pAeroDevice != NULL)
	{

		ULong command = ((ULong)pAeroDevice->Type << 1) + ACM_AERODEVICE_START;

		if (AcmMode[(ACM_COMMAND)(command - 1)])
		{
			pAeroDevice->Attractor = 0x0000;
			AcmMode %= (ACM_COMMAND)(command - 1);
		}

		if (AcmMode[(ACM_COMMAND)command])
		{
			pAeroDevice->Attractor = 0x4000;
			AcmMode %= (ACM_COMMAND)command;
		}

		pAeroDevice->Action (ControlledAC, AeroDevice::CT_AUTO);

		pAeroDevice = pAeroDevice->List.NextItem ();
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModClimbRate
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModClimbRate (AirStrucPtr const ControlledAC)
{
//	FP elev = 0;
//	elev += (pModel->wAcc.y - GRAVITY) * ClimbRate_Elevator_Damping_Power;
//	elev += (pModel->Vel.y - CtrlClimbRate) * ClimbRate_Elevator_Offset_Power;
//
//	Elevator += elev * FCos (pModel->fRoll);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModHeight
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModHeight (AirStrucPtr const ControlledAC)
{
//	FP hd;
//	hd = (pModel->Pos.y - CtrlHeight) * Height_Elevator_Offset_Power;
//	MODLIMIT (hd, Height_Elevator_Limit);
//	Elevator += hd;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModMinHeight
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModMinHeight (AirStrucPtr const ControlledAC)
{
	FP hd;
	PMODEL pModel = ControlledAC->fly.pModel;

	hd = pModel->Pos.y - CtrlHeight; 
	if (hd < 0)	
	{
		CtrlPitch = Rowan2Rads(ControlledAC->BestClimbAngle());
		ModPitch (ControlledAC);

//		hd = hd * Height_Elevator_Offset_Power;
//		MODLIMIT (hd, Height_Elevator_Limit);
//		Elevator += hd;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModRollRate
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModRollRate (AirStrucPtr const ControlledAC)
{
//	FP dr = pModel->fRoll - pModel->OldfRoll - CtrlRollRate;
//	Aileron -= (dr * RollRate_Aileron_Offset_Power);
	PMODEL pModel = ControlledAC->fly.pModel;

//DEADCODE DAW 30/03/99 	const	FP	DIFFAILERONFORMAXAILERON = F1PIE2/2;
	const	FP	MAXROLLRATEFACTOR = 100/FPIE;

	FP deltaroll = CtrlRollRate - pModel->RotVel.z;
	deltaroll = AngleSign (deltaroll);
//	FP	modifier = 0.6;

 
//DeadCode CSB 19/03/99	 	if ((rollmodifier * deltaroll) >= F1PIE2)
//DeadCode CSB 19/03/99	 		CtrlAileron = MaxAileron;
//DeadCode CSB 19/03/99	 	else if ((rollmodifier * deltaroll) <= -F1PIE2)
//DeadCode CSB 19/03/99	 		CtrlAileron = -MaxAileron;
//DeadCode CSB 19/03/99	 	else
 		CtrlAileron = rollmodifier * MaxAileron * deltaroll * MAXROLLRATEFACTOR;
	ModAileron(ControlledAC);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModRoll
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModRoll (AirStrucPtr const ControlledAC)
{
const	FP	DIFFAILERONFORMAXAILERON = F1PIE2/2;
	PMODEL pModel = ControlledAC->fly.pModel;

//DeadCode CSB 08/03/99		FP velmodifier = 110/pModel->Speed;	//CSB 08/03/99
	FP velmodifier = 1;	//CSB 08/03/99
	FP modifier = rollmodifier * velmodifier * velmodifier;
	FP intmodifier = rollintmodifier * velmodifier * velmodifier;

	FP deltaroll = AngleSign (CtrlRoll - pModel->fRoll);
	FP delta = AngleSign (OldCtrlRoll - CtrlRoll);
	FP deltapos = delta;
	if (delta < 0)
		deltapos = -delta;
	if (deltapos > 0.08)
	{//change of nearly 5 degs
//		if  (		(delta > 0)	&&	(deltaroll <0)
//				||	(delta < 0)	&&	(deltaroll >0)
//			)
//		{
			deltarollsum = deltarollsum=0;
			ControlledAC->ai.deltapitchsum = 0;
//		}
		OldCtrlRoll = CtrlRoll;

	}
	deltaroll = AngleSign (deltaroll);
//	FP	modifier = 0.6;
//DeadCode CSB 08/03/99		int MaxIntAileron = MaxAileron/4;
	int MaxIntAileron = MaxAileron;
 
//DeadCode CSB 18/03/99	 	if ((/*modifier * */deltaroll) >= F1PIE2)
//DeadCode CSB 18/03/99	 		pModel->Aileron = MaxAileron;
//DeadCode CSB 18/03/99	 	else if ((/*modifier * */deltaroll) <= -F1PIE2)
//DeadCode CSB 18/03/99	 		pModel->Aileron = -MaxAileron;
//DeadCode CSB 18/03/99	 	else
 		pModel->Aileron = modifier * MaxAileron * deltaroll/F1PIE2;

//integral control
//DeadCode CSB 19/03/99		if (deltarollsum > IntRollForMaxAileron)
//DeadCode CSB 19/03/99		{
//DeadCode CSB 19/03/99			pModel->Aileron += MaxIntAileron;
//DeadCode CSB 19/03/99			if (deltaroll < 0)
//DeadCode CSB 19/03/99				deltarollsum += deltaroll;
//DeadCode CSB 19/03/99		}
//DeadCode CSB 19/03/99		else if (deltarollsum < -IntRollForMaxAileron)
//DeadCode CSB 19/03/99		{
//DeadCode CSB 19/03/99			pModel->Aileron -= MaxIntAileron;
//DeadCode CSB 19/03/99			if (deltaroll >=0)
//DeadCode CSB 19/03/99				deltarollsum += deltaroll;
//DeadCode CSB 19/03/99		}
//DeadCode CSB 19/03/99		else
	{
		pModel->Aileron +=  intmodifier *MaxIntAileron * deltarollsum;// / IntRollForMaxAileron;
		deltarollsum += deltaroll;
	}

	//D control
//	FP deltadeltaroll = modifier * (deltaroll - lastdeltaroll);
//	if (deltadeltaroll >= DIFFAILERONFORMAXAILERON)
//		pModel->Aileron = MaxAileron;
//	else if (deltadeltaroll < -DIFFAILERONFORMAXAILERON)
//		pModel->Aileron = -MaxAileron;
//	else
//		pModel->Aileron +=	(MaxAileron * deltadeltaroll) / DIFFAILERONFORMAXAILERON;
//	
//	lastdeltaroll =  deltaroll;

//	if (pModel->Aileron > MaxAileron)
//		pModel->Aileron = MaxAileron;
//	if (pModel->Aileron < -MaxAileron)
//		pModel->Aileron = -MaxAileron;



}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModRoll
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModFastRoll (AirStrucPtr const ControlledAC)
{
	PMODEL pModel = ControlledAC->fly.pModel;

	SWord deltaroll = Rads2Rowan(AngleSign (CtrlRoll - pModel->fRoll));
	FP RollRate = pModel->RotVel.z;
	FP DesRollRate = deltaroll * 0.0001;
	FP DesAileron  = (DesRollRate - RollRate) * MAXAILERON;
	MODLIMIT(DesAileron, MAXAILERON);
	pModel->Aileron = DesAileron;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModHeading
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//inline void AcmModel::ModHeading ()
//{
//	FP h = pModel->fHdg;
//	FP dh = CtrlHeading - h;
//
//	MODLIMIT (dh, Heading_Aileron_Limit);
//	Aileron += (dh * Heading_Aileron_Offset_Power);
//}

// 14/4/98
// Andrew McRae
//inline void AcmModel::ModFlyDesiredRoll ()
//{
//	FP h = pModel->fRoll;
//	FP dh = desiredRoll - h;
//
//	if (dh > FPIE) dh = dh - F2PIE;
//	if (dh < -FPIE) dh = dh + F2PIE;
//
//	MODLIMIT (dh, Heading_Aileron_Limit);
//	Aileron += (dh * Heading_Aileron_Offset_Power);
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModKeepWingsLevel
//Author		Andrew McRae
//Date			Fri 5 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModKeepWingsLevel (AirStrucPtr const ControlledAC)
{
//	RollRate (0);
		PMODEL pModel = ControlledAC->fly.pModel;

	if ((pModel->fRoll > F1PIE2) && (pModel->fRoll < F3PIE2))
		CtrlRoll = FPIE;
	else
		CtrlRoll = 0;
	ModRoll(ControlledAC);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetThrust
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::SetThrust (AirStrucPtr const ControlledAC)
{
	PMODEL pModel = ControlledAC->fly.pModel;

	if (CtrlThrust >= 0)
		SpeedBrakesIn();
	if (CtrlThrust < 0)
	{
		SpeedBrakesOut();	  
		CtrlThrust = 0;
	}
	ControlledAC->fly.thrustpercent = CtrlThrust;
//	pModel->ThrottleFrac = (SLong)CtrlThrust << 8;
//	MODMAXMIN (pModel->ThrottleFrac, 0, 25600);
	AcmMode %= ACM_SETTHRUST;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModPitchRate
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModPitchRate (AirStrucPtr const ControlledAC)
{
//		PMODEL pModel = ControlledAC->fly.pModel;
//
//	if  (		(ControlledAC->roll >> ANGLES_90Deg)
//		&&	(ControlledAC->roll << ANGLES_270Deg)
//		)
//		pModel->Elevator = pModel->Elevator - pitchratemodifier * (pModel->Inst.pitchrate - CtrlPitchRate);
//	else
//		pModel->Elevator = pModel->Elevator + pitchratemodifier * (pModel->Inst.pitchrate - CtrlPitchRate);
//
//	if (pModel->Elevator < pModel->Elevator)
//		NearMaxAoA(ControlledAC);

//hijacked to do PitchCtrlByRoll
//but abandoned
	SLong	daileron;
	PMODEL pModel = ControlledAC->fly.pModel;


//	daileron = (CtrlPitchRate * CtrlPitchRate)/2048;		//up is positive
//	if (CtrlPitchRate > 0)
//		daileron = -daileron;
	daileron = -CtrlPitchRate/4;		//up is positive

	if (ControlledAC->roll >> ANGLES_180Deg)
		daileron = -daileron;
	if  (		(		(ControlledAC->roll << ANGLES_40Deg)
					&&	(daileron < 0)
				)
			||	(		(ControlledAC->roll >> ANGLES_320Deg)
					&&	(daileron > 0)
				)
		)
	{
		//CtrlRoll set by calling routine;
		ModRoll(ControlledAC);
	}
	else
	{
		CtrlAileron = pModel->Aileron + daileron;
	}
	ModAileron(ControlledAC);



}
inline void AcmModel::ModAoA (AirStrucPtr const ControlledAC)
{
#ifdef PRINT_AI_DATA
PrintString(50, 23, "ModAoa                     ");
PrintString(50, 24, "PitchModifier Int          ");
#endif

	PMODEL pModel = ControlledAC->fly.pModel;

	FP aoa0 = AngleSign (pModel->MainPlaneList->aoa[0][0]) + AngleSign (pModel->MainPlaneList->aoa[0][1]);
	FP aoa1 = AngleSign (pModel->MainPlaneList->aoa[1][0]) + AngleSign (pModel->MainPlaneList->aoa[1][1]);
	aoa0 *= 0.5;
	aoa1 *= 0.5;
	aoa0 = (aoa1+aoa0)/2;

	CtrlAoA = AngleSign (CtrlAoA);
	FP deltapitch = aoa0 - CtrlAoA;

	if  (	(!NearMaxAoA(ControlledAC))
		||	(deltapitch > 0)
		)
	{
		if (deltapitch > DeltaPitchForMaxElevator)
			pModel->Elevator = MaxElevatorForTightTurn;
		else if (deltapitch < -DeltaPitchForMaxElevator)
			pModel->Elevator = -MaxElevatorForTightTurn;
		else
			pModel->Elevator =  pitchmodifier * MaxElevatorForTightTurn * deltapitch / DeltaPitchForMaxElevator;


//Integral control
		if (deltapitchsum > IntPitchForMaxElevator)
		{
			pModel->Elevator += MaxElevatorForTightTurn;
			deltapitchsum = IntPitchForMaxElevator;
		}
		else if (deltapitchsum < -IntPitchForMaxElevator)
		{
			pModel->Elevator -= MaxElevatorForTightTurn;
			deltapitchsum = -IntPitchForMaxElevator;
		}
		else
			pModel->Elevator +=  pitchintmodifier *MaxElevatorForTightTurn * deltapitchsum / IntPitchForMaxElevator;


		if (pModel->Elevator > MaxElevatorForTightTurn)
			pModel->Elevator = MaxElevatorForTightTurn;
		if (pModel->Elevator < -MaxElevatorForTightTurn)
			pModel->Elevator = -MaxElevatorForTightTurn;


		if  (		(ControlledAC->roll > ANGLES_90Deg)
				&&	(ControlledAC->roll < ANGLES_270Deg)
			)
				pModel->Elevator = -pModel->Elevator; 

		lastdeltapitch = deltapitch;
		deltapitchsum += deltapitch;

	}

}
//try to get to within CtrlAoA of critical aoa
inline void AcmModel::ModRelAoA (AirStrucPtr const ControlledAC)
{
#ifdef PRINT_AI_DATA
PrintString(50, 23, "ModRelAoa                   ");
PrintString(50, 24, "PitchModifier Int           ");
#endif
	PMODEL pModel = ControlledAC->fly.pModel;

	UByte	FlyingFactor = ControlledAC->FlyingFactor();
	FP aoa0 = AngleSign (pModel->MainPlaneList->aoa[0][0]) + AngleSign (pModel->MainPlaneList->aoa[0][1]);
	FP aoa1 = AngleSign (pModel->MainPlaneList->aoa[1][0]) + AngleSign (pModel->MainPlaneList->aoa[1][1]);
	aoa0 *= 0.5;
	aoa1 *= 0.5;

	FP maxaoa = pModel->MainPlaneList->ACMmaxaoa;// -
//					((256 - FlyingFactor) * 0.174)/256;	//* 10 degs

	if (aoa0 < aoa1)
		aoa0 = aoa1;

	FP deltapitch = aoa0 - (maxaoa - CtrlAoA);

	if  (	(!NearMaxAoA(ControlledAC))
		||	(deltapitch > 0)
		)
	{
		if (deltapitch > DeltaPitchForMaxElevator)
			pModel->Elevator = MaxElevatorForTightTurn;
		else if (deltapitch < -DeltaPitchForMaxElevator)
			pModel->Elevator = -MaxElevatorForTightTurn;
		else
//			pModel->Elevator =  3 *pitchmodifier * MaxElevatorForTightTurn * deltapitch / DeltaPitchForMaxElevator;
			pModel->Elevator =  pitchmodifier * MaxElevatorForTightTurn * deltapitch / DeltaPitchForMaxElevator;


//Integral control
		if (deltapitchsum > IntPitchForMaxElevator)
		{
			pModel->Elevator += MaxElevatorForTightTurn;
			deltapitchsum = IntPitchForMaxElevator;
		}
		else if (deltapitchsum < -IntPitchForMaxElevator)
		{
			pModel->Elevator -= MaxElevatorForTightTurn;
			deltapitchsum = -IntPitchForMaxElevator;
		}
		else
			pModel->Elevator +=  pitchintmodifier *MaxElevatorForTightTurn * deltapitchsum / IntPitchForMaxElevator;


		if (pModel->Elevator > MaxElevatorForTightTurn)
			pModel->Elevator = MaxElevatorForTightTurn;
		if (pModel->Elevator < -MaxElevatorForTightTurn)
			pModel->Elevator = -MaxElevatorForTightTurn;


		if  (		(ControlledAC->roll > ANGLES_90Deg)
				&&	(ControlledAC->roll < ANGLES_270Deg)
			)
				pModel->Elevator = -pModel->Elevator; 

		lastdeltapitch = deltapitch;
		deltapitchsum += deltapitch;

	}

}

Bool AcmModel::NearMaxAoA(AirStrucPtr const ControlledAC)
{
//	FP modifier = 1000;
	PMODEL pModel = ControlledAC->fly.pModel;

	UByte	FlyingFactor = ControlledAC->FlyingFactor();
//DeadCode CSB 08/03/99		FP aoa0 = AngleSign (pModel->MainPlaneList->aoa[0][0]) + AngleSign (pModel->MainPlaneList->aoa[0][1]);
//DeadCode CSB 08/03/99		FP aoa1 = AngleSign (pModel->MainPlaneList->aoa[1][0]) + AngleSign (pModel->MainPlaneList->aoa[1][1]);
//DeadCode CSB 08/03/99		aoa0 *= 0.5;
//DeadCode CSB 08/03/99		aoa1 *= 0.5;
	FP aoa0 = AngleSign (pModel->MainPlaneList->aoa[0][1]);
	FP aoa1 = AngleSign (pModel->MainPlaneList->aoa[1][1]);

	FP maxaoa = pModel->MainPlaneList->ACMmaxaoa;
	//				- 	((256 - FlyingFactor) * 0.174)/256;	//* 10 degs
//DeadCode CSB 15/03/99		FP AoaRate = 0.5 * (pModel->MainPlaneList->aoa[0][0] + pModel->MainPlaneList->aoa[1][0]) - OldAoa;
//DeadCode CSB 15/03/99		AoaRate /= pModel->MODEL_DT;

#ifdef PRINT_AI_DATA
	PrintString(60, 6, "               ");
#endif
	if( (aoa0 > maxaoa) || (aoa1 > maxaoa) )//|| (AoaRate > FPIE * maxaoa * 0.01) )
	{
//DeadCode CSB 15/03/99			if (aoa0 < aoa1)
//DeadCode CSB 15/03/99				aoa0 = aoa1;
		CtrlElevator = 0;//pModel->Elevator + aoamodifier * (aoa0 - maxaoa);
		if (CtrlElevator > 0)
			CtrlElevator = 0;
		ModElevator(ControlledAC);	
#ifdef PRINT_AI_DATA
		PrintString(60, 6, "**** STALL ****");
#endif
		return (TRUE);
	}else
	{
		return(FALSE);
	}
 	
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModPitch
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModPitch (AirStrucPtr const ControlledAC)
{
#ifdef PRINT_AI_DATA
PrintString(50, 23, "ModPitch                    ");
PrintString(50, 24, "PitchModifier Int           ");
#endif
	static FP velpitch = 0;
//	FP old_velpitch = velpitch;
//	FP modifier = 2, intmodifier = 1.5; 
 
//	FP	elevator = 0;
//	FP modifier = 100;
//Note	MaxElevatorForTightTurn is positive (nose down)
	PMODEL pModel = ControlledAC->fly.pModel;

		CtrlPitch = AngleSign (CtrlPitch);
		velpitch = Rowan2Rads(ControlledAC->fly.cpitch);
		velpitch = AngleSign(velpitch);
		FP deltapitch = CtrlPitch - velpitch;

	if  (	(!NearMaxAoA(ControlledAC))
		||	(deltapitch > 0)
		)
	{
		if (deltapitch > DeltaPitchForMaxElevator)
			pModel->Elevator = -MaxElevatorForTightTurn;
		else if (deltapitch < -DeltaPitchForMaxElevator)
			pModel->Elevator = MaxElevatorForTightTurn;
		else
			pModel->Elevator = -pitchmodifier * MaxElevatorForTightTurn * deltapitch / DeltaPitchForMaxElevator;

//		FP deltadeltapitch = deltapitch - lastdeltapitch;
//		if (deltadeltapitch > DiffPitchForMaxElevator)
//			pModel->Elevator += MaxElevatorForTightTurn;
//		else if (deltadeltapitch < -DiffPitchForMaxElevator)
//			pModel->Elevator -= MaxElevatorForTightTurn;
//		else
//			pModel->Elevator +=  modifier * MaxElevatorForTightTurn * deltadeltapitch / DiffPitchForMaxElevator;

//Integral control
//DeaadCode CSB 18/03/99			PrintVar(50, 16, "dPitchSum %.1f ", (FP)deltapitchsum);
//DeadCode CSB 18/03/99			if (deltapitchsum > IntPitchForMaxElevator)
//DeadCode CSB 18/03/99			{
//DeadCode CSB 18/03/99				pModel->Elevator -= MaxElevatorForTightTurn;
//DeadCode CSB 18/03/99				deltapitchsum = IntPitchForMaxElevator;
//DeadCode CSB 18/03/99			}
//DeadCode CSB 18/03/99			else if (deltapitchsum < -IntPitchForMaxElevator)
//DeadCode CSB 18/03/99			{
//DeadCode CSB 18/03/99				pModel->Elevator += MaxElevatorForTightTurn;
//DeadCode CSB 18/03/99				deltapitchsum = -IntPitchForMaxElevator;
//DeadCode CSB 18/03/99			}
//DeadCode CSB 18/03/99			else
//DeadCode CSB 18/03/99				pModel->Elevator -=  pitchintmodifier *MaxElevatorForTightTurn * deltapitchsum / IntPitchForMaxElevator;


		if (pModel->Elevator > MaxElevatorForTightTurn)
			pModel->Elevator = MaxElevatorForTightTurn;
		if (pModel->Elevator < -MaxElevatorForTightTurn)
			pModel->Elevator = -MaxElevatorForTightTurn;

//		Elevator = LastElevator + (elevator-LastElevator)/ modifier;


		
//		FP ddp = lastdeltapitch - deltapitch;
//		if (ddp < 0)
//			ddp = -ddp;
//		if (ddp > 0.01)
//		{
//			if 	(	(deltapitch < 0)
//					&&
//					(LastElevator >= 0)
//				)
//				Elevator = -1;
//			else if	(	(deltapitch >= 0)
//						&&
//						(LastElevator < 0)
//					)
//				Elevator = 0;
//		}
//		else
//			Elevator = LastElevator + modifier * (deltapitch);


		if  (		(ControlledAC->roll > ANGLES_90Deg)
				&&	(ControlledAC->roll < ANGLES_270Deg)
			)
				pModel->Elevator = -pModel->Elevator; 

		lastdeltapitch = deltapitch;
		deltapitchsum += deltapitch;

	}
//DeadCode RDH 17Apr98 	Elevator += ((velpitch - CtrlPitch) * Pitch_Elevator_Offset_Power);
//DeadCode RDH 17Apr98 	Elevator += ((velpitch - old_velpitch) * Pitch_Elevator_Damping_Power);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModSpeed
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModSpeed (AirStrucPtr const ControlledAC)
{
//	pModel->ThrottleFrac += (SLong)((CtrlSpeed - pModel->AirSpeed) * Speed_Throttle_Offset_Power);
//	pModel->ThrottleFrac += (SLong)((pModel->OldAirSpeed - pModel->AirSpeed) * Speed_Throttle_Damping_Power);
//	MODMAXMIN (pModel->ThrottleFrac, 0, 25600);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModSpeedWithElevators
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModSpeedWithElevators (AirStrucPtr const ControlledAC)
{
#ifdef PRINT_AI_DATA
PrintString(50, 23, "ModSpeedWithElevators       ");
PrintString(50, 24, "PitchIntModifier            ");
#endif
	PMODEL pModel = ControlledAC->fly.pModel;


	FP delta = pModel->Inst.MachNo - CtrlMach;
	if (delta > 0.8)
		CtrlPitch = -MaxElevatorForTightTurn;
	else if (delta < -0.8)
		CtrlElevator = MaxElevatorForTightTurn;
	else
		CtrlElevator = - MaxElevatorForTightTurn * delta / 0.8;

	if (deltapitchsum > IntPitchForMaxElevator)
	{
		pModel->Elevator += MaxElevatorForTightTurn;
		deltapitchsum = IntPitchForMaxElevator;
	}
	else if (deltapitchsum < -IntPitchForMaxElevator)
	{
		pModel->Elevator -= MaxElevatorForTightTurn;
		deltapitchsum = -IntPitchForMaxElevator;
	}
	else
		CtrlElevator -=  pitchintmodifier *MaxElevatorForTightTurn * deltapitchsum / IntPitchForMaxElevator;
	deltapitchsum += delta;

	ModElevator(ControlledAC);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModTurnRate
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModTurnRate (AirStrucPtr const ControlledAC)
{
	FP maxaoa;		
	FP CtrlTurnRateAbs;
	UByte	FlyingFactor = ControlledAC->FlyingFactor();
	PMODEL pModel = ControlledAC->fly.pModel;

//DeadCode CSB 08/03/99		FP velmodifier = 110/pModel->Speed;	//fix this !!!!
	FP velmodifier = 1;	//CSB 08/03/99
	FP modifier = turnmodifier * velmodifier * velmodifier;
	FP intmodifier = turnintmodifier * velmodifier * velmodifier;
#ifdef PRINT_AI_DATA
PrintString(50, 23, "ModTurnRate                 ");
PrintString(50, 24, "TurnModifier Int            ");
#endif
	
	MODLIMIT(CtrlTurnRate, 0.5);
	CtrlTurnRateAbs = CtrlTurnRate;
	if (CtrlTurnRate < 0)
		CtrlTurnRateAbs = -CtrlTurnRate;

	FP AoaRate = 0.5 * (pModel->MainPlaneList->aoa[0][0] + pModel->MainPlaneList->aoa[1][0]) - OldAoa;
	AoaRate /= pModel->MODEL_DT;
	
	if  (	(ControlledAC->Range > DANGERRANGE)
//		||	(CtrlTurnRateAbs > 0.3)
		)
	{
		FP sustainedaoa = ControlledAC->classtype->maxturnrateaoaSL * (ControlledAC->classtype->abs_ceiling - ControlledAC->World.Y)/ControlledAC->classtype->abs_ceiling;
//DeadCode CSB 18/03/99			maxaoa = sustainedaoa + (pModel->MainPlaneList->ACMmaxaoa - sustainedaoa) * (256 - FlyingFactor)/256;	
		maxaoa = sustainedaoa + (pModel->MainPlaneList->ACMmaxaoa - sustainedaoa) * (FlyingFactor - 256)/256;

	}else
	{
		maxaoa = pModel->MainPlaneList->ACMmaxaoa - ((256 - FlyingFactor) * 0.174)/256;	//* 10 degs
	}

	FP aoa0 = AngleSign (pModel->MainPlaneList->aoa[0][1]);
	FP aoa1 = AngleSign (pModel->MainPlaneList->aoa[1][1]);
//DeadCode CSB 09/03/99		aoa0 *= 0.5;
//DeadCode CSB 09/03/99		aoa1 *= 0.5;
//DeadCode CSB 15/03/99		if (aoa0 < aoa1)
//DeadCode CSB 15/03/99			aoa0 = aoa1;
	
#ifdef PRINT_AI_DATA
	PrintString(60, 6, "               ");
#endif
	if( (aoa0 > maxaoa) || (aoa1 > maxaoa) )//|| (AoaRate > FPIE * maxaoa * 0.01 * 0.5) )
	{
	
//DeadCode CSB 30/06/99			FP AoaRate =- OldAoa;
//DeadCode CSB 30/06/99			AoaRate /= pModel->MODEL_DT;
		
		if (aoa0 < aoa1) aoa0 = aoa1;
		if(CtrlTurnRate > 0)
		{
//DeadCode DAW 01Jul99 			if(CtrlElevator < 0)
//DeadCode DAW 01Jul99 				CtrlElevator += aoamodifier * (aoa0 - maxaoa) * 100;
//DeadCode DAW 01Jul99 			CtrlElevator = 0;
		}
		else
		{
//DeadCode DAW 01Jul99 			CtrlElevator = 0;
			deltapitchsum = 0;
		}
	
//DeadCode CSB 15/03/99			CtrlElevator = 0;
//DeadCode CSB 15/03/99			if (CtrlElevator > 0)
//DeadCode CSB 15/03/99				CtrlElevator = 0;
//DeadCode CSB 15/03/99			ModElevator(ControlledAC);	
#ifdef PRINT_AI_DATA
		PrintString(60, 6, "**** STALL ****");
#endif

//DeadCode CSB 01/07/99		}else

		AoaRate *= 1;
		deltapitchsum -= 4 * CtrlTurnRate;

	}
//DeadCode CSB 15/03/99		if( (aoa0 > maxaoa) && (CtrlTurnRate >= 0) )
//DeadCode CSB 15/03/99			CtrlElevator = aoamodifier * (aoa0 - maxaoa);
//DeadCode CSB 15/03/99		else
	{
//DeadCode CSB 09/03/99			FP delta = OldCtrlTurnRate - CtrlTurnRate;
//DeadCode CSB 09/03/99			if (delta < 0)
//DeadCode CSB 09/03/99				delta = -delta;
//DeadCode CSB 09/03/99			if  (		(delta > 0.03)
//DeadCode CSB 09/03/99		//			||	(	(OldCtrlTurnRate > 0) && (CtrlTurnRate < 0))
//DeadCode CSB 09/03/99		//			||	(	(OldCtrlTurnRate < 0) && (CtrlTurnRate > 0))		
//DeadCode CSB 09/03/99		
//DeadCode CSB 09/03/99				)
//DeadCode CSB 09/03/99			{//change of nearly 2 degs
//DeadCode CSB 09/03/99				deltapitchsum = 0;
//DeadCode CSB 09/03/99				ControlledAC->ai.deltapitchsum = 0;
//DeadCode CSB 09/03/99			}
		OldCtrlTurnRate = CtrlTurnRate;
	 
		int MaxIntElevatorForTightTurn = MaxElevatorForTightTurn;
//		if  (	(!NearMaxAoA(ControlledAC))
//			||	(CtrlTurnRate < 0)
//			)
		{
//DeadCode CSB 09/03/99				if (CtrlTurnRate < -.5)
//DeadCode CSB 09/03/99					CtrlElevator = modifier * MaxElevatorForTightTurn;
//DeadCode CSB 09/03/99				else if (CtrlTurnRate > 0.5)
//DeadCode CSB 09/03/99					CtrlElevator = -modifier * MaxElevatorForTightTurn;
//DeadCode CSB 09/03/99				else
				CtrlElevator = -modifier * MaxElevatorForTightTurn * CtrlTurnRate;// / 0.5;
//DeadCode CSB 09/03/99				if (deltapitchsum > 20)
//DeadCode CSB 09/03/99				{
//DeadCode CSB 09/03/99					CtrlElevator -= intmodifier *MaxIntElevatorForTightTurn;
//DeadCode CSB 09/03/99					if (CtrlTurnRate < 0)
//DeadCode CSB 09/03/99						deltapitchsum += CtrlTurnRate;
//DeadCode CSB 09/03/99				}
//DeadCode CSB 09/03/99				else if (deltapitchsum < -20)
//DeadCode CSB 09/03/99				{
//DeadCode CSB 09/03/99					CtrlElevator += intmodifier *MaxIntElevatorForTightTurn;
//DeadCode CSB 09/03/99					if (CtrlTurnRate >= 0)
//DeadCode CSB 09/03/99						deltapitchsum += CtrlTurnRate;
//DeadCode CSB 09/03/99				}
//DeadCode CSB 09/03/99				else
			{
				CtrlElevator -= intmodifier * MaxIntElevatorForTightTurn * deltapitchsum;// / 20;
				
				if(		((CtrlElevator <  MaxIntElevatorForTightTurn) && (CtrlTurnRate < 0))
					||	((CtrlElevator > -MaxIntElevatorForTightTurn) && (CtrlTurnRate > 0)) )
					deltapitchsum += CtrlTurnRate;
			}
	
#ifdef PRINT_AI_DATA
			PrintVar(50, 14, "CtrlTurnR %.2f ", (FP)CtrlTurnRate);
			PrintVar(50, 15, "CtrlElevr %.0f ", (FP)CtrlElevator);
			PrintVar(50, 16, "dPitchSum %.1f ", (FP)deltapitchsum);
#endif
		}
	}	
//DeadCode CSB 09/03/99		//within 2 degs of maxaoa
//DeadCode CSB 09/03/99		//and want to pull more
//DeadCode CSB 09/03/99		if (		((maxaoa - aoa0) < 0.03)
//DeadCode CSB 09/03/99				&&	(CtrlElevator < pModel->Elevator)			
//DeadCode CSB 09/03/99			)
//DeadCode CSB 09/03/99		{
//DeadCode CSB 09/03/99	//DeadCode CSB 08/03/99			FP velmodifier = 110/pModel->Speed;	//CSB 08/03/99
//DeadCode CSB 09/03/99			FP velmodifier = 1;	//CSB 08/03/99
//DeadCode CSB 09/03/99			FP modifier = aoamodifier * velmodifier * velmodifier;
//DeadCode CSB 09/03/99	
//DeadCode CSB 09/03/99			CtrlElevator = pModel->Elevator + modifier * (aoa0 - maxaoa);
//DeadCode CSB 09/03/99		}else
//DeadCode CSB 09/03/99		{
//DeadCode CSB 09/03/99			FP testing = 0;
//DeadCode CSB 09/03/99		}

	CtrlElevator += aoamodifier * AoaRate * 1000;
	ModElevator(ControlledAC);
}


//DeadCode RDH 30Nov98 //	FP modifier = 5000; 
//DeadCode RDH 30Nov98 //
//DeadCode RDH 30Nov98 //
//DeadCode RDH 30Nov98 //	pModel->Elevator = LastElevator - modifier * (CtrlTurnRate);
//DeadCode RDH 30Nov98 //
//DeadCode RDH 30Nov98 //	if (pModel->Elevator < LastElevator)
//DeadCode RDH 30Nov98 //		NearMaxAoA();
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 //	FP modifier = 2, intmodifier = 1.5; 
//DeadCode RDH 30Nov98 	PMODEL pModel = ControlledAC->fly.pModel;
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 	FP	distancemod = 0.00001 * (ControlledAC->Range - METRES500);
//DeadCode RDH 30Nov98 	if (distancemod < 0)
//DeadCode RDH 30Nov98 		distancemod = 0;
//DeadCode RDH 30Nov98 	if (distancemod > 0.5)
//DeadCode RDH 30Nov98 		distancemod = 0.5;
//DeadCode RDH 30Nov98 	else
//DeadCode RDH 30Nov98 		distancemod = 1 - distancemod;
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 	FP delta = OldCtrlTurnRate - CtrlTurnRate;
//DeadCode RDH 30Nov98 	if (delta < 0)
//DeadCode RDH 30Nov98 		delta = -delta;
//DeadCode RDH 30Nov98 	if  (		(delta > 0.03)
//DeadCode RDH 30Nov98 //			||	(	(OldCtrlTurnRate > 0) && (CtrlTurnRate < 0))
//DeadCode RDH 30Nov98 //			||	(	(OldCtrlTurnRate < 0) && (CtrlTurnRate > 0))		
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 		)
//DeadCode RDH 30Nov98 	{//change of nearly 2 degs
//DeadCode RDH 30Nov98 		deltapitchsum = 0;
//DeadCode RDH 30Nov98 		ControlledAC->ai.deltapitchsum = 0;
//DeadCode RDH 30Nov98 	}
//DeadCode RDH 30Nov98 	OldCtrlTurnRate = CtrlTurnRate;
//DeadCode RDH 30Nov98  
//DeadCode RDH 30Nov98 	int MaxIntElevatorForTightTurn = MaxElevatorForTightTurn/4;
//DeadCode RDH 30Nov98 	if  (	(!NearMaxAoA(ControlledAC))
//DeadCode RDH 30Nov98 		||	(CtrlTurnRate < 0)
//DeadCode RDH 30Nov98 		)
//DeadCode RDH 30Nov98 	{
//DeadCode RDH 30Nov98 			UByte	FlyingFactor = ControlledAC->FlyingFactor();
//DeadCode RDH 30Nov98 			FP aoa0 = AngleSign (pModel->MainPlaneList->aoa[0][0]) + AngleSign (pModel->MainPlaneList->aoa[0][1]);
//DeadCode RDH 30Nov98 			FP aoa1 = AngleSign (pModel->MainPlaneList->aoa[1][0]) + AngleSign (pModel->MainPlaneList->aoa[1][1]);
//DeadCode RDH 30Nov98 			aoa0 *= 0.5;
//DeadCode RDH 30Nov98 			aoa1 *= 0.5;
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 			FP maxaoa = pModel->MainPlaneList->ACMmaxaoa;// -
//DeadCode RDH 30Nov98 							//((256 - FlyingFactor) * 0.174)/256;	//* 5 degs
//DeadCode RDH 30Nov98 			if (aoa0 < aoa1)
//DeadCode RDH 30Nov98 				aoa0 = aoa1;
//DeadCode RDH 30Nov98 			if (CtrlTurnRate < -.5)
//DeadCode RDH 30Nov98 				CtrlElevator = turnmodifier * MaxElevatorForTightTurn;
//DeadCode RDH 30Nov98 			else if (CtrlTurnRate > 0.5)
//DeadCode RDH 30Nov98 				CtrlElevator = -turnmodifier * MaxElevatorForTightTurn;
//DeadCode RDH 30Nov98 			else
//DeadCode RDH 30Nov98 				CtrlElevator =  - turnmodifier * MaxElevatorForTightTurn * CtrlTurnRate / 0.5;
//DeadCode RDH 30Nov98 			if (deltapitchsum > 20)
//DeadCode RDH 30Nov98 			{
//DeadCode RDH 30Nov98 				CtrlElevator -= turnintmodifier *MaxIntElevatorForTightTurn;
//DeadCode RDH 30Nov98 				if (CtrlTurnRate < 0)
//DeadCode RDH 30Nov98 					deltapitchsum += CtrlTurnRate;
//DeadCode RDH 30Nov98 			}
//DeadCode RDH 30Nov98 			else if (deltapitchsum < -20)
//DeadCode RDH 30Nov98 			{
//DeadCode RDH 30Nov98 				CtrlElevator += turnintmodifier *MaxIntElevatorForTightTurn;
//DeadCode RDH 30Nov98 				if (CtrlTurnRate >= 0)
//DeadCode RDH 30Nov98 					deltapitchsum += CtrlTurnRate;
//DeadCode RDH 30Nov98 			}
//DeadCode RDH 30Nov98 			else
//DeadCode RDH 30Nov98 			{
//DeadCode RDH 30Nov98 				CtrlElevator -=  turnintmodifier *MaxIntElevatorForTightTurn * deltapitchsum / 20;
//DeadCode RDH 30Nov98 				deltapitchsum += CtrlTurnRate;
//DeadCode RDH 30Nov98 			}
//DeadCode RDH 30Nov98 			CtrlElevator = CtrlElevator * distancemod;
//DeadCode RDH 30Nov98 			if ((maxaoa - aoa0) < 0.14)
//DeadCode RDH 30Nov98 			{
//DeadCode RDH 30Nov98 				int newelevator = pModel->Elevator + liftmodifier * (aoa0 - maxaoa);
//DeadCode RDH 30Nov98 				if (newelevator > CtrlElevator)
//DeadCode RDH 30Nov98 					CtrlElevator = newelevator;
//DeadCode RDH 30Nov98 			}
//DeadCode RDH 30Nov98 //			if (CtrlElevator > 0)
//DeadCode RDH 30Nov98 //				CtrlElevator = 0;
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 	}
//DeadCode RDH 30Nov98 	ModElevator(ControlledAC);
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 //	int MaxIntElevatorForTightTurn = MaxElevatorForTightTurn/2;
//DeadCode RDH 30Nov98 //	if  (	(!NearMaxAoA(ControlledAC))
//DeadCode RDH 30Nov98 //		||	(CtrlTurnRate < 0)
//DeadCode RDH 30Nov98 //		)
//DeadCode RDH 30Nov98 //	{
//DeadCode RDH 30Nov98 //		if (CtrlTurnRate < -.5)
//DeadCode RDH 30Nov98 //			CtrlElevator = MaxElevatorForTightTurn;
//DeadCode RDH 30Nov98 //		else if (CtrlTurnRate > 0.5)
//DeadCode RDH 30Nov98 //			CtrlElevator = -MaxElevatorForTightTurn;
//DeadCode RDH 30Nov98 //		else
//DeadCode RDH 30Nov98 //			CtrlElevator =  - turnmodifier * MaxElevatorForTightTurn * CtrlTurnRate / 0.5;
//DeadCode RDH 30Nov98 //
//DeadCode RDH 30Nov98 //		if (deltapitchsum > 80)
//DeadCode RDH 30Nov98 //		{
//DeadCode RDH 30Nov98 //			CtrlElevator -= turnintmodifier *MaxIntElevatorForTightTurn;
//DeadCode RDH 30Nov98 //			if (CtrlTurnRate < 0)
//DeadCode RDH 30Nov98 //				deltapitchsum += CtrlTurnRate;
//DeadCode RDH 30Nov98 //		}
//DeadCode RDH 30Nov98 //		else if (deltapitchsum < -80)
//DeadCode RDH 30Nov98 //		{
//DeadCode RDH 30Nov98 //			CtrlElevator += turnintmodifier *MaxIntElevatorForTightTurn;
//DeadCode RDH 30Nov98 //			if (CtrlTurnRate >= 0)
//DeadCode RDH 30Nov98 //				deltapitchsum += CtrlTurnRate;
//DeadCode RDH 30Nov98 //		}
//DeadCode RDH 30Nov98 //		else
//DeadCode RDH 30Nov98 //		{
//DeadCode RDH 30Nov98 //			CtrlElevator -=  turnintmodifier *MaxIntElevatorForTightTurn * deltapitchsum / 80;
//DeadCode RDH 30Nov98 //			deltapitchsum += CtrlTurnRate;
//DeadCode RDH 30Nov98 //		}
//DeadCode RDH 30Nov98 //
//DeadCode RDH 30Nov98 		
//DeadCode RDH 30Nov98 //	}
//DeadCode RDH 30Nov98 //	ModElevator(ControlledAC);
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 
//DeadCode RDH 30Nov98 //	FP modifier = 100000; 
//DeadCode RDH 30Nov98 //
//DeadCode RDH 30Nov98 //	if  (		(pModel->fRoll < FPIE)
//DeadCode RDH 30Nov98 //			&&	(CtrlTurnRate < 0)
//DeadCode RDH 30Nov98 //		)
//DeadCode RDH 30Nov98 //		CtrlTurnRate = 0;
//DeadCode RDH 30Nov98 //	if  (		(pModel->fRoll >= FPIE)
//DeadCode RDH 30Nov98 //			&&	(CtrlTurnRate > 0)
//DeadCode RDH 30Nov98 //		)
//DeadCode RDH 30Nov98 //		CtrlTurnRate = 0;
//DeadCode RDH 30Nov98 //
//DeadCode RDH 30Nov98 //	FP turn = pModel->Inst.turn;
//DeadCode RDH 30Nov98 //	if (turn < 0 )
//DeadCode RDH 30Nov98 //		turn = -turn;
//DeadCode RDH 30Nov98 //	if (CtrlTurnRate < 0)
//DeadCode RDH 30Nov98 //		CtrlTurnRate = -CtrlTurnRate;
//DeadCode RDH 30Nov98 //	FP deltaturnrate = turn - CtrlTurnRate;
//DeadCode RDH 30Nov98 //
//DeadCode RDH 30Nov98 //	pModel->Elevator = LastElevator + modifier * (deltaturnrate);
//DeadCode RDH 30Nov98 //
//DeadCode RDH 30Nov98 //	if (pModel->Elevator < LastElevator)
//DeadCode RDH 30Nov98 //		NearMaxAoA();
//DeadCode RDH 30Nov98 }



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModVector
//Author		Andrew McRae
//Date			Wed 21 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void AcmModel::ModVector (AirStrucPtr const ControlledAC)
{
//TempCode ARM 03Sep97 	// Relative Velocity Vector Defined in World Coords
//TempCode ARM 03Sep97 
//TempCode ARM 03Sep97 	// change in vel (world coords)
//TempCode ARM 03Sep97 	
//TempCode ARM 03Sep97 	FCRD tgtvel;
//TempCode ARM 03Sep97 
//TempCode ARM 03Sep97 	tgtvel.x = CtrlVector.x - pModel->Vel.x;
//TempCode ARM 03Sep97 	tgtvel.y = CtrlVector.y - pModel->Vel.y;
//TempCode ARM 03Sep97 	tgtvel.z = CtrlVector.z - pModel->Vel.z;
//TempCode ARM 03Sep97 
//TempCode ARM 03Sep97 	// calc max attainable acceleration (max aoa, speed, limits etc.)
//TempCode ARM 03Sep97 
//TempCode ARM 03Sep97 	// scale to 90%
//TempCode ARM 03Sep97 
//TempCode ARM 03Sep97 	// add gravity
//TempCode ARM 03Sep97 
//TempCode ARM 03Sep97 	// rotate into local coords
}
void AcmModel::ModYawRate(AirStrucPtr const ControlledAC)
{
//	FP deltayaw = CtrlYawRate - pModel->RotVel.x;
//	FP roll = AngleSign (pModel->fRoll);
//	if (roll > 0)
//	{
//		if (pModel->RotVel.x < 0)
//			pModel->RotVel.x = 0;
//	}else
//	{
//		if (pModel->RotVel.x > 0)
//			pModel->RotVel.x = 0;
//	}
//	FP modifier = 0.5, intmodifier = 1; 
	PMODEL pModel = ControlledAC->fly.pModel;

//DeadCode CSB 08/03/99		FP velmodifier = 110/pModel->Speed;		//fix this !!!!
	FP velmodifier = 1;	//CSB 08/03/99
	FP modifier = yawmodifier * velmodifier * velmodifier;
	FP intmodifier = yawintmodifier * velmodifier * velmodifier;

	FP	distancemod = 0.00001 * (ControlledAC->Range - METRES500);		//max out at 1500m
	if (distancemod < 0)
		distancemod = 0;
	if (distancemod > 1)
		distancemod = 1;
	else
		distancemod = 1 - distancemod;

	int MaxIntRudder  = MaxElevatorForTightTurn/4;
 
	FP delta = OldCtrlYawRate - CtrlYawRate;
	if (delta < 0)
		delta = -delta;
	if  (		(delta > 0.05)
//			||	(	(OldCtrlYawRate > 0) && (CtrlYawRate < 0))
//			||	(	(OldCtrlYawRate < 0) && (CtrlYawRate > 0))		

		)
	{//change of nearly 3 degs
		deltayawsum = 0;
		OldCtrlYawRate = CtrlYawRate;
	}
 


		if (CtrlYawRate < -.5)
			pModel->Rudder = -modifier *  MaxElevatorForTightTurn * 0.5;
		else if (CtrlYawRate > 0.5)
			pModel->Rudder = modifier * MaxElevatorForTightTurn * 0.5;
		else
			pModel->Rudder =   modifier * MaxElevatorForTightTurn * CtrlYawRate;

		if (deltayawsum > 40)
		{
			pModel->Rudder += intmodifier *MaxIntRudder;
			if (CtrlYawRate < 0)
				deltayawsum += CtrlYawRate;
		}
		else if (deltayawsum < -40)
		{
			pModel->Rudder -= intmodifier *MaxIntRudder;
			if (CtrlYawRate >= 0)
				deltayawsum += CtrlYawRate;
		}
		else
		{
			pModel->Rudder +=  intmodifier * MaxIntRudder * deltayawsum / 40;
			deltayawsum += CtrlYawRate;
		}
		pModel->Rudder = pModel->Rudder * distancemod;

}


void AcmModel::ZeroIntControl()
{
	deltayawsum = 0;
	deltarollsum = 0;
	deltapitchsum = 0;
//##	ControlledAC->ai.deltapitchsum = 0;

}


void AcmModel::ModLiftLimit (AirStrucPtr const ControlledAC)
{
#ifdef PRINT_AI_DATA
PrintString(50, 23, "ModLiftLimit                ");
PrintString(50, 24, "LiftModifier                 ");
#endif
//	FP liftmodifier = 1000; 
	PMODEL pModel = ControlledAC->fly.pModel;
  
	UByte	FlyingFactor = ControlledAC->FlyingFactor();
	FP aoa0 = AngleSign (pModel->MainPlaneList->aoa[0][0]) + AngleSign (pModel->MainPlaneList->aoa[0][1]);
	FP aoa1 = AngleSign (pModel->MainPlaneList->aoa[1][0]) + AngleSign (pModel->MainPlaneList->aoa[1][1]);
	aoa0 *= 0.5;
	aoa1 *= 0.5;

//If it is right to get to the lift limit, then the better pilots will get closer
	FP maxaoa = pModel->MainPlaneList->ACMmaxaoa - ((256 - FlyingFactor) * 0.174)/256;	//* 10 degs

//DeadCode CSB 21/03/99		if (!NearMaxAoA(ControlledAC))
	{
//DeadCode CSB 21/03/99			if (aoa0 < aoa1)
//DeadCode CSB 21/03/99				aoa0 = aoa1;
//DeadCode CSB 21/03/99	//DeadCode CSB 08/03/99			FP velmodifier = 110/pModel->Speed;	//fix this !!!!
//DeadCode CSB 21/03/99			FP velmodifier = 1;	//CSB 08/03/99
//DeadCode CSB 21/03/99			FP modifier = liftmodifier * velmodifier * velmodifier;
//DeadCode CSB 21/03/99	
//DeadCode CSB 21/03/99	
//DeadCode CSB 21/03/99			CtrlElevator = pModel->Elevator + modifier * (aoa0 - maxaoa);

		FP AoaRate = (0.5 * (aoa0 + aoa1) - OldAoa) / Timer_Code.FRAMETIME;
		FP DesAoaRate = (maxaoa - aoa0) * 0.1;
		FP DesElevator = -(DesAoaRate - AoaRate) * MaxElevatorForTightTurn * 250;
		MODLIMIT(DesElevator, MaxElevatorForTightTurn);
		pModel->Elevator = DesElevator;
		
	}
//DeadCode CSB 21/03/99		ModElevator(ControlledAC);

//			if (pModel->Elevator > MaxElevatorForTightTurn)
//			pModel->Elevator = MaxElevatorForTightTurn;
//		if (pModel->Elevator < -MaxElevatorForTightTurn)
//			pModel->Elevator = -MaxElevatorForTightTurn;

}


void AcmModel::ModZeroSpecificPower (AirStrucPtr const ControlledAC)
{
#ifdef PRINT_AI_DATA
PrintString(50, 23, "ModZeroSpecificPower        ");
PrintString(50, 24, "AoaModifier                 ");
#endif
		PMODEL pModel = ControlledAC->fly.pModel;
  
	UByte	FlyingFactor = ControlledAC->FlyingFactor();
	FP aoa0 = AngleSign (pModel->MainPlaneList->aoa[0][0]) + AngleSign (pModel->MainPlaneList->aoa[0][1]);
	FP aoa1 = AngleSign (pModel->MainPlaneList->aoa[1][0]) + AngleSign (pModel->MainPlaneList->aoa[1][1]);
	aoa0 *= 0.5;
	aoa1 *= 0.5;

//to sustain the speed and turn don't go to the lift limit. Poor pilots will tend towards the lift limit
	FP maxaoa = pModel->MainPlaneList->ACMmaxaoa;// -
	FP aoa;
		//((256 - FlyingFactor) * 0.174)/256;	//* 5 degs
	
	FP sustainedaoa = ControlledAC->classtype->maxturnrateaoaSL * (ControlledAC->classtype->abs_ceiling - ControlledAC->World.Y)/ControlledAC->classtype->abs_ceiling;

	aoa = sustainedaoa;	// + (maxaoa - sustainedaoa) * (256 - FlyingFactor)/256;

//modify max to account for skill
	FP f;
	f = FlyingFactor;
	f = f/256;
	maxaoa = 0.087 + (maxaoa - 0.087) * f;
	if (aoa > maxaoa)
		aoa = maxaoa;

#ifdef PRINT_AI_DATA
PrintVar(60, 8, "%.1f ", (FP)(aoa * 57.3) );
#endif

//DeadCode CSB 08/03/99		FP velmodifier = 110/pModel->Speed;
//DeadCode CSB 08/03/99		FP modifier = aoamodifier * velmodifier * velmodifier;
//DeadCode CSB 08/03/99	
//DeadCode CSB 08/03/99		CtrlElevator = pModel->Elevator + modifier * (aoa0 - aoa);
	FP DeltaAoa = aoa - (aoa0 + aoa1) * 0.5;
	CtrlElevator = pModel->Elevator - aoamodifier * DeltaAoa;

	ModElevator(ControlledAC);


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModStayVertical
//Author		Andrew McRae
//Date			Mon 8 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AcmModel::StayVertical (AirStrucPtr const ControlledAC)
{
	AcmMode |= ACM_STAYVERTICAL;
	ModStayVertical (TRUE);
}


inline void AcmModel::ModRudder(AirStrucPtr const ControlledAC)
{
	PMODEL pModel = ControlledAC->fly.pModel;

	int maxdef = 6553 * pModel->MODEL_DT;
	int drudder = CtrlRudder - pModel->Rudder;
	if (drudder > maxdef)
		drudder = maxdef;
	if (drudder < -maxdef)
		drudder = -maxdef;
	pModel->Rudder = pModel->Rudder + (SWord)drudder;
//		pModel->Rudder = CtrlRudder;
}
inline void AcmModel::ModElevator(AirStrucPtr const ControlledAC)
{
	PMODEL pModel = ControlledAC->fly.pModel;

//	int maxdef = 65536 * pModel->MODEL_DT/100
	int maxdef = 6553 * pModel->MODEL_DT;
	int delevator = CtrlElevator - pModel->Elevator;
	if (delevator > maxdef)
		delevator = maxdef;
	if (delevator < -maxdef)
		delevator = -maxdef;
	int newelevator = pModel->Elevator + (SWord)delevator;
	if (newelevator > 32767)
		newelevator = 32767;
	if (newelevator < -32767)
		newelevator = -32767;

	pModel->Elevator = newelevator;
//	pModel->Elevator = CtrlElevator;
}
inline void AcmModel::ModAileron(AirStrucPtr const ControlledAC)
{
	PMODEL pModel = ControlledAC->fly.pModel;

	int maxdef = 6553 * pModel->MODEL_DT;
	int daileron = CtrlAileron - pModel->Aileron;
	if (daileron > maxdef)
		daileron = maxdef;
	if (daileron < -maxdef)
		daileron = -maxdef;
	pModel->Aileron = pModel->Aileron + (SWord)daileron;
//	pModel->Aileron = CtrlAileron;
}
inline void AcmModel::ModStayVertical (Bool Init)
{
	// use elevator & rudder & aileron
//	PMODEL pModel = ControlledAC->fly.pModel;
//
//	static ULong Stage = 0;
//
//	if (Init)
//	{
//		Stage = 0;
//		return;
//	}
//
//	FP sRoll = AngleSign (pModel->fRoll);
//
//	switch (Stage)
//	{
//		case 0:
//			Roll (0);
//			if ((sRoll < DEGS2RADS(25)) && (sRoll > -DEGS2RADS(25)))
//				Stage = 1;
//			break;
//
//		case 1:
//			Pitch (90);
//			break;
//	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcControls
//Author		Andrew McRae
//Date			Mon 12 May 1997
//
//Description	Calc desired Orientation and speed to achieve ACMPoint
//				And determine if Acm point has been passed
//				(i.e. end or go to next point)
//
//Inputs		Acm Point
//
//Returns		TRUE if completed this point, else FALSE
//
//------------------------------------------------------------------------------
//Bool AcmModel::Logic (ACMPOINT& Pnt)
Bool AcmModel::Logic (AirStrucPtr const ControlledAC)
{
	return FALSE;
//TempCode ARM 14May97 	Model& Mod = *pModel;
//TempCode ARM 14May97 
//TempCode ARM 14May97 	// Calc Point Pos in ac coords
//TempCode ARM 14May97 	FCRD trgtpos;
//TempCode ARM 14May97 	trgtpos.x = Pnt.Pos.x - Mod.Pos.x;
//TempCode ARM 14May97 	trgtpos.y = Pnt.Pos.y - Mod.Pos.y;
//TempCode ARM 14May97 	trgtpos.z = Pnt.Pos.z - Mod.Pos.z;
//TempCode ARM 14May97 
//TempCode ARM 14May97 	// Determine if target achieved
//TempCode ARM 14May97 	FP dist = VecLen (trgtpos);	// only need do after Speed tests
//TempCode ARM 14May97 	switch (SwitchType)
//TempCode ARM 14May97 	{
//TempCode ARM 14May97 		case APST_TOOFAST:
//TempCode ARM 14May97 			if (Mod.Speed > SwitchSpeed) return TRUE;
//TempCode ARM 14May97 			break;
//TempCode ARM 14May97 
//TempCode ARM 14May97 		case APST_TOOSLOW:
//TempCode ARM 14May97 			if (Mod.Speed < SwitchSpeed) return TRUE;
//TempCode ARM 14May97 			break;
//TempCode ARM 14May97 
//TempCode ARM 14May97 		case APST_TOONEAR:
//TempCode ARM 14May97 			if (dist < SwitchDist) return TRUE;
//TempCode ARM 14May97 			break;
//TempCode ARM 14May97 	}
//TempCode ARM 14May97 
//TempCode ARM 14May97 	// calc aim point
//TempCode ARM 14May97 	FP t = dist / Mod.Speed; // could have an adjust value here
//TempCode ARM 14May97 	FCRD aimpos;
//TempCode ARM 14May97 	aimpos.x = Pos.x - (Vel.x * t);
//TempCode ARM 14May97 	aimpos.y = Pos.y - (Vel.y * t);
//TempCode ARM 14May97 	aimpos.z = Pos.z - (Vel.z * t);
//TempCode ARM 14May97 
//TempCode ARM 14May97 	// calc 
//TempCode ARM 14May97 	TnsAxs
//TempCode ARM 14May97 
//TempCode ARM 14May97 	FCRD accvec;
//TempCode ARM 14May97 
//TempCode ARM 14May97 	accvec.x = lpos.x - (Mod.Vel.x * VelAdj);
//TempCode ARM 14May97 	accvec.y = lpos.y - (Mod.Vel.y * VelAdj);
//TempCode ARM 14May97 	accvec.z = lpos.z - (Mod.Vel.z * VelAdj);
//TempCode ARM 14May97 
//TempCode ARM 14May97 	TnsAxs (accvec, accvec, Mod.Ori);
//TempCode ARM 14May97 
//TempCode ARM 14May97 	// Calc required acceleration
//TempCode ARM 14May97 	// (this is approximate and is probably slightly too high)
//TempCode ARM 14May97 	FP acc = 2 * lpos.y * Speed2 / (lpos.z * lpos.z);
//TempCode ARM 14May97 
//TempCode ARM 14May97 	acc = LimitAcceleration (acc);
//TempCode ARM 14May97 
//TempCode ARM 14May97 	// determine roll
//TempCode ARM 14May97 
//TempCode ARM 14May97 	FORI ori;
//TempCode ARM 14May97 
//TempCode ARM 14May97 	lpos.z = 0;
//TempCode ARM 14May97 	NrmVec (lpos, ori.y);
//TempCode ARM 14May97 
//TempCode ARM 14May97 	ori.y.x *= acc;
//TempCode ARM 14May97 	ori.y.y *= acc;
//TempCode ARM 14May97 	ori.y.z *= acc;
//TempCode ARM 14May97 
//TempCode ARM 14May97 	ori.y.y += GRAVITY;
//TempCode ARM 14May97 
//TempCode ARM 14May97 	// determine pitch
//TempCode ARM 14May97 
//TempCode ARM 14May97 	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Control
//Author		Andrew McRae
//Date			Mon 12 May 1997
//
//Description	Calc actual control inputs to achieve desired attitude & speed
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AcmModel::Control (FORI& Ori, FP Speed)
{
//DeadCode ARM 05Sep97 	Model& Mod = *pModel;
//DeadCode ARM 05Sep97 
//DeadCode ARM 05Sep97 	Mod.Elevator = (SWord)0;
//DeadCode ARM 05Sep97 	Mod.Aileron = (SWord)0;
//DeadCode ARM 05Sep97 	Mod.Rudder = (SWord)0;
//DeadCode ARM 05Sep97 
//DeadCode ARM 05Sep97 	Mod.Throttle = (SWord)0;
//DeadCode ARM 05Sep97 
//DeadCode ARM 05Sep97 	Mod.LeftWheelBrake = (SWord)0;
//DeadCode ARM 05Sep97 	Mod.RightWheelBrake = (SWord)0;
//DeadCode ARM 05Sep97 
//DeadCode ARM 05Sep97 	Mod.SpeedBrake = (SWord)0;
//DeadCode ARM 05Sep97 
//DeadCode ARM 05Sep97 	if (Mod.DynamicPressure < Mod.SlatOutPressure)
//DeadCode ARM 05Sep97 		Mod.Slats = 0x4000;
//DeadCode ARM 05Sep97 	if (Mod.DynamicPressure > Mod.SlatInPressure)
//DeadCode ARM 05Sep97 		Mod.Slats = 0x0000;	
//DeadCode ARM 05Sep97 
//DeadCode ARM 05Sep97 	Mod.Flaps = 0x4000;
//DeadCode ARM 05Sep97 	Mod.Flaps = 0x0000;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MaxNormalAcceleration
//Author		Andrew McRae
//Date			Thu 22 May 1997
//
//Description	Calculates Max Normal acceleration allowed
//				Based on Pilot limits, dynamic pressure etc.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void AcmModel::MaxMinNormalAcceleration (FP& maxg, FP& ming)
//{
//TempCode ARM 07Oct97 	FP lift = LiftSlope * pModel->DynamicPressure * Area / pModel->Mass;
//TempCode ARM 07Oct97 
//TempCode ARM 07Oct97 	maxg = MaxAoa * lift;
//TempCode ARM 07Oct97 	ming = MinAoa * lift;
//TempCode ARM 07Oct97 
//TempCode ARM 07Oct97 	if (maxg > MaxG) maxg = MaxG;
//TempCode ARM 07Oct97 	if (ming < MinG) ming = MinG;
//}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Acceleration Limit
//Author		Andrew McRae
//Date			Tue 13 May 1997
//
//Description	Limits requested normal acceleration -
//				Max/Min G, stall, etc.
//
//Inputs		acc
//
//Returns		acc
//
//------------------------------------------------------------------------------
//FP AcmModel::LimitAcceleration (FP acc)
//{
///TempCode ARM 07Oct97 	if (acc > MaxG) return MaxG;
//TempCode ARM 07Oct97 	if (acc < MinG) return MinG;
//TempCode ARM 07Oct97 
//TempCode ARM 07Oct97 	FP lift = LiftSlope * pModel->DynamicPressure * Area;
//TempCode ARM 07Oct97 
//TempCode ARM 07Oct97 	FP maxg = (MaxAoa * lift) / pModel->Mass;
//TempCode ARM 07Oct97 	FP ming = (MinAoa * lift) / pModel->Mass;
//TempCode ARM 07Oct97 
//TempCode ARM 07Oct97 	if (acc > maxg) return maxg;
//TempCode ARM 07Oct97 	if (acc < ming) return ming;

//	return acc;
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeltaAngle
//Author		Andrew McRae
//Date			Thu 15 May 1997
//
//Description	returns signed difference between to angles
//
//Inputs		a1, a2
//
//Returns		a2 - a1
//
//------------------------------------------------------------------------------
inline SWord DeltaAngle (UWord a1, UWord a2)
{
	SLong dif = (SLong)a2 - (SLong)a1;
	if (dif > 32767) dif = dif - 65536;
	if (dif < -32768) dif = 65536 + dif;
	return (SWord)dif;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeltaAngle
//Author		Andrew McRae
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
FP DeltaAngle (FP a1, FP a2)
{
	FP dif = a2 - a1;
	if (dif > FPIE) dif = dif - F2PIE;
	if (dif < -FPIE) dif = F2PIE + dif;
	return dif;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AngleSign
//Author		Andrew McRae
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//inline FP AngleSign (FP ang)
//{	//E3=10 bits - got about 50 bits = E15
//	ang=fmod(ang,FPIE);
//	return ang;
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ControlAttractor
//Author		Andrew McRae
//Date			Thu 8 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord ControlAttractor (SWord val, SWord att, UWord rate)
{
	SLong dval = (SLong)(att - val);
	if (dval > 0)
	{
		dval >>= rate;
		if (!dval) dval = 1;
		val += dval;
		return val;
	}
	if (dval < 0)
	{
		dval = -dval;
		dval >>= rate;
		if (!dval) dval = 1;
		val -= dval;
		return val;
	}
	return val;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CtrlShiftRight
//Author		Andrew McRae
//Date			Mon 12 May 1997
//
//Description	Shifts a number right always leaving 1 bit set
//
//Inputs		the number and shift value
//
//Returns		the shifted number
//
//------------------------------------------------------------------------------
SWord CtrlShiftRight (SWord val, SWord shift)
{
	if (!val) return val;
	val = val >> shift;
	if (!val) val = 1;
	return val;
}
