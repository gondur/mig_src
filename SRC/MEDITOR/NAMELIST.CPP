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
#include "NameList.h"
#include	"memain.h"
#include	"dosdefs.h"
#include	"text.h"
#include	"uniqueid.h"

#include	"persons2.h"
#include	"bfenum.h"
#include "readenum.h"
inline bool operator	>= (StdCtrls_9 a,StdCtrls_9 b)	{return int(a)>=int(b);}
inline bool operator	<= (StdCtrls_9 a,StdCtrls_9 b)	{return int(a)<=int(b);}
inline int operator	% (StdCtrls_9 a,int b)	{return int(a)%int(b);}
//#include	"
//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma resource "*.dfm"
TNameListSel *NameListSel;
//---------------------------------------------------------------------------
__fastcall TNameListSel::TNameListSel(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TNameListSel::FormActivate(TObject *Sender)
{
	NameList->Items->Clear();
	int i,u;
	for (i=0,u=0;u<(int)IllegalSepID;u++)
	{
		char* buff=GetList(ENUM_UIDtitle).Translate(u);
		if (buff==NULL)
			buff=GetList(ENUM_UniqueID).Translate(u);
		if (buff)
		{
//			TListItem* l=NameList->Items->Add();
  //			l->Caption=buff;
	//		l->StateIndex=u;
			NameList->Items->Add(AnsiString(buff)+"\t"+u);
			i++;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TNameListSel::FormClose(TObject *Sender, TCloseAction &Action)
{
	NameList->Items->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TNameListSel::Edit1Change(TObject *Sender)
{
	int i=-1;
	const int	rows=//NameList->VisibleRowCount;
						NameList->Height/NameList->ItemHeight;
	AnsiString keyed=Edit1->Text;
	AnsiString entry;
	if (keyed.IsEmpty())
		return;
	while(++i<NameList->Items->Count-rows)
	{
		entry=NameList->Items->Strings[i];//Item[i]->Caption;
		if (keyed.AnsiCompareIC(entry)<=0)
			break;
	}
	if (i<NameList->TopIndex || i>=NameList->TopIndex+rows)
		NameList->TopIndex=i;
//		NameList->Items->Item[i]->Focused=true;
//	NameList->ItemFocused=
//
//	NameList->ItemFocused=
//		NameList->Selected=
//		NameList->Items->Item[i];
	NameList->ItemIndex=i;
}
//---------------------------------------------------------------------------
void __fastcall TNameListSel::NameListDrawItem(TWinControl *Control, int Index,
	TRect &Rect, TOwnerDrawState State)
{
	NameList->Canvas->Font=NameList->Font;
	AnsiString	s=NameList->Items->Strings[Index];
	int v=s.Pos("\t");
	int u=s.SubString(v+1,5).ToInt();
	if (Persons2::ConvertPtrUID(UniqueID(u)))
		if (State.Contains(odSelected))
			NameList->Canvas->Font->Color=NameList->Color;
		else
			;
	else
		NameList->Canvas->Font->Color=clInactiveCaption;
	NameList->Canvas->FillRect(Rect);
	NameList->Canvas->TextOut(Rect.Left, Rect.Top, s.SubString(0,v-1));
}
//---------------------------------------------------------------------------

void __fastcall TNameListSel::NameListMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	POINT	m={X,Y};
	int Index=NameList->ItemAtPos(m,false);
	AnsiString	s=NameList->Items->Strings[Index];
	int v=s.Pos("\t");
	int u=s.SubString(v+1,5).ToInt();
	UniqueID id=UniqueID(u);//UniqueID(NameList->Selected->StateIndex);
	ItemBasePtr	p=Persons2::ConvertPtrUID(id);
	if (p)
	{
		MissionEditor->currobj=id;
		MissionEditor->CentreOnWorld(p->World.X,p->World.Z);
		Close();
	}

}
//---------------------------------------------------------------------------
