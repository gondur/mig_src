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
//Filename       savegame.cpp
//System         
//Author         Jim Taylor
//Date           Thu 22 Aug 1996
//Description    Various savegame routines - using overloading of << and >>
//_MIGALLEY_GUID					
//------------------------------------------------------------------------------
#undef NDEBUG
#include	"dosdefs.h"
#include	"myerror.h"
//#include <afx.h>
	#define F_GRAFIX
	#define F_SOUNDS
	#define F_BATTLE
#include "files.g"
//#include	"ui.h"
#include	"uniqueid.h"
#include	"worldinc.h"
#include	"bitfield.h"
#include	"text.h"

#include	"missman2.h"

#include	"bstream.h"
#include	"savegame.h"
#include	"analogue.h"
#include	"persons2.h"
#include	"3dcom.h"
#include	"mytime.h"
#include	"miles.h"
#include	<string.h>
#include	"groupitt.h"
#include	"replay.h"
#include "gameset.h"
#include "monotxt.h"
#undef	EmitSysErr
#define EmitSysErr ExitMode().SayAndQuit(__FILE__ "%i ",__LINE__),Error::dummyproc

SaveData	Save_Data;
DeadStream	Dead_Stream={0};
char	date[]="Rowan Savegame: " __DATE__ ;
char	date2[]="Rowan Savegame: " __DATE__ ;
inline	CString	LoadResString(int resnum)
{
	CString s;
	s.LoadString(resnum);
	return s;
};
extern void GetDriverAndMode(int&,int&,int&,int&);
extern void Configure(bool,HWND);
#include	"..\mfc\resource.h"


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		analogue
//Author		Jim Taylor
//Date			Tue 27 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	BOStream& operator  <<  (BOStream& bos,RunTimeDevDesc& devdesc)
{
	 bos<<devdesc.devid.Data1;
	 if (devdesc.devid.Data1)
	 {
		 bos<<devdesc.devid.Data2<<devdesc.devid.Data3;
		 bos.write((char*)devdesc.devid.Data4,8);
		 bos<<(char)devdesc.useff;
		 bos<<(char)devdesc.ismouse;
		 bos.write(devdesc.axismaps,devdesc.MAXMAPS);
		 bos.write(devdesc.hatmaps,devdesc.MAXMAPS);
	 }
	 return	bos;
}

