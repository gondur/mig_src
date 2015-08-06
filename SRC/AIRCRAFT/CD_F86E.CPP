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

#include "dosdefs.h"
#include "modvec.h"
#include "curves.h"

void LoadCurvesF86E ()
{
// ****  F86E  Cl  **** //

CURVEPNT F86E_Cl [20] = {
	0.261799	,	0.960000	,
	0.305433	,	1.100000	,
	0.349066	,	1.200000	,
	0.392699	,	1.000000	,
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
	5.890486	,	-1.000000	,
	5.934119	,	-1.200000	,
	5.977753	,	-1.100000	,
	6.021386	,	-0.960000	
};

new CURVE ("F86E",
			"Cl",
			20,
			0.000000000000,
			6.283185482051,
			1,
			F86E_Cl);


// ****  F86E  Cd  **** //

CURVEPNT F86E_Cd [21] = {
	0.261799	,	0.101634	,
	0.305433	,	0.133750	,
	0.349066	,	0.170806	,
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
	5.934119	,	0.170806	,
	5.977753	,	0.133750	,
	6.021386	,	0.101634	
};

new CURVE ("F86E",
			"Cd",
			21,
			0.000000000000,
			6.283185482051,
			1,
			F86E_Cd);



CURVEPNT F86E_CompCd0 [14] = {
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
//DeadCode CSB 04/05/99		0.000000	,	1.000000	,
//DeadCode CSB 04/05/99		0.758621	,	1.000000	,
//DeadCode CSB 04/05/99		0.827586	,	1.066667	,
//DeadCode CSB 04/05/99		1.000000	,	2.066667	,
//DeadCode CSB 04/05/99		1.086207	,	2.333333	,
//DeadCode CSB 04/05/99		2.000000	,	5.000000	
};

new CURVE ("F86E",
			"CompCd0",
			14,
			0.000000000000,
			2.000000000000,
			2,
			F86E_CompCd0);


CURVEPNT F86E_CompK [7] = {
	0.00	,	1.00	,
	0.75	,	1.00	,
	1.00	,	1.20	,
	1.25	,	1.60	,
	1.50	,	2.00	,
	1.75	,	2.20	,
	2.00	,	2.35	
//DeadCode CSB 04/05/99		0.000000	,	1.000000	,
//DeadCode CSB 04/05/99		0.758621	,	1.000000	,
//DeadCode CSB 04/05/99		0.827586	,	1.016667	,
//DeadCode CSB 04/05/99		1.000000	,	1.166667	,
//DeadCode CSB 04/05/99		1.250000	,	1.666667	,
//DeadCode CSB 04/05/99		2.000000	,	5.000000	
};

new CURVE ("F86E",
			"CompK",
			7,
			0.000000000000,
			2.000000000000,
			2,
			F86E_CompK);


// ****  F86E  Cm  **** //

CURVEPNT F86E_Cm [18] = {
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
//DeadCode CSB 19/02/99		0.000000	,	-0.003000	,
//DeadCode CSB 19/02/99		0.087266	,	-0.005000	,
//DeadCode CSB 19/02/99		0.130900	,	0.000000	,
//DeadCode CSB 19/02/99		0.174533	,	0.022500	,
//DeadCode CSB 19/02/99		0.218166	,	0.032500	,
//DeadCode CSB 19/02/99		0.261799	,	0.035000	,
//DeadCode CSB 19/02/99		0.305433	,	0.032500	,
//DeadCode CSB 19/02/99		0.349066	,	0.025000	,
//DeadCode CSB 19/02/99		0.410152	,	-0.260991	,
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
//DeadCode CSB 19/02/99		5.873033	,	0.260991	,
//DeadCode CSB 19/02/99		5.934119	,	-0.031000	,
//DeadCode CSB 19/02/99		5.977753	,	-0.038500	,
//DeadCode CSB 19/02/99		6.021386	,	-0.041000	,
//DeadCode CSB 19/02/99		6.065019	,	-0.038500	,
//DeadCode CSB 19/02/99		6.108652	,	-0.028500	,
//DeadCode CSB 19/02/99		6.152286	,	-0.006000	,
//DeadCode CSB 19/02/99		6.195919	,	-0.001000	
};

new CURVE ("F86E",
			"Cm",
			18,
			0.000000000000,
			6.283185482051,
			1,
			F86E_Cm);


// ****  F86E  TailCl  **** //

CURVEPNT F86E_TailCl [20] = {
	0.261799	,	0.960000	,
	0.305433	,	1.100000	,
	0.349066	,	1.200000	,
	0.392699	,	1.000000	,
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
	5.890486	,	-1.000000	,
	5.934119	,	-1.200000	,
	5.977753	,	-1.100000	,
	6.021386	,	-0.960000	
};
new CURVE ("F86E",
			"TailCl",
			20,
			0.000000000000,
			6.283185482051,
			1,
			F86E_TailCl);

// ****  F86E  FinCl  **** //

CURVEPNT F86E_FinCl [20] = {
	0.261799	,	0.582036	,
	0.305433	,	0.666916	,
	0.349066	,	0.727545	,
	0.392699	,	0.606287	,
	0.523599	,	0.454716	,
	0.610865	,	0.424401	,
	0.872665	,	0.394087	,
	1.570796	,	0.000000	,
	2.617994	,	0.303144	,
	2.879793	,	0.545659	,
	3.403392	,	-0.545659	,
	3.665191	,	-0.303144	,
	4.712389	,	0.000000	,
	5.410521	,	-0.394087	,
	5.672320	,	-0.424401	,
	5.759587	,	-0.454716	,
	5.890486	,	-0.606287	,
	5.934119	,	-0.727545	,
	5.977753	,	-0.666916	,
	6.021386	,	-0.582036	
};
new CURVE ("F86E",
			"FinCl",
			20,
			0.000000000000,
			6.283185482051,
			1,
			F86E_FinCl);



// ****  F86E  JetMachFact  **** //
CURVEPNT F86E_JetMachFact [6] = {
	0.000	,	1.000	,
	0.600	,	1.000	,
	0.720	,	1.050	,
	0.850	,	1.135	,
	0.970	,	1.265	,
	1.200	,	1.500	
};

new CURVE ("F86E",
			"JetMachFact",
			6,
			0.0,
			1.2,
			2,
			F86E_JetMachFact);


// ****  F86E  JetThrustRpm  **** //
CURVEPNT F86E_JetThrustRpm [10] = {
	0.0000	,	0.0000	,
	0.1250	,	0.0096	,
	0.2500	,	0.0192	,
	0.3750	,	0.0385	,
	0.5000	,	0.0865	,
	0.6250	,	0.1827	,
	0.7500	,	0.3846	,
	0.8750	,	0.6827	,
	1.0000	,	1.0000	,
	1.5000	,	2.2500	
};

new CURVE ("F86E",
			"JetThrustRpm",
			10,
			0.0,
			1.5,
			2,
			F86E_JetThrustRpm);

// ****  F86E  JetWindMillDrag  **** //
CURVEPNT F86E_JetWindMillDrag [6] = {
	0	,	-0.015000	,
	100	,	-0.022500	,
	200	,	-0.085000	,
	300	,	-0.160000	,
	400	,	-0.250000	,
	500	,	-0.350000	
};

new CURVE ("F86E",
			"JetWindMillDrag",
			6,
			0.0,
			500.0,
			2,
			F86E_JetWindMillDrag);

// ****  F86E  JetWindMillRpm  **** //
CURVEPNT F86E_JetWindMillRpm [6] = {
	0	,	0.061300	,
	100	,	0.145770	,
	200	,	0.293389	,
	300	,	0.504159	,
	400	,	0.778079	,
	500	,	1.000000	
};

new CURVE ("F86E",
			"JetWindMillRpm",
			6,
			0.0,
			500.0,
			2,
			F86E_JetWindMillRpm);


}

// End.
