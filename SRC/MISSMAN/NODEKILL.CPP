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
//Filename       node.cpp
//System         
//Author         R. Hyde 
//Date           Wed 19 Feb 1997
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

enum	{DAYS0 = 0};

#define	T SupplyTree
SupplyNode*const	T::FirstNode=&N0_0_Dangdong;
SupplyNode
//this must be the first node
T::N0_0_Dangdong =	{
			/*nextnode*/		&N0_1_Sinuiju,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdUiju},
			/*associated_item*/	UID_WhRdDangDong,
			/*currentstores*/	STORES_MAXSUPPLY,	
			/*maxstores*/		STORES_MAXSUPPLY,	
			/*route[3]*/		{NULL},	
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_0_1Rail0,				//wrong&R0_0_1Rail

				},
T::N0_1_Sinuiju =	{
			/*nextnode*/		&N0_2_Yomju,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},
			/*associated_item*/	UID_WhRdSinuiju,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R0_0_1Rail0},					//wrong{&R0_0_1Rail},							
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_1_2Rail0,

				},		

T::N0_2_Yomju =	{
			/*nextnode*/		&N0_3_Sonchon,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_SCCYomju,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_1_2Rail0},												
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_2_3Rail,


				},


T::N0_3_Sonchon =	{
			/*nextnode*/		&N0_4_Chongju,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdNamsi},	
			/*associated_item*/	UID_SdRdSonchon,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_2_3Rail},												
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_3_4Rail,


				},


T::N0_4_Chongju =	{
			/*nextnode*/		&N0_4b_Maenjungdong,	//FIXED (was N0_5_Suiho)
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdSinanju,UID_AfRdNamsi},
			/*associated_item*/	UID_StChongju,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_3_4Rail},												
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_4_4bRail,


				},

T::N0_4b_Maenjungdong =	{
			/*nextnode*/		&N0_5_Sinaju,	//FIXED (was N0_5_Suiho)
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdSinanju,UID_AfRdNamsi},
			/*associated_item*/	UID_StMaenjungdong,				//MS 26Oct98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_4_4bRail},												
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_4b_5Rail0,


				},


T::N0_57_Suiho =	{
			/*nextnode*/		&N0_46_Chongsongup,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_HEPSuihu,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_57_46Road},												
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_57_46Road,		//BADLINK PROBLEM


				},
T::N0_46_Chongsongup =	{
			/*nextnode*/		&N0_48_Kusong,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_StChongsongup,//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_57_46Road},												
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_46_48Road,
						},			

T::N0_48_Kusong =	{
			/*nextnode*/		&N0_44_Namsanni,		//INCORRECT 4 Chongju
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSinanju},	
			/*associated_item*/	UID_StKusong,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_46_48Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_48_4Rail,


				},
T::N0_44_Namsanni =	{
			/*nextnode*/		&N0_45_Sakchu,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_StNamsanni,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_44_45Rail},	
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_44_45Rail,


				},
T::N0_45_Sakchu =	{
			/*nextnode*/		&N0_60_Chosan,		//INCORRECT 48 Kusong
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_SCCSakchu,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,																					
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,																					
			/*route[3]*/		{&R0_44_45Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_45_48Rail,


				},

T::N0_60_Chosan =	{
			/*nextnode*/		&N0_59_Chosin,			//INCORRECT
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_SCCChosan,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_60_11Road},													
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_60_11Road,			//BADLINK Problem


				},
T::N0_59_Chosin =	{
			/*nextnode*/		&N0_51_Pungsan,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_HEPChosin,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_9_59Road},													
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_59_19Road,


				},

T::N0_51_Pungsan =	{
			/*nextnode*/		&N0_33_Kapsan,	//INCORRECT 37 Purchong
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_StPungsan,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_9_51Road},													
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_51_37Road,


				},
T::N0_33_Kapsan =	{
			/*nextnode*/		&N0_32_Hyesan,	//INCORRECT 51 Pungsan
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_StKapsan,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_32_33Road},													
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_33_51Road,


				},
T::N0_32_Hyesan =	{
			/*nextnode*/		&N0_5_Sinaju,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_StHyesan,	//MS 12Jun98
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R0_32_33Road},													
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_32_33Road,


				},
								


T::N0_5_Sinaju =	{
			/*nextnode*/		&N0_16_Chongjin,		//INCORRECT 6 Sukchon
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdPyongni},	
			/*associated_item*/	UID_StSinanju,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_4b_5Rail0},					
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_5_6Rail,								

				},




T::N0_16_Chongjin =	{
			/*nextnode*/		&N0_56_Kyongsong,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
			/*associated_item*/	UID_MyRlChongjin,
			/*currentstores*/	STORES_MAXSUPPLY,	
			/*maxstores*/		STORES_MAXSUPPLY,	
			/*route[3]*/		{&R0_16_56Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_16_56Rail,

				},


T::N0_56_Kyongsong =	{
			/*nextnode*/		&N0_17_Kilchu,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
			/*associated_item*/	UID_StKyongsong,//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_16_56Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_56_17Rail,

				},

T::N0_17_Kilchu =	{
			/*nextnode*/		&N0_18_Kimchaek,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
			/*associated_item*/	UID_StKilchu,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_56_17Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_17_18Rail,

				},

T::N0_18_Kimchaek =	{
			/*nextnode*/		&N0_50_Tanchon,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
			/*associated_item*/	UID_MSPKimchaek,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_17_18Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_18_50Rail,

				},




T::N0_50_Tanchon =	{
			/*nextnode*/		&N0_37_Pukchong,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
			/*associated_item*/	UID_MSPTanchon,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_18_50Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_50_37Rail,

				},





T::N0_37_Pukchong =	{
			/*nextnode*/		&N0_19_Hamhung,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
			/*associated_item*/	UID_StPukchong,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_50_37Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_37_19Rail,

				},


T::N0_19_Hamhung =	{
			/*nextnode*/		&N0_8_Manpo,		//INCORRECT 34 Yonchung
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
			/*associated_item*/	UID_MyRdHamhung,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R0_37_19Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_19_34Rail,

				},

T::N0_8_Manpo =	{
			/*nextnode*/		&N0_9_Kangye,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_SCCManpo,
			/*currentstores*/	STORES_MAXSUPPLY,	
			/*maxstores*/		STORES_MAXSUPPLY,	
			/*route[3]*/		{&R0_8_9Rail},					//BADLINK
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_8_9Rail,					//BADLINK

				},



T::N0_9_Kangye =	{
			/*nextnode*/		&N0_58_SinmiDo,		//INCORRECT 10 Huichon
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_SCCKangye,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_8_9Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_9_10Rail,

				},
T::N0_58_SinmiDo =	{
			/*nextnode*/		&N0_10_Huichon,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},	
			/*associated_item*/	UID_FCSinmiDo,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_3_58Road},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_3_58Road,		

				},

T::N0_10_Huichon =	{
			/*nextnode*/		&N0_11_Kujang,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdTaechon},	
			/*associated_item*/	UID_SCCHuichon,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_9_10Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_10_11Rail,

				},



T::N0_11_Kujang =	{
			/*nextnode*/		&N0_31_Tokchon,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdTaechon},	
			/*associated_item*/	UID_StKujang,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_10_11Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_11_31Rail,

				},

T::N0_31_Tokchon =	{
			/*nextnode*/		&N1_6_Sukchon,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdTaechon},	
			/*associated_item*/	UID_StTokchon,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_11_31Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R0_31_13Rail,

				},




//------------------------------------------------------------------------------
//supply nodes for area 1

T::N1_6_Sukchon =	{
			/*nextnode*/		&N1_29_Kangdong,	//INCORRECT	7 Pyongyang
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdYongyu,UID_AfRdSinanju,UID_AfRdPyongni},	
			/*associated_item*/	UID_WhRdSukchon,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_6_7Rail},	//BADLINK	&R0_5_6Rail		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_6_7Rail,

				},
T::N1_29_Kangdong =	{
			/*nextnode*/		&N1_54_YulLi,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongyangE,UID_AfRdPyongni},	
			/*associated_item*/	UID_StKangdong,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
			/*route[3]*/		{&R1_13_29Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_29_54Rail,

				},

T::N1_54_YulLi =	{
			/*nextnode*/		&N1_7_Pyongyang,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongyangE,UID_AfRdPyongni},	
			/*associated_item*/	UID_StYulLi,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
			/*route[3]*/		{&R1_29_54Rail},				
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_29_54Rail,					

				},

T::N1_7_Pyongyang =	{
			/*nextnode*/		&N1_30_Nampo,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdUiju},	
			/*associated_item*/	UID_MyRdPyongyang,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R1_6_7Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_1_W7_UN,	
			/*forward*/			&R1_7_49Rail,

				},

T::N1_30_Nampo =	{
			/*nextnode*/		&N1_49_Hwangju,	//INCORRECT
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangD,UID_AfRdAnak,UID_AfRdHwangju},	
			/*associated_item*/	UID_ICMPNampo,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R1_7_30Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_7_30Rail,	//BADLINK	

				},
T::N1_49_Hwangju =	{
			/*nextnode*/		&N1_41_Ichon,	//INCORRECT
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangD,UID_AfRdAnak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StHwangju,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_7_49Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_49_22Rail,

				},
T::N1_41_Ichon =	{
			/*nextnode*/		&N1_22_Sariwon,	//INCORRECT 28 pyonggang
			/*supplyline*/		&WestRoute,	//INCORRECT	central
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
			/*associated_item*/	UID_SdRdIchon,
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_25_41Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_41_28Road,

				},

T::N1_22_Sariwon =	{
			/*nextnode*/		&N1_25_Pyongsan,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdAnak},	
			/*associated_item*/	UID_StSariwon,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R1_7_49Rail},	//BADLINK	R1_49_22Rail 
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_1_W6_UN,	
			/*forward*/			&R1_49_22Rail,	//BADLINK

				},
T::N1_25_Pyongsan =	{
			/*nextnode*/		&N1_26_Kumchon,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdAnak},	
			/*associated_item*/	UID_StPyongsan,	//MS 12Jun98
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R1_22_25Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_25_26Rail,

				},

T::N1_26_Kumchon =	{
			/*nextnode*/		&N1_62_Chaeryong,	//INCORRECT 27 Kaesong
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSunan},	
			/*associated_item*/	UID_SdRdKumchon,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_25_26Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_26_27Rail,

				},
T::N1_62_Chaeryong =	{
			/*nextnode*/		&N1_24_Haeju,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StChaeryong,//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_22_62Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_62_24Rail,

				},
T::N1_24_Haeju =	{
			/*nextnode*/		&N1_61_Yonan,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StHaeju,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_62_24Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_24_61Rail,

				},
T::N1_61_Yonan =	{
			/*nextnode*/		&N1_69_Kalmal, //INCORRECT 27 Kaesong
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StYonan,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_24_61Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_61_27Rail,

				},

T::N1_69_Kalmal =	{
			/*nextnode*/		&N1_27_Kaesong, //INCORRECT
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
	   		/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StKalmal,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_38_69Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_38_69Road, //BADLINK69 49 b
																	   
				},
T::N1_27_Kaesong =	{
			/*nextnode*/		&N1_75_Panmunjom,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
			/*associated_item*/	UID_SdRdKaesong,
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R1_26_27Rail},	
			/*redfrontBF*/		FIL_1_W5_Red,		
			/*bluefrontBF*/		FIL_1_W5_UN,	
			/*forward*/			&R1_27_75Rail,


				},		