static	BIStream& operator  >>  (BIStream& bis,RunTimeDevDesc& devdesc)
{
	 bis>>devdesc.devid.Data1;
	 if (devdesc.devid.Data1)
	 {
		 bis>>devdesc.devid.Data2>>devdesc.devid.Data3;
		 bis.read((char*)devdesc.devid.Data4,8);
		 bis>>(char&)devdesc.useff;
		 bis>>(char&)devdesc.ismouse;
		 bis.read(devdesc.axismaps,devdesc.MAXMAPS);
		 bis.read(devdesc.hatmaps,devdesc.MAXMAPS);
	 }
	 return bis;
}


	BOStream& operator	<<	(BOStream& bos,Analogue& analogue)
{
	for (int dev=0;dev<20;dev++)
		bos<<analogue.runtimedevices[dev];	
	for (int au=0;au<AU_MAX;au++)
		bos<<analogue.deadzones[au];
	return(bos);

}

	BIStream& operator	>>	(BIStream& bis,Analogue& analogue)
{
	for (int dev=0;dev<20;dev++)
		bis>>analogue.runtimedevices[dev];	
	for (int au=0;au<AU_MAX;au++)
		bis>>analogue.deadzones[au];
	analogue.LoadGame();
	return(bis);
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		savedata
//Author		Jim Taylor
//Date			Tue 27 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOStream& operator	<<	(BOStream& bos,SaveData& savedata)
{
	bos<<date2;
	bos.write((char*)&savedata,sizeof(SaveDataLoad));
	char z=0;
	bos<<savedata.lastsavegame<<z;
	bos<<savedata.lastreplayname<<z;
	bos<<savedata.lastpackname<<z;
	bos<<_Analogue;
	return(bos);

}
BIStream& operator	>>	(BIStream& bis,SaveData& savedata)
{
//	Mono_Text.Print(0,UByteP("Save_Data loading!"));
	bis>>date;
	if (strcmp(date,date2)==0)
	{
		bis.read((char*)&savedata,sizeof(SaveDataLoad));
		char buffer[180];
		char b=-1;
		for (int i=0;b;buffer[i++]=b)
			bis>>b;
		savedata.lastsavegame=buffer;
		for (b=-1,i=0;b;buffer[i++]=b)
			bis>>b;
		savedata.lastreplayname=buffer;
		for (b=-1,i=0;b;buffer[i++]=b)
			bis>>b;
		savedata.lastpackname=buffer;
		bis>>_Analogue;

		_Miles.SetGlobalVolumes(savedata.vol.sfx,savedata.vol.music,savedata.vol.engine,savedata.vol.anim,TRUE);//RJS 29Sep96
		Save_Data.successfulLoad=true;
	}
	else Save_Data.successfulLoad=false;
//DEAD		MessageBox(NULL,LoadResString(IDS_CONFIGIGNORED),LoadResString(IDS_CHOOSEPREFS),MB_OK);

	return(bis);
	
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		deadstream
//Author		Jim Taylor
//Date			Tue 27 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOStream& operator	<<	(BOStream& bos,DeadStream & deadstream)
{
	bos<<deadstream.olddaytime;
	for (DeadStream::DeadBlock* curr=deadstream.firstblock;curr;curr=curr->nextblock)
	{
		bos<<ULong(curr->SGT);
		bos<<curr->dataused;
		bos.write(curr->data,curr->dataused);
	}
		bos<<-1;
	return(bos);
}
BIStream& operator	>>	(BIStream& bis,DeadStream & deadstream)
{
	deadstream.ClrWorldDead();
	DeadStream::DeadBlock** curr=&deadstream.firstblock;
	bis>>deadstream.olddaytime;
	int uid;
	bis>>uid;
	while (uid!=-1)
	{
		curr[0]=new DeadStream::DeadBlock(UniqueID(uid));
		bis>>curr[0][0].dataused;
		bis.read(curr[0][0].data,curr[0][0].dataused);
		curr=&curr[0][0].nextblock;
		bis>>uid;
	}
	curr[0]=NULL;
	return(bis);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		campaign
//Author		Jim Taylor
//Date			Tue 27 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	BOStream& operator	<<	(BOStream& bos,Campaign& campaign)
{
	bos<<date2;
	bos<<campaign.garbage;
	bos.write((char*)&campaign+sizeof(CampaignPtrs),sizeof(Campaign)-sizeof(CampaignPtrs));
 	bos<<Dead_Stream;
	return(bos);

}

static	BIStream& operator	>>	(BIStream& bis,Campaign& campaign)
{
	bis>>date;
#ifndef MIG_DEMO_VER
	if (strcmp(date,date2))
		_Error.ReallyEmitSysErr("Savegame dates differ %s != %s",date,date2);
#endif
	bis>>campaign.garbage;
	bis.read((char*)&campaign+sizeof(CampaignPtrs),sizeof(Campaign)-sizeof(CampaignPtrs));
 	bis>>Dead_Stream;
	//Need to fix currmission and dfltmission pointers
	//
	//
//DEAD	switch (Miss_Man.currcampaignnum)
//DEAD	{
//DEAD		case MissMan::PEACETALKCAMPAIGN:
//DEAD		{
//DEAD
//DEAD			Miss_Man.camp.dfltmission = PeaceTalk_Missions [Miss_Man.camp.currmission_no];
//DEAD			Miss_Man.camp.currmission = Miss_Man.camp.dfltmission;
//DEAD			break;
//DEAD		}
//DEAD		case MissMan::SO51_CAMPAIGN:
//DEAD		{
//DEAD			Miss_Man.camp.currmission = Spring51_Missions [Miss_Man.camp.currmission_no];
//DEAD			Miss_Man.camp.dfltmission = Miss_Man.camp.currmission;
//DEAD			break;
//DEAD		}
//DEAD		case MissMan::INTROCAMPAIGN:
//DEAD		{
//DEAD			Miss_Man.camp.currmission = Intro_Missions [Miss_Man.camp.currmission_no];
//DEAD			Miss_Man.camp.dfltmission = Miss_Man.camp.currmission;
//DEAD			break;
//DEAD		}
//DEAD	}
	return(bis);
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		miss_man
//Author		Jim Taylor
//Date			Thu 22 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOStream& operator	<<	(BOStream& bos,MissMan& miss_man)
{

	strcpy(miss_man.camp.CommsPassword,_DPlay.Password);
	bos<<(SByte&) miss_man.currcampaignnum;
	bos<<miss_man.camp;
	SupplyTree::Save(bos);
	Todays_Packages.SaveGame(bos);	//must be last thing in savegame!!!
	return(bos);
}

BIStream& operator	>>	(BIStream& bis,MissMan& miss_man)
{

	if (!_Replay.Playback) // || _Replay.IsCampState(_Replay.PlaybackGameState))
	{
		if (Persons2::pItemSet())
			for (int p=0;p<Profile::MAX_PACKS;p++)
				Todays_Packages.ClearPack(p);
	}

	Persons4::ShutDownMapWorld();
//DeadCode DAW 27Jun99 	Persons4::StartUpMapWorld();
	bis>>(SByte&) miss_man.currcampaignnum;
	bis>>miss_man.camp;
	strcpy(_DPlay.Password,miss_man.camp.CommsPassword);
	SupplyTree::Load(bis);
	Persons4::StartUpMapWorld();
	Todays_Packages.LoadGame(bis);	//must be last thing in savegame!!!
	return(bis);
}






//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PutInfo
//Author		Jim Taylor
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------


CON	DeadStream::DeadBlockItterator::DeadBlockItterator
	(DeadBlockPtr& deadbase,UniqueID sgt)
{
	lastuniqueID=UID_NULL;
	base=&deadbase;
	SGT=sgt;
	newpage=false;
	if (!deadbase)
	{
		newpage=true;
		curr=
			deadbase=new DeadBlock(SGT);
	}
	else
		if (sgt==UID_NULL)
		{
			if (deadbase->SGT!=UID_NULL)
			{
				newpage=true;
				curr=new DeadBlock(sgt);
				curr->nextblock=deadbase;
				deadbase=curr;
			}
			else
				curr=deadbase;
		}
		else
		{
			DeadBlock* page=deadbase;
			while(page->nextblock && page->SGT!=sgt)
				page=page->nextblock;
			if (page->SGT==sgt)
				curr=page;
			else
			{
				newpage=true;
				curr=
					page->nextblock=
						new DeadBlock(sgt);
			}
		}
	off=0;
}

DES	DeadStream::DeadBlockItterator::~DeadBlockItterator()
{
	DeleteTempBlock();	//deletes temp block!!!
}

void	DeadStream::DeadBlockItterator::DeleteTempBlock()
{
	//first destructor the existing block...
	if (newpage && off==0)
	{
		if (*base==curr)
		{
			*base=curr->nextblock;
		}
		else
		{
			DeadBlock* tmp=*base;
			while (tmp->nextblock!=curr)
				tmp=tmp->nextblock;
			tmp->nextblock=curr->nextblock;
		}
		DeadBlock* tmp=curr;
		curr=tmp->nextblock;
		delete tmp;
	}
	newpage=false;

}
UniqueID	DeadStream::DeadBlockItterator::NextSGT()
{
	DeleteTempBlock();
	if (!curr)
		return UID_NULL;
	while (curr && curr->SGT==SGT)
		curr=curr->nextblock;
	if (!curr)
		return UID_NULL;
	SGT=curr->SGT;
	off=0;
	lastuniqueID=UID_NULL;
	return SGT;
}

bool	DeadStream::DeadBlockItterator::SkipToSGT(UniqueID sgt)
{
	DeleteTempBlock();
	if (!curr)
		return false;
	while (curr && curr->SGT!=sgt)
		curr=curr->nextblock;
	if (!curr)
		return false;
	SGT=sgt;
	off=0;
	lastuniqueID=UID_NULL;
	return true;
}

bool	DeadStream::DeadBlockItterator::PutInfo(void* src,int count)
{
	if (count+off>maxblocksize)
	{
		off=count;
		DeadBlock* tmp=new DeadBlock(SGT);
		tmp->nextblock=curr->nextblock;
		curr->nextblock=tmp;
		curr=tmp;
		memcpy(tmp->data,src,count);
		tmp->dataused=off;
		return true;
	}
	else
	{
		memcpy(curr->data+off,src,count);
		off+=count;
		curr->dataused=off;
		return false;
	}
}

void	DeadStream::DeadBlockItterator::GetInfo(void* trg,int count)
{
	if (count+off>maxblocksize)
	{
		curr=curr->nextblock;
		assert(SGT==curr->SGT);
		off=0;
	}
	memcpy(trg,curr->data+off,count);
	off+=count;
}

int	DeadStream::DeadBlockItterator::SkipCountedInfo()
{
	int count=GetWord();
	if (count+off>maxblocksize)
	{
		curr=curr->nextblock;
		assert(SGT==curr->SGT);
		off=0;
	}
////////	memcpy(trg,curr->data+off,count);
	off+=count;
	return count;

}

void	DeadStream::DeadBlockItterator::NextDeadElt(UByte&di1b,int&diplc,char*&dipld)
{
	char firstbyte=GetByte();
	if (((MinAnimData&)firstbyte).IsInvisible)
	{
		((MinAnimData&)firstbyte).IsInvisible=FALSE;
		di1b=firstbyte;
		int count=GetWord();
		if (count+off>maxblocksize)
		{
			curr=curr->nextblock;
			assert(SGT==curr->SGT);
			off=0;
		}
		diplc=count;
		dipld=curr->data+off;
		off+=count;
	}
	else
	{
		di1b=firstbyte;
		diplc=0;
		dipld=NULL;
	}
}

void	DeadStream::DeadBlockItterator::NextEltClearDamage()
{
	char firstbyte=GetByte();
	((MinAnimData&)firstbyte).itemstate=0;
	curr->data[off-1]=firstbyte;
	if (((MinAnimData&)firstbyte).IsInvisible)
		SkipCountedInfo();
}


void	DeadStream::DeadBlockItterator::SetNextDeadElt(char di1b,int diplc,char* dipld)
{
	if (diplc)
	{
		((MinAnimData&)di1b).IsInvisible=TRUE;
		PutByte(di1b);
		PutCountedInfo(dipld,diplc);
	}
	else
	{
		((MinAnimData&)di1b).IsInvisible=FALSE;
		PutByte(di1b);
	}
}
void	DeadStream::DeadBlockItterator::SkipNextDeadElt()
{
	char firstbyte=GetByte();
	if (((MinAnimData&)firstbyte).IsInvisible)
		SkipCountedInfo();
}

UniqueID	DeadStream::DeadBlockItterator::SkipItem()
{
	if (lastuniqueID)
		while (--lastnumelts>=0)
			SkipNextDeadElt();
	else
		if (off)
			return (UniqueID)lastuniqueID;
	UWord get=
	lastuniqueID=GetWord();
	if (lastuniqueID)
	{
		
		lastStatus=GetWord();
		lastshape=GetWord();
		lastnumelts=GetByte();
	}
	return (UniqueID)lastuniqueID;
}

bool	DeadStream::DeadBlockItterator::SkipToItem(UniqueID trg)
{
	if (trg==lastuniqueID)
		return true;
	do
		SkipItem();
	while (lastuniqueID!=UID_NULL && lastuniqueID!=trg);
	return (trg==lastuniqueID);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClrWorldDead
//Author		Jim Taylor
//Date			Mon 2 Sep 1996
//
//Description	Clear all dead fields
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------

void	DeadStream::ClrWorldDead()
{
	DeadBlockPtr tmp=firstblock;
	firstblock=NULL;
	while (tmp)
	{
		DeadBlockPtr tmp2=tmp->nextblock;
		delete tmp;
		tmp=tmp2;
	}
}

bool	DeadStream::ClearForSGT(UniqueID sgt)
{
	DeadBlockPtr* p=&firstblock;
	while (*p && p[0][0].SGT!=sgt)
		p=&p[0][0].nextblock;
	if (*p)
	{
		DeadBlockPtr tmp=*p;
		while (tmp && tmp->SGT==sgt)
		{
			DeadBlockPtr tmp2=tmp->nextblock;
			delete tmp;
			tmp=tmp2;
		}
		*p=tmp;
		return true;
	}
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
//
// Function:    MainWorldBand
// Date:        24/02/99
// Author:      JIM
//
// Description: Flags that these SGT items are kept in the main world indexed directly by their UID
//
////////////////////////////////////////////////////////////////////////
bool	DeadStream::DontRecordBand(UniqueID u)						  //DAW 6/15/99
{
	UniqueIDBand	b=Persons2::getbandfromUID(u);
	return(		b==RedAAASiteBAND	);
}
bool	DeadStream::MainWorldBand(UniqueID u)
{
	UniqueIDBand	b=Persons2::getbandfromUID(u);
	return(		b==RedAAALargeBAND
			||	b==AmberBridgeBAND
			||	b==RunwaySBAND
			||	b==RunwayEBAND
			);


}
void	DeadStream::SetWorldDead(WorldStuff* world)
{
	MAKEFIELD(UniqueID,UID_NULL,IllegalSepID);
	UniqueIDField	issgt;
	issgt=0;
	ClearForSGT(UID_NULL);
	{
		DeadBlockItterator b(firstblock,UID_NULL);
		for (int i=0;i<WorldStuff::PITEMTABLESIZE;i++)
			if (world->pItem[i])
			{
				ItemBasePtr t1=world->pItem[i];
				if (t1->Status.size!=WAYPOINTSIZE && t1->Status.size<MOBILESIZE)
				{
					ItemPtr	tmp=*t1;
					if (	tmp->SGT &&	!MainWorldBand(UniqueID(i)))
						issgt|=tmp->SGT;
					else
						if (tmp->Anim != NULL)
						{	//may have to step through every elt in group doing this!
							//but will save some anim space by doing so.
							bool	nonzero=(tmp->Status.deadtime!=0);
							{
								GroupItterator g(tmp->shape,tmp->Anim);
								if (g.NumElts())
								{	nonzero|=(g.status!=0);
									if (!nonzero)
										while(g++) nonzero|=(g.status!=0);	}
							}
							if (nonzero)
							{
								if (tmp->SGT)
									tmp=tmp;
								GroupItterator g(tmp->shape,tmp->Anim);
								int elts=g.NumElts();
								b.PutWord((short)tmp->uniqueID.count); //DAW 09/05/99 as per Jims instructions
								b.PutWord((short&)tmp->Status);
								b.PutWord((short&)tmp->shape);
						if (elts==-1)
							elts=elts;
								b.PutByte(elts);
								if (elts)
									do{
										assert	(elts--);
										b.SetNextDeadElt(g.AnimDataByte(),g.PostLauncherDataSize(),g.PostLauncherDataLoc());
									}while (g++);
								assert(elts==0);
			}	}		}	}
		b.PutWord(0);
	}
	for (int sgt=0;sgt<WorldStuff::PITEMTABLESIZE;sgt++)
		if (issgt[(UniqueID)sgt])
		{
			bool wrote=false;
			int band=0,uidnum=0;
			ClearForSGT(UniqueID(sgt));
			DeadBlockItterator b(firstblock,UniqueID(sgt));
			if (Persons2::getbandfromUID(UniqueID(sgt))!=AmberBattleNodeBAND)
			for (int i=0;i<WorldStuff::PITEMTABLESIZE;i++)
				if (world->pItem[i])
				{
					ItemBasePtr t1=world->pItem[i];
					if (t1->Status.size!=WAYPOINTSIZE && t1->Status.size<MOBILESIZE)
					{
						ItemPtr	tmp=*t1;
						if (	tmp->SGT==sgt						  //DAW 6/15/99
							&&	!MainWorldBand(UniqueID(i))			  //DAW 6/15/99
							&&	!DontRecordBand(UniqueID(i))		  //DAW 6/15/99
							)										  //DAW 6/15/99
							if (tmp->Anim != NULL)
							{
								bool	nonzero=(tmp->Status.deadtime!=0);
								{
									GroupItterator g(tmp->shape,tmp->Anim);
									if (g.NumElts())
									{
										nonzero|=(g.status!=0);
										if (!nonzero)
											while(g++)
												nonzero|=(g.status!=0);
									}
								}

								int uidval=Persons2::getbandfromUID(UniqueID(tmp->uniqueID.count));
								if (uidval==band)
									uidnum++;
								else
									uidnum=band=uidval;

								if (nonzero)
								{
									wrote=true;
									b.PutWord(uidnum);
									b.PutWord((short&)tmp->Status);
									b.PutWord((short&)tmp->shape);
									GroupItterator g(tmp->shape,tmp->Anim);
									int elts=g.NumElts();
						if (elts==-1)
							elts=elts;
  									b.PutByte(elts);
									do	b.SetNextDeadElt(g.AnimDataByte(),g.PostLauncherDataSize(),g.PostLauncherDataLoc());
									while (g++);
				}	}		}	}
			if (wrote)
				b.PutWord(0);
		}
		{SWord	s;
		for (DeadBlockItterator	b(firstblock,UID_NULL);(s=b.SkipItem())!=UID_NULL;)
		{	ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(s));
			assert(p && (p->SGT==NULL ||  MainWorldBand(UniqueID(s))));
		}}
}
void	DeadStream::GetWorldDead(WorldStuff* world)
{
		{SWord	s;
		for (DeadBlockItterator	b(firstblock,UID_NULL);(s=b.SkipItem())!=UID_NULL;)
		{	ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(s));
			assert(p && (p->SGT==NULL ||  MainWorldBand(UniqueID(s))));
		}}
	UniqueID SGT=UID_NULL;
	DeadBlockItterator	b(firstblock,UID_NULL);
	int targuid=b.GetWord();
	while(targuid)
	{
		ItemPtr t1=*world->pItem[targuid];
		if (t1 && InfoItemFlagPtr(t1)->Minus1!=-1)
		{
			assert(t1->SGT==UID_NULL || MainWorldBand(UniqueID(targuid)));
			(short&)t1->Status=b.GetWord();
			int shapenum=b.GetWord();
			assert(shapenum=t1->shape);

			int tst;
			if (t1->Anim==NULL)
				tst=SHAPE.SetAnimData(t1,0);			//RDH 23Sep96
			else
				tst=SHAPE.GetAnimDataSize(t1->shape);
			GroupItterator g(t1->shape,t1->Anim);
			char count=b.GetByte();
			do{
				UByte	first;
				int		datalen;
				char*	src;
				b.NextDeadElt(first,datalen,src);
				g.AnimDataByte()=first;
				assert(g.PostLauncherDataSize()==datalen);
				memcpy(g.PostLauncherDataLoc(),src,datalen);
				assert(count--);
			}while (g++);
		}
		else
		{
			b.GetWord();	//long dead
			b.GetWord();	//shape
			char count=b.GetByte();	//first anim byte
			while (count--)
				b.SkipNextDeadElt();
		}
		targuid=b.GetWord();
	}
	SGT=b.NextSGT();
	while(SGT)
	{
		for (int i=0;i<WorldStuff::PITEMTABLESIZE;i++)
			if (!MainWorldBand(UniqueID(i)))
				if (world->pItem[i])
				{
					ItemBasePtr t1=world->pItem[i];
					if (t1->Status.size!=WAYPOINTSIZE && t1->Status.size!=AIRSTRUCSIZE && InfoItemFlagPtr(t1)->Minus1!=-1)
					{
						ItemPtr	tmp=*t1;
						if (tmp->SGT==SGT)
							break;
					}
				}

		if (i!=WorldStuff::PITEMTABLESIZE)
		{

			int targuid=b.GetWord();
			int band=0,bandcount=0,lastuid=0;
			while(targuid)
			{
				int targband=Persons2::getbandfromUID(UniqueID(targuid));
				int targbandMAX=Persons2::getbandMAXfromUID(UniqueID(targuid));
				targuid-=targband;
				if (targband!=band)
				{
					band=targband;
					bandcount=0;
					lastuid=band;
				}
				ItemPtr p=NULL;
				for (int skip=targuid-bandcount,u=lastuid;skip>=0;u++)
				{
					p=NULL;
					breakif(u==targbandMAX);
					p=*world->pItem[u];
					if (p && p->SGT==SGT)
						skip--;
				}
				if (p && InfoItemFlagPtr(p)->Minus1!=-1)
				{
					(short&)p->Status=b.GetWord();
					int shapenum=b.GetWord();
					assert(shapenum==p->shape);
					int tst;
					if (p->Anim==NULL)
						tst=SHAPE.SetAnimData(p,0);			//RDH 23Sep96
					else
						tst=SHAPE.GetAnimDataSize(p->shape);

					GroupItterator g(p->shape,p->Anim);
					char count=b.GetByte();
					do{
						UByte	first;
						int		datalen;
						char*	src;
						b.NextDeadElt(first,datalen,src);
						g.AnimDataByte()=first;
						assert(g.PostLauncherDataSize()==datalen);
						memcpy(g.PostLauncherDataLoc(),src,datalen);
						assert(count--);
					}while (g++);
					lastuid=p->uniqueID.count+1;

				}
				else
				{
					b.GetWord();	//long dead
					b.GetWord();	//shape
					char count=b.GetByte();	//first anim byte
					while (count--)
						b.SkipNextDeadElt();
					lastuid=targbandMAX-1;
				}
				bandcount=targuid+1;
//DEADCODE JIM 10/06/99 				lastuid=p->uniqueID.count+1;
				targuid=b.GetWord();
			}
		}
		SGT=b.NextSGT();
	};
}


//////////////////////////////////////////////////////////////////////
//
// Function:    ReviveWorld
// Date:		30/04/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	DeadStream::ReviveWorld(const int repairpointsinperiod,int repairbridgepointsinperiod)
{	//have to make second copy of each block as go along
	//second copy has alive items removed, so damage is forgotten.

	//"Simplified" Mig Alley repair scheme:
	//	Each super group has a limited number of points of repair per period
	//	Each point is 1 element in a group.
	//  This bit is not done:
	//		If an element is a large shape (>200pts) it is repaired 1 level.
	//		If an element is a medium shape (>100pts) repaired 2 levels
	//		If an element is a small shape (<100pts) repaired 3 levels
	//
	//	The problem I have is in accounting for mainworld and subworld elements of same SGT
	//	as I only want to process the list once!
	//
	//	First job is to get together a list of the UIDs that have been damaged
	//	UniqueIDField costs 16K/8=2Kb
	//	If I spend 4 bytes on each SGT that allows 500 SGTs in the same space.
	//
	//

	// IMPORTANT NOTE:
	//	Each SGT member item that is damaged then repaired MUST stay in the list fully
	//  alive for 1 more session in order for the repair to register.
	//	This means that each MainWorld item must stay for 1 turn, and each subworld SGT
	//  block must stay for 1 turn.
	//
	//	The logic is such that the MainWorld is being kept, but the subworld is not.
	//
	//

		{SWord	s;
		for (DeadBlockItterator	b(firstblock,UID_NULL);(s=b.SkipItem())!=UID_NULL;)
		{	ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(s));
			assert(p && (p->SGT==NULL ||  MainWorldBand(UniqueID(s))));
		}}

	if (firstblock)
	{

		struct	DamagedSGT
		{
			FIRSTFIELD(ULong,	UniqueID,uniqueid,13)			//UID is 14 bits
				BITFIELD(			ULong,pointsleft,14,18)		//max repair points = 31
				LASTFIELD(			ULong,eltsleft,19,31);		//max elts to repair= 8K
		};
		enum	{MAX_DAMAGELIST=400};
		int	usedentries=0;
		DamagedSGT	damagelist[MAX_DAMAGELIST];
		{//scan of deadstream to find num of elements in all supergroups
			DeadBlockItterator	src(firstblock,UID_NULL);
			int targuid;
			UniqueID SGT;
			while ((targuid=src.GetWord())!=UID_NULL)
			{
				ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(targuid));
				assert(p);
				if (p->SGT)
				{
					assert(MainWorldBand(UniqueID(targuid)));
					SGT=p->SGT;
				}
				else
					SGT=(UniqueID)targuid;

				for (int entry=0;entry<usedentries;entry++)
					breakif (damagelist[entry].uniqueid==SGT);
				if (entry==usedentries)
				{
					usedentries++;
					damagelist[entry].uniqueid=SGT;
					damagelist[entry].eltsleft=0;
				}

				UWord status=src.GetWord();
				UWord shape=src.GetWord();
				int	numelts=src.GetByte();
				while (numelts--)
				{	char v=src.GetByte();
					MinAnimData firstbyte=(MinAnimData&)v;
					if (firstbyte.itemstate)
						damagelist[entry].eltsleft=damagelist[entry].eltsleft+1;
					if (firstbyte.IsInvisible)
						src.SkipCountedInfo();
				}
				
			}
			while ((SGT=src.NextSGT())!=UID_NULL)
			{
				for (int entry=0;entry<usedentries;entry++)
					breakif (damagelist[entry].uniqueid==SGT);
				if (entry==usedentries)
				{
					usedentries++;
					damagelist[entry].uniqueid=SGT;
					damagelist[entry].eltsleft=0;
				}
				while ((targuid=src.GetWord())!=UID_NULL)
				{
					//skip rest of info
					UWord status=src.GetWord();
					UWord shape=src.GetWord();
					int	numelts=src.GetByte();
					while (numelts--)
					{	char v=src.GetByte();
						MinAnimData firstbyte=(MinAnimData&)v;
						if (firstbyte.itemstate)
							damagelist[entry].eltsleft=damagelist[entry].eltsleft+1;
						if (firstbyte.IsInvisible)
							src.SkipCountedInfo();
					}
				}
			}
			for (int entry=0;entry<usedentries;entry++)
			{													//DAW 27Jun99
				if (Persons2::getbandfromUID(damagelist[entry].uniqueid)==AmberBridgeBAND)
					damagelist[entry].pointsleft=repairbridgepointsinperiod;
				else
					damagelist[entry].pointsleft=repairpointsinperiod+damagelist[entry].eltsleft/7;
			}
		}

		//ok.. now step through and repair.

		//
		//A group is fully repaired when all it's elements are cleared.
		//How do I know it is fully repaired, though?
	
		//I WON'T REMOVE AN ITEM UNTIL THE NEXT DAY
		//I won't remove an item unless there are no more damaged elements to follow
		//in the main world
		DeadBlock* newlist=NULL;

		{//scan of deadstream to revive
			DeadBlockItterator	src(firstblock,UID_NULL);
			int targuid;
			UniqueID SGT;
			Math_Lib.ResetRndCount();
			{//mainworld block
				DeadBlockItterator  trg(newlist,UID_NULL);
				bool reallyput=false;
				while ((targuid=src.GetWord())!=UID_NULL)
				{
					ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(targuid));
					if (p && p->SGT)
						SGT=p->SGT;
					else
						SGT=(UniqueID)targuid;

					for (int entry=0;entry<usedentries;entry++)
						breakif (damagelist[entry].uniqueid==SGT);
					if (damagelist[entry].eltsleft==0)
					{	//skip and discard
						UWord status=src.GetWord();
						UWord shape=src.GetWord();
						int	numelts=src.GetByte();
						while (numelts--)
						{
							char v=src.GetByte();
							MinAnimData firstbyte=(MinAnimData&)v;
							if (firstbyte.IsInvisible)
								src.SkipCountedInfo();
						}
					}
					else
					{

						UWord status=src.GetWord();
						UWord shape=src.GetWord();
						int	numelts=src.GetByte();
						reallyput=true;
						trg.PutWord(targuid);
						trg.PutWord(status);
						trg.PutWord(shape);
						if (numelts==-1)
							numelts=numelts;
						trg.PutByte(numelts);

						while (numelts--)
						{
							UByte stat;
							int datalen;
							char* data;
							src.NextDeadElt(stat,datalen,data);
							MinAnimData firstbyte=(MinAnimData&)stat;
							if (firstbyte.itemstate)
							{
								if (Math_Lib.rnd()*damagelist[entry].eltsleft<damagelist[entry].pointsleft*65536)
								{
									firstbyte.itemstate--;
									damagelist[entry].pointsleft=damagelist[entry].pointsleft-1;
									stat=(char&)firstbyte;
								}
								damagelist[entry].eltsleft=damagelist[entry].eltsleft-1;
							}
							trg.SetNextDeadElt(stat,datalen,data);
						}//while numelts
					}//if eltsleft
				}//while getword
				if (reallyput)
					trg.PutWord(UID_NULL);
			}//mainworld block


			while ((SGT=src.NextSGT())!=UID_NULL)
			{
				for (int entry=0;entry<usedentries;entry++)
					breakif (damagelist[entry].uniqueid==SGT);
				if (damagelist[entry].eltsleft)
				{
					Math_Lib.ResetRndCount();
					DeadBlockItterator  trg(newlist,SGT);
					while ((targuid=src.GetWord())!=UID_NULL)
					{
						if (damagelist[entry].eltsleft==0)
						{	//skip and discard
							UWord status=src.GetWord();
							UWord shape=src.GetWord();
							int	numelts=src.GetByte();
							while (numelts--)
							{
								char v=src.GetByte();
								MinAnimData firstbyte=(MinAnimData&)v;
								if (firstbyte.IsInvisible)
									src.SkipCountedInfo();
							}
						}
						else
						{
							UWord status=src.GetWord();
							UWord shape=src.GetWord();
							int	numelts=src.GetByte();
							trg.PutWord(targuid);
							trg.PutWord(status);
							trg.PutWord(shape);
						if (numelts==-1)
							numelts=numelts;
							trg.PutByte(numelts);

							while (numelts--)
							{
								UByte stat;
								int datalen;
								char* data;
								src.NextDeadElt(stat,datalen,data);
								MinAnimData firstbyte=(MinAnimData&)stat;
								if (firstbyte.itemstate)
								{
									if (Math_Lib.rnd()*damagelist[entry].eltsleft<damagelist[entry].pointsleft*65536)
									{
										firstbyte.itemstate--;
										damagelist[entry].pointsleft=damagelist[entry].pointsleft-1;
										stat=(char&)firstbyte;
									}
									damagelist[entry].eltsleft=damagelist[entry].eltsleft-1;
								}
								trg.SetNextDeadElt(stat,datalen,data);
							}//whilenumelts

						}//if eltsleft
					}//while getword
					trg.PutWord(0);							  //JIM 13/05/99
				}//if eltsleft
				else
				{
					if ((targuid=src.GetWord())!=UID_NULL)
					{	//Keep for 1 day only so last of repair gets through!
						DeadBlockItterator  trg(newlist,SGT);
						trg.PutWord(0);							  //JIM 13/05/99
					}
				}
			}//while SGT
		}//block trg
		ClrWorldDead();
		firstblock=newlist;
//
//		Extra debug checks. The rror must be here!!!!
//
//
//
		{SWord	s;
		for (DeadBlockItterator	b(firstblock,UID_NULL);(s=b.SkipItem())!=UID_NULL;)
		{	ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(s));
			assert(p && (p->SGT==NULL ||  MainWorldBand(UniqueID(s))));
		}}

		olddaytime++;//=newdaytime;
	}
}




