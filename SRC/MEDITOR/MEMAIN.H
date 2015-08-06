//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>


#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>

#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>

#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>

#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>



#include <dosdefs.h>
#include <uniqueid.h>
#include "Files.g"
//#include	"readenum.h"
//#include <angles.h>
class info_base;
//---------------------------------------------------------------------------
enum	UidBandNum{
		PilotedAcBANDNum	,//		=	0x0000,
		WayPointBANDNum		,//	=	0x0100,
		MissileBANDNum		,//		=	0x0400,		WayPointBANDEND = MissileBAND,
		LandscapeBANDNum	,//		=	0x0600,
		RedRailBandNum		,//		=	0x0800,
		RedRoadBANDNum		,//		=	0x0C00,
		RedAcBANDNum		,//		=	0x0E00,
		BlueAcBANDNum		,//		=	0x1000,
		AmberAirfieldBANDNum,//		=	0x1200,		BlueAcBANDEND= AmberAirfieldBAND,
		RedFakeAcBANDNum	,//		=	0x1400,
		RedAAASiteBANDNum	,//		=	0x1800,
		BlueAAASiteBANDNum	,//		=	0x1C00,
		RedAAAHiddenBANDNum	,//	=	0x1E00,
  		AmberCivilianBANDNum,//		=	0x2000,
		AmberSupplyBANDNum	,//		=	0x2200,
		RedRepairBANDNum	,//		=	0x2400,
		AmberBridgeBANDNum	,//		=	0x2600,
		AmberMYardBANDNum	,//		=	0x2800,
		AmberBattleNodeBANDNum ,//		=	0x2880,
		RedTrainBANDNum		,//	=	0x2B00,
		RedTruckBANDNum		,//	=	0x2C00,
		RedTruckParkBANDNum	,//	=	0x2E00,
		RedTroopBANDNum		,//	=	0x2F00,
		BlueTroopBANDNum	,//		=	0x3000,
		RedArmourBANDNum	,//		=	0x3080,
		BlueArmourBANDNum	,//		=	0x3100,
		RedArtilleryBANDNum	,//	=	0x3180,
		BlueArtilleryBANDNum,//		=	0x3200,
		RedCombatVehicleBANDNum,// 	=	0x3280,
		BlueCombatVehicleBANDNum,//	=	0x3300,
		EventBANDNum			,//	=	0x3380,
		GreenVetoedBANDNum		,//	=	0x3400,
		GreenMobileBANDNum		,//	=	0x3480,
	  	GreenMiscBANDNum		,//	=	0x3500,
		RedHQBANDNum			,//	=	0x3580,
		BlueHQBANDNum			,//	=	0x3600,
		RedBoatBANDNum			,//	=	0x3680,
		BlueBoatBANDNum			,//=	0x3700,
		GreenBoatBANDNum		,//	=	0x3780,
		RedStaticAcBANDNum		,//	=	0x3800,
		BlueStaticACBANDNum		,//=	0x3880,
//THESE ARE OLD BANDS I AM KEEPING FOR THE MOMENT SO SYSTEM WILL COMPILE
		RedMilitaryBANDNum		 ,//	=	0x3900,
		BlueMilitaryBANDNum		,//=	0x3980,
		RedAirfieldBANDNum		,//	=	0x3A00,
		BlueAirfieldBANDNum		,//=	0x3A80,
		RedPortBANDNum			,//	=	0x3B00,
		BLuePortBANDNum			,//=	0x3B80,
		RedCCCBANDNum			,//	=	0x3C00,
		BlueCCCBANDNum			,//	=	0x3C80,
		RedGICBANDNum			,//	=	0x3D00,
		BlueGICBANDNum			,//	=	0x3D80,
		RedSAMBANDNum			,//	=	0x3F00,
		BlueSAMBANDNum			,//	=	0x3F80,
//END OF TEMP BANDS
		MaxBANDNum,
		IllegalBANDNum			//	=	0x3fff,



//	PilotedAcBANDNum,
  //					WayPointBANDNum,
	//				RedGroundMobileBANDNum,
	  //				BlueGroundMobileBANDNum,
		//			MissileBANDNum,
		  //			RedAcBANDNum,
			//		BlueAcBANDNum,
			  //		RedCivilianBANDNum,
				//	BlueCivilianBANDNum,
//					GreenCivilianBANDNum,
  //					RedVetoedBANDNum,
	//				BlueVetoedBANDNum,
	  //				LandscapeBANDNum,
		//			RedMilitaryBANDNum,
		  //			BlueMilitaryBANDNum,
			//		RedAirfieldBANDNum,
			  //		BlueAirfieldBANDNum,
				//	RedPortBANDNum,
//					BLuePortBANDNum,
  //					RedCCCBANDNum,
	//				BlueCCCBANDNum,
	  //				RedGICBANDNum,
		//			BlueGICBANDNum,
		  //			RedAAASiteBANDNum,
			//		BlueAAASiteBANDNum,
			  //		RedSAMBANDNum,
//					BlueSAMBANDNum,
  //                  MaxBANDNum
                    };

enum	iconbitmaps{
						wpbmp,
						hi_wpbmp,
						Eventbmp,
						aattackbmp,
						gattackbmp,
						hi_Eventbmp,
						hi_aatckbmp,
						hi_gatckbmp,
						a_afbmp,
						a_hqbmp,
						a_splybmp,
						a_bridgebmp,
						c_afbmp,
						c_hqbmp,
						c_splybmp,
						hospitalbmp,
						singlebmp,
						a_arcftbmp,
						a_tankbmp,
						c_arcftbmp,
						c_tankbmp,
						a_aaabmp,
						c_aaabmp,
						a_ballbmp,
						c_ballbmp,
						a_battbmp,
						c_battbmp,
						a_truckbmp,
						c_truckbmp,
						a_trainbmp,
						c_trainbmp,
						a_troopbmp,
						c_troopbmp,
						groupbmp,
						settlebmp

					};

const int	ZOOMMAXMAP = 700, ZOOMMAXABS = 4000;
 enum 	{	SETHOMEBASEEVENTVAR = 1,SETHOMEBASE = 2,
				SETMAINOBJECTIVE, SETSUBOBJECTIVE, SETWP1, SETWP2,SETWP3,SETWAYPOINT,SETENEMYHOMEBASE,
				SETTARGETEVENTVAR, SETTAKEOFFPOINT, SETSQUADHOMEBASE,
				SETAIRFIELD, SETSUPERGROUP};
