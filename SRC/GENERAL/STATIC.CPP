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

//------------------------------------------------------------------------------
//Filename       static.cpp
//System         
//Author         Jim Taylor
//Date           Thu 16 Nov 1995
//Description    Place any loose static class field initialisers in here
//				I expect most static class field inialisers to be placed
//				with their associated routines such as constructor and new.
//				Please place immediately after the include file which defines them
//------------------------------------------------------------------------------
#include	"dosdefs.h"
#include	"FileMan.h"
#include	"TextRef.h"

//------------------------------------------------------------------------------
#include	"worldinc.h"
ULong		ItemBase::desposrange=0;
COORDS3D 	ItemBase::despos;										//RDH 27Feb96
ANGLES	item::PitchIntercept;
ANGLES	item::HdgIntercept;
SLong	item::Range;

//------------------------------------------------------------------------------
#include	"display.h"
Bool	Graphic::locked=FALSE;									//AMM 02May97
UByte	Graphic::locklevel=0;								//AMM 02May97
DirectDDP  _DirectDraw::lpDirectDD=NULL;
//Direct3DP  _DirectDraw::lpDirect3D=NULL;
//------------------------------------------------------------------------------
//Next??

//#define F_SOUNDS												//DAW 05Aug96
//#define F_COMMON												//DAW 05Aug96
//#include	"files.g"		//NON-GRAPHICS FILES				//JIM 14May96
//DeadCode JIM 30Apr96 #include	"miss_man.h"										//DAW 17Jan96
//#include	"ui.h"												//JIM 30Apr96
//#include	"briefing.h"												//JIM 30Apr96

//#include	"missman2.h" 	//special double-include

//MissMan	Miss_Man ;

