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

#include "missobj.h"
#include "Memain.h"


#include <uniqueid.h>
#include "bfenum.h"
#include "readenum.h"

//#include "missbase.h"
                            					

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMissionObjectivesForm *MissionObjectivesForm;
//---------------------------------------------------------------------------
__fastcall TMissionObjectivesForm::TMissionObjectivesForm(TComponent* Owner)
	: TForm(Owner)
{
	Font->Color = clWindow;
	Font->Color = clWindowText;
}
//---------------------------------------------------------------------------
__fastcall TMissionObjectivesForm::RefreshForm()
{
	char buff[50];


//DeadCode RDH 19Feb98 	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective !=0)
//DeadCode RDH 19Feb98 	{
//DeadCode RDH 19Feb98 		LoadString(HInstance,MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		if (buff[0] == 0)
//DeadCode RDH 19Feb98 		{
//DeadCode RDH 19Feb98 			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective);
//DeadCode RDH 19Feb98 			LoadString(HInstance,text,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		}
//DeadCode RDH 19Feb98 	 }else
//DeadCode RDH 19Feb98 	 {
//DeadCode RDH 19Feb98 		buff[0] = 0;
//DeadCode RDH 19Feb98 	 }
//DeadCode RDH 19Feb98 	Edit0->Text = buff;
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective !=0)
//DeadCode RDH 19Feb98 	{
//DeadCode RDH 19Feb98 		LoadString(HInstance,MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		if (buff[0] == 0)
//DeadCode RDH 19Feb98 		{
//DeadCode RDH 19Feb98 			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective);
//DeadCode RDH 19Feb98 			LoadString(HInstance,text,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		}
//DeadCode RDH 19Feb98 	 }else
//DeadCode RDH 19Feb98 	 {
//DeadCode RDH 19Feb98 		buff[0] = 0;
//DeadCode RDH 19Feb98 	 }
//DeadCode RDH 19Feb98 	Edit1->Text = buff;
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1 !=0)
//DeadCode RDH 19Feb98 	{
//DeadCode RDH 19Feb98 		LoadString(HInstance,MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		if (buff[0] == 0)
//DeadCode RDH 19Feb98 		{
//DeadCode RDH 19Feb98 			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1);
//DeadCode RDH 19Feb98 			LoadString(HInstance,text,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		}
//DeadCode RDH 19Feb98 	 }else
//DeadCode RDH 19Feb98 	 {
//DeadCode RDH 19Feb98 		buff[0] = 0;
//DeadCode RDH 19Feb98 	 }
//DeadCode RDH 19Feb98 	Edit2->Text = buff;
//DeadCode RDH 19Feb98 	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2 !=0)
//DeadCode RDH 19Feb98 	{
//DeadCode RDH 19Feb98 		LoadString(HInstance,MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		if (buff[0] == 0)
//DeadCode RDH 19Feb98 		{
//DeadCode RDH 19Feb98 			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2);
//DeadCode RDH 19Feb98 			LoadString(HInstance,text,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		}
//DeadCode RDH 19Feb98 	 }else
//DeadCode RDH 19Feb98 	 {
//DeadCode RDH 19Feb98 		buff[0] = 0;
//DeadCode RDH 19Feb98 	 }
//DeadCode RDH 19Feb98 	Edit3->Text = buff;
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3 !=0)
//DeadCode RDH 19Feb98 	{
//DeadCode RDH 19Feb98 		LoadString(HInstance,MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		if (buff[0] == 0)
//DeadCode RDH 19Feb98 		{
//DeadCode RDH 19Feb98 			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3);
//DeadCode RDH 19Feb98 			LoadString(HInstance,text,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		}
//DeadCode RDH 19Feb98 	 }else
//DeadCode RDH 19Feb98 	 {
//DeadCode RDH 19Feb98 		buff[0] = 0;
//DeadCode RDH 19Feb98 	 }
//DeadCode RDH 19Feb98 	Edit4->Text = buff;

//camptmp	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective !=0)
//camptmp	{
//camptmp		char*	tmp =  GetList(ENUM_UIDtitle).Translate(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective);
//camptmp		if (tmp == NULL)
//camptmp		{
//camptmp			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective);
//camptmp			LoadString(HInstance,text,buff,sizeof(buff));
//camptmp			Edit0->Text = buff;
//camptmp		}else
//camptmp			Edit0->Text = tmp;
//camptmp
//camptmp	 }else
	 {
		Edit0->Text = "feature disabled temporarily";
	 }

//camptmp	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective !=0)
//camptmp	{
//camptmp		char*	tmp =  GetList(ENUM_UIDtitle).Translate(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective);
//camptmp		if (tmp == NULL)
//camptmp		{
//camptmp			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective);
//camptmp			LoadString(HInstance,text,buff,sizeof(buff));
//camptmp			Edit1->Text = buff;
//camptmp		}else
//camptmp			Edit1->Text = tmp;
//camptmp	 }else
		Edit1->Text = "";