T::N1_75_Panmunjom =	{
			/*nextnode*/		&N1_34_Yonghung,	//INCORRECT 40b Munsan
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
			/*associated_item*/	UID_MyRdPanmunjom,
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_27_75Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_75_40Rail,

				},

T::N1_34_Yonghung =	{
			/*nextnode*/		&N1_12_Sunchon,		//INCORRECT 20a Kowon
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
			/*associated_item*/	UID_StYonghung,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_19_34Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_34_20Rail,

				},
T::N1_12_Sunchon =	{
			/*nextnode*/		&N1_20_Kowon,		//INCORRECT 7 Pyongyang
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdPyongni,UID_AfRdSunan},
			/*associated_item*/	UID_StSunchon,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R0_11_12Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_12_7Rail,

				},

		
T::N1_20_Kowon =	{
			/*nextnode*/		&N1_21_Wonsan,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
			/*associated_item*/	UID_StKowon,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_34_20Rail},	//BADLINK IN Node.CPP!	
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_20_21Rail,

				},

T::N1_21_Wonsan =	{
			/*nextnode*/		&N1_52_Kojo,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
			/*associated_item*/	UID_MyRlWonsan,
			/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R1_20_21Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_21_52Rail,

				},

T::N1_52_Kojo =	{
			/*nextnode*/		&N1_35_Kojin ,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
			/*associated_item*/	UID_StKojo,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R1_21_52Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_52_35Rail,
		

				},

T::N1_35_Kojin  =	{
			/*nextnode*/		&N1_64_Sangwon ,		//INCORRECT 35 Kosong
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StKojin ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_52_35Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_35_42Rail,
			

				},
T::N1_64_Sangwon  =	{
			/*nextnode*/		&N1_65_Nuang ,			// INCORRECT 54 Yul-li
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdHwangju},	
			/*associated_item*/	UID_StSangwon ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_7_64Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_64_54Road,
			

				},
T::N1_65_Nuang  =	{
			/*nextnode*/		&N1_63_Suan ,   //INCORRECT 54 Yul-li
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdHwangju},	
			/*associated_item*/	UID_StNuang ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_22_65Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_65_54Road,
			

				},
T::N1_63_Suan  =	{
			/*nextnode*/		&N1_66_Singye ,		//INCORRECT 54 Yul-li
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdHwangju},	
			/*associated_item*/	UID_StSuan ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_25_63Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_63_54Road,
			

				},
T::N1_66_Singye  =	{
			/*nextnode*/		&N1_42_Kansang,		//INCORRECT 53 Koksan
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdHwangju},	
			/*associated_item*/	UID_StSingye ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_25_66Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_66_53Road,
			

				},

T::N1_42_Kansang =	{
			/*nextnode*/		&N1_70_Hwachon,		// INCORRECT 36 Yangyang
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StKansang,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_35_42Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_42_36Rail,
			

				},
T::N1_70_Hwachon =	{
			/*nextnode*/		&N1_50_Yongpyong,	//INCORRECT 12 Chunchon
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StHwachon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_38_70Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_70_12Road,
			

				},
T::N1_50_Yongpyong =	{
			/*nextnode*/		&N1_68_Changdo,  // INCORRECT 12 Chunchon
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StYongpyong,//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R1_38_50Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_50_12Road,
			

				},


T::N1_68_Changdo =	{
			/*nextnode*/		&N1_53_Koksan,		//INCORRECT 38 Kumhwa
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StChangdo,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_40_68Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_68_38Road,
			

				},
T::N1_53_Koksan =	{
			/*nextnode*/		&N1_40_Hoeyang,		// INCORRECT 55 Majon
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StKoksan,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_15_53Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_15_55Road,
			

				},
T::N1_40_Hoeyang =	{
			/*nextnode*/		&N1_38_Kumhwa,		// INCORRECT 68 Changdo
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StHoeyang,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_39_40Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_40_68Road,
			

				},
T::N1_38_Kumhwa =	{
			/*nextnode*/		&N1_36_Yangyang,	//INCORRECT 69 Kalmal
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StKumhwa,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_68_38Road},		
			/*redfrontBF*/		FIL_1_C4_Red,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_38_69Road,
			

				},



T::N1_36_Yangyang =	{
			/*nextnode*/		&N1_13_Samdung,	//INCORRECT 29 Kangnung
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StYangyang,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R1_35_42Rail},		//BADLINK 42_36Rail
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_36_29Road,
			

				},

T::N1_13_Samdung =	{
			/*nextnode*/		&N1_23_Changyon,	//INCORRECT 14 Wa-Dong
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdPyongni,UID_AfRdSinanju},	
			/*associated_item*/	UID_StSamdung,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R0_31_13Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_13_14Rail,
					

				},
T::N1_23_Changyon =	{
			/*nextnode*/		&N1_14_WaDong ,		//INCORRECT
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StChangyon,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R1_62_23Rail},	//BADLINK NONE!	
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_62_23Rail,		//BADLINK NONE!
					

				},

T::N1_14_WaDong  =	{
			/*nextnode*/		&N1_15_Yangdok ,	
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdSunan},	
			/*associated_item*/	UID_CPWaDong,
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_13_14Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_14_15Rail,
					

				},

T::N1_15_Yangdok  =	{
			/*nextnode*/		&N1_39_Kosan ,		//  INCORRECT 20 Kowon	
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdPyongyangE},	
			/*associated_item*/	UID_StYangdok ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_14_15Rail},			
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_15_20Rail,
					

				},

T::N1_39_Kosan  =	{
			/*nextnode*/		&N1_67_Sepo ,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdPyongyangE},	
			/*associated_item*/	UID_StKosan ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_21_39Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_39_67Rail,
					

				},

T::N1_67_Sepo  =	{
			/*nextnode*/		&N1_71_Inje ,		//INCORRECT 28 Pyonggang
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdPyongyangE},	
			/*associated_item*/	UID_StSepo ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_39_67Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_39_67Rail,		//BADLINK 67_28RAIL
					

				},
T::N1_71_Inje  =	{
			/*nextnode*/		&N1_28_Pyonggang ,	//INCORRECT 12 Chunchon
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdPyongyangE},	
			/*associated_item*/	UID_StInje ,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_42_71Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_71_12Road0,
					

				},

T::N1_28_Pyonggang  =	{
			/*nextnode*/		&N1_43_Chorwon ,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StPyonggang ,//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_67_28Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_28_43Rail,
					

				},


T::N1_43_Chorwon  =	{
			/*nextnode*/		&N1_55_Kanda ,		 //INCORRECT ????!
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StChorwon ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R1_28_43Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_43_56Rail,
					

				},

T::N1_55_Kanda  =	{								//INCORRECT THIS NODE DOES NOT
			/*nextnode*/		&N1_56_Yonchon ,	//EXIst
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDREDLINES,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StKanda ,	//MS 12Jun98
			/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_15_55Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_55_21Road,
					

				},

T::N1_56_Yonchon  =	{
			/*nextnode*/		&N2_40_Munsan,		//INCORRECT 11 Uijongbu
			/*supplyline*/		&CentralRoute,		
			/*type*/			BATTLEFIELD,
			/*status*/			FRONTLINE,
			/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
			/*associated_item*/	UID_StYonchon ,	//MS 12Jun98
			/*currentstores*/	STORES_TODISCOURAGEBLUEATTACK,	
			/*maxstores*/		STORES_TOINITIATEASSAULT,	
			/*route[3]*/		{&R1_43_56Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R1_56_11Rail,
					

				},


//-------------------------------------------------------------------------------
//Supply Nodes for area 2



T::N2_40_Munsan={
			/*nextnode*/		&N2_10_Seoul,		
			/*supplyline*/		&WestRoute,		
			/*type*/			BATTLEFIELD,
			/*status*/			FRONTLINE,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlChuncheon},	
			/*associated_item*/	UID_MyBlMunsan,
			/*currentstores*/	STORES_TODISCOURAGEBLUEATTACK,	
			/*maxstores*/		STORES_TOINITIATEASSAULT,	
			/*route[3]*/		{&R1_75_40Rail},		
			/*redfrontBF*/		FIL_1_W4_Red,		
			/*bluefrontBF*/		FIL_1_W4_UN,	
			/*forward*/			&R2_40_10Rail,

				},

T::N2_10_Seoul={
			/*nextnode*/		&N2_7_Suwon,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlOsan},	
			/*associated_item*/	UID_MyBlSeoul,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYBIGSETTLEMENT,	
			/*route[3]*/		{&R2_40_10Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_1_W3_UN,	
			/*forward*/			&R2_10_7Rail,

				},		




T::N2_7_Suwon =	{
			/*nextnode*/		&N2_14_Osan,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlSeoul,UID_AfBlOsan},	
			/*associated_item*/	UID_SdBlSuwon,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R2_10_7Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_7_14Rail,
					

				},



T::N2_14_Osan =	{
			/*nextnode*/		&N2_29_Kangnung,	// INCORRECT 19 Pyongtaek
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_MyBlOsan,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R2_7_14Rail},		
			/*redfrontBF*/		FIL_1_W2_Red,		
			/*bluefrontBF*/		FIL_1_W2_UN,	
			/*forward*/			&R2_14_19Rail,
					

				},

T::N2_29_Kangnung =	{
			/*nextnode*/		&N2_28_Samchok,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
			/*associated_item*/	UID_StKangnung,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R1_36_29Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_29_28Road,
					

				},

T::N2_28_Samchok =	{
			/*nextnode*/		&N2_49_Pochon,		//INCORRECT 30 Ulhin
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
			/*associated_item*/	UID_StSamchok,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R2_29_28Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_28_30Road,
					

				},
T::N2_49_Pochon =	{
			/*nextnode*/		&N2_12_Chuncheon,	//INCORRECT 11 Uijongbu
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
			/*associated_item*/	UID_StPochon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_69_49Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_49_11Road,
					

				},

T::N2_12_Chuncheon =	{
			/*nextnode*/		&N2_48_Kuri,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
			/*associated_item*/	UID_StChuncheon,//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R1_71_12Road0},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_12_48Road0,
			/*priority*/		SP_NONE,
			/*serviced*/		false,
			/*populate*/		FIL_1_Chunchon,

				},
T::N2_48_Kuri =	{
			/*nextnode*/		&N2_35_Hongchon,		//INCORRECT 10 Seoul
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
			/*associated_item*/	UID_MyBlKuri,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_12_48Road0},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_48_10Road,
					

				},
T::N2_35_Hongchon =	{
			/*nextnode*/		&N2_23_Hoensong,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
			/*associated_item*/	UID_SdRdHongchon,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_12_35Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_35_23Road,
					

				},
T::N2_23_Hoensong =	{
			/*nextnode*/		&N2_34_Yulchon,		//INCORRECT 6 Wonju
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
			/*associated_item*/	UID_StHoensong,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R2_35_23Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_23_6Road,

					
				},
T::N2_34_Yulchon =	{
			/*nextnode*/		&N2_43_Pyongchang,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
			/*associated_item*/	UID_StYulchon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_57_34Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_34_43Road,
					

				},
T::N2_43_Pyongchang =	{
			/*nextnode*/		&N2_57_Sangnam,	//INCORRECT 5 Chechon
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
			/*associated_item*/	UID_StPyongchang,//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_34_43Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_43_5Road,
					

				},
T::N2_57_Sangnam =	{
			/*nextnode*/		&N2_42_Chongson,		//INCORRECT 34 Yulchon
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
			/*associated_item*/	UID_StSangnam,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R1_71_57Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_57_34Road,
					

				},
