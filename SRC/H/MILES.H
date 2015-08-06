//------------------------------------------------------------------------------
//Filename       miles.h
//System         
//Author         Robert Slater
//Date           Fri 1 Mar 1996
//Description	Header file for the Miles midi and sample library    
//------------------------------------------------------------------------------
#ifndef	MILES_Included
#define	MILES_Included

#define	DEFAULT_MILES 0

#ifdef __DOS__													//ARM 02Aug96
typedef struct  _sequence              // XMIDI sequence state table//JIM 29Jul96
SEQUENCE;
typedef SEQUENCE * HSEQUENCE;       // Handle to sequence
#endif															//ARM 02Aug96
#ifdef WIN95													//ARM 02Aug96
typedef struct _SEQUENCE    * HSEQUENCE;       // Handle to sequence
typedef struct _MDI_DRIVER  * HMDIDRIVER;
#endif															//ARM 15Jul96

typedef struct SmackTag Smack;		//RJS 13Apr99
struct	EnginePlayInfo;											//RJS 21Oct97
struct	SequenceStruct;
typedef SequenceStruct *TuneStrucP;
struct	MusicRequest;
struct	SampleLibrary;
struct	SampleRec;
struct	PlayingRec;		
struct	StatusRec;											
struct	SampleRequest;
typedef PlayingRec *SQueuePtr;									//RJS 17Oct97
typedef SLong     HTIMER;            // Handle to timer
#include	"fileman.h"
class	ItemBase;
typedef ItemBase		*ItemBasePtr;							//JIM 14Feb96
class	rotitem;
typedef rotitem			*RotItemPtr;
struct	PlaneType;
typedef	PlaneType	*ClassPtr;
#include	"flyinit.h"
	struct	SampleRequest
	{
		FileNum	thesample;
		SLong	vol;
		SLong	pan;
	};

	enum	SpotEffects
	{
		SPOT_FRIENDLY_KILLED	=	0,
		SPOT_PLAYER_IN_DANGER	=	1,
		SPOT_PLAYER_GETS_HIT	=	2,
		SPOT_PLAYER_MAKES_HIT	=	3,
		SPOT_PLAYER_MAKES_KILL	=	4
	};

enum	MoodSetting												//RJS 30Jun98
{
	MOOD_TOP	= 127,											//RJS 03Feb99
	MOOD_HERO	= MOOD_TOP,										//RJS 03Feb99
	MOOD_CONFIDENT = 84,
	MOOD_HOPEFUL = 42,
	MOOD_NEUTRAL = 0,
	MOOD_TENSE = -26,
	MOOD_ANGRY = -52,
	MOOD_TROUBLED =	-78,
	MOOD_DESPERATE = -104,
	MOOD_DOOMED	= -128,
	MOOD_BOTTOM = MOOD_DOOMED
};																//RJS 30Jun98

enum	MoodDelta												//RJS 30Jun98
{
	MOOD_DOWN = -2,
	MOOD_NOCHANGE = 0,
	MOOD_UP = 2
};																//RJS 30Jun98

enum	SoundType												//RJS 08Sep98
{																//RJS 08Sep98
	SOUND_DIGITAL = 0,											//RJS 08Sep98
	SOUND_MIDI,													//DAW 18Aug99
	SOUND_RADIO												//DAW 18Aug99
};																//RJS 08Sep98

struct	PercRec
{
	SLong	sampleindex;
	SLong	volume;

public:
	PercRec()	{Reset();}

	void	Reset()
	{
		sampleindex = -1;
		volume = 0;
	}
};

class MilesBase
{
public:
	Bool	incombat;											//RJS 12Nov96
	int		allowedsamples;										//RJS 03Dec96
	int	MusicDir;
	SByte	Mood;												//RJS 03Apr97
	SLong	noTracks;											//RJS 26Feb98
	char*	digerror;
static 	MDI_DRIVER	*mdi;
static	DIG_DRIVER	*dig;
static	MDI_DRIVER	*dls;
	SWord	SavedMusic;											//RJS 27Jul98
	SWord	SavedSfx;											//RJS 27Jul98
	SWord	SavedUISfx;											//RJS 12Mar99

