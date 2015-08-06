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
//Filename       calib.cpp
//System         
//Author         Andrew McRae
//Date           Wed 10 Sep 1997
//Description    
//------------------------------------------------------------------------------
//
//To set up the calibration data to be printed out on the mono screen:
//
//		define		EMIT_HM_DATA
//					EMIT_DOGHOUSE_DATA
//					PS_CALCS
//		in model.h
//
//
//
#include <stdio.h>
#include <string.h>
#include	<stdlib.h>

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "ranges.h"
#include "myangles.h"
#include "planetyp.h"
#include "collided.h"
#include "time.h"
#include "myerror.h"
#include "monotxt.h"
#include "savegame.h"
#include "missman2.h"
//DeadCode RJS 02Dec97 #include "3dcom.h"

//#define SETSIMPLEMOVECODE

#ifdef CALIBRATION_CODE
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetInputs
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Flys the  aeroplane in a certain way to calibrate its performance
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalibrationInputs ()
{

//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 	// write data for cl/cd curve
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 	if (Key_Tests.KeyHeld3d (ELEVTRIMNEU))
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 	{
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 		FILE* file = NULL;
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 		file = fopen ("clcd.dat", "wt");
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 		if (file != NULL)
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 		{
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 			FP aoa;
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 			for (aoa = -10; aoa <= 20; aoa += 0.5)
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 			{
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 				FP radaoa = Degs2Rads(aoa);
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 				FP Cl = ACMModel.pClCurve->GetValue (radaoa);
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 				FP Cd = ACMModel.pCdCurve->GetValue (radaoa);
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 				FP ClCd = Cl / Cd;
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 				fprintf (file, "%.2f\t%.4f\t%.4f\t%.4f\n", aoa, Cl, Cd, ClCd);
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 			}
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 			fclose (file);
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 		}
//TempCode ARM 04Nov97 //TempCode ARM 29Aug97 	}
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 	// determine aoa at max ClCd
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 	static Bool Done = FALSE;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 	static FP MaxClCdAoa;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 	static FP MaxClCd;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 	if (!Done)
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 	{
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 		MaxClCdAoa = 0;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 		MaxClCd = -9999;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 		FP aoa;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 		for (aoa = -10; aoa <= 20; aoa += 0.001)
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 		{
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			FP radaoa = Degs2Rads(aoa);
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			FP Cl = ACMModel.pClCurve->GetValue (radaoa);
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			FP Cd = ACMModel.pCdCurve->GetValue (radaoa);
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			FP ClCd = Cl / Cd;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			if (ClCd > MaxClCd)
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			{
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 				MaxClCd = ClCd;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 				MaxClCdAoa = radaoa;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			}
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 		}
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 		Done = TRUE;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 	}
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	static SLong TestElevator = 0;
//TempCode ARM 04Nov97 	static SLong TestAileron = 0;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	#define cTestHeights 5
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	static FP TestHeight [cTestHeights];
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	TestHeight[0] = FT_700;
//TempCode ARM 04Nov97 	TestHeight[1] = FT_10000;
//TempCode ARM 04Nov97 	TestHeight[2] = FT_20000;
//TempCode ARM 04Nov97 	TestHeight[3] = FT_25000;
//TempCode ARM 04Nov97 	TestHeight[4] = FT_35000;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	static SLong iTestHeight = 0;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	SLong hd;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	FP climbrate;
//TempCode ARM 04Nov97 	FP pitch;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	FP accdamp;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	PSURFACE pSurf;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	FP aoa;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	switch (Type)
//TempCode ARM 04Nov97 	{
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 		case AT_F86E:
//TempCode ARM 04Nov97 		case AT_MIG15:
//TempCode ARM 04Nov97 		case AT_F84E:
//TempCode ARM 04Nov97 		case AT_F80C:
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 			TestElevator += (SLong)((wAcc.y - GRAVITY) * 5000);
//TempCode ARM 04Nov97 			TestElevator += (SLong)(Vel.y * 50);
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 			hd = (SLong)((Pos.y - TestHeight[iTestHeight]) * 0.1);
//TempCode ARM 04Nov97 			MODLIMIT (hd, 500);
//TempCode ARM 04Nov97 			TestElevator += hd;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			// keep IAS = 430 - crap
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			// keep NrmG = GRAVITY - crap
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			// Fly at maximum Cl/Cd
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			// keep NrmG = 1
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			accdamp = (30000 * (150 + 10)) / (IndicatedAirSpeed + 10);
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 //			accdamp = 50000;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			TestElevator += (SLong)((wAcc.y - GRAVITY) * accdamp);
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			pSurf = SurfaceList;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			aoa = 0;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			while (pSurf)
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			{
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 				if (pSurf->Type == ST_MAINPLANE)
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 					aoa += pSurf->aoa;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 				pSurf = pSurf->List.NextItem();
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			}
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			aoa = aoa * 0.25;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			if (aoa > FPIE) aoa = aoa - F2PIE;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			TestElevator += (SLong)((aoa - MaxClCdAoa) * 10000);
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			PrintVar (40, 10, "%ld    ", (SLong)(aoa * 1000));
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 			PrintVar (40, 11, "%ld    ", (SLong)(MaxClCdAoa * 1000));
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 //			TestElevator += (SLong)((430 - IndicatedAirSpeed) * 1);
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 //			if (Pos.y < 2136)
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 //				TestElevator += (SLong)((Pos.y - 21336) * 0.01);
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 //			pitch = fPitch;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 //			if (pitch > FPIE) pitch = pitch - F2PIE;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 //			if (pitch > DEGS2RADS(45)) TestElevator += 5000;
//TempCode ARM 04Nov97 //TempCode ARM 20Aug97 //			if (pitch < DEGS2RADS(-20)) TestElevator -= 5000;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 			break;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 		case AT_F51D:
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 			TestElevator += (SLong)((Acc.y - GRAVITY) * 10000);		
//TempCode ARM 04Nov97 			TestElevator += (SLong)(Vel.y * 50);					
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 			hd = (SLong)((Pos.y - TestHeight[iTestHeight]) * 0.1);			
//TempCode ARM 04Nov97 			MODLIMIT (hd, 1000);										
//TempCode ARM 04Nov97 			TestElevator += hd;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 			break;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	}
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	MODLIMIT (TestElevator, 32767);
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	Elevator = (SWord)TestElevator;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	if (Key_Tests.KeyPress3d (ELEVTRIMFWD))
//TempCode ARM 04Nov97 	{
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 		iTestHeight++;
//TempCode ARM 04Nov97 		if (iTestHeight >= cTestHeights) iTestHeight = cTestHeights - 1;
//TempCode ARM 04Nov97 		Pos.y = TestHeight[iTestHeight];
//TempCode ARM 04Nov97 //		TestHeight += FT_100;
//TempCode ARM 04Nov97 	}
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	if (Key_Tests.KeyPress3d (ELEVTRIMAFT))
//TempCode ARM 04Nov97 	{
//TempCode ARM 04Nov97 		iTestHeight--;
//TempCode ARM 04Nov97 		if (iTestHeight < 0) iTestHeight = 0;
//TempCode ARM 04Nov97 		Pos.y = TestHeight[iTestHeight];
//TempCode ARM 04Nov97 //		TestHeight -= FT_100;
//TempCode ARM 04Nov97 	}
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	// Keep level & heading = 180
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	FP r = fRoll;
//TempCode ARM 04Nov97 	if (r > FPIE) r = r - F2PIE;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	FP dr = fRoll - OldfRoll;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 //	FP h = fHdg;
//TempCode ARM 04Nov97 //	FP dh = FPIE - h;
//TempCode ARM 04Nov97 //	MODLIMIT (dh, DEGS2RADS(45));
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	FP ta = /*(dh * 50000)*/ - (r * 5000) - (dr * 25000);
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	TestAileron = (SLong)ta;
//TempCode ARM 04Nov97 	MODLIMIT (TestAileron, 32767);
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	Aileron = TestAileron;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	Rudder = 0;
//TempCode ARM 04Nov97 
//TempCode ARM 04Nov97 	PrintVar (0, 23, "TestHeight %.0f   ", TestHeight[iTestHeight] * 0.03281);


}
#endif



#ifdef WRITE_MODEL_LOG

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WriteModelLog
//Author		Andrew McRae
//Date			Tue 28 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::WriteModelLog ()
{

	static Bool FirstEntry = TRUE;

	static ULong con = 0;

	FILE* file = NULL;

	if (FirstEntry)
	{
		FirstEntry = FALSE;

		file = fopen ("acm.log", "wt");
		if (file != NULL)
		{

			PMODEL pModel = ModelList;

			while (pModel != NULL)
			{

				fprintf (file, "Log Count: %ld\n", con++);

				fprintf (file, "Model Ident: %ld\n", pModel->Ident);

				if (pModel->Type == AT_F86A) fprintf (file, "Ac Type: AT_F86A\n");
				else if (pModel->Type == AT_F86E) fprintf (file, "Ac Type: AT_F86E\n");
				else if (pModel->Type == AT_F86F) fprintf (file, "Ac Type: AT_F86F\n");
				else if (pModel->Type == AT_MIG15) fprintf (file, "Ac Type: AT_MIG15\n");
				else if (pModel->Type == AT_MIG15BIS) fprintf (file, "Ac Type: AT_MIG15BIS\n");
				else if (pModel->Type == AT_F84E) fprintf (file, "Ac Type: AT_F84E\n");
				else if (pModel->Type == AT_F80C) fprintf (file, "Ac Type: AT_F80C\n");
				else if (pModel->Type == AT_F9F2) fprintf (file, "Ac Type: AT_F9F2\n");
				else if (pModel->Type == AT_F8) fprintf (file, "Ac Type: AT_F8\n");
				else if (pModel->Type == AT_F51D) fprintf (file, "Ac Type: AT_F51D\n");
				else if (pModel->Type == AT_F82G) fprintf (file, "Ac Type: AT_F82G\n");
				else if (pModel->Type == AT_YAK9) fprintf (file, "Ac Type: AT_YAK9\n");
				else if (pModel->Type == AT_F4U5) fprintf (file, "Ac Type: AT_F4U4\n");
				else if (pModel->Type == AT_SFURY) fprintf (file, "Ac Type: AT_SFURY\n");
				else if (pModel->Type == AT_FFLY) fprintf (file, "Ac Type: AT_FFLY\n");
				else if (pModel->Type == AT_A1) fprintf (file, "Ac Type: AT_A1\n");
				else fprintf (file, "Ac Type: NOT RECOGNISED\n");

				if (pModel->Controlled) fprintf (file, "%s\n", "Manual");
				else fprintf (file, "%s\n", "Auto");

				fprintf (file, "Pos X: %ld\n", pModel->ControlledAC->World.X);
				fprintf (file, "Pos Y: %ld\n", pModel->ControlledAC->World.Y);
				fprintf (file, "Pos Z: %ld\n", pModel->ControlledAC->World.Z);

				fprintf (file, "Hdg:  %ld\n", pModel->ControlledAC->hdg / 182);
				fprintf (file, "Ptch: %ld\n", pModel->ControlledAC->pitch / 182);

				fprintf (file, "Horiz Vel: %ld\n", pModel->ControlledAC->vel);

				if (pModel->ControlledAC->ai.unfriendly != NULL)
				{
					if (pModel->ControlledAC->ai.unfriendly->Status.size == AirStrucSize)
					{
						AirStrucPtr acptr = (AirStrucPtr)pModel->ControlledAC->ai.unfriendly;

						if (acptr->fly.pModel != NULL)
						{
							fprintf (file, "Unfriendly Model Ident %ld\n", acptr->fly.pModel->Ident);
						}
						else
							fprintf (file, "Got Unfriendly - but no pModel\n");
					}
					else
						fprintf (file, "Got Unfriendly - but not AirStrucSize\n");
				}
				else
					fprintf (file, "No Unfriendly\n");


				fprintf (file, "\n");

				pModel = pModel->List.NextItem ();
			}

			fclose (file);
		}

	}

}
#endif


#ifdef EMIT_HM_DATA
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmitHMData
//Author		Andrew McRae
//Date			Tue 28 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Exit=FALSE;
Bool Init=TRUE;
SLong Selec;
ULong delay;
ULong delay2;
Bool Inc;
Bool Dec;
FP FirstPs, LastPs, PsStep;
FP FirstMach, LastMach, MachStep;
FP LLLastMach, LLFirstMach, LLMachStep;
//FP	PsSteps, MachSteps;
void Model::EmitHMData (AirStrucPtr const ControlledAC)
{
	static Bool FirstTimeRound = TRUE;
	if(FirstTimeRound)
	{
		Mass  = ControlledAC->classtype->weightempty;
		Mass += ControlledAC->classtype->maxintfuel;
		FirstTimeRound = FALSE;
	}

	static FP Height=0;		//feet
	if (Exit) return;
	if (Init)
	{
//		static Bool EmitHMData = TRUE;
	//static Bool EmitHMData = FALSE;


//		if (!EmitHMData) break;

//		EmitHMData = FALSE;

//		if (MainPlaneList == NULL) break;

		LLFirstMach	= 0.025;
		LLMachStep = 0.025;
		LLLastMach = LLFirstMach + LLMachStep * (LIFTLIMITRANGE - 1);
		FirstPs = -100;
		PsStep = 50;
		LastPs = FirstPs + PsStep * (PSRANGE-1);
//		PsSteps = 1+ (LastPs - FirstPs)/PsStep;
		FirstMach = 0.025;
		MachStep = 0.025;
		LastMach = FirstMach + MachStep * (MACHRANGE - 1);
//		MachSteps = 1 + (LastMach- FirstMach)/MachStep;
		Init=FALSE;
		Selec = 0;
		delay = 0;
		delay2 = 0;
		ClrDogHouseData(Height);

		Inc = FALSE;
		Dec = FALSE;

		PrintString (0, 0,"Calibatration Data");
		PrintString (0, 2,"Key 1:   move to prev variable");
		PrintString (0, 3,"Key 2:   move to next variable");

		PrintString (0, 5,"Key +:   inc variable");
		PrintString (0, 6,"Key -:   dec variable");

		PrintString (0, 8,"Key 0:   EXIT");
		PrintString (0, 10,"Key 5:   Thrust Data");
		PrintString (0, 11,"Key 6:   Lift Limited Data");
		PrintString (0, 12,"Key 7:   Min/Max Ps");
		PrintString (0, 13,"Key 8:   Ps data");
		PrintString (0, 14,"Key 9:   General Data");
		PrintString (0, 16,"Key 3:   Send data to file");

	}
//		while (!Exit)
//		{

			PrintString (0, 21, "                                                                                ");
			PrintString (Selec * 11, 21, "***********");

			PrintVar (0, 20, "Cdo %.4f   ", MainPlaneList->Cdo);
			PrintVar (11, 20, "k %.4f   ", MainPlaneList->k);

			PrintVar (22, 20, "p0 %.0f   ", EngineList->p0);
			PrintVar (33, 20, "T0 %.0f   ", EngineList->T100);
//DeadCode CSB 17/11/98				PrintVar (44, 20, "Mck %.3f   ", EngineList->ChokeMach);
			PrintVar (55, 20, "Mass %.0f   ", (FP)(Mass * 0.01));
			PrintVar (66, 20, "Height %.0f   ", (FP)(Height));

			Inc = FALSE;
			Dec = FALSE;

			if (Key_Tests.KeyPress3d (RPM_UP))
			{
				Inc = TRUE;
				delay2 = 100;
			}
			if (Key_Tests.KeyPress3d (RPM_DOWN))
			{
				Dec = TRUE;
				delay2 = 100;
			}

			switch (Selec)
			{
				case 0:
					if (Inc) MainPlaneList->Cdo += 0.0001;
					if (Dec) MainPlaneList->Cdo -= 0.0001;
					break;

				case 1:
					if (Inc) MainPlaneList->k += 0.001;
					if (Dec) MainPlaneList->k -= 0.001;
					break;

				case 2:
					if (Inc) EngineList->p0 += 100;
					if (Dec) EngineList->p0 -= 100;
					break;

				case 3:
					if (Inc) EngineList->T100 += 100;
					if (Dec) EngineList->T100 -= 100;
					break;

//DeadCode CSB 17/11/98					case 4:
//DeadCode CSB 17/11/98						if (Inc) EngineList->ChokeMach += 0.001;
//DeadCode CSB 17/11/98						if (Dec) EngineList->ChokeMach -= 0.001;
//DeadCode CSB 17/11/98						break;

				case 5:
					if (Inc) Mass += 1000;
					if (Dec) Mass -= 1000;

//					if (Mass < MinMass) Mass = MinMass;
//					if (Mass > MaxMass) Mass = MaxMass;

					break;
				case 6:
					if (Inc) 
						Height += 1000;
					if (Dec) 
						Height -= 1000;

					if (Height > 60000)
						Height = 60000;
					if (Height < 0)
						Height = 0;
					ClrDogHouseData(Height);
					break;

			}
			
			if (Key_Tests.KeyPress3d (RPM_10))
			{
				Selec--;
				delay = 250;
			}
			if (Key_Tests.KeyPress3d (RPM_20))
			{
				Selec++;
				delay = 250;
			}

			if (Selec == -1) Selec = 6;
			if (Selec == 7) Selec = 0;

			if (Key_Tests.KeyPress3d (RPM_00)) Exit = TRUE;

			if (Key_Tests.KeyPress3d (RPM_80))
			{
				Mono_Text.ClsMono();
				EmitDoghouseData (ControlledAC,Height);
			}else if (Key_Tests.KeyPress3d (RPM_70))
			{
				Mono_Text.ClsMono();
				EmitDoghouseData2 (ControlledAC,Height);			//max/min mach for a set of Ps
			}else if (Key_Tests.KeyPress3d (RPM_60))
			{
				Mono_Text.ClsMono();
				EmitLiftLimitedData (Height);
			}else if (Key_Tests.KeyPress3d (RPM_50))
			{
				Mono_Text.ClsMono();
				EmitThrustData (ControlledAC,Height);
			}else if (Key_Tests.KeyPress3d (RPM_90))
			{
				Mono_Text.ClsMono();
				EmitPsData (ControlledAC,Height);
			}else if (Key_Tests.KeyPress3d (RPM_30))
			{
				PrintDogHouseData(ControlledAC,Height);
			}

//		} 
}
void Model::PrintDogHouseData(AirStrucPtr const ControlledAC, FP Height)
{
	FILE* PFile = NULL;
	char name[50];
	char printname[50];
	char buffer[50];
	if (Type == AT_F86A)
	{
		strcpy(name,"f86a_");
		strcpy(printname,"F86A");
	}
	else if (Type == AT_F86E)
	{
		strcpy(name,"f86e_");
		strcpy(printname,"F86E");
	}
	else if (Type == AT_F86F)
	{
		strcpy(name,"f86f_");
		strcpy(printname,"F86F");
	}
	else if (Type == AT_F80C)
	{
		strcpy(name,"f80c_");
		strcpy(printname,"F80C");
	}
	else  if (Type == AT_F84E)
	{
		strcpy(name,"f84e_");
		strcpy(printname,"F84E");
	}
	else if (Type == AT_F51D)
	{
		strcpy(name,"f51d_");
		strcpy(printname,"F51D");
	}
	else if (Type == AT_MIG15)
	{
		strcpy(name,"m15_");
		strcpy(printname,"MiG 15");
	}
	else  if (Type == AT_MIG15BIS)
	{
		strcpy(name,"m15b_");
		strcpy(printname,"MiG 15bis");
	}
	else
	{
		strcpy(name,"dgh");
		strcpy(printname,"Unknown");

	}
	
	_itoa(doghousedata.alt/1000, buffer, 10);
	strcat(name,buffer);
	strcat(name,".dat");
//	PFile = fopen ("dghdata.dat", "wt");
	PFile = fopen (name, "wt");
	if (PFile != NULL)
	{
		Mono_Text.ClsMono();
		EmitDoghouseData (ControlledAC,Height);
		Mono_Text.ClsMono();
		EmitLiftLimitedData (Height);
		EmitThrustData (ControlledAC,Height);

		Mono_Text.ClsMono();
		EmitPsData (ControlledAC,Height);
		Mono_Text.ClsMono();
		EmitDoghouseData2 (ControlledAC,Height);			//max/min mach for a set of Ps


		CalibCalcThrust (ControlledAC, Height, 0, 0, doghousedata.thrust);
		 

		fprintf (PFile, "Aircraft Type:\t %s\n", printname);
		fprintf (PFile, "Altitude, ft:\t %.0f\t", doghousedata.alt);
		fprintf (PFile, "\n\n");
		fprintf (PFile, "Wing Area, m^2:\t\t\t %.2f\n",MainPlaneList->Area * 0.0001);
		fprintf (PFile, "Mass, kg:\t\t\t\t %.0f\n",doghousedata.mass);
		fprintf (PFile, "Thrust at alt, N:\t\t %.2f\n",doghousedata.thrust);
		fprintf (PFile, "Thrust/Weight ratio:\t\t%.3f\n",doghousedata.thrust/(doghousedata.mass * 9.81));
		fprintf (PFile, "WingLoading, N/m^2:\t\t %.1f\n",doghousedata.mass * 9.81 /(MainPlaneList->Area * 0.0001));
		fprintf (PFile, "\n");
//general data
		fprintf (PFile, "Stall speed, mph:\t %.0f\n", doghousedata.stallspd);
		fprintf (PFile, "Mach\t\t\t\t %.3f\n", doghousedata.stallmach);
		fprintf (PFile, "Max speed, mph\t\t %.0f\n", doghousedata.maxspd);
		fprintf (PFile, "Max mach\t\t\t %.3f\n", doghousedata.maxmachSL);
		fprintf (PFile, "Max Ps\t\t\t\t %.0f\n", doghousedata.maxPs);
		fprintf (PFile, "Mach at max mach\t %.3f\n\n", doghousedata.machatmaxPs);
		fprintf (PFile, "Ceiling, ft\t %.0f\n\n", doghousedata.ceiling);

//vel vs Ps
		fprintf (PFile, "Turnrate(deg/s) against Mach for a range of Ps values(ft/s)\n");
		fprintf (PFile, "Ps\t");
		for (UWord i=0;i<PSRANGE;i++)
		{
			if (FirstPs+i*PsStep < -50)
				fprintf (PFile, "%.0f\t",FirstPs+i*PsStep);
			else
				fprintf (PFile, "%.0f\t\t",FirstPs+i*PsStep);
		}
		fprintf (PFile, "\n");
		fprintf (PFile, "Mach Range: %.3f - %.3f, step %.3f\n",
				FirstMach,LastMach, MachStep);

		for (UWord j=0;j<MACHRANGE;j++)
		{
//print mach			fprintf (PFile, "%.3f\t\t",FirstMach + j * MachStep);
			for (i=0;i<PSRANGE;i++)
			{
//				if (doghousedata.turndata[i].rate[j] >= 10)
					fprintf (PFile, "%.3f\t",doghousedata.turndata[i].rate[j]);
//				else
//					fprintf (PFile, "%.1f\t\t",doghousedata.turndata[i].rate[j]);

			}
			fprintf (PFile, "\n");
		}
		fprintf (PFile, "\n\n");
//Lift Limited Data
		fprintf (PFile, "Turnrate at maximum lift for a range of Mach\n");

		fprintf (PFile, "Mach Range: %.3f - %.3f, step %.3f\n",LLFirstMach ,
													LLLastMach, LLMachStep);
		fprintf (PFile, "Turnrate(degrees/sec)\n");

		for (j=0;j<LIFTLIMITRANGE;j++)
		{
			
//print mach			fprintf (PFile, "%.3f\t\t",LLFirstMach + j * LLMachStep);
			fprintf (PFile, "%.3f\t",doghousedata.liftlimit[j]);
			fprintf (PFile, "\n");
		}
			fprintf (PFile, "\n");
//minmach and maxmach for a range of Ps
		fprintf (PFile, "minmach and maxmach for a range of Ps\n");
		fprintf (PFile, "Ps\tmin Mach\tmax Mach\n");
		for (i=0;i<PSRANGE;i++)
		{
			if ((FirstPs + i*PsStep) < -50)
				fprintf (PFile, "%.0f\t%.3f\t%.3f\t\n",FirstPs + i*PsStep, doghousedata.minmach[i], doghousedata.maxmach[i]);
			else
				fprintf (PFile, "%.0f\t\t%.3f\t%.3f\t\n",FirstPs + i*PsStep, doghousedata.minmach[i], doghousedata.maxmach[i]);
		}
//thrust data only printed for Height  == 0
		fprintf (PFile, "\n");
		fprintf (PFile, "\n");

		if (Height == 0 )
		{
			for (ULong alt = 0; alt <= 10; alt++ )
			{
				FP height = alt * 5000;
				fprintf (PFile, "Height: \t%.0f\n",height);
				fprintf (PFile, "For mach 0 to 1.3 in 0.1 steps\n\n");
				for (ULong mach = 0; mach <= 13; mach += 1)
				{
					fprintf (PFile, "%.0f\n",doghousedata.thrustatvel[alt].thrust[mach]);
				}
			}
			fprintf (PFile, "\n");
			fprintf (PFile, "time to 16400ft, mins: %.2f\n",doghousedata.timeto16400);
			fprintf (PFile, "time to 20000ft, mins: %.2f\n",doghousedata.timeto20000);
			fprintf (PFile, "time to 30000ft, mins: %.2f\n",doghousedata.timeto30000);
			fprintf (PFile, "time to 32800ft, mins: %.2f\n",doghousedata.timeto32800);
			fprintf (PFile, "time to 40000ft, mins: %.2f\n",doghousedata.timeto40000);


		}

		fclose (PFile);
	}
}
void Model::ClrDogHouseData(FP Height)
{
	doghousedata.alt = Height;
	for (UWord i=0;i<PSRANGE;i++)
	{
		doghousedata.turndata[i].Ps = 0;
			for (UWord j=0;j<MACHRANGE;j++)
			{
				doghousedata.turndata[i].rate[j] = 0;
			}
	}
	
}
void Model::EmitPsData (AirStrucPtr const ControlledAC,FP currheight)
{
	// calc max speeds, ceiling, best climb speed and best climb rate

	FP Height;		//feet

//	FILE* PFile = NULL;
//	Bool PrintToFile;
//	PFile = fopen ("psdata.dat", "wt");
//	if (PFile == NULL) PrintToFile = FALSE;
//	else PrintToFile = TRUE;

	FP Mach, cMach, maxMach;
	FP Ceiling; // feet
	FP Vel, cVel;
	FP Ps;

	maxMach = 0.5;

	ULong y;

	Mono_Text.ClsMono();
	FindCeiling (ControlledAC,Ceiling, cMach, cVel);
	PrintVar (65, 2, "  C = %.0f", Ceiling);

	y = 1;
//	PrintString (0, 0, "Height      ft      Mach      Vel        Ps          MaxMach    Vel");
	PrintString (0, 0, "Height    Mach(0Ps)   Vel     MaxPs    MaxPsMach   Vel       SEP");

#ifndef SETSIMPLEMOVECODE

	for (Height = 0; Height < Ceiling; Height += 5000)
	{
		FP temp, pres, dens;
		MMC.Sky.Ambient (Height * 30.48, dens, temp, pres);

		PrintVar (0, y, "%.0f", Height);
//		if (PrintToFile) fprintf (PFile, "%.0f\t", Height);

  		FindFastestZeroPs (ControlledAC,Height, Mach, Vel);

		PrintVar (10, y, "%.3f", Mach);
		PrintVar (20, y, "%.2f", (FP)(Vel * 2.25));
		if (Height == currheight)
		{
			doghousedata.maxspd = Vel * 2.25;
			doghousedata.maxmachSL = Mach;
		}
//		if (PrintToFile) fprintf (PFile, "%.3f\t", Mach);
//		if (PrintToFile) fprintf (PFile, "%.2f\t", Vel * 2.25);

		FindMaxPs (ControlledAC,Height, maxMach, Vel, Ps);

		PrintVar (30, y, "%.2f", (FP)(Ps * 3.2808));
		PrintVar (40, y, "%.3f", maxMach);
		PrintVar (50, y, "%.0f", (FP)(Vel * 2.25));
//		PrintVar (60, y, "%.0f", CalcAngle(Vel, Ps) * 65536 / F2PIE);
		if (Height == currheight)
		{
			doghousedata.maxPs = Ps * 3.2808;
			doghousedata.machatmaxPs = maxMach;
		}
//		if (PrintToFile) fprintf (PFile, "%.2f\t", Ps * 3.281);
//		if (PrintToFile) fprintf (PFile, "%.3f\t", maxMach);
//		if (PrintToFile) fprintf (PFile, "%.2f\t", Vel * 2.25);

//DeadCode CSB 19/11/98			PrintVar (60, y, "%.2f", FSqrt (dens / 0.0001225) * Vel * 2.25 * 0.89);
//		if (PrintToFile) fprintf (PFile, "%.2f\n", FSqrt (dens / Sky.SeaLevelDensity) * Vel * 2.25 * 0.89);

		y++;

	}
#endif

#ifdef SETSIMPLEMOVECODE

	FILE* file = NULL;

	file = fopen ("Calib_SM.txt", "wt");
	
	for (Height = 0; Height < Ceiling; Height += (1000 * 3.2808))//1000 m
	{
		FP temp, pres, dens;
		MMC.Sky.Ambient (Height * 30.48, dens, temp, pres);

		PrintVar (0, y, "%.0f", (FP)(Height / 3.2808));

  		FindFastestZeroPs (ControlledAC,Height, Mach, Vel);

		PrintVar (10, y, "%.3f", Mach);
		PrintVar (20, y, "%.0f", Vel * 10);//2.25);
		fprintf (file, "MaxVel:	 %.0f ", Vel * 10);

		FindMaxPs (ControlledAC,Height, maxMach, Vel, Ps);

		PrintVar (30, y, "%.2f", Ps);
		PrintVar (40, y, "%.3f", maxMach);
		PrintVar (50, y, "%.0f", Vel * 10);
		PrintVar (60, y, "%.0f", (FP)(CalcAngle(Vel, Ps) * 65536 / F2PIE));

		fprintf (file, "     BestClimbVel:	%.0f ", Vel * 10);
		fprintf (file, "     BestClimbAng:  %.0f\n", CalcAngle(Vel, Ps) * 65536 / F2PIE);

		y++;

	}
	fclose (file);

#endif


	for (ULong n=0; n < 5; n++)
	PrintString (0, y+n, "                                                                                ");

	y++;

	PrintVar (0, y, "%.0f", Ceiling);
	PrintVar (10, y, "%.3f", cMach);
	PrintVar (20, y, "%.2f", (FP)(cVel * 2.25));
	doghousedata.ceiling = Ceiling;
//	if (PrintToFile)
//	{
//		fclose (PFile);
//		PrintToFile = FALSE;
//	}

			
}

#endif


#ifdef EMIT_DOGHOUSE_DATA
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmitDoghouseData2
//Author		Andrew McRae
//Date			Mon 16 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::EmitDoghouseData2 (AirStrucPtr const ControlledAC,FP Height)
{

//	FILE* PFile = NULL;
//	Bool PrintToFile;
//	PFile = fopen ("dghdata2.dat", "wt");
//	if (PFile == NULL) PrintToFile = FALSE;
//	else PrintToFile = TRUE;

	PrintString (0, 0, "Ps,f/s    Min Mach   Max Mach");
	FP Ps = 0;
	FP n, TurnRate, MaxMach, MinMach, v ;
	ULong y =1;

	for (Ps = FirstPs; Ps <= LastPs; Ps += PsStep)
	{
		PrintVar (0, y, "%.0f", Ps);
//		if (PrintToFile) fprintf (PFile, "%.0f\t", Ps);
		int psstep;
		psstep = (Ps - FirstPs)/PsStep;

		FindSlowestAtPsReq (ControlledAC,Height, MinMach, v, Ps);
		PrintVar (12, y, "%.3f", MinMach);
		doghousedata.minmach[psstep] = MinMach;
//		if (PrintToFile) fprintf (PFile, "%.3f\t", MaxMach);

		FindFastestAtPsReq (ControlledAC,Height, MaxMach, v, Ps);
		PrintVar (24, y, "%.3f", MaxMach);
		doghousedata.maxmach[psstep] = MaxMach;
//		if (PrintToFile) fprintf (PFile, "%.3f\n", MaxMach);

		y++;

	}

//	if (PrintToFile)
//	{
//		fclose (PFile);
//		PrintToFile = FALSE;
//	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmitThrustData
//Author		
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::EmitThrustData (AirStrucPtr const ControlledAC,FP Height)
{

	
	PrintString (0, 0, "Thrust Data: Thrust v Vel");
	PrintString (0, 1, " V=0.0  0.1   0.2   0.3   0.4   0.5   0.6   0.7   0.8   0.9   1.0   1.1   1.2  1.3");

	ULong x = 0;
	FP MachNo;
	FP Thrust;
	int mach;
	for (ULong alt = 0; alt <= 10; alt++ )
	{
//	for (MachNo = FirstMach; MachNo <= (LLLastMach + LLMachStep/10); MachNo += LLMachStep)
		Height = alt * 5000;
			// Calc AirSpeed
		FP temp, pres, dens;
		MMC.Sky.Ambient (Height * 30.48, dens, temp, pres);
		FP Vel;

		AmbDensity = dens; // for engine calc

		for (mach = 0; mach <= 13; mach += 1)
		{
			MachNo = mach;
			MachNo = MachNo/10;
			Vel = (FSqrt (1.4 * 287 * temp)) * MachNo;
	
			CalibCalcThrust (ControlledAC, Height, MachNo, Vel, Thrust);
			if (Thrust < 0)
				Thrust = 0;
			PrintVar (1 + 6*x, 2 + alt, "%.0f", Thrust);
			x++;
			doghousedata.thrustatvel[alt].thrust       [mach] = Thrust;
		}
	}
	FP height = 1000;
	FP Ps;
	FP Mach;
	FP Vel;
	FP SumPs = 0;
	int cnt = 1;
	FP cr, dcr;

	while (height <= 40000)
	{
		FindMaxPs (ControlledAC,height-500, Mach, Vel, Ps);
		SumPs += Ps;
		if (height == 20000)
		{
			cr = 60 * 3.281 * SumPs / (cnt);
			doghousedata.timeto20000 = height/cr;
		}
		if (height == 30000)
		{
			cr = 60 * 3.281 * SumPs / (cnt);
			doghousedata.timeto30000 = height/cr;
		}
		if (height == 40000)
		{
			cr = 60 * 3.281 * SumPs / (cnt);
			doghousedata.timeto40000 = height/cr;
		}

		if (height == 32000)
		{
			cr = 60 * 3.281 * SumPs / (cnt);
			dcr  = 3.281 * Ps *60;
			doghousedata.timeto32800 = height/cr + 800/dcr ;
		}
		if (height == 16000)
		{
			cr = 60 * 3.281 * SumPs / cnt;
			dcr  = 3.281 * Ps * 60;
			doghousedata.timeto16400 = height/cr + 400/dcr ;
		}

		height += 1000;
		cnt++;
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmitLiftLimitedData
//Author		Andrew McRae
//Date			Mon 16 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::EmitLiftLimitedData (FP Height)
{
//	FILE* PFile = NULL;
//	Bool PrintToFile;
//	PFile = fopen ("liftlim.dat", "wt");
//	if (PFile == NULL) PrintToFile = FALSE;
//	else PrintToFile = TRUE;
	
	PrintString (0, 0, "Lift Limited Data: TurnRate v Vel");
	PrintString (0, 1, "V=0.05  0.1   0.15  0.2   0.25  0.3   0.35  0.4   0.45  0.5   0.55  0.6");
//	if (PrintToFile) fprintf (PFile, ""V=0.05  0.1   0.15  0.2   0.25  0.3   0.35  0.4   0.45  0.5   0.55  0.6"\n");
	FP n, TurnRate, MachNo, v ;

		ULong x = 0, cnt = 1;
		for (MachNo = LLFirstMach; MachNo <= (LLLastMach + LLMachStep/10); MachNo += LLMachStep)
		{
			CalcnAtMaxLift(Height, MachNo, v, n);
			if (n < 1)
				TurnRate = 0;
			else
				CalcTurnRate(n, v, TurnRate);
			if ((cnt % 2) == 0)
			{
				PrintVar (2 + 6*x, 2, "%.1f", TurnRate);
				x++;
			}
			cnt++;
			int mstep = LLMachStep/10 + (MachNo - LLFirstMach)/LLMachStep;
			doghousedata.liftlimit[mstep] = TurnRate;
//			if (PrintToFile) fprintf (PFile, "%.1f\t", TurnRate);

		}

	CalcStallSpeed (Height, MachNo, v);
	PrintVar (2 , 4, "Stall speed %.2f", v);
	PrintVar (2 , 5, "Stall Mach %.4f", MachNo);
	doghousedata.stallspd = v * 3600 /(5280 * 0.3048);
	doghousedata.stallmach = MachNo;

//	if (PrintToFile)
//	{
//		fclose (PFile);
//		PrintToFile = FALSE;
//	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmitDoghouseData
//Author		Andrew McRae
//Date			Mon 16 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::EmitDoghouseData (AirStrucPtr const ControlledAC,FP Height)
{
//	FILE* PFile = NULL;
//	Bool PrintToFile;
//	PFile = fopen ("dghdata.dat", "wt");
//	if (PFile == NULL) PrintToFile = FALSE;
//	else PrintToFile = TRUE;
	
	PrintString (0, 0, "Ps,f/s V=0.1 0.2   0.3   0.4   0.5   0.6   0.7   0.8   0.9   1.0   1.1   1.2");
	FP Ps = 0;
//	, FirstPs = -100, LastPs = 100, PsStep = 50;
	FP n, TurnRate, MachNo, v; 
	ULong y =1;
	
	for (Ps = FirstPs; Ps <= LastPs; Ps += PsStep)
	{
		int psstep;
		psstep = (Ps - FirstPs)/PsStep;
		doghousedata.turndata[psstep].Ps = Ps;

		PrintVar (0, y, "%.0f", Ps);
		ULong x = 0,cnt = 1;
//cnt is aclumsy attempt to only print on screen at ).1 intervals starting at 0.1
		for (MachNo = FirstMach; MachNo <= LastMach; MachNo += MachStep)
		{
			CalcnAtPs(ControlledAC,Height, MachNo, v, Ps , n);
			if (n == 0)
				TurnRate = 0;
			else
				CalcTurnRate(n, v, TurnRate);
			if ((cnt % 4) == 0)
			{
				PrintVar (6 + 6*x, y, "%.1f", TurnRate);
				x++;
			}
			cnt++;
			int mstep;
			mstep = MachStep/10 + (MachNo- FirstMach)/MachStep;
			doghousedata.turndata[psstep].rate[mstep] = TurnRate;
//			if (PrintToFile) fprintf (PFile, "%.1f\t", TurnRate);
		}
		y++;

	}

//	if (PrintToFile)
//	{
//		fclose (PFile);
//		PrintToFile = FALSE;
//	}

}

#endif


#ifdef PS_CALCS

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcPs
//Author		Andrew McRae
//Date			Thu 23 Oct 1997
//
//Description	Calculates Specific Power
//
//Inputs		Height (feet), Mach no.
//
//Returns		Vel, Ps
//
//------------------------------------------------------------------------------
Bool Model::CalcPs (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP& Vel, FP& Ps)
{
	PrintVar(65,0,"  H = %.0f     ",Height);
	PrintVar(65,1,"  M = %.3f     ",Mach);

	// Height is in feet

	FP Area;
	FP CL,CD,aoa;
	FP Drag,Weight;
	FP Thrust;

	// Calc AirSpeed
	FP temp, pres, dens;

	MMC.Sky.Temp0	 = 288.15;
	MMC.Sky.Density0 = 0.0001225;
	MMC.Sky.Ambient (Height * 30.48, dens, temp, pres);

	AmbDensity = dens; // for engine calc
	AmbTemp	   = temp; // for engine calc
	AmbPres    = pres; // for engine calc

	dens *= 10000;
	pres *= 10000;
	Vel = (FSqrt (1.4 * 287 * temp)) * Mach;

	// Calc CL
	FP mass = Mass * 0.01;

	doghousedata.mass = mass;

	Area = MainPlaneList->Area * 0.0001;

	FP wCL = (mass * 9.80655) / (0.5 * dens * Vel * Vel * Area);

	CL = wCL;

//This will not work because GetIndex have been modified and will not necessarily return the correct Aoa value
//DeadCode CSB 07/01/99		// Calc aoa
//DeadCode CSB 07/01/99		if (!MainPlaneList->pClCurve->GetIndex (CL, aoa))
//DeadCode CSB 07/01/99		{
//DeadCode CSB 07/01/99			CL = 0;
//DeadCode CSB 07/01/99			MainPlaneList->pClCurve->GetMaxValue (CL, aoa);
//DeadCode CSB 07/01/99		}


	if (!MainPlaneList->pClCurve->GetClIndex (CL, aoa))
	{
		CL = 0;
		MainPlaneList->pClCurve->GetMaxValue (CL, aoa);
	}

	if (wCL != CL) 
	{
		Ps = -9999;
		return FALSE;
	}

	// Calc CD

	if ((aoa > MainPlaneList->AoaMin) && (aoa < (MainPlaneList->AoaMax)))
	{
		FP CD0  = MainPlaneList->Cdo * MainPlaneList->pCompCd0Curve->GetValue (Mach);
		FP KCL2 = MainPlaneList->k * CL * CL * MainPlaneList->pCompKCurve->GetValue (Mach);
		CD = CD0 + KCL2;
	}
	else
	{
		FP CD0  = MainPlaneList->Cdo;
		FP KCL2 = MainPlaneList->pCdCurve->GetValue (aoa) - CD0;
		
		CD0  *= MainPlaneList->pCompCd0Curve->GetValue (Mach);
		KCL2 *= MainPlaneList->pCompKCurve->GetValue (Mach);

		CD = CD0 + KCL2;
	}

	// Calc Drag
	Drag = CD * 0.5 * dens * Vel * Vel * Area;

	CalibCalcThrust (ControlledAC, Height, Mach, Vel, Thrust);
	doghousedata.thrust = Thrust;
	// Calc Ps

	Ps = ((Thrust - Drag) * Vel) / (mass * 9.80655);

	return TRUE;

}
void Model::CalcTurnRate(FP n, FP Vel, FP& TurnRate)
{
	if (n > 1)
		TurnRate = 57.3 * 9.80655 * FSqrt(n*n - 1) / Vel;
	else
		TurnRate = 0;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcnAtMaxLift
//Author		RDH
//Date			
//
//Description	
//
//Inputs		Height (feet), Mach no.
//
//Returns		Vel, Ps
//
//------------------------------------------------------------------------------
void Model::CalcnAtMaxLift (FP Height, FP Mach, FP& Vel,FP& n)
{
	// Height is in feet

	FP Area;
	FP CL,CD,aoa;
	FP Drag,Weight;
	FP Thrust;

	// Calc AirSpeed
	FP temp, pres, dens;
	MMC.Sky.Ambient (Height * 30.48, dens, temp, pres);

	AmbDensity = dens; // for engine calc

	dens *= 10000;
	pres *= 10000;
	Vel = (FSqrt (1.4 * 287 * temp)) * Mach;

	// Calc CL
	FP mass = 0;
//	PMASSPOINT pMassPoint = MassList;
//	while (pMassPoint != NULL)
//	{
//		mass += (pMassPoint->Mass * 0.01);
//		pMassPoint = pMassPoint->List.NextItem ();
//	}
//	
	mass = Mass * 0.01;

	Area = MainPlaneList->Area * 0.0001;

	CL = MainPlaneList->pClCurve->GetValue (MainPlaneList->AoaMax);

	n = (dens * Vel * Vel * Area * CL) / (2 * mass * 9.80655);

	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcStallSpeed
//Author		RDH
//Date			
//
//Description	
//
//Inputs		Height (feet), Mach no.
//
//Returns		Vel, Ps
//
//------------------------------------------------------------------------------
void Model::CalcStallSpeed (FP Height, FP& Mach, FP& Vel)
{
	// Height is in feet

	FP Area;
	FP CL,CD,aoa;
	FP Drag,Weight;
	FP Thrust;

	// Calc AirSpeed
	FP temp, pres, dens;
	MMC.Sky.Ambient (Height * 30.48, dens, temp, pres);

	AmbDensity = dens; // for engine calc

	dens *= 10000;
	pres *= 10000;

	// Calc CL
	FP mass = 0;
//	PMASSPOINT pMassPoint = MassList;
//	while (pMassPoint != NULL)
//	{
//		mass += (pMassPoint->Mass * 0.01);
//		pMassPoint = pMassPoint->List.NextItem ();
//	}
	
	mass = Mass * 0.01;

	Area = MainPlaneList->Area * 0.0001;

	CL = MainPlaneList->pClCurve->GetValue (MainPlaneList->AoaMax);	// - MainPlaneList->buffetanglerange

	Vel = FSqrt ((2 * mass * 9.80655)/(dens * Area * CL));

	Mach = Vel/(FSqrt (1.4 * 287 * temp));

}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcnAtPs
//Author		RDH
//Date			
//
//Description	Calculates n (Load Factor) at a given Height, mach, also returns vel
//
//Inputs		Height (feet), Mach no.
//
//Returns		Vel, Ps
//
//------------------------------------------------------------------------------
void Model::CalcnAtPs (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP& Vel, FP& Ps, FP& n)
{


	// Height is in feet

	FP Area;
	FP CL,CD,aoa;
	FP Drag,Weight;
	FP Thrust;

	// Calc AirSpeed
	FP temp, pres, dens;
	MMC.Sky.Ambient (Height * 30.48, dens, temp, pres);

	AmbDensity = dens; // for engine calc

	dens *= 10000;
	pres *= 10000;
	Vel = (FSqrt (1.4 * 287 * temp)) * Mach;

	// Calc CL
	FP mass = 0;
//	PMASSPOINT pMassPoint = MassList;
//	while (pMassPoint != NULL)
//	{
//		mass += (pMassPoint->Mass * 0.01);
//		pMassPoint = pMassPoint->List.NextItem ();
//	}
	
	mass = Mass * 0.01;

	Area = MainPlaneList->Area * 0.0001;


	CalibCalcThrust (ControlledAC,Height, Mach, Vel, Thrust);


	Drag = Thrust - (mass * 9.80655 * Ps* 0.3048 /Vel);

	CD = Drag / (0.5 * dens * Vel * Vel * Area);

	FP Cd2 = CD;
	Cd2 -= MainPlaneList->Cdo * MainPlaneList->pCompCd0Curve->GetValue (Mach);
	Cd2 /= MainPlaneList->k * MainPlaneList->pCompKCurve->GetValue (Mach);

//DeadCode CSB 23/11/98		CD = CD/MainPlaneList->pCompCd0Curve->GetValue (Mach);
	CD = MainPlaneList->Cdo + MainPlaneList->k * Cd2;	//CSB 23/11/98	//Don't know if this is needed

	if ( CD > MainPlaneList->Cdo)
	{
//DeadCode CSB 23/11/98			CL = FSqrt((CD - MainPlaneList->Cdo)/MainPlaneList->k);
		CL = FSqrt(Cd2);
		n = CL * (dens * Vel * Vel * Area)/(2 * mass * 9.80655);
	}else
		n = 0;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalibCalcThrust
//Author		Andrew McRae
//Date			Sat 1 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalibCalcThrust (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP Vel, FP& Thrust)
{

	// Calc Thrust
	Inst.MachNo = Mach;
	ControlledAC->fly.thrustpercent = 100;
	AirVel.z = -Vel;
	AirSpeed =  Vel;
	Pos.y = Height * 30.48;

	MODEL_DT = 10;

	if (EngineList->Type == ET_JET)
		for(;;)
		{
			FP OldSpeedRpm = EngineList->SpeedRpm;
			EngineList->ProcessJetEngine (ControlledAC);
			FP dif = EngineList->SpeedRpm - OldSpeedRpm;
			if(dif < 0) dif *= -1;
			if(dif < 0.001) break;
		}

	if (EngineList->Type == ET_PISTON)
	{
		DesiredRPM = 3000;		//CSB 28/09/98
		EngineList->Speed   = 3.141;
		EngineList->PropInc = 45;
		MODEL_DT = 2;
		UWord n = 0;
		for (;;)
		{
			FP oldSpeed = EngineList->Speed;
			FP oldPropInc = EngineList->PropInc;
			EngineList->ProcessPistonEngine (ControlledAC);
			if(EngineList->Speed > 1.01 * DesiredRPM / 954.9296586) EngineList->Speed = 1.01 * DesiredRPM / 954.9296586;
			if(EngineList->Speed < 0.99 * DesiredRPM / 954.9296586) EngineList->Speed = 0.99 * DesiredRPM / 954.9296586;
			FP ENGRPMTEMP = EngineList->Speed * 954.9296586;
			PrintVar(65,2," RPM = %.0f  ",ENGRPMTEMP);
//DeadCode CSB 19/01/99				FP dif  = EngineList->Speed - oldSpeed;
			FP dif  = ENGRPMTEMP - DesiredRPM;
			FP dif2 = EngineList->PropInc - oldPropInc;
			if (dif  < 0) dif  = -dif;
			if (dif2 < 0) dif2 = -dif2;
			if ((dif < 0.1) && (dif2 < 0.01))break;
			n++;
			if(n > 1000)
			{
				EngineList->Thrust = 0;
				break;
			}

		}
	}

	Thrust = EngineList->Thrust;
	if(ControlledAC->fly.pModel->Type == AT_F82G)
		Thrust *= 2;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindPsSlope
//Author		Andrew McRae
//Date			Thu 23 Oct 1997
//
//Description	
//
//Inputs						
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Model::PsSlope (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP& Slope, FP& Ps)
{
	FP ps1, ps2;
	FP v;

//	Slope = -1000;
//	Ps = -100;

//	if (!CalcPs (Height, Mach - 0.0005, v, ps1)) return FALSE;
//	if (!CalcPs (Height, Mach + 0.0005, v, ps2)) return FALSE;

	CalcPs (ControlledAC,Height, Mach - 0.0005, v, ps1);
	CalcPs (ControlledAC,Height, Mach + 0.0005, v, ps2);

	Slope = (ps2 - ps1) * 1000;

	Ps = (ps1 + ps2) * 0.5;

	return TRUE;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindMaxPs
//Author		Andrew McRae
//Date			Thu 23 Oct 1997
//
//Description	iterates to find max Ps at a given Height
//
//Inputs		Height (feet)
//
//Returns		Mach No. & Vel
//
//------------------------------------------------------------------------------
Bool Model::FindMaxPs (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel, FP& Ps)
{


	FP m1 = 1.0;
	FP m2 = 0.0;	//1.0;	//CSB 28/09/98

	FP m;
	FP s;

	ULong c = 0;

	//This makes the code above obselete but hopefully should get the calib of piston planes right
//DeadCode CSB 17/11/98		if(ControlledAC->fly.pModel->EngineList->Type == ET_PISTON)
	{
		int maxPSstep = 1;
		FP  maxPS     = -999999;
		int stepn;
		for(stepn = 1; stepn <= 50; stepn++)
		{
			FP machno = 0.025 * stepn;		//Mach 0.025 - 1.25
			Bool CanFly = CalcPs (ControlledAC,Height, machno, Vel, Ps);
			if(!CanFly) Ps = -9999;
			
			if(Ps > maxPS)
			{
				maxPSstep = stepn;
				maxPS = Ps;
			}
			int breakpoint = 1;
		}

		m1 = 0.025 * (maxPSstep - 1);	//CSB 28/09/98
		m2 = 0.025 * (maxPSstep + 1);	//CSB 28/09/98
	}

	FP oldm1 = 0.01;
	FP oldm2 = 1.01;

	for (;;)
	{


		FP Ps1, Ps2;

		if(m1 != oldm1)	CalcPs (ControlledAC, Height, m1, Vel, Ps1);
		if(m2 != oldm2)	CalcPs (ControlledAC, Height, m2, Vel, Ps2);

		if(m2 - m1 < 0.001) break;

		oldm1 = m1;
		oldm2 = m2;

		if(Ps1 < Ps2) 
			m1 = (3 * m1 + m2) * 0.25;
		else
			m2 = (m1 + 3 * m2) * 0.25;

//DeadCode CSB 30/09/98			PsSlope (ControlledAC,Height, m, s, Ps);
//DeadCode CSB 30/09/98	
//DeadCode CSB 30/09/98			FP dm = m2 - m1;
//DeadCode CSB 30/09/98	
//DeadCode CSB 30/09/98			if (dm < 0.001) break;
//DeadCode CSB 30/09/98	
//DeadCode CSB 30/09/98			if (s < 0)
//DeadCode CSB 30/09/98				m2 = (m + m2) * 0.5;
//DeadCode CSB 30/09/98			else if (s > 0)
//DeadCode CSB 30/09/98				m1 = (m + m1) * 0.5;
		
//TempCode ARM 04Nov97 		PrintVar (0, 15, "FindMaxPS %ld    ", c);
//TempCode ARM 04Nov97 		PrintVar (0, 16, "Mach %.16f    ", m); 
//TempCode ARM 04Nov97 		PrintVar (0, 17, "Ps %.4f    ", Ps); 

//DeadCode CSB 30/09/98			c++;


	}
	
	m = (m1 + m2) * 0.5;

	Mach = m;

	CalcPs (ControlledAC,Height, Mach, Vel, Ps);

	if(Ps >= 0) return TRUE;
	else return FALSE;

	
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 	// ************
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 //	Mach = 0.7;
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 	ULong c = 0;
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 	for (;;)
//TempCode ARM 29Oct97 	{
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 		FP slope;
//TempCode ARM 29Oct97 		if (!PsSlope (Height, Mach, slope)) return FALSE;
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 		FP h = slope * 0.000001;
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 		Mach += h;
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 		if (slope < 0) slope = -slope;
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 		if (slope < 0.01) break;
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 		PrintVar (0, 15, "FindMaxPS %ld    ", c);
//TempCode ARM 29Oct97 		PrintVar (0, 16, "Mach %.16f    ", Mach); 
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 		c++;
//TempCode ARM 29Oct97 
//TempCode ARM 29Oct97 	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFastestZeroPs
//Author		Andrew McRae
//Date			Mon 27 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Model::FindFastestZeroPs (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel)
{
	if(EngineList->Type == ET_PISTON)
	{
		FP Ps, OldPs;
		FP OldM = 1;
		FP OldVel = 1;
		Ps = -9999;
		for(FP M = 1; M > 0; M -= 0.01)
		{
			OldPs = Ps;
			CalcPs (ControlledAC, Height, M, Vel, Ps);
			if(Ps > 0)
			{
				M = M + Ps / (Ps - OldPs) * (OldM - M);
				Vel = Vel + Ps / (Ps - OldPs) * (OldVel - Vel);
				Mach = M;
				return TRUE;
			}
			OldM = M;
			OldVel = Vel;
		}
		return FALSE;
	}
	else
	{
		FP dm = 0.01;
		FP Ps;

		Mach = 1.0;
	
		ULong c = 0;

		for (;;)
		{
		
			CalcPs (ControlledAC,Height, Mach, Vel, Ps);

			if (Mach <= 0) return FALSE;

			FP ps = Ps;

			if (ps < 0) ps = -ps;

			if (ps < 0.01) break;

			Mach -= dm;

			if (Ps > 0)
			{
				Mach += dm;
				Mach += dm;
				dm *= 0.5;
			}

			c++;
			if(c > 1000)
				return FALSE;
		}
	}

	return TRUE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFastestZeroPs
//Author		Andrew McRae
//Date			Mon 27 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Model::FindFastestAtPsReq (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel, FP PsReq)
{

	FP dm = 0.0078125;
	FP Ps;

	Mach = 1.5;

	ULong c = 0;

	for (;;)
	{

		CalcPs (ControlledAC,Height, Mach, Vel, Ps);

		Ps = Ps/0.3048;

		if (Mach <= 0) return FALSE;

		FP diff = Ps - PsReq;

		if ((diff) < 0)
			diff = -diff;

		if ((diff) < 0.001) 
			break;

		Mach -= dm;

		if ((Ps-PsReq) > 0)
		{
			Mach += dm;
			Mach += dm;
			dm *= 0.5;
		}

//TempCode ARM 04Nov97 		PrintVar (0, 1, "FindFastestZeroPS %ld    ", c);

		c++;

	}

	return TRUE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		Andrew McRae
//Date			Mon 27 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Model::FindSlowestAtPsReq (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel, FP PsReq)
{

	FP dm = 0.0078125;
	FP Ps;

	Mach = 0.0078125;

	ULong c = 0;

	for (;;)
	{

		CalcPs (ControlledAC,Height, Mach, Vel, Ps);

		Ps = Ps/0.3048;

		if (Mach >1.5) 
			return FALSE;

		FP diff = Ps - PsReq;

		if ((diff) < 0)
			diff = -diff;

		if ((diff) < 0.01) 
			break;

		Mach += dm;

		if ((Ps-PsReq) > 0)
		{
			Mach -= dm;
			Mach -= dm;
			dm *= 0.5;
		}

//TempCode ARM 04Nov97 		PrintVar (0, 1, "FindFastestZeroPS %ld    ", c);

		c++;
		if (c > 500)
			return FALSE;

	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindCeiling
//Author		Andrew McRae
//Date			Mon 27 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Model::FindCeiling (AirStrucPtr const ControlledAC,FP& Height, FP& Mach, FP& Vel)
{

	Height = 42000;
//DeadCode CSB 17/11/98		FP dHeight = 32768;//16384;
	FP Ps;

	Mach = 0.5;

	ULong c = 0;

	for (;;)
	{
		Bool CanFly = FindMaxPs (ControlledAC,Height, Mach, Vel, Ps);

		if (Height < 0) break;

		FP sPs = Ps - 0.508006177;				//Service Ceiling 
		if( (CanFly) && (sPs > -0.02) && (sPs < 0.02) )
			break;

//		if(sPs < 0) break;
//		else 
			Height += 100 * sPs;
//		Height += 10;
		c++;
		if(c > 25) break;
	}

	return TRUE;
}


#endif
