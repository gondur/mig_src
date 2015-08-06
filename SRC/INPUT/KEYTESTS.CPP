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
//Filename       keytests.cpp
//System         
//Author         Jim Taylor
//Date           Mon 23 Oct 1995
//Description    Keyboard testing module
//				There are 2 halves... 
//				This is the c - main program task side
//				There is also an asm - ISR side - called keytisr.asm
//------------------------------------------------------------------------------

#include	<dos.h>
#include	"DosDefs.h"
#include	"Files.g"
#include	"fileman.h"
#include	"hardpasm.h"										//ARM 04Jun96

#define	SPECIAL_KEYMAPS	1
#include	"keytest.h"
KeyMapping	*Debug3dMapTable=ThisKeyMapping;


keytests	Key_Tests;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		keytests
//Author		Jim Taylor
//Date			Mon 30 Oct 1995
//
//Description	CONSTRUCTOR
//	//constructor for keyboard tests
	//creates a number of DOS memory buffers & initialises them
	//copies DOS ISR to one of the buffers
	//locks DEX ISR 
	//installs both ISRs		
//
//Inputs		None!
//
//Returns		None!
//
//------------------------------------------------------------------------------
extern	void	DLWRITE(void*,ULong);
#pragma	aux		DLWRITE			=	\
		"mov	ds:[esi],eax"		\
		parm	[esi] [eax]			

	keytests::keytests()
{	
int	i;
	//create a number of DOS memory buffers & initialises them
	//UI queue
	Whole_Screen->GetDOSRAM(hitqueueui,sizeof(UIKeyQueue),0);		//PD 29Nov95
	//3d mapping
	Whole_Screen->GetDOSRAM(reftable3d,sizeof(KeyMap3d),0);			//PD 29Nov95
	//Clear out
	ClearKeyTables();
	//Buffer for DOS mode ISR
	Whole_Screen->GetDOSRAM											//PD 29Nov95
		(isr_data,
		(((ULong) &keytests__dosISRend)-((ULong) &keytests__dosISRstart)),	0);
	isr_code=isr_data;		//first 2 words are segments for tables

	isr_code.off=32;			//code starts at offset 8
	isr_code.flat=((char*)isr_code.flat)+32;

	//copy DOS ISR to the buffer
string
	keyisr=(string) isr_code.flat,
	srcisr=(string) keytests__dosISRcode;
	for	(i=(((ULong) keytests__dosISRend)-((ULong) keytests__dosISRcode));	 i--;)
		*(keyisr++)=*(srcisr++);
UWord*
	keyisrW=(UWord*) isr_data.flat;
	keyisrW[0]=0;
	keyisrW[1]=hitqueueui.seg;
	keyisrW[2]=0;
	keyisrW[3]=reftable3d.seg;
	
	//lock DEX ISR - borrowed this code...
	ULong*	myarea=(ULong*) &keytests__dexISRtables;
	DLWRITE(&myarea[0],(ULong)hitqueueui.flat);
	DLWRITE(&myarea[1],(ULong)reftable3d.flat);
ULong
	locksize,lockstart;
	lockstart=(ULong) &keytests__dexISRstart;
	locksize=((ULong) &keytests__dexISRend)-lockstart;
	DPMIregs r;
	r.l.eax = 0x0600;							/* DPMI lock linear region */
	r.l.ebx = ((ULong) lockstart) >> 16;
	r.l.ecx = ((ULong) lockstart) & 0xFFFF;
	r.l.esi = ((ULong) locksize) >> 16;
	r.l.edi = ((ULong) locksize) & 0xFFFF;
	ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 	int386 (0x31, &r, &r);

	//INSTALL BOTH ISRs
	//Note old vectors
	r.l.eax = 0x0204;							/* DPMI get protected mode vector */
	r.l.ebx = 9;
	ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 	int386 (0x31, &r, &r);
	orig_pm_sel = r.w.cx;
	orig_pm_off = r.l.edx;
	DLWRITE(&myarea[2],(ULong)orig_pm_off);
	DLWRITE(&myarea[3],(ULong)orig_pm_sel);

	r.l.eax = 0x0200;							/* DPMI get real mode vector */
	r.l.ebx = 9;
	ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 	int386 (0x31, &r, &r);
	orig_rm_seg =  r.w.cx;
	orig_rm_off =  r.w.dx;

	keyisrW[4]=orig_rm_off;
	keyisrW[5]=orig_rm_seg;


	//Set new vectors
void __FAR *	fh = (void __far *) keytests__dexISRcode;
	r.l.eax = 0x0205;							/* DPMI set protected mode vector */
	r.l.ebx = 9;
	r.l.ecx = FP_SEG(fh);
	r.l.edx = FP_OFF(fh);
	ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 	int386( 0x031, &r, &r);

	r.l.eax = 0x0201;							/* DPMI set real mode vector */
	r.l.ebx = 9;
	r.l.ecx = isr_code.seg;
	r.l.edx = isr_code.off;
	ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 	int386 (0x31, &r, &r);

//TEST CODE

	RegUIConv((FileNum) 0);
	InsertUIKeyThru=InsertUIKey;
	KeyFake3dThru=KeyFake3d;
//DeadCode JIM 31Oct95 UIKeyEvent	mykeyevent,prevkeyevent;
//DeadCode JIM 31Oct95 
//DeadCode JIM 31Oct95 UByte	*screen=(UByte*) 0xB0000L;
//DeadCode JIM 31Oct95 	while (GetUIKey(mykeyevent)==FALSE) screen[0]++;
//DeadCode JIM 31Oct95 	while (mykeyevent.keycode!=1)
//DeadCode JIM 31Oct95 	{
//DeadCode JIM 31Oct95 		if (mykeyevent.keyhit==KEYHELD)
//DeadCode JIM 31Oct95 			 screen[2*mykeyevent.keycode]++;
//DeadCode JIM 31Oct95 		else
//DeadCode JIM 31Oct95 		if (mykeyevent.keyhit==KEYHIT)
//DeadCode JIM 31Oct95 			 screen[2*mykeyevent.keycode+320]++;
//DeadCode JIM 31Oct95 		else
//DeadCode JIM 31Oct95 			 screen[2*mykeyevent.keycode+320]--;
//DeadCode JIM 31Oct95 
//DeadCode JIM 31Oct95 		prevkeyevent=mykeyevent;
//DeadCode JIM 31Oct95 		while (GetUIKey(mykeyevent)==FALSE) screen[0]++;
//DeadCode JIM 31Oct95 	}
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		keytests (destructor)
//Author		Jim Taylor
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	keytests::~keytests()
{	//destructor for keyboard tests
	//disinstalls both ISRs
	//unlocks DEX ISR
	//frees lumps of memory
	//disinstall both ISRs
	DPMIregs r;
	r.l.eax = 0x0205;							/* DPMI set protected mode vector */
	r.l.ebx = 9;
	r.l.ecx = orig_pm_sel;
	r.l.edx = orig_pm_off;
	ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 	int386 (0x31, &r, &r);

	r.l.eax = 0x0201;							/* DPMI set real mode vector */
	r.l.ebx = 9;
	r.l.ecx = orig_rm_seg;
	r.l.edx = orig_rm_off;
	ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 	int386 (0x31, &r, &r);

	//unlock DEX ISR
ULong
	locksize,lockstart;
	lockstart=(ULong) keytests__dexISRstart;
	locksize=((ULong) keytests__dexISRend)-lockstart;
	r.l.eax = 0x0601;							/* DPMI unlock linear region */
	r.l.ebx = ((ULong) lockstart) >> 16;
	r.l.ecx = ((ULong) lockstart) & 0xFFFF;
	r.l.esi = ((ULong) locksize) >> 16;
	r.l.edi = ((ULong) locksize) & 0xFFFF;
	ASM_DEXint31(&r);
//DeadCode ARM 04Jun96 	int386 (0x31, &r, &r);

	//frees lumps of memory
	Whole_Screen->FreeDOSRAM(hitqueueui);							//PD 29Nov95
	Whole_Screen->FreeDOSRAM(reftable3d);							//PD 29Nov95
	Whole_Screen->FreeDOSRAM(isr_data);								//PD 29Nov95

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearKeyTables
//				(private)
//Author		Jim Taylor
//Date			Mon 30 Oct 1995
//
//Description	Clears out data structures for keyboard- discards unused presses
//
//Inputs		none
//
//Returns		none
//
//------------------------------------------------------------------------------
void	keytests::ClearKeyTables()
{

int	i,j;
	//First, disable both keyboard systems
UIKeyQueue*
	keyqueue=(UIKeyQueue*)	hitqueueui.flat;
	keyqueue->active=FALSE;
KeyMap3d*
	keymap=(KeyMap3d*) reftable3d.flat;
	keymap->active=FALSE;

	//now zero everything in queue

	keyqueue->currshifts=0;
	keyqueue->addref=0;	//you may add when they are equal.
						//You can not add if they will become equal
	keyqueue->takeref=0;	//you may not take when they are equal
	keyqueue->queuesize=MAXqueuesize;
	for (i=16;i--;)
		keyqueue->keyholds[i]=0;

	//now zero everything in 3d system

	keymap->currshifts=0;
	for (i=16;i--;)
		keymap->keyholds[i]=0;
	for	(i=128;i--;)
		for (j=8;j--;)
			keymap->mappings[i][j]=0;
	for (i=(TOTALKEYBITFLAGS+7)/4;i--;)//2 bits per key			//RDH 15Sep97
//Old_Code PD 18Nov97 	for (i=(TOTALKEYBITFLAGS+7)/8;i--;)
		keymap->bitflags[i]=0;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Reg3dConv
//Author		Jim Taylor
//Date			Mon 30 Oct 1995
//
//Description	Register a new conversion table
//
//Inputs		filenum:	table containing conversion
//
//Returns		none
//
//------------------------------------------------------------------------------
void	keytests::Reg3dConv(FileNum	filenum)
{
	if (filenum)
	{
fileblock
		tmp(filenum);
//This file is made up of word pairs: 
//1st word indexes the mappings array by 2 bytes - 0-128,0-7. 
//2nd word indexes the bitflags by bit index. Always even. 2 bits per mapping.
//
		Reg3dConv((KeyMapping*) getdata(tmp),getsize(tmp)/4);
	}
	else
	{
		ClearKeyTables();
		((KeyMap3d*) reftable3d.flat)->active=TRUE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Reg3dConv
//Author		Jim Taylor
//Date			Mon 30 Oct 1995
//
//Description	maps 1 3d keypress manually
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	keytests::Reg3dConv(KeyMapping* mapreq,int	i)
{
	ClearKeyTables();
KeyMap3d*
	keymap=(KeyMap3d*) reftable3d.flat;
	while (i--)
	{
		keymap->mappings[mapreq->scancode][mapreq->shiftstate]=mapreq->bitflag;
		mapreq++;
		breakif(mapreq->scancode==0);
	}
	((KeyMap3d*) reftable3d.flat)->active=TRUE;
	ModeIs3D=TRUE;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RegUIConv
//Author		Jim Taylor
//Date			Mon 30 Oct 1995
//
//Description	Register a userinterface keyboard conversion
//				This will be a stack of converters, starting with the
//				main user-interface keys.
//
//Inputs		filenum: translation list
//
//Returns	
//
//------------------------------------------------------------------------------
void	keytests::RegUIConv(FileNum )	//filenum)
{
	if (((UIKeyQueue*)	hitqueueui.flat)->active==FALSE)
		ClearKeyTables();
//This file registers a foreground translation buffer rather than an interrupt feature
//So I will ignore for now, and just activate the interrupt service!
	((UIKeyQueue*)	hitqueueui.flat)->active=TRUE;
	ModeIs3D=FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnRegUIConv
//Author		Jim Taylor
//Date			Mon 30 Oct 1995
//
//Description	Deregisters keyboard mapping for user interface
//				The user interface mappings are a stack
//
//Inputs		none
//
//Returns		none
//
//------------------------------------------------------------------------------
void	keytests::UnRegUIConv()
{

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetUIKey
//Author		Jim Taylor
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	keytests::GetUIKey(UIKeyEvent& returnedevent)
{
UIKeyQueue*
	keyqueue=(UIKeyQueue*)	hitqueueui.flat;
int	i;
	{	_disable ();
		i=keyqueue->addref - keyqueue->takeref;
//TempCode JIM 30Jan96 char*	B000=(char*) 0xB0000;
//TempCode PD 06Dec95 		B000[160*20]=(char) (keyqueue->addref+'a');
//TempCode PD 06Dec95 		B000[160*20+2]=(char) (keyqueue->takeref+'a');
	}	_enable();
	if	(i==0)	return(FALSE);
	returnedevent=keyqueue->keyqueue[keyqueue->takeref];
	{	_disable ();
		keyqueue->takeref++;
		if (keyqueue->takeref==keyqueue->queuesize)
			keyqueue->takeref=0;
	}	_enable();
	return	(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		mousepos
//Author		Jim Taylor
//Date			Tue 30 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ScreenXY&	keytests::mousepos()
{
UIKeyQueue*
	keyqueue=(UIKeyQueue*)	hitqueueui.flat;
	return(keyqueue->currmouse);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InsertUIKey
//Author		Jim Taylor
//Date			Tue 30 Jan 1996
//
//Description	insert a key press/release event into the key queue
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	keytests::InsertUIKey(UIKeyNoMouse& keyfake)
{
UIKeyQueue*
	keyqueue=(UIKeyQueue*)	hitqueueui.flat;
	{	_disable();
int		oldadd=keyqueue->addref;
int		addref=oldadd+1;

		if (addref==keyqueue->queuesize)
		{
			addref=0;
		}
		if (addref==keyqueue->takeref)
		{
			_enable();											//JIM 21Oct96
			return;
		}
		keyqueue->keyqueue[oldadd].keycode=keyfake.keycode;
		keyqueue->keyqueue[oldadd].keyhit=keyfake.keyhit;
		if (keyfake.keyshifts)
			keyqueue->keyqueue[oldadd].keyshifts=keyfake.keyshifts;
		else
			keyqueue->keyqueue[oldadd].keyshifts=keyqueue->currshifts;
		keyqueue->keyqueue[oldadd].mousecoords=keyqueue->currmouse;
		keyqueue->addref=addref;
	}	_enable();
}

//DeadCode DAW 30Jun96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 30Jun96 //Procedure		BTR
//DeadCode DAW 30Jun96 //Author		Jim Taylor
//DeadCode DAW 30Jun96 //Date			Fri 3 Nov 1995
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Description	bit test and reset assembler macro. 
//DeadCode DAW 30Jun96 //				It will be fun to get this working - not!
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Inputs		pointer to word memory
//DeadCode DAW 30Jun96 //				index to test
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Returns		false=0/true
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //------------------------------------------------------------------------------
//DeadCode DAW 30Jun96 extern	Bool	BITRESET(void*,ULong);
//DeadCode DAW 30Jun96 #pragma	aux		BITRESET		=		\
//DeadCode DAW 30Jun96 		"btr	ds:[esi],ecx"	\
//DeadCode DAW 30Jun96 		"sbb	al,al"		\
//DeadCode DAW 30Jun96 		"neg	al"			\
//DeadCode DAW 30Jun96 		parm	[esi] [ecx]	\
//DeadCode DAW 30Jun96 		value	[al]			\
//DeadCode DAW 30Jun96 
//DeadCode DAW 30Jun96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 30Jun96 //Procedure		BTS
//DeadCode DAW 30Jun96 //Author		Jim Taylor
//DeadCode DAW 30Jun96 //Date			Fri 3 Nov 1995
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Description	bit test and reset assembler macro. 
//DeadCode DAW 30Jun96 //				It will be fun to get this working - not!
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Inputs		pointer to word memory
//DeadCode DAW 30Jun96 //				index to test
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Returns		false=0/true
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //------------------------------------------------------------------------------
//DeadCode DAW 30Jun96 extern	Bool	BITSET(void*,ULong);
//DeadCode DAW 30Jun96 #pragma	aux		BITSET		=		\
//DeadCode DAW 30Jun96 		"bts	ds:[esi],ecx"	\
//DeadCode DAW 30Jun96 		"sbb	al,al"		\
//DeadCode DAW 30Jun96 		"neg	al"			\
//DeadCode DAW 30Jun96 		parm	[esi] [ecx]	\
//DeadCode DAW 30Jun96 		value	[al]			\
//DeadCode DAW 30Jun96 
//DeadCode DAW 30Jun96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 30Jun96 //Procedure		BTS
//DeadCode DAW 30Jun96 //Author		Jim Taylor
//DeadCode DAW 30Jun96 //Date			Fri 3 Nov 1995
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Description	bit test and reset assembler macro. 
//DeadCode DAW 30Jun96 //				It will be fun to get this working - not!
//DeadCode DAW 30Jun96 //Inputs		pointer to word memory
//DeadCode DAW 30Jun96 //				index to test
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Returns		false=0/true
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //------------------------------------------------------------------------------
//DeadCode DAW 30Jun96 extern	Bool	BITTEST(void*,ULong);
//DeadCode DAW 30Jun96 #pragma	aux		BITTEST		=		\
//DeadCode DAW 30Jun96 		"bt		ds:[esi],ecx"	\
//DeadCode DAW 30Jun96 		"sbb	al,al"		\
//DeadCode DAW 30Jun96 		"neg	al"			\
//DeadCode DAW 30Jun96 		parm	[esi] [ecx]	\
//DeadCode DAW 30Jun96 		value	[al]			\
//DeadCode DAW 30Jun96 
//DeadCode DAW 30Jun96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 30Jun96 //Procedure		BTC
//DeadCode DAW 30Jun96 //Author		Jim Taylor
//DeadCode DAW 30Jun96 //Date			Fri 3 Nov 1995
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Description	bit test and reset assembler macro. 
//DeadCode DAW 30Jun96 //				It will be fun to get this working - not!
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Inputs		pointer to word memory
//DeadCode DAW 30Jun96 //				index to test
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //Returns		false=0/true - old value
//DeadCode DAW 30Jun96 //
//DeadCode DAW 30Jun96 //------------------------------------------------------------------------------
//DeadCode DAW 30Jun96 extern	Bool	BITCOMP(void*,ULong);
//DeadCode DAW 30Jun96 #pragma	aux		BITCOMP		=		\
//DeadCode DAW 30Jun96 		"btc	ds:[esi],ecx"	\
//DeadCode DAW 30Jun96 		"sbb	al,al"		\
//DeadCode DAW 30Jun96 		"neg	al"			\
//DeadCode DAW 30Jun96 		parm	[esi] [ecx]	\
//DeadCode DAW 30Jun96 		value	[al]			\
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KeyHeld3d
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	Check if a key is currently held down
//
//Inputs		Alias to test for
//
//Returns		TRUE if not been released
//
//------------------------------------------------------------------------------

Bool	keytests::KeyHeld3d(KeyVal3D keyval)
{
KeyMap3d*
		keymap=(KeyMap3d*) reftable3d.flat;
		if (BITRESET((keymap->bitflags),keyval+1))
			return(TRUE);
		return	(BITTEST((keymap->bitflags),keyval));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KeyPress3d
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	Check if a key has been pressed since last test
//
//Inputs		Alias to test for
//
//Returns		TRUE	if just pressed
//
//------------------------------------------------------------------------------
Bool	keytests::KeyPress3d(KeyVal3D keyval)
{
KeyMap3d*
		keymap=(KeyMap3d*) reftable3d.flat;
		return(BITRESET((keymap->bitflags),keyval+1));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KeyFake3d
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	Fakes a key press to the 3d
//
//Inputs		Alias to fake
//				set or clear bits
//
//Returns		TRUE	if just pressed
//
//------------------------------------------------------------------------------
void	keytests::KeyFake3d(	KeyVal3D keyval,	//combo to fake
								Bool	held,		//set/clear held flag
								Bool	hit)		//set/clear oneshot flag
{
KeyMap3d*
		keymap=(KeyMap3d*) reftable3d.flat;
		if (held)
			BITSET((keymap->bitflags),keyval);
		else
			BITRESET((keymap->bitflags),keyval);
		if (hit)
			BITSET((keymap->bitflags),keyval+1);
		else
			BITRESET((keymap->bitflags),keyval+1);

}
