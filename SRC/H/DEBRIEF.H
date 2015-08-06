//
// Data structure for debrief info
//
//
//
//
//
//
#ifndef	DEBRIEF_INCLUDED
#define	DEBRIEF_INCLUDED
#include "bitcount.h"
#include "infoitem.h"
class	Debrief
{
public:
	enum	Types	{	REDAC, MIG,YAK, AAA,
						SUPPLY,MARTYARD,
						RAILBRIDGE,ROADBRIDGE,
						TRAIN,TRUCK,
						AIRFIELD,
						TROOPS,ARTILLERY,TANK,
						LOSSESTOREDAC, LOSSESTOMIG,	LOSSESTOYAK, LOSSESTOAAA, LOSSESTOOTHER,
						TARG_MAX};
	struct	TargKills
	{
		int	count[TARG_MAX];
		int	TotalLosses()	{return count[LOSSESTOREDAC]+count[LOSSESTOAAA]+count[LOSSESTOOTHER];}

		int& operator[](Types t) {return count[t];} 
	};


	struct	SquadKills
	{
		TargKills	count[(int)SQ_B_NONFLYSPOT+1];		//+1 for all
		TargKills&	operator[](SquadSelect s)	{return count[s];}
	};

	SquadKills	lastday,				//what happened on the last day
				lastperiod,				//what happened on the last period
				cumulative,
				total;					//sum it all
				//playerperiod,			//players actions last period. 
										//not directly displayed, but has effects
				//playertotal;			//sum for player's actions.
	enum	{PERIOD=0, DAY, TOTAL};
	char	displayperiod;

	enum	PlayerTypes {SORTIES, COMBATS, KILLS, LOSSES, PC_MAX};
	struct	PlayerCounts	
	{
 		int	count[PC_MAX];

		int& operator[](PlayerTypes t) {return count[t];} 

	};
	struct	PlayerTotals
	{
		PlayerCounts	count[(int)SQ_VEHICLES+1];
		PlayerCounts&	operator[](SquadSelect s)	{return count[s];}
	};
	PlayerTotals	playertotals;
	struct PlayQuickCounts
	{
		int	countground[TARG_MAX];
		int	countair[SQ_VEHICLES];
		int&	operator[](SquadSelect s)	{return countair[s];}
		int&	operator[](Types s)			{return countground[s];}
	};
	PlayQuickCounts	playerqmcounts,unqmcounts,redqmcounts;
	int	barcapkills,barcaplost;	
	
	struct	PlayerLog
	{	//8 bytes
		UByte		role;
		UByte		dummy;
		UByte		kills;
ONLYFIELD(UByte,	SquadSelect,pilotsquad);
ONLYFIELD(UWord,	UniqueID, 	target1);
ONLYFIELD(UWord,	UniqueID,	target2);
	};
	enum {DAYSPERCAMP=200,PERIODSPERDAY=3};	 //600*8=5K
	PlayerLog	playerlog[DAYSPERCAMP][PERIODSPERDAY];
	enum	{MAXSORTEDEVENTS=40};
	EventEntry	sortedevents[MAXSORTEDEVENTS];
	int		currlogday;
	int		currperiod;
	//Mark's display is:								//My flag:
	//
	//21/1/67											//DATE
	//  Yalu Bridge		Repair crews spotted			//TARGUID
	//  TaeJong			Blue forces taking the offensive//TARGUID
	//22/1/97											//DATE
	//  CIC				You are doing well. Keep it up	//NAME
	//  TaeJong			Ground forces request assistance//DISCARDTARGUID
	//
	//Note the 2 character indents and there are no grid lines.
	//You can view the dossier for TARGUID and DISCARDTARGUID lines
	//If it's an ongoing battle node you see the Army form instead
	//Thus, army requests in the DIS can be general.

