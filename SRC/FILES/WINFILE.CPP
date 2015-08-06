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

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		Paul.   
//Date			Mon 4 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------


#include	"dosdefs.h"
#include 	<stdio.h>
#include    <string.h>
#include    <direct.h>

#define		F_GRAFIX

#include	"hardpasm.h"
#include	"myerror.h"
#include	"mymath.h"
#include	"fileman.h"
#include	"mscdex.h"
#include	"myAngles.h"
#include	"worldinc.h"
#include	"world.h"
#include	"Mytime.h"
#include	"stub3d.h"
#include "savegame.h"
const	int	DOSFILE_SEEKSTEP = 8*2048;							//PD 12Nov96

#define WIN32_LEAN_AND_MEAN										//ARM 06Nov96

#include	<process.h>											//ARM 06Nov96
#include 	<windows.h>											//ARM 06Nov96
#include 	<windowsx.h>										//ARM 06Nov96
#include 	<mmsystem.h>										//ARM 06Nov96

#include	"Files.G"											//ARM 06Nov96
#include	"FileMan.h"											//ARM 06Nov96

#define _WINBASE_

static int pingcount=0;

// see winmove.cpp												//ARM 06Nov96
extern ULong CDCode;	// 1 = invalid data						//ARM 06Nov96
						// 2 = failed							//ARM 06Nov96
						// 3 = working							//ARM 06Nov96
						// 4 = finished							//ARM 06Nov96
						// 5 = idle or not active				//ARM 06Nov96
						// 6 = can't start thread				//ARM 06Nov96
						// 7 = could not get memory				//ARM 06Nov96
extern char* CDData;	// Pointer to data						//ARM 06Nov96

const	int	DOSFILE_SECTSIZE = 2048;							//PD 18Nov96

