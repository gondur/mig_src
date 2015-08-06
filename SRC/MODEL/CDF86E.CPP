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

//DeadCode ARM 03Nov97 // Curves.cpp
//DeadCode ARM 03Nov97 // Produced by ceditor.exe
//DeadCode ARM 03Nov97 // Andrew McRae 10Feb97
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 #include "dosdefs.h"
//DeadCode ARM 03Nov97 #include "modvec.h"
//DeadCode ARM 03Nov97 #include "curves.h"
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 void LoadCurvesF86E ()
//DeadCode ARM 03Nov97 {
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  F86E  Cl  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT F86E_Cl [16] = {
//DeadCode ARM 03Nov97 	0.226892802771,1.250000000000,
//DeadCode ARM 03Nov97 	0.259154952197,1.260409000000,
//DeadCode ARM 03Nov97 	0.343776979185,1.249528000000,
//DeadCode ARM 03Nov97 	0.423110134941,1.204190000000,
//DeadCode ARM 03Nov97 	0.507732144475,1.102112000000,
//DeadCode ARM 03Nov97 	0.772175967905,0.598915000000,
//DeadCode ARM 03Nov97 	1.570796361786,0.000000000000,
//DeadCode ARM 03Nov97 	2.813682323178,-0.116774000000,
//DeadCode ARM 03Nov97 	2.961770770051,-0.864131000000,
//DeadCode ARM 03Nov97 	3.321414712000,0.864131000000,
//DeadCode ARM 03Nov97 	3.469502931980,0.116774000000,
//DeadCode ARM 03Nov97 	4.712388998091,0.000000000000,
//DeadCode ARM 03Nov97 	5.384076587110,-0.463386000000,
//DeadCode ARM 03Nov97 	5.680253533215,-1.052723000000,
//DeadCode ARM 03Nov97 	5.786031080040,-1.129007000000,
//DeadCode ARM 03Nov97 	5.875941978261,-1.120614000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("F86E",
//DeadCode ARM 03Nov97 			"Cl",
//DeadCode ARM 03Nov97 			16,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			6.283185482051,
//DeadCode ARM 03Nov97 			1,
//DeadCode ARM 03Nov97 			F86E_Cl);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  F86E  Cd  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT F86E_Cd [23] = {
//DeadCode ARM 03Nov97 	0.000000000000,0.012708000000,
//DeadCode ARM 03Nov97 	0.044294344570,0.025579000000,
//DeadCode ARM 03Nov97 	0.107099755907,0.050765000000,
//DeadCode ARM 03Nov97 	0.173871811941,0.092872000000,
//DeadCode ARM 03Nov97 	0.256510516581,0.179448000000,
//DeadCode ARM 03Nov97 	0.355676948185,0.360470000000,
//DeadCode ARM 03Nov97 	0.655820730974,1.266886000000,
//DeadCode ARM 03Nov97 	0.782753762730,1.570939000000,
//DeadCode ARM 03Nov97 	0.973153301637,1.843320000000,
//DeadCode ARM 03Nov97 	1.269330387368,1.970008000000,
//DeadCode ARM 03Nov97 	1.570796361786,2.000000000000,
//DeadCode ARM 03Nov97 	2.443460935470,1.600000000000,
//DeadCode ARM 03Nov97 	2.855993502478,0.059889000000,
//DeadCode ARM 03Nov97 	3.141592741025,0.012000000000,
//DeadCode ARM 03Nov97 	3.416614289467,0.047911000000,
//DeadCode ARM 03Nov97 	3.839724302234,1.600000000000,
//DeadCode ARM 03Nov97 	4.712388998091,2.000000000000,
//DeadCode ARM 03Nov97 	5.585053449603,1.600000000000,
//DeadCode ARM 03Nov97 	5.891808609412,0.289664000000,
//DeadCode ARM 03Nov97 	6.010808334319,0.104285000000,
//DeadCode ARM 03Nov97 	6.086174827923,0.040927000000,
//DeadCode ARM 03Nov97 	6.171457968179,0.014560000000,
//DeadCode ARM 03Nov97 	6.230792547952,0.009309000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("F86E",
//DeadCode ARM 03Nov97 			"Cd",
//DeadCode ARM 03Nov97 			23,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			6.283185482051,
//DeadCode ARM 03Nov97 			1,
//DeadCode ARM 03Nov97 			F86E_Cd);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  F86E  CompCd  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT F86E_CompCd [24] = {
//DeadCode ARM 03Nov97 	0.000000000000,1.000000000000,
//DeadCode ARM 03Nov97 	0.750000000000,1.000000000000,
//DeadCode ARM 03Nov97 	0.800000000000,1.037000000000,
//DeadCode ARM 03Nov97 	0.840000000000,1.110000000000,
//DeadCode ARM 03Nov97 	0.860000000000,1.181000000000,
//DeadCode ARM 03Nov97 	0.880000000000,1.264000000000,
//DeadCode ARM 03Nov97 	0.900000000000,1.390000000000,
//DeadCode ARM 03Nov97 	0.920000000000,1.706000000000,
//DeadCode ARM 03Nov97 	0.940000000000,2.546000000000,
//DeadCode ARM 03Nov97 	0.960000000000,3.370000000000,
//DeadCode ARM 03Nov97 	0.980000000000,4.060000000000,
//DeadCode ARM 03Nov97 	1.000000000000,4.583000000000,
//DeadCode ARM 03Nov97 	1.020000000000,4.921000000000,
//DeadCode ARM 03Nov97 	1.040000000000,5.019000000000,
//DeadCode ARM 03Nov97 	1.060185000000,5.016965000000,
//DeadCode ARM 03Nov97 	1.080000000000,4.990000000000,
//DeadCode ARM 03Nov97 	1.117845000000,4.875223000000,
//DeadCode ARM 03Nov97 	1.151515000000,4.658829000000,
//DeadCode ARM 03Nov97 	1.175084000000,4.391519000000,
//DeadCode ARM 03Nov97 	1.222222000000,3.793254000000,
//DeadCode ARM 03Nov97 	1.282828000000,3.182260000000,
//DeadCode ARM 03Nov97 	1.393939000000,2.456705000000,
//DeadCode ARM 03Nov97 	1.612795000000,1.909356000000,
//DeadCode ARM 03Nov97 	2.000000000000,1.700000000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("F86E",
//DeadCode ARM 03Nov97 			"CompCd",
//DeadCode ARM 03Nov97 			24,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			2.000000000000,
//DeadCode ARM 03Nov97 			2,
//DeadCode ARM 03Nov97 			F86E_CompCd);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  F86E  Cm  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT F86E_Cm [23] = {
//DeadCode ARM 03Nov97 	0.000000000000,0.010000000000,
//DeadCode ARM 03Nov97 	0.349065832964,0.010000000000,
//DeadCode ARM 03Nov97 	0.523598793080,0.090000000000,
//DeadCode ARM 03Nov97 	0.698131683382,0.100000000000,
//DeadCode ARM 03Nov97 	1.047197586160,0.100000000000,
//DeadCode ARM 03Nov97 	1.221730476462,0.090000000000,
//DeadCode ARM 03Nov97 	1.570796361786,0.000000000000,
//DeadCode ARM 03Nov97 	1.919862159844,0.090000000000,
//DeadCode ARM 03Nov97 	2.094395154866,0.100000000000,
//DeadCode ARM 03Nov97 	2.443460935470,0.100000000000,
//DeadCode ARM 03Nov97 	2.617993825772,0.090000000000,
//DeadCode ARM 03Nov97 	2.792526716075,0.010000000000,
//DeadCode ARM 03Nov97 	3.490658521630,0.010000000000,
//DeadCode ARM 03Nov97 	3.665191411932,0.090000000000,
//DeadCode ARM 03Nov97 	3.839724302234,0.100000000000,
//DeadCode ARM 03Nov97 	4.188790327185,0.100000000000,
//DeadCode ARM 03Nov97 	4.363323217487,0.090000000000,
//DeadCode ARM 03Nov97 	4.712388998091,0.000000000000,
//DeadCode ARM 03Nov97 	5.061454778696,0.090000000000,
//DeadCode ARM 03Nov97 	5.235987668998,0.100000000000,
//DeadCode ARM 03Nov97 	5.585053449603,0.100000000000,
//DeadCode ARM 03Nov97 	5.759586339905,0.090000000000,
//DeadCode ARM 03Nov97 	5.934119230207,0.010000000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("F86E",
//DeadCode ARM 03Nov97 			"Cm",
//DeadCode ARM 03Nov97 			23,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			6.283185482051,
//DeadCode ARM 03Nov97 			1,
//DeadCode ARM 03Nov97 			F86E_Cm);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  F86E  TailCl  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT F86E_TailCl [10] = {
//DeadCode ARM 03Nov97 	0.380799112720,0.687227000000,
//DeadCode ARM 03Nov97 	0.592354171463,0.834490000000,
//DeadCode ARM 03Nov97 	0.877953532183,0.764365000000,
//DeadCode ARM 03Nov97 	1.570796361786,0.000000000000,
//DeadCode ARM 03Nov97 	2.940615407294,-0.610089000000,
//DeadCode ARM 03Nov97 	3.342570074757,0.610089000000,
//DeadCode ARM 03Nov97 	4.712388998091,0.000000000000,
//DeadCode ARM 03Nov97 	5.405231478628,-0.764365000000,
//DeadCode ARM 03Nov97 	5.690831188414,-0.834490000000,
//DeadCode ARM 03Nov97 	5.902386194798,-0.687227000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("F86E",
//DeadCode ARM 03Nov97 			"TailCl",
//DeadCode ARM 03Nov97 			10,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			6.283185482051,
//DeadCode ARM 03Nov97 			1,
//DeadCode ARM 03Nov97 			F86E_TailCl);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  F86E  FinCl  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT F86E_FinCl [16] = {
//DeadCode ARM 03Nov97 	0.179821813895,0.864660000000,
//DeadCode ARM 03Nov97 	0.243288321046,1.037580000000,
//DeadCode ARM 03Nov97 	0.338488107952,1.135130000000,
//DeadCode ARM 03Nov97 	0.460132268475,1.139564000000,
//DeadCode ARM 03Nov97 	0.565909797847,1.068619000000,
//DeadCode ARM 03Nov97 	1.570796361786,0.000000000000,
//DeadCode ARM 03Nov97 	2.253061536190,-0.700588000000,
//DeadCode ARM 03Nov97 	2.951193097399,-0.904557000000,
//DeadCode ARM 03Nov97 	3.331992157759,0.904557000000,
//DeadCode ARM 03Nov97 	4.030123718968,0.700588000000,
//DeadCode ARM 03Nov97 	4.712388998091,0.000000000000,
//DeadCode ARM 03Nov97 	5.717275143151,-1.068619000000,
//DeadCode ARM 03Nov97 	5.823052881963,-1.139564000000,
//DeadCode ARM 03Nov97 	5.944696902859,-1.135130000000,
//DeadCode ARM 03Nov97 	6.039896969018,-1.037580000000,
//DeadCode ARM 03Nov97 	6.103363511076,-0.864660000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("F86E",
//DeadCode ARM 03Nov97 			"FinCl",
//DeadCode ARM 03Nov97 			16,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			6.283185482051,
//DeadCode ARM 03Nov97 			1,
//DeadCode ARM 03Nov97 			F86E_FinCl);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  F86E  JetCr  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT F86E_JetCr [11] = {
//DeadCode ARM 03Nov97 	0.000000000000,0.000000000000,
//DeadCode ARM 03Nov97 	3200.000000000000,0.000000000000,
//DeadCode ARM 03Nov97 	4067.340067000000,148.225713000000,
//DeadCode ARM 03Nov97 	4565.656566000000,312.920949000000,
//DeadCode ARM 03Nov97 	5050.505051000000,576.433327000000,
//DeadCode ARM 03Nov97 	5360.269360000000,839.945705000000,
//DeadCode ARM 03Nov97 	5710.437710000000,1317.561890000000,
//DeadCode ARM 03Nov97 	6383.838384000000,2602.184733000000,
//DeadCode ARM 03Nov97 	7000.000000000000,3700.000000000000,
//DeadCode ARM 03Nov97 	7630.000000000000,4730.000000000000,
//DeadCode ARM 03Nov97 	7950.000000000000,5200.000000000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("F86E",
//DeadCode ARM 03Nov97 			"JetCr",
//DeadCode ARM 03Nov97 			11,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			8000.000000000000,
//DeadCode ARM 03Nov97 			2,
//DeadCode ARM 03Nov97 			F86E_JetCr);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 }
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // End.
