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
//Filename       modvec.cpp
//System         
//Author         Andrew McRae
//Date           Mon 6 Jan 1997
//Description    Flight Model Floating Point Vector Functions
//------------------------------------------------------------------------------


#include "dosdefs.h"
#include "modvec.h"
#include "mymath.h"

// ******************************************************
//
// Notes:
//
// double precisions floating point variables are used
// 8 bytes.
//
// Sign convention
// 
//	Translation
//
//		forward is	+Z
//		right is 	+X
//		up is		+Y
//
//	Rotation - Rowan ANGLES
//
//		1st	Heading (Y)	left handed
//		2nd	Pitch (X)	right handed
//		3rd	Roll (Z)	right handed
//
//	Rotation - Flight Model
//
//		+ve rotations are right handed screw along +ve axes
//		Angle units are in radians.
//
// UNITY is 1.0
//
// ******************************************************

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NullVec
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Nulls a vector
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void NullVec (FCRD& Vec)
{
	Vec.x = 0;
	Vec.y = 0;
	Vec.z = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NullVec
//Author		Craig Beeston
//Date			Thu 11 Feb 1999
//
//Description	Nulls a vector (long floats)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void NullVec (FCRDlong& Vec)
{
	Vec.x = 0;
	Vec.y = 0;
	Vec.z = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NullOri
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Nulls an orientation structure
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void NullOri (FORI& Ori)
{
	Ori.x.x = 0;
	Ori.x.y = 0;
	Ori.x.z = 0;
	Ori.y.x = 0;
	Ori.y.y = 0;
	Ori.y.z = 0;
	Ori.z.x = 0;
	Ori.z.y = 0;
	Ori.z.z = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyVec
//Author		Andrew McRae
//Date			Tue 14 Jan 1997
//
//Description	Copies a vector
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void CopyVec (FCRD& srce, FCRD& dest)
{
	dest.x = srce.x;
	dest.y = srce.y;
	dest.z = srce.z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyOri
//Author		Andrew McRae
//Date			Thu 16 Jan 1997
//
//Description	Copies an orientation structure
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void CopyOri (FORI& srce, FORI& dest)
{
	dest.x.x = srce.x.x;
	dest.x.y = srce.x.y;
	dest.x.z = srce.x.z;
	dest.y.x = srce.y.x;
	dest.y.y = srce.y.y;
	dest.y.z = srce.y.z;
	dest.z.x = srce.z.x;
	dest.z.y = srce.z.y;
	dest.z.z = srce.z.z;
}


// Angle Convertsion Functions
SWord Rads2Rowan (FP angle)
{
	SLong res = (SLong)(angle * 10430.37835047);
	return (SWord)(res & 0xffff);
}

FP Rads2Degs (FP angle)
{
	return (angle * 57.29577951);
}

SWord Degs2Rowan (FP angle)
{
	SLong res = (SLong)(angle * 182.04444444);
	return (SWord)(res & 0xffff);
}

FP Degs2Rads (FP angle)
{
	return (angle / 57.29577951);
}

FP Rowan2Rads (UWord angle)
{
	return ((FP)angle /  10430.37835047);
}

FP Rowan2Degs (UWord angle)
{
	return ((FP)angle /  182.04444444);
}

FP Rpm2RadsPerCSec (FP rpm)
{
	return rpm * 0.001047197;
}

SWord	RadPerCSec2RowanPerMin(FP	angle)
{
	SLong	rowpmin;

	rowpmin = angle * 62586880;			//rdh

	return (SWord)(rowpmin & 0xffff);
}
SWord	RadPerCSec2DegsPerMin(FP	angle)
{
	SLong	rowpmin;

	rowpmin = angle * 343800;			//rdh

	return (SWord)(rowpmin & 0xffff);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcAngle
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Calculates an angle in radians from 0 to 2pie
//
//Inputs		2D vector
//
//Returns		Angle
//
//------------------------------------------------------------------------------
FP CalcAngle (FP x, FP y)
{

	// \6|7/
	// 5\|/8 
	// -----
	// 4/|\1 
	// /3|2\

	FP a;

	if (y >= 0)
	{
		// 5,6,7,8
		if (x >= 0)
		{
			// 7,8
			if (y > x)
			{
				// 7
				a=FPATan (x,y);
				return F1PIE2 - a;
			}
			else
			{
				// 8
				a=FPATan (y,x);
				return a;
			}
		}
		else
		{
			// 5,6
			x = -x;

			if (y > x)
			{
				// 6
				a=FPATan (x,y);
				return F1PIE2 + a;
			}
			else
			{
				// 5
				a=FPATan (y,x);
				return FPIE - a;
			}

		}
	}
	else
	{
		// 1,2,3,4
		y = -y;

		if (x >= 0)
		{
			// 1,2
			if (y > x)
			{
				// 2
				a=FPATan (x,y);
				return F3PIE2 + a;
			}
			else
			{
				// 1
				a=FPATan (y,x);
				return F2PIE - a;
			}
		}
		else
		{
			// 3,4
			x = -x;

			if (y > x)
			{
				// 3
				a=FPATan (x,y);
				return F3PIE2 - a;
			}
			else
			{
				// 4
				a=FPATan (y,x);
				return FPIE + a;
			}
		}
	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VecLen2D
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	calcs length of a 2d vector
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
FP VecLen2D (FP x, FP y)
{
	return FSqrt ((x*x) + (y*y));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VecLen
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	calculates length of a vector
//
//Inputs		reference to an FCRD
//
//Returns		Fp length
//
//------------------------------------------------------------------------------
FP VecLen (FCRD& v)
{
	return FSqrt ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NrmVec2D
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Normalises a 2D vector
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool NrmVec2D (FP& x, FP& y)
{
	FP len = VecLen2D (x,y);

	if (len == 0)
		return FALSE;

	x /= len;
	y /= len;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NrmVec
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Normalises a vector
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool NrmVec (FCRD& srce, FCRD& dest)
{
	FP len = VecLen (srce);

	if(len == 1.0) return TRUE;
	if (len == 0)
	{
		dest.x = srce.x;
		dest.y = srce.y;
		dest.z = srce.z;
		return FALSE;
	}

	dest.x = srce.x / len;
	dest.y = srce.y / len;
	dest.z = srce.z / len;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotateVec2D
//Author		Andrew McRae
//Date			Wed 2 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void RotateVec2D (FP& x, FP& y, FP angle)
{

	FP cos = FCos(angle);
	FP sin = FSin(angle);

	FP temp = (x * cos) - (y * sin);
	y = (x * sin) + (y * cos);
	x = temp;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotVecXSC
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Rotates a vector about the X axis
//
//Inputs		source vector, dest vector, sine & cosine of the angle
//
//Returns	
//
//------------------------------------------------------------------------------
void RotVecXSC (FCRD& srce, FCRD& dest, FP sin, FP cos)
{
	FCRD v;

	v.x = srce.x;
	v.y = (srce.y * cos) - (srce.z * sin);
	v.z = (srce.z * cos) + (srce.y * sin);

	dest.x = v.x;
	dest.y = v.y;
	dest.z = v.z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotVecYSC
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Rotates a vector about the Y axis
//
//Inputs		source vector, dest vector, sine & cosine of the angle
//
//Returns	
//
//------------------------------------------------------------------------------
void RotVecYSC (FCRD& srce, FCRD& dest, FP sin, FP cos)
{
	FCRD v;

	v.x = (srce.x * cos) + (srce.z * sin);
	v.y = srce.y;
	v.z = (srce.z * cos) - (srce.x * sin);

	dest.x = v.x;
	dest.y = v.y;
	dest.z = v.z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotVecZSC
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Rotates a vector about the Z axis
//
//Inputs		source vector, dest vector, sine & cosine of the angle
//
//Returns	
//
//------------------------------------------------------------------------------
void RotVecZSC (FCRD& srce, FCRD& dest, FP sin, FP cos)
{
	FCRD v;

	v.x = (srce.x * cos) - (srce.y * sin);
	v.y = (srce.y * cos) + (srce.x * sin);
	v.z = srce.z;

	dest.x = v.x;
	dest.y = v.y;
	dest.z = v.z;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TnsAxs
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Transforms vector by an orientation matrix.
//				Imagine this function returns vector coords for
//				the same vector, but relative to the axes described
//				by the orientation matrix.
//
//				External to Internal
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TnsAxs (FCRD& srce, FCRD& dest, FORI& ori)
{
	FCRD r;

	r.x = ((srce.x * ori.x.x) + (srce.y * ori.x.y) + (srce.z * ori.x.z));
	r.y = ((srce.x * ori.y.x) + (srce.y * ori.y.y) + (srce.z * ori.y.z));
	r.z = ((srce.x * ori.z.x) + (srce.y * ori.z.y) + (srce.z * ori.z.z));

	dest.x = r.x;
	dest.y = r.y;
	dest.z = r.z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TnsPnt
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Transforms vector by inverse of an orientation matrix.
//				Imagine the vector is rotated by the orientation matrix 
//				relative to its existing axes.
//
//				Internal to External
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TnsPnt (FCRD& srce, FCRD& dest, FORI& ori)
{
	FCRD r;

	r.x = ((srce.x * ori.x.x) + (srce.y * ori.y.x) + (srce.z * ori.z.x));
	r.y = ((srce.x * ori.x.y) + (srce.y * ori.y.y) + (srce.z * ori.z.y));
	r.z = ((srce.x * ori.x.z) + (srce.y * ori.y.z) + (srce.z * ori.z.z));

	dest.x = r.x;
	dest.y = r.y;
	dest.z = r.z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddVec
//Author		Andrew McRae
//Date			Tue 21 Jan 1997
//
//Description	v1 = v2 + v3
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AddVec (FCRD& v1, FCRD& v2, FCRD& v3)
{
	v1.x = v2.x + v3.x;
	v1.y = v2.y + v3.y;
	v1.z = v2.z + v3.z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubVec
//Author		Andrew McRae
//Date			Tue 21 Jan 1997
//
//Description	v1 = v2 - v3
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SubVec (FCRD& v1, FCRD& v2, FCRD& v3)
{
	v1.x = v2.x - v3.x;
	v1.y = v2.y - v3.y;
	v1.z = v2.z - v3.z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddVec
//Author		Craig Beeston
//Date			Thu 11 Feb 1999
//
//Description	v1 = v2 + v3
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AddVec (FCRDlong& v1, FCRDlong& v2, FCRDlong& v3)
{
	v1.x = v2.x + v3.x;
	v1.y = v2.y + v3.y;
	v1.z = v2.z + v3.z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubVec
//Author		Craig Beeston
//Date			Thu 11 Feb 1999
//
//Description	v1 = v2 - v3
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SubVec (FCRDlong& v1, FCRDlong& v2, FCRDlong& v3)
{
	v1.x = v2.x - v3.x;
	v1.y = v2.y - v3.y;
	v1.z = v2.z - v3.z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CPrdX
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Performs X = Y . Z Cross Product
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void CPrdX (FORI& ori)
{
	ori.x.x = ((ori.y.y * ori.z.z) - (ori.y.z * ori.z.y));
	ori.x.y = ((ori.y.z * ori.z.x) - (ori.y.x * ori.z.z));
	ori.x.z = ((ori.y.x * ori.z.y) - (ori.y.y * ori.z.x));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CPrdY
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Performs Y = Z . X Cross Product
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void CPrdY (FORI& ori)
{
	ori.y.x = ((ori.z.y * ori.x.z) - (ori.z.z * ori.x.y));
	ori.y.y = ((ori.z.z * ori.x.x) - (ori.z.x * ori.x.z));
	ori.y.z = ((ori.z.x * ori.x.y) - (ori.z.y * ori.x.x));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CPrdZ
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Performs Z = X . Y Cross Product
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void CPrdZ(FORI& ori)
{
	ori.z.x = ((ori.x.y * ori.y.z) - (ori.x.z * ori.y.y));
	ori.z.y = ((ori.x.z * ori.y.x) - (ori.x.x * ori.y.z));
	ori.z.z = ((ori.x.x * ori.y.y) - (ori.x.y * ori.y.x));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CPrd
//Author		Andrew McRae
//Date			Thu 16 Jan 1997
//
//Description	Performs v1 = v2 . v3 Cross Product
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void CPrd (FCRD& v1, FCRD& v2, FCRD& v3)
{
	FCRD r;

	r.x = ((v2.y * v3.z) - (v2.z * v3.y));
	r.y = ((v2.z * v3.x) - (v2.x * v3.z));
	r.z = ((v2.x * v3.y) - (v2.y * v3.x));

	v1.x = r.x;
	v1.y = r.y;
	v1.z = r.z;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DotPrd
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calculates the Dot Product of 2 vectors
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
FP DotPrd (FCRD& v1, FCRD& v2)
{
	FCRD nv1,nv2;

	NrmVec (v1,nv1);
	NrmVec (v2,nv2);

	return ((nv1.x * nv2.x) + (nv1.y * nv2.y) + (nv1.z * nv2.z));
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotOriXVec
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Rotates an orientation matrix about its own x vector
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void RotOriXVec (FORI& ori, FP ang)
{

	if (ang == 0)
		return;

	FCRD tvec;

	FP cosa = FCos (ang);
	FP sina = FSin (ang);

	tvec.x = (ori.z.x * cosa) + (ori.y.x * sina);
	tvec.y = (ori.z.y * cosa) + (ori.y.y * sina);
	tvec.z = (ori.z.z * cosa) + (ori.y.z * sina);

	ori.y.x = (ori.y.x * cosa) - (ori.z.x * sina);
	ori.y.y = (ori.y.y * cosa) - (ori.z.y * sina);
	ori.y.z = (ori.y.z * cosa) - (ori.z.z * sina);

	ori.z.x = tvec.x;
	ori.z.y = tvec.y;
	ori.z.z = tvec.z;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotOriYVec
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Rotates an orientation matrix about its own y vector
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void RotOriYVec (FORI& ori, FP ang)
{

	if (ang == 0)
		return;

	FCRD tvec;

	FP cosa = FCos (ang);
	FP sina = FSin (ang);

	tvec.x = (ori.x.x * cosa) + (ori.z.x * sina);
	tvec.y = (ori.x.y * cosa) + (ori.z.y * sina);
	tvec.z = (ori.x.z * cosa) + (ori.z.z * sina);

	ori.z.x = (ori.z.x * cosa) - (ori.x.x * sina);
	ori.z.y = (ori.z.y * cosa) - (ori.x.y * sina);
	ori.z.z = (ori.z.z * cosa) - (ori.x.z * sina);

	ori.x.x = tvec.x;
	ori.x.y = tvec.y;
	ori.x.z = tvec.z;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotOriZVec
//Author		Andrew McRae
//Date			Thu 9 Jan 1997
//
//Description	Rotates an orientation matrix about its own z vector
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void RotOriZVec (FORI& ori, FP ang)
{

	if (ang == 0)
		return;

	FCRD tvec;

	FP cosa = FCos (ang);
	FP sina = FSin (ang);

	tvec.x = (ori.y.x * cosa) + (ori.x.x * sina);
	tvec.y = (ori.y.y * cosa) + (ori.x.y * sina);
	tvec.z = (ori.y.z * cosa) + (ori.x.z * sina);

	ori.x.x = (ori.x.x * cosa) - (ori.y.x * sina);
	ori.x.y = (ori.x.y * cosa) - (ori.y.y * sina);
	ori.x.z = (ori.x.z * cosa) - (ori.y.z * sina);

	ori.y.x = tvec.x;
	ori.y.y = tvec.y;
	ori.y.z = tvec.z;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetOri
//Author		Andrew McRae
//Date			Fri 17 Jan 1997
//
//Description	Initialises an orientation struct from 3 angles
//				Vector sign convention
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SetOri (FORI& ori, FP x, FP y, FP z)
{

	// Order of rotation is hdg, pitch & roll

	// y = hdg
	// x = pitch
	// z = roll

	FP sinx = FSin(x);
	FP cosx = FCos(x);
	FP siny = FSin(y);
	FP cosy = FCos(y);

	ori.x.x = cosy;
	ori.x.y = 0;
	ori.x.z = siny;

	ori.y.x = siny * sinx;
	ori.y.y = cosx;
	ori.y.z = -cosy * sinx;

	ori.z.x = -siny * cosx;
	ori.z.y = sinx;
	ori.z.z = cosy * cosx;

	RotOriZVec (ori, z);

}

