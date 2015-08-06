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


THIS IS DEAD... MILES.CPP DOES BOTH WIN AND DOS

//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 //Filename       milestub.cpp
//DeadCode JIM 25Sep96 //System         
//DeadCode JIM 25Sep96 //Author         Robert Slater
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Conversion to windows Andrew McRae							//ARM 15Jul96
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Date           Wed 21 Feb 1996
//DeadCode JIM 25Sep96 //Description    MIDI and sound sample library functions
//DeadCode JIM 25Sep96 //				Engine sound is at sample queue position 0,
//DeadCode JIM 25Sep96 //				Machine gun sound is at sample queue position 1
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 #include 	"dosdefs.h"
//DeadCode JIM 25Sep96 #define 	F_GRAFIX
//DeadCode JIM 25Sep96 #include	"files.g"
//DeadCode JIM 25Sep96 #include	"fileman.h"
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 #include	"wail.h"
//DeadCode JIM 25Sep96 #include	"miles.h"
//DeadCode JIM 25Sep96 #include	"milesxtr.h"
//DeadCode JIM 25Sep96 #include	<smack.h>
//DeadCode JIM 25Sep96 #include	"time.h"											//PD 15Mar96
//DeadCode JIM 25Sep96 #include	"math.h"
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 Miles _Miles={0};
//DeadCode JIM 25Sep96 TimerCode Timer_Code;											//PD 15Mar96
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96  		SequenceStruct	Miles::tune[Miles::MAXTUNES];
//DeadCode JIM 25Sep96  		MusicRequest	Miles::request;
//DeadCode JIM 25Sep96 		SampleLibrary	Miles::wavetable;
//DeadCode JIM 25Sep96 		SampleRec		Miles::thesample[Miles::MAXSAMPLES];
//DeadCode JIM 25Sep96 		PlayingRec		Miles::soundqueue[Miles::MAXHANDLERS];
//DeadCode JIM 25Sep96 		StatusRec		Miles::status;
//DeadCode JIM 25Sep96 		SampleRequest	Miles::soundtoplay;
//DeadCode JIM 25Sep96 		HTIMER			Miles::timer;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 #pragma off (check_stack);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		mainbeatint
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 22 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Interrupt routine that is trigered by the main track on hitting
//DeadCode JIM 25Sep96 //				certain marked bars.	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Caller sequence handler, channel and value		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 static	void	AILEXPORT Miles::mainbeatint (HSEQUENCE callerseq, S32 channel, S32 value)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96  	if (!request.activated)
//DeadCode JIM 25Sep96  		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (value > 50)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (request.runaway)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			if (	(value == request.spottuneno)
//DeadCode JIM 25Sep96 				&&	!request.enemyready				)
//DeadCode JIM 25Sep96 			{
//DeadCode JIM 25Sep96 				request.enemytorun = TRUE;
//DeadCode JIM 25Sep96 			}
//DeadCode JIM 25Sep96 			else
//DeadCode JIM 25Sep96 			{
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 				switch (value)
//DeadCode JIM 25Sep96 				{
//DeadCode JIM 25Sep96 				case 127:
//DeadCode JIM 25Sep96 					request.wait = FALSE;
//DeadCode JIM 25Sep96 					
//DeadCode JIM 25Sep96 					if (request.startseq)
//DeadCode JIM 25Sep96 					{
//DeadCode JIM 25Sep96 						request.activated = FALSE;
//DeadCode JIM 25Sep96 						request.startseq = FALSE;
//DeadCode JIM 25Sep96 						request.runaway = FALSE;
//DeadCode JIM 25Sep96 						request.enemyready = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 						AIL_set_sequence_volume(request.spothandle, request.spotvol, request.spotfadeval);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 						AIL_start_sequence(request.spothandle);	
//DeadCode JIM 25Sep96 					}
//DeadCode JIM 25Sep96 					break;
//DeadCode JIM 25Sep96 				case 126:
//DeadCode JIM 25Sep96 					request.wait = TRUE;
//DeadCode JIM 25Sep96 					break;
//DeadCode JIM 25Sep96 				default:
//DeadCode JIM 25Sep96 					if (request.enemytorun)
//DeadCode JIM 25Sep96 					{
//DeadCode JIM 25Sep96 						request.spotseqno = value;
//DeadCode JIM 25Sep96 						request.enemytorun = FALSE;
//DeadCode JIM 25Sep96 						request.enemyready = TRUE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 					}
//DeadCode JIM 25Sep96 				}
//DeadCode JIM 25Sep96 			}
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 		
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 	else
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96  		if (request.fader)
//DeadCode JIM 25Sep96  		{
//DeadCode JIM 25Sep96  			request.activated = FALSE;
//DeadCode JIM 25Sep96 			request.fader = FALSE;
//DeadCode JIM 25Sep96  
//DeadCode JIM 25Sep96  			AIL_set_sequence_volume(request.barhandle, request.barvol, request.barfadeval);
//DeadCode JIM 25Sep96 			return;
//DeadCode JIM 25Sep96  		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (request.startsim) 
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96  			request.activated = FALSE;
//DeadCode JIM 25Sep96 			request.startsim = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			AIL_set_sequence_volume(request.barspothandle, request.barspotvol, request.barspotfadeval);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			AIL_start_sequence(request.barspothandle);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			return;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96  		if (request.stopsequence)
//DeadCode JIM 25Sep96  		{
//DeadCode JIM 25Sep96  			if (AIL_sequence_volume(callerseq) > 0)
//DeadCode JIM 25Sep96  				AIL_set_sequence_volume(callerseq, 0, 0);
//DeadCode JIM 25Sep96  			else
//DeadCode JIM 25Sep96  			{
//DeadCode JIM 25Sep96  				request.activated = FALSE;
//DeadCode JIM 25Sep96 				request.stopsequence = FALSE;
//DeadCode JIM 25Sep96  
//DeadCode JIM 25Sep96  				AIL_end_sequence(callerseq);
//DeadCode JIM 25Sep96  			}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			return;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 }			
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		subbeatint
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 22 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 static	void	AILEXPORT Miles::subbeatint(HSEQUENCE callerseq, S32	channel, S32	value)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 //DeadCode PD 06Mar96 	((UByte*) 0xb0000)[480]++;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!request.activated)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }		
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		mainendint
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Fri 23 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 static	void	AILEXPORT Miles::mainendint(HSEQUENCE callerseq)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 //DeadCode PD 06Mar96 	((UByte*) 0xb0000)[320]++;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!request.activated)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		subendint
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Fri 23 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	AILEXPORT Miles::subendint(HSEQUENCE callerseq)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 //DeadCode PD 06Mar96 	((UByte*) 0xb0000)[160]++;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!request.activated)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		timerint
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 29 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	cdecl Miles::timerint(ULONG	user)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	Timer_Code.tus++;											//JIM 02Apr96
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 #pragma on (check_stack);
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		StartUpMiles
//DeadCode JIM 25Sep96 //Author		Andrew McRae
//DeadCode JIM 25Sep96 //Date			Wed 21 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Set up midi and digital samples system	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 void	Miles::StartUpMiles()
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	int			tuneno;
//DeadCode JIM 25Sep96 	int 		count;
//DeadCode JIM 25Sep96 	char		*filename;
//DeadCode JIM 25Sep96 	char		inifilename[80];
//DeadCode JIM 25Sep96 	char		found;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //	HDIGDRIVER	digdrvr;
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 	WAVEFORMAT	waveformat;
//DeadCode JIM 25Sep96 	static PCMWAVEFORMAT PCM_waveformat;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //	HMDIDRIVER	mididrvr;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (mdi || dig || timer)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Default is Direct Sound
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_startup();
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Setup Midi Driver
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	mdi = NULL;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (AIL_midiOutOpen ( &mdi, NULL, (WORD)MIDI_MAPPER))
//DeadCode JIM 25Sep96 		if (AIL_midiOutOpen ( &mdi, NULL, 0))
//DeadCode JIM 25Sep96 			MessageBox (NULL, AIL_last_error(), "error", MB_OK);
//DeadCode JIM 25Sep96 //			_Error.EmitSysErr("Direct Sound Not Installed - midi");
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	wavetable.blockptr = NULL;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (tuneno = 0; tuneno < MAXTUNES; tuneno++)
//DeadCode JIM 25Sep96 		tune[tuneno].blockptr = NULL;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	status.nosamples = 0;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Setup Digital Sounds
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	WORD	chans;
//DeadCode JIM 25Sep96 	DWORD	rate;
//DeadCode JIM 25Sep96 	WORD	bits;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	chans = 2;
//DeadCode JIM 25Sep96 	rate = 11025;
//DeadCode JIM 25Sep96 	bits = 16;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	PCM_waveformat.wf.wFormatTag = WAVE_FORMAT_PCM;
//DeadCode JIM 25Sep96 	PCM_waveformat.wf.nChannels = chans;
//DeadCode JIM 25Sep96 	PCM_waveformat.wf.nSamplesPerSec = rate;
//DeadCode JIM 25Sep96 	PCM_waveformat.wf.nAvgBytesPerSec = rate * (bits / 8) * chans;
//DeadCode JIM 25Sep96 	PCM_waveformat.wf.nBlockAlign = (bits /8) * chans;
//DeadCode JIM 25Sep96 	PCM_waveformat.wBitsPerSample = bits;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	dig = NULL;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (AIL_waveOutOpen ( &dig, NULL, NULL, (LPWAVEFORMAT)&PCM_waveformat) != 0)
//DeadCode JIM 25Sep96 		MessageBox (NULL, AIL_last_error(), "error", MB_OK);
//DeadCode JIM 25Sep96 //		_Error.EmitSysErr("Direct Sound Not Installed - wave");
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Initialise as many sound driver handlers as we can
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (count = 0; count < MAXHANDLERS; count ++)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		soundqueue[count].handler = AIL_allocate_sample_handle(dig);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (soundqueue[count].handler == NULL)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			// We have all the handers we can get, so exit
//DeadCode JIM 25Sep96 			break;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	status.nohandlers = count;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Infinite looping for first sound slot...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_set_sample_loop_count(soundqueue[0].handler,0);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Make sure the smacker is compatible
//DeadCode JIM 25Sep96 	SmackSoundUseMSS (dig);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Reset all samples...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (count = 0; count < MAXSAMPLES; count ++)
//DeadCode JIM 25Sep96 		thesample[count].blockptr = NULL;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	status.notunes = 0;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Timer ???? (not needed for 3D!)
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	timer = NULL;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Initialise callback values...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	request.activated = FALSE;
//DeadCode JIM 25Sep96 	request.fader = FALSE;
//DeadCode JIM 25Sep96 	request.startseq = FALSE;
//DeadCode JIM 25Sep96 	request.startsim = FALSE;
//DeadCode JIM 25Sep96 	request.stopsequence = FALSE;
//DeadCode JIM 25Sep96 	request.runaway = FALSE;
//DeadCode JIM 25Sep96 	request.spottuneno = 0;
//DeadCode JIM 25Sep96 	request.barvol = 0;
//DeadCode JIM 25Sep96 	request.barfadeval = 0;
//DeadCode JIM 25Sep96 	request.spotvol = 0;
//DeadCode JIM 25Sep96 	request.spotfadeval = 0;
//DeadCode JIM 25Sep96 	request.barspotvol = 0;
//DeadCode JIM 25Sep96 	request.barspotfadeval = 0;
//DeadCode JIM 25Sep96 	request.enemytorun = FALSE;
//DeadCode JIM 25Sep96 	request.enemyready = FALSE;
//DeadCode JIM 25Sep96 	request.wait = FALSE;
//DeadCode JIM 25Sep96 	request.spotseqno = 0;
//DeadCode JIM 25Sep96 	request.barhandle = NULL;
//DeadCode JIM 25Sep96 	request.spothandle = NULL;
//DeadCode JIM 25Sep96 	request.barspothandle = NULL;
//DeadCode JIM 25Sep96 	enginedying = FALSE;
//DeadCode JIM 25Sep96 	enginedead = FALSE;
//DeadCode JIM 25Sep96 	canplaynothing = FALSE;
//DeadCode JIM 25Sep96 	deathcount = 0;
//DeadCode JIM 25Sep96 	engineplaying = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		TuneInRange
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 29 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 Bool	Miles::TuneInRange(int	tuneno)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (	(tuneno < 0)
//DeadCode JIM 25Sep96 		||	(tuneno >= MAXTUNES)	)
//DeadCode JIM 25Sep96 		return(FALSE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(TRUE);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		SequenceInRange
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Mon 25 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 Bool	Miles::SequenceInRange(int	tuneno, int	seqno)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (!TuneInRange(tuneno))
//DeadCode JIM 25Sep96 		return(FALSE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (	(seqno < 0)
//DeadCode JIM 25Sep96 		||	(seqno >= tune[tuneno].nosequences)	)
//DeadCode JIM 25Sep96 		return(FALSE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(TRUE);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		SampleInRange
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Mon 25 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 Bool	Miles::SampleInRange(int	sampleno)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (	(sampleno < 0)
//DeadCode JIM 25Sep96 		||	(sampleno >= MAXSAMPLES)	)
//DeadCode JIM 25Sep96 		return(FALSE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(TRUE);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		HandlerInRange
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Mon 25 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 Bool	Miles::HandlerInRange(int	qpos)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (	(qpos < 0)
//DeadCode JIM 25Sep96 		||	(qpos >= status.nohandlers)	)
//DeadCode JIM 25Sep96 		return(FALSE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(TRUE);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		InitTune
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Wed 21 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Initialises all the sequences in the tune and starts them
//DeadCode JIM 25Sep96 //				simultaneously at zero volume	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs				
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		
//DeadCode JIM 25Sep96 //	
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::InitTune(int	tuneno)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	HSEQUENCE	seqhandle;
//DeadCode JIM 25Sep96 	int			sequenceno;
//DeadCode JIM 25Sep96 	LONG		result;
//DeadCode JIM 25Sep96 	Bool		anerror = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (mdi == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	request.activated = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 	// Set up all the sequences in the tune...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (sequenceno = 0; sequenceno < tune[tuneno].nosequences; sequenceno ++)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		seqhandle = tune[tuneno].sequence[sequenceno];
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		result = AIL_init_sequence(seqhandle, getdata(tune[tuneno].blockptr),
//DeadCode JIM 25Sep96 								   sequenceno);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (result == 0	)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			// The sequence could not be found.
//DeadCode JIM 25Sep96 			//
//DeadCode JIM 25Sep96 			//	If the result was -1, then a certain timbre was not found,
//DeadCode JIM 25Sep96 			//	but we can ignore this...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			AIL_shutdown();
//DeadCode JIM 25Sep96 			
//DeadCode JIM 25Sep96 			_Error.EmitSysErr(AIL_last_error());
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 		else
//DeadCode JIM 25Sep96 			AIL_set_sequence_volume(seqhandle,0,0);
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (tuneno == 0)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		// Set up callbacks for main track....
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		AIL_register_trigger_callback(tune[0].sequence[0],mainbeatint);
//DeadCode JIM 25Sep96 		AIL_register_sequence_callback(tune[0].sequence[0],mainendint);
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (tuneno == 1)
//DeadCode JIM 25Sep96 	{	
//DeadCode JIM 25Sep96 		// Set up callbacks for main incidental tracks...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		for (sequenceno = 0; sequenceno < tune[1].nosequences; sequenceno ++)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			AIL_register_trigger_callback(tune[1].sequence[sequenceno],subbeatint);
//DeadCode JIM 25Sep96 			AIL_register_sequence_callback(tune[1].sequence[sequenceno],subendint);
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		StartMain
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 29 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::StartMain(LONG	vol)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int	sequenceno;
//DeadCode JIM 25Sep96 	int	tuneno;
//DeadCode JIM 25Sep96 	int	nosequences;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (mdi == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (tune[0].blockptr == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (request.activated)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Clip the volume if out of range...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	vol = ClipVolume(vol);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Start all sequences in tunes 0, 1 & 2 synchronously
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_set_sequence_volume(tune[0].sequence[0],vol,0);		  // Beat track
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_lock();
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (tuneno = 0; tuneno < 3; tuneno ++)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		nosequences = tune[tuneno].nosequences;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		for (sequenceno = 0; sequenceno < nosequences; sequenceno ++)
//DeadCode JIM 25Sep96 			AIL_start_sequence(tune[tuneno].sequence[sequenceno]);
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_unlock();
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		GetIndex
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Fri 8 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Calculates the index no of a file
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		The file number
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		The file index
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 int	Miles::GetIndex(FileNum	thefile)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	return((thefile & FILENUMMASK) - 1);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		LoadTune
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Wed 21 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Gets a new tune and initialises it
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Filename and number of sequences
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		TRUE  if success
//DeadCode JIM 25Sep96 //				FALSE otherwise
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 Bool	Miles::LoadTune(FileNum	thefile, TuneType	ttype)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	LONG		result, size;
//DeadCode JIM 25Sep96 	void		*tmpptr;
//DeadCode JIM 25Sep96 	LONG		*headptr;
//DeadCode JIM 25Sep96 	int			count;
//DeadCode JIM 25Sep96 	UWORD		noforms = 0;
//DeadCode JIM 25Sep96 	LONG		header;
//DeadCode JIM 25Sep96 	fileblock	*theblock;
//DeadCode JIM 25Sep96 	int			tuneno;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	tuneno = GetIndex(thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (mdi == NULL)
//DeadCode JIM 25Sep96 		return(FALSE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!TuneInRange(tuneno))
//DeadCode JIM 25Sep96 		return(FALSE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// First check if the tune is already present...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (tune[tuneno].blockptr)
//DeadCode JIM 25Sep96 		return(TRUE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// All clear, so load the sequences file...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	theblock = new fileblock (thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	tmpptr = getdata(theblock);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	size = getsize(theblock);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //DeadCode RJS 25Mar96 	tmpptr = FILE_read(safetext,NULL);
//DeadCode JIM 25Sep96 //DeadCode RJS 25Mar96 
//DeadCode JIM 25Sep96 //DeadCode RJS 25Mar96 	size = FILE_size(safetext);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	result = VMM_lock(tmpptr,size);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	if (result == 0)
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	{
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 		AIL_shutdown();
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 		_Error.EmitSysErr("Could not lock the tune memory!\n");
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96   	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	tune[tuneno].blockptr = theblock;
//DeadCode JIM 25Sep96 	tune[tuneno].size = size;
//DeadCode JIM 25Sep96 	status.notunes = status.notunes + 1;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	headptr = (LONG*) tmpptr;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Get IFF_ number of sequences information from header...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (count = 0; count < 5; count ++)
//DeadCode JIM 25Sep96 		header = *headptr++;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	noforms = (UWORD) *headptr;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	tune[tuneno].nosequences = noforms;
//DeadCode JIM 25Sep96 	tune[tuneno].ttype = ttype;
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 	if (ttype != T_seqeffects)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		// Allocate separate sequence handlers for all sequences in the tune,
//DeadCode JIM 25Sep96 		// to allow simultaneous synchronous playing...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		for (count = 0; count < tune[tuneno].nosequences; count ++)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			tune[tuneno].sequence[count] = AIL_allocate_sequence_handle(mdi);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			if (tune[tuneno].sequence[count] == NULL)
//DeadCode JIM 25Sep96 			{
//DeadCode JIM 25Sep96 				AIL_shutdown();
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 				_Error.EmitSysErr(AIL_last_error());
//DeadCode JIM 25Sep96 			}
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		InitTune(tuneno);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 	else
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		// Allocate one sequence handler for all sequences in tune
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		tune[tuneno].sequence[0] = AIL_allocate_sequence_handle(mdi);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (tune[tuneno].sequence[0] == NULL)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			AIL_shutdown();
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			_Error.EmitSysErr(AIL_last_error());
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(TRUE);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		InstallWaveTable
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Wed 21 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Digital waveform table filename		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::InstallWaveTable(FileNum	thefile)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	char		safetext[80];
//DeadCode JIM 25Sep96 	void		*tmpptr;
//DeadCode JIM 25Sep96 	LONG		size, result;
//DeadCode JIM 25Sep96 	fileblock	*theblock;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (mdi == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Set digital preferences with a reasonable latency value for
//DeadCode JIM 25Sep96 	// MIDI-triggered sample playback.
//DeadCode JIM 25Sep96 	//
//DeadCode JIM 25Sep96 	// Request 22kHz stereo output.
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	AIL_set_preference(DIG_LATENCY,					30);
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	AIL_set_preference(DIG_USE_STEREO,				YES);
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	AIL_set_preference(DIG_HARDWARE_SAMPLE_RATE,	22050);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Attempt to load the digital wave library...
//DeadCode JIM 25Sep96 	theblock = new fileblock (thefile);
//DeadCode JIM 25Sep96 	tmpptr = getdata(theblock);
//DeadCode JIM 25Sep96 	size = getsize(theblock);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	result = VMM_lock(tmpptr, size);
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	if (result == 0)
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	{
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 		AIL_shutdown();
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 		_Error.EmitSysErr("Could not secure wave memory!\n");
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	wavetable.blockptr = theblock;
//DeadCode JIM 25Sep96 	wavetable.size = size;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	wavetable.wavesynth = AIL_create_wave_synthesizer(dig, mdi, tmpptr, MAX_W_VOICES);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		ProcessSpot
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Mon 25 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Process interrupt spot-effect data if available.
//DeadCode JIM 25Sep96 //				This procedure initialises the appropriate sequence for the
//DeadCode JIM 25Sep96 //				next callback function with a value of 127.
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //				Ensures the pan and volume of samples are updated in the
//DeadCode JIM 25Sep96 //				3d world.
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //				Chugs the engine.
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		camera world viewpoint
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::ProcessSpot(rotitem	viewpoint)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	LONG	seqno;
//DeadCode JIM 25Sep96 	LONG	tuneno;
//DeadCode JIM 25Sep96 	WORD	engtype;
//DeadCode JIM 25Sep96 	LONG	engloop;
//DeadCode JIM 25Sep96 	LONG	englength;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (	(request.enemyready)
//DeadCode JIM 25Sep96 		&&	(!request.wait)
//DeadCode JIM 25Sep96 		&&	(!request.startseq)			)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (	(request.spotseqno > 50)
//DeadCode JIM 25Sep96 			&&	(request.spotseqno < 58)	)
//DeadCode JIM 25Sep96 			seqno = request.spotseqno - 51;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (	(request.spotseqno > 57)
//DeadCode JIM 25Sep96 			&&	(request.spotseqno < 64)	)
//DeadCode JIM 25Sep96 			seqno = request.spotseqno - 58;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (	(request.spotseqno > 63)
//DeadCode JIM 25Sep96 			&&	(request.spotseqno < 68)  	)
//DeadCode JIM 25Sep96 			seqno = request.spotseqno - 64;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (	(request.spotseqno > 79)
//DeadCode JIM 25Sep96 			&&	(request.spotseqno < 100)  	)
//DeadCode JIM 25Sep96 			seqno = request.spotseqno - 80;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		request.spotseqno = 0;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		// Now initialise the sequence...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		tuneno = request.spottuneno - 97;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (AIL_init_sequence(request.spothandle,
//DeadCode JIM 25Sep96 						getdata(tune[tuneno].blockptr), seqno) <= 0	)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 //			AIL_shutdown();
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			_Error.EmitSysErr("Cannot initialise sequence!\n");
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		request.startseq = TRUE;
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// For sound effects...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (soundtoplay.thesample != FIL_NULL)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		PlaySample(soundtoplay.thesample,soundtoplay.vol,soundtoplay.pan);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		soundtoplay.thesample = FIL_NULL;
//DeadCode JIM 25Sep96 		soundtoplay.vol = 64;
//DeadCode JIM 25Sep96 		soundtoplay.pan = 0;
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (enginedying && !enginedead)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		deathcount++;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (deathcount == 200)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			engineplaying = TRUE;
//DeadCode JIM 25Sep96 			PlaySample(FIL_SFX_ROTARY_STOP2,20,0);
//DeadCode JIM 25Sep96 			enginedead = TRUE;
//DeadCode JIM 25Sep96 			PlayEngine(FIL_SFX_WIND_LOOP,6,0);
//DeadCode JIM 25Sep96 			Update3d(viewpoint);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			return;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (abfactor == AEROBATIC_HIGH)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			engtype = Math_Lib.rnd(4 + damagelevel);
//DeadCode JIM 25Sep96 			englength = thesample[soundqueue[0].sampleindex].size;
//DeadCode JIM 25Sep96 			engloop = englength / (2 + Math_Lib.rnd(5));
//DeadCode JIM 25Sep96 			engloop = englength - engloop;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			if (	(AIL_sample_position(soundqueue[0].handler) > engloop)
//DeadCode JIM 25Sep96 				||	!canplaynothing)
//DeadCode JIM 25Sep96 			{
//DeadCode JIM 25Sep96 				switch (engtype)
//DeadCode JIM 25Sep96 				{
//DeadCode JIM 25Sep96 					case 1:
//DeadCode JIM 25Sep96 						OverrideSample(0,FIL_SFX_ROTARY_CHUGGING1,20,0);
//DeadCode JIM 25Sep96 						engineplaying = TRUE;
//DeadCode JIM 25Sep96 						canplaynothing = TRUE;
//DeadCode JIM 25Sep96 						break;
//DeadCode JIM 25Sep96 					case 2:
//DeadCode JIM 25Sep96 						OverrideSample(0,FIL_SFX_ROTARY_CHUGGING2,20,0);
//DeadCode JIM 25Sep96 						engineplaying = TRUE;
//DeadCode JIM 25Sep96 						canplaynothing = TRUE;
//DeadCode JIM 25Sep96 						break;
//DeadCode JIM 25Sep96 					case 3:
//DeadCode JIM 25Sep96 						OverrideSample(0,FIL_SFX_ROTARY_CHUGGING3,20,0);
//DeadCode JIM 25Sep96 						engineplaying = TRUE;
//DeadCode JIM 25Sep96 						canplaynothing = TRUE;
//DeadCode JIM 25Sep96 						break;
//DeadCode JIM 25Sep96 					default:
//DeadCode JIM 25Sep96 						if (canplaynothing)
//DeadCode JIM 25Sep96 						{
//DeadCode JIM 25Sep96 							PlayEngine(FIL_SFX_WIND_LOOP,6,0);
//DeadCode JIM 25Sep96 							engineplaying = FALSE;
//DeadCode JIM 25Sep96 							canplaynothing = FALSE;
//DeadCode JIM 25Sep96 						}
//DeadCode JIM 25Sep96 				}
//DeadCode JIM 25Sep96 			}
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 		else
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			engtype = Math_Lib.rnd(4 + damagelevel);
//DeadCode JIM 25Sep96 			englength = thesample[soundqueue[0].sampleindex].size;
//DeadCode JIM 25Sep96 			engloop = englength / (2 + Math_Lib.rnd(5));
//DeadCode JIM 25Sep96 			engloop = englength - engloop;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			if (	(AIL_sample_position(soundqueue[0].handler) > engloop)
//DeadCode JIM 25Sep96 				||	!canplaynothing)
//DeadCode JIM 25Sep96 			{
//DeadCode JIM 25Sep96 				switch (engtype)
//DeadCode JIM 25Sep96 				{
//DeadCode JIM 25Sep96 					case 1:
//DeadCode JIM 25Sep96 						OverrideSample(0,FIL_SFX_STATIONARY_CHUGGING1,20,0);
//DeadCode JIM 25Sep96 						engineplaying = TRUE;
//DeadCode JIM 25Sep96 						canplaynothing = TRUE;
//DeadCode JIM 25Sep96 						break;
//DeadCode JIM 25Sep96 					case 2:
//DeadCode JIM 25Sep96 						OverrideSample(0,FIL_SFX_STATIONARY_CHUGGING2,20,0);
//DeadCode JIM 25Sep96 						engineplaying = TRUE;
//DeadCode JIM 25Sep96 						canplaynothing = TRUE;
//DeadCode JIM 25Sep96 						break;
//DeadCode JIM 25Sep96 					case 3:
//DeadCode JIM 25Sep96 						OverrideSample(0,FIL_SFX_STATIONARY_CHUGGING3,20,0);
//DeadCode JIM 25Sep96 						engineplaying = TRUE;
//DeadCode JIM 25Sep96 						canplaynothing = TRUE;
//DeadCode JIM 25Sep96 						break;
//DeadCode JIM 25Sep96 					default:
//DeadCode JIM 25Sep96 						if (canplaynothing)
//DeadCode JIM 25Sep96 						{
//DeadCode JIM 25Sep96 							PlayEngine(FIL_SFX_WIND_LOOP,6,0);
//DeadCode JIM 25Sep96 							engineplaying = FALSE;
//DeadCode JIM 25Sep96 							canplaynothing = FALSE;
//DeadCode JIM 25Sep96 						}
//DeadCode JIM 25Sep96 				}
//DeadCode JIM 25Sep96 			}
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	Update3d(viewpoint);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		KillEngine
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Mon 1 Jul 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Informs the miles code that the engine is damaged
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Damage level (0 - 16)
//DeadCode JIM 25Sep96 //				0 is no damage
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::KillEngine(ClassPtr	classtype, int	dlevel)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (dlevel == damagelevel)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	damagelevel = dlevel;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (damagelevel < 1)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (damagelevel > 16)
//DeadCode JIM 25Sep96 		damagelevel = 16;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	enginedying = TRUE;
//DeadCode JIM 25Sep96 	abfactor = classtype->aerobaticfactor;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_set_sample_loop_count(soundqueue[0].handler,1);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		StartSequence
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Fri 23 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Hard starts a sequence from scratch	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Sequence number, fade time, and fade volume		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::StartSequence(FileNum	thefile, int	sequenceno, LONG	fadeval, LONG	vol)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	HSEQUENCE	seqhandle;
//DeadCode JIM 25Sep96 	int		tuneno;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	tuneno = GetIndex(thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (mdi == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!SequenceInRange(tuneno,sequenceno))
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (tune[tuneno].blockptr == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (request.activated)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	seqhandle = tune[tuneno].sequence[sequenceno];
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	request.activated = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_set_sequence_volume(seqhandle,0,0);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_start_sequence(seqhandle);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_set_sequence_volume(seqhandle,vol,fadeval);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		SequenceAudible
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Fri 23 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Essentially a track volume fader;
//DeadCode JIM 25Sep96 //				Adjusts the volume of the specified sequence	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Tune, Sequence, fade time, fade volume and stomp request
//DeadCode JIM 25Sep96 //				If stomp is FALSE,
//DeadCode JIM 25Sep96 //					a request is placed to fade in/out at an appropriate moment.
//DeadCode JIM 25Sep96 //				otherwise
//DeadCode JIM 25Sep96 //					adjust volume regardless.		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::SequenceAudible(FileNum	thefile, int	sequenceno, LONG	fadeval, LONG	vol)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int		tuneno;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	tuneno = GetIndex(thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (mdi == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 	if (!SequenceInRange(tuneno,sequenceno))
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (tune[tuneno].blockptr == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	vol = ClipVolume(vol);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Block the interrupt callback routine...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	request.activated = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Set up request data depending on tune type...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (tune[tuneno].ttype == T_seqeffects)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (AIL_sequence_status(tune[tuneno].sequence[0]) == SEQ_PLAYING)
//DeadCode JIM 25Sep96 			return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		// Reset interrupt flags...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		request.wait = FALSE;
//DeadCode JIM 25Sep96 		request.enemytorun = FALSE;
//DeadCode JIM 25Sep96 		request.enemyready = FALSE;
//DeadCode JIM 25Sep96 		request.startseq = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		request.spotvol = vol;
//DeadCode JIM 25Sep96 		request.spotfadeval = fadeval;
//DeadCode JIM 25Sep96 		request.spothandle = tune[tuneno].sequence[0];
//DeadCode JIM 25Sep96 		request.spottuneno = tuneno + 100 - 3;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		request.runaway = TRUE;			
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 	else
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (tune[tuneno].ttype == T_main)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			request.barhandle = tune[tuneno].sequence[sequenceno];
//DeadCode JIM 25Sep96 			request.barvol = vol;
//DeadCode JIM 25Sep96 			request.barfadeval = fadeval;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			request.fader = TRUE;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 		else
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			request.barspothandle = tune[tuneno].sequence[sequenceno];
//DeadCode JIM 25Sep96 			request.barspotvol = vol;
//DeadCode JIM 25Sep96 			request.barspotfadeval = fadeval;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			request.startsim = TRUE;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	request.activated = TRUE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		StopSequence
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Fri 23 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Stops a sequence from playing	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Sequence no, and Stomp request		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::StopSequence(FileNum	thefile, int	sequenceno)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	HSEQUENCE	seqhandle;
//DeadCode JIM 25Sep96 	int			tuneno;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	tuneno = GetIndex(thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (mdi == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!SequenceInRange(tuneno,sequenceno))
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (tune[tuneno].blockptr == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (request.activated)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Place a request if we do not want an immediate reaction
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	request.stopsequence = TRUE;
//DeadCode JIM 25Sep96 	request.activated = TRUE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		SequenceMute
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Fri 23 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Fade out sequence	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		The sequence no, the fade time, a stomp request		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::SequenceMute(FileNum	thefile, int	sequenceno, LONG	fadeval)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	SequenceAudible(thefile,sequenceno,fadeval,0);	
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		reporterror
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Tue 27 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::reporterror(int	eno, char	*text)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	status.errorno = eno;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (text)
//DeadCode JIM 25Sep96 		strcpy(status.errorstring,text);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	switch(eno)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 	case 0:
//DeadCode JIM 25Sep96 		_Error.EmitSysErr("Out of range!\n");
//DeadCode JIM 25Sep96 		break;
//DeadCode JIM 25Sep96 	case 2:
//DeadCode JIM 25Sep96 //		AIL_shutdown();
//DeadCode JIM 25Sep96 		_Error.EmitSysErr("Could not play the sample!\n");
//DeadCode JIM 25Sep96 	case 3:
//DeadCode JIM 25Sep96 //		AIL_shutdown();
//DeadCode JIM 25Sep96 		_Error.EmitSysErr("Could not secure the sample memory!\n");
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		LoadSample
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Tue 20 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Gets a sample from disk and stores its information	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Sample number and the filename
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		TRUE if a success,
//DeadCode JIM 25Sep96 //				FALSE otherwise
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 Bool	Miles::LoadSample(FileNum	thefile)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	char		header[10];
//DeadCode JIM 25Sep96 	char		*tmpptr;
//DeadCode JIM 25Sep96 	void		*tmpaddress;
//DeadCode JIM 25Sep96 	int			size;
//DeadCode JIM 25Sep96 	int			count;
//DeadCode JIM 25Sep96 	LONG		result;
//DeadCode JIM 25Sep96 	fileblock	*theblock;
//DeadCode JIM 25Sep96 	int			spos;
//DeadCode JIM 25Sep96 	RIFF		*header1;
//DeadCode JIM 25Sep96 	FMT			*header2;
//DeadCode JIM 25Sep96 	DATA		*header3;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	spos = GetIndex(thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return(FALSE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!SampleInRange(spos))
//DeadCode JIM 25Sep96 		return(FALSE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// If the sample already exists here, then do nothing
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (thesample[spos].blockptr)
//DeadCode JIM 25Sep96 		return(TRUE);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Load the sample as a block
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	theblock = new fileblock (thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	tmpaddress = getdata(theblock);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	size = getsize(theblock);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Make sure the sample in memory is secure...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	result = VMM_lock(tmpaddress, size);
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	if (result == 0)
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 		reporterror(3);
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	elser
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	{
//DeadCode JIM 25Sep96 		thesample[spos].blockptr = theblock;
//DeadCode JIM 25Sep96 		thesample[spos].size = size;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		// Extract header id for file and decide if it is RAW
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		tmpptr = (char*) tmpaddress;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		for (count = 0; count < 4; count ++)
//DeadCode JIM 25Sep96 			header[count] = *tmpptr++;
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 		header[4] = 0;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (	(strcmp(header,"RIFF") == 0)
//DeadCode JIM 25Sep96 			||	(strcmp(header,"Crea") == 0) )
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			thesample[spos].raw = FALSE;
//DeadCode JIM 25Sep96 			header1 = (RIFF*) tmpaddress;
//DeadCode JIM 25Sep96 			header2 = (FMT*) header1->data;
//DeadCode JIM 25Sep96 		
//DeadCode JIM 25Sep96 			while (strnicmp((char *)(header2->FMT_string),"fmt ",4))
//DeadCode JIM 25Sep96     		{
//DeadCode JIM 25Sep96     			header2 = (FMT *) ((BYTE *) header2 +
//DeadCode JIM 25Sep96 			      		header2->chunk_size + 8 + (header2->chunk_size & 1));
//DeadCode JIM 25Sep96     		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			thesample[spos].samplerate = header2->sample_rate;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 		else
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			thesample[spos].raw = TRUE;
//DeadCode JIM 25Sep96 			thesample[spos].samplerate = 44100;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		// Set up temporary priority...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		thesample[spos].priority = spos * PRIORITYFACTOR;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		status.nosamples = status.nosamples +1;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		return(TRUE);
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		SampleRate
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Wed 19 Jun 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Returns the sampling rate of a particular sample file
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		the file
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		the playback rate
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 LONG	Miles::SampleRate(FileNum	thefile)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	return(thesample[GetIndex(thefile)].samplerate);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		LoadList
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Tue 27 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Loads a list of samples into memory	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Pointer to the list of filenames		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::LoadList(char	**list)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 		if (list[count])
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 		{
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 			strcpy(filename,list[count]);
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 			if (LoadSample(count,filename))
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 				count = count + 1;
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 			else
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 				break;
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 		}
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 		else
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 			break;
//DeadCode JIM 25Sep96 //TempCode RJS 01Mar96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		FindFreeHandler
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Tue 20 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Finds a free position in the sound queue.
//DeadCode JIM 25Sep96 //				If there is not one available then replace lowest priority sound
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		The priority of the sound handlers
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		Queue index
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 int		Miles::FindFreeHandler(int	priority)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int		count;
//DeadCode JIM 25Sep96 	int		lowest = 0;
//DeadCode JIM 25Sep96 	int		queuepos = -1;
//DeadCode JIM 25Sep96 	int		lowpos = -1;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (count = 1; count < status.nohandlers; count ++)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		soundqueue[count].playingpriority =
//DeadCode JIM 25Sep96 			soundqueue[count].playingpriority + 1;				//RJS 04Jul96
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (soundqueue[count].playingpriority > lowest)			//RJS 04Jul96
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			lowest = soundqueue[count].playingpriority;
//DeadCode JIM 25Sep96 			lowpos = count;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (	(AIL_sample_status(soundqueue[count].handler) == SMP_DONE)
//DeadCode JIM 25Sep96 			&&	(queuepos == -1)											)
//DeadCode JIM 25Sep96 			queuepos = count;
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// If there were no free slots, then grab the one with the lowest priority
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (queuepos == -1)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		queuepos = lowpos;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (priority > lowest)									//RJS 04Jul96
//DeadCode JIM 25Sep96 			return(-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		AIL_end_sample(soundqueue[queuepos].handler);
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(queuepos);
//DeadCode JIM 25Sep96 		
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		ClipVolume
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 7 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 LONG	Miles::ClipVolume(LONG	vol)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (vol < 0)
//DeadCode JIM 25Sep96 		vol = 0;  			// Too quiet
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (vol > 127)
//DeadCode JIM 25Sep96 		vol = 127;			// Too loud
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(vol);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		ClipPan
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 7 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		+/-32K clipped to +/-10K then shifted to +/- 64
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		0..127
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 LONG	Miles::ClipPan(LONG	pan)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	// Clip the pan...
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (pan < -16383)
//DeadCode JIM 25Sep96 		pan = -16383;		// Hard left
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (pan > 16383)
//DeadCode JIM 25Sep96 		pan = 16383;			// Hard right
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	pan = (pan / 256) + 64;			// Scale and shift to acceptible range
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(pan);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		SoundInWorld
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Tue 25 Jun 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 LONG	Miles::SoundInWorld(LONG	x, LONG	y, LONG	z, rotitem viewpoint, LONG	&vol)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	SLong	distance = 0;
//DeadCode JIM 25Sep96 	SLong	dx = 0;
//DeadCode JIM 25Sep96 	SLong	dy, dz;
//DeadCode JIM 25Sep96 	ULong	big;
//DeadCode JIM 25Sep96 	ULong	big2;
//DeadCode JIM 25Sep96 	float	frac;
//DeadCode JIM 25Sep96 	SWord	hdg = 0;
//DeadCode JIM 25Sep96 	SWord	hdg1 = 0;
//DeadCode JIM 25Sep96 	SWord	pitch;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	dx = x - viewpoint.World.X;
//DeadCode JIM 25Sep96 	dy = y - viewpoint.World.Y;
//DeadCode JIM 25Sep96 	dz = z - viewpoint.World.Z;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	Math_Lib.Intercept(dx,dy,dz,distance,hdg,pitch);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	hdg1 = viewpoint.hdg;
//DeadCode JIM 25Sep96 	hdg = hdg + hdg1;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (hdg > 16383)
//DeadCode JIM 25Sep96 		hdg = 32767 - hdg;
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 	if (hdg < -16383)
//DeadCode JIM 25Sep96 		hdg = -32768 - hdg;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //TempCode RJS 04Jul96 	if (distance > 100000)
//DeadCode JIM 25Sep96 //TempCode RJS 04Jul96 		vol = 0;
//DeadCode JIM 25Sep96 //TempCode RJS 04Jul96 	else
//DeadCode JIM 25Sep96 //TempCode RJS 04Jul96 	{
//DeadCode JIM 25Sep96 //TempCode RJS 04Jul96 		big = 100000 - distance;
//DeadCode JIM 25Sep96 //TempCode RJS 04Jul96 		big2 = (127 * big) / 100000;
//DeadCode JIM 25Sep96 //TempCode RJS 04Jul96 		vol = big2;
//DeadCode JIM 25Sep96 //TempCode RJS 04Jul96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (distance < 45537)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		distance += 20000;
//DeadCode JIM 25Sep96 		distance /= 4;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		big = 8UL*20000UL*20000UL;
//DeadCode JIM 25Sep96 		big2 = distance * distance;
//DeadCode JIM 25Sep96 		vol = big / big2;
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 	else
//DeadCode JIM 25Sep96 		if (distance > 159000)
//DeadCode JIM 25Sep96 			vol = 0;
//DeadCode JIM 25Sep96 		else
//DeadCode JIM 25Sep96 			if (distance > 92014)
//DeadCode JIM 25Sep96 				vol = 1;
//DeadCode JIM 25Sep96 			else
//DeadCode JIM 25Sep96 				if (distance > 71000)
//DeadCode JIM 25Sep96 					vol = 3;
//DeadCode JIM 25Sep96 				else
//DeadCode JIM 25Sep96 					if (distance > 60000)
//DeadCode JIM 25Sep96 						vol = 8;
//DeadCode JIM 25Sep96 					else
//DeadCode JIM 25Sep96 						vol = 11;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return((LONG) hdg);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		Update3d
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 27 Jun 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	update the 3d sound world if any sound is playing
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		current 'camera' position in world
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::Update3d(rotitem	viewpoint)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int		count;
//DeadCode JIM 25Sep96 	LONG	pan;
//DeadCode JIM 25Sep96 	LONG	vol;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (count = 1; count < status.nohandlers; count++)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (	(AIL_sample_status(soundqueue[count].handler) == SMP_PLAYING)
//DeadCode JIM 25Sep96 			&&	(soundqueue[count].transitem == TRUE)	)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 			pan = ClipPan(SoundInWorld(soundqueue[count].x,soundqueue[count].y,soundqueue[count].z,viewpoint,vol));
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			if (vol == 0)
//DeadCode JIM 25Sep96 			{
//DeadCode JIM 25Sep96 				AIL_end_sample(soundqueue[count].handler);
//DeadCode JIM 25Sep96 				return;
//DeadCode JIM 25Sep96 			}
//DeadCode JIM 25Sep96 				
//DeadCode JIM 25Sep96 			AIL_set_sample_pan	 (soundqueue[count].handler, pan);
//DeadCode JIM 25Sep96 		    AIL_set_sample_volume(soundqueue[count].handler, vol);
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		PlaySettings
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 7 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::PlaySettings(int	qpos, ItemBasePtr sampleitem, rotitem	viewpoint, LONG	vol, LONG	pan, int priority, LONG	thefreq)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int		volscale;
//DeadCode JIM 25Sep96 	Bool	changevol = FALSE;
//DeadCode JIM 25Sep96 	Bool	changepan = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!HandlerInRange(qpos))
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (sampleitem)
//DeadCode JIM 25Sep96 		pan = SoundInWorld(sampleitem->World.X,sampleitem->World.Y,sampleitem->World.Z,viewpoint,vol);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (vol > -1)
//DeadCode JIM 25Sep96 		changevol = TRUE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (pan > -50000)
//DeadCode JIM 25Sep96 		changepan = TRUE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	vol = ClipVolume(vol);
//DeadCode JIM 25Sep96 	pan = ClipPan(pan);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	volscale = (127 - vol) / 16;
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	soundqueue[qpos].playingpriority = priority + volscale;
//DeadCode JIM 25Sep96 	soundqueue[qpos].playingvolume = vol;
//DeadCode JIM 25Sep96 	soundqueue[qpos].playingpan = pan;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (thefreq != 0)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (	(thefreq < 5000)
//DeadCode JIM 25Sep96 			||	(thefreq > 48000)	)
//DeadCode JIM 25Sep96 			return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		AIL_set_sample_playback_rate(soundqueue[qpos].handler,thefreq);
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (changepan)
//DeadCode JIM 25Sep96 		AIL_set_sample_pan	 (soundqueue[qpos].handler, pan);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (changevol)
//DeadCode JIM 25Sep96 	    AIL_set_sample_volume(soundqueue[qpos].handler, vol);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		SetUpSample
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Mon 4 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Initialises a sample for a handler and plays it	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::SetUpSample(int	qpos, int	spos, LONG	vol, LONG	pan, ItemBasePtr	sampleitem, rotitem	viewpoint)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	void		*address;
//DeadCode JIM 25Sep96 	int			size;
//DeadCode JIM 25Sep96 	HSAMPLE		handler;
//DeadCode JIM 25Sep96 	LONG		result;
//DeadCode JIM 25Sep96 	int			priority;
//DeadCode JIM 25Sep96 	Bool		isloop = FALSE;									//DAW 30Jun96
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (	(spos > GetIndex(FIL_SFX_LOOP_FX_START))
//DeadCode JIM 25Sep96 		&&	(spos < GetIndex(FIL_SFX_LOOP_FX_END))	)
//DeadCode JIM 25Sep96 		isloop = TRUE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	handler = soundqueue[qpos].handler;
//DeadCode JIM 25Sep96 	address = getdata(thesample[spos].blockptr);
//DeadCode JIM 25Sep96 	size = thesample[spos].size;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	soundqueue[qpos].sampleindex = spos;
//DeadCode JIM 25Sep96 	priority = thesample[spos].priority;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (thesample[spos].raw)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		// Set up the sample manually
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		AIL_init_sample             (handler                 );
//DeadCode JIM 25Sep96         AIL_set_sample_type         (handler, DIG_F_MONO_8, 0);
//DeadCode JIM 25Sep96         AIL_set_sample_address      (handler, address, size  );
//DeadCode JIM 25Sep96         AIL_set_sample_playback_rate(handler, 44100          );
//DeadCode JIM 25Sep96         
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 	else
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		// It is a .VOC or .WAV file
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		result = AIL_set_sample_file(handler,address,-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		if (result == 0)
//DeadCode JIM 25Sep96 			reporterror(2);
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	PlaySettings(qpos,sampleitem,viewpoint,vol,pan,priority);
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 	if (sampleitem)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		soundqueue[qpos].x = (LONG) sampleitem->World.X;
//DeadCode JIM 25Sep96 		soundqueue[qpos].y = (LONG) sampleitem->World.Y;
//DeadCode JIM 25Sep96 		soundqueue[qpos].z = (LONG) sampleitem->World.Z;
//DeadCode JIM 25Sep96 		soundqueue[qpos].transitem = TRUE;
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 	else
//DeadCode JIM 25Sep96 		soundqueue[qpos].transitem = FALSE;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (	(qpos > 0)
//DeadCode JIM 25Sep96 		||	enginedying)
//DeadCode JIM 25Sep96 		if (isloop)
//DeadCode JIM 25Sep96 			AIL_set_sample_loop_count(handler,0);
//DeadCode JIM 25Sep96 		else
//DeadCode JIM 25Sep96 			AIL_set_sample_loop_count(handler,1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		PlaySample
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Tue 25 Jun 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 int 	Miles::PlaySample(FileNum	thefile, rotitem viewpoint, ItemBasePtr	sampleitem)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int		qpos;
//DeadCode JIM 25Sep96 	int		spos;
//DeadCode JIM 25Sep96 	int		vol = 30;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	spos = GetIndex(thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return(-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!SampleInRange(spos))
//DeadCode JIM 25Sep96 		return(-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (thesample[spos].blockptr == NULL)
//DeadCode JIM 25Sep96 		if(!LoadSample(thefile))
//DeadCode JIM 25Sep96 			return(-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	qpos = FindFreeHandler(thesample[spos].priority);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (qpos > -1)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		SetUpSample(qpos,spos,vol,0,sampleitem,viewpoint);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		AIL_start_sample(soundqueue[qpos].handler);
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(qpos);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		PlaySample
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Tue 20 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Soft start a sample; finds a suitable slot in the sound
//DeadCode JIM 25Sep96 //				handler queue then starts it.
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		The sample number, its volume, its stereo pan (0 is central)		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		The sample that has been played.
//DeadCode JIM 25Sep96 //				-1 if it has failed
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 int 	Miles::PlaySample(FileNum	thefile, LONG	vol, LONG	pan, ItemBasePtr	sampleitem)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int		qpos;
//DeadCode JIM 25Sep96 	int		spos;
//DeadCode JIM 25Sep96 	rotitem	viewdummy;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	spos = GetIndex(thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return(-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!SampleInRange(spos))
//DeadCode JIM 25Sep96 		return(-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (thesample[spos].blockptr == NULL)
//DeadCode JIM 25Sep96 		if(!LoadSample(thefile))
//DeadCode JIM 25Sep96 			return(-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	qpos = FindFreeHandler(thesample[spos].priority);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (qpos > -1)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		SetUpSample(qpos,spos,vol,pan,sampleitem,viewdummy);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		AIL_start_sample(soundqueue[qpos].handler);
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(qpos);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 		
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		OverrideSample
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Mon 4 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Hard start a sample on a known handler
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Sound queue index, sample index, volume and pan
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::OverrideSample(int	qpos, FileNum	thefile, LONG	vol, LONG	pan)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int		spos;
//DeadCode JIM 25Sep96 	rotitem	viewdummy;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	spos = GetIndex(thefile);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!HandlerInRange(qpos))
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!SampleInRange(spos))
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (thesample[spos].blockptr == NULL)
//DeadCode JIM 25Sep96 		if(!LoadSample(thefile))
//DeadCode JIM 25Sep96 			return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_stop_sample(soundqueue[qpos].handler);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	SetUpSample(qpos,spos,vol,pan,NULL,viewdummy);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_start_sample(soundqueue[qpos].handler);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		StopSample
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Fri 8 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Hard stops the sample from playing
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		Position in sample handler queue
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		The sample previously playing there
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 int	Miles::StopSample(int	qpos)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return(-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (!HandlerInRange(qpos))
//DeadCode JIM 25Sep96 		return(-1);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_end_sample(soundqueue[qpos].handler);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	return(soundqueue[qpos].sampleindex);
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		PlayEngine
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 7 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Starts the engine sound
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		The sample for the engine, its volume and pan
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::PlayEngine(FileNum	thefile, LONG	vol, LONG	pan)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (GetIndex(thefile) > GetIndex(FIL_SFX_LOOP_FX_START))
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (!engineplaying)
//DeadCode JIM 25Sep96 			return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		engineplaying = FALSE;
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 	else
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (engineplaying || enginedying)
//DeadCode JIM 25Sep96 			return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 		engineplaying = TRUE;
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	AIL_set_sample_loop_count(soundqueue[0].handler,0);
//DeadCode JIM 25Sep96    	OverrideSample(0,thefile,vol,pan);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		ChangeEngine
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 7 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Alter the frequency, pan and volume settings for the engine
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		delta frequency, pan and volume
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::ChangeEngine(LONG	dfreq, LONG	pan, LONG	vol)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	rotitem	viewdummy;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (	(dig == NULL)
//DeadCode JIM 25Sep96 		||	(!engineplaying)
//DeadCode JIM 25Sep96 		||	(enginedying)	)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	PlaySettings(0,NULL,viewdummy,vol,pan,soundqueue[0].playingpriority,dfreq);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		StopEngine
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Fri 8 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Stops the engine sample
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::StopEngine()
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	StopSample(0);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		PlayGun
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 9 May 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Starts a sample for the gunfire and loops it continuously
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::PlayGun(FileNum	thefile, LONG	vol, LONG	pan)
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96    	OverrideSample(1,thefile,vol,pan);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		StopGun
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 9 May 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Stops the gunfire sample
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::StopGun()
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	StopSample(1);
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		StopAll
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Thu 9 May 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Halts all the sound samples
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::StopAll()
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int	qpos;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (qpos = 0; qpos < status.nohandlers; qpos ++)
//DeadCode JIM 25Sep96 		StopSample(qpos);
//DeadCode JIM 25Sep96 		
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		FreeSamples
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Mon 4 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Frees all the samples in memory
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::FreeSamples()
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int	count;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (dig == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (count = 0; count < MAXSAMPLES; count ++)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (thesample[count].blockptr)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 			VMM_unlock(getdata(thesample[count].blockptr), thesample[count].size);
//DeadCode JIM 25Sep96 			delete thesample[count].blockptr;
//DeadCode JIM 25Sep96 			
//DeadCode JIM 25Sep96 			thesample[count].blockptr = NULL;	
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	status.nosamples = 0;
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		FreeTunes
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Mon 4 Mar 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Frees all the tunes in memory	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::FreeTunes()
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int	tuneno;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (mdi == NULL)
//DeadCode JIM 25Sep96 		return;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	for (tuneno = 0; tuneno < MAXTUNES; tuneno++)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 		if (tune[tuneno].blockptr)
//DeadCode JIM 25Sep96 		{
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 			VMM_unlock(getdata(tune[tuneno].blockptr),tune[tuneno].size);
//DeadCode JIM 25Sep96 			delete tune[tuneno].blockptr;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 			tune[tuneno].blockptr = NULL;
//DeadCode JIM 25Sep96 		}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	status.notunes = 0;
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		ShutDownMiles
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Wed 21 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Close down all music drivers and free associated memory	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 void	Miles::ShutDownMiles()
//DeadCode JIM 25Sep96 {
//DeadCode JIM 25Sep96 	int		tuneno;
//DeadCode JIM 25Sep96 	int		count;
//DeadCode JIM 25Sep96 	LONG	result;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	if (wavetable.wavesynth)
//DeadCode JIM 25Sep96 	{
//DeadCode JIM 25Sep96 //WINMOD		AIL_destroy_wave_synthesizer(wavetable.wavesynth);
//DeadCode JIM 25Sep96 //DeadCode ARM 15Jul96 		VMM_unlock(getdata(wavetable.blockptr),wavetable.size);
//DeadCode JIM 25Sep96 		delete wavetable.blockptr;
//DeadCode JIM 25Sep96 	}
//DeadCode JIM 25Sep96 		
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 //WINMOD	if (dig)
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 //WINMOD		AIL_uninstall_DIG_driver(dig);
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 //WINMOD	if (mdi)
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 //WINMOD		AIL_uninstall_MDI_driver(mdi);
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 	if (timer)
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 		AIL_release_timer_handle(timer-1);
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 
//DeadCode JIM 25Sep96 //TempCode ARM 15Jul96 	if (dig || mdi || timer)
//DeadCode JIM 25Sep96 		AIL_shutdown();
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 	FreeTunes();
//DeadCode JIM 25Sep96 	FreeSamples();
//DeadCode JIM 25Sep96 	
//DeadCode JIM 25Sep96 	wavetable.blockptr = NULL;
//DeadCode JIM 25Sep96 	dig = NULL;
//DeadCode JIM 25Sep96 	mdi = NULL;
//DeadCode JIM 25Sep96 	timer = NULL;
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 }
//DeadCode JIM 25Sep96 
//DeadCode JIM 25Sep96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 25Sep96 //Procedure		main
//DeadCode JIM 25Sep96 //Author		Robert Slater
//DeadCode JIM 25Sep96 //Date			Wed 21 Feb 1996
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Description	Test my midi library	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Inputs		
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //Returns	
//DeadCode JIM 25Sep96 //
//DeadCode JIM 25Sep96 //------------------------------------------------------------------------------
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96 void	main()
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96 {
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  	char	input;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  	int		playtrackno;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  	int		mutetrackno;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  	setbuf(stdout,NULL);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  	_Miles.StartUpMiles();
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  	if (	_Miles.LoadTune(0,FIL_IN_GAME_BASE_MUSIC,_Miles.T_main)
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  		&&	_Miles.LoadTune(1,FIL_IN_GAME_INCIDENTAL_MUSIC,_Miles.T_main) 	
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  		&&	_Miles.LoadTune(2,FIL_IN_GAME_SIM_EFFECTS_MUSIC,_Miles.T_simeffects)
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  		&&	_Miles.LoadTune(3,FIL_IN_GAME_SEQ_EFFECTS_MUSIC,_Miles.T_seqeffects)	)
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  	{
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  		if (	_Miles.LoadSample(0,FIL_IN_GAME_SAMPLE1)
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			&&	_Miles.LoadSample(1,FIL_IN_GAME_SAMPLE2)	)
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			printf("Samples loaded ok\n");
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  		_Miles.StartMain();
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  		input = 'r';
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  		while (input != '0')
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  		{
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			input = getch();
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			playtrackno = input - '1';
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			if (_Miles.InRange(1,playtrackno))
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(1,playtrackno,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			switch(input)
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			{
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'q':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceMute(1,0,1000);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'w':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceMute(1,1,1000);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'e':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceMute(1,2,1000);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'r':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceMute(1,3,1000);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 't':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceMute(1,4,1000);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'y':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceMute(1,5,1000);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'a':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(2,0,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 's':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(2,1,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'd':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(2,2,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'f':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(2,3,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'g':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(2,4,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'z':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.PlaySample(0,100,0);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'x':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(3,0,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'c':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(3,1,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'v':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(3,2,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			case 'b':
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				_Miles.SequenceAudible(3,3,500,127);
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  				break;
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  			}
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  		}
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  	}
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96  	_Miles.ShutDownMiles();
//DeadCode JIM 25Sep96  
//DeadCode JIM 25Sep96 //TempCode RJS 04Mar96 }

THIS IS DEAD... MILES.CPP DOES BOTH WIN AND DOS


