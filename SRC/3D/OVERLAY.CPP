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
//Filename       overlay.cpp
//System         
//Author         Paul.   
//Date           Thu 4 Jun 1998
//Description    
//------------------------------------------------------------------------------
//#include "overlay.h"

#include <afxctl.h>
#include	<afxwin.h>
#include "dosdefs.h"
#define	F_BATTLE
#include	"files.g"
#include "fileman.h"
//DeadCode RJS 05Dec100 #include "windows.h"
#include "polygon.h"
#include "imagemap.g"
#include "viewsel.h"
#include "overlay.h"
#include "keytest.h"
#include	"savegame.h"
#include <stdio.h>
#include "..\mfc\resource.h"
#include "analogue.h"
#include "CString.h"
#include "flymodel.h"
#include "landscap.h"
#include	"rchatter.h"
#include	"messengn.h"
#include	"cstring.h"
#include "ai.h"
#include	"gameset.h"
#include	"winmove.h"
#include	"replay.h"
#include	"persons2.h"
#include	"miles.h"
#include	"matrix.h"
#include	<mbstring.h>

extern SWord winmode_bpp;

extern GameSettings gameSettings;

extern	CDC g_OffScreenDC;

const ULong NO_BACKGROUND_WIPE=0x00000000;
const ULong WIPE_ALPHA_MASK=0xFF000000;
const ULong GLASS_GREY_COLOUR=0x7F000000;	//1F1F1F;
const ULong GLASS_COLOUR=GLASS_GREY_COLOUR;	//0x7F1F7F1F;
const ULong TEXT_NORMAL=0xFF00FF00;
const ULong TEXT_HI=0xFFFF0000;
const ULong TEXT_GREYED=0xFF1F7F1F;
const ULong TEXT_MAP_BLACK=0xFF000000;
const ULong TEXT_MAP_WHITE=0xFFFFFFFF;
const ULong ICON_BACK_COLOUR=0xFFFFFFFF;

#define SET_WIPE_TEXTURE(p1) ULong((p1)&0xFFFF)
#define GET_WIPE_TEXTURE(p1) SWord((p1)&0xFFFF)

static int doneonce=0;
static bool nofontkludge=true;
float MapScr::map_scale=.5;
SWord scanX,scanY;

struct OString
{
	char* text;
	ULong resID;
	OString(ULong id=-1L) {text=NULL;resID=id;}
};


inline Colour MAKE_SOFT_COL(ULong inp)
{
	if (inp==TEXT_NORMAL || inp==TEXT_GREYED || inp==TEXT_MAP_WHITE || inp==ICON_BACK_COLOUR)
		return WHITE;
	if (inp==TEXT_HI)
		return RED;
	if (inp==TEXT_MAP_BLACK)
		return BLACK;
	return WHITE;
}

static OString OSpeedText(IDS_INFOPANEL_SPEED);
static OString OAltitudeText(IDS_ALT);
static OString OMachText(IDS_MACH);
static OString OHdgText(IDS_HDG);
static OString OThrustText(IDS_THRUST);
static OString OFrameTimeText(IDS_FRAMES_SEC);
static OString ORangeText(IDS_INFOPANEL_RANGE);
static OString ORelBrgText(IDS_RELBRG);
static OString ORelAltText(IDS_RELALT);
static OString OUnitsMeters(IDS_M_SH);
static OString OUnitsFeet(IDS_FT_ABBR);
static OString OViewee(IDS_VIEWEE);
static OString OViewType(IDS_INFOPANEL_VIEW);
static OString OViewInfo2(IDS_VIEWREQUESTEDNOTAVAILABLE);
static OString OViewResetView(IDS_INFOPANEL_PLAYER);
static OString OViewEnemyView(IDS_ENEMY);
static OString OViewFrndView(IDS_FRIENDLY);
static OString OViewGrndTView(IDS_INFOPANEL_TARGET);
static OString OViewWayptView(IDS_INFOPANEL_WAYPOINT);
static OString OViewMessage(IDS_MESSAGE);
static OString OViewResetEnemyView=OViewEnemyView;
static OString OViewResetFrndView=OViewFrndView;
static OString OViewResetGrndTView=OViewGrndTView;
static OString OViewResetWayptView=OViewWayptView;
static OString OViewResetMessage=OViewMessage;
static OString OViewInsidePadTog(IDS_PADLOCK);
static OString OViewInsideFwdTog(IDS_INSIDELOOKFORWARDS);
static OString OViewInsideTog(IDS_INSIDE);
static OString OViewOutsidePadTog=OViewInsidePadTog;
static OString OViewOutsideTog(IDS_TRACK);
static OString OViewOutsideRevPadTog(IDS_OUTSIDEREVERSEDPADLOCK);
static OString OViewSatelliTog(IDS_SATELLITE);
static OString OViewNrSatelliTog(IDS_NEARSATELLITE);
static OString OViewFlyByTog(IDS_FLYBY);
static OString OViewChaseTog(IDS_CHASE);
static OString OViewCheatTog(IDS_NOCOCKPIT);


inline bool IsWide(SLong pwdth) {return pwdth<=640?false:true;}
inline bool IsExtraWide(SLong pwidth) {return pwidth<=800?false:true;}

static OString* OInfoPanelText[]=
{
	&OSpeedText,
	&OAltitudeText,
	&OMachText,
	&OHdgText,
	&OThrustText,
	&OFrameTimeText,
	&ORangeText,
	&ORelBrgText,
	&ORelAltText,
	&OUnitsMeters,
	&OUnitsFeet,
	&OViewee,
	&OViewType,
	&OViewInfo2,
	&OViewResetView,
	&OViewEnemyView,
	&OViewFrndView,
	&OViewGrndTView,
	&OViewWayptView,
	&OViewMessage,
	&OViewResetEnemyView,
	&OViewResetFrndView,
	&OViewResetGrndTView,
	&OViewResetWayptView,
	&OViewResetMessage,
	&OViewInsidePadTog,
	&OViewInsideFwdTog,
	&OViewInsideTog,
	&OViewOutsidePadTog,
	&OViewOutsideTog,
	&OViewOutsideTog,
	&OViewSatelliTog,
	&OViewNrSatelliTog,
	&OViewFlyByTog,
	&OViewChaseTog,
	&OViewCheatTog
};

const SLong _NumInfoTexts=sizeof(OInfoPanelText)/sizeof(OString*);

OString* listViewee[]=
{
	&OViewResetView,	
	&OViewEnemyView,	
	&OViewFrndView,	
	&OViewGrndTView,	
	&OViewWayptView,	
	&OViewMessage,
	&OViewResetEnemyView,
	&OViewResetFrndView,	
	&OViewResetGrndTView,
	&OViewResetWayptView,
	&OViewResetMessage
};

OString* listViewType[]=
{
	&OViewInsidePadTog,
	&OViewInsideTog,
	&OViewOutsidePadTog,
	&OViewOutsideTog,
	&OViewOutsideTog,
	&OViewSatelliTog,
	&OViewNrSatelliTog,
	&OViewFlyByTog,
	&OViewChaseTog,
	&OViewCheatTog,
	&OViewCheatTog,
	&OViewCheatTog,
	&OViewCheatTog
};

const SWord VIEWEE_LIST_SIZE=sizeof(listViewee)/sizeof(OString*);
const SWord VIEWTYPE_LIST_SIZE=sizeof(listViewType)/sizeof(OString*);

class COverlay OverLay;

struct COORDS2D
{
	SWord x,y;
};

struct RECT2D
{
	SWord x,y,w,h;
};

struct IMAGEDEF
{
  	ImageMapNumber imageNo;
	RECT2D mappingCoords;
};

struct ICON
{
	RECT2D hitBox;
	IMAGEDEF unclicked;
	IMAGEDEF clicked;
};

const SWord HALF_WIDTH_640=320;
const SWord HALF_HEIGHT_640=320;	
const Float FHALF_WIDTH=Float(HALF_WIDTH_640);

//const SWord INFO_LINE_HEIGHT=8;	//info bar height in pixels @ 640x480
const SWord REPLAY_BAR_WIDTH=640;	//replay bar width & height
const SWord REPLAY_BAR_HEIGHT=64;	//in pixels @ 640x480

const Colour REPLAY_BAR_COLOR=Colour(4);

//COORDS2D infoLine1[]=
//{
//	{0,0},{639,0},{639,INFO_LINE_HEIGHT-1},{0,INFO_LINE_HEIGHT-1}
//};

//COORDS2D infoLine2[]=
//{
//	{0,0},{639,0},{639,2*INFO_LINE_HEIGHT-1},{0,2*INFO_LINE_HEIGHT-1}
//};

//COORDS2D infoLine3[]=
//{
//	{0,0},{639,0},{639,3*INFO_LINE_HEIGHT-1},{0,3*INFO_LINE_HEIGHT-1}
//};

//COORDS2D replayBar[]=
//{
//	{0,0},{REPLAY_BAR_WIDTH-1,0},
//	{REPLAY_BAR_WIDTH-1,REPLAY_BAR_HEIGHT-1},{0,REPLAY_BAR_HEIGHT-1}
//};

const SWord ICON_WIDTH=32;
const SWord ICON_HEIGHT=32;
const SWord ICON_SPACING=ICON_WIDTH+2;

ICON replayPanel=
{	{ICON_SPACING*11,0,ICON_WIDTH*4,ICON_HEIGHT},
	{RPLYICNSNO,{0,ICON_HEIGHT*3,(4*ICON_WIDTH)-1,ICON_HEIGHT-1}},
	{RPLYICNSNO,{0,ICON_HEIGHT*3,(4*ICON_WIDTH)-1,ICON_HEIGHT-1}}
};

