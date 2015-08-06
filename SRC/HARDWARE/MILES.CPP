/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       miles.cpp
//System         
//Author         Robert Slater
//Date           Wed 21 Feb 1996
//Description    MIDI and sound sample library functions
//				Engine sound is at sample queue position 0,
//				Machine gun sound is at sample queue position 1
//------------------------------------------------------------------------------

//TEMPCODE JIM 27/07/99 #define		_NO_MILES_AUDIO_

#include 	"dosdefs.h"

#include	<stdlib.h>											//RJS 19Jul96
#include 	<string.h>
#include	"mssw.h"											//RJS 19May98
#define 	F_GRAFIX
#include	"files.g"
#include	"fileman.h"
#include	"worldinc.h"
#include	"miles.h"
#include	"rchatxtr.h"										//RJS 10Jun98
#include	"milesxtr.h"
#include	"smack.h"
#include	"planetyp.h"
#include	"worldinc.h"
#include	"Mytime.h"											//PD 15Mar96
#include	"mymath.h"
//TempCode DAW 17Nov97 #include	<i86.h>												//JIM 05Jul96
#include	<string.h>
#include	"hardpasm.h"										//RJS 22Jul96
#include	"viewsel.h"											//RJS 02Sep96
#include	"savegame.h"										//RJS 02Sep96
#include	<stdio.h>											//RJS 25Nov96
#include	"monotxt.h"											//RJS 09Mar98
#include	"sndfonts.h"										//RJS 03Jul98
#include	"flymodel.h"
#include "modvec.h"
#include "Model.h"
#include	"analogue.h"
#include "stub3d.h"
#include	"replay.h"

#define		MEMORY_MIN	40000000				//32 meg
#define		MIDI_NOTE_ON	0x90
#define		NOTE_ROOT		60

MINMAX	(MTC,0,25) mtc=MTCMIN;
MTC	operator ++(MTC& m)
	{m=(MTC)((m+1)%MTCMAX);return(m);}
int		boffcount;
static MilesBase Blank={FALSE};												//RJS 05Dec96
Miles _Miles;											//JIM 13Dec96
CON Miles::Miles() {MilesBase::operator=(Blank);theblock=NULL;trySoundFonts=false;}

//DEADCODE DAW 28/03/99 TimerCode Timer_Code;											//PD 15Mar96

 		SequenceStruct	Miles::tune[Miles::MAXTUNES];
 		MusicRequest	Miles::request;
		SampleLibrary	Miles::wavetable;
		SampleRec*		Miles::thesample;						//MS 23Sep98
		PlayingRec		Miles::soundqueue[Miles::MAXHANDLERS];
		StatusRec		Miles::status;
		SampleRequest	Miles::soundtoplay;
		HTIMER			Miles::timer;
	 	MDI_DRIVER*		Miles::mdi;
		DIG_DRIVER*		Miles::dig;
		EnginePlayInfo	Miles::EngineSound;						//RJS 21Oct97
	 	MDI_DRIVER*		Miles::dls;								//RJS 18May98
		Bool			Miles::canplaynothing;					//RJS 21May98
		Bool			Miles::critical;						//RJS 21May98
		Bool			Miles::inprefs;							//RJS 21May98
		Bool			Miles::onground;						//RJS 21May98
		Bool			Miles::musicstopped;					//RJS 21May98
		int				Miles::damagelevel;						//RJS 21May98
		int				Miles::delindex;						//RJS 21May98
		int				Miles::thesmackervol;					//RJS 21May98
		FileNum			Miles::currentengine;					//RJS 21May98
		int				Miles::bouncecount;						//RJS 21May98
		SLong			Miles::MAXSAMPLES_LOADED;				//MS 23Sep98
		SampleRec*		Miles::themusicsample;					//RJS 14Apr99
		SLong			Miles::percvolscale;					//RJS 29Jun99
		PercRec			Miles::percussionLog;					//RJS 18Aug99






//#pragma off (check_stack);
#ifdef	__DOS__
		#define	AILEXPORT cdecl
		char*	AIL_last_error()	{return AIL_error;}
#endif

