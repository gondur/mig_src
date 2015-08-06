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

//DEADCODE DAW 28/03/99 //Filename       persons.cpp
//DEADCODE DAW 28/03/99 //System         
//DEADCODE DAW 28/03/99 //Author         Jim Taylor
//DEADCODE DAW 28/03/99 //Date           Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //Description    New 'persons' to process new battlefield format.
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 #ifndef	SOURCE
//DEADCODE DAW 28/03/99 #define	SOURCE
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	#include	"dosdefs.h"
//DEADCODE DAW 28/03/99 	#include	"myerror.h"
//DEADCODE DAW 28/03/99 	#include	"bfcommon.h"
//DEADCODE DAW 28/03/99 //#include	"viewsel.h"
//DEADCODE DAW 28/03/99 #include	"makebf.cc"
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 //DeadCode JIM 25Jul96 #include	"landscap.h"									//PD 15Mar96
//DEADCODE DAW 28/03/99 //DeadCode JIM 25Jul96 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 //DeadCode JIM 25Jul96 #include	"savegame.h"										//RDH 17Jun96
//DEADCODE DAW 28/03/99 //DeadCode JIM 25Jul96 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 //DeadCode JIM 25Jul96 #include	"time.h"										//RDH 17Jun96
//DEADCODE DAW 28/03/99 //DeadCode JIM 25Jul96 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 //DeadCode JIM 25Jul96 #include	"text.h"										//RDH 17Jun96
//DEADCODE DAW 28/03/99 //DeadCode JIM 25Jul96 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 //DeadCode JIM 05Jun96 	#include	"UniqueID.g"
//DEADCODE DAW 28/03/99 //DeadCode JIM 25Jul96 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //DeadCode JIM 28Mar96 extern	PlaneType&	camel;										//RDH 23Feb96
//DEADCODE DAW 28/03/99 //Old_Code PD 27Aug96  	MAKEFIELD	(ShapeNum,ShapeNumMIN,ShapeNumMAX);
//DEADCODE DAW 28/03/99 //	Persons2	Persons_2;
//DEADCODE DAW 28/03/99 	extern	ULong	GR_FriendlyScoutType00;
//DEADCODE DAW 28/03/99 	extern	ULong	GR_GlobalSkillMin;
//DEADCODE DAW 28/03/99 	extern	ULong	GR_GlobalSkillMax;
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 EventRec*	EventRec::eventbase=NULL;
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 SLong
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 		p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 		p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 		p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 		*globallocations[]={
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 							&p0,&p1,&p2,&p3,&p4,&p5,&p6,&p7,&p8,&p9,
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 							&p10,&p11,&p12,&p13,&p14,&p15,&p16,&p17,&p18,&p19,
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 							&p20,&p21,&p22,&p23,&p24,&p25,&p26,&p27,&p28,&p29,
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 								NULL};
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //extern	ViewPoint* View_Point;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 inline Bool operator==(const UniqueID uid1,const UniqueID uid2)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 //	_asm {int 3};
//DEADCODE DAW 28/03/99 	return (Bool)((int)(uid1&IllegalSepID)==(int)(uid2&IllegalSepID));
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 inline Bool operator!=(const UniqueID uid1,const UniqueID uid2)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 //	_asm {int 3};
//DEADCODE DAW 28/03/99 	return (Bool)((int)(uid1&IllegalSepID)!=(int)(uid2&IllegalSepID));
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 typedef void (*ha)(AirStrucPtr,FormationIndex,UByte* colours);
//DEADCODE DAW 28/03/99 ha	Persons2::Colour_Rule_List[]
//DEADCODE DAW 28/03/99 		={
//DEADCODE DAW 28/03/99 			&Persons2::ColourRulePlayerSquadron,
//DEADCODE DAW 28/03/99 			&Persons2::ColourRulePlayerAuto,
//DEADCODE DAW 28/03/99 			&Persons2::ColourRulePaintShop,
//DEADCODE DAW 28/03/99 			&Persons2::ColourRuleAllRandom,
//DEADCODE DAW 28/03/99 			&Persons2::ColourRuleDefined,
//DEADCODE DAW 28/03/99 		};
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 UniqueIDBand	Persons2::uidbandbase[UIDTABLESIZE]= {
//DEADCODE DAW 28/03/99 							PilotedAcBAND, WayPointBAND, RedGroundMobileBAND,
//DEADCODE DAW 28/03/99 							BlueGroundMobileBAND, MissileBAND, RedAcBAND,
//DEADCODE DAW 28/03/99 							BlueAcBAND, RedCivilianBAND, BlueCivilianBAND,
//DEADCODE DAW 28/03/99 							GreenCivilianBAND, RedVetoedBAND, BlueVetoedBAND,
//DEADCODE DAW 28/03/99 							LandscapeBAND, RedMilitaryBAND, BlueMilitaryBAND,
//DEADCODE DAW 28/03/99 							RedAirfieldBAND, BlueAirfieldBAND, RedPortBAND,
//DEADCODE DAW 28/03/99 							BLuePortBAND, RedCCCBAND, BlueCCCBAND, RedGICBAND,
//DEADCODE DAW 28/03/99 							BlueGICBAND, RedAAASiteBAND, BlueAAASiteBAND,
//DEADCODE DAW 28/03/99 							RedSAMBAND, BlueSAMBAND, IllegalBAND };
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 UniqueID		Persons2::uidbandmax[UIDTABLESIZE];
//DEADCODE DAW 28/03/99 UniqueID		Persons2::uidbandmin[UIDTABLESIZE];
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //ItemBasePtr		Persons2::pItem[PITEMTABLESIZE];
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //DeadCode RJS 13Feb96 enum	UILogType
//DEADCODE DAW 28/03/99 //DeadCode RJS 13Feb96 {
//DEADCODE DAW 28/03/99 //DeadCode RJS 13Feb96 	ptrcopy			= 1,
//DEADCODE DAW 28/03/99 //DeadCode RJS 13Feb96 	worldcopy		= 2,
//DEADCODE DAW 28/03/99 //DeadCode RJS 13Feb96 	addworldcopy	= 3
//DEADCODE DAW 28/03/99 //DeadCode RJS 13Feb96 };
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 CON	Persons2::Persons2(WorldStuff* world,ViewPoint* vp)	
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	viewpoint=vp;
//DEADCODE DAW 28/03/99 	eventloglist=NULL;
//DEADCODE DAW 28/03/99 	myworld=world;	
//DEADCODE DAW 28/03/99 	pItem=world->pItem;
//DEADCODE DAW 28/03/99 	rootuidnode = NULL;
//DEADCODE DAW 28/03/99 	permtextpage=(TextPage)0;
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		InitSetPiece
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 18 Jun 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void Persons2::InitSetPiece()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	while (eventloglist)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		EventLogPtr	tmp=eventloglist;
//DEADCODE DAW 28/03/99 		eventloglist=tmp->next;
//DEADCODE DAW 28/03/99 		delete tmp;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	ClrMessage(UserMsg::NOMSG);									//JIM 23Oct96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	mobileitem::MobileList=NULL;
//DEADCODE DAW 28/03/99 	mobileitem::ACList=NULL;
//DEADCODE DAW 28/03/99 	TransientItem::TransientList=NULL;							//PD 11May96
//DEADCODE DAW 28/03/99 	Art_Int.CleanUp();
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	int count=0;
//DEADCODE DAW 28/03/99 	uidbandmax[count] =(UniqueID)(uidbandbase[count+1]-1);
//DEADCODE DAW 28/03/99 	uidbandmin[count] = (UniqueID)uidbandbase[count];
//DEADCODE DAW 28/03/99 	for (count = 1; count < UIDTABLESIZE-1; count++)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		uidbandmax[count] = uidbandbase[count+1]?(UniqueID)(uidbandbase[count+1]-1):(UniqueID)IllegalBAND;
//DEADCODE DAW 28/03/99 		if (uidbandbase[count])
//DEADCODE DAW 28/03/99 			uidbandmin[count] = (UniqueID)uidbandbase[count];
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			uidbandbase[count]=IllegalBAND;
//DEADCODE DAW 28/03/99 			uidbandmin[count] =(UniqueID)IllegalBAND;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	uidbandmax[count] =(UniqueID)IllegalBAND;
//DEADCODE DAW 28/03/99 	if (uidbandbase[count])
//DEADCODE DAW 28/03/99 		uidbandmin[count] = (UniqueID)uidbandbase[count];
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		uidbandbase[count]=IllegalBAND;
//DEADCODE DAW 28/03/99 		uidbandmin[count] =(UniqueID)IllegalBAND;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	uidbandmax[UIDTABLESIZE-1] =
//DEADCODE DAW 28/03/99 		uidbandmin[UIDTABLESIZE-1] = (UniqueID)uidbandbase[UIDTABLESIZE-1];
//DEADCODE DAW 28/03/99 	for (count = 0; count < myworld->PITEMTABLESIZE; count++)
//DEADCODE DAW 28/03/99 		pItem[count] = NULL;
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		LoadSetPiece
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void Persons2::LoadSetPiece(WorldStuff *worldptr, FileNum filenumber)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 	SendInitPacket ();											//ARM 09Aug96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	InitSetPiece();
//DEADCODE DAW 28/03/99 	LoadSubPiece(worldptr,filenumber);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (anyoutstanding())
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Unresolved UIDS! One is: %x",rootuidnode->uidattack);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		LoadSetPiece
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void Persons2::LoadSetPiece(WorldStuff *worldptr, FileNum *filelist)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 	SendInitPacket ();											//ARM 09Aug96
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 	InitSetPiece();
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 	while (*filelist!=INVALIDFILENUM)
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 		LoadSubPiece(worldptr,filelist++_);
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 	if (anyoutstanding())
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 		_Error.EmitSysErr("Unresolved UIDS! One is: %x",rootuidnode->uidattack);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		LoadSetPiece
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Load battlefields as fed by FindNextBf
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void Persons2::LoadSetPiece(WorldStuff *worldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	TruckLog=TargLog=NULL;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	SendInitPacket ();											//ARM 18Sep96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	InitSetPiece();
//DEADCODE DAW 28/03/99 	BattlefieldType	bfctrl=MAINWORLDBF;
//DEADCODE DAW 28/03/99 	FileNum	filelist;
//DEADCODE DAW 28/03/99 	do
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		filelist = FindCommsNextBf (bfctrl);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 		filelist=FindNextBf(bfctrl);
//DEADCODE DAW 28/03/99 		if (filelist)
//DEADCODE DAW 28/03/99 			LoadSubPiece(worldptr,filelist);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	while (bfctrl!=FINISHBF);
//DEADCODE DAW 28/03/99 	if (anyoutstanding())
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Unresolved UIDS! One is: %x",rootuidnode->uidattack);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		FindCommsNextBf
//DEADCODE DAW 28/03/99 //Author		Andrew McRae
//DEADCODE DAW 28/03/99 //Date			Fri 27 Sep 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 FileNum Persons2::FindCommsNextBf (BattlefieldType& bfctrl)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	FileNum filelist;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	char* BFieldPacket;
//DEADCODE DAW 28/03/99 	char* ptr;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	ULong n;
//DEADCODE DAW 28/03/99 	int val;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	char RecPacket [512];
//DEADCODE DAW 28/03/99 	ULong RecPacketLen;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (!_DPlay.Implemented)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		filelist=FindNextBf(bfctrl);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (_DPlay.Host)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			filelist=FindNextBf(bfctrl);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			// Calc Packet Size
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			ULong PackSize;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			PackSize = sizeof (ULong);	// Identifier
//DEADCODE DAW 28/03/99 			PackSize += sizeof (BattlefieldType);
//DEADCODE DAW 28/03/99 			PackSize += sizeof (FileNum);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			n = 0;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			for (;;)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				val = GetLoc (n);
//DEADCODE DAW 28/03/99 				if (val)
//DEADCODE DAW 28/03/99 					n++;
//DEADCODE DAW 28/03/99 				else
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					n++;
//DEADCODE DAW 28/03/99 					break;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			PackSize += sizeof (int) * n;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			// Construct Packet data
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			BFieldPacket = new char [PackSize];
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			ptr = BFieldPacket;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			*(ULong*)ptr = BFIELDPACKETIDENT;
//DEADCODE DAW 28/03/99 			ptr += sizeof (ULong);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			*(BattlefieldType*)ptr = bfctrl;
//DEADCODE DAW 28/03/99 			ptr += sizeof (BattlefieldType);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			*(FileNum*)ptr = filelist;
//DEADCODE DAW 28/03/99 			ptr += sizeof (FileNum);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			n = 0;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			for (;;)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				val = GetLoc (n);
//DEADCODE DAW 28/03/99 				if (val)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					n++;
//DEADCODE DAW 28/03/99 					*(int*)ptr = val;
//DEADCODE DAW 28/03/99 					ptr += sizeof (int);
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				else
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					*(int*)ptr = 0;
//DEADCODE DAW 28/03/99 					ptr += sizeof (int);
//DEADCODE DAW 28/03/99 					break;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			// Transmit Bfields Packet
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			_DPlay.UISendMessageToAll (BFieldPacket, PackSize);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 			// packet has
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 			// bfctrl
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 			// filelist
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 			// could send no. of values below
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 			// rogue NULL terminator
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 			// if filelist != 0
//DEADCODE DAW 28/03/99 //TempCode ARM 27Sep96 			//	  GetLoc(0 to 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			// Read Message Queue until a BFieldPacket is received
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			for (;;)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				ULong from;
//DEADCODE DAW 28/03/99 				RecPacketLen = 512;
//DEADCODE DAW 28/03/99 //DeadCode AMM 07Aug98 				if (_DPlay.UIGetMyNonSysMessage (RecPacket, RecPacketLen))
//DEADCODE DAW 28/03/99 				if (_DPlay.ReceiveNextMessage (RecPacket, RecPacketLen,from))
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					if (from==0)
//DEADCODE DAW 28/03/99 						_DPlay.ProcessSystemMessage(RecPacket,CPS_GAMESTARTUP);
//DEADCODE DAW 28/03/99 					else if (*(ULong*)RecPacket == BFIELDPACKETIDENT)
//DEADCODE DAW 28/03/99 						break;
//DEADCODE DAW 28/03/99 					else
//DEADCODE DAW 28/03/99 						ProcessPlayerMessage(RecPacket,RecPacketLen,from,CPS_GAMESTARTUP);
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			// Init Data from Packet
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			ptr = RecPacket;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			ptr += sizeof (ULong);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			bfctrl = *(BattlefieldType*)ptr;
//DEADCODE DAW 28/03/99 			ptr += sizeof (BattlefieldType);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			filelist = *(FileNum*)ptr;
//DEADCODE DAW 28/03/99 			ptr += sizeof (FileNum);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			n = 0;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			for (;;)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				val = *(int*)ptr;
//DEADCODE DAW 28/03/99 				ptr += sizeof (int);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				if (val)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					SetLoc (n, val);
//DEADCODE DAW 28/03/99 					n++;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				else
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					SetLoc (n, 0);
//DEADCODE DAW 28/03/99 					break;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	return filelist;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		LoadSetPiece
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void Persons2::LoadSubPiece(WorldStuff *worldptr, FileNum filenumber)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	firstobject=IllegalSepID;
//DEADCODE DAW 28/03/99 	eventloglist=new EventLog(eventloglist);
//DEADCODE DAW 28/03/99 	eventloglist->launchtime=Timer_Code.realtime;
//DEADCODE DAW 28/03/99 	ShapeNumField snf;
//DEADCODE DAW 28/03/99 	shapefield=&snf;
//DEADCODE DAW 28/03/99 //	myworld=worldptr;
//DEADCODE DAW 28/03/99 	fileblock	bfield_file(filenumber);
//DEADCODE DAW 28/03/99 string
//DEADCODE DAW 28/03/99 	bfieldptr = (string)getdata(bfield_file);
//DEADCODE DAW 28/03/99 int
//DEADCODE DAW 28/03/99 	count = 0;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //DeadCode PD 16Oct97 	if (strcmp(bfieldptr,(string) ("BATTLEFIELD " __DATE__ "\032\n")))
//DEADCODE DAW 28/03/99 //DeadCode PD 16Oct97 		_Error.EmitSysErr("Battlefield creation version differs from persons compilation! (%s != %s)",
//DEADCODE DAW 28/03/99 //DeadCode PD 16Oct97 				bfieldptr,(string) ("BATTLEFIELD " __DATE__ "\032\n"));
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	while (*(bfieldptr++));
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (*(bfieldptr++)!=T_bfsave)
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Battlefield didn't start with BFSAVE!");
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	processbfieldtoplevel(bfieldptr);
//DEADCODE DAW 28/03/99 	SHAPESTUFF.AddShapesToGlobList(shapefield);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //TempCode DAW 02Apr96  	assert(!anyoutstanding()&&"Outstanding UID references on entry to 3d!");
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		processbfieldtoplevel
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::processbfieldtoplevel(string bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			case T_itemS:
//DEADCODE DAW 28/03/99 				toplevel_itemS(bfieldptr);
//DEADCODE DAW 28/03/99 			break;
//DEADCODE DAW 28/03/99 			case T_itemgrp:
//DEADCODE DAW 28/03/99 				toplevel_itemgrp(bfieldptr);
//DEADCODE DAW 28/03/99 			break;
//DEADCODE DAW 28/03/99 			case T_gndgrp:
//DEADCODE DAW 28/03/99 				toplevel_gndgrp(bfieldptr);
//DEADCODE DAW 28/03/99 			break;
//DEADCODE DAW 28/03/99 			case T_airgrp:
//DEADCODE DAW 28/03/99 				toplevel_airgrp(bfieldptr);
//DEADCODE DAW 28/03/99 			break;
//DEADCODE DAW 28/03/99 			case T_route:
//DEADCODE DAW 28/03/99 				toplevel_route(bfieldptr);
//DEADCODE DAW 28/03/99 			break;
//DEADCODE DAW 28/03/99 			case T_setval:
//DEADCODE DAW 28/03/99 				toplevel_setval(bfieldptr);
//DEADCODE DAW 28/03/99 			break;
//DEADCODE DAW 28/03/99 			default:
//DEADCODE DAW 28/03/99 				_Error.EmitSysErr("Type of symbol not valid in BattleField top level");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_itemgrp
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::toplevel_itemgrp(string	&bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			case T_itemS:
//DEADCODE DAW 28/03/99 				toplevel_itemS(bfieldptr);
//DEADCODE DAW 28/03/99 			break;
//DEADCODE DAW 28/03/99 			default:
//DEADCODE DAW 28/03/99 				_Error.EmitSysErr("Type of symbol not valid in BattleField top level");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_gndgrp
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::toplevel_gndgrp(string	&bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 int				inform=1;
//DEADCODE DAW 28/03/99 PosCtrl			position;
//DEADCODE DAW 28/03/99 UniqueID		wpref;
//DEADCODE DAW 28/03/99 //DeadCode RDH 11Oct96 FormationTypeIndex	formtype=FORM_DIAMOND;
//DEADCODE DAW 28/03/99 FormationTypeIndex	formtype=FORM_V;							//RDH 11Oct96
//DEADCODE DAW 28/03/99 FormationIndex	formindex=(FormationIndex)InFormMIN;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_inform:
//DEADCODE DAW 28/03/99 			inform=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_pos:
//DEADCODE DAW 28/03/99 			getposition(bfieldptr,position);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_route:
//DEADCODE DAW 28/03/99 			wpref=toplevel_route(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_form:
//DEADCODE DAW 28/03/99 			formtype=(FormationTypeIndex)evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_itemG:
//DEADCODE DAW 28/03/99 			if (inform)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 string			hold=bfieldptr;
//DEADCODE DAW 28/03/99 FormationItemPtr
//DEADCODE DAW 28/03/99 				firstentry=toplevel_gndleader(hold,position,wpref,formtype),
//DEADCODE DAW 28/03/99 				lastentry=firstentry;
//DEADCODE DAW 28/03/99 				while (--inform)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					hold=bfieldptr;
//DEADCODE DAW 28/03/99 					formindex+=(InForm)1;
//DEADCODE DAW 28/03/99 					lastentry=
//DEADCODE DAW 28/03/99 						toplevel_gndfollower
//DEADCODE DAW 28/03/99 							(hold,position,wpref,formtype,lastentry,formindex);
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				bfieldptr=hold;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				throwtree(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in BattleField mid level");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_airgrp
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::toplevel_airgrp(string	&bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 int				inform=0;
//DEADCODE DAW 28/03/99 int				inwing=0;
//DEADCODE DAW 28/03/99 PosCtrl			position;
//DEADCODE DAW 28/03/99 UniqueID		wpref;
//DEADCODE DAW 28/03/99 //DeadCode RDH 13May96 FormationTypeIndex	formtype = FORM_STACKEDV;						//RDH 26Feb96
//DEADCODE DAW 28/03/99 //TempCode MS 15Aug96 FormationTypeIndex	formtype = FORM_DIAMOND;					//RDH 13May96
//DEADCODE DAW 28/03/99 //DeadCode RDH 08Nov96 FormationTypeIndex	formtype = FORM_FLATBOX;					//MS 15Aug96
//DEADCODE DAW 28/03/99 FormationTypeIndex	formtype = FORM_STACKEDV;					//RDH 08Nov96
//DEADCODE DAW 28/03/99 DutyType		dutytype;
//DEADCODE DAW 28/03/99 FormationIndex	formindex=(FormationIndex)InFormMIN;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	colourrule=PS_RANDOM;
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_inform:
//DEADCODE DAW 28/03/99 			inform=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_inwing:
//DEADCODE DAW 28/03/99 			inwing=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_duty:
//DEADCODE DAW 28/03/99 			dutytype=(DutyType)evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_form:
//DEADCODE DAW 28/03/99 			formtype=(FormationTypeIndex)evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_pos:
//DEADCODE DAW 28/03/99 			getposition(bfieldptr,position);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_route:
//DEADCODE DAW 28/03/99 			wpref=toplevel_route(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_itemA:
//DEADCODE DAW 28/03/99 AirStruc	*firstac;
//DEADCODE DAW 28/03/99 			if (inform)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 string			hold=bfieldptr;
//DEADCODE DAW 28/03/99 int				inwing2=inwing;
//DEADCODE DAW 28/03/99 				firstac=
//DEADCODE DAW 28/03/99 					toplevel_airformlead(hold,position,wpref,dutytype,formtype);
//DEADCODE DAW 28/03/99 AirStruc		*leadac=firstac,
//DEADCODE DAW 28/03/99 				*lastac=leadac;
//DEADCODE DAW 28/03/99 				if (eventloglist->nat!=NAT_AMBER)
//DEADCODE DAW 28/03/99 					if (eventloglist->nat!=firstac->nationality)
//DEADCODE DAW 28/03/99 						firstac->ai.eventlog=
//DEADCODE DAW 28/03/99 							eventloglist=
//DEADCODE DAW 28/03/99 								new EventLog (eventloglist);
//DEADCODE DAW 28/03/99 //to get more than one airgroup per battlefield					//RDH 28Nov96
//DEADCODE DAW 28/03/99 //DeadCode RDH 28Nov96 				if (eventloglist->nat==NAT_AMBER)				//JIM 30Sep96
//DEADCODE DAW 28/03/99 				{	//enforces player priority on shared event.
//DEADCODE DAW 28/03/99 					eventloglist->nat=firstac->nationality;
//DEADCODE DAW 28/03/99 					eventloglist->targetuid=firstac->uniqueID.count;
//DEADCODE DAW 28/03/99 					eventloglist->type=firstac->classtype->planetext;
//DEADCODE DAW 28/03/99 					eventloglist->encsize += inform;			//RDH 02Oct96
//DEADCODE DAW 28/03/99 					UpdateLog(eventloglist,0,EventLog::UNSEEN);//RDH 02Oct96
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				if (	eventloglist->home==TextSnip0MIN
//DEADCODE DAW 28/03/99 					&& firstac->ai.homebase
//DEADCODE DAW 28/03/99 					&& (int)firstac->ai.homebase!=-1	)	//ARM 18Sep96
//DEADCODE DAW 28/03/99 					eventloglist->home=_Text.ConvSnip0(firstac->ai.homebase->uniqueID.count);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				while (--inform)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					hold=bfieldptr;
//DEADCODE DAW 28/03/99 					if (--inwing2)
//DEADCODE DAW 28/03/99 					{
//DEADCODE DAW 28/03/99 						formindex+=(InWing)1;
//DEADCODE DAW 28/03/99 						lastac=
//DEADCODE DAW 28/03/99 							toplevel_airfollower(	hold,position,wpref,
//DEADCODE DAW 28/03/99 													dutytype,formtype,
//DEADCODE DAW 28/03/99 													formindex,lastac);
//DEADCODE DAW 28/03/99 					}
//DEADCODE DAW 28/03/99 					else
//DEADCODE DAW 28/03/99 					{
//DEADCODE DAW 28/03/99 						inwing2=inwing;
//DEADCODE DAW 28/03/99 						formindex+=(InForm)1;
//DEADCODE DAW 28/03/99 						leadac=
//DEADCODE DAW 28/03/99 						lastac=
//DEADCODE DAW 28/03/99 							toplevel_airwinglead(	hold,position,wpref,
//DEADCODE DAW 28/03/99 													dutytype,formtype,
//DEADCODE DAW 28/03/99 													formindex,leadac);
//DEADCODE DAW 28/03/99 					}
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				bfieldptr=hold;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 			if (!inwing)
//DEADCODE DAW 28/03/99 			{	//use game settings
//DEADCODE DAW 28/03/99 				colourrule=PS_PLAYER;
//DEADCODE DAW 28/03/99 string			hold=bfieldptr;
//DEADCODE DAW 28/03/99 				firstac=
//DEADCODE DAW 28/03/99 					toplevel_airformlead(hold,position,wpref,dutytype,formtype);
//DEADCODE DAW 28/03/99 AirStruc		*leadac=firstac,
//DEADCODE DAW 28/03/99 				*lastac=leadac;
//DEADCODE DAW 28/03/99 				if (eventloglist->nat!=NAT_AMBER)
//DEADCODE DAW 28/03/99 					if (eventloglist->nat!=firstac->nationality)
//DEADCODE DAW 28/03/99 						firstac->ai.eventlog=
//DEADCODE DAW 28/03/99 							eventloglist=
//DEADCODE DAW 28/03/99 								new EventLog (eventloglist);
//DEADCODE DAW 28/03/99 				eventloglist->nat=firstac->nationality;			//JIM 30Sep96
//DEADCODE DAW 28/03/99 				eventloglist->targetuid=firstac->uniqueID.count;
//DEADCODE DAW 28/03/99 				eventloglist->type=firstac->classtype->planetext;
//DEADCODE DAW 28/03/99 //DeadCode RDH 02Oct96 				eventloglist->stage=eventloglist->TAKEOFF;
//DEADCODE DAW 28/03/99 				UpdateLog(eventloglist,0,EventLog::TAKEOFF);//RDH 02Oct96
//DEADCODE DAW 28/03/99 				if (	eventloglist->home==TextSnip0MIN
//DEADCODE DAW 28/03/99 					&& firstac->ai.homebase
//DEADCODE DAW 28/03/99 					&& (int)firstac->ai.homebase!=-1
//DEADCODE DAW 28/03/99 					&& (firstac->movecode==AUTO_TAKEOFF)		//RDH 13Nov96
//DEADCODE DAW 28/03/99 					)
//DEADCODE DAW 28/03/99 					eventloglist->home=_Text.ConvSnip0(firstac->ai.homebase->uniqueID.count);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				inform=0;
//DEADCODE DAW 28/03/99 int				inwing2=Miss_Man.camp.squad[0].flightnum[inform];//RDH 17Feb97
//DEADCODE DAW 28/03/99 				while (--inwing2)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					hold=bfieldptr;
//DEADCODE DAW 28/03/99 					formindex+=(InWing)1;
//DEADCODE DAW 28/03/99 					lastac=
//DEADCODE DAW 28/03/99 						toplevel_airfollower(	hold,position,wpref,
//DEADCODE DAW 28/03/99 												dutytype,formtype,
//DEADCODE DAW 28/03/99 												formindex,lastac);
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				while (++inform<4)
//DEADCODE DAW 28/03/99 					if ((inwing2=Miss_Man.camp.squad[0].flightnum[inform])!=0)//RDH 17Feb97
//DEADCODE DAW 28/03/99 					{
//DEADCODE DAW 28/03/99 						hold=bfieldptr;
//DEADCODE DAW 28/03/99 						formindex+=(InForm)1;
//DEADCODE DAW 28/03/99 						leadac=
//DEADCODE DAW 28/03/99 						lastac=
//DEADCODE DAW 28/03/99 							toplevel_airwinglead(	hold,position,wpref,
//DEADCODE DAW 28/03/99 													dutytype,formtype,
//DEADCODE DAW 28/03/99 													formindex,leadac);
//DEADCODE DAW 28/03/99 						while (--inwing2)
//DEADCODE DAW 28/03/99 						{
//DEADCODE DAW 28/03/99 						hold=bfieldptr;
//DEADCODE DAW 28/03/99 							formindex+=(InWing)1;
//DEADCODE DAW 28/03/99 							lastac=
//DEADCODE DAW 28/03/99 								toplevel_airfollower(	hold,position,wpref,
//DEADCODE DAW 28/03/99 														dutytype,formtype,
//DEADCODE DAW 28/03/99 														formindex,lastac);
//DEADCODE DAW 28/03/99 						}
//DEADCODE DAW 28/03/99 					}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				bfieldptr=hold;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		fixupengagements(firstac);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in BattleField mid level");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		fixupengagements
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Mon 19 Aug 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Fixes to squadron engagement logic for forward references
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::fixupengagements(AirStrucPtr	firstac)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	AirStrucPtr attacker=firstac->ai.attacker;
//DEADCODE DAW 28/03/99 	if (	firstac->ai.unfriendly
//DEADCODE DAW 28/03/99 		&&	(int) firstac->ai.unfriendly !=-1
//DEADCODE DAW 28/03/99 		&& 	firstac->ai.unfriendly->Status.size==AIRSTRUCSIZE	)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		AirStrucPtr	eye=firstac;
//DEADCODE DAW 28/03/99 		AirStrucPtr trg=*firstac->ai.unfriendly;
//DEADCODE DAW 28/03/99 		fixupengagements(eye,trg);
//DEADCODE DAW 28/03/99 		if (	trg->ai.unfriendly==eye
//DEADCODE DAW 28/03/99 			&&	attacker!=trg	)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			AirStrucPtr	eye=trg;
//DEADCODE DAW 28/03/99 			AirStrucPtr trg=firstac;
//DEADCODE DAW 28/03/99 			fixupengagements(eye,trg);
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	if (	attacker
//DEADCODE DAW 28/03/99 		&&	(int)attacker!=-1	)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 			AirStrucPtr	eye=attacker;
//DEADCODE DAW 28/03/99 			AirStrucPtr trg=firstac;
//DEADCODE DAW 28/03/99 			fixupengagements(eye,trg);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 void	Persons2::fixupengagements(AirStrucPtr	eyeF,AirStrucPtr trg)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	//movecodes and manoeuvres already done
//DEADCODE DAW 28/03/99 	//leader goes for leader... already done
//DEADCODE DAW 28/03/99 	trg->ai.attacker=eyeF;
//DEADCODE DAW 28/03/99 	AirStrucPtr	trgF=trg;
//DEADCODE DAW 28/03/99 	forever
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		AirStrucPtr eye=*eyeF->follower;
//DEADCODE DAW 28/03/99 		while (eye)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			AirStrucPtr trgE=Art_Int.SetFollowerWhoCanEngage(eye,trgF);
//DEADCODE DAW 28/03/99 			if (trg)
//DEADCODE DAW 28/03/99 				trgF=trgE;
//DEADCODE DAW 28/03/99 			eye->ai.unfriendly=trgE;
//DEADCODE DAW 28/03/99 			if (trgE && trgE->ai.attacker!=NULL)
//DEADCODE DAW 28/03/99 				trgE->ai.attacker=eye;
//DEADCODE DAW 28/03/99 			eye=*eye->follower;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		eyeF=eyeF->fly.nextflight;
//DEADCODE DAW 28/03/99 		breakif (eyeF==NULL);
//DEADCODE DAW 28/03/99 		AirStrucPtr trgF=Art_Int.SetFlightWhoCanEngage(eyeF,trg);
//DEADCODE DAW 28/03/99 		if (trgF)
//DEADCODE DAW 28/03/99 			trg=trgF;
//DEADCODE DAW 28/03/99 		eyeF->ai.unfriendly=trgF;
//DEADCODE DAW 28/03/99 		if (trgF && trgF->ai.attacker!=NULL)
//DEADCODE DAW 28/03/99 			trgF->ai.attacker=eyeF;
//DEADCODE DAW 28/03/99 	};
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_route
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 UniqueID	Persons2::toplevel_route(string	&bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 UniqueID	chainwp=IllegalSepID,
//DEADCODE DAW 28/03/99 			firstwp=IllegalSepID;
//DEADCODE DAW 28/03/99 	if (*bfieldptr==T_setUID || *bfieldptr==T_target)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		return(getobjectbyUID(bfieldptr));
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			case T_route:
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 UniqueID		tmpUID=toplevel_route(bfieldptr);
//DEADCODE DAW 28/03/99 WayPointPtr		tmpwp2=(WayPointPtr)ConvertPtrUID(tmpUID);
//DEADCODE DAW 28/03/99 				assert((tmpwp2)&&("nested route must exist"));
//DEADCODE DAW 28/03/99 				if (firstwp!=IllegalSepID)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 WayPointPtr			tmpwp1=(WayPointPtr)ConvertPtrUID(chainwp);
//DEADCODE DAW 28/03/99 					assert((tmpwp1)&&("nested route must exist"));
//DEADCODE DAW 28/03/99 					tmpwp1->next=tmpwp2;
//DEADCODE DAW 28/03/99 					while (tmpwp1->next)
//DEADCODE DAW 28/03/99 						tmpwp1=tmpwp1->next;
//DEADCODE DAW 28/03/99 					chainwp=tmpwp1->uniqueID.count;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				else
//DEADCODE DAW 28/03/99 					firstwp=chainwp=tmpUID;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			case T_waypoint:
//DEADCODE DAW 28/03/99 				chainwp=midlevel_waypoint(bfieldptr,chainwp);
//DEADCODE DAW 28/03/99 				if (firstwp==IllegalSepID)	firstwp=chainwp;
//DEADCODE DAW 28/03/99 			break;
//DEADCODE DAW 28/03/99 			default:
//DEADCODE DAW 28/03/99 				_Error.EmitSysErr("Type of symbol not valid in BattleField mid level");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 //what to do with the chain now we have it?
//DEADCODE DAW 28/03/99 //add it to the list of known chains...
//DEADCODE DAW 28/03/99 	AddRoute(firstwp);
//DEADCODE DAW 28/03/99 	return(firstwp);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		midlevel_waypoint
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Fri 12 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 UniqueID	Persons2::midlevel_waypoint(string	&bfieldptr,UniqueID	chainwp)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 //special code if 'existing' route is referenced
//DEADCODE DAW 28/03/99 	if (*bfieldptr==T_setUID)									//JIM 01Apr96
//DEADCODE DAW 28/03/99 	{															//JIM 01Apr96
//DEADCODE DAW 28/03/99 		UniqueID	newUID=getobjectbyUID(bfieldptr);			//JIM 01Apr96
//DEADCODE DAW 28/03/99 		if (chainwp!=IllegalSepID)								//JIM 01Apr96
//DEADCODE DAW 28/03/99 		{														//JIM 01Apr96
//DEADCODE DAW 28/03/99 WayPointPtr														//JIM 01Apr96
//DEADCODE DAW 28/03/99 			oldwp=(WayPointPtr)ConvertPtrUID(chainwp);			//JIM 01Apr96
//DEADCODE DAW 28/03/99 			assert((oldwp)&&("nested route must exist"));		//JIM 01Apr96
//DEADCODE DAW 28/03/99 WayPointPtr														//JIM 01Apr96
//DEADCODE DAW 28/03/99 			newwp=(WayPointPtr)ConvertPtrUID(newUID);			//JIM 01Apr96
//DEADCODE DAW 28/03/99 			oldwp->next=newwp;									//JIM 01Apr96
//DEADCODE DAW 28/03/99 			newwp->prev=oldwp;									//JIM 01Apr96
//DEADCODE DAW 28/03/99 //TempCode JIM 12Jan96 			tmpwp->nextwp=newwaypoint;		//JIM 01Apr96
//DEADCODE DAW 28/03/99 		}														//JIM 01Apr96
//DEADCODE DAW 28/03/99 		return(newUID);											//JIM 01Apr96
//DEADCODE DAW 28/03/99 	}															//JIM 01Apr96
//DEADCODE DAW 28/03/99 //normal code... route is inline
//DEADCODE DAW 28/03/99 WayPointPtr
//DEADCODE DAW 28/03/99 	newwaypoint=new WayPoint;
//DEADCODE DAW 28/03/99 //DeadCode AMM 10Jun98  	newwaypoint->uniqueID.deaded=FALSE;							//RJS 27Feb98
//DEADCODE DAW 28/03/99 //DeadCode AMM 30Nov98  	newwaypoint->uniqueID.commsmove=FALSE;						//AMM 10Jun98
//DEADCODE DAW 28/03/99  	newwaypoint->Status.deaded=FALSE;							//AMM 30Nov98
//DEADCODE DAW 28/03/99 //DeadCode RJS 27Feb98  	newwaypoint->uniqueID.sector=FALSE;
//DEADCODE DAW 28/03/99 UniqueID
//DEADCODE DAW 28/03/99 	tmpUID=IllegalSepID,
//DEADCODE DAW 28/03/99 	targUID=IllegalSepID;
//DEADCODE DAW 28/03/99 PosCtrl
//DEADCODE DAW 28/03/99 	position;
//DEADCODE DAW 28/03/99 int	tmprange=0;
//DEADCODE DAW 28/03/99 	newwaypoint->vel = 0;										//RDH 19Feb96
//DEADCODE DAW 28/03/99 	newwaypoint->eta = 0;										//RDH 19Feb96
//DEADCODE DAW 28/03/99 BFieldWaypointActions
//DEADCODE DAW 28/03/99 	tmpwpaction=wpacnoactionno;
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_setUID:
//DEADCODE DAW 28/03/99 			tmpUID=(UniqueID) evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_vel:
//DEADCODE DAW 28/03/99 			newwaypoint->vel=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_start:
//DEADCODE DAW 28/03/99 			newwaypoint->eta=event_time(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_pos:
//DEADCODE DAW 28/03/99 			getposition(bfieldptr,position);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_target:
//DEADCODE DAW 28/03/99 			targUID=(UniqueID) evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_wpact:
//DEADCODE DAW 28/03/99 			tmpwpaction=(BFieldWaypointActions) evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_range:
//DEADCODE DAW 28/03/99 			tmprange=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_rangepc:
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			tmprange=-evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_event:	//generates an entry somewhere else (mysterious??)
//DEADCODE DAW 28/03/99 			midlevel_event(bfieldptr,newwaypoint);
//DEADCODE DAW 28/03/99 //DeadCode AMM 10Jun98 			newwaypoint->uniqueID.deaded=TRUE;					//RJS 27Feb98
//DEADCODE DAW 28/03/99 //DeadCode AMM 30Nov98 			newwaypoint->uniqueID.commsmove=TRUE;				//AMM 10Jun98
//DEADCODE DAW 28/03/99 			newwaypoint->Status.deaded=TRUE;					//AMM 30Nov98
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 			default:
//DEADCODE DAW 28/03/99 				_Error.EmitSysErr("Type of symbol not valid in BattleField mid level");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	if (tmpUID==IllegalSepID)
//DEADCODE DAW 28/03/99 		tmpUID=assignuid(WayPointBAND);
//DEADCODE DAW 28/03/99 	setposition(newwaypoint,position,FALSE);
//DEADCODE DAW 28/03/99 	if (targUID!=IllegalSepID)
//DEADCODE DAW 28/03/99 		setpointer((ItemBase**)&newwaypoint->target,targUID);
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 		newwaypoint->target=NULL;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	WayPointPtr	tmpwp=NULL;
//DEADCODE DAW 28/03/99 	if (chainwp!=IllegalSepID)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		tmpwp=(WayPointPtr)ConvertPtrUID(chainwp);
//DEADCODE DAW 28/03/99 		assert((tmpwp)&&("nested route must exist"));
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	if (tmprange<0)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		assert(tmpwp&&"RangePC but no prev");
//DEADCODE DAW 28/03/99 		SLong r;
//DEADCODE DAW 28/03/99 		ANGLES b,a;
//DEADCODE DAW 28/03/99 		Math_Lib.Intercept(	tmpwp->World.X-newwaypoint->World.X,
//DEADCODE DAW 28/03/99 							tmpwp->World.Y-newwaypoint->World.Y,
//DEADCODE DAW 28/03/99 							tmpwp->World.Z-newwaypoint->World.Z,
//DEADCODE DAW 28/03/99 							r,b,a);
//DEADCODE DAW 28/03/99 		if (r>1000000)
//DEADCODE DAW 28/03/99 			r=(r/100)*-tmprange;
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			r=(r*-tmprange)/100;
//DEADCODE DAW 28/03/99 		newwaypoint->range=r;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 		newwaypoint->range=tmprange;
//DEADCODE DAW 28/03/99 	newwaypoint->action=tmpwpaction;
//DEADCODE DAW 28/03/99 	newwaypoint->uniqueID.count=tmpUID;
//DEADCODE DAW 28/03/99 	logUID(newwaypoint);
//DEADCODE DAW 28/03/99 	if (tmpwp)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		tmpwp->next=newwaypoint;
//DEADCODE DAW 28/03/99 		newwaypoint->prev=tmpwp;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 		newwaypoint->prev=NULL;
//DEADCODE DAW 28/03/99 	newwaypoint->next=NULL;
//DEADCODE DAW 28/03/99 	return(newwaypoint->uniqueID.count);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		midlevel_event
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Fri 12 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void		Persons2::midlevel_event(string& bfieldptr,ItemBasePtr desire)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 EventRecPtr	newevent=new EventRec (desire,loopcount);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case	T_setval:
//DEADCODE DAW 28/03/99 			newevent->eventlist[loopcount]=event_setval(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_start:
//DEADCODE DAW 28/03/99 			newevent->eventwstart=event_time(bfieldptr);
//DEADCODE DAW 28/03/99 			newevent->eventlist[loopcount].Index=EventSet::GV_EVENT_WINDOW;
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Oct96 			newevent->eventlistsize--;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_window:
//DEADCODE DAW 28/03/99 			newevent->eventwend=event_time(bfieldptr);
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Oct96 			newevent->eventlistsize--;
//DEADCODE DAW 28/03/99 			newevent->eventlist[loopcount].Index=EventSet::GV_EVENT_WINDOW;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_event:
//DEADCODE DAW 28/03/99 			newevent->eventlist[loopcount]=event_event(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	if (newevent->eventwend)									//JIM 04Nov96
//DEADCODE DAW 28/03/99 		newevent->eventwend+=newevent->eventwstart+Timer_Code.realtime;
//DEADCODE DAW 28/03/99 	if (newevent->eventwstart)
//DEADCODE DAW 28/03/99 		newevent->eventwstart+=Timer_Code.realtime;
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Nov96 	if (newevent->eventwstart)
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Nov96 		newevent->eventwstart+=Timer_Code.realtime;
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Nov96 	if (newevent->eventwend)
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Nov96 		newevent->eventwend+=newevent->eventwstart;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		event_setval
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 20 Mar 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 EventSet	Persons2::event_setval(string& bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 EventSet	es;
//DEADCODE DAW 28/03/99 	if (loopcount!=2)
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("There must be an Lvalue and an RValue in SetVal");
//DEADCODE DAW 28/03/99 	es.Index=evaluateglobvar(bfieldptr);
//DEADCODE DAW 28/03/99 	es.Value=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 	return(es);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Procedure		event_start
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Date			Wed 20 Mar 1996
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Description	
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Inputs		
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Returns	
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 EventSet	Persons2::event_start(string& bfieldptr)
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 {
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 EventSet	es;
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 	es.Index=es.GV_EVENT_START;
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 	es.Value=event_time(bfieldptr);
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 	return(es);
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 }
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Procedure		event_window
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Date			Wed 20 Mar 1996
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Description	
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Inputs		
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //Returns	
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 EventSet	Persons2::event_window(string& bfieldptr)
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 {
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 EventSet	es;
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 	es.Index=es.GV_EVENT_WINDOW;
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 	es.Value=event_time(bfieldptr);
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 	return(es);
//DEADCODE DAW 28/03/99 //DeadCode JIM 14Aug96 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		event_event
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 20 Mar 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 EventSet	Persons2::event_event(string& bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (*bfieldptr==T_linklist)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 	int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 EventRecPtr	newevent=new EventRec (NULL,loopcount);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case	T_setval:
//DEADCODE DAW 28/03/99 			newevent->eventlist[loopcount]=event_setval(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_start:
//DEADCODE DAW 28/03/99 			newevent->eventwstart=event_time(bfieldptr);		//JIM 14Aug96
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_window:
//DEADCODE DAW 28/03/99 			newevent->eventwend=event_time(bfieldptr);			//JIM 14Aug96
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_event:
//DEADCODE DAW 28/03/99 			newevent->eventlist[loopcount]=event_event(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		if (newevent->eventwend)								//JIM 04Nov96
//DEADCODE DAW 28/03/99 			newevent->eventwend+=newevent->eventwstart+Timer_Code.realtime;
//DEADCODE DAW 28/03/99 		if (newevent->eventwstart)								//JIM 14Aug96
//DEADCODE DAW 28/03/99 			newevent->eventwstart+=Timer_Code.realtime;
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Nov96 		if (newevent->eventwstart)								//JIM 14Aug96
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Nov96 		newevent->eventwstart+=Timer_Code.realtime;
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Nov96 		if (newevent->eventwend)
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Nov96 			newevent->eventwend+=newevent->eventwstart;
//DEADCODE DAW 28/03/99 		EventSet es;
//DEADCODE DAW 28/03/99 		es.Index=es.GV_EVENT_NEST;
//DEADCODE DAW 28/03/99 		es.Nesting=newevent;
//DEADCODE DAW 28/03/99 		return(es);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		EventSet es;
//DEADCODE DAW 28/03/99 		es.Index=es.GV_EVENT_EVENT;
//DEADCODE DAW 28/03/99 		es.Value=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		return(es);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		Event_Time
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 20 Mar 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 int	Persons2::event_time(string& bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 int	retval=0;
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99  		case T_hours:	//hours
//DEADCODE DAW 28/03/99 			retval+=evaluate(bfieldptr)*60*60*100;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99  		case T_mins:	//mins
//DEADCODE DAW 28/03/99 			retval+=evaluate(bfieldptr)*60*100;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99  		case T_secs:	//mins
//DEADCODE DAW 28/03/99 			retval+=evaluate(bfieldptr)*100;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	return(retval);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_itemS
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::toplevel_itemS(string	&bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 UniqueIDBand	tmpband= RedVetoedBAND;	//GreenCivilianBAND;	//JIM 02Dec96
//DEADCODE DAW 28/03/99 UniqueID		tmpID= IllegalSepID;
//DEADCODE DAW 28/03/99 PosCtrl			position;
//DEADCODE DAW 28/03/99 ShapeNum		shape=(ShapeNum)-1;
//DEADCODE DAW 28/03/99 ANGLES			tmpasp = ANGLES_90Deg;							//RJS 18Nov96
//DEADCODE DAW 28/03/99 ANGLES			tmpbrg = ANGLES_90Deg;							//RJS 18Nov96
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 itemptr	tmpitem = new item;
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_event:
//DEADCODE DAW 28/03/99 			midlevel_event(bfieldptr,tmpitem);
//DEADCODE DAW 28/03/99 			if (Three_Dee.livelist)
//DEADCODE DAW 28/03/99 				*Three_Dee.livelist+=tmpitem;					//JIM 11Dec96
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_hdg:
//DEADCODE DAW 28/03/99 		case T_bearing:
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 //DeadCode RJS 18Nov96 			ANGLES	tmpasp,tmpbrg;
//DEADCODE DAW 28/03/99 			tmpbrg=(Angles)evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 			tmpasp = ANGLES_0Deg;								//RJS 18Nov96
//DEADCODE DAW 28/03/99 			//ROBERT: now what?????
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_target:
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			PosCtrl		trgpos;
//DEADCODE DAW 28/03/99 //DeadCode RJS 18Nov96 			ANGLES	tmpasp,tmpbrg;
//DEADCODE DAW 28/03/99 			SLong	tmprange;
//DEADCODE DAW 28/03/99 			getposition(++bfieldptr,trgpos);
//DEADCODE DAW 28/03/99 			if (	(	(position.absaxes==position.ABS_REL)
//DEADCODE DAW 28/03/99 					&&	(	(trgpos.absaxes!=trgpos.ABS_REL)
//DEADCODE DAW 28/03/99 					 	|| (trgpos.refUID.count!=position.refUID.count)
//DEADCODE DAW 28/03/99 					)	)
//DEADCODE DAW 28/03/99 				||	(	(trgpos.absaxes==trgpos.ABS_REL)
//DEADCODE DAW 28/03/99 					&&	(	(position.absaxes!=position.ABS_REL)
//DEADCODE DAW 28/03/99 					 	|| (trgpos.refUID.count!=position.refUID.count)
//DEADCODE DAW 28/03/99 				)	)	)
//DEADCODE DAW 28/03/99 				_Error.EmitSysErr("Forward reference in intercept not resolved. UIDs: %4x %4x",
//DEADCODE DAW 28/03/99 					position.refUID.count,trgpos.refUID.count);
//DEADCODE DAW 28/03/99 				Math_Lib.Intercept(	trgpos.pos.X-position.pos.X,
//DEADCODE DAW 28/03/99 									trgpos.pos.Y-position.pos.Y,
//DEADCODE DAW 28/03/99 									trgpos.pos.Z-position.pos.Z,
//DEADCODE DAW 28/03/99 									tmprange,tmpbrg,tmpasp);
//DEADCODE DAW 28/03/99 			//ROBERT: now what?????
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_UIDband:
//DEADCODE DAW 28/03/99 			tmpband=(UniqueIDBand) evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_setUID:
//DEADCODE DAW 28/03/99 			tmpID=(UniqueID) evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_pos:
//DEADCODE DAW 28/03/99 			getposition(bfieldptr,position);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_shape:
//DEADCODE DAW 28/03/99 			shape=(ShapeNum) evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in BattleField mid level");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		if (tmpID==IllegalSepID)
//DEADCODE DAW 28/03/99 			tmpID=assignuid(tmpband);
//DEADCODE DAW 28/03/99 		if(shape==(ShapeNum)-1)
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Shape not set in item");
//DEADCODE DAW 28/03/99 		tmpitem->shape=shape;
//DEADCODE DAW 28/03/99 		*shapefield|=shape;
//DEADCODE DAW 28/03/99 		if (tmpasp != ANGLES_90Deg)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			// Set anim for bridge shape....
//DEADCODE DAW 28/03/99 			// ... and fill it in for animation
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			if (SHAPE.SetAnimData(tmpitem,0) == sizeof(ExplodeAnimData))
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				ExplodeAnimData*	adptr = (ExplodeAnimData*) tmpitem->Anim;
//DEADCODE DAW 28/03/99 				adptr->frameno = tmpbrg;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		tmpitem->uniqueID.count=tmpID;
//DEADCODE DAW 28/03/99 		setposition(tmpitem,position,TRUE);
//DEADCODE DAW 28/03/99 		logUID(tmpitem);
//DEADCODE DAW 28/03/99 		if (firstobject==IllegalSepID)
//DEADCODE DAW 28/03/99 			firstobject=tmpID;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //DeadCode JIM 08Jan96 		AddToWorld(tmpitem);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_setval
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 5 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::toplevel_setval(string	&bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 int	locnum;
//DEADCODE DAW 28/03/99 int	value;
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	if (loopcount!=2)
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("There must be an Lvalue and an RValue in SetVal");
//DEADCODE DAW 28/03/99 	locnum=evaluateglobvar(bfieldptr);
//DEADCODE DAW 28/03/99 	value=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 	SetLoc(locnum,value);
//DEADCODE DAW 28/03/99 //DeadCode JIM 20Mar96 	*globallocations[locnum]=value;
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		evaluateglobvar
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Thu 7 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	chain down to get globallocations table index and get that.
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 SLong	Persons2::evaluateglobvar(string &bfieldptr,FormationIndex fi)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 SLong	retval;
//DEADCODE DAW 28/03/99 //DeadCode JIM 08Jan96 	for (;;)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_long:
//DEADCODE DAW 28/03/99 		case T_int:
//DEADCODE DAW 28/03/99 			retval=*((ULong*) bfieldptr);
//DEADCODE DAW 28/03/99 			bfieldptr+=4;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_word:
//DEADCODE DAW 28/03/99 			retval=*((UWord*) bfieldptr);
//DEADCODE DAW 28/03/99 			bfieldptr+=2;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_byte:
//DEADCODE DAW 28/03/99 			retval=((UByte) (*(bfieldptr++)) );
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_linklist:
//DEADCODE DAW 28/03/99 		case T_nlong:
//DEADCODE DAW 28/03/99 		case T_nint:
//DEADCODE DAW 28/03/99 		case T_nword:
//DEADCODE DAW 28/03/99 		case T_nbyte:
//DEADCODE DAW 28/03/99 		case T_random:
//DEADCODE DAW 28/03/99 		case T_select:
//DEADCODE DAW 28/03/99 		case T_list:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Unexpected construct while getting global index");
//DEADCODE DAW 28/03/99 		default:retval=evaluateglobvar(bfieldptr,fi);
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	return(retval);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		evaluate
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Parses an integer value from the stream
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		bfieldptr-> stream which evaluates
//DEADCODE DAW 28/03/99 //Format of evaluation:
//DEADCODE DAW 28/03/99 //				T_rnd	- next 3 integer parameters specify random number basis
//DEADCODE DAW 28/03/99 //				T_sel	- next 3 integer parameters specify a selection process
//DEADCODE DAW 28/03/99 //				T_list	- use (fi) to index the given list of values
//DEADCODE DAW 28/03/99 //				T_int	- long integer value
//DEADCODE DAW 28/03/99 //				T_byte/T_word/T_long	shorter integers
//DEADCODE DAW 28/03/99 //				T_main	- main program variable
//DEADCODE DAW 28/03/99 //				other   - simply skip byte and re-evaluate
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns		the integer value generated
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 SLong	Persons2::evaluate(string &bfieldptr,FormationIndex fi)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 SLong	retval;
//DEADCODE DAW 28/03/99 //DeadCode JIM 08Jan96 	for (;;)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_random:		//int(p1*rnd)*p3+p2
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 int			p1=0,p2=0,p3=1,lc=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 			p1=evaluate(bfieldptr,fi);
//DEADCODE DAW 28/03/99 			if (--lc)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				p2 = p1;										//RDH 26Jun96
//DEADCODE DAW 28/03/99 //DeadCode RDH 26Jun96 				p2=evaluate(bfieldptr,fi);
//DEADCODE DAW 28/03/99 				p1=evaluate(bfieldptr,fi);						//RDH 26Jun96
//DEADCODE DAW 28/03/99 				if (--lc)
//DEADCODE DAW 28/03/99 					p3=evaluate(bfieldptr,fi);
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			return(Math_Lib.rnd((SWord)p1)*p3+p2);
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 //DeadCode DAW 10Jan96 		break;
//DEADCODE DAW 28/03/99 		case T_select:		//p1*p3+p2
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 int			p1=0,p2,p3=1,lc=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 			//select with 1 param discards formation index
//DEADCODE DAW 28/03/99 			p2=evaluate(bfieldptr);							//RDH 27Jun96
//DEADCODE DAW 28/03/99 			if (--lc)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				p1=evaluate(bfieldptr,fi);						//RDH 27Jun96
//DEADCODE DAW 28/03/99 				if (--lc)
//DEADCODE DAW 28/03/99 					p3=evaluate(bfieldptr,fi);
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 //DeadCode JIM 02Sep96 			else _Error.EmitSysErr("Select with 1 param... why bother?");//RDH 27Jun96
//DEADCODE DAW 28/03/99 			return(p1*p3+p2);
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 //DeadCode DAW 10Jan96 		break;
//DEADCODE DAW 28/03/99 		case T_list:	//build list of available values using fi>>5
//DEADCODE DAW 28/03/99 						//select from list using fi&31
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 int			lc=getloopcount(bfieldptr),
//DEADCODE DAW 28/03/99 			lci=0,
//DEADCODE DAW 28/03/99 			fip=fi>>5;
//DEADCODE DAW 28/03/99 			if (fi==FormationIndexMAX)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				fi=(FormationIndex)evaluate(bfieldptr,(FormationIndex) fip);
//DEADCODE DAW 28/03/99 				lc--;
//DEADCODE DAW 28/03/99 				if (fi>=lc)
//DEADCODE DAW 28/03/99 					_Error.EmitSysErr("List (%i) not big enough for index (%i)",lc,fi);
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				fi=(FormationIndex)(fi&31);
//DEADCODE DAW 28/03/99 				if (fi>=lc)
//DEADCODE DAW 28/03/99 					fi=(FormationIndex)(lc-1);
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			while (lci++!=fi)	throwtree(bfieldptr);
//DEADCODE DAW 28/03/99 int			retval=				evaluate(bfieldptr,(FormationIndex) fip);
//DEADCODE DAW 28/03/99 			while (lci++!=lc)	throwtree(bfieldptr);
//DEADCODE DAW 28/03/99 			return(retval);
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 //DeadCode DAW 10Jan96 		break;
//DEADCODE DAW 28/03/99 		case T_long:
//DEADCODE DAW 28/03/99 		case T_int:
//DEADCODE DAW 28/03/99 			retval=*((ULong*) bfieldptr);
//DEADCODE DAW 28/03/99 			bfieldptr+=4;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_nlong:
//DEADCODE DAW 28/03/99 		case T_nint:
//DEADCODE DAW 28/03/99 			retval=*((ULong*) bfieldptr);
//DEADCODE DAW 28/03/99 			retval=-retval;
//DEADCODE DAW 28/03/99 			bfieldptr+=4;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_word:
//DEADCODE DAW 28/03/99 			retval=*((UWord*) bfieldptr);
//DEADCODE DAW 28/03/99 			bfieldptr+=2;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_nword:
//DEADCODE DAW 28/03/99 			retval=*((UWord*) bfieldptr);
//DEADCODE DAW 28/03/99 			retval=-retval;
//DEADCODE DAW 28/03/99 			bfieldptr+=2;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_byte:
//DEADCODE DAW 28/03/99 			retval=((UByte) (*(bfieldptr++)) );
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_nbyte:
//DEADCODE DAW 28/03/99 			retval=-(SLong)((UByte) (*(bfieldptr++)) );
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_mainprog:
//DEADCODE DAW 28/03/99 			retval=GetLoc(evaluateglobvar(bfieldptr,fi));
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_linklist:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Not expecting linklist just here in evaluate!");
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:retval=evaluate(bfieldptr,fi);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	return(retval);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		getposition
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Evaluate a position tree
//DEADCODE DAW 28/03/99 //				Accumulate coords and fill in target item reference
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		Cope with:
//DEADCODE DAW 28/03/99 //				T_x			- delta X
//DEADCODE DAW 28/03/99 //				T_y			- delta Y
//DEADCODE DAW 28/03/99 //				T_z 		- delta Z
//DEADCODE DAW 28/03/99 //				T_setUID	- find item and copy x,y,z
//DEADCODE DAW 28/03/99 //				T_target	- poss create item and copy x,y,z
//DEADCODE DAW 28/03/99 //				T_abs 		- ignore - nesting - contains x,y,z,target
//DEADCODE DAW 28/03/99 //				T_rel		- in here target can mean get hdg/pitch from item
//DEADCODE DAW 28/03/99 //					T_asim
//DEADCODE DAW 28/03/99 //					T_bearing
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns		Filled in PosCtrl
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::getrelpos(string &bfieldptr,PosCtrl &position)
//DEADCODE DAW 28/03/99 {	//handles T_rel
//DEADCODE DAW 28/03/99 	ItemBasePtr		tmpitem=position.refptr;
//DEADCODE DAW 28/03/99 	UniqueID	tmpUID=IllegalSepID;
//DEADCODE DAW 28/03/99 	ANGLES		tmpbrg=ANGLES_0Deg,
//DEADCODE DAW 28/03/99 				tmpasp=ANGLES_0Deg;
//DEADCODE DAW 28/03/99 	Bool		usebrg=FALSE,
//DEADCODE DAW 28/03/99 				useasp=FALSE;
//DEADCODE DAW 28/03/99 	SLong		tmprange=0;
//DEADCODE DAW 28/03/99 	int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		//read all the relative data
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_x:
//DEADCODE DAW 28/03/99 			position.pos.X+=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_y:
//DEADCODE DAW 28/03/99 			position.pos.Y+=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_z:
//DEADCODE DAW 28/03/99 			position.pos.Z+=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		case T_target:	//any object either becomes the basis for relative coords
//DEADCODE DAW 28/03/99 		case T_setUID:	//or is used to fix hdg/pitch info
//DEADCODE DAW 28/03/99 			tmpUID=getobjectbyUID(bfieldptr);
//DEADCODE DAW 28/03/99 			tmpitem=ConvertPtrUID(tmpUID);
//DEADCODE DAW 28/03/99 			if (	(tmpitem==NULL)
//DEADCODE DAW 28/03/99 				||	(tmpitem->Status.size<HPSize)
//DEADCODE DAW 28/03/99 				)
//DEADCODE DAW 28/03/99 				if (position.refUID.count)
//DEADCODE DAW 28/03/99 					_Error.EmitSysErr("Initial position item forward referenced and redefined!");
//DEADCODE DAW 28/03/99 				elseif (position.absaxes!=position.ABS_REL)
//DEADCODE DAW 28/03/99 					_Error.EmitSysErr("Fwd reference target in Rel overrides abs X,Y, or Z");
//DEADCODE DAW 28/03/99 				else
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					position.refUID.count=tmpUID;
//DEADCODE DAW 28/03/99 					position.refptr=tmpitem;
//DEADCODE DAW 28/03/99 					position.absaxes=position.ABS_ABS;
//DEADCODE DAW 28/03/99 					position.pos=tmpitem->World;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 			 	tmpbrg+=((hpitem*) tmpitem)->hdg;		//don't set use flags
//DEADCODE DAW 28/03/99 			 	tmpasp+=((hpitem*) tmpitem)->pitch;	//don't know if I want it!
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				if (	(position.absaxes==position.ABS_REL)		//if coord system still rel. then
//DEADCODE DAW 28/03/99 					&&	(position.refUID.count==0x0fff)	)
//DEADCODE DAW 28/03/99 				{										//too late to get proper abs, so
//DEADCODE DAW 28/03/99 					position.refUID.count=tmpUID;				//use this item for abs
//DEADCODE DAW 28/03/99 					position.refptr=tmpitem;
//DEADCODE DAW 28/03/99 					position.absaxes=position.ABS_ABS;
//DEADCODE DAW 28/03/99 					position.pos=tmpitem->World;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_range:
//DEADCODE DAW 28/03/99 			tmprange=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_bearing:
//DEADCODE DAW 28/03/99 			tmpbrg+=(Angles)evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 			usebrg=TRUE;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_pitch:
//DEADCODE DAW 28/03/99 		case T_asimuth:
//DEADCODE DAW 28/03/99 			tmpasp+=(Angles)evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 			useasp=TRUE;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_icpt:
//DEADCODE DAW 28/03/99 			pos_icpt(bfieldptr,tmpasp,tmpbrg,tmprange);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_rangepc:
//DEADCODE DAW 28/03/99 			if (tmprange>100000)
//DEADCODE DAW 28/03/99 				tmprange=(tmprange/100)*evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				tmprange=(tmprange*evaluate(bfieldptr))/100;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Unexpected symbol in low level bfield processor");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	//if there was any angle data then convert to cartesian
//DEADCODE DAW 28/03/99 	if (useasp||usebrg)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		int	shfact=15;
//DEADCODE DAW 28/03/99 		if (tmprange>0)
//DEADCODE DAW 28/03/99 			while (tmprange>0x00010000)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				shfact--;tmprange=tmprange/2;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			while (tmprange<-0x00010000)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				shfact--;tmprange=tmprange/2;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 SWord	sinA,cosA;
//DEADCODE DAW 28/03/99 		if (useasp)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			Math_Lib.sin_cos(tmpasp,sinA,cosA);
//DEADCODE DAW 28/03/99 			position.pos.Y+=(sinA*tmprange)>>shfact;
//DEADCODE DAW 28/03/99 			tmprange=(cosA*tmprange)>>shfact;
//DEADCODE DAW 28/03/99 			shfact=15;
//DEADCODE DAW 28/03/99 			if (tmprange>0)
//DEADCODE DAW 28/03/99 				while (tmprange>0x00010000)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					shfact--;tmprange=tmprange/2;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				while (tmprange<-0x00010000)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					shfact--;tmprange=tmprange/2;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		if (usebrg)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			Math_Lib.sin_cos(tmpbrg,sinA,cosA);
//DEADCODE DAW 28/03/99 			position.pos.X+=(sinA*tmprange)>>shfact;
//DEADCODE DAW 28/03/99 			position.pos.Z+=(cosA*tmprange)>>shfact;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		getposition
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Mon 19 Aug 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::getposition(string &bfieldptr,PosCtrl &position)
//DEADCODE DAW 28/03/99 {	//handles abs stuff. Pass rel stuff to getrelpos
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case	T_x:
//DEADCODE DAW 28/03/99 			position.absaxes|=position.ABS_X;
//DEADCODE DAW 28/03/99 			position.pos.X=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_y:
//DEADCODE DAW 28/03/99 			position.absaxes|=position.ABS_Y;
//DEADCODE DAW 28/03/99 			position.pos.Y=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_z:
//DEADCODE DAW 28/03/99 			position.absaxes|=position.ABS_Z;
//DEADCODE DAW 28/03/99 			position.pos.Z=evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_abs:
//DEADCODE DAW 28/03/99 		case	T_pos:
//DEADCODE DAW 28/03/99 			getposition(bfieldptr,position);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_target:
//DEADCODE DAW 28/03/99 		case	T_setUID:
//DEADCODE DAW 28/03/99 			position.refUID.count=getobjectbyUID(bfieldptr);
//DEADCODE DAW 28/03/99 			position.refptr=ConvertPtrUID(position.refUID.count);
//DEADCODE DAW 28/03/99 			if (position.refptr)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				position.absaxes=position.ABS_ABS;
//DEADCODE DAW 28/03/99 				if (getbandfromUID(position.refUID.count)!=WayPointBAND)
//DEADCODE DAW 28/03/99 					position.pos=position.refptr->World;
//DEADCODE DAW 28/03/99 				else
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					position.pos=*FindDesPos(*position.refptr);
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 //DeadCode JIM 11Dec95 				position.refUID.count=0xffff;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				position.absaxes=position.ABS_REL;
//DEADCODE DAW 28/03/99 				position.pos.X=0;position.pos.Y=0;position.pos.Z=0;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_rel:
//DEADCODE DAW 28/03/99 			getrelpos(bfieldptr,position);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in BattleField getposition");//JIM 28Mar96
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		pos_icpt
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Mon 19 Aug 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::pos_icpt(string&bfieldptr,ANGLES&tmpasp,ANGLES&tmpbrg,SLong&tmprange)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 PosCtrl	pos1,pos2;
//DEADCODE DAW 28/03/99 UniqueID	tmpUID;
//DEADCODE DAW 28/03/99 ItemBasePtr	tmpitem;
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	if (loopcount!=2)
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Expecting 2 parameters to intercept");
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case	T_target:
//DEADCODE DAW 28/03/99 		case	T_setUID:
//DEADCODE DAW 28/03/99 			tmpUID=getobjectbyUID(bfieldptr);
//DEADCODE DAW 28/03/99 			tmpitem=ConvertPtrUID(tmpUID);
//DEADCODE DAW 28/03/99 			if (	(tmpitem==NULL)
//DEADCODE DAW 28/03/99 				)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				pos1.refUID.count=tmpUID;
//DEADCODE DAW 28/03/99 				pos1.refptr=tmpitem;
//DEADCODE DAW 28/03/99 				pos1.absaxes=pos1.ABS_REL;
//DEADCODE DAW 28/03/99 //DeadCode JIM 10Dec96 				pos1.pos=tmpitem->World;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				pos1.refUID.count=tmpUID;				//use this item for abs
//DEADCODE DAW 28/03/99 				pos1.refptr=tmpitem;
//DEADCODE DAW 28/03/99 				pos1.absaxes=pos1.ABS_ABS;
//DEADCODE DAW 28/03/99 				pos1.pos=tmpitem->World;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_pos:
//DEADCODE DAW 28/03/99 			getposition(bfieldptr,pos1);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in Intercept (1)");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case	T_target:
//DEADCODE DAW 28/03/99 		case	T_setUID:
//DEADCODE DAW 28/03/99 			tmpUID=getobjectbyUID(bfieldptr);
//DEADCODE DAW 28/03/99 			tmpitem=ConvertPtrUID(tmpUID);
//DEADCODE DAW 28/03/99 			if (	(tmpitem==NULL)
//DEADCODE DAW 28/03/99 				)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				pos2.refUID.count=tmpUID;
//DEADCODE DAW 28/03/99 				pos2.refptr=tmpitem;
//DEADCODE DAW 28/03/99 				pos2.absaxes=pos2.ABS_REL;
//DEADCODE DAW 28/03/99 //DeadCode JIM 10Dec96 				pos2.pos=tmpitem->World;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				pos2.refUID.count=tmpUID;				//use this item for abs
//DEADCODE DAW 28/03/99 				pos2.refptr=tmpitem;
//DEADCODE DAW 28/03/99 				pos2.absaxes=pos2.ABS_ABS;
//DEADCODE DAW 28/03/99 				pos2.pos=tmpitem->World;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case	T_pos:
//DEADCODE DAW 28/03/99 			getposition(bfieldptr,pos2);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in Intercept (2)");
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (	(	(pos1.absaxes==pos1.ABS_REL)
//DEADCODE DAW 28/03/99 				&&	(	(pos2.absaxes!=pos2.ABS_REL)
//DEADCODE DAW 28/03/99 					 || (pos2.refUID.count!=pos1.refUID.count)
//DEADCODE DAW 28/03/99 				)	)
//DEADCODE DAW 28/03/99 			||	(	(pos2.absaxes==pos2.ABS_REL)
//DEADCODE DAW 28/03/99 				&&	(	(pos1.absaxes!=pos1.ABS_REL)
//DEADCODE DAW 28/03/99 					 || (pos2.refUID.count!=pos1.refUID.count)
//DEADCODE DAW 28/03/99 			)	)	)
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Forward reference in intercept not resolved. UIDs: %4x %4x",
//DEADCODE DAW 28/03/99 				pos1.refUID.count,pos2.refUID.count);
//DEADCODE DAW 28/03/99 			Math_Lib.Intercept(	pos2.pos.X-pos1.pos.X,
//DEADCODE DAW 28/03/99 								pos2.pos.Y-pos1.pos.Y,
//DEADCODE DAW 28/03/99 								pos2.pos.Z-pos1.pos.Z,
//DEADCODE DAW 28/03/99 								tmprange,tmpbrg,tmpasp);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_gndleader
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 FormationItemPtr	Persons2::toplevel_gndleader
//DEADCODE DAW 28/03/99 						(	string& bfieldptr,		//stream index
//DEADCODE DAW 28/03/99 							PosCtrl	position,		//base position
//DEADCODE DAW 28/03/99 							UniqueID wpref,		//route to use
//DEADCODE DAW 28/03/99 							FormationTypeIndex formtype)	//kind of formation expected
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	FormationItemPtr	newmob=new formationitem;
//DEADCODE DAW 28/03/99 	if(midlevel_gndformdata(bfieldptr,newmob,(FormationIndex) 0))
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		FormationItemPtr	leadmob=newmob->leader;
//DEADCODE DAW 28/03/99 		return(body_gndfollower(bfieldptr,position,newmob,wpref,formtype,leadmob));
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	elser
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		logUID(newmob);
//DEADCODE DAW 28/03/99 		if (firstobject==IllegalSepID)
//DEADCODE DAW 28/03/99 			firstobject=newmob->uniqueID.count;
//DEADCODE DAW 28/03/99 		setpointer((ItemBasePtr*)&newmob->waypoint,wpref);
//DEADCODE DAW 28/03/99 		newmob->formation=formtype;
//DEADCODE DAW 28/03/99 		newmob->formpos=FormationIndexMIN;	
//DEADCODE DAW 28/03/99 		setfolloweroffset(newmob);			
//DEADCODE DAW 28/03/99 		setposition(newmob,position,TRUE);	
//DEADCODE DAW 28/03/99 		if (newmob->pitch == ANGLES_180Deg)	
//DEADCODE DAW 28/03/99 			SetAngles (newmob);				
//DEADCODE DAW 28/03/99 		newmob->AddToList();
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	return(newmob);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_gndfollower
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 FormationItemPtr		Persons2::toplevel_gndfollower
//DEADCODE DAW 28/03/99 						(	string& bfieldptr,		//stream index
//DEADCODE DAW 28/03/99 							PosCtrl	position,		//base position
//DEADCODE DAW 28/03/99 							UniqueID wpref,		//route to use
//DEADCODE DAW 28/03/99 							FormationTypeIndex formtype,	//kind of formation expected
//DEADCODE DAW 28/03/99 							FormationItemPtr	parent,				//link together
//DEADCODE DAW 28/03/99 							FormationIndex	formindex)	//offset position
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	FormationItemPtr	newmob=new formationitem;
//DEADCODE DAW 28/03/99 	midlevel_gndformdata(bfieldptr,newmob,formindex);
//DEADCODE DAW 28/03/99 	return(body_gndfollower(bfieldptr,position,newmob,wpref,formtype,parent));
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 Nationality		defaultside=NAT_GREEN;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 Bool	Persons2::midlevel_gndformdata(string& bfieldptr,FormationItemPtr newmob,FormationIndex formpos)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UniqueID		uniqueID=IllegalSepID;
//DEADCODE DAW 28/03/99 	UniqueIDBand	uniqueIDband=IllegalBAND;
//DEADCODE DAW 28/03/99 	Nationality		nationality=defaultside;
//DEADCODE DAW 28/03/99 	ShapeNum			shape=(ShapeNum)0;
//DEADCODE DAW 28/03/99 	PlaneTypeSelect	type=PT_F86E;
//DEADCODE DAW 28/03/99 	AutoMoveCodeTypeSelect	movecode=AUTO_FOLLOWWP;
//DEADCODE DAW 28/03/99 	ANGLES			hpr[3]={ANGLES_90Deg,ANGLES_180Deg,ANGLES_180Deg};//MGA 21Feb96
//DEADCODE DAW 28/03/99 	UWord			damage=0;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	newmob->velx =0;												//RDH 26Feb96
//DEADCODE DAW 28/03/99 	newmob->vely =0;												//RDH 26Feb96
//DEADCODE DAW 28/03/99 	newmob->velz =0;												//RDH 26Feb96
//DEADCODE DAW 28/03/99 	newmob->velhori =0;												//RDH 26Feb96
//DEADCODE DAW 28/03/99 	newmob->vel = 50;		//5 m/s or 10mph					//JIM 03Dec96
//DEADCODE DAW 28/03/99 	UniqueID		tmpleader=IllegalSepID;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_setUID:
//DEADCODE DAW 28/03/99 			uniqueID=(UniqueID)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_nation:
//DEADCODE DAW 28/03/99 		nationality=(Nationality)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_shape:
//DEADCODE DAW 28/03/99 		shape=(ShapeNum)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_type:
//DEADCODE DAW 28/03/99 		type=(PlaneTypeSelect)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_vel:
//DEADCODE DAW 28/03/99 		newmob->vel=evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_UIDband:
//DEADCODE DAW 28/03/99 		uniqueIDband=(UniqueIDBand)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_move:
//DEADCODE DAW 28/03/99 		movecode=(AutoMoveCodeTypeSelect)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_damage:
//DEADCODE DAW 28/03/99 		damage=(UWord)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_leader:
//DEADCODE DAW 28/03/99 			tmpleader=(UniqueID)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_event:
//DEADCODE DAW 28/03/99 			if (formpos==0)
//DEADCODE DAW 28/03/99 				midlevel_event(bfieldptr,newmob);
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				throwtree(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_att:
//DEADCODE DAW 28/03/99 			toplevel_attitude(bfieldptr,hpr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in BattleField groundformdata");//JIM 28Mar96
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		
//DEADCODE DAW 28/03/99 		
//DEADCODE DAW 28/03/99 //ok... use all that luverly data!
//DEADCODE DAW 28/03/99 	if (uniqueIDband==IllegalBAND)
//DEADCODE DAW 28/03/99 		if (nationality==NAT_RED)
//DEADCODE DAW 28/03/99 			uniqueIDband=RedGroundMobileBAND;
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			uniqueIDband=BlueGroundMobileBAND;
//DEADCODE DAW 28/03/99 	if (uniqueID==IllegalSepID)
//DEADCODE DAW 28/03/99 		uniqueID=assignuid(uniqueIDband);
//DEADCODE DAW 28/03/99 	newmob->uniqueID.count=uniqueID;
//DEADCODE DAW 28/03/99 	//UniqueID is not registered at this point intentionally.
//DEADCODE DAW 28/03/99 	newmob->nationality=nationality;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	newmob->classtype=Plane_Type_Translate[type]_;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (shape)
//DEADCODE DAW 28/03/99 		newmob->shape=shape;
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 		newmob->shape=newmob->classtype->visible;
//DEADCODE DAW 28/03/99 	newmob->movecode=movecode;
//DEADCODE DAW 28/03/99 	newmob->manoeuvretime=0;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (tmpleader==IllegalSepID)
//DEADCODE DAW 28/03/99 		newmob->leader=NULL;
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 		setpointer((ItemBase**)&newmob->leader,tmpleader);
//DEADCODE DAW 28/03/99 	newmob->follower=NULL;
//DEADCODE DAW 28/03/99 	newmob->hdg=hpr[0];
//DEADCODE DAW 28/03/99 	newmob->pitch=hpr[1];
//DEADCODE DAW 28/03/99 	newmob->roll=hpr[2];
//DEADCODE DAW 28/03/99 	return (Bool)(tmpleader!=IllegalSepID);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 FormationItemPtr	Persons2::body_gndfollower(string& bfieldptr,PosCtrl	position,FormationItemPtr newmob,
//DEADCODE DAW 28/03/99 							UniqueID wpref,FormationTypeIndex formtype,FormationItemPtr lastmob)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (lastmob->leader)	lastmob=(FormationItemPtr)lastmob->leader;
//DEADCODE DAW 28/03/99 	assert ((lastmob->leader==NULL)&&("wing leader should be unique, not chained!"));
//DEADCODE DAW 28/03/99 	newmob->leader=*lastmob;
//DEADCODE DAW 28/03/99 	newmob->follower=NULL;
//DEADCODE DAW 28/03/99 	while (lastmob->follower)	lastmob=(FormationItemPtr)lastmob->follower;
//DEADCODE DAW 28/03/99 //now on last mob in formation - get next formation position
//DEADCODE DAW 28/03/99 	FormationIndex formindex=lastmob->formpos+(InWing)1;
//DEADCODE DAW 28/03/99 	lastmob->follower=newmob;
//DEADCODE DAW 28/03/99 //now point to overall leader
//DEADCODE DAW 28/03/99 	if (lastmob->leader)	lastmob=lastmob->leader;
//DEADCODE DAW 28/03/99 	assert((lastmob->leader==NULL)&&("flight leader should be unique, not chained!"));
//DEADCODE DAW 28/03/99 	newmob->leader=lastmob;
//DEADCODE DAW 28/03/99 	
//DEADCODE DAW 28/03/99 	//add to mob lists
//DEADCODE DAW 28/03/99 	//register UID
//DEADCODE DAW 28/03/99 	if (ConvertPtrUID(newmob->uniqueID.count))
//DEADCODE DAW 28/03/99 		newmob->uniqueID.count=assignuid(getbandfromUID(newmob->uniqueID.count));
//DEADCODE DAW 28/03/99 	logUID(newmob);
//DEADCODE DAW 28/03/99 	//find position and add to world
//DEADCODE DAW 28/03/99 	setpointer((ItemBasePtr*)&newmob->waypoint,wpref);
//DEADCODE DAW 28/03/99 	newmob->formation=formtype;
//DEADCODE DAW 28/03/99 	newmob->formpos=formindex;
//DEADCODE DAW 28/03/99 		if (newmob->pitch == ANGLES_180Deg)			
//DEADCODE DAW 28/03/99 			SetAngles (newmob);						
//DEADCODE DAW 28/03/99 		position.pos = *setfolloweroffset(newmob);	
//DEADCODE DAW 28/03/99 		setposition(newmob,position,TRUE);			
//DEADCODE DAW 28/03/99 	newmob->AddToList();
//DEADCODE DAW 28/03/99 	return(newmob);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		throwtree
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Throw a branch away. Don't care what is in the branch.
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void		Persons2::throwtree(string& bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 	case T_linklist:
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 int		count=(*(bfieldptr++));
//DEADCODE DAW 28/03/99 		while (count--)	throwtree(bfieldptr);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	break;
//DEADCODE DAW 28/03/99 	case T_nint:
//DEADCODE DAW 28/03/99 	case T_int:
//DEADCODE DAW 28/03/99 	case T_long:
//DEADCODE DAW 28/03/99 	case T_nlong:
//DEADCODE DAW 28/03/99 		bfieldptr+=2;
//DEADCODE DAW 28/03/99 	case T_word:
//DEADCODE DAW 28/03/99 	case T_nword:
//DEADCODE DAW 28/03/99 		bfieldptr+=1;
//DEADCODE DAW 28/03/99 	case T_byte:
//DEADCODE DAW 28/03/99 	case T_nbyte:
//DEADCODE DAW 28/03/99 		bfieldptr+=1;
//DEADCODE DAW 28/03/99 	break;
//DEADCODE DAW 28/03/99 	case 0xFF:
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Encountered -1 in throwtree. This means undefined!");
//DEADCODE DAW 28/03/99 	default:
//DEADCODE DAW 28/03/99 			throwtree(bfieldptr);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		getloopcount
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 int	Persons2::getloopcount(string & bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (*bfieldptr!=T_linklist)
//DEADCODE DAW 28/03/99 		return(1);
//DEADCODE DAW 28/03/99 	elser
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		bfieldptr++;
//DEADCODE DAW 28/03/99 		return(*(bfieldptr++));
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_colour
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 31 Jul 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::toplevel_colour(string& bfieldptr,UByte* cols,FormationIndex formpos)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	int	instr=evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 	if (instr<16)
//DEADCODE DAW 28/03/99 		colourrule=(PaintSchemes)instr;
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		colourrule=PS_DEFINED;
//DEADCODE DAW 28/03/99 		int	code=instr&0x001f;
//DEADCODE DAW 28/03/99 		if (code==16)
//DEADCODE DAW 28/03/99 			code=Math_Lib.rnd(8);
//DEADCODE DAW 28/03/99 		for (int i=0;i<6;i++)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			if (instr&0xf0000000)
//DEADCODE DAW 28/03/99 				if (code<16)
//DEADCODE DAW 28/03/99 					cols[i]=code;
//DEADCODE DAW 28/03/99 				else
//DEADCODE DAW 28/03/99 					cols[i]=Math_Lib.rnd(8);
//DEADCODE DAW 28/03/99 			instr<<=4;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		lowlevel_squadron
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 31 Jul 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 Bool	Persons2::lowlevel_squadron(string& 			bfieldptr,
//DEADCODE DAW 28/03/99 									FormationIndex		formpos,
//DEADCODE DAW 28/03/99 									UByte* 				cols,
//DEADCODE DAW 28/03/99 									SkillType&			skill,
//DEADCODE DAW 28/03/99 									PlaneTypeSelect&	type,
//DEADCODE DAW 28/03/99 									UniqueID&			homebase,
//DEADCODE DAW 28/03/99 									CharacterType&		character)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (*bfieldptr!=T_linklist)
//DEADCODE DAW 28/03/99 	{	//got a squad number equate...
//DEADCODE DAW 28/03/99 		int	snequ=evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		//set name field of event record from some sort of lookup
//DEADCODE DAW 28/03/99 		return(lowlevel_squadron(snequ));
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_paintscheme:
//DEADCODE DAW 28/03/99 			toplevel_colour(bfieldptr,cols,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_squadron:
//DEADCODE DAW 28/03/99 			lowlevel_squadron(bfieldptr,formpos,cols,skill,type,homebase,character);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_skill:
//DEADCODE DAW 28/03/99 			skill=(SkillType)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_type:
//DEADCODE DAW 28/03/99 			type=(PlaneTypeSelect)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_character:
//DEADCODE DAW 28/03/99 			character=(CharacterType)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_home:
//DEADCODE DAW 28/03/99 			homebase=(UniqueID)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in BattleField Airformdata");//JIM 28Mar96
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		return(TRUE);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		midlevel_Airformdata
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Thu 18 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	TRUE if leader was not specified
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 Bool	Persons2::midlevel_AirformData(string& bfieldptr,AirStrucPtr newac,FormationIndex formpos,UByte* cols)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UniqueID		uniqueID=IllegalSepID;
//DEADCODE DAW 28/03/99 	UniqueIDBand	uniqueIDband=IllegalBAND;
//DEADCODE DAW 28/03/99 	Nationality		nationality=defaultside;
//DEADCODE DAW 28/03/99 	ShapeNum			shape=(ShapeNum)0;
//DEADCODE DAW 28/03/99 	PlaneTypeSelect	type=(PlaneTypeSelect)GR_FriendlyScoutType00;
//DEADCODE DAW 28/03/99 	AutoMoveCodeTypeSelect	movecode=AUTO_FOLLOWWP;
//DEADCODE DAW 28/03/99 	SkillType		skill=SKILL_REGULAR;
//DEADCODE DAW 28/03/99 	MoraleType		morale=MORALE_MEDIUM;
//DEADCODE DAW 28/03/99 	CharacterType	character=CHAR_MRAVERAGE;
//DEADCODE DAW 28/03/99 	NextLeadAct		nextleadact=NL_Flights;
//DEADCODE DAW 28/03/99 	NextFollAct		nextfollact=NF_Double;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	UWord			damage=0;
//DEADCODE DAW 28/03/99 	UWord			bombs=0;
//DEADCODE DAW 28/03/99 	UniqueID		homebase=IllegalSepID,tmptarget=IllegalSepID,tmpleader=IllegalSepID,tmpattacker=IllegalSepID;
//DEADCODE DAW 28/03/99 //DeadCode DAW 26Feb96 	ANGLES			hpr[3]={ANGLES_0Deg,ANGLES_180Deg,ANGLES_180Deg};
//DEADCODE DAW 28/03/99 	ANGLES			hpr[3]={ANGLES_90Deg,ANGLES_180Deg,ANGLES_180Deg};//MGA 21Feb96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	newac->ai.eventlog=eventloglist;
//DEADCODE DAW 28/03/99 //DeadCode RDH 02Oct96 	eventloglist->encsize++;
//DEADCODE DAW 28/03/99 	newac->information = FALSE;								//RDH 28Feb96
//DEADCODE DAW 28/03/99 	newac->velx =0;												//RDH 26Feb96
//DEADCODE DAW 28/03/99 	newac->vely =0;												//RDH 26Feb96
//DEADCODE DAW 28/03/99 	newac->velz =0;												//RDH 26Feb96
//DEADCODE DAW 28/03/99 //rdh	newac->fly.aoa = ANGLES_2Deg;								//RDH 21Mar96
//DEADCODE DAW 28/03/99 //DeadCode JIM 01Aug96 	newac->fly.mainfuel = 1;									//RDH 22Apr96
//DEADCODE DAW 28/03/99 //rdh	newac->fly.slip = ANGLES_0Deg;								//RDH 11Mar96
//DEADCODE DAW 28/03/99 //rdh 8/5/98: storesweight not used now
//DEADCODE DAW 28/03/99 //	newac->fly.storesweight = 0;									//RDH 23Sep96
//DEADCODE DAW 28/03/99 	newac->fly.cpitch = ANGLES_0Deg;							//RDH 26Feb96
//DEADCODE DAW 28/03/99 //rdh	newac->ai.lastdeltapitch = ANGLES_0Deg;						//RDH 22Mar96
//DEADCODE DAW 28/03/99 	newac->ai.lastdeltaroll = ANGLES_0Deg;						//RDH 14May96
//DEADCODE DAW 28/03/99 	newac->fly.aileron = 0;										//RDH 28Feb96
//DEADCODE DAW 28/03/99 	newac->fly.elevator = 0;									//RDH 28Feb96
//DEADCODE DAW 28/03/99 	newac->fly.rudder = 0;										//RDH 28Feb96
//DEADCODE DAW 28/03/99 //	newac->fly.weight = 1000;									//JIM 20Mar96
//DEADCODE DAW 28/03/99 //DeadCode JIM 28Mar96 	newac->classtype = &camel;									//RDH 23Feb96
//DEADCODE DAW 28/03/99 	newac->vel = 500;		//50 m/s or 100mph					//RDH 19Feb96
//DEADCODE DAW 28/03/99 //DeadCode DAW 08Apr96 	newac->fly.vel_cms = 	newac->vel * 10;					//RDH 08Apr96
//DEADCODE DAW 28/03/99 //DeadCode DAW 08Apr96 	newac->fly.rollrate = ANGLES_0Deg;							//RDH 08Apr96
//DEADCODE DAW 28/03/99 //DeadCode DAW 08Apr96 	newac->fly.turnrate = ANGLES_0Deg;							//RDH 08Apr96
//DEADCODE DAW 28/03/99 	newac->weap.ShootDelay=0;									//PD 12Jul96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 int	loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		case T_setUID:
//DEADCODE DAW 28/03/99 			uniqueID=(UniqueID)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_nation:
//DEADCODE DAW 28/03/99 			nationality=(Nationality)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_shape:
//DEADCODE DAW 28/03/99 			shape=(ShapeNum)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_type:
//DEADCODE DAW 28/03/99 			type=(PlaneTypeSelect)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_vel:
//DEADCODE DAW 28/03/99 			newac->vel=evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_UIDband:
//DEADCODE DAW 28/03/99 			uniqueIDband=(UniqueIDBand)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_move:
//DEADCODE DAW 28/03/99 			movecode=(AutoMoveCodeTypeSelect)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_skill:
//DEADCODE DAW 28/03/99 			skill=(SkillType)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_morale:
//DEADCODE DAW 28/03/99 //puts in 0 so temp commented out
//DEADCODE DAW 28/03/99 	 		morale=(MoraleType)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 //DeadCode JIM 31Jul96 		morale=MORALE_MEDIUM;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_character:
//DEADCODE DAW 28/03/99 			character=(CharacterType)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_damage:
//DEADCODE DAW 28/03/99 			damage=(UWord)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_bombs:
//DEADCODE DAW 28/03/99 			bombs=(UByte)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_target:
//DEADCODE DAW 28/03/99 			tmptarget=(UniqueID)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_attacker:
//DEADCODE DAW 28/03/99 			tmpattacker=(UniqueID)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_leader:
//DEADCODE DAW 28/03/99 			tmpleader=(UniqueID)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_follower:
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			AirStrucPtr	tmpfollower=*ConvertPtrUID((UniqueID)evaluate(bfieldptr,formpos));
//DEADCODE DAW 28/03/99 			if (formpos==0)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				if (tmpfollower==NULL)
//DEADCODE DAW 28/03/99 					_Error.EmitSysErr("Follower not loaded yet!");
//DEADCODE DAW 28/03/99 				tmpfollower->fly.leadflight=newac;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_home:
//DEADCODE DAW 28/03/99 			homebase=(UniqueID)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_event:
//DEADCODE DAW 28/03/99 			if (formpos==0)										//JIM 17Dec96
//DEADCODE DAW 28/03/99 				midlevel_event(bfieldptr,newac);
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				throwtree(bfieldptr);
//DEADCODE DAW 28/03/99 //DeadCode JIM 17Dec96 			midlevel_event(bfieldptr,newac);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_att:
//DEADCODE DAW 28/03/99 			toplevel_attitude(bfieldptr,hpr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_paintscheme:
//DEADCODE DAW 28/03/99 			toplevel_colour(bfieldptr,cols,formpos);
//DEADCODE DAW 28/03/99 //DeadCode JIM 31Jul96 			colourrule=(PaintSchemes)evaluate(bfieldptr,formpos);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_squadron:
//DEADCODE DAW 28/03/99 			lowlevel_squadron(bfieldptr,formpos,cols,skill,type,homebase,character);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in BattleField Airformdata");//JIM 28Mar96
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		
//DEADCODE DAW 28/03/99 //ok... use all that luverly data!
//DEADCODE DAW 28/03/99 		if (uniqueIDband==IllegalBAND)
//DEADCODE DAW 28/03/99 			if (nationality==NAT_RED)
//DEADCODE DAW 28/03/99 				uniqueIDband=RedAcBAND;
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				uniqueIDband=BlueAcBAND;
//DEADCODE DAW 28/03/99 		if (uniqueID==IllegalSepID)
//DEADCODE DAW 28/03/99 			uniqueID=assignuid(uniqueIDband);
//DEADCODE DAW 28/03/99 		newac->uniqueID.count=uniqueID;
//DEADCODE DAW 28/03/99 		//UniqueID is not registered at this point intentionally.
//DEADCODE DAW 28/03/99 		newac->nationality=nationality;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		newac->classtype=Plane_Type_Translate[type]_;
//DEADCODE DAW 28/03/99 		if (shape)
//DEADCODE DAW 28/03/99 			newac->shape=shape;
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			newac->shape=newac->classtype->visible;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		newac->hdg=hpr[0];										//JIM 21Oct96
//DEADCODE DAW 28/03/99 		newac->pitch=hpr[1];									//JIM 21Oct96
//DEADCODE DAW 28/03/99 		newac->roll=hpr[2];										//JIM 21Oct96
//DEADCODE DAW 28/03/99   		newac->fly.rpm = 1150;									//JIM 21Oct96
//DEADCODE DAW 28/03/99 		newac->fly.thrustpercent = 100;							//JIM 21Oct96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (movecode>AUTO_COMBAT)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 //DeadCode RDH 01Nov96 			Manual_Pilot.InitManualPilot(newac);				//JIM 21Oct96
//DEADCODE DAW 28/03/99 			newac->movecode=AUTO_COMBAT;						//JIM 21Oct96
//DEADCODE DAW 28/03/99 			newac->ai.manoeuvre=(MANOEUVRE)(movecode-AUTO_COMBAT);//JIM 21Oct96
//DEADCODE DAW 28/03/99 			newac->ai.manoeuvre=MANOEUVRE_SELECT;				//rdh temp 3/4/98
//DEADCODE DAW 28/03/99 //DeadCode JIM 11Sep96 			newac->manoeuvretime=0;
//DEADCODE DAW 28/03/99 //DeadCode JIM 11Sep96 			newac->ai.ManStep=PHASE0;							//RDH 12Mar96
//DEADCODE DAW 28/03/99 //DeadCode JIM 11Sep96 			newac->roll = ANGLES_0Deg;							//RDH 05May96
//DEADCODE DAW 28/03/99 //DeadCode JIM 11Sep96 			newac->hdg = ANGLES_0Deg;							//RDH 05May96
//DEADCODE DAW 28/03/99 //DeadCode JIM 11Sep96 			newac->pitch = ANGLES_0Deg;							//RDH 05May96
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			newac->movecode=movecode;
//DEADCODE DAW 28/03/99 			newac->ai.manoeuvre=MANOEUVRE_SELECT;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		newac->manoeuvretime=0;									//JIM 11Sep96
//DEADCODE DAW 28/03/99 		newac->ai.ManStep=PHASE0;								//JIM 11Sep96
//DEADCODE DAW 28/03/99 		newac->slowdownleader=FALSE;
//DEADCODE DAW 28/03/99 		newac->information=FALSE;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		newac->ai.skill=SkillType(( GR_GlobalSkillMin*SKILL_HERO + (GR_GlobalSkillMax-GR_GlobalSkillMin)*skill )
//DEADCODE DAW 28/03/99 									* (Save_Data.autopilotskill+1)
//DEADCODE DAW 28/03/99 									/ (SKILL_HERO*3)) ;
//DEADCODE DAW 28/03/99 //DeadCode DAW 26Sep96 		//cheep tacky cludge alert!!!!							//PD 25Sep96
//DEADCODE DAW 28/03/99 //DeadCode DAW 26Sep96 		newac->ai.skill=0;//skill + (Save_Data.autopilotskill * 2);	//RDH 19Aug96
//DEADCODE DAW 28/03/99 //DeadCode DAW 26Sep96 		//cheep tacky cludge alert!!!!							//PD 25Sep96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		newac->ai.morale=morale;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //temp for flight model tuning, rdh
//DEADCODE DAW 28/03/99 		newac->ai.morale=MORALE_POOR; 
//DEADCODE DAW 28/03/99 		newac->ai.character=character;
//DEADCODE DAW 28/03/99 		newac->ai.leaderaction=nextleadact;
//DEADCODE DAW 28/03/99 		newac->ai.followeraction=nextfollact;
//DEADCODE DAW 28/03/99 		newac->ai.tellleader=FALSE;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		(UWord&)cols[COLS_DAMAGE]=damage;
//DEADCODE DAW 28/03/99 		(UWord&)cols[COLS_BOMBS]=bombs;
//DEADCODE DAW 28/03/99 		//damage
//DEADCODE DAW 28/03/99 		if (tmptarget==IllegalSepID)
//DEADCODE DAW 28/03/99 			newac->ai.unfriendly=NULL;
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			setpointer((ItemBase**)&newac->ai.unfriendly,tmptarget);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (tmpattacker==IllegalSepID || formpos!=0)
//DEADCODE DAW 28/03/99 			newac->ai.attacker=NULL;
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			setpointer((ItemBase**)&newac->ai.attacker,tmpattacker);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (homebase==IllegalSepID)
//DEADCODE DAW 28/03/99 			newac->ai.homebase=NULL;
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			setpointer((ItemBase**)&newac->ai.homebase,homebase);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (tmpleader==IllegalSepID)
//DEADCODE DAW 28/03/99 			newac->fly.leadflight=NULL;
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			setpointer((ItemBase**)&newac->fly.leadflight,tmpleader);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		newac->fly.nextflight=NULL;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (Three_Dee.livelist)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			DOLAUNCHER_PTR d=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos(newac->shape,0);
//DEADCODE DAW 28/03/99 			if ( d && (d->lnchrtype & LT_MASK) == LT_MOVEGUN )
//DEADCODE DAW 28/03/99 				*Three_Dee.livelist+=newac;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //DeadCode JIM 21Oct96 		newac->hdg=hpr[0];
//DEADCODE DAW 28/03/99 //DeadCode JIM 21Oct96 		newac->pitch=hpr[1];
//DEADCODE DAW 28/03/99 //DeadCode JIM 21Oct96 		newac->roll=hpr[2];
//DEADCODE DAW 28/03/99 //DeadCode JIM 21Oct96   		newac->fly.rpm = 1150;									//RJS 02Jul96
//DEADCODE DAW 28/03/99 //DeadCode JIM 21Oct96 		newac->fly.thrustpercent = 100;
//DEADCODE DAW 28/03/99 //moved to initmanualpilot										//RDH 19Oct96
//DEADCODE DAW 28/03/99 //DeadCode RDH 19Oct96 		newac->fly.vel_cms = 	newac->vel * 10;					//RDH 08Apr96
//DEADCODE DAW 28/03/99 //DeadCode RDH 19Oct96 		newac->fly.vel_mms = 	newac->vel * 100;				//RDH 02May96
//DEADCODE DAW 28/03/99 //DeadCode RDH 19Oct96 		newac->fly.rollrate = ANGLES_0Deg;							//RDH 08Apr96
//DEADCODE DAW 28/03/99 //DeadCode RDH 19Oct96 		newac->fly.turnrate = ANGLES_0Deg;							//RDH 08Apr96
//DEADCODE DAW 28/03/99 //DeadCode RDH 19Oct96 		newac->fly.pitchrate = ANGLES_0Deg;							//RDH 08Apr96
//DEADCODE DAW 28/03/99 //DeadCode RDH 19Oct96 		newac->fly.yawrate = ANGLES_0Deg;						//RDH 30Apr96
//DEADCODE DAW 28/03/99 		return (Bool)(tmpleader!=IllegalSepID);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_airformlead
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 AirStrucPtr	Persons2::toplevel_airformlead
//DEADCODE DAW 28/03/99 						(	string	&hold,
//DEADCODE DAW 28/03/99 							PosCtrl&	position,
//DEADCODE DAW 28/03/99 							UniqueID wpref,		//route to use
//DEADCODE DAW 28/03/99 							DutyType	dutytype,
//DEADCODE DAW 28/03/99 							FormationTypeIndex formtype)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 UByte			cols[COLS_ALL]={0};
//DEADCODE DAW 28/03/99 AirStrucPtr	newac=new AirStruc;
//DEADCODE DAW 28/03/99 	if(midlevel_AirformData(hold,newac,(FormationIndex) 0,cols))
//DEADCODE DAW 28/03/99 	{	//I was going to find the true leader and the proper formation index
//DEADCODE DAW 28/03/99 		//just here, but instead I have decided to put that burden in body_airwinglead
//DEADCODE DAW 28/03/99 		AirStrucPtr	leaditem=newac->fly.leadflight;
//DEADCODE DAW 28/03/99 	return(body_airwinglead(newac,position,wpref,dutytype,formtype,leaditem,cols));
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	elser
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		//add to ac lists
//DEADCODE DAW 28/03/99 		//register UID - As this is a true leader, the given UID is fine!
//DEADCODE DAW 28/03/99 		//need better code here to calc usage from homebase
//DEADCODE DAW 28/03/99 		logUID(newac);
//DEADCODE DAW 28/03/99 		if (firstobject==IllegalSepID)
//DEADCODE DAW 28/03/99 			firstobject=newac->uniqueID.count;
//DEADCODE DAW 28/03/99 		//find position and add to world						//JIM 05Aug96
//DEADCODE DAW 28/03/99 		setpointer((ItemBasePtr*)&newac->waypoint,wpref);		//JIM 05Aug96
//DEADCODE DAW 28/03/99 		newac->duty=dutytype;									//JIM 05Aug96
//DEADCODE DAW 28/03/99 		newac->formation=formtype;
//DEADCODE DAW 28/03/99 		newac->formpos=FormationIndexMIN;						//RDH 16Apr96
//DEADCODE DAW 28/03/99 		newac->fly.originalformpos=FormationIndexMIN;						//RDH 16Apr96
//DEADCODE DAW 28/03/99 		if (setposition(newac,position,TRUE))						//RDH 17Jun96
//DEADCODE DAW 28/03/99 		{	//means was under ground!
//DEADCODE DAW 28/03/99 			newac->movecode=AUTO_TAKEOFF;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 //	 	newac->fly.mainfuel = 	newac->classtype->maxintfuel;	//JIM 05Aug96
//DEADCODE DAW 28/03/99 //	 	newac->fly.auxfuel = 	0;								//JIM 05Aug96
//DEADCODE DAW 28/03/99 		if (newac->ai.homebase)									//JIM 05Aug96
//DEADCODE DAW 28/03/99 		{														//JIM 05Aug96
//DEADCODE DAW 28/03/99 			newac->InterceptandRange(newac->ai.homebase);		//JIM 05Aug96
//DEADCODE DAW 28/03/99 			int time = MULDIVSIN(newac->Range,10,newac->classtype->cruisevel);	//all centiseconds//JIM 05Aug96
//DEADCODE DAW 28/03/99 //			if (time<4*SECSPERHR*SECS100)						//JIM 05Aug96
//DEADCODE DAW 28/03/99 //				newac->fly.mainfuel -= 	time*newac->classtype->fuelcruise;//JIM 05Aug96
//DEADCODE DAW 28/03/99 		}														//JIM 05Aug96
//DEADCODE DAW 28/03/99 //DeadCode RDH 30Sep96   		if (Land_Scape.GetGroundLevel(newac) >= newac->World.Y)		//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode RDH 30Sep96 		{
//DEADCODE DAW 28/03/99 //DeadCode RDH 30Sep96 			newac->vel = 0;										//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode RDH 30Sep96 			newac->fly.vel_cms = 	newac->vel * 10;			//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode RDH 30Sep96 			newac->fly.vel_mms = 	newac->vel * 100;			//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode RDH 30Sep96 		}
//DEADCODE DAW 28/03/99 		setfolloweroffset(newac);								//RDH 16Apr96
//DEADCODE DAW 28/03/99 //DeadCode RDH 17Jun96 		setposition(newac,position,TRUE);						//RDH 16Apr96
//DEADCODE DAW 28/03/99  		if (newac->pitch == ANGLES_180Deg)						//RDH 16Apr96
//DEADCODE DAW 28/03/99  			SetAngles (newac);									//RDH 16Apr96
//DEADCODE DAW 28/03/99 		Colour_Rule_List[colourrule](newac,newac->formpos,cols);			//RDH 16Apr96
//DEADCODE DAW 28/03/99 //		if (newac->movecode==AUTO_COMBAT)						//RDH 01Nov96
//DEADCODE DAW 28/03/99 //		{
//DEADCODE DAW 28/03/99 //			Manual_Pilot.InitManualPilotSub(newac);	
//DEADCODE DAW 28/03/99 //			Manual_Pilot.InitAircraft (newac, FALSE);			//ARM 01May97
//DEADCODE DAW 28/03/99 //		}else
//DEADCODE DAW 28/03/99 //			Manual_Pilot.InitAircraft (newac, TRUE);			//ARM 01May97
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (newac==Manual_Pilot.ControlledAC2)
//DEADCODE DAW 28/03/99 			  viewpoint->SetToPiloted(newac);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		newac->fly.pModel->SetGearAnimPos(ANIM_GEAR_UP);		//RJS 08May98
//DEADCODE DAW 28/03/99 		newac->AddToList();
//DEADCODE DAW 28/03/99 	return(newac);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_airfollower
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 AirStrucPtr	Persons2::toplevel_airfollower
//DEADCODE DAW 28/03/99 						(	string	&hold,
//DEADCODE DAW 28/03/99 							PosCtrl&	position,
//DEADCODE DAW 28/03/99 							UniqueID wpref,		//route to use
//DEADCODE DAW 28/03/99 							DutyType	dutytype,
//DEADCODE DAW 28/03/99 							FormationTypeIndex formtype,
//DEADCODE DAW 28/03/99 	   						FormationIndex formindex,//only used for {list
//DEADCODE DAW 28/03/99 							AirStrucPtr	lastac)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 UByte			cols[COLS_ALL]={0};
//DEADCODE DAW 28/03/99 AirStrucPtr	newac=new AirStruc;
//DEADCODE DAW 28/03/99 	midlevel_AirformData(hold,newac,formindex,cols);
//DEADCODE DAW 28/03/99 //ok.. need to insert this aircraft after the lastac.
//DEADCODE DAW 28/03/99 //I want to ensure that lastac is completely valid, though
//DEADCODE DAW 28/03/99 	if (lastac->leader)	lastac=(AirStrucPtr)lastac->leader;
//DEADCODE DAW 28/03/99 	assert ((lastac->leader==NULL)&&("wing leader should be unique, not chained!"));
//DEADCODE DAW 28/03/99 //now on leadac of formation
//DEADCODE DAW 28/03/99 	newac->leader=*lastac;
//DEADCODE DAW 28/03/99 	newac->follower=NULL;
//DEADCODE DAW 28/03/99 	while (lastac->follower)	lastac=(AirStrucPtr)lastac->follower;
//DEADCODE DAW 28/03/99 //now on last ac in formation - get next formation position
//DEADCODE DAW 28/03/99 	formindex=lastac->formpos+(InWing)1;
//DEADCODE DAW 28/03/99 	lastac->follower=newac;
//DEADCODE DAW 28/03/99 //	newac->fly.mainfuel = 	lastac->fly.mainfuel; 	
//DEADCODE DAW 28/03/99 // 	newac->fly.auxfuel = 	0;								//JIM 05Aug96
//DEADCODE DAW 28/03/99 //now point to overall leader
//DEADCODE DAW 28/03/99 	if (lastac->fly.leadflight)	lastac=lastac->fly.leadflight;
//DEADCODE DAW 28/03/99 	assert((lastac->fly.leadflight==NULL)&&("flight leader should be unique, not chained!"));
//DEADCODE DAW 28/03/99 	newac->fly.leadflight=lastac;
//DEADCODE DAW 28/03/99 	//add to ac lists
//DEADCODE DAW 28/03/99 	//register UID
//DEADCODE DAW 28/03/99 	if (ConvertPtrUID(newac->uniqueID.count))
//DEADCODE DAW 28/03/99 		newac->uniqueID.count=assignuid(getbandfromUID(newac->uniqueID.count));
//DEADCODE DAW 28/03/99 	logUID(newac);
//DEADCODE DAW 28/03/99 	//find position and add to world
//DEADCODE DAW 28/03/99 	setpointer((ItemBasePtr*)&newac->waypoint,wpref);
//DEADCODE DAW 28/03/99 	newac->duty=dutytype;
//DEADCODE DAW 28/03/99 	newac->formation=formtype;
//DEADCODE DAW 28/03/99 	newac->formpos=formindex;
//DEADCODE DAW 28/03/99 	newac->fly.originalformpos=formindex;						//RDH 12Dec96
//DEADCODE DAW 28/03/99 	newac->fly.comefrommap = FALSE;								//RDH 20Nov96
//DEADCODE DAW 28/03/99 	newac->fly.alreadylanded = FALSE;								//RDH 20Nov96
//DEADCODE DAW 28/03/99 		if (newac->pitch == ANGLES_180Deg)						//RDH 16Apr96
//DEADCODE DAW 28/03/99 			SetAngles (newac);									//RDH 16Apr96
//DEADCODE DAW 28/03/99 //rdh		if (newac->movecode==AUTO_COMBAT)						//RDH 01Nov96
//DEADCODE DAW 28/03/99 //			Manual_Pilot.InitManualPilotSub(newac);				//RDH 01Nov96
//DEADCODE DAW 28/03/99 		Colour_Rule_List[colourrule](newac,formindex,cols);			//RDH 16Apr96
//DEADCODE DAW 28/03/99 		position.pos = *setfolloweroffset(newac);				//RDH 16Apr96
//DEADCODE DAW 28/03/99 		setposition(newac,position,TRUE);						//RDH 16Apr96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96   		if (Land_Scape.GetGroundLevel(newac) >= newac->World.Y)		//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 		{
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 			newac->vel = 0;										//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 			newac->fly.vel_cms = 	newac->vel * 10;					//RDH 08Apr96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 			newac->fly.vel_mms = 	newac->vel * 100;				//RDH 02May96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 		}
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	setposition(newac,position,TRUE);
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	setfolloweroffset(newac);
//DEADCODE DAW 28/03/99 	newac->AddToList();
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	return(newac);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_airwinglead
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Dec 1995
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 AirStrucPtr		Persons2::toplevel_airwinglead
//DEADCODE DAW 28/03/99 						(	string	&hold,
//DEADCODE DAW 28/03/99 							PosCtrl&	position,
//DEADCODE DAW 28/03/99 							UniqueID wpref,		//route to use
//DEADCODE DAW 28/03/99 							DutyType	dutytype,
//DEADCODE DAW 28/03/99 							FormationTypeIndex formtype,
//DEADCODE DAW 28/03/99 	   						FormationIndex formindex,
//DEADCODE DAW 28/03/99 							AirStrucPtr	lastac)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UByte			cols[COLS_ALL]={0};
//DEADCODE DAW 28/03/99 AirStrucPtr	newac=new AirStruc;
//DEADCODE DAW 28/03/99 	midlevel_AirformData(hold,newac,formindex,cols);
//DEADCODE DAW 28/03/99 //ok.. need to insert this aircraft after the lastac.
//DEADCODE DAW 28/03/99 //I want to ensure that lastac is completely valid, though
//DEADCODE DAW 28/03/99 //now on leadac of formation
//DEADCODE DAW 28/03/99 	return(body_airwinglead(newac,position,wpref,dutytype,formtype,lastac,cols));
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		body_airwinglead
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Mon 22 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 AirStrucPtr	Persons2::body_airwinglead(	AirStrucPtr	newac,
//DEADCODE DAW 28/03/99 										PosCtrl&	position,
//DEADCODE DAW 28/03/99 										UniqueID wpref,		//route to use
//DEADCODE DAW 28/03/99 										DutyType	dutytype,
//DEADCODE DAW 28/03/99 										FormationTypeIndex formtype,
//DEADCODE DAW 28/03/99 										AirStrucPtr	lastac,
//DEADCODE DAW 28/03/99 										UByte* cols)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	newac->leader=NULL;
//DEADCODE DAW 28/03/99 	newac->follower=NULL;
//DEADCODE DAW 28/03/99 //now point to overall leader
//DEADCODE DAW 28/03/99 	if (lastac->fly.leadflight)	lastac=lastac->fly.leadflight;
//DEADCODE DAW 28/03/99 	assert((lastac->fly.leadflight==NULL)&&("flight leader should be unique, not chained!"));
//DEADCODE DAW 28/03/99 	newac->fly.leadflight=lastac;
//DEADCODE DAW 28/03/99 //now point to latest flight leader
//DEADCODE DAW 28/03/99 	while (lastac->fly.nextflight) lastac=lastac->fly.nextflight;
//DEADCODE DAW 28/03/99 	lastac->fly.nextflight=newac;
//DEADCODE DAW 28/03/99 //	newac->fly.mainfuel = 	lastac->fly.mainfuel; 	
//DEADCODE DAW 28/03/99 // 	newac->fly.auxfuel = 	0;								//JIM 05Aug96
//DEADCODE DAW 28/03/99 	//don't care about input formation number 'cos poss to link in extra flights
//DEADCODE DAW 28/03/99 FormationIndex
//DEADCODE DAW 28/03/99 	formindex=lastac->formpos+(InForm)1;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	//add to ac lists
//DEADCODE DAW 28/03/99 	//register UID
//DEADCODE DAW 28/03/99 	if (ConvertPtrUID(newac->uniqueID.count))
//DEADCODE DAW 28/03/99 		newac->uniqueID.count=assignuid(getbandfromUID(newac->uniqueID.count));
//DEADCODE DAW 28/03/99 	logUID(newac);
//DEADCODE DAW 28/03/99 	//find position and add to world
//DEADCODE DAW 28/03/99 	setpointer((ItemBasePtr*)&newac->waypoint,wpref);
//DEADCODE DAW 28/03/99 	newac->duty=dutytype;
//DEADCODE DAW 28/03/99 	newac->formation=formtype;
//DEADCODE DAW 28/03/99 	newac->formpos=formindex;
//DEADCODE DAW 28/03/99 	newac->fly.originalformpos=formindex;						//RDH 12Dec96
//DEADCODE DAW 28/03/99 	newac->fly.comefrommap = FALSE;								//RDH 25Nov96
//DEADCODE DAW 28/03/99 	newac->fly.alreadylanded = FALSE;							//RDH 25Nov96
//DEADCODE DAW 28/03/99 		if (newac->pitch == ANGLES_180Deg)						//DAW 30Apr96
//DEADCODE DAW 28/03/99 			SetAngles (newac);									//DAW 30Apr96
//DEADCODE DAW 28/03/99 //rdh		if (newac->movecode==AUTO_COMBAT)						//RDH 01Nov96
//DEADCODE DAW 28/03/99 //			Manual_Pilot.InitManualPilotSub(newac);				//RDH 01Nov96
//DEADCODE DAW 28/03/99 		Colour_Rule_List[colourrule](newac,formindex,cols);			//RDH 16Apr96
//DEADCODE DAW 28/03/99 		position.pos = *setfolloweroffset(newac);				//RDH 16Apr96
//DEADCODE DAW 28/03/99 		setposition(newac,position,TRUE);						//RDH 16Apr96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96   		if (Land_Scape.GetGroundLevel(newac) >= newac->World.Y)		//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 		{
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 			newac->vel = 0;										//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 			newac->fly.vel_cms = 	newac->vel * 10;			//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 			newac->fly.vel_mms = 	newac->vel * 100;			//RDH 21Jun96
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Sep96 		}
//DEADCODE DAW 28/03/99 	newac->AddToList();
//DEADCODE DAW 28/03/99 	return(newac);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		toplevel_attitude
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Thu 18 Jan 1996	JIM 01Apr96
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::toplevel_attitude(string& bfieldptr,ANGLES* hpr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 ItemBasePtr		tmpitem=NULL;
//DEADCODE DAW 28/03/99 UniqueID	tmpUID=IllegalSepID;
//DEADCODE DAW 28/03/99 SLong	TmpRange;
//DEADCODE DAW 28/03/99 ANGLES	HTmp=ANGLES_0Deg,PTmp=ANGLES_0Deg;
//DEADCODE DAW 28/03/99 Bool	HSet=FALSE,PSet=FALSE;
//DEADCODE DAW 28/03/99 int		loopcount=getloopcount(bfieldptr);
//DEADCODE DAW 28/03/99 	hpr[0]=
//DEADCODE DAW 28/03/99 		hpr[1]=
//DEADCODE DAW 28/03/99 			hpr[2]=
//DEADCODE DAW 28/03/99 				ANGLES_0Deg;
//DEADCODE DAW 28/03/99 	
//DEADCODE DAW 28/03/99 	while (loopcount--)
//DEADCODE DAW 28/03/99 		switch (*(bfieldptr++))
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99  		case T_target:
//DEADCODE DAW 28/03/99 			tmpUID=getobjectbyUID(bfieldptr);
//DEADCODE DAW 28/03/99 			tmpitem=ConvertPtrUID(tmpUID);
//DEADCODE DAW 28/03/99 			if (tmpitem && tmpitem->Status.size>=HPSize)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				HTmp=((hpitem*) *tmpitem)->hdg;
//DEADCODE DAW 28/03/99 				PTmp=((hpitem*) *tmpitem)->pitch;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				_Error.EmitSysErr("Target to attitude doesn't have angles to copy!");
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		case T_icpt:
//DEADCODE DAW 28/03/99 			pos_icpt(bfieldptr,PTmp,HTmp,TmpRange);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99  		case T_bearing:
//DEADCODE DAW 28/03/99  		case T_hdg:
//DEADCODE DAW 28/03/99 			HTmp+=(Angles)evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 			HSet=TRUE;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99  		case T_pitch:
//DEADCODE DAW 28/03/99 			PTmp+=(Angles)evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 			PSet=TRUE;
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99  		case T_roll:
//DEADCODE DAW 28/03/99 			hpr[2]=(Angles)evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 		break;
//DEADCODE DAW 28/03/99 		default:
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Type of symbol not valid in BattleField Airformdata");//JIM 28Mar96
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		if (HSet&&PSet)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			hpr[0]=HTmp;
//DEADCODE DAW 28/03/99 			hpr[1]=PTmp;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		else	
//DEADCODE DAW 28/03/99 		{	//generate some defaults - note that I don't know the first waypoint.
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			//override as necessary
//DEADCODE DAW 28/03/99 			if (HSet)
//DEADCODE DAW 28/03/99 				hpr[0]=HTmp;
//DEADCODE DAW 28/03/99 			elseif (PSet)
//DEADCODE DAW 28/03/99 				hpr[1]=PTmp;
//DEADCODE DAW 28/03/99 		}	//if neither set, then roll is honoured anyway if not 180 deg!
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		setposition
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Fri 12 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Fills in the position X,Y,Z fields of an item
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		PosCtrl	- definition of position
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns		TRUE if ground correction applied
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 Bool		Persons2::setposition(ItemBasePtr	tmpitem,PosCtrl &position,Bool addwhenfilled)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	tmpitem->World=position.pos;
//DEADCODE DAW 28/03/99 	if (tmpitem->Status.size==WayPointSize)
//DEADCODE DAW 28/03/99 		if (	position.absaxes!=position.ABS_ABS
//DEADCODE DAW 28/03/99 			&&	(ULong)position.refUID.count<IllegalSepID
//DEADCODE DAW 28/03/99 			)
//DEADCODE DAW 28/03/99 			logworldcopy(tmpitem,position.refUID.count,addwhenfilled);
//DEADCODE DAW 28/03/99 		else;
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	if (position.absaxes!=position.ABS_ABS)
//DEADCODE DAW 28/03/99 		if ((ULong)position.refUID.count<IllegalSepID)
//DEADCODE DAW 28/03/99 			logworldcopy(tmpitem,position.refUID.count,addwhenfilled);
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("Could not resolve stored position.");
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		if (addwhenfilled)
//DEADCODE DAW 28/03/99 			if (tmpitem->Status.size!=WayPointSize)
//DEADCODE DAW 28/03/99 	 			AddToWorld(*tmpitem);
//DEADCODE DAW 28/03/99 		if (tmpitem->World.Y < 0)								//RDH 17Jun96
//DEADCODE DAW 28/03/99 		{														//RDH 17Jun96
//DEADCODE DAW 28/03/99 			tmpitem->World.Y =  Land_Scape.GetGroundLevel(tmpitem)//RDH 17Jun96
//DEADCODE DAW 28/03/99 										- tmpitem->World.Y;		//RDH 17Jun96
//DEADCODE DAW 28/03/99 		//PAUL'S NEW ROUTINE RETURNS DELTA TO GROUND
//DEADCODE DAW 28/03/99 		//	This is delta from given alt to ground level
//DEADCODE DAW 28/03/99 		//  given is N below sea level
//DEADCODE DAW 28/03/99 		//	I want abs above sea = ground + |given| = ground -given
//DEADCODE DAW 28/03/99 		// this is paul's returned value!!! (Ok, so I'm lazy! :-)
//DEADCODE DAW 28/03/99 		//	position.pos.Y =
//DEADCODE DAW 28/03/99 		//		tmpitem->World.Y = -Land_Scape.GetGroundDelta(tmpitem);
//DEADCODE DAW 28/03/99 			if (position.pos.Y<-600)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				position.pos.Y =tmpitem->World.Y;
//DEADCODE DAW 28/03/99 				return(FALSE);
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				position.pos.Y =tmpitem->World.Y;
//DEADCODE DAW 28/03/99 				return(TRUE);
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	return (FALSE);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		setpointer
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Fri 12 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Set the pointer to the item with the uid.
//DEADCODE DAW 28/03/99 //				If the item does not yet exist then the 
//DEADCODE DAW 28/03/99 //				pointer is noted until the UID is available.
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void		Persons2::setpointer(ItemBasePtr	*targitemptr,UniqueID	srcuid)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if ((*targitemptr=ConvertPtrUID(srcuid))==0)
//DEADCODE DAW 28/03/99 		logpointercopy(targitemptr,srcuid);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		searchtree
//DEADCODE DAW 28/03/99 //Author		Robert Slater
//DEADCODE DAW 28/03/99 //Date			Tue 13 Feb 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 UidNode**	Persons2::searchtree(UniqueID srcuid,UidNode **nextnode)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UidNode		*currentnode,
//DEADCODE DAW 28/03/99 				**currnodeptr=nextnode;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		while(*nextnode)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			currnodeptr=nextnode;
//DEADCODE DAW 28/03/99 			currentnode = *nextnode;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			if (srcuid == currentnode->uidattack)
//DEADCODE DAW 28/03/99 				return(nextnode);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			if (srcuid < currentnode->uidattack)
//DEADCODE DAW 28/03/99 				nextnode = &currentnode->less;
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				nextnode = &currentnode->more;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		return(currnodeptr);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		adduidrequest
//DEADCODE DAW 28/03/99 //Author		Robert Slater
//DEADCODE DAW 28/03/99 //Date			Tue 13 Feb 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::adduidrequest(ItemBasePtr *trgitemptr,UniqueID srcuid)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UidNode		*newnode = new UidNode;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	newnode->uidattack = srcuid;
//DEADCODE DAW 28/03/99 	newnode->attackerptr = trgitemptr;
//DEADCODE DAW 28/03/99 	newnode->request = ptrcopy;
//DEADCODE DAW 28/03/99 	newnode->less = NULL;
//DEADCODE DAW 28/03/99 	newnode->more = NULL;
//DEADCODE DAW 28/03/99 	adduidrequest(newnode,srcuid);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 void	Persons2::adduidrequest(ItemBasePtr trgitemptr,UniqueID srcuid,UILogType request)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UidNode		*newnode = new UidNode;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	newnode->uidattack = srcuid;
//DEADCODE DAW 28/03/99 	newnode->posptr = trgitemptr;
//DEADCODE DAW 28/03/99 	newnode->request = request;
//DEADCODE DAW 28/03/99 	newnode->less = NULL;
//DEADCODE DAW 28/03/99 	newnode->more = NULL;
//DEADCODE DAW 28/03/99 	adduidrequest(newnode,srcuid);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	Persons2::adduidrequest(UidNode *newnode,UniqueID srcuid)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UidNode	  **foundnode, *thenode;
//DEADCODE DAW 28/03/99 	if (rootuidnode == NULL)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		rootuidnode = newnode;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		// Search down the tree to correct node...
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		foundnode = searchtree(srcuid);
//DEADCODE DAW 28/03/99 		thenode = *foundnode;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		// Select branch...
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (srcuid == thenode->uidattack)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			// Add to the greater node, and shuffle if it is occupied
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			newnode->more = thenode->more;
//DEADCODE DAW 28/03/99 			thenode->more = newnode;
//DEADCODE DAW 28/03/99 			
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			// Must be less than or greater than, so no problem
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			if (srcuid < thenode->uidattack)
//DEADCODE DAW 28/03/99 				thenode->less = newnode;
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				thenode->more = newnode;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		logpointercopy
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Fri 12 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Logs that the given item pointer needs fixing up when the
//DEADCODE DAW 28/03/99 //				given unique id item is loaded.
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::logpointercopy(ItemBasePtr *trgitemptr,UniqueID srcuid)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UILogType	request = ptrcopy;
//DEADCODE DAW 28/03/99    
//DEADCODE DAW 28/03/99 	adduidrequest(trgitemptr,srcuid);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	*trgitemptr=(ItemBasePtr)-1;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		logworldcopy
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Mon 8 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Logs data transfer to happen when source item is loaded
//DEADCODE DAW 28/03/99 //				If 'addwhenfilled' is set then item is added to world when data
//DEADCODE DAW 28/03/99 //				transfer is complete.
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::logworldcopy(ItemBasePtr targitem,UniqueID srcUID,Bool	addwhenfilled)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UILogType	request = worldcopy;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (addwhenfilled)
//DEADCODE DAW 28/03/99 		request = addworldcopy;
//DEADCODE DAW 28/03/99 	if (srcUID==0)
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Asked for zero UID source");
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	adduidrequest(targitem,srcUID,request);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		AddToWorld
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Mon 8 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void		Persons2::AddToWorld(ItemPtr	tmpitem)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99  	#pragma message("Persons2::AddToWorld - Don't forget to take this out!")
//DEADCODE DAW 28/03/99  //	if ((tmpitem->Status.size==AirStrucSize) || (tmpitem->shape == KIMPO))
//DEADCODE DAW 28/03/99  	{	//1M=10km	- .5m=5km
//DEADCODE DAW 28/03/99 //TempCode RDH 20Apr98  		tmpitem->World.X=(tmpitem->World.X&0x3ffff)+0x5000000;
//DEADCODE DAW 28/03/99 //TempCode RDH 20Apr98  		tmpitem->World.Z=(tmpitem->World.Z&0x3ffff)+0x3000000;
//DEADCODE DAW 28/03/99 //DeadCode DAW 28Apr98  		tmpitem->World.X=(tmpitem->World.X&0x3ffff)+0x2600000;
//DEADCODE DAW 28/03/99 //DeadCode DAW 28Apr98  		tmpitem->World.Z=(tmpitem->World.Z&0x3ffff)+0x5400000;
//DEADCODE DAW 28/03/99 //TempCode PD 17Jun98    		tmpitem->World.X=(tmpitem->World.X&0x3ffff)+0x2600000;
//DEADCODE DAW 28/03/99 //TempCode PD 17Jun98    		tmpitem->World.Z=(tmpitem->World.Z&0x3ffff)+0x5400000-0x200000-0x40000;
//DEADCODE DAW 28/03/99    		tmpitem->World.X=(tmpitem->World.X&0x3ffff)+0x2600000;
//DEADCODE DAW 28/03/99    		tmpitem->World.Z=(tmpitem->World.Z&0x3ffff)+0x5400000;//-0x200000-0x40000;
//DEADCODE DAW 28/03/99   		//tmpitem->World.X=(tmpitem->World.X&0x3ffff)+0x4600000;//0x3400000;
//DEADCODE DAW 28/03/99   		//tmpitem->World.Z=(tmpitem->World.Z&0x3ffff)+0x2800000;//0x5000000;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99  	}
//DEADCODE DAW 28/03/99 	myworld->AddToWorld(tmpitem);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 UniqueID	Persons2::getobjectbyUID(string	&bfieldptr)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UniqueID	tmpid = (UniqueID) evaluate(bfieldptr);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	assert (tmpid != -1);
//DEADCODE DAW 28/03/99 		return(tmpid);
//DEADCODE DAW 28/03/99 		
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //Old_Code DAW 09Feb96 	INT3();
//DEADCODE DAW 28/03/99 //DeadCode DAW 15Feb96 	throwtree(bfieldptr);
//DEADCODE DAW 28/03/99 //DeadCode DAW 15Feb96  	return(IllegalSepID);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 ItemBasePtr		Persons2::ConvertPtrUID(UniqueID tmpUID)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	return(pItem[tmpUID]);
//DEADCODE DAW 28/03/99 //Old_Code DAW 09Feb96 	INT3();
//DEADCODE DAW 28/03/99 //DeadCode DAW 15Feb96  	return(NULL);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 UniqueID	Persons2::assignuid(UniqueIDBand	tmpband)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	int			uidindex = -1;
//DEADCODE DAW 28/03/99 	int			count;
//DEADCODE DAW 28/03/99 	UniqueID	TempUID;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	for (count = 0; count < UIDTABLESIZE; count ++)
//DEADCODE DAW 28/03/99 		if (uidbandbase[count] == tmpband)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			uidindex = count;
//DEADCODE DAW 28/03/99 			break;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	TempUID = IllegalSepID;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (uidindex > -1)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		TempUID = (UniqueID) uidbandmin[uidindex];
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		uidbandmin[uidindex] = (UniqueID)(uidbandmin[uidindex] + 1);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (uidbandmin[uidindex] >= uidbandbase[uidindex+1])
//DEADCODE DAW 28/03/99 			_Error.EmitSysErr("UIDband table overlap!");
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99  	return (TempUID);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 UniqueIDBand	Persons2::getbandfromUID(UniqueID	tmpUID)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	int	i = UIDTABLESIZE;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	while (i--)
//DEADCODE DAW 28/03/99 		if (tmpUID >= uidbandbase[i])							//RDH 11Oct96
//DEADCODE DAW 28/03/99 			return(uidbandbase[i]);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99  	return (IllegalBAND);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	Persons2::logUID(ItemBasePtr	selecteditem)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	UidNode			*swapnode, **foundnode, *thenode, *nextnode, **rightmostnode;
//DEADCODE DAW 28/03/99 	UniqueID		theuid;
//DEADCODE DAW 28/03/99 	Bool			finished = FALSE;
//DEADCODE DAW 28/03/99 	ItemBasePtr		*attackerptr;
//DEADCODE DAW 28/03/99 	UILogType	 	request;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	theuid = selecteditem->uniqueID.count;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	assert(pItem[theuid]==NULL&&"UID already used!");
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	assert(pItem[theuid]==0&&"Reused!");
//DEADCODE DAW 28/03/99 	pItem[theuid] = selecteditem;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	while(!finished)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		foundnode = searchtree(theuid);
//DEADCODE DAW 28/03/99 		thenode = *foundnode;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		finished = TRUE;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (thenode)
//DEADCODE DAW 28/03/99 			if (thenode->uidattack == theuid)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				finished = FALSE;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				// Extract data...
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				request = thenode->request;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				switch (request)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 				case ptrcopy :
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					attackerptr = thenode->attackerptr;
//DEADCODE DAW 28/03/99 					*attackerptr = selecteditem;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				break;
//DEADCODE DAW 28/03/99 				case worldcopy :
//DEADCODE DAW 28/03/99 				case addworldcopy :
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					thenode->posptr->World.X =
//DEADCODE DAW 28/03/99 						thenode->posptr->World.X + selecteditem->World.X;
//DEADCODE DAW 28/03/99 					thenode->posptr->World.Y =
//DEADCODE DAW 28/03/99 						thenode->posptr->World.Y + selecteditem->World.Y;
//DEADCODE DAW 28/03/99 					thenode->posptr->World.Z =
//DEADCODE DAW 28/03/99 						thenode->posptr->World.Z + selecteditem->World.Z;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 					if (request == addworldcopy)
//DEADCODE DAW 28/03/99 						AddToWorld((ItemPtr) selecteditem);
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				break;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			
//DEADCODE DAW 28/03/99 				// Tidy tree...
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				nextnode = thenode->more;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				if (thenode->less)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					swapnode = thenode->less;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 					rightmostnode = searchtree(nextnode->uidattack,&swapnode);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 					(*rightmostnode)->more = nextnode;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				else
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					swapnode = thenode->more;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				*foundnode = swapnode;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				delete thenode;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		anyoutstanding
//DEADCODE DAW 28/03/99 //Author		Robert Slater
//DEADCODE DAW 28/03/99 //Date			Thu 15 Feb 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Checks if any outstanding UIDs on the tree.
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 Bool	Persons2::anyoutstanding()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (rootuidnode == NULL)
//DEADCODE DAW 28/03/99 		return(FALSE);
//DEADCODE DAW 28/03/99 	elser
//DEADCODE DAW 28/03/99 		return(TRUE);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		setangles
//DEADCODE DAW 28/03/99 //Author		R. Hyde 
//DEADCODE DAW 28/03/99 //Date			Mon 26 Feb 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::SetAngles (AirStrucPtr	newac)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (newac->roll == ANGLES_180Deg)
//DEADCODE DAW 28/03/99 		newac->roll = ANGLES_0Deg;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (newac->formpos == 0)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		newac->InterceptandRange (newac->FindDesPos ());
//DEADCODE DAW 28/03/99 		newac->pitch= newac->PitchIntercept;
//DEADCODE DAW 28/03/99 		newac->hdg	= newac->HdgIntercept;
//DEADCODE DAW 28/03/99 	}else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		newac->pitch = newac->fly.leadflight->pitch;
//DEADCODE DAW 28/03/99 		newac->hdg = newac->fly.leadflight->hdg;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	if (newac->vel == 0)											//RDH 04Sep96
//DEADCODE DAW 28/03/99 	{															//RDH 04Sep96
//DEADCODE DAW 28/03/99 		newac->fly.cpitch = ANGLES_0Deg;						//RDH 04Sep96
//DEADCODE DAW 28/03/99 	}else
//DEADCODE DAW 28/03/99 	{															//RDH 04Sep96
//DEADCODE DAW 28/03/99 		newac->fly.cpitch = newac->pitch;
//DEADCODE DAW 28/03/99 	}															//RDH 04Sep96
//DEADCODE DAW 28/03/99 	newac->fly.chdg = newac->hdg;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		setangles
//DEADCODE DAW 28/03/99 //Author		R. Hyde 
//DEADCODE DAW 28/03/99 //Date			Mon 26 Feb 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::SetAngles (FormationItemPtr	newmob)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (newmob->roll == ANGLES_180Deg)
//DEADCODE DAW 28/03/99 		newmob->roll = ANGLES_0Deg;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (newmob->formpos == 0)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		newmob->InterceptandRange (newmob->FindDesPos ());
//DEADCODE DAW 28/03/99 		newmob->pitch= newmob->PitchIntercept;
//DEADCODE DAW 28/03/99 		newmob->hdg	= newmob->HdgIntercept;
//DEADCODE DAW 28/03/99 	}else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		newmob->pitch = newmob->leader->pitch;
//DEADCODE DAW 28/03/99 		newmob->hdg = newmob->leader->hdg;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Procedure		GetFollower_xyz
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Author		R. Hyde 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Date			Mon 26 Feb 1996
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Description	
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Inputs		
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Returns	
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 void	GetFollower_xyz (AirStrucPtr	newac,SLong &x,SLong &y,SLong &z)
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 {
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	ANGLES	brg;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	SWord	sinbearing,cosbearing;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	SLong	range;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	SWord	formationtype;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	SWord	formationpos;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	formationtype = newac->formation; 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	formationpos = (newac->formpos&InFormMAX) - 1; 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	brg = newac->fly.leadflight->hdg + Aircraft_Formations [formationtype]->wingpos [formationpos].bearing;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	range = Aircraft_Formations [formationtype]->wingpos [formationpos].range;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	x = sinbearing	* range / ANGLES_FRACT;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	z = cosbearing	* range / ANGLES_FRACT;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	y = Aircraft_Formations [formationtype]->wingpos [formationpos].delta_alt;	
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 }
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Procedure		GetFlightLeader_xyz
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Author		R. Hyde 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Date			Mon 26 Feb 1996
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Description	
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Inputs		
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //Returns	
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 void	GetFlightLeader_xyz (AirStrucPtr	newac,SLong &x,SLong &y,SLong &z)
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 {
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	ANGLES	brg;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	SWord	sinbearing,cosbearing;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	SLong	range;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	SWord	formationtype;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	SWord	formationpos;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	formationtype = 0; 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	formationpos = (newac->formpos&InWingMAX); 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	formationpos = (formationpos/32); 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	brg = newac->fly.leadflight->hdg + Squadron_Formations [formationtype]->wingpos [formationpos].bearing;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	range = Squadron_Formations [formationtype]->wingpos [formationpos].range;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	x = sinbearing	* range / ANGLES_FRACT;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	z = cosbearing	* range / ANGLES_FRACT;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	y = Squadron_Formations [formationtype]->wingpos [formationpos].delta_alt;	
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 }
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		setfolloweroffset
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Mon 22 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Set the offset position for a follower.
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		newac->formpos
//DEADCODE DAW 28/03/99 //				If wing pos is non-zero then realive to leader
//DEADCODE DAW 28/03/99 //				If wing pos is zero then relative to leadflight
//DEADCODE DAW 28/03/99 //				newac->formation
//DEADCODE DAW 28/03/99 //				
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns		newac->world modified
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 COORDS3D*	Persons2::setfolloweroffset(FormationItemPtr	newmob)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (newmob->formpos != 0)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		newmob->GetFollower_xyz ( newmob->formation);					//RDH 17Jun96
//DEADCODE DAW 28/03/99 		return (&newmob->despos);
//DEADCODE DAW 28/03/99 	}elser
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		return (NULL);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 COORDS3D*	Persons2::setfolloweroffset(AirStrucPtr	newac)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	COORDS3D	*despos;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	if (newac->pitch == ANGLES_180Deg)
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 		SetAngles (newac);
//DEADCODE DAW 28/03/99 	newac->HdgIntercept=newac->hdg;
//DEADCODE DAW 28/03/99 	if (newac->formpos != 0)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		if (	(newac->leader && newac->leader->movecode == AUTO_TAKEOFF)
//DEADCODE DAW 28/03/99 			||	(newac->fly.leadflight && newac->fly.leadflight->movecode == AUTO_TAKEOFF)	)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			newac->pitch = newac->classtype->deckangle;			//JIM 04Dec96
//DEADCODE DAW 28/03/99 //DeadCode JIM 27Nov96 			newac->pitch=ANGLES_5Deg;
//DEADCODE DAW 28/03/99 			newac->movecode=AUTO_TAKEOFF;
//DEADCODE DAW 28/03/99 			newac->vel = 0;										//RDH 30Sep96
//DEADCODE DAW 28/03/99 			newac->fly.vel_cms = 	0;							//RDH 30Sep96
//DEADCODE DAW 28/03/99 //rdh			newac->fly.vel_mms = 	0;							//RDH 30Sep96
//DEADCODE DAW 28/03/99 			return (newac->PositionTakeOffWRTLeader ());
//DEADCODE DAW 28/03/99 		}else
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			if (newac->hdg!=newac->HdgIntercept)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				newac->hdg=newac->HdgIntercept;
//DEADCODE DAW 28/03/99 				newac->pitch=ANGLES_0Deg;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			return (newac->PositionWRTLeader ());
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	}elser
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		if (newac->movecode==AUTO_TAKEOFF)
//DEADCODE DAW 28/03/99 //DeadCode RDH 30Sep96 		if (Land_Scape.GetGroundLevel(newac) >= newac->World.Y)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 //DeadCode RDH 30Sep96 			newac->movecode=AUTO_TAKEOFF;
//DEADCODE DAW 28/03/99 //DeadCode RDH 02Aug96 			newac->hdg = Save_Data.winddirection + ANGLES_180Deg;							//RDH 05May96
//DEADCODE DAW 28/03/99 //DeadCode RDH 24Oct96 			newac->hdg = Save_Data.wind.direction;				//RDH 02Aug96
//DEADCODE DAW 28/03/99 			newac->hdg = MMC.wind.direction;				//RDH 02Aug96
//DEADCODE DAW 28/03/99 //DeadCode RDH 21Oct96 			newac->pitch = ANGLES_12Deg;
//DEADCODE DAW 28/03/99 //DeadCode JIM 04Dec96 			newac->pitch=ANGLES_5Deg;		//JIM 04Dec96
//DEADCODE DAW 28/03/99 			newac->pitch = newac->classtype->deckangle;			//JIM 04Dec96
//DEADCODE DAW 28/03/99 			newac->roll = ANGLES_0Deg;
//DEADCODE DAW 28/03/99 			newac->vel = 0;										//RDH 30Sep96
//DEADCODE DAW 28/03/99 			newac->fly.vel_cms = 	0;							//RDH 30Sep96
//DEADCODE DAW 28/03/99 //rdh			newac->fly.vel_mms = 	0;							//RDH 30Sep96
//DEADCODE DAW 28/03/99 		}	
//DEADCODE DAW 28/03/99 		return (NULL);											//RDH 17Jun96
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	if (newac->formpos&InWingMAX)								//RDH 23Feb96
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	{	
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 		GetFlightLeader_xyz (newac,x,y,z);
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96  		newac->World.X+= x;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	 	newac->World.Y+= y;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96  		newac->World.Z+= z;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //DeadCode RDH 26Feb96 		newac->World.X+=60*(newac->formpos&InWingMAX);			//RDH 23Feb96
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	}
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	if (newac->formpos&InFormMAX)								//RDH 23Feb96
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	{
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 		GetFollower_xyz (newac,x,y,z);
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	 	newac->World.X+= x;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96  		newac->World.Y+= y;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	 	newac->World.Z+= z;
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 //DeadCode RDH 26Feb96 		newac->World.Z+=1500*(newac->formpos&InFormMAX);						//RDH 23Feb96
//DEADCODE DAW 28/03/99 //DeadCode RDH 27Feb96 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		PossibleEvent
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 20 Mar 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Execute any event associated with this item
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 extern	ULong	GR_CWP,GR_CPP;
//DEADCODE DAW 28/03/99 void		Persons2::PossibleEvent(WorldStuff *worldptr,ItemBasePtr target,ItemBasePtr actor)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (target)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		FileNum	eventbf=INVALIDFILENUM;
//DEADCODE DAW 28/03/99 		EventRecPtr	evind=EventRec::eventbase;
//DEADCODE DAW 28/03/99 		while (evind)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			if (evind->attitem==target && Timer_Code.realtime>=evind->eventwstart)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				EventRecPtr	tmpnext=evind->eventlink;
//DEADCODE DAW 28/03/99 				//need start/window tests here!
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				//need to set GR_CPP,GR_CWP
//DEADCODE DAW 28/03/99 				GR_CWP=target->uniqueID.count;
//DEADCODE DAW 28/03/99 				GR_CPP=actor->uniqueID.count;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 				eventbf=ActionEvent(evind,mobileitem::currworld,target);
//DEADCODE DAW 28/03/99 				if (eventbf!=INVALIDFILENUM)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					lastbfloaded=eventbf;
//DEADCODE DAW 28/03/99 					lasttarg=target;
//DEADCODE DAW 28/03/99 					lastact=actor;
//DEADCODE DAW 28/03/99 //DeadCode JIM 12Aug96 					LoadSubPiece(worldptr,eventbf);
//DEADCODE DAW 28/03/99 //DeadCode JIM 12Aug96 					assert(!anyoutstanding()&&"Sub event not complete!");
//DEADCODE DAW 28/03/99 //DeadCode RDH 11Oct96 					if (Save_Data.gamedifficulty[GD_TACTICALRANGE])
//DEADCODE DAW 28/03/99 //DeadCode RDH 11Oct96 					{
//DEADCODE DAW 28/03/99 //DeadCode RDH 11Oct96 						Timer_Code.AccelToggle(FALSE);
//DEADCODE DAW 28/03/99 //DeadCode RDH 11Oct96 						Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);
//DEADCODE DAW 28/03/99 //DeadCode RDH 11Oct96 					}
//DEADCODE DAW 28/03/99 					return;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				evind=tmpnext;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				evind=evind->eventlink;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		if (lastbfloaded)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		 	LoadSubPiece(mobileitem::currworld,lastbfloaded);
//DEADCODE DAW 28/03/99 			if (	lasttarg->Status.size==WayPointSize
//DEADCODE DAW 28/03/99 				&&	((WayPointPtr)*lasttarg)->target
//DEADCODE DAW 28/03/99 				)
//DEADCODE DAW 28/03/99 				eventloglist->area=_Text.ConvSnip0(((WayPointPtr)*lasttarg)->target->uniqueID.count);
//DEADCODE DAW 28/03/99 			lastbfloaded=FIL_NULL;
//DEADCODE DAW 28/03/99 			if (anyoutstanding())
//DEADCODE DAW 28/03/99 				_Error.EmitSysErr("Unresolved UIDS! One is: %x",rootuidnode->uidattack);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //DeadCode JIM 22Oct96 NEVER WANT TO QUIT ACCEL HERE
//DEADCODE DAW 28/03/99 //DeadCode JIM 22Oct96 
//DEADCODE DAW 28/03/99 //DeadCode JIM 22Oct96 			if (Save_Data.gamedifficulty[GD_TACTICALRANGE])		//RDH 11Oct96
//DEADCODE DAW 28/03/99 //DeadCode JIM 22Oct96 			{
//DEADCODE DAW 28/03/99 //DeadCode JIM 22Oct96 				Timer_Code.AccelToggle(FALSE);
//DEADCODE DAW 28/03/99 //DeadCode JIM 22Oct96 				Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);
//DEADCODE DAW 28/03/99 //DeadCode JIM 22Oct96 			}
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Nov96 			AddMessage(UserMsg::TIME,TextSnip0MIN,
//DEADCODE DAW 28/03/99 //DeadCode JIM 30Nov96 				ConvertPtrUID(eventloglist->targetuid));
//DEADCODE DAW 28/03/99 			if (lasttarg)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				target=lasttarg;
//DEADCODE DAW 28/03/99 				lasttarg=NULL;
//DEADCODE DAW 28/03/99 				PossibleEvent(mobileitem::currworld,target,lastact);
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 		{	//Look for timed out events on player's waypoint	//JIM 14Aug96
//DEADCODE DAW 28/03/99 			MobileItemPtr a=*actor;
//DEADCODE DAW 28/03/99 			target=a->waypoint;
//DEADCODE DAW 28/03/99 			FileNum	eventbf=INVALIDFILENUM;
//DEADCODE DAW 28/03/99 			EventRecPtr	evind=EventRec::eventbase;
//DEADCODE DAW 28/03/99 			while (evind)
//DEADCODE DAW 28/03/99 			{
//DEADCODE DAW 28/03/99 				if (evind->eventwend && evind->attitem==target && Timer_Code.realtime>=evind->eventwend)
//DEADCODE DAW 28/03/99 				{
//DEADCODE DAW 28/03/99 					EventRecPtr	tmpnext=evind->eventlink;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 					//need to set GR_CPP,GR_CWP
//DEADCODE DAW 28/03/99 					GR_CWP=target->uniqueID.count;
//DEADCODE DAW 28/03/99 					GR_CPP=actor->uniqueID.count;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 					eventbf=ActionEvent(evind,mobileitem::currworld,target);
//DEADCODE DAW 28/03/99 					if (eventbf!=INVALIDFILENUM)
//DEADCODE DAW 28/03/99 					{
//DEADCODE DAW 28/03/99 						lastbfloaded=eventbf;
//DEADCODE DAW 28/03/99 						lasttarg=target;
//DEADCODE DAW 28/03/99 						lastact=actor;
//DEADCODE DAW 28/03/99 //DeadCode JIM 12Aug96 					LoadSubPiece(worldptr,eventbf);
//DEADCODE DAW 28/03/99 //DeadCode JIM 12Aug96 					assert(!anyoutstanding()&&"Sub event not complete!");
//DEADCODE DAW 28/03/99 //DeadCode RDH 11Oct96 						Timer_Code.AccelToggle(FALSE);
//DEADCODE DAW 28/03/99 //DeadCode RDH 11Oct96 						Manual_Pilot.AutoToggle(Manual_Pilot.MANUAL);
//DEADCODE DAW 28/03/99 						return;
//DEADCODE DAW 28/03/99 					}
//DEADCODE DAW 28/03/99 					evind=tmpnext;
//DEADCODE DAW 28/03/99 				}
//DEADCODE DAW 28/03/99 				else
//DEADCODE DAW 28/03/99 					evind=evind->eventlink;
//DEADCODE DAW 28/03/99 			}
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		ActionEvent
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Fri 29 Mar 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 FileNum		Persons2::ActionEvent(EventRecPtr	evind,WorldStuff *worldptr,ItemBasePtr target)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	FileNum	eventbf=INVALIDFILENUM;
//DEADCODE DAW 28/03/99 	int	els=evind->eventlistsize;
//DEADCODE DAW 28/03/99 	while (els--)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		if (evind->eventlist[els].Index>=0)
//DEADCODE DAW 28/03/99 			SetLoc(evind->eventlist[els].Index,evind->eventlist[els].Value);
//DEADCODE DAW 28/03/99 		elseif (evind->eventlist[els].Index==evind->eventlist[els].GV_EVENT_EVENT)
//DEADCODE DAW 28/03/99 			eventbf=(FileNum)evind->eventlist[els].Value;
//DEADCODE DAW 28/03/99 		elseif (evind->eventlist[els].Index==evind->eventlist[els].GV_EVENT_NEST)
//DEADCODE DAW 28/03/99 			if (eventbf!=INVALIDFILENUM)
//DEADCODE DAW 28/03/99 				ActionEvent(evind->eventlist[els].Nesting,mobileitem::currworld,target);
//DEADCODE DAW 28/03/99 			else
//DEADCODE DAW 28/03/99 				eventbf=ActionEvent(evind->eventlist[els].Nesting,mobileitem::currworld,target);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	delete evind;
//DEADCODE DAW 28/03/99 	return(eventbf);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		ColourRules
//DEADCODE DAW 28/03/99 //Author		Jim
//DEADCODE DAW 28/03/99 //Date			Sun 7 Apr 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Various coded methods for colouring squadrons.
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Persons2::ColourRuleAllRandom(AirStrucPtr	newac,FormationIndex formtype,UByte* s)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (SHAPE.SetAnimData(newac,0)!=sizeof(AircraftAnimData))//Pass in weapon pack (0) RJS 12May98
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Animation not aircraft");
//DEADCODE DAW 28/03/99 	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptail=Math_Lib.rnd(8);
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapbtmwing=Math_Lib.rnd(8);
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapfuselage=Math_Lib.rnd(8);
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapother=Math_Lib.rnd(8);
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptopwing=Math_Lib.rnd(8);
//DEADCODE DAW 28/03/99 	anim->imagemapemblem=Math_Lib.rnd(8);
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->dammageflags=*(UWord*)&s[COLS_DAMAGE];
//DEADCODE DAW 28/03/99 	Manual_Pilot.InitManualPilotSub(newac);				//rdh3/4/98
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 void	Persons2::ColourRuleDefined(AirStrucPtr	newac,FormationIndex formpos,UByte* selection)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (SHAPE.SetAnimData(newac,0)!=sizeof(AircraftAnimData))//Pass in weapon pack (0) RJS 12May98
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Animation not aircraft");
//DEADCODE DAW 28/03/99 	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptail=selection[1];
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapbtmwing=selection[4];
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapfuselage=selection[0];
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapother=selection[2];
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptopwing=selection[3];
//DEADCODE DAW 28/03/99 	anim->imagemapemblem=selection[5];
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->dammageflags=*(UWord*)&selection[COLS_DAMAGE];
//DEADCODE DAW 28/03/99 	Manual_Pilot.InitManualPilotSub(newac);				//rdh3/4/98
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	Persons2::ColourRulePlayerSquadron(AirStrucPtr	newac,FormationIndex formpos,UByte* s)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 //DeadCode RDH 23Sep96 	if (SHAPE.SetAnimData(newac)!=sizeof(AircraftAnimData))
//DEADCODE DAW 28/03/99 	if (SHAPE.SetAnimData(newac,0)!=sizeof(AircraftAnimData))//Pass in weapon pack (0) RJS 12May98
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Animation not aircraft");
//DEADCODE DAW 28/03/99 	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
//DEADCODE DAW 28/03/99 	int inwingpos,outwingpos;
//DEADCODE DAW 28/03/99 	inwingpos=formpos&InWingMAX;
//DEADCODE DAW 28/03/99 	outwingpos=formpos&InFormMAX;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	newac->ai.leaderaction = Miss_Man.camp.squad[0].nextleadact	//RDH 17Feb97
//DEADCODE DAW 28/03/99 							[outwingpos];						//RDH 18Aug96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (inwingpos == 0)
//DEADCODE DAW 28/03/99 	{//flight leader get squadron formation
//DEADCODE DAW 28/03/99 		newac->formation = (FormationTypeIndex)Miss_Man.camp.squad[0].squadronform;
//DEADCODE DAW 28/03/99 	}else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		newac->formation = (FormationTypeIndex)Miss_Man.camp.squad[0].formationnum [outwingpos];//RDH 17Feb97
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //DeadCode RDH 17Feb97 	outwingpos*=Miss_Man.camp.squad[0].pilotsperflight;			//RDH 17Feb97
//DEADCODE DAW 28/03/99 	outwingpos*=4;			//RDH 17Feb97
//DEADCODE DAW 28/03/99 	inwingpos+=outwingpos;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	newac->ai.followeraction = 	MMC.Active_Pilots[inwingpos].nextfollact;//RDH 18Aug96
//DEADCODE DAW 28/03/99 	newac->ai.skill 	= 		MMC.Active_Pilots[inwingpos].skill;		//RDH 18Aug96
//DEADCODE DAW 28/03/99 	newac->ai.character = 		MMC.Active_Pilots[inwingpos].character;	//RDH 18Aug96
//DEADCODE DAW 28/03/99 	newac->ai.morale 	= 		MMC.Active_Pilots[inwingpos].morale;		//RDH 18Aug96
//DEADCODE DAW 28/03/99 //fight tuning temp
//DEADCODE DAW 28/03/99 	newac->ai.morale 	= MORALE_EXCELLENT;		
//DEADCODE DAW 28/03/99 	newac->ai.skill 	= SKILL_ACE;		
//DEADCODE DAW 28/03/99 	newac->ai.followeraction = 	MMC.Active_Pilots[inwingpos].nextfollact;//RDH 18Aug96
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptail		=	MMC.Active_Pilots[inwingpos].imagemaps.tail;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapbtmwing	=	MMC.Active_Pilots[inwingpos].imagemaps.btmwing;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapfuselage	=	MMC.Active_Pilots[inwingpos].imagemaps.fuselage;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapother		=	MMC.Active_Pilots[inwingpos].imagemaps.other;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptopwing	=	MMC.Active_Pilots[inwingpos].imagemaps.topwing;
//DEADCODE DAW 28/03/99 	anim->imagemapemblem	=	MMC.Active_Pilots[inwingpos].imagemaps.emblem;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->dammageflags=*(UWord*)&s[COLS_DAMAGE];
//DEADCODE DAW 28/03/99 	if (Miss_Man.camp.currentplayerslot == inwingpos)			//RDH 27Aug96
//DEADCODE DAW 28/03/99 	{															//PD 26Jun96
//DEADCODE DAW 28/03/99 //DeadCode RJS 12Jun97 		Manual_Pilot.Associate(newac,TRUE);	//RDH 17Jun96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //		viewpoint->SetToPiloted(newac);							//PD 26Jun96
//DEADCODE DAW 28/03/99 		SHAPE.SetPilotedAcAnim(newac);							//PD 26Jun96
//DEADCODE DAW 28/03/99 		Manual_Pilot.Associate(newac,TRUE);						//RJS 12Jun97
//DEADCODE DAW 28/03/99 	}else															//PD 26Jun96
//DEADCODE DAW 28/03/99 		Manual_Pilot.InitManualPilotSub(newac);				//rdh3/4/98
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 void	Persons2::ColourRulePlayerAuto(AirStrucPtr	newac,FormationIndex formpos,UByte* s)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 //DeadCode RDH 23Sep96 	if (SHAPE.SetAnimData(newac)!=sizeof(AircraftAnimData))
//DEADCODE DAW 28/03/99 	if (SHAPE.SetAnimData(newac,0)!=sizeof(AircraftAnimData))//Pass in weapon pack (0) RJS 12May98
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Animation not aircraft");
//DEADCODE DAW 28/03/99 	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
//DEADCODE DAW 28/03/99 	int inwingpos,outwingpos;
//DEADCODE DAW 28/03/99 	inwingpos=formpos&InWingMAX;
//DEADCODE DAW 28/03/99 	outwingpos=formpos&InFormMAX;
//DEADCODE DAW 28/03/99 //DeadCode RDH 17Feb97 	outwingpos*=Miss_Man.camp.squad[0].pilotsperflight;			//RDH 17Feb97
//DEADCODE DAW 28/03/99 	outwingpos*=4;												//RDH 17Feb97
//DEADCODE DAW 28/03/99 	inwingpos+=outwingpos;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptail		=MMC.Active_Pilots[inwingpos].imagemaps.tail;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapbtmwing	=MMC.Active_Pilots[inwingpos].imagemaps.btmwing;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapfuselage	=MMC.Active_Pilots[inwingpos].imagemaps.fuselage;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapother		=MMC.Active_Pilots[inwingpos].imagemaps.other;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptopwing	=MMC.Active_Pilots[inwingpos].imagemaps.topwing;
//DEADCODE DAW 28/03/99 	anim->imagemapemblem	=MMC.Active_Pilots[inwingpos].imagemaps.emblem;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->dammageflags=*(UWord*)&s[COLS_DAMAGE];
//DEADCODE DAW 28/03/99 	if (Miss_Man.camp.currentplayerslot == inwingpos)				//PD 26Jun96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	{															//PD 26Jun96
//DEADCODE DAW 28/03/99 //DeadCode RJS 12Jun97 		Manual_Pilot.Associate(newac,TRUE);						//RDH 17Jun96
//DEADCODE DAW 28/03/99 //		View_Point->SetToPiloted(newac);							//PD 26Jun96
//DEADCODE DAW 28/03/99 		SHAPE.SetPilotedAcAnim(newac);							//PD 26Jun96
//DEADCODE DAW 28/03/99 		Manual_Pilot.Associate(newac,TRUE);						//RJS 12Jun97
//DEADCODE DAW 28/03/99 	}else															//PD 26Jun96
//DEADCODE DAW 28/03/99 		Manual_Pilot.InitManualPilotSub(newac);				//rdh3/4/98
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	Persons2::ColourRulePaintShop(AirStrucPtr	newac,FormationIndex formpos,UByte* s)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 //DeadCode RDH 23Sep96 	if (SHAPE.SetAnimData(newac)!=sizeof(AircraftAnimData))
//DEADCODE DAW 28/03/99 	if (SHAPE.SetAnimData(newac,0)!=sizeof(AircraftAnimData))//Pass in weapon pack (0) RJS 12May98
//DEADCODE DAW 28/03/99 		_Error.EmitSysErr("Animation not aircraft");
//DEADCODE DAW 28/03/99 	AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
//DEADCODE DAW 28/03/99 	int inwingpos,outwingpos;
//DEADCODE DAW 28/03/99 	inwingpos=formpos&InWingMAX;
//DEADCODE DAW 28/03/99 	outwingpos=formpos&InFormMAX;
//DEADCODE DAW 28/03/99 //DeadCode RDH 17Feb97 	outwingpos*=Miss_Man.camp.squad[0].pilotsperflight;			//RDH 17Feb97
//DEADCODE DAW 28/03/99 	outwingpos*= 4;												//RDH 17Feb97
//DEADCODE DAW 28/03/99 	inwingpos+=outwingpos;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptail		=MMC.Active_Pilots[inwingpos].imagemaps.tail;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapbtmwing	=MMC.Active_Pilots[inwingpos].imagemaps.btmwing;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapfuselage	=MMC.Active_Pilots[inwingpos].imagemaps.fuselage;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemapother		=MMC.Active_Pilots[inwingpos].imagemaps.other;
//DEADCODE DAW 28/03/99 //DeadCode RJS 09Jun97 	anim->imagemaptopwing	=MMC.Active_Pilots[inwingpos].imagemaps.topwing;
//DEADCODE DAW 28/03/99 	anim->imagemapemblem	=MMC.Active_Pilots[inwingpos].imagemaps.emblem;
//DEADCODE DAW 28/03/99 //DeadCode RJS 12Jun97 	Manual_Pilot.Associate(newac,FALSE);
//DEADCODE DAW 28/03/99 //	View_Point->SetToPiloted(newac);							//PD 26Jun96
//DEADCODE DAW 28/03/99 	SHAPE.SetPilotedAcAnim(newac);							//PD 26Jun96
//DEADCODE DAW 28/03/99 	Manual_Pilot.Associate(newac,FALSE);						//RJS 12Jun97
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	Persons2::AddRoute(UniqueID	firstwp)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	RouteHdr	*tmp=new RouteHdr;
//DEADCODE DAW 28/03/99 	tmp->next=myworld->routelist;
//DEADCODE DAW 28/03/99 	myworld->routelist=tmp;
//DEADCODE DAW 28/03/99 	tmp->waypoint=firstwp;
//DEADCODE DAW 28/03/99 	tmp->numusers=0;
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	Persons2::FreeRoutes()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	RouteHdr*	tmphdr=myworld->routelist;
//DEADCODE DAW 28/03/99 	myworld->routelist=NULL;
//DEADCODE DAW 28/03/99 	while(tmphdr)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		WayPointPtr	tmpwp=*ConvertPtrUID(tmphdr->waypoint);
//DEADCODE DAW 28/03/99 		while(tmpwp)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 		 	WayPointPtr	tmpwp2=tmpwp->next;
//DEADCODE DAW 28/03/99 			delete(tmpwp);
//DEADCODE DAW 28/03/99 			tmpwp=tmpwp2;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		RouteHdr*	tmphdr2=tmphdr->next;
//DEADCODE DAW 28/03/99 		delete tmphdr;
//DEADCODE DAW 28/03/99 		tmphdr=tmphdr2;
//DEADCODE DAW 28/03/99 	}	
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	Persons2::FreeEvents()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	while (EventRec::eventbase)	delete EventRec::eventbase;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		ItemStatus
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Mon 30 Sep 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	get and put statuses of items. Use in State3d destructor.
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 ITEM_STATUS	Persons2::ItemStatus(UniqueID u,ITEM_STATUS s)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	ItemBasePtr	i=ConvertPtrUID(u);
//DEADCODE DAW 28/03/99 	if (i)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		ITEM_STATUS	rv=i->Status;
//DEADCODE DAW 28/03/99 		i->Status.deadtime=s.deadtime;
//DEADCODE DAW 28/03/99 		i->Status.deadscale=s.deadscale;
//DEADCODE DAW 28/03/99 		return (rv);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		ITEM_STATUS	rv;
//DEADCODE DAW 28/03/99 		return rv;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 ITEM_STATUS	Persons2::ItemStatus(UniqueID u)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	ItemBasePtr	i=ConvertPtrUID(u);
//DEADCODE DAW 28/03/99 	if (i)
//DEADCODE DAW 28/03/99 		return (i->Status);
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		ITEM_STATUS	rv;
//DEADCODE DAW 28/03/99 		return rv;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 ITEM_STATUS	Persons2::ConvoyStatus(UniqueID uid,UniqueID& nextwp,UniqueID& nextwptarg,SLong& livelength)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	FormationItemPtr	f=*ConvertPtrUID(uid);
//DEADCODE DAW 28/03/99 	if (f)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		livelength=0;
//DEADCODE DAW 28/03/99 		WayPointPtr w=f->waypoint;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		nextwp=w->uniqueID.count;
//DEADCODE DAW 28/03/99 		ItemBasePtr	i=w->target;
//DEADCODE DAW 28/03/99 		if (i)
//DEADCODE DAW 28/03/99 			nextwptarg=i->uniqueID.count;
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			nextwptarg=IllegalSepID;
//DEADCODE DAW 28/03/99 		while (f)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			if (f->Status.deadtime==0)
//DEADCODE DAW 28/03/99 			  	livelength++;
//DEADCODE DAW 28/03/99 			f=f->follower;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		if (i)
//DEADCODE DAW 28/03/99 			return (i->Status);
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 			return (w->Status);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		ITEM_STATUS	rv;
//DEADCODE DAW 28/03/99 		return rv;
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 ///////////////////
//DEADCODE DAW 28/03/99 #endif
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