ICON replayIcon[]=
{
	//Mark start
	{	{0,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{0,0,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{0,0,ICON_WIDTH-1,ICON_HEIGHT-1}}
	},
	//goto start
	{	{ICON_SPACING,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{ICON_WIDTH,0,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{ICON_WIDTH,0,ICON_WIDTH-1,ICON_HEIGHT-1}}
	},
	//rewind
	{	{ICON_SPACING*2,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{2*ICON_WIDTH,0,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{2*ICON_WIDTH,0,ICON_WIDTH-1,ICON_HEIGHT-1}}
	},
	//pause
	{	{ICON_SPACING*3,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{3*ICON_WIDTH,0,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{3*ICON_WIDTH,0,ICON_WIDTH-1,ICON_HEIGHT-1}}
	},
	//fast fwd
	{	{ICON_SPACING*4,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{ICON_WIDTH,ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{ICON_WIDTH,ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}}
	},
	//goto end
	{	{ICON_SPACING*5,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{2*ICON_WIDTH,2*ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{2*ICON_WIDTH,2*ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}}
	},
	//mark end
	{	{ICON_SPACING*6,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{2*ICON_WIDTH,ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{ICON_WIDTH,2*ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}}
	},
	//load
	{	{ICON_SPACING*7,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{3*ICON_WIDTH,ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{3*ICON_WIDTH,ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}}
	},
	//save
	{	{ICON_SPACING*8,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{0,2*ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{0,2*ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}}
	},
	//eject
	{	{ICON_SPACING*9,0,ICON_WIDTH,ICON_HEIGHT},
		{RPLYICNSNO,{ICON_WIDTH,2*ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}},
		{RPLYICNSNO,{ICON_WIDTH,2*ICON_HEIGHT,ICON_WIDTH-1,ICON_HEIGHT-1}}
	}
};

bool fMouseDisabled;
int active_lines;

const SWord POINTER_WIDTH=32;
const SWord POINTER_HEIGHT=32;

//DeadCode PD 20Feb99 ICON mouseCursor=
//DeadCode PD 20Feb99 {
//DeadCode PD 20Feb99 	{0,0,POINTER_WIDTH,POINTER_HEIGHT},
//DeadCode PD 20Feb99 	{SQUEAKNO,{1,1,POINTER_WIDTH-2,POINTER_HEIGHT-2}},
//DeadCode PD 20Feb99 	{SQUEAKNO,{1,1,POINTER_WIDTH-2,POINTER_HEIGHT-2}}
//DeadCode PD 20Feb99 };

//const SWord INFO_POINT_COUNT=sizeof(infoLine1)/sizeof(COORDS2D);
//const SWord REPLAY_POINT_COUNT=sizeof(replayBar)/sizeof(COORDS2D);
//const SWord REPLAY_ICON_COUNT=sizeof(replayIcon)/sizeof(ICON);

struct TEXTDEF
{
 	COORDS2D pos;
	char* text;
};

//const SWord TOPLINE_Y=0;
SWord TOPLINE_Y=0;
SWord TOPLINE_Y2=0;
SWord TOPLINE_Y3=0;
SWord TOPLINE_YY=0;
const SWord SPEED_X=0;
const SWord MACH_X=100;	
const SWord ALTITUDE_X=170;	
const SWord HDG_X=287;
const SWord THRUST_X=399;

const SWord CHAR_WH=16;
const SWord CHAR_SPACING=8;

const SWord MESSAGE_X=0;
//const SWord MESSAGE_Y=INFO_LINE_HEIGHT;

const SWord VIEWEE_X=0;
const SWord VIEWTYPE_X=212-20;
//const SWord VIEWLINE_Y=2*INFO_LINE_HEIGHT;

const SWord VIEWEETXT_X=56;
const SWord VIEWTYPETXT_X=VIEWTYPE_X+40;

const SWord TRGRNGTXT_X=VIEWTYPETXT_X+60;
const SWord TRGBRGTXT_X=TRGRNGTXT_X+100;
const SWord TRGALTTXT_X=TRGBRGTXT_X+100;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawWholeScreen
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
void COverlay::DrawWholeScreen()
{

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawInfoBar
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
void COverlay::DrawInfoBar()
{
	POLYGON.SetPixelWidth(1);

	active_lines=0;

	if (pCurScr==&mapViewScr) 
		return;

	if (Key_Tests.KeyPress3d(HUDTOGGLE))
	{
		if (Save_Data.gamedifficulty[GD_HUDINSTACTIVE])
			Save_Data.gamedifficulty%=GD_HUDINSTACTIVE;
		else
			Save_Data.gamedifficulty|=GD_HUDINSTACTIVE;
	}
	if (Manual_Pilot.ControlledAC2)
	{
		if (Save_Data.gamedifficulty[GD_HUDINSTACTIVE])
		{
			DoThreat();
			DoArtHoriz();
		}
		DoCheatBox();
	}

	CrossHair();

	if (Save_Data.infoLineCount==0 && messageTimer==0)
		return;

	messageTimer-=pvp->RealFrameTime();
	if (messageTimer<0)
		messageTimer=0;

	COORDS2D* pointList;
	Save_Data.infoLineCount%=INFOLINESMAX;

	DoPointStruc dp;

	SLong box_height;
	
	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);

	fIsWide=IsWide(physicalWidth);

	if (!fIsWide)	box_height=10;
	else			box_height=18;

	longDistUnitStr=LdStr(Save_Data.dist.longabbr);
	shortDistUnitStr=LdStr(Save_Data.dist.mediumabbr);
	heightUnitStr=LdStr(Save_Data.alt.mediumabbr);
	speedUnitStr=LdStr(Save_Data.speed.perhrabbr);

	PreFormatViewText();

	if (TestMessageText())
	{
		SWord local_box_height=0;

		if (Save_Data.infoLineCount==1 || Save_Data.infoLineCount==3) 
		{
			local_box_height+=box_height;
		}
		else if (Save_Data.infoLineCount==2)
		{
			if (fTwoLines)
				local_box_height+=box_height<<1;
			else
				local_box_height+=box_height;
		}

		if (messageTimer && (Save_Data.gamedifficulty[GD_DISPLAYMESSAGES] || !otherText->IsEmpty()))
		{
			local_box_height+=box_height;
			if (otherText->IsEmpty() && !msgText[1].IsEmpty())	local_box_height+=box_height;
		}
		if (!Save_Data.fSoftware)
		{
			pw->DoSetGlobalAlpha(8);
			pw->DoSmokedGlassBox(0,physicalHeight-local_box_height,physicalWidth+1,local_box_height+1,GLASS_GREY_COLOUR);
			pw->DoSetGlobalAlpha(255);
			pw->DoSetFontColour(TEXT_MAP_WHITE);
		}
		else
		{
			POLYGON.DoSmokedGlassBox(0,physicalHeight-local_box_height,physicalWidth+1,local_box_height,BLACK);
			POLYGON.SetFontColour(WHITE);
		}
	}
	TOPLINE_Y=physicalHeight-box_height+1;
	TOPLINE_Y2=TOPLINE_Y-box_height;
	TOPLINE_Y3=TOPLINE_Y2-box_height;

	if (Save_Data.infoLineCount==2 && fTwoLines)
	{
		TOPLINE_YY=TOPLINE_Y;
		TOPLINE_Y-=box_height;
		TOPLINE_Y2-=box_height;
		TOPLINE_Y3-=box_height;
	}
	active_lines=Save_Data.infoLineCount!=0?1:0;

	if (messageTimer && (Save_Data.gamedifficulty[GD_DISPLAYMESSAGES] || !otherText->IsEmpty()))
	{
		if (!active_lines)
		{
			TOPLINE_Y3=TOPLINE_Y2;
			TOPLINE_Y2=TOPLINE_Y;
		}
		DrawMessageText();
		active_lines+=msgText[1].IsEmpty()?1:2;
	}

	switch (Save_Data.infoLineCount)
	{
		case 3:
		DrawWaypointText();
		break;
		case 2:
		DrawViewText();
		if (fTwoLines) active_lines++;
		break;
		case 1:
		DrawTopText();
		break;
	}
	delete[]longDistUnitStr;
	delete[]shortDistUnitStr;
	delete[]heightUnitStr;
	delete[]speedUnitStr;
	active_lines*=box_height;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawTopText
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
void COverlay::DrawTopText()
{
	//flight model code sets speed=>mph & height=>ft

	SLong speed2,altitude2; float speedey;

	altitude2=(altitude*305)/Save_Data.alt.mediummm;
//DeadCode CSB 23/06/99		speedey=(float(speed)/.5147)*Save_Data.speed.mmpcs2perhr;
	speedey = float(speed) * Save_Data.speed.mmpcs2perhr;	//CSB 23/06/99	
	speed2=SLong(speedey);

	const SLong doubleSpace=StrPixelLen2((char*)&"  ");
	const SLong digitWidth=StrPixelLen2((char*)&"8");
//DEAD	if (!fIsWide)	doubleSpace>>=1;
//	speed2=pvp->RealFrameTime();

	char temp[128];
	SWord xpos=0;
	SWord bupxpos=xpos;
	sprintf(temp,"%s: %3d%s",OSpeedText.text,speed2,speedUnitStr);
	PrintAt2(xpos,TOPLINE_Y,temp);

	xpos=bupxpos+StrPixelLen2(OSpeedText.text)+3*digitWidth+StrPixelLen2(speedUnitStr)+doubleSpace;
	bupxpos=xpos;
	sprintf(temp,"%s: %1.2f",OMachText.text,mach);
	PrintAt2(xpos,TOPLINE_Y,temp);

	xpos=bupxpos+StrPixelLen2(OMachText.text)+4*digitWidth+doubleSpace;
	bupxpos=xpos;
	sprintf(temp,"%s: %5d%s",OAltitudeText.text,altitude2,heightUnitStr);
	PrintAt2(xpos,TOPLINE_Y,temp);

	xpos=bupxpos+StrPixelLen2(OAltitudeText.text)+6*digitWidth+StrPixelLen2(heightUnitStr)+doubleSpace;
	bupxpos=xpos;
	sprintf(temp,"%s: %3d",OHdgText.text,heading);
	PrintAt2(xpos,TOPLINE_Y,temp);

	xpos=bupxpos+StrPixelLen2(OHdgText.text)+3*digitWidth+doubleSpace;
	sprintf(temp,"%s: %3d",OThrustText.text,thrust);
	PrintAt2(xpos,TOPLINE_Y,temp);
}

inline bool COverlay::TestMessageText()
{
	if (!otherText->IsEmpty()) return true;
	if (Save_Data.gamedifficulty[GD_DISPLAYMESSAGES])
	{
		if (messageTimer!=0 && !msgText[0].IsEmpty()) return true;
	}
 	if (Save_Data.infoLineCount!=0) return true;
 	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawMessageText
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
void COverlay::DrawMessageText()
{
	SWord xpos=MESSAGE_X;
	if (!otherText->IsEmpty())
	{
		PrintAt2(xpos,TOPLINE_Y2,const_cast<char*>(LPCTSTR(otherText[0])));
	}
	else if (!_MsgBuffer.nothingatall)
	{
		if (!msgText[1].IsEmpty())
		{
			PrintAt2(xpos,TOPLINE_Y3,const_cast<char*>(LPCTSTR(msgText[0])));
			xpos=MESSAGE_X;
			PrintAt2(xpos,TOPLINE_Y2,const_cast<char*>(LPCTSTR(msgText[1])));
		}
		else
			PrintAt2(xpos,TOPLINE_Y2,const_cast<char*>(LPCTSTR(msgText[0])));
	}
	else if (messageTimer!=0) messageTimer=0;
}

void COverlay::PreFormatViewText()
{
	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
	fIsWide=IsWide(physicalWidth);

	SLong	vieweeLen=0,
			viewTypeLen=0,
			i,j,
			totalLen;

	fTwoLines=false;

	if (Save_Data.infoLineCount!=2)
		return;

	const	SLong bigSpaceLen=StrPixelLen2("      ")>>1;
	const	SLong smallSpaceLen=bigSpaceLen>>1;
	const	SLong vieweeTextLen=StrPixelLen2(OViewee.text);
	const	SLong viewTypeTextLen=StrPixelLen2(OViewType.text);
	const	SLong rangeTextLen=StrPixelLen2(ORangeText.text);
	const	SLong relBrgTextLen=StrPixelLen2(ORelBrgText.text);
	const	SLong relAltTextLen=StrPixelLen2(ORelAltText.text);
	const	SLong rangeUnitsLen=(i=StrPixelLen2(shortDistUnitStr))>
								(j=StrPixelLen2(longDistUnitStr))?
								i:j;
	const	SLong relBrgUnitsLen=0;
	const	SLong relAltUnitsLen=StrPixelLen2(heightUnitStr);
	const	SLong rangeDigitLen=StrPixelLen2("00000000");
	const	SLong relBrgDigitLen=StrPixelLen2("0000");
	const	SLong relAltDigitLen=StrPixelLen2("00000000");

	//find the longest viewer & viewee strings

	for (i=VIEWEE_LIST_SIZE-1;i>=0;i--)
		if ((j=StrPixelLen2(listViewee[i]->text))>vieweeLen)
			vieweeLen=j;
	
	for (i=VIEWTYPE_LIST_SIZE-1;i>=0;i--)
		if ((j=StrPixelLen2(listViewType[i]->text))>viewTypeLen)
			viewTypeLen=j;

	totalLen =	vieweeTextLen+
				smallSpaceLen+
				vieweeLen+
				bigSpaceLen+
				viewTypeTextLen+
				smallSpaceLen+
				viewTypeLen;

	if (pvp->trackeditem2!=NULL && targRange!=0)
	{
		totalLen+=	bigSpaceLen+
					rangeTextLen+
					smallSpaceLen+
					rangeDigitLen+
					rangeUnitsLen+
					bigSpaceLen+
					relAltTextLen+
					smallSpaceLen+
					relAltDigitLen+
					relAltUnitsLen+
					bigSpaceLen+
					relBrgTextLen+
					smallSpaceLen+
					relBrgDigitLen+
					relBrgUnitsLen;

		if (totalLen>physicalWidth)
			fTwoLines=true;			
	}
	viewee_x=0;

	viewtype_x=vieweeTextLen+smallSpaceLen+vieweeLen+bigSpaceLen;

	viewrange_x=fTwoLines?0:viewtype_x+viewTypeTextLen+smallSpaceLen+viewTypeLen+bigSpaceLen;

	viewalt_x=viewrange_x+rangeTextLen+smallSpaceLen+rangeDigitLen+rangeUnitsLen+bigSpaceLen;

	viewbrg_x=viewalt_x+relAltTextLen+smallSpaceLen+relAltDigitLen+relAltUnitsLen+bigSpaceLen;
}

void COverlay::DrawWaypointText()
{
	AirStrucPtr ac=Manual_Pilot.ControlledAC2;

	if (!ac) return;

	COORDS3D target;
	COORDS3D source;

	char str[128],rangestr[128],relbrgstr[128],relaltstr[128];

	WayPointPtr waypt=ac->waypoint;

	if (waypt)
	{
		target=*::FindDesPos(waypt);

		ULong resid;

		switch (waypt->wpname)
		{
		case WPNAME_None:		resid=IDS_L_MAIN_WP_GAP; break;
		case WPNAME_Rendevous:	resid=IDS_MAIN_WP_RENDEVOUS; break;
		case WPNAME_Ingress:	resid=IDS_MAIN_WP_INGRESS; break;
		case WPNAME_Target:		resid=IDS_MAIN_WP_TARGET; break;
		case WPNAME_Regroup:	resid=IDS_MAIN_WP_REGROUP; break;
		case WPNAME_Egress:		resid=IDS_MAIN_WP_EGRESS; break;
		case WPNAME_Disperse:	resid=IDS_MAIN_WP_DISPERSE; break;
		case WPNAME_Landing:	resid=IDS_MAIN_WP_LAND; break;
		default:				resid=IDS_L_MAIN_WP_GAP; break;
		}
		char *tmp=LdStr(resid);
		if (waypt->wpnum!=0)	sprintf(str,"%s(%d)",tmp,waypt->wpnum);
		else					sprintf(str,"%s",tmp);
		delete[]tmp;
	}
	else if (ac->ai.homebase)
	{
		target=ac->ai.homebase->World;
		ULong resid=IDS_MAIN_WP_LAND;
		char *tmp=LdStr(resid);
		sprintf(str,"%s",tmp);
	}
	else return;

	source=ac->World;

	SLong	range,relalt;
	ANGLES	relbrg,temp;
	Math_Lib.Intercept(target.X-source.X,target.Y-source.Y,target.Z-source.Z,range,relbrg,temp);
	relbrg=relbrg-ac->hdg;
	relalt=target.Y-source.Y;

	//resource ids
	//	IDS_RELALT
	//	IDS_RELBRG
	//	IDS_INFOPANEL_RANGE

	//scaling for units...

	char *trelbrg=LdStr(IDS_RELBRG);
	SLong rb=((SLong(relbrg)&0xFFFF)*360)>>16;
	sprintf(relbrgstr,"%s:%03d",trelbrg,rb);
	delete[]trelbrg;

	SLong r=range/Save_Data.dist.longcm;
	char *trange=LdStr(IDS_INFOPANEL_RANGE);
	if (!r)
	{
		char *tdu=LdStr(Save_Data.dist.mediumabbr);
		r=(range*10)/Save_Data.dist.mediummm;
		sprintf(rangestr,"%s:%d%s",trange,r,tdu);
		delete[]tdu;
	}
	else if (r>=100)
	{
		char *tdu=LdStr(Save_Data.dist.longabbr);
//DeadCode PD 09Sep99 		r=range;
		sprintf(rangestr,"%s:%d%s",trange,r,tdu);
		delete[]tdu;
	}
	else
	{
		char *tdu=LdStr(Save_Data.dist.longabbr);
		r=(range*10)/Save_Data.dist.longcm;
		sprintf(rangestr,"%s:%.1f%s",trange,float(r)/10,tdu);
		delete[]tdu;
	}
	delete[]trange;

	char *trelalt=LdStr(IDS_RELALT);
	char *tau=LdStr(Save_Data.alt.mediumabbr);
	r=(relalt*10)/Save_Data.alt.mediummm;
	sprintf(relaltstr,"%s: %d%s",trelalt,r,tau);
	delete[]tau;
	delete[]trelalt;

	//str => waypoint text
	//relaltstr => wp rel alt text
	//relbrgstr => wp rel brg text
	//rangestr => wp range text

	SWord half=(fIsWide?16:8)<<3;
	UWord mask=~UWord(half-1);

	SWord pos_y=TOPLINE_Y;
	SWord pos_x=0;
	PrintAt2(pos_x,pos_y,str);
	pos_x=(pos_x&mask)+half;
	half>>=1;
	mask=0x8000+(mask>>1);
	PrintAt2(pos_x,pos_y,rangestr);
	pos_x=(pos_x&mask)+half;
	PrintAt2(pos_x,pos_y,relbrgstr);
	pos_x=(pos_x&mask)+half;
	PrintAt2(pos_x,pos_y,relaltstr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawViewText
//Author		Paul.   
//Date			Fri 5 Jun 1998
//------------------------------------------------------------------------------
void COverlay::DrawViewText()
{
	char str[256];
	SWord pos_y=TOPLINE_Y;

	sprintf(str,"%s %s",OViewee.text,listViewee[pvp->viewnum.viewtarg]->text);
	PrintAt2(viewee_x,pos_y,str);

	sprintf(str,"%s %s",OViewType.text,listViewType[pvp->viewnum.viewmode]->text);
	PrintAt2(viewtype_x,pos_y,str);

	if (pvp->trackeditem2!=NULL && targRange!=0)
	{
		if (fTwoLines) pos_y=TOPLINE_YY;

		//display target range,rel bearing & rel alt
		SLong trange,talt,tbrg;
		char *distUnits=longDistUnitStr;

		//try converting range to large units (km or miles)
		trange=targRange/Save_Data.dist.longcm;

		if (!trange)
		{
			//try meters or yards instead
			distUnits=shortDistUnitStr;
			trange=(targRange*10)/Save_Data.dist.mediummm;
			sprintf(str,"%s: %d%s",ORangeText.text,trange,distUnits);
		}
		else if (trange>=100)
		{
			sprintf(str,"%s: %d%s",ORangeText.text,trange,distUnits);
		}
		else
		{
			trange=(targRange*10)/Save_Data.dist.longcm;
			sprintf(str,"%s: %.1f%s",ORangeText.text,float(trange)/10,distUnits);
		}
		PrintAt2(viewrange_x,pos_y,str);

		talt=(targRelAlt*10)/Save_Data.alt.mediummm;
		tbrg=((SLong(targRelBrg)&0xFFFF)*360)>>16;

		sprintf(str,"%s: %03d",ORelBrgText.text,tbrg);
		PrintAt2(viewbrg_x,pos_y,str);

		sprintf(str,"%s: %d%s",ORelAltText.text,talt,heightUnitStr);
		PrintAt2(viewalt_x,pos_y,str);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawReplayBar
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
void COverlay::DrawReplayBar()
{
//	COORDS2D* pointList=replayBar;
//
//	POLYGON.createpoly(REPLAY_BAR_COLOR);
//
//	DoPointStruc dp;
//
//	for (int x=0;x<REPLAY_POINT_COUNT;x++){
//		dp.bodyx.f=Float(pointList[x].x-HALF_WIDTH_640)/FHALF_WIDTH;
//		dp.bodyy.f=Float(HALF_HEIGHT_640-pointList[x].y)/FHALF_WIDTH;
//		dp.bodyz.f=Float(1);
//		POLYGON.createvert(dp);
//	}
//	POLYGON.drawpoly();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawReplayIcons
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
void COverlay::DrawReplayIcons(bool pausedFlag)
{
//	ICON* iconList;
//	if (pausedFlag)	iconList=replayIcon;
//	else			iconList=replayIcon;

//	for (int i=0;i<REPLAY_ICON_COUNT;iconList++,i++) RenderIcon(*iconList);

	//And the progress bar
//	RenderIcon(replayPanel);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderIcon
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
void COverlay::RenderIcon(ICON& icn,bool clicked)
{
	//position of the icon on screen is taken from the
	//hit box def
	//mapping coordinates are from the unclicked image def

	IMAGEDEF* pid;

	if (clicked)	pid=&icn.clicked;
	else			pid=&icn.clicked;//unclicked;

	IMAGEDEF& id=*pid;

	POLYGON.createpoly(id.imageNo);

	DoPointStruc dp;

	RECT2D& rect=id.mappingCoords;

	SWord u,v;

	//always 4 points...
	dp.bodyx.f=Float(icn.hitBox.x-HALF_WIDTH_640)/FHALF_WIDTH;
	dp.bodyy.f=Float(HALF_HEIGHT_640-icn.hitBox.y)/FHALF_WIDTH;
	dp.bodyz.f=Float(1);
	u=rect.x;
	v=rect.y;
	POLYGON.createvert(dp,u,v);

	dp.bodyx.f=Float(icn.hitBox.x+icn.hitBox.w-1-HALF_WIDTH_640)/FHALF_WIDTH;
	dp.bodyy.f=Float(HALF_HEIGHT_640-icn.hitBox.y)/FHALF_WIDTH;
	dp.bodyz.f=Float(1);
	u=rect.x+rect.w;
	v=rect.y;
	POLYGON.createvert(dp,u,v);

	dp.bodyx.f=Float(icn.hitBox.x+icn.hitBox.w-1-HALF_WIDTH_640)/FHALF_WIDTH;
	dp.bodyy.f=Float(HALF_HEIGHT_640-icn.hitBox.y-icn.hitBox.h+1)/FHALF_WIDTH;
	dp.bodyz.f=Float(1);
	u=rect.x+rect.w;
	v=rect.y+rect.h;
	POLYGON.createvert(dp,u,v);

	dp.bodyx.f=Float(icn.hitBox.x-HALF_WIDTH_640)/FHALF_WIDTH;
	dp.bodyy.f=Float(HALF_HEIGHT_640-icn.hitBox.y-icn.hitBox.h+1)/FHALF_WIDTH;
	dp.bodyz.f=Float(1);
	u=rect.x;
	v=rect.y+rect.h;
	POLYGON.createvert(dp,u,v);

	POLYGON.drawpoly();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReplayIconHitTest
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
//SWord COverlay::ReplayIconHitTest(SWord x,SWord y)
//{
//	ICON* iconList=replayIcon;
//	for (int i=0;i<REPLAY_ICON_COUNT;iconList++,i++)
//	{
//		if (x>=iconList->hitBox.x &&
//			x<iconList->hitBox.x+iconList->hitBox.w &&
//			y>=iconList->hitBox.y &&
//			y<iconList->hitBox.y+iconList->hitBox.h)
//			return SWord(i);
//	}
//	return SWord(-1);
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrintAt
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
void COverlay::PrintAt(SWord x,SWord y,char* str)
{
//	SWord this_y=fIsWide?y<<1:y;
  //	if (str)
	//{
//		char c;
  //		while ((c=*str++)!=0) PutC(x,this_y,c);
	//}
//	y=fIsWide?this_y>>1:this_y;
}

void COverlay::PrintAt2(SWord& x,SWord& y,char* str)
{
//DeadCode RJS 05Dec00 	if (str)
//DeadCode RJS 05Dec00 	{
//DeadCode RJS 05Dec00 		char c;
//DeadCode RJS 05Dec00 		while ((c=*str++)!=0 && x<physicalWidth) PutC(x,y,c);
//DeadCode RJS 05Dec00 	}
 	if (str)													//RJS 05Dec00
 	{
		const unsigned char* ustr=(const unsigned char*)str;

		while (*ustr)
		{
			PutC3(x,y,_mbsnextc(ustr));
			ustr=_mbsinc(ustr);
		}
	}
}

static UByte bigWidths[]=
{8,	2,	5,	8,	5,	8,	9,	2,
2,	2,	7,	7,	2,	7,	2,	10,
6,	3,	7,	6,	8,	6,	6,	7,
6,	6,	2,	2,	5,	6,	5,	6,
10,	10,	7,	7,	8,	7,	6,	8,
7,	2,	4,	7,	7,	9,	8,	8,
7,	8,	8,	7,	8,	8,	9,	11,
11,	7,	10,	3,	10,	3,	7,	7,
2,	7,	7,	6,	7,	6,	6,	7,
7,	2,	2,	7,	2,	12,	7,	7,
7,	9,	5,	6,	4,	7,	7,	12,
8,	7,	7,	5,	2,	5,	3,	5,
1,	1,	1,	1,	1,	1,	1,	1,
1,	1,	1,	1,	1,	1,	1,	1,
1,	1,	1,	1,	1,	1,	1,	1,
1,	1,	1,	1,	1,	1,	1,	1,
1,	2,	1,	1,	1,	1,	1,	1,
1,	9,	1,	1,	1,	1,	1,	1,
1,	1,	1,	1,	1,	1,	1,	1,
1,	1,	1,	1,	1,	1,	1,	6,
10,	10,	11,	12,	10,	10,	11,	7,
6,	6,	6,	6,	3,	3,	3,	3,
9,	8,	8,	8,	8,	8,	8,	6,
8,	8,	8,	8,	8,	7,	7,	7,
7,	7,	7,	9,	7,	7,	11,	6,
6,	6,	6,	6,	3,	2,	3,	3,
7,	7,	7,	7,	7,	7,	7,	6,
7,	7,	7,	7,	7,	7,	7,	7,
1,	1,	1,	1,	1,	1,	1,	1,
1,	1,	1,	1,	1,	1,	1,	1,
1,	1,	1,	1,	1,	1,	1,	1,
1,	1,	1,	1,	1,	1,	1,	1};

//DeadCode PD 10Jun99 {8,	2,	5,	8,	5,	8,	9,	2,
//DeadCode PD 10Jun99 2,	2,	7,	7,	2,	7,	2,	10,
//DeadCode PD 10Jun99 6,	3,	7,	6,	8,	6,	6,	7,
//DeadCode PD 10Jun99 6,	6,	2,	2,	5,	6,	5,	6,
//DeadCode PD 10Jun99 10,	10,	7,	7,	8,	7,	6,	8,
//DeadCode PD 10Jun99 7,	2,	4,	7,	7,	9,	8,	8,
//DeadCode PD 10Jun99 7,	8,	8,	7,	8,	8,	9,	11,
//DeadCode PD 10Jun99 11,	7,	10,	3,	10,	3,	7,	7,
//DeadCode PD 10Jun99 2,	7,	7,	6,	7,	6,	6,	7,
//DeadCode PD 10Jun99 7,	2,	2,	7,	2,	12,	7,	7,
//DeadCode PD 10Jun99 7,	9,	5,	6,	4,	7,	7,	12,
//DeadCode PD 10Jun99 8,	7,	7,	5,	2,	5,	3,	5,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	9,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 13,	10,	11,	12,	9,	11,	7,	6,
//DeadCode PD 10Jun99 6,	6,	6,	3,	3,	3,	3,	9,
//DeadCode PD 10Jun99 8,	8,	8,	8,	8,	8,	6,	8,
//DeadCode PD 10Jun99 8,	8,	8,	8,	7,	7,	7,	7,
//DeadCode PD 10Jun99 7,	7,	9,	7,	7,	11,	6,	6,
//DeadCode PD 10Jun99 6,	6,	6,	3,	3,	3,	3,	7,
//DeadCode PD 10Jun99 7,	7,	7,	7,	7,	7,	6,	7,
//DeadCode PD 10Jun99 7,	7,	7,	7,	7,	7,	7,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1,
//DeadCode PD 10Jun99 1,	1,	1,	1,	1,	1,	1,	1};


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StrPixelLen
//Author		Paul.   
//Date			Thu 17 Dec 1998
//------------------------------------------------------------------------------
SLong COverlay::StrPixelLen(char* pstr)
{
	SLong retVal=0;						//RJS 14Jan98
	if (pstr)							//RJS 14Jan98
	{
		if (!fIsWide)
			return 7*strlen(pstr);

		while (*pstr)
		{
	 		retVal+=bigWidths[(*pstr)-32];
			pstr++;
		}
	}
	return retVal;
}
SLong COverlay::StrPixelLen2(char* pstr)
{
	SLong retVal=0;						//RJS 14Jan98
	if (pstr)							//RJS 14Jan98
	{
		if (!fIsWide)
			return 8*strlen(pstr);

		while (*pstr)
		{
	 		retVal+=bigWidths[(*pstr)-32]+1;
			pstr++;
		}
	}
	return retVal;
}

void COverlay::ChopStr(CString& in,CString& out)
{
	out="";
	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
	fIsWide=IsWide(physicalWidth);
	in.TrimRight();
	in.TrimLeft();
	while (StrPixelLen(const_cast<char*>(LPCTSTR(in)))>=physicalWidth)
	{
		int l=in.GetLength();
		int i=in.ReverseFind(' ');
		if (i>=0)
		{
			out=in.Right(l-i)+out;
			in=in.Left(i);
			in.TrimRight();
		}
		else break;
	}
	if (!out.IsEmpty()) out.TrimLeft();
}

void COverlay::MakeDotDotDot(CString& in)
{
	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
	fIsWide=IsWide(physicalWidth);
	in.TrimLeft();
	in.TrimRight();
	if (StrPixelLen(const_cast<char*>(LPCTSTR(in)))>=physicalWidth)
	{
		CString temp;
		do
		{
			in=in.Left(in.GetLength()-1);
			in.TrimRight();
			temp=in+"...";
		}
		while (StrPixelLen(const_cast<char*>(LPCTSTR(temp)))>=physicalWidth);
		in=temp;
	}
}

SWord COverlay::CalcTargIndex(CString& in)
{
	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
	fIsWide=IsWide(physicalWidth);
	in.TrimLeft();
	in.TrimRight();
	if (StrPixelLen(const_cast<char*>(LPCTSTR(in)))<physicalWidth)
		return 0;
	for (SLong i=0;i<in.GetLength();i++)
	{
		CString temp=in.Right(in.GetLength()-i);
		if (StrPixelLen(const_cast<char*>(LPCTSTR(temp)))<physicalWidth)
		{
			if (i+3<in.GetLength()) i+=3;
			break;
		}
	}
	return i<in.GetLength()?i:0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PutC
//Author		Paul    
//Date			Thu 4 Jun 1998
//------------------------------------------------------------------------------
void COverlay::PutC(SWord& x,SWord& y,unsigned char c)
{
	//lo res version only displays upper case chars
	SWord extra=0;	//nofontkludge?0:1;

	UByte tWidth=8;
	SWord this_y;

	if (!fIsWide && c>='a' && c<='z') c=c-'a'+'A';
	else tWidth=bigWidths[c-32]+1+extra;

 	c-=32;		//1st 32 chars not included
 
 	SWord ou,ov;
 	SWord cWidth,pWidth,cHeight,pHeight;
 	ImageMapNumber fontNo;
 
	SWord oldTQ=pw->DoForceTQ(4);
	bool oldMip=pw->DoSetMipMap(false);

	ImageMapDesc* pmap;

	this_y=y;

	if (!fIsWide)
	{
 		ou=(SWord(c)&0x0F)<<3;
		ou++;
 		ov=(SWord(c)&0xF0)>>1;
 		cWidth=7+extra;		//8;
 		cHeight=8+extra;
 		pWidth=cWidth;
		pHeight=cHeight;
		fontNo=FONTNO;
		pmap=Image_Map.GetImageMapPtr(fontNo);
	}
	else
	{
 		ou=(SWord(c)&0x0F)<<4;
		ou++;
 		ov=(SWord(c)&0xF0);
 		cWidth=tWidth;
 		cHeight=17+extra;	//16;
 		pWidth=cWidth;
		pHeight=cHeight;
		fontNo=FONTNO;
		winmode_bpp=8;
		pmap=Image_Map.GetImageMapPtr(fontNo);
		winmode_bpp=16;
	}
 
 	DoPointStruc dp[4];
 
 	dp[0].bodyx.f=Float(x);
 	dp[0].bodyy.f=Float(this_y);
 	dp[1].bodyx.f=Float(x+pWidth-1);
 	dp[1].bodyy.f=Float(this_y);
 	dp[2].bodyx.f=Float(x+pWidth-1);
 	dp[2].bodyy.f=Float(this_y+pHeight-1);	//CHAR_WH-2);
 	dp[3].bodyx.f=Float(x);
 	dp[3].bodyy.f=Float(this_y+pHeight-1);	//CHAR_WH-2);

	dp[0].ix=ou;
 	dp[0].iy=ov;
 	dp[1].ix=ou+cWidth-1;
 	dp[1].iy=ov;
 	dp[2].ix=ou+cWidth-1;
 	dp[2].iy=ov+cHeight-1;
 	dp[3].ix=ou;
 	dp[3].iy=ov+cHeight-1;
 
	if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap,dp);
	else						pw->DoPutC(pmap,dp);
 
 	x+=pWidth;
 
 	if (x>=physicalWidth) x=0,y+=pHeight;	//CHAR_WH;
 	if (y>=physicalHeight) y=0;

	pw->DoForceTQ(oldTQ);
	pw->DoSetMipMap(oldMip);

	if (doneonce==0)
	{
		scanX=SWord(dp[0].bodyx.f);
		scanY=SWord(dp[2].bodyy.f);
		doneonce=1;
	}
}

void COverlay::ClippedPutC(DoPointStruc* idp,ImageMapDescPtr pmap,FRect& clip)
{
	DoPointStruc dp[4];

	for (int i=0;i<4;dp[i++]=*idp++);

	//check for completely clipped off screen

	if (dp[0].bodyx.f>=clip.right ||
		dp[0].bodyy.f>=clip.bottom ||
		dp[2].bodyx.f<=clip.left ||
		dp[2].bodyy.f<=clip.top)
		return;

	//check for any clipping at all

	if (!(dp[0].bodyx.f>=clip.left && 
		dp[1].bodyx.f<=clip.right &&
		dp[0].bodyy.f>=clip.top &&
		dp[3].bodyy.f<=clip.bottom))
	{
		//clip against left edge
		if (dp[0].bodyx.f<clip.left)
		{
			Float frac=(clip.left-dp[0].bodyx.f)/(dp[1].bodyx.f-dp[0].bodyx.f);
			dp[0].bodyx.f=dp[3].bodyx.f=clip.left;
			frac=Float(dp[1].ix-dp[0].ix)*frac;
			dp[0].ix=dp[3].ix=dp[0].ix+SWord(frac);
		}

		//clip against right edge
		if (dp[1].bodyx.f>clip.right)
		{
			Float frac=(clip.right-dp[0].bodyx.f)/(dp[1].bodyx.f-dp[0].bodyx.f);
			dp[1].bodyx.f=dp[2].bodyx.f=clip.right;
			frac=Float(dp[1].ix-dp[0].ix)*frac;
			dp[1].ix=dp[2].ix=dp[1].ix+SWord(frac);
		}

		//clip against bottom edge
		if (dp[2].bodyy.f>clip.bottom)
		{
			Float frac=(clip.bottom-dp[0].bodyy.f)/(dp[3].bodyy.f-dp[0].bodyy.f);
			dp[2].bodyy.f=dp[3].bodyy.f=clip.bottom;
			frac=Float(dp[3].iy-dp[0].iy)*frac;
			dp[2].iy=dp[3].iy=dp[0].iy+SWord(frac);
		}

		//clip against top edge
		if (dp[0].bodyy.f<clip.top)
		{
			Float frac=(clip.top-dp[0].bodyy.f)/(dp[3].bodyy.f-dp[0].bodyy.f);
			dp[0].bodyy.f=dp[1].bodyy.f=clip.top;
			frac=Float(dp[3].iy-dp[0].iy)*frac;
			dp[0].iy=dp[1].iy=dp[0].iy+SWord(frac);
		}
	}
	if (!Save_Data.fSoftware)	pw->DoSetFontColour(TEXT_MAP_WHITE);
	else						POLYGON.SetFontColour(WHITE);
	SWord oldTQ=pw->DoForceTQ(4);
	bool oldMip=pw->DoSetMipMap(false);
	if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap,dp);
	else						pw->DoPutC(pmap,dp);
	pw->DoForceTQ(oldTQ);
	pw->DoSetMipMap(oldMip);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrintIcon
//Author		Paul.   
//Date			Wed 17 Feb 1999
//------------------------------------------------------------------------------
void COverlay::PrintIcon(SLong sx,SLong sy,SLong sw,SLong sh,UWord iconIndex)
{
 	SWord ou,ov;
 	SWord cWidth,cHeight;

 	ImageMapNumber iconNo=(ImageMapNumber)currIcons[iconIndex].imageMapNo;
 
	SWord oldTQ=pw->DoForceTQ(4);
	bool oldMip=pw->DoSetMipMap(false);

	ImageMapDesc* pmap;

	ou=currIcons[iconIndex].x;
	ov=currIcons[iconIndex].y;
	cWidth=currIcons[iconIndex].w;
	cHeight=currIcons[iconIndex].h;
	pmap=Image_Map.GetImageMapPtr(iconNo);
 
 	DoPointStruc dp[4];
 
 	dp[0].bodyx.f=Float(sx);
 	dp[0].bodyy.f=Float(sy);
 	dp[0].ix=ou;
 	dp[0].iy=ov;
 	dp[1].bodyx.f=Float(sx+sw);
 	dp[1].bodyy.f=Float(sy);
 	dp[1].ix=ou+cWidth;
 	dp[1].iy=ov;
 	dp[2].bodyx.f=Float(sx+sw);
 	dp[2].bodyy.f=Float(sy+sh);
 	dp[2].ix=ou+cWidth;
 	dp[2].iy=ov+cHeight;
 	dp[3].bodyx.f=Float(sx);
 	dp[3].bodyy.f=Float(sy+sh);
 	dp[3].ix=ou;
 	dp[3].iy=ov+cHeight;
 
	if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap,dp);
	else						pw->DoPutC(pmap,dp);
	pw->DoForceTQ(oldTQ);
	pw->DoSetMipMap(oldMip);
}

////////////////////////////////////////////////////////////////////////////////
//
//	CODE STARTS HERE FOR 2D SCREENS...
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderInfoPanel
//Author		Paul.   
//Date			Fri 5 Jun 1998
//------------------------------------------------------------------------------
void COverlay::RenderInfoPanel()
{
	if (pvp==NULL|pw==NULL) return;

	DrawInfoBar();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderMapPad
//Author		Paul.   
//Date			Wed 18 Nov 1998
//------------------------------------------------------------------------------
void COverlay::RenderMapPad()
{
	if (pvp==NULL|pw==NULL|Save_Data.infoLineCount==0) return;

	DrawMapPad();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawMapPad
//Author		Paul.   
//Date			Wed 18 Nov 1998
//------------------------------------------------------------------------------
void COverlay::DrawMapPad()
{
}

COORDS3D last;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DisplayProfileData
//Author		Paul.   
//Date			Wed 18 Nov 1998
//------------------------------------------------------------------------------
void COverlay::DisplayProfileData(bool fDisplay)
{
	static char profileText[]="Profile Data";
	static char minText[]="Max Frames/sec: %-#6.2f";
	static char maxText[]="Min Frames/sec: %-#6.2f";
	static char aveText[]="Ave Frames/sec: %-#6.2f";
	static char curText[]="Cur Frames/sec: %-#6.2f";
	static char textRemadeText[]="Textures remade: %4d";

	const int max_frames=64;
	static int frames=0;
	static int curr_insert_pos=0;
	static int frec[max_frames];

	static char tempStr[128];

	int this_frame_time=pvp->RealFrameTime();
	frec[curr_insert_pos++]=this_frame_time;
	if (curr_insert_pos==max_frames) curr_insert_pos=0;
	if (frames<max_frames) frames++;

	//calculate min,max,average frame time over last 'max_frames' frames

	int min_frame,max_frame,ave_frame;

	min_frame=10000;
	max_frame=0;
	ave_frame=0;

	for (int i=0;i<frames;i++)
	{
		ave_frame+=frec[i];
		if (frec[i]<min_frame) min_frame=frec[i];
		if (frec[i]>max_frame) max_frame=frec[i];
	}
	
	float fp_ave=100./(float(ave_frame)/float(frames));
	float fp_min=100./float(min_frame);
	float fp_max=100./float(max_frame);
	float fp_cur=100./float(this_frame_time);

	if (curr_insert_pos==0) averageFrameRate=SLong(100.*fp_ave);

	if (fDisplay)
	{
		//prepare to display the data

		pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);

		fIsWide=IsWide(physicalWidth);

		if (!Save_Data.fSoftware)
		{
			pw->DoSetGlobalAlpha(8);
			pw->DoSmokedGlassBox((physicalWidth>>2),(physicalHeight>>2),(physicalWidth>>1),(physicalHeight>>1),GLASS_COLOUR);
			pw->DoSetGlobalAlpha(255);
		}
		else POLYGON.DoSmokedGlassBox((physicalWidth>>2),(physicalHeight>>2),(physicalWidth>>1),(physicalHeight>>1),BLACK);

		int lineHeight=fIsWide?16:8;

		SWord cx=(physicalWidth>>2)+lineHeight;
		SWord cy=fIsWide?(physicalHeight>>3)+lineHeight:(physicalHeight>>2)+lineHeight;

		//PrintAt(cx,cy,profileText);
		cy+=lineHeight+lineHeight;
		sprintf(tempStr,minText,fp_min);
		//PrintAt(cx,cy,tempStr);
		cy+=lineHeight;
		sprintf(tempStr,maxText,fp_max);
		//PrintAt(cx,cy,tempStr);
		cy+=lineHeight;
		sprintf(tempStr,aveText,fp_ave);
		//PrintAt(cx,cy,tempStr);
		cy+=lineHeight;
		sprintf(tempStr,curText,fp_cur);
		//PrintAt(cx,cy,tempStr);

	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Prefs3D
//Author		Paul.   
//Date			Thu 19 Nov 1998
//------------------------------------------------------------------------------

struct SOption
{
	char* optionText;
	bool enabled;
	int selection;
	char** selectionList;
};

static char* OnOff[]={"On","Off",NULL};
static char* PoorLowMedHigh[]={"Poor","Low","Medium","High",NULL};
static char* MinMax[]={"Minimum","Maximum",NULL};
static char* MinMaxAuto[]={"Minimum","Maximum","Auto",NULL};

//3D Hardware related options...

static SOption OptTransp={"Transparency Effects: ",true,0,OnOff};
static SOption OptTextureQuality={"Texture Quality: ",true,0,PoorLowMedHigh};

//General 3D options

static SOption OptTrees={"Trees: ",false,0,OnOff};
static SOption OptHorizonFade={"Horizon Fade: ",false,0,MinMax};
static SOption OptAutoLand={"Altitude Detail: ",false,0,MinMaxAuto};

static SOption* gameOptions[]=
{
	&OptTransp,
	&OptTextureQuality,
	&OptTrees,
	&OptHorizonFade,
	&OptAutoLand,
};

static int Selection=3;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Prefs3D
//Author		Paul.   
//Date			Thu 19 Nov 1998
//------------------------------------------------------------------------------
void COverlay::Prefs3D()
{
	if (pvp==NULL|pw==NULL) return;

	static char tempStr[128];

	const int num_options=sizeof(gameOptions)/sizeof(SOption*);

	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);

	fIsWide=IsWide(physicalWidth);

	if (!Save_Data.fSoftware)
	{
		pw->DoSetFontColour(TEXT_NORMAL);
		pw->DoSetGlobalAlpha(8);
		pw->DoSmokedGlassBox((physicalWidth>>2),(physicalHeight>>2),(physicalWidth>>1),(physicalHeight>>1),GLASS_COLOUR);
		pw->DoSetGlobalAlpha(255);
	}
	else POLYGON.DoSmokedGlassBox((physicalWidth>>2),(physicalHeight>>2),(physicalWidth>>1),(physicalHeight>>1),BLACK);

	int lineHeight=fIsWide?10:8;

	SWord cx=(physicalWidth>>2)+lineHeight;
	SWord cy=fIsWide?(physicalHeight>>3)+lineHeight:(physicalHeight>>2)+lineHeight;

	//PrintAt(cx,cy,"Detail Settings");

	cy+=lineHeight+lineHeight;

	for (SLong i=0;i<num_options;i++)
	{
		if (!gameOptions[i]->enabled)	pw->DoSetFontColour(TEXT_GREYED);
		else if (i==Selection)			pw->DoSetFontColour(TEXT_HI);
		else							pw->DoSetFontColour(TEXT_NORMAL);

		sprintf(tempStr,"%s%s",gameOptions[i]->optionText,gameOptions[i]->selectionList[gameOptions[i]->selection]);
		//PrintAt(cx,cy,tempStr);
		cy+=lineHeight;
	}
	cy+=lineHeight;

	if (Selection==num_options)	pw->DoSetFontColour(TEXT_HI);
	else						pw->DoSetFontColour(TEXT_NORMAL);
	//PrintAt(cx,cy,"Okay");
	cx+=lineHeight*10;

	if (Selection==num_options+1)	pw->DoSetFontColour(TEXT_HI);
	else							pw->DoSetFontColour(TEXT_NORMAL);
	//PrintAt(cx,cy,"Cancel");

	//key tests here!

	bool selectCurrent=false;

	if (Key_Tests.KeyPress3d(ELEVATOR_FORWARD))
	{
		Selection--;
		if (Selection<0) Selection=num_options+1;	//move to cancel
		if (Selection<num_options)
			while (gameOptions[Selection]->enabled==false)
			{
				Selection--;
				if (Selection<0)
				{
					Selection=num_options+1;
					break;
				}
			}
	}
	else if (Key_Tests.KeyPress3d(ELEVATOR_BACK))
	{
		Selection++;
		if (Selection>num_options+1) Selection=0;
		for (;Selection<num_options && gameOptions[Selection]->enabled==false;Selection++);
	}
	else if (Key_Tests.KeyPress3d(DROPBOMB) || Key_Tests.KeyPress3d(SHOOT))
		selectCurrent=true;

	if (selectCurrent)
	{
		if (Selection<num_options)
		{
			SOption* selectedOption=gameOptions[Selection];
			selectedOption->selection++;
			if (selectedOption->selectionList[selectedOption->selection]==NULL)
				selectedOption->selection=0;

			UpdateSelections2();
			UpdateSelections();
		}
		else if (Selection==num_options)
		{
			fDonePrefs=true;
			delete pBackupSettings;
		}
		else if (Selection==num_options+1)
		{
			fDonePrefs=true;
			gameSettings=*pBackupSettings;
			delete pBackupSettings;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitPrefs3D
//Author		Paul.   
//Date			Fri 20 Nov 1998
//------------------------------------------------------------------------------
void COverlay::InitPrefs3D()
{
	const int num_options=sizeof(gameOptions)/sizeof(SOption*);
	Selection=num_options;	//default to 'Okay' selected
	fDonePrefs=false;
	pBackupSettings=new GameSettings;
	*pBackupSettings=gameSettings;

	//set initial options based on the current game settings

	UpdateSelections();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateSelections
//Author		Paul.   
//Date			Fri 20 Nov 1998
//------------------------------------------------------------------------------
void COverlay::UpdateSelections()
{
	//setup display based on the current values in 'gameSettings'

	OptTrees.enabled=true;
	OptTrees.selection=Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS]?1:0;

	OptHorizonFade.enabled=true;
	OptHorizonFade.selection=Save_Data.detail_3d[DETAIL3D_HORIZONFADE]?1:0;

	OptAutoLand.enabled=true;
	OptAutoLand.selection=Save_Data.detail_3d[DETAIL3D_AUTODETAIL]?1:0;

	//Hardware specific stuff

	OptTransp.enabled=true;
	OptTransp.selection=Save_Data.detail_3d[DETAIL3D_TRANSSMOKE]?1:0;

	OptTextureQuality.enabled=true;
	OptTextureQuality.selection=Save_Data.textureQuality;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateSelections2
//Author		Paul.   
//Date			Fri 20 Nov 1998
//------------------------------------------------------------------------------
void COverlay::UpdateSelections2()
{
	//Hardware specific stuff

	Save_Data.textureQuality=OptTextureQuality.selection;

	if (OptHorizonFade.selection==0)	Save_Data.detail_3d%=DETAIL3D_HORIZONFADE;
	else								Save_Data.detail_3d|=DETAIL3D_HORIZONFADE;

	if (OptTrees.selection==0)	Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
	else						Save_Data.detail_3d|=DETAIL3D_INCONSEQUENTIALS;

	if (OptAutoLand.selection==0)		Save_Data.detail_3d%=DETAIL3D_AUTODETAIL;
	else								Save_Data.detail_3d|=DETAIL3D_AUTODETAIL;

	if (OptTransp.selection==0)		Save_Data.detail_3d%=DETAIL3D_TRANSSMOKE;
	else							Save_Data.detail_3d|=DETAIL3D_TRANSSMOKE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetViewVals
//Author		Paul
//Date			Mon 23 Nov 1998
//------------------------------------------------------------------------------
void COverlay::SetViewVals(SLong rng,SLong relB,SLong relA)
{
	targRange=rng;
	targRelBrg=relB;
	targRelAlt=relA;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInfoLines
//Author		Dave Whiteside
//Date			Mon 23 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void COverlay::SetInfoLines(SWord l)
{
	Save_Data.infoLineCount=l%INFOLINESMAX;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StepInfoBarUp
//Author		Dave Whiteside
//Date			Mon 23 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void COverlay::StepInfoBarUp()
{
	Save_Data.infoLineCount=(Save_Data.infoLineCount+1)%INFOLINESMAX;
	if (messageTimer) messageTimer=0;		//remove current message when the i key is pressed
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInfoLineVals
//Author		Paul
//Date			Mon 23 Nov 1998
//------------------------------------------------------------------------------
void COverlay::SetInfoLineVals(SLong s,Float m,SLong a, SLong h,SLong t)
{
	speed=s;													//PD 04Jan99
	mach=m;
	altitude = a>0?a:0;
	heading=h;
	thrust=t;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitInfoTexts
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void COverlay::InitInfoTexts()
{
	if (!otherText)
	{
		for (SLong i=0;i<_NumInfoTexts;i++)
		{
			OString* str=OInfoPanelText[i];
			str->text=LdStr(str->resID);
		}
		msgText=new CString[2];
		msgText[0]=msgText[1]="";
		otherText=new CString("");
	}
	target_item=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseInfoTexts
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void COverlay::ReleaseInfoTexts()
{
	for (SLong i=0;i<_NumInfoTexts;i++)
	{
		OString* str=OInfoPanelText[i];
		delete[]str->text,str->text=NULL;
	}
	delete[]msgText;
	delete otherText;
	otherText=NULL;
	msgText=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToMapViewScreen
//Author		Paul.   
//Date			Thu 11 Mar 1999
//------------------------------------------------------------------------------
void COverlay::SetToMapViewScreen()
{
	Kludge();
	currIcons=mapViewIconTable;
 	SetToUIScreen(&mapViewScr);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToOrdersScreen
//Author		Paul.   
//Date			Mon 22 Feb 1999
//------------------------------------------------------------------------------
void COverlay::SetToOrdersScreen()
{
	Kludge();
	if (!Manual_Pilot.ControlledAC2->Status.deadtime &&
		!pCurScr)
	{
		displayTimeLimit=0;
		CancelAccel();
		SetToUIScreen(&orders3dScr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToMapScreen
//Author		Paul.   
//Date			Tue 16 Feb 1999
//------------------------------------------------------------------------------
void COverlay::SetToMapScreen()
{
	Kludge();
	if (Manual_Pilot.ControlledAC2->Status.deadtime)	
		OverLay.pvp->ReturnFromMap();
	else
	{
		if (_DPlay.Implemented)	SetToUIScreen(&firstMapScrCOMMS);
		else					SetToUIScreen(&firstMapScr);
	}
}

void COverlay::SetToRadioScreen()
{
	Kludge();
	if (!Manual_Pilot.ControlledAC2->Status.deadtime)
	{
		if (_DPlay.Implemented)	SetToUIScreen(&userMsgScrCOMMS);
		else					SetToUIScreen(&userMsgScr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToMapAccelScreen
//Author		Paul.   
//Date			Wed 3 Mar 1999
//------------------------------------------------------------------------------
void COverlay::SetToMapAccelScreen()
{
	Kludge();
	if (Manual_Pilot.ControlledAC2->Status.deadtime)// || 
//		Manual_Pilot.ControlledAC2->movecode!=AUTO_FOLLOWWP)	
		OverLay.pvp->ReturnFromMap();
	else
		SetToUIScreen(&accelMapScr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToReplayScreen
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
void COverlay::SetToReplayScreen()
{
	Kludge();
	currIcons=replayIconTable;
	SetToUIScreen(&replayScr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DisplayCommsQuitDialog
//Author		Paul.   
//Date			Fri 19 Feb 1999
//				returns 00x000==no selection
//						0x0001==okay selected
//						0xFFFF==cancel selected
//------------------------------------------------------------------------------
UWord COverlay::DisplayCommsQuitDialog()
{
	Kludge();
 	SetToUIScreen(&commsDialog);
	return commsDialReturn;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetToUIScreen
//Author		Paul.   
//Date			Tue 16 Feb 1999
//------------------------------------------------------------------------------
bool COverlay::SetToUIScreen(MapScr* pns)
{
	if (pScrollyText)
	{
		delete pScrollyText;
		pScrollyText=NULL;
	}

	if (pCurScr!=NULL)
		return false;		//reject a change if a screen is already on display
	InitMousePos();
	pNewScr=pns;
	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitMousePos
//Author		Paul    
//Date			Sat 20 Feb 1999
//------------------------------------------------------------------------------
void COverlay::InitMousePos()
{
	mouseX=320;
	mouseY=240;
	lastMouseX=lastMouseY-1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateMousePos
//Author		Paul    
//Date			Sat 20 Feb 1999
//------------------------------------------------------------------------------
bool COverlay::UpdateMousePos()
{
	_Analogue.PollPosition();
	int newMouseX=(SWord)_Analogue.ReadPosition(AU_UI_X)+32768;

	fMouseDisabled=false;

	if (newMouseX==-0x8000) fMouseDisabled=true;
//	if (newMouseX!=-0x8000)	
//	{
	mouseX=newMouseX*(physicalWidth-10)/65536;

//TEMPCODE RDH 20/05/99 	newMouseX>>=4;
//TEMPCODE RDH 20/05/99 		if (lastMouseX!=-1)	mouseX+=(newMouseX-lastMouseX);
//TEMPCODE RDH 20/05/99 
//TEMPCODE RDH 20/05/99 		if (mouseX>=0 && mouseX<=physicalWidth)
//TEMPCODE RDH 20/05/99 		{
//TEMPCODE RDH 20/05/99 			lastMouseX=newMouseX;
//TEMPCODE RDH 20/05/99 		}
//TEMPCODE RDH 20/05/99 		else if (mouseX<0)
//TEMPCODE RDH 20/05/99 		{
//TEMPCODE RDH 20/05/99 			mouseX=0;
//TEMPCODE RDH 20/05/99 			lastMouseX=-1;
//TEMPCODE RDH 20/05/99 		}
//TEMPCODE RDH 20/05/99 		else if (mouseX>physicalWidth)
//TEMPCODE RDH 20/05/99 		{
//TEMPCODE RDH 20/05/99 			mouseX=physicalWidth;
//TEMPCODE RDH 20/05/99 			lastMouseX=-1;
//TEMPCODE RDH 20/05/99 		}
//	}
	int newMouseY=(SWord)_Analogue.ReadPosition(AU_UI_Y)+32768;
	if (newMouseY==-0x8000) fMouseDisabled=true;
//	if (newMouseY!=-0x8000)	
//	{
	mouseY=newMouseY*(physicalHeight-10)/65536;
//TEMPCODE RDH 20/05/99 	newMouseY>>=4;
//TEMPCODE RDH 20/05/99 		if (lastMouseY!=-1) mouseY+=(newMouseY-lastMouseY);
//TEMPCODE RDH 20/05/99 
//TEMPCODE RDH 20/05/99 		if (mouseY>=0 && mouseY<=physicalHeight)
//TEMPCODE RDH 20/05/99 		{
//TEMPCODE RDH 20/05/99 			lastMouseY=newMouseY;
//TEMPCODE RDH 20/05/99 		}
//TEMPCODE RDH 20/05/99 		else if (mouseY<0)
//TEMPCODE RDH 20/05/99 		{
//TEMPCODE RDH 20/05/99 			mouseY=0;
//TEMPCODE RDH 20/05/99 			lastMouseY=-1;
//TEMPCODE RDH 20/05/99 		}
//TEMPCODE RDH 20/05/99 		else if (mouseY>physicalHeight)
//TEMPCODE RDH 20/05/99 		{
//TEMPCODE RDH 20/05/99 			mouseY=physicalHeight;
//TEMPCODE RDH 20/05/99 			lastMouseY=-1;
//TEMPCODE RDH 20/05/99 		}
//TEMPCODE RDH 20/05/99 //	}
	bool retval;
		
	if (Key_Tests.KeyPress3d(MENUSELECT))
		retval=true;
	else
		retval=false;
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoaderScreen
//Author		Paul.   
//Date			Mon 22 Feb 1999
//------------------------------------------------------------------------------
void COverlay::LoaderScreen(int stage)
{
	if (Save_Data.fSoftware)
		return;
//DeadCode JIM 22Jun99 	Sleep(0); //attempt to force redraw when we want it!
	int realStage,subStage;
	realStage=stage>>8;
	subStage=stage&0xFF;
	const SLong LoaderTextX=400;
	const SLong LoaderTextY=60;
	FileNum loaderArt=FIL_LOADERART;								  //DAW 07/07/99
	fileblockptr fbp=new fileblock(loaderArt);
	pw->DoShowLoaderArt((void*)fbp->getdata());
	char* str=LdStr(IDS_LOADERSTAGE00+realStage);
	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
	fIsWide=IsWide(physicalWidth);

//	SWord textx=SWord(Float(LoaderTextX)*Float(physicalWidth)/Float(640));
//	SWord texty=SWord(Float(LoaderTextY)*Float(physicalHeight)/Float(480));

//	SWord boxX=textx-2;
//	SWord boxY=texty-2;

	SWord boxWidth=0;
	for (int j=4;j>=0;j--)
	{
		char* stmp=LdStr(IDS_LOADERSTAGE00+j);
		SWord tmp=StrPixelLen2(stmp);
		if (tmp>boxWidth) boxWidth=tmp;
		delete[]stmp;
	}
	boxWidth+=fIsWide?20:16;

	SWord boxHeight=fIsWide?20:16;

	SWord textx=(physicalWidth-boxWidth+2)>>1;
	SWord texty=(physicalHeight-boxHeight+2)>>1;

	SWord boxX=textx-2;
	SWord boxY=texty-2;

	pw->BeginScene();
	pw->DoSetGlobalAlpha(255);
	pw->DoSmokedGlassBox(boxX,boxY,boxWidth,boxHeight,0xFF8F8F8F);
	SWord scanW=boxWidth;
	boxX+=1;
	boxY+=1;
	boxHeight-=2;
	boxWidth-=2;
	boxWidth=(boxWidth*subStage)>>8;
	pw->DoSmokedGlassBox(boxX,boxY,boxWidth,boxHeight,0xFFFF0000);
	if (!Save_Data.fSoftware)	pw->DoSetFontColour(0xFF000000);
	else						POLYGON.SetFontColour(BLACK);
	PrintAt2(textx,texty,str);
	pw->EndScene();
	if (doneonce==1)
	{
		doneonce++;
		nofontkludge=pw->DoScanForBottomPixelsOfText(boxX,scanY,scanW);
	}
	pw->DoScreenSwap();

	delete[]str;
	delete fbp;
}

void COverlay::CommsWaitingScreen(int stage)
{
	if (Save_Data.fSoftware)
		return;
//DeadCode JIM 22Jun99 	Sleep(0); //attempt to force redraw when we want it!
	int realStage,subStage;
	realStage=0;
	subStage=stage&0xFF;
	const SLong LoaderTextX=400;
	const SLong LoaderTextY=60;
//DeadCode AMM 08Jul99 	FileNum loaderArt=FIL_LOADERART;
//DeadCode AMM 07Jul99 	FileNum loaderArt=loader_art;
//DeadCode AMM 08Jul99 	fileblockptr fbp=new fileblock(loaderArt);
//DeadCode AMM 08Jul99 	if (!_DPlay.resyncbar)
//DeadCode AMM 08Jul99 		pw->DoShowLoaderArt((void*)fbp->getdata());
	char* str;

	if (_DPlay.resyncbar)
		str=LdStr(IDS_PHRASE_RESYNCHING);
	else
		str=LdStr(IDS_LOADERSTAGE03);

	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
	fIsWide=IsWide(physicalWidth);

	SWord textx=SWord(Float(LoaderTextX)*Float(physicalWidth)/Float(640));
	SWord texty=SWord(Float(LoaderTextY)*Float(physicalHeight)/Float(480));

	SWord boxX=textx-2;
	SWord boxY=texty-2;

	SWord boxWidth=0;
	{
		char* stmp; //=LdStr(IDS_LOADERSTAGE03);

		if (_DPlay.resyncbar)
			stmp=LdStr(IDS_PHRASE_RESYNCHING);
		else
			stmp=LdStr(IDS_LOADERSTAGE03);

		SWord tmp=StrPixelLen2(stmp);
		if (tmp>boxWidth) boxWidth=tmp;
		delete[]stmp;
	}
	boxWidth+=fIsWide?20:16;

	SWord boxHeight=fIsWide?20:16;

	pw->BeginScene();
	pw->DoSetGlobalAlpha(255);
	pw->DoSmokedGlassBox(boxX,boxY,boxWidth,boxHeight,0xFF8F8F8F);
	boxX+=1;
	boxY+=1;
	boxHeight-=2;
	boxWidth-=2;
	boxWidth=(boxWidth*subStage)>>8;
	pw->DoSmokedGlassBox(boxX,boxY,boxWidth,boxHeight,0xFFFF0000);
	if (!Save_Data.fSoftware)	pw->DoSetFontColour(0xFF000000);
	else						POLYGON.SetFontColour(BLACK);
	PrintAt2(textx,texty,str);
	pw->EndScene();
	pw->DoScreenSwap();

	delete[]str;
//DeadCode AMM 08Jul99 	delete fbp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DisplayMouseCursor
//Author		Paul    
//Date			Sat 20 Feb 1999
//------------------------------------------------------------------------------
void COverlay::DisplayMouseCursor()
{
	if (fMouseDisabled)
		return;

	//LoaderScreen();

 	SWord ou,ov;
 	SWord cw,ch;
	SWord sw,sh;
	SLong sx,sy;

	SWord oldTQ=pw->DoForceTQ(4);
	bool oldMip=pw->DoSetMipMap(false);

	ImageMapDesc* pmap=Image_Map.GetImageMapPtr(SQUEAKNO);

	sx=mouseX;
	sy=mouseY;
	ou=
	ov=0;
	cw=sw=pmap->w;
	ch=sh=pmap->h;

	if (!Save_Data.fSoftware)	pw->DoSetFontColour(0xFFFFFFFF);
	else						POLYGON.SetFontColour(WHITE);

//TEMPCODE RDH 20/05/99 	sx=SLong(Float(sx)*Float(physicalWidth)/Float(640));
//TEMPCODE RDH 20/05/99 	sy=SLong(Float(sy)*Float(physicalHeight)/Float(480));

 	DoPointStruc dp[4];
 
 	dp[0].bodyx.f=Float(sx);
 	dp[0].bodyy.f=Float(sy);
 	dp[0].ix=ou;
 	dp[0].iy=ov;
 	dp[1].bodyx.f=Float(sx+sw);
 	dp[1].bodyy.f=Float(sy);
 	dp[1].ix=ou+cw;
 	dp[1].iy=ov;
 	dp[2].bodyx.f=Float(sx+sw);
 	dp[2].bodyy.f=Float(sy+sh);
 	dp[2].ix=ou+cw;
 	dp[2].iy=ov+ch;
 	dp[3].bodyx.f=Float(sx);
 	dp[3].bodyy.f=Float(sy+sh);
 	dp[3].ix=ou;
 	dp[3].iy=ov+ch;
 
	if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap,dp);
	else						pw->DoPutC(pmap,dp);
	pw->DoForceTQ(oldTQ);
	pw->DoSetMipMap(oldMip);
}

void COverlay::SetGridDimensions(MapScr *pscr)
{
	char* prefixTable[]={"1.","2.","3.","4.","5.","6.","7.","8.","9.","0.","  ","  ","  ","  ","  ","  ","  ","  "};
	//find the longest string & count number of lines @ the same time
	MapScr::OptionList *popt=pscr->optionList;
	SLong maxChars=0;
	for (SLong oc=0;popt->key!=SEL_EOL;oc++,popt++)
	{
		if (popt->resIDOffset!=0xFF &&
			(popt->resID<IDS_MAPICON00LO || popt->resID>IDS_MAPICON15HI))
		{
			CString cs=prefixTable[popt->key];
			//check for comms message strings...
			if (popt->resID>=IDS_INDIRECT00 &&
				popt->resID<=IDS_INDIRECT10)
				cs+=_DPlay.Messages[_DPlay.mySlot][popt->resID-IDS_INDIRECT00];
			else
			{
				char *pstr=LdStr(popt->resID+popt->resIDOffset);
				cs+=pstr;
				delete[]pstr;
			}
			//count pixel width of 'cs'
			SLong thisLen=StrPixelLen2(const_cast<char*>(LPCTSTR(cs)));
			if (thisLen>maxChars)
				maxChars=thisLen;
		}
	}
	pscr->rowHeight=fIsWide?20:10;
	oc=(oc+2)*pscr->rowHeight;
	pscr->windowWidth=pscr->columnWidth=UWord(maxChars+(2*pscr->rowHeight));
	pscr->windowHeight=UWord(oc);
	pscr->gridXOffset=
	pscr->gridYOffset=pscr->rowHeight;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessUIScreen
//Author		Paul.   
//Date			Fri 12 Feb 1999
//------------------------------------------------------------------------------
void COverlay::ProcessUIScreen()
{
//dead	if (pvp) pvp->BlockTick(TRUE);

	POLYGON.SetPixelWidth(1);

	char* prefixTable[]={"1.","2.","3.",
						"4.","5.","6.",
						"7.","8.","9.",
						"0.","  ","  ",
						"  ","  ","  ",
						"  ","  ","  "};
	if (pNewScr!=pCurScr)
	{
		pCurScr=pNewScr;
		highTimer=0;
		if (pCurScr!=NULL && pCurScr->initRtn!=NULL)
		{
			Key k=(pCurScr->*(pCurScr->initRtn))();
			hilight=k;
		}
		//eat map key presses

		Key_Tests.KeyPress3d(GOTOMAPKEY);
	}
	else if (pCurScr!=NULL)
	{
		pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
		fIsWide=IsWide(physicalWidth);

		//eat map key presses

		Key_Tests.KeyPress3d(GOTOMAPKEY);

		bool mouseClicked=UpdateMousePos();

		//check for hilight/dehilight counter

		if (highTimer>0 && (highTimer-=5)<=0)
		{
			highTimer=0;
			hilight=SEL_NONE;
		}

		//count options...

		MapScr::OptionList* pCurOpt=pCurScr->optionList;

		SLong optionCount=0;

		while (pCurOpt->key!=SEL_EOL) {pCurOpt++;optionCount++;}

		if (MapScr::SCALE_DYNAMICSIZE&pCurScr->gridFlags)
			SetGridDimensions(pCurScr);

		//display current screen options && test for input @ the same time

		pCurOpt=pCurScr->optionList;

		SLong 	posx,posy,				//scaled screen coordinates
										//of the top left corner of the
										//grid
				width,height,			//scaled screen coordinates of the
										//width and height of a single grid
										//element
				scaledMouseX,scaledMouseY,

				gridXOff,gridYOff,

				rowIndex,columnIndex;

//		if (mouseClicked)
//		{
			scaledMouseX=SLong(Float(mouseX));//*Float(physicalWidth)/Float(640));
			scaledMouseY=SLong(Float(mouseY));//*Float(physicalHeight)/Float(480));
//		}

		if (MapScr::SCALE_GRIDORIGIN&pCurScr->gridFlags)
		{
			posx=SLong(Float(pCurScr->windowLeft)*Float(physicalWidth)/Float(640));
			posy=SLong(Float(pCurScr->windowTop)*Float(physicalHeight)/Float(480));
		}
		else
		{
			posx=pCurScr->windowLeft;
			posy=pCurScr->windowTop;
//			if (fIsWide)
//			{
//				posx<<=1;
//				posy<<=1;
//			}
		}

		//wipe the background if neccessary

		if (pCurScr->wipeColour!=NO_BACKGROUND_WIPE)
		{
			SLong winWidth,winHeight;

			if (MapScr::SCALE_GRIDWH&pCurScr->gridFlags)
			{
				winWidth=SLong(Float(pCurScr->windowWidth)*Float(physicalWidth)/Float(640));
				winHeight=SLong(Float(pCurScr->windowHeight)*Float(physicalHeight)/Float(480));
			}
			else
			{
				winWidth=pCurScr->windowWidth;
				winHeight=pCurScr->windowHeight;
//				if (fIsWide)
//				{
//				 	winWidth<<=1;
//					winHeight<<=1;
//				}
			}
			if (MapScr::JUSTIFY_CENTRE_SX&pCurScr->gridFlags)
				posx=(physicalWidth>>1)-(winWidth>>1);

			if (MapScr::JUSTIFY_CENTRE_SY&pCurScr->gridFlags)
				posy=(physicalHeight>>1)-(winHeight>>1);

			if ((pCurScr->wipeColour&WIPE_ALPHA_MASK)==0)
			{
				ImageMapNumber imno=(ImageMapNumber)GET_WIPE_TEXTURE(pCurScr->wipeColour);
				ImageMapDesc* pmap=Image_Map.GetImageMapPtr(imno);
			 	DoPointStruc dp[4];
  				dp[0].bodyx.f=Float(posx);
			 	dp[0].bodyy.f=Float(posy);
			 	dp[0].ix=
			 	dp[0].iy=0;
			 	dp[1].bodyx.f=Float(posx+winWidth);
			 	dp[1].bodyy.f=Float(posy);
			 	dp[1].ix=pmap->w;
			 	dp[1].iy=0;
			 	dp[2].bodyx.f=Float(posx+winWidth);
			 	dp[2].bodyy.f=Float(posy+winHeight);
				dp[2].ix=pmap->w;
			 	dp[2].iy=pmap->h;
			 	dp[3].bodyx.f=Float(posx);
			 	dp[3].bodyy.f=Float(posy+winHeight);
			 	dp[3].ix=0;
			 	dp[3].iy=pmap->h;
				if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap,dp);
				else						pw->DoPutC(pmap,dp);
			}
			else
			{
				if (!Save_Data.fSoftware)
				{
					pw->DoSetGlobalAlpha(8);
					pw->DoSmokedGlassBox(posx,posy,winWidth,winHeight,pCurScr->wipeColour);
					pw->DoSetGlobalAlpha(255);
				}
				else POLYGON.DoSmokedGlassBox(posx,posy,winWidth,winHeight,BLACK);
			}
		}

		if (MapScr::SCALE_GRIDOFFSETS&pCurScr->gridFlags)
		{
			gridXOff=SLong(Float(pCurScr->gridXOffset)*Float(physicalWidth)/Float(640));
			gridYOff=SLong(Float(pCurScr->gridYOffset)*Float(physicalHeight)/Float(480));
		}
		else
		{
			gridXOff=pCurScr->gridXOffset;
			gridYOff=pCurScr->gridYOffset;
//			if (fIsWide)
//			{
//				gridXOff<<=1;
//				gridYOff<<=1;
//			}
		}

		posx+=gridXOff;
		posy+=gridYOff;

		if (MapScr::SCALE_GRIDELEMENTS&pCurScr->gridFlags)
		{
			width=SLong(Float(pCurScr->columnWidth)*Float(physicalWidth)/Float(640));
			height=SLong(Float(pCurScr->rowHeight)*Float(physicalHeight)/Float(480));
		}
		else
		{
			width=pCurScr->columnWidth;
			height=pCurScr->rowHeight;

			if (MapScr::SCALE_DOUBLEIFGT800&pCurScr->gridFlags)
			{
				if (IsExtraWide(physicalWidth))
				{
					width<<=1;
					height<<=1;
				}
			}
//			else if (fIsWide)
//			{
//				width<<=1;
//				height<<=1;
//			}
		}

		rowIndex=columnIndex=0;

		for (SLong i=0;i<optionCount;i++)
		{
			//check for a blank entry first

			SWord curx,cury;
			SWord savex,savey;

			savex=curx=posx+columnIndex*width;
			savey=cury=posy+rowIndex*height;

			if (pCurOpt->resIDOffset!=0xFF)
			{
				//check for icons instead of text
				if (pCurOpt->resID>=IDS_MAPICON00LO &&
					pCurOpt->resID<=IDS_MAPICON15HI)
				{
					//handle replay icons by printing them on screen as single
					//characters using the text system

					if (!Save_Data.fSoftware)	pw->DoSetFontColour(pCurScr->textColour);
					else						POLYGON.SetFontColour(MAKE_SOFT_COL(pCurScr->textColour));

					UWord iconIndex=pCurOpt->resID-IDS_MAPICON00LO;

					if (pCurOpt->key==hilight)
						iconIndex+=pCurOpt->resIDOffset;

					PrintIcon(curx,cury,width,height,iconIndex);
				}
// if indirectStringTable is not used for anything other than comms
// then can just access players messages

				else if (pCurOpt->resID>=IDS_INDIRECT00 &&
						 pCurOpt->resID<=IDS_INDIRECT10)
				{
					SWord index=pCurOpt->resID-IDS_INDIRECT00;
					if (!Save_Data.fSoftware)
					{
						if (pCurOpt->key==hilight)	pw->DoSetFontColour(pCurScr->hilightColour);
						else						pw->DoSetFontColour(pCurScr->textColour);
					}
					else
					{
						if (pCurOpt->key==hilight)	POLYGON.SetFontColour(MAKE_SOFT_COL(pCurScr->hilightColour));
						else						POLYGON.SetFontColour(MAKE_SOFT_COL(pCurScr->textColour));
					}
					char* theString;
					theString=prefixTable[pCurOpt->key];
					PrintAt2(curx,cury,theString);
					theString=_DPlay.Messages[_DPlay.mySlot][index];
					PrintAt2(curx,cury,theString);
				}
				else
				{
					if (!Save_Data.fSoftware)
					{
						if (pCurOpt->key==hilight)	pw->DoSetFontColour(pCurScr->hilightColour);
						else						pw->DoSetFontColour(pCurScr->textColour);
					}
					else
					{
						if (pCurOpt->key==hilight)	POLYGON.SetFontColour(MAKE_SOFT_COL(pCurScr->hilightColour));
						else						POLYGON.SetFontColour(MAKE_SOFT_COL(pCurScr->textColour));
					}

					char* theString;
					theString=prefixTable[pCurOpt->key];
					PrintAt2(curx,cury,theString);
					theString=LdStr(pCurOpt->resID+pCurOpt->resIDOffset);
					PrintAt2(curx,cury,theString);
					delete[]theString;
				}
			}

			//check this option for keyboard && mouse input

			if (pCurOpt->key!=SEL_BLANK)
			{
				KeyVal3D thisKey;
				KeyVal3D keyTable[]={	RPM_10,RPM_20,RPM_30,RPM_40,
										RPM_50,RPM_60,RPM_70,RPM_80,
										RPM_90,RPM_00,RPM_UP,RPM_DOWN,PADLOCKTOG,
										RESETVIEW,ROTUP,ROTDOWN,ROTLEFT,ROTRIGHT,
										PAUSEKEY,EXITKEY};

				thisKey=keyTable[pCurOpt->key];
				if (Key_Tests.KeyPress3d(thisKey) &&
					pCurOpt->selRtn!=NULL)
				{
					highTimer=pCurScr->highTimer;
					pNewScr=(pCurScr->*(pCurOpt->selRtn))(pCurOpt->resIDOffset,(Key)pCurOpt->key);
					Kludge();
				}
		

				else if (	scaledMouseX>=savex && scaledMouseX<(savex+width) &&
							scaledMouseY>=savey && scaledMouseY<(savey+height)	)
				{
					if (mouseClicked && pCurOpt->selRtn!=NULL)
					{
						highTimer=pCurScr->highTimer;
						pNewScr=(pCurScr->*(pCurOpt->selRtn))(pCurOpt->resIDOffset,(Key)pCurOpt->key);
						Kludge();
					}
					else if (MapScr::FLAG_MOUSEOVERHI&pCurScr->gridFlags)
					{
						hilight=(Key)pCurOpt->key;
					}
				}
			}

			//update grid coordinates to the next entry

			if (++columnIndex>=pCurScr->numColumns)
			{
				columnIndex=0;
				if (++rowIndex>pCurScr->numRows) INT3;
			}
			pCurOpt++;
		}

		//extra piece of code called each frame. Currently used to update the
		//messages displayed in the window on the map screen

		if (pCurScr!=NULL && pCurScr->extraRtn!=NULL)
			(pCurScr->*(pCurScr->extraRtn))();

		DisplayMouseCursor();

		if (quit3d)
			pNewScr=pCurScr=NULL;
	}
	else if (pNewScr==NULL && _MsgBuffer.thereIsANewMessage)
	{
		_MsgBuffer.thereIsANewMessage=false;
		_MsgBuffer.InitMessageWindow();
//Dead		msgText[0]=_MsgBuffer.Callsign(1)+_MsgBuffer.MessageBody(1);
		msgText[0]=_MsgBuffer.Callsign(1)+*_MsgBuffer.lateststring;			//RJS 15Jun99
		otherText[0]="";
		ChopStr(msgText[0],msgText[1]);
		messageTimer=5*100;	//5 seconds of message display			  //RDH 19/06/99
	}
//dead	if (pvp) pvp->BlockTick(FALSE);
}

/**********************
**	FIRST MAP SCREEN **
**********************/

static bool refreshLandscape=false;

const UWord MapScreenX=370;
const UWord MapScreenY=34;
const UWord MapScreenWidth=241;
const UWord MapScreenHeight=272;
const UWord MapGridXOffset=10;
const UWord MapGridYOffset=10;
const UWord MapColumnWidth=MapScreenWidth;
const UWord MapRowHeight=10;
const UWord MapGridNumCols=1;
const UWord MapGridNumRows=10;

const UWord RadioScreenWidth=160;
const UWord RadioScreenHeight=200;

inline void MakeTimeString(char* str,int time)
{
	time/=6000;
	int mins=time%60;
	time=time/60;
	time%=24;
	sprintf(str,"%2d:%02d",time,mins);
}

WayPointPtr FindFirstWP(UNIQUE_ID uid,WayPointPtr wp)
{
	WayPointPtr nwp=wp;
	//return straight away if no waypoint
	if (nwp==NULL)
		return nwp;
	//skip back until prev wp is NULL
	while (nwp->prev!=NULL) 
		nwp=nwp->prev;
	//skip forward 'til get a valid waypoint
	while(nwp!=wp && (uid.count<nwp->skipunder || uid.count>nwp->skipover))
		nwp=nwp->next;
	return nwp;
}

WayPointPtr FindNextWP(UNIQUE_ID uid,WayPointPtr wp)
{
	WayPointPtr nwp=wp;
	//return straight away if no waypoint
	if (nwp==NULL)
		return nwp;
	//skip forwards to the next valid waypoint
	nwp=nwp->next;
	while (nwp!=NULL && (uid.count<nwp->skipunder || uid.count>nwp->skipover))
		nwp=nwp->next;
	return nwp;
}

WayPointPtr FindPrevWP(UNIQUE_ID uid,WayPointPtr wp)
{
	WayPointPtr nwp=wp;
	//return straight away if no waypoint
	if (nwp==NULL)
		return nwp;
	//skip backwards to the next valid waypoint
	nwp=nwp->prev;
	while (nwp!=NULL && (uid.count<nwp->skipunder || uid.count>nwp->skipover))
		nwp=nwp->prev;
	return nwp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateMessageDisplay
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
void MapScr::UpdateWaypointDisplay()
{
	SWord messageX=SWord(Float(1)*Float(OverLay.physicalWidth)/Float(640));
	SWord messageY=SWord(Float(438)*Float(OverLay.physicalHeight)/Float(480));
	SWord messageH=SWord(Float(14)*Float(OverLay.physicalHeight)/Float(480));

	ULong messageColours[3]={TEXT_MAP_WHITE,TEXT_HI,TEXT_MAP_WHITE};
	Colour softMessageColours[3]={WHITE,RED,WHITE};

	for (SLong i=0;i<3 && OverLay.curr_waypoint;i++)
	{
		WayPointPtr wpp;

		if (i==0)		wpp=FindPrevWP(Manual_Pilot.ControlledAC2->uniqueID,OverLay.curr_waypoint);
		else if (i==1)	wpp=OverLay.curr_waypoint;
		else			wpp=FindNextWP(Manual_Pilot.ControlledAC2->uniqueID,OverLay.curr_waypoint);
		
		SWord localX,localY,saveX,saveY;
		localX=messageX;
		localY=messageY;
		messageY+=messageH;

		if (wpp)
		{
			CString cs;
			WPNames this_name=wpp->wpname;
			ULong resid;
			if (this_name==WPNAME_None)				resid=IDS_L_MAIN_WP_GAP;
			else if (this_name==WPNAME_Rendevous)	resid=IDS_MAIN_WP_RENDEVOUS;
			else if (this_name==WPNAME_Ingress)		resid=IDS_MAIN_WP_INGRESS;
			else if (this_name==WPNAME_Target)		resid=IDS_MAIN_WP_TARGET;
			else if (this_name==WPNAME_Regroup)		resid=IDS_MAIN_WP_REGROUP;
			else if (this_name==WPNAME_Egress)		resid=IDS_MAIN_WP_EGRESS;
			else if (this_name==WPNAME_Disperse)	resid=IDS_MAIN_WP_DISPERSE;
			else if (this_name==WPNAME_Landing)		resid=IDS_MAIN_WP_LAND;
			else									resid=IDS_L_MAIN_WP_GAP;
			if (!Save_Data.fSoftware)	OverLay.pw->DoSetFontColour(messageColours[i]);
			else						POLYGON.SetFontColour(softMessageColours[i]);
			char temp[]="1234567890";
			char* theString=OverLay.LdStr(resid);
			cs=theString;
			if (wpp->wpnum!=0)
			{
				sprintf(temp," (%d)",wpp->wpnum);
				cs+=temp;
			}
			delete[]theString;
			saveX=localX;
			saveY=localY;
			OverLay.PrintAt2(localX,localY,const_cast<char*>(LPCTSTR(cs)));
			localX=saveX+8*16;
			localY=saveY;
			COORDS3D pos=*(wpp->FindDesPos());
			pos.Y=(pos.Y*10)/Save_Data.alt.mediummm;
			pos.Y+=50;
			pos.Y-=(pos.Y%100);
			sprintf(temp,"%d",pos.Y);
			cs=temp;
			resid=Save_Data.alt.mediumabbr;
			theString=OverLay.LdStr(resid);
			cs+=theString;
			delete[]theString;
			saveX=localX;
			saveY=localY;
			OverLay.PrintAt2(localX,localY,const_cast<char*>(LPCTSTR(cs)));
			localX=saveX+8*10;
			localY=saveY;
			pos.Y=wpp->eta;
			MakeTimeString(temp,pos.Y);
			cs=temp;
			saveX=localX;
			saveY=localY;
			OverLay.PrintAt2(localX,localY,const_cast<char*>(LPCTSTR(cs)));
			localX=saveX+8*8;
			localY=saveY;

			COORDS3D source,target;
			target=*::FindDesPos(wpp);
//			if (wpp==Manual_Pilot.ControlledAC2->waypoint)
				source=Manual_Pilot.ControlledAC2->World;
//			else
//			{
//				WayPointPtr pwp=FindPrevWP(Manual_Pilot.ControlledAC2->uniqueID,wpp);
//				if (pwp)
//					source=*::FindDesPos(pwp);
//				else if (Manual_Pilot.ControlledAC2->ai.homebase)
//					source=Manual_Pilot.ControlledAC2->ai.homebase->World;
//				else
//					source.Y=-9999;
//			}
//			if (source.Y!=-9999)
			{
				//work out range & rel bearing for source to target
				char relbrgstr[128],rangestr[128];
				SLong range;
				ANGLES relbrg,temp;
				Math_Lib.Intercept(target.X-source.X,target.Y-source.Y,target.Z-source.Z,range,relbrg,temp);
				if (wpp==Manual_Pilot.ControlledAC2->waypoint)
					relbrg=relbrg-Manual_Pilot.ControlledAC2->hdg;
				
				SLong rb=((SLong(relbrg)&0xFFFF)*360)>>16;
				sprintf(relbrgstr,"%03d",rb);

				SLong r=range/Save_Data.dist.longcm;
				if (!r)
				{
					char *tdu=OverLay.LdStr(Save_Data.dist.mediumabbr);
					r=(range*10)/Save_Data.dist.mediummm;
					sprintf(rangestr,"%d%s",r,tdu);
					delete[]tdu;
				}
				else if (r>=100)
				{
					char *tdu=OverLay.LdStr(Save_Data.dist.longabbr);
//DeadCode PD 09Sep99 					r=range;
					sprintf(rangestr,"%d%s",r,tdu);
					delete[]tdu;
				}
				else
				{
					char *tdu=OverLay.LdStr(Save_Data.dist.longabbr);
					r=(range*10)/Save_Data.dist.longcm;
					sprintf(rangestr,"%.1f%s",float(r)/10,tdu);
					delete[]tdu;
				}
				saveX=localX;
				saveY=localY;
				OverLay.PrintAt2(localX,localY,relbrgstr);
				localX=saveX+8*8;
				localY=saveY;
				OverLay.PrintAt2(localX,localY,rangestr);
			}
		}
	} 
	HandleUpDnLftRgtToggleKeys();
	OverLay.message_caller=NULL;
	OverLay.message_callee=NULL;
	OverLay.message_target=NULL;

	if (!OverLay.fZoomedMap) ShowItemIcons(true);
	else					 ShowItemIconsZoomed(true);

	messageX=16+SWord(Float(8)*Float(OverLay.physicalWidth)/Float(640));
	messageY=SWord(Float(3)*Float(OverLay.physicalHeight)/Float(480));

	//display place name and time here
	CString placeName=_MsgBuffer.GetPlaceName(Manual_Pilot.ControlledAC2->World);
	int time=OverLay.pvp->TimeOfDay();
	char timeStr[]="hh:mm\0";
	MakeTimeString(timeStr,time);
	CString csTime=timeStr;
	csTime+="        "+placeName;
	OverLay.PrintAt2(messageX,messageY,const_cast<char*>(LPCTSTR(csTime)));

	//allow user to step through waypoints here

	WayPointPtr newWP;
	if (Key_Tests.KeyPress3d(ZOOMIN) && 
		(newWP=FindPrevWP(Manual_Pilot.ControlledAC2->uniqueID,OverLay.curr_waypoint))!=NULL)
		OverLay.curr_waypoint=newWP;
	else if (Key_Tests.KeyPress3d(ZOOMOUT) && 
		(newWP=FindNextWP(Manual_Pilot.ControlledAC2->uniqueID,OverLay.curr_waypoint))!=NULL)
		OverLay.curr_waypoint=newWP;
}

void MapScr::UpdateMessageDisplay()
{
	SWord messageX=SWord(Float(1)*Float(OverLay.physicalWidth)/Float(640));
	SWord messageY=SWord(Float(438)*Float(OverLay.physicalHeight)/Float(480));
	SWord messageH=SWord(Float(14)*Float(OverLay.physicalHeight)/Float(480));

	if (Manual_Pilot.ControlledAC2 &&
		Manual_Pilot.ControlledAC2->waypoint)
		OverLay.curr_waypoint=Manual_Pilot.ControlledAC2->waypoint;

	ULong messageColours[3]={TEXT_MAP_WHITE,TEXT_HI,TEXT_MAP_WHITE};
	Colour softMessageColours[3]={WHITE,RED,WHITE};

	for (SLong i=2;i>=0;i--)
	{
		SWord localX,localY;
		localX=messageX;
		localY=messageY;
		messageY+=messageH;
		CString cs=_MsgBuffer.Callsign(i)+_MsgBuffer.MessageBody(i);
		if (!Save_Data.fSoftware)	OverLay.pw->DoSetFontColour(messageColours[i]);
		else						POLYGON.SetFontColour(softMessageColours[i]);
		if (i==1)
		{
			if (!OverLay.pScrollyText)
			{
				SWord targetIndex=OverLay.CalcTargIndex(cs);
				OverLay.pScrollyText=new COverlay::ScrollyText(targetIndex);
			}
			cs=OverLay.pScrollyText->Scroll(cs,OverLay.pvp->RealFrameTime());
		}
		OverLay.MakeDotDotDot(cs);
		OverLay.PrintAt2(localX,localY,const_cast<char*>(LPCTSTR(cs)));
	} 
	HandleUpDnLftRgtToggleKeys();
	_MsgBuffer.MessageParticipants(1,OverLay.message_caller,OverLay.message_callee,OverLay.message_target);
	if (!OverLay.fZoomedMap) ShowItemIcons(false);
	else					 ShowItemIconsZoomed(false);

	//display world coordinates & cd block position of the piloted a/c
	//on the map

	messageX=16+SWord(Float(8)*Float(OverLay.physicalWidth)/Float(640));
	messageY=SWord(Float(3)*Float(OverLay.physicalHeight)/Float(480));

#if !defined(NDEBUG)
	SLong viewer_x=Manual_Pilot.ControlledAC2->World.X;
	SLong viewer_z=Manual_Pilot.ControlledAC2->World.Z;
	char block[128];
	sprintf(block,"WX: %d WZ: %d",viewer_x,viewer_z);
	OverLay.PrintAt2(messageX,messageY,block);
	messageX=16+SWord(Float(8)*Float(OverLay.physicalWidth)/Float(640));
	messageY=SWord(Float(3)*Float(OverLay.physicalHeight)/Float(480))+16;
	block[4]=char(0);
	SLong xof=(viewer_x&0x1FFFFF)>>10;	//0..2048
	SLong val=viewer_x>>(17+4);
	block[2]=char(val&0x7)+'1';		//x (lo)
	val>>=3;
	block[0]=char(val)+'1';			//x (hi)
	SLong zof=2047-((viewer_z&0x1FFFFF)>>10);
	val=viewer_z>>(17+4);
	block[3]=char(val&0x7)+'1';		//z (lo)
	val>>=3;
	block[1]=char(val)+'1';			//z (hi)
	OverLay.PrintAt2(messageX,messageY,block);
	sprintf(block," xoff %d ",xof);
	OverLay.PrintAt2(messageX,messageY,block);
	sprintf(block,"zoff %d ",zof);
	OverLay.PrintAt2(messageX,messageY,block);
#else
	//display place name and time here
	CString placeName=_MsgBuffer.GetPlaceName(Manual_Pilot.ControlledAC2->World);
	int time=OverLay.pvp->TimeOfDay();
	char timeStr[]="hh:mm\0";
	MakeTimeString(timeStr,time);
	CString csTime=timeStr;
	csTime+="        "+placeName;
	OverLay.PrintAt2(messageX,messageY,const_cast<char*>(LPCTSTR(csTime)));
#endif
	if (Key_Tests.KeyPress3d(ZOOMIN))		
	{
		_MsgBuffer.DecMessageWindow();
		delete OverLay.pScrollyText;
		OverLay.pScrollyText=NULL;
	}
	else if (Key_Tests.KeyPress3d(ZOOMOUT))	
	{
		_MsgBuffer.IncMessageWindow();
		delete OverLay.pScrollyText;
		OverLay.pScrollyText=NULL;
	}
}

//map is made up of two 256x256 texture maps giving a map size of 256x512
//the map must be clipped to a window defined by the following eqautes

#define MAP_SCREEN_ORIGIN_X_640	6
#define MAP_SCREEN_ORIGIN_Y_640 1
#define MAP_SCREEN_WIDTH_640	316
#define MAP_SCREEN_HEIGHT_640	438
//#define MAP_SCREEN_HRTOP_640	52
//#define MAP_SCREEN_HRBOT_640	380
#define MAP_SCREEN_HRTOP_640	63
#define MAP_SCREEN_HRBOT_640	373
#define MAP_SCREEN_CX_640		(MAP_SCREEN_ORIGIN_X_640+(MAP_SCREEN_WIDTH_640>>1))
#define MAP_SCREEN_CY_640		(MAP_SCREEN_ORIGIN_Y_640+(MAP_SCREEN_HEIGHT_640>>1))

//the shift factor used to zoom the map (1==2x zoom)

#define MAP_SCALE				1
#define MAP_TEXTURE_WIDTH		(256<<MAP_SCALE)
#define MAP_TEXTURE_HEIGHT		(512<<MAP_SCALE)

inline SWord WorldXToTu(SLong wx)
{
	const SLong grid_scale=8;
 	const SLong grid_size=1<<(21-grid_scale);
	const SLong grid_start=11*grid_size;
	const SLong grid_width=37*grid_size;
	wx>>=grid_scale;
	wx-=grid_start;
	wx<<=(8+MAP_SCALE);
	wx/=grid_width;
	return SWord(wx+(8<<MAP_SCALE));
}

inline SWord WorldZToTv(SLong wz)
{
	const SLong grid_scale=8;
 	const SLong grid_size=1<<(21-grid_scale);
	const SLong grid_start=0;
	const SLong grid_width=64*grid_size;
	wz>>=grid_scale;
	wz-=grid_start;
	wz<<=(9+MAP_SCALE);
	wz/=grid_width;
	wz=(512<<MAP_SCALE)-wz;
	return SWord(wz);
}

inline SWord WorldXToTuHi(SLong wx)
{
	wx>>=16;
	wx-=384;	//512;	//256;
	return SWord(wx);
}

inline SWord WorldZToTvHi(SLong wz)
{
	wz>>=16;
	wz=2047-wz;
	return SWord(wz);
}

inline SWord WorldXToSx640Hi(SLong wx,SWord *x)
{
	SWord texel_u=WorldXToTuHi(wx);
	float tu=float(MAP_SCREEN_ORIGIN_X_640+x[0])+float(texel_u)*MapScr::map_scale;
	return SWord(tu);
}

inline SWord WorldZToSy640Hi(SLong wz,SWord *y)
{
	SWord texel_v=WorldZToTvHi(wz);
	float tv=float(MAP_SCREEN_ORIGIN_Y_640+y[0])+float(texel_v)*MapScr::map_scale;
	return SWord(tv);
}

const float XSCALEFUDGE=1.15;

inline SWord WorldXToSx640(SLong wx,SWord *x)
{
	SWord texel_u=WorldXToTu(wx);
	Float frac_u=Float(texel_u-x[0])/Float(x[1]-x[0]);
	SWord screen_x=MAP_SCREEN_ORIGIN_X_640+SWord(XSCALEFUDGE*frac_u*Float(MAP_SCREEN_WIDTH_640));
	return screen_x;
}

inline SWord WorldZToSy640(SLong wz,SWord *y)
{
	SWord texel_v=WorldZToTv(wz);
	Float frac_v=Float(texel_v-y[0])/Float(y[1]-y[0]);
	SWord screen_y=MAP_SCREEN_ORIGIN_Y_640+SWord(frac_v*Float(MAP_SCREEN_HEIGHT_640));
	return screen_y;
}

inline SWord WorldXToSx640Zoomed(SLong wx,SLong *x)
{
	Float frac_u=Float(wx-x[0])/Float(x[1]-x[0]);
	SWord screen_x=2+MAP_SCREEN_ORIGIN_X_640+SWord(frac_u*Float(MAP_SCREEN_WIDTH_640));
	return screen_x;
//	Float frac_u=Float(wx-x[0])/Float(x[1]-x[0]);
//	SWord screen_x=SWord(frac_u*Float(640));
//	return screen_x;
}

inline SWord WorldZToSy640Zoomed(SLong wz,SLong *y)
{
	Float frac_v=Float(wz-y[0])/Float(y[1]-y[0]);
	SWord screen_y=1+MAP_SCREEN_HRTOP_640+SWord(frac_v*Float(MAP_SCREEN_WIDTH_640));
	return screen_y;
//	Float frac_v=Float(wz-y[0])/Float(y[1]-y[0]);
//	SWord screen_y=SWord(frac_v*Float(480));
//	return screen_y;
}

void MapScr::ShowBackgroundMapHi(COORDS3D& pos,SWord *xc,SWord *yc)
{
	struct MapPoint
	{
		float x,y;
		UWord clipFlags;
	}
	mapPoints[5][9];

	ImageMapDesc *pmap[4][8];

	float scale=map_scale;

	for (int x=0;x<5;x++) for (int y=0;y<9;y++)
	{
		mapPoints[x][y].x=float(x)*256*scale;
		mapPoints[x][y].y=float(y)*256*scale;
		mapPoints[x][y].clipFlags=0;
	}

	pmap[0][0]=Image_Map.GetImageMapPtr(SMAP0_7NO);
	pmap[0][1]=Image_Map.GetImageMapPtr(SMAP0_6NO);
	pmap[0][2]=Image_Map.GetImageMapPtr(SMAP0_5NO);
	pmap[0][3]=Image_Map.GetImageMapPtr(SMAP0_4NO);
	pmap[0][4]=Image_Map.GetImageMapPtr(SMAP0_3NO);
	pmap[0][5]=Image_Map.GetImageMapPtr(SMAP0_2NO);
	pmap[0][6]=Image_Map.GetImageMapPtr(SMAP0_1NO);
	pmap[0][7]=Image_Map.GetImageMapPtr(SMAP0_0NO);

	pmap[1][0]=Image_Map.GetImageMapPtr(SMAP1_7NO);
	pmap[1][1]=Image_Map.GetImageMapPtr(SMAP1_6NO);
	pmap[1][2]=Image_Map.GetImageMapPtr(SMAP1_5NO);
	pmap[1][3]=Image_Map.GetImageMapPtr(SMAP1_4NO);
	pmap[1][4]=Image_Map.GetImageMapPtr(SMAP1_3NO);
	pmap[1][5]=Image_Map.GetImageMapPtr(SMAP1_2NO);
	pmap[1][6]=Image_Map.GetImageMapPtr(SMAP1_1NO);
	pmap[1][7]=Image_Map.GetImageMapPtr(SMAP1_0NO);

	pmap[2][0]=Image_Map.GetImageMapPtr(SMAP2_7NO);
	pmap[2][1]=Image_Map.GetImageMapPtr(SMAP2_6NO);
	pmap[2][2]=Image_Map.GetImageMapPtr(SMAP2_5NO);
	pmap[2][3]=Image_Map.GetImageMapPtr(SMAP2_4NO);
	pmap[2][4]=Image_Map.GetImageMapPtr(SMAP2_3NO);
	pmap[2][5]=Image_Map.GetImageMapPtr(SMAP2_2NO);
	pmap[2][6]=Image_Map.GetImageMapPtr(SMAP2_1NO);
	pmap[2][7]=Image_Map.GetImageMapPtr(SMAP2_0NO);

	pmap[3][0]=Image_Map.GetImageMapPtr(SMAP3_7NO);
	pmap[3][1]=Image_Map.GetImageMapPtr(SMAP3_6NO);
	pmap[3][2]=Image_Map.GetImageMapPtr(SMAP3_5NO);
	pmap[3][3]=Image_Map.GetImageMapPtr(SMAP3_4NO);
	pmap[3][4]=Image_Map.GetImageMapPtr(SMAP3_3NO);
	pmap[3][5]=Image_Map.GetImageMapPtr(SMAP3_2NO);
	pmap[3][6]=Image_Map.GetImageMapPtr(SMAP3_1NO);
	pmap[3][7]=Image_Map.GetImageMapPtr(SMAP3_0NO);

	OverLay.pw->DoSetFontColour(0xFFFFFFFF);

	//convert pos X & Z into texel coordinates in the range (0..1023,0..2047)
	
	SWord tu=WorldXToTuHi(pos.X);
	SWord tv=WorldZToTvHi(pos.Z);

	float cx640=MAP_SCREEN_ORIGIN_X_640+(MAP_SCREEN_WIDTH_640>>1);
	float cy640=MAP_SCREEN_ORIGIN_Y_640+(MAP_SCREEN_HEIGHT_640>>1);

	float dx=cx640-float(tu)*scale;
	float dy=cy640-float(tv)*scale;

	for (x=0;x<5;x++) for (int y=0;y<9;y++)
	{
		mapPoints[x][y].x+=dx;
		mapPoints[x][y].y+=dy;
	}
	xc[0]=SWord(dx);
	yc[0]=SWord(dy);

	//check to make sure that no holes are left on screen...

	if (mapPoints[0][0].y>MAP_SCREEN_ORIGIN_Y_640)								
		dy=mapPoints[0][0].y-MAP_SCREEN_ORIGIN_Y_640;
	else if (mapPoints[0][8].y<(MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640))
		dy=mapPoints[0][8].y-(MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640);
	else
		dy=0;
		
	if (mapPoints[0][0].x>MAP_SCREEN_ORIGIN_X_640)								
		dx=mapPoints[0][0].x-MAP_SCREEN_ORIGIN_X_640;
	else if (mapPoints[4][0].x<(MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640))
		dx=mapPoints[4][0].x-(MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640);
	else
		dx=0;

	xc[0]-=SWord(dx);
	yc[0]-=SWord(dy);
		
	for (x=0;x<5;x++) for (int y=0;y<9;y++)
	{
		mapPoints[x][y].x-=dx;
		mapPoints[x][y].y-=dy;
		if (mapPoints[x][y].x<MAP_SCREEN_ORIGIN_X_640)	
			mapPoints[x][y].clipFlags|=CF3D_OFFLEFT;
		if (mapPoints[x][y].x>=(MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640))
			mapPoints[x][y].clipFlags|=CF3D_OFFRIGHT;
		if (mapPoints[x][y].y<MAP_SCREEN_ORIGIN_Y_640)
			mapPoints[x][y].clipFlags|=CF3D_OFFTOP;
		if (mapPoints[x][y].y>=(MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640))
			mapPoints[x][y].clipFlags|=CF3D_OFFBOTTOM;
	}

	float scale_width,scale_height;

	scale_width=float(OverLay.physicalWidth)/640;
	scale_height=float(OverLay.physicalHeight)/480;

	for (x=0;x<4;x++) for (int y=0;y<8;y++)
	{
		UWord oredFlags,andedFlags;

		oredFlags=	mapPoints[x][y].clipFlags|
					mapPoints[x+1][y].clipFlags|
					mapPoints[x+1][y+1].clipFlags|
					mapPoints[x][y+1].clipFlags;

		andedFlags=	mapPoints[x][y].clipFlags&
					mapPoints[x+1][y].clipFlags&
					mapPoints[x+1][y+1].clipFlags&
					mapPoints[x][y+1].clipFlags;

		if (andedFlags==0)
		{
			DoPointStruc dp[4];
			dp[0].bodyx.f=mapPoints[x][y].x;
			dp[0].bodyy.f=mapPoints[x][y].y;
			dp[0].ix=0;
			dp[0].iy=0;

			dp[1].bodyx.f=mapPoints[x+1][y].x;
			dp[1].bodyy.f=mapPoints[x+1][y].y;
			dp[1].ix=255;
			dp[1].iy=0;

			dp[2].bodyx.f=mapPoints[x+1][y+1].x;
			dp[2].bodyy.f=mapPoints[x+1][y+1].y;
			dp[2].ix=255;
			dp[2].iy=255;

			dp[3].bodyx.f=mapPoints[x][y+1].x;
			dp[3].bodyy.f=mapPoints[x][y+1].y;
			dp[3].ix=0;
			dp[3].iy=255;

			if (oredFlags!=0)
			{
				//clip here!
				if (mapPoints[x][y].clipFlags&CF3D_OFFLEFT)
				{
					//dp[0] & dp[3] are off the left edge of the screen
					float frac=(MAP_SCREEN_ORIGIN_X_640-dp[0].bodyx.f)/(dp[1].bodyx.f-dp[0].bodyx.f);
					float tu=float(dp[0].ix)+float(dp[1].ix-dp[0].ix)*frac;
					dp[0].bodyx.f=MAP_SCREEN_ORIGIN_X_640;
					dp[0].ix=tu;
					dp[3].bodyx.f=dp[0].bodyx.f;
					dp[3].ix=dp[0].ix;
				}
				if (mapPoints[x+1][y].clipFlags&CF3D_OFFRIGHT)
				{
					//dp[1] & dp[2] are off the right edge of the screen
					float frac=(MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-dp[0].bodyx.f)/(dp[1].bodyx.f-dp[0].bodyx.f);
					float tu=float(dp[0].ix)+float(dp[1].ix-dp[0].ix)*frac;
					dp[1].bodyx.f=MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640;
					dp[1].ix=tu;
					dp[2].bodyx.f=dp[1].bodyx.f;
					dp[2].ix=dp[1].ix;
				}
				if (mapPoints[x][y].clipFlags&CF3D_OFFTOP)
				{
					//dp[0] & dp[3] are off the top edge of the screen
					float frac=(MAP_SCREEN_ORIGIN_Y_640-dp[0].bodyy.f)/(dp[3].bodyy.f-dp[0].bodyy.f);
					float tv=float(dp[0].iy)+float(dp[3].iy-dp[0].iy)*frac;
					dp[0].bodyy.f=MAP_SCREEN_ORIGIN_Y_640;
					dp[0].iy=tv;
					dp[1].bodyy.f=dp[0].bodyy.f;
					dp[1].iy=dp[0].iy;
				}
				if (mapPoints[x][y+1].clipFlags&CF3D_OFFBOTTOM)
				{
					//dp[2] & dp[3] are off the bottom edge of the screen
					float frac=(MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-dp[0].bodyy.f)/(dp[3].bodyy.f-dp[0].bodyy.f);
					float tv=float(dp[0].iy)+float(dp[3].iy-dp[0].iy)*frac;
					dp[3].bodyy.f=MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640;
					dp[3].iy=tv;
					dp[2].bodyy.f=dp[3].bodyy.f;
					dp[2].iy=dp[3].iy;
				}
			}
			//scale to physical coordinates
			for (int q=3;q>=0;q--)
			{
				dp[q].bodyx.f*=scale_width;
				dp[q].bodyy.f*=scale_height;
			}
			if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap[x][y],dp);
			else						OverLay.pw->DoPutA(pmap[x][y],dp);
		}
	}
}

void MapScr::ShowBackgroundMap(COORDS3D& pos,SWord *xc,SWord *yc)
{
	OverLay.pw->DoSetFontColour(0xFFFFFFFF);

	//convert pos X & Z into texel coordinates in the range (0..255,0..511)

	SWord tu,tv;
	tu=WorldXToTu(pos.X);
	tv=WorldZToTv(pos.Z);

	//i want to display the map with this texel in the center of the
	//screen unless this means that some of the screen window will not
	//be on the map

	SWord x[2],y[2];
	UWord f;

	x[0]=tu-(MAP_SCREEN_WIDTH_640>>1);
	x[1]=tu+(MAP_SCREEN_WIDTH_640>>1);
	y[0]=tv-(MAP_SCREEN_HEIGHT_640>>1);
	y[1]=tv+(MAP_SCREEN_HEIGHT_640>>1);
	f=0;
	if (x[0]<0)						f|=CF3D_OFFLEFT;
	if (x[1]>=MAP_TEXTURE_WIDTH)	f|=CF3D_OFFRIGHT;
	if (y[0]<0)						f|=CF3D_OFFTOP;
	if (y[1]>=MAP_TEXTURE_HEIGHT)	f|=CF3D_OFFBOTTOM;

	if (f!=0)
	{
		//some of the display window doesn't cover the map
		//so the center needs adjusting...

		if (f&CF3D_OFFLEFT)		tu+=(0-x[0]);
		if (f&CF3D_OFFRIGHT)	tu+=(MAP_TEXTURE_WIDTH-x[1]);
		if (f&CF3D_OFFTOP)		tv+=(0-y[0]);
		if (f&CF3D_OFFBOTTOM)	tv+=(MAP_TEXTURE_HEIGHT-y[1]);

		//regenerate the texture window coordinates
		x[0]=tu-(MAP_SCREEN_WIDTH_640>>1);
		x[1]=tu+(MAP_SCREEN_WIDTH_640>>1);
		y[0]=tv-(MAP_SCREEN_HEIGHT_640>>1);
		y[1]=tv+(MAP_SCREEN_HEIGHT_640>>1);
	}

	//generate physical pixel coordinates of the screen window...
	const SWord map_screen_x=SWord((Float(MAP_SCREEN_ORIGIN_X_640)*Float(OverLay.physicalWidth)/Float(640))+.5);
	const SWord map_screen_y=SWord((Float(MAP_SCREEN_ORIGIN_Y_640)*Float(OverLay.physicalHeight)/Float(480))+.5);
	const SWord map_screen_width=SWord((Float(MAP_SCREEN_WIDTH_640)*Float(OverLay.physicalWidth)/Float(640))+.5);
	const SWord map_screen_height=SWord((Float(MAP_SCREEN_HEIGHT_640)*Float(OverLay.physicalHeight)/Float(480))+.5)+
				1*(OverLay.physicalHeight==384);

	DoPointStruc dp[4];
	//is the top half of the map texture to be displayed?
	if (y[0]<MAP_TEXTURE_HEIGHT>>1)
	{
		dp[0].bodyx.f=dp[3].bodyx.f=map_screen_x;
		dp[0].ix=dp[3].ix=x[0]>>MAP_SCALE;
		dp[1].bodyx.f=dp[2].bodyx.f=map_screen_x+map_screen_width-1;
		dp[1].ix=dp[2].ix=x[1]>>MAP_SCALE;
		dp[0].bodyy.f=dp[1].bodyy.f=map_screen_y;
		dp[0].iy=dp[1].iy=y[0]>>MAP_SCALE;
		//points 2 & 3 bodyy & iy are more complicated
		//if the texture coordinates for the bottom of the map are 
		//in the top half of the map then there's no problem
		if (y[1]<=MAP_TEXTURE_HEIGHT>>1)
		{
			dp[2].bodyy.f=dp[3].bodyy.f=map_screen_y+map_screen_height-1;
			dp[2].iy=dp[3].iy=y[1]>>MAP_SCALE;
		}
		else
		{
			//only part of the top half of the texture is to be displayed
			//but how much...
			Float frac=Float((MAP_TEXTURE_HEIGHT>>1)-y[0])/Float(y[1]-y[0]);
			dp[2].bodyy.f=dp[3].bodyy.f=map_screen_y+frac*map_screen_height;
			dp[2].iy=dp[3].iy=MAP_TEXTURE_HEIGHT>>(1+MAP_SCALE);
		}
		//display the map texture...
		ImageMapDesc* pmap=Image_Map.GetImageMapPtr(THUMBTOPNO);
		if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap,dp);
		else						OverLay.pw->DoPutA(pmap,dp);
	}

	//is the bottom half of the map texture to be displayed?
	if (y[1]>MAP_TEXTURE_HEIGHT>>1)
	{
		dp[0].bodyx.f=dp[3].bodyx.f=map_screen_x;
		dp[0].ix=dp[3].ix=x[0]>>MAP_SCALE;
		dp[1].bodyx.f=dp[2].bodyx.f=map_screen_x+map_screen_width-1;
		dp[1].ix=dp[2].ix=x[1]>>MAP_SCALE;
		dp[2].bodyy.f=dp[3].bodyy.f=map_screen_y+map_screen_height-1;
		dp[2].iy=dp[3].iy=y[1]>>MAP_SCALE;
		//points 0 & 1 bodyy & iy are more complicated
		//if the texture coordinates for the top of the map are 
		//in the bottom half of the map then there's no problem

		if (y[0]>=MAP_TEXTURE_HEIGHT>>1)
		{
			dp[0].bodyy.f=dp[1].bodyy.f=map_screen_y;
			dp[0].iy=dp[1].iy=y[0]>>MAP_SCALE;
		}
		else
		{
			Float frac=Float((MAP_TEXTURE_HEIGHT>>1)-y[0])/Float(y[1]-y[0]);
			dp[0].bodyy.f=dp[1].bodyy.f=map_screen_y+frac*map_screen_height;
			dp[0].iy=dp[1].iy=MAP_TEXTURE_HEIGHT>>(1+MAP_SCALE);
		}
		//display the map texture...
		for (int i=3;i>=0;i--)
			dp[i].iy-=MAP_TEXTURE_HEIGHT>>(1+MAP_SCALE);
		ImageMapDesc* pmap=Image_Map.GetImageMapPtr(THUMBBOTNO);
		if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap,dp);
		else						OverLay.pw->DoPutA(pmap,dp);
	}
	xc[0]=x[0]; xc[1]=x[1];
	yc[0]=y[0]; yc[1]=y[1];
}

inline UWord MapClipFlags(SWord ix,SWord iy,SWord *x,SWord *y)
{
	UWord clipResult=0;
	if (ix<x[0])		clipResult|=CF3D_OFFLEFT;
	else if (ix>x[1])	clipResult|=CF3D_OFFRIGHT;
	if (iy<y[0])		clipResult|=CF3D_OFFTOP;
	else if (iy>y[1])	clipResult|=CF3D_OFFBOTTOM;
	return clipResult;
}

inline UWord MapClipFlagsZoomed(SLong ix,SLong iy,SLong *x,SLong *y)
{
	UWord clipResult=0;
	if (ix<x[0])		clipResult|=CF3D_OFFLEFT;
	else if (ix>x[1])	clipResult|=CF3D_OFFRIGHT;
	if (iy<y[0])		clipResult|=CF3D_OFFTOP;
	else if (iy>y[1])	clipResult|=CF3D_OFFBOTTOM;
	return clipResult;
}

inline bool ClipLine(SWord *x,SWord *y,UWord *f,SWord *xc,SWord *yc)
{
	Float frac;
	SWord temp;
	UWord temp2;

	if ((f[0]|f[1])&CF3D_OFFTOP)
	{
		if (f[0]&CF3D_OFFTOP)
		{
			temp=x[0]; x[0]=x[1]; x[1]=temp;
			temp=y[0]; y[0]=y[1]; y[1]=temp;
			temp2=f[0]; f[0]=f[1]; f[1]=temp2;
		}
		frac=Float(yc[0]-y[0])/Float(y[1]-y[0]);
		y[1]=yc[0];
		x[1]=x[0]+SWord(frac*Float(x[1]-x[0]));
		f[1]=MapClipFlags(x[1],y[1],xc,yc);
	}

	if ((f[0]|f[1])&CF3D_OFFBOTTOM)
	{
		if (f[0]&CF3D_OFFBOTTOM)
		{
			temp=x[0]; x[0]=x[1]; x[1]=temp;
			temp=y[0]; y[0]=y[1]; y[1]=temp;
			temp2=f[0]; f[0]=f[1]; f[1]=temp2;
		}
		frac=Float(yc[1]-y[0])/Float(y[1]-y[0]);
		y[1]=yc[1];
		x[1]=x[0]+SWord(frac*Float(x[1]-x[0]));
		f[1]=MapClipFlags(x[1],y[1],xc,yc);
	}

	if ((f[0]|f[1])&CF3D_OFFLEFT)
	{
		if (f[0]&CF3D_OFFLEFT)
		{
			temp=x[0]; x[0]=x[1]; x[1]=temp;
			temp=y[0]; y[0]=y[1]; y[1]=temp;
			temp2=f[0]; f[0]=f[1]; f[1]=temp2;
		}
		frac=Float(xc[0]-x[0])/Float(x[1]-x[0]);
		x[1]=xc[0];
		y[1]=y[0]+SWord(frac*Float(y[1]-y[0]));
		f[1]=MapClipFlags(x[1],y[1],xc,yc);
	}

	if ((f[0]|f[1])&CF3D_OFFRIGHT)
	{
		if (f[0]&CF3D_OFFRIGHT)
		{
			temp=x[0]; x[0]=x[1]; x[1]=temp;
			temp=y[0]; y[0]=y[1]; y[1]=temp;
			temp2=f[0]; f[0]=f[1]; f[1]=temp2;
		}
		frac=Float(xc[1]-x[0])/Float(x[1]-x[0]);
		x[1]=xc[1];
		y[1]=y[0]+SWord(frac*Float(y[1]-y[0]));
		f[1]=MapClipFlags(x[1],y[1],xc,yc);
	}
	return (f[0]|f[1])==0?true:false;
}

inline bool ClipLineZoomed(SLong *x,SLong *y,UWord *f,SLong *xc,SLong *yc)
{
	Float frac;
	SLong temp;
	UWord temp2;

	if ((f[0]|f[1])&CF3D_OFFTOP)
	{
		if (f[0]&CF3D_OFFTOP)
		{
			temp=x[0]; x[0]=x[1]; x[1]=temp;
			temp=y[0]; y[0]=y[1]; y[1]=temp;
			temp2=f[0]; f[0]=f[1]; f[1]=temp2;
		}
		frac=Float(yc[0]-y[0])/Float(y[1]-y[0]);
		y[1]=yc[0];
		x[1]=x[0]+SLong(frac*Float(x[1]-x[0]));
		f[1]=MapClipFlagsZoomed(x[1],y[1],xc,yc);
	}

	if ((f[0]|f[1])&CF3D_OFFBOTTOM)
	{
		if (f[0]&CF3D_OFFBOTTOM)
		{
			temp=x[0]; x[0]=x[1]; x[1]=temp;
			temp=y[0]; y[0]=y[1]; y[1]=temp;
			temp2=f[0]; f[0]=f[1]; f[1]=temp2;
		}
		frac=Float(yc[1]-y[0])/Float(y[1]-y[0]);
		y[1]=yc[1];
		x[1]=x[0]+SLong(frac*Float(x[1]-x[0]));
		f[1]=MapClipFlagsZoomed(x[1],y[1],xc,yc);
	}

	if ((f[0]|f[1])&CF3D_OFFLEFT)
	{
		if (f[0]&CF3D_OFFLEFT)
		{
			temp=x[0]; x[0]=x[1]; x[1]=temp;
			temp=y[0]; y[0]=y[1]; y[1]=temp;
			temp2=f[0]; f[0]=f[1]; f[1]=temp2;
		}
		frac=Float(xc[0]-x[0])/Float(x[1]-x[0]);
		x[1]=xc[0];
		y[1]=y[0]+SLong(frac*Float(y[1]-y[0]));
		f[1]=MapClipFlagsZoomed(x[1],y[1],xc,yc);
	}

	if ((f[0]|f[1])&CF3D_OFFRIGHT)
	{
		if (f[0]&CF3D_OFFRIGHT)
		{
			temp=x[0]; x[0]=x[1]; x[1]=temp;
			temp=y[0]; y[0]=y[1]; y[1]=temp;
			temp2=f[0]; f[0]=f[1]; f[1]=temp2;
		}
		frac=Float(xc[1]-x[0])/Float(x[1]-x[0]);
		x[1]=xc[1];
		y[1]=y[0]+SLong(frac*Float(y[1]-y[0]));
		f[1]=MapClipFlagsZoomed(x[1],y[1],xc,yc);
	}
	return (f[0]|f[1])==0?true:false;
}

void MapScr::ShowWaypointIcon(SWord x,SWord y,WayPointPtr waypt)
{
	struct SAircraftIconDef{
		ImageMapNumber mapno;
		SWord x,y,w,h;
	};
	struct SMapAircraft{
		SAircraftIconDef standard,playerac,caller,messagesubject;
	};
	static SMapAircraft waypoint_map=
	{
		{MAPCHAPNO,0,48,3,3},	//standard waypt
		{MAPCHAPNO,16,48,3,3},	//player current waypt
		{MAPCHAPNO,0,48,6,6},	//standard waypt SELECTED
		{MAPCHAPNO,16,48,6,6}	//player current waypt SELECTED
	};
	const Float p_w=OverLay.physicalWidth;
	const Float p_h=OverLay.physicalHeight;

	//generate clipping values in physical pixels
	FRect clip;

	clip.left=Float(MAP_SCREEN_ORIGIN_X_640)*p_w/Float(640);
	clip.right=Float(MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1)*p_w/Float(640);
	clip.top=Float(MAP_SCREEN_ORIGIN_Y_640)*p_h/Float(480);
	clip.bottom=Float(MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1)*p_h/Float(480);

	//convert input pixels 640 to physical screen pixels

	Float p_x,p_y;

	p_x=Float(x)*p_w/Float(640);
	p_y=Float(y)*p_h/Float(480);

	//select icon to render

	DoPointStruc dp[4];
	ImageMapDesc* pmap;
	SAircraftIconDef* selectedIcon;

	if (waypt==Manual_Pilot.ControlledAC2->waypoint)
	{
		if (waypt==OverLay.curr_waypoint)	selectedIcon=&waypoint_map.messagesubject;
		else								selectedIcon=&waypoint_map.playerac;
	}
	else
	{
		if (waypt==OverLay.curr_waypoint)	selectedIcon=&waypoint_map.caller;
		else								selectedIcon=&waypoint_map.standard;
	}

	pmap=Image_Map.GetImageMapPtr(selectedIcon->mapno);
	const SWord map_w=selectedIcon->w;
	const SWord map_h=selectedIcon->h;
	Float f_w_2,f_h_2;
	f_w_2=Float(map_w>>1);
	f_h_2=Float(map_h>>1);
	dp[0].bodyx.f=dp[3].bodyx.f=int(p_x-f_w_2);
	dp[0].ix=dp[3].ix=selectedIcon->x;
	dp[1].bodyx.f=dp[2].bodyx.f=dp[3].bodyx.f+map_w;
	dp[1].ix=dp[2].ix=selectedIcon->x+map_w;
	dp[0].bodyy.f=dp[1].bodyy.f=int(p_y-f_h_2);
	dp[0].iy=dp[1].iy=selectedIcon->y;
	dp[2].bodyy.f=dp[3].bodyy.f=dp[1].bodyy.f+map_h;
	dp[2].iy=dp[3].iy=selectedIcon->y+map_h;
	OverLay.ClippedPutC(dp,pmap,clip);
}

void MapScr::ShowAircraftRoute(AirStrucPtr itemPtr,SWord *x,SWord *y,bool flag)
{
	//skip to itemPtr's first waypoint...
	WayPointPtr lastwaypt=NULL,waypt=itemPtr->waypoint;

	SWord xc_640[2],yc_640[2];
	xc_640[0]=MAP_SCREEN_ORIGIN_X_640;
	xc_640[1]=MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1;
	yc_640[0]=MAP_SCREEN_ORIGIN_Y_640;
	yc_640[1]=MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1;

	COORDS3D home_pos;
	COORDS3D start_pos;

	if (waypt!=NULL)
	{
		waypt=FindFirstWP(itemPtr->uniqueID,waypt);	//while (waypt->prev) waypt=waypt->prev;
		start_pos=*::FindDesPos(waypt);
		if (itemPtr->ai.homebase)
		{
			home_pos=itemPtr->ai.homebase->World;
			//draw a line from home_pos to start_pos
			SWord wx[2],wy[2];
			UWord cf[2];

			wx[0]=WorldXToSx640(start_pos.X,x);
			wy[0]=WorldZToSy640(start_pos.Z,y);

			wx[1]=WorldXToSx640(home_pos.X,x);
			wy[1]=WorldZToSy640(home_pos.Z,y);

			cf[0]=MapClipFlags(wx[0],wy[0],xc_640,yc_640);
			cf[1]=MapClipFlags(wx[1],wy[1],xc_640,yc_640);

			if ((cf[0]&cf[1])==0)
			{
				//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
				if ((cf[0]|cf[1])==0 || ClipLine(wx,wy,cf,xc_640,yc_640))
				{
					const Float p_w=OverLay.physicalWidth;
					const Float p_h=OverLay.physicalHeight;
					for (int i=1;i>=0;i--)
					{
						wx[i]=SWord(Float(wx[i])*p_w/Float(640));
						wy[i]=SWord(Float(wy[i])*p_h/Float(480));
					}
					OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
				}
			}
		}
		lastwaypt=waypt;
		waypt=FindNextWP(itemPtr->uniqueID,waypt);	//waypt->next;
		while (waypt!=NULL)
		{
			COORDS3D end_pos=*::FindDesPos(waypt);
			SWord wx[2],wy[2];
			UWord cf[2];

			wx[0]=WorldXToSx640(start_pos.X,x);
			wy[0]=WorldZToSy640(start_pos.Z,y);

			wx[1]=WorldXToSx640(end_pos.X,x);
			wy[1]=WorldZToSy640(end_pos.Z,y);

			cf[0]=MapClipFlags(wx[0],wy[0],xc_640,yc_640);
			cf[1]=MapClipFlags(wx[1],wy[1],xc_640,yc_640);

			if ((cf[0]&cf[1])==0)
			{
				if (cf[0]==0) ShowWaypointIcon(wx[0],wy[0],lastwaypt);
				//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
				if ((cf[0]|cf[1])==0 || ClipLine(wx,wy,cf,xc_640,yc_640))
				{
					const Float p_w=OverLay.physicalWidth;
					const Float p_h=OverLay.physicalHeight;
					for (int i=1;i>=0;i--)
					{
						wx[i]=SWord(Float(wx[i])*p_w/Float(640));
						wy[i]=SWord(Float(wy[i])*p_h/Float(480));
					}
					OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
				}
			}
			start_pos=end_pos;
			lastwaypt=waypt;
			waypt=waypt->next;
		}
		if (itemPtr->ai.homebase)
		{
			start_pos=*::FindDesPos(lastwaypt);
			//draw a line from home_pos to start_pos
			SWord wx[2],wy[2];
			UWord cf[2];

			wx[0]=WorldXToSx640(start_pos.X,x);
			wy[0]=WorldZToSy640(start_pos.Z,y);

			wx[1]=WorldXToSx640(home_pos.X,x);
			wy[1]=WorldZToSy640(home_pos.Z,y);

			cf[0]=MapClipFlags(wx[0],wy[0],xc_640,yc_640);
			cf[1]=MapClipFlags(wx[1],wy[1],xc_640,yc_640);

			if ((cf[0]&cf[1])==0)
			{
				if (cf[0]==0) ShowWaypointIcon(wx[0],wy[0],lastwaypt);
				//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
				if ((cf[0]|cf[1])==0 || ClipLine(wx,wy,cf,xc_640,yc_640))
				{
					const Float p_w=OverLay.physicalWidth;
					const Float p_h=OverLay.physicalHeight;
					for (int i=1;i>=0;i--)
					{
						wx[i]=SWord(Float(wx[i])*p_w/Float(640));
						wy[i]=SWord(Float(wy[i])*p_h/Float(480));
					}
					OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
				}
			}
		}
	}
	if (flag)// && itemPtr->waypoint)	//draw line from pilotedac pos to current waypoint...
	{
		if (itemPtr->waypoint)	home_pos=*(itemPtr->waypoint->FindDesPos());
		else					home_pos=itemPtr->ai.homebase->World;
		start_pos=itemPtr->World;
		//draw a line from home_pos to start_pos
		SWord wx[2],wy[2];
		UWord cf[2];

		wx[0]=WorldXToSx640(start_pos.X,x);
		wy[0]=WorldZToSy640(start_pos.Z,y);

		wx[1]=WorldXToSx640(home_pos.X,x);
		wy[1]=WorldZToSy640(home_pos.Z,y);

		cf[0]=MapClipFlags(wx[0],wy[0],xc_640,yc_640);
		cf[1]=MapClipFlags(wx[1],wy[1],xc_640,yc_640);

		if ((cf[0]&cf[1])==0)
		{
			//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
			if ((cf[0]|cf[1])==0 || ClipLine(wx,wy,cf,xc_640,yc_640))
			{
				const Float p_w=OverLay.physicalWidth;
				const Float p_h=OverLay.physicalHeight;
				for (int i=1;i>=0;i--)
				{
					wx[i]=SWord(Float(wx[i])*p_w/Float(640));
					wy[i]=SWord(Float(wy[i])*p_h/Float(480));
				}
				OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
			}
		}
	}
}

void MapScr::ShowAircraftRouteHi(AirStrucPtr itemPtr,SWord *x,SWord *y,bool flag)
{
	//skip to itemPtr's first waypoint...
	WayPointPtr lastwaypt=NULL,waypt=itemPtr->waypoint;

	SWord xc_640[2],yc_640[2];
	xc_640[0]=MAP_SCREEN_ORIGIN_X_640;
	xc_640[1]=MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1;
	yc_640[0]=MAP_SCREEN_ORIGIN_Y_640;
	yc_640[1]=MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1;

	COORDS3D home_pos;
	COORDS3D start_pos;

	if (waypt!=NULL)
	{
		waypt=FindFirstWP(itemPtr->uniqueID,waypt);	//while (waypt->prev) waypt=waypt->prev;
		start_pos=*::FindDesPos(waypt);
		if (itemPtr->ai.homebase)
		{
			home_pos=itemPtr->ai.homebase->World;
			//draw a line from home_pos to start_pos
			SWord wx[2],wy[2];
			UWord cf[2];

			wx[0]=WorldXToSx640Hi(start_pos.X,x);
			wy[0]=WorldZToSy640Hi(start_pos.Z,y);

			wx[1]=WorldXToSx640Hi(home_pos.X,x);
			wy[1]=WorldZToSy640Hi(home_pos.Z,y);

			cf[0]=MapClipFlags(wx[0],wy[0],xc_640,yc_640);
			cf[1]=MapClipFlags(wx[1],wy[1],xc_640,yc_640);

			if ((cf[0]&cf[1])==0)
			{
				//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
				if ((cf[0]|cf[1])==0 || ClipLine(wx,wy,cf,xc_640,yc_640))
				{
					const Float p_w=OverLay.physicalWidth;
					const Float p_h=OverLay.physicalHeight;
					for (int i=1;i>=0;i--)
					{
						wx[i]=SWord(Float(wx[i])*p_w/Float(640));
						wy[i]=SWord(Float(wy[i])*p_h/Float(480));
					}
					OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
				}
			}
		}
		lastwaypt=waypt;
		waypt=FindNextWP(itemPtr->uniqueID,waypt);	//waypt->next;
		while (waypt!=NULL)
		{
			COORDS3D end_pos=*::FindDesPos(waypt);
			SWord wx[2],wy[2];
			UWord cf[2];

			wx[0]=WorldXToSx640Hi(start_pos.X,x);
			wy[0]=WorldZToSy640Hi(start_pos.Z,y);

			wx[1]=WorldXToSx640Hi(end_pos.X,x);
			wy[1]=WorldZToSy640Hi(end_pos.Z,y);

			cf[0]=MapClipFlags(wx[0],wy[0],xc_640,yc_640);
			cf[1]=MapClipFlags(wx[1],wy[1],xc_640,yc_640);

			if ((cf[0]&cf[1])==0)
			{
				if (cf[0]==0) ShowWaypointIcon(wx[0],wy[0],lastwaypt);
				//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
				if ((cf[0]|cf[1])==0 || ClipLine(wx,wy,cf,xc_640,yc_640))
				{
					const Float p_w=OverLay.physicalWidth;
					const Float p_h=OverLay.physicalHeight;
					for (int i=1;i>=0;i--)
					{
						wx[i]=SWord(Float(wx[i])*p_w/Float(640));
						wy[i]=SWord(Float(wy[i])*p_h/Float(480));
					}
					OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
				}
			}
			start_pos=end_pos;
			lastwaypt=waypt;
			waypt=waypt->next;
		}
		if (itemPtr->ai.homebase)
		{
			start_pos=*::FindDesPos(lastwaypt);
			//draw a line from home_pos to start_pos
			SWord wx[2],wy[2];
			UWord cf[2];

			wx[0]=WorldXToSx640Hi(start_pos.X,x);
			wy[0]=WorldZToSy640Hi(start_pos.Z,y);

			wx[1]=WorldXToSx640Hi(home_pos.X,x);
			wy[1]=WorldZToSy640Hi(home_pos.Z,y);

			cf[0]=MapClipFlags(wx[0],wy[0],xc_640,yc_640);
			cf[1]=MapClipFlags(wx[1],wy[1],xc_640,yc_640);

			if ((cf[0]&cf[1])==0)
			{
				if (cf[0]==0) ShowWaypointIcon(wx[0],wy[0],lastwaypt);
				//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
				if ((cf[0]|cf[1])==0 || ClipLine(wx,wy,cf,xc_640,yc_640))
				{
					const Float p_w=OverLay.physicalWidth;
					const Float p_h=OverLay.physicalHeight;
					for (int i=1;i>=0;i--)
					{
						wx[i]=SWord(Float(wx[i])*p_w/Float(640));
						wy[i]=SWord(Float(wy[i])*p_h/Float(480));
					}
					OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
				}
			}
		}
	}
	if (flag)// && itemPtr->waypoint)	//draw line from pilotedac pos to current waypoint...
	{
		if (itemPtr->waypoint)	home_pos=*(itemPtr->waypoint->FindDesPos());
		else					home_pos=itemPtr->ai.homebase->World;
		start_pos=itemPtr->World;
		//draw a line from home_pos to start_pos
		SWord wx[2],wy[2];
		UWord cf[2];

		wx[0]=WorldXToSx640Hi(start_pos.X,x);
		wy[0]=WorldZToSy640Hi(start_pos.Z,y);

		wx[1]=WorldXToSx640Hi(home_pos.X,x);
		wy[1]=WorldZToSy640Hi(home_pos.Z,y);

		cf[0]=MapClipFlags(wx[0],wy[0],xc_640,yc_640);
		cf[1]=MapClipFlags(wx[1],wy[1],xc_640,yc_640);

		if ((cf[0]&cf[1])==0)
		{
			//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
			if ((cf[0]|cf[1])==0 || ClipLine(wx,wy,cf,xc_640,yc_640))
			{
				const Float p_w=OverLay.physicalWidth;
				const Float p_h=OverLay.physicalHeight;
				for (int i=1;i>=0;i--)
				{
					wx[i]=SWord(Float(wx[i])*p_w/Float(640));
					wy[i]=SWord(Float(wy[i])*p_h/Float(480));
				}
				OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
			}
		}
	}
}

void MapScr::ShowAircraftRouteZoomed(AirStrucPtr itemPtr,SLong *x,SLong *y,bool flag)
{
	//skip to itemPtr's first waypoint...
	WayPointPtr lastwaypt=NULL,waypt=itemPtr->waypoint;

	SLong xc_640[2],yc_640[2];
	xc_640[0]=MAP_SCREEN_ORIGIN_X_640;
	xc_640[1]=MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1;
	yc_640[0]=MAP_SCREEN_HRTOP_640;	//ORIGIN_Y_640;
	yc_640[1]=MAP_SCREEN_HRBOT_640-1;	//ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1;

	COORDS3D home_pos;
	COORDS3D start_pos;

	if (waypt!=NULL)
	{
		while (waypt->prev) waypt=waypt->prev;
		start_pos=*::FindDesPos(waypt);
		if (itemPtr->ai.homebase)
		{
			home_pos=itemPtr->ai.homebase->World;
			//draw a line from home_pos to start_pos
			SLong wx[2],wy[2];
			UWord cf[2];

			wx[0]=WorldXToSx640Zoomed(start_pos.X,x);
			wy[0]=WorldZToSy640Zoomed(start_pos.Z,y);

			wx[1]=WorldXToSx640Zoomed(home_pos.X,x);
			wy[1]=WorldZToSy640Zoomed(home_pos.Z,y);

			cf[0]=MapClipFlagsZoomed(wx[0],wy[0],xc_640,yc_640);
			cf[1]=MapClipFlagsZoomed(wx[1],wy[1],xc_640,yc_640);

			if ((cf[0]&cf[1])==0)
			{
				//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
				if ((cf[0]|cf[1])==0 || ClipLineZoomed(wx,wy,cf,xc_640,yc_640))
				{
					const Float p_w=OverLay.physicalWidth;
					const Float p_h=OverLay.physicalHeight;
					for (int i=1;i>=0;i--)
					{
						wx[i]=SWord(Float(wx[i])*p_w/Float(640));
						wy[i]=SWord(Float(wy[i])*p_h/Float(480));
					}
					OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
				}
			}
		}
		lastwaypt=waypt;
		waypt=waypt->next;
		while (waypt!=NULL)
		{
			COORDS3D end_pos=*::FindDesPos(waypt);
			SLong wx[2],wy[2];
			UWord cf[2];

			wx[0]=WorldXToSx640Zoomed(start_pos.X,x);
			wy[0]=WorldZToSy640Zoomed(start_pos.Z,y);

			wx[1]=WorldXToSx640Zoomed(end_pos.X,x);
			wy[1]=WorldZToSy640Zoomed(end_pos.Z,y);

			cf[0]=MapClipFlagsZoomed(wx[0],wy[0],xc_640,yc_640);
			cf[1]=MapClipFlagsZoomed(wx[1],wy[1],xc_640,yc_640);

			if ((cf[0]&cf[1])==0)
			{
				if (cf[0]==0) ShowWaypointIcon(wx[0],wy[0],lastwaypt);
				//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
				if ((cf[0]|cf[1])==0 || ClipLineZoomed(wx,wy,cf,xc_640,yc_640))
				{
					const Float p_w=OverLay.physicalWidth;
					const Float p_h=OverLay.physicalHeight;
					for (int i=1;i>=0;i--)
					{
						wx[i]=SWord(Float(wx[i])*p_w/Float(640));
						wy[i]=SWord(Float(wy[i])*p_h/Float(480));
					}
					OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
				}
			}
			start_pos=end_pos;
			lastwaypt=waypt;
			waypt=waypt->next;
		}
		if (itemPtr->ai.homebase)
		{
			start_pos=*::FindDesPos(lastwaypt);
			//draw a line from home_pos to start_pos
			SLong wx[2],wy[2];
			UWord cf[2];

			wx[0]=WorldXToSx640Zoomed(start_pos.X,x);
			wy[0]=WorldZToSy640Zoomed(start_pos.Z,y);

			wx[1]=WorldXToSx640Zoomed(home_pos.X,x);
			wy[1]=WorldZToSy640Zoomed(home_pos.Z,y);

			cf[0]=MapClipFlagsZoomed(wx[0],wy[0],xc_640,yc_640);
			cf[1]=MapClipFlagsZoomed(wx[1],wy[1],xc_640,yc_640);

			if ((cf[0]&cf[1])==0)
			{
				if (cf[0]==0) ShowWaypointIcon(wx[0],wy[0],lastwaypt);
				//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
				if ((cf[0]|cf[1])==0 || ClipLineZoomed(wx,wy,cf,xc_640,yc_640))
				{
					const Float p_w=OverLay.physicalWidth;
					const Float p_h=OverLay.physicalHeight;
					for (int i=1;i>=0;i--)
					{
						wx[i]=SWord(Float(wx[i])*p_w/Float(640));
						wy[i]=SWord(Float(wy[i])*p_h/Float(480));
					}
					OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
				}
			}
		}
	}
	if (flag)	// && itemPtr->waypoint)	//draw line from pilotedac pos to current waypoint...
	{
		if (itemPtr->waypoint)	home_pos=*(itemPtr->waypoint->FindDesPos());
		else					home_pos=itemPtr->ai.homebase->World;
		start_pos=itemPtr->World;
		//draw a line from home_pos to start_pos
		SLong wx[2],wy[2];
		UWord cf[2];

		wx[0]=WorldXToSx640Zoomed(start_pos.X,x);
		wy[0]=WorldZToSy640Zoomed(start_pos.Z,y);

		wx[1]=WorldXToSx640Zoomed(home_pos.X,x);
		wy[1]=WorldZToSy640Zoomed(home_pos.Z,y);

		cf[0]=MapClipFlagsZoomed(wx[0],wy[0],xc_640,yc_640);
		cf[1]=MapClipFlagsZoomed(wx[1],wy[1],xc_640,yc_640);

		if ((cf[0]&cf[1])==0)
		{
			//clip the waypoint line between (wx[0],wy[0]) and (wx[1],wy[1])
			if ((cf[0]|cf[1])==0 || ClipLineZoomed(wx,wy,cf,xc_640,yc_640))
			{
				const Float p_w=OverLay.physicalWidth;
				const Float p_h=OverLay.physicalHeight;
				for (int i=1;i>=0;i--)
				{
					wx[i]=SWord(Float(wx[i])*p_w/Float(640));
					wy[i]=SWord(Float(wy[i])*p_h/Float(480));
				}
				OverLay.DrawLine(wx[0],wy[0],wx[1],wy[1],Colour(252));
			}
		}
	}
}

void MapScr::ShowAircraftIcon(SWord x,SWord y,AirStrucPtr ip)
{
	struct SAircraftIconDef{
		ImageMapNumber mapno;
		SWord x,y,w,h;
	};
	struct SMapAircraft{
		SAircraftIconDef standard,playerac,caller,messagesubject;
	};
	static SMapAircraft map_red_ac=
	{
		{MAPCHAPNO,0,32,16,16},	//standard red
		{MAPCHAPNO,16,32,16,16},	//player red outline
		{MAPCHAPNO,32,32,16,16},	//caller red outline
		{MAPCHAPNO,48,32,16,16}	//message subject red outline
	};
	static SMapAircraft map_blue_ac=
	{
		{MAPCHAPNO,0,0,16,16},	//standard blue outline
		{MAPCHAPNO,16,0,16,16},	//player blue outline
		{MAPCHAPNO,32,0,16,16},	//caller blue outline
		{MAPCHAPNO,48,0,16,16}	//message subject blue outline
	};

	const Float p_w=OverLay.physicalWidth;
	const Float p_h=OverLay.physicalHeight;

	//generate clipping values in physical pixels
	FRect clip;

	clip.left=Float(MAP_SCREEN_ORIGIN_X_640)*p_w/Float(640);
	clip.right=Float(MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1)*p_w/Float(640);
	clip.top=Float(MAP_SCREEN_ORIGIN_Y_640)*p_h/Float(480);
	clip.bottom=Float(MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1)*p_h/Float(480);

	//convert input pixels 640 to physical screen pixels

	Float p_x,p_y;

	p_x=Float(x)*p_w/Float(640);
	p_y=Float(y)*p_h/Float(480);

	//select icon to render

	DoPointStruc dp[4];
	ImageMapDesc* pmap;
	SAircraftIconDef* selectedIcon;
	SMapAircraft* selectedSide;

	if (ip->nationality==NAT_BLUE)	selectedSide=&map_blue_ac;
	else							selectedSide=&map_red_ac;

	bool noOutline=false;

	if (ip==Manual_Pilot.ControlledAC2)				selectedIcon=&selectedSide->playerac;
	else if (ip==OverLay.message_caller)			selectedIcon=&selectedSide->caller;
	else if (itemptr(ip)==OverLay.message_target)	selectedIcon=&selectedSide->messagesubject;
	else
	{
		noOutline=true;
		selectedIcon=&selectedSide->standard;
	}
	pmap=Image_Map.GetImageMapPtr(selectedIcon->mapno);
	const SWord map_w=selectedIcon->w;
	const SWord map_h=selectedIcon->h;
	Float f_w_2,f_h_2;
	f_w_2=Float(map_w>>1);
	f_h_2=Float(map_h>>1);
	dp[0].bodyx.f=dp[3].bodyx.f=int(p_x-f_w_2);
	dp[0].ix=dp[3].ix=selectedIcon->x;
	dp[1].bodyx.f=dp[2].bodyx.f=dp[3].bodyx.f+map_w;
	dp[1].ix=dp[2].ix=selectedIcon->x+map_w;
	dp[0].bodyy.f=dp[1].bodyy.f=int(p_y-f_h_2);
	dp[0].iy=dp[1].iy=selectedIcon->y;
	dp[2].bodyy.f=dp[3].bodyy.f=dp[1].bodyy.f+map_h;
	dp[2].iy=dp[3].iy=selectedIcon->y+map_h;
	if (!noOutline) OverLay.ClippedPutC(dp,pmap,clip);

	//rotate coordinates to show the ac heading...
 	SWord sinAng,cosAng;
	ANGLES hdgAng=-ip->hdg;
	Math_Lib.high_sin_cos(hdgAng,sinAng,cosAng);

	//generate 2D rotation matrix
	Float m[4];
	const Float af(ANGLES_FRACT);
	m[0]=m[3]=Float(cosAng)/af;
	m[1]=Float(sinAng)/af;
	m[2]=-Float(sinAng)/af;

	selectedIcon=&selectedSide->standard;
	dp[0].ix=dp[3].ix=selectedIcon->x;
	dp[1].ix=dp[2].ix=selectedIcon->x+map_w;
	dp[0].iy=dp[1].iy=selectedIcon->y;
	dp[2].iy=dp[3].iy=selectedIcon->y+map_h;

	bool abortDraw=false;

	for (int i=3;i>=0 && !abortDraw;i--)
	{
		Float tx,ty;
		tx=dp[i].bodyx.f-p_x;
		ty=dp[i].bodyy.f-p_y;
		dp[i].bodyx.f=p_x+(m[0]*tx+m[1]*ty);
		dp[i].bodyy.f=p_y+(m[2]*tx+m[3]*ty);

		if (dp[i].bodyx.f<=clip.left ||
			dp[i].bodyx.f>=clip.right ||
			dp[i].bodyy.f<=clip.top ||
			dp[i].bodyy.f>=clip.bottom)
			abortDraw=true;
	}
	if (!abortDraw) OverLay.ClippedPutC(dp,pmap,clip);
}

void MapScr::ShowAircraftIcons(SWord *x,SWord *y,bool flag)
{
	SWord xc_640[2],yc_640[2];
	xc_640[0]=MAP_SCREEN_ORIGIN_X_640;
	xc_640[1]=MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1;
	yc_640[0]=MAP_SCREEN_ORIGIN_Y_640;
	yc_640[1]=MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1;

	AirStrucPtr itemPtr=(AirStrucPtr)OverLay.pvp->GetFirstAC();

	while (itemPtr!=NULL)
	{
		if (!itemPtr->Status.deadtime && 
			(itemPtr->nationality==Manual_Pilot.ControlledAC2->nationality || Save_Data.gamedifficulty[GD_VISIBLEMIGSCHEAT]))
		{
			SWord sx_640,sy_640;

			sx_640=WorldXToSx640(itemPtr->World.X,x);
			sy_640=WorldZToSy640(itemPtr->World.Z,y);

			if (itemPtr==Manual_Pilot.ControlledAC2 || (!flag && itemPtr->formpos==0))
			{
				if (MapClipFlags(sx_640,sy_640,xc_640,yc_640)==0)
					ShowAircraftIcon(sx_640,sy_640,itemPtr);
			}
		}
		itemPtr=(AirStrucPtr)OverLay.pvp->GetNextAC(itemPtr);
	}
}

void MapScr::ShowAircraftIconsHi(SWord *x,SWord *y,bool flag)
{
	SWord xc_640[2],yc_640[2];
	xc_640[0]=MAP_SCREEN_ORIGIN_X_640;
	xc_640[1]=MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1;
	yc_640[0]=MAP_SCREEN_ORIGIN_Y_640;
	yc_640[1]=MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1;

	AirStrucPtr itemPtr=(AirStrucPtr)OverLay.pvp->GetFirstAC();

	while (itemPtr!=NULL)
	{
		if (!itemPtr->Status.deadtime && 
			(itemPtr->nationality==Manual_Pilot.ControlledAC2->nationality || Save_Data.gamedifficulty[GD_VISIBLEMIGSCHEAT]))
		{
			SWord sx_640,sy_640;

			sx_640=WorldXToSx640Hi(itemPtr->World.X,x);
			sy_640=WorldZToSy640Hi(itemPtr->World.Z,y);

			if (itemPtr==Manual_Pilot.ControlledAC2 || (!flag && itemPtr->formpos==0))
			{
				if (MapClipFlags(sx_640,sy_640,xc_640,yc_640)==0)
					ShowAircraftIcon(sx_640,sy_640,itemPtr);
			}
		}
		itemPtr=(AirStrucPtr)OverLay.pvp->GetNextAC(itemPtr);
	}
}

void MapScr::ShowAircraftIconsZoomed(SLong *x,SLong *y,bool flag)
{
	SWord xc_640[2],yc_640[2];
	xc_640[0]=MAP_SCREEN_ORIGIN_X_640;
	xc_640[1]=MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1;
	yc_640[0]=MAP_SCREEN_ORIGIN_Y_640;
	yc_640[1]=MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1;

	AirStrucPtr itemPtr=(AirStrucPtr)OverLay.pvp->GetFirstAC();

	while (itemPtr!=NULL)
	{
		if (!itemPtr->Status.deadtime)
		{
			SWord sx_640,sy_640;

			sx_640=WorldXToSx640Zoomed(itemPtr->World.X,x);
			sy_640=WorldZToSy640Zoomed(itemPtr->World.Z,y);

			if (itemPtr==Manual_Pilot.ControlledAC2 || !flag)
			{
				if (MapClipFlags(sx_640,sy_640,xc_640,yc_640)==0)
					ShowAircraftIcon(sx_640,sy_640,itemPtr);
			}
		}
		itemPtr=(AirStrucPtr)OverLay.pvp->GetNextAC(itemPtr);
	}
}

void MapScr::ShowTargetIcon(SWord x,SWord y,itemptr ip)
{
	struct SAircraftIconDef{
		ImageMapNumber mapno;
		SWord x,y,w,h;
	};
	static SAircraftIconDef targ_icon_def={MAPCHAPNO,0,16,16,16};

	const Float p_w=OverLay.physicalWidth;
	const Float p_h=OverLay.physicalHeight;

	//generate clipping values in physical pixels
	FRect clip;

	clip.left=Float(MAP_SCREEN_ORIGIN_X_640)*p_w/Float(640);
	clip.right=Float(MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1)*p_w/Float(640);
	clip.top=Float(MAP_SCREEN_ORIGIN_Y_640)*p_h/Float(480);
	clip.bottom=Float(MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1)*p_h/Float(480);

	//convert input pixels 640 to physical screen pixels

	Float p_x,p_y;

	p_x=Float(x)*p_w/Float(640);
	p_y=Float(y)*p_h/Float(480);

	//select icon to render

	DoPointStruc dp[4];
	ImageMapDesc* pmap;
	SAircraftIconDef* selectedIcon=&targ_icon_def;
	pmap=Image_Map.GetImageMapPtr(selectedIcon->mapno);
	const SWord map_w=selectedIcon->w;
	const SWord map_h=selectedIcon->h;
	Float f_w_2,f_h_2;
	f_w_2=Float(map_w>>1);
	f_h_2=Float(map_h>>1);
	dp[0].bodyx.f=dp[3].bodyx.f=int(p_x-f_w_2);
	dp[0].ix=dp[3].ix=selectedIcon->x;
	dp[1].bodyx.f=dp[2].bodyx.f=dp[3].bodyx.f+map_w;
	dp[1].ix=dp[2].ix=selectedIcon->x+map_w;
	dp[0].bodyy.f=dp[1].bodyy.f=int(p_y-f_h_2);
	dp[0].iy=dp[1].iy=selectedIcon->y;
	dp[2].bodyy.f=dp[3].bodyy.f=dp[1].bodyy.f+map_h;
	dp[2].iy=dp[3].iy=selectedIcon->y+map_h;
	OverLay.ClippedPutC(dp,pmap,clip);
}

void MapScr::ShowTargetLocation(itemptr itemPtr,SWord *x,SWord *y)
{
	if (itemPtr!=NULL)
	{
		SWord xc_640[2],yc_640[2];
		xc_640[0]=MAP_SCREEN_ORIGIN_X_640;
		xc_640[1]=MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1;
		yc_640[0]=MAP_SCREEN_ORIGIN_Y_640;
		yc_640[1]=MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1;

		SWord sx_640,sy_640;
		sx_640=WorldXToSx640(itemPtr->World.X,x);
		sy_640=WorldZToSy640(itemPtr->World.Z,y);
		if (MapClipFlags(sx_640,sy_640,xc_640,yc_640)==0) ShowTargetIcon(sx_640,sy_640,itemPtr);
	}
}

void MapScr::ShowTargetLocationHi(itemptr itemPtr,SWord *x,SWord *y)
{
	if (itemPtr!=NULL)
	{
		SWord xc_640[2],yc_640[2];
		xc_640[0]=MAP_SCREEN_ORIGIN_X_640;
		xc_640[1]=MAP_SCREEN_ORIGIN_X_640+MAP_SCREEN_WIDTH_640-1;
		yc_640[0]=MAP_SCREEN_ORIGIN_Y_640;
		yc_640[1]=MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640-1;

		SWord sx_640,sy_640;
		sx_640=WorldXToSx640Hi(itemPtr->World.X,x);
		sy_640=WorldZToSy640Hi(itemPtr->World.Z,y);
		if (MapClipFlags(sx_640,sy_640,xc_640,yc_640)==0) ShowTargetIcon(sx_640,sy_640,itemPtr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShowItemIcons
//Author		Paul.   
//Date			Tue 2 Mar 1999
//------------------------------------------------------------------------------
void MapScr::ShowItemIcons(bool flag)
{
	//flag==true if on waypoint screen & false if not

	//display the map background and generate the
	//parameters needed to calculate the screen coordinates
	//for anything else that needs to go on the map

//#pragma message(__HERE__"Comment this block in when Rod defines the key")
	if (Key_Tests.KeyPress3d(SEEMIGS))
	{
		if (Save_Data.gamedifficulty[GD_VISIBLEMIGSCHEAT])
			Save_Data.gamedifficulty%=GD_VISIBLEMIGSCHEAT;
		else
			Save_Data.gamedifficulty|=GD_VISIBLEMIGSCHEAT;
	}

	SWord x[2],y[2];
	ShowBackgroundMapHi(Manual_Pilot.ControlledAC2->World,x,y);
	ShowAircraftRouteHi(Manual_Pilot.ControlledAC2,x,y,true);	//flag);
	ShowTargetLocationHi(OverLay.target_item,x,y);
	ShowAircraftIconsHi(x,y,flag);
}
//DeadCode DAW 27Aug99 	ShowBackgroundMap(Manual_Pilot.ControlledAC2->World,x,y);
//DeadCode DAW 27Aug99 	ShowAircraftRoute(Manual_Pilot.ControlledAC2,x,y,true);	//flag);
//DeadCode DAW 27Aug99 	ShowTargetLocation(OverLay.target_item,x,y);
//DeadCode DAW 27Aug99 	ShowAircraftIcons(x,y,flag);
//DeadCode DAW 27Aug99 }

void MapScr::ShowItemIconsZoomed(bool flag)
{
	SLong x[2],y[2];
	//generate world coordinated of the area covered by the 
	//map window...
	SLong offset=OverLay.pvp->World.Y;
	x[0]=OverLay.pvp->World.X-offset;
	x[1]=OverLay.pvp->World.X+offset;
	y[0]=OverLay.pvp->World.Z+offset;
	y[1]=OverLay.pvp->World.Z-offset;
	ShowAircraftRouteZoomed(Manual_Pilot.ControlledAC2,x,y,true);	//flag);
	ShowAircraftIconsZoomed(x,y,flag);
}

void MapScr::ShowBackgroundMapHiRez()
{
	//wipe strip @ top & bottom of the map
	SLong width,height;
	width=OverLay.physicalWidth;
	height=OverLay.physicalHeight;
	Float fx,fy,fw,fh;
	SLong x,y,w,h;
	fx=Float(MAP_SCREEN_ORIGIN_X_640)*Float(width)/640.;
	fy=Float(MAP_SCREEN_ORIGIN_Y_640)*Float(height)/480.;
	fw=Float(MAP_SCREEN_WIDTH_640)*Float(width)/640.;
	fh=(Float(MAP_SCREEN_HRTOP_640)*Float(height)/480.)-fy;
	x=SLong(fx);
	y=SLong(fy);
	w=SLong(fw);
	h=SLong(fh);
	OverLay.pw->DoSetGlobalAlpha(255);
	OverLay.pw->DoSmokedGlassBox(x,y,w,h,0xFFB0BCC0);
	fy=Float(MAP_SCREEN_HRBOT_640)*Float(height)/480.;
	x=SLong(fx);
	y=SLong(fy);
	w=SLong(fw);
	h=(((MAP_SCREEN_ORIGIN_Y_640+MAP_SCREEN_HEIGHT_640)*height)/480)-y;
	OverLay.pw->DoSmokedGlassBox(x,y,w,h,0xFFB0BCC0);
}

MESSAGE_STRUC* localMsg;
DecisionAI* localDec;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShowPositionIndicators
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
void MapScr::ShowPositionIndicators()
{
	//3 position indicators (1) block start,
	//						(2) current position
	//						(3) block end

	_Analogue.PollPosition();

	bool markerDone=false;

	SWord _TopY=40;
	SWord _LeftX=8;
	SWord _Width=368;
	SWord _Height=16;
	SWord _Height_2=_Height>>1;
	SWord _Height_3_2=_Height_2+(_Height_2>>1);

	OverLay.startMarker=_Replay.BeginMarkPos;					//AMM 24Feb99
	OverLay.endMarker=_Replay.EndMarkPos;						//AMM 24Feb99
	OverLay.curPos=_Replay.CurrPos;								//AMM 24Feb99

	SLong startBlockX=OverLay.startMarker;
	SLong endBlockX=OverLay.endMarker;
	SLong currentPosX=OverLay.curPos;

	startBlockX=((startBlockX*_Width)>>8)+_LeftX;
	endBlockX=((endBlockX*_Width)>>8)+_LeftX;
	currentPosX=((currentPosX*_Width)>>8)+_LeftX;

	if (IsExtraWide(OverLay.physicalWidth))
	{
		_TopY<<=1;
		_Height<<=1;
		_Height_2<<=1;
		startBlockX<<=1;
		currentPosX<<=1;
		endBlockX<<=1;
	}

	OverLay.DrawLine(startBlockX,_TopY+_Height-_Height_3_2,startBlockX,_TopY+_Height,Colour(21));
	OverLay.DrawLine(endBlockX,_TopY+_Height-_Height_3_2,endBlockX,_TopY+_Height,Colour(21));
	OverLay.DrawLine(currentPosX,_TopY+_Height-_Height_2,currentPosX,_TopY+_Height,Colour(31));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandleUpDnLftRgtToggleKeys
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
void MapScr::HandleUpDnLftRgtToggleKeys()
{
	//find the currently hilighted option

	bool abort;

	OptionList* pCurOpt=optionList;

	while (pCurOpt->key!=SEL_EOL && pCurOpt->key!=OverLay.hilight) pCurOpt++;

	if (pCurOpt->key==SEL_EOL || OverLay.hilight==SEL_NONE)
	{
		pCurOpt=optionList;
		while (pCurOpt->key!=SEL_EOL && pCurOpt->key!=SEL_BLANK) pCurOpt++;
		if (pCurOpt->key==SEL_EOL)
			return;
	}

	if (Key_Tests.KeyPress3d(ROTUP) ||
		Key_Tests.KeyPress3d(ROTLEFT))
	{
		//move the selected hilight option up

		if (ULong(--pCurOpt)<ULong(optionList))
		{
			pCurOpt=optionList;
			while (pCurOpt[1].key!=SEL_EOL) pCurOpt++;
		}
		abort=false;
		while (pCurOpt->key==SEL_BLANK)
		{
			if (ULong(--pCurOpt)<ULong(optionList))
			{
				if (abort) return;
				pCurOpt=optionList;
				while (pCurOpt[1].key!=SEL_EOL) pCurOpt++;
				abort=true;
			}
		}
		OverLay.hilight=(Key)pCurOpt->key;
	}
	else if (Key_Tests.KeyPress3d(ROTDOWN) ||
			 Key_Tests.KeyPress3d(ROTRIGHT))
	{
		//move the selected hilight option down

		pCurOpt++;
		if (pCurOpt->key==SEL_EOL || pCurOpt->key==SEL_BLANK)
		{
			if (pCurOpt->key==SEL_EOL)	pCurOpt=optionList;

			while (pCurOpt->key!=SEL_BLANK)
			{
				pCurOpt++;
				if (pCurOpt->key==SEL_EOL)
				{
					if (abort) return;
					abort=true;
					pCurOpt=optionList;
				}
			}
		}
		OverLay.hilight=(Key)pCurOpt->key;
	}
	else if (Key_Tests.KeyPress3d(SHOOT))
	{
		//call the select routine for the current hilighted option
		if (pCurOpt->selRtn!=NULL)
			OverLay.pNewScr=(this->*(pCurOpt->selRtn))(pCurOpt->resIDOffset,(Key)pCurOpt->key);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FirstMapInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::FirstMapInit()
{
	OverLay.fZoomedMap=false;
	map_scale=.5;
	if (Manual_Pilot.ControlledAC2 && 
		Manual_Pilot.ControlledAC2->waypoint)	
		OverLay.curr_waypoint=Manual_Pilot.ControlledAC2->waypoint;
	else			
		OverLay.curr_waypoint=NULL;
	_MsgBuffer.InitMessageWindow();
	if (!_DPlay.Implemented)
		OverLay.keyFlags=KF_PAUSEON;
//Old_Code DAW 26Mar99 	OverLay.keyFlags=KF_PAUSEON;
	refreshLandscape=false;
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromFirstMap
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromFirstMap(UByte&,Key k)
{
	MapScr* retval=this;

	switch (k)
	{
	case SEL_1:
		retval=&COverlay::accelMapScr;
		map_scale=.5;
		OverLay.fZoomedMap=false;
		break;
	case SEL_2:
		retval=&COverlay::waypointMapScr;
		break;
	case SEL_3:
		retval=&COverlay::radioMapScr;
		break;
	case SEL_4:
		if (OverLay.fZoomedMap)
		{
			OverLay.fZoomedMap=false;
			map_scale=.5;
		}
		else if (map_scale==.5)
		{
			map_scale=2;
		}
		else
		{
			OverLay.fZoomedMap=true;
			Land_Scape.RefreshLandscape();
			refreshLandscape=true;
		}
		break;
	case SEL_5:
		if (_DPlay.Implemented)//AMM20May
			retval=&COverlay::commsMsgMapScr;
		break;
	case SEL_6:
		if (_DPlay.Implemented)//AMM20May
			retval=&COverlay::commsRecipientMapScr;
		break;
	case SEL_0:
	case SEL_ESC:
		OverLay.fZoomedMap=false;
		OverLay.keyFlags=KF_PAUSEOFF|KF_ACCELOFF;
		OverLay.pvp->ReturnFromMap();
		if (refreshLandscape)
			Land_Scape.RefreshLandscape();
		retval=NULL;
		break;
	default:
		break;
	}
	return retval;
}

MapScr COverlay::firstMapScr=
{
	MapScr::SCALE_GRIDORIGIN+/*MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE+
	MapScr::FLAG_MOUSEOVERHI,
	MapScreenX,MapScreenY,
	MapScreenWidth,MapScreenHeight,
	MapGridXOffset,MapGridYOffset,
	NO_BACKGROUND_WIPE,
	TEXT_MAP_BLACK,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::FirstMapInit,
	MapScr::UpdateMessageDisplay,
	{
		{IDS_MAP_ACCEL,0,SEL_1,MapScr::SelectFromFirstMap},
		{IDS_MAP_WAYPOINTS,0,SEL_2,MapScr::SelectFromFirstMap},
		{IDS_MAP_RADIO,0,SEL_3,MapScr::SelectFromFirstMap},
		{IDS_MAP_ZOOM,0,SEL_4,MapScr::SelectFromFirstMap},
		MSBlankLine,
		MSBlankLine,
		MSEscapeLine(MapScr::SelectFromFirstMap),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromFirstMap},
		MSListEnd
	}
};

MapScr COverlay::firstMapScrCOMMS=
{
	MapScr::SCALE_GRIDORIGIN+/*MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE+
	MapScr::FLAG_MOUSEOVERHI,
	MapScreenX,MapScreenY,
	MapScreenWidth,MapScreenHeight,
	MapGridXOffset,MapGridYOffset,
	NO_BACKGROUND_WIPE,
	TEXT_MAP_BLACK,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::FirstMapInit,
	MapScr::UpdateMessageDisplay,
	{
		{IDS_MAP_ACCEL,0,SEL_1,MapScr::SelectFromFirstMap},
		{IDS_MAP_WAYPOINTS,0,SEL_2,MapScr::SelectFromFirstMap},
		{IDS_MAP_RADIO,0,SEL_3,MapScr::SelectFromFirstMap},
		MSBlankLine,
		{IDS_MAP_COMMSMSG,0,SEL_5,MapScr::SelectFromFirstMap},
		{IDS_MAP_COMMSRECIPIENT,0,SEL_6,MapScr::SelectFromFirstMap},
		MSBlankLine,
		MSBlankLine,
		MSEscapeLine(MapScr::SelectFromFirstMap),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromFirstMap},
		MSListEnd
	}
};

/*******************
**	ORDERS SCREEN **
*******************/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendMessageAndCall
//Author		Paul.   
//Date			Thu 1 Apr 1999
//------------------------------------------------------------------------------
void COverlay::SendMessageAndCall(MESSAGE_STRUC* msg,DecisionAI* dec)
{
	if (msg->callee==Persons2::PlayerSeenAC)					  //RDH 17/05/99
		msg->callee=Persons2::PlayerGhostAC;					  //RDH 17/05/99
	if (msg->caller==Persons2::PlayerSeenAC)					  //RDH 17/05/99
		msg->caller=Persons2::PlayerGhostAC;					  //RDH 17/05/99
	if (msg->target==Persons2::PlayerSeenAC)					  //RDH 17/05/99
		msg->target=Persons2::PlayerGhostAC;					  //RDH 17/05/99

	if (dec)
		dec->UserMsgDecision((AirStruc*)msg->callee,msg->target,(AirStruc*)msg->callee,&Art_Int,msg);
	msg->SetPriority(PRI_MAX);
	_Radio.TriggerMsg(*msg);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MsgOptionSelected
//Author		Paul.   
//Date			Thu 1 Apr 1999
//------------------------------------------------------------------------------
void COverlay::MsgOptionSelected(MESSAGE_STRUC* msg,SLong op)
{
	DecisionAI* dec=msg->decisionhandler;
//DeadCode AMM 21May99 	DecisionAI::OptionRef* opt=dec->GetMsgOptions();

	DecisionMessage(dec,op,msg->callee,msg->target,msg->callee);

//DeadCode AMM 21May99 	opt+=op;
//DeadCode AMM 21May99 
//DeadCode AMM 21May99 	if (_DPlay.Implemented || _Replay.Record)
//DeadCode AMM 21May99 	{
//DeadCode AMM 21May99 // COMMS: send message to other players indicating option selected
//DeadCode AMM 21May99 // decision=0-100=7bits, option=0-9=4 bits, target=UID=14 bits (25 bits, only have 24!)
//DeadCode AMM 21May99 // callee and caller are sender of packet
//DeadCode AMM 21May99 
//DeadCode AMM 21May99 
//DeadCode AMM 21May99 		UByte option=(UByte)op;
//DeadCode AMM 21May99 		UniqueID trg=msg->target->uniqueID.count;
//DeadCode AMM 21May99 		UByte decision=msg->decisionhandler->optionnumber;
//DeadCode AMM 21May99 
//DeadCode AMM 21May99 		_DPlay.NewWingmanCommand(decision,option,trg);
//DeadCode AMM 21May99 
//DeadCode AMM 21May99 // On receipt Maybe call Send message and call instead of the following 3 lines
//DeadCode AMM 21May99 
//DeadCode AMM 21May99 //		MESSAGE_STRUC newMsg(opt->saidmsg,MSG_HIPRIORITY,msg->callee,msg->target,msg->callee);
//DeadCode AMM 21May99 //		dec->AutoMsgDecision((AirStruc*)msg->callee,msg->target,(AirStruc*)msg->callee,&Art_Int,&newMsg);
//DeadCode AMM 21May99 //		_Radio.TriggerMsg(newMsg);
//DeadCode AMM 21May99 
//DeadCode AMM 21May99 	}
//DeadCode AMM 21May99 	else
//DeadCode AMM 21May99 	{
//DeadCode AMM 21May99 
//DeadCode AMM 21May99 		MESSAGE_STRUC newMsg(opt->saidmsg,MSG_HIPRIORITY,msg->callee,msg->target,msg->callee);
//DeadCode AMM 21May99 //DeadCode DAW 06Apr99 		dec->AutoMsgDecision((AirStruc*)msg->callee,msg->target,(AirStruc*)msg->callee,&Art_Int,&newMsg);
//DeadCode AMM 21May99 //DeadCode DAW 06Apr99 		_Radio.TriggerMsg(newMsg);
//DeadCode AMM 21May99 		SendMessageAndCall(&newMsg,opt->airesult[0]);
//DeadCode AMM 21May99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ActionMessage
//Author		Paul    
//Date			Tue 9 Mar 1999
//------------------------------------------------------------------------------
void COverlay::ActionMessage(MESSAGE_STRUC* msg)
{
	MapScr::OptionList termOpt=MSListEnd;
	MapScr::OptionList escOpt=MSEscapeLine(MapScr::SelectFrom3DOrders);
	MapScr::OptionList blankOpt=MSBlankLine;
	MapScr::OptionList miscOpt={IDS_INDIRECT00,0,SEL_1,MapScr::SelectFrom3DOrders};

	Kludge();
	if (!Manual_Pilot.ControlledAC2->Status.deadtime &&
		!pCurScr)
	{
		localMsg=msg;

		if (msg->decisionhandler)
		{
			DecisionAI* dec=msg->decisionhandler;
			DecisionAI::OptionRef* opt=dec->GetMsgOptions();
			MapScr* map=&orders3dScr;
			MapScr::OptionList* ol=map->optionList;
			SLong oc=0;
			while (opt->optionmsg!=PHRASE_PARTS_S && oc<9)
			{
				miscOpt.resID=_Radio.PhraseToResource(opt->optionmsg);
				*ol++=miscOpt;
				miscOpt.key++;
				opt++;
				oc++;
			}
			while (oc++<9)	*ol++=blankOpt;
			*ol++=escOpt;
			*ol=termOpt;

			//trigger UI display @ end of the current frame
			SetToOrdersScreen();
		}
	}
}

EXTERNAI(GroupInfoMsg,AirStrucPtr);
EXTERNAI(PreCombatMsg,AirStrucPtr);
EXTERNAI(CombatMsg,AirStrucPtr);
EXTERNAI(PostCombatMsg,AirStrucPtr);
EXTERNAI(TowerMsg,AirStrucPtr);
EXTERNAI(FACMsg,AirStrucPtr);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UserMsgInit
//------------------------------------------------------------------------------
Key MapScr::UserMsgInit()
{
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromUserMsg
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromUserMsg(UByte&,Key k)
{
	MapScr* retval=NULL;	//close on selection of an option
	localDec=NULL;
	switch (k)
	{
	case SEL_1:
		localDec=GroupInfoMsg;
		break;
	case SEL_2:
		localDec=PreCombatMsg;
		break;
	case SEL_3:
		localDec=CombatMsg;
		break;
	case SEL_4:
		localDec=PostCombatMsg;
		break;
	case SEL_5:
		localDec=TowerMsg;
		break;
	case SEL_6:
		localDec=FACMsg;
		break;
	case SEL_7:
//		localDec=CommsPlyrMsg;
//DeadCode AMM 14May99 		retval=&COverlay::commsMsgOrdersScr;
		if (_DPlay.Implemented)//AMM20May
			retval=&COverlay::commsRecipientOrdersScr;
		localDec=NULL;
		break;
	case SEL_8:
//		localDec=CommsMsgMsg;
		localDec=NULL;
//DeadCode AMM 14May99 		retval=&COverlay::commsRecipientOrdersScr;
		if (_DPlay.Implemented)//AMM20May
			retval=&COverlay::commsMsgOrdersScr;					//AMM 14May99
		break;
	default:
		break;
	}

	if (localDec!=NULL)
	{
		retval=&COverlay::userOptionsScr;
	}
	return retval;
}

MapScr COverlay::userMsgScr=
{
	MapScr::JUSTIFY_CENTRE_SX+ /*MapScr::SCALE_GRIDWH+*/
/*	MapScr::SCALE_GRIDORIGIN+MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE,
	MapScreenX,MapScreenY,
	RadioScreenWidth,RadioScreenHeight,
	MapGridXOffset,MapGridYOffset,
	SET_WIPE_TEXTURE(RADIONO),
	TEXT_MAP_WHITE,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::Orders3DInit,
	MapScr::TimeLimitedDisplay,
	{
		{IDS_UM_GROUPINFO,0,SEL_1,MapScr::SelectFromUserMsg},
		{IDS_UM_PRECOMBAT,0,SEL_2,MapScr::SelectFromUserMsg},
		{IDS_UM_COMBAT,0,SEL_3,MapScr::SelectFromUserMsg},
		{IDS_UM_POSTCOMBAT,0,SEL_4,MapScr::SelectFromUserMsg},
		{IDS_UM_TOWER,0,SEL_5,MapScr::SelectFromUserMsg},
		{IDS_UM_FAC,0,SEL_6,MapScr::SelectFromUserMsg},
		MSEscapeLine(MapScr::SelectFromUserMsg),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromUserMsg},
		MSListEnd
	}
};

MapScr COverlay::userMsgScrCOMMS=
{
	MapScr::JUSTIFY_CENTRE_SX+/*MapScr::SCALE_GRIDWH+
	MapScr::SCALE_GRIDORIGIN+MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE,
	MapScreenX,MapScreenY,
	RadioScreenWidth,RadioScreenHeight,
	MapGridXOffset,MapGridYOffset,
	SET_WIPE_TEXTURE(RADIONO),
	TEXT_MAP_WHITE,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::Orders3DInit,
	MapScr::TimeLimitedDisplay,
	{
		{IDS_UM_GROUPINFO,0,SEL_1,MapScr::SelectFromUserMsg},
		{IDS_UM_PRECOMBAT,0,SEL_2,MapScr::SelectFromUserMsg},
		{IDS_UM_COMBAT,0,SEL_3,MapScr::SelectFromUserMsg},
		{IDS_UM_POSTCOMBAT,0,SEL_4,MapScr::SelectFromUserMsg},
		{IDS_UM_TOWER,0,SEL_5,MapScr::SelectFromUserMsg},
		{IDS_UM_FAC,0,SEL_6,MapScr::SelectFromUserMsg},
		{IDS_UM_COMMSPLAYER,0,SEL_7,MapScr::SelectFromUserMsg},
		{IDS_UM_COMMSMSG,0,SEL_8,MapScr::SelectFromUserMsg},
		MSEscapeLine(MapScr::SelectFromUserMsg),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromUserMsg},
		MSListEnd
	}
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UserOptionsInit
//------------------------------------------------------------------------------
Key MapScr::UserOptionsInit()
{
	MapScr::OptionList termOpt=MSListEnd;
	MapScr::OptionList escOpt=MSEscapeLine(MapScr::SelectFromUserOptions);
	MapScr::OptionList blankOpt=MSBlankLine;
	MapScr::OptionList quitOpt={IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromUserOptions};
	MapScr::OptionList miscOpt={IDS_INDIRECT00,0,SEL_1,MapScr::SelectFromUserOptions};

	DecisionAI* dec=localDec;
	DecisionAI::OptionRef* opt=dec->GetMsgOptions();
	MapScr* map=this;
	MapScr::OptionList* ol=map->optionList;

	SLong oc=0;
	while (opt->optionmsg!=PHRASE_PARTS_S && oc<9)
	{
		miscOpt.resID=_Radio.PhraseToResource(opt->optionmsg);
		*ol++=miscOpt;
		miscOpt.key++;
		opt++;
		oc++;
	}
	while (oc++<9)	*ol++=blankOpt;
	*ol++=escOpt;
	*ol++=quitOpt;
	*ol=termOpt;
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UserOptsMapInit
//------------------------------------------------------------------------------
Key MapScr::UserOptsMapInit()
{
	MapScr::OptionList termOpt=MSListEnd;
	MapScr::OptionList escOpt=MSEscapeLine(MapScr::SelectFromUserOptsMap);
	MapScr::OptionList blankOpt=MSBlankLine;
	MapScr::OptionList quitOpt={IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromUserOptsMap};
	MapScr::OptionList miscOpt={IDS_INDIRECT00,0,SEL_1,MapScr::SelectFromUserOptsMap};

	DecisionAI* dec=localDec;
	DecisionAI::OptionRef* opt=dec->GetMsgOptions();
	MapScr* map=this;
	MapScr::OptionList* ol=map->optionList;

	SLong oc=0;
	while (opt->optionmsg!=PHRASE_PARTS_S && oc<9)
	{
		miscOpt.resID=_Radio.PhraseToResource(opt->optionmsg);
		*ol++=miscOpt;
		miscOpt.key++;
		opt++;
		oc++;
	}
//DEAD	while (oc++<9)	*ol++=blankOpt;
	*ol++=escOpt;
	*ol++=quitOpt;
	*ol=termOpt;
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromUserOptions
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromUserOptsMap(UByte& a,Key k)
{
	SelectFromUserOptions(a,k);
	return &COverlay::firstMapScr;
}

MapScr COverlay::userOptsMapScr=
{
	MapScr::SCALE_GRIDORIGIN+/*MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE+
	MapScr::FLAG_MOUSEOVERHI,
	MapScreenX,MapScreenY,
	MapScreenWidth,MapScreenHeight,
	MapGridXOffset,MapGridYOffset,
	NO_BACKGROUND_WIPE,
	TEXT_MAP_BLACK,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows+2,
	0x0000,
	MapScr::UserOptsMapInit,
	MapScr::UpdateMessageDisplay,
	{
		{IDS_INDIRECT00,0,SEL_1,MapScr::SelectFromUserOptsMap},
		{IDS_INDIRECT01,0,SEL_1,MapScr::SelectFromUserOptsMap},
		{IDS_INDIRECT02,0,SEL_1,MapScr::SelectFromUserOptsMap},
		{IDS_INDIRECT03,0,SEL_1,MapScr::SelectFromUserOptsMap},
		{IDS_INDIRECT04,0,SEL_1,MapScr::SelectFromUserOptsMap},
		{IDS_INDIRECT05,0,SEL_1,MapScr::SelectFromUserOptsMap},
		{IDS_INDIRECT06,0,SEL_1,MapScr::SelectFromUserOptsMap},
		{IDS_INDIRECT07,0,SEL_1,MapScr::SelectFromUserOptsMap},
		{IDS_INDIRECT08,0,SEL_1,MapScr::SelectFromUserOptsMap},
		MSEscapeLine(MapScr::SelectFromUserOptsMap),
		{IDS_DEFAULT,0,SEL_0,MapScr::SelectFromUserOptsMap},
		MSListEnd
	}
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromUserOptions
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromUserOptions(UByte&,Key k)
{
	MapScr* retval=NULL;	//close on selection of an option
//rjs 18feb00	if (Trans_Obj.View_Object->FrameTime())//rjs 18feb00
	{
		DecisionAI* dec=NULL;

		if (localMsg && localMsg->decisionhandler)	dec=localMsg->decisionhandler;
		else if (localDec)							dec=localDec;
			
		localMsg=NULL;
		localDec=NULL;
			
		if (dec)
		{
	//DeadCode AMM 21May99 		DecisionAI::OptionRef* opt=dec->GetMsgOptions();

			if (k>=SEL_1 && k<=SEL_9)
			{
				_Miles.SetDelayed(true);

					OverLay.DecisionMessage(dec,
									(SWord)(k-SEL_1),
									Persons2::PlayerGhostAC,
									Persons2::PlayerGhostAC->ai.unfriendly,
									Persons2::PlayerGhostAC);
				_Miles.SetDelayed(false);

	//DeadCode AMM 21May99 			opt+=SLong(k-SEL_1);
	//DeadCode AMM 21May99 			if (_DPlay.Implemented || _Replay.Record)			//AMM 17May99
	//DeadCode AMM 21May99 			{													//AMM 17May99
	//DeadCode AMM 21May99 				UByte option=(UByte)(k-SEL_1);					//AMM 17May99
	//DeadCode AMM 21May99 				UniqueID trg=Persons2::PlayerGhostAC->uniqueID.count;//AMM 17May99
	//DeadCode AMM 21May99 				UByte decision=dec->optionnumber;				//AMM 17May99
	//DeadCode AMM 21May99 				_DPlay.NewWingmanCommand(decision,option,trg);	//AMM 17May99
	//DeadCode AMM 21May99 			}													//AMM 17May99
	//DeadCode AMM 21May99 			else												//AMM 17May99
	//DeadCode AMM 21May99 			{													//AMM 17May99
	//DeadCode AMM 21May99 				MESSAGE_STRUC newMsg(opt->saidmsg,
	//DeadCode AMM 21May99 									MSG_HIPRIORITY,
	//DeadCode AMM 21May99 									Persons2::PlayerGhostAC,	//AMM 17May99
	//DeadCode AMM 21May99 									Persons2::PlayerGhostAC->ai.unfriendly, //MS 18/05/99
	//DeadCode AMM 21May99 									Persons2::PlayerGhostAC);	//AMM 17May99
	//DeadCode AMM 21May99 				OverLay.SendMessageAndCall(&newMsg,opt->airesult[0]);
	//DeadCode AMM 21May99 			}													//AMM 17May99
				retval=NULL;
			}
		}
	}
	return retval;
}

MapScr COverlay::userOptionsScr=
{
	MapScr::JUSTIFY_CENTRE_SX+/*MapScr::SCALE_GRIDWH+
	MapScr::SCALE_GRIDORIGIN+MapScr::SCALE_GRIDOFFSETS*/
	MapScr::SCALE_DYNAMICSIZE,
	MapScreenX,MapScreenY,
	RadioScreenWidth,RadioScreenHeight,
	MapGridXOffset,MapGridYOffset,
	SET_WIPE_TEXTURE(RADIONO),
	TEXT_MAP_WHITE,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	1,15,
	0x0000,
	MapScr::UserOptionsInit,
	NULL,
	{
		{IDS_INDIRECT00,0,SEL_1,MapScr::SelectFromUserOptions},
		{IDS_INDIRECT01,0,SEL_1,MapScr::SelectFromUserOptions},
		{IDS_INDIRECT02,0,SEL_1,MapScr::SelectFromUserOptions},
		{IDS_INDIRECT03,0,SEL_1,MapScr::SelectFromUserOptions},
		{IDS_INDIRECT04,0,SEL_1,MapScr::SelectFromUserOptions},
		{IDS_INDIRECT05,0,SEL_1,MapScr::SelectFromUserOptions},
		{IDS_INDIRECT06,0,SEL_1,MapScr::SelectFromUserOptions},
		{IDS_INDIRECT07,0,SEL_1,MapScr::SelectFromUserOptions},
		{IDS_INDIRECT08,0,SEL_1,MapScr::SelectFromUserOptions},
		MSEscapeLine(MapScr::SelectFromUserOptions),
		{IDS_DEFAULT,0,SEL_0,MapScr::SelectFromUserOptions},
		MSListEnd
	}
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Orders3DInit
//Author		Paul.   
//Date			Mon 22 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::Orders3DInit()
{
	OverLay.displayTimeLimit=5*100;	//5 seconds?					  //RDH 19/06/99
 	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TimeLimitedDisplay
//Author		Paul.   
//Date			Mon 22 Feb 1999
//------------------------------------------------------------------------------
void MapScr::TimeLimitedDisplay()
{
	//decrement timer and select default 
	//option if time has expired

 	OverLay.displayTimeLimit-=OverLay.pvp->FrameTime();

	if (OverLay.displayTimeLimit<=0)
	{
		OptionList* pCurOpt=optionList;

		while (pCurOpt->key!=SEL_0 && pCurOpt->key!=SEL_ESC && pCurOpt->key!=SEL_EOL)
			pCurOpt++;

		if (pCurOpt->key==SEL_ESC && pCurOpt->selRtn!=NULL)
			OverLay.pNewScr=(this->*(pCurOpt->selRtn))(pCurOpt->resIDOffset,SEL_ESC);
		else if (pCurOpt->key==SEL_0 && pCurOpt->selRtn!=NULL)
			OverLay.pNewScr=(this->*(pCurOpt->selRtn))(pCurOpt->resIDOffset,SEL_0);
		else if (pCurOpt->key==SEL_ESC && pCurOpt->selRtn!=NULL)
			OverLay.pNewScr=(this->*(pCurOpt->selRtn))(pCurOpt->resIDOffset,SEL_ESC);

		OverLay.displayTimeLimit=0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFrom3DOrders
//Author		Paul.   
//Date			Mon 22 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFrom3DOrders(UByte&,Key k)
{
	MapScr* retval=this;	//close on selection of an option
	DecisionAI* dec=NULL;
	
	MESSAGE_STRUC* theMsg=localMsg;
	localMsg=NULL;

	if (theMsg && theMsg->decisionhandler)
		dec=theMsg->decisionhandler;

	if (dec)
	{
		DecisionAI::OptionRef* opt=dec->GetMsgOptions();

		if (k>=SEL_1 && k<=SEL_9)
		{
			OverLay.MsgOptionSelected(theMsg,SLong(k-SEL_1));
			retval=NULL;
		}
		else
		{
			DecisionAI* dec=theMsg->decisionhandler;
			DecisionAI::OptionRef* opt=dec->GetMsgOptions();
			PhraseTables defPh=dec->GetDefaultPhrase(theMsg->callee,theMsg->target);
			SLong sel=0;
			while (opt->optionmsg!=PHRASE_PARTS_S &&
					opt->optionmsg!=defPh && sel<9)
			{
				opt++;
				sel++;
			}

			if (sel<9 && opt->optionmsg!=PHRASE_PARTS_S)
			{
				OverLay.MsgOptionSelected(theMsg,sel);
				retval=NULL;
			}
		}
	}
	else retval=NULL;
	return retval;
}

MapScr COverlay::orders3dScr=
{
	MapScr::JUSTIFY_CENTRE_SX+/*MapScr::SCALE_GRIDWH+
	MapScr::SCALE_GRIDORIGIN+MapScr::SCALE_GRIDOFFSETS*/
	MapScr::SCALE_DYNAMICSIZE,
	MapScreenX,MapScreenY,
	RadioScreenWidth,RadioScreenHeight,
	MapGridXOffset,MapGridYOffset,
	SET_WIPE_TEXTURE(RADIONO),
	TEXT_MAP_WHITE,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::Orders3DInit,
	MapScr::TimeLimitedDisplay,
	{
		{IDS_INDIRECT00,0,SEL_1,MapScr::SelectFrom3DOrders},
		{IDS_INDIRECT01,0,SEL_1,MapScr::SelectFrom3DOrders},
		{IDS_INDIRECT02,0,SEL_1,MapScr::SelectFrom3DOrders},
		{IDS_INDIRECT03,0,SEL_1,MapScr::SelectFrom3DOrders},
		{IDS_INDIRECT04,0,SEL_1,MapScr::SelectFrom3DOrders},
		{IDS_INDIRECT05,0,SEL_1,MapScr::SelectFrom3DOrders},
		{IDS_INDIRECT06,0,SEL_1,MapScr::SelectFrom3DOrders},
		{IDS_INDIRECT07,0,SEL_1,MapScr::SelectFrom3DOrders},
		{IDS_INDIRECT08,0,SEL_1,MapScr::SelectFrom3DOrders},
		MSEscapeLine(MapScr::SelectFrom3DOrders),
		{IDS_DEFAULT,0,SEL_0,MapScr::SelectFrom3DOrders},
		MSListEnd
	}
};

/**********************
**	ACCEL MAP SCREEN **
**********************/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		COverlay.CancelAccel
//Author		Paul.   
//Date			Thu 4 Mar 1999
//------------------------------------------------------------------------------
void COverlay::CancelAccel()
{
	if (!pvp || !pvp->Accel	  ())
		return;
	accelcountdown=0;												  //JIM 12/07/99
	UByte dummy;
	if (pCurScr) pCurScr=pNewScr=accelMapScr.SelectFromAccelMap(dummy,SEL_0);
	else
	{
		if (_DPlay.Implemented)	_DPlay.SendDeselectAccelMessage();
		OverLay.keyFlags|=KF_ACCELOFF;
		Manual_Pilot.AutoToggle(ManualPilot::MANUAL);
	}
	if (otherText[0]!="")
	{
		otherText[0]="";
		messageTimer=0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AccelMapInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::AccelMapInit()
{
	//build list of display options based on whether movecode is autofollowwp or not
	MapScr::OptionList termOpt=MSListEnd;
	MapScr::OptionList escOpt=MSEscapeLine(MapScr::SelectFromAccelMap);
	MapScr::OptionList blankOpt=MSBlankLine;
	MapScr::OptionList quitOpt={IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromAccelMap};
	MapScr::OptionList fwdOpt={IDS_MAP_FORWARD,0,SEL_1,MapScr::SelectFromAccelMap};
	MapScr::OptionList wayptOpt={IDS_MAP_NEXTWAYPOINT,0,SEL_2,MapScr::SelectFromAccelMap};
	MapScr::OptionList msubjOpt={IDS_MAP_MESSAGESUBJECT,0,SEL_3,MapScr::SelectFromAccelMap};
	MapScr::OptionList missipOpt={IDS_MAP_MISSIONIP,0,SEL_4,MapScr::SelectFromAccelMap};
	MapScr::OptionList homeOpt={IDS_MAP_HOME,0,SEL_5,MapScr::SelectFromAccelMap};

	bool allowall=true;
	bool allowip=true;

//	if (Manual_Pilot.ControlledAC2)
//	{
	if (Persons2::PlayerGhostAC && Persons2::PlayerGhostAC->movecode!=AUTO_FOLLOWWP) 
			allowall=false;
	else
	if (Manual_Pilot.ControlledAC2 && Manual_Pilot.ControlledAC2->waypoint==NULL)//JIM 14Jul99
			allowall=false;														//JIM 14Jul99
	else																		//JIM 14Jul99
	if (Manual_Pilot.ControlledAC2 && Manual_Pilot.ControlledAC2->waypoint &&
			Manual_Pilot.ControlledAC2->waypoint->wpname>WPNAME_Ingress)
			allowip=false;
//	}
	if (_DPlay.Implemented) allowall=false;

	OptionList* ol=this->optionList;
	*ol++=fwdOpt;
	*ol++=(allowall)?wayptOpt:blankOpt;
	*ol++=(allowall)?msubjOpt:blankOpt;
	*ol++=(allowall && allowip)?missipOpt:blankOpt;
	*ol++=(allowall)?homeOpt:blankOpt;
	*ol++=blankOpt;
	*ol++=blankOpt;
	*ol++=blankOpt;
	*ol++=escOpt;
	*ol++=quitOpt;
	*ol++=termOpt;

	if (_DPlay.Implemented)
		refreshLandscape=true;
	OverLay.fZoomedMap=false;
	map_scale=.5;
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromAccelMap
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromAccelMap(UByte&,Key k)
{
	MapScr* retval=this;

	Manual_Pilot.acceltochanged=NULL;								  //JIM 18/04/99
	switch (k)
	{
	case SEL_0:
	case SEL_ESC:
		UByte dummy;
		if (!_DPlay.Implemented)
			OverLay.keyFlags=KF_PAUSEON+KF_SLOWACCEL;
		else
		{
			_DPlay.SendDeselectAccelMessage();
		}

		OverLay.keyFlags|=KF_ACCELOFF;
		Manual_Pilot.AutoToggle(ManualPilot::MANUAL);
		retval=SelectFromFirstMap(dummy,k);
		break;
	case SEL_2:	//to next waypoint
//DeadCode AMM 10Jun99 		//force the selected option to be hilighted
//DeadCode AMM 10Jun99 		if (_DPlay.Implemented) // && !_DPlay.mapaccelselection)
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			_DPlay.SendMapAccelSelection(k);
//DeadCode AMM 10Jun99 		}
//DeadCode AMM 10Jun99 		else
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			OverLay.hilight=k;
//DeadCode AMM 10Jun99 			OverLay.keyFlags=KF_ACCELON+KF_FASTACCEL;
//DeadCode AMM 10Jun99 			Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_WAYPT);
//DeadCode AMM 10Jun99 			Manual_Pilot.acceltochanged=Manual_Pilot.ControlledAC2->waypoint;					  //JIM 18/04/99
//DeadCode AMM 10Jun99 			refreshLandscape=true;
//DeadCode AMM 10Jun99 		}
		OverLay.AccelSelection(k,DPlay::ACCEL_NEXTWP);
		break;
	case SEL_1:	//forwards
		//force the selected option to be hilighted
//DeadCode AMM 10Jun99 		if (_DPlay.Implemented) // && !_DPlay.mapaccelselection)
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			_DPlay.SendMapAccelSelection(k);
//DeadCode AMM 10Jun99 		}
//DeadCode AMM 10Jun99 		else
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			OverLay.hilight=k;
//DeadCode AMM 10Jun99 			OverLay.keyFlags=KF_ACCELON+KF_FASTACCEL;
//DeadCode AMM 10Jun99 			Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_FWD);
//DeadCode AMM 10Jun99 			refreshLandscape=true;
//DeadCode AMM 10Jun99 		}
		OverLay.AccelSelection(k,DPlay::ACCEL_FORWARD);
		break;
	case SEL_3:	//message subject
		//force the selected option to be hilighted
//DeadCode AMM 10Jun99 		if (_DPlay.Implemented) // && !_DPlay.mapaccelselection)
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			_DPlay.SendMapAccelSelection(k);
//DeadCode AMM 10Jun99 		}
//DeadCode AMM 10Jun99 		else
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			OverLay.hilight=k;
//DeadCode AMM 10Jun99 			OverLay.keyFlags=KF_ACCELON+KF_FASTACCEL;
//DeadCode AMM 10Jun99 			Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_MSG);
//DeadCode AMM 10Jun99 			refreshLandscape=true;
//DeadCode AMM 10Jun99 		}
		OverLay.AccelSelection(k,DPlay::ACCEL_MESSAGESUBJECT);
		break;
	case SEL_4:	//mission IP
		//force the selected option to be hilighted
//DeadCode AMM 10Jun99 		if (_DPlay.Implemented) // && !_DPlay.mapaccelselection)
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			_DPlay.SendMapAccelSelection(k);
//DeadCode AMM 10Jun99 		}
//DeadCode AMM 10Jun99 		else
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			OverLay.hilight=k;
//DeadCode AMM 10Jun99 			OverLay.keyFlags=KF_ACCELON+KF_FASTACCEL;
//DeadCode AMM 10Jun99 			Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_MISS);
//DeadCode AMM 10Jun99 			Manual_Pilot.acceltochanged=Manual_Pilot.ControlledAC2->waypoint->FindWP(WPNAME_Target);
//DeadCode AMM 10Jun99 			refreshLandscape=true;
//DeadCode AMM 10Jun99 		}
		OverLay.AccelSelection(k,DPlay::ACCEL_MISSIONIP);
		break;
	case SEL_5:	//home
		//force the selected option to be hilighted
//DeadCode AMM 10Jun99 		if (_DPlay.Implemented) // && !_DPlay.mapaccelselection)
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			_DPlay.SendMapAccelSelection(k);
//DeadCode AMM 10Jun99 		}
//DeadCode AMM 10Jun99 		else
//DeadCode AMM 10Jun99 		{
//DeadCode AMM 10Jun99 			OverLay.hilight=k;
//DeadCode AMM 10Jun99 			OverLay.keyFlags=KF_ACCELON+KF_FASTACCEL;
//DeadCode AMM 10Jun99 			Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_MISS);
//DeadCode AMM 10Jun99 			Manual_Pilot.acceltochanged=Manual_Pilot.ControlledAC2->waypoint->FindWP(WPNAME_Disperse);
//DeadCode AMM 10Jun99 			refreshLandscape=true;
//DeadCode AMM 10Jun99 		}
		OverLay.AccelSelection(k,DPlay::ACCEL_HOME);
		break;
	default:
		break;
	}
	return retval;
}

MapScr COverlay::accelMapScr=
{
	MapScr::SCALE_GRIDORIGIN+/*MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE+
	MapScr::FLAG_MOUSEOVERHI,
	MapScreenX,MapScreenY,
	MapScreenWidth,MapScreenHeight,
	MapGridXOffset,MapGridYOffset,
	NO_BACKGROUND_WIPE,
	TEXT_MAP_BLACK,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::AccelMapInit,
	MapScr::UpdateMessageDisplay,
	{
		{IDS_MAP_FORWARD,0,SEL_1,MapScr::SelectFromAccelMap},
		{IDS_MAP_NEXTWAYPOINT,0,SEL_2,MapScr::SelectFromAccelMap},
		{IDS_MAP_MESSAGESUBJECT,0,SEL_3,MapScr::SelectFromAccelMap},
		{IDS_MAP_MISSIONIP,0,SEL_4,MapScr::SelectFromAccelMap},
		{IDS_MAP_HOME,0,SEL_5,MapScr::SelectFromAccelMap},
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSEscapeLine(MapScr::SelectFromAccelMap),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromAccelMap},
		MSListEnd
	}
};

/*************************
**	WAYPOINT MAP SCREEN **
*************************/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WaypointMapInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::WaypointMapInit()
{
	bool allowall=true;
	if (Manual_Pilot.ControlledAC2 && Manual_Pilot.ControlledAC2->movecode!=AUTO_FOLLOWWP) allowall=false;
	if (_DPlay.Implemented) allowall=false;

	MapScr::OptionList termOpt=MSListEnd;
	MapScr::OptionList escOpt=MSEscapeLine(MapScr::SelectFromWaypointMap);
	MapScr::OptionList blankOpt=MSBlankLine;
	MapScr::OptionList quitOpt={IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromWaypointMap};
	MapScr::OptionList snwOpt={IDS_MAP_SETNEXTWP,0,SEL_1,MapScr::SelectFromWaypointMap};
	MapScr::OptionList anwOpt={IDS_MAP_ACCELTONEXTWP,0,SEL_2,MapScr::SelectFromWaypointMap};
//dead	MapScr::OptionList ahwOpt={IDS_MAP_ACCELTOHILIGHTEDWP,0,SEL_3,MapScr::SelectFromWaypointMap};
	OptionList* ol=this->optionList;
	*ol++=snwOpt;
	*ol++=(allowall)?anwOpt:blankOpt;
//dead	*ol++=(allowall)?ahwOpt:blankOpt;
	*ol++=blankOpt;
	*ol++=blankOpt;
	*ol++=blankOpt;
	*ol++=blankOpt;
	*ol++=blankOpt;
	*ol++=blankOpt;
	*ol++=escOpt;
	*ol++=quitOpt;
	*ol++=termOpt;
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromWaypointMap
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromWaypointMap(UByte&,Key k)
{
	MapScr* retval=this;

	switch (k)
	{
	case SEL_1:	//set next waypoint to one stored in OverLay.curr_waypoint
		OverLay.hilight=k;
		if (Manual_Pilot.ControlledAC2)
		{
			if (_DPlay.Implemented || _Replay.Record)
			{
				UniqueID wp=OverLay.curr_waypoint->uniqueID.count;

				_DPlay.NewWPMessage(wp);
			}
			else
			{
				Manual_Pilot.ControlledAC2->waypoint=OverLay.curr_waypoint;
				Persons2::PlayerGhostAC->waypoint=OverLay.curr_waypoint;
			}
		}
		break;
	case SEL_2:	//accel to hilighted waypoint
//DeadCode AMM 10Jun99 		OverLay.hilight=k;
//DeadCode AMM 10Jun99 		OverLay.fZoomedMap=false;
//DeadCode AMM 10Jun99 		OverLay.keyFlags=KF_ACCELON+KF_FASTACCEL;
//DeadCode AMM 10Jun99 		Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_WAYPT);
//DeadCode AMM 10Jun99 		Manual_Pilot.acceltochanged=Manual_Pilot.ControlledAC2->waypoint;
//DeadCode AMM 10Jun99 		OverLay.curr_waypoint=Manual_Pilot.ControlledAC2->waypoint;
//DeadCode AMM 10Jun99 		refreshLandscape=true;
		OverLay.AccelSelection(k,DPlay::ACCEL_WP_NEXTWP);
		break;
//dead	case SEL_3:	//accel to hilighted waypoint
//dead		OverLay.hilight=k;
//dead		OverLay.fZoomedMap=false;
//dead		OverLay.keyFlags=KF_ACCELON+KF_FASTACCEL;
//dead		Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_WAYPT);
//dead		Manual_Pilot.acceltochanged=OverLay.curr_waypoint;
//dead		refreshLandscape=true;
//dead		break;
	case SEL_0:
	case SEL_ESC:
		UByte dummy;
		if (_DPlay.Implemented)
		{
			_DPlay.SendDeselectAccelMessage();
		}
		if (OverLay.pvp && OverLay.pvp->Accel())
		{
			OverLay.keyFlags|=KF_ACCELOFF;
			Manual_Pilot.AutoToggle(ManualPilot::MANUAL);
			refreshLandscape=true;
			retval=SelectFromFirstMap(dummy,k);
		}
		else retval=&COverlay::firstMapScr;
		break;
	default:
		break;
	}
	return retval;
}

MapScr COverlay::waypointMapScr=
{
	MapScr::SCALE_GRIDORIGIN+/*MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE+
	MapScr::FLAG_MOUSEOVERHI,	
	MapScreenX,MapScreenY,
	MapScreenWidth,MapScreenHeight,
	MapGridXOffset,MapGridYOffset,
	NO_BACKGROUND_WIPE,
	TEXT_MAP_BLACK,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::WaypointMapInit,
	MapScr::UpdateWaypointDisplay,
	{
		{IDS_MAP_SETNEXTWP,0,SEL_1,MapScr::SelectFromWaypointMap},
		{IDS_MAP_ACCELTONEXTWP,0,SEL_2,MapScr::SelectFromWaypointMap},
		{IDS_MAP_ACCELTOHILIGHTEDWP,0,SEL_3,MapScr::SelectFromWaypointMap},
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSEscapeLine(MapScr::SelectFromWaypointMap),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromWaypointMap},
		MSListEnd
	}
};

/**********************
**	RADIO MAP SCREEN **
**********************/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RadioMapInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::RadioMapInit()
{
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromRadioMap
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromRadioMap(UByte&,Key k)
{
	localDec=NULL;
	MapScr* retval;

	switch (k)
	{
	case SEL_1:
		localDec=GroupInfoMsg;
		break;
	case SEL_2:
		localDec=PreCombatMsg;
		break;
	case SEL_3:
		localDec=CombatMsg;
		break;
	case SEL_4:
		localDec=PostCombatMsg;
		break;
	case SEL_5:
		localDec=TowerMsg;
		break;
	case SEL_6:
		localDec=FACMsg;
		break;
	case SEL_7:
//TEMP		localDec=(DecisionAI*)&CommsPlyrMsg;
		break;
	case SEL_8:
//TEMP		localDec=(DecisionAI*)&CommsMsgMsg;
		break;
	default:
		break;
	}

	if (localDec!=NULL)
	{
		retval=&COverlay::userOptsMapScr;
	}
	else retval=_DPlay.Implemented?&COverlay::firstMapScrCOMMS:&COverlay::firstMapScr;

	return retval;
}

MapScr COverlay::radioMapScr=
{
	MapScr::SCALE_GRIDORIGIN+/*MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE+
	MapScr::FLAG_MOUSEOVERHI,
	MapScreenX,MapScreenY,
	MapScreenWidth,MapScreenHeight,
	MapGridXOffset,MapGridYOffset,
	NO_BACKGROUND_WIPE,
	TEXT_MAP_BLACK,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	1,11,			//MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::RadioMapInit,
	MapScr::UpdateMessageDisplay,
	{
		{IDS_UM_GROUPINFO,0,SEL_1,MapScr::SelectFromRadioMap},
		{IDS_UM_PRECOMBAT,0,SEL_2,MapScr::SelectFromRadioMap},
		{IDS_UM_COMBAT,0,SEL_3,MapScr::SelectFromRadioMap},
		{IDS_UM_POSTCOMBAT,0,SEL_4,MapScr::SelectFromRadioMap},
		{IDS_UM_TOWER,0,SEL_5,MapScr::SelectFromRadioMap},
		{IDS_UM_FAC,0,SEL_6,MapScr::SelectFromRadioMap},
		{IDS_UM_COMMSPLAYER,0,SEL_7,MapScr::SelectFromRadioMap},
		{IDS_UM_COMMSMSG,0,SEL_8,MapScr::SelectFromRadioMap},
		MSBlankLine,
		MSEscapeLine(MapScr::SelectFromRadioMap),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromRadioMap},
		MSListEnd
	}
};

/*************************
**	COMMSMSG MAP SCREEN **
*************************/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsMsgMapInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::CommsMsgMapInit()
{
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromCommsMsgMap
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromCommsMsgMap(UByte&,Key k)
{
	MapScr* retval=_DPlay.Implemented?&COverlay::firstMapScrCOMMS:&COverlay::firstMapScr;

	switch (k)
	{
	case SEL_1:
	case SEL_2:
	case SEL_3:
	case SEL_4:
	case SEL_5:
	case SEL_6:
	case SEL_7:
	case SEL_8:
		_DPlay.NewPlayerMessage(k);
		break;
	case SEL_0:
	case SEL_ESC:
		break;
	default:
		break;
	}
	return retval;
}

MapScr COverlay::commsMsgMapScr=
{
	MapScr::SCALE_GRIDORIGIN+/*MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE+
	MapScr::FLAG_MOUSEOVERHI,
	MapScreenX,MapScreenY,
	MapScreenWidth,MapScreenHeight,
	MapGridXOffset,MapGridYOffset,
	NO_BACKGROUND_WIPE,
	TEXT_MAP_BLACK,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::CommsMsgMapInit,
	MapScr::UpdateMessageDisplay,
	{
		{IDS_INDIRECT00,0,SEL_1,MapScr::SelectFromCommsMsgMap},
		{IDS_INDIRECT01,0,SEL_2,MapScr::SelectFromCommsMsgMap},
		{IDS_INDIRECT02,0,SEL_3,MapScr::SelectFromCommsMsgMap},
		{IDS_INDIRECT03,0,SEL_4,MapScr::SelectFromCommsMsgMap},
		{IDS_INDIRECT04,0,SEL_5,MapScr::SelectFromCommsMsgMap},
		{IDS_INDIRECT05,0,SEL_6,MapScr::SelectFromCommsMsgMap},
		{IDS_INDIRECT06,0,SEL_7,MapScr::SelectFromCommsMsgMap},
		{IDS_INDIRECT07,0,SEL_8,MapScr::SelectFromCommsMsgMap},
		MSEscapeLine(MapScr::SelectFromCommsMsgMap),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromCommsMsgMap},
		MSListEnd
	}
};

/****************************
**	COMMSMSG ORDERS SCREEN **
****************************/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsMsgMapInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::CommsMsgOrdersInit()
{
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromCommsMsgMap
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromCommsMsgOrders(UByte&,Key k)
{
	MapScr* retval=NULL;

	switch (k)
	{
	case SEL_1:
	case SEL_2:
	case SEL_3:
	case SEL_4:
	case SEL_5:
	case SEL_6:
	case SEL_7:
	case SEL_8:
		_DPlay.NewPlayerMessage(k);
		break;
	case SEL_0:
	case SEL_ESC:
		break;
	default:
		break;
	}
	return retval;
}

MapScr COverlay::commsMsgOrdersScr=
{
	MapScr::JUSTIFY_CENTRE_SX+/*MapScr::SCALE_GRIDWH+
	MapScr::SCALE_GRIDORIGIN+MapScr::SCALE_GRIDOFFSETS*/
	MapScr::SCALE_DYNAMICSIZE,
	MapScreenX,MapScreenY,
	RadioScreenWidth,RadioScreenHeight,
	MapGridXOffset,MapGridYOffset,
	SET_WIPE_TEXTURE(RADIONO),
	TEXT_MAP_WHITE,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::CommsMsgOrdersInit,
	MapScr::TimeLimitedDisplay,
	{
		{IDS_INDIRECT00,0,SEL_1,MapScr::SelectFromCommsMsgOrders},
		{IDS_INDIRECT01,0,SEL_2,MapScr::SelectFromCommsMsgOrders},
		{IDS_INDIRECT02,0,SEL_3,MapScr::SelectFromCommsMsgOrders},
		{IDS_INDIRECT03,0,SEL_4,MapScr::SelectFromCommsMsgOrders},
		{IDS_INDIRECT04,0,SEL_5,MapScr::SelectFromCommsMsgOrders},
		{IDS_INDIRECT05,0,SEL_6,MapScr::SelectFromCommsMsgOrders},
		{IDS_INDIRECT06,0,SEL_7,MapScr::SelectFromCommsMsgOrders},
		{IDS_INDIRECT07,0,SEL_8,MapScr::SelectFromCommsMsgOrders},
		MSEscapeLine(MapScr::SelectFromCommsMsgOrders),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromCommsMsgOrders},
		MSListEnd
	}
};

/*******************************
**	COMMSRECIPIENT MAP SCREEN **
*******************************/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsRecipientMapInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::CommsRecipientMapInit()
{
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromCommsRecipientMap
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromCommsRecipientMap(UByte&,Key k)
{
	MapScr* retval=_DPlay.Implemented?&COverlay::firstMapScrCOMMS:&COverlay::firstMapScr;

	switch (k)
	{
	case SEL_1:
		_DPlay.MsgRecipientAll=true;
		break;
	case SEL_2:
		_DPlay.MsgRecipientAll=false;
		break;
	case SEL_0:
	case SEL_ESC:
		break;
	default:
		break;
	}
	return retval;
}

MapScr COverlay::commsRecipientMapScr=
{
	MapScr::SCALE_GRIDORIGIN+/*MapScr::SCALE_GRIDOFFSETS+*/
	MapScr::SCALE_DYNAMICSIZE+
	MapScr::FLAG_MOUSEOVERHI,
	MapScreenX,MapScreenY,
	MapScreenWidth,MapScreenHeight,
	MapGridXOffset,MapGridYOffset,
	NO_BACKGROUND_WIPE,
	TEXT_MAP_BLACK,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::CommsRecipientMapInit,
	MapScr::UpdateMessageDisplay,
	{ 
		{IDS_EVERYBODY,0,SEL_1,MapScr::SelectFromCommsRecipientMap},
		{IDS_MYSIDEONLY,0,SEL_2,MapScr::SelectFromCommsRecipientMap},
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSEscapeLine(MapScr::SelectFromCommsRecipientMap),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromCommsRecipientMap},
		MSListEnd
	}
};

/*******************************
**	COMMSRECIPIENT ORDERS SCREEN **
*******************************/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsRecipientMapInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::CommsRecipientOrdersInit()
{
	return SEL_0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromCommsRecipientMap
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromCommsRecipientOrders(UByte&,Key k)
{
	MapScr* retval=NULL;

	switch (k)
	{
	case SEL_1:
		_DPlay.MsgRecipientAll=true;
		break;
	case SEL_2:
		_DPlay.MsgRecipientAll=false;
		break;
	case SEL_0:
	case SEL_ESC:
		break;
	default:
		break;
	}
	return retval;
}

MapScr COverlay::commsRecipientOrdersScr=
{
	MapScr::JUSTIFY_CENTRE_SX+/*MapScr::SCALE_GRIDWH+
	MapScr::SCALE_GRIDORIGIN+MapScr::SCALE_GRIDOFFSETS*/
	MapScr::SCALE_DYNAMICSIZE,
	MapScreenX,MapScreenY,
	RadioScreenWidth,RadioScreenHeight,
	MapGridXOffset,MapGridYOffset,
	SET_WIPE_TEXTURE(RADIONO),
	TEXT_MAP_WHITE,
	TEXT_HI,
	MapColumnWidth,MapRowHeight,
	MapGridNumCols,MapGridNumRows,
	0x0000,
	MapScr::CommsRecipientOrdersInit,
//DeadCode AMM 14May99 	MapScr::UpdateMessageDisplay,
	MapScr::TimeLimitedDisplay,
	{ 
		{IDS_EVERYBODY,0,SEL_1,MapScr::SelectFromCommsRecipientOrders},
		{IDS_MYSIDEONLY,0,SEL_2,MapScr::SelectFromCommsRecipientOrders},
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSBlankLine,
		MSEscapeLine(MapScr::SelectFromCommsRecipientOrders),
		{IDS_MAP_EXIT,0,SEL_0,MapScr::SelectFromCommsRecipientOrders},
		MSListEnd
	}
};

/*********************
* REPLAY ICON SCREEN *
*********************/

struct IconEntry COverlay::replayIconTable[]=
{
{RPLYICNSNO,0,0,32,32},			//IDS_MAPICON00LO
{RPLYICN2NO,0,0,32,32},			//IDS_MAPICON00HI
{RPLYICNSNO,32,0,32,32},		//IDS_MAPICON01LO
{RPLYICN2NO,32,0,32,32},		//IDS_MAPICON01HI
{RPLYICNSNO,64,0,32,32},		//IDS_MAPICON02LO
{RPLYICN2NO,64,0,32,32},		//IDS_MAPICON02HI
{RPLYICNSNO,96,0,32,32},		//IDS_MAPICON03LO
{RPLYICN2NO,96,0,32,32},		//IDS_MAPICON03HI

{RPLYICNSNO,0,32,32,32},		//IDS_MAPICON04LO
{RPLYICN2NO,0,32,32,32},		//IDS_MAPICON04HI
{RPLYICNSNO,32,32,32,32},		//IDS_MAPICON05LO
{RPLYICN2NO,32,32,32,32},		//IDS_MAPICON05HI
{RPLYICNSNO,64,32,32,32},		//IDS_MAPICON06LO
{RPLYICN2NO,64,32,32,32},		//IDS_MAPICON06HI
{RPLYICNSNO,96,32,32,32},		//IDS_MAPICON07LO
{RPLYICN2NO,96,32,32,32},		//IDS_MAPICON07HI

{RPLYICNSNO,0,64,32,32},		//IDS_MAPICON08LO
{RPLYICN2NO,0,64,32,32},		//IDS_MAPICON08HI
{RPLYICNSNO,32,64,32,32},		//IDS_MAPICON09LO
{RPLYICN2NO,32,64,32,32},		//IDS_MAPICON09HI
{RPLYICNSNO,64,64,32,32},		//IDS_MAPICON09LO
{RPLYICN2NO,64,64,32,32},		//IDS_MAPICON09HI
{RPLYICNSNO,96,64,32,32},		//IDS_MAPICON09LO
{RPLYICN2NO,96,64,32,32},		//IDS_MAPICON09HI

{RPLYICNSNO,0,96,32,32},		//IDS_MAPICON09LO
{RPLYICN2NO,0,96,32,32},		//IDS_MAPICON09HI
{RPLYICNSNO,32,96,32,32},		//IDS_MAPICON09LO
{RPLYICN2NO,32,96,32,32},		//IDS_MAPICON09HI
{RPLYICNSNO,64,96,32,32},		//IDS_MAPICON09LO
{RPLYICN2NO,64,96,32,32},		//IDS_MAPICON09HI
{RPLYICNSNO,96,96,32,32},		//IDS_MAPICON09LO
{RPLYICN2NO,96,96,32,32}		//IDS_MAPICON09HI
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReplayScreenInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::ReplayScreenInit()
{
	return SEL_NONE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromReplayScreen
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromReplayScreen(UByte&,Key k)
{
	MapScr* retval=this;

	if (_Replay.ReplayFlag==RF_NONE)
	{
// if there is already an operation that needs doing then ignore new ones

		switch (k)
		{
		case SEL_1:		//skip back
			OverLay.hilight=k;
//			OverLay.pvp->BlockTick(TRUE);
			_Replay.ReplayFlag=RF_SKIPTOPREVIOUSMARK;
			_Replay.SkipToPreviousMark();
//			Land_Scape.RefreshLandscape();
//DEADCODE JIM 19/05/99 			_Replay.CalcCurrPos();
//			OverLay.pvp->BlockTick(FALSE);
			break;
		case SEL_2:		//back a block
			OverLay.hilight=k;
//			OverLay.pvp->BlockTick(TRUE);
			_Replay.ReplayFlag=RF_BLOCKREWIND;
			_Replay.BlockRewind();
//			Land_Scape.RefreshLandscape();
			_Replay.CalcCurrPos();
//			OverLay.pvp->BlockTick(FALSE);
			break;
		case SEL_3:		//back a frame
			OverLay.hilight=k;
			_Replay.ReplayFlag=RF_FRAMEREWIND;
			break;
		case SEL_PAUSE:
		case SEL_4:		//pause/play
			//force a screen change to toggle the icons
			if (ULong(this)==ULong(&OverLay.replayPlayingScr))
			{
				//was playing but not now
				OverLay.pCurScr=OverLay.pNewScr=retval=&OverLay.replayScr;
				_Replay.PlaybackPaused=TRUE;
				_Replay.setpaused=1;
			}
			else
			{
				//was paused but not now
				OverLay.pCurScr=OverLay.pNewScr=retval=&OverLay.replayPlayingScr;
				_Replay.PlaybackPaused=FALSE;
				_Replay.setpaused=-1;
			}
			OverLay.hilight=k;
/*				_Replay.ppchanged=true;
			if (_Replay.PlaybackPaused)
			{
				_Replay.setpaused=-1;
				_Replay.PlaybackPaused=FALSE;
			}
			else
			{
//DeadCode AMM 22Apr99 				_Replay.setpaused=true;
				_Replay.setpaused=1;
				_Replay.PlaybackPaused=TRUE;
			}*/
			break;
		case SEL_5:		//forward a frame
			OverLay.hilight=k;
			_Replay.ReplayFlag=RF_FRAMEFORWARD;
			break;
		case SEL_6:		//forward a block
			OverLay.hilight=k;
//			OverLay.pvp->BlockTick(TRUE);
			_Replay.ReplayFlag=RF_BLOCKFORWARD;
			_Replay.BlockForward();
//			Land_Scape.RefreshLandscape();
			_Replay.CalcCurrPos();
//			OverLay.pvp->BlockTick(FALSE);
			break;
		case SEL_7:		//skip forward
			OverLay.hilight=k;
//			OverLay.pvp->BlockTick(TRUE);
			_Replay.ReplayFlag=RF_SKIPTONEXTMARK;
			_Replay.SkipToNextMark();
//			Land_Scape.RefreshLandscape();
//DEADCODE JIM 19/05/99 			_Replay.CalcCurrPos();
//			OverLay.pvp->BlockTick(FALSE);
			break;
		case SEL_9:		//clear markers
			OverLay.hilight=k;
			_Replay.RemoveMarks();
			break;
		case SEL_8:		//save
#ifndef MIG_DEMO_VER
			OverLay.hilight=k;
			if (_Replay.SaveBlock())
			{
				_Replay.BackupPlaybackPosition();
				_DPlay.SimulateExitKey=TRUE;
			}
			break;
#endif
	//alt-X to exit
	case SEL_0:		//eject
	case SEL_QUIT:
// escape is used for reset view which we need, so dont have as exit
//		case SEL_ESC:
			OverLay.hilight=k;
			retval=NULL;
			_DPlay.SimulateExitKey=TRUE;
			OverLay.quit3d=1;
			break;
		case SEL_MINUS:	//mark start:
			OverLay.hilight=k;
			_Replay.MarkBlockBeginning();
			break;
		case SEL_PLUS:	//mark end
			OverLay.hilight=k;
			_Replay.MarkBlockEnd();
			break;
		default:
			break;
		}
	}

	return retval;
}

MapScr COverlay::replayPlayingScr=
{
	MapScr::SCALE_DOUBLEIFGT800,
	0,0,
	320,32,
	0,0,
	NO_BACKGROUND_WIPE,
	ICON_BACK_COLOUR,
	ICON_BACK_COLOUR,
	32,32,
	12,2,
	0x00C8,
	MapScr::ReplayScreenInit,
	MapScr::ShowPositionIndicators,
	{
		{IDS_MAPICON01LO,1,SEL_1,MapScr::SelectFromReplayScreen},		//skip back
		{IDS_MAPICON02LO,1,SEL_2,MapScr::SelectFromReplayScreen},		//back a block
		{IDS_MAPICON12LO,1,SEL_3,MapScr::SelectFromReplayScreen},		//back a frame
		{IDS_MAPICON04LO,1,SEL_4,MapScr::SelectFromReplayScreen},		//play
//DeadCode AMM 24Feb99 		{IDS_MAPICON03LO,1,SEL_4,MapScr::SelectFromReplayScreen},		//pause
		{IDS_MAPICON11LO,1,SEL_5,MapScr::SelectFromReplayScreen},		//forward a frame
		{IDS_MAPICON05LO,1,SEL_6,MapScr::SelectFromReplayScreen},		//forward a block
		{IDS_MAPICON10LO,1,SEL_7,MapScr::SelectFromReplayScreen},		//skip forward
		{IDS_MAPICON07LO,1,SEL_8,MapScr::SelectFromReplayScreen},		//save
		{IDS_MAPICON06LO,1,SEL_9,MapScr::SelectFromReplayScreen},		//clear markers
		{IDS_MAPICON00LO,1,SEL_0,MapScr::SelectFromReplayScreen},		//eject
		{IDS_MAPICON08LO,1,SEL_MINUS,MapScr::SelectFromReplayScreen},	//mark start
		{IDS_MAPICON09LO,1,SEL_PLUS,MapScr::SelectFromReplayScreen},	//mark end
		{IDS_MAPICON13LO,0,SEL_BLANK,NULL},								//progress bar start
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON15LO,0,SEL_BLANK,NULL},								//progress bar end
		MSAltXLine(MapScr::SelectFromReplayScreen),
		MSPauseLine(MapScr::SelectFromReplayScreen),
		MSEscapeLine(MapScr::SelectFromReplayScreen),					//escape (eject)
		MSListEnd
	}
};

MapScr COverlay::replayScr=
{
	MapScr::SCALE_DOUBLEIFGT800,
	0,0,
	320,32,
	0,0,
	NO_BACKGROUND_WIPE,
	ICON_BACK_COLOUR,
	ICON_BACK_COLOUR,
	32,32,
	12,2,
	0x0014,
	MapScr::ReplayScreenInit,
	MapScr::ShowPositionIndicators,
	{
		{IDS_MAPICON01LO,1,SEL_1,MapScr::SelectFromReplayScreen},		//skip back
		{IDS_MAPICON02LO,1,SEL_2,MapScr::SelectFromReplayScreen},		//back a block
		{IDS_MAPICON12LO,1,SEL_3,MapScr::SelectFromReplayScreen},		//back a frame
//DeadCode AMM 24Feb99 		{IDS_MAPICON04LO,1,SEL_4,MapScr::SelectFromReplayScreen},		//play
		{IDS_MAPICON03LO,1,SEL_4,MapScr::SelectFromReplayScreen},		//pause
		{IDS_MAPICON11LO,1,SEL_5,MapScr::SelectFromReplayScreen},		//forward a frame
		{IDS_MAPICON05LO,1,SEL_6,MapScr::SelectFromReplayScreen},		//forward a block
		{IDS_MAPICON10LO,1,SEL_7,MapScr::SelectFromReplayScreen},		//skip forward
		{IDS_MAPICON07LO,1,SEL_8,MapScr::SelectFromReplayScreen},		//save
		{IDS_MAPICON06LO,1,SEL_9,MapScr::SelectFromReplayScreen},		//clear markers
		{IDS_MAPICON00LO,1,SEL_0,MapScr::SelectFromReplayScreen},		//eject
		{IDS_MAPICON08LO,1,SEL_MINUS,MapScr::SelectFromReplayScreen},	//mark start
		{IDS_MAPICON09LO,1,SEL_PLUS,MapScr::SelectFromReplayScreen},	//mark end
		{IDS_MAPICON13LO,0,SEL_BLANK,NULL},								//progress bar start
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON14LO,0,SEL_BLANK,NULL},								//progress bar middle
		{IDS_MAPICON15LO,0,SEL_BLANK,NULL},								//progress bar end
		MSAltXLine(MapScr::SelectFromReplayScreen),
		MSPauseLine(MapScr::SelectFromReplayScreen),
		MSEscapeLine(MapScr::SelectFromReplayScreen),					//escape (eject)
		MSListEnd
	}
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsDialogInit
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
Key MapScr::CommsDialogInit()
{
	OverLay.commsDialReturn=0;
	return SEL_ENTER;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromCommsDialog
//Author		Paul.   
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromCommsDialog(UByte&,Key k)
{
	MapScr* retval=this;

	switch (k)
	{
	case SEL_ESC:
		OverLay.commsDialReturn=0xFFFF;
		break;
	case SEL_ENTER:
		OverLay.commsDialReturn=1;
		break;
	default:
		break;
	}
	return retval;
}

MapScr COverlay::commsDialog=
{
	MapScr::JUSTIFY_CENTRE_SX+MapScr::JUSTIFY_CENTRE_SY,
	0,0,
	320,32,
	0,0,
	SET_WIPE_TEXTURE(RADIONO),
	TEXT_MAP_BLACK,
	TEXT_MAP_BLACK,
	32,32,
	10,1,
	0x0000,
	MapScr::CommsDialogInit,
	NULL,
	{
		{IDS_COMMSDIALMSG,0,SEL_NONE,NULL},
		MSBlankLine,
		{IDS_COMMSDIALOK,0,SEL_ENTER,MapScr::SelectFromCommsDialog},
		{IDS_COMMSDIALCANCEL,0,SEL_ESC,MapScr::SelectFromCommsDialog},
		MSListEnd
	}
};

/***********************
* MAP VIEW ICON SCREEN *
***********************/

struct IconEntry COverlay::mapViewIconTable[]=
{
{MAPICNSNO,0,0,32,32},		//IDS_MAPICON00LO
{MAPICN2NO,0,0,32,32},		//IDS_MAPICON00HI
{MAPICNSNO,32,0,32,32},		//IDS_MAPICON01LO
{MAPICN2NO,32,0,32,32},		//IDS_MAPICON01HI
{MAPICNSNO,64,0,32,32},		//IDS_MAPICON02LO
{MAPICN2NO,64,0,32,32},		//IDS_MAPICON02HI
{MAPICNSNO,96,0,32,32},		//IDS_MAPICON03LO
{MAPICN2NO,96,0,32,32},		//IDS_MAPICON03HI

{MAPICNSNO,0,32,32,32},		//IDS_MAPICON04LO
{MAPICN2NO,0,32,32,32},		//IDS_MAPICON04HI
{MAPICNSNO,32,32,32,32},	//IDS_MAPICON05LO
{MAPICN2NO,32,32,32,32},	//IDS_MAPICON05HI
{MAPICNSNO,64,32,32,32},	//IDS_MAPICON06LO
{MAPICN2NO,64,32,32,32},	//IDS_MAPICON06HI
{MAPICNSNO,96,32,32,32},	//IDS_MAPICON07LO
{MAPICN2NO,96,32,32,32},	//IDS_MAPICON07HI

{MAPICNSNO,0,64,32,32},		//IDS_MAPICON08LO
{MAPICN2NO,0,64,32,32},		//IDS_MAPICON08HI
{MAPICNSNO,32,64,32,32},	//IDS_MAPICON09LO
{MAPICN2NO,32,64,32,32},	//IDS_MAPICON09HI
{MAPICNSNO,64,64,32,32},	//IDS_MAPICON09LO
{MAPICN2NO,64,64,32,32},	//IDS_MAPICON09HI
{MAPICNSNO,96,64,32,32},	//IDS_MAPICON09LO
{MAPICN2NO,96,64,32,32},	//IDS_MAPICON09HI

{MAPICNSNO,0,96,32,32},		//IDS_MAPICON09LO
{MAPICN2NO,0,96,32,32},		//IDS_MAPICON09HI
{MAPICNSNO,32,96,32,32},	//IDS_MAPICON09LO
{MAPICN2NO,32,96,32,32},	//IDS_MAPICON09HI
{MAPICNSNO,64,96,32,32},	//IDS_MAPICON09LO
{MAPICN2NO,64,96,32,32},	//IDS_MAPICON09HI
{MAPICNSNO,96,96,32,32},	//IDS_MAPICON09LO
{MAPICN2NO,96,96,32,32}		//IDS_MAPICON09HI
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MapViewScreenInit
//Author		Paul.   
//Date			Thu 11 Mar 1999
//------------------------------------------------------------------------------
Key MapScr::MapViewScreenInit()
{
	OverLay.fHitZoomLimit=false;
	return SEL_ENTER;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectFromMapViewScreen
//Author		Paul.   
//Date			Thu 11 Mar 1999
//------------------------------------------------------------------------------
MapScr* MapScr::SelectFromMapViewScreen(UByte&,Key k)
{
	MapScr* retval=this;

	switch (k)
	{
	case SEL_1:		//rotate left
		if (k!=OverLay.hilight)	OverLay.hilight=k;
		else					OverLay.hilight=SEL_NONE;
		break;
	case SEL_2:		//rotate right
		if (k!=OverLay.hilight)	OverLay.hilight=k;
		else					OverLay.hilight=SEL_NONE;
		break;
	case SEL_3:		//zoom out
		if (k!=OverLay.hilight)	OverLay.hilight=k;
		else					OverLay.hilight=SEL_NONE;
		break;
	case SEL_4:		//zoom in
		if (k!=OverLay.hilight)	OverLay.hilight=k;
		else					OverLay.hilight=SEL_NONE;
		break;
	case SEL_5:		//reset
		OverLay.highTimer=100;
		OverLay.hilight=k;
		break;
	case SEL_0:		//exit
	case SEL_ESC:
		OverLay.quit3d=1;
		delete OverLay.targName;
		OverLay.targName=NULL;
		retval=NULL;
		break;
	default:
		break;
	}
	return retval;
}

MapScr COverlay::mapViewScr=
{
	MapScr::SCALE_DOUBLEIFGT800,
	0,0,
	320,32,
	0,0,
	NO_BACKGROUND_WIPE,
	ICON_BACK_COLOUR,
	ICON_BACK_COLOUR,
	32,32,
	6,1,
	0x0000,
	MapScr::MapViewScreenInit,
	MapScr::DisplayTargName,
	{
		{IDS_MAPICON00LO,1,SEL_1,MapScr::SelectFromMapViewScreen},		//rotate left
		{IDS_MAPICON01LO,1,SEL_2,MapScr::SelectFromMapViewScreen},		//rotate right
		{IDS_MAPICON02LO,1,SEL_3,MapScr::SelectFromMapViewScreen},		//zoom out
		{IDS_MAPICON03LO,1,SEL_4,MapScr::SelectFromMapViewScreen},		//zoom in
		{IDS_MAPICON04LO,1,SEL_5,MapScr::SelectFromMapViewScreen},		//reset
		{IDS_MAPICON05LO,1,SEL_0,MapScr::SelectFromMapViewScreen},		//exit
		MSEscapeLine(MapScr::SelectFromMapViewScreen),					//exit
		MSListEnd
	}
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTargName
//Author		Paul.   
//Date			Fri 12 Mar 1999
//------------------------------------------------------------------------------
void COverlay::SetTargName(char* tn)
{
	targName=new CString(LPCTSTR(tn));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DisplayTargName
//Author		Paul.   
//Date			Fri 12 Mar 1999
//------------------------------------------------------------------------------
void MapScr::DisplayTargName() {OverLay.DisplayTargName();}
void COverlay::DisplayTargName()
{
	//handle icon based zoom & rotate requests here

	static int i=0;
	if((++i)&3)
		pvp->ExecuteMapViewCommand(Key(hilight));

	if (fHitZoomLimit)
	{
		hilight=SEL_NONE;
		fHitZoomLimit=false;
	}

	if (targName)
	{
		LPCTSTR ps=LPCTSTR(*targName);
		pw->DoSetGlobalAlpha(255);
		if (!Save_Data.fSoftware)	pw->DoSetFontColour(TEXT_MAP_WHITE);
		else						POLYGON.SetFontColour(WHITE);


		pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
		fIsWide=IsWide(physicalWidth);
		SWord text_width=StrPixelLen((char*)ps);
		SWord text_x=(physicalWidth-text_width)>>1;
		if (text_x<0) text_x=0;
		SWord text_y=physicalHeight-(fIsWide?32:16);
		PrintAt2(text_x,text_y,(char*)ps);
	}
}

Float AbsRoot(Float f)
{
	double d;
	bool pos;
	if (f<0)
	{
		pos=false;
		d=-f;
	}
	else
	{
		pos=true;
		d=f;
	}
	_asm{
		fld	d;
		fsqrt;
		fstp d;
	}
	return pos?Float(d):Float(-d);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoThreat
//Author		Paul.   
//Date			Fri 26 Mar 1999
//------------------------------------------------------------------------------
void COverlay::DoThreat()
{
	//display threat indicator in the top left corner of the screen
	const SWord THREAT_X=10;
	const SWord THREAT_Y=0;
	const SWord THREAT_W=64*2;
	const SWord THREAT_H=64*2;
	const SWord THREAT_CX=31*2;
	const SWord THREAT_CY=31*2;
	const SWord THREAT_RAD=29*2;
	const SWord THREAT_DISC_H=6*2;
	const SWord MAX_THREATS=32;

	SLong THREAT_RANGE=MaxVisibleRange;	//viewsel.h
	SLong THREAT_ALT=MaxVisibleRange;

	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
	const Float scx=Float(physicalWidth)/640.;
	const Float scy=Float(physicalHeight)/480.;
	const Float scaled_x=scx*Float(THREAT_X);
	const Float scaled_w=scx*Float(THREAT_W);
	const Float scaled_threat_radx=scx*Float(THREAT_RAD);
	const Float scaled_threat_disc_hx=scx*Float(THREAT_DISC_H);
	const Float scaled_y=scy*Float(THREAT_Y);
	const Float scaled_h=scy*Float(THREAT_H);
	const Float scaled_threat_rady=scy*Float(THREAT_RAD);
	const Float scaled_threat_disc_hy=scy*Float(THREAT_DISC_H);

	const Float scaled_orix=scaled_x+scaled_w*.5;
	const Float scaled_oriy=scaled_y+scaled_h*.5;
 
	SWord oldTQ=pw->DoForceTQ(4);
	bool oldMip=pw->DoSetMipMap(false);

	ImageMapDesc* pmap=Image_Map.GetImageMapPtr(THREAT01NO);
 
 	DoPointStruc dp[4];
  	dp[0].bodyx.f=Float(scaled_x);
 	dp[0].bodyy.f=Float(scaled_y);
 	dp[0].ix=
 	dp[0].iy=0;
 	dp[1].bodyx.f=Float(scaled_x+scaled_w);
 	dp[1].bodyy.f=Float(scaled_y);
 	dp[1].ix=128;
 	dp[1].iy=0;
 	dp[2].bodyx.f=Float(scaled_x+scaled_w);
 	dp[2].bodyy.f=Float(scaled_y+scaled_h);
 	dp[2].ix=
 	dp[2].iy=128;
 	dp[3].bodyx.f=Float(scaled_x);
 	dp[3].bodyy.f=Float(scaled_y+scaled_h);
 	dp[3].ix=0;
 	dp[3].iy=128;
	if (!Save_Data.fSoftware)	pw->DoSetFontColour(0xFFFFFFFF);
	else						POLYGON.SetFontColour(WHITE);
	if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap,dp);
	else						pw->DoPutC(pmap,dp);
	pw->DoForceTQ(oldTQ);
	pw->DoSetMipMap(oldMip);

	//check for a/c within THREAT_RANGE cm

	COORDS3D* crd=new COORDS3D[MAX_THREATS];
	UByte* col=new UByte[MAX_THREATS];

	SWord cnt=MAX_THREATS;

	pvp->GetThreatData(cnt,crd,col,THREAT_RANGE);

	if (++cnt>0)
	{
		for (int i=0;i<cnt;i++)
		{
			//generate the screen coordinates for each 
			//aircraft on the threat indicator.

			Float ix,iy,iz;
			ix=AbsRoot(Float(crd[i].X)/Float(THREAT_RANGE));
			iz=AbsRoot(Float(crd[i].Z)/Float(THREAT_RANGE));

			ix*=scaled_threat_radx;
			iz*=scaled_threat_disc_hy;
			ix=scaled_orix+ix;
			iz=scaled_oriy-iz;

			if (crd[i].Y>-THREAT_ALT && crd[i].Y<THREAT_ALT)
			{
				iy=scaled_threat_rady*AbsRoot(Float(crd[i].Y)/Float(THREAT_ALT));

				SWord lsx,lsy,lex,ley,lbx,lby,bex,bey;

				lbx=SWord(scaled_orix);
				lby=SWord(scaled_oriy);
				lsx=lex=SWord(ix);
				lsy=SWord(iz);
				ley=lsy-SWord(iy);

				if (lsy==ley) ley++;

				SWord flag=(lsy>ley)?2:-2;

				if (col[i])
				{
					DrawLine(lbx,lby,lsx,lsy,RED);
					DrawLine(lsx,lsy,lex,ley,RED);
					lex=lsx=lex+1;
					lsy=ley+flag;
					DrawLine(lsx,lsy,lex,ley,RED);
				}
				else
				{
					DrawLine(lbx,lby,lsx,lsy,Colour(197));			  //RDH 05/05/99 was 208 light blue
					DrawLine(lsx,lsy,lex,ley,Colour(197));			  //RDH 05/05/99
					lex=lsx=lex+1;
					lsy=ley+flag;
					DrawLine(lsx,lsy,lex,ley,Colour(197));			  //RDH 05/05/99
				}
			}
		}
	}
	delete[]col;
	delete[]crd;
}

static int lastoffset=0x7fffffff;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCheatBox
//Author		Paul.   
//Date			Wed 5 May 1999
//------------------------------------------------------------------------------
void COverlay::DoCheatBox()
{
	const SWord DIAMOND_WH=16;

	if (Save_Data.detail_3d[DETAIL3D_PADLOCKCHEAT] && 
		pvp && 
		pvp->trackeditem2 &&
		pvp->trackeditem2->Status.size!=WayPointSize &&
		(pvp->viewnum.viewmode==VM_OutPadlock || pvp->viewnum.viewmode==VM_InPadlock))
	{
		pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
		const Float scaled_w_2=Float(DIAMOND_WH)*Float(physicalWidth)/(2.*640.);
		const Float scaled_h_2=Float(DIAMOND_WH)*Float(physicalHeight)/(2.*480.);

		FPMATRIX tmat,*tmatp=&tmat;
		_matrix.Generate(pvp->hdg,pvp->pitch,pvp->roll,tmatp);
		DoPointStruc dp;
		COORDS3D itemPos;
		if (!Three_Dee.GetPosRec(pvp->trackeditem2,itemPos))
			itemPos=pvp->trackeditem2->World;
		dp.bodyx.i=itemPos.X-pvp->World.X;
		dp.bodyy.i=itemPos.Y-pvp->World.Y;
		dp.bodyz.i=itemPos.Z-pvp->World.Z;
		if (_matrix.transform(tmatp,dp.bodyx,dp.bodyy,dp.bodyz)==0)
		{
			if (Save_Data.fSoftware)
			{
				float rw=float(1./(POLYGON.viewdata.hoD*dp.bodyz.f));
				float sx=float(POLYGON.viewdata.scalex*dp.bodyx.f*rw);
				float sy=float(-(POLYGON.viewdata.scaley*dp.bodyy.f*rw));
				dp.screenx.f=sx;
				dp.screeny.f=sy;
			}
			else pw->DoBody2Screen(dp);
			dp.screenx.f+=(physicalWidth>>1);
			dp.screeny.f+=(physicalHeight>>1);
			SWord x1,y1,x2,y2;
			x1=SWord(dp.screenx.f-scaled_w_2);
			y1=SWord(dp.screeny.f);
			x2=SWord(dp.screenx.f);
			y2=SWord(dp.screeny.f-scaled_h_2);
			DoClippedLine(x1,y1,x2,y2,RED,0,0,physicalWidth,physicalHeight);
			x1=x2;
			y1=y2;
			x2=SWord(dp.screenx.f+scaled_w_2);
			y2=SWord(dp.screeny.f);
			DoClippedLine(x1,y1,x2,y2,RED,0,0,physicalWidth,physicalHeight);
			x1=x2;
			y1=y2;
			x2=SWord(dp.screenx.f);
			y2=SWord(dp.screeny.f+scaled_h_2);
			DoClippedLine(x1,y1,x2,y2,RED,0,0,physicalWidth,physicalHeight);
			x1=x2;
			y1=y2;
			x2=SWord(dp.screenx.f-scaled_w_2);
			y2=SWord(dp.screeny.f);
			DoClippedLine(x1,y1,x2,y2,RED,0,0,physicalWidth,physicalHeight);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoClippedLine
//Author		Paul.   
//Date			Wed 5 May 1999
//------------------------------------------------------------------------------
void COverlay::DoClippedLine(SWord x1,SWord y1,SWord x2,SWord y2,Colour col,
							SWord left,SWord top,SWord right,SWord bottom)
{
	UWord cf1=CF3D_NULL,cf2=CF3D_NULL;
	if (x1<left)		cf1|=CF3D_OFFLEFT;
	else if (x1>right)	cf1|=CF3D_OFFRIGHT;
	if (y1<top)			cf1|=CF3D_OFFTOP;
	else if (y1>bottom)	cf1|=CF3D_OFFBOTTOM;
	if (x2<left)		cf2|=CF3D_OFFLEFT;
	else if (x2>right)	cf2|=CF3D_OFFRIGHT;
	if (y2<top)			cf2|=CF3D_OFFTOP;
	else if (y2>bottom)	cf2|=CF3D_OFFBOTTOM;
	if ((cf1&cf2)==0)
	{
		if ((cf1|cf2)!=0)
		{
			if ((cf1|cf2)&CF3D_OFFTOP)
			{
				if (cf1&CF3D_OFFTOP) {SWord q=x1;x1=x2;x2=q;q=y1;y1=y2;y2=q;}
				Float frac=Float(top-y1)/Float(y2-y1);
				x2=x1+SWord(frac*Float(x2-x1));
				y2=top;
				if (x2<left)		cf2=CF3D_OFFLEFT;
				else if (x2>right)	cf2=CF3D_OFFRIGHT;
				else				cf2=CF3D_NULL;
			}
			if ((cf1|cf2)&CF3D_OFFBOTTOM)
			{
				if (cf1&CF3D_OFFBOTTOM) {SWord q=x1;x1=x2;x2=q;q=y1;y1=y2;y2=q;}
				Float frac=Float(bottom-y1)/Float(y2-y1);
				x2=x1+SWord(frac*(x2-x1));
				y2=bottom;
				if (x2<left)		cf2=CF3D_OFFLEFT;
				else if (x2>right)	cf2=CF3D_OFFRIGHT;
				else				cf2=CF3D_NULL;
			}
			if ((cf1|cf2)&CF3D_OFFLEFT)
			{
				if (cf1&CF3D_OFFLEFT) {SWord q=x1;x1=x2;x2=q;q=y1;y1=y2;y2=q;}
				Float frac=Float(left-x1)/Float(x2-x1);
				y2=y1+SWord(frac*Float(y2-y1));
				x2=left;
				cf2=CF3D_NULL;
			}
			if ((cf1|cf2)&CF3D_OFFRIGHT)
			{
				if (cf1&CF3D_OFFRIGHT) {SWord q=x1;x1=x2;x2=q;q=y1;y1=y2;y2=q;}
				Float frac=Float(right-x1)/Float(x2-x1);
				y2=y1+SWord(frac*Float(y2-y1));
				x2=right;
				cf2=CF3D_NULL;
			}
		}
		if ((cf1|cf2)==0)
			DrawLine(x1,y1,x2,y2,col);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoArtHoriz
//Author		Paul.   
//Date			Wed 5 May 1999
//------------------------------------------------------------------------------
void COverlay::DoArtHoriz()
{
	//display threat indicator in the top left corner of the screen
	const SWord THREAT_X=640-64-10;
	const SWord THREAT_Y=10;
	const SWord THREAT_W=64;
	const SWord THREAT_H=64;
	const SWord THREAT_CX=31;
	const SWord THREAT_CY=31;
	const SWord THREAT_RAD=29;
	const SWord THREAT_DISC_H=6;
	const SLong THREAT_RANGE=1000000;
	const SLong THREAT_ALT=1000000;
	const SWord MAX_THREATS=32;

	pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
	const Float scx=Float(physicalWidth)/640.;
	const Float scy=Float(physicalHeight)/480.;
	const Float scaled_x=scx*Float(THREAT_X);
	const Float scaled_w=scx*Float(THREAT_W);
	const Float scaled_threat_radx=scx*Float(THREAT_RAD);
	const Float scaled_threat_disc_hx=scx*Float(THREAT_DISC_H);
	const Float scaled_y=scy*Float(THREAT_Y);
	const Float scaled_h=scy*Float(THREAT_H);
	const Float scaled_threat_rady=scy*Float(THREAT_RAD);
	const Float scaled_threat_disc_hy=scy*Float(THREAT_DISC_H);

	const Float scaled_orix=scaled_x+scaled_w*.5;
	const Float scaled_oriy=scaled_y+scaled_h*.5;
 
	SWord oldTQ=pw->DoForceTQ(4);
	bool oldMip=pw->DoSetMipMap(false);

	//make ball center image

	ImageMapDesc* pOuterImage=Image_Map.GetImageMapPtr(BALL03NO);	//128x128
	ImageMapDesc* pMaskImage=Image_Map.GetImageMapPtr(BALL02NO);	//128x128
	ImageMapDesc* pCentralImage=Image_Map.GetImageMapPtr(BALL01NO);	//256x256

	if (pball==NULL)
	{
		lastoffset=0x7fffffff;
		pball=(ImageMapDesc*)(new UByte[sizeof(ImageMapDesc)+pMaskImage->w*pMaskImage->h*2]);
		pball->w=pMaskImage->w;
		pball->h=pMaskImage->h;
		pball->body=((UByte*)pball)+sizeof(ImageMapDesc);
		pball->alpha=pball->body+pball->w*pball->h;
		pball->palette=pMaskImage->palette;
		pball->paletteindex=pMaskImage->paletteindex;
		pball->isMasked=pMaskImage->isMasked;
		UByte* pBallAlpha=pball->alpha;
		UByte* pMaskAlpha=pMaskImage->body;
		for (int w=0;w<pball->w*pball->h;w++)
			*pBallAlpha++=(*pMaskAlpha++==UByte(ARTWORKMASK))?0:0x7F;
	}

	//use a/c pitch to fill the ball image

	UByte *pDst,*pSrc,*pMsk,*pSrcEnd;

	pSrc=pCentralImage->body;
	pSrcEnd=pSrc+pCentralImage->w*pCentralImage->h;
	pDst=pball->body;
	pMsk=pMaskImage->body;

	pSrc+=pCentralImage->w>>2;

	int offset=(int(SWord(-Manual_Pilot.ControlledAC2->pitch))<<6)/int(ANGLES_90Deg)+64;

	if (offset!=lastoffset)
	{
		pSrc+=offset*pCentralImage->w;

		for (int y=0;y<pball->w;y++)
		{
			UByte* pDst2=pDst;
			UByte* pMsk2=pMsk;
			UByte* pSrc2=pSrc;
			for (int x=0;x<pball->h;x++)
			{
				if (*pMsk2==UByte(ARTWORKMASK))	*pDst2=UByte(ARTWORKMASK);
				else							*pDst2=*pSrc2;
				pMsk2++;
				pDst2++;
				pSrc2++;
			}
			pDst+=pball->w;
			pMsk+=pball->w;
			pSrc+=pCentralImage->w;
			if (ULong(pSrc)>=ULong(pSrcEnd))
				pSrc-=pCentralImage->w*pCentralImage->h;
		}

	}

	SWord sinAng,cosAng;

	Math_Lib.high_sin_cos(Manual_Pilot.ControlledAC2->roll,sinAng,cosAng);

	Float m[4];

	//generate 2D rotation matrix

	m[0]=m[3]=Float(cosAng)/Float(ANGLES_FRACT);
	m[1]=Float(sinAng)/Float(ANGLES_FRACT);
	m[2]=-Float(sinAng)/Float(ANGLES_FRACT);

 	DoPointStruc dp[4],dp2[4];
  	dp[0].bodyx.f=Float(scaled_x);
 	dp[0].bodyy.f=Float(scaled_y);
 	dp[0].ix=
 	dp[0].iy=0;
 	dp[1].bodyx.f=Float(scaled_x+scaled_w);
 	dp[1].bodyy.f=Float(scaled_y);
 	dp[1].ix=128;
 	dp[1].iy=0;
 	dp[2].bodyx.f=Float(scaled_x+scaled_w);
 	dp[2].bodyy.f=Float(scaled_y+scaled_h);
 	dp[2].ix=
 	dp[2].iy=128;
 	dp[3].bodyx.f=Float(scaled_x);
 	dp[3].bodyy.f=Float(scaled_y+scaled_h);
 	dp[3].ix=0;
 	dp[3].iy=128;

	//apply a/c roll to rotate the ball poly coordinates

	Float ori_x=0,ori_y=0;
	for (int i=0;i<4;i++)
	{
		ori_x+=dp[i].bodyx.f;
		ori_y+=dp[i].bodyy.f;
	}
	ori_x/=4;
	ori_y/=4;

	for (i=0;i<4;i++)
	{
		Float tx=dp[i].bodyx.f-ori_x;
		Float tz=dp[i].bodyy.f-ori_y;
		dp[i].bodyx.f=m[0]*tx+m[1]*tz+ori_x;
		dp[i].bodyy.f=m[2]*tx+m[3]*tz+ori_y;
	}

	if (!Save_Data.fSoftware)	pw->DoSetFontColour(0xFFFFFFFF);
	else						POLYGON.SetFontColour(WHITE);
	if (!Save_Data.fSoftware)	pw->DoPutC(pball,dp,offset!=lastoffset?true:false);
  	dp2[0].bodyx.f=Float(scaled_x);
 	dp2[0].bodyy.f=Float(scaled_y);
 	dp2[0].ix=
 	dp2[0].iy=0;
 	dp2[1].bodyx.f=Float(scaled_x+scaled_w);
 	dp2[1].bodyy.f=Float(scaled_y);
 	dp2[1].ix=128;
 	dp2[1].iy=0;
 	dp2[2].bodyx.f=Float(scaled_x+scaled_w);
 	dp2[2].bodyy.f=Float(scaled_y+scaled_h);
 	dp2[2].ix=
 	dp2[2].iy=128;
 	dp2[3].bodyx.f=Float(scaled_x);
 	dp2[3].bodyy.f=Float(scaled_y+scaled_h);
 	dp2[3].ix=0;
 	dp2[3].iy=128;
	if (Save_Data.fSoftware)	
	{
		POLYGON.DoPutC(pOuterImage,dp2);
		POLYGON.DoPutC(pball,dp);
	}
	else pw->DoPutC(pOuterImage,dp2);
	pw->DoForceTQ(oldTQ);
	pw->DoSetMipMap(oldMip);

	lastoffset=offset;
}

void COverlay::CrossHair()
{
	if (pvp && pvp->viewnum.viewmode==VM_InsideCheat)
	{
		pw->DoGetSurfaceDimensions(physicalWidth,physicalHeight);
		const SLong CROSS_WH_2=16;
		const SLong CROSS_Y_SHIFT=3;
		SLong cross_w=(CROSS_WH_2*physicalWidth)/640;
		SLong cross_h=(CROSS_WH_2*physicalHeight)/480;
		SLong cross_y_shift=(CROSS_Y_SHIFT*physicalHeight)/640;
		SWord x1,y1,x2,y2;
		x1=x2=physicalWidth>>1;
		y1=(physicalHeight>>1)-cross_h+cross_y_shift;
		y2=(physicalHeight>>1)+cross_h+cross_y_shift;
		DrawLine(x1,y1,x2,y2,RED);
		y1=y2=(physicalHeight>>1)+cross_y_shift;
		x1=(physicalWidth>>1)-cross_w;
		x2=(physicalWidth>>1)+cross_w;
		DrawLine(x1,y1,x2,y2,RED);
	}
}

void COverlay::DrawLine(SWord sx,SWord sy,SWord ex,SWord ey,Colour c)
{
	if (!Save_Data.fSoftware)	pw->DoPutLine(sx,sy,ex,ey,c);
	else						POLYGON.DoLine2D(c,sx,sy,ex,ey);
}

void COverlay::TriggerMessage(COverlay::MessageType mt,UWord val)
{
	char* theString;
	char localText[64];
	switch (mt)
	{
	case NOVIEWMESS:
		theString=LdStr(IDS_VIEWNOTAVAILABLE);
		sprintf(localText,"%s",theString);
		*otherText=CString(localText);
		messageTimer=500;
		break;
	case IMPACTONMESS:
		theString=LdStr(IDS_IMPACTTOGGLEON);
		sprintf(localText,"%s",theString);
		*otherText=CString(localText);
		messageTimer=500;
		break;
	case IMPACTOFFMESS:
		theString=LdStr(IDS_IMPACTTOGGLEOFF);
		sprintf(localText,"%s",theString);
		*otherText=CString(localText);
		messageTimer=500;
		break;
	case SENSMESS:
		theString=LdStr(IDS_KEY0);									  //RDH 19/05/99
		sprintf(localText,"%s %d",theString,val);
		*otherText=CString(localText);
		messageTimer=500;
		break;
	case PAUSEMESS:
		*otherText=CString("");
		messageTimer=500;
		break;
	case ACCELMESS:
		theString=LdStr(IDS_MAP_ACCEL);
		sprintf(localText,"%s X4",theString);
		delete[]theString;
		*otherText=CString(localText);
		messageTimer=0x7FFF;
		break;
	case CLEARMESS:
		if (!otherText->IsEmpty())
		{
			*otherText=CString("");
			messageTimer=0;
		}
		break;
	}
}

void COverlay::HotKeyTriggerMenu(SWord sel)
{
	if (pCurScr==NULL)
	{
		Key k=(Key)sel;
		localDec=NULL;
		switch (k)
		{
		case SEL_1:	localDec=GroupInfoMsg;	break;
		case SEL_2:	localDec=PreCombatMsg;	break;
		case SEL_3:	localDec=CombatMsg;		break;
		case SEL_4:	localDec=PostCombatMsg;	break;
		case SEL_5:	localDec=TowerMsg;		break;
		case SEL_6:	localDec=FACMsg;		break;
		default:	break;
		}
		if (localDec!=NULL)	SetToUIScreen(&userOptionsScr);
	}
}

void COverlay::HotKeyTriggerMessage(SWord sel1,SWord sel2)
{
	if (pCurScr==NULL)
	{
		DecisionAI* dec=NULL;
		Key k=(Key)sel1;
		localDec=NULL;
		switch (k)
		{
		case SEL_1:	dec=GroupInfoMsg;	break;
		case SEL_2:	dec=PreCombatMsg;	break;
		case SEL_3:	dec=CombatMsg;		break;
		case SEL_4:	dec=PostCombatMsg;	break;
		case SEL_5:	dec=TowerMsg;		break;
		case SEL_6:	dec=FACMsg;			break;
		default:	break;
		}
		if (dec!=NULL)
		{
			k=(Key)sel2;
//DeadCode AMM 21May99 			DecisionAI::OptionRef* opt=dec->GetMsgOptions();
			if (k>=SEL_1 && k<=SEL_9)
			{
				_Miles.SetDelayed(true);
				DecisionMessage(dec,
								(SWord)(k-SEL_1),
								Persons2::PlayerGhostAC,
								Persons2::PlayerGhostAC,
								Persons2::PlayerGhostAC);
				_Miles.SetDelayed(false);

//DeadCode AMM 21May99 				opt+=SLong(k-SEL_1);
//DeadCode AMM 21May99 				if (_DPlay.Implemented || _Replay.Record)		//AMM 17May99
//DeadCode AMM 21May99 				{												//AMM 17May99
//DeadCode AMM 21May99 					UByte option=(UByte)(k-SEL_1);				//AMM 17May99
//DeadCode AMM 21May99 					UniqueID trg=Persons2::PlayerGhostAC->uniqueID.count;//AMM 17May99
//DeadCode AMM 21May99 					UByte decision=dec->optionnumber;			//AMM 17May99
//DeadCode AMM 21May99 					_DPlay.NewWingmanCommand(decision,option,trg);//AMM 17May99
//DeadCode AMM 21May99 				}												//AMM 17May99
//DeadCode AMM 21May99 				else											//AMM 17May99
//DeadCode AMM 21May99 				{												//AMM 17May99
//DeadCode AMM 21May99 					MESSAGE_STRUC newMsg(opt->saidmsg,
//DeadCode AMM 21May99 										MSG_HIPRIORITY,
//DeadCode AMM 21May99 										Persons2::PlayerGhostAC,//AMM 17May99
//DeadCode AMM 21May99 										Persons2::PlayerGhostAC,//AMM 17May99
//DeadCode AMM 21May99 										Persons2::PlayerGhostAC);//AMM 17May99
//DeadCode AMM 21May99 //DeadCode AMM 17May99 											Manual_Pilot.ControlledAC2,
//DeadCode AMM 21May99 //DeadCode AMM 17May99 											Manual_Pilot.ControlledAC2,
//DeadCode AMM 21May99 //DeadCode AMM 17May99 											Manual_Pilot.ControlleddAC2);
//DeadCode AMM 21May99 					SendMessageAndCall(&newMsg,opt->airesult[0]);
//DeadCode AMM 21May99				}												//AMM 17May99
			}
		}
	}
}

void COverlay::Kludge()
{
	KeyVal3D keyTable[]=
	{	
	RPM_10,
	RPM_20,
	RPM_30,
	RPM_40,
	RPM_50,
	RPM_60,
	RPM_70,
	RPM_80,
	RPM_90,
	RPM_00,
	PADLOCKTOG,
	RESETVIEW,
	ROTUP,
	ROTDOWN,
	ROTLEFT,
	ROTRIGHT,
	PAUSEKEY,
	EXITKEY
	};
	const SLong keyCount=sizeof(keyTable)/sizeof(KeyVal3D);
	for (SLong i=keyCount-1;i>=0;i--) Key_Tests.KeyPress3d(keyTable[i]);
}

CString COverlay::ScrollyText::Scroll(CString& in,SWord ft)
{
	timer-=ft;
	if (timer<=0)
	{
		switch (state)
		{
		case WaitingToScroll:		state=ScrollingToEnd;		timer=ScrollToEndTime;		break;
		case ScrollingToEnd:		state=WaitingToScrollBack;	timer=WaitToScrollBackTime;	break;
		case WaitingToScrollBack:	state=ScrollingToFront;		timer=ScrollToFrontTime;	break;
		case ScrollingToFront:		state=WaitingToScroll;		timer=WaitToScrollTime;		break;
		}
	}
	switch (state)
	{
	case WaitingToScrollBack:
	case WaitingToScroll:
	break;
	case ScrollingToEnd:
	index+=CharsToShuffle(ft);
	if (index>targetIndex)
	{
		index=targetIndex;
		state=WaitingToScrollBack;
		timer=WaitToScrollBackTime;
	}
	break;
	case ScrollingToFront:
	index-=CharsToShuffle(ft);
	if (index<0)
	{
		index=0;
		state=WaitingToScroll;
		timer=WaitToScrollTime;
	}
	break;
	}
	return in.Right(in.GetLength()-index);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecisionMessage
//Author		Andy McMaster
//Date			Fri 21 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void COverlay::DecisionMessage(DecisionAI* dec,SWord option,AirStrucPtr callee,ItemBasePtr target,AirStrucPtr caller,Bool sayvox)
{
	if (_DPlay.Implemented || _Replay.Record)
	{
		UByte decision=dec->optionnumber;						
		UniqueID trg;

		if (target)
			trg=target->uniqueID.count;
		else
			trg=UID_Null;

		_DPlay.NewWingmanCommand(decision,option,trg);	
	}
	else
	{
	 	DecisionAI::OptionRef* opt=dec->GetMsgOptions();
	 	opt+=option;
//Poo		int		script;												//RJS 09Jun99
//Poo		if (sayvox)													//RJS 09Jun99
//Poo			script = opt->saidmsg;									//RJS 09Jun99
//Poo		else														//RJS 09Jun99
//Poo			script = 0;												//RJS 09Jun99

		MESSAGE_STRUC newMsg(opt->saidmsg,							//RJS 17Jun99
							MSG_HIPRIORITY,
							callee,
							target,
							caller);
		SendMessageAndCall(&newMsg,opt->airesult[0]);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AccelSelection
//Author		Andy McMaster
//Date			Thu 10 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	COverlay::AccelSelection(UByte hilight,ULong acceltype)
{
	_DPlay.AccelComms=(DPlay::AccelTypeComms)acceltype;
	_DPlay.Accelhilight=hilight;

// No accel in comms quick missions allowed

	if (_DPlay.Implemented)											  //AMM 02/07/99
		return;														  //AMM 02/07/99

//DeadCode AMM 01Jul99 // in comms only allow accel forward 
//DeadCode AMM 01Jul99 
//DeadCode AMM 01Jul99 	if (_DPlay.Implemented && _DPlay.AccelComms==DPlay::ACCEL_FORWARD)
//DeadCode AMM 01Jul99 	{
//DeadCode AMM 01Jul99 // if this is the first time I have pressed accel then send
//DeadCode AMM 01Jul99 // a message to other players indicating I want accel
//DeadCode AMM 01Jul99 
//DeadCode AMM 01Jul99 		if (!(_DPlay.accelselected&(1<<_DPlay.mySlot)))
//DeadCode AMM 01Jul99 		{
//DeadCode AMM 01Jul99 			_DPlay.SendStartAccelMessage();
//DeadCode AMM 01Jul99 		}
//DeadCode AMM 01Jul99 
//DeadCode AMM 01Jul99 
//DeadCode AMM 01Jul99 // we are still waiting for players to select accel 
//DeadCode AMM 01Jul99 // dont do it yet
//DeadCode AMM 01Jul99 
//DeadCode AMM 01Jul99 		if (_DPlay.accelselected!=_DPlay.ActivePlayers)
//DeadCode AMM 01Jul99 			return;
//DeadCode AMM 01Jul99 	}

 	OverLay.hilight=(Key)hilight;
	OverLay.keyFlags=KF_ACCELON+KF_FASTACCEL;
	refreshLandscape=true;

	switch (_DPlay.AccelComms)
	{
	case DPlay::ACCEL_FORWARD:
		Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_FWD);
		break;

	case DPlay::ACCEL_NEXTWP:
		Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_WAYPT);
		Manual_Pilot.acceltochanged=Manual_Pilot.ControlledAC2->waypoint;					  //JIM 18/04/99
		break;

	case DPlay::ACCEL_MESSAGESUBJECT:
		Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_MSG);
		break;

	case DPlay::ACCEL_MISSIONIP:
		Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_MISS);
		Manual_Pilot.acceltochanged=Manual_Pilot.ControlledAC2->waypoint->FindWP(WPNAME_Target);
		break;

	case DPlay::ACCEL_HOME:
		Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_MISS);
		Manual_Pilot.acceltochanged=Manual_Pilot.ControlledAC2->waypoint->FindWP(WPNAME_Disperse);
		break;

	case DPlay::ACCEL_WP_NEXTWP:
		OverLay.fZoomedMap=false;
		MapScr::map_scale=.5;
		Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_WAYPT);
		Manual_Pilot.acceltochanged=Manual_Pilot.ControlledAC2->waypoint;
		OverLay.curr_waypoint=Manual_Pilot.ControlledAC2->waypoint;
		break;

	case DPlay::ACCEL_WP_HIGHLIGHTED_WP:
		OverLay.fZoomedMap=false;
		MapScr::map_scale=.5;
		Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_WAYPT);
		Manual_Pilot.acceltochanged=OverLay.curr_waypoint;
		break;
	}
}

extern CFont* (g_AllFonts[][4]);
static ULong vsets[16]=
{
	0x00000000,0x000000ff,0x0000ff00,0x0000ffff,
	0x00ff0000,0x00ff00ff,0x00ffff00,0x00ffffff,
	0xff000000,0xff0000ff,0xff00ff00,0xff00ffff,
	0xffff0000,0xffff00ff,0xffffff00,0xffffffff
};

void	ImageMap_Desc::MakeChar(int cx, int cy, int	uChar)
{
	int ix=(cx*11) + 1;// + 4;
	int iy=(cy*14) + 1;//4;
	UWord theglyph[]={(uChar>>8)+(uChar<<8),0};

	GLYPHMETRICS gm={0};
//	MAT2		mat2={{51493,0},{0,0},{0,0},{60075,0}};
	MAT2		mat2={{46811,0},{0,0},{0,0},{60075,0}};

	enum	{MAX_BYTES_GLYPH=512};

	assert(GetGlyphOutline(	  g_OffScreenDC,             // handle to DC
							  uChar,          // character to query
							  GGO_GRAY8_BITMAP,//GGO_GRAY8_BITMAP,        // data format
							  &gm, // glyph metrics
							  0,      // size of data buffer
							  NULL,    // data buffer
							  &mat2   // transformation matrix
							) < MAX_BYTES_GLYPH);

	char buffer[MAX_BYTES_GLYPH];

	DWORD ggo2= GetGlyphOutline(
	  g_OffScreenDC,             // handle to DC
	  uChar,          // character to query
	  GGO_GRAY8_BITMAP,        // data format L
	  &gm, // glyph metrics
	  MAX_BYTES_GLYPH,      // size of data buffer
	  buffer,    // data buffer
	  &mat2   // transformation matrix
	);
	
	int longswide=(gm.gmBlackBoxX+3)>>2;
	ULong* src=(ULong*)buffer;
	ULong* trg=(ULong*)(alpha+ix+iy*128);
	int postlongsdelta=0;
	UByte failcode=0;
	if (gm.gmBlackBoxX>10)
	{
		failcode=0x40+gm.gmBlackBoxX;
		postlongsdelta=longswide-3;
		longswide=3;
	}
	//gm.gmptGlyphOrigin.y is where on the glyph the baseline is drawn.
	//I want the baseline at row 11/16
	int starty=11-gm.gmptGlyphOrigin.y;
	if (starty<0)
	{
		failcode=0x20+starty;
		starty=0;
	}
	if (starty>13)
	{
		failcode=0x20+starty;
		starty=13;
	}
	int gmBlackBoxY=gm.gmBlackBoxY+starty;
	if (gmBlackBoxY>13)
	{
		failcode=0x50+gmBlackBoxY;
		gmBlackBoxY=13;
	}

	body[uChar&0x7F] = gm.gmCellIncX + 1;
	alpha[uChar&0x7F] = failcode;
	{//assume(longswide>=0 && longswide<=4);
		int y;
		for (y=0;y<starty;y++)
		{
				*trg++=0;
				*trg++=0;
				*trg++=0;
				trg+=29;
		}
		for (;y<gmBlackBoxY;y++)
		{
			for (int x=0;x<longswide;x++)
			{
				ULong v=*src++;
				ULong t=v&0x40404040;
				v-=t;
//converting byte seperatyed flags to nibble.
				ULong u=t>>14;
				t+=u;
				u=t>>7;
				t+=u;
//deleting crap
				t&=0x3C0;
//putting nibble in right place
				t>>=6;
				v<<=2;
				v|=vsets[t];//hoping optimiser will reduce shift count.
				*trg++=v;
			}
			src+=postlongsdelta;
			for (;x<3;x++)
			{
				*trg++=0;
			}
			trg+=29;
		}
		for (;y<14;y++)
		{
				*trg++=0;
				*trg++=0;
				*trg++=0;
				trg+=29;
		}

		assert((int(trg)-int(alpha))<=(128*128)+29);
	}
}

void	ImageMap_Desc::InitFont(int	pageno, int width, int height)
{
// fill main map with white...

	for (int xy=0; xy < width*height; xy++)
	{
		alpha[xy] = 0;
		body[xy] = 31;
	}

// fill transparency with font table...
	CFont* oldfont=g_OffScreenDC.SelectObject(::g_AllFonts[2][0]);

	int	realpageno = pageno>>1;

	int		cyMax = 9;
	int		cxMax = 0;
	UINT	uChar = (realpageno << 8);

	if (!realpageno)
	{
// this is English, so do a bit of farting about... use characters 0 - 192
		if (pageno&0x01)		//2nd half...
			uChar += 96;
		else
			uChar += 0x20;
	}
	else
	{
		uChar |= 0x8000;

		if (pageno&0x01)
		{
			uChar += 160;
			cyMax = 8;
			cxMax = 5;
		}
		else
			uChar += 64;
	}

	for (int cy = 0; cy < cyMax; cy++)
	{
		for (int cx = 0; cx < 11; cx++)
		{
			MakeChar(cx,cy,uChar);
			uChar++;
		}
	}

	for (int cx = 0; cx < cxMax; cx++)
	{
		MakeChar(cx,cy,uChar);
		uChar++;
	}

	g_OffScreenDC.SelectObject(oldfont);
}

void COverlay::PutC3(SWord& x,SWord& y,int uChar)
{
	int	pageno = (uChar & 0x7f00) >> 7;
	int	index = uChar & 0xFF;

// handle English
	if (!(uChar & 0x8000))
	{
		switch (index&0xe0)
		{
		case 0x20:
		case 0x40:
		case 0x60:
			// 1st half
			index -= 0x20;
			break;
		case 0xa0:
		case 0xc0:
		case 0xe0:
			// 2nd half
			index -= 0xa0;
			pageno++;
			break;
		case 0x00:
		case 0x80:
			pageno = index = 0;
			uChar = ' ';
			break;
		}
	}
	else
	{
		switch (index&0xe0)
		{
		case 0x40:
		case 0x60:
		case 0x80:
			// 1st half
			index -= 0x40;
			break;
		case 0xa0:
		case 0xc0:
		case 0xe0:
			// 2nd half
			index -= 0xa0;
			pageno++;
			break;
		case 0x00:
		case 0x20:
			pageno = index = 0;
			uChar = ' ';
			break;
		}
	}

	ImageMapDesc* pmap =Image_Map.GetImageMapPtr(ImageMapNumber(FONTBASENO+pageno));
	//lo res version only displays upper case chars

	UByte tWidth=8;
	SWord this_y;

 	SWord ou,ov;
 	SWord cWidth,pWidth,cHeight,pHeight;

	this_y=y;

	ov = (index / 11);
	ou = index%11;
	ov *= 14;
	ou *= 11;
	ov += 1;
	ou += 1;

 	cHeight=14;

 	cWidth = pWidth=pmap->body[uChar & 0x7F];
	int failcode=pmap->alpha[uChar & 0x7F];
	if (failcode > 0x50)
		failcode=0;
	pHeight=cHeight;

	SWord oldTQ=pw->DoForceTQ(4);
	bool oldMip=pw->DoSetMipMap(false);

 	DoPointStruc dp[4];
 
 	dp[0].bodyx.f=Float(x);
 	dp[0].bodyy.f=Float(this_y);
 	dp[1].bodyx.f=Float(x+pWidth-1);
 	dp[1].bodyy.f=Float(this_y);
 	dp[2].bodyx.f=Float(x+pWidth-1);
 	dp[2].bodyy.f=Float(this_y+pHeight-1);
 	dp[3].bodyx.f=Float(x);
 	dp[3].bodyy.f=Float(this_y+pHeight-1);

	dp[0].ix=ou;
 	dp[0].iy=ov;
 	dp[1].ix=ou+cWidth-1;
 	dp[1].iy=ov;
 	dp[2].ix=ou+cWidth-1;
 	dp[2].iy=ov+cHeight-1;
 	dp[3].ix=ou;
 	dp[3].iy=ov+cHeight-1;
 
	if (Save_Data.fSoftware)	POLYGON.DoPutC(pmap,dp);
	else						pw->DoPutC(pmap,dp);
 
 	x+=pWidth;
 
 	if (x>=physicalWidth) x=0,y+=pHeight;
 	if (y>=physicalHeight) y=0;

	pw->DoForceTQ(oldTQ);
	pw->DoSetMipMap(oldMip);

	if (doneonce==0)
	{
		scanX=SWord(dp[0].bodyx.f);
		scanY=SWord(dp[2].bodyy.f);
		doneonce=1;
	}
}

void COverlay::PutC3Clipped(SWord& x,SWord& y,int uChar)
{
	int	pageno = (uChar & 0x7f) >> 7;
	int	index = uChar & 0xFF;

// handle English
	if (!(uChar & 0x8000))
	{
		switch (index&0xe0)
		{
		case 0x20:
		case 0x40:
		case 0x60:
			// 1st half
			index -= 0x20;
			break;
		case 0xa0:
		case 0xc0:
		case 0xe0:
			// 2nd half
			index -= 0xa0;
			pageno++;
			break;
		case 0x00:
		case 0x80:
			pageno = index = 0;
			uChar = ' ';
			break;
		}
	}
	else
	{
		switch (index&0xe0)
		{
		case 0x40:
		case 0x60:
		case 0x80:
			// 1st half
			index -= 0x40;
			break;
		case 0xa0:
		case 0xc0:
		case 0xe0:
			// 2nd half
			index -= 0xa0;
			pageno++;
			break;
		case 0x00:
		case 0x20:
			pageno = index = 0;
			uChar = ' ';
			break;
		}
	}

	ImageMapDesc* pmap =Image_Map.GetImageMapPtr(ImageMapNumber(FONTBASENO+pageno));
	//lo res version only displays upper case chars

	UByte tWidth=8;
	SWord this_y;

 	SWord ou,ov;
 	SWord cWidth,pWidth,cHeight,pHeight;

	this_y=y;

	ov = (index / 10);
	ou = index%10;
	ov *= 12;
	ou *= 12;
	ov += 4;
	ou += 4;


}
