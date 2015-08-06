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
//Filename       winfly.cpp
//System         
//Author         Andrew McRae
//Date           Wed 23 Oct 1996
//Description    
//------------------------------------------------------------------------------

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSTALL_MAXCHARS 256

BOOL ChopPathName (char * DirName);

//TempCode ARM 17Dec96 #define SEARCH_STRING "[CTL0001_Device]"
//TempCode ARM 17Dec96 #define SEARCH_STRING2 "CopyFiles=SB16.CopyList"
//TempCode ARM 17Dec96 #define NEW_LINE "DelReg=CLCheckSB16.DelReg"
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 #define INF_FILE "\\INF\\MSDSOUND.TMP"

int WINAPI WinMain (HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpszCmdParam, int iCmdShow)
{

	// Temp Code is not Complete ARM 17 Dec 1996

//TempCode ARM 17Dec96 	// fix msdsound.inf bug
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	
//TempCode ARM 17Dec96 	// find required file
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	char SearchString [] = SEARCH_STRING;
//TempCode ARM 17Dec96 	char SearchString2 [] = SEARCH_STRING2;
//TempCode ARM 17Dec96 	char NewLine [] = NEW_LINE;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	char FileName [128];
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	GetWindowsDirectory (FileName, 128);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	strcat (FileName, INF_FILE);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	HANDLE file;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	SECURITY_ATTRIBUTES SecurityAttributes;
//TempCode ARM 17Dec96 	SECURITY_DESCRIPTOR SecurityDescriptor;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	InitializeSecurityDescriptor (&SecurityDescriptor, SECURITY_DESCRIPTOR_REVISION);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96   	SecurityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
//TempCode ARM 17Dec96   	SecurityAttributes.lpSecurityDescriptor = &SecurityDescriptor;
//TempCode ARM 17Dec96   	SecurityAttributes.bInheritHandle = TRUE;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	file = CreateFile (FileName,
//TempCode ARM 17Dec96 		GENERIC_READ,
//TempCode ARM 17Dec96 		0,
//TempCode ARM 17Dec96 		&SecurityAttributes,
//TempCode ARM 17Dec96 		OPEN_EXISTING,
//TempCode ARM 17Dec96 		FILE_ATTRIBUTE_NORMAL,
//TempCode ARM 17Dec96 		NULL);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	if (file != NULL)
//TempCode ARM 17Dec96 	{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 		DWORD losize,hisize;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 		losize = GetFileSize (file, &hisize);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 //TempCode ARM 17Dec96 		char asd [64];
//TempCode ARM 17Dec96 //TempCode ARM 17Dec96 		wsprintf (asd, "%s %ld,%ld", FileName, hisize, losize);
//TempCode ARM 17Dec96 //TempCode ARM 17Dec96 		MessageBox (NULL, asd, "Size", MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 		if (losize != 0xffffffffl)
//TempCode ARM 17Dec96 		{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 			char* Buffer;
//TempCode ARM 17Dec96 			Buffer = NULL;
//TempCode ARM 17Dec96 			Buffer = new char [losize + sizeof(NEW_LINE) + 1];
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 			if (Buffer != NULL)
//TempCode ARM 17Dec96 			{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 				// read in file to memory
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 				DWORD readin;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 				ReadFile (file,
//TempCode ARM 17Dec96 					Buffer,
//TempCode ARM 17Dec96 					losize,
//TempCode ARM 17Dec96 					&readin,
//TempCode ARM 17Dec96 					NULL);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 				CloseHandle (file);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 				if (readin == losize)
//TempCode ARM 17Dec96 				{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 					// find SEARCH_STRING
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 					DWORD n,m,l;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 					BOOL foundit = FALSE;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 					for (n=0; n<losize; n++)
//TempCode ARM 17Dec96 					{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 						for (m=0; m<strlen(SEARCH_STRING); m++)
//TempCode ARM 17Dec96 						{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							if (*(Buffer+n+m) != SearchString[m])
//TempCode ARM 17Dec96 								break;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 						}
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 						// *(n+m) should == '\n' or '\r'
//TempCode ARM 17Dec96 						if ((*(Buffer + n + m) != '\n') && (*(Buffer + n + m) != '\r'))
//TempCode ARM 17Dec96 							m = 0;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 						if (m == strlen(SEARCH_STRING))
//TempCode ARM 17Dec96 						{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							m += 2;	// go past last char in SEARCH_STRING & newline character
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							// search for SEARCH_STRING2
//TempCode ARM 17Dec96 							// must be directly after above
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							for (l=0; l<strlen(SEARCH_STRING2); l++)
//TempCode ARM 17Dec96 							{
//TempCode ARM 17Dec96 								if (*(Buffer+n+m+l) != SearchString2[l])
//TempCode ARM 17Dec96 									break;
//TempCode ARM 17Dec96 							}
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							if (l == strlen(SEARCH_STRING2))
//TempCode ARM 17Dec96 							{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								// move remaining data forward
//TempCode ARM 17Dec96 								// from end to n + 1
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								l += 2;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 //TempCode ARM 17Dec96 								char poo [256];
//TempCode ARM 17Dec96 //TempCode ARM 17Dec96 								for (DWORD h=0; h<64; h++)
//TempCode ARM 17Dec96 //TempCode ARM 17Dec96 									poo[h+1] = *(Buffer + n + m + l+h);
//TempCode ARM 17Dec96 //TempCode ARM 17Dec96 								poo[h] = 0;
//TempCode ARM 17Dec96 //TempCode ARM 17Dec96 								poo[0] = 'X';
//TempCode ARM 17Dec96 //TempCode ARM 17Dec96 								MessageBox (NULL, poo, "Search 2", MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								DWORD k;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								DWORD shft1,shft2, size;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								shft1 = n + m + l;
//TempCode ARM 17Dec96 								size = losize - shft1;
//TempCode ARM 17Dec96 								shft2 = shft1 + sizeof (NEW_LINE) + 1;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								for (k=shft2; k>=shft1; k--)
//TempCode ARM 17Dec96 									*(Buffer + k + strlen (NEW_LINE)) = *(Buffer + k);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								// put in new text
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								for (k=shft1; k<strlen(NEW_LINE); k++)
//TempCode ARM 17Dec96 									*(Buffer + k) = NewLine[k];
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								foundit = TRUE;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 								break;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							}
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 						}
//TempCode ARM 17Dec96 					}
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 					if (foundit)
//TempCode ARM 17Dec96 					{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 						MessageBox (NULL, SEARCH_STRING, FileName, MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 						file = CreateFile (FileName,
//TempCode ARM 17Dec96 							GENERIC_WRITE,
//TempCode ARM 17Dec96 							0,
//TempCode ARM 17Dec96 							&SecurityAttributes,
//TempCode ARM 17Dec96 							OPEN_EXISTING,
//TempCode ARM 17Dec96 							FILE_ATTRIBUTE_NORMAL,
//TempCode ARM 17Dec96 							NULL);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 						if (file != NULL)
//TempCode ARM 17Dec96 						{
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							// write new file from memory
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							DWORD writeout;
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							WriteFile (file,
//TempCode ARM 17Dec96 								Buffer,
//TempCode ARM 17Dec96 								losize + sizeof (NEW_LINE) + 1,
//TempCode ARM 17Dec96 								&writeout,
//TempCode ARM 17Dec96 								NULL);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							if (writeout != (losize + sizeof (NEW_LINE) + 1))
//TempCode ARM 17Dec96 								MessageBox (NULL, "Failed to write whole file", "Message", MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 							CloseHandle (file);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 						}
//TempCode ARM 17Dec96 						else
//TempCode ARM 17Dec96 							MessageBox (NULL, "Failed to open Write File", "Message", MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 					}
//TempCode ARM 17Dec96 					else
//TempCode ARM 17Dec96 						MessageBox (NULL, "Failed to find string", "Message", MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 				}
//TempCode ARM 17Dec96 				else
//TempCode ARM 17Dec96 					MessageBox (NULL, "Failed to read whole file", "Message", MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 				delete (Buffer);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 			}
//TempCode ARM 17Dec96 			else
//TempCode ARM 17Dec96 				MessageBox (NULL, "Failed to get Buffer memory", "Message", MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 		}
//TempCode ARM 17Dec96 		else
//TempCode ARM 17Dec96 			MessageBox (NULL, "Failed to get file size", "Message", MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	}
//TempCode ARM 17Dec96 	else
//TempCode ARM 17Dec96 		MessageBox (NULL, "Failed to open file", "Message", MB_OK);
//TempCode ARM 17Dec96 
//TempCode ARM 17Dec96 	return 0;

	hInstance = hInstance;
	hPrevInstance = hPrevInstance;
	lpszCmdParam = lpszCmdParam;
	iCmdShow = iCmdShow;

	char* ProcName;

	ProcName = GetCommandLine ();

	if (*ProcName == '"')
		ProcName++;

	ChopPathName (ProcName);

	char ExeName [INSTALL_MAXCHARS];
	char DirName [INSTALL_MAXCHARS];

	STARTUPINFO StartUpInfo;
	PROCESS_INFORMATION ProcessInfo;

	// launch slave16.exe

	strcpy (ExeName, ProcName);
	strcat (ExeName, "\\");
	strcat (ExeName, "slave16.exe");

	strcpy (DirName, ProcName);

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

	// launch wfly.exe

	strcpy (ExeName, ProcName);
	strcat (ExeName, "\\");
	strcat (ExeName, "wfly.exe");

	strcpy (DirName, ProcName);

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
