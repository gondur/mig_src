//------------------------------------------------------------------------------
//Filename       error.h
//System         
//Author         Martin Alderton
//Date           Fri 6 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	error_Included
#define	error_Included

//#ifndef CEDITOR												//ARM 11Apr97
//	#include	"display.h"										//DAW 15Apr96
//#endif															//ARM 11Apr97
class	 Error  
{	//can't allow this to be half commented out!
		FILE	*logfile;										//JIM 01Aug96

	public:
		char* exitmsg;
		Error(void );
		~Error(void );

//DeadCode JIM 02Jul96 		void Error::EmitSysErr(char *, ...);
		Error& Error::ExitMode();
		Error& Error::Say(char *, ...);
		Error& Error::SayAndQuit(const char *, ...);
		void Error::Quit();
//#ifdef __MSVC__
//#define Quit 
//#define SayAndQuit 
//#endif
#ifdef __WATCOMC__
#pragma	aux Quit			aborts;
#pragma	aux SayAndQuit		aborts;
#endif
		#if	DEBUGGING
//DeadCode ARM 05Aug96 			void screenswap(Display *);
			void OpenLog(void );
			void WriteToLog(char *,...);
			void CloseLog(void );
			void KeyTrap(void );								//pd 01Nov95
			static	void	dummyproc(char*)	{;}
			static	void	dummyproc(char*,int)	{;}
			static	void	dummyproc(char*,int,int)	{;}
			static	void	dummyproc(char*,int,int,const char*)	{;}
			static	void	dummyproc(char*,int,int,int)	{;}
			static	void	dummyproc(char*,int,int,int,int)	{;}
			static	void	dummyproc(char*,int,int,int,const char*,int)	{;}
			static	void	dummyproc(char*,char*)	{;}
			static	void	dummyproc(char*,char*,char*)	{;}
			static	void	dummyproc(char*,char*,int,int)	{;}
			static	void	dummyproc(char*,char*,int)	{;}
			static	void	dummyproc(char*,int,char*)	{;}
		#endif
			static	void	ReportLastRunError();
			static void	PleaseReport(bool x)		{pleasereport=x;}
			static void	PleaseLog(bool x)			{pleaselog=x;}
			static void TerminateCondition(char* x=NULL)	
			{	if (x)
				{
					stackedterminatecondition=terminatecondition;
					terminatecondition=x;
				}
				else
				{
					terminatecondition=stackedterminatecondition;
					stackedterminatecondition=NULL;
				}
			}
	private:
		static char*	terminatecondition;
		static char*	stackedterminatecondition;
		static bool	pleasereport;
		static bool	pleaselog;
		static void terminate(); 
	protected:

};
extern	Error	_Error;


//#ifdef	__WATCOMC__
#ifdef NDEBUG
 #define EmitSysErr ExitMode().SayAndQuit(__FILE__ "%i ",__LINE__),Error::dummyproc
#else
 #define EmitSysErr ExitMode().Say(__FILE__ ": ").SayAndQuit
#endif
 #define ReallyEmitSysErr ExitMode().Say(__FILE__ ": ").SayAndQuit

#ifdef	assert
#pragma warnmsg("assert redefined")
#undef assert
#undef nassert
#endif

//DEADCODE DAW 26/04/99 #ifndef	assert

	#ifdef NDEBUG
//	 	#define assert(__ignore) ((void)0)
		#define assert(expr) 	  {}
		#define nassert(__ignore) {}	
	#else
//	 	#define assert(expr) ((expr)?(void)0:(void)_Error.EmitSysErr(#expr))
		#define assert(expr) {if (expr) {} else {(void)_Error.EmitSysErr(#expr);}}
 		#define nassert(expr) ((expr)?(void)_Error.EmitSysErr(#expr):(void)0)
	#endif
//DEADCODE DAW 26/04/99 #endif
//#else
//#ifdef __MSVC__
//	#define EmitSysErr 
//	#define ReallyEmitSysErr
//	#ifndef	assert
//	 	#define assert(__ignore) ((void)0)
// /		#define nassert(__ignore) ((void)0)
//	#endif
//#endif
//#endif

#endif
