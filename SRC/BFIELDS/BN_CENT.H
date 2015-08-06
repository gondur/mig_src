#undef NODE
#define	NODE(num)		UID_BNC_##num##_XX

LocalUID::SuperBattleDesc	centralbattledescs[]=
{

//*******************************************************
//NOT DONE YET

{	BATTLE("C1_RED.bn","FIL_BAT_C1_RED"),{NODE(1a),NODE(4a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	/*DEPART LINE 0a*/
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0b*/
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_ATT_WtrTrp,BF_ATT_WtrTrp}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_ATT_WtrTrp,BF_ATT_WtrTrp}
	},
	{	/*DEPART LINE 0D*/
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),NODE(0e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1d),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_ATT_WtrTrp,BF_ATT_WtrTrp}
	},
	{	/*DEPART LINE 0E*/
			PLACE(0e,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0d),NODE(0f),F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1e),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_ATT_WtrTrp,BF_ATT_WtrTrp}
	},
	{	/*DEPART LINE 0F*/
			PLACE(0f,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(0e),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Bank,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*inroute*/		{NODE(1f),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//FRONT LINE
	{	/*SOUTH OF RIVER, FRONT LINE 1a*/
			PLACE(1a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*SOUTH OF RIVER, FRONT LINE 1b*/
			PLACE(1b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER ISLAND, FRONT LINE 1c*/
			PLACE(1c,PHRASE_POSOTOWN),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER BANK, FRONT LINE 1D*/
			PLACE(1d,PHRASE_RIVERFORD),
/*flanks*/		{NODE(1c),NODE(1e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER BANK, FRONT LINE 1E*/
			PLACE(1e,PHRASE_POSSTOWN),
/*flanks*/		{NODE(1d),NODE(1f),F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER BANK, FRONT LINE 1F*/
			PLACE(1f,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1e),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Bank,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*inroute*/		{NODE(2d),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//SECOND LINE, FIRE SUPPORT
	{	/*IN TOWN, FRONT LINE 2a*/
			PLACE(2a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*IN TOWN, FRONT LINE 2b*/
			PLACE(2b,PHRASE_POSOTOWN),
/*flanks*/		{NODE(2a),NODE(2c),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*IN TOWN, FRONT LINE 2c*/
			PLACE(2c,PHRASE_POSOTOWN),
/*flanks*/		{NODE(2b),NODE(2d),F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(3b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

	{	/*IN TOWN, FRONT LINE 2d*/
			PLACE(2d,PHRASE_POSOTOWN),
/*flanks*/		{NODE(2c),UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(3b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//THIRD LINE, COMMAND POST AND RESERVES
	{	/*STRADDLE ROAD, FRONT LINE 3a*/
			PLACE(3a,PHRASE_GROUPOFHUTS),
/*flanks*/		{UID_NULL,NODE(3b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(4a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*STRADDLE ROAD, FRONT LINE 3b*/
			PLACE(3b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(3a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(4a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//FOURTH LINE, ESCAPE ROUTE
	{	/*STRADDLE ROAD, FRONT LINE 4a*/
			PLACE(4a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
///*inroute*/		{UID_NULL,
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

}
},

//********
//WONJU IS SUPPLY, FIGHT ON RED SIDE

{	BATTLE("C2_RED.bn","FIL_BAT_C2_RED"),{NODE(1a),NODE(4a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	/*DEPART LINE 0a*/
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TANKS,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1a),
//BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_ATT_WtrTrp,BF_ATT_WtrTrp}
				BF_C2R_0A1A, BF_C2R_0A1A, BF_C2R_0A1A, BF_C2R_0A1A}
	},
	{	/*DEPART LINE 0b*/
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Invis},
/*out*/			{L::DEFENDEASY,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0D*/
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),NODE(0e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*inroute*/		{NODE(1d),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0E*/
			PLACE(0e,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0d),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1e),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//FRONT LINE
	{	/*FRONT LINE 1a*/
			PLACE(1a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
//BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*FRONT LINE 1b*/
			PLACE(1b,PHRASE_HILLROAD),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*FRONT LINE 1c*/
			PLACE(1c,PHRASE_RIDGELINE),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDEASY,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*FRONT LINE 1D*/
			PLACE(1d,PHRASE_HILLSIDE),
/*flanks*/		{NODE(1c),NODE(1e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*FRONT LINE 1E*/
			PLACE(1e,PHRASE_TREELINE),
/*flanks*/		{NODE(1d),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	

//SECOND LINE, FIRE SUPPORT
	{	/*SUPPORT LINE 2a*/
			PLACE(2a,PHRASE_TREELINE),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*SUPPORT LINE 2b*/
			PLACE(2b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(2a),NODE(2c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*SUPPORT LINE 2c*/
			PLACE(2c,PHRASE_WOODEDAREA),
/*flanks*/		{NODE(2b),NODE(2d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(3b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

	{	/*SUPPORT LINE 2d*/
			PLACE(2d,PHRASE_HILLROAD),
/*flanks*/		{NODE(2c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(3b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//THIRD LINE, COMMAND POST AND RESERVES
	{	/*LINE 3a*/
			PLACE(3a,PHRASE_TOWNCENTRE),
/*flanks*/		{UID_NULL,NODE(3b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(4a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*LINE 3b*/
			PLACE(3b,PHRASE_TOWNCENTRE),
/*flanks*/		{NODE(3a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(4a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//FOURTH LINE, ESCAPE ROUTE
	{	/*STRADDLE ROAD, FRONT LINE 4a*/
			PLACE(4a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
///*inroute*/		{UID_NULL,
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

}
},


//*******************************************************
//SOUTH OF CHUNCHEON
//All done

{	BATTLE("C4_RED.bn","FIL_BAT_C4_RED"),{NODE(1a),NODE(3a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	/*DEPART LINE 0a*/
			PLACE(0a,PHRASE_VALLEYFLOOR),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(MORTAR,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_CROSSOPEN}
	},
	{	/*DEPART LINE 0b*/
			PLACE(0b,PHRASE_HILLTOP),
/*flanks*/		{NODE(0a),NODE(0c),F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,MORTAR),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_BASEOFSLOPE}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_HILLTOP),
/*flanks*/		{NODE(0b),NODE(0d),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_INPASS}
	},
	{	/*DEPART LINE 0D*/
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(MORTARTRUCK,MORTAR),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_ROUGHTERRAIN}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_HILLROAD),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1b,PHRASE_HILLTOP),
/*flanks*/		{NODE(1a),NODE(1c),F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHTREES}
	},
	{	/*RIVER ISLAND, FRONT LINE 1c*/
			PLACE(1c,PHRASE_TREELINE),
/*flanks*/		{NODE(1b),NODE(1d),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHTREES}
	},
	{	/*RIVER BANK, FRONT LINE 1D*/
			PLACE(1d,PHRASE_FORESTAREA),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_SKIRTINGTREES}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_POSCIVILIAN),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_INPASS}
	},
	{	
			PLACE(2b,PHRASE_POSMAINSTREET),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_INPASS}
	},

//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

//FOURTH LINE, ESCAPE ROUTE
	{	/*STRADDLE ROAD, FRONT LINE 4a*/
			PLACE(3a,PHRASE_BLOCKINGPOS),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_BlkSlt,BF_RET_Mid},
///*inroute*/		{UID_NULL,
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_INPASS}
	},
}
},

//*******************************************************
//No advantages set, no convoy routes set
//JUST SOUTH OF HWACHON

{	BATTLE("C5_RED.bn","FIL_BAT_C5_RED"),{NODE(1a),NODE(4a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	/*DEPART LINE 0a*/
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0b*/
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c),F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),NODE(0d),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0D*/
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_STREAM),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1b,PHRASE_STREAM),
/*flanks*/		{NODE(1a),NODE(1c),F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER ISLAND, FRONT LINE 1c*/
			PLACE(1c,PHRASE_HILLSIDE),
/*flanks*/		{NODE(1b),NODE(1d),F::NOT_LEFT},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDEASY,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER BANK, FRONT LINE 1D*/
			PLACE(1d,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_POSCIVILIAN),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(2b,PHRASE_RIVERFORD),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

	{	/*STRADDLE ROAD, FRONT LINE 3a*/
			PLACE(3a,PHRASE_POSMAINSTREET),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(4a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4

//FOURTH LINE, ESCAPE ROUTE
	{	/*STRADDLE ROAD, FRONT LINE 4a*/
			PLACE(4a,PHRASE_BLOCKINGPOS),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
///*inroute*/		{UID_NULL,
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
}
},

//*******************************************************
//Pyonggang
//done , not played yet											//MS 20Apr99

{	BATTLE("C6_RED.bn","FIL_BAT_C6_RED"),{NODE(1a),NODE(3a)},
{
	{	
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(MORTAR,MORTAR),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(0c,PHRASE_SMALLVILLAGE),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TANKS,TANKS),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(0d,PHRASE_RIDGELINE),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1b,PHRASE_RIDGELINE),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1c,PHRASE_CROSSROADS),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{INITFORCE(ARTILLARY,ARTILLARY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1d,PHRASE_VALLEYRIM),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_ENTRYTOTOWN),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(2b,PHRASE_TREELINE),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

	{	
			PLACE(3a,PHRASE_TOWNCENTRE),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{UID_NULL,
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	}
}
},

//*******************************************************
//Samdung, east of Pyongyang
//links are checked

{	BATTLE("C7_RED.bn","FIL_BAT_C7_RED"),{NODE(1a),NODE(2a)},
{
	{	
			PLACE(0a,PHRASE_OPENGROUND),
				/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),NODE(0e)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0e,PHRASE_RIVERBANK),
/*flanks*/		{NODE(0d),NODE(0f)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1e),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0f,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0e),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1f),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

	{	
			PLACE(1a,PHRASE_ENTRYGULLEY),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1b,PHRASE_RIVERBANK),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1c,PHRASE_RIVERBANK),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1d,PHRASE_RIVERFORD),
/*flanks*/		{NODE(1c),NODE(1e)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1e,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1d),NODE(1f)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1f,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1e),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_STREAM),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(2b,PHRASE_BRIDGECROSSING),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

	{	
			PLACE(3a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{UID_NULL,
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
}
},
//*****************
//******************
//*******************************************************
//SMALL BATTLE AT PUSAN PERIMETER
//All links have been checked, positions checked.

{	BATTLE("C1_UN.bn","FIL_BAT_C1_UN"),{NODE(1a),NODE(2a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(MORTAR,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_C1U_0A1A,BF_C1U_0A1A,		BF_C1U_0A1A,BF_C1U_0A1A}
	},
	{	
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TANKS,ARTILLARY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_C1U_0B1B,BF_C1U_0B1B,		BF_C1U_0B1B,BF_C1U_0B1B}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(MORTAR,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_THROUGHPADDY}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_HILLSIDE),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_BASEOFSLOPE}
	},
	{	
			PLACE(1b,PHRASE_VALLEYFLOOR),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_INPASS}
	},
	{	
			PLACE(1c,PHRASE_RIDGELINE),
/*flanks*/		{NODE(1b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_ROUGHTERRAIN}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{
			PLACE(2a,PHRASE_BLOCKINGPOS),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{UID_NULL,
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
}
},

//*******************************************************
//WONJU, REDS ARE ON THE ATTACK

{	BATTLE("C2_UN.bn","FIL_BAT_C2_UN"),{NODE(1a),NODE(2a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	/*DEPART LINE 0a*/
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0b*/
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0D*/
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1d),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//FRONT LINE
	{	/*SOUTH OF RIVER, FRONT LINE 1a*/
			PLACE(1a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*SOUTH OF RIVER, FRONT LINE 1b*/
			PLACE(1b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER ISLAND, FRONT LINE 1c*/
			PLACE(1c,PHRASE_POSOTOWN),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER BANK, FRONT LINE 1D*/
			PLACE(1d,PHRASE_RIVERFORD),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//LAST LINE, AGGGHGHHHH!!!!
	{	/*CROSSROADS*/
			PLACE(2a,PHRASE_CROSSROADS),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{UID_NULL,
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

}
},



//*******************************************************
//SOUTH OF CHUNCHEON, JUST NORTH OF HONGCHON
//

{	BATTLE("C4_UN.bn","FIL_BAT_C4_UN"),{NODE(1a),NODE(3a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	/*DEPART LINE 0a*/
			PLACE(0a,PHRASE_HILLROAD),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(MORTARTRUCK,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_CROSSOPEN}
	},
	{	/*DEPART LINE 0b*/
			PLACE(0b,PHRASE_HILLTOP),
/*flanks*/		{NODE(0a),NODE(0c),F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,MORTAR),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_BASEOFSLOPE}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_TREELINE),
/*flanks*/		{NODE(0b),NODE(0d),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_INPASS}
	},
	{	/*DEPART LINE 0D*/
			PLACE(0d,PHRASE_FORESTAREA),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(MORTARTRUCK,MORTAR),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_ROUGHTERRAIN}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_VALLEYFLOOR),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1b,PHRASE_HILLTOP),
/*flanks*/		{NODE(1a),NODE(1c),F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_CROSSOPEN}
	},
	{	/*RIVER ISLAND, FRONT LINE 1c*/
			PLACE(1c,PHRASE_HILLTOP),
/*flanks*/		{NODE(1b),NODE(1d),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_CROSSOPEN}
	},
	{	/*RIVER BANK, FRONT LINE 1D*/
			PLACE(1d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_HILLROAD),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(2b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

//FOURTH LINE, ESCAPE ROUTE
	{	/*STRADDLE ROAD, FRONT LINE 4a*/
			PLACE(3a,PHRASE_TOWNCENTRE),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_BlkSlt,BF_RET_Mid},
///*inroute*/		{UID_NULL,
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_INPASS}
	},
}
},

//*******************************************************
//South of Hwachon, North of Chuncheon - bollox

{	BATTLE("C5_UN.bn","FIL_BAT_C5_UN"),{NODE(1a),NODE(2a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	/*DEPART LINE 0a*/
			PLACE(0a,PHRASE_RIVERBANK),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_CROSSOPEN}
	},
	{	/*DEPART LINE 0b*/
			PLACE(0b,PHRASE_VALLEYFLOOR),
/*flanks*/		{NODE(0a),NODE(0c),F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_BASEOFSLOPE}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_HILLTOP),
/*flanks*/		{NODE(0b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_INPASS}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_RIVERBANK),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1b,PHRASE_VALLEYRIM),
/*flanks*/		{NODE(1a),NODE(1c),F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp,IDS_PHRASE_INPASS}
	},
	{	/*RIVER ISLAND, FRONT LINE 1c*/
			PLACE(1c,PHRASE_HILLTOP),
/*flanks*/		{NODE(1b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_CROSSOPEN}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_CROSSROADS),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
///*inroute*/		{UID_NULL,
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_INPASS}
	},
}
},

//*******************************************************
//South of Pyonggang
//done, not played												//MS 20Apr99

{	BATTLE("C6_UN.bn","FIL_BAT_C6_UN"),{NODE(1a),NODE(3a)},
{
	{	
			PLACE(0a,PHRASE_ENTRYTOTOWN),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(MORTAR,MORTAR),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(0b,PHRASE_ENTRYTOTOWN),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(0c,PHRASE_ENTRYTOTOWN),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TANKS,TANKS),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(0d,PHRASE_ENTRYTOTOWN),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1b,PHRASE_RIDGELINE),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1c,PHRASE_CROSSROADS),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{INITFORCE(ARTILLARY,ARTILLARY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1d,PHRASE_VALLEYRIM),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_HILLSIDE),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(2b,PHRASE_RIDGELINE),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

	{	
			PLACE(3a,PHRASE_SMALLVILLAGE),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{UID_NULL,
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	}
}
},

//*******************************************************
//Samdung, mirror of red side
//links are checked

{	BATTLE("C7_UN.bn","FIL_BAT_C7_UN"),{NODE(1a),NODE(2a)},
{
	{	
			PLACE(0a,PHRASE_ENTRYGULLEY),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0b,PHRASE_RIVERBANK),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0c,PHRASE_RIVERBANK),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0d,PHRASE_RIVERFORD),
/*flanks*/		{NODE(0c),NODE(0e)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0e,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0d),NODE(0f)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1e),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0f,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0e),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1f),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

	{	
			PLACE(1a,PHRASE_OPENGROUND),
				/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1c),NODE(1e)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1e,PHRASE_RIVERBANK),
/*flanks*/		{NODE(1d),NODE(1f)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1f,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1e),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},



//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{UID_NULL,
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
}
},

//*****************
//*******************************************************
//FRONT LINE IS CHIPYONGNI, UN SIDE OF LINE
//

{	BATTLE("C3_UN.bn","FIL_BAT_C3_UN"),{NODE(1b),NODE(4a)},
{
	{	
			PLACE(0a,PHRASE_POSOTOWN),
/*flanks*/		{NODE(0b),UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(0b,PHRASE_POSOTOWN),
/*flanks*/		{NODE(0c),NODE(0a),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,MORTAR),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(0c,PHRASE_POSOTOWN),
/*flanks*/		{NODE(0d),NODE(0b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(ARTILLARY,MORTAR),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(0d,PHRASE_POSOTOWN),
/*flanks*/		{UID_NULL,NODE(0c),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(MORTARTRUCK,MORTAR),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	
//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

	{	
			PLACE(1a,PHRASE_HILLSIDE),
/*flanks*/		{NODE(1b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},
	{	
			PLACE(1b,PHRASE_HILLTOWN),
/*flanks*/		{NODE(1c),NODE(1a)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},
	{	
			PLACE(1c,PHRASE_PADDYFIELDS),
/*flanks*/		{NODE(1d),NODE(1b)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},
	{	
			PLACE(1d,PHRASE_ENTRYGULLEY),
/*flanks*/		{UID_NULL,NODE(1c),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_GROUPOFHUTS),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},

	{	
			PLACE(2b,PHRASE_POSMAINSTREET),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},


//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

	{	
			PLACE(3a,PHRASE_BLOCKINGPOS),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(4a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4

	{	
			PLACE(4a,PHRASE_BLOCKINGPOS),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{UID_NULL,
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},


}
},

//*******************************************************
//PUSH FROM WONJU TO HOENGSONG, RED SIDE OF LINE
//

{	BATTLE("C3_Red.bn","FIL_BAT_C3_RED"),{NODE(1b),NODE(4a)},
{	
	{	/*1a*/
			PLACE(1a,PHRASE_HILLROAD),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*1b*/
			PLACE(1b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*FRONT LINE 1c*/
			PLACE(1c,PHRASE_HILLROAD),
/*flanks*/		{NODE(1b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//NEXT 2nd

	{	/*1a*/
			PLACE(2a,PHRASE_HILLROAD),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*1b*/
			PLACE(2b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(2a),NODE(2c)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(3b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*FRONT LINE 1c*/
			PLACE(2c,PHRASE_HILLROAD),
/*flanks*/		{NODE(2b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//line 3

	{	/*1a*/
			PLACE(3a,PHRASE_HILLROAD),
/*flanks*/		{UID_NULL,NODE(3b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(4a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*1b*/
			PLACE(3b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(3a),NODE(3c)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(4a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*FRONT LINE 1c*/
			PLACE(3c,PHRASE_HILLROAD),
/*flanks*/		{NODE(3b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(4a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//last line

	{	/*FRONT LINE 1c*/
			PLACE(4a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
///*inroute*/		{NODE(4a),
//				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}

	},

}
},
////////////////// END OF LIST ///////////////////////////
{{NULL}}
};
