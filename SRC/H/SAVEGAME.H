//------------------------------------------------------------------------------
//Filename       savegame.h
//System         
//Author         R. Hyde 
//Date           Mon 22 Apr 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	SAVEGAME_Included
#define	SAVEGAME_Included

#include "analogue.h"
#include "myangles.h"
#include "bitcount.h"
#include "config.h"

#define	DEFAULT_SAVEGAME 0

enum	FlightDifficulty		{FD_MIN = 0,
				FD_THRUSTPOWERCONTROL = 0,
				FD_TORQUEEFFECTS,
				FD_JETFLAMEOUT,
				FD_LIMITEDFUEL,
				FD_POWERBOOST,
				FD_WINDEFFECTS,
				FD_WINDGUSTS,
				FD_AIRCRAFTINTERFERENCE,
				FD_IDEALSANDCONTROL,
				FD_COORDINATEDRUDDER,
				FD_SPINS,
				FD_SLIPSTREAMEFFECTS,
				FD_GEARSUSPENSION,
				FD_EXCESSIVEACCELDAMAGE,
				FD_STORESWEIGHTDRAG,
				FD_AUTOTHROTTLE,
				FD_FF_GUN,
				FD_FF_BUFFET,		//FD_FF_STALL,
				FD_FF_AERODYNAMIC,	//FD_FF_SPEED,
				FD_FF_AIRFRAME,


								FD_MAX};

MAKEFIELD(FlightDifficulty,FD_MIN,FD_MAX);


enum	GameDifficulty		{GD_MIN = 0,

		GD_UNLIMITEDARM = 0,									//RJS 06May99
		GD_RELOADARMS,											//RJS 25Jan99
		GD_USAIRCRAFTFITTEDWITHGUNS,
		GD_GUNJAM,
		GD_STICKINGORDINANCE,
		GD_INSIDECOCKPITONLYAVAILABLE,
		GD_TEXTCHATTER,
		GD_PADLOCKONLYWHENVIS,
		GD_ALTXTOEXIT,
		GD_TACTICALRANGE,
		GD_BESTVARIANTS,
		GD_REALISTICRADARASSISTEDGUNSIGHT,
		GD_PERFECTRADARASSISTEDGUNSIGHT,
		GD_VULNERABLE,
		GD_GROUNDCOLLISIONS,
		GD_COLLISIONS,
		GD_WHITEOUT,
		GD_BLACKOUT,	//superceded by geffects and injury effects				//last of 1st set
		GD_PERFECTUSGCI,
		GD_PERFECTCOMMUNISTGCI,
		GD_PERFECTCOMMUNISTAAA,
		GD_AUTOPADLOCKTOG,										//PD 18Nov97
		GD_VIEWMODESELECT,										//PD 18Nov97
		GD_UPTOGGLESTICKS,										//PD 18Nov97
		GD_REDOUT,		//superceded by geffects and injury effects
		GD_AIPILOTSALLTIME,
		GD_MAXOPTION,
		FRAME_RATE_DISPLAY,
		GD_WEATHEREFFECTS,
		GD_PERIPHERALVISION,
		GC_MULTIPLAYERVIEWRESTRICTED,
		GD_GUNCAMERACOLOUR,
		GD_INFOLINESTATUS,
		GD_UNITS,
		GD_GUNCAMERAATSTART,
		GD_GUNCAMERAONTRIGGER,
		GD_GEFFECTS,
		GD_INJURYEFFECTS,
		GD_AUTOVECTORING,
		GD_HUDINSTACTIVE,
		GD_VISIBLEMIGSCHEAT,
		GD_DISPLAYMESSAGES,
		GD_NOPLAYERVOICE,										//RJS 30Jun99


								GD_MAX};

MAKEFIELD(GameDifficulty,GD_MIN,GD_MAX);

