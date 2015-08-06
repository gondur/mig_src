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
//Filename       winststb.cpp
//System         
//Author         Andrew McRae
//Date           Mon 28 Oct 1996
//Description    Check for CD in drive and launch Installer
//------------------------------------------------------------------------------

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSTALL_MAXCHARS 256

BOOL ChopPathName (char * DirName);
DWORD GetCDDrives (char* Let);


int WINAPI WinMain (HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpszCmdParam, int iCmdShow)
{

	hInstance = hInstance;
	hPrevInstance = hPrevInstance;
	lpszCmdParam = lpszCmdParam;
	iCmdShow = iCmdShow;

	// Check Cd is in CD Drive


	char TestDrive [64];

	char CDDrives [12];

	DWORD NoofDrives;

	NoofDrives = GetCDDrives (CDDrives);

	DWORD Count,Go;
	char CurrDir [256];

	Count = 3;
	Go = FALSE;


	for (;;)
	{

		DWORD i;
		for (i=0; i<strlen(CDDrives); i++)
		{

			TestDrive[0] = CDDrives[i];
			TestDrive[1] = 0;

			strcat (TestDrive, ":\\FLY");

			// Set Current Directory


			strcpy (CurrDir, TestDrive);

			DWORD fileattb;
			fileattb = GetFileAttributes (CurrDir);

			if (!(fileattb & FILE_ATTRIBUTE_DIRECTORY) || (fileattb == 0xffffffffL))
			{
			}
			else
			{
				Go = TRUE;
				break;
			}

		}

		if (i == strlen(CDDrives))
		{

			// failed
			int res;

			res = MessageBox (NULL, "Please insert the Flying Corps CD into your CD drive.", "Message", MB_OKCANCEL);

			if (res == IDCANCEL)
				return 0;
		}

		Count--;

		if (!Count)
			break;

	}



	if (!Go)
	{
		MessageBox (NULL, "The Flying Corps CD is required to run the Installer.", "Message", MB_OK);
		return 0;
	}

	// CurrDir has path to winstall.exe on the CD

	// Launch Winstall

//	ProcName = GetCommandLine ();

//	if (*CurrDir == '"')
//		CurrDir++;

//	ChopPathName (CurrDir);

	char ExeName [INSTALL_MAXCHARS];
	char DirName [INSTALL_MAXCHARS];

	strcpy (ExeName, CurrDir);
	strcat (ExeName, "\\");
	strcat (ExeName, "winstall.exe");

	strcpy (DirName, CurrDir);

	STARTUPINFO StartUpInfo;
	PROCESS_INFORMATION ProcessInfo;

	StartUpInfo.cb = sizeof (STARTUPINFO);
	StartUpInfo.lpReserved = NULL;
	StartUpInfo.lpDesktop = NULL;
	StartUpInfo.lpTitle = NULL;
	StartUpInfo.dwX = 0;
	StartUpInfo.dwY = 0;
	StartUpInfo.dwXSize = 0;
	StartUpInfo.dwYSize = 0;
	StartUpInfo.dwXCountChars = 0;
	StartUpInfo.dwYCountChars = 0;
	StartUpInfo.dwFillAttribute = NULL;
	StartUpInfo.dwFlags = 0;
	StartUpInfo.wShowWindow = 0;
	StartUpInfo.cbReserved2 = 0;
	StartUpInfo.lpReserved2 = NULL;
	StartUpInfo.hStdInput = NULL;
	StartUpInfo.hStdOutput = NULL;
	StartUpInfo.hStdError = NULL;

	CreateProcess (
		ExeName,
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS,
		NULL,
		DirName,
		&StartUpInfo,
		&ProcessInfo);


	return 0;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChopPathName
//Author		Andrew McRae
//Date			Tue 22 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOOL ChopPathName (char * DirName)
{

	char* ptr;
	ptr = DirName + strlen (DirName) - 1;

	for (;;)
	{

		if (ptr <= DirName)
			return FALSE;

		if (strlen (DirName) < 4)
			return FALSE;

		if (*ptr == '\\')
		{
			*ptr = 0;
			return TRUE;
		}

		ptr--;

	}



}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetCDDrives
//Author		Andrew McRae
//Date			Fri 25 Oct 1996
//
//Description	Returns no. of drives & all CDDrive letters in Let
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DWORD GetCDDrives (char* Let)
{

	DWORD DriveMask;

	DriveMask = GetLogicalDrives ();

	char strg [12];

	DWORD n = 26;
	DWORD b = 1;
	char letter = 'a';

	DWORD m = 0;

	for (;;)
	{
		n--;

		if (DriveMask & b)
		{

			strcpy (strg, "a:\\");
			strg [0] = letter;

			if (GetDriveType (strg) == DRIVE_CDROM)
			{
				*(Let + m) = letter;
				m++;
				*(Let + m) = 0;
			}

		}

		b += b;
		letter ++;

		if (!n)
			break;

	}

	return m;

}


