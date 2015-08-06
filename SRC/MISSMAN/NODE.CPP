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
//Filename	node.cpp
//System
//Author	 R. Hyde
//Date		Wed 19 Feb 1997
//Description
//------------------------------------------------------------------------------
//jobs:
//
//
//
//
#include	"dosdefs.h"
#include	"files.g"
#include	"worldinc.h"
#include	"node.h"
#include	"..\mfc\resource.h"
enum	{DAYS0 = 0};
#define	T SupplyTree

//Examples:
//T_Advance01_H											UN move north to new line
//T_AttackWest01_H										UN launch offensive
//IDS_T_DefendWest01_H									IX CORPS MAKES FINAL STAND
//IDS_T_Retreat02_H										Allies pull back
//

SupplyFightFiles	  
T::DummyBlank	={0},
//TempCode JIM 13May99 T::F_W1_RED,	  
//TempCode JIM 13May99 T::F_W1_UN,	  
T::F_C1_RED		={1,FIL_1_C1_RED,FIL_BAT_C1_RED,	Debrief::T_AttackWest02_H,0,METRES1000},	  //special case...
T::F_C1_UN		={1,FIL_1_C1_UN,FIL_BAT_C1_UN,		Debrief::T_DefendWest02_H,0,METRES1000},

T::F_W2_RED		={2,FIL_1_W2_RED,FIL_BAT_W2_RED,	Debrief::T_AttackWest01_H,Debrief::T_Advance01_H,METRES500},
T::F_W2_UN		={2,FIL_1_W2_UN,FIL_BAT_W2_UN,		Debrief::T_DefendWest01_H,Debrief::T_Retreat01_H,METRES500},
T::F_C2_RED		={2,FIL_1_C2_RED,FIL_BAT_C2_RED,	Debrief::T_AttackCntr01_H,Debrief::T_Advance01_H,METRES1000},
T::F_C2_UN		={2,FIL_1_C2_UN,FIL_BAT_C2_UN,		Debrief::T_DefendCntr01_H,Debrief::T_Retreat01_H,METRES1000},

T::F_W3_RED		={3,FIL_1_W3_RED,FIL_BAT_W3_RED,	Debrief::T_AttackWest02_H,Debrief::T_Advance02_H,METRES500},
T::F_W3_UN		={3,FIL_1_W3_UN,FIL_BAT_W3_UN,		Debrief::T_DefendWest02_H,Debrief::T_Retreat02_H,METRES500},
T::F_C3_RED		={3,FIL_1_C3_RED,FIL_BAT_C3_RED,	Debrief::T_AttackCntr02_H,Debrief::T_Advance02_H,METRES1000},
T::F_C3_UN		={3,FIL_1_C3_UN,FIL_BAT_C3_UN,		Debrief::T_DefendCntr02_H,Debrief::T_Retreat02_H,METRES1000},

T::F_W4_RED		={4,FIL_1_W4_RED,FIL_BAT_W4_RED,	Debrief::T_AttackWest03_H,Debrief::T_Advance03_H,METRES500},
T::F_W4_UN		={4,FIL_1_W4_UN,FIL_BAT_W4_UN,		Debrief::T_DefendWest03_H,Debrief::T_Retreat03_H,METRES500},
T::F_C4_RED		={4,FIL_1_C4_RED,FIL_BAT_C4_RED,	Debrief::T_AttackCntr03_H,Debrief::T_Advance03_H,METRES1000},
T::F_C4_UN		={4,FIL_1_C4_UN,FIL_BAT_C4_UN,		Debrief::T_DefendCntr03_H,Debrief::T_Retreat03_H,METRES1000},
													
T::F_W5_RED		={5,FIL_1_W5_RED,FIL_BAT_W5_RED,	Debrief::T_AttackWest04_H,Debrief::T_Advance04_H,METRES500},
T::F_W5_UN		={5,FIL_1_W5_UN,FIL_BAT_W5_UN,		Debrief::T_DefendWest04_H,Debrief::T_Retreat01_H,METRES500},
T::F_C5_RED		={5,FIL_1_C5_RED,FIL_BAT_C5_RED,	Debrief::T_AttackCntr04_H,Debrief::T_Advance04_H,METRES1000},
T::F_C5_UN		={5,FIL_1_C5_UN,FIL_BAT_C5_UN,		Debrief::T_DefendCntr04_H,Debrief::T_Retreat01_H,METRES1000},

T::F_W6_RED		={6,FIL_1_W6_RED,FIL_BAT_W6_RED,	Debrief::T_AttackWest05_H,Debrief::T_Advance05_H,METRES500},
T::F_W6_UN		={6,FIL_1_W6_UN,FIL_BAT_W6_UN,		Debrief::T_DefendWest05_H,Debrief::T_Retreat02_H,METRES500},
T::F_C6_RED		={6,FIL_1_C6_RED,FIL_BAT_C6_RED,	Debrief::T_AttackCntr05_H,Debrief::T_Advance05_H,METRES1000},
T::F_C6_UN		={6,FIL_1_C6_UN,FIL_BAT_C6_UN,		Debrief::T_DefendCntr05_H,Debrief::T_Retreat02_H,METRES1000},

T::F_W7_RED		={7,FIL_1_W7_RED,FIL_BAT_W7_RED,	Debrief::T_AttackWest06_H,Debrief::T_Retreat03_H,METRES500},
T::F_W7_UN		={7,FIL_1_W7_UN,FIL_BAT_W7_UN,		Debrief::T_DefendWest06_H,0,METRES500},
T::F_C7_RED		={7,FIL_1_C7_RED,FIL_BAT_C7_RED,	Debrief::T_AttackCntr06_H,Debrief::T_Retreat03_H,METRES1000},
T::F_C7_UN		={7,FIL_1_C7_UN,FIL_BAT_C7_UN,		Debrief::T_DefendCntr06_H,0,METRES1000}; 	//end of game...
//TempCode JIM 13May99 T::F_C7_RED,
//TempCode JIM 13May99 T::F_C7_UN,







SupplyNode*const	T::FirstNode=&N0_0_Dangdong;
SupplyNode
//this must be the first node
T::N0_0_Dangdong =	{
			/*nextnode*/		&N0_1_Sinuiju,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdUiju},//MS 18Jun99
			/*associated_item*/	UID_NODE_AnTung, //UID_WhRdDangDong,//MS 16May99
			/*associated_town*/	UID_Null,	//UID_StDangDong,	//MS 16May99
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_MAXSUPPLY,
			/*maxstores*/		STORES_MAXSUPPLY,
			/*route[3]*/		{NULL},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_0_1Rail0,				//wrong&R0_0_1Rail
				},
T::N0_1_Sinuiju =	{
			/*nextnode*/		&N0_2_Yomju,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdAntung,UID_AfRdTaTung},//MS 18Jun99
			/*associated_item*/	UID_WhRdSinuiju,
			/*associated_town*/	UID_NODE_sinuiju,
			/*associated_text*/	IDS_TARG_WhRdSinuiju,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R0_0_1Rail0},					//wrong{&R0_0_1Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_1_2Rail0,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Sinuiju,
			/*repairrate*/		0,								//MS 25May99
			/*maxstores*/		0,								//MS 25May99
			/*attacks*/			{0,0,0,0,0,0,255}				//MS 25May99
				},
T::N0_2_Yomju =	{
			/*nextnode*/		&N0_3_Sonchon,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdUiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_SCCYomju,
			/*associated_town*/	UID_StYomju,
			/*associated_text*/	IDS_TARG_SCCYomju,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_1_2Rail0},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_2_3Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YOMJU,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 25May99
			/*attacks*/			{0,0,0,0,0,0,255}				//MS 25May99
				},
T::N0_3_Sonchon =	{
			/*nextnode*/		&N0_4_Chongju,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdUiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_SdRdSonchon,
			/*associated_town*/	UID_StSonchon,
			/*associated_text*/	IDS_TARG_SdRdSonchon,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_2_3Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_3_4Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SONCHON,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 25May99
			/*attacks*/			{0,0,0,0,0,0,64}				//MS 25May99
				},
T::N0_4_Chongju =	{
			/*nextnode*/		&N0_4b_Maenjungdong,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSinuiju},//MS 18Jun99
			/*associated_item*/	UID_StChongju,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_3_4Rail,&R0_48_4Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_4_4bRail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHONGJU,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 25May99
			/*attacks*/			{0,0,0,0,0,0,32}				//MS 25May99
				},
T::N0_4b_Maenjungdong =	{
			/*nextnode*/		&N0_57_Suiho,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdTaechon,UID_AfRdNamsi},//MS 18Jun99
			/*associated_item*/	UID_StMaenjungdong,				//MS 26Oct98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_4_4bRail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_4b_5Rail0,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Maenjungdong,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 25May99
			/*attacks*/			{0,0,0,0,0,0,16}				//MS 25May99
				},
T::N0_57_Suiho =	{
			/*nextnode*/		&N0_46_Chongsongup,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_StSuihu,					//MS 02May99
			/*associated_town*/	UID_NULL,						//MS 02May99
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_0_57Rail},	//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_57_46Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Suiho,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_46_Chongsongup =	{
			/*nextnode*/		&N0_48_Kusong,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_StChongsongup,//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_57_46Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_46_48Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Chongsongup,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
						},
T::N0_48_Kusong =	{
			/*nextnode*/		&N0_44_Namsanni,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},//MS 18Jun99
			/*associated_item*/	UID_StKusong,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_46_48Road,&R0_45_48Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_48_4Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KUSONG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_44_Namsanni =	{
			/*nextnode*/		&N0_45_Sakchu,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_StNamsanni,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_0_44Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_44_45Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_NAMSANNI,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_45_Sakchu =	{
			/*nextnode*/		&N0_60_Chosan,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdTaechon,UID_AfRdSinanju},//MS 18Jun99
			/*associated_item*/	UID_SCCSakchu,
			/*associated_town*/	UID_Sakchu,						//MS 02May99
			/*associated_text*/	IDS_TARG_SCCSakchu,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_44_45Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_45_48Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SAKCHU,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_60_Chosan =	{
			/*nextnode*/		&N0_59_Chosin,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_SCCChosan,
			/*associated_town*/	UID_StChosan,
			/*associated_text*/	IDS_TARG_SCCChosan,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R0_8_60Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_60_11Road,			//SORTED, actually 60_10
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHOSAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_59_Chosin =	{
			/*nextnode*/		&N0_51_Pungsan,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_StChosin,					//MS 02May99
			/*associated_town*/	UID_NULL,						//MS 02May99
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_9_59Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_59_19Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Chosin,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_51_Pungsan =	{
			/*nextnode*/		&N0_33_Kapsan,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_SdRdPungsan,				//MS 22Feb99
			/*associated_town*/	UID_StPungsan,					//MS 22Feb99
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_9_51Road,&R0_33_51Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_51_37Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_PUNGSAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_33_Kapsan =	{
			/*nextnode*/		&N0_32_Hyesan,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_StKapsan,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_32_33Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_33_51Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KAPSAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_32_Hyesan =	{
			/*nextnode*/		&N0_5_Sinaju,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_StHyesan,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R0_16_32Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_32_33Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_HYESAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_5_Sinaju =	{
			/*nextnode*/		&China_E,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdTaechon},//MS 18Jun99
			/*associated_item*/	UID_StSinanju,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_4b_5Rail0,&R0_11_5Rail},					//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_5_6Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SINAJU,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 25May99
			/*attacks*/			{0,0,0,0,0,0,128}				//MS 25May99
				},

//THIS IS FIRST NODE ON EASTERN MSR

T::China_E =	{
			/*nextnode*/		&N0_16_Chongjin,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_SdChina_E,
			/*associated_town*/	UID_Null,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_MAXSUPPLY,
			/*maxstores*/		STORES_MAXSUPPLY,
			/*route[3]*/		{NULL},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_C_16Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHONGJIN,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,192}				//MS 28May99
				},

T::N0_16_Chongjin =	{
			/*nextnode*/		&N0_56_Kyongsong,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_MyRlChongjin,
			/*associated_town*/	UID_StChongjin,
			/*associated_text*/	IDS_TARG_MyRlChongjin,
			/*currentstores*/	STORES_MAXSUPPLY,
			/*maxstores*/		STORES_MAXSUPPLY,
			/*route[3]*/		{&R0_C_16Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_16_56Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHONGJIN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_56_Kyongsong =	{
			/*nextnode*/		&N0_17_Kilchu,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_StKyongsong,//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_16_56Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_56_17Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KYONGSON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_17_Kilchu =	{
			/*nextnode*/		&N0_18_Kimchaek,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_StKilchu,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_56_17Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_17_18Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KILCHU,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_18_Kimchaek =	{
			/*nextnode*/		&N0_50_Tanchon,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_MSPKimchaek,
			/*associated_town*/	UID_StKimchaek,
			/*associated_text*/	IDS_TARG_MSPKimchaek,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_17_18Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_18_50Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KIMCHAEK,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_50_Tanchon =	{
			/*nextnode*/		&N0_37_Pukchong,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_MSPTanchon,
			/*associated_town*/	UID_StTanchon,					//MS 22Feb99
			/*associated_text*/	IDS_TARG_MSPTanchon,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R0_18_50Rail,&R0_51_50Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_50_37Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_TANCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_37_Pukchong =	{
			/*nextnode*/		&N0_19_Hamhung,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdTaechon,UID_AfRdNamsi},//MS 18Jun99
			/*associated_item*/	UID_StPukchong,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_50_37Rail,&R0_51_37Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_37_19Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_PUKCHONG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_19_Hamhung =	{
			/*nextnode*/		&China_C,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdTaechon,UID_AfRdNamsi},//MS 18Jun99
			/*associated_item*/	UID_MyRdHamhung,
			/*associated_town*/	UID_StHamhung,
			/*associated_text*/	IDS_TARG_MyRdHamhung,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R0_37_19Rail,&R0_59_19Road,&R0_11_19Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_19_34Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_HAMHUNG,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,128}				//MS 28May99
				},
//CENTRAL FIRST NODE

T::China_C =	{
			/*nextnode*/		&N0_8_Manpo,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuiju,UID_AfRdUiju},//MS 18Jun99
			/*associated_item*/	UID_SdChina_C,
			/*associated_town*/	UID_Null,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_MAXSUPPLY,
			/*maxstores*/		STORES_MAXSUPPLY,
			/*route[3]*/		{NULL},				//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_C_8Rail,					//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_MANPO,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},

T::N0_8_Manpo =	{
			/*nextnode*/		&N0_9_Kangye,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_SCCManpo,
			/*associated_town*/	UID_StManpo,
			/*associated_text*/	IDS_TARG_SCCManpo,
			/*currentstores*/	STORES_MAXSUPPLY,
			/*maxstores*/		STORES_MAXSUPPLY,
			/*route[3]*/		{&R0_C_8Rail},				//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_8_9Rail,					//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_MANPO,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_9_Kangye =	{
			/*nextnode*/		&N0_10_Huichon,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdUiju,UID_AfRdSinuiju,UID_AfRdAntung},//MS 18Jun99
			/*associated_item*/	UID_SCCKangye,
			/*associated_town*/	UID_StKangye,
			/*associated_text*/	IDS_TARG_SCCKangye,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_8_9Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_9_10Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KANGYE,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
//T::N0_58_SinmiDo =	{
//			/*nextnode*/		&N0_10_Huichon,
//			/*supplyline*/		&WestRoute,
//			/*type*/			NOCONTEST,
//			/*status*/			BEHINDREDLINES,
//			/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},//MS 18Jun99
//			/*associated_item*/	UID_FCSinmiDo,
//			/*associated_town*/	UID_FCSinmiDo,
//			/*associated_text*/	IDS_NOINFO,
//			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
//			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
//			/*route[3]*/		{&R0_3_58Road},
//			/*redfrontBF*/		{FIL_NULL},
//			/*bluefrontBF*/		{FIL_NULL},
//			/*forward*/			&R0_3_58Road,
//			/*priority*/		SP_NONE,
//			/*serviced*/		FALSE,
//			/*populate*/		FIL_1_SinmiDo,
//				},
T::N0_10_Huichon =	{
			/*nextnode*/		&N0_11_Kujang,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},//MS 18Jun99
			/*associated_item*/	UID_SCCHuichon,
			/*associated_town*/	UID_StHuichon,					//MS 22Feb99
			/*associated_text*/	IDS_TARG_SCCHuichon,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_9_10Rail,&R0_60_11Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_10_11Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_HUICHON,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,16}				//MS 28May99
				},
T::N0_11_Kujang =	{
			/*nextnode*/		&N0_31_Tokchon,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},//MS 18Jun99
			/*associated_item*/	UID_StKujang,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_10_11Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_11_12Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KUJANG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N0_31_Tokchon =	{
			/*nextnode*/		&N1_6_Sukchon,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdTaechon},//MS 18Jun99
			/*associated_item*/	UID_StTokchon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,		//MS 20Jan99
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,		//MS 20Jan99
			/*route[3]*/		{&R0_11_31Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R0_31_29Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_TOKCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
//------------------------------------------------------------------------------
//supply nodes for area 1
T::N1_6_Sukchon =	{
			/*nextnode*/		&N1_29_Kangdong,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdYongyu,UID_AfRdPyongni},//MS 18Jun99
			/*associated_item*/	UID_WhRdSukchon,
			/*associated_town*/	UID_StSukchon,
			/*associated_text*/	IDS_TARG_WhRdSukchon,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R0_5_6Rail},	//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_6_7Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SUKCHON,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,32}				//MS 28May99
				},
T::N1_29_Kangdong =	{
			/*nextnode*/		&N1_54_YulLi,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdSunan},//MS 18Jun99
			/*associated_item*/	UID_StKangdong,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_12_29Rail,&R0_31_29Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_29_13Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KANGDONG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_54_YulLi =	{
			/*nextnode*/		&N1_7_Pyongyang,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdPyongni},//MS 18Jun99
			/*associated_item*/	UID_SdRdYulLi,					//MS 22Feb99
			/*associated_town*/	UID_StYulLi,					//MS 22Feb99
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_13_54Rail,&R1_64_54Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_63_54Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YULLI,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_7_Pyongyang =	{
			/*nextnode*/		&N1_30_Nampo,
			/*supplyline*/		&WestRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdPyongyangM,UID_AfRdYongyu},//MS 18Jun99
			/*associated_item*/	UID_MyRdPyongyang,
			/*associated_town*/	UID_StPyongyang,
			/*associated_text*/	IDS_TARG_MyRdPyongyang,
			/*currentstores*/	STORES_INITALVERYBIGSETTLEMENT,
			/*maxstores*/		STORES_INITALVERYBIGSETTLEMENT,
			/*route[3]*/		{&R1_6_7Rail,&R1_12_7Rail},
			/*redfrontBF*/		{FIL_1_W7_RED,&F_W7_RED},
			/*bluefrontBF*/		{FIL_1_W7_UN,&F_W7_UN},
			/*forward*/			&R1_7_49Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_PYONGYAN,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,192}				//MS 28May99
				},
T::N1_30_Nampo =	{
			/*nextnode*/		&N1_49_Hwangju,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangD,UID_AfRdSunan,UID_AfRdPyongyangE},//MS 18Jun99
			/*associated_item*/	UID_ICMPNampo,
			/*associated_town*/	UID_StNampo,
			/*associated_text*/	IDS_TARG_ICMPNampo,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R1_7_30Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_30_62Road,	//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_NAMPO,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_49_Hwangju =	{
			/*nextnode*/		&N1_41_Ichon,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdHwangju,UID_AfRdPyongyangD,UID_AfRdPyongyangE},//MS 18Jun99
			/*associated_item*/	UID_StHwangju,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_7_49Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_49_22Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_HWANGJU,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_41_Ichon =	{
			/*nextnode*/		&N1_22_Sariwon,
			/*supplyline*/		&CentralRoute,	//SORTED
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdHwangju,UID_AfRdPyongyangE},//MS 18Jun99
			/*associated_item*/	UID_SdRdIchon,
			/*associated_town*/	UID_StIchon,
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R1_66_41Road,&R1_25_41Road},	//MS 21Jun99
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_41_28Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_ICHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_22_Sariwon =	{
			/*nextnode*/		&N1_25_Pyongsan,
			/*supplyline*/		&WestRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdHwangju,UID_AfRdAnak},//MS 18Jun99
			/*associated_item*/	UID_SdRdSariwon,				//MS 22Feb99
			/*associated_town*/	UID_StSariwon,					//MS 22Feb99
			/*associated_text*/	IDS_TARG_SdRdSariwon,				//MS 22Feb99
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_49_22Rail,&R1_65_22Road,&R_Fake06},//MS 09Jun99
			/*redfrontBF*/		{FIL_1_W6_RED,&F_W6_RED},
			/*bluefrontBF*/		{FIL_1_W6_UN,&F_W6_UN},
			/*forward*/			&R1_22_25Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SARIWON,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,128}				//MS 28May99
				},