int	DeadStream::DecodeDamage(UniqueID SGT,DamageDef* damagetable)
{	//first find damage for SGT
		{SWord	s;
		for (DeadBlockItterator	b(firstblock,UID_NULL);(s=b.SkipItem())!=UID_NULL;)
		{	ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(s));
			assert(p && (p->SGT==NULL ||  MainWorldBand(UniqueID(s))));
		}}
	int	numreturned=0;
	{
		DeadBlockItterator	b(firstblock,UID_NULL);
		if (b.SkipToItem(SGT))
		{
			damagetable->memberid=SGT;
			damagetable->loadedid=SGT;
			(UWord&)damagetable->status=b.lastStatus;
			damagetable->shape=ShapeNum(b.lastshape);
//			char elts=b.GetByte();
//			while (--elts>=0)
//			{
//				char v=b.GetByte();	//first anim byte
//				if (((MinAnimData&)v).IsInvisible)
//					b.SkipCountedInfo();
//			}
//			{
//				damagetable->animbytesskip=0;
//				damagetable->animbyteslen=0;
//				damagetable->remaininganimbytes=NULL;
//			}
			damagetable++;
			numreturned++;
		}
	}
	{
		UniqueID s;
		for (DeadBlockItterator	b(firstblock,UID_NULL);(s=b.SkipItem())!=UID_NULL;)
			if (Persons2::ConvertPtrUID(s))
			if (ItemPtr(*Persons2::ConvertPtrUID(s))->SGT==SGT)
			{
				assert(MainWorldBand(s));
				Persons2::ConvertPtrUID(s)->Status.deaded=TRUE;
				damagetable->memberid=s;
				damagetable->loadedid=s;
				(UWord&)damagetable->status=b.lastStatus;
				damagetable->shape=ShapeNum(b.lastshape);
				damagetable++;
				numreturned++;
			}
	}

	{
		UniqueID targuid;
		for (DeadBlockItterator	c(firstblock,SGT);(targuid=c.SkipItem())!=UID_NULL;)
		{	//need to convert targuid to correct element uid
			damagetable->memberid=targuid;

			int targband=Persons2::getbandfromUID(targuid);
			ItemPtr p;
			for (int skip=targuid-targband,u=targband,max=Persons2::getbandMAXfromUID(targuid);skip>=0;u++)
			{
				if (u==max)
				{
					u=0;
					p=NULL;
					break;
				}
				p=*Persons2::ConvertPtrUID(UniqueID(u));
				if (p && p->SGT==SGT)
					skip--;
			}
			if (u && p && p->SGT==SGT)
			{
				damagetable->loadedid=UniqueID(u-1);
				p->Status.deaded=TRUE;
			}
			else
				damagetable->loadedid=UID_NULL;
			(UWord&)damagetable->status=c.lastStatus;
			damagetable->shape=ShapeNum(c.lastshape);

			{
				damagetable->animbytesskip=0;
				damagetable->animbyteslen=0;
				damagetable->remaininganimbytes=NULL;
			}
			damagetable++;
			numreturned++;
		}
	}
	return numreturned;
}
//
// ShapeItterator -- DeadBlockItterator interface
//
//
//
//
 
