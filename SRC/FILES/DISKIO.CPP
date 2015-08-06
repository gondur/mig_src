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
//Filename       diskio.cpp
//System         
//Author         Paul.   
//Date           Thu 6 Jul 1995
//Description    
//------------------------------------------------------------------------------

#define	InDiskIO	"Yes"

#include	<stdlib.h>
#include	<io.h>
#include	<dos.h>
#include	<fcntl.h>

#include	"DOSDefs.h"
#include	"DiskIO.H"
//DeadCode DAW 15Apr96 #include	"Screen.H"
//DeadCode DAW 19Mar96 #include	"GetSet.H"
#include	"myAngles.h"
#include	"Worldinc.h"
#include	"World.h"
#include	"Main.H"
#include 	"myError.h"

extern	Main	_Main;
extern 	Error	_Error;

DiskIO	_DiskIO;

//Old_Code DAW 15Nov95 const	char	*FileList[] =
//Old_Code DAW 15Nov95 	{
//Old_Code DAW 15Nov95 		#include	"MastFile.H"
//Old_Code DAW 15Nov95 	};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	DiskIO::LoadNumberedFile
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Thu 6 Jul 1995
//Modified	
//
//Description	Temporary version that just uses an equate to index into a list 
//			of filenames.
//
//Inputs		File number
//
//Returns	Address where file has been loaded
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
char *DiskIO::LoadNumberedFile(short FileNumber)
{
	int	handle;
	unsigned int	readlength;
	long	filesize;
	char	*buffer;

	if(_dos_open(FileList[FileNumber],O_RDONLY,&handle) !=0)
	{
		_Error.EmitSysErr(__FILE__":Can't open %s",FileList[FileNumber]);
	}

	if((filesize = filelength(handle))==-1)
	{
		_Error.EmitSysErr(__FILE__":Error getting length of %s",FileList[FileNumber]);
	}

	readlength = filesize;

	buffer = new char [readlength];

	if(_dos_read(handle,buffer,readlength,&readlength) !=0)
	{
		_Error.EmitSysErr(__FILE__":Error reading %s",FileList[FileNumber]);
	}

	if(_dos_close(handle) !=0)
	{
		_Error.EmitSysErr(__FILE__":Error closing %s",FileList[FileNumber]);
	}
	return(buffer);
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	DiskIO::SaveNumberedFile
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Thu 6 Jul 1995
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
void DiskIO::SaveNumberedFile(short FileNumber, char *Buffer, short FileLength)
{
	int	handle;
	unsigned int BytesWritten;

	if(_dos_creat(FileList[FileNumber],_A_NORMAL,&handle) !=0)
	{
		_Error.EmitSysErr(__FILE__":Can't open %s for output",FileList[FileNumber]);
	}

	if(_dos_write(handle,Buffer,FileLength,&BytesWritten) !=0)
	{
		_Error.EmitSysErr(__FILE__":Error writing %s",FileList[FileNumber]);
	}

	if(_dos_close(handle) !=0)
	{
	 	_Error.EmitSysErr(__FILE__":Error closing %s",FileList[FileNumber]);
	}
}

