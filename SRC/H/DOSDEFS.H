//------------------------------------------------------------------------------
//Filename       dosdefs.h
//System         
//Author         Paul.   
//Date           Tue 4 Jul 1995
//Description    PLEASE DON'T PUT INCLUDES IN HERE. 
//				THIS SHOULD BE THE BAREST MINIMAL FILE!
//				
//------------------------------------------------------------------------------
//I am told that this works... we shall see!
#define _XSTR(x)         #x
#define TOSTR(x)        _XSTR(x)
//__HERE__ is a string describing the current source file and line!
#define __HERE__	__FILE__ "(" TOSTR(__LINE__) "): "
#define	warnmsg(text)	message(__HERE__ text)
#define TODO(msg) message(__FILE__ "(" TOSTR(__LINE__) ") TO DO: " msg)
//

#define LOCAL_new(DEBUG_NEW_PARAMS)	new
#define	DEBUG_NEW_PARAMS (__FILE__, __LINE__)

#ifndef new
extern void*  operator new(unsigned int nSize);

extern void* __cdecl operator new(unsigned int nSize,const char* FileName, int nLine);
#endif

#ifndef DEBUG_NEW
        #if !defined(NDEBUG) && !defined(__BCPLUSPLUS__)
			#define	DEBUG_NEW_MODE
            #define DEBUG_NEW new DEBUG_NEW_PARAMS
        #else
			#undef	DEBUG_NEW_MODE
            #define DEBUG_NEW new
        #endif
#endif

#define	new DEBUG_NEW
//
//
//these 2 are done always to override any sys lib garbage
#ifdef	__WATCOMC__
#undef new
	#pragma warning	690	2
#endif

#ifndef __BORLANDC__
#pragma pack (1)
#endif

#ifndef	dosdefs_Included
#define	dosdefs_Included

#ifdef	__SW_OM
#ifdef	__SW_OA
	#ifdef	__SW_OR
	#ifdef	__SW_OL
		#ifndef	__SW_OD
				#define	NDEBUG
		#endif
	#endif
	#endif
#endif
#endif

#ifdef __QNX
	#undef	__QNX
#endif

#ifdef	__NT__
	#define WIN95
#endif
//
// Fixes for 'useless' warnings:
#ifdef	_MSC_VER
#ifndef	__MSVC__
#define	__MSVC__
#endif
#ifndef	WIN95
#define	WIN95
#endif
#endif
#ifdef	__WATCOMC__
#pragma warning	389	9				// value may be truncated
#pragma warning	14	8				// defined but not referenced
#pragma warning	139	4				// enumeration not assigned from its enumeration
#pragma warning	7	7				// &array not intended result
#pragma warning	690	2				// Fix against "condition is always true"
#endif
#ifdef __MSVC__

//HAPPY TO LOSE THESE
//4097 class synonym;
//4510 union constructor;
//4610 nonstandard conversion;
//4725 inaccurate pentium;
//4201 nameless struct
#pragma warning( disable : 4097 4510 4610 4725 4201 )
//4244 math truncation
//4103 alignment changed!
//4305 math truncation
//4003 not enough parameters for macro
//4309 conversion - truncation
//4514 unreferenced function removed
//4512 class default assinment operator not possible
//4201 nameless struct
//4230 obsolete procedure qualifiers
//4710 inline ignored
 
#pragma warning( disable : 4244 4103 4305 4003 4309 4514 4512 4201 4230 4710)
//not happy losing these, but given time, we can fix them
//4100 unreferenced parameter
//4018 signed unsigned comparison
//4101 unreferenced local
//4127 constant conditional
//4245 signed/unsigned mismatch
//4310 cast truncates constant
//4701 poss unassigned
#pragma warning( disable : 4100 4239 4018 4127 4101 4245 4310 4701)

#endif
//-this can be included wherever you want it, but not as a blanket thing.
//#pragma warning	690	6

//
// Do we want a bit of publicity? Of course we do!
//
//#define	PUBLICVERSION	1	//Same as usual
#ifdef		PUBLICVERSION
	#define	DEBUGGING	0