T::N1_25_Pyongsan =	{
			/*nextnode*/		&N1_26_Kumchon,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdHwangju,UID_AfRdSariwon},//MS 18Jun99
			/*associated_item*/	UID_StPyongsan,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R1_22_25Rail,&R1_25_63Road,&R1_25_66Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_25_26Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_PYONGSAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_26_Kumchon =	{
			/*nextnode*/		&N1_62_Chaeryong,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdHwangju,UID_AfRdSariwon},//MS 18Jun99
			/*associated_item*/	UID_SdRdKumchon,
			/*associated_town*/	UID_StKumchon,
			/*associated_text*/	IDS_TARG_SdRdKumchon,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_25_26Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_26_27Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KUMCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_62_Chaeryong =	{
			/*nextnode*/		&N1_24_Haeju,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdHwangju,UID_AfRdSariwon,UID_AfRdAnak},//MS 18Jun99
			/*associated_item*/	UID_StChaeryong,//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_22_62Rail,&R1_30_62Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_62_24Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHAERYON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_24_Haeju =	{
			/*nextnode*/		&N1_61_Yonan,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdSinmak},//MS 18Jun99
			/*associated_item*/	UID_StHaeju,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_62_24Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_24_61Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_HAEJU,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_61_Yonan =	{
			/*nextnode*/		&N1_69_Kalmal,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdSinmak},//MS 18Jun99
			/*associated_item*/	UID_StYonan,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_24_61Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_61_27Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YONAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_69_Kalmal =	{
			/*nextnode*/		&N1_27_Kaesong,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfBlSeoul,UID_AfBlKimpo},//MS 18Jun99
			/*associated_item*/	UID_StKalmal,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_38_69Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_69_49Road, //SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Kalmal,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,32}				//MS 28May99
				},
T::N1_27_Kaesong =	{
			/*nextnode*/		&N1_34_Yonghung,
			/*supplyline*/		&WestRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfBlSeoul,UID_AfBlKimpo},//MS 18Jun99
			/*associated_item*/	UID_SdRdKaesong,
			/*associated_town*/	UID_StKaesong,
			/*associated_text*/	IDS_TARG_SdRdKaesong,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_26_27Rail,&R1_61_27Rail,&R_Fake04},//MS 08Jun99
			/*redfrontBF*/		{FIL_1_W5_RED,&F_W5_RED},
			/*bluefrontBF*/		{FIL_1_W5_UN,&F_W5_UN},
			/*forward*/			&R1_27_75Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KAESONG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_34_Yonghung =	{
			/*nextnode*/		&N1_12_Sunchon,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongni,UID_AfRdKangdong,UID_AfRdSinanju},//MS 18Jun99
			/*associated_item*/	UID_StYonghung,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_19_34Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_34_20Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YONGHUNG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_12_Sunchon =	{
			/*nextnode*/		&N1_20_Kowon,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdPyongni,UID_AfRdKangdong},//MS 18Jun99
			/*associated_item*/	UID_StSunchon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R0_11_12Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_12_29Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SUNCHON,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,32}				//MS 28May99
				},
T::N1_20_Kowon =	{
			/*nextnode*/		&N1_21_Wonsan,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdPyongni,UID_AfRdKangdong},//MS 18Jun99
			/*associated_item*/	UID_StKowon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_34_20Rail},	//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_20_21Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KOWON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_21_Wonsan =	{
			/*nextnode*/		&N1_52_Kojo,
			/*supplyline*/		&EastRoute,
			/*type*/			BATTLEFIELD,					//MS 08Jun99
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdPyongyangE},//MS 18Jun99
			/*associated_item*/	UID_MyRlWonsan,
			/*associated_town*/	UID_StWonsan,
			/*associated_text*/	IDS_TARG_MyRlWonsan,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R1_20_21Rail,&R1_55_21Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_21_52Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_WONSAN,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,128}				//MS 28May99
				},
T::N1_52_Kojo =	{
			/*nextnode*/		&N1_35_Kojin,
			/*supplyline*/		&EastRoute,
			/*type*/			BATTLEFIELD,					//MS 09Jun99
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdKangdong,UID_AfRdPyongni},//MS 18Jun99
			/*associated_item*/	UID_StKojo,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_21_52Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_52_35Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KOJO,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_35_Kojin	=	{
			/*nextnode*/		&N1_64_Sangwon,
			/*supplyline*/		&EastRoute,
			/*type*/			BATTLEFIELD,					//MS 06Jun99
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfBlChuncheon,UID_AfRdKangdong},//MS 18Jun99
			/*associated_item*/	UID_StKojin,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_52_35Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_35_42Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Kojin,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_64_Sangwon	=	{
			/*nextnode*/		&N1_65_Nuang,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdSunan},//MS 18Jun99
			/*associated_item*/	UID_StSangwon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R1_7_64Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_64_54Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SANGWON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_65_Nuang	=	{
			/*nextnode*/		&N1_63_Suan,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdHwangju,UID_AfRdSariwon,UID_AfRdSinmak},//MS 18Jun99
			/*associated_item*/	UID_StNuang,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R1_54_65Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_65_22Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Nuang,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_63_Suan	=	{
			/*nextnode*/		&N1_66_Singye,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdPyongyangE,UID_AfRdPyongyangM},//MS 18Jun99
			/*associated_item*/	UID_StSuan,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R1_63_54Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_63_66Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SUAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_66_Singye	=	{
			/*nextnode*/		&N1_42_Kansang,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdHwangju,UID_AfRdSariwon},//MS 18Jun99
			/*associated_item*/	UID_StSingye,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R1_63_66Road,&R1_66_53Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_66_41Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SINGYE,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_42_Kansang =	{
			/*nextnode*/		&N1_70_Hwachon,
			/*supplyline*/		&EastRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlChuncheon,UID_AfRdSinmak,UID_AfRdPyongyangE},//MS 18Jun99
			/*associated_item*/	UID_StKansang,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_35_42Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_42_36Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KANSANG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_70_Hwachon =	{
			/*nextnode*/		&N1_68_Changdo,
			/*supplyline*/		&CentralRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlChuncheon,UID_AfBlSeoul,UID_AfBlKimpo},//MS 18Jun99
			/*associated_item*/	UID_StHwachon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_38_70Road,&R_Fake03},		//MS 08Jun99
			/*redfrontBF*/		{FIL_1_C5_RED,&F_C5_RED},
			/*bluefrontBF*/		{FIL_1_C5_UN,&F_C5_UN},
			/*forward*/			&R1_70_12Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_HWACHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},

T::N1_68_Changdo =	{
			/*nextnode*/		&N1_53_Koksan,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlChuncheon,UID_AfBlSeoul,UID_AfBlKimpo},//MS 18Jun99
			/*associated_item*/	UID_StChangdo,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R1_40_68Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_68_38Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Changdo,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N1_53_Koksan =	{
			/*nextnode*/		&N1_40_Hoeyang,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdKangdong,UID_AfRdPyongyangE},//MS 18Jun99
			/*associated_item*/	UID_StKoksan,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_15_53Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_66_53Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KOKSAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_40_Hoeyang =	{
			/*nextnode*/		&N1_38_Kumhwa,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdKangdong,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_StHoeyang,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_39_40Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_40_68Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_HOEYANG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_38_Kumhwa =	{
			/*nextnode*/		&N1_36_Yangyang,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdHwangju,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_SdRdKumhwa,					//MS 22Feb99
			/*associated_town*/	UID_StKumhwa,					//MS 22Feb99
			/*associated_text*/	IDS_TARG_SdRdKumhwa,					//MS 22Feb99
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_28_38Road,&R1_68_38Road},//MS 18Jun99
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
//DeadCode MS 18Jun99 			/*forward*/			&R1_38_12Road,
			/*forward*/			&R1_38_70Road,					//MS 18Jun99
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KUMHWA,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 25May99
			/*attacks*/			{0,0,0,0,0,0,64}				//MS 25May99
				},
T::N1_36_Yangyang =	{
			/*nextnode*/		&N1_13_Samdung,
			/*supplyline*/		&EastRoute,
			/*type*/			BATTLEFIELD,					//MS 08Jun99
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlChuncheon,UID_AfBlSeoul,UID_AfBlKangnung},//MS 18Jun99
			/*associated_item*/	UID_SdRdYangyang,					//MS 20Jan99
			/*associated_town*/	UID_StYangyang,	//UID_NULL,		//MS 20Jan99
			/*associated_text*/	IDS_TARG_SdRdYangyang,					//MS 20Jan99
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_42_36Rail,&R1_71_36Road},		//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_36_29Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YANGYANG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_13_Samdung =	{
			/*nextnode*/		&N1_14_WaDong,
			/*supplyline*/		&CentralRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdPyongni},//MS 18Jun99
			/*associated_item*/	UID_StSamdung,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_29_13Rail},
			/*redfrontBF*/		{FIL_1_C7_RED,&F_C7_RED},
			/*bluefrontBF*/		{FIL_1_C7_UN,&F_C7_UN},
			/*forward*/			&R1_13_54Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SAMDUNG,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 25May99
			/*attacks*/			{0,0,0,0,0,0,128}				//MS 25May99
				},


//MAY HAVE TO TAKE WADONG OUT
T::N1_14_WaDong	=	{
			/*nextnode*/		&N1_15_Yangdok,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongni,UID_AfRdKangdong,UID_AfRdPyongyangE},//MS 18Jun99
			/*associated_item*/	UID_StWaDong,
			/*associated_town*/	UID_Null,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_29_14Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_14_15Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_WaDong,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,64}				//MS 28May99
				},
T::N1_15_Yangdok	=	{
			/*nextnode*/		&N1_39_Kosan,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongni,UID_AfRdKangdong,UID_AfRdPyongyangE},//MS 18Jun99
			/*associated_item*/	UID_SdRdYangdok,				//MS 22Feb99
			/*associated_town*/	UID_StYangdok,					//MS 22Feb99
			/*associated_text*/	IDS_TARG_SdRdYangdok,				//MS 22Feb99
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_14_15Rail,&R1_15_20Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_15_53Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YANGDOK,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,255}				//MS 28May99
				},
T::N1_39_Kosan	=	{
			/*nextnode*/		&N1_67_Sepo,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongyangM,UID_AfRdPyongyangE},//MS 18Jun99
			/*associated_item*/	UID_StKosan,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_21_39Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_39_67Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KOSAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_67_Sepo	=	{
			/*nextnode*/		&N1_71_Inje,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfBlChuncheon,UID_AfRdSinmak,UID_AfRdHwangju},//MS 18Jun99
			/*associated_item*/	UID_StSepo,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_39_67Rail,&R_Fake05},		//MS 09Jun99
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_67_28Rail,		//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SEPO,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_71_Inje	=	{
			/*nextnode*/		&N1_28_Pyonggang,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSeoul,UID_AfBlKimpo,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_StInje,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_42_71Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_71_12Road0,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Inje,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_28_Pyonggang	=	{
			/*nextnode*/		&N1_43_Chorwon,
			/*supplyline*/		&CentralRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfBlKimpo,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_SdRdPyonggang,				//MS 20Jan99
			/*associated_town*/	UID_StPyonggang,				//MS 20Jan99
			/*associated_text*/	IDS_TARG_SdRdPyonggang,				//MS 20Jan99
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_41_28Road,&R1_67_28Rail},
			/*redfrontBF*/		{FIL_1_C6_RED,&F_C6_RED},
			/*bluefrontBF*/		{FIL_1_C6_UN,&F_C6_UN},
			/*forward*/			&R1_28_38Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_PYONGGAN,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,64}				//MS 28May99
				},
T::N1_43_Chorwon	=	{
			/*nextnode*/		&N1_55_Kanda,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfBlKimpo,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_StChorwon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_28_43Rail,&R1_38_43Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_43_56Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHORWON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_55_Kanda	=		{							//INCORRECT THIS NODE DOES NOT
			/*nextnode*/		&N1_56_Yonchon,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdSinmak},//MS 18Jun99
			/*associated_item*/	UID_StKanda,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_15_55Road,&R1_53_55Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_55_21Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Kanda,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N1_56_Yonchon	=	{
			/*nextnode*/		&N2_40_Munsan,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,						//MS 09Jun99
			/*status*/			BEHINDREDLINES,					//MS 09Jun99
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfBlChuncheon,UID_AfBlKimpo},//MS 18Jun99
			/*associated_item*/	UID_SdRdYonchon,				//MS 22Feb99
			/*associated_town*/	UID_StYonchon,					//MS 22Feb99
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_TODISCOURAGEBLUEATTACK,
			/*maxstores*/		STORES_TOINITIATEASSAULT,
			/*route[3]*/		{&R1_43_56Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R1_56_11Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YONCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
//-------------------------------------------------------------------------------
//Supply Nodes for area 2
T::N2_40_Munsan={
			/*cnextnode*/		&N2_10_Seoul,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,					//MS 09Jun99
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_MyBlMunsan,
			/*associated_town*/	UID_StMunsan,
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,	//STORES_TOINITIATEASSAULT, //TEMP STORES_TODISCOURAGEBLUEATTACK,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	//STORES_TOINITIATEASSAULT,
			/*route[3]*/		{&R1_27_75Rail}, //this is a nobble, leave
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
//DeadCode MS 06Apr99 			/*redfrontBF*/		{FIL_1_W4_RED,&F_W4_RED},
//DeadCode MS 06Apr99 			/*bluefrontBF*/		{FIL_1_W4_UN,&F_W4_UN},
			/*forward*/			&R2_40_10Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Munsan,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,128}				//MS 28May99
				},
T::N2_10_Seoul={
			/*nextnode*/		&N2_7_Suwon,
			/*supplyline*/		&WestRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},//MS 18Jun99
			/*associated_item*/	UID_MyBlSeoul,
			/*associated_town*/	UID_StSeoul,
			/*associated_text*/	IDS_TARG_MyBlSeoul,
			/*currentstores*/	STORES_INITALVERYBIGSETTLEMENT,	//MS 18Jun99
			/*maxstores*/		STORES_INITALVERYBIGSETTLEMENT,
			/*route[3]*/		{&R2_40_10Rail,&R2_48_10Rail,&R2_11_10Rail},		//&R1_39_10Road		no room
			/*redfrontBF*/		{FIL_1_W4_RED,&F_W4_RED},
			/*bluefrontBF*/		{FIL_1_W4_UN,&F_W4_UN},
			/*forward*/			&R2_10_7Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Seoul,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N2_7_Suwon =	{
			/*nextnode*/		&N2_14_Osan,
			/*supplyline*/		&WestRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},//MS 18Jun99
			/*associated_item*/	UID_SdBlSuwon,
			/*associated_town*/	UID_StSuwon,
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
//I'VE PUT THIS TO NIL TO ENSURE MOVEMENT OF SUPPLIES FOR CAMP1	//MS 11Jun99
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	//MS 18Jun99
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R2_10_7Rail,&R2_9_7Road,&R2_7_8Road}, //last route gets reversed, ok//MS 02Jun99
			/*redfrontBF*/		{FIL_1_W3_RED,&F_W3_RED},
			/*bluefrontBF*/		{FIL_1_W3_UN,&F_W3_UN},
			/*forward*/			&R2_7_14Road,					//MS 18Jun99
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SUWON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N2_14_Osan =	{
			/*nextnode*/		&N2_29_Kangnung,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlSuwon,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StOsan,	//UID_MyBlOsan,		//MS 20Jan99
			/*associated_town*/	UID_Null,	//UID_StOsan,		//MS 20Jan99
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	//MS 18Jun99
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	//MS 18Jun99
			/*route[3]*/		{&R2_7_14Road},					//MS 18Jun99
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
//PUT THIS IN			/*redfrontBF*/		{FIL_1_W2_Red,&F_W2_Red},
//PUT THIS IN			/*bluefrontBF*/		{FIL_1_W2_UN,&F_W2_UN},
			/*forward*/			&R2_14_19Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_OSAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N2_29_Kangnung =	{
			/*nextnode*/		&N2_28_Samchok,
			/*supplyline*/		&EastRoute,
			/*type*/			BATTLEFIELD,					//MS 09Jun99
			/*status*/			FRONTLINE,						//MS 09Jun99
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},//MS 18Jun99
			/*associated_item*/	UID_StKangnung,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_36_29Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_29_28Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KANGNUNG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N2_28_Samchok =	{
			/*nextnode*/		&N2_49_Pochon,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlPyongtaek,UID_AfBlChuncheon,UID_AfBlKangnung},//MS 18Jun99
			/*associated_item*/	UID_StSamchok,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R2_29_28Road,&R2_42_28Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_28_30Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SAMCHOK,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_49_Pochon =	{
			/*nextnode*/		&N2_12_Chuncheon,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_StPochon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_69_49Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_49_11Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Pochon,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_12_Chuncheon =	{
			/*nextnode*/		&N2_48_Kuri,
			/*supplyline*/		&CentralRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlChuncheon,UID_AfBlSeoul},//MS 18Jun99
			/*associated_item*/	UID_StChuncheon,//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	//MS 18Jun99
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_70_12Road,&R1_71_12Road0},
			/*redfrontBF*/		{FIL_1_C4_RED,&F_C4_RED},
			/*bluefrontBF*/		{FIL_1_C4_UN,&F_C4_UN},
			/*forward*/			&R2_12_35Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHUNCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N2_48_Kuri =	{
			/*nextnode*/		&N2_35_Hongchon,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_MyBlKuri,
			/*associated_town*/	UID_StKuri,
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R2_12_48Rail,&R2_11_48Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_48_10Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KURI,						//MS 15Jun99
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N2_35_Hongchon =	{
			/*nextnode*/		&N2_23_Hoensong,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSeoul,UID_AfBlChuncheon,UID_AfBlKangnung},//MS 18Jun99
			/*associated_item*/	UID_SdRdHongchon,
			/*associated_town*/	UID_StHongchon,
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	//MS 17Jun99
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R2_12_35Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_35_23Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_HONGCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_23_Hoensong =	{
			/*nextnode*/		&N2_34_Yulchon,
			/*supplyline*/		&CentralRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlChuncheon,UID_AfBlKangnung},//MS 18Jun99
			/*associated_item*/	UID_StHoensong,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	//MS 17Jun99
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R2_35_23Road,&R2_34_23Road,&R_Fake02},//MS 02Jun99
			/*redfrontBF*/		{FIL_1_C3_RED,&F_C3_RED},
			/*bluefrontBF*/		{FIL_1_C3_UN,&F_C3_UN},
			/*forward*/			&R2_23_6Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_HOENSONG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_34_Yulchon =	{
			/*nextnode*/		&N2_43_Pyongchang,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlChuncheon,UID_AfBlKangnung},//MS 18Jun99
			/*associated_item*/	UID_StYulchon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R2_57_34Road,&R2_29_34Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_34_43Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YULCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_43_Pyongchang =	{
			/*nextnode*/		&N2_57_Sangnam,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlChuncheon,UID_AfBlKangnung},//MS 18Jun99
			/*associated_item*/	UID_StPyongchang,//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R2_34_43Road,&R2_6_43Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_43_5Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Pyongchang,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_57_Sangnam =	{
			/*nextnode*/		&N2_42_Chongson,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlSeoul,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_StSangnam,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R1_71_57Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_57_34Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Sangnam,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_42_Chongson =	{
			/*nextnode*/		&N2_9_Inchon,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,						//MS 09Jun99
			/*status*/			BEHINDBLUELINES,				//MS 09Jun99
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlSeoul,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_StChongson,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_TODISCOURAGEBLUEATTACK,
			/*maxstores*/		STORES_TOINITIATEASSAULT,
			/*route[3]*/		{&R2_43_42Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_42_28Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Chongson,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_9_Inchon =	{
			/*nextnode*/		&N2_8_Songnam,					//MS 02May99
			/*supplyline*/		&WestRoute,			// SORTED
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSuwon,UID_AfBlSeoul},//MS 18Jun99
			/*associated_item*/	UID_StInchon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R2_10_9Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_9_7Road,		//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_INCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
//DeadCode MS 02May99 T::N2_39_Kimpo	=	{						  //DAW 14/06/99
//DeadCode MS 02May99 			/*nextnode*/		&N2_8_Songnam,
//DeadCode MS 02May99 			/*supplyline*/		&WestRoute,
//DeadCode MS 02May99 			/*type*/			NOCONTEST,
//DeadCode MS 02May99 			/*status*/			BEHINDBLUELINES,
//DeadCode MS 02May99 			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},//MS 18Jun99
//DeadCode MS 02May99 			/*associated_item*/	UID_StKimpo,	//MS 12Jun98
//DeadCode MS 02May99 			/*associated_town*/	UID_NULL,
//DeadCode MS 02May99 			/*associated_text*/	IDS_NOINFO,
//DeadCode MS 02May99 			/*currentstores*/	STORES_NIL,
//DeadCode MS 02May99 			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
//DeadCode MS 02May99 			/*route[3]*/		{&R1_40_39Road},		//SORTED
//DeadCode MS 02May99 			/*redfrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*bluefrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*forward*/			&R1_39_10Road,		//SORTED
//DeadCode MS 02May99 			/*priority*/		SP_NONE,
//DeadCode MS 02May99 			/*serviced*/		FALSE,
//DeadCode MS 02May99 			/*populate*/		FIL_1_Kimpo,
//DeadCode MS 02May99 
//DeadCode MS 02May99 				},
T::N2_8_Songnam =	{
			/*nextnode*/		&N2_41_Ichon,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},//MS 18Jun99
			/*associated_item*/	UID_StSongnam,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R2_10_8Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_8_41Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_SONGNAM,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_41_Ichon=	{
			/*nextnode*/		&N2_11_Uijongbu,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSuwon,UID_AfBlSeoul},//MS 18Jun99
			/*associated_item*/	UID_Ichon_S,	//MS 12Jun98
			/*associated_town*/	UID_NULL,						//MS 22Apr99
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R2_8_41Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_41_26Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Icho,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_11_Uijongbu =	{
			/*nextnode*/		&N2_58_Yangpyong,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_StUijongbu,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	//MS 18Jun99
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_56_11Rail,&R2_49_11Road},		//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_11_10Rail,			//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_UIJONGBU,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N2_58_Yangpyong =	{
			/*nextnode*/		&N2_6_Wonju,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlSeoul,UID_AfBlChuncheon},//MS 18Jun99
			/*associated_item*/	UID_StYangpyong,//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R2_10_58Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_58_6Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YANGPYON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N2_6_Wonju =	{
			/*nextnode*/		&N3_19_Pyongtaek,
			/*supplyline*/		&CentralRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},//MS 18Jun99
			/*associated_item*/	UID_SdRdWonju,					//MS 20Jan99
			/*associated_town*/	UID_StWonju,	//UID_NULL,		//MS 20Jan99
			/*associated_text*/	IDS_TARG_SdRdWonju,					//MS 20Jan99
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,		//MS 17Jun99
			/*maxstores*/		STORES_INITALVERYBIGSETTLEMENT,	//STORES_INITALBIGSETTLEMENT,
//TempCode MS 25Mar99 			/*currentstores*/	STORES_INITALVERYBIGSETTLEMENT,
//TempCode MS 25Mar99 			/*maxstores*/		STORES_INITALVERYBIGSETTLEMENT,
			/*route[3]*/		{&R2_23_6Road,&R2_58_6Rail},	//&R2_23_6Rail//MS 21Jun99
			/*redfrontBF*/		{FIL_1_C2_RED,&F_C2_RED},
			/*bluefrontBF*/		{FIL_1_C2_UN,&F_C2_UN},
			/*forward*/			&R2_6_5Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Wonju,
			/*repairrate*/		0,								//MS 28May99
			/*maxstores*/		0,								//MS 28May99
			/*attacks*/			{0,0,0,0,0,0,128}				//MS 15Jun99

				},
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//Supply Nodes for area 3
T::N3_19_Pyongtaek =	{
			/*nextnode*/		&N3_3_Chonan,
			/*supplyline*/		&WestRoute,
			/*type*/			BATTLEFIELD,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlPyongtaek,UID_AfBlSuwon},//MS 18Jun99
			/*associated_item*/	UID_SdBlPyongtaek,
			/*associated_town*/	UID_StPyongtaek,
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
//PUT BACK AFTER GROUND BATTLE TEST COMPLETE
//TempCode MS 24Mar99 			/*currentstores*/	STORES_NIL,
//TempCode MS 24Mar99 			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,		//MS 17Jun99
			/*maxstores*/		STORES_INITALVERYBIGSETTLEMENT,	//STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R2_14_19Road,&R_Fake00},
