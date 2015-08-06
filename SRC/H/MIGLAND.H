//------------------------------------------------------------------------------
//Filename       migland.h
//System         
//Author         Paul.   
//Date           Wed 14 Jan 1998
//Description    
//------------------------------------------------------------------------------

#ifndef	MIGLAND_Included

const int _altitudeScale=25;									//PD 24Aug98


#define	MIGLAND_Included
#include	"files.g"
#include	"myangles.h"

#include	"3ddefs.h"

class	Display;

typedef struct 	ImageMap_Desc									//PD 01Aug96
				ImageMapDesc,									//PD 01Aug96
				*ImageMapDescPtr;								//PD 01Aug96

#define	DEFAULT_MIGLAND 0

#define NOASSERTS

struct SmallPoint
{
	UByte x,z;
	UWord alt;
};

struct PointDef{
	UWord x,z;		//values are 0->256 inclusive
	UWord alt;
	UByte shadeVal;
};

struct DrawDataHdr{
	UWord	noOfPolys;
	UWord	noOfLines;
	UWord	noOfTrees;
	UWord	treeOffset;
	UWord	noOfWaves;
	UWord	waveOffset;
	UWord	totalTris;		//for hardware execute buffer fill test
};

struct	NormalList
{
 	Float	ni,nj,nk;
	UByte	count;
};

#ifdef	IN_MIGLAND_CPP

