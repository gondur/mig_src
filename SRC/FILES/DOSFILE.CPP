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
//Filename       dosfile.cpp
//System         
//Author         Paul.   
//Date           Mon 4 Nov 1996
//Description    
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#define		F_GRAFIX
#include	"hardpasm.h"
#include	"myerror.h"
#include 	<stdio.h>
#include 	<conio.h>
#include    <string.h>
#include    <direct.h>
#include	"mymath.h"
#include	"fileman.h"
#include	"mscdex.h"
#include	"myAngles.h"
#include	"worldinc.h"
#include	"world.h"
#include	"main.h"
#include	"Mytime.h"
#include	<new.h>
#define		SPECIAL_KEYMAPS	FALSE
#include	"Keytest.h"

extern 		Error 		_Error;
extern 		MathLib		Math_Lib;

const	int	DOSFILE_SECTSIZE = 2048;							//PD 18Nov96
const	int	DOSFILE_SEEKSTEP = 8*DOSFILE_SECTSIZE;				//PD 18Nov96

DPMIMem		int_code,	int_data;

#ifdef __WATCOMC__
extern		void ASM_strcpy(UByte* src,UByte* dest);
#pragma		aux	 ASM_strcpy = \
"			mov		ebx,esi					"\
"			xor		eax,eax					"\
"			xor		ecx,ecx					"\
"lp1:		mov		al,byte ptr ds:[esi]	"\
"			inc		ecx						"\
"			inc		esi						"\
"			or		eax,eax					"\
"			jnz		short lp1				"\
"ok1:		mov		esi,ebx					"\
"			rep		movsb					"\
parm		[esi] [edi]						\
modify		[eax ebx ecx esi edi]
#else
#ifdef __MSVC__
inline void ASM_strcpy(UByte* src,UByte* dest)
{
    __asm
    {
		mov esi,src;
		mov edi,dest;
		mov		ebx,esi;
		xor		eax,eax;
		xor		ecx,ecx;
lp1:	mov		al,byte ptr ds:[esi];
		inc		ecx;
		inc		esi;
		or		eax,eax;
		jnz		short lp1;
ok1:	mov		esi,ebx;
		rep		movsb;
    }
}

#endif
#endif

