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
#include	"monotxt.h"
#include <malloc.h>
#include	"stdio.h"											//ARM 10Dec96
#include	"string.h"											//ARM 10Dec96

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
//	1:	creator
//	2:	deletor: 0 = allocated
//	3:	size   
//
//	When deleted the first 2 fields are stomped by the system free chain
//  Size is last so that it looks like a system allocation size field
//
#define	EMPTYPOINTERSBASE 0xE0000000
int	EMPTYPOINTERS=EMPTYPOINTERSBASE;


void	*operator	new(size_t s)
{
	if (s)
	{
		void* v=malloc(s+16);
		while (v==0)                                                                                                   
		{
			if (fileman::MyMemFailPFU(s+16)==0)
				break;
			v=malloc(s+16);
		}
		if (v)
		{
			ULong* u=(ULong*)v;
			*(u++)=(ULong)MemoryBase;
			MemoryBase=(ULong*)v;
			*(u++)=sp()[STACKGAP];
			*(u++)=0;
			*(u++)=s;
			v=u;
	//Old_Code PD 16Dec96 		for (;s;s-=4)									//DAW 29Oct96
	//Old_Code PD 16Dec96 			*(u++)=0x0;											//PD 16Dec96
		}
		return	v;
	}
	else
	{
		return((void*)EMPTYPOINTERS++);
	}
}
void	*operator	new[](size_t s)
{
	if (s)
	{
		void* v=malloc(s+16);
		while (v==0)
		{
			if (fileman::MyMemFailPFU(s+16)==0)
				break;
			v=malloc(s+16);
		}
		if (v)
		{
			ULong* u=(ULong*)v;
			*(u++)=(ULong)MemoryBase;
			MemoryBase=(ULong*)v;
			*(u++)=sp()[STACKGAP];
			*(u++)=0;
			*(u++)=s;
			v=u;
	//Old_Code PD 16Dec96 		for (;s;s--)									//DAW 29Oct96
	//Old_Code PD 16Dec96 			*(u++)=0x0;											//PD 16Dec96
		}
		return	v;
	}
	else
	{
		return((void*)EMPTYPOINTERS++);
	}
}
void	operator	delete(void* v)
{
	ULong* t1,t2;
	if (v)
	{
		if ((int)v>=EMPTYPOINTERSBASE && (int)v<EMPTYPOINTERS)
			return;
		v=(void*)((int)v-16);
		ULong* u=(ULong*)&MemoryBase;

		while (*u!=(ULong)v && u)
			u=(ULong*)*u;
		if (u==NULL)
			if (_Error.exitmsg)							//MS 05Dec96
				return;
			else
				_Error.EmitSysErr("Bit of memory [] missing");
		*u=*(ULong*)*u;
		((ULong*)v)[0]=0;
		((ULong*)v)[2]=sp()[STACKGAP];
		free(v);
	}
}
void	operator	delete[](void* v)
{
	ULong* t1,t2;
	if (v)
	{
		if ((int)v>=EMPTYPOINTERSBASE && (int)v<EMPTYPOINTERS)
			return;
		v=(void*)((int)v-16);
		ULong* u=(ULong*)&MemoryBase;
		while (*u!=(ULong)v && u)
			u=(ULong*)*u;
		if (u==NULL)
			if (_Error.exitmsg)							//MS 05Dec96
				return;
			else
				_Error.EmitSysErr("Bit of memory [] missing");
		*u=*(ULong*)*u;
		((ULong*)v)[0]=0;
		((ULong*)v)[2]=sp()[STACKGAP];
		free(v);
	}
}

extern "C"	int*	__nheapbeg;

void	TraceChain(int yoff)
{
	int*	heapptr=__nheapbeg;
	int*   	memptr;
	SLong	usedmem=0;
	SLong	freemem=0;
	SLong	cachedmem=0;
	SLong	biggestfrag=0;
	SLong	numheaps=0;
	while (heapptr)
	{
		numheaps++;
		memptr=heapptr+11;
		while (*memptr!=-1)
		{
			if(*memptr&1)
				if (memptr[2]&0xf0000000)
					cachedmem+=*memptr&-2;
				else
					usedmem+=*memptr&-2;
			else
			{
				freemem+=*memptr;
				if (*memptr>biggestfrag)
					biggestfrag=*memptr;
			}
			memptr=(int*)((int)memptr+*memptr&-2);
		}
		heapptr=(int*)heapptr[2];

	}

	Mono_Text.PrintAt(0,0+yoff,(UByte*)"Use");
	Mono_Text.PrintHexAt(4,0+yoff,usedmem,7);

	Mono_Text.PrintAt(0,1+yoff,(UByte*)"Fr");
	Mono_Text.PrintHexAt(4,1+yoff,freemem,7);
	Mono_Text.PrintAt(0,2+yoff,(UByte*)"Big");
	Mono_Text.PrintHexAt(4,2+yoff,biggestfrag,7);
	Mono_Text.PrintAt(0,3+yoff,(UByte*)"Fil");
	Mono_Text.PrintHexAt(4,3+yoff,cachedmem,7);

	FILE* file;													//ARM 10Dec96
	file = fopen ("memdbg1.txt", "wt");							//ARM 10Dec96

	if (file != NULL)											//ARM 10Dec96
	{
		char txt [128];											//ARM 10Dec96
		sprintf (txt, "Use %x\n", usedmem);						//ARM 10Dec96
		fwrite (txt, strlen (txt), 1, file);					//ARM 10Dec96
		sprintf (txt, "Fr %x\n", freemem);						//ARM 10Dec96
		fwrite (txt, strlen (txt), 1, file);					//ARM 10Dec96
		sprintf (txt, "Big %x\n", biggestfrag);					//ARM 10Dec96
		fwrite (txt, strlen (txt), 1, file);					//ARM 10Dec96
		sprintf (txt, "Fil %x\n", cachedmem);					//ARM 10Dec96
		fwrite (txt, strlen (txt), 1, file);					//ARM 10Dec96
		fclose (file);											//ARM 10Dec96
	}															//ARM 10Dec96

}


