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
//Filename       doserror.cpp
//System         
//Author         Martin Alderton   
//Date           Fri 6 Oct 1995
//Description    
//------------------------------------------------------------------------------

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<conio.h>										//pd 01Nov95
#include	<dos.h>										//pd 01Nov95
#include	"DosDefs.h"
//DeadCode DAW 01Mar96 #include	"Files.g"
#include	"Palette.h"
//DeadCode DAW 15Apr96 #include	"screen.h"
#include	"wrapper.h"
#include	"myerror.h"
//DeadCode DAW 19Mar96 #include	"getset.h"
#include	"myAngles.H"	

#include	"WorldInc.H"
#include	"World.h"

#include	"main.h"

extern Main 	_Main;
//DeadCode PD 26Oct95 extern Wrapper	_Wrapper;

Error	_Error;

extern		void	TraceChain(int x);
extern		void	TrackMemUse();

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Error
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Error::Error()
{
	exitmsg=NULL;

//DeadCode DAW 10Apr96 	#if	DEBUGGING
//DeadCode DAW 10Apr96 		OpenLog();
//DeadCode DAW 10Apr96 	#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Error
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Error::~Error()
{
//DeadCode DAW 10Apr96 	#if	DEBUGGING
//DeadCode DAW 10Apr96 		CloseLog();
//DeadCode DAW 10Apr96 	#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Error::EmitSysErr
//------------------------------------------------------------------------------
//Author	Martin Alderton   
//Date		Friday 6 Oct 1995
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
//DeadCode JIM 02Jul96 void Error::EmitSysErr(char *fmt, ...)
//DeadCode JIM 02Jul96 {
//DeadCode JIM 02Jul96 	va_list	marker;
//DeadCode JIM 02Jul96 
//DeadCode JIM 02Jul96 	va_start(marker, fmt);
//DeadCode JIM 02Jul96 
//DeadCode JIM 02Jul96 	_Main.QuitGame();
//DeadCode JIM 02Jul96 
//DeadCode JIM 02Jul96 	fprintf(stdout, "ERROR! ");
//DeadCode JIM 02Jul96 	vfprintf(stdout, fmt, marker);
//DeadCode JIM 02Jul96 	fprintf(stdout, "\n");
//DeadCode JIM 02Jul96 
//DeadCode JIM 02Jul96 	exit(0);
//DeadCode JIM 02Jul96 }

extern	void TraceChain();
Error&	Error::ExitMode()
{
#ifdef __WATCOMC__
	INT3();
#endif
#ifdef __MSVC__
	INT3;
#endif
	//DAW 28Oct96
	if (exitmsg==NULL)
	{
		exitmsg="ERROR! ";
//TempCode DAW 19Nov96 		TraceChain(0);
//TempCode DAW 19Nov96 		TrackMemUse();
	}
	_Main.QuitGame();
	fprintf(stdout, exitmsg);
	return *this;
}

Error& Error::Say(char *fmt, ...)
{
	va_list	marker;

	va_start(marker, fmt);


	vfprintf(stdout, fmt, marker);
	return *this;
}

Error& Error::SayAndQuit(char *fmt, ...)
{
	va_list	marker;

	va_start(marker, fmt);

	vfprintf(stdout, fmt, marker);
	Quit();
	return *(Error*)NULL;
}

void Error::Quit()
{
	fprintf(stdout,"\n");
#ifdef __WATCOMC__
	INT3();
#endif
#ifdef __MSVC__
	INT3;
#endif
	exit(1);
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		screenswap
//Author		Paul.   
//Date			Fri 20 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode ARM 05Aug96 void Error::screenswap(Display *screen)							//JIM 12Dec95
//DeadCode ARM 05Aug96 {
//DeadCode ARM 05Aug96 	screen->ScreenSwap();								//PD 29Nov95
//DeadCode ARM 05Aug96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OpenLog
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Error::OpenLog()
{

	#if	DEBUGGING
	if((logfile = fopen("main.log","wt"))==NULL)
		EmitSysErr(__FILE__":Can't open log file.");

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WriteToLog
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Error::WriteToLog(char *fmt,...)
{
	va_list marker;

	va_start(marker,fmt);

	vfprintf(logfile,fmt,marker);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseLog
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Error::CloseLog()
{
	fclose(logfile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KeyTrap
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Error::KeyTrap()
{
	char	c;
	if(kbhit())
	{
		c=getch()&0x00FF;
		if(c==' ')
#ifdef __WATCOMC__
	INT3();
#endif
#ifdef __MSVC__
	INT3;
#endif
	}
}

	#endif

//Old_Code PD 16Jan96 	#if	DEBUGGING
//Old_Code PD 16Jan96 
//Old_Code PD 16Jan96 	#include	<stddef.h>
//Old_Code PD 16Jan96 	#include	<stdlib.h>
//Old_Code PD 16Jan96 
//Old_Code PD 16Jan96 
//Old_Code PD 16Jan96 static SLong malloced=0;
//Old_Code PD 16Jan96 
//Old_Code PD 16Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Old_Code PD 16Jan96 //Procedure		my_malloc
//Old_Code PD 16Jan96 //Author		Paul.   
//Old_Code PD 16Jan96 //Date			Tue 16 Jan 1996
//Old_Code PD 16Jan96 //
//Old_Code PD 16Jan96 //Description	Replacement for 'new'
//Old_Code PD 16Jan96 //
//Old_Code PD 16Jan96 //Inputs		
//Old_Code PD 16Jan96 //
//Old_Code PD 16Jan96 //Returns	
//Old_Code PD 16Jan96 //
//Old_Code PD 16Jan96 //------------------------------------------------------------------------------
//Old_Code PD 16Jan96 void *my_malloc(size_t s)
//Old_Code PD 16Jan96 {
//Old_Code PD 16Jan96 	void *retval;
//Old_Code PD 16Jan96 	if((retval=malloc(s))==NULL)
//Old_Code PD 16Jan96 	{
//Old_Code PD 16Jan96 		retval=(void *)0x0A0000;
//Old_Code PD 16Jan96 		INT3();
//Old_Code PD 16Jan96 	}
//Old_Code PD 16Jan96 
//Old_Code PD 16Jan96 	malloced+=(SLong)s;
//Old_Code PD 16Jan96 
//Old_Code PD 16Jan96 	return(retval);
//Old_Code PD 16Jan96 }
//Old_Code PD 16Jan96 
//Old_Code PD 16Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Old_Code PD 16Jan96 //Procedure		my_delete
//Old_Code PD 16Jan96 //Author		Paul.   
//Old_Code PD 16Jan96 //Date			Tue 16 Jan 1996
//Old_Code PD 16Jan96 //
//Old_Code PD 16Jan96 //Description	
//Old_Code PD 16Jan96 //
//Old_Code PD 16Jan96 //Inputs		
//Old_Code PD 16Jan96 //
//Old_Code PD 16Jan96 //Returns	
//Old_Code PD 16Jan96 //
//Old_Code PD 16Jan96 //------------------------------------------------------------------------------
//Old_Code PD 16Jan96 void my_delete(void *p)
//Old_Code PD 16Jan96 {
//Old_Code PD 16Jan96 	malloced-=*((SLongP )p-4);
//Old_Code PD 16Jan96 	free(p);
//Old_Code PD 16Jan96 }
//Old_Code PD 16Jan96 	#endif
