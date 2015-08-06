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



#include	"dosdefs.h"
#define F_COMMON
#define F_GRAFIX
#define F_SOUNDS
#include	"files.g"
#include "Memain.h"
#include "AcItem.h"

#include "strings.h"

#include	"text.h"
#include	"makebf.h"
#include	"myangles.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include "globals.h"
#include	"sqinfo.h"

#include "worldinc.h"
 #include "bfenum.h"
#include "readenum.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"

int AlliedAircraftAvailable[]  =	{
	0,		//	IDS_PLANE_TYPE_CAMEL
	1,		//    IDS_PLANE_TYPE_SE5a
	-1,		//    IDS_PLANE_TYPE_FOKKER_DR1
	-1,		//    IDS_PLANE_TYPE_ALBATROS_D3
	2,		//    IDS_PLANE_TYPE_NIEUPORT28
	3,		//    IDS_PLANE_TYPE_SPAd
	4,		//    IDS_PLANE_FRENCHSPAD
	-1,		//    IDS_PLANE_TYPE_FOKKER_D7
	5,			//    IDS_PLANE_TYPE_NIEUPORT17
	6,		//    IDS_PLANE_TYPE_STRUTTEr
	7,		//    IDS_PLANE_TYPE_BRISTOL_F2a
	8,		//    IDS_PLANE_TYPE_PUp
	9,		//    IDS_PLANE_TYPE_FE2b
	10,		//    IDS_PLANE_TYPE_BE2c
	11,		//    IDS_PLANE_TYPE_RE8
	12,		//    IDS_PLANE_TYPE_DH9
	-1,		//    IDS_PLANE_TYPE_PFALz
	-1,		//    IDS_PLANE_TYPE_HALBERSTADt
	-1,		//    IDS_PLANE_TYPE_ZEPP
	-1,		//    IDS_PLANE_TYPE_AVIATIK_c
	-1,		//    IDS_PLANE_TYPE_RUMBLER_c
	13,		//    IDS_PLANE_TYPE_SE5
	-1,		//    IDS_ATRUCK
	-1		//    IDS_ATANK
					 };
int CPAircraftAvailable[]  =	{
	-1,		//	IDS_PLANE_TYPE_CAMEL
	-1,		//    IDS_PLANE_TYPE_SE5a
	0,		//    IDS_PLANE_TYPE_FOKKER_DR1
	1,		//    IDS_PLANE_TYPE_ALBATROS_D3
	-1,		//    IDS_PLANE_TYPE_NIEUPORT28
	-1,		//    IDS_PLANE_TYPE_SPAd
	-1,		//    IDS_PLANE_FRENCHSPAD
	2,		//    IDS_PLANE_TYPE_FOKKER_D7
	-1,		//    IDS_PLANE_TYPE_NIEUPORT17
	-1,		//    IDS_PLANE_TYPE_STRUTTEr
	-1,		//    IDS_PLANE_TYPE_BRISTOL_F2a
	-1,		//    IDS_PLANE_TYPE_PUp
	-1,		//    IDS_PLANE_TYPE_FE2b
	-1,		//    IDS_PLANE_TYPE_BE2c
	-1,		//    IDS_PLANE_TYPE_RE8
	-1,		//    IDS_PLANE_TYPE_DH9
	3,		//    IDS_PLANE_TYPE_PFALz
	4,		//    IDS_PLANE_TYPE_HALBERSTADt
	-1,		//    IDS_PLANE_TYPE_ZEPP
	5,		//    IDS_PLANE_TYPE_AVIATIK_c
	6,		//    IDS_PLANE_TYPE_RUMBLER_c
	-1,		//    IDS_PLANE_TYPE_SE5
	-1,		//    IDS_ATRUCK
	-1		//    IDS_ATANK
					 };

TSquadronDataForm *SquadronDataForm;
//	sel file based on:				area=verd   side=Alies	file=friends
FileNum		TSquadronDataForm::squadfiles[2]		[2]			[2]		=
{	{	{FIL_MainWorld,FIL_MainWorld},
		{FIL_MainWorld,FIL_MainWorld}
	},
	{	{FIL_MainWorld,FIL_MainWorld},
		{FIL_MainWorld,FIL_MainWorld}
}   };