enum	SG_Detail_3D		{DETAIL3D_MIN = 0,
							DETAIL3D_HORIZONFADE=0,
							DETAIL3D_HORIZONDIST,
							DETAIL3D_INCONSEQUENTIALS,
							DETAIL3D_AUTODETAIL,
							DETAIL3D_TRANSSMOKE,
							DETAIL3D_ITEMSHADING,
							DETAIL3D_GROUNDSHADING,
							DETAIL3D_ITEMSHADOWS,
							DETAIL3D_AIRCRAFTSHADOWS,
							DETAIL3D_ROUTES,
							DETAIL3D_CONTOURDETAIL,
							DETAIL3D_PADLOCKCHEAT,
							DETAIL3D_FASTFRAME,
							DETAIL3D_MAX};

MAKEFIELD(SG_Detail_3D,DETAIL3D_MIN,DETAIL3D_MAX);

// Cockpit detail switches...									//RJS 23Jan98
enum	SG_Detail_Cockpit3D
{
	COCK3D_MIN = 0,
	COCK3D_PANELPLAIN = 0,		//plain panel behind dials
	COCK3D_PANELHOODPLAIN,		//plain cowling
	COCK3D_PANELIMAPDSPLIT,		//split panels to stop bend	
//	COCK3D_PANELIMAPDSPLIT,
	COCK3D_PANELGLASSFRONT,		//reflection map on front
	COCK3D_PANELSHADOWFRONT,	//moving dial shadow maps on front
	COCK3D_DIALSROW1ON,			//top row
	COCK3D_DIALSROW2ON,
	COCK3D_DIALSROW3ON,
	COCK3D_DIALSROW4ON,			//bottom row
	COCK3D_FRONTQIMAPD,			//front quarter artwork
	COCK3D_SIDEQIMAPD,			//side artwork
	COCK3D_REARQIMAPD,			//rear quarter artwork
	COCK3D_GUNSIGHTPANE,		//pane of glass in gunsite
	COCK3D_GUNSIGHTFURNITURE,	//furniture at bottom truncated
	COCK3D_GUNSIGHTTRANS,		//whole gunsite transparent
	COCK3D_SKYTRANS,			//imagemaps in the sky rather than lines
	COCK3D_SKYIMAGES,			//translucent
	COCK3D_SKYWHENDOWN,			//even when looking down into cockpit
//	COCK3D_PERIPHERALVISION,
	COCK3D_MAX //= 31
};											


//this gives 1 bit per flag above
MAKEFIELD(SG_Detail_Cockpit3D,COCK3D_MIN,COCK3D_MAX);			//RJS 23Jan98

enum	MapFilters	
{
	MAPFILTERSMIN,
	FILT_BLUE_CIVILIAN,
	FILT_BLUE_SUPPLY,
	FILT_BLUE_MYARD,
	FILT_BLUE_BRIDGE,
	FILT_BLUE_ROADLINK,
	FILT_BLUE_RAILLINK,
	FILT_BLUE_TRUCK,
	FILT_BLUE_TRAIN,
	FILT_BLUE_ARTIE,
	FILT_BLUE_TROOP,
	FILT_BLUE_TANK,
	FILT_BLUE_AIRFIELDS,
	MAPFILTERSMAXBLUE,
	FILT_RED_CIVILIAN,
	FILT_RED_SUPPLY,
	FILT_RED_MYARD,
	FILT_RED_BRIDGE,
	FILT_RED_ROADLINK,
	FILT_RED_RAILLINK,
	FILT_RED_TRUCK,
	FILT_RED_TRAIN,
	FILT_RED_ARTIE,
	FILT_RED_TROOP,
	FILT_RED_TANK,
	FILT_RED_AIRFIELDS,

	MAPFILTERSMAXRED,
	  FILT_MAINWP,
	  FILT_SUBWP,
	  FILT_ROUTES,
	  FILT_FRONTLINE,

	MAPFILTERSMAX
};
MAKEFIELD(MapFilters,MAPFILTERSMIN,MAPFILTERSMAX);

enum ProcType {PROC_SLOW=0,PROC_MIN,PROC_MED,PROC_MAX};

enum	TargetSize		{TS_MIN = 0,TS_SMALL=0,TS_MEDIUM,TS_LARGE,TS_MAX};//PD 30Aug96
//DeadCode RDH 24Oct96 	enum					{MAXWEATHERNUM = 3};

