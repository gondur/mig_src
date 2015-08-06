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
//Filename       aerodev.cpp
//System         
//Author         Andrew McRae
//Date           Wed 13 Aug 1997
//Description    
//------------------------------------------------------------------------------


#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "ranges.h"
#include "myangles.h"
#include "monotxt.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AeroDevice
//Author		Andrew McRae
//Date			Wed 17 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AeroDevice::AeroDevice (
	AirStrucPtr const ControlledAC,
	PMODEL pmodel,		// parent flight model class
	DT_TYPE type,		// DT_xxxxx
	FP dcl,	  			// delta CL
	FP dcd,				// delta CD
	FP dcm,				// delta CM
	FP dalpha,			// delta Alpha
	SWord rate,			// movement rate
	KeyVal3D key,		// control key (0 if none)
	UByte* pAnimByte,	// anim byte address
	SLong	minval,		// used for auto surface animation
	SLong	maxval,		// surface anim....
	SLong Scale)		// anim scale

{
	pModel = pmodel;
	Type = type;

	Val = 0x0000;
 	Attractor = 0x0000;

	OldAttractor=0x0000;

	dCl = dcl;
	dCd = dcd;
	dCm = dcm;
	dAlpha = dalpha;

	Rate = rate;
	Key = key;

//	Dir = STATIONARY;

	scale = 1;
	scale /= 16384;

	List.Attach (&pModel->DeviceList, this);

	if (pAnimByte != NULL)
	{
		// Attach an MA_SURFACE
		//this is for an animation
		new MODELANIM (ControlledAC,MA_AEROSURFACE, pModel, &Val, pAnimByte, minval, maxval, Scale, FALSE);//RJS 20Jul98
	}

	if (Type == DT_GEAR)
	{
// 		Val = 0;
//		OldAttractor = Attractor = 0;

 		Val = 0x4000;
		OldAttractor = Attractor = 0x4000;


		AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
 		if (adptr)							//rdh
 			adptr->animtoggle = 255;

	}

	// Aero dev should have unique count for comms
	DeviceID = ControlledAC->fly.AeroDeviceCnt++;				//RJS 18Sep98
//DeadCode AMM 29Jun99 	pModel->UniqueID = ControlledAC->uniqueID.count;			//RJS 18Sep98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AeroDevice
//Author		Andrew McRae
//Date			Wed 17 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AeroDevice::~AeroDevice ()
{
	List.Detach (this);
}

void AeroDevice::GearUp ()
{
	if (Type == DT_GEAR)
	{
 		Val = 0;
		OldAttractor = Attractor = 0;
	}

}

void AeroDevice::GearDown ()
{
	if (Type == DT_GEAR)
	{
 		Val = 16384;
		OldAttractor = Attractor = 16384;

	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Process
//Author		Andrew McRae
//Date			Tue 12 Aug 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AeroDevice::Process ()
{
	FP frac;

	if (Val)
	{
		frac = (FP)Val * scale;//0.000061035;

		pModel->DeltaCl += (frac * dCl);
		pModel->DeltaCd += (frac * dCd);
		pModel->DeltaCm += (frac * dCm);
		pModel->DeltaAlpha += (frac * dAlpha);
	}

}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Action
//Author		Andrew McRae
//Date			Wed 13 Aug 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AeroDevice::Action (AirStrucPtr const ControlledAC, CONTROL_TYPE ctrl_type, Bool sendpacket)
{

	// exception test for slats

	if ((Type == DT_SLATS) && (Key == 0))
	{
		// auto slats;
		if (pModel->DynamicPressure < pModel->SlatOutPressure) Attractor = 0x4000;
		if (pModel->DynamicPressure > pModel->SlatInPressure) Attractor = 0x0000;
		return;
	}

	if (ctrl_type == CT_KEYS)
	{
		if (Key_Tests.KeyPress3d (Key))
		{
			if (Attractor != 0x4000) Attractor = 0x4000;
			else if (Attractor == 0x4000) Attractor = 0x0000;

		}
	}


	// for gear anim
	if (Type == DT_GEAR)
	{
		Bool OnGround = FALSE;
		PGEAR pGear = pModel->GearList;

		while (pGear != NULL)
		{
			if(pGear->LegPos != 0) OnGround = TRUE;
			pGear = pGear->List.NextItem ();
		}
		if(OnGround) return;
		pModel->Gear = FALSE;

//DeadCode RJS 29Apr98 		static SWord OldAttractor = Attractor;

		if (OldAttractor != Attractor)
		{
			OldAttractor = Attractor;
			pModel->Gear = TRUE;

			if(Attractor == 0x4000)
				SHAPE.NavigationLightsActive(ControlledAC, TRUE);
			else
				SHAPE.NavigationLightsActive(ControlledAC, FALSE);


// gear is handled in setgearanimpos for record and comms....

			// Log UniqueID (14 bits), DeviceID (8 bits)
		}

		if (Val < Attractor)
		{
			Val += Rate;
			if (Val > Attractor) Val = Attractor;
		}

		if (Val > Attractor)
		{
			Val -= Rate;
			if (Val < Attractor) Val = Attractor;
		}


	}
	else
	{
		if (OldAttractor != Attractor)
		{
			//Hydraulic sound effect...
 			if(pModel->Controlled)								//AMM 26Apr99
				_Miles.PlayOnce(FIL_SFX_FLAPS);					//AMM 26Apr99

			OldAttractor = Attractor;

			// Can we send, and is it the piloted AC?
			if (sendpacket && (pModel->Controlled == TRUE))
				_DPlay.NewAeroDevAction(DeviceID,Attractor);
			// Log UniqueID (14 bits), DeviceID (8 bits)
		}

		if (Val < Attractor)
		{
			Val += Rate;
			if (Val > Attractor) Val = Attractor;
		}

		if (Val > Attractor)
		{
			Val -= Rate;
			if (Val < Attractor) Val = Attractor;
		}
	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowerFlaps
//Author		Craig Beeston
//Date			Wed 21 Apr 1999
//
//Description	Lower the flaps
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::FlapsDown(AirStrucPtr const ControlledAC)
{
	PAERODEVICE pDevice = DeviceList;
	while (pDevice != NULL)
	{
		if( (pDevice->Type == 2/*DT_FLAPS*/) && (pDevice->Val < 16384) )
		{
			pDevice->Val += pDevice->Rate;
			if(pDevice->Val > 16384) pDevice->Val = 16384;
		
			PMODELANIM pModelAnim = AnimList;

 			if (ControlledAC)														//RJS 27May98
			{
 				while (pModelAnim != NULL)
 				{
//DEADCODE DAW 26/04/99 					pModelAnim->pAnim = (void*)(pModelAnim->pOffset + (ULong)(ControlledAC->Anim));
					pModelAnim->pAnim = (void*)&ControlledAC->Anim[(int)pModelAnim->pOffset]; //DAW 26/04/99
 					if(pModelAnim->Type == MA_AEROSURFACE)
 						pModelAnim->ProcAnimSurface ();

 					pModelAnim = pModelAnim->List.NextItem ();
 				}
			}
		}
		pDevice = pDevice->List.NextItem ();
	}
}


