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
//Filename       milestub.cpp
//System         
//Author         Andy McRae
//Date           Tue 4 Jun 1996
//Description    Stub Functions for miles.cpp
//------------------------------------------------------------------------------


#include 	"dosdefs.h"
#define 	F_GRAFIX
#include	"files.g"
#include	"fileman.h"
#include	"miles.h"
#include	"Mytime.h"											//PD 15Mar96
#include	"worldinc.h"										//ARM 01Jul96

Miles _Miles={0};
TimerCode Timer_Code;											//PD 15Mar96

 		Miles::SequenceStruct	Miles::tune[MAXTUNES];
 		Miles::MusicRequest		Miles::request;


#pragma off (check_stack);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		mainbeatint
//Author		Robert Slater
//Date			Thu 22 Feb 1996
//
//Description	Interrupt routine that is trigered by the main track on hitting
//				certain marked bars.	
//
//Inputs		Caller sequence handler, channel and value		
//
//Returns	
//
//------------------------------------------------------------------------------
void	cdecl Miles::mainbeatint(HSEQUENCE callerseq, LONG	channel, LONG	value)
{
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
void	cdecl Miles::subbeatint(HSEQUENCE callerseq, LONG	channel, LONG	value)
{
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
void	cdecl Miles::mainendint(HSEQUENCE callerseq)
{
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
void	cdecl Miles::subendint(HSEQUENCE callerseq)
{
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
void	cdecl Miles::timerint(ULONG	user)
{
}

#pragma on (check_stack);
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
void	Miles::StartUpMiles()
{
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
	return (FALSE);
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
Bool	Miles::SequenceInRange(int	tuneno, int	seqno)
{
	return(FALSE);
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
	return(FALSE);
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
	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitTune
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Initialises all the sequences in the tune and starts them
//				simultaneously at zero volume	
//
//Inputs				
//
//Returns		
//	
//------------------------------------------------------------------------------
void	Miles::InitTune(int	tuneno)
{
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
void	Miles::StartMain(LONG	vol)
{
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
	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadTune
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Gets a new tune and initialises it
//
//Inputs		Filename and number of sequences
//
//Returns		TRUE  if success
//				FALSE otherwise
//
//------------------------------------------------------------------------------
Bool	Miles::LoadTune(FileNum	thefile, TuneType	ttype)
{
	return(FALSE);
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
void	Miles::InstallWaveTable(FileNum	thefile)
{
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
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::ProcessSpot(rotitem	viewpoint)					//ARM 01Jul96
{
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
void	Miles::StartSequence(FileNum	thefile, int	sequenceno, LONG	fadeval, LONG	vol)
{
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
void	Miles::SequenceAudible(FileNum	thefile, int	sequenceno, LONG	fadeval, LONG	vol)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopSequence
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	Stops a sequence from playing	
//
//Inputs		Sequence no, and Stomp request		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopSequence(FileNum	thefile, int	sequenceno)
{
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
void	Miles::SequenceMute(FileNum	thefile, int	sequenceno, LONG	fadeval)
{
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
Bool	Miles::LoadSample(FileNum	thefile)
{
	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadList
//Author		Robert Slater
//Date			Tue 27 Feb 1996
//
//Description	Loads a list of samples into memory	
//
//Inputs		Pointer to the list of filenames		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::LoadList(char	**list)
{
//TempCode RJS 01Mar96 	char	filename[80];
//TempCode RJS 01Mar96 	int		count = 0;
//TempCode RJS 01Mar96 
//TempCode RJS 01Mar96 
//TempCode RJS 01Mar96 	while (count < MAXSAMPLES)
//TempCode RJS 01Mar96 	{
//TempCode RJS 01Mar96 		if (list[count])
//TempCode RJS 01Mar96 		{
//TempCode RJS 01Mar96 			strcpy(filename,list[count]);
//TempCode RJS 01Mar96 
//TempCode RJS 01Mar96 			if (LoadSample(count,filename))
//TempCode RJS 01Mar96 				count = count + 1;
//TempCode RJS 01Mar96 			else
//TempCode RJS 01Mar96 				break;
//TempCode RJS 01Mar96 		}
//TempCode RJS 01Mar96 		else
//TempCode RJS 01Mar96 			break;
//TempCode RJS 01Mar96 	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeHandler
//Author		Robert Slater
//Date			Tue 20 Feb 1996
//
//Description	Finds a free position in the sound queue.
//				If there is not one available then replace lowest priority sound
//
//Inputs		The priority of the sound handlers
//
//Returns		Queue index
//
//------------------------------------------------------------------------------
int		Miles::FindFreeHandler(int	priority)
{
	return(FALSE);
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
LONG	Miles::ClipVolume(LONG	vol)
{
	return(FALSE);
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
LONG	Miles::ClipPan(LONG	pan)
{
	return(FALSE);
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
void	Miles::PlaySettings(int	qpos, ItemBasePtr	sampleitem, rotitem	viewpoint, LONG	vol, LONG	pan, int priority, LONG	dfreq)//ARM 01Jul96
{
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
void	SetUpSample(int	qpos, int	spos, LONG	vol, LONG	pan, ItemBasePtr	sampleitem, rotitem	viewpoint)//ARM 01Jul96
{
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
int 	Miles::PlaySample(FileNum	thefile, LONG	vol, LONG	pan, ItemBasePtr	sampleitem)
{
	return(FALSE);
}

int 	Miles::PlaySample(FileNum	thefile, rotitem viewpoint, ItemBasePtr	sampleitem)//ARM 01Jul96
{																//ARM 01Jul96
	return(FALSE);												//ARM 01Jul96
}																//ARM 01Jul96
		
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OverrideSample
//Author		Robert Slater
//Date			Mon 4 Mar 1996
//
//Description	Hard start a sample on a known handler
//
//Inputs		Sound queue index, sample index, volume and pan
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::OverrideSample(int	qpos, FileNum	thefile, LONG	vol, LONG	pan)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopSample
//Author		Robert Slater
//Date			Fri 8 Mar 1996
//
//Description	Hard stops the sample from playing
//
//Inputs		Position in sample handler queue
//
//Returns		The sample previously playing there
//
//------------------------------------------------------------------------------
int	Miles::StopSample(int	qpos)
{
	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayEngine
//Author		Robert Slater
//Date			Thu 7 Mar 1996
//
//Description	Starts the engine sound
//
//Inputs		The sample for the engine, its volume and pan
//
//Returns		
//
//------------------------------------------------------------------------------
void	Miles::PlayEngine(FileNum	thefile, LONG	vol, LONG	pan)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChangeEngine
//Author		Robert Slater
//Date			Thu 7 Mar 1996
//
//Description	Alter the frequency, pan and volume settings for the engine
//
//Inputs		delta frequency, pan and volume
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::ChangeEngine(LONG	dfreq, LONG	pan, LONG	vol)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopEngine
//Author		Robert Slater
//Date			Fri 8 Mar 1996
//
//Description	Stops the engine sample
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopEngine()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayGun
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
void	Miles::PlayGun(FileNum	thefile, LONG	vol, LONG	pan)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopGun
//Author		Robert Slater
//Date			Thu 9 May 1996
//
//Description	Stops the gunfire sample
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Miles::StopGun()
{
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
}