DeadStream::DeadBlockItterator*	
	GroupItterator::DeadIttCopy(DeadStream::DeadBlockItterator* I)
{
	return new DeadStream::DeadBlockItterator(I); 
}
void	GroupItterator::DeadIttDelete(DeadStream::DeadBlockItterator* I)
{
	delete I;
}
void	GroupItterator::NextDeadIttElt(DeadStream::DeadBlockItterator* I,UByte&di1b,int&diplc,char*&dipld)
{
	I->NextDeadElt(di1b,diplc,dipld);
}


//
// Group -- ShapeItterator interafce dummies
//
//		 ... code in mfc\damage.cpp
//
//DeadCode RJS 15Feb99 bool	GroupItterator::operator++(int)		{status++;return (status<10);}				
//move on to next element? 
//if not NULL Push animptr,grpindexer, and deadstream forward
//DeadCode RJS 15Feb99 GroupItterator::operator bool()		{return (status<10);}	//reached end of group?


//DeadCode RJS 15Feb99 int GroupItterator::NumElts(void)	
//DeadCode RJS 15Feb99 {return 5;}
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 char& GroupItterator::AnimDataByte()
//DeadCode RJS 15Feb99 {
//DeadCode RJS 15Feb99 	static char dummy=5;
//DeadCode RJS 15Feb99 	return dummy;
//DeadCode RJS 15Feb99 }
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 int GroupItterator::PostLauncherDataSize()
//DeadCode RJS 15Feb99 {
//DeadCode RJS 15Feb99 	return 0;
//DeadCode RJS 15Feb99 }
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 char * GroupItterator::PostLauncherDataLoc()
//DeadCode RJS 15Feb99 {
//DeadCode RJS 15Feb99 	return NULL;
//DeadCode RJS 15Feb99 }

