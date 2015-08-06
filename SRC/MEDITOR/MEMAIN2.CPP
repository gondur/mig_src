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


#define F_SOUNDS
#include <dos.h>
#include <direct.h>
//#include "eventwp.h"
//#include "test.h"
#include "direct.h"
//---------------------------------------------------------------------------

#include	"sysdefs.h"
#include	<INTABLE.h>
//#include "AcItem.h"
#include	"PreComp.h"
#include "GrndGrp.h"
//#include "eventwp.h"
//#include "Route.h"
//#include "piltlist.h"
#include	"bfform.h"
//#include "misscond.h"
//#include "missbase.h"
#include	"uniqueid.h"
#include "Waypoint.h"
//#include "MissText.h"
//#include "Static.h"

//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include	<vcl\clipbrd.hpp>
#include	"loadsave.h"
#pragma hdrstop
#include "text.h"
//#include "bstream.h"
#include	"shapenum.g"

//#include "meMain.h"
//#include "About.h"
//#include "mainevt.h"

//#include "CampText.h"
//#include "CampEdit.h"
#include "AcItem.h"

#include "strings.h"
#include "globals.h"
#include "player.h"
//#include "afselect.h"
//#include "SelTarg.h"
//#include "missobj.h"
//#include "misscond.h"
//#include "SimRun.h"
//#include "piltlist.h"
//#include "Aces.h"
//#include "respool.h"
//#include "InitCamp.h"
#include "confirm.h"
//#include "MissText.h"
#include	"fileman.h"
#include	"mymath.h"
#include	"MonoTxt2.h"

//#include "Reserves.h"

MonoText	Mono_Text;
//---------------------------------------------------------------------------
//#pragma resource "*.dfm"
 int bfieldbeingfilled=1;

//#include "Files.g"
//#include "persons2.h"
//#include "maps.h"
#include	"myangles.h"
#include	"makebf.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include 	"meMain.h"
#include	"mapload.h"
//#include	"mytime.h"

//#include	"readenum.h"
//#include "currshp.h"
//#include "choosebf.h"
//#include "playerac.h"
//#include "info.h"
//#include "flyinit.h"
//#include "sqinfo.h"
//#include "CampPara.h"
//#include "itemcnt.h"
#include "intable.h"
INTABLE(TMissionEditor::GridConsts);
LevelDrop Level_Drop[4];
//---------------------------------------------------------------------------

static STARTUPINFO sui=
{
	sizeof(STARTUPINFO),
	NULL,NULL,                  //res/desk
	"Texture loading... please ignore",	//title
	0,0,						//x,y
	400,200,					//w,h
	40,20,                      //tw,th
	0,							//colour
	STARTF_USECOUNTCHARS+STARTF_USEPOSITION+STARTF_USESIZE+STARTF_USESHOWWINDOW,		//flags
	SW_SHOWMINIMIZED,
	0,
	NULL,
	0,0,0
};
static PROCESS_INFORMATION	pi;

