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

//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//#include "Route.h"
#include "AcItem.h"
#include "waypoint.h"
//#include "choosebf.h"
#include "strings.h"
//#include "mainevt.h"
#include "currshp.h"
#include "SGroups.h"
#include	"text.h"
#include	"shapenum.g"
#include "memain.h"
#include	"worldinc.h"
#include	"bfnumber.h"
#include	"persons2.h"

#include "bfenum.h"
#include "readenum.h"



//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma resource "*.dfm"
TSuperGroups *SuperGroups;
//---------------------------------------------------------------------------
__fastcall TSuperGroups::TSuperGroups(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

  void __fastcall TSuperGroups::OpenForm()
{
	UWord i;
	for (i = 0; i < MAXLOADEDSUPERGROUPS;i++)
		MissionEditor->tmploadedsupergroup[i] = MissionEditor->loadedsupergroup[i];

	SuperGroupGrid->Rows[0]->SetText("Name\nCurrent\nViewable\nMovable\nDeletable\nNew\nChanged");

	Refresh();

	int result = ShowModal();
	switch (result)
	{
		case	mrOk:
		  {

				break;
		  }
		case	mrCancel:
		  {
				for (i = 0; i < MAXLOADEDSUPERGROUPS;i++)
					MissionEditor->loadedsupergroup[i] = MissionEditor->tmploadedsupergroup[i];
				 break;
		  }
	  }

}

void __fastcall TSuperGroups::Refresh()
{
	UWord i;
	char buff[50];
	for (i = 0; i < MAXLOADEDSUPERGROUPS;i++)
	{
		if	(MissionEditor->loadedsupergroup[i].uid != AbsolutingSepID)
		{
			if (MissionEditor->loadedsupergroup[i].uid == UID_Null)
				strcpy(buff,"None");
			else
				strcpy(buff,GetList(ENUM_UIDtitle).Translate(MissionEditor->loadedsupergroup[i].uid));
			SuperGroupGrid->Cells[0][i+1]= buff;
			if (i == MissionEditor->supergroupbeingfilled)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			SuperGroupGrid->Cells[1][i+1]= buff;

			if (MissionEditor->loadedsupergroup[i].viewable)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			SuperGroupGrid->Cells[2][i+1]= buff;

			if (MissionEditor->loadedsupergroup[i].movable)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			SuperGroupGrid->Cells[3][i+1]= buff;

			if (MissionEditor->loadedsupergroup[i].deletable)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			SuperGroupGrid->Cells[4][i+1]= buff;

			if (MissionEditor->loadedsupergroup[i].newlynamed)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			SuperGroupGrid->Cells[5][i+1]= buff;

			if (MissionEditor->loadedsupergroup[i].changed)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			SuperGroupGrid->Cells[6][i+1]= buff;
		}
	}

}

void __fastcall TSuperGroups::SuperGroupGridMouseUp(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	long	c,r;
	UWord	i;
	TStringGrid* G=(TStringGrid*)Sender;
	G->MouseToCell(X,Y,c,r);
	if (c == 1)
	{
		MissionEditor->supergroupbeingfilled = r -1;
	}else if (c == 2)
	{
		  if (MissionEditor->loadedsupergroup[r -1].viewable)
			MissionEditor->loadedsupergroup[r -1].viewable = false;
		  else
			MissionEditor->loadedsupergroup[r -1].viewable = true;
		  if ( r == 1)
		  {
			  if (MissionEditor->loadedsupergroup[r -1].viewable)
			  {
				for (i = 1; i < MAXLOADEDSUPERGROUPS;i++)
					MissionEditor->loadedsupergroup[i].viewable = false;
			  }else
			  {
				for (i = 1; i < MAXLOADEDSUPERGROUPS;i++)
					MissionEditor->loadedsupergroup[i].viewable = true;
			  }
			}else
			{
			  if (MissionEditor->loadedsupergroup[r -1].viewable)
					MissionEditor->loadedsupergroup[0].viewable = false;
			}

	}else 	if (c == 3)
	{
		  if (MissionEditor->loadedsupergroup[r -1].movable)
			MissionEditor->loadedsupergroup[r -1].movable = false;
		  else
			MissionEditor->loadedsupergroup[r -1].movable = true;
	}else 	if (c == 4)
	{
		  if (MissionEditor->loadedsupergroup[r -1].deletable)
			MissionEditor->loadedsupergroup[r -1].deletable = false;
		  else
			MissionEditor->loadedsupergroup[r -1].deletable = true;
	}else 	if (c == 5)
	{
		  if (MissionEditor->loadedsupergroup[r -1].newlynamed)
			MissionEditor->loadedsupergroup[r -1].newlynamed = false;
		  else
			MissionEditor->loadedsupergroup[r -1].newlynamed = true;
	}else 	if (c == 6)
	{
		  if (MissionEditor->loadedsupergroup[r -1].changed)
			MissionEditor->loadedsupergroup[r -1].changed = false;
		  else
			MissionEditor->loadedsupergroup[r -1].changed = true;
	}
	Refresh();
	Invalidate();

}
//---------------------------------------------------------------------------