//MARK, MUST PUT THESE BACK IN!!!!!!!!!!!!!
			/*redfrontBF*/		{FIL_1_W2_RED,&F_W2_RED},
			/*bluefrontBF*/		{FIL_1_W2_UN,&F_W2_UN},
			/*forward*/			&R3_19_3Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Pyongtae,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_3_Chonan =	{
			/*nextnode*/		&N3_36_Mokkye,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},//MS 18Jun99
			/*associated_item*/	UID_StChonan,	//UID_SdBlChonan,//MS 20Jan99
			/*associated_town*/	UID_Null,	//UID_StChonan,		//MS 20Jan99
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_19_3Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_3_17Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHONAN,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_36_Mokkye =	{
			/*nextnode*/		&N3_44_Taepaek,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},//MS 18Jun99
			/*associated_item*/	UID_StMokkye,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R2_6_36Road,&R2_5_36Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_36_4Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Mokkye,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_44_Taepaek =	{
			/*nextnode*/		&N3_62_Noktong,
			/*supplyline*/		&EastRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlOsan},//MS 18Jun99
			/*associated_item*/	UID_StTaepaek,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R2_28_44Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_44_62Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Taepaek,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_62_Noktong =	{
			/*nextnode*/		&N3_20_Yechon,
			/*supplyline*/		&EastRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlOsan},//MS 18Jun99
			/*associated_item*/	UID_StNoktong,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R3_44_62Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_62_16Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Noktong,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_20_Yechon =	{
			/*nextnode*/		&N3_24_Chomchon,
			/*supplyline*/		&CentralRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlTaegu,UID_AfBlTaeguW},//MS 18Jun99
			/*associated_item*/	UID_StYechon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R3_18_20Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_20_24Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Yechon,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_24_Chomchon =	{
			/*nextnode*/		&N3_21_Sangju,
			/*supplyline*/		&CentralRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlTaegu,UID_AfBlTaeguW},//MS 18Jun99
			/*associated_item*/	UID_StChomchon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R3_60_24Road,&R3_20_24Road,},		//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_24_21Road,			//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHOMCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_21_Sangju =	{
			/*nextnode*/		&N3_2_Chongju,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlTaegu,UID_AfBlTaeguW},//MS 18Jun99
			/*associated_item*/	UID_StSangju,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R3_24_21Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_21_22Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Sangju,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_2_Chongju =	{
			/*nextnode*/		&N3_8_Songnam,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlPyongtaek,UID_AfBlOsan,UID_AfBlTaejon},//MS 18Jun99
			/*associated_item*/	UID_StChongju_S,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_59_2Rail,&R3_54_2Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_2_1Rail,			//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHONGJU,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_8_Songnam =	{
			/*nextnode*/		&N3_51_Maesan,					//MS 02May99
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlSuwon,UID_AfBlKimpo},//MS 18Jun99
			/*associated_item*/	UID_StSongnam,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R2_10_8Road},		//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_8_41Road,		//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Songnam2,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