static	DistanceFactors	
Distance[]=
{
	{	//SHORT			//MEDIUM		//far
		10000,			1000,			100000,
		IDS_CM_NAME,	IDS_M_NAME,		IDS_KM_NAME,
		IDS_CM_SH,		IDS_M_SH,		IDS_KM_SH
	},
	{
		25440,				305,		185300,
		IDS_IN_NAME,	IDS_FT_NAME,	IDS_NM_NAME,
		IDS_IN_ABBR,	IDS_FT_ABBR,	IDS_NM_ABBR
	}
};
static	AltitudeFactors
Altitude[]=
{
	{	//SHORT			//MEDIUM		//far
		10000,			1000,			100000,
		IDS_CM_NAME,	IDS_M_NAME,		IDS_KM_NAME,
		IDS_CM_SH,		IDS_M_SH,		IDS_KM_SH,
		//scale
		500,2,26
	},
	{
		25440,			305,			30480,
		IDS_IN_NAME,	IDS_FT_NAME,	IDS_THFT_NAME,
		IDS_IN_ABBR,	IDS_FT_ABBR,	IDS_THFT_ABBR,
		//scale
		1000,2,40
	}
};
static	SpeedFactors
Speed[]=
{
	{	//persec		//permin		//perhr
		0.1,				6.0,		0.36,
		IDS_MPERSEC,	IDS_MPERMIN,	IDS_KMPERHR,
		IDS_MPSEC,		IDS_MPMIN,		IDS_KMPHR
	},
	{
		0.25440,		0.5088,			0.19426,	//0.5147,	//CSB 23/06/99	
		IDS_INPERSEC,	IDS_FTPERMIN,	IDS_KNOTTS,
		IDS_INPS,		IDS_FTPM,		IDS_KTS
	}
};
static	MoneyFactors
Money[]=
{
	{
		100,		//penceperunit;
		100,		//fractionsperunit;
		'.',		//fractionseparator;
		IDS_PENCE,	IDS_POUNDS,	//unitname,
		IDS_PEE,	IDS_PNDS	//unitabbr;
	}
};
static	MassFactors
Mass[]=
{
	{//conversion in grammes
		1000,
		IDS_KG,
		IDS_KG
	},
	{
		454,
		IDS_LBS,
		IDS_LBS
	}
};
void	SetFiltersFromSaveGame();
void SaveData::SetUnits()
{
	if (Save_Data.gamedifficulty [GD_UNITS])
	{
		dist=Distance[METRIC];
		alt=Altitude[METRIC];
		mass = Mass[METRIC];
		speed=Speed[METRIC];
	}else
	{
		dist=Distance[IMPERIAL];
	   	alt=Altitude[IMPERIAL];
		mass = Mass[IMPERIAL];
	   	speed=Speed[IMPERIAL];
	}

}
void SaveData::InitPreferences(int wh)
{
	HWND hWnd=(HWND)wh;
	flightdifficulty %= FD_THRUSTPOWERCONTROL;		// done for jet, but not prop
	flightdifficulty %= FD_TORQUEEFFECTS;				// done
	flightdifficulty %= FD_JETFLAMEOUT;				// done
	flightdifficulty %= FD_LIMITEDFUEL;				// wait for Robert
	flightdifficulty %= FD_POWERBOOST;				// done
	flightdifficulty |= FD_AUTOTHROTTLE;				// done
	flightdifficulty %= FD_WINDEFFECTS;				// done
	flightdifficulty %= FD_WINDGUSTS;					// done
	flightdifficulty %= FD_AIRCRAFTINTERFERENCE;		// wait for ACM to be implemented
	flightdifficulty %= FD_IDEALSANDCONTROL;			// Big job, implement jointly with ACM model
	flightdifficulty %= FD_COORDINATEDRUDDER;			// done
	flightdifficulty |= FD_SPINS;						// done
	flightdifficulty %= FD_SLIPSTREAMEFFECTS;			// done
	flightdifficulty |= FD_GEARSUSPENSION;			// done, but upgrade "SimpleGearCalcs" & "Ground"
	flightdifficulty %= FD_EXCESSIVEACCELDAMAGE;		// wait for Robert
	flightdifficulty %= FD_STORESWEIGHTDRAG;			// wait for Robert
	gamedifficulty |= GD_VULNERABLE;
	gamedifficulty |= GD_AUTOPADLOCKTOG;
	gamedifficulty |= GD_GEFFECTS;									  //rdh 14/04/99
	gamedifficulty |= GD_INJURYEFFECTS;								  //rdh 14/04/99
	gamedifficulty |= GD_WHITEOUT;									  //rdh 14/04/99
	gamedifficulty |= GD_PERFECTRADARASSISTEDGUNSIGHT;				  //rdh 14/04/99
	gamedifficulty |= GD_PERIPHERALVISION;							  //rdh 14/04/99
	gamedifficulty |= GD_HUDINSTACTIVE;								  //rdh 14/04/99
	gamedifficulty |= GD_AUTOVECTORING;								  //RDH 18/04/99
	gamedifficulty %= GD_VISIBLEMIGSCHEAT;
	gamedifficulty |=  GD_DISPLAYMESSAGES;

#ifdef	MIG_DEMO_VER
	gamedifficulty |= GD_GUNCAMERACOLOUR;
#endif

	keysensitivity=2;												  //JIM 11/06/99
	if (LoadResString(IDS_SHORT_DIST_ABBR)[0]==LoadResString(IDS_CM_SH)[0])
	{
		dist=Distance[METRIC];
		gamedifficulty |= GD_UNITS;
	}else
	{
	   	dist=Distance[IMPERIAL];
		gamedifficulty %= GD_UNITS;
	}

	if (LoadResString(IDS_SHORT_ALT_ABBR)[0]==LoadResString(IDS_CM_SH)[0])
		alt=Altitude[METRIC];
	else
	   	alt=Altitude[IMPERIAL];
	if  (LoadResString(IDS_MASS_ABBR)[0]==LoadResString(IDS_KG)[0])
		mass = Mass[METRIC];
	else
		mass = Mass[IMPERIAL];
	if (LoadResString(IDS_SHORTPS)[0]==LoadResString(IDS_MPSEC)[0])
		speed=Speed[METRIC];
	else
	   	speed=Speed[IMPERIAL];

	infoLineCount=1;	//want to see messages											  //RDH 20/06/99

	curr=Money[ENGLISH];
//	mapfilters=-1;
	mapfilters|= FILT_RED_SUPPLY;
	mapfilters|= FILT_RED_BRIDGE;
	mapfilters|= FILT_MAINWP;
	mapfilters|= FILT_BLUE_AIRFIELDS;
	mapfilters|= FILT_FRONTLINE;

	_Analogue.deadzones[AU_AILERON] = DZ_SMALL;						  //RDH 24/05/99
	_Analogue.deadzones[AU_ELEVATOR] = DZ_SMALL;					  //RDH 24/05/99
	_Analogue.deadzones[AU_RUDDER] = DZ_SMALL;						  //RDH 24/05/99

//DEADCODE RDH 30/06/99 	Save_Data.targetsize = TS_LARGE;
	Save_Data.targetsize = TS_MEDIUM;
	Save_Data.autopilotskillUN  = 2;								  //RDH 09/07/99
	Save_Data.autopilotskillRED = 2;								  //RDH 09/07/99
	// SFX stuff...
	vol.sfx = 125;
	vol.uisfx = 125;
	vol.uiambient = 64;
	vol.music = 64;
	vol.rchat = 90;
	vol.engine = 64;

	detail_3d %= DETAIL3D_PADLOCKCHEAT;

//PD 11Feb99 - Dave I moved these up here
//PD 11Feb99 - Dave I moved these up here

	lastsavegame = "MiG Alley.sav";
	lastpackname = "MiG Alley.prf";
	lastreplayname = "MiG Alley.cam";

	//Do initialisation before here!!							//PD 11Feb99
	FileNum	sgfile=File_Man.fakefile(FIL_SAVEGAMEDIR,"settings.mig");
	if (File_Man.ExistNumberedFile(sgfile))
	{
		BIStream bis(File_Man.NameNumberedFile(sgfile));
		bis>>Save_Data;
		if (!Save_Data.successfulLoad)
		{
			MessageBox(hWnd,LoadResString(IDS_CONFIGIGNORED),LoadResString(IDS_CHOOSEPREFS),MB_OK);
			Configure(true,hWnd);
		}
	}
	else Configure(true,hWnd);
#ifndef	MIG_DEMO_VER
	SetFiltersFromSaveGame();
#endif
	//Don't put initialisation after this						//PD 11Feb99
}	

