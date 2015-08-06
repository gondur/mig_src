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
//DeadCode ARM 03Nov97 void LoadCurvesATMOS ()
//DeadCode ARM 03Nov97 {
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  ATMOS  MinTemp  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT ATMOS_MinTemp [3] = {
//DeadCode ARM 03Nov97 	0.000000000000,288.000000000000,
//DeadCode ARM 03Nov97 	1100000.000000000000,216.600000000000,
//DeadCode ARM 03Nov97 	2500000.000000000000,216.600000000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("ATMOS",
//DeadCode ARM 03Nov97 			"MinTemp",
//DeadCode ARM 03Nov97 			3,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			2500000.000000000000,
//DeadCode ARM 03Nov97 			2,
//DeadCode ARM 03Nov97 			ATMOS_MinTemp);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  ATMOS  MaxTemp  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT ATMOS_MaxTemp [3] = {
//DeadCode ARM 03Nov97 	0.000000000000,288.000000000000,
//DeadCode ARM 03Nov97 	1100000.000000000000,216.600000000000,
//DeadCode ARM 03Nov97 	2500000.000000000000,216.600000000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("ATMOS",
//DeadCode ARM 03Nov97 			"MaxTemp",
//DeadCode ARM 03Nov97 			3,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			2500000.000000000000,
//DeadCode ARM 03Nov97 			2,
//DeadCode ARM 03Nov97 			ATMOS_MaxTemp);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  ATMOS  MinPres  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT ATMOS_MinPres [23] = {
//DeadCode ARM 03Nov97 	0.000000000000,9.625875000000,
//DeadCode ARM 03Nov97 	100000.000000000000,8.538600000000,
//DeadCode ARM 03Nov97 	200000.000000000000,7.552500000000,
//DeadCode ARM 03Nov97 	300000.000000000000,6.661400000000,
//DeadCode ARM 03Nov97 	400000.000000000000,5.857700000000,
//DeadCode ARM 03Nov97 	500000.000000000000,5.177500000000,
//DeadCode ARM 03Nov97 	600000.000000000000,4.485900000000,
//DeadCode ARM 03Nov97 	700000.000000000000,3.905450000000,
//DeadCode ARM 03Nov97 	800000.000000000000,3.388175000000,
//DeadCode ARM 03Nov97 	900000.000000000000,2.926000000000,
//DeadCode ARM 03Nov97 	1000000.000000000000,2.517500000000,
//DeadCode ARM 03Nov97 	1100000.000000000000,2.156500000000,
//DeadCode ARM 03Nov97 	1200000.000000000000,1.843000000000,
//DeadCode ARM 03Nov97 	1300000.000000000000,1.575100000000,
//DeadCode ARM 03Nov97 	1400000.000000000000,1.346150000000,
//DeadCode ARM 03Nov97 	1500000.000000000000,1.150450000000,
//DeadCode ARM 03Nov97 	1600000.000000000000,0.983250000000,
//DeadCode ARM 03Nov97 	1700000.000000000000,0.840750000000,
//DeadCode ARM 03Nov97 	1800000.000000000000,0.718675000000,
//DeadCode ARM 03Nov97 	1900000.000000000000,0.614365000000,
//DeadCode ARM 03Nov97 	2000000.000000000000,0.525255000000,
//DeadCode ARM 03Nov97 	2200000.000000000000,0.384465000000,
//DeadCode ARM 03Nov97 	2400000.000000000000,0.282340000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("ATMOS",
//DeadCode ARM 03Nov97 			"MinPres",
//DeadCode ARM 03Nov97 			23,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			2400000.000000000000,
//DeadCode ARM 03Nov97 			2,
//DeadCode ARM 03Nov97 			ATMOS_MinPres);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // ****  ATMOS  MaxPres  **** //
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 CURVEPNT ATMOS_MaxPres [23] = {
//DeadCode ARM 03Nov97 	0.000000000000,10.639125000000,
//DeadCode ARM 03Nov97 	100000.000000000000,9.437400000000,
//DeadCode ARM 03Nov97 	200000.000000000000,8.347500000000,
//DeadCode ARM 03Nov97 	300000.000000000000,7.362600000000,
//DeadCode ARM 03Nov97 	400000.000000000000,6.474300000000,
//DeadCode ARM 03Nov97 	500000.000000000000,5.722500000000,
//DeadCode ARM 03Nov97 	600000.000000000000,4.958100000000,
//DeadCode ARM 03Nov97 	700000.000000000000,4.316550000000,
//DeadCode ARM 03Nov97 	800000.000000000000,3.744825000000,
//DeadCode ARM 03Nov97 	900000.000000000000,3.234000000000,
//DeadCode ARM 03Nov97 	1000000.000000000000,2.782500000000,
//DeadCode ARM 03Nov97 	1100000.000000000000,2.383500000000,
//DeadCode ARM 03Nov97 	1200000.000000000000,2.037000000000,
//DeadCode ARM 03Nov97 	1300000.000000000000,1.740900000000,
//DeadCode ARM 03Nov97 	1400000.000000000000,1.487850000000,
//DeadCode ARM 03Nov97 	1500000.000000000000,1.271550000000,
//DeadCode ARM 03Nov97 	1600000.000000000000,1.086750000000,
//DeadCode ARM 03Nov97 	1700000.000000000000,0.929250000000,
//DeadCode ARM 03Nov97 	1800000.000000000000,0.794325000000,
//DeadCode ARM 03Nov97 	1900000.000000000000,0.679035000000,
//DeadCode ARM 03Nov97 	2000000.000000000000,0.580545000000,
//DeadCode ARM 03Nov97 	2200000.000000000000,0.424935000000,
//DeadCode ARM 03Nov97 	2400000.000000000000,0.312060000000
//DeadCode ARM 03Nov97 };
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 new CURVE ("ATMOS",
//DeadCode ARM 03Nov97 			"MaxPres",
//DeadCode ARM 03Nov97 			23,
//DeadCode ARM 03Nov97 			0.000000000000,
//DeadCode ARM 03Nov97 			2400000.000000000000,
//DeadCode ARM 03Nov97 			2,
//DeadCode ARM 03Nov97 			ATMOS_MaxPres);
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 }
//DeadCode ARM 03Nov97 
//DeadCode ARM 03Nov97 // End.