	enum
	{
		MAXTUNES 		= 35,									//RJS 30Aug96
		MAXSEQUENCES 	= 16,
		MAXHANDLERS 	= 16,									//JIM 25Jul96
		MAXSAMPLES 		= 256,									//MS 23Sep98
		PRIORITYFACTOR	= 8
	};

	enum	HSampRate
	{
		MIN_SAMP_VAL	= 11025,								//RJS 30Oct96
		NOM_SAMP_VAL	= 22050,								//RJS 30Oct96
		MAX_SAMP_VAL	= 44100									//RJS 30Oct96
	};

	enum	TuneType
	{
		T_main			=	0,
		T_spoteffects,											//RJS 06May99
		T_seqeffects, 											//RJS 06May99
		T_independent,											//RJS 06May99
		T_independent_pri										//RJS 06May99
	};

	enum	CBTCodes
	{
		CODE_JUMP1		=	1,
		CODE_JUMP2,
		CODE_JUMP3,
		CODE_STANDALONE,
		CODE_SFX,
		CODE_SPECIAL	=	12,
		CODE_HIPRIORITY	=	125,
		CODE_LOPRIORITY	=	126,
		CODE_STOP		=	127
	};

	enum	CBTCodesLo
	{
		CODE_SFX_VOL = 0,
		CODE_SFX_PAN,
		CODE_SFX_BAR
	};

///////////////////

	static	SequenceStruct	tune[MAXTUNES];
	static	MusicRequest	request;
	static	SampleLibrary	wavetable;
	static	SampleRec		*thesample;							//MS 23Sep98
//DeadCode MS 23Sep98 	static	SampleRec		thesample[MAXSAMPLES];
//DeadCode RJS 01Jun98 	static	SampleRec		radiosamples[MAXSAMPLES];				//RJS 19Dec97
	static	PlayingRec		soundqueue[MAXHANDLERS];
	static	StatusRec		status;
	static	HTIMER			timer;
	static	SampleRequest	soundtoplay;
	static	EnginePlayInfo	EngineSound;						//RJS 21May98

	static  Bool			canplaynothing;						//RJS 21May98
	static  Bool			critical;							//RJS 21May98
	static  Bool			inprefs;							//RJS 21May98
	static  Bool			onground;							//RJS 21May98
	static  Bool			musicstopped;						//RJS 21May98
	static 	int				damagelevel;						//RJS 21May98
	static 	int				delindex;							//RJS 21May98
	static	int				thesmackervol;						//RJS 21May98
	static	FileNum			currentengine;						//RJS 21May98
	static	int				bouncecount;						//RJS 21May98
	static	SLong			MAXSAMPLES_LOADED;					//MS 23Sep98
	static	SampleRec		*themusicsample;					//RJS 14Apr99
	static	SLong			percvolscale;						//RJS 29Jun99
	static	PercRec			percussionLog;						//RJS 18Aug99
};

struct	LogSoundRec
{
	ItemBasePtr	theitem;
	FileNum		thefile;
	Bool		isLooped;
	Bool		isSet;
	SLong		vol;
	FileNum		sfile;
	FileNum		efile;
public:
	LogSoundRec()
	{
		isSet = FALSE;
	}

	void	Add(FileNum p1, ItemBasePtr	p2, SLong p3, Bool lp, FileNum p4, FileNum p5)
	{
		isSet = TRUE;
		thefile = p1;
		theitem = p2;
		vol = p3;
		isLooped = lp;
		sfile = p4;
		efile = p5;
	}

	Bool	Get(FileNum& p1, ItemBasePtr&	p2, SLong& p3, Bool& lp, FileNum& p4, FileNum& p5)
	{
		if (isSet)
		{
			isSet = FALSE;

			p1 = thefile;
			p2 = theitem;
			p3 = vol;
			p4 = sfile;
			p5 = efile;
			lp = isLooped;

			return TRUE;
		}
		return FALSE;
	}
};

class	ViewPoint;												//RJS 25May99
class	fileblock;
class	mobileitem;
class Miles:public MilesBase
{
//DeadCode RJS 07Jun99 	Bool		CockpitView;
	void*		pooMidiDev;
	SLong		bestDrivers[16];
	ULong		uDriverID;
	bool		trySoundFonts;

