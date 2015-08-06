//
//This is a crude attempt to sort out the list of globrefs so that they can be
//managed efficiently as a group - all cleared together, etcetera.
//
//
//
#ifdef	pass
#if	pass==1

#define	startstatic						\
enum	{	E_first_Static,

#define startglobal								\
enum	{	E_first_Global=(int)E_static_END,

#define	entry(name)	E_##name,

#define	endstatic						\
	E_static_END};

#define	endglobal						\
	E_global_END};						\
static	ULong	names[E_global_END]={0};

#endif

#if pass==2
#undef	startstatic
#undef	startglobal
#undef	endstatic
#undef	endglobal
#undef	entry

typedef	ULong& ULongRefBadTechniqueDoNotUse;
#define	startstatic						\
static	ULongRefBadTechniqueDoNotUse

#define startglobal								\
ULongRefBadTechniqueDoNotUse

#define	entry(name)	name=names[E_##name],

#define	endstatic						\
		LAST_STATIC=names[E_static_END];

#define	endglobal						\
		LAST_GLOBAL=names[E_global_END];

#endif

startstatic

entry(GR_Pack_BlankZero)
entry(GR_bluestrength)
entry(GR_bluefighters)
entry(GR_bluebombers)
entry(GR_redstrength)
entry(GR_redfighters)
entry(GR_redbombers)
entry(GR_greenstrength)
entry(GR_PlyrFormSize)
entry(GR_rndbluescouts)
entry(GR_PlyrWingSize)
entry(GR_EnemyWingSize00)
entry(GR_EnemyScoutType00)
entry(GR_EnemyChargeType00)
entry(GR_EnemyScoutType01)
entry(GR_EnemyChargeType01)
entry(GR_CampaignEnemyScoutType00)
entry(GR_CampaignEnemyChargeType00)
entry(GR_CampaignEnemyScoutType01)
entry(GR_CampaignEnemyChargeType01)
entry(GR_FriendlyChargeType00)
entry(GR_CampaignFriendlyScoutType00)
entry(GR_CampaignFriendlyChargeType00)
entry(GR_AngleStepSize)
entry(GR_HeightStepSize)
entry(GR_RangeStepSize)								//MS 02Jul96
entry(GR_EncounterSize)
entry(GR_ParentRand)								//MS 15Dec96
entry(GR_AngleSelect)
entry(GR_HeightSize)
entry(GR_RequiredNationality)
entry(GR_DesPitch)
entry(GR_DesHdg)
entry(GR_RandAngle)
entry(GR_PS_1)
entry(GR_PS_2)
entry(GR_PS_3)
entry(GR_PS_4)
entry(GR_PS_5)
entry(GR_PS_6)
entry(GR_PS_7)
entry(GR_PS_8)

entry(GR_FormType00)
entry(GR_FormType01)
entry(GR_FormType02)

entry(GR_EnemyScoutHomeBase)								//MS 18Apr96
entry(GR_EnemyChargeHomeBase)								//MS 18Apr96
entry(GR_FriendlyScoutHomeBase)								//MS 18Apr96
entry(GR_FriendlyChargeHomeBase)							//MS 18Apr96
entry(GR_FriendlyObjective)									//MS 18Apr96
entry(GR_EnemyObjective)									//MS 18Apr96
entry(GR_EnemyScoutMorale)									//MS 13Jun96
entry(GR_FriendlyScoutMorale)								//MS 13Jun96
entry(GR_EnemyScoutCharacter)								//MS 13Jun96
entry(GR_EnemyScoutTactician)								//MS 02Sep96
entry(GR_EnemyScoutMrAverage)								//MS 02Sep96
entry(GR_EnemyScoutCavalier)								//MS 02Sep96
entry(GR_FriendlyScoutCharacter)							//MS 02Oct96
entry(GR_FriendlyScoutTactician)							//MS 02Oct96
entry(GR_FriendlyScoutMrAverage)							//MS 02Oct96
entry(GR_FriendlyScoutCavalier)								//MS 02Oct96
entry(GR_FriendlyChargeCharacter)							//MS 13Jun96
entry(GR_FriendlyChargeMorale)							//MS 13Jun96
entry(GR_EnemyChargeCharacter)							//MS 13Jun96
entry(GR_EnemyChargeMorale)							//MS 13Jun96
entry(GR_FriendlyScoutSkillMin)								//MS 30Aug96
entry(GR_FriendlyChargeSkillMin)							//MS 30Aug96
entry(GR_EnemyScoutSkillMin)								//MS 30Aug96
entry(GR_EnemyChargeSkillMin)								//MS 30Aug96
entry(GR_FriendlyScoutSkillMax)								//MS 30Aug96
entry(GR_FriendlyChargeSkillMax)							//MS 30Aug96
entry(GR_EnemyScoutSkillMax)								//MS 30Aug96
entry(GR_EnemyChargeSkillMax)								//MS 30Aug96
entry(GR_ConvoyUid)											//RDH 09Aug96
entry(GR_EnemyHomeBase)										//MS 21Jun96
entry(GR_FriendHomeBase)										//MS 21Jun96
entry(GR_WP3)										//MS 21Jun96
entry(GR_GunSite)
entry(GR_AAASite)
entry(GR_MainPosX)
entry(GR_MainPosY)
entry(GR_MainPosZ)
entry(GR_SubPosX)
entry(GR_SubPosY)
entry(GR_SubPosZ)
entry(GR_MainAction)		//RDH 05Dec96
entry(GR_SubAction)		//RDH 05Dec96

