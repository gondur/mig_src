//------------------------------------------------------------------------------
//Author	Andrew McRae
//Date		Mon 29 Jul 1996
//Modified	
//
//Description	Windows Install header file
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#ifndef WINSTALL_Included
#define WINSTALL_Included

#include	"winstall.smb"		// Dialogue symbols

#define	INSTALL_MAXCHARS 256

#define	DEFAULT_DIR "c:\\rowan\\mig"	// Destination
#define	INSTALL_TEST_FILE	"wmig.exe"

// Install Dialog
#define	GO_INSTALL	0x0001
#define	ABORT_INSTALL	0x0002
#define	INSTALL_SIZE_LARGE	0x0003	// specific values
#define	INSTALL_SIZE_MEDIUM	0x0002
#define	INSTALL_SIZE_SMALL	0x0001

// FlyingCorps Dialog
#define	FLY_PLAY	0x0001
#define	FLY_CANCEL	0x0002
#define	FLY_UNINSTALL	0x0003

// Uninstall Dialog
#define	GO_UNINSTALL	0x0001
#define	ABORT_UNINSTALL	0x0002
#define	UNINSTALL_MAINGAME	0x0001
#define	UNINSTALL_SAVEGAMES	0x0002
#define	UNINSTALL_STILLS	0x0004

// Registry
#define	ROOT HKEY_LOCAL_MACHINE
#define	LEVEL1 "SOFTWARE"
#define	LEVEL2 "Rowan"
#define	LEVEL3 "FlyingCorps"
#define REG_VERSION 1L

// Install Error Codes
#define	NOINSTERROR		0x0001
#define	NODESTPATH		0x0002
#define	NOSIZE			0x0004
#define	NOTREGISTERED	0x0008
#define	NODIRECTX		0x0010
#define NOFILES			0x0020
#define CREATEDIR_FAILED	0x0040
#define COPYFILE_FAILED		0x0080
#define CANCELLED		0x0100

#define MENUITEM_DIR "\\Start Menu\\Programs\\"
#define MENUITEM_NAME "Mig Alley.lnk"
#define MENUITEM_TEXT "Mig Alley"
#define MENUITEM_PRG "\\winmig.exe"
#define MENUITEM_ICONNAME "\\wmig.ico"

// File Types
#define	FILETYPE 1
#define DIRTYPE 2	
#define MAX_FILENAME_SIZE 246

// Progress Flag States
//#define	NOTDONE		0x0011
//#define	MESSAGESENT	0x0012
//#define	DONE		0x0101
//#define HASFAILED	0x0102
//#define ACTION		0x0010

// CopyFile & CreateDir Error Codes
#define DIR_ERROR 2
#define FILE_ERROR 3

// DoInstall Return Codes
#define FATAL_ERROR 1
#define WARNING_ERROR 2
#define RESTART_ERROR 3
#define IGNORE_ERROR 4

// Full Disk Test Limit in bytes
#define FULLBYTES 512

// Uninstall Error Codes
#define UNINST_INVALIDPATH 12
#define UNINST_INVALIDFILE 13
#define UNINST_FAILED 14
#define UNINST_NOERROR 0

// Minimum Installation Path Size - chars
#define MININSTPATHSIZE 4

typedef struct _file_data FILEITEM;
typedef struct _file_data* PFILEITEM;
struct _file_data {

	DWORD Type;
	DWORD Size;
	char Name[MAX_FILENAME_SIZE];
	BOOL Created;

};

class Main {

	public:

	Bool Main::InitFileSystem(InitDisplayDef&);

};


// for Lock CD
#define VWIN32_DIOC_DOS_IOCTL 1 

typedef struct _DEVIOCTL_REGISTERS {

	DWORD reg_EBX;
	DWORD reg_EDX;
	DWORD reg_ECX;
	DWORD reg_EAX;
	DWORD reg_EDI;
	DWORD reg_ESI;
	DWORD reg_Flags;

} DEVIOCTL_REGISTERS, *PDEVIOCTL_REGISTERS;
 
typedef struct _MID {

	WORD  midInfoLevel;
	DWORD midSerialNum;
	BYTE  midVolLabel[11];
	BYTE  midFileSysType[8];

} MID, *PMID;

// Andrew's Parameter Block
typedef struct _DEVPAR {

	BYTE	pbFun;
	BYTE	pbDevType;
	WORD	pbAttb;
	WORD	pbCyl;
	BYTE	pbType;
	BYTE	pbBPB [31];
	WORD	pbSects;
	WORD	pbSectSize [63];

} DEVPAR, *PDEVPAR;


