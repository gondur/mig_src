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

#include "AcItem.h"
#include "meMain.h"
//#include "strings.h"
#include "sqinfo.h"

#include "strings.h"
			  
#include "waypoint.h"
#include	"text.h"
#include	"worldinc.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include "GrndGrp.h"
//#include "bfnumber.h"
 #include "bfenum.h"
#include "readenum.h"


extern TypeData	typedata[];
extern int AlliedAircraftAvailableToFly[];
extern int CPAircraftAvailableToFly[];
extern int AlliedAircraftAvailable[];
extern int CPAircraftAvailable[];

//---------------------------------------------------------------------------
#pragma link "sampreg"
//DeadCode DAW 03Sep97 #pragma link "spin"
#pragma resource "*.dfm"
TAcItemForm *AcItemForm;
//---------------------------------------------------------------------------
__fastcall TAcItemForm::TAcItemForm(TComponent* Owner)
	: TForm(Owner)
{
	Font->Color = clWindow;
	Font->Color = clWindowText;
}
//---------------------------------------------------------------------------

void __fastcall TAcItemForm::DeleteCurrTransItem()
{
	ItemBasePtr	I=Persons2::ConvertPtrUID(MissionEditor->currobj);


	if ((int)I->Status.size>(int)MOBILESIZE)
	{
		info_airgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
//CAMP		if ((int)MissionEditor->currobj != (int)MissionEditor->ActiveCampaign.PlayerAcuid)
//CAMP		{
			if ((int)tmp->nat == (int)NAT_RED)
			MissionEditor->RedAcCnt -=  tmp->inform.Evaluate();
			else
			MissionEditor->BlueAcCnt -=  tmp->inform.Evaluate();
//CAMP		}
	}else if ((int)I->Status.size == (int)MOBILESIZE)
   {
		info_grndgrp*	G=*Persons2::ConvertPtrUID(MissionEditor->currobj);
		UniqueIDBand	uidband = Persons2::getbandfromUID(MissionEditor->currobj);

//		if (	((int)G->shape == (int)BTANK)
  //			||  ((int)G->shape == (int)GTANK)
//			)
  //    {
//			if ((int)uidband == (int)RedSAMBAND)
  //	 			MissionEditor->RedTanksCnt -=  G->inform.Evaluate();
//			else
  //			MissionEditor->BlueTanksCnt -=  G->inform.Evaluate();
//		}else
		{
  			if ((int)uidband == (int)RedTruckBAND)
   			MissionEditor->RedGroundMobilesCnt -=  G->inform.Evaluate();
  			else
   			MissionEditor->BlueGroundMobilesCnt -=  G->inform.Evaluate();
		}
   }else
   {
		//info_itemS*	 G=*Persons_2.ConvertPtrUID(MissionEditor->currobj);
		UniqueIDBand	uidband = Persons2::getbandfromUID(MissionEditor->currobj);

		switch (uidband)
		{
		case	RedSAMBAND:				MissionEditor->RedTanksCnt--;			break;
		case	BlueSAMBAND:			MissionEditor->BlueTanksCnt--;			break;
		case	RedArmourBAND:			MissionEditor->RedGroundMobilesCnt--;	break;
		case	BlueArmourBAND:			MissionEditor->BlueGroundMobilesCnt--;	break;
		case	BlueGICBAND:	//there is an associated winch...
		case	RedGICBAND:
		{
			UniqueID u=(UniqueID)AmberCivilianBAND;
			info_itemS*	i;
			while ((int)u<=(int)IllegalSepID)
			{
				i=	*Persons2::ConvertPtrUID(u);
				if (i)
					if (i->position[0].Evaluate()==MissionEditor->currobj)
						break;
				u=UniqueID(int(u)+1);
			}
			Persons2::delUID(u);
			delete i;
		}
		break;					
		}
   }   
   
	if ((int)I->Status.size>=(int)MOBILESIZE)
	{
		info_grndgrp*	M=*I;
		UniqueID u=M->wpref;
		while (u)
		{
			info_waypoint* W=*Persons2::ConvertPtrUID(u);
			Persons2::delUID(u);
			MissionEditor->WayPointCnt--;
			if (MissionEditor->WayPointCnt < 0)
				MissionEditor->WayPointCnt = 0;
			u=W->nextwp;   
			MissionEditor->DisableWPUsageifnecessary();
			delete W;
		}
		MissionEditor->currwp=UID_Null;
	}
	//delete target if necessary
	MissionEditor->CheckObjectives();
//	if	((int)MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective ==  (int)MissionEditor->currobj)
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].MainObjective =  NULL;
//	else if ((int)MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective ==  (int)MissionEditor->currobj)
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].SubObjective =  NULL;
//	else if ((int)MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1 ==  (int)MissionEditor->currobj)
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP1 =  NULL;
//	else if ((int)MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2 ==  (int)MissionEditor->currobj)
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP2 =  NULL;
//	else if ((int)MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3 ==  (int)MissionEditor->currobj)
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].WP3 =  NULL;

	MissionEditor->UnLockTargetWayPoint(MissionEditor->currobj);


	Persons2::delUID(MissionEditor->currobj);
