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
//Filename       curves.cpp
//System         
//Author         Andrew McRae
//Date           Mon 10 Feb 1997
//Description    curve resource & curves
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include	<math.h>

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "curves.h"
#include "myerror.h"

CurveResource _CurveRsc;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CurveResource
//Author		Andrew McRae
//Date			Tue 11 Feb 1997
//
//Description	Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CurveResource::CurveResource ()
{
	pCurves = NULL;

	// load all curves for all aircraft
	LoadCurvesCOMM ();

	LoadCurvesF51D ();
	LoadCurvesF80C ();
	LoadCurvesF84E ();
	LoadCurvesF86E ();
	LoadCurvesMIG15 ();
	LoadCurvesYAK9 ();
//DeadCode CSB 28/04/99		LoadCurvesF82G ();
//TempCode ARM 03Nov97 	LoadCurvesF94A ();
//DeadCode CSB 28/04/99		LoadCurvesF9F2 ();
//DeadCode CSB 28/04/99		LoadCurvesF8 ();
//DeadCode CSB 28/04/99		LoadCurvesF4U5 ();
//DeadCode CSB 28/04/99		LoadCurvesSFURY ();
//DeadCode CSB 28/04/99		LoadCurvesFFLY ();
//DeadCode CSB 28/04/99		LoadCurvesA1 ();											//D 02Apr98

//DeadCode CSB 27/10/98		LoadCurvesATMOS ();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CurveResource
//Author		Andrew McRae
//Date			Tue 11 Feb 1997
//
//Description	destructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CurveResource::~CurveResource ()
{
	while (pCurves != NULL) delete pCurves;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindCurve
//Author		Andrew McRae
//Date			Mon 10 Feb 1997
//
//Description	Get pointer to curve
//
//Inputs		Aircraft & Curve Name
//
//Returns	
//
//------------------------------------------------------------------------------
PCURVE CurveResource::FindCurve (char* AircraftName, char* CurveName)
{

	PCURVE pCurve = pCurves;

	for (;;)
	{

		if (pCurve == NULL) break;

		if (!strncmp (AircraftName,
			pCurve->AircraftName,
			CURVEMIN(strlen(AircraftName),CURVENAMESIZE)))
		{
			if (!strncmp (CurveName,
				pCurve->CurveName,
				CURVEMIN(strlen(CurveName), CURVENAMESIZE)))
			{
				return pCurve;
			}
		}

		pCurve = pCurve->List.NextItem();
	}

#ifndef __CEDITOR__
	_Error.SayAndQuit ("Failed to Find Requested Curve %s %s", AircraftName, CurveName);
#endif

	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Curve
//Author		Andrew McRae
//Date			Thu 30 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Curve::Curve (char* aircraftname,
				char* curvename,
				ULong cVals,
				FP minindex,
				FP maxindex,
				UWord Type,
				PCURVEPNT pCurvePnt)

{
	ULong	n;

	CurveData = new CURVEPNT [cVals];

	for (n = 0; n<CURVENAMESIZE; n++) AircraftName [n] = 0;
	for (n = 0; n<CURVENAMESIZE; n++) CurveName [n] = 0;


#ifndef __CEDITOR__
	if (CurveData == NULL)
		_Error.SayAndQuit ("No Curve Memory %ld", cVals * sizeof(CURVEPNT));
#endif

	Active = TRUE;

	cPoints = cVals;

	MinIndex = minindex;
	MaxIndex = maxindex;

#ifndef __CEDITOR__
	if (MinIndex >= MaxIndex)
		_Error.SayAndQuit ("Curve MinIndex >= MaxIndex.");
#endif

	IndexType = Type;

	DeltaIndex = MaxIndex - MinIndex;

	iPoint = 0;

//	PCURVEPNT pCurveData = CurveData;

	for (n=0; n<cPoints; n++)
	{

		CurveData[n].index = pCurvePnt[n].index;
		CurveData[n].value = pCurvePnt[n].value;

	}

	strncpy (AircraftName, aircraftname, CURVEMIN(strlen(aircraftname),CURVENAMESIZE));
	strncpy (CurveName, curvename, CURVEMIN(strlen(curvename),CURVENAMESIZE));

	List.Attach (&_CurveRsc.pCurves, this);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Curve
//Author		Andrew McRae
//Date			Thu 30 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Curve::~Curve ()
{
	if (CurveData != NULL)
		delete CurveData;

	List.Detach (this);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetValue
//Author		Andrew McRae		Craig Beeston
//Date			Mon 27 Jan 1997		Mon 1 Mar 1999
//
//Description	
// 
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
FP Curve::GetValue (FP index)
{
	if (!Active)
		return(0);

	if( (index < MinIndex) || (index > MaxIndex) )
		switch (IndexType)
		{
			case IDT_WRAP:
			{
				while (index < MinIndex) index += DeltaIndex;
				while (index > MaxIndex) index -= DeltaIndex;
				break;
			}
			case IDT_LIMIT:
				if (index < MinIndex)	index = MinIndex;
				else					index = MaxIndex;
				break;
		}

	SWord c1, c2;
	FP    i1, i2;

	for(;;)
	{
		if(IndexType == IDT_WRAP)
		{
			c1 = cPoints - 1;
			c2 = 0;
			i1 = CurveData[c1].index;
			i2 = CurveData[c2].index;
			if( (index < i2) || (index >= i1) )
			{
				if(index > i1) index -= DeltaIndex;
				i1 -= DeltaIndex;
				break;
			}
		}
		FP HalfIndex = (MinIndex + MaxIndex) * 0.5;
		if(index < HalfIndex)
		{
			for(c2 = 1; c2 < cPoints; c2++)
				if(index < CurveData[c2].index)
				{
					c1 = c2 - 1;
					i1 = CurveData[c1].index;
					i2 = CurveData[c2].index;
					break;
				}
		}
		else
		{
			for(c1 = cPoints - 2; c1 >= 0; c1--)
				if(index > CurveData[c1].index)
				{
					c2 = c1 + 1;
					i1 = CurveData[c1].index;
					i2 = CurveData[c2].index;
					break;
				}
		}
		break;
	}	
	FP v1 = CurveData[c1].value;
	FP v2 = CurveData[c2].value;
	return(v1 + (v2 - v1) * (index - i1) / (i2 - i1) );
}

//DeadCode CSB 26/02/99		for (;;)
//DeadCode CSB 26/02/99		{
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99			// special cases
//DeadCode CSB 26/02/99			// should not occur in a IDT_LIMIT
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99			if (index < CurveData[0].index)
//DeadCode CSB 26/02/99			{
//DeadCode CSB 26/02/99				c1 = cPoints - 1;
//DeadCode CSB 26/02/99				c2 = 0;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99				i1 = CurveData[c1].index - DeltaIndex;
//DeadCode CSB 26/02/99				i2 = CurveData[c2].index;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99				break;
//DeadCode CSB 26/02/99			}
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99			if (index > CurveData[cPoints - 1].index)
//DeadCode CSB 26/02/99			{
//DeadCode CSB 26/02/99				c1 = cPoints - 1;
//DeadCode CSB 26/02/99				c2 = 0;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99				i1 = CurveData[c1].index;
//DeadCode CSB 26/02/99				i2 = CurveData[c2].index + DeltaIndex;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99				break;
//DeadCode CSB 26/02/99			}
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99			c2 = 1;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99			for (;;)
//DeadCode CSB 26/02/99			{
//DeadCode CSB 26/02/99				if (index <= CurveData[c2].index)
//DeadCode CSB 26/02/99					break;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99				c2++;
//DeadCode CSB 26/02/99			}
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99			c1 = c2 - 1;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99			i1 = CurveData[c1].index;
//DeadCode CSB 26/02/99			i2 = CurveData[c2].index;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99			break;
//DeadCode CSB 26/02/99		}
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99		FP v1,v2;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99		v1 = CurveData[c1].value;
//DeadCode CSB 26/02/99		v2 = CurveData[c2].value;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99		return (((index - i1) * (v2 - v1)) / (i2 - i1)) + v1;
//DeadCode CSB 26/02/99	
//DeadCode CSB 26/02/99	}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetIndex
//Author		Andrew McRae
//Date			Thu 23 Oct 1997
//
//Description	used for calibration only (slow)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Curve::GetIndex (FP value, FP& result)
{

	if (!Active) return FALSE;

	// test if an index exists

	ULong n;

	Bool TooBig = TRUE;
	Bool TooSmall = TRUE;

	PCURVEPNT pPoint = CurveData;
	for (n=0; n<cPoints; n++)
	{
		if (pPoint->value >= value) TooBig = FALSE;
		if (pPoint->value <= value) TooSmall = FALSE;

		pPoint++;
	}

	if (TooBig || TooSmall) return FALSE;


	// find first segment to fit value

//	PCURVEPNT p1 = CurveData + cPoints - 1;
//	PCURVEPNT p2 = CurveData;
	PCURVEPNT p1 = CurveData;
	PCURVEPNT p2 = CurveData + 1;

	for (n=0; n< cPoints - 1; n ++)
	{

		if ((p1->value <= value)
			&& (p2->value > value))
				break;

		if ((p1->value >= value)
			&& (p2->value < value))
				break;

		p1 ++;
		p2 ++;

		if (p1 == (CurveData + cPoints)) p1 = CurveData;
		if (p2 == (CurveData + cPoints)) p2 = CurveData;

	}

	if (n == (cPoints - 1)) return FALSE;

	FP v1 = p1->value;
	FP i1 = p1->index;

	pPoint++;

	FP v2 = p2->value;
	FP i2 = p2->index;

	if (i1 > FPIE) i1 -= F2PIE;
	if (i2 > FPIE) i2 -= F2PIE;

	result = i1 + (((value - v1) * (i2 - i1)) / (v2 - v1));

	return TRUE;
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetClIndex
//Author		Craig Beeston
//Date			Thu 7 Jan 1999
//
//Description	Used in Calib to find the Aoa for a given CL.  Only considers Aoa below stall
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Curve::GetClIndex (FP value, FP& result)
{
	if (!Active) return FALSE;

	PCURVEPNT pPoint = CurveData + cPoints - 1;
	FP OldValue = pPoint->value;
	pPoint--;

	for (;;)
	{
		if (pPoint->value > OldValue) break;
		OldValue = pPoint->value;
		pPoint--;
	}

	PCURVEPNT Pnt0, Pnt1;
	Pnt0 = pPoint + 1;

	for(;;)
	{
		if(Pnt0 >= (CurveData + cPoints - 1) ) Pnt0 = CurveData;
		Pnt1 = Pnt0 + 1;
		if(Pnt1 >= (CurveData + cPoints - 1) ) Pnt1 = CurveData;
	
		if(Pnt1->value < Pnt0->value) return FALSE;	//Stalls before reaching desired CL
		if( (value > Pnt0->value) && (value < Pnt1->value) ) break;

		Pnt0++;
	}

	FP Index0 = Pnt0->index;
	FP Index1 = Pnt1->index;

	if(Index0 > FPIE) Index0 -= F2PIE;
	if(Index1 > FPIE) Index1 -= F2PIE;

	result = Index0 + (Index1 - Index0) * (value - Pnt0->value) / (Pnt1->value - Pnt0->value);

	return TRUE;
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMaxValue
//Author		Andrew McRae
//Date			Tue 28 Oct 1997
//
//Description	
//
//Inputs		lower limit on value		
//
//Returns		max value, index of max value
//
//------------------------------------------------------------------------------
void Curve::GetMaxValue (FP& value, FP& index)
{
	PCURVEPNT pPoint = CurveData;

	for (ULong n=0; n<cPoints; n++)
	{
		if (pPoint->value >= value)
		{
			value = pPoint->value;
			index = pPoint->index;
		}
		pPoint++;
	}
}
