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
//Filename       getset.cpp
//System         
//Author         Paul.   
//Date           Mon 24 Jul 1995
//Description    
//------------------------------------------------------------------------------

#include	<stdlib.h>

#include	"DOSDefs.H"
//DeadCode DAW 15Apr96 #include	"Screen.H"
#include	"GetSet.H"
#include	"keytest.h"
#include	"fileman.h"

#ifndef	PUBLICVERSION
	#include	<stdio.h>
//DeadCode DAW 24Jan96 	#include	<stdlib.h>
	#include	<conio.h>
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GetSet
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Mon 7 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
GetSet::GetSet()
{
//TempCode JIM 12Dec95  	GetSet::Mode = MODE_320x200;	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	ReadArgs
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Mon 24 Jul 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void GetSet::ReadArgs(int argc, char *argv[])
{
	string	s;
	//Default values
//Old_Code DAW 10May96 	width=320;
//Old_Code DAW 10May96 	height=200;													//PD 19Dec95
	width=640;													//DAW 10May96
	height=480;													//DAW 10May96
	colourdepth=8;

//TempCode JIM 12Dec95 	Mode = MODE_320x200;

	//Read command line for any variations on the default values

	FILEMAN.errhandle=NULL;
	while(argc--)
	{
		if(*argv[argc] == '/' || *argv[argc] == '-')
		{
			switch(argv[argc][1])
			{
				case	'F':
				case	'f':
					FILEMAN.errhandle=stderr;

				break;					//-Mbdrs
				case	'M':			//s, single screen flipping mode forced
				case	'm':			//b, bit depth  is one of T=24,H=15,V=8
					s=argv[argc];		//d, physical debug is set with D
					s+=2;				//r, resolution is a number
					while	((*s>='A' && *s<='Z') || (*s>='a' && *s<='z'))//PD 20Jun96
						switch(*s++)
						{
						case	't':
						case	'T':
							if (colourdepth<0)	colourdepth=-24;
							else				colourdepth=24;
						break;
						case  	'h':
						case  	'H':
							if (colourdepth<0)	colourdepth=-15;
							else				colourdepth=15;
						break;
						case	'v':
						case	'V':
							if (colourdepth<0)	colourdepth=-8;
							else				colourdepth=8;
						break;
						case	'd':
						case	'D':
							colourdepth=-colourdepth;
						break;
						case	's':
						case	'S':
							width=-width;
						break;
						default:;
						}
					if ((*s>='0')&&(*s<='9'))
						if (width<0)
							width=-atoi(s);
						else
							width=atoi(s);
			}
		}
	}
 	height=(width*3)/4;
	#ifndef	PUBLICVERSION

	//Debug to display initial setup read from cmd line
	GetSet::EchoParameters();

	#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadArgsInstall
//Author		Dave Whiteside
//Date			Wed 10 Apr 1996
//
//Description	A stub to make the install happy
//
//Inputs		nufin
//
//Returns		640x480 mode set
//
//------------------------------------------------------------------------------
void	GetSet::ReadArgsInstall(int argc, char *argv[])
{
	width=640;
	height=480;
	colourdepth=8;
	string	s;

	FILEMAN.errhandle=NULL;
	while(argc--)
	{
		if(*argv[argc] == '/' || *argv[argc] == '-')
		{
			switch(argv[argc][1])
			{
				case	'F':
				case	'f':
					FILEMAN.errhandle=stderr;

				break;
				case	'M':			//-Mbdr
				case	'm':			//b, bit depth  is one of T=24,H=15,V=8
					s=argv[argc];		//d, physical debug is set with D
					s+=2;				//r, resolution is a number
					while	(*s>='A')
						switch(*s++)
						{
						case	't':
						case	'T':
							if (colourdepth<0)	colourdepth=-24;
							else				colourdepth=24;
						break;
						case  	'h':
						case  	'H':
							if (colourdepth<0)	colourdepth=-15;
							else				colourdepth=15;
						break;
						case	'v':
						case	'V':
							if (colourdepth<0)	colourdepth=-8;
							else				colourdepth=8;
						break;
						case	'd':
						case	'D':
							colourdepth=-colourdepth;
						break;
						default:;
						}
					if ((*s>='0')&&(*s<='9'))
						width=atoi(s);
			}
		}
	}
 	height=(width*3)/4;
}


	#ifndef	PUBLICVERSION
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	EchoParameters
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Mon 24 Jul 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void GetSet::EchoParameters()
{
//DeadCode JIM 12Dec95 	static char	*mode_320x200debug = "Single screen 320 x 200 @ 256 colours.";
//DeadCode JIM 12Dec95 	static char	*mode_320x200 = "Three screen 320 x 200 @ 256 colours.";
//DeadCode JIM 12Dec95 	static char	*mode_640x480 = "640 x 480 @ 256 colours.";
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 	char *mode_selected;


//TempCode JIM 12Dec95 	switch(Mode)
//TempCode JIM 12Dec95 	{
//TempCode JIM 12Dec95 		default:
//TempCode JIM 12Dec95 		case MODE_320x200:
//DeadCode JIM 12Dec95 			mode_selected = mode_320x200;
//TempCode JIM 12Dec95 			break;
//TempCode JIM 12Dec95 		case MODE_320x200Debug:
//TempCode JIM 12Dec95 			mode_selected = mode_320x200debug;
//TempCode JIM 12Dec95 			break;
//TempCode JIM 12Dec95 		case MODE_640x480:
//TempCode JIM 12Dec95 			mode_selected = mode_640x480;
//TempCode JIM 12Dec95 			break;
//TempCode JIM 12Dec95 	}

	fprintf(stdout,"================================================================================");
	fprintf(stdout,"GetSet::EchoParamters\n");
	fprintf(stdout,"================================================================================");
	fprintf(stdout,"Video Mode : %i bit. %ix%i pixels\n",
				colourdepth,width,height);

//DeadCode DAW 24Oct96 	fprintf(stdout,"\n\nPress <ENTER> to continue.\n");
UIKeyEvent mykeyevent;											//PD 30Nov95
//TempCode PD 26Jan96 	while (Key_Tests.GetUIKey(mykeyevent)==FALSE);				//PD 30Nov95
//DeadCode DAW 11Jan96 	while (Key_Tests.GetUIKey(mykeyevent)==FALSE);				//PD 30Nov95
//DeadCode JIM 12Dec95 int	i=1000000;													//PD 30Nov95
//DeadCode JIM 12Dec95 	while(i--);													//PD 30Nov95
//DeadCode JIM 12Dec95 	fprintf(stdout,"\n\nPress <ENTER> to continue.\n");			//PD 30Nov95
//DeadCode JIM 12Dec95 	while (Key_Tests.GetUIKey(mykeyevent)==FALSE);				//PD 30Nov95
//DeadCode JIM 12Dec95 	fprintf(stdout,"\n\nPress <ENTER> to continue.\n");			//PD 30Nov95
}
	#endif