//------------------------------------------------------------------------------
//Author		R. Hyde 
//Date			Mon 22 Apr 1996
//Modified	
//
//Description	
//
//Inputs		
//------------------------------------------------------------------------------
enum	DateOrder	{DO_UK_DMY,DO_US_MDY,DO_JP_YMD};

struct	DistanceFactors
{
	int	shortnm,		//CM or IN				in nm
		mediummm,		//METRES or YARDS		in mm
		longcm;			//KM or MILES			in cm
	int	shortname,
		mediumname,
		longname;
	int	shortabbr,
		mediumabbr,
		longabbr;
};

struct	AltitudeFactors
{
	int	shortnm,		//CM or IN							in nm
		mediummm,		//METRES or FEET					in mm
		longcm;			//thousands of metres or feet		in cm
	int	shortname,
		mediumname,
		longname;		//THOUSAND FEET
	int	shortabbr,
		mediumabbr,
		longabbr;		//'000FT
	int mediumstepsize,
		minstepcount,	//controls list of offered altitudes
		maxstepcount;
};
struct	SpeedFactors
{
	float
		mmpcs2persec,
		mmpcs2permin,
		mmpcs2perhr;
	int	persecname,
		perminname,
		perhrname;
	int	persecabbr,
		perminabbr,
		perhrabbr;

};
struct	MoneyFactors
{
	int		penceperunit;
	int		fractionsperunit;
	char	fractionseparator;
	int		fractionmane,
			unitname,
			fractionabbr,
			unitabbr;
};
struct	MassFactors
{
	int		gm;		  //in kg or lb
	int		nametype;
	int		abbrtype;
};
struct	VolumeFactors
{
	int		type;
	int		nametype;
	int		abbrtype;
};


class	SaveDataLoad
{
public:
	enum	Units		{METRIC,IMPERIAL,UNITS_LEN};
	enum	Currency	{ENGLISH,CURRENCY_LEN};
	enum	{NAMEARRAYSIZE = 20};
	FlightDifficultyField	flightdifficulty;
	GameDifficultyField	gamedifficulty;
	SG_Detail_3DField	detail_3d;
	SWord filtering;
	UWord textureQuality;
	//GameSettings	gameSettings;
	MapFiltersField		mapfilters;
	TargetSize targetsize;										//PD 30Aug96
	DateOrder	dateorder;
	UByte	metricdistance:1,
			metricspeed:1,
			metricalt:1;
	SWord	messagelines;										//RDH 01Oct96
	SWord	autopilotskillUN;
	SWord	autopilotskillRED;
	SWord	pixelsize;
	SWord	gammacorrection;
	SWord	desiredfps;
	SWord	infoLineCount;
//DeadCode RDH 24Oct96 	SWord	weathernum;											//RDH 02Oct96
//DeadCode RDH 24Oct96 	struct	Wind {
//DeadCode RDH 24Oct96 				SWord	speed;
//DeadCode RDH 24Oct96 				SWord	velx;
//DeadCode RDH 24Oct96 				SWord	velz;
//DeadCode RDH 24Oct96 				ANGLES	direction;			//direction from which the wind comes
//DeadCode RDH 24Oct96 				}	wind;
	struct	Vol {	// Duplicated in comms.h					//ARM 04Oct96
				SWord	sfx;
				SWord	engine;
				SWord	anim;
				SWord	music;									//RJS 21Aug96
				SWord	rchat;									//RJS 11Jun98
				SWord	uisfx;									//RJS 12Mar99
				SWord	uiambient;								//RJS 12Mar99
				}	vol;
	SLong	missiontime;										//RDH 22Nov96
	SWord	screenresolution;									//RDH 22Oct96
	SWord	colourdepth;										//PD 04Feb97
	SWord	displayW,displayH;
	SWord	dddriver;											//PD 22May97
	ProcType processorType;
	SDrivers sd;
	bool	fNoHardwareAtAll;
	bool	fSoftware;
//DeadCode RDH 22Nov96 	SWord	tfdiv,milediv;
	SWord	rangediv,speeddiv;
//DeadCode RDH 14Aug96 	SWord	missionwpset;
//DeadCode JIM 20Nov96 	SaveData::SaveData()	{}
//DeadCode RDH 22Apr96 		SaveData::~SaveData();
//DeadCode JIM 22Aug96 	char	namearray [NAMEARRAYSIZE];
	UByte	viewwobble;											//PD 18Nov97
	SG_Detail_Cockpit3DField	cockpit3Ddetail;									//RJS 23Jan98
	SWord	SeekStep,PingStep,PingDelay,SeekingDelay;
	ANGLES  fieldOfView;
	bool	successfulLoad;

