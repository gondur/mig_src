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

void LoadCurvesCOMM ()
{



//DeadCode CSB 07 Sep 98	// ****  COMM  TailCd  **** //
//DeadCode CSB 07 Sep 98	
//DeadCode CSB 07 Sep 98	CURVEPNT COMM_TailCd [6] = {
//DeadCode CSB 07 Sep 98		0.000000000000,0.000000000000,
//DeadCode CSB 07 Sep 98		0.349065850418,0.000000000000,
//DeadCode CSB 07 Sep 98		1.570796361786,1.000000000000,
//DeadCode CSB 07 Sep 98		3.141592653759,0.000000000000,
//DeadCode CSB 07 Sep 98		4.712388998091,1.000000000000,
//DeadCode CSB 07 Sep 98		5.934119457100,0.000000000000
//DeadCode CSB 07 Sep 98	};
//DeadCode CSB 07 Sep 98	
//DeadCode CSB 07 Sep 98	new CURVE ("COMM",
//DeadCode CSB 07 Sep 98				"TailCd",
//DeadCode CSB 07 Sep 98				6,
//DeadCode CSB 07 Sep 98				0.000000000000,
//DeadCode CSB 07 Sep 98				6.283185482051,
//DeadCode CSB 07 Sep 98				1,
//DeadCode CSB 07 Sep 98				COMM_TailCd);
// ****  F51D  TailCd  **** //

CURVEPNT COMM_TailCd [9] = {
	0.087266463,	0.010000,
	0.174532925,	0.100000,
	0.34906585, 	2.000000,
	2.35619449, 	2.000000,
	3.141592654,	0.100000,
	3.926990817,	2.000000,
	5.934119457,	2.000000,
	6.108652382,	0.100000,
	6.195918845,	0.010000
};

new CURVE ("COMM",
			"TailCd",
			9,
			0.000000000000,
			6.283185482051,
			1,
			COMM_TailCd);




// ****  COMM  CtrlCl  **** //

CURVEPNT COMM_CtrlCl [8] = {
	0.261799387813,1.200000000000,
	0.523598775626,0.600000000000,
	2.617993878132,0.600000000000,
	2.879793161226,1.200000000000,
	3.403392076479,1.200000000000,
	3.665191429385,0.600000000000,
	5.759586531891,0.600000000000,
	6.021386146597,1.200000000000
};

new CURVE ("COMM",
			"CtrlCl",
			8,
			0.000000000000,
			6.283185482051,
			1,
			COMM_CtrlCl);


}

// End.
