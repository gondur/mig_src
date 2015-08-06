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

// RowTasks.cpp: implementation of the RowanTasks class.
//
//////////////////////////////////////////////////////////////////////

//#include ""
//#include "MIG.h"
#include "dosdefs.h"
#include	"stdafx.h"
#include "RowTasks.h"

#ifdef _DEBUG
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Statics	 enum	{MAX_TASKS=32,MAX_IGNORES=512,MAX_STACKINGS=2048}
//////////////////////////////////////////////////////////////////////

#ifdef	STACKLOGGINGENABLED
	#define	ALLOWLOGBIGARRAY	hello
#else
	#define	ALLOWLOGBIGARRAY	1 + 0*(int) /**/
#endif
//As each task starts, it's stack address is logged here.
//A call with lower stack address is the same task.
//If this table is empty then no logging can take place
ULong		RowanTasks::taskstacks[MAX_TASKS]={0};
//sanity checks... was last caller same as the return address being logged?
//If not, logging must be disabled, as using pascal style ret n (probably)
int		RowanTasks::lastcaller[ALLOWLOGBIGARRAY MAX_TASKS];		
int		RowanTasks::laststack[ALLOWLOGBIGARRAY MAX_TASKS];

//Until tasks are logged, they can't be stacked. 
//This table logs top level routines that contain logging code 
//and therefore can't be logged themsselves
void*	RowanTasks::RoutinesToIgnore[]=
{

	0
};


//This table logs statistics for 
StackTimes	RowanTasks::stacktimes[ALLOWLOGBIGARRAY MAX_LOGS];

//These tables match the jump/call table of exit procedures
int		RowanTasks::RoutineAddresses[ALLOWLOGBIGARRAY MAX_STACKINGS];
int		RowanTasks::ReturnAddresses[ALLOWLOGBIGARRAY MAX_STACKINGS];
int		RowanTasks::StartTimes[ALLOWLOGBIGARRAY MAX_STACKINGS];

int		RowanTasks::semaphore=0;
int		RowanTasks::lasttasknum=0;



RowanTasks	Rowan_Task;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RowanTasks::RowanTasks()
{
	StartTask();
}

RowanTasks::~RowanTasks()
{
	EndTask();
}

#define	stackdelta
int		RowanTasks::StartTask()
{
	int	count=lasttasknum;
	while (count<MAX_TASKS)
		breakif (taskstacks[++count]==0);
	if (count==MAX_TASKS)
		for (count=0;count<lasttasknum;)
			breakif (taskstacks[++count]==0);
	if (count==lasttasknum)
		INT3;	//oh dear... run out of tasks?
	taskstacks[count]=ULong(&count);	//get address of local variable...
	return count;
}

void	RowanTasks::EndTask()
{
	int	task=GetCurrTask();
	if (task>=0)
		taskstacks[task]=0;
}

int		RowanTasks::GetCurrTask()
{
	ULong testval=ULong(&testval);
	ULong	lowestvalueabove=0xffffffff;
	int	entforlowest=-1;
	int	count;
	for (count=0;count<MAX_TASKS;count++)
		if (taskstacks[count]>testval && taskstacks[count]<lowestvalueabove)
		{
			lowestvalueabove=taskstacks[count];
			entforlowest=count;
		}
	return count;
}

