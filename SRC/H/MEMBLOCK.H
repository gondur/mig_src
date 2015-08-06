//------------------------------------------------------------------------------
//Filename       memblock.h
//System         
//Author         Jim
//Date           Sat 4 Jan 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	MEMBLOCK_Included
#define	MEMBLOCK_Included

struct	MemManage1K;
typedef	MemManage1K*	MemPtr1K;

struct	BiList1K
{
	MemPtr1K	next;
	MemPtr1K*	back;
};
typedef	BiList1K*	BiPtr1K;

typedef	BiList1K	(MemManage1K::*MemBiPtr);

#ifndef MEMMANAGEROVERHEAD
#define	MEMMANAGEROVERHEAD	4
#endif

struct	MemManage1K
{
	BiList1K	samesize,
				sameoff,
				diffoff;
	UByte		unitsize;
	UByte		fieldbytes;
	UByte		lastfieldmask;
	UByte		spare;

	enum	{	PAGESIZE=1024,BLOCKSIZE=PAGESIZE-MEMMANAGEROVERHEAD,
				SPACESIZE=BLOCKSIZE-3*2*4-4,SPACEBITS=SPACESIZE*8,

				MAXDATASIZE=63,ZEROBASE=0xE0000000};

	UByte	dataarea[SPACESIZE];

	static	MemPtr1K	MemTables[MAXDATASIZE+1];
	static  int		zeroaddr;


	CON		MemManage1K(int size);
	DES		~MemManage1K();
	void	Link(MemBiPtr mbp,MemPtr1K&	referee);
	void	UnLink(MemBiPtr mbp);
	int		GetSpace();					//returns space number, or -1 if no space
	static	void*	newdata(size_t s);
	static	void	deldata(void* v);
};

#define	DEFAULT_MEMBLOCK 0

#endif
