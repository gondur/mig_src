//------------------------------------------------------------------------------
//Filename       winfile.h
//System         
//Author         Paul.   
//Date           Tue 22 Sep 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	WINFILE_Included
#define	WINFILE_Included

#define	DEFAULT_WINFILE 0

extern "C"
{
	__declspec(dllimport) UWord WINAPI InitCDFS();
	__declspec(dllimport) void WINAPI ExitCDFS();
	__declspec(dllimport) BOOL WINAPI SeekToLocation(UWord hFile,ULong fOffset);
};

#endif
