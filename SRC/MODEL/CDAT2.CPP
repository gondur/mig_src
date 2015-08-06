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

//DeadCode ARM 12Sep97 // Curves.cpp
//DeadCode ARM 12Sep97 // Produced by ceditor.exe
//DeadCode ARM 12Sep97 // Andrew McRae 10Feb97
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 #include "dosdefs.h"
//DeadCode ARM 12Sep97 #include "modvec.h"
//DeadCode ARM 12Sep97 #include "curves.h"
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 void LoadCurves ()
//DeadCode ARM 12Sep97 {
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  FuseCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_FuseCl [4] = {
//DeadCode ARM 12Sep97 	0.785398185253,0.400000005960,
//DeadCode ARM 12Sep97 	2.356194496155,-0.400000005960,
//DeadCode ARM 12Sep97 	3.926990747452,0.400000005960,
//DeadCode ARM 12Sep97 	5.497786998749,-0.400000005960
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"FuseCl",
//DeadCode ARM 12Sep97 			4,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_FuseCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  FuseCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_FuseCd [4] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.000000000000,
//DeadCode ARM 12Sep97 	1.570796370506,0.800000011921,
//DeadCode ARM 12Sep97 	3.141592741013,0.000000000000,
//DeadCode ARM 12Sep97 	4.712388992310,0.800000011921
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"FuseCd",
//DeadCode ARM 12Sep97 			4,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_FuseCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  InnerWingCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_InnerWingCl [12] = {
//DeadCode ARM 12Sep97 	0.186750233173,1.220000028610,
//DeadCode ARM 12Sep97 	0.197222203016,1.268000006676,
//DeadCode ARM 12Sep97 	0.218166157603,1.187999963760,
//DeadCode ARM 12Sep97 	0.366519153118,0.140000000596,
//DeadCode ARM 12Sep97 	1.570796370506,0.000000000000,
//DeadCode ARM 12Sep97 	2.813682317734,-0.116774000227,
//DeadCode ARM 12Sep97 	2.961770772934,-0.864130973816,
//DeadCode ARM 12Sep97 	3.321414232254,0.688970029354,
//DeadCode ARM 12Sep97 	3.448347568512,0.116881996393,
//DeadCode ARM 12Sep97 	4.712388992310,0.000000000000,
//DeadCode ARM 12Sep97 	5.923541545868,-0.151947006583,
//DeadCode ARM 12Sep97 	6.039896965027,-1.066547036171
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"InnerWingCl",
//DeadCode ARM 12Sep97 			12,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_InnerWingCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  OuterWingCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_OuterWingCl [12] = {
//DeadCode ARM 12Sep97 	0.322621464729,1.944936990738,
//DeadCode ARM 12Sep97 	0.339810311794,2.020199060440,
//DeadCode ARM 12Sep97 	0.354354709387,1.888826966286,
//DeadCode ARM 12Sep97 	0.602931976318,0.140258997679,
//DeadCode ARM 12Sep97 	1.570796370506,0.000000000000,
//DeadCode ARM 12Sep97 	2.813682317734,-0.105194002390,
//DeadCode ARM 12Sep97 	2.972348690033,-0.853241026402,
//DeadCode ARM 12Sep97 	3.321414232254,0.689606010914,
//DeadCode ARM 12Sep97 	3.437769651413,0.128571003675,
//DeadCode ARM 12Sep97 	4.712388992310,0.000000000000,
//DeadCode ARM 12Sep97 	5.722564220428,-0.549346983433,
//DeadCode ARM 12Sep97 	5.923541545868,-1.670181989670
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"OuterWingCl",
//DeadCode ARM 12Sep97 			12,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_OuterWingCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  WingCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_WingCd [16] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.013000000268,
//DeadCode ARM 12Sep97 	0.046277668327,0.015879999846,
//DeadCode ARM 12Sep97 	0.108421966434,0.029378000647,
//DeadCode ARM 12Sep97 	0.174532920122,0.058242000639,
//DeadCode ARM 12Sep97 	0.272377133369,0.129420995712,
//DeadCode ARM 12Sep97 	0.401954621077,0.173498004675,
//DeadCode ARM 12Sep97 	1.565507531166,1.202658057213,
//DeadCode ARM 12Sep97 	2.855993509293,0.059888999909,
//DeadCode ARM 12Sep97 	3.141592741013,0.012000000104,
//DeadCode ARM 12Sep97 	3.416614294052,0.047910999507,
//DeadCode ARM 12Sep97 	4.717677593231,1.202658057213,
//DeadCode ARM 12Sep97 	5.881230831146,0.173498004675,
//DeadCode ARM 12Sep97 	6.010807991028,0.129420995712,
//DeadCode ARM 12Sep97 	6.108652591705,0.058242000639,
//DeadCode ARM 12Sep97 	6.174763202667,0.029378000647,
//DeadCode ARM 12Sep97 	6.236907482147,0.015879999846
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"WingCd",
//DeadCode ARM 12Sep97 			16,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_WingCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  WingCm  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_WingCm [11] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.009999999553,
//DeadCode ARM 12Sep97 	0.244346097112,0.009999999553,
//DeadCode ARM 12Sep97 	0.314159274101,0.0250000002980,
//DeadCode ARM 12Sep97 	1.570796370506,0.000000000000,
//DeadCode ARM 12Sep97 	2.932153224945,0.0250000002980,
//DeadCode ARM 12Sep97 	3.001966238022,0.009999999553,
//DeadCode ARM 12Sep97 	3.246312379837,0.009999999553,
//DeadCode ARM 12Sep97 	3.316125631332,0.0250000002980,
//DeadCode ARM 12Sep97 	4.712388992310,0.000000000000,
//DeadCode ARM 12Sep97 	5.951572895050,0.0250000002980,
//DeadCode ARM 12Sep97 	6.038839340210,0.009999999553
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"WingCm",
//DeadCode ARM 12Sep97 			11,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_WingCm);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  TailCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_TailCl [10] = {
//DeadCode ARM 12Sep97 	0.261799395084,1.399999976158,
//DeadCode ARM 12Sep97 	0.349065840244,1.360000014305,
//DeadCode ARM 12Sep97 	0.698131680489,0.699999988079,
//DeadCode ARM 12Sep97 	2.443460941315,-0.699999988079,
//DeadCode ARM 12Sep97 	2.879793167114,-1.399999976158,
//DeadCode ARM 12Sep97 	3.403392076492,1.399999976158,
//DeadCode ARM 12Sep97 	3.839724302292,0.699999988079,
//DeadCode ARM 12Sep97 	5.585053443909,-0.699999988079,
//DeadCode ARM 12Sep97 	5.934119224548,-1.360000014305,
//DeadCode ARM 12Sep97 	6.021386146545,-1.399999976158
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"TailCl",
//DeadCode ARM 12Sep97 			10,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_TailCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  TailCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_TailCd [6] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.019999999553,
//DeadCode ARM 12Sep97 	0.314159274101,0.100000001490,
//DeadCode ARM 12Sep97 	1.570796370506,2.000000000000,
//DeadCode ARM 12Sep97 	3.141592741013,0.019999999553,
//DeadCode ARM 12Sep97 	4.712388992310,2.000000000000,
//DeadCode ARM 12Sep97 	5.969026088715,0.100000001490
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"TailCd",
//DeadCode ARM 12Sep97 			6,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_TailCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  FinCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_FinCl [14] = {
//DeadCode ARM 12Sep97 	0.139626339078,0.620000004768,
//DeadCode ARM 12Sep97 	0.366519153118,1.139999985695,
//DeadCode ARM 12Sep97 	0.558505356312,1.279999971390,
//DeadCode ARM 12Sep97 	0.767944872379,1.190000057220,
//DeadCode ARM 12Sep97 	1.169370651245,0.689999997616,
//DeadCode ARM 12Sep97 	2.181661605835,-1.169999957085,
//DeadCode ARM 12Sep97 	2.879793167114,-1.399999976158,
//DeadCode ARM 12Sep97 	3.403392076492,1.399999976158,
//DeadCode ARM 12Sep97 	4.101523876190,1.230000019073,
//DeadCode ARM 12Sep97 	5.113814830780,-0.689999997616,
//DeadCode ARM 12Sep97 	5.515240669250,-1.190000057220,
//DeadCode ARM 12Sep97 	5.724679946899,-1.279999971390,
//DeadCode ARM 12Sep97 	5.916666030884,-1.139999985695,
//DeadCode ARM 12Sep97 	6.143558979034,-0.620000004768
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"FinCl",
//DeadCode ARM 12Sep97 			14,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_FinCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  FinCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_FinCd [6] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.019999999553,
//DeadCode ARM 12Sep97 	0.314159274101,0.100000001490,
//DeadCode ARM 12Sep97 	1.570796370506,2.000000000000,
//DeadCode ARM 12Sep97 	3.141592741013,0.019999999553,
//DeadCode ARM 12Sep97 	4.712388992310,2.000000000000,
//DeadCode ARM 12Sep97 	5.969026088715,0.100000001490
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"FinCd",
//DeadCode ARM 12Sep97 			6,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_FinCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  CtrlCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_CtrlCl [8] = {
//DeadCode ARM 12Sep97 	0.261799395084,1.200000047684,
//DeadCode ARM 12Sep97 	0.523598790169,0.000000000000,
//DeadCode ARM 12Sep97 	2.617993831635,0.000000000000,
//DeadCode ARM 12Sep97 	2.879793167114,1.200000047684,
//DeadCode ARM 12Sep97 	3.403392076492,1.200000047684,
//DeadCode ARM 12Sep97 	3.665191411972,0.000000000000,
//DeadCode ARM 12Sep97 	5.759586334229,0.000000000000,
//DeadCode ARM 12Sep97 	6.021386146545,1.200000047684
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"CtrlCl",
//DeadCode ARM 12Sep97 			8,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_CtrlCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  CtrlCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_CtrlCd [8] = {
//DeadCode ARM 12Sep97 	0.261799395084,0.079999998212,
//DeadCode ARM 12Sep97 	0.523598790169,0.000000000000,
//DeadCode ARM 12Sep97 	2.617993831635,0.000000000000,
//DeadCode ARM 12Sep97 	2.879793167114,0.079999998212,
//DeadCode ARM 12Sep97 	3.403392076492,0.079999998212,
//DeadCode ARM 12Sep97 	3.665191411972,0.000000000000,
//DeadCode ARM 12Sep97 	5.759586334229,0.000000000000,
//DeadCode ARM 12Sep97 	6.021386146545,0.079999998212
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"CtrlCd",
//DeadCode ARM 12Sep97 			8,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_CtrlCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  SlatCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_SlatCl [6] = {
//DeadCode ARM 12Sep97 	0.197671771049,0.000000000000,
//DeadCode ARM 12Sep97 	0.227421686053,0.288367003202,
//DeadCode ARM 12Sep97 	0.280310451984,0.902069985867,
//DeadCode ARM 12Sep97 	0.366254717112,1.000041007996,
//DeadCode ARM 12Sep97 	0.569876432419,0.000000000000,
//DeadCode ARM 12Sep97 	3.152170419693,0.000000000000
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"SlatCl",
//DeadCode ARM 12Sep97 			6,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_SlatCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  FlapCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_FlapCl [4] = {
//DeadCode ARM 12Sep97 	0.336848556995,0.250000000000,
//DeadCode ARM 12Sep97 	0.389208436012,0.000000000000,
//DeadCode ARM 12Sep97 	5.969026088715,0.000000000000,
//DeadCode ARM 12Sep97 	6.038839340210,0.250000000000
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"FlapCl",
//DeadCode ARM 12Sep97 			4,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_FlapCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  FlapCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_FlapCd [3] = {
//DeadCode ARM 12Sep97 	0.349065840244,0.200000002980,
//DeadCode ARM 12Sep97 	1.570796370506,0.000000000000,
//DeadCode ARM 12Sep97 	5.934119224548,0.000000000000
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"FlapCd",
//DeadCode ARM 12Sep97 			3,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_FlapCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  FlapCm  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_FlapCm [2] = {
//DeadCode ARM 12Sep97 	1.745329260826,-0.100000000000,
//DeadCode ARM 12Sep97 	5.235987663269,-0.100000000000
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"FlapCm",
//DeadCode ARM 12Sep97 			2,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			F86E_FlapCm);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  F86E  JetCt  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT F86E_JetCt [10] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.000000000000,
//DeadCode ARM 12Sep97 	0.396465003490,0.105263002217,
//DeadCode ARM 12Sep97 	0.686869025230,0.315789014101,
//DeadCode ARM 12Sep97 	0.873736977577,0.640348970890,
//DeadCode ARM 12Sep97 	1.000000000000,1.000000000000,
//DeadCode ARM 12Sep97 	1.101009964943,1.210523009300,
//DeadCode ARM 12Sep97 	1.169191956520,1.285084962845,
//DeadCode ARM 12Sep97 	1.247475028038,1.241225004196,
//DeadCode ARM 12Sep97 	1.330808043480,0.999997973442,
//DeadCode ARM 12Sep97 	1.500000000000,0.000000000000
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("F86E",
//DeadCode ARM 12Sep97 			"JetCt",
//DeadCode ARM 12Sep97 			10,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			1.500000000000,
//DeadCode ARM 12Sep97 			2,
//DeadCode ARM 12Sep97 			F86E_JetCt);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  FuseCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_FuseCl [4] = {
//DeadCode ARM 12Sep97 	0.785398185253,0.400000005960,
//DeadCode ARM 12Sep97 	2.356194496155,-0.400000005960,
//DeadCode ARM 12Sep97 	3.926990747452,0.400000005960,
//DeadCode ARM 12Sep97 	5.497786998749,-0.400000005960
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"FuseCl",
//DeadCode ARM 12Sep97 			4,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_FuseCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  FuseCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_FuseCd [4] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.000000000000,
//DeadCode ARM 12Sep97 	1.570796370506,0.400000005960,
//DeadCode ARM 12Sep97 	3.141592741013,0.000000000000,
//DeadCode ARM 12Sep97 	4.712388992310,0.400000005960
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"FuseCd",
//DeadCode ARM 12Sep97 			4,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_FuseCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  WingCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_WingCl [12] = {
//DeadCode ARM 12Sep97 	0.279252678156,1.700000047684,
//DeadCode ARM 12Sep97 	0.314159274101,1.759999990463,
//DeadCode ARM 12Sep97 	0.383972436190,1.639999985695,
//DeadCode ARM 12Sep97 	0.523598790169,0.400000005960,
//DeadCode ARM 12Sep97 	1.570796370506,0.000000000000,
//DeadCode ARM 12Sep97 	2.652900457382,-0.159999996424,
//DeadCode ARM 12Sep97 	3.001966238022,-0.600000023842,
//DeadCode ARM 12Sep97 	3.281219005585,0.400000005960,
//DeadCode ARM 12Sep97 	3.700098037720,0.159999996424,
//DeadCode ARM 12Sep97 	4.712388992310,0.000000000000,
//DeadCode ARM 12Sep97 	5.759586334229,-0.439999997616,
//DeadCode ARM 12Sep97 	6.003932476044,-1.299999952316
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"WingCl",
//DeadCode ARM 12Sep97 			12,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_WingCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  WingCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_WingCd [13] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.009999999776,
//DeadCode ARM 12Sep97 	0.069813169539,0.014000000432,
//DeadCode ARM 12Sep97 	0.139626339078,0.029999999329,
//DeadCode ARM 12Sep97 	0.244346097112,0.079999998212,
//DeadCode ARM 12Sep97 	0.314159274101,0.170000001788,
//DeadCode ARM 12Sep97 	0.488692194223,0.200000002980,
//DeadCode ARM 12Sep97 	1.570796370506,1.200000047684,
//DeadCode ARM 12Sep97 	3.001966238022,0.029999999329,
//DeadCode ARM 12Sep97 	3.281219005585,0.029999999329,
//DeadCode ARM 12Sep97 	4.712388992310,1.200000047684,
//DeadCode ARM 12Sep97 	6.073745727539,0.150000005960,
//DeadCode ARM 12Sep97 	6.143558979034,0.039999999106,
//DeadCode ARM 12Sep97 	6.213372230530,0.014999999665
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"WingCd",
//DeadCode ARM 12Sep97 			13,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_WingCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  WingCm  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_WingCm [11] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.019999999553,
//DeadCode ARM 12Sep97 	0.244346097112,0.019999999553,
//DeadCode ARM 12Sep97 	0.314159274101,0.200000002980,
//DeadCode ARM 12Sep97 	1.570796370506,0.000000000000,
//DeadCode ARM 12Sep97 	2.932153224945,0.200000002980,
//DeadCode ARM 12Sep97 	3.001966238022,0.019999999553,
//DeadCode ARM 12Sep97 	3.246312379837,0.019999999553,
//DeadCode ARM 12Sep97 	3.316125631332,0.200000002980,
//DeadCode ARM 12Sep97 	4.712388992310,0.000000000000,
//DeadCode ARM 12Sep97 	5.951572895050,0.200000002980,
//DeadCode ARM 12Sep97 	6.038839340210,0.019999999553
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"WingCm",
//DeadCode ARM 12Sep97 			11,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_WingCm);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  TailCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_TailCl [8] = {
//DeadCode ARM 12Sep97 	0.244346097112,1.600000023842,
//DeadCode ARM 12Sep97 	0.698131680489,0.400000005960,
//DeadCode ARM 12Sep97 	2.443460941315,-0.400000005960,
//DeadCode ARM 12Sep97 	2.897246599197,-1.600000023842,
//DeadCode ARM 12Sep97 	3.385938644409,1.600000023842,
//DeadCode ARM 12Sep97 	3.839724302292,0.400000005960,
//DeadCode ARM 12Sep97 	5.585053443909,-0.400000005960,
//DeadCode ARM 12Sep97 	6.038839340210,-1.600000023842
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"TailCl",
//DeadCode ARM 12Sep97 			8,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_TailCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  TailCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_TailCd [6] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.009999999776,
//DeadCode ARM 12Sep97 	0.314159274101,0.050000000745,
//DeadCode ARM 12Sep97 	1.570796370506,1.000000000000,
//DeadCode ARM 12Sep97 	3.141592741013,0.009999999776,
//DeadCode ARM 12Sep97 	4.712388992310,1.000000000000,
//DeadCode ARM 12Sep97 	5.969026088715,0.050000000745
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"TailCd",
//DeadCode ARM 12Sep97 			6,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_TailCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  FinCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_FinCl [8] = {
//DeadCode ARM 12Sep97 	0.244346097112,1.600000023842,
//DeadCode ARM 12Sep97 	0.698131680489,0.400000005960,
//DeadCode ARM 12Sep97 	2.443460941315,-0.400000005960,
//DeadCode ARM 12Sep97 	2.897246599197,-1.600000023842,
//DeadCode ARM 12Sep97 	3.385938644409,1.600000023842,
//DeadCode ARM 12Sep97 	3.839724302292,0.400000005960,
//DeadCode ARM 12Sep97 	5.585053443909,-0.400000005960,
//DeadCode ARM 12Sep97 	6.038839340210,-1.600000023842
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"FinCl",
//DeadCode ARM 12Sep97 			8,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_FinCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  FinCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_FinCd [6] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.009999999776,
//DeadCode ARM 12Sep97 	0.314159274101,0.050000000745,
//DeadCode ARM 12Sep97 	1.570796370506,1.000000000000,
//DeadCode ARM 12Sep97 	3.141592741013,0.009999999776,
//DeadCode ARM 12Sep97 	4.712388992310,1.000000000000,
//DeadCode ARM 12Sep97 	5.969026088715,0.050000000745
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"FinCd",
//DeadCode ARM 12Sep97 			6,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_FinCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  CtrlCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_CtrlCl [2] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.899999976158,
//DeadCode ARM 12Sep97 	3.141592741013,0.899999976158
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"CtrlCl",
//DeadCode ARM 12Sep97 			2,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_CtrlCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  BladeCl  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_BladeCl [8] = {
//DeadCode ARM 12Sep97 	0.244346097112,1.799999952316,
//DeadCode ARM 12Sep97 	0.698131680489,0.400000005960,
//DeadCode ARM 12Sep97 	2.443460941315,-0.400000005960,
//DeadCode ARM 12Sep97 	2.897246599197,-1.600000023842,
//DeadCode ARM 12Sep97 	3.385938644409,1.600000023842,
//DeadCode ARM 12Sep97 	3.839724302292,0.400000005960,
//DeadCode ARM 12Sep97 	5.585053443909,-0.400000005960,
//DeadCode ARM 12Sep97 	6.038839340210,-1.799999952316
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"BladeCl",
//DeadCode ARM 12Sep97 			8,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_BladeCl);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  BladeCd  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_BladeCd [12] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.017000000924,
//DeadCode ARM 12Sep97 	0.122173048556,0.023000000045,
//DeadCode ARM 12Sep97 	0.244346097112,0.046000000089,
//DeadCode ARM 12Sep97 	0.314159274101,0.086999997497,
//DeadCode ARM 12Sep97 	0.872664630413,0.670000016689,
//DeadCode ARM 12Sep97 	1.570796370506,1.000000000000,
//DeadCode ARM 12Sep97 	3.141592741013,0.002499999944,
//DeadCode ARM 12Sep97 	4.712388992310,1.000000000000,
//DeadCode ARM 12Sep97 	5.410520553589,0.670000016689,
//DeadCode ARM 12Sep97 	5.969026088715,0.086999997497,
//DeadCode ARM 12Sep97 	6.038839340210,0.046000000089,
//DeadCode ARM 12Sep97 	6.161012172699,0.023000000045
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"BladeCd",
//DeadCode ARM 12Sep97 			12,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			6.283185482025,
//DeadCode ARM 12Sep97 			1,
//DeadCode ARM 12Sep97 			P51D_BladeCd);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  Torque100  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_Torque100 [9] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.100000001490,
//DeadCode ARM 12Sep97 	0.255892008543,0.411738008261,
//DeadCode ARM 12Sep97 	0.535354018211,0.703122019768,
//DeadCode ARM 12Sep97 	0.824916005135,0.943830013275,
//DeadCode ARM 12Sep97 	1.000000000000,1.000000000000,
//DeadCode ARM 12Sep97 	1.148147940636,0.926872014999,
//DeadCode ARM 12Sep97 	1.383838057518,0.622328996658,
//DeadCode ARM 12Sep97 	1.612794995308,0.127996996045,
//DeadCode ARM 12Sep97 	2.000000000000,-1.000000000000
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"Torque100",
//DeadCode ARM 12Sep97 			9,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			2.000000000000,
//DeadCode ARM 12Sep97 			2,
//DeadCode ARM 12Sep97 			P51D_Torque100);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // ****  P51D  Torque0  **** //
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 CURVEPNT P51D_Torque0 [5] = {
//DeadCode ARM 12Sep97 	0.000000000000,0.100000001490,
//DeadCode ARM 12Sep97 	0.215488001704,-0.126689001918,
//DeadCode ARM 12Sep97 	0.754208981991,-0.538426995277,
//DeadCode ARM 12Sep97 	1.360268950462,-0.823476016521,
//DeadCode ARM 12Sep97 	2.000000000000,-1.000000000000
//DeadCode ARM 12Sep97 };
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 new CURVE ("P51D",
//DeadCode ARM 12Sep97 			"Torque0",
//DeadCode ARM 12Sep97 			5,
//DeadCode ARM 12Sep97 			0.000000000000,
//DeadCode ARM 12Sep97 			2.000000000000,
//DeadCode ARM 12Sep97 			2,
//DeadCode ARM 12Sep97 			P51D_Torque0);
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 }
//DeadCode ARM 12Sep97 
//DeadCode ARM 12Sep97 // End.
