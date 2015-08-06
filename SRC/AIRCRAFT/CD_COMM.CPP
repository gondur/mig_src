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

// ****  COMM  TailCl  **** //

CURVEPNT COMM_TailCl [2] = {
	0.785398	,	2.903226	,
	5.497787	,	-2.903226	
//DeadCode CSB 28/01/99		0.270526	,	1.000000	,
//DeadCode CSB 28/01/99		0.305433	,	1.125000	,
//DeadCode CSB 28/01/99		0.349066	,	1.250000	,
//DeadCode CSB 28/01/99		0.392699	,	1.050000	,
//DeadCode CSB 28/01/99		0.523599	,	0.900000	,
//DeadCode CSB 28/01/99		0.610865	,	0.700000	,
//DeadCode CSB 28/01/99		0.872665	,	0.650000	,
//DeadCode CSB 28/01/99		1.570796	,	0.000000	,
//DeadCode CSB 28/01/99		2.617994	,	0.500000	,
//DeadCode CSB 28/01/99		2.879793	,	0.900000	,
//DeadCode CSB 28/01/99		3.403392	,	-0.900000	,
//DeadCode CSB 28/01/99		3.665191	,	-0.500000	,
//DeadCode CSB 28/01/99		4.712389	,	0.000000	,
//DeadCode CSB 28/01/99		5.410521	,	-0.650000	,
//DeadCode CSB 28/01/99		5.672320	,	-0.700000	,
//DeadCode CSB 28/01/99		5.759587	,	-0.900000	,
//DeadCode CSB 28/01/99		5.890486	,	-1.050000	,
//DeadCode CSB 28/01/99		5.934119	,	-1.250000	,
//DeadCode CSB 28/01/99		5.977753	,	-1.125000	,
//DeadCode CSB 28/01/99		6.012659	,	-1.000000	
};
new CURVE ("COMM",
			"TailCl",
			2,
			0.000000000000,
			6.283185482051,
			1,
			COMM_TailCl);



// ****  COMM  FinCl  **** //

CURVEPNT COMM_FinCl [20] = {
	0.270526	,	0.666667	,
	0.305433	,	0.750000	,
	0.349066	,	0.833334	,
	0.392699	,	0.900000	,
	0.523599	,	0.900000	,
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
	5.759587	,	-0.900000	,
	5.890486	,	-0.900000	,
	5.934119	,	-0.833334	,
	5.977753	,	-0.750000	,
	6.012659	,	-0.666667	

//DeadCode CSB 15/01/99		0.270526	,	0.610166	,
//DeadCode CSB 15/01/99		0.349066	,	0.762707	,
//DeadCode CSB 15/01/99		0.392699	,	0.640674	,
//DeadCode CSB 15/01/99		0.436332	,	0.579658	,
//DeadCode CSB 15/01/99		0.610865	,	0.427116	,
//DeadCode CSB 15/01/99		0.872665	,	0.396608	,
//DeadCode CSB 15/01/99		1.570796	,	0.000000	,
//DeadCode CSB 15/01/99		2.617994	,	0.305083	,
//DeadCode CSB 15/01/99		2.879793	,	0.549149	,
//DeadCode CSB 15/01/99		3.403392	,	-0.549149	,
//DeadCode CSB 15/01/99		3.665191	,	-0.305083	,
//DeadCode CSB 15/01/99		4.712389	,	0.000000	,
//DeadCode CSB 15/01/99		5.410521	,	-0.396608	,
//DeadCode CSB 15/01/99		5.672320	,	-0.427116	,
//DeadCode CSB 15/01/99		5.846853	,	-0.579658	,
//DeadCode CSB 15/01/99		5.890486	,	-0.640674	,
//DeadCode CSB 15/01/99		5.934119	,	-0.762707	,
//DeadCode CSB 15/01/99		6.012659	,	-0.610166	,
};

new CURVE ("COMM",
			"FinCl",
			20,
			0.000000000000,
			6.283185482051,
			1,
			COMM_FinCl);



// ****  COMM  TailCd  **** //