//camp	if (MissionEditor->ActiveCampaign.PlayerAcuid == MissionEditor->currobj)
//camp	{
//camp			MissionEditor->ActiveCampaign.PlayerAcuid = UID_Null;
//camp			MissionEditor->MissionStarted = false;
//camp
//camp	}
	MissionEditor->currobj=UID_Null;
	delete I;
//	MissionEditor->PaintBox->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::AcceptChanges()
{
	info_airgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	MissionEditor->loadedbfs[tmp->bfieldindex].changed=true;
//	MissionEditor->MissionEdited=true;

//		strcpy(tmp->squadronname,SquadronName);
	tmp->squadron = Squadron;

//camp	if (MissionEditor->ActiveCampaign.PlayerAcuid != tmpplayeracuid)
//camp	{
//camp		MissionEditor->MissionStarted = true;
//camp		MissionEditor->ActiveCampaign.PlayerAcuid = tmpplayeracuid;
//camp		if (MissionEditor->ActiveCampaign.PlayerAcuid == MissionEditor->currobj)
//camp			MissionEditor->MakePlayerAc(true);
//camp		else
//camp		{
//camp			MissionEditor->MissionStarted = false;
//camp			MissionEditor->MakePlayerAc(false);
//camp		}
//camp	}

//camp	if ((int)MissionEditor->currobj == (int)MissionEditor->ActiveCampaign.PlayerAcuid)
//camp	{
//camp		int PlayerNat =  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerNationality;
//camp		if (PlayerNat == (int)NAT_BLUE)
//camp			 MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerAcType= MissionEditor->FindOrginalIndex(
//camp				IDS_PLANE_TYPE_CAMEL,
//camp											IDS_PLANE_TYPE_FOKKER_D7,
//camp						AircraftComboBox->ItemIndex,AlliedAircraftAvailableToFly);
//camp		else
//camp			 MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerAcType= MissionEditor->FindOrginalIndex(
//camp				IDS_PLANE_TYPE_CAMEL,
//camp											IDS_PLANE_TYPE_FOKKER_D7,
//camp						AircraftComboBox->ItemIndex,CPAircraftAvailableToFly);
//camp
//camp		MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].
//camp			formationtypeindex = FormComboBox->ItemIndex;
//camp		MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofsquadronac
//camp					= WingSizeSpinEdit->Value;
//camp		MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofflightac
//camp					= FormSizeSpinEdit->Value;
//camp		tmp->form = ENABLE_COMPLEX_VAL;
//camp		tmp->inform = ENABLE_COMPLEX_VAL;
//camp		tmp->inwing = ENABLE_COMPLEX_VAL;
//camp		tmp->type = ENABLE_COMPLEX_VAL;
//camp		tmp->shape = ENABLE_COMPLEX_VAL;
//camp	}
//camp	else
	{
		tmp->form = FormComboBox->ItemIndex;
		tmp->inwing = FormSizeSpinEdit->Value;
		if ((int)tmp->nat == (int)NAT_RED)
		{
			MissionEditor->RedAcCnt -=  tmp->inform.Evaluate();
			tmp->inform = WingSizeSpinEdit->Value;
			MissionEditor->RedAcCnt +=  (int)tmp->inform;
		}else
		{
			MissionEditor->BlueAcCnt -=  tmp->inform.Evaluate();
            tmp->inform = WingSizeSpinEdit->Value;
			MissionEditor->BlueAcCnt +=  (int)tmp->inform;
		}
	}

	if (MissionEditor->Configure_Units == METRIC)
	{
				tmp->vel = (MissionEditor->ValidEdit(SpeedEdit) * 100+50)/36;
				if (tmp->position[0].Evaluate()==ENABLE_COMPLEX_VAL)
					tmp->position[0][1]=
						tmp->World.Y = 100 *  - MissionEditor->ValidEdit(AltEdit);
//				if (tmp->pos[0].complex && tmp->pos[0]->type==Expr::EXPR_XYZ)
///					tmp->pos[0][1] = StrToInt(AltEdit->Text) * 100;
//				else
///				if (tmp->pos[1].complex && tmp->pos[1]->type==Expr::EXPR_XYZ)
//					tmp->pos[1][1] = StrToInt(AltEdit->Text) * 100;

			}elseif (MissionEditor->Configure_Units == IMPERIAL)
			{
				tmp->vel = (MissionEditor->ValidEdit(SpeedEdit) * 1000+500)/224;
				if (tmp->position[0].Evaluate()==ENABLE_COMPLEX_VAL)
					tmp->position[0][1]=
						tmp->World.Y = 3048 *  - MissionEditor->ValidEdit(AltEdit) / 100;
///				if (tmp->pos[0].complex && tmp->pos[0]->type==Expr::EXPR_XYZ)
//					tmp->pos[0][1] = StrToInt(AltEdit->Text) * 3048/100;
///				else
//				if (tmp->pos[1].complex && tmp->pos[1]->type==Expr::EXPR_XYZ)
//					tmp->pos[1][1] = StrToInt(AltEdit->Text) * 3048/100;
			}else
			{
				tmp->vel = (MissionEditor->ValidEdit(SpeedEdit) * 100+50)/36;
				if (tmp->position[0].Evaluate()==ENABLE_COMPLEX_VAL)
					tmp->position[0][1]=
						tmp->World.Y = 3048 *  - MissionEditor->ValidEdit(AltEdit) / 100;
			}

	if (Bombs->Checked)
		tmp->bombs = 4;
	else
		tmp->bombs = ENABLE_COMPLEX_VAL;

}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::InitForm(int X, int Y)
{
	int left = AcItemForm->Left;
	int top = AcItemForm->Top;
	info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);

	if (X != 0)
		MissionEditor->FormCoords(X,Y,AcItemFormId,left,top,
							AcItemForm->Width,AcItemForm->Height);

	acvel = ac->vel.Evaluate();
	//the form needs a temp Y.
   //it is used in refresh form
   //	it is set here and when the altitude is changed so
   //that a refresh is possible
   //A refresh is needed after a alt change because the speed may have to be changed
   //as well
	WorldY = ac->World.Y;

	AcItemForm->Left = left;
	AcItemForm->Top = top;

	Squadron = ac->squadron;
	tmphomebase = ac->homebase;
