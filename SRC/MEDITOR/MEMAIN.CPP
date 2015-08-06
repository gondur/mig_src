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


#include <dos.h>
#include <direct.h>
#define F_SOUNDS
//#include "eventwp.h"
//#include "test.h"
#include	"dosdefs.h"
#include "direct.h"
#include	"stdio.h"
#include "bstream.h"
//---------------------------------------------------------------------------
#include	"sysdefs.h"
#include	<INTABLE.h>
//#include "AcItem.h"
//#include	"PreComp.h"
//#include "eventwp.h"
//#include "Route.h"
//#include "piltlist.h"
#include "misscond.h"
//#include "missbase.h"
#include	"uniqueid.h"
#include "Waypoint.h"
#include "MissText.h"
#include "Static.h"
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include	<vcl\clipbrd.hpp>
#include	"loadsave.h"
#pragma hdrstop
#include "files.g"
#include "bfform.h"
#include "SGroups.h"
#include	"namelist.h"
#include "text.h"

#include	"shapenum.g"

//#include "meMain.h"
#include "About.h"
//#include "mainevt.h"

//#include "CampText.h"

//#include "CampEdit.h"
#include "AcItem.h"
#include "GrndGrp.h"

#include "strings.h"
#include "globals.h"
#include "player.h"
#include "afselect.h"
#include "SelTarg.h"
#include "missobj.h"
//#include "misscond.h"
//#include "SimRun.h"
//#include "piltlist.h"
//#include "Aces.h"
//#include "respool.h"
//#include "InitCamp.h"
//#include "confirm.h"
//#include "MissText.h"

#include	"fileman.h"
#include	"mymath.h"
//#include "Reserves.h"
 #include "bfenum.h"
#include "readenum.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"

//#include "Files.g"
//#include "persons2.h"
//#include "maps.h"

#include	"myangles.h"
#include	"makebf.h"
#include	"bfnumber.h"
#include	"persons2.h"

#include "meMain.h"

#include	"mytime.h"

#include	"readenum.h"
#include "currshp.h"
//#include "choosebf.h"
//#include "playerac.h"
#include "info.h"
#include "flyinit.h"
#include "sqinfo.h"
//#include "CampPara.h"
#include "itemcnt.h"
//inline	ItemBase&	operator &(UniqueID I)
//{return *Persons_2.ConvertPtrUID(I);}

FormPosnInfo	formposninfo [] =
{
	{POSN_OPPOSITE,0,0},         //AcItemFormId
	{POSN_OPPOSITE,0,0},         //WayPointFormId
	{POSN_OPPOSITE,0,0},         //EventWayPointFormId
	{POSN_CENTER,0,0},           //MainEventFormId
	{POSN_CENTER,0,0},  		 //ChooseBfFormId
};

   StaticBand   staticbands []=
   {    //Needs to be consistent with:
   		//Uniqueid.h:   UniqueIDBand
        //memain.h:     UidBandNum
        //
		{false, PilotedAcBAND,			WayPointBAND},
		{false, WayPointBAND,			MissileBAND},
		{false, MissileBAND,			LandscapeBAND},
		{false, LandscapeBAND,			RedRailBand},
		{false, RedRailBand,			RedRoadBAND},
		{false, RedRoadBAND,			RedAcBAND},
		{false, RedAcBAND,			BlueAcBAND},
		{false, BlueAcBAND,			AmberAirfieldBAND},
		{false, AmberAirfieldBAND,			RedFakeAcBAND},
		{false, RedFakeAcBAND,			RedAAASiteBAND},
		{false, RedAAASiteBAND,			BlueAAASiteBAND},
		{false, BlueAAASiteBAND,			RedAAALargeBAND},
		{false, RedAAALargeBAND,					AmberCivilianBAND},
		{false, 		AmberCivilianBAND,			AmberSupplyBAND},
		{false, AmberSupplyBAND,			RedRepairBAND},
		{false, RedRepairBAND,			AmberBridgeBAND},
		{false, AmberBridgeBAND,			AmberMYardBAND},
		{false, AmberMYardBAND,			AmberBattleNodeBAND},
        {false,	AmberBattleNodeBAND	,   RedTrainBAND},
		{false, RedTrainBAND,			RedTruckBAND},
		{false, RedTruckBAND,			RedTruckParkBAND},
		{false, RedTruckParkBAND,			RedTroopBAND},
		{false, RedTroopBAND,			BlueTroopBAND},
		{false, BlueTroopBAND,			RedArmourBAND},
		{false, RedArmourBAND,			BlueArmourBAND},
		{false, BlueArmourBAND,			RedArtilleryBAND},
		{false, RedArtilleryBAND,			BlueArtilleryBAND},
		{false, BlueArtilleryBAND,			RedCombatVehicleBAND},
		{false, RedCombatVehicleBAND,			BlueCombatVehicleBAND},
		{false, BlueCombatVehicleBAND,			EventBAND},
		{false, EventBAND,			GreenVetoedBAND},
		{false, GreenVetoedBAND,			GreenMobileBAND},
		{false, GreenMobileBAND,			 	GreenMiscBAND},
		{false,  	GreenMiscBAND,			RedHQBAND},
		{false, RedHQBAND,			BlueHQBAND},
		{false, BlueHQBAND,			RedBoatBAND},
		{false, RedBoatBAND,			BlueBoatBAND},
		{false, BlueBoatBAND,			GreenBoatBAND},
		{false, GreenBoatBAND,			RedStaticAcBAND},
		{false, RedStaticAcBAND,			BlueStaticACBAND},
		{false, BlueStaticACBAND,			RedMilitaryBAND},
		{false, RedMilitaryBAND,			BlueMilitaryBAND},
		{false, BlueMilitaryBAND,			RedAirfieldBAND},
		{false, RedAirfieldBAND,			BlueAirfieldBAND},
		{false, BlueAirfieldBAND,			RedPortBAND},
		{false, RedPortBAND,			BLuePortBAND},
		{false, BLuePortBAND,			RedCCCBAND},
		{false, RedCCCBAND,			BlueCCCBAND},
		{false, BlueCCCBAND,			RedGICBAND},
		{false, RedGICBAND,			BlueGICBAND},
		{false, BlueGICBAND,			RedSAMBAND},
		{false, RedSAMBAND,			BlueSAMBAND},
		{false, BlueSAMBAND,			IllegalBAND}

//DeadCode MS 14Oct98 		{false,	PilotedAcBAND,			WayPointBAND},
//DeadCode MS 14Oct98 		{false,	WayPointBAND,			RedGroundMobileBAND},
//DeadCode MS 14Oct98 		{false,	RedGroundMobileBAND,	BlueGroundMobileBAND},
//DeadCode MS 14Oct98 		{false,	BlueGroundMobileBAND,	MissileBAND},
//DeadCode MS 14Oct98 		{false,	MissileBAND,			RedAcBAND},
//DeadCode MS 14Oct98 		{false,	RedAcBAND,				BlueAcBAND},
//DeadCode MS 14Oct98 		{false,	BlueAcBAND,				RedCivilianBAND},
//DeadCode MS 14Oct98 		{false,	RedCivilianBAND,		BlueCivilianBAND},
//DeadCode MS 14Oct98 		{false,	BlueCivilianBAND,		GreenCivilianBAND},
//DeadCode MS 14Oct98 		{false,	GreenCivilianBAND,		RedVetoedBAND},
//DeadCode MS 14Oct98 		{false,	RedVetoedBAND,			BlueVetoedBAND},
//DeadCode MS 14Oct98 		{false,	BlueVetoedBAND,			LandscapeBAND},
//DeadCode MS 14Oct98 		{false,	LandscapeBAND,			RedMilitaryBAND},
//DeadCode MS 14Oct98 		{false,	RedMilitaryBAND,		BlueMilitaryBAND},
//DeadCode MS 14Oct98 		{false,	BlueMilitaryBAND,		RedAirfieldBAND},
//DeadCode MS 14Oct98 		{false,	RedAirfieldBAND,		BlueAirfieldBAND},
//DeadCode MS 14Oct98 		{false,	BlueAirfieldBAND,		RedPortBAND},
//DeadCode MS 14Oct98 		{false,	RedPortBAND,			BLuePortBAND},
//DeadCode MS 14Oct98 		{false,	BLuePortBAND,			RedCCCBAND},
//DeadCode MS 14Oct98 		{false,	RedCCCBAND,				BlueCCCBAND},
//DeadCode MS 14Oct98 		{false,	BlueCCCBAND,			RedGICBAND},
//DeadCode MS 14Oct98 		{false,	RedGICBAND,				BlueGICBAND},
//DeadCode MS 14Oct98 		{false,	BlueGICBAND,			RedAAASiteBAND},
//DeadCode MS 14Oct98 		{false,	RedAAASiteBAND,			BlueAAASiteBAND},
//DeadCode MS 14Oct98 		{false,	BlueAAASiteBAND,		RedSAMBAND},
//DeadCode MS 14Oct98 		{false,	RedSAMBAND,				BlueSAMBAND},
//DeadCode MS 14Oct98 		{false,	BlueSAMBAND,			IllegalBAND}

   };

TMissionEditor *MissionEditor;
TPaintBox* PaintGrid[16][16];
static const int 	TRUCK=999,STAFF=998,TRAIN3=997,TRAIN4=996,
                    TROOPS=995,WOOD=994,FARMYRD=993,VILLAGE=992,DEADTOWN=991,
                    FLAKBRIT=FTRUCK,FLAKGERM=989,BTHBRIT=CRANE,BTHGERM=987,
                    BBALL=986,GBALL=985,BTANK=984,GTANK=983,DHOUS1=982,
                    TRAIN1=981,TRAIN2=980,WINCH=979

                    ;
static const int	SOMMEREGION=0;
static const int	MAY1st1917=0;

bool __fastcall TMissionEditor::PaletteChanged(bool Foreground)
{
//	static int p=0;
  //	if (!p++)
	//	if (Application->MessageBox("This user interface requires more\nthan 256 colours to function efficiently.\nDo you wish to continue?",
	  //		"Warning: Paletised mode detected!",MB_YESNO+MB_ICONSTOP+MB_DEFBUTTON2)==IDNO)
		//	exit(1);
//	if (Foreground)
		return TForm::PaletteChanged(Foreground);
  //	else
	//	return false;
}
//void __fastcall TMissionEditor::WMQueryNewPalette(TMessage* Message)
//{
//  int i=5;
//  (*(UByte*)0xB00000)++;
//
//}

////---------------------------------------------------------------------------
//HPALETTE __fastcall TMissionEditor::GetPalette(void)
//{
////	return MapImageList->Palette;
//
////	Graphics::TBitmap* h=new Graphics::TBitmap;
////	MapImageList->GetBitmap(0,h);
//
//	return (SB_Single_Filter->Glyph->Palette);
////	delete h;
//}

