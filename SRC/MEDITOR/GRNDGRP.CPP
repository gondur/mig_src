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

#include	"text.h"
#include	"shapenum.g"
#include 	"memain.h"
#include	"worldinc.h"
#include	"bfnumber.h"
#include	"persons2.h"

#include "bfenum.h"
#include "readenum.h"
#include "GrndGrp.h"
#include	"globals.h"

//---------------------------------------------------------------------------
#pragma link "sampreg"
#pragma resource "*.dfm"


extern TypeData	typedata[];

TGroundGroupForm *GroundGroupForm;

int GroundFormCtrl[] = {-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,1};

int	AvailableShapes[4][256]={{0}};

int	UIDBandList[100]={0};
//---------------------------------------------------------------------------
__fastcall TGroundGroupForm::TGroundGroupForm(TComponent* Owner)
	: TForm(Owner)
{
	Font->Color = clWindow;
	Font->Color = clWindowText;
    dialheight[0][0]=0;
}
void  TGroundGroupForm::FillUIDBandList(int value)
{
	if (!UIDBandList[0])
    {
    	int j=0;
        UIDBandList[j++]=ENABLE_COMPLEX_VAL;
		for (int i=1;i<(int)IllegalSepID;i++)
        	if (GetList(ENUM_UIDBand).Translate(i))
            	UIDBandList[j++]=i;
		UIDBandList[j++]=0;
    }
    UIDGroupCombo->Clear();
    int index=0;
    for (int i=0,b;(b=UIDBandList[i])!=0;i++)
    {
    	if (b==value)
        	index=i;
		char* tmp =  GetList(ENUM_UIDBand).Translate(b);
        if (!tmp)
        	tmp="Default";
		UIDGroupCombo->Items->Add(tmp);
    }
	UIDGroupCombo->ItemIndex=index;
}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::GG_StatusComboBoxChange(TObject *Sender)
{
	info_itemS*		curritem;
	int			mapx,mapy;


	ItemBasePtr	I=Persons2::ConvertPtrUID(MissionEditor->currobj);


	if (  	(		((int)I->Status.size>=(int)MOBILESIZE)
				&&	(GG_StatusComboBox->ItemIndex != 0)
			)
		   ||	(		((int)I->Status.size<(int)MOBILESIZE)
					&&  (GG_StatusComboBox->ItemIndex == 0)
				)
		)

	{
		GGCancel->Enabled = false;
		curritem=*Persons2::ConvertPtrUID(MissionEditor->currobj);
		mapx=curritem->World.X;
		mapy=curritem->World.Z;
		MissionEditor->ScreenPosition(mapx,mapy);
		ShapeNum s = curritem->shape.Evaluate(2);

		UniqueIDBand	uidband;
		uidband = Persons2::getbandfromUID(MissionEditor->currobj);

		AcItemForm->DeleteCurrTransItem();

		//CurrNationality is used by the init item functions
		SWord	currnatbak = MissionEditor->CurrNationality;
		if (	(uidband == BlueSAMBAND)
			||	(uidband == BlueArmourBAND)
			)
			MissionEditor->CurrNationality = ALLIES;
		else
			MissionEditor->CurrNationality = CENTRALPOWERS;


		 if (GG_StatusComboBox->ItemIndex == 0)
		 {
			MissionEditor->SetMobile (true);
 //			if (	(s == BTANK)
   //				||  (s == GTANK)
	 //			)
	   //			MissionEditor->TopInitMobile(mapx,mapy,BlueSAMBAND,RedSAMBAND,s,s);
		 //	else
				MissionEditor->TopInitMobile(mapx,mapy,BlueArmourBAND,RedArmourBAND,s,s);

				GGRoute->Visible = true;
				GGSpeedLabel->Enabled = true;
				GGSpeedData->Enabled = true;
				SpdComboBox->Enabled = true;
				GGFormationSizeLabel->Enabled = true;
				GGFormationTypeLabel->Enabled = true;
				GGFormationSpinEdit->Value = 1;
				GGFormationSpinEdit->Enabled = true;
				GGFormTypeBox->Enabled = true;
		 }else
		 {
			MissionEditor->SetMobile (false);
//			if (	(s == BTANK)
  //				||  (s == GTANK)
	//			)
	  //			MissionEditor->TopInitStatic(mapx,0,mapy,BlueSAMBAND,RedSAMBAND,s,s);
		//	else
				MissionEditor->TopInitStatic(mapx,0,mapy,BlueArmourBAND,RedArmourBAND,s,s);
				GGRoute->Visible = false;
				GGSpeedLabel->Enabled = false;
				SpdComboBox->Enabled = false;
				GGSpeedData->Enabled = false;
				GGFormationSizeLabel->Enabled = false;
				GGFormationTypeLabel->Enabled = false;
				GGFormationSpinEdit->Enabled = false;
				GGFormationSpinEdit->Value = 1;
				GGFormTypeBox->Enabled = false;
		 }
		 MissionEditor->CurrNationality = currnatbak;
		MissionEditor->Invalidate();
	}

}
//DeadCode RDH 19Feb98 //---------------------------------------------------------------------------
//DeadCode RDH 19Feb98 int __fastcall TGroundGroupForm::GeneralFindShapes(int currshape)
//DeadCode RDH 19Feb98 {
//DeadCode RDH 19Feb98 	int i = 0;
//DeadCode RDH 19Feb98 	int	shapeindex;
//DeadCode RDH 19Feb98
//DeadCode RDH 19Feb98 	while (AvailableShapes[i] != currshape)
//DeadCode RDH 19Feb98
//DeadCode RDH 19Feb98 	{
//DeadCode RDH 19Feb98 		if ( (AvailableShapes[i] ==NULL) &&  (AvailableShapes[i+1] ==NULL))
//DeadCode RDH 19Feb98 			break;
//DeadCode RDH 19Feb98
//DeadCode RDH 19Feb98 		i++;
//DeadCode RDH 19Feb98 	}
//DeadCode RDH 19Feb98 	return(TEXT_FLAKBRIT+i-1);
//DeadCode RDH 19Feb98 }
//---------------------------------------------------------------------------
int __fastcall TGroundGroupForm::FindShapes(int currshape,int& groupindex,int shapepage)
{
	int i = 0;
	int firstnull = -1;
	int secondnull = -1;
	int	shapeindex;
    //25/10/98 DAVE: Ignore Mark's Edits here. Take my version!!
    if (!AvailableShapes[0][0])
    {
		int trg=0;
    	for (int src=0;src<256;src++)
        	if (	GetList(ENUM_ShapeTitle).Translate(src)	||	GetList(ENUM_Shape).Translate(src)	)
				AvailableShapes[0][trg++]=src;
    	AvailableShapes[0][trg++]=0;
        trg=0;
    	for (int src=256;src<512;src++)
        	if (	GetList(ENUM_ShapeTitle).Translate(src)	||	GetList(ENUM_Shape).Translate(src)	)
				AvailableShapes[1][trg++]=src;
        AvailableShapes[1][trg++]=0;
        trg=0;
    	for (int src=512;src<768;src++)
        	if (	GetList(ENUM_ShapeTitle).Translate(src)	||	GetList(ENUM_Shape).Translate(src)	)
				AvailableShapes[2][trg++]=src;
        AvailableShapes[2][trg++]=0;
        trg=0;
        GlobalsInfo* g;

    	for (int src=0;(g=(GlobalsInfo*)BFieldGlobalTable[src].reference)!=NULL;src++)
        	if (g->processor==&ShapeProcess)
				AvailableShapes[3][trg++]=src;
        AvailableShapes[3][trg++]=0;
    }

    if (shapepage==-1)
    	shapepage=currshape/256;

	SWord j = 1;
	char*	tmp;

	ShapeComboBox->Items->Clear();
	CurrShape->ShapeComboBox->Items->Clear();

    shapeindex=-1;
    if (shapepage==3)
    {
    	for (int src=0;AvailableShapes[shapepage][src];src++)
        {
            if (AvailableShapes[shapepage][src]==currshape)
            	shapeindex=src;
            char* tmp=((GlobalsInfo*)BFieldGlobalTable[AvailableShapes[shapepage][src]].reference)->identifier;
			ShapeComboBox->Items->Add(tmp);
        }
    }
    else
    {
    	for (int src=0;AvailableShapes[shapepage][src];src++)
        {
        	if (AvailableShapes[shapepage][src]==currshape)
            	shapeindex=src;
        	char* tmp=GetList(ENUM_ShapeTitle).Translate(AvailableShapes[shapepage][src]);
	        if (!tmp)
    	    	tmp=GetList(ENUM_Shape).Translate(AvailableShapes[shapepage][src]);
			ShapeComboBox->Items->Add(tmp);
        }
    }
	ShapeComboBox->ItemIndex =   shapeindex;
	CurrShape->ShapeComboBox->ItemIndex =   shapeindex;
    ShapeCat->ItemIndex=shapepage;
    currshapecat=shapepage;
   return(firstnull+1);
}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::OpenGroundGroupStatic(int X,int Y)
{
	char buff[50];
//    UniqueID CurrUID;
	if (!dialheight[0][0])
    {
    	dialheight[0][0]=Height;
        dialheight[0][1]=Panel1->Top;
        dialheight[0][2]=ButtonPanel->Top;
        int delta=GGPanel->Height;
		dialheight[1][0]=dialheight[0][0]-delta;
		dialheight[1][1]=dialheight[0][1]-delta;
		dialheight[1][2]=dialheight[0][2]-delta;
    }

    Height=dialheight[1][0];
    Panel1->Top=dialheight[1][1];
    ButtonPanel->Top=dialheight[1][2];

		GGAltLabel->Visible = false;
		GGEditAlt->Visible = false;

	UniqueIDBand	uidband;

	uidband = Persons2::getbandfromUID(MissionEditor->currobj);
	ItemBasePtr i=Persons2::ConvertPtrUID(MissionEditor->currobj);


//	MissionEditor->FillComboBox(IDS_CENTRALPOWERS, IDS_ALLIES, NationalityComboBox,
//										i->Nationality);

	info_itemS*	I= *Persons2::ConvertPtrUID(MissionEditor->currobj);
	int groupindex = -1;

	if (I->shape==ENABLE_COMPLEX_VAL)
    	if (I->shape->type==Expr::EXPR_GLOB)
            FindShapes(I->shape->UsesGlobRef(),groupindex,3);
        else
        	if (I->shape[2]->type==Expr::EXPR_GLOB)
	            FindShapes(I->shape[2]->UsesGlobRef(),groupindex,3);
            else
            	FindShapes(I->shape.Evaluate(2),groupindex,-1);
    else
        FindShapes(I->shape.Evaluate(2),groupindex,-1);

	FillUIDBandList(I->band.Evaluate());
//	MissionEditor->FillComboBox(IDS_CENTRALPOWERS, IDS_ALLIES, NationalityComboBox,
//										I->nationality-1);

		GGPanel->Visible = false;
//		ButtonPanel->Top = 38;
//		Height = 181;		//216;

		GGSpeedLabel->Visible = false;
		GGSpeedData->Visible = false;
		AltSpinButton->Visible = false;
		SpdComboBox->Visible = false;


	RefreshText();
    if (MissionEditor->loadedbfs[I->bfieldindex].name[0])
		BfieldLabel->Caption = MissionEditor->loadedbfs[I->bfieldindex].name;
    else
		BfieldLabel->Caption = MissionEditor->loadedbfs[I->bfieldindex].fname;


	switch (uidband)
	{
		case MissileBAND:
		{
			break;
		}
		case RedGICBAND:
		case BlueGICBAND:
		{
		GGAltLabel->Visible = true;
		GGEditAlt->Visible = true;
		GGPanel->Visible = true;
//		ButtonPanel->Top = 144;
//		Height = 279;



		char	altitude[50];

		 LoadString(HInstance,TEXT_ALT,altitude,sizeof(altitude));


		if (MissionEditor->Configure_Units == METRIC)
		{
		 strcat(altitude,"m");
		  GGEditAlt->Text = IntToStr(-i->World.Y/100);

		}else if (MissionEditor->Configure_Units == IMPERIAL)
		{
			strcat(altitude,"ft");
		  GGEditAlt->Text = IntToStr(-(i->World.Y*100-50)/3048);
		}else
		{
			strcat(altitude,"ft");
		  GGEditAlt->Text = IntToStr(-(i->World.Y*100-50)/3048);
		}

		   GGAltLabel->Caption = altitude;
		break;
		}
	 }
	 int text = MissionEditor->GetBandorShapeText(MissionEditor->currobj);
	 LoadString(HInstance,text,buff,sizeof(buff));
	 Caption = buff;


		GG_StatusLabel->Visible = true;
		GG_StatusComboBox->Visible = true;
		GGEventMore->Visible = false;
		GGRoute->Visible = false;
		GG_StatusComboBox->ItemIndex = 1;
		GG_StatusComboBox->Enabled = false;
		GGRoute->Visible = false;
		GGFormationSizeLabel->Visible = false;
		GGFormationTypeLabel->Visible = false;
		GGFormationSpinEdit->Visible = false;
		GGFormTypeBox->Visible = false;
		int result = ShowModal();
	   switch (result)
	   {
		   case	mrOk:
		   {
				info_itemS* I=*i;
                MissionEditor->loadedbfs[I->bfieldindex].changed=true;
  //				MissionEditor->MissionEdited=true;
				if (GGEditAlt->Visible)
				{


					if (MissionEditor->Configure_Units == METRIC)
						I->position[0][1] = -MissionEditor->ValidEdit(GGEditAlt) * 100;
					else	if (MissionEditor->Configure_Units == IMPERIAL)
						I->position[0][1] = -MissionEditor->ValidEdit(GGEditAlt) * 3048/100;
					else
						I->position[0][1] = -MissionEditor->ValidEdit(GGEditAlt) * 3048/100;
					I->position.EvalW(I->World);
				 }

                int shape=ShapeComboBox->ItemIndex;
                if (shape>=0)
                {
                	int shapepage=ShapeCat->ItemIndex;
                	if (shapepage==3)
                    {
                    	GlobRefExpr* gr=new GlobRefExpr(AvailableShapes[3][shape]);
						if (I->shape.complex && I->shape.complex->type==Expr::EXPR_FORM)
							I->shape[2]=gr;
						else
							I->shape = gr;
                    }
                    else
                    {
                    	shape=AvailableShapes[shapepage][shape];
						if (I->shape.complex && I->shape.complex->type==Expr::EXPR_FORM)
							I->shape[2]=shape;
						else
							I->shape = shape;
                    }
                }
                I->band= UIDBandList[UIDGroupCombo->ItemIndex];

//				I->nationality= NationalityComboBox->ItemIndex+1;
				MissionEditor->ChangeTag(groupindex,shape);

				EditText();

				break;
		   }
			case	mrDelete:
			{
				AcItemForm->DeleteCurrTransItem();
				break;
			}

		}
	//MissionEditor->MobileSpdButtonState();
	MissionEditor->DisableWPUsageifnecessary();	//rdh


}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::OpenGroundGroupEvent(int X,int Y)
{

	if (!dialheight[0][0])
    {
    	dialheight[0][0]=Height;
        dialheight[0][1]=Panel1->Top;
        dialheight[0][2]=ButtonPanel->Top;
        int delta=GGPanel->Height;
		dialheight[1][0]=dialheight[0][0]-delta;
		dialheight[1][1]=dialheight[0][1]-delta;
		dialheight[1][2]=dialheight[0][2]-delta;
    }

    Height=dialheight[1][0];
    Panel1->Top=dialheight[1][1];
    ButtonPanel->Top=dialheight[1][2];
		GGPanel->Visible = false;
//		ButtonPanel->Top = 4;
//		Height = 182;

//		ShapeLabel->Enabled = false;
		ShapeComboBox->Enabled = false;


		GGSpeedLabel->Visible = false;
		GGSpeedData->Visible = false;
		GGEventMore->Visible = true;
		Caption = " Event";
		GG_StatusLabel->Visible = false;
		GG_StatusComboBox->Visible = false;
		GGFormationSizeLabel->Visible = false;
		GGFormationTypeLabel->Visible = false;
		GGFormationSpinEdit->Visible = false;
		GGFormTypeBox->Visible = false;
		GGRoute->Visible = false;
		int result = ShowModal();
	   switch (result)
	   {
		   case	mrOk:
		   {
				break;
		   }
		   case	mrRoute:
		   {
				break;
		   }
			case	mrDelete:
			{
				AcItemForm->DeleteCurrTransItem();
				break;
			}
		}
//		ShapeLabel->Enabled = true;
		ShapeComboBox->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::RefreshSpeedInfo()
{
		char	spdbuff[50];
		info_grndgrp*	G=*Persons2::ConvertPtrUID(MissionEditor->currobj);
		
//rdh	   int	vel = G->vel.Evaluate();
	   if ( grndvel == ENABLE_COMPLEX_VAL)			//default set and never been filled in
			grndvel = typedata[G->type].cruisevel;
		 
		 LoadString(HInstance,TEXT_SPD2,spdbuff,sizeof(spdbuff));
	  
		if (MissionEditor->Configure_Units == METRIC)
		{
			strcat(spdbuff,"kmh");
		  GGSpeedData->Text = IntToStr((int)(grndvel*36+18)/100);

		}else if (MissionEditor->Configure_Units == IMPERIAL)
		{
			strcat(spdbuff,"mph"); 
		  GGSpeedData->Text = IntToStr((int)(grndvel*224+112)/1000);
		}else
		{
			strcat(spdbuff,"kmh"); 
		  GGSpeedData->Text = IntToStr((int)(grndvel*36+18)/100);
		}

		GGSpeedLabel->Caption = spdbuff;
		CheckSpeedField();

}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::OpenGroundGroupMobile(int X,int Y)
{

 //	int*	ctrlarray;
	char buff[50];

	if (!dialheight[0][0])
    {
    	dialheight[0][0]=Height;
        dialheight[0][1]=Panel1->Top;
        dialheight[0][2]=ButtonPanel->Top;
        int delta=GGPanel->Height;
		dialheight[1][0]=dialheight[0][0]-delta;
		dialheight[1][1]=dialheight[0][1]-delta;
		dialheight[1][2]=dialheight[0][2]-delta;
    }

    Height=dialheight[0][0];
    Panel1->Top=dialheight[0][1];
    ButtonPanel->Top=dialheight[0][2];
	info_grndgrp*	G=*Persons2::ConvertPtrUID(MissionEditor->currobj);

//	MissionEditor->FillComboBox(IDS_CENTRALPOWERS, IDS_ALLIES, NationalityComboBox,
//										G->Nationality);

	UniqueID	uidwp;

		GGAltLabel->Visible = false;
		GGEditAlt->Visible = false;

	int groupindex = -1;
	if (G->shape==ENABLE_COMPLEX_VAL)
    	if (G->shape->type==Expr::EXPR_GLOB)
            FindShapes(G->shape->UsesGlobRef(),groupindex,3);
        else
        	if (G->shape[2]->type==Expr::EXPR_GLOB)
	            FindShapes(G->shape[2]->UsesGlobRef(),groupindex,3);
            else
            	FindShapes(G->shape.Evaluate(2),groupindex,-1);
    else
        FindShapes(G->shape.Evaluate(2),groupindex,-1);
	RefreshText();
	BfieldLabel->Caption = MissionEditor->loadedbfs[G->bfieldindex].name;


	UniqueIDBand	uidband;

	if ((int)G->Status.size > (int)ITEMSIZE)
	{
		grndvel = G->vel.Evaluate();
		uidwp=G->wpref;
	}else
	{
		uidwp = UID_Null;
	}

	uidband = Persons2::getbandfromUID(MissionEditor->currobj);

	 int text = MissionEditor->GetBandorShapeText(MissionEditor->currobj);
	 LoadString(HInstance,text,buff,sizeof(buff));
	 Caption = buff;

		GGPanel->Visible = true;
//		ButtonPanel->Top = 147;
//		Height = 284;		//325;

//		MissionEditor->FillComboBox(IDS_CENTRALPOWERS, IDS_ALLIES, NationalityComboBox,
//										G->nationality-1);

		GGSpeedLabel->Visible = true;
		GGSpeedData->Visible = true;
		AltSpinButton->Visible = true;
		SpdComboBox->Visible = true;
		GGFormationSizeLabel->Visible = true;
		GGFormationTypeLabel->Visible = true;
		GGFormationSpinEdit->Visible = true;
		GGFormTypeBox->Visible = true;
		GG_StatusLabel->Visible = true;
		GG_StatusComboBox->Visible = true;
 //		if 	(	((int)G->shape.Evaluate(2) == (int)TRAIN3)
   //						  || ((int)G->shape.Evaluate(2) == (int)TRAIN4)
	 //		 )
	   //		GG_StatusComboBox->Enabled = false;
		//else
			GG_StatusComboBox->Enabled = true;

		GGEventMore->Visible = false;

	if ((int)G->Status.size > (int)ITEMSIZE)
//	if (uidwp != UID_Null)
	{

		GGRoute->Visible = true;
		GGRoute->Enabled = true;

		SpdComboBox->OnChange = NULL;
		RefreshSpeedInfo();
		SpdComboBox->OnChange = SpdComboBoxChange;


	   int	inform = G->inform.Evaluate();
	   if ( inform == ENABLE_COMPLEX_VAL)			//default set and never been filled in
			inform = 1;


	int maxmobiles = 6;
//		if (	((int)G->shape.Evaluate(2) == (int)BTANK)
  //			||  ((int)G->shape.Evaluate(2) == (int)GTANK)
	//	)
	  //{
		//		if ((int)uidband == (int)RedSAMBAND)
		  //	   {
			//	if ((maxmobiles+MissionEditor->RedTanksCnt-inform) > MissionEditor->RedTanksMax)
			//		maxmobiles = MissionEditor->RedTanksMax - MissionEditor->RedTanksCnt+inform;
		  //	   }else
		//	   {
	  //			if ((maxmobiles+MissionEditor->BlueTanksCnt-inform) > MissionEditor->BlueTanksMax)
	//				maxmobiles = MissionEditor->BlueTanksMax - MissionEditor->BlueTanksCnt+inform;
  //			   }
//		}else
	  {
				if ((int)uidband == (int)RedArmourBAND)
			   {
				if ((maxmobiles+MissionEditor->RedGroundMobilesCnt-inform) > MissionEditor->RedGroundMobilesMax)
					maxmobiles = MissionEditor->RedGroundMobilesMax - MissionEditor->RedGroundMobilesCnt+inform;
			   }else
			   {
				if ((maxmobiles+MissionEditor->BlueGroundMobilesCnt-inform) > MissionEditor->BlueGroundMobilesMax)
					maxmobiles = MissionEditor->BlueGroundMobilesMax - MissionEditor->BlueGroundMobilesCnt+inform;
			   }
	  }
		GGFormationSpinEdit->MaxValue = maxmobiles;
		GGFormationSpinEdit->Text = IntToStr(inform);

	   int	form = G->form.Evaluate();
	   if ( form == ENABLE_COMPLEX_VAL)			//default set and never been filled in
			form = IDS_TEXT_SINGLEFILE_FORM-IDS_TEXT_STACKED;

		MissionEditor->PartFillComboBox(IDS_TEXT_STACKED,
								IDS_TEXT_SINGLEFILE_FORM,
											GGFormTypeBox,
											form,GroundFormCtrl);



 //		if (	((int)G->band == (int)BlueSAMBAND)
//			||	((int)G->band == (int)RedSAMBAND)
//			||	((int)G->shape.Evaluate(2) == (int)TROOPS)
//			||	((int)G->shape.Evaluate(2) == (int)TROOP1)
//		   )	
//		 {
//			GGSpeedLabel->Enabled = false;
//			SpdComboBox->Enabled = false;  
//			GGSpeedData->Enabled = false;
//		 }else
//		 {
			GGSpeedLabel->Enabled = true;
			SpdComboBox->Enabled = true;  
			GGSpeedData->Enabled = true;
//		 }
			
		GGFormationSizeLabel->Enabled = true;
		GGFormationTypeLabel->Enabled = true;
		GGFormationSpinEdit->Enabled = true;

//		if (	((int)G->shape.Evaluate(2) == (int)TRAIN3)
  //			||  ((int)G->shape.Evaluate(2) == (int)TRAIN4)
	//	 )
	  //	 {
		//		GGFormTypeBox->Enabled = false;
	//		GGFormTypeBox->ItemIndex = IDS_TEXT_SINGLEFILE_FORM-IDS_TEXT_STACKED;
  //		 }
//		 else
			GGFormTypeBox->Enabled = true;
			GG_StatusComboBox->ItemIndex = 0;
	}else
	{
		GGRoute->Visible = false;
		GGRoute->Enabled = false;
		SpdComboBox->Enabled = false;  
		GGSpeedLabel->Enabled = false;
		GGSpeedData->Enabled = false;
		GGFormationSizeLabel->Enabled = false;
		GGFormationTypeLabel->Enabled = false;
		GGFormationSpinEdit->Value = 1;
		GGFormationSpinEdit->Enabled = false;
		GGFormTypeBox->Enabled = false;
		GG_StatusComboBox->ItemIndex = 1;
	}
	MissionEditor->currwp = uidwp;
	int result = GroundGroupForm->ShowModal();
//	MissionEditor->PaintBox->Invalidate();
	switch (result)
	{
		case	mrOk:
		{
//				MissionEditor->MissionEdited=true;

				info_itemS*		curritem =*Persons2::ConvertPtrUID(MissionEditor->currobj);
			MissionEditor->loadedbfs[curritem->bfieldindex].changed=true;

               int shape=ShapeComboBox->ItemIndex;
                if (shape>=0)
                {
                	int shapepage=ShapeCat->ItemIndex;
                	if (shapepage==3)
                    {
                    	GlobRefExpr* gr=new GlobRefExpr(AvailableShapes[3][shape]);
						if (G->shape.complex && G->shape.complex->type==Expr::EXPR_FORM)
							G->shape[2]=gr;
						else
							G->shape = gr;
                    }
                    else
                    {
                    	shape=AvailableShapes[shapepage][shape];
						if (G->shape.complex && G->shape.complex->type==Expr::EXPR_FORM)
							G->shape[2]=shape;
						else
							G->shape = shape;
                    }
                }
 				if (curritem->shape.complex && curritem->shape.complex->type==Expr::EXPR_FORM)
					curritem->shape[2]=shape;
				else
					curritem->shape = shape;
				MissionEditor->ChangeTag(groupindex,shape);

				if ((int)curritem->Status.size > (int)ITEMSIZE)
				{
					info_grndgrp*	G=*Persons2::ConvertPtrUID(MissionEditor->currobj);

//					if (	((int)G->shape.Evaluate(2) == (int)BTANK)
  //						||  ((int)G->shape.Evaluate(2) == (int)GTANK)
	//					)
	  //		   {
		//					if ((int)uidband == (int)RedSAMBAND)
		  //				   {
			//				MissionEditor->RedTanksCnt -=  G->inform;
			  //						G->inform =GGFormationSpinEdit->Value;
			  //				MissionEditor->RedTanksCnt +=  (int)G->inform;
			//				}else
		  //				 {
		//					MissionEditor->BlueTanksCnt -=  G->inform;
	  //								G->inform =GGFormationSpinEdit->Value;
	//						MissionEditor->BlueTanksCnt +=  (int)G->inform;
  //						 }
//					}else
			   {
							if ((int)uidband == (int)RedArmourBAND)
						   {
							MissionEditor->RedGroundMobilesCnt -=  G->inform;
						G->inform =GGFormationSpinEdit->Value;
							MissionEditor->RedGroundMobilesCnt +=  (int)G->inform;
							}else
						 {
							MissionEditor->BlueGroundMobilesCnt -=  G->inform;
						G->inform =GGFormationSpinEdit->Value;
							MissionEditor->BlueGroundMobilesCnt +=  (int)G->inform;
						 }
			   }
					G->form = MissionEditor->FindOrginalIndex(IDS_TEXT_STACKED,IDS_TEXT_SINGLEFILE_FORM,
									GGFormTypeBox->ItemIndex,GroundFormCtrl);

					if (GGSpeedData->Visible)
					{

						if (MissionEditor->Configure_Units == METRIC)
							G->vel = (MissionEditor->ValidEdit(GGSpeedData) * 100+50)/36;
						else if (MissionEditor->Configure_Units == IMPERIAL)
							G->vel = (MissionEditor->ValidEdit(GGSpeedData) * 1000+500)/224;
						else
							G->vel = (MissionEditor->ValidEdit(GGSpeedData) * 100+50)/36;
					 }
				}
				EditText();

				break;
		}
		case	mrRoute:
		{

			WayPointForm->ShowWpDialog( 0,0);
			break;
		}
			case	mrDelete:
			{
				AcItemForm->DeleteCurrTransItem();
				break;
			}
	}
	GGCancel->Enabled = true;
//	MissionEditor->MobileSpdButtonState();
	MissionEditor->DisableWPUsageifnecessary();	//rdh 

}
//---------------------------------------------------------------------------
void	__fastcall TGroundGroupForm::CheckandSetRoute()
 {

 //if item is required to be mobile
 //		if	it has no waypoints make one
 //else if it has waypoints delete them


//////	RodsWayPoint*	currwp;
//////	RodsWayPoint*	nextwp;

//////	if (GroundGroupForm->GG_StatusComboBox->ItemIndex == 0)
//////	{//mobile
//////		if (MissionEditor->CurrTransItem->waypoint == NULL)
//////			MissionEditor->MakeDefaultRoute(MissionEditor->CurrTransItem);
//////
//////	}else
//////	{
//////		if (MissionEditor->CurrTransItem->waypoint != NULL)
//////		{
//////			currwp = MissionEditor->CurrTransItem->waypoint;
//////			MissionEditor->CurrTransItem->waypoint = NULL;
//////			do{
//////				nextwp = currwp->next;
//////				delete (currwp);
//////				currwp = nextwp;
//////			}while (currwp != NULL);
//////
//////		}
//////
//////	}

 }


void __fastcall TGroundGroupForm::EventMoreClick(TObject *Sender)
{
//////	MissionEditor->CurrWp = MissionEditor->CurrTransItem->waypoint;
//////
//////	if (MissionEditor->CurrWp->eventinfo == NULL)
//////	{
//////		MissionEditor->CurrWp->eventinfo = new EventInfo;
//////		MissionEditor->CurrWp->eventinfo->prev  = NULL;
//////
//////		ChooseBfForm->InitEventInfo(MissionEditor->CurrWp->eventinfo);
//////		ChooseBfForm->GoToChooseBf();
//////
//////	}else
//////	{
//////		EventForm->SetEventVars();
//////	}


//////	info_grndgrp*	G=*Persons2::ConvertPtrUID(uid);
//////	UniqueID	uidwp=G->wpref;



}
//---------------------------------------------------------------------------

void __fastcall TGroundGroupForm::GGFormationSpinEditChange(TObject *Sender)
{
	ValidSpinEdit(GGFormationSpinEdit);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::ValidSpinEdit(TSpinEdit *editbox)
{
	int value = 0;
   char	chknumber[50];

	if (!(editbox->Text.IsEmpty()))
   {
		editbox->GetTextBuf(chknumber,sizeof(chknumber));
		int i =0;
		bool isnum = true;
        if (chknumber[i]=='-')
           i++;
		while (chknumber[i] != 0)
		{
			if ((chknumber[i] <'0') || (chknumber[i] > '9'))
				isnum = false;
			i++;
		}
		if (isnum)
			value = StrToInt(editbox->Text);
   }
	if(value > editbox->MaxValue)
		value = editbox->MaxValue;
   if (value < editbox->MinValue)
	   value = editbox->MinValue;

   editbox->Text = IntToStr(value);
}



//inline operator <=	(char i,TFileAttr j)	{return int(i)<=int(j);}
//inline operator >=	(char i,TFileAttr j)	{return int(i)>=int(j);}
//inline operator <=	(TFileAttr i,char j)	{return int(i)<=int(j);}
//inline operator >=	(TFileAttr i,char j)	{return int(i)>=int(j);}
//inline operator /	(TFileAttr i,char j)	{return int(i)/int(j);}
//inline operator %	(TFileAttr i,char j)	{return int(i)%int(j);}

//---------------------------------------------------------------------------

void __fastcall TGroundGroupForm::CheckSpeedField()
{
   int SpdComboBoxIndex;
		   
	SpdComboBoxIndex = AcItemForm->FindVel(grndvel);
	MissionEditor->FillComboBox(TEXT_MINVEL,
								TEXT_CUSTOM,
											SpdComboBox,
											SpdComboBoxIndex);
   
}

void __fastcall TGroundGroupForm::SpdComboBoxChange(TObject *Sender)
{
	info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);

	switch	(SpdComboBox->ItemIndex)
	{
		case	0:
		{
			grndvel = typedata[tmp->type].climbvel;
			break;
		}
		case	1:
		{
			grndvel = typedata[tmp->type].cruisevel;
			break;
		}
		case	2:
		{
			grndvel = typedata[tmp->type].maxvel;
			break;
		}
		case	3:
		{
			break;
		}
	}
	RefreshSpeedInfo();
	
}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::GGSpeedDataChange(TObject *Sender)
{
	info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);


	if (MissionEditor->Configure_Units == METRIC)
		grndvel =  (100 * MissionEditor->ValidEdit(GGSpeedData)+50) /36;
	else	if (MissionEditor->Configure_Units == IMPERIAL)
		grndvel =  (1000 * MissionEditor->ValidEdit(GGSpeedData)+500) /224;
	else
	   grndvel =  (100 * MissionEditor->ValidEdit(GGSpeedData)+50) /36;

	if ((int)grndvel > (int)typedata[tmp->type].maxvel)
		grndvel = typedata[tmp->type].maxvel;
	if ((int)grndvel < (int)typedata[tmp->type].climbvel)
		grndvel = typedata[tmp->type].climbvel;
		

	if ((int)grndvel == (int)typedata[tmp->type].cruisevel)
		grndvel = ENABLE_COMPLEX_VAL;
	RefreshSpeedInfo();

}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::AltSpinButtonDownClick(TObject *Sender)
{
		GGSpeedData->Text = IntToStr(StrToInt(GGSpeedData->Text) - 1);
			  
}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::AltSpinButtonUpClick(TObject *Sender)
{
		GGSpeedData->Text = IntToStr(StrToInt(GGSpeedData->Text) + 1);

}
//---------------------------------------------------------------------------