void	TrackMemUse()
{
	enum	{MAXMEMSETS=200};
	struct	MemSets
	{
		int	caller;
		int	sizeoom;
		int	numbits;
		int	totalmem;
	}
	memsets[MAXMEMSETS];

	for (int j=0;j<MAXMEMSETS;j++)
		memsets[j].caller=memsets[j].sizeoom=memsets[j].numbits=memsets[j].totalmem=0;
	memsets[MAXMEMSETS-1].caller=-1;
	memsets[MAXMEMSETS-1].sizeoom=-1;

	ULong* memfollow=MemoryBase;
	int	usedmemsets=0;
	while (memfollow)
	{
		int	s=memfollow[3];
		int	a=memfollow[1];
		memfollow=(ULong*) memfollow[0];

		for (int i=0;i<usedmemsets;i++)
		{
			if (	(memsets[i].caller&-256)==(a&-256)
				&&	memsets[i].sizeoom<=s
				&&  memsets[i].sizeoom*2>s)
			{
				break;
			}
		}
		if (i==usedmemsets && usedmemsets<MAXMEMSETS+1)
		{
			usedmemsets++;
			int j=1;
			int	l=s;
			while (l>=2)
			{
				j+=j;
				l>>=1;
			}
			memsets[i].caller=a;
			memsets[i].sizeoom=j;
			memsets[i].numbits=0;
			memsets[i].totalmem=0;
		}
		memsets[i].numbits++;
		memsets[i].totalmem+=s;
	}

	FILE* file;													//ARM 10Dec96
	file = fopen ("memdbg2.txt", "wt");							//ARM 10Dec96
	char txt [256];												//ARM 10Dec96

	if (file != NULL)											//ARM 10Dec96
	{															//ARM 10Dec96
		for (int i=0; i<74; i++)								//ARM 10Dec96
		{														//ARM 10Dec96
			sprintf (txt, "%x\t%x\t%x\t%x\n",					//ARM 10Dec96
				memsets[i].caller,								//ARM 10Dec96
				memsets[i].sizeoom,								//ARM 10Dec96
				memsets[i].numbits,								//ARM 10Dec96
				memsets[i].totalmem);							//ARM 10Dec96
			fwrite (txt, strlen (txt), 1, file);				//ARM 10Dec96
		}														//ARM 10Dec96
		fclose (file);											//ARM 10Dec96
	}															//ARM 10Dec96

	for (int i=0;i<25;i++)
	{
		Mono_Text.PrintHexAt(12,i,memsets[i].caller,6);
		Mono_Text.PrintHexAt(19,i,memsets[i].sizeoom,5);
		Mono_Text.PrintHexAt(25,i,memsets[i].numbits,3);
		Mono_Text.PrintHexAt(29,i,memsets[i].totalmem,5);
	}

	for (	i=0;i<25;i++)
	{
		Mono_Text.PrintHexAt(35,i,memsets[25+i].caller,6);
		Mono_Text.PrintHexAt(42,i,memsets[25+i].sizeoom,5);
		Mono_Text.PrintHexAt(48,i,memsets[25+i].numbits,3);
		Mono_Text.PrintHexAt(52,i,memsets[25+i].totalmem,5);
	}						
	for (	i=0;i<24;i++)
	{
		Mono_Text.PrintHexAt(58,i,memsets[50+i].caller,6);
		Mono_Text.PrintHexAt(65,i,memsets[50+i].sizeoom,5);
		Mono_Text.PrintHexAt(71,i,memsets[50+i].numbits,3);
		Mono_Text.PrintHexAt(75,i,memsets[50+i].totalmem,5);
	}						
}