T::N2_42_Chongson =	{
			/*nextnode*/		&N2_9_Inchon,		//INCORRECT 28 Samchok
			/*supplyline*/		&EastRoute,		
			/*type*/			BATTLEFIELD,
			/*status*/			FRONTLINE,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
			/*associated_item*/	UID_StChongson,	//MS 12Jun98
			/*currentstores*/	STORES_TODISCOURAGEBLUEATTACK,	
			/*maxstores*/		STORES_TOINITIATEASSAULT,	
			/*route[3]*/		{&R2_43_42Road},			
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_42_28Road,
					

				},
T::N2_9_Inchon =	{
			/*nextnode*/		&N2_39_Kimpo,		// INCORRECT 7 Suwon
			/*supplyline*/		&EastRoute,			// INCORRECT WEST!
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
			/*associated_item*/	UID_StInchon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R2_10_9Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_10_9Road,		//BADLINK 9-7	
					

				},

T::N2_39_Kimpo	=	{
			/*nextnode*/		&N2_8_Songnam,		// INCORRECT 10 Seoul
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},
			/*associated_item*/	UID_StKimpo,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_10_9Road},		//BADLINK 40-39
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_10_9Road,		//BADLINK 39-10			
					

				},
T::N2_8_Songnam =	{
			/*nextnode*/		&N2_41_Ichon,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},	
			/*associated_item*/	UID_StSongnam,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_10_8Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_8_41Road,
					

				},
T::N2_41_Ichon=	{
			/*nextnode*/		&N2_11_Uijongbu,	//INCORRECT 26 Changhowon
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},	
			/*associated_item*/	UID_StIchon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R2_8_41Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_41_26Road,
					

				},


T::N2_11_Uijongbu =	{
			/*nextnode*/		&N2_58_Yangpyong,		// INCORRECT 48 or 10
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
			/*associated_item*/	UID_StUijongbu,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R2_29_28Road},		//BADLINK!
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_28_30Road,			//BADLINK!
					

				},

T::N2_58_Yangpyong =	{
			/*nextnode*/		&N2_6_Wonju,		
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
			/*associated_item*/	UID_StYangpyong,//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_10_58Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_58_6Rail,
					

				},

T::N2_6_Wonju =	{
			/*nextnode*/		&N3_19_Pyongtaek,	// INCORRECT 5 Chechon
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
			/*associated_item*/	UID_StWonju,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R2_58_6Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R2_6_5Rail,
					

				},



//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//Supply Nodes for area 3


T::N3_19_Pyongtaek =	{
			/*nextnode*/		&N3_3_Chonan,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_SdBlPyongtaek,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R2_14_19Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_19_3Rail,
					

				},



T::N3_3_Chonan =	{
			/*nextnode*/		&N3_36_Mokkye,		//INCORRECT 17 Chochiwon
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_SdBlChonan,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_19_3Rail},		
			/*redfrontBF*/		FIL_1_W1_Red,		
			/*bluefrontBF*/		FIL_1_W1_UN,	
			/*forward*/			&R3_3_17Rail,
					

				},
T::N3_36_Mokkye =	{
			/*nextnode*/		&N3_44_Taepaek,		//INCORRECT 4 Chungju
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StMokkye,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_6_36Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_36_4Road,
					

				},
T::N3_44_Taepaek =	{
			/*nextnode*/		&N3_62_Noktong,		
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StTaepaek,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_28_44Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_44_62Road,
					

				},
T::N3_62_Noktong =	{
			/*nextnode*/		&N3_20_Yechon,		//INCORRECT 16 Yongju
			/*supplyline*/		&EastRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StNoktong,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_44_62Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_62_16Road,
					

				},
T::N3_20_Yechon =	{
			/*nextnode*/		&N3_24_Chomchon,
			/*supplyline*/		&EastRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StYechon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_18_20Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_20_24Road,
					

				},
T::N3_24_Chomchon =	{
			/*nextnode*/		&N3_21_Sangju,
			/*supplyline*/		&EastRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StChomchon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_24_21Road},		//BADLINK 20_24Road
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_21_22Road,			//BADLINK 24_21Road/Rail
					

				},
T::N3_21_Sangju =	{
			/*nextnode*/		&N3_2_Chongju,			//INCORRECT 22 Kimchon
			/*supplyline*/		&EastRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StSangju,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_24_21Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_21_22Road,
					

				},
T::N3_2_Chongju =	{
			/*nextnode*/		&N3_8_Songnam,			//INCORRECT PROBLEM!
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StChongju,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_59_2Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_2_1Rail,			//BADLINK PROBLEM!
					

				},
T::N3_8_Songnam =	{
			/*nextnode*/		&N3_64_Hongsong,	//INCORRECT 8_41 or 8_7
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlSeoul,UID_AfBlOsan},	
			/*associated_item*/	UID_StSongnam,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_59_2Rail},		//BADLINK 8_8 or 10_8
			/*redfrontBF*/		FIL_NULL,
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_2_1Rail,		//BADLINK 8_7
					

				},

T::N3_64_Hongsong =	{
			/*nextnode*/		&N3_65_Hannae,
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlTaejon,UID_AfBlPyongtaek},	
			/*associated_item*/	UID_SdBlHongsong,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_3_64Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_64_65Rail,
					

				},
T::N3_65_Hannae =	{
			/*nextnode*/		&N3_51_Maesan,		//INCORRECT 66 Taechon
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StHannae,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_64_65Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_65_66Rail,
					

				},
T::N3_51_Maesan =	{
			/*nextnode*/		&N3_52_Kwangheywan,
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StMaesan,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_41_51Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_51_52Road,
					

				},
T::N3_52_Kwangheywan =	{
			/*nextnode*/		&N3_53_Chinchon,
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StKwangheywan,//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_51_52Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_52_53Road,
					

				},
T::N3_53_Chinchon =	{
			/*nextnode*/		&N3_54_Chungpyong,
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StChinchon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_52_53Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_53_54Road,
					

				},
T::N3_54_Chungpyong =	{
			/*nextnode*/		&N3_60_Mungyong,   //INCORRECT 2 Chongju
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StChungpyong,//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_53_54Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_54_2Road,
					

				},
T::N3_60_Mungyong =	{
			/*nextnode*/		&N3_61_Tanyang,		//INCORRECT 24 Chomchon
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StMungyong,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_4_60Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_60_24Road,
					

				},
T::N3_61_Tanyang =	{
			/*nextnode*/		&N3_55_Uisong,		//INCORRECT 16 Yongju
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StTanyang,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_4_61Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_61_16Road,
					

				},
T::N3_55_Uisong =	{
			/*nextnode*/		&N3_66_Taechon,		//INCORRECT 37 Kunwi
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StUisong,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_18_55Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_55_37Road,
					

				},

T::N3_66_Taechon =	{
			/*nextnode*/		&N3_45_Nonsan,		//INCORRECT 63 Kunsan
			/*supplyline*/		&EastRoute,			//WEST!
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StTaechon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_65_66Rail},			
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_66_63Rail,
					

				},
T::N3_45_Nonsan =	{
			/*nextnode*/		&N3_63_Kunsan,		//INCORRECT 1 Taejon
			/*supplyline*/		&EastRoute,			//WEST!
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StNonsan,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_63_45Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_45_1Rail,
					

				},
T::N3_63_Kunsan =	{
			/*nextnode*/		&N3_15_Kongju,		//INCORRECT 45 Nonsan
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlKunsan,UID_AfBlTaegu},	
			/*associated_item*/	UID_StKunsan,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R3_66_63Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_63_45Rail,
					

				},
T::N3_15_Kongju =	{
			/*nextnode*/		&N3_4_Chungju,	//INCORRECT 1 or 45
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StKongju,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_66_63Rail},	//BADLINK 3_15	
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_63_45Rail,		//BADLINK 15_45 or 15_1
					

				},

T::N3_4_Chungju =	{
			/*nextnode*/		&N3_59_Koesan,
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StChungju,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_36_4Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_4_59Rail,
					

				},
T::N3_59_Koesan =	{
			/*nextnode*/		&N3_26_Changhowon,		//INCORRECT 2 Chongju
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StKoesan,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_4_59Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_59_2Rail,
					

				},

T::N3_26_Changhowon =	{
			/*nextnode*/		&N3_17_Chochiwon,	//INCORRECT 4 Chungju
			/*supplyline*/		&WestRoute,		
			/*tyxpe*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
			/*associated_item*/	UID_StChanghowon,//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_43_5Road},		//BADLINK	41_26	
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_5_47Rail,		//BADLINK   26_57 or 26_4 etc
					

				},



T::N3_17_Chochiwon =	{
			/*nextnode*/		&N3_1_Taejon,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlTaejon,UID_AfBlKunsan},	
			/*associated_item*/	UID_MyBlChochiwon,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_3_17Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_17_1Rail,
					

				},




T::N3_1_Taejon =	{
			/*nextnode*/		&N3_46_Yongdong,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlTaejon,UID_AfBlKunsan},	
			/*associated_item*/	UID_SdBlTaejon,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R3_17_1Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_1_46Rail,
					

				},
T::N3_46_Yongdong =	{
			/*nextnode*/		&N3_22_Kimchon,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlTaejon,UID_AfBlKunsan},	
			/*associated_item*/	UID_SdBlYongdong,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_17_1Rail},		//BADLINK 46_1
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_1_46Rail,		//BADLINK 46_22
					

				},

T::N3_22_Kimchon =	{
			/*nextnode*/		&N3_37_Kumi,
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlTaejon,UID_AfBlTaeguW},	
			/*associated_item*/	UID_StKimchon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
			/*route[3]*/		{&R3_46_22Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_46_22Rail,
					

				},
T::N3_37_Kumi =	{
			/*nextnode*/		&N3_30_Ulhin,			//INCORRECT NONE!
			/*supplyline*/		&WestRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlTaejon,UID_AfBlTaeguW},	
			/*associated_item*/	UID_MyBlKumi,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_22_37Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_46_22Road,			//BADLINK PROBLEM!	
					

				},

T::N3_30_Ulhin =	{
			/*nextnode*/		&N3_31_Yonghae,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlPohang,UID_AfBlTaeguW},	
			/*associated_item*/	UID_StUlhin,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R2_28_30Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_30_31Road,
					

				},


T::N3_31_Yonghae =	{
			/*nextnode*/		&N3_32_Yongdok,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlPohang,UID_AfBlTaeguW},	
			/*associated_item*/	UID_MyBlYonghae,
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_28_30Road},	//BADLINK R3_30_31Road
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_31_32Road,
					

				},

T::N3_32_Yongdok =	{
			/*nextnode*/		&N3_25_Pohang,
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlPohang,UID_AfBlTaeguW},	
			/*associated_item*/	UID_StYongdok,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_31_32Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_32_25Road,
					

				},



T::N3_25_Pohang =	{
			/*nextnode*/		&N3_5_Chechon,		//INCORRECT 18 Andong
			/*supplyline*/		&EastRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlPohang,UID_AfBlTaeguW},	
			/*associated_item*/	UID_StPohang,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_32_25Road},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_32_25Road,		//BADLINK 25_18Rail
					

				},
T::N3_5_Chechon =	{
			/*nextnode*/		&N3_47_Punggi,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},	
			/*associated_item*/	UID_StChechon,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R2_6_5Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_5_47Rail,
					

				},
T::N3_47_Punggi =	{
			/*nextnode*/		&N3_16_Yongju,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},	
			/*associated_item*/	UID_StPunggi,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_5_47Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_47_16Rail,
					

				},

