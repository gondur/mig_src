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

//Filename       persons.cpp
//System         
//Author         Jim Taylor
//Date           Tue 5 Dec 1995
//Description    New 'persons' to process new battlefield format.
//------------------------------------------------------------------------------
#ifndef	SOURCE
#define	SOURCE
#define	F_COMMON


	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
	#include	<stdio.h>
//---------------------------------------------------------------------------

	#include	"dosdefs.h"
	#include	"files.g"
	#include	"myerror.h"

	#include	"worldinc.h"
	#include	"bfnumber.h"

	#include	"bfcommon.h"

	#include	"bfnumber.h"	//intensional double include

//#define source
//#define GRCHECK
#ifdef GRCHECK
#include "replay.h"
#endif
#include	"makebf.cxx"
extern	ULong&	GR_TakeOffTime;
//#undef source
	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DeadCode JIM 28Mar96 extern	PlaneType&	camel;										//RDH 23Feb96
//Old_Code PD 27Aug96  	MAKEFIELD	(ShapeNum,ShapeNumMIN,ShapeNumMAX);
//	Persons2	Persons_2;
//	extern	ULong	GR_FriendlyScoutType00;
//DeadCode RDH 30Jul97 	extern	ULong	GR_GlobalSkillMin;
//DeadCode RDH 30Jul97 	extern	ULong	GR_GlobalSkillMax;

int inline operator==(char a,TokenCode b) {return (int)a==(int)b;}
int inline operator!=(char a,TokenCode b) {return (int)a!=(int)b;}
//UniqueID inline operator +(UniqueIDBand b) {return UniqueID(b);}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//EventRec*	EventRec::eventbase=NULL;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 20Mar96 SLong
//DeadCode JIM 20Mar96 		p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,
//DeadCode JIM 20Mar96 		p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,
//DeadCode JIM 20Mar96 		p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,
//DeadCode JIM 20Mar96 		*globallocations[]={
//DeadCode JIM 20Mar96 							&p0,&p1,&p2,&p3,&p4,&p5,&p6,&p7,&p8,&p9,
//DeadCode JIM 20Mar96 							&p10,&p11,&p12,&p13,&p14,&p15,&p16,&p17,&p18,&p19,
//DeadCode JIM 20Mar96 							&p20,&p21,&p22,&p23,&p24,&p25,&p26,&p27,&p28,&p29,
//DeadCode JIM 20Mar96 								NULL};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


extern  BAD_RV; //=0x80000000;
//ULong GR_FriendlyChargeType00;									//JIM 09Apr96
//extern Replay _Replay;
//extern DPlay _DPlay;												//AMM 01Jun98

UniqueIDBand	Persons2::uidbandbase[UIDTABLESIZE]= {
							PilotedAcBAND,		
							WayPointBAND,		
							MissileBAND,			
							LandscapeBAND,		
							RedRailBand,			
							RedRoadBAND,		
							RedAcBAND,			
							BlueAcBAND,			
							AmberAirfieldBAND,
							RedFakeAcBAND,
							RedAAASiteBAND,		
							BlueAAASiteBAND,		
							RedAAALargeBAND,	
							AmberCivilianBAND,
							AmberSupplyBAND,		
							RedRepairBAND,		
							AmberBridgeBAND,		
							AmberMYardBAND,	
							AmberBattleNodeBAND,
							RedTrainBAND,		
							RedTruckBAND,		
							RedTruckParkBAND,
							RedTroopBAND,		
							BlueTroopBAND,		
							RedArmourBAND,		
							BlueArmourBAND,		
							RedArtilleryBAND,	
							BlueArtilleryBAND,
							RedCombatVehicleBAND,
							BlueCombatVehicleBAND,							
							EventBAND,			
							GreenVetoedBAND,		
							GreenMobileBAND,		
							GreenMiscBAND,		
							RedHQBAND,			
							BlueHQBAND,			
							RedBoatBAND,			
							BlueBoatBAND,		
							GreenBoatBAND,		
							RedStaticAcBAND,		
							BlueStaticACBAND,	

							RunwaySBAND,
							RunwayEBAND,
							AfHangerBAND,
							AfRevetmentBAND,
							AfSupplyBAND,
							AfRunwayBAND,
							AfNoScoreBAND,

							//new ones go here:

							NextBAND,LastBAND,
							RedMilitaryBAND,		
							BlueMilitaryBAND,	
							RedAirfieldBAND,		
							BlueAirfieldBAND,	
							RedPortBAND,			
							BLuePortBAND,		
							RedCCCBAND,			
							BlueCCCBAND,			
							RedGICBAND,			
							BlueGICBAND,			
							RedSAMBAND,			
							BlueSAMBAND,
							IllegalBAND,			
//array must be filled for getband to work, rdh		
							IllegalBAND			
							};


UniqueID		Persons2::uidbandmax[UIDTABLESIZE];
UniqueID		Persons2::uidbandmin[UIDTABLESIZE];

FileNum			Persons2::loadedBF[LOADEDBFS];
UniqueID		Persons2::loadedSG[LOADEDSGS];
ItemBase**		Persons2::pItem;//ME =items;




CON	Persons2::Persons2(WorldStuff* world,ViewPoint* vp)
{
	inst3d=NULL;
	viewpoint=vp;
//DEADCODE JIM 17/03/99 	eventloglist=NULL;
	myworld=world;	
	if (world)
		pItem=world->pItem;
	rootuidnode = NULL;
//DEADCODE JIM 25/03/99 	permtextpage=(TextPage)0;
	justscanning=LOAD;

}


