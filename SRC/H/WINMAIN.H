//------------------------------------------------------------------------------
//Filename       WinMain.h
//System         
//Author         Andrew McRae
//Date           Wed 2 Jul 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	main_Included
#define	main_Included

#include	"getset.h"
#include	"screenxy.h"

#define APP_NAME    "MiG Alley"
#define APP_TITLE   "MIG ALLEY"

#define	ID_TIMER	1

#define	NOGUID	(LPGUID)-1

typedef ULong myDPID;
typedef ULong* myLPDPID;

class	Main : public	GetSet
{
	public:

		void	Main::MainInit(void);
		void	Main::QuitGame(void );
		void	Main::RowanMessage();
		void	Main::DoScreen(Window *);						//JIM 12Dec95

 		Bool	Main::InitFileSystem(InitDisplayDef&);

		// Windows Params
		HWND hWnd;

		// Message Loop Control + task switching bits'n'bobs
		ScreenRez	prevMode;
		UINT 		AppActive;
		Bool 		Minimized;
		Bool 		GameEnd;
		Bool 		DDrawInitialised;

		// Timer Stuff
		TIMECAPS    tc;
		UINT        wTimerRes;
		UINT		uTimerID;

		// Misc
		char MyString [256];

		// Palette management stuff

	private:

	protected:

};

	extern Main _Main;		//For 'EmitSysErr'			//JIM 21Sep95

#endif


long FAR PASCAL DLLExport WndProc (HWND, UINT, UINT, LONG);

VOID MainLoopThread (PVOID pvoid);
VOID TimerThread (PVOID pvoid);
void CALLBACK TimeProc (UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

Bool GetCDFile (FileNum, char* Name, ULong Offset);
void ThreadFunction (void * ptr);

//TempCode ARM 09Aug96 // Temporary Debug params
//TempCode ARM 09Aug96 SLong Count;
//TempCode ARM 09Aug96 SLong MainLoopCount;
//TempCode ARM 09Aug96 // Temporary String for Message Boxes

// Direct Play Callback Functions
//TempCode ARM 13Aug96 BOOL FAR PASCAL EnumSP(LPGUID lpSPGuid, LPSTR lpDesc, DWORD dwMajorVersion, DWORD dwMinorVersion, LPVOID lpv);
//TempCode ARM 13Aug96 BOOL FAR PASCAL EnumSession(LPDPSESSIONDESC lpDPGameDesc, LPVOID lpContext, LPDWORD lpdwTimeOut, DWORD dwFlags);
//TempCode ARM 13Aug96 BOOL FAR PASCAL EnumPlayer(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName, DWORD dwFlags, LPVOID lpContext);

//TempCode ARM 15Aug96 BOOL FAR PASCAL EnumAllPlayers(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName, DWORD dwFlags, LPVOID lpContext)