#else
	
	#define	DEBUGGING	1
//TempCode PD 25Jan96 	#define	SHAPE_VIEWER	TRUE								//PD 08Jan96

#endif

#define	NULL	0
#define	_	[0]

#define ZEROLOCK 0,0
#define LOWLOCK	1,3
#define MIDLOCK 4,6
#define HIGHLOCK 7,9

#ifdef	TRUE
#undef	TRUE
#undef	FALSE
#endif

#define	TRUE	BOOL_TRUE
#define	TRUEST	BOOL_TRUE
#define	FALSE	BOOL_FALSE
typedef	enum	Bool	{BOOL_TRUE=1,BOOL_FALSE=0,BOOL_Align=255} Bool;

//DeadCode DAW 30Jun96 enum	Bool	{TRUE=1,FALSE=0,BOOL_Align=255};

typedef	signed	char	SByte,*SByteP;
typedef	unsigned char	UByte,*UByteP;

typedef	signed	short	SWord,*SWordP;
typedef	unsigned short	UWord,*UWordP;

typedef	signed	long	SLong,*SLongP;
typedef	unsigned long	ULong,*ULongP;
typedef double 	Float,*FloatP;							//PD 06Jan97

typedef	char	*string,*String,	//pointer to a character array
				**strind;			//pointer to pointer

typedef union	ifshare
{
	SLong	i;
	Float	f;
}
IFShare,*IFShareP;

//struct	rminfo
//{
//	long EDI;
//	long ESI;
//	long EBP;
//	long reserved_by_systemESP;
//	long EBX;
//	long EDX;
//	long ECX;
//	long EAX;
//	short flags;
//	enum	flagbits	{	CF=1,PF=4,AF=16,ZF=64,SF=128,
//							TF=256,IF=512,DF=1024,OF=2048
//						};
//	short ES,DS,FS,GS,IP,CS,SP,SS;
//};


//
//virtual width's height's
//
#define	FULLW	25600
#define	FULLH	19200
#define	FULLW_2	(FULLW/2)
#define	FULLH_2	(FULLH/2)
#define	TAB		(FULLW/32)
#define	VTAB	(FULLH/8)
#define	PIXEL640 	40											//RDH 18Jan96


#ifdef	__WATCOMC__
	#pragma	aux	INT3	= 0xCC		// breakpoint 
#else
	#ifdef	__MSVC__
//	#include <stdio.h>
//	#include <stdlib.h>
//	extern FILE*	debugfile;

#ifndef 	NDEBUG
	#define	INT3 _asm {int 3}
#else
	#define	INT3	_asm	{}
#endif

//	#define	INT3 {fprintf(debugfile,"%s INT3()\n",__FILE__);fflush(debugfile);}
//	#define	INT3 {;}
	#ifdef	LOG__CON
		static struct SSS{SSS(char*);} s_s_s(__HERE__ __DATE__ " " __TIME__);
	#endif
	#endif
#endif

