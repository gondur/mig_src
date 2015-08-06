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
//Filename       memblock.cpp
//System         
//Author         R. Hyde 
//Date           Sat 4 Jan 1997
//Description    Nasty horid memory block management
//------------------------------------------------------------------------------

#include	"DOSDEFS.H"
#define	TRACING	1
#include	"Mathasm.H"
#include	"fileman.H"
#include <malloc.h>
#include	"monotxt.h"
#include	"stdio.h"											//ARM 10Dec96
#include	"string.h"											//ARM 10Dec96




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		static	declarations
//Author		Jim
//Date			Sat 4 Jan 1997
//
//Description	If tracing is enabled then MEMMANAGEROVERHEAD=0x14
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#if	TRACING
#define	MEMMANAGEROVERHEAD	0x14
#else
#define	MEMMANAGEROVERHEAD	0x04
#endif
#include	"MEMBLOCK.H"
MemPtr1K	MemManage1K::MemTables[]={NULL};
int			MemManage1K::zeroaddr=MemManage1K::ZEROBASE;


void	CheckE3()
{
//DeadCode JIM 06Jan97 	MemPtr1K	p1=MemManage1K::MemTables[17];
//DeadCode JIM 06Jan97 	while (p1)
//DeadCode JIM 06Jan97 	{
//DeadCode JIM 06Jan97 		int	j=0;
//DeadCode JIM 06Jan97 		for (int i=7;i<MemManage1K::SPACESIZE-17;i+=17,j++)
//DeadCode JIM 06Jan97 		{
//DeadCode JIM 06Jan97 			if (BITTEST(p1->dataarea,j))
//DeadCode JIM 06Jan97 				if (*(ULong*)(p1->dataarea+i+8)!=*(ULong*)(p1->dataarea+i+17))
//DeadCode JIM 06Jan97 				{
//DeadCode JIM 06Jan97 					if (!*(UWord*)(p1->dataarea+i+17) && *(UWord*)(p1->dataarea+i+19))
//DeadCode JIM 06Jan97 					INT3();
//DeadCode JIM 06Jan97 					*(ULong*)(p1->dataarea+i+8)=*(ULong*)(p1->dataarea+i+17);
//DeadCode JIM 06Jan97 				}
//DeadCode JIM 06Jan97 		}
//DeadCode JIM 06Jan97 		p1=p1->samesize.next;
//DeadCode JIM 06Jan97 	}
//DeadCode JIM 06Jan97 

}