//entry(GR_firstobject)
entry(GR_lastitem)
entry(GR_bfitem1)
entry(GR_bfitem2)
entry(GR_bfitem3)
entry(GR_bfitem4)
entry(GR_bfitem5)
entry(GR_bfitem6)
entry(GR_bfitem7)
entry(GR_ConvoyCount)
//entry(GR_WP1)
//entry(GR_WP2)
endstatic

startglobal


entry(GR_Pack_Takeoff)
entry(GR_Pack_Target)				//Set in scramble
entry(GR_Pack_Regroup)

entry(GR_MainObjective)										//MS 21Jun96
entry(GR_SubObjective)										//MS 21Jun96
entry(GR_NAT_ENEMY)
entry(GR_NAT_FRIEND)
entry(GR_Quit3DNow)
entry(GR_GlobalSkillMin)									//MS 30Aug96
entry(GR_GlobalSkillMax)									//MS 30Aug96
entry(GR_BLUESKILLCONFIG)
entry(GR_REDSKILLCONFIG)
entry(GR_FriendlyScoutType00)								//JIM 09Apr96
entry(GR_EnemyScoutSquad)									//MS 27Sep96
entry(GR_FriendlyScoutSquad)								//MS 27Sep96
entry(GR_EnemyChargeSquad)									//MS 27Sep96
entry(GR_FriendlyChargeSquad)								//MS 27Sep96
entry(GR_CPP)										//MS 21Jun96
entry(GR_CWP)										//MS 21Jun96
entry(GR_CloudBase)											//MS 21Nov96
entry(GR_OkToQuit3DNow)
entry(GR_amberstrength)
entry(GR_H2H_PT1)
entry(GR_H2H_PT2)
entry(GR_H2H_PT3)
entry(GR_H2H_PT4)			//AMM 01Jun98
entry(GR_H2H_PT5)
entry(GR_H2H_PT6)
entry(GR_H2H_PT7)
entry(GR_H2H_PT8)			//AMM 01Jun98
entry(GR_firstobject)
entry(GR_WP2)
entry(GR_WP1)
entry(GR_FormSize00)
entry(GR_FormSize01)
entry(GR_FormSize02)
entry(GR_FormSize03)
entry(GR_TankShape)
entry(GR_TroopShape)
entry(GR_GunShape)
entry(GR_DefendBarageShape)
entry(GR_Truck1Shape)
entry(GR_Truck2Shape)
entry(GR_TentsShape)
entry(GR_ParkedACShape)
entry(GR_GroundForceType)
entry(GR_WaveNum)
entry(GR_TakeOffTime)
entry(GR_AAALevel64K)
entry(GR_movecode)
entry(GR_TruckMoveCode)
endglobal
#undef entry
#else
#define	entry(name)	extern ULong& name;
extern	ULong GR_Scram_Alt[];
extern	ULong GR_Scram_AC[];
extern	ULong GR_Scram_Skill[];
extern	ULong GR_Scram_Squad[];
extern	ULong GR_Pack_Sq_Used[SQ_R_NONFLYABLE+1];
extern	ULong GR_Pack_Targ[][2];
extern	ULong GR_Pack_Home[8];
extern	ULong GR_Pack_TakeTime[8][3];

entry(GR_PACK_FIRST)
entry(GR_Pack_Takeoff)
entry(GR_Pack_Target)				//Set in scramble
entry(GR_Pack_Regroup)

