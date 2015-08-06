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

void LoadCurvesF80C ()
{



// ****  F80C  Cl  **** //

CURVEPNT F80C_Cl [18] = {
	0.261799	,	1.200000	,
	0.305433	,	1.375000	,
	0.349066	,	1.475000	,
	0.392699	,	1.250000	,
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
	5.890486	,	-1.250000	,
	5.934119	,	-1.475000	,
	5.977753	,	-1.375000	,
	6.021386	,	-1.200000	
};

new CURVE ("F80C",
			"Cl",
			18,
			0.000000000000,
			6.283185482051,
			1,
			F80C_Cl);


// ****  F80C  Cd  **** //

CURVEPNT F80C_Cd [21] = {
	0.261799	,	0.103861	,
	0.305433	,	0.133025	,
	0.349066	,	0.166675	,
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
	5.934119	,	0.166675	,
	5.977753	,	0.133025	,
	6.021386	,	0.103861	
};

new CURVE ("F80C",
			"Cd",
			21,
			0.000000000000,
			6.283185482051,
			1,
			F80C_Cd);


// ****  F80C  CompCd0  **** //
	
CURVEPNT F80C_CompCd0 [6] = {
	0.000000	,	1.000000	,
	0.758621	,	1.000000	,
	0.827586	,	1.066667	,
	1.000000	,	2.066667	,
	1.086207	,	2.333333	,
	2.000000	,	5.000000	
};

new CURVE ("F80C",
			"CompCd0",
			6,
			0.000000000000,
			2.000000000000,
			2,
			F80C_CompCd0);

// ****  F80C  CompK  **** //

CURVEPNT F80C_CompK [6] = {
	0.000000	,	1.000000	,
	0.758621	,	1.000000	,
	0.827586	,	1.016667	,
	1.000000	,	1.166667	,
	1.250000	,	1.666667	,
	2.000000	,	5.000000	
};

new CURVE ("F80C",
			"CompK",
			6,
			0.000000000000,
			2.000000000000,
			2,
			F80C_CompK);



// ****  F80C  Cm  **** //

CURVEPNT F80C_Cm [16] = {
	0.261799	,	0.000	,
	0.305433	,	-0.005	,
	0.349066	,	-0.020	,
	0.523599	,	-0.225	,
	0.872665	,	-0.250	,
	1.745329	,	-0.250	,
	2.617994	,	-0.170	,
	2.879793	,	0.000	,
	3.403392	,	0.000	,
	3.665191	,	0.170	,
	4.537856	,	0.250	,
	5.410521	,	0.250	,
	5.759587	,	0.225	,
	5.934119	,	0.020	,
	5.977753	,	0.005	,
	6.021386	,	0.000	
//DeadCode CSB 08/06/99		0.261799	,	0.000000	,
//DeadCode CSB 08/06/99		0.305433	,	-0.005000	,
//DeadCode CSB 08/06/99		0.349066	,	-0.020000	,
//DeadCode CSB 08/06/99		0.410152	,	-0.260000	,
//DeadCode CSB 08/06/99		0.523599	,	-0.225000	,
//DeadCode CSB 08/06/99		0.872665	,	-0.250000	,
//DeadCode CSB 08/06/99		1.745329	,	-0.250000	,
//DeadCode CSB 08/06/99		2.617994	,	-0.170000	,
//DeadCode CSB 08/06/99		2.879793	,	0.000000	,
//DeadCode CSB 08/06/99		3.403392	,	0.000000	,
//DeadCode CSB 08/06/99		3.665191	,	0.170000	,
//DeadCode CSB 08/06/99		4.537856	,	0.250000	,
//DeadCode CSB 08/06/99		5.410521	,	0.250000	,
//DeadCode CSB 08/06/99		5.759587	,	0.225000	,
//DeadCode CSB 08/06/99		5.873033	,	0.260000	,
//DeadCode CSB 08/06/99		5.934119	,	0.020000	,
//DeadCode CSB 08/06/99		5.977753	,	0.005000	,
//DeadCode CSB 08/06/99		6.021386	,	0.000000	

//DeadCode CSB 19/02/99		0.349066	,	0.000000	,
//DeadCode CSB 19/02/99		0.410152	,	-0.260000	,
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
//DeadCode CSB 19/02/99		5.873033	,	0.260000	,
//DeadCode CSB 19/02/99		5.934119	,	0.000000	
};

new CURVE ("F80C",
			"Cm",
			16,
			0.000000000000,
			6.283185482051,
			1,
			F80C_Cm);


// ****  F80C  TailCl  **** //

CURVEPNT F80C_TailCl [18] = {
	0.261799	,	1.143476	,
	0.305433	,	1.310233	,
	0.349066	,	1.405522	,
	0.392699	,	1.191121	,
	0.610865	,	0.667028	,
	0.872665	,	0.619383	,
	1.570796	,	0.000000	,
	2.617994	,	0.476448	,
	2.879793	,	0.857607	,
	3.403392	,	-0.857607	,
	3.665191	,	-0.476448	,
	4.712389	,	0.000000	,
	5.410521	,	-0.619383	,
	5.672320	,	-0.667028	,
	5.890486	,	-1.191121	,
	5.934119	,	-1.405522	,
	5.977753	,	-1.310233	,
	6.021386	,	-1.143476	
};
new CURVE ("F80C",
			"TailCl",
			18,
			0.000000000000,
			6.283185482051,
			1,
			F80C_TailCl);

// ****  F80C  FinCl  **** //

CURVEPNT F80C_FinCl [18] = {
	0.261799	,	0.633140	,
	0.305433	,	0.725472	,
	0.349066	,	0.778234	,
	0.392699	,	0.659520	,
	0.610865	,	0.369331	,
	0.872665	,	0.342951	,
	1.570796	,	0.000000	,
	2.617994	,	0.263808	,
	2.879793	,	0.474855	,
	3.403392	,	-0.474855	,
	3.665191	,	-0.263808	,
	4.712389	,	0.000000	,
	5.410521	,	-0.342951	,
	5.672320	,	-0.369331	,
	5.890486	,	-0.659520	,
	5.934119	,	-0.778234	,
	5.977753	,	-0.725472	,
	6.021386	,	-0.633140	
};
new CURVE ("F80C",
			"FinCl",
			18,
			0.000000000000,
			6.283185482051,
			1,
			F80C_FinCl);

}

// End.
