/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       winmain.cpp
//System         
//Author         Andrew McRae
//Date           Tue 4 Jun 1996
//Description    
//------------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN

#include	"DOSDefs.H"
#include	<stdio.h>
#include	<stdlib.h>

#pragma init_seg( lib); 
struct iniclass
{
	iniclass()
	{
	debugfile = NULL;

	debugfile=fopen("\\MIG\\GAME\\deb.out","wt");
	fprintf(debugfile,"hello\n");
	INT3;
	}
} Ini_C;
//#pragma init_seg( user ); 
#include	<process.h>
#include 	<windows.h>
#include 	<windowsx.h>
#include 	<mmsystem.h>

#include	<ddraw.h>											//DAW 09Jul96
#include	<dplay.h>

	#define F_GRAFIX
	#define F_SOUNDS
	#define F_BATTLE
#include	"Files.G"
#include	"FileMan.h"
#include	"getset.h"
#include	"WinMain.H"
#define	SHEETLST_Included
#include	"UI.h"
#include	"Analogue.h"
#include	<Signal.h>										//PD 06Nov95
#include 	"Mytime.h"
#include	"keymaps.h"
#include	"wail.h"
#include	"miles.h"
#include	"display.h"
#include	"monotxt.h"

#include	"savegame.h"

#include	"worldinc.h"
#include	"uniqueID.h"
#include	"winmove.h"
#include	"comms.h"
//DeadCode PD 08Aug97 #include	"wpgapi.h"
#include	"h2h.h"
#include	"3dcode.h"

void	TextTest();

Main	_Main;
DPlay	_DPlay;

Display		*Whole_Screen=NULL;

char dpString [256];

#define	BEGIN_MESSAGE_MAP	switch (message){

#define HANDLE_MESSAGE(wmsg,proc)	case wmsg: \
									{Bool retval=proc(hWnd,message,wParam,lParam);\
									if (retval)	return (0);}\
									break;

#define END_MESSAGE_MAP		}return (DefWindowProc(hWnd,message,wParam,lParam));

#define MESSAGE_HANDLER(proc)	inline Bool proc (HWND hWnd,UINT message,UINT wParam,UINT lParam)


//TempCode PD 03Jul97 #define TRACE_MESSAGE(wm,state)	fprintf(lpfDebugFile,wm);fprintf(lpfDebugFile,state);

//TempCode PD 03Jul97 FILE*	lpfDebugFile;


ULong	dwGlobalTimeUpdate;

//FILE*	debugfile=NULL;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	winmain
//------------------------------------------------------------------------------
//Author	Andrew McRae   
//Date		Tue 4 June 1996
//Modified	
//
//Description	Windows Entry
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

extern	void	TextTest();										//DAW 16Nov95