void	SaveData::SavePreferences()
{
	FileNum	sgfile=File_Man.fakefile(FIL_SAVEGAMEDIR,"settings.mig");
	BOStream bos(File_Man.NameNumberedFile(sgfile));
	bos<<Save_Data;
}
/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//static	BOStream& operator	<<	(BOStream& bos,AirFieldInfo& airfieldinfo)
//static	BIStream& operator	>>	(BIStream& bis,AirFieldInfo& airfieldinfo)
//
//
/////////////////////////////////////////////////////////////////////////////////
static	BOStream& operator	<<	(BOStream& bos,Attacks& a)	
{	return bos.write((char*)&a,sizeof(Attacks));return bos;	}
static	BIStream& operator	>>	(BIStream& bis,Attacks& a)	
{	return bis.read((char*)&a,sizeof(Attacks));return bis;	}

static	BOStream& operator	<<	(BOStream& bos,AirFieldInfo& airfieldinfo)
{
	bos<<(char&)airfieldinfo.nationality;
	bos<<airfieldinfo.capacity;
	bos<<airfieldinfo.days;
	bos<<airfieldinfo.activeac;
	bos<<airfieldinfo.attackstats;
	return bos;
}

static	BIStream& operator	>>	(BIStream& bis,AirFieldInfo& airfieldinfo)
{
	bis>>(char&)airfieldinfo.nationality;
	bis>>airfieldinfo.capacity;
	bis>>airfieldinfo.days;
	bis>>airfieldinfo.activeac;
	bis>>airfieldinfo.attackstats;
	return bis;
}

