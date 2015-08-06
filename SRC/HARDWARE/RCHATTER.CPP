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
//Filename       rchatter.cpp
//System         
//Author         Robert Slater
//Date           Mon 8 Jun 1998
//Description    
//------------------------------------------------------------------------------

#include 	"dosdefs.h"
#include 	<string.h>
#define 	F_GRAFIX
#include	"files.g"
#include	"fileman.h"
#include	"worldinc.h"
#include	"miles.h"
#include	"mymath.h"
#include	"world.h"
#include	"worldinc.h"
#include	"savegame.h"
#include	"rchatter.h"
#include	"..\mfc\resource.h"
#include	"radioxtr.g"
#include	"messengn.h"
#include	"flyinit.h"										//RJS 10Feb99
#include	"missman2.h"
#include	"cstring.h"
#include	"replay.h"											//AMM 14Apr99

RadioChatter	_Radio;

//static	ULong	totmess = 0;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RadioChatter
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
RadioChatter::RadioChatter()
{
	int	count,count2;
	RadioSampleRec	*RPtr;

	for (count2 = 0; count2 < VOICE_MAX; count2++)
	{
		for (count=0; count < MaxSamples;count++)
		{
			RPtr = &radiosamples[count][count2];

			RPtr->blockptr = NULL;
			RPtr->size = 0;
			RPtr->offsetptr = NULL;
			RPtr->headerptr = NULL;
			RPtr->noFiles = 0;
		}
	}

	RootMessPtr = NULL;

	theSectors.theblock = NULL;
	theSectors.PlaceNames = NULL;
	theSectors.noelements = 0;

//	Save_Data.vol.rchat = 127;

 	MessageCount = 0;

	timesincelast = 0;
	timesincestart = 0;

	theScripts.theblock = NULL;
	theScripts.ScriptTable = NULL;

	windHeightSet = 0;											//RJS 10Feb99
	windSpeedSet = -1;											//RJS 10Feb99

	totmess = 0;

	View_Point= NULL;

	voicechoiceFAC = 0;											//RJS 17May99
	voicechoiceTOWER = 0;										//RJS 17May99
	voicechoiceV2 = 0;											//RJS 08Jun99

	hipriSet = false;											//RJS 25May99
	lockout = false;											//RJS 04Jun99
}