CURVEPNT COMM_TailCd [24] = {
	0.000000	,	0.000000	,
	0.087266	,	0.009748	,
	0.174533	,	0.038991	,
	0.261799	,	0.087730	,
	0.349066	,	0.155964	,
	0.410152	 , 	0.398749	,
	0.785398	 , 	0.707107	,
	1.134464	 , 	0.906308	,
	1.570796	 , 	1.000000	,
	2.007129	 , 	0.906308	,
	2.356194	 , 	0.707107	,
	2.967060	 , 	0.173648	,
	3.141593	 , 	0.100000	,
	3.316126	 , 	0.173649	,
	3.926991	 , 	0.707107	,
	4.276057	 , 	0.906308	,
	4.712389	 , 	1.000000	,
	5.148721	 , 	0.906308	,
	5.497787	 , 	0.707107	,
	5.873033	 , 	0.398749	,
	5.934119	,	0.155964	,
	6.021386	,	0.087730	,
	6.108652	,	0.038991	,
	6.195919	,	0.009748	
//DeadCode CSB 30/11/98		0.000000	,	0.000000	,
//DeadCode CSB 30/11/98		0.087266	,	0.008038	,
//DeadCode CSB 30/11/98		0.174533	,	0.032154	,
//DeadCode CSB 30/11/98		0.261799	,	0.072345	,
//DeadCode CSB 30/11/98		0.349066	,	0.128614	,
//DeadCode CSB 30/11/98		0.610865	,	0.946685	,
//DeadCode CSB 30/11/98		1.047198	,	1.163256	,
//DeadCode CSB 30/11/98		1.570796	,	1.250000	,
//DeadCode CSB 30/11/98		2.356194	,	1.051121	,
//DeadCode CSB 30/11/98		3.054326	,	0.369027	,
//DeadCode CSB 30/11/98		3.228859	,	0.369027	,
//DeadCode CSB 30/11/98		3.926991	,	1.051121	,
//DeadCode CSB 30/11/98		4.712389	,	1.250000	,
//DeadCode CSB 30/11/98		5.235988	,	1.163256	,
//DeadCode CSB 30/11/98		5.672320	,	0.946685	,
//DeadCode CSB 30/11/98		5.934119	,	0.128614	,
//DeadCode CSB 30/11/98		6.021386	,	0.072345	,
//DeadCode CSB 30/11/98		6.108652	,	0.032154	,
//DeadCode CSB 30/11/98		6.195919	,	0.008038	
//DeadCode CSB 03/11/98		0.000000000000,0.000000000000,
//DeadCode CSB 03/11/98		0.349065850418,0.000000000000,
//DeadCode CSB 03/11/98		1.570796361786,1.000000000000,
//DeadCode CSB 03/11/98		3.141592653759,0.000000000000,
//DeadCode CSB 03/11/98		4.712388998091,1.000000000000,
//DeadCode CSB 03/11/98		5.934119457100,0.000000000000
};

new CURVE ("COMM",
			"TailCd",
			24,
			0.000000000000,
			6.283185482051,
			1,
			COMM_TailCd);

// ****  COMM  TailCm  **** //

CURVEPNT COMM_TailCm [16] = {
	0.305433	,	0.0	,
	0.349066	,	-0.1	,
	0.392699	,	-0.4	,
	0.436332	,	-0.5	,
	1.396263	,	-0.5	,
	1.745329	,	0.5	,
	2.792527	,	0.5	,
	2.967060	,	0.0	,
	3.316126	,	0.0	,
	3.490659	,	-0.5	,
	4.537856	,	-0.5	,
	4.886922	,	0.5	,
	5.846853	,	0.5	,
	5.890486	,	0.4	,
	5.934119	,	0.1	,
	5.977753	,	0.0	
};

new CURVE ("COMM",
			"TailCm",
			16,
			0.000000000000,
			6.283185482051,
			1,
			COMM_TailCm);


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


//************ Compressibility Drag ***************

CURVEPNT COMM_CompK [6] = {
	0.000	,	1.000	,
	0.750	,	1.000	,
	0.875	,	1.500	,
	1.000	,	2.500	,
	1.250	,	5.000	,
	2.000	,	5.000	
};

new CURVE ("COMM",
			"CompK",
			6,
			0.000000000000,
			2.000000000000,
			2,
			COMM_CompK);

}
// End.
