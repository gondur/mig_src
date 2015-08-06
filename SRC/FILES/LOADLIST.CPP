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
//Filename       loadlist.cpp
//System         
//Author         Dave Whiteside
//Date           Mon 16 Dec 1996
//Description    Loads  a list of files...
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#define		F_GRAFIX											//JIM 01Aug96
#include	"files.G"
#include	"fileman.h"
#include	"myangles.h"
#include	"worldinc.h"
#include	"mymath.h"
#include 	"imagemap.h"
#include	"Shapes.h"
#include	"Miles.h"


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		preload
//Author		Robert Slater
//Date			Mon 2 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	fileman::preload()
{
//DeadCode AM 14Jan97 	fileblock	pl(FIL_PRELOAD_LIST);
//DeadCode AM 14Jan97 	char* t=(char*)getdata(pl);
//DeadCode AM 14Jan97 	FileNum f;
//DeadCode AM 14Jan97 	while (*t<'0')	t++;
//DeadCode AM 14Jan97 	f=(FileNum)Math_Lib.a2iend(t);
//DeadCode AM 14Jan97 	while(f)
//DeadCode AM 14Jan97 		if (dirnum(f)==dirnum(FIL_SUN_NUM))
//DeadCode AM 14Jan97 		{
//DeadCode AM 14Jan97 
//DeadCode AM 14Jan97 			fileblock z(f,shapestuff::FixupShapeFile);
//DeadCode AM 14Jan97 			while (*t<'0')	t++;
//DeadCode AM 14Jan97 			f=(FileNum)Math_Lib.a2iend(t);
//DeadCode AM 14Jan97 		}
//DeadCode AM 14Jan97 		else
//DeadCode AM 14Jan97 		{
//DeadCode AM 14Jan97 			if (dirnum(f)==dirnum(FIL_MUSIC_BASE))				//JIM 15Dec96
//DeadCode AM 14Jan97 				if (f!=FIL_MUSIC_SPOT_EFFECTS)					//DAW 17Dec96
//DeadCode AM 14Jan97 					f=(FileNum)(f+_Miles.MusicDir);					//JIM 15Dec96
//DeadCode AM 14Jan97 			fileblock z(f);
//DeadCode AM 14Jan97 			while (*t<'0')	t++;
//DeadCode AM 14Jan97 			f=(FileNum)Math_Lib.a2iend(t);
//DeadCode AM 14Jan97 		}
//DeadCode AM 14Jan97 
}
