//------------------------------------------------------------------------------
//Filename       animdata.h
//System         
//Author         Robert Slater
//Date           Mon 10 Feb 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	ANIMDATA_Included
#define	ANIMDATA_Included

#define	DEFAULT_ANIMDATA 0

typedef	void	*detectrtnref;



//For now, keep anim flags under 1 byte each to allow easy indexing

//enum	ItemState {DEAD = -1,ALIVE,DAMMAGED,DYING};
enum	ItemState {ALIVE=0,DAMMAGED,DYING,DEAD};

enum	WarningLights	{STALLON=1,PRESTALLON=2,BRAKEON=4,WBRAKEON=8};
enum	ToggleLights	{FLAPSON=1,GEARON=2,WBREAKON=4,BREAKON=8};


class	MinAnimData
{
public:
	UByte		nolaunchers:4,									//RJS 03Dec98
				IsBullied:1,									//RJS 03Dec98
				itemstate:2,									//RJS 22Oct97
				IsInvisible:1;									//RJS 17Nov98
};

class	GrpMinAnimData
{
public:
	UByte		nolaunchers:4,
				IsBullied:1,
				itemstate:2,
				IsInvisible:1;
};

class	SunAnimData:public	MinAnimData							
{																
public:															
	Bool	wasdrawn;
	UByte	fader;												//RJS 22Jun98
	UByte	frameno;											//RJS 02Jul98
};																

class	ExplodeAnimData:public	MinAnimData						
{
public:
	SWord	frameno;
};

class	FireAnimData:public	MinAnimData							
{
public:
	SWord	frameno;
};

class	BalloonAnimData:public	MinAnimData	
{
public:
	Bool	manjumped;											//RJS 01Oct97
	SLong	groundheight;
	SWord	countdown;
	UByte	frameno;											//RJS 01Oct97
};

class	BarageAnimData:public	MinAnimData						
{
public:
	SWord	countdown;
};

class	TroopAnimData:public	MinAnimData						
{
public:
	SByte	frameno;							
	SLong	xpos, ypos, zpos;									//RJS 01Oct97
	UByte	homing:1,						
			oncourse:1;
};

class	DirectAnimData					
{
public:
	SWord		hdg,pitch;										//RJS 12Jan98
};

class	WeapAnimData:public	DirectAnimData
{
public:
	UByte			LauncherType;								
	UWord			LaunchTime;
	SWord			Stores,
					LoadedStores;
	UWord			target;										//RJS 24Nov97
	UWord			stationshape:10,
					SubDamage:5,
					IsArmed:1;									//RJS 11Jun97
};

class	MoveGunAnimData:public	MinAnimData
{
public:
	WeapAnimData	weaponlaunchers[1];							
};

class	TwoGunAnimData:public	MinAnimData						
{																
public:															
	WeapAnimData	weaponlaunchers[2];							
};

class	AircraftAnimData:public	MinAnimData						
{
public:
	WeapAnimData	weaponlaunchers[14];						//RJS 18Jun98

	UByte			imagemapemblem;								//RJS 12Mar99
	UByte			imagemapacid1;								//RJS 11Mar99
	UByte			imagemapacid2;								//RJS 11Mar99
	UByte			imagemapacid3;								//RJS 11Mar99

	UByte			nokills;									//RJS 09Jun97

	UByte			acaileronl,
					acaileronr,
					acelevator,								
					acrudder;

	UByte			acflaps,
					acbreak;									//RJS 17Feb98

	UByte			acleglowerl,
					acleglowerr,
					acleglowerf,
					acleglowerb;

	UByte			aclegsuspl,
					aclegsuspr,
					aclegsuspf,
					aclegsuspb;

	UByte			aclegsteer;
	UByte			acbombbays;									//RJS 25Jan99

 	UWord			acrpm;										//RJS 03Sep97

	UByte			exhaustframe;								//RJS 17Jun98
 	UByte			frameno;									//RJS 27Aug97
	SWord			randvel;									//RJS 14Feb97
	UByte			animtoggle;									//RJS 18Feb97
	UByte			animtimer;									//RJS 18Feb97
	UWord			timenotvis;									//RJS 30Jun99

	UByte			aclightclock1;								//RJS 15Feb99
	UByte			aclightclock2;								//RJS 15Feb99
	UByte			lighttoggle:1,								//RJS 12Mar99
					hassmoked:1,								//RJS 06Jun99
					muzzleflash:1,								//RJS 06Jun99
					shooting:1,									//RJS 06Jun99
					DUMMYPAD:4;									//RJS 06Jun99

	UByte			currweapindex:6,
					hasdust:1,
					justlanded:1;

	UByte			LEFTWINGOUT,
					LEFTWINGIN,
					RIGHTWINGOUT,
					RIGHTWINGIN,
					PILOTLEFT,
					PILOTRIGHT,
					PROPLEFTOUT,
					PROPLEFTIN,
					PROPRIGHTIN,
					PROPRIGHTOUT,
					ENGINELEFTOUT,
					ENGINELEFTIN,
					ENGINERIGHTIN,
					ENGINERIGHTOUT,
					INTFUELLEFT,
					INTFUELRIGHT,
					EXTFUELLEFT,
					EXTFUELRIGHT,
					LEFTWEAPONS,
					RIGHTWEAPONS,
					TAIL,
					FIN,
					LEFTWHEEL,
					RIGHTWHEEL,
					FRONTWHEEL,
					BACKWHEEL,
					CANOPY1,
					CANOPY2,
					FRONT,
					OTHER;
};