T::N3_16_Yongju =	{
			/*nextnode*/		&N3_18_Andong,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},	
			/*associated_item*/	UID_StYongju,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
			/*route[3]*/		{&R3_47_16Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_16_18Rail,
					

				},

T::N3_18_Andong =	{
			/*nextnode*/		&Last_Node,
			/*supplyline*/		&CentralRoute,		
			/*type*/			NOCONTEST,
			/*status*/			BEHINDBLUELINES,
			/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},	
			/*associated_item*/	UID_StAndong,	//MS 12Jun98
			/*currentstores*/	STORES_NIL,
			/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
			/*route[3]*/		{&R3_16_18Rail},		
			/*redfrontBF*/		FIL_NULL,		
			/*bluefrontBF*/		FIL_NULL,	
			/*forward*/			&R3_18_25Rail,
			},
//this must be the last one!
T::Last_Node = 
		{
			/*nextnode*/		&Last_Node,
			/*supplyline*/		&CentralRoute,		
			/*type*/			LASTONE,
		};


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
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STORES_MAXSUPPLY,
			/*maxcapacitysummer*/		STORES_MAXSUPPLY,
			/*associated_brdg*/			UID_Null,
						},

T::R0_0_1Rail0= 	{
			/*next*/					&R0_0_1Rail1,
			/*alternateroute*/			&R0_0_1Rail1,
			/*supplier*/				&N0_0_Dangdong,
			/*suppliee*/				&N0_1_Sinuiju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlYalu0,
						},



T::R0_0_1Rail1= 	{
			/*next*/					&R0_0_1Road,
			/*alternateroute*/			&R0_0_1Road,
			/*supplier*/				&N0_0_Dangdong,		
			/*suppliee*/				&N0_1_Sinuiju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlYalu1,
							},
T::R0_0_1Road= 	{
			/*next*/					&R0_1_2Rail0,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_0_Dangdong,		
			/*suppliee*/				&N0_1_Sinuiju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdYalu,
				/*storeslaunched*/			0,
			/*stores_destroyed*/		0,
			/*totalstores_destroyed*/	0,
			/*consecutive_days_attacked*/		0,				
						},




T::R0_1_2Rail0= 	{
			/*next*/					&R0_1_2Rail1,
			/*alternateroute*/			&R0_1_2Rail1,
			/*supplier*/				&N0_1_Sinuiju,		
			/*suppliee*/				&N0_2_Yomju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinuiju0,
							},


T::R0_1_2Rail1= 	{
			/*next*/					&R0_1_2Road,
			/*alternateroute*/			&R0_1_2Road,
			/*supplier*/				&N0_1_Sinuiju,		
			/*suppliee*/				&N0_2_Yomju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinuiju1,
							},




T::R0_1_2Road= 	{
			/*next*/					&R0_32_33Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_1_Sinuiju,		
			/*suppliee*/				&N0_2_Yomju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSinuiju,
							},