void	RadioChatter::SetUpRandomVoices()
{
//Dead	voicechoiceFAC = Math_Lib.rnd(2);
//Dead	voicechoiceTOWER = Math_Lib.rnd(3);
//Dead	voicechoiceV2 = Math_Lib.rnd(2);											//RJS 08Jun99

	int	count2,count;
	RadioSampleRec	*RPtr;
	for (count2 = 0; count2 < VOICE_MAX; count2++)
	{
		for (count=0; count < MaxSamples; count++)
		{
			RPtr = &radiosamples[count][count2];
			if (RPtr->blockptr)
				delete RPtr->blockptr;

			RPtr->blockptr = NULL;
			RPtr->size = 0;
			RPtr->offsetptr = NULL;
			RPtr->headerptr = NULL;
			RPtr->noFiles = 0;
		}
	}

	//Clean-up any old stuff...
	RadioMessageP	MessPtr = RootMessPtr;
	RadioMessageP	TmpMessPtr;
	while (MessPtr)
	{
		TmpMessPtr = MessPtr->next;

		if (MessPtr->sampleptr)
			delete[]MessPtr->sampleptr;

		MessPtr->caller = NULL;
		MessPtr->callee = NULL;
		MessPtr->target = NULL;
		MessPtr->distance = -1;
		MessPtr->samplesize = 0;

		delete MessPtr;

		MessPtr = TmpMessPtr;
	}

	RootMessPtr = NULL;

	if (FILEMAN.getTotalMem() <= MEMORY_MIN)									//RJS 08Jun99
	{
		//this is the cheapest combination...	16,957,157	bytes
		// we might have to load an alternate DENTIST PLACENAMES table (same trick as V2)
		voicechoiceFAC = 0;				
		voicechoiceTOWER = 1;
		voicechoiceV2= 0;
	}
	else
	{
		voicechoiceFAC = Math_Lib.rnd(2);
		voicechoiceTOWER = Math_Lib.rnd(3);
		voicechoiceV2 = Math_Lib.rnd(2);
	}

	_Miles.SetUpRandomVoices(voicechoiceFAC,voicechoiceTOWER,voicechoiceV2);

	//Random frequencies...										//RJS 06Jul99
	for (count = 0; count < MaxPilots; count++)					//RJS 06Jul99
		randomvoice[count] = Math_Lib.rnd(1000) - 750;			//RJS 06Jul99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RadioChatter
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
RadioChatter::~RadioChatter()
{
	int	count,count2;
	RadioSampleRec	*RPtr;
	RadioMessageP	MessPtr = RootMessPtr;
	RadioMessageP	TmpMessPtr;

	for (count2 = 0; count2 < VOICE_MAX; count2++)
	{
		for (count=0; count < MaxSamples; count++)
		{
			RPtr = &radiosamples[count][count2];
			if (RPtr->blockptr)
				delete RPtr->blockptr;

			RPtr->blockptr = NULL;
			RPtr->size = 0;
			RPtr->offsetptr = NULL;
			RPtr->headerptr = NULL;
			RPtr->noFiles = 0;
		}
	}

	while (MessPtr)
	{
		TmpMessPtr = MessPtr->next;

		if (MessPtr->sampleptr)
			delete[]MessPtr->sampleptr;

		MessPtr->caller = NULL;
		MessPtr->callee = NULL;
		MessPtr->target = NULL;
		MessPtr->distance = -1;
		MessPtr->samplesize = 0;

		delete MessPtr;

		MessPtr = TmpMessPtr;
	}

	RootMessPtr = NULL;

	delete theSectors.theblock;
	delete theScripts.theblock;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayMessage
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode RJS 27Jan99 void	RadioChatter::PlayMessage(	int		Scriptno,
//DeadCode RJS 27Jan99 									TargetIndexes&	tstruc,
//DeadCode RJS 27Jan99 									ItemPtr	Caller,
//DeadCode RJS 27Jan99 									ItemPtr	Trg,
//DeadCode RJS 27Jan99 									ItemPtr	Callee,
//DeadCode RJS 27Jan99 									Bool	noCaller	)
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	if (Save_Data.vol.rchat)
//DeadCode RJS 27Jan99 	{
//DeadCode RJS 27Jan99 		RadioMessageP	MessPtr = CreateMessage((mobileitem*)Caller,
//DeadCode RJS 27Jan99 												(mobileitem*)Trg,
//DeadCode RJS 27Jan99 												(mobileitem*)Callee,
//DeadCode RJS 27Jan99 												tstruc	);
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 		if (MessPtr)
//DeadCode RJS 27Jan99 		{
//DeadCode RJS 27Jan99 			if (!noCaller)
//DeadCode RJS 27Jan99 			{
//DeadCode RJS 27Jan99 				ComposeSample(MessPtr,PHRASE_THISCALLER);
//DeadCode RJS 27Jan99 				ComposeSample(MessPtr,PHRASE_COMMA);
//DeadCode RJS 27Jan99 			}
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 			DecomposeScript(MessPtr,Scriptno);
//DeadCode RJS 27Jan99 		}
//DeadCode RJS 27Jan99 	}
//DeadCode RJS 27Jan99 }
//DeadCode RJS 27Jan99 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecomposeScript
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::DecomposeScript(RadioMessageP	MessPtr,int Scriptno)
{
	UWordP			ScriptPtr;
	PhraseTables	ThePhrase;
	int		count=0;
	ULong	nochoices = Scriptno & 0xFFFF0000;

	if (nochoices)
	{
//DeadCode RJS 12Apr99 		nochoices >>= 16;

		Scriptno &= 0xFFFF;
		ScriptPtr = GetScript(Scriptno,MessPtr,ThePhrase);		//RJS 12Apr99
		if (ScriptPtr)
		{
			ThePhrase = (PhraseTables) *ScriptPtr;
			while (ThePhrase != PHRASE_NULL)
			{
				ComposeSample(MessPtr,ThePhrase);
				ScriptPtr++;

				lastPhrase = ThePhrase;
				ThePhrase = (PhraseTables) *ScriptPtr;
			}
		}
		else
			ComposeSample(MessPtr,ThePhrase);
	}
	else
		ComposeSample(MessPtr,Scriptno);

	if (!MessPtr->BuildMessageAsSamples())
	{
		// Set up a fake one...
		timesincelast = 0;
		timesincestart = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateMessage
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RadioMessageP	RadioChatter::CreateMessage(ItemPtr	caller,
											ItemPtr	target,
											ItemPtr	callee,
											UWord	randno,
											const TargetIndexes&	tstruc,
											VoiceType		vox,
											PhraseBuffer	*fbuffp,
											SWord			vol,
											VoiceState		voxstate)
{
	RadioMessageP	NewMessagePtr = NULL;
	// If there is no queue...
	if (RootMessPtr == NULL)									//RJS 27Jan99
	{
		NewMessagePtr = new RadioMessage(RootMessPtr,caller,target,callee,vol,tstruc,fbuffp,vox);//RJS 27Jan99
		if (NewMessagePtr)
		{
			if (voxstate == VOXSTATE_EXCITED)
				NewMessagePtr->IsExcited = 1;

			NewMessagePtr->masterrandom = randno<<16;
			NewMessagePtr->masterrandom |= randno;

			if (vox == VOICE_FACTAC)
				NewMessagePtr->randomvoice = voicechoiceFAC;
			else
			{
				if (vox == VOICE_TOWER)
					NewMessagePtr->randomvoice = voicechoiceTOWER;
				else
				{
					if ((vox == VOICE_REST) && caller)							//RJS 06Jul99
					{															//RJS 06Jul99
						SLong	callnum = ((AirStrucPtr)caller)->fly.callnum;	//RJS 06Jul99
						if (callnum < MaxPilots)								//RJS 06Jul99
							NewMessagePtr->theFrequency += randomvoice[callnum];//RJS 06Jul99
					}
				}
			}

			MessageCount++;
		}
	}

	lastPhrase = PHRASE_NULL;
	RelativeToPilot = FALSE;
	DigRange = FALSE;

	return(NewMessagePtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ComposeSample
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ComposeSample(RadioMessageP	MessPtr,int phrase)
{
	if (phrase != PHRASE_NULL)									//RJS 12Feb99
	{
		int			ptype = phrase & 0xFF00;
		int			pelement = phrase & 0xFF;

		if (pelement)
		{
			if (MessPtr->isAudio)
			{
				RadioSampleRec*	RSamplePtr;
				int				StartOffset;
				int				SampleSize;

				if (ptype == PHRASE_VOICE2_ONLY)								//RJS 08Jun99
					MessPtr->IsExcited = voicechoiceV2;							//RJS 08Jun99

				RSamplePtr = LoadSample(MessPtr,phrase,StartOffset,SampleSize);
				if (RSamplePtr)
				{
					if ((ptype == PHRASE_PUNCTUATION) || ((lastPhrase & 0xFF00) == PHRASE_PUNCTUATION))
						MessPtr->phraselist[MessPtr->nophrases].noCrossFade = 1;
					else
						MessPtr->phraselist[MessPtr->nophrases].noCrossFade = 0;

					MessPtr->AddSample(RSamplePtr->dataptr,StartOffset,SampleSize);
				}
			}
			else
				MessPtr->AddPhrase(phrase);
		}
		else
		{
			RadioOnz*		phraseControl = &PhraseToFile[ptype>>8];
			PhraseTables	compositePhrase;
			int				pilotno;
			int				squadron;
			int				punctuate = PHRASE_COMMA;
			UniqueID		commsname = (UniqueID) 0;

			switch (ptype)
			{
			case PHRASE_CALLERGROUP:
			{
				AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;
				if (ac)
				{
					squadron = ac->fly.callname;
					if (squadron)
						ComposeSample(MessPtr,PHRASE_CALLGROUPS+squadron);
				}
			}
			break;
			case PHRASE_CALLEEGROUP:
			{
				AirStrucPtr	ac = (AirStrucPtr) MessPtr->callee;
				if (ac)
				{
					squadron = ac->fly.callname;
					if (squadron)
						ComposeSample(MessPtr,PHRASE_CALLGROUPS+squadron);
				}
			}
			break;
			case PHRASE_CALLERSTOP:
				punctuate = PHRASE_STOP;
			case PHRASE_THISCALLER:
			case PHRASE_CALLER:
			{
//DeadCode RDH 12Apr99 				if (MessPtr->isAudio)			//RJS 01Apr99
				{
					AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;//RJS 13Jan99
					if (ac)
					{
						pilotno = ac->fly.callnum;		
						squadron = ac->fly.callname;
						Bool	fixlater = FALSE;

						if (squadron)
						{
							if (ptype == PHRASE_THISCALLER)				//RJS 15Jan99
							{
								punctuate = PHRASE_STOP;
								if (!MessPtr->Random(2))		//RDH 04May99
									ComposeSample(MessPtr,PHRASE_THISIS);	//RJS 15Jan99
								else
									fixlater = TRUE;				//RJS 10Feb99
							}

							ComposeSample(MessPtr,PHRASE_CALLSIGNS_N+squadron);
							if (pilotno && (ac->fly.callname < Call_FAC0))	//RJS 20May99
							{
								if ((pilotno == 1) && (fixlater==FALSE))
								{
									if (MessPtr->Random(1))		//RDH 04May99
										ComposeSample(MessPtr,PHRASE_LEAD);
									else
										ComposeSample(MessPtr,PHRASE_LEAD2);
								}
								else
									ComposeSample(MessPtr,PHRASE_NUMTABLE1_N+pilotno+1);
							}

							if (fixlater)
								ComposeSample(MessPtr,PHRASE_HERE);	//RJS 10Feb99

							ComposeSample(MessPtr,punctuate);			//RJS 08Mar99
						}
					}
				}
			}
			break;
			case PHRASE_SUBJECT:
			case PHRASE_CALLEE:
			{
				AirStrucPtr	ac;												//RJS 04May99
				if (ptype == PHRASE_SUBJECT)								//RJS 04May99
					ac = (AirStrucPtr) MessPtr->target;						//RJS 04May99
				else														//RJS 04May99
					ac = (AirStrucPtr) MessPtr->callee;						//RJS 04May99
				if (ac)
				{
					pilotno = ac->fly.callnum;			
					squadron = ac->fly.callname;

					if (squadron)
					{
//DeadCode RDH 04May99 						UWord	randy = Math_Lib.rnd();
						ComposeSample(MessPtr,PHRASE_CALLSIGNS_N+squadron);
						if (pilotno && (ac->fly.callname < Call_FAC0))		//RJS 20May99
						{
							if (pilotno == 1)
							{
 								if (!MessPtr->Random(2))		//RDH 04May99
 									ComposeSample(MessPtr,PHRASE_LEAD);
 								else
									ComposeSample(MessPtr,PHRASE_LEAD2);
							}
							else
								ComposeSample(MessPtr,PHRASE_NUMTABLE1_N+pilotno+1);
						}
					}
				}
			}
			break;
			case PHRASE_SMLRANGESKM:
			case PHRASE_SMLRANGESIMP:
			{
				SLong	dist = MessPtr->distance;

				dist += phraseControl->subFactor;
				dist /= phraseControl->divFactor;

				ComposeSample(MessPtr,PHRASE_SMALLRANGES+dist);
			}
			break;
			case PHRASE_BIGRANGESKM:
			case PHRASE_BIGRANGESIMP:
			{
				SLong	dist = MessPtr->distance;

				dist += phraseControl->subFactor;				//RJS 12Feb99
				dist /= phraseControl->divFactor;				//RJS 12Feb99

				dist += PHRASE_NUMTABLE25_N;
				if (dist > PHRASE_NUMBER800)
					dist = PHRASE_NUMBER800;

				ComposeSample(MessPtr,dist);
			}
			break;
			case PHRASE_RANGESKM:
			case PHRASE_RANGESIMP:
			{
				SLong	dist = MessPtr->distance;
			
				dist += phraseControl->subFactor;			//RJS 12Feb99
				dist /= phraseControl->divFactor;			//RJS 12Feb99

				if (dist > 100)
				{
					// Are we a pilot?
					if (MessPtr->theVoice < VOICE_FACTAC)
					{
						// only the leader can say big ranges...
						if (MessPtr->caller != ((AirStrucPtr)MessPtr->caller)->GroupLeader())
						{
							ComposeSample(MessPtr,PHRASE_OVER100);
							break;
						}
					}

					if (ptype == PHRASE_RANGESKM)
						ComposeSample(MessPtr,PHRASE_BIGRANGESKM);
					else
						ComposeSample(MessPtr,PHRASE_BIGRANGESIMP);
				}
				else
				{
					SLong	 newphrase = dist + PHRASE_NUMTABLEF;
					if (newphrase < PHRASE_FNUMBER2)
						newphrase = PHRASE_FNUMBER2;

					if (newphrase > PHRASE_FNUMBER16)
					{
						newphrase -= PHRASE_NUMTABLEF;
						newphrase += PHRASE_NUMTABLE1_N;
					}

					ComposeSample(MessPtr,newphrase);
				}
			}
			break;
			case PHRASE_NUMBERCLOCK:
			case PHRASE_BEARINGS:
			{
				if (MessPtr->InitROL())
				{
					UWord	relbearing = UWord(MessPtr->bearing);

					relbearing -= UWord(MessPtr->callee->hdg);	//RJS 05May99
					relbearing += phraseControl->subFactor;		//RJS 12Feb99
					relbearing /= phraseControl->divFactor;		//RJS 12Feb99

					if (ptype == PHRASE_BEARINGS)
					{
						if (!relbearing)
							relbearing = 1;
							
						ComposeSample(MessPtr,ptype+relbearing);
						ComposeSample(MessPtr,PHRASE_THEOCLOCK);
					}
					else
					{
						relbearing += PHRASE_NUMTABLE1_N;
						if (relbearing < PHRASE_NUMBER1)
							relbearing = PHRASE_NUMBER12;
						
						ComposeSample(MessPtr,PHRASE_YOUR);
						ComposeSample(MessPtr,relbearing);
					}
				}
			}
			break;
			case PHRASE_TARGDIR:
			if (MessPtr->InitROL())
			{
				UWord	relbearing = MessPtr->bearing;

				relbearing += phraseControl->subFactor;		//RJS 12Feb99
				relbearing /= phraseControl->divFactor;		//RJS 12Feb99
				if (!relbearing)
					relbearing = 1;
					
				ComposeSample(MessPtr,ptype+relbearing);
			}
			break;
			case PHRASE_RELHEIGHTS:
			{
//DeadCode AMM 05Jul99 				// Must cater for relative heights from
//DeadCode AMM 05Jul99 				// different perspectives!!
//DeadCode AMM 05Jul99 				//
//DeadCode AMM 05Jul99 				// ie. caller and target, or callee and target
//DeadCode AMM 05Jul99 
//DeadCode AMM 05Jul99 				SLong	rheights = MessPtr->pitch;
//DeadCode AMM 05Jul99 				if (rheights > 5000)
//DeadCode AMM 05Jul99 					ComposeSample(MessPtr,PHRASE_HIGH);
//DeadCode AMM 05Jul99 				else
//DeadCode AMM 05Jul99 				{
//DeadCode AMM 05Jul99 					if (rheights < -5000)
//DeadCode AMM 05Jul99 						ComposeSample(MessPtr,PHRASE_LOW);
//DeadCode AMM 05Jul99 					else
//DeadCode AMM 05Jul99 						ComposeSample(MessPtr,PHRASE_OURLEVEL);//RJS 10Feb99
//DeadCode AMM 05Jul99 				}
				if (MessPtr->target && MessPtr->callee)			//RJS 05Jul99
				{
					SLong	rheights = MessPtr->target->World.Y - MessPtr->callee->World.Y;
					//100m
					if (rheights > 10000)
						ComposeSample(MessPtr,PHRASE_HIGH);
					else
					{
						if (rheights < -10000)
							ComposeSample(MessPtr,PHRASE_LOW);
						else
							ComposeSample(MessPtr,PHRASE_OURLEVEL);//RJS 10Feb99
					}
				}
			}
			break;
			case PHRASE_HEIGHTSANGELS:
			{
				if (MessPtr->target)
				{
					MessPtr->realheight = MessPtr->target->World.Y;

					DigRange = TRUE;
					if (Save_Data.gamedifficulty [GD_UNITS])
						ComposeSample(MessPtr,PHRASE_HEIGHTSM);
					else
						ComposeSample(MessPtr,PHRASE_HEIGHTSFT);
					DigRange = FALSE;

					ComposeSample(MessPtr,PHRASE_ANGELS);
				}
			}
			break;
			case PHRASE_PLACENAMESNP:
				lastPhrase = PHRASE_LOST;
			case PHRASE_PLACENAMES:
			{
				SectorNameP	NamePtr;

//DeadCode RJS 23May99 				if (lastPhrase == PHRASE_LOST)
//DeadCode RJS 23May99 				{
//DeadCode RJS 23May99 					RelativeToPilot = TRUE;
//DeadCode RJS 23May99 					NamePtr = GetPlaceName(MessPtr->caller);
//DeadCode RJS 23May99 				}
//DeadCode RJS 23May99 				else
				if (MessPtr->target)
					NamePtr = GetPlaceName(MessPtr->target);
				else
					NamePtr = GetPlaceName(MessPtr->TargetStuff.targetname);

				if (NamePtr)
				{
					if (lastPhrase == PHRASE_NULL)					//RJS 11Feb99
						ComposeSample(MessPtr,NamePtr->prefix);
					else
					{
						if (lastPhrase != PHRASE_LOST)		//RJS 11Feb99
						{
							if (	((NamePtr->prefix >= PHRASE_CENTRAL) && (NamePtr->prefix < PHRASE_OVER))
								||	(NamePtr->prefix == PHRASE_NULL)	)
								ComposeSample(MessPtr,PHRASE_OVER);

							ComposeSample(MessPtr,NamePtr->prefix);
						}
					}

					ComposeSample(MessPtr,NamePtr->name);
					ComposeSample(MessPtr,NamePtr->postfix);	//RJS 15Jun99
				}
			}
			break;
			case PHRASE_ANAMED_AC:
			case PHRASE_NAMED_AC:
			{
				if (MessPtr->target && (MessPtr->target->Status.size==AIRSTRUCSIZE))
				{
					ClassPtr	clstyp = ((AirStrucPtr)MessPtr->target)->classtype;
					SLong		pno = 0;						//RJS 01Jul99

					if (clstyp->phrasename == PHRASE_MIGS)
						pno = PHRASE_QMIG - PHRASE_NAMED_AC;
					else
					{
						if (clstyp->phrasename == PHRASE_F86S)	//RJS 01Jul99
							pno = PHRASE_QSABRE - PHRASE_NAMED_AC;
					}

					if (pno)									//RJS 01Jul99
						ComposeSample(MessPtr,ptype+pno);		//RJS 01Jul99
				}
			}
			break;
			case PHRASE_NAMED_ACS:
			{
				if (MessPtr->target && (MessPtr->target->Status.size==AIRSTRUCSIZE))
				{
					ClassPtr	clstyp = ((AirStrucPtr)MessPtr->target)->classtype;

					ComposeSample(MessPtr,clstyp->phrasename);
				}
			}
			break;
			case PHRASE_DIRECTIONS_TRAVEL:
			{
				if (MessPtr->TargetStuff.targetdirection)	//RJS 12Jan99
				{
					ComposeSample(MessPtr,PHRASE_HEADING);
					ComposeSample(MessPtr,ptype+MessPtr->TargetStuff.targetdirection);
				}
				else
				{
					ULong	direction;
					Bool	dirset = FALSE;

					if (RelativeToPilot == TRUE)
					{
						if (MessPtr->caller)
						{
							direction = MessPtr->caller->hdg;
							dirset = TRUE;
						}
					}
					else
					{
						if (MessPtr->target)
						{
							direction = MessPtr->target->hdg;
							dirset = TRUE;
						}
					}

					if (dirset)
					{
						direction += phraseControl->subFactor;	//RJS 12Feb99
						direction /= phraseControl->divFactor;	//RJS 12Feb99

//						if (direction == 0)
//							direction = 1;

						ComposeSample(MessPtr,PHRASE_HEADING);
						ComposeSample(MessPtr,ptype+direction);
					}
				}
			}
			break;
//DeadCode RJS 17Mar99 			case PHRASE_BANDIT_ALERT:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				ULong	randy = Math_Lib.rnd();
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				randy += phraseControl->subFactor;				//RJS 12Feb99
//DeadCode RJS 17Mar99 				randy /= phraseControl->divFactor;				//RJS 12Feb99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ComposeSample(MessPtr,ptype+randy);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
			case PHRASE_TARGTYPE:
			{
				compositePhrase = (PhraseTables)MessPtr->TargetStuff.targettype;
				if ((compositePhrase & 0xFF00)==ptype)
					ComposeSample(MessPtr,compositePhrase);			//RJS 28Apr99
			}
			break;
			case PHRASE_TARGNAM:
			{
				compositePhrase = (PhraseTables)MessPtr->TargetStuff.targetname;
				if ((compositePhrase & 0xFF00)==ptype)
					ComposeSample(MessPtr,compositePhrase);			//RJS 28Apr99
			}
			break;
			case PHRASE_TARGMOV:
			{
				compositePhrase = (PhraseTables)MessPtr->TargetStuff.targetmovement;
				if ((compositePhrase & 0xFF00)==ptype)
					ComposeSample(MessPtr,compositePhrase);		//RJS 28Apr99
			}
			break;
			case PHRASE_WEAPONS:
			{
				compositePhrase = (PhraseTables)MessPtr->TargetStuff.weaponset;
				if ((compositePhrase & 0xFF00)==ptype)
					ComposeSample(MessPtr,compositePhrase);			//RJS 28Apr99
			}
			break;
			case PHRASE_HEIGHTSM:
			case PHRASE_HEIGHTSFT:
			{
				SLong	height = MessPtr->realheight;

				height += phraseControl->subFactor;
				height /= phraseControl->divFactor;

				if (DigRange)
					ComposeDigitNumber(MessPtr,height,2);
				else
				{
					height += PHRASE_NUMTABLEF;
					if (height < PHRASE_FNUMBER1)
						height = PHRASE_FNUMBER1;

					if (height > PHRASE_FNUMBER16)				//RJS 12Apr99
					{
						height -= PHRASE_NUMTABLEF;
						height += PHRASE_NUMTABLE1_N;
					}
					ComposeSample(MessPtr,height);
				}
			}
			break;
			case PHRASE_HEIGHTS:
			{
				if (MessPtr->target || MessPtr->TargetStuff.targetheight)//RJS 01Jun99
				{
					bool	saidheight = false;
//DeadCode RDH 04May99 					UWord	randy = Math_Lib.rnd();
					if (MessPtr->Random(3))						//RDH 04May99
					{
						ComposeSample(MessPtr,PHRASE_HEIGHT);
						saidheight = true;
					}
					else
					{
						if ((MessPtr->IsExcited == 0) && MessPtr->Random(3))//RDH 04May99
						{
							ComposeSample(MessPtr,PHRASE_ESTHEIGHT);
							saidheight = true;
						}
					}

					if (!saidheight)
						ComposeSample(MessPtr,PHRASE_SPACE);

					if (MessPtr->TargetStuff.targetheight)		//RJS 01Jun99
						MessPtr->realheight = MessPtr->TargetStuff.targetheight;
					else
						MessPtr->realheight = MessPtr->target->World.Y;

					if (Save_Data.gamedifficulty [GD_UNITS])
					{
						ComposeSample(MessPtr,PHRASE_HEIGHTSM);
						ComposeSample(MessPtr,PHRASE_THOUSANDM);
					}
					else
					{
						ComposeSample(MessPtr,PHRASE_HEIGHTSFT);
						ComposeSample(MessPtr,PHRASE_THOUSANDFT);
					}
				}
			}
			break;
			case PHRASE_SPEEDS:
			{
				if (MessPtr->InitROL())
				{
					ULong	vel;
					SLong	newphrase;
					
//DeadCode RJS 18Mar99 					if (Save_Data.gamedifficulty [GD_UNITS])
//DeadCode RJS 18Mar99 					{
//DeadCode RJS 18Mar99 						// metric (m/cm)... but have as knots
//DeadCode RJS 18Mar99 						vel = Float(MessPtr->speed) * 0.19438;
//DeadCode RJS 18Mar99 						newphrase = PHRASE_SPEEDSKNOT;
//DeadCode RJS 18Mar99 					}
//DeadCode RJS 18Mar99 					else
//DeadCode RJS 18Mar99 					{
//DeadCode RJS 18Mar99 						// mph
//DeadCode RJS 18Mar99 						vel = Float(MessPtr->speed) * 0.225;
//DeadCode RJS 18Mar99 						newphrase = PHRASE_SPEEDSMPH;
//DeadCode RJS 18Mar99 					}
//DeadCode RJS 18Mar99 
//DeadCode RJS 18Mar99 					MessPtr->speed = vel;
//DeadCode RJS 18Mar99 					ComposeSample(MessPtr,newphrase);

					vel = MessPtr->speed;
					vel += phraseControl->subFactor;
					vel /= phraseControl->divFactor;
					if (!vel)	vel = 1;

					ComposeSample(MessPtr,PHRASE_SPACE);				//RJS 09May99
					ComposeSample(MessPtr,PHRASE_NUMTABLE25_N+vel); 

					if (Save_Data.gamedifficulty [GD_UNITS])
						ComposeSample(MessPtr,PHRASE_CLICKS);
					else
						ComposeSample(MessPtr,PHRASE_KNOTS);
				}
			}
			break;
			case PHRASE_RANGES:
			{
				if (MessPtr->InitROL())
				{
					bool	saidrange = false;
					if ((MessPtr->distance > 300000) || (MessPtr->IsExcited==0))
					{
//DeadCode RDH 04May99 						UWord	randpoo = Math_Lib.rnd();
						if (MessPtr->Random(1))					//RDH 04May99
						{
// At Range can only be said, if no comma precedes it...
//DeadCode RJS 17Mar99 							if (randpoo > 55000)
//DeadCode RJS 17Mar99 								ComposeSample(MessPtr,PHRASE_ATRANGE);
//DeadCode RJS 17Mar99 							else
							ComposeSample(MessPtr,PHRASE_RANGE);
							saidrange = true;
						}
					}

					if (!saidrange)
						ComposeSample(MessPtr,PHRASE_SPACE);

					if (MessPtr->distance > 250000)
					{
						if (Save_Data.gamedifficulty [GD_UNITS])
						{
							ComposeSample(MessPtr,PHRASE_RANGESKM);
							ComposeSample(MessPtr,PHRASE_KILOMETRES);
						}
						else
						{
							ComposeSample(MessPtr,PHRASE_RANGESIMP);
							ComposeSample(MessPtr,PHRASE_MILES);
						}
					}
					else
					{
						// Small ranges...
						if (Save_Data.gamedifficulty [GD_UNITS])
						{
							if (	(MessPtr->theVoice != VOICE_DENTIST)
								&&	(MessPtr->theVoice != VOICE_TOWER)	)
							{
								ComposeSample(MessPtr,PHRASE_SMLRANGESKM);
								ComposeSample(MessPtr,PHRASE_METRES);
							}
							else
							{
								ComposeSample(MessPtr,PHRASE_UNDER2);
								ComposeSample(MessPtr,PHRASE_KILOMETRES);
							}
						}
						else
						{
							if (	(MessPtr->theVoice != VOICE_DENTIST)
								&&	(MessPtr->theVoice != VOICE_TOWER)	)
							{
								ComposeSample(MessPtr,PHRASE_SMLRANGESIMP);
								ComposeSample(MessPtr,PHRASE_YARDS);
							}
							else
							{
								ComposeSample(MessPtr,PHRASE_UNDER2);
								ComposeSample(MessPtr,PHRASE_MILES);
							}
						}
					}
				}
			}
			break;
			case PHRASE_BEARINGNO:								//RJS 18Mar99
			{
				if (MessPtr->InitROL())
				{
					UWord	relbearing = UWord(MessPtr->bearing);//RDH 13Apr99
					SLong	therel = (relbearing * 360)>>16;	//RDH 13Apr99

					ComposeDigitNumber(MessPtr,therel,3);		//RDH 30Apr99
				}
			}
			break;
			case PHRASE_ALTWINDBEARINGNO:
			{
				windHeightSet = 1061666;	//35,000ft in cm
				ComposeSample(MessPtr,PHRASE_ALTWIND);
				ComposeSample(MessPtr,PHRASE_COMMA);
				ComposeSample(MessPtr,PHRASE_WINDBEARINGNO);
			}
			break;
			case PHRASE_SURFACEWINDBEARINGNO:
			{
				windHeightSet = 0;
				ComposeSample(MessPtr,PHRASE_SURFACEWIND);
				ComposeSample(MessPtr,PHRASE_COMMA);
				ComposeSample(MessPtr,PHRASE_WINDBEARINGNO);
			}
			break;
			case PHRASE_WINDBEARINGNO:
			{
				SLong	vx,vy,vz;

				// height is set up by prevous wind phrase...
//DeadCode DAW 04May99 				if (MMC.Sky.GetWind(windHeightSet,vx,vy,vz))
//DeadCode DAW 04May99 				{
//DeadCode DAW 04May99 					ANGLES	bearing,pitch;
//DeadCode DAW 04May99 					
//DeadCode DAW 04May99 					Math_Lib.Intercept(vx,vy,vz,windSpeedSet,bearing,pitch);

					ULong	theBearing;
					
					//These values should already be in degrees...
					if (windHeightSet)
						theBearing = UWord(MMC.Sky.diralt);
					else
						theBearing = UWord(MMC.Sky.dir0);

//DeadCode DAW 04May99 					theBearing *= 360;
//DeadCode DAW 04May99 					theBearing >>= 16;

					ComposeSample(MessPtr,PHRASE_THEBEARING);
					ComposeDigitNumber(MessPtr,SLong(theBearing),3);
//DEADCODE DAW 04/05/99 				}
			}
			break;
			case PHRASE_WINDSPEED:
			{
				if (windSpeedSet == -1)
				{
//DeadCode DAW 04May99 					SLong	vx,vy,vz;
//DeadCode DAW 04May99 					if (MMC.Sky.GetWind(windHeightSet,vx,vy,vz))
//DeadCode DAW 04May99 						windSpeedSet = Math_Lib.distance3d(vx,vy,vz);
					//Knots...
					if (windHeightSet)
						windSpeedSet = UWord(MMC.Sky.windalt);
					else
						windSpeedSet = UWord(MMC.Sky.wind0);
				}

				if (windSpeedSet > -1)
				{
//DeadCode DAW 04May99 					Float	fspeed;
//DeadCode DAW 04May99 
//DeadCode DAW 04May99 					//Scale & divide by 10!
//DeadCode DAW 04May99 					fspeed = Float(windSpeedSet);
//DeadCode DAW 04May99 					if (Save_Data.gamedifficulty [GD_UNITS])
//DeadCode DAW 04May99 						fspeed *= 0.194261;						//RJS 30Apr99
//DeadCode DAW 04May99 					else
//DeadCode DAW 04May99 						fspeed *= 0.22369;						//RJS 30Apr99
//DeadCode DAW 04May99 			 
//DeadCode DAW 04May99 					windSpeedSet = SLong(fspeed);
					windSpeedSet += PHRASE_FNUMBER0;

					if (windSpeedSet < PHRASE_FNUMBER2)
						windSpeedSet = PHRASE_FNUMBER2;

					if (windSpeedSet > PHRASE_FNUMBER16)
					{
						windSpeedSet -= PHRASE_NUMTABLEF;
						windSpeedSet += PHRASE_NUMTABLE1_N;

						if (windSpeedSet > PHRASE_NUMBER100)
							windSpeedSet = PHRASE_NUMBER100;
					}

					ComposeSample(MessPtr,PHRASE_SPACE);
					ComposeSample(MessPtr,windSpeedSet);
//DEADCODE DAW 05/05/99 					if (Save_Data.gamedifficulty [GD_UNITS])
						ComposeSample(MessPtr,PHRASE_KNOTS);
//DEADCODE DAW 05/05/99 					else
//DEADCODE DAW 05/05/99 						ComposeSample(MessPtr,PHRASE_PERHOUR);
				}

				windSpeedSet = -1;
			}
			break;
			case PHRASE_FUELLEVEL:
			{
				if (MessPtr->caller)
				{
					AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;
					ULong	fueltot = ac->weap.left.int_fuel;

					fueltot += ac->weap.left.ext_fuel;
					fueltot += ac->weap.right.int_fuel;
					fueltot += ac->weap.right.ext_fuel;
					fueltot += ac->weap.centre.int_fuel;
					fueltot += ac->weap.centre.ext_fuel;

					fueltot /= 100000;	//kgs
//DeadCode CSB 30/06/99						fueltot = Float(fueltot) * 0.453597;		//RJS 13May99
					fueltot = Float(fueltot) * 2.2046;		//CSB 30/06/99	

					ComposeSample(MessPtr,PHRASE_SPACE);		//RJS 13May99
					ComposeDigitNumber(MessPtr,SLong(fueltot));
					ComposeSample(MessPtr,PHRASE_GALLONS);
				}
			}
			break;
			case PHRASE_RELPOSITION:							//RJS 25Feb99
			{
				// split into 4 directions, with 45 degree spread -&+...
				if (MessPtr->InitROL())
				{
					UWord	relbearing = MessPtr->bearing;
					relbearing += phraseControl->subFactor;		//RJS 12Feb99
					relbearing /= phraseControl->divFactor;		//RJS 12Feb99
					if (!relbearing)
						relbearing++;

					ComposeSample(MessPtr,ptype+relbearing);
				}
			}
			break;
			case PHRASE_RANDOMTHINKTIME:
			{
				if (MessPtr->isAudio)
				{
					RadioSampleRec*	RSamplePtr;
					int				StartOffset;
					int				SampleSize;

					RSamplePtr = LoadSample(MessPtr,PHRASE_THINKING,StartOffset,SampleSize);
					if (RSamplePtr)
					{
						// Fiddle the sample size to vary pause length...
						SampleSize >>= 1;
						SampleSize += Math_Lib.rnd(SampleSize);
			
						MessPtr->AddSample(RSamplePtr->dataptr,StartOffset,SampleSize);
					}
				}
				else
					MessPtr->AddPhrase(PHRASE_THINKING);
//				{
//					//1.5 secs...
//					for (int i=0; i < 3; i++)
//						MessPtr->AddPhrase(PHRASE_THINKING);
//				}
			}
			break;
			case PHRASE_GUSTTYPE:
			{
				SLong magnitude = MMC.Sky.MaxMagnitude;

				//assume magnitude is 0...6
				magnitude = (2 * magnitude)/6;		//scale down to 3 possible types...
				
				ComposeSample(MessPtr,PHRASE_GUSTLIGHT+magnitude);
			}
			break;
			case PHRASE_THISDENTIST:
			{
//DeadCode RDH 12Apr99 				if (MessPtr->isAudio)
				{
					if (!MessPtr->Random(2))					//RDH 04May99
					{
						ComposeSample(MessPtr,PHRASE_THISIS);
						ComposeSample(MessPtr,PHRASE_DENTIST);
					}
					else
						ComposeSample(MessPtr,PHRASE_DENTISTHERE);
				}
			}
			break;
			case PHRASE_THISDENTISTTO:
			{
//DeadCode RDH 12Apr99 				if (MessPtr->isAudio)
					ComposeSample(MessPtr,PHRASE_DENTISTTO);
			}
			break;
			case PHRASE_DENTISTSTOP:
			{
//DeadCode RDH 12Apr99 				if (MessPtr->isAudio)
				{
					ComposeSample(MessPtr,PHRASE_DENTIST);
					ComposeSample(MessPtr,PHRASE_STOP);
				}
			}
			break;
			case PHRASE_AIRFIELDS:
			{
				if (MessPtr->target)									//RJS 05May99
				{	
					SLong	uid = MessPtr->target->uniqueID.count;		//RJS 05May99

					// Find offset...
					uid -= UID_AfRdPyongyangM;
					uid++;

					uid += PHRASE_AIRFIELDS;
					if ((uid > PHRASE_AIRFIELDS) && (uid <= PHRASE_AFJAPAN))
					{
						ComposeSample(MessPtr,uid);
//Dead(moved to script)						ComposeSample(MessPtr,PHRASE_AIRFIELD);
					}
				}
			}
			break;
			case PHRASE_THISCOMMS:
			case PHRASE_COMMSCALLER:
				commsname = MessPtr->caller->uniqueID.count;
			case PHRASE_COMMSTARGET:
			{
				if (!commsname)
					commsname = MessPtr->target->uniqueID.count;

				ComposeSample(MessPtr,PHRASE_PLAYERNAME1+_DPlay.GetPlayerNumber(commsname));

				if (ptype == PHRASE_THISCOMMS)
				{
					ComposeSample(MessPtr,PHRASE_COLON);
					ComposeSample(MessPtr,PHRASE_SPACE);
				}
			}
			break;
			case PHRASE_USER_DEFINED:
			{
				ULong	messno = 8 * _DPlay.GetPlayerNumber(MessPtr->caller->uniqueID.count);

				messno += MessPtr->TargetStuff.usermessage;
				messno++;

				ComposeSample(MessPtr,ptype+messno);
			}
			break;
			case PHRASE_GERMANCALLERSTOP:
				punctuate = PHRASE_STOP;
			case PHRASE_GERMANTHISCALLER:
			case PHRASE_GERMANCALLER:
			{
				if (MessPtr->isAudio)
				{
					switch (ptype)
					{
					case PHRASE_GERMANCALLERSTOP:
						ComposeSample(MessPtr,PHRASE_CALLERSTOP);
						break;
					case PHRASE_GERMANTHISCALLER:
						ComposeSample(MessPtr,PHRASE_THISCALLER);
						break;
					case PHRASE_GERMANCALLER:
						ComposeSample(MessPtr,PHRASE_CALLER);
						break;
					}
				}
				else
				{
					AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;
					if (ac)
					{
						pilotno = ac->fly.callnum;		
						squadron = ac->fly.callname;
						Bool	fixlater = FALSE;

						if (squadron)
						{
							if (ptype == PHRASE_GERMANTHISCALLER)
							{
								punctuate = PHRASE_STOP;
								if (!MessPtr->Random(2))
									ComposeSample(MessPtr,PHRASE_THISIS);
								else
								{	
									ComposeSample(MessPtr,PHRASE_HERE);
									ComposeSample(MessPtr,PHRASE_SPACE);
									fixlater = TRUE;
								}
							}

							ComposeSample(MessPtr,PHRASE_CALLSIGNS_N+squadron);
							if (pilotno && (ac->fly.callname < Call_FAC0))
							{
//DeadCode RJS 15Jun99 								if ((pilotno == 1) && (fixlater==FALSE))
//DeadCode RJS 15Jun99 								{
//DeadCode RJS 15Jun99 									if (MessPtr->Random(1))
//DeadCode RJS 15Jun99 										ComposeSample(MessPtr,PHRASE_LEAD);
//DeadCode RJS 15Jun99 									else
//DeadCode RJS 15Jun99 										ComposeSample(MessPtr,PHRASE_LEAD2);
//DeadCode RJS 15Jun99 								}
//DeadCode RJS 15Jun99 								else
									ComposeSample(MessPtr,PHRASE_NUMTABLE1_N+pilotno+1);
							}

							ComposeSample(MessPtr,punctuate);
						}
					}
				}
			}
			break;
			case PHRASE_GERMANNUMBERCLOCK:
			{
				if (MessPtr->isAudio)
					ComposeSample(MessPtr,PHRASE_NUMBERCLOCK);
				else
				{
					if (MessPtr->InitROL())
					{
						UWord	relbearing = MessPtr->bearing;

						relbearing -= UWord(MessPtr->callee->hdg);
						relbearing += phraseControl->subFactor;
						relbearing /= phraseControl->divFactor;
						relbearing += PHRASE_NUMTABLE1_N;
						if (relbearing < PHRASE_NUMBER1)
							relbearing = PHRASE_NUMBER12;
		
						ComposeSample(MessPtr,PHRASE_SPACE);
						ComposeSample(MessPtr,relbearing);
						ComposeSample(MessPtr,PHRASE_YOUR);
					}
				}
			}
			break;
			case PHRASE_COMMSACCEL:
			{
				int	accelno = _DPlay.GetAccelNumber();

				ComposeSample(MessPtr,PHRASE_NUMBER0+accelno);
			}
			break;
			case PHRASE_ITALIANBEARINGS:
			{
				if (MessPtr->isAudio)
					ComposeSample(MessPtr,PHRASE_BEARINGS);
				else
				{
					if (MessPtr->InitROL())
					{
						UWord	relbearing = MessPtr->bearing;

						relbearing -= UWord(MessPtr->callee->hdg);
						relbearing += phraseControl->subFactor;	  
						relbearing /= phraseControl->divFactor;	  
						if (!relbearing)
							relbearing = 1;
						
						ComposeSample(MessPtr,PHRASE_THEOCLOCK);
						ComposeSample(MessPtr,ptype+relbearing);
					}
				}
			}
			break;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddSample
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
void	RADIOMESSAGE::AddSample(UByteP	data,int	theOffset, int theSize)	//RJS 22Mar99
{
	if (theSize)
	{
		phraselist[nophrases].size = theSize/4;			// long words
		phraselist[nophrases++].address = data + theOffset;
		samplesize += theSize;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPhrase
//Author		Robert Slater
//Date			Thu 13 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::AddPhrase(int phrase)
{
	SLong	visphrase = phrase;

//TempCode RJS 13May99 	if (TextNum)
//TempCode RJS 13May99 	{
//TempCode RJS 13May99 		visphrase -= PHRASE_NUMTABLE1_N;
//TempCode RJS 13May99 		visphrase += PHRASE_TNUMTABLE1;
//TempCode RJS 13May99 	}

	if (messbuffptr)
	{
		if (messbuffptr->phrase_count < MaxPhrases)
			messbuffptr->phrase_buffer[messbuffptr->phrase_count++] = visphrase;
	}
	else
		nophrases++;
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildMessageAsSamples
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//								     
//Returns	
//
//------------------------------------------------------------------------------
Bool	RADIOMESSAGE::BuildMessageAsSamples()
{
	if (samplesize)
	{
		ULong	longsamplesize = (samplesize+16)>>2;			//RJS 04Jun99
		ULong	newsamplesize = longsamplesize << 2;			//RJS 04Jun99
																//RJS 04Jun99
		sampleptr = new UByte[newsamplesize];					//RJS 04Jun99
		if (sampleptr)
		{
			ULong	*destptr = (ULong*)sampleptr;
			ULong	*srcptr;
			int		count;
			int		sampcnt;
			int		noCrossFade = TRUE;
			ULong	*destptr2 = destptr;
			SByte	sample1,sample2;
			SLong	mixed;
			int		count2;
			SLong	depth = 448;
			SByteP	tmpdestptr;
			SByteP	tmpsrcptr;
			ULong	total;

			ULongP	tmpptr = destptr;							//RJS 04Jun99
			for (count=0; count < longsamplesize; count++)		//RJS 04Jun99
			{													//RJS 04Jun99
				*tmpptr = 0x80808080;							//DAW 31Aug99
				tmpptr++;										//RJS 04Jun99
			}													//RJS 04Jun99

			for (count = 0; count < nophrases; count++)
			{
				srcptr = (ULong*) phraselist[count].address;
				if (noCrossFade)
				{
					for (sampcnt = 0; sampcnt < phraselist[count].size; sampcnt++)
					{
						*destptr = *srcptr;
						destptr++;
						srcptr++;
					}
				}
				else
				{
					for (sampcnt = 0; sampcnt < phraselist[count].size; sampcnt++)
					{
						if (destptr < destptr2)
						{
							tmpdestptr = (SByteP) destptr;
							tmpsrcptr = (SByteP) srcptr;
							for (count2 = 0; count2 < 4; count2++)
							{
								sample1 = *tmpdestptr;
								sample1 -= 128;
								sample2 = *tmpsrcptr;
								sample2 -= 128;

								mixed = (sample1 * depth)/448;
								mixed += (sample2 * (448-depth))/448;

								if (mixed < -128)	mixed = -128;
								else
									if (mixed > 127)	mixed = 127;

								*tmpdestptr = SByte(mixed + 128);

								tmpdestptr++;
								tmpsrcptr++;

								depth--;
							}

							destptr++;
							srcptr++;
						}
						else
						{
							*destptr = *srcptr;
							destptr++;
							srcptr++;
						}
					}
				}

				// Cross-fade (if this or last phrase was not punctuation)
				noCrossFade = phraselist[count].noCrossFade;
				if (!noCrossFade)
				{
					destptr2 = destptr;
					depth = 448;
					destptr -= 112;
				}
			}

			*destptr = 0x80808080;								//DAW 31Aug99
		}
#ifndef	NANIMDEBUG
	DbgMemTest2(sampleptr);
#endif

		return TRUE;
	}

	isAudio = FALSE;			//an empty message...
	fakeplaytime = 250;	//4 secs to read...						//DAW 07Apr99

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitROL
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	RADIOMESSAGE::InitROL()
{
	Bool	retval = FALSE;
	if (target)
	{
		retval = TRUE;
		if (distance == -1)
		{
			SLong	dx, dy, dz;

			if (callee)
			{
				dx = target->World.X - callee->World.X;
				dy = target->World.Y - callee->World.Y;
				dz = target->World.Z - callee->World.Z;

				Math_Lib.Intercept(dx,dy,dz,distance,bearing,pitch);
			}
			else
			{
				retval = FALSE;					//RJS 09May99
				distance = 0;
			}
		}

		speed = target->vel * 10000;							//RJS 18Mar99
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSample
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//				Format:
//							n files		(ULong)
//							offset (ULong),	size (ULong)	* n
//							Samples Header
//							Samples data
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RadioSampleRec*	RadioChatter::LoadSample(	RadioMessageP	MessPtr,
											int				thephrase,
											int 			&StartOff,
											int 			&SampleSize)
{
	RadioSampleRec*	SamplePtr = NULL;
	int				pelement = thephrase & 0xFF;				//RJS 12Feb99
	SLong			fileindex = PhraseToFile[thephrase>>8].mainFileName & FILENUMMASK;//RJS 12Feb99
	SLong			voiceoffset = MessPtr->theVoice + MessPtr->IsExcited + MessPtr->randomvoice;//RJS 17May99
	SLong			thedir = rootChatDir + (voiceoffset<<8);				//RJS 08Apr99
	FileNum			thefile = (FileNum) (thedir + fileindex);
																//RJS 17Mar99
	StartOff = SampleSize = 0;									//RJS 17Mar99
	SamplePtr = &radiosamples[fileindex-1][voiceoffset];		//RJS 17Mar99
	if (!SamplePtr->blockptr)
	{
		fileblock	*theblock;
		SWAV		*header1;
		void		*tmpaddress;
		ULong		*longaddress;
		SLong		size;
		char		*tmpptr;
		int			count;
		char		id[5];
		int			noSamples;
		ULong		*offlist;
		ULong		ssize = sizeof(SWAV) / 4;

		theblock = new fileblock (thefile);
		if (theblock)
		{
			tmpaddress = getdata(theblock);
			size = getsize(theblock);

			longaddress = (ULong*)tmpaddress;

			noSamples = *longaddress;
			if (pelement <= noSamples)							//RJS 07Apr99
			{
				longaddress++;

				offlist = longaddress;

				SamplePtr->blockptr = theblock;
				SamplePtr->size = size;
				SamplePtr->noFiles = noSamples;
				SamplePtr->offsetptr = (SOffsetList*) offlist;

				longaddress += (noSamples*2); // offlist is 2 longs * nosamples

				tmpptr = (char*) longaddress;

				for (count = 0; count < 4; count ++)
					id[count] = *tmpptr++;

				id[4] = 0;

				if (stricmp(id,"SWAV") == 0)
				{
					header1 = (SWAV*) longaddress;

					longaddress += ssize;

					SamplePtr->headerptr = header1;
					SamplePtr->dataptr = (UByteP) longaddress; 
				}
				else
				{
					SamplePtr->blockptr = NULL;

					delete theblock;

					_Error.EmitSysErr("Unknown sample format");
				}
			}
			else
			{
				SamplePtr->blockptr = NULL;						//DAW 07Apr99
				SamplePtr = NULL;								//DAW 07Apr99
																//DAW 07Apr99
				delete theblock;								//DAW 07Apr99
																//DAW 07Apr99
				_Error.EmitSysErr("Chatter file size wrong... %d, %d elements!",fileindex,noSamples);//DAW 07Apr99
			}
		}
		else
			SamplePtr = NULL;
	}

	if (pelement)
	{
		pelement--;
		if (pelement < SamplePtr->noFiles)						//RDH 12Apr99
		{
			StartOff = SamplePtr->offsetptr[pelement].offset;		//RJS 27Jul98
			SampleSize = SamplePtr->offsetptr[pelement].size;		//RJS 27Jul98
		}
		else
			_Error.EmitSysErr("Chatter file size wrong... phrase %x, %d elements!",thephrase,SamplePtr->noFiles);

//DeadCode RJS 27Jul98 		if (pelement)											//RJS 23Jul98
//DeadCode RJS 27Jul98 			StartOff = SamplePtr->offsetptr[pelement-1];		//RJS 23Jul98
//DeadCode RJS 27Jul98 															
//DeadCode RJS 27Jul98 		SampleSize = SamplePtr->offsetptr[pelement] - StartOff;	//RJS 23Jul98
	}

	return(SamplePtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessMessages
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
void	RadioChatter::ProcessMessages(SLong frametime)
{
	if (	!lockout											//RJS 11Jun99
		&&	Manual_Pilot.ControlledAC2							//RJS 11Jun99
		&&	!Manual_Pilot.ControlledAC2->weap.Ejected)			//RJS 11Jun99
	{
		//Without internal sample buffer...							//RJS 25May99
		if (!_Replay.Playback && !Three_Dee.IsPaused())				//RJS 25May99
		{
			RadioMessageP	MessPtr = RootMessPtr;
			MESSAGE_STRUC*	newmess;

			if (MessPtr)
			{
				if (MessPtr->isAudio)
				{
					if (MessPtr->PlayQueue)
					{
						if (_Miles.SampleFinished(MessPtr->PlayQueue,hipriSet))//RJS 25May99
						{
							RootMessPtr = NULL;

							delete[]MessPtr->sampleptr;
							delete MessPtr;
						}											//RJS 25May99
						else
							timesincestart += frametime;		//RJS 01Apr99
					}
					else
					{
//DeadCode RJS 06Jul99 						SLong	frequency = 11025;
//DeadCode RJS 06Jul99 						if (MessPtr->theVoice == VOICE_REST)
//DeadCode RJS 06Jul99 							frequency += Math_Lib.rnd(1000) - 750;

						timesincelast = 0;
						timesincestart = 0;

						MessPtr->PlayQueue = _Miles.PlaySampleRadio(MessPtr->sampleptr,MessPtr->samplesize,MessPtr->VolScale,MessPtr->theFrequency,8);//RJS 06Jul99
					}
				}
				else
				{
					MessPtr->fakeplaytime -= frametime;		//RJS 01Apr99
					if (MessPtr->fakeplaytime <= 0)
					{
						MessPtr->fakeplaytime = 0;

						RootMessPtr = NULL;
						if (MessPtr->sampleptr)				//RJS 18Jun99
							delete[]MessPtr->sampleptr;		//RJS 18Jun99
						delete MessPtr;
					}
					else
						timesincestart += frametime;		//RJS 01Apr99
				}
			}
			else
			{
				hipriSet = false;									//RJS 25May99
				newmess = _MsgBuffer.SayNextMessage(frametime);		//RJS 10May99
				if (newmess)
				{
					//No audio if in accel...						//RJS 27May99
					if (!View_Point->Accel())						//RJS 27May99
						PlayMessage(*newmess);						//RJS 27May99

					_MsgBuffer.nothingatall = false;
					timesincelast = 0;
				}
				else
				{
					timesincelast += frametime;				//RJS 01Apr99
					if (timesincelast > 450)		//display nowt after 4.5secs//DAW 07Apr99
					{
	//DEADCODE DAW 05/05/99 					timesincelast = 450;
						_MsgBuffer.nothingatall = true;
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPlaceName
//Author		Robert Slater
//Date			Tue 14 Jul 1998
//
//Description	
//
//				Converts an item world X & Z coordinate
//				into its equivalent 4-digit landscape block number.
//
//				This is then turned into a 40 x 56 placename location...
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord		RadioChatter::GetPlaceNum(Coords3D* WPtr,int noelements)
{
			UWord	location;
			SLong	xof, zof, val;
			UWord	bigx, bigz, x, z;
//DEADCODE JIM 18/03/99 			Coords3D	*WPtr = &itm->World;

			// Sector shift = 21...
			val=WPtr->X>>21;

			x = (val&0x7);
			bigx = (val>>3);

			// Sector shift = 21...
			val=WPtr->Z>>21;

			z = (val&0x7);
			bigz = (val>>3);

			// x vals range from 2 to 6
			// z vals range from 2 to 8

			if (bigx > 6)
				bigx = 6;

			bigx -= 1;
			bigz -= 1;

			xof = (bigx * 8) + x;
			zof = (bigz * 8) + z;

			location = (zof * 40) + xof;
			if (location < noelements)
				return location;
			else
				return 0;
}

SectorNameP	RadioChatter::GetPlaceName(UWord location)
{
	if (LoadSectorNames(FIL_RCHAT_NAMEGRID))
		if (location < theSectors.noelements)
			return	&theSectors.PlaceNames[location];
	return NULL;
}

SectorNameP	RadioChatter::GetPlaceName(ItemPtr	itm)
{
	SectorNameP	NamePtr = NULL;
	if (LoadSectorNames(FIL_RCHAT_NAMEGRID) && itm)						//RJS 15Jun99
	{
		UWord location=GetPlaceNum(&itm->World,theSectors.noelements);
		return (GetPlaceName(location));
	}

	return(NamePtr);
}
//DeadCode DAW 26Mar99 SectorNameP	RadioChatter::GetPlaceName(ItemPtr	itm)
//DeadCode DAW 26Mar99 {
//DeadCode DAW 26Mar99 	SectorNameP	NamePtr = NULL;
//DeadCode DAW 26Mar99 	if (itm)
//DeadCode DAW 26Mar99 	{
//DeadCode DAW 26Mar99 		if (LoadSectorNames(FIL_RCHAT_NAMEGRID))
//DeadCode DAW 26Mar99 		{
//DeadCode DAW 26Mar99 			UWord	location;
//DeadCode DAW 26Mar99 			SLong	xof, zof, val;
//DeadCode DAW 26Mar99 			UWord	bigx, bigz, x, z;
//DeadCode DAW 26Mar99 			Coords3D	*WPtr = &itm->World;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			// Sector shift = 21...
//DeadCode DAW 26Mar99 			val=WPtr->X>>21;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			x = (val&0x7);
//DeadCode DAW 26Mar99 			bigx = (val>>3);
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			// Sector shift = 21...
//DeadCode DAW 26Mar99 			val=WPtr->Z>>21;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			z = (val&0x7);
//DeadCode DAW 26Mar99 			bigz = (val>>3);
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			// x vals range from 2 to 6
//DeadCode DAW 26Mar99 			// z vals range from 2 to 8
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			if (bigx > 6)
//DeadCode DAW 26Mar99 				bigx = 6;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			bigx -= 1;
//DeadCode DAW 26Mar99 			bigz -= 1;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			xof = (bigx * 8) + x;
//DeadCode DAW 26Mar99 			zof = (bigz * 8) + z;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			location = (zof * 40) + xof;
//DeadCode DAW 26Mar99 			if (location < theSectors.noelements)
//DeadCode DAW 26Mar99 				NamePtr = &theSectors.PlaceNames[location];
//DeadCode DAW 26Mar99 		}
//DeadCode DAW 26Mar99 	}
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	return(NamePtr);
//DeadCode DAW 26Mar99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSectorNames
//Author		Robert Slater
//Date			Tue 14 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SectorNameP	RadioChatter::LoadSectorNames(SLong	thefile)
{
	if (theSectors.theblock == NULL)
	{
		fileblock	*theblock = new fileblock ((FileNum)thefile);
		if (theblock)
		{
			theSectors.theblock = theblock;
			theSectors.PlaceNames = (SectorNameP) getdata(theblock);
			theSectors.noelements = getsize(theblock) / sizeof(SectorName);
		}
	}

	return(theSectors.PlaceNames);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetScript
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
UWordP	RadioChatter::GetScript(SLong	scriptno,RadioMessageP MessPtr,PhraseTables& singlephrase)
{
	UWordP	ptr = NULL;

	singlephrase = PHRASE_NULL;
	if (scriptno)
	{
		if (theScripts.theblock == NULL)
		{
			fileblock	*theblock = new fileblock (FIL_RCHAT_SCRIPT_TABLE);
			if (theblock)
			{
				theScripts.theblock = theblock;
				theScripts.ScriptTable = (ULongP) getdata(theblock);
			}
		}

		ULong	scriptptr = theScripts.ScriptTable[scriptno-1];
		ULong	isscript = scriptptr & 0x80000000;

		if (isscript)											//RJS 12Apr99
		{
			scriptptr -= 0x80000000;
			ptr = (UWordP) ((UByteP)theScripts.ScriptTable + scriptptr);

			MessPtr->MainStrip(ptr);							//RJS 11May99
		}
		else
			singlephrase = (PhraseTables) scriptptr;
	}

	return(ptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayMessage
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode RJS 27Jan99 void	RadioChatter::PlayMessage(	int		Scriptno,
//DeadCode RJS 27Jan99 									ItemPtr	Caller,
//DeadCode RJS 27Jan99 									ItemPtr	Trg,
//DeadCode RJS 27Jan99 									ItemPtr	Callee,
//DeadCode RJS 27Jan99 									Bool	noCaller	)
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	if (Save_Data.vol.rchat)
//DeadCode RJS 27Jan99 	{
//DeadCode RJS 27Jan99 		TargetIndexes	tripeval;
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 		PlayMessage(Scriptno,tripeval,Caller,Trg,Callee,noCaller);
//DeadCode RJS 27Jan99 	}
//DeadCode RJS 27Jan99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandMessage
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ExpandMessage(PhraseBuffer&	fbuff,
									int		Scriptno,
									UWord&	randno,
									const	TargetIndexes&	tstruc,
									ItemPtr	Caller,
									ItemPtr	Trg,
									ItemPtr	Callee	)
{
	//Block RootMessPtr, so we can view while playing...
	lockout = true;												//RJS 04Jun99
	RadioMessageP	OldRootMessPtr = RootMessPtr;
	RootMessPtr = NULL;
	RadioMessageP	MessPtr = CreateMessage((mobileitem*)Caller,
											(mobileitem*)Trg,
											(mobileitem*)Callee,
											randno,
											tstruc,
											VOICE_MIN,
											&fbuff	);

	if (MessPtr)
		Message_DecomposeScript(MessPtr,Scriptno);

	RootMessPtr = OldRootMessPtr;
	lockout = false;											//RJS 04Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandCallsign
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ExpandCallsign(PhraseBuffer&	phbuf, ItemPtr	Caller,const VoiceType& voice)
{
	TargetIndexes	tstruc;
	int				thephrase = 0;
	UWord			tmprand = 0;
	if (Caller)
		thephrase = PHRASE_CALLEE;
	else
	{
		// Pick from voice...
 		switch (voice)											//RJS 17Mar99
 		{														//RJS 17Mar99
 		case VOICE_TOWER:										//RJS 17Mar99
 			thephrase = PHRASE_THETOWER;						//RJS 17Mar99
 			break;												//RJS 17Mar99
 		case VOICE_DENTIST:										//RJS 17Mar99
 			thephrase = PHRASE_THEDENTIST;						//RJS 17Mar99
 			break;												//RJS 17Mar99
//DeadCode RDH 04May99  		case VOICE_FACTAC:										//RJS 17Mar99
//DeadCode RDH 04May99  			thephrase = PHRASE_THETAC1 + Math_Lib.rnd(3);		//RJS 17Mar99
//DeadCode RDH 04May99  			break;												//RJS 17Mar99
 		}														//RJS 17Mar99
	}

	ExpandMessage(phbuf,thephrase,tmprand,tstruc,NULL,NULL,Caller);	//RDH 04May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandPlace
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ExpandPlacename(PhraseBuffer&	phbuf, ItemPtr	Caller)
{
	if (Caller)
	{
		TargetIndexes	tstruc;
		UWord			tmprand = 0;

		ExpandMessage(phbuf,PHRASE_PLACENAMES,tmprand,tstruc,NULL,Caller,NULL);//RDH 04May99
	}
}
void	RadioChatter::ExpandPlacename(PhraseBuffer&	phbuf, UWord place)
{
		TargetIndexes	tstruc;
		tstruc.targetname=place;
		UWord	tmprand=0;
		ExpandMessage(phbuf,PHRASE_PLACENAMES,tmprand,tstruc,NULL,NULL,NULL);//RDH 04May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Message_DecomposeScript
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Message_DecomposeScript(RadioMessageP	MessPtr,int Scriptno)
{
	UWordP			ScriptPtr;
	PhraseTables	ThePhrase;
	int		count=0;
	ULong	nochoices = Scriptno & 0xFFFF0000;

	if (nochoices)
	{
//DeadCode RJS 12Apr99 		nochoices >>= 16;

		Scriptno &= 0xFFFF;
		ScriptPtr = GetScript(Scriptno,MessPtr,ThePhrase);		//RJS 12Apr99
		if (ScriptPtr)
		{
			ThePhrase = (PhraseTables) *ScriptPtr;
			while (ThePhrase != PHRASE_NULL)
			{
				ComposeSample(MessPtr,ThePhrase);
				ScriptPtr++;

				lastPhrase = ThePhrase;
				ThePhrase = (PhraseTables) *ScriptPtr;
			}
		}
		else
			ComposeSample(MessPtr,ThePhrase);
	}
	else
		ComposeSample(MessPtr,Scriptno);

	delete MessPtr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayMessage
//Author		Robert Slater
//Date			Wed 13 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::PlayMessage(const	MESSAGE_STRUC&	radiomessage, SLong vol, bool isChatter)
{
#ifndef NDEBUG
#ifdef CHATTERTRACE
// defined in rchatter.h
	UWord cw=GETFPCW();
	::AfxTrace("Saying: %08x\n",radiomessage.messagecnt);//radiomessage.scriptno);
	SETFPCW(cw);
#endif
#endif
	RadioMessageP	MessPtr = CreateMessage((mobileitem*)radiomessage.caller,
											(mobileitem*)radiomessage.target,
											(mobileitem*)radiomessage.callee,
											radiomessage.randomno,//RDH 04May99
											radiomessage.targetinfo,
											radiomessage.voiceindex,
											NULL,
											vol,
											radiomessage.voxstate);

	if (MessPtr)
	{
 		if (radiomessage.isComms)	MessPtr->isAudio = FALSE;//RJS 22Mar99

//DeadCode RJS 10May99 		if (radiomessage.addThinkTime)
//DeadCode RJS 10May99  			ComposeSample(MessPtr,PHRASE_RANDOMTHINKTIME);
		DecomposeScript(MessPtr,radiomessage.scriptno);
	}

	//Expand latest message to string straight away...
	if (!isChatter)													//RJS 15Jun99
		_MsgBuffer.ExpandDirect(radiomessage);						//RJS 15Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandMessage
//Author		Robert Slater
//Date			Wed 13 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ExpandMessage(PhraseBuffer&	fbuff, const MESSAGE_STRUC&	radiomessage )
{
	//Block RootMessPtr, so we can view while playing...
	lockout = true;												//RJS 04Jun99
	RadioMessageP	OldRootMessPtr = RootMessPtr;
	RootMessPtr = NULL;
	RadioMessageP	MessPtr = CreateMessage((mobileitem*)radiomessage.caller,
											(mobileitem*)radiomessage.target,
											(mobileitem*)radiomessage.callee,
											radiomessage.randomno,//RDH 04May99
											radiomessage.targetinfo,
											radiomessage.voiceindex,
											&fbuff,
											128,
											radiomessage.voxstate);

	if (MessPtr)
	{
		if (radiomessage.isComms)	MessPtr->isAudio = FALSE;//RJS 22Mar99

		Message_DecomposeScript(MessPtr,radiomessage.scriptno);
	}

	RootMessPtr = OldRootMessPtr;
	lockout = false;											//RJS 04Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TimeOut
//Author		Robert Slater
//Date			Wed 27 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	RadioChatter::TimeOut()
{
	if (timesincelast < TIME_TIMEOUT)
		return (FALSE);

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RADIOMESSAGE
//Author		Robert Slater
//Date			Wed 27 Jan 1999
//
//Description	constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RADIOMESSAGE::RADIOMESSAGE(	RADIOMESSAGE*& 	MessPtr,
							ItemPtr 		from,
							ItemPtr			about,
							ItemPtr			to,
							SWord			vol,
							const TargetIndexes&	tstruc,
							PhraseBuffer*	fbuffp,
							VoiceType		vox	)
{
	caller = (mobileitem*) from;
	target = (mobileitem*) about;
	callee = (mobileitem*) to;

	theFrequency = 11025;										//RJS 06Jul99
	//Even quieter if you want the voice off...					//RJS 30Jun99
	if (	(vox == VOICE_PLAYER)								//RJS 30Jun99
		&&	Save_Data.gamedifficulty[GD_NOPLAYERVOICE]	)		//RJS 30Jun99
		VolScale = 0;											//RJS 30Jun99
	else
	{
		if (from)
			VolScale = vol;
		else
			VolScale = 64;				//Quiet if no caller...	//RJS 30Jun99
	}

	TargetStuff = tstruc;					
	messbuffptr = fbuffp;
	theVoice = vox;


	next = NULL;
	sampleptr = NULL;
	samplelength = 0;

	bearing = 0;
	distance = -1;
	nophrases = 0;
	samplesize = 0;
	isPlaying = FALSE;
	PlayQueue = NULL;
									   
	if ((fbuffp==NULL) && (Save_Data.vol.rchat > 0))			//RJS 22Mar99
	{								   
		isAudio = TRUE;				   
				
		MessPtr = this;				   
	}								   
	else		
	{			   
		isAudio = FALSE;
		MessPtr = this;
	}

	IsExcited = 0;												//RJS 18Mar99
	TextNum = FALSE;											//RJS 18Mar99
	fakeplaytime = 0;											//RJS 22Mar99

	randomvoice = 0;											//RJS 17May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindVoiceType
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MESSAGE_STRUC::SetVoiceType()
{
	voiceindex = VOICE_PLAYER;										  //RDH 11/05/99
	if (caller)
	{
		if (caller->AcIsPlayer())
			voiceindex = VOICE_PLAYER;
 		else
 		{
			if (caller->fly.callname > Call_FAC0)					  //RJS 12/04/99
				voiceindex = VOICE_FACTAC;
			else
 				voiceindex = VOICE_REST;
 		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TriggerMsg
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
#ifdef TriggerMsg
#undef	TriggerMsg
#endif
const MESSAGE_STRUC&	RadioChatter::TriggerMsg(const MESSAGE_STRUC&	msg)
{
	//We still want to buffer in accel mode!					//RJS 27May99
	if (!_Replay.Playback && msg.scriptno)						//RJS 09Jun99
	{
		if (!_MsgBuffer.AddToBuffer(msg))
		{
			if (!View_Point->Accel())							//RJS 28May99
			{
				if (TimeOut()){			// timeout > 30 secs?
					PlayMessage(msg,105,true);					//RJS 15/06/99
				}
			}
		}
		else
		{
			//prioritise!
			if (msg.priority == PRI_MAX)						//RJS 25May99
			{													//RJS 25May99
				hipriSet = true;								//RJS 25May99
				if (	RootMessPtr
					&&	(RootMessPtr->fakeplaytime > 200))		//RJS 25May99
					RootMessPtr->fakeplaytime = 200;			//RJS 25May99
			}													//RJS 25May99
		}
	}
	return(msg);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ComposeDigitNumber
//Author		Robert Slater
//Date			Wed 10 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ComposeDigitNumber(RadioMessageP	MessPtr, SLong number, SWord nodigits)
{
	if (number >= 0)
	{
		SLong	tmpnumber;
		SLong	digits[32];
		SWord	digitcnt = 0;

		do
		{
			tmpnumber = number;
			number /= 10;

			// extract remainder + 1, cos 0 not valid script..
			digits[digitcnt++] = (tmpnumber-(number*10))+1;
		}
		while (number);

		while (digitcnt < nodigits)		digits[digitcnt++] = 1;					//zero
	
		MessPtr->TextNum = TRUE;								//RJS 18Mar99

		digitcnt--;
		if (digitcnt > -1)
			ComposeSample(MessPtr,PHRASE_NUMTABLE1_N+digits[digitcnt--]);//RJS 18Mar99
		else
			ComposeSample(MessPtr,PHRASE_NUMBER0);	//zero		//RJS 18Mar99

		while (digitcnt > -1)
		{
			if (MessPtr->isAudio)								//RJS 12Apr99
 				ComposeSample(MessPtr,PHRASE_STOP);				//RJS 12Apr99

			ComposeSample(MessPtr,PHRASE_NUMTABLE1_N+digits[digitcnt]);
			digitcnt--;
		}

		MessPtr->TextNum = FALSE;								//RJS 18Mar99
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessUserMessage
//Author		Robert Slater
//Date			Thu 11 Feb 1999
//
//Description	Calc delay, repeatable and priority
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MESSAGE_STRUC::ProcessUserMessage()
{
	// Priority...
	if (messagetype & MSG_LP)
	{
		priority = PRI_LOW;
		if (messagetype & MSG_REPEAT)
			visibility = NOTVIS_2;
		else
			visibility = NOTVIS_1;
   	}
	else
	{
//DEADCODE RDH 02/04/99 		if ((caller == Manual_Pilot.ControlledAC2) || (callee == Manual_Pilot.ControlledAC2))
//DEADCODE RDH 02/04/99 			priority = PRI_MAX;
//DEADCODE RDH 02/04/99 		else
		priority = PRI_MED;
		if (messagetype & MSG_REPEAT)
			visibility = VIS_2;
		else
			visibility = VIS_3;
	}

	if (messagetype & MSG_DELAY)
		timeout = 50 + Math_Lib.rnd(50);						//RJS 13May99
	else
		timeout = 0;

	if (messagetype & MSG_COMMS)
		isComms = TRUE;
	else
		isComms = FALSE;

	if (messagetype & MSG_HIPRIORITY_X)							//RJS 13May99
		priority = PRI_MAX;										//RJS 13May99
	else
	{
		if (messagetype & MSG_MEDHIPRIORITY_X)					//RJS 24Jun99
			priority = PRI_MEDMAX;
	}

	if (messagetype & MSG_BLOCKCHATTER)							//RJS 06Jul99
		blockchatter = TRUE;									//RJS 06Jul99
	else														//RJS 06Jul99
		blockchatter = FALSE;									//RJS 06Jul99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PhraseToResource
//Author		Robert Slater
//Date			Fri 12 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ULong	RadioChatter::PhraseToResource(SLong	thePhrase)
{
	return (PhraseToFile[thePhrase>>8].idsresourcename+(thePhrase&0xFF));
}

static int poodistance = 25000;
static UWord poobearing = 0;
static int	poogust = PHRASE_GUSTLIGHT;
static int	pootargtype = 1;
static int	pootargname = 1;
static int	pootargmove = 1;
static int	pootargweap = 1;
static UWord poobearing2 = 0;
static int  poospeed = 1500;
static int  pooheight = 1;
static int  pooaf = 1;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FiddleROL
//Author		Robert Slater
//Date			Mon 22 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	RADIOMESSAGE::FiddleROL()
{
	distance = poodistance;
	bearing = poobearing;
	pitch = Math_Lib.rnd(32768) - 16384;
	speed = poospeed;

	return(TRUE);
}

void	RadioChatter::ComposeFakeDigitNumber(RadioMessageP	MessPtr, SLong number, SWord nodigits)
{
//DeadCode RJS 18Mar99 	if (number >= 0)
//DeadCode RJS 18Mar99 	{
//DeadCode RJS 18Mar99 		SLong	tmpnumber;
//DeadCode RJS 18Mar99 		SLong	digits[32];
//DeadCode RJS 18Mar99 		SLong	digitcnt = 0;
//DeadCode RJS 18Mar99 
//DeadCode RJS 18Mar99 		do
//DeadCode RJS 18Mar99 		{
//DeadCode RJS 18Mar99 			tmpnumber = number;
//DeadCode RJS 18Mar99 			number /= 10;
//DeadCode RJS 18Mar99 
//DeadCode RJS 18Mar99 			// extract remainder + 1, cos 0 not valid script..
//DeadCode RJS 18Mar99 			digits[digitcnt++] = (tmpnumber-(number*10))+1;
//DeadCode RJS 18Mar99 		}
//DeadCode RJS 18Mar99 		while (number);
//DeadCode RJS 18Mar99 
//DeadCode RJS 18Mar99 		while (digitcnt < nodigits)		digits[digitcnt++] = 1;					//zero
//DeadCode RJS 18Mar99 
//DeadCode RJS 18Mar99 		digitcnt--;
//DeadCode RJS 18Mar99 		if (digitcnt > -1)
//DeadCode RJS 18Mar99 			ComposeFakeSample(MessPtr,PHRASE_WNUMBERS_N+digits[digitcnt--]);
//DeadCode RJS 18Mar99 		else
//DeadCode RJS 18Mar99 			ComposeFakeSample(MessPtr,PHRASE_WNUMBERS_N+1);	//zero
//DeadCode RJS 18Mar99 
//DeadCode RJS 18Mar99 		while (digitcnt > -1)
//DeadCode RJS 18Mar99 		{
//DeadCode RJS 18Mar99 			ComposeFakeSample(MessPtr,PHRASE_COMMA);
//DeadCode RJS 18Mar99 			ComposeFakeSample(MessPtr,PHRASE_WNUMBERS_N+digits[digitcnt]);
//DeadCode RJS 18Mar99 			digitcnt--;
//DeadCode RJS 18Mar99 		}
//DeadCode RJS 18Mar99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ComposeFakeSample
//Author		Robert Slater
//Date			Mon 22 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ComposeFakeSample(RadioMessageP	MessPtr,int phrase)
{
//DeadCode RJS 17Mar99 	if (phrase != PHRASE_NULL)									//RJS 12Feb99
//DeadCode RJS 17Mar99 	{
//DeadCode RJS 17Mar99 		int			ptype = phrase & 0xFF00;
//DeadCode RJS 17Mar99 		int			pelement = phrase & 0xFF;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 		if (pelement)
//DeadCode RJS 17Mar99 		{
//DeadCode RJS 17Mar99 			RadioSampleRec*	RSamplePtr;
//DeadCode RJS 17Mar99 			int				StartOffset;
//DeadCode RJS 17Mar99 			int				SampleSize;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			RSamplePtr = LoadSample(MessPtr,phrase,StartOffset,SampleSize);
//DeadCode RJS 17Mar99 			if (RSamplePtr)
//DeadCode RJS 17Mar99 				MessPtr->AddSample(RSamplePtr->dataptr,StartOffset,SampleSize,phrase);//RJS 12Jan99
//DeadCode RJS 17Mar99 		}
//DeadCode RJS 17Mar99 		else
//DeadCode RJS 17Mar99 		{
//DeadCode RJS 17Mar99 			RadioOnz*		phraseControl = &PhraseToFile[ptype>>8];
//DeadCode RJS 17Mar99 			PhraseTables	compositePhrase;
//DeadCode RJS 17Mar99 			int				pilotno;
//DeadCode RJS 17Mar99 			int				squadron;
//DeadCode RJS 17Mar99 			int				maxrange = 1500000;
//DeadCode RJS 17Mar99 			int				nextrange = PHRASE_RANGES10;
//DeadCode RJS 17Mar99 			int				punctuate = PHRASE_COMMA;			//RJS 08Mar99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			switch (ptype)
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 			case PHRASE_CALLERGROUP:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				AirStrucPtr	ac = (AirStrucPtr) MessPtr->callee;
//DeadCode RJS 17Mar99 				ac->fly.callname++;
//DeadCode RJS 17Mar99 				if (ac->fly.callname > 33)
//DeadCode RJS 17Mar99 					ac->fly.callname = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				squadron = ac->fly.callname;
//DeadCode RJS 17Mar99 				if (squadron)
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_CALLGROUPS+squadron);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_CALLEEGROUP:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				AirStrucPtr	ac = (AirStrucPtr) MessPtr->callee;
//DeadCode RJS 17Mar99 				ac->fly.callname++;
//DeadCode RJS 17Mar99 				if (ac->fly.callname > 33)
//DeadCode RJS 17Mar99 					ac->fly.callname = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				squadron = ac->fly.callname;
//DeadCode RJS 17Mar99 				if (squadron)
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_CALLGROUPS+squadron);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_CALLERSTOP:
//DeadCode RJS 17Mar99 				punctuate = PHRASE_STOP;
//DeadCode RJS 17Mar99 			case PHRASE_THISCALLER:
//DeadCode RJS 17Mar99 			case PHRASE_CALLER:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;//RJS 13Jan99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ac->fly.callname++;
//DeadCode RJS 17Mar99 				if (ac->fly.callname > 33)
//DeadCode RJS 17Mar99 					ac->fly.callname = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ac->fly.callnum++;
//DeadCode RJS 17Mar99 				if (ac->fly.callnum > 31)
//DeadCode RJS 17Mar99 					ac->fly.callnum = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				pilotno = ac->fly.callnum;		
//DeadCode RJS 17Mar99 				squadron = ac->fly.callname;
//DeadCode RJS 17Mar99 				Bool	fixlater = FALSE;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (squadron)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					if (ptype == PHRASE_THISCALLER)				//RJS 15Jan99
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						punctuate = PHRASE_STOP;
//DeadCode RJS 17Mar99 						if (Math_Lib.rnd() > 44000)
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,PHRASE_THISIS);	//RJS 15Jan99
//DeadCode RJS 17Mar99 						else
//DeadCode RJS 17Mar99 							fixlater = TRUE;				//RJS 10Feb99
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_CALLSIGNS_N+squadron);
//DeadCode RJS 17Mar99 					if (pilotno)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						if ((pilotno == 1) && (fixlater==FALSE))
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							if (Math_Lib.rnd() > 32767)
//DeadCode RJS 17Mar99 								ComposeFakeSample(MessPtr,PHRASE_LEAD);
//DeadCode RJS 17Mar99 							else
//DeadCode RJS 17Mar99 								ComposeFakeSample(MessPtr,PHRASE_LEAD2);
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 						else
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							if ((PHRASE_CALLSIGNS_N+squadron) < PHRASE_THEFAC1)
//DeadCode RJS 17Mar99 								ComposeFakeSample(MessPtr,PHRASE_NUMBERS_N+pilotno+1);
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					if (fixlater)
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_HERE);	//RJS 10Feb99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,punctuate);		//RJS 08Mar99
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_SUBJECT:
//DeadCode RJS 17Mar99 			case PHRASE_CALLEE:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				AirStrucPtr	ac = (AirStrucPtr) MessPtr->callee;//RJS 13Jan99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ac->fly.callname++;
//DeadCode RJS 17Mar99 				if (ac->fly.callname > 33)
//DeadCode RJS 17Mar99 					ac->fly.callname = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ac->fly.callnum++;
//DeadCode RJS 17Mar99 				if (ac->fly.callnum > 31)
//DeadCode RJS 17Mar99 					ac->fly.callnum = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				pilotno = ac->fly.callnum;			
//DeadCode RJS 17Mar99 				squadron = ac->fly.callname;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (squadron)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_CALLSIGNS_N+squadron);
//DeadCode RJS 17Mar99 					if (pilotno)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						if ((pilotno == 1) && (Math_Lib.rnd() > 32000))
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,PHRASE_LEAD);
//DeadCode RJS 17Mar99 						else
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							if ((PHRASE_CALLSIGNS_N+squadron) < PHRASE_THEFAC1)
//DeadCode RJS 17Mar99 								ComposeFakeSample(MessPtr,PHRASE_NUMBERS_N+pilotno+1);
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_RANGESKM10:
//DeadCode RJS 17Mar99 			case PHRASE_RANGES10:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				SLong	dist = MessPtr->distance;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				dist += phraseControl->subFactor;				//RJS 12Feb99
//DeadCode RJS 17Mar99 				dist /= phraseControl->divFactor;				//RJS 12Feb99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,ptype+dist);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_RANGESKM:
//DeadCode RJS 17Mar99 				maxrange = 1975000;
//DeadCode RJS 17Mar99 				nextrange = PHRASE_RANGESKM10;
//DeadCode RJS 17Mar99 			case PHRASE_RANGESIMP:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				SLong	dist = MessPtr->distance;
//DeadCode RJS 17Mar99 				if (dist > maxrange)					//10miles
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,nextrange);//RJS 10Feb99
//DeadCode RJS 17Mar99 					break;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			
//DeadCode RJS 17Mar99 				dist += phraseControl->subFactor;			//RJS 12Feb99
//DeadCode RJS 17Mar99 				dist /= phraseControl->divFactor;			//RJS 12Feb99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (dist == 0)
//DeadCode RJS 17Mar99 					dist = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,ptype+dist);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_NUMBERCLOCK:
//DeadCode RJS 17Mar99 			case PHRASE_BEARINGS:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->FiddleROL())
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					UWord	relbearing = MessPtr->bearing;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					relbearing += phraseControl->subFactor;		//RJS 12Feb99
//DeadCode RJS 17Mar99 					relbearing /= phraseControl->divFactor;		//RJS 12Feb99
//DeadCode RJS 17Mar99 					if (!relbearing)
//DeadCode RJS 17Mar99 						relbearing = 1;
//DeadCode RJS 17Mar99 						
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,ptype+relbearing);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					poobearing += 5461;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_XRELHEIGHTS:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->distance < 150000)		// 1mile
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					SLong	rheights = MessPtr->pitch;
//DeadCode RJS 17Mar99 					if (rheights > 5000)
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_EXHIGH);
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						if (rheights < -5000)
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,PHRASE_EXLOW);
//DeadCode RJS 17Mar99 						else
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,PHRASE_EXOURLEVEL);
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_RELHEIGHTS);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_RELHEIGHTS:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				// Must cater for relative heights from
//DeadCode RJS 17Mar99 				// different perspectives!!
//DeadCode RJS 17Mar99 				//
//DeadCode RJS 17Mar99 				// ie. caller and target, or callee and target
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				SLong	rheights = MessPtr->pitch;
//DeadCode RJS 17Mar99 				if (rheights > 5000)
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_HIGH);
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					if (rheights < -5000)
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_LOW);
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_OURLEVEL);//RJS 10Feb99
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_HEIGHTSANGELS:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->target)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					SLong	aheight = MessPtr->realheight;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					aheight += phraseControl->subFactor;
//DeadCode RJS 17Mar99 					aheight /= phraseControl->divFactor;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					// Angels is 1000th of the height.
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					aheight /= 1000;
//DeadCode RJS 17Mar99 				
//DeadCode RJS 17Mar99 					ComposeFakeDigitNumber(MessPtr,SLong(aheight),2);
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_ANGELS);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_HEIGHTSIMP:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				SLong	height = MessPtr->realheight;
//DeadCode RJS 17Mar99 				if (height > -1)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					height += phraseControl->subFactor;			//RJS 12Feb99
//DeadCode RJS 17Mar99 					height /= phraseControl->divFactor;			//RJS 12Feb99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					if (height == 0)
//DeadCode RJS 17Mar99 						height = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,ptype+height);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_PLACENAMESNP:
//DeadCode RJS 17Mar99 				lastPhrase = PHRASE_APPROACHING;
//DeadCode RJS 17Mar99 			case PHRASE_PLACENAMES:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				SectorNameP	NamePtr;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (lastPhrase == PHRASE_APPROACHING)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 //					RelativeToPilot = TRUE;
//DeadCode RJS 17Mar99 					NamePtr = GetFakePlaceName();
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 					NamePtr = GetFakePlaceName();
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (NamePtr)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					if (lastPhrase == PHRASE_NULL)					//RJS 11Feb99
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,NamePtr->prefix);
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						if (lastPhrase != PHRASE_APPROACHING)		//RJS 11Feb99
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							if (	((NamePtr->prefix >= PHRASE_CENTRAL) && (NamePtr->prefix < PHRASE_OVER))
//DeadCode RJS 17Mar99 								||	(NamePtr->prefix == PHRASE_NULL)	)
//DeadCode RJS 17Mar99 								ComposeFakeSample(MessPtr,PHRASE_OVER);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,NamePtr->prefix);
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,NamePtr->name);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_NAMED_AC:
//DeadCode RJS 17Mar99 			case PHRASE_NAMED_ACS:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->target && (MessPtr->target->Status.size==AIRSTRUCSIZE))
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					ClassPtr	clstyp = ((AirStrucPtr)MessPtr->target)->classtype;
//DeadCode RJS 17Mar99 					SLong		pno = clstyp->phrasename - PHRASE_NAMED_AC;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,ptype+pno);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					pno++;
//DeadCode RJS 17Mar99 					if (pno > 13)
//DeadCode RJS 17Mar99 						pno = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				   	clstyp->phrasename = ptype+pno;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_DIRECTIONS_TRAVEL:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->TargetStuff.targetdirection)	//RJS 12Jan99
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_HEADING);
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,ptype+MessPtr->TargetStuff.targetdirection);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					ULong	direction;
//DeadCode RJS 17Mar99 					Bool	dirset = FALSE;
//DeadCode RJS 17Mar99 					SWordP	hdgptr;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					if (RelativeToPilot == TRUE)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						if (MessPtr->caller)
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							hdgptr = (SWordP) &MessPtr->caller->hdg;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 							direction = MessPtr->caller->hdg;
//DeadCode RJS 17Mar99 							dirset = TRUE;
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						if (MessPtr->target)
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							hdgptr = (SWordP) &MessPtr->target->hdg;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 							direction = MessPtr->target->hdg;
//DeadCode RJS 17Mar99 							dirset = TRUE;
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					*hdgptr = (*hdgptr) + 8192;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					if (dirset)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						direction += phraseControl->subFactor;	//RJS 12Feb99
//DeadCode RJS 17Mar99 						direction /= phraseControl->divFactor;	//RJS 12Feb99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_HEADING);
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,ptype+direction);
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_BANDIT_ALERT:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				ULong	randy = Math_Lib.rnd();
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				randy += phraseControl->subFactor;				//RJS 12Feb99
//DeadCode RJS 17Mar99 				randy /= phraseControl->divFactor;				//RJS 12Feb99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,ptype+randy);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_TARGTYPE:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (pootargtype < 6)
//DeadCode RJS 17Mar99 					pootargtype++;
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 					pootargtype = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,ptype+pootargtype);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_TARGNAM:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (pootargname < 34)
//DeadCode RJS 17Mar99 					pootargname++;
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 					pootargname = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,ptype+pootargname);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_TARGMOV:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (pootargmove < 16)
//DeadCode RJS 17Mar99 					pootargmove++;
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 					pootargmove = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,ptype+pootargmove);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_WEAPONS:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (pootargweap < 7)
//DeadCode RJS 17Mar99 					pootargweap++;
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 					pootargweap = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,ptype+pootargweap);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_HEIGHTS:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				MessPtr->realheight = pooheight;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				UWord	randy = Math_Lib.rnd();
//DeadCode RJS 17Mar99 				if (randy < 60000)
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_HEIGHT);
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					if (randy < 64000)
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_ESTHEIGHT);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (Math_Lib.rnd() > 63000)
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_HEIGHTSANGELS);
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					if (Save_Data.gamedifficulty [GD_UNITS])
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						ULong	olddist = MessPtr->distance;
//DeadCode RJS 17Mar99 						MessPtr->distance = MessPtr->realheight;
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_RANGESKM);
//DeadCode RJS 17Mar99 						MessPtr->distance = olddist;
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_HEIGHTSIMP);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				pooheight += 166667;
//DeadCode RJS 17Mar99 				if (pooheight > (12*166667))
//DeadCode RJS 17Mar99 					pooheight = 1;
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_SPEEDS:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->FiddleROL())
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					ULong	vel;
//DeadCode RJS 17Mar99 					SLong	newphrase;
//DeadCode RJS 17Mar99 					
//DeadCode RJS 17Mar99 					if (Save_Data.gamedifficulty [GD_UNITS])
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						// metric (m/cm)... but have as knots
//DeadCode RJS 17Mar99 						vel = Float(MessPtr->speed) * 0.19438;
//DeadCode RJS 17Mar99 						newphrase = PHRASE_SPEEDSKNOT;
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						// mph
//DeadCode RJS 17Mar99 						vel = Float(MessPtr->speed) * 0.225;
//DeadCode RJS 17Mar99 						newphrase = PHRASE_SPEEDSMPH;
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					MessPtr->speed = vel;
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,newphrase);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					poospeed += 257;
//DeadCode RJS 17Mar99 					if (poospeed > 3601)
//DeadCode RJS 17Mar99 						poospeed = 1;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_BEARINGNO:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->FiddleROL())
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					UWord	relbearing = UWord(MessPtr->bearing);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					relbearing *= 360;
//DeadCode RJS 17Mar99 					relbearing >>= 16;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeDigitNumber(MessPtr,SLong(relbearing),3);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					poobearing += 5461;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_RANGES:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->FiddleROL())
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					UWord	randpoo = Math_Lib.rnd();
//DeadCode RJS 17Mar99 					if (randpoo > 32767)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						if (randpoo > 55000)
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,PHRASE_ATRANGE);
//DeadCode RJS 17Mar99 						else
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,PHRASE_RANGE);
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					if (Save_Data.gamedifficulty [GD_UNITS])
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_RANGESKM);
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_RANGESIMP);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					poodistance += 25000;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_SPEEDSMPH:
//DeadCode RJS 17Mar99 			case PHRASE_SPEEDSKNOT:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				ULong	vel = MessPtr->speed;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (vel < 300)
//DeadCode RJS 17Mar99 					vel = 300;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (vel > 700)
//DeadCode RJS 17Mar99 					vel = 700;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				vel += phraseControl->subFactor;			//RJS 12Feb99
//DeadCode RJS 17Mar99 				vel /= phraseControl->divFactor;			//RJS 12Feb99
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,ptype+vel);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			case PHRASE_ALTWINDBEARINGNO:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				windHeightSet = 1061666;	//35,000ft in cm
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,PHRASE_ALTWIND);
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,PHRASE_COMMA);
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,PHRASE_WINDBEARINGNO);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_SURFACEWINDBEARINGNO:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				windHeightSet = 0;
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,PHRASE_SURFACEWIND);
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,PHRASE_COMMA);
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,PHRASE_WINDBEARINGNO);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_WINDBEARINGNO:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				SLong	vx,vy,vz;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				// height is set up by prevous wind phrase...
//DeadCode RJS 17Mar99 				if (MMC.Sky.GetWind(windHeightSet,vx,vy,vz))
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					ANGLES	bearing,pitch;
//DeadCode RJS 17Mar99 					
//DeadCode RJS 17Mar99 					Math_Lib.Intercept(vx,vy,vz,windSpeedSet,bearing,pitch);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_THEBEARING);
//DeadCode RJS 17Mar99 					ComposeFakeDigitNumber(MessPtr,SLong(bearing),3);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_WINDSPEED:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (windSpeedSet == -1)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					SLong	vx,vy,vz;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					if (MMC.Sky.GetWind(windHeightSet,vx,vy,vz))
//DeadCode RJS 17Mar99 						windSpeedSet = Math_Lib.distance3d(vx,vy,vz);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				// in cm/hr...
//DeadCode RJS 17Mar99 				if (windSpeedSet > -1)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					windSpeedSet *= 360000;		//cm / hour
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					if (Save_Data.gamedifficulty [GD_UNITS])
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_RANGESKM+windSpeedSet);
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						windSpeedSet *= 2;
//DeadCode RJS 17Mar99 						windSpeedSet /= 3;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,PHRASE_RANGESIMP+windSpeedSet);
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_PERHOUR);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				windSpeedSet = -1;
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_FUELLEVEL:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->caller)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;
//DeadCode RJS 17Mar99 					ULong	fueltot = ac->weap.left.int_fuel;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 //DeadCode RJS 08Mar99 					fueltot += ac->weap.left.ext_fuel;
//DeadCode RJS 17Mar99 //DeadCode RJS 08Mar99 					fueltot += ac->weap.right.int_fuel;
//DeadCode RJS 17Mar99 //DeadCode RJS 08Mar99 					fueltot += ac->weap.right.ext_fuel;
//DeadCode RJS 17Mar99 //DeadCode RJS 08Mar99 					fueltot += ac->weap.centre.int_fuel;
//DeadCode RJS 17Mar99 //DeadCode RJS 08Mar99 					fueltot += ac->weap.centre.ext_fuel;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					fueltot = Math_Lib.rnd(100000000);
//DeadCode RJS 17Mar99 					fueltot /= 100000;	//kgs
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeDigitNumber(MessPtr,SLong(fueltot));
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_TARGDIR:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (MessPtr->FiddleROL())
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					UWord	relbearing = poobearing2;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					relbearing += phraseControl->subFactor;		//RJS 12Feb99
//DeadCode RJS 17Mar99 					relbearing /= phraseControl->divFactor;		//RJS 12Feb99
//DeadCode RJS 17Mar99 					if (!relbearing)
//DeadCode RJS 17Mar99 						relbearing = 1;
//DeadCode RJS 17Mar99 						
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,ptype+relbearing);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					poobearing2 += 8192;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_RELPOSITION:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				// split into 4 directions, with 45 degree spread -&+...
//DeadCode RJS 17Mar99 				if (MessPtr->FiddleROL())
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					UWord	relbearing = MessPtr->bearing;
//DeadCode RJS 17Mar99 					relbearing += phraseControl->subFactor;		//RJS 12Feb99
//DeadCode RJS 17Mar99 					relbearing /= phraseControl->divFactor;		//RJS 12Feb99
//DeadCode RJS 17Mar99 					if (!relbearing)
//DeadCode RJS 17Mar99 						relbearing++;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,ptype+relbearing);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_RANDOMTHINKTIME:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				RadioSampleRec*	RSamplePtr;
//DeadCode RJS 17Mar99 				int				StartOffset;
//DeadCode RJS 17Mar99 				int				SampleSize;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				RSamplePtr = LoadSample(MessPtr,PHRASE_THINKING,StartOffset,SampleSize);
//DeadCode RJS 17Mar99 				if (RSamplePtr)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					// Fiddle the sample size to vary pause length...
//DeadCode RJS 17Mar99 					SampleSize >>= 1;
//DeadCode RJS 17Mar99 					SampleSize += Math_Lib.rnd(SampleSize);
//DeadCode RJS 17Mar99 		
//DeadCode RJS 17Mar99 					MessPtr->AddSample(RSamplePtr->dataptr,StartOffset,SampleSize,PHRASE_THINKING);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_GUSTTYPE:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,poogust);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				poogust++;
//DeadCode RJS 17Mar99 				if (poogust > PHRASE_GUSTSEVERE)
//DeadCode RJS 17Mar99 					poogust = PHRASE_GUSTLIGHT;
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_THISDENTIST:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				if (Math_Lib.rnd() > 44000)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_THISIS);
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_DENTIST);
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 				else
//DeadCode RJS 17Mar99 					ComposeFakeSample(MessPtr,PHRASE_DENTISTHERE);
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			case PHRASE_AIRFIELDS:
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				ComposeFakeSample(MessPtr,ptype+pooaf);
//DeadCode RJS 17Mar99 				pooaf++;
//DeadCode RJS 17Mar99 				if (pooaf > 33)
//DeadCode RJS 17Mar99 					pooaf = 1;
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 			break;
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 		}
//DeadCode RJS 17Mar99 	}
}

