//------------------------------------------------------------------------------
//Filename       lstream.h
//System         
//Author         Paul.   
//Date           Thu 11 Jul 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	LSTREAM_Included
#define	LSTREAM_Included

#define	DEFAULT_LSTREAM 0

#ifdef	COMMENT


#include	"DOSDefs.h"
#include	"Palette.h"
#include	"Worldinc.h"
#include	"imagemap.h"
#include	"landscap.h"
#include	"hardpasm.h"
#include	"Mytime.h"
#include	"viewsel.h"											//PD 28Aug96

//DeadCode PD 08Aug97 extern	Bool	Demoversion;									//PD 28Jan97

enum	LandMapNum{LandMapNumMIN=0,LandMapNumMAX=64,LandMapNum_Align=0x7FFF};

MAKEFIELD (LandMapNum,LandMapNumMIN,LandMapNumMAX);

//origin currently set to south west corner of block 340000		//PD 10Nov96
//DeadCode PD 12Nov96 const	SLong WorldBaseX = 0x1000000;							//PD 10Nov96
//DeadCode PD 12Nov96 const	SLong WorldBaseZ = 0x1800000;							//PD 10Nov96

//Old_Code PD 28Jan97 #ifndef	DEMOVERSION												//PD 27Jan97
//Old_Code PD 28Jan97 	const 	int 	BIG_FILE_SIZE =	112;
//Old_Code PD 28Jan97 	const	SLong	Area1SW_X = 16777216;
//Old_Code PD 28Jan97 	const	SLong	Area1SW_Z = 20971520;
//Old_Code PD 28Jan97 	const	SLong	Area1NE_X = 31457280;
//Old_Code PD 28Jan97 	const	SLong	Area1NE_Z = 35651584;
//Old_Code PD 28Jan97 #else
//Old_Code PD 28Jan97 	const 	int 	BIG_FILE_SIZE =	56;
//Old_Code PD 28Jan97 	const	SLong	Area1SW_X = 0x12e0000;
//Old_Code PD 28Jan97 	const	SLong	Area1SW_Z = 0x1800000;
//Old_Code PD 28Jan97 	const	SLong	Area1NE_X = 0x19e0000;
//Old_Code PD 28Jan97 	const	SLong	Area1NE_Z = 0x1f00000;
//Old_Code PD 28Jan97 #endif

//Old_Code PD 28Jan97 const	SLong	Area2SW_X = 34603008;							//PD 27Jan97
//Old_Code PD 28Jan97 const	SLong	Area2SW_Z = 8388608;
//Old_Code PD 28Jan97 const	SLong	Area2NE_X = 49283072;
//Old_Code PD 28Jan97 const	SLong	Area2NE_Z = 23068672;

const	int	DestBytesPerScanLine = 257;
const	int	AltBytesPerScanLine = 35;
const	int DestHeight = 257;
const	int MaxImageMapsNo = 36;
const	int	Maps512End = 11;									//PD 17Sep96
const	int	ColourRanges = 14;
const	int	ColourDataSize = DestBytesPerScanLine*DestBytesPerScanLine+1;
const	int	AltDataSize = AltBytesPerScanLine*AltBytesPerScanLine+1;

//DeadCode PD 08Nov96 const	int	FilesListWidth = 8;
//DeadCode PD 08Nov96 const	int	FilesListHeight = 8;

const	ULong	SectorMask = 0x0000FFFF;
const	int	SectorShift = 16;

const	SLong	WORLD_BIG_WZ = 0x07FFFFFFF;

const	UByte	RoadColoursEnd = 16;
const	UByte	RoadColoursMask = 0xF0;
const	UByte	RoadColoursTR = 0;
const	UByte	RoadColoursBL = 1;
const	UByte	RoadColoursBR = 2;

const	int	MaxLDSAliasX2	=	256;
const	int	MaxLDSAliasX1	=	256;
const	int	MaxLDSNormal	=	256;
const	int	MaxLDSHalf		=	256;
const	int	MaxLDSQuarter	=	256;
const	int	MaxLDSEighth	=	128;							//PD 15Apr97
const	int	MaxLDSSixteenth	=	128;							//PD 15Apr97
const	int BIG_TILES_MAX	=	16;								//PD 17Dec96

const	int	FadeStartRangeLo = 131072>>XZ_COL_SCALE;			//PD 05Sep96
const	int	FadeStartRangeHi = 65536>>XZ_COL_SCALE;				//PD 05Sep96
const	int FadeEndRange = (524288-98304)>>XZ_COL_SCALE;		//PD 05Sep96

const	int	MaxCacheReqs	=	256;

//Max. size colour data can be and still leave room for
//uncompressed altitude data
const	int ROOM_FOR_UNCOMP_ALT = 2871;	//4K - 35*35

// values for altitude compression #2

const	int	LEVEL2BITS		= 1;
const	int	LEVEL2BITS_MASK	= 1;
const	int	MAXLEVEL2		= 1;

const	int	SINGLEBITS		= 1;
const	int	SINGLEBITS_MASK	= 1;
const	int	MAXSINGLEDELTA	= 1;

const	UWord MaxDecompressionTime = 3;	//centiseconds

#ifdef __WATCOMC__
extern	UByte ASM_GetBits(UByte*,int,int);
#pragma	aux ASM_GetBits = \
		"mov	ax,word ptr ds:[esi]"	\
		"shr	ax,cl"					\
		"and	ax,dx"					\
		parm	[esi] [ecx] [edx]		\
		modify	[ax]					\
		value	[al]