static	BOStream& operator	<<	(BOStream& bos,TeamDef& team)
{
	bos<<team.strength;
	bos<<(char&)team.team;
	bos<<team.forcename;
	bos<<(char&)team.forcetype;
	bos<<(char&)team.action;
	bos<<(char&)team.namedaction;
	bos<<team.advantagepriority;
	bos<<(UWord&)team.location;
	bos<<(UWord&)team.nextlocation;
	bos<<team.lastlosses;
	bos<<team.lastlostforces;
	return bos;
}

static	BIStream& operator	>>	(BIStream& bis,TeamDef& team)
{
	bis>>team.strength;
	bis>>(char&)team.team;
	bis>>team.forcename;
	bis>>(char&)team.forcetype;
	bis>>(char&)team.action;
	bis>>(char&)team.namedaction;
	bis>>team.advantagepriority;
	bis>>(UWord&)team.location;
	bis>>(UWord&)team.nextlocation;
	bis>>team.lastlosses;
	bis>>team.lastlostforces;
	team.node=NULL;
	team.nextnode=NULL;
	return bis;
}

static	BOStream& operator	<<	(BOStream& bos,BattleStruct& battle)
{
	for (int i=0;i<battle.MAXTEAMS;i++)
		bos<<battle.teamlist[i];
	return bos;
}
static	BIStream& operator	>>	(BIStream& bis,BattleStruct& battle)
{
	for (int i=0;i<battle.MAXTEAMS;i++)
		bis>>battle.teamlist[i];
	battle.LinkTeams();
	return bis;
}
static	BOStream& operator	<<	(BOStream& bos,SupplyLine& Supply)
{
	bos<<Supply.MaxMobiles;
	bos<<Supply.TodaysMobiles;
	bos<<Supply.CurrMobiles;
	SWord frontuid=Supply.frontline->associated_item;
	bos<<frontuid;
	bos<<(char&)Supply.attackpotential;
	bos<<(char&)Supply.FACActive;
	bos<<(char&)Supply.initiative;
	bos<<Supply.groundbattle;
	return bos;
}
static	BIStream& operator	>>	(BIStream& bis,SupplyLine& Supply)
{
	bis>>Supply.MaxMobiles;
	bis>>Supply.TodaysMobiles;
	bis>>Supply.CurrMobiles;
	SWord frontuid;
	bis>>frontuid;
	Supply.frontline=SupplyTree::FindSupplyNodeForNodeItem((UniqueID)frontuid);
	bis>>(char&)Supply.attackpotential;
	bis>>(char&)Supply.FACActive;
	bis>>(char&)Supply.initiative;
	bis>>Supply.groundbattle;

	FileNum	bf=FIL_NULL;
	FileNum	bn=FIL_NULL;
	if (	Supply.initiative==REDATTACKING
		||	Supply.initiative==REDINITIATIVE
		)
	{
		bf=Supply.frontline->bluefrontBF->bf;
		bn=Supply.frontline->bluefrontBF->nodetree;
	}
	else
	if (	Supply.initiative==BLUEATTACKING
		||	Supply.initiative==BLUEINITIATIVE
		)
	{
		bf=Supply.frontline->redfrontBF->bf;
		bn=Supply.frontline->redfrontBF->nodetree;
	}
	if (bf)
	{
		Supply.groundbattle.LoadBattleNodes(bn);
		Supply.groundbattle.LinkBattleNodes();
		Supply.groundbattle.LinkTeams();
	}

	return bis;
}

