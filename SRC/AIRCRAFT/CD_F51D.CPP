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

void LoadCurvesF51D ()
{



// ****  P51D  Cl  **** //

CURVEPNT P51D_Cl [18] = {
	0.261799	,	1.177787	,
	0.305433	,	1.350000	,
	0.349066	,	1.450000	,
	0.392699	,	1.200000	,
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
	5.890486	,	-1.200000	,
	5.934119	,	-1.450000	,
	5.977753	,	-1.350000	,
	6.021386	,	-1.177787	
};

new CURVE ("P51D",
			"Cl",
			18,
			0.000000000000,
			6.283185482051,
			1,
			P51D_Cl);


// ****  P51D  Cd  **** //

CURVEPNT P51D_Cd [19] = {
	0.261799	,	0.100158	,
	0.349066	,	0.146675	,
	0.436332	,	0.422618	,
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
	5.846853	,	0.422618	,
	5.934119	,	0.146675	,
	6.021386	,	0.100158	
};

new CURVE ("P51D",
			"Cd",
			19,
			0.000000000000,
			6.283185482051,
			1,
			P51D_Cd);


// ****  P51D  CompCd0  **** //
	
CURVEPNT P51D_CompCd0 [6] = {
	0.000000	,	1.000000	,
	0.758621	,	1.000000	,
	0.827586	,	1.066667	,
	1.000000	,	2.066667	,
	1.086207	,	2.333333	,
	2.000000	,	5.000000	
};

new CURVE ("P51D",
			"CompCd0",
			6,
			0.000000000000,
			2.000000000000,
			2,
			P51D_CompCd0);

// ****  P51D  CompK  **** //

CURVEPNT P51D_CompK [6] = {
	0.000000	,	1.000000	,
	0.758621	,	1.000000	,
	0.827586	,	1.016667	,
	1.000000	,	1.166667	,
	1.250000	,	1.666667	,
	2.000000	,	5.000000	
};

new CURVE ("P51D",
			"CompK",
			6,
			0.000000000000,
			2.000000000000,
			2,
			P51D_CompK);



// ****  P51D  Cm  **** //

CURVEPNT P51D_Cm [18] = {
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

new CURVE ("P51D",
			"Cm",
			18,
			0.000000000000,
			6.283185482051,
			1,
			P51D_Cm);



// ****  P51D  TailCl  **** //

CURVEPNT P51D_TailCl [18] = {
	0.261799	,	1.043883	,
	0.305433	,	1.196517	,
	0.349066	,	1.285147	,
	0.392699	,	1.063570	,
	0.610865	,	0.620416	,
	0.872665	,	0.576101	,
	1.570796	,	0.000000	,
	2.617994	,	0.443154	,
	2.879793	,	0.797678	,
	3.403392	,	-0.797678	,
	3.665191	,	-0.443154	,
	4.712389	,	0.000000	,
	5.410521	,	-0.576101	,
	5.672320	,	-0.620416	,
	5.890486	,	-1.063570	,
	5.934119	,	-1.285147	,
	5.977753	,	-1.196517	,
	6.021386	,	-1.043883	
};
new CURVE ("P51D",
			"TailCl",
			18,
			0.000000000000,
			6.283185482051,
			1,
			P51D_TailCl);

// ****  P51D  FinCl  **** //

CURVEPNT P51D_FinCl [16] = {
	0.261799	,	0.675050	,
	0.305433	,	0.775000	,
	0.349066	,	0.850000	,
	0.610865	,	0.700000	,
	0.872665	,	0.650000	,
	1.570796	,	0.000000	,
	2.617994	,	0.500000	,
	2.879793	,	0.800000	,
	3.403392	,	-0.800000	,
	3.665191	,	-0.500000	,
	4.712389	,	0.000000	,
	5.410520	,	-0.650000	,
	5.672320	,	-0.700000	,
	5.934119	,	-0.850000	,
	5.977753	,	-0.775000	,
	6.021386	,	-0.675050	
//DeadCode CSB 07/05/99		0.261799	,	0.67505	,
//DeadCode CSB 07/05/99		0.305433	,	0.77500	,
//DeadCode CSB 07/05/99		0.349066	,	0.85000	,
//DeadCode CSB 07/05/99		0.610865	,	0.70000	,
//DeadCode CSB 07/05/99		0.872665	,	0.65000	,
//DeadCode CSB 07/05/99		1.570796	,	0.00000	,
//DeadCode CSB 07/05/99		2.617994	,	0.50000	,
//DeadCode CSB 07/05/99		2.879793	,	0.80000	,
//DeadCode CSB 07/05/99		3.403392	,	-0.80000	,
//DeadCode CSB 07/05/99		3.665191	,	-0.50000	,
//DeadCode CSB 07/05/99		4.712389	,	0.00000	,
//DeadCode CSB 07/05/99		5.410520	,	-0.65000	,
//DeadCode CSB 07/05/99		5.672320	,	-0.70000	,
//DeadCode CSB 07/05/99		5.934119	,	-0.85000	,
//DeadCode CSB 07/05/99		5.977753	,	-0.77500	,
//DeadCode CSB 07/05/99		6.021386	,	-0.67505
//DeadCode CSB 29/04/99		0.261799	,	0.471760	,
//DeadCode CSB 29/04/99		0.305433	,	0.540740	,
//DeadCode CSB 29/04/99		0.349066	,	0.580795	,
//DeadCode CSB 29/04/99		0.392699	,	0.480658	,
//DeadCode CSB 29/04/99		0.610865	,	0.280384	,
//DeadCode CSB 29/04/99		0.872665	,	0.260356	,
//DeadCode CSB 29/04/99		1.570796	,	0.000000	,
//DeadCode CSB 29/04/99		2.617994	,	0.200274	,
//DeadCode CSB 29/04/99		2.879793	,	0.360493	,
//DeadCode CSB 29/04/99		3.403392	,	-0.360493	,
//DeadCode CSB 29/04/99		3.665191	,	-0.200274	,
//DeadCode CSB 29/04/99		4.712389	,	0.000000	,
//DeadCode CSB 29/04/99		5.410521	,	-0.260356	,
//DeadCode CSB 29/04/99		5.672320	,	-0.280384	,
//DeadCode CSB 29/04/99		5.890486	,	-0.480658	,
//DeadCode CSB 29/04/99		5.934119	,	-0.580795	,
//DeadCode CSB 29/04/99		5.977753	,	-0.540740	,
//DeadCode CSB 29/04/99		6.021386	,	-0.471760	
};
new CURVE ("P51D",
			"FinCl",
			16,
			0.000000000000,
			6.283185482051,
			1,
			P51D_FinCl);


// ****  F51D  Power100  **** //

CURVEPNT F51D_Power100 [11] = {
	0	,	0	,
	500	,	100	,
	1000	,	300	,
	1500	,	550	,
	2000	,	950	,
	2750	,	1525	,
	3000	,	1590	,
	3250	,	1425	,
	3500	,	1000	,
	4000	,	-500	,
	5000	,	-4000	
};

new CURVE ("F51D",
			"Power100",
			11,
			0.0,
			5000.0,
			2,
			F51D_Power100);


// ****  F51D  Power0  **** //

CURVEPNT F51D_Power0 [6] = {
	0	,	0	,
	1000	,	-50	,
	2000	,	-250	,
	3000	,	-850	,
	4000	,	-2000	,
	5000	,	-4000	
};

new CURVE ("F51D",
			"Power0",
			6,
			0.0,
			5000.0,
			2,
			F51D_Power0);


// ****  F51D  PowerAlt  **** //

CURVEPNT F51D_PowerAlt [8] = {
//	0.000000000000,0.800000000000,	
//	21400.000000000000,1.000000000000,
//	29494.949495000001,0.765199000000,
//	40000.000000000000,0.530000000000,
//	50101.010101000000,0.352194000000,
//	60000.000000000000,0.200000000000
	    0.0,	0.94151,	//CSB
	 8500.0,	1.00000,
	14000.0,	0.81509,
	21400.0,	0.61069,
	30000.0,	0.42201,
	40000.0,	0.25220,
	50000.0,	0.12390,
	60000.0,	0.03082
};

new CURVE ("F51D",
			"PowerAlt",
			8,
			0.000000000000,
			60000.000000000000,
			2,
			F51D_PowerAlt);

// ****  F51D  PowerAltSuper (High Blower)  **** //	CSB

CURVEPNT F51D_PowerAltSuper [8] = {
	    0.0,	0.71384,	//CSB
	 8500.0,	0.77233,
	14000.0,	0.81069,
	21400.0,	0.86164,
	30000.0,	0.59497,
	40000.0,	0.35535,
	50000.0,	0.17484,
	60000.0,	0.04340};

new CURVE ("F51D",
			"PowerAltSuper",
			8,
			0.000000000000,
			60000.000000000000,
			2,
			F51D_PowerAltSuper);



//DeadCode CSB 28/04/99	// ****  F51D  PropEff  **** //
//DeadCode CSB 28/04/99	
//DeadCode CSB 28/04/99	CURVEPNT F51D_PropEff [20] = {
//DeadCode CSB 28/04/99		0.000000000000,0.000000000000,
//DeadCode CSB 28/04/99		0.459596000000,0.501841000000,
//DeadCode CSB 28/04/99		0.797980000000,0.767213000000,
//DeadCode CSB 28/04/99		1.057239000000,0.867285000000,
//DeadCode CSB 28/04/99		1.457912000000,0.933999000000,
//DeadCode CSB 28/04/99		1.848485000000,0.944901000000,
//DeadCode CSB 28/04/99		1.989899000000,0.936612000000,
//DeadCode CSB 28/04/99		2.087542000000,0.912088000000,
//DeadCode CSB 28/04/99		2.161616000000,0.862110000000,
//DeadCode CSB 28/04/99		2.222222000000,0.784021000000,
//DeadCode CSB 28/04/99		2.279461000000,0.680942000000,
//DeadCode CSB 28/04/99		2.336700000000,0.531010000000,
//DeadCode CSB 28/04/99		2.380471000000,0.374831000000,
//DeadCode CSB 28/04/99		2.420875000000,0.193662000000,
//DeadCode CSB 28/04/99		2.455000000000,0.000000000000,
//DeadCode CSB 28/04/99		2.505051000000,-0.450407000000,
//DeadCode CSB 28/04/99		2.646465000000,-1.126018000000,
//DeadCode CSB 28/04/99		2.902357000000,-1.820396000000,
//DeadCode CSB 28/04/99		3.420875000000,-2.533541000000,
//DeadCode CSB 28/04/99		4.000000000000,-3.000000000000
//DeadCode CSB 28/04/99	};
//DeadCode CSB 28/04/99	
//DeadCode CSB 28/04/99	new CURVE ("F51D",
//DeadCode CSB 28/04/99				"PropEff",
//DeadCode CSB 28/04/99				20,
//DeadCode CSB 28/04/99				0.000000000000,
//DeadCode CSB 28/04/99				4.000000000000,
//DeadCode CSB 28/04/99				2,
//DeadCode CSB 28/04/99				F51D_PropEff);
//DeadCode CSB 28/04/99	
//DeadCode CSB 28/04/99	
//DeadCode CSB 28/04/99	// ****  F51D  PropTq  **** //
//DeadCode CSB 28/04/99	
//DeadCode CSB 28/04/99	CURVEPNT F51D_PropTq [17] = {				// WRONG !!!
//DeadCode CSB 28/04/99		0.000000000000,0.000000000000,			// WRONG !!!
//DeadCode CSB 28/04/99		552.188552000000,114.236862000000,		// WRONG !!!
//DeadCode CSB 28/04/99		1084.175084000000,285.592156000000,		// WRONG !!!
//DeadCode CSB 28/04/99		1562.289562000000,514.065881000000,		// WRONG !!!
//DeadCode CSB 28/04/99		1993.265993000000,812.351022000000,		// WRONG !!!
//DeadCode CSB 28/04/99		2356.902357000000,1091.596686000000,	// WRONG !!!
//DeadCode CSB 28/04/99		2659.932660000000,1269.298472000000,	// WRONG !!!
//DeadCode CSB 28/04/99		2848.484848000000,1351.802873000000,	// WRONG !!!
//DeadCode CSB 28/04/99		3000.000000000000,1370.000000000000,	// WRONG !!!
//DeadCode CSB 28/04/99		3124.579125000000,1326.416903000000,	// WRONG !!!
//DeadCode CSB 28/04/99		3239.057239000000,1218.526533000000,	// WRONG !!!
//DeadCode CSB 28/04/99		3420.875421000000,945.627362000000,		// WRONG !!!
//DeadCode CSB 28/04/99		3636.363636000000,542.623295000000,		// WRONG !!!
//DeadCode CSB 28/04/99		3855.218855000000,-12.193782000000,		// WRONG !!!
//DeadCode CSB 28/04/99		5000.000000000000,-3400.000000000000	// WRONG !!!
//DeadCode CSB 28/04/99	};
//DeadCode CSB 28/04/99	
//DeadCode CSB 28/04/99	new CURVE ("F51D",
//DeadCode CSB 28/04/99				"PropTq",
//DeadCode CSB 28/04/99				17,
//DeadCode CSB 28/04/99				0.000000000000,
//DeadCode CSB 28/04/99				6.283185482051,
//DeadCode CSB 28/04/99				1,
//DeadCode CSB 28/04/99				F51D_PropTq);
//DeadCode CSB 28/04/99	
//DeadCode CSB 28/04/99	
}

// End.