//	if (Squadron == 0)
//	{
//		if (MissionEditor->ActiveCampaign.
//				mission[MissionEditor->currmission].PlayerNationality ==
//					ac->nat)
//			Squadron = 2;
//		else
//			Squadron = -2;
//		SquadronDataForm->ForceSqadUpdate(Squadron);
//		ac->homebase = tmphomebase;
//		if ((int)ac->nat ==(int)NAT_BLUE)
//			ac->type = MissionEditor->FindOrginalIndex(
//					IDS_PLANE_TYPE_CAMEL,
//						IDS_PLANE_TYPE_SE5,
//							SquadronDataForm->AcComboBoxItemIndex,AlliedAircraftAvailable);
//		else
//			ac->type = MissionEditor->FindOrginalIndex(
//					IDS_PLANE_TYPE_CAMEL,
//						IDS_PLANE_TYPE_SE5,
//							SquadronDataForm->AcComboBoxItemIndex,CPAircraftAvailable);
//
//
//	}
//
	SquadronDataForm->InitForm();

//	strcpy(SquadronName,ac->squadronname);

//camp	int PlayerAcType =  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerAcType;
//	int PlayerNat =  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerNationality;

//	if (PlayerNat == (int)NAT_BLUE)
//		MissionEditor->PartFillComboBox(	IDS_PLANE_TYPE_CAMEL,
//											IDS_PLANE_TYPE_FOKKER_D7,
//											AircraftComboBox,
//											0,//PlayerAcType,
//                                            AlliedAircraftAvailableToFly);
//	else
//		MissionEditor->PartFillComboBox(	IDS_PLANE_TYPE_CAMEL,
  //											IDS_PLANE_TYPE_FOKKER_D7,
	//										AircraftComboBox,
	  //										0,//PlayerAcType,
        //                                    CPAircraftAvailableToFly);




	tmpplayeracuid =   0;//	MissionEditor->ActiveCampaign.PlayerAcuid;
