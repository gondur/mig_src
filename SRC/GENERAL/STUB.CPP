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
//Filename		stub.cpp
//System		flying corps install
//Author		Dave Whiteside
//Date			Tue 19 Mar 1996
//Description	to stubb out routines and classes that are not used in the
//				install program.
//------------------------------------------------------------------------------

#include	<dos.h>
#include	<direct.h>
#include	<string.h>
#include	<stdio.h>
#include	<malloc.h>
#include	"miss_man.h"
#include	"ui.h"
#include	"Mytime.h"
#include	"install.h"
#include	"hotkeys.h"

//
//The starting sheet for the instrallation - it's not what it says its
//in this file
//
BaseSheetDefType	SheetBase::basesheetconstructor=UISheet::MakeIntroAnimFullScrnSmk;//DAW 11Apr96

char	* Inst_source		= "d:\\fly\\game,d:\\fly\\game,d:\\fly\\game";
char	* Inst_destination;

#define	SHEETNAME	InstallSheet
#include	"SHEETTOP.h"
#include	"hotkeys.h"


Install	all;
char	mybuff[60];
int		FileNo;

STRINGPAINT(StringDraw,UIC)
{
 	short	garbage;
	window->RegisterFontActive (FIL_TEXTFONT,garbage,garbage,garbage);
	RefreshBackground(UIC);
	window->SetColour (WHITE);
	_Text.Print(window,UIC.xy,UIC.wh,PF_HAlignCenter+PF_VAlignCenter+PF_HalfSpaces,
			_Text.Conv(UIC.value));
}

TEXTEVENT(SelectFullInstall,UIC)
{
	all.Initialize();
	all.GenerateFlist(Inst_source);
	all.SetGenerated(TRUE);
	all.SetDstDir(Inst_destination);
	ChildSheet(MakeCopyingSheet(UIC.xy,*window,all));
}


TEXTEVENT(SelectMediumInstall,)
{
	PopThisSheet(RequestExitGame);
}


TEXTEVENT(SelectSmallInstall,)
{
	PopThisSheet(RequestExitGame);
}

TEXTEVENT(SelectChangeDest,UIC)
{
	ChildSheet(MakeDrvCngSheet(UIC.xy,*window,Inst_destination));
}

TEXTEVENT(SelectQuit,)
{
	PopThisSheet(RequestExitGame);
}

TEXTEVENT(SelectCampaign,)
{
	PopThisSheet(RequestExitGame);
}

Bool	FakeBool;

TEXTEVENT(NoHelp,UIC)
{
	ChildSheet(MakeSureSheet(UIC.xy,*window,FakeBool,(TextRef)TEXT_SHEPHERD,FIL_SUREART,YELLOW));
}

TEXTEVENT(Doit,)
{
}

TEXTPAINT(TextAndOutLine,UIC)
{
 	short	garbage;
	window->RegisterFontActive (FIL_LARGEFONT,garbage,garbage,garbage);
	window->SetColour (BLACK);
	_Text.Print(window,UIC.xy,UIC.wh,PF_HAlignCenter+PF_VAlignCenter+PF_HalfSpaces,UIC.text);
	window->RegisterFontActive (FIL_TEXTFONT,garbage,garbage,garbage);
}

TEXTPAINT(TextAndOutLineHi,UIC)
{
 	short	garbage;
 	window->RegisterFontActive (FIL_LARGEFONT,garbage,garbage,garbage);
 	window->SetColour (RED);
	_Text.Print(window,UIC.xy,UIC.wh,PF_HAlignCenter+PF_VAlignCenter+PF_HalfSpaces,UIC.text);
 	window->RegisterFontActive (FIL_TEXTFONT,garbage,garbage,garbage);
}

TEXTPAINT(Drawit,UIC)
{
 	short	garbage;
 	window->SetColour (WHITE);
 	window->RegisterFontActive (FIL_TEXTFONT,garbage,garbage,garbage);
	_Text.Print(window,UIC.xy,UIC.wh,PF_HAlignCenter+PF_VAlignCenter+PF_HalfSpaces+PF_IgnoreBSlash,
		_Text.Conv(TEXT_INSTALL_ONE,
			_Text.Conv(all.GetDefDst())
	));
}

InstallSheet()						//constructor
{

backdropart = FIL_GAMESELECTART;

SWord	currx = PIXEL640 * 200,
		curry = PIXEL640 * 10,
		currw = PIXEL640 * 240,
		currh = PIXEL640 * 36;
UIComponentPtr	InterestingComp;
TextComp*		InterestingComp2;
		Inst_destination=mybuff;
		FileNo=0;
		Inst_source = all.FindSrcDir(Inst_source);
		all.SetSrcDir(Inst_source);
		strcpy(Inst_destination,all.GetDefDst());


	ADD(DRAW|CURRENT|TEST,
		Text,(currx,curry,currw,currh),
		SELECT(SelectFullInstall)
		SELECTR(NoHelp)
		DRAW(TextAndOutLine)
		DRAWHI(TextAndOutLineHi)
		DATAVAL((TextRef)TEXT_INSTALL_FULL)
		);

	curry += currh;
	ADD(DRAW,
		Text,(currx,curry,currw,currh),
		SELECT(SelectMediumInstall)
		SELECTR(NoHelp)
		DRAW(TextAndOutLine)
		DRAWHI(TextAndOutLineHi)
		DATAVAL((TextRef)TEXT_INSTALL_MED)
		);

	curry += currh;
	ADD(DRAW,
		Text,(currx,curry,currw,currh),
		SELECT(SelectSmallInstall)
		DRAWHI(TextAndOutLineHi)
		SELECTR(NoHelp)
		DATAVAL((TextRef)TEXT_INSTALL_SMALL)
		DRAW(TextAndOutLine)
		);

	curry += currh;
	ADD (DRAW,
		Text,(currx,curry,currw,currh),
		SELECT(SelectCampaign)
		SELECTR(NoHelp)
		DRAW(TextAndOutLine)
		DRAWHI(TextAndOutLineHi)
		DATAVAL((TextRef)TEXT_INSTALL_SOUND)
		);

	curry += currh;
	ADD (DRAW,
		Text,(currx,curry,currw,currh),
		SELECT(SelectCampaign)
		SELECTR(NoHelp)
		DRAW(TextAndOutLine)
		DRAWHI(TextAndOutLineHi)
		DATAVAL((TextRef)TEXT_INSTALL_GRAPHIC)
		);


	curry += currh;
	ADD (DRAW|TEST,
		Text,(currx,curry,currw,currh),
		SELECT(SelectChangeDest)
		DRAW(TextAndOutLine)
		DRAWHI(TextAndOutLineHi)
		DATAVAL((TextRef)TEXT_INSTALL_DRIVE)
		);

//DeadCode DAW 12Apr96 	curry += currh;
//DeadCode DAW 12Apr96 	ADD (DRAW,
//DeadCode DAW 12Apr96 		Text,(currx,curry,currw,currh),
//DeadCode DAW 12Apr96 		DRAW(Drawit)
//DeadCode DAW 12Apr96 		);

	curry += currh;
	ADD(DRAW|TEST,
		Text,(currx,curry,currw,currh),
		DRAWHI(TextAndOutLineHi)
		SELECT(SelectQuit)
		SELECTR(NoHelp)
		DATAVAL((TextRef)TEXT_QUIT)
		DRAW(TextAndOutLine)
		);

	}
};


UISheetPtr	UISheet::MakeIntroAnimFullScrnSmk()
{
	return(new InstallSheet());
}

