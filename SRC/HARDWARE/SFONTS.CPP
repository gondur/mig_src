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
//Filename       sfonts.cpp
//System         
//Author         Robert Slater
//Date           Fri 3 Jul 1998
//Description    
//------------------------------------------------------------------------------
#include 	"dosdefs.h"
#define 	F_GRAFIX
#include	<stdio.h>
#include	<string.h>
#include	"mssw.h"
#include	"files.g"
#include	"fileman.h"
#include	"sndfonts.h"

SndFonts	_SndFonts;

SndFonts::SndFonts()
{
	bIsMIDIPlaying = FALSE;
	bIsUserBankLoaded = FALSE;
	bCalledAlready = FALSE;
	numSFDevs = 0;
	wMCIDeviceID = 0;
	dwAvailableMemBest = 0;
	BestsfIdx = NO_INDEX;
	hSFMANDLL = 0; 
	lpSFManager = 0;
 	lpSFL1API = 0;
	theBank = 1;
	thePreset = 0;
 
	hMIDIOutInteractive = NULL;
	SFontSet = FALSE;

	bMMSystemOnly = FALSE; 
	bRouteDialog = FALSE;
	
	lastDev=NO_DEVID;
}

SndFonts::~SndFonts()
{
	hMIDIOutInteractive = NULL;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SF_SendRouterCommand
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool SndFonts::SF_SendRouterCommand(ULong sfRouterID, CSFRouterData *pRoute)
{
	char 	sfRouteCommand[20], Text[200];
	ULong 	bufLength = 0;
	UWord	numDevs=0;
	MIDIHDR	sysExMessage;
	SWord	status;
	Bool	bOK=TRUE;

	if (hMIDIOutInteractive) 
	{
		if (pRoute == NULL) 
		{ 
			if (lastDev != NO_DEVID)
				pRoute = &last;
			else
				return FALSE;
		}   
		else
		{
			last = *pRoute;
			lastDev = sfRouterID;
		}

		sfRouteCommand[0]  = (BYTE) 0xF0;
		sfRouteCommand[1]  = (BYTE) 0x00;
		sfRouteCommand[2]  = (BYTE) 0x20;
		sfRouteCommand[3]  = (BYTE) 0x21;
		sfRouteCommand[4]  = (BYTE) 0x5F;
		sfRouteCommand[5]  = (BYTE) 0x00;  // 0 or 127
		sfRouteCommand[6]  = pRoute->m_RouterCommand;
		switch(pRoute->m_RouterCommand)
		{
		case SFROUTER_RESET_ALL_ROUTINGS:
			sfRouteCommand[7] = (BYTE)0xF7; 
			bufLength = 8;
			break;
		case SFROUTER_ROUTE_ALL_CHANS_TO_DEV:
			bufLength = 12; 
			SFMAN_GET_ROUTING_INDEX(sfRouterID, sfRouteCommand[7], sfRouteCommand[8], sfRouteCommand[9], sfRouteCommand[10]);
			sfRouteCommand[11] = (BYTE) 0xF7;
			break;
		case SFROUTER_ROUTE_BANKPRG_TO_DEV_BANKPRG:
			sfRouteCommand[7]  = 0;
			sfRouteCommand[8]  = (BYTE)pRoute->m_SourceLocation.m_BankIndex;
			sfRouteCommand[9]  = 0;
			sfRouteCommand[10]  = (BYTE)pRoute->m_SourceLocation.m_PresetIndex;
			SFMAN_GET_ROUTING_INDEX(sfRouterID, sfRouteCommand[11], sfRouteCommand[12], sfRouteCommand[13], sfRouteCommand[14]);
			sfRouteCommand[15] = (BYTE)pRoute->m_TargetLocation.m_BankIndex;
			sfRouteCommand[16] = 0;
			sfRouteCommand[17] = (BYTE)pRoute->m_TargetLocation.m_PresetIndex;
			sfRouteCommand[18] = (BYTE) 0xF7;
			bufLength = 19;
			break;
		case SFROUTER_ROUTE_CHAN_TO_DEV:
			sfRouteCommand[7] = (BYTE)pRoute->m_Channel;
			SFMAN_GET_ROUTING_INDEX(sfRouterID, sfRouteCommand[8], sfRouteCommand[9], sfRouteCommand[10], sfRouteCommand[11]);
			sfRouteCommand[12] = (BYTE)0xF7;
			bufLength = 13;
			break;
		default:
			return FALSE;
		}

		memset ( &sysExMessage , 0, sizeof(MIDIHDR) ) ;
		sysExMessage.lpData = (char*) sfRouteCommand ;
    	sysExMessage.dwBufferLength = bufLength ;

		if (midiOutPrepareHeader( hMIDIOutInteractive, &sysExMessage, sizeof(MIDIHDR)) == 0)
		{
			if (midiOutLongMsg ( hMIDIOutInteractive, &sysExMessage, sizeof(MIDIHDR)) != 0)
				bOK = FALSE;
		}
		else
			bOK = FALSE;
	}

	return bOK; 
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSFDLL
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description	
//
//	This function loads the SF Manager DLL, and then queries all the SoundFont devices in 
//	the system. Each device is given a rating (see #define statements above for details),
// 	and the device with the best rating is opened. A router command to route all MIDI data  
// 	to this device is then sent.
//
// 	Pass TRUE to this function to do the above and
// 	Pass FALSE to close the SF device, and unload the SF Manager library.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool SndFonts::InitSFDLL(Bool bStartUp)
{
    UWord	count,done;
	ULong	dwMaxMem,dwAvailableMemCurrent;
	UByte	Rating[MAXNUMDEVICES] = {0};
	LRESULT dwErr;
	CSFMIDILocation midiLoc;
	CSFCapsObject sfCaps;
	char	String[60];
	ULong	dwRouterID;
	UByte	sfRouterCommand[12] = {0xf0, 0x00, 0x20, 0x21, 0x5f, 0x00, 0x00, 
							    0x00, 0x00, 0x00, 0x00, 0xf7};
	MIDIHDR sysExMessage;
	Bool	retval = TRUE;

	if (bStartUp == TRUE)
	{
		// Load the SoundFont Master Manager

		hSFMANDLL = LoadLibrary (SF_MASTER_MANAGER_FILENAME);
		if (hSFMANDLL == NULL )
		{
//			MessageBox(NULL, "Error loading SoundFont Manager", "Error", MB_OK) ;
			return FALSE;
		}
		
		// Get the address of the SoundFont manager function table
        lpSFManager = (PSFMANAGER)GetProcAddress((HINSTANCE__*)hSFMANDLL, SF_FUNCTION_TABLE_NAME);
		if  (lpSFManager == NULL) 
		{
			FreeLibrary((HINSTANCE__*)hSFMANDLL);
//			MessageBox(NULL, "Error getting SFMAN function table", "Error", MB_OK) ;
			return FALSE;
		}
 
 		// Use SF_QueryInterface to get access to the appropriate function table
        if ((dwErr = lpSFManager->SF_QueryInterface(ID_SFMANL101API,(ULong*)&lpSFL1API))!=0)
        {
			FreeLibrary((HINSTANCE__*)hSFMANDLL);
//			MessageBox(NULL,"Failed to Query Interface","Error !",MB_OK);
             return FALSE ;
        }
 
		// Get the number of SoundFont compatible devices in system
        lpSFL1API->SF_GetNumDevs(&numSFDevs);
 		if (numSFDevs != 0)
 		{
 			// For each SF compatible device, query the caps, and assign a
 			// rating to it.
 
 			for (count=0; count<numSFDevs; count++) 
 			{
 				// Get current device capabilities
 				memset(&sfCaps, 0, sizeof(CSFCapsObject));
 				sfCaps.m_SizeOf = sizeof(sfCaps);
             	lpSFL1API->SF_GetDevCaps(count,&sfCaps);
 
 				// Does this device have a Hardware synthesiser ?
 				if ((sfCaps.m_DevCaps & SFMANCAP_SOFTWARE_SYNTH_CAP) == 0)
 				{
 					// Yes, device has a hardware synthesier ...
 					// Does this device use hardware memory?
 					if ((sfCaps.m_DevCaps & SFMANCAP_DYNAMIC_MEM_CAP) == 0)
 					{
 						// Yes, device has hardware memory ...
						// Open the device so that the amount of memory can be queried
 				    	lpSFL1API->SF_Open(count);
 					
 						// Query the amount of memory available for this device
 						lpSFL1API->SF_QueryStaticSampleMemorySize(count,&dwMaxMem, 
 								                              	&dwAvailableMemCurrent);
 
 						Rating[count]=(BYTE)(dwAvailableMemCurrent/HWMemBlock);
 						Rating[count]+=HWSynthHWMem;
 
 						// If hardware RAM size is less than HWMemBlock, then do not use this
 						// device. (This caters for unexpanded SB32 cards which have no memory)
 						if (Rating[count]==HWSynthHWMem)
 							Rating[count]=0;
 
 						lpSFL1API->SF_Close(count);
 					}
 					else
 						Rating[count]=(BYTE)HWSynthSysMem;	// No, device uses system memory
 				}
 				else
 					Rating[count]=SWSynthSysMem;	//No, device has a software synthesier ...
 			}
 
 			// Choose best device and try to open it, if it fails then find next best device
 			// and open that and so on ...
 			done = numSFDevs;
 			while (done>0)
 			{
 				BestsfIdx = 0;
 				done--;
 
 				// Search through the other devices, for one with a higher rating
 				for (count = 1; count<numSFDevs; count++)
 				{
 					if (Rating[count] > Rating[BestsfIdx])
 						BestsfIdx = count;
 				}
 			
 				// Found best device - now try to open it 
 				if (lpSFL1API->SF_Open(BestsfIdx) != SFERR_NOERR)
 					Rating[BestsfIdx]=0;
 				else
 					done=0;
 			}
 
 			if (Rating[BestsfIdx] == 0)
 			{
 				// Failed to open any devices
 				FreeLibrary((HINSTANCE__*)hSFMANDLL);
 				return FALSE;
 			}
 		
 			// Query and capabilities of the best device, and set dwAvailableMemBest to the amount
 			// of RAM available.
 			memset(&sfCaps, 0, sizeof(CSFCapsObject));
 			sfCaps.m_SizeOf = sizeof(sfCaps);
         	lpSFL1API->SF_GetDevCaps(BestsfIdx,&sfCaps);
 			if ((sfCaps.m_DevCaps & SFMANCAP_DYNAMIC_MEM_CAP) == 0)
 				lpSFL1API->SF_QueryStaticSampleMemorySize(BestsfIdx,&dwMaxMem,&dwAvailableMemBest);
 			else
 				dwAvailableMemBest=0xFFFFFFFF;
 
 			// Need to find the Router ID associated with this device
 			lpSFL1API->SF_GetRouterID(BestsfIdx, &dwRouterID);
 		
 			// Call macro to obtain routing index
 			SFMAN_GET_ROUTING_INDEX(dwRouterID, sfRouterCommand[7], sfRouterCommand[8], 
 			                                	sfRouterCommand[9], sfRouterCommand[10]);
 	
 			memset(&sysExMessage, 0, sizeof(MIDIHDR));
 			sysExMessage.lpData = (char*) sfRouterCommand;
 			sysExMessage.dwBufferLength = 12;
 	
 			if (midiOutPrepareHeader(hMIDIOutInteractive, &sysExMessage, sizeof(MIDIHDR)) ==0 ) 
			{
	 			if (midiOutLongMsg(hMIDIOutInteractive, &sysExMessage, sizeof(MIDIHDR)) ==0 )
		 			SFontSet = TRUE;
				else
 					retval = FALSE;
			}
			else
				retval = FALSE;
 		}
 		else
 			retval = FALSE;
 	}
	else
	{
	    // Close down the SoundFont compatible device.
		SFontSet = FALSE;

        if ((lpSFL1API != NULL) && (numSFDevs != 0))
		{
			ClearBank();
 			
 			lpSFL1API->SF_Close(BestsfIdx);
 			FreeLibrary ((HINSTANCE__*) hSFMANDLL );

			lpSFL1API = NULL;
			numSFDevs = 0;
		}
    }
	
    return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearSFRoute
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	SndFonts::ClearSFRoute()
{
	CSFRouterData route;

	// Clear route structure
	memset(&route, 0, sizeof(CSFRouterData));
	
	route.m_RouterCommand = SFROUTER_RESET_ALL_ROUTINGS;

	SF_SendRouterCommand(0, &route);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSFont
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	SndFonts::InitSFont(LPHMIDIOUT mdi)
{
	if (!SFontSet)
	{
		hMIDIOutInteractive = *mdi;

		ClearSFRoute();

		SFontSet = InitSFDLL(TRUE);
	}

	return(SFontSet);

//	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillSFont
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	SndFonts::KillSFont()
{
	if (SFontSet)
		InitSFDLL(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearBank
//Author		Robert Slater
//Date			Mon 6 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	SndFonts::ClearBank()
{
	CSFBufferObject	obj;
	CSFMIDILocation midiLoc;
	LRESULT			dwErr;
	UWord			bankIndex;
	SWord			i;
	char			buffer[80];
	Bool			retval = FALSE;

	obj.m_Size = 80;
	obj.m_Buffer = buffer;
    obj.m_Flag = 0;

	midiLoc.m_PresetIndex = 0;

	bankIndex = theBank;
	dwErr = lpSFL1API->SF_IsMIDIBankUsed(BestsfIdx, &bankIndex);
	if (bankIndex >= 0) 
	{
		buffer[0]=0;
		obj.m_SizeUsed = 1; 
		midiLoc.m_BankIndex = theBank;

		lpSFL1API->SF_GetLoadedBankDescriptor(BestsfIdx, &midiLoc, &obj);
		if ((obj.m_SizeUsed > 1) || (buffer[0] != 0))
		{
			dwErr = lpSFL1API->SF_ClearLoadedBank(BestsfIdx, &midiLoc);
			if (dwErr == SFERR_NOERR)
			{
				// ok...
				theBank = 1;
				thePreset = 0;
			}
		}
	}

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSoundFont
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	SndFonts::LoadSoundFont(LPHMIDIOUT mdi,FileNum	thefile,UByte	bankno, UByte  patchno)
{
	Bool	retval = FALSE;

	if (InitSFont(mdi))
	{
		// Test to see if sound font will fit onto the card's memory...
		if (dwAvailableMemBest)
		{
			CSFBufferObject	obj;
			CSFMIDILocation midiLoc;
			char			filename[128];
			LRESULT			dwErr;

			strcpy(filename,FILEMAN.namenumberedfile(thefile));

			theBank = bankno;
			thePreset = patchno;

			// Load up appropriate SoundFont
			midiLoc.m_BankIndex = theBank;
			midiLoc.m_PresetIndex = thePreset;
			obj.m_Size = 128;
			obj.m_Flag = SFFLAG_OPER_FILE;
			obj.m_Buffer = filename;

			dwErr = lpSFL1API->SF_LoadBank(BestsfIdx, &midiLoc, &obj);

 			if (dwErr == SFERR_NOERR)
 				retval = TRUE;
			else
				KillSFont();
		}			
	}

	return (retval);
}

