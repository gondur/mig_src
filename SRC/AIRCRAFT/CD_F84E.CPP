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

void LoadCurvesF84E ()
{



// ****  F84E  Cl  **** //

CURVEPNT F84E_Cl [18] = {
	0.261799	,	1.120000	,
	0.305433	,	1.275000	,
	0.349066	,	1.400000	,
	0.392699	,	1.150000	,
	0.610865	,	0.700000	,
	0.872665	,	0.650000	,
	1.570796	,	0.000000	,
	2.617994	,	0.500000	,
	2.879793	,	0.900000	,
	3.403392	,	-0.900000	,
	3.665191	,	-0.500000	,
	4.712389	,	0.000000	,
	5.410521	,	-0.650000	,
	5.672320	,	-0.700000	,
	5.890486	,	-1.150000	,
	5.934119	,	-1.400000	,
	5.977753	,	-1.275000	,
	6.021386	,	-1.120000	
};

new CURVE ("F84E",
			"Cl",
			18,
			0.000000000000,
			6.283185482051,
			1,
			F84E_Cl);


// ****  F84E  Cd  **** //

CURVEPNT F84E_Cd [21] = {
	0.261799	,	0.112939	,
	0.305433	,	0.123165	,
	0.349066	,	0.153797	,
	0.410152	,	0.398749	,
	0.785398	,	0.707107	,
	1.134464	,	0.906308	,
	1.570796	,	1.000000	,
	2.007129	,	0.906308	,
	2.356194	,	0.707107	,
	2.967060	,	0.173648	,
	3.141593	,	0.100000	,
	3.316126	,	0.173649	,
	3.926991	,	0.707107	,
	4.276057	,	0.906308	,
	4.712389	,	1.000000	,
	5.148721	,	0.906308	,
	5.497787	,	0.707107	,
	5.873033	,	0.398749	,
	5.934119	,	0.153797	,
	5.977753	,	0.123165	,
	6.021386	,	0.112939	
};

new CURVE ("F84E",
			"Cd",
			21,
			0.000000000000,
			6.283185482051,
			1,
			F84E_Cd);


// ****  F84E  CompCd0  **** //
	
CURVEPNT F84E_CompCd0 [6] = {
	0.000000	,	1.000000	,
	0.758621	,	1.000000	,
	0.827586	,	1.066667	,
	1.000000	,	2.066667	,
	1.086207	,	2.333333	,
	2.000000	,	5.000000	
};

new CURVE ("F84E",
			"CompCd0",
			6,
			0.000000000000,
			2.000000000000,
			2,
			F84E_CompCd0);

// ****  F84E  CompK  **** //

CURVEPNT F84E_CompK [6] = {
	0.000000	,	1.000000	,
	0.758621	,	1.000000	,
	0.827586	,	1.016667	,
	1.000000	,	1.166667	,
	1.250000	,	1.666667	,
	2.000000	,	5.000000	
};

new CURVE ("F84E",
			"CompK",
			6,
			0.000000000000,
			2.000000000000,
			2,
			F84E_CompK);



// ****  F84E  Cm  **** //

CURVEPNT F84E_Cm [18] = {
	0.261799	,	0.000000	,
	0.305433	,	-0.005000	,
	0.349066	,	-0.020000	,
	0.410152	,	-0.260000	,
	0.523599	,	-0.225000	,
	0.872665	,	-0.250000	,
	1.745329	,	-0.250000	,
	2.617994	,	-0.170000	,
	2.879793	,	0.000000	,
	3.403392	,	0.000000	,
	3.665191	,	0.170000	,
	4.537856	,	0.250000	,
	5.410521	,	0.250000	,
	5.759587	,	0.225000	,
	5.873033	,	0.260000	,
	5.934119	,	0.020000	,
	5.977753	,	0.005000	,
	6.021386	,	0.000000	
//DeadCode CSB 19/02/99		0.349066	,	0.000000	,
//DeadCode CSB 19/02/99		0.392699	,	-0.025000	,
//DeadCode CSB 19/02/99		0.479966	,	-0.200000	,
//DeadCode CSB 19/02/99		0.523599	,	-0.225000	,
//DeadCode CSB 19/02/99		0.872665	,	-0.250000	,
//DeadCode CSB 19/02/99		1.745329	,	-0.250000	,
//DeadCode CSB 19/02/99		2.617994	,	-0.170000	,
//DeadCode CSB 19/02/99		2.967060	,	0.000000	,
//DeadCode CSB 19/02/99		3.316126	,	0.000000	,
//DeadCode CSB 19/02/99		3.665191	,	0.170000	,
//DeadCode CSB 19/02/99		4.537856	,	0.250000	,
//DeadCode CSB 19/02/99		5.410521	,	0.250000	,
//DeadCode CSB 19/02/99		5.759587	,	0.225000	,
//DeadCode CSB 19/02/99		5.803220	,	0.200000	,
//DeadCode CSB 19/02/99		5.890486	,	0.025000	,
//DeadCode CSB 19/02/99		5.934119	,	0.000000
};

new CURVE ("F84E",
			"Cm",
			18,
			0.000000000000,
			6.283185482051,
			1,
			F84E_Cm);


// ****  F84E  TailCl  **** //

CURVEPNT F84E_TailCl [20] = {
	0.261799	,	1.108719	,
	0.305433	,	1.275000	,
	0.349066	,	1.400000	,
	0.392699	,	1.100000	,
	0.523599	,	0.750000	,
	0.610865	,	0.700000	,
	0.872665	,	0.650000	,
	1.570796	,	0.000000	,
	2.617994	,	0.500000	,
	2.879793	,	0.900000	,
	3.403392	,	-0.900000	,
	3.665191	,	-0.500000	,
	4.712389	,	0.000000	,
	5.410521	,	-0.650000	,
	5.672320	,	-0.700000	,
	5.759587	,	-0.750000	,
	5.890486	,	-1.100000	,
	5.934119	,	-1.400000	,
	5.977753	,	-1.275000	,
	6.021386	,	-1.108719	
};
new CURVE ("F84E",
			"TailCl",
			20,
			0.000000000000,
			6.283185482051,
			1,
			F84E_TailCl);

// ****  F84E  FinCl  **** //

CURVEPNT F84E_FinCl [20] = {
	0.261799	,	0.654498	,
	0.305433	,	0.750000	,
	0.349066	,	0.825000	,
	0.392699	,	0.750000	,
	0.523599	,	0.750000	,
	0.610865	,	0.700000	,
	0.872665	,	0.650000	,
	1.570796	,	0.000000	,
	2.617994	,	0.500000	,
	2.879793	,	0.900000	,
	3.403392	,	-0.900000	,
	3.665191	,	-0.500000	,
	4.712389	,	0.000000	,
	5.410521	,	-0.650000	,
	5.672320	,	-0.700000	,
	5.759587	,	-0.750000	,
	5.890486	,	-0.750000	,
	5.934119	,	-0.825000	,
	5.977753	,	-0.750000	,
	6.021386	,	-0.654498	
};
new CURVE ("F84E",
			"FinCl",
			20,
			0.000000000000,
			6.283185482051,
			1,
			F84E_FinCl);
}

// End.
