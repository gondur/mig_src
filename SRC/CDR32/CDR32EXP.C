// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993 - 1996  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   exports.c
//
//  PURPOSE:   Contains the DLL's exported functions.
//
//  FUNCTIONS:
//    DLL32Function -  Calls the 16 bit side of the thunk
//
//  COMMENTS:
//    This is a simple demonstration of the structure of the thunking
//    mechanism.  It is not designed to cover all test cases of thunks
//    but rather to provide a framework for adding a thunking layer
//    to a 32 to 16 bit application.
//

#include <windows.h>
#include "dllglob.h"

// Prototype for functions in 16-bit dll.

typedef unsigned char UByte,*UByteP;
typedef signed char SByte,*SByteP;

typedef unsigned short UWord,*UWordP;
typedef signed short SWord,*SWordP;

typedef unsigned long int ULong,*ULongP;
typedef signed long int SLong,*SLongP;


UWord PASCAL InitCDFS16();
void PASCAL ExitCDFS16();
BOOL PASCAL SeekToLocation16(UWord,ULong);


DLLEXPORT UWord WINAPI InitCDFS()
{
	return InitCDFS16();
}

DLLEXPORT void WINAPI ExitCDFS()
{
	ExitCDFS16();
}

DLLEXPORT BOOL WINAPI SeekToLocation(UWord hFile,ULong fOffset)
{
	return SeekToLocation16(hFile,fOffset);
}