T::R0_32_33Road= 	{
			/*next*/					&R0_3_58Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_32_Hyesan,		
			/*suppliee*/				&N0_33_Kapsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R0_3_58Road= 	{
			/*next*/					&R0_33_51Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_3_Sonchon,				
			/*suppliee*/				&N0_58_SinmiDo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R0_33_51Road= 	{
			/*next*/					&R0_51_37Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_33_Kapsan,				
			/*suppliee*/				&N0_51_Pungsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R0_51_37Road= 	{
			/*next*/					&R0_9_19Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_51_Pungsan,				
			/*suppliee*/				&N0_37_Pukchong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R0_9_19Road= 	{
			/*next*/					&R0_9_59Road,
			/*alternateroute*/			&R0_9_59Road,
			/*supplier*/				&N0_9_Kangye,				
			/*suppliee*/				&N0_19_Hamhung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdChangig,
							},
T::R0_9_59Road= 	{
			/*next*/					&R0_48_4Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_9_Kangye,				
			/*suppliee*/				&N0_59_Chosin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R0_48_4Road= 	{
			/*next*/					&R0_59_19Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_48_Kusong,				
			/*suppliee*/				&N0_4_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R0_59_19Road= 	{
			/*next*/					&R0_11_19Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_59_Chosin,				
			/*suppliee*/				&N0_19_Hamhung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R0_11_19Road= 	{
			/*next*/					&R0_2_3Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_11_Kujang,				
			/*suppliee*/				&N0_19_Hamhung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R0_2_3Rail= 	{
			/*next*/					&R0_11_12Rail,
			/*alternateroute*/			&R0_2_3Road,
			/*supplier*/				&N0_2_Yomju,		
			/*suppliee*/				&N0_3_Sonchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R0_11_12Rail= 	{
			/*next*/					&R0_2_3Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_11_Kujang,		
			/*suppliee*/				&N1_12_Sunchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},




T::R0_2_3Road= 	{
			/*next*/					&R0_3_4Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_2_Yomju,		
			/*suppliee*/				&N0_3_Sonchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R0_3_4Rail= 	{
			/*next*/					&R0_3_4Road,
			/*alternateroute*/			&R0_3_4Road,
			/*supplier*/				&N0_3_Sonchon,		
			/*suppliee*/				&N0_4_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},


T::R0_3_4Road= 	{
			/*next*/					&R0_9_51Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_3_Sonchon,		
			/*suppliee*/				&N0_4_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R0_9_51Road= 	{
			/*next*/					&R0_60_11Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_9_Kangye,		
			/*suppliee*/				&N0_51_Pungsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdUngig,
							},


T::R0_60_11Road= 	{
			/*next*/					&R0_11_5Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_60_Chosan,		
			/*suppliee*/				&N0_11_Kujang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdChosan,
							},
T::R0_11_5Rail= 	{
			/*next*/					&R0_11_5Road,
			/*alternateroute*/			&R0_11_5Road,
			/*supplier*/				&N0_11_Kujang,		
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_NULL, //WAS UID_BrRlChongchon0,
							},
T::R0_11_5Road= 	{
			/*next*/					&R0_4b_5Rail0,	//TOTALLY WRONG!!!!
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_11_Kujang,				
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},





T::R0_4_4bRail= 	{
			/*next*/					&R0_4_4bRoad,
			/*alternateroute*/			&R0_4_4bRoad,
			/*supplier*/				&N0_4_Chongju,		
			/*suppliee*/				&N0_4b_Maenjungdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlTaeryong,
							},


T::R0_4_4bRoad= 	{
			/*next*/					&R0_5_6Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_4_Chongju,		
			/*suppliee*/				&N0_4b_Maenjungdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdTaeryong,
							},

T::R0_4b_5Rail0= 	{
			/*next*/					&R0_4b_5Rail1,
			/*alternateroute*/			&R0_4b_5Rail1,
			/*supplier*/				&N0_4b_Maenjungdong,		
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinanju0,
			},

T::R0_4b_5Rail1= 	{
			/*next*/					&R0_4b_5Rail2,
			/*alternateroute*/			&R0_4b_5Rail2,
			/*supplier*/				&N0_4b_Maenjungdong,		
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinanju1,
			},

T::R0_4b_5Rail2= 	{
			/*next*/					&R0_4b_5Rail2,
			/*alternateroute*/			&R0_4b_5Rail2,
			/*supplier*/				&N0_4b_Maenjungdong,		
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinanju2,
			},

T::R0_4b_5Rail3= 	{
			/*next*/					&R0_4b_5Rail3,
			/*alternateroute*/			&R0_4b_5Rail3,
			/*supplier*/				&N0_4b_Maenjungdong,		
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinanju3,
			},

T::R0_4b_5Rail4= 	{
			/*next*/					&R0_4b_5Road,
			/*alternateroute*/			&R0_4b_5Road,
			/*supplier*/				&N0_4b_Maenjungdong,		
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSinanju4,
			},


T::R0_4b_5Road= 	{
			/*next*/					&R0_5_6Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_4b_Maenjungdong,		
			/*suppliee*/				&N0_5_Sinaju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSinanju,
							},



T::R0_5_6Rail= 	{
			/*next*/					&R0_5_6Road,
			/*alternateroute*/			&R0_5_6Road,
			/*supplier*/				&N0_5_Sinaju,		
			/*suppliee*/				&N1_6_Sukchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},


T::R0_5_6Road= 	{
			/*next*/					&R0_16_56Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_5_Sinaju,		
			/*suppliee*/				&N1_6_Sukchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R0_16_56Rail= 	{
			/*next*/					&R0_16_56Road,
			/*alternateroute*/			&R0_16_56Road,
			/*supplier*/				&N0_16_Chongjin,		
			/*suppliee*/				&N0_56_Kyongsong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

T::R0_16_56Road= 	{
			/*next*/					&R0_56_17Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_16_Chongjin,		
			/*suppliee*/				&N0_56_Kyongsong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},



T::R0_56_17Rail= 	{
			/*next*/					&R0_56_17Road,
			/*alternateroute*/			&R0_56_17Road,
			/*supplier*/				&N0_56_Kyongsong,		
			/*suppliee*/				&N0_17_Kilchu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRdKyongsong,
							},

T::R0_56_17Road= 	{
			/*next*/					&R0_17_18Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_56_Kyongsong,		
			/*suppliee*/				&N0_17_Kilchu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdKyongsong,
							},


T::R0_17_18Rail= 	{
			/*next*/					&R0_17_18Road,
			/*alternateroute*/			&R0_17_18Road,
			/*supplier*/				&N0_17_Kilchu,		
			/*suppliee*/				&N0_18_Kimchaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRdKilchu,
							},

T::R0_17_18Road= 	{
			/*next*/					&R0_18_50Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_17_Kilchu,		
			/*suppliee*/				&N0_18_Kimchaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R0_18_50Rail= 	{
			/*next*/					&R0_18_50Road,
			/*alternateroute*/			&R0_18_50Road,
			/*supplier*/				&N0_18_Kimchaek,		
			/*suppliee*/				&N0_50_Tanchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRdKimchaek,
							},

T::R0_18_50Road= 	{
			/*next*/					&R0_50_37Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_18_Kimchaek,		
			/*suppliee*/				&N0_50_Tanchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R0_50_37Rail= 	{
			/*next*/					&R0_50_37Road0,
			/*alternateroute*/			&R0_50_37Road0,
			/*supplier*/				&N0_50_Tanchon,		
			/*suppliee*/				&N0_37_Pukchong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlPuktaechon,	//2 bridges
							},
T::R0_50_37Road0= 	{
			/*next*/					&R0_50_37Road1,
			/*alternateroute*/			&R0_50_37Road1,
			/*supplier*/				&N0_50_Tanchon,		
			/*suppliee*/				&N0_37_Pukchong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRdTanchon0,
							},



T::R0_50_37Road1= 	{
			/*next*/					&R0_37_19Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_50_Tanchon,		
			/*suppliee*/				&N0_37_Pukchong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdTanchon1,
							},



T::R0_37_19Rail= 	{
			/*next*/					&R0_37_19Road,
			/*alternateroute*/			&R0_37_19Road,
			/*supplier*/				&N0_37_Pukchong,		
			/*suppliee*/				&N0_19_Hamhung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlNamdaechon,
							},

T::R0_37_19Road= 	{
			/*next*/					&R0_19_34Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_37_Pukchong,		
			/*suppliee*/				&N0_19_Hamhung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R0_19_34Rail= 	{
			/*next*/					&R0_19_34Road,
			/*alternateroute*/			&R0_19_34Road,
			/*supplier*/				&N0_19_Hamhung,		
			/*suppliee*/				&N1_34_Yonghung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlKumjinchon,
							},

T::R0_19_34Road= 	{
			/*next*/					&R0_8_9Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_19_Hamhung,		
			/*suppliee*/				&N1_34_Yonghung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R0_8_9Rail= 	{
			/*next*/					&R0_8_9Road,
			/*alternateroute*/			&R0_8_9Road,
			/*supplier*/				&N0_8_Manpo,		
			/*suppliee*/				&N0_9_Kangye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlManpo,
							},

T::R0_8_9Road= 	{
			/*next*/					&R0_9_10Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_8_Manpo,	
			/*suppliee*/				&N0_9_Kangye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R0_9_10Rail= 	{
			/*next*/					&R0_9_10Road,
			/*alternateroute*/			&R0_9_10Road,
			/*supplier*/				&N0_9_Kangye,		
			/*suppliee*/				&N0_10_Huichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlHuichon,
							},

T::R0_9_10Road= 	{
			/*next*/					&R0_10_11Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_9_Kangye,		
			/*suppliee*/				&N0_10_Huichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R0_10_11Rail= 	{
			/*next*/					&R0_10_11Road,
			/*alternateroute*/			&R0_10_11Road,
			/*supplier*/				&N0_10_Huichon,		
			/*suppliee*/				&N0_11_Kujang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

T::R0_10_11Road= 	{
			/*next*/					&R0_11_31Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_10_Huichon,		
			/*suppliee*/				&N0_11_Kujang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R0_11_31Rail= 	{
			/*next*/					&R0_44_45Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_31_Tokchon,		
			/*suppliee*/				&N0_11_Kujang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R0_44_45Rail= 	{
			/*next*/					&R0_46_48Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_44_Namsanni,	
			/*suppliee*/				&N0_45_Sakchu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R0_46_48Road= 	{
			/*next*/					&R0_57_46Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_46_Chongsongup,		
			/*suppliee*/				&N0_48_Kusong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R0_57_46Road= 	{
			/*next*/					&R0_45_48Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_57_Suiho,			
			/*suppliee*/				&N0_46_Chongsongup,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},



T::R0_45_48Rail= 	{
			/*next*/					&R0_48_4Rail,
			/*alternateroute*/			&R0_46_48Road,
			/*supplier*/				&N0_45_Sakchu,		
			/*suppliee*/				&N0_48_Kusong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R0_48_4Rail= 	{
			/*next*/					&R0_31_13Rail,
			/*alternateroute*/			&R0_48_4Road,
			/*supplier*/				&N0_48_Kusong,		
			/*suppliee*/				&N0_4_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},



T::R0_31_13Rail= 	{
			/*next*/					&R1_6_7Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N0_31_Tokchon,		
			/*suppliee*/				&N1_13_Samdung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},



//------------------------------------------------------------------------------
//supply routes for area 1

T::R1_6_7Rail= 	{
			/*next*/					&R1_6_7Road,
			/*alternateroute*/			&R1_6_7Road,
			/*supplier*/				&N1_6_Sukchon,
			/*suppliee*/				&N1_7_Pyongyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_6_7Road= 	{
			/*next*/					&R1_7_30Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_6_Sukchon,
			/*suppliee*/				&N1_7_Pyongyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							
			},
T::R1_7_30Rail= 	{
			/*next*/					&R1_13_29Rail,
			/*alternateroute*/			&R1_7_30Road,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_30_Nampo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_13_29Rail= 	{
			/*next*/					&R1_13_29Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_13_Samdung,
			/*suppliee*/				&N1_29_Kangdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlChongchon1,
							},
T::R1_13_29Road= 	{
			/*next*/					&R1_29_54Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_13_Samdung,
			/*suppliee*/				&N1_29_Kangdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_29_54Rail= 	{
			/*next*/					&R1_49_22Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_13_Samdung,
			/*suppliee*/				&N1_54_YulLi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlNan,
							},
T::R1_49_22Rail= 	{
			/*next*/					&R1_25_41Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_49_Hwangju,
			/*suppliee*/				&N1_22_Sariwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_25_41Road= 	{
			/*next*/					&R1_7_64Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_25_Pyongsan,
			/*suppliee*/				&N1_41_Ichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_7_64Road= 	{
			/*next*/					&R1_64_54Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_64_Sangwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_64_54Road= 	{
			/*next*/					&R1_22_65Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_64_Sangwon,
			/*suppliee*/				&N1_54_YulLi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_22_65Road= 	{
			/*next*/					&R1_65_54Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_22_Sariwon,
			/*suppliee*/				&N1_65_Nuang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_65_54Road= 	{
			/*next*/					&R1_25_63Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_65_Nuang,
			/*suppliee*/				&N1_54_YulLi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_25_63Road= 	{
			/*next*/					&R1_7_30Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_25_Pyongsan,
			/*suppliee*/				&N1_63_Suan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_7_30Road= 	{
			/*next*/					&R1_62_23Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_30_Nampo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_62_23Rail= 	{
			/*next*/					&R1_15_53Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_62_Chaeryong,
			/*suppliee*/				&N1_23_Changyon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},


T::R1_15_53Road= 	{
			/*next*/					&R1_53_55Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_15_Yangdok,
			/*suppliee*/				&N1_53_Koksan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_53_55Road= 	{
			/*next*/					&R1_12_7Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_53_Koksan,
			/*suppliee*/				&N1_55_Kanda,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R1_12_7Rail= 	{
			/*next*/					&R1_22_62Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_12_Sunchon,
			/*suppliee*/				&N1_7_Pyongyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_22_62Rail= 	{
			/*next*/					&R1_62_24Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_22_Sariwon,
			/*suppliee*/				&N1_62_Chaeryong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_62_24Rail= 	{
			/*next*/					&R1_24_61Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_62_Chaeryong,
			/*suppliee*/				&N1_24_Haeju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_24_61Rail= 	{
			/*next*/					&R1_61_27Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_24_Haeju,
			/*suppliee*/				&N1_61_Yonan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

T::R1_61_27Rail= 	{
			/*next*/					&R1_12_13Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_61_Yonan,
			/*suppliee*/				&N1_27_Kaesong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},


T::R1_12_13Rail= 	{
			/*next*/					&R1_7_49Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_12_Sunchon,
			/*suppliee*/				&N1_13_Samdung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},




T::R1_7_49Rail= 	{
			/*next*/					&R1_66_53Road,
			/*alternateroute*/			&R1_7_49Road0,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_49_Hwangju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlPyongyang,
							},
T::R1_66_53Road= 	{
			/*next*/					&R1_15_55Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_66_Singye,
			/*suppliee*/				&N1_53_Koksan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_15_55Road= 	{
			/*next*/					&R1_63_54Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_15_Yangdok,
			/*suppliee*/				&N1_55_Kanda,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_63_54Road= 	{
			/*next*/					&R1_71_57Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_63_Suan,
			/*suppliee*/				&N1_54_YulLi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_71_57Road= 	{
			/*next*/					&R1_42_71Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_71_Inje,
			/*suppliee*/				&N2_57_Sangnam,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R1_42_71Road= 	{
			/*next*/					&R1_55_21Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_42_Kansang,
			/*suppliee*/				&N1_71_Inje,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_55_21Road= 	{
			/*next*/					&R1_38_70Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_55_Kanda,
			/*suppliee*/				&N1_21_Wonsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_38_70Road= 	{
			/*next*/					&R1_71_36Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_38_Kumhwa,
			/*suppliee*/				&N1_70_Hwachon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_71_36Road= 	{
			/*next*/					&R1_71_12Road0,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_71_Inje,
			/*suppliee*/				&N1_36_Yangyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_71_12Road0= 	{
			/*next*/					&R1_71_12Road1,
			/*alternateroute*/			&R1_71_12Road1,
			/*supplier*/				&N1_71_Inje,
			/*suppliee*/				&N2_12_Chuncheon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdInje,
							},
T::R1_71_12Road1= 	{
			/*next*/					&R1_38_50Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_71_Inje,
			/*suppliee*/				&N2_12_Chuncheon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_38_50Road= 	{
			/*next*/					&R1_25_66Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_38_Kumhwa,
			/*suppliee*/				&N1_50_Yongpyong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_25_66Road= 	{
			/*next*/					&R1_50_12Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_25_Pyongsan,
			/*suppliee*/				&N1_66_Singye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_50_12Road= 	{
			/*next*/					&R1_41_28Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_50_Yongpyong,
			/*suppliee*/				&N2_12_Chuncheon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdPukhan1,
							},


T::R1_41_28Road= 	{
			/*next*/					&R1_7_49Road0,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_41_Ichon,
			/*suppliee*/				&N1_28_Pyonggang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R1_7_49Road0= 	{
			/*next*/					&R1_7_49Road1,
			/*alternateroute*/			&R1_7_49Road1,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_49_Hwangju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdPyongyang0,
							},
T::R1_7_49Road1= 	{
			/*next*/					&R1_22_25Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_7_Pyongyang,
			/*suppliee*/				&N1_49_Hwangju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdPyongyang1,
							},

T::R1_22_25Rail= 	{
			/*next*/					&R1_22_25Road,
			/*alternateroute*/			&R1_22_25Road,
			/*supplier*/				&N1_22_Sariwon,
			/*suppliee*/				&N1_25_Pyongsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_22_25Road= 	{
			/*next*/					&R1_25_26Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_22_Sariwon,
			/*suppliee*/				&N1_25_Pyongsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_25_26Rail= 	{
			/*next*/					&R1_25_26Road,
			/*alternateroute*/			&R1_25_26Road,
			/*supplier*/				&N1_25_Pyongsan,
			/*suppliee*/				&N1_26_Kumchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_25_26Road= 	{
			/*next*/					&R1_26_27Rail,
			/*alternateroute*/			NULL,
			/*suppliee*/				&N1_25_Pyongsan,
			/*suppliee*/				&N1_26_Kumchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_26_27Rail= 	{
			/*next*/					&R1_26_27Road,
			/*alternateroute*/			&R1_25_26Road,
			/*supplier*/				&N1_26_Kumchon,
			/*suppliee*/				&N1_27_Kaesong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_26_27Road= 	{
			/*next*/					&R1_27_75Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_26_Kumchon,
			/*suppliee*/				&N1_27_Kaesong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R1_27_75Rail= 	{
			/*next*/					&R1_27_75Road,
			/*alternateroute*/			&R1_27_75Road,
			/*supplier*/				&N1_27_Kaesong,
			/*suppliee*/				&N1_75_Panmunjom,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlYesong,
							},
T::R1_27_75Road= 	{
			/*next*/					&R1_75_40Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_27_Kaesong,
			/*suppliee*/				&N1_75_Panmunjom,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},

T::R1_75_40Rail=	{
			/*next*/					&R1_75_40Road,
			/*alternateroute*/			&R1_75_40Road,
			/*supplier*/				&N1_75_Panmunjom,
			/*suppliee*/				&N2_40_Munsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,  
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},
	
T::R1_75_40Road= 	{
			/*next*/					&R1_34_20Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_75_Panmunjom,
			/*suppliee*/				&N2_40_Munsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},

						
T::R1_34_20Rail=	{
			/*next*/					&R1_34_20Road,
			/*alternateroute*/			&R1_34_20Road,
			/*supplier*/				&N1_20_Kowon,	//INCORRECT &N1_34_Yonghung
			/*suppliee*/				&N1_20_Kowon,	
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlTokohig,
								},
	
T::R1_34_20Road= 	{
			/*next*/					&R1_20_21Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_34_Yonghung,
			/*suppliee*/				&N1_20_Kowon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},



T::R1_20_21Rail=	{
			/*next*/					&R1_20_21Road,
			/*alternateroute*/			&R1_20_21Road,
			/*supplier*/				&N1_20_Kowon,
			/*suppliee*/				&N1_21_Wonsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlKowon,
								},
	
T::R1_20_21Road= 	{
			/*next*/					&R1_21_52Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_20_Kowon,
			/*suppliee*/				&N1_21_Wonsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},

T::R1_21_52Rail=	{
			/*next*/					&R1_52_35Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_21_Wonsan,
			/*suppliee*/				&N1_52_Kojo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},

T::R1_52_35Rail=	{
			/*next*/					&R1_52_35Road,
			/*alternateroute*/			&R1_52_35Road,
			/*supplier*/				&N1_52_Kojo,
			/*suppliee*/				&N1_35_Kojin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},
	
T::R1_52_35Road= 	{
			/*next*/					&R1_35_42Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_52_Kojo,
			/*suppliee*/				&N1_35_Kojin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},


T::R1_35_42Rail=	{
			/*next*/					&R1_35_42Road,
			/*alternateroute*/			&R1_35_42Road,
			/*supplier*/				&N1_35_Kojin,
			/*suppliee*/				&N1_42_Kansang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},
	
T::R1_35_42Road= 	{
			/*next*/					&R1_42_36Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_35_Kojin,
			/*suppliee*/				&N1_42_Kansang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},



T::R1_42_36Rail=	{
			/*next*/					&R1_36_29Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_42_Kansang,
			/*suppliee*/				&N1_36_Yangyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},
	
T::R1_36_29Road= 	{
			/*next*/					&R1_13_14Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_36_Yangyang,
			/*suppliee*/				&N2_29_Kangnung,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},

T::R1_13_14Rail= 	{
			/*next*/					&R1_13_14Road,
			/*alternateroute*/			&R1_13_14Road,
			/*supplier*/				&N1_13_Samdung,
			/*suppliee*/				&N1_14_WaDong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},
T::R1_13_14Road= 	{
			/*next*/					&R1_14_15Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_13_Samdung,
			/*suppliee*/				&N1_14_WaDong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},

T::R1_14_15Rail= 	{
			/*next*/					&R1_14_15Road,
			/*alternateroute*/			&R1_14_15Road,
			/*supplier*/				&N1_14_WaDong,
			/*suppliee*/				&N1_15_Yangdok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},
T::R1_14_15Road= 	{
			/*next*/					&R1_15_20Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_14_WaDong,
			/*suppliee*/				&N1_15_Yangdok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},

T::R1_15_20Rail= 	{
			/*next*/					&R1_21_39Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_15_Yangdok,
			/*suppliee*/				&N1_20_Kowon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},

T::R1_21_39Rail= 	{
			/*next*/					&R1_21_39Road,
			/*alternateroute*/			&R1_21_39Road,
			/*supplier*/				&N1_21_Wonsan,
			/*suppliee*/				&N1_39_Kosan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},

T::R1_21_39Road= 	{
			/*next*/					&R1_39_40Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_21_Wonsan,
			/*suppliee*/				&N1_39_Kosan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},
T::R1_39_40Road= 	{
			/*next*/					&R1_40_68Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_39_Kosan,
			/*suppliee*/				&N1_40_Hoeyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},
T::R1_40_68Road= 	{
			/*next*/					&R1_70_12Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_40_Hoeyang,
			/*suppliee*/				&N1_68_Changdo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},
T::R1_70_12Road= 	{
			/*next*/					&R1_68_38Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_70_Hwachon,
			/*suppliee*/				&N2_12_Chuncheon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},

T::R1_68_38Road= 	{
			/*next*/					&R1_38_69Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_68_Changdo,
			/*suppliee*/				&N1_38_Kumhwa,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},

T::R1_38_69Road= 	{
			/*next*/					&R1_69_49Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_38_Kumhwa,
			/*suppliee*/				&N1_69_Kalmal,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},
T::R1_69_49Road= 	{
			/*next*/					&R1_30_7Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_69_Kalmal,		//####
			/*suppliee*/				&N2_49_Pochon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},


T::R1_30_7Rail= 	{
			/*next*/					&R1_30_7Road,
			/*alternateroute*/			&R1_30_7Road,
			/*supplier*/				&N1_30_Nampo,			
			/*suppliee*/				&N1_7_Pyongyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},

T::R1_30_7Road= 	{
			/*next*/					&R1_39_67Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_30_Nampo,				
			/*suppliee*/				&N1_7_Pyongyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
								},



T::R1_39_67Rail= 	{
			/*next*/					&R1_67_28Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_39_Kosan,
			/*suppliee*/				&N1_67_Sepo,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},
T::R1_67_28Rail= 	{
			/*next*/					&R1_28_43Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_67_Sepo,
			/*suppliee*/				&N1_28_Pyonggang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},
T::R1_28_43Rail= 	{
			/*next*/					&R1_43_56Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_28_Pyonggang,
			/*suppliee*/				&N1_43_Chorwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
								},		

T::R1_43_56Rail= 	{
			/*next*/					&R1_56_11Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_43_Chorwon,
			/*suppliee*/				&N1_56_Yonchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
						},

T::R1_56_11Rail= 	{
			/*next*/					&R1_28_38Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_56_Yonchon,
			/*suppliee*/				&N2_11_Uijongbu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlImjin,
						},		

T::R1_28_38Rail= 	{
			/*next*/					&R1_38_70Rail,
			/*alternateroute*/			&R1_28_38Road,
			/*supplier*/				&N1_28_Pyonggang,
			/*suppliee*/				&N1_38_Kumhwa,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_28_38Road= 	{
			/*next*/					&R1_38_70Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N1_28_Pyonggang,
			/*suppliee*/				&N1_38_Kumhwa,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R1_38_70Rail= 	{
			/*next*/					&R1_70_12Rail,
			/*alternateroute*/			&R1_38_70Road,
			/*supplier*/				&N1_38_Kumhwa,
			/*suppliee*/				&N1_70_Hwachon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R1_70_12Rail= 	{
			/*next*/					&R2_40_10Rail,
			/*alternateroute*/			&R1_70_12Road,
			/*supplier*/				&N1_70_Hwachon,
			/*suppliee*/				&N2_12_Chuncheon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

//-------------------------------------------------------------------------------
//Supply routes for area 2

T::R2_40_10Rail= 	{
			/*next*/					&R2_40_10Road0,
			/*alternateroute*/			&R2_40_10Road0,
			/*supplier*/				&N2_40_Munsan,			//####
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlMunsan,
							},

T::R2_40_10Road0= 	{
			/*next*/					&R2_40_10Road1,
			/*alternateroute*/			&R2_40_10Road1,				
			/*supplier*/				&N2_40_Munsan,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdMunsan0,
							},


T::R2_40_10Road1= 	{
			/*next*/					&R2_40_10Road2,
			/*alternateroute*/			&R2_40_10Road2,
			/*supplier*/				&N2_40_Munsan,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdMunsan1,
							},

T::R2_40_10Road2= 	{
			/*next*/					&R2_10_7Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_40_Munsan,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdMunsan2,
							},


T::R2_10_7Rail= 	{
			/*next*/					&R2_10_7Road0,
			/*alternateroute*/			&R2_10_7Road0,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlSeoul,
							},


T::R2_10_7Road0= 	{
			/*next*/					&R2_6_36Road,
			/*alternateroute*/			&R2_10_7Road1,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSeoul0,
							},
T::R2_6_36Road= 	{
			/*next*/					&R2_10_7Road1,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_6_Wonju,
			/*suppliee*/				&N3_36_Mokkye,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R2_10_7Road1= 	{
			/*next*/					&R2_10_7Road2,
			/*alternateroute*/			&R2_10_7Road2,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSeoul2,
							},


T::R2_10_7Road2= 	{
			/*next*/					&R2_10_7Road3,
			/*alternateroute*/			&R2_10_7Road3,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSeoul3,
							},



T::R2_10_7Road3= 	{
			/*next*/					&R2_10_7Road4,
			/*alternateroute*/			&R2_10_7Road4,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSeoul4,
							},



T::R2_10_7Road4= 	{
			/*next*/					&R2_10_7Road5,
			/*alternateroute*/			&R2_10_7Road5,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSeoul5,
							},



T::R2_10_7Road5= 	{
			/*next*/					&R2_7_14Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdSeoul6,
							},


T::R2_7_14Rail= 	{
			/*next*/					&R2_7_14Road,
			/*alternateroute*/			&R2_7_14Road,
			/*supplier*/				&N2_7_Suwon,
			/*suppliee*/				&N2_14_Osan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},




T::R2_7_14Road= 	{
			/*next*/					&R2_14_19Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_7_Suwon,				
			/*suppliee*/				&N2_14_Osan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R2_14_19Rail= 	{
			/*next*/					&R2_14_19Road,
			/*alternateroute*/			&R2_14_19Road,
			/*supplier*/				&N2_14_Osan,
			/*suppliee*/				&N3_19_Pyongtaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R2_14_19Road= 	{
			/*next*/					&R2_29_28Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_14_Osan,				
			/*suppliee*/				&N3_19_Pyongtaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R2_29_28Road= 	{
			/*next*/					&R2_28_30Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_29_Kangnung,				
			/*suppliee*/				&N2_28_Samchok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_28_30Road= 	{
			/*next*/					&R2_11_10Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_28_Samchok,				
			/*suppliee*/				&N3_30_Ulhin,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},



T::R2_11_10Rail= 	{
			/*next*/					&R2_11_10Road,
			/*alternateroute*/			&R2_11_10Road,
			/*supplier*/				&N2_11_Uijongbu,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R2_11_10Road= 	{
			/*next*/					&R2_49_11Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_11_Uijongbu,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_49_11Road= 	{
			/*next*/					&R2_48_10Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_49_Pochon,
			/*suppliee*/				&N2_11_Uijongbu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_48_10Road= 	{
			/*next*/					&R2_12_35Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_48_Kuri,
			/*suppliee*/				&N2_10_Seoul,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_12_35Road= 	{
			/*next*/					&R2_35_23Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_12_Chuncheon,
			/*suppliee*/				&N2_35_Hongchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_35_23Road= 	{
			/*next*/					&R2_40_11Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_35_Hongchon,
			/*suppliee*/				&N2_23_Hoensong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_40_11Road= 	{
			/*next*/					&R2_42_28Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_40_Munsan,
			/*suppliee*/				&N2_11_Uijongbu,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_42_28Road= 	{
			/*next*/					&R2_10_9Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_42_Chongson,
			/*suppliee*/				&N2_28_Samchok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_10_9Road= 	{
			/*next*/					&R2_43_5Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_9_Inchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_43_5Road= 	{
			/*next*/					&R2_23_6Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_43_Pyongchang,
			/*suppliee*/				&N3_5_Chechon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_23_6Road= 	{
			/*next*/					&R2_8_41Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_23_Hoensong,
			/*suppliee*/				&N2_6_Wonju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_8_41Road= 	{
			/*next*/					&R2_41_26Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_8_Songnam,
			/*suppliee*/				&N2_41_Ichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_41_26Road= 	{
			/*next*/					&R2_34_43Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_41_Ichon,
			/*suppliee*/				&N3_26_Changhowon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_34_43Road= 	{
			/*next*/					&R2_43_42Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_34_Yulchon,
			/*suppliee*/				&N2_43_Pyongchang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_43_42Road= 	{
			/*next*/					&R2_10_8Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_43_Pyongchang,
			/*suppliee*/				&N2_42_Chongson,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_10_8Road= 	{
			/*next*/					&R2_28_44Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N3_8_Songnam,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R2_28_44Road= 	{
			/*next*/					&R2_14_41Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_28_Samchok,
			/*suppliee*/				&N3_44_Taepaek,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R2_14_41Road= 	{
			/*next*/					&R2_7_8Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_14_Osan,
			/*suppliee*/				&N2_41_Ichon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_7_8Road= 	{
			/*next*/					&R2_9_7Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_7_Suwon,
			/*suppliee*/				&N2_8_Songnam,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R2_9_7Road= 	{
			/*next*/					&R2_57_34Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_9_Inchon,
			/*suppliee*/				&N2_7_Suwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R2_57_34Road= 	{
			/*next*/					&R2_10_58Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_57_Sangnam,
			/*suppliee*/				&N2_34_Yulchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R2_10_58Rail= 	{
			/*next*/					&R2_58_6Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_10_Seoul,
			/*suppliee*/				&N2_58_Yangpyong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlHan,
							},

T::R2_58_6Rail= 	{
			/*next*/					&R2_12_48Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_58_Yangpyong,
			/*suppliee*/				&N2_6_Wonju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R2_12_48Rail= 	{
			/*next*/					&R2_12_48Road0,
			/*alternateroute*/			&R2_12_48Road0,
			/*supplier*/				&N2_12_Chuncheon,
			/*suppliee*/				&N2_48_Kuri,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlPukhan0,
							},
T::R2_12_48Road0= 	{
			/*next*/					&R2_12_48Road1,
			/*alternateroute*/			&R2_12_48Road1,
			/*supplier*/				&N2_12_Chuncheon,				
			/*suppliee*/				&N2_48_Kuri,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdChuncheon0,
							},

T::R2_12_48Road1= 	{
			/*next*/					&R2_6_5Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_12_Chuncheon,				
			/*suppliee*/				&N2_48_Kuri,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdChuncheon1,
							},

T::R2_6_5Rail= 	{
			/*next*/					&R2_12_35Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_6_Wonju,
			/*suppliee*/				&N3_5_Chechon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

T::R2_12_35Rail= 	{
			/*next*/					&R2_35_23Rail,
			/*alternateroute*/			&R2_12_35Road,
			/*supplier*/				&N2_12_Chuncheon,
			/*suppliee*/				&N2_35_Hongchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R2_35_23Rail= 	{
			/*next*/					&R2_23_6Rail,
			/*alternateroute*/			&R2_35_23Road,
			/*supplier*/				&N2_35_Hongchon,
			/*suppliee*/				&N2_23_Hoensong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R2_23_6Rail= 	{
			/*next*/					&R3_19_3Rail,
			/*alternateroute*/			&R2_23_6Road,
			/*supplier*/				&N2_35_Hongchon,
			/*suppliee*/				&N2_23_Hoensong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

//-------------------------------------------------------------------------------
//Supply routes for area 3

T::R3_19_3Rail= 	{
			/*next*/					&R3_19_3Road,
			/*alternateroute*/			&R3_19_3Road,
			/*supplier*/				&N3_19_Pyongtaek,
			/*suppliee*/				&N3_3_Chonan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},



T::R3_19_3Road= 	{
			/*next*/					&R3_3_17Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_19_Pyongtaek,
			/*suppliee*/				&N3_3_Chonan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},



T::R3_3_17Rail= 	{
			/*next*/					&R3_3_17Road,
			/*alternateroute*/			&R3_3_17Road,
			/*supplier*/				&N3_3_Chonan,
			/*suppliee*/				&N3_17_Chochiwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlChonui,
							},


T::R3_3_17Road= 	{
			/*next*/					&R3_17_1Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_3_Chonan,
			/*suppliee*/				&N3_17_Chochiwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R3_17_1Rail= 	{
			/*next*/					&R3_3_64Rail,
			/*alternateroute*/			&R3_17_1Road,
			/*supplier*/				&N3_17_Chochiwon,
			/*suppliee*/				&N3_1_Taejon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_BrRlKum0,
							},
T::R3_3_64Rail= 	{
			/*next*/					&R3_64_65Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_3_Chonan,
			/*suppliee*/				&N3_64_Hongsong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

T::R3_64_65Rail= 	{
			/*next*/					&R3_65_66Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_64_Hongsong,
			/*suppliee*/				&N3_65_Hannae,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

T::R3_65_66Rail= 	{
			/*next*/					&R3_4_59Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_65_Hannae,
			/*suppliee*/				&N3_66_Taechon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R3_4_59Rail= 	{
			/*next*/					&R3_17_1Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_4_Chungju,
			/*suppliee*/				&N3_59_Koesan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},


T::R3_17_1Road= 	{
			/*next*/					&R3_62_16Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_17_Chochiwon,
			/*suppliee*/				&N3_1_Taejon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R3_62_16Road= 	{
			/*next*/					&R3_36_4Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_62_Noktong,
			/*suppliee*/				&N3_16_Yongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R3_36_4Road= 	{
			/*next*/					&R3_44_62Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_36_Mokkye,
			/*suppliee*/				&N3_4_Chungju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdChungju,
							},
T::R3_44_62Road= 	{
			/*next*/					&R3_24_21Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_44_Taepaek,
			/*suppliee*/				&N3_62_Noktong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R3_24_21Road= 	{
			/*next*/					&R3_21_22Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_24_Chomchon,
			/*suppliee*/				&N3_21_Sangju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R3_21_22Road= 	{
			/*next*/					&R3_20_24Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_21_Sangju,
			/*suppliee*/				&N3_22_Kimchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R3_20_24Road= 	{
			/*next*/					&R3_41_51Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_20_Yechon,
			/*suppliee*/				&N3_24_Chomchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R3_41_51Road= 	{
			/*next*/					&R3_60_24Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N2_41_Ichon,
			/*suppliee*/				&N3_51_Maesan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},
T::R3_60_24Road= 	{
			/*next*/					&R3_1_46Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_60_Mungyong,
			/*suppliee*/				&N3_24_Chomchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R3_1_46Rail= 	{
			/*next*/					&R3_1_46Road,
			/*alternateroute*/			&R3_1_46Road,
			/*supplier*/				&N3_1_Taejon,
			/*suppliee*/				&N3_46_Yongdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},


T::R3_1_46Road= 	{
			/*next*/					&R3_45_1Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_1_Taejon,
			/*suppliee*/				&N3_46_Yongdong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_BrRdKum1                                                                                                                                        ,
							},
T::R3_45_1Rail= 	{
			/*next*/					&R3_63_45Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_45_Nonsan,
			/*suppliee*/				&N3_1_Taejon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_63_45Rail= 	{
			/*next*/					&R3_66_63Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_63_Kunsan,
			/*suppliee*/				&N3_45_Nonsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_66_63Rail= 	{
			/*next*/					&R3_55_37Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_66_Taechon,
			/*suppliee*/				&N3_63_Kunsan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_55_37Road= 	{
			/*next*/					&R3_18_55Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_55_Uisong,
			/*suppliee*/				&N3_37_Kumi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_18_55Road= 	{
			/*next*/					&R3_61_16Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_18_Andong,
			/*suppliee*/				&N3_55_Uisong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_61_16Road= 	{
			/*next*/					&R3_59_2Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_61_Tanyang,
			/*suppliee*/				&N3_16_Yongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_59_2Rail= 	{
			/*next*/					&R3_2_1Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_59_Koesan,
			/*suppliee*/				&N3_2_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},

T::R3_2_1Rail= 	{
			/*next*/					&R3_4_61Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_2_Chongju,
			/*suppliee*/				&N3_1_Taejon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},

T::R3_4_61Road= 	{
			/*next*/					&R3_52_53Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_4_Chungju,
			/*suppliee*/				&N3_61_Tanyang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_52_53Road= 	{
			/*next*/					&R3_51_52Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_52_Kwangheywan,
			/*suppliee*/				&N3_53_Chinchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_51_52Road= 	{
			/*next*/					&R3_53_54Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_51_Maesan,
			/*suppliee*/				&N3_52_Kwangheywan,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_53_54Road= 	{
			/*next*/					&R3_54_2Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_53_Chinchon,
			/*suppliee*/				&N3_54_Chungpyong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_54_2Road= 	{
			/*next*/					&R3_4_60Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_54_Chungpyong,
			/*suppliee*/				&N3_2_Chongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_4_60Road= 	{
			/*next*/					&R3_46_22Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_4_Chungju,
			/*suppliee*/				&N3_60_Mungyong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},


T::R3_46_22Rail= 	{
			/*next*/					&R3_46_22Road,
			/*alternateroute*/			&R3_46_22Road,
			/*supplier*/				&N3_46_Yongdong,
			/*suppliee*/				&N3_22_Kimchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

T::R3_46_22Road= 	{
			/*next*/					&R3_18_20Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_46_Yongdong,
			/*suppliee*/				&N3_22_Kimchon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_18_20Road= 	{
			/*next*/					&R3_22_37Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_18_Andong,
			/*suppliee*/				&N3_20_Yechon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},



T::R3_22_37Road= 	{
			/*next*/					&R3_30_31Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_22_Kimchon,
			/*suppliee*/				&N3_37_Kumi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},

T::R3_30_31Road= 	{
			/*next*/					&R3_31_32Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_30_Ulhin,
			/*suppliee*/				&N3_31_Yonghae,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},

T::R3_31_32Road= 	{
			/*next*/					&R3_32_25Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_31_Yonghae,
			/*suppliee*/				&N3_32_Yongdok,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},

T::R3_32_25Road= 	{
			/*next*/					&R3_5_47Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_32_Yongdok,
			/*suppliee*/				&N3_25_Pohang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null                                                                                                                                        ,
							},
T::R3_5_47Rail= 	{
			/*next*/					&R3_47_16Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_5_Chechon,
			/*suppliee*/				&N3_47_Punggi,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R3_47_16Rail= 	{
			/*next*/					&R3_47_16Road,
			/*alternateroute*/			&R3_47_16Road,
			/*supplier*/				&N3_47_Punggi,
			/*suppliee*/				&N3_16_Yongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

T::R3_47_16Road= 	{
			/*next*/					&R3_16_18Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_47_Punggi,
			/*suppliee*/				&N3_16_Yongju,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},


T::R3_16_18Rail= 	{
			/*next*/					&R3_2_17Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_16_Yongju,
			/*suppliee*/				&N3_18_Andong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},
T::R3_2_17Rail= 	{
			/*next*/					&R3_16_18Road,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_2_Chongju,
			/*suppliee*/				&N3_17_Chochiwon,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},

T::R3_16_18Road= 	{
			/*next*/					&R3_18_25Rail,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_16_Yongju,
			/*suppliee*/				&N3_18_Andong,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRUCK,
			/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
			/*associated_brdg*/			UID_Null,
							},

T::R3_18_25Rail= 	{
			/*next*/					&LastRoute,
			/*alternateroute*/			NULL,
			/*supplier*/				&N3_16_Yongju,
			/*suppliee*/				&N3_25_Pohang,
			/*status*/					SR_ACTIVE,
			/*recommision_time*/		DAYS0,
			/*redsupplyBF*/				FIL_NULL,
			/*storespermobile*/			STORES_TRAIN,
			/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
			/*associated_brdg*/			UID_Null,
							},


T::LastRoute= 	{
			/*next*/					&LastRoute,
			/*alternateroute*/			NULL,
			/*supplier*/				NULL,
			/*suppliee*/				NULL,
			/*status*/					SR_LASTONE,

			};	

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//
//
//
//
SupplyLine

T::WestRoute = {
			/*AssociatedDepot[2]*/			{UID_RpRdSinuiju,UID_MyRdPyongyang},
			/*firstnode*/					&N0_0_Dangdong,
			/*splitsAB and BC*/				&N1_22_Sariwon,&N2_10_Seoul,
			/*MaxMobiles*/					MAXMOBILESONDOUBLETRACK,
			/*TodaysMobiles*/				MAXMOBILESONDOUBLETRACK,
			/*CurrMobiles*/					0,
			/*frontline*/					&N2_40_Munsan,
			/*attackpotential*/				0,
			},
T::CentralRoute = {
			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
			/*firstnode*/					&N0_8_Manpo,
			/*splitsAB and BC*/				&N3_53_Chinchon,&N2_11_Uijongbu,
			/*MaxMobiles*/					MAXMOBILESONSINGLETRACK,
			/*TodaysMobiles*/				MAXMOBILESONSINGLETRACK,
			/*CurrMobiles*/					0,
			/*frontline*/					&N1_56_Yonchon,
			/*attackpotential*/				0,
			},
T::EastRoute = {
			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
			/*firstnode*/					&N0_16_Chongjin,
			/*splitsAB and BC*/				&N1_21_Wonsan,&N2_28_Samchok,
			/*MaxMobiles*/					MAXMOBILESONSINGLETRACK,
			/*TodaysMobiles*/				MAXMOBILESONSINGLETRACK,
			/*CurrMobiles*/					0,
			/*frontline*/					&N2_42_Chongson,
			/*attackpotential*/				0,
			};
//DeadCode RDH 13Mar97 WestRoute = {
//DeadCode RDH 13Mar97 			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
//DeadCode RDH 13Mar97 			/*MaxMobiles*/					MAXMOBILESONSINGLEROAD,
//DeadCode RDH 13Mar97 			/*TodaysMobiles*/				MAXMOBILESONSINGLEROAD,
//DeadCode RDH 13Mar97 			/*CurrMobiles*/					0,
//DeadCode RDH 13Mar97 			/*frontline*/					&N1_6_Sukchon,				
//DeadCode RDH 13Mar97 			/*attackpotential*/				0,
//DeadCode RDH 13Mar97 			},
//DeadCode RDH 13Mar97 EastRoute = {
//DeadCode RDH 13Mar97 			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
//DeadCode RDH 13Mar97 			/*MaxMobiles*/					MAXMOBILESONSINGLEROAD,
//DeadCode RDH 13Mar97 			/*TodaysMobiles*/				MAXMOBILESONSINGLEROAD,
//DeadCode RDH 13Mar97 			/*CurrMobiles*/					0,
//DeadCode RDH 13Mar97 			/*frontline*/					&N2_49_Pochon,
//DeadCode RDH 13Mar97 			/*attackpotential*/				0,
//DeadCode RDH 13Mar97 			};


//------------------------------------------------------------------------------


AirFieldInfo	T::airfieldinfo[] =
{
		{//0
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdSinmak,
			/*northnodes[2]*/	{&N1_22_Sariwon,&N1_25_Pyongsan},	
			/*southnodes[2]*/	{&N1_26_Kumchon,&N1_61_Yonan},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//1
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdHwangju,
			/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_49_Hwangju},
			/*southnodes[2]*/	{&N1_22_Sariwon,&N1_62_Chaeryong},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//2
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdSinuiju,		
			/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_46_Chongsongup},	
			/*southnodes[2]*/	{&N0_2_Yomju,&N0_3_Sonchon},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		3
		},		
		{//3
			/*nationality*/	 	NAT_RED,						
			/*airfield*/		UID_AfRdSinuijuNE,
			/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_46_Chongsongup},	
			/*southnodes[2]*/	{&N0_2_Yomju,&N0_3_Sonchon},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		1
		},
		{//4
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdSunan,
			/*northnodes[2]*/	{&N1_6_Sukchon,&N1_12_Sunchon},	
			/*southnodes[2]*/	{&N1_29_Kangdong,&N1_7_Pyongyang},
			/*AirFieldType*/	AFT_LIGHTBOMBER,
			/*capacity*/		2
		},
		{//5
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdAntung,
			/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},	
			/*southnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		3
		},
		{//6
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdTaTung,
			/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},	
			/*southnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		3
		},
		{//7
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdUiju,
			/*northnodes[2]*/	{&N0_57_Suiho,&N0_46_Chongsongup},	
			/*southnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		1
		},
		{//8
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdAnak,
			/*northnodes[2]*/	{&N1_30_Nampo,&N1_49_Hwangju},	
			/*southnodes[2]*/	{&N1_62_Chaeryong,&N1_22_Sariwon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//9
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdSariwon,
			/*northnodes[2]*/	{&N1_22_Sariwon,&N1_49_Hwangju},	
			/*southnodes[2]*/	{&N1_62_Chaeryong,&N1_25_Pyongsan},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//10
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdYongyu,
			/*northnodes[2]*/	{&N1_6_Sukchon,&N1_12_Sunchon},	
			/*southnodes[2]*/	{&N1_29_Kangdong,&N1_7_Pyongyang},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//11
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdSinanju,
			/*northnodes[2]*/	{&N0_4_Chongju,&N0_5_Sinaju},	
			/*southnodes[2]*/	{&N1_6_Sukchon,&N1_12_Sunchon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//12
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdPyongni,
			/*northnodes[2]*/	{&N1_12_Sunchon,&N1_6_Sukchon},	
			/*southnodes[2]*/	{&N1_13_Samdung,&N1_7_Pyongyang},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//13
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdTaechon,
			/*northnodes[2]*/	{&N0_48_Kusong,&N0_11_Kujang},	
			/*southnodes[2]*/	{&N0_4_Chongju,&N0_5_Sinaju},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		2
		},
		{//14
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdNamsi,
			/*northnodes[2]*/	{&N0_2_Yomju,&N0_48_Kusong},	
			/*southnodes[2]*/	{&N0_3_Sonchon,&N0_4_Chongju},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		2
		},
		{//15
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdSaamcham,
			/*northnodes[2]*/	{&N0_11_Kujang,&N0_4_Chongju},	
			/*southnodes[2]*/	{&N0_5_Sinaju,&N0_31_Tokchon},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		2
		},
		{//16
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdPyongyangE,
			/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_29_Kangdong},	
			/*southnodes[2]*/	{&N1_49_Hwangju,&N1_22_Sariwon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//17
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdPyongyangM,
			/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_29_Kangdong},	
			/*southnodes[2]*/	{&N1_49_Hwangju,&N1_30_Nampo},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		1
		},
		{//18
			/*nationality*/	 	NAT_RED,
			/*airfield*/		UID_AfRdPyongyangD,
			/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_29_Kangdong},	
			/*southnodes[2]*/	{&N1_49_Hwangju,&N1_30_Nampo},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		1
		},
		{//19
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlKimpo,
			/*northnodes[2]*/	{&N2_39_Kimpo,&N2_40_Munsan},	
			/*southnodes[2]*/	{&N2_9_Inchon,&N2_10_Seoul},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		3
		},
		{//20
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlSeoul,
			/*northnodes[2]*/	{&N2_10_Seoul,&N2_9_Inchon},	
			/*southnodes[2]*/	{&N2_7_Suwon,&N2_8_Songnam},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		1
		},
		{//21
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlChuncheon,
			/*northnodes[2]*/	{&N2_12_Chuncheon,&N2_48_Kuri},	
			/*southnodes[2]*/	{&N2_58_Yangpyong,&N2_35_Hongchon},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//22
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlOsan,
			/*northnodes[2]*/	{&N2_14_Osan,&N2_7_Suwon},	
			/*southnodes[2]*/	{&N3_19_Pyongtaek,&N3_3_Chonan},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//23
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlSuwon,
			/*northnodes[2]*/	{&N2_8_Songnam,&N2_7_Suwon},	
			/*southnodes[2]*/	{&N3_19_Pyongtaek,&N2_14_Osan},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		2
		},
		{//24
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlPyongtaek,
			/*northnodes[2]*/	{&N3_19_Pyongtaek,&N2_14_Osan},	
			/*southnodes[2]*/	{&N3_3_Chonan,&N3_64_Hongsong},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//25
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlKunsan,
			/*northnodes[2]*/	{&N3_64_Hongsong,&N3_17_Chochiwon},	
			/*southnodes[2]*/	{&N3_65_Hannae,&N3_15_Kongju},
			/*AirFieldType*/	AFT_LIGHTBOMBER,
			/*capacity*/		2
		},
		{//26
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlTaejon,
			/*northnodes[2]*/	{&N3_1_Taejon,&N3_15_Kongju},	
			/*southnodes[2]*/	{&N3_45_Nonsan,&N3_46_Yongdong},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//27
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlTaegu,
			/*northnodes[2]*/	{&N3_22_Kimchon,&N3_37_Kumi},	
			/*southnodes[2]*/	{&N3_22_Kimchon,&N3_37_Kumi},
			/*AirFieldType*/	AFT_LOADEDJET,
			/*capacity*/		2
		},
		{//28
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlTaeguW,
			/*northnodes[2]*/	{&N3_22_Kimchon,&N3_37_Kumi},	
			/*southnodes[2]*/	{&N3_22_Kimchon,&N3_37_Kumi},
			/*AirFieldType*/	AFT_JET,
			/*capacity*/		1
		},
		{//29
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlKangnung,
			/*northnodes[2]*/	{&N2_29_Kangnung,&N1_36_Yangyang},	
			/*southnodes[2]*/	{&N2_28_Samchok,&N2_42_Chongson},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
		{//30
			/*nationality*/	 	NAT_BLUE,
			/*airfield*/		UID_AfBlPohang,
			/*northnodes[2]*/	{&N3_25_Pohang,&N3_32_Yongdok},	
			/*southnodes[2]*/	{&N3_25_Pohang,&N3_32_Yongdok},
			/*AirFieldType*/	AFT_PROPONLY,
			/*capacity*/		1
		},
//this must be the last one!
		{
			/*nationality*/	 	NAT_ALIGN,
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
		/*idtext*/			Debrief::T_ByPassBuilt_H,
		/*FIL_NULL*/			FIL_SMACK_CAMP1INTRO
	},
	{
		/*idtext*/			Debrief::T_DeceptionFound00_H,
		/*FIL_NULL*/			FIL_SMACK_CAMP2INTRO
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
	},
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
//		   {
//				/*type*/				D_AIRSUPERIORITY,
//				/*strikeac*/			0,
//				/*fighterac*/			16,
//				/*targets*/				0,
//				/*missionsset*/			0
//		   },
//		   {
//				/*type*/				D_CHOKE,
//				/*strikeac*/			64,
//				/*fighterac*/			16,
//				/*targets*/				0,
//				/*missionsset*/			0
//		   },
//		   {
//				/*type*/				D_SUPPLY,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//		   },
//		   {
//				/*type*/				D_AIRFIELDS,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//		   },
//		   {
//				/*type*/				D_RAIL,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//		   },
//		   {
//				/*type*/				D_ROAD,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//		   },
//		   {
//				/*type*/				D_ARMY,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//		   },
//		   {
//				/*type*/				D_RESTING,
//				/*strikeac*/			0,
//				/*fighterac*/			0,
//				/*targets*/				0,
//				/*missionsset*/			0
//		   }
//	}
//};
