//------------------------------------------------------------------------------
//Filename       main.h
//System         
//Author         Paul.   
//Date           Wed 5 Jul 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	main_Included
#define	main_Included

#include	"getset.h"
//DeadCode DAW 19Mar96 #include	"world.h"


class	Main : public	GetSet
{
	public:
//TempCode MGA 06Oct95 		void	Main::EmitSysErr(char *, ...);
		void	Main::MainInit(void);
		void	Main::QuitGame(void );
		void	Main::RowanMessage();
//DeadCode JIM 22Nov95 		UWord	Main::Loop3D(ScreenRecord *, WorldStuff *);
//DeadCode JIM 14May96 		void	Main::Do3DScreen(Window *, WorldStuff *);		//JIM 12Dec95
		void	Main::DoScreen(Window *);						//JIM 12Dec95

 		Bool	Main::InitFileSystem(InitDisplayDef&);

	private:

	protected:

};

	extern Main _Main;		//For 'EmitSysErr'			//JIM 21Sep95

#endif
