//------------------------------------------------------------------------------
//Filename       milesxtr.h
//System         
//Author         Paul Dunscombe
//Date           Fri 13 Aug 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	MILESXTR_Included
#define	MILESXTR_Included

#define	DEFAULT_MILESXTR 0

struct SampleRec
{
	fileblock	*blockptr;
	SLong		size;
	ULong		priority;										//RJS 11Jun99
	UWord		samplerate;									//RJS 16Oct97
	SLong		samplevolume;								//RJS 23Feb99
//DeadCode AMM 23Feb99 	ULong		LastTime;									//RJS 16Oct97
	ULong		datasize;										//RJS 09Mar98
	void*		dataptr;										//RJS 09Mar98
};

typedef struct	PlayingRec
{
	HSAMPLE			handler;
	int				playingpriority;
	SampleRec*		sampleindex;								//RJS 17Oct97
	UWord			playingvolume;								//RJS 17Oct97
	UWord			playingfrequency;							//RJS 17Oct97
	ItemBasePtr		worlditem;									//RJS 17Oct97
	COORDS3D		StaticPos;									//RJS 17Oct97
	UByte			GameSound:1,								//RJS 17Oct97
					looping:1,									//RJS 09Jun98
					isRadio:1;									//RJS 09Jun98
} SQueue;

	struct	SampleLibrary
	{
		fileblock	*blockptr;
		SLong		size;
		HWAVESYNTH	wavesynth;									//RJS 19May98
		HDLSDEVICE	DLSwavesynth;								//RJS 19May98
	};

	typedef struct	SequenceStruct								//RJS 26Feb98
	{
		HSEQUENCE	sequence[MilesBase::MAXSEQUENCES];
		HSEQUENCE	DLSsequence[MilesBase::MAXSEQUENCES];		//RJS 19May98
		fileblock	*blockptr;
		SLong		size;
		int			nosequences;
		MilesBase::TuneType	ttype;
		HDLSFILEID	dlsID;										//RJS 18May98
		void		*dlsPtr;									//RJS 18May98
		void		*xmiPtr;									//RJS 18May98
		SLong		dlsSize;									//RJS 18May98
		SLong		xmiSize;									//RJS 18May98
	}TuneStruc, *TuneStrucP;									//RJS 26Feb98

struct	SubMiles
{

};

	#define	INT_NULL			0								//RJS 18Jun99
	#define	INT_ON				1								//RJS 18Jun99
	#define	INT_STOPSEQUENCE	2								//RJS 18Jun99
	#define	INT_FADER			4								//RJS 18Jun99
	#define	INT_DIRECTION		8								//RJS 18Jun99

	#define	MUSIC_TIMEOUT		12000		//2mins					//RJS 18Jun99

	struct	MusicRequest
	{
		ULong		activated;									//RJS 18Jun99
//DeadCode RJS 18Jun99 		UByte		activated:1,								//RJS 17Oct97
//DeadCode RJS 18Jun99 					fader:1,									//RJS 17Oct97
//DeadCode RJS 18Jun99  					stopsequence:1;							//RJS 17Oct97
		UByte		todiscard:1,								//RJS 17Oct97
					killnow:1,									//RJS 17Oct97
					mainstopped:1,								//RJS 17Oct97
					wait:1,										//RJS 17Oct97
					forcestop:1;								//RJS 18Jun99
		HSEQUENCE	NewHandle;
		SLong		NewVolume;
		SLong		NewFade;
		TuneStrucP	alonetuneno;
 		SLong		musictimeout;								//RJS 18Jun99
		SLong		CurrentTrack;
	};

	typedef struct
	{
   		SByte RIFF_string[4];
   		ULong chunk_size;
   		SByte  ID_string[4];
   		UByte data[1];
	}
	RIFF;

	//
	// .WAV PCM file format chunk
	//

	typedef struct
	{
   		char  FMT_string[4];
   		ULong chunk_size;

   		SWord  format_tag;
   		SWord  channels;
   		SLong  sample_rate;
   		SLong  average_data_rate;
   		SWord  alignment;
   		SWord  bits_per_sample;
	}
	FMT;

	//
	// .WAV file data chunk
	//

	typedef struct
	{
   		char  DATA_string[4];
   		ULong chunk_size;
   		UByte data[1];
	}
	DATA;

//DeadCode RJS 16Oct97 	struct SampleRec
//DeadCode RJS 16Oct97 	{
//DeadCode RJS 16Oct97 		fileblock	*blockptr;
//DeadCode RJS 16Oct97 		SLong		size;
//DeadCode RJS 16Oct97 		int			priority;
//DeadCode RJS 16Oct97 		UWord		samplerate;									//RJS 16Oct97
//DeadCode RJS 16Oct97 		UWord		samplevolume;								//RJS 16Oct97
//DeadCode RJS 16Oct97 		ULong		LastTime;									//RJS 16Oct97
//DeadCode RJS 16Oct97 	};


	struct StatusRec
	{
		int		nohandlers;
		int		nosamples;
		int		notunes;
		int		errorno;
		char	errorstring[80];
	};

struct	EnginePlayInfo
{
	UByte	Dying:1,
			Playing:1,
			Dead:1,
			IsJet:1,											//RJS 19May98
			InCockpit:1,									//RJS 09Apr99
			Changed:1,										//RJS 09Apr99
			isInitialised:1;									//RJS 25May99

	SLong	RumbleVolume;										//RJS 26Jun98
	SLong	Volume;
	SLong	SubHarmonicVolume;
	SLong	WindVolume;
	FileNum	CurrentSubFile;										//RJS 26Jun98
	FileNum	CurrentFile;
	FileNum	OldFile;

	SLong	Freq;
	SLong	SubHarmonicFreq;

	SLong	OverRevving;
	SLong	OverRevFreq;

	PlayingRec*	ChanPtr;
	PlayingRec*	SubChanPtr;
	SLong	CockpitWind;										//RJS 19May98
	SLong	VolLoaded;											//RJS 18Jan99
};



#endif