//char 	readblockbufferbase[8192];
char 	readblockbufferbase[65536];
char* 	readblockbuffer=(char*)(((int)readblockbufferbase+2047)&-2048);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CDSeek
//Author		Paul.   
//Date			Tue 29 Oct 1996
//
//Description	Interface to MSCDEX via int 2Fh funtion 15h subfunction 10h
//
//Inputs		Request seek to block 'pos'
//
//Returns		Status after executing the command
//
//------------------------------------------------------------------------------
UWord fileman::CDSeek(ULong seekpos)
{
	for (int fileindex=0;cdfile->number!=cdfiles[fileindex].number;fileindex++)
	{
		if (fileindex>=MAXCDFILEENTRIES)
			_Error.EmitSysErr("Invalid CD filenumber");
	}

	switch (fileindex)
	{
		case 0:	fileindex=0;	break;	//north.dat
		case 1:	fileindex=1;	break;	//east.dat
		case 2:	fileindex=2;	break;	//south.dat
		case 3:	fileindex=3;	break;	//west.dat
	}
//TempCode PD 08Oct98 	SeekToLocation(fileindex,seekpos);	//in CDR32.DLL

	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupAreaFiles
//Author		Paul.   
//Date			Mon 18 Nov 1996
//
//Description	Opens and sets up the data structures required to
//				keep all four landscape data files open
//
//Inputs		areafiles = ptr to a list of the four area file numbers required
//
//Returns	
//
//------------------------------------------------------------------------------
void fileman::SetupAreaFiles(FileNum* areafiles)
{
	FILE*	filehandle;
	FileNum	myfile;

  	for (int fileindex=0;fileindex<MAXCDFILEENTRIES;fileindex++)
	{
		myfile = areafiles[fileindex];

		if (cdfiles[fileindex].number!=myfile)
		{
			char* name=namenumberedfile(myfile);
			HANDLE h=CreateFile(name,GENERIC_READ,FILE_SHARE_READ,NULL,
				OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL+FILE_FLAG_RANDOM_ACCESS,NULL);
//DeadCode DAW 01Nov99 				OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL+FILE_FLAG_NO_BUFFERING,NULL);

			if (cdfiles[fileindex].winhandle!=INVALID_HANDLE_VALUE)
				CloseHandle(cdfiles[fileindex].winhandle);

			cdfiles[fileindex].number=myfile;
			cdfiles[fileindex].winhandle=h;
			cdfiles[fileindex].maxfilesize=0x7FFFFFFF;	//51380224;
		}
	}
	cdfile->number = INVALIDFILENUM;
	cdfile->handle = NULL;
	cdfile->winhandle = INVALID_HANDLE_VALUE;
	cdfile->maxfilesize = 0;
	cdfile->currindex = 0;
	cdfile->actualindex = -1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseAreaFiles
//Author		Paul.   
//Date			Mon 18 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void fileman::CloseAreaFiles()
{
	int	fileindex;
	for (fileindex=0;fileindex<MAXCDFILEENTRIES;fileindex++)
	{
		if (cdfiles[fileindex].number!=INVALIDFILENUM)
		{
			CloseHandle(cdfiles[fileindex].winhandle);
			cdfiles[fileindex].number = INVALIDFILENUM;
			cdfiles[fileindex].handle = NULL;
			cdfiles[fileindex].winhandle = INVALID_HANDLE_VALUE;
			cdfiles[fileindex].maxfilesize = 0;
		}
	}
	cdfile->number = INVALIDFILENUM;
	cdfile->handle = NULL;
	cdfile->winhandle = INVALID_HANDLE_VALUE;
	cdfile->maxfilesize = 0;
	cdfile->currindex = 0;
	cdfile->actualindex = -1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		resetCDfile
//Author		Paul.   
//Date			Mon 18 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void fileman::resetCDfile(FileNum myfile)
{
	if (cdfile->number!=myfile)
	{
		//requested file is not the current one
		//make the requested file the current file

		for (int fileindex=0;;fileindex++)
		{
			if (fileindex==MAXCDFILEENTRIES)
				_Error.EmitSysErr("Requested CD file is not in the current area");

			if (cdfiles[fileindex].number==myfile)	break;
		}

		cdfile->number = cdfiles[fileindex].number;
		cdfile->handle = cdfiles[fileindex].handle;
		cdfile->winhandle = cdfiles[fileindex].winhandle;
		cdfile->maxfilesize = cdfiles[fileindex].maxfilesize;
	}
	cdfile->currindex = 0;
	cdfile->actualindex = -1;
	cdfile->seekingtoposition=0;									//DAW 19Dec96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		loadCDfile
//Author		Paul.   
//Date			Mon 18 Nov 1996
//
//Description	
//
//Inputs		myfile = CD landscape file number
//				length = length of block to load
//				offset = index into the file to load the block from
//				skipread = 	TRUE means do skip reads and waits (default)
//							FALSE means just load the block immediately	
//
//Returns	
//
//------------------------------------------------------------------------------
void* fileman::loadCDfile(FileNum myfile,SLong length,SLong offset,Bool skipread)
{
	if (length>ULong(readblockbufferbase+65536)-ULong(readblockbuffer))
		_asm {int 3}

	pingcount=0;
	void*	retval = NULL;

//	if ((offset+length)>cdfile->maxfilesize)
//	{
//		offset-=cdfile->maxfilesize;
//		skipread=FALSE;
//	}

	if (myfile!=cdfile->number || (skipread && cdfile->actualindex>offset))//PD 14Jun97
	{
		//not the current CD file - or gone past!!

		if (driveletter!=0)
		{
			resetCDfile(myfile);

			if (skipread==TRUE)
			{
				UWord	cmdstatus=CDSeek(offset);
				cdfile->currindex = offset;
				cdfile->actualindex = offset;
				cdfile->seekingtoposition = Save_Data.SeekingDelay;					//JIM 29May97
				return	(retval);
			}
		}
		else
			cdfile->actualindex = -1;
	}

	if (cdfile->seekingtoposition!=0)
	{
		cdfile->seekingtoposition--;
		return (retval);
	}

	if (skipread==FALSE)
	{
		retval = (void*)readblockbuffer;	//new unsigned char[length];
		if (retval==NULL)
			_Error.EmitSysErr("Failed to allocate memory for file load");
		CDseekreadfilepos(cdfile->winhandle,offset,retval,length);
		cdfile->currindex = cdfile->actualindex = offset+length;
		cdfile->seekingtoposition=0;
	}
	else
	{
		int	realindex = cdfile->currindex;

		if (realindex & 0x80000000)
		{
			//Currently processing an existing request for
			//a block of data

			realindex &= 0x7FFFFFFF;
			int	deltaseekpos;

			if (realindex!=offset)
			{
				//Abort the current seek and just load in
				//the block that has been requested

				deltaseekpos=0;
			}
			else
				deltaseekpos=realindex-cdfile->actualindex;

			if (deltaseekpos<=Save_Data.SeekStep)
			{
				retval = (void*)readblockbuffer;	//new unsigned char[length];
				if (retval==NULL)
					_Error.EmitSysErr("Failed to allocate memory for file load");
				CDseekreadfilepos(cdfile->winhandle,realindex,retval,length);
				cdfile->currindex = cdfile->actualindex = realindex;//JIM 30May97
				//it isn't actually, but nobody cares!
			}
			else
			{
				//Do the skip reads here

				cdfile->actualindex += Save_Data.SeekStep;
				retval = (void*)readblockbuffer;	//(void*)new unsigned char[2048];
				CDseekreadfilepos(cdfile->winhandle,cdfile->actualindex,retval,2048);
				//delete ((unsigned char *)retval);				//PD 13Jun97
				retval = NULL;									//PD 13Jun97
			}
		}
		else
		{
			//Start off a new seek request here!!

			cdfile->currindex = offset | 0x80000000;
//			if ((offset+length)>=cdfile->maxfilesize)
//				_Error.EmitSysErr("Seek past end of file");
			if (cdfile->actualindex==-1)	//New seek + new file
			{
				cdfile->actualindex = offset;
			}
		}
	}
	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pingCD
//Author		R. Hyde 
//Date			Tue 17 Dec 1996
//
//Description	Read 1 cd block and increment the current head position
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void fileman::pingCD()
{
	//Do the skip reads here

	if (cdfile->seekingtoposition)
		cdfile->seekingtoposition--;
	else
		if (pingcount++>=Save_Data.PingDelay)
			if (cdfile->actualindex<cdfile->maxfilesize)
			{
				pingcount=0;
				cdfile->actualindex += Save_Data.PingStep;
				char buffer[10];
				void*	retval = buffer;

				LARGE_INTEGER	t1;
				QueryPerformanceCounter(&t1);
				CDseekreadfilepos(cdfile->winhandle,cdfile->actualindex,retval,4);
				LARGE_INTEGER	t2;
				QueryPerformanceCounter(&t2);
				int t=t2.LowPart-t1.LowPart;
				t>>=4;
				if(t && QueryPerformanceFrequency(&t2))
				{
					t=t2.LowPart/t;				//this gives parts of 16 seconds
					if (t<12)		// 1+1/2 sec
						Save_Data.PingDelay--;
				}

			}
			else
			{
				cdfile->actualindex-=1024*1024;
				CDSeek(cdfile->actualindex);
 				cdfile->seekingtoposition = Save_Data.SeekingDelay;					//JIM 29May97
			}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CDseekreadfilepos
//Author		Paul.   
//Date			Thu 24 Sep 1998
//------------------------------------------------------------------------------
void	fileman::CDseekreadfilepos(HANDLE winhandle,int index,void* buffer,int sizecopy)
{
	static UWord	pos=0;

	int	size=(sizecopy+2047)&-2048;

	ULong retsize=0;
	SetFilePointer(winhandle,index,(SLongP)&retsize,FILE_BEGIN);
	retsize=GetLastError();
	ReadFile(winhandle,readblockbuffer,size,&retsize,NULL);
	retsize=GetLastError();
//DeadCode PD 08Oct98 	memcpy(buffer,readblockbuffer,sizecopy);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setcdsavedata
//Author		Paul.   
//Date			Fri 25 Sep 1998
//------------------------------------------------------------------------------
void fileman::setcdsavedata()
{
	//temp fix
	Save_Data.SeekStep=7*2*1024;
	Save_Data.PingStep=2*1024;
	Save_Data.PingDelay=13;
	Save_Data.SeekingDelay=300;
}

