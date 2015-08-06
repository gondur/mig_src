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

// Curves.cpp
// Produced by ceditor.exe
// Andrew McRae 10Feb97

#include "dosdefs.h"
#include "modvec.h"
#include "curves.h"

void LoadCurvesF94A ()
{



// ****  F94A  Cd  **** //

CURVEPNT F94A_Cd [16] = {
	0.000000000000,0.016700000000,
	0.060500000000,0.017000000000,
	0.134680000000,0.017432000000,
	0.219000000000,0.018000000000,
	0.289562000000,0.020156000000,
	0.354000000000,0.023000000000,
	0.385000000000,0.025000000000,
	0.517172000000,0.034320000000,
	0.632997000000,0.047939000000,
	0.794613000000,0.072998000000,
	0.918519000000,0.102415000000,
	1.020875000000,0.136190000000,
	1.110000000000,0.172000000000,
	1.198653000000,0.216370000000,
	1.290236000000,0.281104000000,
	1.368350000000,0.352932000000
};

new CURVE ("F94A",
			"Cd",
			16,
			0.000000000000,
			1.600000000000,
			2,
			F94A_Cd);


}

// End.