//---------------------------------------------------------------------------
__fastcall TSquadronDataForm::TSquadronDataForm(TComponent* Owner)
	: TForm(Owner)
{
	Font->Color = clWindow;
	Font->Color = clWindowText;
}
//---------------------------------------------------------------------------
void	__fastcall TSquadronDataForm::InitForm()
{
	char buff[50];
	info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);


//camp	if (MissionEditor->ActiveCampaign.
//			mission[MissionEditor->currmission].PlayerNationality ==
//					ac->nat)
//	{
//		SquadronDataForm->ScanSquad(true,*SquadronComboBox->Items);
//		SquadronComboBox->ItemIndex = AcItemForm->Squadron - 1;
//	}
//	else
	{
		SquadronDataForm->ScanSquad(false,*SquadronComboBox->Items);
		SquadronComboBox->ItemIndex = -AcItemForm->Squadron - 1;
	}

	homebase = ac->homebase;
	char*	tmp =  GetList(ENUM_UIDtitle).Translate(homebase);
	if (tmp == NULL)
	{
		int text = MissionEditor->GetBandorShapeText(ac->homebase);
		LoadString(HInstance,text,buff,sizeof(buff));
		 HomeBaseEdit->Text = buff;
	}else
		 HomeBaseEdit->Text = tmp;
	 if ((int)ac->nat ==(int)NAT_BLUE)
		MissionEditor->PartFillComboBox(IDS_PLANE_TYPE_CAMEL,
								IDS_PLANE_TYPE_SE5,
											AcComboBox,
											ac->type,AlliedAircraftAvailable);
	else
		MissionEditor->PartFillComboBox(IDS_PLANE_TYPE_CAMEL,
								IDS_PLANE_TYPE_SE5,
											AcComboBox,
											ac->type,CPAircraftAvailable);

	int skill = ac->skill;
	skill = skill/((int)SKILL_STAGE);
	int morale = ac->morale;
	morale = morale/((int)MORALE_STAGE);
	MissionEditor->FillComboBox(IDS_TEXT_NOVICE,
								IDS_TEXT_HERO,
											SkillComboBox,
											skill);
	MissionEditor->FillComboBox(IDS_TEXT_ROCKBOTTOM,
								IDS_TEXT_EXCELLENT,
											MoraleComboBox,
											morale);
	MissionEditor->FillComboBox(IDS_TACTICIAN,
								IDS_CAVALIER,
											CharComboBox,
											ac->character);

}
//---------------------------------------------------------------------------
void	__fastcall TSquadronDataForm::OpenForm()
{
//	char buff[50];
	info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);

	InitForm();
	HomeBaseEdit->Enabled = true;
	HomeBaseButton->Enabled = true;
			
	int result = ShowModal();
	switch (result)
	{
		   case	mrCancel:
		   {
				ac->homebase = homebase;
				SetLandingWP();
				break;
			}	
		   case	mrOk:
		   {
	    		MissionEditor->loadedbfs[ac->bfieldindex].changed=true;

//				MissionEditor->MissionEdited=true;
				ExtractSquadName();
				ac->skill =   (int) SkillComboBox->ItemIndex * (int)SKILL_STAGE;
				ac->morale =   (int)MoraleComboBox->ItemIndex* (int)MORALE_STAGE;
				ac->character =   CharComboBox->ItemIndex;
				 if ((int)ac->nat ==(int)NAT_BLUE)
					ac->type = MissionEditor->FindOrginalIndex(
							IDS_PLANE_TYPE_CAMEL,
								IDS_PLANE_TYPE_SE5,
									AcComboBox->ItemIndex,AlliedAircraftAvailable);
				else
					ac->type = MissionEditor->FindOrginalIndex(
							IDS_PLANE_TYPE_CAMEL,
								IDS_PLANE_TYPE_SE5,
									AcComboBox->ItemIndex,CPAircraftAvailable);


//				ac->homebase = homebase;
//				SetLandingWP();

//camp				if (MissionEditor->ActiveCampaign.
//						mission[MissionEditor->currmission].PlayerNationality ==
//							ac->nat)
//					AcItemForm->Squadron = (SWord) SquadronComboBox->ItemIndex+1;
//				else
					AcItemForm->Squadron = (SWord) -(SquadronComboBox->ItemIndex+1);

		   }
	}
}
void	TSquadronDataForm::GetSquadName(int sqnum,char* buffer)
{
	if (sqnum<0)
		GetSquadName(false,-sqnum,buffer);
	else
		GetSquadName(true,sqnum,buffer);
}
void	TSquadronDataForm::GetSquadInfo(int sqnum,info_event& ev)
{
	if (sqnum<0)
		GetSquadInfo(false,-sqnum,ev);
	else
		GetSquadInfo(true,sqnum,ev);



}
void	TSquadronDataForm::GetSquadInfo(bool friends,int sqnum,info_event& ev)
{
	GetSquadInfo(   squadfiles	[0]
								[0]
								[friends],
					sqnum,ev);
}
void	TSquadronDataForm::ScanSquad(bool friends,TStrings& desc)
{
	ScanSquad(	   squadfiles	[0]
								[0]
								[friends],
					desc);

}
void	TSquadronDataForm::GetSquadName(bool friends,int sqnum,char* buffer)
{
	GetSquadName(   squadfiles	[0]
								[0]
								[friends],
					sqnum,buffer);
}