//DeadCode MS 02May99 T::N3_64_Hongsong =	{
//DeadCode MS 02May99 			/*nextnode*/		&N3_65_Hannae,
//DeadCode MS 02May99 			/*supplyline*/		&WestRoute,
//DeadCode MS 02May99 			/*tyxpe*/			NOCONTEST,
//DeadCode MS 02May99 			/*status*/			BEHINDBLUELINES,
//DeadCode MS 02May99 			/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlTaejon,UID_AfBlPyongtaek},//MS 18Jun99
//DeadCode MS 02May99 			/*associated_item*/	UID_SdBlHongsong,
//DeadCode MS 02May99 			/*associated_town*/	UID_StHongsong,
//DeadCode MS 02May99 			/*associated_text*/	IDS_TARG_SdBlHongsong,
//DeadCode MS 02May99 			/*currentstores*/	STORES_NIL,
//DeadCode MS 02May99 			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
//DeadCode MS 02May99 			/*route[3]*/		{&R3_3_64Rail},
//DeadCode MS 02May99 			/*redfrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*bluefrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*forward*/			&R3_64_65Rail,
//DeadCode MS 02May99 			/*priority*/		SP_NONE,
//DeadCode MS 02May99 			/*serviced*/		FALSE,
//DeadCode MS 02May99 			/*populate*/		FIL_1_Hongsong,
//DeadCode MS 02May99 
//DeadCode MS 02May99 				},
//DeadCode MS 02May99 T::N3_65_Hannae =	{
//DeadCode MS 02May99 			/*nextnode*/		&N3_51_Maesan,
//DeadCode MS 02May99 			/*supplyline*/		&WestRoute,
//DeadCode MS 02May99 			/*tyxpe*/			NOCONTEST,
//DeadCode MS 02May99 			/*status*/			BEHINDBLUELINES,
//DeadCode MS 02May99 			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},//MS 18Jun99
//DeadCode MS 02May99 			/*associated_item*/	UID_StHannae,	//MS 12Jun98
//DeadCode MS 02May99 			/*associated_town*/	UID_NULL,
//DeadCode MS 02May99 			/*associated_text*/	IDS_NOINFO,
//DeadCode MS 02May99 			/*currentstores*/	STORES_NIL,
//DeadCode MS 02May99 			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
//DeadCode MS 02May99 			/*route[3]*/		{&R3_64_65Rail},
//DeadCode MS 02May99 			/*redfrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*bluefrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*forward*/			&R3_65_66Rail,
//DeadCode MS 02May99 			/*priority*/		SP_NONE,
//DeadCode MS 02May99 			/*serviced*/		FALSE,
//DeadCode MS 02May99 			/*populate*/		FIL_1_Hannae,
//DeadCode MS 02May99 
//DeadCode MS 02May99 				},
T::N3_51_Maesan =	{
			/*nextnode*/		&N3_52_Kwangheywan,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlOsan,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StMaesan,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R3_41_51Road,&R_Fake01},		//MS 14May99
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_51_52Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Maesan,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_52_Kwangheywan =	{
			/*nextnode*/		&N3_53_Chinchon,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlOsan,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StKwangheywan,//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R3_51_52Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_52_53Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Kwangheywan,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_53_Chinchon =	{
			/*nextnode*/		&N3_54_Chungpyong,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlOsan,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StChinchon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R3_52_53Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_53_54Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Chinchon,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_54_Chungpyong =	{
			/*nextnode*/		&N3_60_Mungyong,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlOsan,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StChungpyong,//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R3_53_54Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_54_2Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Chungpyong,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_60_Mungyong =	{
			/*nextnode*/		&N3_61_Tanyang,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlOsan,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StMungyong,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_4_60Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_60_24Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Mungyong,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_61_Tanyang =	{
			/*nextnode*/		&N3_55_Uisong,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlOsan,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StTanyang,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,
			/*route[3]*/		{&R3_4_61Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_61_16Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Tanyang,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_55_Uisong =	{
			/*nextnode*/		&N3_XX_Taegu,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			FRONTLINE,
			/*airfield[3]*/		{UID_AfBlPohang,UID_AfBlTaegu,UID_AfBlTaeguW},//MS 18Jun99
			/*associated_item*/	UID_StUisong,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_18_55Road},
			/*redfrontBF*/		{FIL_NULL},						//MS 09Jun99
			/*bluefrontBF*/		{FIL_NULL},						//MS 09Jun99
			/*forward*/			NULL,							//MS 09Jun99
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Uisong,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
																//MS 22Apr99
T::N3_XX_Taegu =	{
			/*nextnode*/		&N3_4_Chungju,					//MS 02May99
			/*supplyline*/		&WestRoute,						//MS 09Jun99
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlPohang,UID_AfBlTaegu,UID_AfBlTaeguW},//MS 18Jun99
			/*associated_item*/	UID_StTaegu,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_18_25Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			NULL,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Taegu,					//MS 11May99
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
																//MS 22Apr99

//DeadCode MS 02May99 T::N3_66_Taechon =	{
//DeadCode MS 02May99 			/*nextnode*/		&N3_45_Nonsan,
//DeadCode MS 02May99 			/*supplyline*/		&EastRoute,			//WEST!
//DeadCode MS 02May99 			/*tyxpe*/			NOCONTEST,
//DeadCode MS 02May99 			/*status*/			BEHINDBLUELINES,
//DeadCode MS 02May99 			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},//MS 18Jun99
//DeadCode MS 02May99 			/*associated_item*/	UID_StTaechon,	//MS 12Jun98
//DeadCode MS 02May99 			/*associated_town*/	UID_NULL,
//DeadCode MS 02May99 			/*associated_text*/	IDS_NOINFO,
//DeadCode MS 02May99 			/*currentstores*/	STORES_NIL,
//DeadCode MS 02May99 			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
//DeadCode MS 02May99 			/*route[3]*/		{&R3_65_66Rail},
//DeadCode MS 02May99 			/*redfrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*bluefrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*forward*/			&R3_66_63Rail,
//DeadCode MS 02May99 			/*priority*/		SP_NONE,
//DeadCode MS 02May99 			/*serviced*/		FALSE,
//DeadCode MS 02May99 			/*populate*/		FIL_1_Taechon,
//DeadCode MS 02May99 
//DeadCode MS 02May99 				},
//DeadCode MS 02May99 T::N3_45_Nonsan =	{
//DeadCode MS 02May99 			/*nextnode*/		&N3_15_Kongju,					//MS 02May99
//DeadCode MS 02May99 			/*supplyline*/		&WestRoute,						//MS 02May99
//DeadCode MS 02May99 			/*tyxpe*/			NOCONTEST,
//DeadCode MS 02May99 			/*status*/			BEHINDBLUELINES,
//DeadCode MS 02May99 			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},//MS 18Jun99
//DeadCode MS 02May99 			/*associated_item*/	UID_StNonsan,	//MS 12Jun98
//DeadCode MS 02May99 			/*associated_town*/	UID_NULL,
//DeadCode MS 02May99 			/*associated_text*/	IDS_NOINFO,
//DeadCode MS 02May99 			/*currentstores*/	STORES_NIL,
//DeadCode MS 02May99 			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
//DeadCode MS 02May99 			/*route[3]*/		{&R3_63_45Rail},
//DeadCode MS 02May99 			/*redfrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*bluefrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*forward*/			&R3_45_1Rail,
//DeadCode MS 02May99 			/*priority*/		SP_NONE,
//DeadCode MS 02May99 			/*serviced*/		FALSE,
//DeadCode MS 02May99 			/*populate*/		FIL_1_Nonsan,
//DeadCode MS 02May99 
//DeadCode MS 02May99 				},
//DeadCode MS 02May99 T::N3_63_Kunsan =	{
//DeadCode MS 02May99 			/*nextnode*/		&N3_15_Kongju,
//DeadCode MS 02May99 			/*supplyline*/		&WestRoute,
//DeadCode MS 02May99 			/*tyxpe*/			NOCONTEST,
//DeadCode MS 02May99 			/*status*/			BEHINDBLUELINES,
//DeadCode MS 02May99 			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlKunsan,UID_AfBlTaegu},//MS 18Jun99
//DeadCode MS 02May99 			/*associated_item*/	UID_StKunsan,	//MS 12Jun98
//DeadCode MS 02May99 			/*associated_town*/	UID_NULL,
//DeadCode MS 02May99 			/*associated_text*/	IDS_NOINFO,
//DeadCode MS 02May99 			/*currentstores*/	STORES_NIL,
//DeadCode MS 02May99 			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
//DeadCode MS 02May99 			/*route[3]*/		{&R3_66_63Rail},
//DeadCode MS 02May99 			/*redfrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*bluefrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*forward*/			&R3_63_45Rail,
//DeadCode MS 02May99 			/*priority*/		SP_NONE,
//DeadCode MS 02May99 			/*serviced*/		FALSE,
//DeadCode MS 02May99 			/*populate*/		FIL_1_Kunsan,
//DeadCode MS 02May99 
//DeadCode MS 02May99 				},

//DeadCode MS 02May99 T::N3_15_Kongju =	{
//DeadCode MS 02May99 			/*nextnode*/		&N3_4_Chungju,
//DeadCode MS 02May99 			/*supplyline*/		&WestRoute,
//DeadCode MS 02May99 			/*tyxpe*/			NOCONTEST,
//DeadCode MS 02May99 			/*status*/			BEHINDBLUELINES,
//DeadCode MS 02May99 			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},//MS 18Jun99
//DeadCode MS 02May99 			/*associated_item*/	UID_StKongju,	//MS 12Jun98
//DeadCode MS 02May99 			/*associated_town*/	UID_NULL,
//DeadCode MS 02May99 			/*associated_text*/	IDS_NOINFO,
//DeadCode MS 02May99 			/*currentstores*/	STORES_NIL,
//DeadCode MS 02May99 			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
//DeadCode MS 02May99 			/*route[3]*/		{&R3_66_63Rail},	//BADLINK 3_15
//DeadCode MS 02May99 			/*redfrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*bluefrontBF*/		{FIL_NULL},
//DeadCode MS 02May99 			/*forward*/			&R3_63_45Rail,		//BADLINK 15_45 or 15_1
//DeadCode MS 02May99 			/*priority*/		SP_NONE,
//DeadCode MS 02May99 			/*serviced*/		FALSE,
//DeadCode MS 02May99 			/*populate*/		FIL_1_KONGJU,
//DeadCode MS 02May99 
//DeadCode MS 02May99 				},
T::N3_4_Chungju =	{
			/*nextnode*/		&N3_59_Koesan,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},//MS 18Jun99
			/*associated_item*/	UID_StChungju,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_36_4Road,&R2_26_4Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_4_59Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHUNGJU,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_59_Koesan =	{
			/*nextnode*/		&N3_26_Changhowon,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlPyongtaek,UID_AfBlOsan},//MS 18Jun99
			/*associated_item*/	UID_StKoesan,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R3_4_59Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_59_2Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Koesan,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_26_Changhowon =	{
			/*nextnode*/		&N3_17_Chochiwon,
			/*supplyline*/		&WestRoute,
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},//MS 18Jun99
			/*associated_item*/	UID_StChanghowon,//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R2_41_26Road},		//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R2_26_4Road,		//SORTED
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Changhowon,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_17_Chochiwon =	{
			/*nextnode*/		&N3_1_Taejon,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlTaejon,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_MyBlChochiwon,
			/*associated_town*/	UID_StChochiwon,
			/*associated_text*/	IDS_TARG_MyBlChochiwon,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_3_17Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_17_1Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_CHOCHIWO,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_1_Taejon =	{
			/*nextnode*/		&N3_46_Yongdong,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,						//MS 09Jun99
			/*status*/			FRONTLINE,						//MS 09Jun99
			/*airfield[3]*/		{UID_AfBlPyongtaek,UID_AfBlTaejon,UID_AfBlKunsan},//MS 18Jun99
			/*associated_item*/	UID_SdBlTaejon,
			/*associated_town*/	UID_StTaejon,
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,
			/*route[3]*/		{&R3_17_1Rail,&R_Fake07,&R3_2_1Rail},//MS 09Jun99
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_1_46Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_TAEJON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_46_Yongdong =		{	
			/*nextnode*/		&N3_22_Kimchon,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlPyongtaek,UID_AfBlTaejon,UID_AfBlKunsan},//MS 18Jun99
			/*associated_item*/	UID_SdBlYongdong,
			/*associated_town*/	UID_StYongdong,
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_1_46Rail},		//MS 22Apr99
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_46_22Rail,					//MS 22Apr99
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Yongdong,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
				},
T::N3_22_Kimchon =		{	
			/*nextnode*/		&N3_37_Kumi,
			/*supplyline*/		&WestRoute,
			/*type*/			NOCONTEST,						//MS 09Jun99
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlTaeguW,UID_AfBlTaegu},//MS 18Jun99
			/*associated_item*/	UID_StKimchon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_MAXSUPPLY,				//MS 17Jun99
			/*maxstores*/		STORES_MAXSUPPLY,				//MS 17Jun99
			/*route[3]*/		{&R3_46_22Rail,&R3_21_22Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_22_37Road,					//MS 22Apr99
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KIMCHON,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_37_Kumi =		{	
			/*nextnode*/		&N3_30_Ulhin,
			/*supplyline*/		&WestRoute,
			/*type*/			BATTLEFIELD,					//MS 09Jun99
			/*status*/			FRONTLINE,						//MS 09Jun99
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlTaeguW,UID_AfBlTaegu},//MS 18Jun99
			/*associated_item*/	UID_StKumi,						//MS 02May99
			/*associated_town*/	UID_NULL,						//MS 02May99
			/*associated_text*/	IDS_NOINFO,						//MS 14May99
			/*currentstores*/	STORES_MAXSUPPLY,				//MS 17Jun99
			/*maxstores*/		STORES_MAXSUPPLY,				//MS 17Jun99
			/*route[3]*/		{&R3_22_37Road,&R3_55_37Road},
			/*redfrontBF*/		{FIL_1_C1_RED,&F_C1_RED},		//MS 09Jun99
			/*bluefrontBF*/		{FIL_1_C1_UN,&F_C1_UN},			//MS 09Jun99
			/*forward*/			&R3_18_25Rail,					//MS 09Jun99
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_KUMI,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_30_Ulhin =	{
			/*nextnode*/		&N3_31_Yonghae,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlTaegu,UID_AfBlPohang},//MS 18Jun99
			/*associated_item*/	UID_StUlhin,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R2_28_30Road,&R2_62_30Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_30_31Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Ulhin,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_31_Yonghae =	{
			/*nextnode*/		&N3_32_Yongdok,
			/*supplyline*/		&EastRoute,
			/*type*/			BATTLEFIELD,					//MS 09Jun99
			/*status*/			FRONTLINE,						//MS 09Jun99
			/*airfield[3]*/		{UID_AfBlPohang,UID_AfBlTaeguW,UID_AfBlTaegu},//MS 18Jun99
			/*associated_item*/	UID_StYonghae,	//UID_MyBlYonghae,//MS 20Jan99
			/*associated_town*/	UID_Null,	//UID_StYonghae,	//MS 20Jan99
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	//MS 13Jun99
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	//MS 09Jun99
			/*route[3]*/		{&R3_30_31Road},	//SORTED
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_31_32Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_YONGHAE,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_32_Yongdok =	{
			/*nextnode*/		&N3_25_Pohang,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,						//MS 09Jun99
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlPohang,UID_AfBlTaeguW,UID_AfBlTaegu},//MS 18Jun99
			/*associated_item*/	UID_StYongdok,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_31_32Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_32_25Road,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Yongdok,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_25_Pohang =	{
			/*nextnode*/		&N3_5_Chechon,
			/*supplyline*/		&EastRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlPohang,UID_AfBlTaeguW,UID_AfBlTaegu},//MS 18Jun99
			/*associated_item*/	UID_StPohang,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_32_25Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			NULL,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_POHANG,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_5_Chechon =	{
			/*nextnode*/		&N3_47_Punggi,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StChechon,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R2_6_5Rail,&R2_43_5Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_5_47Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Chechon,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_47_Punggi =	{
			/*nextnode*/		&N3_16_Yongju,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StPunggi,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R3_5_47Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_47_16Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_PUNGGI,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_16_Yongju =	{
			/*nextnode*/		&N3_18_Andong,
			/*supplyline*/		&CentralRoute,
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},//MS 18Jun99
			/*associated_item*/	UID_StYongju,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R3_47_16Rail,&R3_62_16Road,&R3_61_16Road},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_16_18Rail,
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Yongju,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99

				},
T::N3_18_Andong =	{
			/*nextnode*/		&Last_Node,
			/*supplyline*/		&CentralRoute,
			/*type*/			BATTLEFIELD,					//MS 09Jun99
			/*status*/			FRONTLINE,						//MS 09Jun99
			/*airfield[3]*/		{UID_AfBlPohang,UID_AfBlTaeguW,UID_AfBlTaegu},//MS 18Jun99
			/*associated_item*/	UID_StAndong,	//MS 12Jun98
			/*associated_town*/	UID_NULL,
			/*associated_text*/	IDS_NOINFO,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	//MS 13Jun99
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,		//MS 09Jun99
			/*route[3]*/		{&R3_16_18Rail},
			/*redfrontBF*/		{FIL_NULL},
			/*bluefrontBF*/		{FIL_NULL},
			/*forward*/			&R3_18_55Road,					//MS 22Apr99
			/*priority*/		SP_NONE,
			/*serviced*/		FALSE,
			/*populate*/		FIL_1_Andong,
			/*repairrate*/		0,								//MS 15Jun99
			/*maxstores*/		0,								//MS 15Jun99
			/*attacks*/			{0,0,0,0,0,0,0}					//MS 15Jun99
			},
//this must be the last one!
T::Last_Node =
		{
			/*nextnode*/		&Last_Node,
			/*supplyline*/		&CentralRoute,
			/*type*/			LASTONE,
		};

//T::N1_50_Yongpyong =		{	//Yongpyong is no longer required, will remove
//			/*nextnode*/		&N1_68_Changdo,
//			/*supplyline*/		&CentralRoute,
//			/*type*/			NOCONTEST,
//			/*status*/			BEHINDBLUELINES,
//			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},//MS 18Jun99
//			/*associated_item*/	UID_StYongpyong,//MS 12Jun98
//			/*associated_town*/	UID_NULL,
//			/*associated_text*/	IDS_NOINFO,
//			/*currentstores*/	STORES_NIL,
//			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
//			/*route[3]*/		{NULL},
//			/*redfrontBF*/		{FIL_NULL},
//			/*bluefrontBF*/		{FIL_NULL},
//			/*forward*/			NULL,
//			/*priority*/		SP_NONE,
//			/*serviced*/		FALSE,
//			/*populate*/		FIL_1_Yongpyong,
//				},

			//T::N1_23_Changyon =		{	//THIS PLACE IS PRETTY MUCH REDUNDANT
//			/*nextnode*/		&N1_14_WaDong,
//			/*supplyline*/		&WestRoute,
//			/*type*/			NOCONTEST,
//			/*status*/			BEHINDREDLINES,
//			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},//MS 18Jun99
//			/*associated_item*/	UID_StChangyon,	//MS 12Jun98
//			/*associated_town*/	UID_NULL,
//			/*associated_text*/	IDS_NOINFO,
//			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
//			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
//			/*route[3]*/		{&R1_62_23Rail},	//BADLINK NONE!
//			/*redfrontBF*/		{FIL_NULL},
//			/*bluefrontBF*/		{FIL_NULL},
//			/*forward*/			&R1_62_23Rail,		//BADLINK NONE!
//			/*priority*/		SP_NONE,
//			/*serviced*/		FALSE,
//			/*populate*/		FIL_1_Changyon,
//				},


//------------------------------------------------------------------------------
//supply routes for area 0
SupplyRoute*const	T::FirstRoute=&WestMainSupply;
SupplyRoute
T::WestMainSupply={
			/*next*/					&R0_0_1Rail0,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_0_Dangdong,
			/*suppliee*/				&N0_0_Dangdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
						},
T::R0_0_1Rail0=	{
			/*next*/					&R0_0_1Rail1,
			/*alternateroute*/			&R0_0_1Rail1,
			/*supplier*/				&N0_0_Dangdong,
			/*suppliee*/				&N0_1_Sinuiju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlYalu0,
			/*associated_brdgtext*/		IDS_BrXXYalu0,
			/*populatebf*/				FIL_1_BRIDGE00
						},
T::R0_0_1Rail1=	{
			/*next*/					&R0_0_1Road,
			/*alternateroute*/			&R0_0_1Road,
			/*supplier*/				&N0_0_Dangdong,
			/*suppliee*/				&N0_1_Sinuiju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,	//UID_BrRlYalu1,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_0_1Road=	{
			/*next*/					&R0_1_2Rail0,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_0_Dangdong,
			/*suppliee*/				&N0_1_Sinuiju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdYalu,
			/*associated_brdgtext*/		IDS_BrXXYalu0,
			/*populatebf*/				FIL_1_BRIDGE01
		//		/*storeslaunched*/			0,
		//	/*stores_destroyed*/		0,
		//	/*totalstores_destroyed*/	0,
		//	/*consecutive_days_attacked*/		0,
						},
T::R0_1_2Rail0=	{
			/*next*/					&R0_1_2Rail1,
			/*alternateroute*/			&R0_1_2Rail1,
			/*supplier*/				&N0_1_Sinuiju,
			/*suppliee*/				&N0_2_Yomju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinuiju0,
			/*associated_brdgtext*/		IDS_BrXXSinuiju0,
			/*populatebf*/				FIL_1_BRIDGE02
							},
T::R0_1_2Rail1=	{
			/*next*/					&R0_1_2Road,
			/*alternateroute*/			&R0_1_2Road,
			/*supplier*/				&N0_1_Sinuiju,
			/*suppliee*/				&N0_2_Yomju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,	//UID_BrRlSinuiju1,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_1_2Road=	{
			/*next*/					&R0_32_33Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_1_Sinuiju,
			/*suppliee*/				&N0_2_Yomju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSinuiju,
			/*associated_brdgtext*/		IDS_BrXXSinuiju0,
			/*populatebf*/				FIL_1_BRIDGE03
							},
T::R0_32_33Road=	{
			/*next*/					&R0_33_51Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_32_Hyesan,
			/*suppliee*/				&N0_33_Kapsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Hyesan2Kapsan,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD32
							},
//T::R0_3_58Road=	{
//			/*next*/					&R0_33_51Road,
//			/*alternateroute*/			NULL,
//			/*supplier*/				&N0_3_Sonchon,
//			/*suppliee*/				&N0_58_SinmiDo,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRUCK,
//			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},
T::R0_33_51Road=	{
			/*next*/					&R0_51_37Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_33_Kapsan,
			/*suppliee*/				&N0_51_Pungsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_51_37Road=	{
			/*next*/					&R0_9_59Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_51_Pungsan,
			/*suppliee*/				&N0_37_Pukchong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Pungsan2Pukchong,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD31
							},

T::R0_9_59Road=	{
			/*next*/					&R0_48_4Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_9_Kangye,
			/*suppliee*/				&N0_59_Chosin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_48_4Road=	{
			/*next*/					&R0_59_19Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_48_Kusong,
			/*suppliee*/				&N0_4_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Kusong2Chongju,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD00			//MS 02MAR99
							},
T::R0_59_19Road=	{
			/*next*/					&R0_11_19Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_59_Chosin,
			/*suppliee*/				&N0_19_Hamhung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_11_19Road=	{
			/*next*/					&R0_2_3Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_11_Kujang,
			/*suppliee*/				&N0_19_Hamhung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_2_3Rail=	{
			/*next*/					&R0_11_12Rail,
			/*alternateroute*/			&R0_2_3Road,
			/*supplier*/				&N0_2_Yomju,
			/*suppliee*/				&N0_3_Sonchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Yomju2Sonchon,	//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL00			//MS 02MAR99
							},
T::R0_11_12Rail=	{
			/*next*/					&R0_2_3Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_11_Kujang,
			/*suppliee*/				&N1_12_Sunchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_RAIL_Kujang2Sunchon,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL18
							},
T::R0_2_3Road=	{
			/*next*/					&R0_3_4Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_2_Yomju,
			/*suppliee*/				&N0_3_Sonchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Yomju2Sonchon,	//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD01			//MS 02MAR99
							},
T::R0_3_4Rail=	{
			/*next*/					&R0_3_4Road,
			/*alternateroute*/			&R0_3_4Road,
			/*supplier*/				&N0_3_Sonchon,
			/*suppliee*/				&N0_4_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Sonchon2Chongju,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL01			//MS 02MAR99
							},
T::R0_3_4Road=	{
			/*next*/					&R0_9_51Road,
			/*alternateroute*/			NULL,	//&R0_48_4Rail,
			/*supplier*/				&N0_3_Sonchon,
			/*suppliee*/				&N0_4_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Sonchon2Chongju,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD02			//MS 02MAR99
							},
T::R0_9_51Road=	{
			/*next*/					&R0_60_11Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_9_Kangye,
			/*suppliee*/				&N0_51_Pungsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdUngig,
			/*associated_brdgtext*/		IDS_BrXXUngig,
			/*populatebf*/				FIL_1_BRIDGE04
							},
//used for 60_10
T::R0_60_11Road=	{
			/*next*/					&R0_11_5Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_60_Chosan,
			/*suppliee*/				&N0_10_Huichon,	//this is correct, do not change
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdChosan,
			/*associated_brdgtext*/		IDS_BrXXchosan,
			/*populatebf*/				FIL_1_BRIDGE05
							},
T::R0_11_5Rail=	{
			/*next*/					&R0_11_5Road,
			/*alternateroute*/			&R0_11_5Road,
			/*supplier*/				&N0_11_Kujang,
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_RAIL_Kujang2Sinaju,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,	//UID_BrRlChongchon0,//MS 20Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL17
							},
T::R0_11_5Road=	{
			/*next*/					&R0_4_4bRail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_11_Kujang,
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_4_4bRail=	{
			/*next*/					&R0_4_4bRoad,
			/*alternateroute*/			&R0_4_4bRoad,
			/*supplier*/				&N0_4_Chongju,
			/*suppliee*/				&N0_4b_Maenjungdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlTaeryong,
			/*associated_brdgtext*/		IDS_BrXXTaeryong,
			/*populatebf*/				FIL_1_BRIDGE06
							},
T::R0_4_4bRoad=	{
			/*next*/					&R0_4b_5Rail0,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_4_Chongju,
			/*suppliee*/				&N0_4b_Maenjungdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdTaeryong,
			/*associated_brdgtext*/		IDS_BrXXTaeryong,
			/*populatebf*/				FIL_1_BRIDGE07
							},
T::R0_4b_5Rail0=	{
			/*next*/					&R0_4b_5Rail1,
			/*alternateroute*/			&R0_4b_5Rail1,
			/*supplier*/				&N0_4b_Maenjungdong,
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinanju0,
			/*associated_brdgtext*/		IDS_BrXXSinanju0,
			/*populatebf*/				FIL_1_BRIDGE08
			},
T::R0_4b_5Rail1=	{
			/*next*/					&R0_4b_5Rail2,
			/*alternateroute*/			&R0_4b_5Rail2,
			/*supplier*/				&N0_4b_Maenjungdong,
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinanju1,
			/*associated_brdgtext*/		IDS_BrXXSinanju0,
			/*populatebf*/				FIL_1_BRIDGE09
			},
T::R0_4b_5Rail2=	{
			/*next*/					&R0_4b_5Rail3,
			/*alternateroute*/			&R0_4b_5Rail3,
			/*supplier*/				&N0_4b_Maenjungdong,
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL,	//UID_BrRlSinanju2,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO	,
			/*populatebf*/				FIL_NULL
			},
T::R0_4b_5Rail3=	{
			/*next*/					&R0_4b_5Rail4,
			/*alternateroute*/			&R0_4b_5Rail4,
			/*supplier*/				&N0_4b_Maenjungdong,
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL,	//UID_BrRlSinanju3,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},
T::R0_4b_5Rail4=	{
			/*next*/					&R0_4b_5Road,
			/*alternateroute*/			&R0_4b_5Road,
			/*supplier*/				&N0_4b_Maenjungdong,
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL,	//UID_BrRlSinanju4,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},
T::R0_4b_5Road=	{
			/*next*/					&R0_4_5Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_4b_Maenjungdong,
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSinanju,
			/*associated_brdgtext*/		IDS_BrXXSinanju0,
			/*populatebf*/				FIL_1_BRIDGE10
							},

T::R0_4_5Road=	{
			/*next*/					&R0_5_6Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_4_Chongju,
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_5_6Rail=	{
			/*next*/					&R0_5_6Road,
			/*alternateroute*/			&R0_5_6Road,
			/*supplier*/				&N0_5_Sinaju,
			/*suppliee*/				&N1_6_Sukchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_RAIL_Sinaju2Sukchon,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL16
							},
T::R0_5_6Road=	{
			/*next*/					&R0_C_16Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_5_Sinaju,
			/*suppliee*/				&N1_6_Sukchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_C_16Rail=	{
			/*next*/					&R0_16_56Rail,
			/*alternateroute*/			&R0_16_56Road,
			/*supplier*/				&China_E,
			/*suppliee*/				&N0_16_Chongjin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_16_56Rail=	{
			/*next*/					&R0_16_56Road,
			/*alternateroute*/			&R0_16_56Road,
			/*supplier*/				&N0_16_Chongjin,
			/*suppliee*/				&N0_56_Kyongsong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_RAIL_Chongjin2Kyongsong,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL25
							},


T::R0_16_56Road=	{
			/*next*/					&R0_56_17Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_16_Chongjin,
			/*suppliee*/				&N0_56_Kyongsong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_56_17Rail=	{
			/*next*/					&R0_56_17Road,
			/*alternateroute*/			&R0_56_17Road,
			/*supplier*/				&N0_56_Kyongsong,
			/*suppliee*/				&N0_17_Kilchu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL,		//UID_BrRdKyongsong,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_56_17Road=	{
			/*next*/					&R0_17_18Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_56_Kyongsong,
			/*suppliee*/				&N0_17_Kilchu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_NULL,	//UID_BrRdKyongsong,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_17_18Rail=	{
			/*next*/					&R0_17_18Road,
			/*alternateroute*/			&R0_17_18Road,
			/*supplier*/				&N0_17_Kilchu,
			/*suppliee*/				&N0_18_Kimchaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_17_18Road=	{
			/*next*/					&R0_18_50Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_17_Kilchu,
			/*suppliee*/				&N0_18_Kimchaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdKilchu,
			/*associated_brdgtext*/		IDS_BrXXKilchu,
			/*populatebf*/				FIL_1_BRIDGE11
							},
T::R0_18_50Rail=	{
			/*next*/					&R0_18_50Road,
			/*alternateroute*/			&R0_18_50Road,
			/*supplier*/				&N0_18_Kimchaek,
			/*suppliee*/				&N0_50_Tanchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL,	//UID_BrRdKimchaek,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_18_50Road=	{
			/*next*/					&R0_51_50Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_18_Kimchaek,
			/*suppliee*/				&N0_50_Tanchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_51_50Rail=	{
			/*next*/					&R0_50_37Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_51_Pungsan,
			/*suppliee*/				&N0_50_Tanchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_RAIL_Pungsan2Tanchon,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL,	//	UID_BrRdKimchaek,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL24
							},
T::R0_50_37Rail=	{
			/*next*/					&R0_50_37Road0,
			/*alternateroute*/			&R0_50_37Road0,
			/*supplier*/				&N0_50_Tanchon,
			/*suppliee*/				&N0_37_Pukchong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlPuktaechon,	//2 bridges
			/*associated_brdgtext*/		IDS_BrXXPuktaechon,
			/*populatebf*/				FIL_1_BRIDGE12
							},
T::R0_50_37Road0=	{
			/*next*/					&R0_50_37Road1,
			/*alternateroute*/			&R0_50_37Road1,
			/*supplier*/				&N0_50_Tanchon,
			/*suppliee*/				&N0_37_Pukchong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRdTanchon0,
			/*associated_brdgtext*/		IDS_BrXXPuktaechon,
			/*populatebf*/				FIL_1_BRIDGE13
							},
T::R0_50_37Road1=	{
			/*next*/					&R0_37_19Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_50_Tanchon,
			/*suppliee*/				&N0_37_Pukchong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdTanchon1,
			/*associated_brdgtext*/		IDS_BrXXPuktaechon,
			/*populatebf*/				FIL_1_BRIDGE14
							},
T::R0_37_19Rail=	{
			/*next*/					&R0_37_19Road,
			/*alternateroute*/			&R0_37_19Road,
			/*supplier*/				&N0_37_Pukchong,
			/*suppliee*/				&N0_19_Hamhung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlNamdaechon,
			/*associated_brdgtext*/		IDS_BrXXNamdaechon,
			/*populatebf*/				FIL_1_BRIDGE15
							},
T::R0_37_19Road=	{
			/*next*/					&R0_19_34Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_37_Pukchong,
			/*suppliee*/				&N0_19_Hamhung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRlNamdaechon, //FIXME this is temp, need road bridge
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_19_34Rail=	{
			/*next*/					&R0_19_34Road,
			/*alternateroute*/			&R0_19_34Road,
			/*supplier*/				&N0_19_Hamhung,
			/*suppliee*/				&N1_34_Yonghung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlKumjinchon,
			/*associated_brdgtext*/		IDS_BrXXKumjinchon,
			/*populatebf*/				FIL_1_BRIDGE16
							},
T::R0_19_34Road=	{
			/*next*/					&R0_8_9Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_19_Hamhung,
			/*suppliee*/				&N1_34_Yonghung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_8_9Rail=	{
			/*next*/					&R0_C_8Rail,
			/*alternateroute*/			&R0_8_9Road,
			/*supplier*/				&N0_8_Manpo,
			/*suppliee*/				&N0_9_Kangye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlManpo,
			/*associated_brdgtext*/		IDS_BrXXManpo,
			/*populatebf*/				FIL_1_BRIDGE17
							},

T::R0_C_8Rail=	{
			/*next*/					&R0_8_9Road,
			/*alternateroute*/			&R0_8_9Road,
			/*supplier*/				&China_C,
			/*suppliee*/				&N0_8_Manpo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},

T::R0_8_9Road=	{
			/*next*/					&R0_9_10Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_8_Manpo,
			/*suppliee*/				&N0_9_Kangye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_9_10Rail=	{
			/*next*/					&R0_9_10Road,
			/*alternateroute*/			&R0_9_10Road,
			/*supplier*/				&N0_9_Kangye,
			/*suppliee*/				&N0_10_Huichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlHuichon,
			/*associated_brdgtext*/		IDS_BrXXHuichon,
			/*populatebf*/				FIL_1_BRIDGE18
							},
T::R0_9_10Road=	{
			/*next*/					&R0_10_11Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_9_Kangye,
			/*suppliee*/				&N0_10_Huichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_10_11Rail=	{
			/*next*/					&R0_10_11Road,
			/*alternateroute*/			&R0_10_11Road,
			/*supplier*/				&N0_10_Huichon,
			/*suppliee*/				&N0_11_Kujang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Huichon2Kujang,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL02			//MS 02MAR99
							},
T::R0_10_11Road=	{
			/*next*/					&R0_11_31Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_10_Huichon,
			/*suppliee*/				&N0_11_Kujang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Huichon2Kujang,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD03			//MS 02MAR99
							},
T::R0_11_31Rail=	{
			/*next*/					&R0_44_45Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_11_Kujang,
			/*suppliee*/				&N0_31_Tokchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_RAIL_Kujang2Tokchon,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL19
							},
T::R0_44_45Rail=	{
			/*next*/					&R0_46_48Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_44_Namsanni,
			/*suppliee*/				&N0_45_Sakchu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_46_48Road=	{
			/*next*/					&R0_0_57Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_46_Chongsongup,
			/*suppliee*/				&N0_48_Kusong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_0_57Rail=	{
			/*next*/					&R0_0_44Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_0_Dangdong,
			/*suppliee*/				&N0_57_Suiho,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_0_44Rail=	{
			/*next*/					&R0_8_60Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_0_Dangdong,
			/*suppliee*/				&N0_44_Namsanni,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_8_60Rail=	{	//THIS IS USED FOR CHINA_C to Chosan
			/*next*/					&R0_16_32Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&China_C,
			/*suppliee*/				&N0_60_Chosan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_16_32Rail=	{	//USED FOR CHINA_E to Hyesan
			/*next*/					&R0_57_46Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&China_E,
			/*suppliee*/				&N0_32_Hyesan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_57_46Road=	{
			/*next*/					&R0_45_48Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_57_Suiho,
			/*suppliee*/				&N0_46_Chongsongup,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_45_48Rail=	{
			/*next*/					&R0_48_4Rail,
			/*alternateroute*/			NULL,	//was &R0_46_48Road wrong,
			/*supplier*/				&N0_45_Sakchu,
			/*suppliee*/				&N0_48_Kusong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R0_48_4Rail=	{
			/*next*/					&R0_31_29Rail,
			/*alternateroute*/			&R0_48_4Road,
			/*supplier*/				&N0_48_Kusong,
			/*suppliee*/				&N0_4_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Kusong2Chongju,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL03			//MS 02MAR99
							},
T::R0_31_29Rail=	{
			/*next*/					&R1_6_7Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_31_Tokchon,
			/*suppliee*/				&N1_29_Kangdong, //fudge fix
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
//------------------------------------------------------------------------------
//supply routes for area 1
T::R1_6_7Rail=	{
			/*next*/					&R1_6_7Road,
			/*alternateroute*/			&R1_6_7Road,
			/*supplier*/				&N1_6_Sukchon,
			/*suppliee*/				&N1_7_Pyongyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Sukchon2Pyongyang,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL04			//MS 02MAR99
							},
T::R1_6_7Road=	{
			/*next*/					&R1_7_30Rail,
			/*alternateroute*/			NULL,	//was Null
			/*supplier*/				&N1_6_Sukchon,
			/*suppliee*/				&N1_7_Pyongyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Sukchon2Pyongyang,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD04			//MS 02MAR99
			},
T::R1_7_30Rail=	{
			/*next*/					&R1_13_54Rail,
			/*alternateroute*/			&R1_7_30Road,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_30_Nampo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},


T::R1_13_54Rail=	{
			/*next*/					&R1_49_22Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_13_Samdung,
			/*suppliee*/				&N1_54_YulLi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlNan,
			/*associated_brdgtext*/		IDS_BrXXNan,
			/*populatebf*/				FIL_1_BRIDGE19
							},
T::R1_49_22Rail=	{
			/*next*/					&R1_49_22Road,
			/*alternateroute*/			&R1_49_22Road,
			/*supplier*/				&N1_49_Hwangju,
			/*suppliee*/				&N1_22_Sariwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Hwangju2Sariwon,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL05			//MS 02MAR99
							},
T::R1_49_22Road=	{
			/*next*/					&R1_25_41Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_49_Hwangju,
			/*suppliee*/				&N1_22_Sariwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Hwangju2Sariwon,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD05			//MS 02MAR99
							},
T::R1_25_41Road=	{
			/*next*/					&R1_7_64Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_25_Pyongsan,
			/*suppliee*/				&N1_41_Ichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_7_64Road=	{
			/*next*/					&R1_64_54Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_64_Sangwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_64_54Road=	{
			/*next*/					&R1_65_22Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_64_Sangwon,
			/*suppliee*/				&N1_54_YulLi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_65_22Road=		{
			/*next*/					&R1_54_65Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_65_Nuang,
			/*suppliee*/				&N1_22_Sariwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_54_65Road=	{
			/*next*/					&R1_25_63Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_54_YulLi,
			/*suppliee*/				&N1_65_Nuang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_25_63Road=		{	//reversed
			/*next*/					&R1_7_30Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_63_Suan,
			/*suppliee*/				&N1_25_Pyongsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Suan2Pyongsan,	//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD06			//MS 02MAR99
							},
T::R1_7_30Road=	{
			/*next*/					&R1_15_53Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_30_Nampo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},

T::R1_15_53Road=	{
			/*next*/					&R1_53_55Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_15_Yangdok,
			/*suppliee*/				&N1_53_Koksan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_53_55Road=	{
			/*next*/					&R1_12_7Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_53_Koksan,
			/*suppliee*/				&N1_55_Kanda,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_12_7Rail=	{
			/*next*/					&R1_22_62Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_12_Sunchon,
			/*suppliee*/				&N1_7_Pyongyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Sunchon2Pyongyang,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL06			//MS 02MAR99
							},
T::R1_22_62Rail=	{
			/*next*/					&R1_30_62Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_22_Sariwon,
			/*suppliee*/				&N1_62_Chaeryong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_30_62Road=	{
			/*next*/					&R1_62_24Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_30_Nampo,
			/*suppliee*/				&N1_62_Chaeryong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Nampo2Chaeryong,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD07			//MS 02MAR99
							},
T::R1_62_24Rail=	{
			/*next*/					&R1_24_61Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_62_Chaeryong,
			/*suppliee*/				&N1_24_Haeju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_24_61Rail=	{
			/*next*/					&R1_61_27Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_24_Haeju,
			/*suppliee*/				&N1_61_Yonan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Haeju2Yonan,	//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL07			//MS 02MAR99
							},
T::R1_61_27Rail=	{
			/*next*/					&R1_12_29Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_61_Yonan,
			/*suppliee*/				&N1_27_Kaesong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},

T::R1_12_29Rail=	{
			/*next*/					&R1_12_29Road,
			/*alternateroute*/			&R1_12_29Road,
			/*supplier*/				&N1_12_Sunchon,
			/*suppliee*/				&N1_29_Kangdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_12_29Road=		{
			/*next*/					&R1_29_13Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_12_Sunchon,
			/*suppliee*/				&N1_29_Kangdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_29_13Rail=	{
			/*next*/					&R1_29_13Road,
			/*alternateroute*/			&R1_29_13Road,
			/*supplier*/				&N1_29_Kangdong,
			/*suppliee*/				&N1_13_Samdung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_29_13Road=		{
			/*next*/					&R1_7_49Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_29_Kangdong,
			/*suppliee*/				&N1_13_Samdung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_7_49Rail=	{
			/*next*/					&R1_66_53Road,
			/*alternateroute*/			&R1_7_49Road0,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_49_Hwangju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlPyongyang,
			/*associated_brdgtext*/		IDS_BrXXPyongyang,
			/*populatebf*/				FIL_1_BRIDGE20
							},
T::R1_66_53Road=		{//switched flow 53 to 66
			/*next*/					&R1_15_55Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_53_Koksan,
			/*suppliee*/				&N1_66_Singye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_15_55Road=	{
			/*next*/					&R1_63_54Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_15_Yangdok,
			/*suppliee*/				&N1_55_Kanda,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_63_54Road=		{		//reversed
			/*next*/					&R1_63_66Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_54_YulLi,
			/*suppliee*/				&N1_63_Suan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_63_66Road=	{
			/*next*/					&R1_66_41Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_63_Suan,
			/*suppliee*/				&N1_66_Singye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_66_41Road=	{
			/*next*/					&R1_71_57Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_66_Singye,
			/*suppliee*/				&N1_41_Ichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_71_57Road=	{
			/*next*/					&R1_42_71Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_71_Inje,
			/*suppliee*/				&N2_57_Sangnam,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_42_71Road=	{
			/*next*/					&R1_55_21Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_42_Kansang,
			/*suppliee*/				&N1_71_Inje,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_55_21Road=	{
			/*next*/					&R1_38_70Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_55_Kanda,
			/*suppliee*/				&N1_21_Wonsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Kanda2Wonsan,	//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD08			//MS 02MAR99
							},
T::R1_38_70Road=	{
			/*next*/					&R1_71_36Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_38_Kumhwa,
			/*suppliee*/				&N1_70_Hwachon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Kumhwa2Hwachon,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD09			//MS 02MAR99
							},
T::R1_71_36Road=	{
			/*next*/					&R1_71_12Road0,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_71_Inje,
			/*suppliee*/				&N1_36_Yangyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Inje2Yangyang,	//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD10			//MS 02MAR99
							},
T::R1_71_12Road0=	{
			/*next*/					&R1_71_12Road1,
			/*alternateroute*/			&R1_71_12Road1,
			/*supplier*/				&N1_71_Inje,
			/*suppliee*/				&N2_12_Chuncheon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdInje,
			/*associated_brdgtext*/		IDS_BrXXInje,
			/*populatebf*/				FIL_1_BRIDGE21
							},
T::R1_71_12Road1=	{
			/*next*/					&R1_25_66Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_71_Inje,
			/*suppliee*/				&N2_12_Chuncheon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},


T::R1_25_66Road=		{//reversed
			/*next*/					&R1_41_28Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_66_Singye,
			/*suppliee*/				&N1_25_Pyongsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},


T::R1_41_28Road=	{
			/*next*/					&R1_7_49Road0,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_41_Ichon,
			/*suppliee*/				&N1_28_Pyonggang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Ichon2Pyonggang,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD11			//MS 02MAR99
							},
T::R1_7_49Road0=	{
			/*next*/					&R1_7_49Road1,
			/*alternateroute*/			&R1_7_49Road1,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_49_Hwangju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdPyongyang0,
			/*associated_brdgtext*/		IDS_BrXXPyongyang0,
			/*populatebf*/				FIL_1_BRIDGE22
							},
T::R1_7_49Road1=	{
			/*next*/					&R1_22_25Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_49_Hwangju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdPyongyang1,
			/*associated_brdgtext*/		IDS_BrXXPyongyang0,
			/*populatebf*/				FIL_1_BRIDGE23
							},
T::R1_22_25Rail=	{
			/*next*/					&R1_22_25Road,
			/*alternateroute*/			&R1_22_25Road,
			/*supplier*/				&N1_22_Sariwon,
			/*suppliee*/				&N1_25_Pyongsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Sariwon2Pyongsan,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL08			//MS 02MAR99
							},
T::R1_22_25Road=	{
			/*next*/					&R1_25_26Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_22_Sariwon,
			/*suppliee*/				&N1_25_Pyongsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Sariwon2Pyongsan,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD12			//MS 02MAR99
							},
T::R1_25_26Rail=	{
			/*next*/					&R1_25_26Road,
			/*alternateroute*/			&R1_25_26Road,
			/*supplier*/				&N1_25_Pyongsan,
			/*suppliee*/				&N1_26_Kumchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_25_26Road=	{
			/*next*/					&R1_26_27Rail,
			/*alternateroute*/			NULL,
			/*suppliee*/				&N1_25_Pyongsan,
			/*suppliee*/				&N1_26_Kumchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_26_27Rail=	{
			/*next*/					&R1_26_27Road,
			/*alternateroute*/			&R1_26_27Road,
			/*supplier*/				&N1_26_Kumchon,
			/*suppliee*/				&N1_27_Kaesong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Kumchon2Kaesong,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL09			//MS 02MAR99
							},
T::R1_26_27Road=	{
			/*next*/					&R1_27_75Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_26_Kumchon,
			/*suppliee*/				&N1_27_Kaesong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Kumchon2Kaesong,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD13			//MS 02MAR99
							},
T::R1_27_75Rail=	{
			/*next*/					&R1_27_75Road,
			/*alternateroute*/			&R1_27_75Road,
			/*supplier*/				&N1_27_Kaesong,
			/*suppliee*/				&N2_40_Munsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlYesong,
			/*associated_brdgtext*/		IDS_BrXXYesong,
			/*populatebf*/				FIL_1_BRIDGE24
							},
T::R1_27_75Road=		{//now goes to munsan 40
			/*next*/					&R1_34_20Rail,			//MS 02May99
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_27_Kaesong,
			/*suppliee*/				&N2_40_Munsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
//DeadCode MS 02May99 T::R1_40_39Road=	{
//DeadCode MS 02May99 			/*next*/					&R1_39_10Road,
//DeadCode MS 02May99 			/*alternateroute*/			NULL,
//DeadCode MS 02May99 			/*supplier*/				&N2_40_Munsan,
//DeadCode MS 02May99 			/*suppliee*/				&N2_39_Kimpo,
//DeadCode MS 02May99 			/*status*/					SR_ACTIVE,
//DeadCode MS 02May99 			/*recommision_time*/		DAYS0,
//DeadCode MS 02May99 			/*redsupplyUID*/				UID_NULL,
//DeadCode MS 02May99 			/*storespermobile*/			STORES_TRUCK,
//DeadCode MS 02May99 			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//DeadCode MS 02May99 			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//DeadCode MS 02May99 			/*associated_brdg*/			UID_Null,
//DeadCode MS 02May99 			/*associated_brdgtext*/		IDS_NOINFO,
//DeadCode MS 02May99 			/*populatebf*/				FIL_NULL
//DeadCode MS 02May99 								},
//DeadCode MS 02May99 T::R1_39_10Road=	{
//DeadCode MS 02May99 			/*next*/					&R1_34_20Rail,
//DeadCode MS 02May99 			/*alternateroute*/			NULL,
//DeadCode MS 02May99 			/*supplier*/				&N2_39_Kimpo,
//DeadCode MS 02May99 			/*suppliee*/				&N2_10_Seoul,
//DeadCode MS 02May99 			/*status*/					SR_ACTIVE,
//DeadCode MS 02May99 			/*recommision_time*/		DAYS0,
//DeadCode MS 02May99 			/*redsupplyUID*/				UID_NULL,
//DeadCode MS 02May99 			/*storespermobile*/			STORES_TRUCK,
//DeadCode MS 02May99 			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//DeadCode MS 02May99 			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//DeadCode MS 02May99 			/*associated_brdg*/			UID_Null,
//DeadCode MS 02May99 			/*associated_brdgtext*/		IDS_NOINFO,
//DeadCode MS 02May99 			/*populatebf*/				FIL_NULL
//DeadCode MS 02May99 								},
T::R1_34_20Rail=	{
			/*next*/					&R1_34_20Road,
			/*alternateroute*/			&R1_34_20Road,
			/*supplier*/				&N1_34_Yonghung,
			/*suppliee*/				&N1_20_Kowon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlTokohig,
			/*associated_brdgtext*/		IDS_BrXXTokohig,
			/*populatebf*/				FIL_1_BRIDGE25
								},
T::R1_34_20Road=	{
			/*next*/					&R1_20_21Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_34_Yonghung,
			/*suppliee*/				&N1_20_Kowon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_20_21Rail=	{
			/*next*/					&R1_20_21Road,
			/*alternateroute*/			&R1_20_21Road,
			/*supplier*/				&N1_20_Kowon,
			/*suppliee*/				&N1_21_Wonsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_RAIL_Kowon2Wonsan,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlKowon,
			/*associated_brdgtext*/		IDS_BrXXKowan,
			/*populatebf*/				FIL_1_BRIDGE26
								},
T::R1_20_21Road=	{
			/*next*/					&R1_21_52Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_20_Kowon,
			/*suppliee*/				&N1_21_Wonsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_21_52Rail=	{
			/*next*/					&R1_52_35Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_21_Wonsan,
			/*suppliee*/				&N1_52_Kojo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_RAIL_Wonsan2Kojo,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL23
								},
T::R1_52_35Rail=	{
			/*next*/					&R1_52_35Road,
			/*alternateroute*/			&R1_52_35Road,
			/*supplier*/				&N1_52_Kojo,
			/*suppliee*/				&N1_35_Kojin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_52_35Road=	{
			/*next*/					&R1_35_42Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_52_Kojo,
			/*suppliee*/				&N1_35_Kojin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_35_42Rail=	{
			/*next*/					&R1_35_42Road,
			/*alternateroute*/			&R1_35_42Road,
			/*supplier*/				&N1_35_Kojin,
			/*suppliee*/				&N1_42_Kansang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_35_42Road=	{
			/*next*/					&R1_42_36Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_35_Kojin,
			/*suppliee*/				&N1_42_Kansang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_42_36Rail=	{
			/*next*/					&R1_36_29Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_42_Kansang,
			/*suppliee*/				&N1_36_Yangyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Kansang2Yangyang,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL10			//MS 02MAR99
								},
T::R1_36_29Road=	{
			/*next*/					&R1_29_14Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_36_Yangyang,
			/*suppliee*/				&N2_29_Kangnung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Yangyang2Kangnung,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD14			//MS 02MAR99
								},


T::R1_29_14Rail=	{
			/*next*/					&R1_29_14Road,
			/*alternateroute*/			&R1_29_14Road,
			/*supplier*/				&N1_29_Kangdong,
			/*suppliee*/				&N1_14_WaDong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_29_14Road=	{
			/*next*/					&R1_14_15Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_29_Kangdong,
			/*suppliee*/				&N1_14_WaDong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_14_15Rail=	{
			/*next*/					&R1_14_15Road,
			/*alternateroute*/			&R1_14_15Road,
			/*supplier*/				&N1_14_WaDong,
			/*suppliee*/				&N1_15_Yangdok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,					  //MS 30/04/99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_14_15Road=	{
			/*next*/					&R1_15_20Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_14_WaDong,
			/*suppliee*/				&N1_15_Yangdok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Wadong2Yangdok,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD15			//MS 02MAR99
								},
T::R1_15_20Rail=		{	 //i've reversed flow to 15 to 20, so don't correct
			/*next*/					&R1_21_39Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_20_Kowon,
			/*suppliee*/				&N1_15_Yangdok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_RAIL_Kowon2Yangdok,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL20
								},
T::R1_21_39Rail=	{
			/*next*/					&R1_21_39Road,
			/*alternateroute*/			&R1_21_39Road,
			/*supplier*/				&N1_21_Wonsan,
			/*suppliee*/				&N1_39_Kosan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_RAIL_Wonsan2Kosan,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL22
								},
T::R1_21_39Road=	{
			/*next*/					&R1_39_40Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_21_Wonsan,
			/*suppliee*/				&N1_39_Kosan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_39_40Road=	{
			/*next*/					&R1_40_68Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_39_Kosan,
			/*suppliee*/				&N1_40_Hoeyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_40_68Road=	{
			/*next*/					&R1_70_12Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_40_Hoeyang,
			/*suppliee*/				&N1_68_Changdo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_70_12Road=	{
			/*next*/					&R1_68_38Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_70_Hwachon,
			/*suppliee*/				&N2_12_Chuncheon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Hwachon2Chuncheon,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD16			//MS 02MAR99
								},
T::R1_68_38Road=	{
			/*next*/					&R1_38_69Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_68_Changdo,
			/*suppliee*/				&N1_38_Kumhwa,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_ROAD_Changdo2Kumhwa,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD17			//MS 02MAR99
								},
T::R1_38_69Road=	{
			/*next*/					&R1_38_12Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_38_Kumhwa,
			/*suppliee*/				&N1_69_Kalmal,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},

//DON'T THINK THIS SHOULD BE USED								//MS 18Jun99
T::R1_38_12Road=	{
			/*next*/					&R1_69_49Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_38_Kumhwa,
			/*suppliee*/				&N2_12_Chuncheon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_69_49Road=	{
			/*next*/					&R1_30_7Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_69_Kalmal,		//####
			/*suppliee*/				&N2_49_Pochon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},

T::R1_30_7Road=	{
			/*next*/					&R1_39_67Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_30_Nampo,
			/*suppliee*/				&N1_7_Pyongyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_39_67Rail=	{
			/*next*/					&R1_67_28Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_39_Kosan,
			/*suppliee*/				&N1_67_Sepo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_67_28Rail=	{
			/*next*/					&R1_28_43Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_67_Sepo,
			/*suppliee*/				&N1_28_Pyonggang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Sepo2Pyonggang,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL11			//MS 02MAR99
								},
T::R1_28_43Rail=	{
			/*next*/					&R1_38_43Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_28_Pyonggang,
			/*suppliee*/				&N1_43_Chorwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_38_43Rail=	{
			/*next*/					&R1_43_56Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_38_Kumhwa,
			/*suppliee*/				&N1_43_Chorwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
								},
T::R1_43_56Rail=	{
			/*next*/					&R1_56_11Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_43_Chorwon,
			/*suppliee*/				&N1_56_Yonchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Chorwon2Yonchon,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL12			//MS 02MAR99
						},
T::R1_56_11Rail=	{
			/*next*/					&R1_28_38Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_56_Yonchon,
			/*suppliee*/				&N2_11_Uijongbu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlImjin,
			/*associated_brdgtext*/		IDS_BrXXImjin,
			/*populatebf*/				FIL_1_BRIDGE27
						},
T::R1_28_38Rail=		{//there is no rail link between pyonggang and kumhwa
			/*next*/					&R1_28_38Road,
			/*alternateroute*/			&R1_28_38Road,
			/*supplier*/				&N1_28_Pyonggang,
			/*suppliee*/				&N1_38_Kumhwa,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R1_28_38Road=	{
			/*next*/					&R2_40_10Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_28_Pyonggang,
			/*suppliee*/				&N1_38_Kumhwa,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},


//-------------------------------------------------------------------------------
//Supply routes for area 2
T::R2_40_10Rail=	{
			/*next*/					&R2_40_10Road0,
			/*alternateroute*/			&R2_40_10Road0,
			/*supplier*/				&N2_40_Munsan,			//####
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				UID_RAIL_Munsan2Seoul,	//UID_BrRlMunsan, ms feb 99//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL13			//MS 02MAR99
							},
T::R2_40_10Road0=	{
			/*next*/					&R2_40_10Road1,
			/*alternateroute*/			&R2_40_10Road1,
			/*supplier*/				&N2_40_Munsan,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Munsan2Seoul,	//UID_BrRdMunsan0,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD18		//MS 02MAR99
							},
T::R2_40_10Road1=	{
			/*next*/					&R2_40_10Road2,
			/*alternateroute*/			&R2_40_10Road2,
			/*supplier*/				&N2_40_Munsan,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_NULL,	//UID_BrRdMunsan1,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_40_10Road2=	{
			/*next*/					&R2_10_7Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_40_Munsan,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_NULL,	//UID_BrRdMunsan2,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_10_7Rail=	{
			/*next*/					&R2_10_7Road0,
			/*alternateroute*/			&R2_10_7Road0,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSeoul,
			/*associated_brdgtext*/		IDS_BrXXSeoul,
			/*populatebf*/				FIL_1_BRIDGE28
							},
T::R2_10_7Road0=	{
			/*next*/					&R2_6_36Road,
			/*alternateroute*/			&R2_10_7Road1,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSeoul0,
			/*associated_brdgtext*/		IDS_BrXXSeoul,
//CAN'T POPULATE ALTERNATE BRIDGES!
//DEADCODE JIM 28/06/99 			/*populatebf*/				FIL_1_BRIDGE29
							},
T::R2_6_36Road=	{
			/*next*/					&R2_5_36Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_6_Wonju,
			/*suppliee*/				&N3_36_Mokkye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_5_36Road=	{
			/*next*/					&R2_10_7Road1,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_5_Chechon,
			/*suppliee*/				&N3_36_Mokkye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_10_7Road1=	{
			/*next*/					&R2_10_7Road2,
			/*alternateroute*/			&R2_10_7Road2,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_ROAD_Seoul2Suwon,	//MS 14May99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_NULL,				//MS 14May99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD29
							},
T::R2_10_7Road2=	{
			/*next*/					&R2_10_7Road3,
			/*alternateroute*/			&R2_10_7Road3,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,	//UID_BrRdSeoul3,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_10_7Road3=	{
			/*next*/					&R2_10_7Road4,
			/*alternateroute*/			&R2_10_7Road4,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,	//UID_Seoul4,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_10_7Road4=	{
			/*next*/					&R2_10_7Road5,
			/*alternateroute*/			&R2_10_7Road5,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,	//UID_BrRdSeoul5,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_10_7Road5=	{
			/*next*/					&R2_7_14Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,	//UID_BrRdSeoul6,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_7_14Rail=	{
			/*next*/					&R2_7_14Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_7_Suwon,
			/*suppliee*/				&N2_14_Osan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_7_14Road=	{
			/*next*/					&R2_14_19Rail,
			/*alternateroute*/			&R2_7_14Rail,			//MS 18Jun99
			/*supplier*/				&N2_7_Suwon,
			/*suppliee*/				&N2_14_Osan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Suwon2Osan,	//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD19		//MS 02MAR99
							},
T::R2_14_19Rail=	{
			/*next*/					&R2_14_19Road,
			/*alternateroute*/			&R2_14_19Road,
			/*supplier*/				&N2_14_Osan,
			/*suppliee*/				&N3_19_Pyongtaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_14_19Road=	{
			/*next*/					&R2_29_28Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_14_Osan,
			/*suppliee*/				&N3_19_Pyongtaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Osan2Pyongtaek,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD20		//MS 02MAR99
							},
T::R2_29_28Road=	{
			/*next*/					&R2_28_30Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_29_Kangnung,
			/*suppliee*/				&N2_28_Samchok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_28_30Road=	{
			/*next*/					&R2_62_30Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_28_Samchok,
			/*suppliee*/				&N3_30_Ulhin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_62_30Road=	{
			/*next*/					&R2_11_10Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_62_Noktong,
			/*suppliee*/				&N3_30_Ulhin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_11_10Rail=	{
			/*next*/					&R2_11_10Road,
			/*alternateroute*/			&R2_11_10Road,
			/*supplier*/				&N2_11_Uijongbu,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_RAIL_Uijongbu2Seoul,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_RAIL14		//MS 02MAR99
							},
T::R2_11_10Road=	{
			/*next*/					&R2_49_11Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_11_Uijongbu,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Uijongbu2Seoul,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD21		//MS 02MAR99
							},
T::R2_49_11Road=	{
			/*next*/					&R2_48_10Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_49_Pochon,
			/*suppliee*/				&N2_11_Uijongbu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Pochon2Uijongbu,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD30		//MS 02MAR99
			
							},
T::R2_48_10Rail=	{
			/*next*/					&R2_48_10Road,
			/*alternateroute*/			&R2_48_10Road,
			/*supplier*/				&N2_48_Kuri,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_RAIL_Kuri2Seoul, //UID_BrRlHan,//MS 02Mar99
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,				//MS 14May99
			/*populatebf*/				FIL_1_BRIDGE30		//MS 02MAR99
							},
T::R2_48_10Road=	{
			/*next*/					&R2_11_48Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_48_Kuri,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Kuri2Seoul,	//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD22		//MS 02MAR99
							},
T::R2_11_48Road=	{
			/*next*/					&R2_12_35Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_11_Uijongbu,
			/*suppliee*/				&N2_48_Kuri,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_12_35Road=	{
			/*next*/					&R2_35_23Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_12_Chuncheon,
			/*suppliee*/				&N2_35_Hongchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Chuncheon2Hongchon,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD23		//MS 02MAR99
							},
T::R2_35_23Road=	{
			/*next*/					&R2_34_23Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_35_Hongchon,
			/*suppliee*/				&N2_23_Hoensong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Hongchon2Hoensong,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD24		//MS 02MAR99
							},
T::R2_34_23Road=	{
			/*next*/					&R2_42_28Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_34_Yulchon,
			/*suppliee*/				&N2_23_Hoensong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_ROAD_Yulchon2Hoensong,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD25		//MS 02MAR99
							},

T::R2_42_28Road=	{
			/*next*/					&R2_10_9Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_42_Chongson,
			/*suppliee*/				&N2_28_Samchok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_10_9Road=	{
			/*next*/					&R2_43_5Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_9_Inchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_43_5Road=	{
			/*next*/					&R2_23_6Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_43_Pyongchang,
			/*suppliee*/				&N3_5_Chechon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_23_6Road=	{
			/*next*/					&R2_8_41Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_23_Hoensong,
			/*suppliee*/				&N2_6_Wonju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_ROAD_Hoensong2Wonju,//MS 02Mar99
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD26		//MS 02MAR99
							},
T::R2_8_41Road=	{
			/*next*/					&R2_41_26Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_8_Songnam,
			/*suppliee*/				&N2_41_Ichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_41_26Road=	{
			/*next*/					&R2_26_4Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_41_Ichon,
			/*suppliee*/				&N3_26_Changhowon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_26_4Road=	{
			/*next*/					&R2_34_43Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_26_Changhowon,
			/*suppliee*/				&N3_4_Chungju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_34_43Road=	{
			/*next*/					&R2_6_43Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_34_Yulchon,
			/*suppliee*/				&N2_43_Pyongchang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_6_43Road=	{
			/*next*/					&R2_43_42Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_6_Wonju,
			/*suppliee*/				&N2_43_Pyongchang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_43_42Road=	{
			/*next*/					&R2_10_8Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_43_Pyongchang,
			/*suppliee*/				&N2_42_Chongson,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_10_8Road=	{
			/*next*/					&R2_28_44Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N3_8_Songnam,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRlHan,
			/*associated_brdgtext*/		IDS_BrXXHan,			//MS 30Apr99
			/*populatebf*/				FIL_NULL
							},
T::R2_28_44Road=	{
			/*next*/					&R2_14_41Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_28_Samchok,
			/*suppliee*/				&N3_44_Taepaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_14_41Road=	{
			/*next*/					&R2_7_8Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_14_Osan,
			/*suppliee*/				&N2_41_Ichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_7_8Road=	{	//REVERSED 									//MS 02Jun99
			/*next*/					&R2_9_7Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_8_Songnam,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_9_7Road=	{
			/*next*/					&R2_57_34Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_9_Inchon,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_57_34Road=	{
			/*next*/					&R2_29_34Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_57_Sangnam,
			/*suppliee*/				&N2_34_Yulchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_ROAD_Sangnam2Yulchon,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD27
							},
T::R2_29_34Road=	{
			/*next*/					&R2_10_58Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_29_Kangnung,
			/*suppliee*/				&N2_34_Yulchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_ROAD_Kangnung2Yulchon,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_1_ROAD28			//DAW 01Jun99
							},
T::R2_10_58Rail=	{
			/*next*/					&R2_58_6Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_58_Yangpyong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlPukhan0, //UID_BrRlHan,//MS 04Feb99
			/*associated_brdgtext*/		IDS_BrXXPukhan0,
			/*populatebf*/				FIL_1_BRIDGE31
							},
T::R2_58_6Rail=	{
			/*next*/					&R2_12_48Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_58_Yangpyong,
			/*suppliee*/				&N2_6_Wonju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_12_48Rail=	{
			/*next*/					&R2_12_48Road0,
			/*alternateroute*/			&R2_12_48Road0,
			/*supplier*/				&N2_12_Chuncheon,
			/*suppliee*/				&N2_48_Kuri,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlKapyong,	//UID_BrRlPukhan0,//MS 04Feb99
			/*associated_brdgtext*/		IDS_BrXXKapyong,
			/*populatebf*/				FIL_1_BRIDGE32
							},
T::R2_12_48Road0=	{
			/*next*/					&R2_12_48Road1,
			/*alternateroute*/			&R2_12_48Road1,
			/*supplier*/				&N2_12_Chuncheon,
			/*suppliee*/				&N2_48_Kuri,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdChuncheon0,
			/*associated_brdgtext*/		IDS_BrXXKapyong,
			/*populatebf*/				FIL_1_BRIDGE33
							},
T::R2_12_48Road1=	{
			/*next*/					&R2_6_5Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_12_Chuncheon,
			/*suppliee*/				&N2_48_Kuri,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,	//UID_BrRdChuncheon1,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R2_6_5Rail=	{
			/*next*/					&R2_23_6Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_6_Wonju,
			/*suppliee*/				&N3_5_Chechon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},


T::R2_23_6Rail=	{
			/*next*/					&R3_19_3Rail,
			/*alternateroute*/			&R2_23_6Road,
			/*supplier*/				&N2_23_Hoensong,
			/*suppliee*/				&N2_6_Wonju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
//-------------------------------------------------------------------------------
//Supply routes for area 3
T::R3_19_3Rail=	{
			/*next*/					&R3_19_3Road,
			/*alternateroute*/			&R3_19_3Road,
			/*supplier*/				&N3_19_Pyongtaek,
			/*suppliee*/				&N3_3_Chonan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_19_3Road=	{
			/*next*/					&R3_3_17Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_19_Pyongtaek,
			/*suppliee*/				&N3_3_Chonan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_3_17Rail=	{
			/*next*/					&R3_3_17Road,
			/*alternateroute*/			&R3_3_17Road,
			/*supplier*/				&N3_3_Chonan,
			/*suppliee*/				&N3_17_Chochiwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlChonui,
			/*associated_brdgtext*/		IDS_BrXXChonui,
			/*populatebf*/				FIL_1_BRIDGE34
							},
T::R3_3_17Road=	{
			/*next*/					&R3_17_1Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_3_Chonan,
			/*suppliee*/				&N3_17_Chochiwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_17_1Rail=	{
			/*next*/					&R3_4_59Rail,
			/*alternateroute*/			&R3_17_1Road,
			/*supplier*/				&N3_17_Chochiwon,
			/*suppliee*/				&N3_1_Taejon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL,	//UID_BrRlKum0,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
//DeadCode MS 02May99 T::R3_3_64Rail=	{
//DeadCode MS 02May99 			/*next*/					&R3_64_65Rail,
//DeadCode MS 02May99 			/*alternateroute*/			NULL,
//DeadCode MS 02May99 			/*supplier*/				&N3_3_Chonan,
//DeadCode MS 02May99 			/*suppliee*/				&N3_64_Hongsong,
//DeadCode MS 02May99 			/*status*/					SR_ACTIVE,
//DeadCode MS 02May99 			/*recommision_time*/		DAYS0,
//DeadCode MS 02May99 			/*redsupplyUID*/				UID_NULL,
//DeadCode MS 02May99 			/*storespermobile*/			STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*associated_brdg*/			UID_Null,
//DeadCode MS 02May99 			/*associated_brdgtext*/		IDS_NOINFO,
//DeadCode MS 02May99 			/*populatebf*/				FIL_NULL
//DeadCode MS 02May99 							},
//DeadCode MS 02May99 T::R3_64_65Rail=	{
//DeadCode MS 02May99 			/*next*/					&R3_65_66Rail,
//DeadCode MS 02May99 			/*alternateroute*/			NULL,
//DeadCode MS 02May99 			/*supplier*/				&N3_64_Hongsong,
//DeadCode MS 02May99 			/*suppliee*/				&N3_65_Hannae,
//DeadCode MS 02May99 			/*status*/					SR_ACTIVE,
//DeadCode MS 02May99 			/*recommision_time*/		DAYS0,
//DeadCode MS 02May99 			/*redsupplyUID*/				UID_NULL,
//DeadCode MS 02May99 			/*storespermobile*/			STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*associated_brdg*/			UID_Null,
//DeadCode MS 02May99 			/*associated_brdgtext*/		IDS_NOINFO,
//DeadCode MS 02May99 			/*populatebf*/				FIL_NULL
//DeadCode MS 02May99 							},
//DeadCode MS 02May99 T::R3_65_66Rail=	{
//DeadCode MS 02May99 			/*next*/					&R3_4_59Rail,
//DeadCode MS 02May99 			/*alternateroute*/			NULL,
//DeadCode MS 02May99 			/*supplier*/				&N3_65_Hannae,
//DeadCode MS 02May99 			/*suppliee*/				&N3_66_Taechon,
//DeadCode MS 02May99 			/*status*/					SR_ACTIVE,
//DeadCode MS 02May99 			/*recommision_time*/		DAYS0,
//DeadCode MS 02May99 			/*redsupplyUID*/				UID_NULL,
//DeadCode MS 02May99 			/*storespermobile*/			STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*associated_brdg*/			UID_Null,
//DeadCode MS 02May99 			/*associated_brdgtext*/		IDS_NOINFO,
//DeadCode MS 02May99 			/*populatebf*/				FIL_NULL
//DeadCode MS 02May99 							},
T::R3_4_59Rail=	{
			/*next*/					&R3_17_1Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_4_Chungju,
			/*suppliee*/				&N3_59_Koesan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_17_1Road=	{
			/*next*/					&R3_62_16Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_17_Chochiwon,
			/*suppliee*/				&N3_1_Taejon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_NULL,	//UID_BrRdKum1,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},

T::R3_62_16Road=	{
			/*next*/					&R3_36_4Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_62_Noktong,
			/*suppliee*/				&N3_16_Yongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_36_4Road=	{
			/*next*/					&R3_44_62Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_36_Mokkye,
			/*suppliee*/				&N3_4_Chungju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,	//UID_BrRdChungju,//MS 19Jan99
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_44_62Road=	{
			/*next*/					&R3_24_21Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_44_Taepaek,
			/*suppliee*/				&N3_62_Noktong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_24_21Road=	{
			/*next*/					&R3_21_22Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_24_Chomchon,
			/*suppliee*/				&N3_21_Sangju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_21_22Road=	{
			/*next*/					&R3_20_24Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_21_Sangju,
			/*suppliee*/				&N3_22_Kimchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_20_24Road=	{
			/*next*/					&R3_41_51Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_20_Yechon,
			/*suppliee*/				&N3_24_Chomchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_41_51Road=	{
			/*next*/					&R3_60_24Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_41_Ichon,
			/*suppliee*/				&N3_51_Maesan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_60_24Road=	{
			/*next*/					&R3_1_46Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_60_Mungyong,
			/*suppliee*/				&N3_24_Chomchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_1_46Rail=	{
			/*next*/					&R3_1_46Road,
			/*alternateroute*/			&R3_1_46Road,
			/*supplier*/				&N3_1_Taejon,
			/*suppliee*/				&N3_46_Yongdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_1_46Road=	{
			/*next*/					&R3_55_37Road,			//MS 02May99
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_1_Taejon,
			/*suppliee*/				&N3_46_Yongdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_NULL																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
//DeadCode MS 02May99 T::R3_45_1Rail=	{
//DeadCode MS 02May99 			/*next*/					&R3_55_37Road,
//DeadCode MS 02May99 			/*alternateroute*/			NULL,
//DeadCode MS 02May99 			/*supplier*/				&N3_45_Nonsan,
//DeadCode MS 02May99 			/*suppliee*/				&N3_1_Taejon,
//DeadCode MS 02May99 			/*status*/					SR_ACTIVE,
//DeadCode MS 02May99 			/*recommision_time*/		DAYS0,
//DeadCode MS 02May99 			/*redsupplyUID*/				UID_NULL,
//DeadCode MS 02May99 			/*storespermobile*/			STORES_TRUCK,
//DeadCode MS 02May99 			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//DeadCode MS 02May99 			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//DeadCode MS 02May99 			/*associated_brdg*/			UID_Null																	,
//DeadCode MS 02May99 			/*associated_brdgtext*/		IDS_NOINFO,
//DeadCode MS 02May99 			/*populatebf*/				FIL_NULL
//DeadCode MS 02May99 							},
//DeadCode MS 02May99 T::R3_63_45Rail=	{
//DeadCode MS 02May99 			/*next*/					&R3_66_63Rail,
//DeadCode MS 02May99 			/*alternateroute*/			NULL,
//DeadCode MS 02May99 			/*supplier*/				&N3_63_Kunsan,
//DeadCode MS 02May99 			/*suppliee*/				&N3_45_Nonsan,
//DeadCode MS 02May99 			/*status*/					SR_ACTIVE,
//DeadCode MS 02May99 			/*recommision_time*/		DAYS0,
//DeadCode MS 02May99 			/*redsupplyUID*/				UID_NULL,
//DeadCode MS 02May99 			/*storespermobile*/			STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*associated_brdg*/			UID_Null																	,
//DeadCode MS 02May99 			/*associated_brdgtext*/		IDS_NOINFO,
//DeadCode MS 02May99 			/*populatebf*/				FIL_NULL
//DeadCode MS 02May99 							},
//DeadCode MS 02May99 T::R3_66_63Rail=	{
//DeadCode MS 02May99 			/*next*/					&R3_55_37Road,
//DeadCode MS 02May99 			/*alternateroute*/			NULL,
//DeadCode MS 02May99 			/*supplier*/				&N3_66_Taechon,
//DeadCode MS 02May99 			/*suppliee*/				&N3_63_Kunsan,
//DeadCode MS 02May99 			/*status*/					SR_ACTIVE,
//DeadCode MS 02May99 			/*recommision_time*/		DAYS0,
//DeadCode MS 02May99 			/*redsupplyUID*/				UID_NULL,
//DeadCode MS 02May99 			/*storespermobile*/			STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode MS 02May99 			/*associated_brdg*/			UID_Null																	,
//DeadCode MS 02May99 			/*associated_brdgtext*/		IDS_NOINFO,
//DeadCode MS 02May99 			/*populatebf*/				FIL_NULL
//DeadCode MS 02May99 							},
T::R3_55_37Road=	{
			/*next*/					&R3_18_55Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_55_Uisong,
			/*suppliee*/				&N3_37_Kumi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_18_55Road=	{
			/*next*/					&R3_61_16Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_18_Andong,
			/*suppliee*/				&N3_55_Uisong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_61_16Road=	{
			/*next*/					&R3_59_2Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_61_Tanyang,
			/*suppliee*/				&N3_16_Yongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_59_2Rail=	{
			/*next*/					&R3_2_1Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_59_Koesan,
			/*suppliee*/				&N3_2_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_2_1Rail=	{
			/*next*/					&R3_4_61Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_2_Chongju,
			/*suppliee*/				&N3_1_Taejon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_4_61Road=	{
			/*next*/					&R3_52_53Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_4_Chungju,
			/*suppliee*/				&N3_61_Tanyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_52_53Road=	{
			/*next*/					&R3_51_52Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_52_Kwangheywan,
			/*suppliee*/				&N3_53_Chinchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_51_52Road=	{
			/*next*/					&R3_53_54Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_51_Maesan,
			/*suppliee*/				&N3_52_Kwangheywan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_53_54Road=	{
			/*next*/					&R3_54_2Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_53_Chinchon,
			/*suppliee*/				&N3_54_Chungpyong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_54_2Road=	{
			/*next*/					&R3_4_60Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_54_Chungpyong,
			/*suppliee*/				&N3_2_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_4_60Road=	{
			/*next*/					&R3_46_22Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_4_Chungju,
			/*suppliee*/				&N3_60_Mungyong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_46_22Rail=	{
			/*next*/					&R3_46_22Road,
			/*alternateroute*/			&R3_46_22Road,
			/*supplier*/				&N3_46_Yongdong,
			/*suppliee*/				&N3_22_Kimchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_46_22Road=	{
			/*next*/					&R3_18_20Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_46_Yongdong,
			/*suppliee*/				&N3_22_Kimchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_18_20Road=	{
			/*next*/					&R3_22_37Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_18_Andong,
			/*suppliee*/				&N3_20_Yechon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_22_37Road=	{
			/*next*/					&R3_30_31Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_22_Kimchon,
			/*suppliee*/				&N3_37_Kumi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_30_31Road=	{
			/*next*/					&R3_31_32Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_30_Ulhin,
			/*suppliee*/				&N3_31_Yonghae,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_31_32Road=	{
			/*next*/					&R3_32_25Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_31_Yonghae,
			/*suppliee*/				&N3_32_Yongdok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_32_25Road=	{
			/*next*/					&R3_5_47Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_32_Yongdok,
			/*suppliee*/				&N3_25_Pohang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null																	,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_5_47Rail=	{
			/*next*/					&R3_47_16Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_5_Chechon,
			/*suppliee*/				&N3_47_Punggi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_47_16Rail=	{
			/*next*/					&R3_47_16Road,
			/*alternateroute*/			&R3_47_16Road,
			/*supplier*/				&N3_47_Punggi,
			/*suppliee*/				&N3_16_Yongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_47_16Road=	{
			/*next*/					&R3_16_18Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_47_Punggi,
			/*suppliee*/				&N3_16_Yongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_16_18Rail=	{
			/*next*/					&R3_2_17Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_16_Yongju,
			/*suppliee*/				&N3_18_Andong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_2_17Rail=	{
			/*next*/					&R3_16_18Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_2_Chongju,
			/*suppliee*/				&N3_17_Chochiwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},
T::R3_16_18Road=	{
			/*next*/					&R3_18_25Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_16_Yongju,
			/*suppliee*/				&N3_18_Andong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},

//THIS ROUTE HAS BEEN COMMANDERED BY MARK						//MS 22Apr99
//NOW LINKS 37 KUMI TO XXTaegu									//MS 09Jun99
T::R3_18_25Rail=	{
			/*next*/					&R_Fake00,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_37_Kumi,			//MS 09Jun99
			/*suppliee*/				&N3_XX_Taegu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/				UID_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
							},

//NEW DUMMY LINKS WITH ZERO CAPACITY TO STRAIGHTEN LINE OUT		//RDH 14May99

T::R_Fake00=	{
			/*next*/					&R_Fake02,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_52_Kwangheywan,		
			/*suppliee*/				&N3_19_Pyongtaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		0,
			/*maxcapacitysummer*/		0,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},

T::R_Fake02=	{
			/*next*/					&R_Fake03,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_58_Yangpyong,		//MS 02Jun99
			/*suppliee*/				&N2_23_Hoensong,		//MS 02Jun99
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		0,
			/*maxcapacitysummer*/		0,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},

T::R_Fake03=	{												//MS 08Jun99
			/*next*/					&R_Fake04,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_69_Kalmal,		
			/*suppliee*/				&N1_70_Hwachon,	
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		0,
			/*maxcapacitysummer*/		0,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},

T::R_Fake04=	{												//MS 08Jun99
			/*next*/					&R_Fake05,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_56_Yonchon,
			/*suppliee*/				&N1_27_Kaesong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		0,
			/*maxcapacitysummer*/		0,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},

T::R_Fake05=	{												//MS 09Jun99
			/*next*/					&R_Fake06,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_40_Hoeyang,
			/*suppliee*/				&N1_67_Sepo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		0,
			/*maxcapacitysummer*/		0,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},

T::R_Fake06=	{												//MS 09Jun99
			/*next*/					&R_Fake07,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_62_Chaeryong,
			/*suppliee*/				&N1_22_Sariwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		0,
			/*maxcapacitysummer*/		0,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},

T::R_Fake07=	{												//MS 09Jun99
			/*next*/					&R_Fake01,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_37_Kumi,
			/*suppliee*/				&N3_1_Taejon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		0,
			/*maxcapacitysummer*/		0,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},

T::R_Fake01=	{
			/*next*/					&LastRoute,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_26_Changhowon,		
			/*suppliee*/				&N3_51_Maesan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyUID*/			UID_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		0,
			/*maxcapacitysummer*/		0,
			/*associated_brdg*/			UID_Null,
			/*associated_brdgtext*/		IDS_NOINFO,
			/*populatebf*/				FIL_NULL
			},


T::LastRoute=	{
			/*next*/					&LastRoute,
			/*alternateroute*/			NULL,
			/*supplier*/				NULL,
			/*suppliee*/				NULL,
			/*status*/					SR_LASTONE,
			};

//T::R1_62_23Rail=	{
//			/*next*/					&R1_15_53Road,
//			/*alternateroute*/			NULL,
//			/*supplier*/				&N1_62_Chaeryong,
//			/*suppliee*/				&N1_23_Changyon,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R0_9_19Road=	{
//			/*next*/					&R0_9_59Road,
//			/*alternateroute*/			NULL,	//&R0_9_59Road,
//			/*supplier*/				&N0_9_Kangye,
//			/*suppliee*/				&N0_19_Hamhung,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRUCK,
//			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*associated_brdg*/			UID_BrRdChangig,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R1_30_7Rail=	{
//			/*next*/					&R1_30_7Road,
//			/*alternateroute*/			&R1_30_7Road,
//			/*supplier*/				&N1_30_Nampo,
//			/*suppliee*/				&N1_7_Pyongyang,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//								},

//T::R0_4_5Rail=	{
//			/*next*/					&R0_4_5Road,
//			/*alternateroute*/			&R0_4_5Road,
//			/*supplier*/				&N0_4_Chongju,
//			/*suppliee*/				&N0_5_Sinaju,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		MAJ_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_BrRlTaeryong,
//			/*associated_brdgtext*/		IDS_NOINFO
// 							},

//T::R1_13_29Road=	{
//			/*next*/					&R1_13_54Rail,
//			/*alternateroute*/			NULL,
//			/*supplier*/				&N1_13_Samdung,
//			/*suppliee*/				&N1_29_Kangdong,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRUCK,
//			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R1_12_13Rail=	{
//			/*next*/					&R1_7_49Rail,
//			/*alternateroute*/			NULL,
//			/*supplier*/				&N1_12_Sunchon,
//			/*suppliee*/				&N1_29_Kangdong,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

							//T::R1_38_50Road=	{
//			/*next*/					&R1_25_66Road,
//			/*alternateroute*/			NULL,
//			/*supplier*/				&N1_38_Kumhwa,
//			/*suppliee*/				&N1_50_Yongpyong,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRUCK,
//			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R1_50_12Road=	{
//			/*next*/					&R1_41_28Road,
//			/*alternateroute*/			NULL,
//			/*supplier*/				&N1_50_Yongpyong,
//			/*suppliee*/				&N2_12_Chuncheon,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRUCK,
//			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*associated_brdg*/			UID_BrRdPukhan1,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R1_13_14Rail=	{
//			/*next*/					&R1_13_14Road,
//			/*alternateroute*/			&R1_13_14Road,
//			/*supplier*/				&N1_13_Samdung,
//			/*suppliee*/				&N1_14_WaDong,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//								},

//T::R1_13_14Road=	{
//			/*next*/					&R1_14_15Rail,
//			/*alternateroute*/			NULL,
//			/*supplier*/				&N1_13_Samdung,
//			/*suppliee*/				&N1_14_WaDong,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRUCK,
//			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//								},

//T::R1_38_70Rail=		{//there is no rail between kumhwa and hwachon redundant
//			/*next*/					&R1_70_12Rail,
//			/*alternateroute*/			&R1_38_70Road,
//			/*supplier*/				&N1_38_Kumhwa,
//			/*suppliee*/				&N1_70_Hwachon,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R1_70_12Rail=		{	//there is no rail between hwachon and chuncheon
//			/*next*/					&R2_40_10Rail,
//			/*alternateroute*/			&R1_70_12Road,
//			/*supplier*/				&N1_70_Hwachon,
//			/*suppliee*/				&N2_12_Chuncheon,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R2_40_11Road=	{
//			/*next*/					&R2_42_28Road,
//			/*alternateroute*/			NULL,
//			/*supplier*/				&N2_40_Munsan,
//			/*suppliee*/				&N2_11_Uijongbu,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRUCK,
//			/*maxcapacitywinter*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
//			/*maxcapacitysummer*/		MIN_TRUCKSPERDAY*STORES_TRUCK,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R2_12_35Rail=	{
//			/*next*/					&R2_35_23Rail,
//			/*alternateroute*/			&R2_12_35Road,
//			/*supplier*/				&N2_12_Chuncheon,
//			/*suppliee*/				&N2_35_Hongchon,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R2_35_23Rail=	{
//			/*next*/					&R2_23_6Rail,
//			/*alternateroute*/			&R2_35_23Road,
//			/*supplier*/				&N2_35_Hongchon,
//			/*suppliee*/				&N2_23_Hoensong,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//							},

//T::R3_62_16Rail=	{
//			/*next*/					&R3_62_16Road,
//			/*alternateroute*/			&R3_62_16Road,
//			/*supplier*/				&N3_62_Noktong,
//			/*suppliee*/				&N3_16_Yongju,
//			/*status*/					SR_ACTIVE,
//			/*recommision_time*/		DAYS0,
//			/*redsupplyUID*/				UID_NULL,
//			/*storespermobile*/			STORES_TRAIN,
//			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//			/*associated_brdg*/			UID_Null,
//			/*associated_brdgtext*/		IDS_NOINFO
//								},

//DeadCode DAW 19Nov98 T::R1_75_40Rail=	{
//DeadCode DAW 19Nov98 			/*next*/					&R1_75_40Road,
//DeadCode DAW 19Nov98 			/*alternateroute*/			&R1_75_40Road,
//DeadCode DAW 19Nov98 			/*supplier*/				&N1_75_Panmunjom,
//DeadCode DAW 19Nov98 			/*suppliee*/				&N2_40_Munsan,
//DeadCode DAW 19Nov98 			/*status*/					SR_ACTIVE,
//DeadCode DAW 19Nov98 			/*recommision_time*/		DAYS0,
//DeadCode DAW 19Nov98 			/*redsupplyUID*/				UID_NULL,
//DeadCode DAW 19Nov98 			/*storespermobile*/			STORES_TRAIN,
//DeadCode DAW 19Nov98 			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode DAW 19Nov98 			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//DeadCode DAW 19Nov98 			/*associated_brdg*/			UID_Null,
//DeadCode DAW 19Nov98 			/*associated_brdgtext*/		IDS_NOINFO
//DeadCode DAW 19Nov98 								},
//DeadCode DAW 19Nov98 T::R1_75_40Road=	{
//DeadCode DAW 19Nov98 			/*next*/					&R1_34_20Rail,
//DeadCode DAW 19Nov98 			/*alternateroute*/			NULL,
//DeadCode DAW 19Nov98 			/*supplier*/				&N1_75_Panmunjom,
//DeadCode DAW 19Nov98 			/*suppliee*/				&N2_40_Munsan,
//DeadCode DAW 19Nov98 			/*status*/					SR_ACTIVE,
//DeadCode DAW 19Nov98 			/*recommision_time*/		DAYS0,
//DeadCode DAW 19Nov98 			/*redsupplyUID*/				UID_NULL,
//DeadCode DAW 19Nov98 			/*storespermobile*/			STORES_TRUCK,
//DeadCode DAW 19Nov98 			/*maxcapacitywinter*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//DeadCode DAW 19Nov98 			/*maxcapacitysummer*/		MAJ_TRUCKSPERDAY*STORES_TRUCK,
//DeadCode DAW 19Nov98 			/*associated_brdg*/			UID_Null,
//DeadCode DAW 19Nov98 			/*associated_brdgtext*/		IDS_NOINFO
//DeadCode DAW 19Nov98 								},

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//
//
//
//
//
SupplyLine
T::WestRoute = {
			/*AssociatedDepot[2]*/			{UID_WhRdSinuiju,UID_MyRdPyongyang},
			/*firstnode*/					&N0_0_Dangdong,
//			/*splitsAB and BC*/				&N1_22_Sariwon,&N2_10_Seoul,
			/*MaxMobiles*/					MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*TodaysMobiles*/				MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*CurrMobiles*/					0,
			/*frontline*/					&N2_40_Munsan,
			/*attackpotential*/				0,
			/*Callsigns*/					Call_TAC1,Call_FAC1,false,
	REDINITIATIVE
			},
T::CentralRoute = {
			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
			/*firstnode*/					&China_C,
//			/*splitsAB and BC*/				&N3_53_Chinchon,&N2_11_Uijongbu,
			/*MaxMobiles*/					MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*TodaysMobiles*/				MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*CurrMobiles*/					0,
			/*frontline*/					&N1_56_Yonchon,
			/*attackpotential*/				0,
			/*Callsigns*/					Call_TAC2,Call_FAC2,true,
	REDINITIATIVE
			},
T::EastRoute = {
			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
			/*firstnode*/					&China_E,
//			/*splitsAB and BC*/				&N1_21_Wonsan,&N2_28_Samchok,
			/*MaxMobiles*/					MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*TodaysMobiles*/				MAJ_TRUCKSPERDAY*STORES_TRUCK,
			/*CurrMobiles*/					0,
			/*frontline*/					&N2_42_Chongson,
			/*attackpotential*/				0,
			/*Callsigns*/					Call_TAC0,Call_FAC0,false,
			},
*T::supplylines[4]={&EastRoute,&CentralRoute,&WestRoute};
			
//DeadCode RDH 13Mar97 WestRoute = {
//DeadCode RDH 13Mar97			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
//DeadCode RDH 13Mar97			/*MaxMobiles*/					MAXMOBILESONSINGLEROAD,
//DeadCode RDH 13Mar97			/*TodaysMobiles*/				MAXMOBILESONSINGLEROAD,
//DeadCode RDH 13Mar97			/*CurrMobiles*/					0,
//DeadCode RDH 13Mar97			/*frontline*/					&N1_6_Sukchon,
//DeadCode RDH 13Mar97			/*attackpotential*/				0,
//DeadCode RDH 13Mar97			},
//DeadCode RDH 13Mar97 EastRoute = {
//DeadCode RDH 13Mar97			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
//DeadCode RDH 13Mar97			/*MaxMobiles*/					MAXMOBILESONSINGLEROAD,
//DeadCode RDH 13Mar97			/*TodaysMobiles*/				MAXMOBILESONSINGLEROAD,
//DeadCode RDH 13Mar97			/*CurrMobiles*/					0,
//DeadCode RDH 13Mar97			/*frontline*/					&N2_49_Pochon,
//DeadCode RDH 13Mar97			/*attackpotential*/				0,
//DeadCode RDH 13Mar97			};
//------------------------------------------------------------------------------
AirFieldInfo	T::airfieldinfo[] =								//MS 18Jun99
{
		{//0
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdSinmak,
			/*airfieldtext*/	IDS_AfXXSinmak,
			/*northnodes[2]*/	{&N1_65_Nuang,&N1_22_Sariwon},
			/*southnodes[2]*/	{&N1_61_Yonan,&N1_26_Kumchon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLSINMAK,FIL_1_RDSINMAK,FIL_1_AFSINMAK,FIL_AFBUZZ01,
			/*factorsPC*/		25,20,7,13,						//MS 14Jun99
		},
		{//1
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdHwangju,
			/*airfieldtext*/	IDS_AfXXHwangju,
			/*northnodes[2]*/	{&N1_64_Sangwon,&N1_49_Hwangju},
			/*southnodes[2]*/	{&N1_22_Sariwon,&N1_65_Nuang},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLHWANGJ,FIL_1_RDHWANGJ,FIL_1_AFHWANGJ,FIL_AFBUZZ01,
			/*factorsPC*/		0,25,6,30,						//MS 14Jun99
		},
		{//2
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdSinuiju,
			/*airfieldtext*/	IDS_AfXXSinuiju,
			/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_46_Chongsongup},
			/*southnodes[2]*/	{&N0_2_Yomju,&N0_3_Sonchon},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		3,
			/*populate*/ 		FIL_1_BLSINUIJ,FIL_1_RDSINUIJ,FIL_1_AFSINUIJ,FIL_NULL,
			/*factorsPC*/		0,10,12,25,						//MS 14Jun99
		},
		{//3
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdKangdong,
			/*airfieldtext*/	IDS_AfXXKangdong,
			/*northnodes[2]*/	{&N1_12_Sunchon,&N1_14_WaDong},
			/*southnodes[2]*/	{&N1_29_Kangdong,&N1_13_Samdung},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,			 //POPULATE NEEDS FIXING
			/*populate*/ 		FIL_1_BLKANGDO,FIL_1_RDKANGDO,FIL_1_AFKANGDO,FIL_NULL,
			/*factorsPC*/		30,25,5,25,						//MS 14Jun99
		},
		{//4
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdSunan,
			/*airfieldtext*/	IDS_AfXXSunan,
			/*northnodes[2]*/	{&N1_6_Sukchon,&N1_12_Sunchon},
			/*southnodes[2]*/	{&N1_29_Kangdong,&N1_7_Pyongyang},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		2,
			/*populate*/ 		FIL_1_BLSUNAN,FIL_1_RDSUNAN,FIL_1_AFSUNAN,FIL_NULL,
			/*factorsPC*/		80,20,5,20,						//MS 14Jun99
		},
		{//5
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdAntung,
			/*airfieldtext*/	IDS_AfXXAntung,
			/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},
			/*southnodes[2]*/	{&N0_1_Sinuiju,&N0_3_Sonchon},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		3,
			/*populate*/ 		FIL_1_BLANTUNG,FIL_1_RDANTUNG,FIL_1_AFANTUNG,FIL_NULL,
			/*factorsPC*/		30,20,5,10,						//MS 14Jun99
		},
		{//6
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdTaTung,
			/*airfieldtext*/	IDS_AfXXTaTung,
			/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},
			/*southnodes[2]*/	{&N0_1_Sinuiju,&N0_3_Sonchon},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		3,
			/*populate*/ 		FIL_1_BLTATUNG,FIL_1_RDTATUNG,FIL_1_AFTATUNG,FIL_NULL,
			/*factorsPC*/		30,20,12,12,					//MS 14Jun99
		},
		{//7
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdUiju,
			/*airfieldtext*/	IDS_AfXXUiju,
			/*northnodes[2]*/	{&N0_57_Suiho,&N0_46_Chongsongup},
			/*southnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLUIJU,FIL_1_RDUIJU,FIL_1_AFUIJU,FIL_NULL,
			/*factorsPC*/		30,20,7,25,						//MS 14Jun99
		},
		{//8
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdAnak,
			/*airfieldtext*/	IDS_AfXXAnak,
			/*northnodes[2]*/	{&N1_30_Nampo,&N1_49_Hwangju},
			/*southnodes[2]*/	{&N1_62_Chaeryong,&N1_22_Sariwon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLANAK,FIL_1_RDANAK,FIL_1_AFANAK,FIL_AFBUZZ00,
			/*factorsPC*/		0,0,5,13,						//MS 14Jun99
		},
		{//9
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdSariwon,
			/*airfieldtext*/	IDS_AfXXSariwon,
			/*northnodes[2]*/	{&N1_65_Nuang,&N1_49_Hwangju},
			/*southnodes[2]*/	{&N1_62_Chaeryong,&N1_22_Sariwon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLSARIWO,FIL_1_RDSARIWO,FIL_1_AFSARIWO,FIL_AFBUZZ03,
			/*factorsPC*/		0,0,10,20,						//MS 14Jun99
		},
		{//10
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdYongyu,
			/*airfieldtext*/	IDS_AfXXYongyu,
			/*northnodes[2]*/	{&N1_6_Sukchon,&N1_12_Sunchon},
			/*southnodes[2]*/	{&N1_29_Kangdong,&N1_7_Pyongyang},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLYONGYU,FIL_1_RDYONGYU,FIL_1_AFYONGYU,FIL_NULL,
			/*factorsPC*/		0,0,8,13,						//MS 14Jun99
		},
		{//11
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdSinanju,
			/*airfieldtext*/	IDS_AfXXSinanju,
			/*northnodes[2]*/	{&N0_45_Sakchu,&N0_5_Sinaju},
			/*southnodes[2]*/	{&N1_6_Sukchon,&N1_12_Sunchon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLSINANJ,FIL_1_RDSINANJ,FIL_1_AFSINANJ,FIL_NULL,
			/*factorsPC*/		30,20,5,25,						//MS 14Jun99
		},
		{//12
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdPyongni,
			/*airfieldtext*/	IDS_AfXXPyongni,
			/*northnodes[2]*/	{&N1_12_Sunchon,&N1_6_Sukchon},
			/*southnodes[2]*/	{&N1_29_Kangdong,&N1_7_Pyongyang},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLPYONGN,FIL_1_RDPYONGN,FIL_1_AFPYONGN,FIL_NULL,
			/*factorsPC*/		0,0,9,12,						//MS 14Jun99
		},
		{//13
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdTaechon,
			/*airfieldtext*/	IDS_AfXXTaechon,
			/*northnodes[2]*/	{&N0_48_Kusong,&N0_11_Kujang},
			/*southnodes[2]*/	{&N0_4_Chongju,&N0_4b_Maenjungdong},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		2,
			/*populate*/ 		FIL_1_BLTAECHO,FIL_1_RDTAECHO,FIL_1_AFTAECHO,FIL_NULL,
			/*factorsPC*/		25,15,6,20,						//MS 14Jun99
		},
		{//14
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdNamsi,
			/*airfieldtext*/	IDS_AfXXNamsi,
			/*northnodes[2]*/	{&N0_2_Yomju,&N0_48_Kusong},
			/*southnodes[2]*/	{&N0_3_Sonchon,&N0_4_Chongju},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		2,
			/*populate*/ 		FIL_1_BLNAMSI,FIL_1_RDNAMSI,FIL_1_AFNAMSI,FIL_NULL,
			/*factorsPC*/		0,20,9,20,						//MS 14Jun99
		},
		{//15
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdSaamcham,
			/*airfieldtext*/	IDS_AfXXSaamcham,
			/*northnodes[2]*/	{&N0_11_Kujang,&N0_4_Chongju},
			/*southnodes[2]*/	{&N0_2_Yomju,&N0_31_Tokchon},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		2,
			/*populate*/ 		FIL_1_BLSAAMCH,FIL_1_RDSAAMCH,FIL_1_AFSAAMCH,FIL_NULL,
			/*factorsPC*/		30,20,7,20,						//MS 14Jun99
		},
		{//16
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdPyongyangE,
			/*airfieldtext*/	IDS_AfXXPyongyangE,
			/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_29_Kangdong},
			/*southnodes[2]*/	{&N1_49_Hwangju,&N1_64_Sangwon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLP_EAST,FIL_1_RDP_EAST,FIL_1_AFP_EAST,FIL_NULL,
			/*factorsPC*/		30,20,5,14,						//MS 14Jun99
		},
		{//17
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdPyongyangM,
			/*airfieldtext*/	IDS_AfXXPyongyangM,
			/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_29_Kangdong},
			/*southnodes[2]*/	{&N1_49_Hwangju,&N1_64_Sangwon},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLP_MAIN,FIL_1_RDP_MAIN,FIL_1_AFP_MAIN,FIL_NULL,
			/*factorsPC*/		30,15,7,13,						//MS 14Jun99
		},
		{//18
			/*nationality*/		NAT_RED,
			/*airfield*/		UID_AfRdPyongyangD,
			/*airfieldtext*/	IDS_AfXXPyongyangD,
			/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_29_Kangdong},
			/*southnodes[2]*/	{&N1_49_Hwangju,&N1_30_Nampo},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLP_DOWN,FIL_1_RDP_DOWN,FIL_1_AFP_DOWN,FIL_NULL,
			/*factorsPC*/		0,0,15,70,						//MS 14Jun99
		},
		{//19
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlKimpo,
			/*airfieldtext*/	IDS_AfXXKimpo,
			/*northnodes[2]*/	{&N2_10_Seoul,&N2_40_Munsan},
			/*southnodes[2]*/	{&N2_9_Inchon,&N2_7_Suwon},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		3,
			/*populate*/		FIL_1_BLKIMPO,FIL_1_RDKIMPO,FIL_1_AFKIMPO,FIL_AFBUZZ02,
			/*factorsPC*/		90,15,30,50,					//MS 14Jun99
		},
		{//20
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlSeoul,
			/*airfieldtext*/	IDS_AfXXSeoul,
			/*northnodes[2]*/	{&N2_10_Seoul,&N2_48_Kuri},
			/*southnodes[2]*/	{&N2_9_Inchon,&N2_8_Songnam},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLSEOUL,FIL_1_RDSEOUL,FIL_1_AFSEOUL,FIL_AFBUZZ01,
			/*factorsPC*/		0,0,10,13,						//MS 14Jun99
		},
		{//21
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlChuncheon,
			/*airfieldtext*/	IDS_AfXXChuncheon,
			/*northnodes[2]*/	{&N2_49_Pochon,&N1_70_Hwachon},
			/*southnodes[2]*/	{&N2_48_Kuri,&N2_35_Hongchon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLCHUNCH,FIL_1_RDCHUNCH,FIL_1_AFCHUNCH,FIL_AFBUZZ03,
			/*factorsPC*/		20,20,8,7,						//MS 14Jun99
		},
		{//22
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlOsan,
			/*airfieldtext*/	IDS_AfXXOsan,
			/*northnodes[2]*/	{&N2_14_Osan,&N2_14_Osan},
			/*southnodes[2]*/	{&N3_19_Pyongtaek,&N3_3_Chonan},
			/*AirFieldType*/	AFT_JET,						//MS 23May99
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLOSAN,FIL_1_RDOSAN,FIL_1_AFOSAN,FIL_NULL,
			/*factorsPC*/		15,15,8,11,						//MS 14Jun99
		},
		{//23
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlSuwon,
			/*airfieldtext*/	IDS_AfXXSuwon,
			/*northnodes[2]*/	{&N2_8_Songnam,&N2_7_Suwon},
			/*southnodes[2]*/	{&N3_19_Pyongtaek,&N2_14_Osan},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		2,
			/*populate*/ 		FIL_1_BLSUWON,FIL_1_RDSUWON,FIL_1_AFSUWON,FIL_AFBUZZ03,
			/*factorsPC*/		25,10,9,6,						//MS 14Jun99
		},
		{//24
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlPyongtaek,
			/*airfieldtext*/	IDS_AfXXPyongtaek,
			/*northnodes[2]*/	{&N3_19_Pyongtaek,&N2_14_Osan},
			/*southnodes[2]*/	{&N3_3_Chonan,&N3_53_Chinchon},		  //MS 02/05/99
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLPYONGT,FIL_1_RDPYONGT,FIL_1_AFPYONGT,FIL_AFBUZZ00,
			/*factorsPC*/		80,15,5,10,						//MS 14Jun99
//put back to correct											//MS 15Jun99
		},
		{//25
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlKunsan,
			/*airfieldtext*/	IDS_AfXXKunsan,
			/*northnodes[2]*/	{&N3_1_Taejon,&N3_17_Chochiwon},	  //MS 02/05/99
			/*southnodes[2]*/	{&N3_22_Kimchon,&N3_37_Kumi},		  //MS 02/05/99
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		1,								//MS 23May99
			/*populate*/ 		FIL_1_BLKUNSAN,FIL_1_RDKUNSAN,FIL_1_AFKUNSAN,FIL_AFBUZZ00,
			/*factorsPC*/		25,15,5,7,						//MS 14Jun99
		},
		{//26
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlTaejon,
			/*airfieldtext*/	IDS_AfXXTaejon,
			/*northnodes[2]*/	{&N3_17_Chochiwon,&N3_2_Chongju},//MS 02May99
			/*southnodes[2]*/	{&N3_46_Yongdong,&N3_1_Taejon},	//MS 02May99
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLTAEJON,FIL_1_RDTAEJON,FIL_1_AFTAEJON,FIL_AFBUZZ02,
			/*factorsPC*/		0,0,5,10,						//MS 14Jun99
		},
		{//27
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlTaegu,
			/*airfieldtext*/	IDS_AfXXTaegu,
			/*northnodes[2]*/	{&N3_XX_Taegu,&N3_XX_Taegu},	//MS 18Jun99
			/*southnodes[2]*/	{&N3_XX_Taegu,&N3_XX_Taegu},	//MS 18Jun99
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		2,
			/*populate*/ 		FIL_1_BLTAEGU,FIL_1_RDTAEGU,FIL_1_AFTAEGU,FIL_AFBUZZ01,
			/*factorsPC*/		80,10,5,5,						//MS 14Jun99
//put back to correct											//MS 15Jun99
		},
		{//28
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlTaeguW,
			/*airfieldtext*/	IDS_AfXXTaeguW,
			/*northnodes[2]*/	{&N3_XX_Taegu,&N3_XX_Taegu},
			/*southnodes[2]*/	{&N3_XX_Taegu,&N3_XX_Taegu},
			/*AirFieldType*/	AFT_PROPONLY,					//MS 23May99
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLTAEGUW,FIL_1_RDTAEGUW,FIL_1_AFTAEGUW,FIL_AFBUZZ00,
			/*factorsPC*/		0,0,15,15,						//MS 14Jun99
		},
		{//29
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlKangnung,
			/*airfieldtext*/	IDS_AfXXKangnung,
			/*northnodes[2]*/	{&N2_57_Sangnam,&N1_36_Yangyang},
			/*southnodes[2]*/	{&N2_28_Samchok,&N2_42_Chongson},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLKANGNU,FIL_1_RDKANGNU,FIL_1_AFKANGNU,FIL_NULL,
			/*factorsPC*/		15,15,8,13,						//MS 14Jun99
		},
		{//30
			/*nationality*/		NAT_BLUE,
			/*airfield*/		UID_AfBlPohang,
			/*airfieldtext*/	IDS_AfXXPohang,
			/*northnodes[2]*/	{&N3_25_Pohang,&N3_25_Pohang},
			/*southnodes[2]*/	{&N3_25_Pohang,&N3_25_Pohang},
			/*AirFieldType*/	AFT_JET,					//MS 02Jun99
			/*capacity*/		1,
			/*populate*/ 		FIL_1_BLPOHANG,FIL_1_RDPOHANG,FIL_1_AFPOHANG,FIL_AFBUZZ03,
			/*factorsPC*/		30,15,8,10,						//MS 14Jun99
		},
//DeadCode MS 30Apr99 		{//31
//DeadCode MS 30Apr99 			/*nationality*/		NAT_RED,
//DeadCode MS 30Apr99 			/*airfield*/		UID_AfRdKangdong,
//DeadCode MS 30Apr99 			/*airfieldtext*/	IDS_AfXXKangdong,
//DeadCode MS 30Apr99 			/*northnodes[2]*/	{&N1_12_Sunchon,&N1_14_WaDong},
//DeadCode MS 30Apr99 			/*southnodes[2]*/	{&N1_29_Kangdong,&N1_13_Samdung},
//DeadCode MS 30Apr99 			/*AirFieldType*/	AFT_PROPONLY,
//DeadCode MS 30Apr99 			/*capacity*/		1,			 //POPULATE NEEDS FIXING
//DeadCode MS 30Apr99 			/*populate*/ 		FIL_1_BLKANGDO,FIL_1_RDKANGDO,FIL_1_AFKANGDO,FIL_NULL,
//DeadCode MS 30Apr99 			/*factorsPC*/		100,100,100,100,
//DeadCode MS 30Apr99 		},
//this must be the last one!
		{
			/*nationality*/		NAT_ALIGN,
		}
};
//DirectivesProfile	T::profilelib[T::MAXPROFILELIBS]	 =
//{
//			 86,86,80,84,51,26,29
//GROUND ATTACK
//-------------
//
//			{16, 0,16,16,0,16, 0},		//P_ALPHASTRIKE
//			{0, 0, 0, 0, 0, 0, 0},		//P_MEDSTRIKE		allocated at runtime
//			{0, 0, 0, 0, 0, 0, 0},		//P_FBSTRIKE		allocated at runtime
//			{0, 0, 8, 8, 0, 0, 8},		//P_B29CARPETBOMB
//			{0, 0, 8, 8, 0, 0, 8},		//P_B29PRECISIONBOMB
//			{0, 0, 0, 0, 0, 8, 0},		//P_B26RAID
//			{0, 0, 0, 8, 0, 0, 0},		//P_DEEPFBSTRIKE
//			{0, 0, 8, 0, 0, 0, 0},		//P_NORMALFBSTRIKE
//			{0, 0, 0, 0, 8, 0, 0},		//P_LOWRISKFBSTRIKE
//			{0, 0, 0, 8, 0, 0, 0},		//P_HITANDRUN
//			{0, 0, 8, 8, 8, 0, 0},		//P_MIXEDRAID
////ARMED RECONN PATROLS
////--------------------
//			{0, 0, 0, 0, 4, 0, 0},		//P_ARMEDRECONN
////MIGCAP
////------
//			{16,16,0, 0, 0, 0, 0},		//P_SABRESCREEN
////CAS
////---
//			{0, 0, 0, 0, 4, 0, 0},		//P_RAPIDRESPONSE
//
//
//};
T::DisSmacker	T::dissmackers [T::MAX_DISSMACKERS]=
{
	{
		/*idtext*/			Debrief::D_MiniText09_H,
		/*FIL_NULL*/			FIL_SMACK_BRIT_TROOPS
	},
	{
		/*idtext*/			Debrief::T_AttackWest01_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MORTAR
	},
	{
		/*idtext*/			Debrief::T_AttackCntr01_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MORTAR
	},
	{
		/*idtext*/			Debrief::T_AttackWest03_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_ARTILLERY
	},
	{
		/*idtext*/			Debrief::T_AttackCntr03_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_ARTILLERY
	},
	{
		/*idtext*/			Debrief::T_AttackWest02_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_HALFTRACK
	},
	{
		/*idtext*/			Debrief::T_AttackCntr02_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_HALFTRACK
	},
	{
		/*idtext*/			Debrief::T_AttackWest04_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MGUN
	},
	{
		/*idtext*/			Debrief::T_AttackCntr04_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MGUN
	},
	{
		/*idtext*/			Debrief::T_AttackWest05_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MEN
	},
	{
		/*idtext*/			Debrief::T_AttackCntr05_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MEN
	},
	{
		/*idtext*/			Debrief::T_AttackWest06_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_TANKS
	},
	{
		/*idtext*/			Debrief::T_AttackCntr06_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_TANKS
	},

	{
		/*idtext*/			Debrief::T_DefendWest01_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MORTAR
	},
	{
		/*idtext*/			Debrief::T_DefendCntr01_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MORTAR
	},
	{
		/*idtext*/			Debrief::T_DefendWest03_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_ARTILLERY
	},
	{
		/*idtext*/			Debrief::T_DefendCntr03_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_ARTILLERY
	},
	{
		/*idtext*/			Debrief::T_DefendWest02_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_HALFTRACK
	},
	{
		/*idtext*/			Debrief::T_DefendCntr02_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_HALFTRACK
	},
	{
		/*idtext*/			Debrief::T_DefendWest04_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MGUN
	},
	{
		/*idtext*/			Debrief::T_DefendCntr04_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MGUN
	},
	{
		/*idtext*/			Debrief::T_DefendWest05_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MEN
	},
	{
		/*idtext*/			Debrief::T_DefendCntr05_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_MEN
	},
	{
		/*idtext*/			Debrief::T_DefendWest06_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_TANKS
	},
	{
		/*idtext*/			Debrief::T_DefendCntr06_H,
		/*FIL_NULL*/			FIL_SMACK_BATTLE_TANKS
	},
	{																  //RDH 14/06/99
		/*idtext*/			Debrief::D_AlJolson_H,				  //RDH 14/06/99
		/*FIL_NULL*/			FIL_SMACK_ALJOLSON				  //RDH 14/06/99 //RDH 14/06/99
	},

//DEADCODE RDH 14/06/99 	{
//DEADCODE RDH 14/06/99 		/*idtext*/			Debrief::T_FAC01_H,
//DEADCODE RDH 14/06/99 		/*FIL_NULL*/			FIL_SMACK_BATTLE_SPARE
//DEADCODE RDH 14/06/99 	},
	{
		/*idtext*/			Debrief::T_Advance01_H,
		/*FIL_NULL*/			FIL_SMACK_UN_ADVANCE_HALFTRACK
	},
	{
		/*idtext*/			Debrief::T_Advance02_H,
		/*FIL_NULL*/			FIL_SMACK_UN_ADVANCE_MEN
	},
	{
		/*idtext*/			Debrief::T_Advance03_H,
		/*FIL_NULL*/			FIL_SMACK_UN_ADVANCE_HAN
	},
	{
		/*idtext*/			Debrief::T_Advance04_H,
		/*FIL_NULL*/			FIL_SMACK_UN_ADVANCE_DEAD
	},
	{
		/*idtext*/			Debrief::T_Advance05_H,
		/*FIL_NULL*/			FIL_SMACK_UN_ADVANCE_TANK
	},
	{
		/*idtext*/			Debrief::T_Bombers01_H,
		/*FIL_NULL*/			FIL_SMACK_B29_ONLINE
	},
	{
		/*idtext*/			Debrief::T_Bombers00_H,
		/*FIL_NULL*/			FIL_SMACK_B29_STANDDOWN
	},
	{
		/*idtext*/			Debrief::T_FAC03_H,
		/*FIL_NULL*/			FIL_SMACK_CHINESE_PRISONER
	},
	{
		/*idtext*/			Debrief::D_Repairs00_H,
		/*FIL_NULL*/			FIL_SMACK_LABOUR
	},
	{
		/*idtext*/			Debrief::T_Airfield00_H,
		/*FIL_NULL*/			FIL_SMACK_MIGS_ATTACK
	},
	{
		/*idtext*/			Debrief::T_Army02_H,
		/*FIL_NULL*/			FIL_SMACK_LINE_STABLE
	},
	{
		/*idtext*/			Debrief::T_Army03_H,
		/*FIL_NULL*/			FIL_SMACK_LINE_STABLE
	},
	{															//MS 11Jun99
		/*idtext*/			Debrief::D_MiniText00_H,			//MS 11Jun99
		/*FIL_NULL*/			FIL_SMACK_KIMPO					//MS 11Jun99
	},															//MS 11Jun99
	{
		/*idtext*/			Debrief::T_Retreat01_H,
		/*FIL_NULL*/			FIL_SMACK_UN_NEWLINE_1
	},
	{
		/*idtext*/			Debrief::T_Retreat02_H,
		/*FIL_NULL*/			FIL_SMACK_UN_NEWLINE_1				  //rdh 14/06/99
	},
	{
		/*idtext*/			Debrief::T_Retreat03_H,
		/*FIL_NULL*/			FIL_SMACK_UN_NEWLINE_2				  //rdh 14/06/99
	},
	{
		/*idtext*/			-1,
		/*FIL_NULL*/			FIL_NULL
	},
	{
		/*idtext*/			-1,
		/*FIL_NULL*/			FIL_NULL
	},
	{
		/*idtext*/			-1,
		/*FIL_NULL*/			FIL_NULL
	},
	{
		/*idtext*/			-1,
		/*FIL_NULL*/			FIL_NULL
	},
	{
		/*idtext*/			-1,
		/*FIL_NULL*/			FIL_NULL
	},
	{
		/*idtext*/			-1,
		/*FIL_NULL*/			FIL_NULL
	},
	{
		/*idtext*/			-1,
		/*FIL_NULL*/			FIL_NULL
	},
	{
		/*idtext*/			-1,
		/*FIL_NULL*/			FIL_NULL
	}//,
//	{
//		/*idtext*/			-1,
//		/*FIL_NULL*/			FIL_NULL
//	}
};

//T::DirControl	T::dir_ctrl =
//{
//	/*autogen*/			true,
//	/*autodisplay*/		true,
//	/*B29avail*/		true,
//	/*alphastrikesallowed*/		false,
//	/*dayssinceB29*/	0,
//
//	{
//			{
//				/*type*/				D_AIRSUPERIORITY,
//				/*strikeac*/			0,
//				/*fighterac*/			16,
//				/*targets*/				0,
//				/*missionsset*/			0
//			},
//			{
//				/*type*/				D_CHOKE,
//				/*strikeac*/			64,
//				/*fighterac*/			16,
//				/*targets*/				0,
//				/*missionsset*/			0
//			},
//			{
//				/*type*/				D_SUPPLY,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//			},
//			{
//				/*type*/				D_AIRFIELDS,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//			},
//			{
//				/*type*/				D_RAIL,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//			},
//			{
//				/*type*/				D_ROAD,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//			},
//			{
//				/*type*/				D_ARMY,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//			},
//			{
//				/*type*/				D_RESTING,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//			}
//	}
//};
SupplyNode*	T::CurrDisNode = FirstNode;	
