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
//Filename       fileman.cpp
//System         
//Author         Jim Taylor
//Date           Tue 8 Aug 1995
//Description    File management module for new engine
//------------------------------------------------------------------------------
//
//	First pass is to produce a file access engine which can input a file number //RDH 28/04/99
//  and return a pointer to the loaded file.
//
//  In addition, a translation function should be provided which is run when the
//  file is loaded. For example, the shapes fix up certain procedure pointers.
//
//  Later these allocated data areas will be automatically treated as cache data.
//  Then, the fixup routine will only be called for the initial load.
//
//
//DeadCode JIM 02Jul96 #include	<assert.h>
#define		F_GRAFIX											//JIM 01Aug96

#include	"windows.h"
#include	"dosdefs.h"
#include	"hardpasm.h"
#include	"myerror.h"
#include 	<stdio.h>
#include    <string.h>
#include    <direct.h>
#include	"mymath.h"
#include	"fileman.h"
//#include	"myAngles.h"
#include	"worldinc.h"
#include	"world.h"
//#include	"main.h"
#include	"Mytime.h"
//#include	<new.h>
#include 	"imagemap.h"
#include	"Shapes.h"
#include	"lstream.h"
#include "monotxt.h"
#include "..\mfc\resource.h"
#ifndef __BCPLUSPLUS__
#include "CString.h"
#endif

#define _WINBASE_

#include "winfile.h"

#include	"stub3d.h"
//#include	"display.h"
#ifdef __MSVC__

//#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <Windows.h>         // MFC core and standard components
//#include <afxext.h>         // MFC extensions
//#include <afxdisp.h>        // MFC OLE automation classes
//#include <afxcmn.h>			// MFC support for Windows Common Controls

#include <WinBase.h>
#endif

UByte	stuffed=0;


extern Error _Error;
extern class MathLib	Math_Lib;								//PD 29Nov95
//
// Lets write some code!
//
//
//char	namedirdir[]="DIR.DIR";
char	namedirdir[256]={'D','I','R','.','D','I','R',0,	 		0,0,0,0,0,0,0,0,
						'R','O','O','T','S','.','D','I','R',	0,0,0,0,0,0,0};



int	(*fileman::MemFailPFU) (unsigned)=NULL;
int	interlocker=0;
#ifdef	__MSVC__	
//inline	int	LockExchange(int* loc,int newval=0)
//{
//	int rv;
//	_asm	{	mov		eax,newval
//				mov		ebx,loc
//				xchg	ds:[ebx],eax
//				mov		rv,eax
//			}
//	return	rv;
//}
#else
//inline	int	LockExchange(int* loc,int newval=0)
//{
//	return 0;
//}
#endif
FileMan	File_Man;