void	TSquadronDataForm::GetSquadName(FileNum f,int sqnum,char* buffer)
{
	Persons4	Persons_2;
	Persons_2.keptstr=buffer;
//	Persons_2.justscanning=Persons_2.NAMESQUAD;
	Persons_2.selectedsquad=sqnum;
	Persons_2.LoadSubPiece(NULL,f,(int)Persons_2.LOADEDBFS-1,Persons2::NAMESQUAD);
//	Persons_2.justscanning=Persons_2.LOAD;

}

void	TSquadronDataForm::GetSquadInfo(FileNum f,int sqnum,info_event& ev)
{
	Persons4	Persons_2;
	Persons_2.keptevent=&ev;
//	Persons_2.justscanning=Persons_2.SELECTSQUAD;
	Persons_2.selectedsquad=sqnum;
	Persons_2.LoadSubPiece(NULL,f,(int)Persons_2.LOADEDBFS-1,Persons_2.SELECTSQUAD);
  //	Persons_2.justscanning=Persons_2.LOAD;
}
void	TSquadronDataForm::ScanSquad(FileNum f,TStrings& desc)
{
	Persons4	Persons_2;
//	Persons_2.justscanning=Persons_2.SCANSQUADS;
	desc.Clear();
	descs=&desc;
	Persons_2.LoadSubPiece(NULL,f,(int)Persons_2.LOADEDBFS-1,Persons_2.SCANSQUADS);
  //	Persons_2.justscanning=Persons_2.LOAD;
	descs=NULL;
}

//void		Persons4::SquadAddDesc(string src ,int len,TokenCode t)
//{
//	SquadronDataForm->AddDesc(src,len,t);/
//}

void	TSquadronDataForm::AddDesc(string src,int len,TokenCode t)
{
	char	work[200];
	strncpy(work,src,len);
	work[len]=0;
	if ((int)t==(int)T_comment)
		descs->Add(work);
}


//---------------------------------------------------------------------------
void	TSquadronDataForm::ForceSqadUpdate(int squadnum)
{
	info_event	tmp;
	if (squadnum)
	{
		GetSquadInfo(squadnum,tmp);
		for (int i=tmp.usedsetvals;--i>=0;)
		{
			ProcessVar(tmp.setvals[i]);
		}

	}
}
//---------------------------------------------------------------------------
void	TSquadronDataForm::ProcessVar(EventVar& var)
{
	  char data[50];
	  UniqueID	hb;
		int text = ((GlobalsInfo*)BFieldGlobalTable[var.index].reference)->text;
		Process process = ((GlobalsInfo*)BFieldGlobalTable[var.index].reference)->processor->process;
		int min =  ((GlobalsInfo*)BFieldGlobalTable[var.index].reference)->processor->min;
		int max =  ((GlobalsInfo*)BFieldGlobalTable[var.index].reference)->processor->max;
		int stepsize =  ((GlobalsInfo*)BFieldGlobalTable[var.index].reference)->processor->stepsize;
		switch (process)
		{
			case	P_COMBOBOX:
			{

				switch (min)
				{
					case   IDS_TEXT_NOVICE:
					{
						SkillComboBox->ItemIndex = var.Evaluate()/stepsize;
						break;
					}
					case   IDS_TEXT_ROCKBOTTOM:
					{
						MoraleComboBox->ItemIndex = var.Evaluate()/stepsize;
						break;
					}
					case   IDS_TACTICIAN:
					{
						CharComboBox->ItemIndex = var.Evaluate()/stepsize;
						break;
					}
					case   IDS_PLANE_TYPE_CAMEL:
					{
						info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);

						int* ctrlarray;

						if ((int)ac->nat ==(int)NAT_BLUE)
							ctrlarray = AlliedAircraftAvailable;
						else
							ctrlarray = CPAircraftAvailable;

						int index = var.Evaluate()/stepsize;
						SWord j = 0,k=-1;
						while ((min+j) <= max)
						{
							if	(ctrlarray[j] != -1)
							{
								k++;
								if  (j == index)
								{
									AcComboBoxItemIndex = k;			//system wipes item index when we need it, hence temp var
									AcComboBox->ItemIndex =   k;
								}	
							}
							j++;
						}
						break;
					}
				}
			}
			break;
			case	P_HOMEBASE:
			{
				info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);
				hb = var.Evaluate();
				if (Persons2::ConvertPtrUID(hb))
					ac->homebase = hb;
				SetLandingWP();
				char*	tmp =  GetList(ENUM_UIDtitle).Translate(hb);
				if (tmp == NULL)
				{
					int text = MissionEditor->GetBandorShapeText(hb);
					LoadString(HInstance,text,data,sizeof(data));
					HomeBaseEdit->Text = data;
				}else
					HomeBaseEdit->Text = tmp;
				break;
			}
		}
}