static char fnum=0;
//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//Procedure		CDCommand
//Author		Paul.   
//Date			Tue 29 Oct 1996
//
//Description	Interface to MSCDEX via int 2Fh funtion 15h subfunction 10h
//
//Inputs		Request block and command block + size of command block
//
//Returns		Status after executing the command
//
//------------------------------------------------------------------------------
UWord fileman::CDCommand(RequestHeaderP ioctl,CDCommP command,int cmdsize)
{
	IOCTLI			*ioctli = (IOCTLI*)ioctl,
					*rm_ioctli;
	UByte			*commandp,
					*rm_command;
	unsigned char 	*real_mode_stack;
	DPMIregs		regs;
	int				REALMODE_STACK_SIZE;

//DeadCode JIM 14Dec96 	*(char*)0xB0702=fnum;///////////////////
	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;

	real_mode_stack = Whole_Screen->real_mode_stack;

	REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;

	//Copy request header and command block to DOS RAM

	rm_ioctli = (IOCTLI* )real_mode_stack;

	*rm_ioctli = *ioctli;

	rm_ioctli->transferaddr_seg = real_mode_seg;
	rm_ioctli->transferaddr_off = sizeof(IOCTLI);				//PD 29Oct96

	rm_ioctli->bytestotransfer = cmdsize;

	rm_ioctli->status = 0;	//Must be cleared before command is executed

	rm_command = (UByte* )(real_mode_stack + sizeof(IOCTLI));

	commandp = (UByte* )command;

	for (int j=0;j<cmdsize;*rm_command++ = *commandp++,j++);

	regs.w.ax = 0x1510;
	regs.w.cx = driveletter;

	regs.w.bx = 0;
	regs.flags=regs.CLEAR;

//DeadCode JIM 14Dec96 	*(char*)0xB0704=fnum;///////////////////
	ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//DeadCode JIM 14Dec96 	*(char*)0xB0706=fnum;///////////////////

	//copy the modified structures back up from DOS RAM

	*ioctli = *rm_ioctli;

	rm_command = (UByte* )(real_mode_stack + sizeof(IOCTLI));

	commandp = (UByte* )command;

	for (j=0;j<cmdsize;*commandp++ = *rm_command++,j++);

//DeadCode JIM 14Dec96 	*(char*)0xB0708=fnum;///////////////////
	return(rm_ioctli->status);
}

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
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
UWord fileman::CDSeek(ULong pos)
{

	DPMIregs		regs;
	unsigned char 	*real_mode_stack;
	int				REALMODE_STACK_SIZE;

	real_mode_stack = Whole_Screen->real_mode_stack;

	REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;

	regs.l.edx 	= pos;
	regs.w.ax = 0x0000;		//SEEK

	ASM_DOSvia31(0x18,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	return(regs.w.ax);
}

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//Procedure		GetDirectoryEntry
//Author		Paul.   
//Date			Wed 30 Oct 1996
//
//Description	Use int 2Fh function 15h subfunction Fh to fill dir_entry
//				structure.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord fileman::CDGetDirectoryEntry(DirEntryP direntry,string filename)
{			 
	unsigned char 	*real_mode_stack;
	DPMIregs		regs;
	int				REALMODE_STACK_SIZE;

	DirEntryP		rm_direntry;
	UByte*			rm_filename;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;

	real_mode_stack = Whole_Screen->real_mode_stack;

	REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;

	rm_direntry = (DirEntryP)real_mode_stack;

	rm_filename = (UByte* )(real_mode_stack+sizeof(DirEntry)*2);

	ASM_strcpy((UByte*)filename,rm_filename);							//PD 08Nov96

	regs.w.ax = 0x150F;

	regs.b.cl = driveletter;
	regs.b.ch = 0x01;			//Fill generic directory structure

	//filename string comes straight after the DirEntry structure
	//on the real_mode_stack

	//pointer to DirEntry structure to fill in

	regs.w.si = real_mode_seg;		
	regs.w.di = 0;

	//pointer to NULL terminated filename string

	regs.s.es = real_mode_seg;
	regs.w.bx = sizeof(DirEntry)*2;

	ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);

	//Copy filled in structure back up from DOS RAM

	*direntry = *rm_direntry;

	if (regs.flags & DPMIregs::CF)	return (regs.w.ax);	//Error code if carry set

	return (0);
}

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//Procedure		CDReadFileBlock
//Author		Paul.   
//Date			Wed 30 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord fileman::CDReadFileBlock(ULong seekpos,void* blockdata,ULong datasize)
{
	DPMIregs		regs;
	unsigned char 	*real_mode_stack;
	int				REALMODE_STACK_SIZE;

	real_mode_stack = Whole_Screen->real_mode_stack;

	REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;

	regs.l.edx 	= seekpos;
	regs.w.cx	= real_mode_seg;
	regs.w.bx	= 0;

	regs.w.ax = 0x0001;

	ASM_DOSvia31(0x18,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);

	//Copy the loaded data to the correct data area

	ULong	*srcp,*destp;

	srcp = (ULong* )real_mode_stack;
	destp = (ULong* )blockdata;

	for (int j=0;j<(datasize/4);*destp++=*srcp++,j++);

	return(regs.w.ax);
}

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//Procedure		CDSetup
//Author		Paul.   
//Date			Mon 28 Oct 1996
//
//Description	Determines how many CD-ROM drives are attatched. Decides
//				which one (if any ) contain our CD and makes sure the
//				door is closed and locked.
//				(for the moment I just assume that the first CD drive
//				is ours and that the CD is in the drive)
//
//Inputs		
//
//Returns		cddir == ?:\FLY where ? is the CD-ROM drive letter for
//						the drive containing our CD
//
//------------------------------------------------------------------------------
void fileman::CDSetup(string cddir)
{
	DPMIregs	regs;

//DeadCode DAW 13Dec96 	if (Whole_Screen->prevmodeAX==0)
//DeadCode DAW 13Dec96 		printf("Flying Corps CD ?\n");

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;

	unsigned char *real_mode_stack = Whole_Screen->real_mode_stack;

	int	REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;

	//Get number of CD-ROM drive letters

	cddir[0]='\0';
	regs.w.ax = 0x1500;
	regs.w.bx=0;
	ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	if (regs.w.bx==0)
		return;

	//Returns 	regs.w.bx = no. of CD-ROM drive letters
	//			regs.w.cx = starting drive letter of CD-ROM drive
	//						letters

	real_mode_seg 	= regs.s.ds;
	driveletter 	= regs.w.cx;
	noofdrives 		= regs.w.bx;

	regs.w.ax = 0x150C;
	regs.w.bx=0;
	ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
	if (regs.b.bh<2 || (regs.b.bh==2 && regs.b.bl<0x0a))
		return;

	Bool cdisours=FALSE;

	UWord	cmdstatus;

	IOCTLO	ioctlo,*ioctlop=&ioctlo;
	IOCTLI	ioctli,*ioctlip=&ioctli;

	struct	Raddr		raddr,		*raddrp=&raddr;
	struct	MedChng		medchng,	*medchngp=&medchng;
	struct	DevStat 	devstat,	*devstatp=&devstat;

	do
	{
		for (int disknum=0;disknum<26;disknum++)
		{
			regs.w.ax=0x150B;
			regs.w.cx=disknum;
			ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
			if (regs.w.bx==0xadad && regs.w.ax!=0)
			{
				driveletter=disknum;
				cmdstatus = CDCommand(ioctlip,devstatp,sizeof(DevStat));	//Read drive status
				if ((devstatp->deviceparameters & 0x801)==0)	//PD 05Nov96
				{
					string keyfile = "\\FLY\\LANDSCAP\\DIR.DIR";	
					DirEntry direntry,*direntryp=&direntry;
					cmdstatus = CDGetDirectoryEntry(direntryp,keyfile);
					if (cmdstatus==0)
					{
						if (Whole_Screen->prevmodeAX==0)
							printf("CD-ROM %c:\n",disknum+'A');
					 	cdisours=TRUE;
						break;
					}
				}
			}
		}
		if (disknum==26)
			printf("Flying Corps CD-ROM ?\n");
		if (!cdisours)
		{
			if (Whole_Screen->prevmodeAX==0)
				printf("Press any key to retry\n");									//english
//TempCode DAW 06Jan97 				printf("Appuyez sur une touche pour redémarrer\n");					//french
//TempCode DAW 06Jan97 				printf("Pulsa cualquier tecla para volver a intentarlo\n");			//spanish
//TempCode DAW 06Jan97 				printf("Beliebige Taste drücken, um es erneut zu versuchen.\n");	//german
			UIKeyEvent	latestrawkey;
			while	(!Key_Tests.GetUIKey(latestrawkey)) {}
			if (latestrawkey.keycode==1)
			{
//TempCode DAW 13Dec96 				if (Whole_Screen->prevmodeAX==0)
//TempCode DAW 13Dec96 					printf("Skipping test...\n");
				driveletter=0;
				cdisours=TRUE;
			}
		}
	}
	while (!cdisours);

	struct	LockDoor	lockdoor,	*lockdoorp=&lockdoor;
	struct	SectSize	sectsize,	*sectsizep=&sectsize;

	if (driveletter)
	{
		cmdstatus = CDCommand(ioctlip,raddrp,sizeof(Raddr));		//Get device header//JIM 12Nov96
		cmdstatus = CDCommand(ioctlip,medchngp,sizeof(MedChng));	//Check for media change//JIM 12Nov96
		lockdoor.lockfunction = 1;

		cmdstatus = CDCommand(ioctlop,lockdoorp,sizeof(LockDoor));

		cmdstatus = CDCommand(ioctlip,sectsizep,sizeof(SectSize));

		sectorsize = sectsizep->sectorsize;

//DeadCode PD 18Nov96 		direntries[dirnum(DIR_LANDSCAP)].openfile.cdstart=1;		//PD 05Nov96
	}
	cddir[0]='A'+driveletter;
	cddir[1]=':';
	cddir[2]='\\';
	cddir[3]='F';
	cddir[4]='L';
	cddir[5]='Y';
	cddir[6]='\0';

	//Install a new INT 18h handler to handle MSCDEX device
	//requests

	ULong	devheadseg 	= (ULong )&fileman__DeviceHdrSeg - (ULong )&fileman__dosIRstart;
	ULong	devheadoff 	= (ULong )&fileman__DeviceHdrOff - (ULong )&fileman__dosIRstart;
	ULong	devletter 	= (ULong )&fileman__DriveLetter - (ULong )&fileman__dosIRstart;

	Whole_Screen->GetDOSRAM(int_data,(((ULong) &fileman__dosIRend)-((ULong) &fileman__dosIRstart)),0);

	int_code=int_data;

	//copy DOS IR to the buffer

	string	fileisr=(string) int_code.flat,
			srcisr=(string) fileman__dosIRcode;

	for	(int i=(((ULong) fileman__dosIRend)-((ULong) fileman__dosIRcode));	 i--;)
		*(fileisr++)=*(srcisr++);

	*((UWord *)((UByte*)int_code.flat + devheadseg))=raddr.devheaderp_seg;
	*((UWord *)((UByte*)int_code.flat + devheadoff))=raddr.devheaderp_off;
	*((UWord *)((UByte*)int_code.flat + devletter))=driveletter;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;

	regs.w.ax = 0x0200;
	regs.b.bl = 0x18;

	ASM_DEXint31(&regs);

	old_int18h_seg = regs.w.cx;
	old_int18h_off = regs.w.dx;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;

	regs.w.ax = 0x0201;
	regs.b.bl = 0x18;

	regs.w.cx = int_code.seg;
	regs.w.dx = int_code.off;

	ASM_DEXint31(&regs);
}

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//Procedure		CDCloseDown
//Author		Paul.   
//Date			Tue 29 Oct 1996
//
//Description	Removes the lock on the CD drive
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void fileman::CDCloseDown()
{
	UWord		cmdstatus;
	DPMIregs	regs;

	IOCTLO	ioctlo,*ioctlop=&ioctlo;
	IOCTLI	ioctli,*ioctlip=&ioctli;

	struct	Raddr		raddr,		*raddrp=&raddr;
	struct	MedChng		medchng,	*medchngp=&medchng;
	struct	LockDoor	lockdoor,	*lockdoorp=&lockdoor;
	if (driveletter)
	{
		cmdstatus = CDCommand(ioctlip,raddrp,sizeof(Raddr));

		cmdstatus = CDCommand(ioctlip,medchngp,sizeof(MedChng));

		lockdoor.lockfunction = 0;

		cmdstatus = CDCommand(ioctlop,lockdoorp,sizeof(LockDoor));
	}
	//Restore old int 18h vector

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
	regs.l.edi=regs.l.ebp=regs.l.esi=0;

	regs.w.ax = 0x0201;
	regs.b.bl = 0x18;

	regs.w.cx = old_int18h_seg;
	regs.w.dx = old_int18h_off;

	ASM_DEXint31(&regs);

	Whole_Screen->FreeDOSRAM(int_data);							//PD 06Nov96
}