#ifndef	NDEBUG
	static int robtotalfilememused = 0;
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		fileman
//Author		Jim Taylor
//Date			Thu 28 Mar 1996
//
//Description	
//Basic constructor for fileman. Only caled once - what a waste!
//
//Inputs		
// 
//Returns	
//
//------------------------------------------------------------------------------
struct	CDOpenFile	
{int i;};
CON	fileman::fileman()
{
	currdirnum=RAMCACHEHANDLEDIR;
	currfilenum=INVALIDFILENUM;
	currfileblock=NULL;
	currfilesize=0;
	currfilehandle=NULL;
	nestcount=0;
	allfreedfiles=NULL;
//	pathname[83];
//	filenameindex=70;
	pathnameindex=0;
	pathnameptr=pathname;
	filrootblock=NULL;
	dirrootblock=NULL;
//	direntries[MAXDIRENTRIES];
//	makerootdirlist();
//DeadCode JIM 24Oct96 	makerootdirlist();
#ifdef	__MSVC__
	MemFailPFU=_set_new_handler(MyMemFailPFU);
#endif

	cdfiles=new CDOpenFile[MAXCDFILEENTRIES];
	cdfile=new CDCurrOpenFile;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		~fileman
//Author		Jim Taylor
//Date			Thu 28 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DES	fileman::~fileman()
{
#ifdef	__MSVC__
	MemFailPFU=_set_new_handler(MemFailPFU);
#endif
	delete []dirrootblock;
	fileblocklink::deletelink(0x7fffffff);
//TempCode PD 08Oct98 	ExitCDFS();
	delete[]cdfiles;
	delete cdfile;
}
//
//Temp garbage stuff
//
//
//
string	dupandrepointtxt(string&	srcandtrg)
{
string
	newtrg=new char [strlen(srcandtrg)+1];
	strcpy(newtrg,srcandtrg);
	return(srcandtrg=newtrg);
}

#define RUNTIME 200
void	fileman::fakedir(FileNum thisdir,char* dirname)
{
	strncpy((string)dirfakeblock+RUNTIME,dirname,50);
	direntries[dirnum(thisdir)].driverfile=RCH_DIRBASE;
	direntries[dirnum(thisdir)].parentdir=RAMCACHEHANDLEDIR;
	direntries[dirnum(thisdir)].dirnameind=(DirNameInd) RUNTIME;
	currdirnum=
		assumefakedir=255;
	fileblocklink::deletedirchain(thisdir);
}

FileNum	fileman::fakefile(FileNum thisdir,const char* filename)
{	//returns file number to use for fake (always dir+2 at present)
//DeadCode DAW 20Nov98 #pragma message ("fileman::fakefile - string copy causes memory overwrite")
	strncpy(namedirdir+128,filename,80);
	assumefakedir=dirnum(thisdir);
	fileblocklink::deletedirchain(thisdir);
	return FileNum((int)dirnum(dirnum(thisdir))+8);
}


//
//Clever constructor for first block of directory numbers
//
//Basically, it nobbles the system enough
//to test for the existance of .\ROOTS.DIR
//
//If that is found then it is loaded, otherwise, I stick with these paths.
//
//
void	nochange(void*	&,ULong&)	{};

void	fileman::makerootdirlist()
{
	assumefakedir=255;


//DeadCode JIM 21Sep95 char	here[]=".",
//DeadCode JIM 21Sep95 		exedir[80],
//DeadCode JIM 21Sep95 		cddir[80],
//DeadCode JIM 21Sep95 		paramdir[80];

static char	worker[250];
		dirfakeblock=worker;
//	First, find some hardware locations
const	HERE=0,EXE=2,CD=70,PARAM=135;
		worker[0]='.';worker[1]=0;
		Getexedirectory(&worker[EXE]);		//Directory containing executable
		GetCDdirectory(&worker[CD]);		//hardware CD drive location
		GetParamDir(&worker[PARAM]);		//Command-line parameter

//Now shoehorn them into the system
		direntries[0].driverfile=RCH_DIRBASE;
		direntries[0].parentdir=RAMCACHEHANDLEDIR;
		direntries[0].dirnameind=(DirNameInd) HERE;

		direntries[1].driverfile=RCH_DIRBASE;
		direntries[1].parentdir=RAMCACHEHANDLEDIR;
		direntries[1].dirnameind=(DirNameInd) EXE;

		direntries[2].driverfile=RCH_DIRBASE;
		direntries[2].parentdir=RAMCACHEHANDLEDIR;
		direntries[2].dirnameind=(DirNameInd) CD;

		direntries[3].driverfile=RCH_DIRBASE;
		direntries[3].parentdir=RAMCACHEHANDLEDIR;
		direntries[3].dirnameind=(DirNameInd) PARAM;

//Now, find a ROOT.DIR file and load it
		fileblockptr filrootblock=NULL;
		nestcount++;	//FORCES USE OF FAKE FILE-LIST
		if	(existnumberedfile(FIL_HEREROOTDIR))
			filrootblock=loaddirlist(FIL_HEREROOTDIR);
		else
		if	(	(worker[EXE])
			&&	(existnumberedfile(FIL_EXEROOTDIR)))
			filrootblock=loaddirlist(FIL_EXEROOTDIR);
		else
		if	(	(worker[CD])
			&&	(existnumberedfile(FIL_CDROMROOTDIR)))
			filrootblock=loaddirlist(FIL_CDROMROOTDIR);
		else
		if	(	(worker[PARAM])
			&&	(existnumberedfile(FIL_PARAMROOTDIR)))
			filrootblock=loaddirlist(FIL_PARAMROOTDIR);
		else
			_Error.ReallyEmitSysErr("Can't find ROOTS.DIR");
		nestcount--;	//FORCES LOADING OF REAL FILE_LIST

//fixy stuff:
		filrootblock->link->datasize=0;
		filrootblock->link->fileblockdata=NULL;
		dirrootblock=filrootblock->fileblockdata;								//JIM 01Apr96
		delete filrootblock;

//If the ROOT.DIR didn't effect these names then copy into static memory.
//already permanent. Just flag the illegal ones...

		if ((direntries[1].driverfile==RCH_DIRBASE)	&& (worker[EXE]==0))
			direntries[1].driverfile=INVALIDFILENUM;
		if ((direntries[2].driverfile==RCH_DIRBASE)	&& (worker[CD]==0))
			direntries[2].driverfile=INVALIDFILENUM;
		if ((direntries[3].driverfile==RCH_DIRBASE)	&& (worker[PARAM]==0))
			direntries[3].driverfile=INVALIDFILENUM;
}

void	fileman::Getexedirectory(string	exedir)
{
	exedir[0]=0;
}

void	fileman::GetCDdirectory(string	cddir)
{
//	CDSetup(cddir);												//PD 30Oct96
}

void	fileman::GetParamDir(string		paramdir)
{
	paramdir[0]=0;
}

//Defines link between res and directory names
//Load numbered file and process into direntries
//As each file is loaded, a number of 'sanity' checks are made:
//1) The parent directory number is already known
//2) A self reference means a dead end.
//		This is only allowed in ROOT.DIR;
//		The index must be less than 8.
//3) Any existing dir list entry should be cleaned up.
//		At present I dont know what this means.
//

//
// Convert the loaded file into entries in the dir list.
// Return a second data area to act as the cacheable image.
// First, the data is compressed into the existing buffer,
// and then it is copied to a new buffer.
//
//

void	fileman::translatedirlist(void*	&dataarea,ULong&	datalengthin)
{
//DeadCode JIM 07Sep95 ULong	outputpos=0;
string	datascan=	(string)dataarea,
		outptr=		(string)dataarea;
int		outind=0;
ULong	datalength=datalengthin;

dirindex	dirnum,parentnum;
ULong	mathret;
	while (	(*datascan<'0')	  ||	(*datascan>'9'))
	{
		datascan++;
		datalength--;
	}

//For every line in the file:
	while (datalength>0)
	{

//First read in the line:
		//get first number field
		mathret=Math_Lib.a2iend(datascan,datalength);
		if (mathret>255)
			_Error.EmitSysErr("Dir num %i too high!",mathret);
		dirnum=(dirindex) mathret;
		while (*datascan<=' ')
		{
			datascan++;
			datalength--;
		}
		//if second field is numeric then read that
		if ((*datascan<='9')&&(*datascan>='0'))
		{
			mathret=Math_Lib.a2iend(datascan,datalength);
			if (mathret>255)
				_Error.EmitSysErr("Dir num %i too high!",mathret);
			parentnum=(dirindex) mathret;
			if (parentnum==dirnum)
				parentnum=RAMCACHEHANDLEDIR;
			while (*datascan<=' ')
			{
				datascan++;
				datalength--;
			}
		}
		else
			parentnum=RAMCACHEHANDLEDIR;
		//copy the text field which is the directory name
int		pathstart=outind;
		if (datascan[0]=='"')
			do{
				outptr[outind++]=*++datascan;
				datalength--;
			}while (datascan[1]!='"');
		else
			while (*datascan>' ')
			{
				outptr[outind++]=*(datascan++);
				datalength--;
			}
		outptr[outind++]=0;
		//skip to end of line
		while (*datascan!='\n')
		{
			datascan++;
			datalength--;
		}
		//skip to useful data on next line, assuming we haven't run out!
		while (	(*datascan<'0') &&	(datalength>0))
		{
			datascan++;
			datalength--;
		}

//Ok.. now process the info collected.
//First perform sanity checks
		if (parentnum==RAMCACHEHANDLEDIR)
		{
			if (dirnum>16)
				_Error.EmitSysErr("Base directory over 16");
		} 
		else
		{
			if (FILEMAN.direntries[parentnum].driverfile==INVALIDFILENUM)
				_Error.EmitSysErr("parent directory number not yet loaded");
//TempCode DAW 17Jun96 			if (	(FILEMAN.direntries[dirnum].driverfile!=INVALIDFILENUM)
//TempCode DAW 17Jun96 				&&	(FILEMAN.direntries[dirnum].driverfile!=RCH_DIRBASE))
//TempCode DAW 17Jun96 				_Error.EmitSysErr("directory number reused. Multi-res not yet supported");
			if (	(outptr[pathstart]=='\\')
				||	(outptr[pathstart+1]==':'))
				_Error.EmitSysErr("Non-base directory starts with root path");

		}
//Now add fix for alias directories - modify pointer to NULL &!!DONT delete text DONT!!
		if 	(	(outptr[pathstart]=='.')  &&	(outptr[pathstart+1]==0))
		{
//DeadCode JIM 21Sep95 			outind=pathstart;
			pathstart=fileman::ALIASDIRIND;
		}

//Ok.. now lets insert the entry...
//Oops... my plan is to later move this data area!
//Ok.. the plan:
// Initially store in the dirlist with temp pointers, then move the data block,
// then scan the direntries for references to this file, and offset them to the new buffer!

		FILEMAN.direntries[dirnum].driverfile=FILEMAN.currfilenum;	//semi dirty
		FILEMAN.direntries[dirnum].dirnameind=(fileman::DirNameInd) pathstart;
		FILEMAN.direntries[dirnum].parentdir=parentnum;

//Thats it for this reading loop
	}


//At this point, we want to make a copy from dataarea to outptr
//For all the direntries referencing the .DIR file num 
//and not null name ptr then we can patch the name pointer
//Finally return a pointer to the new area in order to delete the old area.
//
//Well.. for now I am going to ignore that and keep hold of the existing area.
//This job must be finished properly, but this saves dev. time.

}
//////////////////////////////////////////////////////////
//
// ReTranslate must rebuild the binary image of the directory names
// but relies on the existing hooks in the direntries, so does not
// have to translate that info again, and is therefore shorter than
// the Translate function above, which will work in the same scenario.
//
//////////////////////////////////////////////////////////

void	retranslatedirlist(void*	&dataarea,ULong&	datalengthin)
{
//DeadCode JIM 07Sep95 ULong	outputpos=0;
string	datascan=	(char*)dataarea,
		outptr=		(char*)dataarea;
int		outind=0,
		datalength=datalengthin;

//DeadCode JIM 06Nov95 dirindex	dirnum;
//Skip leading garbage...
	while (	(*datascan<'0')	  ||	(*datascan>'9'))
	{
		datascan++;
		datalength--;
	}
//For every line in the file:
	while (datalength>0)
	{

//First read in the line:
		//get first number field
		while (	(*datascan>='0') &&	(*datascan<='9'))
		{
			datascan++;
			datalength--;
		}
		//find second
		while (	(*datascan<=' '))
		{
			datascan++;
			datalength--;
		}

		//if second field is numeric then read that
		if ((*datascan<='9')&&(*datascan>='0'))
		{
			while (	(*datascan>='0') &&	(*datascan<='9'))
			{
				datascan++;
				datalength--;
			}
			//find 3rd field
			while (*datascan<=' ')
			{
				datascan++;
				datalength--;
			}
		}
		//copy the text field which is the directory name
		if (datascan[0]=='"')
			do{
				outptr[outind++]=*++datascan;
				datalength--;
			}while (datascan[1]!='"');
		else
			while (*datascan>' ')
			{
				outptr[outind++]=*(datascan++);
				datalength--;
			}
		outptr[outind++]=0;
		//skip to end of line
		while (*datascan!='\n')
		{
			datascan++;
			datalength--;
		}
		//skip to useful data on next line, assuming we haven't run out!
		while (	(*datascan<'0') &&	(datalength>0))
		{
			datascan++;
			datalength--;
		}

//Ok.. now process the info collected.
//First perform sanity checks - not needed on reload
//Now add fix for alias directories - modify pointer to NULL & delete text
//DeadCode JIM 21Sep95 	This is difficult so I have stopped doing it ever!
//DeadCode JIM 21Sep95 		if 	(*((uword*) &outptr[outind-2])==*((uword*) "."))
//DeadCode JIM 21Sep95 			outind-=2;

//Thats it for this reading loop
		}


//At this point, we want to make a copy from dataarea to outptr
//For all the direntries referencing the .DIR file num 
//and not null name ptr then we can patch the name pointer
//Finally return a pointer to the new area in order to delete the old area.
//
//Well.. for now I am going to ignore that and keep hold of the existing area.
//This job must be finished properly, but this saves dev. time.

}


//////////////////////////////////////////////////////////
fileblockptr	fileman::loaddirlist(FileNum	filenum)
{
	return(new fileblock (filenum,translatedirlist));
}

//////////////////////////////////////////////////////////////////////
//	fileman::makedirectoryname(MyFile)
//
//	Ok.. this is an interesting recursion problem.
//	This proc fills in the pathname space in the header recursively
//	To do this it loads in additional files,
//  and makes additional directory names!
//  Of course, I hope these are cached, but no guarantees.
//	What I am going to do is build up the path in local string buffers
//	and then concatenate these.
//	The local buffers will only be 20 characters for recursion cases.
//	If we can guarantee each nesting is independent, and 8 chars, then this
//	20 can be reduced.
//	As the root path may be longer, this case will be dealt with
//	differently (yuck!)
//
//////////////////////////////////////////////////////////////////////
const	PATHSTEPCHARS	=	20;

void	fileman::makedirectoryname(dirindex	reqdir,int	pathend)
{
	//Optimisation: if we go for the same dirnum again, don't reload!
	if (reqdir!=currdirnum)
	{
		//If a nesting,
		//then
			//Allocate the directory patch
			//copy the name to a local buffer, and count the characters (add '\')
			//free patch
			//Recursively call makedirectoryname
			//copy local buffer to path space (add '\')
		//else
			//Assume memory never freed
			//count the characters
			//copy name to path space, (add '\')

		//If a nesting,
		if	(direntries[reqdir].parentdir!=RAMCACHEHANDLEDIR)
		//then
			//Extra test for 'alias' directories...
			if (direntries[reqdir].dirnameind!=ALIASDIRIND)		//PD 05Oct95
			{
				//Allocate the directory patch and fix up a pointer to the right text
char			tmpstr[PATHSTEPCHARS];
string			trgpos=tmpstr;
int				strsize=1;
				{
					if (direntries[reqdir].driverfile==INVALIDFILENUM)
						_Error.ReallyEmitSysErr("Directory %02x not known!",reqdir);


fileblock		fbp(direntries[reqdir].driverfile,retranslatedirlist,2048,0,false);
				//copy the name to a local buffer, and count the characters (add '\')
string			srcpos=&((string) getdata(fbp))[direntries[reqdir].dirnameind];
				{
					int	strsize=1;
					string	cmppos=srcpos;
					while (*(cmppos++))	strsize++;
					if (strsize>=PATHSTEPCHARS)
						_Error.EmitSysErr("Path step too big: (%s)> %i",
										srcpos,PATHSTEPCHARS);
				}

				while ((*(trgpos++)=*(srcpos++))!=0)	strsize++;
				//free patch
				//delete fbp;	//it is a local var!
				}
				//Recursively call makedirectoryname
				pathend=pathend-strsize;
				makedirectoryname(direntries[reqdir].parentdir,pathend);
				//copy local buffer to path space (add '\')
string			srcpos=tmpstr;
				trgpos=&pathname[pathend];
				while (--strsize!=0)	*(trgpos++)=*(srcpos++);
				*trgpos='\\';
			}
			else	 // 'alias' directory just recurse on but without stack size!
				makedirectoryname(direntries[reqdir].parentdir,pathend);
		else
		{	//Assume memory never freed
			//count the characters
fileblock	tmp((direntries[reqdir].driverfile==RCH_DIRBASE)
								?	dirfakeblock
								:	dirrootblock);

string		srcpos=&((string) getdata(tmp))[direntries[reqdir].dirnameind];
int			strsize=strlen(srcpos);
			//copy name to path space, (add '\' if required)
			if ((direntries[reqdir].dirnameind!=ALIASDIRIND))
			{													//DAW 03Oct96
				if (	(strsize!=0)		//(add '\' if required)
		   		&&(srcpos[strsize-1]!='\\')
		   		&&(srcpos[strsize-1]!=':')
		   		)
				{				// Backslash required
					pathnameindex=pathend-(strsize+1);
	string			trgpos=&pathname[pathnameindex];
					pathnameptr=trgpos;
					while (strsize--)	*(trgpos++)=*(srcpos++);
					*trgpos='\\';
				}
				else
				{				// Backslash not required
					pathnameindex=pathend-(strsize);
	string			trgpos=&pathname[pathnameindex];
					pathnameptr=trgpos;
					while (strsize--)	*(trgpos++)=*(srcpos++);
				}
			}
			else
			{
				pathnameindex=pathend;							//DAW 03Oct96
			 	pathnameptr=&pathname[pathnameindex];
			}
		}
		currdirnum=reqdir;	//Only at this point is the dir name known
	}
	else
	{
			//New Bits
string		srcpos=&pathname[pathnameindex];
int			strsize = filenameindex- pathnameindex;
			pathend-=strsize;
string		trgpos=pathnameptr=&pathname[pathend];
			pathnameindex=pathend;
			while (strsize--)	*(trgpos++)=*(srcpos++);
	}
}


//
// FileBlock conversion routine.
// This routine is able to convert a text format file-list
// into a binary format file-list. It will also be used in
// association with the file cache system to identify
// concatenated directories.
//
// I also later want support for 'missing' DIR.DIR files that are
// actually user-filled directories - like videos.
//
void	fixmanualdirnum(void*	&srcdata,ULong& srcsize)
{
string	srcchar=(string)	srcdata;
//If area is zero length then need to build list by wildcard
	assert 	((srcsize) && ("=0=wildcard - not implemented"));
//If first byte is zero then it is a concatenated directory
	//else
//Old_Code DAW 24Feb97 	assert	((srcchar[0])&&("=0=concatenated - not implemented"));
	if (srcchar[0]==0)			//Concatinated Dir.dir files
	{							//Don't do anything yet
////		INT3;
	}
//File-name is max. 12 characters.
//If loc'n 12 is non-zero then list is manually edited
	//else
	if	(srcchar[12])
	{
		//work to do to organize the file
		//1) count the entries
		//2) allocate a second buffer 16*entries
		//3) copy the entries
int		entries=0;
ULong	indexer=0;
		while (srcchar[indexer]<=' ')	indexer++;
		while (indexer<srcsize)
		{
			entries++;
			while 	(srcchar[indexer]>' ')	indexer++;
			while 	(	(srcchar[indexer]<=' ')
					 &&	(indexer<srcsize)
					)
				indexer++;
		}
		indexer=entries*16;

//Allocate: Temporary cheat.. not changing data areas
		assert((indexer<=srcsize)&&("Storing back at present!"));
string	outchar=srcchar;
void*		outstart=srcdata;

//Copy the entries
		indexer=0;
		while(entries--)
		{
			while (srcchar[indexer]<=' ')	indexer++;
int			count=16;
			while 	(srcchar[indexer]>' ')
			{
				*(outchar++)=srcchar[indexer++];
				count--;
			}
			while (count--)
				*(outchar++)=0;
		}
//DeadCode JIM 21Sep95 //Return the result
//DeadCode JIM 21Sep95 		return(outstart);
	}
//DeadCode JIM 21Sep95 	//else
//DeadCode JIM 21Sep95 	{
//DeadCode JIM 21Sep95 		return(srcdata);
//DeadCode JIM 21Sep95 	}
}

//////////////////////////////////////////////////////////////////////
// Load in the list of files for this directory
// Returns a fileblock.
//////////////////////////////////////////////////////////////////////
fileblockptr	fileman::readfilelist(dirindex	reqdir)
{
fileblockptr	dfblock;
//DeadCode JIM 21Sep95 dirindex
//DeadCode JIM 21Sep95 	reqdir= dirnum(MyFile);
	makedirectoryname(reqdir,filenameindex);
	//At this point I want to load 'dir.dir'
	//This would be:
	// new fileblock (deqdir<<DIRNUMSH,fixmanualdirnum,16*256,0)
	//The problem is that if this fails it will just come back here!
	//So, I need a test to force the first load.
	//I think this will be by checking the filenameslist ptr directly
	//
	//Ok.. so if the filenameslist is NOT DIR.DIR
	//We load it and fix it
	//Otherwise, we have the filename ready for recurse from default DIR.DIR
	if (nestcount==0 && reqdir!=assumefakedir)
		{
		nestcount++;
		dfblock=new fileblock
					(dirnum(reqdir),fixmanualdirnum,16L*256,0L,false);
		nestcount--;
		//Ok.. that should have loaded the dir file this time!
		}
	else
		dfblock=new fileblock (namedirdir);
	return (dfblock);
}

//////////////////////////////////////////////////////////////////////
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		namenumberedfile
//Author		JIM
//Date			fuck knows - Jim can't use ctrl-f-p because it hurts his fingers
//				DAW 25Feb97
//
//Description	return a string containing the name of the file
//
//Inputs
//
//Returns		filename or / if it is a concatinated dir.dir
//
//------------------------------------------------------------------------------
string	fileman::namenumberedfilelessfail(FileNum	MyFile)
{
    if (direntries[dirnum(MyFile)].driverfile==INVALIDFILENUM)
    	return NULL;
	int		fnum=((int)MyFile & (int)FILENUMMASK)<<4;
	fileblockptr	fbp=NULL;
	if (fnum==0)
	{
		makedirectoryname(dirnum(MyFile),filenameindex);
		fbp= new fileblock (namedirdir);
	}
	else
		fbp=readfilelist(dirnum(MyFile));
	fileblock fb=fbp;
	currfilenum=MyFile;
	string		dirlister=(string)	fb.getdata();

//DeadCode DAW 25Feb97 	INT3();
	if (dirlister[0]==0)										//DAW 25Feb97
		return("//");
	assert(  (dirlister[0]) && ("Not expecting concatenated directory here!") );
	assert(  (dirlister[12]==0)
		  &&("Not expecting hand built file-list here!")
		 );

	if (fb.getsize() && (fnum>fb.getsize()))
    {
    	pathname[filenameindex]=0;
    }
    else
    {
		((ULong*) (&pathname[filenameindex]))[0]=((ULong*) (&dirlister[fnum]))[0];
		((ULong*) (&pathname[filenameindex]))[1]=((ULong*) (&dirlister[fnum]))[1];
		((ULong*) (&pathname[filenameindex]))[2]=((ULong*) (&dirlister[fnum]))[2];
		((ULong*) (&pathname[filenameindex]))[3]=0L;
    }


	return	pathnameptr;

}

void fileman::flushcachedfiles()
{
	fileblocklink::deletelink(-1);
}

string	fileman::namenumberedfile(FileNum	MyFile)
{
	fileblock	fb=readfilelist(dirnum(MyFile));
	currfilenum=MyFile;
	string		dirlister=(string)	fb.getdata();

//DeadCode DAW 25Feb97 	INT3();
	if (dirlister[0]==0)										//DAW 25Feb97
		return("//");
	assert(  (dirlister[0]) && ("Not expecting concatenated directory here!") );
	assert(  (dirlister[12]==0)
		  &&("Not expecting hand built file-list here!")
		 );
	currfilenum=MyFile;

	int		fnum=((int)MyFile & (int)FILENUMMASK)<<4;

	if (fb.getsize() && (fnum>fb.getsize()))
		_Error.EmitSysErr("File number (%04X) past end of Dir.Dir file!",MyFile);
	if (dirnum(MyFile)==assumefakedir && (int(MyFile)&255)==8)
	{	//fake long file name potential
		memcpy(namedirdir+128-filenameindex,pathname,filenameindex);
		return	namedirdir+128-filenameindex+(pathnameptr-pathname);
	}
	else
	{
		((ULong*) (&pathname[filenameindex]))[0]=((ULong*) (&dirlister[fnum]))[0];
		((ULong*) (&pathname[filenameindex]))[1]=((ULong*) (&dirlister[fnum]))[1];
		((ULong*) (&pathname[filenameindex]))[2]=((ULong*) (&dirlister[fnum]))[2];
		((ULong*) (&pathname[filenameindex]))[3]=0L;
	//delete fb;

		if (errhandle)
		{
//DEADCODE DAW 28/03/99 		#ifdef	___MSVC__
//DEADCODE DAW 28/03/99 			fprintf(errhandle,"%d",Inst3d->timeofday);
//DEADCODE DAW 28/03/99 		#endif
			fputs(pathnameptr,errhandle);
			fputc('\n',errhandle);
		}

	
		return(pathnameptr);
	}
};

//////////////////////////////////////////////////////////////////////
FILE*	fileman::easyopennumberedfile(FileNum	MyFile)
{
string	name=namenumberedfile(MyFile);
		FILE* rv=fopen(name,"rb");
		return(rv);
			
}
bool	BLOCKCHILD=false;
//////////////////////////////////////////////////////////////////////
FILE*	fileman::opennumberedfile(FileNum	MyFile)
{
FILE*	retval=easyopennumberedfile(MyFile);
	while (!retval)
	{
    #ifdef __MSVC__
    	CString string;
		char* n=pathnameptr;
		char buffer[80];
		strcpy(buffer,pathnameptr);
//DeadCode AMM 09Jul99 		int level=LockExchange(&interlocker,0);
		char* fname=buffer;									  //JIM 21/12/98
		if (dirnum(MyFile)==assumefakedir && (MyFile&255)==8)		  //JIM 21/12/98
			fname=namedirdir+128-filenameindex+(pathnameptr-pathname); //JIM 21/12/98

//DEADCODE RDH 20/05/99 		if(MessageBox(Master_3d.winst,"Please insert correct media for above file",fname,MB_RETRYCANCEL)
//DEADCODE RDH 20/05/99 			==IDCANCEL)
		BLOCKCHILD=true;
		string.LoadString(IDS_INSERTCD);
//			HWND upperwnd=HWND_BOTTOM;  
//			::SetWindowPos(m_hWnd,upperwnd,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);

		if(MessageBox(NULL,string,fname,MB_RETRYCANCEL|MB_SYSTEMMODAL|MB_TOPMOST|MB_SETFOREGROUND|MB_ICONHAND)
			==IDCANCEL)
		{
				string.LoadString(IDS_FILENOTEXIST);

				_Error.ReallyEmitSysErr(string,
							 MyFile,pathnameptr);
		}
//DeadCode AMM 09Jul99 		while (LockExchange(&interlocker,1))
//DeadCode AMM 09Jul99 		{Sleep(0);}
		pathnameptr=n;
		strcpy(pathnameptr,buffer);
    #else
				_Error.ReallyEmitSysErr("File not found: %04x=%s",
							 MyFile,pathnameptr);

	#endif
		BLOCKCHILD=false;
		retval=easyopennumberedfile(MyFile);
		if (retval)
			InvalidateRect(NULL,NULL,NULL);
	}
		return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsConcatinatedFile
//Author		Dave Whiteside
//Date			Tue 25 Feb 1997
//
//Description	Returns TRUE is the file is part of a concatinated dir.dir
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	fileman::IsConcatinatedFile(FileNum	MyFile)
{
	Bool	retval=FALSE;
//	if (!strcmp(namenumberedfile(MyFile),"//"))
  //		retval=TRUE;
	return(retval);
}

//////////////////////////////////////////////////////////////////////
Bool	fileman::existnumberedfile(FileNum	MyFile)
{
	for (fileblocklink	**search=&FILEMAN.direntries[dirnum(MyFile)].freedfiles;
		*search;
		search=&search _->dir.next
		)
		if (search _->filenum==MyFile)
			return TRUE;
		string	name=namenumberedfilelessfail(MyFile);
		if (name==NULL || name[0]==0 || name[1]==0)
			return(FALSE);
		//else
			FILE* retval=fopen(name,"rb");
		if (retval==NULL)
			return(FALSE);
		//else
			closefile(retval);
			return(TRUE);
}

//////////////////////////////////////////////////////////////////////
ULong	fileman::getfilesize(FILE*	filehandle)
{
ULong 	oldpos=(ULong)	ftell(filehandle);
		fseek(filehandle,0,SEEK_END);
ULong 	returnval=(ULong)	ftell(filehandle);
		fseek(filehandle,oldpos,SEEK_SET);
		return(returnval);
//Old_Code PD 19Sep96 		DPMIregs	regs;
//Old_Code PD 19Sep96 
//Old_Code PD 19Sep96 		regs.w.ax=0x4201;
//Old_Code PD 19Sep96 		regs.w.bx=filehandle->_handle;
//Old_Code PD 19Sep96 		regs.w.cx=0;
//Old_Code PD 19Sep96 		regs.w.dx=0;
//Old_Code PD 19Sep96 		ASM_DOSvia31(0x21,&regs);
//Old_Code PD 19Sep96 ULong	oldposl=regs.w.ax;
//Old_Code PD 19Sep96 ULong	oldposh=regs.w.dx;
//Old_Code PD 19Sep96 		regs.w.ax=0x4202;
//Old_Code PD 19Sep96 		regs.w.bx=filehandle->_handle;
//Old_Code PD 19Sep96 		regs.w.cx=0;
//Old_Code PD 19Sep96 		regs.w.dx=0;
//Old_Code PD 19Sep96 		ASM_DOSvia31(0x21,&regs);
//Old_Code PD 19Sep96 ULong	returnval=regs.w.ax+(regs.w.dx<<16);
//Old_Code PD 19Sep96 		regs.w.ax=0x4200;
//Old_Code PD 19Sep96 		regs.w.bx=filehandle->_handle;
//Old_Code PD 19Sep96 		regs.w.cx=oldposh;
//Old_Code PD 19Sep96 		regs.w.dx=oldposl;
//Old_Code PD 19Sep96 		ASM_DOSvia31(0x21,&regs);
//Old_Code PD 19Sep96 		return(returnval);
};
//////////////////////////////////////////////////////////////////////
ULong	fileman::seekfilepos(FILE*	filehandle,ULong	offset)
{
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'(';
	fseek(filehandle,offset,SEEK_SET);
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+')';
	return((ULong) ftell(filehandle));
//Old_Code PD 19Sep96 		DPMIregs	regs;
//Old_Code PD 19Sep96 
//Old_Code PD 19Sep96 		regs.w.ax=0x4200;
//Old_Code PD 19Sep96 		regs.w.bx=filehandle->_handle;
//Old_Code PD 19Sep96 		regs.w.cx=offset >>16;
//Old_Code PD 19Sep96 		regs.w.dx=offset;
//Old_Code PD 19Sep96 		ASM_DOSvia31(0x21,&regs);
//Old_Code PD 19Sep96 ULong	returnval=regs.w.ax+(regs.w.dx<<16);
//Old_Code PD 19Sep96 		return(returnval);
};
//////////////////////////////////////////////////////////////////////
ULong	fileman::readfileblock(
				FILE*	filehandle,		//Opened using an open function
				void*	fileblockdata,	//data area to fill
				ULong	datasize		//ammount to load
						)			//returns ammount actually loaded
{
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'[';
	ULong rv=(fread(fileblockdata,1,datasize,filehandle));
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+']';

	return rv;
}
//////////////////////////////////////////////////////////////////////
void	fileman::closefile(FILE*	filehandle)
{
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'{';
	fclose(filehandle);	
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'}';

}

static	Bool	gotnewfix=FALSE;
//DeadCode DAW 16Dec96 
//DeadCode DAW 16Dec96 Moved to loadlist.cpp
//DeadCode DAW 16Dec96 
//DeadCode DAW 16Dec96 

//DeadCode DAW 16Dec96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 16Dec96 //Procedure		preload
//DeadCode DAW 16Dec96 //Author		Robert Slater
//DeadCode DAW 16Dec96 //Date			Mon 2 Dec 1996
//DeadCode DAW 16Dec96 //
//DeadCode DAW 16Dec96 //Description	
//DeadCode DAW 16Dec96 //
//DeadCode DAW 16Dec96 //Inputs		
//DeadCode DAW 16Dec96 //
//DeadCode DAW 16Dec96 //Returns	
//DeadCode DAW 16Dec96 //
//DeadCode DAW 16Dec96 //------------------------------------------------------------------------------
//DeadCode DAW 16Dec96 void	fileman::preload()
//DeadCode DAW 16Dec96 {
//DeadCode DAW 16Dec96 	fileblock	pl(FIL_PRELOAD_LIST);
//DeadCode DAW 16Dec96 	char* t=(char*)getdata(pl);
//DeadCode DAW 16Dec96 	FileNum f;
//DeadCode DAW 16Dec96 	while (*t<'0')	t++;
//DeadCode DAW 16Dec96 	f=(FileNum)Math_Lib.a2iend(t);
//DeadCode DAW 16Dec96 	while(f)
//DeadCode DAW 16Dec96 		if (dirnum(f)==dirnum(FIL_SUN_NUM))
//DeadCode DAW 16Dec96 		{
//DeadCode DAW 16Dec96 
//DeadCode DAW 16Dec96 			fileblock z(f,shapestuff::FixupShapeFile);
//DeadCode DAW 16Dec96 			while (*t<'0')	t++;
//DeadCode DAW 16Dec96 			f=(FileNum)Math_Lib.a2iend(t);
//DeadCode DAW 16Dec96 		}
//DeadCode DAW 16Dec96 		else
//DeadCode DAW 16Dec96 		{
//DeadCode DAW 16Dec96 			if (dirnum(f)==dirnum(FIL_MUSIC_BASE))				//JIM 15Dec96
//DeadCode DAW 16Dec96 				f=(FileNum)(f+_Miles.MusicDir);					//JIM 15Dec96
//DeadCode DAW 16Dec96 			fileblock z(f);
//DeadCode DAW 16Dec96 			while (*t<'0')	t++;
//DeadCode DAW 16Dec96 			f=(FileNum)Math_Lib.a2iend(t);
//DeadCode DAW 16Dec96 		}
//DeadCode DAW 16Dec96 
//DeadCode DAW 16Dec96 }
//DeadCode DAW 16Dec96 

#ifdef __WATCOMC__
	extern	SLong eip();
	#pragma aux eip="call next" "next: pop eax" value [eax]
#else
#ifdef __MSVC__
inline SLong eip()
{
	SLong	retval;
    __asm
    {
		call next;
		next: pop eax;
		mov retval,eax;
    }
    return retval;
}

#endif
#endif
#ifdef __WATCOMC__
	extern	SLong* esp();
	#pragma aux esp="mov eax,esp" value [eax]
#else
#ifdef __MSVC__
inline SLong* esp()
{
	SLong*	retval;
    __asm
    {
		mov eax,esp;
		mov retval,eax;
    }
    return retval;
}

#endif
#endif
//
// Implementation for the fileblock task next!
//
// Constructors:
//


//	This constructor syntax is used to load a file
//	defining a call-back function:
//	The NEW overload for
//
void	fileblock::makefileblock
		(FileNum	MyFile,		//R	//file number (if dir=-1 then no file)
		filetrans*	MyTrans,	//O	//translation routine if area reallocated
		ULong	blocksize,		//O	//max size to load/translate
		ULong	offset,			//O	//offset into file
		bool	processlock)	//X //process locking always enabled externally
{

FILE*	filehandle;
	link=NULL;
	fileblockdata=NULL;
	if (BLOCKCHILD) //RDH 08/07/99
		return; //RDH 08/07/99

	if (processlock)
	{
//		(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'M';
		while(LockExchange(&interlocker,1))
			Sleep(20);
	}

	if ((fileblockdata=link->makelink(MyFile,offset,blocksize,link))==NULL)
	{
		dirindex di=dirnum(MyFile);

		if (di==RAMCACHEHANDLEDIR)
		{
			if (processlock)
			{
//				(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'m';
				LockExchange(&interlocker,0);
			}
			link->datasize=blocksize;
			assert(blocksize&&"Must provide data size for RAMBUFFER");
			assert(MyTrans&&"Must provide translate fn for RAMBUFFER");
			FILEMAN.MakeRoomFor(blocksize);
			fileblockdata = new voidbigblock [blocksize];
		}
		else
		{
			if (FILEMAN.direntries[di].openfile.number==MyFile)
			{
				if (processlock)
				{
//					(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'m';
					LockExchange(&interlocker,0);
				}
				filehandle=FILEMAN.direntries[di].openfile.handle;
				link->datasize=blocksize;
				FILEMAN.seekfilepos(filehandle,offset);
				FILEMAN.direntries[di].openfile.currfileindex=offset+blocksize;
				assert(FILEMAN.direntries[di].openfile.currfileindex<=FILEMAN.direntries[di].openfile.maxfilesize);
			}
			else
			{
				if (FILEMAN.IsConcatinatedFile(MyFile)==TRUE)
				{
				   filehandle=NULL;
#ifdef __WATCOMC__
	INT3();
#endif
#ifdef __MSVC__
	INT3;
#endif
				}
				else
				{
					filehandle=	FILEMAN.fileman::opennumberedfile(MyFile);
					if (processlock)
					{
//						(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'m';
						LockExchange(&interlocker,0);
					}
					FILEMAN.fileloadedthisframe=TRUE;
					link->datasize=		FILEMAN.getfilesize(filehandle);
					if (!link->datasize)
						filehandle=filehandle;
					if (!blocksize)
						filehandle=filehandle;

					if (link->datasize>blocksize)
					{
						if (FILEMAN.direntries[di].openfile.number!=INVALIDFILENUM)
							FILEMAN.closefile(FILEMAN.direntries[di].openfile.handle);
						FILEMAN.direntries[di].openfile.number=MyFile;
						FILEMAN.direntries[di].openfile.handle=filehandle;
						FILEMAN.direntries[di].openfile.maxfilesize=link->datasize;
						FILEMAN.direntries[di].openfile.currfileindex=offset+blocksize;
	
						if (offset>link->datasize)
							_Error.EmitSysErr("Index past end of file");
						link->datasize=blocksize;
						if (!link->datasize)
							filehandle=filehandle;
						if (offset)
								FILEMAN.seekfilepos(filehandle,offset);
					}
					else
						assert((offset==0)&&"Can only use offset if buffer smaller than file!");
				}
			}
            #if	defined(__WATCOMC__) || defined (__MSVC__)
			#ifndef NDEBUG
			SLong b4=eip();

		    if (link->datasize==259)
				b4=b4;
			#endif
            #endif
			FILEMAN.MakeRoomFor(blocksize);
#ifdef DEBUG_NEW_MODE
	#undef new
	#define	new new(__HERE__,MyFile)
#endif
			if ((fileblockdata = new voidbigblock [link->datasize])==NULL)
				_Error.EmitSysErr("Failed to allocate memory for file load "
									"(file %x, size %d)",
									MyFile,link->datasize);
#ifdef	DEBUG_NEW_MODE
	#undef new
	#define new DEBUG_NEW
#endif
            #if	defined(__WATCOMC__) || defined (__MSVC__)
			#ifndef NDEBUG
			SLong ft=eip();
			if (	*((SLong*)fileblockdata-3) >=b4
				&&	*((SLong*)fileblockdata-3) <=ft
				)
			{
				*((SLong*)fileblockdata-3)=esp()[18];
				gotnewfix=TRUE;
			}
			#endif
            #endif
			if (!FILEMAN.readfileblock(filehandle,fileblockdata,link->datasize))
				filehandle=filehandle;
			if (FILEMAN.direntries[di].openfile.number!=MyFile)
				FILEMAN.closefile(filehandle);
		}


	//TempCode JIM 01Apr96 	nextinfile=NULL;
	//TempCode JIM 01Apr96 	heapmanagelink=NULL;
		if (MyTrans)
			{
			voidbigblock*	oldfbd=(voidbigblock*) fileblockdata;
			ULong	oldds=link->datasize;
			MyTrans(fileblockdata,link->datasize);
			if (oldfbd!=(voidbigblock*) fileblockdata)
			{
				FILEMAN.MakeRoomFor(-int(oldds));
				delete [] oldfbd;
			}
			}
		link->fileblockdata=fileblockdata;
	}
	else
		if (processlock)
		{
//			(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'m';
			LockExchange(&interlocker,0);
		}
#ifndef	NDEBUG
	if (link)
		robtotalfilememused += link->datasize;
#endif
}
////////////////////////////////////////////////////////
//	I sometimes need to make a block of data look like a fileblock
//  This is really a casting, rather than a constructor.
//	The memory manager shaould have some way of knowing that the
//	associated data is not available for cacheing.
//	This will be because the size is zero.
//
////////////////////////////////////////////////////////
	fileblock::fileblock(void*	dataarea)
{
	link=NULL;
	fileblockdata=dataarea;
}

//	fileblock::fileblock(fileblock& srcblock)
//{
//	filenum=srcblock.filenum;
//	filehandle=srcblock.filehandle;
//	fileoffset=srcblock.fileoffset;
//	datasize=srcblock.datasize;
//	fileblockdata=srcblock.fileblockdata;
//	nextinfile=NULL;
//	heapmanagelink=NULL;
//}

	fileblock::fileblock(const fileblockptr srcblockptr)
{
	link=srcblockptr->link;
	srcblockptr->link=NULL;
	fileblockdata=srcblockptr->fileblockdata;
	srcblockptr->fileblockdata=NULL;
	delete srcblockptr;
}

//	fileblock::fileblock(fileblockptr& srcblockptr)
//{
//	filenum=srcblockptr->filenum;
//	filehandle=srcblockptr->filehandle;
//	fileoffset=srcblockptr->fileoffset;
//	datasize=srcblockptr->datasize;
//	fileblockdata=srcblockptr->fileblockdata;
//	nextinfile=NULL;
//	heapmanagelink=NULL;
//	srcblockptr=this;
//}

////////////////////////////////////////////////////////
//
// Don't delete the data block if the data size is a zero,
// adn while we're there lets check the pointer.
//
////////////////////////////////////////////////////////
	fileblock::~fileblock()
{
	if (link)
		link->breaklink();	//this does all the work now!

//DeadCode JIM 01Apr96 	if ((fileblockdata)&&(datasize))
	{
//TempCode JIM 29Mar96 		dirindex reqdir=dirnum(filenum);
//TempCode JIM 29Mar96 		//find in old list
//TempCode JIM 29Mar96 		fileblockptr *search=&FILEMAN.direntries[reqdir].openfiles;
//TempCode JIM 29Mar96 		while (*search)
//TempCode JIM 29Mar96 		{
//TempCode JIM 29Mar96 			breakif(search[0]->nextindir==this);
//TempCode JIM 29Mar96 			search=&search[0]->nextindir;
//TempCode JIM 29Mar96 		}
//TempCode JIM 29Mar96 //		assert(search&&"deleted unknown area???!!!");
//TempCode JIM 29Mar96 		search[0]->nextindir=nextindir;
//TempCode JIM 29Mar96 
//TempCode JIM 29Mar96 		search=&FILEMAN.direntries[reqdir].freedfiles;
//TempCode JIM 29Mar96 		while (*search)
//TempCode JIM 29Mar96 		{
//TempCode JIM 29Mar96 			breakif(search[0]->filenum&FILENUMMASK>=filenum&FILENUMMASK);
//TempCode JIM 29Mar96 			search=&search[0]->nextindir;
//TempCode JIM 29Mar96 		}
//TempCode JIM 29Mar96 		fileblockptr newfb=new fileblock (*this);
//TempCode JIM 29Mar96 		newfb->nextindir=search;
//TempCode JIM 29Mar96 		search = newfb;

//DeadCode JIM 01Apr96 		delete []	(voidbigblock*)	fileblockdata;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		loadednumberedfile
//Author		Jim Taylor
//Date			Mon 30 Sep 1996
//
//Description	Is this file already loaded?
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	fileman::loadednumberedfile(FileNum filenum,int offset)
{
int	filehandle=-1;
dirindex reqdir=dirnum(filenum);
fileblocklink	**search=&direntries[reqdir].freedfiles;
fileblocklink	*s2;
	while (*search)
	{
		if (search _->filenum==filenum)
			if (search _->fileoffset==offset)
				return(TRUE);
		search=&search _->dir.next;
	}
	return	FALSE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		makelink
//Author		Jim Taylor
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void*	fileblocklink::makelink(FileNum filenum,ULong fileoffset,ULong size,fileblocklink*&link)
{
int	filehandle=-1;
dirindex reqdir=dirnum(filenum);
fileblocklink	**search=&FILEMAN.direntries[reqdir].freedfiles;
fileblocklink	*s2;
	while (*search)
	{
		if (search _->filenum==filenum)
			if (search _->fileoffset==fileoffset)
			{	//as good as found a match if not asked for all.
				assert(	(fileoffset==0 || search _->datasize==size)
						&&"Indexed part of file with different size!");
				link=s2=*search;
				//remove from free list, 
				fileblocklink **tmp = &FILEMAN.allfreedfiles;
				s2->dir.remove(s2);
				s2->heap.remove(s2);
				//insert in active lists
				s2->dir.insert(s2,FILEMAN.direntries[reqdir].openfiles);
				s2->heap.insert(s2,FILEMAN.allactivefiles);
				#ifndef NDEBUG
					if (gotnewfix)
						*((ULong*)s2->fileblockdata-3)&=0x0fffffff;
				#endif
				return(s2->fileblockdata);
			}
			else
			{
				filehandle=search _->filehandle;
			}
		search=&search _->dir.next;
	}
	s2=FILEMAN.direntries[reqdir].openfiles;
	while (s2)
	{
		if (s2->filenum==filenum)
			_Error.ReallyEmitSysErr("Opened file block (%x) again without closing!",filenum);
		s2=s2->dir.next;
	}
#ifdef DEBUG_NEW_MODE
	#undef new
	#define	new new(__HERE__,filenum)
#endif
	link=s2=new fileblocklink;
#ifdef DEBUG_NEW_MODE
	#undef new
	#define	new DEBUG_NEW
#endif
	link->filenum=filenum;
	link->fileoffset=fileoffset;
	link->fileblockdata=NULL;
	link->filehandle=filehandle;
	//insert in active lists
	s2->dir.insert(s2,FILEMAN.direntries[reqdir].openfiles);
	s2->heap.insert(s2,FILEMAN.allactivefiles);
	return(NULL);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		breaklink
//Author		Jim Taylor
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	fileblocklink::breaklink()
{
	if (this)
	{	//flexibility are us
		//remove from open list
		dir.remove(this);
		heap.remove(this);

		if (fileblockdata)
		{
			#ifndef NDEBUG
				if (gotnewfix)
					*((ULong*)fileblockdata-3)|=0x80000000;
			#endif
			//insert in freed lists:
			//First, the directory list:
			fileblocklink	**search=&FILEMAN.direntries[dirnum(filenum)].freedfiles;
			while (*search && search _->filenum<=filenum)
				search=& search _->dir.next;
			dir.insert(this,*search);

			//Next, the full list
			fileblocklink **tmp = &FILEMAN.allfreedfiles;
			search = & FILEMAN.allfreedfiles;
			while (*search && search _->datasize<=datasize+500)
				search=& search _->heap.next;
			heap.insert(this,*search);
			return(TRUE);
		}
		elser
			delete this;
	}
	return(FALSE);
}

void	fileblocklink::deletedirchain(FileNum fnum)
{
dirindex reqdir=dirnum(fnum);
fileblocklink	*s2;
fileblocklink	*search=FILEMAN.direntries[reqdir].freedfiles;
	while (search)
	{
		s2=search;
		s2->dir.remove(s2);
		s2->heap.remove(s2);
		delete [] (voidbigblock*) s2->fileblockdata;
		FILEMAN.MakeRoomFor(-int(s2->datasize));
		delete s2;
		search=FILEMAN.direntries[reqdir].freedfiles;
	};
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		deletelink
//Author		Jim Taylor
//Date			Mon 1 Apr 1996
//
//Description	Actually throw it away... how sad!
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	fileblocklink::deletelink(ULong size)
{
	//find a bigger link to free
	fileblocklink	*s2 = FILEMAN.allfreedfiles;
		while (s2 && s2->datasize<size)
			s2=s2->heap.next;

	if (s2)
	{	//delete the one bigger element
		//remove from freed list
		s2->dir.remove(s2);
		s2->heap.remove(s2);
		//do something with file handles
		delete [] (voidbigblock*) s2->fileblockdata;
		delete s2;
		return(TRUE);
	}

//TempCode PD 16Jan98 	if (LandStream.DeleteDisplayCache(TRUE))									//PD 01Aug96
//TempCode PD 16Jan98 		return(TRUE);

	if (!FILEMAN.allfreedfiles)
	{
		SHAPESTUFF.UnLoadRequiredShapes();
	}

	if (!FILEMAN.allfreedfiles)
	{
 		Image_Map.UnLoadImageMapPtrs();								//PD 29Nov95
	}
	if (FILEMAN.allfreedfiles)
	{	//delete all the held memory
		s2 = FILEMAN.allfreedfiles;								//JIM 10Apr96
		while (s2)
		{
			s2->dir.remove(s2);									//JIM 10Apr96
//DeadCode JIM 10Apr96 			s2->heap.remove(s2);			//JIM 10Apr96
 			FILEMAN.allfreedfiles=s2->heap.next;
			//do something with file handles
			delete [] (voidbigblock*) s2->fileblockdata;
			delete s2;
			s2=FILEMAN.allfreedfiles;
		}
		return(TRUE);
	}
	elser	//bugger! really run out now!
		return(FALSE);
}
void	fileman::MakeRoomFor(int delta)
{
	if (totalfilesysmemused>totalfilesysmem)
    	totalfilesysmemused+=delta;
    else
    {
    	totalfilesysmemused+=delta;
	    #ifndef	__BCPLUSPLUS__
		if (totalfilesysmemused>totalfilesysmem)
			if (totalfilesysmem==5000000)
				fileblocklink::deletelink(totalfilesysmem);
			else
				fileblocklink::deletelink(delta);
	    #endif
    }
}
////////////////////////////////////////////////////////
//DeadCode JIM 21Sep95 ULong	fileblock::getsize()
//DeadCode JIM 21Sep95 	{return(datasize);}
//DeadCode JIM 21Sep95 
//DeadCode JIM 21Sep95 ////////////////////////////////////////////////////////
//DeadCode JIM 21Sep95 void*	fileblock::getdata()
//DeadCode JIM 21Sep95 	{return(fileblockdata);}

////////////////////////////////////////////////////////
	fileman::dirfileentry::dirfileentry()
{
	driverfile=INVALIDFILENUM;
	freedfiles=NULL;
	openfiles=NULL;

}

////////////////////////////////////////////////////////////

//TempCode JIM 03Oct95 	JimTests()
//TempCode JIM 03Oct95 {
//TempCode JIM 03Oct95 //fileman	FILEMAN;
//TempCode JIM 03Oct95 	delete 		FILEMAN.loaddirlist(FIL_COMMONDIRLIST);
//TempCode JIM 03Oct95 	fileblock fb2(FIL_DEEPJUNK);
//TempCode JIM 03Oct95  	((string)getdata(fb2))[getsize(fb2)-1]=0;
//TempCode JIM 03Oct95 	_Error.EmitSysErr((string)getdata(fb2));
//TempCode JIM 03Oct95 }


//
//	Memory management interface...
//	The plan is that the file system caches every file load, but
//	deletes cached files if memory runs out.
//	First, I need to pick up that the memory has run out...
//
//


Bool	fileman::quitonfailalloc=TRUE;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MyMemFailPFU
//Author		Jim Taylor
//Date			Thu 28 Mar 1996
//
//Description	System callback if alloc can't be made
//				Return TRUE if alloc attempt should be repeated
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	fileman::MyMemFailPFU(unsigned s)
{
	if (MemFailPFU)	 	//Perhaps the previous handler has some memory to give?
		if (MemFailPFU(s))
			return(TRUE);

//	_asm { int 3 }

	if (fileblocklink::deletelink(s))
		return(TRUE);
	if (quitonfailalloc)
		_Error.ReallyEmitSysErr("Memory request failed for %ibytes (%2iM%4iK%4iB)",
			s,s/(1024*1024),(s/1024)%1024,s%1024);
	return(FALSE);
}

//TempCode JIM 01Apr96 Bool	fileman::FreeMemory(unsigned s)
//TempCode JIM 01Apr96 {
//TempCode JIM 01Apr96 
//TempCode JIM 01Apr96 
//TempCode JIM 01Apr96 }



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dirlist constructor
//Author		Jim Taylor
//Date			Mon 12 Aug 1996
//
//Description	variants for using file system or using raw pathname.
//				wildcard is optional. *.* assumed.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON	dirlist::dirlist(FileNum d):
	dirnum(d)
{
	ownfilelist=FALSE;
	pathname=NULL;
//	FILEMAN.makedirectoryname(::dirnum(d),FILEMAN.filenameindex);
//	FILEMAN.pathname[FILEMAN.filenameindex]=0;

//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'D';
	while(LockExchange(&interlocker,1))
		Sleep(20);
	makedirlist(FILEMAN.makedirectoryname(::dirnum(d)),"*.*");
	LockExchange(&interlocker,0);	//NOT GOOD ENOUGH!!!
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'d';
}

CON	dirlist::dirlist(FileNum d,char* w):
	dirnum(d)
{
	pathname=NULL;
	ownfilelist=FALSE;
//	FILEMAN.makedirectoryname(::dirnum(d),FILEMAN.filenameindex);
//	FILEMAN.pathname[FILEMAN.filenameindex]=0;

//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'L';
	while(LockExchange(&interlocker,1))
		Sleep(20);
	makedirlist(FILEMAN.makedirectoryname(::dirnum(d)),w);
	LockExchange(&interlocker,0);	//NOT GOOD ENOUGH!!!
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'l';
}

CON	dirlist::dirlist(char* d,char* w):
	dirnum(INVALIDFILENUM)
{
	pathname=NULL;
	ownfilelist=FALSE;
	makedirlist(d,w);
}


void	dirlist::makedirlist(char* p,char* w)
{

	pathlen=strlen(p);
	pathname=new char [pathlen+(int)FNAMESIZE+2];

	wildname=w;
	ownfilelist=TRUE;
	w=pathname;
	if (*p)
	{
		while (*p) *w++=*p++;
		if (*(p-1)!='\\')
		{
			*w++='\\';
			pathlen++;
		}
	}
	p=wildname;
	while ((*w++=*p++)!=0);
	//allpath is dir name
	char*	tmpflist= new char [FNAMESIZE*MAXFLIST];
	int i=0;
	p=wildname;
	w=&tmpflist[i*FNAMESIZE];
	while ((*w++=*p++)!=0);
	i++;
#ifdef __WATCOMC__

	dirent* dir=opendir(pathname);
	dirent* dent=dir;
	if (dir)
	{
		dent=readdir(dir);
		while (i<MAXFLIST&&dent)
		{
			if ((dent->d_attr&_A_SUBDIR)==0)
			{
				p=dent->d_name;

				if (strlen (p) > 15)
					p = " Bad Long Name";

				w=&tmpflist[i*FNAMESIZE];
				while ((*w++=*p++)!=0);
				i++;
			}
			dent=readdir(dir);
		}
		closedir(dir);
	}
#endif
#ifdef __MSVC__

	WIN32_FIND_DATA results;
	HANDLE h=FindFirstFile(pathname,&results);
	while (i<MAXFLIST && h!=INVALID_HANDLE_VALUE)
	{
		p=results.cAlternateFileName; // if long file name converts to short
		w=&tmpflist[i*FNAMESIZE];
		while ((*w++=*p++)!=0);
		i++;
		if (!FindNextFile(h,&results)) break;
	}

#endif
	numfiles=i;
	filelist=new char [i*FNAMESIZE];
	while (i--)
	{
	 	p=&tmpflist[i*FNAMESIZE];
		w=&filelist[i*FNAMESIZE];
	 	while ((*w++=*p++)!=0);
	}
	delete [] tmpflist;
}


char*	dirlist::operator+(char *c)
{
		char* pn;
		pn=&pathname[pathlen];
		for (int i=FNAMESIZE;--i!=0;)
			*pn++=*c++;
		return(pathname);
}

void dirlist::operator -= (int i)
{
	operator -= (operator [] (i));
}

void dirlist::operator -= (char* s)
{
	char* pname = operator	+ (s);
	remove(pname);
}


DES	dirlist::~dirlist()
{
	if (ownfilelist)
 		delete [] filelist;
	filelist=NULL;
	delete pathname;
	pathname=NULL;
	pathlen=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitFileSystem
//Author		Jim Taylor
//Date			Tue 3 Oct 1995
//
//Description	Initialise the file handling system. Will eventually 
//				handle graphics library selection.
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void fileman::InitFileSystem()
{
	//Work out what resources are available for the file system
#ifdef	_MSC_VER
	Mono_Text.Print((UByte*)"Before mem test ");
#endif
	MEMORYSTATUS	memstats={sizeof(MEMORYSTATUS)};
	GlobalMemoryStatus(&memstats);
	const blocksize=4096;
	typedef	char k4[blocksize];
	const MEMBLOCKSsize=(memstats.dwTotalPhys>20000000)?(memstats.dwTotalPhys/2):5000000;
	if (MEMBLOCKSsize>memstats.dwAvailPhys+memstats.dwAvailPageFile)
		_Error.ReallyEmitSysErr("Not Enough Virtual memory.\nWanted %iK, Got %iK phys and %iK virtual",
								MEMBLOCKSsize/1024,memstats.dwAvailPhys/1024,memstats.dwAvailPageFile/1024);
	const MEMBLOCKS= MEMBLOCKSsize/blocksize-1;
	int totalscore=0;
#ifdef NOMEMTEST
	k4* lump=new k4[MEMBLOCKS];
	Mono_Text.Print((UByte*)"Before mem test pass 0");
	int	i;
	for (i=0;i<MEMBLOCKS;i++)
		totalscore+=lump[i][0]+lump[i][blocksize-1];
	Mono_Text.Print((UByte*)"After pass 1 ");
	for (i=0;i<MEMBLOCKS;i++)
		totalscore+=lump[i][0]+lump[i][blocksize-1];
	Mono_Text.Print((UByte*)"After pass 2 ");
	for (i=0;i<MEMBLOCKS;i++)
		totalscore+=lump[i][0]+lump[i][blocksize-1];
	Mono_Text.Print((UByte*)"After pass 3 ");
	delete []lump;
#else
#ifdef	_MSC_VER
	Mono_Text.Print((UByte*)"Mem test disabled");
#endif
#endif

	GlobalMemoryStatus(&memstats);
	if (MEMBLOCKSsize>memstats.dwAvailPhys+memstats.dwAvailPageFile)
		_Error.ReallyEmitSysErr("Not Enough Virtual memory.\nWanted %iK, Got %iK phys and %iK virtual",
								MEMBLOCKSsize/1024,memstats.dwAvailPhys/1024,memstats.dwAvailPageFile/1024,totalscore);
#ifdef	_MSC_VER
	Mono_Text.Print((UByte*)"After mem test");
#endif

	totalmem=memstats.dwTotalPhys;
	totalfilesysmem=MEMBLOCKSsize;
	totalmemused=4000000;
	totalfilesysmemused=0;

	//Initialise the file system itself:
	makerootdirlist();
	delete loaddirlist(FIL_CommonDIR);
	delete loaddirlist(FIL_640resDIR);
	delete loaddirlist(FIL_soundsDIR);
	delete loaddirlist(FIL_battleDIR);
//DeadCode DAW 08Jan97 	delete FILEMAN.loaddirlist(FIL_localsDIR);

	//set up CD file access

//TempCode PD 08Oct98 
	driveletter='F';	//InitCDFS();

//	return(TRUE);
}

//----------Stuff used for the install-----------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getbasedir
//Author		Dave Whiteside
//Date			Tue 24 Sep 1996
//
//Description	return the base directory number
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
dirindex fileman::getbasedir(dirindex	d)						//DAW 24Sep96
{
	dirindex	n=d;

	while (direntries[n].driverfile!= INVALIDFILENUM
		&& direntries[n].parentdir != RAMCACHEHANDLEDIR)
		n=direntries[n].parentdir;
	if (direntries[n].driverfile==INVALIDFILENUM)
		return(RAMCACHEHANDLEDIR);
//DeadCode DAW 25Sep96 	printf("directory src:%i\tdest:%i\n",d,n);
	return(n);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		filesindir
//Author		R. Hyde 
//Date			Thu 31 Jul 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	fileman::filesindir(FileNum MyFile)
{
fileblock	fb=readfilelist(dirnum(MyFile));
string		dirlister=(string)	fb.getdata();
			assert(  (dirlister[0]) && ("Not expecting concatenated directory here!") );
			assert(  (dirlister[12]==0)
				  &&("Not expecting hand built file-list here!")
				 );
return	(fb.getsize()>>4);
}




//
// New Section for FileMan:
//		These are stubs to the actual code.
//		The stubs will contain interprocess locking
//
//
//
//

int		FileMan::filesindir(FileNum dirnum)
{
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'F';
	while(LockExchange(&interlocker,1))
		Sleep(20);
	int rv=fileman::filesindir(dirnum);
	LockExchange(&interlocker,0);
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'f';
	return rv;
}
Bool	FileMan::existnumberedfile(FileNum filenum)
{
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'E';
	while(LockExchange(&interlocker,1))
		Sleep(20);
	Bool rv=fileman::existnumberedfile(filenum);
	LockExchange(&interlocker,0);
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'e';
	return rv;
}
ULong	FileMan::readfileblock(FILE* openhandle,void* dataarea,ULong areasize)
{	//handle based- doesn't need locking!
	return	fileman::readfileblock(openhandle,dataarea,areasize);
}

ULong	FileMan::seekfilepos(FILE* openhandle,ULong offset)
{
	return	fileman::seekfilepos(openhandle,offset);
}
FILE*	FileMan::opennumberedfile(FileNum filenum)
{
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'O';
	while(LockExchange(&interlocker,1))
		Sleep(20);
	FILE*	rv=fileman::opennumberedfile(filenum);
	LockExchange(&interlocker,0);
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'o';
	return rv;
}

void	FileMan::setcdsavedata()
{
	fileman::setcdsavedata();
}

void	FileMan::closefile(FILE* openhandle)
{
	//handle based- doesn't need locking!
	fileman::closefile(openhandle);
}
char*	FileMan::makedirectoryname(dirindex	reqdir)
{	//requires external unlocking of access, or string copy operation
	fileman::makedirectoryname(reqdir);
	pathname[filenameindex]=0;
	return	pathnameptr;
}
string	FileMan::namenumberedfile(FileNum f)
{	//requires external unlocking of access, or string copy operation
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'N';
	while(LockExchange(&interlocker,1))
		Sleep(20);
	string rv=fileman::namenumberedfile(f);
	LockExchange(&interlocker,0);	//NOT GOOD ENOUGH!!!
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'n';
	return rv;
}

void FileMan::flushcachedfiles()
{
	while(LockExchange(&interlocker,1))
		Sleep(20);
	fileman::flushcachedfiles();
	LockExchange(&interlocker,0);
}

string	FileMan::namenumberedfile(FileNum f, string sss)
{	//requires external unlocking of access, or string copy operation

//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'S';
	while(LockExchange(&interlocker,1))
		Sleep(20);
	string rv=fileman::namenumberedfile(f);
	strcpy(sss,rv);
	LockExchange(&interlocker,0);	//NOT GOOD ENOUGH!!!
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'s';
	return sss;
}
string	FileMan::namenumberedfilelessfail(FileNum f)
{	//requires external unlocking of access, or string copy operation
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'X';
	while(LockExchange(&interlocker,1))
		Sleep(20);
	string rv=fileman::namenumberedfilelessfail(f);
	LockExchange(&interlocker,0);	//NOT GOOD ENOUGH!!!
//	(ULONG&)(((UWord*)0xb0000)[stuffed+=1])=0x700+'x';
	return rv;
}
void	FileMan::InitFileSystem()
{	
	fileman::InitFileSystem();
}

void FileMan::SetupAreaFiles(FileNum* fn)
{
	while(LockExchange(&interlocker,1))
		Sleep(20);
	fileman::SetupAreaFiles(fn);
	LockExchange(&interlocker,0);	//NOT GOOD ENOUGH!!!
}

void FileMan::CloseAreaFiles()
{
	while(LockExchange(&interlocker,1))
		Sleep(20);
	fileman::CloseAreaFiles();
	LockExchange(&interlocker,0);	//NOT GOOD ENOUGH!!!
}

void* FileMan::loadCDfile(FileNum a,SLong b,SLong c,Bool skipread)
{
	while(LockExchange(&interlocker,1))
		Sleep(20);
	void* retval=fileman::loadCDfile(a,b,c,skipread);
	LockExchange(&interlocker,0);	//NOT GOOD ENOUGH!!!
	return retval;
}

void FileMan::pingCD()
{
	while(LockExchange(&interlocker,1))
		Sleep(20);
	fileman::pingCD();
	LockExchange(&interlocker,0);	//NOT GOOD ENOUGH!!!
}

SLong	FileMan::getTotalMem()
{
	return totalmem;
}

SLong	FileMan::getTotalFileMemUsed()
{
#ifndef	NDEBUG
	return robtotalfilememused;
#else
	return 0;
#endif
}