static	BOStream& operator	<<	(BOStream& bos,SupplyNode& node)
{
	bos<<(char&) node.status;
	bos<<node.currentstores;
	bos<<node.maxstorestonnes;
	bos<<(char&)node.priority;
//rdh2/2/99	bos<<node.damagelevel;
//rdh6/1/99	bos<<node.aaalevel;
	bos<<node.repairrate;
	bos<<node.maxstorestokens;
	bos<<node.attackstats;
//DEADCODE JIM 09/04/99 	if (node.next)
//DEADCODE JIM 09/04/99 		bos<<*node.next;
	return bos;
}
static	BIStream& operator	>>	(BIStream& bis,SupplyNode& node)
{
	bis>>(char&) node.status;
	bis>>node.currentstores;
	bis>>node.maxstorestonnes;
	bis>>(char&)node.priority;
	bis>>node.repairrate;
	bis>>node.maxstorestokens;
	bis>>node.attackstats;
	return bis;
}
static	BOStream& operator	<<	(BOStream& bos,SupplyRoute& route)
{
	bos<<(char&)route.status;
	bos<<route.recommision_time;
	bos<<route.storeslaunched;
	bos<<route.stores_destroyed;
	bos<<route.stores_destroyed_today;								  //RDH 25/05/99
	bos<<route.totalstores_destroyed;
	bos<<route.attackstats;
	return bos;
}
static	BIStream& operator	>>	(BIStream& bis,SupplyRoute& route)
{
	bis>>(char&)route.status;
	bis>>route.recommision_time;
	bis>>route.storeslaunched;
	bis>>route.stores_destroyed;
	bis>>route.stores_destroyed_today;								  //RDH 25/05/99
	bis>>route.totalstores_destroyed;
//rdh6/1/99	bis>>route.consecutive_days_attacked;
	bis>>route.attackstats;
	return bis;
}
/////////////////////////////////////////////////////////
void	SupplyTree::Save(BOStream& bos)
{
	for (int i=0;airfieldinfo[i].nationality!=NAT_ALIGN;i++)
		bos<<airfieldinfo[i];
	bos<<WestRoute;
	bos<<CentralRoute;
	bos<<EastRoute;
	for (SupplyNode* node=FirstNode;node->next!=node;node=node->next)
		bos<<*node;
	for (SupplyRoute* route=FirstRoute;route->next!=route;route=route->next)
		bos<<*route;
}
void	SupplyTree::Load(BIStream& bis)
{
	for (int i=0;airfieldinfo[i].nationality!=NAT_ALIGN;i++)
		bis>>airfieldinfo[i];
	bis>>WestRoute;
	bis>>CentralRoute;
	bis>>EastRoute;
	for (SupplyNode* node=FirstNode;node->next!=node;node=node->next)
		bis>>*node;
	for (SupplyRoute* route=FirstRoute;route->next!=route;route=route->next)
		bis>>*route;
}
int		BattleStruct::LoadBattleNodes(FileNum f)
{
	usednodes=0;
	if (f)
	{
		fileblock b(f);
		SuperBattleDesc::Header* header=(SuperBattleDesc::Header*)b.getdata();
		SuperBattleNode* src=(SuperBattleNode*) ((char*)b.getdata()+sizeof(SuperBattleDesc::Header));
		usednodes=(b.getsize()-sizeof(SuperBattleDesc::Header))/sizeof(SuperBattleNode);
		for (int i=0;i<usednodes;i++)
			nodelist[i]=src[i];
		for (i=0;i<usednodes;i++)
		{
			if (nodelist[i].mainuid==header->awayreinforceleft)
				awaynodes=nodelist+i;
			if (nodelist[i].mainuid==header->homereinforceleft)
				homenodes=nodelist+i;
		}
	}
	return usednodes;
}
void	BattleStruct::LinkBattleNodes()
{
	for (int i=0;i<usednodes;i++)
	{	//left/right/in pointers
		nodelist[i].firstoutnode=NULL;
		nodelist[i].occupier=NULL;
		nodelist[i].in.occupier=NULL;
		nodelist[i].out.occupier=NULL;
		for (int j=0;j<usednodes;j++)
		{
			if (nodelist[j].mainuid==nodelist[i].innerlink.uid)
				nodelist[i].innode=nodelist+j;
			if (nodelist[j].mainuid==nodelist[i].flanks.left)
				nodelist[i].flanks.leftnode=nodelist+j;
			if (nodelist[j].mainuid==nodelist[i].flanks.right)
				nodelist[i].flanks.rightnode=nodelist+j;
		}
	}
	for (int k=0;k<usednodes;k++)
	{	//outer pointer is leftmost inner counterpointer
		if (nodelist[k].innode && (!nodelist[k].flanks.leftnode || nodelist[k].flanks.leftnode->innode!=nodelist[k].innode))
		{
				nodelist[k].innode->firstoutnode=nodelist+k;
				if (!nodelist[k].out.uid && !nodelist[k].flanks.left)
					awaynodes=nodelist+k;
				if (!nodelist[k].in.uid && !nodelist[k].flanks.left)
					homenodes=nodelist+k;
		}
	}
}
void	BattleStruct::LinkTeams()
{
	for (int j=0;j<usednodes;j++)
		nodelist[j].occupier=
			nodelist[j].in.occupier=
				nodelist[j].out.occupier=NULL;

	for (int k=0;teamlist[k].strength;k++)
	{
		UniqueID comp=teamlist[k].location;
		teamlist[k].node=NULL;
		for (int j=0;j<usednodes;j++)
			if (nodelist[j].mainuid==comp)
			{
				teamlist[k].node=nodelist+j;
				nodelist[j].occupier=teamlist+k;
				break;
			}
			elseif (nodelist[j].in.uid==comp)
			{
				teamlist[k].node=nodelist+j;
				nodelist[j].in.occupier=teamlist+k;
				break;
			}
			elseif (nodelist[j].out.uid==comp)
			{
				teamlist[k].node=nodelist+j;
				nodelist[j].out.occupier=teamlist+k;
				break;
			}
		comp=teamlist[k].nextlocation;
		teamlist[k].nextnode=NULL;
		for (j=0;j<usednodes;j++)
			if (nodelist[j].mainuid==comp)
			{
				teamlist[k].nextnode=nodelist+j;
				break;
			}
			elseif (nodelist[j].in.uid==comp)
			{
				teamlist[k].nextnode=nodelist+j;
				break;
			}
			elseif (nodelist[j].out.uid==comp)
			{
				teamlist[k].nextnode=nodelist+j;
				break;
			}

	}
	usedteams=k;
}
extern	char* compiledate; 
void	SupplyTree::LoadCleanNodeTree()
{
	char buffer[150];
	bool	filegood;
	{
		BIStream bis(File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,"blank_nt.dat"),buffer));
		filegood=(bis.is_open()==TRUE);
		if (filegood)
		{
			char buffer[50];
			int len=strlen(compiledate);
			bis.read(buffer,len+4);
			buffer[len]=0;
			if (strcmp(buffer,compiledate))
				filegood=false;
		}
		if (filegood)
		{
			SupplyTree::Load(bis);
		}
	}
	if (!filegood)
	{
		BOStream bos(buffer);
		bos.write(compiledate,strlen(compiledate));
		bos.write("\n\032\0\0",4);
		SupplyTree::Save(bos);
	}
}