//---------------------------------------------------------------------------
extern	GlobalsInfo	GR_MainObjective,GR_SubObjective,GR_WP1,GR_WP2,GR_WP3;
void	TMissionEditor::AccumulateLoadedCount()
{
	SetMaxMobCnt();
//	ActiveCampaign.mission[currmission].MainObjective=GR_MainObjective.value;
//	ActiveCampaign.mission[currmission].SubObjective=GR_SubObjective.value;
//	ActiveCampaign.mission[currmission].WP1=GR_WP1.value;
//	ActiveCampaign.mission[currmission].WP2=GR_WP2.value;
//	ActiveCampaign.mission[currmission].WP3=GR_WP3.value;

	for (UniqueID i=UID_Null;(int)i<(int)IllegalSepID;i=UniqueID((int)i+1))
	{
		ItemBasePtr B=*Persons2::ConvertPtrUID(i);
		info_event* E=NULL;
		if (B)
			switch (B->Status.size)
			{
			case WAYPOINTSIZE:
			{
				E=((info_waypoint*)*B)->events;
				MissionEditor->WayPointCnt++;
			}
			break;
			case ITEMSIZE:
				E=((info_itemS*)*B)->events;
				switch (Persons2::getbandfromUID(i))
				{
				case	RedAcBAND:				MissionEditor->RedAcCnt++;				break;
				case	BlueAcBAND:				MissionEditor->BlueAcCnt++;				break;
				case	RedSAMBAND:				MissionEditor->RedTanksCnt++;			break;
				case	BlueSAMBAND:			MissionEditor->BlueTanksCnt++;			break;
				case	RedArmourBAND:	MissionEditor->RedGroundMobilesCnt++;	break;
				case	BlueArmourBAND:	MissionEditor->BlueGroundMobilesCnt++;	break;
				}
			break;
			case AIRSTRUCSIZE:
			case MOBILESIZE:
			{
				info_grndgrp* G=*B;
				int count=G->inform.Evaluate();
				Persons2::FixupRouteOwner(G->uniqueID.count,G->wpref);	//fix wp-->item refs
				Persons2::FixupRouteOwner(G->uniqueID.count,G->wpref);	//fix wp-->wp refs
				if (count==ENABLE_COMPLEX_VAL)
					count=0;				//rdh
				switch (Persons2::getbandfromUID(i))
				{
				case	RedAcBAND:	
				{
//							if ((int)i != (int)ActiveCampaign.PlayerAcuid)
								MissionEditor->RedAcCnt+=count;
							break;
				}
				case	BlueAcBAND:
				{
//							if ((int)i != (int)ActiveCampaign.PlayerAcuid)
								MissionEditor->BlueAcCnt+=count;
							break;
				}
				case	RedSAMBAND:				MissionEditor->RedTanksCnt+=count;			break;
				case	BlueSAMBAND:			MissionEditor->BlueTanksCnt+=count;			break;
				case	RedArmourBAND:	MissionEditor->RedGroundMobilesCnt+=count;	break;
				case	BlueArmourBAND:	MissionEditor->BlueGroundMobilesCnt+=count;	break;
				}
				E=G->events;
			}
			break;
			}
//events		while (E)    //RAC,BAC,WP,ST,RGR,BGR;
//events		{
//events			ChooseBfForm->FillEventFromBfList(E);
//events			MissionEditor->RedAcMax				-=Persons2::bfdesc->RAC;
//events			MissionEditor->BlueAcMax			-=Persons2::bfdesc->BAC;
//events			MissionEditor->RedGroundMobilesMax	-=Persons2::bfdesc->RGR;
//events			MissionEditor->BlueGroundMobilesMax	-=Persons2::bfdesc->BGR;
//events			MissionEditor->WayPointMax			-=Persons2::bfdesc->WP;
//events			E=E->next;
//events		}
	}
	//AcSpdButtonState();
	//MobileSpdButtonState();
		DisableWPUsageifnecessary();	//rdh
}
//---------------------------------------------------------------------------
bool	TMissionEditor::CheckObjectives()
{	//returns false if any cleared.
	bool rv=true;
//	if (!Persons2::ConvertPtrUID(ActiveCampaign.mission[currmission].MainObjective))
//		rv=ActiveCampaign.mission[currmission].MainObjective=UID_Null;
//	if (!Persons2::ConvertPtrUID(ActiveCampaign.mission[currmission].SubObjective))
//		rv=ActiveCampaign.mission[currmission].SubObjective=UID_Null;
//	if (!Persons2::ConvertPtrUID(ActiveCampaign.mission[currmission].WP1))
//		rv=ActiveCampaign.mission[currmission].WP1=UID_Null;
//	if (!Persons2::ConvertPtrUID(ActiveCampaign.mission[currmission].WP2))
//		rv=ActiveCampaign.mission[currmission].WP2=UID_Null;
//	if (!Persons2::ConvertPtrUID(ActiveCampaign.mission[currmission].WP3))
//		rv=ActiveCampaign.mission[currmission].WP3=UID_Null;
	return	rv;
}
//---------------------------------------------------------------------------
void  __fastcall TMissionEditor::DisableWPUsageifnecessary()
{

	if ( WayPointCnt >= WayPointMax)
	{
		ResetSpeedButtons();
		if (	(SB_CP_Aircraft->Down == true)
				||	(SB_A_Aircraft->Down== true)
				||	(SB_CP_Train->Down== true)
				||	(SB_A_Train->Down== true)
				||	(SB_CP_Truck->Down== true)
				||	(SB_A_Truck->Down== true)
				||	(SB_A_Troops->Down== true)
				||	(SB_CP_Troops->Down== true)
				||	(SB_CP_Tank->Down== true)
				||	(SB_A_Tank->Down== true)
				||	(SB_Route->Down== true)
			)
			{	  			
				SB_Arrow->Down = true;
				currtransient = T_NONE;
				currtransientshape = NULL;
			}
		SB_Route->Enabled = false;
		SB_CP_Aircraft->Enabled = false;
		SB_A_Aircraft->Enabled = false;
		SB_CP_Train->Enabled = false;
		SB_CP_Truck->Enabled = false;
		SB_CP_Troops->Enabled = false;
		SB_A_Train->Enabled = false;
		SB_A_Truck->Enabled = false;
		SB_A_Troops->Enabled = false;
		SB_CP_Tank->Enabled = false;
		SB_A_Tank->Enabled = false;
		if (WayPointForm)
		{
			WayPointForm->WPBefore->Enabled = false;
			WayPointForm->WPAfter->Enabled = false;
		}
	}
	else
	{
		SB_Route->Enabled = true;
//		SB_CP_Aircraft->Enabled = true;
//		SB_A_Aircraft->Enabled = true;
	   AcSpdButtonState();
		if (WayPointForm)
		{
			WayPointForm->WPBefore->Enabled = true;
			WayPointForm->WPAfter->Enabled = true;
		}
		MobileSpdButtonState();
	}

	UniqueID uid;
	
	uid = Persons2::findavailuid(BlueGICBAND);
	if ((int)UID_Null == (int)uid)
	{
		SB_A_Balloon->Enabled = false;
		SB_A_Balloon_T->Enabled = false;
	}
	else
	{
		SB_A_Balloon->Enabled = true;
		SB_A_Balloon_T->Enabled = true;
	}
	uid = Persons2::findavailuid(RedGICBAND);
	if ((int)UID_Null == (int)uid)
	{
		SB_CP_Balloon->Enabled = false;
		SB_CP_Balloon_T->Enabled = false;
	}else
	{
		SB_CP_Balloon->Enabled = true;
		SB_CP_Balloon_T->Enabled = true;
	}
	 uid = Persons2::findavailuid(RedMilitaryBAND);
	if ((int)UID_Null == (int)uid)
	{
		SB_CP_Battery->Enabled = false;
		SB_CP_Battery_T->Enabled = false;
	}else
	{
		SB_CP_Battery->Enabled = true;
		SB_CP_Battery_T->Enabled = true;
	}
	 uid = Persons2::findavailuid(BlueMilitaryBAND);
	if ((int)UID_Null == (int)uid)
	{
		SB_A_Battery->Enabled = false;
		SB_A_Battery_T->Enabled = false;
	}else
	{
		SB_A_Battery->Enabled = true;
		SB_A_Battery_T->Enabled = true;
	}

	 uid = Persons2::findavailuid(RedAAASiteBAND);
	if ((int)UID_Null == (int)uid)
	{
		SB_CP_AAA->Enabled = false;
		SB_CP_AAA_T->Enabled = false;
	}else
	{
		SB_CP_AAA->Enabled = true;
		SB_CP_AAA_T->Enabled = true;
	}
	 uid = Persons2::findavailuid(BlueAAASiteBAND);
	if ((int)UID_Null == (int)uid)
	{
		SB_A_AAA->Enabled = false;
		SB_A_AAA_T->Enabled = false;
	}else
	{
		SB_A_AAA->Enabled = true;
		SB_A_AAA_T->Enabled = true;
	}

	 uid = Persons2::findavailuid(LandscapeBAND);
	if ((int)UID_Null == (int)uid)
	{
		SB_Event->Enabled = false;
		SB_Single->Enabled = false;
		SB_Event_T->Enabled = false;
		SB_Single_T->Enabled = false;
	}
	else
	{
		SB_Event->Enabled = true;
		SB_Single->Enabled = true;
		SB_Event_T->Enabled = true;
		SB_Single_T->Enabled = true;
	}

	 uid = Persons2::findavailuid(MissileBAND);
	if ((int)UID_Null == (int)uid)
	{
		SB_Group->Enabled = false;
		SB_Group_T->Enabled = false;
	}
	else
	{
		SB_Group->Enabled = true;
		SB_Group_T->Enabled = true;
	}



	Invalidate();
}
//---------------------------------------------------------------------------
int  __fastcall TMissionEditor::IncMobileCounters(UniqueIDBand  uidband,int cnt)
{
	if	((int)uidband == (int)BlueArmourBAND)
	{
		if (((int)cnt+BlueGroundMobilesCnt) > BlueGroundMobilesMax)
			cnt = BlueGroundMobilesMax - BlueGroundMobilesCnt;
		BlueGroundMobilesCnt += cnt;
	}else if ((int)uidband == (int)RedArmourBAND)
	{
		if (((int)cnt+RedGroundMobilesCnt) > RedGroundMobilesMax)
			cnt = RedGroundMobilesMax - RedGroundMobilesCnt;
		RedGroundMobilesCnt += (int)cnt;
	}else if ((int)uidband == (int)BlueSAMBAND)
	{
		if (((int)cnt+BlueTanksCnt) > BlueTanksMax)
			cnt = BlueTanksMax - BlueTanksCnt;
		BlueTanksCnt += (int)cnt;
	}else if ((int)uidband == (int)RedSAMBAND)
	{
		if (((int)cnt+RedTanksCnt) > RedTanksMax)
			cnt = RedTanksMax - RedTanksCnt;
		RedTanksCnt += (int)cnt;
	}
	return (cnt);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
 void __fastcall TMissionEditor::InitCampaign()
 {
//camp	ActiveCampaign.mission[currmission].region = 0;
//	ActiveCampaign.title[0] = 0;
	currmission = 0;
//	CampaignStarted=false;
//camp	MissionEditor->ActiveCampaign.mission[currmission].era = 1;
//	ActiveCampaign.success.airkills = 0;
//	ActiveCampaign.success.groundkills = 0;
//	ActiveCampaign.success.airlosses = 0;
//	ActiveCampaign.success.groundlosses = 0;
//	ActiveCampaign.success.acescreated = 0;
//	ActiveCampaign.success.totalsquadkills = 0;
//	ActiveCampaign.success.PlayerRank = 0;
//	ActiveCampaign.initial.airkills = 0;
//	ActiveCampaign.initial.groundkills = 0;
//	ActiveCampaign.initial.airlosses = 0;
//	ActiveCampaign.initial.groundlosses = 0;
//	ActiveCampaign.initial.acescreated = 0;
//	ActiveCampaign.initial.totalsquadkills = 0;
//	ActiveCampaign.initial.PlayerRank = 0;
//	ActiveCampaign.successcriteria = SC_AIRKILLS;


 }

 void __fastcall TMissionEditor:: SetMaxMobCnt()
 {

	RedAcMax  = (int)Persons2::uidbandmax[RedAcBANDNum] - (int)Persons2::uidbandbase[RedAcBANDNum]-1;
	BlueAcMax = (int)Persons2::uidbandmax[BlueAcBANDNum] - (int)Persons2::uidbandbase[BlueAcBANDNum]-1;
//camp	if ((int)ActiveCampaign.mission[currmission].PlayerNationality == (int)NAT_RED)
//	{
		RedAcMax -=	MAXACINPLAYERSQUAD;
//camp	}else
//	{
//		BlueAcMax -=	MAXACINPLAYERSQUAD;
//	}
   BlueAcCnt = 0;
   RedAcCnt = 0;
   RedGroundMobilesCnt = 0;
   BlueGroundMobilesCnt = 0;
   RedTanksCnt = 0;
   BlueTanksCnt = 0;
   WayPointCnt = 0;
   RedGroundMobilesMax  = 32;//(int)Persons2::uidbandmax[RedGroundMobileBANDNum] - (int)Persons2::uidbandbase[RedGroundMobileBANDNum]-1;
   BlueGroundMobilesMax = 32;//(int)Persons2::uidbandmax[BlueGroundMobileBANDNum] - (int)Persons2::uidbandbase[BlueGroundMobileBANDNum]-1;
   WayPointMax = (int)Persons2::uidbandmax[WayPointBANDNum] - (int)Persons2::uidbandbase[WayPointBANDNum]-1;
   RedTanksMax  =  (int)Persons2::uidbandmax[RedSAMBANDNum] - (int)Persons2::uidbandbase[RedSAMBANDNum]-1;
   BlueTanksMax =  (int)Persons2::uidbandmax[BlueSAMBANDNum] - (int)Persons2::uidbandbase[BlueSAMBANDNum]-1;
   //rdh22AcSpdButtonState();
   //rdh22MobileSpdButtonState();
   DisableWPUsageifnecessary();	//rdh22
 }
//---------------------------------------------------------------------------
//DeadCode JIM 31May98 void __fastcall TMissionEditor_was_NewWorld()		//FileNum	file,int region)
//DeadCode JIM 31May98 {
//DeadCode JIM 31May98 //need to delete old world even if using same world as last time
//DeadCode JIM 31May98 //	if (WorldFile != file)
//DeadCode JIM 31May98 //	{
//DeadCode JIM 31May98 //	scrnconvert = 5803;
//DeadCode JIM 31May98 //		if (WorldFile != FIL_NULL)
//DeadCode JIM 31May98 //			DeleteWorld();
//DeadCode JIM 31May98 		FileNum	file=FIL_MainWorld;
//DeadCode JIM 31May98 //        int region
//DeadCode JIM 31May98 
//DeadCode JIM 31May98         Persons2	Persons_2(NULL,NULL);
//DeadCode JIM 31May98 		Persons_2.currbfindex=0;
//DeadCode JIM 31May98 		Persons_2.LoadSetPiece(NULL,file);
//DeadCode JIM 31May98 		Persons_2.currbfindex=1;
//DeadCode JIM 31May98 
//DeadCode JIM 31May98 //			MapOriginX = SOMMEMAPORIGINX * 100;					//RDH 12Feb98
//DeadCode JIM 31May98   //			MapOriginY = SOMMEMAPORIGINY * 100;
//DeadCode JIM 31May98 //DeadCode RDH 12Feb98 			MapWidth = SOMMEMAPWIDTH;
//DeadCode JIM 31May98 //			MapHeight = SOMMEMAPHEIGHT * (int)CONVERTTOSCRN_DIV;
//DeadCode JIM 31May98   //			MapHeight = MapHeight / scrnconvert;
//DeadCode JIM 31May98 	//		MapHeight = MapHeight * 100;
//DeadCode JIM 31May98 	  //		MapOriginY = MapOriginY + MapHeight;
//DeadCode JIM 31May98 //camp			if ((int)ActiveCampaign.mission[currmission].PlayerNationality == (int)NAT_BLUE)
//DeadCode JIM 31May98 //			{
//DeadCode JIM 31May98 //				ActiveCampaign.mission[currmission].PlayerHomeBase = UID_ToAlBoiryStMartin;
//DeadCode JIM 31May98 //				ActiveCampaign.mission[currmission].EnemyHomeBase =  UID_ToCpRoucourt;
//DeadCode JIM 31May98 //			}
//DeadCode JIM 31May98 //			else
//DeadCode JIM 31May98 //			{
//DeadCode JIM 31May98 //				ActiveCampaign.mission[currmission].EnemyHomeBase = UID_ToAlBoiryStMartin;
//DeadCode JIM 31May98 //				ActiveCampaign.mission[currmission].PlayerHomeBase =  UID_ToCpRoucourt;
//DeadCode JIM 31May98 //			}
//DeadCode JIM 31May98 //		if (Visible)
//DeadCode JIM 31May98   //			SetScrollBars();
//DeadCode JIM 31May98 //		maptopx = 0;
//DeadCode JIM 31May98  //		maptopy = MapHeight;
//DeadCode JIM 31May98 //		WorldFile = file;
//DeadCode JIM 31May98    //		CheckHomeBase ();
//DeadCode JIM 31May98 	   //AcSpdButtonState();
//DeadCode JIM 31May98 	   //MobileSpdButtonState();
//DeadCode JIM 31May98 	 //	DisableWPUsageifnecessary();	//rdh
//DeadCode JIM 31May98 
//DeadCode JIM 31May98 //	}
//DeadCode JIM 31May98 }

///////////////////////////////////////////////////////////////////////////////
//void	TMissionEditor::OpenMission(AnsiString name,int bfindex)
//{
////	if (!MissionBaseForm->OfferSaveCurrent())
//  //		return;
//    Persons2	Persons_2(NULL,NULL);
//	Persons_2.justscanning=Persons2::SCANNAMES;
//	char fname[20];
//	strcpy(fname,name.c_str());
////	strcpy(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].name,fname);
//	strcat(fname,".BF");
//	FileNum f=FILEMAN.fakefile(FIL_USERMISSION1,fname);
////		FileLoadSave->DefaultDirectory();
//		(UWord&)Persons_2.bfdesc->description[0]=0;
//	//Persons_2.bfdesc->description[0]=0;
//	Persons_2.currbfindex=bfindex;
//	Persons_2.LoadSubPiece(NULL,f);
//	Persons_2.justscanning=Persons2::LOAD;
////DeadCode DAW 06Sep97 	ActiveCampaign.mission[currmission].era=ActiveCampaign.nextera;
//
////camp	ActiveCampaign.mission[currmission].region=ActiveCampaign.nextregion;
////	strcpy(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].title,
////			Persons_2.bfdesc->title);
////	strcpy(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].missiontext,
////			Persons_2.bfdesc->description);
////	strcpy(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].newstext,
////			Persons_2.bfdesc->news);
////	FindWorldTemplateFiles(ActiveCampaign.mission[currmission].region);
////	ActiveCampaign.mission[currmission].era=0;//ConvertFileToEra(ActiveCampaign.nextera);//DAW 06Sep97
//	MissionEditor->NewWorld();
////			ChooseBfForm->BFields[ChooseBfForm->AvailBf[ActiveCampaign.mission[currmission].era]].file,
//  //			ActiveCampaign.mission[currmission].region);
//	Persons_2.LoadSubPiece(NULL,f);
//	AccumulateLoadedCount();
//	CheckObjectives();
//	MissionNew=false;
//	MissionEdited=false;
//	MissionStarted=true;
////	SetCaption(MissionEditor->ActiveCampaign.name,ActiveCampaign.mission[currmission].name);
////	PaintBox->Invalidate();
//}
//---------------------------------------------------------------------------
//void	TMissionEditor::NewMission(AnsiString name,AnsiString title,int bfindex)
//{
////	if (!MissionBaseForm->OfferSaveCurrent())
//  //		return;
//	NewLoadedBf(name);
//	InitMission();
////camp	strcpy(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].name,name.c_str());
////	strcpy(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].title,title.c_str());
////	FindWorldTemplateFiles(ActiveCampaign.mission[currmission].region);
////	MissionEditor->NewWorld(
////			ChooseBfForm->BFields[ChooseBfForm->AvailBf[ActiveCampaign.mission[currmission].era]].file,
////			ActiveCampaign.mission[currmission].region);
//	MissionNew=true;
//	MissionStarted=false;
//	MissionEdited=false;
//	PaintRefresh();
//	MissionBaseForm->OpenNewMiss();
////	SetCaption(MissionEditor->ActiveCampaign.name,ActiveCampaign.mission[currmission].name);
//}
//---------------------------------------------------------------------------
//void	TMissionEditor::OpenMissGrp(AnsiString name)
//{
//	if (!MissionBaseForm->OfferSaveCurrent())
//		return;
//	char* f=FILEMAN.namenumberedfile(DIR_USEROBJ);
//	f[strlen(f)-7]=0;
//	char dir[20];
//	dir[0]='M';
//	char* dirp=dir+1;
//	strcpy(dirp,name.c_str());
//	if (dirp[0]!='M' && dirp[0]!='m')
//		if (strcmpi(dirp,"DEFAULT"))
//			dirp--;
//	strcat(f,dirp);
//	FILEMAN.fakedir(FIL_USERMISSION1,f);
//	strcpy(ActiveCampaign.name,dirp);
//	SetMissionMode(true);
//	int rv;
//	bool	toggle=false;
//	name="";
//	AnsiString title="";
//	do{
//		f=FILEMAN.namenumberedfile(FILEMAN.fakefile(FIL_USERMISSION1,""));
//		if (toggle)
//			rv=FileLoadSave->ShowModal(f,name,title,FM_NewFile);
//		else
//			rv=FileLoadSave->ShowModal(f,name,title,FM_OpenFile);
//		toggle=!toggle;
//	}while (rv==mrCancel);
//
//	switch (rv)
//	{
//	case	mrYes:
//		OpenMission(name,bfieldbeingfilled);
//	return;
//	case	mrOk:
//		NewMission(name,title,bfieldbeingfilled);
//	return;
//	}
//}
//---------------------------------------------------------------------------
void	TMissionEditor::QuickDisassemble(char* line)
{
//DeadCode JIM 31May98 			char* name=line+strlen(line);
//DeadCode JIM 31May98 			while (*name!='\\')
//DeadCode JIM 31May98 				name--;
//DeadCode JIM 31May98 			*name++=0;
//DeadCode JIM 31May98 			char* path=FILEMAN.namenumberedfile(FILEMAN.fakefile(DIR_USEROBJ,""));
//DeadCode JIM 31May98 			strcat(path,line);
//DeadCode JIM 31May98 			FILEMAN.fakedir(FIL_USERMISSION1,path);
//DeadCode JIM 31May98 			FileNum f=FILEMAN.fakefile(FIL_USERMISSION1,name);
//DeadCode JIM 31May98 		Persons2	Persons_2(NULL,NULL);
//DeadCode JIM 31May98 		(UWord&)Persons_2.bfdesc->description[0]=0;
//DeadCode JIM 31May98         Persons_2.currbfindex=0;
//DeadCode JIM 31May98 		Persons_2.justscanning=Persons2::SCANNAMES;
//DeadCode JIM 31May98 		Persons_2.LoadSubPiece(NULL,f);
//DeadCode JIM 31May98 		Persons_2.justscanning=Persons2::LOAD;
//DeadCode JIM 31May98 //DeadCode DAW 06Sep97 	ActiveCampaign.mission[currmission].era=ActiveCampaign.nextera;
//DeadCode JIM 31May98 //camp		ActiveCampaign.mission[currmission].region=ActiveCampaign.nextregion;
//DeadCode JIM 31May98 //		strcpy(MissionEditor->ActiveCampaign.mission[0].title,
//DeadCode JIM 31May98 //				Persons_2.bfdesc->title);
//DeadCode JIM 31May98 //		strcpy(MissionEditor->ActiveCampaign.mission[0].missiontext,
//DeadCode JIM 31May98 //				Persons_2.bfdesc->description);
//DeadCode JIM 31May98 //		strcpy(MissionEditor->ActiveCampaign.mission[0].newstext,
//DeadCode JIM 31May98 //				Persons_2.bfdesc->news);
//DeadCode JIM 31May98 //		FindWorldTemplateFiles(ActiveCampaign.mission[0].region);
//DeadCode JIM 31May98 //		ActiveCampaign.mission[0].era=0;//ConvertFileToEra(ActiveCampaign.nextera);//DAW 06Sep97
//DeadCode JIM 31May98 //		MissionEditor->NewWorld();
//DeadCode JIM 31May98 //				ChooseBfForm->BFields[ChooseBfForm->AvailBf[ActiveCampaign.mission[currmission].era]].file,
//DeadCode JIM 31May98   //				ActiveCampaign.mission[currmission].region);
//DeadCode JIM 31May98 		Persons_2.LoadSubPiece(NULL,f);
//DeadCode JIM 31May98 		path=name;
//DeadCode JIM 31May98 		while (*path!='.')
//DeadCode JIM 31May98 			path++;
//DeadCode JIM 31May98 		*path=0;
//DeadCode JIM 31May98 //camp		strcpy(MissionEditor->ActiveCampaign.mission[0].name,name);
//DeadCode JIM 31May98 		AccumulateLoadedCount();
//DeadCode JIM 31May98 		CheckObjectives();
//DeadCode JIM 31May98 //			Persons_2.loadingmainworld=FALSE;
//DeadCode JIM 31May98 
//DeadCode JIM 31May98 //			Persons_2.SaveBF(line,
//DeadCode JIM 31May98   //								name,
//DeadCode JIM 31May98 	//							ActiveCampaign.mission[currmission].title,
//DeadCode JIM 31May98 	  //							ActiveCampaign.mission[currmission].missiontext,
//DeadCode JIM 31May98 		//						ActiveCampaign.mission[currmission].newstext);
}
//---------------------------------------------------------------------------
//void	TMissionEditor::NewMissGrp(AnsiString name,AnsiString Title)
//{
//	if (!MissionBaseForm->OfferSaveCurrent())
//		return;
//
//	char* f=FILEMAN.namenumberedfile(DIR_USEROBJ);
//	f[strlen(f)-7]=0;
//	char dir[20];
//	dir[0]='M';
//	char* dirp=dir+1;
//	strcpy(dirp,name.c_str());
//	if (dirp[0]!='M' && dirp[0]!='m')
//		if (strcmpi(dirp,"DEFAULT"))
//			dirp--;
//	strcat(f,dirp);
//	_mkdir(f);
//	FILEMAN.fakedir(FIL_USERMISSION1,f);
//	FILEMAN.fakefile(FIL_USERMISSION1,"");
//	strcpy(ActiveCampaign.name,dirp);
//	strcpy(ActiveCampaign.title,Title.c_str());
//	MissionStarted = false;
//	MissionNew = true;
//	SetMissionMode(true);
//	InitCampaign();
//
//	FindWorldTemplateFiles(ActiveCampaign.mission[currmission].region);
//
//	MissionEditor->NewWorld();
////		ChooseBfForm->BFields[ChooseBfForm->AvailBf[ActiveCampaign.mission[currmission].era]].file,
//  //		ActiveCampaign.mission[currmission].region);
//	InitMission();
//
//	ActiveCampaign.filelist.Clear();
//	MissionBaseForm->OpenNewMiss();
//}
//---------------------------------------------------------------------------
//campvoid	TMissionEditor::OpenCampaign(AnsiString name)
//camp{
//camp	Persons2	Persons_2(NULL,NULL);
//camp	if (!MissionBaseForm->OfferSaveCurrent())
//camp		return;
//camp	InitCampaign();
//camp	InitMission();
//camp	char* f=FILEMAN.namenumberedfile(DIR_USEROBJ);
//camp	f[strlen(f)-7]=0;
//camp	char	dirname[20];
//camp	dirname[0]='C';
//camp	strcpy(dirname+1,name.c_str());
//camp	strcat(f,dirname);
//camp	strcpy(MissionEditor->ActiveCampaign.name,dirname);
//camp	SetMissionMode(false);
//camp	FILEMAN.fakedir(FIL_USERMISSION1,f);
//camp	f=FILEMAN.namenumberedfile(dirnum(dirnum(FIL_USERMISSION1)));
//camp	FILE*F=fopen(f,"rb");
//camp	fread(	&ActiveCampaign.filelist.data,
//camp			ActiveCampaign.filelist.maxfiles,
//camp			ActiveCampaign.filelist.charsperfile,
//camp			F);
//camp	fclose(F);
//camp	f=FILEMAN.namenumberedfile(FileNum(((int)FIL_USERMISSION1&0xff00)+(int)ActiveCampaign.filelist.maxfiles-2));
//camp	F=fopen(f,"rb");
//camp	fread(&ActiveCampaign,sizeof(MeCampaignTexts),1,F);
//camp	fclose(F);
//camp	PilotForm->LoadPilots(FILEMAN.namenumberedfile(FileNum(((int)FIL_USERMISSION1&0xff00)+(int)ActiveCampaign.filelist.maxfiles-1)));
//camp
//camp	SetMissionMode(false);
//camp
//camp//	Persons_2.justscanning=Persons_2.SCANNAMES;
//camp	for (int i=ActiveCampaign.totaldays;--i>=0;)
//camp	{
//camp		(UWord&)Persons_2.bfdesc->description[0]=0;
//camp		Persons_2.LoadSubPiece(NULL,FileNum(int(FIL_USERMISSION1)+i),Persons2::SCANNAMES);
//camp		strcpy(ActiveCampaign.mission[i].title,Persons_2.bfdesc->title);
//camp		strcpy(ActiveCampaign.mission[i].missiontext,Persons_2.bfdesc->description);
//camp		strcpy(ActiveCampaign.mission[i].newstext,Persons_2.bfdesc->news);
//camp		{
//camp			int j=0;
//camp			for (;ActiveCampaign.filelist[i+1][j]!='.';j++)
//camp				ActiveCampaign.mission[i].name[j]=ActiveCampaign.filelist[i+1][j];
//camp			ActiveCampaign.mission[i].name[j]=0;
//camp		}
//camp		ActiveCampaign.mission[i].missiondate=ActiveCampaign.nextdate;
//camp		ActiveCampaign.mission[i].region=ActiveCampaign.nextregion;
//camp		FindWorldTemplateFiles(ActiveCampaign.nextregion);
//camp		ActiveCampaign.mission[i].era=ConvertFileToEra(ActiveCampaign.nextera);//DAW 06Sep97
//camp		ActiveCampaign.mission[i].PlayerNationality=ActiveCampaign.nextnat;
//camp	}
//camp//	Persons_2.justscanning=false;
//camp
//camp
//camp	if (ActiveCampaign.totaldays==0)
//camp	{
//camp		MissionNew=true;
//camp		ActiveCampaign.totaldays=1;
//camp		currmission=0;
//camp		FindWorldTemplateFiles(ActiveCampaign.mission[currmission].region);
//camp		MissionEditor->NewWorld();
//camp//				ChooseBfForm->BFields[ChooseBfForm->AvailBf[ActiveCampaign.mission[currmission].era]].file,
//camp  //				ActiveCampaign.mission[currmission].region);
//camp//		PaintBox->Invalidate();
//camp		InitMission();
//camp		CampaignStarted=false;
//camp		MissionBaseForm->OpenNewMiss();
//camp		SetCaption(dirname,ActiveCampaign.mission[currmission].name);
//camp	}
//camp	else
//camp	{
//camp		CampaignStarted=true;
//camp		SetCaption(dirname,ActiveCampaign.mission[currmission].name);
//camp		MissionNew=false;
//camp		CampaignEditDlg->CloseBtn->Enabled=false;
//camp		CampaignEditDlg->OpenForm();
//camp	}
//camp	SetCaption(MissionEditor->ActiveCampaign.name,ActiveCampaign.mission[currmission].name);
//camp}
//camp///////////////////////////////////////////////////////////////////////////////
//campvoid	TMissionEditor::NewCampaign(AnsiString name,AnsiString title)
//camp{
//camp	if (!MissionBaseForm->OfferSaveCurrent())
//camp		return;
//camp
//camp	char	f[100];
//camp	char	dirname[10];
//camp
//camp	strcpy(f,FILEMAN.namenumberedfile(DIR_USEROBJ));
//camp	f[strlen(f)-7]=0;
//camp	dirname[0]='C';
//camp	strcpy(dirname+1,name.c_str());
//camp	strcat(f,dirname);
//camp	_mkdir(f);
//camp	strcpy(MissionEditor->ActiveCampaign.name,dirname);
//camp	SetMissionMode(false);
//camp	FILEMAN.fakedir(FIL_USERMISSION1,f);
//camp	strcat(f,"\\dir.dir");
//camp	FILE* F=fopen(f,"wb");
//camp	ActiveCampaign.filelist.Clear();
//camp	fwrite(	&ActiveCampaign.filelist.data,
//camp			ActiveCampaign.filelist.maxfiles,
//camp			ActiveCampaign.filelist.charsperfile,
//camp			F);
//camp	fclose(F);
//camp	InitCampaign();
//camp	strcpy(MissionEditor->ActiveCampaign.title,title.c_str());
//camp	ActiveCampaign.totaldays=0;
//camp	InitMission();
//camp	FindWorldTemplateFiles(ActiveCampaign.mission[currmission].region);
//camp	MissionEditor->NewWorld(
//camp			ChooseBfForm->BFields[ChooseBfForm->AvailBf[ActiveCampaign.mission[currmission].era]].file,
//camp			ActiveCampaign.mission[currmission].region);
//camp//	PaintBox->Invalidate();
//camp	MissionNew=true;
//camp	MissionBaseForm->OpenNewMiss();
//camp	SetCaption(dirname,ActiveCampaign.mission[currmission].name);
//camp	F=fopen(FILEMAN.namenumberedfile(FileNum(((int)FIL_USERMISSION1&0xff00)+(int)ActiveCampaign.filelist.maxfiles-2)),"wb");
//camp	fwrite(&ActiveCampaign,sizeof(MeCampaignTexts),1,F);
//camp	fclose(F);
//camp	PilotForm->SavePilots(FILEMAN.namenumberedfile(FileNum(((int)FIL_USERMISSION1&0xff00)+(int)ActiveCampaign.filelist.maxfiles-1)));
//camp	ActiveCampaign.totaldays=1;
//camp//	FileLoadSave->DefaultDirectory();
//camp	currmission=0;
//camp   //MobileSpdButtonState();
//camp	DisableWPUsageifnecessary();	//rdh
//camp}
//camp//---------------------------------------------------------------------------
//campvoid __fastcall TMissionEditor::RunCampaignClick(TObject *)
//camp{
//camp	if (!SaveMission(bfieldbeingfilled))
//camp		return;
//camp	TClipboard*	MyBoard=Clipboard();
//camp	AnsiString tmp=(AnsiString)"MED: "+ActiveCampaign.name;
//camp	MyBoard->AsText=tmp;
//camp	sleep(3);
//camp	AnsiString tmp2=MyBoard->AsText;
//camp	if (tmp==tmp2)
//camp	{
//camp		char	path[300];
//camp		strcpy (path,GetCommandLine ());
//camp		int i=1;
//camp		while (path[i]>=' ' && path[i]!='"')
//camp			i++;
//camp		while (i>0 && path[i]!=':' && path[i]!='\\')
//camp			i--;
//camp		i--;
//camp		while (i>0 && path[i]!=':' && path[i]!='\\')
//camp			i--;
//camp		if (i==2 && path[1]==':')
//camp			i++;
//camp		path[i]=0;
//camp		char cmd[300];
//camp		char line[300];
//camp		strcpy(cmd,path);
//camp		strcpy(line,path);
//camp		if (i==3 && cmd[1]==':')
//camp		{
//camp			cmd[2]=0;
//camp			line[2]=0;
//camp		}
//camp		strcat(cmd,"\\winfly.exe");
//camp		strcat(line,"\\winfly.exe\"");
//camp
//camp		CreateProcess(	cmd+1,line,
//camp//		CreateProcess(	"c:\\fly\\src\\mycmds\\bug.bat",NULL,
//camp						NULL,NULL,
//camp						FALSE,CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS,
//camp						NULL,path+1,
//camp						&sui,&pi
//camp						);
//camp	}
//camp}
//camp//---------------------------------------------------------------------------
void __fastcall TMissionEditor::RunMissionClick(TObject *)
{
	if (!BfieldForm->SaveMission(bfieldbeingfilled))
		return;
	TClipboard*	MyBoard=Clipboard();
	AnsiString tmp=(AnsiString)"MED: not working...";//+ActiveCampaign.name+" "+ActiveCampaign.mission[currmission].name+".BF";
	MyBoard->AsText=tmp;
	sleep(3);
	AnsiString tmp2=MyBoard->AsText;
	if (tmp==tmp2)
	{
		char	path[300];
		strcpy (path,GetCommandLine ());
		int i=1;
		while (path[i]>=' ' && path[i]!='"')
			i++;
		while (i>0 && path[i]!=':' && path[i]!='\\')
			i--;
		i--;
		while (i>0 && path[i]!=':' && path[i]!='\\')
			i--;
		if (i==2 && path[1]==':')
			i++;
		path[i]=0;
		char cmd[300];
		char line[300];
		strcpy(cmd,path);
		strcpy(line,path);
		if (i==3 && cmd[1]==':')
		{
			cmd[2]=0;
			line[2]=0;
		}
		strcat(cmd,"\\winfly.exe");
		strcat(line,"\\winfly.exe\"");

		CreateProcess(	cmd+1,line,
//		CreateProcess(	"c:\\fly\\src\\mycmds\\bug.bat",NULL,
						NULL,NULL,
						FALSE,CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS,
						NULL,path+1,
						&sui,&pi
						);
//		sleep(10);
//		MyBoard->AsText=tmp;
//		sleep(3);
//		tmp2=MyBoard->AsText;
//		if (tmp==tmp2)
//		{
//			tmp=tmp2;
//		}
	}
}
 //---------------------------------------------------------------------------
void __fastcall TMissionEditor::ScrollMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TComponent* s=(TComponent*)Sender;
	if (s->Tag&1)
		HS_Scroll.OnPress(Sender,X);
	else
		VS_Scroll.OnPress(Sender,Y);
}