	DistanceFactors	dist;
	AltitudeFactors	alt;
	SpeedFactors	speed;
	MoneyFactors	curr;
	MassFactors		mass;
	int			keysensitivity;										  //JIM 11/06/99
//DeadCode AMM 19Jan99 	char	CommsPassword[11];									//AMM 14Dec98

//not included until needed	VolumeFactors	volume;
	protected:
	private:

};
class	SaveDataNoLoad:public	SaveDataLoad
{
public:
#if defined(__AFX_H__) || defined(CSTRING_Included)
	CString		lastsavegame,lastreplayname,lastpackname;
#endif
	void	InitPreferences(int);
	void	SavePreferences();
	void	SetUnits();

};

typedef SaveDataNoLoad	SaveData;

extern	SaveData Save_Data;
extern	SaveData Temp_Data;

class	BIStream;
class	BOStream;
class	MissMan;
class	SaveDataNoLoad;
typedef	SaveDataNoLoad	SaveData;
//DeadCode RDH 24Sep96 	BIStream& operator	<<	(BIStream&,MissMan&);
//DeadCode RDH 24Sep96 	BOStream& operator	>>	(BOStream&,MissMan&);
//DeadCode RDH 24Sep96 	BIStream& operator	<<	(BIStream&,SaveData&);
//DeadCode RDH 24Sep96 	BOStream& operator	>>	(BOStream&,SaveData&);

//called from mfc\filing.cpp & 
	BIStream& operator	>>	(BIStream&,MissMan&);
//called from mfc\filing.cpp & 
	BOStream& operator	<<	(BOStream&,MissMan&);
	BIStream& operator	>>	(BIStream&,SaveData&);
	BOStream& operator	<<	(BOStream&,SaveData&);




class	WorldStuff;
struct	DamageDef;
class	DeadStream
{
public:
	//This is a stream of records of following format:
	//	UID
	//	HowLongDead
	//	Shape
	//  first byte of anim: contains num launchers to skip
	//	Len of anim
	//	Anim
	enum	{maxblocksize=1024};			//JIM 04Nov96
	struct	DeadBlock
	{
//DEADCODE JIM 24/02/99 	struct	T_SGT{											
//DEADCODE JIM 24/02/99 			UWord	value;									
//DEADCODE JIM 24/02/99 			operator UniqueID()	{return (UniqueID(value));}			
//DEADCODE JIM 24/02/99 			UniqueID operator = (UniqueID v)	{return (UniqueID(value=v));}
//DEADCODE JIM 24/02/99 		}	SGT;	
		ONLYFIELD(UWord,UniqueID,SGT);
		UWord		dataused;
		DeadBlock*	nextblock;
		char data[maxblocksize];
		DeadBlock(UniqueID sgt=UID_NULL) {nextblock=0;(int&)(data[0])=0;dataused=0;SGT=sgt;}
	};
	typedef	DeadBlock* DeadBlockPtr;

