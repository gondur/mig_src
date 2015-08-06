 // -----------------------------------------------------------------
// File name:  DLL16.C
//
// This is the main DLL source file.  It contains LibMain, the DLL's
// entry point.
//
// Description of functions:
//
//    LibMain          -  This DLL's entry point.  Analogous to WinMain.
//    DLL16PascalCall   -  A function exported by this DLL that uses the
//                        Pascal calling convention
//    DLL16CCall        -  A function exported by this DLL that uses the
//                        C calling convention
//
//
//   Copyright (C) 1993 - 1996 Microsoft Corporation.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
// -----------------------------------------------------------------

#define DLL16NAME	"CRR16.DLL"
#define DLL32NAME	"CDR32.DLL"

#include<windows.h>
#include <memory.h>
#include "cdr16.h"
#include "globals.h"

typedef unsigned char UByte,*UByteP;
typedef signed char SByte,*SByteP;

typedef unsigned short UWord,*UWordP;
typedef signed short SWord,*SWordP;

typedef unsigned long int ULong,*ULongP;
typedef signed long int SLong,*SLongP;

#include "mscdex.h"

#define DOS_STACK_SIZE  2048

typedef struct  DPMIb
{
        ULong   edi;
        ULong   esi;
        ULong   ebp;
        ULong   esp;
        UByte   bl,bh,ebl,ebh;
        UByte   dl,dh,edl,edh;
        UByte   cl,ch,ecl,ech;
        UByte   al,ah,eal,eah;
}
DPMIb;

typedef struct  DPMIw
{
        UWord   di,exdi;
        UWord   si,exsi;
        UWord   bp,exbp;
        UWord   sp,exsp;
        UWord   bx,exbx;
        UWord   dx,exdx;
        UWord   cx,excx;
        UWord   ax,exax;
}
DPMIw;

typedef struct  DPMIl
{
        ULong   edi;
        ULong   esi;
        ULong   ebp;
        ULong   esp;
        ULong   ebx;
        ULong   edx;
        ULong   ecx;
        ULong   eax;
}
DPMIl;

typedef struct  DPMIsb
{
        SLong   edi;
        SLong   esi;
        SLong   ebp;
        SLong   esp;
        SByte   bl,bh,ebl,ebh;
        SByte   dl,dh,edl,edh;
        SByte   cl,ch,ecl,ech;
        SByte   al,ah,eal,eah;
}
DPMIsb;

typedef struct  DPMIsw
{
        SWord   di,exdi;
        SWord   si,exsi;
        SWord   bp,exbp;
        SWord   sp,exsp;
        SWord   bx,exbx;
        SWord   dx,exdx;
        SWord   cx,excx;
        SWord   ax,exax;
}
DPMIsw;

typedef struct  DPMIsl
{
        SLong   edi;    //0
        SLong   esi;    //4
        SLong   ebp;    //8
        SLong   esp;    //12
        SLong   ebx;    //16
        SLong   edx;    //20
        SLong   ecx;    //24
        SLong   eax;    //28
}
DPMIsl;


typedef struct  Ubytereg
{
        UByte   l,h,hl,hh;
}
Ubytereg;

typedef struct  Sbytereg
{
        SByte   l,h,hl,hh;
}
Sbytereg;

typedef struct  DPMIseg
{
        UWord   es,ds,fs,gs,ip,cs,sp,ss;
}
DPMIseg;

typedef enum   Flags
                {
                CF      = 0x0001,       /* carry */
                PF      = 0x0004,       /* parity */
                AF      = 0x0010,       /* auxiliary carry */
                ZF      = 0x0040,       /* zero */
                SF      = 0x0080,       /* sign */
                TF      = 0x0100,       /* trace */
                IF      = 0x0200,       /* interrupt */
                DF      = 0x0400,       /* direction */
                OF      = 0x0800,       /* overflow */
                IOPL=0x3000,    /* overflow */
                NT      = 0x4000        /* overflow */
                }
                Flags;