#else
#ifdef __MSVC__
inline UByte ASM_GetBits(UByte* num1,int num2,int num3)
{
	UByte	retval;
    _asm
    {
		push	eax
		push	ecx
		push	edx
		push	esi
		mov 	esi,num1
		mov 	ecx,num2
		mov 	edx,num3
		mov		ax,word ptr ds:[esi]
		shr		ax,cl
		and		ax,dx
		mov 	retval,al
		pop		esi
		pop		edx
		pop		ecx
		pop		eax
    }
    return retval;
}

#endif
#endif

#ifdef __WATCOMC__
extern	UByte ASM_GetByte(UByte*,int);
#pragma aux ASM_GetByte = \
		"mov	ax,word ptr ds:[esi]"	\
		"shr	ax,cl"					\
		parm [esi] [ecx]				\
		modify [ax]						\
		value [al]
#else
#ifdef __MSVC__
inline UByte ASM_GetByte(UByte* num1,int num2)
{
	UByte	retval;
    _asm
    {
		push	eax
		push	ecx
		push	esi
		mov 	esi,num1
		mov 	ecx,num2
		mov		ax,word ptr ds:[esi]
		shr		ax,cl
		mov 	retval,al
		pop		esi
		pop		ecx
		pop		eax
    }
    return retval;
}

#endif
#endif

#ifdef __WATCOMC__
extern	UByte ASM_GetScanLines(UByte*,int);
#pragma aux ASM_GetScanLines = \
		"mov	ax,word ptr ds:[esi]"	\
		"shr	ax,cl"					\
		"and	al,7"					\
		parm [esi] [ecx]				\
		modify [ax]						\
		value [al]
#else
#ifdef __MSVC__
inline UByte ASM_GetScanLines(UByte* num1,int num2)
{
	UByte	retval;

    _asm
    {
		push	eax
		push	ecx
		push	esi
		mov 	esi,num1
		mov 	ecx,num2
		mov		ax,word ptr ds:[esi]
		shr		ax,cl
		and		al,7
		mov 	retval,al
		pop		esi
		pop		ecx
		pop		eax
    }
    return retval;
}

#endif
#endif

#ifdef __WATCOMC__
extern	SByte ASM_GetDelta(UByte*,int);
#pragma aux ASM_GetDelta = \
		"mov	ax,word ptr ds:[esi]"	\
		"shr	ax,cl"					\
		"and	ax,7"					\
		"shr	al,1"					\
		"sbb	ah,0"					\
		"xor	al,ah"					\
		"sub	al,ah"					\
		parm [esi] [ecx]				\
		modify [ax]						\
		value [al]
#else
#ifdef __MSVC__
inline SByte ASM_GetDelta(UByte* num1,int num2)
{
	SByte	retval;

    _asm
    {
		push	eax
		push	ecx
		push	esi
		mov 	esi,num1
		mov 	ecx,num2
		mov		ax,word ptr ds:[esi]
		shr		ax,cl
		and		ax,7
		shr		al,1
		sbb		ah,0
		xor		al,ah
		sub		al,ah
		mov 	retval,al
		pop		esi
		pop		ecx
		pop		eax
    }
    return retval;
}

#endif
#endif
#ifdef __WATCOMC__
extern	Bool ASM_GetBit(UByte*,int);
#pragma aux	ASM_GetBit = \
		"xor	ax,ax"					\
		"mov	al,byte ptr ds:[esi]"	\
		"shr	ax,cl"					\
		"and	al,1"					\
		parm [esi] [ecx]				\
		modify [ax]						\
		value [al]
#else
#ifdef __MSVC__
inline Bool ASM_GetBit(UByte* num1,int num2)
{
	UByte	retval;
    _asm
    {
		push	eax
		push	ecx
		push	esi
		mov 	esi,num1
		mov 	ecx,num2
		xor		ax,ax
		mov		al,byte ptr ds:[esi]
		shr		ax,cl
		and		al,1
		mov 	retval,al
		pop		esi
		pop		ecx
		pop		eax
    }
    return (Bool)retval;
}

#endif
#endif
#ifdef __WATCOMC__
extern	void 	ASM_HorizAliasX1(UByte*,UByte*,UByte*);
#pragma	aux		ASM_HorizAliasX1 = 		\
		"xor	eax,eax"				\
		"mov	ax,word ptr [esi]"		\
		"mov	byte ptr [edi],al"		\
		"mov	al,byte ptr [ebx+eax]"	\
		"mov	byte ptr [edi+1],al"	\
		parm	[esi] [edi] [ebx]		\
		modify	[eax]
#else
#ifdef __MSVC__
inline void 	ASM_HorizAliasX1(UByte* num1,UByte* num2,UByte* num3)
{
    _asm
    {
		push	eax
		push	ebx
		push	esi
		push	edi
		mov 	esi,num1
		mov 	edi,num2
		mov 	ebx,num3
		xor		eax,eax
		mov		ax,word ptr [esi]
		mov		byte ptr [edi],al
		mov		al,byte ptr [ebx+eax]
		mov		byte ptr [edi+1],al
		pop		edi
		pop		esi
		pop		ebx
		pop		eax
    }
}

