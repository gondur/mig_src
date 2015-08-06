//
// Mark's idea of 1 structure to represent all 3 wps associated with 1 node
//
//
//
//
//
//
//



SuperBattleNode	battlenodes[]=
{
	{	//LEVEL 4 //2 similar hill nodes
/*place*/		UID_BNE_4A,IDS_LEFTFLANK
/*flanks*/		{UID_NULL,UID_BNE_4B,NOT_LEFT},
/*in*/			{UID_BNE_4AI,ATTACKEASY,
				BF_ReForceOnRoad,BF_LineAttack,	BF_DefendThin,BF_RetreatThrough},
/*out*/			{UID_BNE_4AO,DEFENDADV,
				BF_ReinforceOpen,BF_ArcNoFlank,	BF_DefendSmArc,BF_RetreatThrough},
/*inroute*/		{UID_BNE_5A,
				BF_BThinRoad,BF_BThinRoad,		BF_RThinRoad,BF_RThinRoad}
	},
	{	//LEVEL 4 //2nd node
/*place*/		UID_BNE_4B,IDS_RIGHTFLANK
/*flanks*/		{UID_BNE_4A,UID_NULL,NOT_RIGHT},
/*in*/			{UID_BNE_4BI,ATTACKEASY,
				BF_ReForceOnRoad,BF_LineAttack,	BF_DefendThin,BF_RetreatThrough},
/*out*/			{UID_BNE_4BO,DEFENDADV,
				BF_ReinforceOpen,BF_ArcNoFlank,	BF_DefendSmArc,BF_RetreatThrough},
/*inroute*/		{UID_BNE_5A,
				BF_BThinRoad,BF_BThinRoad,		BF_RThinRoad,BF_RThinRoad}
	},

	{	//LEVEL 5 //ambush at back
/*place*/		UID_BNE_5A,IDS_MOUNTAINPASS,
/*flanks*/		{UID_NULL,UID_NULL,NOT_LINKED},
/*in*/			{UID_BNE_5AI,ATTACKEASY,
/*reinforce/attack*/	BF_ReinforceOnRoad,BF_AttackRoadSide,		
/*defend/retreat*/		BF_LayRoadAmbush,BF_EnterAmbush},
/*out*/			{UID_BNE_5AO,NOADV,
/*reinforce/attack*/	BF_ReinforceOnRoad,BF_AttackRoadSide,		
/*defend/retreat*/		BF_LayRoadAmbush,BF_EnterAmbushRoad},
/*inroute*/		{UID_BNE_6A,
				BF_BThinRoad,BF_BThinRoad,		BF_RThinRoad,BF_RThinRoad}
	},

	{	//LEVEL 6 //root node
/*place*/		UID_BNE_6A,IDS_LASTSTANDHILL,
/*flanks*/		{UID_NULL,UID_NULL,NOT_LINKED},
/*in*/			{UID_NULL},

/*out*/			{UID_BNE_6AO,DEFENDEASY,
				BF_ReForceOpen,BF_FlatAttack,  BF_DefendArc,BF_RetreatArc},
/*inroute*/		{UID_NULL}

	},

};