//---------------------------------------------------------------------------
__fastcall TMissionEditor::TMissionEditor(TComponent* Owner)
	: TForm(Owner),
		BARCON(VS,ScrollBox),BARCON(HS,ScrollBox)
{
//	Application->OnDeactivate=FormActivate;
	Application->OnActivate=FormActivate;
	Application->OnDeactivate=FormDeactivate;
	Application->OnIdle=IdleTime;
	Font->Color = clWindow;
	Font->Color = clWindowText;
//	MissionNew=true;
//	MissionEdited=false;
	canmodifymainworld=FALSE;


	MapImageList = new TCustomImageList( 18,18);
	MapImageList->FileLoad(rtBitmap,FILEMAN.namenumberedfile(FIL_BUTTONSET),(TColor)0xBFBFBF);
//	strcpy(ActiveCampaign.name,"default");
	FILEMAN.fakefile(FIL_USERMISSION1,"");


//	MapImageList->FileLoad(rtBitmap,"icons\\settle.bmp",0xc0c0c0);


//	MapImageList->FileLoad(rtBitmap,"icons\\hi_wp.bmp",0xc0c0c0);
//	MapImageList->FileLoad(rtBitmap,"icons\\Event.bmp",0xc0c0c0);
//	MapImageList->FileLoad(rtBitmap,"icons\\aattack.bmp",0xc0c0c0);
//	MapImageList->FileLoad(rtBitmap,"icons\\gattack.bmp",0xc0c0c0);
//	MapImageList->FileLoad(rtBitmap,"icons\\hi_Event.bmp",0xc0c0c0);
//	MapImageList->FileLoad(rtBitmap,"icons\\hi_aatck.bmp",0xc0c0c0);
//	MapImageList->FileLoad(rtBitmap,"icons\\hi_gatck.bmp",0xc0c0c0);

	IEnumStuff.readenums();
//	for (int i=ComponentCount;i--;)
  //		if (Components[i]->ClassType()==SB_Single_Filter->ClassType())
	//	{
	  //		((TSpeedButton*)Components[i])->Glyph->IgnorePalette=false;
		//}
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FormCreate(TObject *)
{
	InitPaintGrid();

	char buff[50];
 //	char campname[50];

Application->OnHint = &OnHint;
currmission = 0;


//MapBitmap = new Graphics::TBitmap();
//MapBitmap->LoadFromFile("sommemap.bmp");
//PaintBox->Canvas->Draw(0, 0, MapBitmap);
zoom = 200;
oldzoom = 200;
currtransient = T_AIRCRAFT;
CurrNationality = ALLIES;
//LastGGTransItem = NULL;
//lastconvoystatic = FALSE;
//load in main world
WorldFile = FIL_NULL;

//camp ActiveCampaign.mission[currmission].PlayerNationality = ALLIES;

//NewWorld(FIL_CircusWorld,MissionEditor->ActiveCampaign.region);
//SetScrollBars();

ZoomLabel2->Caption=
 ZoomLabel->Caption =  "100%";

 Configure_Units = METRIC;
 findingstatic = NULL;
// PlayerItem = NULL;

	currobj=UID_Null;
	currwp=UID_Null;
	playerobj=UID_Null;


//MissionEditor->MissionTime = 0;
InitCampaign();
//Persons_2.InitGamePiece();


//MiG Alley
for (UWord i = 0; i < MAXLOADEDBFIELDS;i++)
{
	strcpy(MissionEditor->loadedbfs[i].fname,"");
	strcpy(	MissionEditor->loadedbfs[i].name,"");
	strcpy(	MissionEditor->loadedbfs[i].newstext,"");
	MissionEditor->loadedbfs[i].family = 0;
	MissionEditor->loadedbfs[i].fnum = 0;
	MissionEditor->loadedbfs[i].viewable = false;
	MissionEditor->loadedbfs[i].movable = false;
	MissionEditor->loadedbfs[i].deletable = false;
	MissionEditor->loadedbfs[i].newlynamed = false;
	MissionEditor->loadedbfs[i].changed = false;
}
for (UWord i = 0; i < MAXLOADEDSUPERGROUPS;i++)
{
	MissionEditor->loadedsupergroup[i].uid = AbsolutingSepID;
	MissionEditor->loadedsupergroup[i].viewable = false;
	MissionEditor->loadedsupergroup[i].movable = false;
	MissionEditor->loadedsupergroup[i].deletable = false;
	MissionEditor->loadedsupergroup[i].newlynamed = false;
	MissionEditor->loadedsupergroup[i].changed = false;
}

//MiG Alley: temp to set mainworld and first subworld
Persons2::InitTables();
InitMission();
bfieldbeingfilled = 0;
supergroupbeingfilled = 0;
loadedsupergroup[supergroupbeingfilled].uid = UID_Null;
loadedsupergroup[supergroupbeingfilled].viewable = true;
//MissionEditor->loadedbfs[0].fnum = -1;
//MissionEditor->loadedbfs[0].viewable = true;
//strcpy(MissionEditor->loadedbfs[0].name,"Main World");
MissionEditor->loadedbfs[0].fnum=FIL_1_mainmig;
	MissionEditor->loadedbfs[0].changed=false;
	MissionEditor->loadedbfs[0].viewable=
		MissionEditor->loadedbfs[0].movable=
			MissionEditor->loadedbfs[0].deletable=true;
	strcpy(MissionEditor->loadedbfs[0].fname,"mainmig");
	strcpy(MissionEditor->loadedbfs[0].name,"Main Mig World");
	BfieldForm->LoadBf(0,MissionEditor->loadedbfs[0].fnum,MissionEditor->loadedbfs[0].fname);


StatusBar->Panels->Items[3]->Text = MissionEditor->loadedbfs[bfieldbeingfilled].name;


//NewWorld(FIL_MainWorld,ActiveCampaign.mission[currmission].region);
//NewWorld(FIL_CircusAirfields,ActiveCampaign.mission[currmission].region);
//	FindWorldTemplateFiles(ActiveCampaign.mission[currmission].region);
//	MissionEditor->NewWorld();
//			(FileNum)ChooseBfForm->BFields[ChooseBfForm->AvailBf[ActiveCampaign.mission[currmission].era]].file,
  //			ActiveCampaign.mission[currmission].region);
		  
//MissionNumber = 1;
//MissionMode = true;
//SetMissionMode(true);

LoadString(HInstance,TEXT_MISSION,buff,sizeof(buff));
MissionEditor->SetCaption("",buff);


		staticbands [RedAcBANDNum].visible = true;
		staticbands [BlueAcBANDNum].visible = true;
		staticbands [WayPointBANDNum].visible = true;

ShowWPvel = true;
//CruiseSpeed = 545;
//TmpPlayerHomeBase = PlayerHomeBase;
//TmpEnemyHomeBase = EnemyHomeBase;
//TmpPlayerNationality = PlayerNationality;
//CheckHomeBase ();
//PlayerHomeBase = TmpPlayerHomeBase;
//EnemyHomeBase = TmpEnemyHomeBase;
ScaleX = 100;
ScaleY = 100;
Initialising = false;
SwapGroup = 0;
WithGroup = 0;

InMenu = false;
Editting = NOTEDITTING;
displayworldtemplateitems = true;

SetSpeedButtonTags();

zoomiconsize=ZoomWorldIconSize();



}
//---------------------------------------------------------------------------
__fastcall	TMissionEditor::~TMissionEditor()
{
	ExitPaintGrid();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::About3Click(TObject *)
{
	AboutBox->ShowModal();	
}
//---------------------------------------------------------------------------
//void __fastcall TMissionEditor::CampaignTextClick(TObject *)
//{
//	CampTextDlg->OpenForm();
//
//}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MissionTextClick(TObject *)
{
		MissionTextDlg->OpenForm();
}


//---------------------------------------------------------------------------
//void __fastcall TMissionEditor::TankBtnClick(TObject *)
//{
//	PaintBox->Repaint();
//}
//---------------------------------------------------------------------------
void	__fastcall TMissionEditor::DrawWpIcon(UniqueID	wpUID,SWord currwpnum)
{
	int x,z;                 info_waypoint* W=*Persons2::ConvertPtrUID(wpUID);
	x=W->World.X;
	z=W->World.Z;
	ScreenPosition(x,z);
//	if (W->target.Evaluate()!=ENABLE_COMPLEX_VAL)
//	{
//		x+=ICONW/2;
//		z+=ICONW/2;
//	}
	int act=W->wpact.Evaluate();
	if ((int)currwp==(int)wpUID)
		if (W->events)
			CurrCanvas->Draw(MapImageList,x-ICONW/2, z-ICONW/2, Eventbmp);
		else if (act==(IDS_TEXT_FLYWPBALLOONBUSTNO-IDS_TEXT_FLYWPACNOACTIONNO))
			CurrCanvas->Draw(MapImageList,x-ICONW/2, z-ICONW/2, aattackbmp);
		else if (	(act==(IDS_TEXT_FLYWPBOMBNO - IDS_TEXT_FLYWPACNOACTIONNO))
				  ||	(act==(IDS_TEXT_FLYWPDIVEBOMBSTRAFFENO - IDS_TEXT_FLYWPACNOACTIONNO))
				  ||	(act==(IDS_TEXT_FLYWPSTRAFFENO - IDS_TEXT_FLYWPACNOACTIONNO))
				)  
			CurrCanvas->Draw(MapImageList,x-ICONW/2, z-ICONW/2, gattackbmp);
		else
			CurrCanvas->Draw(MapImageList,x-ICONW/2, z-ICONW/2, hi_wpbmp);
	else
		if (W->events)
			CurrCanvas->Draw(MapImageList,x-ICONW/2, z-ICONW/2, hi_Eventbmp);
		else if (act==(IDS_TEXT_FLYWPBALLOONBUSTNO-IDS_TEXT_FLYWPACNOACTIONNO))
			CurrCanvas->Draw(MapImageList,x-ICONW/2, z-ICONW/2, hi_aatckbmp);
		else if (	(act==(IDS_TEXT_FLYWPBOMBNO - IDS_TEXT_FLYWPACNOACTIONNO))
				  ||	(act==(IDS_TEXT_FLYWPDIVEBOMBSTRAFFENO - IDS_TEXT_FLYWPACNOACTIONNO))
				  ||	(act==(IDS_TEXT_FLYWPSTRAFFENO - IDS_TEXT_FLYWPACNOACTIONNO))
				 )	

		
			CurrCanvas->Draw(MapImageList,x-ICONW/2, z-ICONW/2, hi_gatckbmp);
		else
			CurrCanvas->Draw(MapImageList,x-ICONW/2, z-ICONW/2, wpbmp);

	int X = x-ICONW/4;
	int Z = z-ICONW/2 + 1;
	CurrCanvas->CopyMode(cmSrcCopy);
	CurrCanvas->TextOut(X,Z,IntToStr(currwpnum));
}
//---------------------------------------------------------------------------
void	__fastcall TMissionEditor::DrawLoBorder(int X,int Y)
{
   CurrCanvas->Pen(psSolid,(Graphics::TColor)0xeeeeee,1);
   CurrCanvas->MoveTo(X,Y+ICONW);
   CurrCanvas->LineTo(X,Y);
   CurrCanvas->LineTo(X+ICONW,Y);
   CurrCanvas->Pen(psSolid,(Graphics::TColor)0x444444,1);
   CurrCanvas->LineTo(X+ICONW,Y+ICONW);
   CurrCanvas->LineTo(X,Y+ICONW);
   CurrCanvas->Pen(psSolid,(Graphics::TColor)0x444444,2);
}
void	__fastcall TMissionEditor::DrawHiBorder(int X,int Y)
{
   CurrCanvas->Pen(psSolid,(Graphics::TColor)0xdddddd,1);
   CurrCanvas->MoveTo(X,Y+ICONW);
   CurrCanvas->LineTo(X,Y);
   CurrCanvas->LineTo(X+ICONW,Y);
   CurrCanvas->Pen(psSolid,(Graphics::TColor)0x444444,1);
   CurrCanvas->LineTo(X+ICONW,Y+ICONW);
   CurrCanvas->LineTo(X,Y+ICONW);
   CurrCanvas->Pen(psSolid,(Graphics::TColor)0x444444,2);
}

void __fastcall TMissionEditor::DrawMobileIcon(UniqueID uid,SLong x, SLong z,ShapeNum	shape)
{
	info_grndgrp*	G=*Persons2::ConvertPtrUID(uid);
	UniqueID	uw=G->wpref;
	CurrCanvas->MoveTo(x,z);
	if (uw)
	if ((int)uid==(int)currobj || staticbands[WayPointBANDNum].visible)
	{
		int	x,z;
		while  ((int)uw!=(int)UID_Null)
		{
			info_waypoint*	W=*Persons2::ConvertPtrUID(uw);
			x=W->World.X;
			z=W->World.Z;
			ScreenPosition(x,z);
		if ((int)uid == (int)currobj)
			CurrCanvas->Pen((Graphics::TColor)0xffffff);
        else
			CurrCanvas->Pen((Graphics::TColor)0x444444);

			CurrCanvas->LineTo(x, z);
			uw = W->nextwp;
		}
		uw=G->wpref;
		int currwpnum=1;
		while  ((int)uw!=(int)UID_Null)
		{
			DrawWpIcon(uw,currwpnum);
			info_waypoint*	W=*Persons2::ConvertPtrUID(uw);
			uw = W->nextwp;
			currwpnum++;
		}

	}
//	DrawStaticIcon(uid,x - ICONW/2,z - ICONW/2,shape);
}
#define ZOOMMAXMAP 700
#define ZOOMMAXABS 40000

INTABLE(ITEM_SIZE);
//---------------------------------------------------------------------------

void __fastcall TMissionEditor::DrawStatics()
{
	info_itemS*		curritem;
	int			mapx,mapy;
	UniqueID       currUID;

	CurrCanvas->Font(clWhite);
	bool drawncurr=false;

	for(SWord i = 0; i < (int)MaxBANDNum;i++)
//	for(SWord i = 9; i < (int)MaxBANDNum;i++)
	{
//		if (staticbands [i].visible && i!=WayPointBANDNum)
		if (i!=WayPointBANDNum)
		{
			for(currUID = UniqueID(staticbands [i].startband);
				(((int)currUID) < ((int)staticbands [i].endband));
				currUID=(UniqueID)((int)currUID+1)
				)
			{
				curritem=*Persons2::ConvertPtrUID(currUID);
				if 	(curritem!=NULL)
				{
					if ((int)currUID==(int)currobj)
						drawncurr=true;
					mapx=curritem->World.X;
					mapy=curritem->World.Z;
					ScreenPosition(mapx,mapy);

					info_base* J=*Persons2::ConvertPtrUID(currUID);
					if (		(MissionEditor->loadedbfs[J->bfieldindex].viewable)
							&&  (SuperGroupViewable(currUID))
						)
//					if (	(J->bfieldindex || canmodifymainworld)
//						||	(displayworldtemplateitems)
//						)

					{
						if (	((int)staticbands [i].startband == (int)AmberCivilianBAND)
							&& (	(staticbands [i].visible && i!=WayPointBANDNum)
								||	(int)currUID==(int)currobj
								)
						   )
							DrawSettlement(currUID,mapx + ICONW/2, mapy - ICONW/2);
						if (curritem->Status.size>=MOBILESIZE)
						{
							DrawMobileIcon(currUID,mapx, mapy,(ShapeNum)curritem->shape.Evaluate(2));
							if (	(staticbands [i].visible && i!=WayPointBANDNum)
								||	(int)currUID==(int)currobj
								)
								DrawStaticIcon(currUID,mapx - ICONW/2,mapy - ICONW/2,(ShapeNum)curritem->shape.Evaluate(2));

						}
						else
							if (	(staticbands [i].visible && i!=WayPointBANDNum)
								||	(int)currUID==(int)currobj
								)
							DrawStaticIcon(currUID,mapx - ICONW/2, mapy - ICONW/2,(ShapeNum)curritem->shape.Evaluate(2));
					}
				}

			}
		}
	}
	//highlight targets 
	for(SWord i = 0; i < (int)MaxBANDNum;i++)
	{
		if (staticbands [i].visible && i!=WayPointBANDNum)
		{
			for(currUID = UniqueID(staticbands [i].startband);
				(((int)currUID) < ((int)staticbands [i].endband));
				currUID=(UniqueID)((int)currUID+1)
				)
			{
				curritem=*Persons2::ConvertPtrUID(currUID);
				if 	(curritem!=NULL)
				{
					if ((int)currUID==(int)currobj)
						drawncurr=true;
					mapx=curritem->World.X;
					mapy=curritem->World.Z;
					ScreenPosition(mapx,mapy);

					info_base* J=*Persons2::ConvertPtrUID(currUID);

					if (	(MissionEditor->loadedbfs[J->bfieldindex].viewable)
						&&  (SuperGroupViewable(currUID))
						)

//					if (	(J->bfieldindex || canmodifymainworld)
//						||	(displayworldtemplateitems)
//						)

					{
						if	(TodaysTarget(currUID))
							DrawTarget(currUID,mapx, mapy);
					}
				}

			}
		}
	}
	




	
	
	if (!drawncurr && currobj)
	{
		currUID=currobj;
		curritem=*Persons2::ConvertPtrUID(currUID);
		mapx=curritem->World.X;
		mapy=curritem->World.Z;
		ScreenPosition(mapx,mapy);
		if (curritem->Status.size>=MOBILESIZE)
		{
			DrawMobileIcon(currUID,mapx, mapy,(ShapeNum)curritem->shape.Evaluate(2));
			DrawStaticIcon(currUID,mapx - ICONW/2,mapy - ICONW/2,(ShapeNum)curritem->shape.Evaluate(2));
		}	
		else
			DrawStaticIcon(currUID,mapx - ICONW/2, mapy - ICONW/2,(ShapeNum)curritem->shape.Evaluate(2));
	}
}
//----------------------------------------------------------------------------------------
void __fastcall TMissionEditor::SetScrollBars()
{

//DEAD	 TRect ARect;
//DEAD
//DEAD	ScrollBox->HorzScrollBar->Range = (MapBitmapTL->Width+MapBitmapTR->Width)* zoom/ZOOMINITIAL;
//DEAD	ScrollBox->VertScrollBar->Range = (MapBitmapTL->Height+MapBitmapBL->Height) * zoom/ZOOMINITIAL;
//DEAD
//DEAD
//DEAD
//DEAD
//DEAD	int centrey = ScrollBox->VertScrollBar->Position+ScrollBox->Height/2;
//DEAD	centrey = centrey*zoom/oldzoom;
//DEAD	int centrex = ScrollBox->HorzScrollBar->Position+ScrollBox->Width/2;
//DEAD	centrex = centrex*zoom/oldzoom;
//DEAD
//DEAD	ScrollBox->HorzScrollBar->Position =  centrex - ScrollBox->Width/2;
//DEAD	ScrollBox->VertScrollBar->Position =  centrey - ScrollBox->Height/2;
//DEAD	ScaleX = ScaleX *zoom/oldzoom;
//DEAD	ScaleY = ScaleY *zoom/oldzoom;
//DEAD
//DEAD	oldzoom = zoom;
//DEAD

//	ARect = Rect(0, 0,ScrollBox->HorzScrollBar->Range,ScrollBox->VertScrollBar->Range );
//	ARect = CurrCanvas->ClipRect;
//   CurrCanvas->ClipRect = ARect;

}
void __fastcall TMissionEditor::CentreSetScrollBars(int X,int Y)
{

//DEAD	 TRect ARect;
//DEAD
//DEAD	ScrollBox->HorzScrollBar->Range = (MapBitmapTL->Width+MapBitmapTR->Width)* zoom/ZOOMINITIAL;
//DEAD	ScrollBox->VertScrollBar->Range = (MapBitmapTL->Height+MapBitmapBL->Height) * zoom/ZOOMINITIAL;
//DEAD
//DEAD
//DEAD
//DEAD
//DEAD	int centrey = Y *zoom/oldzoom;
//DEAD	int centrex = X *zoom/oldzoom;
//DEAD
//DEAD	ScrollBox->HorzScrollBar->Position =  centrex - ScrollBox->Width/2;
//DEAD	ScrollBox->VertScrollBar->Position =  centrey - ScrollBox->Height/2;
//DEAD
//DEAD	ScaleX = ScaleX *zoom/oldzoom;
//DEAD	ScaleY = ScaleY *zoom/oldzoom;
//DEAD
//DEAD	oldzoom = zoom;
//DEAD

//	ARect = Rect(0, 0,ScrollBox->HorzScrollBar->Range,ScrollBox->VertScrollBar->Range );
//	ARect = CurrCanvas->ClipRect;
//   CurrCanvas->ClipRect = ARect;

}


//---------------------------------------------------------------------------
void __fastcall TMissionEditor::DrawScale()
{
//   int x = ScrollBox->HorzScrollBar->Position + 100;
//   int y = ScrollBox->VertScrollBar->Position + 100;

   int x = ScaleX;
   int y = ScaleY;


   CurrCanvas->Pen(psSolid,(TColor) 0x00ffff,2);
	CurrCanvas->MoveTo(x,y);
	CurrCanvas->LineTo(x + 98 * zoom/ZOOMINITIAL , y );
	CurrCanvas->MoveTo(x,y + 6);
	CurrCanvas->LineTo(x , y - 6);

	CurrCanvas->MoveTo(x + 98 * zoom/ZOOMINITIAL,y + 6);
	CurrCanvas->LineTo(x + 98 * zoom/ZOOMINITIAL , y - 6);

	if (zoom >= 600)
	{
		CurrCanvas->MoveTo(x + 12 * zoom/ZOOMINITIAL,y + 6);
		CurrCanvas->LineTo(x + 12 * zoom/ZOOMINITIAL , y - 6);
		CurrCanvas->MoveTo(x + 24 * zoom/ZOOMINITIAL,y + 6);
		CurrCanvas->LineTo(x + 24 * zoom/ZOOMINITIAL , y - 6);
		CurrCanvas->MoveTo(x + 37 * zoom/ZOOMINITIAL,y + 6);
		CurrCanvas->LineTo(x + 37 * zoom/ZOOMINITIAL , y - 6);
		CurrCanvas->MoveTo(x + 49 * zoom/ZOOMINITIAL,y + 6);
		CurrCanvas->LineTo(x + 49 * zoom/ZOOMINITIAL , y - 6);
		CurrCanvas->MoveTo(x + 61 * zoom/ZOOMINITIAL,y + 6);
		CurrCanvas->LineTo(x + 61 * zoom/ZOOMINITIAL , y - 6);
		CurrCanvas->MoveTo(x + 73 * zoom/ZOOMINITIAL,y + 6);
		CurrCanvas->LineTo(x + 73 * zoom/ZOOMINITIAL , y - 6);
		CurrCanvas->MoveTo(x + 86 * zoom/ZOOMINITIAL,y + 6);
		CurrCanvas->LineTo(x + 86 * zoom/ZOOMINITIAL , y - 6);
	}

	CurrCanvas->Font((TColor)0x00ffff);
	//CurrCanvas->Font->Style = fsBold;
	char			buff[50];
	LoadString(HInstance,TEXT_SCALE,buff,sizeof(buff));
//	strcpy(buff,"8 Km/5 miles");
	CurrCanvas->TextOut(x+ 49 * zoom/ZOOMINITIAL -38,y -16,buff);
	CurrCanvas->Font((TColor)0x0);
}



//---------------------------------------------------------------------------
void __fastcall TMissionEditor::CampaignParametersClick(TObject *)
{
//	CampaignParametersDlg->OpenForm(ActiveCampaign.mission[currmission].PlayerNationality );
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::CampaignEditClick(TObject *)
{
//		CampaignEditDlg->OpenForm();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::DeleteWorld()
{
	for (int uid=0;uid<(int)IllegalBAND;uid++)
	{
		delete Persons2::ConvertPtrUID(UniqueID(uid));
		Persons2::delUID(uid);
	}
	currwp=
		currobj=UID_Null;
}
//---------------------------------------------------------------------------
 void __fastcall TMissionEditor::NewLoadedBf(AnsiString name)
{
 UWord	i= 0;
 while ( 	( i < MAXLOADEDBFIELDS)
		&&	(MissionEditor->loadedbfs[i].fnum != 0)
		)
		i++;
 bfieldbeingfilled = i;
 MissionEditor->loadedbfs[bfieldbeingfilled].fnum = -1;
 MissionEditor->loadedbfs[bfieldbeingfilled].viewable = true;
 strcpy(MissionEditor->loadedbfs[bfieldbeingfilled].name,name.c_str());
StatusBar->Panels->Items[3]->Text = MissionEditor->loadedbfs[bfieldbeingfilled].name;
}
//---------------------------------------------------------------------------
 void __fastcall TMissionEditor::SuperGroupStatusBar(UniqueID uid)
{
	char buff[100];
	if ((int)uid == (int)UID_Null)
		strcpy(buff,"None");
	else
		strcpy(buff,GetList(ENUM_UIDtitle).Translate(uid));
	StatusBar->Panels->Items[4]->Text = buff;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::NewSuperGroup(UniqueID uid)
{
UWord	i= 0;
while ( 	( i < MAXLOADEDSUPERGROUPS)
		&&	(MissionEditor->loadedsupergroup[i].uid != AbsolutingSepID)
		)
		i++;
 supergroupbeingfilled = i;
 MissionEditor->loadedsupergroup[supergroupbeingfilled].uid = uid;
 SuperGroupStatusBar(uid);
 MissionEditor->loadedsupergroup[supergroupbeingfilled].viewable = true;

}

//---------------------------------------------------------------------------
 void __fastcall TMissionEditor::InitMission()
 {



//camp	ActiveCampaign.mission[currmission].timeofday = HR08MIN20;
//	ActiveCampaign.mission[currmission].missiondate = MAY1st1917;
//	ActiveCampaign.mission[currmission].MainObjective = (UniqueID) 0;
//	ActiveCampaign.mission[currmission].SubObjective = (UniqueID) 0;
//	ActiveCampaign.mission[currmission].WP1 = (UniqueID) 0;
//	ActiveCampaign.mission[currmission].WP2 = (UniqueID) 0;
//	ActiveCampaign.mission[currmission].WP3 = (UniqueID) 0;
//	ActiveCampaign.mission[MissionEditor->currmission].title[0] = 0;
//	ActiveCampaign.mission[MissionEditor->currmission].name[0] = 0;
//	ActiveCampaign.mission[MissionEditor->currmission].newstext[0] = 0;
//	ActiveCampaign.mission[MissionEditor->currmission].missiontext[0] = 0;
//	ActiveCampaign.PlayerAcuid = UID_Null;
//	ActiveCampaign.mission[currmission].numofflightac = 1;
//	ActiveCampaign.mission[currmission].numofsquadronac = 1;
	SetMaxMobCnt();
 }

//---------------------------------------------------------------------------
 void __fastcall TMissionEditor::SetSpeedButtonTags()
 {
   SB_A_AAA->Tag = HUT;
   SB_CP_AAA->Tag = HUT;
   SB_A_Battery->Tag =HUT;
   SB_CP_Battery->Tag =HUT;
   SB_A_Balloon->Tag =HUT;
   SB_CP_Balloon->Tag =HUT;
   SB_A_Troops->Tag =HUT;
   SB_CP_Troops->Tag =HUT;
   SB_A_Tank->Tag = HUT;
   SB_CP_Tank->Tag = HUT;
   SB_A_Train->Tag =HUT;
   SB_CP_Train->Tag =HUT;
   SB_A_Truck->Tag =HUT;
   SB_CP_Truck->Tag =HUT;
   SB_Group->Tag = HUT;
   SB_Single->Tag = HUT;
 }


//---------------------------------------------------------------------------
 void __fastcall TMissionEditor::OnHint(TObject* Sender)
 {
	StatusBar->Panels->Items[2]->Text = Application->Hint;
 }

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FindWorldTemplateFiles(int Region)
{
//events	int family;
//	if  (ActiveCampaign.mission[currmission].region == SOMMEREGION)
//events	if  (Region == SOMMEREGION)
//events		family = FAM_MW_S;
//events	else
//events		family = FAM_MW_V;
//events	 ChooseBfForm->InitAvailBf();
//events	 SWord i = 0,j = 0;
//events	 while (	(ChooseBfForm->BFields[i].file != -1)
//events			&&	(i < MAXBFIELDS)
//events		  )
//events	 {
//events		if (ChooseBfForm->BFields[i].family == family)
//events		{
//events			ChooseBfForm->AvailBf[j] = i;
//events			j++;
//events		}
//events		i++;
//events	 }

}

//---------------------------------------------------------------------------
//int TMissionEditor::ConvertFileToEra(FileNum f)
//{
//	for (int j=0;j<30;j++)
//	{
//		if ((int)ChooseBfForm->BFields[ChooseBfForm->AvailBf[j]].file==(int)f)
//			return j;
//	}
//	return 0;
//}
//---------------------------------------------------------------------------
bool	__fastcall TMissionEditor::SuperGroupViewable(UniqueID currUID)
{
	info_base* i=*Persons2::ConvertPtrUID(currUID);
	//if the supergroup filter is down, we only display items that could become supergroups
	bool	viewable = false;
	char*	tmp =  GetList(ENUM_UIDtitle).Translate(currUID);

	if (SB_SuperGroupFilter->Down == true)
	{
		if (	((int)i->SGT == (int)UID_Null)
			&&	(tmp != NULL)
			)
			viewable = true;

	}else
	{
		viewable = true;
	}
	if ((viewable) && (loadedsupergroup[0].viewable == false))
	{//user has selected one/some supergroups to view
	 //see if the cuuruid is either the supergroup item or a member
		viewable = false;
		UWord j = 1;
	   while ( 	( j < MAXLOADEDSUPERGROUPS)
			)
	   {
			if (MissionEditor->loadedsupergroup[j].uid != AbsolutingSepID)
			{
				if (loadedsupergroup[j].viewable)
				{
					if (	((int)MissionEditor->loadedsupergroup[j].uid == (int)currUID)
						||	((int)i->SGT == (int)MissionEditor->loadedsupergroup[j].uid)
						)
							viewable = true;
				 }

			}
		   j++;
	   }
	}




	return (viewable);
}
//---------------------------------------------------------------------------
void	__fastcall TMissionEditor::ShowItemDialog(int X, int Y)
{
		info_base* i=*Persons2::ConvertPtrUID(currobj);
		WayPointForm->Close();

		if (	(MissionEditor->loadedbfs[i->bfieldindex].viewable)
			)

//		if (i->bfieldindex || canmodifymainworld)
		{
			switch(i->Status.size)
			{
			case	AIRSTRUCSIZE:
				AcItemForm->OpenAcItem(X,Y);
			break;
			case	MOBILESIZE:
				GroundGroupForm->OpenGroundGroupMobile(X,Y);
			break;
			case    ITEMSIZE:
			{
				UniqueIDBand	uidband;
				uidband = Persons2::getbandfromUID(currobj);
				if	(	((int)uidband == (int)BlueArmourBAND)
					||  ((int)uidband == (int)RedArmourBAND)
					||  ((int)uidband == (int)BlueSAMBAND)
					||  ((int)uidband == (int)RedSAMBAND)
					)
				{
					GroundGroupForm->OpenGroundGroupMobile(X,Y);
				}else
				{
				info_itemS* j=*i;
//events					if (j->events)
//						GroundGroupForm->OpenGroundGroupEvent(X,Y);
//events						EventForm->SetEventVars(&j->events);
//events					else
						GroundGroupForm->OpenGroundGroupStatic(X,Y);
				}
				break;
			}
			}
		}
//		else
  //			StaticForm->OpenForm();

}


UniqueID __fastcall TMissionEditor::MakeDefaultAirRoute(int X,int Z)
{
//	UniqueID u;
//	u = MakeDefaultRoute(X,Z);
//	return (u);
	info_waypoint*	W=new info_waypoint;
	W->bfieldindex=bfieldbeingfilled;
	W->SGT = loadedsupergroup[supergroupbeingfilled].uid;
//DeadCode RDH 11Feb98 	W->uniqueID.sector=FALSE;
	MissionEditor->currwp=UID_Null;

//	if ((int)ActiveCampaign.mission[currmission].PlayerNationality == (int)CurrNationality)
//	else
//		W->target = ActiveCampaign.mission[currmission].EnemyHomeBase;

	W->position.MakeAbsWorldPos();


	if (W->position[0].Evaluate()!=ENABLE_COMPLEX_VAL)
		W->position[0]=ENABLE_COMPLEX_VAL;
	W->position[0][0]=0;
	W->position[0][1]=100000;		//JT sun
	W->position[0][2]=0;
	W->position.EvalW(W->World);
	if (currhomebase)
	{
		W->target = currhomebase;//ActiveCampaign.mission[currmission].PlayerHomeBase;
		Coords3D& c=Persons2::ConvertPtrUID(W->target)->World;
		W->World.X+=c.X+zoomiconsize;
		W->World.Z+=c.Z-zoomiconsize;
	}
	W->wpact = IDS_TEXT_FLYWPALANDINGNO - IDS_TEXT_FLYWPACNOACTIONNO;
	W->range = 200000;
	UniqueID u;
	W->uniqueID.count=
		u=Persons2::assignuid(WayPointBAND);
	IncWayPointandCheck();
	Persons2::tabulateUID(W);
	return (u);
}



UniqueID __fastcall TMissionEditor::MakeDefaultRoute(int X,int Z)
{
	X+=50;Z+=50;
	info_waypoint*	I=new info_waypoint;
	I->bfieldindex=bfieldbeingfilled;
	I->SGT = loadedsupergroup[supergroupbeingfilled].uid;
//DeadCode RDH 11Feb98 	I->uniqueID.sector=FALSE;
	MissionEditor->currwp=UID_Null;

	I->position.MakeAbsWorldPos();

//DeadCode RDH 12Feb98 					X = X * ZOOMINITIAL/zoom;
//DeadCode RDH 12Feb98 					X = X+ maptopx/PIXEL640;
//DeadCode RDH 12Feb98 					X = X*PIXEL640;
//DeadCode RDH 12Feb98 					X = X*(int)CONVERTTOSCRN_DIV;
//DeadCode RDH 12Feb98 					X = X /scrnconvert;
//DeadCode RDH 12Feb98 					X = X + MapOriginX;
//DeadCode RDH 12Feb98 					X = X * 100;
//DeadCode RDH 12Feb98 					Z = Z * ZOOMINITIAL/zoom;
//DeadCode RDH 12Feb98 					Z = maptopy/PIXEL640 - Z;
//DeadCode RDH 12Feb98 					Z = Z*PIXEL640;
//DeadCode RDH 12Feb98 					Z = Z*(int)CONVERTTOSCRN_DIV;
//DeadCode RDH 12Feb98 					Z = Z/scrnconvert;
//DeadCode RDH 12Feb98 					Z = Z + MapOriginY;
//DeadCode RDH 12Feb98 					Z = Z * 100;

					X = MulScaleFactor(X);//*PIXEL640;
///					X = X * ZOOMINITIAL/zoom;
   ///					X = X*(int)CONVERTTOSCRN_DIV;
      ///					X = X /scrnconvert;
	 ///				X = X * 100;
					X = X + MapOriginX;

					Z = MulScaleFactor(Z);//*PIXEL640;
///					Z = Z * ZOOMINITIAL/zoom;
   ///					Z = Z*(int)CONVERTTOSCRN_DIV;
	  ///					Z = Z/scrnconvert;
	 ///				Z = Z * 100;
					Z = MapOriginY - Z;


	I->position[0][0]=X;
	I->position[0][2]=Z;

	I->position.EvalW(I->World);

	UniqueID u;
	I->uniqueID.count=
		u=Persons2::assignuid(WayPointBAND);
	I->wpact = IDS_TEXT_FLYWPDMBTRKSTOPNO - IDS_TEXT_FLYWPACNOACTIONNO;
	IncWayPointandCheck();

	Persons2::tabulateUID(I);
	return (u);
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SetTransItem(UniqueID	transitem)
{
		currobj = transitem;
}
//---------------------------------------------------------------------------
UniqueID	__fastcall TMissionEditor::TopInitStatic(int X,int Y,int Z,UniqueIDBand au,UniqueIDBand cu,ShapeNum as,ShapeNum cs)
{
	if ((int)CurrNationality == (int) ALLIES)
	{
		cu = au;
		cs = as;
	}
//   MobileSpdButtonState();
	UniqueID uid = Persons2::findavailuid(cu);
	if ((int)uid == (int)UID_Null)
	{
		MessageBeep(MB_ICONEXCLAMATION);	
//	   PlaySound("ID_YELL2",HInstance,SND_ASYNC|SND_RESOURCE);
//		MobileSpdButtonState();
		DisableWPUsageifnecessary();	//rdh 
	   return UID_Null;
	}
	else
	{
		currobj=InitStatic(X,Y,Z,cu,cs,uid);
//		MobileSpdButtonState();
		DisableWPUsageifnecessary();	//rdh
  		return	currobj;
	}
}

//---------------------------------------------------------------------------
UniqueID __fastcall TMissionEditor::InitStatic(int X, int Y, int Z,UniqueIDBand u,ShapeNum s,UniqueID uid)
{
		info_itemS*	I=new info_itemS;
		I->bfieldindex=bfieldbeingfilled;
		I->SGT = loadedsupergroup[supergroupbeingfilled].uid;

//DeadCode RDH 11Feb98 	I->uniqueID.sector=FALSE;
		I->position.MakeAbsWorldPos();

		WorldPosition(X,Z);
		I->position[0][0]=X;
		if (Y !=0)
			I->position[0][1]=Y;
		I->position[0][2]=Z;
		I->shape=s;//GBALL;
		I->band=u;// RedGICBAND;

		IncMobileCounters(u,1);
//		MobileSpdButtonState();


		I->position.EvalW(I->World);
//		I->uniqueID.count=Persons2::assignuid(u);//(RedGICBAND);
		I->uniqueID.count= uid;
		I->bfieldindex=bfieldbeingfilled;
		I->SGT = loadedsupergroup[supergroupbeingfilled].uid;

//DeadCode RDH 11Feb98 		I->uniqueID.sector=FALSE;
		Persons2::tabulateUID(I);
//		return	I->uniqueID.count;
		return	uid;
}
//---------------------------------------------------------------------------
UniqueID __fastcall TMissionEditor::TopInitMobile(int X, int Z,UniqueIDBand au,UniqueIDBand cu,ShapeNum as,ShapeNum cs)
{

	if ((int)CurrNationality == (int) ALLIES)
	{
		cu = au;
		cs = as;
	}
	UniqueID uid = Persons2::findavailuid(cu);
	if ((int)uid == (int)UID_Null)
	{
		MessageBeep(MB_ICONEXCLAMATION);	
//	   PlaySound("ID_YELL2",HInstance,SND_ASYNC|SND_RESOURCE);
		DisableWPUsageifnecessary();	//rdh
		//MobileSpdButtonState();
	   return UID_Null;
	}
	else
	{
		UniqueID r=MakeDefaultRoute(X,Z);
		currobj=InitMobile(X,Z,cu,cs,r,uid);
		DisableWPUsageifnecessary();	//rdh 21/10 MobileSpdButtonState();
		return currobj;
	}
}

//---------------------------------------------------------------------------
UniqueID __fastcall TMissionEditor::InitMobile(int X, int Z,UniqueIDBand u,ShapeNum s,UniqueID route,UniqueID uid)
{
	info_grndgrp*	I=new info_grndgrp;
	I->bfieldindex=bfieldbeingfilled;
	I->SGT = loadedsupergroup[supergroupbeingfilled].uid;

//DeadCode RDH 11Feb98 	I->uniqueID.sector=FALSE;
	I->position.MakeAbsWorldPos();

	WorldPosition(X,Z);


	I->position[0][0]=X;
	I->position[0][2]=Z;
	if ((int)s==(int)TRAIN3 || (int)s==(int)TRAIN4)
	{
		ListFormExpr* L=new ListFormExpr;
		L->maxentries=3;
		L->entries[0]=TRAIN1;
		L->entries[1]=TRAIN2;
		L->entries[2]=s;
		I->shape=L;
	}
	else
		I->shape=s;//GBALL;
	I->band=u;// RedGICBAND;

	//everything is considered to be type truck except troops and tanks
	if (	((int)I->band == (int)BlueSAMBAND)
		||	((int)I->band == (int)RedSAMBAND)
		||	((int)I->shape == (int)TROOPS)
		||	((int)I->shape == (int)TROOP1)
	   )	
	{	   
	   I->form = IDS_TEXT_FLATV-IDS_TEXT_STACKED;
	   I->type = SQ_ATank;
	}
	else
	{
	   I->form = IDS_TEXT_SINGLEFILE_FORM-IDS_TEXT_STACKED;
	   I->type = SQ_ATruck;
	}
	I->inform = IncMobileCounters(u,3);
//	MobileSpdButtonState();

	I->position.EvalW(I->World);
//	I->uniqueID.count=Persons2::assignuid(u);//(RedGICBAND);
	I->uniqueID.count=uid;
	I->bfieldindex=bfieldbeingfilled;
	I->SGT = loadedsupergroup[supergroupbeingfilled].uid;

//DeadCode RDH 11Feb98 	I->uniqueID.sector=FALSE;
	I->wpref=route;
	if ((int)CurrNationality == (int) ALLIES)
		I->nat=NAT_BLUE;
	else
		I->nat=NAT_RED;
	info_waypoint* W=*Persons2::ConvertPtrUID(route);
	W->owner=I->uniqueID.count;
	Persons2::tabulateUID(I);
//	return	I->uniqueID.count;
	return	uid;
}

//---------------------------------------------------------------------------
UniqueID __fastcall TMissionEditor::TopInitAc(int X, int Y, int Z,UniqueIDBand au,UniqueIDBand cu,ShapeNum as,ShapeNum cs)
{
	if ((int)CurrNationality == (int) ALLIES)
	{
		cu = au;
		cs = as;
	}
	UniqueID uid = Persons2::findavailuid(cu);
	if ((int)uid == (int)UID_Null)
	{
		MessageBeep(MB_ICONEXCLAMATION);	
//	   PlaySound("ID_YELL2",HInstance,SND_ASYNC|SND_RESOURCE);
	   //AcSpdButtonState();
		DisableWPUsageifnecessary();	//rdh 
		return UID_Null;
	}
	else
	{
		UniqueID r=MakeDefaultAirRoute(X,Z);
		currobj=InitAircraft(X,Y,Z,cu,cs,r,uid);
		DisableWPUsageifnecessary();	//rdh 21/10 	   AcSpdButtonState();
		return currobj;
	}
  
}
void __fastcall TMissionEditor::AcSpdButtonState()
{
	if (RedAcCnt >= RedAcMax)
   {
	if (SB_CP_Aircraft->Down)
	  {
			ResetSpeedButtons();
		 SB_Arrow->Down = true;
			currtransient = T_NONE;
			currtransientshape = NULL;
	  }
		SB_CP_Aircraft->Enabled = false;
		SB_CP_Aircraft_T->Enabled = false;
   }   
  else
  {
	SB_CP_Aircraft->Enabled = true;
	SB_CP_Aircraft_T->Enabled = true;
  }
  if (BlueAcCnt >= BlueAcMax)
  {
	   if (SB_A_Aircraft->Down)
	  {
			ResetSpeedButtons();
		 SB_Arrow->Down = true;
			currtransient = T_NONE;
			currtransientshape = NULL;
	  }
		SB_A_Aircraft->Enabled = false;
		SB_A_Aircraft_T->Enabled = false;
  }
  else
  {
	SB_A_Aircraft->Enabled = true;
	SB_A_Aircraft_T->Enabled = true;
  }
}                                 


void __fastcall TMissionEditor::MobileSpdButtonState()
{
	if (RedGroundMobilesCnt >= RedGroundMobilesMax)
   {
	if (	(SB_CP_Train->Down)
			||	(SB_CP_Truck->Down)
		 || (SB_CP_Troops->Down)
		 )

	  {
			ResetSpeedButtons();
		 SB_Arrow->Down = true;
			currtransient = T_NONE;
			currtransientshape = NULL;
	  }
	  SB_CP_Train->Enabled = false;
	  SB_CP_Truck->Enabled = false;
	  SB_CP_Troops->Enabled = false;
	  SB_CP_Train_T->Enabled = false;
	  SB_CP_Truck_T->Enabled = false;
	  SB_CP_Troops_T->Enabled = false;
   }
  else
  {
	  SB_CP_Train->Enabled = true;
	  SB_CP_Truck->Enabled = true;
	  SB_CP_Troops->Enabled = true;
	  SB_CP_Train_T->Enabled = true;
	  SB_CP_Truck_T->Enabled = true;
	  SB_CP_Troops_T->Enabled = true;
  }                 
	if (BlueGroundMobilesCnt >= BlueGroundMobilesMax)
   {
	if (	(SB_A_Train->Down)
			||	(SB_A_Truck->Down)
		 || (SB_A_Troops->Down)	
		 )
	  
	  {
			ResetSpeedButtons();
		 SB_Arrow->Down = true;
			currtransient = T_NONE;
			currtransientshape = NULL;
	  }
	  SB_A_Train->Enabled = false;
	  SB_A_Truck->Enabled = false;
	  SB_A_Troops->Enabled = false;
	  SB_A_Train_T->Enabled = false;
	  SB_A_Truck_T->Enabled = false;
	  SB_A_Troops_T->Enabled = false;
   }
  else
  {
	  SB_A_Train->Enabled = true;
	  SB_A_Truck->Enabled = true;
	  SB_A_Troops->Enabled = true;
	  SB_A_Train_T->Enabled = true;
	  SB_A_Truck_T->Enabled = true;
	  SB_A_Troops_T->Enabled = true;
  }                

	if (RedTanksCnt >= RedTanksMax)
   {
	if (	(SB_CP_Tank->Down)
		 )
	  
	  {
			ResetSpeedButtons();
		 SB_Arrow->Down = true;
			currtransient = T_NONE;
			currtransientshape = NULL;
	  }
	  SB_CP_Tank->Enabled = false;
	  SB_CP_Tank_T->Enabled = false;
   }   
  else
  {
	  SB_CP_Tank->Enabled = true;
	  SB_CP_Tank_T->Enabled = true;
  }	  
	if (BlueTanksCnt >= BlueTanksMax)
   {
	if (	(SB_A_Tank->Down)
		 )
	  
	  {
			ResetSpeedButtons();
		 SB_Arrow->Down = true;
			currtransient = T_NONE;
			currtransientshape = NULL;
	  }
	  SB_A_Tank->Enabled = false;
	  SB_A_Tank_T->Enabled = false;
   }   
  else
  {
	  SB_A_Tank->Enabled = true;
	  SB_A_Tank_T->Enabled = true;
   }	
//also blank out for statics
//moved to DisableWp....
}                                 



UniqueID __fastcall TMissionEditor::InitAircraft(int X, int Y,int Z,UniqueIDBand u,ShapeNum s,UniqueID route, UniqueID uid)
{
	info_airgrp*	I=new info_airgrp;
	I->bfieldindex=bfieldbeingfilled;
	I->SGT = loadedsupergroup[supergroupbeingfilled].uid;

//DeadCode RDH 11Feb98 	I->uniqueID.sector=FALSE;
	I->nat = CurrNationality; 

	I->position.MakeAbsWorldPos();

//camp	if ((int)ActiveCampaign.mission[currmission].PlayerNationality == (int)CurrNationality)
		I->homebase = currhomebase;//ActiveCampaign.mission[currmission].PlayerHomeBase;
//	else
//		I->homebase = ActiveCampaign.mission[currmission].EnemyHomeBase;


	WorldPosition(X,Z);

	I->position[0][0]=X;
	I->position[0][1]=Y;
	I->position[0][2]=Z;
// don't put in shape, rely on type	
//	I->shape=s;
	I->band=u;


	I->skill = SKILL_VETERAN;
	I->morale = MORALE_GOOD;
	I->character = CHAR_MRAVERAGE;

	I->inform=3;
	I->inwing=3;
	if ((int)I->nat == (int)NAT_RED)
   {
	   I->type = PT_MIG15;
	if (((int)I->inform+RedAcCnt) > RedAcMax)
		I->inform = RedAcMax - RedAcCnt;
	   RedAcCnt += (int)I->inform;

   }else
   {
	   I->type = PT_F86E;
	if (((int)I->inform+BlueAcCnt) > BlueAcMax)
      	I->inform = BlueAcMax - BlueAcCnt;
   	BlueAcCnt += (int)I->inform;
   }
//   AcSpdButtonState();

	I->position.EvalW(I->World);
//	I->uniqueID.count=Persons2::assignuid(u);
	I->uniqueID.count= uid;
	I->bfieldindex=bfieldbeingfilled;
	I->SGT = loadedsupergroup[supergroupbeingfilled].uid;

//DeadCode RDH 11Feb98 	I->uniqueID.sector=FALSE;
	I->wpref=route;
	info_waypoint* W=*Persons2::ConvertPtrUID(route);
//	W->pos[0][1]=Y;
  //	W->World.Y=Y;

	W->owner=I->uniqueID.count;
	Persons2::tabulateUID(I);
//	return	I->uniqueID.count;
	return	uid;
}


//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MakeTransient(int X, int Y)
{
	MissionEditor->loadedbfs[bfieldbeingfilled].changed=true;

//	MissionEdited=true;
	WayPointForm->Close();

	ShapeNum cts=(ShapeNum)currtransientshape;

	if ((int)currtransient != (int)T_NONE)
	{

		switch (currtransient)
		{
			case	T_AIRCRAFT:
			{
////				UniqueID r=MakeDefaultAirRoute(X,Y);
				if (TopInitAc(X, -100000, Y,BlueAcBAND,RedAcBAND,F86,MIG15))
//camp				if (	((int)ActiveCampaign.PlayerAcuid == (int)UID_Null)
  //					&&   (CurrNationality == ActiveCampaign.mission[currmission].PlayerNationality)
	//				)
	  //				{
		//				MakePlayerAc(true);
		  //				CampaignStarted = true;
			//			MissionStarted = true;
			  //		}
				break;
			}
			case	T_BALLOON:
			{
				UniqueID u=TopInitStatic(X,-100000,Y,BlueGICBAND,RedGICBAND,cts,cts);
				if (u)
				{   //place winch using relative coords system directly below balloon
					UniqueID v=TopInitStatic(X,0,Y,AmberCivilianBAND,AmberCivilianBAND,WINCH,WINCH);
					info_itemS* I=*Persons2::ConvertPtrUID(v);
					WorldExpr* W=I->position.MakeRelWorldPos(u);
					W->delta[1]=-1;
					W->deltaisabs=TRUE;
					W->EvalW(I->World);
					currobj=u;
				}
				break;
			}
			case	T_BATTERY:
			{
				TopInitStatic(X,0,Y,BlueMilitaryBAND,RedMilitaryBAND,cts,cts);
				break;
			}
			case	T_AAA:
			{
				TopInitStatic(X,0,Y,BlueAAASiteBAND,RedAAASiteBAND,cts,cts);
				break;
			}
			case	T_EVENT:
			{

				if (TopInitStatic(X,0,Y,LandscapeBAND,LandscapeBAND,EMPTY,EMPTY))
				{
					info_itemS* I=*Persons2::ConvertPtrUID(currobj);
					I->events=new info_event;
///	W->uniqueID->sector=FALSE;
				}
				break;
			}
			case	T_TRUCK:
			{
				if (Mobile->Checked)
					TopInitMobile(X,Y,BlueArmourBAND,RedArmourBAND,cts,cts);
				else
					TopInitStatic(X,0,Y,BlueArmourBAND,RedArmourBAND,cts,cts);
				break;
			}
			case	T_TRAIN:
			{
//rdh				if (Mobile->Checked)
					TopInitMobile(X,Y,BlueArmourBAND,RedArmourBAND,cts,cts);
//rdh				}else
 //rdh				TopInitStatic(X,0,Y,BlueArmourBAND,RedArmourBAND,cts,cts);
				break;

			}
			case	T_TANK:
			{
				if (Mobile->Checked)
				{
					TopInitMobile(X,Y,BlueSAMBAND,RedSAMBAND,cts,cts);
				}else
				{
					TopInitStatic(X,0,Y,BlueSAMBAND,RedSAMBAND,cts,cts);
				}
				break;

			}
			case	T_TROOP:
			{
				if (Mobile->Checked)
				{
					TopInitMobile(X,Y,BlueArmourBAND,RedArmourBAND,cts,cts);
				}else
				{
					TopInitStatic(X,0,Y,BlueArmourBAND,RedArmourBAND,cts,cts);
				}
				break;

			}

			case	T_SINGLEPOPULATE:
			{
						TopInitStatic(X,0,Y,LandscapeBAND,LandscapeBAND,cts,cts);
						break;

			}
			case	T_GROUPPOPULATE:
			{
						TopInitStatic(X,0,Y,MissileBAND,MissileBAND,cts,cts);
						break;

			}
			default:
			{
						TopInitStatic(X,0,Y,LandscapeBAND,LandscapeBAND,cts,cts);
			}
		 }

	}
}

//---------------------------------------------------------------------------
int __fastcall TMissionEditor::GetBandorShapeText(UniqueID currUID)
{
//only want the band don't add the shape, rdh

	UniqueIDBand	uidband;

	uidband = Persons2::getbandfromUID(currUID);
	for(SWord i = 0; i < (int)MaxBANDNum;i++)
	{
		if ((int)staticbands[i].startband == (int)uidband)
		{
			ItemBasePtr k=Persons2::ConvertPtrUID(currUID);
			info_itemS* j=*k;
			if (	(j) && (j->events))
				return (TEXT_EVENT);
			else
				return (T_PilotedAcBANDNum+i);
		}

	}
	return (0);
 }


//---------------------------------------------------------------------------
void	TMissionEditor::MouseUpFindStatic(int X,int Y)
{
	int fs=findingstatic;
	findingstatic = NULL;
	SelectAirfield->Close();
	SelectTarget->Close();
	PaintRefresh();
	UniqueID currUID;
			if (OverStatic(X,Y,currUID))
			{

				switch (fs)
				{
//events					case	SETHOMEBASEEVENTVAR:
//events					{
//events						currUID=FindNeighbour(currUID,RedVetoedBANDNum);
//events						if (currUID)
//events							*(ULong*)UIDLocation=currUID;
//events
//events						EventForm->SetEventVars();
//events
//events						break;
//events					}
//events					case	SETTARGETEVENTVAR:
//events					{
//events						*(ULong*)UIDLocation=currUID;
//events						EventForm->SetEventVars();
//events
//events						break;
//events					}
//					case	SETENEMYHOMEBASE:
  //					case	SETHOMEBASE:
	//				{
	  //					currUID=FindNeighbour(currUID,RedVetoedBANDNum);
		//				if (currUID)
		  //				{
			//				*UIDLocation=currUID;
			  //				MissionBaseForm->ProcessForm();
				//		}
				  //		break;
					//}
					case	SETSUPERGROUP:
					{
						if (currUID)
						{
							NewSuperGroup(currUID);
							info_itemS*	I= *Persons2::ConvertPtrUID(MissionEditor->currobj);
							I->SGT = loadedsupergroup[supergroupbeingfilled].uid;
							ShowItemDialog(0,0);
						}
						break;
					}

//camp tmp					case	SETMAINOBJECTIVE:
//					{
//						MissionEditor->ActiveCampaign.mission[currmission].MainObjective =  currUID;
//						if (MissionBaseForm->wasfinding)
//							MissionBaseForm->ProcessForm();
//						else
//							MissionObjectivesForm->ProcessForm();
//						break;
//					}
//					case	SETSUBOBJECTIVE:
//					{
//						MissionEditor->ActiveCampaign.mission[currmission].SubObjective =  currUID;
//						if (MissionBaseForm->wasfinding)
//							MissionBaseForm->ProcessForm();
//						else
//							MissionObjectivesForm->ProcessForm();
//						break;
//					}
//					case	SETWP1:
//					{
//						MissionEditor->ActiveCampaign.mission[currmission].WP1 =  currUID;
//						if (MissionBaseForm->wasfinding)
//							MissionBaseForm->ProcessForm();
//						else
//							MissionObjectivesForm->ProcessForm();
//						break;
//					}
//					case	SETWP2:
//					{
//						MissionEditor->ActiveCampaign.mission[currmission].WP2 =  currUID;
//						if (MissionBaseForm->wasfinding)
//							MissionBaseForm->ProcessForm();
//						else
//							MissionObjectivesForm->ProcessForm();
//						break;
//					}
//					case	SETWP3:
//					{
//						MissionEditor->ActiveCampaign.mission[currmission].WP3 =  currUID;
//						if (MissionBaseForm->wasfinding)
//							MissionBaseForm->ProcessForm();
//						else
//							MissionObjectivesForm->ProcessForm();
//						break;
//					}



					case	SETSQUADHOMEBASE:
					{
////						currUID=FindNeighbour(currUID,RedVetoedBANDNum);
						info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);
						ac->homebase = currUID;
						SquadronDataForm->SetLandingWP();
						AcItemForm->ProcessForm(0,0);
					}
					break;
					case	SETAIRFIELD:
					{
////						currUID=FindNeighbour(currUID,RedVetoedBANDNum);
						info_waypoint* W=*Persons2::ConvertPtrUID(currwp);
						if (currUID)
						{
							*UIDLocation=currUID;
							info_grndgrp* G=*Persons2::ConvertPtrUID(W->owner);
                            currhomebase=currUID;
//							if ((int)W->owner == (int)ActiveCampaign.PlayerAcuid)
  //							{
	//							ActiveCampaign.mission[currmission].PlayerHomeBase = currUID;
	  //						}
		//					else
		  //					if ((int)ActiveCampaign.mission[currmission].PlayerNationality!= (int)G->nat)
			//					ActiveCampaign.mission[currmission].EnemyHomeBase =  currUID;
						}
						else
							currUID=*UIDLocation;
						W->target = currUID;
						if (W->position[0].Evaluate()!=ENABLE_COMPLEX_VAL)
								W->position[0]=ENABLE_COMPLEX_VAL;
						W->position[0][0]=0;
						W->position[0][1]=-W->position[0][1];//
						W->position[0][2]=0;
						W->position.EvalW(W->World);
						Coords3D& c=Persons2::ConvertPtrUID(currUID)->World;
						W->World.X+=c.X+zoomiconsize;
						W->World.Z+=c.Z-zoomiconsize;
						WayPointForm->ShowWpDialog( 0,0);
					}
					break;

					case	SETTAKEOFFPOINT:
					{
//nah can't do this.. too easy!						*UIDLocation=currUID;
						ItemBasePtr I=Persons2::ConvertPtrUID(currobj);
						if ((int)I->Status.size==(int)AIRSTRUCSIZE)
						{
							info_airgrp* A=*I;
							currUID=UID_Null;
							if (	A->nat.Evaluate()==(int)NAT_BLUE
								&&	staticbands[BlueAirfieldBANDNum].visible
								)
								currUID=FindNeighbour(currobj,BlueAirfieldBANDNum,zoomiconsize*3);
							else
							if (	A->nat.Evaluate()==(int)NAT_RED
								&&	staticbands[RedAirfieldBANDNum].visible
								)
								currUID=FindNeighbour(currobj,RedAirfieldBANDNum,zoomiconsize*3);
							if  (currUID)
							{
 ////								currUID=FindNeighbour(currUID,RedVetoedBANDNum);
								A->position.MakeRelWorldPos(currUID);
								A->position.EvalW(A->World);
								A->World.X+=zoomiconsize;
								A->World.Z+=zoomiconsize;
								A->position[1][1]=-1;
								//set the local variable that processform uses
								AcItemForm->WorldY = A->World.Y;
							}
						}

						AcItemForm->ProcessForm(0,0);
						break;
					}
				}
			}else	//NOT OVER STATIC
			{
				switch (fs)
				{
//events					case	SETTARGETEVENTVAR:
//events					case	SETHOMEBASEEVENTVAR:
//events					{
//events						EventForm->SetEventVars();
//events						break;
//events					}

//					case	SETENEMYHOMEBASE:
  //					case	SETHOMEBASE:
	//				{
	  //					MissionBaseForm->ProcessForm();
		//				break;
		  //			}
					case	SETSUPERGROUP:
					{
					 	ShowItemDialog(0,0);
						break;
					}


					case	SETMAINOBJECTIVE:
  					case	SETSUBOBJECTIVE:
					case	SETWP1:
	  				case	SETWP2:
					case	SETWP3:
		  			{
//						if (MissionBaseForm->wasfinding)
  //			  				MissionBaseForm->ProcessForm();
	//					else
				  			MissionObjectivesForm->ProcessForm();
						break;
					}
					case	SETWAYPOINT:
					{
						break;
					}
					case	SETTAKEOFFPOINT:
					{
					ItemBasePtr I=Persons2::ConvertPtrUID(currobj);
					if ((int)I->Status.size==(int)AIRSTRUCSIZE)
					{
						info_airgrp* A=*I;
						currUID=UID_Null;
						if (	A->nat.Evaluate()==(int)NAT_BLUE
							&&	staticbands[BlueAirfieldBANDNum].visible
							)
							currUID=FindNeighbour(currobj,BlueAirfieldBANDNum,zoomiconsize*3);
						else
						if (	A->nat.Evaluate()==(int)NAT_RED
							&&	staticbands[RedAirfieldBANDNum].visible
							)
							currUID=FindNeighbour(currobj,RedAirfieldBANDNum,zoomiconsize*3);
						if  (currUID)
						{
////							currUID=FindNeighbour(currUID,RedVetoedBANDNum);
							A->position.MakeRelWorldPos(currUID);
							A->position.EvalW(A->World);
							A->World.X+=zoomiconsize;
							A->World.Z+=zoomiconsize;
							A->position[1][1]=-1;
						}
					}
						AcItemForm->ProcessForm(0,0);
						break;
					}
					case	SETSQUADHOMEBASE:
					{
						AcItemForm->ProcessForm(0,0);
					}
					break;
					case	SETAIRFIELD:
					{
						currUID=*UIDLocation;
						info_waypoint* W=*Persons2::ConvertPtrUID(currwp);
						W->target = currUID;
						if (W->position[0].Evaluate()!=ENABLE_COMPLEX_VAL)
								W->position[0]=ENABLE_COMPLEX_VAL;
						W->position[0][0]=0;
						W->position[0][1]=-W->position[0][1];//
						W->position[0][2]=0;
						W->position.EvalW(W->World);
						Coords3D& c=Persons2::ConvertPtrUID(currUID)->World;
						W->World.X+=c.X+zoomiconsize;
						W->World.Z+=c.Z-zoomiconsize;
						WayPointForm->ShowWpDialog( 0,0);
					}
					break;
				}

			}

}

//---------------------------------------------------------------------------
UniqueID TMissionEditor::FindNeighbour(UniqueID existing,UidBandNum band,int bestrange)
{
	ItemBasePtr S=Persons2::ConvertPtrUID(existing);
	UniqueID bestuid=UID_Null;
	if (S)
	{
		for(	UniqueID currUID = UniqueID(staticbands [band].startband);
				(((int)currUID) < ((int)staticbands [band].endband));
				currUID=(UniqueID)((int)currUID+1)
			)
		{
			ItemBasePtr T=Persons2::ConvertPtrUID(currUID);
			if (T)
			{
				int range=	Math_Lib.AbsSign(T->World.X-S->World.X)
						+   Math_Lib.AbsSign(T->World.Z-S->World.Z);
				if (range<bestrange)
				{
					bestrange=range;
					bestuid=T->uniqueID.count;
				}
			}
		}
	}
	return bestuid;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ImageMouseUp(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	MapTimer->Enabled=false;
	UniqueID currUID;
	if  ((int)Button == 0)			//Controls::mbLeft
	{
		if (findingstatic != NULL)
		{
			dragging=false;
			MouseUpFindStatic(X,Y);
		}
		else
		if (dragging)	//we are dragging
		{
        	EndDrag();
			loadedbfs[bfieldbeingfilled].changed=true;
//			MissionEditor->MissionEdited=true;
			if (FastClick)
			{
				if (!currwp)
				{
					ShowItemDialog(X,Y);
				}else
				{
					WayPointForm->ShowWpDialog(X,Y);
				}
			}else
			{
               	int wx=X,wy=Y;
				WorldPosition(wx,wy);
				if (currwp)
				{	//dragging a waypoint
	                MoveWp(wx,wy);

					info_waypoint*	W=*Persons2::ConvertPtrUID(currwp);
					if (!W->events)
					{	//dragging event waypoint
						if  (	(OverStatic(X,Y,currUID))
							 &&	(currUID != W->owner)
							 )
						{
                        	//if  landing get takeoff point
							int targ=W->target.Evaluate();
							int alt;
							bool altcalc = false;
							if (targ == ENABLE_COMPLEX_VAL)
							{
								info_itemS* t=*Persons2::ConvertPtrUID(currUID);
								if 	(		(t->World.Y <= 0)
										&&	(W->World.Y <= 0)
									)
								{
									altcalc = true;
									alt = -W->World.Y + t->World.Y;
								}
							}

							W->target = currUID;
							if (W->position[0].Evaluate()!=ENABLE_COMPLEX_VAL)
								W->position[0]=ENABLE_COMPLEX_VAL;
							W->position[0][0]=0;
							if (altcalc)
								W->position[0][1]=alt;
							W->position[0][2]=0;
							W->position.EvalW(W->World);
							Coords3D& c=Persons2::ConvertPtrUID(currUID)->World;
							W->World.X+=c.X+zoomiconsize;
							W->World.Z+=c.Z-zoomiconsize;
						}
						else
						{	//draging static waypoint
							int targ=W->target.Evaluate();
							bool altcalc = false;
							int alt;
							ItemBasePtr I=Persons2::ConvertPtrUID(currobj);
							if (targ != ENABLE_COMPLEX_VAL)
							{
								altcalc = true;
								if ((int)I->Status.size==(int)AIRSTRUCSIZE)
									alt = -100000;
								else
									alt = 0;
								info_itemS* t=*Persons2::ConvertPtrUID(targ);
								if 	(t->World.Y <= 0)
										alt = -W->World.Y + t->World.Y;
							}
							W->target = ENABLE_COMPLEX_VAL;
							if (altcalc)
								W->position[0][1]=alt;
							W->position.EvalW(W->World);

							//only reset target waypoints for aircraft
							//doesn't matter for truck, rdh
							if ((int)I->Status.size==(int)AIRSTRUCSIZE)
								WayPointForm->ResetTargetAction();
						}
					}
					WayPointForm->PositionEvents();
					formposninfo[WayPointFormId].type = POSN_OPPOSITE;
					WayPointForm->ShowWpDialog( X, Y);
				}else
				{	//dragging item
	                MoveTransient(wx,wy);
					ItemBasePtr I=Persons2::ConvertPtrUID(currobj);
					if ((int)I->Status.size==(int)AIRSTRUCSIZE)
					{
						info_airgrp* A=*I;
						currUID=UID_Null;
						if (	A->nat.Evaluate()==(int)NAT_BLUE
							&&	staticbands[BlueAirfieldBANDNum].visible
							)
							currUID=FindNeighbour(currobj,BlueAirfieldBANDNum,zoomiconsize*3);
						else
						if (	A->nat.Evaluate()==(int)NAT_RED
							&&	staticbands[RedAirfieldBANDNum].visible
							)
							currUID=FindNeighbour(currobj,RedAirfieldBANDNum,zoomiconsize*3);
						if  (currUID)
						{
////							currUID=FindNeighbour(currUID,RedVetoedBANDNum);
							A->position.MakeRelWorldPos(currUID);
							A->position.EvalW(A->World);
							A->World.X+=zoomiconsize;
							A->World.Z+=zoomiconsize;
							A->position[1][1]=-1;
						}
					}
					ResetTargetWayPoints();
					PaintRefresh();
				}

			}
		}
		CurrCanvas->Pen(pmCopy,TColor(0),1);
		//only refresh all time on normal zoom, other code should do most of work when refresh is slower
		//this makes sure all possibilities are covered
		//for instance without this call, last curr event is not removed if filter not on
		if (zoom == 200)
			PaintRefresh();
		else
		{
			RefreshTimer->Enabled=false;
			RefreshTimer->Enabled=true;
		}

//		DrawStatics();
		dragging = NOTDRAGGING;
	}
    else
    	if (!FastClick && currobj && dragging)
	    {
           	int wx=X,wy=Y;
			WorldPosition(wx,wy);
			MoveTransient(wx,wy);
 //			dragging = NOTDRAGGING;
        	EndDrag();
 			POINT p={X,Y};
			p=((TControl*)Sender)->ClientToScreen(p);
			MapPopupMenu->Popup(p.x,p.y);
    	}
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MoveWp(int X, int Y)
{
//////	CurrCanvas->Pen->Mode = pmNotXor;
//////	CurrCanvas->Pen->Mode = pmXor;
////
//////clip to map
////	if (X<0)
////		X = 0;
////	if (Y<0)
////		Y = 0;
////	if (X >	ScrollBox->HorzScrollBar->Range)
////		X =	ScrollBox->HorzScrollBar->Range;
////	if (Y >	ScrollBox->VertScrollBar->Range)
////		Y =	ScrollBox->VertScrollBar->Range;
////
////
////	DrawWp();
////
	info_waypoint* W=*Persons2::ConvertPtrUID(currwp);
	if (!W->events)
	{
		//reset when moving off a target
				int targ=W->target.Evaluate();
				bool altcalc = false;
				int alt;
				ItemBasePtr I=Persons2::ConvertPtrUID(currobj);
				if (targ != ENABLE_COMPLEX_VAL)
				{
					altcalc = true;
					if ((int)I->Status.size==(int)AIRSTRUCSIZE)
						alt = -100000;
					else
						alt = 0;
					info_itemS* t=*Persons2::ConvertPtrUID(targ);
					if 	(t && t->World.Y <= 0)
							alt = -W->World.Y + t->World.Y;
				}
				W->target = ENABLE_COMPLEX_VAL;
				if (altcalc)
					W->position[0][1]=alt;

//		W->target=(int)ENABLE_COMPLEX_VAL;
////		WorldPosition(X,Y);
		W->position[0][0]=X;
		W->position[0][2]=Y;
		W->position.EvalW(W->World);

	}else
	{
		WayPointForm->NewEventWpPos(X,Y);
	}
////
////	DrawWp();
////
////
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MoveTransient(int X, int Y)
{
		info_itemS* I=*Persons2::ConvertPtrUID(currobj);
		info_waypoint* W=NULL;
		int 	x,y;
		int 	wx,wy;
		if (I->Status.size>=MOBILESIZE)
		{
			info_grndgrp* t=*I;
			W=*Persons2::ConvertPtrUID(t->wpref);
			wx=W->World.X;
			wy=W->World.Z;
		}
////		WorldPosition(X,Y);
		if (I->position[0].Evaluate()!=ENABLE_COMPLEX_VAL)
		{   //only aircraft should get here
			//so if not on airfield reset the alt to 1000m
			I->position[0]=ENABLE_COMPLEX_VAL;
			I->position[0][1]=-100000;
			AcItemForm->WorldY=-100000;
			info_grndgrp* t=*I;
			t->vel = ENABLE_COMPLEX_VAL;
		}
		I->position[0][0]=X;
		I->position[0][2]=Y;
		I->position.EvalW(I->World);
}
//////---------------------------------------------------------------------------
////void __fastcall TMissionEditor::MoveTransientNotWP(int X, int Y)
////{
////		WayPointForm->Close();
////		info_itemS* I=*Persons2::ConvertPtrUID(currobj);
////		int 	x,y;
////		x=I->World.X;
////		y=I->World.Z;
////		ScreenPosition(x,y);
////
////		CurrCanvas->Rectangle(x-ICONW/2, y-ICONW/2, x+ICONW/2, y+ICONW/2);
////
////		WorldPosition(X,Y);
////		if (I->position[0].Evaluate() != ENABLE_COMPLEX_VAL)
////		{
////			AcTarget = I->position[0].Evaluate();
////			I->position[0]= ENABLE_COMPLEX_VAL;
////		}
////		I->position[0][0]=X;
////		I->position[0][2]=Y;
////		I->position.EvalW(I->World);
////
////		x=I->World.X;
////		y=I->World.Z;
////		ScreenPosition(x,y);
////
////		CurrCanvas->Rectangle(x-ICONW/2, y-ICONW/2, x+ICONW/2, y+ICONW/2);
////}
////
////
////
//////---------------------------------------------------------------------------
void __fastcall TMissionEditor::ImageMouseMove(TObject *Sender,
	TShiftState Shift, int X, int Y)
	{
		MouseMove(X,Y);
	}


void TMissionEditor::MouseMove(int X, int Y)
{


	UniqueID currUID;
	char			buff[50];

	if (InMenu)
	{
		InMenu = false;
		PaintRefresh();
	}
	if (OverStatic(X,Y,currUID))
	{
		char*	tmp =  GetList(ENUM_UIDtitle).Translate(currUID);
		if (tmp == NULL)
		{
			int text = MissionEditor->GetBandorShapeText(currUID);
			LoadString(HInstance,text,buff,sizeof(buff));
			StatusBar->Panels->Items[1]->Text = buff;

		}else
			StatusBar->Panels->Items[1]->Text = tmp;

	}else
	{
    	//calc square number from world coordinates...
        int wx=X,wy=Y;
   		WorldPosition(wx,wy);
        wx/=512*512;
        wy/=512*512;
        wx=100000*(wx/64) + 1000*((wx/8)%8) + 10*(wx%8);
        wy= 10000*(wy/64) +  100*((wy/8)%8) +  1*(wy%8);
        char outbuff[7];
        sprintf(outbuff,"%6i",wx+wy+111111);
		StatusBar->Panels->Items[1]->Text = outbuff;
	}

	if (!FastClick)
	{
		if (dragging == DRAGGINGLEFT || dragging == DRAGGINGRIGHT)
		{
        	MoveDragPix(X,Y);
		}else
		{
			rightX = X;	//done here for top menu...
			rightY = Y;
		}
	}
	else
	{
		WorldPosition(X,Y);
		FC_x=X;
		FC_y=Y;
	}
  TVarRec tempvar[2] = {X*ZOOMINITIAL/zoom, Y*ZOOMINITIAL/zoom};
//  TVarRec tempvar[2] = {X, Y};

//  StatusBar->Panels->Items[0]->Text = Format("%d,%d", tempvar, 2);

//  	TRect	ARect;
//	ARect = CurrCanvas->ClipRect;

//    tempvar[0] = ARect.Left;
//    tempvar[1] = ARect.Top;
//    tempvar[0] = ARect.Right;
//    tempvar[1] = ARect.Bottom;
//  StatusBar->Panels->Items[0]->Text = Format("(%d, %d,)",tempvar , 2);


}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ImageMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
//   RodsWayPoint*	currwp;
//   TransItem*	currtransitem;
//////   TransItem*	oldtransitem = CurrTransItem;

	FC_x=X;
	FC_y=Y;
    WorldPosition(FC_x,FC_y);

	if (Editting == EDITMOVETO)
	{
		MainMenuMoveToEdit(X,Y);
		InMenu = false;
		return;
	}
	if (Editting == EDITCOPY)
	{
		MainMenuCopyEdit(X,Y);
		InMenu = false;
		return;
	}
	if (InMenu)
	{
		PaintRefresh();
		dragging = NOTDRAGGING;
		InMenu = false;
		return;
	}

	if (dragging)
		return;

	int	tlx=X-ICONW/2,	//The icons are centred on the world position already,
		tly=Y-ICONW/2,	//
		brx=X+ICONW/2,	//I am considering a box around the mouse to be equivalent
		bry=Y+ICONW/2;	//to a box around the icon

		WorldPosition(brx,bry);
		WorldPosition(tlx,tly);




	//	dragging = FALSE;
		dragging = NOTDRAGGING;
   FastClick = true;
//   CurrTransItem = NULL;

//   if (	 (	(int)Button == 0)				//mbLeft
//		&& (findingstatic == NULL)
//		)
	if(	(findingstatic == NULL)	)
	{
		int	uid=currobj;
		info_base* i=*Persons2::ConvertPtrUID(UniqueID(uid));
		if (!i
			||	brx<i->World.X || bry>i->World.Z
			||	tlx>i->World.X || tly<i->World.Z)
		for(SWord b = 0; b < (int)MaxBANDNum;b++)
		{
			i=NULL;
			if (staticbands [b].visible)
			{
				for(uid = staticbands [b].startband;
					uid < (int)staticbands [b].endband;
					uid ++)
				{
					i=*Persons2::ConvertPtrUID(UniqueID(uid));
					if (i
						&&	brx>i->World.X && bry<i->World.Z
						&&	tlx<i->World.X && tly>i->World.Z)
					{
						if ((MissionEditor->loadedbfs[i->bfieldindex].viewable)
							&&  (SuperGroupViewable(uid))
							)

//        				if (	(i->bfieldindex || canmodifymainworld)
  //							||	(displayworldtemplateitems)
	//						)
							{
								b=MaxBANDNum;
								break;
							}
					}
					i=NULL;
				}
			}
		}
		if (!i && currobj && !staticbands[WayPointBANDNum].visible)
		{	//waypoints not displayed, except for current asset
			if (Persons2::ConvertPtrUID(currobj)->Status.size>=MOBILESIZE)
			{

				if (currwp)
				{
					uid=currwp;
					i=*Persons2::ConvertPtrUID(currwp);
				}
				if (!i
				||	brx<i->World.X || bry>i->World.Z
				||	tlx>i->World.X || tly<i->World.Z)
				{
					info_grndgrp* t=*Persons2::ConvertPtrUID(currobj);
					uid=t->wpref;
					while (uid)
					{
						i=*Persons2::ConvertPtrUID(UniqueID(uid));
						if (i
							&&	brx>i->World.X && bry<i->World.Z
							&&	tlx<i->World.X && tly>i->World.Z)
							break;
						info_waypoint* w=*i;
						i=NULL;
						uid=w->nextwp;
					}
				}
			}
		}
		if 	 (	(int)Button == 0)				//mbLeft
		{
			if (i)
			{	//got an object - now what?
				MapTimer->Enabled = true;
				if (uid>=(int)WayPointBAND && uid<(int)WayPointBANDEND)
				{
					currwp=UniqueID(uid);
					currobj=((info_waypoint*)*i)->owner;
					dragging = DRAGGINGLEFT;
				}
				else
				{
					WayPointForm->Close();
					currwp=UID_Null;
					currtemplateitem=UID_Null;
					currobj=UniqueID(uid);
					dragging = DRAGGINGLEFT;
				}
				PaintRefresh();
			}
			else
			{
				if ((int)currtransient != (int)T_WAYPOINT)
					MakeTransient(X,Y);
				else
				{

					if (!currwp)
					{
						if (currobj &&	Persons2::ConvertPtrUID(currobj)->Status.size>=MOBILESIZE)
						{
							info_grndgrp*	g=*Persons2::ConvertPtrUID(currobj);
							if (g->wpref)
							{
								WayPointForm->InsertWPBefore(g->wpref);
								info_waypoint* W=*Persons2::ConvertPtrUID(currwp);
								WorldPosition(X,Y);
								W->position[0][0]=X;

	//							UniqueID	prevu=W->prevwp;
	//							ItemBasePtr prevwp;
	//							if (prevu)
	//							{
	//								info_waypoint* tmp=*Persons2::ConvertPtrUID(prevu);
	//								prevwp=tmp;
	//							}
	//							else
	//							{
	//								info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	//								prevwp=tmp;
	//							}
	//							W->pos[0][1]=prevwp->World.Y;
								W->position[0][2]=Y;
								W->position.EvalW(W->World);
								WayPointForm->PositionEvents();
								WayPointForm->ShowWpDialog( X, Y);
							}
						}
					}
					else
					{
						UniqueID next;
						info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
						if (currwp)
							next =	W->nextwp;
						else
							next = UID_Null;
						if (next)
						{
							WayPointForm->InsertWPAfter(currwp);
							info_waypoint* W=*Persons2::ConvertPtrUID(currwp);
							WorldPosition(X,Y);
							W->position[0][0]=X;
							W->position[0][2]=Y;
							W->position.EvalW(W->World);
							WayPointForm->PositionEvents();
							WayPointForm->ShowWpDialog( X, Y);
						}else
						{
							WayPointForm->InsertWPBefore(currwp);
							info_waypoint* W=*Persons2::ConvertPtrUID(currwp);
							WorldPosition(X,Y);
							W->position[0][0]=X;
							W->position[0][2]=Y;
							W->position.EvalW(W->World);
							WayPointForm->PositionEvents();
							WayPointForm->ShowWpDialog( X, Y);
						}

					}
				}
			}
		}else
		{//right button, set up currobj and currwp
			rightX = X;
			rightY = Y;

			AcTarget=UID_Null;
			if (i)
			{	//got an object - now what?
//				dragging = DRAGGINGRIGHT;
				MapTimer->Enabled = true;
				if (uid>=(int)WayPointBAND && uid<(int)WayPointBANDEND)
				{
					clickedonitem = true;
					currwp=UniqueID(uid);
					currobj=((info_waypoint*)*i)->owner;
				}
				else
				{
					clickedonitem = true;
					//if it's a main world item and editing of main world is disabled show dialogue now!
//					if (!i->bfieldindex && !canmodifymainworld)
  //						currtemplateitem=UniqueID(uid);
	//				else
					{
						dragging = DRAGGINGRIGHT;
						currtemplateitem=UID_Null;
						currobj=UniqueID(uid);
					}
					currwp=UID_Null;
				}
			PaintRefresh();
			}else
            {
				clickedonitem = false;
                POINT p={X,Y};
                p=((TControl*)Sender)->ClientToScreen(p);
                MapPopupMenu->Popup(p.x,p.y);
            }


		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ViewZoomInClick(TObject *)
{
//rdh	if (zoom < 700)
	if (zoom < ZOOMMAXABS)
   {
		oldzoom = zoom;
		if (zoom <= ZOOMMAXMAP)
			zoom += 100;
		else
			zoom += 200;
		if (zoom > ZOOMMAXABS)
			zoom = ZOOMMAXABS;
					
		SetZoomLabel();
		SetScrollBars();
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		MissionEditor->Invalidate();
   }
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ViewZoomOutClick(TObject *)
{
	if (zoom > 100)
   {
		oldzoom = zoom;
		zoom -= 100;
		SetZoomLabel();
		SetScrollBars();
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		MissionEditor->Invalidate();
	}               
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMCenterClick(TObject *)
{
		CentreSetScrollBars(rightX,rightY);
		MissionEditor->Invalidate();
	
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMZoomOutClick(TObject *)
{

	if (zoom > 100)
   {	
		oldzoom = zoom;
		zoom -= 100;

		SetZoomLabel();                 
		CentreSetScrollBars(rightX,rightY);
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		MissionEditor->Invalidate();                  
	}               
	
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMZoomInClick(TObject *)
{
	if (zoom < ZOOMMAXABS)
   {
		oldzoom = zoom;
		if (zoom <= ZOOMMAXMAP)
			zoom += 100;
		else
			zoom += 200;
		if (zoom > ZOOMMAXABS)
			zoom = ZOOMMAXABS;
						 
		
		SetZoomLabel();                 
		CentreSetScrollBars(rightX,rightY);
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		PaintRefresh();
   }
				
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ResetSpeedButtons()
{
//	SB_A_Tank->Down = false;
//	SB_A_Aircraft->Down = false;
////	SB_A_Balloon->Down = false;
 ////	SB_CP_Tank->Down = false;
  ////	SB_CP_Aircraft->Down = false;
   //	SB_CP_Balloon->Down = false;
}                                         
//---------------------------------------------------------------------------

void __fastcall TMissionEditor::SB_A_AircraftClick(TObject *)
{
	ResetSpeedButtons();
	SB_A_Aircraft->Down = true;
	CurrNationality = ALLIES;
	currtransient = T_AIRCRAFT;
	currtransientshape = NULL;

	SB_Ac_Filter->Down = true;
	staticbands [RedAcBANDNum].visible = true;	
	staticbands [BlueAcBANDNum].visible = true;

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_A_TankClick(TObject *)
{
	ResetSpeedButtons();
	SB_A_Tank->Down = true;
	currtransient = T_TANK;
	currtransientshape = SB_A_Tank->Tag;
	CurrNationality = ALLIES;

	SB_Tank_Filter->Down = true;
	staticbands [RedSAMBANDNum].visible = true;
	staticbands [BlueSAMBANDNum].visible = true;
	PaintRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_A_BalloonClick(TObject *)
{
	ResetSpeedButtons();
	SB_A_Balloon->Down = true;
	currtransient = T_BALLOON;
	currtransientshape = SB_A_Balloon->Tag;
	CurrNationality = ALLIES;

	SB_Bl_Filter->Down = true;
	staticbands [RedGICBANDNum].visible = true;
	staticbands [BlueGICBANDNum].visible = true;
	PaintRefresh();
}                   
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_CP_AircraftClick(TObject *)
{
	ResetSpeedButtons();
	SB_CP_Aircraft->Down = true;
	currtransient = T_AIRCRAFT;
	currtransientshape = NULL;
	CurrNationality = CENTRALPOWERS;            

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_CP_BalloonClick(TObject *)
{
	ResetSpeedButtons();
	SB_CP_Balloon->Down = true;
	currtransient = T_BALLOON;
	currtransientshape = SB_CP_Balloon->Tag;
	CurrNationality = CENTRALPOWERS;

	SB_Bl_Filter->Down = true;
	staticbands [RedGICBANDNum].visible = true;
	staticbands [BlueGICBANDNum].visible = true;
	PaintRefresh();
}                   

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_CP_TankClick(TObject *)
{
	ResetSpeedButtons();
	SB_CP_Tank->Down = true;
	currtransient = T_TANK;
	currtransientshape = SB_CP_Tank->Tag;
	CurrNationality = CENTRALPOWERS;


	SB_Tank_Filter->Down = true;
	staticbands [RedSAMBANDNum].visible = true;
	staticbands [BlueSAMBANDNum].visible = true;
	PaintRefresh();
}
//---------------------------------------------------------------------------//---------------------------------------------------------------------------
void __fastcall TMissionEditor::CampaignClick(TObject *)
{
//	AircraftForm->OpenForm();


}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MissionBaseClick(TObject *)
{
//	TmpPlayerHomeBase = MissionEditor->PlayerHomeBase;

//	 MissionBaseForm->OpenInfo();
//camp tmp	 SetCaption(ActiveCampaign.name,ActiveCampaign.mission[currmission].name);
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MissionConditionsClick(TObject *)
{
//	 MissionConditionsForm->OpenForm();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::CampaignPilotsClick(TObject *)
{
//	 AvailableAces->OpenForm();
  //	 ResPool->OpenForm();
//	 PilotForm->OpenForm();


}

void __fastcall TMissionEditor::MapTimerTimer(TObject *)
{
	FastClick = false;
	MapTimer->Enabled = false;
    StartDragItem();
    MoveDrag(FC_x,FC_y);
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ViewToolBarClick(TObject *)
{
//		TPanel* tmp=TransPanelSwap;
  //		TransPanelSwap=TransientPanel;
	//	TransientPanel=tmp;
		

	if (ViewToolBar->Checked == true)
	{
		ViewToolBar->Checked = false;
		SpeedBar->Visible = false;
		TransPanelSwap->Visible=true;
		Panel3->Visible=true;
		if (ToolBarFilter->Checked==false)
			FilterSpeedBar->Visible = false;
//		TransientPanel->Parent=FilterSpeedBar;
  //		FilterSpeedBar->Refresh();
	}else
	{
		FilterSpeedBar->Visible = true;
		SpeedBar->Visible = true; 
		ViewToolBar->Checked = true;
		TransPanelSwap->Visible=false;
		Panel3->Visible=false;
//		TransientPanel->Parent=SpeedBar;
		
	}
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ToolBarFilterClick(TObject *)
{
	static int panelx=0;
	if (panelx==0)panelx=Panel1->Left;
	if (ToolBarFilter->Checked == true)
	{
		ToolBarFilter->Checked = false;
		if (ViewToolBar->Checked)
			FilterSpeedBar->Visible = true;
		else
			FilterSpeedBar->Visible = false;
		Panel1->Left=0;
	}else
	{
		ToolBarFilter->Checked = true;
		FilterSpeedBar->Visible = true;
		Panel1->Top=panelx;
	}

	if ((int)FilterSpeedBar->Align==(int)alTop)
		FilterSpeedBar->Align=alLeft;
	else	
		FilterSpeedBar->Align=alTop;
	for (int i=ComponentCount-1;i>=0;i--)
		if (Components[i]->Tag==-1)
		{
		   TControl* T=(TControl*)	Components[i];
		   int tmp=T->Width;
		   T->Width=T->Height;
		   T->Height=tmp;
		   tmp=T->Top;
		   T->Top=T->Left;
		   T->Left=tmp;
		}
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MoveClick(TObject *)
{
//	   PlaySound("ID_YELL2",HInstance,SND_ASYNC|SND_RESOURCE);
		Editting = EDITMOVETO;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_ArrowClick(TObject *)
{
	ResetSpeedButtons();
	currtransient = T_NONE;
	currtransientshape = NULL;


}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_RouteClick(TObject *)
{
	ResetSpeedButtons();
	currtransient = T_WAYPOINT;
	currtransientshape = NULL;

	SB_Route_Filter->Down = true;
	staticbands [WayPointBANDNum].visible = true;
	PaintRefresh();
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_Route_FilterClick(TObject *)
{
	if (SB_Route_Filter->Down == true)
	{
		staticbands [WayPointBANDNum].visible = true;
	}else
	{
		staticbands [WayPointBANDNum].visible = false;
	}
	PaintRefresh();
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_Settlement_FilterClick(TObject *)
{

	if (SB_Settlement_Filter->Down == true)
	{
		staticbands [AmberSupplyBANDNum].visible = true;
	}else
	{
		staticbands [AmberSupplyBANDNum].visible = false;
	}
	PaintRefresh();


}
void __fastcall  TMissionEditor::SB_SupplyFilterClick(TObject *)
{
	if (SB_SupplyFilter->Down == true)
	{
		staticbands [RedPortBANDNum].visible = true;
		staticbands [BLuePortBANDNum].visible = true;
	}else
	{
		staticbands [RedPortBANDNum].visible = false;
		staticbands [BLuePortBANDNum].visible = false;
	}
	PaintRefresh();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_Af_FilterClick(TObject *)
{

	if (SB_Af_Filter->Down == true)
	{
		staticbands [AmberAirfieldBANDNum].visible = true;
		staticbands [RedAirfieldBANDNum].visible = true;
		staticbands [BlueAirfieldBANDNum].visible = true;
	}else
	{
		staticbands [AmberAirfieldBANDNum].visible = false;
		staticbands [RedAirfieldBANDNum].visible = false;
		staticbands [BlueAirfieldBANDNum].visible = false;
	}

	PaintRefresh();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SetZoomLabel()
{
	ZoomLabel->Caption = IntToStr(zoom/2) + "%";
	ZoomLabel2->Caption=ZoomLabel->Caption;

}
////---------------------------------------------------------------------------
//void __fastcall TMissionEditor::ViewZoomResetClick(TObject *)
//{
//		oldzoom = zoom;
//		zoom = 200;
//
//		SetZoomLabel();
//		SetScrollBars();
//		PaintRefresh();
//
//}
//---------------------------------------------------------------------------
//void __fastcall TMissionEditor::MapPopupMenuPopup(TObject *)
//{
//	   PlaySound("ID_YELL2",HInstance,SND_ASYNC|SND_RESOURCE);
//
//}

void __fastcall TMissionEditor::MapPopupMenuPopup(TObject *)
{
 //	UniqueID currUID;

//	   PlaySound("ID_YELL2",HInstance,SND_ASYNC|SND_RESOURCE);
		WayPointForm->Close();
		InMenu = true;                    

		if (clickedonitem)
//		if (OverStatic(rightX,rightY,currUID))
		{
			if (		(dragging)
					&&(!FastClick)
			   )
			{
				SMMoveTo->Visible = true;
				SMCopy->Visible = true;
				SMZoomIn->Visible = false;
				SMZoomOut->Visible = false;
				SMZoomReset->Visible = false;
				SMZoomInMax->Visible = false;
				SMZoomInMapMax->Visible = false;
				SMCenter->Visible = false;
				Spacer->Visible = false;
				SMOpen->Visible = false;
				SMDelete->Visible = false;
				SMScale->Visible = false;
				CurrCanvas->Pen(pmCopy,(TColor)0,1);
			}else                         
			{
				SMMoveTo->Visible = false;
				SMCopy->Visible = false;
				SMOpen->Visible = true;
				SMDelete->Visible = true;
				SMZoomIn->Visible = true;
				SMZoomOut->Visible = true;
				SMZoomInMax->Visible = true;
				SMZoomInMapMax->Visible = true;
				SMZoomReset->Visible = true;
				SMCenter->Visible = true;
				Spacer->Visible = true;
				SMScale->Visible = true;
			}
		}else
		{
		 	SMMoveTo->Visible = false;
		 	SMCopy->Visible = false;
			SMOpen->Visible = false;
			SMDelete->Visible = false;
			SMZoomIn->Visible = true;
			SMZoomOut->Visible = true;
			SMZoomReset->Visible = true;
			SMZoomInMax->Visible = true;
			SMZoomInMapMax->Visible = true;
			SMCenter->Visible = true;
			SMScale->Visible = true;
			Spacer->Visible = true;
		}
			dragging = NOTDRAGGING;

}

//---------------------------------------------------------------------------
 void __fastcall TMissionEditor::SB_Hospital_FilterClick(TObject *)
 {
	if (SB_Hospital_Filter->Down == true)
	{
		staticbands [AmberCivilianBANDNum].visible = true;
	}else
	{
		staticbands [AmberCivilianBANDNum].visible = false;
	}
	PaintRefresh();	
  
 }

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_HQ_FilterClick(TObject *)

 {
	if (SB_HQ_Filter->Down == true)
	{
		staticbands [RedCCCBANDNum].visible = true;	
		staticbands [BlueCCCBANDNum].visible = true;	
	}else
	{
		staticbands [RedCCCBANDNum].visible = false;
		staticbands [BlueCCCBANDNum].visible = false;	
    }   
	PaintRefresh();	
  
 }

void __fastcall TMissionEditor::SB_BridgeFilterClick(TObject *)
{
	if (SB_BridgeFilter->Down == true)
	{
		staticbands [AmberBridgeBANDNum].visible = true;
    }else
	{
		staticbands [AmberBridgeBANDNum].visible = false;
	}
	PaintRefresh();	
  
	                 
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_AAA_FilterClick(TObject *)
{
	if (SB_AAA_Filter->Down == true)
	{
		staticbands [RedAAASiteBANDNum].visible = true;	
		staticbands [BlueAAASiteBANDNum].visible = true;	
    }else
    {
		staticbands [RedAAASiteBANDNum].visible = false;
		staticbands [BlueAAASiteBANDNum].visible = false;	
    }   
	PaintRefresh();	

	
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_Art_FilterClick(TObject *)
{
	if (SB_Art_Filter->Down == true)
	{
		staticbands [RedMilitaryBANDNum].visible = true;
		staticbands [BlueMilitaryBANDNum].visible = true;	
    }else
	{
		staticbands [RedMilitaryBANDNum].visible = false;
		staticbands [BlueMilitaryBANDNum].visible = false;	
    }   
	PaintRefresh();


}
//---------------------------------------------------------------------------
	void __fastcall TMissionEditor::SB_Event_FilterClick(TObject *)
{
	if (SB_Event_Filter->Down == true)
	{
		staticbands [LandscapeBANDNum].visible = true;
		LandscapeVisible |= EVENTVISIBLE;
	}else
	{
		LandscapeVisible = LandscapeVisible & ~(EVENTVISIBLE);
//		staticbands [LandscapeBANDNum].visible = false;
	}
	PaintRefresh();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_Group_FilterClick(TObject *)
{
	if (SB_Group_Filter->Down == true)
	{
		staticbands [MissileBANDNum].visible = true;
	}else
	{
		staticbands [MissileBANDNum].visible = false;
	}
	PaintRefresh();

}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_Single_FilterClick(TObject *)
{
	if (SB_Single_Filter->Down == true)
	{
		staticbands [LandscapeBANDNum].visible = true;
		LandscapeVisible |= SINGLEVISIBLE;
	}else
	{
		LandscapeVisible = LandscapeVisible & ~(SINGLEVISIBLE);
//		staticbands [LandscapeBANDNum].visible = false;
	}
	PaintRefresh();

}
//---------------------------------------------------------------------------

void __fastcall  TMissionEditor::SB_Bl_FilterClick(TObject *)
 {
	if (SB_Bl_Filter->Down == true)
	{
		staticbands [RedGICBANDNum].visible = true;
		staticbands [BlueGICBANDNum].visible = true;
	}else
	{
		staticbands [RedGICBANDNum].visible = false;
		staticbands [BlueGICBANDNum].visible = false;
	}
	PaintRefresh();

 }
//---------------------------------------------------------------------------
void __fastcall  TMissionEditor::SB_Ac_FilterClick(TObject *)
 {
	if (SB_Ac_Filter->Down == true)
	{
		staticbands [RedAcBANDNum].visible = true;	
		staticbands [BlueAcBANDNum].visible = true;	
    }else
    {
		staticbands [RedAcBANDNum].visible = false;
		staticbands [BlueAcBANDNum].visible = false;	
    }   
	PaintRefresh();
    	
  
 }
//---------------------------------------------------------------------------
void __fastcall  TMissionEditor::FormCoords(int X,int Y,FormId form,int& formX,int& formY,int formW,int formH)
{               
	if ((int)formposninfo[form].type == (int)POSN_OPPOSITE)
    {
		if (X < (ScrollBox->HorzScrollBar->Position + Screen->Width/2))
			X = Screen->Width/2;
		else
			X = 0;
    	if (Y < (ScrollBox->VertScrollBar->Position+Screen->Height/2))
			Y = Screen->Height/2;
        else
        	Y = 0;
            	  
		formX = X + (Screen->Width/2-formW)/2;
    	formY = Y + (Screen->Height/2-formH)/2;
        
    }else if ((int)formposninfo[form].type == (int)POSN_CENTER)
    {
    	formX = (Screen->Width-formW)/2;
    	formY = (Screen->Height-formH)/2;

    }
    formposninfo[form].x = formX;
    formposninfo[form].y = formY;
    formposninfo[form].type = POSN_USER;
}
void __fastcall TMissionEditor::SB_A_AAAClick(TObject *)
{
	ResetSpeedButtons();
	SB_A_AAA->Down = true;
	currtransient = T_AAA;
	currtransientshape = SB_A_AAA->Tag;
	CurrNationality = ALLIES;
		

	SB_AAA_Filter->Down = true;
	staticbands [RedAAASiteBANDNum].visible = true;
	staticbands [BlueAAASiteBANDNum].visible = true;	
	PaintRefresh();	
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_CP_AAAClick(TObject *)
{
	ResetSpeedButtons();
	SB_CP_AAA->Down = true;
	currtransient = T_AAA;
	currtransientshape = SB_CP_AAA->Tag;
	CurrNationality = CENTRALPOWERS;
	
	SB_AAA_Filter->Down = true;
	staticbands [RedAAASiteBANDNum].visible = true;	
	staticbands [BlueAAASiteBANDNum].visible = true;	
	PaintRefresh();	
   
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_A_BatteryClick(TObject *)
{
	ResetSpeedButtons();
	SB_A_Battery->Down = true;
	currtransient = T_BATTERY;
	currtransientshape = SB_A_Battery->Tag;
	CurrNationality = ALLIES;

	SB_Art_Filter->Down = true;
	staticbands [RedMilitaryBANDNum].visible = true;
	staticbands [BlueMilitaryBANDNum].visible = true;
	PaintRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_A_TruckClick(TObject *)
{
	ResetSpeedButtons();
	SB_A_Truck->Down = true;
	currtransient = T_TRUCK;
	currtransientshape = SB_A_Truck->Tag;
	CurrNationality = ALLIES;

	SB_Truck_Filter->Down = true;
	staticbands [RedCombatVehicleBANDNum].visible = true;
	staticbands [BlueCombatVehicleBANDNum].visible = true;
	MobilesVisible |=TRUCKSVISIBLE;
	PaintRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_CP_BatteryClick(TObject *)
{
	ResetSpeedButtons();
	SB_CP_Battery->Down = true;
	currtransient = T_BATTERY;
	currtransientshape = SB_CP_Battery->Tag;
	CurrNationality = CENTRALPOWERS;

	SB_Art_Filter->Down = true;
	staticbands [RedMilitaryBANDNum].visible = true;
	staticbands [BlueMilitaryBANDNum].visible = true;
	PaintRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_CP_TruckClick(TObject *)
{
	ResetSpeedButtons();
	SB_CP_Truck->Down = true;
	currtransient = T_TRUCK;
	currtransientshape = SB_CP_Truck->Tag;
	CurrNationality = CENTRALPOWERS;

	SB_Truck_Filter->Down = true;
	staticbands [RedCombatVehicleBANDNum].visible = true;
	staticbands [BlueCombatVehicleBANDNum].visible = true;
	MobilesVisible |=TRUCKSVISIBLE;
	PaintRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_A_TrainClick(TObject *)
{
	ResetSpeedButtons();
	SB_A_Train->Down = true;
	currtransient = T_TRAIN;
	currtransientshape = SB_A_Train->Tag;
	CurrNationality = ALLIES;

	SB_Train_Filter->Down = true;
	staticbands [RedTrainBANDNum].visible = true;
//	staticbands [BlueTrainBANDNum].visible = true;
	MobilesVisible |=TRAINSVISIBLE;
	PaintRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_CP_TrainClick(TObject *)
{
	ResetSpeedButtons();
	SB_CP_Train->Down = true;
	currtransient = T_TRAIN;
	currtransientshape = SB_CP_Train->Tag;
	CurrNationality = CENTRALPOWERS;

	SB_Train_Filter->Down = true;
	staticbands [RedTrainBANDNum].visible = true;
//	staticbands [BlueTrainBANDNum].visible = true;
	MobilesVisible |=TRAINSVISIBLE;
	PaintRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_A_TroopsClick(TObject *)
{
	ResetSpeedButtons();
	SB_A_Troops->Down = true;
	currtransient = T_TROOP;
	currtransientshape = SB_A_Troops->Tag;
	CurrNationality = ALLIES;

	SB_Troops_Filter->Down = true;
	staticbands [RedTroopBANDNum].visible = true;
	staticbands [BlueTroopBANDNum].visible = true;
	MobilesVisible |=TROOPSVISIBLE;

	PaintRefresh();


}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_CP_TroopsClick(TObject *)
{
	ResetSpeedButtons();
	SB_CP_Troops->Down = true;
	currtransient = T_TROOP;
	currtransientshape = SB_CP_Troops->Tag;
	CurrNationality = CENTRALPOWERS;

	SB_Troops_Filter->Down = true;
	staticbands [RedTroopBANDNum].visible = true;
	staticbands [BlueTroopBANDNum].visible = true;
	MobilesVisible |=TROOPSVISIBLE;
	PaintRefresh();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_EventClick(TObject *)
{
	ResetSpeedButtons();
	SB_Event->Down = true;
	currtransient = T_EVENT;
	currtransientshape = NULL;

	SB_Event_Filter->Down = true;
	LandscapeVisible |= EVENTVISIBLE;
	staticbands [LandscapeBANDNum].visible = true;
	PaintRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_SingleClick(TObject *)
{
	ResetSpeedButtons();
	SB_Single->Down = true;
	currtransient = T_SINGLEPOPULATE;
	LandscapeVisible |= SINGLEVISIBLE;
	staticbands [LandscapeBANDNum].visible = true;
	currtransientshape = SB_Single->Tag;
	SB_Single_Filter->Down = true;
	PaintRefresh();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_GroupClick(TObject *)
{
	ResetSpeedButtons();
	SB_Group->Down = true;
	currtransient = T_GROUPPOPULATE;
	staticbands [MissileBANDNum].visible = true;
	currtransientshape = SB_Group->Tag;
	SB_Group_Filter->Down = true;
	PaintRefresh();
            
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::CampaignPlayerClick(TObject *)
{
	  //int result =
//	  PlayerForm->ShowModal();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FillComboBox(int min, int max, TComboBox* combobox, int index)
{
	char buff[50];
	SWord j = 0;

	combobox->Items->Clear();

	while ((min+j) <= max)
	{
		LoadString(HInstance,min+j,buff,sizeof(buff));
		combobox->Items->Add(buff);
		j++;
	}

	combobox->ItemIndex =   index;

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::PartFillComboBox(EnumListNames list, int max, TComboBox* combobox, int index, int* ctrlarray)
{
	combobox->Items->Clear();
	for (int k=-1,j=0;j<max;j++)
		if	(ctrlarray[j] != -1)
		{
			combobox->Items->Add(GetList(list).Translate(j));
			k++;
			if  (j == index)
				combobox->ItemIndex =   k;
		}
	if (combobox->ItemIndex == -1)
		combobox->ItemIndex =   0;
}

void __fastcall TMissionEditor::PartFillComboBox(int min, int max, TComboBox* combobox, int index, int* ctrlarray)
{
	char buff[50];
	SWord j = 0,k=-1;

	combobox->Items->Clear();

	while ((min+j) <= max)
	{
		if	(ctrlarray[j] != -1)
		{
			LoadString(HInstance,min+j,buff,sizeof(buff));
			combobox->Items->Add(buff);
			k++;
			if  (j == index)
				combobox->ItemIndex =   k;
		}
		j++;
	}
 if (combobox->ItemIndex == -1)
	combobox->ItemIndex =   0;


}

//---------------------------------------------------------------------------
int __fastcall TMissionEditor::FindOrginalIndex(int min, int max,int index,int* ctrlarray)
{
	SWord j = 0;
	while ((min+j) <= max)
	{
		if (ctrlarray[j] == index)
			return (j);
		j++;

	 }
	 return (0);
}

void __fastcall TMissionEditor::SetFindingStaticMode(int method)
{
	findingstatic = method;
	switch (method)
	{
		case	SETTARGETEVENTVAR:
		{
			SelectTarget->Show();
			break;
		}
		case	SETSQUADHOMEBASE:
		case	SETAIRFIELD:
		case	SETTAKEOFFPOINT:
		case	SETENEMYHOMEBASE:
		case	SETHOMEBASE:
		case	SETHOMEBASEEVENTVAR:
		{
			staticbands [RedAirfieldBANDNum].visible = true;
			staticbands [BlueAirfieldBANDNum].visible = true;
			SB_Af_Filter->Down = true;
//////		 	FindingStaticVar = EventForm->EventListBox->ItemIndex;
			SelectAirfield->Show();
			PaintRefresh();
		}
		break;
		case	SETSUPERGROUP:
		{
			SB_SuperGroupFilter->Down = true;
			SB_AllDown();

			PaintRefresh();
			break;
		}


//		case	SETHOMEBASE:
  //		{
	//		staticbands [RedAirfieldBANDNum].visible = true;
	  //		staticbands [BlueAirfieldBANDNum].visible = true;
		//	SB_Af_Filter->Down = true;
//			SelectAirfield->Show();
  //			break;
	//	}
	  //	case	SETENEMYHOMEBASE:
		//{
		  //	staticbands [RedAirfieldBANDNum].visible = TRUE;
//			staticbands [BlueAirfieldBANDNum].visible = true;
  //			SB_Af_Filter->Down = true;
	//		SelectAirfield->Show();
	  //		break;
		//}
		case	SETMAINOBJECTIVE:
		case	SETSUBOBJECTIVE:
		case	SETWP1:
		case	SETWP2:
		case	SETWP3:
		case	SETWAYPOINT:
		{
			SelectTarget->Show();
			break;
		}
//		case	SETWAYPOINT:
  //		{
	//		SelectTarget->Show();
	  //		break;
		//}
//		case	SETAIRFIELD:
  //		{
	//		staticbands [RedAirfieldBANDNum].visible = true;
	  //		staticbands [BlueAirfieldBANDNum].visible = true;
//			SB_Af_Filter->Down = true;
  //			SelectAirfield->Show();
	//		break;
	  //	}

	}
}
void __fastcall TMissionEditor::MissionObjectivesClick(TObject *)
{
	  MissionObjectivesForm->OpenForm();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_AllDown()
{
		SB_Settlement_Filter->Down = true;
		SB_Af_Filter->Down = true;
		SB_BridgeFilter->Down = true;
		SB_HQ_Filter->Down = true;
		SB_SupplyFilter->Down = true;
		SB_Hospital_Filter->Down = true;
		SB_Single_Filter->Down = true;
		SB_Event_Filter->Down = true;
		SB_Group_Filter->Down = true;
		SB_Ac_Filter->Down = true;
		SB_Bl_Filter->Down = true;
		SB_Art_Filter->Down = true;
		SB_Truck_Filter->Down = true;
		SB_Train_Filter->Down = true;
		SB_Tank_Filter->Down = true;
		SB_AAA_Filter->Down = true;
		SB_Troops_Filter->Down = true;
		SB_Route_Filter->Down = true;
		MobilesVisible = ALLVISIBLE;
		LandscapeVisible = ALLVISIBLE;

		for(SWord i = 0; i < (int)MaxBANDNum;i++)
			staticbands [i].visible = true;
//		staticbands [GreenCivilianBANDNum].visible = false;
//		staticbands [RedVetoedBANDNum].visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_AllClick(TObject *)
{
	if (SB_All->Down == true)
	{
		SB_AllDown();
	}else
	{
		SB_Settlement_Filter->Down = false;
		SB_Af_Filter->Down = false;
		SB_BridgeFilter->Down = false;
		SB_HQ_Filter->Down = false;
		SB_SupplyFilter->Down = false;
		SB_Hospital_Filter->Down = false;
		SB_Single_Filter->Down = false;
		SB_Event_Filter->Down = false;
		SB_Group_Filter->Down = false;
		SB_Ac_Filter->Down = false;
		SB_Bl_Filter->Down = false;
		SB_Art_Filter->Down = false;
		SB_Truck_Filter->Down = false;
		SB_Train_Filter->Down = false;
		SB_Tank_Filter->Down = false;
		SB_AAA_Filter->Down = false;
		SB_Troops_Filter->Down = false;
		SB_Route_Filter->Down = false;
		MobilesVisible = 0;
	  	LandscapeVisible = 0;
		for(SWord i = 0; i < (int)MaxBANDNum;i++)
			staticbands [i].visible = false;
	}
	PaintRefresh();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FileSavePilotsClick(TObject *)
{

//	if (SavePilots->Execute())
//	{
//	 BOStream file(SavePilots->FileName.c_str());
//
//	 file.write((char*)&Active_Pilots,ACTIVEPILOTS*sizeof(MEPilotType));
//
//	}

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FileLoadPilotsClick(TObject *)
{
//	if (OpenPilots->Execute())
//	{
//		 BIStream file(OpenPilots->FileName.c_str());
//		 file.read((char*)&Active_Pilots,ACTIVEPILOTS*sizeof(MEPilotType));
//	}

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_Truck_FilterClick(TObject *)
{
	if (SB_Truck_Filter->Down == true)
	{
		MobilesVisible = MobilesVisible | (TRUCKSVISIBLE);
		staticbands [RedTruckBANDNum].visible = true;
 //		staticbands [BlueTruckBANDNum].visible = true;
	}else
	{
		MobilesVisible = MobilesVisible & ~(TRUCKSVISIBLE);
//		staticbands [RedGroundMobileBANDNum].visible = false;
//		staticbands [BlueGroundMobileBANDNum].visible = false;
	}
	PaintRefresh();


}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_Train_FilterClick(TObject *)
{
	if (SB_Train_Filter->Down == true)
	{
		MobilesVisible = MobilesVisible | TRAINSVISIBLE;
		staticbands [RedTrainBANDNum].visible = true;
		staticbands [RedTrainBANDNum].visible = true;
	}else
	{
		MobilesVisible = MobilesVisible & ~(TRAINSVISIBLE);
//		staticbands [RedGroundMobileBANDNum].visible = false;
//		staticbands [BlueGroundMobileBANDNum].visible = false;
	}
	PaintRefresh();


}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_Tank_FilterClick(TObject *)
{
	if (SB_Tank_Filter->Down == true)
	{
		staticbands [RedSAMBANDNum].visible = true;
		staticbands [BlueSAMBANDNum].visible = true;
	}else
	{
		staticbands [RedSAMBANDNum].visible = false;
		staticbands [BlueSAMBANDNum].visible = false;
	}
	PaintRefresh();
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ReservePoolClick(TObject *)
{
//	ReservePool->OpenForm();
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SetCaption(char* campaignname, char* missionname)
{
	char buff[200];

//	if (MissionMode)
//	{
		LoadString(HInstance,TEXT_MISSIONEDITTING,buff,sizeof(buff));
		strcat(buff,missionname);
		MissionEditor->Caption =  buff;

//	}else
//	{
//		LoadString(HInstance,TEXT_CAMPAIGNEDITTING,buff,sizeof(buff));
//		strcat(buff,campaignname);
//		strcat(buff,", ");
//		strcat(buff,"Mission: ");
//		strcat(buff,missionname);
//		MissionEditor->Caption =  buff;
//	}

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SetMissionMode(bool missionmode)
{
	char buff[50];
	char campname[50];

//	MissionMode = missionmode;
//	CampaignStarted = false;
//	MissionStarted = false;
//	if (MissionMode)
	{
//		RunCampaign->Visible = false;
		CampaignMenu->Visible = false;
		MissionInit->Visible = true;
//		FileMissionMode->Checked = true;
//		CampaignMode1->Checked = false;
		LoadString(HInstance,TEXT_MISSION,buff,sizeof(buff));
		MissionEditor->SetCaption("",buff);

		LoadString(HInstance,TEXT_NEWSINGLEMISSION,buff,sizeof(buff));
		NewMissionMenu->Caption = buff;
		LoadString(HInstance,TEXT_OPENSINGLEMISSION,buff,sizeof(buff));
		FileOpenMission->Caption = buff;
		LoadString(HInstance,TEXT_SAVESINGLEMISSION,buff,sizeof(buff));
		FileSaveMission->Caption = buff;
//		LoadString(HInstance,TEXT_SAVEASSINGLEMISSION,buff,sizeof(buff));
//		FileSaveAsMission->Caption = buff;
//		SaveCampaign->Enabled = false;


	}
//    else
//	{
//		MissionInit->Visible = false;
////		RunCampaign->Visible = true;
//		CampaignMenu->Visible = true;
////		FileMissionMode->Checked = false;
////		CampaignMode1->Checked = true;
//		LoadString(HInstance,TEXT_MISSION,buff,sizeof(buff));
//		LoadString(HInstance,TEXT_NEWCAMPAIGN,campname,sizeof(campname));
//		MissionEditor->SetCaption(campname,buff);
//
//		LoadString(HInstance,TEXT_NEWCAMPAIGNMISSION,buff,sizeof(buff));
//		NewMissionMenu->Caption = buff;
//		LoadString(HInstance,TEXT_OPENCAMPAIGNMISSION,buff,sizeof(buff));
//		FileOpenMission->Caption = buff;
//		LoadString(HInstance,TEXT_SAVECAMPAIGNMISSION,buff,sizeof(buff));
//		FileSaveMission->Caption = buff;
////		LoadString(HInstance,TEXT_SAVEASCAMPAIGNMISSION,buff,sizeof(buff));
////		FileSaveAsMission->Caption = buff;
////		SaveCampaign->Enabled = true;
//
//
//	}

 }
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::CampaignInitClick(TObject *)
{
//	   CampInit->OpenForm();
//	   MissionBaseForm->OpenInfo();
//camp tmp	 SetCaption(ActiveCampaign.name,ActiveCampaign.mission[currmission].name);

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MissionInitClick(TObject *)
{
//		MissionBaseForm->OpenInfo();
//camp tmp		SetCaption(ActiveCampaign.name,ActiveCampaign.mission[currmission].name);
}


//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FileOpenMissionClick(TObject *Sender)
{	//brought them all together here!
	BfieldForm->LoadNewClick(true);
}


//---------------------------------------------------------------------------
void __fastcall TMissionEditor::NewMissionMenuClick(TObject *Sender)
{	//brought them all together here!
	BfieldForm->LoadNewClick(false);
}


//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FileSaveMissionClick(TObject *)
{
	BfieldForm->SaveMission(bfieldbeingfilled);
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::metricClick(TObject *)
{

	char buff[200];

		Configure_Units = METRIC;
		imperial->Checked = false;
		metric->Checked = true;
	    mixed->Checked = false;
		LoadString(HInstance,TEXT_UNITSMETRIC,buff,sizeof(buff));
		ConfigureUnits->Caption = buff;


}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::imperialClick(TObject *)
{
	char buff[200];
		LoadString(HInstance,TEXT_UNITSIMPERIAL,buff,sizeof(buff));
		Configure_Units = IMPERIAL;
		imperial->Checked = true;
		metric->Checked = false;
        mixed->Checked = false;
		ConfigureUnits->Caption = buff;

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SetMobile(bool option)
{
	char buff[200];
	if (option)
	{
		Stationary->Checked = false;
		Mobile->Checked = true;
		LoadString(HInstance,TEXT_VEHICLEMOBILE,buff,sizeof(buff));
	}else
	{
		Stationary->Checked = true;
		Mobile->Checked = false;
		LoadString(HInstance,TEXT_VEHICLESTATIC,buff,sizeof(buff));
	}
	ConfigureVehicles->Caption = buff;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MobileClick(TObject *)
{
	SetMobile (true);
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::StationaryClick(TObject *)
{
	SetMobile (false);

}
//---------------------------------------------------------------------------
UniqueID __fastcall TMissionEditor::FindDefaultAirfield(SWord nationality)
{
	ItemBasePtr i;
	UidBandNum start;
	UniqueID currUID;


	if ((int)nationality == (int)NAT_BLUE)
		start = BlueAirfieldBANDNum;
	else
		start = RedAirfieldBANDNum;


	for(currUID = UniqueID(staticbands [start].startband);
			(((int)currUID) < ((int)staticbands [start].endband));
				currUID=(UniqueID)((int)currUID+1)
				)
   {
		i=Persons2::ConvertPtrUID(UniqueID(currUID));
		if  (i)
			return ( (UniqueID) currUID);
   }
		i=Persons2::ConvertPtrUID(UniqueID(currUID));
		if  (i)
			return ( (UniqueID) currUID);

	return ( (UniqueID) staticbands [start].startband);
}
//---------------------------------------------------------------------------
//			if  (MissionEditor->ActiveCampaign.mission[currmission].region == SOMMEREGION)

UniqueID __fastcall TMissionEditor::FindAirfield(SWord nationality,int region)
{
	ItemBasePtr i;
	UniqueID preferredbase;

//	switch	(nationality)
//	{
//		case	NAT_BLUE:
//		{
////			if  (region == SOMMEREGION)
//				preferredbase = UID_ToAlBoiryStMartin;
//  //			else
//	//			preferredbase = UID_ToAlEToul;
//
//			break;
//		}
//		case	NAT_RED:
//		{
//  //			if  (region == SOMMEREGION)
//				preferredbase =  UID_ToCpRoucourt;
//	//		else
//	  //			preferredbase = UID_ToCpThiaucourt;
//			break;
//		}
//	}
//
//	i=Persons2::ConvertPtrUID(preferredbase);
//	if  (i)
//		return (preferredbase);
	return(FindDefaultAirfield(nationality));

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::CheckHomeBase()
{
	CheckHomeBase(//ActiveCampaign.mission[currmission].PlayerNationality,
					//ActiveCampaign.mission[currmission].PlayerHomeBase,
					//ActiveCampaign.mission[currmission].EnemyHomeBase,
					//ActiveCampaign.mission[currmission].region
                	0,currhomebase,currhomebase,0

					);
}

void __fastcall TMissionEditor::CheckHomeBase(int fnat,UniqueID& fhome,UniqueID& ehome,int region)
{
	ItemBasePtr i;
	char buff[50];
	UniqueIDBand	homeband;
	UniqueID homeaf;


//	if (fnat == (int)NAT_RED)
//		homeaf=FindNeighbour(fhome,RedAirfieldBANDNum);
//	else
//		homeaf=FindNeighbour(fhome,BlueAirfieldBANDNum);
//	if (homeaf)
//		homeaf=FindNeighbour(homeaf,RedVetoedBANDNum);
//	if (!homeaf || (int)homeaf!=(int)fhome)
//		fhome=FindAirfield(fnat,region);
	if (!Persons2::ConvertPtrUID(fhome))
    	fhome=FindAirfield(0,0);

//	if (MissionBaseForm)
//	{
//		char*	tmp =  GetList(ENUM_UIDtitle).Translate(fhome);
//		if (tmp == NULL)
//		{
//			int text = MissionEditor->GetBandorShapeText(fhome);
//			LoadString(HInstance,text,buff,sizeof(buff));
//			MissionBaseForm->HomeBaseEdit->Text = buff;
//		}else
//			MissionBaseForm->HomeBaseEdit->Text = tmp;
//
//	}

//
//	if (fnat == (int)NAT_BLUE)
//		fnat =NAT_RED;
//	else
//		fnat = NAT_BLUE;
//	if (fnat == (int)NAT_RED)
//		homeaf=FindNeighbour(ehome,RedAirfieldBANDNum);
//	else
//		homeaf=FindNeighbour(ehome,BlueAirfieldBANDNum);
//	if (homeaf)
//		homeaf=FindNeighbour(homeaf,RedVetoedBANDNum);
//	if (!homeaf || (int)homeaf!=(int)ehome)
//		ehome=FindAirfield(fnat,region);

//now same as fhome...
//	if (MissionBaseForm)
  //	{
	//	char*	tmp =  GetList(ENUM_UIDtitle).Translate(ehome);
//		if (tmp == NULL)
  //		{
	//		int text = MissionEditor->GetBandorShapeText(ehome);
//			LoadString(HInstance,text,buff,sizeof(buff));
  //			MissionBaseForm->EnemyHomeBaseEdit->Text = buff;
    //
//		}else
  //			MissionBaseForm->EnemyHomeBaseEdit->Text = tmp;
    //	}

}



//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ddmmyyClick(TObject *)
{
	char buff[200];

		mmddyy->Checked = false;
		ddmmyy->Checked = true;
		LoadString(HInstance,TEXT_DDMMYY,buff,sizeof(buff));
		Date->Caption = buff;

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::mmddyyClick(TObject *)
{
	char buff[200];

		mmddyy->Checked = true;
		ddmmyy->Checked = false;
		LoadString(HInstance,TEXT_MMDDYY,buff,sizeof(buff));
		Date->Caption = buff;

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMOpenClick(TObject *)
{
				if (!currwp)
				{
					if (currtemplateitem)
							StaticForm->OpenForm();
					else
						ShowItemDialog(rightX,rightY);
				}else
				{
					WayPointForm->ShowWpDialog(rightX,rightY);
				}

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMDeleteClick(TObject *)
{
	if (!currwp)
	{
		if (currtemplateitem)
			MessageBeep(MB_ICONEXCLAMATION);	
		else
			AcItemForm->DeleteCurrTransItem();
	}else
	{
		WayPointForm->WpDelete();
	}
	MissionEditor->PaintRefresh();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMScaleClick(TObject *)
{
	ScaleX = rightX;
	ScaleY = rightY;
	MissionEditor->PaintRefresh();
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMMoveToClick(TObject *)
{

	MoveToEdit(rightX,rightY);


}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MoveToEdit(int X, int Y)
{


	info_itemS* I=*Persons2::ConvertPtrUID(currobj);
	info_waypoint* W=NULL;
	int 	x,y;
	if (I->Status.size>=MOBILESIZE)
	{
			x=I->World.X;
			y=I->World.Z;
			ScreenPosition(x,y);
			int deltax = x - X;
			int deltay = y - Y;


					deltax = MulScaleFactor(deltax);/// * PIXEL640 *ZOOMINITIAL/zoom;
///					deltax = deltax *(int)CONVERTTOSCRN_DIV/scrnconvert;
   ///					deltax = 100 * deltax;
					deltay = MulScaleFactor(deltay);/// *PIXEL640 * ZOOMINITIAL/zoom;
///					deltay = deltay *(int)CONVERTTOSCRN_DIV/scrnconvert;
   ///					deltay = 100 * deltay;




			UniqueID thiswp;
			info_grndgrp* t=*I;
			thiswp = t->wpref;
			do{
					W=*Persons2::ConvertPtrUID(thiswp);
					info_waypoint* P;
					if (	(W->target.Evaluate() ==ENABLE_COMPLEX_VAL)
						&&	(!W->events)
						)

					{
						W->World.X += deltax;
						W->World.Z -= deltay;

						W->position[0][0] = W->World.X;
						W->position[0][2] = W->World.Z;
						W->position.EvalW(W->World);
						if (W->prevwp)
						{
							P=*Persons2::ConvertPtrUID(W->prevwp);
							if (P->events)
							{
								WayPointForm->ReposEventWp(W->prevwp);
							}
						}
					}
					thiswp=W->nextwp;
			}while(thiswp);

	}
	MissionEditor->PaintRefresh();
	Editting = NOTEDITTING;

}
//---------------------------------------------------------------------------
bool __fastcall TMissionEditor::CopyEdit(int X, int Y)	//these coords ignored!!!
{
	int			mapx,mapy,mapz;

	Editting = NOTEDITTING;
	info_itemS* i=*Persons2::ConvertPtrUID(currobj);
	info_airgrp*	ac;
	UniqueIDBand	uidband;      
	uidband = Persons2::getbandfromUID(currobj);
//X, Y contains old screen position
//old object has been moved to new object position
//get the position for new object
	mapx=i->World.X;
	mapy=i->World.Y;
	mapz=i->World.Z;
	ScreenPosition(mapx,mapz);
	ShapeNum s = i->shape.Evaluate(2);
//put old object back
			GetDragLine(D_A,X,Y);		//get coords from drag structure
			if (AcTarget)
			{
				i->position.MakeRelWorldPos(AcTarget);
				i->position[1][0]=0;
				i->position[1][1]=0;
				i->position[1][2]=0;
				i->position.EvalW(i->World);
				i->World.X+=zoomiconsize;		
				i->World.Z-=zoomiconsize;		
			}                             
			else
			{
				i->position[0][0]=X;
				i->position[0][2]=Y;
				i->position.EvalW(i->World);
			}
			AcTarget=UID_Null;

	UniqueID  srcobj=currobj;
	int	avail_item = 0;
	int	reqd_item = 0;

	switch (uidband)
	{
		case	RedSAMBAND:
		{
			if (i->Status.size >= MOBILESIZE)
			{
				info_grndgrp* I=*i;
				avail_item = MissionEditor->RedTanksMax - MissionEditor->RedTanksCnt; 
				reqd_item = I->inform.Evaluate();
			}				
			break;
		}
		case	BlueSAMBAND:
		{
			if (i->Status.size >= MOBILESIZE)
			{
				info_grndgrp* I=*i;
				avail_item = MissionEditor->BlueTanksMax - MissionEditor->BlueTanksCnt;
				reqd_item = I->inform.Evaluate();
			}	
			break;
		}
		case	RedArmourBAND:
		{
			if (i->Status.size >= MOBILESIZE)
			{
				info_grndgrp* I=*i;
				avail_item = MissionEditor->RedGroundMobilesMax
										 - MissionEditor->RedGroundMobilesCnt;
				reqd_item = I->inform.Evaluate();
			}				
			break;
		}
		case	BlueArmourBAND:
		{
			if (i->Status.size >= MOBILESIZE)
			{
				info_grndgrp* I=*i;
				avail_item = MissionEditor->BlueGroundMobilesMax
										 - MissionEditor->BlueGroundMobilesMax;
				reqd_item = I->inform.Evaluate();
			}
			break;
		}
		case	RedAcBAND:
		{
			ac=*i;
			avail_item = MissionEditor->RedAcMax - MissionEditor->RedAcCnt;
//camp			if ((int)srcobj == (int)ActiveCampaign.PlayerAcuid)
//				reqd_item =  3;
//			else
				reqd_item = ac->inform.Evaluate();
			break;
		}
		case	BlueAcBAND:
		{
			ac=*i;
			avail_item = MissionEditor->BlueAcMax - MissionEditor->BlueAcCnt;
//camp			if ((int)srcobj == (int)ActiveCampaign.PlayerAcuid)
//				reqd_item =  3;
//			else
				reqd_item = ac->inform.Evaluate();
			break;
		}
	}


	if ( (WPsusedbycurrobj() > (WayPointMax - WayPointCnt))
		|| (	reqd_item > avail_item)
		)
	{
		MessageBeep(MB_ICONEXCLAMATION);
		return (false);

	}else
	{

		switch(i->Status.size)
		{
			case	AIRSTRUCSIZE:
				if (TopInitAc(mapx,mapy,mapz,uidband,uidband,s,s))
				{
						info_airgrp*	ac2=*Persons2::ConvertPtrUID(MissionEditor->currobj);

//camp					if ((int)srcobj == (int)ActiveCampaign.PlayerAcuid)
//						{
//							if ((int)ac->nat == (int)NAT_RED)
//								RedAcCnt -= 3;
//							else
//								BlueAcCnt -= 3;
//						}else
						{
							if ((int)ac->nat == (int)NAT_RED)
								RedAcCnt -= (int)ac2->inform.Evaluate();
							else
								BlueAcCnt -= (int)ac2->inform.Evaluate();
						}
					// copy over aircraft parameters
						ac2->skill = ac->skill.Clone();
						ac2->morale = ac->morale.Clone();
						ac2->character = ac->character.Clone();
						ac2->inwing = ac->inwing.Clone();
//						if ((int)srcobj == (int)ActiveCampaign.PlayerAcuid)
  //							ac2->inform = 3;
	//					else
							ac2->inform = ac->inform.Clone();
						ac2->form = ac->form.Clone();
						ac2->type = ac->type.Clone();
						ac2->nat = ac->nat.Clone();
						ac2->vel = ac->vel.Clone();
						ac2->homebase  = ac->homebase.Clone();
					   //	ac2->squadname = ac->squadname.Clone();
						ac2->squadron = ac->squadron;
						ac2->bombs     = ac->bombs.Clone();
						if ((int)ac->nat == (int)NAT_RED)
						   RedAcCnt += (int)ac2->inform.Evaluate();
					   else
							BlueAcCnt += (int)ac2->inform.Evaluate();
					CopyWayPoints(currobj,srcobj);
				}
			break;
			case	MOBILESIZE:
				if (TopInitMobile(mapx,mapz,uidband,uidband,s,s))
				{
					info_grndgrp*	mob2=*Persons2::ConvertPtrUID(MissionEditor->currobj);
					info_grndgrp*	mob=*i;
					mob2->inform = mob->inform.Clone();
					mob2->form = mob->form.Clone();
					mob2->type = mob->type.Clone();
					mob2->nat = mob->nat.Clone();
					mob2->vel = mob->vel.Clone();
					CopyWayPoints(currobj,srcobj);
				}
			break;
			case    ITEMSIZE:
				if (!i->events)
					TopInitStatic(mapx,0,mapz,uidband,uidband,s,s);
				else
				{
					if (TopInitStatic(mapx,0,mapz,LandscapeBAND,LandscapeBAND,EMPTY,EMPTY))
					{
						info_itemS* E=*Persons2::ConvertPtrUID(currobj);
						E->events=new info_event;
//	W->uniqueID->sector=FALSE;
					}
				}
			break;
		}
   }

}


//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FileMenuClick(TObject *)
{
	InMenu = true;
	WayPointForm->Close();
//	if (!MissionEditor->MissionMode && MissionEditor->MissionNew && !MissionEditor->MissionStarted)
//		NewMissionMenu->Enabled=false;
//	else
		NewMissionMenu->Enabled=true;

	if (currobj)
	{
		Move->Enabled = true;
		Copy->Enabled = true;
	}else
	{
		Move->Enabled = false;
		Copy->Enabled = false;
	}

	if 	(currtransientshape == NULL)
		currshape->Enabled = false;
	else
		currshape->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMCopyClick(TObject *)
{
	if (CopyEdit(rightX,rightY))
		MoveToEdit(rightX,rightY);

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::CopyClick(TObject *)
{
		Editting = EDITCOPY;

}
//---------------------------------------------------------------------------

void __fastcall TMissionEditor::MainMenuCopyEdit(int X,int Y)
{
	int srcx,srcy;
	if (currobj)
	{
		info_itemS* I=*Persons2::ConvertPtrUID(currobj);
//		if (I->Status.size>=MOBILESIZE)
//		{
			//srcx,srcy is where object was
				srcx=I->World.X;
				srcy=I->World.Z;
				ScreenPosition(srcx,srcy);
	
				//X,Y is where we want to move it to
				WorldPosition(X,Y);
		if (I->position[0].Evaluate() != ENABLE_COMPLEX_VAL)
		{
			AcTarget = I->position[0].Evaluate();
			I->position[0]= ENABLE_COMPLEX_VAL;		
		}		
		else
			AcTarget=UID_Null;
					
				I->position[0][0]=X;
				I->position[0][2]=Y;
				I->position.EvalW(I->World);
				//copy object and return old one 
				if (CopyEdit(srcx,srcy))
				 //move  waypoints
					MoveToEdit(srcx,srcy);
//		}         
	}	
}
//---------------------------------------------------------------------------

void __fastcall TMissionEditor::MainMenuMoveToEdit(int X,int Y)
{
	int srcx,srcy;
	if (currobj)
	{
		info_itemS* I=*Persons2::ConvertPtrUID(currobj);
		if (I->Status.size>=MOBILESIZE)
		{
			//srcx,srcy is where object was
				srcx=I->World.X;
				srcy=I->World.Z;
				ScreenPosition(srcx,srcy);
	
				//X,Y is where we want to move it to
				WorldPosition(X,Y);
		if (I->position[0].Evaluate() != ENABLE_COMPLEX_VAL)
		{
			AcTarget = I->position[0].Evaluate();
			I->position[0]= ENABLE_COMPLEX_VAL;		
		}		
		else
			AcTarget=UID_Null;
				
				
				I->position[0][0]=X;
				I->position[0][2]=Y;
				I->position.EvalW(I->World);
				//object is now where we want it so move all the waypoints
				MoveToEdit(srcx,srcy);
		}
	}
}

void __fastcall TMissionEditor::SB_Troops_FilterClick(TObject *)
{
	if (SB_Troops_Filter->Down == true)
	{
		MobilesVisible = MobilesVisible | (TROOPSVISIBLE);
		staticbands [RedTroopBANDNum].visible = true;
		staticbands [BlueTroopBANDNum].visible = true;
	}else
	{
		MobilesVisible = MobilesVisible & ~(TROOPSVISIBLE);
//		staticbands [RedGroundMobileBANDNum].visible = false;
//		staticbands [BlueGroundMobileBANDNum].visible = false;
	}
	PaintRefresh();


}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int __fastcall TMissionEditor::ValidEdit(TEdit *editbox)
{
	int value = 0;
   char	chknumber[50];

	if (!(editbox->Text.IsEmpty()))
   {
		editbox->GetTextBuf(chknumber,sizeof(chknumber));
	int i =0;
	bool isnum = true;
	while (chknumber[i] != 0)
	{
		if ((i == 0)
			&& ((chknumber[i] == '-')
				|| (chknumber[i] != '+')
			   )
			)   	
		{
			i++;
		}else
		{	
			if ((chknumber[i] <'0') || (chknumber[i] > '9')
				)
				isnum = false;
			i++;
		}	
	}
	if (isnum)
		value = StrToInt(editbox->Text);

   }
   editbox->Text = IntToStr(value);
   return(value);
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::CopyWayPoints(UniqueID destobj,UniqueID srcobj)
{
	info_waypoint*	destwp;
	info_waypoint*	srcwp;//=*Persons2::ConvertPtrUID(src->wpref);
	info_grndgrp* src=*Persons2::ConvertPtrUID(srcobj);
	info_grndgrp* dest=*Persons2::ConvertPtrUID(destobj);

	if ( WPsusedbycurrobj() > (WayPointMax - WayPointCnt))
	{
		MessageBeep(MB_ICONEXCLAMATION);	
	}else
	{
		if (dest->wpref)
		{
			destwp=*Persons2::ConvertPtrUID(dest->wpref);
			delete destwp;
			Persons2::delUID(dest->wpref);
		}
	
		//the first waypoint has been made already
	   //now make and copy waypoints
		UniqueID*	destur=(UniqueID*)&(UWord&)dest->wpref;
		UniqueID	srcu=src->wpref;
		UniqueID	lastwp=UID_Null;
	//	srcwp=*Persons2::ConvertPtrUID(srcu);
	
	   while(srcu)
	   {
			destwp=new info_waypoint;
			destwp->bfieldindex=bfieldbeingfilled;
			destwp->SGT = loadedsupergroup[supergroupbeingfilled].uid;

//DeadCode RDH 11Feb98 			destwp->uniqueID.sector=FALSE;
			destwp->prevwp=lastwp;
			lastwp =
				*destur=
					destwp->uniqueID.count=Persons2::assignuid(WayPointBAND);
			IncWayPointandCheck();	
			Persons2::tabulateUID(destwp);
			destwp->owner=destobj;
			destur=(UniqueID*)&(UWord&)destwp->nextwp;
	
			srcwp=*Persons2::ConvertPtrUID(srcu);
			destwp->uid   =srcwp->uid.Clone();
			destwp->etah  =srcwp->etah		.Clone();
			destwp->etam  =srcwp->etam      .Clone();
			destwp->etas  =srcwp->etas      .Clone();
			destwp->position=srcwp->position.Clone();
			destwp->vel   =srcwp->vel       .Clone();
			destwp->target=srcwp->target    .Clone();
			destwp->wpact =srcwp->wpact     .Clone();
			destwp->range =srcwp->range     .Clone();
			destwp->rangeispercent=srcwp->rangeispercent;
			destwp->World=srcwp->World;
			srcu=srcwp->nextwp;
	
	   }
	   *destur=UID_Null;
		MissionEditor->currwp = UID_Null;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ChangeTag(int index, int shapeL)
{
	SWord	shape=shapeL;

	switch(index)
	{
		case	AFLAKSHAPEGROUP:
		{
			if (currtransientshape ==  SB_A_AAA->Tag)		
				currtransientshape = shape;
			SB_A_AAA->Tag = shape;
			break;
		}
		case	CPFLAKSHAPEGROUP:
		{
			if (currtransientshape ==  SB_CP_AAA->Tag)		
				currtransientshape = shape;
			SB_CP_AAA->Tag = shape;  
			break;
		}
		case	ABATTSHAPEGROUP:
		{
			if (currtransientshape ==  SB_A_Battery->Tag)		
				currtransientshape = shape;
			SB_A_Battery->Tag = shape;      
			break;
		}
		case	CPBATTSHAPEGROUP:
		{
			if (currtransientshape ==  SB_CP_Battery->Tag)		
				currtransientshape = shape;
			SB_CP_Battery->Tag = shape;            
			break;
		}
		case	TRUCKSHAPEGROUP:
		{
			if (currtransientshape ==  SB_A_Truck->Tag)		
				currtransientshape = shape;
			if (currtransientshape ==  SB_CP_Truck->Tag)		
				currtransientshape = shape;
			SB_A_Truck->Tag = shape;             
			SB_CP_Truck->Tag = shape;
			break;
		}
		case	TROOPSHAPEGROUP:
		{
			if (currtransientshape ==  SB_A_Troops->Tag)		
				currtransientshape = shape;
			if (currtransientshape ==  SB_CP_Troops->Tag)		
				currtransientshape = shape;
			SB_A_Troops->Tag = shape;             
			SB_CP_Troops->Tag = shape;
			break;
		}
		case	TRAINSHAPEGROUP:
		{
			if (currtransientshape ==  SB_A_Train->Tag)		
				currtransientshape = shape;      
			if (currtransientshape ==  SB_CP_Train->Tag)		
				currtransientshape = shape;      
			SB_A_Train->Tag = shape;        
			SB_CP_Train->Tag = shape;
			break;
		}
		case	GROUPSHAPEGROUP:
		{
			if (currtransientshape ==  SB_Group->Tag)		
				currtransientshape = shape;      
			SB_Group->Tag = shape;          
			break;
		}
		case	SINGLESHAPEGROUP:
		{
			if (currtransientshape ==  SB_Single->Tag)		
				currtransientshape = shape;      
			SB_Single->Tag = shape;            
			break;
		}
		case		BTANKGROUP:
		{
			break;
		}
		case		GTANKGROUP:
		{
			break;
		}
		case		ABALLGROUP:
		{
			break;
		}
		case		GBALLGROUP:
		{
			break;
		}
	};
}

void __fastcall TMissionEditor::currshapeClick(TObject *)
{
		CurrShape->OpenForm();
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_WorldTemplateClick(TObject *)
{

//	if (SB_WorldTemplate->Down == true)
  //	{
	//	displayworldtemplateitems = true;
//
  //	}else
	//{
//		displayworldtemplateitems = false;
  //	}
	//PaintRefresh();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::HelpTopicsClick(TObject *)
{
	Application->HelpCommand(HELP_FINDER,0);

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::MakePlayerAc(bool option)
{
//	info_airgrp*	ac=*Persons2::ConvertPtrUID(MissionEditor->currobj);
//
//	if (option)
//	{
//		if ((int)ac->nat == (int)NAT_RED)
//	   		MissionEditor->RedAcCnt -=  (int)ac->inform.Evaluate();
//		else
//			MissionEditor->BlueAcCnt -=  (int)ac->inform.Evaluate();
//
//		ActiveCampaign.PlayerAcuid = currobj;
//		ac->inwing =
//			ac->inform = ENABLE_COMPLEX_VAL;
//		ac->form = ENABLE_COMPLEX_VAL;
//		ac->type = ENABLE_COMPLEX_VAL;
//		ac->shape = ENABLE_COMPLEX_VAL;
//
//	}else
//   {
//			if ((int)ac->nat == (int)NAT_RED)
//		   {
//				if (ac->type.Evaluate() == ENABLE_COMPLEX_VAL)
//					ac->type = PT_MIG15;
// //  			MissionEditor->RedAcCnt -=  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofsquadronac;
//   			MissionEditor->RedAcCnt +=  (int)ac->inform.Evaluate();
//			}else
//         {
//				if (ac->type.Evaluate() == ENABLE_COMPLEX_VAL)
//					ac->type = PT_F86E;
//  // 			MissionEditor->BlueAcCnt -=  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofsquadronac;
//   			MissionEditor->BlueAcCnt +=  (int)ac->inform.Evaluate();
//         }
//   }
//
}
//---------------------------------------------------------------------------
bool __fastcall TMissionEditor::PlayerAcPresent()
{
//camp	if (ActiveCampaign.PlayerAcuid)
		return(true);
//	else
//	{
//		PlayerAcNeededForm->ShowModal();
//		return(false);
//	}
}


//---------------------------------------------------------------------------
inline	int	operator	| (int i,ios::open_mode j)	{return int(i)|int(j);}
inline	int	operator	| (ios::open_mode i,ios::open_mode j)	{return int(i)|int(j);}
inline	int	operator	+ (ios::open_mode i,ios::open_mode j)	{return int(i)|int(j);}
inline	int	operator	+ (int i,ios::open_mode j)	{return int(i)|int(j);}
inline operator <=	(char i,TFileAttr j)	{return int(i)<=int(j);}
inline operator >=	(char i,TFileAttr j)	{return int(i)>=int(j);}
inline operator <=	(TFileAttr i,char j)	{return int(i)<=int(j);}
inline operator >=	(TFileAttr i,char j)	{return int(i)>=int(j);}
inline operator /	(TFileAttr i,char j)	{return int(i)/int(j);}
inline operator %	(TFileAttr i,char j)	{return int(i)%int(j);}




//---------------------------------------------------------------------------
void __fastcall TMissionEditor::EditMissionSrc1Click(TObject *)
{
	EditMissionSrc1->Checked=!EditMissionSrc1->Checked;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TMissionEditor::mixedClick(TObject *)
{
	char buff[200];

		Configure_Units = MIXED;
		imperial->Checked = false;
		metric->Checked = false;
	  mixed->Checked = true;
		LoadString(HInstance,TEXT_UNITSMIXED,buff,sizeof(buff));
		ConfigureUnits->Caption = buff;
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ResetTargetWayPoints()
{
	int	currwpback = currwp;		//backup currwp because we need to use it temporarily for PositionEvents
	for(int wpUID = (int)WayPointBAND;wpUID < (int)WayPointBANDEND;wpUID++)
	{
		info_waypoint* W=*Persons2::ConvertPtrUID((UniqueID)wpUID);
		if ((W)
			&&(W->target.Evaluate()!=ENABLE_COMPLEX_VAL)
			)
		{
			W->position.EvalW(W->World);
	  
			Coords3D& c=Persons2::ConvertPtrUID(UniqueID(W->target.Evaluate()))->World;
			W->World.X+=c.X+zoomiconsize;
			W->World.Z+=c.Z-zoomiconsize;
			currwp = wpUID;
			WayPointForm->PositionEvents();
			
		}
	}
	currwp = currwpback;
}                           



//---------------------------------------------------------------------------
bool  __fastcall TMissionEditor::TodaysTarget(UniqueID currUID)
{
	bool	retval;
//camp	if	((int)ActiveCampaign.mission[currmission].MainObjective ==  (int)currUID)
//			retval =  true;
//	else if ((int)ActiveCampaign.mission[currmission].SubObjective ==  (int)currUID)
//			retval =  true;
//	else if ((int)ActiveCampaign.mission[currmission].WP1 ==  (int)currUID)
//			retval =  true;
//	else if ((int)ActiveCampaign.mission[currmission].WP2 ==  (int)currUID)
//			retval =  true;
//	else if ((int)ActiveCampaign.mission[currmission].WP3 ==  (int)currUID)
//			retval =  true;
//	else             
			retval =  false;
	return (retval);		
}       
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::DrawTarget(UniqueID currUID,int X, int Y)
{
   int XL = X - ICONW/2;
   int YT = Y - ICONW/2;

   CurrCanvas->Pen(psSolid,(Graphics::TColor)0x00ffff,2);
   CurrCanvas->MoveTo(X,YT+ICONW);
   CurrCanvas->LineTo(X,YT);
   CurrCanvas->MoveTo(XL,Y);
   CurrCanvas->LineTo(XL+ICONW,Y);
//   CurrCanvas->Pen->Width = 2;

}

void __fastcall TMissionEditor::AboutClick(TObject *)
{
	AboutBox->ShowModal();
	
}
//---------------------------------------------------------------------------
int  __fastcall TMissionEditor::WPsusedbycurrobj()
{
	ItemBasePtr b=Persons2::ConvertPtrUID(currobj);
	if (b->Status.size<MOBILESIZE)
		return 0;
	info_grndgrp* 	G=*b;
	info_waypoint* 	W;
	UniqueID		wp=	G->wpref;
	int				i=0;	
	   while(wp)
	   {
			W=*Persons2::ConvertPtrUID(wp);
			i++;
			wp=W->nextwp;
	
	   }
	return (i);		
}
//---------------------------------------------------------------------------
void  __fastcall TMissionEditor::IncWayPointandCheck()
{	
	MissionEditor->WayPointCnt++;	
	DisableWPUsageifnecessary();
	
}																			 

void __fastcall TMissionEditor::FileExitClick(TObject *)
{
	Close();
}

void error_sayandquit( char	*error)	
{	
	Application->MessageBox(error,"Error",MB_OK+MB_ICONQUESTION);
	exit(1);
}
 
Error	&	Error::SayAndQuit(const char	*error, ... )
{
	va_list argptr;
	int cnt;
	char	buffer[1000];
	va_start(argptr, error);
	cnt = vsprintf(buffer, error, argptr);
	va_end(argptr);
	error_sayandquit(buffer);
	return(*this);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FormActivate(TObject *)
{
	MissionEditor->InMenu=true;
//	PaintBox->OnMouseDown = ImageMouseDown;
//	PaintBox->OnMouseUp = ImageMouseUp;
//	PaintBox->OnMouseMove = ImageMouseMove;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FormDeactivate(TObject *)
{
	if (WindowState != wsMaximized)
	{
		MissionEditor->InMenu=true;
//		PaintBox->OnMouseDown = NULL;
//		PaintBox->OnMouseUp = NULL;
//		PaintBox->OnMouseMove = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ItemCountClick(TObject *)
{
   	CountForm->OpenForm();
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SecretCancelClick(TObject *)
{
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::FormClose(TObject *Sender, TCloseAction &Action)
{
	
	if (!BfieldForm->QuerySaveChanges())
			Action=caNone;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMZoomInMapMaxClick(TObject *)
{
		oldzoom = zoom;
		zoom = ZOOMMAXMAP;

		SetZoomLabel();
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		CentreSetScrollBars(rightX,rightY);
		PaintRefresh();
	
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SMZoomInMaxClick(TObject *)
{
		oldzoom = zoom;
		zoom = ZOOMMAXABS;

		SetZoomLabel();
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		CentreSetScrollBars(rightX,rightY);
		PaintRefresh();
	   
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ViewZoomResetClick(TObject *)
{
		oldzoom = zoom;
		zoom = 200;

		SetZoomLabel();
		SetScrollBars();
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		PaintRefresh();
	
}

void __fastcall TMissionEditor::N7Click(TObject *)
{
	
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ZoomInMaxClick(TObject *)
{
		oldzoom = zoom;
		zoom = ZOOMMAXABS;

		SetZoomLabel();
		SetScrollBars();
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		PaintRefresh();
	
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ZoomInMapMaxClick(TObject *)
{
		oldzoom = zoom;
		zoom = ZOOMMAXMAP;

		SetZoomLabel();
		SetScrollBars();
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		PaintRefresh();
	
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::Zoom2Click(TObject *Sender)
{
		oldzoom = zoom;
		zoom = ((TComponent*)Sender)->Tag;

		SetZoomLabel();
		if (rightX>=0)
			CentreSetScrollBars(rightX,rightY);
		else	
			SetScrollBars();
		SetScrollBars();
		zoomiconsize=ZoomWorldIconSize();
		ResetTargetWayPoints();
		PaintRefresh();
	
}
//---------------------------------------------------------------------------
int	TMissionEditor::ZoomWorldIconSize()
{
	int	tlx=0,	//The icons are centred on the world position already,
		tly=0,	//
		brx=ICONW/2,	//I am considering a box around the mouse to be equivalent
		bry=ICONW/2;	//to a box around the icon

		WorldPosition(brx,bry);
		WorldPosition(tlx,tly);
		return	brx-tlx;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::UnLockTargetWayPoint(UniqueID uid)
{

	for(int wpUID = (int)WayPointBAND;wpUID < (int)WayPointBANDEND;wpUID++)
	{
		info_waypoint* W=*Persons2::ConvertPtrUID((UniqueID)wpUID);
		if ((W)
			&&(W->target.Evaluate()!=ENABLE_COMPLEX_VAL)
			)
		{
			if ((int)W->target.Evaluate() == (int)uid)
			{			
				Coords3D& c=Persons2::ConvertPtrUID(UniqueID(W->target.Evaluate()))->World;
				//fill pos
				W->position[0][0]=c.X;
				W->position[0][2]=c.Z;
				W->position.EvalW(W->World);
				W->target = ENABLE_COMPLEX_VAL;
				W->wpact =  IDS_TEXT_FLYWPACNOACTIONNO - IDS_TEXT_FLYWPACNOACTIONNO;
			}	
		}
	}
}


void __fastcall TMissionEditor::FilterSpeedBarMouseMove(TObject *Sender,
	TShiftState Shift, int X, int Y)
{
		rightX = -1;
		rightY = -1;
}
//---------------------------------------------------------------------------
								




void __fastcall TMissionEditor::SideGClick(TObject *Sender)
{
	int movedown=((TSpeedButton*)Sender)->Tag;
	int moveup=3-movedown;
	int propery=((TSpeedButton*)Sender)->Top;
	for (int i=topgrp->ControlCount-1;i>=0;i--)
		if (topgrp->Controls[i]->Tag==movedown)
			((TSpeedButton*)topgrp->Controls[i])->Top=100;
		else
		if (topgrp->Controls[i]->Tag==moveup)
			((TSpeedButton*)topgrp->Controls[i])->Top=propery;
											   
		
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::InfoPanel1Click(TObject *)
{
	if (InfoPanel1->Checked)
		StatusBar->Visible=InfoPanel1->Checked=false;
	else
		StatusBar->Visible=InfoPanel1->Checked=true;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::RefreshTimerTimer(TObject *Sender)
{
	RefreshTimer->Enabled=false;
	PaintRefresh();
}
void __fastcall TMissionEditor::ScrollBy(int DeltaX, int DeltaY)
{
	TForm::ScrollBy(DeltaX,DeltaY);
}



//---------------------------------------------------------------------------
void __fastcall TMissionEditor::Button1Click(TObject *Sender)
{
	char	buff[50];
    TButton* b=(TButton*)Sender;
    sprintf(buff,"%i,%i",b->Left,b->Top);
    b->Caption=buff;

}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SpeedButton1Click(TObject *Sender)
{

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_BfieldsClick(TObject *Sender)
{
		BfieldForm->OpenForm();
		PaintRefresh();
   StatusBar->Panels->Items[3]->Text = MissionEditor->loadedbfs[bfieldbeingfilled].name;

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_SuperGroupsClick(TObject *Sender)
{
		SuperGroups->OpenForm();
		PaintRefresh();
		SuperGroupStatusBar(loadedsupergroup[supergroupbeingfilled].uid);


}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_SaveallClick(TObject *Sender)
{
 //		savestrings("SNIP\tT_","\t=\t\"","\";\n",GetList(ENUM_UniqueID),"titles.tst",GetList(ENUM_UIDtitle));
   //		savestrings("SNIP\tD_","\t=\t\"","\";\n",GetList(ENUM_UniqueID),"descs.tst",GetList(ENUM_UIDdesc));

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::SB_SuperGroupFilterClick(TObject *Sender)
{
	PaintRefresh();

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::WipeBf(int index)
{
	UniqueID	currobj = MissionEditor->currobj;
	UniqueID       currUID;

	for(SWord i = 0; i < (int)MaxBANDNum;i++)
	{
		if (i!=WayPointBANDNum)
		{
			for(currUID = UniqueID(staticbands [i].startband);
				(((int)currUID) < ((int)staticbands [i].endband));
				currUID=(UniqueID)((int)currUID+1)
				)
			{
				info_base* J=*Persons2::ConvertPtrUID(currUID);
				if 	(J != NULL)
				{
					if (J->bfieldindex == index)
					{
						MissionEditor->currobj = currUID;
						if ((int)currUID == (int)currobj)
							currobj = UID_Null;
						AcItemForm->DeleteCurrTransItem();
					}
				}

			}
		}
	}
	MissionEditor->currobj = currobj;
}

//-----------------------------------------------------
void	__fastcall TMissionEditor::GenIdleTimerTimer(TObject*)
{
}

void __fastcall TMissionEditor::FindClick(TObject *Sender)
{
	NameListSel->ShowModal();
}
//---------------------------------------------------------------------------