#define	MINMAX(typename,minval,maxval)				\
	enum	typename	{typename##MIN=minval,typename##MAX=maxval}

//Constructor/destructor standouts
#define	CON	/*CON*/
#define	DES	/*DES*/

//standard "C" syntax extensions and standouts
#define	breakif(cond)	{if	(cond)	break;}
#define	elser			/*else for returned if*/
#define	elseif			else if
#define	forever			for(;;)
#define	RETURN(p)		return(p)
#define repeat			do
#define	until(x)		while(!(x))
#define	proc			void 
#define	NULLREF(t)		*(t*)NULL

typedef	struct	COORDS3D
{	SLong	X,Y,Z;
	COORDS3D&	operator = (COORDS3D& src)	{X=src.X;Y=src.Y;Z=src.Z;return(*this);}
} Coords3D;


typedef	struct	fpCOORDS3D										//PD 02Apr97
{																//PD 02Apr97
	IFShare	X,Y,Z;												//PD 02Apr97
}																//PD 02Apr97
fpCOORDS3D;														//PD 02Apr97

	struct _DDSURFACEDESC;

//	struct _DDCAPS;												//JIM 25Jul96
struct _MDI_DRIVER;
typedef _MDI_DRIVER          // Handle to digital audio driver
MDI_DRIVER;
struct _DIG_DRIVER;
typedef _DIG_DRIVER          // Handle to digital audio driver
DIG_DRIVER;
struct _SEQUENCE;

#ifdef __WATCOMC__
//This protects BX from library screwups						//JIM 25Jul96
     #pragma aux __cdecl "_*"		\
                parm caller []		\
				value struct float struct routine [eax] \
                modify [eax ebx ecx edx]
#endif

#ifdef	__MSVC__
struct	_iobuf;
typedef	_iobuf	FILE;
#else
struct	__iobuf;
typedef	__iobuf	FILE;
#endif


struct _GUID;
typedef struct _GUID GUID;
typedef GUID *LPGUID;

//DeadCode DAW 17Nov97 struct _DPSESSIONDESC;
//DeadCode DAW 17Nov97 typedef struct _DPSESSIONDESC DPSESSIONDESC;
//DeadCode DAW 17Nov97 typedef DPSESSIONDESC* LPDPSESSIONDESC;
//DeadCode DAW 17Nov97 struct IDirectDraw2;
//DeadCode DAW 17Nov97 typedef struct IDirectDraw2			*LPDIRECTDRAW2;				//ARM 25Nov96
//DeadCode DAW 17Nov97 
//DeadCode DAW 17Nov97 struct IDirectDraw        ;
//DeadCode DAW 17Nov97 struct IDirectDraw2        ;
//DeadCode DAW 17Nov97 struct IDirectDrawSurface 	;
//DeadCode DAW 17Nov97 struct IDirectDrawSurface2	 ;
//DeadCode DAW 17Nov97 							  ;
//DeadCode DAW 17Nov97 struct IDirectDrawPalette 	   ;
//DeadCode DAW 17Nov97 struct IDirectDrawClipper 		;
//DeadCode DAW 17Nov97 								 ;
//DeadCode DAW 17Nov97 struct _DDFXROP           		  ;
//DeadCode DAW 17Nov97 struct _DDSURFACEDESC     		   ;
//DeadCode DAW 17Nov97 struct IDirect3D					;
//DeadCode DAW 17Nov97 
//DeadCode DAW 17Nov97 
//DeadCode DAW 17Nov97 typedef struct IDirectDraw             *LPDIRECTDRAW;
//DeadCode DAW 17Nov97 typedef struct IDirectDraw2            *LPDIRECTDRAW2;
//DeadCode DAW 17Nov97 typedef struct IDirectDrawSurface      *LPDIRECTDRAWSURFACE;
//DeadCode DAW 17Nov97 typedef struct IDirectDrawSurface2     *LPDIRECTDRAWSURFACE2;
//DeadCode DAW 17Nov97 
//DeadCode DAW 17Nov97 typedef struct IDirectDrawPalette      *LPDIRECTDRAWPALETTE;
//DeadCode DAW 17Nov97 typedef struct IDirectDrawClipper      *LPDIRECTDRAWCLIPPER;
//DeadCode DAW 17Nov97 
//DeadCode DAW 17Nov97 typedef struct _DDFXROP                *LPDDFXROP;
//DeadCode DAW 17Nov97 typedef struct _DDSURFACEDESC          *LPDDSURFACEDESC;
//DeadCode DAW 17Nov97 typedef struct IDirect3D			*LPDIRECT3D;				//PD 03Feb97

#ifdef	__SW_EP
	extern "C" void ASM_TogglePrologCode(ULong,void*);
#endif

#ifdef __WATCOMC__
#define	DLLExport	_export
#define	__FAR		__far
#define	__NEAR		__near
#else
#ifdef __MSVC__
#define DLLExport	__declspec( dllexport )
#define __FAR
#define	__NEAR
#define db(p1)	__asm _emit p1
#define dw(p1)	__asm _emit p1/0x100 __asm _emit p1&0xFF
#endif
#endif

#endif

