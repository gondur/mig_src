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

void LoadCurvesF82G ()
{



// ****  F82G  Cl  **** //

CURVEPNT F82G_Cl [13] = {
	0.243288321046,1.711431000000,
	0.285599343267,1.770108000000,
	0.370221370255,1.648352000000,
	0.518309921847,1.526362000000,
	1.026042066323,1.526362000000,
	1.570796361786,0.000000000000,
	1.925151100890,-1.078060000000,
	2.967059728550,-1.600000000000,
	3.316125578968,1.600000000000,
	4.014257279803,1.200000000000,
	4.712388998091,0.000000000000,
	5.405231949867,-1.066085000000,
	6.039897161005,-1.327760000000
};

new CURVE ("F82G",
			"Cl",
			13,
			0.000000000000,
			6.283185482051,
			1,
			F82G_Cl);


// ****  F82G  Cd  **** //

CURVEPNT F82G_Cd [20] = {
	0.000000000000,0.022099000000,
	0.042311004767,0.032360000000,
	0.087266462604,0.048539000000,
	0.160649633860,0.092343000000,
	0.239321676348,0.159036000000,
	0.322621476801,0.265191000000,
	0.412532375022,0.457770000000,
	0.687553958370,1.366458000000,
	0.962575559171,1.838736000000,
	1.248174902438,1.970974000000,
	1.565507490553,2.002459000000,
	2.432883262818,1.594249000000,
	3.001966243779,0.030000000000,
	3.281219011379,0.030000000000,
	3.839724459314,1.600551000000,
	4.707100231579,2.003839000000,
	5.563898261378,1.594249000000,
	5.964530667400,0.118670000000,
	6.095430361307,0.030391000000,
	6.193935679644,0.010269000000
};

new CURVE ("F82G",
			"Cd",
			20,
			0.000000000000,
			6.283185482051,
			1,
			F82G_Cd);


// ****  F82G  CompCd  **** //

CURVEPNT F82G_CompCd [17] = {
	0.000000000000,1.000000000000,
	0.600000000000,1.000000000000,
	0.715000000000,1.150000000000,
	0.814815000000,1.553144000000,
	0.882155000000,2.247102000000,
	0.929293000000,3.106289000000,
	0.952862000000,4.031566000000,
	0.969697000000,5.617756000000,
	0.995000000000,10.000000000000,
	1.000000000000,10.892056000000,
	1.026936000000,11.433650000000,
	1.067340000000,11.253119000000,
	1.090909000000,10.470816000000,
	1.164983000000,6.318596000000,
	1.252525000000,5.355762000000,
	1.400000000000,5.000000000000,
	2.000000000000,5.000000000000
};

new CURVE ("F82G",
			"CompCd",
			17,
			0.000000000000,
			2.000000000000,
			2,
			F82G_CompCd);


// ****  F82G  Cm  **** //

CURVEPNT F82G_Cm [11] = {
	0.000000000000,0.020000000000,
	0.244346095292,0.020000000000,
	0.314159265376,0.200000000000,
	1.570796361786,0.000000000000,
	2.932153230775,0.200000000000,
	3.001966243779,0.020000000000,
	3.246312373978,0.020000000000,
	3.316125631328,0.200000000000,
	4.712388998091,0.000000000000,
	5.951572889247,0.200000000000,
	6.038839334398,0.020000000000
};

new CURVE ("F82G",
			"Cm",
			11,
			0.000000000000,
			6.283185482051,
			1,
			F82G_Cm);


// ****  F82G  TailCl  **** //

CURVEPNT F82G_TailCl [8] = {
	0.244346095292,1.600000000000,
	0.698131683382,0.400000000000,
	2.443460935470,-0.400000000000,
	2.897246593373,-1.600000000000,
	3.385938644331,1.600000000000,
	3.839724302234,0.400000000000,
	5.585053449603,-0.400000000000,
	6.038839334398,-1.600000000000
};

new CURVE ("F82G",
			"TailCl",
			8,
			0.000000000000,
			6.283185482051,
			1,
			F82G_TailCl);


// ****  F82G  FinCl  **** //

CURVEPNT F82G_FinCl [8] = {
	0.244346095292,1.600000000000,
	0.698131683382,0.400000000000,
	2.443460935470,-0.400000000000,
	2.897246593373,-1.600000000000,
	3.385938644331,1.600000000000,
	3.839724302234,0.400000000000,
	5.585053449603,-0.400000000000,
	6.038839334398,-1.600000000000
};

new CURVE ("F82G",
			"FinCl",
			8,
			0.000000000000,
			6.283185482051,
			1,
			F82G_FinCl);

// ****  F82G  Power100  **** //

CURVEPNT F82G_Power100 [15] = {
	   0.0000,     0.0000,
	 589.0011,	 142.5876,
	1156.4534,	 356.4690,
	1666.4422,	 641.6443,
	2126.1504,	1013.9564,
	2514.0292,	1362.5039,
	2837.2615,	1584.3069,
	3038.3838,	1687.2868,
	3200.0000,	1710.0000,
	3332.8844,	1655.6007,
	3454.9944,	1520.9346,
	3648.9338,	1180.3086,
	3878.7879,	 677.2889,
	4112.2334,   -15.2200,
	5333.3333, -4243.7956
};

new CURVE ("F82G",
			"Power100",
			15,
			0.000000000000,
			5333.3333,
			2,
			F82G_Power100);


// ****  F82G  Power0  **** //

CURVEPNT F82G_Power0 [7] = {
	   0.0000,		0.1067,
	1059.4837,    -50.6050,
	1960.9428,	 -199.8657,
	2887.5421,	 -647.8406,
	3663.2997,	-1357.7084,
	4525.2525,	-2588.3853,
	5351.2907,	-4402.0157
};

new CURVE ("F82G",
			"Power0",
			7,
			0.000000000000,
			5351.2907,
			2,
			F82G_Power0);


// ****  F82G  PowerAlt  **** //

CURVEPNT F82G_PowerAlt [8] = {
	    0.0,	0.93550,	//CSB
	 8500.0,	1.00000,
	14000.0,	0.81509,
	21400.0,	0.61069,
	30000.0,	0.42201,
	40000.0,	0.25220,
	50000.0,	0.12390,
	60000.0,	0.03082
};

new CURVE ("F82G",
			"PowerAlt",
			8,
			0.000000000000,
			60000.000000000000,
			2,
			F82G_PowerAlt);

// ****  F82G  PowerAltSuper (High Blower)  **** //	CSB

CURVEPNT F82G_PowerAltSuper [8] = {
	    0.0,	0.852077496,	//CSB
	 8500.0,	0.910812496,
	14000.0,	0.948817496,
	21400.0,	0.999951496,
	30000.0,	0.719730072,
	40000.0,	0.449784206,
	50000.0,	0.23993834,
	60000.0,	0.090192474
};

new CURVE ("F82G",
			"PowerAltSuper",
			8,
			0.000000000000,
			60000.000000000000,
			2,
			F82G_PowerAltSuper);



}

// End.