const int MAXACINPLAYERSQUAD = 12;
const int	SINGLEVISIBLE = 1, EVENTVISIBLE = 2;
const	int	TRUCKSVISIBLE = 1, TRAINSVISIBLE = 2,TROOPSVISIBLE = 4, ALLVISIBLE = 7;
const int	METRIC = 0,IMPERIAL = 1, MIXED = 2;
const int	NOTDRAGGING = 0,DRAGGINGLEFT = 1,DRAGGINGRIGHT = 2;
const int	NOTEDITTING = 0, EDITMOVETO = 1, EDITCOPY = 2;
const int 	AFLAKSHAPEGROUP = 0,CPFLAKSHAPEGROUP = 1,
			ABATTSHAPEGROUP = 2,CPBATTSHAPEGROUP = 3,
			TRUCKSHAPEGROUP = 4,TROOPSHAPEGROUP = 5,TRAINSHAPEGROUP = 6,
			GROUPSHAPEGROUP = 7,SINGLESHAPEGROUP = 8,
			BTANKGROUP = 9, GTANKGROUP = 10,
			ABALLGROUP = 11, GBALLGROUP = 12,OTHERGROUPS = 13;
enum	{ mrOK = 1, mr_Cancel,
			mrRoute = 100, mrDelete = 101, mrMoveTo= 102,
			mrInsetWpBefore = 103,mrInsetWpAfter = 104,
			mrInsetEvBefore = 105,mrInsetEvAfter = 106,mrAddBf = 107,mrNewEvent = 108,mrEventMore = 109,
			mrCampaignText = 110, mrMissionText = 111, mrCampaignParameters = 112, mrMissionConditions = 113,
			mrMissionObjectives = 114
			};
enum	{ NEUTRAL = 0,  CENTRALPOWERS = 1, ALLIES = 2};

const	int	ICONW = 18;
const	int	ZOOMINITIAL = 200;
const int	MAXMISSIONSPERCAMPAIGN = 40;
enum	Transient	{T_NONE,T_WAYPOINT,T_AIRCRAFT,T_TANK,T_TRUCK,T_TRAIN,T_BATTERY,T_AAA,
						T_BALLOON,T_TROOP,T_SETTLEMENT, T_GROUPPOPULATE,T_SINGLEPOPULATE,T_EVENT
					};
#ifdef INTABLE
	INTABLE(Transient);
#endif


//const int MAXEVENTS = 50;
//const int MAXEVENTSPERWP = 16;
//const int MAXEVENTVAR = 50;

enum	FormPosnType {POSN_OPPOSITE,POSN_CENTER,POSN_USER};
enum	FormId		{AcItemFormId,WayPointFormId,EventWayPointFormId,EventFormId,ChooseBfFormId};

struct	FormPosnInfo
{
	FormPosnType	type;
	int				x;
	int				y;
};

//enum	CtrlVar {SYM_INLINEABLE,SYM_BFLOADABLE};

//struct EventVar;
//{
//	int index;
//    int	value;
//};
///struct EventBf;
///{
/////	EventBf*	nextevent;
/////	EventBf*	nextbf;
///	EventVar	eventvar[MAXEVENTVAR];
///    char		title[TITLE_LEN];
///    char		name[TITLE_LEN];
///    char		description[DESCRIPT_LEN];
///	CtrlVar		ctrlvar;
///	int			family;
///	int			file;
///    int			index;
///};
///struct	EventInfo;
///{
///	EventInfo*	next;
///	EventInfo*	prev;
///    int			file[MAXEVENTSPERWP];
///    int			index[MAXEVENTSPERWP];
///    EventVar	eventvar[MAXEVENTVAR];
///    int			lastvar;
///    int			endvar;
///    int			active;
///    int			timer;
///
///};

struct	StaticBand
	{
		bool	    	visible;
		UniqueIDBand	startband;
		UniqueIDBand 	endband;
	};

//	#include	"mecamp.h"

const int MAXLOADEDBFIELDS = 30  ;
const int MAXLOADEDSUPERGROUPS = 30;
const int UID_LENGTH = 25;
const int FNAME_LENGTH = 13;
const	int	TITLE_LENGTH	=	60;
const	int	DESCRIPTION_LENGTH = 300;

struct	LoadedBfDesc	//loadedbfs[]
{
	char	fname[FNAME_LENGTH];
	char    name[TITLE_LENGTH];
	char    newstext[DESCRIPTION_LENGTH];
	int		family;
	int 	fnum;
	bool	viewable;
	bool	movable;
	bool	deletable;
	bool	newlynamed;
	bool	changed;

};
struct	SuperGroupDesc
{
	UniqueID	uid;
	bool	viewable;
	bool	movable;
	bool	deletable;
	bool	newlynamed;
	bool	changed;

};
//struct	CampaignMissData
//{
//	SWord	    era;
//	SWord	    PlayerAcType;
//	UniqueID    PlayerHomeBase;
//	UniqueID    EnemyHomeBase;
//
//	SWord	    region;
//	SWord	    PlayerNationality;
//
//};
//
//struct	MissionData:CampaignMissData
//{
//   UniqueID	MainObjective;
//   UniqueID	SubObjective;
//   UniqueID	WP1,WP2,WP3;
//	SLong	missiondate;
//	SLong	timeofday;
//	SWord	numofsquadronac;
//	SWord	numofflightac;
//	SWord	formationtypeindex;
//	SWord	weathernum;											//RDH 02Oct96
//	SWord	windspeed;
//	UWord  winddirection;
//};
//
//
//struct	MissionType:MissionData
//{
//	char    name[TITLE_LENGTH];
//	char    newstext[DESCRIPTION_LENGTH];
//	char    missiontext[DESCRIPTION_LENGTH];
//	char	title[TITLE_LENGTH];
//void	Save(FILE* f);
//};
//
//
//struct	CampaignType:MeCampaignTexts
//{
//	char		name[TITLE_LENGTH];
//	MissionType	mission[MAXMISSIONSPERCAMPAIGN];
//	UniqueID    PlayerAcuid;
//	SWord		nextregion,nextera,nextnat;
//	SLong		nextdate;
//	struct	FileList
//	{
//		enum	{maxfiles=253,charsperfile=16};
//		char	data[maxfiles][charsperfile];
//		void	Clear();
//		char*	operator[](int i){return data[i];}
//	}	filelist;
//
//};
//---------------------------------------------------------------------------
#define	BARCON(D,backcont)   \
	D##_Scroll(D##_PUCK,D##_BACK,backcont,\
			D##_PL,D##_L,D##_ZL,D##_ML,\
			D##_PG,D##_G,D##_ZG,D##_MG,\
			D##_TL,D##_TG,D##_BarMoved,this)