int	NCIndex(char*	s,char*	t)									//RJS 21Sep99
{
	int	i, j, k;

	for(i=0;s[i]!='\0';i++)
	{
		for(j=i,k=0;t[k]!='\0' && toupper(s[j])==toupper(t[k]);j++,k++);
			if(t[k]=='\0')
				return(i);
	}
	return(-1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		mainbeatint
//Author		Robert Slater
//Date			Thu 26 Feb 1998
//
//Description	Processes all the main music interrupt requests...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	__stdcall	Miles::mainbeatint(HSEQUENCE callerseq, SLong	channel, SLong	value)
{
  	if (request.activated)
 	{
//DeadCode RJS 18Jun99  		if (request.stopsequence)
 		if (request.activated & INT_STOPSEQUENCE)
 		{
			if (AIL_sequence_volume(callerseq) == 0)
			{
//DeadCode RJS 18Jun99 				request.activated = FALSE;
				request.activated &= ~INT_STOPSEQUENCE;
//DeadCode RJS 18Jun99 				request.stopsequence = FALSE;
				request.mainstopped = TRUE;
				request.killnow = TRUE;
//DeadCode RJS 18Jun99 
//DeadCode RJS 18Jun99 				Mono_Text.PrintAt(50,10,(UByteP)"  ...stopped...  ");
			}
 		}
 		else
 		{
 			SLong	code, track;
 
 			code = value / 10;
 			track = value - (code * 10);
 
 			if (code < CODE_STANDALONE)
 			{
 				SLong	newcode;
//DeadCode RJS 18Jun99  				if (request.direction)
 				if (request.activated & INT_DIRECTION)
 				{
 					// We can weave around through the tracks...
 					SLong	tunedelta = request.CurrentTrack - track;
 
 					newcode = code;
 
 					if (tunedelta > 0)
 						newcode += 4;
 					else
 					{
 						if (tunedelta < 0)
 							newcode += 7;
  						else
  						{
							//Drunken walk...
							ULong	drunkenwalk = Math_Lib.rnd();
  							if (drunkenwalk < 21845)
								newcode += 7;				//go backwards
							else
							{
								if (drunkenwalk > 43690)
									newcode += 4;			//go forwards
							}
   						}
 					}
 			
 					if (code == CODE_JUMP3)
 						newcode -= 3;
 
 					newcode = (newcode * 10) + track;
 				}
 				else
 				{
 					// We can jump straight to a new track...
//DeadCode RJS 18Jun99 					request.direction = TRUE;
	 				request.activated |= INT_DIRECTION;			//RJS 18Jun99
 					newcode = 10 + request.CurrentTrack;
//DeadCode RJS 18Jun99 //Dead 					request.activated = FALSE;
 				}
 
 				AIL_branch_index(callerseq,newcode);
 			}
 			else
 			{
 				switch (code)
 				{
 				case CODE_STANDALONE:
 				{
 					if (request.alonetuneno)
 					{
 						AIL_set_sequence_volume(callerseq, 0, 100);
						request.activated &= ~INT_STOPSEQUENCE;
//DeadCode RJS 18Jun99  						request.stopsequence = TRUE;
 					}
 
 					break;
 				}
 				case CODE_SFX:
 				{
 					switch (track)
 					{
 					case CODE_SFX_VOL:
 						// Set sfx volume...
 						break;
 					case CODE_SFX_PAN:
 						// Set sfx pan...
 						break;
 					case CODE_SFX_BAR:
 						// Hmmmm...
 						break;
 					}
 
 					break;
 				}
 				case CODE_SPECIAL:
 				{
					request.activated &= ~INT_DIRECTION;
//DeadCode RJS 18Jun99  					request.direction = FALSE;
 					switch (value)
 					{
 					case CODE_HIPRIORITY:
 						break;
 					case CODE_LOPRIORITY:
 						break;
 					case CODE_STOP:
 						break;
 					}
 
 					break;
 				}
 				}
 			}

//DeadCode RJS 18Jun99 			if (request.fader)
			if (request.activated & INT_FADER)
			{
				request.activated &= ~INT_FADER;
//DeadCode RJS 18Jun99 				request.fader = FALSE;
				AIL_set_sequence_volume(callerseq,request.NewVolume,request.NewFade);
			}
 		}
 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MIDIEventInterrupt
//Author		Robert Slater
//Date			Wed 14 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	__stdcall	Miles::MIDIEventInterrupt(HMDIDRIVER midi,HSEQUENCE callerseq,SLong	status, SLong	value1, SLong value2)
{
	if ((status & 0x0f)==14)		//is this channel 15 (percussion)?...
	{
		//what is this midi event?
		if ((status & 0xf0)==MIDI_NOTE_ON)
		{
			if (dig)
			{
				value1 -= NOTE_ROOT;
				if ((value1 < _Miles.nomusicsamples) && themusicsample[value1].blockptr)
				{
					percussionLog.sampleindex = value1;			//DAW 18Aug99
					percussionLog.volume = value2;				//DAW 18Aug99
//DeadCode DAW 18Aug99 					HSAMPLE		handler;
//DeadCode DAW 18Aug99 					void		*address = getdata(themusicsample[value1].blockptr);
//DeadCode DAW 18Aug99 					SQueuePtr	ChannelPtr = &_Miles.soundqueue[_Miles.channel_percussion];
//DeadCode DAW 18Aug99 
//DeadCode DAW 18Aug99 					handler = ChannelPtr->handler;
//DeadCode DAW 18Aug99 					if (ChannelPtr->sampleindex)
//DeadCode DAW 18Aug99 					{
//DeadCode DAW 18Aug99 						if (AIL_sample_status(handler)!=SMP_DONE)
//DeadCode DAW 18Aug99 							AIL_end_sample(handler);
//DeadCode DAW 18Aug99 					}
//DeadCode DAW 18Aug99 
//DeadCode DAW 18Aug99 					ChannelPtr->sampleindex = &themusicsample[value1];
//DeadCode DAW 18Aug99 
//DeadCode DAW 18Aug99 					AIL_init_sample(handler);
//DeadCode DAW 18Aug99 				 	if (AIL_set_sample_file(handler,address,-1))
//DeadCode DAW 18Aug99 					{
//DeadCode DAW 18Aug99 						//Balance the percussion volume between 3d sample and music volume...
//DeadCode DAW 18Aug99 						value2 *= percvolscale;						//RJS 29Jun99
//DeadCode DAW 18Aug99 						value2 >>= 8;
//DeadCode DAW 18Aug99 
//DeadCode DAW 18Aug99 						AIL_set_sample_volume(handler, value2);
//DeadCode DAW 18Aug99 						AIL_start_sample(handler);
//DeadCode DAW 18Aug99 					}
				}
			}
			return 1;	//disable midi event
		}
	}

	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		subbeatint
//Author		Robert Slater
//Date			Thu 22 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::subbeatint(HSEQUENCE callerseq, SLong	channel, SLong	value)
{
	if (!request.activated)
		return;
}		

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		mainendint
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	__stdcall Miles::mainendint(HSEQUENCE callerseq)
{
	if (!request.activated)
		return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		subendint
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::subendint(HSEQUENCE callerseq)
{
	if (!request.activated)
		return;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		timerint
//Author		Robert Slater
//Date			Thu 29 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	cdecl	Miles::timerint(ULONG	user)
{
	#ifdef	__DOS__

//TempCode PD 12Nov96 	((UByte*) 0xb0000)[(Timer_Code.tus+Timer_Code.tus)&4095]=Timer_Code.Quit3DTimer;

	if (!*(char*)0x4f4)
		Timer_Code.tus++;											//JIM 02Apr96
	#endif
}

//#pragma on (check_stack);
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartUpMiles
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Set up midi and digital samples system	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
extern	void*	ailmalloc(size_t);
extern	void	ailfree(void*);
void	Miles::StartUpMiles(ULong	thiswin)					//RJS 19May98
{
#ifdef _NO_MILES_AUDIO_
	mdi = NULL;
	dig = NULL;
	timer = NULL;
	dls = NULL;
	Save_Data.vol.sfx = Save_Data.vol.music = Save_Data.vol.uisfx = 0;//RJS 12Mar99
#else
	int			tuneno;											//RJS 13Mar98
//Dead	int 		count;											//RJS 13Mar98
	char		*filename;										//RJS 13Mar98
	char		inifilename[80];								//RJS 13Mar98
	char		found;											//RJS 13Mar98
	void		*tmpaddress;									//RJS 29Aug96
	int			size;											//RJS 29Aug96
	SLong		result;											//RJS 29Aug96
	fileblock	*theblock;										//RJS 29Aug96
	int			sequenceno;										//RJS 30Aug96
//Rob	UINT		uDriverID;										//RJS 03Apr97
	MMRESULT	midiRes;										//RJS 03Apr97
	MIDIOUTCAPS midiOutCaps;									//RJS 03Apr97
	SLong		ndevs;
	SLong		driverid;
	LPHMIDIOUT	midiOutDev;
//Rob	SLong		bestDrivers[16];
	ULong		bestCnt = 3;

	if (mdi || dig || timer || dls)								//RJS 18May98
		return;

	HWND	newwin = (HWND) thiswin;							//RJS 13Mar98
	View_Point=NULL;											//RJS 13Mar98
	midiOutDev=NULL;

	delayedstate = false;
																//RJS 13Mar98
	SLong	initval = AIL_startup();							//RJS 13Mar98

	for (bestCnt=0; bestCnt < 16; bestCnt++)
		bestDrivers[bestCnt] = -1;

	bestCnt = 3;

	mdi = NULL;
 	Save_Data.vol.anim = thesmackervol = 64;
	uDriverID = MIDI_MAPPER;

	ndevs = midiOutGetNumDevs();
	for (driverid = 0; driverid < ndevs; driverid++)
	{
		midiRes = midiOutGetDevCaps((ULong)driverid, &midiOutCaps, sizeof (MIDIOUTCAPS));
		switch (midiOutCaps.wTechnology)
		{
		case MOD_MAPPER:
			// Sound Font is the 1st choice...
			if (NCIndex(midiOutCaps.szPname,"SoundFont") != -1)
				bestDrivers[0] = driverid;
			else
				bestDrivers[bestCnt++] = driverid;
//DeadCode DAW 21Sep99 			if (strncmp(midiOutCaps.szPname,"SoundFont",9) == 0)
//DeadCode DAW 21Sep99 				bestDrivers[0] = driverid;
			break;
		case MOD_SYNTH:
			//Internal synthesizer...
			if (bestDrivers[1] == -1)							//RJS 21Sep99
			{
				if (	(NCIndex(midiOutCaps.szPname,"Wave") != -1)
					||	(NCIndex(midiOutCaps.szPname,"Software") != -1)
					||	(NCIndex(midiOutCaps.szPname,"S/W") != -1)	)
 					bestDrivers[bestCnt++] = driverid;
				else
 					bestDrivers[1] = driverid;
			}
			else
 				bestDrivers[bestCnt++] = driverid;
//DeadCode DAW 21Sep99 			if (	(bestDrivers[1] != -1)
//DeadCode DAW 21Sep99 				&&	(strncmp(midiOutCaps.szPname,"WaveSynth",9)==0))
//DeadCode DAW 21Sep99 				bestDrivers[bestCnt++] = driverid;
//DeadCode DAW 21Sep99 			else
//DeadCode DAW 21Sep99 				bestDrivers[1] = driverid;
			break;
		case MOD_FMSYNTH:
			bestDrivers[2] = driverid;
			break;
		case MOD_SQSYNTH:
			bestDrivers[bestCnt++] = driverid;
			break;
		case MOD_MIDIPORT:
			// not supported...
			break;
		}
	}

	//Just in case...
	MusicDir = FIL_DIR_MUSICMED-FIL_DIR_MUSIC;					//RJS 21Sep99

	havePercussion = false;										//RJS 14Apr99
	for (driverid = 0; driverid < bestCnt; driverid++)
	{
		if (bestDrivers[driverid] > -1)
		{
			switch (driverid)
			{
			case 0:
				MusicDir = 0;
				break;
			case 1:
				MusicDir = FIL_DIR_MUSICMED-FIL_DIR_MUSIC;
				break;
			default:
				MusicDir = FIL_DIR_MUSICLOW-FIL_DIR_MUSIC;
				havePercussion = true;							//RJS 14Apr99
				break;
			}

			break;
		}
	}

	uDriverID = (ULong) bestDrivers[driverid];
	if (AIL_midiOutOpen (&mdi, &midiOutDev, uDriverID))				//RJS 03Jul98
	{
		mdi = NULL;
		Save_Data.vol.music = 0;
	}
	else
	{
		if (MusicDir == 0)
			trySoundFonts = true;

		if (mdi == NULL)
			Save_Data.vol.music = 0;
	}

	pooMidiDev = (void*) midiOutDev;
/*	if (midiRes != MMSYSERR_NOERROR)
	{

		if (midiRes == MMSYSERR_BADDEVICEID)
			MessageBox (NULL, "The specified device identifier is out of range.", "MIDI", MB_OK);

		else if (midiRes == MMSYSERR_INVALPARAM)
			MessageBox (NULL, "The specified pointer or structure is invalid.", "MIDI", MB_OK);

		else if (midiRes == MMSYSERR_NODRIVER)
			MessageBox (NULL, "The driver is not installed.", "MIDI", MB_OK);

		else if (midiRes == MMSYSERR_NOMEM)
			MessageBox (NULL, "The system is unable to load mapper string description.", "MIDI", MB_OK);

		else
			MessageBox (NULL, "No MIDI Card?", "MIDI", MB_OK);
	}*/

	wavetable.blockptr = NULL;
	wavetable.wavesynth = NULL;								//RJS 18May98
	wavetable.DLSwavesynth = NULL;

	for (tuneno = 0; tuneno < MAXTUNES; tuneno++)				//RJS 30Aug96
	{
		tune[tuneno].blockptr = NULL;
		tune[tuneno].dlsID = NULL;
		tune[tuneno].dlsPtr = NULL;
		tune[tuneno].xmiPtr = NULL;

		for (sequenceno = 0; sequenceno < MAXSEQUENCES; sequenceno++)
		{
			tune[tuneno].sequence[sequenceno] = NULL;
			tune[tuneno].DLSsequence[sequenceno] = NULL;		//RJS 19May98
		}
	}

	status.nosamples = 0;

//DeadCode DAW 06Apr99 	if (NewDigitalDriver(MIN_SAMP_VAL,MAXHANDLERS))				//RJS 17Oct97
//DeadCode DAW 06Apr99 	{
//DeadCode DAW 06Apr99 		SLong	rval = AIL_set_DirectSound_HWND(dig,newwin);
//DeadCode DAW 06Apr99 		EngineSound.ChanPtr = &soundqueue[0];							//RJS 17Oct97
//DeadCode DAW 06Apr99 		EngineSound.SubChanPtr = &soundqueue[1];						//RJS 26Jun98
//DeadCode DAW 06Apr99 
//DeadCode RJS 08Sep98 		Save_Data.vol.sfx = 64;					//Crap fix, cos everything is crap
//DeadCode RJS 08Sep98 //		Save_Data.vol.sfx = 0;					//Crap fix, cos everything is crap
//DeadCode RJS 08Sep98 		AIL_set_digital_master_volume(dig,127);	//RJS 27Feb98
//DeadCode DAW 06Apr99 	}
//DeadCode DAW 06Apr99 	else														//RJS 17Oct97
//DeadCode DAW 06Apr99 	{
//DeadCode DAW 06Apr99 		EngineSound.ChanPtr = NULL;									//RJS 17Oct97
//DeadCode DAW 06Apr99 		EngineSound.SubChanPtr = NULL;								//RJS 26Jun98
//DeadCode DAW 06Apr99 	}

	if (InitUI(thiswin))										//DAW 06Apr99
	{															//DAW 06Apr99
		EngineSound.ChanPtr = &soundqueue[0];					//DAW 06Apr99
		EngineSound.SubChanPtr = &soundqueue[1];				//DAW 06Apr99
	}															//DAW 06Apr99
	else														//DAW 06Apr99
	{															//DAW 06Apr99
		EngineSound.ChanPtr = NULL;								//DAW 06Apr99
		EngineSound.SubChanPtr = NULL;							//DAW 06Apr99
	}															//DAW 06Apr99
#endif
//DeadCode MS 23Sep98 	// Reset all samples...
//DeadCode MS 23Sep98 
//DeadCode MS 23Sep98 	for (count = 0; count < MAXSAMPLES; count ++)
//DeadCode MS 23Sep98 		thesample[count].blockptr = NULL;

	MAXSAMPLES_LOADED = 0;										//MS 23Sep98
	thesample = NULL;											//MS 23Sep98
	themusicsample = NULL;										//RJS 14Apr99
	nomusicsamples = 0;											//RJS 14Apr99

	status.notunes = 0;

	// Timer ???? (not needed for 3D!)

	timer = NULL;

	// Initialise callback values...

	ResetMidiFlags();											//RJS 29Aug96

	canplaynothing = FALSE;

//	EngineSound.Volume = 7800;									//RJS 21Oct97
	EngineSound.Volume = 30000;									//RJS 21Oct97
	musicstopped = FALSE;										//RJS 22Aug96

	ResetSoundFlags();											//RJS 22Aug96
	EngineSound.VolLoaded = 0;									//RJS 18Jan99

	GetSampleVolumes();											//RJS 03Apr97
																//MS 23Sep98
	// Reset all samples...										//MS 23Sep98
	for (int	count = 0; count < MAXSAMPLES_LOADED; count ++)		//MS 23Sep98
		thesample[count].blockptr = NULL;						//MS 23Sep98

 	allowedsamples = status.nohandlers / 3;						//RJS 17Nov98

	donePreLoad = false;		//RJS 01Apr99
	shootTimer = 0;

	donePreLoadRadio = false;									//RJS 17May99
	randomFAC = randomTOWER = 0;								//RJS 17May99

	percvolscale = 256;											//RJS 29Jun99
	rchatter_allowed = true;									//RJS 16Aug99
//
//DeadCode RJS 08Sep98 	SavedMusic = Save_Data.vol.music;
//DeadCode RJS 08Sep98 	SavedSfx = Save_Data.vol.sfx;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDigitalDriver
//Author		Robert Slater
//Date			Mon 18 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::NewDigitalDriver(HSampRate	srate,int	nohandlers,Bool	usemono)
{
	int 		count;
	char		*filename;
	char		inifilename[80];
	char		found;
	void		*tmpaddress;									
	int			size;											
	SLong		result;			
	Bool		ok;
	static PCMWAVEFORMAT PCM_waveformat;

	ok = FALSE;

	if (dig)
	{
		// Free everything...

		for (count = 0; count < status.nohandlers; count ++)
		{
			AIL_release_sample_handle(soundqueue[count].handler);
			soundqueue[count].handler = NULL;
		}

		AIL_waveOutClose(dig);
	}

	// Setup Digital Sounds

	WORD	chans;
	DWORD	rate;
	WORD	bits;

	if (usemono)												//DAW 15Dec96
		chans = 1;												//DAW 15Dec96
	else														//DAW 15Dec96
		chans = 2;												//DAW 15Dec96

	rate = (DWORD) srate;
 	bits = 16;

	PCM_waveformat.wf.wFormatTag = WAVE_FORMAT_PCM;
	PCM_waveformat.wf.nChannels = chans;
	PCM_waveformat.wf.nSamplesPerSec = rate;
	PCM_waveformat.wf.nAvgBytesPerSec = rate * (bits / 8) * chans;
	PCM_waveformat.wf.nBlockAlign = (bits /8) * chans;
	PCM_waveformat.wBitsPerSample = bits;

	dig = NULL;

	if (AIL_waveOutOpen ( &dig, NULL, WAVE_MAPPER, (LPWAVEFORMAT)&PCM_waveformat) != 0)
	{
		digerror=AIL_last_error();
		dig = NULL;
		Save_Data.vol.sfx = 0;
		Save_Data.vol.rchat = 0;
	}

//	if (usemono)											//DAW 15Dec96
//		SmackSoundUseMSS (dig);

	if (dig)
	{
//DeadCode RJS 03Jul98 		InstallWaveTable(FIL_MUSIC_WAVETABLE);						//RJS 18May98

		// Initialise as many sound driver handlers as we can

		for (count = 0; count < nohandlers; count ++)
		{
			soundqueue[count].handler = AIL_allocate_sample_handle(dig);
			if (soundqueue[count].handler)
				AIL_init_sample(soundqueue[count].handler);		//DAW 28Nov96
 			soundqueue[count].GameSound = FALSE;
			soundqueue[count].worlditem = NULL;
			soundqueue[count].looping = FALSE;
			soundqueue[count].sampleindex = NULL;					//RJS 03Oct96

			if (soundqueue[count].handler == NULL)
			{
				// We have all the handers we can get, so exit
				break;
			}
		}

		status.nohandlers = count;

		if (status.nohandlers || status.nohandlers ==nohandlers)						//JIM 18Dec96
			ok = TRUE;
	}
	else
	{
		Save_Data.vol.sfx = 0;
		Save_Data.vol.uisfx = 0;								//RJS 12Mar99
	}

	playerShooting = false;										//RJS 12Apr99

	return(ok);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TuneInRange
//Author		Robert Slater
//Date			Thu 29 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::TuneInRange(int	tuneno)
{
	if (	(tuneno < 0)
		||	(tuneno >= MAXTUNES)	)
		return(FALSE);

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceInRange
//Author		Robert Slater
//Date			Mon 25 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::SequenceInRange(TuneStrucP	TunePtr, int	seqno)
{
	if (	(seqno < 0)											//RJS 26Feb98
		||	(seqno >= TunePtr->nosequences)	)					//RJS 26Feb98
		return(FALSE);											//RJS 26Feb98
																//RJS 26Feb98
	return(TRUE);												//RJS 26Feb98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleInRange
//Author		Robert Slater
//Date			Mon 25 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::SampleInRange(int	sampleno)
{
	if (	(sampleno < 0)
		||	(sampleno >= MAXSAMPLES_LOADED)	)
		return(FALSE);

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandlerInRange
//Author		Robert Slater
//Date			Mon 25 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::HandlerInRange(int	qpos)
{
	if ((qpos > -1) && (qpos < status.nohandlers))				//RJS 19Nov96
		return(TRUE);											//RJS 19Nov96

	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitTune
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Initialises all the sequences in a tune
//			
//
//Inputs				
//
//Returns		
//	
//------------------------------------------------------------------------------
void	Miles::InitTune(TuneStrucP	TunePtr)
{
/*	HSEQUENCE	seqhandle;
	int			sequenceno;
	SLong		result;
	Bool		anerror = FALSE;
	int			combatbase = GetIndex(FIL_MUSIC_MAIN);

	request.activated = FALSE;
	
	// Set up all the sequences in the tune...
	for (sequenceno = 0; sequenceno < TunePtr->nosequences; sequenceno ++)
	{

		seqhandle = TunePtr->sequence[sequenceno];
		result = AIL_init_sequence(seqhandle, TunePtr->xmiPtr, sequenceno);//RJS 19May98
		if (result == 0	)
		{
			// The sequence could not be found.
			//
			//	If the result was -1, then a certain timbre was not found,
			//	but we can ignore this...


			AIL_shutdown();
			
			_Error.EmitSysErr(AIL_last_error());

		}
		else
			AIL_set_sequence_volume(seqhandle,0,0);

		seqhandle = TunePtr->DLSsequence[sequenceno];
		if (seqhandle)
		{
			if (AIL_init_sequence(seqhandle, TunePtr->dlsPtr, sequenceno) == 0)//RJS 02Jul98
			{
				AIL_shutdown();
				_Error.EmitSysErr(AIL_last_error());
			}
			else
				AIL_set_sequence_volume(seqhandle,0,0);
		}
	}

//DeadCode RJS 02Jul98 	if (TunePtr == &tune[combatbase])
//DeadCode RJS 02Jul98 	{
//DeadCode RJS 02Jul98 		// Set up callbacks for main track....
//DeadCode RJS 02Jul98 
//DeadCode RJS 02Jul98 		AIL_register_trigger_callback(TunePtr->sequence[0],mainbeatint);
//DeadCode RJS 02Jul98 		AIL_register_sequence_callback(TunePtr->sequence[0],mainendint);
//DeadCode RJS 02Jul98 	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartMain
//Author		Robert Slater
//Date			Thu 29 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::StartMain(SLong	vol)
{
	int		sequenceno;
	int		tuneno;
	int		nosequences;
	ULong	status, channelno;									//RJS 30Sep96
	int		combatbase = GetIndex(FIL_MUSIC_MAIN);				//RJS 02Jul98

	if ((Save_Data.vol.music != 0) && !incombat)					//RJS 25Jun98
	{
		if (tune[combatbase].sequence[0])						//RJS 02Jul98
		{
 			if (AIL_sequence_status(tune[0].sequence[0]) == SEQ_PLAYING)
				return FALSE;
		}

		TuneStrucP	TunePtr = LoadTune(FIL_MUSIC_MAIN);					//RJS 18May98
		if (TunePtr && TunePtr->blockptr && !request.activated)
		{
			HSEQUENCE	thishandle;

//Dead			request.activated = FALSE;
//Dead			request.fader = FALSE;
//Dead 			request.stopsequence = FALSE;
			request.wait = FALSE;
			request.todiscard = FALSE;
			request.killnow = FALSE;
			incombat = TRUE;											//RJS 06Jan97
			request.mainstopped = FALSE;								//RJS 06Jan97
			request.alonetuneno = NULL;									//RJS 26Feb98
			request.forcestop = 0;										//RJS 18Jun99

			// Clip the volume if out of range...

			vol = ClipVolume(127,vol);

			AIL_lock();

			// Launch xmidi and dls sequences simultaneously
			thishandle = TunePtr->sequence[0];				
			if (AIL_init_sequence(thishandle,TunePtr->xmiPtr,0) != 0)//RJS 02Jul98
			{
				AIL_register_trigger_callback(thishandle,mainbeatint);
				AIL_start_sequence(thishandle);
				AIL_set_sequence_volume(thishandle,vol,0);

//DeadCode RJS 18Jun99 				Mono_Text.PrintAt(50,10,(UByteP)"Main started...");

				if (TunePtr->DLSsequence[0])
				{
					thishandle = TunePtr->DLSsequence[0];
					if (AIL_init_sequence(thishandle,TunePtr->dlsPtr,0) != 0)
						AIL_start_sequence(thishandle);
					else
					{
						AIL_shutdown();
				   		_Error.EmitSysErr("Cannot initialise DLS sequence!\n");
					}
				}
			}
			else
			{
				AIL_shutdown();
			   _Error.EmitSysErr("Cannot initialise XMIDI sequence!\n");
			}

			AIL_unlock();
		}
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopMain
//Author		Robert Slater
//Date			Tue 12 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopMain()
{
	int	count;

	if (	(Save_Data.vol.music == 0)
		||	(incombat == FALSE)			
		||	(request.mainstopped == TRUE)		)
		return;

	request.activated = INT_NULL;

	for (count = 0; count < 4; count++)
	{
		if (tune[count].blockptr)
	 		AIL_set_sequence_volume(tune[count].sequence[0],0,3000);
	}

//Dead	request.stopsequence = TRUE;
	request.activated |= INT_STOPSEQUENCE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiscardMusic
//Author		Robert Slater
//Date			Thu 29 Aug 1996
//
//Description	Throws away all the main music stuff
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::DiscardMusic(TuneStrucP	exception)
{
	int			endtune = GetIndex(FIL_MUSIC_LAST_TUNE);
	int			tuneno;
	int			nosequences;
	int			sequenceno;
	Bool		specialcase = FALSE;
	HSEQUENCE	tmphandle;
	TuneStrucP	TunePtr;
	HSEQUENCE	basehandle = tune[GetIndex(FIL_MUSIC_MAIN)].sequence[0];//RJS 26Jun98

	if (!mdi)													//RJS 03Dec96
		return;													//RJS 03Dec96

//Dead	request.activated = FALSE;
	request.activated = INT_NULL;
	incombat = FALSE;											//RJS 12Nov96

	for (tuneno = 0; tuneno < endtune; tuneno++)
	{
		TunePtr = &tune[tuneno];

		if (TunePtr == exception)
			specialcase = TRUE;
		else
			specialcase = FALSE;

		if (TunePtr->blockptr)
		{
			nosequences = TunePtr->nosequences;
			tmphandle = TunePtr->sequence[0];

			if (tmphandle)
			{
				AIL_end_sequence(tmphandle);

				if (tmphandle != basehandle)
				{
					AIL_release_sequence_handle(tmphandle);
					for (sequenceno = 0; sequenceno < nosequences; sequenceno ++)
						TunePtr->sequence[sequenceno] = NULL;
				}
			}

			if (!specialcase)
			{
				delete TunePtr->blockptr;

				TunePtr->blockptr = NULL;
			}
		}
	}

	request.killnow = FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetIndex
//Author		Robert Slater
//Date			Fri 8 Mar 1996
//
//Description	Calculates the index no of a file
//
//Inputs		The file number
//
//Returns		The file index
//
//------------------------------------------------------------------------------
int	Miles::GetIndex(FileNum	thefile)
{
	return((thefile & FILENUMMASK) - 1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadTune
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Gets a new tune and initialises it
//
//Inputs		Filename
//
//Returns		TRUE  if success
//				FALSE otherwise
//
//------------------------------------------------------------------------------
TuneStrucP	Miles::LoadTune(FileNum	thefile)
{
	SLong		result, size;
	void		*tmpptr;
	SLong		*headptr;
	int			count;
	UWord		noforms = 0;
	SLong		header;
	fileblock	*theblock;
	int			tuneno = GetIndex(thefile);
	TuneType	ttype;
	HSEQUENCE	tmphandle = NULL;
	TuneStrucP	TunePtr = NULL;									//RJS 26Feb98
																//RJS 26Feb98
	if (Save_Data.vol.music && TuneInRange(tuneno))				//RJS 26Feb98
	{															//RJS 26Feb98
		TunePtr = &tune[tuneno];								//RJS 26Feb98
		if (TunePtr->blockptr == NULL)							//RJS 26Feb98
		{
			if (tuneno < GetIndex(FIL_MUSIC_STAND_ALONE))			//RJS 18May98
				ttype = T_main;									//RJS 18May98
			else												//RJS 18May98
			{													//RJS 06May99

				if (tuneno < GetIndex(FIL_MUSIC_PRIORITY))		//RJS 06May99
					ttype = T_independent;						//RJS 06May99
				else											//RJS 06May99
					ttype = T_independent_pri;					//RJS 06May99

			}

			// All clear, so load the sequences file...
			thefile=(FileNum)(thefile+MusicDir);
	
			theblock = new fileblock (thefile);
			if (theblock)
			{
				tmpptr = getdata(theblock);

				size = getsize(theblock);

				TunePtr->blockptr = theblock;						//RJS 18May98
				TunePtr->size = size;								//RJS 18May98
				TunePtr->ttype = ttype;
				status.notunes = status.notunes + 1;

				headptr = (SLong*) tmpptr;

				SLong	ftype = AIL_file_type((void*)headptr,size);
				switch (ftype)
				{
					case AILFILETYPE_XMIDI:
					case AILFILETYPE_XMIDI_DLS:
						SetUncompressedDLS(TunePtr,tmpptr,size);
						break;
					case AILFILETYPE_XMIDI_MLS:
						SetCompressedDLS(TunePtr,tmpptr,size);
						break;
				}

				SetXMidi(TunePtr);
				SetDLS(TunePtr);
			}

//			if (TunePtr->ttype == T_main)
//			{
//				InitTune(TunePtr);
//				AIL_register_trigger_callback(TunePtr->sequence[0],mainbeatint);
//			}
		}
	}

	return(TunePtr);											//RJS 26Feb98
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InstallWaveTable
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	
//
//Inputs		Digital waveform table filename		
//
//Returns		
//
//------------------------------------------------------------------------------
void	Miles::InstallWaveTable(FileNum	thefile,Bool	useDLS)
{
 	if (dig && mdi)												//RJS 18May98
 	{
		if (useDLS)
		{
			if (!dls)
			{
			 	if (AIL_midiOutOpen ( &dls, NULL, MIDI_NULL_DRIVER))
					dls = NULL;
			}

			// DLS_dll_name is NULL for software, or "S3BASE.DLL" for SonicVibes...

//			AIL_set_preference(DLS_ENABLE_GLOBAL_REVERB,	YES);
//			AIL_set_preference(DLS_ENABLE_FILTERING,	NO);

			if (wavetable.DLSwavesynth)
  			  	AIL_DLS_close(wavetable.DLSwavesynth,RETURN_TO_GM_ONLY_STATE);

			wavetable.DLSwavesynth = AIL_DLS_open(	dls,
													dig,
													NULL,				// DLS_dll_name
													0,
													NOM_SAMP_VAL,
													16,
													1					// mono
										  		  );					//RJS 18May98

			if (wavetable.DLSwavesynth == 0)
			{
				AIL_midiOutClose(dls);
				dls = NULL;
			}
		}
		else
		{
			void		*tmpptr;
		 	SLong		size, result;
		 	fileblock	*theblock;

			if (wavetable.blockptr == NULL)
			{
				theblock = new fileblock (thefile);
				if (theblock)
				{
	 				size = getsize(theblock);

					wavetable.blockptr = theblock;
		 			wavetable.size = size;
				}
			}

			if (wavetable.blockptr)
			{
	 			tmpptr = getdata(theblock);
 				size = wavetable.size;

				if (wavetable.wavesynth)
					AIL_destroy_wave_synthesizer(wavetable.wavesynth);

 				wavetable.wavesynth = AIL_create_wave_synthesizer(	dig,
																	mdi,
																	tmpptr,
																	2);
			}
		}
	}
	else
	{
		dls = NULL;
		wavetable.wavesynth = NULL;								//RJS 18May98
		wavetable.DLSwavesynth = NULL;								//RJS 18May98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSpot
//Author		Robert Slater
//Date			Mon 25 Mar 1996
//
//Description	Process interrupt spot-effect data if available.
//				This procedure initialises the appropriate sequence for the
//				next callback function with a value of 127.
//
//				Ensures the pan and volume of samples are updated in the
//				3d world.
//
//				Chugs the engine.
//
//Inputs		camera world viewpoint
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::ProcessSpot(ViewPoint*	viewobject)
{
	Log_Stack.Check(LogStack::MOVECODE);
	if (viewobject && Manual_Pilot.ControlledAC2)						//RJS 11Jun99
	{
		if (	!Three_Dee.IsPaused()
			&&	!viewobject->Accel()
			&&	(	!viewobject->drawSpecialFlags
				||	(viewobject->drawSpecialFlags & VIEW_SPECIAL_REPLAY) )	)	
		{
			SLong	seqno;
			SLong	tuneno;
			SWord	engtype;
			SLong	engloop;
			SLong	englength;
			TuneStrucP	TunePtr;

		//DeadCode RJS 06May99 //	if (mdi || dig)
			{
				if (Save_Data.vol.music != 0)
				{
					TuneStrucP	BaseTunePtr = &tune[GetIndex(FIL_MUSIC_MAIN)];//RJS 18May98
					HSEQUENCE	thishandle;

					//This will catch music not caught by the interrrupt...
					if (request.activated & INT_STOPSEQUENCE)
 					{
						bool		stopnow = true;
						thishandle = BaseTunePtr->sequence[0];
						if (AIL_sequence_status(thishandle) == SEQ_PLAYING)
						{
							if (AIL_sequence_volume(thishandle) != 0)
								stopnow = false;
						}

						if (stopnow)
						{
							request.activated &= ~INT_STOPSEQUENCE;
							request.mainstopped = TRUE;
							request.killnow = TRUE;
						}
 					}

					if (request.killnow)
					{
						if (request.forcestop)								//RJS 18Jun99
						{
							request.forcestop = 0;
							TunePtr = NULL;
						}
						else
							TunePtr = request.alonetuneno;					//RJS 26Feb98

						DiscardMusic(TunePtr);								//RJS 26Feb98
						if (TunePtr)
						{
							thishandle = TunePtr->sequence[0];					//RJS 26Feb98
							if (AIL_init_sequence(thishandle,TunePtr->xmiPtr,0)==0)
							{
			//DeadCode RJS 06May99 					AIL_shutdown();
								_Error.EmitSysErr("Cannot initialise XMIDI sequence!\n");
							}

							AIL_lock();
							AIL_start_sequence(thishandle);
 							AIL_set_sequence_volume(thishandle,request.NewVolume,request.NewFade);//RJS 19May98

							thishandle = TunePtr->DLSsequence[0];				//RJS 19May98
							if (thishandle)
							{
								if (AIL_init_sequence(thishandle,TunePtr->dlsPtr,0)==0)
								{
									AIL_start_sequence(thishandle);
 									AIL_set_sequence_volume(thishandle,request.NewVolume,request.NewFade);//RJS 19May98
								}
								else
								{
			//DeadCode RJS 06May99 						AIL_shutdown();
									_Error.EmitSysErr("Cannot initialise DLS sequence!\n");
								}
							}

							AIL_unlock();
						}
						else
							request.musictimeout = 0;
					}
					else
					{
						if (request.musictimeout)
						{
							request.musictimeout -= viewobject->FrameTime();
							if (request.musictimeout <= 0)
							{
								request.musictimeout = 0;
								SequenceMute(3000);
							}
						}
					}

					if (request.mainstopped)								//RJS 12Nov96
					{
			//			for (tuneno = 0; tuneno < 4; tuneno++)
			//			{
			//				if (tune[tuneno].blockptr)
			//				{
			//					if (tune[tuneno].sequence[0])
			//					{
			//						AIL_end_sequence(tune[tuneno].sequence[0]);
			//
			//						if (tuneno != 0)
			//						{
			//							AIL_release_sequence_handle(tune[tuneno].sequence[0]);
			//							tune[tuneno].sequence[0] = NULL;
			//						}
			//					}
			//
			//					#ifdef	__DOS__
			//					VMM_unlock(getdata(tune[tuneno].blockptr),tune[tuneno].size);
			//					#endif
			//					delete tune[tuneno].blockptr;
			//
			//					tune[tuneno].blockptr = NULL;
			//				}
			//			}

		//				if (BaseTunePtr->blockptr && BaseTunePtr->sequence[0])
		//				{
		//					AIL_end_sequence(BaseTunePtr->sequence[0]);
		//
		//					delete BaseTunePtr->blockptr;
		//					BaseTunePtr->blockptr = NULL;
		//				}

						request.mainstopped = FALSE;
						incombat = FALSE;
					}
				}

				// For sound effects...


				allowedsamples = status.nohandlers / 3;						//RJS 09Dec96

				if (EngineSound.Freq == 0)									//RJS 21Oct97
					return;													//RJS 03Dec96

				if (Save_Data.vol.sfx != 0)
				{
					if (!_Replay.replayskip)
					{											//PD 13Aug99
						Bool		delLooped;
						ItemBasePtr	delItem;
						FileNum		delFile;
						FileNum		delSFile;
						FileNum		delEFile;
						SLong		delVol;

						while (delayedsounds.Get(delFile,delItem,delVol,delLooped,delSFile,delEFile))
						{
							if (delLooped)
								PlayLooped(delFile,delItem,delVol,0);
							else
								PlayOnce(delFile,delItem,delVol,delSFile,delEFile);
						}
					}											//PD 13Aug99
					else
						delayedsounds.isSet = FALSE;

					if (EngineSound.CockpitWind)
						PlayWind();

//DeadCode PD 13Aug99 					if (soundtoplay.thesample != FIL_NULL)
//DeadCode PD 13Aug99 					{
//DeadCode PD 13Aug99 						PlaySample(soundtoplay.thesample,soundtoplay.vol,soundtoplay.pan);
//DeadCode PD 13Aug99 
//DeadCode PD 13Aug99 						soundtoplay.thesample = FIL_NULL;
//DeadCode PD 13Aug99 						soundtoplay.vol = 64;
//DeadCode PD 13Aug99 						soundtoplay.pan = 0;
//DeadCode PD 13Aug99 					}

					if (EngineSound.Dying && !EngineSound.Dead)				//RJS 21Oct97
					{
		//				if (abfactor == AEROBATIC_HIGH)
		//				{
		//				}
		//				else
						{
							engtype = Math_Lib.rnd(5 + damagelevel);		//RJS 02Dec96
							englength = EngineSound.ChanPtr->sampleindex->size;	//RJS 17Oct97
							engloop = englength / (2 + Math_Lib.rnd(5));
							engloop = englength - engloop;

							if (	(AIL_sample_position(EngineSound.ChanPtr->handler) > engloop)
								||	!canplaynothing)
							{
								if ((engtype > 0) && (engtype < 3))			//RJS 19Feb98
								{
									engtype -= 1;
									OverrideSample(EngineSound.ChanPtr,(FileNum) (FIL_SFX_P51_CHUGGING1 + engtype),EngineSound.Volume);//RJS 19Feb98

									canplaynothing = TRUE;
								}
								else
								{
									if (canplaynothing)
									{
										OverrideSample(EngineSound.ChanPtr,EngineSound.CurrentFile,EngineSound.WindVolume,0,11025);//RJS 21Oct97

										UpdateEngine();						//RJS 03Dec96
										canplaynothing = FALSE;
									}
								}
							}
						}
					}
					else
					{
						if (!EngineSound.Dead)								//RJS 21Oct97
						{
							UpdateEngine();										//RJS 03Dec96
							OverRevCheck();		//RJS 09Apr99
						}
					}

					Update3d();												//RJS 19Nov96
//Dead					shootTimer -= ((ViewPoint*)View_Point)->FrameTime();					//RJS 12Apr99
//Dead					if (shootTimer <= 0)
//Dead						shootTimer = 0;
				}
			}
		}

		shootTimer -= viewobject->FrameTime();					//RJS 31May99
		if (shootTimer <= 0)
			shootTimer = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillEngine
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	Informs the miles code that the engine is damaged
//
//Inputs		Damage level (0 - 16)
//				0 is no damage
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::KillEngine(ClassPtr	classtype, int	dlevel)
{
	if (dlevel == damagelevel)
		return;

	damagelevel = dlevel;

	if (damagelevel > 0)
	{
		if (damagelevel > 16)
			damagelevel = 16;

		EngineSound.Dying = TRUE;
//		abfactor = classtype->aerobaticfactor;

		if (Save_Data.vol.sfx != 0)
			AIL_set_sample_loop_count(EngineSound.ChanPtr->handler,1);//RJS 17Oct97
	}
	else
 		EngineSound.Dying = FALSE;								//RJS 21Oct97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartSequence
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	Hard starts a sequence from scratch	
//
//Inputs		Sequence number, fade time, and fade volume		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StartSequence(FileNum	thefile, int	sequenceno, SLong	fadeval, SLong	vol)
{
//DeadCode RJS 18Jun99 /*	HSEQUENCE	seqhandle;									
//DeadCode RJS 18Jun99 	TuneStrucP	TunePtr = LoadTune(thefile);					//RJS 26Feb98
//DeadCode RJS 18Jun99 
//DeadCode RJS 18Jun99 	if (TunePtr)												//RJS 26Feb98
//DeadCode RJS 18Jun99 	{
//DeadCode RJS 18Jun99 		if (SequenceInRange(TunePtr,sequenceno) && !request.activated)//RJS 26Feb98
//DeadCode RJS 18Jun99 		{
//DeadCode RJS 18Jun99 			seqhandle = TunePtr->sequence[sequenceno];			//RJS 26Feb98
//DeadCode RJS 18Jun99 
//DeadCode RJS 18Jun99 			request.activated = FALSE;
//DeadCode RJS 18Jun99 
//DeadCode RJS 18Jun99 			AIL_set_sequence_volume(seqhandle,0,0);
//DeadCode RJS 18Jun99 			AIL_start_sequence(seqhandle);
//DeadCode RJS 18Jun99 			AIL_set_sequence_volume(seqhandle,vol,fadeval);
//DeadCode RJS 18Jun99 		}
//DeadCode RJS 18Jun99 	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartSeqEffect
//Author		Robert Slater
//Date			Thu 26 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::StartSeqEffect(TuneStrucP	TunePtr,SLong	vol,SLong fadeval)
{
	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartSeqMain
//Author		Robert Slater
//Date			Thu 26 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::StartSeqMain(TuneStrucP	TunePtr, SLong	vol,SLong fadeval)
{
	int		lasttrack = request.CurrentTrack;

	request.CurrentTrack = ((Mood+128) * 9)/255;
//Dead	if (!request.stopsequence && !request.killnow)				//RJS 06May99
	if (	((request.activated & INT_STOPSEQUENCE)==0)				//RJS 18Jun99
		&& !request.killnow)										//RJS 18Jun99
	{
		Bool	doInt = TRUE;
		int		tuneno = 1;
//Dead		int		lasttrack = request.CurrentTrack;

		SLong	volmoodscale = Mood;
		if (volmoodscale < 0)	volmoodscale = -volmoodscale;

		//16 units of volume difference between neutral and peaks
		volmoodscale = (128 - volmoodscale) << 4;
		volmoodscale >>= 7;
		vol -= volmoodscale;
		if (vol < 0)	vol = 0;

		request.activated = INT_NULL;								//RJS 18Jun99
		request.NewVolume = vol;									//RJS 06May99
		request.NewFade = fadeval;									//RJS 06May99

//Dead		request.CurrentTrack = ((Mood+128) * 9)/255; 

		if (!incombat)										
			doInt = StartMain(request.NewVolume);					//RJS 18Jun99
		else												
		{
			if (lasttrack == request.CurrentTrack)				//RJS 30Jun98
				doInt = FALSE;							
		}													

		if (incombat)										
		{
			if (doInt)
				request.activated |= INT_FADER;
//Dead				request.fader = TRUE;
		}

		if (doInt)
			request.activated |= INT_ON;

		return (doInt);
	}

	return (FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartSeqIndependent
//Author		Robert Slater
//Date			Thu 26 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::StartSeqIndependent(TuneStrucP	TunePtr, SLong	vol,SLong fadeval)
{
	Bool	doInt = TRUE;

	request.activated = INT_NULL;								//RJS 18Jun99
	request.NewVolume = vol;									//RJS 06May99
	request.NewFade = fadeval;									//RJS 06May99

	if (AIL_sequence_status(TunePtr->sequence[0]) == SEQ_PLAYING)
 	{
		//only interrupt if this is a priority stand-alone piece...
		if (TunePtr->ttype==T_independent_pri)
		{
			if (!request.alonetuneno)
			{
				request.NewHandle = TunePtr->sequence[0];
				request.alonetuneno = TunePtr;
//Dead				request.stopsequence = TRUE;
				request.activated |= INT_STOPSEQUENCE;			//RJS 18Jun99

				FadeAll(500);
			}
			else
			{
				if (request.alonetuneno != TunePtr)
				{
					request.NewHandle = TunePtr->sequence[0];
					request.alonetuneno = TunePtr;
//Dead					request.stopsequence = TRUE;
					request.activated |= INT_STOPSEQUENCE;			//RJS 18Jun99

					FadeAll(500);
				}
				else
					doInt = FALSE;		
			}
		}
		else
			doInt = FALSE;
 	}
 	else
 	{
		if (request.alonetuneno != TunePtr)
		{
			request.NewHandle = TunePtr->sequence[0];
			request.alonetuneno = TunePtr;
			request.killnow = TRUE;

 			FadeAll(500);
		}
 	}

	return(doInt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceAudible
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	Essentially a track volume fader;
//				Adjusts the volume of the specified sequence	
//
//Inputs		Tune, Sequence, fade time, fade volume and stomp request
//				If stomp is FALSE,
//					a request is placed to fade in/out at an appropriate moment.
//				otherwise
//					adjust volume regardless.		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SequenceAudible(FileNum	thefile, SLong	vol, SLong	fadeval)
{
	if (!delayedstate)
	{
		Log_Stack.Check(LogStack::MOVECODE);
		TuneStrucP	TunePtr = LoadTune(thefile);					//RJS 26Feb98
		if (TunePtr)												//RJS 26Feb98
		{
			Bool	dochange = FALSE;									//RJS 26Feb98
	//Dead		Bool	oldstate;											//RJS 26Feb98

			vol = ClipVolume(127,vol);

			ULong	oldstate = request.activated;						//RJS 18jUN99

	//DeadCode RJS 06May99 		// Block the interrupt callback routine...					//RJS 06Jan97
	//DeadCode RJS 06May99 		request.activated = FALSE;									//RJS 06Jan97
	//DeadCode RJS 06May99 		request.NewVolume = vol;
	//DeadCode RJS 06May99 		request.NewFade = fadeval;

			switch (TunePtr->ttype)									//RJS 26Feb98
			{
				case T_main:
					dochange = StartSeqMain(TunePtr,vol,fadeval);
					break;
				case T_independent:
				case T_independent_pri:
					dochange = StartSeqIndependent(TunePtr,vol,fadeval);
					break;
			}														//RJS 26Feb98

			if (dochange)												//RJS 06Jan97
			{
				request.musictimeout = MUSIC_TIMEOUT;					//RJS 18Jun99
				request.forcestop = 0;
			}
			else														//RJS 06Jan97
				request.activated = oldstate;							//RJS 06Jan97
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceAudible
//Author		Robert Slater
//Date			Thu 29 Aug 1996
//
//Description	For mood settings
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SequenceAudible(MoodSetting	 setMood,SLong vol,SLong fadeval)
{
	Mood = setMood;
	SequenceAudible(FIL_MUSIC_MAIN,vol,fadeval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceAudible
//Author		Robert Slater
//Date			Wed 3 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SequenceAudible(MoodDelta	 deltaMood,SLong vol,SLong fadeval)
{
	Mood += deltaMood;
	SequenceAudible(FIL_MUSIC_MAIN,vol,fadeval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopSequence
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	Stops a sequence from playing	
//
//Inputs		The file, Sequence no
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopSequence(FileNum	thefile, int	sequenceno)
{
	HSEQUENCE	seqhandle;
	int			tuneno;

	tuneno = GetIndex(thefile);

	if (Save_Data.vol.music == 0)
		return;

	if (tune[tuneno].blockptr == NULL)
		return;

	if (!SequenceInRange(&tune[tuneno],sequenceno))
		return;

	if (request.activated)
		return;

	// Place a request if we do not want an immediate reaction

//Dead	request.stopsequence = TRUE;
	request.activated |= INT_STOPSEQUENCE;						//RJS 18Jun99

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopMusic
//Author		Robert Slater
//Date			Thu 22 Aug 1996
//
//Description	Stops all the midi music if any is playing
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopMusic()
{
	int			tuneno, seqno;
	HSEQUENCE	tmphandle;

	if ((Save_Data.vol.music != 0) && (musicstopped==FALSE))	//RJS 25Jun98
	{
 		request.activated = INT_NULL;

		for (tuneno = 0; tuneno < MAXTUNES; tuneno++)
		{
			if (tune[tuneno].blockptr)
			{
				for (seqno = 0; seqno < tune[tuneno].nosequences; seqno++)
				{
					tmphandle = tune[tuneno].sequence[seqno];
					if (AIL_sequence_status(tmphandle) == SEQ_PLAYING)
	 					AIL_stop_sequence(tmphandle);

					tmphandle = tune[tuneno].DLSsequence[seqno];
					if (tmphandle)
					{
						if (AIL_sequence_status(tmphandle) == SEQ_PLAYING)
		 					AIL_stop_sequence(tmphandle);
					}
				}
			}
		}
	}

	musicstopped = TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FadeAll
//Author		Robert Slater
//Date			Fri 30 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	Miles::FadeAll(SLong fadeval)
{
	bool	somethingplaying = false;
	if (Save_Data.vol.music != 0)								//RJS 25Jun98
	{
		int			endtune = GetIndex(FIL_MUSIC_LAST_TUNE);
		int			tuneno;
		HSEQUENCE	tmphandle;

		for (tuneno = 0; tuneno < endtune; tuneno++)
		{
			tmphandle = tune[tuneno].sequence[0];
			if (tmphandle)
			{
	 			if (AIL_sequence_status(tmphandle) == SEQ_PLAYING)
				{
					somethingplaying = true;
	 				AIL_set_sequence_volume(tmphandle, 0, fadeval);
				}
			}

			tmphandle = tune[tuneno].DLSsequence[0];
			if (tmphandle)
			{
				if (AIL_sequence_status(tmphandle) == SEQ_PLAYING)
				{
					somethingplaying = true;
	 				AIL_set_sequence_volume(tmphandle, 0, fadeval);
				}
			}
		}
	}

	return somethingplaying;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResumeMusic
//Author		Robert Slater
//Date			Thu 22 Aug 1996
//
//Description	Resumes all stopped midi music
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::ResumeMusic()
{
	if ((Save_Data.vol.music != 0) && (musicstopped==TRUE))		//RJS 25Jun98
	{
		int	tuneno, seqno;
		HSEQUENCE	tmphandle;

		for (tuneno = 0; tuneno < MAXTUNES; tuneno++)
		{
			if (tune[tuneno].blockptr)
			{
				for (seqno = 0; seqno < tune[tuneno].nosequences; seqno++)
				{
					tmphandle = tune[tuneno].sequence[seqno];
	 				AIL_resume_sequence(tmphandle);
				}
			}
		}

		musicstopped = FALSE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceMute
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	Fade out sequence	
//
//Inputs		The sequence no, the fade time, a stomp request		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SequenceMute(FileNum	thefile, int	sequenceno, SLong	fadeval)
{
	SequenceAudible(thefile,0,fadeval);							//RJS 29Aug96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		reporterror
//Author		Robert Slater
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::reporterror(int	eno, char	*text)
{
	if (dig || mdi)
	{
		status.errorno = eno;

		if (text)
			strcpy(status.errorstring,text);

		switch(eno)
		{
		case 0:
			_Error.EmitSysErr("Out of range!\n");
			break;
		case 2:
			AIL_shutdown();
			_Error.EmitSysErr("Could not play the sample!\n");
		case 3:
			AIL_shutdown();
			_Error.EmitSysErr("Could not secure the sample memory!\n");
		}
	}
	else
		_Error.EmitSysErr("Horrendous MILES error!\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSample
//Author		Robert Slater
//Date			Tue 20 Feb 1996
//
//Description	Gets a sample from disk and stores its information	
//
//Inputs		Sample number and the filename
//
//Returns		TRUE if a success,
//				FALSE otherwise
//
//------------------------------------------------------------------------------
SampleRec*	Miles::LoadSample(FileNum	thefile, Bool inUI)
{
	int			spos = GetIndex(thefile);
	SampleRec*	SamplePtr = NULL;

	if ((Save_Data.vol.sfx || inUI) && SampleInRange(spos))
	{
		SamplePtr = &thesample[spos];

		if (!SamplePtr->blockptr)
		{
//			if (FILEMAN.fileloadedthisframe && !FILEMAN.loadednumberedfile(thefile))
//				SamplePtr = NULL;
//			else
			{
				char		header[10];
				char		*tmpptr;
				void		*tmpaddress;
				int			size;
				int			count;
				SLong		result = 1;
				fileblock	*theblock;
				RIFF		*header1;
				FMT			*header2;
				DATA		*header3;

				theblock = new fileblock (thefile);

				tmpaddress = getdata(theblock);
				size = getsize(theblock);

				// Make sure the sample in memory is secure...
				#ifdef __DOS__
				result = VMM_lock(tmpaddress, size);
				#endif

				if (!result)
					reporterror(3);
				elser
				{
					SamplePtr->blockptr = theblock;
					SamplePtr->size = size;

					// Extract header id for file and decide if it is RAW

					tmpptr = (char*) tmpaddress;

					for (count = 0; count < 4; count ++)
						header[count] = *tmpptr++;
	
					header[4] = 0;

					if (	(strcmp(header,"RIFF") == 0)
						||	(strcmp(header,"Crea") == 0) )
					{
						header1 = (RIFF*) tmpaddress;
						header2 = (FMT*) header1->data;
		
						count = 0;											//RJS 24Nov96
						while (strnicmp(header2->FMT_string,"fmt ",4))
    					{
    						header2 = (FMT *) ((BYTE *) header2 +
			      					header2->chunk_size + 8 + (header2->chunk_size & 1));

							count++;										//RJS 24Nov96
							if (count >3)									//RJS 24Nov96
								break;										//RJS 24Nov96
    					}

						if (count > 3)
							SamplePtr->samplerate = 11025;
						else
							SamplePtr->samplerate = header2->sample_rate;

						header3 = (DATA*) header1->data;
						while (strnicmp(header3->DATA_string,"data",4))
	  					{
    						header3 = (DATA *) ((char *) header3 +
			      					header3->chunk_size + 8 + (header3->chunk_size & 1));
    					}

						SamplePtr->datasize = header3->chunk_size;
						SamplePtr->dataptr = (void*) header3->data;
					}
					else													//RJS 16Oct97
						SamplePtr->samplerate = 44100;					//RJS 16Oct97

					SamplePtr->priority = spos * PRIORITYFACTOR;

					status.nosamples++;
				}
			}
		}
	}

	return(SamplePtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleRate
//Author		Robert Slater
//Date			Wed 19 Jun 1996
//
//Description	Returns the sampling rate of a particular sample file
//
//Inputs		the file
//
//Returns		the playback rate
//
//------------------------------------------------------------------------------
SLong	Miles::SampleRate(FileNum	thefile)
{
	return(thesample[GetIndex(thefile)].samplerate);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeHandler
//Author		Robert Slater
//Date			Tue 20 Feb 1996
//
//Description	Finds a free position in the sound queue.
//				If there is not one available then replace lowest priority sound
//
//Inputs		The priority of the sound handlers,
//				The sample number,
//				The world position pointer
//
//Returns		Queue index
//
//------------------------------------------------------------------------------
SQueuePtr	Miles::FindFreeHandler(SampleRec* SamplePtr, ItemBasePtr	sampleitem, SQueuePtr	&OldChannelPtr, UByte	looplength)
{
	int			count;
	int			lowest = 0;
	int			lowpos = -1;
	SQueuePtr	ChannelPtr;
	SQueuePtr	NewChannelPtr = NULL;
	int			priority = SamplePtr->priority;

	OldChannelPtr = NULL;
	ChannelPtr = &soundqueue[freechannelstart];					//RJS 28Jan99
	for (count = freechannelstart; count < status.nohandlers; count ++)//RJS 28Jan99
	{
		if (!ChannelPtr->isRadio)								//RJS 10Jun98
		{
			ChannelPtr->playingpriority++;							//RJS 16Oct97

			if (ChannelPtr->playingpriority > lowest)			//RJS 04Jul96
			{
				lowest = ChannelPtr->playingpriority;
				lowpos = count;
			}

			if (ChannelPtr->sampleindex)								//RJS 16Oct97
			{
				if (AIL_sample_status(ChannelPtr->handler) == SMP_DONE)
				{
					ChannelPtr->looping = FALSE;
					ChannelPtr->worlditem = NULL;
					ChannelPtr->GameSound = FALSE;				//RJS 26Nov96
					ChannelPtr->isRadio = FALSE;					//RJS 09Jun98

					if (!NewChannelPtr && !OldChannelPtr)				//RJS 17Oct97
						NewChannelPtr = ChannelPtr;						//RJS 17Oct97

					ChannelPtr->sampleindex = NULL;
				}
				else
				{
					if (	(ChannelPtr->looping)						//RJS 17Oct97
						&&	(ChannelPtr->worlditem == sampleitem)		//RJS 17Oct97
						&&	(ChannelPtr->sampleindex == SamplePtr)	//RJS 17Oct97
						&&	!OldChannelPtr		)					//RJS 17Oct97
					{												//RJS 17Oct97
						OldChannelPtr = ChannelPtr;						//RJS 17Oct97
						NewChannelPtr = NULL;

						AIL_set_sample_loop_count(ChannelPtr->handler,looplength);//RJS 05Dec96
					}
				}
			}
			else
			{
				if (!NewChannelPtr && !OldChannelPtr)					//RJS 17Oct97
					NewChannelPtr = ChannelPtr;							//RJS 17Oct97
			}
		}

		ChannelPtr++;											//RJS 21Oct97
	}

	// If there were no free slots, then grab the one with the lowest priority

	if (!NewChannelPtr && !OldChannelPtr)
	{
		if (priority <= lowest)									//RJS 04Jul96
		{
			NewChannelPtr = &soundqueue[lowpos];

			NewChannelPtr->sampleindex = NULL;					//RJS 16Oct97
			NewChannelPtr->looping = FALSE;						//RJS 16Oct97
			NewChannelPtr->worlditem = NULL;						//RJS 16Oct97
			NewChannelPtr->GameSound = FALSE;						//RJS 16Oct97
			NewChannelPtr->isRadio = FALSE;						//RJS 09Jun98

			AIL_end_sample(NewChannelPtr->handler);				//RJS 16Oct97
		}
	}

	return(NewChannelPtr);										//RJS 16Oct97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeHandlerOnce
//Author		Robert Slater
//Date			Tue 19 Nov 1996
//
//Description	Same as above, but blocks the sample if already playing
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SQueuePtr	Miles::FindFreeHandlerOnce(SampleRec* SamplePtr, ItemBasePtr	sampleitem, SQueuePtr	&OldChannelPtr, int	stblock, int	endblock)
{
	int		count;
	int		lowest = 0;
	int		lowpos = -1;
	SQueuePtr	ChannelPtr;
	SQueuePtr	NewChannelPtr = NULL;
	int			priority = SamplePtr->priority;
	SampleRec*	StBlockPtr = &thesample[stblock];
	SampleRec*	EndBlockPtr = &thesample[endblock];

	OldChannelPtr = NULL;	//RJS 29Jan99

	ChannelPtr = &soundqueue[freechannelstart];					//RJS 28Jan99
	for (count = freechannelstart; count < status.nohandlers; count ++)//RJS 28Jan99
	{
		ChannelPtr = &soundqueue[count];							//RJS 16Oct97
		if (!ChannelPtr->isRadio)								//RJS 10Jun98
		{
			ChannelPtr->playingpriority++;							//RJS 16Oct97
			if (ChannelPtr->playingpriority > lowest)			//RJS 04Jul96
			{
				lowest = ChannelPtr->playingpriority;
				lowpos = count;
			}

			if (ChannelPtr->sampleindex)								//RJS 16Oct97
			{
				if (AIL_sample_status(ChannelPtr->handler) == SMP_DONE)
				{
					ChannelPtr->looping = FALSE;
					ChannelPtr->worlditem = NULL;
					ChannelPtr->GameSound = FALSE;
					ChannelPtr->isRadio = FALSE;					//RJS 09Jun98

					if (!NewChannelPtr && !OldChannelPtr)				//RJS 17Oct97
						NewChannelPtr = ChannelPtr;						//RJS 17Oct97

					ChannelPtr->sampleindex = NULL;
				}
				else
				{
					if (	(ChannelPtr->worlditem == sampleitem)		//RJS 17Oct97
						&&  (ChannelPtr->sampleindex > StBlockPtr)	//RJS 17Oct97
						&&	(ChannelPtr->sampleindex < EndBlockPtr)	//RJS 17Oct97
						&&	!OldChannelPtr	)						//RJS 17Oct97
					{												//RJS 17Oct97
						OldChannelPtr = ChannelPtr;						//RJS 17Oct97
					}												//RJS 17Oct97
				}
			}
			else
			{
				if (!NewChannelPtr && !OldChannelPtr)
					NewChannelPtr = ChannelPtr;							//RJS 17Oct97
			}
		}

		ChannelPtr++;
	}

	// If there were no free slots, then grab the one with the lowest priority

	if (!NewChannelPtr && !OldChannelPtr)							//RJS 17Oct97
	{
		if (priority <= lowest)									//RJS 16Oct97
		{
			NewChannelPtr = &soundqueue[lowpos];					//RJS 16Oct97

			NewChannelPtr->sampleindex = NULL;					//RJS 16Oct97
			NewChannelPtr->looping = FALSE;						//RJS 16Oct97
			NewChannelPtr->worlditem = NULL;						//RJS 16Oct97
			NewChannelPtr->GameSound = FALSE;						//RJS 16Oct97
			NewChannelPtr->isRadio = FALSE;						//RJS 09Jun98

			AIL_end_sample(NewChannelPtr->handler);				//RJS 16Oct97
		}
	}

	return(NewChannelPtr);										//RJS 16Oct97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeRadioHandler
//Author		Robert Slater
//Date			Mon 1 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SQueuePtr	Miles::FindFreeRadioHandler()
{
//DeadCode RJS 28Jan99 	int			count;
//DeadCode RJS 28Jan99 	SQueuePtr	ChannelPtr;
//DeadCode RJS 28Jan99 	SQueuePtr	NewChannelPtr = NULL;
//DeadCode RJS 28Jan99 	SQueuePtr	OldChannelPtr = NULL;
//DeadCode RJS 28Jan99 
//DeadCode RJS 28Jan99 	ChannelPtr = &soundqueue[2];								
//DeadCode RJS 28Jan99 	for (count = 2; count < status.nohandlers; count ++)
//DeadCode RJS 28Jan99 	{
//DeadCode RJS 28Jan99 		ChannelPtr = &soundqueue[count];						
//DeadCode RJS 28Jan99 
//DeadCode RJS 28Jan99 		if (ChannelPtr->sampleindex)								
//DeadCode RJS 28Jan99 		{
//DeadCode RJS 28Jan99 			if (AIL_sample_status(ChannelPtr->handler) == SMP_DONE)
//DeadCode RJS 28Jan99 			{
//DeadCode RJS 28Jan99 				ChannelPtr->looping = FALSE;
//DeadCode RJS 28Jan99 				ChannelPtr->worlditem = NULL;
//DeadCode RJS 28Jan99 				ChannelPtr->GameSound = FALSE;
//DeadCode RJS 28Jan99 				ChannelPtr->isRadio = FALSE;
//DeadCode RJS 28Jan99 
//DeadCode RJS 28Jan99 				if (!NewChannelPtr && !OldChannelPtr)		
//DeadCode RJS 28Jan99 					NewChannelPtr = ChannelPtr;			
//DeadCode RJS 28Jan99 
//DeadCode RJS 28Jan99 				ChannelPtr->sampleindex = NULL;
//DeadCode RJS 28Jan99 			}
//DeadCode RJS 28Jan99 			else
//DeadCode RJS 28Jan99 			{
//DeadCode RJS 28Jan99 				if (ChannelPtr->isRadio)
//DeadCode RJS 28Jan99 				{
//DeadCode RJS 28Jan99 					OldChannelPtr = ChannelPtr;
//DeadCode RJS 28Jan99 					NewChannelPtr = NULL;
//DeadCode RJS 28Jan99 					break;
//DeadCode RJS 28Jan99 				}
//DeadCode RJS 28Jan99 			}
//DeadCode RJS 28Jan99 		}
//DeadCode RJS 28Jan99 		else
//DeadCode RJS 28Jan99 		{
//DeadCode RJS 28Jan99 			if (!NewChannelPtr && !OldChannelPtr)
//DeadCode RJS 28Jan99 				NewChannelPtr = ChannelPtr;			
//DeadCode RJS 28Jan99 		}
//DeadCode RJS 28Jan99 
//DeadCode RJS 28Jan99 		ChannelPtr++;
//DeadCode RJS 28Jan99 	}

	int			count;
	SQueuePtr	ChannelPtr;
	SQueuePtr	NewChannelPtr = NULL;
	SQueuePtr	OldChannelPtr = NULL;

	ChannelPtr = &soundqueue[channel_radiochatter];								//RJS 14Apr99
	if (ChannelPtr->sampleindex)								
	{
		if (AIL_sample_status(ChannelPtr->handler) == SMP_DONE)
		{
			ChannelPtr->looping = FALSE;
			ChannelPtr->worlditem = NULL;
			ChannelPtr->GameSound = FALSE;
			ChannelPtr->isRadio = FALSE;

			if (!NewChannelPtr && !OldChannelPtr)		
				NewChannelPtr = ChannelPtr;			

			ChannelPtr->sampleindex = NULL;
		}
		else
		{
			if (ChannelPtr->isRadio)
			{
				OldChannelPtr = ChannelPtr;
				NewChannelPtr = NULL;
			}
		}
	}
	else
	{
		if (!NewChannelPtr && !OldChannelPtr)
			NewChannelPtr = ChannelPtr;			
	}

	return(NewChannelPtr);							
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeHandlerUI
//Author		Robert Slater
//Date			Fri 12 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SQueuePtr	Miles::FindFreeHandlerUI(SampleRec* SamplePtr)
{
	int		count;
	int		lowest = 0;
	int		lowpos = -1;
	SQueuePtr	ChannelPtr;
	SQueuePtr	NewChannelPtr = NULL;
	int			priority = SamplePtr->priority;
	SQueuePtr	OldChannelPtr = NULL;

//Dead	ChannelPtr = &soundqueue[freechannelstart];
//Dead	for (count = freechannelstart; count < status.nohandlers; count ++)
	ChannelPtr = &soundqueue[0];
	for (count = 0; count < status.nohandlers; count ++)
	{
		ChannelPtr = &soundqueue[count];						
		if (!ChannelPtr->isRadio)								
		{
			ChannelPtr->playingpriority++;						
			if (ChannelPtr->playingpriority > lowest)			
			{
				lowest = ChannelPtr->playingpriority;
				lowpos = count;
			}

			if (ChannelPtr->sampleindex)
			{
				if (AIL_sample_status(ChannelPtr->handler) == SMP_DONE)
				{
					ChannelPtr->looping = FALSE;
					ChannelPtr->worlditem = NULL;
					ChannelPtr->GameSound = FALSE;
					ChannelPtr->isRadio = FALSE;

					if (!NewChannelPtr && !OldChannelPtr)
						NewChannelPtr = ChannelPtr;

					ChannelPtr->sampleindex = NULL;
				}
				else
				{
					if (	(ChannelPtr->sampleindex == SamplePtr)
						&&	!OldChannelPtr	)						
					{												
						OldChannelPtr = ChannelPtr;
						NewChannelPtr = OldChannelPtr;

						AIL_end_sample(ChannelPtr->handler);

						ChannelPtr->looping = FALSE;
						ChannelPtr->worlditem = NULL;
						ChannelPtr->GameSound = FALSE;
						ChannelPtr->isRadio = FALSE;
						ChannelPtr->sampleindex = NULL;
					}												
				}
			}
			else
			{
				if (!NewChannelPtr && !OldChannelPtr)
					NewChannelPtr = ChannelPtr;
			}
		}

		ChannelPtr++;
	}

	// If there were no free slots, then grab the one with the lowest priority

	if (!NewChannelPtr && !OldChannelPtr)						
	{
		if (priority <= lowest)									
		{
			NewChannelPtr = &soundqueue[lowpos];				

			NewChannelPtr->sampleindex = NULL;					
			NewChannelPtr->looping = FALSE;						
			NewChannelPtr->worlditem = NULL;					
			NewChannelPtr->GameSound = FALSE;					
			NewChannelPtr->isRadio = FALSE;						

			AIL_end_sample(NewChannelPtr->handler);				
		}
	}

	return(NewChannelPtr);										
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipVolume
//Author		Robert Slater
//Date			Thu 7 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	Miles::ClipVolume(SLong	maxvol, SLong	vol)
{
	if (vol < 0)
		vol = 0;  			// Too quiet

	if (vol > maxvol)
		vol = maxvol;			// Too loud

	return(vol);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipPan
//Author		Robert Slater
//Date			Thu 7 Mar 1996
//
//Description	
//
//Inputs		+/-32K clipped to +/-10K then shifted to +/- 64
//
//Returns		0..127
//
//------------------------------------------------------------------------------
SLong	Miles::ClipPan(SLong	pan)
{

	// Clip the pan...

	if (pan < -16383)
		pan = -16383;		// Hard left

	if (pan > 16383)
		pan = 16383;			// Hard right


	pan = (pan>>8) + 64;			// Scale and shift to acceptible range

	return(pan);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SoundInWorld
//Author		Robert Slater
//Date			Tue 25 Jun 1996
//
//Description	Calculates the pan angle of the sound relative to view point,
//				And the volume of the sound :
//
//										 2
//						vol = MaxVol * uD			uD = Unit Distance (20000)
//									   ---			D  = Distance from source
//									     2
//									    D
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	Miles::SoundInWorld(COORDS3D WPos, SLong	&vol, SLong	&newdist)
{
	SLong	distance = 0;
	SLong	dx = 0;
	SLong	dy, dz;
//DeadCode AMM 23Feb99 	ULong	big = 400000000;     //Unit-Distance squared...
	ULong	newervol = 0;										//RJS 15Oct97
//DeadCode RJS 15Oct97 	ULong	big2;
//DeadCode RJS 16Oct97 	float	frac;
	SWord	hdg = 0;
	SWord	hdg1 = 0;
	SWord	pitch;

	if (View_Point)												//RJS 26Feb98
	{
		dx = WPos.X - View_Point->World.X;							//RJS 16Oct97
		dy = WPos.Y - View_Point->World.Y;							//RJS 16Oct97
		dz = WPos.Z - View_Point->World.Z;							//RJS 16Oct97

		Math_Lib.Intercept(dx,dy,dz,distance,hdg,pitch);

		hdg1 = View_Point->hdg;										//RJS 16Oct97
	}
	else
	{
		dx = dy = dz = 0;
		hdg1 = 0;
	}															//RJS 26Feb98

	hdg += hdg1;												//RJS 16Oct97

	if (distance < 100)
		hdg = 0;
	else														//RJS 16Oct97
		RowanToPan(hdg);		//RJS 29Jan99

//DeadCode RJS 15Oct97 	if (distance < 45536)										//RJS 02Aug96
//DeadCode RJS 15Oct97 	{
//DeadCode RJS 15Oct97 		distance += 20000;
//DeadCode RJS 15Oct97 		big2 = distance * distance;
//DeadCode RJS 15Oct97 		newervol = (SLong) MULDIVUNS((ULong) vol,big,big2);
//DeadCode RJS 15Oct97 		vol = newervol;
//DeadCode RJS 15Oct97 	}
//DeadCode RJS 15Oct97 	else
//DeadCode RJS 15Oct97 		if (distance > 159000)
//DeadCode RJS 15Oct97 			vol = 0;
//DeadCode RJS 15Oct97 		else
//DeadCode RJS 15Oct97 			if (distance > 92014)
//DeadCode RJS 15Oct97 				vol >>= 7;										//RJS 27Nov96
//DeadCode RJS 15Oct97 			else
//DeadCode RJS 15Oct97 				if (distance > 71000)
//DeadCode RJS 15Oct97 					vol >>= 5;									//RJS 27Nov96
//DeadCode RJS 15Oct97 				else
//DeadCode RJS 15Oct97 
//DeadCode RJS 15Oct97 					vol >>= 3;
//DeadCode RJS 15Oct97 
//DeadCode RJS 15Oct97 	vol >>= 8;

//DeadCode AMM 23Feb99 	distance += 20000;
//DeadCode AMM 23Feb99 	newervol = MULDIVUNS((ULong) vol,big,(ULong)distance);
//DeadCode AMM 23Feb99 	newervol /= distance;
//DeadCode AMM 23Feb99 	vol = newervol/256;
//DeadCode AMM 23Feb99 
//DeadCode AMM 23Feb99 	newdist = distance;											//RJS 16Oct97

	if (distance >= 0)																//RJS 15Jun99
	{
		ULong	distmetres;
		distmetres = ULong(distance);
		distmetres /= 100;
		distmetres += 200;		//(+ 1 unit of sound distance)

		newervol = ULong(vol);
		newervol *= 40000;
		newervol /= distmetres;
//		newervol = MULDIVUNS((ULong) vol,40000,distmetres);
		newervol /= distmetres;

		newervol>>=8;				//scale to 127...
		vol = SLong(newervol);
	}
	else
	{
		// Too far away... overflow
		vol = 0;
	}

	return((SLong)hdg);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Update3d
//Author		Robert Slater
//Date			Thu 27 Jun 1996
//
//Description	update the 3d sound world if any sound is playing
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::Update3d()
{
	Log_Stack.Check(LogStack::MOVECODE);
	int		count;
	SLong	pan;
	SLong	vol;
	SampleRec*	thissamp;										//RJS 16Oct97
	Bool	isused = FALSE;										//RJS 03Dec96
	ULong	TimeDiff;											//RJS 16Oct97
	SLong	distance;											//RJS 16Oct97
	SQueuePtr	ChannelPtr = soundqueue;						//RJS 16Oct97

	if (delindex < (MAXSAMPLES_LOADED-1))						//MS 23Sep98
		delindex++;												//RJS 15May98
	else														//RJS 15May98
		delindex = 0;											//RJS 15May98

	for (count = 0; count < status.nohandlers; count++)			//RJS 04Jun99
	{
		thissamp = ChannelPtr->sampleindex;
		if (count >= freechannelstart)									//RJS 04Jun99
		{
			if (thissamp && ChannelPtr->GameSound)				//RJS 16Oct97
			{
				if (AIL_sample_status(ChannelPtr->handler) == SMP_PLAYING)
				{
					vol = ChannelPtr->playingvolume;					//RJS 16Oct97

					if (ChannelPtr->worlditem)						//RJS 16Oct97
						pan = ClipPan(SoundInWorld(ChannelPtr->worlditem->World,vol,distance));//RJS 16Oct97
					else
						pan = ClipPan(SoundInWorld(ChannelPtr->StaticPos,vol,distance));//RJS 16Oct97

	//				AIL_lock();										//RJS 05Dec96
					if (AIL_sample_status(ChannelPtr->handler) == SMP_PLAYING)//RJS 05Dec96
					{
						if (vol)									//RJS 05Dec96
						{
							if (vol > 127)	vol = 127;
							AIL_set_sample_pan	 (ChannelPtr->handler, pan);//RJS 16Oct97
				    		AIL_set_sample_volume(ChannelPtr->handler, vol);//RJS 16Oct97
						}
						else
							ChannelPtr->playingpriority+=PRIORITYFACTOR;	//RJS 15Jun99
					}
	//				AIL_unlock();									//RJS 05Dec96
				}
				else
				{
					thissamp = NULL;								//RJS 16Oct97
					ChannelPtr->sampleindex = NULL;					//RJS 16Oct97
				}
			}
		}

		if (thissamp == &thesample[delindex])					//RJS 16Oct97
			isused = TRUE;										//RJS 03Dec96

		ChannelPtr++;											//RJS 20Oct97
	}

	if (!isused)												//RJS 16Oct97
		DeleteSample(delindex);									//RJS 15May98

//	if (delindex < (MAXSAMPLES-1))								//RJS 03Dec96
//		delindex++;												//RJS 03Dec96
//	else														//RJS 03Dec96
//		delindex = 0;											//RJS 03Dec96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HaltItemSound
//Author		Robert Slater
//Date			Thu 11 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::HaltItemSound(ItemBasePtr	sampleitem)
{
//	Log_Stack.Check(LogStack::MOVECODE);
	int	count;
	SQueuePtr	ChannelPtr;										//RJS 16Oct97

	if ((Save_Data.vol.sfx != 0) && sampleitem)					//RJS 19Nov96
		for (count = 1; count < status.nohandlers; count++)
		{
			ChannelPtr = &soundqueue[count];
			if ((ChannelPtr->worlditem == sampleitem) && ChannelPtr->GameSound)//RJS 16Oct97
			{
				ChannelPtr->StaticPos = ChannelPtr->worlditem->World;
				ChannelPtr->worlditem = NULL;
				ChannelPtr->looping = FALSE;
			}
		}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlaySettings
//Author		Robert Slater
//Date			Thu 7 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlaySettings(SQueuePtr	ChannelPtr, SLong	vol, SLong	pan, int priority)
{
//	Log_Stack.Check(LogStack::MOVECODE);
	int		volscale;
//DeadCode RJS 09Apr99 	Bool	changevol = FALSE;
//DeadCode RJS 09Apr99 	Bool	changepan = FALSE;
//DeadCode RJS 09Apr99 
//DeadCode RJS 09Apr99 	if (vol > -1)
//DeadCode RJS 09Apr99 		changevol = TRUE;
//DeadCode RJS 09Apr99 
//DeadCode RJS 09Apr99 	if (pan > -50000)
//DeadCode RJS 09Apr99 		changepan = TRUE;

//	vol = ClipVolume(ChannelPtr->playingvolume>>8,vol);			//RJS 17Oct97
	if (vol > 127)	vol = 127;
	pan = ClipPan(pan);

	volscale = (127 - vol) >> 4;								//RJS 05Dec96

	ChannelPtr->playingpriority = priority + volscale;			//RJS 21Oct97
																//RJS 21Oct97
//DeadCode RJS 09Apr99 	if (changepan)												//RJS 21Oct97
//DeadCode RJS 09Apr99 		AIL_set_sample_pan	 (ChannelPtr->handler, pan);		//RJS 21Oct97
//DeadCode RJS 09Apr99 																//RJS 21Oct97
//DeadCode RJS 09Apr99 	if (changevol)												//RJS 21Oct97
//DeadCode RJS 09Apr99 	    AIL_set_sample_volume(ChannelPtr->handler, vol);		//RJS 21Oct97

	AIL_set_sample_pan	 (ChannelPtr->handler, pan);			//RJS 09Apr99
	AIL_set_sample_volume(ChannelPtr->handler, vol);			//RJS 09Apr99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpSample
//Author		Robert Slater
//Date			Mon 4 Mar 1996
//
//Description	Initialises a sample for a handler and plays it	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetUpSample(SQueuePtr ChannelPtr, SampleRec* SamplePtr, SLong	maxvol, SLong	vol, SLong	pan, ItemBasePtr	sampleitem)
{
	void		*address;
	HSAMPLE		handler;
	UByte		isloop = FALSE;									//RJS 21Oct97

	if (	(SamplePtr > &thesample[GetIndex(FIL_SFX_LOOP_FX_START)])
		&&	(SamplePtr < &thesample[GetIndex(FIL_SFX_LOOP_FX_END)])	)
		isloop = TRUE;

	handler = ChannelPtr->handler;								//RJS 16Oct97
	address = getdata(SamplePtr->blockptr);

	ChannelPtr->sampleindex = SamplePtr;						//RJS 21Oct97
	ChannelPtr->playingvolume = maxvol;							//RJS 16Oct97
	ChannelPtr->worlditem = sampleitem;							//RJS 16Oct97
	ChannelPtr->GameSound = TRUE;								//RJS 21Oct97
	ChannelPtr->looping = isloop;								//RJS 21Oct97

	if (!sampleitem)											//RJS 21Oct97
 		ChannelPtr->GameSound = FALSE;							//RJS 21Oct97

	AIL_init_sample(handler);									//RJS 26Nov96
//	AIL_set_sample_type(handler,DIG_F_MONO_8,0);				//RJS 09Mar98
//	AIL_set_sample_address(handler,SamplePtr->dataptr,SamplePtr->datasize);//RJS 09Mar98
//	AIL_set_sample_playback_rate(handler,11025);				//RJS 09Mar98

 	if (AIL_set_sample_file(handler,address,-1))				//RJS 21Oct97
 	{															//RJS 21Oct97
		PlaySettings(ChannelPtr,vol,pan,SamplePtr->priority);	//RJS 21Oct97
																//RJS 21Oct97
		if ((ChannelPtr != EngineSound.ChanPtr) || EngineSound.Dying)//RJS 21Oct97
		{														//RJS 21Oct97
//			SamplePtr->LastTime = Timer_Code.realtime;			//RJS 21Oct97
			if (isloop)											//RJS 21Oct97
				AIL_set_sample_loop_count(handler,2);			//RJS 21Oct97
			else												//RJS 21Oct97
				AIL_set_sample_loop_count(handler,1);			//RJS 21Oct97
		}														//RJS 21Oct97
 	}															//RJS 21Oct97
 	else														//RJS 21Oct97
 		reporterror(2);											//RJS 21Oct97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlaySample
//Author		Robert Slater
//Date			Tue 25 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void 	Miles::PlaySample(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol)
{
	if (delayedstate)
		PlayDelayed(thefile,sampleitem,vol,FALSE);
	else
	{
		Log_Stack.Check(LogStack::MOVECODE);
		SQueuePtr	ChannelPtr;										//RJS 16Oct97
		SQueuePtr	OldChannelPtr;									//RJS 16Oct97
		SLong	thevol;												//RJS 05Dec96
		int		thepan;												//RJS 05Dec96
		SLong	distance;
		SampleRec*	SamplePtr;

		if (allowedsamples)											//RJS 16Oct97
		{
			SamplePtr = LoadSample(thefile);
			if (SamplePtr)
			{
				thevol = (SamplePtr->samplevolume * vol) >> 7;			//RJS 05Dec96
				vol = thevol;												//RJS 05Dec96

				if (sampleitem)										//RJS 26Feb98
					thepan = SoundInWorld(sampleitem->World,thevol,distance);//RJS 16Oct97
				else
				{
					thepan = 0;
					thevol >>= 8;
				}

				if (thevol)
				{
					ChannelPtr = FindFreeHandler(SamplePtr,sampleitem,OldChannelPtr);
					if (ChannelPtr)											//RJS 16Oct97
					{
						allowedsamples--;

						SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,sampleitem);//RJS 16Oct97
						AIL_start_sample(ChannelPtr->handler);				//RJS 16Oct97
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlaySample
//Author		Robert Slater
//Date			Tue 20 Feb 1996
//
//Description	Soft start a sample; finds a suitable slot in the sound
//				handler queue then starts it.
//
//Inputs		The sample number, its volume, its stereo pan (0 is central)		
//
//Returns		The sample that has been played.
//				-1 if it has failed
//
//------------------------------------------------------------------------------
void 	Miles::PlaySample(FileNum	thefile, SLong	vol, SLong	pan)
{
	if (delayedstate)
		PlayDelayed(thefile,NULL,vol,FALSE);
	else
	{
		Log_Stack.Check(LogStack::MOVECODE);
		SQueuePtr	ChannelPtr;										//RJS 16Oct97
		SQueuePtr	OldChannelPtr;									//RJS 16Oct97
		SampleRec*	SamplePtr;

		if (allowedsamples)											//RJS 03Dec96
		{
			SamplePtr = LoadSample(thefile);
			if (SamplePtr)
			{
				ChannelPtr = FindFreeHandler(SamplePtr,NULL,OldChannelPtr);	//RJS 17Oct97
				if (ChannelPtr)												//RJS 17Oct97
				{
					allowedsamples--;										//RJS 03Dec96
					SetUpSample(ChannelPtr,SamplePtr,vol,vol>>8,pan,NULL);	//RJS 17Oct97
					AIL_start_sample(ChannelPtr->handler);
				}
			}
		}
	}
}
		
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OverrideSample
//Author		Robert Slater
//Date			Mon 4 Mar 1996
//
//Description	Hard start a sample on a known handler
//
//Inputs		Sound queue index, sample index, volume, pan and frequency
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::OverrideSample(SQueuePtr ChannelPtr, FileNum	thefile, SLong	vol, SLong	pan,SLong	newfreq)
{
	SampleRec*	SamplePtr = LoadSample(thefile);

	if (SamplePtr && ChannelPtr)									//RJS 17Oct97
	{
//DeadCode RJS 09Apr99 		SLong	thevol = (SamplePtr->samplevolume * vol) >> 7;		//RJS 19May98
		//Volume is virtual (32k)					
		SLong	thevol = vol >> 8;								//RJS 09Apr99

		if (AIL_sample_status(ChannelPtr->handler) == SMP_PLAYING)//RJS 17Oct97
			AIL_end_sample(ChannelPtr->handler);				//RJS 09Apr99

		SetUpSample(ChannelPtr,SamplePtr,vol,thevol,pan,NULL);		//RJS 19May98
	
		if (newfreq > -1)
		{
			AIL_set_sample_playback_rate(ChannelPtr->handler,newfreq);//RJS 13Nov96
			AIL_set_sample_loop_count(ChannelPtr->handler,0);		//RJS 27Nov96
		}

		AIL_start_sample(ChannelPtr->handler);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopSample
//Author		Robert Slater
//Date			Mon 15 Jul 1996
//
//Description	Stops a sample in the sample queue, depending on which item
//				had recently requested it.
//
//Inputs		The sample file name,
//				The item pointer.
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopSample(FileNum	thefile, ItemBasePtr	sampleitem)
{
	Log_Stack.Check(LogStack::MOVECODE);
	int	count;
	int	spos = GetIndex(thefile);
	int	lastpos = GetIndex(FIL_SFX_LASTSOUND);
	SQueuePtr	ChannelPtr = soundqueue;						//RJS 21Oct97

	if ((spos >= 0) && (spos < lastpos))						//RJS 21Oct96
	{
		SampleRec*	SamplePtr = &thesample[spos];
		if (sampleitem)
		{	
			for (count = 0; count < status.nohandlers; count++)	//RJS 21Oct97
			{													//RJS 21Oct97
				if (	(ChannelPtr->sampleindex == SamplePtr)	//RJS 21Oct97
					&&	(ChannelPtr->worlditem == sampleitem) )	//RJS 21Oct97
					HardStop(ChannelPtr);						//RJS 21Oct97
																//RJS 21Oct97
				ChannelPtr++;									//RJS 21Oct97
			}													//RJS 21Oct97
		}
		else
		{
			for (count = 0; count < status.nohandlers; count++)	//RJS 21Oct97
			{													//RJS 21Oct97
				if (ChannelPtr->sampleindex == SamplePtr)		//RJS 21Oct97
					HardStop(ChannelPtr);						//RJS 21Oct97
																//RJS 21Oct97
				ChannelPtr++;									//RJS 21Oct97
			}													//RJS 21Oct97
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HardStop
//Author		Robert Slater
//Date			Fri 8 Mar 1996
//
//Description	Hard stops the sample from playing
//
//Inputs		Position in sample handler queue
//
//Returns		
//
//------------------------------------------------------------------------------
void	Miles::HardStop(SQueuePtr	ChannelPtr)
{
	if (dig)													//RJS 26Sep96
	{
 		if (AIL_sample_status(ChannelPtr->handler) == SMP_PLAYING)//RJS 21Oct97
			AIL_end_sample(ChannelPtr->handler);				//RJS 21Oct97

		if (ChannelPtr == EngineSound.ChanPtr)					//RJS 21Oct97
		{
//DeadCode RJS 21May98 			EngineSound.CurrentFile = FIL_NULL;					//RJS 21Oct97
			EngineSound.Playing = FALSE;						//RJS 21Oct97
			if (AIL_sample_status(EngineSound.SubChanPtr->handler) == SMP_PLAYING)
				AIL_end_sample(EngineSound.SubChanPtr->handler);	
		}

		ChannelPtr->sampleindex = NULL;							//RJS 21Oct97
		ChannelPtr->looping = FALSE;							//RJS 21Oct97
		ChannelPtr->worlditem = NULL;							//RJS 21Oct97
 		ChannelPtr->GameSound = FALSE;							//RJS 21Oct97
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateEngine
//Author		Robert Slater
//Date			Tue 3 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::UpdateEngine()
{
	if (EngineSound.isInitialised)								//RJS 25May99
	{
		if (EngineSound.CurrentFile != FIL_NULL)
		{
			SLong		NewFreq = EngineSound.Freq;						//RJS 21Oct97

			if (thesample[GetIndex(EngineSound.CurrentFile)].blockptr && !EngineSound.Changed)	//RJS 09Apr99
			{
				SLong	thewindvol = EngineSound.WindVolume >> 8;
				SLong	therumblevol = EngineSound.RumbleVolume >> 8;

				if (EngineSound.Playing)								//RJS 21Oct97
				{
					if (EngineSound.IsJet)//RJS 06Oct98
					{
						if (	(NewFreq > 4000)							//RJS 21Oct97
							&&	(NewFreq < 44100))							//RJS 21Oct97
							AIL_set_sample_playback_rate(EngineSound.SubChanPtr->handler,NewFreq);//RJS 26Jun98
					}
					else
					{
						if (	(NewFreq > 4000)							//RJS 21Oct97
							&&	(NewFreq < 44100))							//RJS 21Oct97
							AIL_set_sample_playback_rate(EngineSound.ChanPtr->handler,NewFreq);//RJS 26Jun98
					}

					if (therumblevol > 127)	therumblevol = 127;
					AIL_set_sample_volume(EngineSound.ChanPtr->handler,therumblevol);
				}
				else
				{
					if (thewindvol > 127)	thewindvol = 127;
					AIL_set_sample_volume(EngineSound.ChanPtr->handler,thewindvol);//RJS 21Oct97
				}
			}
			else
			{
				if (EngineSound.Playing)								//RJS 21Oct97
				{
					if (EngineSound.IsJet)
					{
						OverrideSample(	EngineSound.ChanPtr,				//RJS 21Oct97
										EngineSound.CurrentFile,			//RJS 21Oct97
										EngineSound.RumbleVolume,			//RJS 26Jun98
										0,									//RJS 21Oct97
										11025);								//RJS 26Jun98

						OverrideSample(	EngineSound.SubChanPtr,
										EngineSound.CurrentSubFile,
										EngineSound.SubHarmonicVolume,
										0,
										NewFreq);
					}
					else
					{
						OverrideSample(	EngineSound.ChanPtr,				
										EngineSound.CurrentFile,	
										EngineSound.RumbleVolume,
										0,					
										NewFreq);	
					
						//Boost sound too?
					}
				}
				else							
					OverrideSample(	EngineSound.ChanPtr,				//RJS 21Oct97
									EngineSound.CurrentFile,			//RJS 21Oct97
									EngineSound.WindVolume,				//RJS 21Oct97
									0,									//RJS 21Oct97
									11025);								//RJS 21Oct97

	//			if (EngineSound.OldFile != FIL_NULL)					//RJS 08Jul98
	//				DeleteSample(EngineSound.OldFile);					//RJS 08Jul98
			}
		}
	}
	EngineSound.Changed = FALSE;									//RJS 09Apr99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayEngine
//Author		Robert Slater
//Date			Tue 3 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayEngine(SLong	CockpitNobble,AirStrucPtr	ac, SLong	rpm, SLong	vel,SWord thrustp)
{
	Log_Stack.Check(LogStack::MOVECODE);
	if (Save_Data.vol.sfx && EngineSound.Volume)					//RJS 18Jan99
	{
		SLong	revgap;
		SLong	revlimit;
		SLong	Maxvol = EngineSound.Volume;						//RJS 21Oct97
		SLong	RumbleVol;
		SLong	wvol;												//RJS 18Jan99
		FileNum	newSound;
		ClassPtr	classtype = ac->classtype;

		EngineSound.WindVolume = (vel * Maxvol)/4000;

		EngineSound.isInitialised = TRUE;						//RJS 25May99

		if (CockpitView)
		{
			// vel is in 10ms, max wind vol is 1000 10ms,
			// max damage is 255...
			wvol = (Maxvol * CockpitNobble * vel)/255000;			//RJS 18Jan99
			if (wvol > Maxvol)
				wvol = Maxvol;

			EngineSound.CockpitWind = wvol;
			if (CockpitNobble < 192)
				EngineSound.InCockpit = TRUE;
			else
				EngineSound.InCockpit = FALSE;
		}
		else
		{
			EngineSound.InCockpit = FALSE;
			if (EngineSound.CockpitWind)
				StopSample(FIL_SFX_WIND_COCKPIT_LOOP);

			EngineSound.CockpitWind = 0;
		}

//		if (	(rpm > classtype->minrpm)
		if (EngineSound.Dying == FALSE)
		{
			EngineSound.Playing = TRUE;							//RJS 21Oct97

			if (!EngineSound.InCockpit)											//RJS 19May98
				newSound = (FileNum) (classtype->enginesnd + 1);				//RJS 08Jul98
			else																//RJS 19May98
				newSound = classtype->enginesnd;								//RJS 08Jul98

			if (newSound != EngineSound.CurrentFile)					//RJS 08Jul98
			{
				EngineSound.OldFile = EngineSound.CurrentFile;			//RJS 08Jul98
				EngineSound.Changed = TRUE;									//RJS 09Apr99
			}

			if (thrustp < 0)	thrustp = 0;								//RJS 09Apr99
			if (thrustp > 256)	thrustp = 256;								//RJS 09Apr99

			if (EngineSound.IsJet)
			{
				rpm -= 3975;
				EngineSound.Freq = 11025 + (4000*rpm/3975);

				RumbleVol = Maxvol - (Maxvol/16);
//Dead				EngineSound.SubHarmonicVolume = (Maxvol / 4)>>8;
				EngineSound.SubHarmonicVolume = Maxvol / 4;							//RJS 09Apr99
				EngineSound.CurrentSubFile = (FileNum) (newSound + 2);				//RJS 08Jul98

//Dead				if (thrustp < 0)	thrustp = 0;
//Dead				if (thrustp > 256)	thrustp = 256;								//RJS 09Apr99

				EngineSound.RumbleVolume = (RumbleVol * thrustp)>>8;			//RJS 14Jan99
			}
			else
			{
				//pistoff
				rpm -= 3975;
				EngineSound.Freq = 11025 + (4000*rpm/3975);

				//Never let vol go to zero for prop...
				RumbleVol = (Maxvol*2)/3;
				EngineSound.RumbleVolume = (Maxvol/3) + ((RumbleVol * thrustp)>>8);

				//Boost thing...
			}

			EngineSound.CurrentFile = newSound;									//RJS 08Jul98

			revgap = (classtype->maxdiverpm - classtype->maxrpm)>>1;
			revlimit = classtype->maxrpm + revgap;

			if (rpm > revlimit)
			{
				if (revgap)
					EngineSound.OverRevving = ((rpm - revlimit) * Maxvol) / revgap;//RJS 21Oct97
				else
					EngineSound.OverRevving = (rpm - revlimit) * Maxvol;//RJS 21Oct97

				EngineSound.OverRevFreq = 11025 + ((rpm - revlimit) << 2);
			}
			else
				EngineSound.OverRevving = 0;
		}
//		else
//		{
//			if (EngineSound.CurrentFile != FIL_SFX_WIND_LOOP)	//RJS 08Jul98
//				EngineSound.OldFile = EngineSound.CurrentFile;	//RJS 08Jul98
  //
	//		EngineSound.Playing = FALSE;						//RJS 21Oct97
	//		EngineSound.Freq = -1;								//RJS 21Oct97
	//		EngineSound.OverRevving = 0;						//RJS 21Oct97
	//		EngineSound.CurrentFile = FIL_SFX_WIND_LOOP;		//RJS 21Oct97
//		}

//Dead		EngineSound.WindVolume >>= 8;							//RJS 21Oct97
																//RJS 21Oct97
		if (!EngineSound.WindVolume)							//RJS 21Oct97
			EngineSound.WindVolume = 1;							//RJS 21Oct97
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OverRevCheck
//Author		Robert Slater
//Date			Tue 1 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::OverRevCheck()
{
	if (EngineSound.isInitialised)								//RJS 25May99
	{
/*	if (!EngineSound.IsJet && EngineSound.OverRevving)			//RJS 09Apr99
	{
		SQueuePtr	ChannelPtr;										//RJS 17Oct97
		SQueuePtr	OldChannelPtr;									//RJS 17Oct97
		SampleRec*	SamplePtr;										//RJS 17Oct97
		int	vol;
		int	freq;
		int	volfrac = EngineSound.OverRevving;						//RJS 21Oct97
		int	thevol;												//RJS 27Nov96
		SLong	MaxVol = EngineSound.Volume;						//RJS 21Oct97

		SamplePtr = LoadSample(FIL_SFX_OVERREVVING_LOOP1);			//RJS 17Oct97
		if (SamplePtr)												//RJS 17Oct97
		{
			vol = ClipVolume(MaxVol,volfrac);						//RJS 21Oct97
			thevol = vol >> 8;										//RJS 27Nov96

			if (thevol)
			{
				ChannelPtr = FindFreeHandler(SamplePtr,NULL,OldChannelPtr,3);
				if (ChannelPtr)
				{
					SetUpSample(ChannelPtr,SamplePtr,MaxVol,thevol,0,NULL);//RJS 21Oct97
					AIL_set_sample_loop_count(ChannelPtr->handler,3);//RJS 26Nov96
					ChannelPtr->looping = TRUE;
					AIL_start_sample(ChannelPtr->handler);
				}
				else
				{
					if (OldChannelPtr)								//RJS 17Oct97
					{
	//					AIL_lock();									//RJS 05Dec96
						if (AIL_sample_status(OldChannelPtr->handler) == SMP_PLAYING)//RJS 17Oct97
						{			
							thevol = ClipVolume(127,thevol);
			 				AIL_set_sample_volume(OldChannelPtr->handler,thevol);//RJS 17Oct97
							AIL_set_sample_playback_rate(OldChannelPtr->handler,EngineSound.OverRevFreq);//RJS 21Oct97
						}											
	//					AIL_unlock();								//RJS 05Dec96
					}
				}
			}
		}
	}*/
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopEngine
//Author		Robert Slater
//Date			Fri 8 Mar 1996
//
//Description	Stops the engine sample, so wind can kick in
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopEngine(int	velocity)
{
	Log_Stack.Check(LogStack::MOVECODE);
	if (Save_Data.vol.sfx > 0)									//RJS 03Apr97
	{												
		HardStop(EngineSound.ChanPtr);							//RJS 21Oct97
//		HardStop(EngineSound.SubChanPtr);//RJS 03Sep98
		StopSample(FIL_SFX_OVERREVVING_LOOP1);		
		EngineSound.Playing = TRUE;								//RJS 21Oct97
		EngineSound.Dead = TRUE;								//RJS 21Oct97
		EngineSound.Dying = TRUE;								//RJS 21Oct97
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayLooped
//Author		Robert Slater
//Date			Thu 9 May 1996
//
//Description	Starts a sample for the gunfire and loops it continuously
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayLooped(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol, UByte	looplength, Bool sound3d)
{
	if (delayedstate)
		PlayDelayed(thefile,sampleitem,vol,TRUE);
	else
	{
		Log_Stack.Check(LogStack::MOVECODE);
		SQueuePtr	ChannelPtr;										//RJS 17Oct97
		SQueuePtr	OldChannelPtr;									//RJS 17Oct97
		SampleRec*	SamplePtr;										//RJS 17Oct97
		SLong	thevol;												//RJS 05Dec96
		int	thepan;													//RJS 05Dec96
		SLong	distance;

		SamplePtr = LoadSample(thefile);
		if (SamplePtr)
		{
			if (	allowedsamples											//RJS 23Jun99
				||	(sampleitem == Manual_Pilot.ControlledAC2)	)
			{
				thevol = (SamplePtr->samplevolume * vol) >> 7;			//RJS 17Oct97
				vol = thevol;												//RJS 05Dec96

				if (sampleitem)												//RJS 05Dec96
					thepan = SoundInWorld(sampleitem->World,thevol,distance);//RJS 16Oct97
				else
				{
					thepan = 0;
					thevol >>= 8;
				}

				if (thevol)
				{
					ChannelPtr = FindFreeHandler(SamplePtr,sampleitem,OldChannelPtr,looplength);//RJS 17Oct97
					if (ChannelPtr)										//RJS 23Jun99
					{
						allowedsamples--;										//RJS 04Dec96

						SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,sampleitem);//RJS 05Dec96
						AIL_set_sample_loop_count(ChannelPtr->handler,looplength);
						ChannelPtr->looping = TRUE;
						ChannelPtr->GameSound = sound3d;
						AIL_start_sample(ChannelPtr->handler);
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayLanded
//Author		Robert Slater
//Date			Mon 22 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayLanded(ItemBasePtr	sampleitem, SLong	velocity, Bool skid)
{
	Log_Stack.Check(LogStack::MOVECODE);
	SQueuePtr	ChannelPtr;										//RJS 17Oct97
	SQueuePtr	OldChannelPtr;									//RJS 17Oct97
	SampleRec*	SamplePtr;										//RJS 17Oct97
	int	vol;
	int	freq;
	int	thevol;

	if (allowedsamples)											//RJS 03Dec96
	{
		allowedsamples--;										//RJS 03Dec96

		SamplePtr = LoadSample(FIL_SFX_LANDING_GRASS_LOOP);			//RJS 14Jan99
		if (SamplePtr)												//RJS 17Oct97
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) ((mobileitem*)sampleitem)->Anim;
			SLong	legtally = 0;
			SLong	maxvol = SamplePtr->samplevolume;			//RJS 23Feb99
			SLong	thisvol = SamplePtr->samplevolume;			//RJS 23Feb99

			if (!adptr->acleglowerl)							//RJS 10May99
				legtally++;

			if (!adptr->acleglowerr)							//RJS 10May99
				legtally++;

			if (!adptr->acleglowerf)							//RJS 10May99
				legtally++;

			if (!adptr->acleglowerb)							//RJS 10May99
				legtally++;

			maxvol *= legtally;
			maxvol /= 3;			// Probably only ever get 3 wheels at once
			if (maxvol)
			{
				maxvol *= velocity;
				maxvol /= 7500;			//(ie. 75m/s * 100)

				bouncecount = 100;
				vol = ClipVolume(thisvol,maxvol);				//RJS 23Feb99
				thevol = vol >> 8;											//RJS 27Nov96

				if (skid)										//RJS 13Jan99
				{
					// Perhaps check ground type.....


					SLong	skidvol = (128 * vol)/thisvol;		//RJS 23Feb99

					PlayLooped(FIL_SFX_TYRE_SCREECH1,sampleitem,skidvol);
				}

				if (thevol)													//RJS 27Nov96
				{
					ChannelPtr = FindFreeHandler(SamplePtr,sampleitem,OldChannelPtr);//RJS 17Oct97
					freq = 11025 + (vol/3);
					onground = TRUE;

					if (ChannelPtr)
					{
						SetUpSample(ChannelPtr,SamplePtr,vol,thevol,0,sampleitem);//RJS 17Oct97
						AIL_set_sample_loop_count(ChannelPtr->handler,4);//RJS 21May99
						ChannelPtr->looping = TRUE;						//RJS 17Oct97
						AIL_start_sample(ChannelPtr->handler);			//RJS 17Oct97
					}
					else
					{
						if (OldChannelPtr)							//RJS 17Oct97
						{
	//						AIL_lock();									//RJS 05Dec96
							if (AIL_sample_status(OldChannelPtr->handler) == SMP_PLAYING)//RJS 17Oct97
							{
								thevol = ClipVolume(127,thevol);
								AIL_set_sample_volume(OldChannelPtr->handler,thevol);//RJS 17Oct97
								AIL_set_sample_playback_rate(OldChannelPtr->handler,freq);//RJS 17Oct97
							}											
	//						AIL_unlock();								//RJS 05Dec96
						}
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopLanded
//Author		Robert Slater
//Date			Tue 23 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopLanded()
{
	onground = FALSE;

	if (bouncecount > 0)
		bouncecount--;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayOnce
//Author		Robert Slater
//Date			Fri 19 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayOnce(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol, FileNum	stsam, FileNum	endsam)
{
	if (delayedstate)
		PlayDelayed(thefile,sampleitem,vol,FALSE,stsam,endsam);
	else
	{
		Log_Stack.Check(LogStack::MOVECODE);
		SQueuePtr	ChannelPtr;										//RJS 17Oct97
		SampleRec*	SamplePtr;										//RJS 17Oct97
		int			spos;
		int	stblock = 0;
		int	endblock = 0;
		SLong	thevol;												//RJS 05Dec96
		int	thepan;													//RJS 05Dec96
		SLong	distance;

		SamplePtr = LoadSample(thefile);
		if (SamplePtr)
		{
			if (allowedsamples || (sampleitem == Manual_Pilot.ControlledAC2))	//RJS 23Jun99
			{
				thevol = (SamplePtr->samplevolume * vol) >> 7;			//RJS 27Nov96
				vol = thevol;												//RJS 05Dec96

				spos = GetIndex(thefile);
				stblock = spos - 1;											//RJS 19Nov96
				endblock = spos + 1;										//RJS 19Nov96

				if (	(stsam != FIL_NULL)
					&&	(endsam != FIL_NULL)	)
				{
					stblock = GetIndex(stsam) - 1;
					endblock = GetIndex(endsam) + 1;
				}

				if (sampleitem)												//RJS 05Dec96
					thepan = SoundInWorld(sampleitem->World,thevol,distance);//RJS 16Oct97
				else
				{
					thepan = 0;
					thevol >>= 8;
				}

				if (thevol)													//RJS 23Jun99
				{
					SQueuePtr	OldChannelPtr;

					ChannelPtr = FindFreeHandlerOnce(SamplePtr,sampleitem,OldChannelPtr,stblock,endblock);//RJS 29Jan99
					if (ChannelPtr)										//RJS 17Oct97
					{
						allowedsamples--;									//RJS 05Dec96

						SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,sampleitem);//RJS 17Oct97
						AIL_start_sample(ChannelPtr->handler);			//RJS 17Oct97
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayOnce
//Author		Robert Slater
//Date			Thu 26 Sep 1996
//
//Description	Simplified version for static items
//
//Inputs		pan is in rowan angles...
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayOnce(FileNum	thefile, int	vol, SLong thepan)
{
	if (delayedstate)
		PlayDelayed(thefile,NULL,vol,FALSE);
	else
	{
		Log_Stack.Check(LogStack::MOVECODE);
		SQueuePtr	ChannelPtr;										//RJS 17Oct97
		SampleRec*	SamplePtr;										//RJS 17Oct97
		int	spos;													//RJS 17Oct97
		int	stblock = 0;
		int	endblock = 0;
		ItemBasePtr	sampleitem = NULL;
		int	thevol;													//RJS 27Nov96

		SamplePtr = LoadSample(thefile);
		if (SamplePtr)
		{
			SQueuePtr	OldChannelPtr;

			spos = GetIndex(thefile);

			thevol = (SamplePtr->samplevolume * vol) >> 7;			//RJS 27Nov96
			vol = thevol;												//RJS 05Dec96

			thevol >>= 8;

			stblock = spos - 1;											//RJS 19Nov96
			endblock = spos + 1;										//RJS 19Nov96

			ChannelPtr = FindFreeHandlerOnce(SamplePtr,sampleitem,OldChannelPtr,stblock,endblock);//RJS 29Jan99
			if (ChannelPtr && allowedsamples)							//RJS 17Oct97
			{
				allowedsamples--;										//RJS 05Dec96

				RowanToPan(thepan);

				SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,sampleitem);//RJS 28Jan99
				AIL_start_sample(ChannelPtr->handler);				//RJS 17Oct97
			}
			else
			{
				if (OldChannelPtr)						//RJS 29Jan99...
				{
					if (AIL_sample_status(OldChannelPtr->handler) == SMP_PLAYING)
					{
						RowanToPan(thepan);
						thevol = ClipVolume(127,thevol);
						AIL_set_sample_volume(OldChannelPtr->handler,thevol);
						AIL_set_sample_pan(OldChannelPtr->handler,ClipPan(thepan));
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopAll
//Author		Robert Slater
//Date			Thu 9 May 1996
//
//Description	Halts all the sound samples
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopAll()
{
	int	qpos;

	if (dig)													//RJS 26Sep96
	{
		for (qpos = 0; qpos < status.nohandlers; qpos ++)
			HardStop(&soundqueue[qpos]);						//RJS 21Oct97
	}

	EngineSound.Dying = FALSE;									
	EngineSound.Dead = FALSE;									
	EngineSound.Playing = FALSE;								
	EngineSound.CurrentFile = FIL_NULL;							
	EngineSound.OldFile = FIL_NULL;								
	EngineSound.Freq = 8000;									
	EngineSound.SubHarmonicFreq = 8000;							
	EngineSound.SubHarmonicVolume = 1;							
	EngineSound.WindVolume = 1;									
	EngineSound.OverRevving = 0;								
	EngineSound.OverRevFreq = 11025;							
	EngineSound.CockpitWind = 0;								
	EngineSound.InCockpit = TRUE;								
	EngineSound.RumbleVolume = 1;
	EngineSound.Changed = TRUE;
	EngineSound.isInitialised = FALSE;

	delayedsounds.isSet = FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteSample
//Author		Robert Slater
//Date			Tue 23 Jul 1996
//
//Description	Removes a sample from memory and frees its location
//
//Inputs		The sample file
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::DeleteSample(FileNum	thefile)
{
	DeleteSample(GetIndex(thefile));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteSample
//Author		Robert Slater
//Date			Thu 3 Oct 1996
//
//Description	Alternative private delete sample function
//
//Inputs		Internal sample number
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::DeleteSample(SLong	spos)
{
	if ((spos >= 0) && (spos < MAXSAMPLES_LOADED))				//MS 23Sep98
	{
		if (thesample[spos].blockptr)
		{
			delete thesample[spos].blockptr;
			thesample[spos].blockptr = NULL;	
		}
	}
	else
		_Error.EmitSysErr("Bullshit sample delete %d",spos);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeSamples
//Author		Robert Slater
//Date			Mon 4 Mar 1996
//
//Description	Frees all the samples in memory
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::FreeSamples()
{
	int	count;

	if (dig == NULL)
		return;

	for (count = 0; count < MAXSAMPLES_LOADED; count ++)		//MS 23Sep98
	{
		if (thesample[count].blockptr)
		{
			delete thesample[count].blockptr;
			
			thesample[count].blockptr = NULL;	
		}

	}

	status.nosamples = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeTunes
//Author		Robert Slater
//Date			Mon 4 Mar 1996
//
//Description	Frees all the tunes in memory	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::FreeTunes()
{
	int	tuneno;

	if (mdi == NULL)
		return;

	for (tuneno = 0; tuneno < MAXTUNES; tuneno++)
	{
		if (tune[tuneno].blockptr)
		{
			#ifdef	__DOS__
			VMM_unlock(getdata(tune[tuneno].blockptr),tune[tuneno].size);
			#endif
			delete tune[tuneno].blockptr;

			tune[tuneno].blockptr = NULL;
		}

	}

	status.notunes = 0;
}

	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShutDownMiles
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Close down all music drivers and free associated memory	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::ShutDownMiles()
{
	int		tuneno;
	int		count;
	SLong	result;

	StopAll();													//RJS 21Jul98

	_SndFonts.KillSFont();

	if (wavetable.wavesynth)
	{
		AIL_destroy_wave_synthesizer(wavetable.wavesynth);
		delete wavetable.blockptr;
	}

	if (wavetable.DLSwavesynth)
  		AIL_DLS_close(wavetable.DLSwavesynth,RETURN_TO_GM_ONLY_STATE);
		
	if (timer)
		AIL_release_timer_handle(timer-1);

	if (dls)
		AIL_midiOutClose(dls);

	if (mdi)
		AIL_midiOutClose(mdi);

	if (dig || mdi || timer)
		AIL_shutdown();

	FreeTunes();
	FreeSamples();
	
	wavetable.blockptr = NULL;
	dig = NULL;
	mdi = NULL;
	timer = NULL;
	delete []thesample;											//MS 23Sep98
	thesample = NULL;											//MS 23Sep98
	if (themusicsample)											//RJS 14Apr99
		delete []themusicsample;								//RJS 14Apr99
	themusicsample=NULL;										//RJS 14Apr99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GamePaused
//Author		Robert Slater
//Date			Fri 9 Aug 1996
//
//Description	Stops the engine sound
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::GamePaused()
{
	if (Save_Data.vol.sfx != 0)
	{
		if (AIL_sample_status(EngineSound.ChanPtr->handler) == SMP_PLAYING)
			AIL_stop_sample(EngineSound.ChanPtr->handler);
		else
			AIL_resume_sample(EngineSound.ChanPtr->handler);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetSoundFlags
//Author		Robert Slater
//Date			Fri 12 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::ResetSoundFlags()
{
	EngineSound.Dying = FALSE;									//RJS 21Oct97
	EngineSound.Dead = FALSE;									//RJS 21Oct97
	EngineSound.Playing = FALSE;								//RJS 21Oct97
	EngineSound.IsJet = FALSE;									//RJS 21Oct97
	EngineSound.CurrentFile = FIL_NULL;							//RJS 21Oct97
	EngineSound.OldFile = FIL_NULL;								//RJS 21Oct97
	EngineSound.Freq = 8000;									//RJS 21Oct97
	EngineSound.SubHarmonicFreq = 8000;							//RJS 21Oct97
	EngineSound.SubHarmonicVolume = 1;							//RJS 21Oct97
	EngineSound.WindVolume = 1;									//RJS 21Oct97
	EngineSound.OverRevving = 0;								//RJS 21Oct97
	EngineSound.OverRevFreq = 11025;							//RJS 21Oct97
	EngineSound.CockpitWind = 0;								//RJS 19May98
	EngineSound.InCockpit = TRUE;								//RJS 19May98
	EngineSound.RumbleVolume = 1;
	EngineSound.Changed = TRUE;
	EngineSound.isInitialised = FALSE;							//RJS 25May99

	canplaynothing = FALSE;

	inprefs = FALSE;											//RJS 29Nov96

	onground = FALSE;
	bouncecount = 0;
	delindex = 0;												//RJS 29Nov96
	allowedsamples = 1;											//RJS 25May99
	boffcount = 0;
	CockpitView = TRUE;

	lastBuffetVol = 0;											//RJS 28Jan99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetMidiFlags
//Author		Robert Slater
//Date			Thu 29 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::ResetMidiFlags()
{
	request.activated = INT_NULL;								//RJS 18Jun99
//Dead	request.fader = FALSE;
//Dead 	request.stopsequence = FALSE;
	request.wait = FALSE;
	request.todiscard = FALSE;
	request.killnow = FALSE;
	request.alonetuneno = NULL;									//RJS 26Feb98
	request.mainstopped = FALSE;								//RJS 12Nov96
	request.musictimeout = 0;									//RJS 18Jun99
	incombat = FALSE;											//RJS 12Nov96
	request.CurrentTrack = 0;
	Mood = MOOD_NEUTRAL;

	request.forcestop = 0;										//RJS 18Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitUI
//Author		Robert Slater
//Date			Tue 6 Apr 1999
//
//Description	Set up user interface handler for sfx
//				and Smacker
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::InitUI(int	wind)
{
	Bool	theresult = FALSE;
#ifndef _NO_MILES_AUDIO_
 	if (dig)
		StopAll();
	
 	if (NewDigitalDriver(NOM_SAMP_VAL,4,TRUE))
 	{
		HWND	thiswin = (HWND) wind;

		SmackSoundUseMSS (dig);
		AIL_set_DirectSound_HWND(dig,thiswin);
 		theresult = TRUE;

		SetVolumes(FALSE);
		SmackerOff();
 	}
#endif
	return(theresult);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Init3D
//Author		Dave Whiteside
//Date			Tue 6 Apr 1999
//
//Description	Set up 3d digital handler
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::Init3D()
{
	Bool	theresult = FALSE;									//RJS 30Oct96
#ifndef _NO_MILES_AUDIO_

	if (NewDigitalDriver(MIN_SAMP_VAL,MAXHANDLERS,FALSE))	
	{
		SetVolumes(FALSE);
		theresult = TRUE;
 	}
#endif
	playingMiller = false;										//RJS 21May99

	delayedsounds.isSet = FALSE;									//DAW 18Aug99
	percussionLog.Reset();										//DAW 18Aug99

	return(theresult);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGlobalVolumes
//Author		Robert Slater
//Date			Tue 13 Aug 1996
//
//Description	Sets the global volumes for sfx, midi and engine	
//
//Inputs		sfx vol, midi vol, engine vol
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetGlobalVolumes(int	sfxvol, int	midivol, int	engvol, int	smackervol, Bool	saveset)
{
	int	spos;
	TuneStrucP	TunePtr;

	inprefs = TRUE;												//RJS 06Dec96

	if (dig)
	{
		if (sfxvol > -1)
		{
 			if (sfxvol)
 				AIL_set_digital_master_volume(dig,127);			//RJS 09Mar98
//DeadCode RJS 09Mar98  				AIL_set_digital_master_volume(dig,sfxvol);

			Save_Data.vol.sfx = sfxvol;							//RJS 09Dec96
		}

		if (engvol > -1)
			EngineSound.Volume = (EngineSound.VolLoaded * engvol) >> 7;//RJS 18Jan99
		else
			EngineSound.Volume = 0;

		if (smackervol > -1)
		 	thesmackervol = smackervol;
	}
	else
		Save_Data.vol.sfx = 0;

	if (mdi)
	{
		if (midivol > -1)
		{
			if (!saveset)
			{
				if (midivol == 0)
				{
					DiscardMusic();
					Save_Data.vol.music = 0;
				}
				else
				{
					Save_Data.vol.music = midivol;

					TunePtr = LoadTune(FIL_MUSIC_OBJECTIVE_FAILED);
					if (TunePtr)
					{
			 			if (AIL_sequence_status(tune[0].sequence[0]) == SEQ_DONE)
							request.alonetuneno = NULL;
					}
				}
			}

			AIL_set_XMIDI_master_volume(mdi,midivol);
		}
	}
	else
		Save_Data.vol.music = 0;

//	SavedMusic = Save_Data.vol.music;
//	SavedSfx = Save_Data.vol.sfx;
//	SavedUISfx = Save_Data.vol.uisfx;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSampleVolumes
//Author		Robert Slater
//Date			Thu 3 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::GetSampleVolumes()
{
	int			novolumes=0;									//RJS 23Feb99
	int			count;											//RJS 23Feb99
	SLongP		volptr;											//RJS 23Feb99
																//RJS 23Feb99
	theblock = new fileblock (FIL_SFX_VOLUMES);					//RJS 23Feb99
	if (theblock)												//RJS 23Feb99
	{															//RJS 23Feb99
		volptr = (SLongP) getdata(theblock);					//RJS 23Feb99
																//RJS 23Feb99
		novolumes = *volptr;									//RJS 23Feb99
		volptr++;												//RJS 23Feb99
																//RJS 23Feb99
		if (novolumes > MAXSAMPLES)								//RJS 23Feb99
			novolumes = MAXSAMPLES;								//RJS 23Feb99
																//RJS 23Feb99
		thesample = new SampleRec[novolumes];					//RJS 23Feb99
		if (thesample)											//RJS 23Feb99
		{														//RJS 23Feb99
			MAXSAMPLES_LOADED = novolumes;						//RJS 23Feb99
			count = 0;											//RJS 23Feb99
			SLong	maxvol,boost;								//RJS 23Feb99
																//RJS 23Feb99
			do													//RJS 23Feb99
			{													//RJS 23Feb99
				maxvol = *volptr++;								//RJS 23Feb99
				boost = *volptr++;								//RJS 23Feb99
																//RJS 23Feb99
				maxvol *= boost;								//RJS 23Feb99
				maxvol /= 100;									//RJS 23Feb99
																//RJS 23Feb99
				thesample[count++].samplevolume = maxvol;		//RJS 23Feb99
			}													//RJS 23Feb99
			while (count < novolumes);							//RJS 23Feb99
																//RJS 23Feb99
//DeadCode RJS 11Jun99 			EngineSound.VolLoaded = thesample[GetIndex(FIL_SFX_JET_EXTERNAL_LOOP)].samplevolume;//RJS 23Feb99
			EngineSound.VolLoaded = 32768;						//RJS 11Jun99
		}														//RJS 23Feb99
		else													//RJS 23Feb99
			Save_Data.vol.sfx = 0;								//RJS 23Feb99
																//RJS 23Feb99
		delete theblock;										//RJS 23Feb99
	}															//RJS 23Feb99
	else														//RJS 23Feb99
		Save_Data.vol.sfx = 0;									//RJS 23Feb99
}												

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDirectSoundWindow
//Author		Robert Slater
//Date			Mon 18 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetDirectSoundWindow(ULong	newwin)
{
	if (dig)
	{
		HWND	thiswin = (HWND) newwin;

		AIL_set_DirectSound_HWND(dig,thiswin);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCompressedDLS
//Author		Robert Slater
//Date			Mon 18 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetCompressedDLS(TuneStrucP TunePtr, void*	ptr, SLong	size)
{
	SLong	resval = AIL_extract_DLS(ptr,
									 size,
									 &TunePtr->xmiPtr,
									 0,
									 &TunePtr->dlsPtr,
									 0	);

	if (TunePtr->dlsPtr)
	{
		TunePtr->dlsID = AIL_DLS_load_memory(wavetable.DLSwavesynth,
				 							 TunePtr->dlsPtr,
				 							 0						);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUncompressedDLS
//Author		Robert Slater
//Date			Mon 18 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetUncompressedDLS(TuneStrucP TunePtr, void* ptr, SLong	size)
{
	SLong	resval = AIL_find_DLS(	ptr,
									size,
									&TunePtr->xmiPtr,
									0,
									&TunePtr->dlsPtr,
									0	);

	if (TunePtr->dlsPtr)
	{
		TunePtr->dlsID = AIL_DLS_load_memory(wavetable.DLSwavesynth,
											 TunePtr->dlsPtr,
											 0						);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetXMidi
//Author		Robert Slater
//Date			Tue 19 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetXMidi(TuneStrucP	TunePtr)
{
	if (TunePtr->xmiPtr)
	{
		SLong		result, size;
		void		*tmpptr;
		SLong		*headptr;
		int			count;
		UWord		noforms = 0;
		SLong		header;
		HSEQUENCE	tmphandle = NULL;

		// Get IFF_ number of sequences information from header...
		headptr = (SLongP) TunePtr->xmiPtr;

		for (count = 0; count < 5; count ++)
			header = *headptr++;

		noforms = (UWord) *headptr;

		TunePtr->nosequences = noforms;
		if (	(TunePtr->ttype == T_independent)				//RJS 06May99
			||	(TunePtr->ttype == T_independent_pri)	)		//RJS 06May99
		{
			tmphandle = tune[GetIndex(FIL_MUSIC_MAIN)].sequence[0];
			if (tmphandle == NULL)
				LoadTune(FIL_MUSIC_MAIN);				
			tmphandle = tune[GetIndex(FIL_MUSIC_MAIN)].sequence[0];
		}
		else
		{
			if (TunePtr->sequence[0] == NULL)
				tmphandle = AIL_allocate_sequence_handle(mdi);
			else
				tmphandle = TunePtr->sequence[0];
		}

		for (count = 0; count < TunePtr->nosequences; count ++)
		{
			TunePtr->sequence[count] = tmphandle;		
			if (TunePtr->sequence[count] == NULL)
			{
				AIL_shutdown();

				_Error.EmitSysErr(AIL_last_error());
			}
		}
	}
	else
	{
		AIL_shutdown();
		_Error.EmitSysErr("Not an XMIDI file!");
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDLS
//Author		Robert Slater
//Date			Tue 19 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetDLS(TuneStrucP	TunePtr)
{
	if (TunePtr->dlsPtr)
	{
		SLong		result, size;
		void		*tmpptr;
		SLong		*headptr;
		int			count;
		UWord		noforms = 0;
		SLong		header;
		HSEQUENCE	tmphandle = NULL;

		noforms = TunePtr->nosequences;
		if (TunePtr->ttype == T_independent)
		{
			tmphandle = tune[GetIndex(FIL_MUSIC_MAIN)].DLSsequence[0];
			if (tmphandle == NULL)
				LoadTune(FIL_MUSIC_MAIN);				
			tmphandle = tune[GetIndex(FIL_MUSIC_MAIN)].DLSsequence[0];
		}
		else
		{
			if (TunePtr->DLSsequence[0] == NULL)
				tmphandle = AIL_allocate_sequence_handle(mdi);
			else
				tmphandle = TunePtr->DLSsequence[0];
		}

		for (count = 0; count < noforms; count ++)
		{
			TunePtr->DLSsequence[count] = tmphandle;		
			if (TunePtr->DLSsequence[count] == NULL)
			{
				AIL_shutdown();

				_Error.EmitSysErr(AIL_last_error());
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCockpit
//Author		Robert Slater
//Date			Wed 20 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetCockpit(Bool	thecock)
{
	CockpitView = thecock;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetVP
//Author		Robert Slater
//Date			Thu 21 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetVP(mobileitem *vp)
{
	View_Point = vp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayWind
//Author		Robert Slater
//Date			Wed 20 May 1998
//
//Description	Plays cockpit wind, adjusting the volume on-the-fly
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayWind()
{
	Log_Stack.Check(LogStack::MOVECODE);
	if (Save_Data.vol.sfx != 0)
	{
		SQueuePtr	ChannelPtr;								   
		SQueuePtr	OldChannelPtr;							   
		SampleRec*	SamplePtr;								   
		int			vol;
		int			thevol;											   

		SamplePtr = LoadSample(FIL_SFX_WIND_COCKPIT_LOOP);	   
		if (SamplePtr)										   
		{
			vol = EngineSound.CockpitWind;			//RJS 18Jan99
			thevol = vol >> 8;								   

			if (thevol)
			{
				ChannelPtr = FindFreeHandler(SamplePtr,NULL,OldChannelPtr,3);
				if (ChannelPtr)
				{
					SetUpSample(ChannelPtr,SamplePtr,vol,thevol,0,NULL);
					AIL_set_sample_loop_count(ChannelPtr->handler,3);
					ChannelPtr->looping = TRUE;
					AIL_start_sample(ChannelPtr->handler);
				}
				else
				{
					if (OldChannelPtr)				
					{
	//					AIL_lock();									
						if (AIL_sample_status(OldChannelPtr->handler) == SMP_PLAYING)
						{
							if (thevol > 127)	thevol = 127;
			 				AIL_set_sample_volume(OldChannelPtr->handler,thevol);
						}
	//					AIL_unlock();								
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayFlyAway
//Author		Robert Slater
//Date			Mon 1 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayFlyAway(ItemBasePtr	sampleitem)
{
	Log_Stack.Check(LogStack::MOVECODE);
	if (Save_Data.vol.sfx)										//RJS 31May99
	{
		if (EngineSound.CurrentFile < FIL_SFX_LOOP_FX_START)
		{
			StopEngine();
			if (EngineSound.CurrentFile < FIL_SFX_P51_TAXI_INT_LOOP)
				PlayOnce(FIL_SFX_JET_FLYAWAY,sampleitem);
			else
				PlayOnce(FIL_SFX_P51_FLYAWAY,sampleitem);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleFinished
//Author		Robert Slater
//Date			Tue 9 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::SampleFinished(UByteP	QueuePtr, bool hipriset)
{
	Log_Stack.Check(LogStack::MOVECODE);
	Bool		retval = FALSE;

	if (dig)													//RJS 31May99
	{
		SQueuePtr	ChannelPtr = (SQueuePtr) QueuePtr;
		if (ChannelPtr)
		{
			if (	(AIL_sample_status(ChannelPtr->handler) == SMP_DONE)
				||	hipriset											)
			{
				if (hipriset)
					AIL_end_sample(ChannelPtr->handler);

				ChannelPtr->sampleindex = NULL;						
				ChannelPtr->playingvolume = 0;							
				ChannelPtr->worlditem = NULL;							
				ChannelPtr->GameSound = FALSE;								
				ChannelPtr->looping = FALSE;
				ChannelPtr->isRadio = FALSE;

				retval = TRUE;
			}
		}
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlaySampleRadio
//Author		Robert Slater
//Date			Tue 9 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP	Miles::PlaySampleRadio(UByteP	DataPtr, int Size, SWord volscale, int Frequency, int noBits)
{
	Log_Stack.Check(LogStack::MOVECODE);
	SQueuePtr	ChannelPtr=NULL;
	if (dig)													//DAW 25May99
	{
		if (Save_Data.vol.rchat)								//RJS 30Jun99
		{														//RJS 30Jun99
			ChannelPtr = FindFreeRadioHandler();				//RJS 30Jun99
			if (ChannelPtr)										//RJS 30Jun99
			{
				SWord	theVol = (volscale * Save_Data.vol.rchat)>>7;//RJS 30Jun99

				ChannelPtr->sampleindex = NULL;						
				ChannelPtr->playingvolume = 0;							
				ChannelPtr->worlditem = NULL;							
				ChannelPtr->GameSound = FALSE;								
				ChannelPtr->isRadio = TRUE;								
				ChannelPtr->looping = FALSE;								

				AIL_init_sample(ChannelPtr->handler);									
				AIL_set_sample_type(ChannelPtr->handler,DIG_F_MONO_8,0);				
				AIL_set_sample_address(ChannelPtr->handler,(void*)DataPtr,Size);
				AIL_set_sample_playback_rate(ChannelPtr->handler,Frequency);
				AIL_set_sample_volume(ChannelPtr->handler,theVol);		//RJS 14Jan99

				AIL_start_sample(ChannelPtr->handler);				
			}
		}
	}

	return((UByteP)ChannelPtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DisableAll
//Author		Robert Slater
//Date			Mon 27 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::DisableAll()
{
	StopAll();
	DiscardMusic();

//	Save_Data.vol.music = 0;
//	Save_Data.vol.sfx = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillAll
//Author		Robert Slater
//Date			Mon 27 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::KillAll()
{
//	Save_Data.vol.music = SavedMusic;
//	Save_Data.vol.sfx = SavedSfx;
//	Save_Data.vol.uisfx = SavedUISfx;							//RJS 12Mar99

	StopAll();
	DiscardMusic();

	FreeSamples();
	ResetSoundFlags();
	ResetMidiFlags();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetVolumes
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetVolumes(Bool goinginto3d)
{
	allowedsamples = status.nohandlers / 3;
	if (goinginto3d)
	{
		// Set 3d volume...
		if ((Save_Data.vol.sfx >= 0) && (Save_Data.vol.sfx < 128) && IsEnabled(SOUND_DIGITAL))
		{
			AIL_set_digital_master_volume(dig,Save_Data.vol.sfx);

			if (!donePreLoad)
			{
				donePreLoad = true;
				PreLoadSFX();
			}

			if (!donePreLoadRadio)									//RJS 17May99
			{
				donePreLoadRadio = true;
				if (!PreLoadRadioChatter())
				{
					Save_Data.vol.rchat = 0;
					rchatter_allowed = false;									//RJS 16Aug99
				}
				else
					rchatter_allowed = true;
			}
		}
		else
		{
			Save_Data.vol.sfx = 0;
			Save_Data.vol.rchat = 0;
		}
	}
	else
	{
		// Set User Interface volume...
		if ((Save_Data.vol.uisfx >= 0) && (Save_Data.vol.uisfx < 128) && IsEnabled(SOUND_DIGITAL))
			AIL_set_digital_master_volume(dig,Save_Data.vol.uisfx);
		else
			Save_Data.vol.uisfx = 0;
	}

	if ((Save_Data.vol.music >= 0) && (Save_Data.vol.music < 128) && IsEnabled(SOUND_MIDI))
	{
 		AIL_set_XMIDI_master_volume(mdi,Save_Data.vol.music);

		if (havePercussion==true)								//RJS 14Apr99
		{
			if (goinginto3d)
			{
				if (IsEnabled(SOUND_DIGITAL))					//RJS 29Jun99
				{
					if (PreLoadMusicSamples())
					{
						//if we want sampled percussion, but no sfx, make sure we get volume!
						if (Save_Data.vol.sfx)
						{
							percvolscale = (Save_Data.vol.music<<8)/Save_Data.vol.sfx;
							if (percvolscale > 256)
								percvolscale = 256;
						}
						else
						{
							percvolscale = 256;
							AIL_set_digital_master_volume(dig,Save_Data.vol.music);
						}

						if (setPercussion)
						{
							AIL_register_event_callback(mdi,MIDIEventInterrupt);
							setPercussion = FALSE;
						}
					}
				}
			}
			else
				DeleteMusicSamples();
		}
	}
	else
		Save_Data.vol.music = 0;

	if (IsEnabled(SOUND_DIGITAL))
		EngineSound.Volume = (EngineSound.VolLoaded * Save_Data.vol.engine) >> 7;
	else
		EngineSound.Volume = 0;

	// Free up channel if we don't need it...
	if (Save_Data.vol.rchat)									//RJS 28Jan99
		freechannelstart = 3;									//RJS 28Jan99
	else														//RJS 28Jan99
		freechannelstart = 2;									//RJS 28Jan99

	channel_radiochatter = 2;									//RJS 14Apr99
	channel_percussion = 3;										//RJS 14Apr99
	if (havePercussion)											//RJS 14Apr99
		freechannelstart++;										//RJS 14Apr99

	thesmackervol = Save_Data.vol.anim;

//	SavedMusic = Save_Data.vol.music;
//	SavedSfx = Save_Data.vol.sfx;
//	SavedUISfx = Save_Data.vol.uisfx;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsEnabled
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::IsEnabled(SoundType	theSound)
{
	Bool	retval = FALSE;
	switch (theSound)
	{
	case SOUND_DIGITAL:
	{
		if (dig)	retval = TRUE;
	}
	break;
	case SOUND_MIDI:
	{
		if (mdi)	retval = TRUE;
	}
	break;
	case SOUND_RADIO:
	{
		if (rchatter_allowed)	retval = TRUE;
	}
	break;
	}

	return(retval);
}

void	Miles::SetEngine()
{
	if (Manual_Pilot.ControlledAC2)								//DAW 21Jun99
	{
		if (Manual_Pilot.ControlledAC2->fly.pModel->EngineList->Type == ET_PISTON)
			EngineSound.IsJet = FALSE;
		else
			EngineSound.IsJet = TRUE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessInterfaceSpot
//Author		Bobby Parp
//Date			Tue 17 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::ProcessInterfaceSpot()
{
 	allowedsamples = status.nohandlers / 3;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSoundFonts
//Author		Robert Slater
//Date			Thu 28 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::InitSoundFonts()
{
	if (trySoundFonts == true)
	{
		LPHMIDIOUT	midiOutDev = (LPHMIDIOUT) pooMidiDev;

		trySoundFonts = false;

		if (_SndFonts.LoadSoundFont(midiOutDev,FIL_SFONT_SNARES) == FALSE)
		{
			AIL_midiOutClose(mdi);

			havePercussion = false;								//RJS 14Apr99
			if (bestDrivers[1] > -1)
			{
				MusicDir = FIL_DIR_MUSICMED-FIL_DIR_MUSIC;
				uDriverID = (ULong) bestDrivers[1];
				if (AIL_midiOutOpen (&mdi, &midiOutDev, uDriverID))				
				{
					MusicDir = FIL_DIR_MUSICLOW-FIL_DIR_MUSIC;
					if (bestDrivers[2] > -1)
					{
						uDriverID = (ULong) bestDrivers[2];
						if (AIL_midiOutOpen (&mdi, &midiOutDev, uDriverID))				
							mdi = NULL;
						else
							havePercussion=true;				//RJS 14Apr99
					}
				}
			}
			else
			{
				MusicDir = FIL_DIR_MUSICLOW-FIL_DIR_MUSIC;
				if (bestDrivers[2] > -1)
				{
					uDriverID = (ULong) bestDrivers[2];
					if (AIL_midiOutOpen (&mdi, &midiOutDev, uDriverID))				
						mdi = NULL;
					else
						havePercussion=true;
				}
				else
					mdi = NULL;
			}
		}

		if (mdi == NULL)
			Save_Data.vol.music = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayBuffet
//Author		Robert Slater
//Date			Thu 28 Jan 1999
//
//Description	
//
//Inputs		vol is 0 - 128 scale factor,
//				pan is in Rowan angles
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayBuffet(SLong vol, SLong thepan)
{
	Log_Stack.Check(LogStack::MOVECODE);
	if (vol || lastBuffetVol)
	{
		SampleRec*	SamplePtr = LoadSample(FIL_SFX_SPRING1);
		if (SamplePtr)
		{
			SQueuePtr	ChannelPtr;										
			SQueuePtr	OldChannelPtr;
			SLong		thevol,audiblevol;											
			SLong		distance;
			Bool		dothis = FALSE;


			thevol = (SamplePtr->samplevolume * vol) >> 7;			
			vol = thevol;

			audiblevol = thevol>>8;
			if (audiblevol)
				dothis = TRUE;
			else
			{	
				if (lastBuffetVol)
					dothis = TRUE;
			}

			if (dothis)
			{
				RowanToPan(thepan);

				ChannelPtr = FindFreeHandler(SamplePtr,NULL,OldChannelPtr);
				if (ChannelPtr && allowedsamples)
				{
					allowedsamples--;

					SetUpSample(ChannelPtr,SamplePtr,vol,audiblevol,thepan,NULL);
					AIL_set_sample_loop_count(ChannelPtr->handler,2);	
					ChannelPtr->looping = TRUE;						
					AIL_start_sample(ChannelPtr->handler);			
				}
				else
				{
					if (OldChannelPtr)	
					{
						if (AIL_sample_status(OldChannelPtr->handler) == SMP_PLAYING)
						{
							if (audiblevol > 127)	audiblevol = 127;
							AIL_set_sample_volume(OldChannelPtr->handler,audiblevol);
							AIL_set_sample_pan(OldChannelPtr->handler,ClipPan(thepan));
						}
					}
				}
			}

			lastBuffetVol = audiblevol;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RowanToPan
//Author		Robert Slater
//Date			Fri 29 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::RowanToPan(SLong	&theAngle)
{
	if (theAngle > 16383)
		theAngle = 32767 - theAngle;
	
	if (theAngle < -16383)
		theAngle = -32768 - theAngle;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RowanToPan
//Author		Robert Slater
//Date			Fri 29 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::RowanToPan(SWord	&theAngle)
{
	if (theAngle > 16383)
		theAngle = 32767 - theAngle;
	
	if (theAngle < -16383)
		theAngle = -32768 - theAngle;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceAudible
//Author		Robert Slater
//Date			Wed 3 Feb 1999
//
//Description	Scale morale to fit mood...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SequenceAudible(MoraleType	 morale,SLong vol,SLong fadeval)
{
	SLong	newmood = (MOOD_TOP - MOOD_BOTTOM)*morale;
	newmood /= (MORALE_TOPMORALE-MORALE_ROCKBOTTOM);
	newmood += MOOD_BOTTOM;

	Mood = (MoodSetting) newmood;

	SequenceAudible(FIL_MUSIC_MAIN,vol,fadeval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UIPlaySample
//Author		Robert Slater
//Date			Fri 12 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::UIPlaySample(FileNum	thefile,SLong vol)
{
	if (Save_Data.vol.uisfx)
	{
		SQueuePtr	ChannelPtr;										
		SQueuePtr	OldChannelPtr;									
		SampleRec*	SamplePtr;

		if (allowedsamples)											
		{
			SamplePtr = LoadSample(thefile,TRUE);
			if (SamplePtr)
			{
				SLong	spos = GetIndex(thefile);
				SLong	thepan = 0;
				SLong	thevol = (SamplePtr->samplevolume * vol) >> 7;
				vol = thevol;
				thevol >>= 8;

				ChannelPtr = FindFreeHandlerUI(SamplePtr);	
				if (ChannelPtr)												
				{
					allowedsamples--;										
					SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,NULL);	
					AIL_start_sample(ChannelPtr->handler);
				}
			}
		}
	}

//  then...	ProcessInterfaceSpot();							

 	allowedsamples = status.nohandlers / 3;						//RJS 12Mar99
}

void	Miles::SequenceMute(SLong	fadeval)
{
//	if (!request.stopsequence)
	if ((request.activated & INT_STOPSEQUENCE)==0)				//RJS 18Jun99
	{
		fadeval *= 10;				//to millisecs
		if (FadeAll(fadeval))
		{
//Dead		request.activated = TRUE;
//Dead		request.stopsequence = TRUE;
			request.activated &= ~INT_ON;
			request.activated |= INT_STOPSEQUENCE;					//RJS 18Jun99
			request.forcestop = 1;									//RJS 18Jun99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreLoadSFX
//Author		Robert Slater
//Date			Thu 1 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PreLoadSFX()
{
	if (Save_Data.vol.sfx)
	{
		FreeSamples();

		SLong	thefile = FIL_DIR_SFX;
		SLong	lastsnd = FIL_SFX_VOCAL_ENEMY1;
		SLong	index;

		thefile++;
		for (index=thefile; index < lastsnd; index++)
		{
			FileNum	realname = (FileNum)index;

			if (	(index != FIL_SFX_LOOP_FX_START)
				&&	(index != FIL_SFX_LOOP_FX_END))
				PreLoadFile(index);
		}
	}

	if (Save_Data.vol.music)
	{
		SLong	thedir = FIL_DIR_MUSIC+MusicDir;
		SLong	thefile;
		SLong	lastsnd = FIL_MUSIC_LAST_TUNE - FIL_DIR_MUSIC;
		SLong	index;

		for (index=1; index < lastsnd; index++)
		{
			thefile = FIL_DIR_MUSIC+index;
			if (	(thefile != FIL_MUSIC_STAND_ALONE)
 				&&	(thefile != FIL_MUSIC_PRIORITY)					  //DAW 07/05/99
				)
				PreLoadFile(thedir+index);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreLoadRadioChatter
//Author		Robert Slater
//Date			Thu 1 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::PreLoadRadioChatter()
{
	Bool	retval = FALSE;
	if (Manual_Pilot.ControlledAC2)
	{
#ifndef	NDEBUG
	SLong	memused = FILEMAN.getTotalFileMemUsed();
#endif

		if (Save_Data.vol.rchat)
		{
			if (FILEMAN.getTotalMem() >= MEMORY_MIN)
			{
				AirStrucPtr	ac = Manual_Pilot.ControlledAC2;
				Bool		playerLeader;
				Bool		haveFAC;
				SLong		thefile;
				SLong		theroot = FIL_DIR_RCHAT_PLAYER;
				SLong		voxfac = randomFAC << 8;
				SLong		voxtower = randomTOWER << 8;

				if (ac->formpos == 0)
					playerLeader = TRUE;
				else
					playerLeader = FALSE;

				while (ac->fly.leadflight)
					ac = ac->fly.leadflight;

				if ((ac->duty & ACTIONCODE) == DA_CAP)			//RJS 08Jun99
					haveFAC = FALSE;
				else
				{
					if ((ac->duty & DUTYMASK) == DC_CAS)
						haveFAC = TRUE;
					else
						haveFAC = FALSE;
				}


				//Player...
				thefile = FIL_DIR_RCHAT_PLAYER - theroot;
				PreLoadFile(thefile+FIL_RCHAT_PARTS_S);
				PreLoadFile(thefile+FIL_RCHAT_PUNCTUATION);					//RJS 08Jun99
				PreLoadFile(thefile+FIL_RCHAT_PARTS_COMBAT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_KILL);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_EJECT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_DAMAGE);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_MISC);
				PreLoadFile(thefile+FIL_RCHAT_SMALLRANGES);
				PreLoadFile(thefile+FIL_RCHAT_RELPOSITION);
				PreLoadFile(thefile+FIL_RCHAT_BEARINGS);
				PreLoadFile(thefile+FIL_RCHAT_TARGTYPE);
				PreLoadFile(thefile+FIL_RCHAT_TARGNAME);
				PreLoadFile(thefile+FIL_RCHAT_TARGMOV);
				PreLoadFile(thefile+FIL_RCHAT_CALLSIGNS_N);
				PreLoadFile(thefile+FIL_RCHAT_NUMTABLE1);
				PreLoadFile(thefile+FIL_RCHAT_QNAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_ANAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_PLACENAME);
				PreLoadFile(thefile+FIL_RCHAT_BANDIT_ALERT);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_INFO);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_COMBAT);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_POSTCOMBAT);
				PreLoadFile(thefile+FIL_RCHAT_TO_TOWER);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_XCOMBAT);
				if (playerLeader)
				{
					PreLoadFile(thefile+FIL_RCHAT_NUMTABLE25);
					PreLoadFile(thefile+FIL_RCHAT_CALLGROUPS);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_PARTS_MISC);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_INFO);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_PRECOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_COMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_POSTCOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_HOME);
					PreLoadFile(thefile+FIL_RCHAT_WEAPONS);
					PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_TRAVEL);
					if (haveFAC)
						PreLoadFile(thefile+FIL_RCHAT_TO_FACTAC);
				}

				thefile = FIL_DIR_RCHAT_XPLAYER - theroot;
				PreLoadFile(thefile+FIL_RCHAT_PARTS_S);
				PreLoadFile(thefile+FIL_RCHAT_PUNCTUATION);					//RJS 08Jun99
				PreLoadFile(thefile+FIL_RCHAT_PARTS_COMBAT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_KILL);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_EJECT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_DAMAGE);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_MISC);
				PreLoadFile(thefile+FIL_RCHAT_SMALLRANGES);
				PreLoadFile(thefile+FIL_RCHAT_RELPOSITION);
				PreLoadFile(thefile+FIL_RCHAT_BEARINGS);
				PreLoadFile(thefile+FIL_RCHAT_TARGTYPE);
				PreLoadFile(thefile+FIL_RCHAT_TARGNAME);
				PreLoadFile(thefile+FIL_RCHAT_TARGMOV);
				PreLoadFile(thefile+FIL_RCHAT_CALLSIGNS_N);
				PreLoadFile(thefile+FIL_RCHAT_NUMTABLE1);
				PreLoadFile(thefile+FIL_RCHAT_QNAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_ANAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_PLACENAME);
				PreLoadFile(thefile+FIL_RCHAT_BANDIT_ALERT);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_INFO);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_COMBAT);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_POSTCOMBAT);
				PreLoadFile(thefile+FIL_RCHAT_TO_TOWER);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_XCOMBAT);
				if (playerLeader)
				{
					PreLoadFile(thefile+FIL_RCHAT_NUMTABLE25);
					PreLoadFile(thefile+FIL_RCHAT_CALLGROUPS);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_PARTS_MISC);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_INFO);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_PRECOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_COMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_POSTCOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_HOME);
					PreLoadFile(thefile+FIL_RCHAT_WEAPONS);
					PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_TRAVEL);
					if (haveFAC)
						PreLoadFile(thefile+FIL_RCHAT_TO_FACTAC);
				}

				thefile = FIL_DIR_RCHAT_OTHER - theroot;
				PreLoadFile(thefile+FIL_RCHAT_PARTS_S);
				PreLoadFile(thefile+FIL_RCHAT_PUNCTUATION);					//RJS 08Jun99
				PreLoadFile(thefile+FIL_RCHAT_PARTS_COMBAT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_KILL);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_EJECT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_DAMAGE);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_MISC);
				PreLoadFile(thefile+FIL_RCHAT_SMALLRANGES);
				PreLoadFile(thefile+FIL_RCHAT_RELPOSITION);
				PreLoadFile(thefile+FIL_RCHAT_BEARINGS);
				PreLoadFile(thefile+FIL_RCHAT_TARGTYPE);
				PreLoadFile(thefile+FIL_RCHAT_TARGNAME);
				PreLoadFile(thefile+FIL_RCHAT_TARGMOV);
				PreLoadFile(thefile+FIL_RCHAT_CALLSIGNS_N);
				PreLoadFile(thefile+FIL_RCHAT_NUMTABLE1);
				PreLoadFile(thefile+FIL_RCHAT_QNAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_ANAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_PLACENAME);
				PreLoadFile(thefile+FIL_RCHAT_BANDIT_ALERT);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_INFO);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_COMBAT);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_POSTCOMBAT);
				PreLoadFile(thefile+FIL_RCHAT_TO_TOWER);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_XCOMBAT);
				if (!randomV2)
					PreLoadFile(thefile+FIL_RCHAT_VOICE2_ONLY);
				if (!playerLeader)
				{
					PreLoadFile(thefile+FIL_RCHAT_NUMTABLE25);
					PreLoadFile(thefile+FIL_RCHAT_CALLGROUPS);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_PARTS_MISC);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_INFO);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_PRECOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_COMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_POSTCOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_HOME);
					PreLoadFile(thefile+FIL_RCHAT_WEAPONS);
					PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_TRAVEL);
					if (haveFAC)
						PreLoadFile(thefile+FIL_RCHAT_TO_FACTAC);
				}

				thefile = FIL_DIR_RCHAT_XOTHER - theroot;
				PreLoadFile(thefile+FIL_RCHAT_PARTS_S);
				PreLoadFile(thefile+FIL_RCHAT_PUNCTUATION);					//RJS 08Jun99
				PreLoadFile(thefile+FIL_RCHAT_PARTS_COMBAT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_KILL);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_EJECT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_DAMAGE);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_MISC);
				PreLoadFile(thefile+FIL_RCHAT_SMALLRANGES);
				PreLoadFile(thefile+FIL_RCHAT_RELPOSITION);
				PreLoadFile(thefile+FIL_RCHAT_BEARINGS);
				PreLoadFile(thefile+FIL_RCHAT_TARGTYPE);
				PreLoadFile(thefile+FIL_RCHAT_TARGNAME);
				PreLoadFile(thefile+FIL_RCHAT_TARGMOV);
				PreLoadFile(thefile+FIL_RCHAT_CALLSIGNS_N);
				PreLoadFile(thefile+FIL_RCHAT_NUMTABLE1);
				PreLoadFile(thefile+FIL_RCHAT_QNAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_ANAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_PLACENAME);
				PreLoadFile(thefile+FIL_RCHAT_BANDIT_ALERT);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_INFO);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_COMBAT);
				PreLoadFile(thefile+FIL_RCHAT_GROUP_POSTCOMBAT);
				PreLoadFile(thefile+FIL_RCHAT_TO_TOWER);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_XCOMBAT);
				if (randomV2)
					PreLoadFile(thefile+FIL_RCHAT_VOICE2_ONLY);
				if (!playerLeader)
				{
					PreLoadFile(thefile+FIL_RCHAT_NUMTABLE25);
					PreLoadFile(thefile+FIL_RCHAT_CALLGROUPS);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_PARTS_MISC);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_INFO);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_PRECOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_COMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_POSTCOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_LEAD_GROUP_HOME);
					PreLoadFile(thefile+FIL_RCHAT_WEAPONS);
					PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_TRAVEL);
					if (haveFAC)
						PreLoadFile(thefile+FIL_RCHAT_TO_FACTAC);
				}

				if (haveFAC)
				{
					thefile = FIL_DIR_RCHAT_FACTAC + voxfac - theroot;	//RJS 08Jun99
					PreLoadFile(thefile+FIL_RCHAT_PARTS_S);
					PreLoadFile(thefile+FIL_RCHAT_PUNCTUATION);					//RJS 08Jun99
					PreLoadFile(thefile+FIL_RCHAT_PARTS_COMBAT);
					PreLoadFile(thefile+FIL_RCHAT_PARTS_KILL);
					PreLoadFile(thefile+FIL_RCHAT_PARTS_EJECT);
					PreLoadFile(thefile+FIL_RCHAT_PARTS_DAMAGE);
					PreLoadFile(thefile+FIL_RCHAT_PARTS_MISC);
					PreLoadFile(thefile+FIL_RCHAT_SMALLRANGES);
					PreLoadFile(thefile+FIL_RCHAT_RELPOSITION);
					PreLoadFile(thefile+FIL_RCHAT_BEARINGS);
					PreLoadFile(thefile+FIL_RCHAT_TARGTYPE);
					PreLoadFile(thefile+FIL_RCHAT_TARGNAME);
					PreLoadFile(thefile+FIL_RCHAT_TARGMOV);
					PreLoadFile(thefile+FIL_RCHAT_CALLSIGNS_N);
					PreLoadFile(thefile+FIL_RCHAT_NUMTABLE1);
					PreLoadFile(thefile+FIL_RCHAT_QNAMED_AC);
					PreLoadFile(thefile+FIL_RCHAT_ANAMED_AC);
					PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_PLACENAME);
					PreLoadFile(thefile+FIL_RCHAT_BANDIT_ALERT);
					PreLoadFile(thefile+FIL_RCHAT_GROUP_INFO);
					PreLoadFile(thefile+FIL_RCHAT_GROUP_COMBAT);
					PreLoadFile(thefile+FIL_RCHAT_GROUP_POSTCOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_TO_TOWER);
					PreLoadFile(thefile+FIL_RCHAT_PARTS_XCOMBAT);
					PreLoadFile(thefile+FIL_RCHAT_NUMTABLE25);
					PreLoadFile(thefile+FIL_RCHAT_WEAPONS);
					PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_TRAVEL);
					PreLoadFile(thefile+FIL_RCHAT_FACTAC);
				}
	//			else
				{
					thefile = FIL_DIR_RCHAT_DENTIST - theroot;
					PreLoadFile(thefile+FIL_RCHAT_PARTS_S);
					PreLoadFile(thefile+FIL_RCHAT_PUNCTUATION);					//RJS 08Jun99
					PreLoadFile(thefile+FIL_RCHAT_PARTS_COMBAT);
					PreLoadFile(thefile+FIL_RCHAT_PARTS_KILL);
					PreLoadFile(thefile+FIL_RCHAT_PARTS_EJECT);
					PreLoadFile(thefile+FIL_RCHAT_PARTS_DAMAGE);
					PreLoadFile(thefile+FIL_RCHAT_PARTS_MISC);
					PreLoadFile(thefile+FIL_RCHAT_SMALLRANGES);
					PreLoadFile(thefile+FIL_RCHAT_RELPOSITION);
					PreLoadFile(thefile+FIL_RCHAT_BEARINGS);
					PreLoadFile(thefile+FIL_RCHAT_TARGTYPE);
					PreLoadFile(thefile+FIL_RCHAT_TARGNAME);
					PreLoadFile(thefile+FIL_RCHAT_TARGMOV);
					PreLoadFile(thefile+FIL_RCHAT_CALLSIGNS_N);
					PreLoadFile(thefile+FIL_RCHAT_NUMTABLE1);
					PreLoadFile(thefile+FIL_RCHAT_QNAMED_AC);
					PreLoadFile(thefile+FIL_RCHAT_ANAMED_AC);
					PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_PLACENAME);
					PreLoadFile(thefile+FIL_RCHAT_BANDIT_ALERT);
					PreLoadFile(thefile+FIL_RCHAT_NUMTABLE25);
					PreLoadFile(thefile+FIL_RCHAT_WEAPONS);
					PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_TRAVEL);
					PreLoadFile(thefile+FIL_RCHAT_FACTAC);
					PreLoadFile(thefile+FIL_RCHAT_SPECIAL_RADAR);
					PreLoadFile(thefile+FIL_RCHAT_PLACENAMES);
				}

				thefile = FIL_DIR_RCHAT_TOWER + voxtower - theroot;	//RJS 08Jun99
				PreLoadFile(thefile+FIL_RCHAT_PARTS_S);
				PreLoadFile(thefile+FIL_RCHAT_PUNCTUATION);					//RJS 08Jun99
				PreLoadFile(thefile+FIL_RCHAT_PARTS_COMBAT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_KILL);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_EJECT);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_DAMAGE);
				PreLoadFile(thefile+FIL_RCHAT_PARTS_MISC);
				PreLoadFile(thefile+FIL_RCHAT_SMALLRANGES);
				PreLoadFile(thefile+FIL_RCHAT_RELPOSITION);
				PreLoadFile(thefile+FIL_RCHAT_BEARINGS);
				PreLoadFile(thefile+FIL_RCHAT_TARGTYPE);
				PreLoadFile(thefile+FIL_RCHAT_TARGNAME);
				PreLoadFile(thefile+FIL_RCHAT_TARGMOV);
				PreLoadFile(thefile+FIL_RCHAT_CALLSIGNS_N);
				PreLoadFile(thefile+FIL_RCHAT_NUMTABLE1);
				PreLoadFile(thefile+FIL_RCHAT_QNAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_ANAMED_AC);
				PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_PLACENAME);
				PreLoadFile(thefile+FIL_RCHAT_BANDIT_ALERT);
				PreLoadFile(thefile+FIL_RCHAT_NUMTABLE25);
				PreLoadFile(thefile+FIL_RCHAT_DIRECTIONS_TRAVEL);
				PreLoadFile(thefile+FIL_RCHAT_SPECIAL_TOWER);
				PreLoadFile(thefile+FIL_RCHAT_AIRFIELDS);

				retval = TRUE;
			}
#ifndef	NDEBUG
	memused = FILEMAN.getTotalFileMemUsed() - memused;
#endif
		}
	}

	return(retval);
}

void	Miles::PreLoadFile(SLong	thefile)
{
	fileblock ((FileNum)thefile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmackerOn
//Author		Dave Whiteside
//Date			Tue 6 Apr 1999
//
//Description	Vol toggle
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SmackerOn(Smack* smk)
{
	if (dig)
	{
		//only scale up to 32k, cos most sound libraries can't amplify
		SmackVolumePan(smk,SMACKTRACKS,(Save_Data.vol.anim<<8),0);	   //RJS 13Apr99
	}
//Dead 		AIL_set_digital_master_volume(dig,Save_Data.vol.anim);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmackerOff
//Author		Dave Whiteside
//Date			Tue 6 Apr 1999
//
//Description	Vol toggle
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SmackerOff()
{
	if (dig)
 		AIL_set_digital_master_volume(dig,Save_Data.vol.uisfx);
}

void	Miles::StopShooting()
{
	Log_Stack.Check(LogStack::MOVECODE);
	if (playerShooting)
	{
		if (!shootTimer)
		{
			if(Save_Data.flightdifficulty[FD_FF_GUN])	//CSB 05/07/99	
				_Analogue.FFshake.SetZ(0,0,false);

			if (Save_Data.vol.sfx)
			{
				int	qpos;
				for (qpos = freechannelstart; qpos < status.nohandlers; qpos ++)
				{
					if (	(soundqueue[qpos].sampleindex == GunSampleIndex)
						&&	(soundqueue[qpos].worlditem == Manual_Pilot.ControlledAC2)	)
						HardStop(&soundqueue[qpos]);
				}
			}

			playerShooting = false;
		}
	}
}

Bool	Miles::StartShooting(FileNum	theSample,SLong shoottime,SLong	gunfreq)
{
	Log_Stack.Check(LogStack::MOVECODE);
	Bool	shootnow = FALSE;
	if (!playerShooting)
	{
		if(Save_Data.flightdifficulty[FD_FF_GUN])	//CSB 05/07/99	
			_Analogue.FFshake.SetZ(/*100000*/65000,gunfreq,false);				  //RJS 31/05/99	//CSB 18/06/99	
//DeadCode DAW 25Jun99 		_Analogue.FFshake.SetZ(65000,gunfreq,false);				  //RJS 31/05/99	//CSB 18/06/99	

		shootTimer = shoottime;
		shootnow = TRUE;
		playerShooting = true;
		GunSampleIndex = &thesample[GetIndex(theSample)];
	}
	else
	{
		if (!shootTimer)
			shootTimer = shoottime;
	}

	return(shootnow);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreLoadMusicSamples
//Author		Robert Slater
//Date			Wed 14 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Miles::PreLoadMusicSamples()
{
	Bool	retval = TRUE;
	if (Save_Data.vol.music)
	{
		SLong	nosamples = FIL_MUSIC_LAST_SAMPLE-FIL_MUSIC_FIRST_SAMPLE;
		if (!themusicsample)
		{
			themusicsample = new SampleRec[nosamples];
			if (themusicsample)
			{
				SLong index;
				for (index=0; index < nosamples; index++)
					themusicsample[index].blockptr = NULL;

				setPercussion = TRUE;
			}

			nomusicsamples = 0;
		}

		if (themusicsample)
		{
			SLong		thedir = FIL_DIR_MUSICLOW;
			SLong		lastsnd = FIL_MUSIC_LAST_SAMPLE - FIL_DIR_MUSIC;
			SLong		firstsnd = FIL_MUSIC_FIRST_SAMPLE - FIL_DIR_MUSIC;
			SLong		index,realindex;
			SampleRec*	SamplePtr;
			char		header[10];
			char		*tmpptr;
			void		*tmpaddress;
			int			size;
			int			count;
			SLong		result = 1;
			RIFF		*header1;
			FMT			*header2;
			DATA		*header3;

			for (index=firstsnd; index < lastsnd; index++)
			{
				FileNum	thefile = (FileNum) (index+thedir);

				realindex= index-firstsnd;
				SamplePtr = &themusicsample[realindex];

				if (SamplePtr->blockptr==NULL)
				{
					SamplePtr->blockptr = new fileblock(thefile);
					if (SamplePtr->blockptr)
					{
						nomusicsamples++;

						SamplePtr->size = getsize(SamplePtr->blockptr);

						tmpaddress = getdata(SamplePtr->blockptr);

						tmpptr = (char*) tmpaddress;

						for (count = 0; count < 4; count ++)
							header[count] = *tmpptr++;
	
						header[4] = 0;

						if (	(strcmp(header,"RIFF") == 0)
							||	(strcmp(header,"Crea") == 0) )
						{
							header1 = (RIFF*) tmpaddress;
							header2 = (FMT*) header1->data;
		
							count = 0;								
							while (strnicmp(header2->FMT_string,"fmt ",4))
    						{
    							header2 = (FMT *) ((BYTE *) header2 +
			      						header2->chunk_size + 8 + (header2->chunk_size & 1));

								count++;										
								if (count >3)									
									break;										
    						}

							if (count > 3)
								SamplePtr->samplerate = 11025;
							else
								SamplePtr->samplerate = header2->sample_rate;

							header3 = (DATA*) header1->data;
							while (strnicmp(header3->DATA_string,"data",4))
	  						{
    							header3 = (DATA *) ((char *) header3 +
			      						header3->chunk_size + 8 + (header3->chunk_size & 1));
    						}

							SamplePtr->datasize = header3->chunk_size;
							SamplePtr->dataptr = (void*) header3->data;
						}
						else					
							SamplePtr->samplerate = 44100;

						SamplePtr->priority = 0;
					}
					else
					{
						nomusicsamples = 0;
						retval = FALSE;
						break;
					}
				}
			}
		}
		else
			retval = FALSE;
	}
	else
		retval = FALSE;

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteMusicSamples
//Author		Robert Slater
//Date			Wed 14 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::DeleteMusicSamples()
{
	if (themusicsample)
	{
		SLong	nosamples = FIL_MUSIC_LAST_SAMPLE - FIL_MUSIC_FIRST_SAMPLE;
		SLong	index;

		for (index=0; index < nosamples; index++)
		{
			if (themusicsample[index].blockptr)
				delete themusicsample[index].blockptr;

			themusicsample[index].blockptr = NULL;
		}

		nomusicsamples = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpRandomVoices
//Author		Robert Slater
//Date			Fri 21 May 1999
//
//Description	Called from radio chatter to reset preload with alternate voices
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::SetUpRandomVoices(SLong	fac, SLong	tower, SLong v2)
{
	randomFAC = fac;
	randomTOWER = tower;
	randomV2 = v2;

	donePreLoadRadio = false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayWindyMiller
//Author		Robert Slater
//Date			Fri 21 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayWindyMiller(AirStrucPtr	ac)
{
	Log_Stack.Check(LogStack::MOVECODE);
	bool	notplayed = true;
	ULong	velscale = (ac->vel << 15)/1500;
	if (CockpitView && velscale && (allowedsamples || playingMiller))//RJS 07Jun99
	{
		AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
		ULong				acflaps = adptr->acflaps;
		ULong				acbreak = adptr->acbreak;
		ULong				acgear = adptr->acleglowerl;
		ULong				thevol;

		if (acbreak || acflaps || !acgear)
		{
			SampleRec*	SamplePtr = LoadSample(FIL_SFX_WIND_COCKPIT_LOOP);
			if (SamplePtr)
			{
				acgear = 255 - acgear;
				if (acgear > 128)	acgear = 128;

				acbreak += acflaps<<1;	//cos flaps are noisier
				acbreak += acgear;		
			
				if (velscale > 32768)
					velscale = 32768;

				thevol = acbreak * velscale;
				thevol >>= 8;
				thevol *= 13000;
				thevol >>= 15;
				thevol /= 893;
				if (thevol)
				{
					SQueuePtr	OldChannelPtr;
					SQueuePtr	ChannelPtr;

					playingMiller = true;
					allowedsamples--;

					if (thevol > 127)
						thevol = 127;

					notplayed = false;
					ChannelPtr = FindFreeHandler(SamplePtr,ac,OldChannelPtr);
					if (ChannelPtr)
					{
						SetUpSample(ChannelPtr,SamplePtr,thevol<<8,thevol,0,ac);

						ChannelPtr->looping = TRUE;
						ChannelPtr->GameSound = FALSE;

						AIL_set_sample_loop_count(ChannelPtr->handler,0);
						AIL_start_sample(ChannelPtr->handler);
					}
					else
					{
						if (OldChannelPtr)
						{
							if (AIL_sample_status(OldChannelPtr->handler) == SMP_PLAYING)
								AIL_set_sample_volume(OldChannelPtr->handler,thevol);
						}
					}
				}
			}
		}
	}

	if (notplayed && playingMiller)
	{
		StopSample(FIL_SFX_WIND_COCKPIT_LOOP,ac);
		playingMiller = false;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSysTime
//Author		Andy McMaster
//Date			Fri 11 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ULong		Miles::GetSysTime()
{
	ULong	theTime;
	if (mdi || dig)
	{
		AIL_lock();
		theTime = timeGetTime();
		AIL_unlock();
	}
	else
		theTime = timeGetTime();

	return theTime;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayDelayed
//Author		Robert Slater
//Date			Wed 16 Aug 1999
//
//Description	Log a sample to be played from a different thread, if it is not
//				already playing.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::PlayDelayed(FileNum	thefile, ItemBasePtr	theitm,SLong vol,Bool looped,FileNum	stsam, FileNum	endsam)
{
	if (Save_Data.vol.sfx)
	{
		int	spos = GetIndex(thefile);

		SampleRec*	SamplePtr = &thesample[spos];

		for (int count = freechannelstart; count < status.nohandlers; count ++)
		{
			if (	(soundqueue[count].sampleindex == SamplePtr)
				&&	(soundqueue[count].worlditem == theitm)	)
				return;
		}

		delayedsounds.Add(thefile,theitm,vol,looped,stsam,endsam);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessPercussion
//Author		Robert Slater
//Date			Wed 18 Aug 1999
//
//Description	Play percussion sample that has been logged by a midi event.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::ProcessPercussion()
{
	if (percussionLog.sampleindex > -1)
	{
		SQueuePtr	ChannelPtr = &soundqueue[channel_percussion];
		HSAMPLE		handler = ChannelPtr->handler;
		SLong		volume = percussionLog.volume;

		if (ChannelPtr->sampleindex)
		{
			if (AIL_sample_status(handler)!=SMP_DONE)
				AIL_end_sample(handler);
		}

		ChannelPtr->sampleindex = &themusicsample[percussionLog.sampleindex];

		AIL_init_sample(handler);
		if (AIL_set_sample_file(handler,getdata(ChannelPtr->sampleindex->blockptr),-1))
		{
			//Balance the percussion volume between 3d sample and music volume...
			volume *= percvolscale;
			volume >>= 8;

			AIL_set_sample_volume(handler, volume);
			AIL_start_sample(handler);
		}

		percussionLog.sampleindex = -1;
	}
}

void	Miles::SetDelayed(bool dstate)
{
	delayedstate = dstate;
}
