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
//Filename       winsmack.cpp
//System         Mig Alley
//Author         Dave Whiteside
//Date           Sun 19 Jul 1998
//Description    Smacker interface for migalley
// getfreediskspace
//------------------------------------------------------------------------------

#include	"DosDefs.h"
#include	"Display.h"
#include	"myError.h"
#include	"smack.h"
#include	"fileman.h"
#include	"worldinc.h"										//RJS 24Mar99
#include	"miles.h"											//RJS 24Mar99
#include	"winmove.h"

SmackBuf	far* sbuf=0;
Smack		far* smk=0;
int			Xoff=0;
int			Yoff=0;
int			wait=0;

void	CloseSmack()
{
    if (sbuf)
      SmackBufferClose(sbuf);
	if (smk)
	{
		SmackClose(smk);
		_Miles.SmackerOff();										//RJS 24Mar99
	}

	sbuf=0;
	smk=0;
}

Smack* OpenSmack(FileNum filenumber,int win, int x, int y,int w, int h)
{
	HWND	hWnd=(HWND)win;
	char	filename[80];

	if ((x!=-1) && (y!=-1))
	{
		Xoff=x;
		Yoff=y;		
	}
	wait=0;

	CloseSmack();
	if (filenumber)
	{
		smk=SmackOpen(FILEMAN.namenumberedfile(filenumber,filename),SMACKTRACKS+SMACKNEEDVOLUME,SMACKAUTOEXTRA);//RJS 14Apr99
		if (smk)
		{
			_Miles.SmackerOn(smk);										//RJS 13Apr99
			sbuf=SmackBufferOpen(hWnd,SMACKAUTOBLIT,smk->Width,smk->Height,w,h);
		}
	}
	else
		smk=NULL;

	return (smk);
}

/*
	UWord	DoSmack(int h)
	Returns Number of frames left [0 if finished]
	Inputs	Window Handle


*/
extern	int	introsmk;
UWord	DoSmack(int h)
{
	UWord	retval=0;
	HDC		dc;

	HWND	hWnd=(HWND)h;

#ifdef MIG_DEMO_VER
	if (_DPlay.PossibleLobby)
		return 1;
#endif

	if (introsmk==0)
	{
		if (sbuf)						//Is there a buffer
		{
			if (smk)					//If there is a smack then retv= the number of frames
			{
				ULong	retv=0;
				retv=smk->Frames-1;
				if (!SmackWait(smk))	//If I should play a frame then do it.
				{
					dc=GetDC( hWnd);
					if (smk->NewPalette) {
						SmackBufferNewPalette(sbuf,smk->Palette,smk->PalType);
						SmackColorRemap(smk,sbuf->Palette,sbuf->MaxPalColors,sbuf->PalType);
					}
					SmackToBuffer(smk,0,0,sbuf->Pitch,sbuf->Height,sbuf->Buffer,0);//(u8)sbuf->Reversed);
					SmackDoFrame(smk);
	
					SmackBufferStartMultipleBlits(sbuf);
					while (SmackToBufferRect(smk,sbuf->SurfaceType))
						if (SmackBufferBlit(sbuf,dc,Xoff,Yoff,smk->LastRectx,smk->LastRecty,smk->LastRectw,smk->LastRecth))
							break;
					SmackBufferEndMultipleBlits(sbuf);
	 				ReleaseDC( hWnd, dc );
					SmackNextFrame(smk);
					retv-=smk->FrameNum;	//retv has number of frames left
					retval=UWord(retv);
					if (retval <= 1)
					{
						retval=0;			//make sure things are OK
					}
				}else{
					retval=(smk->Frames)-(smk->FrameNum);	//just return the frame number - don't play anything
				}
			}
		}
	}else
		introsmk=0;
	return(retval);
}