#if	!TRACING
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		new
//Author		Jim
//Date			Sat 4 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void*	operator	new(size_t s)
{
	return	MemManage1K::newdata(s);
}
void*	operator	new[](size_t s)
{
	return MemManage1K::newdata(s);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		delete
//Author		Jim
//Date			Sat 4 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	operator	delete(void* v)
{
	MemManage1K::deldata(v);
}

void	operator	delete[](void* v)
{
	MemManage1K::deldata(v);
}
/////////////////////////////////
#else
extern	ULong* sp();
#pragma aux	sp=	"mov ecx,esp"	value [ecx]

#ifdef	__SW_OD
	#define	STACKGAP	10
#else
	#define	STACKGAP	3
#endif
ULong* MemoryBase=NULL;
void	*operator	new(size_t s)
{
//DeadCode JIM 06Jan97 		CheckE3();
		void* v=MemManage1K::newdata(s+16);
		while (v==0)                                                                                                   
		{
			if (fileman::MyMemFailPFU(s+16)==0)
				break;
			v=MemManage1K::newdata(s+16);
		}
		if (v)
		{
			ULong* u=(ULong*)v;
			*(u++)=(ULong)MemoryBase;
			MemoryBase=(ULong*)v;
			*(u++)=sp()[STACKGAP];
			*(u++)=*(int*)((char*)v+s+16);
//TempCode JIM 05Jan97 			*(u++)=0;
			*(u++)=s;
			v=u;
	//Old_Code PD 16Dec96 		for (;s;s-=4)									//DAW 29Oct96
	//Old_Code PD 16Dec96 			*(u++)=0x0;											//PD 16Dec96
		}
//DeadCode JIM 06Jan97 		CheckE3();
		return	v;
}
void	*operator	new[](size_t s)
{
//DeadCode JIM 06Jan97 		CheckE3();
		void* v=MemManage1K::newdata(s+16);
		while (v==0)
		{
			if (fileman::MyMemFailPFU(s+16)==0)
				break;
			v=MemManage1K::newdata(s+16);
		}
		if (v)
		{
			ULong* u=(ULong*)v;
			*(u++)=(ULong)MemoryBase;
			MemoryBase=(ULong*)v;
			*(u++)=sp()[STACKGAP];
			*(u++)=*(int*)((char*)v+s+16);
//TempCode JIM 05Jan97 			*(u++)=0;
			*(u++)=s;
			v=u;
	//Old_Code PD 16Dec96 		for (;s;s--)									//DAW 29Oct96
	//Old_Code PD 16Dec96 			*(u++)=0x0;											//PD 16Dec96
		}
//DeadCode JIM 06Jan97 		CheckE3();
		return	v;
}
void	operator	delete(void* v)
{
//DeadCode JIM 06Jan97 	CheckE3();
	ULong* t1,t2;
	if (v)
	{
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
		MemManage1K::deldata(v);
	}
//DeadCode JIM 06Jan97 	CheckE3();
}
void	operator	delete[](void* v)
{
//DeadCode JIM 06Jan97 	CheckE3();
	ULong* t1,t2;
	if (v)
	{
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
		MemManage1K::deldata(v);
	}
//DeadCode JIM 06Jan97 	CheckE3();
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		debugtools
//Author		Jim Taylor
//Date			Sun 5 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
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

#endif
////////////////////////////////////////////
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
			if (((int)memptr&0xffffe000)==0x69e000)
				if (*memptr>0x400)
					if (*memptr>0x800)
						if (*memptr>0x1000)
							memptr=memptr;
						
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



void	Trace1K()
{
	FILE*	f=fopen("s:\\transfer\\memdbg3.txt","wt");
	MemPtr1K	lp=MemManage1K::MemTables[0];
	fprintf(f,"�\n");
	while (lp)
	{
		if (lp->diffoff.next)
			fprintf(f,"쳐");
		else
			fprintf(f,"읕");
		if (lp->sameoff.next)
			fprintf(f,"쩡");
		else
			fprintf(f,"컴");
		MemPtr1K	lp2=lp;
		while (lp2)
		{
			int	c2=(lp2->fieldbytes-1)<<3;
			c2+=BITSCANHIGHEST(lp2->lastfieldmask);
			int	c1=c2;
			int	c3=0;
			while (c1--)
				if (BITTEST(lp2->dataarea,c1))
					c3++;
		 	fprintf(f,"%8x\t%3d\t%3d/%3d\t%8x\n",
					(int)lp2,lp2->unitsize,c3,c2,(int)lp2->samesize.next);
			lp2=lp2->sameoff.next;
			if (lp2)
			{
				fprintf(f,"  ");
				if (lp2->sameoff.next)
					fprintf(f,"쳐");
				else
					fprintf(f,"읕");
			}
		}
		lp=lp->diffoff.next;
	}


	fclose(f);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		newdata
//Author		R. Hyde 
//Date			Sat 4 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void*	MemManage1K::newdata(size_t size)
{
	//handle standard sized allocations
	if (size==0)
		return((void*)zeroaddr++);
	if (size>MAXDATASIZE)
	{
		void* rv;
		while ((rv=malloc(size))==NULL)
			if (fileman::MyMemFailPFU(size)==0)
				break;
		return(rv);
	}
	//special code for small allocations

	//if space in existing tables
	MemPtr1K	lp=MemTables[size];
	while (lp)
	{
		int ind=lp->GetSpace();
		if (ind!=-1)
			return(void*)(&lp->dataarea[lp->fieldbytes+ind*size]);
		lp=lp->samesize.next;
	}

	//make a new table
	//linked in all right places
	lp=new MemManage1K(size);
	return(void*)(&lp->dataarea[lp->fieldbytes+lp->GetSpace()*size]);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		deldata
//Author		R. Hyde 
//Date			Sat 4 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MemManage1K::deldata(void* v)
{
	if (v==NULL)
		return;
	if ((int)v>=ZEROBASE && (int)v<zeroaddr)
		return;													//RDH 04Jan97
	MemPtr1K	lp=*MemTables;
	while (lp->diffoff.next && (int)lp->diffoff.next<(int)v)
		lp=lp->diffoff.next;
//DeadCode RDH 04Jan97 	if (lp==NULL)
//DeadCode RDH 04Jan97 		_Error.EmitSysErr("Input loc off botton of all mem");
	//dirty maths time... 
	//get pointer to block that is on same boundary as lp, but holds v
	while (lp->sameoff.next && (int)lp->sameoff.next<(int)v)
		lp=lp->sameoff.next;
	if ((int)v-int(lp)>BLOCKSIZE)
		free(v);
	else
	{
		int offset=((int)v-(int)&lp->dataarea[lp->fieldbytes])/lp->unitsize;

		BITRESET(lp->dataarea,offset);
		if (lp->dataarea[lp->fieldbytes-1] & lp->lastfieldmask)
			return;
		for (int i=lp->fieldbytes-2;i>=0;i--)
			if (lp->dataarea[i])
				return;
		delete(lp);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getspace
//Author		R. Hyde 
//Date			Sat 4 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	MemManage1K::GetSpace()
{
	int	i=0,j=0;
	for (int k=fieldbytes;--k>=0;i+=8,j++)
		if (dataarea[j]!=0xff)
		{
			i+=BITSCANLOWEST(~dataarea[j]);
			BITSET(dataarea,i);
			return(i);
		}
	return(-1);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CON MemManage1K
//Author		R. Hyde 
//Date			Sat 4 Jan 1997
//
//Description	? is irrelevent node
//				new node is to be inserted after lp2
//
//
//A)	the beginning						nul
//											|
//		nul						==>		nul-N-nul
//		|									|
//		0									0
//
//
//B)	new is same as lp
//
//		|								|
//		lp-?-?-?-lp2-?			==>		lp-?-?-?-lp2-N-?
//		|								|
//
//		when lp2=lp:
//
//		|								|
//		lp2-?					==>		lp2-N-?
//		|								|
//
//
//C)	new is at end of lp same list and different to both lp and lp3:
//		
//										lp3-
//										|
//		lp3-							N-nul
//		|								|
//		lp-?-?-lp2-nul			==>		lp-?-?-lp2-nul
//		|						   		|
//
//										lp3-
//										|
//										N-nul
//		lp3-							|
//		|						==>		lp2-nul
//		lp2-nul					   		|
//		|
//
//D)	new is same as lp3, and is at end of lp list
//
//		|								|
//		lp3-							N-lp3-
//		|								|
//		lp-?-?-lp2-nul			==>		lp-?-?-lp2-nul
//		|						   		|
//
//										|
//		|								N-lp3-
//		lp3-							|
//		|						==>		lp2-nul
//		lp2-nul					   		|
//		|
//		
//E)	new is different to lp, but in middle of list:
//
//										?
//										|
//										lp3-
//										|
//		?								N-nul
//		|								|
//		lp-?-?-lp2-lp3-			==>		lp-?-?-lp2-nul
//		|								|
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON	MemManage1K::MemManage1K(int size)
{	//fill in data fields...
	unitsize=size;
	int	numelts=SPACEBITS/((size<<3)+1);	//num bits to represent=bytes+1 bit flag
	fieldbytes=(numelts+7)>>3;
	lastfieldmask=(0xffUL)>>(7-((numelts+7)&7));
	dataarea[fieldbytes-1]=~lastfieldmask;			//set unused bits of last byte
	for (numelts=fieldbytes-2;numelts>=0;numelts--)	//clear all other bits
		dataarea[numelts]=0;
	//debug: clear memory region
	for (numelts=fieldbytes;numelts<SPACESIZE;numelts++)
		dataarea[numelts]=-1;
	//add to lists

	Link(&MemManage1K::samesize,MemTables[size]);

	MemPtr1K	lp=*MemTables;
	if (lp==NULL)		//case A
	{
		Link(&MemManage1K::diffoff,*MemTables);
		sameoff.next=NULL;
		sameoff.back=NULL;
		return;
	}
	while (lp->diffoff.next && (int)lp->diffoff.next<=(int)this)
		lp=lp->diffoff.next;
	MemPtr1K	lp2=lp;
	while (lp2->sameoff.next && (int)lp2->sameoff.next<=(int)this)
		lp2=lp2->sameoff.next;
	if ( ((int)lp%PAGESIZE)==((int)this%PAGESIZE) )
	{					//case B
		Link(&MemManage1K::sameoff,lp2->sameoff.next);
		diffoff.next=NULL;
		diffoff.back=NULL;
	}
	else
		if (lp2->sameoff.next)		//case E
		{	//nasty... need to split sameoff and put 2 entries in diffoff
			MemPtr1K	lp3=lp2->sameoff.next;
			lp2->sameoff.next=NULL;
			lp3->sameoff.back=NULL;
			Link(&MemManage1K::diffoff,lp->diffoff.next);
			lp3->Link(&MemManage1K::diffoff,diffoff.next);
			sameoff.next=NULL;
			sameoff.back=NULL;

		}
		else						//case D
			if (	lp->diffoff.next
				&&	((int)lp->diffoff.next%PAGESIZE)==((int)this%PAGESIZE)
				)
			{	//replace diffoff with this entry
				//put old diffoff as sameoff of this
				MemPtr1K	lp3=lp->diffoff.next;
				lp3->UnLink(&MemManage1K::diffoff);
				sameoff.next=lp3;
				sameoff.back=NULL;
				lp3->sameoff.back=&sameoff.next;
				lp3->diffoff.next=NULL;
				lp3->diffoff.back=NULL;
				Link(&MemManage1K::diffoff,lp->diffoff.next);


			}
			else					//case C
			{	//insert as new diffoff
				Link(&MemManage1K::diffoff,lp->diffoff.next);
				sameoff.next=NULL;
				sameoff.back=NULL;
			}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DES MemManage1K
//Author		R. Hyde 
//Date			Sat 4 Jan 1997
//
//Description	delete the record from the system.
//
//A)	same.back set
//
//		|					|
//		a-b-*-c		==>		a-b-c
//		|					|
//
//		same.back clear,	same.next	set
//
//
//		y					y
//B)	|					|
//		*-a-b		==>		a-b
//		|					|
//		x					x
//
//
//C)	same.back=same.next=NULL
//		diff.next=NULL
//
//		nul					nul
//		|					|
//		*-nul		==>		x-
//		|
//		x
//
//		same.back=same.next=NULL
//		diff.next set
//
//		z
//		|					z
//		y					|
//		|					y
//		*-nul		==>		|
//		|					x
//		x
//
//D)	can't implement this enhancement...
//		x same as y so can be merged:
//
//		z
//		|
//		y-y2-y3-				==>		z
//		|								|
//		*								x-x1-x2-?-?-?-xn-y-y2-y3-
//		|
//		x-x1-x2-?-?-?-xn-nul
//
//		Not very useful anyway as would have to split again if * used again
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DES	MemManage1K::~MemManage1K()
{
	UnLink(&MemManage1K::samesize);

	if (sameoff.back)
		UnLink(&MemManage1K::sameoff);		//case A
	else
		if (sameoff.next==NULL)
			UnLink(&MemManage1K::diffoff);	//case C
		else	//case B
		{
			MemManage1K*& diffback=*diffoff.back;
			UnLink(&MemManage1K::diffoff);
			sameoff.next->sameoff.back=NULL;
			sameoff.next->Link(&MemManage1K::diffoff,diffback);
		}
}

void	MemManage1K::Link(MemBiPtr mbp,MemPtr1K&	referee)
{
	BiList1K fred;
	(this->*mbp).next=fred.next;

	(this->*mbp).next=referee;
	((this->*mbp).next->*mbp).back=&(this->*mbp).next;
	(this->*mbp).back=&referee;
	referee=this;

}
void	MemManage1K::UnLink(MemBiPtr mbp)
{
	if ((this->*mbp).next)
		((this->*mbp).next->*mbp).back=(this->*mbp).back;
	if ((this->*mbp).back)
		*(this->*mbp).back=(this->*mbp).next;
}