	class	DeadBlockItterator;
//	{
//		bool newpage;
//		UniqueID		SGT;
//		DeadBlockPtr*	base;
//		DeadBlockPtr	curr;
//		char*			off;
//		DeadBlockItterator(DeadBlockPtr& deadbase,UniqueID sgt=UID_NULL);
//		bool	PutInfo(void*,int);			//true if new page
//		bool	PutCountedInfo(void* v,int i) {bool rv=PutWord(i);rv|=PutInfo(v,i);return rv;}
//		bool	PutByte(UByte i)	{return PutInfo(&i,1);}
//		bool	PutWord(UWord i)	{return PutInfo(&i,2);}
//		bool	PutLong(int i)		{return PutInfo(&i,4);}
//		bool	PutItemID(ItemBasePtr);
//		void	GetInfo(void*,int);
//		int		GetCountedInfo(void* v,int max) 
//		{int count=GetWord();if (count<max) GetInfo(v,count) else return -count; return count;}
//		UByte	GetByte()	{UByte	rv;GetInfo(&rv,1);return rv;}
//		UWord	GetWord()	{UWord	rv;GetInfo(&rv,2);return rv;}
//		int		GetLong()	{int	rv;GetInfo(&rv,4);return rv;}
//		ItemBasePtr
//				GetItemID();
//		UniqueID	NextSGT()	
//		{if (curr && curr->nextblock) return curr->nextblock->SGT; else return UID_NULL;}
//	};


	int	olddaytime;
	DeadBlock* firstblock;
	//init all to zero
	bool	ClearForSGT(UniqueID);

	void	SetWorldDead(WorldStuff* world);	//this sets the static data to reflect the world
	void	GetWorldDead(WorldStuff* world);	//this sets the world to reflect the static data
	void	ClrWorldDead();
	void	ReviveWorld(const int repairpointsinperiod=7,const int repairbridgepointsinperiod=2);
	int	DecodeDamage(UniqueID SGT,DamageDef* damagetable);
	static	bool	MainWorldBand(UniqueID u);
	static	bool	DontRecordBand(UniqueID u);
	void	ScoreSGKills();


};
extern	DeadStream	Dead_Stream;
class	ItemBase;
typedef	ItemBase *ItemBasePtr;
#ifndef	__BCPLUSPLUS__
class	DeadStream::DeadBlockItterator
	{
		friend	DeadStream::DeadBlockItterator;
		bool newpage;
		UniqueID		SGT;
		DeadBlockPtr*	base;
		DeadBlockPtr	curr;
		int			off;
		void	DeleteTempBlock();
public:
		int			lastnumelts;
		SWord	lastuniqueID;	//access with myitem->uniqueID.count
		SWord	lastStatus;		//access with myitem->Status.size
		SWord	lastshape;
		CON		DeadBlockItterator(DeadBlockPtr& deadbase,UniqueID sgt=UID_NULL);
		DES		~DeadBlockItterator();
		CON		DeadBlockItterator(const DeadBlockItterator* clone)
		{
			if (clone->newpage && !clone->off)
				INT3;
			*this=*clone;
			newpage=false;
		}
		bool	PutInfo(void*,int);			//true if new page
		bool	PutCountedInfo(void* v,int i) {bool rv=PutWord(i);rv|=PutInfo(v,i);return rv;}
		bool	PutByte(UByte i)	{return PutInfo(&i,1);}
		bool	PutWord(UWord i)	{return PutInfo(&i,2);}
		bool	PutLong(int i)		{return PutInfo(&i,4);}
		bool	PutItemID(ItemBasePtr);
		void	GetInfo(void*,int);
		int		GetCountedInfo(void* v,int max) 
		{int count=GetWord();if (count<max) {GetInfo(v,count); return count;} return -count;}
		int		SkipCountedInfo();
		UByte	GetByte()	{UByte	rv;GetInfo(&rv,1);return rv;}
		UWord	GetWord()	{UWord	rv;GetInfo(&rv,2);return rv;}
		int		GetLong()	{int	rv;GetInfo(&rv,4);return rv;}
		ItemBasePtr	GetItemID();
		UniqueID	NextSGT();
		bool	SkipToSGT(UniqueID sgt);
		char*	GetPointerToCurrent()	{return curr->data+off;}
		void	NextDeadElt(UByte&di1b,int&diplc,char*&dipld);
		void	SetNextDeadElt(char di1b,int diplc,char* dipld);
		void	SkipNextDeadElt();
	 	void	NextEltClearDamage();
		UniqueID	SkipItem();
		bool		SkipToItem(UniqueID u);

	};
#endif


#endif