static int poolocation;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayAll
//Author		Robert Slater
//Date			Mon 22 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::PlayAll()
{
//DeadCode RJS 17Mar99 	UWordP			ScriptPtr;
//DeadCode RJS 17Mar99 	ULong			noscripts;
//DeadCode RJS 17Mar99 	ULong			count;
//DeadCode RJS 17Mar99 	PhraseTables	ThePhrase;
//DeadCode RJS 17Mar99 	PhraseBuffer	fbuff;
//DeadCode RJS 17Mar99 	const			TargetIndexes	tstruc;
//DeadCode RJS 17Mar99 	CString 		thestring;
//DeadCode RJS 17Mar99 	AirStruc		caller,callee,target;
//DeadCode RJS 17Mar99 	Coords3D		tmpworld;
//DeadCode RJS 17Mar99 	int				beg[16];
//DeadCode RJS 17Mar99 	int				end[16];
//DeadCode RJS 17Mar99 	SLong			lastline[24];
//DeadCode RJS 17Mar99 	SLong			thisline[24];
//DeadCode RJS 17Mar99 	SLong			linecnt;
//DeadCode RJS 17Mar99 	SLong			lastlinecnt;
//DeadCode RJS 17Mar99 	SLong			toteq;
//DeadCode RJS 17Mar99 	SLong			i;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	//ac...
//DeadCode RJS 17Mar99 	beg[0] = SCRIPT_CALLEE_OTHERDAMAGE1LOW & 0xFFFF;
//DeadCode RJS 17Mar99 	end[0] = SCRIPT_OUTNUMBEREDINFO & 0xFFFF;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	//dentist...
//DeadCode RJS 17Mar99 	beg[1] = end[0];
//DeadCode RJS 17Mar99 	end[1] = SCRIPT_ADVISEFACFINISHEDREPLY & 0xFFFF;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	//factac...
//DeadCode RJS 17Mar99 	beg[2] = end[1];
//DeadCode RJS 17Mar99 	end[2] = SCRIPT_CALLER_GOHOME_REPLY & 0xFFFF;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	//voice2...
//DeadCode RJS 17Mar99 	beg[3] = end[2];
//DeadCode RJS 17Mar99 	end[3] = SCRIPT_CALLEE_CLEARTOFLY & 0xFFFF;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	//tower...
//DeadCode RJS 17Mar99 	beg[4] = end[3];
//DeadCode RJS 17Mar99 	end[4] = SCRIPT_DISTANCESFIDDLE & 0xFFFF;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	tmpworld.X = 0;
//DeadCode RJS 17Mar99 	tmpworld.Y = 0;
//DeadCode RJS 17Mar99 	tmpworld.Z = 0;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	caller.fly.callname = 0;
//DeadCode RJS 17Mar99 	target.fly.callname = 0;
//DeadCode RJS 17Mar99 	callee.fly.callname = 0;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	caller.fly.callnum=0;		
//DeadCode RJS 17Mar99 	target.fly.callnum=0;		
//DeadCode RJS 17Mar99 	callee.fly.callnum=0;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	caller.World = tmpworld;
//DeadCode RJS 17Mar99 	target.World = tmpworld;
//DeadCode RJS 17Mar99 	callee.World = tmpworld;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	caller.classtype = new PlaneType;
//DeadCode RJS 17Mar99 	target.classtype = new PlaneType;
//DeadCode RJS 17Mar99 	callee.classtype = new PlaneType;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	caller.classtype->phrasename = PHRASE_MIG;
//DeadCode RJS 17Mar99 	target.classtype->phrasename = PHRASE_MIG;
//DeadCode RJS 17Mar99 	callee.classtype->phrasename = PHRASE_MIG;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	caller.vel = 300;
//DeadCode RJS 17Mar99 	target.vel = 300;
//DeadCode RJS 17Mar99 	callee.vel = 300;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	RadioMessageP	MessPtr;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	ScriptPtr = GetScript(1,1,ThePhrase);	//loadit
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	noscripts = theScripts.ScriptTable[0];
//DeadCode RJS 17Mar99 	noscripts -= 0x80000000;
//DeadCode RJS 17Mar99 	noscripts /= sizeof(ULong);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	FILE*	fp;
//DeadCode RJS 17Mar99 	fp = fopen("chtscrpt.txt","wt");
//DeadCode RJS 17Mar99 	if (fp)
//DeadCode RJS 17Mar99 	{
//DeadCode RJS 17Mar99 		int	count2;
//DeadCode RJS 17Mar99 		for (count2 = 0; count2 < 5; count2++)
//DeadCode RJS 17Mar99 		{
//DeadCode RJS 17Mar99 			poolocation = 0;
//DeadCode RJS 17Mar99 			for (count=0; count < 2000; count++)
//DeadCode RJS 17Mar99 				phraseused[count] = 0;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			caller.fly.callname = 0;
//DeadCode RJS 17Mar99 			target.fly.callname = 0;
//DeadCode RJS 17Mar99 			callee.fly.callname = 0;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			caller.fly.callnum=0;		
//DeadCode RJS 17Mar99 			target.fly.callnum=0;		
//DeadCode RJS 17Mar99 			callee.fly.callnum=0;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			caller.classtype->phrasename = PHRASE_MIG;
//DeadCode RJS 17Mar99 			target.classtype->phrasename = PHRASE_MIG;
//DeadCode RJS 17Mar99 			callee.classtype->phrasename = PHRASE_MIG;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			poodistance = 25000;
//DeadCode RJS 17Mar99 			poobearing = 0;
//DeadCode RJS 17Mar99 			poogust = PHRASE_GUSTLIGHT;
//DeadCode RJS 17Mar99 			pootargtype = 1;
//DeadCode RJS 17Mar99 			pootargname = 1;
//DeadCode RJS 17Mar99 			pootargmove = 1;
//DeadCode RJS 17Mar99 			pootargweap = 1;
//DeadCode RJS 17Mar99 			poobearing2 = 0;
//DeadCode RJS 17Mar99 			poospeed = 1500;
//DeadCode RJS 17Mar99 			pooheight = 1;
//DeadCode RJS 17Mar99 			pooaf = 1;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			lastlinecnt = 0;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			for (count=beg[count2]; count < end[count2]; count++)
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				MessPtr = CreateMessage((mobileitem*)&caller,
//DeadCode RJS 17Mar99 												(mobileitem*)&target,
//DeadCode RJS 17Mar99 												(mobileitem*)&callee,
//DeadCode RJS 17Mar99 												tstruc,
//DeadCode RJS 17Mar99 												VOICE_MIN,
//DeadCode RJS 17Mar99 												&fbuff	);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (MessPtr)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					thestring = "";
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					linecnt = 0;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ScriptPtr = GetScript(count,1,ThePhrase);
//DeadCode RJS 17Mar99 					if (ScriptPtr)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						ThePhrase = (PhraseTables) *ScriptPtr;
//DeadCode RJS 17Mar99 						while (ThePhrase != PHRASE_NULL)
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							thisline[linecnt++] = ThePhrase;
//DeadCode RJS 17Mar99 							ScriptPtr++;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 							ThePhrase = (PhraseTables) *ScriptPtr;
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 						thisline[linecnt++] = ThePhrase;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					toteq = 0;
//DeadCode RJS 17Mar99 					if (linecnt == lastlinecnt)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						for (i=0; i < linecnt; i++)
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							if (thisline[i] == lastline[i])
//DeadCode RJS 17Mar99 								toteq++;
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					for (i=0; i < linecnt; i++)	(lastline[i] = thisline[i]);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					lastlinecnt = linecnt;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					if (toteq < linecnt)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						i=0;
//DeadCode RJS 17Mar99 						for (i=0; i < linecnt; i++)
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							ThePhrase = (PhraseTables) thisline[i];
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,ThePhrase);
//DeadCode RJS 17Mar99 							lastPhrase = ThePhrase;
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 						_MsgBuffer.FakePhraseToString(thestring,fbuff);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 						fprintf(fp,"%s\n",thestring);
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					delete MessPtr;
//DeadCode RJS 17Mar99 					fbuff.phrase_count = 0;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 			fprintf(fp,"\n\n........................................\n\n");
//DeadCode RJS 17Mar99 		}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 		fprintf(fp,"\n\nDentist placenames....\n\n");
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 		// Rest of the placenames...
//DeadCode RJS 17Mar99 		ULong	thescriptno = SCRIPT_PLACENAMEFIDDLE & 0xFFFF;
//DeadCode RJS 17Mar99 		ULong	nochoices = SCRIPT_PLACENAMEFIDDLE & 0xFFFF0000;
//DeadCode RJS 17Mar99 		
//DeadCode RJS 17Mar99 		nochoices >>= 16;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 		for (count=0; count < 223; count++)
//DeadCode RJS 17Mar99 		{
//DeadCode RJS 17Mar99 			if (nochoices)
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				MessPtr = CreateMessage(	(mobileitem*)&caller,
//DeadCode RJS 17Mar99 											(mobileitem*)&target,
//DeadCode RJS 17Mar99 											(mobileitem*)&callee,
//DeadCode RJS 17Mar99 											tstruc,
//DeadCode RJS 17Mar99 											VOICE_MIN,
//DeadCode RJS 17Mar99 											&fbuff	);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (MessPtr)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					thestring = "";
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ScriptPtr = GetScript(thescriptno,nochoices,ThePhrase);
//DeadCode RJS 17Mar99 					if (ScriptPtr)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						ThePhrase = (PhraseTables) *ScriptPtr;
//DeadCode RJS 17Mar99 						while (ThePhrase != PHRASE_NULL)
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,ThePhrase);
//DeadCode RJS 17Mar99 							ScriptPtr++;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 							lastPhrase = ThePhrase;
//DeadCode RJS 17Mar99 							ThePhrase = (PhraseTables) *ScriptPtr;
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,ThePhrase);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					_MsgBuffer.FakePhraseToString(thestring,fbuff);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					fprintf(fp,"%s\n",thestring);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					delete MessPtr;
//DeadCode RJS 17Mar99 					fbuff.phrase_count = 0;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 		}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 		fprintf(fp,"\n\nairfield names....\n\n");
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 		// Rest of the placenames...
//DeadCode RJS 17Mar99 		thescriptno = SCRIPT_AIRFIELDSFIDDLE & 0xFFFF;
//DeadCode RJS 17Mar99 		nochoices = SCRIPT_AIRFIELDSFIDDLE & 0xFFFF0000;
//DeadCode RJS 17Mar99 		
//DeadCode RJS 17Mar99 		nochoices >>= 16;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 		for (count=0; count < 223; count++)
//DeadCode RJS 17Mar99 		{
//DeadCode RJS 17Mar99 			if (nochoices)
//DeadCode RJS 17Mar99 			{
//DeadCode RJS 17Mar99 				MessPtr = CreateMessage(	(mobileitem*)&caller,
//DeadCode RJS 17Mar99 											(mobileitem*)&target,
//DeadCode RJS 17Mar99 											(mobileitem*)&callee,
//DeadCode RJS 17Mar99 											tstruc,
//DeadCode RJS 17Mar99 											VOICE_MIN,
//DeadCode RJS 17Mar99 											&fbuff	);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 				if (MessPtr)
//DeadCode RJS 17Mar99 				{
//DeadCode RJS 17Mar99 					thestring = "";
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					ScriptPtr = GetScript(thescriptno,nochoices,ThePhrase);
//DeadCode RJS 17Mar99 					if (ScriptPtr)
//DeadCode RJS 17Mar99 					{
//DeadCode RJS 17Mar99 						ThePhrase = (PhraseTables) *ScriptPtr;
//DeadCode RJS 17Mar99 						while (ThePhrase != PHRASE_NULL)
//DeadCode RJS 17Mar99 						{
//DeadCode RJS 17Mar99 							ComposeFakeSample(MessPtr,ThePhrase);
//DeadCode RJS 17Mar99 							ScriptPtr++;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 							lastPhrase = ThePhrase;
//DeadCode RJS 17Mar99 							ThePhrase = (PhraseTables) *ScriptPtr;
//DeadCode RJS 17Mar99 						}
//DeadCode RJS 17Mar99 					}
//DeadCode RJS 17Mar99 					else
//DeadCode RJS 17Mar99 						ComposeFakeSample(MessPtr,ThePhrase);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					_MsgBuffer.FakePhraseToString(thestring,fbuff);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					fprintf(fp,"%s\n",thestring);
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 					delete MessPtr;
//DeadCode RJS 17Mar99 					fbuff.phrase_count = 0;
//DeadCode RJS 17Mar99 				}
//DeadCode RJS 17Mar99 			}
//DeadCode RJS 17Mar99 		}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 		fclose(fp);
//DeadCode RJS 17Mar99 	}
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	delete caller.classtype;
//DeadCode RJS 17Mar99 	delete target.classtype;
//DeadCode RJS 17Mar99 	delete callee.classtype;
//DeadCode RJS 17Mar99 
//DeadCode RJS 17Mar99 	caller.classtype = NULL;
//DeadCode RJS 17Mar99 	target.classtype = NULL;
//DeadCode RJS 17Mar99 	callee.classtype = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFakePlaceName
//Author		Robert Slater
//Date			Thu 25 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SectorNameP	RadioChatter::GetFakePlaceName()
{
	SectorNameP	RealNamePtr = NULL;
	SectorNameP	NamePtr = NULL;

//DEADCODE MS 02/05/99 	if (LoadSectorNames(FIL_RCHAT_NAMEGRID))
//DEADCODE MS 02/05/99 	{
//DEADCODE MS 02/05/99 		while (poolocation < theSectors.noelements)
//DEADCODE MS 02/05/99 		{
//DEADCODE MS 02/05/99 			poolocation++;
//DEADCODE MS 02/05/99 			NamePtr = &theSectors.PlaceNames[poolocation];
//DEADCODE MS 02/05/99 			if (NamePtr->prefix || NamePtr->name)
//DEADCODE MS 02/05/99 			{
//DEADCODE MS 02/05/99 				if (NamePtr->name <= PHRASE_YUKTAE_DONG_COAST)
//DEADCODE MS 02/05/99 				{
//DEADCODE MS 02/05/99 					ULong	thename = PhraseToResource(NamePtr->name) - PhraseToResource(0);
//DEADCODE MS 02/05/99 					if (!phraseused[thename])
//DEADCODE MS 02/05/99 					{
//DEADCODE MS 02/05/99 						RealNamePtr = NamePtr;
//DEADCODE MS 02/05/99 						break;
//DEADCODE MS 02/05/99 					}
//DEADCODE MS 02/05/99 				}
//DEADCODE MS 02/05/99 			}
//DEADCODE MS 02/05/99 		}
//DEADCODE MS 02/05/99 	}
//DEADCODE MS 02/05/99 
#pragma message ("GetFakePlaceName has noexistant phrase")
//DeadCode PD 04May99 	SectorNameP	RealNamePtr = NULL;
//DeadCode PD 04May99 	SectorNameP	NamePtr = NULL;
//DeadCode PD 04May99 
//DeadCode PD 04May99 	if (LoadSectorNames(FIL_RCHAT_NAMEGRID))
//DeadCode PD 04May99 	{
//DeadCode PD 04May99 		while (poolocation < theSectors.noelements)
//DeadCode PD 04May99 		{
//DeadCode PD 04May99 			poolocation++;
//DeadCode PD 04May99 			NamePtr = &theSectors.PlaceNames[poolocation];
//DeadCode PD 04May99 			if (NamePtr->prefix || NamePtr->name)
//DeadCode PD 04May99 			{
//DeadCode PD 04May99 #pragma message ("GetFakePlaceName has noexistant phrase")
//DeadCode PD 04May99 /*				if (NamePtr->name <= PHRASE_YUKTAE_DONG_COAST)
//DeadCode PD 04May99 				{
//DeadCode PD 04May99 					ULong	thename = PhraseToResource(NamePtr->name) - PhraseToResource(0);
//DeadCode PD 04May99 					if (!phraseused[thename])
//DeadCode PD 04May99 					{
//DeadCode PD 04May99 						RealNamePtr = NamePtr;
//DeadCode PD 04May99 						break;
//DeadCode PD 04May99 					}
//DeadCode PD 04May99 				}
//DeadCode PD 04May99 */
//DeadCode PD 04May99 			}
//DeadCode PD 04May99 		}
//DeadCode PD 04May99 	}
	return(RealNamePtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseScript
//Author		Robert Slater
//Date			Thu 4 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MESSAGE_STRUC::ChooseScript(int	sno)
{
	ULong	nochoices = sno & 0xFFFF0000;
	if (nochoices)
	{
		ULong	randchoice = nochoices>>16;						//RJS 17Mar99
		ULong	normrand = randchoice & 0x00FF;					//RJS 17Mar99
		ULong	topflag = 65536;
																//RJS 17Mar99
		sno &= 0xFFFF;											//RJS 17Mar99
		if (randchoice & 0xFF00)								//RJS 17Mar99
		{														//RJS 17Mar99
			ULong	excitedoffset = normrand;					//RJS 17May99
		 	randchoice >>= 8;									//RJS 17Mar99

			if (normrand)
			{
				// can we do range check?
				if (target && callee)
				{
					SLong	dx,dy,dz,distance;
	
					dx = target->World.X - callee->World.X;
					dy = target->World.Y - callee->World.Y;
					dz = target->World.Z - callee->World.Z;

					distance = Math_Lib.distance3d(dx,dy,dz);
					if (distance <= 250000)	//cms
					{
						normrand = 0;
						voxstate = VOXSTATE_EXCITED;
					}
					else
					{
						randchoice = 0;
						voxstate = VOXSTATE_NORMAL;
					}
				}
				else
				{
					randchoice = 0;
					voxstate = VOXSTATE_NORMAL;					//RJS 18Mar99
				}
			}
			else
			{
				normrand = 0;
				voxstate = VOXSTATE_EXCITED;
			}

			if (randchoice > 1)									//RJS 17Mar99
			{
				sno += excitedoffset;							//RJS 17May99
				sno += Math_Lib.rnd(randchoice);				//RJS 17Mar99
				sno += 65537;									//RJS 17Mar99
				topflag = 0;
			}
		}														//RJS 17Mar99
		else													//RJS 17Mar99
			voxstate = VOXSTATE_NORMAL;							//RJS 17Mar99
																//RJS 17Mar99
		if (normrand > 1)										//RJS 17Mar99
		{														//RJS 17Mar99
			sno += Math_Lib.rnd(normrand);						//RJS 17Mar99
			sno += 65537;										//RJS 17Mar99
		}
		else
			sno += topflag;						//RJS 01Apr99
	}

	scriptno = sno;

#ifndef	NDEBUG
	_Radio.totmess++;
	messagecnt = _Radio.totmess;										//JIM 29Apr99
#endif

	randomno = Math_Lib.rnd();
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StripIsPlayer
//Author		Robert Slater
//Date			Mon 12 Apr 1999
//
//Description	removes any callsign from script, if it is the 1st phrase
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::StripIsPlayer(UWordP &ScriptPtr)
{
	thePhrase = (PhraseTables) *ScriptPtr;						//RJS 11May99
	while (thePhrase != PHRASE_NULL)
	{
		//Assume there is a bandwidth for this...
		if ((thePhrase >= PHRASE_CALLER) && (thePhrase <= PHRASE_CALLEE))
		{
			DodgyRandomFix();									//RJS 11May99
			ScriptPtr++;
		}
		else
		{
			if (((ULong)thePhrase & 0xFF00) == PHRASE_PUNCTUATION)
				ScriptPtr++;
			else
				break;
		}

		thePhrase = (PhraseTables) *ScriptPtr;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StripCaller
//Author		Robert Slater
//Date			Mon 12 Apr 1999
//
//Description	Just removes caller from script, if it is the 1st phrase
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::StripCaller(UWordP &ScriptPtr)
{
	thePhrase = (PhraseTables) *ScriptPtr;						//RJS 11May99
	while (thePhrase != PHRASE_NULL)
	{
		//Assume there is a bandwidth for this...
		if ((thePhrase >= PHRASE_CALLER) && (thePhrase < PHRASE_CALLEE))
		{
			DodgyRandomFix();									//RJS 11May99
			ScriptPtr++;
		}
		else
		{
			if (((ULong)thePhrase & 0xFF00) == PHRASE_PUNCTUATION)
				ScriptPtr++;
			else
				break;
		}

		thePhrase = (PhraseTables) *ScriptPtr;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Enter3D
//Author		R. Hyde 
//Date			Wed 28 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Enter3D()
{
	RootMessPtr = NULL;

 	MessageCount = 0;

	timesincelast = 0;
	timesincestart = 0;

	windHeightSet = 0;
	windSpeedSet = -1;		
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Random
//Author		R. Hyde 
//Date			Tue 4 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		RADIOMESSAGE::Random(int	numbits)
{
	int	retval = masterrandom & ((1<<numbits)-1);

	masterrandom >>= numbits;

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MainStrip
//Author		Robert Slater
//Date			Tue 11 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::MainStrip(UWordP&	ptr)
{
	if (	(caller == callee) 
		&&	(theVoice == VOICE_PLAYER)	)
		StripIsPlayer(ptr);						 
	else										 
	{											 
		if (!isAudio)					 
		{
			if (theVoice == VOICE_PLAYER)
				StripIsPlayer(ptr);
			else
				StripCaller(ptr);
		}
	}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DodgyRandomFix
//Author		Robert Slater
//Date			Tue 11 May 1999
//
//Description	This is to ensure that the random seed remains in sync,
//				even when caller/callee phrases are stripped from the
//				message bar.
//
//				Must perform same Random tests as in ComposeSample()
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::DodgyRandomFix()
{
	switch (thePhrase)
	{
	case PHRASE_CALLERSTOP:
	case PHRASE_THISCALLER:
	case PHRASE_CALLER:
	{
		if (caller)
		{
			Bool		fixlater = FALSE;
			AirStrucPtr	ac = (AirStrucPtr) caller;
			if (ac->fly.callname)
			{
				if (thePhrase == PHRASE_THISCALLER)
				{
					if (Random(2))
						fixlater = TRUE;
				}

				if ((ac->fly.callnum == 1) && !fixlater && (ac->fly.callname < Call_FAC0))
					Random(1);
			}
		}
	}
	break;
	case PHRASE_CALLEE:
		if (callee)
		{
			AirStrucPtr	ac = (AirStrucPtr) callee;
			if ((ac->fly.callname) && (ac->fly.callnum == 1) && (ac->fly.callname < Call_FAC0))
				Random(2);
		}
	break;
	case PHRASE_THISDENTIST:
		Random(2);
	break;
	case PHRASE_GERMANCALLERSTOP:
	case PHRASE_GERMANTHISCALLER:
	case PHRASE_GERMANCALLER:
	{
		if (caller)
		{
			Bool		fixlater = FALSE;
			AirStrucPtr	ac = (AirStrucPtr) caller;
			if (ac->fly.callname)
			{
				if (thePhrase == PHRASE_GERMANTHISCALLER)
				{
					if (Random(2))
						fixlater = TRUE;
				}

//DeadCode RJS 15Jun99 				if ((ac->fly.callnum == 1) && !fixlater && (ac->fly.callname < Call_FAC0))
//DeadCode RJS 15Jun99 					Random(1);
			}
		}
	}
	break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearMessages
//Author		Robert Slater
//Date			Mon 31 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ClearMessages(MsgType	messagetype)
{
	_MsgBuffer.ClearMessagesMsg(messagetype);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MsgInQ
//Author		Robert Slater
//Date			Mon 31 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		RadioChatter::MsgInQ()
{
	return _MsgBuffer.noBufferedMessages;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearMessages
//Author		Robert Slater
//Date			Thu 3 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ClearMessages(MsgPriority	priority)
{
	_MsgBuffer.ClearMessagesPri(priority);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearMessages
//Author		Robert Slater
//Date			Mon 14 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ClearMessages(MsgType	messagetype, ItemPtr	theTarget)
{
	_MsgBuffer.ClearMessagesMsg(messagetype,theTarget);
}