class	PolyPitAnimData:public	AircraftAnimData				
{
public:
	UByte	actempexhaust;		
	UByte	actempair;											
	UByte	acaltitude;
	UByte	acalt1000;
	UByte	acspeed;
	UByte	acfuelint;
	UByte	acfueltot;											//CSB 14Apr99
	UByte	acmach;
	SWord	acclimb;											//RJS 10Feb98
	UByte	acpitch;
	UByte	acvoltage;
	UByte	accompass;
	SWord	acgyrocompass;
	UByte	acrpmdial;
	UByte	acrpmpercent;
	UByte	acaccel;
	UByte	accabinpress;
	UByte	acfuelpress;
	UByte	achydraulicpress;
	UByte	acoilpress;
	UByte	acclockhour;
	UByte	acclockmin;
	UByte	acclocksec;											//RJS 30Mar98
	UByte	actempgas;											//RJS 30Mar98
	UByte	acoxygenpress;										//RJS 30Mar98
	UByte	acslip;												//RJS 06Apr98
	UByte	acturn;												//RJS 06Apr98
	UByte	acspeed100;											//RJS 20Apr98
	UByte	acrpmtotal;											//RJS 20Apr98
	UByte	acbank;												//RJS 21Apr98
	UByte	acgunrange;											//RJS 26May98
	UByte	acwingspam;											//RJS 26May98
	UByte	acsuctionguage;										//RJS 19Jun98
	UByte	acmanifoldpress;									//RJS 19Jun98
	UByte	accarburettor;										//RJS 19Jun98
	UWord	acammoleft;											//RJS 09Sep98
	SWord	acgyrocompassflip;									//RJS 31Mar99
	UByte	acalt100;											//RJS 31Mar99
	UByte	acfuelext;											//CSB 14Apr99

	UByte	lightfire;											//RDH 13Apr99
	UByte	lightstall;											//RDH 13Apr99
	UByte	lightguncamera;										//RDH 13Apr99
	UByte	lightgunsight;										//RDH 13Apr99

	UByte	fuelswitch:1,										//RDH 13Apr99
			gunotherswitch:1,									//RDH 13Apr99
			bombrocketswitch:1;									//RDH 13Apr99

	UByte	lastweapindex;										//RJS 17Jun99

	ULong	detailmask;											//RJS 23Jan98
	UWord	acprevammoleft;										//RJS 17Jun99
};

class	LauncherAnimData:public	MinAnimData
{
public:
	UByte	ammoleft;							
};

class	WindsocAnimData:public	MinAnimData
{
public:
	UByte	frameno;							
};

class	CloneAnimData:public	MinAnimData						//RJS 01Oct97
{																//RJS 01Oct97
public:															//RJS 01Oct97
	UWord	shapename:10,										//RJS 08Sep98
			weapindex:3,										//RJS 08Sep98
			weapindex2:3;										//RJS 08Sep98
	UByte	lnchtype;											//RJS 21Jul98
	UByte	delay;												//RJS 21Jul98
	ULong	originitm;											//RJS 21Jul98
};																//RJS 21Jul98

class	FlareAnimData:public	MinAnimData						//RJS 21Jan98
{																//RJS 21Jan98
public:															//RJS 21Jan98
	UByte	colstep;											//RJS 21Jan98
	UByte	depth;												//RJS 21Jan98
};																//RJS 21Jan98

class	ParachuteAnimData:public	MinAnimData
{
public:
	UByte	stage;
	ULong	detailmask;
	ULong	animclock;
	UWord	frameno;
	UByte	BLOKEON;
	UByte	OTHER;
};

class	ThugAnimData:public	MinAnimData
{
public:
	UWord	prevcount:15,
			disableprev:1;
	UWord	nextcount:15,
			disablenext:1;
	UWord	panimoff;
	UWord	nanimoff;
	SLong	pXPos;
	SLong	pYPos;
	SLong	pZPos;
	SLong	nXPos;
	SLong	nYPos;
	SLong	nZPos;
};

class	MissileAnimData:public	MinAnimData
{
public:
	UByte	frameno;
	UByte	hitstrength;										//DAW 01Dec98
	UByte	novirtualguns;										//RJS 29Mar99
	ULong	lastmissile;										//RJS 29Mar99
	UWord	target;												//RJS 29Mar99
};

class	DebrisAnimData:public	MinAnimData						
{
public:
	UByte	frameno;
};

class	SmokeTrailAnimData:public	MinAnimData
{
public:
	WeapAnimData	weaponlaunchers[1];
	ULong			thelist;
	UWord			nopoints;					
 	ULong			lifetime;									
	ULong			currTime;										
	UWord			SmkDescIndex:8,
					isDegraded:8;
};

class	BlokesAnimData:public	MinAnimData
{
public:
	UByte			beenlaunched:1,
					animtype:7;
	UWord			timer;
	UWord			nearestuid;
};

class	TrainAnimData:public	MinAnimData						
{
public:
	WeapAnimData	weaponlaunchers[1];
};





#endif
