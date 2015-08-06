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

void LoadCurvesMIG15 ()
{



// ****  MIG15  Cl  **** //

CURVEPNT MIG15_Cl [22] = {
	0.261799	,	1.050000	,
	0.287979	,	1.125000	,
	0.305433	,	1.150000	,
	0.322886	,	1.100000	,
	0.349066	,	1.125000	,
	0.392699	,	1.000000	,
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
	5.890486	,	-1.000000	,
	5.934119	,	-1.125000	,
	5.960299	,	-1.100000	,
	5.977753	,	-1.150000	,
	5.995206	,	-1.125000	,
	6.021386	,	-1.050000	
};

new CURVE ("MIG15",
			"Cl",
			22,
			0.000000000000,
			6.283185482051,
			1,
			MIG15_Cl);


// ****  MIG15  Cd  **** //

CURVEPNT MIG15_Cd [21] = {
	0.261799	,	0.110756	,
	0.305433	,	0.143602	,
	0.349066	,	0.179200	,
	0.436332	,	0.422618	,
	0.698132	,	0.642788	,
	1.134464	,	0.906308	,
	1.570796	,	1.000000	,
	2.007129	,	0.906308	,
	2.443461	,	0.642788	,
	2.967060	,	0.173648	,
	3.141593	,	0.100000	,
	3.316126	,	0.173648	,
	3.839724	,	0.642788	,
	4.276057	,	0.906308	,
	4.712389	,	1.000000	,
	5.148721	,	0.906308	,
	5.585054	,	0.642788	,
	5.846853	,	0.422618	,
	5.934119	,	0.179200	,
	5.977753	,	0.143602	,
	6.021386	,	0.110756	
};

new CURVE ("MIG15",
			"Cd",
			21,
			0.000000000000,
			6.283185482051,
			1,
			MIG15_Cd);


// ****  MIG15  CompCd  **** //

CURVEPNT MIG15_CompCd0 [14] = {
//DeadCode CSB 04/05/99		0.000	,	1.000	,
//DeadCode CSB 04/05/99		0.200	,	1.000	,
//DeadCode CSB 04/05/99		0.400	,	0.925	,
//DeadCode CSB 04/05/99		0.600	,	0.900	,
//DeadCode CSB 04/05/99		0.850	,	1.050	,
//DeadCode CSB 04/05/99		0.875	,	1.150	,
//DeadCode CSB 04/05/99		0.900	,	1.400	,
//DeadCode CSB 04/05/99		0.925	,	2.000	,
//DeadCode CSB 04/05/99		0.950	,	2.750	,
//DeadCode CSB 04/05/99		0.980	,	3.500	,
//DeadCode CSB 04/05/99		1.000	,	3.700	,
//DeadCode CSB 04/05/99		1.050	,	3.950	,
//DeadCode CSB 04/05/99		2.000	,	10.000	
	0.0000	,	1.0000	,
	0.7500	,	1.0000	,
	0.8000	,	1.0250	,
	0.8750	,	1.2500	,
	0.9000	,	1.4500	,
	0.9125	,	1.6500	,
	0.9250	,	2.0000	,
	0.9500	,	3.2500	,
	0.9750	,	4.2500	,
	1.0000	,	5.1250	,
	1.0200	,	5.5000	,
	1.0400	,	5.6000	,
	1.1000	,	5.5000	,
	2.0000	,	10.0000	
};

new CURVE ("MIG15",
			"CompCd0",
			14,
			0.000000000000,
			2.000000000000,
			2,
			MIG15_CompCd0);

//****************************

CURVEPNT MIG15_CompK [6] = {
	0.000000	,	1.000000	,
	0.758621	,	1.000000	,
	0.827586	,	1.016667	,
	1.000000	,	1.166667	,
	1.250000	,	1.666667	,
	2.000000	,	5.000000	
};

new CURVE ("MIG15",
			"CompK",
			6,
			0.000000000000,
			2.000000000000,
			2,
			MIG15_CompK);



// ****  MIG15  Cm  **** //

CURVEPNT MIG15_Cm [18] = {
//DeadCode CSB 07/04/99		0.261799	,	0.000000	,
//DeadCode CSB 07/04/99		0.305433	,	-0.005000	,
//DeadCode CSB 07/04/99		0.349066	,	-0.020000	,
//DeadCode CSB 07/04/99		0.410152	,	-0.260000	,
//DeadCode CSB 07/04/99		0.523599	,	-0.225000	,
//DeadCode CSB 07/04/99		0.872665	,	-0.250000	,
//DeadCode CSB 07/04/99		1.745329	,	-0.250000	,
//DeadCode CSB 07/04/99		2.617994	,	-0.170000	,
//DeadCode CSB 07/04/99		2.879793	,	0.000000	,
//DeadCode CSB 07/04/99		3.403392	,	0.000000	,
//DeadCode CSB 07/04/99		3.665191	,	0.170000	,
//DeadCode CSB 07/04/99		4.537856	,	0.250000	,
//DeadCode CSB 07/04/99		5.410521	,	0.250000	,
//DeadCode CSB 07/04/99		5.759587	,	0.225000	,
//DeadCode CSB 07/04/99		5.873033	,	0.260000	,
//DeadCode CSB 07/04/99		5.934119	,	0.020000	,
//DeadCode CSB 07/04/99		5.977753	,	0.005000	,
//DeadCode CSB 07/04/99		6.021386	,	0.000000	
	0.279253	,	0.000000	,
	0.296706	,	0.010000	,
	0.322886	,	0.040000	,
	0.366519	,	0.060000	,
	0.383972	,	0.055000	,
	0.436332	,	-0.250000	,
	1.745329	,	-0.250000	,
	2.617994	,	-0.170000	,
	2.879793	,	0.000000	,
	3.403392	,	0.000000	,
	3.665191	,	0.170000	,
	4.537856	,	0.250000	,
	5.846853	,	0.250000	,
	5.899213	,	-0.055000	,
	5.916666	,	-0.060000	,
	5.960299	,	-0.040000	,
	5.986479	,	-0.010000	,
	6.003933	,	0.000000	
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

new CURVE ("MIG15",
			"Cm",
			18,
			0.000000000000,
			6.283185482051,
			1,
			MIG15_Cm);


// ****  MIG15  TailCl  **** //

CURVEPNT MIG15_TailCl [18] = {
	0.261799	,	0.904206	,
	0.287979	,	0.975000	,
	0.305433	,	1.000000	,
	0.349066	,	0.900000	,
	0.610865	,	0.700000	,
	0.872665	,	0.650000	,
	1.570796	,	0.000000	,
	2.617994	,	0.500000	,
	2.879793	,	-0.900000	,
	3.403392	,	0.900000	,
	3.665191	,	-0.500000	,
	4.712389	,	0.000000	,
	5.410521	,	-0.650000	,
	5.672320	,	-0.700000	,
	5.934119	,	-0.900000	,
	5.977753	,	-1.000000	,
	5.995206	,	-0.975000	,
	6.021386	,	-0.904206	
};
new CURVE ("MIG15",
			"TailCl",
			18,
			0.000000000000,
			6.283185482051,
			1,
			MIG15_TailCl);

// ****  MIG15  FinCl  **** //

CURVEPNT MIG15_FinCl [18] = {
	0.261799	,	0.350811	,
	0.287979	,	0.382500	,
	0.305433	,	0.400000	,
	0.392699	,	0.375000	,
	0.610865	,	0.275000	,
	0.872665	,	0.250000	,
	1.570796	,	0.000000	,
	2.617994	,	0.200000	,
	2.879793	,	0.350000	,
	3.403392	,	-0.350000	,
	3.665191	,	-0.200000	,
	4.712389	,	0.000000	,
	5.410521	,	-0.250000	,
	5.672320	,	-0.275000	,
	5.890486	,	-0.375000	,
	5.977753	,	-0.400000	,
	5.995206	,	-0.382500	,
	6.021386	,	-0.350811	
};
new CURVE ("MIG15",
			"FinCl",
			18,
			0.000000000000,
			6.283185482051,
			1,
			MIG15_FinCl);


// ****  MIG15  JetMachFact  **** //
CURVEPNT MIG15_JetMachFact [9] = {
	0.0	,	1.000	,
	0.2	,	0.940	,
	0.4	,	0.890	,
	0.5	,	0.880	,
	0.6	,	0.880	,
	0.7	,	0.885	,
	0.8	,	0.900	,
	0.9	,	0.940	,
	1.0	,	1.000	
};

new CURVE ("MIG15",
			"JetMachFact",
			9,
			0.0,
			1.0,
			2,
			MIG15_JetMachFact);
}

// End.