#include "MathASM.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////																		////
////	CACHE AND MEMORY MANAGEMENT TEMPLATES FOR MIG ALLEY LANSCAPE CODE	////
////																		////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<class Object> class CAllocator
{
	Object*	pObjList;
	UWord	size,
			used;

	public:

	CAllocator(UWord sz=1);
	~CAllocator() { delete [] pObjList; }

	Object* Alloc(UWord cnt=1);
	UWord	Reset();
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CAllocator
//Author		Paul.   
//Date			Wed 3 Dec 1997
//------------------------------------------------------------------------------
template<class Object> CAllocator<Object>::CAllocator(UWord sz)
{
	pObjList=new Object[size=sz];
	used=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Alloc
//Author		Paul.   
//Date			Wed 3 Dec 1997
//------------------------------------------------------------------------------
template<class Object> Object* CAllocator<Object>::Alloc(UWord cnt)
{
	#ifndef NOASSERTS
	assert((cnt+used<=size)&&"CAllocator out of storeage space");
	#endif
	Object* retval = pObjList+used;
	used+=cnt;
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Reset
//Author		Paul.   
//Date			Wed 3 Dec 1997
//------------------------------------------------------------------------------
template<class Object> UWord CAllocator<Object>::Reset()
{
	used=0;
	return size;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

template <class Object> class CBlockAllocator
{
private:
	Object*	pObjList;
	ULong*	pRecord;
	ULong	sizeObjList;
	ULong	sizeRecord;
	ULong	lastStart;
public:
	CBlockAllocator(int sz=0);
	~CBlockAllocator();

	Object*	Alloc();
	void	Free(Object*);
	void	Reset();
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CBlockAllocator
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
template<class Object> CBlockAllocator<Object>::CBlockAllocator(int sz)
{
	#ifndef NOASSERTS
	assert(sz!=0&&" What?");
	#endif
	sizeRecord=(sz>>5)+1;
	pObjList=new Object[sizeObjList=sz];
	pRecord=new ULong[sizeRecord];
	for (int i=0;i<sizeRecord;pRecord[i++]=0L) {}
	lastStart=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CBlockAllocator
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
template<class Object> CBlockAllocator<Object>::~CBlockAllocator()
{
	//Call the destructor code for all the currently
	//allocated objects

	for (int i=0;i<sizeObjList;i++)
		if (BITTEST(pRecord,i)) (pObjList+i)->~Object();

 	delete [] pRecord;
	delete [] pObjList;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Alloc
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
template<class Object> Object* CBlockAllocator<Object>::Alloc()
{
	ULong index=lastStart;
	while(index<sizeObjList&&BITTEST(pRecord,index)) index++;
	lastStart=index;
	#ifndef NOASSERTS
	assert(index!=sizeObjList&&" CBlockAllocator out of storeage space");
	#endif
	if (index==sizeObjList) return NULL;
	BITSET(pRecord,index);
	return pObjList+index;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Free
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
template<class Object> void CBlockAllocator<Object>::Free(Object* pObj)
{
	#ifndef NOASSERTS
	assert(pObj>=pObjList&&" I didn't allocate this (lo)");
	assert(pObj<pObjList+sizeObjList&&" I didn't allocate this (hi)");
	#endif
	ULong index=ULong(pObj-pObjList);
	if (index<lastStart) lastStart=index;
	#ifndef NOASSERTS
	assert(BITTEST(pRecord,index)&&" Already Freed");
	#endif
	BITRESET(pRecord,index);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Reset
//Author		Paul.   
//Date			Fri 19 Dec 1997
//------------------------------------------------------------------------------
template<class Object> void CBlockAllocator<Object>::Reset()
{
	for (int i=0;i<sizeRecord;pRecord[i++]=0L) {}
	lastStart=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

struct SInfo
{
	ULong offset,length;
};

class CDecompressData;

//Seek request structure

typedef struct SeekStruc
{
	enum {CENTER_WH=37};
	SeekStruc*	pNext;
	FileNum		fileNum;
	ULong		seekPos;
	ULong		dataLen;
	ULong		firstSkipIndex;
	ULong		numBlocks;
	SByte*		blockPtrs[CENTER_WH];
	SeekStruc()	{pNext=NULL;}
}
*SeekStrucP;

class CRectangularCache
{
	ViewPoint* v_p;
	enum WhichWay
	{
	WW_north=0,
	WW_east,
	WW_south,
	WW_west
	};

	public:

	SInfo *pNorth,*pEast;	//DEAD ,*pSouth,*pWest;
	CDecompressData* pDecomp;

	enum
	{
	CENTER_WH=SeekStruc::CENTER_WH,
	MIN_BOUND=16,
	MAX_BOUND=19,	//20,
	CENTER_HALF=CENTER_WH>>1,
	XZ_COL_SCALE=9,
	BLOCK_WIDTH=0x20000,
	LARGEST_BLOCK_SIZE=1024+512
	};

	private:

	SByte** pCBlkData;

	COORDS3D bufferbase;

	MovingItem* fselitemp;

	SeekStrucP masterseeklist;

	WhichWay currentdirection;
	FileNum currentfilenum;

	SLong pingcounter;
	SLong pingtimer;

	bool AttemptSeek(SeekStrucP);
	void AddSeekRequest(SeekStrucP);
	void ProcessSeekRequests2();
	void ScrollSouth();
	void ScrollNorth();
	void ScrollWest();
	void ScrollEast();
	void RecenterBuffer(SLong,SLong,SLong,SLong);
	void BuildNorthRequests();
	void BuildEastRequests();
	void BuildSouthRequests();
	void BuildWestRequests();
	void BigRebuild();
	void StillGoingNorth();
	void StillGoingEast();
	void StillGoingSouth();
	void StillGoingWest();
	void NowGoingNorth();
	void NowGoingEast();
	void NowGoingSouth();
	void NowGoingWest();
	WhichWay GetDirectionFlags();
	WhichWay GetDirectionFlags2();

	public:

	CRectangularCache(UWord dir=0);
	~CRectangularCache();
	void SetViewpoint(MovingItem* vp) {fselitemp=vp;v_p=(ViewPoint*)vp;}
	bool ProcessSeekRequests();
	void ProcessSeekRequestsNF();
	void OneShotSeekRequest(SLong,SLong,SeekStrucP,DataRecord*);

	UByte* GetData(SLong,SLong);
	void BigInit();
};


template<class HashObject> class CCircularCache
{
	private:

	class	CRecord
	{
		public:

		HashObject	hObj;
		bool		inBuffer;

		UByte*		pStart;
		ULong		length;

		CRecord() {inBuffer=false;}
		~CRecord() {};
	};

	private:

	enum {_boundaryLimit=2048};

	UByte*		pBuf;
	UByte*		pStart;
	UByte*		pFin;
	ULong		size;
	ULong		maxEntries;
	ULong		curEntries;
	CRecord*	pRecords;
	UByte*		pCurrentData;
	SLong		currentDataLen;
	ULong		bufferEnd;

	inline ULong Avail();

	public:

	CCircularCache(ULong sz=0L,ULong me=0L);
	~CCircularCache();

	void	GetEntry(HashObject&,FILE*,ULong,ULong);
	void	Reset();

	//slow operators with buffer boundary checks

	inline UByte operator*();
	inline UByte* operator+=(int);
	inline UByte* operator++();
	inline UByte* operator++(int);

	//equivalent routines with no boundary checks

	UByte fastPostInc()	//equivalent to the combination *x++
	{
		currentDataLen--;
		return *pCurrentData++;
	}

	void fastInc()		//equivalent to x++
	{
		currentDataLen--;
		pCurrentData++;
	}

	//quick block skipping code

	inline void skipToNextFFFF();

	bool fastUnpackPermitted()
	{
		if ((bufferEnd-ULong(pCurrentData))<_boundaryLimit) return false;
		return true;
	}
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	skipToNextFFFF
//------------------------------------------------------------------------------
template<class HashObject> void CCircularCache<HashObject>::skipToNextFFFF()
{
	if ((bufferEnd-ULong(pCurrentData))<_boundaryLimit)
	{
		bool gotOne=false;

		for (;;)
		{
		 	if (gotOne)
			{
				gotOne=bool(*pCurrentData++==0xFF);
				currentDataLen--;
				if (ULong(pCurrentData)>=bufferEnd)
					pCurrentData=pBuf;
				if (gotOne) break;
			}
			if (!gotOne)
			{
			 	gotOne=bool(*pCurrentData++==0xFF);
				currentDataLen--;
				if (ULong(pCurrentData)>=bufferEnd)
					pCurrentData=pBuf;
			}
		}
	}
	else
	{
		UByte* psrc=pCurrentData;
		while (*(UWord*)psrc!=UWord(0xFFFF)) psrc++;
		psrc+=2;
		currentDataLen-=ULong(psrc)-ULong(pCurrentData);
		pCurrentData=psrc;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		operator*
//Author		Paul.   
//Date			Thu 4 Dec 1997
//------------------------------------------------------------------------------
template<class HashObject> UByte CCircularCache<HashObject>::operator*()
{
	#ifndef NOASSERTS
	assert(pCurrentData!=NULL&&"No data yet");
	#endif

	return *pCurrentData;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		operator++
//Author		Paul.   
//Date			Thu 4 Dec 1997
//------------------------------------------------------------------------------
template<class HashObject> UByte* CCircularCache<HashObject>::operator++()
{
	#ifndef NOASSERTS
 	assert(currentDataLen-->0&&"Run out of data(1)");
	#endif
	pCurrentData++;
	if ((ULong)pCurrentData>=bufferEnd) pCurrentData-=size;

	return pCurrentData;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		operator++
//Author		Paul.   
//Date			Thu 4 Dec 1997
//------------------------------------------------------------------------------
template<class HashObject> UByte* CCircularCache<HashObject>::operator++(int)
{
	#ifndef NOASSERTS
 	assert(currentDataLen-->0&&"Run out of data(2)");
	#endif
	UByte*	pLast=pCurrentData;

	pCurrentData++;
	if ((ULong)pCurrentData>=bufferEnd) pCurrentData-=size;

	return pLast;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		operator+=
//Author		Paul.   
//Date			Mon 8 Dec 1997
//------------------------------------------------------------------------------
template<class HashObject> UByte* CCircularCache<HashObject>::operator+=(int a)
{
	#ifndef NOASSERTS
	assert((currentDataLen-=a)>0&&"Run out of data(3)");
	#endif

	pCurrentData+=a;
	if ((ULong)pCurrentData>=bufferEnd) pCurrentData-=size;

	return pCurrentData;
}

//-----------------------------------------------------------------------------
// Procedure    CCircularCache::CCircularCache
// Author       Paul
// Date         04/12/97
//-----------------------------------------------------------------------------
template<class HashObject> CCircularCache<HashObject>::CCircularCache(ULong sz,ULong me)
{
	#ifndef NOASSERTS
	assert(sz!=0&&"Zero length buffer is illegal");
	assert(me!=0&&"Zero max elements is illegal");
	#endif
	pBuf = new UByte[size=sz];
	pRecords = new CRecord[maxEntries=me];
	pStart=pFin=pBuf;
	curEntries=0;
	bufferEnd=ULong(pBuf)+size;
}

//-----------------------------------------------------------------------------
// Procedure    CCircularCache::~CCircularCache
// Author       Paul
// Date         04/12/97
//-----------------------------------------------------------------------------
template<class HashObject> CCircularCache<HashObject>::~CCircularCache()
{
	delete [] pRecords;
	delete [] pBuf;
}

//-----------------------------------------------------------------------------
// Procedure    CCircularCache::GetEntry
// Author       Paul
// Date         04/12/97
//-----------------------------------------------------------------------------
template<class HashObject> void CCircularCache<HashObject>::GetEntry(	HashObject& hObj,	FILE* pFile,
																		ULong offset,		ULong length)
{
	int i=0;
	while (i<maxEntries)
	{
		if (pRecords[i].inBuffer)
			if (pRecords[i].hObj==hObj) break;
		i++;
	}
	if (i!=maxEntries)	//Found in the cache
	{
		pCurrentData=pRecords[i].pStart;
		currentDataLen=pRecords[i].length;
	}
	else	//Not found in the cache - so load it!
	{
		if (Avail()<length || curEntries==maxEntries)	//Need to make some room in the buffer
		{
			//Discard from the head of the buffer
			bool bufferEmpty=false;
			do 
			{
				bool foundEntry=false;
				for (int j=0;j<maxEntries;j++)
				{
					foundEntry=pRecords[j].inBuffer?true:foundEntry;
					if (pRecords[j].pStart==pStart)	break;
				}
				if (j<maxEntries)
				{
					pStart+=pRecords[j].length;
					if (ULong(pStart)>=ULong(pBuf)+size) pStart-=size;
					pRecords[j].inBuffer=false;
					curEntries--;
				}
				bufferEmpty=!foundEntry;
			}
			while (bufferEmpty==false && (Avail()<length || curEntries==maxEntries));
		}
	#ifndef NOASSERTS
		assert(Avail()>=length&&"Data too large for the buffer");
	#endif

		//Find a record that can be re-used

		for (int j=0;j<maxEntries&&pRecords[j].inBuffer==true;j++);
		pRecords[j].hObj=hObj;
		pRecords[j].inBuffer=true;
		pRecords[j].pStart=pFin;
		pRecords[j].length=length;
		pCurrentData=pFin;
		currentDataLen=length;
		pFin+=length;
		curEntries++;

		//Load the file block - may need to wrap round to the start
		//of the buffer part way through the file

		FILEMAN.seekfilepos(pFile,offset);

		if ((ULong)pFin<(ULong)pBuf+size)
			FILEMAN.readfileblock(pFile,(void*)pRecords[j].pStart,length);
		else
		{
			ULong	sect1,sect2;
			sect1 = (ULong)pBuf+size-(ULong)pRecords[j].pStart;
			sect2 = length-sect1;
			FILEMAN.readfileblock(pFile,(void*)pRecords[j].pStart,sect1);
			FILEMAN.readfileblock(pFile,(void*)pBuf,sect2);
			pFin-=size;
		}
	}
}

//-----------------------------------------------------------------------------
// Procedure    CircularCache::Avail
// Author       Paul
// Date         04/12/97
//-----------------------------------------------------------------------------
template<class HashObject> ULong CCircularCache<HashObject>::Avail()
{
	return	(ULong)pStart<=(ULong)pFin?
			size-(ULong)pFin+(ULong)pStart:
			(ULong)pStart-(ULong)pFin;
}

//-----------------------------------------------------------------------------
// Procedure    Reset
// Author       Paul
// Date         04/12/97
//-----------------------------------------------------------------------------
template<class HashObject>void CCircularCache<HashObject>::Reset()
{
	for (int i=0;i<maxEntries;pRecords[i++].inBuffer=false);
	pStart=pFin=pBuf;
	curEntries=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

template<class Object> class CCircularBlockCache
{
private:
	ULong	size;		//total buffer size in bytes
	UByte*	pBuff;		//ptr to the start of the buffer
	UByte*	pHead;		//ptr to the first inserted element
	UByte*	pTail;		//ptr to the insertion point for the next new element
	UByte*	pLast;		//ptr to the start of the last element inserted

	inline void DeleteHead();
public:
	CCircularBlockCache(ULong sz=0);
	~CCircularBlockCache();

	Object* Alloc(ULong);
};

//-----------------------------------------------------------------------------
// Procedure    CCircularBlockCache::CCircularBlockCache
// Author       Paul
// Date         13/01/98
//-----------------------------------------------------------------------------
template<class Object> CCircularBlockCache<Object>::CCircularBlockCache(ULong sz)
{
	#ifndef NOASSERTS
	assert(sz!=0&&" Buffer size is zero");
	#endif
	pHead=pBuff=new UByte[size=sz];
	pLast=pTail=NULL;
}

//-----------------------------------------------------------------------------
// Procedure    CCircularBlockCache::~CCircularBlockCache
// Author       Paul
// Date         13/01/98
//-----------------------------------------------------------------------------
template<class Object> CCircularBlockCache<Object>::~CCircularBlockCache()
{
	//If the buffer is not empty then call the destructors for
	//each element in the buffer
	if (pTail!=NULL) while (pHead!=NULL) DeleteHead();
	delete [] pBuff;
}

//-----------------------------------------------------------------------------
// Procedure    CCircularBlockCache::DeleteHead
// Author       Paul
// Date         13/01/98
//-----------------------------------------------------------------------------
template<class Object> void CCircularBlockCache<Object>::DeleteHead()
{
	Object* pDataBlk=(Object*)(pHead+4);//Get ptr to stored element
	pDataBlk->~Object();				//Call its destructor code	
	pHead=(UByte*)*(ULong*)pHead;		//Get the next ptr
}

//-----------------------------------------------------------------------------
// Procedure    CDataBlockAllocator::Alloc
// Author       Paul
// Date         13/01/98
//-----------------------------------------------------------------------------
template<class Object> Object* CCircularBlockCache<Object>::Alloc(ULong sz)
{
	//Add size of ptr to next element
	sz+=4;
	#ifndef NOASSERTS
	assert((sz)<=size&&" Buffer too small");	//Should never happen
	#endif
	//Initialise return value to NULL
	Object*	pRVal=NULL;
	//Test for first insertion to an empty buffer
	if (pTail==NULL)
	{
		*(ULong*)pHead=ULong(pLast);//Fill in the 'next' field will be NULL
		pTail=pHead+sz;				//Set tail ptr to end of the alloc'd block
		pLast=pHead;				//Record this element as the last inserted
		pRVal=(Object*)(pHead+4);	//Set pointer to the alloc'd data area
	}
	else
	{
		while (pRVal==NULL)
		{
			ULong freeSpace;
			if (ULong(pTail)>ULong(pHead))
			{
				//Moving from pTail->pHead means wrapping round the
				//end of the buffer. First, test to see if there is
				//enough room to fit the new data in between pTail
				//and the end of the buffer.
				freeSpace=size-(ULong(pTail)-ULong(pBuff));
				if (sz<=freeSpace)
				{
					//The new element will fit without going over
					//the end of the buffer

					//Fill in new elements 'next' field
					*(ULong*)pTail=NULL;
					//Update the last elements 'next' field
					*(ULong*)pLast=ULong(pTail);
					//Update the last inserted element ptr
					pLast=pTail;
					//Update the tail ptr
					pTail+=sz;
					//Set pointer to alloc'd data area
					pRVal=(Object*)(pLast+4);
				}
				else pTail=pBuff;
			}
			else
			{
			 	//Moving from pTail->pHead doesn't involve
				//wrapping around the end of the buffer
				freeSpace=ULong(pHead)-ULong(pTail);
				if (sz<=freeSpace)
				{
					//The new element will fit between pTail & pHead

					//Fill in the new elements 'next' field
					*(ULong*)pTail=NULL;
					//Update the last elements 'next' field
					*(ULong*)pLast=ULong(pTail);
					//Update the last inserted element ptr
					pLast=pTail;
					//Update the tail ptr
					pTail+=sz;
					//Set the pointer to the alloc'd data area
					pRVal=(Object*)(pLast+4);
				}
				else
				{
					DeleteHead();
					//Test for completely empty buffer and reset 
					//accordingly
					if (pHead==NULL)
					{
						pLast=pHead=pBuff;
						*(ULong*)pHead=NULL;
						pTail=pHead+sz;
						pRVal=(Object*)(pLast+4);
					}
				}
			}
		}
	}
	return pRVal;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////																		////
////	CLASS FORWARD DEFINITIONS & TYPEDEFS FOR MIG ALLEY LANSCAPE CODE	////
////																		////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class	CDecompressData;	// Class responsible for decompressing the data

class	CDataBlock;			// Data block class for holding decompressed data
class	CCacheBlock;		// Class responsible for searching and maintaining
							// the currently allocated blocks of intermediate
							// data

class	CPrimaryDB;			// Data block class for holding decompressed data
class	CPrimaryCB;			// Class responsible for searching and maintaining
							// the currently allocated blocks of decompressed
							// data

class	CFileID;

typedef CCircularBlockCache<CDataBlock> CDataBlockAllocator;
typedef CBlockAllocator<CCacheBlock>	CCacheBlockAlloc;

typedef CCircularBlockCache<CPrimaryDB> CPrimaryDBAllocator;
typedef CBlockAllocator<CPrimaryCB>		CPrimaryCBAlloc;

typedef CRectangularCache CMigFile;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////																		////
////	GENERAL CLASS DEFINITIONS FOR MIG ALLEY LANSCAPE CODE				////
////																		////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class CFileID
{
	protected:

	UWord	l[2];	//UByte	l[4];

	public:

	CFileID() {};
	CFileID(ULong f,ULong s) {l[0]=UWord(f);l[1]=UWord(s);}
	~CFileID()	{};

	bool operator==(const CFileID& cmp) const
	{ return (bool)(*(ULong*)l==*(ULong*)cmp.l); }
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

struct DataRecord;

typedef int (*DecompCallBackPtr) (UByte,PointDef*,UByte*,UByte*&);

class CDecompressData
{
	private:	//new bits to rearrange data format on decompression

	enum {PT_JUNCTION=0,PT_EDGE=1};

	struct EdgeDef{
		UByte  startPoint,endPoint;	//indices into point list above
		UByte  length;				//distance between start and end point
		UByte  noOfPoints;			//number of other points between start & end
		UWord  edgeOffset;			//offset to list of of intermediate points
	};

	struct RouteCon{
	 	UByte	count,
				flags,
				types[8];
	};

	UByte* edgeLists[256];
	UByte pointFlags[256];		//A junction or not a junction
	UByte newPolyStream[8192];
	UByte newLineStream[8192];
	UByte edgePoints[8192];

	RouteCon routeCon[256];

	EdgeDef* edgeDefs;

	ULong edgeCount;
	ULong polyStreamLen;
	ULong lineStreamLen;
	ULong edgePointLen;

	UWord globalPolyCount;
	UWord globalLineCount;

	bool lightShadingEnabled;

	void MakeIntermediateData();
	void GenerateEdges();
	void GeneratePointFlags(UWord edgePointCount);
	void InsertEdgeDefs(UByte,UByte*,UByte*&,UByte*&);
	void InsertEdgeDefs2(UByte,UByte*,UByte*&,UByte*&);
	UWord AddEdge(UByte,UByte,UByte,UByte*,UByte*&);
	void DeRezEdges(ULong,EdgeDef*,UByte*,ULong,UByte*);

	void skipToNextFFFF(UByte*&);

	inline void ResetRouteCon(UByte);

	DecompCallBackPtr pGenTri;

	private:


	enum {NO_ALT=0,BYTE_ALT,WORD_ALT};

	enum {TEMP_DECOMP_BUFF_SIZE=65536};

	enum {NULLCON=0xff};

	enum	{FLAGINDEX=0x07,
			EDGEPT=0xF0,
			LEDGE=0x01,TEDGE,REDGE,BEDGE,
			CORNERPT=0xF8,
			TLCORNER=0x01,TRCORNER,BRCORNER,BLCORNER};

	enum JoinCodings	{	JOIN_POLY_NEXT=0xff,JOIN_ROAD_NEXT=0xfe,
							JOIN_FOLLOW_TO=0xfd,JOIN_FOLLOW_FROM=0xfc,
							JOIN_NEW_COORDS=0xfb	};

	UByte*	PolyStream;
	UByte*	PolyPtr;
	UByte*	LineStream;
	UByte*	LinePtr;

	ULong	dataLen;
	ULong	totalEdgePoints;

	struct PointList
	{
		ULong 	x,y;				//8
		UByte	unpairedfrom[4];	//4
		ULong	alt;				//4	//make this a word
		ULong	lastfrom,lastto;	//8	//make this bytes - to fit 16 byte records
		UByte	shadeVal;
		UByte	directionsused[7];	//8		//32
	}
	pointdec[256];

	//Vertex normals
	NormalList normalList[256];
	double wLi,wLj,wLk;		//Light vector
	double tLi,tLj,tLk;;		//for light shading

	inline void ResetNList(SLong pntCnt){
		NormalList* pN=normalList;
		for (int x=0;x<pntCnt;x++,pN++){
			pN->ni=pN->nj=pN->nk=float(0);
			pN->count=0;
		}
	}
	void CalculateNVecs(PointDef*,UByte*,NormalList*);
	inline void AverageNormals(SLong pntCnt,PointDef*,UByte*);

	PointList*	pplReset;
	PointList*	pplPoint0;
	PointList*	pplPoint1;
	PointList*	pplPoint2;
	PointList*	pplPoint3;

	UByte	topEdgeCnt,rightEdgeCnt,bottomEdgeCnt,leftEdgeCnt;
	SLong	lowestAlt,highestAlt;

	UByte	Max_Points;
	UByte	Highest_Point_Defined;
	UWord	altData;
	ULong	baseAltitude,scaleAltitude;

	inline ULong getAltitude(UByte*& inptr);
	inline ULong fastGetAltitude(UByte*& inptr);
	inline ULong getAltWord(UByte*& inptr);
	inline ULong fastGetAltWord(UByte*& inptr);

	UWord	FindEdgePoints(UByte*&);
	UWord	FastFindEdgePoints(UByte*&);
	UWord	SkipEdgePoints(UByte*&);
	void	FakePointsLinesPolys(UByte*&,UWord);
	void	FindPointsLinesPolys(UByte*&);
	void	FastFindPointsLinesPolys(UByte*&);
	void	SkipPointsLinesPolys(UByte*&);
	void	FastSkipPLP(UByte*&);
	inline void	PointsConnected(SLong,SLong);

	UWord copyHeader(UByte*&,UByte*&);
	void copyToNextFFFF(UByte*&,UByte*);
	void copyBody(UByte*&,UByte*);

	void	putpixel(SLong col,SLong x,SLong y);
	void	putline(SLong sx,SLong sy,SLong ex,SLong ey,SLong colour);
	inline void	RemoveStupids(UByte&,UByte*);
	bool 	HitTest(SLong,SLong,PointDef&,PointDef&,PointDef&,SLong&);
	UWord 	PointInTriangle(SLong,SLong,PointDef&,PointDef&,PointDef&,SLong&);
	SLong	BuildTreeList(UByte*,PointDef*,SmallPoint*&);
	SLong	BuildWaveList(UByte*,PointDef*,SmallPoint*&);

	public:

	CDecompressData();
	~CDecompressData();

	void	UnPack(ULong,ULong,UByte*&,CDataBlock*&);
	void	MakeIntData(ULong,ULong,ULong,void*,CPrimaryDB*&);
	void DebugDumpIData(void*);
	void	Skip(UByte*&,ULong);
	void	CopyData(UByte*&,UByte*);
	inline void SetLVector(SLong li,SLong lj,SLong lk);
	void FindAltNType(SLong,SLong,DataRecord&,SLong&,UByte&);
	void FindRoughAlt(SLong,SLong,SLong,DataRecord&,SLong&);
	void UnpackIntData(UByte*,ULong);

	UByte*	pDataStart;

	bool treesEnabled;
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


////////////////////////////////////////
//
//Landscape file index management class
//
////////////////////////////////////////

class CMigIndex
{
	friend class fileblock;

public:
	SInfo* pNorth;
	SInfo* pEast;
//DEAD	SInfo* pSouth;
//DEAD	SInfo* pWest;

private:
	fileblock* pfNorth;
	fileblock* pfEast;
//DEAD	fileblock* pfSouth;
//DEAD	fileblock* pfWest;

	enum
	{
		ROW_ENTRIES=8,
		COLUMN_ENTRIES=5,
		BLOCK_ENTRIES=128,
	};

public:
	CMigIndex()
	{
		pfNorth=new fileblock(FIL_NORTHINDEX_NUM);
		pfEast=new fileblock(FIL_EASTINDEX_NUM);
//DEAD		pfSouth=new fileblock(FIL_SOUTHINDEX_NUM);
//DEAD		pfWest=new fileblock(FIL_WESTINDEX_NUM);

		pNorth=(SInfo*)pfNorth->getdata();
		pEast=(SInfo*)pfEast->getdata();
//DEAD		pSouth=(SInfo*)pfSouth->getdata();
//DEAD		pWest=(SInfo*)pfWest->getdata();
	}
	~CMigIndex()
	{
		pNorth=pEast=NULL;
//DEAD		pNorth=pSouth=pEast=pWest=NULL;
//DEAD		delete pfWest;
//DEAD		delete pfSouth;
		delete pfEast;
		delete pfNorth;
	}
};

class CMigFMan
{
private:
//DEAD	FILE* f;
//DEAD	UWord d;
//DEAD	CMigIndex* pInd;
public:
	enum
	{
		//DEAD CMFM_NORTH=0,CMFM_EAST,CMFM_SOUTH,CMFM_WEST,
		COORDS_SHIFT=17
	};
	CMigFMan(/*int i=CMFM_NORTH*/){
		FileNum areaFiles[]={FIL_AREAN_NUM,FIL_AREAE_NUM};

		FILEMAN.SetupAreaFiles(areaFiles);
//DEAD		d=UWord(i);
//DEAD		pInd=NULL;
	}
	~CMigFMan()
	{
		FILEMAN.CloseAreaFiles();
	}
	UByte* getdata(CMigFile& migFile,CDecompressData& migDecomp,ULong x,ULong z)
	{
		UByte* rv=migFile.GetData(x,z);
		assert(rv);
		return rv;
	}
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
#undef new
class CCacheBlock
{
	friend class CMigLand;
	friend class CDataBlock;
	friend class CRectangularCache;
private:
	enum	{ COORD_SCALE=17 };

	static	CCacheBlock*		pHead;
	static	CCacheBlockAlloc*	pAlloc;

	CCacheBlock*	pParent;
	CCacheBlock*	pNorth;
	CCacheBlock*	pEast;

	SWord			blockWx;
	SWord			blockWz;

	CDataBlock*		pData;

public:
	CCacheBlock(int wx=0,int wz=0) 
	{
		wx>>=COORD_SCALE;
		wz>>=COORD_SCALE; 
		blockWx=SWord(wx); 
		blockWz=SWord(wz);

		pParent=
			pNorth=
			pEast=NULL;

		pData=NULL;
	}
	~CCacheBlock();

	void Insert();
	void Remove();

	bool Search(int wx,int wz,CDataBlock*& pDBlk);

	inline void* operator new(size_t);
	inline void operator delete(void* pDelMe);
};

class CPrimaryCB
{
	friend class CMigLand;
	friend class CPrimaryDB;
private:
	enum	{ COORD_SCALE=17 };

	static CPrimaryCB*		pHead;
	static CPrimaryCBAlloc*	pAlloc;

	CPrimaryCB*	pParent;
	CPrimaryCB*	pNorth;
	CPrimaryCB*	pEast;

	SWord blockWx;
	SWord blockWz;
	UWord resolution;

	CPrimaryDB*	pData;

public:
	CPrimaryCB(int wx=0,int wz=0,int rez=0) 
	{
		blockWx=SWord(wx>>COORD_SCALE); 
		blockWz=SWord(wz>>COORD_SCALE);
		resolution=UWord(rez);
		pParent=pNorth=pEast=NULL;
		pData=NULL;
	}
	~CPrimaryCB();

	void Insert();
	void Remove();

	UWord Search(int wx,int wz,int rez,CPrimaryDB*& pDBlk);

	inline void* operator new(size_t);
	inline void operator delete(void* pDelMe);
};
#define	new DEBUG_NEW
#else

class CDataBlockAllocator;
class CPrimaryDBAllocator;
class CMigFile;
class CDecompressData;
class CCacheBlock;
class CPrimaryCB;
class CMigIndex;
class CMigFMan;

#ifndef	File_Man
class fileblock;
typedef class	fileblock *fileblockptr;
#endif

#endif

struct DataRecord;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

const SLong WORLD_BIG_WZ = 0x07FFFFFFF;

class LandMapNumRecord;

class LandMapNum
{
	friend class LandMapNumRecord;
private:
	enum {LandMapNumMIN=0,LandMapNumMAX=255};
	static LandMapNumRecord* pRecord;
 	SWord	no;
public:
	LandMapNum() {}
	LandMapNum(FileNum,FileNum f=DIR_LANDMAPS);
	operator int() { return int(no); }
	ImageMapDescPtr GetLandMapPtr();
};

class LandMapNumRecord
{
private:
	enum {MAXMAPS=255};
	ImageMap_Desc	lm[MAXMAPS];								//RJS 09Feb98
	FileNum 		whichDir;
public:
	LandMapNumRecord();
	inline ~LandMapNumRecord();
	inline void Reset(FileNum);
	inline void Switch(FileNum);
	inline ImageMapDescPtr operator[] (int i);
};
#undef new
class CDataBlock
{
	friend class CCacheBlock;
	friend class CMigLand;
private:
	static CDataBlockAllocator* pAlloc;

	CCacheBlock*	pCacheBlock;
	ULong			dataLen;
	UByte			pDataStart;
public:
	CDataBlock()	{pCacheBlock=NULL;dataLen=0L;}
	CDataBlock(CCacheBlock*,ULong, UByte*);
	~CDataBlock();

	inline void* DataStart() {return (void*)&pDataStart;}
	inline ULong DataLen() {return dataLen;}

	inline void* operator new(size_t sz,ULong dataLen);

	inline void operator delete(void*) {assert(false&&" I can't be deleted like this!");}
};

class CPrimaryDB
{
	friend class CPrimaryCB;
	friend class CMigLand;
private:
	static CPrimaryDBAllocator* pAlloc;

	CPrimaryCB*		pCacheBlock;
	ULong			dataLen;
	UByte			pDataStart;
public:
	CPrimaryDB() {pCacheBlock=NULL;dataLen=0L;}
	CPrimaryDB(CPrimaryCB*,ULong, UByte*);
	~CPrimaryDB();

	inline void* DataStart() {return (void*)&pDataStart;}
	inline ULong DataLen() {return dataLen;}

	inline void* operator new(size_t sz,ULong dataLen);
	inline void operator delete(void*) {assert(false&&" I can't be deleted like this!");}
};
#define	new DEBUG_NEW

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

class CLandColor
{
private:
	enum {	TEXTURE_LIMIT=128,
			TEXTURE_MASK=31,
			TXTROT_NORTH=0x00,
			TXTROT_EAST=0x20,
			TXTROT_SOUTH=0x40,
			TXTROT_WEST=0x80,
			TXTROT_MASK=TXTROT_NORTH+TXTROT_EAST+TXTROT_SOUTH+TXTROT_WEST};

	UByte			ubType;
	UByte			ubRotation;
	ImageMapDescPtr	pImage;

public:
	CLandColor(UByte cval=0)
	{
		if (cval<TEXTURE_LIMIT)
		{
			ubRotation=cval&TXTROT_MASK;
			FileNum	f=FileNum(FIL_IMG10000+(cval&TEXTURE_MASK));
			LandMapNum lmnMapNo(f,DIR_LANDMAP2);
			pImage=lmnMapNo.GetLandMapPtr();
		}
		else pImage=NULL;
	}
	~CLandColor() {}

	UByte 	Rotation() {return ubRotation;}
	ImageMapDescPtr pImg() {return pImage;}
	UByte	pCol() {return pImage!=NULL?*(pImage->body):UByte(254);}
};

class MovingItem;

class CMigLand
{
private:

	UByte	lastGroundHit;

	enum	{PRIMARYCACHE_SIZE=0x220000,	//
			 PRIMARYCACHE_MAXELEMENTS=256};	// .25 Meg primary cache

	enum	{SECONDLAYER_ENTRIES=8,
			THIRDLAYER_ENTRIES=1024,
			FILEOFFSET_ENTRIES=9216};

	enum	{MAX_DECOMP_BLOCKS=4};

	ULong	blocksDecompressed;

	CMigFile*			pMigFile;

	CDecompressData*	pMigLandDecomp;

	enum CurrentFile {CF_BAD,CF_NORTH,CF_EAST,CF_SOUTH,CF_WEST};

	CMigIndex* pMigIndex;
	CMigFMan* pMigFMan;

	CurrentFile	currentFile;

	ANGLES	currentDirection;

	ANGLES	ClampAngle(ANGLES a);

	public:

	CMigLand();
	~CMigLand();
	void BigInit(MovingItem*);
	void SetViewpoint(MovingItem* ip);// {pMigFile->SetViewpoint(ip);}
	bool ProcessSeekRequests();// {pMigFile->ProcessSeekRequests();}
	void SetLVector(SLong li,SLong lj,SLong lk);

	DataRecord GetData(ULong,ULong,ULong,DataRecord&);
	DataRecord GetData(ULong,ULong);
	UByte*	MakeIData(const DataRecord&,const ULong);

	SLong GetAltitude(COORDS3D&,UByte* pAreaType=NULL,bool fReallyGetData=false);
	SLong GetRoughAltitude(SLong,SLong,SLong);
	inline UByte GetAreaType();
	void GetShadowAngles(COORDS3D&,ANGLES,ANGLES&,ANGLES&);

	void ResetDecompCount() {blocksDecompressed=0;}
};

struct AltPointsHdr
{
	UByte	vertexCount,
			topEdgePoints,
			rightEdgePoints,
			bottomEdgePoints,
			leftEdgePoints;
	ULong	edgePointsStart;
	ULong	edgeListStart;
	ULong	polyDataStart;
	ULong	edgeCount;
	SLong	minAlt,maxAlt;
	ULong	checksum;
	void	MakeChecksum() 
	{
		checksum=	vertexCount+	topEdgePoints+
					rightEdgePoints+bottomEdgePoints+
					leftEdgePoints+	edgePointsStart+
					edgeListStart+	polyDataStart+
					edgeCount;
	}
	bool	CheckChecksum()
	{
		return checksum==vertexCount+	topEdgePoints+
					rightEdgePoints+	bottomEdgePoints+
					leftEdgePoints+		edgePointsStart+
					edgeListStart+		polyDataStart+
					edgeCount?true:false;
	}
};

struct DataRecord{
	void* pData;
	ULong dataLen;
};

#endif



