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

#include	"dosdefs.h"
#include	"fileman.h"
#include <malloc.h>

#ifdef __WATCOMC__
extern	ULong* sp();
#pragma aux	sp=	"mov ecx,esp"	value [ecx]
#else
#ifdef __MSVC__
inline ULong* sp()
{
	ULong*	retval;
    __asm
    {
		mov ecx,esp;
		mov retval,ecx;
    }
    return retval;
}

#endif
#endif

#ifdef	__SW_OD
	#define	STACKGAP	10
#else
	#define	STACKGAP	3
#endif

ULong* MemoryBase=NULL;
ULong	count=0;

//
// Simple linklist hung from MemoryBase
// Longword fields are:
//	0:	linklist
//	1:	revnum	- neg = delete
//	2:	size
//	3:	creator
//


void	*operator	new(size_t s)
{
	void* v=malloc(s+16);
//DeadCode JIM 28Oct96 	while (v==0)
//DeadCode JIM 28Oct96 	{
//DeadCode JIM 28Oct96 		if (fileman::MyMemFailPFU(s+16)==0)
//DeadCode JIM 28Oct96 			break;
//DeadCode JIM 28Oct96 		v=malloc(s+16);
//DeadCode JIM 28Oct96 	}
	if (v)
	{
		ULong* u=(ULong*)v;
		*(u++)=(ULong)MemoryBase;
		MemoryBase=(ULong*)v;
		*(u++)=count++;
		*(u++)=s;
		*(u++)=sp()[STACKGAP];
		v=u;
	}
	return	v;
}
void	*operator	new[](size_t s)
{
	void* v=malloc(s+16);
//DeadCode JIM 28Oct96 	while (v==0)
//DeadCode JIM 28Oct96 	{
//DeadCode JIM 28Oct96 		if (fileman::MyMemFailPFU(s+16)==0)
//DeadCode JIM 28Oct96 			break;
//DeadCode JIM 28Oct96 		v=malloc(s+16);
//DeadCode JIM 28Oct96 	}
	if (v)
	{
		ULong* u=(ULong*)v;
		*(u++)=(ULong)MemoryBase;
		MemoryBase=(ULong*)v;
		*(u++)=count++;
		*(u++)=s;
		*(u++)=sp()[STACKGAP];
		v=u;
	}
	return	v;
}
void	operator	delete(void* v)
{
	if (v)
	{
		v=(void*)((int)v-16);
		ULong* u=(ULong*)&MemoryBase;

		while (*u!=(ULong)v && u)
			u=(ULong*)*u;
		if (u==NULL)
#ifdef __WATCOMC__
			INT3();
#endif
#ifdef __MSVC__
		INT3;
#endif
//DeadCode JIM 28Oct96 			_Error.EmitSysErr("Bit of memory missiong");
		*u=*(ULong*)*u;
		((ULong*)v)[0]=0;
		((ULong*)v)[1]=-((ULong*)v)[1];
		free(v);
	}
}
void	operator	delete[](void* v)
{
	if (v)
	{
		v=(void*)((int)v-16);
		ULong* u=(ULong*)&MemoryBase;
		while (*u!=(ULong)v && u)
			u=(ULong*)*u;
		if (u==NULL)
#ifdef __WATCOMC__
			INT3();
#endif
#ifdef __MSVC__
		INT3;
#endif
//DeadCode JIM 28Oct96 			_Error.EmitSysErr("Bit of memory missiong");
		*u=*(ULong*)*u;
		((ULong*)v)[0]=0;
		((ULong*)v)[1]=-((ULong*)v)[1];
		free(v);
	}
}

extern "C"	int*	__nheapbeg;

void	TraceChain()
{
	int*	heapptr=__nheapbeg;
	int*   	memptr;
	int		usedmem=0;
	int		usedlumps=0;
	int		freemem=0;
	int		freelumps=0;
	int	numheaps=0;
	while (heapptr)
	{
		numheaps++;
		memptr=heapptr+11;
		while (*memptr!=-1)
		{
			if(*memptr&1)
			{
				usedmem+=*memptr&-2;
				usedlumps++;
			}
			else
			{
				freemem+=*memptr;
				freelumps++;
			}
			memptr=(int*)((int)memptr+*memptr&-2);
		}
		heapptr=(int*)heapptr[2];
		memptr=heapptr+11;
	}


}