typedef struct  DPMIregs2
{
        union   {       ULong   edi;    SLong   Edi;    UWord   di;     SWord   Di;};
        union   {       ULong   esi;    SLong   Esi;    UWord   si;     SWord   Si;};
        union   {       ULong   ebp;    SLong   Ebp;    UWord   bp;     SWord   Bp;};
        union   {       ULong   esp2;   SLong   Esp2;   UWord   sp2;SWord       Sp2;};
        union   {       ULong   ebx;    SLong   Ebx;    UWord   bx;     SWord   Bx;     Ubytereg        b;      Sbytereg        B;};
        union   {       ULong   edx;    SLong   Edx;    UWord   dx;     SWord   Dx;     Ubytereg        d;      Sbytereg        D;};
        union   {       ULong   ecx;    SLong   Ecx;    UWord   cx;     SWord   Cx;     Ubytereg        c;      Sbytereg        C;};
        union   {       ULong   eax;    SLong   Eax;    UWord   ax;     SWord   Ax;     Ubytereg        a;      Sbytereg        A;};
        Flags   flags;
        UWord   es,ds,fs,gs,ip,cs,sp,ss;
}
DPMIregs2;

typedef struct  DPMIregs
{
        union   {       DPMIb   b;      DPMIsb  sb;
                                DPMIw   w;      DPMIsw  sw;
                                DPMIl   l;      DPMIsl  sl;
                        };
        Flags   flags;
        DPMIseg s;
}
DPMIregs,FAR *LPDPMIregs;

typedef enum    CdCodes
{
    CD_EXIT=4,
    CD_LOCK=5,
    NORTH=0,
    EAST=1,
    SOUTH=2,
    WEST=3,
    SETAREA=6,
}
CdCodes;


BOOL FAR PASCAL SimulateRM_Int (BYTE bIntNum, LPDPMIregs lpCallStruct);

BOOL SRMI();

typedef struct IOCTLI IOCTLI,FAR *LPIOCTLI;

typedef struct IOCTLO IOCTLO,FAR *LPIOCTLO;

typedef struct LockDoor LockDoor, FAR *LPLockDoor;

typedef struct DevStat DevStat, FAR *LPDEVSTAT;

typedef struct Raddr Raddr, FAR *LPRADDR;

typedef struct dir_entry DirEntry, FAR *LPDIRENTRY;

typedef struct SEEKREQ SEEKREQ, FAR *LPSEEKREQ;


UWord FAR PASCAL GetCDROMDriveLetter(void);

UWord FAR PASCAL GetDevStat(LPDEVSTAT,UWord);

UWord FAR PASCAL CDGetDirectoryEntry(LPDIRENTRY,LPBYTE);

UWord FAR PASCAL CDGetAllFileBases();

BOOL FAR PASCAL __export DllEntryPoint (DWORD dwReason,
                               			WORD  hInst,
                               			WORD  wDS,
                               			WORD  wHeapSize,
                               			DWORD dwReserved1,
                               			WORD  wReserved2);

BOOL FAR PASCAL thk_ThunkConnect16(LPSTR pszDll16,
                                   LPSTR pszDll32,
                                   WORD  hInst,
                                   DWORD dwReason);

HANDLE ghDLLInst;

LPBYTE	lpRealModeBuffer,lpProtModeBuffer;
DWORD	gdaBuffer;

static	char	szKeyFile[]="\\MIG\\LANDSCAP\\DIR.DIR";
static	char	szArea1N[]="\\MIG\\LANDSCAP\\NORTH.DAT";
static	char	szArea1E[]="\\MIG\\LANDSCAP\\EAST.DAT";
static	char	szArea1S[]="\\MIG\\LANDSCAP\\SOUTH.DAT";
static	char	szArea1W[]="\\MIG\\LANDSCAP\\WEST.DAT";