#define	BARINST(D)											\
	void	D##_BarMoved2(float scale,int pos);					\
	static void	D##_BarMoved(TForm* f,float scale,int pos)  \
	{((currentclass*)f)-> D##_BarMoved2(scale,pos);}          \
	RScrollBar	D##_Scroll

#define BARMOVED(D)	\
	D##_BarMoved2(float scale,int D##_pos)


typedef	TPanel *TPanelPtr;
typedef	AnsiString (*Tcornertext)(int);
typedef	int	(*TGetExt)(TControl*);
typedef	int (*TSetExt)(TControl*,int);
typedef void	(*DHH_BarMoved)(TForm* f,float scale,int pos);

class	RScrollBar
{
	TForm* 			parent;
	DHH_BarMoved	parentmoved;
	typedef TLabel	*TLabelPtr;
public:
	struct P4{ TPanelPtr p,s,z,m;
				P4(TPanelPtr pp,TPanelPtr ss,TPanelPtr zz, TPanelPtr mm)
					{p=pp;s=ss;z=zz;m=mm;}
					};

	RScrollBar(
		TPanelPtr	puck,TPanelPtr back,TControl* vback,
		TPanelPtr pgless,TPanelPtr stepless,TPanelPtr zoomless,TPanelPtr setmin,
		TPanelPtr pgmore,TPanelPtr stepmore,TPanelPtr zoommore,TPanelPtr setmax,
		TLabelPtr txtless,TLabelPtr txtmore,DHH_BarMoved,TForm*);

	SetScroll(int scurr,double spix2scale=0.0,int smax=-1,int smin=0);
	int GetPos()			{return (int)curr;}
	double	GetScale()		{return pix2scale;}
	int		GetCoverage()	{return page;}

private:
	TPanelPtr
		puck,back,
		pgless,stepless,zoomless,setmin,
		pgmore,stepmore,zoommore,setmax;
	TControl* vback;

	TLabelPtr
		txtless,txtmore;
 //	(TPanel::int)& widfield;
	int	min;
	int	max;
	int	page;int pagesize;
	double curr;
	double pix2scale,bar2scale;
	Tcornertext	cornertext;
	TGetExt		GetExt;
	TSetExt		SetExt;
	void	SetZoomCaption();
	static int GetW(TControl* p)	{return p->Width;}
	static int GetH(TControl* p)	{return p->Height;}
	static int	SetW(TControl* p,int w)	{return p->Width=w;}
	static int	SetH(TControl* p,int h) {return p->Height=h;}
	static AnsiString vtext(int);
	static AnsiString htext(int);
 public:
	int downpos;
	void	OnPress(TObject*,int start);
	void	OnMove(int delta);
	void	OnRelease(TObject*);
	void	OnResize();

};

struct	JimBits
{
	    typedef	UByte	JimStorage;
    	class	JimBit
	    {
		public:
    		JimStorage& storage;
    	    int index;
			JimBit(JimStorage& store,int ind):
    		storage(store)			{index=ind;}
	        operator bool() const
        	{return bool(storage&(1<<index));}
    	    bool operator = (bool v) const
	        {bool rv=*this;v=(v!=rv);storage^=UByte(v)<<index;return rv;}
        	JimBit(JimBit& src):
    	    storage(src.storage)	{index=src.index;}
	    };
    	JimStorage storage;
    public:
		JimBits(UByte v=0)	{storage=v;}
		JimBit	operator[](int ind)
        {return	JimBit(storage,ind);}
};
struct LevelDrop;
struct PtPair;
//---------------------------------------------------------------------------
class TMissionEditor : public TForm
{
	friend class MapLoad;
	typedef	TForm			parentclass;
	typedef	TMissionEditor  currentclass;
__published:	// IDE-managed Components
	TPanel *BACKPANEL;
	TPanel *Panel4;
	TPanel *Panel6;
	TPanel *HS_VBACK;
	TPanel *HS_G;
	TPanel *HS_L;
	TPanel *HS_BACK;
	TPanel *HS_PG;
	TLabel *HS_TG;
	TPanel *HS_MG;
	TPanel *HS_ZG;
	TPanel *HS_PUCK;
	TPanel *HS_ZL;
	TPanel *HS_PL;
	TLabel *HS_TL;
	TPanel *HS_ML;
	TPanel *SpeedBar;
	TSpeedButton *SB_Bfields;
	TSpeedButton *SB_SuperGroups;
	TSpeedButton *SB_Saveall;
	TPanel *ZoomPanel;
	TSpeedButton *ZoomOutBtn;
	TSpeedButton *ZoomInBtn;
	TLabel *ZoomLabel;
	TSpeedButton *SpeedButton25;
	TSpeedButton *SpeedButton26;
	TSpeedButton *SpeedButton27;
	TSpeedButton *SpeedButton28;
	TSpeedButton *SpeedButton29;
	TSpeedButton *SpeedButton30;
	TSpeedButton *SpeedButton31;
	TSpeedButton *SpeedButton32;
	TSpeedButton *SpeedButton33;
	TSpeedButton *SpeedButton34;
	TPanel *TransientPanel;
	TSpeedButton *SB_CP_Aircraft;
	TSpeedButton *SB_CP_Truck;
	TSpeedButton *SB_CP_Train;
	TSpeedButton *SB_CP_Tank;
	TSpeedButton *SB_CP_Battery;
	TSpeedButton *SB_CP_AAA;
	TSpeedButton *SB_CP_Balloon;
	TSpeedButton *SB_CP_Troops;
	TSpeedButton *SB_A_Troops;
	TSpeedButton *SB_A_Balloon;
	TSpeedButton *SB_A_Battery;
	TSpeedButton *SB_A_AAA;
	TSpeedButton *SB_A_Tank;
	TSpeedButton *SB_A_Train;
	TSpeedButton *SB_A_Truck;
	TSpeedButton *SB_A_Aircraft;
	TSpeedButton *SB_Arrow;
	TSpeedButton *SB_Route;
	TSpeedButton *SB_Event;
	TSpeedButton *SB_Single;
	TSpeedButton *SB_Group;
	TPanel *Panel5;
	TPanel *FilterSpeedBar;
	TSpeedButton *FileOpenBtn;
	TSpeedButton *FileSaveBtn;
	TPanel *Panel1;
	TSpeedButton *SB_Af_Filter;
	TSpeedButton *SB_BridgeFilter;
	TSpeedButton *SB_HQ_Filter;
	TSpeedButton *SB_SupplyFilter;
	TSpeedButton *SB_Art_Filter;
	TSpeedButton *SB_Truck_Filter;
	TSpeedButton *SB_Train_Filter;
	TSpeedButton *SB_Tank_Filter;
	TSpeedButton *SB_AAA_Filter;
	TSpeedButton *SB_Troops_Filter;
	TSpeedButton *SB_Event_Filter;
	TSpeedButton *SB_Single_Filter;
	TSpeedButton *SB_Group_Filter;
	TSpeedButton *SB_Settlement_Filter;
	TSpeedButton *SB_Hospital_Filter;
	TSpeedButton *SB_Bl_Filter;
	TSpeedButton *SB_Ac_Filter;
	TSpeedButton *SB_All;
	TSpeedButton *SB_Route_Filter;
	TSpeedButton *SB_SuperGroupFilter;
	TPanel *TransPanelSwap;
	TGroupBox *topgrp;
	TSpeedButton *SB_Arrow_T;
	TSpeedButton *SB_Route_T;
	TSpeedButton *SB_Event_T;
	TSpeedButton *SB_Single_T;
	TSpeedButton *SB_Group_T;
	TSpeedButton *SideG;
	TSpeedButton *SB_CP_Battery_T;
	TSpeedButton *SB_CP_Tank_T;
	TSpeedButton *SB_CP_Balloon_T;
	TSpeedButton *SB_CP_AAA_T;
	TSpeedButton *SB_CP_Aircraft_T;
	TSpeedButton *SB_CP_Truck_T;
	TSpeedButton *SB_CP_Train_T;
	TSpeedButton *SB_CP_Troops_T;
	TSpeedButton *SB_A_Troops_T;
	TSpeedButton *SB_A_Train_T;
	TSpeedButton *SB_A_Truck_T;
	TSpeedButton *SB_A_Aircraft_T;
	TSpeedButton *SB_A_Tank_T;
	TSpeedButton *SB_A_Balloon_T;
	TSpeedButton *SB_A_AAA_T;
	TSpeedButton *SB_A_Battery_T;
	TSpeedButton *SideA;
	TPanel *Panel2;
	TPanel *Panel3;
	TSpeedButton *SpeedButton22;
	TSpeedButton *SpeedButton23;
	TSpeedButton *SpeedButton24;
	TSpeedButton *SpeedButton35;
	TSpeedButton *SpeedButton36;
	TSpeedButton *SpeedButton37;
	TSpeedButton *SpeedButton38;
	TSpeedButton *SpeedButton39;
	TSpeedButton *SpeedButton40;
	TSpeedButton *SpeedButton41;
	TSpeedButton *SpeedButton42;
	TSpeedButton *SpeedButton43;
	TPanel *ZoomLabel2;
	TScrollBox *ScrollBox;
	TPaintBox *PB01;
	TPaintBox *PB11;
	TPaintBox *PB21;
	TPaintBox *PB31;
	TPaintBox *PB02;
	TPaintBox *PB12;
	TPaintBox *PB22;
	TPaintBox *PB32;
	TPaintBox *PB03;
	TPaintBox *PB13;
	TPaintBox *PB23;
	TPaintBox *PB33;
	TPaintBox *PB41;
	TPaintBox *PB42;
	TPaintBox *PB43;
	TPaintBox *PB04;
	TPaintBox *PB14;
	TPaintBox *PB24;
	TPaintBox *PB34;
	TPaintBox *PB44;
	TPaintBox *PB54;
	TPaintBox *PB51;
	TPaintBox *PB52;
	TPaintBox *PB53;
	TPaintBox *PB55;
	TPaintBox *PB25;
	TPaintBox *PB05;
	TPaintBox *PB15;
	TPaintBox *PB35;
	TPaintBox *PB45;
	TPaintBox *PB00;
	TPaintBox *PB10;
	TPaintBox *PB20;
	TPaintBox *PB30;
	TPaintBox *PB40;
	TPaintBox *PB50;
	TStatusBar *StatusBar;
	TPanel *VS_VBACK;
	TPanel *VS_G;
	TPanel *VS_L;
	TPanel *VS_BACK;
	TPanel *VS_PL;
	TLabel *VS_TL;
	TPanel *VS_ML;
	TPanel *VS_PUCK;
	TPanel *VS_ZL;
	TPanel *VS_PG;
	TLabel *VS_TG;
	TPanel *VS_ZG;
	TPanel *VS_MG;
	TMainMenu *MainMenu;
	TMenuItem *FileMenu;
	TMenuItem *NewMissionMenu;
	TMenuItem *FileOpenMission;
	TMenuItem *FileSaveMission;
	TMenuItem *N3;
	TMenuItem *FileExit;
	TMenuItem *EditMenu;
	TMenuItem *Move;
	TMenuItem *Copy;
	TMenuItem *ViewMenu;
	TMenuItem *ViewZoomIn;
	TMenuItem *ViewZoomOut;
	TMenuItem *ViewZoomReset;
	TMenuItem *ZoomInMapMax;
	TMenuItem *ZoomInMax;
	TMenuItem *N7;
	TMenuItem *ViewToolBar;
	TMenuItem *ToolBarFilter;
	TMenuItem *InfoPanel1;
	TMenuItem *N4;
	TMenuItem *ItemCount;
	TMenuItem *CampaignMenu;
	TMenuItem *CampaignInit;
	TMenuItem *CampaignEdit;
	TMenuItem *CampaignText;
	TMenuItem *N8;
	TMenuItem *CampaignPilots;
	TMenuItem *MissionMenu;
	TMenuItem *MissionInit;
	TMenuItem *MissionText;
	TMenuItem *MissionConditions;
	TMenuItem *MissionObjectives;
	TMenuItem *Configure1;
	TMenuItem *ConfigureUnits;
	TMenuItem *metric;
	TMenuItem *imperial;
	TMenuItem *mixed;
	TMenuItem *ConfigureVehicles;
	TMenuItem *Mobile;
	TMenuItem *Stationary;
	TMenuItem *Date;
	TMenuItem *ddmmyy;
	TMenuItem *mmddyy;
	TMenuItem *currshape;
	TMenuItem *N2;
	TMenuItem *EditMissionSrc1;
	TMenuItem *RunMenu;
	TMenuItem *RunMission;
	TMenuItem *MenuHelp;
	TMenuItem *HelpTopics;
	TMenuItem *N1;
	TMenuItem *About;
	TMenuItem *Zoom2;
	TMenuItem *Zoom1;
	TMenuItem *Z2;
	TMenuItem *Z3;
	TMenuItem *N4001;
	TMenuItem *N5001;
	TMenuItem *N6001;
	TMenuItem *N71;
	TMenuItem *N81;
	TMenuItem *N91;
	TMenuItem *N101;
	TTimer *MapTimer;
	TPopupMenu *MapPopupMenu;
	TMenuItem *SMOpen;
	TMenuItem *SMDelete;
	TMenuItem *SMMoveTo;
	TMenuItem *SMCopy;
	TMenuItem *SMZoomIn;
	TMenuItem *SMZoomOut;
	TMenuItem *SMZoomReset;
	TMenuItem *SMZoomInMapMax;
	TMenuItem *SMZoomInMax;
	TMenuItem *Spacer;
	TMenuItem *SMCenter;
	TMenuItem *SMScale;
	TTimer *RefreshTimer;
	TTimer *GenIdleTimer;


	TSaveDialog *SavePilots;
	TOpenDialog *OpenPilots;
	TSpeedButton *Find;
        void __fastcall About3Click(TObject *Sender);
//	void __fastcall CampaignTextClick(TObject *Sender);
//	void __fastcall TankBtnClick(TObject *Sender);


	void __fastcall CampaignParametersClick(TObject *Sender);
	void __fastcall CampaignEditClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

//	void __fastcall FileSaveAsCampaignClick(TObject *Sender);
	void __fastcall NewMissionMenuClick(TObject *Sender);
	void __fastcall ImageMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift, int X,
	int Y);
	void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall ViewZoomInClick(TObject *Sender);
	void __fastcall ViewZoomOutClick(TObject *Sender);

	void __fastcall MissionTextClick(TObject *Sender);
	void __fastcall SB_A_AircraftClick(TObject *Sender);
	void __fastcall SB_A_TankClick(TObject *Sender);
	void __fastcall CampaignClick(TObject *Sender);

	void __fastcall MissionBaseClick(TObject *Sender);
	void __fastcall MissionConditionsClick(TObject *Sender);
	void __fastcall CampaignPilotsClick(TObject *Sender);
	void __fastcall MapTimerTimer(TObject *Sender);
	void __fastcall SB_A_BalloonClick(TObject *Sender);
	void __fastcall SB_CP_AircraftClick(TObject *Sender);
	void __fastcall SB_CP_TankClick(TObject *Sender);
	void __fastcall ViewToolBarClick(TObject *Sender);
	void __fastcall MoveClick(TObject *Sender);

	void __fastcall SB_CP_BalloonClick(TObject *Sender);
	void __fastcall SB_ArrowClick(TObject *Sender);
	void __fastcall SB_RouteClick(TObject *Sender);
//	void __fastcall PaintBoxPaint(TObject *Sender);
	void __fastcall SB_Settlement_FilterClick(TObject *Sender);
	void __fastcall SB_Af_FilterClick(TObject *Sender);
//	void __fastcall ViewZoomResetClick(TObject *Sender);
//	void __fastcall SMZoomInClick(TObject *Sender);
	void __fastcall MapPopupMenuPopup(TObject *Sender);
	void __fastcall SMCenterClick(TObject *Sender);
//	void __fastcall SMZoomOutClick(TObject *Sender);
	void __fastcall SB_Hospital_FilterClick(TObject *Sender);
	void __fastcall SB_SupplyFilterClick(TObject *Sender);
	void __fastcall SB_HQ_FilterClick(TObject *Sender);
	void __fastcall SB_BridgeFilterClick(TObject *Sender);
	void __fastcall SB_AAA_FilterClick(TObject *Sender);
	void __fastcall SB_Art_FilterClick(TObject *Sender);
	void __fastcall SB_Event_FilterClick(TObject *Sender);
	void __fastcall SB_Single_FilterClick(TObject *Sender);
	void __fastcall SB_Bl_FilterClick(TObject *Sender);
	void __fastcall SB_Ac_FilterClick(TObject *Sender);
	void __fastcall SB_A_AAAClick(TObject *Sender);
	void __fastcall SB_CP_AAAClick(TObject *Sender);
	void __fastcall SB_A_BatteryClick(TObject *Sender);
	void __fastcall SB_A_TruckClick(TObject *Sender);
	void __fastcall SB_CP_BatteryClick(TObject *Sender);
	void __fastcall SB_CP_TruckClick(TObject *Sender);
	void __fastcall SB_A_TrainClick(TObject *Sender);
	void __fastcall SB_CP_TrainClick(TObject *Sender);
	void __fastcall SB_A_TroopsClick(TObject *Sender);
	void __fastcall SB_CP_TroopsClick(TObject *Sender);
	void __fastcall SB_EventClick(TObject *Sender);
	void __fastcall SB_SingleClick(TObject *Sender);
	void __fastcall SB_GroupClick(TObject *Sender);
	void __fastcall CampaignPlayerClick(TObject *Sender);


	void __fastcall MissionObjectivesClick(TObject *Sender);
	void __fastcall SB_AllClick(TObject *Sender);
	void __fastcall ToolBarFilterClick(TObject *Sender);


	void __fastcall FileSavePilotsClick(TObject *Sender);
	void __fastcall FileLoadPilotsClick(TObject *Sender);
	void __fastcall SB_Truck_FilterClick(TObject *Sender);
	void __fastcall SB_Train_FilterClick(TObject *Sender);


	void __fastcall SB_Tank_FilterClick(TObject *Sender);
	void __fastcall SB_Route_FilterClick(TObject *Sender);

	void __fastcall ReservePoolClick(TObject *Sender);
//	void __fastcall NewCampaignClick(TObject *Sender);
//	void __fastcall NewMissionGroupClick(TObject *Sender);
	void __fastcall CampaignInitClick(TObject *Sender);
	void __fastcall MissionInitClick(TObject *Sender);

//	void __fastcall OpenCampaignClick(TObject *Sender);

//	void __fastcall OpenMissionGroup1Click(TObject *Sender);
	void __fastcall metricClick(TObject *Sender);
	void __fastcall imperialClick(TObject *Sender);

	void __fastcall MobileClick(TObject *Sender);
	void __fastcall StationaryClick(TObject *Sender);


	void __fastcall FileSaveMissionClick(TObject *Sender);
	void __fastcall ddmmyyClick(TObject *Sender);
	void __fastcall mmddyyClick(TObject *Sender);
	void __fastcall SMOpenClick(TObject *Sender);
	void __fastcall SMDeleteClick(TObject *Sender);
	void __fastcall SMScaleClick(TObject *Sender);
	void __fastcall SMMoveToClick(TObject *Sender);
	void __fastcall FileMenuClick(TObject *Sender);
	void __fastcall SMCopyClick(TObject *Sender);
	void __fastcall CopyClick(TObject *Sender);
	void __fastcall SB_Troops_FilterClick(TObject *Sender);
	void __fastcall currshapeClick(TObject *Sender);
	void __fastcall SB_Group_FilterClick(TObject *Sender);
	void __fastcall FileOpenMissionClick(TObject *Sender);
	void __fastcall SB_WorldTemplateClick(TObject *Sender);
	void __fastcall HelpTopicsClick(TObject *Sender);
//	void __fastcall SaveCampaignClick(TObject *Sender);
	void __fastcall EditMissionSrc1Click(TObject *Sender);
	void __fastcall RunMissionClick(TObject *Sender);
	void __fastcall mixedClick(TObject *Sender);
	void __fastcall AboutClick(TObject *Sender);
	void __fastcall FileExitClick(TObject *Sender);
//	void __fastcall RunCampaignClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);
	void __fastcall ItemCountClick(TObject *Sender);
	void __fastcall SecretCancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SMZoomInMapMaxClick(TObject *Sender);
	void __fastcall SMZoomInMaxClick(TObject *Sender);
	void __fastcall SMZoomInClick(TObject *Sender);
	void __fastcall ViewZoomResetClick(TObject *Sender);
	void __fastcall SMZoomOutClick(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall ZoomInMaxClick(TObject *Sender);
	void __fastcall ZoomInMapMaxClick(TObject *Sender);
	void __fastcall Zoom2Click(TObject *Sender);
	void __fastcall FilterSpeedBarMouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y);
	void __fastcall SideGClick(TObject *Sender);
	void __fastcall InfoPanel1Click(TObject *Sender);
	void __fastcall RefreshTimerTimer(TObject *Sender);
//	void __fastcall ScrollBoxResize(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall PGPaint(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SB_BfieldsClick(TObject *Sender);
	void __fastcall SB_SuperGroupsClick(TObject *Sender);

	void __fastcall SB_SaveallClick(TObject *Sender);
	void __fastcall SB_SuperGroupFilterClick(TObject *Sender);
	void __fastcall ScrollMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall ScrollMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall ScrollMouseMove(TObject *Sender, TShiftState Shift, int X,
	int Y);
    void __fastcall IdleTime(TObject* Sender, bool &Done);
	void __fastcall ScrollResize(TObject *Sender);
    bool __fastcall ScrollIdle();


	void __fastcall ScrollMouseDown2(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
//	void __fastcall HS_TLClick(TObject *Sender);
	void __fastcall GenIdleTimerTimer(TObject *Sender);
	void __fastcall PBMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall PBMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall PBMOuseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall FindClick(TObject *Sender);
private:	// User declarations
	int	ZoomWorldIconSize();
	void   MouseUpFindStatic(int X,int Y);
	void __fastcall OnHint(TObject* Sender);
///	void __fastcall DrawTransientIcon(TransItem*	currtransitem);
	void	__fastcall DrawWpIcon(UniqueID	wpUID,SWord currwpnum);
	void __fastcall ResetSpeedButtons();
	void __fastcall SetScrollBars();
	Bool __fastcall OverStatic( int X, int Y,UniqueID&  currUID);
	void __fastcall DrawLoBorder(int X,int Y);
	void __fastcall DrawHiBorder(int X,int Y);
	void __fastcall DrawSettlement(UniqueID uid,SLong x, SLong y);
	void __fastcall SetZoomLabel();
//	void __fastcall InitTransient(int X, int Y);
	void __fastcall NewLoadedBf(AnsiString name);
	void __fastcall InitMission();

	void __fastcall DrawScale();
	void __fastcall SetSpeedButtonTags();
	void __fastcall InitCampaign();
	void __fastcall DrawTarget(UniqueID currUID,int X, int Y);
	bool  __fastcall TodaysTarget(UniqueID currUID);
   void __fastcall NewSuperGroup(UniqueID uid);
   void __fastcall SB_AllDown();

protected:
//  void __fastcall WMQueryNewPalette(TMessage* Message);
//BEGIN_MESSAGE_MAP
//  MESSAGE_HANDLER(WM_QUERYNEWPALETTE, TMessage*, WMQueryNewPalette)
//END_MESSAGE_MAP(TControl)
	BARINST(HS);
	BARINST(VS);
void	BarMoved(int newx,int newy,double newscale);
	typedef	Graphics::TBitmap*	TBitmapPtr;


    
    TBitmapPtr		mtbackdrop;
	LevelDrop		*leveldrop;

    int		xloadreq,yloadreq,levelreq,bloadreq,hloadreq;
    bool    loadquick;
    Bool	loadrequested;
	struct	MapBlock
    {
    	TPaintBox* box;
    	int	WX,WZ;
        bool dirty:1,scaled:1;
		char sourcescale;
        char gridxblk;
        char gridyblk;
        TBitmapPtr	backdrop;
        TPaintBox*	operator ->()	{return box;}
  bool      Draw(Controls::TCustomImageList*,int x,int y,iconbitmaps index);
        int	CopyMode(int i) {return box->Canvas->CopyMode=i;}
        int	CopyMode()		{return box->Canvas->CopyMode;}
        void	TextOut(int x,int y,AnsiString s);
        void	Pen(TPenStyle style,Graphics::TColor col,int wid);
        void	Pen(Graphics::TColor col);
        void	Font(TFontStyles style,Graphics::TColor col,int wid);
        void	Font(Graphics::TColor col);
        void	MoveTo(int x,int y);
        void	LineTo(int x,int y);    	//ignores lines that are being dragged
        void	DragLineTo(int x,int y);	//draws dragged version of line
        void	Rectangle(int x,int y,int x2,int y2);
    };
    bool	CouldDoBetter(MapBlock& map);
    bool	GetBlock(int level,int xreq,int yreq,int* blkx,int* blky);
    void	StartBlockLoad(int level,int x,int y,bool fast);
    bool	DoneLoadBlockReq();
    void __fastcall RescaleArt(MapBlock& block);
public:
    enum	GridConsts	{REALMAXPAINT=6,GRIDMAXPAINT=8,GRIDMAXSIZE=16};
    struct PaintRow
    {
    	MapBlock*	row[GRIDMAXSIZE];
        MapBlock& 	operator [](int ind)	{return row[ind][0];}
        MapBlock*&	operator +(int ind)		{return	row[ind];}
        PaintRow*	operator ()(int ind)	{return (PaintRow*)(row+ind);}
    };

private:
	MapBlock	RealPoints[REALMAXPAINT][REALMAXPAINT];
   	PaintRow PaintGrid[GRIDMAXSIZE];
    PaintRow *paintpos;
    float	 cmpixscale;
void	setdrawpos(MapBlock& paintpos,int paintx,int painty);
void	InitPaintGrid();
void    ExitPaintGrid();
bool	MapIdle();
MapBlock*	CurrCanvas;
void	PaintRefresh();
void	StartDragItem();
void	StartDragLine1(int xa,int ya,int xb,int yb,int wb,int hb);
void	StartDragLine2(int xa,int ya,int xb,int yb,int xc,int yc,int wb,int hb);
void	StartDragBox(int x,int y,int w,int h);
void	MoveDragPix(int X,int Y);
void	MoveDrag(int x,int y);
void	EndDrag();
enum 	DragOrds	{D_B1,D_B2,D_A,D_C,D_W};
void	TMissionEditor::GetDragLine(DragOrds d,int& X,int& Y);
void	DrawDrag(MapBlock& block);
void	PushScreenDrag(PtPair & a);
bool	PushDragIdle();

void	InvalidateLine(PtPair & a,PtPair& b);
void	InvalidateBox(PtPair & a,PtPair& b);



public:		// User declarations
// 	virtual HPALETTE __fastcall GetPalette(void);
	virtual bool __fastcall PaletteChanged(bool Foreground);
	  void __fastcall SuperGroupStatusBar(UniqueID uid);
bool	__fastcall SuperGroupViewable(UniqueID currUID);
 void __fastcall WipeBf(int index) ;
void __fastcall ReloadBf(int index);


	__fastcall TMissionEditor(TComponent* Owner);
    __fastcall ~TMissionEditor();

	void __fastcall ShowItemDialog(int X, int Y);
	TCustomImageList* MapImageList;
///	void __fastcall MakeDefaultRoute(TransItem* Item);
	void __fastcall MakeTransient(int X, int Y);
//	void __fastcall SetTransItem(TransItem*	transitem);
	void __fastcall SetTransItem(UniqueID	transitem);
	void __fastcall DrawStatics();
	void __fastcall SetupStatics(UniqueID currUID,UniqueID endband);
//	void __fastcall DeleteStaticItems();
	void __fastcall MoveTransient(int X, int Y);
	void __fastcall MoveWp(int X, int Y);
	void __fastcall DrawWp();
void __fastcall  FormCoords(int X,int Y,FormId form,int& formX,int& formY,int formW,int formH);
	void __fastcall CentreSetScrollBars(int X,int Y);
	void __fastcall FillComboBox(int min, int max, TComboBox* combobox,int index);
	void __fastcall PartFillComboBox(int min, int max, TComboBox* combobox, int index, int* ctrlarray);
#ifdef    BFENUM_Included
	void __fastcall PartFillComboBox(EnumListNames list, int max, TComboBox* combobox, int index, int* ctrlarray);
#endif
    int __fastcall FindOrginalIndex(int min, int max,int index,int* ctrlarray);

	void __fastcall SetFindingStaticMode(int method);
	int __fastcall GetBandorShapeText(UniqueID currUID);
#ifdef	SHAPENUM_INCLUDED
	void __fastcall DrawStaticIcon(UniqueID uid,SLong x, SLong y,ShapeNum	shape);
	UniqueID __fastcall InitStatic(int X, int Y, int Z,UniqueIDBand u,ShapeNum s,UniqueID uid);
//	UniqueID	__fastcall InitStatic(int X, int Y, int Z,UniqueIDBand u,ShapeNum s);
	UniqueID	__fastcall MakeDefaultRoute(int X,int Z);
	UniqueID __fastcall MakeDefaultAirRoute(int X,int Z);
	UniqueID __fastcall TopInitAc(int X, int Y, int Z,UniqueIDBand au,UniqueIDBand cu,ShapeNum as,ShapeNum cs);
	UniqueID __fastcall TopInitMobile(int X, int Z,UniqueIDBand au,UniqueIDBand cu,ShapeNum as,ShapeNum cs);
	UniqueID __fastcall InitMobile(int X, int Z,UniqueIDBand u,ShapeNum s,UniqueID route,UniqueID uid);
//	UniqueID	__fastcall InitMobile(int X, int Z,UniqueIDBand u,ShapeNum s,UniqueID route);
//	void	__fastcall TopInitStatic(int X,int Y,UniqueIDBand au,UniqueIDBand cu,ShapeNum as,ShapeNum cs);
	UniqueID __fastcall TopInitStatic(int X,int Y,int Z,UniqueIDBand au,UniqueIDBand cu,ShapeNum as,ShapeNum cs);
	UniqueID __fastcall InitAircraft(int X, int Y,int Z,UniqueIDBand u,ShapeNum s,UniqueID route, UniqueID uid);
//	UniqueID	__fastcall InitAircraft(int X, int Y,int Z,UniqueIDBand u,ShapeNum s,UniqueID route);
void __fastcall DrawMobileIcon(UniqueID uid,SLong x, SLong z,ShapeNum	shape);
#endif
	void __fastcall NewWorld();	//FileNum	file,int region);
	void __fastcall DeleteWorld();
	void __fastcall UnLockTargetWayPoint(UniqueID uid);


	void		__fastcall WorldPosition(int& X, int& Z);
	void		__fastcall ScreenPosition(int& mapx, int& mapy);
	void __fastcall SetMissionMode(bool missionmode);
	void __fastcall SetCaption(char* campaignname, char* missionname);
void __fastcall CheckHomeBase();
void __fastcall CheckHomeBase(int fnat,UniqueID& fhome,UniqueID& ehome,int region);
UniqueID __fastcall FindAirfield(SWord nationality,int region);
UniqueID __fastcall FindDefaultAirfield(SWord nationality);
void __fastcall MoveTransientNotWP(int X, int Y);
void __fastcall MoveToEdit(int X, int Y);
//void __fastcall CopyEdit(int X, int Y);
bool __fastcall CopyEdit(int X, int Y);
void __fastcall MainMenuMoveToEdit(int X,int Y);
void __fastcall MainMenuCopyEdit(int X,int Y);
int __fastcall ValidEdit(TEdit *editbox);
void __fastcall CopyWayPoints(UniqueID destobj,UniqueID srcobj);
void __fastcall ChangeTag(int index, int shape);
void __fastcall SetMobile(bool option);
void __fastcall FindWorldTemplateFiles(int region);
void __fastcall MakePlayerAc(bool option);
bool __fastcall PlayerAcPresent();
//bool __fastcall FileNameAvailable(int bfindex);
void __fastcall AcSpdButtonState();
 void __fastcall  SetMaxMobCnt();
void __fastcall MobileSpdButtonState();
void __fastcall ResetTargetWayPoints();
UniqueID FindNeighbour(UniqueID existing,UidBandNum band,int bestrange=200000);
int  __fastcall IncMobileCounters(UniqueIDBand  uidband,int cnt);
void  __fastcall DisableWPUsageifnecessary();
void  __fastcall IncWayPointandCheck();
int  __fastcall WPsusedbycurrobj();
int ConvertFileToEra(FileNum f);

void	AccumulateLoadedCount();
bool	CheckObjectives();
void	QuickDisassemble(char* line);
void	CentreOnWorld(int X,int Z);

void	NewCampaign(AnsiString	name,AnsiString title);
void	OpenCampaign(AnsiString	name);
//void	NewMissGrp(AnsiString	name,AnsiString title);
//void	OpenMissGrp(AnsiString	name);
void	NewMission(AnsiString	name,AnsiString title,int bfindex);
void	OpenMission(AnsiString	name,int bfindex);
bool 	SaveMission(int bfindex);
void	MouseMove(int X,int Y);
float	GetScaleFactor();
int	MulScaleFactor(int);
int	DivScaleFactor(int);
//   CampaignType	ActiveCampaign;
//   CampaignType	TempCampaign;
   SWord	currmission;
//   TransItem*	FirstTransItem;
//   TransItem*	CurrTransItem;
//   TransItem*	PlayerItem;
//   TransItem*	LastGGTransItem;
//   StaticItem*	FirstStaticItem;
//   RodsWayPoint*	CurrWp;
	UniqueID	currhomebase;
	UniqueID	currobj;
	UniqueID	currtemplateitem;
	UniqueID	currwp;
	UniqueID	playerobj;
	UniqueID	AcTarget;
//	Bool		lastconvoystatic;

///  EventBf*			CurrEventBf;
///   EventInfo*		CurrEventInfo;
//   EVentBf			*CurrEventBfAddr;
//    EventBf*    EventBfield;

   int	dragging,draggingdelay;

	int	findingstatic;
	int   FindingStaticVar;

	bool	FastClick;
	bool	canmodifymainworld;



//   Graphics::TBitmap *MapBitmap;
//   Graphics::TBitmap *MapBitmapTL;
//   Graphics::TBitmap *MapBitmapTR;
//   Graphics::TBitmap *MapBitmapBL;
//   Graphics::TBitmap *MapBitmapBR;
   private:
	   SWord	zoom,oldzoom;
   public:
   Transient	currtransient;
   SWord	currtransientshape;
   SWord	currtransientgroup;
   SWord	CurrNationality;
   SWord	Configure_Units;

   //The following variables will have to be treated differently before we can get them into the game
   // player globals
//   SWord	PlayerNationality;
//   SWord	PlayerRank;
//   SWord	PlayerAc;
   SWord	TempPlayerAcType;
//   UniqueID	PlayerHomeBase;
//   UniqueID	EnemyHomeBase;
   UniqueID	TmpEnemyHomeBase;

//   UniqueID	MainObjective;
//   UniqueID	SubObjective;
//   UniqueID	WP1,WP2,WP3;

   SWord	SquadSkill;
   SWord	SquadMorale;
	SWord	SquadChar;
   int     MissionTime;

   //temp vars
	UniqueID TmpPlayerHomeBase;
	SWord	 TmpPlayerNationality;
	SWord	TmpRegion;
	SWord	TmpEra;

   UniqueID	TmpMainObjective;
   UniqueID	TmpSubObjective;
   UniqueID	TmpWP1,TmpWP2,TmpWP3;
   UniqueID	TmpWayPoint;
  // Bool firstpaint;

   //
   SLong	MapOriginX;
   SLong	MapOriginY;
   //SLong	MapWidth;
   SLong	MapHeight;
private:
   SLong	scrnconvert;
public:
//   SLong	maptopx;
 //  SLong	maptopy;
   int		rightX,rightY;
   int		FC_x,FC_y;		//x,y of moved mouse while fast clicking.
//   bool		MissionMode;
//   bool		CampaignStarted;
//   bool		MissionStarted;
//   bool		MissionNew;
//   bool		MissionEdited;
//	int		MissionNumber;
	bool 	ShowWPvel;
//	int		CruiseSpeed;
	FileNum	WorldFile;
	UniqueID*	UIDLocation;
////	EnumStuff	IEnumStuff;
	bool	clickedonitem;
   int ScaleX;
   int ScaleY;
	bool	Initialising;
	int SwapGroup;
	int WithGroup;
	int SwapPilot;
	int WithPilot;
	bool InMenu;
	int Editting;
	bool	displayworldtemplateitems;
	int MobilesVisible;
	int LandscapeVisible;
   int BlueAcCnt;
   int RedAcCnt;
   int BlueAcMax;
   int RedAcMax;
   int RedGroundMobilesCnt;
   int RedTanksCnt;
   int RedGroundMobilesMax;
   int RedTanksMax;

   int BlueGroundMobilesCnt;
   int BlueTanksCnt;
   int BlueGroundMobilesMax;
   int BlueTanksMax;
   int WayPointCnt;
   int WayPointMax;
	int zoomiconsize;
	LoadedBfDesc	loadedbfs[MAXLOADEDBFIELDS];
	LoadedBfDesc	tmploadedbfs[MAXLOADEDBFIELDS];
	SuperGroupDesc	loadedsupergroup[MAXLOADEDSUPERGROUPS];
	SuperGroupDesc  tmploadedsupergroup[MAXLOADEDSUPERGROUPS];
	int bfieldbeingfilled;
	UniqueID	supergroupbeingfilled;
	void __fastcall ScrollBy(int DeltaX, int DeltaY);
};
//---------------------------------------------------------------------------
extern TMissionEditor *MissionEditor;
//extern TransItem*	CurrTransItem;
//extern TransItem*	FirstTransItem;

//---------------------------------------------------------------------------
#endif