int WINAPI WinMain (HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    MSG         msg ;
	WNDCLASS	wndclass ;

	if (debugfile)
		fclose(debugfile);
	debugfile=fopen("\\MIG\\GAME\\deb2.out","wt");

	_Main.GameEnd 			= FALSE;
  	_Main.AppActive 		= FALSE;
	_Main.Minimized 		= FALSE;
	_Main.DDrawInitialised	= FALSE;

	#ifdef	NDEBUG

	//Add application name to global atom table - this can be
	//checked for by WinFly to prevent unwanted autoruns

	ATOM	aAtom;

	if (aAtom=GlobalFindAtom(APP_NAME)!=0)	return (FALSE);

	aAtom = GlobalAddAtom(APP_NAME);

	#endif

    if (!hPrevInstance) {
        wndclass.style          = CS_HREDRAW | CS_VREDRAW ;
        wndclass.lpfnWndProc    = WndProc ;
        wndclass.cbClsExtra     = 0 ;
        wndclass.cbWndExtra     = 0 ;
        wndclass.hInstance      = hInstance ;
        wndclass.hIcon          = LoadIcon (NULL, IDI_APPLICATION) ;
        wndclass.hCursor        = LoadCursor (NULL, IDC_ARROW) ;
        wndclass.hbrBackground  = GetStockObject (BLACK_BRUSH) ;
        wndclass.lpszMenuName   = APP_NAME;
        wndclass.lpszClassName  = APP_NAME;
        RegisterClass (&wndclass) ;
    }
/*dallas
    _Main.hWnd = CreateWindowEx (
        WS_EX_TOPMOST,
        APP_NAME,
        APP_TITLE,
        WS_POPUP,
        0,       // initial x position
        0,       // initial y position
/*dallas
        GetSystemMetrics ( SM_CXFULLSCREEN ),					//PD 14Jul97
        GetSystemMetrics ( SM_CYFULLSCREEN ),					//PD 14Jul97
dallas*/
/*dallas
		640,
		480,
		NULL,                       // parent window handle
        NULL,                       // window menu handle
        hInstance,                  // program instance handle
        NULL) ;                     // creation parameters
dallas*/
	_Main.hWnd= CreateWindow (
        APP_NAME,
        APP_TITLE,
        WS_CAPTION,
        0,       // initial x position
        0,       // initial y position
		640,
		480,
		NULL,                       // parent window handle
        NULL,                       // window menu handle
        hInstance,                  // program instance handle
        NULL) ;                     // creation parameters
    if (!_Main.hWnd)	return FALSE;

//	HDC	dcTmp = GetDC(_Main.hWnd);
  //	SetSystemPaletteUse(dcTmp,SYSPAL_NOSTATIC);
	//ReleaseDC(_Main.hWnd,dcTmp);

	_Main.MainInit();

    ShowWindow (_Main.hWnd, nCmdShow) ;

    UpdateWindow (_Main.hWnd) ;

	HDC	dcTmp = GetDC(_Main.hWnd);
	SetSystemPaletteUse(dcTmp,SYSPAL_NOSTATIC);
	ReleaseDC(_Main.hWnd,dcTmp);

	// Setup Timer
    if ( timeGetDevCaps ( &_Main.tc, sizeof (TIMECAPS)) != TIMERR_NOERROR )
    {
		MessageBox ( NULL, "Could Not Get Timer Caps", "Error", MB_OK );
        DestroyWindow ( _Main.hWnd );
        return FALSE;
    }
	_Main.wTimerRes = min(max(_Main.tc.wPeriodMin,1),_Main.tc.wPeriodMax);
 	timeBeginPeriod (_Main.wTimerRes);
	_Main.uTimerID = timeSetEvent ((1000/TimerCode::FREQ), _Main.wTimerRes, TimeProc, 0, TIME_PERIODIC);

	TextTest();

	//_Analogue.Test();

    while (!_Main.GameEnd)
    {
        if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        {
            if(msg.message==WM_QUIT)	break;

			TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }
        else if(_Main.AppActive && !_Main.Minimized)
        {
  			if (!UISheet::Win95ManageSheets(Whole_Screen))
  			{
				_Main.AppActive = FALSE;
				break;
			}
        }
		else WaitMessage();
    }

	timeKillEvent (_Main.uTimerID);

	DestroyWindow ( _Main.hWnd );

	_Main.QuitGame();

	#ifdef	NDEBUG

	GlobalDeleteAtom(aAtom);									//PD 04Jul97

	#endif

	return msg.wParam;
}


