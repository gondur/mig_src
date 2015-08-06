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

#include	"dosdefs.h"
#include	"stdio.h"
#define	F_COMMON
#define F_GRAFIX	
#include	"files.g"
#include	"fileman.h"
#include	"node.h"
#include	"makebf.h"
#include	"bfnumber.h"
#include	"persons2.h"
#define	QUICKQUICKQUICK
		#include	"..\mfc\resource.h"
		#include	"squick1.h"

typedef	 QuickFields	Q;
typedef	 QuickFields::QFD	QFD;
#define BLUE	0
#define	RED		1
int			CSQuick1::currquickmiss=-1;
QuickDef	CSQuick1::quickdef;

QuickDef	CSQuick1::quickmissions[]=
{


//-----------------------------------------------------------------------------
//Landing / Takeoff practice
	{
		IDS_QUICK_12,IDS_QUICK_12_DESC,
		{	
			{	{	{SQ_F86A,1,SKILL_VETERAN,FT_3000,IDS_UN_CAP,Q::QFD_LONE_PLAYER} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_11,0,0,
		{ IDS_AIRFIELD},
		{	{UID_AfBlKimpo,UID_AfBlTaegu,UID_AfBlPohang,UID_AfBlKunsan}
		},
		UID_AfBlKimpo
	},

//-----------------------------------------------------------------------------
//see the world test, travel 
//Free Flight
	{
		IDS_QUICK_10,IDS_QUICK_10_DESC,
		{	
			{	{	{SQ_F86A,1,SKILL_VETERAN,FT_5000,IDS_UN_CAP,Q::QFD_LONE_PLAYER} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_09,0,0,
		{ IDS_BRIDGE,IDS_AIRFIELD},
		{	{UID_BrRdInje,UID_BrRdChosan,UID_BrRlSinanju0,UID_BrRdUngig},
			{UID_AfBlSuwon,UID_AfRdAntung},
		},
		UID_BrRdInje
	},
//-----------------------------------------------------------------------------
//TURKEY SHOOT
	{
		IDS_QUICK_15,IDS_QUICK_15_DESC,
		{	
			{	{	{SQ_F86A,1,SKILL_ACE,FT_5000,IDS_UN_CAP,Q::QFD_LONE_PLAYER} }	},
			{	{	{SQ_MIG15,1,SKILL_NOVICE,FT_5000,IDS_RED_CAP,Q::QFD_LONE_MIG}	}	}
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_14,0,0,
		{ IDS_CIVILIAN},
		{	{UID_NODE_sinuiju,UID_StNamsanni,UID_StSinanju,UID_StHuichon},
		},
		UID_NODE_sinuiju
	},

//-----------------------------------------------------------------------------
//ONE ON ONE
	{	IDS_QUICK_14,IDS_QUICK_14_DESC,
//DEADCODE DAW 26/03/99 		IDS_CAS,IDS_CAS,
		{	
			{	{	{SQ_F86A,1,SKILL_ACE,FT_5000,IDS_UN_CAP,Q::QFD_LONE_PLAYER} }	},
			{	{	{SQ_MIG15,1,SKILL_ACE,FT_5000,IDS_RED_CAP,Q::QFD_LONE_MIG}	}	}
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_13,0,0,
		{ IDS_CIVILIAN},
		{	{UID_NODE_sinuiju,UID_StNamsanni,UID_StSinanju,UID_StHuichon},
//DeadCode MS 14Apr99 		{	{UID_AfRdSinuiju,UID_AfBlKimpo,UID_StKusong,UID_StSunchon},
//DeadCode MS 14Apr99 			{UID_StYangdok,UID_StPyongyang,UID_StSamdung,UID_BrRlHuichon},
//DeadCode MS 14Apr99 			{UID_StSingye,UID_StIchon,UID_StChangdo,UID_StKuri},
//DeadCode MS 14Apr99 			{UID_StHongchon,UID_StChomchon,UID_StKongju,UID_StKimchon},
		},
		UID_NODE_sinuiju
	},

//-----------------------------------------------------------------------------
//DOGFIGHT 1: No Advantage 
	{
		IDS_QUICK_3,IDS_QUICK_3_DESC,
		{	
			{	{	{SQ_F86A,1,SKILL_ACE,FT_20000,IDS_UN_CAP,Q::QFD_FIGHTER} }	},
			{	{	{SQ_MIG15,1,SKILL_ACE,FT_20000,IDS_RED_CAP,Q::QFD_MIG_PLAYER_AUTO}	}	}
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_02,0,0,
		{ IDS_CIVILIAN},
		{	{UID_NODE_sinuiju,UID_StNamsanni,UID_StChosan,UID_StChongju}
		},
		UID_NODE_sinuiju
	},

//-----------------------------------------------------------------------------
//DOGFIGHT 2: Random Advantage
	{
		IDS_QUICK_4,IDS_QUICK_4_DESC,
		{	
			{	{	{SQ_F86A,1,SKILL_ACE,FT_20000,IDS_UN_CAP,Q::QFD_FIGHTER} }	},
			{	{	{SQ_MIG15,1,SKILL_ACE,FT_20000,IDS_RED_CAP,Q::QFD_MIG_PLAYER_AUTO}	}	}
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_03,0,0,
		{ IDS_CIVILIAN},
		{	{UID_NODE_sinuiju,UID_StNamsanni,UID_StChosan,UID_StChongju}
		},
		UID_NODE_sinuiju
	},

//-----------------------------------------------------------------------------
//DOGFIGHT 3: Advantage UN
	{
		IDS_QUICK_5,IDS_QUICK_5_DESC,
		{	
			{	{	{SQ_F86A,1,SKILL_ACE,FT_10000,IDS_UN_CAP,Q::QFD_FIGHTER} }	},
			{	{	{SQ_MIG15,1,SKILL_ACE,FT_9000,IDS_RED_CAP,Q::QFD_MIG_PLAYER_AUTO}	}	}
		},
		BLUE,0,0,0 ,
		FIL_QUICKMISSION_04,0,0,
		{ IDS_CIVILIAN},
		{	{UID_NODE_sinuiju,UID_StNamsanni,UID_StChosan,UID_StChongju}
		},
		UID_NODE_sinuiju
	},

//-----------------------------------------------------------------------------
//DOGFIGHT 4: Advantage Reds
	{
		IDS_QUICK_6,IDS_QUICK_6_DESC,
		{	
			{	{	{SQ_F86A,1,SKILL_ACE,FT_30000,IDS_UN_CAP,Q::QFD_FIGHTER} }	},//MS 24May99
			{	{	{SQ_MIG15,1,SKILL_ACE,FT_30000+FT_1000,IDS_RED_CAP,Q::QFD_MIG_PLAYER_AUTO}	}	}//MS 24May99
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_05,0,0,
		{ IDS_CIVILIAN},
		{	{UID_NODE_sinuiju,UID_StNamsanni,UID_StChosan,UID_StChongju}
		},
		UID_NODE_sinuiju
	},

//-----------------------------------------------------------------------------
//MEDIUM BOMBER STRIKE
	{
		IDS_QUICK_2,IDS_QUICK_2_DESC,
		{
			{	{	{SQ_F80,2,SKILL_REGULAR,FT_6000,IDS_UN_FLAK_DUTY,Q::QFD_BOMBER_PLAYER_AUTO+Q::QFD_ALLOW_ZERO_FL}	},
				{	{SQ_B29,2,SKILL_REGULAR,FT_12000,IDS_UN_FB_STRIKE,Q::QFD_BOMBER_AUTO_ONLY},
					{SQ_F86A,2,SKILL_REGULAR,FT_16000,IDS_UN_ESCORT_DUTY,Q::QFD_FIGHTER+Q::QFD_ALLOW_ZERO_FL}
				}
			},
			{	{	{SQ_MIG15,2,SKILL_REGULAR,FT_16000,IDS_RED_CAP,Q::QFD_MIG_PLAYER_AUTO}	},		
				{	{SQ_MIG15,2,SKILL_REGULAR,FT_25000,IDS_RED_CAP,Q::QFD_MIG_PLAYER_AUTO+Q::QFD_ALLOW_ZERO_FL}	}	
			}
		},

		BLUE,1,1,0,
		FIL_QUICKMISSION_01,0,0,
		{ IDS_BRIDGE,IDS_SUPPLYPOINT,IDS_AIRFIELD	},
		{	{UID_BrRdYalu,UID_BrRlPyongyang,UID_BrRdChosan,UID_BrRlSinanju0},
			{UID_MyRdPyongyang,UID_MyBlMunsan,UID_SdRdSonchon,UID_WhRdSukchon},
			{UID_AfRdSinuiju,UID_AfRdPyongyangM,UID_AfRdSunan,UID_AfRdAnak}
		},
		UID_BrRdYalu
	},

//-----------------------------------------------------------------------------
//FIGHTER BOMBER STRIKE
	{	//	S	W	G
		IDS_L_QUICK_1,IDS_QUICK_1_DESC,
		{	{	{	{SQ_F80,2,SKILL_REGULAR,FT_6000,IDS_UN_FLAK_DUTY,Q::QFD_BOMBER_PLAYER_AUTO+Q::QFD_ALLOW_ZERO_FL	}	},
				{	{SQ_F84,2,SKILL_REGULAR,FT_12000,IDS_UN_FB_STRIKE,Q::QFD_BOMBER_PLAYER_AUTO},
					{SQ_F86A,2,SKILL_REGULAR,FT_16000,IDS_UN_ESCORT_DUTY,Q::QFD_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	
				}	
			},
			{	{	{SQ_MIG15,2,SKILL_REGULAR,FT_16000,IDS_RED_CAP,Q::QFD_MIG_PLAYER_AUTO}	},		
				{	{SQ_MIG15,2,SKILL_REGULAR,FT_25000,IDS_RED_CAP,Q::QFD_MIG_PLAYER_AUTO+Q::QFD_ALLOW_ZERO_FL}	}	
			}
		},

		BLUE,1,0,0,
		FIL_QUICKMISSION_00,0,0,
		{ IDS_AIRFIELD,IDS_SUPPLYPOINT,IDS_BRIDGE},
		{ 	{UID_AfRdSinuiju,UID_AfRdPyongyangM,UID_AfRdSunan,UID_AfRdAnak},	
			{UID_MyRdPyongyang,UID_MyBlMunsan,UID_SdRdSonchon,UID_WhRdSukchon},
			{UID_BrRdSinuiju,UID_BrRlPyongyang,UID_BrRdChosan,UID_BrRlSinanju0}
		},
		UID_AfRdPyongyangM	//UID_AfRdSinuiju
	},
//-----------------------------------------------------------------------------
//Fighter Bomber Strike 2
	{
		IDS_QUICK_17,IDS_QUICK_11_DESC,
		{	
			{	{	{SQ_F84,1,SKILL_VETERAN,FT_3000,IDS_UN_FB_STRIKE,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_16,0,0,
		{ IDS_SUPPLYPOINT,IDS_BRIDGE,IDS_AIRFIELD	},
		{	{UID_SdRdWonju,UID_MyBlMunsan,UID_SdRdSariwon,UID_MyRlWonsan,},//MS 31Aug99
			{UID_BrRlHan,UID_BrRlSeoul,UID_BrRdChuncheon0,UID_BrRlKapyong},//MS 31Aug99
			{UID_AfRdPyongyangD,UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdYongyu}
		},
		UID_SdRdWonju											//MS 31Aug99
	},


//-----------------------------------------------------------------------------
//AR: Road
	{
		IDS_QUICK_7,IDS_QUICK_7_DESC,
		{	
			{	{	{SQ_F51,1,SKILL_VETERAN,FT_3000,IDS_DUTY_RECCY,Q::QFD_BOMBER_PLAYER_AUTO} }},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_06,0,0,
		{ IDS_ROAD },
		{	{UID_StChuncheon}
		},
		UID_StChuncheon
	},

//-----------------------------------------------------------------------------
//AR: Rail
	{
		IDS_QUICK_8,IDS_QUICK_8_DESC,
		{	
			{	{	{SQ_F51,1,SKILL_VETERAN,FT_3000,IDS_DUTY_RECCY,Q::QFD_BOMBER_PLAYER_AUTO} }	}, //RDH 08/06/99 //RDH 08/06/99
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_07,0,0,
		{ IDS_RAIL },
		{	{UID_SdRdPyonggang}
		},
		UID_SdRdPyonggang
	},

//-----------------------------------------------------------------------------
//CAS: UN Defend at Seoul
	{
		IDS_QUICK_13,IDS_QUICK_13_DESC,
		{	
			{	{	{SQ_F51,1,SKILL_VETERAN,FT_3000,IDS_DUTY_CAS,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_12,0,0,
		{ IDS_CIVILIAN},
		{	{UID_MyBlSeoul},
		},
		UID_MyBlSeoul
	},
//-----------------------------------------------------------------------------
//CAS: UN attack Hoengsong
	{
		IDS_QUICK_16,IDS_QUICK_16_DESC,
		{	
			{	{	{SQ_F51,1,SKILL_VETERAN,FT_3000,IDS_DUTY_CAS,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_15,0,0,
		{ IDS_CIVILIAN},
		{	{UID_StHoensong},
		},
		UID_StHoensong
	},


//-----------------------------------------------------------------------------
// RED GROUND ATTACK
	{
		IDS_QUICK_9,IDS_QUICK_9_DESC,
		{	
			{	{	{SQ_F51,2,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_FIGHTER} }	},
			{	{	{SQ_YAK,4,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO} }	}
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_08,0,0,
		{IDS_AIRFIELD},
		{	{UID_AfBlTaegu,UID_AfBlPohang},
		},
		UID_AfBlTaegu
	},

//-----------------------------------------------------------------------------
//AFTER THIS POINT, ALL DEBUG, NOT FINAL VERSION
//-----------------------------------------------------------------------------
#ifndef NDEBUG

//-----------------------------------------------------------------------------

//test convoy node
	{
		IDS_QUICK_11,IDS_QUICK_11,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_10,0,0,
		{ IDS_CIVILIAN,IDS_CIVILIAN,IDS_CIVILIAN,IDS_CIVILIAN},
		{	{UID_StHoensong,UID_StWonsan,UID_StKusong,UID_StSunchon},
			{UID_StYangdok,UID_StPyongyang,UID_StSamdung,UID_BrRlHuichon},
			{UID_StSingye,UID_StIchon,UID_StChangdo,UID_StKuri},
			{UID_StHongchon,UID_StChomchon,UID_StKimchon,UID_StKimchon},//MS 02May99
		},
		UID_StHwangju
	},

//-----------------------------------------------------------------------------

//IAN 1
	{
		IDS_AIRFIELD,IDS_AIRFIELD,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_AfRdSinmak,UID_AfRdHwangju,UID_AfRdSinuiju,UID_AfRdAntung},
			{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdTaTung,UID_AfRdUiju},
			{UID_AfRdAnak,UID_AfRdSariwon,UID_AfRdYongyu,UID_AfRdSinanju},
			{UID_AfRdPyongni,UID_AfRdTaechon,UID_AfRdNamsi,UID_AfRdSaamcham},
		},
		UID_NODE_sinuiju
	},
//IAN 2
	{
		IDS_AIRFIELD,IDS_AIRFIELD,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_AfRdPyongyangE,UID_AfRdPyongyangM,UID_AfRdPyongyangD,UID_AfBlKimpo},
			{UID_AfBlSeoul,UID_AfBlChuncheon,UID_AfBlOsan,UID_AfBlSuwon},
			{UID_AfBlPyongtaek,UID_AfBlKunsan,UID_AfBlTaejon,UID_AfBlTaegu},
			{UID_AfBlTaeguW,UID_AfBlKangnung,UID_AfBlPohang,UID_StKimchon},
		},
		UID_NODE_sinuiju
	},
//AMANDA 1
	{
		IDS_CIVILIAN,IDS_CIVILIAN,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
			{	{UID_MyRlChongjin,UID_MSPKimchaek,UID_MSPKimchaek,UID_MyRdHamhung},
			{UID_StKowon,UID_MyRlWonsan,UID_StKumhwa,UID_StChorwon},
			{UID_SdRdPyonggang,UID_SdRdIchon,UID_SdRdKaesong,UID_StPyongsan},
			{UID_SdRdKumchon,UID_ICMPNampo,UID_MyRdPyongyang,UID_WhRdSukchon},
		},
		UID_NODE_sinuiju
	},
//AMANDA 2
	{
		IDS_TOWN,IDS_TOWN,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_StSunchon,UID_StKangdong,UID_StYangdok,UID_SdRdSonchon},
			{UID_SCCYomju,UID_WhRdDangDong,UID_SCCHuichon,UID_SCCChosan},
			{UID_SCCKangye,UID_SCCManpo,UID_SdRdYangyang,UID_MyBlMunsan},
			{UID_MyBlSeoul,UID_SdBlSuwon,UID_StInchon,UID_StOsan},
		},
		UID_NODE_sinuiju
	},
//AMANDA 3
	{
		IDS_CIVILIAN,IDS_CIVILIAN,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_SdBlPyongtaek,UID_StChonan,UID_MyBlChochiwon,UID_SdBlTaejon},
			{UID_MyBlKuri,UID_StChuncheon,UID_SdRdHongchon,UID_StHoensong},
			{UID_SdRdWonju,UID_StChungju,UID_StSamchok, UID_StYulchon},
			{UID_StKusong,UID_StChomchon,UID_StChongju,UID_StChongju},//MS 02May99
		},
		UID_NODE_sinuiju
	},
//AMANDA 4
	{
		IDS_TOWN,IDS_TOWN,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_StKujang,UID_StSariwon,UID_StYulLi,UID_StPungsan},
			{UID_StKangnung,UID_StHwachon,UID_StYangpyong,UID_StYonchon},
			{UID_StUijongbu,UID_StSongnam,UID_MyBlKuri,UID_StKuri},
			{UID_StSinanju,UID_StPukchong,UID_StKilchu,UID_StKimchon},
		},
		UID_NODE_sinuiju
	},
//AMANDA 5
	{
		IDS_CIVILIAN,IDS_CIVILIAN,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_StAndong,UID_StUisong,UID_StChechon,UID_StKanda},
			{UID_StPohang,UID_StSamdung,UID_StKumi,UID_StKoksan},
			{UID_StSingye,UID_StYonan,UID_StChangdo,UID_StKuri},
			{UID_StHongchon,UID_StChomchon,UID_StKimchon,UID_StKimchon},
		},
		UID_StAndong
	},
//general testing type stuff
	{
		IDS_UN_CAP,IDS_UN_CAP,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_18,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_StHoensong,UID_StWonsan,UID_StKusong,UID_StSunchon},
			{UID_StYangdok,UID_StPyongyang,UID_StSamdung,UID_BrRlHuichon},
			{UID_StSingye,UID_StIchon,UID_StChangdo,UID_StKuri},
			{UID_StHongchon,UID_StChomchon,UID_StKimchon,UID_StKimchon},//MS 02May99
		},
		UID_NODE_sinuiju
	},
//RICH 1
	{
		IDS_BRIDGE,IDS_BRIDGE,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_BrRdTanchon0,UID_BrRdTanchon1,UID_BrRdChosan,UID_BrRlManpo},
			{UID_BrRlYesong,UID_BrRlTokohig,UID_BrRdYalu,UID_BrRlYalu0},
			{UID_BrRdSinuiju,UID_BrRlSinuiju0,UID_BrRlNamdaechon,UID_BrRdUngig},
			{UID_BrRlNan,UID_BrRlHan,UID_BrRdInje,UID_BrRlPukhan0},
		},
		UID_NODE_sinuiju
	},
//RICH 2
	{
		IDS_CHOKE,IDS_CHOKE,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_BrRlImjin,UID_BrRlPuktaechon,UID_BrRlKumjinchon,UID_BrRlChonui},
			{UID_BrRlHuichon,UID_BrRdChuncheon0,UID_BrRdKilchu,UID_BrRlSeoul},
			{UID_BrRdSeoul0,UID_BrRlKowon,UID_BrRlHuichon,UID_BrRlKowon},
			{UID_BrRlTaeryong,UID_BrRlPyongyang,UID_BrRdPyongyang1,UID_BrRdPyongyang0},
		},
		UID_NODE_sinuiju
	},
//RICH 3
	{
		IDS_BRIDGE,IDS_BRIDGE,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_BrRdSinanju,UID_BrRlSinanju0,UID_BrRdTaeryong,UID_BrRlSinanju1},
			{UID_BrRlKapyong,UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1},
			{UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1},
			{UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1},
		},
		UID_NODE_sinuiju
	},
//RICH 4
	{
		IDS_CHOKE,IDS_CHOKE,
		{	
			{	{	{SQ_F80,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	},
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_17,0,0,
		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
		{	{UID_StHoensong,UID_StWonsan,UID_StKusong,UID_StSunchon},
			{UID_StYangdok,UID_StPyongyang,UID_StSamdung,UID_BrRlHuichon},
			{UID_StSingye,UID_StIchon,UID_StChangdo,UID_StKuri},
			{UID_StHongchon,UID_StChomchon,UID_StKimchon,UID_StKimchon},//MS 02May99
		},
		UID_NODE_sinuiju
	},
//DEATH MATCH TESTING
	{
		IDS_QUICK_6,IDS_QUICK_6,
		{	
			{	{	{SQ_F86A,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} },	
				{	{SQ_F86A,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} },	
				{	{SQ_F84,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} },	
				{	{SQ_F84,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} } },	
			{	{	{SQ_MIG15,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} },
				{	{SQ_MIG15,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} },
				{	{SQ_MIG15,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} },
				{	{SQ_MIG15,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_PLAYER_AUTO} }	}
		},
		BLUE,0,0,0,
		FIL_deathmatch1,0,0,
		{ IDS_CIVILIAN,IDS_SUPPLYPOINT,IDS_AIRFIELD},
		{	{UID_NODE_sinuiju,UID_StSinanju,UID_StSuihu,UID_StChosan},
			{UID_MyRdPyongyang,UID_MyBlMunsan,UID_SdRdSonchon,UID_WhRdSukchon},
			{UID_AfRdSinuiju,UID_AfRdPyongyangM,UID_AfRdUiju,UID_StSamchok},
		},
		UID_NODE_sinuiju
	},
#endif
	{NULL}				//terminator!!!!!!!!!!!
};
void	QuickDef::MakeDeathMatchMission(int index)
{
	currmissnum = FIL_deathmatch0 + index;

}
void	QuickDef::MakeTeamPlayMission(int index)
{
	currmissnum = FIL_teamplay0 + index;


}
void	QuickDef::UpdateAcType()
{
	int i = 0, wave;
	int bluewave = -1;
	int redwave = -1;
	int side;
//	while	(		(i < _DPlay.CurrPlayers)
	while	(		(i < MAXPLAYERS)
			)
	{
		if (		(_DPlay.GameType == DEATHMATCH)
				||	(DPlay::H2H_Player[i].squadron < SQ_B_NONFLYABLE)
			)
		{
			side = 0;
			bluewave++;
			wave = bluewave;
		}else
		{
			side = 1;
			redwave++;
			wave = redwave;
		}
		CSQuick1::quickdef.line[side][wave][0].duty = 0;
		CSQuick1::quickdef.line[side][wave][0].flights = 1;
		CSQuick1::quickdef.line[side][wave][0].actype = DPlay::H2H_Player[i].squadron;
		for (int grp=1;grp<3;grp++)
		{
			CSQuick1::quickdef.line[side][wave][grp].duty = 0;
			CSQuick1::quickdef.line[side][wave][grp].flights = 0;
			CSQuick1::quickdef.line[side][wave][grp].actype = 0;
		}
		i++;	
	}	
	int startwave;
	for (side = 0; side < 2; side++)
	{
		if (side == 0)
		{
			bluewave++;
			startwave = bluewave;
		}else
		{
			redwave++;
			startwave = redwave;
		}
		for (startwave;wave<8;wave++)
		{
			for (int grp=0;grp<3;grp++)
			{
				CSQuick1::quickdef.line[side][wave][grp].duty = 0;
				CSQuick1::quickdef.line[side][wave][grp].flights = 0;
				CSQuick1::quickdef.line[side][wave][grp].actype = 0;
			}
		}
	}
}