void __fastcall TMissionEditor::ScrollMouseDown2(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TLabel* l=(TLabel*)Sender;
	ScrollMouseDown(l->FocusControl,Button,Shift,X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ScrollMouseUp(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (VS_Scroll.downpos)
		VS_Scroll.OnRelease(Sender);
	else if (HS_Scroll.downpos)
		HS_Scroll.OnRelease(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ScrollMouseMove(TObject *Sender,
	TShiftState Shift, int X, int Y)
{
	if (VS_Scroll.downpos)
		VS_Scroll.OnMove(Y);
	else if (HS_Scroll.downpos)
		HS_Scroll.OnMove(X);

}

Bool	DidRepos=FALSE;
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ScrollResize(TObject *Sender)
{

	int newh=0,neww=0;
	if (ScrollBox->Width>1280)
    {
    	neww=1280-((TControl*)Sender)->Width;

    }
	if (ScrollBox->Height>1280)
    {
    	newh=1280-((TControl*)Sender)->Height;
    }
    if (neww||newh)
    {

    	int t=Top;
        int l=Left;
    	newh+=Height;
        neww+=Width;
        WindowState=wsNormal;
        Width=neww;
        Height=newh;
        Left=l;
        Top=t;
        DidRepos=TRUE;
    }

		VS_Scroll.OnResize();
		HS_Scroll.OnResize();


}
//---------------------------------------------------------------
#include	<dos.h>
void __fastcall TMissionEditor::IdleTime(TObject* Sender, bool &Done)
{
	if (DidRepos)
    {
    	Realign();
        BACKPANEL->Realign();
		DidRepos=FALSE;
    }

    PushDragIdle();
	ScrollIdle();
    MapIdle();
   	Done=true;
}

//---------------------------------------------------------------

bool __fastcall TMissionEditor::ScrollIdle()
{   //return true if did something!
	if (VS_Scroll.downpos<0)
		VS_Scroll.OnMove(1);
	else if (HS_Scroll.downpos<0)
		HS_Scroll.OnMove(1);
	else
		return false;
    return true;
}
//---------------------------------------------------------------

RScrollBar::RScrollBar(
		TPanelPtr	spuck,TPanelPtr sback,TControl* svback,
		TPanelPtr spgless,TPanelPtr sstepless,TPanelPtr szoomless,TPanelPtr ssetmin,
		TPanelPtr spgmore,TPanelPtr sstepmore,TPanelPtr szoommore,TPanelPtr ssetmax,
		TLabelPtr stxtless,TLabelPtr stxtmore,DHH_BarMoved smoved,TForm* sparent)
{

	parent=sparent;
	parentmoved=smoved;
	txtless=stxtless;
	txtmore=stxtmore;
	puck=spuck;
	back=sback;
	vback=svback;
	pgless=spgless,
	stepless=sstepless,
	zoomless=szoomless,
	setmin=ssetmin,
	pgmore=spgmore,
	stepmore=sstepmore,
	zoommore=szoommore,
	setmax=ssetmax;
	if (setmax->Width>3)
	{
		puck->Tag=0;
		pgless->Tag=0;
		stepless->Tag=0;
		zoomless->Tag=0;
		setmin->Tag=0;
		pgmore->Tag=0;
		stepmore->Tag=0;
		zoommore->Tag=0;
		setmax->Tag=0;
		cornertext=&vtext;
		GetExt=&GetH;
		SetExt=&SetH;
	}
	else
	{
		puck->Tag=1;
		pgless->Tag=1;
		stepless->Tag=1;
		zoomless->Tag=1;
		setmin->Tag=1;
		pgmore->Tag=1;
		stepmore->Tag=1;
		zoommore->Tag=1;
		setmax->Tag=1;
		cornertext=&htext;
		GetExt=&GetW;
		SetExt=&SetW;
	}
	downpos=0;
	max=0;min=0;
	pix2scale=0;	//disabled
}
const float ROOT_2=1.25992105;//1.414213562;

int		zoombase[]={1,4,16,64,256,1024,4096,16384,65536,256*1024,1024*1024,4*1024*1024,16*1024*1024};
//float	zoomopt[]={1.0,1.25,1.625,2.0,2.5,3.125,4.0};
float	zoomopt[]={1.0,1.280014,1.600007,2.0,2.666687,3.20002,4.0};
void	RScrollBar::OnPress(TObject* b,int startval)
{
if (min!=max)
	if (b==puck)
	{
		downpos=startval;
	}
	else
	if (b==pgless)
	{
		curr=curr-page;
		if (curr<min)
			curr=min;
		if (int((curr-min)/bar2scale)!=GetExt(pgless))
			SetExt(pgless,(curr-min)/bar2scale);
		txtless->Caption=cornertext(curr);
		txtmore->Caption=cornertext(curr+page);
		parentmoved(parent,0.0,curr);
        downpos=-4;
	}
	else
	if (b==pgmore)
	{
		curr=curr+page;
		if (curr>max-page)
			curr=max-page;
		if (int((curr-min)/bar2scale)!=GetExt(pgless))
			SetExt(pgless,(curr-min)/bar2scale);
		pgless->Left=0;
		pgless->Top=0;
		txtless->Caption=cornertext(curr);
		txtmore->Caption=cornertext(curr+page);
		parentmoved(parent,0.0,curr);
        downpos=-3;
	}
	else
	if (b==stepless)
	{
		downpos=-2;
		OnMove(0);
		parentmoved(parent,0.0,curr);
	}
	else
	if (b==stepmore)
	{
		downpos=-1;
		OnMove(0);
		pgless->Left=0;
		pgless->Top=0;
		parentmoved(parent,0.0,curr);
	}
	else
	if (b==zoomless)
	{

        int zoomb=0,zooms=0;
		while (pix2scale>zoombase[zoomb+1])
        	zoomb++;
    	zoomb=zoombase[zoomb];
        pix2scale/=zoomb;
        while (pix2scale>zoomopt[zooms+1])
        	zooms++;
        pix2scale=zoomb*zoomopt[zooms];
		OnResize();
        SetZoomCaption();
		parentmoved(parent,pix2scale,curr);
	}
	else
	if (b==zoommore)
	{
		int zoomb=0,zooms=0;
		while (pix2scale>=zoombase[zoomb+1])
        	zoomb++;
    	zoomb=zoombase[zoomb];
        pix2scale/=zoomb;
        while (pix2scale>=zoomopt[zooms+1])
        	zooms++;
        pix2scale=zoomb*zoomopt[zooms+1];
  		curr+=page;
		OnResize();
 		OnPress(pgless,0);
        SetZoomCaption();
		parentmoved(parent,pix2scale,curr);
	}
	else
	if (b==setmin)
	{
		SetExt(pgless,0);
		curr=min;
		txtless->Caption=cornertext(curr);
		txtmore->Caption=cornertext(curr+page);
		parentmoved(parent,0.0,curr);
	}
	else
	if (b==setmax)
	{
		SetExt(pgless,GetExt(back)-GetExt(puck));
		pgless->Left=0;
		pgless->Top=0;
		SetExt(pgmore,0);
		curr=max-page;
		txtless->Caption=cornertext(curr);
		txtmore->Caption=cornertext(curr+page);
		parentmoved(parent,0.0,curr);
	}
}
void	RScrollBar::OnRelease(TObject* b)
{
	downpos=0;
}
void	RScrollBar::OnMove(int pos)
{
	if (downpos>=0)
	{

		pos-=downpos;
		curr+=pos*bar2scale;
		if (curr<min)
		{
			curr=min;
			SetExt(pgless,0);
		}
		else
		if (curr>max-page)
		{
			curr=max-page;
			SetExt(pgless,GetExt(back)-GetExt(puck));
			SetExt(pgmore,0);
		}
		else
		{
			SetExt(pgless,GetExt(pgless)+pos);
			pgless->Left=0;
			pgless->Top=0;
		}

		txtless->Caption=cornertext(curr);
		txtmore->Caption=cornertext(curr+page);
		parentmoved(parent,0.0,curr);

	}
	else
    {
	    switch (downpos)
	    {
    	case -1:
		{
			curr=curr+pix2scale*4;
			if (curr>max-page)
				curr=max-page;
			if (int((curr-min)/bar2scale)!=GetExt(pgless))
				SetExt(pgless,(curr-min)/bar2scale);
			txtless->Caption=cornertext(curr);
			txtmore->Caption=cornertext(curr+page);
			parentmoved(parent,0.0,curr);
		}
    	break;
	    case -2:
		{
			curr=curr-pix2scale*4;
			if (curr<min)
				curr=min;
			if (int((curr-min)/bar2scale)!=GetExt(pgless))
				SetExt(pgless,(curr-min)/bar2scale);
			txtless->Caption=cornertext(curr);
			txtmore->Caption=cornertext(curr+page);
            parentmoved(parent,0.0,curr);
		}
    	break;
	    case -3:
		{
			curr=curr+pix2scale*64;
			if (curr>max-page)
				curr=max-page;
			if (int((curr-min)/bar2scale)!=GetExt(pgless))
				SetExt(pgless,(curr-min)/bar2scale);
			txtless->Caption=cornertext(curr);
			txtmore->Caption=cornertext(curr+page);
			parentmoved(parent,0.0,curr);
		}
	    break;
    	case -4:
		{
			curr=curr-pix2scale*64;
			if (curr<min)
				curr=min;
			if (int((curr-min)/bar2scale)!=GetExt(pgless))
				SetExt(pgless,(curr-min)/bar2scale);
			txtless->Caption=cornertext(curr);
			txtmore->Caption=cornertext(curr+page);
			parentmoved(parent,0.0,curr);
		}
    	}
    }
}
void	RScrollBar::OnResize()
{
	if (max!=min)
	{
		bar2scale=double(max-min)/GetExt(back);
		if ((curr-min)>=0)
			SetExt(pgless,int((curr-min)/bar2scale));
		else
            SetExt(pgless,0);
		page=int(GetExt(vback)*pix2scale);
		if (page>max-min)
			page=max-min;
		SetExt(puck,int(page/bar2scale));
		txtless->Caption=cornertext(curr);
		txtmore->Caption=cornertext(curr+page);
		parentmoved(parent,0.0,curr);
	}
}
AnsiString	RScrollBar::vtext(int i)
{

	char buff[20];
    i=60*60*3080*40-i;      //top lat
    int s=i/3080;
    i=i%3080;

	sprintf(buff,"%02d° %02d\" %02d' %02dm ",
	s/(60*60),(s%(60*60))/60,s%60,i/100);
	return((AnsiString)buff);
}
AnsiString	RScrollBar::htext(int i)
{
	char buff[20];
    int s=i/2500;
    s+=120*60*60;			//left long
    i=i%2500;
	sprintf(buff,"%02d° %02d\" %02d' %02dm ",
	s/(60*60),(s%(60*60))/60,s%60,i/100);
	return((AnsiString)buff);
}
//------------------------------
RScrollBar::SetScroll(int scurr,double spix2scale,int smax,int smin)
{
	curr=scurr;
	if (spix2scale!=0.0)
	{
		if (spix2scale==pix2scale)
			spix2scale=0.0;
		else
			pix2scale=spix2scale;
	}

	if (smax!=-1)
	{
		max=smax;
		min=smin;
	}
	OnResize();
	if (spix2scale)
    {
        SetZoomCaption();
    }
	parentmoved(parent,spix2scale,curr);
	return 0;
}

void	RScrollBar::SetZoomCaption()
{
	    AnsiString C1=" ",C2="",C3="";
		if (puck->Width>30)
			C2=C1+int(pix2scale+0.0001)+C1;
		else
        if (pgless->Width>100)
        	C1=C1+int(pix2scale+0.0001)+C1;
        else
        if (pgmore->Width>100)
        	C3=C1+int(pix2scale+0.0001)+C1;
        pgmore->Caption=C3;
        puck->Caption=C2;
        pgless->Caption=C1;
}
//-----------------------------------------------------
void	TMissionEditor::BARMOVED(VS)
{
	int currx=HS_Scroll.GetPos();
	if (scale)
	{
		HS_Scroll.SetScroll(currx,scale);
	}
    BarMoved(currx,VS_pos,scale);

}
void	TMissionEditor::BARMOVED(HS)
{
	int curry=VS_Scroll.GetPos();
	if (scale)
	{
		VS_Scroll.SetScroll(curry,scale);
	}
    BarMoved(HS_pos,curry,scale);

}


UINT	cfreq;UINT cfsrc;
HANDLE  gmem;
BITMAPINFO	bmi={{sizeof(BITMAPINFOHEADER),2048,2048,1,8,BI_RGB,2048*2048,1,1,0,0}};

struct Bmi2:public BITMAPINFO
{
	char palspace[1020];
}	BMI2,BMI3;


//////////////////////////////////////////////////////////////////////////////////
void	TMissionEditor::InitPaintGrid()
{
	loadrequested=FALSE;
    leveldrop=Level_Drop;
    new MapLoad();
	FILE* f=fopen("blank256.bmp","rb");
    fread(&BMI2,14,1,f);
    fread(&BMI2,sizeof(Bmi2),1,f);
    fclose(f);
    BMI2.bmiHeader.biHeight=2048;
    BMI2.bmiHeader.biWidth=2048;
    BMI2.bmiHeader.biClrUsed=256;
    BMI2.bmiHeader.biClrImportant=256;
    BMI3=BMI2;
    for (int i=0;i<256;i++)
	    UWordP(BMI3.bmiColors)[i]=i;

	#define	box1(x,y) RealPoints[x][y].box=PB##x##y;
    #define boxrow(y)  \
   	box1(0,y) box1(1,y) box1(2,y) box1(3,y) box1(3,y) box1(4,y) box1(5,y)
    boxrow(0)
    boxrow(1)
    boxrow(2)
    boxrow(3)
    boxrow(4)
    boxrow(5)
    CurrCanvas=&PaintGrid[0][0];
	cfreq=RegisterClipboardFormat("RowanTT2Req");
	cfsrc=RegisterClipboardFormat("RowanTT2Sup");
	CreateProcess(
     					"\\utilsrc\\tt2\\wtt2.exe","\\utilsrc\\tt2\\wtt2.exe -d9rcdwc",
        					NULL,NULL,
							FALSE,IDLE_PRIORITY_CLASS,
							NULL,"\\mig\\src\\meditor",
							&sui,&pi
							);

//    while (!OpenClipboard(NULL))
//    	Sleep(0);
//	gmem=GlobalAlloc(GMEM_MOVEABLE+GMEM_DDESHARE,8);
//    char* str=(char*)GlobalLock(gmem);

    leveldrop[0].minscale=65536;leveldrop[0].blblk=8311;
    leveldrop[1].minscale=16384;leveldrop[1].blblk=8411;
    leveldrop[2].minscale= 4096;leveldrop[2].blblk=7511;
    leveldrop[3].minscale= 1024;leveldrop[3].blblk=1111;

//	sprintf(str,"R%i",leveldrop[0].blblk);
//    EmptyClipboard();
//    SetClipboardData(cfreq,gmem);
//    GlobalUnlock(gmem);
//	CloseClipboard();
//    loadrequested=TRUE;


    StartBlockLoad(0,0,0,true);
//        int error=GetLastError();
    paintpos=&PaintGrid[0];
    cmpixscale=20480.0;
    int cmpertile=256*cmpixscale;
    Color=clNone;
    Brush->Style=bsClear;
    Panel5->Color=clNone;
    Panel5->Brush->Style=bsClear;
    Panel4->Color=clNone;
    Panel4->Brush->Style=bsClear;
    ScrollBox->Color=clNone;
    ScrollBox->Brush->Style=bsClear;
    mtbackdrop=new Graphics::TBitmap;
    mtbackdrop->LoadFromFile("blank256.bmp");
//    ScrollBox1->Color=clNone;
//    ScrollBox1->Brush->Style=bsClear;
   	for (int x=0;x<REALMAXPAINT;x++)
		for (int y=0;y<REALMAXPAINT;y++)
        {
        	PaintGrid[x]+y=&RealPoints[x][y];
        	PaintGrid[x][y]->Width=256;
        	PaintGrid[x][y]->Height=256;
            PaintGrid[x][y].WX=16*1024*1024+cmpertile*x;
            PaintGrid[x][y].WZ=cmpertile*y;
        	PaintGrid[x][y]->Top=y*256;
            PaintGrid[x][y]->Left=x*256;
            PaintGrid[x][y]->Tag=x+y*65536;
            PaintGrid[x][y].gridxblk=x;
            PaintGrid[x][y].dirty=true;
            PaintGrid[x][y].gridyblk=y;
            PaintGrid[x][y]->Color = (TColor)0;
			PaintGrid[x][y]->Canvas->Brush->Style = bsClear;
            PaintGrid[x][y].backdrop=new Graphics::TBitmap;
            PaintGrid[x][y].backdrop->LoadFromFile("blank256.bmp");
        }
    for (int dx=0;dx<=GRIDMAXPAINT;dx+=REALMAXPAINT)
    	for (int dy=0;dy<GRIDMAXPAINT;dy+=REALMAXPAINT)
        	for (int x=0;x<REALMAXPAINT;x++)
            	for (int y=0;y<REALMAXPAINT;y++)
                	PaintGrid[x+dx]+(y+dy)=PaintGrid[x]+y;

//	leveldrop[0].hmaps[0]=
  //  	CreateDIBSection(NULL,&bmi,DIB_RGB_COLORS,
    //    				(void**)&leveldrop[0].cmaps[0],
      //                  NULL,NULL);

//	leveldrop[0].maps[0]=new Graphics::TBitmap;
  //	leveldrop[0].maps[0]->IgnorePalette=true;
//    while	(!DoneLoadBlockReq())	{}
//    leveldrop[1].maps[0]->LoadFromFile("pic.bmp");
	VS_Scroll.SetScroll(0,cmpixscale,128*1024*1024);
	HS_Scroll.SetScroll(16*1024*1024,cmpixscale,16*6*1024*1024,16*1024*1024);

}
///////////////////////////////////////////////////////////////////////
LevelDrop::LevelDrop(int scale):
        	dirty(0xf)
        {
        	minscale=scale;
//            cmaps[0]=cmaps[1]=cmaps[2]=cmaps[3]=NULL;
//	        maps[0]=new Graphics::TBitmap;maps[1]=new Graphics::TBitmap;
//            maps[2]=new Graphics::TBitmap;maps[3]=new Graphics::TBitmap;
//            maps[0]->IgnorePalette=true;maps[1]->IgnorePalette=true;
//            maps[2]->IgnorePalette=true;maps[3]->IgnorePalette=true;
//            maps[0]->Width=2048;maps[0]->Height=2048;
//            maps[1]->Width=2048;maps[1]->Height=2048;
//            maps[2]->Width=2048;maps[2]->Height=2048;
//            maps[3]->Width=2048;maps[3]->Height=2048;
        	px=py=0x0000000;
        }

///////////////////////////////////////////////////////////////////////////////////
void	TMissionEditor::ExitPaintGrid()
{
   	for (int x=0;x<REALMAXPAINT;x++)
		for (int y=0;y<REALMAXPAINT;y++)
			if (&PaintGrid[x][y])
				delete	PaintGrid[x][y].backdrop;
    delete		mtbackdrop;
    while (!OpenClipboard(NULL))
    	Sleep(0);
	gmem=GlobalAlloc(GMEM_MOVEABLE+GMEM_DDESHARE,8);
    UWord* str=(UWord*)GlobalLock(gmem);
    *str='Q';
    EmptyClipboard();
    SetClipboardData(cfreq,gmem);
	CloseClipboard();
    GlobalUnlock(gmem);
}

///////////////////////////////////////////////////////////////////////////////////
void	TMissionEditor::BarMoved(int newx,int newy,double newscale)
{
	int dwx=newx-paintpos[0][0].WX;
    int	dwy=newy-paintpos[0][0].WZ;
    int dpx=dwx/cmpixscale;
    int	dpy=dwy/cmpixscale;
    bool	changed=false;
    int sx=paintpos[0][0].gridxblk;
    int sy=paintpos[0][0].gridyblk;
	if ((newscale && newscale!=cmpixscale) || dpx<-1024 || dpx>1024+256 || dpy<-1024 || dpy>1024+256)
    {
        if (newscale)
        	cmpixscale=newscale;
        int blocksize=cmpixscale*256;
        dpx=newx%blocksize;
        dwx=newx-dpx;
        dpy=newy%blocksize;
        dwy=newy-dpy;
        dpx/=cmpixscale;
        dpy/=cmpixscale;
        paintpos=PaintGrid;
        newscale=cmpixscale;
       	for (int x=0;x<int(REALMAXPAINT);x++)
        {
        	for (int y=0;y<int(REALMAXPAINT);y++)
			{
            	setdrawpos(paintpos[x][y],dwx+x*blocksize,dwy+y*blocksize);
            }
        }


    }
    else
    {   //calc screen x,y of paintpos
    	//if still in corner then just move all coords
        //if off corner then change paintpos.
//        Mono_Text.PrintF("Delta	X=%i,y=%i                \n",-(dpx+paintpos[0][0]->Left),-(dpy+paintpos[0][0]->Top));
        ScrollBox->ScrollBy(-(dpx+paintpos[0][0]->Left),-(dpy+paintpos[0][0]->Top));
        ScrollBox->VertScrollBar->Visible=FALSE;
        ScrollBox->HorzScrollBar->Visible=FALSE;
        if ((ULong)dpx>=256)
        {
			if (dpx>=256)
            {
            	do{
                    double paintdelta=cmpixscale*256;
                    double paintx=paintpos[0][0].WX+int(REALMAXPAINT)*paintdelta;
                    double painty=paintpos[0][0].WZ;
                    for (int y=0;y<int(REALMAXPAINT);y++)
                    {
                        setdrawpos(paintpos[0][y],paintx,painty);
                        painty+=paintdelta;
                    }
                	sx+=1;
                    if (sx>=REALMAXPAINT)
                    	sx-=REALMAXPAINT;
		            paintpos=PaintGrid[sx](sy);
                    dpx-=256;
                }while(dpx>=256);
            }
            else
            {
            	do{
                    double paintdelta=cmpixscale*256;
                    double paintx=paintpos[0][0].WX-paintdelta;
                    double painty=paintpos[0][0].WZ;
                	sx-=1;
                    if (sx<0)
                    	sx+=REALMAXPAINT;
		            paintpos=PaintGrid[sx](sy);
                    for (int y=0;y<int(REALMAXPAINT);y++)
                    {
                        setdrawpos(paintpos[0][y],paintx,painty);
                        painty+=paintdelta;
                    }
                    dpx+=256;
                }while(dpx<0);
            }
        	changed=true;
		}
        if ((ULong)dpy>=256)
		{
			if (dpy>=256)
    		{
            	do{
                    double paintdelta=cmpixscale*256;
                    double paintx=paintpos[0][0].WX;
                    double painty=paintpos[0][0].WZ+int(REALMAXPAINT)*paintdelta;
                    for (int x=0;x<int(REALMAXPAINT);x++)
                    {
                        setdrawpos(paintpos[x][0],paintx,painty);
                        paintx+=paintdelta;
                    }
                	sy+=1;
                    if (sy>=REALMAXPAINT)
                    	sy-=REALMAXPAINT;
		            paintpos=PaintGrid[sx](sy);
                    dpy-=256;
                }while(dpy>=256);
            }
            else
            {
            	do{
                    double paintdelta=cmpixscale*256;
                    double paintx=paintpos[0][0].WX;
                    double painty=paintpos[0][0].WZ-paintdelta;
                	sy-=1;
                    if (sy<0)
                    	sy+=REALMAXPAINT;
		            paintpos=PaintGrid[sx](sy);
                    for (int x=0;x<int(REALMAXPAINT);x++)
                    {
                        setdrawpos(paintpos[x][0],paintx,painty);
                        paintx+=paintdelta;
                    }
                    dpy+=256;
                }while(dpy<0);
            }
        	changed=true;
        }
        if (changed)
        {
        	dpx=dpx;
        }
//        else
        {
        	dpy=-dpy;
            dpx=-dpx;
        	for (int x=0;x<int(REALMAXPAINT);x++)
            {
            	for (int y=0;y<int(REALMAXPAINT);y++)
                {
//                	if ((ULong(paintpos)-ULong(PaintGrid))>16*4*8)
  //                  	y=y;
    //            	if (paintpos[x](y)==NULL)
      //              	y=y;
//                    UByteP(0xb0000)[x*10+y*160]='0'+sx;
 //                   UByteP(0xb0000)[x*10+y*160+2]='0'+sy;
  //                  UByteP(0xb0000)[x*10+y*160+4]='0'+paintpos[x][y].gridxblk;
   //                 UByteP(0xb0000)[x*10+y*160+6]='0'+paintpos[x][y].gridyblk;
   					int xx=dpx+256*x,yy=dpy+256*y;
					if (paintpos[x][y]->Left!=xx)
  	                    paintpos[x][y].box->Left=xx;
                    if (paintpos[x][y]->Top!=yy)
	                    paintpos[x][y].box->Top=yy;
                }
            }
        }

    }
}


void	TMissionEditor::setdrawpos(MapBlock& paintpos,int paintx,int painty)
{
	paintpos.box->Invalidate();
	paintpos.WX=paintx;
    paintpos.WZ=painty;
    paintpos.scaled=false;
    paintpos.dirty=true;
//    int	newscale=cmpixscale;///1024;
//    if (cmpixscale)
//    	newscale=1024*1024*32/cmpixscale;
//    else
//    	newscale=1024*1024;
}
/////////////////////////////////////////////////////////////////////////
bool TMissionEditor::MapIdle()
{
//   	Mono_Text.PrintF("I");
//	static int timeh;
//    struct time	stime;



    if (leveldrop[0].maps[0].c==NULL)
    {

	    for (int l=1;l<4;l++)
    		for (int b=0;b<4;b++)
        		if (leveldrop[l].maps[b].c==NULL)
                {
                    leveldrop[l].maps[b].h=
                    	CreateDIBSection(NULL,&bmi,DIB_RGB_COLORS,
                        					(void**)(&leveldrop[l].maps[b].c),
                                            NULL,NULL);
                    return false;
//                	leveldrop[l].maps[b]=new Graphics::TBitmap;
  //					leveldrop[l].maps[b]->LoadFromFile("pic.bmp");
    //                leveldrop[l].maps[b]->IgnorePalette=true;
   //		            leveldrop[l].maps[b]->FreeImage();
                }
		leveldrop[0].maps[0].h=
   			CreateDIBSection(NULL,&bmi,DIB_RGB_COLORS,
  	    					(void**)(&leveldrop[0].maps[0].c),
							NULL,NULL);

		return false;
    }
	static MonoText Mono_text(0xb0000+160*18+80);
	    for (int l=1;l<4;l++)
    		for (int b=0;b<4;b++)
				if (!leveldrop[l].dirty[b])
                	Mono_text.PrintF(20+b*5,l,"C    ");
                else
                	for (int s=0;s<4;s++)
                    	if (leveldrop[l].maps[b].scaled[s])
                        	Mono_text.PrintF(20+b*5+s,l,"s");
                        else
                        	Mono_text.PrintF(20+b*5+s,l,"d");

	for (int x=0;x<REALMAXPAINT;x++)
    	for (int y=0;y<REALMAXPAINT;y++)
			if (!paintpos[x][y]->Visible)
            {
		    	if (loadrequested)	return false;

				paintpos[x][y]->Visible=true;
                paintpos[x][y]->Invalidate();
                return false;
            }

//    gettime(&stime);
//    if ((stime.ti_sec)==timeh)
//    {
//    	Mono_Text.PrintF("T");
//        return true;
//    }
//	timeh=(stime.ti_sec);


//    if (loadrequested)
  //  {
    //	if (DoneLoadBlockReq())
	  //  	return false;
//    }

	for (int x=0;x<REALMAXPAINT;x++)
    	for (int y=0;y<REALMAXPAINT;y++)
        {
        	if (!paintpos[x][y].dirty)
	            Mono_text.PrintF(x,y,"c");
            else
        	if (paintpos[x][y].scaled)
	            Mono_text.PrintF(x,y,"s");
            else
	            Mono_text.PrintF(x,y,"d");

        	if (CouldDoBetter(paintpos[x][y]))
            {
	        	if (!paintpos[x][y].dirty)
		            Mono_text.PrintF(x,y,"C");
        	    else
        		if (paintpos[x][y].scaled)
	            	Mono_text.PrintF(x,y,"S");
	            else
		            Mono_text.PrintF(x,y,"D");
                RescaleArt(paintpos[x][y]);
                paintpos[x][y]->Invalidate();
            	return false;
            }
        }
    int order=0x00010203;
	if (cmpixscale>=leveldrop[1].minscale)
        order=0x00030201;
    else if (cmpixscale>=leveldrop[2].minscale)
    	order=0x00010302;

    for (int l=order&0x0f;order;order>>=8,l=order&0x0f)
    	for (int b=0;b<4;b++)
        	if (leveldrop[l].dirty[b])
            {
                StartBlockLoad(l,
                	(leveldrop[l].px+(b&1))*leveldrop[l].minscale*2048,
                	(leveldrop[l].py+(b>>1))*leveldrop[l].minscale*2048,
                    false);
                return false;
            }
	return false;
}

bool	TMissionEditor::CouldDoBetter(MapBlock& map)
{
	if (!map.dirty)
    	return FALSE;
    else
    if (!map.scaled)
    	return TRUE;
    else
    {
		int level=3;

        if (cmpixscale>leveldrop[1].minscale)
        	level=0;
        else
	        while	(leveldrop[level].minscale<cmpixscale)
    	    	level--;
		LevelDrop& ld=leveldrop[level];
		int dx=map.WX/(ld.minscale*2048)-ld.px;
		int dy=map.WZ/(ld.minscale*2048)-ld.py;
		if ((dx&-2)==0 && (dy&-2)==0)
        	if (!ld.dirty[dx+dy*2])
	        	return TRUE;
            else
            	return FALSE;
        else
	    	return TRUE;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::RescaleArt(MapBlock& block)
{
    	int	paintx=block.WX;
    	int	painty=block.WZ;
        int newscale=cmpixscale;

		int level=3;
        if (newscale>leveldrop[1].minscale)
        	level=0;
        else
	        while	(leveldrop[level].minscale<newscale)
    	    	level--;
        LevelDrop& ld=leveldrop[level];
//		int levelcms=ld.minscale*2048;
//	    Mono_Text.PrintF("Scale Box level %i\t",level);
        int	blky,blkx=1*64*256*1024;
        if (newscale<=leveldrop[1].minscale*2)
        	blkx+=2*8*256*2048;
        else
        if (newscale<=leveldrop[1].minscale)
        	blkx+=3*8*256*2048;
        else
        if (newscale<=leveldrop[2].minscale)
        	blkx+=4*8*256*2048;

        if (paintx<blkx || painty<0 || paintx>=6*64*256*1024|| painty>=8*64*256*1024)
        {
		    TRect scaletrg=Rect(0,0,256,256);
            block.backdrop->Canvas->Brush->Color=(TColor)0xffffff;
            block.backdrop->Canvas->FillRect(scaletrg);
            block.dirty=false;
            return;

        }
       	block.scaled=false;

        if (GetBlock( level,paintx,painty,&blkx,&blky))
	    	block.dirty=false;
        else
        	block.scaled=true;

//        mtbackdrop->IgnorePalette=true;
  //		mtbackdrop->Canvas->CopyMode=cmSrcCopy;
        block.backdrop->Canvas->CopyMode=cmSrcCopy;

	    TRect scalesrc;
        scalesrc.Left=(ld.px+blkx)*2048-paintx/ld.minscale;
        scalesrc.Top=(ld.py+blky)*2048-painty/ld.minscale;
        scalesrc.Right=2048+scalesrc.Left;
        scalesrc.Bottom=2048+scalesrc.Top;
        if (blkx<0||blkx>=2||blky<0||blky>=2)
        	blkx=blkx;
	    HBITMAP h=block.backdrop->Canvas->Handle;
        SetStretchBltMode(h,COLORONCOLOR);
        int dx=paintx/ld.minscale-(ld.px+blkx)*2048;
        int dy=painty/ld.minscale-(ld.py+blky)*2048;
        int srcpix=256*newscale/ld.minscale;
        Mono_Text.PrintF("D%i",level);
        if (dx>2048-srcpix || dy>2048-srcpix)
        {
        	TRect wipetrg=Rect(0,0,256,256);
            block.backdrop->Canvas->Brush->Color = (TColor)0x00ff00;
			block.backdrop->Canvas->FillRect(wipetrg);
        }
        StretchDIBits(h,0,255,256,-256,					//trg handle,x,y,w,h
        			dx,dy,srcpix,srcpix,    			//src x,y,w,h
        			ld.maps[blkx+blky+blky].c,&BMI2,    //src data and pal
			        DIB_RGB_COLORS,SRCCOPY);        //DIB_RGB_COLOURS
       	Mono_Text.PrintF("y");
}

UByte* src;
bool	TMissionEditor::GetBlock(int level,int xreq,int yreq,int* blkx,int* blky)
{
	bool rv=true;
	LevelDrop& ld=leveldrop[level];
    int blcm=(ld.minscale*2048);
	int dx=xreq/blcm-ld.px;
	int dy=yreq/blcm-ld.py;
	if (!((dx&-2)==0 && (dy&-2)==0 && !ld.dirty[dx+dy*2]))
    {
 		StartBlockLoad(level,xreq,yreq,false);
        blcm>>=1;
		int qx=xreq/blcm-ld.px*2,
	        qy=yreq/blcm-ld.py*2;
		dx=qx/2;qx=qx%2;
        dy=qy/2;qy=qy%2;
//        if (ld.scaled[dx+dy*2][4])
  //      	ld.scaled[dx+dy*2]=0;
        if (!ld.maps[dx+dy*2].scaled[qx+qy*2])
        {
        	int px,py;
            //get relevent parent
            Mono_Text.PrintF("Stretch %i:\t",level);
            GetBlock(level-1,xreq,yreq,&px,&py);
            LevelDrop& lz=leveldrop[level-1];
            //clip relevent parent 8th^2 into mtbackdrop
//			int sx=(xreq/(lz.minscale*256)-lz.px*8)*256,
//		        sy=(yreq/(lz.minscale*256)-lz.py*8)*256;


            //should be perfect quarters size 256 --> 1024, but overlap of 30 --> 120
            //offset is 226 --> 904. Size is 286 --> 1144
            //shunt between rows is  trg: 1/2 row+ 3 rows; src: 7/8 row - plus overlap
            if (dy!=0)
            	dy=dy;
            int offset=((ld.px+dx)&3)*512+((ld.py+dy)&3)*512*2048+qx*226+qy*226*2048;
           /* UByte* */src=(UByte*)(lz.maps[px+py*2].c+offset);
            ULong* trg=(ULong*)(ld.maps[dx+dy*2].c+qx*904+qy*904*2048);
            Mono_Text.PrintF("Stretching  %i[%i] to %i[%i]",level-1,px+py*2,level,dx+dy*2);
            for (int y=0;y<256+30;y++,trg+=256*7-30,src+=256*7-30)
            	for (int x=0;x<256+30;x++,trg++,src++)
                {
                	int s=*src *0x1010101;
                    s=s;
					trg[0]=trg[512]=trg[1024]=trg[1536]=s;
                }
            if (int(trg)>int(lz.maps[px+py*2].c+2048*2048+256*7-33))
            	dx=dx;
            Mono_Text.PrintF("Done\n");
        	ld.maps[dx+dy*2].scaled[qx+qy*2]=true;
//        	ld.scaled[dx+dy*2][4]=true;
        }
        rv=false;
    }
	*blkx=dx;
	*blky=dy;
    //rescale 1/4 of source block through buffer


    return rv;
}


//            for (int y=0;y<512;y++,trg+=256*6,src+=256*6)
  //          	for (int x=0;x<512;x++,trg++,src++)
///////////////////////////////////////////////////////////////////////////////
void	TMissionEditor::StartBlockLoad(int level,int x,int y,bool fast)
{
	LevelDrop::SubDrop tmpdrop;
	int levelcms=leveldrop[level].minscale*2048;
	int xreq=(x/levelcms)*levelcms;
    int yreq=(y/levelcms)*levelcms;
    static bool blocker=true;
	if (!loadrequested && blocker)
    {	//blocker=false;
		xloadreq=x;
	    yloadreq=y;
    	levelreq=level;
	    loadquick=fast;
		x/=levelcms;
		y/=levelcms;
    	y=64*1024/leveldrop[level].minscale-1-y;
	    int	x1=x%8;	x/=8;
    	int	y1=y%8;	y/=8;
	    bloadreq=leveldrop[level].blblk+x*1000+y*100+x1*10+y1;
 //   	int priority=CREATE_DEFAULT_ERROR_MODE | IDLE_PRIORITY_CLASS;
 //	    if (fast)
 //   		priority=CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS;

		while (!OpenClipboard(NULL))
        	Sleep(0);
		gmem=GlobalAlloc(GMEM_MOVEABLE+GMEM_DDESHARE,8);
    	char* str=(char*)GlobalLock(gmem);
    	sprintf(str,"R%i",bloadreq);
	    EmptyClipboard();
    	SetClipboardData(cfreq,gmem);
	    GlobalUnlock(gmem);
		CloseClipboard();
	    loadrequested=TRUE;
    }
	LevelDrop& ld=leveldrop[level];
	int dx=xreq/(ld.minscale*2048)-ld.px;
	int dy=yreq/(ld.minscale*2048)-ld.py;
    if (dx>=3||dx<=-2||dy>=3||dy<=-2)
    {		//no overlap - restart
    	Mono_Text.PrintF("Origin\t");
    	ld.px+=dx;
		ld.py+=dy;
		ld.dirty[0]=true;
        ld.dirty[1]=true;
        ld.dirty[2]=true;
        ld.dirty[3]=true;
		ld.maps[0].scaled=0;
		ld.maps[1].scaled=0;
		ld.maps[2].scaled=0;
		ld.maps[3].scaled=0;
	}
    else
	if ((dx<0||dx>1)&&(dy<0||dy>1))
	{	//shift origin diagonally
    	tmpdrop=ld.maps[0];
        ld.maps[0]=ld.maps[3];
        ld.maps[3]=tmpdrop;
    	tmpdrop=ld.maps[1];
        ld.maps[1]=ld.maps[2];
        ld.maps[2]=tmpdrop;
        if (dx<0)
        	ld.px-=1;
        else
           	ld.px+=1;
        if (dy<0)
        	ld.py-=1;
        else
           	ld.py+=1;
        dx=((dx+1)&1);
        dy=((dy+1)&1);
    	Mono_Text.PrintF("Diag %i,%i\t",dx,dy);
       	ld.dirty[dx+dy*2]=true;
        ld.dirty[dx+2-dy*2]=true;
        ld.dirty[dy*2+1-dx]=true;
       	ld.maps[dx+dy*2].scaled=0;
       	ld.maps[dx+2-dy*2].scaled=0;
       	ld.maps[dy*2+1-dx].scaled=0;
    }
    else
    if (dx<0||dx>1)
    {	//shift origin accross
    	tmpdrop=ld.maps[0];
        ld.maps[0]=ld.maps[1];
        ld.maps[1]=tmpdrop;
    	tmpdrop=ld.maps[2];
        ld.maps[2]=ld.maps[3];
        ld.maps[3]=tmpdrop;
        dx=((dx+1)&1);
        if (dx)
	        ld.px+=1;
        else
    	    ld.px-=1;
    	Mono_Text.PrintF("Col %i\t",dx);
		ld.dirty[dx]=true;
		ld.dirty[dx+2]=true;
       	ld.maps[dx].scaled=0;
       	ld.maps[dx+2].scaled=0;

    }
    else
    if (dy<0||dy>1)
    {	//shifyt origin up
    	tmpdrop=ld.maps[0];
        ld.maps[0]=ld.maps[2];
        ld.maps[2]=tmpdrop;
    	tmpdrop=ld.maps[1];
        ld.maps[1]=ld.maps[3];
        ld.maps[3]=tmpdrop;
        dy=((dy+1)&1);
        if (dy)
           	ld.py+=1;
        else
        	ld.py-=1;
    	Mono_Text.PrintF("Row %i\t",dy);
		ld.dirty[2*dy]=true;
		ld.dirty[2*dy+1]=true;
       	ld.maps[dy*2].scaled=0;
       	ld.maps[dy*2+1].scaled=0;
	}
    tmpdrop.c=NULL;
    tmpdrop.h=NULL;
//    else
  //  	return;

}

///////////////////////////////////////////////////////////////////////////////
bool	TMissionEditor::DoneLoadBlockReq()
{
//dead	LevelDrop& ld=leveldrop[levelreq];
//dead	if (loadrequested)
//dead    {
//dead    	DWORD	rc;
//dead
//dead
//dead        static int accpt=0;
//dead 		int blcm=(ld.minscale*2048);
//dead		int dx=xloadreq/blcm-ld.px;
//dead		int dy=yloadreq/blcm-ld.py;
//dead//		if (dx>=0 && dy>=0 && dx<2 && dy<2)
//dead//		{		//proper overlap
//dead//            for (int i=0;i<100;i++)
//dead//            {
//dead//	            accpt+=4096;
//dead//    	        accpt&=(2048*2048-1);
//dead//        	    rc=ld.maps[dx+dy*2].c[accpt];
//dead//            }
//dead//                Mono_Text.PrintF("%2i\b\b",accpt/41930);
//dead//        }
//dead
//dead        static int freshclip=0;
//dead        if (!IsClipboardFormatAvailable(cfsrc))
//dead        {
//dead        	freshclip=0;
//dead        	return FALSE;
//dead        }
//dead        while (!OpenClipboard(NULL))
//dead        	Sleep(0);
//dead        HANDLE clip=GetClipboardData(cfsrc);
//dead        char* src=(char*)GlobalLock(clip);
//dead		if (dx>=0 && dy>=0 && dx<2 && dy<2)
//dead        	if (freshclip<2048*2048)
//dead	   		{
//dead            	ld.maps[dx+dy*2].scaled=-1;
//dead            	const stepsize=2048*8;
//dead            	if (freshclip)
//dead                	Mono_Text.PrintF("\b\b%2i",freshclip/(205*205));
//dead                else
//dead                    Mono_Text.PrintF("Load %i[%i]:  ",levelreq,dx+dy*2);
//dead    	       	char* trg=ld.maps[dx+dy*2].c;
//dead
//dead		        memcpy(trg+freshclip,src+freshclip,stepsize);
//dead				freshclip+=stepsize;
//dead		        GlobalUnlock(clip);
//dead        	    rc=false;	//busy
//dead	        }
//dead    	    else
//dead			{
//dead				ld.dirty[dx+dy*2]=false;
//dead	        	freshclip=0;
//dead                GlobalUnlock(clip);
//dead		    	EmptyClipboard();
//dead        	    rc=true;
//dead    	    	loadrequested=false;
//dead                Mono_Text.PrintF("Done");
//dead	        }
//dead		else
//dead        {
//dead        		if (freshclip==0)
//dead                	Mono_Text.PrintF("Aborted %i[%i]!",levelreq,dx+dy*2);
//dead				else
//dead					Mono_Text.PrintF("Abort!");
//dead	        	freshclip=0;
//dead                GlobalUnlock(clip);
//dead		    	EmptyClipboard();
//dead        	    rc=true;
//dead    	    	loadrequested=false;
//dead
//dead        }
//dead    	CloseClipboard();
//dead        return rc;
//dead    }
//dead    else
    	return true;
}