//	if ((int)MissionEditor->currobj == (int)MissionEditor->ActiveCampaign.PlayerAcuid)
//	{
//		PlayerCheckBox->Checked = true;
//	}
//	else
	{
		PlayerCheckBox->Checked = false;
	}

	if (ac->bombs.Evaluate() == ENABLE_COMPLEX_VAL)
		  Bombs->Checked = false;
	else
		  Bombs->Checked = true;

	SetMaxAc();
}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::SetMaxAc()
{
	info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);

   int maxac,currac;
	if ((int)MissionEditor->currobj == (int)tmpplayeracuid)
   {
	maxac = 12;
	}else
   {
	currac = ac->inform.Evaluate();
	  maxac = 18;
		if ((int)ac->nat == (int)NAT_RED)
	   {
		if ((maxac+MissionEditor->RedAcCnt-currac) > MissionEditor->RedAcMax)
			maxac = MissionEditor->RedAcMax - MissionEditor->RedAcCnt+currac;
	   }else
	   {
		if ((maxac+MissionEditor->BlueAcCnt-currac) > MissionEditor->BlueAcMax)
			maxac = MissionEditor->BlueAcMax - MissionEditor->BlueAcCnt+currac;
	   }
   }

   WingSizeSpinEdit->MaxValue = maxac;
	#define		TEXT_STACKED						4680
	#define		TEXT_SHEPHERD           			4687
//camp	if ((int)MissionEditor->currobj == (int)tmpplayeracuid)
//	{
//
//		FormSizeSpinEdit->Value = MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofflightac;
//		WingSizeSpinEdit->Value = MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofsquadronac;
//		MissionEditor->FillComboBox(TEXT_STACKED, TEXT_SHEPHERD, FormComboBox,
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].
//					formationtypeindex);
//	}else
	{
		MissionEditor->FillComboBox(TEXT_STACKED, TEXT_SHEPHERD, FormComboBox, ac->form);
		if (ac->inform!=ENABLE_COMPLEX_VAL)
			WingSizeSpinEdit->Value = ac->inform.Evaluate();
		else
			WingSizeSpinEdit->Value = 1;
		if (ac->inwing!=ENABLE_COMPLEX_VAL)
			FormSizeSpinEdit->Value = ac->inwing;
		else
			FormSizeSpinEdit->Value = 1;
	}
}