#endif
#endif
#ifdef __WATCOMC__
extern	void 	ASM_VertAliasX1(UByte*,UByte*);
#pragma	aux		ASM_VertAliasX1	=		\
		"xor	eax,eax"				\
		"mov	al,byte ptr [edi-32]"	\
		"mov	ah,byte ptr [edi+32]"	\
		"mov	al,byte ptr [ebx+eax]"	\
		"mov	byte ptr [edi],al"		\
		parm	[edi] [ebx]				\
		modify	[eax]
#else
#ifdef __MSVC__
inline void 	ASM_VertAliasX1(UByte* num1,UByte* num2)
{
    _asm
    {
		push	eax
		push	ebx
		push	edi
		mov 	edi,num1
		mov 	ebx,num2
		xor		eax,eax
		mov		al,byte ptr [edi-32]
		mov		ah,byte ptr [edi+32]
		mov		al,byte ptr [ebx+eax]
		mov		byte ptr [edi],al
		pop		edi
		pop		ebx
		pop		eax
    }
}

#endif
#endif
#ifdef __WATCOMC__
extern	void 	ASM_HorizAliasX2(UByte*,UByte*,UByte*);
#pragma	aux		ASM_HorizAliasX2 = 		\
		"xor	eax,eax"				\
		"xor	edx,edx"				\
		"mov	ax,word ptr [esi]"		\
		"mov	byte ptr [edi],al"		\
		"mov	dl,byte ptr [ebx+eax]"	\
		"mov	byte ptr [edi+2],dl"	\
		"mov	dh,al"					\
		"mov	al,byte ptr [ebx+edx]"	\
		"mov	byte ptr [edi+1],al"	\
		"mov	dh,ah"					\
		"mov	al,byte ptr [ebx+edx]"	\
		"mov	byte ptr [edi+3],al"	\
		parm	[esi] [edi] [ebx]		\
		modify	[eax edx]
#else
#ifdef __MSVC__
inline void 	ASM_HorizAliasX2(UByte* num1,UByte* num2,UByte* num3)
{
    _asm
    {
		push	eax
		push	ebx
		push	ecx
		push	edx
		push	esi
		push	edi
		mov 	esi,num1
		mov 	edi,num2
		mov 	ebx,num3
		xor		eax,eax
		xor		edx,edx
		mov		ax,word ptr [esi]
		mov		byte ptr [edi],al
		mov		dl,byte ptr [ebx+eax]
		mov		byte ptr [edi+2],dl
		mov		dh,al
		mov		al,byte ptr [ebx+edx]
		mov		byte ptr [edi+1],al
		mov		dh,ah
		mov		al,byte ptr [ebx+edx]
		mov		byte ptr [edi+3],al
		pop		edi
		pop		esi
		pop		edx
		pop		ecx
		pop		ebx
		pop		eax
    }
}

#endif
#endif
#ifdef __WATCOMC__
extern	void 	ASM_VertAliasX2(UByte*,UByte*);
#pragma	aux		ASM_VertAliasX2	=		\
		"xor	eax,eax"				\
		"xor	edx,edx"				\
		"mov	al,byte ptr [edi-64]"	\
		"mov	ah,byte ptr [edi+64]"	\
		"mov	dl,byte ptr [ebx+eax]"	\
		"mov	byte ptr [edi],dl"		\
		"mov	dh,al"					\
		"mov	al,byte ptr [ebx+edx]"	\
		"mov	byte ptr [edi-32],al"	\
		"mov	dh,ah"					\
		"mov	al,byte ptr [ebx+edx]"	\
		"mov	byte ptr [edi+32],al"	\
		parm	[edi] [ebx]				\
		modify	[eax edx]
#else
#ifdef __MSVC__
inline void 	ASM_VertAliasX2(UByte* num1,UByte* num2)
{
    _asm
    {
		push	eax
		push	ebx
		push	edx
		push	esi
		push	edi
		mov 	edi,num1
		mov 	ebx,num2
		xor		eax,eax
		xor		edx,edx
		mov		al,byte ptr [edi-64]
		mov		ah,byte ptr [edi+64]
		mov		dl,byte ptr [ebx+eax]
		mov		byte ptr [edi],dl
		mov		dh,al
		mov		al,byte ptr [ebx+edx]
		mov		byte ptr [edi-32],al
		mov		dh,ah
		mov		al,byte ptr [ebx+edx]
		mov		byte ptr [edi+32],al
		pop		edi
		pop		esi
		pop		edx
		pop		ebx
		pop		eax
    }
}

#endif
#endif
#ifdef __WATCOMC__
extern	void 	ASM_DeRezX1(UByte*,UByte*,UByte*);
#pragma aux		ASM_DeRezX1 = 			\
		"xor	eax,eax"				\
		"mov	ax,word ptr [esi]"		\
		"mov	dl,byte ptr [ebx+eax]"	\
		"mov	ax,word ptr [esi+2]"	\
		"mov	dh,byte ptr [ebx+eax]"	\
		"mov	word ptr [edi],dx"		\
		parm	[esi] [edi] [ebx]		\
		modify	[eax dx]
#else
#ifdef __MSVC__
inline void 	ASM_DeRezX1(UByte* num1,UByte* num2,UByte* num3)
{
	_asm {	int 3 };

//TempCode PD 29Oct97     __asm
//TempCode PD 29Oct97     {
//TempCode PD 29Oct97 		mov esi,num1;
//TempCode PD 29Oct97 		mov edi,num2;
//TempCode PD 29Oct97 		mov ebx,num3;
//TempCode PD 29Oct97 		xor	eax,eax;
//TempCode PD 29Oct97 		mov	ax,word ptr [esi];
//TempCode PD 29Oct97 		mov	dl,byte ptr [ebx+eax];
//TempCode PD 29Oct97 		mov	ax,word ptr [esi+2];
//TempCode PD 29Oct97 		mov	dh,byte ptr [ebx+eax];
//TempCode PD 29Oct97 		mov	word ptr [edi],dx;
//TempCode PD 29Oct97     }
}