class Winstall
{

public:

	Winstall ()
	{


		Sx = 0;
		OldSx = 0;

		hWnd = 0;
		hProgDlg = 0;

		Stage = 0;

		InstallError = 0;

		ValidInstDir = 0;

		DirectX = 0;

		InstallSelection = 0;
		memset (SrceRoot, 0, INSTALL_MAXCHARS);
		memset (InstDir, 0, INSTALL_MAXCHARS);
		memset (wSourceDir, 0, INSTALL_MAXCHARS);

		InstallSize = 0;
		MenuItem = 0;

		FlySelection = 0;

		UninstallSelection = 0;
		UninstallOptions = 0;

		cListSize = 0;
		cIndex = 0;
		pFileList = 0;
		pIndex = 0;

		Files = 0;
		FilesDone = 0;

		CDDrive [0] = 0;
		CDDrive [1] = 0;

		ProgressCancel = FALSE;

		memset (SrcPath, 0, 128);
		Size = 0;

		Reboot = FALSE;

		UndoInstall = FALSE;
		FullDisk = FALSE;

		NT4 = TRUE;

	}

	~Winstall ()
	{

		char WinDir [INSTALL_MAXCHARS];

		GetWindowsDirectory (WinDir, INSTALL_MAXCHARS);
		strcat (WinDir, "\\WINSTALL.INI");

		DeleteFile (WinDir);

	}


	// Params

	DWORD TotalFileSize;
	DWORD TotalFileTime;

	DWORD Sx,OldSx;	// fuel bar

	BOOL NT4;

	BOOL Reboot;
	BOOL UndoInstall;
	BOOL FullDisk;

	HWND hWnd;
	HWND hProgDlg;

	DWORD	Stage;

	DWORD	InstallError;

	DWORD 	ValidInstDir;

	DWORD 	DirectX;

	DWORD	InstallSelection;
	char	SrceRoot[INSTALL_MAXCHARS];
	char	InstDir [INSTALL_MAXCHARS];
	char	wSourceDir [INSTALL_MAXCHARS];
	DWORD	InstallSize;
	DWORD	MenuItem;

	DWORD	FlySelection;

	DWORD	UninstallSelection;
	DWORD	UninstallOptions;

	DWORD	cListSize;
	DWORD	cIndex;
	PFILEITEM	pFileList;
	PFILEITEM	pIndex;

	DWORD	Files;
	DWORD	FilesDone;

	char CDDrive [2];

	// Progress Flags
	BOOL ProgressCancel;

	// Dave's WriteRoots
	char SrcPath [128];	// for write roots.dir
	ULong Size;

	// Functions

	BOOL DoInstall ();
	void LaunchGame ();
	int	WriteRoots();

	BOOL CreateRootDir (char*);

	void TopMessage (char* Text);
	void BottomMessage (char* Text);
	void UpdateProgressBar ();

	BOOL InitFileList (DWORD);
	DWORD DoInstallError (UINT Err);

	DWORD DoUninstall (char * DirName, DWORD Options);

	DWORD InstRemDir (char * DirName);

	DWORD CreateOneListDir (char*, char*);
	DWORD CreateDir (char*, char*);
	DWORD CopyOneListFile (char*, char*);

	DWORD CountFiles (char *);
  	void MakeFileList (char *);
	void AddFileToList (DWORD, DWORD, char*);

	DWORD FMCountFiles ();
  	void FMMakeFileList ();

	BOOL Registered (char * Data, DWORD);
	BOOL Register (char * DirName);
	void UnRegister ();

	int InstallDirectX (HWND hWnd);

	BOOL Installed (char * Dir);

	DWORD GetDiskSpace (char*, DWORD& Bytes);
	void CreateMenuItem ();
	void SetInstDir (char* NewPath);

	BOOL RegInstaller ();
	void UnRegInstaller ();

};

void CALLBACK TimeProc (UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);


BOOL CALLBACK InstallProc (HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK UninstallProc (HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK FlyingCorpsProc (HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ProgressProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

BOOL DetectValidOS ();
BOOL GetCDDrive (char* Let);
DWORD GetCDDrives (char* Let);
void DrawBitmap (HDC hdc, HBITMAP pic, POINT scrn);

BOOL ChopPathName (char * DirName);
BOOL LockCD (DWORD);
void WriteWininiFile ();
DWORD GetSizeOfFile (char* Name);

extern Winstall _Winstall;

#endif
