static	UWord driveletter=0;
static	SLong area1base[4];

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LibMain
//Author		Paul.   
//Date			Fri 18 Sep 1998
//
//Params  		hInstance   ==  The handle to the DLL's instance.
//           	wDataSeg    ==  Basically it is a pointer to the DLL's
//                           data segment.
//           	wHeapSize   ==  Size of the DLL's heap in bytes.
//           	lpszCmdLine ==  The command line passed to the DLL
//                           by Windows.  This is rarely used.
//
//Returns  		1 indicating DLL initialization is successful.
//------------------------------------------------------------------------------
int FAR PASCAL LibMain (HANDLE hInstance,
                        WORD   wDataSeg,
                        WORD   wHeapSize,
                        LPSTR  lpszCmdLine)
{
    ghDLLInst=hInstance;

    if (wHeapSize!=0)	UnlockData (0);	// If DLL data seg is MOVEABLE

    return (1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DllEntryPoint
//Author		Paul.   
//Date			Fri 18 Sep 1998
//------------------------------------------------------------------------------
BOOL FAR PASCAL __export DllEntryPoint (DWORD dwReason,
                               			WORD  hInst,
                               			WORD  wDS,
                               			WORD  wHeapSize,
                               			DWORD dwReserved1,
                               			WORD  wReserved2)
{
    if (!thk_ThunkConnect16(DLL16NAME,DLL32NAME,hInst,dwReason))
    {
        return FALSE;
    }
    return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LockCD16
//Author		Paul.   
//Date			Fri 18 Sep 1998
//------------------------------------------------------------------------------
void FAR PASCAL LockCD16()
{
	DPMIregs        regs;
	LPDPMIregs      lpRegs;
	LPIOCTLO        lpRIoctlo,
					lpPIoctlo;
	LPLockDoor      lpRLockDoor,
					lpPLockDoor;

	lpPIoctlo=(LPIOCTLO)lpProtModeBuffer;
	lpRIoctlo=(LPIOCTLO)lpRealModeBuffer;

	lpPLockDoor=(LPLockDoor)(lpProtModeBuffer+sizeof(struct IOCTLO));
	lpRLockDoor=(LPLockDoor)(lpRealModeBuffer+sizeof(struct IOCTLO));

	_fmemset(lpProtModeBuffer,0,sizeof(IOCTLI));
	_fmemset(lpPLockDoor,0,sizeof(LockDoor));

	lpRegs=&regs;

	regs.flags=0;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=
	regs.l.esi=regs.l.edi=regs.l.ebp=0;

	regs.s.ds=regs.s.es=regs.s.fs=regs.s.gs=HIWORD(lpRegs);

	regs.s.ss=HIWORD(lpRealModeBuffer);
	regs.l.esp=LOWORD(lpRealModeBuffer)+DOS_STACK_SIZE;

	lpPIoctlo->mediadescriptor=0;
	lpPIoctlo->startsector=0;
	lpPIoctlo->requestedvol=0;
	lpPIoctlo->unit=0;
	lpPIoctlo->length=sizeof(struct IOCTLI);
	lpPIoctlo->function=12;

	lpPIoctlo->status=0;

	lpPLockDoor->request=OREQ_LOCKUNLOCKDOOR;
	lpPLockDoor->lockfunction=1;             //LOCK!!

	lpPIoctlo->bytestotransfer=sizeof(struct LockDoor);
	lpPIoctlo->transferaddr_seg=HIWORD(lpRLockDoor);
	lpPIoctlo->transferaddr_off=LOWORD(lpRLockDoor);

	regs.w.ax=0x1510;
	regs.w.cx=driveletter;
	regs.l.ebx=LOWORD(lpRIoctlo);
	regs.s.es=
	regs.s.ds=
	regs.s.fs=
	regs.s.gs=HIWORD(lpRIoctlo);

//DeadCode PD 23Sep98 	(void )SimulateRM_Int(0x2F,lpRegs);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnlockCD16
//Author		Paul.   
//Date			Fri 18 Sep 1998
//------------------------------------------------------------------------------
void FAR PASCAL UnlockCD16()
{
	DPMIregs        regs;
	LPDPMIregs      lpRegs;
	LPIOCTLO        lpRIoctlo,
					lpPIoctlo;
	LPLockDoor      lpRLockDoor,
					lpPLockDoor;

	lpPIoctlo=(LPIOCTLO)lpProtModeBuffer;
	lpRIoctlo=(LPIOCTLO)lpRealModeBuffer;

	lpPLockDoor=(LPLockDoor)(lpProtModeBuffer+sizeof(struct IOCTLO));
	lpRLockDoor=(LPLockDoor)(lpRealModeBuffer+sizeof(struct IOCTLO));

	_fmemset(lpProtModeBuffer,0,sizeof(IOCTLI));
	_fmemset(lpPLockDoor,0,sizeof(LockDoor));

	lpRegs=&regs;

	regs.flags=0;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=
	regs.l.esi=regs.l.edi=regs.l.ebp=0;

	regs.s.ds=regs.s.es=regs.s.fs=regs.s.gs=HIWORD(lpRegs);

	regs.s.ss=HIWORD(lpRealModeBuffer);
	regs.l.esp=LOWORD(lpRealModeBuffer)+DOS_STACK_SIZE;

	lpPIoctlo->mediadescriptor=0;
	lpPIoctlo->startsector=0;
	lpPIoctlo->requestedvol=0;
	lpPIoctlo->unit=0;
	lpPIoctlo->length=sizeof(struct IOCTLI);
	lpPIoctlo->function=12;

	lpPIoctlo->status=0;

	lpPLockDoor->request=OREQ_LOCKUNLOCKDOOR;
	lpPLockDoor->lockfunction=0;             //UNLOCK!!

	lpPIoctlo->bytestotransfer=sizeof(struct LockDoor);
	lpPIoctlo->transferaddr_seg=HIWORD(lpRLockDoor);
	lpPIoctlo->transferaddr_off=LOWORD(lpRLockDoor);

	regs.w.ax=0x1510;
	regs.w.cx=driveletter;
	regs.l.ebx=LOWORD(lpRIoctlo);
	regs.s.es=
	regs.s.ds=
	regs.s.fs=
	regs.s.gs=HIWORD(lpRIoctlo);

	(void )SimulateRM_Int(0x2F,lpRegs);

//DeadCode PD 23Sep98 	return (lpPIoctlo->status);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure             SimulateRM_Int
//Author                Paul.   
//Date                  Fri 13 Dec 1996
//
//Description   
//
//Inputs                
//
//Returns       
//
//------------------------------------------------------------------------------
BOOL FAR PASCAL SimulateRM_Int (BYTE bIntNum, LPDPMIregs lpCallStruct)
{
	BOOL fRetVal;

	_asm {
		push di
		mov ax,0300h
		mov bl,bIntNum
		mov bh,01h
		xor cx,cx
		les di,lpCallStruct
		int 31h
		mov ax,0
		jc END1
		mov ax,1
END1:
		pop di
		mov fRetVal,ax
	}
	return fRetVal;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetCDROMDriveLetter
//Author		Paul.   
//Date			Fri 18 Sep 1998
//------------------------------------------------------------------------------
UWord FAR PASCAL GetCDROMDriveLetter()
{
    DevStat     devstat;
    LPDEVSTAT   lpDevStat;
    DPMIregs    regs;
    LPDPMIregs  lpRegs;
    DirEntry    direntry;
    LPDIRENTRY  lpDirEntry;
    LPBYTE		lpKeyFile;
    UWord       cmdstatus;

    BOOL		cdisours;

    cdisours=FALSE;

	for (driveletter=0;driveletter<26;driveletter+=1)
	{
		lpRegs=&regs;

		regs.flags=0;

		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=
		regs.l.esi=regs.l.edi=regs.l.ebp=0;

		regs.s.ds=regs.s.es=regs.s.fs=regs.s.gs=HIWORD(lpRegs);

		regs.s.ss=HIWORD(lpRealModeBuffer);
		regs.l.esp=LOWORD(lpRealModeBuffer)+DOS_STACK_SIZE;
        
		regs.w.ax=0x150B;
		regs.w.cx=driveletter;

		SimulateRM_Int(0x2F,lpRegs);

		if (regs.w.bx==0xadad && regs.w.ax!=0)
		{
			lpDevStat=&devstat;
            
			cmdstatus=GetDevStat(lpDevStat,driveletter);
            
			if ((lpDevStat->deviceparameters & 0x801)==0)
			{
				lpDirEntry=&direntry;

				lpKeyFile=&szKeyFile[0];
               
				cmdstatus=CDGetDirectoryEntry(lpDirEntry,lpKeyFile);
                
				if (cmdstatus==0)
				{
					cdisours=TRUE;
					break;
				}
			}
		}
	}

	if (cdisours==FALSE)
		return 0;

	return driveletter;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDevStat
//Author		Paul.   
//Date			Fri 18 Sep 1998
//------------------------------------------------------------------------------
UWord FAR PASCAL GetDevStat(LPDEVSTAT lpDevStat,UWord driveno)
{
	DPMIregs        regs;
	LPDPMIregs      lpRegs;
	LPIOCTLI        lpRIoctli,
                    lpPIoctli;
	LPDEVSTAT       lpRDevStat,
                    lpPDevStat;

	lpPIoctli=(LPIOCTLI)lpProtModeBuffer;
	lpRIoctli=(LPIOCTLI)lpRealModeBuffer;

	lpPDevStat=(LPDEVSTAT)(lpProtModeBuffer+sizeof(struct IOCTLI));
	lpRDevStat=(LPDEVSTAT)(lpRealModeBuffer+sizeof(struct IOCTLI));

	_fmemset(lpProtModeBuffer,0,sizeof(IOCTLI));
	_fmemset(lpPDevStat,0,sizeof(DevStat));

	lpRegs=&regs;

	regs.flags=0;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=
	regs.l.esi=regs.l.edi=regs.l.ebp=0;

	regs.s.ds=regs.s.es=regs.s.fs=regs.s.gs=HIWORD(lpRegs);

	regs.s.ss=HIWORD(lpRealModeBuffer);
	regs.l.esp=LOWORD(lpRealModeBuffer)+DOS_STACK_SIZE;

	lpPIoctli->mediadescriptor=0;
	lpPIoctli->startsector=0;
	lpPIoctli->requestedvol=0;
	lpPIoctli->unit=0;
	lpPIoctli->length=sizeof(struct IOCTLI);
	lpPIoctli->function=0x3;

	lpPIoctli->status=0;

	lpPDevStat->request=IREQ_DEVSTAT;

	lpPIoctli->bytestotransfer=sizeof(struct DevStat);
	lpPIoctli->transferaddr_seg=HIWORD(lpRDevStat);
	lpPIoctli->transferaddr_off=LOWORD(lpRDevStat);

	regs.w.ax=0x1510;
	regs.w.cx=driveno;
	regs.l.ebx=LOWORD(lpRIoctli);
	regs.s.es=
	regs.s.ds=
	regs.s.fs=
	regs.s.gs=HIWORD(lpRIoctli);

	(void )SimulateRM_Int(0x2F,lpRegs);

	//Return contents of devstat structure to caller

	_fmemcpy(lpDevStat,lpPDevStat,sizeof(DevStat));

	return (lpPIoctli->status);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CDGetDirectoryEntry
//Author		Paul.   
//Date			Fri 18 Sep 1998
//------------------------------------------------------------------------------
UWord FAR PASCAL CDGetDirectoryEntry(LPDIRENTRY lpDirEntry,LPBYTE lpFilename)
{
	DPMIregs    regs;
	LPDPMIregs  lpRegs;

	LPDIRENTRY  lpRDirEntry,
				lpPDirEntry;

	LPBYTE		lpRFilename,
				lpPFilename;

	SLong		direntrysize;

	lpPDirEntry=(LPDIRENTRY)(lpProtModeBuffer);
	lpRDirEntry=(LPDIRENTRY)(lpRealModeBuffer);

	direntrysize=sizeof(struct dir_entry);

	lpPFilename=(LPBYTE)(lpProtModeBuffer+direntrysize);
	lpRFilename=(LPBYTE)(lpRealModeBuffer+direntrysize);

	lpRegs=&regs;

	regs.flags=0;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=
	regs.l.esi=regs.l.edi=regs.l.ebp=0;

	regs.s.ds=regs.s.es=regs.s.fs=regs.s.gs=HIWORD(lpRegs);

	regs.s.ss=HIWORD(lpRealModeBuffer);
	regs.l.esp=LOWORD(lpRealModeBuffer)+DOS_STACK_SIZE;

	_fmemcpy(lpPDirEntry,lpDirEntry,sizeof(struct dir_entry));

	//copy the filename string down to DOS RAM

	for(;;)
	{
		*lpPFilename=*lpFilename;

		if (*lpPFilename==0)    break;

		lpPFilename++;
		lpFilename++;
	}

	regs.w.ax=0x150F;
	regs.b.cl=(BYTE)driveletter;
	regs.b.ch=0x01;                         //Fill generic directory structure

	//pointer to DirEntry structure to fill in

	regs.l.esi=HIWORD(lpRDirEntry);
	regs.l.edi=LOWORD(lpRDirEntry);

	//pointer to NULL terminated filename string

	regs.l.ebx=LOWORD(lpRFilename);

	regs.s.es=
	regs.s.ds=
	regs.s.fs=
	regs.s.gs=HIWORD(lpRFilename);

	(void )SimulateRM_Int(0x2F,lpRegs);

	//Return contents of direntry structure to caller
        
	_fmemcpy(lpDirEntry,lpPDirEntry,sizeof(struct dir_entry));

	if (regs.flags & CF)
		return (regs.w.ax);     //Error code if carry set

	return (0);
}


//real CD access routines

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitCDFS16
//Author		Paul.   
//Date			Tue 22 Sep 1998
//
//Description	Allocates DOS RAM buffer for all CD access calls.
//				Scans for a CDROM drive containing 'KeyFileName'
//				if 'KeyFileName' found then
//					lock the CD drive door
//					return the CD drive letter
//				else
//					return 0x0000
//
//Returns		CDROM drive letter OR 0x0000 if failed
//
//------------------------------------------------------------------------------
UWord FAR PASCAL __export InitCDFS16()
{
	UWord driveno;

    gdaBuffer=GlobalDosAlloc(DOS_STACK_SIZE);

    lpRealModeBuffer=(LPBYTE)MAKELONG(0,HIWORD(gdaBuffer));
    
    lpProtModeBuffer=(LPBYTE)MAKELONG(0,LOWORD(gdaBuffer));

	driveno=GetCDROMDriveLetter();

	if (driveno!=0)
	{
	 	LockCD16();
		(void)CDGetAllFileBases();
		driveno+=(UWord)'A';
	}

	return driveno;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExitCDFS16
//Author		Paul.   
//Date			Tue 22 Sep 1998
//
//Description	Unlocks CDROM drive door and frees DOS RAM allocated for
//				CDROM access
//
//------------------------------------------------------------------------------
void FAR PASCAL __export ExitCDFS16()
{
	if (driveletter!=0)
		UnlockCD16();

	GlobalDosFree(gdaBuffer);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SeekToLocation
//Author		Paul.   
//Date			Tue 22 Sep 1998
//
//Description	Seeks to position 'seekPos' in file 'hFile'
//
//Inputs		hFile - handle to file as returned by 'AddCDAreaFile'
//				seekPos - offset from the start of the file to seek to
//
//Returns		TRUE if success, otherwise returns FALSE
//
//------------------------------------------------------------------------------
BOOL FAR PASCAL __export SeekToLocation16(UWord filenum,ULong position)
{

	DPMIregs        regs;
	LPDPMIregs      lpRegs;
	LPSEEKREQ		lpRSeekreq,
					lpPSeekreq;

	lpRegs=&regs;

	regs.flags=0;

	regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=
	regs.l.esi=regs.l.edi=regs.l.ebp=0;

	regs.s.ds=regs.s.es=regs.s.fs=regs.s.gs=HIWORD(lpRegs);

	regs.s.ss=HIWORD(lpRealModeBuffer);
	regs.l.esp=LOWORD(lpRealModeBuffer)+DOS_STACK_SIZE;

	lpRSeekreq=(LPSEEKREQ)lpRealModeBuffer;
	lpPSeekreq=(LPSEEKREQ)lpProtModeBuffer;

	_fmemset(lpPSeekreq,0,sizeof(SEEKREQ));

	//convert the offset to CD block size

	position /= 2048;

	//add the base location for this file

	position += area1base[filenum];

	lpPSeekreq->addressingmode=0;
	lpPSeekreq->transferaddr_seg=0;
	lpPSeekreq->transferaddr_off=0;
	lpPSeekreq->unit=0;
	lpPSeekreq->length=sizeof(struct SEEKREQ);
	lpPSeekreq->function=131;
	lpPSeekreq->noofsectorstoread=0;
	lpPSeekreq->startsectorno=position;
	lpPSeekreq->status=0;

	regs.w.ax=0x1510;
	regs.w.cx=driveletter;

	//pointer to SEEKREQ structure to fill in

	regs.l.ebx=LOWORD(lpRSeekreq);

	regs.s.es=
	regs.s.ds=
	regs.s.fs=
	regs.s.gs=HIWORD(lpRSeekreq);

	(void )SimulateRM_Int(0x2F,lpRegs);

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CDGetAllFileBases
//Author		Paul.   
//Date			Thu 24 Sep 1998
//------------------------------------------------------------------------------
UWord FAR PASCAL CDGetAllFileBases()
{
	DirEntry        direntry;
	LPDIRENTRY      lpDirEntry;
	UWord           cmdstatus;
	LPBYTE          lpFilename;

	lpDirEntry=&direntry;

	//Fill in the base locations for all eight area files

	lpFilename=&szArea1N[0];

	cmdstatus=CDGetDirectoryEntry(lpDirEntry,lpFilename);

	area1base[0]=lpDirEntry->loc_extent;

	lpFilename=&szArea1E[0];

	cmdstatus=CDGetDirectoryEntry(lpDirEntry,lpFilename);

	area1base[1]=lpDirEntry->loc_extent;

	lpFilename=&szArea1S[0];

	cmdstatus=CDGetDirectoryEntry(lpDirEntry,lpFilename);

	area1base[2]=lpDirEntry->loc_extent;

	lpFilename=&szArea1W[0];

	cmdstatus=CDGetDirectoryEntry(lpDirEntry,lpFilename);

	area1base[3]=lpDirEntry->loc_extent;

	return(1);
}