#endif
#endif

#ifdef __WATCOMC__
extern	SWord	ASM_UpdateJitter(SWord );
#pragma	aux		ASM_UpdateJitter =	\
		"add	al,0x091"			\
		"ror	al,3"				\
		parm	[ax]				\
		value	[ax]
#else
#ifdef __MSVC__
inline SWord	ASM_UpdateJitter(SWord num)
{
	SWord	retval;
    _asm
    {
		push	eax
		mov 	ax,num
		add 	al,0x091
		ror 	al,3
		mov 	retval,ax
		pop		eax
    }
    return retval;
}

#endif
#endif
//Old_Code DAW 27Jan97 const int BIG_FILE_SIZE		=	112;
const int BIG_CACHE_SIZE	=	21;
const int BIG_EDGE_SIZE		=	5;

class	ViewPoint;
class	LSFileBlock;
typedef	class LSFileBlock *LSFileBlockPtr;
class	LSFileBlock
{
	void*			data;
	public:
	LSFileBlock(	FileNum myfile,
					SLong length=0x1000,
					SLong offset=0,
					Bool skipread=TRUE)
	{data=FILEMAN.loadCDfile(myfile,length,offset,skipread);}
	~LSFileBlock()
	{if (data!=NULL) delete[] ((unsigned char*)data);data=NULL;}
	void *GetData()	{return (data);}
};

class	Land_Stream
{
	SLong	AreaBaseX,AreaBaseZ;

	FileNum	AreaFiles[4];

	struct	CachedDataBlock
	{
	 	UByte	data[4096];
	};

	struct	CachedFileBlock
	{
//PD 21Nov96 - for debug only
		SLong	fileblk;										//PD 21Nov96
//PD 21Nov96 - for debug only

		CachedDataBlock	data;
		CachedFileBlock() {}
		CachedFileBlock(ULong* datp)
		{ULong* dest=(ULong*)data.data;
		for(int ccnt=1024;ccnt;ccnt--)
		{*dest++=*datp++;}
		}
	};

	typedef	struct CachedFileBlock *CachedFileBlockP;

	enum	WhichWay {WW_north=0,WW_east,WW_south,WW_west};

	CachedFileBlockP bigareacahe[BIG_CACHE_SIZE*BIG_CACHE_SIZE];
	COORDS3D		 bufferbase;
	CachedFileBlockP rcbuffer0[BIG_CACHE_SIZE*BIG_EDGE_SIZE];
	COORDS3D		 rcbuff0;
	CachedFileBlockP rcbuffer1[BIG_CACHE_SIZE*BIG_EDGE_SIZE];
	COORDS3D		 rcbuff1;

	WhichWay		 currentdirection;
	FileNum			 currentfilenum;

	friend	class fileblock;									//PD 27Aug96

	fileblockptr landmaps[LandMapNumMAX];						//PD 27Aug96

	struct	SeekStruc;
	struct	CacheBlock;
	struct	CacheReqBlock;
	struct	BigCacheBlock;

	typedef	struct CacheBlock *CacheBlockP;
	typedef struct CacheReqBlock *CacheReqP;
	typedef struct BigCacheBlock *BigCacheBlockP;
	typedef	struct SeekStruc	*SeekStrucP;

	struct	SeekStruc
	{
		SeekStrucP	next;
		FileNum		filenum;
		ULong		seekpos;
		UByte*		destdata;

		SeekStruc()
			{next=NULL;filenum=INVALIDFILENUM;seekpos=0;}
		SeekStruc(FileNum f,ULong sp,UByte* ddp)
			{next=NULL;
			filenum=f;
			seekpos=sp;
			destdata=ddp;}
	};

	struct	CacheBlock
	{
		//For search...

		CacheBlockP	parent,
					northp,	//increasing world Z
					eastp;	//increasing world X

		//For discard...

		CacheBlockP	prev,
					next;

		//Rest of data...

		SLong		wx,
					wz;

		SLong		discarded;

		LandMapDescPtr											//PD 27Aug96
					data;
	};

	struct	BigCacheBlock
	{
		//For search...

		BigCacheBlockP	parent,
						northp,	//increasing world Z
						eastp;	//increasing world X

		//For discard...

		BigCacheBlockP	prev,
						next;

		//Rest of data...

		SLong		wx,
					wz;

		UByte*		data;
	};

	struct	CacheReqBlock
	{
		CacheReqP	next;
		SLong		wx, wz;
	};

	enum LDataScales
	{
		LDS_AliasX2=0x0,
		LDS_AliasX1,
		LDS_Normal,
		LDS_Half,
		LDS_Quarter,
		LDS_Eighth,
		LDS_Sixteenth,
		LDS_MAX
	};

	typedef	union
	{
		Colour			color;
		ImageMapDescPtr	imagep;
	}
	ColorIndex,
	*ColorIndexP;

	SeekStrucP	masterseeklist;									//PD 31Oct96

	CacheBlockP	cachescale[LDS_MAX];