entry(GR_MainObjective)										//MS 21Jun96
entry(GR_SubObjective)										//MS 21Jun96
entry(GR_WP1)
entry(GR_NAT_ENEMY)
entry(GR_NAT_FRIEND)
entry(GR_Quit3DNow)
entry(GR_GlobalSkillMin)									//MS 30Aug96
entry(GR_GlobalSkillMax)									//MS 30Aug96
entry(GR_FriendlyScoutType00)								//JIM 09Apr96
entry(GR_EnemyScoutSquad)									//MS 27Sep96
entry(GR_FriendlyScoutSquad)								//MS 27Sep96
entry(GR_EnemyChargeSquad)									//MS 27Sep96
entry(GR_FriendlyChargeSquad)								//MS 27Sep96
entry(GR_CPP)										//MS 21Jun96
entry(GR_CWP)										//MS 21Jun96
entry(GR_CloudBase)											//MS 21Nov96
entry(GR_OkToQuit3DNow)
entry(GR_amberstrength)
entry(GR_H2H_PT1)
entry(GR_H2H_PT2)
entry(GR_H2H_PT3)
entry(GR_H2H_PT4)			//AMM 01Jun98
entry(GR_H2H_PT5)
entry(GR_H2H_PT6)
entry(GR_H2H_PT7)
entry(GR_H2H_PT8)			//AMM 01Jun98
entry(GR_firstobject)
entry(GR_WP2)
entry(GR_FormSize00)
entry(GR_FormSize01)
entry(GR_FormSize02)
entry(GR_FormSize03)
entry(GR_GroundForceType)
entry(GR_WaveNum)
entry(GR_TakeOffTime)
entry(GR_AAALevel64K)
entry(GR_movecode)
entry(GR_TruckMoveCode)
#endif

#undef entry

/*	Actual external references (Aug '98):

Transite.obj : GR_NAT_FRIEND
Aaa.obj :	   GR_NAT_FRIEND
Rtestsh1.obj : GR_NAT_FRIEND
Transite.obj : GR_Quit3DNow
Stub3d.obj :   GR_Quit3DNow
Automove.obj : GR_Quit3DNow
Winmove.obj :  GR_Quit3DNow
Aaa.obj :      GR_NAT_ENEMY
Rtestsh1.obj : GR_NAT_ENEMY
Persons3.obj : GR_GlobalSkillMax
Rtestsh1.obj : GR_GlobalSkillMax
Persons3.obj : GR_GlobalSkillMin
Rtestsh1.obj : GR_GlobalSkillMin
Persons3.obj : GR_Pack_PlayerPos
Fullpane.obj : GR_Pack_PlayerPos
Persons3.obj : GR_Pack_PlayerSquad
Fullpane.obj : GR_Pack_PlayerSquad
Persons3.obj : GR_FriendlyScoutType00
Persons3.obj : GR_EnemyScoutSquad
Persons3.obj : GR_FriendlyScoutSquad
Persons3.obj : GR_EnemyChargeSquad
Persons3.obj : GR_FriendlyChargeSquad
Persons3.obj : GR_CPP
Persons3.obj : GR_CWP
Tank.obj :     GR_WP2
Tank.obj :     GR_WP1
Tank.obj :     GR_ConvoyCount
Tank.obj :     GR_SubAction
Tank.obj :     GR_SubObjective
Tank.obj :     GR_SubPosY
Tank.obj :     GR_SubPosX
Tank.obj :     GR_SubPosZ
Tank.obj :     GR_MainAction
Tank.obj :     GR_MainObjective
Tank.obj :     GR_MainPosY
Tank.obj :     GR_MainPosX
Tank.obj :     GR_MainPosZ
Fullpane.obj : GR_Pack_Target
Stub3d.obj :   GR_OkToQuit3DNow
Rtestsh1.obj : GR_CloudBase
Comms.obj :    GR_amberstrength
Winmove.obj :  GR_amberstrength
Comms.obj :    GR_H2H_PT8
Winmove.obj :  GR_H2H_PT8
Comms.obj :    GR_H2H_PT7
Winmove.obj :  GR_H2H_PT7
Comms.obj :    GR_H2H_PT6
Winmove.obj :  GR_H2H_PT6
Comms.obj :    GR_H2H_PT5
Winmove.obj :  GR_H2H_PT5
Comms.obj :    GR_H2H_PT4
Winmove.obj :  GR_H2H_PT4
Comms.obj :    GR_H2H_PT3
Winmove.obj :  GR_H2H_PT3
Comms.obj :    GR_H2H_PT2
Winmove.obj :  GR_H2H_PT2
Comms.obj :    GR_H2H_PT1
Winmove.obj :  GR_H2H_PT1
*/