void __fastcall TGroundGroupForm::EditText()
{
	char buff[TITLE_LENGTH];
	char buffuid[UID_LENGTH];
	char buffdesc[DESCRIPTION_LENGTH];

	char*	tmp =  GetList(ENUM_UIDtitle).Translate(MissionEditor->currobj);
	if (tmp == NULL)
	{//only add if it does not exist, these could be a temp fix
		if (Edit_Title->Text!="None")
			GetList(ENUM_UIDtitle).Add(MissionEditor->currobj,Edit_Title->Text.c_str());
		if (Edit_UID->Text!="UID_")
			GetList(ENUM_UniqueID).Add(MissionEditor->currobj,Edit_UID->Text.c_str());
		if (Memo_Description->Lines->Text!="None")
			GetList(ENUM_UIDdesc).Add(MissionEditor->currobj,Memo_Description->Lines->Text.c_str());
	}
 }
//---------------------------------------------------------------------------

void __fastcall TGroundGroupForm::RefreshText()
{
	char buff[TITLE_LENGTH];
	char buffuid[UID_LENGTH];
	char buffdesc[DESCRIPTION_LENGTH];

 //	LoadString(HInstance,MissionEditor->currobj,buff,sizeof(buff));
	char*	tmp =  GetList(ENUM_UIDtitle).Translate(MissionEditor->currobj);

	if (tmp == NULL)
		Edit_Title->SetTextBuf("None");
	else
		Edit_Title->SetTextBuf(tmp);

	tmp = GetList(ENUM_UniqueID).Translate(MissionEditor->currobj);
	if (tmp  != NULL)
		Edit_UID->SetTextBuf(tmp);
	else
		Edit_UID->SetTextBuf("UID_");
	tmp = GetList(ENUM_UIDdesc).Translate(MissionEditor->currobj);
	if (tmp  != NULL)
		Memo_Description->SetTextBuf(tmp);
	else
		Memo_Description->SetTextBuf("None");

   info_itemS*	I= *Persons2::ConvertPtrUID(MissionEditor->currobj);
   SWord i = 0;

	bool	itemissupergroup = false;
	while ( i < MAXLOADEDSUPERGROUPS)
	{
		if	(MissionEditor->loadedsupergroup[i].uid  == MissionEditor->currobj)
			itemissupergroup = true;
		i++;
	}
	if (itemissupergroup)
	{
		SuperGroupCombo->Enabled = false;
		SuperGroupButton->Enabled = false;
		SuperGroupCombo->Items->Clear();

	}else
	{
		SuperGroupCombo->Enabled = true;
		SuperGroupButton->Enabled = true;
		SWord selection=-1;
		while (selection==-1)
		{
			SuperGroupCombo->Items->Clear();
			SuperGroupCombo->Items->Add("(none)");
			if (!I->SGT)
				selection=0;
			i =0;
			while ( 	( ++i < MAXLOADEDSUPERGROUPS)	)
				if (MissionEditor->loadedsupergroup[i].uid != AbsolutingSepID)
				{
					char* buff=GetList(ENUM_UIDtitle).Translate(MissionEditor->loadedsupergroup[i].uid);
					SuperGroupCombo->Items->Add(buff);
					if ( I->SGT == MissionEditor->loadedsupergroup[i].uid)
						selection=i;
				}
			if (selection==-1)
			{	//add new SG to list:
				i=1;
				while (MissionEditor->loadedsupergroup[i].uid != AbsolutingSepID)
					i++;
				MissionEditor->loadedsupergroup[i].uid=I->SGT;
			}
		}
		SuperGroupCombo->ItemIndex = selection;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::SuperGroupButtonClick(TObject *Sender)
{
	MissionEditor->SetFindingStaticMode(SETSUPERGROUP);
	Close();
//	MissionEditor->PaintBox->Invalidate();

}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::SuperGroupComboChange(TObject *Sender)
{
   info_itemS*	I= *Persons2::ConvertPtrUID(MissionEditor->currobj);
	I->SGT = MissionEditor->loadedsupergroup[SuperGroupCombo->ItemIndex].uid;
	MissionEditor->supergroupbeingfilled = SuperGroupCombo->ItemIndex;
	MissionEditor->SuperGroupStatusBar(I->SGT);

	RefreshText();
	MissionEditor->Invalidate();

}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::Edit_TitleClick(TObject *Sender)
{
		Edit_Title->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TGroundGroupForm::Edit_UIDExit(TObject *Sender)
{
	if (Edit_UID->Text=="")
		Edit_UID->Text="UID_";
}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::Edit_TitleEnter(TObject *Sender)
{
	if (Edit_Title->Text=="None")
		Edit_Title->Text="";

}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::Edit_TitleExit(TObject *Sender)
{
	if (Edit_Title->Text=="")
		Edit_Title->Text="None";

}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::Memo_DescriptionEnter(TObject *Sender)
{
	if (Memo_Description->Lines->Text=="None")
		Memo_Description->Lines->Text="";

}
//---------------------------------------------------------------------------
void __fastcall TGroundGroupForm::Memo_DescriptionExit(TObject *Sender)
{
	if (Memo_Description->Lines->Text=="")
		Memo_Description->Lines->Text="None";

}
//---------------------------------------------------------------------------

void __fastcall TGroundGroupForm::ShapeCatChange(TObject *Sender)
{
	int currshape=ShapeComboBox->ItemIndex;
    if (currshape>=0)
    	currshape=AvailableShapes[currshapecat][currshape];
	currshapecat=ShapeCat->ItemIndex;
    FindShapes(currshape,currshape,currshapecat);
}
//---------------------------------------------------------------------------