	CacheBlockP	dumpscale[LDS_MAX];

	BigCacheBlockP	bigcachep[1],
					bigdumpp[1];

	SLong			bigcachecount,
					bigcachemax;


	CacheReqP	cachereq[LDS_MAX];

	UByte*		tbuffer;										//PD 25Sep96

	UByte*		preshadetable;									//PD 16Jan97

	SLong		cachecount[LDS_MAX];

	SLong		cachemax[LDS_MAX];

	CacheReqBlock	cachereqblks[MaxCacheReqs];

	UByte*	beginbuffer;

	UByte*	ailtbl16p;

	UByte*	ailtbl04p;

	UByte*	ailclrindexp;

	UByte*	gColindexp;

	SByte*	shadeindexp;

	FileNum*	cddatap;

	LandMapDescPtr	dummyimagep;								//PD 27Aug96

	COORDS3D currpos;

	LandMapNum*	lpLandMapFList;

	int	ioriginx, ioriginz;

	int	FadeStartRange;

	ColorIndex 	colorindex[256];
	UByte		incolindex[256];

	FileNum	*fileslistp;	//For Demo only!!!!

	Bool	firstcall;

	public:

	int 	BIG_FILE_SIZE;
	SLong	Area1SW_X;
	SLong	Area1SW_Z;
	SLong	Area1NE_X;
	SLong	Area1NE_Z;
	SLong	Area2SW_X;
	SLong	Area2SW_Z;
	SLong	Area2NE_X;
	SLong	Area2NE_Z;

	UByte*	endbuffer;											//PD 09Jan97

	SLong	requestcount;										//PD 01Aug96

	LandMapNumField	lmnf;										//PD 27Aug96

	LandMapNumField* landmapfield;								//PD 27Aug96

	CON		Land_Stream();

	DES 	~Land_Stream();

	void	SetupLandStuff();									//DAW 27Oct97

	void	SetBlockDelete(Bool);								//PD 09Jan97
	Bool	ProcessingSeeks() {return (Bool)(masterseeklist!=NULL);}	//PD 04Oct97
	Bool	OverTheEdge(itemptr,SLong&,SLong&);
	Bool	DataValid(COORDS3D&);
	Window*	currwin;
	void	ReInit();	//JIM
	void	ResetEverything();									//PD 22Nov96
	void	BigInit(ViewPoint* v=NULL );											//PD 18Nov96
	void	BigRebuild(MovingItem*);								//PD 11Nov96

	void	ProcessSeekRequests();								//PD 18Nov96
	void	ProcessSeekRequests2();								//PD 11Nov96
	void	OutputAltDataAsH8();								//PD 03Oct96
	void	CDBlockWorldCoords(SLong seekpos,COORDS3D& coords);	//PD 25Oct96
	SLong	CDBlockIndexNumber(COORDS3D& );						//PD 02Oct96
	SLong	FindGroundHeight(COORDS3D& );
	void	GetTileCoords(COORDS3D&,vector&,vector&,vector&,vector&);//PD 29Sep96

	void	InitialiseCache();									//PD 01Aug96
	void	DeleteCache();										//PD 01Aug96
	Bool	DeleteDisplayCache(Bool onelayeronly=FALSE);										//PD 01Aug96
	void	ProcessRequests();									//PD 01Aug96
	void	ProcessRequestsNoLimit();							//PD 20Sep96
	void	RezChanged(Window* win,ScreenRez&);								//PD 06Jun97

	LandMapDescPtr RequestBlock(SLong,SLong,SWord);				//PD 27Aug96
	LandMapDescPtr RequestBlockNF(SLong,SLong,SWord);			//PD 15Apr97
	void RequestInitBlock(SLong,SLong,SWord);					//PD 16Dec96

	ImageMapDescPtr	GetLandMapPtr(LandMapNum lmn);

	void	UnLoadLandMaps()
	{
		for (int count=LandMapNumMIN;count<(int)landmapfield->MAX;count++)
		{
			*landmapfield %= (LandMapNum)count;
			delete landmaps[count];
			landmaps[count]=NULL;
		}
	}

	private:

//DeadCode PD 12Nov96 	void	TestCache();										//PD 12Nov96

	void	SetArea(MovingItem*);								//PD 12Nov96

	void	StillGoingNorth();
	void	StillGoingEast();
	void	StillGoingSouth();
	void	StillGoingWest();
	void	NowGoingNorth(MovingItem*);
	void	NowGoingEast(MovingItem*);
	void	NowGoingSouth(MovingItem*);
	void	NowGoingWest(MovingItem*);
	void	ScrollEdge(CachedFileBlockP*);
	void	ScrollNorth();
	void	ScrollSouth();
	void	ScrollEast();
	void	ScrollWest();
	void	RecenterBuffer(SLong,SLong,SLong,SLong);

//Old_Code PD 20Aug97 	Bool	DiskAccessRequired(COORDS3D&);						//PD 20Aug97
	void	AddSeekRequest(SeekStruc&);							//PD 31Oct96
	void 	DecompressTile(UByte*,UByte*&);						//PD 25Sep96
	void	FakeTile(Colour,UByte*&);							//PD 04Oct96

	public:														//PD 20Aug97

	Bool	DiskAccessRequired(COORDS3D&);						//PD 20Aug97

	protected:

	Bool	FindCacheEntry(CacheBlockP* , SLong , SLong , CacheBlockP&);

