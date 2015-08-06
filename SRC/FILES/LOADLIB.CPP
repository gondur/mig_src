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
//Filename       loadlib.cpp
//System         
//Author         Jim Taylor
//Date           Mon 9 Oct 1995
//Description    Loads a rowan runtime library
//
//The library data starts with the quadword "ROWANLIB"
//We have to find this string in source and destination
//Then comes the filename and date with zero byte separators - they should match
//Then, we copy up to "ROWANLIB" followed by "REALCODE" and date with separators
//These should match in source and destination positions
//Then, we copy until "ROWANLIB" followed by "EXITOVER"
//The "OVER" part of "EXITOVER" should not be copied
//The "ROWANLIB" of the target which has "EXITOVER" after must not be overwritten
//or this means the library is too big!
//------------------------------------------------------------------------------
#include	<string.h>
#include	"dosdefs.h"
#include	"files.g"
#include	"fileman.h"
#include	"stub.m"
//#include	"main.h"
#include	"myerror.h"
#include	"hardpasm.h"
#ifdef	WIN95
	#include	<windows.h>
	#undef LoadLibrary
#else
	#include <dos.h>
#endif

#ifdef __WATCOMC__
#pragma aux	loadlibflag	= db 'ROWANLIBloadercode'
#else
inline void loadlibflag()
{
	__asm _emit 'R' __asm _emit 'O' __asm _emit 'W' __asm _emit 'A' 
	__asm _emit 'N' __asm _emit 'L' __asm _emit 'I' __asm _emit 'B' 
	__asm _emit 'l' __asm _emit 'o' __asm _emit 'a' __asm _emit 'd' 
	__asm _emit 'e' __asm _emit 'r' __asm _emit 'c' __asm _emit 'o' 
	__asm _emit 'd' __asm _emit 'e'
}
#endif