//camptmp	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1 !=0)
//camptmp	{
//camptmp		char*	tmp =  GetList(ENUM_UIDtitle).Translate(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1);
//camptmp		if (tmp == NULL)
//camptmp		{
//camptmp			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1);
//camptmp			LoadString(HInstance,text,buff,sizeof(buff));
//camptmp			Edit2->Text = buff;
//camptmp		}else
//camptmp			Edit2->Text = tmp;
//camptmp	 }else
		Edit2->Text = "";

//camptmp	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2 !=0)
//camptmp	{
//camptmp		char*	tmp =  GetList(ENUM_UIDtitle).Translate(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2);
//camptmp		if (tmp == NULL)
//camptmp		{
//camptmp			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2);
//camptmp			LoadString(HInstance,text,buff,sizeof(buff));
//camptmp			Edit3->Text = buff;
//camptmp		}else
//camptmp			Edit3->Text = tmp;
//camptmp	 }else
		Edit3->Text = "";

//camptmp	if  (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3 !=0)
//camptmp	{
//camptmp		char*	tmp =  GetList(ENUM_UIDtitle).Translate(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3);
//camptmp		if (tmp == NULL)
//camptmp		{
//camptmp			int text = MissionEditor->GetBandorShapeText(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3);
//camptmp			LoadString(HInstance,text,buff,sizeof(buff));
//camptmp			Edit4->Text = buff;
//camptmp		}else
//camptmp			Edit4->Text = tmp;
//camptmp	 }else
		Edit4->Text = "";

}
//---------------------------------------------------------------------------
__fastcall TMissionObjectivesForm::InitForm()
{
//	MissionEditor->CheckObjectives();

//camp	MissionEditor->TmpMainObjective = MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective;
//	MissionEditor->TmpSubObjective = MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective;
//	MissionEditor->TmpWP1 = MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1;
//	MissionEditor->TmpWP2 = MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2;
//	MissionEditor->TmpWP3 = MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3;


}

//---------------------------------------------------------------------------
__fastcall TMissionObjectivesForm::ProcessForm()
{
	RefreshForm();
	int result = ShowModal();
	switch (result)
	{
		case	mrOk:
		  {
			MissionEditor->loadedbfs[MissionEditor->bfieldbeingfilled].changed=true;
 //				MissionEditor->CampaignStarted = true;
   //				MissionEditor->MissionStarted = true;
	 //			MissionEditor->MissionEdited=true;

				 break;
		  }
		case	mrCancel:
		  {

				if  (MissionEditor->findingstatic == NULL)
				{
//					 MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective = MissionEditor->TmpMainObjective;
  //					 MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective = MissionEditor->TmpSubObjective;
	//				 MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1 = MissionEditor->TmpWP1;
	  //				 MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2 = MissionEditor->TmpWP2;
		//			 MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3 = MissionEditor->TmpWP3;
				 }
				 break;
		  }
	  }
//	  if (		(MissionEditor->Initialising)
  //			&&	(MissionEditor->findingstatic == NULL)
	//		)
	  //	  MissionBaseForm->ProcessForm();
//	MissionEditor->PaintBox->Invalidate();
 	return true;
}

//---------------------------------------------------------------------------
__fastcall TMissionObjectivesForm::OpenForm()
{
	InitForm();
	ProcessForm();
    return true;
}
//---------------------------------------------------------------------------

void __fastcall TMissionObjectivesForm::Button0Click(TObject *Sender)
{
	MissionEditor->SetFindingStaticMode(SETMAINOBJECTIVE);
	Close();
//	MissionEditor->PaintBox->Invalidate();

}
//---------------------------------------------------------------------------
void __fastcall TMissionObjectivesForm::Button1Click(TObject *Sender)
{
	MissionEditor->SetFindingStaticMode(SETSUBOBJECTIVE);
	Close();
//	MissionEditor->PaintBox->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TMissionObjectivesForm::Button2Click(TObject *Sender)
{
	MissionEditor->SetFindingStaticMode(SETWP1);            	
   	Close();
//    MissionEditor->PaintBox->Invalidate();
	                                       
}
//---------------------------------------------------------------------------
void __fastcall TMissionObjectivesForm::Button3Click(TObject *Sender)
{
	MissionEditor->SetFindingStaticMode(SETWP2);            	
   	Close();
//    MissionEditor->PaintBox->Invalidate();
	                                          
}
//---------------------------------------------------------------------------
void __fastcall TMissionObjectivesForm::Button4Click(TObject *Sender)
{
	MissionEditor->SetFindingStaticMode(SETWP3);            	
   	Close();
//    MissionEditor->PaintBox->Invalidate();
	                                          
}
//---------------------------------------------------------------------------