	Bool	FindCacheEntry(BigCacheBlockP* , SLong , SLong , BigCacheBlockP&);//PD 20Sep96

	void	InsertCacheEntry(CacheBlockP* , CacheBlockP);

	void	InsertCacheEntry(BigCacheBlockP* , BigCacheBlockP);	//PD 20Sep96

	void	UnLinkCacheEntry(CacheBlockP* , CacheBlockP);

	void	UnLinkCacheEntry(BigCacheBlockP* , BigCacheBlockP);	//PD 20Sep96

	void	Init();

	UByte* 	GetBigTile(COORDS3D&);								//PD 20Sep96
	UByte* 	GetBigAltTile(COORDS3D&);							//PD 08Oct96

	void	Decompress(UByte* ,UByte* ,UByte*);
	void 	PartialDecompress(UByte*&);

	void	UnpackColorData(UByte*& ,UByte*);

	void	UnpackAltitudeData(Bool, UByte*& ,UByte*);
	void	UpdateAltitudeData(COORDS3D&,UByte*);				//PD 24Sep96

	void	AliasTile(UByte* ,UByte*);

	void	ShadeTile(UByte* ,UByte*);
	void	ApplyLShade(UByte* ,int ,SByte*, int);

	void	PlainColour(UByte, UByte*&, int&, UByte* );

	void	Maps512NoMirror(UByte, int, UByte*&, int&, UByte* );
	void	Maps512MirrorY(UByte, int, UByte*&, int&, UByte* );
	void	Maps512MirrorXY(UByte, int, UByte*&, int&, UByte* );
	void	Maps512MirrorX(UByte, int, UByte*&, int&, UByte* );

	void	Maps256NoMirror(UByte, UByte*&, int&, UByte* );
	void	Maps256MirrorY(UByte, UByte*&, int&, UByte* );
	void	Maps256MirrorXY(UByte, UByte*&, int&, UByte* );
	void	Maps256MirrorX(UByte, UByte*&, int&, UByte* );

	void	AddBlockRequest(SLong,SLong,LDataScales);			//PD 01Aug96
	CacheBlockP DecompressBlock(CacheReqP,LDataScales);			//PD 22Nov96
	void 	PartialDecompressBlock(CacheReqP);					//PD 08Oct96

	void	GetColourData(CacheBlockP,LDataScales);				//PD 01Aug96
	void	GetAltitudeDataOnly(CacheBlockP,LDataScales);		//PD 08Oct96

	void	DecompressAltitude(UByte*&, UByte*);				//PD 07Oct96
	void	BuildAltitudes(int,UByte*,UByte*&,int&,int);		//PD 23Sep96
	void	BuildMainBody(int,int,UByte*,UByte*&,int&);			//PD 23Sep96

	typedef	void SampleTile (	CacheBlockP,
								const COORDS3D&,
								UByte* );			//PD 01Aug96

	SampleTile	SampleTile400pc,
				SampleTile200pc,
				SampleTile100pc,
				SampleTile50pc,
				SampleTile25pc,
				SampleTile12pc,
				SampleTile6pc,									//PD 15Apr97
				
				SampleTile200pcNoAlias,							//PD 05Sep96
				SampleTile400pcNoAlias;							//PD 05Sep96