static Bool	LMBdown=FALSE;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnActivate
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnActivate)
{
	switch (LOWORD(wParam))
	{
	case WA_ACTIVE:
	case WA_CLICKACTIVE:
		_Main.AppActive=TRUE;
		break;

	case WA_INACTIVE:
		_Main.AppActive=FALSE;
		break;

		default:
		break;

	}
	return (FALSE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnSize
//Author		Paul.   
//Date			Fri 27 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnSize)
{
	if (wParam==SIZE_MINIMIZED)
	{
		_Main.Minimized = TRUE;

		if (_Main.DDrawInitialised==TRUE && Whole_Screen!=NULL)
		{
			_Main.DDrawInitialised=FALSE;

			Whole_Screen->ExitDirectDraw();

			Whole_Screen->SetTextMode();

			if (Three_Dee.b3DRunning==TRUE)
			{
				_Main.prevMode.width 		= Save_Data.screenresolution;
				_Main.prevMode.colourdepth	= Save_Data.colourdepth;
				_Main.prevMode.driver 		= Save_Data.dddriver;
			}
			else
			{
				_Main.prevMode.width = 640;
				_Main.prevMode.colourdepth = 8;
				_Main.prevMode.driver = -1;
			}
		}

 		#ifndef NDEBUG
		_asm { int 3 };
 		#endif

		return (FALSE);			//Allow call to DefWindowProc()
	}

	if (_Main.Minimized)
	{
		_Main.Minimized = FALSE;

		//Restore lost surfaces here

		if (Whole_Screen!=NULL && _Main.DDrawInitialised==FALSE)
		{
			_Main.DDrawInitialised = TRUE;

			Whole_Screen->DD.hWnd = _Main.hWnd;

			Whole_Screen->InitDirectDraw();

			Whole_Screen->ReinitDisplay();

			class Main	*lpThis;

			lpThis = &_Main;

 			if(Whole_Screen->Init(*lpThis) == FALSE)	
 				_Error.EmitSysErr(__FILE__":Failed to initialise screen record\n");

			//UISheet::Win95ForceRedraw(Whole_Screen);

			if ((_Main.prevMode.width != 640) && (_Main.prevMode.width != -640) ||
				_Main.prevMode.colourdepth != 8 || _Main.prevMode.driver != -1)
			{
				Whole_Screen->ChangeRes(_Main.prevMode);
			}
		}

		return (FALSE);
	}

	//If we get here then this is just a normal window
	//re-size message so ignore it.

	return (TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnSetCursor
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnSetCursor)
{
	SetCursor(NULL);
	return (TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnCreate
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnCreate)
{
	OpenClipboard(hWnd);
	EmptyClipboard();
	HGLOBAL hGMem= GlobalAlloc(GHND,6);
	PSTR p=(PSTR)GlobalLock(hGMem);
	p[0]='C';
	p[1]='D';
	p[2]='R';
	p[3]='X';
	p[4]='5';
	GlobalUnlock(hGMem);
	SetClipboardData(CF_TEXT,hGMem);
	CloseClipboard();
	return (TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnDestroy
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnDestroy)
{
	OpenClipboard(hWnd);
	EmptyClipboard();
	HGLOBAL hGMem= GlobalAlloc(GHND,6);
	PSTR p=(PSTR)GlobalLock(hGMem);
	p[0]='C';
	p[1]='D';
	p[2]='R';
	p[3]='X';
	p[4]='4';
	GlobalUnlock(hGMem);
	SetClipboardData(CF_TEXT,hGMem);
	CloseClipboard();
	if (*_Error.exitmsg)
	MessageBox ( hWnd,_Error.exitmsg
		,"(c) 1995 Rowan Software Ltd. Compiled "__DATE__" "__TIME__, MB_OK );

	_Main.GameEnd = TRUE;

	PostQuitMessage (0);
	return (TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnKeyDown
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnKeyDown)
{
	struct	UIKeyNoMouse myUIKeyNoMouse;
	KeyMap3d* keymap = (KeyMap3d*)Key_Tests.reftable3d.flat;
	int mappingval;
	int keycount;

	// Process Key Down Message
	if (!Key_Tests.ModeIs3D)
	{

		// User Interface
		myUIKeyNoMouse.keycode = (UByte)((lParam & 0x00ff0000) >> 16);
		if (lParam & 0x01000000)
			myUIKeyNoMouse.keyshifts = KEYSH_normext;
		else
			myUIKeyNoMouse.keyshifts = KEYSH_none;

		myUIKeyNoMouse.keyhit = KEYHIT;

		// Process Shift keys
		if (GetKeyState (VK_SHIFT) < 0)
			myUIKeyNoMouse.keyshifts |= KEYSH_Shift;
		if (GetKeyState (VK_CONTROL) < 0)
		{
			if (lParam & 0x01000000)
				myUIKeyNoMouse.keyshifts |= KEYSH_CtrlR;
			else
				myUIKeyNoMouse.keyshifts |= KEYSH_CtrlL;
		}
		if (lParam & 0x20000000)
			if (lParam & 0x01000000)
				myUIKeyNoMouse.keyshifts |= KEYSH_AltGR;
			else
				myUIKeyNoMouse.keyshifts |= KEYSH_AltL;

		Key_Tests.InsertUIKey (myUIKeyNoMouse);

	}
	else
	{
		// 3D Keyboard

		mappingval = (lParam & 0x00ff0000) >> 16;

		if (!BITTEST(keymap->keyholds, mappingval))
		{
			BITSET ( keymap->keyholds, mappingval );

			if (lParam & 0x01000000)
				mappingval = (int)keymap->mappings [mappingval][KEYSH_BN_extsh];

			// Process Shift keys
			else if (GetKeyState (VK_SHIFT) < 0)
			{
				mappingval = (int)keymap->mappings [mappingval][KEYSH_BN_ShiftL];
			}
			else if (GetKeyState (VK_CONTROL) < 0)
			{
				if (lParam & 0x01000000)
					mappingval = (int)keymap->mappings [mappingval][KEYSH_BN_CtrlR];
				else
					mappingval = (int)keymap->mappings [mappingval][KEYSH_BN_CtrlL];
			}
			else if (lParam & 0x20000000)
			{
				if (lParam & 0x01000000)
					mappingval = (int)keymap->mappings [mappingval][KEYSH_BN_AltGR];
				else
					mappingval = (int)keymap->mappings [mappingval][KEYSH_BN_AltL];

				//polyTarget++;								//PD 17Jun97
			}
			else 
				mappingval = (int)keymap->mappings [mappingval][KEYSH_BN_norm];

			BITSET (keymap->bitflags, mappingval);
			BITSET (keymap->bitflags, mappingval + 1);
	
		}
	}
	return (TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnKeyUp
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnKeyUp)
{
	struct	UIKeyNoMouse myUIKeyNoMouse;
	KeyMap3d* keymap = (KeyMap3d*)Key_Tests.reftable3d.flat;
	int mappingval;
	int keycount;
	// Process Key Up Message

	if (!Key_Tests.ModeIs3D)
	{

		myUIKeyNoMouse.keycode = (UByte)((lParam & 0x00ff0000) >> 16);
		if (lParam & 0x01000000)
			myUIKeyNoMouse.keyshifts = KEYSH_normext;
		else
			myUIKeyNoMouse.keyshifts = KEYSH_norm;

		// Process Shift keys
		if (GetKeyState (VK_SHIFT) < 0)
			myUIKeyNoMouse.keyshifts = KEYSH_Shift;
		if (GetKeyState (VK_CONTROL) < 0)
		{
			if (lParam & 0x01000000)
				myUIKeyNoMouse.keyshifts = KEYSH_CtrlR;
			else
				myUIKeyNoMouse.keyshifts = KEYSH_CtrlL;
		}
		if (lParam & 0x20000000)
			if (lParam & 0x01000000)
				myUIKeyNoMouse.keyshifts = KEYSH_AltGR;
			else
				myUIKeyNoMouse.keyshifts = KEYSH_AltL;

		myUIKeyNoMouse.keyhit = KEYREL;

		Key_Tests.InsertUIKey (myUIKeyNoMouse);

	}
	else
	{	

		// 3D Keyboard
		mappingval = (lParam & 0x00ff0000) >> 16;
		BITRESET ( keymap->keyholds, mappingval);
		for (keycount=0; keycount<8; keycount++)
			BITRESET (keymap->bitflags, (int)keymap->mappings [mappingval][keycount]);
	}
	return (TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IgnoreMessage
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(IgnoreMessage)
{
	return (TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnLButtonDown
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnLButtonDown)
{
	if (!Key_Tests.ModeIs3D)
	{

		UIKeyNoMouse	myfakekey;

		keytests* keyboard = &Key_Tests;

	 	//insert key press for LMB+i
		myfakekey.keycode=100/*Raw_Extra0ML*/+0;
		myfakekey.keyshifts=0;
		myfakekey.keyhit=KEYHIT;
		(keyboard->*keyboard->InsertUIKeyThru)(myfakekey);
		LMBdown=TRUE;

	}
	return (TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnLButtonUp
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnLButtonUp)
{
	if (!Key_Tests.ModeIs3D)
	{

		UIKeyNoMouse	myfakekey;

		keytests* keyboard = &Key_Tests;

	 	//insert key rls for LMB+i
		myfakekey.keycode=100/*Raw_Extra0ML*/+0;
		myfakekey.keyshifts=0;
		myfakekey.keyhit=KEYREL;
		(keyboard->*keyboard->InsertUIKeyThru)(myfakekey);
		LMBdown=FALSE;

	}
	return (TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnMouseMove
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnMouseMove)
{
	ScreenXY& mousepos=Key_Tests.mousepos();

	mousepos.x = LOWORD (lParam) * Whole_Screen->virtualXscale;
	mousepos.y = HIWORD (lParam) * Whole_Screen->virtualYscale;


	if (!Key_Tests.ModeIs3D)
	{

		UIKeyNoMouse	myfakekey;

		keytests* keyboard = &Key_Tests;

	 	//insert key rls for LMB+i
		myfakekey.keycode=100/*Raw_Extra0ML*/+0;
		myfakekey.keyshifts=0;
		myfakekey.keyhit=KEYHELD;
		if (LMBdown)
			(keyboard->*keyboard->InsertUIKeyThru)(myfakekey);

	}
	return (TRUE);
}

static int nColIndex[]=
{
	COLOR_3DDKSHADOW ,
	COLOR_3DFACE, 
	COLOR_BTNFACE ,
	COLOR_3DHILIGHT, 
	COLOR_3DHIGHLIGHT, 
	COLOR_BTNHILIGHT, 
	COLOR_BTNHIGHLIGHT ,
	COLOR_3DLIGHT ,
	COLOR_3DSHADOW, 
	COLOR_BTNSHADOW ,
	COLOR_ACTIVEBORDER, 
	COLOR_ACTIVECAPTION, 
	COLOR_APPWORKSPACE ,
	COLOR_BACKGROUND, 
	COLOR_DESKTOP ,
	COLOR_BTNTEXT ,
	COLOR_CAPTIONTEXT, 
	COLOR_GRAYTEXT ,
	COLOR_HIGHLIGHT ,
	COLOR_HIGHLIGHTTEXT, 
	COLOR_INACTIVEBORDER, 
	COLOR_INACTIVECAPTION, 
	COLOR_INACTIVECAPTIONTEXT, 
	COLOR_INFOBK ,
	COLOR_INFOTEXT, 
	COLOR_MENU ,
	COLOR_MENUTEXT, 
	COLOR_SCROLLBAR, 
	COLOR_WINDOW ,
	COLOR_WINDOWFRAME, 
	COLOR_WINDOWTEXT ,
	-1
};

static DWORD dwSaveCol[32];

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnKillFocus
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnKillFocus)
{
//TempCode PD 1Dec97 	HDC	dcTmp = GetDC(_Main.hWnd);
//TempCode PD 1Dec97 
//TempCode PD 1Dec97 	//restore the original system palette entries
//TempCode PD 1Dec97 
//TempCode PD 1Dec97 	for (int i=0;nColIndex[i]!=-1;i++)
//TempCode PD 1Dec97 		SetSysColors(1,&i,&dwSaveCol[i]);
//TempCode PD 1Dec97 
//TempCode PD 1Dec97 	SetSystemPaletteUse(dcTmp,SYSPAL_STATIC);
//TempCode PD 1Dec97 
//TempCode PD 1Dec97 	ReleaseDC(_Main.hWnd,dcTmp);

//DeadCode PD 19Jan98 	_asm { int 3 }												//PD 19Jan98

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnKillFocus
//Author		Paul.   
//Date			Wed 25 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_HANDLER(OnSetFocus)
{
//TempCode PD 1Dec97 	HDC	dcTmp = GetDC(_Main.hWnd);
//TempCode PD 1Dec97 
//TempCode PD 1Dec97 	//preserve the original system palette entries
//TempCode PD 1Dec97 
//TempCode PD 1Dec97 	for (int i=0;nColIndex[i]!=-1;i++)
//TempCode PD 1Dec97 		dwSaveCol[i]=GetSysColor(nColIndex[i]);
//TempCode PD 1Dec97 
//TempCode PD 1Dec97 	SetSystemPaletteUse(dcTmp,SYSPAL_NOSTATIC);
//TempCode PD 1Dec97 
//TempCode PD 1Dec97 	ReleaseDC(_Main.hWnd,dcTmp);
//TempCode PD 1Dec97 
	return (FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	WndProc
//------------------------------------------------------------------------------
//Author	Andrew McRae   
//Date		Tue 4 June 1996
//Modified	
//
//Description	Window Procedure Function
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, UINT wParam, LONG lParam)
//LastModified:	PD 03Jul97
{
	BEGIN_MESSAGE_MAP;

	HANDLE_MESSAGE(	WM_ACTIVATE,		OnActivate);
	HANDLE_MESSAGE( WM_SETCURSOR,		OnSetCursor);
	HANDLE_MESSAGE( WM_CREATE,			OnCreate);
	HANDLE_MESSAGE( WM_DESTROY,			OnDestroy);
	HANDLE_MESSAGE( WM_KEYDOWN,			OnKeyDown);
	HANDLE_MESSAGE( WM_SYSKEYDOWN,		OnKeyDown);
	HANDLE_MESSAGE(	WM_KEYUP,			OnKeyUp);
	HANDLE_MESSAGE(	WM_SYSKEYUP,		OnKeyUp);
	HANDLE_MESSAGE( WM_CHAR,			IgnoreMessage);
	HANDLE_MESSAGE( WM_SYSCHAR,			IgnoreMessage);
	HANDLE_MESSAGE( WM_LBUTTONDOWN,		OnLButtonDown);
	HANDLE_MESSAGE( WM_LBUTTONUP,		OnLButtonUp);
	HANDLE_MESSAGE( WM_MOUSEMOVE,		OnMouseMove);
	HANDLE_MESSAGE( WM_KILLFOCUS,		OnKillFocus);
	HANDLE_MESSAGE( WM_SETFOCUS,		OnSetFocus);

	HANDLE_MESSAGE( WM_SIZE,			OnSize);

	END_MESSAGE_MAP;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TimeProc
//Author		Andrew McRae
//Date			Tue 11 Jun 1996
//
//Description	50 Hz Timer CallBack Function
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void CALLBACK TimeProc (UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	//PD 07Jul97 - prevent timer updates when the game is inactive
	if (_Main.AppActive==TRUE)
	{
		dwGlobalTimeUpdate++;

		Timer_Code.IncTus ();
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Main::MainInit
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 5 Jul 1995
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
void Main::MainInit(void)
{
	if(InitFileSystem(*this)==FALSE)
		_Error.EmitSysErr(__FILE__":Failed to init file system\n");

	_DPlay.Implemented = FALSE;

	_Miles.Init();

	if (_Main.DDrawInitialised==FALSE)
	{
		_Main.DDrawInitialised = TRUE;

		if((Whole_Screen = new Display) == 0)
			_Error.EmitSysErr(__FILE__":Failed to create screen record\n");

		Whole_Screen->DD.hWnd = _Main.hWnd;

		Whole_Screen->InitDirectDraw ();

 		if(	Whole_Screen->Init(*this) == FALSE)	
 			_Error.EmitSysErr(__FILE__":Failed to initialise screen record\n");
  }
//DeadCode RJS 03Dec96 	FILEMAN.errhandle = fopen("tmpcrap.txt","wt");
}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Main::QuitGame
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 5 Jul 1995
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
void Main::QuitGame()
{
	_DPlay.ExitDirectPlay();

	if (_Main.DDrawInitialised==TRUE)
	{
		_Main.DDrawInitialised=FALSE;

		Whole_Screen->ExitDirectDraw ();	// put in Display::Exit

		Whole_Screen->SetTextMode();
	}

	_Miles.ShutDownMiles();										//RJS 15Dec97

	delete	Whole_Screen;

	Whole_Screen=NULL;

	//DeadCode PD 20Jan98 if (debugfile!=NULL) fclose (debugfile);
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Test
//Author		Andrew McRae
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Analogue::Test()
{
	devices[0].devfile=FILLIB_JOYSTICK_DLL;
	(devices[0].activeaxes|=AU_AILERON)|=AU_ELEVATOR;
//DeadCode RDH 19Apr96 	((devices[0].activeaxes|=AU_AILERON)|=AU_ELEVATOR)|=AU_THROTTLE;
 	Initialise();
}




//TempCode ARM 25Nov96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode ARM 25Nov96 //Procedure		GetCDFile
//TempCode ARM 25Nov96 //Author		Andrew McRae
//TempCode ARM 25Nov96 //Date			Mon 4 Nov 1996
//TempCode ARM 25Nov96 //
//TempCode ARM 25Nov96 //Description	
//TempCode ARM 25Nov96 //
//TempCode ARM 25Nov96 //Inputs		
//TempCode ARM 25Nov96 //
//TempCode ARM 25Nov96 //Returns	
//TempCode ARM 25Nov96 //
//TempCode ARM 25Nov96 //------------------------------------------------------------------------------
//TempCode ARM 25Nov96 Bool GetCDFile (FileNum cdfilenum,char* Name, ULong Offset)
//TempCode ARM 25Nov96 {
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	ULong ThreadID;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	*CDFile = 0;
//TempCode ARM 25Nov96 	CDOffset = 0;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	CDCode = 5;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	CDReady = FALSE;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	ThreadID = _beginthread (ThreadFunction, NULL, 8192, NULL);
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	if (ThreadID == -1)
//TempCode ARM 25Nov96 	{
//TempCode ARM 25Nov96 		CDCode = 6;
//TempCode ARM 25Nov96 		return FALSE;
//TempCode ARM 25Nov96 	}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	strcpy (CDFile, Name);
//TempCode ARM 25Nov96 	CDOffset = Offset;
//TempCode ARM 25Nov96 	CDfilenum = cdfilenum;										//PD 07Nov96
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	CDCode = 3;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	CDReady = TRUE;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	return TRUE;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 }
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode ARM 25Nov96 //Procedure		ThreadFunction
//TempCode ARM 25Nov96 //Author		Andrew McRae
//TempCode ARM 25Nov96 //Date			Mon 4 Nov 1996
//TempCode ARM 25Nov96 //
//TempCode ARM 25Nov96 //Description	
//TempCode ARM 25Nov96 //
//TempCode ARM 25Nov96 //Inputs		
//TempCode ARM 25Nov96 //
//TempCode ARM 25Nov96 //Returns	
//TempCode ARM 25Nov96 //
//TempCode ARM 25Nov96 //------------------------------------------------------------------------------
//TempCode ARM 25Nov96 void ThreadFunction (void * ptr)
//TempCode ARM 25Nov96 {
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 //	MessageBox (NULL, "In Thread", "Message", MB_OK);
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	CDCode = 3;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	while (!CDReady) {}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	// Load in Selected File
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	// Name is CDFile
//TempCode ARM 25Nov96 	// Offset is CDOffset;
//TempCode ARM 25Nov96 	// Block size is 1000h
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	if (CDData != NULL)		// delete previous memory (if any)
//TempCode ARM 25Nov96 	{
//TempCode ARM 25Nov96 		delete CDData;
//TempCode ARM 25Nov96 		CDData = NULL;
//TempCode ARM 25Nov96 	}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	// check for invalid params
//TempCode ARM 25Nov96 	if (!(*CDFile))
//TempCode ARM 25Nov96 	{
//TempCode ARM 25Nov96 		CDCode = 1;
//TempCode ARM 25Nov96 		return;
//TempCode ARM 25Nov96 	}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	// Open the file
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	if (CDfilehandle==NULL)
//TempCode ARM 25Nov96 	{
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 		CDfilehandle = fopen(CDFile,"rb");
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 		char* dest;
//TempCode ARM 25Nov96 		dest = (char*)&MMIOInfo;
//TempCode ARM 25Nov96 		ULong n;
//TempCode ARM 25Nov96 		for (n=0; n<sizeof(MMIOInfo); n++)
//TempCode ARM 25Nov96 			*dest++ = 0;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 		CDfilehandle = mmioOpen (CDFile, &MMIOInfo, MMIO_READ);
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 		if (!CDfilehandle)
//TempCode ARM 25Nov96 		{
//TempCode ARM 25Nov96 			CDCode = 2;
//TempCode ARM 25Nov96 			return;
//TempCode ARM 25Nov96 		}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 		switch (MMIOInfo.wErrorRet)
//TempCode ARM 25Nov96 		{
//TempCode ARM 25Nov96 			case MMIOERR_ACCESSDENIED:
//TempCode ARM 25Nov96 			case MMIOERR_INVALIDFILE:
//TempCode ARM 25Nov96 			case MMIOERR_NETWORKERROR:
//TempCode ARM 25Nov96 			case MMIOERR_PATHNOTFOUND:
//TempCode ARM 25Nov96 			case MMIOERR_SHARINGVIOLATION:
//TempCode ARM 25Nov96 			case MMIOERR_TOOMANYOPENFILES:
//TempCode ARM 25Nov96 				CDCode = 2;
//TempCode ARM 25Nov96 				return;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 		}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 		CDlastfilenum = CDfilenum;
//TempCode ARM 25Nov96 	}
//TempCode ARM 25Nov96 	else
//TempCode ARM 25Nov96 	{
//TempCode ARM 25Nov96 		if (CDlastfilenum!=CDfilenum)
//TempCode ARM 25Nov96 		{
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 			fclose(CDfilehandle);
//TempCode ARM 25Nov96 			mmioClose (CDfilehandle, MMIO_FHOPEN);
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 			CDfilehandle = fopen(CDFile,"rb");
//TempCode ARM 25Nov96 			CDfilehandle = mmioOpen (CDFile, &MMIOInfo, MMIO_READ);
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 			if (!CDfilehandle)
//TempCode ARM 25Nov96 			{
//TempCode ARM 25Nov96 				CDCode = 2;
//TempCode ARM 25Nov96 				return;
//TempCode ARM 25Nov96 			}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 			switch (MMIOInfo.wErrorRet)
//TempCode ARM 25Nov96 			{
//TempCode ARM 25Nov96 				case MMIOERR_ACCESSDENIED:
//TempCode ARM 25Nov96 				case MMIOERR_INVALIDFILE:
//TempCode ARM 25Nov96 				case MMIOERR_NETWORKERROR:
//TempCode ARM 25Nov96 				case MMIOERR_PATHNOTFOUND:
//TempCode ARM 25Nov96 				case MMIOERR_SHARINGVIOLATION:
//TempCode ARM 25Nov96 				case MMIOERR_TOOMANYOPENFILES:
//TempCode ARM 25Nov96 					CDCode = 2;
//TempCode ARM 25Nov96 					return;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 			}
//TempCode ARM 25Nov96 			CDlastfilenum = CDfilenum;
//TempCode ARM 25Nov96 		}
//TempCode ARM 25Nov96 	}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	// Move to required position in the file
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	int res;
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 	res = fseek (CDfilehandle, CDOffset, SEEK_SET);
//TempCode ARM 25Nov96 	res = mmioSeek (CDfilehandle, CDOffset, SEEK_SET);
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 	if (res != 0)
//TempCode ARM 25Nov96 	if (res == -1)
//TempCode ARM 25Nov96 	{
//TempCode ARM 25Nov96 		CDCode = 2;
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 		fclose (CDfilehandle);
//TempCode ARM 25Nov96 		mmioClose (CDfilehandle, MMIO_FHOPEN);
//TempCode ARM 25Nov96 		CDfilenum = CDlastfilenum = INVALIDFILENUM;
//TempCode ARM 25Nov96 		return;
//TempCode ARM 25Nov96 	}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	// Get Memory for data
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	CDData = new char [0x1000];
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	if (CDData == NULL)
//TempCode ARM 25Nov96 	{
//TempCode ARM 25Nov96 		CDCode = 7;
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 		fclose (CDfilehandle);
//TempCode ARM 25Nov96 		mmioClose (CDfilehandle, MMIO_FHOPEN);
//TempCode ARM 25Nov96 		CDfilenum = CDlastfilenum = INVALIDFILENUM;
//TempCode ARM 25Nov96 		return;
//TempCode ARM 25Nov96 	}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	// load in the data
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 	res = fread (CDData, 0x1000, 1, CDfilehandle);
//TempCode ARM 25Nov96 	res = mmioRead (CDfilehandle, CDData, 0x1000);
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 	if (res == 0)
//TempCode ARM 25Nov96 	if ((res == 0) || (res == -1))
//TempCode ARM 25Nov96 	{
//TempCode ARM 25Nov96 		CDCode = 2;
//TempCode ARM 25Nov96 		delete (CDData);
//TempCode ARM 25Nov96 		CDData = NULL;
//TempCode ARM 25Nov96 //TempCode ARM 07Nov96 		fclose (CDfilehandle);
//TempCode ARM 25Nov96 		mmioClose (CDfilehandle, MMIO_FHOPEN);
//TempCode ARM 25Nov96 		CDfilenum = CDlastfilenum = INVALIDFILENUM;
//TempCode ARM 25Nov96 		return;
//TempCode ARM 25Nov96 	}
//TempCode ARM 25Nov96 
//TempCode ARM 25Nov96 	CDCode = 4;
//TempCode ARM 25Nov96 	return;
//TempCode ARM 25Nov96 }