string	StubLock::LoadJimLib(	void*		targetaddr,		//Address of StubStart
								string		keyname,		//Text from stubstart2()
								FileNum		sourcefile,		//Caller decision
								void*		cmpbase,		//Original fix table
								int**		jumpobject		//Current virtual table ptr
							)
{

	if (sourcefile==-2)
	{
		loadlibflag();
		return (NULL);
	}
	else

#ifdef	WIN95

	{	//Windows is not interested in targetaddr, but does a DLL LOAD
		HANDLE	hLibrary=::LoadLibraryA(FILEMAN.namenumberedfile(sourcefile));
		locksize=1;
		(HANDLE&)lockstart=hLibrary;
		typedef char*	(WINAPI *Launcher) (int** object,string stamp);
		Launcher l=(Launcher) GetProcAddress(hLibrary,"_DEVICEHOOK@8");
		if (l==NULL)
			_Error.EmitSysErr("Couldn't get function from dll. File %x",sourcefile);
		char* dllret=l(jumpobject,keyname);
		if (dllret!=NULL)
			_Error.EmitSysErr("Incompatible function from dll. File %x\n%s!=%s?\n",sourcefile,keyname,dllret);

		return (string) targetaddr;
	}
#endif

#ifdef __DOS__													//ARM 02Aug96

	{
string	trgptr=(string)	targetaddr;
string	cmpaddr=cmpbase?(string)cmpbase:trgptr;
fileblock	fb(sourcefile);
string	srcptr=(string) getdata(fb);
ULong	fs=getsize(fb);
ULong	llockstart;
		//Find "ROWANLIB"
		while	(	(	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
			 	 	|| (((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
					)
			 	&& fs--	//this is the only check for file size!
				)
			srcptr++;
		while	(	(((ULong*) (cmpaddr))[0] != *((ULong*) ("ROWA")))
			 	|| (((ULong*) (cmpaddr))[1] != *((ULong*) ("NLIB")))
				)
		{
			cmpaddr++;
			trgptr++;
		}


		if	(lockstart)
		{	//unlock existing page
			if (lockstart!=(ULong) trgptr)
				_Error.EmitSysErr("Target address has moved between calls?");
			DPMIregs r;
			r.l.eax = 0x0601;							/* DPMI UNlock linear region */
			r.l.ebx = ((ULong) lockstart) >> 16;
			r.l.ecx = ((ULong) lockstart) & 0xFFFF;
			r.l.esi = ((ULong) locksize) >> 16;
			r.l.edi = ((ULong) locksize) & 0xFFFF;
			ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 			int386 (0x31, &r, &r);
		}
//DeadCode JIM 15Mar96 		else
		llockstart=(ULong) trgptr;
		srcptr+=8;
		cmpaddr+=8;
		trgptr+=8;
		if 	(	(((ULong*) (srcptr))[0] != *((ULong*) ("HEAD")))
		 	||	(((ULong*) (srcptr))[1] != *((ULong*) ("CODE")))
			)
			_Error.EmitSysErr("Source ROWANLIB file doesn't start HEADCODE. %x %s",
				sourcefile,keyname);

		if 	(	(((ULong*) (cmpaddr))[0] != *((ULong*) ("HEAD")))
		 	||	(((ULong*) (cmpaddr))[1] != *((ULong*) ("CODE")))
			)
			_Error.EmitSysErr("Source ROWANLIB file doesn't start HEADCODE. %x %s",
				sourcefile,keyname);


		//now pointing past matched header
		//copy until "REALCODE" header

		while	(	(((ULong*) (cmpaddr))[0] != *((ULong*) ("ROWA")))	//comparator header size
			 	&&	(((ULong*) (cmpaddr))[1] != *((ULong*) ("NLIB")))
				&&	(((ULong*) (trgptr))[0] != *((ULong*) ("ROWA")))	//target run out of space
			 	&&	(((ULong*) (trgptr))[1] != *((ULong*) ("NLIB")))
				)
		{
			*(trgptr++)=*(srcptr++);
			cmpaddr++;
		}
		//Check headers match up correctly

    	if (	(((ULong*) (cmpaddr))[2] != *((ULong*) ("REAL")))
			||	(((ULong*) (cmpaddr))[3] != *((ULong*) ("CODE")))
			)
			_Error.EmitSysErr("Middle ROWANLIB not REALCODE in target memory");
		if (	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
			||	(((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
			)
			_Error.EmitSysErr("Middle ROWANLIB position mismatch - file %x",sourcefile);
		if (	(((ULong*) (srcptr))[2] != *((ULong*) ("REAL")))
			||	(((ULong*) (srcptr))[3] != *((ULong*) ("CODE")))
			)
			_Error.EmitSysErr("Middle ROWANLIB not REALCODE in sourcefile %x",sourcefile);
//DeadCode JIM 27Feb96 		if (((ULong*) (srcptr))[4] != ((ULong*) (trgptr))[4])
//DeadCode JIM 27Feb96 			_Error.EmitSysErr("Middle ROWANLIB dates don't match - file %x",sourcefile);
//DeadCode JIM 27Feb96 		if (((ULong*) (srcptr))[5] != ((ULong*) (trgptr))[5])
//DeadCode JIM 27Feb96 			_Error.EmitSysErr("Middle ROWANLIB dates don't match - file %x",sourcefile);

		//CMPADDR HAS DONE ITS JOB!

		srcptr+=8;
		trgptr+=8;
		//Ok.. can now copy until next header in either file

		while 	(	(	(((ULong*) (trgptr))[0] != *((ULong*) ("ROWA")))
				 	|| (((ULong*) (trgptr))[1] != *((ULong*) ("NLIB")))
				 	|| (((ULong*) (trgptr))[2] != *((ULong*) ("EXIT")))
				 	|| (((ULong*) (trgptr))[3] != *((ULong*) ("OVER")))
					)
			 	&&	(	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
				 	|| (((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
				 	|| (((ULong*) (srcptr))[2] != *((ULong*) ("EXIT")))
				 	|| (((ULong*) (srcptr))[3] != *((ULong*) ("OVER")))
					)
				)
			*(trgptr++)=*(srcptr++);

		//Copy ROWANLIB part only, and only if target not full

		if	 	(	(	(((ULong*) (trgptr))[0] == *((ULong*) ("ROWA")))
				 	|| (((ULong*) (trgptr))[1] == *((ULong*) ("NLIB")))
				 	|| (((ULong*) (trgptr))[2] == *((ULong*) ("EXIT")))
				 	|| (((ULong*) (trgptr))[3] == *((ULong*) ("OVER")))
					)
			 	&&	(	(((ULong*) (srcptr))[0] == *((ULong*) ("ROWA")))
				 	|| (((ULong*) (srcptr))[1] == *((ULong*) ("NLIB")))
				 	|| (((ULong*) (srcptr))[2] == *((ULong*) ("EXIT")))
				 	|| (((ULong*) (srcptr))[3] == *((ULong*) ("OVER")))
					)
				)
		{
			trgptr+=8;
			srcptr+=8;
		}
		else
		{
	
int			count=8;
			while 	(	(	(((ULong*) (trgptr))[0] != *((ULong*) ("ROWA")))
					 	|| (((ULong*) (trgptr))[1] != *((ULong*) ("NLIB")))
					 	|| (((ULong*) (trgptr))[2] != *((ULong*) ("EXIT")))
				 		|| (((ULong*) (trgptr))[3] != *((ULong*) ("OVER")))
						)
				 	&&	(count--)
					)
				*(trgptr++)=*(srcptr++);

			//If target is full then error message
		
			if	(	(((ULong*) (trgptr))[0] == *((ULong*) ("ROWA")))
		 		&& (((ULong*) (trgptr))[1] == *((ULong*) ("NLIB")))
		 		&& (((ULong*) (trgptr))[2] == *((ULong*) ("EXIT")))
		 		&& (((ULong*) (trgptr))[3] == *((ULong*) ("OVER")))
				)
				_Error.EmitSysErr("Library too big for code space!!! - file %x",sourcefile);
		}
		//Now search for ROWANLIB again in source
		while	(	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
			 	|| (((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
				)
			srcptr++;
		if (strcmp(srcptr,keyname))
			_Error.EmitSysErr("Keycode for library did not match. [%s] != [%s]",srcptr,keyname);

		{
			lockstart=llockstart;
			locksize=((ULong) trgptr)-lockstart;
			DPMIregs r;
			r.l.eax = 0x0600;							/* DPMI lock linear region */
			r.l.ebx = ((ULong) lockstart) >> 16;
			r.l.ecx = ((ULong) lockstart) & 0xFFFF;
			r.l.esi = ((ULong) locksize) >> 16;
			r.l.edi = ((ULong) locksize) & 0xFFFF;
			ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 			int386 (0x31, &r, &r);

		}

		if (cmpbase && cmpbase!=targetaddr)
		{	//new job: build new virtual function table
			int delta =(int)targetaddr-(int)cmpbase;
			int *builder=(int*)trgptr;
			assert(jumpobject);
			int *bsrc=*jumpobject;
			*jumpobject=builder;
			while (*bsrc<(int)cmpaddr && *bsrc>(int)cmpbase)
			{
				for (int i=4;--i;)
				{
					if	(	(((ULong*) (trgptr))[0] == *((ULong*) ("ROWA")))
				 		&& (((ULong*) (trgptr))[1] == *((ULong*) ("NLIB")))
				 		&& (((ULong*) (trgptr))[2] == *((ULong*) ("EXIT")))
		 				&& (((ULong*) (trgptr))[3] == *((ULong*) ("OVER")))
						)
						_Error.EmitSysErr("Run out of space making DLL VFR! (%x,%s)",sourcefile,keyname);
					trgptr++;
				}
				*builder++=*bsrc++ + delta;
			}
		}
		return(trgptr);
	 }
#endif
}


//destructor
DES		StubLock::~StubLock()	{ClearLock();}
void	StubLock::ClearLock()
{
	if (lockstart && locksize!=-1)
#ifdef WIN95
		FreeLibrary((HANDLE&)lockstart);
#endif
#ifdef __DOS__
	{	//free the lock
		DPMIregs r;
		r.l.eax = 0x0601;							/* DPMI lock linear region */
		r.l.ebx = ((ULong) lockstart) >> 16;
		r.l.ecx = ((ULong) lockstart) & 0xFFFF;
		r.l.esi = ((ULong) locksize) >> 16;
		r.l.edi = ((ULong) locksize) & 0xFFFF;
		ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 		int386 (0x31, &r, &r);
	}
#endif
	lockstart=0;
	locksize=0;
}


//DeadCode JIM 02May97 string	StubLock::CopyLibHeader(int newaddr,int oldaddr)
//DeadCode JIM 02May97 {
//DeadCode JIM 02May97 
//DeadCode JIM 02May97 
//DeadCode JIM 02May97 string	trgptr=(string)	newaddr;
//DeadCode JIM 02May97 	if (newaddr!=oldaddr)
//DeadCode JIM 02May97 	{
//DeadCode JIM 02May97 string	srcptr=(string) oldaddr;
//DeadCode JIM 02May97 		
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		while	(	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
//DeadCode JIM 02May97 			 	&&	(((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
//DeadCode JIM 02May97 				)
//DeadCode JIM 02May97 			*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//DeadCode JIM 02May97 	}
//DeadCode JIM 02May97 		return (trgptr);
//DeadCode JIM 02May97 #endif
//DeadCode JIM 02May97 }