ItemBasePtr		Persons2::ConvertPtrUID(UniqueID tmpUID)
{
//DAW 5-11-98 I do not like have multiple return statements in a routine
//this is not too bad because you can see what is happening i.e. 3 lines
//however on a large routine you will shaft yourself.
//The reason I'm here is because it crashes because pItem is null
//Therefore this should be protected in it's calls like the one below...
//THANK'S FOR THE COMMENTS DAVE... 5 YEARS TOO LATE AND ALL THAT, 
//THAT@S WHY THER@S A SLOW VERSION BELOW.


#ifndef NDEBUG
	if (tmpUID==0)
		return NULL;
	if (tmpUID==0x107)
		tmpUID=tmpUID;
#endif
	return(pItem[tmpUID]);
}
ItemBasePtr		Persons2::SlowConvertPtrUID(UniqueID tmpUID)
{
	if (pItem != NULL)
		return(ConvertPtrUID(tmpUID));
	else
		return(NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	UID/World interface
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴



UniqueID	Persons2::findavailuid(UniqueIDBand	tmpband)
{

	int			uidindex = -1;
	int			count;
	UniqueID	tempUID;

	for (count = 0; count < (int)UIDTABLESIZE; count ++)
		if ((int)uidbandbase[count] == (int)tmpband)
		{
			uidindex = count;
			break;
		}

	tempUID = IllegalSepID;

	if (uidindex > -1)
	{
		do{
			tempUID = (UniqueID) uidbandmin[uidindex];
			uidbandmin[uidindex] = (UniqueID)((int)uidbandmin[uidindex] + 1);
		}while (pItem[tempUID] && (int)tempUID<(int)uidbandmax[uidindex]);
		if (tempUID==uidbandmax[uidindex])
		{
			uidbandmin[uidindex]=(UniqueID)uidbandbase[uidindex];
			do{
				tempUID = (UniqueID) uidbandmin[uidindex];
				uidbandmin[uidindex] = (UniqueID)((int)uidbandmin[uidindex] + 1);
			}while (pItem[tempUID] && (int)tempUID<(int)uidbandmax[uidindex]);
		}
		if (tempUID==uidbandmax[uidindex])
		{
			uidbandmin[uidindex]=(UniqueID)uidbandbase[uidindex];
			return UID_Null;
		}
		else
			return tempUID;
	}
	else
		return UID_Null;



}

UniqueID	Persons2::assignuid(UniqueIDBand	tmpband)
{
	UniqueID	rv=findavailuid(tmpband);
	if (rv==UID_Null)
	{
		for (int i=tmpband;i<IllegalBAND;i++)
		{	//this is just a debug scan
			ItemPtr p=*ConvertPtrUID(UniqueID(i));

		}
		_Error.EmitSysErr("UIDband table overlap! %04x",tmpband);
	}
	return (rv);
}

UniqueIDBand	Persons2::getbandfromUID(UniqueID	tmpUID)
{
	int	i = UIDTABLESIZE;

	while (i--)
		if ((int)tmpUID >= (int)uidbandbase[i])							//RDH 11Oct96
			return(uidbandbase[i]);

	return (IllegalBAND);
}
UniqueIDBand	Persons2::getbandMAXfromUID(UniqueID	tmpUID)
{
	int	i = UIDTABLESIZE;

	while (i--)
		if ((int)tmpUID >= (int)uidbandbase[i])							//RDH 11Oct96
			return(uidbandbase[i+1]);

	return (IllegalBAND);
}


int	Persons2::getbandnumfromUID(UniqueID	tmpUID)
{
	int	i = UIDTABLESIZE;

	while (i--)
		if ((int)tmpUID >= (int)uidbandbase[i])							//RDH 11Oct96
			return(i);												  //CSB 03/06/99

	return (i);
}

//DeadCode RJS 13Feb96 enum	UILogType
//DeadCode RJS 13Feb96 {
//DeadCode RJS 13Feb96 	ptrcopy			= 1,
//DeadCode RJS 13Feb96 	worldcopy		= 2,
//DeadCode RJS 13Feb96 	addworldcopy	= 3
//DeadCode RJS 13Feb96 };

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSetPiece
//Author		Jim Taylor
//Date			Tue 18 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//;;------------------------------------------------------------------------------
//inline UniqueIDBand	operator+(UniqueID u) {return (UniqueIDBand) u;}
//inline UniqueID	operator+(UniqueIDBand u) {return (UniqueID) u;}
//------------------------------------------------------------------
void Persons2::InitTables()
{
	int count=0;
	uidbandmax[count] =(UniqueID)((int)uidbandbase[count+1]-1);
	uidbandmin[count] = (UniqueID)uidbandbase[count];
	for (count = 1; count < (int)UIDTABLESIZE-1; count++)
	{
		uidbandmax[count] = uidbandbase[count+1]?(UniqueID)((int)uidbandbase[count+1]-1):(UniqueID)IllegalBAND;
		if (uidbandbase[count])
			uidbandmin[count] = (UniqueID)uidbandbase[count];
		else
		{
			uidbandbase[count]=IllegalBAND;
			uidbandmin[count] =(UniqueID)IllegalBAND;
		}
	}

	uidbandmax[count] =(UniqueID)IllegalBAND;
	if (uidbandbase[count])
		uidbandmin[count] = (UniqueID)uidbandbase[count];
	else
	{
		uidbandbase[count]=IllegalBAND;
		uidbandmin[count] =(UniqueID)IllegalBAND;
	}


	uidbandmax[(int)UIDTABLESIZE-1] =
		uidbandmin[(int)UIDTABLESIZE-1] = (UniqueID)uidbandbase[(int)UIDTABLESIZE-1];
	if (pItem)
		for (count = 0; count < (int)PITEMTABLESIZE; count++)
			pItem[count] = NULL;
	for (int i=0;i<LOADEDBFS;i++)
		loadedBF[i]=FIL_NULL;
	for (int j=0;j<LOADEDSGS;j++)
		loadedSG[j]=UID_NULL;
}

void Persons2::InitSetPiece()
{
	InitTables();
	InitGamePiece();
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSetPiece
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void Persons2::LoadSetPiece(WorldStuff *worldptr, FileNum filenumber)
//{
//
////TempCode ARM 27Sep96 	SendInitPacket ();											//ARM 09Aug96
//
//	InitSetPiece();
//	LoadSubPiece(worldptr,filenumber);
//
//	if (anyoutstanding())
//		_Error.EmitSysErr("Unresolved UIDS! One is: %x",rootuidnode->uidattack);
//}
//

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSetPiece
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	Load battlefields as fed by FindNextBf
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void Persons2::LoadSetPiece(WorldStuff *worldptr)
{
	SENT_REQ=FALSE;
	TruckLog=TargLog=PlayerLog=NULL;
	FileNum	filelist;

	SendInitPacket ();

	InitSetPiece();

	BattlefieldType	bfctrl=MAINWORLDBF;
	int bf=0;
	do
	{
		filelist = FindCommsNextBf (bfctrl);
//DEADCODE JIM 17/05/99 		_DPlay.SetRandomListPos();								//AMM 10May99
		if (bfctrl==TAKEOFFAFBF)
		   if (inst3d)
			   inst3d->timeofday=GR_TakeOffTime*int(SECS100);
#ifdef GRCHECK
		FILE* fp;
		if (_Replay.Record)
			fp=fopen("grcheckr.txt","at");
		else
			fp=fopen("grcheckp.txt","at");

		bool	finished=false;
		int val,n=0;

		fprintf(fp,"FILE=%d bf=%d nextrnd=%d\n",filelist,bf,Math_Lib.rnd());
		while (!finished)
		{
			val=Persons2::GetLoc(n++);
			if (val==BAD_RV)
				finished=true;

			fprintf(fp,"%d: %d\n",n-1,val);
		}
		fprintf(fp,"\n");
		fclose(fp);
#endif
		if (filelist)
			LoadSubPiece(worldptr,filelist,bf++);
	}while ((int)bfctrl!=(int)FINISHBF);

	FinishSetPiece();
}
/*
	daw 17/7/98 removed a load of dead / temp code

*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindCommsNextBf
//Author		Andrew McRae
//Date			Fri 27 Sep 1996
//
//Description	NOW IN PERSONS3.CPP
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
FileNum Persons4::FindCommsNextBf (Persons2::BattlefieldType& bfctrl)		//ARM 27Sep96
{
		return FindNextBf(bfctrl);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Load SUB Piece
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	Loads 1 battlefield
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Persons2::LoadSubPiece(WorldStuff *worldptr, FileNum filenumber,int bfindex,JustScanning scanning)
{  
	if (bfindex<LOADEDBFS)
		loadedBF[bfindex]=filenumber;

	fileblock	bfield_file(filenumber);
string
	bfieldptr = (string)getdata(bfield_file);

	while (*(bfieldptr++));
	LoadSubPiece(worldptr,bfieldptr,bfindex,scanning);
}


void Persons2::LoadSubPiece(WorldStuff *worldptr, string& bfieldptr,int bfindex,JustScanning scanning)
{  
	int	oldbfindex=currbfindex;
	currbfindex=bfindex;
//	if (bfindex<LOADEDBFS)
//		loadedBF[bfindex]=filenumber;
	InitSubPiece();
	myworld=worldptr;
	if (scanning)
		justscanning=scanning;

	if (*(bfieldptr++)!=(int)T_bfsave)
		_Error.EmitSysErr("Battlefield didn't start with BFSAVE!");

	processbfieldtoplevel(bfieldptr);

    EndSubPiece();
	if (scanning)
		currbfindex=oldbfindex;
	justscanning=LOAD;

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		processbfieldtoplevel
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons2::processbfieldtoplevel(string& bfieldptr)
{
currsupergroup=UID_Null;
int	loopcount=getloopcount(bfieldptr);
	while (loopcount--)
		switch (*(bfieldptr++))
		{
			case T_comment:		toplevel_string(bfieldptr,T_comment);		break;
			case T_name:		toplevel_string(bfieldptr,T_name);			break;
			case T_family:  	toplevel_string(bfieldptr,T_family);			break;
			case T_event:
			{	//I can't do anything with top level events, but mission editor can!
				info_event*	E=NULL;
				midlevel_event(bfieldptr,E);
				make_events(E,NULL);
				delete E;
			}
			break;
			case T_itemS:		toplevel_itemS(bfieldptr,true);					break;
			case T_itemgrp:		toplevel_itemgrp(bfieldptr);				break;
			case T_gndgrp:		toplevel_gndgrp(bfieldptr);					break;
			case T_airgrp:		toplevel_airgrp(bfieldptr);					break;
			case T_route:		toplevel_route(bfieldptr);					break;
			case T_setval:		toplevel_setval(bfieldptr);					break;
			default:
				_Error.EmitSysErr("Type of symbol not valid in BattleField top level");
		}
}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_itemgrp
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::toplevel_itemgrp(string	&bfieldptr)
{
int	loopcount=getloopcount(bfieldptr);
UniqueID	lastsupergroup=currsupergroup;
	int	numinform=32767;
	while (loopcount--)
	{
		numinform--;
		switch (*(bfieldptr++))
		{
			case T_target:
				currsupergroup=(UniqueID)constructvalue(bfieldptr,TRUE).Evaluate();
				AddSGToList(currsupergroup);
			break;
	 		case T_inform:	
				numinform=make_itemgroupcount(constructvalue(bfieldptr));
			break;
			case T_itemS:		toplevel_itemS(bfieldptr,(numinform>=0));				break;
			case T_itemgrp:		toplevel_itemgrp(bfieldptr);			break;
			case T_gndgrp:		toplevel_gndgrp(bfieldptr);				break;
			case T_airgrp:		toplevel_airgrp(bfieldptr);				break;
			default:
				_Error.EmitSysErr("Type of symbol not valid in BattleField top level");
		}
	}
	currsupergroup=lastsupergroup;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_itemS
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::toplevel_itemS(string	&bfieldptr,bool	enabled)
{
//	if (*(int*)0x660444!=0)
  //	   (*(char*)0xB000A)='a';

	info_itemS	I;
	I.SGT=currsupergroup;

int	loopcount=getloopcount(bfieldptr);
//DeadCode JIM 11Jun97 itemptr	tmpitem = new item;
	while (loopcount--)
		switch (*(bfieldptr++))
		{
		case T_event:
			midlevel_event(bfieldptr,I.events);
		break;
		case T_hdg:
		case T_bearing:
		{
			I.attitude=	constructvalue(bfieldptr);
			//ROBERT: now what?????
		}
		break;
		case T_target:
		{
			_Error.EmitSysErr("Not supported...");
			//ROBERT: now what?????
		}
		break;
		case T_UIDband:
			I.band=constructvalue(bfieldptr);
		break;
		case T_setUID:
			I.uid=constructvalue(bfieldptr);
		break;
		case T_pos:
			I.position=constructposition(bfieldptr);
		break;
		case T_shape:
			I.shape=constructvalue(bfieldptr,TRUE);
		break;
		default:
			_Error.EmitSysErr("Type of symbol not valid in BattleField mid level");
		}

	make_itemS(I,enabled);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_gndgrp
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::toplevel_gndgrp(string	&bfieldptr)
{
	info_grndgrp	I;
	I.SGT=currsupergroup;
	int	loopcount=getloopcount(bfieldptr);
	while (loopcount--)
		switch (*(bfieldptr++))
		{
		case T_inform:	I.inform=constructvalue(bfieldptr);		break;
		case T_pos:		I.position=constructposition(bfieldptr);		break;
		case T_route:	I.wpref=toplevel_route(bfieldptr);		break;
		case T_form:	I.form=constructvalue(bfieldptr);		break;
		case T_itemG:
		{
			int	loopcount=getloopcount(bfieldptr);
            while (loopcount--)
	 			switch (*(bfieldptr++))
 				{
 				case T_setUID:	I.uid=constructvalue(bfieldptr,TRUE);		break;
 				case T_nation:	I.nat=constructvalue(bfieldptr,TRUE);		break;
	 			case T_shape:	I.shape=constructvalue(bfieldptr,TRUE);		break;
 				case T_type:	I.type=constructvalue(bfieldptr,TRUE);		break;
 				case T_vel:		I.vel=constructvalue(bfieldptr,TRUE);		break;
 				case T_UIDband:	I.band=constructvalue(bfieldptr,TRUE);		break;
	 			case T_move:	I.movecode=constructvalue(bfieldptr,TRUE);	break;
 				case T_damage:	I.damage=constructvalue(bfieldptr,TRUE);	break;
 				case T_leader:	I.leader=constructvalue(bfieldptr,TRUE);	break;
 				case T_event:	midlevel_event(bfieldptr,I.events);			break;
	 			case T_att:		I.attitude=constructangles(bfieldptr);		break;
 				default:
 					_Error.EmitSysErr("Type of symbol not valid in BattleField groundformdata");//JIM 28Mar96
 				}
		}
		break;
		default:
			_Error.EmitSysErr("Type of symbol not valid in BattleField mid level");
		}
	make_gndgrp(I);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_airgrp
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons2::toplevel_airgrp(string	&bfieldptr)
{
//DeadCode JIM 16Jun97 	UByte		cols[COLS_ALL]={0};
	info_airgrp	I;
	I.SGT=currsupergroup;
	I.usedpaintrules=0;
int	loopcount=getloopcount(bfieldptr);
	while (loopcount--)
		switch (*(bfieldptr++))
		{
		case T_inform:	I.inform=constructvalue(bfieldptr);		break;
		case T_inwing:	I.inwing=constructvalue(bfieldptr);		break;
		case T_duty:	I.duty=constructvalue(bfieldptr);		break;
		case T_form:	I.form=constructvalue(bfieldptr,TRUE);		break;
		case T_pos:		I.position=constructposition(bfieldptr);		break;
		case T_route:	I.wpref=toplevel_route(bfieldptr);		break;
		case T_leader:	I.leader=constructvalue(bfieldptr,TRUE);	break;
		case T_itemA:
		{
			int	loopcount=getloopcount(bfieldptr);
			while (loopcount--)
				switch (*(bfieldptr++))
				{
				case T_name
					:	toplevel_agname(bfieldptr,I);				break;
				case T_setUID:	I.uid=constructvalue(bfieldptr,TRUE);		break;
				case T_nation:	I.nat=constructvalue(bfieldptr,TRUE);		break;
				case T_shape:	I.shape=constructvalue(bfieldptr,TRUE);		break;
				case T_type:	I.type=constructvalue(bfieldptr,TRUE);		break;
				case T_vel:		I.vel=constructvalue(bfieldptr,TRUE);		break;
				case T_UIDband:	I.band=constructvalue(bfieldptr,TRUE);		break;
				case T_move:	I.movecode=constructvalue(bfieldptr,TRUE);	break;
				case T_skill:	I.skill=constructvalue(bfieldptr,TRUE);		break;
				case T_morale:	I.morale=constructvalue(bfieldptr,TRUE);	break;
				case T_character:I.character=constructvalue(bfieldptr,TRUE);break;
				case T_damage:	I.damage=constructvalue(bfieldptr,TRUE);	break;
				case T_bombs:
					I.bombs=constructvalue(bfieldptr,TRUE);
					break;
				case T_target:	I.target=constructvalue(bfieldptr,TRUE);	break;
				case T_attacker:I.attacker=constructvalue(bfieldptr,TRUE);	break;
				case T_leader:	I.leader=constructvalue(bfieldptr,TRUE);	break;
				case T_follower:I.follower=constructvalue(bfieldptr,TRUE);	break;
				case T_home:	I.homebase=constructvalue(bfieldptr,TRUE);	break;
				case T_event:	midlevel_event(bfieldptr,I.events);			break;
				case T_att:		I.attitude=constructangles(bfieldptr);		break;
				case T_squadron:lowlevel_squadron(bfieldptr,I);				break;
				case T_paintscheme:
					I.paintrules[I.usedpaintrules++]=constructvalue(bfieldptr,TRUE);
				break;
				case T_attmethod:I.attmethod=constructvalue(bfieldptr,TRUE);	break;
				case T_attpattern:I.attpattern=constructvalue(bfieldptr,TRUE);	break;
				case T_radiosilence:I.radiosilence=constructvalue(bfieldptr,TRUE);	break;


				default:
					_Error.EmitSysErr("Type of symbol not valid in BattleField Airformdata");//JIM 28Mar96
				}
		}
		break;
		default:
			_Error.EmitSysErr("Type of symbol not valid in BattleField Airformgroup");//JIM 28Mar96
		}


	make_airgrp(I);
}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_route
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UniqueID	Persons2::toplevel_route(string	&bfieldptr)
{


UniqueID	chainwp=IllegalSepID,
			firstwp=IllegalSepID;
	if (*bfieldptr==T_setUID || *bfieldptr==T_target)
	{
		info_waypoint I;
	 	I.prevwp=chainwp;
		I.useexistingWP=constructvalue(bfieldptr);
		return make_waypoint(I);
	}
int	loopcount=getloopcount(bfieldptr);
	while (loopcount--)
		switch (*(bfieldptr++))
		{
			case T_route:
			{
UniqueID		tmpUID=toplevel_route(bfieldptr);
WayPointPtr		tmpwp2=(WayPointPtr)ConvertPtrUID(tmpUID);
				assert((tmpwp2)&&("nested route must exist"));
				if ((int)firstwp!=(int)IllegalSepID)
				{
WayPointPtr			tmpwp1=(WayPointPtr)ConvertPtrUID(chainwp);
					assert((tmpwp1)&&("nested route must exist"));
					tmpwp1->next=tmpwp2;
					while (tmpwp1->next)
						tmpwp1=tmpwp1->next;
					chainwp=tmpwp1->uniqueID.count;
				}
				else
					firstwp=chainwp=tmpUID;
			}
			case T_waypoint:
				chainwp=midlevel_waypoint(bfieldptr,chainwp);
				if ((int)firstwp==(int)IllegalSepID)
					firstwp=chainwp;
			break;
			default:
				_Error.EmitSysErr("Type of symbol not valid in BattleField mid level");
		}
//what to do with the chain now we have it?
//add it to the list of known chains...
	AddRoute(firstwp);
	return(firstwp);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		midlevel_waypoint
//Author		Jim Taylor
//Date			Fri 12 Jan 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
UniqueID	Persons2::midlevel_waypoint(string	&bfieldptr,UniqueID	chainwp)
{
//special code if 'existing' route is referenced
	if (*bfieldptr==T_setUID)									//JIM 01Apr96
	{															//JIM 01Apr96
		info_waypoint I;
		I.SGT=currsupergroup;
		I.prevwp=chainwp;
		I.useexistingWP=constructvalue(bfieldptr);
		return make_waypoint(I);
	}															//JIM 01Apr96

	info_waypoint I;
	I.prevwp=chainwp;
	I.rangeispercent=FALSE;
//normal code... route is inline
	int	loopcount=getloopcount(bfieldptr);
	while (loopcount--)
		switch (*(bfieldptr++))
		{
		case T_setUID:	I.uid=constructvalue(bfieldptr);		break;
		case T_vel:		I.vel=constructvalue(bfieldptr);		break;
		case T_start:	event_time(bfieldptr,I.etah,I.etam,I.etas);break;
		case T_pos:		I.position=constructposition(bfieldptr);		break;
		case T_target:	I.target=constructvalue(bfieldptr);		break;
		case T_wpact:	I.wpact=constructvalue(bfieldptr);		break;
		case T_rangepc:
			I.rangeispercent=TRUE;
		case T_range:
			I.range=constructvalue(bfieldptr);
		break;
		case T_event:	//generates an entry somewhere else (mysterious??)
			midlevel_event(bfieldptr,I.events);
		case T_applygroup: I.applygroup=constructvalue(bfieldptr);		break;
		case T_applyflight: I.applyflight=constructvalue(bfieldptr);		break;
		case T_applyelt: I.applyelt=constructvalue(bfieldptr);		break;
		case T_applyac: I.applyac=constructvalue(bfieldptr);		break;

		break;
			default:
				_Error.EmitSysErr("Type of symbol not valid in BattleField mid level");
		}
	return	make_waypoint(I);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		midlevel_event
//Author		Jim Taylor
//Date			Fri 12 Jan 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------

void		Persons2::midlevel_event(string& bfieldptr,info_event*& E)
{
	info_event&	I=*new info_event;
//	I.SGT=currsupergroup;
	I.next=E;
	E=&I;

	midlevel_event(bfieldptr,I);
///make_events(I); ///called from make_xxx as required
//DeadCode JIM 17Jun97 	if (newevent->eventwend)									//JIM 04Nov96
//DeadCode JIM 17Jun97 		newevent->eventwend+=newevent->eventwstart+Timer_Code.realtime;
//DeadCode JIM 17Jun97 	if (newevent->eventwstart)
//DeadCode JIM 17Jun97 		newevent->eventwstart+=Timer_Code.realtime;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		event_setval
//Author		Jim Taylor
//Date			Wed 20 Mar 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
EventVar	Persons2::event_setval(string& bfieldptr)
{
int	loopcount=getloopcount(bfieldptr);
EventVar	es;
	if (loopcount!=2)
		_Error.EmitSysErr("There must be an Lvalue and an RValue in SetVal");
	es.index=evaluateglobvar(bfieldptr);
	es=constructvalue(bfieldptr);
	return(es);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		event_event
//Author		Jim Taylor
//Date			Wed 20 Mar 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void		Persons2::midlevel_event(string& bfieldptr,info_event& I)
{
	Bool Process=TRUE;
	if (*bfieldptr==T_linklist)
	{
		int	loopcount=getloopcount(bfieldptr);
	//EventRecPtr	newevent=new EventRec (NULL,loopcount);
		while (loopcount--)
			switch (*(bfieldptr++))
			{
			case	T_comment:	toplevel_string(bfieldptr,T_comment);				break;
			case	T_name:		Process=toplevel_eventname(bfieldptr,I);				break;
			case	T_setval:
				if (Process)	I.setvals[I.usedsetvals++]=event_setval(bfieldptr);
				else			event_setval(bfieldptr);
				break;
			case	T_start:	event_time(bfieldptr,I.starth,I.startm,I.starts);	break;
			case	T_window:	event_time(bfieldptr,I.winh,I.winm,I.wins);			break;
			case	T_event:
				if (!Process) 	_Error.EmitSysErr("Can't nest ignore stuff!");
								midlevel_event(bfieldptr,I);						break;
			default:
					_Error.EmitSysErr("Type of symbol not valid in Events mid level");
			}
		I.allsetvals=I.usedsetvals;	
		
	}
	else
		I.bfields=constructvalue(bfieldptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Event_Time
//Author		Jim Taylor
//Date			Wed 20 Mar 1996
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------

void	Persons2::event_time(string& bfieldptr,EventVal&h,EventVal&m,EventVal&s)
{
int	loopcount=getloopcount(bfieldptr);
	while (loopcount--)
		switch (*(bfieldptr++))
		{
 		case T_hours:	//hours
			if (h.Evaluate()!=ENABLE_COMPLEX_VAL)
				_Error.EmitSysErr("Hours repeated");
			h=constructvalue(bfieldptr);
		break;
 		case T_mins:	//mins
			if (m.Evaluate()!=ENABLE_COMPLEX_VAL)
				_Error.EmitSysErr("Mins repeated");
			m=constructvalue(bfieldptr);
		break;
 		case T_secs:	//mins
			if (s.Evaluate()!=ENABLE_COMPLEX_VAL)
				_Error.EmitSysErr("Seconds repeated");
			s=constructvalue(bfieldptr);
		}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_setval
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons2::toplevel_setval(string	&bfieldptr)
{
	EventVar	es;
int	loopcount=getloopcount(bfieldptr);
	if (loopcount!=2)
		_Error.EmitSysErr("There must be an Lvalue and an RValue in SetVal");
	es.index=evaluateglobvar(bfieldptr);
	es=constructvalue(bfieldptr);
	make_setval(es);
//DeadCode JIM 20Mar96 	*globallocations[locnum]=value;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		evaluateglobvar
//Author		Jim Taylor
//Date			Thu 7 Dec 1995
//
//Description	chain down to get globallocations table index and get that.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	Persons2::evaluateglobvar(string &bfieldptr,FormationIndex fi)
{
SLong	retval;
//DeadCode JIM 08Jan96 	for (;;)
		switch (*(bfieldptr++))
		{
		case T_long:
		case T_int:
			retval=*((ULong*) bfieldptr);
			bfieldptr+=4;
		break;
		case T_word:
			retval=*((UWord*) bfieldptr);
			bfieldptr+=2;
		break;
		case T_byte:
			retval=((UByte) (*(bfieldptr++)) );
		break;
		case T_linklist:
		case T_nlong:
		case T_nint:
		case T_nword:
		case T_nbyte:
		case T_random:
		case T_select:
		case T_list:
			_Error.EmitSysErr("Unexpected construct while getting global index");
		default:retval=evaluateglobvar(bfieldptr,fi);
		}
	return(retval);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_string
//Author		Jim Taylor
//Date			Wed 11 Jun 1997
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void		Persons2::toplevel_string(string	&bfieldptr,TokenCode t)
{
int	len=(int)(UByte)*bfieldptr++;
	make_string(bfieldptr,len,t);
	bfieldptr+=len;
}

Bool		Persons2::toplevel_eventname(string	&bfieldptr,info_event& E)
{
int	len=(int)(UByte)*bfieldptr++;
string t=bfieldptr;
	bfieldptr+=len;
	return(make_eventname(t,len,E));
}
Bool		Persons2::toplevel_agname(string	&bfieldptr,info_airgrp& A)
{
int	len=(int)(UByte)*bfieldptr++;
string t=bfieldptr;
	bfieldptr+=len;
	return(make_agname(t,len,A));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		constructvalue
//Author		Jim Taylor
//Date			Wed 11 Jun 1997
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
EventVal	Persons2::constructvalue(string &bfieldptr,Bool isform)
{
	EventVal	retval;
	switch (*(bfieldptr++))
	{
		case T_random:		//int(p1*rnd)*p3+p2
		{
			EventVal	p1=0,p2=0,p3=1;
			int	lc=getloopcount(bfieldptr);
			p1=constructvalue(bfieldptr,isform);
			if (--lc!=0)
			{
				p2=p1;
				p1=constructvalue(bfieldptr,isform);
				if (--lc!=0)
					p3=constructvalue(bfieldptr,isform);
			}

			RndExpr*	t=new RndExpr;

			t->base=p2;
			t->stepsize=p3;
			t->maxsteps=p1;
			retval=t;
			return (retval);
		}
		case T_select:		//p1*p3+p2
		{
			EventVal	p1=0,p2=0,p3=1,p4;
			int	lc=getloopcount(bfieldptr);
			p1=constructvalue(bfieldptr,FALSE);
			if (--lc!=0)
			{
				p2=constructvalue(bfieldptr,isform);
				if (--lc!=0)
				{
					p3=constructvalue(bfieldptr,isform);
					if (--lc!=0)
						p4=constructvalue(bfieldptr,isform);
				}
			}
			SelExpr*	t=new SelExpr;
			t->base=p1;
			t->steps=p2;
			t->stepsize=p3;
			t->div=p4;
			retval=t;
			return (retval);
	 	}
		case T_list:
		{
			int lc=getloopcount(bfieldptr);
			if (isform)
			{
				ListFormExpr*	t=new ListFormExpr;
				t->maxentries=lc;
				for (int ind=0;ind<lc;ind++)
					t->entries[ind]=constructvalue(bfieldptr,TRUE);
				retval=t;
				return (retval);
			}
			else
			{
				ListExpr*	t=new ListExpr;
				t->index=constructvalue(bfieldptr,FALSE);
				lc--;
				t->maxentries=lc;
				for (int ind=0;ind<lc;ind++)
					t->entries[ind]=constructvalue(bfieldptr,FALSE);
				retval=t;
				return (retval);
			}
		}
		case T_long:
		case T_int:
			retval=*((ULong*) bfieldptr);
			bfieldptr+=4;
			break;
	case T_nlong:
	case T_nint:
			retval=-*((SLong*) bfieldptr);
//			retval=-retval;
			bfieldptr+=4;
	break;
	case T_word:
			retval=*((UWord*) bfieldptr);
			bfieldptr+=2;
	break;
	case T_nword:
			retval=-*((SWord*) bfieldptr);
//			retval=-retval;
			bfieldptr+=2;
		break;
		case T_byte:
			retval=((UByte) (*(bfieldptr++)) );
		break;
		case T_nbyte:
		retval=-(SLong)((UByte) (*(bfieldptr++)) );
		break;
		case T_mainprog:
		{
			GlobRefExpr	*t=new GlobRefExpr;
			switch (*(bfieldptr++))
			{
			case T_long:
			case T_int:
				t->globrefind=*((ULong*) bfieldptr);
				bfieldptr+=4;
			break;
			case T_word:
				t->globrefind=*((UWord*) bfieldptr);
				bfieldptr+=2;
			break;
			case T_byte:
				t->globrefind=((UByte) (*(bfieldptr++)) );
			break;
			case T_linklist:
			case T_nlong:
			case T_nint:
			case T_nword:
			case T_nbyte:
			case T_random:
			case T_select:
			case T_list:
			default:	//retval=evaluateglobvar(bfieldptr,fi);
				_Error.EmitSysErr("Unexpected construct while getting global index");
			}
			used_globref(t->globrefind);
			retval=t;
			return (retval);
		}
		case T_linklist:
			_Error.EmitSysErr("Not expecting linklist just here in evaluate!");
		default:
			retval=constructvalue(bfieldptr,isform);
	}
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		constructangles
//Author		Jim Taylor
//Date			Mon 16 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
EventVal Persons2::constructangles(string& bfieldptr)
{
	RotExpr*	rot=new RotExpr;
int	loopcount=getloopcount(bfieldptr);
	while (loopcount--)
		switch (*(bfieldptr++))
		{
			case T_target:	//any object either becomes the basis for relative coords
			case T_setUID:	//or is used to fix hdg/pitch info
				_Error.EmitSysErr("Can't cope with copied angles any more...");
			case T_rangepc:
				if (rot->range.Evaluate()!=ENABLE_COMPLEX_VAL)
					_Error.EmitSysErr("Range reused");
				rot->range=constructvalue(bfieldptr);
				rot->rangeispercent=TRUE;
			break;
			case T_range:
				if (rot->range.Evaluate()!=ENABLE_COMPLEX_VAL)
					_Error.EmitSysErr("Range reused");
				rot->range=constructvalue(bfieldptr);
				rot->rangeispercent=FALSE;
			break;
			case T_bearing:
				if (rot->hdg.Evaluate()!=ENABLE_COMPLEX_VAL)
					_Error.EmitSysErr("Heading reused");
				rot->hdg=constructvalue(bfieldptr);
			break;
			case T_pitch:
			case T_asimuth:
				if (rot->pitch.Evaluate()!=ENABLE_COMPLEX_VAL)
					_Error.EmitSysErr("Heading reused");
				rot->pitch=constructvalue(bfieldptr);
			break;
			case T_icpt:
			{
				UIDExpr*	itempos;
				if (rot->icpt.complex!=NULL)
					_Error.EmitSysErr("Heading reused");
				IcptExpr*	icpt;
				rot->icpt=icpt=new	IcptExpr;
				int	loopcount=getloopcount(bfieldptr);
				if (loopcount!=2)
					_Error.EmitSysErr("Expecting 2 parameters to intercept");
				switch (*(bfieldptr++))
				{
				case	T_target:
				case	T_setUID:
					icpt->objA=itempos=new UIDExpr;
					itempos->val=constructvalue(bfieldptr);
				break;
				case	T_pos:
					icpt->objA=constructposition(bfieldptr);
				break;
				default:
					_Error.EmitSysErr("Type of symbol not valid in BattleField getangle intercept");//JIM 28Mar96

				}
				switch (*(bfieldptr++))
				{
				case	T_target:
				case	T_setUID:
					icpt->objB=itempos=new UIDExpr;
					itempos->val=constructvalue(bfieldptr);
				break;
				case	T_pos:
					icpt->objB=constructposition(bfieldptr);
				break;
				default:
					_Error.EmitSysErr("Type of symbol not valid in BattleField getangle intercept(2)");//JIM 28Mar96
				}
			}
			break;
			case T_roll:
				if (constructvalue(bfieldptr).Evaluate()!=0)
					_Error.EmitSysErr("Roll non-zero? Roll no longer supported!");
			break;
			default:
				_Error.EmitSysErr("Type of symbol not valid in BattleField getangle");//JIM 28Mar96
		}
//TempCode JIM 16Jun97 	EventVal rv=rot;
	return(rot);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		constructposition
//Author		Jim Taylor
//Date			Thu 12 Jun 1997
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
EventVal Persons2::constructposition(string& bfieldptr)
{
	WorldExpr*	W=new WorldExpr;
	return	constructposition(bfieldptr,W);
}

WorldExpr* Persons2::constructposition(string& bfieldptr,WorldExpr*	W)
{
	XyzExpr*	XYZ	= (XyzExpr*)W->delta.complex;
	RotExpr*	rot	= (RotExpr*)W->rotate.complex;
	UIDExpr*	itempos	=(UIDExpr*)	W->uniqueID.complex;
	int	loopcount=getloopcount(bfieldptr);
	while (loopcount--)
		switch (*(bfieldptr++))
		{
		case	T_x:
			if (W->delta.complex==NULL)
				W->delta.complex=XYZ=new	XyzExpr;
			if (XYZ->X.Evaluate()==0)
				XYZ->X=constructvalue(bfieldptr);
			else
				_Error.EmitSysErr("X reused");
			W->deltaisabs=TRUE;
		break;
		case	T_y:
			if (W->delta.complex==NULL)
				W->delta.complex=XYZ=new	XyzExpr;
   //			if (XYZ->Y.Evaluate()!=0)
  	 //			_Error.EmitSysErr("Y reused");
			XYZ->Y=constructvalue(bfieldptr);
			W->deltaisabs=TRUE;
		break;
		case	T_z:
			if (W->delta.complex==NULL)
				W->delta.complex=XYZ=new	XyzExpr;
			if (XYZ->Z.Evaluate()==0)
				XYZ->Z=constructvalue(bfieldptr);
			else
				_Error.EmitSysErr("Z reused");
			W->deltaisabs=TRUE;
		break;
		case	T_abs:
		case	T_pos:
			constructposition(bfieldptr,W);
			XYZ=(XyzExpr*)W->delta.complex;
			rot=(RotExpr*)W->rotate.complex;
		break;
		case	T_target:
		case	T_setUID:
			if (W->uniqueID.complex)
				_Error.EmitSysErr("Already defined base position for item. Now doing UID.");
			W->uniqueID=itempos=new UIDExpr;
			itempos->val=constructvalue(bfieldptr);
		break;
		case	T_rel:
		{
			int	loopcount=getloopcount(bfieldptr);
			if (	(	W->delta.complex
					&&	(	(*bfieldptr==T_x &&	(XYZ->X.Evaluate() || W->deltaisabs))
						||	(*bfieldptr==T_y &&	(XYZ->Y.Evaluate() || W->deltaisabs))
						||	(*bfieldptr==T_z &&	W->deltaisabs)
//////more general test:|| *bfieldptr==T_x 硼 *bfieldptr==T_y 硼 *bfieldptr==T_z
					)	)
				||	(	W->rotate.complex
					&&	(*bfieldptr==T_icpt || *bfieldptr==T_range || *bfieldptr==T_rangepc)
				)	)
				
			{
				WorldExpr*	t=new WorldExpr;
				*t=*W;
				W->uniqueID=t;
				W->deltaisabs=FALSE;

				XYZ=NULL;
				rot=NULL;
			}
			while (loopcount--)
			//read all the relative data
			switch (*(bfieldptr++))
			{
			case	T_x:
				if (W->delta.complex==NULL)
					W->delta.complex=XYZ=new	XyzExpr;
				if (XYZ->X.Evaluate()==0)
					XYZ->X=constructvalue(bfieldptr);
				else
					_Error.EmitSysErr("X reused");
			break;
			case	T_y:
				if (W->delta.complex==NULL)
					W->delta.complex=XYZ=new	XyzExpr;
				if (XYZ->Y.Evaluate()==0)
					XYZ->Y=constructvalue(bfieldptr);
				else
					_Error.EmitSysErr("Y reused");
			break;
			case	T_z:
				if (W->delta.complex==NULL)
					W->delta.complex=XYZ=new	XyzExpr;
				if (XYZ->Z.Evaluate()==0)
					XYZ->Z=constructvalue(bfieldptr);
				else
					_Error.EmitSysErr("Z reused");
			break;
			case T_target:	//any object either becomes the basis for relative coords
			case T_setUID:	//or is used to fix hdg/pitch info
				if (W->uniqueID.complex)
					_Error.EmitSysErr("Already defined base position for item. Now doing UID.");
				W->uniqueID=itempos=new UIDExpr;
				itempos->val=constructvalue(bfieldptr);
			break;
			case T_rangepc:
				if (W->rotate.complex==NULL)
					W->rotate.complex=rot=new	RotExpr;
				if (rot->range.Evaluate()!=ENABLE_COMPLEX_VAL)
					_Error.EmitSysErr("Range reused");
				rot->range=constructvalue(bfieldptr);
				rot->rangeispercent=TRUE;
			break;
			case T_range:
				if (W->rotate.complex==NULL)
					W->rotate.complex=rot=new	RotExpr;
				if (rot->range.Evaluate()!=ENABLE_COMPLEX_VAL)
					_Error.EmitSysErr("Range reused");
				rot->range=constructvalue(bfieldptr);
				rot->rangeispercent=FALSE;
			break;
			case T_hdg:
			case T_bearing:
				if (W->rotate.complex==NULL)
					W->rotate.complex=rot=new	RotExpr;
				if (rot->hdg.Evaluate()!=ENABLE_COMPLEX_VAL)
					_Error.EmitSysErr("Heading reused");
				rot->hdg=constructvalue(bfieldptr);
			break;

			case T_pitch:
			case T_asimuth:
				if (W->rotate.complex==NULL)
					W->rotate.complex=rot=new	RotExpr;
				if (rot->pitch.Evaluate()!=ENABLE_COMPLEX_VAL)
					_Error.EmitSysErr("Heading reused");
				rot->pitch=constructvalue(bfieldptr);
			break;
			case T_icpt:
			{

				if (W->rotate.complex==NULL)
					W->rotate.complex=rot=new	RotExpr;
				if (rot->icpt.complex!=NULL)
					_Error.EmitSysErr("Heading reused");
				IcptExpr*	icpt;
				rot->icpt=icpt=new	IcptExpr;
				int	loopcount=getloopcount(bfieldptr);
				if (loopcount!=2)
					_Error.EmitSysErr("Expecting 2 parameters to intercept");
				switch (*(bfieldptr++))
				{
				case	T_target:
				case	T_setUID:
					icpt->objA=itempos=new UIDExpr;
					itempos->val=constructvalue(bfieldptr);
				break;
				case	T_pos:
					icpt->objA=constructposition(bfieldptr);
				break;
				default:
					_Error.EmitSysErr("Type of symbol not valid in BattleField getposition intercept");//JIM 28Mar96
				}
				switch (*(bfieldptr++))
				{
				case	T_target:
				case	T_setUID:
					icpt->objB=itempos=new UIDExpr;
					itempos->val=constructvalue(bfieldptr);
				break;
				case	T_pos:
					icpt->objB=constructposition(bfieldptr);
				break;
				default:
					_Error.EmitSysErr("Type of symbol not valid in BattleField getposition intercept(2)");//JIM 28Mar96
				}
			}
			break;
			default:
				_Error.EmitSysErr("Type of symbol not valid in BattleField getposition rel");//JIM 28Mar96
			}
		}
		break;
		default:
			_Error.EmitSysErr("Type of symbol not valid in BattleField constructposition");//JIM 28Mar96
		}
	return W;
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		throwtree
//Author		Jim Taylor
//Date			Wed 6 Dec 1995
//
//Description	Throw a branch away. Don't care what is in the branch.
//
//Inputs
//
//Returns	
//
//------------------------------------------------------------------------------
void		Persons2::throwtree(string& bfieldptr)
{
	switch (*(bfieldptr++))
	{
	case T_linklist:
	{
int		count=(*(bfieldptr++));
		while (count--)	throwtree(bfieldptr);
	}
	break;
	case T_nint:
	case T_int:
	case T_long:
	case T_nlong:
		bfieldptr+=2;
	case T_word:
	case T_nword:
		bfieldptr+=1;
	case T_byte:
	case T_nbyte:
		bfieldptr+=1;
	break;
	case T_comment:
	case T_family:
	case T_name:
		bfieldptr+=*bfieldptr+1;
	break;
	case 0xFF:
		_Error.EmitSysErr("Encountered -1 in throwtree. This means undefined!");
	default:
			throwtree(bfieldptr);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getloopcount
//Author		Jim Taylor
//Date			Wed 6 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	Persons2::getloopcount(string & bfieldptr)
{
	if (*bfieldptr!=T_linklist)
		return(1);
	elser
	{
		bfieldptr++;
		return((int)(UByte)*(bfieldptr++));
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		lowlevel_squadron
//Author		Jim Taylor
//Date			Wed 31 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Persons2::lowlevel_squadron(string& bfieldptr,info_airgrp& I)
{
	if (*bfieldptr!=T_linklist)
	{	//got a squad number equate...
		I.squadname=constructvalue(bfieldptr);
//DeadCode JIM 16Jun97 		return(lowlevel_squadron(snequ));
		return FALSE;
	}
	else
	{
int	loopcount=getloopcount(bfieldptr);
	while (loopcount--)
		switch (*(bfieldptr++))
		{
		case T_paintscheme:
					I.paintrules[I.usedpaintrules++]=constructvalue(bfieldptr,TRUE);
		break;
		case T_squadron: 	lowlevel_squadron(bfieldptr,I);				break;
		case T_skill:	 	I.skill=constructvalue(bfieldptr,TRUE);		break;
		case T_type:	 	I.type=constructvalue(bfieldptr,TRUE); 		break;
		case T_character:	I.character=constructvalue(bfieldptr,TRUE);	break;
		case T_home:	 	I.homebase=constructvalue(bfieldptr,TRUE); 	break;
		default:
			_Error.EmitSysErr("Type of symbol not valid in BattleField Airformdata");//JIM 28Mar96
		}
		return(TRUE);
	}
}

///////////////////
void	Persons2::AddSGToList(UniqueID newSGT)
{
	if (justscanning)
		return;
	if (!newSGT) 
		return;
	for (int i=0;i<LOADEDSGS;i++)
		if (loadedSG[i]==newSGT)
			return;

	for (int j=0;j<(int)LOADEDSGS-1;j++)
		if (loadedSG[j]==0)
		{
			loadedSG[j]=newSGT;
			return;
		}
	return;
}

bool	Persons2::DeleteBFItems(FileNum bfieldtoremove)
{
	int i;
	for (i=0;i<LOADEDBFS;i++)
		breakif(loadedBF[i]==bfieldtoremove);
	if (i==LOADEDBFS)
		return false;
	loadedBF[i]=FIL_NULL;
	for (int u=0;u<IllegalBAND;u++)
		if (pItem[u])
		{
			info_base *p=*pItem[u];
			if (p->bfieldindex==i)
			{
				pItem[u]=NULL;
				delete	p;
			}
		}
	return true;
}

bool	Persons2::BFLoaded(FileNum f)
{
	for (int i=0;i<LOADEDBFS;i++)
		if(loadedBF[i]==f)
			return true;
		return false;
}

bool	Persons2::GetSpareBFNumber(int& number)
{
	for (int i=0;i<LOADEDBFS;i++)
		if(loadedBF[i]==0)
		{
			number=i;
			return true;
		}
		return false;
}

int		Persons2::DeleteOldestBF()	//need schema to flag accesses...
{
#ifdef INT3
	INT3;

//	INT3;
#endif
	int r=Math_Lib.rnd((int)LOADEDBFS-4)+4; //FIX TO STOP MAINWORLD GETTING CHUCKED!
	DeleteBFItems(loadedBF[r]);
	return r;
}

///////////////////

#endif







