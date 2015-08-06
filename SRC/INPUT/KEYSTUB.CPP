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
//Filename       keystub.cpp
//System         
//Author         Andy McRea
//Date           Tue 4 Jun 1996
//Description    Keyboard testing module stub
//------------------------------------------------------------------------------

#include	<dos.h>
//#include	"stdafx.h"
#include	"DosDefs.h"

#include	"Files.g"
#include	"fileman.h"

#include	"hardpasm.h"										//ARM 04Jun96
#pragma message ("Keystub")

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
#ifdef __WATCOMC__
#pragma	aux		DLWRITE			=	\
		"mov	ds:[esi],eax"		\
		parm	[esi] [eax]			
#else
#ifdef __MSVC__
inline	void	DLWRITE(void* num1,ULong num2)
{
    __asm
    {
		mov esi,num1;
		mov eax,num2;
		mov ds:[esi],eax;
    }
}

#endif
#endif

	keytests::keytests()
{	
int	i;
	//create a number of DOS memory buffers & initialises them
	//UI queue
	hitqueueui.flat=new UIKeyQueue;
	//3d mapping
	reftable3d.flat=new KeyMap3d;
	//Clear out
	ClearKeyTables();

	//Buffer for DOS mode ISR

	//copy DOS ISR to the buffer

	//lock DEX ISR - borrowed this code...

	//INSTALL BOTH ISRs
	//Note old vectors

	//Set new vectors

//TEST CODE

//	RegUIConv((FileNum) 0);
//	InsertUIKeyThru=InsertUIKey;
	KeyFake3dThru=KeyFake3d;
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

	//unlock DEX ISR

	//frees lumps of memory

	delete	(UIKeyQueue*)	hitqueueui.flat;
	delete	(KeyMap3d*)		reftable3d.flat;
	
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
	for	(i=KeyMap3d::MAXKEYS;i--;)
		for (j=8;j--;)
			keymap->mappings[i][j]=0;
	for (i=(TOTALKEYBITFLAGS+7)/4;i--;)							//RJS 29Jan98
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
//void	keytests::Reg3dConv(FileNum	filenum)
//{
//	if (filenum)
//	{
//fileblock
//		tmp(filenum);
//This file is made up of word pairs: 
//1st word indexes the mappings array by 2 bytes - 0-128,0-7. 
//2nd word indexes the bitflags by bit index. Always even. 2 bits per mapping.
//
//		Reg3dConv((KeyMapping*) getdata(tmp),getsize(tmp)/4);
//	}
//	else
//	{
//		ClearKeyTables();
//		((KeyMap3d*) reftable3d.flat)->active=TRUE;
//	}
//} 

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
static __int64	lastkeychecksum=0;
void	keytests::Reg3dConv(KeyMapping* mapreq,int	i)
{
	ClearKeyTables();
KeyMap3d*
	keymap=(KeyMap3d*) reftable3d.flat;
	int	keychecksum=0;
	while (i--)
	{
		keychecksum=keychecksum*2+(keychecksum>>63)+mapreq->scancode+mapreq->shiftstate+mapreq->bitflag;
		keymap->mappings[mapreq->scancode][mapreq->shiftstate]=mapreq->bitflag;
		mapreq++;
		breakif(mapreq->bitflag==0);
	}
	((KeyMap3d*) reftable3d.flat)->active=TRUE;
	ModeIs3D=TRUE;
	if (lastkeychecksum==0)
		lastkeychecksum=keychecksum;
	else
		if(lastkeychecksum!=keychecksum)
			_Error.EmitSysErr("Key table has changed between loads???");
}
void keytests::Reg3dConv(FileNum f)
{
	fileblock b=f;
	Reg3dConv((KeyMapping*)b.getdata(),b.getsize()/sizeof(KeyMapping));


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
//	if (((UIKeyQueue*)	hitqueueui.flat)->active==FALSE)
//		ClearKeyTables();
//This file registers a foreground translation buffer rather than an interrupt feature
//So I will ignore for now, and just activate the interrupt service!
//	((UIKeyQueue*)	hitqueueui.flat)->active=TRUE;
//	ModeIs3D=FALSE;
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
//UIKeyQueue*
	//keyqueue=(UIKeyQueue*)	hitqueueui.flat;
//int	i;
	//{	_disable ();
		//i=keyqueue->addref - keyqueue->takeref;
//TempCode JIM 30Jan96 char*	B000=(char*) 0xB0000;
//TempCode PD 06Dec95 		B000[160*20]=(char) (keyqueue->addref+'a');
//TempCode PD 06Dec95 		B000[160*20+2]=(char) (keyqueue->takeref+'a');
	//}	_enable();
	//if	(i==0)	return(FALSE);
	//returnedevent=keyqueue->keyqueue[keyqueue->takeref];
	//{	_disable ();
		//keyqueue->takeref+=1;
		//if (keyqueue->takeref==keyqueue->queuesize)
			//keyqueue->takeref=0;
	//}	_enable();
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
//ScreenXY&	keytests::mousepos()
//{
//UIKeyQueue*
//	keyqueue=(UIKeyQueue*)	hitqueueui.flat;
//	return(keyqueue->currmouse);
//}

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
//UIKeyQueue*
//	keyqueue=(UIKeyQueue*)	hitqueueui.flat;
//	{	_disable();
//int		oldadd=keyqueue->addref;
//int		addref=oldadd+1;
//		if (addref==keyqueue->queuesize)
//			addref=0;
//		if (addref==keyqueue->takeref)
//			return;
//		keyqueue->keyqueue[oldadd].keycode=keyfake.keycode;
//		keyqueue->keyqueue[oldadd].keyhit=keyfake.keyhit;
//		if (keyfake.keyshifts)
//			keyqueue->keyqueue[oldadd].keyshifts=keyfake.keyshifts;
//		else
//			keyqueue->keyqueue[oldadd].keyshifts=keyqueue->currshifts;
//		keyqueue->keyqueue[oldadd].mousecoords=keyqueue->currmouse;
//		keyqueue->addref=addref;
//	}	_enable();
} 

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BTR
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	bit test and reset assembler macro. 
//				It will be fun to get this working - not!
//
//Inputs		pointer to word memory
//				index to test
//
//Returns		false=0/true
//
//------------------------------------------------------------------------------
//DeadCode ARM 04Jun96 extern	Bool	BITRESET(void*,ULong);
//DeadCode ARM 04Jun96 #pragma	aux		BITRESET		=		\
//DeadCode ARM 04Jun96 		"btr	ds:[esi],ecx"	\
//DeadCode ARM 04Jun96 		"sbb	al,al"		\
//DeadCode ARM 04Jun96 		"neg	al"			\
//DeadCode ARM 04Jun96 		parm	[esi] [ecx]	\
//DeadCode ARM 04Jun96 		value	[al]			\

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BTS
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	bit test and reset assembler macro. 
//				It will be fun to get this working - not!
//
//Inputs		pointer to word memory
//				index to test
//
//Returns		false=0/true
//
//------------------------------------------------------------------------------
//DeadCode ARM 04Jun96 extern	Bool	BITSET(void*,ULong);
//DeadCode ARM 04Jun96 #pragma	aux		BITSET		=		\
//DeadCode ARM 04Jun96 		"bts	ds:[esi],ecx"	\
//DeadCode ARM 04Jun96 		"sbb	al,al"		\
//DeadCode ARM 04Jun96 		"neg	al"			\
//DeadCode ARM 04Jun96 		parm	[esi] [ecx]	\
//DeadCode ARM 04Jun96 		value	[al]			\

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BTS
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	bit test and reset assembler macro. 
//				It will be fun to get this working - not!
//Inputs		pointer to word memory
//				index to test
//
//Returns		false=0/true
//
//------------------------------------------------------------------------------
//DeadCode ARM 04Jun96 extern	Bool	BITTEST(void*,ULong);
//DeadCode ARM 04Jun96 #pragma	aux		BITTEST		=		\
//DeadCode ARM 04Jun96 		"bt		ds:[esi],ecx"	\
//DeadCode ARM 04Jun96 		"sbb	al,al"		\
//DeadCode ARM 04Jun96 		"neg	al"			\
//DeadCode ARM 04Jun96 		parm	[esi] [ecx]	\
//DeadCode ARM 04Jun96 		value	[al]			\

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BTC
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	bit test and reset assembler macro. 
//				It will be fun to get this working - not!
//
//Inputs		pointer to word memory
//				index to test
//
//Returns		false=0/true - old value
//
//------------------------------------------------------------------------------
//DeadCode ARM 04Jun96 extern	Bool	BITCOMP(void*,ULong);
//DeadCode ARM 04Jun96 #pragma	aux		BITCOMP		=		\
//DeadCode ARM 04Jun96 		"btc	ds:[esi],ecx"	\
//DeadCode ARM 04Jun96 		"sbb	al,al"		\
//DeadCode ARM 04Jun96 		"neg	al"			\
//DeadCode ARM 04Jun96 		parm	[esi] [ecx]	\
//DeadCode ARM 04Jun96 		value	[al]			\
//DeadCode ARM 04Jun96 
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

bool	keytests::KeyHeld3d(KeyVal3D keyval)
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
bool	keytests::KeyPress3d(KeyVal3D keyval)
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