//Old_Code PD 18Nov96 //ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//Old_Code PD 18Nov96 //Procedure		CDReSeek
//Old_Code PD 18Nov96 //Author		Paul.   
//Old_Code PD 18Nov96 //Date			Mon 4 Nov 1996
//Old_Code PD 18Nov96 //
//Old_Code PD 18Nov96 //Description	
//Old_Code PD 18Nov96 //
//Old_Code PD 18Nov96 //Inputs		
//Old_Code PD 18Nov96 //
//Old_Code PD 18Nov96 //Returns	
//Old_Code PD 18Nov96 //
//Old_Code PD 18Nov96 //------------------------------------------------------------------------------
//Old_Code PD 18Nov96 void fileman::CDReSeek()
//Old_Code PD 18Nov96 {
//Old_Code PD 18Nov96 	if (driveletter)											//PD 05Nov96
//Old_Code PD 18Nov96 	{															//PD 05Nov96
//Old_Code PD 18Nov96 		dirindex	di = dirnum(DIR_LANDSCAP);
//Old_Code PD 18Nov96 		direntries[di].openfile.currfileindex=0x07FFFFFFF;
//Old_Code PD 18Nov96 	}															//PD 05Nov96
//Old_Code PD 18Nov96 }

//Old_Code PD 18Nov96 //ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//Old_Code PD 18Nov96 //Procedure		CDMakeFileBlock
//Old_Code PD 18Nov96 //Author		Paul.   
//Old_Code PD 18Nov96 //Date			Mon 4 Nov 1996
//Old_Code PD 18Nov96 //
//Old_Code PD 18Nov96 //Description	
//Old_Code PD 18Nov96 //
//Old_Code PD 18Nov96 //Inputs		
//Old_Code PD 18Nov96 //
//Old_Code PD 18Nov96 //Returns	
//Old_Code PD 18Nov96 //
//Old_Code PD 18Nov96 //------------------------------------------------------------------------------
//Old_Code PD 18Nov96 void fileman::CDMakeFileBlock(	fileblock* fbp,
//Old_Code PD 18Nov96 								fileblocklink* link,
//Old_Code PD 18Nov96 								FileNum MyFile,
//Old_Code PD 18Nov96 								ULong	blocksize,
//Old_Code PD 18Nov96 								ULong	offset)
//Old_Code PD 18Nov96 {
//Old_Code PD 18Nov96 	//direntries.openfile.cdstart = logical block number of the CD file start on the disk
//Old_Code PD 18Nov96 	//direntries.openfile.currfileindex = current offset into the file
//Old_Code PD 18Nov96 	//									  if -ve then we are currently seeking to position
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 	FILE*		filehandle;
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 	dirindex	di = dirnum(MyFile);
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 	int			realfileindex = direntries[di].openfile.currfileindex;
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 	if (realfileindex & 0x80000000)
//Old_Code PD 18Nov96 	{
//Old_Code PD 18Nov96 		link->datasize=blocksize;
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 		realfileindex &= 0x7FFFFFFF;
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 		SLong	deltaseekpos;
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 		if (realfileindex!=offset)
//Old_Code PD 18Nov96 		{
//Old_Code PD 18Nov96 			//Abort the current seek and load the new data now
//Old_Code PD 18Nov96 			deltaseekpos=0;
//Old_Code PD 18Nov96 		}
//Old_Code PD 18Nov96 		else
//Old_Code PD 18Nov96 			deltaseekpos = realfileindex - direntries[di].openfile.actualfileindex;
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 		if (deltaseekpos<=DOSFILE_SEEKSTEP)
//Old_Code PD 18Nov96 		{
//Old_Code PD 18Nov96 			direntries[di].openfile.currfileindex = realfileindex;
//Old_Code PD 18Nov96 			direntries[di].openfile.actualfileindex = realfileindex;
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 			//close enough to load
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 			if ((fbp->fileblockdata = new voidbigblock [link->datasize])==NULL)
//Old_Code PD 18Nov96 				_Error.EmitSysErr("Failed to allocate memory for file load "
//Old_Code PD 18Nov96 									"(file %x, size %d)",
//Old_Code PD 18Nov96 									MyFile,link->datasize);
//Old_Code PD 18Nov96 			seekfilepos(direntries[di].openfile.handle,realfileindex);
//Old_Code PD 18Nov96 			readfileblock(direntries[di].openfile.handle,fbp->fileblockdata,link->datasize);
//Old_Code PD 18Nov96 		}
//Old_Code PD 18Nov96 		else
//Old_Code PD 18Nov96 		{
//Old_Code PD 18Nov96 			//skip read in steps of DOSFILE_SEEKSTEP
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 			direntries[di].openfile.actualfileindex += DOSFILE_SEEKSTEP;
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 			if ((fbp->fileblockdata = new voidbigblock [link->datasize])==NULL)
//Old_Code PD 18Nov96 				_Error.EmitSysErr("Failed to allocate memory for file load "
//Old_Code PD 18Nov96 									"(file %x, size %d)",
//Old_Code PD 18Nov96 									MyFile,link->datasize);
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 			seekfilepos(direntries[di].openfile.handle,direntries[di].openfile.actualfileindex);
//Old_Code PD 18Nov96 			readfileblock(direntries[di].openfile.handle,fbp->fileblockdata,2048);
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 			delete (fbp->fileblockdata);
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 			fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//Old_Code PD 18Nov96 		}
//Old_Code PD 18Nov96 	}
//Old_Code PD 18Nov96 	else
//Old_Code PD 18Nov96 	{
//Old_Code PD 18Nov96 		//start a new seek to position
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 		if (direntries[di].openfile.number==MyFile)
//Old_Code PD 18Nov96 		{
//Old_Code PD 18Nov96 			direntries[di].openfile.currfileindex=offset | 0x80000000;
//Old_Code PD 18Nov96 			link->datasize=blocksize;
//Old_Code PD 18Nov96 			fbp->fileblockdata=NULL;
//Old_Code PD 18Nov96 
//Old_Code PD 18Nov96 			if (offset<direntries[di].openfile.actualfileindex)
//Old_Code PD 18Nov96 			{
//Old_Code PD 18Nov96 				direntries[di].openfile.actualfileindex = offset;
//Old_Code PD 18Nov96 //TempCode PD 17Nov96 				_Error.EmitSysErr("This file system has no reverse gear");
//Old_Code PD 18Nov96 			}
//Old_Code PD 18Nov96 		}
//Old_Code PD 18Nov96 		else
//Old_Code PD 18Nov96 		{
//Old_Code PD 18Nov96 			filehandle=opennumberedfile(MyFile);
//Old_Code PD 18Nov96 			link->datasize=getfilesize(filehandle);
//Old_Code PD 18Nov96 			if (link->datasize>blocksize)
//Old_Code PD 18Nov96 			{
//Old_Code PD 18Nov96 				if (direntries[di].openfile.number!=INVALIDFILENUM)
//Old_Code PD 18Nov96 					closefile(FILEMAN.direntries[di].openfile.handle);
//Old_Code PD 18Nov96 				direntries[di].openfile.number=MyFile;
//Old_Code PD 18Nov96 				direntries[di].openfile.handle=filehandle;
//Old_Code PD 18Nov96 				direntries[di].openfile.maxfilesize=link->datasize;
//Old_Code PD 18Nov96 				direntries[di].openfile.currfileindex=offset | 0x80000000;
//Old_Code PD 18Nov96 				direntries[di].openfile.actualfileindex=offset;
//Old_Code PD 18Nov96 				if (offset>link->datasize)
//Old_Code PD 18Nov96 					_Error.EmitSysErr("Index past end of file");
//Old_Code PD 18Nov96 				link->datasize=blocksize;
//Old_Code PD 18Nov96 				fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//Old_Code PD 18Nov96 			}
//Old_Code PD 18Nov96 			else
//Old_Code PD 18Nov96 				assert((offset==0)&&"Can only use offset if buffer smaller than file!");
//Old_Code PD 18Nov96 		}
//Old_Code PD 18Nov96 	}
//Old_Code PD 18Nov96 }
//Old_Code PD 12Nov96 {
//Old_Code PD 12Nov96 	//direntries.openfile.cdstart = logical block number of the CD file start on the disk
//Old_Code PD 12Nov96 	//direntries.openfile.currfileindex = current offset into the file
//Old_Code PD 12Nov96 	//									  if -ve then we are currently seeking to position
//Old_Code PD 12Nov96 	UWord		cmdstatus;
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 	dirindex	di = dirnum(MyFile);
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 	int			realfileindex = direntries[di].openfile.currfileindex;
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 	if (realfileindex & 0x80000000)
//Old_Code PD 12Nov96 	{
//Old_Code PD 12Nov96 		link->datasize=blocksize;
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 		struct	IOCTLI	ioctli,	*ioctlip=&ioctli;
//Old_Code PD 12Nov96 		struct	LocHead	lochead,*locheadp=&lochead;
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 		realfileindex &= 0x7FFFFFFF;
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 		if (realfileindex!=offset)
//Old_Code PD 12Nov96 		{
//Old_Code PD 12Nov96 			//Abort the current seek and load the new data now
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 			CDgetthedata=TRUE;
//Old_Code PD 12Nov96 		}
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 		ULong	reqseekpos = direntries[di].openfile.cdstart + (realfileindex/sectorsize);
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 		if (CDgetthedata)
//Old_Code PD 12Nov96 		{
//Old_Code PD 12Nov96 			direntries[di].openfile.currfileindex = realfileindex;
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 			//close enough to load ( <3 sectors away)
//Old_Code PD 12Nov96 			if ((fbp->fileblockdata = new voidbigblock [link->datasize])==NULL)
//Old_Code PD 12Nov96 				_Error.EmitSysErr("Failed to allocate memory for file load "
//Old_Code PD 12Nov96 									"(file %x, size %d)",
//Old_Code PD 12Nov96 									MyFile,link->datasize);
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 			cmdstatus = CDReadFileBlock(reqseekpos,fbp->fileblockdata,2048);
//Old_Code PD 12Nov96 			cmdstatus = CDReadFileBlock(reqseekpos+1,(void*)((int)fbp->fileblockdata+2048),2048);
//Old_Code PD 12Nov96 			assert((cmdstatus==0x100)&&("CD Read file block failed"));
//Old_Code PD 12Nov96 		}
//Old_Code PD 12Nov96 		else
//Old_Code PD 12Nov96 		{
//Old_Code PD 12Nov96 			//check to see if we are close to the requested offset
//Old_Code PD 12Nov96 			cmdstatus = CDCommand(ioctlip,locheadp,sizeof(LocHead));
//Old_Code PD 12Nov96 			assert((cmdstatus&0x0100)&&("Request for CD head location failed"));
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 			ULong	disttogo = (reqseekpos>=lochead.locofdrivehead)?
//Old_Code PD 12Nov96 								reqseekpos-lochead.locofdrivehead:
//Old_Code PD 12Nov96 								0x7FFFFFFF;
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 			if (disttogo==0)
//Old_Code PD 12Nov96 				CDgetthedata=TRUE;
//Old_Code PD 12Nov96 			else
//Old_Code PD 12Nov96 				fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//Old_Code PD 12Nov96 		}
//Old_Code PD 12Nov96 	}
//Old_Code PD 12Nov96 	else
//Old_Code PD 12Nov96 	{
//Old_Code PD 12Nov96 		//start a new seek to position
//Old_Code PD 12Nov96 		DirEntry 	direntry,*direntryp=&direntry;
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 		CDgetthedata = FALSE;
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 		if (direntries[di].openfile.number==MyFile)
//Old_Code PD 12Nov96 		{
//Old_Code PD 12Nov96 			direntries[di].openfile.currfileindex=offset | 0x80000000;
//Old_Code PD 12Nov96 			link->datasize=blocksize;
//Old_Code PD 12Nov96 			ULong	reqseekpos = direntries[di].openfile.cdstart + (offset/sectorsize);
//Old_Code PD 12Nov96 
//Old_Code PD 12Nov96 			cmdstatus = CDSeek(reqseekpos);
//Old_Code PD 12Nov96 			assert((cmdstatus & 0x0100)&&("CD seek request failed"));
//Old_Code PD 12Nov96 			fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//Old_Code PD 12Nov96 		}
//Old_Code PD 12Nov96 		else
//Old_Code PD 12Nov96 		{
//Old_Code PD 12Nov96 			cmdstatus = CDGetDirectoryEntry(direntryp,namenumberedfile(MyFile)+2);
//Old_Code PD 12Nov96 			assert((cmdstatus==0)&&("CDGetDirectoryEntry failed"));
//Old_Code PD 12Nov96 			direntries[di].openfile.cdstart=direntry.loc_extent;
//Old_Code PD 12Nov96 			link->datasize = direntry.data_len;								//file size
//Old_Code PD 12Nov96 			if (link->datasize>blocksize)
//Old_Code PD 12Nov96 			{
//Old_Code PD 12Nov96 				direntries[di].openfile.number=MyFile;
//Old_Code PD 12Nov96 				direntries[di].openfile.handle=0;
//Old_Code PD 12Nov96 				direntries[di].openfile.maxfilesize=link->datasize;
//Old_Code PD 12Nov96 				direntries[di].openfile.currfileindex=offset | 0x80000000;
//Old_Code PD 12Nov96 				if (offset>link->datasize)
//Old_Code PD 12Nov96 					_Error.EmitSysErr("Index past end of file");
//Old_Code PD 12Nov96 				link->datasize=blocksize;
//Old_Code PD 12Nov96 				ULong	reqseekpos = direntries[di].openfile.cdstart + (offset/sectorsize);
//Old_Code PD 12Nov96 				cmdstatus = CDSeek(reqseekpos);
//Old_Code PD 12Nov96 				assert((cmdstatus & 0x0100)&&("CD seek request failed"));
//Old_Code PD 12Nov96 				fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//Old_Code PD 12Nov96 			}
//Old_Code PD 12Nov96 			else
//Old_Code PD 12Nov96 				assert((offset==0)&&"Can only use offset if buffer smaller than file!");
//Old_Code PD 12Nov96 		}
//Old_Code PD 12Nov96 	}
//Old_Code PD 12Nov96 }