//---------------------------------------------------------------------------
void __fastcall TAcItemForm::ProcessForm(int X, int Y)
{
	RefreshForm();
	int result = ShowModal();
	switch (result)
	{
		case	mrRoute:
		{
			AcceptChanges();
			info_grndgrp*	g=*Persons2::ConvertPtrUID(MissionEditor->currobj);
			MissionEditor->currwp = g->wpref;

			WayPointForm->ShowWpDialog( X,Y);
		}
		case	mrOk:
		{
			AcceptChanges();
//			MissionEditor->PaintBox->Invalidate();
			break;
		}
		case	mr_Cancel:
		{
			info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);
			ac->homebase = tmphomebase;
			SquadronDataForm->SetLandingWP();

			break;
		}
		case	mrDelete:
		{
			DeleteCurrTransItem();
//		 MissionEditor->PaintBox->Invalidate();
			break;
		}
	}


   //MissionEditor->AcSpdButtonState();
	MissionEditor->DisableWPUsageifnecessary();	//rdh


}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::RefreshForm()
{
	char	buffer[50];
	char	data[50];

	info_airgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	int actype;

//	if ((int)MissionEditor->currobj != (int)MissionEditor->ActiveCampaign.PlayerAcuid)
		actype = tmp->type;
//	else
//		actype =  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerAcType;

	if ((int)MissionEditor->currobj == (int)tmpplayeracuid)
	{
		PlayerCheckBox->Enabled = true;
		SquadronLabel->Visible = false;
		SquadButton->Visible = false;
		AircraftComboBox->Visible = true;
		AircraftLabel->Visible = true;

	}
	else
	{
//		if (	(tmpplayeracuid)
//			  ||		((int)tmp->nat != (int)MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerNationality)
//		 )
			PlayerCheckBox->Enabled = false;
//		else
//			PlayerCheckBox->Enabled = true;
		AircraftComboBox->Visible = false;
		AircraftLabel->Visible = false;
		SquadronLabel->Visible = true;
		SquadButton->Visible = true;
	}

	if (Squadron == 0)
		LoadString(HInstance,IDS_SQUADRONINFO,buffer,sizeof(buffer));
	else
	{

		SquadronDataForm->ExtractSquadName();
		strcpy(buffer,SquadronName);
		strcat(buffer," (");
		LoadString(HInstance,(int)IDS_PLANE_TYPE_CAMEL+(int)tmp->type,data,sizeof(data));
		strcat(buffer,data);
		strcat(buffer,")");
	}
	SquadronLabel->Caption = buffer;

//	#define		TEXT_STACKED						4680
//	#define		TEXT_SHEPHERD           			4687
//	if ((int)MissionEditor->currobj == (int)tmpplayeracuid)
//	{
//
//		FormSizeSpinEdit->Value = MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofflightac;
//		WingSizeSpinEdit->Value = MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofsquadronac;
//		MissionEditor->FillComboBox(TEXT_STACKED, TEXT_SHEPHERD, FormComboBox,
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].
//					formationtypeindex);
//	}else
//	{
//		MissionEditor->FillComboBox(TEXT_STACKED, TEXT_SHEPHERD, FormComboBox, tmp->form);
//		if (tmp->inform!=ENABLE_COMPLEX_VAL)
//			WingSizeSpinEdit->Value = tmp->inform.Evaluate();
//		else
//			WingSizeSpinEdit->Value = 1;
//		if (tmp->inwing!=ENABLE_COMPLEX_VAL)
//			FormSizeSpinEdit->Value = tmp->inwing;
//		else
//			FormSizeSpinEdit->Value = 1;
//	}
	if ( acvel == ENABLE_COMPLEX_VAL)			//default set and never been filled in
		   acvel = typedata[actype].cruisevel;

	char	altitude[50];
	char	spdbuff[50];

	 LoadString(HInstance,TEXT_SPD,spdbuff,sizeof(spdbuff));
	 LoadString(HInstance,TEXT_ALT,altitude,sizeof(altitude));

	SpeedEdit->OnChange = NULL;
	AltEdit->OnChange = NULL;
	if (MissionEditor->Configure_Units == METRIC)
	{
		strcat(spdbuff,"kmh");
		strcat(altitude,"m");

	  SpeedEdit->Text = IntToStr((int)(acvel*36+18)/100);
	  AltEdit->Text = IntToStr(-WorldY/100);
	}else if (MissionEditor->Configure_Units == IMPERIAL)
	{
		strcat(spdbuff,"mph");
	  SpeedEdit->Text = IntToStr((int)(acvel*224+112)/1000);
	  AltEdit->Text = IntToStr(-(WorldY*100-50)/3048);
		strcat(altitude,"ft");
	}else
	{
		strcat(spdbuff,"kmh");
	  SpeedEdit->Text = IntToStr((int)(acvel*36+18)/100);
	  AltEdit->Text = IntToStr(-(WorldY*100-50)/3048);
		strcat(altitude,"ft");
	}


   SpeedLabel->Caption = spdbuff;
   AltLabel->Caption = altitude;

	CheckSpeedField();
	SpeedEdit->OnChange = SpeedEditChange;
	AltEdit->OnChange = AltEditChange;


   if (tmp->position[0].Evaluate()!=ENABLE_COMPLEX_VAL)
   {
   //then tmp->position[0].Evaluate() is the UID of the take-off airfield
		AltEdit->Enabled = false;
		char	buff[50];
		int uid = tmp->position[0].Evaluate();
		char*	tmp =  GetList(ENUM_UIDtitle).Translate(uid);
		if (tmp == NULL)
		{
			int text = MissionEditor->GetBandorShapeText(uid);
			LoadString(HInstance,text,buff,sizeof(buff));
			Position->Text = buff;
		}else
			Position->Text = tmp;
	}else
	{
		AltEdit->Enabled = true;
		Position->Text = "";
	}
}