	SLong		freechannelstart;
	SLong		lastBuffetVol;									//RJS 28Jan99
	bool		donePreLoad;
	bool		playerShooting;									//RJS 12Apr99
	SampleRec*	GunSampleIndex;									//RJS 12Apr99
	SLong		shootTimer;

	bool		havePercussion;									//RJS 14Apr99
	bool		setPercussion;									//RJS 14Apr99
	SLong		nomusicsamples;									//RJS 14Apr99
	SLong		channel_percussion;
	SLong		channel_radiochatter;

	void		PreLoadSFX();
	Bool		PreLoadRadioChatter();
	Bool		PreLoadMusicSamples();							//RJS 14Apr99
	void		DeleteMusicSamples();							//RJS 14Apr99

	UByte		randomFAC;										//RJS 17May99
	UByte		randomTOWER;									//RJS 17May99
	bool		donePreLoadRadio;								//RJS 17May99
	bool		playingMiller;									//RJS 21May99
	UByte		randomV2;										//RJS 08Jun99
	bool		rchatter_allowed;								//RJS 16Aug99

	bool		delayedstate;

public:
	mobileitem* View_Point;
	Bool		CockpitView;									//RJS 07Jun99
	LogSoundRec		delayedsounds;

///////////////////

CON     Miles();
void	Init(ULong newwin)		{StartUpMiles(newwin);}			//RJS 13Mar98
void	StartUpMiles(ULong);									//RJS 13Mar98
void	SetVP(mobileitem*);										//RJS 21May98
void	ShutDownMiles();
///////////////////			

#ifdef __DOS__													//ARM 02Aug96
DES		~Miles()	{ShutDownMiles();}
static	void	cdecl mainbeatint(HSEQUENCE callerseq, SLong	channel, SLong	value);
static	void	cdecl subbeatint(HSEQUENCE callerseq, SLong	channel, SLong	value);
static	void	cdecl mainendint(HSEQUENCE callerseq);
static	void	cdecl subendint(HSEQUENCE callerseq);
static	void	cdecl timerint(ULong	user);
#endif															//ARM 02Aug96
#ifdef WIN95													//ARM 02Aug96
#ifdef __WATCOMC__
static	void	AILEXPORT mainbeatint (HSEQUENCE callerseq,signed long channel, signed long value);//ARM 15Jul96
static	void	AILEXPORT subbeatint(HSEQUENCE callerseq, signed long	channel, signed long value);
static	void	AILEXPORT mainendint(HSEQUENCE callerseq);
static	void	AILEXPORT subendint(HSEQUENCE callerseq);
#endif
#ifdef __MSVC__
static	void	__stdcall mainbeatint (HSEQUENCE callerseq,signed long channel, signed long value);//ARM 15Jul96
static	void	__stdcall subbeatint(HSEQUENCE callerseq, signed long	channel, signed long value);
static	void	__stdcall mainendint(HSEQUENCE callerseq);
static	void	__stdcall subendint(HSEQUENCE callerseq);
static	signed long	__stdcall MIDIEventInterrupt(HMDIDRIVER,HSEQUENCE,signed long,signed long,signed long);//RJS 14Apr99
#endif
DES		~Miles()	{ShutDownMiles();/*delete theblock*/;theblock=NULL;}
static	void	cdecl timerint(ULong	user);
	fileblock	*theblock;
#endif															//ARM 15Jul96

///////////////////
private:
Bool		TuneInRange(int	tuneno);
Bool		SequenceInRange(TuneStrucP, int	seqno);
Bool		SampleInRange(int	sampleno);
Bool		HandlerInRange(int	qpos);
void		InitTune(TuneStrucP);
int			GetIndex(FileNum	thefile);
Bool		StartMain(SLong	vol=127);
TuneStrucP	LoadTune(FileNum	thefile);						//RJS 15Aug96
void		InstallWaveTable(FileNum,Bool useDLS=FALSE);		//RJS 19May98
void		StartSequence(FileNum	thefile, int	sequenceno=0, SLong	fadeval=500, SLong	vol=127);
//void		SequenceAudible(SpotEffects spotnum, SLong	vol=127, SLong	fadeval=500);//RJS 29Aug96
void		StopSequence(FileNum	thefile, int	sequenceno=0);
void		SequenceMute(FileNum	thefile, int	sequenceno=0, SLong	fadeval=0);
void		reporterror(int	eno, char	*text=NULL);
SampleRec*	LoadSample(FileNum	thefile,Bool inUI=FALSE);				//RJS 25May99
//DeadCode RJS 16Oct97 SQueuePtr	FindFreeHandler(int	priority, int	spos, ItemBasePtr	sampleitem, SQueuePtr &oldqueue, UByte	looplength=2);//RJS 16Oct97
//DeadCode RJS 17Oct97 void		OverrideSample(SQueuePtr, FileNum	thefile, SLong	vol=-1, SLong	pan=0, SLong	newfreq=-1);//RJS 17Oct97
SLong		ClipVolume(SLong	maxvol, SLong	vol);								
SLong		ClipPan(SLong	pan);
void		FreeSamples();
void		FreeTunes();
SLong		SampleRate(FileNum	thefile);
void		Update3d();											//RJS 19Nov96
void		KillEngine(ClassPtr	classtype, int	dlevel = 5);		//RJS 03Jul96
void		HardStop(SQueuePtr);								//RJS 21Oct97
void		DeleteSample(FileNum	thefile);					//RJS 23Jul96
void		StopLanded();										//RJS 23Jul96
void		GamePaused();										//RJS 09Aug96
void		StopMusic();										//RJS 22Aug96
void		ResumeMusic();										//RJS 22Aug96
void		ResetMidiFlags();									//RJS 29Aug96
void		DiscardMusic(TuneStrucP exception=NULL);			//RJS 26Feb98
bool		FadeAll(SLong);										//RJS 18Jun99
void		OverRevCheck();										//RJS 03Dec96
void		StopMain();											//RJS 12Nov96
void		UpdateEngine();										//RJS 03Dec96
void		PlaySampleEcho(FileNum, ItemBasePtr, SLong	vol = 128);//RJS 05Dec96
void		ProcessInterfaceSpot();								//RJS 17Nov98
void		SequenceAudible(MoraleType, SLong	vol=127, SLong	fadeval=500);//RJS 03Feb99
void		UIPlayAmbient(FileNum,SLong,SLong vol=128);			//RJS 12Mar99

private:

void		DeleteSample(SLong );								//RJS 21May98
Bool		NewDigitalDriver(HSampRate	srate, int	nohandlers, Bool	usemono=FALSE);//DAW 15Dec96
SQueuePtr	FindFreeHandlerOnce(SampleRec*, ItemBasePtr	sampleitem, SQueuePtr&,int	stblock, int	endblock);//RJS 29Jan99
void		PlaySettings(SQueuePtr, SLong	vol, SLong	pan, int priority=0);//RJS 21Oct97
void		SetUpSample(SQueuePtr, SampleRec*, SLong	maxvol, SLong	vol, SLong	pan, ItemBasePtr	sampleitem);//RJS 05Dec96
SLong		SoundInWorld(COORDS3D, SLong &,SLong &);			//RJS 16Oct97
void		GetSampleVolumes();									//RJS 03Apr97
SQueuePtr	FindFreeHandler(SampleRec*, ItemBasePtr	sampleitem, SQueuePtr &oldqueue, UByte	looplength=2);//RJS 16Oct97
void		OverrideSample(SQueuePtr, FileNum	thefile, SLong	vol=-1, SLong	pan=0, SLong	newfreq=-1);//RJS 17Oct97
Bool		StartSeqEffect(TuneStrucP,SLong,SLong);				//RJS 26Feb98
Bool		StartSeqMain(TuneStrucP,SLong,SLong);				//RJS 26Feb98
Bool		StartSeqIndependent(TuneStrucP,SLong,SLong);		//RJS 26Feb98
void		SetCompressedDLS(TuneStrucP,void*,SLong);				//RJS 18May98
void		SetUncompressedDLS(TuneStrucP,void*,SLong);				//RJS 18May98
void		SetXMidi(TuneStrucP);								//RJS 19May98
void		SetDLS(TuneStrucP);									//RJS 19May98
void		PlayWind();											//RJS 20May98
SQueuePtr	FindFreeRadioHandler();								//RJS 09Jun98
void		RowanToPan(SLong&);									//RJS 29Jan99
void		RowanToPan(SWord&);									//RJS 29Jan99
SQueuePtr	FindFreeHandlerUI(SampleRec*);						//RJS 12Mar99
void		PreLoadFile(SLong);									//RJS 01Apr99


public:
//UI
Bool		IsEnabled(SoundType);								//RJS 08Sep98
void		StopAll();
void		SetVolumes(Bool);									//RJS 12Mar99
Bool		InitUI(int);										//RJS 06Apr99
Bool		Init3D();										//RJS 26Jul96
void		SetDirectSoundWindow(ULong);						//RJS 03Apr98
void		KillAll();
void		DisableAll();
void		UIPlaySample(FileNum,SLong vol=128);				//RJS 12Mar99
void		InitSoundFonts();
//COMMS
ULong		GetSysTime();										//AMM 11Jun99
//MOVE
void		ResetSoundFlags();									//RJS 12Jul96
void		PlayEngine(SLong,AirStrucPtr,SLong	rpm, SLong	vel,SWord);//RJS 17Nov98
void		PlayLanded(ItemBasePtr	sampleitem, SLong	velocity,Bool skid);//RJS 14Jan99
void		PlayBuffet(SLong vol, SLong pan=0);					//RJS 28Jan99
void		ProcessPercussion();								//RJS 18Aug99
//MODEL
void		PlayWindyMiller(AirStrucPtr);						//RJS 21May99
void		SetEngine();//RJS 06Oct98
void		SequenceMute(SLong	fadeval=500);					//RJS 24Mar99
//GENERAL
void		ProcessSpot(ViewPoint*);							//RJS 25May99
void		PlayOnce(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol=128,FileNum	stsam=FIL_NULL, FileNum	endsam=FIL_NULL);//RJS 27Nov96
void		PlayOnce(FileNum	thefile, int	vol=128,SLong thepan=0);//RJS 28Jan99
void		SmackerOn(Smack*);								//RJS 13Apr99
void		SmackerOff();										//RJS 06Apr99
void		SetCockpit(Bool);									//RJS 20May98
void		PlayDelayed(FileNum,ItemBasePtr,SLong vol=128,Bool islooped=FALSE,FileNum	stsam=FIL_NULL, FileNum	endsam=FIL_NULL);
void		SequenceAudible(FileNum	thefile, SLong	vol=127, SLong	fadeval=500);//RJS 29Aug96
void		HaltItemSound(ItemBasePtr	sampleitem);			//RJS 11Jul96
Bool		StartShooting(FileNum,SLong,SLong);					//RJS 31May99
void		PlayLooped(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol=128, UByte	looplength=2, Bool sound3d=TRUE);//RJS 01Jun99
void 		PlaySample(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol = 128);//RJS 17Oct97
void 		PlaySample(FileNum	thefile, SLong	vol=-1, SLong	pan=0);//RJS 17Oct97
void		StopShooting();								//RJS 12Apr99
void		StopEngine(int	velocity=-1);
void		PlayFlyAway(ItemBasePtr);							//RJS 21May98
void		StopSample(FileNum	thefile, ItemBasePtr	sampleitem = NULL);//RJS 15Jul96
void		SequenceAudible(MoodSetting, SLong	vol=127, SLong	fadeval=500);//RJS 30Jun98
void		SequenceAudible(MoodDelta, SLong	vol=127, SLong	fadeval=500);//RJS 30Jun98
void		SetUpRandomVoices(SLong,SLong,SLong);				//RJS 08Jun99
Bool		SampleFinished(UByteP,bool);						//RJS 25May99
UByteP		PlaySampleRadio(UByteP, int, SWord,int, int);		//RJS 14Jan99
void		SetGlobalVolumes(int	sfxvol=127, int	midivol=-1, int	engvol=-1,int smackervol=-1, Bool	saveset=FALSE);//RJS 29Sep96

void		SetDelayed(bool dstate=true);

};
extern Miles _Miles;

#endif