//////////// New version of landscape file manipulation code - should work for Windows too ///////////////

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
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
	FILE*		filehandle;
	FileNum		myfile;
	DirEntry 	direntry,
				*direntryp=&direntry;
	UWord		cmdstatus;

  	for (int fileindex=0;fileindex<MAXCDFILEENTRIES;fileindex++)
	{
		myfile = areafiles[fileindex];

		if (cdfiles[fileindex].number!=myfile)
		{
 			filehandle = opennumberedfile(myfile);

			if (cdfiles[fileindex].number!=INVALIDFILENUM)
				closefile(cdfiles[fileindex].handle);

			cdfiles[fileindex].number=myfile;
			cdfiles[fileindex].handle=filehandle;
			cdfiles[fileindex].maxfilesize=getfilesize(filehandle);

			cmdstatus=CDGetDirectoryEntry(direntryp,namenumberedfile(myfile));

			if (cmdstatus==0)
				cdfiles[fileindex].filebase=direntry.loc_extent;
		}
	}
}

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
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
			fclose (cdfiles[fileindex].handle);
			cdfiles[fileindex].number = INVALIDFILENUM;
			cdfiles[fileindex].handle = NULL;
			cdfiles[fileindex].maxfilesize = 0;
		}
	}
	cdfile.number = INVALIDFILENUM;
	cdfile.handle = NULL;
	cdfile.maxfilesize = 0;
	cdfile.currindex = 0;
	cdfile.actualindex = -1;
	cdfile.seekingtoposition=0;
}

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
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
	if (cdfile.number!=myfile)
	{
		//requested file is not the current one
		//make the requested file the current file

		for (int fileindex=0;;fileindex++)
		{
			if (fileindex==MAXCDFILEENTRIES)
				_Error.EmitSysErr("Requested CD file is not in the current area");

			if (cdfiles[fileindex].number==myfile)	break;
		}

		cdfile.number = cdfiles[fileindex].number;
		cdfile.handle = cdfiles[fileindex].handle;
		cdfile.maxfilesize = cdfiles[fileindex].maxfilesize;
		cdfile.filebase = cdfiles[fileindex].filebase;
	}
	cdfile.currindex = 0;
	cdfile.actualindex = -1;
	cdfile.seekingtoposition=0;									//DAW 19Dec96
}

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
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
	void*	retval = NULL;
	fnum++;
	if ((offset+length)>cdfile.maxfilesize)
	{
		offset-=cdfile.maxfilesize;
		skipread=FALSE;
	}

	if (myfile!=cdfile.number)
	{
		//not the current CD file

		if (cdfile.currindex & 0x80000000)
			_Error.EmitSysErr("Still seeking in different file");
		else
			resetCDfile(myfile);

		if (driveletter!=0)
		{
			if (skipread==TRUE)
			{
				ULong	reqseekpos=cdfile.filebase+(offset/sectorsize);
				UWord	cmdstatus=CDSeek(reqseekpos);
				assert	((cmdstatus&0x0100)&&("CD Seek request failed"));
				cdfile.currindex = offset;
				cdfile.actualindex = offset;
				cdfile.seekingtoposition = 300;					//PD 10Dec96
				return	(retval);
			}
		}
		else
			cdfile.actualindex = -1;
	}

	if (cdfile.seekingtoposition!=0)
	{
		UWord	cmdstatus;

		IOCTLI	ioctli,
				*ioctlip=&ioctli;

		struct	LocHead	lochead,
						*locheadp=&lochead;

		cmdstatus = CDCommand(ioctlip,locheadp,sizeof(LocHead));

		assert((cmdstatus&0x0100)&&("Request for CD head location failed"));

		SLong	disttogo=cdfile.filebase+(cdfile.currindex/sectorsize);

		disttogo -= lochead.locofdrivehead;

		if (disttogo == 0)										//PD 10Dec96
		{
			cdfile.seekingtoposition=0;
		}
		else
		{
			cdfile.seekingtoposition--;
		}
		return (retval);
	}

	if (skipread==FALSE)
	{
		retval = (void*)new unsigned char[length];
		if (retval==NULL)
			_Error.EmitSysErr("Failed to allocate memory for file load");
		seekfilepos(cdfile.handle,offset);
		readfileblock(cdfile.handle,retval,length);
		cdfile.currindex = cdfile.actualindex = offset+length;
		cdfile.seekingtoposition=0;
	}
	else
	{
		int	realindex = cdfile.currindex;

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
				deltaseekpos=realindex-cdfile.actualindex;

			if (deltaseekpos<=DOSFILE_SEEKSTEP)
			{
				retval = (void*)new unsigned char[length];
				if (retval==NULL)
					_Error.EmitSysErr("Failed to allocate memory for file load");
				seekfilepos(cdfile.handle,realindex);			//PD 21Nov96
				readfileblock(cdfile.handle,retval,length);
				cdfile.currindex = cdfile.actualindex = realindex + DOSFILE_SEEKSTEP;
			}
			else
			{
				//Do the skip reads here

				cdfile.actualindex += DOSFILE_SEEKSTEP;
				retval = (void*)new unsigned char[DOSFILE_SECTSIZE];
				if (retval==NULL)
					_Error.EmitSysErr("Failed to allocate memory for skip read");
				seekfilepos(cdfile.handle,cdfile.actualindex);
				readfileblock(cdfile.handle,retval,DOSFILE_SECTSIZE);
				delete ((unsigned char *)retval);
				retval = NULL;
			}
		}
		else
		{
			//Start off a new seek request here!!

			cdfile.currindex = offset | 0x80000000;
			if ((offset+length)>=cdfile.maxfilesize)
				_Error.EmitSysErr("Seek past end of file");
			if (cdfile.actualindex==-1)	//New seek + new file
			{
				seekfilepos(cdfile.handle,cdfile.actualindex);
				cdfile.actualindex = offset;
			}
		}
	}
	return (retval);
}

void fileman::SendCDCommand(UByteP command)					//PD 16Dec96
{
}

//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
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
	void* retval;
	//Do the skip reads here
	cdfile.actualindex += DOSFILE_SEEKSTEP;
	retval = (void*)new unsigned char[DOSFILE_SECTSIZE];
	seekfilepos(cdfile.handle,cdfile.actualindex);
	readfileblock(cdfile.handle,retval,DOSFILE_SECTSIZE);
	delete ((unsigned char *)retval);
}