		enum	DisEntry	{
			L2_DISTITLE_0,
			T_DefendWest01_H,
			T_DefendWest02_H,
			T_DefendWest03_H,
			T_DefendWest04_H,
			T_AttackWest01_H,
			T_AttackWest02_H,
			T_AttackWest03_H,
			T_AttackWest04_H,
			T_AttackWest05_H,
			T_AttackWest06_H,
			T_AttackCntr01_H,
			T_AttackCntr02_H,
			T_AttackCntr03_H,
			T_AttackCntr04_H,
			T_AttackCntr05_H,
			T_AttackCntr06_H,
			T_DefendCntr01_H,
			T_DefendCntr02_H,
			T_DefendCntr03_H,
			T_DefendCntr04_H,
			T_DefendCntr05_H,
			T_DefendCntr06_H,
			T_Advance01_H,
			T_Advance02_H,
			T_Advance03_H,
			T_Advance04_H,
			T_Advance05_H,
			T_Retreat01_H,
			T_DefendWest05_H,
			D_BritsArrive_H,
			T_Supply00_H,
			T_Supply01_H,
			T_Supply02_H,
			T_FAC00_H,
			T_Army00_H,
			T_Army01_H,
			T_Army02_H,
			T_Army03_H,
			T_Army04_H,
			T_Army05_H,
			T_Army06_H,
			T_Army07_H,
			T_FAC01_H,
			T_FAC02_H,
			T_FAC03_H,
			D_Flak00_H,
			D_Flak01_H,
			D_Flak02_H,
			D_Flak03_H,
			T_DeceptionFound00_H,
			D_DeceptionFound01_H,
			T_Bombers00_H,
			T_Bombers01_H,
			T_FAC04_H,
			D_DeceptionFound02_H,
			D_DeceptionFound03_H,
			T_Retreat02_H,
			T_Retreat03_H,
			D_Repairs00_H,
			T_ByPassBuilt_H,
			D_RailInterdict00_H,
			T_AF00_H,
			T_AF01_H,
			T_AF02_H,
			D_Repairs01_H,
			T_Airfield00_H,
			T_Airfield01_H,
			T_Airfield02_H,
			T_DefendWest06_H,
			T_Airfield04_H,
			T_Airfield05_H,
			T_Airfield06_H,
			T_USE_DAMAGED_WH_H,
			T_Replenish_H,
			D_AlJolson_H,
			T_SquadRotate_H,
			T_StoodDown_H,
			D_MiniText00_H,
			D_MiniText01_H,
			D_MiniText02_H,
			D_MiniText03_H,
			D_MiniText04_H,
			D_MiniText05_H,
			D_MiniText06_H,
			D_MiniText07_H,
			D_MiniText08_H,
			D_MiniText09_H,
			D_MiniText10_H,
			D_MiniText11_H,
			D_MiniText12_H,
			D_MiniText13_H,
			D_MiniText14_H,
			D_MiniText15_H,
			D_MiniText16_H,
			D_MiniText17_H,
			D_MiniText18_H,
			D_MiniText19_H,
			D_MiniText20_H,
			D_MiniText21_H,
			D_MiniText22_H,
			D_MiniText23_H,
			D_MiniText24_H

		};

	enum	OneOffDisses
	{
		OOD_HutTruck=1,
		OOD_Monk=2,
		//4
		//8

	};
	int	oneoffdisses;

	bool	OneOffDiss(OneOffDisses trial)	
	{
		if (oneoffdisses&(int)trial)
			return	true;
		oneoffdisses|=(int)trial;
		return false;
	}

	enum	TypeFlag	{TARGUID,DATE,NAME,DISCARDTARGUID};
	struct	DisLog
	{	//4 bytes per item
		ULong	typeflag:2,	
			msgowner:15,
			msgtextid:15;
	};
	enum	{DISISALLTOOMUCH=256,DISISITFORTODAY=20};
	DisLog	alldis[DISISALLTOOMUCH];
	int		disgoeshere;
	//alldis is a circular list.
	//vape up to the next date to make room for the next days requests
	//so disgoeshere will generally point at an empty slot.

	DisLog	disday[DISISITFORTODAY];
	//disday is cleared out every day
	//There would not be an initial DATE entry
	//If we want, messages generated during the three periods could 
	//be separated by DATE entries.
	//When the disday is appended to the alldis, a DATE entry is manufactured,
	//and any DISCARDTARGUIDs or DATE entries are ignored.
	//disday is then cleared.
	//we use msgowner to hold the day number
//DEADCODE JIM 03/03/99 	struct	ArmyReq
//DEADCODE JIM 03/03/99 	{	//these fields control what is printed in the list
//DEADCODE JIM 03/03/99 		int			forcename;
//DEADCODE JIM 03/03/99 		int			forcenum;
//DEADCODE JIM 03/03/99 		int			requesttext;
//DEADCODE JIM 03/03/99 		//these fields control what happens when you hit authorise
//DEADCODE JIM 03/03/99 		UniqueID	attacknode;
//DEADCODE JIM 03/03/99 		int			attackmethod;	//same idea as target type control in DIS
//DEADCODE JIM 03/03/99 	};
//DEADCODE JIM 03/03/99 	ArmyReq	armyrequests[3][16];
	//3 fronts, 16 messages per front per day.

//	void	NextPeriod();
//	void	NextPeriod(SquadKills& period,SquadKills& day);
//	void	NextDay();
};

#endif

