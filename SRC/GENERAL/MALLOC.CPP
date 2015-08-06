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
//Filename       malloc.cpp
//System         Flying corp
//Author         Dave Whiteside
//Date           Wed 31 Jan 1996
//Description    Malloc stubs for the smacker stuff
//------------------------------------------------------------------------------
#include	<stdlib.h>
//TempCode DAW 17Nov97 #include	<i86.h>
#include	<dos.h>
#include	<stdio.h>
#include	<string.h>
#include	<dosdefs.h>
#include	<rad.h>												//DAW 31Jan96
//DeadCode ARM 18Jul96 #include	"smack.h"
#include	"myerror.h"

struct meminfo {
    unsigned LargestBlockAvail;
    unsigned MaxUnlockedPage;
    unsigned LargestLockablePage;
    unsigned LinAddrSpace;
    unsigned NumFreePagesAvail;
    unsigned NumPhysicalPagesFree;
    unsigned TotalPhysicalPages;
    unsigned FreeLinAddrSpace;
    unsigned SizeOfPageFile;
    unsigned Reserved[3];
} MemInfo;

#define DPMI_INT	0x31

void MemoryTest(char * poo)
{
//DeadCode ARM 04Jun96 	unsigned int	start=0x1000000;
//DeadCode ARM 04Jun96 	char*		next=NULL;
//DeadCode ARM 04Jun96 	char*		fiss=NULL;
//DeadCode ARM 04Jun96 	int			count=1;
//DeadCode ARM 04Jun96 
//DeadCode ARM 04Jun96 	INT3();
//DeadCode ARM 04Jun96 	fprintf(stderr,"About to Start %s\n",poo);
//DeadCode ARM 04Jun96 	while (start>4096)
//DeadCode ARM 04Jun96 	{
//DeadCode ARM 04Jun96 		fiss=new char[start];
//DeadCode ARM 04Jun96 		if (fiss)
//DeadCode ARM 04Jun96 		{
//DeadCode ARM 04Jun96 			fprintf(stderr,"Size alloced:\t%i\n",start);
//DeadCode ARM 04Jun96 			*((char **)fiss)=next;
//DeadCode ARM 04Jun96 			next=fiss;
//DeadCode ARM 04Jun96 			count++;
//DeadCode ARM 04Jun96 		}
//DeadCode ARM 04Jun96 		else
//DeadCode ARM 04Jun96 			start=(start-start/10);
//DeadCode ARM 04Jun96 	}
//DeadCode ARM 04Jun96 	while (next)
//DeadCode ARM 04Jun96 	{
//DeadCode ARM 04Jun96 		fiss=*((char **)next);
//DeadCode ARM 04Jun96 		delete[]next;
//DeadCode ARM 04Jun96 		next=fiss;
//DeadCode ARM 04Jun96 	}
//DeadCode ARM 04Jun96 
}



void memory()
{
//DeadCode ARM 04Jun96     union REGS regs;
//DeadCode ARM 04Jun96     struct SREGS sregs;
//DeadCode ARM 04Jun96 
//DeadCode ARM 04Jun96     regs.x.eax = 0x00000500;
//DeadCode ARM 04Jun96     memset( &sregs, 0, sizeof(sregs) );
//DeadCode ARM 04Jun96     sregs.es = FP_SEG( &MemInfo );
//DeadCode ARM 04Jun96     regs.x.edi = FP_OFF( &MemInfo );
//DeadCode ARM 04Jun96 
//DeadCode ARM 04Jun96     int386x( DPMI_INT, &regs, &regs, &sregs );
//DeadCode ARM 04Jun96 
//DeadCode ARM 04Jun96 	printf("%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n",
//DeadCode ARM 04Jun96 		MemInfo.LargestBlockAvail,
//DeadCode ARM 04Jun96 		MemInfo.MaxUnlockedPage,
//DeadCode ARM 04Jun96 		MemInfo.LargestLockablePage,
//DeadCode ARM 04Jun96 		MemInfo.LinAddrSpace,
//DeadCode ARM 04Jun96 		MemInfo.NumFreePagesAvail,
//DeadCode ARM 04Jun96 		MemInfo.NumPhysicalPagesFree,
//DeadCode ARM 04Jun96 		MemInfo.TotalPhysicalPages,
//DeadCode ARM 04Jun96 		MemInfo.FreeLinAddrSpace);
}

void*	ailmalloc(size_t numbytes)
{
  void * temp=0;
	if (numbytes==0)
		return(NULL);
	if (numbytes!=0xffffffff)
		temp=new char[numbytes];
	
	if (!temp)
	{
#ifdef __WATCOMC__
		INT3();													//JIM 19Jun97
#endif
#ifdef __MSVC__
		INT3;
#endif
		_Error.EmitSysErr("Smacker/Miles alloc Failed for %i.\n",numbytes);
	}
	return(temp);
}

/*
RCFUNC void PTR4* RADLINK radmalloc(u32 numbytes)
{
	return (void PTR4*) ailmalloc(numbytes);
}


void	ailfree(void* ptr)
{
  delete[](char*)ptr;
}

RCFUNC void RADLINK radfree(void PTR4* ptr)
{
  delete[](char*)ptr;
}



*/