	void	FillTile(Colour, UByte*, SWord);					//PD 20Aug96

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GetCacheReqBlock
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Fri 23 Aug 1996
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
	CacheReqP	GetCacheReqBlock()
	{
		if (requestcount==MaxCacheReqs)
			return (NULL);

		CacheReqP retval = &cachereqblks[requestcount];

		requestcount++;

		return (retval);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	FlushRequests
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Fri 23 Aug 1996
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
	void	FlushRequests()
	{
		if (requestcount>0)
		{
			requestcount = 0;

			cachereq[LDS_AliasX2] =
				cachereq[LDS_AliasX1] =
				cachereq[LDS_Normal] =
				cachereq[LDS_Half] =
				cachereq[LDS_Quarter] = 
				cachereq[LDS_Eighth] = 
				cachereq[LDS_Sixteenth] = NULL;					//PD 15Apr97
		}
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WipeDest
//Author		Paul.   
//Date			Thu 11 Jul 1996
//
//Description	Wipes the destination buffer with colour 'ARTWORKMASK'
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	void 	WipeDest(UByte* ptr)
	{
		_asm {int 3};

    	#ifdef __WATCOMC__
		ASM_Splat(ARTWORKMASK * 0x01010101, ptr, 257 * 257 + 1);
    	#endif    
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindNextPosition
//Author		Paul.   
//Date			Thu 11 Jul 1996
//
//Description	Finds the next occurance of 'ARTWORKMASK' in the
//				destination buffer
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	void FindNextPosition(UByte*& ptr)
	{
 		while(*ptr!=(UByte )ARTWORKMASK) ptr++;
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetByte
//Author		Paul.   
//Date			Thu 11 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	UByte GetByte(UByte*& ptr, int& cnt)
	{
		//If bit position==0 then we're on a byte boundary so it's easy!

		if (!cnt)	return(*ptr++);

		UByte retval = ASM_GetByte(ptr,cnt);

		cnt += 8; cnt &= 0x07;

		ptr++;

		return (retval);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GetBits
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Thu 19 Sep 1996
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
	UByte GetBits(UByte*& ptr, int& cnt, int cbits, int cmask)
	{
  		UByte retval = ASM_GetBits(ptr,cnt,cmask);

		cnt += cbits;

		if (cnt<8)	return (retval);

		cnt &= 0x07;

		ptr++;

		return (retval);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetScanlines
//Author		Paul.   
//Date			Thu 11 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	int	GetScanLines(UByte*& ptr, int& cnt)
	{
		int	retval = ASM_GetScanLines(ptr,cnt);

		cnt	+= 3;

		if (cnt<8)	return (retval);

		cnt &= 0x07;

		ptr++;

		return (retval);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDelta
//Author		Paul.   
//Date			Thu 11 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	int	GetDelta(UByte*& ptr, int& cnt)
	{
		int	retval = ASM_GetDelta(ptr,cnt);

		cnt += 3;	//Delta + Sign bit

		if (cnt<8)	return (retval);

		cnt &= 0x07;

		ptr++;

		return (retval);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBit
//Author		Paul.   
//Date			Thu 11 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	int GetBit(UByte*& ptr, int& cnt)
	{
		int	retval = ASM_GetBit(ptr,cnt);

		if ((++cnt)==8)
		{
			cnt = 0; ptr++;
		}
		return (retval);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IGetSector
//Author		Paul.   
//Date			Thu 18 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	ULong	IGetSector(COORDS3D& coords)
	{
		int	sectorshift = XZ_COL_SCALE + 8; 	// 256*256 tiles of colour
												// data => shift of 8

		ULong sectorx = (coords.X>>sectorshift) & 0x0FFFF;

		ULong sectorz = (coords.Z>>sectorshift) & 0x0FFFF;

		return ((sectorz<<16) + sectorx);
	}

//Old_Code PD 09Nov96 	void	GetBigTileFile(	COORDS3D&	coords,
//Old_Code PD 09Nov96 							FileNum& 	f,
//Old_Code PD 09Nov96 							ULong& 		seekpos,
//Old_Code PD 09Nov96 							ULong& 		blksize);

	UByte*	GetBigTileFile(COORDS3D&);							//PD 09Nov96

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTileFile
//Author		Paul.   
//Date			Thu 18 Jul 1996
//
//Description	Calculate the file offset containing the data for
//				a particular area of ground
//
//Inputs		Coordinate information
//
//Returns		File offset of compressed data block
//
//------------------------------------------------------------------------------
	void	GetTileFile(COORDS3D& coords, int& x, int& z)
	{
//TempCode PD 08Nov96 		ULong	sector = IGetSector(coords);
//TempCode PD 08Nov96 
//TempCode PD 08Nov96 		x = (sector & SectorMask) % FilesListWidth;
//TempCode PD 08Nov96 
//TempCode PD 08Nov96 		sector = (sector >> SectorShift) & SectorMask;
//TempCode PD 08Nov96 
//TempCode PD 08Nov96 		z = sector % FilesListHeight;
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTileFile
//Author		Paul.   
//Date			Wed 31 Jul 1996
//
//Description	Calculate the file offset containing the data for
//				a particular area of ground
//
//Inputs		Coordinate information
//
//Returns		File offset of compressed data block
//
//------------------------------------------------------------------------------
	LandMapDescPtr CreateNewMap(LDataScales scale)
	{
		LandMapDescPtr	retval;

		switch (scale)
		{
			case LDS_AliasX2:
				retval = (LandMapDescPtr )(new UByte[sizeof(LandMapDesc)+32*33]);	//PD 29Aug96
				assert((retval)&&(" - LDS_AliasX2 create failed!"));
				retval->tilemap.width =
					retval->tilemap.height = 5;					//PD 29Aug96
				break;

			case LDS_AliasX1:
				retval = (LandMapDescPtr )(new UByte[sizeof(LandMapDesc)+32*33]);	//PD 29Aug96
				assert((retval)&&(" - LDS_AliasX1 create failed!"));
				retval->tilemap.width =
					retval->tilemap.height = 5;					//PD 29Aug96
				break;

#ifdef __FAR_LAND__
			case LDS_Sixteenth:
				retval = (LandMapDescPtr )(new UByte[sizeof(LandMapDesc)+16*17]);
				assert((retval)&&(" - LDS_Sixteenth create failed!"));
				retval->tilemap.width =
					retval->tilemap.height = 4;
				break;
#endif
			default:
				retval = (LandMapDescPtr )(new UByte[sizeof(LandMapDesc)+32*32]);	//PD 29Aug96
				assert((retval)&&(" - LDS_?? create failed!"));
				retval->tilemap.width =
					retval->tilemap.height = 5;					//PD 29Aug96
				break;

		}
		return (retval);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	InsertInDiscardList
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Thu 22 Aug 1996
//Modified	
//
//Description	Puts a block at the head of the discard list
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
	void	InsertInDiscardList(LDataScales scale,CacheBlockP blockp)
	{
		CacheBlockP* listheadp = &dumpscale[scale];

		CacheBlockP	scanp = *listheadp;

		*listheadp = blockp;

		blockp->prev = NULL;

		blockp->next = scanp;

		if (scanp!=NULL)
			scanp->prev = blockp;
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	InsertInDiscardList
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Thu 22 Aug 1996
//Modified	
//
//Description	Puts a block at the head of the discard list
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
	void	InsertInDiscardList(BigCacheBlockP* listheadp,BigCacheBlockP blockp)
	{
		BigCacheBlockP	scanp = *listheadp;

		*listheadp = blockp;

		blockp->prev = NULL;

		blockp->next = scanp;

		if (scanp!=NULL)
			scanp->prev = blockp;
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	UpdateDiscardList
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Thu 22 Aug 1996
//Modified	
//
//Description	Puts a block at the head of the discard list
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
	void	UpdateDiscardList(LDataScales scale,CacheBlockP blockp)
	{
		CacheBlockP* listheadp = &dumpscale[scale];

		CacheBlockP	scanp = *listheadp;

		if (scanp!=blockp)
		{
			//First, remove the block from 
			//its current position in the list

			blockp->prev->next = blockp->next;

			if (blockp->next!=NULL)
				blockp->next->prev = blockp->prev;

			//Then, add it to the start of the list

			blockp->prev = NULL;

			blockp->next = scanp;

			*listheadp = blockp;

			scanp->prev = blockp;
		}
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	UpdateDiscardList
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Thu 22 Aug 1996
//Modified	
//
//Description	Puts a block at the head of the discard list
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
	void	UpdateDiscardList(BigCacheBlockP* listheadp,BigCacheBlockP blockp)
	{

		BigCacheBlockP	scanp = *listheadp;

		if (scanp!=blockp)
		{
			//First, remove the block from 
			//its current position in the list

			blockp->prev->next = blockp->next;

			if (blockp->next!=NULL)
				blockp->next->prev = blockp->prev;

			//Then, add it to the start of the list

			blockp->prev = NULL;

			blockp->next = scanp;

			*listheadp = blockp;

			scanp->prev = blockp;
		}
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	FindDiscardableBlock
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Thu 22 Aug 1996
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
	CacheBlockP FindDiscardableBlock(LDataScales scale)
	{
		CacheBlockP* listheadp = &dumpscale[scale];

		CacheBlockP	scanp = *listheadp;

		//If nothing to discard then return NULL

		if (scanp==NULL)	return (scanp);

		//Find the last entry in the list

		while (scanp->next!=NULL)	scanp=scanp->next;

		//Check to see if the last entry is
		//also the first entry

		if (scanp==*listheadp)
			*listheadp = NULL;
		else
			scanp->prev->next = NULL;

		//return pointer to the block (removed from the discard list)

		return (scanp);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	FindDiscardableBlock
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Thu 22 Aug 1996
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
	BigCacheBlockP FindDiscardableBlock(BigCacheBlockP* listheadp)
	{
		BigCacheBlockP	scanp = *listheadp;

		//If nothing to discard then return NULL

		if (scanp==NULL)	return (scanp);

		//Find the last entry in the list

		while (scanp->next!=NULL)	scanp=scanp->next;

		//Check to see if the last entry is
		//also the first entry

		if (scanp==*listheadp)
			*listheadp = NULL;
		else
			scanp->prev->next = NULL;

		//return pointer to the block (removed from the discard list)

		return (scanp);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GetDirectionFlags
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Fri 8 Nov 1996
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
	WhichWay GetDirectionFlags(MovingItemPtr miptr)
	{
		UWord		lhdg;
		WhichWay 	whichway;

		lhdg = (UWord )miptr->hdg;

		if (lhdg<=0x2000 || lhdg>0xE000)
			whichway=WW_north;
		else
		{
			if (lhdg>0x2000 && lhdg<=0x6000)
	 			whichway=WW_east;
			else
			{
				if (lhdg>0x6000 && lhdg<=0xA000)
					whichway=WW_south;
				else
					whichway=WW_west;
			}
		}
		return (whichway);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GetDirectionFlags2
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Tue 19 Nov 1996
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
	WhichWay GetDirectionFlags2(MovingItem* fselitemp)
	{
		SLong		xindex,
					zindex;
		COORDS3D	lcoords;

		lcoords = fselitemp->World;
		xindex = (lcoords.X>>8+XZ_COL_SCALE) - (bufferbase.X>>8+XZ_COL_SCALE);
		zindex = (bufferbase.Z>>8+XZ_COL_SCALE) - (lcoords.Z>>8+XZ_COL_SCALE);

		if (zindex<=5)	return(WW_north);
		if (zindex>=15)	return(WW_south);
		if (xindex<=5)	return(WW_west);
		return(WW_east);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	GetFileOffset
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Fri 8 Nov 1996
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
	SLong GetFileOffset(WhichWay whichway,SLong ix,SLong iz)
	{
		SLong	offset;

		ix -= AreaBaseX;
		iz -= AreaBaseZ;

		ix >>=(XZ_COL_SCALE+8);
		iz >>=(XZ_COL_SCALE+8);

		switch (whichway)
		{
			case WW_north:
				offset = (BIG_FILE_SIZE * iz) + (BIG_FILE_SIZE-1 - ix);
				break;
			case WW_east:
				offset = (BIG_FILE_SIZE * ix) + iz;
				break;
			case WW_south:
				offset = ((BIG_FILE_SIZE-1 - iz)*BIG_FILE_SIZE) + ix;
				break;
			case WW_west:
				offset = ((BIG_FILE_SIZE-1 - ix)*BIG_FILE_SIZE) + (BIG_FILE_SIZE-1 - iz);
				break;
		}
		return (offset*4096);
	}

	typedef struct RGBVal
	{
		UByte red,green,blue;
	}
	RGBVal,*RGBValP;

	UByte Land_Stream::GetClosestMatch(Float&,Float&,Float&,RGBValP);
};






extern	Land_Stream LandStream;

#endif	//COMMENT

#endif