//---------------------------------------------------------------------------
void __fastcall TAcItemForm::OpenAcItem(int X, int Y)
{
	InitForm(X,Y);
	ProcessForm(X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TAcItemForm::SquadButtonClick(TObject *Sender)
{
	SquadronDataForm->OpenForm();
	RefreshForm();
}

void __fastcall TAcItemForm::PositionButtonClick(TObject *Sender)
{
//	info_airgrp* I=*Persons_2.ConvertPtrUID(MissionEditor->currobj);
//	MissionEditor->UIDLocation=(UniqueID*)&I->Target;

	MissionEditor->SetFindingStaticMode(SETTAKEOFFPOINT);
	Close();
//	MissionEditor->PaintBox->Invalidate();
	MissionEditor->draggingdelay=DRAGGINGLEFT;

}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::AltEditExit(TObject *Sender)
{
	if (MissionEditor->Configure_Units == METRIC)
		WorldY = 100 *  - MissionEditor->ValidEdit(AltEdit);
	else if (MissionEditor->Configure_Units == IMPERIAL)
		WorldY = 3048 *  - MissionEditor->ValidEdit(AltEdit) / 100;
	else
	  WorldY = 3048 *  - MissionEditor->ValidEdit(AltEdit) / 100;
	if (WorldY > 500000)
		WorldY = 500000;		
	if (WorldY < -500000)
		WorldY = -500000;		
			 
	RefreshForm();			 
//	CheckSpeedField();
}
//---------------------------------------------------------------------------

void __fastcall TAcItemForm::CheckSpeedField()
{
   int SpdComboBoxIndex;

	if (MissionEditor->ValidEdit(AltEdit) == 0)
	{
		SpdComboBox->Enabled = false;
		SpeedSpin->Enabled = false;
	  SpeedEdit->Text = IntToStr(0);
	  SpeedEdit->Enabled = false;
	  SpeedLabel->Enabled = false;
	// SpdComboBoxIndex = 1;

	}else
	{
		SpdComboBox->Enabled = true;
		SpeedSpin->Enabled = true;
	  SpeedEdit->Enabled = true;
	  SpeedLabel->Enabled = true;

	}

	SpdComboBoxIndex = FindVel(acvel);
	MissionEditor->FillComboBox(TEXT_MINVEL,
								TEXT_CUSTOM,
											SpdComboBox,
											SpdComboBoxIndex);
   
}

void __fastcall TAcItemForm::PlayerCheckBoxMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (tmpplayeracuid)
		tmpplayeracuid = UID_Null;
	else
		tmpplayeracuid = MissionEditor->currobj;

  SetMaxAc();
  if (WingSizeSpinEdit->MaxValue <= 0)
  {
		PlayerCheckBoxMouseDown(Sender, Button, Shift, X, Y);
  }else
  {   
  		InitForm(0,0);
		RefreshForm();
  }	
}
//---------------------------------------------------------------------------


void __fastcall TAcItemForm::SpeedEditChange(TObject *Sender)
{
	info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	int actype;

//	if ((int)MissionEditor->currobj != (int)MissionEditor->ActiveCampaign.PlayerAcuid)
		actype = tmp->type;
//	else
//		actype =  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerAcType;
			 
	if (MissionEditor->Configure_Units == METRIC)
		acvel =  (100 * MissionEditor->ValidEdit(SpeedEdit)+50) /36;
	else	if (MissionEditor->Configure_Units == IMPERIAL)
		acvel =  (1000 * MissionEditor->ValidEdit(SpeedEdit)+500) /224;
	else
		acvel =  (100 * MissionEditor->ValidEdit(SpeedEdit)+50) /36;

	if ((int)acvel > (int)typedata[actype].maxvel)
		acvel = typedata[actype].maxvel; 
	if ((int)acvel < (int)typedata[actype].climbvel)
		acvel = typedata[actype].climbvel; 
	 
	if ((int)acvel == (int)typedata[actype].cruisevel)
	acvel = ENABLE_COMPLEX_VAL;
	RefreshForm();
	  

		   
}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::SpdComboBoxChange(TObject *Sender)
{
	info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	int actype;

//	if ((int)MissionEditor->currobj != (int)MissionEditor->ActiveCampaign.PlayerAcuid)
		actype = tmp->type;
//	else
//		actype =  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerAcType;

	switch	(SpdComboBox->ItemIndex)
	{
		case	0:
		{
			acvel = typedata[actype].climbvel;
			break;
		}
		case	1:
		{
			acvel = typedata[actype].cruisevel;
			break;
		}
		case	2:
		{
			acvel = typedata[actype].maxvel;
			break;
		}
		case	3:
		{
			break;
		}
	}
	RefreshForm();

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int  __fastcall TAcItemForm::FindVel( int& vel)
{
	info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	int actype;

//	if ((int)MissionEditor->currobj != (int)MissionEditor->ActiveCampaign.PlayerAcuid)
		actype = tmp->type;
//	else
//		actype =  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].PlayerAcType;


	int retval;
	int delta = 1;
	if (vel == ENABLE_COMPLEX_VAL)			//default set and never been filled in
	{
		vel = typedata[tmp->type].cruisevel;
	//  retval =1;
	}
	if (		((vel - typedata[actype].cruisevel + delta ) <= (2*delta))
				&&  ((vel - typedata[actype].cruisevel + delta ) >= 0)
		  )
	{
		vel = typedata[actype].cruisevel;
	  retval =1;
	}
	else if (		((vel - typedata[actype].climbvel + delta ) <= (2*delta))
				&&  ((vel - typedata[actype].climbvel + delta ) >= 0)
			)
	{
	  vel = typedata[actype].climbvel;
	  retval =0;
	}
	else if (		((vel - typedata[actype].maxvel + delta ) <= (2*delta))
				&&  ((vel - typedata[actype].maxvel + delta ) >= 0)
			)
	{
	  vel = typedata[actype].maxvel;
	  retval =2;
	}
	else
	  retval =3;
	return (retval);
}


void __fastcall TAcItemForm::FormSizeSpinEditMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	GroundGroupForm->ValidSpinEdit(FormSizeSpinEdit);



}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::WingSizeSpinEditMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	GroundGroupForm->ValidSpinEdit(WingSizeSpinEdit);

	GroundGroupForm->ValidSpinEdit(WingSizeSpinEdit);


}