//---------------------------------------------------------------------------

void __fastcall TSquadronDataForm::SquadronComboBoxChange(TObject *Sender)
{
	info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	ExtractSquadName();
	if (FullSquadronName[0] == 45)
	{
		SquadronComboBox->ItemIndex = -1;
	}else
	{
		HomeBaseEdit->Enabled = false;
		HomeBaseButton->Enabled = false;
		SquadronComboBox->Hint =  FullSquadronName;

//camp		if (MissionEditor->ActiveCampaign.
//				mission[MissionEditor->currmission].PlayerNationality ==
//						ac->nat)
//			ForceSqadUpdate(SquadronComboBox->ItemIndex+1);
//		else
			ForceSqadUpdate(-(SquadronComboBox->ItemIndex+1));
	}
}
//---------------------------------------------------------------------------
void __fastcall TSquadronDataForm::ExtractSquadName()
{
	if 	(SquadronComboBox->ItemIndex != -1)
	{
				char* squadronnames;
				squadronnames = SquadronComboBox->Items->GetText();
				int i =0, j=0;
				while (squadronnames[i] != 0)
				{
					if (j == SquadronComboBox->ItemIndex)
						break;
					if (squadronnames[i] == 10)
						j++;
					i++;
				}

				j=0;
				while (squadronnames[i] != ',')
				{
					AcItemForm->SquadronName[j] = squadronnames[i];
					FullSquadronName[j] = squadronnames[i];
					j++;
					i++;
				}
				AcItemForm->SquadronName[j] = 0;
				while (squadronnames[i] != 10)
				{
					FullSquadronName[j] = squadronnames[i];
					j++;
					i++;
				}
				FullSquadronName[j] = 0;
				delete squadronnames;
    }
 }

//---------------------------------------------------------------------------
void __fastcall TSquadronDataForm::SetLandingWP()
{ 
   info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);
   info_waypoint* W;
   
   UniqueID	wp=ac->wpref;
   do
   {
		W=*Persons2::ConvertPtrUID(wp);
		wp=W->nextwp;
   }while(W->nextwp);
   
   W->target = ac->homebase;

   W->position.MakeAbsWorldPos();

	if (W->position[0].Evaluate()!=ENABLE_COMPLEX_VAL)
		W->position[0]=ENABLE_COMPLEX_VAL;
	W->position[0][0]=0;
	W->position[0][2]=0;
	W->position.EvalW(W->World);
	Coords3D& c=Persons2::ConvertPtrUID(W->target)->World;
	W->World.X+=c.X+30000;
	W->World.Z+=c.Z-30000;
//    MissionEditor->PaintBox->Invalidate();
}

void __fastcall TSquadronDataForm::HomeBaseButtonClick(TObject *Sender)
{

	MissionEditor->SetFindingStaticMode(SETSQUADHOMEBASE);
	Close();
	AcItemForm->Close();
//	WindowState = wsMinimized;
//	AcItemForm->WindowState = wsMinimized;
}
//---------------------------------------------------------------------------

