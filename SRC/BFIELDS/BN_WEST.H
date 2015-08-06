#undef NODE
#define	NODE(num)		UID_BNW_##num##_XX
//SayAndQuit
LocalUID::SuperBattleDesc	westbattledescs[]=
{
//////////////////////////

//initforce, away and home!!!!

{	BATTLE("osan_s.bn","FIL_BAT_OSAN"),{NODE(1a),NODE(2a)},
{
//ATTACKER'S LINE OF DEPARTURE




//FRONT LINE
	{	/*OPEN PLAIN, FRONT LINE 1a*/
	PLACE(		1a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TANKS,TANKS),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*OPEN PLAIN, FRONT LINE 1b*/
			PLACE(1b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*OPEN PLAIN, FRONT LINE 1c*/
			PLACE(1c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*SMALL HILL, FRONT LINE 1D*/
			PLACE(1d,PHRASE_HILLSIDE),
/*flanks*/		{NODE(1c),NODE(1e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*inroute*/		{NODE(2c),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*SMALL HILL, FRONT LINE 1E*/
			PLACE(1e,PHRASE_HILLSIDE),
/*flanks*/		{NODE(1d),NODE(1f)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Rgt},
/*inroute*/		{NODE(2c),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*OPEN PLAIN, FRONTRIGHT LINE 1F*/
			PLACE(1f,PHRASE_HILLSIDE),
/*flanks*/		{NODE(1e),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2d),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//SECOND LINE, FIRE SUPPORT
	{	/*OPEN PLAIN, FRONT LINE 2a*/
			PLACE(2a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
///*inroute*/		{NODE(3a),
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*OPEN PLAIN, FRONT LINE 1b*/
			PLACE(2b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(2a),NODE(2c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
///*inroute*/		{NODE(3b),
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/*OPEN PLAIN, FRONT LINE 1c*/
			PLACE(2c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(2b),NODE(2d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
///*inroute*/		{NODE(3b),
//				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*SMALL HILL, FRONT LINE 1D*/
			PLACE(2d,PHRASE_HILLSIDE),
				/*flanks*/		{NODE(2c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
///*inroute*/		{NODE(3c),
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

}
},


//*******************************************************
//PYONGYANG

{	BATTLE("W7_UN.bn","FIL_BAT_W7_UN"),{NODE(1a),NODE(2a)},
{
	{	
			PLACE(0a,PHRASE_POSSTOWN),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{
			PLACE(0b,PHRASE_POSOTOWN),
/*flanks*/		{NODE(0a),NODE(0c),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{
			PLACE(0c,PHRASE_RIVERBANK),
/*flanks*/		{NODE(0b),NODE(0d),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{
			PLACE(0d,PHRASE_BRIDGECROSSING),
/*flanks*/		{NODE(0c),NODE(0e),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0e,PHRASE_BRIDGECROSSING),
/*flanks*/		{NODE(0d),NODE(0f),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1e),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{
			PLACE(0f,PHRASE_POSMAINSTREET),
/*flanks*/		{NODE(0e),UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1f),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{
			PLACE(1a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1b,PHRASE_POSOTOWN),
/*flanks*/		{NODE(1a),NODE(1c),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1c,PHRASE_PADDYFIELDS),
/*flanks*/		{NODE(1b),NODE(1d),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1d,PHRASE_CROSSROADS),
/*flanks*/		{NODE(1c),NODE(1e),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1e,PHRASE_POSCIVILIAN),
/*flanks*/		{NODE(1d),NODE(1f),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{
			PLACE(1f,PHRASE_POSCIVILIAN),
/*flanks*/		{NODE(1e),UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
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

//*******************************************************
//REDS attack, south of Sariwon, road and rail, road is on right
//positions are linked

{	BATTLE("W6_UN.bn","FIL_BAT_W6_UN"),{NODE(1a),NODE(4a)},
{
	{	
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(0b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(0a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{
			PLACE(1a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
	{
			PLACE(2a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(3a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(2b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(3b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
	{
			PLACE(3a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(3b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(4a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(3b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(3a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(4b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4
	{
			PLACE(4a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(4b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(5a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(4b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(4a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(5a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5

//FOURTH LINE, ESCAPE ROUTE
	{	/*STRADDLE ROAD, FRONT LINE 4a*/
			PLACE(5a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*inroute*/		{UID_NULL,
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
}
},

//*******************************************************
//Into Munsan from Kaesong

{	BATTLE("W5_UN.bn","FIL_BAT_W5_UN"),{NODE(1a),NODE(3a)},
{
	{	
			PLACE(0a,PHRASE_TOWNCENTRE),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(ARTILLARY,TANKS),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHPADDY},
	},
	{
			PLACE(0b,PHRASE_TOWNCENTRE),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TANKS,ARTILLARY),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHPADDY},
	},
	{
			PLACE(0c,PHRASE_TOWNCENTRE),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TROOPSONLY,MORTAR),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1c),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHPADDY}
	},
	{
			PLACE(0d,PHRASE_TOWNCENTRE),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(MORTARTRUCK,MORTARTRUCK),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1d),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHPADDY}
	},
//1111

	{
			PLACE(1a,PHRASE_FERRYPOINT),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},
	{
			PLACE(1b,PHRASE_RIVERFORD),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},
	{
			PLACE(1c,PHRASE_RIVERBANK),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},
	{
			PLACE(1d,PHRASE_RIVERFORD),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2c),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},

//22222
	{
			PLACE(2a,PHRASE_POSOTOWN),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_USESIDESTREET}
	},
	{
			PLACE(2b,PHRASE_ENTRYTOTOWN),
/*flanks*/		{NODE(2a),NODE(2c)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_ONMAINHIGHWAY}
	},
	{
			PLACE(2c,PHRASE_POSSTOWN),
/*flanks*/		{NODE(2b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_USESIDESTREET}
	},

//33333333
	{
			PLACE(3a,PHRASE_POSCIVILIAN),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
///*inroute*/		{NODE(3a),
//				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},

}
},

//*******************************************************
//FRONT LINE IS SEOUL
//A allows tanks

{	BATTLE("W4_UN.bn","FIL_BAT_W4_UN"),{NODE(1a),NODE(4a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	/*DEPART LINE 0a*/
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TANKS,TANKS),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
//TempCode MS 15Mar99 				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*DEPART LINE 0b*/
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_ATT_WtrTrp,BF_ATT_WtrTrp}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_ATT_WtrTrp,BF_ATT_WtrTrp}
	},
	{	/*DEPART LINE 0D*/
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),NODE(0e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1d),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_ATT_WtrTrp,BF_ATT_WtrTrp}
	},
	{	/*DEPART LINE 0E*/
			PLACE(0e,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0d),NODE(0f),F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1e),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_ATT_WtrTrp,BF_ATT_WtrTrp}
	},
	{	/*DEPART LINE 0F*/
			PLACE(0f,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(0e),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Bank,BF_ATT_ArcTrp,	BF_DEF_ArcSlt_N,BF_RET_Lft},
/*inroute*/		{NODE(1f),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
//TempCode MS 16Mar99 				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
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
			PLACE(1c,PHRASE_FERRYPOINT),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER BANK, FRONT LINE 1D*/
			PLACE(1d,PHRASE_BRIDGECROSSING),
/*flanks*/		{NODE(1c),NODE(1e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER BANK, FRONT LINE 1E*/
			PLACE(1e,PHRASE_PADDYFIELDS),
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

//*******************************************************
//BETWEEN SUWON AND OSAN
//Positions correct, links checked

{	BATTLE("W3_UN.bn","FIL_BAT_W3_UN"),{NODE(1a),NODE(2a)},
{
	{	
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1a),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},
	{
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1b),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},
	{
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1c),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
	{
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{
			PLACE(1a,PHRASE_FORESTAREA),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
	{
			PLACE(1b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
	{
			PLACE(1c,PHRASE_FORESTAREA),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
	{
			PLACE(1d,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_ENTRYTOTOWN),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{UID_NULL,
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
}
},

//*******************************************************
//FRONT LINE IS CHONAN
//d and e allow tanks

{	BATTLE("W2_UN.bn","FIL_BAT_W2_UN"),{NODE(0a),NODE(3a)},
{
	{	
			PLACE(0a,PHRASE_POSSTOWN),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{
			PLACE(0b,PHRASE_POSOTOWN),
/*flanks*/		{NODE(0a),NODE(0c),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{INITFORCE(TANKS,TANKS),
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),NODE(0d),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{INITFORCE(ARTILLARY,TANKS),
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),NODE(0e),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,MORTARTRUCK),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{
			PLACE(0e,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0d),UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{INITFORCE(TANKS,TANKS),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1e),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_POSOTOWN),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1b,PHRASE_POSCIVILIAN),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1c,PHRASE_POSMAINSTREET),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDEASY,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1d,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1c),NODE(1e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1e,PHRASE_ENTRYTOTOWN),
/*flanks*/		{NODE(1d),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_Astern,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_POSOTOWN),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(2b,PHRASE_POSOTOWN),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//THIRD LINE, COMMAND POST AND RESERVES
	{	/*STRADDLE ROAD, FRONT LINE 3a*/
			PLACE(3a,PHRASE_POSOTOWN),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*inroute*/		{UID_NULL,
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
}
},



//*******************************************************
//FRONT LINE IS KONGJU, UN SIDE OF LINE
//

{	BATTLE("W1_UN.bn","FIL_BAT_W1_UN"),{NODE(1b),NODE(3a)},
{
	{	/*1a*/
			PLACE(1a,RIVER_SOUTHWESTOFTOWN),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*1b*/
			PLACE(1b,RIVER_WESTOFTOWN),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(3a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*FRONT LINE 1c*/
			PLACE(1c,RIVER_NORTHWESTOFTOWN),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*1d*/
			PLACE(1d,RIVER_NORTHOFTOWN),
/*flanks*/		{NODE(1c),NODE(1e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*RIVER BANK, FRONT LINE 1E*/
			PLACE(1e,RIVER_EASTOFTOWN),
/*flanks*/		{NODE(1d),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2b),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//SECOND LINE, SECONDARY AND REGROUP
	{	/* 2a*/
			PLACE(2a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	/* 2b*/
			PLACE(2b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
//THIRD LINE, FIRESUPPORT
	{	/*STRADDLE ROAD, FRONT LINE 3a*/
			PLACE(3a,SMALLHAMLETONROAD),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*inroute*/		{NODE(4a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
//FOURTH LINE, CP AND RESERVE
	{	/*STRADDLE ROAD, FRONT LINE 4a*/
			PLACE(4a,RESERVE),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*inroute*/		{UID_NULL,
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

}
},

//*******************************************************
//JUST SOUTH OF PYONGTAEK

{	BATTLE("W2_RED.bn","FIL_BAT_W2_RED"),{NODE(0a),NODE(4a)},
{

	{	
			PLACE(0a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TANKS,TANKS),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(0b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(0a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TANKS,TANKS),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{	
			PLACE(1a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(1b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
	{	
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
			PLACE(2b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

	{	
			PLACE(3a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(3b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(4a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{	
			PLACE(3b,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(3a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(4a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4
	{	
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
//aghhh

{	BATTLE("W3_RED.bn","FIL_BAT_W3_RED"),{NODE(1a),NODE(2a)},
{
	{	
			PLACE(0a,PHRASE_FORESTAREA),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1a),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},
	{
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1b),
				BF_MOV_LinFst,BF_MOV_LinFst,		BF_MOV_LinFst,BF_MOV_LinFst}
	},
	{
			PLACE(0c,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1c),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
	{
			PLACE(0d,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{
			PLACE(1a,PHRASE_FORESTAREA),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
	{
			PLACE(1b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
	{
			PLACE(1c,PHRASE_FORESTAREA),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
	{
			PLACE(1d,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

	{	
			PLACE(2a,PHRASE_STREAM),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{UID_NULL,
				BF_MOV_ColFst,BF_MOV_ColFst,		BF_MOV_ColFst,BF_MOV_ColFst}
	},
}
},

//*******************************************************
//Into Seoul
//

{	BATTLE("W4_RED.bn","FIL_BAT_W4_RED"),{NODE(1a),NODE(2a)},
{
//ATTACKER'S LINE OF DEPARTURE

	{	/*DEPART LINE 0a*/
			PLACE(0a,PHRASE_PADDYFIELDS),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{	/*DEPART LINE 0b*/
			PLACE(0b,PHRASE_FERRYPOINT),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{	/*DEPART LINE 0c*/
			PLACE(0c,PHRASE_POSSTOWN),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1c),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{	/*DEPART LINE 0D*/
			PLACE(0d,PHRASE_BRIDGECROSSING),
/*flanks*/		{NODE(0c),NODE(0e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1d),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{	/*DEPART LINE 0E*/
			PLACE(0e,PHRASE_POSOTOWN),
/*flanks*/		{NODE(0d),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{INITFORCE(TROOPSONLY,TROOPSONLY),
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1e),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},

//FRONT LINE
	{	/*SOUTH OF RIVER, FRONT LINE 1a*/
			PLACE(1a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_RAILCUTTING}
	},
	{	/*SOUTH OF RIVER, FRONT LINE 1b*/
			PLACE(1b,PHRASE_FERRYPOINT),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_CROSSOPEN}
	},
	{	/*RIVER ISLAND, FRONT LINE 1c*/
			PLACE(1c,PHRASE_POSOTOWN),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDEASY,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_THROUGHBUILDINGS}
	},
	{	/*RIVER BANK, FRONT LINE 1D*/
			PLACE(1d,PHRASE_LINEMAINROAD),
/*flanks*/		{NODE(1c),NODE(1e)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_HEADMAINSTREET}
	},
	{	/*RIVER BANK, FRONT LINE 1E*/
			PLACE(1e,PHRASE_POSMAINSTREET),
/*flanks*/		{NODE(1d),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,IDS_PHRASE_THROUGHBUILDINGS}
	},

	{	
			PLACE(2a,PHRASE_POSCIVILIAN),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
///*inroute*/		{UID_NULL,
//				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp,PHRASE_ONMAINHIGHWAY}
	},

}
},

//*******************************************************
//Into Kaesong from munsan
//NOT DONE YET

{	BATTLE("W5_RED.bn","FIL_BAT_W5_RED"),{NODE(1a),NODE(3a)},
{
	{	
			PLACE(0a,PHRASE_TOWNCENTRE),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(ARTILLARY,TANKS),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHPADDY},
	},
	{
			PLACE(0b,PHRASE_TOWNCENTRE),
/*flanks*/		{NODE(0a),NODE(0c)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TANKS,ARTILLARY),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHPADDY},
	},
	{
			PLACE(0c,PHRASE_TOWNCENTRE),
/*flanks*/		{NODE(0b),NODE(0d)},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(TROOPSONLY,MORTAR),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1c),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHPADDY}
	},
	{
			PLACE(0d,PHRASE_TOWNCENTRE),
/*flanks*/		{NODE(0c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{INITFORCE(MORTARTRUCK,MORTARTRUCK),
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(1d),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_THROUGHPADDY}
	},
//1111

	{
			PLACE(1a,PHRASE_FERRYPOINT),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},
	{
			PLACE(1b,PHRASE_RIVERFORD),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},
	{
			PLACE(1c,PHRASE_RIVERBANK),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2b),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},
	{
			PLACE(1d,PHRASE_RIVERFORD),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(2c),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},

//22222
	{
			PLACE(2a,PHRASE_POSOTOWN),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_USESIDESTREET}
	},
	{
			PLACE(2b,PHRASE_ENTRYTOTOWN),
/*flanks*/		{NODE(2a),NODE(2c)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_ONMAINHIGHWAY}
	},
	{
			PLACE(2c,PHRASE_POSSTOWN),
/*flanks*/		{NODE(2b),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_USESIDESTREET}
	},

//33333333
	{
			PLACE(3a,PHRASE_POSCIVILIAN),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Mid},
///*inroute*/		{NODE(3a),
//				BF_FAST,BF_FAST,		BF_FAST,BF_FAST,IDS_PHRASE_CROSSOPEN}
	},

}
},

//*******************************************************
//South of Sariwon, road and rail, road is on left 
//positions are linked

{	BATTLE("W6_RED.bn","FIL_BAT_W6_RED"),{NODE(1a),NODE(4a)},
{

	{	
			PLACE(0a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(1a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(0b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(0a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	{
			PLACE(1a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(1b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(1a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
	{
			PLACE(2a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(2b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(2b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(2a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(3b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
	{
			PLACE(3a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(3b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(4a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(3b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(3a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(4b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4
	{
			PLACE(4a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,NODE(4b),F::NOT_LEFT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(5a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	
			PLACE(4b,PHRASE_OPENGROUND),
/*flanks*/		{NODE(4a),UID_NULL,F::NOT_RIGHT},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(5a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5

	{	
			PLACE(5a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*inroute*/		{UID_NULL,
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

}
},

//*******************************************************
//REDS DEFEND AT PYONGYANG
//All fields checked and A-OK

{	BATTLE("W7_RED.bn","FIL_BAT_W7_RED"),{NODE(1a),NODE(2a)},
{
	{	
			PLACE(0a,PHRASE_OPENGROUND),
/*flanks*/		{UID_NULL,NODE(0b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{
			PLACE(0b,PHRASE_POSOTOWN),
/*flanks*/		{NODE(0a),NODE(0c),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1b),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{
			PLACE(0c,PHRASE_PADDYFIELDS),
/*flanks*/		{NODE(0b),NODE(0d),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1c),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{
			PLACE(0d,PHRASE_CROSSROADS),
/*flanks*/		{NODE(0c),NODE(0e),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(1d),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(0e,PHRASE_POSCIVILIAN),
/*flanks*/		{NODE(0d),NODE(0f),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(1e),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{
			PLACE(0f,PHRASE_POSCIVILIAN),
/*flanks*/		{NODE(0e),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(1f),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

	{	
			PLACE(1a,PHRASE_POSSTOWN),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{
			PLACE(1b,PHRASE_POSOTOWN),
/*flanks*/		{NODE(1a),NODE(1c),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},
	{
			PLACE(1c,PHRASE_RIVERBANK),
/*flanks*/		{NODE(1b),NODE(1d),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{
			PLACE(1d,PHRASE_BRIDGECROSSING),
/*flanks*/		{NODE(1c),NODE(1e),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_FAST,BF_FAST,		BF_FAST,BF_FAST}
	},
	{
			PLACE(1e,PHRASE_BRIDGECROSSING),
/*flanks*/		{NODE(1d),NODE(1f),F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{
			PLACE(1f,PHRASE_POSMAINSTREET),
/*flanks*/		{NODE(1e),UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Rgt},
/*inroute*/		{NODE(2a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
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

//*******************************************************
//FRONT LINE IS KONGJU, RED SIDE OF LINE
//

{	BATTLE("W1_Red.bn","FIL_BAT_W1_RED"),{NODE(1b),NODE(3a)},
{
	{	/*1a*/
			PLACE(1a,RIVER_WESTOFTOWN),
/*flanks*/		{UID_NULL,NODE(1b),F::NOT_LEFT},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*1b*/
			PLACE(1b,RIVER_NORTHWESTOFTOWN),
/*flanks*/		{NODE(1a),NODE(1c)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*FRONT LINE 1c*/
			PLACE(1c,RIVER_NORTHOFTOWN),
/*flanks*/		{NODE(1b),NODE(1d)},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Invis},
/*out*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Invis},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},
	{	/*1d*/
			PLACE(1d,MAINEASTHIGHWAY),
/*flanks*/		{NODE(1c),UID_NULL,F::NOT_LINKED},
/*in*/			{L::DEFENDADV,
				BF_HLD_Open,BF_ATT_LinTrp,	BF_DEF_LinTrp,BF_RET_Lft},
/*out*/			{L::DEFENDADV,
				BF_HLD_Bank,BF_ATT_StandOff,	BF_DEF_LinTrp,BF_RET_Lft},
/*inroute*/		{NODE(2a),
				BF_MOV_ColTrp,BF_MOV_ColTrp,		BF_MOV_ColTrp,BF_MOV_ColTrp}
	},

//SECOND LINE, FIRE SUPPORT
	{	/* 2a*/
			PLACE(2a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Mid},
/*inroute*/		{NODE(3a),
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

//THIRD LINE, ESCAPE ROUTE
	{	/*STRADDLE ROAD, 3a*/
			PLACE(3a,PHRASE_LINEMAINROAD),
/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
/*in*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*out*/			{L::NOADV,
				BF_HLD_Open,BF_ATT_PassTrp,	BF_DEF_BlkSlt,BF_RET_Rgt},
/*inroute*/		{UID_NULL,
				BF_MOV_LinTrp,BF_MOV_LinTrp,		BF_MOV_LinTrp,BF_MOV_LinTrp}
	},

}
},

//////////////////////////////////
{{NULL}}  	//End of West battle nodes.
};	//End of West battle nodes...

