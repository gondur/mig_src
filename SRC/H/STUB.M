//;;------------------------------------------------------------------------------
//;;Filename       stub.m
//;;System         
//;;Author         Jim Taylor
//;;Date           Mon 9 Oct 1995
//;;Description    Stub model for runtime libraries
//;;
//;;Each procedure to be stubbed has 2 versions in the class.
//;;The public version simply stubs to the private version.
//;;It also has a STUBLOADABLE() statement to define some extra hooks.
//;;
//;;The header for the library and the main program contains:
//;;	STUBSTART(classname)
//;;	followed by the public stubs
//;;	STUBREAL(classname)
//;;
//;;The main program now defines empty versions of the procedures
//;;followed by STUB256() statements.
//;;The main program area is terminated by a STUBEND() statement
//;;
//;;The library defines the procedure bodies. This is also terminated by STUBEND()
//;;
//;;Thus, the library fixup is made up of 3 linked modules: pub, gap and lib
//;;
//;;The stub loader code requires the address of classname::stubstart()
//;;defined by STUBSTART(). It will then overwrite between STUBSTART and STUBEND.
//;;Note: This interface will need a going over if we ever allow virtual memory,
//;;but the use of a stub should simplify this work.
//;;
//;;To load the library call	STUBLOAD(classname)
//;;
//;;------------------------------------------------------------------------------
#ifndef	STUB_Included
#define	STUB_Included
#include	"files.g"
//#ifdef LoadLibrary
//#undef LoadLibrary
//#endif

#define	STUBLOADABLE(staticauto) static	void	stubstart();			\
				static	char*	stubstart2();			\
				static	void	stubend();				\
				static	void	stubreal();				\
				staticauto	StubLock	stublock;			

#ifdef __WATCOMC__ 
#pragma aux	STUBINTRO	=	"db	'ROWANLIB'"
#pragma	aux	STUBHEADCODE=	"db	'HEADCODE'"
#pragma	aux	STUBREALCODE=	"db	'REALCODE'"
#pragma aux	STUBEXIT	=	"db	'EXITOVER'"
#pragma aux STUBBYTE	=	0
#endif
#ifdef __MSVC__
inline void STUBINTRO()
{
	__asm _emit 'R' __asm _emit 'O' __asm _emit 'W' __asm _emit 'A' 
	__asm _emit 'N' __asm _emit 'L' __asm _emit 'I' __asm _emit 'B' 
}
inline void STUBHEADCODE()
{
	__asm _emit 'H' __asm _emit 'E' __asm _emit 'A' __asm _emit 'D' 
	__asm _emit 'C' __asm _emit 'O' __asm _emit 'D' __asm _emit 'E' 
}
inline void STUBREALCODE()
{
	__asm _emit 'R' __asm _emit 'E' __asm _emit 'A' __asm _emit 'L' 
	__asm _emit 'C' __asm _emit 'O' __asm _emit 'D' __asm _emit 'E' 
}
inline void STUBEXIT()
{
	__asm _emit 'E' __asm _emit 'X' __asm _emit 'I' __asm _emit 'T' 
	__asm _emit 'O' __asm _emit 'V' __asm _emit 'E' __asm _emit 'R' 
}
inline void STUBBYTE()
{
	__asm _emit 0
}
#endif

#ifdef	__DOS__
#define STUBWORD()		{STUBBYTE();STUBBYTE();}
#define STUBLONG()		{STUBWORD();STUBWORD();}
#define STUBDBLE()		{STUBLONG();STUBLONG();}
#define STUBPARA()		{STUBDBLE();STUBDBLE();}
#define STUB32()		{STUBPARA();STUBPARA();}
#define STUB64()		{STUB32();STUB32();}
#define STUB128()		{STUB64();STUB64();}
#define STUB256()		{STUB128();STUB128();}
#endif

#ifdef	WIN95
#define STUBWORD()		
#define STUBLONG()		
#define STUBDBLE()		
#define STUBPARA()		
#define STUB32()		
#define STUB64()		
#define STUB128()		
#define STUB256()		
#endif

//#undef LoadLibrary
class	StubLock
{
public:
	ULong	lockstart;
	ULong	locksize;
	~StubLock();
void	ClearLock();
string	LoadJimLib(		void*		targetaddr,		//Address of StubStart
						string		keyname,		//Text from stubstart2()
						FileNum		sourcefile,		//Caller decision
						void*		srcaddr=NULL,
						int**		jumpobject=NULL		
					);
//DeadCode JIM 02May97 string	CopyLibHeader(int newaddr,int oldaddr);
};

#define	STUBSTATIC(classname)							\
StubLock	classname::stublock={0,0};

#define	STUBSTART(classname)							\
														\
char*	STUBNAME="ROWANLIB"	__FILE__ __DATE__;	\
														\
				char*	classname::stubstart2()	\
				{										\
					return STUBNAME;					\
				}										\
														\
				void	classname::stubstart()	\
				{										\
					STUBINTRO();						\
					STUBHEADCODE();						\
					STUBBYTE();							\
				}


#define	STUBREAL(classname)								\
				void	classname::stubreal()	\
				{										\
					STUBINTRO();						\
					STUBREALCODE();						\
					STUBBYTE();							\
				}

#define	STUBEND(classname)								\
				void	classname::stubend()	\
				{										\
					STUBINTRO();						\
					STUBEXIT();							\
					STUBBYTE();							\
				}										\
				void	main	(){}					\
				void	StubLock::ClearLock()	{}		\
				DES		StubLock::~StubLock()	{}				
														
#define	STUBENDSPACE(classname)							\
				void	classname::stubend()	\
				{										\
					STUBINTRO();						\
					STUBEXIT();							\
					STUBBYTE();							\
				}
														


#define	STUBLOAD(classname,filenum)											\
		classname##stublock.LoadLibrary((void*)classname##stubstart,						\
				classname##stubstart2(),									\
				filenum);													\
				
//
// END OF FILE!
//

#endif

