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
//Filename       monotxt.cpp
//System         
//Author         Paul.   
//Date           Wed 16 Oct 1996
//Description    
//------------------------------------------------------------------------------
//DeadCode DAW 23Feb98 #include	"dosdefs.h"
#define NO_AFX_AUTO
//TEMPCODE JIM 27/07/99 #include	"stdafx.h"
#include "dosdefs.h"
#include	"monotxt.h"
#include	"Mytime.h"

#ifdef	NDEBUG
#pragma message (__HERE__ "Mono debugs disabled")
#else
#pragma message (__HERE__ "Mono debugs enabled!!!!")
#endif
const	SLong	MonoScreenWidth = 80;
const	SLong	MonoScreenHeight= 25;
const	SLong	MonoStartAddr = 0x0B0000;

class MonoText Mono_Text;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MonoText
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::ClsMono()
{
#ifndef NDEBUG													//DAW 13Nov96
	UWord	temp;

	UWord* scradr = (UWord* )MonoStartAddr;

	cx = cy = 0;

	for (int row = 0;row<MonoScreenWidth;row++)
	{
		for (int column = 0;column<MonoScreenHeight;column++)
		{
			temp = *scradr;

			temp = (temp & 0xFF00) + ' ';

			*scradr++ = temp;
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCursor
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
#ifndef NDEBUG													//DAW 13Nov96
//------------------------------------------------------------------------------
void MonoText::SetCursor(SLong rx,SLong ry)
{
	cx = rx; cy = ry;
}
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Print
//Author		Paul.   
//Date			Thu 24 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#ifndef NDEBUG													//DAW 13Nov96
void MonoText::Print(UByte* text,SLong length)
{
	UWord  temp;

	UByte  chr;

	UWord* scradr = (UWord* )MonoStartAddr;

	scradr += (cy * MonoScreenWidth) + cx;

	while (length--)
	{
		chr = *text++;

		temp = 0xFF00 & *scradr;

		temp += 0x00FF & (UWord )chr;

		*scradr++ = temp;

		cx++;

		if (cx>=MonoScreenWidth) break;
	}

	cx = 0;

	cy++;

	if (cy>=MonoScreenHeight)
		cy = 0;
}
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TextOutMono
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#ifndef NDEBUG													//DAW 13Nov96
void MonoText::TextOutMono(UByte* string)
{
	UWord  temp;

	UByte  chr;

	UWord* scradr = (UWord* )MonoStartAddr;

	scradr += (cy * MonoScreenWidth) + cx;

	while (*string)
	{
		chr = *string++;

		if (chr=='\n')	//newline
		{
			cx = 0;
			cy++;

			if (cy>=MonoScreenHeight)	ClsMono();

			scradr = (UWord* )MonoStartAddr + (cy * MonoScreenWidth) + cx;
		}
		else
		{
			temp = 0xFF00 & *scradr;

			temp += 0x00FF & (UWord )chr;

			*scradr++ = temp;

			cx++;

			if (cx>=MonoScreenWidth)
			{
				cx = 0;
				cy++;
				if (cy>=MonoScreenHeight)
				{
					ClsMono();

					scradr = (UWord* )MonoStartAddr;
				}
			}
		}
	}
}

#endif
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BinToASCII
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#ifndef NDEBUG													//DAW 13Nov96
void MonoText::BinToASCII(SLong value,UByte* strval)
{
	SLong	ival;

	strval += 9;

	for (int counter=0;counter<10;counter++)
	{
		ival = value % 10;

		value = (value - ival)/10;

		*strval = '0' + (UByte )ival;

		strval--;
	}
}
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartTimer
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::StartTimer(SLong& timevar)
{
#ifndef NDEBUG													//DAW 13Nov96
//TempCode PD 22Oct96 	timevar = Timer_Code.tus;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopTimer
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::StopTimer(SLong& timevar)
{
#ifndef NDEBUG													//DAW 13Nov96
//	SLong	stoptime;

//TempCode PD 22Oct96 	stoptime = Timer_Code.tus;

//	stoptime -= timevar;

//	timevar = stoptime;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopTimer
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::StopTimer(SLong& timevar,UByte* string)
{
#ifndef NDEBUG													//DAW 13Nov96
//	SLong	stoptime;

//	UByte	ltstring[] = "1234567890 \n";

//	UByte*	tstring = ltstring;

//TempCode PD 22Oct96 	stoptime = Timer_Code.tus;

//	stoptime -= timevar;

//	TextOutMono(string);

//	BinToASCII(stoptime,tstring);

//	TextOutMono(tstring);
#endif
}

#ifndef NDEBUG													//DAW 13Nov96
void	MonoText::BinToHEX(SLong v,UByte* c)
{
	int p=7;
	while (p>=0)
	{
		int i=v&0xf;
		v>>=4;
		if (i>9)
			c[p]='A'-10+i;
		else
			c[p]='0'+i;
		p--;
	}
	c[8]=0;

}
#endif



