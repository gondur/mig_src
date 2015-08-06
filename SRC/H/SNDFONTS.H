//------------------------------------------------------------------------------
//Filename       sndfonts.h
//System         
//Author         Robert Slater
//Date           Fri 3 Jul 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	SNDFONTS_Included
#define	SNDFONTS_Included

#define	DEFAULT_SNDFONTS 0

#include	"sfman.h"

#define NO_DEVID 0xFFFFFFFF
#define NO_INDEX 0xFFFF

#define MAXFILENAME         128
#define MAXNUMDEVICES		16
#define SIZEOFBIGSF			2574190			// Set this variable to the size of the big bank

// Assign values to the 4 variables below to create a priority system for multiple SF devices
// For devices with hardware memory, the rating is given as :
// Rating = HWSynthHWMem + Number of blocks of HWMemBlock size
// This means that the HWSynth device with the most hardware memory gets the highest rating

// Note that a HWSynthHWMem device with less than HwMemBlock Memory (unexpanded SB32)
// gets a rating of 0.

// Therefore these default values give the best device as one with a HWSynth that uses System
// RAM followed by HW Synth devices with hardware RAM (in order of most RAM to least RAM), 
// followed by a device with a SW synth. (This code assumes that devices with SW Synth's and 
// hardware RAM don't exist !)

#define HWSynthSysMem		128				// These values must be less than 255 !
#define HWSynthHWMem		64				
#define SWSynthSysMem		32			 
#define HWMemBlock			524288			// 512K						 
									

// Portable Macros for splitting WM_COMMAND

//Killed these... do we use them?????
//#ifdef WIN32 // 32-bit version
//    #define GET_WM_COMMAND_CMD(wp, lp) HIWORD(wp)
//    #define GET_WM_COMMAND_ID(wp, lp) LOWORD(wp)
//    #define GET_WM_COMMAND_HWND(wp, lp) (HWND) (lp)
//#else        // 16-bit version
//    #define GET_WM_COMMAND_CMD(wp, lp) HIWORD(lp)
//    #define GET_WM_COMMAND_ID(wp, lp) (wp)
//    #define GET_WM_COMMAND_HWND(wp, lp) ((HWND) LOWORD(lp))
//#endif

enum SFROUTERCMD
{
    SFROUTER_ROUTE_ALL_CHANS_TO_DEV,
    SFROUTER_ROUTE_CHAN_TO_DEV=2,
    SFROUTER_ROUTE_BANKPRG_TO_DEV_BANKPRG=4,
    SFROUTER_RESET_ALL_ROUTINGS = 127
};

typedef struct
{
    enum SFROUTERCMD  m_RouterCommand;
    DWORD             m_Channel;
    CSFMIDILocation   m_SourceLocation;
    CSFMIDILocation   m_TargetLocation;
} CSFRouterData, *PSFROUTERDATA;

class SndFonts
{
	Bool 	bIsMIDIPlaying;
	Bool 	bIsUserBankLoaded;
	Bool 	bCalledAlready;
	char	sfCurrDevName[10];
	UWord	numSFDevs;
	UWord	wMCIDeviceID;
	ULong	dwAvailableMemBest;
	SFDEVINDEX 	BestsfIdx; 
	HANDLE 		hMainProcInst;
	HANDLE		hSFMANDLL; 
	PSFMANAGER  lpSFManager;
 	PSFMANL101API lpSFL1API;
	HMIDIOUT	hMIDIOutInteractive;
	Bool		SFontSet;
	Bool		bMMSystemOnly; 
	BOOL		bRouteDialog;
	CSFRouterData last;
	ULong		lastDev;
	UByte		theBank, thePreset;


public:
	CON		SndFonts();
	DES		~SndFonts();

	Bool	LoadSoundFont(LPHMIDIOUT,FileNum,UByte bankno=1,UByte patchno=0);
	void	KillSFont();


private:
	Bool	InitSFont(LPHMIDIOUT);
	Bool	InitSFDLL(Bool);
	void	ClearSFRoute();
	Bool	SF_SendRouterCommand(ULong,CSFRouterData*);
	Bool	ClearBank();

};

extern SndFonts _SndFonts;


#endif