//---------------------------------------------------------------------------
void __fastcall TAcItemForm::FormSizeSpinEditChange(TObject *Sender)
{
	if (FormSizeSpinEdit->Value > WingSizeSpinEdit->Value)
		WingSizeSpinEdit->Value = FormSizeSpinEdit->Value;
	if (FormSizeSpinEdit->Value > 6)
		FormSizeSpinEdit->Value  = 6;
	if (FormSizeSpinEdit->Value < 1)
		FormSizeSpinEdit->Value  = 1;
}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::WingSizeSpinEditChange(TObject *Sender)
{
//	FormSizeSpinEdit->MaxValue = WingSizeSpinEdit->Value;

	FormSizeSpinEdit->MinValue = 1;
	if (FormSizeSpinEdit->MaxValue > 6)
		FormSizeSpinEdit->MaxValue = 6;
	if ((WingSizeSpinEdit->Value/3) > FormSizeSpinEdit->Value)
	{
		FormSizeSpinEdit->MinValue = WingSizeSpinEdit->Value/3;
		FormSizeSpinEdit->Value = WingSizeSpinEdit->Value/3;
	}
	if (WingSizeSpinEdit->Value < FormSizeSpinEdit->Value)
	{
		FormSizeSpinEdit->Value = WingSizeSpinEdit->Value;
	}

	if (FormSizeSpinEdit->Value > WingSizeSpinEdit->Value)
		WingSizeSpinEdit->Value = FormSizeSpinEdit->MaxValue;

	if (FormSizeSpinEdit->Value < 1)
		FormSizeSpinEdit->Value = 1;
	if (WingSizeSpinEdit->Value < 1)
		WingSizeSpinEdit->Value = 1;

}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::SpeedSpinDownClick(TObject *Sender)
{
		int i;
		i = StrToInt(SpeedEdit->Text);
		i = i - 1;
		SpeedEdit->Text = IntToStr(i);
	//shouldnot need next line, but do!
	AltEditExit(Sender);

}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::SpeedSpinUpClick(TObject *Sender)
{
		SpeedEdit->Text = IntToStr(StrToInt(SpeedEdit->Text) + 1);
	//shouldnot need next line, but do!
	AltEditExit(Sender);

}
//---------------------------------------------------------------------------
void __fastcall TAcItemForm::AltEditChange(TObject *Sender)
{
//	CheckSpeedField();

}
//---------------------------------------------------------------------------

